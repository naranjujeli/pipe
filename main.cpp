#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int pipe_arr[2];
	int result = pipe(pipe_arr);
	if (result == -1) {
		std::cout << "(Parent) Creating the pipe was not posible, che" << std::endl;
	} else {
		int pid = fork();
		if (pid == 0) {
			int user_input;
			std::cout << "(Child) Enter a number: "; std::cin >> user_input;
			write(pipe_arr[1], &user_input, sizeof(int));
			close(pipe_arr[1]);
			exit(0);
		} else {
			wait(NULL);
			int *child_response;
			read(pipe_arr[0], child_response, sizeof(int));
			std::cout << "(Parent) The number received by the child process was: " << *child_response << std::endl;
		}
	}

	return 0;
}
