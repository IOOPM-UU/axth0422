package tests;

import org.ioopm.calculator.ast.*;

public class PriorityTests {

    public static void testPriority() {
        SymbolicExpression assignment = new Assignment(new Constant(3), new Variable("x"));

        SymbolicExpression addition = new Addition(new Constant(3), new Constant(3));
        SymbolicExpression subtraction = new Subtraction(new Constant(7), new Constant(4));

        SymbolicExpression division = new Division(new Constant(3), new Constant(9));
        SymbolicExpression multiplication = new Multiplication(new Constant(5), new Constant(4));

        SymbolicExpression cos = new Cos(new Constant(2));
        SymbolicExpression exp = new Exp(new Constant(3));
        SymbolicExpression log = new Log(new Constant(1));
        SymbolicExpression sin = new Sin(new Constant(8));

        SymbolicExpression negation = new Negation(new Constant(3));

        SymbolicExpression constant = new Constant(5);
        SymbolicExpression namedConstant = new NamedConstant("Answer", 42.0);
        SymbolicExpression variable = new Variable("y");

        assert assignment.getPriority() < addition.getPriority()
                : "Assignment should have a lower priorty than addition";

        assert addition.getPriority() == subtraction.getPriority()
                : "Addition and subtraction should have the same priority";

        assert subtraction.getPriority() < division.getPriority()
                : "Subtraction should have a lower priority than division";

        assert division.getPriority() == multiplication.getPriority()
                : "Division and multiplication should have the same priority";

        assert multiplication.getPriority() < cos.getPriority()
                : "Multiplication should have a lower priority than cos";

        assert cos.getPriority() == exp.getPriority() : "Cos and exp should have the same priority";

        assert exp.getPriority() == log.getPriority() : "Exp and cos should have the same priority";

        assert log.getPriority() == sin.getPriority() : "Log and sin should have the same priority";

        assert log.getPriority() < negation.getPriority() : "Log should have a lower priority than negation";

        assert negation.getPriority() < constant.getPriority() : "Negation should have a lower priority than constants";

        assert constant.getPriority() == namedConstant.getPriority()
                : "Constants and named constants should have the same priority";

        assert namedConstant.getPriority() == variable.getPriority()
                : "Named constants and variables should have the same priority";

    }

}
