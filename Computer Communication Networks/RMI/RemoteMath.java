/* defines the interface RemoteMath which is used to support 
 RMI based simple math operations. */

import java.rmi.*;

// The interface must extend the Remote interface to become something
// that RMI can serve up. 

public interface RemoteMath extends Remote {

    public int Add(int x, int y) throws RemoteException;
    public int Sub(int x, int y) throws RemoteException;
    public int Mult(int x, int y) throws RemoteException;
    public int Div(int x, int y) throws RemoteException;
}

