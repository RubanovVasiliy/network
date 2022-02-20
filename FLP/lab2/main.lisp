(write 'lab2_7)
( defun  insert ( x  L )      
    ( cond
        (( null   L )  (list x))
        (( if (> x (car L))    (append(cons (car L) (insert x (cdr L))))))
        ((append (list x) L))))
        

(print (insert 7 '(0 3 3 6 9)))
(terpri)
(terpri)



(write 'lab2_17)
( defun  remove-even ( L )      
    ( cond
        (( atom   L )  L)
        (T (append(cons (car L) (remove-even (cddr L)))))))


(print (remove-even '(-2 6 s -1 4 f 0 z x r)))
(terpri)
(terpri)


(write 'lab2_27)
(defun max-depth (L)
 
  (cond ((null L) 1)
        ((atom (car L)) (max-depth (cdr L)))
        (t (max (+ 1 (max-depth (car L))) (max-depth (cdr L))))))


(print(max-depth '((((1))) 2 (3 4))))