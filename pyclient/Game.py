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
        self.connected = False
        self.live = True
        self.carry = True
        if len(host) and len(port):
            self.connect()

    def connect(host, port):
        self.__sock = tcp.create()
        tcp.connect(self.__sock, host, int(port))
        self.connected = True

    def read(self):
        if self.connected:
            pass

    def procID(self, args):
        self.id = int(args[0])

    def procKO(self, args):
        self.carry = False
        print(' !-> Your last action failed')

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
        state.limited = bool(args[3])
        state.ace = bool(args[4])
        state.tank = bool(args[5])
        state.punctureProof = bool(args[6])
        state.prioritised = bool(args[7])
        return state

    def procPlayerState(self, args):
        if len(args) is 8:
            state = self.__procPlayerStateExtract(args)
            if state.uid is self.state.uid:
                self.state = state
            else:
                if len(self.players) < 5:
                    self.players.append(state)
