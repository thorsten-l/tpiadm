# tpiadm
A simple TuringPi V1 slot administration tool.

## See also
- [ESP8266 Turing Pi WiFi Controller](https://github.com/thorsten-l/ESP8266-TuringPi-WiFi-Controller) - a WiFi Controller for the Turing Pi V1 cluster board connected via the onboard I2C bus.

## Binary

Find a precompiled static binary at the [`bin/`](https://github.com/thorsten-l/tpiadm/tree/main/bin) directoy or at the [Releases](https://github.com/thorsten-l/tpiadm/releases) page.

- Compiled with Rasberry PI OS (buster, 32Bit)

## Documentation
- [Turing Pi V1 - Cluster Management Bus (i2c)](https://docs.turingpi.com/cluster-management-bus-i2c)

## Usage
```text
Usage: tpiadm [OPTION...]
tpiadm -- TuringPi V1 slot administration tool.

  -i, --info                 show slots info
  -n, --slot=SLOT-ID         slot number (1-7)
  -p, --power=POWER          power 0=OFF, 1=ON
  -s, --set                  set slot power mode
  -v, --verbose              verbose output
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.

Report bugs to <t.ludewig@gmail.com>.
```

## Sample

### get info

```text
tpiadm -i
slot 1 ON installed
slot 2 ON installed
slot 3 ON installed
slot 4 ON installed
slot 5 ON installed
slot 6 ON installed
slot 7 OFF -
```

### Power on slot 7

```text
tpiadm -s -n 7 -p 1
slot #7 power ON
```

or

```text
tpiadm --set --slot=7 --power=1
slot #7 power ON
```
