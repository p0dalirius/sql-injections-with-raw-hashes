# SQL injections with raw MD5 hashes

<p align="center">
    List of values that produces SQL injections with their raw hashes values.
    <br>
    <a href="https://twitter.com/intent/follow?screen_name=podalirius_" title="Follow"><img src="https://img.shields.io/twitter/follow/podalirius_?label=Podalirius&style=social"></a>
    <a href="https://www.youtube.com/c/Podalirius_?sub_confirmation=1" title="Subscribe"><img alt="YouTube Channel Subscribers" src="https://img.shields.io/youtube/channel/subscribers/UCF_x5O7CSfr82AfNVTKOv_A?style=social"></a>
    <br>
</p>

> [!NOTE]
> This repository is a proof of concept and improvements or implementation of other hash algorithms is left as an exercise for the reader.

## Features

 - [x] Supports MD5 hashing algorithm.
 - [x] Supports multithreading.

### Results

The repository includes a directory, [`./results/`](./results/), documenting notable findings. 

## Demonstration

```
$ ./bin/hashsqli 
[+] Fuzzer of values that produces SQL injections with their raw hashes values
[+] by @podalirius_ 

[+] File ./found_md5sqli.json already exists, appending new values to it.
[+] Started at : 2024-12-28 15h 41m 55s
[+] Workers : 32
   [>] Starting worker 0 ...
...
   [>] Starting worker 31 ...
[+] Running ...
^C
[+] Preparing for stop ...
   [>] Stopped worker 0.
...
   [>] Stopped worker 31.
[+] Stopped at : 2024-12-28 15h 42m 02s
```

The results are stored in a file in JSON format, line by line, as shown below:

```json
{"value" : "6510162991392070490117810683271182887", "hex" : "84f9316c1da8cac4274f7227357d2c31"}
{"value" : "11437017811074159169486132531026160100", "hex" : "7c4f0b177132171fe8274f52273499df"}
{"value" : "67995529919522538885116708721809890699", "hex" : "258e274f5227343857b7a9e9a529ca4d"}
{"value" : "237246171204506417118698731411430840070", "hex" : "aefc274f722735ebd6cc44c128d9ff64"}
```

Each entry includes:

- `value`: The input string generating the hash.

- `hex`: The hexadecimal representation of the MD5 hash.

## Contributing

Pull requests are welcome. Feel free to open an issue if you want to add other features.
