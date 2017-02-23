#!/usr/bin/perl

open(IN,"list");
#open(OUT,">13TeV_data_2015C_FSQJets3");
#open(OUT,">13TeV_data_2015C_Min_Bias");
#open(OUT,">13TeV_data_2015C_ZeroBias");
#open(OUT,">13TeV_mc_herwigpp_MinBias");
#open(OUT,">13TeV_mc_herwigpp_pt10to35");
#open(OUT,">>13TeV_mc_herwigpp_pt10to35_FB");
#open(OUT,">13TeV_mc_herwigpp_pt35toInf");
open(OUT,">13TeV_mc_herwigpp_pt35toInf_FB");
@inn=<IN>;
for ($i=0; $i<=$#inn; $i++){
	print OUT "/afs/cern.ch/work/i/ivanp/CFF_SOFT/CFF_SKIMS/13TeV/herwigpp_det/QCD_Pt35toInf_FB_13TeV_herwigpp_noPU/$inn[$i]";
}
close(IN);
close(OUT); 
