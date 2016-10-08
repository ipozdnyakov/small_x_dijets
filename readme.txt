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


	measurement.cpp/.h	- class "Measurement" - combination of several observables

	object.cpp/.h		- class "Object" for phenomena from event (MN, incl dijets, etc.)

	function.cpp/.h		- class "Function" for particular values from  phenomena (pt, dphi, etc.)

	sample.cpp/.h		- class "Sample" for accessing events from the input data



	event.cpp/.h		- class "Event" for event data (nPV, triggers, weigth, jets, etc.)

	observable.cpp/.h	- class "Observable" = object + function = some plot (k_factor, decorr, etc.)

	bining.h		- global definition of bining arrays

	finder.cpp/.h		- set of functions to find required dijet in vectors


4. FUNCTIONALITY
----------------------------

/access_to_the_data	- [DONE] class "Sample" for access to each event
			  Sample -> ReadSample() -> ReadFile()

/access_to_the_event	- [DONE] class "Measurement" - combination of several observables,
			  Measurement -> ReadEvent(), Observable -> CatchObject(Object )

/efficiency_calc	- [TO BE DONE]

/sample_merging		- [TO BE DONE]

/pileup			- [TO BE DONE]

/jec_study		- [IN PROGRESS] jet energy correction study of the  data,  for  each 
			  observable from  the  set  of  observables  it  plots  observable
			  on  jets   with pt_plus_unc and pt_minus_unc results  are  stored
			  in  two  .root files, for each set of observables

/jer_study		- [TO BE DONE]

/phi_res		- [TO BE DONE]

/eta_res		- [TO BE DONE]

/unfolding		- [TO BE DONE]

/normalisation		- [TO BE DONE]

/final_values		- [TO BE DONE]

/total_syst		- [TO BE DONE]

5. NEED TO BE COMPATIBLE WITH CMSSW 
-----------------------------------
to use internal events (edmEvent) and objects (jets) classes and access to the data, triggers and so on..
