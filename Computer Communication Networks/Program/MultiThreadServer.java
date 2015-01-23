import java.io.*;
import java.net.*;
import java.util.*;
import java.awt.*;
import javax.swing.*;

public class MultiThreadServer extends JFrame {
    
    private JTextArea jta = new JTextArea();

    /** Creates a new instance of SimpleServer */
    public MultiThreadServer() {
        // place text area on the frame
        getContentPane().setLayout(new BorderLayout());
        getContentPane().add(new JScrollPane(jta), BorderLayout.CENTER);
        
        setTitle("Simple Server");
        setSize(500, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

        jta.setEditable(false);
        
        try {
            ServerSocket serverSocket = new ServerSocket(4242);
            System.out.println("Server is upp and running");
            jta.append("Server started at " + new Date() + "\n");
            
            String messageReceived = null;
            
            while (true) {
                
            Socket socket = serverSocket.accept(); // accept connections
            
            InetAddress inetAddress = socket.getInetAddress(); // used to get host information
            
            /* Get host IP and hostname and display on the window */
            jta.append("Client connected to the server!\n" + 
                    "Client's host name is: " + inetAddress.getHostName() + "\n" +
                    "Client's IP Address is: " + inetAddress.getHostAddress() + "\n");
            
            // Create a new thread for connection
            HandleAClient thread = new HandleAClient(socket);
            
            thread.start();

            }
        }
        catch (IOException ex) {
            System.err.println(ex);
        }
        
    }
    
    public static void main(String[] args) {
        new MultiThreadServer();
    }

    // inned class to handle a new connection
    class HandleAClient extends Thread {
    
        private Socket socket; // a connected socket
    
        /** Creates a new thread */
        public HandleAClient(Socket socket) {
            this.socket = socket;
        }
    
        public void run() {
            try {
            
                DataInputStream inputFromClient = new DataInputStream(socket.getInputStream());
                DataOutputStream outputToClient = new DataOutputStream(socket.getOutputStream());
    
                while (true) {
                
                    String messageReceived = inputFromClient.readUTF();
                                                
                    // this is more like a joke. Ignore this ^_^
                    if (messageReceived.equals("+kill_server")) {
                        System.exit(0);
                    }
                                
                    outputToClient.writeUTF(messageReceived);
                
                    jta.append("User said: " + messageReceived);
   
                }
        
            } catch (IOException ex) {
                System.err.println(ex);
            }
       }
        
    } // close handle client
    
} // close MultiThreadServer
// Client