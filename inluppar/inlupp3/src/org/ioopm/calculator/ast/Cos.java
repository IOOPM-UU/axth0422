package org.ioopm.calculator.ast;

public class Cos extends Unary implements FunctionInterface {

    public Cos(SymbolicExpression primary) {
        super(primary);
        this.priority = 90;
    }

    @Override 
    public String getName() {
        return "Cos";
    }

    @Override 
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = this.primary.eval(vars);

        if (!arg.isConstant()) {
            return new Cos(arg);
        }

        return new Constant(Math.cos(arg.getValue()));
    }
}
