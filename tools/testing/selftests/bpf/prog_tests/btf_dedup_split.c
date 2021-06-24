<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <test_progs.h>
#समावेश <bpf/btf.h>
#समावेश "btf_helpers.h"

अटल व्योम test_split_simple() अणु
	स्थिर काष्ठा btf_type *t;
	काष्ठा btf *btf1, *btf2;
	पूर्णांक str_off, err;

	btf1 = btf__new_empty();
	अगर (!ASSERT_OK_PTR(btf1, "empty_main_btf"))
		वापस;

	btf__set_poपूर्णांकer_size(btf1, 8); /* enक्रमce 64-bit arch */

	btf__add_पूर्णांक(btf1, "int", 4, BTF_INT_SIGNED);	/* [1] पूर्णांक */
	btf__add_ptr(btf1, 1);				/* [2] ptr to पूर्णांक */
	btf__add_काष्ठा(btf1, "s1", 4);			/* [3] काष्ठा s1 अणु */
	btf__add_field(btf1, "f1", 1, 0, 0);		/*      पूर्णांक f1; */
							/* पूर्ण */

	VALIDATE_RAW_BTF(
		btf1,
		"[1] INT 'int' size=4 bits_offset=0 nr_bits=32 encoding=SIGNED",
		"[2] PTR '(anon)' type_id=1",
		"[3] STRUCT 's1' size=4 vlen=1\n"
		"\t'f1' type_id=1 bits_offset=0");

	ASSERT_STREQ(btf_type_c_dump(btf1), "\
काष्ठा s1 अणु\न\
	पूर्णांक f1;\न\
पूर्ण;\न\न", "c_dump");

	btf2 = btf__new_empty_split(btf1);
	अगर (!ASSERT_OK_PTR(btf2, "empty_split_btf"))
		जाओ cleanup;

	/* poपूर्णांकer size should be "inherited" from मुख्य BTF */
	ASSERT_EQ(btf__poपूर्णांकer_size(btf2), 8, "inherit_ptr_sz");

	str_off = btf__find_str(btf2, "int");
	ASSERT_NEQ(str_off, -ENOENT, "str_int_missing");

	t = btf__type_by_id(btf2, 1);
	अगर (!ASSERT_OK_PTR(t, "int_type"))
		जाओ cleanup;
	ASSERT_EQ(btf_is_पूर्णांक(t), true, "int_kind");
	ASSERT_STREQ(btf__str_by_offset(btf2, t->name_off), "int", "int_name");

	btf__add_काष्ठा(btf2, "s2", 16);		/* [4] काष्ठा s2 अणु	*/
	btf__add_field(btf2, "f1", 6, 0, 0);		/*      काष्ठा s1 f1;	*/
	btf__add_field(btf2, "f2", 5, 32, 0);		/*      पूर्णांक f2;		*/
	btf__add_field(btf2, "f3", 2, 64, 0);		/*      पूर्णांक *f3;	*/
							/* पूर्ण */

	/* duplicated पूर्णांक */
	btf__add_पूर्णांक(btf2, "int", 4, BTF_INT_SIGNED);	/* [5] पूर्णांक */

	/* duplicated काष्ठा s1 */
	btf__add_काष्ठा(btf2, "s1", 4);			/* [6] काष्ठा s1 अणु */
	btf__add_field(btf2, "f1", 5, 0, 0);		/*      पूर्णांक f1; */
							/* पूर्ण */

	VALIDATE_RAW_BTF(
		btf2,
		"[1] INT 'int' size=4 bits_offset=0 nr_bits=32 encoding=SIGNED",
		"[2] PTR '(anon)' type_id=1",
		"[3] STRUCT 's1' size=4 vlen=1\n"
		"\t'f1' type_id=1 bits_offset=0",
		"[4] STRUCT 's2' size=16 vlen=3\n"
		"\t'f1' type_id=6 bits_offset=0\n"
		"\t'f2' type_id=5 bits_offset=32\n"
		"\t'f3' type_id=2 bits_offset=64",
		"[5] INT 'int' size=4 bits_offset=0 nr_bits=32 encoding=SIGNED",
		"[6] STRUCT 's1' size=4 vlen=1\n"
		"\t'f1' type_id=5 bits_offset=0");

	ASSERT_STREQ(btf_type_c_dump(btf2), "\
काष्ठा s1 अणु\न\
	पूर्णांक f1;\न\
पूर्ण;\न\
\न\
काष्ठा s1___2 अणु\न\
	पूर्णांक f1;\न\
पूर्ण;\न\
\न\
काष्ठा s2 अणु\न\
	काष्ठा s1___2 f1;\न\
	पूर्णांक f2;\न\
	पूर्णांक *f3;\न\
पूर्ण;\न\न", "c_dump");

	err = btf__dedup(btf2, शून्य, शून्य);
	अगर (!ASSERT_OK(err, "btf_dedup"))
		जाओ cleanup;

	VALIDATE_RAW_BTF(
		btf2,
		"[1] INT 'int' size=4 bits_offset=0 nr_bits=32 encoding=SIGNED",
		"[2] PTR '(anon)' type_id=1",
		"[3] STRUCT 's1' size=4 vlen=1\n"
		"\t'f1' type_id=1 bits_offset=0",
		"[4] STRUCT 's2' size=16 vlen=3\n"
		"\t'f1' type_id=3 bits_offset=0\n"
		"\t'f2' type_id=1 bits_offset=32\n"
		"\t'f3' type_id=2 bits_offset=64");

	ASSERT_STREQ(btf_type_c_dump(btf2), "\
काष्ठा s1 अणु\न\
	पूर्णांक f1;\न\
पूर्ण;\न\
\न\
काष्ठा s2 अणु\न\
	काष्ठा s1 f1;\न\
	पूर्णांक f2;\न\
	पूर्णांक *f3;\न\
पूर्ण;\न\न", "c_dump");

