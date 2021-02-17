### LIBMBD AND PYMBD IN INTEL ENVIRONMENT (ON IRIS) ###


*~~~~~~~~~~~~~~~~~~~~~*
*~  GETTING STARTED  ~*
*~~~~~~~~~~~~~~~~~~~~~*

create and enter virtual environment::

  virtualenv venv-pymbd
  source venv-pymbd/bin/activate

install basic requirements::

  pip install --upgrade pip cmake cffi mpi4py

clone libmbd::

  git clone https://github.com/jhrmnn/libmbd.git
or::
  git clone https://github.com/martin-stoehr/libmbd.git



*~~~~~~~~~~~~~~~~~~*
*~  BUILD LIBMBD  ~*
*~~~~~~~~~~~~~~~~~~*

- create and enter build directory::

  cd libmbd && mkdir _build && cd _build

- configure for intel environment::

  FC=mpiifort cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_Fortran_COMPILER=ifort -DCMAKE_C_COMPILER=icc -DCMAKE_CXX_COMPILER=icpc -DMPI_Fortran_COMPILER=mpiifort -DENABLE_SCALAPACK_MPI=ON -DSCALAPACK_LIBRARIES="${MKLROOT}/lib/intel64/libmkl_scalapack_lp64.so;-Wl,--start-group;${MKLROOT}/lib/intel64/libmkl_intel_lp64.so;${MKLROOT}/lib/intel64/libmkl_sequential.so;${MKLROOT}/lib/intel64/libmkl_core.so;${MKLROOT}/lib/intel64/libmkl_blacs_intelmpi_lp64.so;-Wl,--end-group" -DLAPACK_LIBRARIES="-Wl,--start-group;${MKLROOT}/lib/intel64/libmkl_intel_lp64.so;${MKLROOT}/lib/intel64/libmkl_sequential.so;${MKLROOT}/lib/intel64/libmkl_core.so;-Wl,--end-group" -DCMAKE_EXE_LINKER_FLAGS="-lpthread -qopenmp -lm -ldl" -DCMAKE_Fortran_FLAGS="-qopenmp" -DCMAKE_INSTALL_PREFIX=$(pwd)

- build and install::

  make && make install; cd ..

- *if* the top-level directory only contains the directory lib64 and not lib::

  ln -s $(pwd)/lib64/ $(pwd)/lib



*~~~~~~~~~~~~~~~~~~~*
*~  INSTALL PYMBD  ~*
*~~~~~~~~~~~~~~~~~~~*

- set non-default installation path of libmbd::

  export LIBMBD_PREFIX=$(pwd)

- install using ``pip``::

  FC=mpiifort CC=icc pip install -U pymbd[mpi]

- *On Iris*, the Python-C API only works with the below for some reason::

  export LD_PRELOAD=$MKLROOT/lib/intel64/libmkl_rt.so

*NOTE:* This has to be set every time you want to use the Fortran code!

- When compiled with MPI extensions, the Fortran code doesn't allow for standard execution. When trying to use the Fortran library (pymbd.fortran), you need to run your script through an MPI wrapper, e.g.::

  srun -n 1 python my_pymbd_script.py

