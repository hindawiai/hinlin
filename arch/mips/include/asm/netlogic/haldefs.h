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

#अगर_अघोषित __NLM_HAL_HALDEFS_H__
#घोषणा __NLM_HAL_HALDEFS_H__

#समावेश <linux/irqflags.h>	/* क्रम local_irq_disable */

/*
 * This file contains platक्रमm specअगरic memory mapped IO implementation
 * and will provide a way to पढ़ो 32/64 bit memory mapped रेजिस्टरs in
 * all ABIs
 */
अटल अंतरभूत uपूर्णांक32_t
nlm_पढ़ो_reg(uपूर्णांक64_t base, uपूर्णांक32_t reg)
अणु
	अस्थिर uपूर्णांक32_t *addr = (अस्थिर uपूर्णांक32_t *)(दीर्घ)base + reg;

	वापस *addr;
पूर्ण

अटल अंतरभूत व्योम
nlm_ग_लिखो_reg(uपूर्णांक64_t base, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	अस्थिर uपूर्णांक32_t *addr = (अस्थिर uपूर्णांक32_t *)(दीर्घ)base + reg;

	*addr = val;
पूर्ण

/*
 * For o32 compilation, we have to disable पूर्णांकerrupts to access 64 bit
 * रेजिस्टरs
 *
 * We need to disable पूर्णांकerrupts because we save just the lower 32 bits of
 * रेजिस्टरs in  पूर्णांकerrupt handling. So अगर we get hit by an पूर्णांकerrupt जबतक
 * using the upper 32 bits of a रेजिस्टर, we lose.
 */

अटल अंतरभूत uपूर्णांक64_t
nlm_पढ़ो_reg64(uपूर्णांक64_t base, uपूर्णांक32_t reg)
अणु
	uपूर्णांक64_t addr = base + (reg >> 1) * माप(uपूर्णांक64_t);
	अस्थिर uपूर्णांक64_t *ptr = (अस्थिर uपूर्णांक64_t *)(दीर्घ)addr;
	uपूर्णांक64_t val;

	अगर (माप(अचिन्हित दीर्घ) == 4) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		__यंत्र__ __अस्थिर__(
			".set	push"			"\n\t"
			".set	mips64"			"\n\t"
			"ld	%L0, %1"		"\n\t"
			"dsra32	%M0, %L0, 0"		"\n\t"
			"sll	%L0, %L0, 0"		"\n\t"
			".set	pop"			"\n"
			: "=r" (val)
			: "m" (*ptr));
		local_irq_restore(flags);
	पूर्ण अन्यथा
		val = *ptr;

	वापस val;
पूर्ण

अटल अंतरभूत व्योम
nlm_ग_लिखो_reg64(uपूर्णांक64_t base, uपूर्णांक32_t reg, uपूर्णांक64_t val)
अणु
	uपूर्णांक64_t addr = base + (reg >> 1) * माप(uपूर्णांक64_t);
	अस्थिर uपूर्णांक64_t *ptr = (अस्थिर uपूर्णांक64_t *)(दीर्घ)addr;

	अगर (माप(अचिन्हित दीर्घ) == 4) अणु
		अचिन्हित दीर्घ flags;
		uपूर्णांक64_t पंचांगp;

		local_irq_save(flags);
		__यंत्र__ __अस्थिर__(
			".set	push"			"\n\t"
			".set	mips64"			"\n\t"
			"dsll32	%L0, %L0, 0"		"\n\t"
			"dsrl32	%L0, %L0, 0"		"\n\t"
			"dsll32	%M0, %M0, 0"		"\n\t"
			"or	%L0, %L0, %M0"		"\n\t"
			"sd	%L0, %2"		"\n\t"
			".set	pop"			"\n"
			: "=r" (पंचांगp)
			: "0" (val), "m" (*ptr));
		local_irq_restore(flags);
	पूर्ण अन्यथा
		*ptr = val;
पूर्ण

/*
 * Routines to store 32/64 bit values to 64 bit addresses,
 * used when going thru XKPHYS to access रेजिस्टरs
 */
अटल अंतरभूत uपूर्णांक32_t
nlm_पढ़ो_reg_xkphys(uपूर्णांक64_t base, uपूर्णांक32_t reg)
अणु
	वापस nlm_पढ़ो_reg(base, reg);
पूर्ण

अटल अंतरभूत व्योम
nlm_ग_लिखो_reg_xkphys(uपूर्णांक64_t base, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	nlm_ग_लिखो_reg(base, reg, val);
पूर्ण

अटल अंतरभूत uपूर्णांक64_t
nlm_पढ़ो_reg64_xkphys(uपूर्णांक64_t base, uपूर्णांक32_t reg)
अणु
	वापस nlm_पढ़ो_reg64(base, reg);
पूर्ण

अटल अंतरभूत व्योम
nlm_ग_लिखो_reg64_xkphys(uपूर्णांक64_t base, uपूर्णांक32_t reg, uपूर्णांक64_t val)
अणु
	nlm_ग_लिखो_reg64(base, reg, val);
पूर्ण

/* Location where IO base is mapped */
बाह्य uपूर्णांक64_t nlm_io_base;

#अगर defined(CONFIG_CPU_XLP)
अटल अंतरभूत uपूर्णांक64_t
nlm_pcicfg_base(uपूर्णांक32_t devoffset)
अणु
	वापस nlm_io_base + devoffset;
पूर्ण

#या_अगर defined(CONFIG_CPU_XLR)

अटल अंतरभूत uपूर्णांक64_t
nlm_mmio_base(uपूर्णांक32_t devoffset)
अणु
	वापस nlm_io_base + devoffset;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
