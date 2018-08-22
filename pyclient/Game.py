import tcp
from enum import Enum


class Card(Enum):
    HazCarCrash = 0
    HazGasOutage = 1
    HazFlatTire = 2  # Disabled for the back to code session
    HazSpeedLimit = 3  # Disabled for the back to code session
    HazRedLight = 4  # Disabled for the back to code session

    DefRepair = 5
    DefGas = 6
    DefSpareWheel = 7  # Disabled for the back to code session
    DefEndOfLimit = 8  # Disabled for the back to code session
    DefGreenLight = 9  # Disabled for the back to code session

    SpeAcePilot = 10
    SpeTankLorry = 11
    SpePunctureProof = 12  # Disabled for the back to code session
    SpePrioritised = 13  # Disabled for the back to code session

    Dst25kms = 14
    Dst50kms = 15
    Dst75kms = 16
    Dst100kms = 17
    Dst200kms = 18

    COUNT = 19
    NONE = 20


def strtobool(string):
    if string == '1':
        return True
    return False


class PlayerState:
    def __init__(self):
        self.uid = 0
        self.dist = 0
        self.incident = Card.NONE
        self.limited = False
        self.ace = False
        self.tank = False
        self.punctureProof = False
        self.prioritised = False


class Game:
    def __init__(self, host="", port=""):
        self.hand = [Card.NONE]
        self.hand *= 6
        self.players = []
        self.state = PlayerState()
        self.msgQueue = []
        self.connected = False
        self.live = True
        self.carry = True
        self.winnerUid = 0
        if len(host) and len(port):
            self.connect(host, port)

        self.__processors = {"id": lambda args: self.procID(args),
                             'playerstate': lambda args:
                             self.procPlayerState(args),
                             'lscards': lambda args: self.procLsCards(args),
                             'ok': lambda args: self.procOK(args),
                             'ko': lambda args: self.procKO(args),
                             'forfeit': lambda args: self.procWinner(args),
                             'winner': lambda args: self.procWinner(args)
                             }

    def connect(self, host, port):
        self.__sock = tcp.create()
        tcp.connect(self.__sock, host, int(port))
        self.connected = True

    def read(self):
        status = 0
        while status is 0:
            if self.connected:
                self.msgQueue = tcp.fillQueue(self.__sock, self.msgQueue)
            while len(self.msgQueue) is not 0:
                msg = self.msgQueue.pop(0)
                print('processing: ', msg)
                if msg[:4] == 'info':
                    print('info from server', msg)
                elif msg == 'your_turn':
                    print('Your turn!')
                    status = 1
                elif msg == 'quit':
                    print('exiting')
                    status = -1
                else:
                    self.proc(msg)

        if status is 1:
            return True
        else:
            return False

    def procID(self, args):
        self.state.uid = int(args[0])

    def procKO(self, args):
        self.carry = False
        print(' !-> Your last action failed')

    def procOK(self, args):
        self.carry = True

    def procLsCards(self, args):
        if len(args) is 6:
            index = 0
            for card in args:
                try:
                    if card.isdigit():
                        self.hand[index] = Card(int(card))
                    else:
                        self.hand[index] = Card.NONE
                except:
                    self.hand[index] = Card.NONE
                index += 1

    def __procPlayerStateExtract(self, args):
        state = PlayerState()
        state.uid = int(args[0])
        state.dist = int(args[1])
        state.incident = Card(int(args[2]))
        state.limited = strtobool(args[3])
        state.ace = strtobool(args[4])
        state.tank = strtobool(args[5])
        state.punctureProof = strtobool(args[6])
        state.prioritised = strtobool(args[7])
        return state

    def procPlayerState(self, args):
        if len(args) is 8:
            state = self.__procPlayerStateExtract(args)
            if state.uid is self.state.uid:
                self.state = state
            else:
                if len(self.players) < 5:
                    self.players.append(state)

    def procWinner(self, args):
        if len(args) is 0:
            print(' --> Everyone but you has declared forfeit.')
        else:
            self.winnerUid = int(args[0])
        self.live = False

    def useCard(self, cardPos):
        if self.live is True and self.connected is True:
            string = 'use {}\n'.format(cardPos)
            print(':: sending: \'{}\''.format(string))
            self.__sock.sendall(str.encode(string))
            return string

    def discardCard(self, cardPos):
        if self.live is True and self.connected is True:
            string = 'discard {}\n'.format(cardPos)
            print(':: sending: \'{}\''.format(string))
            self.__sock.sendall(str.encode(string))
            return string

    def useAttack(self, cardPos, idTarget):
        if self.live is True and self.connected is True:
            string = 'use {} {}\n'.format(cardPos, idTarget)
            print(':: sending: \'{}\''.format(string))
            self.__sock.sendall(str.encode(string))
            return string

    def proc(self, msg):
        try:
            args = msg.split(' ')
            self.__processors[args[0]](args[1:])
        except Exception as error:
            print(error)
