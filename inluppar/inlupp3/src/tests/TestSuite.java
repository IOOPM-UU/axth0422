package tests;

public class TestSuite {

    public static void main(String[] args) {
        System.out.println("Starting tests");

        EvalTests.testAddition();
        EvalTests.testSubtraction();
        EvalTests.testMultiplication();
        EvalTests.testDivision();
        EvalTests.testAssignment();
        EvalTests.testSin();
        EvalTests.testCos();
        EvalTests.testExponent();
        EvalTests.testLog();
        EvalTests.testNegation();
        EvalTests.testVariable();
        EvalTests.testConstant();
        EvalTests.testLongExpression();

        EqualsTests.testAtomExpression();
        EqualsTests.testBinaryExpression();
        EqualsTests.testEqualValueButNotEqualTree();
        EqualsTests.testUnaryExpression();

        ParserTests.testAtomExpression();
        ParserTests.testBinaryExpression();
        ParserTests.testCommandExpression();
        ParserTests.testUnaryExpression();

        ToStringTests.testAtomExpression();
        ToStringTests.testBinaryExpression();
        ToStringTests.testNestedExpression();
        ToStringTests.testUnaryExpression();

        PriorityTests.testPriority();

        IsCommandTests.testIsCommand();

        GetNameTests.testGetName();

        IsConstantTests.testIsConstant();

        GetValueTests.testGetValue();

        System.out.println("Tests done");
    }
}
