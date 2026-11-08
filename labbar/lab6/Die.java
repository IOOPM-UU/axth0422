import java.util.Scanner;

public class Die {
    private int numberOfSides;
    private int value;

    public Die(int sides) {
        if (sides < 1) {
            throw new IllegalArgumentException(sides + " is an illegal number of sides for die");
        }
        this.numberOfSides = sides;
        this.value = 1;
    }

    public int roll() {
        this.value = (int) (Math.random() * numberOfSides) + 1;
        return this.get();
    }

    public int get() {
        return value;
    }

    public String toString() {
        return "Die(" + value + ")";
    }

    boolean equals(Die otherDie) {
        return this.value == otherDie.get();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Number of sides: ");
        int sides = sc.nextInt();
        Die d = new Die(sides);
        System.out.println("Alea iacta est: " + d.roll());
        sc.close();
    }
}
