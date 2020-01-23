/* ----------------------------------------------------------------
 * pj_guile.c 
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
 * --------------------------------------------------------------*/

#include <libguile.h>
#include "projects.h"

/*
 *  Version Info
 */

static char vcid[] = "0.2.1";

SCM_DEFINE (pj_strerrno_wrapper, "pj-strerrno", 1, 0, 0,
	    (SCM s_errno),
	    "return the string of the given errno.")
{
  int errno = scm_to_int(s_errno);
  char* pj_err;
  pj_err = pj_strerrno(errno);
  return scm_from_locale_string(pj_err);
}

SCM_DEFINE (pj_get_errno_wrapper, "pj-errno", 0, 0, 0,
	    (),
	    "return the last errno.")
{
  int *errno;
  errno = pj_get_errno_ref();
  return scm_from_int(*errno);
}

SCM_DEFINE (pj_get_errno_ref_wrapper, "pj-get-errno-ref", 0, 0, 0,
	    (),
	    "print the last errno.")
{
  int *errno;
  errno = pj_get_errno_ref();
  fprintf(stderr,"%d\n",errno);
  return SCM_BOOL_T;
}

/*
 * ProjUV struct
 */

struct projuv
{
  projUV projuv_id;
  SCM name;
  SCM update_func;
};

static SCM projuv_type;

void
init_projuv_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("projUV");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;
  projuv_type = scm_make_foreign_object_type (name, slots, finalizer);
}

SCM_DEFINE (make_projuv, "scm->pjuv", 2, 0, 0,
	    (SCM s_u, SCM s_v),
	    "Make a proj UV object. Input longitude and latitude.")
{
  struct projuv *projuv;
  projUV c_projuv;
  double u = scm_to_double (s_u);
  double v = scm_to_double (s_v);
  
  projuv = (struct projuv *)
    scm_gc_malloc (sizeof (struct projuv), "projuv");

  c_projuv.u = u;
  c_projuv.v = v;
  projuv->projuv_id = c_projuv;
  projuv->name = scm_from_locale_string("projUV");
  projuv->update_func = SCM_BOOL_F;

  return scm_make_foreign_object_1 (projuv_type, projuv);
}

SCM_DEFINE (get_projuv_uv, "pjuv->scm", 1, 0, 0,
	    (SCM projuv_ob),
	    "Return the projuv object as a list '(x . y)")
{
  int status;
  projUV c_projuv;
  struct projuv *projuv;

  scm_assert_foreign_object_type (projuv_type, projuv_ob);
  projuv = scm_foreign_object_ref (projuv_ob, 0);
  c_projuv = projuv->projuv_id;

  return scm_list_2(scm_from_double(c_projuv.u),\
		    scm_from_double(c_projuv.v));
}

/*
 *  ProjUVW struct
 */

struct projuvw
{
  projUVW projuvw_id;
  SCM name;
  SCM update_func;
};

static SCM projuvw_type;

void
init_projuvw_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("projUVW");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;
  projuvw_type = scm_make_foreign_object_type (name, slots, finalizer);
}

SCM_DEFINE (make_projuvw, "scm->pjuvw", 3, 0, 0,
	    (SCM s_u, SCM s_v, SCM s_w),
	    "Make a proj UV object. Input longitude and latitude.")
{
  struct projuvw *projuvw;
  projUVW c_projuvw;
  double u = scm_to_double (s_u);
  double v = scm_to_double (s_v);
  double w = scm_to_double (s_w);
  
  projuvw = (struct projuvw *)
    scm_gc_malloc (sizeof (struct projuvw), "projuvw");

  c_projuvw.u = u;
  c_projuvw.v = v;
  c_projuvw.w = w;
  projuvw->projuvw_id = c_projuvw;
  projuvw->name = scm_from_locale_string("projUVW");
  projuvw->update_func = SCM_BOOL_F;

  return scm_make_foreign_object_1 (projuvw_type, projuvw);
}

SCM_DEFINE (get_projuvw_uvw, "pjuvw->scm", 1, 0, 0,
	    (SCM projuvw_ob),
	    "Return the projuvw object as a list '(x  y z)")
{
  int status;
  projUVW c_projuvw;
  struct projuvw *projuvw;

  scm_assert_foreign_object_type (projuvw_type, projuvw_ob);
  projuvw = scm_foreign_object_ref (projuvw_ob, 0);
  c_projuvw = projuvw->projuvw_id;

  return scm_list_3(scm_from_double(c_projuvw.u),\
		     scm_from_double(c_projuvw.v),\
		     scm_from_double(c_projuvw.w));
}

/*
  ProjPJ struct
*/

struct projpj
{
  projPJ projpj_id;
  SCM proj_string;
  SCM name;
  SCM update_func;
};

static SCM projpj_type;

void
init_projpj_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("projPJ");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;
  projpj_type = scm_make_foreign_object_type (name, slots, finalizer);
}

SCM_DEFINE (make_projpj, "make-pjob", 1, 0, 0,
	    (SCM name),
	    "Create an empty proj object.")
{
  struct projpj *projpj;
  projPJ c_projpj;
  init_projpj_type();
 
  /* Allocate the `struct projuv'.  Because we
     use scm_gc_malloc, this memory block will
     be automatically reclaimed when it becomes
     inaccessible, and its members will be traced
     by the garbage collector.  */
  projpj = (struct projpj *)
    scm_gc_malloc (sizeof (struct projpj), "projpj");

  projpj->projpj_id = c_projpj;
  projpj->name = name;
  projpj->update_func = SCM_BOOL_F;

  /* Now wrap the struct projuv* in a new foreign
     object, and return that object.  */
  return scm_make_foreign_object_1 (projpj_type, projpj);
}

