<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BCM63XX_IOREMAP_H_
#घोषणा BCM63XX_IOREMAP_H_

#समावेश <bcm63xx_cpu.h>

अटल अंतरभूत पूर्णांक is_bcm63xx_पूर्णांकernal_रेजिस्टरs(phys_addr_t offset)
अणु
	चयन (bcm63xx_get_cpu_id()) अणु
	हाल BCM3368_CPU_ID:
		अगर (offset >= 0xfff80000)
			वापस 1;
		अवरोध;
	हाल BCM6338_CPU_ID:
	हाल BCM6345_CPU_ID:
	हाल BCM6348_CPU_ID:
	हाल BCM6358_CPU_ID:
		अगर (offset >= 0xfff00000)
			वापस 1;
		अवरोध;
	हाल BCM6328_CPU_ID:
	हाल BCM6362_CPU_ID:
	हाल BCM6368_CPU_ID:
		अगर (offset >= 0xb0000000 && offset < 0xb1000000)
			वापस 1;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __iomem *plat_ioremap(phys_addr_t offset, अचिन्हित दीर्घ size,
					 अचिन्हित दीर्घ flags)
अणु
	अगर (is_bcm63xx_पूर्णांकernal_रेजिस्टरs(offset))
		वापस (व्योम __iomem *)offset;
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक plat_iounmap(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस is_bcm63xx_पूर्णांकernal_रेजिस्टरs((अचिन्हित दीर्घ)addr);
पूर्ण

#पूर्ण_अगर /* BCM63XX_IOREMAP_H_ */
