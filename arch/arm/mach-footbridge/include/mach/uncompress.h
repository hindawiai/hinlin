<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-footbridge/include/mach/uncompress.h
 *
 *  Copyright (C) 1996-1999 Russell King
 */
#समावेश <यंत्र/mach-types.h>

/*
 * Note! This could cause problems on the NetWinder
 */
#घोषणा DC21285_BASE ((अस्थिर अचिन्हित पूर्णांक *)0x42000160)
#घोषणा SER0_BASE    ((अस्थिर अचिन्हित अक्षर *)0x7c0003f8)

अटल अंतरभूत व्योम अ_दो(अक्षर c)
अणु
	अगर (machine_is_netwinder()) अणु
		जबतक ((SER0_BASE[5] & 0x60) != 0x60)
			barrier();
		SER0_BASE[0] = c;
	पूर्ण अन्यथा अणु
		जबतक (DC21285_BASE[6] & 8);
		DC21285_BASE[0] = c;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम flush(व्योम)
अणु
पूर्ण

/*
 * nothing to करो
 */
#घोषणा arch_decomp_setup()
