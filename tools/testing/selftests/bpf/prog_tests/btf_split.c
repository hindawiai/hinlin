<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <test_progs.h>
#समावेश <bpf/btf.h>

अटल अक्षर *dump_buf;
अटल माप_प्रकार dump_buf_sz;
अटल खाता *dump_buf_file;

अटल व्योम btf_dump_म_लिखो(व्योम *ctx, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	भख_लिखो(ctx, fmt, args);
पूर्ण

व्योम test_btf_split() अणु
	काष्ठा btf_dump_opts opts;
	काष्ठा btf_dump *d = शून्य;
	स्थिर काष्ठा btf_type *t;
	काष्ठा btf *btf1, *btf2;
	पूर्णांक str_off, i, err;

	btf1 = btf__new_empty();
	अगर (!ASSERT_OK_PTR(btf1, "empty_main_btf"))
		वापस;

	btf__set_poपूर्णांकer_size(btf1, 8); /* enक्रमce 64-bit arch */

	btf__add_पूर्णांक(btf1, "int", 4, BTF_INT_SIGNED);	/* [1] पूर्णांक */
	btf__add_ptr(btf1, 1);				/* [2] ptr to पूर्णांक */

	btf__add_काष्ठा(btf1, "s1", 4);			/* [3] काष्ठा s1 अणु */
	btf__add_field(btf1, "f1", 1, 0, 0);		/*      पूर्णांक f1; */
							/* पूर्ण */

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
	btf__add_field(btf2, "f1", 3, 0, 0);		/*      काष्ठा s1 f1;	*/
	btf__add_field(btf2, "f2", 1, 32, 0);		/*      पूर्णांक f2;		*/
	btf__add_field(btf2, "f3", 2, 64, 0);		/*      पूर्णांक *f3;	*/
							/* पूर्ण */

	t = btf__type_by_id(btf1, 4);
	ASSERT_शून्य(t, "split_type_in_main");

	t = btf__type_by_id(btf2, 4);
	अगर (!ASSERT_OK_PTR(t, "split_struct_type"))
		जाओ cleanup;
	ASSERT_EQ(btf_is_काष्ठा(t), true, "split_struct_kind");
	ASSERT_EQ(btf_vlen(t), 3, "split_struct_vlen");
	ASSERT_STREQ(btf__str_by_offset(btf2, t->name_off), "s2", "split_struct_name");

	/* BTF-to-C dump of split BTF */
	dump_buf_file = खोलो_memstream(&dump_buf, &dump_buf_sz);
	अगर (!ASSERT_OK_PTR(dump_buf_file, "dump_memstream"))
		वापस;
	opts.ctx = dump_buf_file;
	d = btf_dump__new(btf2, शून्य, &opts, btf_dump_म_लिखो);
	अगर (!ASSERT_OK_PTR(d, "btf_dump__new"))
		जाओ cleanup;
	क्रम (i = 1; i <= btf__get_nr_types(btf2); i++) अणु
		err = btf_dump__dump_type(d, i);
		ASSERT_OK(err, "dump_type_ok");
	पूर्ण
	ख_साफ(dump_buf_file);
	dump_buf[dump_buf_sz] = 0; /* some libc implementations करोn't करो this */
	ASSERT_STREQ(dump_buf,
"struct s1 {\n"
"	int f1;\n"
"};\n"
"\n"
"struct s2 {\n"
"	struct s1 f1;\n"
"	int f2;\n"
"	int *f3;\n"
"};\n\n", "c_dump");

cleanup:
	अगर (dump_buf_file)
		ख_बंद(dump_buf_file);
	मुक्त(dump_buf);
	btf_dump__मुक्त(d);
	btf__मुक्त(btf1);
	btf__मुक्त(btf2);
पूर्ण
