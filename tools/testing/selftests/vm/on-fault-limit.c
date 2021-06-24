<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/mman.h>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>

#अगर_अघोषित MCL_ONFAULT
#घोषणा MCL_ONFAULT (MCL_FUTURE << 1)
#पूर्ण_अगर

अटल पूर्णांक test_limit(व्योम)
अणु
	पूर्णांक ret = 1;
	काष्ठा rlimit lims;
	व्योम *map;

	अगर (getrlimit(RLIMIT_MEMLOCK, &lims)) अणु
		लिखो_त्रुटि("getrlimit");
		वापस ret;
	पूर्ण

	अगर (mlockall(MCL_ONFAULT | MCL_FUTURE)) अणु
		लिखो_त्रुटि("mlockall");
		वापस ret;
	पूर्ण

	map = mmap(शून्य, 2 * lims.rlim_max, PROT_READ | PROT_WRITE,
		   MAP_PRIVATE | MAP_ANONYMOUS | MAP_POPULATE, -1, 0);
	अगर (map != MAP_FAILED)
		म_लिखो("mmap should have failed, but didn't\n");
	अन्यथा अणु
		ret = 0;
		munmap(map, 2 * lims.rlim_max);
	पूर्ण

	munlockall();
	वापस ret;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक ret = 0;

	ret += test_limit();
	वापस ret;
पूर्ण
