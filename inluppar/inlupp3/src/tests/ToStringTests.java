package tests;

import org.ioopm.calculator.ast.*;

public class ToStringTests {

    public static void testAtomExpression() {
        SymbolicExpression actual;
        String expected;

        actual = new Constant(7734);
        expected = "7734.0";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);

        actual = new Variable("x");
        expected = "x";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);

        actual = new NamedConstant("Answer", 42.0);
        expected = "Answer";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);
    }

    public static void testUnaryExpression() {
        SymbolicExpression actual;
        String expected;

        actual = new Sin(new Constant(4859));
        expected = "Sin( 4859.0 )";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);

        actual = new Cos(new Constant(3234));
        expected = "Cos( 3234.0 )";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);

        actual = new Exp(new Constant(1589));
        expected = "Exp( 1589.0 )";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);

        actual = new Log(new Constant(1648));
        expected = "Log( 1648.0 )";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);

        actual = new Negation(new Constant(1916));
        expected = "-1916.0";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);
    }

    public static void testBinaryExpression() {
        SymbolicExpression actual;
        String expected;

        actual = new Addition(new Constant(1), new Constant(2));
        expected = "1.0 + 2.0";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);

        actual = new Subtraction(new Constant(5), new Constant(2));
        expected = "5.0 - 2.0";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);

        actual = new Multiplication(new Constant(5), new Constant(6));
        expected = "5.0 * 6.0";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);

        actual = new Division(new Constant(15), new Constant(3));
        expected = "15.0 / 3.0";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);

        actual = new Assignment(new Constant(10), new Variable("x"));
        expected = "10.0 = x";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);
    }

    public static void testNestedExpression() {
        SymbolicExpression actual;
        String expected;

        actual = new Division(
                new Addition(new Constant(3), new Constant(2)),
                new Multiplication(new Constant(2), new Constant(3)));

        expected = "( 3.0 + 2.0 ) / ( 2.0 * 3.0 )";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);

        actual = new Negation(new Addition(new Constant(2), new Constant(3)));

        expected = "-( 2.0 + 3.0 )";

        assert actual.toString().compareTo(expected) == 0 : "\nExpected: %s\nActual:   %s".formatted(expected, actual);
    }
}
