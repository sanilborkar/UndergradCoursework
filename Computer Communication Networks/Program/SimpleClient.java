import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.awt.*;
import javax.swing.*;

public class SimpleClient extends JFrame implements ActionListener {
    
    private JTextField jtfMessageToSend = new JTextField();
    
    private JTextArea jtaMessageReceived = new JTextArea();
    
    private JButton btnSend = new JButton("Send");
    
    private DataOutputStream toServer;
    
    private DataInputStream fromServer;
    
    /** Creates a new instance of SimpleClient */
    public SimpleClient() {
        
        JPanel p = new JPanel();
        p.setLayout(new BorderLayout());
        p.add(new JLabel("Message to send: "), BorderLayout.WEST);
        btnSend.addActionListener(this);
        btnSend.setMnemonic('s');
        p.add(btnSend, BorderLayout.EAST);
        p.add(jtfMessageToSend, BorderLayout.CENTER);
        jtfMessageToSend.setHorizontalAlignment(JTextField.LEFT);
        jtaMessageReceived.setEditable(false);
        
        getContentPane().setLayout(new BorderLayout());
        getContentPane().add(p, BorderLayout.SOUTH);
        getContentPane().add(new JScrollPane(jtaMessageReceived), BorderLayout.CENTER);
        
        jtfMessageToSend.addActionListener(this);
        
        setTitle("SimpleClient");
        setSize(500, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        
        try {
            Socket socket = new Socket("localhost", 4242);
            
            fromServer = new DataInputStream(socket.getInputStream());
            
            toServer = new DataOutputStream(socket.getOutputStream());
            
        }
        catch (IOException ex) {
            jtaMessageReceived.append(ex.toString());
        }
        
    }

    public void actionPerformed(ActionEvent e) {
        String actionCommand = e.getActionCommand();
        if (e.getSource() instanceof JTextField || e.getSource() == btnSend) {
            try {
                toServer.writeUTF(jtfMessageToSend.getText());
                toServer.flush();
                jtfMessageToSend.setText("");
                
                String messageToDisplay = fromServer.readUTF();
                jtaMessageReceived.append(messageToDisplay + "\n");
                
            }
            catch (IOException ex) {
                System.err.println(ex);
            }
        }
    }
    
    public static void main(String[] args) {
        new SimpleClient();
    }
    
}