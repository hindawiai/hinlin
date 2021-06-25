<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम Microtune MT2131 "QAM/8VSB single chip tuner"
 *
 *  Copyright (c) 2006 Steven Toth <stoth@linuxtv.org>
 */

#अगर_अघोषित __MT2131_PRIV_H__
#घोषणा __MT2131_PRIV_H__

/* Regs */
#घोषणा MT2131_PWR              0x07
#घोषणा MT2131_UPC_1            0x0b
#घोषणा MT2131_AGC_RL           0x10
#घोषणा MT2131_MISC_2           0x15

/* frequency values in KHz */
#घोषणा MT2131_IF1              1220
#घोषणा MT2131_IF2              44000
#घोषणा MT2131_FREF             16000

काष्ठा mt2131_priv अणु
	काष्ठा mt2131_config *cfg;
	काष्ठा i2c_adapter   *i2c;

	u32 frequency;
पूर्ण;

#पूर्ण_अगर /* __MT2131_PRIV_H__ */
