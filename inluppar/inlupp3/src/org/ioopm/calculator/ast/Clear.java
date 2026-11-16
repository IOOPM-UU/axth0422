package org.ioopm.calculator.ast;

import org.ioopm.calculator.Statistics;

public class Clear extends Command {
    private static final Clear theInstance = new Clear();
    private Clear() {}
    public static Clear instance() {
        return theInstance;
    }

    @Override 
    public void execute(Environment vars, Statistics stats) {
        
        vars.clear();
        System.out.println("Cleared variables");
    }
}
