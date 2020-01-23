/* ----------------------------------------------------------------
 * geodesic_guile.c 
 *
 * This file is part of GUILE-PROJ
 *
 * Copyright (C) 2018 by Matthew Love <matthew.love@colorado.edu>
 * GUILE-PROJ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GUILE-PROJ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GUILE-PROJ.  If not, see <http://www.gnu.org/licenses/>.
 *
 * guile-proj is now depedent on guile 2.2, using the new
 * foreign functions interface.
 *
 * TODO: Error checking
 * --------------------------------------------------------------*/

#include <libguile.h>
#include "geodesic.h"

/*
 *  Geod Pj_Geodesic Structure
 */
struct pj_geodesic
{
  struct geod_geodesic geodesic_id;
  SCM name;
  SCM update_func;
};

static SCM pj_geodesic_type;

void
init_pj_geodesic_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("pj_geodesic");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;

  pj_geodesic_type = scm_make_foreign_object_type (name, slots, finalizer);
}

SCM_DEFINE (make_pj_geodesic, "make-geodesic", 1, 0, 0,
	    (SCM name),
	    "Make a geodesic object.")
{
  struct pj_geodesic *pj_geodesic;
  struct geod_geodesic c_pj_geodesic;
 
  /* Allocate the `struct projuv'.  Because we
     use scm_gc_malloc, this memory block will
     be automatically reclaimed when it becomes
     inaccessible, and its members will be traced
     by the garbage collector.  */
  pj_geodesic = (struct pj_geodesic *)
    scm_gc_malloc (sizeof (struct pj_geodesic), "pj_geodesic");

  pj_geodesic->geodesic_id = c_pj_geodesic;

  pj_geodesic->name = name;
  pj_geodesic->update_func = SCM_BOOL_F;

  /* Now wrap the struct projuv* in a new foreign
     object, and return that object.  */
  return scm_make_foreign_object_1 (pj_geodesic_type, pj_geodesic);
}

/*
 *  Geod geodesic_line structure
 */
struct pj_geodesicline
{
  struct geod_geodesicline geodesicline_id;
  SCM name;
  SCM update_func;
};

static SCM pj_geodesicline_type;

void
init_pj_geodesicline_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("pj_geodesicline");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;

  pj_geodesicline_type = scm_make_foreign_object_type (name, slots, finalizer);
}

SCM_DEFINE (make_pj_geodesicline, "make-geodesic-line", 1, 0, 0,
	    (SCM name),
	    "Make a geodesic line object")
{
  struct pj_geodesicline *pj_geodesicline;
  struct geod_geodesicline c_pj_geodesicline;
 
  /* Allocate the `struct projuv'.  Because we
     use scm_gc_malloc, this memory block will
     be automatically reclaimed when it becomes
     inaccessible, and its members will be traced
     by the garbage collector.  */
  pj_geodesicline = (struct pj_geodesicline *)
    scm_gc_malloc (sizeof (struct pj_geodesicline), "pj_geodesicline");

  pj_geodesicline->geodesicline_id = c_pj_geodesicline;

  pj_geodesicline->name = name;
  pj_geodesicline->update_func = SCM_BOOL_F;

  /* Now wrap the struct projuv* in a new foreign
     object, and return that object.  */
  return scm_make_foreign_object_1 (pj_geodesicline_type, pj_geodesicline);
}


SCM_DEFINE (geod_init_wrapper, "geod-init", 3, 0, 0,
	    (SCM pj_geodesic_ob, SCM s_a, SCM s_f),
	    "Initialize a geodesic object. Input is the geodesic object and the desired ellipsoid values of Major-Axis S_A and Flattening S_F")
{
  struct geod_geodesic c_geod_geodesic;
  struct pj_geodesic *pj_geodesic;
  double a, f;

  a = scm_to_double(s_a);
  f = scm_to_double(s_f);

  scm_assert_foreign_object_type (pj_geodesic_type, pj_geodesic_ob);
  pj_geodesic = scm_foreign_object_ref (pj_geodesic_ob, 0);
  c_geod_geodesic = pj_geodesic->geodesic_id;
  
  geod_init(&c_geod_geodesic, a, f);

  pj_geodesic->geodesic_id = c_geod_geodesic;
  
  return SCM_BOOL_T;
}

SCM_DEFINE (geod_init_or, "geod-init/", 2, 0, 0,
	    (SCM s_a, SCM s_f),
	    "Initialize a geodesic object. Input is the desired ellipsoid values of Major-Axis S_A and Flattening S_F")
{
  struct geod_geodesic c_geod_geodesic;
  struct pj_geodesic *pj_geodesic;
  double a, f;

  a = scm_to_double(s_a);
  f = scm_to_double(s_f);

  pj_geodesic = (struct pj_geodesic *)
    scm_gc_malloc (sizeof (struct pj_geodesic), "pj_geodesic");

  pj_geodesic->name = scm_from_locale_string("pj-geodesic");
  pj_geodesic->update_func = SCM_BOOL_F;
  
  geod_init(&c_geod_geodesic, a, f);

  pj_geodesic->geodesic_id = c_geod_geodesic;

  return scm_make_foreign_object_1 (pj_geodesic_type, pj_geodesic);
}

