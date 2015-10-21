
from archimedes import use_merlin
use_merlin()

from merlin import setup, find_packages

setup(
    
    name = 'Exchanger', 
    version = '1.0',

    zip_safe = False,
    packages = find_packages(),
    
    install_requires = [
    'pythia[mpi] >= 0.8.1.0, < 0.8.2a',
    ],

    author = 'Eh Tan',
    author_email = 'cig-mc@geodynamics.org',
    license = 'GPL',
    url = 'http://www.geodynamics.org/cig/software/packages/mc/citcoms/',

)
