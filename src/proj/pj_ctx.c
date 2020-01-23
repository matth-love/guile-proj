/* ----------------------------------------------------------------
 * pj_ctx.c 
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
 * --------------------------------------------------------------*/

#include "pj_guile.h"

/*
 * ProjCtx struct
 */
struct projctx
{
  SCM proj_string;
  SCM name;
  projPJ projpj_id;
  projCtx projctx_id;
  SCM update_func;
};

static SCM projctx_type;

//projctx
void
init_projctx_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("projCtx");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;

  projctx_type = scm_make_foreign_object_type (name, slots, finalizer);
}

SCM
make_projctx ()
{
  struct projctx *projctx;
  projCtx c_projctx;
 
  /* Allocate the `struct projuv'.  Because we
     use scm_gc_malloc, this memory block will
     be automatically reclaimed when it becomes
     inaccessible, and its members will be traced
     by the garbage collector.  */
  projctx = (struct projctx *)
    scm_gc_malloc (sizeof (struct projctx), "projctx");

  projctx->projctx_id = c_projctx;

  projctx->name = scm_from_locale_string("projctx");
  projctx->update_func = SCM_BOOL_F;

  /* Now wrap the struct projuv* in a new foreign
     object, and return that object.  */
  return scm_make_foreign_object_1 (projctx_type, projctx);
}

SCM
pj_get_default_ctx_wrapper() {

  struct projctx *projctx;
  projCtx c_projctx;
  
  projctx = (struct projctx *)
    scm_gc_malloc (sizeof (struct projctx), "projctx");

  if (!(c_projctx = pj_get_default_ctx()))
    return SCM_BOOL_F;

  projctx->projctx_id = c_projctx;

  projctx->name = scm_from_locale_string("projctx");
  projctx->update_func = SCM_BOOL_F;
 
  return scm_make_foreign_object_1 (projctx_type, projctx);
}

SCM
pj_ctx_set_debug_wrapper(SCM projctx_ob, SCM debug_val) {

  int status;
  projCtx c_projctx;
  struct projctx *projctx;  

  scm_assert_foreign_object_type (projctx_type, projctx_ob);
  projctx = scm_foreign_object_ref (projctx_ob, 0);
  c_projctx = projctx->projctx_id;

  pj_ctx_set_debug(c_projctx, scm_to_int(debug_val));
 
  return SCM_BOOL_T;
}
