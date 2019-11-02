import {Tone, Sheet} from "./sheet.js";
export class MBoxPlayer {
  constructor() {
    this.isPlaying = false;
  }

  play() {
    if(!this.sheet) throw new ReferenceError("no sheet set");
    this.stop();

    const ctx = this._ctx = new AudioContext;

    const div = this.sheet.div;
    const type = this.sheet.toneType;
    const detune = this.sheet.detune;

    this.isPlaying = true;

    let time = 0;
    this.sheet.forEach(tones => {
      tones.forEach(tone => {
        const gain = ctx.createGain();
        gain.gain.linearRampToValueAtTime(1, time);
        gain.gain.linearRampToValueAtTime(0.5, time+0.125);
        gain.gain.linearRampToValueAtTime(0, time+1);
        gain.connect(ctx.destination);

        const osc = ctx.createOscillator();
        osc.type = type;
        osc.frequency.value = tone.frequency;
        osc.detune.value = detune;
        osc.connect(gain);
        osc.start(time);
        osc.stop(time+1);
      });
      time += div;
    });
  }

  stop() {
    if(!this.isPlaying) return;
    this.isPlaying = false;
    this._ctx.close();
  }

  get currentTime() {
    return this._ctx.currentTime;
  }
  
  set onended(onended) {
    this._ctx.onended = onended;
  }
}
