<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: card.c
 * Purpose: Provide functions to setup NIC operation mode
 * Functions:
 *      vnt_set_rspinf - Set RSPINF
 *      vnt_update_अगरs - Update slotTime,SIFS,DIFS, and EIFS
 *      vnt_update_top_rates - Update BasicTopRate
 *      vnt_add_basic_rate - Add to BasicRateSet
 *      vnt_ofdm_min_rate - Check अगर any OFDM rate is in BasicRateSet
 *      vnt_get_tsf_offset - Calculate TSFOffset
 *      vnt_get_current_tsf - Read Current NIC TSF counter
 *      vnt_get_next_tbtt - Calculate Next Beacon TSF counter
 *      vnt_reset_next_tbtt - Set NIC Beacon समय
 *      vnt_update_next_tbtt - Sync. NIC Beacon समय
 *      vnt_radio_घातer_off - Turn Off NIC Radio Power
 *      vnt_radio_घातer_on - Turn On NIC Radio Power
 *
 * Revision History:
 *      06-10-2003 Bryan YC Fan:  Re-ग_लिखो codes to support VT3253 spec.
 *      08-26-2003 Kyle Hsu:      Modअगरy the definition type of dwIoBase.
 *      09-01-2003 Bryan YC Fan:  Add vnt_update_अगरs().
 *
 */

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश "device.h"
#समावेश "card.h"
#समावेश "baseband.h"
#समावेश "mac.h"
#समावेश "desc.h"
#समावेश "rf.h"
#समावेश "power.h"
#समावेश "key.h"
#समावेश "usbpipe.h"

/* स्थिर u16 cw_rxbcntsf_off[MAX_RATE] =
 *   अणु17, 34, 96, 192, 34, 23, 17, 11, 8, 5, 4, 3पूर्ण;
 */

अटल स्थिर u16 cw_rxbcntsf_off[MAX_RATE] = अणु
	192, 96, 34, 17, 34, 23, 17, 11, 8, 5, 4, 3
पूर्ण;

पूर्णांक vnt_set_channel(काष्ठा vnt_निजी *priv, u32 connection_channel)
अणु
	पूर्णांक ret;

	अगर (connection_channel > CB_MAX_CHANNEL || !connection_channel)
		वापस -EINVAL;

	/* clear NAV */
	vnt_mac_reg_bits_on(priv, MAC_REG_MACCR, MACCR_CLRNAV);

	/* Set Channel[7] = 0 to tell H/W channel is changing now. */
	vnt_mac_reg_bits_off(priv, MAC_REG_CHANNEL,
			     (BIT(7) | BIT(5) | BIT(4)));

	ret = vnt_control_out(priv, MESSAGE_TYPE_SELECT_CHANNEL,
			      connection_channel, 0, 0, शून्य);
	अगर (ret)
		वापस ret;

	वापस vnt_control_out_u8(priv, MESSAGE_REQUEST_MACREG, MAC_REG_CHANNEL,
				  (u8)(connection_channel | 0x80));
पूर्ण

अटल स्थिर u8 vnt_rspinf_b_लघु_table[] = अणु
	0x70, 0x00, 0x00, 0x00, 0x38, 0x00, 0x09, 0x00,
	0x15, 0x00, 0x0a, 0x00, 0x0b, 0x00, 0x0b, 0x80
पूर्ण;

अटल स्थिर u8 vnt_rspinf_b_दीर्घ_table[] = अणु
	0x70, 0x00, 0x00, 0x00, 0x38, 0x00, 0x01, 0x00,
	0x15, 0x00, 0x02, 0x00, 0x0b, 0x00, 0x03, 0x80
पूर्ण;

अटल स्थिर u8 vnt_rspinf_a_table[] = अणु
	0x9b, 0x18, 0x9f, 0x10, 0x9a, 0x0a, 0x9e, 0x08, 0x99,
	0x08, 0x9d, 0x04, 0x98, 0x04, 0x9c, 0x04, 0x9c, 0x04
पूर्ण;

अटल स्थिर u8 vnt_rspinf_gb_table[] = अणु
	0x8b, 0x1e, 0x8f, 0x16, 0x8a, 0x12, 0x8e, 0x0e, 0x89,
	0x0e, 0x8d, 0x0a, 0x88, 0x0a, 0x8c, 0x0a, 0x8c, 0x0a
पूर्ण;

