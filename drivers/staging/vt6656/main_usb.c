<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: मुख्य_usb.c
 *
 * Purpose: driver entry क्रम initial, खोलो, बंद, tx and rx.
 *
 * Author: Lynकरोn Chen
 *
 * Date: Dec 8, 2005
 *
 * Functions:
 *
 *   vt6656_probe - module initial (insmod) driver entry
 *   vnt_मुक्त_tx_bufs - मुक्त tx buffer function
 *   vnt_init_रेजिस्टरs- initial MAC & BBP & RF पूर्णांकernal रेजिस्टरs.
 *
 * Revision History:
 */
#अघोषित __NO_VERSION__

#समावेश <linux/bits.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/file.h>
#समावेश <linux/kernel.h>
#समावेश "device.h"
#समावेश "card.h"
#समावेश "baseband.h"
#समावेश "mac.h"
#समावेश "power.h"
#समावेश "wcmd.h"
#समावेश "rxtx.h"
#समावेश "rf.h"
#समावेश "usbpipe.h"
#समावेश "channel.h"

/*
 * define module options
 */

/* version inक्रमmation */
#घोषणा DRIVER_AUTHOR \
	"VIA Networking Technologies, Inc., <lyndonchen@vntek.com.tw>"
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DEVICE_FULL_DRV_NAM);

#घोषणा RX_DESC_DEF0 64
अटल पूर्णांक vnt_rx_buffers = RX_DESC_DEF0;
module_param_named(rx_buffers, vnt_rx_buffers, पूर्णांक, 0644);
MODULE_PARM_DESC(rx_buffers, "Number of receive usb rx buffers");

#घोषणा TX_DESC_DEF0 64
अटल पूर्णांक vnt_tx_buffers = TX_DESC_DEF0;
module_param_named(tx_buffers, vnt_tx_buffers, पूर्णांक, 0644);
MODULE_PARM_DESC(tx_buffers, "Number of receive usb tx buffers");

#घोषणा RTS_THRESH_DEF     2347
#घोषणा FRAG_THRESH_DEF     2346

/* BasebandType[] baseband type selected
 * 0: indicate 802.11a type
 * 1: indicate 802.11b type
 * 2: indicate 802.11g type
 */

#घोषणा BBP_TYPE_DEF     2

/*
 * Static vars definitions
 */

अटल स्थिर काष्ठा usb_device_id vt6656_table[] = अणु
	अणुUSB_DEVICE(VNT_USB_VENDOR_ID, VNT_USB_PRODUCT_ID)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम vnt_set_options(काष्ठा vnt_निजी *priv)
अणु
	/* Set number of TX buffers */
	अगर (vnt_tx_buffers < CB_MIN_TX_DESC || vnt_tx_buffers > CB_MAX_TX_DESC)
		priv->num_tx_context = TX_DESC_DEF0;
	अन्यथा
		priv->num_tx_context = vnt_tx_buffers;

	/* Set number of RX buffers */
	अगर (vnt_rx_buffers < CB_MIN_RX_DESC || vnt_rx_buffers > CB_MAX_RX_DESC)
		priv->num_rcb = RX_DESC_DEF0;
	अन्यथा
		priv->num_rcb = vnt_rx_buffers;

	priv->op_mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->bb_type = BBP_TYPE_DEF;
	priv->packet_type = priv->bb_type;
	priv->preamble_type = PREAMBLE_LONG;
	priv->exist_sw_net_addr = false;
पूर्ण

अटल पूर्णांक vnt_करोwnload_firmware(काष्ठा vnt_निजी *priv)
अणु
	काष्ठा device *dev = &priv->usb->dev;
	स्थिर काष्ठा firmware *fw;
	u16 length;
	पूर्णांक ii;
	पूर्णांक ret = 0;

	dev_dbg(dev, "---->Download firmware\n");

	ret = request_firmware(&fw, FIRMWARE_NAME, dev);
	अगर (ret) अणु
		dev_err(dev, "firmware file %s request failed (%d)\n",
			FIRMWARE_NAME, ret);
		जाओ end;
	पूर्ण

	क्रम (ii = 0; ii < fw->size; ii += FIRMWARE_CHUNK_SIZE) अणु
		length = min_t(पूर्णांक, fw->size - ii, FIRMWARE_CHUNK_SIZE);

		ret = vnt_control_out(priv, 0, 0x1200 + ii, 0x0000, length,
				      fw->data + ii);
		अगर (ret)
			जाओ मुक्त_fw;

		dev_dbg(dev, "Download firmware...%d %zu\n", ii, fw->size);
	पूर्ण

मुक्त_fw:
	release_firmware(fw);
end:
	वापस ret;
पूर्ण

अटल पूर्णांक vnt_firmware_branch_to_sram(काष्ठा vnt_निजी *priv)
अणु
	dev_dbg(&priv->usb->dev, "---->Branch to Sram\n");

	वापस vnt_control_out(priv, 1, 0x1200, 0x0000, 0, शून्य);
