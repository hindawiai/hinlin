<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_BMIPS_IOREMAP_H
#घोषणा __ASM_MACH_BMIPS_IOREMAP_H

#समावेश <linux/types.h>

अटल अंतरभूत पूर्णांक is_bmips_पूर्णांकernal_रेजिस्टरs(phys_addr_t offset)
अणु
	अगर (offset >= 0xfff80000)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __iomem *plat_ioremap(phys_addr_t offset, अचिन्हित दीर्घ size,
					 अचिन्हित दीर्घ flags)
अणु
	अगर (is_bmips_पूर्णांकernal_रेजिस्टरs(offset))
		वापस (व्योम __iomem *)offset;

	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक plat_iounmap(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस is_bmips_पूर्णांकernal_रेजिस्टरs((अचिन्हित दीर्घ)addr);
पूर्ण

#पूर्ण_अगर /* __ASM_MACH_BMIPS_IOREMAP_H */
