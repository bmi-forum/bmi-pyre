###
# Docker file for building a container ready for building and running BMI-Pyre-SNAC
# This does NOT build clone and build bmi-pyre yet.
# 
# Some basic build instructions:
# ```
# docker build -t ${DOCKER_HUB_ID}/${PROJECT_NAME}:${TAG} .
# # run a shell in the container to inspect the environment (as root):
# docker run --rm -it ${DOCKER_HUB_ID}/${PROJECT_NAME}:${TAG} /bin/bash
# ```
###
FROM ubuntu:14.04
MAINTAINER Eunseo Choi "echoi2@memphis.edu"

### Install bmi-pyre and dependencies.

# Get the barebone linux ready for building packages.
RUN apt-get update
RUN apt-get -y install gcc-4.8
RUN apt-get -y install python python-dev
RUN apt-get -y install zlib1g-dev
RUN apt-get -y install libxml2 libxml2-dev
RUN apt-get -y install mpich
RUN apt-get -y install git

# Add a normal user, 'bmiuser'.
RUN adduser --disabled-password --gecos '' bmiuser
RUN adduser bmiuser sudo
RUN chown -R bmiuser:bmiuser /home/bmiuser

###
### Becoming 'bmiuser' doesn't work, which causes failure in running git below.
###
# RUN cd && cp -R .bashrc .profile /home/bmiuser
# ADD .ssh /home/bmiuser/.ssh
# RUN su -m bmiuser
# USER bmiuser
# ENV HOME /home/bmiuser
# WORKDIR /home/bmiuser/bmiprojects
# RUN cd /home/bmiuser/bmiprojects
#
### Check out bmi-pyre and bmi-python
# RUN su bmiuser -c 'git clone git@github.com:bmi-forum/bmi-pyre.git'
# RUN git clone https://github.com/csdms/bmi-python.git

# Build bmi-pyre
# RUN cd ./bmi-pyre