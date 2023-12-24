import java.rmi.*;

public interface MyInterface extends Remote {
  public long countInput(long input) throws RemoteException;
}