पूर्णांक vnt_set_rspinf(काष्ठा vnt_निजी *priv, u8 bb_type)
अणु
	स्थिर u8 *data;
	u16 len;
	पूर्णांक ret;

	अगर (priv->preamble_type) अणु
		data = vnt_rspinf_b_लघु_table;
		len = ARRAY_SIZE(vnt_rspinf_b_लघु_table);
	पूर्ण अन्यथा अणु
		data = vnt_rspinf_b_दीर्घ_table;
		len = ARRAY_SIZE(vnt_rspinf_b_दीर्घ_table);
	पूर्ण

	 /* RSPINF_b_1 to RSPINF_b_11 */
	ret = vnt_control_out(priv, MESSAGE_TYPE_WRITE, MAC_REG_RSPINF_B_1,
			      MESSAGE_REQUEST_MACREG, len, data);
	अगर (ret)
		वापस ret;

	अगर (bb_type == BB_TYPE_11A) अणु
		data = vnt_rspinf_a_table;
		len = ARRAY_SIZE(vnt_rspinf_a_table);
	पूर्ण अन्यथा अणु
		data = vnt_rspinf_gb_table;
		len = ARRAY_SIZE(vnt_rspinf_gb_table);
	पूर्ण

	/* RSPINF_a_6 to RSPINF_a_72 */
	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE, MAC_REG_RSPINF_A_6,
			       MESSAGE_REQUEST_MACREG, len, data);
पूर्ण

पूर्णांक vnt_update_अगरs(काष्ठा vnt_निजी *priv)
अणु
	u8 max_min = 0;
	u8 data[4];
	पूर्णांक ret;

	अगर (priv->packet_type == PK_TYPE_11A) अणु
		priv->slot = C_SLOT_SHORT;
		priv->sअगरs = C_SIFS_A;
		priv->dअगरs = C_SIFS_A + 2 * C_SLOT_SHORT;
		max_min = 4;
	पूर्ण अन्यथा अणु
		priv->sअगरs = C_SIFS_BG;

		अगर (priv->लघु_slot_समय) अणु
			priv->slot = C_SLOT_SHORT;
			max_min = 4;
		पूर्ण अन्यथा अणु
			priv->slot = C_SLOT_LONG;
			max_min = 5;
		पूर्ण

		priv->dअगरs = C_SIFS_BG + 2 * priv->slot;
	पूर्ण

	priv->eअगरs = C_EIFS;

	data[0] = (u8)priv->sअगरs;
	data[1] = (u8)priv->dअगरs;
	data[2] = (u8)priv->eअगरs;
	data[3] = (u8)priv->slot;

	ret = vnt_control_out(priv, MESSAGE_TYPE_WRITE, MAC_REG_SIFS,
			      MESSAGE_REQUEST_MACREG, 4, &data[0]);
	अगर (ret)
		वापस ret;

	max_min |= 0xa0;

	वापस vnt_control_out(priv, MESSAGE_TYPE_WRITE, MAC_REG_CWMAXMIN0,
			       MESSAGE_REQUEST_MACREG, 1, &max_min);
पूर्ण

