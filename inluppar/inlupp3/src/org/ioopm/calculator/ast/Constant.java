package org.ioopm.calculator.ast;

public class Constant extends Atom {
    private double value;

    public Constant(double value) {
        this.value = value;
        this.priority = 150;
    }

    @Override 
    public boolean isConstant() {
        return true;
    }

    @Override 
    public double getValue() {
        return this.value;
    }

    @Override 
    public String toString() {
        return String.valueOf(this.value);
    }

    @Override 
    public boolean equals(Object other) {
        if (other instanceof Constant) {
            return this.equals((Constant) other);
        } else {
            return false;
        }
    }

    public boolean equals(Constant other) {
        return this.value == other.value;
    }

    @Override 
    public SymbolicExpression eval(Environment vars) {
        return this;
    }
}