पूर्ण

अटल पूर्णांक vnt_check_firmware_version(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक ret = 0;

	ret = vnt_control_in(priv, MESSAGE_TYPE_READ, 0,
			     MESSAGE_REQUEST_VERSION, 2,
			     (u8 *)&priv->firmware_version);
	अगर (ret) अणु
		dev_dbg(&priv->usb->dev,
			"Could not get firmware version: %d.\n", ret);
		जाओ end;
	पूर्ण

	dev_dbg(&priv->usb->dev, "Firmware Version [%04x]\n",
		priv->firmware_version);

	अगर (priv->firmware_version == 0xFFFF) अणु
		dev_dbg(&priv->usb->dev, "In Loader.\n");
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	अगर (priv->firmware_version < FIRMWARE_VERSION) अणु
		/* branch to loader क्रम करोwnload new firmware */
		ret = vnt_firmware_branch_to_sram(priv);
		अगर (ret) अणु
			dev_dbg(&priv->usb->dev,
				"Could not branch to SRAM: %d.\n", ret);
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
	पूर्ण

end:
	वापस ret;
पूर्ण

/*
 * initialization of MAC & BBP रेजिस्टरs
 */
अटल पूर्णांक vnt_init_रेजिस्टरs(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक ret;
	काष्ठा vnt_cmd_card_init *init_cmd = &priv->init_command;
	काष्ठा vnt_rsp_card_init *init_rsp = &priv->init_response;
	u8 antenna;
	पूर्णांक ii;
	u8 पंचांगp;
	u8 calib_tx_iq = 0, calib_tx_dc = 0, calib_rx_iq = 0;

	dev_dbg(&priv->usb->dev, "---->INIbInitAdapter. [%d][%d]\n",
		DEVICE_INIT_COLD, priv->packet_type);

	ret = vnt_check_firmware_version(priv);
	अगर (ret) अणु
		ret = vnt_करोwnload_firmware(priv);
		अगर (ret) अणु
			dev_dbg(&priv->usb->dev,
				"Could not download firmware: %d.\n", ret);
			जाओ end;
		पूर्ण

		ret = vnt_firmware_branch_to_sram(priv);
		अगर (ret) अणु
			dev_dbg(&priv->usb->dev,
				"Could not branch to SRAM: %d.\n", ret);
			जाओ end;
		पूर्ण
	पूर्ण

	ret = vnt_vt3184_init(priv);
	अगर (ret) अणु
		dev_dbg(&priv->usb->dev, "vnt_vt3184_init fail\n");
		जाओ end;
	पूर्ण

	init_cmd->init_class = DEVICE_INIT_COLD;
	init_cmd->exist_sw_net_addr = priv->exist_sw_net_addr;
	क्रम (ii = 0; ii < ARRAY_SIZE(init_cmd->sw_net_addr); ii++)
		init_cmd->sw_net_addr[ii] = priv->current_net_addr[ii];
	init_cmd->लघु_retry_limit = priv->hw->wiphy->retry_लघु;
	init_cmd->दीर्घ_retry_limit = priv->hw->wiphy->retry_दीर्घ;

	/* issue card_init command to device */
	ret = vnt_control_out(priv, MESSAGE_TYPE_CARDINIT, 0, 0,
			      माप(काष्ठा vnt_cmd_card_init),
			      (u8 *)init_cmd);
	अगर (ret) अणु
		dev_dbg(&priv->usb->dev, "Issue Card init fail\n");
		जाओ end;
	पूर्ण

	ret = vnt_control_in(priv, MESSAGE_TYPE_INIT_RSP, 0, 0,
			     माप(काष्ठा vnt_rsp_card_init),
			     (u8 *)init_rsp);
	अगर (ret) अणु
		dev_dbg(&priv->usb->dev, "Cardinit request in status fail!\n");
		जाओ end;
	पूर्ण

	/* local ID क्रम AES functions */
	ret = vnt_control_in(priv, MESSAGE_TYPE_READ, MAC_REG_LOCALID,
			     MESSAGE_REQUEST_MACREG, 1, &priv->local_id);
	अगर (ret)
		जाओ end;

	/* करो MACbSoftwareReset in MACvInitialize */

	priv->top_ofdm_basic_rate = RATE_24M;
	priv->top_cck_basic_rate = RATE_1M;

	/* target to IF pin जबतक programming to RF chip */
	priv->घातer = 0xFF;

	priv->cck_pwr = priv->eeprom[EEP_OFS_PWR_CCK];
	priv->ofdm_pwr_g = priv->eeprom[EEP_OFS_PWR_OFDMG];
	/* load घातer table */
	क्रम (ii = 0; ii < ARRAY_SIZE(priv->cck_pwr_tbl); ii++) अणु
		priv->cck_pwr_tbl[ii] =
			priv->eeprom[ii + EEP_OFS_CCK_PWR_TBL];
		अगर (priv->cck_pwr_tbl[ii] == 0)
			priv->cck_pwr_tbl[ii] = priv->cck_pwr;

		priv->ofdm_pwr_tbl[ii] =
				priv->eeprom[ii + EEP_OFS_OFDM_PWR_TBL];
		अगर (priv->ofdm_pwr_tbl[ii] == 0)
			priv->ofdm_pwr_tbl[ii] = priv->ofdm_pwr_g;
	पूर्ण

	/*
	 * original zonetype is USA, but custom zonetype is Europe,
	 * then need to recover 12, 13, 14 channels with 11 channel
	 */
	क्रम (ii = 11; ii < ARRAY_SIZE(priv->cck_pwr_tbl); ii++) अणु
		priv->cck_pwr_tbl[ii] = priv->cck_pwr_tbl[10];
		priv->ofdm_pwr_tbl[ii] = priv->ofdm_pwr_tbl[10];
	पूर्ण

	priv->ofdm_pwr_a = 0x34; /* same as RFbMA2829SelectChannel */

	/* load OFDM A घातer table */
	क्रम (ii = 0; ii < CB_MAX_CHANNEL_5G; ii++) अणु
		priv->ofdm_a_pwr_tbl[ii] =
			priv->eeprom[ii + EEP_OFS_OFDMA_PWR_TBL];

		अगर (priv->ofdm_a_pwr_tbl[ii] == 0)
			priv->ofdm_a_pwr_tbl[ii] = priv->ofdm_pwr_a;
	पूर्ण

	antenna = priv->eeprom[EEP_OFS_ANTENNA];

	अगर (antenna & EEP_ANTINV)
		priv->tx_rx_ant_inv = true;
	अन्यथा
		priv->tx_rx_ant_inv = false;

	antenna &= (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN);

	अगर (antenna == 0) /* अगर not set शेष is both */
		antenna = (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN);

	अगर (antenna == (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN)) अणु
		priv->tx_antenna_mode = ANT_B;
		priv->rx_antenna_sel = 1;

		अगर (priv->tx_rx_ant_inv)
			priv->rx_antenna_mode = ANT_A;
		अन्यथा
			priv->rx_antenna_mode = ANT_B;
	पूर्ण अन्यथा  अणु
		priv->rx_antenna_sel = 0;

		अगर (antenna & EEP_ANTENNA_AUX) अणु
			priv->tx_antenna_mode = ANT_A;

			अगर (priv->tx_rx_ant_inv)
				priv->rx_antenna_mode = ANT_B;
			अन्यथा
				priv->rx_antenna_mode = ANT_A;
		पूर्ण अन्यथा अणु
			priv->tx_antenna_mode = ANT_B;

			अगर (priv->tx_rx_ant_inv)
				priv->rx_antenna_mode = ANT_A;
			अन्यथा
				priv->rx_antenna_mode = ANT_B;
		पूर्ण
	पूर्ण

	/* Set initial antenna mode */
	ret = vnt_set_antenna_mode(priv, priv->rx_antenna_mode);
	अगर (ret)
		जाओ end;

	/* शेष Auto Mode */
	priv->bb_type = BB_TYPE_11G;

	/* get RFType */
	priv->rf_type = init_rsp->rf_type;

	/* load vt3266 calibration parameters in EEPROM */
	अगर (priv->rf_type == RF_VT3226D0) अणु
		अगर ((priv->eeprom[EEP_OFS_MAJOR_VER] == 0x1) &&
		    (priv->eeprom[EEP_OFS_MINOR_VER] >= 0x4)) अणु
			calib_tx_iq = priv->eeprom[EEP_OFS_CALIB_TX_IQ];
			calib_tx_dc = priv->eeprom[EEP_OFS_CALIB_TX_DC];
			calib_rx_iq = priv->eeprom[EEP_OFS_CALIB_RX_IQ];
			अगर (calib_tx_iq || calib_tx_dc || calib_rx_iq) अणु
				/* CR255, enable TX/RX IQ and
				 * DC compensation mode
				 */
				ret = vnt_control_out_u8(priv,
							 MESSAGE_REQUEST_BBREG,
							 0xff, 0x03);
				अगर (ret)
					जाओ end;

				/* CR251, TX I/Q Imbalance Calibration */
				ret = vnt_control_out_u8(priv,
							 MESSAGE_REQUEST_BBREG,
							 0xfb, calib_tx_iq);
				अगर (ret)
					जाओ end;

				/* CR252, TX DC-Offset Calibration */
				ret = vnt_control_out_u8(priv,
							 MESSAGE_REQUEST_BBREG,
							 0xfC, calib_tx_dc);
				अगर (ret)
					जाओ end;

				/* CR253, RX I/Q Imbalance Calibration */
				ret = vnt_control_out_u8(priv,
							 MESSAGE_REQUEST_BBREG,
							 0xfd, calib_rx_iq);
				अगर (ret)
					जाओ end;
			पूर्ण अन्यथा अणु
				/* CR255, turn off
				 * BB Calibration compensation
				 */
				ret = vnt_control_out_u8(priv,
							 MESSAGE_REQUEST_BBREG,
							 0xff, 0x0);
				अगर (ret)
					जाओ end;
			पूर्ण
		पूर्ण
	पूर्ण

	/* get permanent network address */
	स_नकल(priv->permanent_net_addr, init_rsp->net_addr, 6);
	ether_addr_copy(priv->current_net_addr, priv->permanent_net_addr);

	/* अगर exist SW network address, use it */
	dev_dbg(&priv->usb->dev, "Network address = %pM\n",
		priv->current_net_addr);

	priv->radio_ctl = priv->eeprom[EEP_OFS_RADIOCTL];

	अगर ((priv->radio_ctl & EEP_RADIOCTL_ENABLE) != 0) अणु
		ret = vnt_control_in(priv, MESSAGE_TYPE_READ,
				     MAC_REG_GPIOCTL1, MESSAGE_REQUEST_MACREG,
				     1, &पंचांगp);
		अगर (ret)
			जाओ end;

		अगर ((पंचांगp & GPIO3_DATA) == 0) अणु
			ret = vnt_mac_reg_bits_on(priv, MAC_REG_GPIOCTL1,
						  GPIO3_INTMD);
		पूर्ण अन्यथा अणु
			ret = vnt_mac_reg_bits_off(priv, MAC_REG_GPIOCTL1,
						   GPIO3_INTMD);
		पूर्ण

		अगर (ret)
			जाओ end;
	पूर्ण

	ret = vnt_mac_set_led(priv, LEDSTS_TMLEN, 0x38);
	अगर (ret)
		जाओ end;

	ret = vnt_mac_set_led(priv, LEDSTS_STS, LEDSTS_SLOW);
	अगर (ret)
		जाओ end;

	ret = vnt_mac_reg_bits_on(priv, MAC_REG_GPIOCTL0, BIT(0));
	अगर (ret)
		जाओ end;

	ret = vnt_radio_घातer_on(priv);
	अगर (ret)
		जाओ end;

	dev_dbg(&priv->usb->dev, "<----INIbInitAdapter Exit\n");

end:
	वापस ret;
पूर्ण

अटल व्योम vnt_मुक्त_tx_bufs(काष्ठा vnt_निजी *priv)
अणु
	काष्ठा vnt_usb_send_context *tx_context;
	पूर्णांक ii;

	usb_समाप्त_anchored_urbs(&priv->tx_submitted);

	क्रम (ii = 0; ii < priv->num_tx_context; ii++) अणु
		tx_context = priv->tx_context[ii];
		अगर (!tx_context)
			जारी;

		kमुक्त(tx_context);
	पूर्ण
पूर्ण

अटल व्योम vnt_मुक्त_rx_bufs(काष्ठा vnt_निजी *priv)
अणु
	काष्ठा vnt_rcb *rcb;
	पूर्णांक ii;

	क्रम (ii = 0; ii < priv->num_rcb; ii++) अणु
		rcb = priv->rcb[ii];
		अगर (!rcb)
			जारी;

		/* deallocate URBs */
		अगर (rcb->urb) अणु
			usb_समाप्त_urb(rcb->urb);
			usb_मुक्त_urb(rcb->urb);
		पूर्ण

		/* deallocate skb */
		अगर (rcb->skb)
			dev_kमुक्त_skb(rcb->skb);

		kमुक्त(rcb);
	पूर्ण
पूर्ण

अटल व्योम vnt_मुक्त_पूर्णांक_bufs(काष्ठा vnt_निजी *priv)
अणु
	kमुक्त(priv->पूर्णांक_buf.data_buf);
पूर्ण

अटल पूर्णांक vnt_alloc_bufs(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक ret;
	काष्ठा vnt_usb_send_context *tx_context;
	काष्ठा vnt_rcb *rcb;
	पूर्णांक ii;

	init_usb_anchor(&priv->tx_submitted);

	क्रम (ii = 0; ii < priv->num_tx_context; ii++) अणु
		tx_context = kदो_स्मृति(माप(*tx_context), GFP_KERNEL);
		अगर (!tx_context) अणु
			ret = -ENOMEM;
			जाओ मुक्त_tx;
		पूर्ण

		priv->tx_context[ii] = tx_context;
		tx_context->priv = priv;
		tx_context->pkt_no = ii;
		tx_context->in_use = false;
	पूर्ण

	क्रम (ii = 0; ii < priv->num_rcb; ii++) अणु
		priv->rcb[ii] = kzalloc(माप(*priv->rcb[ii]), GFP_KERNEL);
		अगर (!priv->rcb[ii]) अणु
			ret = -ENOMEM;
			जाओ मुक्त_rx_tx;
		पूर्ण

		rcb = priv->rcb[ii];

		rcb->priv = priv;

		/* allocate URBs */
		rcb->urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!rcb->urb) अणु
			ret = -ENOMEM;
			जाओ मुक्त_rx_tx;
		पूर्ण

		rcb->skb = dev_alloc_skb(priv->rx_buf_sz);
		अगर (!rcb->skb) अणु
			ret = -ENOMEM;
			जाओ मुक्त_rx_tx;
		पूर्ण
		/* submit rx urb */
		ret = vnt_submit_rx_urb(priv, rcb);
		अगर (ret)
			जाओ मुक्त_rx_tx;
	पूर्ण

	priv->पूर्णांकerrupt_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!priv->पूर्णांकerrupt_urb) अणु
		ret = -ENOMEM;
		जाओ मुक्त_rx_tx;
	पूर्ण

	priv->पूर्णांक_buf.data_buf = kदो_स्मृति(MAX_INTERRUPT_SIZE, GFP_KERNEL);
	अगर (!priv->पूर्णांक_buf.data_buf) अणु
		ret = -ENOMEM;
		जाओ मुक्त_rx_tx_urb;
	पूर्ण

	वापस 0;

मुक्त_rx_tx_urb:
	usb_मुक्त_urb(priv->पूर्णांकerrupt_urb);
मुक्त_rx_tx:
	vnt_मुक्त_rx_bufs(priv);
मुक्त_tx:
	vnt_मुक्त_tx_bufs(priv);
	वापस ret;
पूर्ण

अटल व्योम vnt_tx_80211(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_tx_control *control,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	अगर (vnt_tx_packet(priv, skb))
		ieee80211_मुक्त_txskb(hw, skb);
पूर्ण

अटल पूर्णांक vnt_start(काष्ठा ieee80211_hw *hw)
अणु
	पूर्णांक ret;
	काष्ठा vnt_निजी *priv = hw->priv;

	priv->rx_buf_sz = MAX_TOTAL_SIZE_WITH_ALL_HEADERS;

	ret = vnt_alloc_bufs(priv);
	अगर (ret) अणु
		dev_dbg(&priv->usb->dev, "vnt_alloc_bufs fail...\n");
		जाओ err;
	पूर्ण

	clear_bit(DEVICE_FLAGS_DISCONNECTED, &priv->flags);

	ret = vnt_init_रेजिस्टरs(priv);
	अगर (ret) अणु
		dev_dbg(&priv->usb->dev, " init register fail\n");
		जाओ मुक्त_all;
	पूर्ण

	ret = vnt_key_init_table(priv);
	अगर (ret)
		जाओ मुक्त_all;

	priv->पूर्णांक_पूर्णांकerval = 1;  /* bInterval is set to 1 */

	ret = vnt_start_पूर्णांकerrupt_urb(priv);
	अगर (ret)
		जाओ मुक्त_all;

	ieee80211_wake_queues(hw);

	वापस 0;

मुक्त_all:
	vnt_मुक्त_rx_bufs(priv);
	vnt_मुक्त_tx_bufs(priv);
	vnt_मुक्त_पूर्णांक_bufs(priv);

	usb_समाप्त_urb(priv->पूर्णांकerrupt_urb);
	usb_मुक्त_urb(priv->पूर्णांकerrupt_urb);
err:
	वापस ret;
पूर्ण

अटल व्योम vnt_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;
	पूर्णांक i;

	अगर (!priv)
		वापस;

	क्रम (i = 0; i < MAX_KEY_TABLE; i++)
		vnt_mac_disable_keyentry(priv, i);

	/* clear all keys */
	priv->key_entry_inuse = 0;

	अगर (!test_bit(DEVICE_FLAGS_UNPLUG, &priv->flags))
		vnt_mac_shutकरोwn(priv);

	ieee80211_stop_queues(hw);

	set_bit(DEVICE_FLAGS_DISCONNECTED, &priv->flags);

	cancel_delayed_work_sync(&priv->run_command_work);

	priv->cmd_running = false;

	vnt_मुक्त_tx_bufs(priv);
	vnt_मुक्त_rx_bufs(priv);
	vnt_मुक्त_पूर्णांक_bufs(priv);

	usb_समाप्त_urb(priv->पूर्णांकerrupt_urb);
	usb_मुक्त_urb(priv->पूर्णांकerrupt_urb);
पूर्ण

अटल पूर्णांक vnt_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	priv->vअगर = vअगर;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		vnt_mac_reg_bits_off(priv, MAC_REG_RCR, RCR_UNICAST);

		vnt_mac_reg_bits_on(priv, MAC_REG_HOSTCR, HOSTCR_ADHOC);

		अवरोध;
	हाल NL80211_IFTYPE_AP:
		vnt_mac_reg_bits_off(priv, MAC_REG_RCR, RCR_UNICAST);

		vnt_mac_reg_bits_on(priv, MAC_REG_HOSTCR, HOSTCR_AP);

		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	priv->op_mode = vअगर->type;

	/* LED blink on TX */
	vnt_mac_set_led(priv, LEDSTS_STS, LEDSTS_INTER);

	वापस 0;
पूर्ण

अटल व्योम vnt_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		vnt_mac_reg_bits_off(priv, MAC_REG_TCR, TCR_AUTOBCNTX);
		vnt_mac_reg_bits_off(priv, MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);
		vnt_mac_reg_bits_off(priv, MAC_REG_HOSTCR, HOSTCR_ADHOC);
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		vnt_mac_reg_bits_off(priv, MAC_REG_TCR, TCR_AUTOBCNTX);
		vnt_mac_reg_bits_off(priv, MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);
		vnt_mac_reg_bits_off(priv, MAC_REG_HOSTCR, HOSTCR_AP);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	vnt_radio_घातer_off(priv);

	priv->op_mode = NL80211_IFTYPE_UNSPECIFIED;

	/* LED slow blink */
	vnt_mac_set_led(priv, LEDSTS_STS, LEDSTS_SLOW);
पूर्ण

अटल पूर्णांक vnt_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;
	काष्ठा ieee80211_conf *conf = &hw->conf;

	अगर (changed & IEEE80211_CONF_CHANGE_PS) अणु
		अगर (conf->flags & IEEE80211_CONF_PS)
			vnt_enable_घातer_saving(priv, conf->listen_पूर्णांकerval);
		अन्यथा
			vnt_disable_घातer_saving(priv);
	पूर्ण

	अगर ((changed & IEEE80211_CONF_CHANGE_CHANNEL) ||
	    (conf->flags & IEEE80211_CONF_OFFCHANNEL)) अणु
		vnt_set_channel(priv, conf->chandef.chan->hw_value);

		अगर (conf->chandef.chan->band == NL80211_BAND_5GHZ)
			priv->bb_type = BB_TYPE_11A;
		अन्यथा
			priv->bb_type = BB_TYPE_11G;
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_POWER)
		vnt_rf_setघातer(priv, conf->chandef.chan);

	अगर (conf->flags & (IEEE80211_CONF_OFFCHANNEL | IEEE80211_CONF_IDLE))
		/* Set max sensitivity*/
		vnt_update_pre_ed_threshold(priv, true);
	अन्यथा
		vnt_update_pre_ed_threshold(priv, false);

	वापस 0;
पूर्ण

अटल व्योम vnt_bss_info_changed(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_bss_conf *conf, u32 changed)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	priv->current_aid = conf->aid;

	अगर (changed & BSS_CHANGED_BSSID && conf->bssid)
		vnt_mac_set_bssid_addr(priv, (u8 *)conf->bssid);

	अगर (changed & BSS_CHANGED_BASIC_RATES) अणु
		priv->basic_rates = conf->basic_rates;

		vnt_update_top_rates(priv);

		dev_dbg(&priv->usb->dev, "basic rates %x\n", conf->basic_rates);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		अगर (conf->use_लघु_preamble) अणु
			vnt_mac_enable_barker_preamble_mode(priv);
			priv->preamble_type = PREAMBLE_SHORT;
		पूर्ण अन्यथा अणु
			vnt_mac_disable_barker_preamble_mode(priv);
			priv->preamble_type = PREAMBLE_LONG;
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_CTS_PROT) अणु
		अगर (conf->use_cts_prot)
			vnt_mac_enable_protect_mode(priv);
		अन्यथा
			vnt_mac_disable_protect_mode(priv);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		अगर (conf->use_लघु_slot)
			priv->लघु_slot_समय = true;
		अन्यथा
			priv->लघु_slot_समय = false;

		vnt_set_लघु_slot_समय(priv);
		vnt_set_vga_gain_offset(priv, priv->bb_vga[0]);
	पूर्ण

	अगर (changed & (BSS_CHANGED_BASIC_RATES | BSS_CHANGED_ERP_PREAMBLE |
		       BSS_CHANGED_ERP_SLOT))
		vnt_set_bss_mode(priv);

	अगर (changed & (BSS_CHANGED_TXPOWER | BSS_CHANGED_BANDWIDTH))
		vnt_rf_setघातer(priv, conf->chandef.chan);

	अगर (changed & BSS_CHANGED_BEACON_ENABLED) अणु
		dev_dbg(&priv->usb->dev,
			"Beacon enable %d\n", conf->enable_beacon);

		अगर (conf->enable_beacon) अणु
			vnt_beacon_enable(priv, vअगर, conf);

			vnt_mac_reg_bits_on(priv, MAC_REG_TCR, TCR_AUTOBCNTX);
		पूर्ण अन्यथा अणु
			vnt_mac_reg_bits_off(priv, MAC_REG_TCR, TCR_AUTOBCNTX);
		पूर्ण
	पूर्ण

	अगर (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_BEACON_INFO) &&
	    priv->op_mode != NL80211_IFTYPE_AP) अणु
		अगर (conf->assoc && conf->beacon_rate) अणु
			u16 ps_beacon_पूर्णांक = conf->beacon_पूर्णांक;

			अगर (conf->dtim_period)
				ps_beacon_पूर्णांक *= conf->dtim_period;
			अन्यथा अगर (hw->conf.listen_पूर्णांकerval)
				ps_beacon_पूर्णांक *= hw->conf.listen_पूर्णांकerval;

			vnt_mac_reg_bits_on(priv, MAC_REG_TFTCTL,
					    TFTCTL_TSFCNTREN);

			vnt_mac_set_beacon_पूर्णांकerval(priv, ps_beacon_पूर्णांक);

			vnt_reset_next_tbtt(priv, conf->beacon_पूर्णांक);

			vnt_adjust_tsf(priv, conf->beacon_rate->hw_value,
				       conf->sync_tsf, priv->current_tsf);

			vnt_update_next_tbtt(priv,
					     conf->sync_tsf, ps_beacon_पूर्णांक);
		पूर्ण अन्यथा अणु
			vnt_clear_current_tsf(priv);

			vnt_mac_reg_bits_off(priv, MAC_REG_TFTCTL,
					     TFTCTL_TSFCNTREN);
		पूर्ण
	पूर्ण
