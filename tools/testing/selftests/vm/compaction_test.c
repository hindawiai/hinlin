<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *
 * A test क्रम the patch "Allow compaction of unevictable pages".
 * With this patch we should be able to allocate at least 1/4
 * of RAM in huge pages. Without the patch much less is
 * allocated.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/mman.h>
#समावेश <sys/resource.h>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <माला.स>

#समावेश "../kselftest.h"

#घोषणा MAP_SIZE_MB	100
#घोषणा MAP_SIZE	(MAP_SIZE_MB * 1024 * 1024)

काष्ठा map_list अणु
	व्योम *map;
	काष्ठा map_list *next;
पूर्ण;

पूर्णांक पढ़ो_memory_info(अचिन्हित दीर्घ *memमुक्त, अचिन्हित दीर्घ *hugepagesize)
अणु
	अक्षर  buffer[256] = अणु0पूर्ण;
	अक्षर *cmd = "cat /proc/meminfo | grep -i memfree | grep -o '[0-9]*'";
	खाता *cmdfile = pखोलो(cmd, "r");

	अगर (!(ख_माला_लो(buffer, माप(buffer), cmdfile))) अणु
		लिखो_त्रुटि("Failed to read meminfo\n");
		वापस -1;
	पूर्ण

	pबंद(cmdfile);

	*memमुक्त = म_से_दl(buffer);
	cmd = "cat /proc/meminfo | grep -i hugepagesize | grep -o '[0-9]*'";
	cmdfile = pखोलो(cmd, "r");

	अगर (!(ख_माला_लो(buffer, माप(buffer), cmdfile))) अणु
		लिखो_त्रुटि("Failed to read meminfo\n");
		वापस -1;
	पूर्ण

	pबंद(cmdfile);
	*hugepagesize = म_से_दl(buffer);

	वापस 0;
पूर्ण

पूर्णांक prereq(व्योम)
अणु
	अक्षर allowed;
	पूर्णांक fd;

	fd = खोलो("/proc/sys/vm/compact_unevictable_allowed",
		  O_RDONLY | O_NONBLOCK);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("Failed to open\n"
		       "/proc/sys/vm/compact_unevictable_allowed\n");
		वापस -1;
	पूर्ण

	अगर (पढ़ो(fd, &allowed, माप(अक्षर)) != माप(अक्षर)) अणु
		लिखो_त्रुटि("Failed to read from\n"
		       "/proc/sys/vm/compact_unevictable_allowed\n");
		बंद(fd);
		वापस -1;
	पूर्ण

	बंद(fd);
	अगर (allowed == '1')
		वापस 0;

	वापस -1;
पूर्ण

