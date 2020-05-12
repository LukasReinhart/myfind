# myfind

Schreiben Sie ein C/C++-Programm, das es ermöglicht, parallel nach unterschiedlichen Files in einem Dateiverzeichnis zu suchen.

Dem Hauptprogramm werden als Kommandozeilenparameter der Suchpfad und die Dateinamen übergeben. Beachten Sie, dass eine beliebige Anzahl an Dateinamen möglich ist, nach denen gesucht werden soll.

Usage:
`./myfind [-R] [-i] searchpath filename1 [filename2] ...[filenamen]`

Bsp.:
`./myfind ./ test.txt test.doc test`
(sucht parallel nach den drei Dateien test.txt test.doc test im aktuellen Arbeitsverzeichnis)

Das Hauptprogramm spaltet pro Dateiname mit fork() einen Kindprozess ab, der die Dateien im angegebenen Suchpfad (Parameter ‚searchpath‘) durchforstet und für jede gefundene Datei folgendes ausgibt:
`<pid>: <filename>: <complete-path-to-found-file>\n`
* \<pid> gibt dabei die Prozess-ID des aktuellen Kindprozesses an, der die Suche durchführt.
* \<filename> ist der Dateiname, wie er auf der Kommandozeile angegeben wurde
* \<complete-path-to-found-file> ist der vollständige Pfad, in dem die Datei (ausgehend von ‚searchpath‘) gefunden wurde. Der complete-path-to-found-file soll auch den Dateinamen selbst (am Ende) beinhalten und ein absoluter (!) Pfad sein, auch wenn der angegebene ‚searchpath‘ ein relativer Pfad war.

* Wird die Option -R angegeben, soll die Suche rekursiv erfolgen, ansonst nur im angegebenen ‚searchpath‘.
* Der angegebene ‚searchpath‘ kann ein absoluter Pfad oder ein relativer Pfad sein.
* Die angegebenen Dateinamen sind keine Pfade sondern nur einzelne Namen. Weiters müssen Wildcards (wie etwa ‚*‘) zwecks Verinfachung nicht behandelt werden.
* Wird die Option –i angegeben, sollen Dateien unabhängig von Groß/Kleinschreibung gefunden werden (es wird dann zum Beispiel auch test.txt oder TEST.txt gefunden).
* Die Optionen –R und –i können an beliebiger Stelle auf der Kommandozeile angegeben werden.
* Die Ausgabe erfolgt auf stdout und unsortiert. Einzelne Zeilen müssen jedoch stets vollständig auf stdout erfolgen. Also von \<pid> beginnend bis Übungsunterlagen zum Newline am Ende einer Ausgabezeile soll ein Prozess sicherstellen, dass kein anderer Prozess die Ausgabe beeinflusst (Wie stellt man dies sicher bzw. wie kann man dessen sicher sein?). Die Ausgabe der Zeilen verschiedener Prozesse kann jedoch in beliebiger Reihenfolge erfolgen.

Der Kindprozess darf für die Implementierung nicht den Linux Befehl find verwenden sondern muss die Suche selbst durchführen.

Der Vaterprozess muss auf die Terminierung der Kindprozesse reagieren (wait()). Es dürfen keine Zombies im System verbleiben!

## Hinweise
* Verwenden Sie getopt() für eine ordnungsgemäße Verarbeitung der Kommandozeilenparameter und Optionen.
* In Moodle finden sie unter Beispielprogramme (Operationen auf Dateieverzeichnissen) die Datei shownames.c welche zeigt, wie man ein Dateiverzeichnis ausgeben kann.
* Halten Sie sich weiters an die Richtlinien zur Linux-Programmierung.

## Abgabe
Im Abgabesystem ist ein .tgz File abzugeben. Dieses soll beinhalten:
* Alle Sourcen inkl. Code Kommentaren!
* Ein Makefile mind. mit den Targets all und clean Abgabe über Moodle.

Das Beispiel muss beim abschließenden Codereview präsentiert werden.
