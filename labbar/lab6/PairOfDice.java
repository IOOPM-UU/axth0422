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

    public String ToString()
    {
        return "PairOfDice(" + die1 + ", " + die2 + ")";
    }
}