package tests;

import org.ioopm.calculator.ast.*;

public class EvalTests {

    public static void testAddition() {
        Environment vars = new Environment();

        SymbolicExpression const1 = new Constant(1);
        SymbolicExpression const9 = new Constant(9);

        SymbolicExpression add1 = new Addition(const1, const9);
        double sum1 = add1.eval(vars).getValue();
        assert (sum1 == 10) : ("Expected: 10, Got: " + sum1);

        SymbolicExpression constNeg = new Negation(const9);

        SymbolicExpression add2 = new Addition(const1, constNeg);
        double sum2 = add2.eval(vars).getValue();
        assert (sum2 == -8) : ("Expected: -8, Got: " + sum2);
    }

    public static void testSubtraction() {
        Environment vars = new Environment();
        
        SymbolicExpression const1 = new Constant(64);
        SymbolicExpression const2 = new Constant(64);

        SymbolicExpression sub0 = new Subtraction(const1, const2);
        double diff0 = sub0.eval(vars).getValue();
        assert (diff0 == 0) : ("Expected: 0, Got: " + diff0);

        SymbolicExpression constNeg = new Negation(const1);

        SymbolicExpression sub128 = new Subtraction(const1, constNeg);
        double diff128 = sub128.eval(vars).getValue();
        assert (diff128 == 128) : ("Expected: 128, Got: " + diff128);
    }

    public static void testMultiplication() {
        Environment vars = new Environment();
    
        SymbolicExpression const0 = new Constant(0);
        SymbolicExpression const3 = new Constant(3);
        SymbolicExpression const7 = new Constant(7);

        SymbolicExpression mult0 = new Multiplication(const0, const7);
        SymbolicExpression mult21 = new Multiplication(const7, const3);
        double prod0 = mult0.eval(vars).getValue();
        double prod21 = mult21.eval(vars).getValue();
        assert (prod0 == 0) : ("Expected: 0, Got: " + prod0);
        assert (prod21 == 21) : ("Expected: 21, Got: " + prod21);

        SymbolicExpression constNeg = new Negation(const3);
        SymbolicExpression multNeg = new Multiplication(const7, constNeg);
        double prodNeg = multNeg.eval(vars).getValue();
        assert (prodNeg == -21) : ("Expected: -21, Got: " + prodNeg);
    }

    public static void testDivision() {
        Environment vars = new Environment();

        SymbolicExpression const0 = new Constant(0);
        SymbolicExpression const9 = new Constant(9);
        SymbolicExpression const81 = new Constant(81);

        SymbolicExpression div0 = new Division(const0, const9);
        SymbolicExpression div9 = new Division(const81, const9);
        double quot0 = div0.eval(vars).getValue();
        double quot9 = div9.eval(vars).getValue();
        assert (quot0 == 0) : ("Expected: 0, Got: " + quot0);
        assert (quot9 == 9) : ("Expected: 9, Got: " + quot9);

        SymbolicExpression constNeg = new Negation(const9);
        SymbolicExpression divNeg = new Division(const81, constNeg);
        double quotNeg = divNeg.eval(vars).getValue();
        assert (quotNeg == -9) : ("Expected: -9, Got: " + quotNeg);
    }

    public static void testAssignment() {
        Environment vars = new Environment();

        SymbolicExpression const5 = new Constant(5.001);
        SymbolicExpression var = new Variable("x");

        SymbolicExpression assign = new Assignment(const5, var);
        double result = assign.eval(vars).getValue();
        assert (result == 5.001) : ("Expected: 5.001, Got: " + result);
    }

    public static void testSin() {
        Environment vars = new Environment();

        SymbolicExpression constPI = new Constant(Math.PI);
        SymbolicExpression const0 = new Constant(0);
        SymbolicExpression const2 = new Constant(2);

        SymbolicExpression sin0 = new Sin(const0);
        SymbolicExpression sin1 = new Sin(new Division(constPI, const2));
        SymbolicExpression sinNeg = new Sin(new Division(new Negation(constPI), const2));
        double result0 = sin0.eval(vars).getValue();
        double result1 = sin1.eval(vars).getValue();
        double resultNeg = sinNeg.eval(vars).getValue();
        
        assert (result0 == 0) : ("Expected: 0, Got: " + result0);
        assert (result1 == Math.sin(Math.PI/2)) : ("Expected: 1, Got: " + result1);
        assert (resultNeg == -Math.sin(Math.PI/2)) : ("Expected: -1, Got: " + resultNeg);
    }

    public static void testCos() {
        Environment vars = new Environment();

        SymbolicExpression constPI = new Constant(Math.PI);
        SymbolicExpression const0 = new Constant(0);
        SymbolicExpression const2 = new Constant(2);

        SymbolicExpression cos0 = new Cos(new Division(constPI, const2));
        SymbolicExpression cos1 = new Cos(const0);
        SymbolicExpression cosNeg = new Cos(constPI);
        double result0 = cos0.eval(vars).getValue();
        double result1 = cos1.eval(vars).getValue();
        double resultNeg = cosNeg.eval(vars).getValue();

        assert (result0 == Math.cos(Math.PI/2)) : ("Expected: 0, Got: " + result0);
        assert (result1 == 1) : ("Expected: 1, Got: " + result1);
        assert (resultNeg == Math.cos(Math.PI)) : ("Expected: -1, Got: " + resultNeg);
    }

