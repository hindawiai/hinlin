<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <dirent.h>
#समावेश <मानककोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <api/fs/fs.h>
#समावेश "dso.h"
#समावेश "machine.h"
#समावेश "symbol.h"
#समावेश "tests.h"
#समावेश "debug.h"

अटल अक्षर *test_file(पूर्णांक size)
अणु
#घोषणा TEMPL "/tmp/perf-test-XXXXXX"
	अटल अक्षर buf_templ[माप(TEMPL)];
	अक्षर *templ = buf_templ;
	पूर्णांक fd, i;
	अचिन्हित अक्षर *buf;

	म_नकल(buf_templ, TEMPL);
#अघोषित TEMPL

	fd = mkstemp(templ);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("mkstemp failed");
		वापस शून्य;
	पूर्ण

	buf = दो_स्मृति(size);
	अगर (!buf) अणु
		बंद(fd);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < size; i++)
		buf[i] = (अचिन्हित अक्षर) ((पूर्णांक) i % 10);

	अगर (size != ग_लिखो(fd, buf, size))
		templ = शून्य;

	मुक्त(buf);
	बंद(fd);
	वापस templ;
पूर्ण

#घोषणा TEST_खाता_SIZE (DSO__DATA_CACHE_SIZE * 20)

काष्ठा test_data_offset अणु
	off_t offset;
	u8 data[10];
	पूर्णांक size;
पूर्ण;

काष्ठा test_data_offset offsets[] = अणु
	/* Fill first cache page. */
	अणु
		.offset = 10,
		.data   = अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 पूर्ण,
		.size   = 10,
	पूर्ण,
	/* Read first cache page. */
	अणु
		.offset = 10,
		.data   = अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 पूर्ण,
		.size   = 10,
	पूर्ण,
	/* Fill cache boundary pages. */
	अणु
		.offset = DSO__DATA_CACHE_SIZE - DSO__DATA_CACHE_SIZE % 10,
		.data   = अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 पूर्ण,
		.size   = 10,
	पूर्ण,
	/* Read cache boundary pages. */
	अणु
		.offset = DSO__DATA_CACHE_SIZE - DSO__DATA_CACHE_SIZE % 10,
		.data   = अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 पूर्ण,
		.size   = 10,
	पूर्ण,
	/* Fill final cache page. */
	अणु
		.offset = TEST_खाता_SIZE - 10,
		.data   = अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 पूर्ण,
		.size   = 10,
	पूर्ण,
	/* Read final cache page. */
	अणु
		.offset = TEST_खाता_SIZE - 10,
		.data   = अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 पूर्ण,
		.size   = 10,
	पूर्ण,
	/* Read final cache page. */
	अणु
		.offset = TEST_खाता_SIZE - 3,
		.data   = अणु 7, 8, 9, 0, 0, 0, 0, 0, 0, 0 पूर्ण,
		.size   = 3,
	पूर्ण,
पूर्ण;

/* move it from util/dso.c क्रम compatibility */
अटल पूर्णांक dso__data_fd(काष्ठा dso *dso, काष्ठा machine *machine)
अणु
	पूर्णांक fd = dso__data_get_fd(dso, machine);

	अगर (fd >= 0)
		dso__data_put_fd(dso);

	वापस fd;
पूर्ण

