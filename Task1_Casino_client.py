import socket
import time

HEADER = 80
PORT = 5050
FORMAT = 'utf-8'
DISCONNECT_MESSAGE = "BYE!"
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDR) 

def client_fxn(): 
    print(client.recv(1024).decode(FORMAT)) 
    print(client.recv(1024).decode(FORMAT)) 

    time.sleep(0.1)
    round = 0
    while True:
        print(client.recv(1024).decode(FORMAT))
        time.sleep(1)
        print(client.recv(1024).decode(FORMAT))
        time.sleep(1)
        MaxCard = input()
        print("You entered:", MaxCard,", please wait for every player to select...")
        message = MaxCard.encode(FORMAT) 
        msg_length = len(message) 
        send_length = str(msg_length).encode(FORMAT) 
        send_length += b' ' * (HEADER - len(send_length)) 
        client.send(send_length)
        client.send(message) 
            
        print(client.recv(1024).decode(FORMAT))
        time.sleep(20)
        round+=1
        if(round == 4):
            break
    
    print(client.recv(1024).decode(FORMAT))
    time.sleep(20)
    print(client.recv(1024).decode(FORMAT))
    endingMessage = input()
    message = endingMessage.encode(FORMAT) 
    msg_length = len(message) 
    send_length = str(msg_length).encode(FORMAT) 
    send_length += b' ' * (HEADER - len(send_length)) 
    client.send(send_length)
    client.send(message)
    if(endingMessage == "y"):
        client_fxn()

client_fxn()