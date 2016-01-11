#!/usr/bin/env mpipython.exe
"""Basic Model Interface implementation for SNAC as a Pyre application."""

#### Pyre-SNAC-specific setup
import StGermain
import StGermain.Base.IO.Dictionary
from StGermain.Base.IO.Dictionary import Dictionary
from Snac.Context import Context
import StGermain.Bindings.MPI as MPI

# We have to init here because a default to the inventory in snac requires construction of StGermain things... the only way to
# fix this is to upgrade to pythia-0.8, which will mean citcom and exchanger needs to too.
StGermain.initialise()

#### BMI-specific setup
import types

from bmi import Bmi

class BmiPyreSnac(Bmi):

    """Run SNAC as a Pyre application using BMI."""

    _name = 'SNAC as a Pyre application'
    _input_var_names = ('surface_topography',)
    _output_var_names = ('surface_topography',)

    def __init__(self):
        """Create a BmiPyreSnac model that is ready for initialization."""
        self._model = None
        self._values = {}
        self._var_units = {}
        self._grids = {}
        self._grid_type = {}

    def initialize(self, filename=None):
        """
            Initialize the Pyre-SNAC model.
        """
        d = Dictionary( StGermain.Base.IO.Dictionary.new() )

        if filename is None:
            d.LoadFromFile( "basic.xml" )
        elif isinstance( filename, types.StringTypes ):
            
            d.LoadFromFile( filename )
        else:
            print "Need to specify a path to a valid input file."

        self._model = Context( d, MPI.COMM_WORLD() )
        self._model.Construct()
        self._model.Build()
        self._model.Initialise()

    def run(self):
        """Run model as specified in the input file."""
        self._model.Execute()

    def update(self):
        """Advance model by one time step."""
        dt = self._model.Dt()
        self._model.Step( dt )

    def update_frac(self, time_frac):
        """Update model by a fraction of a time step.

        Parameters
        ----------
        time_frac : float
            Fraction fo a time step.
        """
        time_step = time_frac * self._model.Dt()
        #self._model.time_step = time_frac * time_step
        #self.update()
        self._model.Step( time_step )

    # def update_until(self, then):
    #     """Update model until a particular time.

    #     Parameters
    #     ----------
    #     then : float
    #         Time to run model until.
    #     """
    #     n_steps = (then - self.get_current_time()) / self.get_time_step()

    #     for _ in xrange(int(n_steps)):
    #         self.update()
    #     self.update_frac(n_steps - int(n_steps))

    def finalize(self):
        """Finalize model."""
        self._model.Destroy()

'''
# API defined in StGermain/Base/Context/Python/Context.py

    def Print( self ):
        return bindings.Print( self._handle )
    
    def Construct( self ):
        self._handle = bindings.Construct( self._handle )
        return None
    
    def Build( self ):
        return bindings.Build( self._handle )
    
    def Initialise( self ):
        return bindings.Initialise( self._handle )
    
    def Execute( self ):
        return bindings.Execute( self._handle )
        
    def Destroy( self ):
        return bindings.Destroy( self._handle )
        
    def Dt( self ):
        return bindings.Dt( self._handle )
    
    def Step( self, dt ):
        return bindings.Step( self._handle, dt )
    
    def __init__( self, handle ):
        self._handle = handle
        self.dictionary = Dictionary.Dictionary( bindings.GetDictionary( self._handle ) )
        return

    def handle(self):
        return self._handle

    def Delete( self ):
        return bindings.Delete( self._handle )

    def SetTime( self, time ):  
        bindings.SetTime( self._handle, time )
        self.__time = time

    def GetTime( self ):
        return self.__time

    time = property( GetTime, SetTime, doc="Current sim. time.")
    
    def SetStep( self, timeStep ):
        bindings.SetTimeStep( self._handle, timeStep )
        self.__timeStep = timeStep

    def GetStep( self ):    
        return self.__timeStep

    step = property( GetStep, SetStep, doc="Current sim. step.")
'''