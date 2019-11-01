import "./sheet.js";

export class SheetViewer {
  constructor(canvas) {
    this._canvas = canvas;
    this._ctx = canvas.getContext("2d");
    this._height = canvas.height = 10 + 10 * 30; // 1divを10pxで表し、30div分表示する
  }

  set sheet(sheet) {
    if(!sheet) return;
    this._sheet = sheet;
    this._width = this._canvas.width = 10 * sheet.keys.length; // 鍵盤の幅×鍵盤の数

    const colors = ["#ffe", "#555", "#ffe", "#555", "#ffe", "#ffe", "#555", "#ffe", "#555", "#ffe", "#555", "#ffe"];
    for(let i=0; i<sheet.keys.length; i++) {
      this._ctx.fillStyle = colors[sheet.keys[i].tone];
      this._ctx.fillRect(i * 10, 0, 10, 10);
    }
  }

  scroll(time) {
    const sheet = this._sheet;
    const ctx = this._ctx;
    const beginOffsetY = time / sheet.div * 10;
    const countStart = time / sheet.div | 0;
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
}