SCM_DEFINE (pj_init_wrapper, "pj-init", 1, 0, 0,
	    (SCM scm_args_list),
	    "Initialize a proj object based on the input projection string list. e.g. '(pj-init '(\"+proj=longlat\") (\"+ellps=WGS84\")) ")
{
  int i;
  int arg_len;
  projPJ c_projpj;
  struct projpj *projpj;  
  
  arg_len = scm_to_int(scm_length(scm_args_list));
  char *args[arg_len];
  
  for (i = 0; i < arg_len; i++) {
    args[i] = scm_to_locale_string(scm_list_ref(scm_args_list, scm_from_int(i)));
  }

  // projpj
  projpj = (struct projpj *) scm_gc_malloc (sizeof (struct projpj), "projpj");

  if (!(c_projpj = pj_init(arg_len, args))) {
    fprintf (stderr,"guile_proj: failed to initialize projection:\n");
    fprintf (stderr,"guile_proj: %s\n", pj_strerrno(pj_errno));
    return SCM_BOOL_F;
  }

  projpj->projpj_id = c_projpj;
  projpj->name = scm_from_locale_string ("projpj");
  projpj->proj_string = scm_from_locale_string ("None");
  projpj->update_func = SCM_BOOL_F;

  return scm_make_foreign_object_1 (projpj_type, projpj);
}

SCM_DEFINE (pj_init_plus_wrapper, "pj-init+", 1, 0, 0,
	    (SCM scm_param),
	    "Initialize a proj object based on the input projection string. e.g. '(pj-init+ \"+proj=longlat +ellps=WGS84\") ")
{
  const char *c_param;
  size_t length;
  projPJ c_projpj;
  struct projpj *projpj;
  
  if (scm_is_true (scm_string_p (scm_param))) {
    c_param = scm_to_locale_string (scm_param);
  } 
  else {
    fprintf (stderr,"guile_proj: projection parameter: %a is not a string\n", c_param);
  }
  
  // projpj
  projpj = (struct projpj *) scm_gc_malloc (sizeof (struct projpj), "projpj");

  if (!(c_projpj = pj_init_plus(c_param))) {
    fprintf (stderr,"guile_proj: failed to initialize projection string: %s\n", c_param);
    fprintf (stderr,"guile_proj: %s\n", pj_strerrno(pj_errno));
    return SCM_BOOL_F;
  }

  projpj->name = scm_from_locale_string ("projpj");
  projpj->projpj_id = 0;
  projpj->update_func = SCM_BOOL_F;  
  projpj->proj_string = scm_param;
  projpj->projpj_id = c_projpj;

  return scm_make_foreign_object_1 (projpj_type, projpj);
}

SCM_DEFINE (pj_pr_list_wrapper, "pj-pr-list", 1, 0, 0,
	    (SCM projpj_ob),
	    "Get the parameters of the proj object.")
{
  int status;
  projPJ c_projpj;
  struct projpj *projpj;  

  scm_assert_foreign_object_type (projpj_type, projpj_ob);
  projpj = scm_foreign_object_ref (projpj_ob, 0);
  c_projpj = projpj->projpj_id;
  
  pj_pr_list(c_projpj);

  return SCM_UNSPECIFIED;
}

SCM_DEFINE (pj_get_def_wrapper, "pj-get-def", 1, 0, 0,
	    (SCM projpj_ob),
	    "Get the definition of the projection of the proj object.")
{
  int status;
  projPJ c_projpj;

  struct projpj *projpj;
  
  scm_assert_foreign_object_type (projpj_type, projpj_ob);
  projpj = scm_foreign_object_ref (projpj_ob, 0);
  c_projpj = projpj->projpj_id;
  
  char *pjdef;
  if (!(pjdef = pj_get_def(c_projpj, status))) {
    fprintf (stderr,"guile_proj: %s\n", pj_strerrno(pj_errno));
    return SCM_BOOL_F;
  }

  return scm_from_locale_string(pjdef);
}

SCM_DEFINE (pj_free_wrapper, "pj-free", 1, 0, 0,
	    (SCM projpj_ob),
	    "Free proj object.")
{
  int status;
  projPJ c_projpj;

  struct projpj *projpj;
  
  scm_assert_foreign_object_type (projpj_type, projpj_ob);
  projpj = scm_foreign_object_ref (projpj_ob, 0);
  c_projpj = projpj->projpj_id;

  pj_free(c_projpj);
  
  return SCM_BOOL_T;
}

SCM_DEFINE (pj_fwd_wrapper, "pj-fwd", 2, 0, 0,
	    (SCM projuv_ob, SCM projpj_ob),
	    "Project the uv object to the projection of the proj object.")
{
  int status;
  projPJ c_projpj;
  projUV c_projuv;
  struct projpj *projpj;
  struct projuv *projuv;  

  scm_assert_foreign_object_type (projpj_type, projpj_ob);
  projpj = scm_foreign_object_ref (projpj_ob, 0);
  c_projpj = projpj->projpj_id;

  scm_assert_foreign_object_type (projuv_type, projuv_ob);
  projuv = scm_foreign_object_ref (projuv_ob, 0);
  c_projuv = projuv->projuv_id;

  projuv->projuv_id = pj_fwd(c_projuv, c_projpj);
  
  return SCM_UNSPECIFIED;
}

