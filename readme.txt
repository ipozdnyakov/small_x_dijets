1. INTRODUCTION
---------------
This project contains code for analises of low pile-up dijets in FSQ subgroup, particularly for 
analises like dijet k-factor and dijets decorrelations, looking for BFKL effects in pQCD.

This project takes input data from .root files produced by https://github.com/ipozdnyakov/cmssw_jets.git,
each file conatains TTree with one entry for each jet in the event.



2. ENVIRONMENT
--------------
Project is written to be run within CMSSW environment. Current version is used - CMSSW_7_4_15.
Top level of the project repository should be placed in /CMSSW_X_X_X/src/. 



3. CONTENT OF THE PROJECT
-------------------------
Initial commit consists of separate folders each of which is containing a similar set of source files
intended to perform specific task (efficieny study, plotting variables, etc.)

Using git allows one to make more sofisticated and flexible control and reuse of similar parts, so it goes.

To reflect the nature of the physical analysis of collisions data 
the workflow in the project is organised as follows

	- each branch contains a code for specific task of the analysis in separate
	- all branches should be merged to master branch
	- finally master branch should be a "button" which one can push to perform full steps of analysis

3.1 CONTENT

/Listing	- contains lists of files from 13TeV_DATA (output of git@github.com:ipozdnyakov/cmssw_jets project)
		  (data stored in /afs/cern.ch/work/i/ivanp/13TeV_DATA/)

/Jec_txt	- contains .txt files with JEC and uncertainties

/Docs		- contains detailed information on various aspects of the analysis, additional to this readme 

maker_gss	- script to compile the code to k_factor.exe, wich is the "final button"

3.2 CODE OF MASTER BRANCH

main.cpp	- main code of the analysis

Reader.cpp/.h	- function for reading each file from the list

Finder.cpp/.h	- set of functions to find required dijet in the event (event is a vector of jets)

Observables.cpp/.h	- class, contains set of histograms and functions for analysis of particular type of dijets

3.3 BRANCHES

/jec_study	- jet energy correction study of the data, for each observable from 
		  the  set  of  observables  it  plots  observable  on  jets   with 
		  pt_plus_unc and pt_minus_unc results  are  stored  in  two  .root 
		  files, for each set of observables


