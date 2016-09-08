1. INTRODUCTION
---------------
This project contains code for analises of low pile-up dijets in FSQ subgroup, 
particularly for analises like dijet k-factor and dijets decorrelations, 
looking for BFKL effects in pQCD.

This project takes input data from .root files produced by 
https://github.com/ipozdnyakov/cmssw_jets.git,
each file conatains TTree with one entry for each jet in the event.


2. ENVIRONMENT
--------------
Project is written to be run within CMSSW environment. 
Current version is used - CMSSW_7_4_15.
Top level of the project repository should be placed in /CMSSW_X_X_X/src/. 


3. CONTENT OF THE PROJECT
-------------------------
Initial commit consists of separate folders each of which is containing 
a similar set of source files intended to perform specific task 
(efficieny study, plotting variables, etc.) Using git allows one to make 
more sofisticated and flexible control and reuse of similar parts,
so it goes.

To reflect the nature of the physical analysis of collisions data 
the workflow in the project is organised as follows

	- each task of the analysis developed in separate branch
	- after completion branch have to be merged to master branch
	- finally master branch should be a "button" for running full analysis

/Docs		- contains detailed information on various aspects of the analysis, 
		  additional to this readme.txt 

/Listing	- contains lists of files from 13TeV_DATA - output of 
		  git@github.com:ipozdnyakov/cmssw_jets project
		  (data stored in /afs/cern.ch/work/i/ivanp/13TeV_DATA/)

/Jec_txt	- contains .txt files with JEC and uncertainties

maker_gcc	- script to compile the code to k_factor.exe, wich is the "final button"

main.cpp	- main code of the analysis

Source/Include  - *.cpp and *.h files correspondingly

	Observable.cpp/.h	- base class for each observable

	Reader.cpp/.h		- function for reading each file from the list

	Finder.cpp/.h		- set of functions to find required dijet in the event

4. TASK FLOW (FUNCTIONALITY)
----------------------------

/access_to_the_data	- [IN PROGRESS] framework for access to each event

/introduce_observation	- [TO BE DONE] base class for all further observables

/define_observable	- [TO BE DONE] framework to define particular observable

/plot_observables	- [TO BE DONE] plot all defined observable

/jec_study		- [TO BE DONE] jet energy correction study of the  data,  for  each 
			  observable from  the  set  of  observables  it  plots  observable
			  on  jets   with pt_plus_unc and pt_minus_unc results  are  stored
			  in  two  .root files, for each set of observables
