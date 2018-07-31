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


def test_Game_procOK():
    gm = Game.Game()
    gm.procKO([])
    assert gm.carry is False
    gm.procOK([])
    assert gm.carry is True


def test_Game_procPlayerState():
    gm = Game.Game()
    gm.state.uid = 12
    gm.procPlayerState(['12', '450', '20', '1', '0', '1', '0', '1'])
    assert gm.state.limited is True
    assert gm.state.ace is False


def test_Game_procWinner():
    gm = Game.Game()
    gm.proc('winner 7845')
    assert gm.live is False
    assert gm.winnerUid == 7845


def test_Game_procForfeit():
    gm = Game.Game()
    gm.proc('forfeit')
    assert gm.live is False
    assert gm.winnerUid == 0


def test_Game_proc():
    gm = Game.Game()

    gm.proc('id 12')
    assert gm.state.uid == 12
    gm.proc('playerstate 12 450 20 1 0 1 0 1')
    gm.proc('playerstate 12 450 20 1 0 1 1')
    gm.proc('playerstate 14 125 20 1 0 1 0 1')
    gm.proc('your_turn')
    gm.proc('info :kappa')
    assert gm.state.limited is True
    gm.proc('playerstate 12 450 20 0 0 1 0 1')
    assert gm.state.limited is False
    assert gm.players[0].limited is True
    assert gm.players[0].dist is 125
    gm.proc('ko')
    assert gm.carry is False