पूर्ण

अटल u64 vnt_prepare_multicast(काष्ठा ieee80211_hw *hw,
				 काष्ठा netdev_hw_addr_list *mc_list)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;
	काष्ठा netdev_hw_addr *ha;
	u64 mc_filter = 0;
	u32 bit_nr;

	netdev_hw_addr_list_क्रम_each(ha, mc_list) अणु
		bit_nr = ether_crc(ETH_ALEN, ha->addr) >> 26;
		mc_filter |= BIT_ULL(bit_nr);
	पूर्ण

	priv->mc_list_count = mc_list->count;

	वापस mc_filter;
पूर्ण

अटल व्योम vnt_configure(काष्ठा ieee80211_hw *hw,
			  अचिन्हित पूर्णांक changed_flags,
			  अचिन्हित पूर्णांक *total_flags, u64 multicast)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;
	u8 rx_mode = 0;

	*total_flags &= FIF_ALLMULTI | FIF_OTHER_BSS | FIF_BCN_PRBRESP_PROMISC;

	vnt_control_in(priv, MESSAGE_TYPE_READ, MAC_REG_RCR,
		       MESSAGE_REQUEST_MACREG, माप(u8), &rx_mode);

	dev_dbg(&priv->usb->dev, "rx mode in = %x\n", rx_mode);

	अगर (changed_flags & FIF_ALLMULTI) अणु
		अगर (*total_flags & FIF_ALLMULTI) अणु
			अगर (priv->mc_list_count > 2)
				vnt_mac_set_filter(priv, ~0);
			अन्यथा
				vnt_mac_set_filter(priv, multicast);

			rx_mode |= RCR_MULTICAST | RCR_BROADCAST;
		पूर्ण अन्यथा अणु
			rx_mode &= ~(RCR_MULTICAST | RCR_BROADCAST);
		पूर्ण
	पूर्ण

	अगर (changed_flags & (FIF_OTHER_BSS | FIF_BCN_PRBRESP_PROMISC)) अणु
		अगर (*total_flags & (FIF_OTHER_BSS | FIF_BCN_PRBRESP_PROMISC))
			rx_mode &= ~RCR_BSSID;
		अन्यथा
			rx_mode |= RCR_BSSID;
	पूर्ण

	vnt_control_out_u8(priv, MESSAGE_REQUEST_MACREG, MAC_REG_RCR, rx_mode);

	dev_dbg(&priv->usb->dev, "rx mode out= %x\n", rx_mode);
