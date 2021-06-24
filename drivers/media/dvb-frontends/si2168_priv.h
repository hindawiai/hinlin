<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Silicon Lअसल Si2168 DVB-T/T2/C demodulator driver
 *
 * Copyright (C) 2014 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित SI2168_PRIV_H
#घोषणा SI2168_PRIV_H

#समावेश "si2168.h"
#समावेश <media/dvb_frontend.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/kernel.h>

#घोषणा SI2168_A20_FIRMWARE "dvb-demod-si2168-a20-01.fw"
#घोषणा SI2168_A30_FIRMWARE "dvb-demod-si2168-a30-01.fw"
#घोषणा SI2168_B40_FIRMWARE "dvb-demod-si2168-b40-01.fw"
#घोषणा SI2168_D60_FIRMWARE "dvb-demod-si2168-d60-01.fw"
#घोषणा SI2168_B40_FIRMWARE_FALLBACK "dvb-demod-si2168-02.fw"

/* state काष्ठा */
काष्ठा si2168_dev अणु
	काष्ठा mutex i2c_mutex;
	काष्ठा i2c_mux_core *muxc;
	काष्ठा dvb_frontend fe;
	क्रमागत fe_delivery_प्रणाली delivery_प्रणाली;
	क्रमागत fe_status fe_status;
	#घोषणा SI2168_CHIP_ID_A20 ('A' << 24 | 68 << 16 | '2' << 8 | '0' << 0)
	#घोषणा SI2168_CHIP_ID_A30 ('A' << 24 | 68 << 16 | '3' << 8 | '0' << 0)
	#घोषणा SI2168_CHIP_ID_B40 ('B' << 24 | 68 << 16 | '4' << 8 | '0' << 0)
	#घोषणा SI2168_CHIP_ID_D60 ('D' << 24 | 68 << 16 | '6' << 8 | '0' << 0)
	अचिन्हित पूर्णांक chip_id;
	अचिन्हित पूर्णांक version;
	स्थिर अक्षर *firmware_name;
	u8 ts_mode;
	अचिन्हित पूर्णांक active:1;
	अचिन्हित पूर्णांक warm:1;
	अचिन्हित पूर्णांक ts_घड़ी_inv:1;
	अचिन्हित पूर्णांक ts_घड़ी_gapped:1;
	अचिन्हित पूर्णांक spectral_inversion:1;
पूर्ण;

/* firmware command काष्ठा */
#घोषणा SI2168_ARGLEN      30
काष्ठा si2168_cmd अणु
	u8 args[SI2168_ARGLEN];
	अचिन्हित wlen;
	अचिन्हित rlen;
पूर्ण;

#पूर्ण_अगर
