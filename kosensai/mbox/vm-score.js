import Table from "./vm-table.js";

const table = new Table("#score-table");
const keys = "A, ,B,C, ,D, ,E,F, ,G, ,A, ,B,C".split(",");
table.header = keys.map(key => $(`<th class="key-${key==" " ? "black" : "white"}">${key}</th>`)[0]);
table.row = keys.map(key => $(`<td class="key-${key==" " ? "black" : "white"} key-off">●</td>`)[0]);


$("#score-row-addRow").attr("colspan", table.header.length);

$("#score-button-addRow").click(() => {
  for(let i=0; i<5; i++) table.addRow();
});

$("#score-table").
  on("mouseover", "tbody td", function (e) {
    const f = e.target;
    if(f.classList.contains("key-off")) $(f).addClass("key-candidate");
  }).
  on("mouseout", "tbody td", function (e) {
    const f = e.target;
    if(f.classList.contains("key-off")) $(f).removeClass("key-candidate");
  }).
  on("click", "tbody td", function (e) {
    const f = e.target;
    if(f.classList.contains("key-off")) {
      $(f).addClass("key-on").removeClass("key-off");
    } else if(f.classList.contains("key-on")) {
      $(f).addClass("key-off").removeClass("key-on");
    }
  });

const btnEdit = $("#score-button-edit");