    public static void testExponent() {
        Environment vars = new Environment();

        SymbolicExpression const0 = new Constant(0);
        SymbolicExpression const1 = new Constant(1);
        SymbolicExpression const7 = new Constant(7);
        SymbolicExpression ln7 = new Log(const7);

        SymbolicExpression e0 = new Exp(const0);
        SymbolicExpression e1 = new Exp(const1);
        SymbolicExpression e7 = new Exp(ln7);
        double result1 = e0.eval(vars).getValue();
        double resultE = e1.eval(vars).getValue();
        double result7 = e7.eval(vars).getValue();

        assert (result1 == 1) : ("Expected: 1, Got: " + result1);
        assert (resultE == Math.E) : ("Expected: " + Math.E + ", Got: " + resultE);
        assert (result7 == Math.exp(Math.log(7))) : ("Expected: " + Math.exp(Math.log(7)) + ", Got: " + result7);
    }

    public static void testLog() {
        Environment vars = new Environment();
        
        SymbolicExpression const1 = new Constant(1);
        SymbolicExpression constE = new Constant(Math.E);
        SymbolicExpression const0 = new Constant(1/Math.E);

        SymbolicExpression log1 = new Log(const1);
        SymbolicExpression log0 = new Log(const0);
        SymbolicExpression logE = new Log(constE);
        double result0 = log1.eval(vars).getValue();
        double result1 = logE.eval(vars).getValue();
        double resultNeg = log0.eval(vars).getValue();

        assert (result0 == 0) : ("Expected: 0, Got: " + result0);
        assert (result1 == 1) : ("Expected: 1, Got: " + result1);
        assert (resultNeg == -1) : ("Expected: -1, Got: " + resultNeg);
    }

    public static void testNegation() {
        Environment vars = new Environment();

        SymbolicExpression const0 = new Constant(0);
        SymbolicExpression const6 = new Constant(6);
        SymbolicExpression const9 = new Constant(-9);

        SymbolicExpression neg0 = new Negation(const0);
        SymbolicExpression neg6 = new Negation(const6);
        SymbolicExpression neg9 = new Negation(const9);
        double negation0 = neg0.eval(vars).getValue();
        double negation6 = neg6.eval(vars).getValue();
        double negation9 = neg9.eval(vars).getValue();
        
        assert (negation0 == 0) : ("Expected: 0, Got: " + negation0);
        assert (negation6 == -6) : ("Expected: -6, Got: " + negation6);
        assert (negation9 == 9) : ("Expected: 9, Got: " + negation9);
    }

    public static void testVariable() {
        Environment vars = new Environment();

        Variable varX = new Variable("x");
        Variable varY = new Variable("y");
        Variable varZ = new Variable("z");
        SymbolicExpression const2 = new Constant(2);
        SymbolicExpression const6 = new Constant(6);
        SymbolicExpression const89 = new Constant(89);

        vars.put(varX, const2);
        vars.put(varY, const6);
        vars.put(varZ, const89);

        double resultX = varX.eval(vars).getValue();
        double resultY = varY.eval(vars).getValue();
        double resultZ = varZ.eval(vars).getValue();

        assert (resultX == 2) : ("Expected: 2, Got: " + resultX);
        assert (resultY == 6) : ("Expected: 6, Got: " + resultY);
        assert (resultZ == 89) : ("Expected: 89, Got: " + resultZ);
    }

    public static void testConstant() {
        Environment vars = new Environment();

        SymbolicExpression const0 = new Constant(0);
        SymbolicExpression const73 = new Constant(73);
        SymbolicExpression const53 = new Constant(-53);
    
        double result0 = const0.eval(vars).getValue();
        double result73 = const73.eval(vars).getValue();
        double result53 = const53.eval(vars).getValue();

        assert (result0 == 0) : ("Expected: 0, Got: " + result0);
        assert (result73 == 73) : ("Expected: 73, Got: " + result73);
        assert (result53 == -53) : ("Expected: -53, Got: " + result53);
    }

    public static void testLongExpression() {
        Environment vars = new Environment();

        SymbolicExpression const7 = new Constant(7);
        SymbolicExpression sin1 = new Sin((SymbolicExpression) new Constant(Math.PI/2));
        SymbolicExpression sub22 = new Subtraction(new Constant(32), new Constant(10));
        SymbolicExpression add15 = new Addition(new Constant(7), new Constant(8));
        SymbolicExpression mult = new Multiplication(add15, sub22);
        SymbolicExpression div = new Division(mult, sin1);

        SymbolicExpression sub = new Subtraction(div, const7);

        double result = sub.eval(vars).getValue();

        assert (result == 323) : ("Expected: 323, Got: " + result); 
    }
}