SCM_DEFINE (pj_fwd_list_wrapper, "pj-fwd->scm", 2, 0, 0,
	    (SCM xylist, SCM projpj_ob),
	    "Project points in xylist `(lon . lat) on to the projection of the proj object and return a list `(x . y).")
{
  int status;
  projPJ c_projpj;
  projUV c_projuv;
  struct projpj *projpj;

  c_projuv.u = scm_to_double(scm_car(xylist));
  c_projuv.v = scm_to_double(scm_cadr(xylist));
  
  scm_assert_foreign_object_type (projpj_type, projpj_ob);
  projpj = scm_foreign_object_ref (projpj_ob, 0);
  c_projpj = projpj->projpj_id;

  c_projuv = pj_fwd(c_projuv, c_projpj);
  
  return scm_list_2(scm_from_double(c_projuv.u), \
		    scm_from_double(c_projuv.v));
}

SCM_DEFINE (pj_inv_wrapper, "pj-inv", 2, 0, 0,
	    (SCM projuv_ob, SCM projpj_ob),
	    "Remove the projection from the uv object based on the projection of the proj object.")
{
  int status;
  projPJ c_projpj;
  projUV c_projuv;
  struct projpj *projpj;
  struct projuv *projuv;  

  scm_assert_foreign_object_type (projpj_type, projpj_ob);
  projpj = scm_foreign_object_ref (projpj_ob, 0);
  c_projpj = projpj->projpj_id;

  scm_assert_foreign_object_type (projuv_type, projuv_ob);
  projuv = scm_foreign_object_ref (projuv_ob, 0);
  c_projuv = projuv->projuv_id;

  projuv->projuv_id = pj_inv(c_projuv, c_projpj);
  
  return SCM_UNSPECIFIED;
}

SCM_DEFINE (pj_inv_list_wrapper, "pj-inv->scm", 2, 0, 0,
	    (SCM xylist, SCM projpj_ob),
	    "Remove the projection from the points in xylist `(x . y) based on the projection of the proj object and return a list `(lon . lat).")
{
  int status;
  projPJ c_projpj;
  projUV c_projuv;
  struct projpj *projpj;

  c_projuv.u = scm_to_double(scm_car(xylist));
  c_projuv.v = scm_to_double(scm_cadr(xylist));
  
  scm_assert_foreign_object_type (projpj_type, projpj_ob);
  projpj = scm_foreign_object_ref (projpj_ob, 0);
  c_projpj = projpj->projpj_id;

  pj_inv(c_projuv, c_projpj);
  
  return scm_list_2(scm_from_double(c_projuv.u), \
		    scm_from_double(c_projuv.v));
}

SCM_DEFINE (pj_fwd3d_wrapper, "pj-fwd3d", 2, 0, 0,
	    (SCM projuvw_ob, SCM projpj_ob),
	    "Project the uvw object to the projection of the proj object.")
{
  int status;
  projPJ c_projpj;
  projUVW c_projuvw;
  struct projpj *projpj;
  struct projuvw *projuvw;  

  scm_assert_foreign_object_type (projpj_type, projpj_ob);
  projpj = scm_foreign_object_ref (projpj_ob, 0);
  c_projpj = projpj->projpj_id;

  scm_assert_foreign_object_type (projuvw_type, projuvw_ob);
  projuvw = scm_foreign_object_ref (projuvw_ob, 0);
  c_projuvw = projuvw->projuvw_id;

  projuvw->projuvw_id = pj_fwd3d(c_projuvw, c_projpj);
  
  return SCM_UNSPECIFIED;
}

SCM_DEFINE (pj_inv3d_wrapper, "pj-inv3d", 2, 0, 0,
	    (SCM projuvw_ob, SCM projpj_ob),
	    "Remove the projection from the uvw object based on the projection of the proj object.")
{
  int status;
  projPJ c_projpj;
  projUVW c_projuvw;
  struct projpj *projpj;
  struct projuvw *projuvw;  

  scm_assert_foreign_object_type (projpj_type, projpj_ob);
  projpj = scm_foreign_object_ref (projpj_ob, 0);
  c_projpj = projpj->projpj_id;

  scm_assert_foreign_object_type (projuvw_type, projuvw_ob);
  projuvw = scm_foreign_object_ref (projuvw_ob, 0);
  c_projuvw = projuvw->projuvw_id;

  projuvw->projuvw_id = pj_inv3d(c_projuvw, c_projpj);
  
  return SCM_UNSPECIFIED;
}

