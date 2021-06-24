<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>

पूर्णांक
stfiwx(u32 *frS, व्योम *ea)
अणु
#अगर_घोषित DEBUG
	prपूर्णांकk("%s: %p %p\n", __func__, frS, ea);
#पूर्ण_अगर

	अगर (copy_to_user(ea, &frS[1], माप(frS[1])))
		वापस -EFAULT;

	वापस 0;
पूर्ण
