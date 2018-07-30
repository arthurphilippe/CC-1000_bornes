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
    uid = 0
    dist = 0
    incident = Card.NONE
    limited = False
    ace = False
    tank = False
    punctureProof = False
    prioritised = False


class Game:
    def __init__(self, host="", port=""):
        self.id = 0
        self.hand = [Card.NONE]
        self.hand *= 6
        self.players = [PlayerState()]
        self.players *= 6
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
