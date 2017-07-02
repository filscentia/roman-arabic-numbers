

class ConvertRomanNumeral {

    /**
     * Setups up the key constants
     */
    constructor() {
        this.VALUES = {
            "E": 0,    // spceial marker to make the algorthim simpler
            "I": 1,
            "V": 5,
            "X": 10,
            "L": 50,
            "C": 100,
            "D": 500,
            "M": 1000
        };

        this.SETS = {
            1 : {'high': 'X','mid':'V','low':'I'},
            10: {'high': 'C','mid':'L','low':'X'},
            100:{'high': 'M','mid':'D','low':'C'}
        }

    }

    /**
     * Utility method to create a simple string for a single number
     * 
     * @param {int} num 
     * @param {String} high 
     * @param {String} mid 
     * @param {String} low 
     */
    getSingleRomanNumeral(num, symbols) {
        let s = [];

        if (num === 9) {
            s.push(symbols.low, symbols.high);
        } else if (num === 4) {
            s.push(symbols.low,  symbols.mid);
        } else if (num >= 5) {
            s.push(symbols.mid, symbols.low.repeat(num - 5));
        } else {
            s.push(symbols.low.repeat(num));
        }
        return s.join('');
    }

    /**
     * Public API to convert from a integer to a String form
     * 
     * @param {int} number 
     */
    fromArabicToRoman(number) {
        let i = number;
        let roman = [];
       
        let thousands = Math.floor(i / 1000);
        i -= (thousands * 1000);
        let hundreds = Math.floor(i / 100);
        i -= hundreds * 100;
        let tens = Math.floor(i / 10);
        i -= tens * 10;
        let units = i;

        roman.push('M'.repeat(thousands));
        roman.push(this.getSingleRomanNumeral(hundreds, this.SETS[100]));
        roman.push(this.getSingleRomanNumeral(tens,  this.SETS[10]));
        roman.push(this.getSingleRomanNumeral(units, this.SETS[1]));
       
        return roman.join('');
    }

    /**
     * Public API to return the int of the String Roman numeral 
     * 
     * @param {String} roman_number 
     */
    fromRomanToArabic(roman_number) {

        let result = 0;
        let chars = roman_number.split('');
        chars.push('E');
        let len = chars.length;
       
        for (let i = len - 2; i >= 0; i--) {
            let lastValue = this.VALUES[chars[i + 1]];
            let thisValue = this.VALUES[chars[i]];
       
            if (thisValue < lastValue) {
                result -= thisValue;
            } else {
                result += thisValue;
            }
        }
        return result;
    }
}

module.exports = ConvertRomanNumeral;
