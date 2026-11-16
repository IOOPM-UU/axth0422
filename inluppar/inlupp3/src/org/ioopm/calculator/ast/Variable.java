package org.ioopm.calculator.ast;

public class Variable extends Atom {
    private String identifier;

    public Variable(String identifier) {
        this.identifier = identifier;
        this.priority = 150;
    }

    @Override 
    public String toString() {
        return this.identifier;
    }

    @Override 
    public boolean equals(Object other) {
        if (other instanceof Variable) {
            return this.equals((Variable) other);
        } else {
            return false;
        }
    }

    public boolean equals(Variable other) {
        return this.identifier.compareTo(other.identifier) == 0;
    }

    @Override 
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = vars.get(this);

        if (arg == null) {
            return this;
        }

        if (!arg.isConstant()) {
            return arg;
        }

        return new Constant(arg.getValue());
    }

    @Override 
    public int hashCode() {
        return identifier.hashCode();
    }
}
