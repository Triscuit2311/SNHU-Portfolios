
## Setting up local jupyter ecosystem for MAT243

*Note: Setup on windows, using python 3.11.X & VSCode.*

First ensure that the jupyter components are up to date.
Nbconvert is required for exporting notebooks as html or pdf.
```powershell
pip install --upgrade ipykernel
pip install --upgrade nbconvert
```

The following libraries are required for the code.
```powershell
pip install numpy
pip install pandas
pip install seaborn
pip install matplotlib
```