SCM_DEFINE (pj_transform_wrapper, "pj-transform", 7, 0, 0,
	    (SCM projpj_src_ob, SCM projpj_dst_ob, \
	     SCM scm_ptcnt, SCM scm_ptoffset, \
	     SCM scm_x, SCM scm_y, SCM scm_z),
	    "Transform xyz data based on the src and dst proj objects.")
{
  double x,y,z;
  int c_ptoffset, status;
  long c_ptcnt;
  projPJ c_src_projpj, c_dst_projpj;
  //projUV data;
  
  struct projpj *pj_src_projpj;
  struct projpj *pj_dst_projpj;

  c_ptoffset = scm_to_int(scm_ptoffset);
  c_ptcnt = scm_to_long(scm_ptcnt);

  scm_assert_foreign_object_type (projpj_type, projpj_src_ob);
  pj_src_projpj = scm_foreign_object_ref (projpj_src_ob, 0);
  c_src_projpj = pj_src_projpj->projpj_id;

  scm_assert_foreign_object_type (projpj_type, projpj_dst_ob);
  pj_dst_projpj = scm_foreign_object_ref (projpj_dst_ob, 0);
  c_dst_projpj = pj_dst_projpj->projpj_id;

  x = scm_to_double(scm_x);
  y = scm_to_double(scm_y);
  
  if (c_src_projpj->is_latlong) {
    x *= DEG_TO_RAD;
    y *= DEG_TO_RAD;
  }
  
  z = scm_to_double(scm_z);
  
  status = pj_transform(c_src_projpj, c_dst_projpj, 1, 0, &x, &y, &z);

  if (status !=  0) {
    fprintf(stderr,"guile-proj: %s\n", pj_strerrno(status));
    return SCM_BOOL_F;
  }
  
  if (c_dst_projpj->is_latlong) {
    x *= RAD_TO_DEG;
    y *= RAD_TO_DEG;
  }  
  return scm_list_3 (scm_from_double(x),\
		     scm_from_double(y),\
		     scm_from_double(z));
}

SCM_DEFINE (pj_datum_transform_wrapper, "pj-datum-transform", 7, 0, 0,
	    (SCM projpj_src_ob, SCM projpj_dst_ob, \
	     SCM scm_ptcnt, SCM scm_ptoffset, \
	     SCM scm_x, SCM scm_y, SCM scm_z),
	    "transform xyz data based on the proj objects.")
{
  double x,y,z;
  int c_ptoffset, status;
  long c_ptcnt;
  projPJ c_src_projpj, c_dst_projpj;
  //projUV data;
  
  struct projpj *pj_src_projpj;
  struct projpj *pj_dst_projpj;

  c_ptoffset = scm_to_int(scm_ptoffset);
  c_ptcnt = scm_to_long(scm_ptcnt);

  scm_assert_foreign_object_type (projpj_type, projpj_src_ob);
  pj_src_projpj = scm_foreign_object_ref (projpj_src_ob, 0);
  c_src_projpj = pj_src_projpj->projpj_id;

  scm_assert_foreign_object_type (projpj_type, projpj_dst_ob);
  pj_dst_projpj = scm_foreign_object_ref (projpj_dst_ob, 0);
  c_dst_projpj = pj_dst_projpj->projpj_id;

  x = scm_to_double(scm_x);
  y = scm_to_double(scm_y);
  
  if (c_src_projpj->is_latlong) {
    x *= DEG_TO_RAD;
    y *= DEG_TO_RAD;
  }
  
  z = scm_to_double(scm_z);
  
  status = pj_datum_transform(c_src_projpj, c_dst_projpj, 1, 0, &x, &y, &z);

  if (status !=  0) {
    fprintf(stderr,"guile-proj: %s\n", pj_strerrno(status));
    return SCM_BOOL_F;
  }
  
  if (c_dst_projpj->is_latlong) {
    x *= RAD_TO_DEG;
    y *= RAD_TO_DEG;
  }
  
  if (status !=  0)
    fprintf(stderr,"guile-proj: %s\n", pj_strerrno(status));
  return scm_list_3 (scm_from_double(x),\
		     scm_from_double(y),\
		     scm_from_double(z));
}

SCM_DEFINE (pj_compare_datums_wrapper, "pj-datums-eq?", 2, 0, 0,
	    (SCM projpj_src_ob, SCM projpj_dst_ob),
	    "Compare two proj objects.")
{
  int status;
  projPJ c_src_projpj, c_dst_projpj;
  struct projpj *pj_src_projpj;
  struct projpj *pj_dst_projpj;
  
  scm_assert_foreign_object_type (projpj_type, projpj_src_ob);
  pj_src_projpj = scm_foreign_object_ref (projpj_src_ob, 0);
  c_src_projpj = pj_src_projpj->projpj_id;
  
  scm_assert_foreign_object_type (projpj_type, projpj_dst_ob);
  pj_dst_projpj = scm_foreign_object_ref (projpj_src_ob, 0);
  c_dst_projpj = pj_dst_projpj->projpj_id;

  // Not sure what this function does
  status = pj_compare_datums( c_src_projpj, c_dst_projpj );
  fprintf(stderr,"%d\n",status);
    
  return SCM_UNSPECIFIED;
}

SCM_DEFINE (pj_latlong_from_proj_wrapper, "pj->latlong", 1, 0, 0,
	    (SCM projpj_ob),
	    "Transform a proj object to latlong.")
{  
  int status;
  projPJ c_projpj;
  struct projpj *projpj;
  
  scm_assert_foreign_object_type (projpj_type, projpj_ob);
  projpj = scm_foreign_object_ref (projpj_ob, 0);
  c_projpj = projpj->projpj_id;
  
  projpj->projpj_id = pj_latlong_from_proj( c_projpj );

  return SCM_UNSPECIFIED;
}

