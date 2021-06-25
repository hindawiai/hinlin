<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2013 STMicroelectronics (R&D) Limited
 * Author: Stephen Gallimore <stephen.gallimore@st.com>
 */
#अगर_अघोषित __STI_RESET_SYSCFG_H
#घोषणा __STI_RESET_SYSCFG_H

#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

/**
 * Reset channel description क्रम a प्रणाली configuration रेजिस्टर based
 * reset controller.
 *
 * @compatible: Compatible string of the syscon regmap containing this
 *              channel's control and ack (status) bits.
 * @reset: Regmap field description of the channel's reset bit.
 * @ack: Regmap field description of the channel's acknowledge bit.
 */
काष्ठा syscfg_reset_channel_data अणु
	स्थिर अक्षर *compatible;
	काष्ठा reg_field reset;
	काष्ठा reg_field ack;
पूर्ण;

#घोषणा _SYSCFG_RST_CH(_c, _rr, _rb, _ar, _ab)		\
	अणु .compatible	= _c,				\
	  .reset	= REG_FIELD(_rr, _rb, _rb),	\
	  .ack		= REG_FIELD(_ar, _ab, _ab), पूर्ण

#घोषणा _SYSCFG_RST_CH_NO_ACK(_c, _rr, _rb)		\
	अणु .compatible	= _c,			\
	  .reset	= REG_FIELD(_rr, _rb, _rb), पूर्ण

/**
 * Description of a प्रणाली configuration रेजिस्टर based reset controller.
 *
 * @रुको_क्रम_ack: The controller will रुको क्रम reset निश्चित and de-निश्चित to
 *                be "ack'd" in a channel's ack field.
 * @active_low: Are the resets in this controller active low, i.e. clearing
 *              the reset bit माला_दो the hardware पूर्णांकo reset.
 * @nr_channels: The number of reset channels in this controller.
 * @channels: An array of reset channel descriptions.
 */
काष्ठा syscfg_reset_controller_data अणु
	bool रुको_क्रम_ack;
	bool active_low;
	पूर्णांक nr_channels;
	स्थिर काष्ठा syscfg_reset_channel_data *channels;
पूर्ण;

/**
 * syscfg_reset_probe(): platक्रमm device probe function used by syscfg
 *                       reset controller drivers. This रेजिस्टरs a reset
 *                       controller configured by the OF match data क्रम
 *                       the compatible device which should be of type
 *                       "struct syscfg_reset_controller_data".
 *
 * @pdev: platक्रमm device
 */
पूर्णांक syscfg_reset_probe(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* __STI_RESET_SYSCFG_H */
