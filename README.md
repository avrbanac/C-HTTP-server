# Web Server (aka httpserv)

This small lightweight server can be compiled using STB SDK to provide 2-way communication solution
for STB using HTTP. It can be used both as simple http server which can return resources to client
side, or as a tool (shell wrapper) to send commands to STB.
The whole idea behind this small project was to have a small tool which I could use on Motorola STB 
to kill a process through JS (or run any script on STB FS).
This server is not production tool quality. It is intended to be used as testing tool.

## Structure

    <root>
        ├── inc/
        |   ├── config.h
        |   ├── helper.h
        |   ├── reqhead.h
        |   ├── resource.h
        |   ├── resphead.h
        |   └── servreq.h
        ├── src/
        |   ├── config.c
        |   ├── helper.c
        |   ├── reqhead.c
        |   ├── resource.c
        |   ├── resphead.c
        |   └── servreq.c
        ├── .dep.inc
        ├── .editorconfig
        ├── .gitignore
        ├── CHANGELOG.md
        ├── HOWTO.md
        ├── README.md
        ├── config.ini
        ├── Makefile
        └── main.c


## Install

- Before compiling:

    - Check for needed changes to config.ini
    - Check for needed changes to makefile

- Run make
- After compiling:

    - Include binary to STB image and rebuild
    - Arrange all other needed files (e.g. config.ini)


## Usage 

- Compiled binary can be run without arguments to make it read default configuration file
- Different configuration file can be provided through argument (with full absolute pathing)
- New _key-value_ pairs can be added to configuration, but they will be skipped
- It is __necessary__ to provide required keys through configuration
- Server can parse simple and full http requests, but it will skip header part
- Currently, server does not provide any security solutions
- If request starts with `/<ACTION_CMD>/` (can be changed through configuration), it will trigger script
- Any following _rest_ structure after `/<ACTION_CMD>/` will be converted to script arguments
- If request starts with `/<ACTION_RUN>/` , it will try to run __\<ARG1\>__ as executable
- Any following _rest_ structure after `/<ACTION_RUN>/` will be converted to arguments


## Troubleshooting

``` bash
$ wget "http://<address>:<port>/<some/existing/resource>"
$ wget "http://<address>:<port>/<exec/arg1/arg2/../>"
$ echo -e "GET /<resource> HTTP/1.1\n" | nc <address> <port>
$ echo -e "GET /<resource>\n" | nc <address> <port>
```

__For more in-depth explanation on how things work please see [HOWTO](HOWTO.md).__

## Change log

Please see [CHANGELOG](CHANGELOG.md) for more information what has changed recently.


## Copyright (c) 2016 :P

- This softwere is an open source.
- Feel free to use, change, update or do whatever you like with this code or any part of it.
- Some ideas and solutions were taken from [Paul Griffiths](http://www.paulgriffiths.net/program/c/webserv.php)


## Author

- Aljosa Vrbanac (__avrbanac__)
- Inspired by Paul Griffiths (original code)
