package org.ioopm.calculator.ast;

public abstract class Unary extends SymbolicExpression {
    protected SymbolicExpression primary = null;

    public Unary(SymbolicExpression primary) {
        this.primary = primary;
    }

    @Override 
    public String toString() {

        if (FunctionInterface.class.isAssignableFrom(getClass())) {
            String[] args = { primary.toString() };
            return FunctionInterface.getFormat(getName(), args);
        }
        SymbolicExpression[] args = { primary };
        return ExpressionInterface.getFormat(getName(), args);
    }

    @Override 
    public boolean equals(Object other) {
        if (other instanceof Unary) {
            return this.equals((Unary) other);
        }

        return false;
    }

    public boolean equals(Unary other) {
        boolean primaryEq = this.primary.equals(other.primary);
        boolean nameEq = this.getName().compareTo(other.getName()) == 0;
        return primaryEq && nameEq;
    }
}
