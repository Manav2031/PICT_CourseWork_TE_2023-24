let displayValue = "";

function appendToDisplay(value) {
    displayValue += value;
    document.getElementById('display').value = displayValue;
}

function clearDisplay() {
    displayValue = "";
    document.getElementById('display').value = displayValue;
}

function calculate() {
    try {
        displayValue = eval(displayValue);
        document.getElementById('display').value = displayValue;
    } catch (error) {
        alert("Invalid input");
        clearDisplay();
    }
}

function calculateSquare() {
    try {
        displayValue = eval(displayValue);
        displayValue = Math.pow(displayValue, 2);
        document.getElementById('display').value = displayValue;
    } catch (error) {
        alert("Invalid input");
        clearDisplay();
    }
}
