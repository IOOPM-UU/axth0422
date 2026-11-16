package tests;

import org.ioopm.calculator.ast.*;

public class EqualsTests {
    public static void testAtomExpression() {
        SymbolicExpression expr;
        SymbolicExpression exprCorrect;
        SymbolicExpression exprIncorrect;

        expr = new Constant(5);
        exprCorrect = new Constant(5);
        exprIncorrect = new Constant(2);
        assert (expr.equals(exprCorrect)) : "Equal constants are not equal";
        assert (!expr.equals(exprIncorrect)) : "Unequal constants are equal";

        expr = new NamedConstant("Answer", 42.0);
        exprCorrect = new NamedConstant("Answer", 42.0);
        exprIncorrect = new NamedConstant("L", 6.022140857E23);
        assert (expr.equals(exprCorrect)) : "Equal named constants are not equal";
        assert (!expr.equals(exprIncorrect)) : "Unequal named constants are equal";

        expr = new Variable("x");
        exprCorrect = new Variable("x");
        exprIncorrect = new Variable("y");
        assert (expr.equals(exprCorrect)) : "Equal variables are not equal";
        assert (!expr.equals(exprIncorrect)) : "Unequal variables are equal";
    }

    public static void testUnaryExpression() {
        SymbolicExpression expr;
        SymbolicExpression exprCorrect;
        SymbolicExpression exprIncorrect;

        expr = new Sin(new Constant(1));
        exprCorrect = new Sin(new Constant(1));
        exprIncorrect = new Sin(new Constant(3));

        assert (expr.equals(exprCorrect)) : "Equal unary expressions are not equal";
        assert (!expr.equals(exprIncorrect)) : "Unequal unary expressions are equal";
    }

    public static void testBinaryExpression() {
        SymbolicExpression expr;
        SymbolicExpression exprCorrect;
        SymbolicExpression exprIncorrect;

        expr = new Addition(new Constant(2), new Constant(3));
        exprCorrect = new Addition(new Constant(2), new Constant(3));
        exprIncorrect = new Addition(new Constant(2), new Constant(4));

        assert (expr.equals(exprCorrect)) : "Equal binary expressions are not equal";
        assert (!expr.equals(exprIncorrect)) : "Unequal binary expressions are equal";
    }

    public static void testEqualValueButNotEqualTree() {
        SymbolicExpression expr1 = new Addition(new Constant(2), new Constant(3));
        SymbolicExpression expr2 = new Constant(5);

        assert (!expr1.equals(expr2)) : "Expressions without identical trees should not be equal";
    }
}
