1. INTRODUCTION
---------------
This project contains code for analises of low pile-up dijets in FSQ subgroup, 
particularly for analises like dijets k-factor and dijets decorrelations, 
looking for BFKL effects in pQCD.

This project takes input data from *.root files produced by 
other projects
	 - https://github.com/ipozdnyakov/cmssw_jets.git	-each file conatains TTree with one entry for each jet in the event
	 - https://github.com/ipozdnyakov/CommonFSQFramework	-each file conatains TTree with one entry for each event


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

- finally master branch should be a "button" for running full analysis

/Docs		- contains detailed information on various aspects of the analysis, 
		  additional to this readme.txt 

	/listing	- contains lists of files from 13TeV_DATA - output of 
		  	git@github.com:ipozdnyakov/cmssw_jets project		- data stored in /afs/cern.ch/work/i/ivanp/CMSSW_SKIMS/
		  	git@github.com:ipozdnyakov/CommonFSQFramework  project	- data stored in /afs/cern.ch/work/i/ivanp/CFF_SOFT/CFF_SKIMS/

	/jec_txt	- contains *.txt files with JEC and uncertainties

maker_gcc	- script to compile the code to k_factor.exe, wich is the "final button"

main.cpp	- main code of the analysis

Source/Include  - *.cpp and *.h files correspondingly


	dataset.cpp/.h		- class "Dataset" for storing files and names for data in files

	measurement.cpp/.h	- class "Measurement" - combination of several observables
				>> push each event to each observable

	observable.cpp/.h	- class "Observable" = sample + object + function = some distribution
				>> check if event entry in the sample	- Sample->CheckEvent(event)
				>> construct object from event		- Object->LoadEvent(event)
				>> calculate function from object	- Function->CalculateValues(object)

	sample.cpp/.h		- class "Sample" for set of events (central, minbias, merged, etc.)
	object.cpp/.h		- class "Object" for phenomena from event (MN, incl dijets, etc.)
	function.cpp/.h		- class "Function" for particular values from  phenomena (pt, dphi, etc.)

	result.cpp/h.		- class "Result" calculation on several observables = some plot (eff, k_factor, decorr, etc.)

	event.cpp/.h		- class "Event" for event data (nPV, triggers, weigth, jets, etc.)

	bining.h		- global definition of bining arrays

	finder.cpp/.h		- set of functions to find required dijet in vectors


4. FUNCTIONALITY
----------------------------

class Measurement	- the main class over which all functionality is realised

/access_to_the_data	- [DONE] class "Dataset" to manage TTree name, branch names in TTrees and path to listing
			  Measurement -> ReadDataset() -> ReadFile() -> ReadEvent(), Observable -> ReadEvent()

/efficiency_calc	- [DONE] class "Sample" to measure observables on various sets of events
			  based on triggers + selection - "central_trg", "forward2_trg", "forward3_trg" samples
			  based on dataset  + selection - "unbiased" sample

/samples_merging	- [IN PROGRESS] new samples for calculating weights and merging
			  based on dataset 		 - "low_pthat", "high_pthat" samples
			  based on datasets and triggers - "central", "central_no_fwd", "forward" samples
			  based on reweighting		 - "merged" sample

/pileup			- [IN PROGRESS] the same as for JEC, but reference file not written yet

/jec_study		- [DONE] jet energy correction  study  of  the   data,   for   each 
			  observable from  the  set  of  observables  it  plots  observable
			  on  jets   with pt_plus_unc and pt_minus_unc

/mc_processing		- [TO BE DONE]

/jer_study		- [TO BE DONE]

/phi&eta_res		- [TO BE DONE]

/unfolding		- [TO BE DONE]

/final_values		- [IN PROGRESS] class "Result"

/total_syst		- [IN PROGRESS] class "Result"

/syst_correlations	- [TO BE DONE]
