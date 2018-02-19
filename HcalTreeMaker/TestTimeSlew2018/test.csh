#!/bin/tcsh

set a = `echo $CMSSW_BASE | grep -Po '(?<=/uscms_data/d3/cmadrid/ana/HCAL/digi_pulseshape/)[^"]+'`
echo $a
