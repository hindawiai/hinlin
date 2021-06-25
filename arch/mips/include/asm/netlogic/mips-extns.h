<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _ASM_NLM_MIPS_EXTS_H
#घोषणा _ASM_NLM_MIPS_EXTS_H

/*
 * XLR and XLP पूर्णांकerrupt request and पूर्णांकerrupt mask रेजिस्टरs
 */
/*
 * NOTE: Do not save/restore flags around ग_लिखो_c0_eimr().
 * On non-R2 platक्रमms the flags has part of EIMR that is shaकरोwed in STATUS
 * रेजिस्टर. Restoring flags will overग_लिखो the lower 8 bits of EIMR.
 *
 * Call with पूर्णांकerrupts disabled.
 */
#घोषणा ग_लिखो_c0_eimr(val)						\
करो अणु									\
	अगर (माप(अचिन्हित दीर्घ) == 4) अणु				\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips64\n\t"				\
			"dsll\t%L0, %L0, 32\n\t"			\
			"dsrl\t%L0, %L0, 32\n\t"			\
			"dsll\t%M0, %M0, 32\n\t"			\
			"or\t%L0, %L0, %M0\n\t"				\
			"dmtc0\t%L0, $9, 7\n\t"				\
			".set\tmips0"					\
			: : "r" (val));					\
	पूर्ण अन्यथा								\
		__ग_लिखो_64bit_c0_रेजिस्टर($9, 7, (val));		\
पूर्ण जबतक (0)

/*
 * Handling the 64 bit EIMR and EIRR रेजिस्टरs in 32-bit mode with
 * standard functions will be very inefficient. This provides
 * optimized functions क्रम the normal operations on the रेजिस्टरs.
 *
 * Call with पूर्णांकerrupts disabled.
 */
अटल अंतरभूत व्योम ack_c0_eirr(पूर्णांक irq)
अणु
	__यंत्र__ __अस्थिर__(
		".set	push\n\t"
		".set	mips64\n\t"
		".set	noat\n\t"
		"li	$1, 1\n\t"
		"dsllv	$1, $1, %0\n\t"
		"dmtc0	$1, $9, 6\n\t"
		".set	pop"
		: : "r" (irq));
पूर्ण

अटल अंतरभूत व्योम set_c0_eimr(पूर्णांक irq)
अणु
	__यंत्र__ __अस्थिर__(
		".set	push\n\t"
		".set	mips64\n\t"
		".set	noat\n\t"
		"li	$1, 1\n\t"
		"dsllv	%0, $1, %0\n\t"
		"dmfc0	$1, $9, 7\n\t"
		"or	$1, %0\n\t"
		"dmtc0	$1, $9, 7\n\t"
		".set	pop"
		: "+r" (irq));
पूर्ण

अटल अंतरभूत व्योम clear_c0_eimr(पूर्णांक irq)
अणु
	__यंत्र__ __अस्थिर__(
		".set	push\n\t"
		".set	mips64\n\t"
		".set	noat\n\t"
		"li	$1, 1\n\t"
		"dsllv	%0, $1, %0\n\t"
		"dmfc0	$1, $9, 7\n\t"
		"or	$1, %0\n\t"
		"xor	$1, %0\n\t"
		"dmtc0	$1, $9, 7\n\t"
		".set	pop"
		: "+r" (irq));
पूर्ण

/*
 * Read c0 eimr and c0 eirr, करो AND of the two values, the result is
 * the पूर्णांकerrupts which are उठाओd and are not masked.
 */
अटल अंतरभूत uपूर्णांक64_t पढ़ो_c0_eirr_and_eimr(व्योम)
अणु
	uपूर्णांक64_t val;

#अगर_घोषित CONFIG_64BIT
	val = __पढ़ो_64bit_c0_रेजिस्टर($9, 6) & __पढ़ो_64bit_c0_रेजिस्टर($9, 7);
#अन्यथा
	__यंत्र__ __अस्थिर__(
		".set	push\n\t"
		".set	mips64\n\t"
		".set	noat\n\t"
		"dmfc0	%M0, $9, 6\n\t"
		"dmfc0	%L0, $9, 7\n\t"
		"and	%M0, %L0\n\t"
		"dsll	%L0, %M0, 32\n\t"
		"dsra	%M0, %M0, 32\n\t"
		"dsra	%L0, %L0, 32\n\t"
		".set	pop"
		: "=r" (val));
#पूर्ण_अगर
	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक hard_smp_processor_id(व्योम)
अणु
	वापस __पढ़ो_32bit_c0_रेजिस्टर($15, 1) & 0x3ff;
पूर्ण

अटल अंतरभूत पूर्णांक nlm_nodeid(व्योम)
अणु
	uपूर्णांक32_t prid = पढ़ो_c0_prid() & PRID_IMP_MASK;

	अगर ((prid == PRID_IMP_NETLOGIC_XLP9XX) ||
			(prid == PRID_IMP_NETLOGIC_XLP5XX))
		वापस (__पढ़ो_32bit_c0_रेजिस्टर($15, 1) >> 7) & 0x7;
	अन्यथा
		वापस (__पढ़ो_32bit_c0_रेजिस्टर($15, 1) >> 5) & 0x3;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक nlm_core_id(व्योम)
