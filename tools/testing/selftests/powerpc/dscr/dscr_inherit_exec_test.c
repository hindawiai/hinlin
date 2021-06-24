<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * POWER Data Stream Control Register (DSCR) विभाजन exec test
 *
 * This testहाल modअगरies the DSCR using mtspr, विभाजनs & execs and
 * verअगरies that the child is using the changed DSCR using mfspr.
 *
 * When using the privilege state SPR, the inकाष्ठाions such as
 * mfspr or mtspr are privileged and the kernel emulates them
 * क्रम us. Inकाष्ठाions using problem state SPR can be executed
 * directly without any emulation अगर the HW supports them. Else
 * they also get emulated by the kernel.
 *
 * Copyright 2012, Anton Blanअक्षरd, IBM Corporation.
 * Copyright 2015, Anshuman Khandual, IBM Corporation.
 */
#समावेश "dscr.h"

अटल अक्षर *prog;

अटल व्योम करो_exec(अचिन्हित दीर्घ parent_dscr)
अणु
	अचिन्हित दीर्घ cur_dscr, cur_dscr_usr;

	cur_dscr = get_dscr();
	cur_dscr_usr = get_dscr_usr();

	अगर (cur_dscr != parent_dscr) अणु
		ख_लिखो(मानक_त्रुटि, "Parent DSCR %ld was not inherited "
				"over exec (kernel value)\n", parent_dscr);
		निकास(1);
	पूर्ण

	अगर (cur_dscr_usr != parent_dscr) अणु
		ख_लिखो(मानक_त्रुटि, "Parent DSCR %ld was not inherited "
				"over exec (user value)\n", parent_dscr);
		निकास(1);
	पूर्ण
	निकास(0);
पूर्ण

पूर्णांक dscr_inherit_exec(व्योम)
अणु
	अचिन्हित दीर्घ i, dscr = 0;
	pid_t pid;

	SKIP_IF(!have_hwcap2(PPC_FEATURE2_DSCR));

	क्रम (i = 0; i < COUNT; i++) अणु
		dscr++;
		अगर (dscr > DSCR_MAX)
			dscr = 0;

		अगर (dscr == get_शेष_dscr())
			जारी;

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
			अक्षर dscr_str[16];

			प्र_लिखो(dscr_str, "%ld", dscr);
			execlp(prog, prog, "exec", dscr_str, शून्य);
			निकास(1);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अगर (argc == 3 && !म_भेद(argv[1], "exec")) अणु
		अचिन्हित दीर्घ parent_dscr;

		parent_dscr = म_से_प(argv[2]);
		करो_exec(parent_dscr);
	पूर्ण अन्यथा अगर (argc != 1) अणु
		ख_लिखो(मानक_त्रुटि, "Usage: %s\n", argv[0]);
		निकास(1);
	पूर्ण

	prog = argv[0];
	वापस test_harness(dscr_inherit_exec, "dscr_inherit_exec_test");
पूर्ण
