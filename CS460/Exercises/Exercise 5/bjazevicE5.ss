;Vince Bjazevic Exercise 3

(define (reciprocal n)
(if (and (number? n) (not (= n 0)))
      (/ 1 n)
      'invalid_parameter
      )
)

(define (square n)
  (if (and (number? n) (not (= n 0)))
      (* n n)
      'invalid_parameter
      )
  )
(define (list_copy ls)
  (if (list? ls)
      ls
      'list_copy_requires_a_list_argument
      )
  )

(define (odd_copy ls)
  (cond ((null? ls)
	 '())
	((null? (cdr ls))
	 '())
	((list? ls)
	 (cons (car ls) (odd_copy (cddr ls)
				      )
	       )
	 )
	(else 'odd_copy_requires_a_list_arg)
	)
  )

(define (even_copy ls)
  (cond ((null? ls)
         '())
        ((null? (cdr ls))
         '())
        ((list? ls)
         (cons (car(cdr ls)) (even_copy (cddr ls)
                                      )
               )
         )
        (else 'even_copy_requires_a_list_arg)
	)
  )

(define (list_sum mylist)
  (if (null? mylist)
   0
   (+ (car mylist) (list_sum (cdr mylist)))
   )
  )

(define (last mylist)
  (if (null? (cdr mylist))
      (car mylist)
      (last (cdr mylist))
      )
  )

(define (insert_last myvalue mylist)
  (if (null? mylist)
      (cons myvalue mylist)
      (cons (car mylist) (insert_last myvalue (cdr mylist))
	    )
      )
  )


(define (remove_first mylist)
  (if (null? (cdr mylist))
      '()
      (cons (car(cdr mylist)) (remove_first (cdr mylist))
            )
     )
  )

(define (remove_last mylist)
  (if (null? (cdr mylist)) '()
      (cons (car mylist) (remove_last (cdr mylist))))
)

(define (list_reverse mylist)
  (if (null? mylist)
      mylist
      (reverse_helper (car mylist) (list_reverse (cdr mylist)))
      )
  )

(define (reverse_helper var mylist)
  (if (null? mylist)
      (cons var mylist)
      (cons (car mylist) (reverse_helper var (cdr mylist)))
      )
  )

;removed my attempt at square root due to compile errors


;Vince Bjazevic Exercise 5 works as intended

(define append_helper (lambda (ls1 ls2)
	(cond
	    [(null? ls1) ls2]
	    [else (cons (car ls1) (append_helper (cdr ls1) ls2))]))
)

(define (all_reverse ls)
	(cond
	    [(null? ls) '()]
	    [(list? ls)(if(list? (car ls))
				(append_helper (all_reverse (cdr ls)) (list( all_reverse ( car ls))))
				(append_helper (all_reverse (cdr ls))  (list( car ls))))]
	    [else (ls)]
    )
)

(define (quicksort ls)
	(quicksort_helper (numbers_only ls))
)

(define (quicksort_helper ls)
	(cond
	    [(null? ls) '()]
	    [else(let ((pivot (car ls)))(append (append(quicksort (greater_operation pivot ls))(equal_operation pivot ls))(quicksort (less_operation pivot ls))))])
)

(define (less_operation pivot ls)
	(cond [(null? ls)	'()]
		[ (< pivot (car ls)) (cons (car ls) (less_operation pivot (cdr ls)))]
		[else (less_operation pivot (cdr ls))])
)

(define (greater_operation pivot ls)
	(cond
	    [(null? ls) '()]
		[(> pivot (car ls)) (cons (car ls) (greater_operation pivot (cdr ls)))]
		[else (greater_operation pivot (cdr ls))])
)

(define (equal_operation pivot ls)
	(cond
	    [(null? ls) '()]
        [(= pivot (car ls)) (cons (car ls) (equal_operation pivot (cdr ls)))]
	    [else (equal_operation pivot (cdr ls))])
)

(define (mergesort ls)
	(mergesort_helper (numbers_only ls))
)

(define (mergesort_helper ls)
	(cond
	    [(or (null? ls) (null? (cdr ls))) ls]
	    [else(let ((split (splitList ls))) (merge (mergesort (car split)) (mergesort (car (cdr split)))))])
)

(define (merge ls1 ls2)
	(cond
	    [(null? ls1) ls2]
        [(null? ls2) ls1]
	    [else (let ((lsh1 (car ls1)) (lsh2 (car ls2)))(if(<= lsh1 lsh2) (cons lsh1 (merge (cdr ls1) ls2))(cons lsh2 (merge ls1 (cdr ls2)))))]
	)
)

(define (split_list_helper ls start end count)
	(cond
	    [(null? ls) '()]
		[(and (>= count start) (< count end))(cons (car ls) (split_list_helper (cdr ls) start end (+ count 1)))]
		[else (split_list_helper (cdr ls) start end (+ count 1))])
)

(define (splitList ls)
	(cons (split_list_helper ls 0(/ (len ls) 2)  0) (cons (split_list_helper ls (/ (len ls) 2) (len ls) 0) '()))
)

(define (len ls)
	(cond
	    [(null? ls) 0]
	    [else (+ 1 (len(cdr ls)))])
)

(define (flatten ls)
    (cond [(null? ls) '()]
          [(list? (car ls)) (append (flatten (car ls)) (flatten (cdr ls)))]
          [else (cons (car ls) (flatten (cdr ls)))])
)

(define (numbers_only ls)
	(numbers_only_helper (flatten ls))
)

(define (numbers_only_helper ls)
	(cond
	 [(null? ls) '()]
 	 [(number? (car ls)) (cons (car ls) (numbers_only_helper (cdr ls)))]
	 [else (numbers_only_helper (cdr ls))])
)

(display 'quicksort:)
(display (quicksort '(1 5 3 6 8 92 –1 0 4 5 3)))
(newline)
(display 'quicksort:)
(display (quicksort '(a b d e c t s)))
(newline)
(display 'mergesort:)
(display (mergesort '(1 5 3 6 8 92 –1 0 4 5 3)))
(newline)
(display 'mergesort:)
(display (mergesort '(a b d e c t s)))
(newline)
(display 'quicksort:)
(display (quicksort '(1 (5 (3 6 8)) 92 –1 (0) 4 5 3)))
(newline)
(display 'quicksort:)
(display (quicksort '(a b (67 4 (3 (3)) 101) d e (7 c) c t s)))
(newline)