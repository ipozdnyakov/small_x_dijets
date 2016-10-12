1. INTRODUCTION
---------------
This project contains code for analises of low pile-up dijets in FSQ subgroup, 
particularly for analises like dijets k-factor and dijets decorrelations, 
looking for BFKL effects in pQCD.

This project takes input data from *.root files produced by 
other project - https://github.com/ipozdnyakov/cmssw_jets.git,
each file conatains TTree with one entry for each jet in the event.


2. ENVIRONMENT
--------------
Project is written to be run within CMSSW environment. 
Current version is used - CMSSW_7_4_15.
Top level of the project repository should be placed in /CMSSW_X_X_X/src/. 


3. CONTENT OF THE PROJECT
-------------------------
Initial commit consisted of separate folders each of which is containing 
a similar set of source files intended to perform specific task 
(efficiency study, plotting variables, etc.) Using git allows one to make 
more sofisticated and flexible control and reuse of similar parts,
so it goes.

To reflect the nature of the physical analysis of collisions data 
the workflow in the project is organised as follows

	- each task of the analysis developing in separate branch
	- after completion branch have to be merged to master branch
	- finally master branch should be a "button" for running full analysis

/Docs		- contains detailed information on various aspects of the analysis, 
		  additional to this readme.txt 

/Listing	- contains lists of files from 13TeV_DATA - output of 
		  git@github.com:ipozdnyakov/cmssw_jets project
		  (data stored in /afs/cern.ch/work/i/ivanp/13TeV_DATA/)

/Jec_txt	- contains *.txt files with JEC and uncertainties

maker_gcc	- script to compile the code to k_factor.exe, wich is the "final button"

main.cpp	- main code of the analysis

Source/Include  - *.cpp and *.h files correspondingly


	sample.cpp/.h		- class "Sample" for accessing events from the input data

	measurement.cpp/.h	- class "Measurement" - combination of several observables

	observable.cpp/.h	- class "Observable" = object + function = some plot (k_factor, decorr, etc.)

	function.cpp/.h		- class "Function" for particular values from  phenomena (pt, dphi, etc.)

	object.cpp/.h		- class "Object" for phenomena from event (MN, incl dijets, etc.)

	result.cpp/h.		- class "Result" calculation on several observables

	event.cpp/.h		- class "Event" for event data (nPV, triggers, weigth, jets, etc.)

	bining.h		- global definition of bining arrays

	finder.cpp/.h		- set of functions to find required dijet in vectors


4. FUNCTIONALITY
----------------------------

/access_to_the_data	- [DONE] class "Sample" for access to each event
			  Sample -> ReadSample() -> ReadFile()

/access_to_the_event	- [DONE] class "Measurement" - combination of several observables,
			  Measurement -> ReadEvent(), Observable -> ReadEvent()

/efficiency_calc	- [IN PROGRESS] family of observables MINBIAS

/samples_merging	- [IN PROGRESS] families of observables CNTR, FWD. CNTRnoFWD

/pileup			- [IN PROGRESS] the   same   as   for  JEC,  but   reference  file 
			  not written yet

/jec_study		- [DONE] jet energy correction  study  of  the   data,   for   each 
			  observable from  the  set  of  observables  it  plots  observable
			  on  jets   with pt_plus_unc and pt_minus_unc

/jer_study		- [TO BE DONE]

/phi_res		- [TO BE DONE]

/eta_res		- [TO BE DONE]

/unfolding		- [TO BE DONE]

/final_values		- [IN PROGRESS] class "Result"

/total_syst		- [IN PROGRESS] class "Result"

5.!!!!!! NEED TO combine WITH CommonFSQFramework
