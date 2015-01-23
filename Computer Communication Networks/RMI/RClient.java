// Sample client for RemoteMath RMI object

/* This client expects a hostname and 2 numbers on the command line.
 the hostname is the host running the RMI server, and the client
 calls each of the RemoteMath methods with the numbers specified. */

import java.rmi.*;

public class RClient {
    
    public static void main(String args[]) {
	if (args.length != 3) {
	    System.out.println("Usage: RClient hostname num1 num2");
	} else {
	    System.out.println("Remote Client Starting");

	    // Grab the command line parameters
	    String hostname = args[0];
	    int num1 = Integer.parseInt(args[1]);
	    int num2 = Integer.parseInt(args[2]);

	    /* creating the remote object - there are a number of
	     exceptions that can arise:
	    
	     Naming.lookup can throw NotBound if the name isn't bound.
	     RemoteException if the remote registry isn't running
	     AccessException (security stuff - not an issue here)
	     MalformedURLException - bad rmi URL
	     In general there are a bunch of other exceptions that can crop up
	     due to all the network (socket) code that happens when Naming.lookup
	     is called, or when the remote object methods are invoked. */

	    try {
		// The naming service returns a generic object
		// the name of the server is specified using an rmi URL

		Object o = Naming.lookup("rmi://"+hostname+"/ReMath");

		// need to cast the generic object as something that
		// supports the RemoteMath interface.

		RemoteMath r = (RemoteMath) o;

		// Now we have a RemoteMath object r - the rest of the code
		// look just like it would if this was a local object!

		System.out.println(num1 + "+" + num2 + " = " + r.Add(num1,num2));
		System.out.println(num1 + "-" + num2 + " = " + r.Sub(num1,num2));
		System.out.println(num1 + "*" + num2 + " = " + r.Mult(num1,num2));
		System.out.println(num1 + "/" + num2 + " = " + r.Div(num1,num2));

	    } catch (Exception e) {
		System.out.println("ERROR " + e.getMessage());
		e.printStackTrace();
	    }
	}
    }
}
