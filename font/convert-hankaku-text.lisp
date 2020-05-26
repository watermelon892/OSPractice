;; sbcl --load convert-hankaku-text.lisp

(defconstant +input-file+ "./hankaku.txt")
(defconstant +output-file+ "./hankaku.S")
(defconstant +head+ "    .data
    .global hankaku

hankaku:
")

(defconstant +byte+ "    .byte ")
(defun convert (line)
  (if (or (zerop (length line)) (> (length line) 8))
      (format nil "")
      (let* ((line2 (substitute #\0 #\. line))
             (line3 (substitute #\1 #\* line2)))
        (format nil "0x~2,'0X" (parse-integer line3 :radix 2)))))

(defun convert-hankaku-text-to-asm ()
  (with-open-file (in +input-file+)
    (with-open-file (out +output-file+
                         :direction :output
                         :if-exists :supersede)
      (format out +head+)
      (let ((i 0))
        (loop for line = (read-line in nil)
              while line
              do (let ((ret (convert line)))
                   (unless (zerop (length ret))
                     (when (zerop i) (format out "~A" +byte+))
                     (format out "~A" ret)
                     (if (>= i 3)
                         (progn
                           (format out "~%")
                           (setf i 0))
                         (progn
                           (format out ", ")
                           (incf i))))))))))

(convert-hankaku-text-to-asm)
(quit)
