package org.ioopm.calculator.ast;

public interface FunctionInterface {

    static public String getFormat(String name, String[] args) {
        return "%s( %s )".formatted(name, String.join(", ", args));
    }
}
