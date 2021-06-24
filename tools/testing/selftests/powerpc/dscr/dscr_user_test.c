<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * POWER Data Stream Control Register (DSCR) SPR test
 *
 * This test modअगरies the DSCR value through both the SPR number
 * based mtspr inकाष्ठाion and then makes sure that the same is
 * reflected through mfspr inकाष्ठाion using either of the SPR
 * numbers.
 *
 * When using the privilege state SPR, the inकाष्ठाions such as
 * mfspr or mtspr are priviledged and the kernel emulates them
 * क्रम us. Inकाष्ठाions using problem state SPR can be exuecuted
 * directly without any emulation अगर the HW supports them. Else
 * they also get emulated by the kernel.
 *
 * Copyright 2013, Anton Blanअक्षरd, IBM Corporation.
 * Copyright 2015, Anshuman Khandual, IBM Corporation.
 */
#समावेश "dscr.h"

अटल पूर्णांक check_dscr(अक्षर *str)
अणु
	अचिन्हित दीर्घ cur_dscr, cur_dscr_usr;

	cur_dscr = get_dscr();
	cur_dscr_usr = get_dscr_usr();
	अगर (cur_dscr != cur_dscr_usr) अणु
		म_लिखो("%s set, kernel get %lx != user get %lx\n",
					str, cur_dscr, cur_dscr_usr);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक dscr_user(व्योम)
अणु
	पूर्णांक i;

	SKIP_IF(!have_hwcap2(PPC_FEATURE2_DSCR));

	check_dscr("");

	क्रम (i = 0; i < COUNT; i++) अणु
		set_dscr(i);
		अगर (check_dscr("kernel"))
			वापस 1;
	पूर्ण

	क्रम (i = 0; i < COUNT; i++) अणु
		set_dscr_usr(i);
		अगर (check_dscr("user"))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(dscr_user, "dscr_user_test");
पूर्ण
