VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form frmServer 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Server"
   ClientHeight    =   5385
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7635
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5385
   ScaleWidth      =   7635
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Listen"
      Height          =   375
      Left            =   6360
      TabIndex        =   4
      Top             =   120
      Width           =   1095
   End
   Begin VB.TextBox txtLocalPort 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   5400
      TabIndex        =   3
      Text            =   "8170"
      Top             =   165
      Width           =   735
   End
   Begin VB.TextBox txtInput 
      Appearance      =   0  'Flat
      Height          =   285
      Left            =   120
      TabIndex        =   1
      Top             =   4920
      Width           =   7335
   End
   Begin MSWinsockLib.Winsock Winsock1 
      Left            =   720
      Top             =   1680
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.TextBox txtHistory 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      Height          =   4335
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   600
      Width           =   7335
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Local Port"
      Height          =   195
      Left            =   4560
      TabIndex        =   2
      Top             =   210
      Width           =   720
   End
End
Attribute VB_Name = "frmServer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
Winsock1.LocalPort = txtLocalPort.Text
Winsock1.Protocol = sckTCPProtocol
Winsock1.Listen
txtHistory.Text = "Waiting for client request ... "
Command1.Enabled = False
End Sub

Private Sub txtInput_KeyDown(KeyCode As Integer, Shift As Integer)
If KeyCode = 13 Then
    Winsock1.SendData txtInput.Text
    txtHistory.Text = txtHistory.Text & "Server : " & txtInput.Text & vbNewLine & vbNewLine
    txtInput.Text = ""
    txtInput.SetFocus
End If
Exit Sub
End Sub

Private Sub Winsock1_ConnectionRequest(ByVal requestID As Long)
Winsock1.Close
Winsock1.Accept requestID
txtHistory.Text = txtHistory.Text & " Accepted!" & vbNewLine & vbNewLine
End Sub

Private Sub Winsock1_DataArrival(ByVal bytesTotal As Long)
Winsock1.GetData Txt, vbString, 100
txtHistory.Text = txtHistory.Text & "Client : " & Txt & vbNewLine & vbNewLine
End Sub

