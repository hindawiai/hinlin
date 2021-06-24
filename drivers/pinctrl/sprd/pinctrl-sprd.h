<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver header file क्रम pin controller driver
 * Copyright (C) 2017 Spपढ़ोtrum  - http://www.spपढ़ोtrum.com
 */

#अगर_अघोषित __PINCTRL_SPRD_H__
#घोषणा __PINCTRL_SPRD_H__

काष्ठा platक्रमm_device;

#घोषणा NUM_OFFSET	(20)
#घोषणा TYPE_OFFSET	(16)
#घोषणा BIT_OFFSET	(8)
#घोषणा WIDTH_OFFSET	(4)

#घोषणा SPRD_PIN_INFO(num, type, offset, width, reg)	\
		(((num) & 0xFFF) << NUM_OFFSET |	\
		 ((type) & 0xF) << TYPE_OFFSET |	\
		 ((offset) & 0xFF) << BIT_OFFSET |	\
		 ((width) & 0xF) << WIDTH_OFFSET |	\
		 ((reg) & 0xF))

#घोषणा SPRD_PINCTRL_PIN(pin)	SPRD_PINCTRL_PIN_DATA(pin, #pin)

#घोषणा SPRD_PINCTRL_PIN_DATA(a, b)				\
	अणु							\
		.name = b,					\
		.num = (((a) >> NUM_OFFSET) & 0xfff),		\
		.type = (((a) >> TYPE_OFFSET) & 0xf),		\
		.bit_offset = (((a) >> BIT_OFFSET) & 0xff),	\
		.bit_width = ((a) >> WIDTH_OFFSET & 0xf),	\
		.reg = ((a) & 0xf)				\
	पूर्ण

क्रमागत pin_type अणु
	GLOBAL_CTRL_PIN,
	COMMON_PIN,
	MISC_PIN,
पूर्ण;

काष्ठा sprd_pins_info अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक num;
	क्रमागत pin_type type;

	/* क्रम global control pins configuration */
	अचिन्हित दीर्घ bit_offset;
	अचिन्हित दीर्घ bit_width;
	अचिन्हित पूर्णांक reg;
पूर्ण;

पूर्णांक sprd_pinctrl_core_probe(काष्ठा platक्रमm_device *pdev,
			    काष्ठा sprd_pins_info *sprd_soc_pin_info,
			    पूर्णांक pins_cnt);
पूर्णांक sprd_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev);
व्योम sprd_pinctrl_shutकरोwn(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* __PINCTRL_SPRD_H__ */
