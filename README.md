# JOYROOT
Set of tools to work with [ROOT](https://root.cern.ch/), to create better plots.
The structure is C++.

## Compilation

1. Change setup.csh or setup.sh according to your path
2. Change on `src/Makefile` according to OS:
```bash
> LDFLAGS += -shared -Wl,-install_name #Mac OS X
> DFLAGS += -shared -Wl,-soname #LINUX 
```
3. Compile
```bash
> make
```

## Creating files for analysis
	This tool works with TTreereader structure (faster than old TBranch).

1. Go to your work area, then run the python script to create you source and analysis files.
```bash
cd <work area> # i.e work_area
python JoyRoot/scripts/makeAnaSkeleton.py work analysis Mass
```
2. You will noticed a directory created with name you defined on previous step. And the class name `Mass` (the name is an example)
Add the branches you want to work.

## Drawing plots

Call the function like static tools like:
```C++
Plot1::bookTH1F(,,);
```
and not like: 
```C++
Plot1 *p1;
p1->bookTH1F(,,);
```

