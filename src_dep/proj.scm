;-*-scheme-*-

;; Copyright (c) 2013 - 2018 Matthew Love <matthew.love@colorado.edu>>
;; GUILE-PROJ is liscensed under the GPL v.2 or later and 
;; is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details. 
;; <http://www.gnu.org/licenses/>

;; Define the module
(define-module (proj proj))

;; Export the module functions
(export
 ;; CONSTANTS
 deg2rad
 rad2deg
 ;; INQ
 pj-inq-libvers
 pj-guile-inq-libvers
 ;; FUNCTIONS
 pj-uv-init
 pj-is-latlong
 pj-pr-list
 pj-init-plus
 pj-transform)

;; Load the module extension
(load-extension "libguile-proj" "scm_init_proj")
;; End
