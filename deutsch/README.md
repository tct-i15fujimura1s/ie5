# ドイツ語

<input type="hidden" id="url" value="{{ page.url }}">
## Index of {{ page.url }}
<ul id="dirs">
</ul>

<script>
  const dirs = document.querySelector("#dirs");
  const url = document.querySelector("#url");
  fetch("https://api.github.com/repos/tct-i15fujimura1s/ie5/contents" + url.value, {mode: "cors"})
  .then(res => res.json())
  .then(entries => entries.forEach(entry => {
    const li = document.createElement("li");
    {
      const a = document.createElement("a");
      a.textContent = a.href = entry.name;
      li.appendChild(a);
    }
    dirs.appendChild(li);
  }));
</script>
