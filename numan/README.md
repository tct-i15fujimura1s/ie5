# 数値解析

## 数値解析とは
* 昔：物理現象の理論的な説明（仮定→実験)
* 近年：原子、素粒子レベル（実験は困難）⇒仮定→シミュレーション→現実に則しているか確認

  * シミュレーション：膨大な計算→多くの人と時間が必要
  * コンピュータ：膨大な計算が可能（数式でなく離散値）→誤差の要因を考える

**計算のためのアルゴリズムを考える**

* 常微分方程式
  * 補間法
  * 微分・積分
    * 連立方程式
      * 単一方程式
        * 誤差

**[シラバス](https://syllabus.kosen-k.go.jp/Pages/PublicSyllabus?school_id=35&department_id=03&subject_id=0138&year=2015&lang=ja)**

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
