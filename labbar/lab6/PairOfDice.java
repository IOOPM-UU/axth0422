package labbar.lab6;

public class PairOfDice {
    private Die die1;
    private Die die2;

    public PairOfDice(int sides) {
        this.die1 = new Die(sides);
        this.die2 = new Die(sides);
    }

    public int roll() {
        return die1.roll() + die2.roll();
    }

    public int getDie1() {
        return die1.get();
    }

    public int getDie2() {
        return die2.get();
    }

    public String toString() {
        return "PairOfDice(%s, %s)".formatted(die1, die2);
    }

    public static void main(String[] args) {
        PairOfDice pod = new PairOfDice(20);

        System.out.println(pod.roll());
        System.out.println(pod.getDie1());
        System.out.println(pod.getDie2());
        System.out.println(pod);
    }
}