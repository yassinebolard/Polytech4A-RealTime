# Pour kill le port 8000/tcp
```bash
fuser -k 8000/tcp
```

# Pour kill un process (le num 17886 par exemple)
```bash
kill -9 17886
```

## Par nom
```bash
pkill tcp-echo-server
```