SCM_DEFINE (pj_is_latlong_wrapper, "pj-latlong?", 1, 0, 0,
	    (SCM projpj_ob),
	    "Return true if the proj object is lat/long.")
{
  int status;
  projPJ c_projpj;
  struct projpj *projpj;  

  scm_assert_foreign_object_type (projpj_type, projpj_ob);
  projpj = scm_foreign_object_ref (projpj_ob, 0);
  c_projpj = projpj->projpj_id;

  status = pj_is_latlong(c_projpj);
  
  return scm_from_bool(status);
}

SCM_DEFINE (pj_is_geocent_wrapper, "pj-geocent?", 1, 0, 0,
	    (SCM projpj_ob),
	    "Return true if the proj object is gecentric.")
{
  int status;
  projPJ c_projpj;
  struct projpj *projpj;  

  scm_assert_foreign_object_type (projpj_type, projpj_ob);
  projpj = scm_foreign_object_ref (projpj_ob, 0);
  c_projpj = projpj->projpj_id;

  status = pj_is_geocent(c_projpj);
  
  return scm_from_bool(status);
}

SCM_DEFINE (set_rtodms_wrapper, "pj-set-r->dms", 1, 0, 0,
	    (SCM s_u),
	    "Set the dms precision")
{
  set_rtodms(scm_to_int(s_u),1);
  return SCM_BOOL_T;
}

SCM_DEFINE (dmstor_wrapper, "pj-dms->r", 1, 0, 0,
	    (SCM s_str),
	    "transform a dms string to radians")
{
  double out_u;
  char* s = scm_to_locale_string(s_str);
  if(out_u = dmstor(s, &s)) return scm_from_double(out_u);
  else return scm_from_int(0);
}

SCM_DEFINE (rtodms_wrapper, "pj-r->dms", 3, 0, 0,
	    (SCM s_x, SCM s_u, SCM s_v),
	    "transform a radian S_X to a dms string using S_U (#\E/#\S) or S_V (#\W/#\N) as direction")
{
  char pline[40];
  double x;
  int u, v;

  if ((scm_char_p(s_u) == SCM_BOOL_T) && (scm_char_p(s_v) == SCM_BOOL_T) && (scm_is_number(s_x))) {
    x = scm_to_double(s_x);
    u = scm_to_int(scm_char_to_integer(s_u));
    v = scm_to_int(scm_char_to_integer(s_v));
  } else return SCM_BOOL_F;
  
  if (!(rtodms(pline,x, u, v))) return SCM_BOOL_F;
  else return scm_from_locale_string(pline);
}

/*
  PJ_LIST struct
*/

struct projpj_list
{
  struct PJ_LIST *projpj_list_id;
  SCM name;
  SCM update_func;
};

static SCM projpj_list_type;

void
init_projpj_list_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("projPJ_LIST");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;

  projpj_list_type = scm_make_foreign_object_type (name, slots, finalizer);
}

SCM_DEFINE (make_projpj_list, "make-projpj-list", 0, 0, 0,
	    (),
	    "Make a pj list object.")  
{
  struct projpj_list *projpj_list;
  struct PJ_LIST *c_projpj_list;

  projpj_list = (struct projpj_list *)
    scm_gc_malloc (sizeof (struct projpj_list), "projpj_list");

  projpj_list->projpj_list_id = c_projpj_list;

  projpj_list->name = scm_from_locale_string("projPJ_LIST");
  projpj_list->update_func = SCM_BOOL_F;

  return scm_make_foreign_object_1 (projpj_list_type, projpj_list);
}

SCM_DEFINE (pj_get_list_ref_wrapper, "pj-get-list-ref", 0, 0, 0,
	    (),
	    "Initialize the list reference")
{
  struct projpj_list *projpj_list;
  struct PJ_LIST *c_projpj_list;

  /* Allocate the `struct projuv'.  Because we
     use scm_gc_malloc, this memory block will
     be automatically reclaimed when it becomes
     inaccessible, and its members will be traced
     by the garbage collector.  */
  projpj_list = (struct projpj_list *)
    scm_gc_malloc (sizeof (struct projpj_list), "projpj_list");

  c_projpj_list = pj_get_list_ref();
  
  projpj_list->projpj_list_id = c_projpj_list;

  projpj_list->name = scm_from_locale_string("projPJ_LIST");
  projpj_list->update_func = SCM_BOOL_F;

  /* Now wrap the struct projuv* in a new foreign
     object, and return that object.  */
  return scm_make_foreign_object_1 (projpj_list_type, projpj_list);
}

SCM_DEFINE (plus_plus_pj_list, "++pj-list", 1, 0, 0,
	    (SCM projpj_list_ob),
	    "increment the pj-list")
{
  int status;
  
  struct projpj_list *projpj_list;
  
  scm_assert_foreign_object_type (projpj_list_type, projpj_list_ob);
  projpj_list = scm_foreign_object_ref (projpj_list_ob, 0);
  ++projpj_list->projpj_list_id;

  return SCM_UNSPECIFIED;
}

