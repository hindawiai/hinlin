<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * BTF-to-C dumper test क्रम majority of C syntax quirks.
 *
 * Copyright (c) 2019 Facebook
 */
/* ----- START-EXPECTED-OUTPUT ----- */
क्रमागत e1 अणु
	A = 0,
	B = 1,
पूर्ण;

क्रमागत e2 अणु
	C = 100,
	D = 4294967295,
	E = 0,
पूर्ण;

प्रकार क्रमागत e2 e2_t;

प्रकार क्रमागत अणु
	F = 0,
	G = 1,
	H = 2,
पूर्ण e3_t;

प्रकार पूर्णांक पूर्णांक_t;

प्रकार अस्थिर स्थिर पूर्णांक * अस्थिर स्थिर crazy_ptr_t;

प्रकार पूर्णांक *****we_need_to_go_deeper_ptr_t;

प्रकार अस्थिर स्थिर we_need_to_go_deeper_ptr_t * restrict * अस्थिर * स्थिर * restrict अस्थिर * restrict स्थिर * अस्थिर स्थिर * restrict अस्थिर स्थिर how_about_this_ptr_t;

प्रकार पूर्णांक *ptr_arr_t[10];

प्रकार व्योम (*fn_ptr1_t)(पूर्णांक);

प्रकार व्योम (*म_लिखो_fn_t)(स्थिर अक्षर *, ...);

/* ------ END-EXPECTED-OUTPUT ------ */
/*
 * While previous function poपूर्णांकers are pretty trivial (C-syntax-level
 * trivial), the following are deciphered here क्रम future generations:
 *
 * - `fn_ptr2_t`: function, taking anonymous काष्ठा as a first arg and poपूर्णांकer
 *   to a function, that takes पूर्णांक and वापसs पूर्णांक, as a second arg; वापसing
 *   a poपूर्णांकer to a स्थिर poपूर्णांकer to a अक्षर. Equivalent to:
 *	प्रकार काष्ठा अणु पूर्णांक a; पूर्ण s_t;
 *	प्रकार पूर्णांक (*fn_t)(पूर्णांक);
 *	प्रकार अक्षर * स्थिर * (*fn_ptr2_t)(s_t, fn_t);
 *
 * - `fn_complext_t`: poपूर्णांकer to a function वापसing काष्ठा and accepting
 *   जोड़ and काष्ठा. All काष्ठाs and क्रमागत are anonymous and defined अंतरभूत.
 *
 * - `संकेत_t: poपूर्णांकer to a function accepting a poपूर्णांकer to a function as an
 *   argument and वापसing poपूर्णांकer to a function as a result. Sane equivalent:
 *	प्रकार व्योम (*संकेत_handler_t)(पूर्णांक);
 *	प्रकार संकेत_handler_t (*संकेत_ptr_t)(पूर्णांक, संकेत_handler_t);
 *
 * - fn_ptr_arr1_t: array of poपूर्णांकers to a function accepting poपूर्णांकer to
 *   a poपूर्णांकer to an पूर्णांक and वापसing poपूर्णांकer to a अक्षर. Easy.
 *
 * - fn_ptr_arr2_t: array of स्थिर poपूर्णांकers to a function taking no arguments
 *   and वापसing a स्थिर poपूर्णांकer to a function, that takes poपूर्णांकer to a
 *   `पूर्णांक -> अक्षर *` function and वापसs poपूर्णांकer to a अक्षर. Equivalent:
 *   प्रकार अक्षर * (*fn_input_t)(पूर्णांक);
 *   प्रकार अक्षर * (*fn_output_outer_t)(fn_input_t);
 *   प्रकार स्थिर fn_output_outer_t (* fn_output_inner_t)();
 *   प्रकार स्थिर fn_output_inner_t fn_ptr_arr2_t[5];
 */
/* ----- START-EXPECTED-OUTPUT ----- */
प्रकार अक्षर * स्थिर * (*fn_ptr2_t)(काष्ठा अणु
	पूर्णांक a;
पूर्ण, पूर्णांक (*)(पूर्णांक));

प्रकार काष्ठा अणु
	पूर्णांक a;
	व्योम (*b)(पूर्णांक, काष्ठा अणु
		पूर्णांक c;
	पूर्ण, जोड़ अणु
		अक्षर d;
		पूर्णांक e[5];
	पूर्ण);
पूर्ण (*fn_complex_t)(जोड़ अणु
	व्योम *f;
	अक्षर g[16];
पूर्ण, काष्ठा अणु
	पूर्णांक h;
पूर्ण);

प्रकार व्योम (* (*संकेत_t)(पूर्णांक, व्योम (*)(पूर्णांक)))(पूर्णांक);

प्रकार अक्षर * (*fn_ptr_arr1_t[10])(पूर्णांक **);

प्रकार अक्षर * (* स्थिर (* स्थिर fn_ptr_arr2_t[5])())(अक्षर * (*)(पूर्णांक));

