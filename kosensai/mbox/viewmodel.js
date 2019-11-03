import {Sheet} from "./sheet.js";
import {SheetViewer} from "./sheet-viewer.js";
import {SheetEditor} from "./sheet-editor.js";
import {MBoxPlayer} from "./mbox-player.js";

// elements
const eSong = $("#song");
const eSheetViewer = $("#sheet-viewer");
const eSheetEditor = $("#sheet-editor");
const eBGEditor = $("#bg-editor");
const eBtnPlay = $("#button-play");
const eBtnImport = $("#button-import");
const eBtnEdit = $("#button-edit");
const eBtnEditUp = $("#button-edit-up");
const eBtnEditDn = $("#button-edit-down");
const eBtnEditExport = $("#button-edit-export");
const eRowViewer = $("#row-viewer");
const eRowEditor = $("#row-editor");

const viewer = new SheetViewer(eSheetViewer[0]);
const editor = new SheetEditor(eSheetEditor[0], eBGEditor[0]);
const player = new MBoxPlayer();


// init
eRowEditor.hide();

fetch("./songs.json").then(res => res.json()).then(json => {
  for(let key in json) $("<option>").val(json[key]).text(key).appendTo(eSong);
});

eSong.change(() => loadSong(eSong.val()));

eBtnPlay.click(() => togglePlaying());

eBtnEdit.click(() => toggleEditing());

eBtnImport.click(() => {
  const eInputFile = $("<input type=file>")[0];
  eInputFile.onchange = () => {
    const file = eInputFile.files[0];
    const url = URL.createObjectURL(file);
    $("<option>").val(url).text(file.name).appendTo(eSong);
    eSong.val(url).change();
  };
  eInputFile.click();
});

eSheetEditor
  .mousemove(e => editor.hightlightAt(e.offsetX, e.offsetY))
  .mouseout(() => editor.highlightNone())
  .click(e => editor.putAt(e.offsetX, e.offsetY));

eBtnEditUp.click(() => { editor.currentTime -= editor.div; });
eBtnEditDn.click(() => { editor.currentTime += editor.div; });

eBtnEditExport.click(() => {
  const blob = new Blob([editor.sheet.toString()], {type: "text/plain"});
  const eA = $("<a download=mbox.txt>")[0];
  eA.href = URL.createObjectURL(blob);
  eA.click();
});

player.sheet = viewer.sheet = new Sheet();


// functions
let isLoaded = false;
function loadSong(file){
  if(!file) return;
  unloadSong();
  return fetch(file).then(res => res.text()).then(text => {
    console.log("Loaded: %s", file);
    const sheet = Sheet.fromString(text);
    viewer.sheet = player.sheet = sheet;
    eBtnPlay.prop("disabled", false);
    stop();
    isLoaded = true;
    viewer.scroll(0);
  });
}

function unloadSong() {
  isLoaded = false;
  eBtnPlay.prop("disabled", true);
  viewer.sheet = player.sheet = null;
}


let isPlaying = false;
function togglePlaying() {
  if(isPlaying) stop();
  else play();
}

let timer;
function play() {
  if(!isLoaded) return;
  player.play();
  timer = setInterval(() => {
    viewer.scroll(player.currentTime);
  }, player.sheet.div/10 * 1000);
  eBtnPlay.text("停止");
  isPlaying = true;
}

function stop() {
  player.stop();
  clearInterval(timer);
  eBtnPlay.text("再生");
  isPlaying = false;
}


let isEditing = false;
function toggleEditing() {
  if(isEditing) closeEditor();
  else openEditor();
  isEditing = !isEditing;
}

function openEditor() {
  eBtnEdit.text("編集を終了");
  eBtnPlay.prop("disabled", true);
  stop();
  eRowViewer.hide();
  editor.sheet = player.sheet;
  editor.scroll(0);
  eRowEditor.show();
}

function closeEditor() {
  eBtnEdit.text("編集");
  eBtnPlay.prop("disabled", false);
  eRowEditor.hide();
  viewer.sheet = player.sheet = editor.sheet;
  viewer.scroll(0);
  eRowViewer.show();
}