cleanup:
	btf__मुक्त(btf2);
	btf__मुक्त(btf1);
पूर्ण

अटल व्योम test_split_fwd_resolve() अणु
	काष्ठा btf *btf1, *btf2;
	पूर्णांक err;

	btf1 = btf__new_empty();
	अगर (!ASSERT_OK_PTR(btf1, "empty_main_btf"))
		वापस;

	btf__set_poपूर्णांकer_size(btf1, 8); /* enक्रमce 64-bit arch */

	btf__add_पूर्णांक(btf1, "int", 4, BTF_INT_SIGNED);	/* [1] पूर्णांक */
	btf__add_ptr(btf1, 4);				/* [2] ptr to काष्ठा s1 */
	btf__add_ptr(btf1, 5);				/* [3] ptr to काष्ठा s2 */
	btf__add_काष्ठा(btf1, "s1", 16);		/* [4] काष्ठा s1 अणु */
	btf__add_field(btf1, "f1", 2, 0, 0);		/*      काष्ठा s1 *f1; */
	btf__add_field(btf1, "f2", 3, 64, 0);		/*      काष्ठा s2 *f2; */
							/* पूर्ण */
	btf__add_काष्ठा(btf1, "s2", 4);			/* [5] काष्ठा s2 अणु */
	btf__add_field(btf1, "f1", 1, 0, 0);		/*      पूर्णांक f1; */
							/* पूर्ण */

	VALIDATE_RAW_BTF(
		btf1,
		"[1] INT 'int' size=4 bits_offset=0 nr_bits=32 encoding=SIGNED",
		"[2] PTR '(anon)' type_id=4",
		"[3] PTR '(anon)' type_id=5",
		"[4] STRUCT 's1' size=16 vlen=2\n"
		"\t'f1' type_id=2 bits_offset=0\n"
		"\t'f2' type_id=3 bits_offset=64",
		"[5] STRUCT 's2' size=4 vlen=1\n"
		"\t'f1' type_id=1 bits_offset=0");

	btf2 = btf__new_empty_split(btf1);
	अगर (!ASSERT_OK_PTR(btf2, "empty_split_btf"))
		जाओ cleanup;

	btf__add_पूर्णांक(btf2, "int", 4, BTF_INT_SIGNED);	/* [6] पूर्णांक */
	btf__add_ptr(btf2, 10);				/* [7] ptr to काष्ठा s1 */
	btf__add_fwd(btf2, "s2", BTF_FWD_STRUCT);	/* [8] fwd क्रम काष्ठा s2 */
	btf__add_ptr(btf2, 8);				/* [9] ptr to fwd काष्ठा s2 */
	btf__add_काष्ठा(btf2, "s1", 16);		/* [10] काष्ठा s1 अणु */
	btf__add_field(btf2, "f1", 7, 0, 0);		/*      काष्ठा s1 *f1; */
	btf__add_field(btf2, "f2", 9, 64, 0);		/*      काष्ठा s2 *f2; */
							/* पूर्ण */

	VALIDATE_RAW_BTF(
		btf2,
		"[1] INT 'int' size=4 bits_offset=0 nr_bits=32 encoding=SIGNED",
		"[2] PTR '(anon)' type_id=4",
		"[3] PTR '(anon)' type_id=5",
		"[4] STRUCT 's1' size=16 vlen=2\n"
		"\t'f1' type_id=2 bits_offset=0\n"
		"\t'f2' type_id=3 bits_offset=64",
		"[5] STRUCT 's2' size=4 vlen=1\n"
		"\t'f1' type_id=1 bits_offset=0",
		"[6] INT 'int' size=4 bits_offset=0 nr_bits=32 encoding=SIGNED",
		"[7] PTR '(anon)' type_id=10",
		"[8] FWD 's2' fwd_kind=struct",
		"[9] PTR '(anon)' type_id=8",
		"[10] STRUCT 's1' size=16 vlen=2\n"
		"\t'f1' type_id=7 bits_offset=0\n"
		"\t'f2' type_id=9 bits_offset=64");

	err = btf__dedup(btf2, शून्य, शून्य);
	अगर (!ASSERT_OK(err, "btf_dedup"))
		जाओ cleanup;

	VALIDATE_RAW_BTF(
		btf2,
		"[1] INT 'int' size=4 bits_offset=0 nr_bits=32 encoding=SIGNED",
		"[2] PTR '(anon)' type_id=4",
		"[3] PTR '(anon)' type_id=5",
		"[4] STRUCT 's1' size=16 vlen=2\n"
		"\t'f1' type_id=2 bits_offset=0\n"
		"\t'f2' type_id=3 bits_offset=64",
		"[5] STRUCT 's2' size=4 vlen=1\n"
		"\t'f1' type_id=1 bits_offset=0");