SCM_DEFINE (geod_direct_wrapper, "geod-direct", 5, 0, 0,
	    (SCM pj_geodesic_ob, SCM s_lat1, SCM s_lon1, SCM s_azi1, SCM s_s12),
	    "General Inverse. Get geodesic inverse for two points.")
{
  struct geod_geodesic c_geod_geodesic;
  struct pj_geodesic *pj_geodesic;
  double lat1, lat2, lon1, lon2, azi1, azi2, s12;

  lat1 = scm_to_double(s_lat1);
  lon1 = scm_to_double(s_lon1);
  azi1 = scm_to_double(s_azi1);
  s12 = scm_to_double(s_s12);
  
  scm_assert_foreign_object_type (pj_geodesic_type, pj_geodesic_ob);
  pj_geodesic = scm_foreign_object_ref (pj_geodesic_ob, 0);
  c_geod_geodesic = pj_geodesic->geodesic_id;

  geod_direct(&c_geod_geodesic, lat1, lon1, azi1, s12, &lat2, &lon2, &azi2);

  return scm_list_3(scm_from_double(lat2), scm_from_double(lon2), scm_from_double(azi2));
}

SCM_DEFINE (geod_inverse_wrapper, "geod-inverse", 5, 0, 0,
	    (SCM pj_geodesic_ob, SCM s_lat1, SCM s_lon1, SCM s_lat2, SCM s_lon2),
	    "Inverse. Get geodesic inverse for two points.")
{
  struct geod_geodesic c_geod_geodesic;
  struct pj_geodesic *pj_geodesic;
  double lat1, lat2, lon1, lon2, azi1, azi2, s12;

  lat1 = scm_to_double(s_lat1);
  lat2 = scm_to_double(s_lat2);
  lon1 = scm_to_double(s_lon1);
  lon2 = scm_to_double(s_lon2);
  
  scm_assert_foreign_object_type (pj_geodesic_type, pj_geodesic_ob);
  pj_geodesic = scm_foreign_object_ref (pj_geodesic_ob, 0);
  c_geod_geodesic = pj_geodesic->geodesic_id;

  geod_inverse(&c_geod_geodesic, lat1, lon1, lat2, lon2, &s12, &azi1, &azi2);

  return scm_list_3(scm_from_double(s12), scm_from_double(azi1), scm_from_double(azi2));
}

SCM_DEFINE (geod_geninverse_wrapper, "geod-geninverse", 5, 0, 0,
	    (SCM pj_geodesic_ob, SCM s_lat1, SCM s_lon1, SCM s_lat2, SCM s_lon2),
	    "General Inverse. Get geodesic inverse for two points.")
{
  struct geod_geodesic c_geod_geodesic;
  struct pj_geodesic *pj_geodesic;
  double lat1, lat2, lon1, lon2, azi1, azi2, s12, m12, M12, M21, S12, a12;

  lat1 = scm_to_double(s_lat1);
  lat2 = scm_to_double(s_lat2);
  lon1 = scm_to_double(s_lon1);
  lon2 = scm_to_double(s_lon2);
  
  scm_assert_foreign_object_type (pj_geodesic_type, pj_geodesic_ob);
  pj_geodesic = scm_foreign_object_ref (pj_geodesic_ob, 0);
  c_geod_geodesic = pj_geodesic->geodesic_id;

  a12 = geod_geninverse(&c_geod_geodesic, lat1, lon1, lat2, lon2, &s12, &azi1, &azi2, &m12, &M12, &M21, &S12);

  return scm_list_n(scm_from_double(s12), scm_from_double(azi1), scm_from_double(azi2), scm_from_double(m12), scm_from_double(M12), scm_from_double(M21), scm_from_double(S12), SCM_UNDEFINED);
}

SCM_DEFINE (geod_lineinit_wrapper, "geod-line-init", 4, 0, 0,
	    (SCM pj_geodesic_ob, SCM s_lat1, SCM s_lon1, SCM s_azi1),
	    "Initialize a geodesic line.")
{
  struct geod_geodesic c_geod_geodesic;
  struct pj_geodesic *pj_geodesic;
  struct geod_geodesicline c_geod_geodesicline;
  struct pj_geodesicline *pj_geodesicline;
  double lat1, lon1, azi1;

  lat1 = scm_to_double(s_lat1);
  lon1 = scm_to_double(s_lon1);
  azi1 = scm_to_double(s_azi1);

  scm_assert_foreign_object_type (pj_geodesic_type, pj_geodesic_ob);
  pj_geodesic = scm_foreign_object_ref (pj_geodesic_ob, 0);
  c_geod_geodesic = pj_geodesic->geodesic_id;

  pj_geodesicline = (struct pj_geodesicline *)
    scm_gc_malloc (sizeof (struct pj_geodesicline), "pj_geodesicline");

  pj_geodesicline->name = scm_from_locale_string("pj-geodesicline");
  pj_geodesicline->update_func = SCM_BOOL_F;
  
  geod_lineinit(&c_geod_geodesicline, &c_geod_geodesic, lat1, lon1, azi1, 0);

  pj_geodesicline->geodesicline_id = c_geod_geodesicline;

  return scm_make_foreign_object_1 (pj_geodesicline_type, pj_geodesicline);
}

