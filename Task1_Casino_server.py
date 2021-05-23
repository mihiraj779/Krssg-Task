import socket          
import threading
import time
import random

HEADER = 80           
PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())   
ADDR = (SERVER, PORT) 
FORMAT = 'utf-8'
DISCONNECT_MESSAGE = "End Server"
PLAYERS = 3 

conn = [0,0,0]

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

server.bind(ADDR) 

dis_cards = [0,0,0,0,0,0,0,0,0]
recvCardsbyplayer = [0,0,0]
round_winner = [0,0,0]

def handle_clients(clientID, addr):

    while threading.active_count() -1 < PLAYERS:
        time.sleep(25)

    time.sleep(1)
    round=0
    while True:

        time.sleep(0.1)
        dist_ran_cards(clientID)
                            
        time.sleep(5)

        max_cards_byclient(clientID,addr,round)

        if(clientID == conn[0]):
            upd_declare(round)
            time.sleep(5)
        else:
            time.sleep(20)  

        round+=1
        if(round == 4):
            break
    
    maxPoints=0
    
    winningMessage = "The winner(s) of the 4 rounds is(are) player(s)---"
    for m in range(PLAYERS):
        if(round_winner[m] > maxPoints):
            maxPoints = round_winner[m]
    for n in range(PLAYERS):
        if(maxPoints == round_winner[n]):
            winningMessage = winningMessage + (' ' + str(n+1))
    if(clientID == conn[0]):
        print(winningMessage)
    clientID.send(winningMessage.encode(FORMAT))

    time.sleep(20)

    endingMessage = "Do you wish to continue? [y/n]"

    clientID.send(endingMessage.encode(FORMAT))
    msg_length = clientID.recv(HEADER).decode(FORMAT)
    if msg_length: 
        msg_length = int(msg_length) 
        msg = clientID.recv(msg_length).decode(FORMAT)
        if msg == DISCONNECT_MESSAGE:
            clientID.close()
        else:
            time.sleep(30)
            handle_clients(clientID, addr)
def upd_declare(round):
    time.sleep(15)
    Winnermost = 0
    max_among_all_player = 0
    for i in range(PLAYERS):
        if(max_among_all_player == recvCardsbyplayer[i]):
            Winnermost += 1
        if(max_among_all_player < recvCardsbyplayer[i]):
            max_among_all_player = recvCardsbyplayer[i]
            Winnermost = 0
    if(Winnermost == 0):
        for i in range(PLAYERS):
            if(recvCardsbyplayer[i] == max_among_all_player):
                round_winner[i] += 1
                print("Winner of round-", round+1," is player-", i+1)
                print("\n")
    elif(Winnermost > 0):
        print("This round was a tie between the players--", end=' ')
        for i in range(PLAYERS):
            if(recvCardsbyplayer[i] == max_among_all_player):
                print(i+1, end = ' ')
                print("\n")
    rand_cards()

def dist_ran_cards(clientID):
    for i in range(PLAYERS):
        if clientID == conn[i]:
            clientID.send("Pick the largest among:".encode(FORMAT))
            time.sleep(1)
            yourCards = [0,0,0]
            for j in range(3):
                yourCards[j] = (dis_cards[3*i + j])
            b=str(yourCards)
            clientID.send(b.encode(FORMAT))

def max_cards_byclient(clientID, addr,round):
    for i in range(PLAYERS):
        if clientID == conn[i]:
            msg_length = clientID.recv(HEADER).decode(FORMAT)
            if msg_length: 
                    msg_length = int(msg_length) 
                    msg = clientID.recv(msg_length).decode(FORMAT) 
                    print(f"[{addr}] {msg}")
                    recvCardsbyplayer[i] = int(msg)
                    if(round < 3):
                       clientID.send("Msg received, next round starts soon...".encode(FORMAT))
                    else:
                        clientID.send("Game is over, results will be declared soon...".encode(FORMAT))




#this function generates random numbers within the range and converts them to card numbers
def rand_cards():
    random.seed()
    i=0
    f=0
    while i<9:
        while True:
            dis_cards[i] = random.randint(1,52)
            j=i-1
            while j>=0:
                if(dis_cards[i]==dis_cards[j]):
                    f=1
                    break
                else:
                    f=0
                j-=1    
                    
            if(f==0):
                 break
                  
        i+=1                
        
    for k in range(9):
        if((dis_cards[k]%13) == 0):
            dis_cards[k] = 13
        else:
            dis_cards[k] %= 13
def start():

    server.listen() 
    print(f"Server is listening on the IP Address: {SERVER}")
    
    while True: 
        i = threading.active_count() - 1
        while i < PLAYERS:
            conn[i], addr = server.accept()
            thread = threading.Thread(target = handle_clients, args=(conn[i],addr)) 
            thread.start()
            first_mess_server = "Starting the game...[Please wait until other players to join]"
            conn[i].send(first_mess_server.encode(FORMAT))
            time.sleep(0.5)
            no_player = "You are player "
            no_player = no_player + str((i+1))
            conn[i].send(no_player.encode(FORMAT))
            print(f"[NEW CONNECTION] {addr} connected.")
            i = threading.active_count() - 1
    
print("=============Server is starting=================")
rand_cards()
start()