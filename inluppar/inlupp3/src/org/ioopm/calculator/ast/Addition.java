package org.ioopm.calculator.ast;

public class Addition extends Binary implements  ExpressionInterface {

    public Addition(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
        this.priority = 30;
    }

    @Override 
    public String getName() {
        return "+";
    }

    @Override 
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhs = this.lhs.eval(vars);
        SymbolicExpression rhs = this.rhs.eval(vars);

        if (lhs.isConstant() && rhs.isConstant()) {
            return new Constant(lhs.getValue() + rhs.getValue());
        }

        return new Addition(lhs, rhs);
    }
}
