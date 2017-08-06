const fs = require('fs');
const readline = require("readline");
const chalk = require("chalk");
const ConnvertRomanNumeral = require("./lib/ConvertRomanNumeral");

let converter = new ConnvertRomanNumeral();

// for (let i=1; i<=3000; i++){
//   let roman = converter.fromArabicToRoman(i);
//   // console.log(i+','+roman);
//   console.log(roman+','+i);
// }

var argv = require("yargs")
  .usage("Usage: $0  [options]")
  // .example('$0 count -f foo.js', 'count the lines in the given file')
  .alias("i", "interactive")
  .alias("f", "file")
  .nargs("f", 1)
  .describe("i", "run in interactive mode")
  .help("h")
  .alias("h", "help")
  .epilog("Filscentia/roman-numerals").argv;

// set the prompt
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
    line = line.trim();
    let val = parseInt(line);
    if (isNaN(val)) {
      console.log(converter.fromRomanToArabic(line.toUpperCase()));
    } else {
      console.log(converter.fromArabicToRoman(val));
    }
    rl.prompt();
  });

  rl.on("close", function() {
    console.log(chalk.green("\nGood bye!"));
    process.exit(0);
  });
} else {
  rl = readline.createInterface({
    input: fs.createReadStream(argv["f"]),
    output: process.stdout,
    terminal: false
  });
  // when a line has been entered by the user
  rl.on("line", function(line) {
    // check if its numbers or a string
    line = line.trim();
    let val = parseInt(line);
    if (isNaN(val)) {
      console.log(line + "," + converter.fromRomanToArabic(line.toUpperCase()));
    } else {
      console.log(line + "," + converter.fromArabicToRoman(val));
    }
    // rl.prompt();
  });

  rl.on("close", function() {
    // console.log(chalk.green("\nGood bye!"));
    process.exit(0);
  });
}
