import Game


def test_Game_create():
    gm = Game.Game()
    assert gm.id is 0
    assert gm.connected is False
    assert len(gm.hand) is 6
    for card in gm.hand:
        assert card is Game.Card.NONE
    assert len(gm.players) is 6
    for player in gm.players:
        assert player.dist is 0
        assert player.incident is Game.Card.NONE