अणु
	uपूर्णांक32_t prid = पढ़ो_c0_prid() & PRID_IMP_MASK;

	अगर ((prid == PRID_IMP_NETLOGIC_XLP9XX) ||
			(prid == PRID_IMP_NETLOGIC_XLP5XX))
		वापस (पढ़ो_c0_ebase() & 0x7c) >> 2;
	अन्यथा
		वापस (पढ़ो_c0_ebase() & 0x1c) >> 2;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक nlm_thपढ़ो_id(व्योम)
अणु
	वापस पढ़ो_c0_ebase() & 0x3;
पूर्ण

#घोषणा __पढ़ो_64bit_c2_split(source, sel)				\
(अणु									\
	अचिन्हित दीर्घ दीर्घ __val;					\
	अचिन्हित दीर्घ __flags;						\
									\
	local_irq_save(__flags);					\
	अगर (sel == 0)							\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips64\n\t"				\
			"dmfc2\t%M0, " #source "\n\t"			\
			"dsll\t%L0, %M0, 32\n\t"			\
			"dsra\t%M0, %M0, 32\n\t"			\
			"dsra\t%L0, %L0, 32\n\t"			\
			".set\tmips0\n\t"				\
			: "=r" (__val));				\
	अन्यथा								\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips64\n\t"				\
			"dmfc2\t%M0, " #source ", " #sel "\n\t"		\
			"dsll\t%L0, %M0, 32\n\t"			\
			"dsra\t%M0, %M0, 32\n\t"			\
			"dsra\t%L0, %L0, 32\n\t"			\
			".set\tmips0\n\t"				\
			: "=r" (__val));				\
	local_irq_restore(__flags);					\
									\
	__val;								\
पूर्ण)

#घोषणा __ग_लिखो_64bit_c2_split(source, sel, val)			\
करो अणु									\
	अचिन्हित दीर्घ __flags;						\
									\
	local_irq_save(__flags);					\
	अगर (sel == 0)							\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips64\n\t"				\
			"dsll\t%L0, %L0, 32\n\t"			\
			"dsrl\t%L0, %L0, 32\n\t"			\
			"dsll\t%M0, %M0, 32\n\t"			\
			"or\t%L0, %L0, %M0\n\t"				\
			"dmtc2\t%L0, " #source "\n\t"			\
			".set\tmips0\n\t"				\
			: : "r" (val));					\
	अन्यथा								\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips64\n\t"				\
			"dsll\t%L0, %L0, 32\n\t"			\
			"dsrl\t%L0, %L0, 32\n\t"			\
			"dsll\t%M0, %M0, 32\n\t"			\
			"or\t%L0, %L0, %M0\n\t"				\
			"dmtc2\t%L0, " #source ", " #sel "\n\t"		\
			".set\tmips0\n\t"				\
			: : "r" (val));					\
	local_irq_restore(__flags);					\
पूर्ण जबतक (0)

#घोषणा __पढ़ो_32bit_c2_रेजिस्टर(source, sel)				\
(अणु uपूर्णांक32_t __res;							\
	अगर (sel == 0)							\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips32\n\t"				\
			"mfc2\t%0, " #source "\n\t"			\
			".set\tmips0\n\t"				\
			: "=r" (__res));				\
	अन्यथा								\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips32\n\t"				\
			"mfc2\t%0, " #source ", " #sel "\n\t"		\
			".set\tmips0\n\t"				\
			: "=r" (__res));				\
	__res;								\
पूर्ण)

#घोषणा __पढ़ो_64bit_c2_रेजिस्टर(source, sel)				\
(अणु अचिन्हित दीर्घ दीर्घ __res;						\
	अगर (माप(अचिन्हित दीर्घ) == 4)					\
		__res = __पढ़ो_64bit_c2_split(source, sel);		\
	अन्यथा अगर (sel == 0)						\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips64\n\t"				\
			"dmfc2\t%0, " #source "\n\t"			\
			".set\tmips0\n\t"				\
			: "=r" (__res));				\
	अन्यथा								\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips64\n\t"				\
			"dmfc2\t%0, " #source ", " #sel "\n\t"		\
			".set\tmips0\n\t"				\
			: "=r" (__res));				\
	__res;								\
पूर्ण)

#घोषणा __ग_लिखो_64bit_c2_रेजिस्टर(रेजिस्टर, sel, value)			\
करो अणु									\
	अगर (माप(अचिन्हित दीर्घ) == 4)					\
		__ग_लिखो_64bit_c2_split(रेजिस्टर, sel, value);		\
	अन्यथा अगर (sel == 0)						\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips64\n\t"				\
			"dmtc2\t%z0, " #रेजिस्टर "\n\t"			\
			".set\tmips0\n\t"				\
			: : "Jr" (value));				\
	अन्यथा								\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips64\n\t"				\
			"dmtc2\t%z0, " #रेजिस्टर ", " #sel "\n\t"	\
			".set\tmips0\n\t"				\
			: : "Jr" (value));				\
पूर्ण जबतक (0)

#घोषणा __ग_लिखो_32bit_c2_रेजिस्टर(reg, sel, value)			\
(अणु									\
	अगर (sel == 0)							\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips32\n\t"				\
			"mtc2\t%z0, " #reg "\n\t"			\
			".set\tmips0\n\t"				\
			: : "Jr" (value));				\
	अन्यथा								\
		__यंत्र__ __अस्थिर__(					\
			".set\tmips32\n\t"				\
			"mtc2\t%z0, " #reg ", " #sel "\n\t"		\
			".set\tmips0\n\t"				\
			: : "Jr" (value));				\
पूर्ण)

#पूर्ण_अगर /*_ASM_NLM_MIPS_EXTS_H */