काष्ठा काष्ठा_w_प्रकारs अणु
	पूर्णांक_t a;
	crazy_ptr_t b;
	we_need_to_go_deeper_ptr_t c;
	how_about_this_ptr_t d;
	ptr_arr_t e;
	fn_ptr1_t f;
	म_लिखो_fn_t g;
	fn_ptr2_t h;
	fn_complex_t i;
	संकेत_t j;
	fn_ptr_arr1_t k;
	fn_ptr_arr2_t l;
पूर्ण;

प्रकार काष्ठा अणु
	पूर्णांक x;
	पूर्णांक y;
	पूर्णांक z;
पूर्ण anon_काष्ठा_t;

काष्ठा काष्ठा_fwd;

प्रकार काष्ठा काष्ठा_fwd काष्ठा_fwd_t;

प्रकार काष्ठा काष्ठा_fwd *काष्ठा_fwd_ptr_t;

जोड़ जोड़_fwd;

प्रकार जोड़ जोड़_fwd जोड़_fwd_t;

प्रकार जोड़ जोड़_fwd *जोड़_fwd_ptr_t;

काष्ठा काष्ठा_empty अणुपूर्ण;

काष्ठा काष्ठा_simple अणु
	पूर्णांक a;
	अक्षर b;
	स्थिर पूर्णांक_t *p;
	काष्ठा काष्ठा_empty s;
	क्रमागत e2 e;
	क्रमागत अणु
		ANON_VAL1 = 1,
		ANON_VAL2 = 2,
	पूर्ण f;
	पूर्णांक arr1[13];
	क्रमागत e2 arr2[5];
पूर्ण;

जोड़ जोड़_empty अणुपूर्ण;

जोड़ जोड़_simple अणु
	व्योम *ptr;
	पूर्णांक num;
	पूर्णांक_t num2;
	जोड़ जोड़_empty u;
पूर्ण;

काष्ठा काष्ठा_in_काष्ठा अणु
	काष्ठा काष्ठा_simple simple;
	जोड़ जोड़_simple also_simple;
	काष्ठा अणु
		पूर्णांक a;
	पूर्ण not_so_hard_as_well;
	जोड़ अणु
		पूर्णांक b;
		पूर्णांक c;
	पूर्ण anon_जोड़_is_good;
	काष्ठा अणु
		पूर्णांक d;
		पूर्णांक e;
	पूर्ण;
	जोड़ अणु
		पूर्णांक f;
		पूर्णांक g;
	पूर्ण;
पूर्ण;

काष्ठा काष्ठा_in_array अणुपूर्ण;

काष्ठा काष्ठा_in_array_typed अणुपूर्ण;

प्रकार काष्ठा काष्ठा_in_array_typed काष्ठा_in_array_t[2];

काष्ठा काष्ठा_with_embedded_stuff अणु
	पूर्णांक a;
	काष्ठा अणु
		पूर्णांक b;
		काष्ठा अणु
			काष्ठा काष्ठा_with_embedded_stuff *c;
			स्थिर अक्षर *d;
		पूर्ण e;
		जोड़ अणु
			अस्थिर दीर्घ पूर्णांक f;
			व्योम * restrict g;
		पूर्ण;
	पूर्ण;
	जोड़ अणु
		स्थिर पूर्णांक_t *h;
		व्योम (*i)(अक्षर, पूर्णांक, व्योम *);
	पूर्ण j;
	क्रमागत अणु
		K = 100,
		L = 200,
	पूर्ण m;
	अक्षर n[16];
	काष्ठा अणु
		अक्षर o;
		पूर्णांक p;
		व्योम (*q)(पूर्णांक);
	पूर्ण r[5];
	काष्ठा काष्ठा_in_काष्ठा s[10];
	पूर्णांक t[11];
	काष्ठा काष्ठा_in_array (*u)[2];
	काष्ठा_in_array_t *v;
पूर्ण;

काष्ठा भग्न_काष्ठा अणु
	भग्न f;
	स्थिर द्विगुन *d;
	अस्थिर दीर्घ द्विगुन *ld;
पूर्ण;

काष्ठा root_काष्ठा अणु
	क्रमागत e1 _1;
	क्रमागत e2 _2;
	e2_t _2_1;
	e3_t _2_2;
	काष्ठा काष्ठा_w_प्रकारs _3;
	anon_काष्ठा_t _7;
	काष्ठा काष्ठा_fwd *_8;
	काष्ठा_fwd_t *_9;
	काष्ठा_fwd_ptr_t _10;
	जोड़ जोड़_fwd *_11;
	जोड़_fwd_t *_12;
	जोड़_fwd_ptr_t _13;
	काष्ठा काष्ठा_with_embedded_stuff _14;
	काष्ठा भग्न_काष्ठा _15;
पूर्ण;

/* ------ END-EXPECTED-OUTPUT ------ */

पूर्णांक f(काष्ठा root_काष्ठा *s)
अणु
	वापस 0;
पूर्ण
