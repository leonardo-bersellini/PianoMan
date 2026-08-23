#ifndef COMPOSER_H
#define COMPOSER_H

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

#include "tunes.h"

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "generator/generator.h"

/*
 *  COMPOSER
 *  Lo scrittore degli spartiti suonati. Rappresenta un interprete che legge
 *  un linguaggio speciale, traducibile in note musicali e tempi.
 */

/*
 *  REGOLE DEL LINGUAGGIO-SPARTITO
 *
 *  Il linguaggio permette di rappresentare una canzone leggibile dal composer.
 *  E' possibile utilizzare le note da DO a SI. senza bemolle o diesis.
 *  Lo spartito è fatto di due linee, che rappresentano le due linee sonore riprodotte
 *  dai players. E' quindi possibile fare accordi solo ponendo due note sullo stesso intervallo 
 *  delle due linee.
 *  Per praticità di scrittura, è possibile scrivere le due linee spezettate in segmenti incolonnati.
 *  Per questo ci sono le "macro" #LINE e #ENDLINE.
 *  Per iniziare una line si usa inoltre il token '-'.
 *  Le varie note possono avere durate diverse, differenzianto tra note semplici, crome e note lunghe.
 *  Per questa distinzione si usano parentesi diverse che avvolgono il token della nota.
 *  () -> semplice
 *  [] -> lunga
 *  {} -> croma
 *  Esistono inolte tokens per le pause.
 *  // -> pausa semplice
 *  /[ -> pausa lunga
 *  /( -> pausa croma
 * 
 *  L'unico svantaggio di questo codice è che richiede all'utente scrittore di calcolare da se la musica prodotta.
 *  Per fare un esempio, una pausa lunga occupa lo stesso spazio di scrittura di una nota croma, ma 
 *  nella riproduzione vi saranno effetti molto diversi. Questo si può risolvere / chiarire con
 *  una buona pratica di indentazione.
 *  Inoltre il linguaggio non è pensato per accumulare gli errori, ma va in eccezione al primo.
 * 
 *  Esempio di spartito:
 *  
 *  #LINE
 *  - (Mi) (Mi) (Fa) (Sol) (Sol) (Fa) (Mi) (Re) (Do) (Do) (Re) (Mi) {Mi} (Re) (Re)
 *  - //    //   //   //    //    //   //   //   //   //   //   //   //   //   //
 *  #ENDLINE
 * 
 *  Questo esempio produce il ritornello dell'inno alla giogia. Come si può notare le pause 
 *  sono state indentate sotto alle note per chiarezza.
 * 
 *  !nota: alcuni token richiedono di essere separati con spazi dagli altri.
 *  - token startline (-)
 *  - token newline e endline
 *
 */

class Composer
{
public:
    Composer() = default;
    ~Composer() = default;

    // genera una serie di note (divise per player) in base allo spartito letto
    MusicSheet generateFromMusicSheet(const std::string& path) 
    {
        std::ifstream in(path, std::ios::in);
        if(!in.is_open()) {
            throw std::runtime_error("impossibile aprire il path: " + path);
        }

        std::string sheet, line;

        while(std::getline(in, line)) {
            sheet.append(line + "\n");
        }

        std::cout << "[composer] source text: " << sheet << std::endl;

        Lexer lexer;
        const auto& tokens = lexer.analiseSheet(sheet);

        std::cout << "[composer] lexer done" << std::endl;

        Parser parser;
        const auto& musicAst = parser.parseProgram(tokens);

        std::cout << "[composer] parser done" << std::endl;

        Generator generator;
        const MusicSheet& music_sheet = generator.generateMusic(musicAst);

        std::cout << "[composer] generator done" << std::endl;

        std::cout << "[composer] music sheet: line one: " << music_sheet.line_one.size() << std::endl;
        std::cout << "[composer] music sheet: line two: " << music_sheet.line_two.size() << std::endl;

        return music_sheet;
    }
};


#endif //COMPOSER_H