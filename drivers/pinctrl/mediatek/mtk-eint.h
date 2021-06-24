<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2014-2018 MediaTek Inc.
 *
 * Author: Maoguang Meng <maoguang.meng@mediatek.com>
 *	   Sean Wang <sean.wang@mediatek.com>
 *
 */
#अगर_अघोषित __MTK_EINT_H
#घोषणा __MTK_EINT_H

#समावेश <linux/irqकरोमुख्य.h>

काष्ठा mtk_eपूर्णांक_regs अणु
	अचिन्हित पूर्णांक	stat;
	अचिन्हित पूर्णांक	ack;
	अचिन्हित पूर्णांक	mask;
	अचिन्हित पूर्णांक	mask_set;
	अचिन्हित पूर्णांक	mask_clr;
	अचिन्हित पूर्णांक	sens;
	अचिन्हित पूर्णांक	sens_set;
	अचिन्हित पूर्णांक	sens_clr;
	अचिन्हित पूर्णांक	soft;
	अचिन्हित पूर्णांक	soft_set;
	अचिन्हित पूर्णांक	soft_clr;
	अचिन्हित पूर्णांक	pol;
	अचिन्हित पूर्णांक	pol_set;
	अचिन्हित पूर्णांक	pol_clr;
	अचिन्हित पूर्णांक	करोm_en;
	अचिन्हित पूर्णांक	dbnc_ctrl;
	अचिन्हित पूर्णांक	dbnc_set;
	अचिन्हित पूर्णांक	dbnc_clr;
पूर्ण;

काष्ठा mtk_eपूर्णांक_hw अणु
	u8		port_mask;
	u8		ports;
	अचिन्हित पूर्णांक	ap_num;
	अचिन्हित पूर्णांक	db_cnt;
पूर्ण;

काष्ठा mtk_eपूर्णांक;

काष्ठा mtk_eपूर्णांक_xt अणु
	पूर्णांक (*get_gpio_n)(व्योम *data, अचिन्हित दीर्घ eपूर्णांक_n,
			  अचिन्हित पूर्णांक *gpio_n,
			  काष्ठा gpio_chip **gpio_chip);
	पूर्णांक (*get_gpio_state)(व्योम *data, अचिन्हित दीर्घ eपूर्णांक_n);
	पूर्णांक (*set_gpio_as_eपूर्णांक)(व्योम *data, अचिन्हित दीर्घ eपूर्णांक_n);
पूर्ण;

काष्ठा mtk_eपूर्णांक अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक irq;

	पूर्णांक *dual_edge;
	u32 *wake_mask;
	u32 *cur_mask;

	/* Used to fit पूर्णांकo various EINT device */
	स्थिर काष्ठा mtk_eपूर्णांक_hw *hw;
	स्थिर काष्ठा mtk_eपूर्णांक_regs *regs;

	/* Used to fit पूर्णांकo various pinctrl device */
	व्योम *pctl;
	स्थिर काष्ठा mtk_eपूर्णांक_xt *gpio_xlate;
पूर्ण;

#अगर IS_ENABLED(CONFIG_EINT_MTK)
पूर्णांक mtk_eपूर्णांक_करो_init(काष्ठा mtk_eपूर्णांक *eपूर्णांक);
पूर्णांक mtk_eपूर्णांक_करो_suspend(काष्ठा mtk_eपूर्णांक *eपूर्णांक);
पूर्णांक mtk_eपूर्णांक_करो_resume(काष्ठा mtk_eपूर्णांक *eपूर्णांक);
पूर्णांक mtk_eपूर्णांक_set_debounce(काष्ठा mtk_eपूर्णांक *eपूर्णांक, अचिन्हित दीर्घ eपूर्णांक_n,
			  अचिन्हित पूर्णांक debounce);
पूर्णांक mtk_eपूर्णांक_find_irq(काष्ठा mtk_eपूर्णांक *eपूर्णांक, अचिन्हित दीर्घ eपूर्णांक_n);

#अन्यथा
अटल अंतरभूत पूर्णांक mtk_eपूर्णांक_करो_init(काष्ठा mtk_eपूर्णांक *eपूर्णांक)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक mtk_eपूर्णांक_करो_suspend(काष्ठा mtk_eपूर्णांक *eपूर्णांक)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक mtk_eपूर्णांक_करो_resume(काष्ठा mtk_eपूर्णांक *eपूर्णांक)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक mtk_eपूर्णांक_set_debounce(काष्ठा mtk_eपूर्णांक *eपूर्णांक, अचिन्हित दीर्घ eपूर्णांक_n,
			  अचिन्हित पूर्णांक debounce)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक mtk_eपूर्णांक_find_irq(काष्ठा mtk_eपूर्णांक *eपूर्णांक, अचिन्हित दीर्घ eपूर्णांक_n)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __MTK_EINT_H */
