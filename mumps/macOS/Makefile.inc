#
#  This file is part of MUMPS 5.9.0, released
#  on Tue Apr 28 13:05:59 UTC 2026
#
################################################################################
#
#   Makefile.inc.generic
#
#   This defines some parameters dependent on your platform; you should
#   look for the approriate file in the directory ./Make.inc/ and copy it
#   into a file called Makefile.inc. For example, from the MUMPS root
#   directory, use 
#   "cp Make.inc/Makefile.inc.generic ./Makefile.inc"
#   (see the main README file for details)
#
#   If you do not find any suitable Makefile in Makefile.inc, use this file:
#   "cp Make.inc/Makefile.inc.generic ./Makefile.inc" and modify it according
#   to the comments given below. If you manage to build MUMPS on a new platform,
#   and think that this could be useful to others, you may want to send us
#   the corresponding Makefile.inc file.
#
################################################################################


########################################################################
#Begin orderings
#
# NOTE that PORD is distributed within MUMPS by default. It is recommended to
# install other orderings. For that, you need to obtain the corresponding package
# and modify the variables below accordingly.
# For example, to have Metis available within MUMPS:
#          1/ download Metis and compile it
#          2/ uncomment (suppress # in first column) lines
#             starting with LMETISDIR,  LMETIS
#          3/ add -Dmetis in line ORDERINGSF
#             ORDERINGSF  = -Dpord -Dmetis
#          4/ Compile and install MUMPS
#             make clean; make   (to clean up previous installation)
#
#          Metis/ParMetis and SCOTCH/PT-SCOTCH (ver 6.0 and later) orderings are recommended.
#

SCOTCHDIR  = /opt/homebrew/opt/scotch
ISCOTCH    = -I$(SCOTCHDIR)/include

#
# You have to choose one among the following two lines depending on
# the type of analysis you want to perform. If you want to perform only
# sequential analysis choose the first (remember to add -Dscotch in the ORDERINGSF
# variable below); for both parallel and sequential analysis choose the second 
# line (remember to add -Dptscotch in the ORDERINGSF variable below)

#LSCOTCH    = -L$(SCOTCHDIR)/lib -lesmumps -lscotch -lscotcherr

LSCOTCH    = -L$(SCOTCHDIR)/lib -lptesmumps -lscotch -lptscotch -lptscotcherr


LPORDDIR = $(topdir)/PORD/lib/
IPORD    = -I$(topdir)/PORD/include/
LPORD    = -L$(LPORDDIR) -lpord$(PLAT)

LMETISDIR = /opt/homebrew/opt/metis/lib
IMETIS    = -I/opt/homebrew/opt/metis/include

# You have to choose one among the following two lines depending on
# the type of analysis you want to perform. If you want to perform only
# sequential analysis choose the first (remember to add -Dmetis in the ORDERINGSF
# variable below); for both parallel and sequential analysis choose the second 
# line (remember to add -Dparmetis in the ORDERINGSF variable below)

LMETIS    = -L$(LMETISDIR) -lmetis
# LMETIS    = -L$(LMETISDIR) -lparmetis -lmetis

# The following variables will be used in the compilation process.
# Please note that -Dptscotch and -Dparmetis imply -Dscotch and -Dmetis respectively.
# If you want to use Metis 4.X or an older version, you should use -Dmetis4 instead of -Dmetis
# or in addition with -Dparmetis (if you are using parmetis 3.X or older).

ORDERINGSF = -Dpord -Dmetis -Dptscotch
#ORDERINGSF  = -Dpord
ORDERINGSC  = $(ORDERINGSF)

LORDERINGS = $(LMETIS) $(LPORD) $(LSCOTCH)
IORDERINGSF = $(ISCOTCH)
IORDERINGSC = $(IMETIS) $(IPORD) $(ISCOTCH)

#End orderings
########################################################################

########################################################################
# DEFINE HERE SOME COMMON COMMANDS, THE COMPILER NAMES, ETC...

# PLAT : use it to add a default suffix to the generated libraries
PLAT    = 
# Suffix for libraries, -soname and -fPIC options, C and Fortran "-o" option
# may be adapted

SONAME = -install_name

# Adapt/uncomment RPATH_OPT to avoid modifying
# LD_LIBRARY_PATH in case of shared libraries

RPATH_OPT = -Wl,-rpath,/Users/jrascon/MUMPS_5.9.0/lib/
LIBEXT  = .a
LIBEXT_SHARED = .dylib
OUTC    = -o 
OUTF    = -o 
# RM : remove files
RM      = /bin/rm -f
# CC : C compiler
CC      = mpicc -fopenmp
# FC : Fortran 90 compiler
FC      = mpifort -fopenmp
# FL : Fortran linker
FL      = mpifort -fopenmp
# AR : Archive object in a library
#      keep a space at the end if options have to be separated from lib name
AR      = ar vr 
# RANLIB : generate index of an archive file
#   (optionnal use "RANLIB = echo" in case of problem)
RANLIB  = ranlib
#RANLIB  = echo

# DEFINE HERE YOUR LAPACK LIBRARY

LAPACK = -framework Accelerate

# SCALAP should define the SCALAPACK and  BLACS libraries.
SCALAP  = -L/opt/homebrew/opt/scalapack/lib -lscalapack

# INCLUDE DIRECTORY FOR MPI
INCPAR  = -I/opt/homebrew/opt/open-mpi/include

# LIBRARIES USED BY THE PARALLEL VERSION OF MUMPS: $(SCALAP) and MPI
LIBPAR  = $(SCALAP) $(LAPACK) -L/opt/homebrew/opt/open-mpi/lib -lmpi

# The parallel version is not concerned by the next two lines.
# They are related to the sequential library provided by MUMPS,
# to use instead of ScaLAPACK and MPI.
INCSEQ  = -I$(topdir)/libseq
LIBSEQ  = $(LAPACK) -L$(topdir)/libseq -lmpiseq$(PLAT)

# DEFINE HERE YOUR BLAS LIBRARY

LIBBLAS = -framework Accelerate

# DEFINE HERE YOUR PTHREAD LIBRARY
LIBOTHERS = -lpthread -fopenmp

# FORTRAN/C COMPATIBILITY:
#  Use:
#    -DAdd_ if your Fortran compiler adds an underscore at the end
#              of symbols,
#     -DAdd__ if your Fortran compiler adds 2 underscores,
#
#     -DUPPER if your Fortran compiler uses uppercase symbols
#
#     leave empty if your Fortran compiler does not change the symbols.
#

CDEFS = -DAdd_

#COMPILER OPTIONS
OPTF    = -O -fPIC -fopenmp -fallow-argument-mismatch
OPTC    = -O -I. -fPIC -fopenmp
OPTL    = -O -fPIC -dynamiclib -fopenmp

# CHOOSE BETWEEN USING THE SEQUENTIAL OR THE PARALLEL VERSION.

#Sequential:
#INCS = $(INCSEQ)
#LIBS = $(LIBSEQ)
#LIBSEQNEEDED = libseqneeded

#Parallel:
INCS = $(INCPAR)
LIBS = $(LIBPAR)
LIBSEQNEEDED = 

