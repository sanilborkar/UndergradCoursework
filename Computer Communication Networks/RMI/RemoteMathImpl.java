/* Implementation of RemoteMath interface for RMI server
 This class implements the interface RemoteMath which is used to support 
 RMI based simple math operations. This class extends
 UnicastRemoteObject (this is the simplest way to create a class
 that will become available as a remote object). See the example
 named AlternativeSimpleRMI for another approach... */

import java.net.*;    	// need this for MalformedURLException
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;

/* Note that this class will be used to
 generate stub and skeleton files ... (using rmic)

 In this example we include a main, in general you would probably not
 include a main() in the remote object class definitions... */

public class RemoteMathImpl extends UnicastRemoteObject implements RemoteMath {

    /* We need to create a constructor (even if it does nothing).
     The constructor must throw RemoteException - since 
        when a new UnicastRemoteObject is created it requires some
        communication resources that may not be available!
     In this constructor we just call the constructor for
     UnicastRemoteObject which exports the object */

    public RemoteMathImpl() throws RemoteException {
	super();
    }

    /* For this simple example we include a main here, in general
     we will define remote objects and create them elsewhere
     (in general we don't put main inside the implementation
     of a remote object). */

    public static void main(String args[]) { 
	try {
	    // create a RemoteMathImpl object 
	    RemoteMathImpl r = new RemoteMathImpl();

	    // register the object with the rmi registry
	    // (registry mush already be running)
	    Naming.rebind("ReMath",r);
	    System.out.println("Registered RemoteMath object\n"); 

	} catch (RemoteException e) {
	    System.out.println("RemoteException: " + e.getMessage());
	    e.printStackTrace();

	} catch (MalformedURLException m) {
	    System.out.println("URL Problem: " + m.getMessage());
	    m.printStackTrace();
	}
    }

    /* Below are the actual remote methods. Although these are
     simple methods in this example - it's worth noting that aside
     from the declaration that each can throw RemoteException, there
     is no difference between the code in these methods and in
     a local method (the fact that these methods can be called
     remotely doesn't change the way we write the code.

     LogRequest is just doing some printing here, although in a real
     service you might want to replace this with code that does
     something fancy (actually log to a file or to syslog). */

    public int Add(int x, int y) throws RemoteException {
	LogRequest("ADD: " + x + "+" + y);
	return(x+y);
    }
    public int Sub(int x, int y) throws RemoteException {
	LogRequest("SUB: " + x + "-" + y);
	return(x-y);
    }
    public int Mult(int x, int y) throws RemoteException {
	LogRequest("MULT: " + x + "*" + y);
	return(x*y);
    }
    public int Div(int x, int y) throws RemoteException {
	LogRequest("DIV: " + x + "/" + y);
	return(x/y);
    }

    void LogRequest(String s) {
	System.out.println("RemoteMath Request: " + s );
    }

}


