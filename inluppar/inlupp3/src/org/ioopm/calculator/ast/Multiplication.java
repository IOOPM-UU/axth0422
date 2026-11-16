package org.ioopm.calculator.ast;

public class Multiplication extends Binary implements ExpressionInterface {
    
    public Multiplication(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
        this.priority = 60;
    }

    @Override 
    public String getName() {
        return "*";
    }

    @Override 
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhs = this.lhs.eval(vars);
        SymbolicExpression rhs = this.rhs.eval(vars);

        if (lhs.isConstant() && rhs.isConstant()) {
            return new Constant(lhs.getValue() * rhs.getValue());
        }

        return new Multiplication(lhs, rhs);
    }
}
