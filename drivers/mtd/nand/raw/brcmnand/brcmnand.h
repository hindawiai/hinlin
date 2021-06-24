<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright तऊ 2015 Broadcom Corporation
 */

#अगर_अघोषित __BRCMन_अंकD_H__
#घोषणा __BRCMन_अंकD_H__

#समावेश <linux/types.h>
#समावेश <linux/पन.स>

काष्ठा platक्रमm_device;
काष्ठा dev_pm_ops;

काष्ठा brcmnand_soc अणु
	bool (*ctlrdy_ack)(काष्ठा brcmnand_soc *soc);
	व्योम (*ctlrdy_set_enabled)(काष्ठा brcmnand_soc *soc, bool en);
	व्योम (*prepare_data_bus)(काष्ठा brcmnand_soc *soc, bool prepare,
				 bool is_param);
पूर्ण;

अटल अंतरभूत व्योम brcmnand_soc_data_bus_prepare(काष्ठा brcmnand_soc *soc,
						 bool is_param)
अणु
	अगर (soc && soc->prepare_data_bus)
		soc->prepare_data_bus(soc, true, is_param);
पूर्ण

अटल अंतरभूत व्योम brcmnand_soc_data_bus_unprepare(काष्ठा brcmnand_soc *soc,
						   bool is_param)
अणु
	अगर (soc && soc->prepare_data_bus)
		soc->prepare_data_bus(soc, false, is_param);
पूर्ण

अटल अंतरभूत u32 brcmnand_पढ़ोl(व्योम __iomem *addr)
अणु
	/*
	 * MIPS endianness is configured by boot strap, which also reverses all
	 * bus endianness (i.e., big-endian CPU + big endian bus ==> native
	 * endian I/O).
	 *
	 * Other architectures (e.g., ARM) either करो not support big endian, or
	 * अन्यथा leave I/O in little endian mode.
	 */
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		वापस __raw_पढ़ोl(addr);
	अन्यथा
		वापस पढ़ोl_relaxed(addr);
पूर्ण

अटल अंतरभूत व्योम brcmnand_ग_लिखोl(u32 val, व्योम __iomem *addr)
अणु
	/* See brcmnand_पढ़ोl() comments */
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		__raw_ग_लिखोl(val, addr);
	अन्यथा
		ग_लिखोl_relaxed(val, addr);
पूर्ण

पूर्णांक brcmnand_probe(काष्ठा platक्रमm_device *pdev, काष्ठा brcmnand_soc *soc);
पूर्णांक brcmnand_हटाओ(काष्ठा platक्रमm_device *pdev);

बाह्य स्थिर काष्ठा dev_pm_ops brcmnand_pm_ops;

#पूर्ण_अगर /* __BRCMन_अंकD_H__ */
