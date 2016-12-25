#!/usr/bin/perl

open(IN,"list");
#open(OUT,">13TeV_data_2015C_FSQJets3");
#open(OUT,">13TeV_data_2015C_Min_Bias");
open(OUT,">13TeV_data_2015C_ZeroBias");
@inn=<IN>;
for ($i=0; $i<=$#inn; $i++){
	#print OUT "/afs/cern.ch/work/i/ivanp/CFF_SOFT/CFF_SKIMS/13TeV/data_run2015C/$inn[$i]";
	for ($j=1; $j<=8; $j++){
		#print OUT "/afs/cern.ch/work/i/ivanp/CFF_SOFT/CFF_SKIMS/13TeV/data_run2015C/L1MinimumBiasHF$j/$inn[$i]";
		print OUT "/afs/cern.ch/work/i/ivanp/CFF_SOFT/CFF_SKIMS/13TeV/data_run2015C/ZeroBias$j/$inn[$i]";
	}
}
close(IN);
close(OUT); 