cleanup:
	btf__मुक्त(btf2);
	btf__मुक्त(btf1);
पूर्ण

अटल व्योम test_split_काष्ठा_duped() अणु
	काष्ठा btf *btf1, *btf2;
	पूर्णांक err;

	btf1 = btf__new_empty();
	अगर (!ASSERT_OK_PTR(btf1, "empty_main_btf"))
		वापस;

	btf__set_poपूर्णांकer_size(btf1, 8); /* enक्रमce 64-bit arch */

	btf__add_पूर्णांक(btf1, "int", 4, BTF_INT_SIGNED);	/* [1] पूर्णांक */
	btf__add_ptr(btf1, 5);				/* [2] ptr to काष्ठा s1 */
	btf__add_fwd(btf1, "s2", BTF_FWD_STRUCT);	/* [3] fwd क्रम काष्ठा s2 */
	btf__add_ptr(btf1, 3);				/* [4] ptr to fwd काष्ठा s2 */
	btf__add_काष्ठा(btf1, "s1", 16);		/* [5] काष्ठा s1 अणु */
	btf__add_field(btf1, "f1", 2, 0, 0);		/*      काष्ठा s1 *f1; */
	btf__add_field(btf1, "f2", 4, 64, 0);		/*      काष्ठा s2 *f2; */
							/* पूर्ण */

	VALIDATE_RAW_BTF(
		btf1,
		"[1] INT 'int' size=4 bits_offset=0 nr_bits=32 encoding=SIGNED",
		"[2] PTR '(anon)' type_id=5",
		"[3] FWD 's2' fwd_kind=struct",
		"[4] PTR '(anon)' type_id=3",
		"[5] STRUCT 's1' size=16 vlen=2\n"
		"\t'f1' type_id=2 bits_offset=0\n"
		"\t'f2' type_id=4 bits_offset=64");

	btf2 = btf__new_empty_split(btf1);
	अगर (!ASSERT_OK_PTR(btf2, "empty_split_btf"))
		जाओ cleanup;

	btf__add_पूर्णांक(btf2, "int", 4, BTF_INT_SIGNED);	/* [6] पूर्णांक */
	btf__add_ptr(btf2, 10);				/* [7] ptr to काष्ठा s1 */
	btf__add_fwd(btf2, "s2", BTF_FWD_STRUCT);	/* [8] fwd क्रम काष्ठा s2 */
	btf__add_ptr(btf2, 11);				/* [9] ptr to काष्ठा s2 */
	btf__add_काष्ठा(btf2, "s1", 16);		/* [10] काष्ठा s1 अणु */
	btf__add_field(btf2, "f1", 7, 0, 0);		/*      काष्ठा s1 *f1; */
	btf__add_field(btf2, "f2", 9, 64, 0);		/*      काष्ठा s2 *f2; */
							/* पूर्ण */
	btf__add_काष्ठा(btf2, "s2", 40);		/* [11] काष्ठा s2 अणु	*/
	btf__add_field(btf2, "f1", 7, 0, 0);		/*      काष्ठा s1 *f1;	*/
	btf__add_field(btf2, "f2", 9, 64, 0);		/*      काष्ठा s2 *f2;	*/
	btf__add_field(btf2, "f3", 6, 128, 0);		/*      पूर्णांक f3;		*/
	btf__add_field(btf2, "f4", 10, 192, 0);		/*      काष्ठा s1 f4;	*/
							/* पूर्ण */
	btf__add_ptr(btf2, 8);				/* [12] ptr to fwd काष्ठा s2 */
	btf__add_काष्ठा(btf2, "s3", 8);			/* [13] काष्ठा s3 अणु */
	btf__add_field(btf2, "f1", 12, 0, 0);		/*      काष्ठा s2 *f1; (fwd) */
							/* पूर्ण */

	VALIDATE_RAW_BTF(
		btf2,
		"[1] INT 'int' size=4 bits_offset=0 nr_bits=32 encoding=SIGNED",
		"[2] PTR '(anon)' type_id=5",
		"[3] FWD 's2' fwd_kind=struct",
		"[4] PTR '(anon)' type_id=3",
		"[5] STRUCT 's1' size=16 vlen=2\n"
		"\t'f1' type_id=2 bits_offset=0\n"
		"\t'f2' type_id=4 bits_offset=64",
		"[6] INT 'int' size=4 bits_offset=0 nr_bits=32 encoding=SIGNED",
		"[7] PTR '(anon)' type_id=10",
		"[8] FWD 's2' fwd_kind=struct",
		"[9] PTR '(anon)' type_id=11",
		"[10] STRUCT 's1' size=16 vlen=2\n"
		"\t'f1' type_id=7 bits_offset=0\n"
		"\t'f2' type_id=9 bits_offset=64",
		"[11] STRUCT 's2' size=40 vlen=4\n"
		"\t'f1' type_id=7 bits_offset=0\n"
		"\t'f2' type_id=9 bits_offset=64\n"
		"\t'f3' type_id=6 bits_offset=128\n"
		"\t'f4' type_id=10 bits_offset=192",
		"[12] PTR '(anon)' type_id=8",
		"[13] STRUCT 's3' size=8 vlen=1\n"
		"\t'f1' type_id=12 bits_offset=0");

	err = btf__dedup(btf2, शून्य, शून्य);
	अगर (!ASSERT_OK(err, "btf_dedup"))
		जाओ cleanup;

	VALIDATE_RAW_BTF(
		btf2,
		"[1] INT 'int' size=4 bits_offset=0 nr_bits=32 encoding=SIGNED",
		"[2] PTR '(anon)' type_id=5",
		"[3] FWD 's2' fwd_kind=struct",
		"[4] PTR '(anon)' type_id=3",
		"[5] STRUCT 's1' size=16 vlen=2\n"
		"\t'f1' type_id=2 bits_offset=0\n"
		"\t'f2' type_id=4 bits_offset=64",
		"[6] PTR '(anon)' type_id=8",
		"[7] PTR '(anon)' type_id=9",
		"[8] STRUCT 's1' size=16 vlen=2\n"
		"\t'f1' type_id=6 bits_offset=0\n"
		"\t'f2' type_id=7 bits_offset=64",
		"[9] STRUCT 's2' size=40 vlen=4\n"
		"\t'f1' type_id=6 bits_offset=0\n"
		"\t'f2' type_id=7 bits_offset=64\n"
		"\t'f3' type_id=1 bits_offset=128\n"
		"\t'f4' type_id=8 bits_offset=192",
		"[10] STRUCT 's3' size=8 vlen=1\n"
		"\t'f1' type_id=7 bits_offset=0");

cleanup:
	btf__मुक्त(btf2);
	btf__मुक्त(btf1);
पूर्ण

व्योम test_btf_dedup_split()
अणु
	अगर (test__start_subtest("split_simple"))
		test_split_simple();
	अगर (test__start_subtest("split_struct_duped"))
		test_split_काष्ठा_duped();
	अगर (test__start_subtest("split_fwd_resolve"))
		test_split_fwd_resolve();
पूर्ण
