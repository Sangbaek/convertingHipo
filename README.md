# convertingHipo

To compile
```
./compile
```

It creates executables in two directories.
Each directory has three files.

convertEPG: for experimental data

convertGen: for simulation data, saves all MC::Particle (depreciated)
convertGen2: for dvcs simulation data, saves xB Q2 t phi weight radMode only for fast i/o.

convertRec: for simulation data, saves MC::Particle and REC::Particle (for dvpi0p)
convertRec: for simulation data, saves MC::Particle and REC::Particle with radMode for dvcs simulation

convertEPG can have an additional argument, which is the mode.
i.e.,

```
./convertEPG [mode]
```
where the mode can be "pi0" and "dvcs" for now.

## all
saves all possible vars. (depreciated as of Mar. 9.)

## minimal
Saves all rec/ pid vars required for dvcs and dvpi0p research.

## nonfid
Saves rec vars only useful for dvcs dvpi0p research
