import {Sheet} from "./sheet.js";
import {SheetViewer} from "./sheet-viewer.js";
import {MBoxPlayer} from "./mbox-player.js";

const eSheet = $("#sheet");
const eBtnPlay = $("#button-play");
const eBtnLoad = $("#button-load");
const editor = new SheetViewer(eSheet[0]);
const player = new MBoxPlayer();

let isLoaded = false;
function loadSong(file){
  eBtnLoad.text("読込中…");
  unloadSong();
  return fetch(file).then(res => res.text()).then(text => {
    console.log("Loaded: %s", file);
    const sheet = Sheet.fromString(text);
    editor.sheet = player.sheet = sheet;
    isLoaded = true;
    eBtnPlay.prop("disabled", false);
    eBtnLoad.prop("disabled", false).text("選択");
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

$("#button-load").click(() => loadSong($("#song").val()));

let isPlaying = false;
$("#button-play").click(() => {
  if(isPlaying) stop();
  else play();
});
