<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 */
#घोषणा TAR_1   10
#घोषणा TAR_2   20
#घोषणा TAR_3   30
#घोषणा TAR_4   40
#घोषणा TAR_5   50

#घोषणा DSCR_1  100
#घोषणा DSCR_2  200
#घोषणा DSCR_3  300
#घोषणा DSCR_4  400
#घोषणा DSCR_5  500

#घोषणा PPR_1   0x4000000000000         /* or 31,31,31*/
#घोषणा PPR_2   0x8000000000000         /* or 1,1,1 */
#घोषणा PPR_3   0xc000000000000         /* or 6,6,6 */
#घोषणा PPR_4   0x10000000000000        /* or 2,2,2 */

अक्षर *user_पढ़ो = "[User Read (Running)]";
अक्षर *user_ग_लिखो = "[User Write (Running)]";
अक्षर *ptrace_पढ़ो_running = "[Ptrace Read (Running)]";
अक्षर *ptrace_ग_लिखो_running = "[Ptrace Write (Running)]";
अक्षर *ptrace_पढ़ो_ckpt = "[Ptrace Read (Checkpointed)]";
अक्षर *ptrace_ग_लिखो_ckpt = "[Ptrace Write (Checkpointed)]";

पूर्णांक validate_tar_रेजिस्टरs(अचिन्हित दीर्घ *reg, अचिन्हित दीर्घ tar,
				अचिन्हित दीर्घ ppr, अचिन्हित दीर्घ dscr)
अणु
	पूर्णांक match = 1;

	अगर (reg[0] != tar)
		match = 0;

	अगर (reg[1] != ppr)
		match = 0;

	अगर (reg[2] != dscr)
		match = 0;

	अगर (!match)
		वापस TEST_FAIL;
	वापस TEST_PASS;
पूर्ण
