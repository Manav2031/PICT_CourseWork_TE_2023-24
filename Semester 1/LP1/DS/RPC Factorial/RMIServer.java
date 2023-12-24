import java.rmi.*;
import java.rmi.server.*;

public class RMIServer extends UnicastRemoteObject implements MyInterface {
  public RMIServer() throws RemoteException {
    System.out.println("Remote Server is running Now.!!");
  }

  public static void main(String args[]) {
    try {
      RMIServer p = new RMIServer();
      Naming.rebind("rmiInterface", p);
    } catch (Exception e) {
      System.out.println("Exception occurred : " + e.getMessage());
    }
  }

  @Override
  public long countInput(long input) throws RemoteException {
    System.out.println("Received your input "+input+" at server");
    long f = 1;
    for (int i = 1; i <= input; i++)
      f = f * i;
    return f;
  }
}
