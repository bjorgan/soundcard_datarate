Calculate mean effective data rate from arecord. Used for
debugging IC9100 in https://www.la1k.no/?p=4219.

Build and Usage instructions
----------------------------

Compilation:

```
mkdir build
cd build
cmake ..
make
```

Run as e.g.

```
arecord -t raw -f FLOAT_LE -r [sample rate] | ./arecord_collector
```

Effective data rates are printed to standard output.
