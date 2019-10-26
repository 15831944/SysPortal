#!/usr/bin/perl

# DO NOT EDIT code below this line!!#  perl script online shoping
#   developer: Vladimir Novick v_novick@yahoo.com 19.12.2000

   $fn = "D:/SysPortal/TreeWebControl/Users/contents.mnu";      	print "Content-Type: text/html\n\n";   
open(INPUT, "< $fn");
  
  while (<INPUT>) {
    $rString = $_;    $LineP = $.;    print "$rString";
    }

   close(FILE);
