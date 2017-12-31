# JOYROOT
Set of tools to work with [ROOT](https://root.cern.ch/), to create better plots.
The structure is C++.

1. [Installation](#Installation)
2. [Creating files for analysis](#creating-files-for-analysis)
3. [Drawing plots](#drawing-plots)
4. [Make Selector](#make-selector)

## Installation

Be sure you have cmake in your system.

```bash
git clone https://github.com/palominogallo/JoyRoot
mkdir JoyRoot-v1-0
cd JoyRoot
cmake -DCMAKE_INSTALL_PREFIX=../JoyRoot-v1-0 .
make
make install
```

## Creating files for analysis
    This tool works with TTreereader structure (faster than old TBranch).

1) Go to your work area, then run the python script to create you source and analysis files.
```bash
cd <work area> # i.e work_area
python JoyRoot/scripts/makeAnaSkeleton.py work analysis Mass
```
2) You will noticed a directory created with name you defined on previous step and the class name `Mass` (the name is an example)
Add the branches you want to work.

## Drawing plots

Call the function like static tools:
```C++
Plot1::bookTH1F(,,);
```
and not like: 
```C++
Plot1 *p1;
p1->bookTH1F(,,);
```
## Make Selector
We can use the make selector can help us to create our branches used by TTreereader.
```bash
root -l
> TChain t("name of tree")
> t.Add("roorfilename")
> t.MakeSelector("temp") 
```
That will create `temp.c` and `temp.h` files,  copy and paste the branches inside `temp.h` into your class header.
