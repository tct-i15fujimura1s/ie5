import {Sheet} from "./sheet.js";
import {SheetViewer} from "./sheet-viewer.js";
import {MBoxPlayer} from "./mbox-player.js";

const eSong = $("#song");
const eSheet = $("#sheet");
const eBtnPlay = $("#button-play");
const eBtnEdit = $("#button-edit");
const editor = new SheetViewer(eSheet[0]);
const player = new MBoxPlayer();

fetch("./songs.json").then(res => res.json()).then(json => {
  for(let key in json) $("<option>").val(json[key]).text(key).appendTo(eSong);
});

let isLoaded = false;
function loadSong(file){
  if(!file) return;
  unloadSong();
  return fetch(file).then(res => res.text()).then(text => {
    console.log("Loaded: %s", file);
    const sheet = Sheet.fromString(text);
    editor.sheet = player.sheet = sheet;
    isLoaded = true;
    eBtnPlay.prop("disabled", false);
    stop();
  });
}

function unloadSong() {
  eBtnPlay.prop("disabled", true);
  isLoaded = false;
  editor.sheet = player.sheet = null;
}

let timer;
function play() {
  if(!isLoaded) return;
  eBtnPlay.text("停止");
  player.play();
  timer = setInterval(() => {
    editor.scroll(player.currentTime);
  }, sheet.div/10 * 1000);
  isPlaying = true;
}

function stop() {
  eBtnPlay.text("再生");
  player.stop();
  clearInterval(timer);
  isPlaying = false;
}

eSong.change(() => loadSong(eSong.val()));

let isPlaying = false;
$("#button-play").click(() => {
  if(isPlaying) stop();
  else play();
});
