<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 1999, 2009
 *
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित __ASM_FACILITY_H
#घोषणा __ASM_FACILITY_H

#समावेश <यंत्र/facility-defs.h>
#समावेश <linux/माला.स>
#समावेश <linux/preempt.h>
#समावेश <यंत्र/lowcore.h>

#घोषणा MAX_FACILITY_BIT (माप(((काष्ठा lowcore *)0)->stfle_fac_list) * 8)

अटल अंतरभूत व्योम __set_facility(अचिन्हित दीर्घ nr, व्योम *facilities)
अणु
	अचिन्हित अक्षर *ptr = (अचिन्हित अक्षर *) facilities;

	अगर (nr >= MAX_FACILITY_BIT)
		वापस;
	ptr[nr >> 3] |= 0x80 >> (nr & 7);
पूर्ण

अटल अंतरभूत व्योम __clear_facility(अचिन्हित दीर्घ nr, व्योम *facilities)
अणु
	अचिन्हित अक्षर *ptr = (अचिन्हित अक्षर *) facilities;

	अगर (nr >= MAX_FACILITY_BIT)
		वापस;
	ptr[nr >> 3] &= ~(0x80 >> (nr & 7));
पूर्ण

अटल अंतरभूत पूर्णांक __test_facility(अचिन्हित दीर्घ nr, व्योम *facilities)
अणु
	अचिन्हित अक्षर *ptr;

	अगर (nr >= MAX_FACILITY_BIT)
		वापस 0;
	ptr = (अचिन्हित अक्षर *) facilities + (nr >> 3);
	वापस (*ptr & (0x80 >> (nr & 7))) != 0;
पूर्ण

/*
 * The test_facility function uses the bit ordering where the MSB is bit 0.
 * That makes it easier to query facility bits with the bit number as
 * करोcumented in the Principles of Operation.
 */
अटल अंतरभूत पूर्णांक test_facility(अचिन्हित दीर्घ nr)
अणु
	अचिन्हित दीर्घ facilities_als[] = अणु FACILITIES_ALS पूर्ण;

	अगर (__builtin_स्थिरant_p(nr) && nr < माप(facilities_als) * 8) अणु
		अगर (__test_facility(nr, &facilities_als))
			वापस 1;
	पूर्ण
	वापस __test_facility(nr, &S390_lowcore.stfle_fac_list);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __stfle_यंत्र(u64 *stfle_fac_list, पूर्णांक size)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र("0") = size - 1;

	यंत्र अस्थिर(
		".insn s,0xb2b00000,0(%1)" /* stfle */
		: "+d" (reg0)
		: "a" (stfle_fac_list)
		: "memory", "cc");
	वापस reg0;
पूर्ण

/**
 * stfle - Store facility list extended
 * @stfle_fac_list: array where facility list can be stored
 * @size: size of passed in array in द्विगुन words
 */
अटल अंतरभूत व्योम __stfle(u64 *stfle_fac_list, पूर्णांक size)
अणु
	अचिन्हित दीर्घ nr;

	यंत्र अस्थिर(
		"	stfl	0(0)\n"
		: "=m" (S390_lowcore.stfl_fac_list));
	nr = 4; /* bytes stored by stfl */
	स_नकल(stfle_fac_list, &S390_lowcore.stfl_fac_list, 4);
	अगर (S390_lowcore.stfl_fac_list & 0x01000000) अणु
		/* More facility bits available with stfle */
		nr = __stfle_यंत्र(stfle_fac_list, size);
		nr = min_t(अचिन्हित दीर्घ, (nr + 1) * 8, size * 8);
	पूर्ण
	स_रखो((अक्षर *) stfle_fac_list + nr, 0, size * 8 - nr);
पूर्ण

अटल अंतरभूत व्योम stfle(u64 *stfle_fac_list, पूर्णांक size)
अणु
	preempt_disable();
	__stfle(stfle_fac_list, size);
	preempt_enable();
पूर्ण

#पूर्ण_अगर /* __ASM_FACILITY_H */
