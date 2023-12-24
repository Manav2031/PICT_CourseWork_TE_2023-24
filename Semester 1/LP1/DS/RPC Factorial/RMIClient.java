import java.rmi.*;
import java.io.*;

//import java.util.*;
public class RMIClient {
  public static void main(String args[]) {
    try {
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); // Scanner sc = new Scanner(System.in);
      MyInterface p = (MyInterface) Naming.lookup("rmiInterface");
      System.out.println("Enter a number to calculate its factorial");
      long input = Integer.parseInt(br.readLine()); // String input = sc.nextLine();
      System.out.println("Factorial of " + input + " is " +p.countInput(input));
    } catch (Exception e) {
      System.out.println("Exception occurred : " + e.getMessage());
    }
  }
}
