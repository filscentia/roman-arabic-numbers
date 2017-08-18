
'use strict'
var chalk = require('chalk');
var fs  = require('fs');
var path= require('path');
var pretty = require('prettyjson');


console.log(chalk.blue.bold('Roman-Arabic numeral programs available:\n'));

let apps = fs.readdirSync('./_general');
apps.forEach(function(entry) {
    
	var possiblePackage = path.resolve('./_general',entry,'package.json');
	
	if (fs.existsSync(possiblePackage)){
	    var packagejson = require(possiblePackage);
        var relativeDir = path.relative('',path.parse(possiblePackage).dir);
        var sampleapp = { 'Directory': path.relative('',path.parse(possiblePackage).dir),
                          'Name':packagejson.name,
                          'Description':packagejson.description,
                          'Interactive Command': chalk.yellow('cd '+relativeDir+' && '+packagejson.scripts.interactive),
                          'Author':packagejson.author,
                          'Keywords':packagejson.keywords  
         }



	    console.log(pretty.render(sampleapp));
	    console.log('\n');
	}
});