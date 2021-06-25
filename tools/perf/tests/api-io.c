<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश "debug.h"
#समावेश "tests.h"
#समावेश <api/पन.स>
#समावेश <linux/kernel.h>

#घोषणा TEMPL "/tmp/perf-test-XXXXXX"

#घोषणा EXPECT_EQUAL(val, expected)                             \
करो अणु								\
	अगर (val != expected) अणु					\
		pr_debug("%s:%d: %d != %d\n",			\
			__खाता__, __LINE__, val, expected);	\
		ret = -1;					\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा EXPECT_EQUAL64(val, expected)                           \
करो अणु								\
	अगर (val != expected) अणु					\
		pr_debug("%s:%d: %lld != %lld\n",		\
			__खाता__, __LINE__, val, expected);	\
		ret = -1;					\
	पूर्ण							\
पूर्ण जबतक (0)

अटल पूर्णांक make_test_file(अक्षर path[PATH_MAX], स्थिर अक्षर *contents)
अणु
	sमाप_प्रकार contents_len = म_माप(contents);
	पूर्णांक fd;

	म_नकल(path, TEMPL);
	fd = mkstemp(path);
	अगर (fd < 0) अणु
		pr_debug("mkstemp failed");
		वापस -1;
	पूर्ण
	अगर (ग_लिखो(fd, contents, contents_len) < contents_len) अणु
		pr_debug("short write");
		बंद(fd);
		unlink(path);
		वापस -1;
	पूर्ण
	बंद(fd);
	वापस 0;
पूर्ण

अटल पूर्णांक setup_test(अक्षर path[PATH_MAX], स्थिर अक्षर *contents,
		      माप_प्रकार buf_size, काष्ठा io *io)
अणु
	अगर (make_test_file(path, contents))
		वापस -1;

	io->fd = खोलो(path, O_RDONLY);
	अगर (io->fd < 0) अणु
		pr_debug("Failed to open '%s'\n", path);
		unlink(path);
		वापस -1;
	पूर्ण
	io->buf = दो_स्मृति(buf_size);
	अगर (io->buf == शून्य) अणु
		pr_debug("Failed to allocate memory");
		बंद(io->fd);
		unlink(path);
		वापस -1;
	पूर्ण
	io__init(io, io->fd, io->buf, buf_size);
	वापस 0;
पूर्ण

अटल व्योम cleanup_test(अक्षर path[PATH_MAX], काष्ठा io *io)
अणु
	मुक्त(io->buf);
	बंद(io->fd);
	unlink(path);
पूर्ण

अटल पूर्णांक करो_test_get_अक्षर(स्थिर अक्षर *test_string, माप_प्रकार buf_size)
अणु
	अक्षर path[PATH_MAX];
	काष्ठा io io;
	पूर्णांक ch, ret = 0;
	माप_प्रकार i;

	अगर (setup_test(path, test_string, buf_size, &io))
		वापस -1;

	क्रम (i = 0; i < म_माप(test_string); i++) अणु
		ch = io__get_अक्षर(&io);

		EXPECT_EQUAL(ch, test_string[i]);
		EXPECT_EQUAL(io.eof, false);
	पूर्ण
	ch = io__get_अक्षर(&io);
	EXPECT_EQUAL(ch, -1);
	EXPECT_EQUAL(io.eof, true);

	cleanup_test(path, &io);
	वापस ret;
पूर्ण

अटल पूर्णांक test_get_अक्षर(व्योम)
अणु
	पूर्णांक i, ret = 0;
	माप_प्रकार j;

	अटल स्थिर अक्षर *स्थिर test_strings[] = अणु
		"12345678abcdef90",
		"a\nb\nc\nd\n",
		"\a\b\t\v\f\r",
	पूर्ण;
	क्रम (i = 0; i <= 10; i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(test_strings); j++) अणु
			अगर (करो_test_get_अक्षर(test_strings[j], 1 << i))
				ret = -1;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक करो_test_get_hex(स्थिर अक्षर *test_string,
			__u64 val1, पूर्णांक ch1,
			__u64 val2, पूर्णांक ch2,
			__u64 val3, पूर्णांक ch3,
			bool end_eof)
