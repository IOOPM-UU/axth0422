package org.ioopm.calculator.ast;

public class Assignment extends Binary {

    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super(lhs, rhs);
        this.priority = 10;
    }

    @Override
    public String getName() {
        return "=";
    }

    @Override
    public String toString() {
        String lhsStr = "";
        String rhsStr = "";
        if (lhs.priority < this.priority) {
            lhsStr = "( " + lhs + " )";
        } else {
            lhsStr = lhs.toString();
        }

        if (rhs.priority < this.priority) {
            rhsStr = "( " + rhs + " )";
        } else {
            rhsStr = rhs.toString();
        }

        return lhsStr + " = " + rhsStr;
    }

    public SymbolicExpression eval(Environment vars) {
        SymbolicExpression lhs = this.lhs.eval(vars);

        if (rhs instanceof Variable) {
            vars.put((Variable) rhs, lhs);
            return lhs;
        }

        throw new IllegalAssignmentException("Can not assign to anything other than variables");
    }
}
