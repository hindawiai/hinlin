<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

पूर्णांक
stfd(व्योम *frS, व्योम *ea)
अणु
#अगर 0
#अगर_घोषित DEBUG
	prपूर्णांकk("%s: S %p, ea %p: ", __func__, frS, ea);
	dump_द्विगुन(frS);
	prपूर्णांकk("\n");
#पूर्ण_अगर
#पूर्ण_अगर

	अगर (copy_to_user(ea, frS, माप(द्विगुन)))
		वापस -EFAULT;

	वापस 0;
पूर्ण
