<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Silicon Lअसल Si2146/2147/2148/2157/2158 silicon tuner driver
 *
 * Copyright (C) 2014 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित SI2157_PRIV_H
#घोषणा SI2157_PRIV_H

#समावेश <linux/firmware.h>
#समावेश <media/v4l2-mc.h>
#समावेश "si2157.h"

क्रमागत si2157_pads अणु
	SI2157_PAD_RF_INPUT,
	SI2157_PAD_VID_OUT,
	SI2157_PAD_AUD_OUT,
	SI2157_NUM_PADS
पूर्ण;

/* state काष्ठा */
काष्ठा si2157_dev अणु
	काष्ठा mutex i2c_mutex;
	काष्ठा dvb_frontend *fe;
	अचिन्हित पूर्णांक active:1;
	अचिन्हित पूर्णांक inversion:1;
	अचिन्हित पूर्णांक करोnt_load_firmware:1;
	u8 chiptype;
	u8 अगर_port;
	u32 अगर_frequency;
	u32 bandwidth;
	u32 frequency;
	काष्ठा delayed_work stat_work;

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_device	*mdev;
	काष्ठा media_entity	ent;
	काष्ठा media_pad	pad[SI2157_NUM_PADS];
#पूर्ण_अगर

पूर्ण;

#घोषणा SI2157_CHIPTYPE_SI2157 0
#घोषणा SI2157_CHIPTYPE_SI2146 1
#घोषणा SI2157_CHIPTYPE_SI2141 2
#घोषणा SI2157_CHIPTYPE_SI2177 3

/* firmware command काष्ठा */
#घोषणा SI2157_ARGLEN      30
काष्ठा si2157_cmd अणु
	u8 args[SI2157_ARGLEN];
	अचिन्हित wlen;
	अचिन्हित rlen;
पूर्ण;

#घोषणा SI2158_A20_FIRMWARE "dvb-tuner-si2158-a20-01.fw"
#घोषणा SI2141_A10_FIRMWARE "dvb-tuner-si2141-a10-01.fw"
#घोषणा SI2157_A30_FIRMWARE "dvb-tuner-si2157-a30-01.fw"
#पूर्ण_अगर
