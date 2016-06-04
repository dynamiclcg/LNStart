import java.util.Scanner;
/*
 * File : HelloWorldV1.java
 * ------------------------------
 * add the scanner features
 */
public class HelloWorldV1{
    public static void main(String[] args){
	Scanner input = new Scanner(System.in);
	String fname; 
	String lname;
	System.out.println("Please enter your first name: ");
	fname=input.next();
	System.out.println("Please enter your last name: ");
	lname=input.next();
	System.out.printf("Hello world! %s - %s \n" ,lname,fname);
    }
}
