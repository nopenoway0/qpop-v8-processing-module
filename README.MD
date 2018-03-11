# QPOP Processing Module

This module uses Google's V8 engine to create bindings that allow an application with javascript frontend to perform several specific functions with high performance

## Requirements
* NodeJS
* node-gyp - install using `npm install node-gyp` for a local installation or `npm install --global node-gyp` for global. If using local, the following command will run node-gyp from the base directory: `node node_modules/node-gyp/bin/node-gyp.js`

## Compiling
To compile for electron run the following commands:
* `node-gyp rebuild --target=1.8.0 --arch=x64 --dist-url=https://atom.io/download/electron`