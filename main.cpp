#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>

int min_states = 3;
int max_states = 3;
int guess_length = 4;

struct FSM
{
	int num_input;
	int num_output;

	struct State
	{
		std::vector<int> nexts;
		int output;
	};

	std::vector<State> states;
	int start;
};

auto generate_fsm() -> FSM*
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis_states(min_states, max_states);

	int num_states = dis_states(gen);

	std::uniform_int_distribution<> dis_inputs(2, num_states);
	std::uniform_int_distribution<> dis_outputs(2, num_states);

	std::uniform_int_distribution<> dis_state(0, num_states-1);

	int num_inputs = dis_inputs(gen);
	int num_outputs = dis_outputs(gen);

	std::uniform_int_distribution<> dis_input(0, num_inputs-1);
	std::uniform_int_distribution<> dis_output(0, num_outputs-1);

	FSM* fsm = new FSM;
	fsm->states.resize(num_states);

	for(auto& state : fsm->states) {
		state.nexts.resize(num_inputs);
		for(int& next : state.nexts) {
			next = dis_state(gen);
		}
		state.output = dis_output(gen);
	}

	fsm->num_input = num_inputs;
	fsm->num_output = num_outputs;
	fsm->start = dis_state(gen);

	
	return fsm;
}

auto question_fsm(FSM* fsm) -> void
{
	int cur_state = fsm->start;
	std::string s;
	while(true) {
		std::cout << fsm->states[cur_state].output << std::endl;
		std::cout << "> ";
		std::cin >> s;

		if(s == "s") {
			cur_state = fsm->start;
			continue;
		} else if(s == "q") {
			break;
		}

		int input = std::atoi(s.c_str());

		if(input < 0 || input >= fsm->num_input) {
			std::cout << "Invalid input." << std::endl;
			continue;
		}

		cur_state = fsm->states[cur_state].nexts[input];
	}
}

auto guess_fsm(FSM* fsm) -> void
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis_input(0, fsm->num_input-1);

	int cur_state = fsm->start;
	for(int i=0; i<guess_length; ++i) {
		int input = dis_input(gen);
		std::cout << input;
		cur_state = fsm->states[cur_state].nexts[input];
	}

	std::cout << std::endl;
	std::cout << "What is current output: ";

	int output = 0;
	std::cin >> output;

	if(output == fsm->states[cur_state].output) {
		std::cout << "Success!" << std::endl;
	} else {
		std::cout << "Unfortunatly it's not right answer, the correct answer was " << output << "." << std::endl;
	}
}

auto main() -> int
{
	FSM* fsm = generate_fsm();
	std::cout << "FSM generated!" << std::endl;
	std::cout << "There are " << fsm->num_input << " inputs" << std::endl;

	std::cout << "Type a number to enter an input" << std::endl;
	std::cout << "Type 's' to go back to initial state" << std::endl;
	std::cout << "Type 'q' to quit exploring and go to guessing game" << std::endl;

	question_fsm(fsm);
	guess_fsm(fsm);

	system("PAUSE");

	delete fsm;
	return 0;
}
