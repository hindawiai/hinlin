<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This program reserves and uses hugetlb memory, supporting a bunch of
 * scenarios needed by the अक्षरged_reserved_hugetlb.sh test.
 */

#समावेश <err.h>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <sys/types.h>
#समावेश <sys/shm.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>

/* Global definitions. */
क्रमागत method अणु
	HUGETLBFS,
	MMAP_MAP_HUGETLB,
	SHM,
	MAX_METHOD
पूर्ण;


/* Global variables. */
अटल स्थिर अक्षर *self;
अटल अक्षर *shmaddr;
अटल पूर्णांक shmid;

/*
 * Show usage and निकास.
 */
अटल व्योम निकास_usage(व्योम)
अणु
	म_लिखो("Usage: %s -p <path to hugetlbfs file> -s <size to map> "
	       "[-m <0=hugetlbfs | 1=mmap(MAP_HUGETLB)>] [-l] [-r] "
	       "[-o] [-w] [-n]\n",
	       self);
	निकास(निकास_त्रुटि);
पूर्ण

व्योम sig_handler(पूर्णांक signo)
अणु
	म_लिखो("Received %d.\n", signo);
	अगर (signo == संक_विघ्न) अणु
		म_लिखो("Deleting the memory\n");
		अगर (shmdt((स्थिर व्योम *)shmaddr) != 0) अणु
			लिखो_त्रुटि("Detach failure");
			shmctl(shmid, IPC_RMID, शून्य);
			निकास(4);
		पूर्ण

		shmctl(shmid, IPC_RMID, शून्य);
		म_लिखो("Done deleting the memory\n");
	पूर्ण
	निकास(2);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक fd = 0;
	पूर्णांक key = 0;
	पूर्णांक *ptr = शून्य;
	पूर्णांक c = 0;
	पूर्णांक size = 0;
	अक्षर path[256] = "";
	क्रमागत method method = MAX_METHOD;
	पूर्णांक want_sleep = 0, निजी = 0;
	पूर्णांक populate = 0;
	पूर्णांक ग_लिखो = 0;
	पूर्णांक reserve = 1;

	अगर (संकेत(संक_विघ्न, sig_handler) == संक_त्रुटि)
		err(1, "\ncan't catch SIGINT\n");

	/* Parse command-line arguments. */
	रखो_भबफ(मानक_निकास, शून्य, _IONBF, 0);
	self = argv[0];

	जबतक ((c = getopt(argc, argv, "s:p:m:owlrn")) != -1) अणु
		चयन (c) अणु
		हाल 's':
			size = म_से_प(optarg);
			अवरोध;
		हाल 'p':
			म_नकलन(path, optarg, माप(path));
			अवरोध;
		हाल 'm':
			अगर (म_से_प(optarg) >= MAX_METHOD) अणु
				त्रुटि_सं = EINVAL;
				लिखो_त्रुटि("Invalid -m.");
				निकास_usage();
			पूर्ण
			method = म_से_प(optarg);
			अवरोध;
		हाल 'o':
			populate = 1;
			अवरोध;
		हाल 'w':
			ग_लिखो = 1;
			अवरोध;
		हाल 'l':
			want_sleep = 1;
			अवरोध;
		हाल 'r':
		    निजी
			= 1;
			अवरोध;
		हाल 'n':
			reserve = 0;
			अवरोध;
		शेष:
			त्रुटि_सं = EINVAL;
			लिखो_त्रुटि("Invalid arg");
			निकास_usage();
		पूर्ण
	पूर्ण

	अगर (म_भेदन(path, "", माप(path)) != 0) अणु
		म_लिखो("Writing to this path: %s\n", path);
	पूर्ण अन्यथा अणु
		त्रुटि_सं = EINVAL;
		लिखो_त्रुटि("path not found");
		निकास_usage();
	पूर्ण

	अगर (size != 0) अणु
		म_लिखो("Writing this size: %d\n", size);
	पूर्ण अन्यथा अणु
		त्रुटि_सं = EINVAL;
		लिखो_त्रुटि("size not found");
		निकास_usage();
	पूर्ण

	अगर (!populate)
		म_लिखो("Not populating.\n");
	अन्यथा
		म_लिखो("Populating.\n");

	अगर (!ग_लिखो)
		म_लिखो("Not writing to memory.\n");

	अगर (method == MAX_METHOD) अणु
		त्रुटि_सं = EINVAL;
		लिखो_त्रुटि("-m Invalid");
		निकास_usage();
	पूर्ण अन्यथा
		म_लिखो("Using method=%d\n", method);

	अगर (!निजी)
		म_लिखो("Shared mapping.\n");
	अन्यथा
		म_लिखो("Private mapping.\n");

	अगर (!reserve)
		म_लिखो("NO_RESERVE mapping.\n");
	अन्यथा
		म_लिखो("RESERVE mapping.\n");

	चयन (method) अणु
	हाल HUGETLBFS:
		म_लिखो("Allocating using HUGETLBFS.\n");
		fd = खोलो(path, O_CREAT | O_RDWR, 0777);
		अगर (fd == -1)
			err(1, "Failed to open file.");

		ptr = mmap(शून्य, size, PROT_READ | PROT_WRITE,
			   (निजी ? MAP_PRIVATE : MAP_SHARED) |
				   (populate ? MAP_POPULATE : 0) |
				   (reserve ? 0 : MAP_NORESERVE),
			   fd, 0);

		अगर (ptr == MAP_FAILED) अणु
			बंद(fd);
			err(1, "Error mapping the file");
		पूर्ण
		अवरोध;
	हाल MMAP_MAP_HUGETLB:
		म_लिखो("Allocating using MAP_HUGETLB.\n");
		ptr = mmap(शून्य, size, PROT_READ | PROT_WRITE,
			   (निजी ? (MAP_PRIVATE | MAP_ANONYMOUS) :
				      MAP_SHARED) |
				   MAP_HUGETLB | (populate ? MAP_POPULATE : 0) |
				   (reserve ? 0 : MAP_NORESERVE),
			   -1, 0);

		अगर (ptr == MAP_FAILED)
			err(1, "mmap");

		म_लिखो("Returned address is %p\n", ptr);
		अवरोध;
	हाल SHM:
		म_लिखो("Allocating using SHM.\n");
		shmid = shmget(key, size,
			       SHM_HUGETLB | IPC_CREAT | SHM_R | SHM_W);
		अगर (shmid < 0) अणु
			shmid = shmget(++key, size,
				       SHM_HUGETLB | IPC_CREAT | SHM_R | SHM_W);
			अगर (shmid < 0)
				err(1, "shmget");
		पूर्ण
		म_लिखो("shmid: 0x%x, shmget key:%d\n", shmid, key);

		ptr = shmat(shmid, शून्य, 0);
		अगर (ptr == (पूर्णांक *)-1) अणु
			लिखो_त्रुटि("Shared memory attach failure");
			shmctl(shmid, IPC_RMID, शून्य);
			निकास(2);
		पूर्ण
		म_लिखो("shmaddr: %p\n", ptr);

		अवरोध;
	शेष:
		त्रुटि_सं = EINVAL;
		err(1, "Invalid method.");
	पूर्ण

	अगर (ग_लिखो) अणु
		म_लिखो("Writing to memory.\n");
		स_रखो(ptr, 1, size);
	पूर्ण

	अगर (want_sleep) अणु
		/* Signal to caller that we're करोne. */
		म_लिखो("DONE\n");

		/* Hold memory until बाह्यal समाप्त संकेत is delivered. */
		जबतक (1)
			sleep(100);
	पूर्ण

	अगर (method == HUGETLBFS)
		बंद(fd);

	वापस 0;
पूर्ण
