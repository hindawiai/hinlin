<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */

#समावेश <test_progs.h>
#समावेश <sys/mman.h>
#समावेश <sys/utsname.h>
#समावेश <linux/version.h>
#समावेश "test_core_extern.skel.h"

अटल uपूर्णांक32_t get_kernel_version(व्योम)
अणु
	uपूर्णांक32_t major, minor, patch;
	काष्ठा utsname info;

	uname(&info);
	अगर (माला_पूछो(info.release, "%u.%u.%u", &major, &minor, &patch) != 3)
		वापस 0;
	वापस KERNEL_VERSION(major, minor, patch);
पूर्ण

#घोषणा CFG "CONFIG_BPF_SYSCALL=n\n"

अटल काष्ठा test_हाल अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *cfg;
	bool fails;
	काष्ठा test_core_बाह्य__data data;
पूर्ण test_हालs[] = अणु
	अणु .name = "default search path", .data = अणु .bpf_syscall = true पूर्ण पूर्ण,
	अणु
		.name = "custom values",
		.cfg = "CONFIG_BPF_SYSCALL=n\n"
		       "CONFIG_TRISTATE=m\n"
		       "CONFIG_BOOL=y\n"
		       "CONFIG_CHAR=100\n"
		       "CONFIG_USHORT=30000\n"
		       "CONFIG_INT=123456\n"
		       "CONFIG_ULONG=0xDEADBEEFC0DE\n"
		       "CONFIG_STR=\"abracad\"\n"
		       "CONFIG_MISSING=0",
		.data = अणु
			.bpf_syscall = false,
			.tristate_val = TRI_MODULE,
			.bool_val = true,
			.अक्षर_val = 100,
			.uलघु_val = 30000,
			.पूर्णांक_val = 123456,
			.uदीर्घ_val = 0xDEADBEEFC0DE,
			.str_val = "abracad",
		पूर्ण,
	पूर्ण,
	/* TRISTATE */
	अणु .name = "tristate (y)", .cfg = CFG"CONFIG_TRISTATE=y\n",
	  .data = अणु .tristate_val = TRI_YES पूर्ण पूर्ण,
	अणु .name = "tristate (n)", .cfg = CFG"CONFIG_TRISTATE=n\n",
	  .data = अणु .tristate_val = TRI_NO पूर्ण पूर्ण,
	अणु .name = "tristate (m)", .cfg = CFG"CONFIG_TRISTATE=m\n",
	  .data = अणु .tristate_val = TRI_MODULE पूर्ण पूर्ण,
	अणु .name = "tristate (int)", .fails = 1, .cfg = CFG"CONFIG_TRISTATE=1" पूर्ण,
	अणु .name = "tristate (bad)", .fails = 1, .cfg = CFG"CONFIG_TRISTATE=M" पूर्ण,
	/* BOOL */
	अणु .name = "bool (y)", .cfg = CFG"CONFIG_BOOL=y\n",
	  .data = अणु .bool_val = true पूर्ण पूर्ण,
	अणु .name = "bool (n)", .cfg = CFG"CONFIG_BOOL=n\n",
	  .data = अणु .bool_val = false पूर्ण पूर्ण,
	अणु .name = "bool (tristate)", .fails = 1, .cfg = CFG"CONFIG_BOOL=m" पूर्ण,
	अणु .name = "bool (int)", .fails = 1, .cfg = CFG"CONFIG_BOOL=1" पूर्ण,
	/* CHAR */
	अणु .name = "char (tristate)", .cfg = CFG"CONFIG_CHAR=m\n",
	  .data = अणु .अक्षर_val = 'm' पूर्ण पूर्ण,
	अणु .name = "char (bad)", .fails = 1, .cfg = CFG"CONFIG_CHAR=q\n" पूर्ण,
	अणु .name = "char (empty)", .fails = 1, .cfg = CFG"CONFIG_CHAR=\n" पूर्ण,
	अणु .name = "char (str)", .fails = 1, .cfg = CFG"CONFIG_CHAR=\"y\"\n" पूर्ण,
	/* STRING */
	अणु .name = "str (empty)", .cfg = CFG"CONFIG_STR=\"\"\n",
	  .data = अणु .str_val = "\0\0\0\0\0\0\0" पूर्ण पूर्ण,
	अणु .name = "str (padded)", .cfg = CFG"CONFIG_STR=\"abra\"\n",
	  .data = अणु .str_val = "abra\0\0\0" पूर्ण पूर्ण,
	अणु .name = "str (too long)", .cfg = CFG"CONFIG_STR=\"abracada\"\n",
	  .data = अणु .str_val = "abracad" पूर्ण पूर्ण,
	अणु .name = "str (no value)", .fails = 1, .cfg = CFG"CONFIG_STR=\n" पूर्ण,
	अणु .name = "str (bad value)", .fails = 1, .cfg = CFG"CONFIG_STR=bla\n" पूर्ण,
	/* INTEGERS */
	अणु
		.name = "integer forms",
		.cfg = CFG
		       "CONFIG_CHAR=0xA\n"
		       "CONFIG_USHORT=0462\n"
		       "CONFIG_INT=-100\n"
		       "CONFIG_ULONG=+1000000000000",
		.data = अणु
			.अक्षर_val = 0xA,
			.uलघु_val = 0462,
			.पूर्णांक_val = -100,
			.uदीर्घ_val = 1000000000000,
		पूर्ण,
	पूर्ण,
	अणु .name = "int (bad)", .fails = 1, .cfg = CFG"CONFIG_INT=abc" पूर्ण,
	अणु .name = "int (str)", .fails = 1, .cfg = CFG"CONFIG_INT=\"abc\"" पूर्ण,
	अणु .name = "int (empty)", .fails = 1, .cfg = CFG"CONFIG_INT=" पूर्ण,
	अणु .name = "int (mixed)", .fails = 1, .cfg = CFG"CONFIG_INT=123abc" पूर्ण,
	अणु .name = "int (max)", .cfg = CFG"CONFIG_INT=2147483647",
	  .data = अणु .पूर्णांक_val = 2147483647 पूर्ण पूर्ण,
	अणु .name = "int (min)", .cfg = CFG"CONFIG_INT=-2147483648",
	  .data = अणु .पूर्णांक_val = -2147483648 पूर्ण पूर्ण,
	अणु .name = "int (max+1)", .fails = 1, .cfg = CFG"CONFIG_INT=2147483648" पूर्ण,
	अणु .name = "int (min-1)", .fails = 1, .cfg = CFG"CONFIG_INT=-2147483649" पूर्ण,
	अणु .name = "ushort (max)", .cfg = CFG"CONFIG_USHORT=65535",
	  .data = अणु .uलघु_val = 65535 पूर्ण पूर्ण,
	अणु .name = "ushort (min)", .cfg = CFG"CONFIG_USHORT=0",
	  .data = अणु .uलघु_val = 0 पूर्ण पूर्ण,
	अणु .name = "ushort (max+1)", .fails = 1, .cfg = CFG"CONFIG_USHORT=65536" पूर्ण,
	अणु .name = "ushort (min-1)", .fails = 1, .cfg = CFG"CONFIG_USHORT=-1" पूर्ण,
	अणु .name = "u64 (max)", .cfg = CFG"CONFIG_ULONG=0xffffffffffffffff",
	  .data = अणु .uदीर्घ_val = 0xffffffffffffffff पूर्ण पूर्ण,
	अणु .name = "u64 (min)", .cfg = CFG"CONFIG_ULONG=0",
	  .data = अणु .uदीर्घ_val = 0 पूर्ण पूर्ण,
	अणु .name = "u64 (max+1)", .fails = 1, .cfg = CFG"CONFIG_ULONG=0x10000000000000000" पूर्ण,
