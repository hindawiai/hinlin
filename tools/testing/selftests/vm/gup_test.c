<शैली गुरु>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश "../../../../mm/gup_test.h"

#घोषणा MB (1UL << 20)
#घोषणा PAGE_SIZE sysconf(_SC_PAGESIZE)

/* Just the flags we need, copied from mm.h: */
#घोषणा FOLL_WRITE	0x01	/* check pte is writable */
#घोषणा FOLL_TOUCH	0x02	/* mark page accessed */

अटल अक्षर *cmd_to_str(अचिन्हित दीर्घ cmd)
अणु
	चयन (cmd) अणु
	हाल GUP_FAST_BENCHMARK:
		वापस "GUP_FAST_BENCHMARK";
	हाल PIN_FAST_BENCHMARK:
		वापस "PIN_FAST_BENCHMARK";
	हाल PIN_LONGTERM_BENCHMARK:
		वापस "PIN_LONGTERM_BENCHMARK";
	हाल GUP_BASIC_TEST:
		वापस "GUP_BASIC_TEST";
	हाल PIN_BASIC_TEST:
		वापस "PIN_BASIC_TEST";
	हाल DUMP_USER_PAGES_TEST:
		वापस "DUMP_USER_PAGES_TEST";
	पूर्ण
	वापस "Unknown command";
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा gup_test gup = अणु 0 पूर्ण;
	अचिन्हित दीर्घ size = 128 * MB;
	पूर्णांक i, fd, filed, opt, nr_pages = 1, thp = -1, repeats = 1, ग_लिखो = 1;
	अचिन्हित दीर्घ cmd = GUP_FAST_BENCHMARK;
	पूर्णांक flags = MAP_PRIVATE, touch = 0;
	अक्षर *file = "/dev/zero";
	अक्षर *p;

	जबतक ((opt = getopt(argc, argv, "m:r:n:F:f:abctTLUuwWSHpz")) != -1) अणु
		चयन (opt) अणु
		हाल 'a':
			cmd = PIN_FAST_BENCHMARK;
			अवरोध;
		हाल 'b':
			cmd = PIN_BASIC_TEST;
			अवरोध;
		हाल 'L':
			cmd = PIN_LONGTERM_BENCHMARK;
			अवरोध;
		हाल 'c':
			cmd = DUMP_USER_PAGES_TEST;
			/*
			 * Dump page 0 (index 1). May be overridden later, by
			 * user's non-option arguments.
			 *
			 * .which_pages is zero-based, so that zero can mean "करो
			 * nothing".
			 */
			gup.which_pages[0] = 1;
			अवरोध;
		हाल 'p':
			/* works only with DUMP_USER_PAGES_TEST */
			gup.test_flags |= GUP_TEST_FLAG_DUMP_PAGES_USE_PIN;
			अवरोध;
		हाल 'F':
			/* म_से_दीर्घ, so you can pass flags in hex क्रमm */
			gup.gup_flags = म_से_दीर्घ(optarg, 0, 0);
			अवरोध;
		हाल 'm':
			size = म_से_प(optarg) * MB;
			अवरोध;
		हाल 'r':
			repeats = म_से_प(optarg);
			अवरोध;
		हाल 'n':
			nr_pages = म_से_प(optarg);
			अवरोध;
		हाल 't':
			thp = 1;
			अवरोध;
		हाल 'T':
			thp = 0;
			अवरोध;
		हाल 'U':
			cmd = GUP_BASIC_TEST;
			अवरोध;
		हाल 'u':
			cmd = GUP_FAST_BENCHMARK;
			अवरोध;
		हाल 'w':
			ग_लिखो = 1;
			अवरोध;
		हाल 'W':
			ग_लिखो = 0;
			अवरोध;
		हाल 'f':
			file = optarg;
			अवरोध;
		हाल 'S':
			flags &= ~MAP_PRIVATE;
			flags |= MAP_SHARED;
			अवरोध;
		हाल 'H':
			flags |= (MAP_HUGETLB | MAP_ANONYMOUS);
			अवरोध;
		हाल 'z':
			/* fault pages in gup, करो not fault in userland */
			touch = 1;
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (optind < argc) अणु
		पूर्णांक extra_arg_count = 0;
		/*
		 * For example:
		 *
		 *   ./gup_test -c 0 1 0x1001
		 *
		 * ...to dump pages 0, 1, and 4097
		 */

		जबतक ((optind < argc) &&
		       (extra_arg_count < GUP_TEST_MAX_PAGES_TO_DUMP)) अणु
			/*
			 * Do the 1-based indexing here, so that the user can
			 * use normal 0-based indexing on the command line.
			 */
			दीर्घ page_index = म_से_दीर्घ(argv[optind], 0, 0) + 1;

			gup.which_pages[extra_arg_count] = page_index;
			extra_arg_count++;
			optind++;
		पूर्ण
	पूर्ण

	filed = खोलो(file, O_RDWR|O_CREAT);
	अगर (filed < 0) अणु
		लिखो_त्रुटि("open");
		निकास(filed);
	पूर्ण

	gup.nr_pages_per_call = nr_pages;
	अगर (ग_लिखो)
		gup.gup_flags |= FOLL_WRITE;

	fd = खोलो("/sys/kernel/debug/gup_test", O_RDWR);
	अगर (fd == -1) अणु
		लिखो_त्रुटि("open");
		निकास(1);
	पूर्ण

	p = mmap(शून्य, size, PROT_READ | PROT_WRITE, flags, filed, 0);
	अगर (p == MAP_FAILED) अणु
		लिखो_त्रुटि("mmap");
		निकास(1);
	पूर्ण
	gup.addr = (अचिन्हित दीर्घ)p;

	अगर (thp == 1)
		madvise(p, size, MADV_HUGEPAGE);
	अन्यथा अगर (thp == 0)
		madvise(p, size, MADV_NOHUGEPAGE);

	/*
	 * FOLL_TOUCH, in gup_test, is used as an either/or हाल: either
	 * fault pages in from the kernel via FOLL_TOUCH, or fault them
	 * in here, from user space. This allows comparison of perक्रमmance
	 * between those two हालs.
	 */
	अगर (touch) अणु
		gup.gup_flags |= FOLL_TOUCH;
	पूर्ण अन्यथा अणु
		क्रम (; (अचिन्हित दीर्घ)p < gup.addr + size; p += PAGE_SIZE)
			p[0] = 0;
	पूर्ण

	/* Only report timing inक्रमmation on the *_BENCHMARK commands: */
	अगर ((cmd == PIN_FAST_BENCHMARK) || (cmd == GUP_FAST_BENCHMARK) ||
	     (cmd == PIN_LONGTERM_BENCHMARK)) अणु
		क्रम (i = 0; i < repeats; i++) अणु
			gup.size = size;
			अगर (ioctl(fd, cmd, &gup))
				लिखो_त्रुटि("ioctl"), निकास(1);

			म_लिखो("%s: Time: get:%lld put:%lld us",
			       cmd_to_str(cmd), gup.get_delta_usec,
			       gup.put_delta_usec);
			अगर (gup.size != size)
				म_लिखो(", truncated (size: %lld)", gup.size);
			म_लिखो("\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		gup.size = size;
		अगर (ioctl(fd, cmd, &gup)) अणु
			लिखो_त्रुटि("ioctl");
			निकास(1);
		पूर्ण

		म_लिखो("%s: done\n", cmd_to_str(cmd));
		अगर (gup.size != size)
			म_लिखो("Truncated (size: %lld)\n", gup.size);
	पूर्ण

	वापस 0;
पूर्ण
