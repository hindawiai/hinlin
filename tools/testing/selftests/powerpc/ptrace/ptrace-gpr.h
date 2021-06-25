<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 */
#घोषणा GPR_1	1
#घोषणा GPR_2	2
#घोषणा GPR_3	3
#घोषणा GPR_4	4

#घोषणा FPR_1	0.001
#घोषणा FPR_2	0.002
#घोषणा FPR_3	0.003
#घोषणा FPR_4	0.004

#घोषणा FPR_1_REP 0x3f50624de0000000
#घोषणा FPR_2_REP 0x3f60624de0000000
#घोषणा FPR_3_REP 0x3f689374c0000000
#घोषणा FPR_4_REP 0x3f70624de0000000

/* Buffer must have 18 elements */
पूर्णांक validate_gpr(अचिन्हित दीर्घ *gpr, अचिन्हित दीर्घ val)
अणु
	पूर्णांक i, found = 1;

	क्रम (i = 0; i < 18; i++) अणु
		अगर (gpr[i] != val) अणु
			म_लिखो("GPR[%d]: %lx Expected: %lx\n",
				i+14, gpr[i], val);
			found = 0;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस TEST_FAIL;
	वापस TEST_PASS;
पूर्ण

/* Buffer must have 32 elements */
पूर्णांक validate_fpr(अचिन्हित दीर्घ *fpr, अचिन्हित दीर्घ val)
अणु
	पूर्णांक i, found = 1;

	क्रम (i = 0; i < 32; i++) अणु
		अगर (fpr[i] != val) अणु
			म_लिखो("FPR[%d]: %lx Expected: %lx\n", i, fpr[i], val);
			found = 0;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस TEST_FAIL;
	वापस TEST_PASS;
पूर्ण

/* Buffer must have 32 elements */
पूर्णांक validate_fpr_भग्न(भग्न *fpr, भग्न val)
अणु
	पूर्णांक i, found = 1;

	क्रम (i = 0; i < 32; i++) अणु
		अगर (fpr[i] != val) अणु
			म_लिखो("FPR[%d]: %f Expected: %f\n", i, fpr[i], val);
			found = 0;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस TEST_FAIL;
	वापस TEST_PASS;
पूर्ण