SCM_DEFINE (pj_list_to_scm, "pj-list->scm", 1, 0, 0,
	    (SCM projpj_list_ob),
	    "return a list of the values associated with the current projpj list object")
{
  int status;
  char *prjid, *prjdescr;
  
  struct PJ_LIST *c_projpj_list;
  struct projpj_list *projpj_list;
  
  scm_assert_foreign_object_type (projpj_list_type, projpj_list_ob);
  projpj_list = scm_foreign_object_ref (projpj_list_ob, 0);
  c_projpj_list = projpj_list->projpj_list_id;
  
  prjid = c_projpj_list->id;
  prjdescr = *c_projpj_list->descr;
  
  if (prjid == NULL) return SCM_BOOL_F;
  else return scm_list_2 (scm_from_locale_string(prjid), scm_from_locale_string(prjdescr));
}

/*
  PJ_ELLPS struct
*/

struct projpj_ellps
{
  struct PJ_ELLPS *projpj_ellps_id;
  SCM name;
  SCM update_func;
};

static SCM projpj_ellps_type;

void
init_projpj_ellps_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("projPJ_ELLPS");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;

  projpj_ellps_type = scm_make_foreign_object_type (name, slots, finalizer);
}

SCM_DEFINE (make_projpj_ellps_list, "make-projpj-ellps", 0, 0, 0,
	    (),
	    "Make a pj ellps list object.")  
{
  struct projpj_ellps *projpj_ellps;
  struct PJ_ELLPS *c_projpj_ellps;

  projpj_ellps = (struct projpj_ellps *)
    scm_gc_malloc (sizeof (struct projpj_ellps), "projpj_ellps");

  projpj_ellps->projpj_ellps_id = c_projpj_ellps;
  projpj_ellps->name = scm_from_locale_string("projPJ_ELLPS");
  projpj_ellps->update_func = SCM_BOOL_F;

  return scm_make_foreign_object_1 (projpj_ellps_type, projpj_ellps);
}

SCM_DEFINE (pj_get_ellps_ref_wrapper, "pj-get-ellps-ref", 0, 0, 0,
	    (),
	    "Initialize the ellps list reference")
{
  struct projpj_ellps *projpj_ellps;
  struct PJ_ELLPS *c_projpj_ellps;

  projpj_ellps = (struct projpj_ellps *)
    scm_gc_malloc (sizeof (struct projpj_ellps), "projpj_ellps");

  c_projpj_ellps = pj_get_ellps_ref();
  
  projpj_ellps->projpj_ellps_id = c_projpj_ellps;
  projpj_ellps->name = scm_from_locale_string("projPJ_ELLPS");
  projpj_ellps->update_func = SCM_BOOL_F;

  return scm_make_foreign_object_1 (projpj_ellps_type, projpj_ellps);
}

SCM_DEFINE (plus_plus_pj_ellps, "++pj-ellps", 1, 0, 0,
	    (SCM projpj_ellps_ob),
	    "increment the pj-ellps list")
{
  int status;
  
  struct projpj_ellps *projpj_ellps;
  
  scm_assert_foreign_object_type (projpj_ellps_type, projpj_ellps_ob);
  projpj_ellps = scm_foreign_object_ref (projpj_ellps_ob, 0);
  ++projpj_ellps->projpj_ellps_id;

  return SCM_UNSPECIFIED;
}

SCM_DEFINE (pj_ellps_to_scm, "pj-ellps->scm", 1, 0, 0,
	    (SCM projpj_ellps_ob),
	    "return a list of the values associated with the current projpj ellps list object")
{
  int status;
  char *ellpsid, *ellpsmajor, *ellpsell, *ellpsname;
 
  struct PJ_ELLPS *c_projpj_ellps;
  struct projpj_ellps *projpj_ellps;
  
  scm_assert_foreign_object_type (projpj_ellps_type, projpj_ellps_ob);
  projpj_ellps = scm_foreign_object_ref (projpj_ellps_ob, 0);
  c_projpj_ellps = projpj_ellps->projpj_ellps_id;
  
  ellpsid = c_projpj_ellps->id;
  ellpsmajor = c_projpj_ellps->major;
  ellpsell = c_projpj_ellps->ell;
  ellpsname = c_projpj_ellps->name;
  
  if (ellpsid == NULL) return SCM_BOOL_F;
  else return scm_list_4(scm_from_locale_string(ellpsid), \
			 scm_from_locale_string(ellpsmajor), \
			 scm_from_locale_string(ellpsell), \
			 scm_from_locale_string(ellpsname));
}

/*
  PJ_UNITS struct
*/
struct projpj_units
{
  struct PJ_UNITS *projpj_units_id;
  SCM name;
  SCM update_func;
};

static SCM projpj_units_type;

void
init_projpj_units_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("projPJ_UNITS");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;

  projpj_units_type = scm_make_foreign_object_type (name, slots, finalizer);
}

SCM_DEFINE (make_projpj_units_list, "make-projpj-units", 0, 0, 0,
	    (),
	    "Make a pj units list object.")  
{
  struct projpj_units *projpj_units;
  struct PJ_UNITS *c_projpj_units;

  projpj_units = (struct projpj_units *)
    scm_gc_malloc (sizeof (struct projpj_units), "projpj_units");

  projpj_units->projpj_units_id = c_projpj_units;
  projpj_units->name = scm_from_locale_string("projPJ_UNITS");
  projpj_units->update_func = SCM_BOOL_F;

  return scm_make_foreign_object_1 (projpj_units_type, projpj_units);
}

