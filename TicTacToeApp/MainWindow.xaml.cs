using System;
using System.IO.Ports;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace TicTacToeBRApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        JogoDaVelha jogoDaVelha;
        SerialPort serialPort;
        string[] serialPorts;
        public MainWindow()
        {
            jogoDaVelha = new JogoDaVelha();
            PopUp popUp = new PopUp(jogoDaVelha);
            popUp.ShowDialog();

            InitializeComponent();
            InitializeSerialPorts();
            InitializeGame();
        }

        private void Window_Initialized(object sender, EventArgs e)
        {
            symbolsMenu.Text = "Jogador 1: " + jogoDaVelha.Player1.ToString() + "\nJogador 2: " + jogoDaVelha.Player2.ToString();
            btA1.Click += new RoutedEventHandler(BClick);
            btA2.Click += new RoutedEventHandler(BClick);
            btA3.Click += new RoutedEventHandler(BClick);
            btA4.Click += new RoutedEventHandler(BClick);
            btA5.Click += new RoutedEventHandler(BClick);
            btA6.Click += new RoutedEventHandler(BClick);
            btA7.Click += new RoutedEventHandler(BClick);
            btA8.Click += new RoutedEventHandler(BClick);
            btA9.Click += new RoutedEventHandler(BClick);
        }

        private void InitializeSerialPorts()
        {
            serialPorts = SerialPort.GetPortNames();
            if (serialPorts.Count() != 0)
            {
                SerialPortConnectBtn.IsEnabled = true;
                foreach (string serial in serialPorts)
                {
                    var serialItems = SerialPortNamesCmbBox.Items;
                    if (!serialItems.Contains(serial)) // if the serial is not yet inside the combobox 
                    {
                        SerialPortNamesCmbBox.Items.Add(serial);  // add a serial port name to combo box
                    }
                }
                SerialPortNamesCmbBox.SelectedItem = serialPorts[0];// combobox as default selected item 
            }
            else { SerialPortConnectBtn.IsEnabled = false; }
        }

        #region WPF to Arduino connection
        bool isConnectedToArduino = false;

        private void ConnectToArduino()
        {
            try
            {
                string selectedSerialPort = SerialPortNamesCmbBox.SelectedItem.ToString(); // gets the selected port
                serialPort = new SerialPort(selectedSerialPort, 9600);
                serialPort.Open();
                SerialPortConnectBtn.Content = "Disconnect";
                TurnOnButtons();
                isConnectedToArduino = true;
            }
            catch (UnauthorizedAccessException)
            {
                MessageBox.Show("The selected serial port is busy!", "Busy", MessageBoxButton.OK, MessageBoxImage.Stop);
            }
            catch (NullReferenceException)
            {
                MessageBox.Show("There is no serial port!", "Empty Serial Port", MessageBoxButton.OK, MessageBoxImage.Exclamation);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }
        }

        private void DisconnectFromArduino()
        {
            SerialPortConnectBtn.Content = "Connect";
            isConnectedToArduino = false;
            serialPort.Close();
            TurnOffButtons();
        }

        private void SerialPortConnectBtn_Click(object sender, RoutedEventArgs e)
        {
            if (!isConnectedToArduino)
            {
                ConnectToArduino();
            }
            else
            {
                DisconnectFromArduino();
            }
        }

        private void TurnOffButtons()
        {
            btA1.IsEnabled = false;
            btA2.IsEnabled = false;
            btA3.IsEnabled = false;
            btA4.IsEnabled = false;
            btA5.IsEnabled = false;
            btA6.IsEnabled = false;
            btA7.IsEnabled = false;
            btA8.IsEnabled = false;
            btA9.IsEnabled = false;
        }

        private void TurnOnButtons()
        {
            btA1.IsEnabled = true;
            btA2.IsEnabled = true;
            btA3.IsEnabled = true;
            btA4.IsEnabled = true;
            btA5.IsEnabled = true;
            btA6.IsEnabled = true;
            btA7.IsEnabled = true;
            btA8.IsEnabled = true;
            btA9.IsEnabled = true;
        }
        #endregion

        private void BClick(object sender, EventArgs e)
        {
            int playerIndex;
            if (jogoDaVelha.User1Playing)
            {
                ((Button)sender).Content = jogoDaVelha.Player1;
                jogoDaVelha.MarkCell(ButtonSelected(sender), 1);
                playerIndex = 2;
            }
            else
            {
                ((Button)sender).Content = jogoDaVelha.Player2;
                jogoDaVelha.MarkCell(ButtonSelected(sender), 2);
                playerIndex = 1;
            }
            jogoDaVelha.BoardCount++;
            ((Button)sender).IsEnabled = false;

            MakeTheMove(ButtonSelected(sender) + 1);
            CheckWinCondition(jogoDaVelha, jogoDaVelha.BoardCount);
            playerBox.Text = $"Jogador {playerIndex}";
            jogoDaVelha.User1Playing = !jogoDaVelha.User1Playing;
        }
        /// <summary>
        /// - "m" + "numero(1 - 9)" para mover para posição escolhida, "c" para fechar garra, "o" para abrir a garra, 
        /// </summary>
        private void MakeTheMove(int pos)
        {
            serialPort.Write("o");
            WaitManipulatorResponse(2000);
            serialPort.Write("");

            serialPort.Write("c");
            WaitManipulatorResponse(3000);
            serialPort.Write("");

            serialPort.Write("m" + pos.ToString());
            WaitManipulatorResponse(10000);
            
        }
        
        void WaitManipulatorResponse(int time)
        {
            Thread.Sleep(time);
        }
        private int ButtonSelected(object refObj)
        {
            if (((Button)refObj) == btA1) { return 0; }
            else if (((Button)refObj) == btA2) { return 1; }
            else if (((Button)refObj) == btA3) { return 2; }
            else if (((Button)refObj) == btA4) { return 3; }
            else if (((Button)refObj) == btA5) { return 4; }
            else if (((Button)refObj) == btA6) { return 5; }
            else if (((Button)refObj) == btA7) { return 6; }
            else if (((Button)refObj) == btA8) { return 7; }
            else if (((Button)refObj) == btA9) { return 8; }
            else { return -1; }
        }

        private void CheckWinCondition(JogoDaVelha jg, int count)
        {
            if (
                jg.BoardState[0] != 0 && jg.BoardState[0] == jg.BoardState[1] && jg.BoardState[1] == jg.BoardState[2] || //linha 1
                jg.BoardState[3] != 0 && jg.BoardState[3] == jg.BoardState[4] && jg.BoardState[4] == jg.BoardState[5] || //linha 2
                jg.BoardState[6] != 0 && jg.BoardState[6] == jg.BoardState[7] && jg.BoardState[7] == jg.BoardState[8] || //linha 3

                jg.BoardState[0] != 0 && jg.BoardState[0] == jg.BoardState[3] && jg.BoardState[3] == jg.BoardState[6] || //coluna 1
                jg.BoardState[1] != 0 && jg.BoardState[1] == jg.BoardState[4] && jg.BoardState[4] == jg.BoardState[7] || //coluna 2                                                                                                                           //coluna 2
                jg.BoardState[2] != 0 && jg.BoardState[2] == jg.BoardState[5] && jg.BoardState[5] == jg.BoardState[8] || //coluna 3

                jg.BoardState[0] != 0 && jg.BoardState[0] == jg.BoardState[4] && jg.BoardState[4] == jg.BoardState[8] || //diagonal \
                jg.BoardState[2] != 0 && jg.BoardState[2] == jg.BoardState[4] && jg.BoardState[4] == jg.BoardState[6]    //diagonal /
              )
            {
                if (jogoDaVelha.User1Playing)
                {
                    MessageBox.Show("O ganhador é o Jogador 1");
                }
                else { MessageBox.Show("O ganhador é o Jogador 2"); }
                TurnOffButtons();
            }

            if (jogoDaVelha.BoardCount == 9)
            {
                MessageBox.Show("Ops! Deu velha...");
            }
        }

        private void InitializeGame()
        {
            btA1.IsEnabled = false;
            btA2.IsEnabled = false;
            btA3.IsEnabled = false;
            btA4.IsEnabled = false;
            btA5.IsEnabled = false;
            btA6.IsEnabled = false;
            btA7.IsEnabled = false;
            btA8.IsEnabled = false;
            btA9.IsEnabled = false;

            if (jogoDaVelha.User1Playing)
            {
                playerBox.Text = "Jogador 1";
            }
            else
            {
                playerBox.Text = "Jogador 2";
            }
        }

        private void RefreshBtn_Click(object sender, RoutedEventArgs e)
        {
            InitializeSerialPorts();
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            //try
            //{
            //    if (serialPort.IsOpen == true)    // se porta aberta
            //    {
            //      MessageBox.Show("Porta serial foi fechada");
            //      serialPort.Close();            //fecha a porta
            //    }     
            //}
            //catch (NullReferenceException)
            //{
            //    Close();
            //}
            if (serialPort.IsOpen == true)  // se porta aberta
            {
                MessageBox.Show("Porta serial foi fechada");
                serialPort.Close();             //fecha a porta
            }
        }
    }
}