SCM_DEFINE (geod_inverseline_wrapper, "geod-inverse-line", 5, 0, 0,
	    (SCM pj_geodesic_ob, SCM s_lat1, SCM s_lon1, SCM s_lat2, SCM s_lon2),
	    "Initialize a geodesic line.")
{  
  struct geod_geodesic c_geod_geodesic;
  struct pj_geodesic *pj_geodesic;
  struct geod_geodesicline c_geod_geodesicline;
  struct pj_geodesicline *pj_geodesicline;
  double lat1, lon1, lat2, lon2;

  lat1 = scm_to_double(s_lat1);
  lon1 = scm_to_double(s_lon1);
  lat2 = scm_to_double(s_lat2);
  lon2 = scm_to_double(s_lon2);

  scm_assert_foreign_object_type (pj_geodesic_type, pj_geodesic_ob);
  pj_geodesic = scm_foreign_object_ref (pj_geodesic_ob, 0);
  c_geod_geodesic = pj_geodesic->geodesic_id;

  pj_geodesicline = (struct pj_geodesicline *)
    scm_gc_malloc (sizeof (struct pj_geodesicline), "pj_geodesicline");

  pj_geodesicline->name = scm_from_locale_string("pj-geodesicline");
  pj_geodesicline->update_func = SCM_BOOL_F;
  
  geod_inverseline(&c_geod_geodesicline, &c_geod_geodesic, lat1, lon1, lat2, lon2, 0);

  pj_geodesicline->geodesicline_id = c_geod_geodesicline;

  return scm_make_foreign_object_1 (pj_geodesicline_type, pj_geodesicline);
}

SCM_DEFINE (geod_directline_wrapper, "geod-direct-line", 5, 0, 0,
	    (SCM pj_geodesic_ob, SCM s_lat1, SCM s_lon1, SCM s_azi1, SCM s_s12),
	    "Initialize a geodesic line.")
{
  struct geod_geodesic c_geod_geodesic;
  struct pj_geodesic *pj_geodesic;
  struct geod_geodesicline c_geod_geodesicline;
  struct pj_geodesicline *pj_geodesicline;
  double lat1, lon1, azi1, s12;

  lat1 = scm_to_double(s_lat1);
  lon1 = scm_to_double(s_lon1);
  azi1 = scm_to_double(s_azi1);
  s12 = scm_to_double(s_s12);

  scm_assert_foreign_object_type (pj_geodesic_type, pj_geodesic_ob);
  pj_geodesic = scm_foreign_object_ref (pj_geodesic_ob, 0);
  c_geod_geodesic = pj_geodesic->geodesic_id;

  pj_geodesicline = (struct pj_geodesicline *)
    scm_gc_malloc (sizeof (struct pj_geodesicline), "pj_geodesicline");

  pj_geodesicline->name = scm_from_locale_string("pj-geodesicline");
  pj_geodesicline->update_func = SCM_BOOL_F;
  
  geod_directline(&c_geod_geodesicline, &c_geod_geodesic, lat1, lon1, azi1, s12, 0);

  pj_geodesicline->geodesicline_id = c_geod_geodesicline;

  return scm_make_foreign_object_1 (pj_geodesicline_type, pj_geodesicline);
}

SCM_DEFINE (geod_position_wrapper, "geod-position", 2, 0, 0,
	    (SCM pj_geodesicline_ob, SCM s_s12),
	    "Get the position of a point at a distace along a geodesic line.")
{
  struct geod_geodesicline c_geod_geodesicline;
  struct pj_geodesicline *pj_geodesicline;
  double s12 = scm_to_double(s_s12);
  double lat2, lon2, azi2;

  scm_assert_foreign_object_type (pj_geodesicline_type, pj_geodesicline_ob);
  pj_geodesicline = scm_foreign_object_ref (pj_geodesicline_ob, 0);
  c_geod_geodesicline = pj_geodesicline->geodesicline_id;
  
  geod_position(&c_geod_geodesicline, s12, &lat2, &lon2, &azi2);

  return scm_list_3(scm_from_double(lat2), scm_from_double(lon2), scm_from_double(azi2));
}

void
scm_init_geod()
{
  init_pj_geodesic_type();
  init_pj_geodesicline_type();
  scm_c_define("geodesic-version-major", scm_from_int(GEODESIC_VERSION_MAJOR));
  scm_c_define("geodesic-version-minor", scm_from_int(GEODESIC_VERSION_MINOR));
  scm_c_define("geodesic-version-patch", scm_from_int(GEODESIC_VERSION_PATCH));
  

#ifndef SCM_MAGIC_SNARFER
#include "geodesic_guile.x"
#endif
}
