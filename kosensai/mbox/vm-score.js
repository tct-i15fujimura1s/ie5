import Table from "./vm-table.js";

const table = new Table("#score-table");
const keys = "A, ,B,C, ,D, ,E,F, ,G, ,A, ,B,C".split(",");
table.header = keys.map(key => $(`<th class="key-${key==" " ? "black" : "white"}">${key}</th>`)[0]);
table.row = keys.map(key => $(`<td class="key-${key==" " ? "black" : "white"} key-off">●</td>`)[0]);
table.rowMap = row => {
  let freq = 220;
  const list = [];
  for(let cell of row.children) {
    if(cell.classList.contains("key-on")) list.push(freq);
    freq *= 2**(1/12);
  }
  return list;
};

var editMode = false;

const btnEdit = $("#score-button-edit").click(() => {
  if(btnEdit.hasClass("btn-primary")) {
    btnEdit.removeClass("btn-primary").addClass("btn-secondary");
    editMode = true;
  } else {
    btnEdit.addClass("btn-primary").removeClass("btn-secondary");
    editMode = false;
  }
});

$("#score-row-addRow").attr("colspan", table.header.length);

$("#score-button-addRow").click(() => {
  if(!editMode) return;
  for(let i=0; i<5; i++) table.addRow();
});

$("#score-table").
  on("mouseover", "tbody td", function (e) {
    if(!editMode) return;
    const f = e.target;
    if(f.classList.contains("key-off")) $(f).addClass("key-candidate");
  }).
  on("mouseout", "tbody td", function (e) {
    if(!editMode) return;
    const f = e.target;
    if(f.classList.contains("key-off")) $(f).removeClass("key-candidate");
  }).
  on("click", "tbody td", function (e) {
    if(!editMode) return;
    const f = e.target;
    if(f.classList.contains("key-off")) {
      $(f).addClass("key-on").removeClass("key-off");

      console.log(table.get(0));
    } else if(f.classList.contains("key-on")) {
      $(f).addClass("key-off").removeClass("key-on");
    }
  });
