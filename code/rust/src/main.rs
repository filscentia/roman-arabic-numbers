
use clap::Parser;
use regex::Regex;
use std::collections::HashMap;

#[derive(Parser)]
struct Args {
    command: String,
    path:  std::path::PathBuf,
}


struct RomanSet {
    upper: String,
    mid: String,
    lower: String,
}

struct Converter {
    values: HashMap<char,i32>,
    set_units: RomanSet,
    set_tens: RomanSet,
    set_hundreds: RomanSet,
    lines: String,
}

impl Converter{
    fn new(s: String)-> Converter {
        Converter {
            values: HashMap::from([
                ('I',1),
                ('V',5),
                ('X',10),
                ('L',50),
                ('C',100),
                ('D',500),
                ('M',1000),
                ('_',0),
            ]),
            set_units: RomanSet{upper:"X".to_string(),mid:"V".to_string(),lower:"I".to_string()},
            set_tens: RomanSet{upper:"C".to_string(),mid:"L".to_string(),lower:"X".to_string()},
            set_hundreds: RomanSet{upper:"M".to_string(),mid:"D".to_string(),lower:"C".to_string()},
            lines:s,
        }
    }

    fn get_roman_numeral(self:&Converter, i: usize,symbols: &RomanSet)-> String {
        if 9 == i {
          return format!("{}{}",symbols.lower,symbols.upper);
        } else if i ==4 {
            return format!("{}{}",symbols.lower,symbols.mid);
        } else if i >=5 {
            return format!("{}{}",symbols.mid,symbols.lower.repeat(i-5));
        }else {
            return symbols.lower.repeat(i);
        }
    }

    fn from_arabic_to_roman(self:&Converter,s: String) -> String{       
        let mut i = s.parse::<usize>().unwrap();
    
        let thousands = i / 1000;
        i -= thousands * 1000;
        let hundreds = i / 100;
        i -= hundreds * 100;
        let tens = i / 10;
        i -= tens * 10;
    
        let units = i;
    
        let h = self.get_roman_numeral(hundreds, &self.set_hundreds);
        let t = self.get_roman_numeral(tens, &self.set_tens);
        let u = self.get_roman_numeral(units, &self.set_units);
        return format!("{}{}{}{}","M".repeat(thousands),h,t,u);
        
    }

    fn from_roman_to_arabic(self:&Converter,s: String)-> i32 {
        let r = format!("{}",s.to_uppercase());
        let mut result=0;
        let chars = r.chars().rev();

        let mut previous_value=0;

        for c in chars {
            let this_value = self.values.get(&c).unwrap();
            // println!("{} {}  {} {} {}",i,c,this_value,previous_value,result);
            if this_value < &previous_value {
                result -= this_value;
            } else {
                result += this_value;
            }

            previous_value = this_value.clone();
        }

        return result;
    }

    fn process(self:&Converter){
        let arabic_regex = Regex::new(r"^[0-9]+").unwrap();
        let roman_regex = Regex::new(r"^[MDCLXVImdclxvi]+").unwrap();
    
        println!("--START--");
        for line in self.lines.lines() {
            if roman_regex.is_match(line) {
                let r = self.from_roman_to_arabic(line.to_string());
                println!("{},{}",line,r);
            } else if arabic_regex.is_match(line){
                let r = self.from_arabic_to_roman(line.to_string());
                println!("{},{}",line,r);
            } else {
                println!("{},ERROR",line);
            }
            
        }
        println!("--END--");
    }

}

fn main() {    


    let args = Args::parse();

    let content = std::fs::read_to_string(&args.path).expect("Could not read file");


    let converter = Converter::new(content);

    converter.process();

}


