import java.rmi.*;
public interface MyInterface extends Remote
{
 public String countInput(String input)throws RemoteException;   
}