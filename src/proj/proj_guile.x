/* cpp arguments: proj_guile.c -DHAVE_CONFIG_H -g -O2 */
scm_c_define_gsubr (s_pj_strerrno_wrapper,   1  ,   0  ,   0  , (SCM (*)())   pj_strerrno_wrapper  );;
scm_c_define_gsubr (s_pj_get_errno_wrapper,   0  ,   0  ,   0  , (SCM (*)())   pj_get_errno_wrapper  );;
scm_c_define_gsubr (s_pj_get_errno_ref_wrapper,   0  ,   0  ,   0  , (SCM (*)())   pj_get_errno_ref_wrapper  );;
scm_c_define_gsubr (s_make_projuv,   2  ,   0  ,   0  , (SCM (*)())   make_projuv  );;
scm_c_define_gsubr (s_get_projuv_uv,   1  ,   0  ,   0  , (SCM (*)())   get_projuv_uv  );;
scm_c_define_gsubr (s_make_projuvw,   3  ,   0  ,   0  , (SCM (*)())   make_projuvw  );;
scm_c_define_gsubr (s_get_projuvw_uvw,   1  ,   0  ,   0  , (SCM (*)())   get_projuvw_uvw  );;
scm_c_define_gsubr (s_make_projpj,   1  ,   0  ,   0  , (SCM (*)())   make_projpj  );;
scm_c_define_gsubr (s_pj_init_wrapper,   1  ,   0  ,   0  , (SCM (*)())   pj_init_wrapper  );;
scm_c_define_gsubr (s_pj_init_plus_wrapper,   1  ,   0  ,   0  , (SCM (*)())   pj_init_plus_wrapper  );;
scm_c_define_gsubr (s_pj_pr_list_wrapper,   1  ,   0  ,   0  , (SCM (*)())   pj_pr_list_wrapper  );;
scm_c_define_gsubr (s_pj_get_def_wrapper,   1  ,   0  ,   0  , (SCM (*)())   pj_get_def_wrapper  );;
scm_c_define_gsubr (s_pj_free_wrapper,   1  ,   0  ,   0  , (SCM (*)())   pj_free_wrapper  );;
scm_c_define_gsubr (s_pj_fwd_wrapper,   2  ,   0  ,   0  , (SCM (*)())   pj_fwd_wrapper  );;
scm_c_define_gsubr (s_pj_fwd_list_wrapper,   2  ,   0  ,   0  , (SCM (*)())   pj_fwd_list_wrapper  );;
scm_c_define_gsubr (s_pj_inv_wrapper,   2  ,   0  ,   0  , (SCM (*)())   pj_inv_wrapper  );;
scm_c_define_gsubr (s_pj_inv_list_wrapper,   2  ,   0  ,   0  , (SCM (*)())   pj_inv_list_wrapper  );;
scm_c_define_gsubr (s_pj_fwd3d_wrapper,   2  ,   0  ,   0  , (SCM (*)())   pj_fwd3d_wrapper  );;
scm_c_define_gsubr (s_pj_inv3d_wrapper,   2  ,   0  ,   0  , (SCM (*)())   pj_inv3d_wrapper  );;
scm_c_define_gsubr (s_pj_transform_wrapper,   7  ,   0  ,   0  , (SCM (*)())   pj_transform_wrapper  );;
scm_c_define_gsubr (s_pj_datum_transform_wrapper,   7  ,   0  ,   0  , (SCM (*)())   pj_datum_transform_wrapper  );;
scm_c_define_gsubr (s_pj_compare_datums_wrapper,   2  ,   0  ,   0  , (SCM (*)())   pj_compare_datums_wrapper  );;
scm_c_define_gsubr (s_pj_latlong_from_proj_wrapper,   1  ,   0  ,   0  , (SCM (*)())   pj_latlong_from_proj_wrapper  );;
scm_c_define_gsubr (s_pj_is_latlong_wrapper,   1  ,   0  ,   0  , (SCM (*)())   pj_is_latlong_wrapper  );;
scm_c_define_gsubr (s_pj_is_geocent_wrapper,   1  ,   0  ,   0  , (SCM (*)())   pj_is_geocent_wrapper  );;
scm_c_define_gsubr (s_set_rtodms_wrapper,   1  ,   0  ,   0  , (SCM (*)())   set_rtodms_wrapper  );;
scm_c_define_gsubr (s_dmstor_wrapper,   1  ,   0  ,   0  , (SCM (*)())   dmstor_wrapper  );;
scm_c_define_gsubr (s_rtodms_wrapper,   3  ,   0  ,   0  , (SCM (*)())   rtodms_wrapper  );;
scm_c_define_gsubr (s_make_projpj_list,   0  ,   0  ,   0  , (SCM (*)())   make_projpj_list  );;
scm_c_define_gsubr (s_pj_get_list_ref_wrapper,   0  ,   0  ,   0  , (SCM (*)())   pj_get_list_ref_wrapper  );;
scm_c_define_gsubr (s_plus_plus_pj_list,   1  ,   0  ,   0  , (SCM (*)())   plus_plus_pj_list  );;
scm_c_define_gsubr (s_pj_list_to_scm,   1  ,   0  ,   0  , (SCM (*)())   pj_list_to_scm  );;
scm_c_define_gsubr (s_make_projpj_ellps_list,   0  ,   0  ,   0  , (SCM (*)())   make_projpj_ellps_list  );;
scm_c_define_gsubr (s_pj_get_ellps_ref_wrapper,   0  ,   0  ,   0  , (SCM (*)())   pj_get_ellps_ref_wrapper  );;
scm_c_define_gsubr (s_plus_plus_pj_ellps,   1  ,   0  ,   0  , (SCM (*)())   plus_plus_pj_ellps  );;
scm_c_define_gsubr (s_pj_ellps_to_scm,   1  ,   0  ,   0  , (SCM (*)())   pj_ellps_to_scm  );;
scm_c_define_gsubr (s_make_projpj_units_list,   0  ,   0  ,   0  , (SCM (*)())   make_projpj_units_list  );;
scm_c_define_gsubr (s_pj_get_units_ref_wrapper,   0  ,   0  ,   0  , (SCM (*)())   pj_get_units_ref_wrapper  );;
scm_c_define_gsubr (s_plus_plus_pj_units,   1  ,   0  ,   0  , (SCM (*)())   plus_plus_pj_units  );;
scm_c_define_gsubr (s_pj_units_to_scm,   1  ,   0  ,   0  , (SCM (*)())   pj_units_to_scm  );;
scm_c_define_gsubr (s_make_projpj_datums_list,   0  ,   0  ,   0  , (SCM (*)())   make_projpj_datums_list  );;
scm_c_define_gsubr (s_pj_get_datums_ref_wrapper,   0  ,   0  ,   0  , (SCM (*)())   pj_get_datums_ref_wrapper  );;
scm_c_define_gsubr (s_plus_plus_pj_datums,   1  ,   0  ,   0  , (SCM (*)())   plus_plus_pj_datums  );;
scm_c_define_gsubr (s_pj_datums_to_scm,   1  ,   0  ,   0  , (SCM (*)())   pj_datums_to_scm  );;
scm_c_define_gsubr (s_make_projpj_prime_meridians_list,   0  ,   0  ,   0  , (SCM (*)())   make_projpj_prime_meridians_list  );;
scm_c_define_gsubr (s_pj_get_prime_meridians_ref_wrapper,   0  ,   0  ,   0  , (SCM (*)())   pj_get_prime_meridians_ref_wrapper  );;
scm_c_define_gsubr (s_plus_plus_pj_prime_meridians,   1  ,   0  ,   0  , (SCM (*)())   plus_plus_pj_prime_meridians  );;
scm_c_define_gsubr (s_pj_prime_meridians_to_scm,   1  ,   0  ,   0  , (SCM (*)())   pj_prime_meridians_to_scm  );;
