import java.io.*;
import java.net.*;
class TcpServer
{	public static void main(String args[])
	{
		try	
	{
			ServerSocket sc=new ServerSocket(3129);
			Socket ss=sc.accept();	
			InputStream i=ss.getInputStream();
			OutputStream o=ss.getOutputStream();
			DataOutputStream dos=new DataOutputStream(o);
			DataInputStream dis=new DataInputStream(i);
			byte b[]=new byte[200];
			String str="";

			while(true)
			{
				str=dis.readUTF();
				System.out.println("message received: "+str);

				str="Received";

				dos.writeUTF(str);
							
}		
}	
	catch(Exception ee)	
	{
			System.out.println(ee);
	}	
}
}