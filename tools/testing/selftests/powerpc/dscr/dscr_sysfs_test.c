<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * POWER Data Stream Control Register (DSCR) sysfs पूर्णांकerface test
 *
 * This test updates to प्रणाली wide DSCR शेष through the sysfs पूर्णांकerface
 * and then verअगरies that all the CPU specअगरic DSCR शेषs are updated as
 * well verअगरied from their sysfs पूर्णांकerfaces.
 *
 * Copyright 2015, Anshuman Khandual, IBM Corporation.
 */
#समावेश "dscr.h"

अटल पूर्णांक check_cpu_dscr_शेष(अक्षर *file, अचिन्हित दीर्घ val)
अणु
	अक्षर buf[10];
	पूर्णांक fd, rc;

	fd = खोलो(file, O_RDWR);
	अगर (fd == -1) अणु
		लिखो_त्रुटि("open() failed");
		वापस 1;
	पूर्ण

	rc = पढ़ो(fd, buf, माप(buf));
	अगर (rc == -1) अणु
		लिखो_त्रुटि("read() failed");
		वापस 1;
	पूर्ण
	बंद(fd);

	buf[rc] = '\0';
	अगर (म_से_दीर्घ(buf, शून्य, 16) != val) अणु
		म_लिखो("DSCR match failed: %ld (system) %ld (cpu)\n",
					val, म_से_दीर्घ(buf, शून्य, 16));
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_all_cpu_dscr_शेषs(अचिन्हित दीर्घ val)
अणु
	सूची *sysfs;
	काष्ठा dirent *dp;
	अक्षर file[LEN_MAX];

	sysfs = सूची_खोलो(CPU_PATH);
	अगर (!sysfs) अणु
		लिखो_त्रुटि("opendir() failed");
		वापस 1;
	पूर्ण

	जबतक ((dp = सूची_पढ़ो(sysfs))) अणु
		पूर्णांक len;

		अगर (!(dp->d_type & DT_सूची))
			जारी;
		अगर (!म_भेद(dp->d_name, "cpuidle"))
			जारी;
		अगर (!म_माला(dp->d_name, "cpu"))
			जारी;

		len = snम_लिखो(file, LEN_MAX, "%s%s/dscr", CPU_PATH, dp->d_name);
		अगर (len >= LEN_MAX)
			जारी;
		अगर (access(file, F_OK))
			जारी;

		अगर (check_cpu_dscr_शेष(file, val))
			वापस 1;
	पूर्ण
	बंद_सूची(sysfs);
	वापस 0;
पूर्ण

पूर्णांक dscr_sysfs(व्योम)
अणु
	अचिन्हित दीर्घ orig_dscr_शेष;
	पूर्णांक i, j;

	SKIP_IF(!have_hwcap2(PPC_FEATURE2_DSCR));

	orig_dscr_शेष = get_शेष_dscr();
	क्रम (i = 0; i < COUNT; i++) अणु
		क्रम (j = 0; j < DSCR_MAX; j++) अणु
			set_शेष_dscr(j);
			अगर (check_all_cpu_dscr_शेषs(j))
				जाओ fail;
		पूर्ण
	पूर्ण
	set_शेष_dscr(orig_dscr_शेष);
	वापस 0;
fail:
	set_शेष_dscr(orig_dscr_शेष);
	वापस 1;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(dscr_sysfs, "dscr_sysfs_test");
पूर्ण
