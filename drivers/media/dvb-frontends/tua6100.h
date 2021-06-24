<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Infineon tua6100 PLL.
 *
 * (c) 2006 Andrew de Quincey
 *
 * Based on code found in budget-av.c, which has the following:
 * Compiled from various sources by Michael Hunold <michael@mihu.de>
 *
 * CI पूर्णांकerface support (c) 2004 Olivier Gournet <ogournet@anevia.com> &
 *                               Andrew de Quincey <adq_dvb@lidskialf.net>
 *
 * Copyright (C) 2002 Ralph Metzler <rjkm@metzlerbros.de>
 *
 * Copyright (C) 1999-2002 Ralph  Metzler
 *                       & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 */

#अगर_अघोषित __DVB_TUA6100_H__
#घोषणा __DVB_TUA6100_H__

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

#अगर IS_REACHABLE(CONFIG_DVB_TUA6100)
बाह्य काष्ठा dvb_frontend *tua6100_attach(काष्ठा dvb_frontend *fe, पूर्णांक addr, काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend* tua6100_attach(काष्ठा dvb_frontend *fe, पूर्णांक addr, काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर // CONFIG_DVB_TUA6100

#पूर्ण_अगर
