<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015, Michael Neuling, IBM Corp.
 *
 * Original: Michael Neuling 3/4/2014
 * Modअगरied: Rashmica Gupta 8/12/2015
 *
 * Check अगर any of the Transaction Memory SPRs get corrupted.
 * - TFIAR  - stores address of location of transaction failure
 * - TFHAR  - stores address of software failure handler (अगर transaction
 *   fails)
 * - TEXASR - lots of info about the transacion(s)
 *
 * (1) create more thपढ़ोs than cpus
 * (2) in each thपढ़ो:
 * 	(a) set TFIAR and TFHAR a unique value
 * 	(b) loop क्रम aजबतक, continually checking to see अगर
 * 	either रेजिस्टर has been corrupted.
 *
 * (3) Loop:
 * 	(a) begin transaction
 *    	(b) पात transaction
 *	(c) check TEXASR to see अगर FS has been corrupted
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <pthपढ़ो.h>
#समावेश <माला.स>

#समावेश "utils.h"
#समावेश "tm.h"

पूर्णांक	num_loops	= 1000000;
पूर्णांक	passed = 1;

व्योम tfiar_tfhar(व्योम *in)
अणु
	अचिन्हित दीर्घ tfhar, tfhar_rd, tfiar, tfiar_rd;
	पूर्णांक i;

	/* TFIAR: Last bit has to be high so userspace can पढ़ो रेजिस्टर */
	tfiar = ((अचिन्हित दीर्घ)in) + 1;
	tfiar += 2;
	mtspr(SPRN_TFIAR, tfiar);

	/* TFHAR: Last two bits are reserved */
	tfhar = ((अचिन्हित दीर्घ)in);
	tfhar &= ~0x3UL;
	tfhar += 4;
	mtspr(SPRN_TFHAR, tfhar);

	क्रम (i = 0; i < num_loops; i++)	अणु
		tfhar_rd = mfspr(SPRN_TFHAR);
		tfiar_rd = mfspr(SPRN_TFIAR);
		अगर ( (tfhar != tfhar_rd) || (tfiar != tfiar_rd) ) अणु
			passed = 0;
			वापस;
		पूर्ण
	पूर्ण
	वापस;
पूर्ण

व्योम texasr(व्योम *in)
अणु
	अचिन्हित दीर्घ i;
	uपूर्णांक64_t result = 0;

	क्रम (i = 0; i < num_loops; i++) अणु
		यंत्र __अस्थिर__(
			"tbegin.;"
			"beq    3f ;"
			"tabort. 0 ;"
			"tend.;"

			/* Abort handler */
			"3: ;"
			::: "memory");

                /* Check the TEXASR */
                result = mfspr(SPRN_TEXASR);
		अगर ((result & TEXASR_FS) == 0) अणु
			passed = 0;
			वापस;
		पूर्ण
	पूर्ण
	वापस;
पूर्ण

पूर्णांक test_पंचांगspr()
अणु
	pthपढ़ो_t	*thपढ़ो;
	पूर्णांक	   	thपढ़ो_num;
	अचिन्हित दीर्घ	i;

	SKIP_IF(!have_hपंचांग());

	/* To cause some context चयनing */
	thपढ़ो_num = 10 * sysconf(_SC_NPROCESSORS_ONLN);

	thपढ़ो = दो_स्मृति(thपढ़ो_num * माप(pthपढ़ो_t));
	अगर (thपढ़ो == शून्य)
		वापस निकास_त्रुटि;

	/* Test TFIAR and TFHAR */
	क्रम (i = 0; i < thपढ़ो_num; i += 2) अणु
		अगर (pthपढ़ो_create(&thपढ़ो[i], शून्य, (व्योम *)tfiar_tfhar,
				   (व्योम *)i))
			वापस निकास_त्रुटि;
	पूर्ण
	/* Test TEXASR */
	क्रम (i = 1; i < thपढ़ो_num; i += 2) अणु
		अगर (pthपढ़ो_create(&thपढ़ो[i], शून्य, (व्योम *)texasr, (व्योम *)i))
			वापस निकास_त्रुटि;
	पूर्ण

	क्रम (i = 0; i < thपढ़ो_num; i++) अणु
		अगर (pthपढ़ो_join(thपढ़ो[i], शून्य) != 0)
			वापस निकास_त्रुटि;
	पूर्ण

	मुक्त(thपढ़ो);

	अगर (passed)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अगर (argc > 1) अणु
		अगर (म_भेद(argv[1], "-h") == 0) अणु
			म_लिखो("Syntax:\t [<num loops>]\n");
			वापस 0;
		पूर्ण अन्यथा अणु
			num_loops = म_से_प(argv[1]);
		पूर्ण
	पूर्ण
	वापस test_harness(test_पंचांगspr, "tm_tmspr");
पूर्ण
