package tests;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

public class ParserTests {

    public static void testAtomExpression() {
        try {
            CalculatorParser parser = new CalculatorParser();
            Environment vars = new Environment();
            String input;
            SymbolicExpression output;

            input = "3";

            output = parser.parse(input, vars);

            assert (output instanceof Constant) : "Output not constant";

            assert (output.getValue() == 3) : "Incorrect value";

            input = "x";

            output = parser.parse(input, vars);

            assert (output instanceof Variable) : "Output not variable";

            assert (output.toString().compareTo(input) == 0) : "Variable identifier incorrect";

            input = "pi";

            output = parser.parse(input, vars);

            assert (output instanceof NamedConstant) : "Output not Named Constant";

            assert (output.toString().compareTo(input) == 0) : "Named constant name incorrect";
        } catch (Exception e) {
            assert false : e;
        }
    }

    public static void testCommandExpression() {
        try {
            CalculatorParser parser = new CalculatorParser();
            Environment vars = new Environment();
            String input;
            SymbolicExpression output;

            input = "Quit";

            output = parser.parse(input, vars);

            assert (output.isCommand()) : "Output not command";

            assert (output instanceof Quit) : "Output not quit command";

            input = "Vars";

            output = parser.parse(input, vars);

            assert (output.isCommand()) : "Output not command";

            assert (output instanceof Vars) : "Output not vars command";

            input = "Clear";

            output = parser.parse(input, vars);

            assert (output.isCommand()) : "Output not command";

            assert (output instanceof Clear) : "Output not clear command";
        } catch (Exception e) {
            assert false : e;
        }
    }

    public static void testUnaryExpression() {
        try {
            CalculatorParser parser = new CalculatorParser();
            Environment vars = new Environment();
            String input;
            SymbolicExpression output;

            input = "Sin(3)";

            output = parser.parse(input, vars);

            assert (output instanceof Sin) : "Output not Sin";

            input = "Cos(3)";

            output = parser.parse(input, vars);

            assert (output instanceof Cos) : "Output not Cos";

            input = "Log(3)";

            output = parser.parse(input, vars);

            assert (output instanceof Log) : "Output not Log";

            input = "Exp(3)";

            output = parser.parse(input, vars);

            assert (output instanceof Exp) : "Output not Exp";

            input = "Neg(3)";

            output = parser.parse(input, vars);

            assert (output instanceof Negation) : "Output not Negation";

            input = "-3";

            output = parser.parse(input, vars);

            assert (output instanceof Negation) : "Output not Negation";
        } catch (Exception e) {
            assert false : e;
        }
    }

    public static void testBinaryExpression() {
        try {
            CalculatorParser parser = new CalculatorParser();
            Environment vars = new Environment();
            String input;
            SymbolicExpression output;

            input = "2 + 3";

            output = parser.parse(input, vars);

            assert (output instanceof Addition) : "Output not Addition";

            input = "3 - 2";

            output = parser.parse(input, vars);

            assert (output instanceof Subtraction) : "Output not Subtraction";

            input = "3 * 4";

            output = parser.parse(input, vars);

            assert (output instanceof Multiplication) : "Output not Multiplication";

            input = "7 / 4";

            output = parser.parse(input, vars);

            assert (output instanceof Division) : "Output not Division";

            input = "3 = x";

            output = parser.parse(input, vars);

            assert (output instanceof Assignment) : "Output not Assignment";
        } catch (Exception e) {
            assert false : e;
        }
    }
}
