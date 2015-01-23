package udp;

import java.net.*;
import java.io.*;


public class Server {

public static void main(String args[])
{
byte b[]=new byte[100];
try
{
DatagramSocket ds=new DatagramSocket(5001);

while(true)
{

DatagramPacket dp = new DatagramPacket(b,50);
ds.receive(dp);
int tmp = dp.getPort();
String str1 = new String(dp.getData(),0,dp.getLength());
System.out.print(str1);


 DataInputStream dis = new DataInputStream(System.in);
 dis.read(b);

dp = new DatagramPacket(b,50,InetAddress.getLocalHost(),tmp);
ds.send(dp);




//ds.send(dp);


}

}
catch(Exception e)
{}



}

}
