   M S B A M L   `   `   `  ????I  ETicTacToeBRApp, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null/clr-namespace:TicTacToeBRAppTicTacToeBRApp  5   	       TicTacToeBRApp.PopUp   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   .localclr-namespace:TicTacToeBRApp     5   	   -   5          ?Name$  popUp??5   	    ? Title$ Seleção de Símbolo??5   	   $	??250??6$   $	??310??61   $	??310??6S   $	??250??6b   $	??310??6r   $	??250??6?    ? WindowStartupLocation$ CenterScreen=?6?   .??5	      ? $??0,0,2,0q?6    ? ColumnDefinitions 5
   
   ?? 5      $??1* ?6   ?? 5      $??1* ?6   .+?5   
   ?? -   5         ??Name$ ButtonX??5      $??X??6"   $
??Left=?6.   $??	56,72,0,0q?6I   $	??Top=?6\   $??77??6?   $??22??6?   ?? 5   
   -   5        $ Button0??5      $??0??6"   $
??Left=?6.   $??	12,72,0,0q?6I   $	??Top=?6\   $??80??6t   $??22??6   $??1??6?   ?? 5   
    J? RenderTransformOrigin$ 0.5,0.5&?6   $??70,28,63,149q?60   $??Símbolo do Jogador 1??6F   $??15(?6e   $??2??6s   z?5      V? 5      .~?5      ?? ?? 5      ?? 5       ?? Angle$ 0.398Q?6&   T? 5      5      5      	? 5   
   -   5         	?Name$ btnUser1??5      $??	Jogador 1??6(   $
??Left=?6<   $??
74,153,0,0q?6W   $	??Top=?6k   $??11(?6?   $??18??6?   $??68??6?    d? 	IsChecked$
 TrueY?6?   	? 5   
   -   5        $ btnUser2??5      $??	Jogador 2??6(   $
??Left=?6<   $??
14,153,0,0q?6W   $	??Top=?6k   $??1??6?   $??11(?6?   $??18??6?   $??69??6?   6?   ?? 5   
   $ 0.5,0.5&?6   $??60,116,50,68q?60   $'??!Escolha Quem Irá Jogar Primeiro!??6F   $??2??6q   z?5      V? 5      .~?5       ?? ?? 5!      ?? 5"      $ 0.398Q?6&   T? 5#      5$      5'      5(      5)      