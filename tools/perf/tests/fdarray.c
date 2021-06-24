<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <api/fd/array.h>
#समावेश <poll.h>
#समावेश "util/debug.h"
#समावेश "tests/tests.h"

अटल व्योम fdarray__init_revents(काष्ठा fdarray *fda, लघु revents)
अणु
	पूर्णांक fd;

	fda->nr = fda->nr_alloc;

	क्रम (fd = 0; fd < fda->nr; ++fd) अणु
		fda->entries[fd].fd	 = fda->nr - fd;
		fda->entries[fd].events  = revents;
		fda->entries[fd].revents = revents;
	पूर्ण
पूर्ण

अटल पूर्णांक fdarray__ख_लिखो_prefix(काष्ठा fdarray *fda, स्थिर अक्षर *prefix, खाता *fp)
अणु
	पूर्णांक prपूर्णांकed = 0;

	अगर (verbose <= 0)
		वापस 0;

	prपूर्णांकed += ख_लिखो(fp, "\n%s: ", prefix);
	वापस prपूर्णांकed + fdarray__ख_लिखो(fda, fp);
पूर्ण

पूर्णांक test__fdarray__filter(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक nr_fds, err = TEST_FAIL;
	काष्ठा fdarray *fda = fdarray__new(5, 5);

	अगर (fda == शून्य) अणु
		pr_debug("\nfdarray__new() failed!");
		जाओ out;
	पूर्ण

	fdarray__init_revents(fda, POLLIN);
	nr_fds = fdarray__filter(fda, POLLHUP, शून्य, शून्य);
	अगर (nr_fds != fda->nr_alloc) अणु
		pr_debug("\nfdarray__filter()=%d != %d shouldn't have filtered anything",
			 nr_fds, fda->nr_alloc);
		जाओ out_delete;
	पूर्ण

	fdarray__init_revents(fda, POLLHUP);
	nr_fds = fdarray__filter(fda, POLLHUP, शून्य, शून्य);
	अगर (nr_fds != 0) अणु
		pr_debug("\nfdarray__filter()=%d != %d, should have filtered all fds",
			 nr_fds, fda->nr_alloc);
		जाओ out_delete;
	पूर्ण

	fdarray__init_revents(fda, POLLHUP);
	fda->entries[2].revents = POLLIN;

	pr_debug("\nfiltering all but fda->entries[2]:");
	fdarray__ख_लिखो_prefix(fda, "before", मानक_त्रुटि);
	nr_fds = fdarray__filter(fda, POLLHUP, शून्य, शून्य);
	fdarray__ख_लिखो_prefix(fda, " after", मानक_त्रुटि);
	अगर (nr_fds != 1) अणु
		pr_debug("\nfdarray__filter()=%d != 1, should have left just one event", nr_fds);
		जाओ out_delete;
	पूर्ण

	fdarray__init_revents(fda, POLLHUP);
	fda->entries[0].revents = POLLIN;
	fda->entries[3].revents = POLLIN;

	pr_debug("\nfiltering all but (fda->entries[0], fda->entries[3]):");
	fdarray__ख_लिखो_prefix(fda, "before", मानक_त्रुटि);
	nr_fds = fdarray__filter(fda, POLLHUP, शून्य, शून्य);
	fdarray__ख_लिखो_prefix(fda, " after", मानक_त्रुटि);
	अगर (nr_fds != 2) अणु
		pr_debug("\nfdarray__filter()=%d != 2, should have left just two events",
			 nr_fds);
		जाओ out_delete;
	पूर्ण

	pr_debug("\n");

	err = 0;
out_delete:
	fdarray__delete(fda);
out:
	वापस err;
पूर्ण

पूर्णांक test__fdarray__add(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक err = TEST_FAIL;
	काष्ठा fdarray *fda = fdarray__new(2, 2);

	अगर (fda == शून्य) अणु
		pr_debug("\nfdarray__new() failed!");
		जाओ out;
	पूर्ण

#घोषणा FDA_CHECK(_idx, _fd, _revents)					   \
	अगर (fda->entries[_idx].fd != _fd) अणु				   \
		pr_debug("\n%d: fda->entries[%d](%d) != %d!",		   \
			 __LINE__, _idx, fda->entries[1].fd, _fd);	   \
		जाओ out_delete;					   \
	पूर्ण								   \
	अगर (fda->entries[_idx].events != (_revents)) अणु			   \
		pr_debug("\n%d: fda->entries[%d].revents(%d) != %d!",	   \
			 __LINE__, _idx, fda->entries[_idx].fd, _revents); \
		जाओ out_delete;					   \
	पूर्ण

#घोषणा FDA_ADD(_idx, _fd, _revents, _nr)				   \
	अगर (fdarray__add(fda, _fd, _revents, fdarray_flag__शेष) < 0) अणु \
		pr_debug("\n%d: fdarray__add(fda, %d, %d) failed!",	   \
			 __LINE__,_fd, _revents);			   \
		जाओ out_delete;					   \
	पूर्ण								   \
	अगर (fda->nr != _nr) अणु						   \
		pr_debug("\n%d: fdarray__add(fda, %d, %d)=%d != %d",	   \
			 __LINE__,_fd, _revents, fda->nr, _nr);		   \
		जाओ out_delete;					   \
	पूर्ण								   \
	FDA_CHECK(_idx, _fd, _revents)

	FDA_ADD(0, 1, POLLIN, 1);
	FDA_ADD(1, 2, POLLERR, 2);

	fdarray__ख_लिखो_prefix(fda, "before growing array", मानक_त्रुटि);

	FDA_ADD(2, 35, POLLHUP, 3);

	अगर (fda->entries == शून्य) अणु
		pr_debug("\nfdarray__add(fda, 35, POLLHUP) should have allocated fda->pollfd!");
		जाओ out_delete;
	पूर्ण

	fdarray__ख_लिखो_prefix(fda, "after 3rd add", मानक_त्रुटि);

	FDA_ADD(3, 88, POLLIN | POLLOUT, 4);

	fdarray__ख_लिखो_prefix(fda, "after 4th add", मानक_त्रुटि);

	FDA_CHECK(0, 1, POLLIN);
	FDA_CHECK(1, 2, POLLERR);
	FDA_CHECK(2, 35, POLLHUP);
	FDA_CHECK(3, 88, POLLIN | POLLOUT);

#अघोषित FDA_ADD
#अघोषित FDA_CHECK

	pr_debug("\n");

	err = 0;
out_delete:
	fdarray__delete(fda);
out:
	वापस err;
पूर्ण
