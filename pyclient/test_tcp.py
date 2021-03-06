import unittest
import tcp


class dummySock:
    def __init__(self):
        self.count = 0

    def recv(self, count):
        if self.count is 0:
            self.count = 1
            return b'I like trains\nkappa\n\rwa kawai\n\r'
        else:
            return b''


class Socket(unittest.TestCase):
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


class Queue(unittest.TestCase):
    def test_fill(self):
        queue = []
        self.assertEqual(len(queue), 0)
        sock = dummySock()
        queue = tcp.fillQueue(sock, queue)
        self.assertEqual(queue[0], 'I like trains')
        self.assertEqual(queue[1], 'kappa')
        self.assertEqual(queue[2], 'wa kawai')

    def test_empty_quit(self):
        queue = []
        self.assertEqual(len(queue), 0)
        sock = dummySock()
        queue = tcp.fillQueue(sock, queue)
        queue = tcp.fillQueue(sock, queue)
        self.assertEqual(queue[0], 'I like trains')
        self.assertEqual(queue[1], 'kappa')
        self.assertEqual(queue[2], 'wa kawai')
        self.assertEqual(queue[3], 'quit')


if __name__ == '__main__':
    unittest.main()
