/* ----------------------------------------------------------------
 * guile_proj.c 
 *
 * Copyright (c) 2013-2018 Matthew Love <matthew.love@colorado.edu>
 * GUILE-PROJ is liscensed under the GPL v.2 or later and
 * is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * <http://www.gnu.org/licenses/>
 *
 * --------------------------------------------------------------*/

/*
 TODO:
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <libguile.h>

#include "proj_api.h"

//---BEGIN
static scm_t_bits projuv_tag;
static scm_t_bits projpj_tag;
static scm_t_bits projctx_tag;

static char vcid[] = "0.0.6-dep";

/*
  Version Info
*/

SCM 
pj_inq_libvers_wrapper () {
  // RETURN PROJ_API LIBVERSION
  return scm_from_int (PJ_VERSION);
}

SCM
pj_guile_inq_libvers_wrapper () {
  // RETURN GUILE-PROJ LIBVERSION
  return scm_from_locale_string (vcid);
}

/* 
   projUV Smob
   This smob holds the c projUV datatype

*/

//---projUV
struct projuv {
  SCM idname;
  SCM u; // double
  SCM v; // double
  projUV projuv_id;
  SCM update_func;
};

static SCM
mark_projuv (SCM projuv_smob) {
  /* Mark the image's name and update function.  */
  struct projuv *projuv = (struct projuv *) SCM_SMOB_DATA (projuv_smob);
  
  scm_gc_mark (projuv->idname);
  
  return projuv->update_func;
}

static size_t
free_projuv (SCM projuv_smob) {
  struct projuv *projuv = (struct projuv *) SCM_SMOB_DATA (projuv_smob);
  //projpj->proj_string = scm_from_locale_string("VOID");
  scm_gc_free (projuv, sizeof (struct projuv), "projuv");

  return 0;
}

static int
print_projuv (SCM projuv_smob, SCM port, scm_print_state *pstate) {
    
  struct projuv *projuv = (struct projuv *) SCM_SMOB_DATA (projuv_smob);
  
  scm_puts ("#<projUV \"", port);
  scm_display (projuv->u, port);
  scm_display (projuv->v, port);
  scm_puts ("\">", port);
  
  /* non-zero means success */
  return 1;
}

/* 
   projPJ Smob
   This smob holds the c projPJ datatype

*/

//---projPJ
struct projpj {
  SCM proj_string;
  SCM idname;
  projPJ projpj_id;
  SCM update_func;
};

static SCM
mark_projpj (SCM projpj_smob) {
  /* Mark the image's name and update function.  */
  struct projpj *projpj = (struct projpj *) SCM_SMOB_DATA (projpj_smob);
  
  scm_gc_mark (projpj->proj_string);
  scm_gc_mark (projpj->idname);
  
  return projpj->update_func;
}

static size_t
free_projpj (SCM projpj_smob) {
  struct projpj *projpj = (struct projpj *) SCM_SMOB_DATA (projpj_smob);
  //projpj->proj_string = scm_from_locale_string("VOID");
  scm_gc_free (projpj, sizeof (struct projpj), "projpj");

  return 0;
}

static int
print_projpj (SCM projpj_smob, SCM port, scm_print_state *pstate) {
    
  struct projpj *projpj = (struct projpj *) SCM_SMOB_DATA (projpj_smob);
  
  scm_puts ("#<projPJ \"", port);
  scm_display (projpj->proj_string, port);
  scm_puts ("\">", port);
  
  /* non-zero means success */
  return 1;
}

/* 
   projCtx Smob
   This smob holds the c projCtx datatype

*/

//---projCtx
struct projctx {
  SCM proj_string;
  SCM idname;
  projPJ projpj_id;
  projCtx projctx_id;
  SCM update_func;
};

static SCM
mark_projctx (SCM projctx_smob) {
  /* Mark the image's name and update function.  */
  struct projctx *projctx = (struct projctx *) SCM_SMOB_DATA (projctx_smob);
  
  scm_gc_mark (projctx->proj_string);
  scm_gc_mark (projctx->idname);
  
  return projctx->update_func;
}

static size_t
free_projctx (SCM projctx_smob) {
  struct projctx *projctx = (struct projctx *) SCM_SMOB_DATA (projctx_smob);
  
  scm_gc_free (projctx, sizeof (struct projctx), "projctx");

  return 0;
}

static int
print_projctx (SCM projctx_smob, SCM port, scm_print_state *pstate) {
    
  struct projctx *projctx = (struct projctx *) SCM_SMOB_DATA (projctx_smob);
  
  scm_puts ("#<projCtx \"", port);
  scm_display (projctx->proj_string, port);
  scm_puts ("\">", port);
  
  /* non-zero means success */
  return 1;
}

/* 
   SCM Functions
*/

