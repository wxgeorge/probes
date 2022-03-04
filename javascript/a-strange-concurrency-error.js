#!/usr/bin/env node

const fs = require('fs')

// running this program will create some directories.
// we'll work in the ./tmp folder, creating if necessary
let workDir = './tmp'
if(!fs.existsSync(workDir)) {
  console.log(`Need a workspace. ${workDir} provided but does not exist. Creating.`)
  fs.mkdirSync(workDir)
}

// we'll also create a separate "session" folder for each run.
let sessionPrefix = Buffer.from(Math.random().toString()).toString("base64").substr(10,10)
workDir = `${workDir}/${sessionPrefix}`
fs.mkdirSync(workDir)
console.log(`Prefix for this download session is ${sessionPrefix}. I.e. working directory is now ${workDir}`)

// here's where the fun beings
let range = [ 1, 2, 3 ]

return Promise.all(
  range.map(i => {
    let = downloadDir = `${workDir}/${i}`

    console.log(`pre fs.promises.mkdir(${i}), downloadDir=${downloadDir}`)
    return fs.promises.mkdir(downloadDir)
      .then(() => {
        console.log(`POST fs.promises.mkdir(${i}), downloadDir=${downloadDir}`)
        return downloadDir
      })

  })
)
  .then(paths => {
    // Think about what the value of paths will be?
    console.log(`All directories successfully! Paths are ${paths}`)
    return paths
  })
