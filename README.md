# ePICRecoDataAnalysis
Analysis of ePIC reconstructed data. The code is written so that it can be easily converted between 3 different data reading modes:
- ROOT trees
- `podio::ROOTFrameReader`
- `podio::EventStore`

### To run interactively:


```Sh
root -l -b -q readFrameRootReco.C+ | tee run.log
```

Old:

```Sh
root -l -b -q readTreeReco.C+ | tee run.log
```

### To compile executable:

```Sh
make
```

and Run:


```Sh
./readFrameRootRecoMain | tee run.log
```

Old:

```Sh
./readTreeRecoMain | tee run.log
```

### Batch scripts to use condor on RCF

```Sh
submitRecoAnalysis.job
runRecoAnaBatch.sh
```
Submit with:

```Sh
condor_submit submitRecoAnalysis.job
```

### TO DO
1. Add more histograms and functionality
2. Add macros for drawing histograms