SCM_DEFINE (pj_get_units_ref_wrapper, "pj-get-units-ref", 0, 0, 0,
	    (),
	    "Initialize the units list reference")
{
  struct projpj_units *projpj_units;
  struct PJ_UNITS *c_projpj_units;

  projpj_units = (struct projpj_units *)
    scm_gc_malloc (sizeof (struct projpj_units), "projpj_units");

  c_projpj_units = pj_get_units_ref();
  
  projpj_units->projpj_units_id = c_projpj_units;
  projpj_units->name = scm_from_locale_string("projPJ_UNITS");
  projpj_units->update_func = SCM_BOOL_F;

  return scm_make_foreign_object_1 (projpj_units_type, projpj_units);
}

SCM_DEFINE (plus_plus_pj_units, "++pj-units", 1, 0, 0,
	    (SCM projpj_units_ob),
	    "increment the pj-units list")
{
  int status;
  
  struct projpj_units *projpj_units;
  
  scm_assert_foreign_object_type (projpj_units_type, projpj_units_ob);
  projpj_units = scm_foreign_object_ref (projpj_units_ob, 0);
  ++projpj_units->projpj_units_id;

  return SCM_UNSPECIFIED;
}

SCM_DEFINE (pj_units_to_scm, "pj-units->scm", 1, 0, 0,
	    (SCM projpj_units_ob),
	    "return a list of the values associated with the current projpj units list object")
{
  int status;
  char *unitsid, *unitsto_meter, *unitsname;
    
  struct PJ_UNITS *c_projpj_units;
  struct projpj_units *projpj_units;
  
  scm_assert_foreign_object_type (projpj_units_type, projpj_units_ob);
  projpj_units = scm_foreign_object_ref (projpj_units_ob, 0);
  c_projpj_units = projpj_units->projpj_units_id;
  
  unitsid = c_projpj_units->id;
  unitsto_meter = c_projpj_units->to_meter;
  unitsname = c_projpj_units->name;
  
  if (unitsid == NULL) return SCM_BOOL_F;
  else return scm_list_3(scm_from_locale_string(unitsid), \
			 scm_from_locale_string(unitsto_meter), \
			 scm_from_locale_string(unitsname));
}

/*
  PJ_DATUMS struct
*/

struct projpj_datums
{
  struct PJ_DATUMS *projpj_datums_id;
  SCM name;
  SCM update_func;
};

static SCM projpj_datums_type;

void
init_projpj_datums_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("projPJ_DATUMS");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;

  projpj_datums_type = scm_make_foreign_object_type (name, slots, finalizer);
}

SCM_DEFINE (make_projpj_datums_list, "make-projpj-datums", 0, 0, 0,
	    (),
	    "Make a pj datums list object.")  
{
  struct projpj_datums *projpj_datums;
  struct PJ_DATUMS *c_projpj_datums;

  projpj_datums = (struct projpj_datums *)
    scm_gc_malloc (sizeof (struct projpj_datums), "projpj_datums");

  projpj_datums->projpj_datums_id = c_projpj_datums;

  projpj_datums->name = scm_from_locale_string("projPJ_DATUMS");
  projpj_datums->update_func = SCM_BOOL_F;

  return scm_make_foreign_object_1 (projpj_datums_type, projpj_datums);
}

SCM_DEFINE (pj_get_datums_ref_wrapper, "pj-get-datums-ref", 0, 0, 0,
	    (),
	    "Initialize the datums list reference")
{
  struct projpj_datums *projpj_datums;
  struct PJ_DATUMS *c_projpj_datums;

  projpj_datums = (struct projpj_datums *)
    scm_gc_malloc (sizeof (struct projpj_datums), "projpj_datums");

  c_projpj_datums = pj_get_datums_ref();
  
  projpj_datums->projpj_datums_id = c_projpj_datums;

  projpj_datums->name = scm_from_locale_string("projPJ_DATUMS");
  projpj_datums->update_func = SCM_BOOL_F;

  return scm_make_foreign_object_1 (projpj_datums_type, projpj_datums);
}

SCM_DEFINE (plus_plus_pj_datums, "++pj-datums", 1, 0, 0,
	    (SCM projpj_datums_ob),
	    "increment the pj-datums list")
{
  int status;
  
  struct projpj_datums *projpj_datums;
  
  scm_assert_foreign_object_type (projpj_datums_type, projpj_datums_ob);
  projpj_datums = scm_foreign_object_ref (projpj_datums_ob, 0);
  ++projpj_datums->projpj_datums_id;

  return SCM_UNSPECIFIED;
}

SCM_DEFINE (pj_datums_to_scm, "pj-datums->scm", 1, 0, 0,
	    (SCM projpj_datums_ob),
	    "return a list of the values associated with the current projpj datums list object")
{
  int status;
  char *datumsid, *datumsdefn;
  char *datumsellipse_id, *datumscomments;
  
  struct PJ_DATUMS *c_projpj_datums;
  struct projpj_datums *projpj_datums;
  
  scm_assert_foreign_object_type (projpj_datums_type, projpj_datums_ob);
  projpj_datums = scm_foreign_object_ref (projpj_datums_ob, 0);
  c_projpj_datums = projpj_datums->projpj_datums_id;
  
  datumsid = c_projpj_datums->id;
  datumsdefn = c_projpj_datums->defn;
  datumsellipse_id = c_projpj_datums->ellipse_id;
  datumscomments = c_projpj_datums->comments;
  
  if (datumsid == NULL) return SCM_BOOL_F;
  else return scm_list_4(scm_from_locale_string(datumsid), \
			 scm_from_locale_string(datumsdefn), \
			 scm_from_locale_string(datumsellipse_id), \
			 scm_from_locale_string(datumscomments));
}

