# packet-collector

A utility for collecting and persisting network packets. 

Currently, a work in progress.  Being developed on an Intel i7 920 cpu under a 2.6.32-358.2.1.el6.x86_64 Linux kernel and currently working on getting it up and running and sorting out some of the design issues.

# Dependencies:

* libpcap-devel-1.0.0
* libpcap-1.0.0
* libconfig-devel.x86_64 0:1.3.2
* libconfig-1.3.2
* boost_1_54_0:
	- Installed it from source into /usr/local/boost_1_54_0
	- Add CPLUS_INCLUDE_PATH env var with ':' separated list of paths (including /usr/local/boost, obviously)
