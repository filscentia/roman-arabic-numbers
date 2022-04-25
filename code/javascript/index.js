const fs = require("fs");
const readline = require("readline");
const chalk = require("chalk");
const ConvertRomanNumeral = require("./lib/ConvertRomanNumeral");

let converter = new ConvertRomanNumeral();

var argv = require("yargs")
  .usage("Usage: $0  [options]")
  // .example('$0 count -f foo.js', 'count the lines in the given file')
  .alias("i", "interactive")
  .alias("f", "file")
  .nargs("f", 1)
  //.demand(1)
  .describe("i", "Run in interactive mode")
  .describe("f", "File to load the input from")
  .help("h")
  .alias("h", "help")
  .epilog("Filscentia/roman-numerals").argv;

if (argv.i) {
  rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    terminal: true
  });

  rl.setPrompt(chalk.yellow("roman-numerals > "));
  rl.prompt();

  // when a line has been entered by the user
  rl.on("line", function(line) {
    // check if its numbers or a string
    console.log(converter.process(line));
    rl.prompt();
  });

  rl.on("close", function() {
    console.log(chalk.green("\nGood bye!"));
    process.exit(0);
  });
} else if (argv.f) {

  console.log("--START--");
  rl = readline.createInterface({
    input: fs.createReadStream(argv["f"]),
    output: process.stdout,
    terminal: false
  });

  // when a line has been entered by the user
  rl.on("line", function(line) {
    const converted = converter.process(line)
    console.log(`${line},${converted},${line.length},${converted.length},${line.length/converted.length}` );
  });

  rl.on("close", function() {
    console.log("--END--");
    process.exit(0);
  });
} else {
  console.log(chalk.red("\nWrong options specified"));
  process.exit(-1);
}
