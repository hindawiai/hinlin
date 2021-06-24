<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <bpf/btf.h>

अटल पूर्णांक duration = 0;

व्योम btf_dump_म_लिखो(व्योम *ctx, स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	भख_लिखो(ctx, fmt, args);
पूर्ण

अटल काष्ठा btf_dump_test_हाल अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *file;
	bool known_ptr_sz;
	काष्ठा btf_dump_opts opts;
पूर्ण btf_dump_test_हालs[] = अणु
	अणु"btf_dump: syntax", "btf_dump_test_case_syntax", true, अणुपूर्णपूर्ण,
	अणु"btf_dump: ordering", "btf_dump_test_case_ordering", false, अणुपूर्णपूर्ण,
	अणु"btf_dump: padding", "btf_dump_test_case_padding", true, अणुपूर्णपूर्ण,
	अणु"btf_dump: packing", "btf_dump_test_case_packing", true, अणुपूर्णपूर्ण,
	अणु"btf_dump: bitfields", "btf_dump_test_case_bitfields", true, अणुपूर्णपूर्ण,
	अणु"btf_dump: multidim", "btf_dump_test_case_multidim", false, अणुपूर्णपूर्ण,
	अणु"btf_dump: namespacing", "btf_dump_test_case_namespacing", false, अणुपूर्णपूर्ण,
पूर्ण;

अटल पूर्णांक btf_dump_all_types(स्थिर काष्ठा btf *btf,
			      स्थिर काष्ठा btf_dump_opts *opts)
अणु
	माप_प्रकार type_cnt = btf__get_nr_types(btf);
	काष्ठा btf_dump *d;
	पूर्णांक err = 0, id;

	d = btf_dump__new(btf, शून्य, opts, btf_dump_म_लिखो);
	अगर (IS_ERR(d))
		वापस PTR_ERR(d);

	क्रम (id = 1; id <= type_cnt; id++) अणु
		err = btf_dump__dump_type(d, id);
		अगर (err)
			जाओ करोne;
	पूर्ण

करोne:
	btf_dump__मुक्त(d);
	वापस err;
पूर्ण

अटल पूर्णांक test_btf_dump_हाल(पूर्णांक n, काष्ठा btf_dump_test_हाल *t)
अणु
	अक्षर test_file[256], out_file[256], dअगरf_cmd[1024];
	काष्ठा btf *btf = शून्य;
	पूर्णांक err = 0, fd = -1;
	खाता *f = शून्य;

	snम_लिखो(test_file, माप(test_file), "%s.o", t->file);

	btf = btf__parse_elf(test_file, शून्य);
	अगर (CHECK(IS_ERR(btf), "btf_parse_elf",
	    "failed to load test BTF: %ld\n", PTR_ERR(btf))) अणु
		err = -PTR_ERR(btf);
		btf = शून्य;
		जाओ करोne;
	पूर्ण

	/* tests with t->known_ptr_sz have no "long" or "unsigned long" type,
	 * so it's impossible to determine correct poपूर्णांकer size; but अगर they
	 * करो, it should be 8 regardless of host architecture, becaues BPF
	 * target is always 64-bit
	 */
	अगर (!t->known_ptr_sz) अणु
		btf__set_poपूर्णांकer_size(btf, 8);
	पूर्ण अन्यथा अणु
		CHECK(btf__poपूर्णांकer_size(btf) != 8, "ptr_sz", "exp %d, got %zu\n",
		      8, btf__poपूर्णांकer_size(btf));
	पूर्ण

	snम_लिखो(out_file, माप(out_file), "/tmp/%s.output.XXXXXX", t->file);
	fd = mkstemp(out_file);
	अगर (!ASSERT_GE(fd, 0, "create_tmp")) अणु
		err = fd;
		जाओ करोne;
	पूर्ण
	f = fकरोpen(fd, "w");
	अगर (CHECK(f == शून्य, "open_tmp",  "failed to open file: %s(%d)\n",
		  म_त्रुटि(त्रुटि_सं), त्रुटि_सं)) अणु
		बंद(fd);
		जाओ करोne;
	पूर्ण

	t->opts.ctx = f;
	err = btf_dump_all_types(btf, &t->opts);
	ख_बंद(f);
	बंद(fd);
	अगर (CHECK(err, "btf_dump", "failure during C dumping: %d\n", err)) अणु
		जाओ करोne;
	पूर्ण

	snम_लिखो(test_file, माप(test_file), "progs/%s.c", t->file);
	अगर (access(test_file, R_OK) == -1)
		/*
		 * When the test is run with O=, kselftest copies TEST_खाताS
		 * without preserving the directory काष्ठाure.
		 */
		snम_लिखो(test_file, माप(test_file), "%s.c", t->file);
	/*
	 * Dअगरf test output and expected test output, contained between
	 * START-EXPECTED-OUTPUT and END-EXPECTED-OUTPUT lines in test हाल.
	 * For expected output lines, everything beक्रमe '*' is stripped out.
	 * Also lines containing comment start and comment end markers are
	 * ignored. 
	 */
	snम_लिखो(dअगरf_cmd, माप(dअगरf_cmd),
		 "awk '/START-EXPECTED-OUTPUT/{out=1;next} "
		 "/END-EXPECTED-OUTPUT/{out=0} "
		 "/\\/\\*|\\*\\//{next} " /* ignore comment start/end lines */
		 "out अणुsub(/^[ \\ट]*\\*/, \"\"); print}' '%s' | diff -u - '%s'",
		 test_file, out_file);
	err = प्रणाली(dअगरf_cmd);
	अगर (CHECK(err, "diff",
		  "differing test output, output=%s, err=%d, diff cmd:\n%s\n",
		  out_file, err, dअगरf_cmd))
		जाओ करोne;

	हटाओ(out_file);

करोne:
	btf__मुक्त(btf);
	वापस err;
पूर्ण

अटल अक्षर *dump_buf;
अटल माप_प्रकार dump_buf_sz;
अटल खाता *dump_buf_file;

व्योम test_btf_dump_incremental(व्योम)
अणु
	काष्ठा btf *btf = शून्य;
	काष्ठा btf_dump *d = शून्य;
	काष्ठा btf_dump_opts opts;
	पूर्णांक id, err, i;

	dump_buf_file = खोलो_memstream(&dump_buf, &dump_buf_sz);
	अगर (!ASSERT_OK_PTR(dump_buf_file, "dump_memstream"))
		वापस;
	btf = btf__new_empty();
	अगर (!ASSERT_OK_PTR(btf, "new_empty"))
		जाओ err_out;
	opts.ctx = dump_buf_file;
	d = btf_dump__new(btf, शून्य, &opts, btf_dump_म_लिखो);
	अगर (!ASSERT_OK(libbpf_get_error(d), "btf_dump__new"))
		जाओ err_out;

	/* First, generate BTF corresponding to the following C code:
	 *
	 * क्रमागत अणु VAL = 1 पूर्ण;
	 *
	 * काष्ठा s अणु पूर्णांक x; पूर्ण;
	 *
	 */
	id = btf__add_क्रमागत(btf, शून्य, 4);
	ASSERT_EQ(id, 1, "enum_id");
	err = btf__add_क्रमागत_value(btf, "VAL", 1);
	ASSERT_OK(err, "enum_val_ok");

	id = btf__add_पूर्णांक(btf, "int", 4, BTF_INT_SIGNED);
	ASSERT_EQ(id, 2, "int_id");

	id = btf__add_काष्ठा(btf, "s", 4);
	ASSERT_EQ(id, 3, "struct_id");
	err = btf__add_field(btf, "x", 2, 0, 0);
	ASSERT_OK(err, "field_ok");

	क्रम (i = 1; i <= btf__get_nr_types(btf); i++) अणु
		err = btf_dump__dump_type(d, i);
		ASSERT_OK(err, "dump_type_ok");
	पूर्ण

	ख_साफ(dump_buf_file);
	dump_buf[dump_buf_sz] = 0; /* some libc implementations करोn't करो this */
	ASSERT_STREQ(dump_buf,
"enum {\n"
"	VAL = 1,\n"
"};\n"
"\n"
"struct s {\n"
"	int x;\n"
"};\n\n", "c_dump1");

	/* Now, after dumping original BTF, append another काष्ठा that embeds
	 * anonymous क्रमागत. It also has a name conflict with the first काष्ठा:
	 *
	 * काष्ठा s___2 अणु
	 *     क्रमागत अणु VAL___2 = 1 पूर्ण x;
	 *     काष्ठा s s;
	 * पूर्ण;
	 *
	 * This will test that btf_dump'er मुख्यtains पूर्णांकernal state properly.
	 * Note that VAL___2 क्रमागत value. It's because we've alपढ़ोy emitted
	 * that क्रमागत as a global anonymous क्रमागत, so btf_dump will ensure that
	 * क्रमागत values करोn't conflict;
	 *
	 */
	ख_जाओ(dump_buf_file, 0, शुरू_से);

	id = btf__add_काष्ठा(btf, "s", 4);
	ASSERT_EQ(id, 4, "struct_id");
	err = btf__add_field(btf, "x", 1, 0, 0);
	ASSERT_OK(err, "field_ok");
	err = btf__add_field(btf, "s", 3, 32, 0);
	ASSERT_OK(err, "field_ok");

	क्रम (i = 1; i <= btf__get_nr_types(btf); i++) अणु
		err = btf_dump__dump_type(d, i);
		ASSERT_OK(err, "dump_type_ok");
	पूर्ण

	ख_साफ(dump_buf_file);
	dump_buf[dump_buf_sz] = 0; /* some libc implementations करोn't करो this */
	ASSERT_STREQ(dump_buf,
"struct s___2 {\n"
"	enum {\n"
"		VAL___2 = 1,\n"
"	} x;\n"
"	struct s s;\n"
"};\n\n" , "c_dump1");

err_out:
	ख_बंद(dump_buf_file);
	मुक्त(dump_buf);
	btf_dump__मुक्त(d);
	btf__मुक्त(btf);
पूर्ण

व्योम test_btf_dump() अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(btf_dump_test_हालs); i++) अणु
		काष्ठा btf_dump_test_हाल *t = &btf_dump_test_हालs[i];

		अगर (!test__start_subtest(t->name))
			जारी;

		test_btf_dump_हाल(i, &btf_dump_test_हालs[i]);
	पूर्ण
	अगर (test__start_subtest("btf_dump: incremental"))
		test_btf_dump_incremental();
पूर्ण
