import unittest
import tcp


class TestTcp(unittest.TestCase):
    def test_create(self):
        s = tcp.create()
        self.assertNotEqual(s.fileno, -1)
        s.close()

    def test_connect(self):
        s = tcp.create()
        success = True
        try:
            tcp.connect(s, "google.fr", 80)
        except:
            success = False
        finally:
            s.close()
        self.assertEqual(success, True)

    # def test_connect_fail_port(self):
    #     s = tcp.create()
    #     success = True
    #     try:
    #         tcp.connect(s, "google.fr", 8042)
    #     except:
    #         success = False
    #     finally:
    #         s.close()
    #     self.assertEqual(success, False)

    def test_connect_fail_host(self):
        s = tcp.create()
        success = True
        try:
            tcp.connect(s, "gaagle.france", 80)
        except:
            success = False
        finally:
            s.close()
        self.assertEqual(success, False)


if __name__ == '__main__':
    unittest.main()
