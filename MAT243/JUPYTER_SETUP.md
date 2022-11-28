
## Setting up local jupyter ecosystem for MAT243

Please note this is for people unfamiliar with python packages or jupyter. (Some Classmates)

*Note: Setup on windows, using python 3.11.X & VSCode.*


Ensure pip is up to date.
```powershell
python.exe -m pip install --upgrade p
```

Next, ensure that the jupyter components are up to date.
Nbconvert is required for exporting notebooks as html or pdf.

```powershell
pip install --upgrade ipykernel
pip install --upgrade nbconvert
```

The following libraries are required for the discussion code.
```powershell
pip install numpy
pip install pandas
pip install seaborn
pip install matplotlib
pip install statsmodels
```