package tests;

import org.ioopm.calculator.ast.*;

public class GetValueTests {

    public static void testGetValue() {
        SymbolicExpression const1 = new Constant(1);
        SymbolicExpression const2 = new Constant(5);
        SymbolicExpression const3 = new Constant(1000);
        SymbolicExpression const4 = new Constant(1.523E5);

        assert const1.getValue() == 1 : "Incorrect value from getValue";
        assert const2.getValue() == 5 : "Incorrect value from getValue";
        assert const3.getValue() == 1000 : "Incorrect value from getValue";
        assert const4.getValue() == 152300 : "Incorrect value from getValue";
    }
}
