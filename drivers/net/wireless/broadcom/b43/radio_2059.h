<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_RADIO_2059_H_
#घोषणा B43_RADIO_2059_H_

#समावेश <linux/types.h>

#समावेश "phy_ht.h"

#घोषणा R2059_C1			0x000
#घोषणा R2059_C2			0x400
#घोषणा R2059_C3			0x800
#घोषणा R2059_ALL			0xC00

#घोषणा R2059_RCAL_CONFIG			0x004
#घोषणा R2059_RFPLL_MASTER			0x011
#घोषणा R2059_RFPLL_MISC_EN			0x02b
#घोषणा R2059_RFPLL_MISC_CAL_RESETN		0x02e
#घोषणा R2059_XTAL_CONFIG2			0x0c0
#घोषणा R2059_RCCAL_START_R1_Q1_P1		0x13c
#घोषणा R2059_RCCAL_X1				0x13d
#घोषणा R2059_RCCAL_TRC0			0x13e
#घोषणा R2059_RCCAL_DONE_OSCCAP			0x140
#घोषणा R2059_RCAL_STATUS			0x145
#घोषणा R2059_RCCAL_MASTER			0x17f

/* Values क्रम various रेजिस्टरs uploaded on channel चयनing */
काष्ठा b43_phy_ht_channeltab_e_radio2059 अणु
	/* The channel frequency in MHz */
	u16 freq;
	/* Values क्रम radio रेजिस्टरs */
	u8 radio_syn16;
	u8 radio_syn17;
	u8 radio_syn22;
	u8 radio_syn25;
	u8 radio_syn27;
	u8 radio_syn28;
	u8 radio_syn29;
	u8 radio_syn2c;
	u8 radio_syn2d;
	u8 radio_syn37;
	u8 radio_syn41;
	u8 radio_syn43;
	u8 radio_syn47;
	u8 radio_rxtx4a;
	u8 radio_rxtx58;
	u8 radio_rxtx5a;
	u8 radio_rxtx6a;
	u8 radio_rxtx6d;
	u8 radio_rxtx6e;
	u8 radio_rxtx92;
	u8 radio_rxtx98;
	/* Values क्रम PHY रेजिस्टरs */
	काष्ठा b43_phy_ht_channeltab_e_phy phy_regs;
पूर्ण;

व्योम r2059_upload_inittअसल(काष्ठा b43_wldev *dev);

स्थिर काष्ठा b43_phy_ht_channeltab_e_radio2059
*b43_phy_ht_get_channeltab_e_r2059(काष्ठा b43_wldev *dev, u16 freq);

#पूर्ण_अगर /* B43_RADIO_2059_H_ */