पूर्ण

अटल पूर्णांक vnt_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
		       काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		       काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	चयन (cmd) अणु
	हाल SET_KEY:
		वापस vnt_set_keys(hw, sta, vअगर, key);
	हाल DISABLE_KEY:
		अगर (test_bit(key->hw_key_idx, &priv->key_entry_inuse)) अणु
			clear_bit(key->hw_key_idx, &priv->key_entry_inuse);

			vnt_mac_disable_keyentry(priv, key->hw_key_idx);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vnt_get_stats(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	स_नकल(stats, &priv->low_stats, माप(*stats));

	वापस 0;
पूर्ण

अटल u64 vnt_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	वापस priv->current_tsf;
पूर्ण

अटल व्योम vnt_set_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			u64 tsf)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	vnt_update_next_tbtt(priv, tsf, vअगर->bss_conf.beacon_पूर्णांक);
पूर्ण

अटल व्योम vnt_reset_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	vnt_mac_reg_bits_off(priv, MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);

	vnt_clear_current_tsf(priv);
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops vnt_mac_ops = अणु
	.tx			= vnt_tx_80211,
	.start			= vnt_start,
	.stop			= vnt_stop,
	.add_पूर्णांकerface		= vnt_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= vnt_हटाओ_पूर्णांकerface,
	.config			= vnt_config,
	.bss_info_changed	= vnt_bss_info_changed,
	.prepare_multicast	= vnt_prepare_multicast,
	.configure_filter	= vnt_configure,
	.set_key		= vnt_set_key,
	.get_stats		= vnt_get_stats,
	.get_tsf		= vnt_get_tsf,
	.set_tsf		= vnt_set_tsf,
	.reset_tsf		= vnt_reset_tsf,
