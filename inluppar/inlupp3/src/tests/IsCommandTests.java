package tests;

import org.ioopm.calculator.ast.*;

public class IsCommandTests {

    public static void testIsCommand() {
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

        SymbolicExpression clear = Clear.instance();
        SymbolicExpression quit = Quit.instance();
        SymbolicExpression vars = Vars.instance();

        assert !assignment.isCommand() : "Assignment should not be a command";
        assert !addition.isCommand() : "Addition should not be a command";
        assert !subtraction.isCommand() : "Subtraction should not be a command";
        assert !division.isCommand() : "Division should not be a command";
        assert !multiplication.isCommand() : "Multiplication should not be a command";
        assert !cos.isCommand() : "Cos should not be a command";
        assert !exp.isCommand() : "Exp should not be a command";
        assert !log.isCommand() : "Log should not be a command";
        assert !sin.isCommand() : "Sin should not be a command";
        assert !negation.isCommand() : "Negation should not be a command";
        assert !constant.isCommand() : "Constant should not be a command";
        assert !namedConstant.isCommand() : "NamedConstant should not be a command";
        assert !variable.isCommand() : "Variable should not be a command";

        assert clear.isCommand() : "Clear should be a command";
        assert quit.isCommand() : "Quit should be a command";
        assert vars.isCommand() : "Vars should be a command";
    }

}