पूर्णांक test__dso_data(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा machine machine;
	काष्ठा dso *dso;
	अक्षर *file = test_file(TEST_खाता_SIZE);
	माप_प्रकार i;

	TEST_ASSERT_VAL("No test file", file);

	स_रखो(&machine, 0, माप(machine));

	dso = dso__new((स्थिर अक्षर *)file);

	TEST_ASSERT_VAL("Failed to access to dso",
			dso__data_fd(dso, &machine) >= 0);

	/* Basic 10 bytes tests. */
	क्रम (i = 0; i < ARRAY_SIZE(offsets); i++) अणु
		काष्ठा test_data_offset *data = &offsets[i];
		sमाप_प्रकार size;
		u8 buf[10];

		स_रखो(buf, 0, 10);
		size = dso__data_पढ़ो_offset(dso, &machine, data->offset,
				     buf, 10);

		TEST_ASSERT_VAL("Wrong size", size == data->size);
		TEST_ASSERT_VAL("Wrong data", !स_भेद(buf, data->data, 10));
	पूर्ण

	/* Read cross multiple cache pages. */
	अणु
		sमाप_प्रकार size;
		पूर्णांक c;
		u8 *buf;

		buf = दो_स्मृति(TEST_खाता_SIZE);
		TEST_ASSERT_VAL("ENOMEM\n", buf);

		/* First iteration to fill caches, second one to पढ़ो them. */
		क्रम (c = 0; c < 2; c++) अणु
			स_रखो(buf, 0, TEST_खाता_SIZE);
			size = dso__data_पढ़ो_offset(dso, &machine, 10,
						     buf, TEST_खाता_SIZE);

			TEST_ASSERT_VAL("Wrong size",
				size == (TEST_खाता_SIZE - 10));

			क्रम (i = 0; i < (माप_प्रकार)size; i++)
				TEST_ASSERT_VAL("Wrong data",
					buf[i] == (i % 10));
		पूर्ण

		मुक्त(buf);
	पूर्ण

	dso__put(dso);
	unlink(file);
	वापस 0;
पूर्ण

अटल दीर्घ खोलो_files_cnt(व्योम)
अणु
	अक्षर path[PATH_MAX];
	काष्ठा dirent *dent;
	सूची *dir;
	दीर्घ nr = 0;

	scnम_लिखो(path, PATH_MAX, "%s/self/fd", procfs__mountpoपूर्णांक());
	pr_debug("fd path: %s\n", path);

	dir = सूची_खोलो(path);
	TEST_ASSERT_VAL("failed to open fd directory", dir);

	जबतक ((dent = सूची_पढ़ो(dir)) != शून्य) अणु
		अगर (!म_भेद(dent->d_name, ".") ||
		    !म_भेद(dent->d_name, ".."))
			जारी;

		nr++;
	पूर्ण

	बंद_सूची(dir);
	वापस nr - 1;
पूर्ण

अटल काष्ठा dso **dsos;

अटल पूर्णांक dsos__create(पूर्णांक cnt, पूर्णांक size)
अणु
	पूर्णांक i;

	dsos = दो_स्मृति(माप(*dsos) * cnt);
	TEST_ASSERT_VAL("failed to alloc dsos array", dsos);

	क्रम (i = 0; i < cnt; i++) अणु
		अक्षर *file;

		file = test_file(size);
		TEST_ASSERT_VAL("failed to get dso file", file);

		dsos[i] = dso__new(file);
		TEST_ASSERT_VAL("failed to get dso", dsos[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dsos__delete(पूर्णांक cnt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cnt; i++) अणु
		काष्ठा dso *dso = dsos[i];

		unlink(dso->name);
		dso__put(dso);
	पूर्ण

	मुक्त(dsos);
पूर्ण

अटल पूर्णांक set_fd_limit(पूर्णांक n)
अणु
	काष्ठा rlimit rlim;

	अगर (getrlimit(RLIMIT_NOखाता, &rlim))
		वापस -1;

	pr_debug("file limit %ld, new %d\n", (दीर्घ) rlim.rlim_cur, n);

	rlim.rlim_cur = n;
	वापस setrlimit(RLIMIT_NOखाता, &rlim);
पूर्ण

पूर्णांक test__dso_data_cache(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा machine machine;
	दीर्घ nr_end, nr = खोलो_files_cnt();
	पूर्णांक dso_cnt, limit, i, fd;

	/* Rest the पूर्णांकernal dso खोलो counter limit. */
	reset_fd_limit();

	स_रखो(&machine, 0, माप(machine));

	/* set as प्रणाली limit */
	limit = nr * 4;
	TEST_ASSERT_VAL("failed to set file limit", !set_fd_limit(limit));

	/* and this is now our dso खोलो FDs limit */
	dso_cnt = limit / 2;
	TEST_ASSERT_VAL("failed to create dsos\n",
		!dsos__create(dso_cnt, TEST_खाता_SIZE));

	क्रम (i = 0; i < (dso_cnt - 1); i++) अणु
		काष्ठा dso *dso = dsos[i];

		/*
		 * Open dsos via dso__data_fd(), it खोलोs the data
		 * file and keep it खोलो (unless खोलो file limit).
		 */
		fd = dso__data_fd(dso, &machine);
		TEST_ASSERT_VAL("failed to get fd", fd > 0);

		अगर (i % 2) अणु
			#घोषणा बफ_मानE 10
			u8 buf[बफ_मानE];
			sमाप_प्रकार n;

			n = dso__data_पढ़ो_offset(dso, &machine, 0, buf, बफ_मानE);
			TEST_ASSERT_VAL("failed to read dso", n == बफ_मानE);
		पूर्ण
	पूर्ण

	/* verअगरy the first one is alपढ़ोy खोलो */
	TEST_ASSERT_VAL("dsos[0] is not open", dsos[0]->data.fd != -1);

	/* खोलो +1 dso to reach the allowed limit */
	fd = dso__data_fd(dsos[i], &machine);
	TEST_ASSERT_VAL("failed to get fd", fd > 0);

	/* should क्रमce the first one to be बंदd */
	TEST_ASSERT_VAL("failed to close dsos[0]", dsos[0]->data.fd == -1);

	/* cleanup everything */
	dsos__delete(dso_cnt);

	/* Make sure we did not leak any file descriptor. */
	nr_end = खोलो_files_cnt();
	pr_debug("nr start %ld, nr stop %ld\n", nr, nr_end);
	TEST_ASSERT_VAL("failed leaking files", nr == nr_end);
	वापस 0;
पूर्ण

पूर्णांक test__dso_data_reखोलो(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	काष्ठा machine machine;
	दीर्घ nr_end, nr = खोलो_files_cnt();
	पूर्णांक fd, fd_extra;

#घोषणा dso_0 (dsos[0])
#घोषणा dso_1 (dsos[1])
#घोषणा dso_2 (dsos[2])

	/* Rest the पूर्णांकernal dso खोलो counter limit. */
	reset_fd_limit();

	स_रखो(&machine, 0, माप(machine));

	/*
	 * Test scenario:
	 * - create 3 dso objects
	 * - set process file descriptor limit to current
	 *   files count + 3
	 * - test that the first dso माला_लो बंदd when we
	 *   reach the files count limit
	 */

	/* Make sure we are able to खोलो 3 fds anyway */
	TEST_ASSERT_VAL("failed to set file limit",
			!set_fd_limit((nr + 3)));

	TEST_ASSERT_VAL("failed to create dsos\n", !dsos__create(3, TEST_खाता_SIZE));

	/* खोलो dso_0 */
	fd = dso__data_fd(dso_0, &machine);
	TEST_ASSERT_VAL("failed to get fd", fd > 0);

	/* खोलो dso_1 */
	fd = dso__data_fd(dso_1, &machine);
	TEST_ASSERT_VAL("failed to get fd", fd > 0);

	/*
	 * खोलो extra file descriptor and we just
	 * reached the files count limit
	 */
	fd_extra = खोलो("/dev/null", O_RDONLY);
	TEST_ASSERT_VAL("failed to open extra fd", fd_extra > 0);

	/* खोलो dso_2 */
	fd = dso__data_fd(dso_2, &machine);
	TEST_ASSERT_VAL("failed to get fd", fd > 0);

	/*
	 * dso_0 should get बंदd, because we reached
	 * the file descriptor limit
	 */
	TEST_ASSERT_VAL("failed to close dso_0", dso_0->data.fd == -1);

	/* खोलो dso_0 */
	fd = dso__data_fd(dso_0, &machine);
	TEST_ASSERT_VAL("failed to get fd", fd > 0);

	/*
	 * dso_1 should get बंदd, because we reached
	 * the file descriptor limit
	 */
	TEST_ASSERT_VAL("failed to close dso_1", dso_1->data.fd == -1);

	/* cleanup everything */
	बंद(fd_extra);
	dsos__delete(3);

	/* Make sure we did not leak any file descriptor. */
	nr_end = खोलो_files_cnt();
	pr_debug("nr start %ld, nr stop %ld\n", nr, nr_end);
	TEST_ASSERT_VAL("failed leaking files", nr == nr_end);
	वापस 0;
पूर्ण