व्योम vnt_update_top_rates(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक pos;

	pos = fls(priv->basic_rates & GENMASK(RATE_54M, RATE_6M));
	priv->top_ofdm_basic_rate = pos ? (pos - 1) : RATE_24M;

	pos = fls(priv->basic_rates & GENMASK(RATE_11M, RATE_1M));
	priv->top_cck_basic_rate = pos ? (pos - 1) : RATE_1M;
पूर्ण

bool vnt_ofdm_min_rate(काष्ठा vnt_निजी *priv)
अणु
	वापस priv->basic_rates & GENMASK(RATE_54M, RATE_6M) ? true : false;
पूर्ण

u8 vnt_get_pkt_type(काष्ठा vnt_निजी *priv)
अणु
	अगर (priv->bb_type == BB_TYPE_11A || priv->bb_type == BB_TYPE_11B)
		वापस (u8)priv->bb_type;
	अन्यथा अगर (vnt_ofdm_min_rate(priv))
		वापस PK_TYPE_11GA;
	वापस PK_TYPE_11GB;
पूर्ण

/*
 * Description: Calculate TSF offset of two TSF input
 *              Get TSF Offset from RxBCN's TSF and local TSF
 *
 * Parameters:
 *  In:
 *      rx_rate	- rx rate.
 *      tsf1	- Rx BCN's TSF
 *      tsf2	- Local TSF
 *  Out:
 *      none
 *
 * Return Value: TSF Offset value
 *
 */
u64 vnt_get_tsf_offset(u8 rx_rate, u64 tsf1, u64 tsf2)
अणु
	वापस tsf1 - tsf2 - (u64)cw_rxbcntsf_off[rx_rate % MAX_RATE];
पूर्ण

पूर्णांक vnt_adjust_tsf(काष्ठा vnt_निजी *priv, u8 rx_rate,
		   u64 समय_stamp, u64 local_tsf)
अणु
	u64 tsf_offset = 0;
	u8 data[8];

	tsf_offset = vnt_get_tsf_offset(rx_rate, समय_stamp, local_tsf);

	data[0] = (u8)tsf_offset;
	data[1] = (u8)(tsf_offset >> 8);
	data[2] = (u8)(tsf_offset >> 16);
	data[3] = (u8)(tsf_offset >> 24);
	data[4] = (u8)(tsf_offset >> 32);
	data[5] = (u8)(tsf_offset >> 40);
	data[6] = (u8)(tsf_offset >> 48);
	data[7] = (u8)(tsf_offset >> 56);

	वापस vnt_control_out(priv, MESSAGE_TYPE_SET_TSFTBTT,
			       MESSAGE_REQUEST_TSF, 0, 8, data);
पूर्ण

/*
 * Description: Read NIC TSF counter
 *              Get local TSF counter
 *
 * Parameters:
 *  In:
 *	priv		- The adapter to be पढ़ो
 *  Out:
 *	current_tsf	- Current TSF counter
 *
 * Return Value: true अगर success; otherwise false
 *
 */
bool vnt_get_current_tsf(काष्ठा vnt_निजी *priv, u64 *current_tsf)
अणु
	*current_tsf = priv->current_tsf;

	वापस true;
पूर्ण

/*
 * Description: Clear NIC TSF counter
 *              Clear local TSF counter
 *
 * Parameters:
 *  In:
 *      priv	- The adapter to be पढ़ो
 *
 * Return Value: true अगर success; otherwise false
 *
 */
bool vnt_clear_current_tsf(काष्ठा vnt_निजी *priv)
अणु
	vnt_mac_reg_bits_on(priv, MAC_REG_TFTCTL, TFTCTL_TSFCNTRST);

	priv->current_tsf = 0;

	वापस true;
पूर्ण

/*
 * Description: Read NIC TSF counter
 *              Get NEXTTBTT from adjusted TSF and Beacon Interval
 *
 * Parameters:
 *  In:
 *      tsf		- Current TSF counter
 *      beacon_पूर्णांकerval - Beacon Interval
 *  Out:
 *      tsf		- Current TSF counter
 *
 * Return Value: TSF value of next Beacon
 *
 */
u64 vnt_get_next_tbtt(u64 tsf, u16 beacon_पूर्णांकerval)
अणु
	u32 beacon_पूर्णांक;

	beacon_पूर्णांक = beacon_पूर्णांकerval * 1024;

	/* Next TBTT =
	 *	((local_current_TSF / beacon_पूर्णांकerval) + 1) * beacon_पूर्णांकerval
	 */
	अगर (beacon_पूर्णांक) अणु
		करो_भाग(tsf, beacon_पूर्णांक);
		tsf += 1;
		tsf *= beacon_पूर्णांक;
	पूर्ण

	वापस tsf;
पूर्ण

पूर्णांक vnt_reset_next_tbtt(काष्ठा vnt_निजी *priv, u16 beacon_पूर्णांकerval)
अणु
	u64 next_tbtt = 0;
	u8 data[8];

	vnt_clear_current_tsf(priv);

	next_tbtt = vnt_get_next_tbtt(next_tbtt, beacon_पूर्णांकerval);

	data[0] = (u8)next_tbtt;
	data[1] = (u8)(next_tbtt >> 8);
	data[2] = (u8)(next_tbtt >> 16);
	data[3] = (u8)(next_tbtt >> 24);
	data[4] = (u8)(next_tbtt >> 32);
	data[5] = (u8)(next_tbtt >> 40);
	data[6] = (u8)(next_tbtt >> 48);
	data[7] = (u8)(next_tbtt >> 56);

	वापस vnt_control_out(priv, MESSAGE_TYPE_SET_TSFTBTT,
			       MESSAGE_REQUEST_TBTT, 0, 8, data);
पूर्ण

पूर्णांक vnt_update_next_tbtt(काष्ठा vnt_निजी *priv, u64 tsf,
			 u16 beacon_पूर्णांकerval)
अणु
	u8 data[8];
	पूर्णांक ret;

	tsf = vnt_get_next_tbtt(tsf, beacon_पूर्णांकerval);

	data[0] = (u8)tsf;
	data[1] = (u8)(tsf >> 8);
	data[2] = (u8)(tsf >> 16);
	data[3] = (u8)(tsf >> 24);
	data[4] = (u8)(tsf >> 32);
	data[5] = (u8)(tsf >> 40);
	data[6] = (u8)(tsf >> 48);
	data[7] = (u8)(tsf >> 56);

	ret = vnt_control_out(priv, MESSAGE_TYPE_SET_TSFTBTT,
			      MESSAGE_REQUEST_TBTT, 0, 8, data);
	अगर (ret)
		वापस ret;

	dev_dbg(&priv->usb->dev, "%s TBTT: %8llx\n", __func__, tsf);
	वापस 0;
पूर्ण

/*
 * Description: Turn off Radio घातer
 *
 * Parameters:
 *  In:
 *      priv         - The adapter to be turned off
 *  Out:
 *      none
 *
 * Return Value: true अगर success; otherwise false
 *
 */
पूर्णांक vnt_radio_घातer_off(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक ret = 0;

	चयन (priv->rf_type) अणु
	हाल RF_AL2230:
	हाल RF_AL2230S:
	हाल RF_AIROHA7230:
	हाल RF_VT3226:
	हाल RF_VT3226D0:
	हाल RF_VT3342A0:
		ret = vnt_mac_reg_bits_off(priv, MAC_REG_SOFTPWRCTL,
					   (SOFTPWRCTL_SWPE2 |
					    SOFTPWRCTL_SWPE3));
		अवरोध;
	पूर्ण

	अगर (ret)
		जाओ end;

	ret = vnt_mac_reg_bits_off(priv, MAC_REG_HOSTCR, HOSTCR_RXON);
	अगर (ret)
		जाओ end;

	ret = vnt_set_deep_sleep(priv);
	अगर (ret)
		जाओ end;

	ret = vnt_mac_reg_bits_on(priv, MAC_REG_GPIOCTL1, GPIO3_INTMD);

end:
	वापस ret;
पूर्ण

/*
 * Description: Turn on Radio घातer
 *
 * Parameters:
 *  In:
 *      priv         - The adapter to be turned on
 *  Out:
 *      none
 *
 * Return Value: true अगर success; otherwise false
 *
 */
पूर्णांक vnt_radio_घातer_on(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक ret = 0;

	ret = vnt_निकास_deep_sleep(priv);
	अगर (ret)
		वापस ret;

	ret = vnt_mac_reg_bits_on(priv, MAC_REG_HOSTCR, HOSTCR_RXON);
	अगर (ret)
		वापस ret;

	चयन (priv->rf_type) अणु
	हाल RF_AL2230:
	हाल RF_AL2230S:
	हाल RF_AIROHA7230:
	हाल RF_VT3226:
	हाल RF_VT3226D0:
	हाल RF_VT3342A0:
		ret = vnt_mac_reg_bits_on(priv, MAC_REG_SOFTPWRCTL,
					  (SOFTPWRCTL_SWPE2 |
					   SOFTPWRCTL_SWPE3));
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस vnt_mac_reg_bits_off(priv, MAC_REG_GPIOCTL1, GPIO3_INTMD);
पूर्ण

पूर्णांक vnt_set_bss_mode(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर type = priv->bb_type;
	अचिन्हित अक्षर data = 0;
	अचिन्हित अक्षर bb_vga_0 = 0x1c;
	अचिन्हित अक्षर bb_vga_2_3 = 0x00;

	अगर (priv->rf_type == RF_AIROHA7230 && priv->bb_type == BB_TYPE_11A)
		type = BB_TYPE_11G;

	ret = vnt_mac_set_bb_type(priv, type);
	अगर (ret)
		वापस ret;

	priv->packet_type = vnt_get_pkt_type(priv);

	अगर (priv->bb_type == BB_TYPE_11A) अणु
		data = 0x03;
		bb_vga_0 = 0x20;
		bb_vga_2_3 = 0x10;
	पूर्ण अन्यथा अगर (priv->bb_type == BB_TYPE_11B) अणु
		data = 0x02;
	पूर्ण अन्यथा अगर (priv->bb_type == BB_TYPE_11G) अणु
		data = 0x08;
	पूर्ण

	अगर (data) अणु
		ret = vnt_control_out_u8(priv, MESSAGE_REQUEST_BBREG,
					 0x88, data);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = vnt_update_अगरs(priv);
	अगर (ret)
		वापस ret;

	ret = vnt_set_rspinf(priv, priv->bb_type);
	अगर (ret)
		वापस ret;

	अगर (priv->rf_type == RF_AIROHA7230) अणु
		priv->bb_vga[0] = bb_vga_0;

		ret = vnt_control_out_u8(priv, MESSAGE_REQUEST_BBREG,
					 0xe7, priv->bb_vga[0]);
		अगर (ret)
			वापस ret;
	पूर्ण

	priv->bb_vga[2] = bb_vga_2_3;
	priv->bb_vga[3] = bb_vga_2_3;

	वापस vnt_set_vga_gain_offset(priv, priv->bb_vga[0]);
पूर्ण
