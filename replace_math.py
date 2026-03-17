import re

with open("calcolo.html", "r") as f:
    html = f.read()

# 1. Add MathJax
mathjax_script = """    <link rel="stylesheet" href="styles.css">
    <script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script>
    <script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"></script>"""
html = html.replace('    <link rel="stylesheet" href="styles.css">', mathjax_script)

# 2. Section 1 Aritmetica Finita
s1_old = """            <pre class="modern-code">
x = segno(x) · (d₁β⁻¹ + d₂β⁻² + ... + d_t·β⁻ᵗ) · βᵉ

dove: 
  β : base (2 nei computer moderni)
  t : numero di cifre della mantissa (indica la Precisione)
  e : esponente / caratteristica, compreso tra un minimo L e massimo U
  d₁ ≠ 0 : questa condizione assicura la "forma normalizzata" garantendo unicità.
           In base 2, se d₁ ≠ 0 deve per forza valere 1 (implicit bit).</pre>"""
s1_new = """            <div class="math-container">
                \\[ x = \\text{segno}(x) \\cdot (d_1 \\beta^{-1} + d_2 \\beta^{-2} + \\dots + d_t \\beta^{-t}) \\cdot \\beta^e \\]
            </div>
            <ul>
                <li><strong>\\(\\beta\\)</strong>: base (2 nei computer moderni)</li>
                <li><strong>\\(t\\)</strong>: numero di cifre della mantissa (indica la Precisione)</li>
                <li><strong>\\(e\\)</strong>: esponente / caratteristica, compreso tra un minimo \\(L\\) e massimo \\(U\\)</li>
                <li><strong>\\(d_1 \\neq 0\\)</strong>: questa condizione assicura la "forma normalizzata" garantendo unicità. In base 2, se \\(d_1 \\neq 0\\) deve per forza valere 1 (implicit bit).</li>
            </ul>"""
html = html.replace(s1_old, s1_new)

# 3. Section 3 Norme e Condizionamento
s3_old = """            <pre class="modern-code">
<strong>K(A) = ‖A‖ · ‖A⁻¹‖</strong></pre>"""
s3_new = """            <div class="math-container">
                \\[ K(A) = \\|A\\| \\cdot \\|A^{-1}\\| \\]
            </div>"""
html = html.replace(s3_old, s3_new)

s4_old = """            <pre class="modern-code">
<strong>‖δx‖ / ‖x‖   ≤   K(A) · (‖δb‖ / ‖b‖)</strong></pre>"""
s4_new = """            <div class="math-container">
                \\[ \\frac{\\|\\delta x\\|}{\\|x\\|} \\le K(A) \\cdot \\frac{\\|\\delta b\\|}{\\|b\\|} \\]
            </div>"""
html = html.replace(s4_old, s4_new)

# 4. Section 4 Interpolazione
s5_old = """            <pre class="modern-code">
<strong>Pₙ(x) = Σ_{k=0}ⁿ  yₖ · Lₖ(x)</strong>

I polinomi base (tutti di grado n) sono definiti come:
Lₖ(x) = Π_{j=0, j≠k}ⁿ  (x - xⱼ) / (xₖ - xⱼ)

Proprietà chiave: Lₖ(xⱼ) = δ_kj = { 1 se k=j, 0 se k≠j }
Svantaggio: Aggiungendo un nuovo nodo x_{n+1}, tutti gli Lₖ(x) devono essere ricalcolati da zero.</pre>"""
s5_new = """            <div class="math-container">
                \\[ P_n(x) = \\sum_{k=0}^{n} y_k L_k(x) \\]
                \\[ L_k(x) = \\prod_{j=0, j \\neq k}^{n} \\frac{x - x_j}{x_k - x_j} \\]
            </div>
            <ul>
                <li><strong>Proprietà chiave:</strong> \\(L_k(x_j) = \\delta_{kj}\\) (vale 1 se \\(k=j\\), 0 altrimenti)</li>
                <li><strong>Svantaggio:</strong> Aggiungendo un nuovo nodo \\(x_{n+1}\\), tutti gli \\(L_k(x)\\) devono essere ricalcolati da zero.</li>
            </ul>"""
html = html.replace(s5_old, s5_new)


