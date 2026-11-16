package org.ioopm.calculator.ast;

public class Exp extends Unary implements FunctionInterface {

    public Exp(SymbolicExpression primary) {
        super(primary);
        this.priority = 90;
    }

    @Override 
    public String getName() {
        return "Exp";
    }

    @Override 
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = this.primary.eval(vars);

        if (!arg.isConstant()) {
            return new Exp(arg);
        }

        return new Constant(Math.exp(arg.getValue()));
    }
}