/*
  PJ_PRIME_MERIDIANS struct
*/

struct projpj_prime_meridians
{
  struct PJ_PRIME_MERIDIANS *projpj_prime_meridians_id;
  SCM name;
  SCM update_func;
};

static SCM projpj_prime_meridians_type;

void
init_projpj_prime_meridians_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("projPJ_PRIME_MERIDIANS");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;

  projpj_prime_meridians_type = scm_make_foreign_object_type (name, slots, finalizer);
}

SCM_DEFINE (make_projpj_prime_meridians_list, "make-projpj-prime-meridians", 0, 0, 0,
	    (),
	    "Make a pj prime-meridians list object.")  
{
  struct projpj_prime_meridians *projpj_prime_meridians;
  struct PJ_PRIME_MERIDIANS *c_projpj_prime_meridians;
 
  projpj_prime_meridians = (struct projpj_prime_meridians *)
    scm_gc_malloc (sizeof (struct projpj_prime_meridians), "projpj_prime_meridians");

  projpj_prime_meridians->projpj_prime_meridians_id = c_projpj_prime_meridians;

  projpj_prime_meridians->name = scm_from_locale_string("projPJ_PRIME_MERIDIANS");
  projpj_prime_meridians->update_func = SCM_BOOL_F;

   return scm_make_foreign_object_1 (projpj_prime_meridians_type, projpj_prime_meridians);
}

SCM_DEFINE (pj_get_prime_meridians_ref_wrapper, "pj-get-prime-meridians-ref", 0, 0, 0,
	    (),
	    "Initialize the prime-meridians list reference")
{
  struct projpj_prime_meridians *projpj_prime_meridians;
  struct PJ_PRIME_MERIDIANS *c_projpj_prime_meridians;

  projpj_prime_meridians = (struct projpj_prime_meridians *)
    scm_gc_malloc (sizeof (struct projpj_prime_meridians), "projpj_prime_meridians");

  c_projpj_prime_meridians = pj_get_prime_meridians_ref();
  
  projpj_prime_meridians->projpj_prime_meridians_id = c_projpj_prime_meridians;

  projpj_prime_meridians->name = scm_from_locale_string("projPJ_PRIME_MERIDIANS");
  projpj_prime_meridians->update_func = SCM_BOOL_F;

  return scm_make_foreign_object_1 (projpj_prime_meridians_type, projpj_prime_meridians);
}

SCM_DEFINE (plus_plus_pj_prime_meridians, "++pj-prime-meridians", 1, 0, 0,
	    (SCM projpj_prime_meridians_ob),
	    "increment the pj-prime-meridians list")
{
  int status;
  
  struct projpj_prime_meridians *projpj_prime_meridians;
  
  scm_assert_foreign_object_type (projpj_prime_meridians_type, projpj_prime_meridians_ob);
  projpj_prime_meridians = scm_foreign_object_ref (projpj_prime_meridians_ob, 0);
  ++projpj_prime_meridians->projpj_prime_meridians_id;

  return SCM_UNSPECIFIED;
}

SCM_DEFINE (pj_prime_meridians_to_scm, "pj-prime-meridians->scm", 1, 0, 0,
	    (SCM projpj_prime_meridians_ob),
	    "return a list of the values associated with the current projpj prime meridians list object")
{
  int status;
  char *prime_meridiansid, *prime_meridiansdefn;
  struct PJ_PRIME_MERIDIANS *c_projpj_prime_meridians;
  struct projpj_prime_meridians *projpj_prime_meridians;
  
  scm_assert_foreign_object_type (projpj_prime_meridians_type, projpj_prime_meridians_ob);
  projpj_prime_meridians = scm_foreign_object_ref (projpj_prime_meridians_ob, 0);
  c_projpj_prime_meridians = projpj_prime_meridians->projpj_prime_meridians_id;
  
  prime_meridiansid = c_projpj_prime_meridians->id;
  prime_meridiansdefn = c_projpj_prime_meridians->defn;
  
  if (prime_meridiansid == NULL) return SCM_BOOL_F;
  else return scm_list_2(scm_from_locale_string(prime_meridiansid), scm_from_locale_string(prime_meridiansdefn));
}

/*
 * Scheme Initializations
 */
void
scm_init_proj()
{
  // Initialize the Data Types
  init_projuv_type();
  init_projuvw_type();
  init_projpj_type();
  init_projpj_list_type();
  init_projpj_ellps_type();
  init_projpj_units_type();
  init_projpj_datums_type();
  init_projpj_prime_meridians_type();
  /* init_projctx_type(); */

  // VARIABLES
  scm_c_define ("deg2rad", scm_from_double(DEG_TO_RAD));
  scm_c_define ("rad2deg", scm_from_double(RAD_TO_DEG));
  scm_c_define ("pj-inq-libvers", scm_from_int((int)PJ_VERSION));
  scm_c_define ("pj-inq-release", scm_from_locale_string(pj_release));
  scm_c_define ("pj-guile-inq-libvers", scm_from_locale_string(vcid));
  
#ifndef SCM_MAGIC_SNARFER
#include "proj_guile.x"
#endif  
}
