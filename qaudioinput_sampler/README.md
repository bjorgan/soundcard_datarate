Pulls data from an QAudioInput and calculates effective datarates. Used for
debugging IC9100 in https://www.la1k.no/?p=4219.

Lightly based on the QAudioInput parts of WSJTX
(https://www.physics.princeton.edu/pulsar/K1JT/wsjtx.html, GPLv3, Joe Taylor,
K1JT).

Build and usage instructions
----------------------------

```
mkdir build
cd build
cmake ..
make
```

Run as

```
./qaudioinput_sampler [sound input device] [sample rate]
```

Prints mean effective data rates to stdout.
