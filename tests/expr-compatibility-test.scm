#!/usr/bin/guile -s
!#

(use-modules (ice-9 popen)
             (ice-9 textual-ports) ;; for get-string-all
             (ice-9 rdelim)) ;; for string-split

(define expressions-str-list '("543 * 3286 - ( 4212 * 432 )"
                               "2 + 2 / 2 * 2 - 2"
                               "323532 * ( 2342 + 13254364565 )"
                               "3235325 * ( 2342 + 13254364565 )"
                               ))
(define failed #f)

(for-each
 (lambda (args-str)
   (define args (string-split args-str #\space)) ;; tokenize
   (define expr-pipe (apply open-pipe* OPEN_READ "expr" args))
   (define fexpr-pipe (apply open-pipe* OPEN_READ "fexpr" args))
   ;; compare the results
   (if (not (equal? (get-string-all expr-pipe) (get-string-all fexpr-pipe)))
       (begin
         (display (string-append "Test Case Failed: " args-str))
         (newline)
         (set! failed #t)))
   (close-pipe expr-pipe)
   (close-pipe fexpr-pipe))
 expressions-str-list)

(if failed
    (exit 1)
    (exit 0))
