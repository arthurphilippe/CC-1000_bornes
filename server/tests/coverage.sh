#!/bin/bash

set -e

echo ":: Rebuilding with coverage flags..."
make fclean
make tests_run -j 4
echo " --> Test and build complete!"


if [ "$1" == "html" ] || [ "$2" == "html" ]; then
	echo -e "\n:: Proccessing coverage artefacts..."
	gcovr -r . --html -o coverage.html --html-details --exclude-directories=tests/ --delete -s

	mkdir -p coverage
	mv *.html coverage/
else
	echo -e "\n:: Proccessing coverage artefacts..."
	gcovr -r . --delete -s > coverage.log
	echo " --> Success! (coverage info was written to \"coverage.log\")"
fi

echo ":: Cleanning up..."
make fclean
