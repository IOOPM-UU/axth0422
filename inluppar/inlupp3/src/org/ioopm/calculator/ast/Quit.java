package org.ioopm.calculator.ast;

import org.ioopm.calculator.Statistics;

public class Quit extends Command {
    private static final Quit theInstance = new Quit();
    private Quit() {}
    public static Quit instance() {
        return theInstance;
    }

    @Override 
    public void execute(Environment vars, Statistics stats) {
        System.out.println("Quitting");
        System.out.println("Total number of expressions: " + stats.getNoExpressions());
        System.out.println("Total successful evaluations: " + stats.getNoSuccessful());
        System.out.println("Total fully evaluated: " + stats.getNoFully());
        System.exit(0);
    }
}
