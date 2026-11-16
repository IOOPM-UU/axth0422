package org.ioopm.calculator.ast;

import org.ioopm.calculator.Statistics;

public class Vars extends Command {
    private static final Vars theInstance = new Vars();

    private Vars() {
    }

    public static Vars instance() {
        return theInstance;
    }

    @Override 
    public void execute(Environment vars, Statistics stats) {
        for (Variable key : vars.keySet()) {
            System.out.println("%s = %s".formatted(key, vars.get(key)));
        }
    }
}
