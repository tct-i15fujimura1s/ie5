# システム数理工学
* 実世界で必要となる数学的な基礎を習得する
* 問題を定式化して解くための手段・方法の体感を得る

## この授業で取り上げる手法（予定）
* 線形計画法
* 非線形計画法
* 動的計画法
* 組合せ最適化
* 多変量解析とその応用（の一部）
  * 主成分分析（と因子分析）
* 決定論的手法
* 確率論的手法
  * ビッグデータだと、決定論的手法だけだと計算量が大きくなりすぎて解けない場合も
  * `In this world nothing can be said to be certain, except death and taxes.`

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
