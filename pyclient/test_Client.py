import Client
import Game


def test_findCard():
    gm = Game.Game()
    gm.procLsCards(['20', '2', '0', '1', '14', '6'])

    assert Client.findCard(gm, Game.Card.HazFlatTire) is 1
    assert Client.findCard(gm, Game.Card.NONE) is 0
    assert Client.findCard(gm, Game.Card.HazCarCrash) is 2
    assert Client.findCard(gm, Game.Card.DefGas) is 5
    assert Client.findCard(gm, Game.Card.Dst100kms) is -1


def test_findBestDist():
    gm = Game.Game()
    gm.procLsCards(['20', '2', '0', '1', '11', '6'])
    assert Client.findBestDist(gm) is -1

    gm.procLsCards(['20', '2', '0', '1', '14', '6'])
    assert Client.findBestDist(gm) is 4

    gm.procLsCards(['20', '2', '0', '15', '14', '6'])
    assert Client.findBestDist(gm) is 3

    gm.procLsCards(['20', '2', '0', '15', '14', '16'])
    assert Client.findBestDist(gm) is 5

    gm.procLsCards(['20', '2', '17', '15', '14', '16'])
    assert Client.findBestDist(gm) is 2

    gm.procLsCards(['18', '2', '17', '15', '14', '16'])
    assert Client.findBestDist(gm) is 0
