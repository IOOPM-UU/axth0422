package org.ioopm.calculator.ast;

public class Sin extends Unary implements FunctionInterface {

    public Sin(SymbolicExpression primary) {
        super(primary);
        this.priority = 90;
    }

    @Override 
    public String getName() {
        return "Sin";
    }

    @Override 
    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression arg = this.primary.eval(vars);

        if (!arg.isConstant()) {
            return new Sin(arg);
        }

        return new Constant(Math.sin(arg.getValue()));
    }
}
