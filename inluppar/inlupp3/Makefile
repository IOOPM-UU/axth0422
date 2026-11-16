all:
	javac -d classes -sourcepath src src/org/ioopm/calculator/Calculator.java

run:
	java -cp classes org.ioopm.calculator.Calculator

test:
	javac -d classes -sourcepath src src/tests/TestSuite.java
	java -enableassertions -cp classes tests/TestSuite

clean:
	rm -rf classes