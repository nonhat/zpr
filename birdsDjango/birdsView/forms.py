 
from django import forms

class SimulateForm(forms.Form):
    shootX = forms.DecimalField()
    shootY = forms.DecimalField()
    