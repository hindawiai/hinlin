<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <stdbool.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <subcmd/exec-cmd.h>

#समावेश "debug.h"
#समावेश "util/build-id.h"
#समावेश "util/symbol.h"
#समावेश "util/dso.h"

#समावेश "tests.h"

#अगर_घोषित HAVE_LIBBFD_SUPPORT

अटल पूर्णांक run_dir(स्थिर अक्षर *d)
अणु
	अक्षर filename[PATH_MAX];
	अक्षर debugfile[PATH_MAX];
	काष्ठा build_id bid;
	अक्षर debuglink[PATH_MAX];
	अक्षर expect_build_id[] = अणु
		0x5a, 0x0f, 0xd8, 0x82, 0xb5, 0x30, 0x84, 0x22,
		0x4b, 0xa4, 0x7b, 0x62, 0x4c, 0x55, 0xa4, 0x69,
	पूर्ण;
	अक्षर expect_debuglink[PATH_MAX] = "pe-file.exe.debug";
	काष्ठा dso *dso;
	काष्ठा symbol *sym;
	पूर्णांक ret;

	scnम_लिखो(filename, PATH_MAX, "%s/pe-file.exe", d);
	ret = filename__पढ़ो_build_id(filename, &bid);
	TEST_ASSERT_VAL("Failed to read build_id",
			ret == माप(expect_build_id));
	TEST_ASSERT_VAL("Wrong build_id", !स_भेद(bid.data, expect_build_id,
						  माप(expect_build_id)));

	ret = filename__पढ़ो_debuglink(filename, debuglink, PATH_MAX);
	TEST_ASSERT_VAL("Failed to read debuglink", ret == 0);
	TEST_ASSERT_VAL("Wrong debuglink",
			!म_भेद(debuglink, expect_debuglink));

	scnम_लिखो(debugfile, PATH_MAX, "%s/%s", d, debuglink);
	ret = filename__पढ़ो_build_id(debugfile, &bid);
	TEST_ASSERT_VAL("Failed to read debug file build_id",
			ret == माप(expect_build_id));
	TEST_ASSERT_VAL("Wrong build_id", !स_भेद(bid.data, expect_build_id,
						  माप(expect_build_id)));

	dso = dso__new(filename);
	TEST_ASSERT_VAL("Failed to get dso", dso);

	ret = dso__load_bfd_symbols(dso, debugfile);
	TEST_ASSERT_VAL("Failed to load symbols", ret == 0);

	dso__sort_by_name(dso);
	sym = dso__find_symbol_by_name(dso, "main");
	TEST_ASSERT_VAL("Failed to find main", sym);
	dso__delete(dso);

	वापस TEST_OK;
पूर्ण

पूर्णांक test__pe_file_parsing(काष्ठा test *test __maybe_unused,
			  पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा stat st;
	अक्षर path_dir[PATH_MAX];

	/* First try development tree tests. */
	अगर (!lstat("./tests", &st))
		वापस run_dir("./tests");

	/* Then installed path. */
	snम_लिखो(path_dir, PATH_MAX, "%s/tests", get_argv_exec_path());

	अगर (!lstat(path_dir, &st))
		वापस run_dir(path_dir);

	वापस TEST_SKIP;
पूर्ण

#अन्यथा

पूर्णांक test__pe_file_parsing(काष्ठा test *test __maybe_unused,
			  पूर्णांक subtest __maybe_unused)
अणु
	वापस TEST_SKIP;
पूर्ण

#पूर्ण_अगर