अणु
	अक्षर path[PATH_MAX];
	काष्ठा io io;
	पूर्णांक ch, ret = 0;
	__u64 hex;

	अगर (setup_test(path, test_string, 4, &io))
		वापस -1;

	ch = io__get_hex(&io, &hex);
	EXPECT_EQUAL64(hex, val1);
	EXPECT_EQUAL(ch, ch1);

	ch = io__get_hex(&io, &hex);
	EXPECT_EQUAL64(hex, val2);
	EXPECT_EQUAL(ch, ch2);

	ch = io__get_hex(&io, &hex);
	EXPECT_EQUAL64(hex, val3);
	EXPECT_EQUAL(ch, ch3);

	EXPECT_EQUAL(io.eof, end_eof);

	cleanup_test(path, &io);
	वापस ret;
पूर्ण

अटल पूर्णांक test_get_hex(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (करो_test_get_hex("12345678abcdef90",
				0x12345678abcdef90, -1,
				0, -1,
				0, -1,
				true))
		ret = -1;

	अगर (करो_test_get_hex("1\n2\n3\n",
				1, '\n',
				2, '\n',
				3, '\n',
				false))
		ret = -1;

	अगर (करो_test_get_hex("12345678ABCDEF90;a;b",
				0x12345678abcdef90, ';',
				0xa, ';',
				0xb, -1,
				true))
		ret = -1;

	अगर (करो_test_get_hex("0x1x2x",
				0, 'x',
				1, 'x',
				2, 'x',
				false))
		ret = -1;

	अगर (करो_test_get_hex("x1x",
				0, -2,
				1, 'x',
				0, -1,
				true))
		ret = -1;

	अगर (करो_test_get_hex("10000000000000000000000000000abcdefgh99i",
				0xabcdef, 'g',
				0, -2,
				0x99, 'i',
				false))
		ret = -1;

	वापस ret;
पूर्ण

अटल पूर्णांक करो_test_get_dec(स्थिर अक्षर *test_string,
			__u64 val1, पूर्णांक ch1,
			__u64 val2, पूर्णांक ch2,
			__u64 val3, पूर्णांक ch3,
			bool end_eof)
अणु
	अक्षर path[PATH_MAX];
	काष्ठा io io;
	पूर्णांक ch, ret = 0;
	__u64 dec;

	अगर (setup_test(path, test_string, 4, &io))
		वापस -1;

	ch = io__get_dec(&io, &dec);
	EXPECT_EQUAL64(dec, val1);
	EXPECT_EQUAL(ch, ch1);

	ch = io__get_dec(&io, &dec);
	EXPECT_EQUAL64(dec, val2);
	EXPECT_EQUAL(ch, ch2);

	ch = io__get_dec(&io, &dec);
	EXPECT_EQUAL64(dec, val3);
	EXPECT_EQUAL(ch, ch3);

	EXPECT_EQUAL(io.eof, end_eof);

	cleanup_test(path, &io);
	वापस ret;
पूर्ण

अटल पूर्णांक test_get_dec(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (करो_test_get_dec("12345678abcdef90",
				12345678, 'a',
				0, -2,
				0, -2,
				false))
		ret = -1;

	अगर (करो_test_get_dec("1\n2\n3\n",
				1, '\n',
				2, '\n',
				3, '\n',
				false))
		ret = -1;

	अगर (करो_test_get_dec("12345678;1;2",
				12345678, ';',
				1, ';',
				2, -1,
				true))
		ret = -1;

	अगर (करो_test_get_dec("0x1x2x",
				0, 'x',
				1, 'x',
				2, 'x',
				false))
		ret = -1;

	अगर (करो_test_get_dec("x1x",
				0, -2,
				1, 'x',
				0, -1,
				true))
		ret = -1;

	अगर (करो_test_get_dec("10000000000000000000000000000000000000000000000000000000000123456789ab99c",
				123456789, 'a',
				0, -2,
				99, 'c',
				false))
		ret = -1;

	वापस ret;
पूर्ण

पूर्णांक test__api_io(काष्ठा test *test __maybe_unused,
		पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक ret = 0;

	अगर (test_get_अक्षर())
		ret = TEST_FAIL;
	अगर (test_get_hex())
		ret = TEST_FAIL;
	अगर (test_get_dec())
		ret = TEST_FAIL;
	वापस ret;
पूर्ण
