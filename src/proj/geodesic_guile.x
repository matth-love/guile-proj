/* cpp arguments: geodesic_guile.c -DHAVE_CONFIG_H -g -O2 */
scm_c_define_gsubr (s_make_pj_geodesic,   1  ,   0  ,   0  , (SCM (*)())   make_pj_geodesic  );;
scm_c_define_gsubr (s_make_pj_geodesicline,   1  ,   0  ,   0  , (SCM (*)())   make_pj_geodesicline  );;
scm_c_define_gsubr (s_geod_init_wrapper,   3  ,   0  ,   0  , (SCM (*)())   geod_init_wrapper  );;
scm_c_define_gsubr (s_geod_init_or,   2  ,   0  ,   0  , (SCM (*)())   geod_init_or  );;
scm_c_define_gsubr (s_geod_direct_wrapper,   5  ,   0  ,   0  , (SCM (*)())   geod_direct_wrapper  );;
scm_c_define_gsubr (s_geod_inverse_wrapper,   5  ,   0  ,   0  , (SCM (*)())   geod_inverse_wrapper  );;
scm_c_define_gsubr (s_geod_geninverse_wrapper,   5  ,   0  ,   0  , (SCM (*)())   geod_geninverse_wrapper  );;
scm_c_define_gsubr (s_geod_lineinit_wrapper,   4  ,   0  ,   0  , (SCM (*)())   geod_lineinit_wrapper  );;
scm_c_define_gsubr (s_geod_inverseline_wrapper,   5  ,   0  ,   0  , (SCM (*)())   geod_inverseline_wrapper  );;
scm_c_define_gsubr (s_geod_directline_wrapper,   5  ,   0  ,   0  , (SCM (*)())   geod_directline_wrapper  );;
scm_c_define_gsubr (s_geod_position_wrapper,   2  ,   0  ,   0  , (SCM (*)())   geod_position_wrapper  );;
