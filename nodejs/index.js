
const ConnvertRomanNumeral = require('./lib/ConvertRomanNumeral');

let converter = new ConnvertRomanNumeral();

for (let i = 1; i <= 11; i++) {
    console.log(i + '=' + converter.fromArabicToRoman(i));
}