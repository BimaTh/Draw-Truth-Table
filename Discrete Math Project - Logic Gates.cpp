/*
	Date: 10/12/2023

	Name: Ibrahim Ahmed Abdelfattah
	ID: 23P0279
	Group Number: 41

	Description: This program will simulate a logic gate circuit and output the truth table for the circuit and a simplified version of the circuit.
	Use only basic C++ code and do not use any advanced C++ code or any other libraries.
	Do not use any classes. Use only functions and arrays.

	The circuit will have 3 inputs, A, B, and C. AND, OR, and NOT gates will be used to create the circuit. + a Light bulb to show the output.

	Variable to define the function of the circuit

	The Function is : (~C OR A) AND (~C OR B) AND (C OR A) AND (C OR B)
	The function is simplified to :
*/	

#include <iostream>
#include <string>
using namespace std;


// Number of possible inputs for the circuit
const int INPUTS_COUNT = 8;

// Struct to store the inputs and output of the circuit
struct BinaryVariable {
	bool A = 0;
	bool B = 0;
	bool C = 0;
	bool output = 0;
};

// Function Prototypes
void SetLimits();
void drawTruthTable(BinaryVariable inputs[INPUTS_COUNT], string Terms[5], bool Output_of_terms[5][INPUTS_COUNT], int termsCount);
void drawSimplifiedTruthTable(BinaryVariable inputs[INPUTS_COUNT]);
void checkEquivalent(BinaryVariable OutputMainFunction[INPUTS_COUNT], BinaryVariable OutputSimplifiedFunction[INPUTS_COUNT]);
void return_error(string error_message);

//void calculateOutput(BinaryVariable input[INPUTS_COUNT]);

bool AND_GATE(bool input1, bool input2);
bool OR_GATE(bool input1, bool input2);
bool NOT_GATE(bool input);
bool GetBinaryValue(int BinaryIndex, char  Letter, BinaryVariable* OutputMainFunction);



BinaryVariable* OutputMainFunction = new BinaryVariable[INPUTS_COUNT]{
	{0,0,0},
	{0,0,1},
	{0,1,0},
	{0,1,1},
	{1,0,0},
	{1,0,1},
	{1,1,0},
	{1,1,1}
};
BinaryVariable* OutputSimplifiedFunction = new BinaryVariable[INPUTS_COUNT]{
	{0,0,0},
	{0,0,1},
	{0,1,0},
	{0,1,1},
	{1,0,0},
	{1,0,1},
	{1,1,0},
	{1,1,1}
};


