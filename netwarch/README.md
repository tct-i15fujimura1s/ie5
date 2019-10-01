# ネットワークアーキテクチャ
<input type="hidden" id="url" value="{{ page.url }}">
## Index of {{ page.url }}
<ul id="dirs">
</ul>

<script>
  const dirs = document.querySelector("#dirs");
  const url = document.querySelector("#url");
  const base = "https://api.github.com/repos/tct-i15fujimura1s/ie5/contents";
  fetch(base + url.value, {mode: "cors"})
  .then(res => res.json())
  .then(entries => entries.forEach(entry => {
    const li = document.createElement("li");
    {
      const a = document.createElement("a");
      const match = /^(.+?)\.md$/.exec(entry.name);
      a.textContent = a.href = match ? match[1] : entry.name;
      li.appendChild(a);
    }
    dirs.appendChild(li);
  }));
</script>
