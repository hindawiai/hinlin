<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_DMA_H
#घोषणा _ASM_S390_DMA_H

#समावेश <यंत्र/पन.स>

/*
 * MAX_DMA_ADDRESS is ambiguous because on s390 its completely unrelated
 * to DMA. It _is_ used क्रम the s390 memory zone split at 2GB caused
 * by the 31 bit heritage.
 */
#घोषणा MAX_DMA_ADDRESS         0x80000000

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक isa_dma_bridge_buggy;
#अन्यथा
#घोषणा isa_dma_bridge_buggy	(0)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_S390_DMA_H */
