<शैली गुरु>
#समावेश <sys/resource.h>
#समावेश <मानकपन.स>

अटल  __attribute__((स्थिरructor)) व्योम bpf_rlimit_ctor(व्योम)
अणु
	काष्ठा rlimit rlim_old, rlim_new = अणु
		.rlim_cur	= RLIM_अनन्त,
		.rlim_max	= RLIM_अनन्त,
	पूर्ण;

	getrlimit(RLIMIT_MEMLOCK, &rlim_old);
	/* For the sake of running the test हालs, we temporarily
	 * set rlimit to infinity in order क्रम kernel to focus on
	 * errors from actual test हालs and not getting noise
	 * from hitting memlock limits. The limit is on per-process
	 * basis and not a global one, hence deकाष्ठाor not really
	 * needed here.
	 */
	अगर (setrlimit(RLIMIT_MEMLOCK, &rlim_new) < 0) अणु
		लिखो_त्रुटि("Unable to lift memlock rlimit");
		/* Trying out lower limit, but expect potential test
		 * हाल failures from this!
		 */
		rlim_new.rlim_cur = rlim_old.rlim_cur + (1UL << 20);
		rlim_new.rlim_max = rlim_old.rlim_max + (1UL << 20);
		setrlimit(RLIMIT_MEMLOCK, &rlim_new);
	पूर्ण
पूर्ण
