<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Fitiघातer FC0013 tuner driver
 *
 * Copyright (C) 2012 Hans-Frieder Vogt <hfvogt@gmx.net>
 */

#अगर_अघोषित _FC0013_PRIV_H_
#घोषणा _FC0013_PRIV_H_

#घोषणा LOG_PREFIX "fc0013"

#अघोषित err
#घोषणा err(f, arg...)  prपूर्णांकk(KERN_ERR     LOG_PREFIX": " f "\n" , ## arg)
#अघोषित info
#घोषणा info(f, arg...) prपूर्णांकk(KERN_INFO    LOG_PREFIX": " f "\n" , ## arg)
#अघोषित warn
#घोषणा warn(f, arg...) prपूर्णांकk(KERN_WARNING LOG_PREFIX": " f "\n" , ## arg)

काष्ठा fc0013_priv अणु
	काष्ठा i2c_adapter *i2c;
	u8 addr;
	u8 dual_master;
	u8 xtal_freq;

	u32 frequency;
	u32 bandwidth;
पूर्ण;

#पूर्ण_अगर
