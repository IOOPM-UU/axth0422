package labbar.lab6;

import java.util.Scanner;

public class NameOrder {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the first string: ");
        String name1 = sc.nextLine();
        System.out.println("Enter the second string: ");
        String name2 = sc.nextLine();
        sc.close();
        if (name1.compareTo(name2) < 0) {
            System.out.println(name1);
            System.out.println(name2);
        } else {
            System.out.println(name2);
            System.out.println(name1);
        }
    }
}