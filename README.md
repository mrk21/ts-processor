ts-processor
===========

MPEG-2 Transport Stream processing tools.

Tools
===========

## tssplitter

The tssplitter is a tool which splits the Transport Stream when the video PID and audio PID was changed.

### usage

```bash
$ tssplitter /path/to/input.ts /path/to/output.ts
```

The tssplitter will create files shown below:

```bash
$ ls /path/to
output.ts output1.ts output2.ts ... outputN.ts
```
