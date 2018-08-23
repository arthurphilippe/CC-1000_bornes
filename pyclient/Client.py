import Game
import sys


def runStrat(ga):
    pass


if __name__ == '__main__':
    if len(sys.argv) is not 3:
        print('error: too few or too much arguments')
        print('usage: {} host port'.format(sys.argv[0]))
        sys.exit(84)
    else:
        print('launching client')
        ga = Game.Game(sys.argv[1], sys.argv[2])
        while ga.live is True and ga.read() is True:
            runStrat(ga)
