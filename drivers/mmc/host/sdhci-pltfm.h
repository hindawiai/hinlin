<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2010 MontaVista Software, LLC.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#अगर_अघोषित _DRIVERS_MMC_SDHCI_PLTFM_H
#घोषणा _DRIVERS_MMC_SDHCI_PLTFM_H

#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "sdhci.h"

काष्ठा sdhci_pltfm_data अणु
	स्थिर काष्ठा sdhci_ops *ops;
	अचिन्हित पूर्णांक quirks;
	अचिन्हित पूर्णांक quirks2;
पूर्ण;

काष्ठा sdhci_pltfm_host अणु
	काष्ठा clk *clk;

	/* migrate from sdhci_of_host */
	अचिन्हित पूर्णांक घड़ी;
	u16 xfer_mode_shaकरोw;

	अचिन्हित दीर्घ निजी[] ____cacheline_aligned;
पूर्ण;

#अगर_घोषित CONFIG_MMC_SDHCI_BIG_ENDIAN_32BIT_BYTE_SWAPPER
/*
 * These accessors are deचिन्हित क्रम big endian hosts करोing I/O to
 * little endian controllers incorporating a 32-bit hardware byte swapper.
 */
अटल अंतरभूत u32 sdhci_be32bs_पढ़ोl(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	वापस in_be32(host->ioaddr + reg);
पूर्ण

अटल अंतरभूत u16 sdhci_be32bs_पढ़ोw(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	वापस in_be16(host->ioaddr + (reg ^ 0x2));
पूर्ण

अटल अंतरभूत u8 sdhci_be32bs_पढ़ोb(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	वापस in_8(host->ioaddr + (reg ^ 0x3));
पूर्ण

अटल अंतरभूत व्योम sdhci_be32bs_ग_लिखोl(काष्ठा sdhci_host *host,
				       u32 val, पूर्णांक reg)
अणु
	out_be32(host->ioaddr + reg, val);
पूर्ण

अटल अंतरभूत व्योम sdhci_be32bs_ग_लिखोw(काष्ठा sdhci_host *host,
				       u16 val, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	पूर्णांक base = reg & ~0x3;
	पूर्णांक shअगरt = (reg & 0x2) * 8;

	चयन (reg) अणु
	हाल SDHCI_TRANSFER_MODE:
		/*
		 * Postpone this ग_लिखो, we must करो it together with a
		 * command ग_लिखो that is करोwn below.
		 */
		pltfm_host->xfer_mode_shaकरोw = val;
		वापस;
	हाल SDHCI_COMMAND:
		sdhci_be32bs_ग_लिखोl(host,
				    val << 16 | pltfm_host->xfer_mode_shaकरोw,
				    SDHCI_TRANSFER_MODE);
		वापस;
	पूर्ण
	clrsetbits_be32(host->ioaddr + base, 0xffff << shअगरt, val << shअगरt);
पूर्ण

अटल अंतरभूत व्योम sdhci_be32bs_ग_लिखोb(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	पूर्णांक base = reg & ~0x3;
	पूर्णांक shअगरt = (reg & 0x3) * 8;

	clrsetbits_be32(host->ioaddr + base , 0xff << shअगरt, val << shअगरt);
पूर्ण
#पूर्ण_अगर /* CONFIG_MMC_SDHCI_BIG_ENDIAN_32BIT_BYTE_SWAPPER */

व्योम sdhci_get_property(काष्ठा platक्रमm_device *pdev);

अटल अंतरभूत व्योम sdhci_get_of_property(काष्ठा platक्रमm_device *pdev)
अणु
	वापस sdhci_get_property(pdev);
पूर्ण

बाह्य काष्ठा sdhci_host *sdhci_pltfm_init(काष्ठा platक्रमm_device *pdev,
					  स्थिर काष्ठा sdhci_pltfm_data *pdata,
					  माप_प्रकार priv_size);
बाह्य व्योम sdhci_pltfm_मुक्त(काष्ठा platक्रमm_device *pdev);

बाह्य पूर्णांक sdhci_pltfm_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
				स्थिर काष्ठा sdhci_pltfm_data *pdata,
				माप_प्रकार priv_size);
बाह्य पूर्णांक sdhci_pltfm_unरेजिस्टर(काष्ठा platक्रमm_device *pdev);

बाह्य अचिन्हित पूर्णांक sdhci_pltfm_clk_get_max_घड़ी(काष्ठा sdhci_host *host);

अटल अंतरभूत व्योम *sdhci_pltfm_priv(काष्ठा sdhci_pltfm_host *host)
अणु
	वापस host->निजी;
पूर्ण

बाह्य स्थिर काष्ठा dev_pm_ops sdhci_pltfm_pmops;
#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक sdhci_pltfm_suspend(काष्ठा device *dev);
पूर्णांक sdhci_pltfm_resume(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक sdhci_pltfm_suspend(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक sdhci_pltfm_resume(काष्ठा device *dev) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _DRIVERS_MMC_SDHCI_PLTFM_H */
