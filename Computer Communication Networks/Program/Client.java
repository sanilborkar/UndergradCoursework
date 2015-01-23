package udp;
import java.net.*;
import java.io.*;

public class Client {
 public static void main(String args[])
{
byte b[]=new byte[100];
try
{
DatagramSocket ds=new DatagramSocket();
//DatagramPacket dp=new DatagramPacket(b,1024);
while(true)
{
  DataInputStream dis = new DataInputStream(System.in);
  //b = byte(dis);
  dis.read(b);

DatagramPacket dp = new DatagramPacket(b,b.length,InetAddress.getLocalHost(),5001);
ds.send(dp);
//String str1 = new String(dp.getData(),0,dp.getLength());
//System.out.print(str1);

//ds.receive(dp);

dp = new DatagramPacket(b,50);
ds.receive(dp);
String str1 = new String(dp.getData(),0,dp.getLength());
System.out.print(str1);

}

}
catch(Exception e)
{}


 }
}