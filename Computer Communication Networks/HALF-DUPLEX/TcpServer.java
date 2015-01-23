import java.io.*;
import java.net.*;
public class TcpServer
{
	public static void main(String args[])
	{
		try
		{
			ServerSocket sc=new ServerSocket(3128);
			Socket ss=sc.accept();
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
				System.out.println(name+":");  //create msg and send to client
				k=System.in.read(b);
				put=new String(b,0,k-2);
				dos.writeUTF(name+":"+put);

				get=dis.readUTF();       //get msg from client and print
				System.out.println(get);
			}
		}
		catch(Exception ee)
		{
			System.out.println(ee);
		}
	}
}