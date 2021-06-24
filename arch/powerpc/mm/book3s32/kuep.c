<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <यंत्र/kup.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/task_size_32.h>
#समावेश <यंत्र/mmu.h>

#घोषणा KUEP_UPDATE_TWO_USER_SEGMENTS(n) करो अणु		\
	अगर (TASK_SIZE > ((n) << 28))			\
		mtsr(val1, (n) << 28);			\
	अगर (TASK_SIZE > (((n) + 1) << 28))		\
		mtsr(val2, ((n) + 1) << 28);		\
	val1 = (val1 + 0x222) & 0xf0ffffff;		\
	val2 = (val2 + 0x222) & 0xf0ffffff;		\
पूर्ण जबतक (0)

अटल __always_अंतरभूत व्योम kuep_update(u32 val)
अणु
	पूर्णांक val1 = val;
	पूर्णांक val2 = (val + 0x111) & 0xf0ffffff;

	KUEP_UPDATE_TWO_USER_SEGMENTS(0);
	KUEP_UPDATE_TWO_USER_SEGMENTS(2);
	KUEP_UPDATE_TWO_USER_SEGMENTS(4);
	KUEP_UPDATE_TWO_USER_SEGMENTS(6);
	KUEP_UPDATE_TWO_USER_SEGMENTS(8);
	KUEP_UPDATE_TWO_USER_SEGMENTS(10);
	KUEP_UPDATE_TWO_USER_SEGMENTS(12);
	KUEP_UPDATE_TWO_USER_SEGMENTS(14);
पूर्ण

व्योम kuep_lock(व्योम)
अणु
	kuep_update(mfsr(0) | SR_NX);
पूर्ण

व्योम kuep_unlock(व्योम)
अणु
	kuep_update(mfsr(0) & ~SR_NX);
पूर्ण
