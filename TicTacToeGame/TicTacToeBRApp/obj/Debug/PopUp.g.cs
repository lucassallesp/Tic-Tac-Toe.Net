#pragma checksum "..\..\PopUp.xaml" "{8829d00f-11b8-4213-878b-770e8597ac16}" "4476EC5F4A10BA98C921995E678CF87980959479BFF9E24299E4823A614F3E6B"
//------------------------------------------------------------------------------
// <auto-generated>
//     O código foi gerado por uma ferramenta.
//     Versão de Tempo de Execução:4.0.30319.42000
//
//     As alterações ao arquivo poderão causar comportamento incorreto e serão perdidas se
//     o código for gerado novamente.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;
using TicTacToeBRApp;


namespace TicTacToeBRApp {
    
    
    /// <summary>
    /// PopUp
    /// </summary>
    public partial class PopUp : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 1 "..\..\PopUp.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal TicTacToeBRApp.PopUp popUp;
        
        #line default
        #line hidden
        
        
        #line 14 "..\..\PopUp.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button ButtonX;
        
        #line default
        #line hidden
        
        
        #line 15 "..\..\PopUp.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button Button0;
        
        #line default
        #line hidden
        
        
        #line 27 "..\..\PopUp.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.RadioButton btnUser1;
        
        #line default
        #line hidden
        
        
        #line 28 "..\..\PopUp.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.RadioButton btnUser2;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/TicTacToeBRApp;component/popup.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\PopUp.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.popUp = ((TicTacToeBRApp.PopUp)(target));
            
            #line 8 "..\..\PopUp.xaml"
            this.popUp.Closed += new System.EventHandler(this.popUp_Closed);
            
            #line default
            #line hidden
            return;
            case 2:
            this.ButtonX = ((System.Windows.Controls.Button)(target));
            
            #line 14 "..\..\PopUp.xaml"
            this.ButtonX.Click += new System.Windows.RoutedEventHandler(this.ButtonX_Click);
            
            #line default
            #line hidden
            return;
            case 3:
            this.Button0 = ((System.Windows.Controls.Button)(target));
            
            #line 15 "..\..\PopUp.xaml"
            this.Button0.Click += new System.Windows.RoutedEventHandler(this.ButtonO_Click);
            
            #line default
            #line hidden
            return;
            case 4:
            this.btnUser1 = ((System.Windows.Controls.RadioButton)(target));
            
            #line 27 "..\..\PopUp.xaml"
            this.btnUser1.Click += new System.Windows.RoutedEventHandler(this.btnUser1_Click);
            
            #line default
            #line hidden
            return;
            case 5:
            this.btnUser2 = ((System.Windows.Controls.RadioButton)(target));
            
            #line 28 "..\..\PopUp.xaml"
            this.btnUser2.Checked += new System.Windows.RoutedEventHandler(this.btnUser2_Checked);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}

