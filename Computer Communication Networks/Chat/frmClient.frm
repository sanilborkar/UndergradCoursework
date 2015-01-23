VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form frmClient 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Client"
   ClientHeight    =   5355
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7815
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5355
   ScaleWidth      =   7815
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Connect"
      Height          =   375
      Left            =   6600
      TabIndex        =   8
      Top             =   120
      Width           =   1095
   End
   Begin VB.TextBox txtRemPort 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   5640
      TabIndex        =   7
      Text            =   "8170"
      Top             =   165
      Width           =   735
   End
   Begin VB.TextBox txtRemIP 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   3120
      TabIndex        =   5
      Text            =   "127.0.0.1"
      Top             =   165
      Width           =   1335
   End
   Begin VB.TextBox txtLocalPort 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   1200
      TabIndex        =   3
      Text            =   "8171"
      Top             =   165
      Width           =   735
   End
   Begin VB.TextBox txtInput 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   240
      TabIndex        =   1
      Top             =   4920
      Width           =   7335
   End
   Begin MSWinsockLib.Winsock Winsock1 
      Left            =   1200
      Top             =   2520
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.TextBox txtHistory 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      Height          =   4335
      Left            =   240
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   600
      Width           =   7335
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "Remote Port"
      Height          =   195
      Left            =   4635
      TabIndex        =   6
      Top             =   210
      Width           =   885
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "Remote IP"
      Height          =   195
      Left            =   2280
      TabIndex        =   4
      Top             =   210
      Width           =   750
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Local Port"
      Height          =   195
      Left            =   360
      TabIndex        =   2
      Top             =   210
      Width           =   720
   End
End
Attribute VB_Name = "frmClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
txtHistory.Text = "Connecting to server ... "
Winsock1.Protocol = sckTCPProtocol
Winsock1.RemoteHost = txtRemIP.Text
Winsock1.RemotePort = txtRemPort.Text
Winsock1.LocalPort = txtLocalPort.Text
Winsock1.Connect
txtHistory.Text = txtHistory.Text & " Connected" & vbNewLine & vbNewLine
Command1.Enabled = False
End Sub

Private Sub txtInput_KeyDown(KeyCode As Integer, Shift As Integer)
If KeyCode = 13 Then
    Winsock1.SendData txtInput.Text
    txtHistory.Text = txtHistory.Text & "Client : " & txtInput.Text & vbNewLine & vbNewLine
    txtInput.Text = ""
    txtInput.SetFocus
End If
End Sub

Private Sub Winsock1_DataArrival(ByVal bytesTotal As Long)
Winsock1.GetData Txt, vbString, 100
txtHistory.Text = txtHistory.Text & "Server : " & Txt & vbNewLine & vbNewLine
End Sub
