<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Bt8xx based DVB adapter driver
 *
 * Copyright (C) 2002,2003 Florian Schirmer <jolt@tuxbox.org>
 * Copyright (C) 2002 Peter Hettkamp <peter.hettkamp@htp-tel.de>
 * Copyright (C) 1999-2001 Ralph  Metzler & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 * Copyright (C) 1998,1999 Christian Theiss <mistert@rz.fh-augsburg.de>
 */

#अगर_अघोषित DVB_BT8XX_H
#घोषणा DVB_BT8XX_H

#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_net.h>
#समावेश "bttv.h"
#समावेश "mt352.h"
#समावेश "sp887x.h"
#समावेश "dst_common.h"
#समावेश "nxt6000.h"
#समावेश "cx24110.h"
#समावेश "or51211.h"
#समावेश "lgdt330x.h"
#समावेश "zl10353.h"
#समावेश "tuner-simple.h"

काष्ठा dvb_bt8xx_card अणु
	काष्ठा mutex lock;
	पूर्णांक nfeeds;
	अक्षर card_name[32];
	काष्ठा dvb_adapter dvb_adapter;
	काष्ठा bt878 *bt;
	अचिन्हित पूर्णांक bttv_nr;
	काष्ठा dvb_demux demux;
	काष्ठा dmxdev dmxdev;
	काष्ठा dmx_frontend fe_hw;
	काष्ठा dmx_frontend fe_mem;
	u32 gpio_mode;
	u32 op_sync_orin;
	u32 irq_err_ignore;
	काष्ठा i2c_adapter *i2c_adapter;
	काष्ठा dvb_net dvbnet;

	काष्ठा dvb_frontend* fe;
पूर्ण;

#पूर्ण_अगर /* DVB_BT8XX_H */
