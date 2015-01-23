import java.io.*;
import java.net.*;
public class TcpClient
{
	public static void main(String args[])
	{
		try
		{
			String str2="";
			InetAddress addr = InetAddress.getLocalHost();
			str2  = addr.getHostAddress();

			Socket ss=new Socket(str2,3128);
			InputStream i=ss.getInputStream();
			OutputStream o=ss.getOutputStream();
			DataOutputStream dos=new DataOutputStream(o);
			DataInputStream dis=new DataInputStream(i);
			byte b[]=new byte[200];
			String put="";
			String get="";
			String name="";
			System.out.println("Enter your name");
			int k=System.in.read(b);
			name=new String(b,0,k-2);
			
			while(true)
			{
				get=dis.readUTF();       //read msg from server and print
				System.out.println(get);  

				System.out.println(name+":");  //client sends it's message
				k=System.in.read(b);
				put=new String(b,0,k-2);
				dos.writeUTF(name+":"+put);

			}
		}
		catch(Exception ee)
		{
			System.out.println(ee);
		}
	}
}