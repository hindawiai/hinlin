<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

पूर्णांक
भ_असल(u32 *frD, u32 *frB)
अणु
	frD[0] = frB[0] & 0x7fffffff;
	frD[1] = frB[1];

#अगर_घोषित DEBUG
	prपूर्णांकk("%s: D %p, B %p: ", __func__, frD, frB);
	dump_द्विगुन(frD);
	prपूर्णांकk("\n");
#पूर्ण_अगर

	वापस 0;
पूर्ण
