<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * POWER Data Stream Control Register (DSCR) विभाजन test
 *
 * This testहाल modअगरies the DSCR using mtspr, विभाजनs and then
 * verअगरies that the child process has the correct changed DSCR
 * value using mfspr.
 *
 * When using the privilege state SPR, the inकाष्ठाions such as
 * mfspr or mtspr are priviledged and the kernel emulates them
 * क्रम us. Inकाष्ठाions using problem state SPR can be exuecuted
 * directly without any emulation अगर the HW supports them. Else
 * they also get emulated by the kernel.
 *
 * Copyright 2012, Anton Blanअक्षरd, IBM Corporation.
 * Copyright 2015, Anshuman Khandual, IBM Corporation.
 */
#समावेश "dscr.h"

पूर्णांक dscr_inherit(व्योम)
अणु
	अचिन्हित दीर्घ i, dscr = 0;
	pid_t pid;

	SKIP_IF(!have_hwcap2(PPC_FEATURE2_DSCR));

	बेक्रम(getpid());
	set_dscr(dscr);

	क्रम (i = 0; i < COUNT; i++) अणु
		अचिन्हित दीर्घ cur_dscr, cur_dscr_usr;

		dscr++;
		अगर (dscr > DSCR_MAX)
			dscr = 0;

		अगर (i % 2 == 0)
			set_dscr_usr(dscr);
		अन्यथा
			set_dscr(dscr);

		pid = विभाजन();
		अगर (pid == -1) अणु
			लिखो_त्रुटि("fork() failed");
			निकास(1);
		पूर्ण अन्यथा अगर (pid) अणु
			पूर्णांक status;

			अगर (रुकोpid(pid, &status, 0) == -1) अणु
				लिखो_त्रुटि("waitpid() failed");
				निकास(1);
			पूर्ण

			अगर (!WIFEXITED(status)) अणु
				ख_लिखो(मानक_त्रुटि, "Child didn't exit cleanly\n");
				निकास(1);
			पूर्ण

			अगर (WEXITSTATUS(status) != 0) अणु
				ख_लिखो(मानक_त्रुटि, "Child didn't exit cleanly\n");
				वापस 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			cur_dscr = get_dscr();
			अगर (cur_dscr != dscr) अणु
				ख_लिखो(मानक_त्रुटि, "Kernel DSCR should be %ld "
					"but is %ld\n", dscr, cur_dscr);
				निकास(1);
			पूर्ण

			cur_dscr_usr = get_dscr_usr();
			अगर (cur_dscr_usr != dscr) अणु
				ख_लिखो(मानक_त्रुटि, "User DSCR should be %ld "
					"but is %ld\n", dscr, cur_dscr_usr);
				निकास(1);
			पूर्ण
			निकास(0);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(dscr_inherit, "dscr_inherit_test");
पूर्ण
