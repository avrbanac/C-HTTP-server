# HOWTO (things work)

This file contains explanation on how httpserv works and also how life cycle of the
request looks like. In order to extend server functionality, it is important to understand
this data flow: to and from server.

# Global information

Roughly, httpserv can be divided into 5 distinct logical parts:

- init part (main.c), where all initialization processes take place together with main application loop
- configuration part (config.c, config.h, config.ini)
- utility part (helper.c, helper.h) where all helper functions reside
- request handling
- response handling

__NOTES:__ 

- For additional information about configuration, look at the comments in `config.ini`.
- Both request and response logic is further divided into header part and data part

# Request life cycle

- upon initialization in main.c, first configuration file (by default config.ini) is parsed for required config values
- in indefinite loop server waits for connection and if it receives one, it spawns child process to serve connection
- child process is calling ServiceRequest (`servreq.c`)
- ServiceRequest will first GetRequest() (`reqhead.c`) and then ParseHTTPHeader (`reqhead.c`)
- ServiceRequest will then CheckResource (`resource.c`)
- depending on request `REST` and existence of requested resource further actions are triggered
- currently valid options for those actions: exec script / run binary / return resource
- ServiceRequest is returning response header (`resphead.c`)
- ServiceRequest is returning additional information about taken action if needed (`resource.c`)
- if something failed, ServiceRequest is returning error (`resource.h`)
- ServiceRequest is freeing request info resources (`resource.c`)
- child process is ending and parent process id waiting for next connection

# TODO

- one of the following versions should implement return value from running script/binary
- implement direct STB command functionality
- implement screen capture wrapper for STB

# to be continued... :P
