#! /usr/bin/perl
use strict;

my $filename=shift || die 'Usage: parse.pl FILENAME';

# Open input file
open(F, '<', $filename) || die 'File not found!';

# Parse header
my $header=<F>;
my $i=0;
my %column;
foreach my $item (split(/,/, $header)) {
	$item=$1 if ($item=~/^\s*(.*?)\s*$/);
	$column{$item}=$i;
	$i++;
}
die 'Unable to parse header (first line)!' if ($i<2);

# Parse size
my $size=<F>;
$size=~/(\d+)\s+(\d+)/ || die 'Unable to parse size (second line)!';
my $size_z=$1-2;
my $size_x=$2-2;

# Open output files
open(X, '>', $filename.'_X');
open(Z, '>', $filename.'_Z');
open(U, '>', $filename.'_U');
open(W, '>', $filename.'_W');

# Parse values
my $count_x=0;
while (my $line=<F>) {
	while (chomp $line) {}

	# Parse line
	my @values=split(/,/, $line);

	# Print values
	print X $values[$column{'X'}]*1;
	print Z $values[$column{'Z'}]*1;
	print U $values[$column{'VelocityU'}]*1;
	print W $values[$column{'VelocityW'}]*1;

	# Increment
	$count_x++;
	if ($count_x>=$size_x) {
		print X "\n";
		print Z "\n";
		print U "\n";
		print W "\n";
		$count_x=0;
	} else {
		print X "\t";
		print Z "\t";
		print U "\t";
		print W "\t";
	}
}

# Close files
close F;
close X;
close Z;
close U;
close W;
