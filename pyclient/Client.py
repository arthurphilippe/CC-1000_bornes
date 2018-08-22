import Game
import sys


def findCard(ga, card):
    pos = 0
    while pos < 6:
        if ga.hand[pos] is card:
            return pos
        pos += 1
    return -1


def findBestDist(ga):
    bestIdx = -1
    bestCard = Game.Card.NONE
    pos = 0
    while pos < 6 and bestCard is not Game.Card.Dst200kms:
        if ga.hand[pos].value >= Game.Card.Dst25kms.value and ga.hand[pos].value <= Game.Card.Dst200kms.value:
            if bestCard.value is Game.Card.NONE.value or bestCard.value < ga.hand[pos].value:
                bestCard = ga.hand[pos]
                bestIdx = pos
        pos += 1
    return bestIdx


def runStrat(ga):
    toPlay = -1

    if ga.state.incident is Game.Card.HazCarCrash:
        toPlay = findCard(ga, Game.Card.DefRepair)
    elif ga.state.incident is Game.Card.HazGasOutage:
        toPlay = findCard(ga, Game.Card.DefGas)
    else:
        toPlay = findBestDist(ga)

    if toPlay is -1:
        ga.discardCard(toPlay)
    else:
        ga.useCard(toPlay)


if __name__ == '__main__':
    print('launching client')

    ga = Game.Game(sys.argv[1], sys.argv[2])
    while ga.live is True and ga.read() is True:
        runStrat(ga)