// Create a projUV smob
SCM
pj_uv_init(SCM u, SCM v) {
  size_t length;
  projUV c_projuv;
  SCM smob;
  struct projuv *projuv;
  
  // projuv
  projuv = (struct projuv *) scm_gc_malloc (sizeof (struct projuv), "projuv");

  /* c_projuv.u = scm_to_double(u); */
  /* c_projuv.v = scm_to_double(v); */
  
  // projpj SMOB
  projuv->idname = scm_from_locale_string ("projuv");
  //projuv->projuv_id = 0;
  projuv->update_func = SCM_BOOL_F;
  
  SCM_NEWSMOB (smob, projuv_tag, projuv);
  
  projuv->idname = scm_from_locale_string ("projuv");
  projuv->projuv_id = c_projuv;
  projuv->u = u;
  projuv->v = v;
  
  // RETURN projpj SMOB
  return smob;  
}

// Creates a projPJ smob for use in pj-transform.
SCM
pj_init_plus_wrapper(SCM scm_param) {
  const char *c_param;
  size_t length;
  projPJ c_projpj;
  SCM smob;
  struct projpj *projpj;
  
  if (scm_is_true (scm_string_p (scm_param))) {
    c_param = scm_to_locale_stringn (scm_param, &length);
  } 
  else {
    c_param = "N/A";
    fprintf (stderr,"guile_proj: projection parameter: %s is not a string\n", c_param);
  }
  
  // projpj
  projpj = (struct projpj *) scm_gc_malloc (sizeof (struct projpj), "projpj");
  
  if (!(c_projpj = pj_init_plus(c_param))) {
    fprintf (stderr,"guile_proj: failed to initialize projection string: %s\n", c_param);
  }

  // projpj SMOB
  projpj->proj_string = scm_param;
  projpj->idname = scm_from_locale_string ("projpj");
  projpj->projpj_id = 0;
  projpj->update_func = SCM_BOOL_F;
  
  SCM_NEWSMOB (smob, projpj_tag, projpj);
  
  projpj->proj_string = scm_param;
  projpj->idname = scm_from_locale_string ("projpj");
  projpj->projpj_id = c_projpj;
  
  // RETURN projpj SMOB
  return smob;
}

SCM
pj_is_latlong_wrapper(SCM projpj_smob) {
  int status;
  projPJ c_projpj;

  struct projpj *projpj;  
  
  // projpj_src_smob
  
  scm_assert_smob_type (projpj_tag, projpj_smob);
  projpj = (struct projpj *) SCM_SMOB_DATA (projpj_smob);
  c_projpj = projpj->projpj_id;

  status = pj_is_latlong(c_projpj);
  
  return scm_from_int(status);
}

// Print out some info regarding the projpj
SCM
pj_pr_list_wrapper(SCM projpj_smob) {
  int status;
  projPJ c_projpj;
  struct projpj *projpj;  

    // projpj_src_smob

  scm_assert_smob_type (projpj_tag, projpj_smob);
  projpj = (struct projpj *) SCM_SMOB_DATA (projpj_smob);
  c_projpj = projpj->projpj_id;
  
  pj_pr_list(c_projpj);

  return SCM_BOOL_T;
}

// if x and y are in degrees, they must be converted first to radians (use deg2rad);
// the inverse is also true (use rad2deg).  TODO make it auto detect such things.
SCM
pj_transform_wrapper(SCM projpj_src_smob, SCM projpj_dst_smob, \
		     SCM scm_ptcnt, SCM scm_ptoffset, \
		     SCM scm_x, SCM scm_y, SCM scm_z) {
  double x,y,z;
  int c_ptoffset, status;
  long c_ptcnt;
  projPJ c_src_projpj, c_dst_projpj;
  
  struct projpj *pj_src_projpj;
  struct projpj *pj_dst_projpj;

  x = scm_to_double(scm_x);
  y = scm_to_double(scm_y);
  z = scm_to_double(scm_z);

  c_ptoffset = scm_to_int(scm_ptoffset);
  c_ptcnt = scm_to_long(scm_ptcnt);

  // projpj_src_smob

  scm_assert_smob_type (projpj_tag, projpj_src_smob);
  pj_src_projpj = (struct projpj *) SCM_SMOB_DATA (projpj_src_smob);
  c_src_projpj = pj_src_projpj->projpj_id;

  // projpj_dst_smob

  scm_assert_smob_type (projpj_tag, projpj_dst_smob);
  pj_dst_projpj = (struct projpj *) SCM_SMOB_DATA (projpj_dst_smob);
  c_dst_projpj = pj_dst_projpj->projpj_id;

  status = pj_transform(c_src_projpj, c_dst_projpj, c_ptcnt, c_ptoffset, &x, &y, &z);

  return scm_list_3 (scm_from_double(x),scm_from_double(y),scm_from_double(z));

}

