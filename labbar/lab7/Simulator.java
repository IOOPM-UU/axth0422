package labbar.lab7;

import java.util.Random;
import java.util.stream.Collectors;
import java.util.ArrayList;
import java.util.Collections;

class Customer {
    private int bornTime;
    private int groceries;

    public Customer(int bornTime, int groceries) {
        this.bornTime = bornTime;
        this.groceries = groceries;
    }

    public void serve() {
        this.groceries--;
    }

    public boolean isDone() {
        return groceries == 0;
    }

    public int getGroceries() {
        return groceries;
    }

    public int getBornTime() {
        return this.bornTime;
    }
}

class Register {
    private boolean open;
    private Queue queue;

    public Register() {
        open = false;
        queue = new Queue();
    }

    public void open() {
        this.open = true;
    }

    public void close() {
        this.open = false;
    }

    public boolean isOpen() {
        return open;
    }

    public boolean hasCustomers() {
        return queue.length() > 0;
    }

    public boolean currentCustomerIsDone() {
        return queue.first().isDone();
    }

    public void addToQueue(Customer c) {
        queue.enqueue(c);
    }

    public Customer removeCurrentCustomer() {
        return queue.dequeue();
    }

    public Customer getCurrentCustomer() {
        return queue.first();
    }

    public int getQueueLength() {
        return queue.length();
    }

    public String toString() {
        if (!open) {
            return " X [ ]\n\n";
        }

        if (queue.length() == 0) {
            return "   [ ]\n\n";
        }

        return "   [%d]%s\n\n".formatted(queue.first().getGroceries(), queue);

    }
}

class Queue {
    class Node {
        public Customer element;
        public Node next;
        public Node prev;

        public Node(Node prev, Node next, Customer element) {
            this.prev = prev;
            this.next = next;
            this.element = element;
        }
    }

    private Node vanguard;
    private Node sternguard;
    private int length;

    public Queue() {
        this.vanguard = new Node(null, sternguard, null);
        this.sternguard = new Node(vanguard, null, null);
        this.length = 0;
    }

    public int length() {
        return this.length;
    }

    public void enqueue(Customer c) {
        Node node = new Node(sternguard.prev, sternguard, c);
        sternguard.prev.next = node;
        sternguard.prev = node;

        length++;

    }

    public Customer dequeue() {
        Node node = vanguard.next;

        node.next.prev = vanguard;
        vanguard.next = node.next;

        length--;

        return node.element;
    }

    public Customer first() {
        return vanguard.next.element;
    }

    public String toString() {
        return "@".repeat(length);
    }
}

class Store {
    private Register[] registers;

    public Store(int registerCount) {
        this.registers = new Register[registerCount];

        for (int i = 0; i < registers.length; i++) {
            registers[i] = new Register();
        }

        registers[0].open();
    }

    public float getAverageQueueLength() {
        int sum = 0;
        int openRegisters = 0;
        for (Register register : registers) {
            if (register.isOpen()) {
                sum += register.getQueueLength();
                openRegisters++;
            }
        }

        return ((float) sum) / ((float) openRegisters);
    }

    public void newCustomer(Customer c) {
        Register shortest = registers[0];
        for (Register register : registers) {
            if (register.getQueueLength() < shortest.getQueueLength() && register.isOpen()) {
                shortest = register;
            }
        }

        shortest.addToQueue(c);
    }

    public void step() {
        for (Register r : registers) {
            if (r.isOpen() && r.hasCustomers()) {
                r.getCurrentCustomer().serve();
            }
        }
    }

    public void openNewRegister() {
        for (Register register : registers) {
            if (!register.isOpen()) {
                register.open();
                break;
            }
        }
    }

    public ArrayList<Customer> getDoneCustomers() {

        ArrayList<Customer> done = new ArrayList<Customer>();

        for (Register register : registers) {
            if (register.isOpen() && register.hasCustomers() && register.currentCustomerIsDone()) {
                // TODO: Is this correct?
                done.add(register.removeCurrentCustomer());
            }
        }

        return done;
    }

    public String toString() {
        String storelayout = "";
        for (Register r : registers) {
            storelayout += r;
        }

        return storelayout;
    }
}

class Simulation {
    private Store store;
    private int time;
    private int intensity;
    private int maxGroceries;
    private int thresholdForNewRegister;

    private ArrayList<Integer> waitingTimes;

    public Simulation(int intensity, int maxGroceries, int thresholdForNewRegister, int registers) {
        this.store = new Store(registers);
        this.waitingTimes = new ArrayList<Integer>();
        this.time = 0;
        this.intensity = intensity;
        this.maxGroceries = maxGroceries;
        this.thresholdForNewRegister = thresholdForNewRegister;
    }

    public void step() {
        time++;
        store.step();
        waitingTimes.addAll(
                store.getDoneCustomers().stream().map(s -> time - s.getBornTime()).collect(Collectors.toList()));
        Random random = new Random();

        if (random.nextInt(100) < intensity) {
            store.newCustomer(new Customer(time, random.nextInt(maxGroceries - 1) + 1));
        }

        if (store.getAverageQueueLength() > thresholdForNewRegister) {
            store.openNewRegister();
        }
    }

    public String toString() {
        String storelayout = store.toString();
        int max = 0;
        float average = 0;
        int size = waitingTimes.size();
        if (size > 0) {
            max = Collections.max(waitingTimes);
            average = (float) waitingTimes.stream().mapToInt(Integer::intValue).sum() / size;
        }
        return "\n\n%sNumer of customers served: %d\nMax wait-time: %d\nAverage wait-time: %.2f".formatted(storelayout,
                size, max, average);
    }
}

public class Simulator {

    public static void main(String[] args) throws InterruptedException {
        int steps = 100;
        Simulation s = new Simulation(50, 15, 3, 4);
        for (int i = 0; i < steps; i++) {
            System.out.print("\033[2J\033[;H");
            s.step();
            System.out.println(s);
            Thread.sleep(500);
        }
        System.out.println("");
        System.out.println("Simulation finished!");
    }
}
