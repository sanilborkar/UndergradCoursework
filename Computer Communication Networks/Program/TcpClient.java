import java.io.*;
import java.net.*;
public class TcpClient
{	public static void main(String args[])	
{		try
	
{
			String str2="";
			InetAddress addr = InetAddress.getLocalHost();
    
 			// Get IP Address
 			str2  = addr.getHostAddress();	

			Socket ss=new Socket(str2,3129);
			InputStream i=ss.getInputStream();
			OutputStream o=ss.getOutputStream();								DataOutputStream dos=new DataOutputStream(o);
			DataInputStream dis=new DataInputStream(i);
			byte b[]=new byte[200];
			String str="";

		while(true)			
{

				System.out.println("Enter request to server");
				int k=System.in.read(b);
				str=new String(b,0,k-2);
				str=str+" from "+str2;
				dos.writeUTF(str);

				str=dis.readUTF();
				System.out.println("Response from server is  "+str);
			}
		}
		catch(Exception ee)
		{			System.out.println(ee);		
}	
}
}