SCM
pj_free_wrapper(SCM projpj_smob) {
  int status;
  projPJ c_projpj;
  struct projpj *projpj;  
  
  // projpj_src_smob

  scm_assert_smob_type (projpj_tag, projpj_smob);
  projpj = (struct projpj *) SCM_SMOB_DATA (projpj_smob);
  c_projpj = projpj->projpj_id;

  pj_free(c_projpj);
  //free_projpj(projpj_smob);

  return SCM_BOOL_T;
}

// CTX

SCM
pj_get_ctx_wrapper (SCM projpj_smob) {
  int status;
  projPJ c_projpj;

  struct projpj *projpj;  

  // projpj_smob
  scm_assert_smob_type (projpj_tag, projpj_smob);
  projpj = (struct projpj *) SCM_SMOB_DATA (projpj_smob);
  c_projpj = projpj->projpj_id;

  // projctx_smob

  size_t length;
  projCtx c_projctx;
  SCM smob;
  struct projctx *projctx;
  
  // projctx
  projctx = (struct projctx *) scm_gc_malloc (sizeof (struct projctx), "projctx");
  
  if (!(c_projctx = pj_get_ctx(c_projpj))) {
    fprintf (stderr,"guile_proj: failed to initialize projCtx:\n");
  }

  // projctx SMOB
  projctx->proj_string = projpj->proj_string;
  projctx->idname = scm_from_locale_string ("projctx");
  projctx->projpj_id = projpj->projpj_id;
  projctx->projctx_id = 0;
  projctx->update_func = SCM_BOOL_F;
  
  SCM_NEWSMOB (smob, projctx_tag, projctx);
  
  //projctx->proj_string = scm_param;
  projctx->idname = scm_from_locale_string ("projctx");
  projctx->projctx_id = c_projctx;
  
  // RETURN projpj SMOB
  return smob;
}

SCM
pj_ctx_get_app_data_wrapper(SCM projctx_smob) {
  int status;
  projCtx c_projctx;
  struct projctx *projctx;  

  // projctx_smob

  scm_assert_smob_type (projctx_tag, projctx_smob);
  projctx = (struct projctx *) SCM_SMOB_DATA (projctx_smob);
  c_projctx = projctx->projctx_id;

  pj_ctx_get_app_data( c_projctx );

  return SCM_BOOL_T;
}


/*----------
  Init
----------*/

void
scm_init_proj() {
  
  // PROJUV SMOB
  projuv_tag = scm_make_smob_type ("projuv", sizeof (struct projuv));
  scm_set_smob_mark (projuv_tag, mark_projuv);
  scm_set_smob_print (projuv_tag, print_projuv);
  
  // PROJPJ SMOB
  projpj_tag = scm_make_smob_type ("projpj", sizeof (struct projpj));
  scm_set_smob_mark (projpj_tag, mark_projpj);
  scm_set_smob_free (projpj_tag, free_projpj);
  scm_set_smob_print (projpj_tag, print_projpj);

  // PROJCTX SMOB
  projctx_tag = scm_make_smob_type ("projctx", sizeof (struct projctx));
  scm_set_smob_mark (projctx_tag, mark_projctx);
  scm_set_smob_free (projctx_tag, free_projctx);
  scm_set_smob_print (projctx_tag, print_projctx);

  // VARIABLES
  scm_c_define ("deg2rad", scm_from_double(DEG_TO_RAD));
  scm_c_define ("rad2deg", scm_from_double(RAD_TO_DEG));

  // FUNCTION WRAPPERS
  scm_c_define_gsubr ("pj-uv-init", 2, 0, 0, pj_uv_init);
  scm_c_define_gsubr ("pj-inq-libvers", 0, 0, 0, pj_inq_libvers_wrapper);
  scm_c_define_gsubr ("pj-guile-inq-libvers", 0, 0, 0, pj_guile_inq_libvers_wrapper);
  scm_c_define_gsubr ("pj-is-latlong", 1, 0, 0, pj_is_latlong_wrapper);
  scm_c_define_gsubr ("pj-pr-list", 1, 0, 0, pj_pr_list_wrapper);
  scm_c_define_gsubr ("pj-init-plus", 1, 0, 0, pj_init_plus_wrapper);
  scm_c_define_gsubr ("pj-transform", 7, 0, 0, pj_transform_wrapper);
  scm_c_define_gsubr ("pj-free", 1, 0, 0, pj_free_wrapper);

  scm_c_define_gsubr ("pj-get-ctx", 1, 0, 0, pj_get_ctx_wrapper);
  scm_c_define_gsubr ("pj-ctx-get-app-data", 1, 0, 0, pj_ctx_get_app_data_wrapper);
}


