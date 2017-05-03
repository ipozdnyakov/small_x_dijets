#!/usr/bin/perl

open(IN,"list");
#open(OUT,">13TeV_data_2016H_FSQ_Jets");
open(OUT,">13TeV_data_2016H_Min_Bias");
#open(OUT,">13TeV_data_2015C_FSQJets3");
#open(OUT,">13TeV_data_2015C_Min_Bias");
#open(OUT,">13TeV_data_2015C_ZeroBias");
#open(OUT,">13TeV_mc_herwigpp_MinBias");
#open(OUT,">13TeV_mc_herwigpp_pt10to35");
#open(OUT,">>13TeV_mc_herwigpp_pt10to35_FB");
#open(OUT,">13TeV_mc_herwigpp_pt35toInf");
#open(OUT,">13TeV_mc_herwigpp_pt35toInf_FB");
@inn=<IN>;
$j=0
#for ($j=0; $j<=9; $j++){
for ($i=0; $i<=$#inn; $i++){
	print OUT "/afs/cern.ch/work/i/ivanp/CFF_SOFT/CFF_SKIMS/13TeV/data_2016H/L1MinimumBias$j/$inn[$i]";
}
#}
close(IN);
close(OUT); 
