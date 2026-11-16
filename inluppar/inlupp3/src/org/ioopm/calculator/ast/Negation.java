package org.ioopm.calculator.ast;

public class Negation extends Unary implements ExpressionInterface {

    public Negation(SymbolicExpression primary) {
        super(primary);
        this.priority = 100;
    }

    @Override 
    public String getName() {
        return "-";
    }

    @Override 
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = this.primary.eval(vars);

        if (!arg.isConstant()) {
            return new Negation(arg);
        }

        return new Constant(-(arg.getValue()));
    }
}
