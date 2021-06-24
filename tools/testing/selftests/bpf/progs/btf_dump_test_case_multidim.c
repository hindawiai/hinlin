<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * BTF-to-C dumper test क्रम multi-dimensional array output.
 *
 * Copyright (c) 2019 Facebook
 */
/* ----- START-EXPECTED-OUTPUT ----- */
प्रकार पूर्णांक arr_t[2];

प्रकार पूर्णांक multiarr_t[3][4][5];

प्रकार पूर्णांक *ptr_arr_t[6];

प्रकार पूर्णांक *ptr_multiarr_t[7][8][9][10];

प्रकार पूर्णांक * (*fn_ptr_arr_t[11])();

प्रकार पूर्णांक * (*fn_ptr_multiarr_t[12][13])();

काष्ठा root_काष्ठा अणु
	arr_t _1;
	multiarr_t _2;
	ptr_arr_t _3;
	ptr_multiarr_t _4;
	fn_ptr_arr_t _5;
	fn_ptr_multiarr_t _6;
पूर्ण;

/* ------ END-EXPECTED-OUTPUT ------ */

पूर्णांक f(काष्ठा root_काष्ठा *s)
अणु
	वापस 0;
पूर्ण
