<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _PPC_BOOT_REG_H
#घोषणा _PPC_BOOT_REG_H
/*
 * Copyright 2007 Davud Gibson, IBM Corporation.
 */

अटल अंतरभूत u32 mfpvr(व्योम)
अणु
	u32 pvr;
	यंत्र अस्थिर ("mfpvr	%0" : "=r"(pvr));
	वापस pvr;
पूर्ण

#घोषणा __stringअगरy_1(x)	#x
#घोषणा __stringअगरy(x)		__stringअगरy_1(x)

#घोषणा mfspr(rn)	(अणुअचिन्हित दीर्घ rval; \
			यंत्र अस्थिर("mfspr %0," __stringअगरy(rn) \
				: "=r" (rval)); rval; पूर्ण)
#घोषणा mtspr(rn, v)	यंत्र अस्थिर("mtspr " __stringअगरy(rn) ",%0" : : "r" (v))

रेजिस्टर व्योम *__stack_poपूर्णांकer यंत्र("r1");
#घोषणा get_sp()	(__stack_poपूर्णांकer)

#पूर्ण_अगर	/* _PPC_BOOT_REG_H */
