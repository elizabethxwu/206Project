#!/usr/bin/perl

use strict;
use warnings;
use CGI ':standard', '-debug';

my $q = new CGI;

print $q->header;
print $q->start_html;

my $name = param("FullName");
my $username = param("Username");
my $password = param("Password");
my $confirm_password = param("ConfirmPassword");




# print $q->h1($name);
# print $q->h1($username);
# print $q->h1($password);
# print $q->h1($confirm_password);
if ($password ne $confirm_password){
	print $q->h1("Password not equal");
}

my $members = 'Members.csv';
open(INFO, "<$members" || die $!);
my @lines = <INFO>;
close(INFO);
my $line;
my $exists=0;
foreach $line (@lines){
	my @memberinfo = split(/,/, $line);
	if ($memberinfo[1] eq $username){
		print"invalid name!\n";
		$exists = 1;
	}
}
if($exists == 0){
	open(INFO, ">>$members" || die $!);
	print INFO "$name,$username,$password\n";
	print "you hav been successfully added \n please go back to the home page";
	print "        <ul> <a href='../index.html'>Home </a> </ul>";
}


print $q->end_html;
