(write 'lab1_1)
;(print '((1) ((2 *)) (3(4))))
;(print (cdr '((1) ((2 *)) (3(4)))) )
;(print (cadr '((1) ((2 *)) (3(4)))) )
;(print (caadr '((1) ((2 *)) (3(4)))) )
;(print (cdaadr '((1) ((2 *)) (3(4)))) )
(print (car(cdaadr '((1) ((2 *)) (3(4))))) )
(terpri)
(terpri)


(write 'lab1_2)
(print (list '(+ 1 2) '() '(+ 1)))
(terpri)
(terpri)



(write 'lab1_3_1)
;(print  (cons(cons '3 nil)nil) )
;(print  (cons '2 (cons(cons '3 nil)nil)) )
;(print  (cons '1 (cons'2 (cons(cons '3 nil)nil))) )
(print  (cons(cons '1 (cons'2 (cons(cons '3 nil)nil)))nil) )
(terpri)
(terpri)



(write 'lab1_3_2)
(print  (list(list '1 '2 (list(list '3)))) )
(terpri)
(terpri)



(write 'lab1_4)
(defvar d  '(1 2 3 6))
(defun foo (f)
  (print (append(list(car f)(car(last f)))(cddr(butlast f))(list(cadr f)))))
(print d)
(foo d)
(terpri)
(terpri)
;(print (cadr f))
;(print (car(last f)))
;(print (car f))
;(print (butlast f))
;(print (cddr (butlast f)))
;(print (list (car f) (car(last f)) (cddr (butlast f)) (cadr f)))
;(print (append(list(car f)(car(last f)))(cddr(butlast f))(list(cadr f))))
