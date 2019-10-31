export default class {
  constructor(selector) {
    this._e = $(selector);
    this._header = [];
    this._thead = $("<thead>").appendTo(this._e);
    this._tbody = $("<tbody>").appendTo(this._e);

    this.row = [];
    this.rowMap = row => row;
  }

  get header() { return this._header; }
  set header(fs) {
    const tr = $("<tr>").appendTo(this._thead.empty());
    fs.forEach(f => {
      const node = (f instanceof Node) ? f : $("<th>").append(f);
      tr.append(node);
    });
    this._header = fs;
  }

  get length() {
    return this._tbody.children.length;
  }

  get(index) {
    return Array.from(this._tbody.children).map(this.rowMap);
  }

  addRow() {
    const tr = $("<tr>");
    this.row.forEach(item => {
      const clone =
        (item instanceof Node)
          ? item.cloneNode(true)
          : item;
      const node = (clone instanceof Node) ? clone : $("<td>").append(clone);
      tr.append(node);
    });
    tr.appendTo(this._tbody);
  }
}
