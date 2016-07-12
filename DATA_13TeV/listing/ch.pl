#!/usr/bin/perl
open(IN,"./list");
open(OUT,">./FSQJets_2016B_VdMmay_list");
@inn=<IN>;
for($i = 0; $i <=$#inn; $i++)
		{
		$fname=substr($inn[$i],0,-1);
		print OUT "/afs/cern.ch/work/i/ivanp/2015_JetHunter/CMSSW_8_0_5/src/JetAnalyzer/MyJetAnalyzer/crab/FSQJets_2016B_VdMmay/crab_FSQJets_2016B_VdMmay/results/$fname\n";
				}
close(IN);
close(OUT);
