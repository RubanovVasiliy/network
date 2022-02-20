( defun  enters ( A  B )      
    ( cond
        ((null A) t)
        ((find (car A) B) (enters (cdr A) B))))
        

(terpri)
(terpri)
(print (enters '(2 1 3) '(1 2 3)))

( defun difference( A  B )      
    ( cond
        ((null A) nil)
        ((if(eq (find (car A) B) nil) (append (list(car A)) (difference (cdr A) B))))
        (t (difference (cdr A) B))))
        

(terpri)
(terpri)
(print (difference '(1 2 3 4 5 6 7 8 9 0) '(1 2 3 4 5 7 8 9 0)))


(print (evenp 2))

( defun  insert (f L )      
    ( cond
        (( null   L )  nil)
        ((if (funcall f (car L)) (append (list '*) (list(car L)) (insert f (cdr L))) ))
        (t (append (list(car L)) (insert f (cdr L)) ))
        ))
        

(print (insert #'evenp '(1 2 3 4 5 6 7 8 9)))
(print (insert #'(lambda (x) (> x 0)) '(-1 2 3 -4 5 6 -7 8 9)))
(terpri)
(terpri)
