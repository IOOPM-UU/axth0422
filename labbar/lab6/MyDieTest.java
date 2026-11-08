import java.util.Scanner;

public class MyDieTest {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Number of sides: ");
        int sides = sc.nextInt();

        Die d = new Die(sides);

        int sum = 0;
        for (int i = 0; i < 10; i++) {
            sum += d.roll();
        }

        System.out.println("Alea iacta est: " + sum);

        sc.close();
    }
}