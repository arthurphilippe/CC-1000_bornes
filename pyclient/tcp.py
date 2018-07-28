#!/bin/python3

import socket #for sockets
import sys #for exit

def create():
	try:
		# create an AF_INET, STREAM socket (TCP)
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	except socket.error as error:
		raise RuntimeError(error)
	return s

def connect(sock, hostname="0.0.0.0", port=4242):
	# Resolve the hostname
	try:
		remote_ip = socket.gethostbyname(hostname)

	except socket.error as error:
		raise RuntimeError(error)
	print('Resolved hostname ' + hostname + ' as being ' + remote_ip)

	# Connect to remote server
	try:
		sock.connect((remote_ip , port))
	except socket.error as error:
		raise RuntimeError(error)

	print('Socket Connected to ' + hostname + ' on ip ' + remote_ip)

if __name__ == '__main__':
	try:
		s = create()
	except RuntimeError as error:
		print(error, sys.stderr)
		sys.exit(1)

	try:
		connect(s, "www.google.fr", 80)
		print('Socket Created')
	except RuntimeError as error:
		print(error, sys.stderr)
		sys.exit(1)
	finally:
		s.close()
		print('Socket Closed')