int main()
{
	SetLimits();

	int functionType;
	{
		cout << "Please specify if the function is POS or SOP (1 for POS, 2 for SOP): ";
		cin >> functionType;
		cout << endl;
		if (functionType != 1 && functionType != 2)
		{
			return_error("Input must be either 1 or 2");
			return 0;
		}
	}

	int termsCount;
	{
		cout << "Please specify the number of terms (gates): ";
		cin >> termsCount;
		cout << endl;
		if (termsCount > 5)
		{
			return_error("Number of terms must be less than or equal to 5");
			return 0;
		}
	}

	int variablesCount;
	{
		cout << "Please specify the number of variables: ";
		cin >> variablesCount;
		cout << endl;
		if (variablesCount > 3)
		{
			return_error("Number of variables must be less than or equal to 3");
			return 0;
		}
	}

	int literalsCount;
	{
		cout << "Please specify the number of literals: ";
		cin >> literalsCount;
		cout << endl;
		if (literalsCount > 10)
		{
			return_error("Number of literals must be less than or equal to 10");
			return 0;
		}
	}

	string function;
	cout << "Please specify the function: ";
	cin.ignore();
	getline(cin, function);
	cout << endl;



	string Terms[5];
	string term = "";
	int termsIndex = 0;
	int termsCountInFunction = 0;
	
	
	cout << endl << endl << "The function is: " << function << endl << endl;
	cout << "Running the termsIndex function..." << endl;
	for (int i = 0; i < function.length(); i++)
	{
		if (function[i] == '(')
		{
			termsCountInFunction++;
			term = "";
		}
		else if (function[i] == ')')
		{
			Terms[termsIndex] = term;
			termsIndex++;
		}
		else
		{
			term += function[i];
		}
	}

	if (termsIndex != termsCountInFunction)
	{
		return_error("There has been a bracket opened and not closed.");
		return 0;
	}
	if (termsIndex != termsCount)
	{
		return_error("The number of terms is not equal to the number of terms specified.");
		return 0;
	}

	bool Output_of_terms[5][INPUTS_COUNT];
	char literal[2]={0 ,0};
	bool termOutput = 0;
	bool output = 0;

	int literalIndex = 0;
	int coloumnIndex = 0;
	bool Output_of_function[INPUTS_COUNT] = { 0,0,0,0,0,0,0,0 };
	// Evaluate the terms and store the output in the output array
	for (int i = 0; i < termsCountInFunction; i++) // Loop for the terms
	{
		literalIndex = 0;
		coloumnIndex = i;

		for (int h = 0; h < INPUTS_COUNT; h++) // Loop for the inputs
		{

			 // Loop for the literals

			for (int k = 0; k < Terms[i].length(); k++)
			{	
				if (literalIndex == 2) {
					break;
				}

				term = Terms[i];
					
				if (term[k] == ' ') {
					k++;
						
				}

				if (term[k] == 'A') {
					if (term[k + 1] == 'N') {
						k+= 3;

					}
				}
					
				if (term[k] == 'O'){
					if (term[k + 1] == 'R') {
						k += 2;
					}
				}
					
				if (term[k] == 'A')
				{
					literal[literalIndex] = 'A';//OutputMainFunction[h].A;
					literalIndex++;
				}
				else if (term[k] == 'B')
				{
					literal[literalIndex] = 'B'; //OutputMainFunction[h].B;
					literalIndex++;
				}
				else if (term[k] == 'C')
				{
					literal[literalIndex] = 'C'; //OutputMainFunction[h].C;
					literalIndex++;
				}
				else if (term[k] == '~')
				{
					if (term[k + 1] == 'A')
					{
						literal[literalIndex] = 'D'; //!OutputMainFunction[h].A;
						k++;
						literalIndex++;
					}
					else if (term[k + 1] == 'B')
					{
						literal[literalIndex] = 'E'; // !OutputMainFunction[h].B;
						k++;
						literalIndex++;
					}
					else if (term[k + 1] == 'C')
					{
						literal[literalIndex] = 'F'; // !OutputMainFunction[h].C;
						k++;
						literalIndex++;
					}
					else
					{
						cout << "Running the Error Function 5" << endl;
						return_error("Invalid function");
						return 0;
					}
				}
				else if (term[k] == '(' || term[k] == ')' || term[k] == ' ')
				{
					continue;
				}
			}
				
			if (functionType == 1) {
				Output_of_terms[coloumnIndex][h] = OR_GATE((GetBinaryValue(h, literal[0], OutputMainFunction)), (GetBinaryValue(h, literal[1], OutputMainFunction)));
			}
			else if (functionType == 2) {
				Output_of_terms[coloumnIndex][h] = AND_GATE((GetBinaryValue(h, literal[0], OutputMainFunction)), (GetBinaryValue(h, literal[1], OutputMainFunction)));
			};	

		};
	};

	for (int i = 0; i < INPUTS_COUNT; i++)
	{
		if (functionType == 1) {
			OutputMainFunction[i].output = AND_GATE(Output_of_terms[0][i], Output_of_terms[1][i]);
			OutputMainFunction[i].output = AND_GATE(OutputMainFunction[i].output, Output_of_terms[2][i]);
			OutputMainFunction[i].output = AND_GATE(OutputMainFunction[i].output, Output_of_terms[3][i]);
			OutputMainFunction[i].output = AND_GATE(OutputMainFunction[i].output, Output_of_terms[4][i]);
		}
		else if (functionType == 2) {
			OutputMainFunction[i].output = OR_GATE(Output_of_terms[0][i], Output_of_terms[1][i]);
			OutputMainFunction[i].output = OR_GATE(OutputMainFunction[i].output, Output_of_terms[2][i]);
			OutputMainFunction[i].output = OR_GATE(OutputMainFunction[i].output, Output_of_terms[3][i]);
			OutputMainFunction[i].output = OR_GATE(OutputMainFunction[i].output, Output_of_terms[4][i]);
		}
	}

	drawTruthTable(OutputMainFunction, Terms, Output_of_terms, termsCount);
	// Simplified Truth Table


	

	/*drawSimplifiedTruthTable(OutputSimplifiedFunction);
	checkEquivalent(OutputMainFunction, OutputSimplifiedFunction);*/
	return 0;
}
void SetLimits() {
	{
		cout << "Welcome to the Logic Gates Simulator" << endl;
		cout << "This program will simulate a logic gate circuit and output the truth table for the circuit and a simplified version of the circuit." << endl;
		cout << "The circuit will have 3 inputs, A, B, and C. AND, OR, and NOT gates will be used to create the circuit." << endl;
		cout << "Althought the user can input the function, there exists certain limitations." << endl << endl;
		cout << "1. The function must be Either product of sum (POS) or sum of product (SOP)." << endl;
		cout << "2. The maximum number of terms (gates) is 5." << endl;
		cout << "3. The maximum number of variables is 3." << endl;
		cout << "4. The maximum number of literals is 10." << endl;
		cout << "5. Each term should contain by maximum 2 literals." << endl;
		cout << "6 . The function must be in the following format: " << endl;
		cout << "   - The variables must be A, B, and C." << endl;
		cout << "   - The literals must be ~A, ~B, ~C, A, B, and C." << endl;
		cout << "   - The operators must be AND, OR, and NOT." << endl;
		cout << "   - The operators must be in the following format: " << endl;
		cout << "     - AND: A AND B" << endl;
		cout << "     - OR: A OR B" << endl;
		cout << "     - NOT: ~A" << endl;
		cout << "6. Each term should be in brackets. and separated by 'OR' if SOP and by  'AND' if POS." << endl;
		cout << "   - Example: (A AND B) OR (C AND ~A) OR (B AND ~C) OR (A AND ~B) OR (C AND ~B)" << endl << endl;
	}
};


