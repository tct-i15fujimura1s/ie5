# IE5
* https://tct-i15fujimura1s.github.io/ie5/
* Apr., 2019 .. Mar., 2020


## Index of /
<ul id="dirs">
</ul>

<script>
  const dirs = document.querySelector("#dirs");
  fetch("https://api.github.com/repos/tct-i15fujimura1s/ie5/contents/", {mode: "cors"})
  .then(res => res.json())
  .then(entries => entries.forEach(entry => {
    if(~"_.".indexOf(entry.name[0])) return;
    const li = document.createElement("li");
    {
      const a = document.createElement("a");
      a.textContent = a.href = entry.name;
      li.appendChild(a);
    }
    dirs.appendChild(li);
  }));
</script>
