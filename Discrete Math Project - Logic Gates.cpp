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
	(~C OR A) AND (~C OR B) AND (C OR A) AND (C OR B)
	(A OR A) AND (B OR B);
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

// Variables
string Bothfunction;


int PrimaryFunctionType = 0;
int SimplifiedFunctionType = 0;

string PrimaryTerms[5], SimplifiedTerms[5];
string term = "";

int PrimaryTermIndex = 0, PrimarytermsCountInFunction = 0;

int SimplifiedTermIndex = 0, SimplifiedtermsCountInFunction = 0;



// Function Prototypes
void SetLimits();
void parameters();
void drawTruthTable(BinaryVariable inputs[INPUTS_COUNT], string Terms[5], bool Output_of_terms[5][INPUTS_COUNT], int termsCount);
void checkEquivalent(BinaryVariable OutputMainFunction[INPUTS_COUNT], BinaryVariable OutputSimplifiedFunction[INPUTS_COUNT]);
void return_error(string error_message);

//void calculateOutput(BinaryVariable input[INPUTS_COUNT]);

bool AND_GATE(bool input1, bool input2);
bool OR_GATE(bool input1, bool input2);
bool NOT_GATE(bool input);
bool GetBinaryValue(int BinaryIndex, char  Letter, BinaryVariable* OutputMainFunction);



