export class Tone {
  static toneFromName(str) {
    let shift = 0;
    if("-" == str[1] || "♭" == str[1]) shift = -1;
    else if("+" == str[1] || "#" == str[1] || "♯" == str[1]) shift = 1;
    switch(str[0]) {
      case "c": case "C": return shift;
      case "d": case "D": return shift+2;
      case "e": case "E": return shift+4;
      case "f": case "F": return shift+5;
      case "g": case "G": return shift+7;
      case "a": case "A": return shift+9;
      case "b": case "B": return shift+11;
      default: return NaN;
    }
  }

  static fromString(str) {
    const match = str.match(/([a-g][-+#♯♭]?)(\d+)?/i);
    if(!match) throw new TypeError("not a valid tone string");
    const tone = Tone.toneFromName(match[1]);
    const octave = isFinite(match[2]) ? +match[2] : 3;
    return new Tone(octave, tone);
  }

  static fromNumber(n) {
    return new Tone(n/12|0, n%12);
  }

  constructor(octave, tone) {
    if(!isFinite(octave)) throw new TypeError("octave isn't finite");
      if(!isFinite(tone)) throw new TypeError("tone isn't finite");
    this.octave = +octave;
    this.tone = +tone;
  }

  get frequency() {
    return 55 * 2**this.octave * 2**(this.tone/12);
  }

  get number() {
    return 12 * this.octave + this.tone;
  }

  toString() {
    const names = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"];
    return names[this.tone] + this.octave;
  }
}

export class Sheet {
  static fromString(str, keys = Sheet.keys72(), div = -1) {
    let match;
    if(div<0 && (match = str.match(/;!tempo\s+(\d+)/im))) {
      div = 60/+match[1];
    }
    let toneType = "triangle";
    if(match = str.match(/;!toneType\s*(\w+)/im)) {
      toneType = match[1];
    }
    let detune = 0;
    if(match = str.match(/;!detune\s*(\d+)/im)) {
      detune = +match[1];
    }
    const sheet = new Sheet(keys, div, toneType, detune);
    str.replace(/\n*;[^\n]*/g, "").split(/\n/).forEach(row =>
      sheet.add(...(row.match(/[a-g][-+#♯♭]?\d*/gi) || []).map(Tone.fromString)));
    return sheet;
  }

  static keysInRange(beginTone, endTone) {
    const keys = [];
    const begin=beginTone.number, end=endTone.number;
    for(let i=begin; i<=end; i++) keys.push(Tone.fromNumber(i));
    return keys;
  }

  static keys72() {
    return this.keysInRange(new Tone(1, 0), new Tone(6, 11));
  }

  constructor(keys = Sheet.keys72(), div = 1, toneType = "triangle", detune = 0) {
    this.keys = keys;
    this.div = div;
    this._array = [];
    this.toneType = toneType;
    this.detune = 0;
  }

  add(...tones) {
    this._array.push(tones);
  }

  get(index) {
    return this._array[index];
  }

  forEach(consumer, context = null) {
    this._array.forEach(consumer, context);
  }
}
