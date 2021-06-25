<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015, 2017-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __QCOM_GDSC_H__
#घोषणा __QCOM_GDSC_H__

#समावेश <linux/err.h>
#समावेश <linux/pm_करोमुख्य.h>

काष्ठा regmap;
काष्ठा regulator;
काष्ठा reset_controller_dev;

/**
 * काष्ठा gdsc - Globally Distributed Switch Controller
 * @pd: generic घातer करोमुख्य
 * @regmap: regmap क्रम MMIO accesses
 * @gdscr: gsdc control रेजिस्टर
 * @gds_hw_ctrl: gds_hw_ctrl रेजिस्टर
 * @cxcs: offsets of branch रेजिस्टरs to toggle mem/periph bits in
 * @cxc_count: number of @cxcs
 * @pwrsts: Possible घातerकरोमुख्य घातer states
 * @resets: ids of resets associated with this gdsc
 * @reset_count: number of @resets
 * @rcdev: reset controller
 */
काष्ठा gdsc अणु
	काष्ठा generic_pm_करोमुख्य	pd;
	काष्ठा generic_pm_करोमुख्य	*parent;
	काष्ठा regmap			*regmap;
	अचिन्हित पूर्णांक			gdscr;
	अचिन्हित पूर्णांक			gds_hw_ctrl;
	अचिन्हित पूर्णांक			clamp_io_ctrl;
	अचिन्हित पूर्णांक			*cxcs;
	अचिन्हित पूर्णांक			cxc_count;
	स्थिर u8			pwrsts;
/* Powerकरोमुख्य allowable state bitfields */
#घोषणा PWRSTS_OFF		BIT(0)
#घोषणा PWRSTS_RET		BIT(1)
#घोषणा PWRSTS_ON		BIT(2)
#घोषणा PWRSTS_OFF_ON		(PWRSTS_OFF | PWRSTS_ON)
#घोषणा PWRSTS_RET_ON		(PWRSTS_RET | PWRSTS_ON)
	स्थिर u16			flags;
#घोषणा VOTABLE		BIT(0)
#घोषणा CLAMP_IO	BIT(1)
#घोषणा HW_CTRL		BIT(2)
#घोषणा SW_RESET	BIT(3)
#घोषणा AON_RESET	BIT(4)
#घोषणा POLL_CFG_GDSCR	BIT(5)
#घोषणा ALWAYS_ON	BIT(6)
#घोषणा RETAIN_FF_ENABLE	BIT(7)
#घोषणा NO_RET_PERIPH	BIT(8)
	काष्ठा reset_controller_dev	*rcdev;
	अचिन्हित पूर्णांक			*resets;
	अचिन्हित पूर्णांक			reset_count;

	स्थिर अक्षर 			*supply;
	काष्ठा regulator		*rsupply;
पूर्ण;

काष्ठा gdsc_desc अणु
	काष्ठा device *dev;
	काष्ठा gdsc **scs;
	माप_प्रकार num;
पूर्ण;

#अगर_घोषित CONFIG_QCOM_GDSC
पूर्णांक gdsc_रेजिस्टर(काष्ठा gdsc_desc *desc, काष्ठा reset_controller_dev *,
		  काष्ठा regmap *);
व्योम gdsc_unरेजिस्टर(काष्ठा gdsc_desc *desc);
पूर्णांक gdsc_gx_करो_nothing_enable(काष्ठा generic_pm_करोमुख्य *करोमुख्य);
#अन्यथा
अटल अंतरभूत पूर्णांक gdsc_रेजिस्टर(काष्ठा gdsc_desc *desc,
				काष्ठा reset_controller_dev *rcdev,
				काष्ठा regmap *r)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम gdsc_unरेजिस्टर(काष्ठा gdsc_desc *desc) अणुपूर्ण;
#पूर्ण_अगर /* CONFIG_QCOM_GDSC */
#पूर्ण_अगर /* __QCOM_GDSC_H__ */
