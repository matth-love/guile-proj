;; ---------------------------------------------------------------;
;;; geodesic.scm 
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
;; geod init functions:
;; `geod-init` is a direct wrapper for the geodesic.h `geod_init` which means it takes a `geod_geodesic` structure as
;; input to initiaize, `pj-geod-init` is like `geod-init`, but it creates a new `geod_geodesic` structure
;; type and one only has to supply the ellipse values to initialize the structure. `geod-init-ellps`
;; is like `pj-geod-init` but takes the ellipse name as input and generates a `geod_geidesic structure` as output.
;; To use `geod-init` one must first create a `geod_geodetic` structure with `(make-geodetic "Name")`.
;; To use `pj-geod-init` one must supply the radius and flattening of the desired ellipse.
;; To use `geod-init-ellps` one must supply the name of the desired ellipse; find the names with `(pj-lists->scm `ellps)`.
;; Each of these functions initializes a WGS84 geodetic structure type
;;  (geod-init (make-geodesic) 6378137 (/ 1 298.257223563))
;;  (geod-init 6378137 (/ 1 298.257223563))
;;  (geod-init-ellps "WGS84")
;;; Code:

;; Define the module
(define-module (proj geodesic)
  #:version (0 2 2)
  #:use-module (proj projects)
  #:export
  (geodesic-version-major
   geodesic-version-minor
   geodesic-version-patch
   make-geodesic
   make-geodesic-line
   geod-init
   geod-init/
   geod-init-ellps
   geod-direct
   geod-inverse
   geod-geninverse
   geod-line-init
   geod-inverse-line
   geod-direct-line
   geod-position))

;; Load the module extension
;;-scm_init_geod
(load-extension "libguile-proj" "scm_init_geod")

;; Extract the ellipsoid Major Axis from the ellipsoid list in proj
(define (geod-ellps-a ellps-list)
  (if (pair? ellps-list)
      (if (string=? (substring (car ellps-list) 0 2) "a=")
	  (substring (car ellps-list) 2 (- (string-length (car ellps-list)) 1))
	  (geod-ellps-a (cdr ellps-list)))))

;; Extract the ellipsoid flattening from the ellipsoid list in proj.
(define (geod-ellps-f ellps-list)
  (if (pair? ellps-list)
      (if (string=? (substring (car ellps-list) 0 3) "rf=")
	  (substring (car ellps-list) 3 (- (string-length (car ellps-list)) 1))
	  (geod-ellps-f (cdr ellps-list)))))

;; Initialize a geodesic object based on ELLPS
(define (geod-init-ellps ellps)
  "Initialize a geodesic object based on the ellipse.
Use `(pj-lists->scm 'ellps)` to see the avaialble ellipses."
  (if (not (assoc ellps (pj-lists->scm 'ellps)))
      (begin
	(format (current-error-port)
		"guile-proj: warning specified ellipse (~a) doesn't exit, falling back to WGS84\n" ellps)
	(set! ellps "WGS84")))
  (let ((f (string->number (geod-ellps-f (assoc ellps (pj-lists->scm 'ellps)))))
	(a (string->number (geod-ellps-a (assoc ellps (pj-lists->scm 'ellps))))))
    (if (and (number? f) (number? f))
	(geod-init/ a (/ 1 f)))))
;;; End
