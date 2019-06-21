#include <iostream>
#include <string>
#include <vector>
#include <random>

int min_states = 2;
int max_states = 4;

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

auto main() -> int
{
	return 0;
}
