# First, Follow, Directorを求めてみる

```
S → B A | A A d
A → a | ε
B → b A | c B
```

<div>
\[
\begin{eqnarray*}
{\rm First}(S) &=& {\rm First}(B) \cup {\rm First}(A) \cup \{d\} - \{\varepsilon\} = \{a, b, c, d\} \\
{\rm First}(A) &=& \{a, \varepsilon\} \\
{\rm First}(B) &=& \{b, c\} \\
~\\
{\rm Follow}(S) &=& \{$\} \\
{\rm Follow}(A) &=& {\rm First}(S) \cup {\rm First}(A) \cup \{d\} \cup {\rm Follow}(B) - \{\varepsilon\} = \{a, d, $\} \\
{\rm Follow}(B) &=& {\rm First}(A) \cup {\rm Follow}(S) \cup {\rm Follow}(B) - \{\varepsilon\} = \{a, $\}
\end{eqnarray*}
\]
</div>

| $V_T \cup V_N$ | First | Follow |
| --- | --- | --- |
| $ | $ | |
| a | a | |
| b | b | |
| c | c | |
| d | d | |
| S' | a, b, c, d | |
| S | a, b, c, d | $ |
| A | a, ε | a, d, $ |
| B | b, c | a, $ |

<div>
\[
\begin{eqnarray*}
{\rm Director}(S \to BA) &=& {\rm First}(B) &=& \{b, c\} \\
{\rm Director}(S \to AAd) &=& {\rm First}(A) \cup {\rm First}(A) \cup \{d\} - \{\varepsilon\} &=& \{a, d\} \\
{\rm Director}(A \to a) &=& {\rm First}(a) &=& \{a\} \\
{\rm Director}(A \to \varepsilon) &=& {\rm Follow}(A) &=& \{a, d, $\} \\
{\rm Director}(B \to bA) &=& {\rm First}(b) &=& \{b\} \\
{\rm Director}(B \to cB) &=& {\rm First}(c) &=& \{c\}
\]
</div>