bool GetBinaryValue(int BinaryIndex, char  Letter, BinaryVariable* OutputMainFunction) {
	if (Letter == 'A') {
		return OutputMainFunction[BinaryIndex].A;
	}
	else if (Letter == 'B') {
		return OutputMainFunction[BinaryIndex].B;
	}
	else if (Letter == 'C') {
		return OutputMainFunction[BinaryIndex].C;
	}
	else if (Letter == 'D') {
		return !OutputMainFunction[BinaryIndex].A;
	}
	else if (Letter == 'E') {
		return !OutputMainFunction[BinaryIndex].B;
	}
	else if (Letter == 'F') {
		return !OutputMainFunction[BinaryIndex].C;
	}
	else {
		cout << "Running the Error Function 6" << endl;
		return_error("Invalid function");
		return 0;
	}
}


//void calculateOutput(BinaryVariable input[INPUTS_COUNT])  
//{
//	for (int i = 0; i < INPUTS_COUNT; i++)
//	{
//		input[i].output = (!input[i].C || input[i].A) && (!input[i].C || input[i].B) && (input[i].C || input[i].A) && (input[i].C || input[i].B);
//	}
//}

// Function to draw the truth table of the circuit
void drawTruthTable(BinaryVariable inputs[INPUTS_COUNT], string Terms[5], bool Output_of_terms[5][INPUTS_COUNT], int termsCount)
{
	// calculateOutput(OutputMainFunction);
	string Head = "";
	string TotalBars = "";
	for (int j = 0; j < termsCount; j++)
	{
		Head += Terms[j] + "\t|\t";
	}
	for (int j = 0; j < termsCount; j++)
	{
		TotalBars += "________________";
	}
	cout << "_________________________________________________________________" + TotalBars  << endl;
	
	// Print the header of the truth table

	cout << "|\tA\t|\tB\t|\tC\t|\t"+ Head + "Output\t|" << endl;
	
	cout << "_________________________________________________________________" + TotalBars << endl;

	// Loop to print the truth table
	for (int i = 0; i < INPUTS_COUNT; i++)
	{
		cout << "|\t"
			<< inputs[i].A << "\t|\t"
			<< inputs[i].B << "\t|\t"
			<< inputs[i].C << "\t|\t";
		for (int j = 0; j < termsCount; j++)
		{
			cout << Output_of_terms[j][i] << "\t|\t";
		}
		/*
			<< Output_of_terms[0][i] << "\t|\t"
			<< Output_of_terms[1][i] << "\t|\t" 
			<< Output_of_terms[2][i] << "\t|\t" 
			<< Output_of_terms[3][i] << "\t|\t" 
			<< Output_of_terms[4][i] << "\t|\t"*/ 
			cout << inputs[i].output << "\t|" << endl;
	}


	/*for (int i = 0; i < INPUTS_COUNT; i++)  
	{
		cout << "|\t" 
			<< inputs[i].A << "\t|\t" 
			<< inputs[i].B << "\t|\t" 
			<< inputs[i].C << "\t|\t" 
			<< !inputs[i].C << "\t|\t" 
			<< (!inputs[i].C || inputs[i].A) << "\t|\t" 
			<< (!inputs[i].C || inputs[i].B) << "\t|\t" 
			<< (inputs[i].C || inputs[i].A) << "\t|\t" 
			<< (inputs[i].C || inputs[i].B) << "\t|\t" 
			<< inputs[i].output << "\t|" << endl;
	}*/
	
	cout << "_________________________________________________________________" + TotalBars << endl;

}

