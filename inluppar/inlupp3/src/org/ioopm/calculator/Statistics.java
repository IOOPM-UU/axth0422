package org.ioopm.calculator;

public class Statistics {
    private int noExpressions = 0;
    private int noSuccessful = 0;
    private int noFully = 0;

    public void addNoExpressions() {
        noExpressions++;
    }

    public void addNoSuccessful() {
        noSuccessful++;
    }

    public void addNoFully() {
        noFully++;
    }

    public int getNoExpressions() {
        return noExpressions;
    }

    public int getNoSuccessful() {
        return noSuccessful;
    }

    public int getNoFully() {
        return noFully;
    }
}
