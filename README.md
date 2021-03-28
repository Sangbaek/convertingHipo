# convertingHipo

To compile
```
./compile
```

It creates executables in two directories.
Each directory has three files.

convertEPG: for experimental data

convertGen: for simulation data, saves all MC::Particle

convertRec: for simulation data, saves MC::Particle and REC::Particle

convertEPG can have an additional argument, which is the mode.
i.e.,

```
./convertEPG [mode]
```
where the mode can be "pi0" and "dvcs" for now.

## all

The executables in this directory saves all useful information,
such as Q2, missing masses, ...

##minimal
The executables in this directory saves px, py, pz of particles.
The convertEPG saves some logistic information such as run numbers too, because it's useful for the experimental data.