How to use these files
======================

`pileup.csv.tgz`
----------------
- a tarball containing a csv file full of minbias events
- each line is a single particle with $p_T > 1$ GeV and $|\eta| < 2.5$.
- each particle comes with an event number, PDG ID, charge, and 3-momentum.
- if an event number is missing, it means there was no fiducial for that event.
- "missing" events should not be neglected!! they are just "trivial" in a sense.



`ttbar.csv.tgz`
----------------
- a tarball containing a csv file full of jets ($R = 1.0$, $p_T > 250$ GeV) from
$t\bar t$ events 
- each line is a single particle with $p_T > 1$ GeV and $|\eta| < 2.5$.
- each particle comes with a jet number, PDG ID, charge, and 3-momentum.
- events with no high-$p_T$ jets simply don't appear -- no need to handle them.
