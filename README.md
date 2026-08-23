# PianoMan

Un piccolo interprete C++/SFML che legge uno "spartito testuale" scritto in un linguaggio custom e lo esegue suonando le note.

Il progetto è diviso in due parti:

- **Pianist** — l'interprete: riceve sequenze di note e le suona tramite due `Player` indipendenti (thread separati), permettendo di eseguire due linee musicali in contemporanea.
- **Composer** — il "lettore di spartiti": legge un file di testo scritto nel linguaggio-spartito custom e lo traduce in note eseguibili dal Pianist, tramite un lexer, un parser e un generator.
---

## Come Funziona?

Il progetto pianoman permette di eseguire uno spartito musicale direttamente sul tuo pc, tramite un interprete che riproduce suoni con la libreria SFML.
L'interprete esegue spartiti scritti in un linguaggio custom per pianoman, spiegato nel dettaglio nella prossima sezione.

## Come si scrive uno spartito

Il linguaggio permette di rappresentare una canzone come due linee sonore parallele (una per ciascun `Player`), scritte in blocchi delimitati da `#LINE` / `#ENDLINE`. Ogni linea inizia con il token `-`.

Le note vanno da `DO` a `SI` (senza bemolle/diesis) e la loro durata è indicata dal tipo di parentesi che le racchiude:

| Sintassi | Durata |
|---|---|
| `(NOTA)` | Semplice |
| `[NOTA]` | Lunga |
| `{NOTA}` | Croma |

Le pause si scrivono senza indicare una nota:

| Sintassi | Durata pausa |
|---|---|
| `//` | Semplice |
| `/[` | Lunga |
| `/(` | Croma |

Esempio (scala di Do centrale, con la seconda linea silenziosa):

```
#LINE
- (DO) (RE) (MI) (FA) (SOL) (LA) (SI) (DO)
- //    //   //   //   //   //    //   //
#ENDLINE
```

Si possono concatenare più blocchi `#LINE`/`#ENDLINE` per costruire lo spartito in più segmenti. Uno spartito completo di esempio, commentato, si trova in [`examples/tutorial.txt`](examples/tutorial.txt).

> Nota: il linguaggio non recupera dagli errori — al primo errore di sintassi l'esecuzione si interrompe con un'eccezione.
---

## Build

Requisiti: CMake ≥ 3.16, compilatore C++20, [SFML](https://www.sfml-dev.org/) 2.6.2 (componenti graphics, window, system, audio).

```bash
cmake -B build
cmake --build build
```

L'eseguibile chiederà a runtime il path di un file di spartito da eseguire.

---

## Struttura del progetto

```
examples/                # Esempi di spartiti
pianoman/
├── tunes.h              # Tune, TuneDuration, MusicSheet
├── pianist/
│   ├── pianist.h        # Pianist: traduce le note in buffer audio
│   └── player.h         # Player: riproduce una linea su un thread dedicato
└── composer/
    ├── composer.h        # Composer: orchestratore lexer -> parser -> generator
    ├── tokens.h
    ├── lexer/lexer.h
    ├── parser/parser.h
    └── generator/generator.h
```

## Stato del progetto

Progetto hobby, in sviluppo. Alcune parti (gestione delle pause/durate a livello di Player, calcolo automatico del pitch in base al tempo della nota) sono ancora in corso di rifinitura.