BinaryVariable* PrimaryFunction = new BinaryVariable[INPUTS_COUNT]{
	{0,0,0},
	{0,0,1},
	{0,1,0},
	{0,1,1},
	{1,0,0},
	{1,0,1},
	{1,1,0},
	{1,1,1}
};
BinaryVariable* SimplifiedFunction = new BinaryVariable[INPUTS_COUNT]{
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
	parameters();

	cout << "Please enter your function, then in a new line enter the simplified function. After entering the simplified function, end your lines with ';'" << endl;
	cin.ignore();
	getline(cin, Bothfunction, ';');
	cout << endl;

	string function = Bothfunction.substr(0, Bothfunction.find("\n"));
	string Simplified = Bothfunction.substr(Bothfunction.find("\n") + 1, Bothfunction.length() - 1);
	
	cout << "The function is: " << function << endl << endl;
	cout << "The simplified function is: " << Simplified << endl << endl;

	
	
	for (int i = 0; i < function.length(); i++)
	{
		if (function[i] == '(')
		{
			PrimarytermsCountInFunction++;
			term = "";
		}
		else if (function[i] == ')')
		{
			PrimaryTerms[PrimaryTermIndex] = term;
			PrimaryTermIndex++;
		}
		else
		{
			term += function[i];
		}
	}

	for (int i = 0; i < Simplified.length(); i++)
	{
		if (Simplified[i] == '(')
		{
			SimplifiedtermsCountInFunction++;
			term = "";
		}
		else if (Simplified[i] == ')')
		{
			SimplifiedTerms[SimplifiedTermIndex] = term;
			SimplifiedTermIndex++;
		}
		else
		{
			term += Simplified[i];
		}
	}

	if (PrimaryTermIndex != PrimarytermsCountInFunction)
	{
		return_error("There has been a bracket opened and not closed.");
		return 0;
	}
	if (PrimaryTermIndex > 5)
	{
		return_error("You have exceded the maximum number of terms (max. number: 5)");
		return 0;
	}

	bool PrimaryTermsOutput[5][INPUTS_COUNT];
	bool SimplifiedTermsOutput[5][INPUTS_COUNT];
	char literal[2]={0 ,0};
	bool termOutput = 0;
	bool output = 0;

	int literalIndex = 0;
	int coloumnIndex = 0;
	bool Output_of_function[INPUTS_COUNT] = { 0,0,0,0,0,0,0,0 };

	for (int i = 0; i < PrimarytermsCountInFunction; i++) // Loop for the terms
	{
		literalIndex = 0;
		coloumnIndex = i;

		for (int h = 0; h < INPUTS_COUNT; h++) // Loop for the inputs
		{

			 // Loop for the literals

			for (int k = 0; k < PrimaryTerms[i].length(); k++)
			{	
				if (literalIndex == 2) {
					break;
				}

				term = PrimaryTerms[i];
					
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
				
			if (PrimaryFunctionType == 1) {
				PrimaryTermsOutput[coloumnIndex][h] = OR_GATE((GetBinaryValue(h, literal[0], PrimaryFunction)), (GetBinaryValue(h, literal[1], PrimaryFunction)));
			}
			else if (PrimaryFunctionType == 2) {
				PrimaryTermsOutput[coloumnIndex][h] = AND_GATE((GetBinaryValue(h, literal[0], PrimaryFunction)), (GetBinaryValue(h, literal[1], PrimaryFunction)));
			};	

		};
	};

	for (int i = 0; i < SimplifiedtermsCountInFunction; i++) // Loop for the terms
	{
		literalIndex = 0;
		coloumnIndex = i;

		for (int h = 0; h < INPUTS_COUNT; h++) // Loop for the inputs
		{

			// Loop for the literals

			for (int k = 0; k < SimplifiedTerms[i].length(); k++)
			{
				if (literalIndex == 2) {
					break;
				}

				term = SimplifiedTerms[i];

				if (term[k] == ' ') {
					k++;

				}

				if (term[k] == 'A') {
					if (term[k + 1] == 'N') {
						k += 3;

					}
				}

				if (term[k] == 'O') {
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

			if (SimplifiedFunctionType == 1) {
				SimplifiedTermsOutput[coloumnIndex][h] = OR_GATE((GetBinaryValue(h, literal[0], SimplifiedFunction)), (GetBinaryValue(h, literal[1], SimplifiedFunction)));
			}
			else if (SimplifiedFunctionType == 2) {
				SimplifiedTermsOutput[coloumnIndex][h] = AND_GATE((GetBinaryValue(h, literal[0], SimplifiedFunction)), (GetBinaryValue(h, literal[1], SimplifiedFunction)));
			};

		};
	};


	for (int i = 0; i < INPUTS_COUNT; i++)
	{
		if (PrimaryFunctionType == 1) {
			PrimaryFunction[i].output = AND_GATE(PrimaryTermsOutput[0][i], PrimaryTermsOutput[1][i]);
			PrimaryFunction[i].output = AND_GATE(PrimaryFunction[i].output, PrimaryTermsOutput[2][i]);
			PrimaryFunction[i].output = AND_GATE(PrimaryFunction[i].output, PrimaryTermsOutput[3][i]);
			PrimaryFunction[i].output = AND_GATE(PrimaryFunction[i].output, PrimaryTermsOutput[4][i]);
		}
		else if (PrimaryFunctionType == 2) {
			PrimaryFunction[i].output = OR_GATE(PrimaryTermsOutput[0][i], PrimaryTermsOutput[1][i]);
			PrimaryFunction[i].output = OR_GATE(PrimaryFunction[i].output, PrimaryTermsOutput[2][i]);
			PrimaryFunction[i].output = OR_GATE(PrimaryFunction[i].output, PrimaryTermsOutput[3][i]);
			PrimaryFunction[i].output = OR_GATE(PrimaryFunction[i].output, PrimaryTermsOutput[4][i]);
		}
	}

	for (int i = 0; i < INPUTS_COUNT; i++)
	{
		if (PrimaryFunctionType == 1) {
			SimplifiedFunction[i].output = AND_GATE(SimplifiedTermsOutput[0][i], SimplifiedTermsOutput[1][i]);
			SimplifiedFunction[i].output = AND_GATE(SimplifiedFunction[i].output, SimplifiedTermsOutput[2][i]);
			SimplifiedFunction[i].output = AND_GATE(SimplifiedFunction[i].output, SimplifiedTermsOutput[3][i]);
			SimplifiedFunction[i].output = AND_GATE(SimplifiedFunction[i].output, SimplifiedTermsOutput[4][i]);
		}
		else if (PrimaryFunctionType == 2) {
			SimplifiedFunction[i].output = OR_GATE(SimplifiedTermsOutput[0][i], SimplifiedTermsOutput[1][i]);
			SimplifiedFunction[i].output = OR_GATE(SimplifiedFunction[i].output, SimplifiedTermsOutput[2][i]);
			SimplifiedFunction[i].output = OR_GATE(SimplifiedFunction[i].output, SimplifiedTermsOutput[3][i]);
			SimplifiedFunction[i].output = OR_GATE(SimplifiedFunction[i].output, SimplifiedTermsOutput[4][i]);
		}
	}


	drawTruthTable(PrimaryFunction, PrimaryTerms, PrimaryTermsOutput, PrimaryTermIndex);
	drawTruthTable(SimplifiedFunction, SimplifiedTerms, SimplifiedTermsOutput, SimplifiedTermIndex);

	checkEquivalent(PrimaryFunction, SimplifiedFunction);

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

void parameters() {
	{
		cout << "Please specify if the function is POS or SOP (1 for POS, 2 for SOP): ";
		cin >> PrimaryFunctionType;
		cout << endl;
		if (PrimaryFunctionType != 1 && PrimaryFunctionType != 2)
		{
			return_error("Input must be either 1 or 2");
		}
	}
	{
		cout << "Please specify if the simplified function is POS or SOP (1 for POS, 2 for SOP): ";
		cin >> SimplifiedFunctionType;
		cout << endl;
		if (SimplifiedFunctionType != 1 && SimplifiedFunctionType != 2)
		{
			return_error("Input must be either 1 or 2");
		}
	}
}

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
			cout << inputs[i].output << "\t|" << endl;
	}
	
	cout << "_________________________________________________________________" + TotalBars << endl;

}

void checkEquivalent(BinaryVariable OutputMainFunction[INPUTS_COUNT], BinaryVariable OutputSimplifiedFunction[INPUTS_COUNT])
{
	cout << endl;
	cout << "Checking if the 2 expressions are equivalent or not..." << endl;
	
	bool flag = 1;

	for (int i = 0; i < INPUTS_COUNT; i++)
	{
		if (OutputMainFunction[i].output != OutputSimplifiedFunction[i].output)
		{
			cout << "Both Functions Are not Equivalent.";
			flag = 0;
			break;
		}
	}
	if(flag)
	cout << "Functions Are Equivalent";
	cout << endl;
}

void return_error(string error_message = "Unhandled function")
{
	cout << "Invalid Input. Exiting Program..." << endl;
	cout << "Error: " + error_message << endl;
}

bool AND_GATE(bool input1, bool input2)
{
	return input1 && input2;
}

bool OR_GATE(bool input1, bool input2)
{
	return (input1 || input2);
}

bool NOT_GATE(bool input)
{
	return !input;
}
