#!/usr/bin/perl

open(IN,"list");
open(OUT,">13TeV_data_2015C_FSQJets3");
@inn=<IN>;
for ($i=0; $i<=$#inn; $i++)
	{
	$fname=substr($inn[$i],67,-1);
	print OUT "/afs/cern.ch/work/i/ivanp/CFF_SOFT/CFF_SKIMS/13TeV/data_run2015C/FSQJets3/$inn[$i]";
	}
close(IN);
close(OUT); 
