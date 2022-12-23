using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

namespace TicTacToeBRApp
{
    public class JogoDaVelha : INotifyPropertyChanged
    {
        private int boardCount = 0;
        private bool user1Playing = true;
        private char player1;
        private char player2;
        private int[] boardState = { 0, 0, 0,
                                      0, 0, 0,
                                      0, 0, 0 }; //0 para vazio, 1 para player1 e 2 para player2 

        public JogoDaVelha()
        {
            clearBoard();
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this , new PropertyChangedEventArgs(name));
        }

        public void UpdateSymbolContext()
        {
            OnPropertyChanged("Player1");
        }

        public bool User1Playing
        {
            get { return user1Playing; }
            set { user1Playing = value; }
        }

        public char Player1
        {
            get { return player1; }

            set
            {
                char aux = Char.ToUpper(value);
                if (aux == 'O')
                {
                    player1 = aux;
                    player2 = 'X';
                }
                else if (aux == 'X')
                {
                    player1 = aux;
                    player2 = 'O';
                }
                else
                {
                    player1 = '\0';
                    player2 = '\0';
                }
            }
        }
        public char Player2 { get { return player2; } }
        public int[] BoardState { get { return boardState; } }

        public int BoardCount { get => boardCount; set => boardCount = value; }

        public void MarkCell(int cell,byte state)
        {
            boardState[cell] = state;
        }

        public void clearBoard ()
        {
            for (byte i = 0; i < 9; i++) MarkCell(i, 0);
        }

        public override string ToString()
        {
            string print = "";
            foreach(var boardPrint in BoardState)
            {
                print += $"{boardPrint} ";
            }
            return print;
        }
    }
}