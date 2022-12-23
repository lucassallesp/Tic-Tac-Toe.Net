using System;
using System.Diagnostics;
using System.Windows;

namespace TicTacToeBRApp
{
    /// <summary>
    /// Interaction logic for PopUp.xaml
    /// </summary>
    public partial class PopUp : Window
    {
        JogoDaVelha jogoDaVelha;
        public PopUp(JogoDaVelha refObj) : base()
        {
            InitializeComponent();
            jogoDaVelha = refObj;
        }
        private void ButtonO_Click(object sender, RoutedEventArgs e)
        {
            jogoDaVelha.Player1 = 'O';
            jogoDaVelha.clearBoard();
            jogoDaVelha.UpdateSymbolContext();
            Debug.WriteLine($"{jogoDaVelha.Player1} foi escolhido pelo usuario");
            this.Close();
        }
        private void ButtonX_Click(object sender, RoutedEventArgs e)
        {
            jogoDaVelha.Player1 = 'X';
            jogoDaVelha.clearBoard();
            jogoDaVelha.UpdateSymbolContext();
            Debug.WriteLine($"{jogoDaVelha.Player1} foi escolhido pelo usuario");
            this.Close();
        }

        private void popUp_Closed(object sender, EventArgs e)
        {
            //symbolsMenu.Text = JogoDaVelha.PlayerSymbol.ToString();
            this.Close();
        }

        private void QuitButton_Click(object sender, RoutedEventArgs e)
        {           
            this.Close();
            
        }

        private void btnUser1_Click(object sender, RoutedEventArgs e)
        {
            jogoDaVelha.User1Playing = true; // usuario joga
            btnUser2.IsChecked = false;
        }

        private void btnUser2_Checked(object sender, RoutedEventArgs e)
        {
            jogoDaVelha.User1Playing = false; // robo joga
            btnUser1.IsChecked = false;
        }
    }
}