# Telegram-Data-Clustering

### Build

```
> make
```

### Usage

```
> ./tgnews <option> <source_dir>
```
The `source_dir` should only contain html files or directories, for example:


```
## For all html inside a Sample
> ./tgnews languages ./DataClusteringSample0107/

## Or choise a small sample
> ./tgnews top ./DataClusteringSample0107/20191101/00/
```