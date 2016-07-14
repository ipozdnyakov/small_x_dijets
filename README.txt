1. INTRODUCTION
---------------
This project contains code for analyses of low pile-up dijets in FSQ subgroup, particularly for 
analyses like dijet k-factor and dijets decorrelations, looking for BFKL effects in pQCD.

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

	- each branch (except master) contains a code for specific task of the analysis in separate directory
	- all branches should be merged to master branch
	- it is normally if master branch will never be integrated and will be only a container for common README.txt
	  and code of each branch in separate directory



4. STEPS OF THE ANALYSIS
------------------------
Each step is a branch in its nature.

/jec_study	- jet energy correction study of the data, for each observable from 
		  the  set  of  observables  it  plots  observable  on  jets   with 
		  pt_plus_unc and pt_minus_unc results  are  stored  in  two  .root 
		  files, for each set of observables


5. DATA
-----------

/listing - contains lists of files from 13TeV_DATA (output of git@github.com:ipozdnyakov/cmssw_jets project)
(data stored in /afs/cern.ch/work/i/ivanp/13TeV_DATA/)
