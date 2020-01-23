;; ---------------------------------------------------------------;
;;; projects.scm 
;;
;; This file is part of GUILE-PROJ
;;
;; Copyright (C) 2018 by Matthew Love <matthew.love@colorado.edu>
;; GUILE-PROJ is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.
;;
;; GUILE-PROJ is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GUILE-PROJ.  If not, see <http://www.gnu.org/licenses/>.
;;
;; --------------------------------------------------------------;
;;
;;; Commentary:
;;
;;
;;; Code:

;; Define the module
(define-module (proj projects)
  #:version (0 2 2)
  ;; Export the module functions
  #:export
  (deg2rad
   rad2deg
   pj-inq-libvers
   pj-inq-release
   pj-guile-inq-libvers
   pj-errno
   pj-strerrno
   pj-get-errno-ref
   scm->pjuv
   scm->pjuvw
   pjuv->scm
   pjuvw->scm
   pj-init
   pj-init+
   pj-pr-list
   pj-get-def
   pj-fwd
   pj-fwd->scm
   pj-inv
   pj-inv->scm
   pj-fwd3d
   pj-inv3d
   pj-transform
   pj-datum-transform
   pj->latlong
   pj-latlong?
   pj-geocent?
   pj-r->dms
   pj-set-r->dms
   pj-dms->r
   pj-get-list-ref
   ++pj-list
   pj-list->scm
   pj-get-ellps-ref
   ++pj-ellps
   pj-ellps->scm
   pj-get-units-ref
   ++pj-units
   pj-units->scm
   pj-get-datums-ref
   ++pj-datums
   pj-datums->scm
   pj-get-prime-meridians-ref
   ++pj-prime-meridians
   pj-prime-meridians->scm
   make-pjctx
   pj-get-default-ctx
   pj-ctx-set-debug
   pj-lists->scm))

;; Load the module extension
;;-scm_init_proj
(load-extension "libguile-proj" "scm_init_proj")

;; Gather the projection list
(define (pj-gather-list pj-list cs-list)
  "gather a *list values from proj"
  (if (pj-list->scm pj-list)
      (let ((this-cs (pj-list->scm pj-list)))
	(++pj-list pj-list)
	(pj-gather-list pj-list (append (list this-cs) cs-list)))
      (reverse cs-list)))

;; Gather the ellipsoid list
(define (pj-gather-ellps pj-list cs-list)
  "gather a *list values from proj"
  (if (pj-ellps->scm pj-list)
      (let ((this-cs (pj-ellps->scm pj-list)))
	(++pj-ellps pj-list)
	(pj-gather-ellps pj-list (acons (car this-cs) (cdr this-cs) cs-list)))
      cs-list))

;; Gather the units list
(define (pj-gather-units pj-list cs-list)
  "gather a *list values from proj"
  (if (pj-units->scm pj-list)
      (let ((this-cs (pj-units->scm pj-list)))
	(++pj-units pj-list)
	(pj-gather-units pj-list (append (list this-cs) cs-list)))
      (reverse cs-list)))

;; Gather the datums list
(define (pj-gather-datums pj-list cs-list)
  "gather a *list values from proj"
  (if (pj-datums->scm pj-list)
      (let ((this-cs (pj-datums->scm pj-list)))
	(++pj-datums pj-list)
	(pj-gather-datums pj-list (append (list this-cs) cs-list)))
      (reverse cs-list)))

;; Gather the prime-meridans list
(define (pj-gather-prime-meridians pj-list cs-list)
  "gather a *list values from proj"
  (if (pj-prime-meridians->scm pj-list)
      (let ((this-cs (pj-prime-meridians->scm pj-list)))
	(++pj-prime-meridians pj-list)
	(pj-gather-prime-meridians pj-list (append (list this-cs) cs-list)))
      (reverse cs-list)))

;; Return a list of pj-list-type values.
;; list-type options are 'pj 'ellps 'units 'datums 'prime-meridians
(define* (pj-lists->scm #:optional (list-type 'pj) (cs-list '()))
  "return a list of pj-list-type values
list-type options are 'pj 'ellps 'units 'datums 'prime-meridians"
  (case list-type
    ((pj)
     (pj-gather-list (pj-get-list-ref) '()))
    ((ellps)
     (pj-gather-ellps (pj-get-ellps-ref) '()))
    ((units)
     (pj-gather-units (pj-get-units-ref) '()))
    ((datums)
     (pj-gather-datums (pj-get-datums-ref) '()))
    ((prime-meridians)
     (pj-gather-prime-meridians (pj-get-prime-meridians-ref) '()))))
;;; End