पूर्ण;

व्योम test_core_बाह्य(व्योम)
अणु
	स्थिर uपूर्णांक32_t kern_ver = get_kernel_version();
	पूर्णांक err, duration = 0, i, j;
	काष्ठा test_core_बाह्य *skel = शून्य;
	uपूर्णांक64_t *got, *exp;
	पूर्णांक n = माप(*skel->data) / माप(uपूर्णांक64_t);

	क्रम (i = 0; i < ARRAY_SIZE(test_हालs); i++) अणु
		काष्ठा test_हाल *t = &test_हालs[i];
		DECLARE_LIBBPF_OPTS(bpf_object_खोलो_opts, opts,
			.kconfig = t->cfg,
		);

		अगर (!test__start_subtest(t->name))
			जारी;

		skel = test_core_बाह्य__खोलो_opts(&opts);
		अगर (CHECK(!skel, "skel_open", "skeleton open failed\n"))
			जाओ cleanup;
		err = test_core_बाह्य__load(skel);
		अगर (t->fails) अणु
			CHECK(!err, "skel_load",
			      "shouldn't succeed open/load of skeleton\n");
			जाओ cleanup;
		पूर्ण अन्यथा अगर (CHECK(err, "skel_load",
				 "failed to open/load skeleton\n")) अणु
			जाओ cleanup;
		पूर्ण
		err = test_core_बाह्य__attach(skel);
		अगर (CHECK(err, "attach_raw_tp", "failed attach: %d\n", err))
			जाओ cleanup;

		usleep(1);

		t->data.kern_ver = kern_ver;
		t->data.missing_val = 0xDEADC0DE;
		got = (uपूर्णांक64_t *)skel->data;
		exp = (uपूर्णांक64_t *)&t->data;
		क्रम (j = 0; j < n; j++) अणु
			CHECK(got[j] != exp[j], "check_res",
			      "result #%d: expected %llx, but got %llx\n",
			       j, (__u64)exp[j], (__u64)got[j]);
		पूर्ण
cleanup:
		test_core_बाह्य__destroy(skel);
		skel = शून्य;
	पूर्ण
पूर्ण