s6_old = """            <pre class="modern-code">
<strong>Pₙ(x) = f[x₀] + f[x₀,x₁](x-x₀) + f[x₀,x₁,x₂](x-x₀)(x-x₁) + ... + f[x₀,..,xₙ] Π_{j=0}ⁿ⁻¹ (x-xⱼ)</strong>

Le <em>Differenze Divise di Newton</em> ƒ[ ... ] sono definite ricorsivamente:
- <strong>Ordine 0:</strong> f[xᵢ] = yᵢ
- <strong>Ordine 1:</strong> f[xᵢ, x_{i+1}] = (y_{i+1} - yᵢ) / (x_{i+1} - xᵢ)
- <strong>Ordine k:</strong> f[xᵢ,...,x_{i+k}] = (f[x_{i+1},...,x_{i+k}] - f[xᵢ,...,x_{i+k-1}]) / (x_{i+k} - xᵢ)

Per la valutazione finale del polinomio in un punto generico x', si applica una variante dell'algoritmo di Horner in O(n).</pre>"""
s6_new = """            <div class="math-container">
                \\[ P_n(x) = f[x_0] + f[x_0,x_1](x-x_0) + f[x_0,x_1,x_2](x-x_0)(x-x_1) + \\dots + f[x_0,\\dots,x_n] \\prod_{j=0}^{n-1} (x-x_j) \\]
            </div>
            <p>Le <em>Differenze Divise di Newton</em> \\(f[\\dots]\\) sono definite ricorsivamente:</p>
            <ul>
                <li><strong>Ordine 0:</strong> \\(f[x_i] = y_i\\)</li>
                <li><strong>Ordine 1:</strong> \\(f[x_i, x_{i+1}] = \\frac{y_{i+1} - y_i}{x_{i+1} - x_i}\\)</li>
                <li><strong>Ordine k:</strong> \\(f[x_i,\\dots,x_{i+k}] = \\frac{f[x_{i+1},\\dots,x_{i+k}] - f[x_i,\\dots,x_{i+k-1}]}{x_{i+k} - x_i}\\)</li>
            </ul>
            <p>Per la valutazione finale del polinomio in un punto generico \\(x'\\), si applica una variante dell'algoritmo di Horner in \\(O(n)\\).</p>"""
html = html.replace(s6_old, s6_new)


s7_old = """            <pre class="modern-code">
<strong>Eₙ(x) = f(x) - Pₙ(x) = ( f^{(n+1)}(ξ_x) / (n+1)! ) · ω_{n+1}(x)</strong>

dove:
- ω_{n+1}(x) = (x-x₀)(x-x₁)...(x-xₙ) si chiama "polinomio nodale".
- ξ_x è un punto incognito appartenente all'intervallo (min(x_i), max(x_i)).</pre>"""
s7_new = """            <div class="math-container">
                \\[ E_n(x) = f(x) - P_n(x) = \\frac{f^{(n+1)}(\\xi_x)}{(n+1)!} \\omega_{n+1}(x) \\]
            </div>
            <ul>
                <li><strong>\\(\\omega_{n+1}(x)\\)</strong> = \\((x-x_0)(x-x_1)\\dots(x-x_n)\\) si chiama "polinomio nodale".</li>
                <li><strong>\\(\\xi_x\\)</strong> è un punto incognito appartenente all'intervallo \\((\\min(x_i), \\max(x_i))\\).</li>
            </ul>"""
html = html.replace(s7_old, s7_new)


s8_old = """            <pre class="modern-code">
Obiettivo: minimizzare || r ||₂² = Σ_{i=1}ⁿ (P_m(xᵢ) - yᵢ)²

Matematicamente, si impone l'annullamento delle derivate parziali, ottenendo
il Sistema delle <strong>Equazioni Normali</strong>:
    <strong>(Aᵀ A) c = Aᵀ y</strong>
Dove A è la Matrice di Vandermonde. 
In MATLAB si risolve in automatico con l'operatore slash: `c = A \ y` oppure col comando `polyfit`.</pre>"""
s8_new = """            <div class="math-container">
                \\[ \\min \\| \\mathbf{r} \\|_2^2 = \\sum_{i=0}^{n} (P_m(x_i) - y_i)^2 \\]
            </div>
            <p>Matematicamente, si impone l'annullamento delle derivate parziali, ottenendo il Sistema delle <strong>Equazioni Normali</strong>:</p>
            <div class="math-container">
                \\[ (A^T A) \\mathbf{c} = A^T \\mathbf{y} \\]
            </div>
            <p>Dove \\(A\\) è la Matrice di Vandermonde. In MATLAB si risolve in automatico con l'operatore slash: <code>c = A \ y</code> oppure col comando <code>polyfit</code>.</p>"""
html = html.replace(s8_old, s8_new)


