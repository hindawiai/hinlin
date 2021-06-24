<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_EDAC_H
#घोषणा _ASM_X86_EDAC_H

/* ECC atomic, DMA, SMP and पूर्णांकerrupt safe scrub function */

अटल अंतरभूत व्योम edac_atomic_scrub(व्योम *va, u32 size)
अणु
	u32 i, *virt_addr = va;

	/*
	 * Very carefully पढ़ो and ग_लिखो to memory atomically so we
	 * are पूर्णांकerrupt, DMA and SMP safe.
	 */
	क्रम (i = 0; i < size / 4; i++, virt_addr++)
		यंत्र अस्थिर("lock; addl $0, %0"::"m" (*virt_addr));
पूर्ण

#पूर्ण_अगर /* _ASM_X86_EDAC_H */
