<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_GOLDFISH_H
#घोषणा __LINUX_GOLDFISH_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>

/* Helpers क्रम Goldfish भव platक्रमm */

अटल अंतरभूत व्योम gf_ग_लिखो_ptr(स्थिर व्योम *ptr, व्योम __iomem *portl,
				व्योम __iomem *porth)
अणु
	स्थिर अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)ptr;

	__raw_ग_लिखोl(lower_32_bits(addr), portl);
#अगर_घोषित CONFIG_64BIT
	__raw_ग_लिखोl(upper_32_bits(addr), porth);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम gf_ग_लिखो_dma_addr(स्थिर dma_addr_t addr,
				     व्योम __iomem *portl,
				     व्योम __iomem *porth)
अणु
	__raw_ग_लिखोl(lower_32_bits(addr), portl);
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	__raw_ग_लिखोl(upper_32_bits(addr), porth);
#पूर्ण_अगर
पूर्ण


#पूर्ण_अगर /* __LINUX_GOLDFISH_H */
