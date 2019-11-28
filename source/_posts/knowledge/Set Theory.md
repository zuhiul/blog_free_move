---
title: 	Problems in Set Theory
date:		2019-07-29
author:	"zuhiul"
tags:
  - Mathematical Analysis
---

$\text{1.Prove Theorem 1 (show that $x$ is in the left-hand set iff it is in the right-hand set).For example,for (d),}$

\begin{eqnarray} 
x \in(A \cup B) \cap C &\Longleftrightarrow& [x \in(A \cup B) \text { and } x \in C] \\\
&\Longleftrightarrow& [(x \in A \text { or } x \in B), \text { and } x \in C] \\\
&\Longleftrightarrow& [(x \in A, x \in C) \text { or }(x \in B, x \in C)] 
\end{eqnarray}


- $ A \cup A = A ; A \cap A = A$

\begin{eqnarray}
A \cup A &=& \\{ x|x \in A \\} \cup \\{ x|x \in A \\}\\\
&=& \\{ x|x \in A \\}\\\
&=&A\\\
A \cap A &=& \\{ x| x \in A \\} \cup \\{ x|x \in A \\}\\\
&=& \\{ x|x \in A \\}\\\
&=&A\\\
\end{eqnarray}

- $ A \cup B = B \cup A , A \cap B = B \cap A $

\begin{eqnarray}
A \cup B &=& \\{ x| x \in A \\} \cup \\{ x|x \in B \\} \\\
&=& \\{ x|x \in A\ or\ x \in B \\}\\\
&=& \\{ x|x \in B \\} \cup \\{ x|x \in A \\}\\\
&=& B \cup A
\end{eqnarray}