// Calcule the simplified function of the circuit
void calculateSimplifiedOutput(BinaryVariable input[INPUTS_COUNT])
{
	for (int i = 0; i < INPUTS_COUNT; i++)
	{
		input[i].output = (input[i].A && input[i].B);
	}
}

// Function to draw the simplified truth table of the circuit
void drawSimplifiedTruthTable(BinaryVariable inputs[INPUTS_COUNT])
{
	calculateSimplifiedOutput(OutputSimplifiedFunction);
	
	cout << "_________________________________________________________________" << endl;
	
	// Print the header of the truth table
	cout << "|\tA\t|\tB\t|\tA AND B\t|\tOutput\t|" << endl; 
	
	cout << "_________________________________________________________________" << endl;

	// Loop to print the truth table
	for (int i = 0; i < INPUTS_COUNT; i++)
	{
		cout << "|\t" 
			<< inputs[i].A << "\t|\t" 
			<< inputs[i].B << "\t|\t" 
			<< (inputs[i].A && inputs[i].B) << "\t|\t" 
			<< inputs[i].output << "\t|" << endl;
	}
	
	cout << "_________________________________________________________________" << endl;
}

// Check whether the 2 expressions are equivalent or not.
void checkEquivalent(BinaryVariable OutputMainFunction[INPUTS_COUNT], BinaryVariable OutputSimplifiedFunction[INPUTS_COUNT])
{
	cout << endl;
	cout << "Checking if the 2 expressions are equivalent or not..." << endl;
	
	for (int i = 0; i < INPUTS_COUNT; i++)
	{
		if (OutputMainFunction[i].output != OutputSimplifiedFunction[i].output)
		{
			cout << "Both Functions Are not Equivalent.";
			break;
		}
	}
	cout << "Functions Are Equivalent";
	cout << endl;
}

// Error message function
void return_error(string error_message = "Unhandled function")
{
	cout << "Invalid Input. Exiting Program..." << endl;
	cout << "Error: " + error_message << endl;
}

// AND Gate Function
bool AND_GATE(bool input1, bool input2)
{
	return input1 && input2;
}

// OR Gate Function
bool OR_GATE(bool input1, bool input2)
{
	return (input1 || input2);
}

// NOT Gate Function
bool NOT_GATE(bool input)
{
	return !input;
}