पूर्ण;

पूर्णांक vnt_init(काष्ठा vnt_निजी *priv)
अणु
	अगर (vnt_init_रेजिस्टरs(priv))
		वापस -EAGAIN;

	SET_IEEE80211_PERM_ADDR(priv->hw, priv->permanent_net_addr);

	vnt_init_bands(priv);

	अगर (ieee80211_रेजिस्टर_hw(priv->hw))
		वापस -ENODEV;

	priv->mac_hw = true;

	vnt_radio_घातer_off(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक
vt6656_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev;
	काष्ठा vnt_निजी *priv;
	काष्ठा ieee80211_hw *hw;
	काष्ठा wiphy *wiphy;
	पूर्णांक rc;

	udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));

	dev_notice(&udev->dev, "%s Ver. %s\n",
		   DEVICE_FULL_DRV_NAM, DEVICE_VERSION);
	dev_notice(&udev->dev,
		   "Copyright (c) 2004 VIA Networking Technologies, Inc.\n");

	hw = ieee80211_alloc_hw(माप(काष्ठा vnt_निजी), &vnt_mac_ops);
	अगर (!hw) अणु
		dev_err(&udev->dev, "could not register ieee80211_hw\n");
		rc = -ENOMEM;
		जाओ err_nomem;
	पूर्ण

	priv = hw->priv;
	priv->hw = hw;
	priv->usb = udev;
	priv->पूर्णांकf = पूर्णांकf;

	vnt_set_options(priv);

	spin_lock_init(&priv->lock);
	mutex_init(&priv->usb_lock);

	INIT_DELAYED_WORK(&priv->run_command_work, vnt_run_command);

	usb_set_पूर्णांकfdata(पूर्णांकf, priv);

	wiphy = priv->hw->wiphy;

	wiphy->frag_threshold = FRAG_THRESH_DEF;
	wiphy->rts_threshold = RTS_THRESH_DEF;
	wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_ADHOC) | BIT(NL80211_IFTYPE_AP);

	ieee80211_hw_set(priv->hw, TIMING_BEACON_ONLY);
	ieee80211_hw_set(priv->hw, SIGNAL_DBM);
	ieee80211_hw_set(priv->hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(priv->hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(priv->hw, SUPPORTS_PS);
	ieee80211_hw_set(priv->hw, PS_शून्यFUNC_STACK);

	priv->hw->extra_tx_headroom =
		माप(काष्ठा vnt_tx_buffer) + माप(काष्ठा vnt_tx_usb_header);
	priv->hw->max_संकेत = 100;

	SET_IEEE80211_DEV(priv->hw, &पूर्णांकf->dev);

	rc = usb_reset_device(priv->usb);
	अगर (rc)
		dev_warn(&priv->usb->dev,
			 "%s reset fail status=%d\n", __func__, rc);

	clear_bit(DEVICE_FLAGS_DISCONNECTED, &priv->flags);
	vnt_reset_command_समयr(priv);

	vnt_schedule_command(priv, WLAN_CMD_INIT_MAC80211);

	वापस 0;

err_nomem:
	usb_put_dev(udev);

	वापस rc;
पूर्ण

अटल व्योम vt6656_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा vnt_निजी *priv = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (!priv)
		वापस;

	अगर (priv->mac_hw)
		ieee80211_unरेजिस्टर_hw(priv->hw);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	usb_put_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));

	set_bit(DEVICE_FLAGS_UNPLUG, &priv->flags);

	ieee80211_मुक्त_hw(priv->hw);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक vt6656_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vt6656_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

MODULE_DEVICE_TABLE(usb, vt6656_table);

अटल काष्ठा usb_driver vt6656_driver = अणु
	.name =		DEVICE_NAME,
	.probe =	vt6656_probe,
	.disconnect =	vt6656_disconnect,
	.id_table =	vt6656_table,
#अगर_घोषित CONFIG_PM
	.suspend = vt6656_suspend,
	.resume = vt6656_resume,
#पूर्ण_अगर /* CONFIG_PM */
पूर्ण;

module_usb_driver(vt6656_driver);

MODULE_FIRMWARE(FIRMWARE_NAME);
