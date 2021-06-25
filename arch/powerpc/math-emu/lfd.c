<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/sfp-machine.h>
#समावेश <math-emu/द्विगुन.h>

पूर्णांक
lfd(व्योम *frD, व्योम *ea)
अणु
	अगर (copy_from_user(frD, ea, माप(द्विगुन)))
		वापस -EFAULT;
#अगर_घोषित DEBUG
	prपूर्णांकk("%s: D %p, ea %p: ", __func__, frD, ea);
	dump_द्विगुन(frD);
	prपूर्णांकk("\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण
