# Analysis Tutorial

This package is intended to demonstrate some basic features of analysis tutorials and walk a new user through building a package, extracting physics information from the NodeTree, and then using that package to produce a root file that can be used for further analysis. The package demonstrates some basic features and contains some useful code for extracting physics information like reconstructed tracks, reconstructed EMCal clusters, and truth particle information (amongst some other things). 

Please note that this package is NOT intended to be a "do-it-all" package for you to start your analysis. The evaluator classes are aimed at detector evaluation, while this package is intended to showcase some of the basic features of developing your own analysis package and should serve as a reference for how to access commonly used analysis nodes off of the node tree.


## Building The Package

The first step to running the tutorial is to build the analysis package from src. Follow these instructions:

```bash
$ cd src
$ mkdir build
$ cd build
$ ../autogen.sh --prefix=$MYINSTALL
$ make
$ make install
```

Here, this assumes that you have set an environment variable `$MYINSTALL` that points to your install directory. For example, `$ echo $MYINSTALL` returns `/home/vagrant/install` for me, where the install directory is set on my virtual machine when running the Singularity container. The install directory can be wherever you like, but it is generally good practice to have one where all of your installation libraries will live.

You should also make sure that your `$LD_LIBRARY_PATH` and `$ROOT_INCLUDE_PATH` point to the correct place for your install directory. See [here](https://wiki.bnl.gov/sPHENIX/index.php/Example_of_using_DST_nodes) and [here](https://wiki.bnl.gov/sPHENIX/index.php/Sphenix_root6) for more details. You can use the following script to do this for you:


```bash
# for bash
source $OPT_SPHENIX/bin/setup_local.sh $MYINSTALL  

# for csh/tcsh
source $OPT_SPHENIX/bin/setup_local.csh $MYINSTALL  
```


## Running the example macro

The example macro, found in `macro/Fun4All_G4_EICDetector_AnaTutorial.C`, is just the default ECCE macro with the AnaTutorial package added to it. If you would like to see how the default macro and this macro are different, you can just open `Fun4All_G4_EICDetector_AnaTutorial.C` in your favorite text editor and search for `anatutorial`, or run a `diff` command on the two files. 


The macro can be run out of the box with `root Fun4All_G4_EICDetector_AnaTutorial.C`, and the type of event can be changed within the macro itself (e.g. between running single particle and pythia simulations).

In the event that the macro does not work, you should look at the default macro (which should always work) available [here](https://github.com/ECCE-EIC/macros/blob/master/detectors/EICDetector/Fun4All_G4_EICDetector.C). You can always run the AnaTutorial package by adding to the default macro `Fun4All_G4_EICDetector.C` the relevant code that calls AnaTutorial in `Fun4All_G4_EICDetector_AnaTutorial.C`. Just search for `anatutorial` in your favorite text editor in `Fun4All_G4_EICDetector_AnaTutorial.C` to see the lines of code that should be added to `Fun4All_G4_EICDetector.C`.


## Troubleshooting

In the event that the macros do not work, that is because they have become out of sync with the main macros repository. In the Fun4All macro that you want to run, add the following to the header files:

```
#include <anatutorialecce/AnaTutorialECCE.h>
R__LOAD_LIBRARY(libanatutorialecce.so)
```

and add the following after the line `if (Enable::USER) UserAnalysisInit();`

```
AnaTutorialECCE *anaTutorial = new AnaTutorialECCE("anaTutorial", outputroot + "_anaTutorial.root");
anaTutorial->setMinJetPt(3.);
anaTutorial->Verbosity(0);
anaTutorial->analyzeTracks(true);
anaTutorial->analyzeClusters(true);
anaTutorial->analyzeJets(true);
anaTutorial->analyzeTruth(false);
se->registerSubsystem(anaTutorial);
```

If you developed your own analysis package, you would use a similar workflow to add your analysis package to the macro that you want to run.