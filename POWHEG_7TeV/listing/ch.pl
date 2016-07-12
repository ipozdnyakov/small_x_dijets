#!/usr/bin/perl
open(IN,"./list");
open(OUT,">./powheg_cteq6l");
@inn=<IN>;
for($i = 0; $i <=$#inn; $i++)
		{
		$fname=substr($inn[$i],0,-1);
		print OUT "/afs/cern.ch/work/i/ivanp/MC/powheg/$fname\n";
				}
close(IN);
close(OUT);
