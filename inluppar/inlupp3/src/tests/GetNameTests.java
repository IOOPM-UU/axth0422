package tests;

import org.ioopm.calculator.ast.*;

public class GetNameTests {
    
    public static void testGetName() {
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

        assert assignment.getName().equals("=") : "Incorrect name for assignment";
        assert addition.getName().equals("+") : "Incorrect name for addition";
        assert subtraction.getName().equals("-") : "Incorrect name for subtraction";
        assert division.getName().equals("/") : "Incorrect name for division";
        assert multiplication.getName().equals("*") : "Incorrect name for multiplication";
        assert cos.getName().equals("Cos") : "Incorrect name for cos";
        assert exp.getName().equals("Exp") : "Incorrect name for exp";
        assert log.getName().equals("Log") : "Incorrect name for log";
        assert sin.getName().equals("Sin") : "Incorrect name for sin";
        assert negation.getName().equals("-") : "Incorrect name for negation";
    }
}
