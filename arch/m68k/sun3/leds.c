<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <यंत्र/contregs.h>
#समावेश <यंत्र/sun3mmu.h>
#समावेश <यंत्र/पन.स>

व्योम sun3_leds(अचिन्हित अक्षर byte)
अणु
	अचिन्हित अक्षर dfc;

	GET_DFC(dfc);
	SET_DFC(FC_CONTROL);
	SET_CONTROL_BYTE(AC_LEDS, byte);
	SET_DFC(dfc);
पूर्ण
