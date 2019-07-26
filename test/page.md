---
theme: jekyll-theme-modernist
---

# Test Page

## Index of /
<ul id="dirs">
</ul>

<script>
  const dirs = document.querySelector("#dirs");
  fetch("https://api.github.com/repos/tct-i15fujimura1s/ie5/contents/", {mode: "cors"})
  .then(res => res.json())
  .then(entries => entries.forEach(entry => {
    const li = document.createElement("li");
    {
      const a = document.createElement("a");
      a.textContent = entry.name;
      a.href = entry.html_url;
      li.appendChild(a);
    }
    dirs.appendChild(li);
  }));
</script>

$.create("li", [
  
]);

li
  
