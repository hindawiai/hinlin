<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * POWER Data Stream Control Register (DSCR) explicit test
 *
 * This test modअगरies the DSCR value using mtspr inकाष्ठाion and
 * verअगरies the change with mfspr inकाष्ठाion. It uses both the
 * privilege state SPR and the problem state SPR क्रम this purpose.
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

पूर्णांक dscr_explicit(व्योम)
अणु
	अचिन्हित दीर्घ i, dscr = 0;

	SKIP_IF(!have_hwcap2(PPC_FEATURE2_DSCR));

	बेक्रम(getpid());
	set_dscr(dscr);

	क्रम (i = 0; i < COUNT; i++) अणु
		अचिन्हित दीर्घ cur_dscr, cur_dscr_usr;
		द्विगुन ret = unअगरorm_deviate(अक्रम());

		अगर (ret < 0.001) अणु
			dscr++;
			अगर (dscr > DSCR_MAX)
				dscr = 0;

			set_dscr(dscr);
		पूर्ण

		cur_dscr = get_dscr();
		अगर (cur_dscr != dscr) अणु
			ख_लिखो(मानक_त्रुटि, "Kernel DSCR should be %ld but "
					"is %ld\n", dscr, cur_dscr);
			वापस 1;
		पूर्ण

		ret = unअगरorm_deviate(अक्रम());
		अगर (ret < 0.001) अणु
			dscr++;
			अगर (dscr > DSCR_MAX)
				dscr = 0;

			set_dscr_usr(dscr);
		पूर्ण

		cur_dscr_usr = get_dscr_usr();
		अगर (cur_dscr_usr != dscr) अणु
			ख_लिखो(मानक_त्रुटि, "User DSCR should be %ld but "
					"is %ld\n", dscr, cur_dscr_usr);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(dscr_explicit, "dscr_explicit_test");
पूर्ण