# Integrazione
s9_old = """            <pre class="modern-code">
<strong>Iₙ(f) = Σ_{i=0}ⁿ  wᵢ · f(xᵢ)</strong>

- <strong>xᵢ</strong> : Nodi di quadratura appartenenti ad [a,b]
- <strong>wᵢ</strong> : Pesi di quadratura (indipendenti dalla funzione f!)</pre>"""
s9_new = """            <div class="math-container">
                \\[ I_n(f) = \\sum_{i=0}^{n} w_i f(x_i) \\]
            </div>
            <ul>
                <li><strong>\\(x_i\\)</strong> : Nodi di quadratura appartenenti ad \\([a,b]\\)</li>
                <li><strong>\\(w_i\\)</strong> : Pesi di quadratura (indipendenti dalla funzione \\(f\\)!)</li>
            </ul>"""
html = html.replace(s9_old, s9_new)

# Metodi Root finding
s10_old = """            <pre class="modern-code">
<strong>Formula iterativa Newton:    x_{k+1} = x_k - f(x_k) / f'(x_k)</strong>

<span class="comment">% Condizioni per efficacia e convergenza QUADRATICA (p=2):</span>
- La funzione deve essere differenziabile e la derivata calcolabile analiticamente (svantaggio costoso).
- Il punto `x_0` iniziale deve essere "abbastanza vicino" alla radice.
- La radice deve avere molteplicità m=1, ovvero occorre che f'(α) ≠ 0. Se la derivata
  si annulla vicina alla radice, il grafico smette di intersecare l'asse "in verticale"
  e il metodo degenera a velocità Lineare.</pre>"""
s10_new = """            <div class="math-container">
                \\[ x_{k+1} = x_k - \\frac{f(x_k)}{f'(x_k)} \\]
            </div>
            <p><strong>Condizioni per efficacia e convergenza QUADRATICA (\\(p=2\\)):</strong></p>
            <ul>
                <li>La funzione deve essere differenziabile e la derivata calcolabile analiticamente.</li>
                <li>Il punto \\(x_0\\) iniziale deve essere "abbastanza vicino" alla radice.</li>
                <li>La radice deve avere molteplicità \\(m=1\\), ovvero occorre che \\(f'(\\alpha) \\neq 0\\). Se la derivata si annulla vicina alla radice, il metodo degenera a velocità Lineare.</li>
            </ul>"""
html = html.replace(s10_old, s10_new)


s11_old = """            <pre class="modern-code">
f'(x_k)  ≈  (f(x_k) - f(x_{k-1})) / (x_k - x_{k-1})

Formula iterativa: 
<strong>x_{k+1} = x_k - f(x_k) [ (x_k - x_{k-1}) / (f(x_k) - f(x_{k-1})) ]</strong>

Vantaggio: richiede una sola nuova valutazione di f(x) per iterazione, non richiede f'(x).
Ordine di Convergenza: p ≈ 1.618 (Rapporto Aureo). Superlineare.</pre>"""
s11_new = """            <div class="math-container">
                \\[ f'(x_k) \\approx \\frac{f(x_k) - f(x_{k-1})}{x_k - x_{k-1}} \\quad \\implies \\quad x_{k+1} = x_k - f(x_k) \\frac{x_k - x_{k-1}}{f(x_k) - f(x_{k-1})} \\]
            </div>
            <ul>
                <li><strong>Vantaggio:</strong> richiede una sola nuova valutazione di \\(f(x)\\) per iterazione, non richiede \\(f'(x)\\).</li>
                <li><strong>Ordine di Convergenza:</strong> \\(p \\approx 1.618\\) (Rapporto Aureo). Superlineare.</li>
            </ul>"""
html = html.replace(s11_old, s11_new)

s12_old = """            <pre class="modern-code">
<strong>Teorema di Convergenza (Contrazione):</strong>
Sia Φ differenziabile. Se attorno al punto fisso α esiste un intervallo 
dove <strong>|Φ'(x)| ≤ L < 1</strong>, allora la serie partirà convergente (indipendentemente da x_0) e
convergerà in ordine LINEARE.
L approssima il tasso di convergenza (fattore L). Più L è vicino a 0, 
più rapida sarà la fine!</pre>"""
s12_new = """            <div class="math-container">
                \\[ |\\Phi'(x)| \\le L < 1 \\]
            </div>
            <p><strong>Teorema di Convergenza (Contrazione):</strong></p>
            <p>Sia \\(\\Phi\\) differenziabile. Se attorno al punto fisso \\(\\alpha\\) esiste un intervallo dove \\(|\\Phi'(x)| \\le L < 1\\), allora la successione converge (indipendentemente da \\(x_0\\)) in ordine LINEARE.<br>
            \\(L\\) è il fattore di contrazione. Più \\(L\\) è vicino a 0, più rapida sarà la fine!</p>"""
html = html.replace(s12_old, s12_new)


with open("calcolo.html", "w") as f:
    f.write(html)
