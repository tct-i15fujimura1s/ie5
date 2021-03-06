import {Sheet, Tone} from "./sheet.js";

export class SheetEditor {
  constructor(eSheet, eBG) {
    this._eSheet = eSheet;
    this._eBG = eBG;
    this._cSheet = eSheet.getContext("2d");
    this._cBG = eBG.getContext("2d");
    this._height = eSheet.height = eBG.height = 10 + 10 * 30; // 1divを10pxで表し、30div分表示する
    this._prevHL = null;
    this.loaded = false;
    this._timeCount = 0;
  }

  set sheet(sheet) {
    this._sheet = sheet;
    this.loaded = false;
    if(!sheet) return;
    this.loaded = true;
    this._width = this._eSheet.width = this._eBG.width = 10 * sheet.keys.length; // 鍵盤の幅×鍵盤の数

    const colors = ["#ffe", "#555", "#ffe", "#555", "#ffe", "#ffe", "#555", "#ffe", "#555", "#ffe", "#555", "#ffe"];
    for(let i=0; i<sheet.keys.length; i++) {
      this._cBG.fillStyle = colors[sheet.keys[i].tone];
      this._cBG.fillRect(i * 10, 0, 10, 10);
    }
  }

  get sheet() {
    return this._sheet;
  }

  get div() {
    return this._sheet.div;
  }

  get currentTime() {
    return this._timeCount*this._sheet.div;
  }

  set currentTime(time) {
    if(time < 0) time = 0;
    this._timeCount = time/this._sheet.div;
    this.scroll(time);
  }

  scroll(time) {
    if(!this.loaded) return;
    this.paint();
    this.rehighlight();
  }

  paint() {
    const sheet = this._sheet;
    const ctx = this._cSheet;
    const time = this._timeCount;
    const beginOffsetY = time * 10;
    const countStart = time | 0;
    const countEnd = countStart + 30;
    const numberBegin = sheet.keys[0].number;
    ctx.clearRect(0, 10, this._width, this._height-10);
    ctx.fillStyle = "rgba(0, 0, 0, 0.5)";
    for(let i=countStart; i<=countEnd; i++) {
      const row = sheet.get(i);
      if(!row) continue;
      const y = 10 + i * 10 - beginOffsetY;
      row.forEach(tone => {
        const x = (tone.number - numberBegin) * 10;
        const realY = Math.max(10, y);
        const realH = Math.max(0, y+2-realY);
        ctx.fillRect(x+2, realY, 8, realH);
      });
    }
  }

  rehighlight() {
    const ctx = this._cBG;
    ctx.clearRect(0, 10, this._width, this._height-10);
    if(!this._prevHL) return;
    const {time, tone} = this._prevHL;
    const y = (time-this._timeCount)*10+10;
    const x = tone*10;
    ctx.fillStyle = "rgba(150, 255, 0, 0.25)";
    ctx.fillRect(x, 10, 10, this._height-10);
    ctx.fillStyle = "rgba(255, 150, 0, 0.25)";
    ctx.fillRect(0, y, this._width, 10);
  }

  highlight(time, tone) {
    if(time<0) return;
    if(this._prevHL && this._prevHL.time==time && this._prevHL.tone==tone) return;
    this._prevHL = {time, tone};
    this.rehighlight();
  }

  noteAt(x, y) {
    return {
      time: Math.floor((y-10)*0.1+this._timeCount),
      tone: Math.floor(x*0.1)
    };
  }

  hightlightAt(x, y) {
    if(y<=10) return;
    const note = this.noteAt(x, y);
    this.highlight(note.time, note.tone);
  }

  highlightNone() {
    this._prevHL = null;
    this.rehighlight();
  }

  putAt(x, y) {
    const note = this.noteAt(x, y);
    const number = note.tone+this._sheet.keys[0].number;
    const tones = this._sheet.get(note.time) || this._sheet.set(note.time, []);
    const index = tones.findIndex(tone => tone.number == number);
    if(~index) tones.splice(index, 1);
    else {
      tones.push(Tone.fromNumber(number));
      // play sound
    }
    this.paint();
  }
}
