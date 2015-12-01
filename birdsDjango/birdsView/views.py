from django.shortcuts import render
from django.template import RequestContext, loader
from django.http import HttpResponse
from django.http import Http404
from django.views.decorators.csrf import csrf_exempt
import json
import libgameworld


from .forms import *

# Create your views here.

def index(request):
    template = loader.get_template('index.html')
    context = RequestContext(request, {})
    return HttpResponse(template.render(context))

@csrf_exempt
def map(request):            
    ret = libgameworld.getmapinfo()
    return HttpResponse(ret)

@csrf_exempt
def simulate(request, x=50, y=50):    
    """if request.method != 'POST':
        raise Http404
    
    form = SimulateForm(request.POST)
    if form.is_valid() is not True:
        raise Http404
    """
    try:
      shootX = int(form.cleaned_data['shootX'])
      shootY = int(form.cleaned_data['shootY'])
    except:
      shootX = 10
      shootY = 10
    
    #return HttpResponse(json.dumps(dict))
    return HttpResponse(libgameworld.getsimulation(shootX,shootY))

    