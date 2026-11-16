package tests;

import org.ioopm.calculator.ast.Addition;
import org.ioopm.calculator.ast.Assignment;
import org.ioopm.calculator.ast.Clear;
import org.ioopm.calculator.ast.Constant;
import org.ioopm.calculator.ast.Cos;
import org.ioopm.calculator.ast.Division;
import org.ioopm.calculator.ast.Exp;
import org.ioopm.calculator.ast.Log;
import org.ioopm.calculator.ast.Multiplication;
import org.ioopm.calculator.ast.NamedConstant;
import org.ioopm.calculator.ast.Negation;
import org.ioopm.calculator.ast.Quit;
import org.ioopm.calculator.ast.Sin;
import org.ioopm.calculator.ast.Subtraction;
import org.ioopm.calculator.ast.SymbolicExpression;
import org.ioopm.calculator.ast.Variable;
import org.ioopm.calculator.ast.Vars;

public class IsConstantTests {

    public static void testIsConstant() {
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
        SymbolicExpression namedConstant = new NamedConstant("Answer", 42.0);
        SymbolicExpression variable = new Variable("y");
        SymbolicExpression clear = Clear.instance();
        SymbolicExpression quit = Quit.instance();
        SymbolicExpression vars = Vars.instance();

        SymbolicExpression constant = new Constant(5);

        assert !assignment.isConstant() : "Assignment should not be a constant";
        assert !addition.isConstant() : "Addition should not be a constant";
        assert !subtraction.isConstant() : "Subtraction should not be a constant";
        assert !division.isConstant() : "Division should not be a constant";
        assert !multiplication.isConstant() : "Multiplication should not be a constant";
        assert !cos.isConstant() : "Cos should not be a constant";
        assert !exp.isConstant() : "Exp should not be a constant";
        assert !log.isConstant() : "Log should not be a constant";
        assert !sin.isConstant() : "Sin should not be a constant";
        assert !negation.isConstant() : "Negation should not be a constant";
        assert !namedConstant.isConstant() : "Named constant should not be a constant"; // Is our implementation really correct?
        assert !variable.isConstant() : "Variable should not be a constant";
        assert !clear.isConstant() : "Clear should not be a constant";
        assert !quit.isConstant() : "Quit should not be a constant";
        assert !vars.isConstant() : "Vars should not be a constant";

        assert constant.isConstant() : "Constant should be a constant";
    }
}
