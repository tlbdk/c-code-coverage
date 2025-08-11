# c-code-coverage
Example repo that show how to generate code coverage in C

## MacOS

``` bash
brew install lcov
```

## Linux
``` bash
apt install build-essential # Be able to compile c code
apt install lcov
```

## Build with coverage
``` bash
cd src
make cov
```

## VSCode

[coverage-gutters](https://marketplace.visualstudio.com/items?itemName=ryanluker.vscode-coverage-gutters)

![Alt text](./img/vscode-coverage.png)

