<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Atheros AR71XX/AR724X/AR913X common definitions
 *
 *  Copyright (C) 2008-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 *
 *  Parts of this file are based on Atheros' 2.6.15 BSP
 */

#अगर_अघोषित __ASM_MACH_ATH79_H
#घोषणा __ASM_MACH_ATH79_H

#समावेश <linux/types.h>
#समावेश <linux/पन.स>

क्रमागत ath79_soc_type अणु
	ATH79_SOC_UNKNOWN,
	ATH79_SOC_AR7130,
	ATH79_SOC_AR7141,
	ATH79_SOC_AR7161,
	ATH79_SOC_AR7240,
	ATH79_SOC_AR7241,
	ATH79_SOC_AR7242,
	ATH79_SOC_AR9130,
	ATH79_SOC_AR9132,
	ATH79_SOC_AR9330,
	ATH79_SOC_AR9331,
	ATH79_SOC_AR9341,
	ATH79_SOC_AR9342,
	ATH79_SOC_AR9344,
	ATH79_SOC_QCA9533,
	ATH79_SOC_QCA9556,
	ATH79_SOC_QCA9558,
	ATH79_SOC_TP9343,
	ATH79_SOC_QCA956X,
पूर्ण;

बाह्य क्रमागत ath79_soc_type ath79_soc;
बाह्य अचिन्हित पूर्णांक ath79_soc_rev;

अटल अंतरभूत पूर्णांक soc_is_ar71xx(व्योम)
अणु
	वापस (ath79_soc == ATH79_SOC_AR7130 ||
		ath79_soc == ATH79_SOC_AR7141 ||
		ath79_soc == ATH79_SOC_AR7161);
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_ar724x(व्योम)
अणु
	वापस (ath79_soc == ATH79_SOC_AR7240 ||
		ath79_soc == ATH79_SOC_AR7241 ||
		ath79_soc == ATH79_SOC_AR7242);
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_ar7240(व्योम)
अणु
	वापस (ath79_soc == ATH79_SOC_AR7240);
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_ar7241(व्योम)
अणु
	वापस (ath79_soc == ATH79_SOC_AR7241);
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_ar7242(व्योम)
अणु
	वापस (ath79_soc == ATH79_SOC_AR7242);
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_ar913x(व्योम)
अणु
	वापस (ath79_soc == ATH79_SOC_AR9130 ||
		ath79_soc == ATH79_SOC_AR9132);
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_ar933x(व्योम)
अणु
	वापस (ath79_soc == ATH79_SOC_AR9330 ||
		ath79_soc == ATH79_SOC_AR9331);
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_ar9341(व्योम)
अणु
	वापस (ath79_soc == ATH79_SOC_AR9341);
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_ar9342(व्योम)
अणु
	वापस (ath79_soc == ATH79_SOC_AR9342);
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_ar9344(व्योम)
अणु
	वापस (ath79_soc == ATH79_SOC_AR9344);
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_ar934x(व्योम)
अणु
	वापस soc_is_ar9341() || soc_is_ar9342() || soc_is_ar9344();
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_qca9533(व्योम)
अणु
	वापस ath79_soc == ATH79_SOC_QCA9533;
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_qca953x(व्योम)
अणु
	वापस soc_is_qca9533();
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_qca9556(व्योम)
अणु
	वापस ath79_soc == ATH79_SOC_QCA9556;
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_qca9558(व्योम)
अणु
	वापस ath79_soc == ATH79_SOC_QCA9558;
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_qca955x(व्योम)
अणु
	वापस soc_is_qca9556() || soc_is_qca9558();
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_tp9343(व्योम)
अणु
	वापस ath79_soc == ATH79_SOC_TP9343;
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_qca9561(व्योम)
अणु
	वापस ath79_soc == ATH79_SOC_QCA956X;
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_qca9563(व्योम)
अणु
	वापस ath79_soc == ATH79_SOC_QCA956X;
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_qca956x(व्योम)
अणु
	वापस soc_is_qca9561() || soc_is_qca9563();
पूर्ण

व्योम ath79_ddr_wb_flush(अचिन्हित पूर्णांक reg);
व्योम ath79_ddr_set_pci_winकरोws(व्योम);

बाह्य व्योम __iomem *ath79_pll_base;
बाह्य व्योम __iomem *ath79_reset_base;

अटल अंतरभूत व्योम ath79_pll_wr(अचिन्हित reg, u32 val)
अणु
	__raw_ग_लिखोl(val, ath79_pll_base + reg);
पूर्ण

अटल अंतरभूत u32 ath79_pll_rr(अचिन्हित reg)
अणु
	वापस __raw_पढ़ोl(ath79_pll_base + reg);
पूर्ण

अटल अंतरभूत व्योम ath79_reset_wr(अचिन्हित reg, u32 val)
अणु
	__raw_ग_लिखोl(val, ath79_reset_base + reg);
	(व्योम) __raw_पढ़ोl(ath79_reset_base + reg); /* flush */
पूर्ण

अटल अंतरभूत u32 ath79_reset_rr(अचिन्हित reg)
अणु
	वापस __raw_पढ़ोl(ath79_reset_base + reg);
पूर्ण

व्योम ath79_device_reset_set(u32 mask);
व्योम ath79_device_reset_clear(u32 mask);

#पूर्ण_अगर /* __ASM_MACH_ATH79_H */
