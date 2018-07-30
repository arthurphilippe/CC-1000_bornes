import Game


def test_Game_create():
    gm = Game.Game()
    assert gm.state.uid is 0
    assert gm.connected is False
    assert len(gm.hand) is 6
    for card in gm.hand:
        assert card is Game.Card.NONE
    assert len(gm.players) is 0


def test_Game_procLsCards_normal():
    gm = Game.Game()
    gm.procLsCards(['20', '2', '0', '1', '14', '6'])
    assert gm.hand[0] is Game.Card.NONE
    assert gm.hand[1] is Game.Card.HazFlatTire
    assert gm.hand[2] is Game.Card.HazCarCrash


def test_Game_procLsCards_error_count():
    gm = Game.Game()
    gm.procLsCards(['20', '2', '0', '1', '14'])
    for card in gm.hand:
        assert card is Game.Card.NONE


def test_Game_procLsCards_error_content():
    gm = Game.Game()
    gm.procLsCards(['20', '45', '0', 'kappa', '14', '6'])
    assert gm.hand[1] is Game.Card.NONE
    assert gm.hand[3] is Game.Card.NONE


def test_Game_procKO():
    gm = Game.Game()
    gm.procKO([])
    assert gm.carry is False


def test_Game_procPlayerState():
    gm = Game.Game()
    gm.state.uid = 12
    gm.procPlayerState(['12', '450', '20', '1', '0', '1', '0', '1'])
    assert gm.state.limited is True
