# redmond-grep

![grep CI](https://github.com/<YOUR_USERNAME>/<YOUR_REPO>/actions/workflows/ci.yml/badge.svg)

A simple `grep` clone written in C supporting:

- `-i` ignore case
- `-n` show line numbers
- `-E` extended regex
- `--help` display help
- `--version` show version

## Build

```sh
make
```

## Install

```sh
sudo make install
```

## Usage

```sh
./grep [OPTIONS] pattern [file...]
```

## Examples

```sh
./grep -i "hello" file.txt
./grep -n "pattern" file1.txt file2.txt
./grep -E "foo|bar" file.txt
```