पूर्णांक check_compaction(अचिन्हित दीर्घ mem_मुक्त, अचिन्हित पूर्णांक hugepage_size)
अणु
	पूर्णांक fd;
	पूर्णांक compaction_index = 0;
	अक्षर initial_nr_hugepages[10] = अणु0पूर्ण;
	अक्षर nr_hugepages[10] = अणु0पूर्ण;

	/* We want to test with 80% of available memory. Else, OOM समाप्तer comes
	   in to play */
	mem_मुक्त = mem_मुक्त * 0.8;

	fd = खोलो("/proc/sys/vm/nr_hugepages", O_RDWR | O_NONBLOCK);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("Failed to open /proc/sys/vm/nr_hugepages");
		वापस -1;
	पूर्ण

	अगर (पढ़ो(fd, initial_nr_hugepages, माप(initial_nr_hugepages)) <= 0) अणु
		लिखो_त्रुटि("Failed to read from /proc/sys/vm/nr_hugepages");
		जाओ बंद_fd;
	पूर्ण

	/* Start with the initial condition of 0 huge pages*/
	अगर (ग_लिखो(fd, "0", माप(अक्षर)) != माप(अक्षर)) अणु
		लिखो_त्रुटि("Failed to write 0 to /proc/sys/vm/nr_hugepages\n");
		जाओ बंद_fd;
	पूर्ण

	lseek(fd, 0, शुरू_से);

	/* Request a large number of huge pages. The Kernel will allocate
	   as much as it can */
	अगर (ग_लिखो(fd, "100000", (6*माप(अक्षर))) != (6*माप(अक्षर))) अणु
		लिखो_त्रुटि("Failed to write 100000 to /proc/sys/vm/nr_hugepages\n");
		जाओ बंद_fd;
	पूर्ण

	lseek(fd, 0, शुरू_से);

	अगर (पढ़ो(fd, nr_hugepages, माप(nr_hugepages)) <= 0) अणु
		लिखो_त्रुटि("Failed to re-read from /proc/sys/vm/nr_hugepages\n");
		जाओ बंद_fd;
	पूर्ण

	/* We should have been able to request at least 1/3 rd of the memory in
	   huge pages */
	compaction_index = mem_मुक्त/(म_से_प(nr_hugepages) * hugepage_size);

	अगर (compaction_index > 3) अणु
		म_लिखो("No of huge pages allocated = %d\n",
		       (म_से_प(nr_hugepages)));
		ख_लिखो(मानक_त्रुटि, "ERROR: Less that 1/%d of memory is available\n"
			"as huge pages\n", compaction_index);
		जाओ बंद_fd;
	पूर्ण

	म_लिखो("No of huge pages allocated = %d\n",
	       (म_से_प(nr_hugepages)));

	lseek(fd, 0, शुरू_से);

	अगर (ग_लिखो(fd, initial_nr_hugepages, म_माप(initial_nr_hugepages))
	    != म_माप(initial_nr_hugepages)) अणु
		लिखो_त्रुटि("Failed to write value to /proc/sys/vm/nr_hugepages\n");
		जाओ बंद_fd;
	पूर्ण

	बंद(fd);
	वापस 0;

 बंद_fd:
	बंद(fd);
	म_लिखो("Not OK. Compaction test failed.");
	वापस -1;
पूर्ण


पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा rlimit lim;
	काष्ठा map_list *list, *entry;
	माप_प्रकार page_size, i;
	व्योम *map = शून्य;
	अचिन्हित दीर्घ mem_मुक्त = 0;
	अचिन्हित दीर्घ hugepage_size = 0;
	दीर्घ mem_fragmentable_MB = 0;

	अगर (prereq() != 0) अणु
		म_लिखो("Either the sysctl compact_unevictable_allowed is not\n"
		       "set to 1 or couldn't read the proc file.\n"
		       "Skipping the test\n");
		वापस KSFT_SKIP;
	पूर्ण

	lim.rlim_cur = RLIM_अनन्त;
	lim.rlim_max = RLIM_अनन्त;
	अगर (setrlimit(RLIMIT_MEMLOCK, &lim)) अणु
		लिखो_त्रुटि("Failed to set rlimit:\n");
		वापस -1;
	पूर्ण

	page_size = getpagesize();

	list = शून्य;

	अगर (पढ़ो_memory_info(&mem_मुक्त, &hugepage_size) != 0) अणु
		म_लिखो("ERROR: Cannot read meminfo\n");
		वापस -1;
	पूर्ण

	mem_fragmentable_MB = mem_मुक्त * 0.8 / 1024;

	जबतक (mem_fragmentable_MB > 0) अणु
		map = mmap(शून्य, MAP_SIZE, PROT_READ | PROT_WRITE,
			   MAP_ANONYMOUS | MAP_PRIVATE | MAP_LOCKED, -1, 0);
		अगर (map == MAP_FAILED)
			अवरोध;

		entry = दो_स्मृति(माप(काष्ठा map_list));
		अगर (!entry) अणु
			munmap(map, MAP_SIZE);
			अवरोध;
		पूर्ण
		entry->map = map;
		entry->next = list;
		list = entry;

		/* Write something (in this हाल the address of the map) to
		 * ensure that KSM can't merge the mapped pages
		 */
		क्रम (i = 0; i < MAP_SIZE; i += page_size)
			*(अचिन्हित दीर्घ *)(map + i) = (अचिन्हित दीर्घ)map + i;

		mem_fragmentable_MB -= MAP_SIZE_MB;
	पूर्ण

	क्रम (entry = list; entry != शून्य; entry = entry->next) अणु
		munmap(entry->map, MAP_SIZE);
		अगर (!entry->next)
			अवरोध;
		entry = entry->next;
	पूर्ण

	अगर (check_compaction(mem_मुक्त, hugepage_size) == 0)
		वापस 0;

	वापस -1;
पूर्ण
