package org.ioopm.calculator.ast;

public interface ExpressionInterface {

    static public String getFormat(String name, SymbolicExpression[] args) {
        if (args.length == 1) {
            if (args[0] instanceof Binary) {
                return name + "( %s )".formatted(args[0]);
            }
            return name + "%s".formatted(args[0]);
        }
        else 
        {
            return "%s ".formatted(args[0]) + name + " %s".formatted(args[1]);
        }
    }
} 
