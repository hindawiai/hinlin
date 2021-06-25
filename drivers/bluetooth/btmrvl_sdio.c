<शैली गुरु>
/**
 * Marvell BT-over-SDIO driver: SDIO पूर्णांकerface related functions.
 *
 * Copyright (C) 2009, Marvell International Ltd.
 *
 * This software file (the "File") is distributed by Marvell International
 * Ltd. under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 **/

#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>

#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/module.h>
#समावेश <linux/devcoredump.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "btmrvl_drv.h"
#समावेश "btmrvl_sdio.h"

#घोषणा VERSION "1.0"

अटल काष्ठा memory_type_mapping mem_type_mapping_tbl[] = अणु
	अणु"ITCM", शून्य, 0, 0xF0पूर्ण,
	अणु"DTCM", शून्य, 0, 0xF1पूर्ण,
	अणु"SQRAM", शून्य, 0, 0xF2पूर्ण,
	अणु"APU", शून्य, 0, 0xF3पूर्ण,
	अणु"CIU", शून्य, 0, 0xF4पूर्ण,
	अणु"ICU", शून्य, 0, 0xF5पूर्ण,
	अणु"MAC", शून्य, 0, 0xF6पूर्ण,
	अणु"EXT7", शून्य, 0, 0xF7पूर्ण,
	अणु"EXT8", शून्य, 0, 0xF8पूर्ण,
	अणु"EXT9", शून्य, 0, 0xF9पूर्ण,
	अणु"EXT10", शून्य, 0, 0xFAपूर्ण,
	अणु"EXT11", शून्य, 0, 0xFBपूर्ण,
	अणु"EXT12", शून्य, 0, 0xFCपूर्ण,
	अणु"EXT13", शून्य, 0, 0xFDपूर्ण,
	अणु"EXTLAST", शून्य, 0, 0xFEपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bपंचांगrvl_sdio_of_match_table[] = अणु
	अणु .compatible = "marvell,sd8897-bt" पूर्ण,
	अणु .compatible = "marvell,sd8997-bt" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल irqवापस_t bपंचांगrvl_wake_irq_bt(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा bपंचांगrvl_sdio_card *card = priv;
	काष्ठा device *dev = &card->func->dev;
	काष्ठा bपंचांगrvl_plt_wake_cfg *cfg = card->plt_wake_cfg;

	dev_info(dev, "wake by bt\n");
	cfg->wake_by_bt = true;
	disable_irq_nosync(irq);

	pm_wakeup_event(dev, 0);
	pm_प्रणाली_wakeup();

	वापस IRQ_HANDLED;
पूर्ण

/* This function parses device tree node using mmc subnode devicetree API.
 * The device node is saved in card->plt_of_node.
 * If the device tree node exists and includes पूर्णांकerrupts attributes, this
 * function will request platक्रमm specअगरic wakeup पूर्णांकerrupt.
 */
अटल पूर्णांक bपंचांगrvl_sdio_probe_of(काष्ठा device *dev,
				काष्ठा bपंचांगrvl_sdio_card *card)
अणु
	काष्ठा bपंचांगrvl_plt_wake_cfg *cfg;
	पूर्णांक ret;

	अगर (!dev->of_node ||
	    !of_match_node(bपंचांगrvl_sdio_of_match_table, dev->of_node)) अणु
		dev_info(dev, "sdio device tree data not available\n");
		वापस -1;
	पूर्ण

	card->plt_of_node = dev->of_node;

	card->plt_wake_cfg = devm_kzalloc(dev, माप(*card->plt_wake_cfg),
					  GFP_KERNEL);
	cfg = card->plt_wake_cfg;
	अगर (cfg && card->plt_of_node) अणु
		cfg->irq_bt = irq_of_parse_and_map(card->plt_of_node, 0);
		अगर (!cfg->irq_bt) अणु
			dev_err(dev, "fail to parse irq_bt from device tree\n");
			cfg->irq_bt = -1;
		पूर्ण अन्यथा अणु
			ret = devm_request_irq(dev, cfg->irq_bt,
					       bपंचांगrvl_wake_irq_bt,
					       0, "bt_wake", card);
			अगर (ret) अणु
				dev_err(dev,
					"Failed to request irq_bt %d (%d)\n",
					cfg->irq_bt, ret);
			पूर्ण

			/* Configure wakeup (enabled by शेष) */
			device_init_wakeup(dev, true);
			disable_irq(cfg->irq_bt);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* The bपंचांगrvl_sdio_हटाओ() callback function is called
 * when user हटाओs this module from kernel space or ejects
 * the card from the slot. The driver handles these 2 हालs
 * dअगरferently.
 * If the user is removing the module, a MODULE_SHUTDOWN_REQ
 * command is sent to firmware and पूर्णांकerrupt will be disabled.
 * If the card is हटाओd, there is no need to send command
 * or disable पूर्णांकerrupt.
 *
 * The variable 'user_rmmod' is used to distinguish these two
 * scenarios. This flag is initialized as FALSE in हाल the card
 * is हटाओd, and will be set to TRUE क्रम module removal when
 * module_निकास function is called.
 */
अटल u8 user_rmmod;
अटल u8 sdio_ireg;

अटल स्थिर काष्ठा bपंचांगrvl_sdio_card_reg bपंचांगrvl_reg_8688 = अणु
	.cfg = 0x03,
	.host_पूर्णांक_mask = 0x04,
	.host_पूर्णांकstatus = 0x05,
	.card_status = 0x20,
	.sq_पढ़ो_base_addr_a0 = 0x10,
	.sq_पढ़ो_base_addr_a1 = 0x11,
	.card_fw_status0 = 0x40,
	.card_fw_status1 = 0x41,
	.card_rx_len = 0x42,
	.card_rx_unit = 0x43,
	.io_port_0 = 0x00,
	.io_port_1 = 0x01,
	.io_port_2 = 0x02,
	.पूर्णांक_पढ़ो_to_clear = false,
पूर्ण;
अटल स्थिर काष्ठा bपंचांगrvl_sdio_card_reg bपंचांगrvl_reg_87xx = अणु
	.cfg = 0x00,
	.host_पूर्णांक_mask = 0x02,
	.host_पूर्णांकstatus = 0x03,
	.card_status = 0x30,
	.sq_पढ़ो_base_addr_a0 = 0x40,
	.sq_पढ़ो_base_addr_a1 = 0x41,
	.card_revision = 0x5c,
	.card_fw_status0 = 0x60,
	.card_fw_status1 = 0x61,
	.card_rx_len = 0x62,
	.card_rx_unit = 0x63,
	.io_port_0 = 0x78,
	.io_port_1 = 0x79,
	.io_port_2 = 0x7a,
	.पूर्णांक_पढ़ो_to_clear = false,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगrvl_sdio_card_reg bपंचांगrvl_reg_8887 = अणु
	.cfg = 0x00,
	.host_पूर्णांक_mask = 0x08,
	.host_पूर्णांकstatus = 0x0C,
	.card_status = 0x5C,
	.sq_पढ़ो_base_addr_a0 = 0x6C,
	.sq_पढ़ो_base_addr_a1 = 0x6D,
	.card_revision = 0xC8,
	.card_fw_status0 = 0x88,
	.card_fw_status1 = 0x89,
	.card_rx_len = 0x8A,
	.card_rx_unit = 0x8B,
	.io_port_0 = 0xE4,
	.io_port_1 = 0xE5,
	.io_port_2 = 0xE6,
	.पूर्णांक_पढ़ो_to_clear = true,
	.host_पूर्णांक_rsr = 0x04,
	.card_misc_cfg = 0xD8,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगrvl_sdio_card_reg bपंचांगrvl_reg_8897 = अणु
	.cfg = 0x00,
	.host_पूर्णांक_mask = 0x02,
	.host_पूर्णांकstatus = 0x03,
	.card_status = 0x50,
	.sq_पढ़ो_base_addr_a0 = 0x60,
	.sq_पढ़ो_base_addr_a1 = 0x61,
	.card_revision = 0xbc,
	.card_fw_status0 = 0xc0,
	.card_fw_status1 = 0xc1,
	.card_rx_len = 0xc2,
	.card_rx_unit = 0xc3,
	.io_port_0 = 0xd8,
	.io_port_1 = 0xd9,
	.io_port_2 = 0xda,
	.पूर्णांक_पढ़ो_to_clear = true,
	.host_पूर्णांक_rsr = 0x01,
	.card_misc_cfg = 0xcc,
	.fw_dump_ctrl = 0xe2,
	.fw_dump_start = 0xe3,
	.fw_dump_end = 0xea,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगrvl_sdio_card_reg bपंचांगrvl_reg_89xx = अणु
	.cfg = 0x00,
	.host_पूर्णांक_mask = 0x08,
	.host_पूर्णांकstatus = 0x0c,
	.card_status = 0x5c,
	.sq_पढ़ो_base_addr_a0 = 0xf8,
	.sq_पढ़ो_base_addr_a1 = 0xf9,
	.card_revision = 0xc8,
	.card_fw_status0 = 0xe8,
	.card_fw_status1 = 0xe9,
	.card_rx_len = 0xea,
	.card_rx_unit = 0xeb,
	.io_port_0 = 0xe4,
	.io_port_1 = 0xe5,
	.io_port_2 = 0xe6,
	.पूर्णांक_पढ़ो_to_clear = true,
	.host_पूर्णांक_rsr = 0x04,
	.card_misc_cfg = 0xd8,
	.fw_dump_ctrl = 0xf0,
	.fw_dump_start = 0xf1,
	.fw_dump_end = 0xf8,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगrvl_sdio_device bपंचांगrvl_sdio_sd8688 = अणु
	.helper		= "mrvl/sd8688_helper.bin",
	.firmware	= "mrvl/sd8688.bin",
	.reg		= &bपंचांगrvl_reg_8688,
	.support_pscan_win_report = false,
	.sd_blksz_fw_dl	= 64,
	.supports_fw_dump = false,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगrvl_sdio_device bपंचांगrvl_sdio_sd8787 = अणु
	.helper		= शून्य,
	.firmware	= "mrvl/sd8787_uapsta.bin",
	.reg		= &bपंचांगrvl_reg_87xx,
	.support_pscan_win_report = false,
	.sd_blksz_fw_dl	= 256,
	.supports_fw_dump = false,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगrvl_sdio_device bपंचांगrvl_sdio_sd8797 = अणु
	.helper		= शून्य,
	.firmware	= "mrvl/sd8797_uapsta.bin",
	.reg		= &bपंचांगrvl_reg_87xx,
	.support_pscan_win_report = false,
	.sd_blksz_fw_dl	= 256,
	.supports_fw_dump = false,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगrvl_sdio_device bपंचांगrvl_sdio_sd8887 = अणु
	.helper		= शून्य,
	.firmware	= "mrvl/sd8887_uapsta.bin",
	.reg		= &bपंचांगrvl_reg_8887,
	.support_pscan_win_report = true,
	.sd_blksz_fw_dl	= 256,
	.supports_fw_dump = false,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगrvl_sdio_device bपंचांगrvl_sdio_sd8897 = अणु
	.helper		= शून्य,
	.firmware	= "mrvl/sd8897_uapsta.bin",
	.reg		= &bपंचांगrvl_reg_8897,
	.support_pscan_win_report = true,
	.sd_blksz_fw_dl	= 256,
	.supports_fw_dump = true,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगrvl_sdio_device bपंचांगrvl_sdio_sd8977 = अणु
	.helper         = शून्य,
	.firmware       = "mrvl/sdsd8977_combo_v2.bin",
	.reg            = &bपंचांगrvl_reg_89xx,
	.support_pscan_win_report = true,
	.sd_blksz_fw_dl = 256,
	.supports_fw_dump = true,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगrvl_sdio_device bपंचांगrvl_sdio_sd8987 = अणु
	.helper		= शून्य,
	.firmware	= "mrvl/sd8987_uapsta.bin",
	.reg		= &bपंचांगrvl_reg_89xx,
	.support_pscan_win_report = true,
	.sd_blksz_fw_dl	= 256,
	.supports_fw_dump = true,
पूर्ण;

अटल स्थिर काष्ठा bपंचांगrvl_sdio_device bपंचांगrvl_sdio_sd8997 = अणु
	.helper         = शून्य,
	.firmware       = "mrvl/sdsd8997_combo_v4.bin",
	.reg            = &bपंचांगrvl_reg_89xx,
	.support_pscan_win_report = true,
	.sd_blksz_fw_dl = 256,
	.supports_fw_dump = true,
पूर्ण;

अटल स्थिर काष्ठा sdio_device_id bपंचांगrvl_sdio_ids[] = अणु
	/* Marvell SD8688 Bluetooth device */
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8688_BT),
			.driver_data = (अचिन्हित दीर्घ)&bपंचांगrvl_sdio_sd8688 पूर्ण,
	/* Marvell SD8787 Bluetooth device */
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8787_BT),
			.driver_data = (अचिन्हित दीर्घ)&bपंचांगrvl_sdio_sd8787 पूर्ण,
	/* Marvell SD8787 Bluetooth AMP device */
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8787_BT_AMP),
			.driver_data = (अचिन्हित दीर्घ)&bपंचांगrvl_sdio_sd8787 पूर्ण,
	/* Marvell SD8797 Bluetooth device */
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8797_BT),
			.driver_data = (अचिन्हित दीर्घ)&bपंचांगrvl_sdio_sd8797 पूर्ण,
	/* Marvell SD8887 Bluetooth device */
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8887_BT),
			.driver_data = (अचिन्हित दीर्घ)&bपंचांगrvl_sdio_sd8887 पूर्ण,
	/* Marvell SD8897 Bluetooth device */
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8897_BT),
			.driver_data = (अचिन्हित दीर्घ)&bपंचांगrvl_sdio_sd8897 पूर्ण,
	/* Marvell SD8977 Bluetooth device */
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8977_BT),
			.driver_data = (अचिन्हित दीर्घ)&bपंचांगrvl_sdio_sd8977 पूर्ण,
	/* Marvell SD8987 Bluetooth device */
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8987_BT),
			.driver_data = (अचिन्हित दीर्घ)&bपंचांगrvl_sdio_sd8987 पूर्ण,
	/* Marvell SD8997 Bluetooth device */
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8997_BT),
			.driver_data = (अचिन्हित दीर्घ)&bपंचांगrvl_sdio_sd8997 पूर्ण,

	अणु पूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(sdio, bपंचांगrvl_sdio_ids);

अटल पूर्णांक bपंचांगrvl_sdio_get_rx_unit(काष्ठा bपंचांगrvl_sdio_card *card)
अणु
	u8 reg;
	पूर्णांक ret;

	reg = sdio_पढ़ोb(card->func, card->reg->card_rx_unit, &ret);
	अगर (!ret)
		card->rx_unit = reg;

	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_पढ़ो_fw_status(काष्ठा bपंचांगrvl_sdio_card *card, u16 *dat)
अणु
	u8 fws0, fws1;
	पूर्णांक ret;

	*dat = 0;

	fws0 = sdio_पढ़ोb(card->func, card->reg->card_fw_status0, &ret);
	अगर (ret)
		वापस -EIO;

	fws1 = sdio_पढ़ोb(card->func, card->reg->card_fw_status1, &ret);
	अगर (ret)
		वापस -EIO;

	*dat = (((u16) fws1) << 8) | fws0;

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_पढ़ो_rx_len(काष्ठा bपंचांगrvl_sdio_card *card, u16 *dat)
अणु
	u8 reg;
	पूर्णांक ret;

	reg = sdio_पढ़ोb(card->func, card->reg->card_rx_len, &ret);
	अगर (!ret)
		*dat = (u16) reg << card->rx_unit;

	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_enable_host_पूर्णांक_mask(काष्ठा bपंचांगrvl_sdio_card *card,
								u8 mask)
अणु
	पूर्णांक ret;

	sdio_ग_लिखोb(card->func, mask, card->reg->host_पूर्णांक_mask, &ret);
	अगर (ret) अणु
		BT_ERR("Unable to enable the host interrupt!");
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_disable_host_पूर्णांक_mask(काष्ठा bपंचांगrvl_sdio_card *card,
								u8 mask)
अणु
	u8 host_पूर्णांक_mask;
	पूर्णांक ret;

	host_पूर्णांक_mask = sdio_पढ़ोb(card->func, card->reg->host_पूर्णांक_mask, &ret);
	अगर (ret)
		वापस -EIO;

	host_पूर्णांक_mask &= ~mask;

	sdio_ग_लिखोb(card->func, host_पूर्णांक_mask, card->reg->host_पूर्णांक_mask, &ret);
	अगर (ret < 0) अणु
		BT_ERR("Unable to disable the host interrupt!");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_poll_card_status(काष्ठा bपंचांगrvl_sdio_card *card, u8 bits)
अणु
	अचिन्हित पूर्णांक tries;
	u8 status;
	पूर्णांक ret;

	क्रम (tries = 0; tries < MAX_POLL_TRIES * 1000; tries++) अणु
		status = sdio_पढ़ोb(card->func, card->reg->card_status,	&ret);
		अगर (ret)
			जाओ failed;
		अगर ((status & bits) == bits)
			वापस ret;

		udelay(1);
	पूर्ण

	ret = -ETIMEDOUT;

failed:
	BT_ERR("FAILED! ret=%d", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_verअगरy_fw_करोwnload(काष्ठा bपंचांगrvl_sdio_card *card,
								पूर्णांक pollnum)
अणु
	u16 firmwarestat;
	पूर्णांक tries, ret;

	 /* Wait क्रम firmware to become पढ़ोy */
	क्रम (tries = 0; tries < pollnum; tries++) अणु
		sdio_claim_host(card->func);
		ret = bपंचांगrvl_sdio_पढ़ो_fw_status(card, &firmwarestat);
		sdio_release_host(card->func);
		अगर (ret < 0)
			जारी;

		अगर (firmwarestat == FIRMWARE_READY)
			वापस 0;

		msleep(100);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_करोwnload_helper(काष्ठा bपंचांगrvl_sdio_card *card)
अणु
	स्थिर काष्ठा firmware *fw_helper = शून्य;
	स्थिर u8 *helper = शून्य;
	पूर्णांक ret;
	व्योम *पंचांगphlprbuf = शून्य;
	पूर्णांक पंचांगphlprbufsz, hlprblknow, helperlen;
	u8 *helperbuf;
	u32 tx_len;

	ret = request_firmware(&fw_helper, card->helper,
						&card->func->dev);
	अगर ((ret < 0) || !fw_helper) अणु
		BT_ERR("request_firmware(helper) failed, error code = %d",
									ret);
		ret = -ENOENT;
		जाओ करोne;
	पूर्ण

	helper = fw_helper->data;
	helperlen = fw_helper->size;

	BT_DBG("Downloading helper image (%d bytes), block size %d bytes",
						helperlen, SDIO_BLOCK_SIZE);

	पंचांगphlprbufsz = ALIGN_SZ(BTM_UPLD_SIZE, BTSDIO_DMA_ALIGN);

	पंचांगphlprbuf = kzalloc(पंचांगphlprbufsz, GFP_KERNEL);
	अगर (!पंचांगphlprbuf) अणु
		BT_ERR("Unable to allocate buffer for helper."
			" Terminating download");
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	helperbuf = (u8 *) ALIGN_ADDR(पंचांगphlprbuf, BTSDIO_DMA_ALIGN);

	/* Perक्रमm helper data transfer */
	tx_len = (FIRMWARE_TRANSFER_NBLOCK * SDIO_BLOCK_SIZE)
			- SDIO_HEADER_LEN;
	hlprblknow = 0;

	करो अणु
		ret = bपंचांगrvl_sdio_poll_card_status(card,
					    CARD_IO_READY | DN_LD_CARD_RDY);
		अगर (ret < 0) अणु
			BT_ERR("Helper download poll status timeout @ %d",
				hlprblknow);
			जाओ करोne;
		पूर्ण

		/* Check अगर there is more data? */
		अगर (hlprblknow >= helperlen)
			अवरोध;

		अगर (helperlen - hlprblknow < tx_len)
			tx_len = helperlen - hlprblknow;

		/* Little-endian */
		helperbuf[0] = ((tx_len & 0x000000ff) >> 0);
		helperbuf[1] = ((tx_len & 0x0000ff00) >> 8);
		helperbuf[2] = ((tx_len & 0x00ff0000) >> 16);
		helperbuf[3] = ((tx_len & 0xff000000) >> 24);

		स_नकल(&helperbuf[SDIO_HEADER_LEN], &helper[hlprblknow],
				tx_len);

		/* Now send the data */
		ret = sdio_ग_लिखोsb(card->func, card->ioport, helperbuf,
				FIRMWARE_TRANSFER_NBLOCK * SDIO_BLOCK_SIZE);
		अगर (ret < 0) अणु
			BT_ERR("IO error during helper download @ %d",
				hlprblknow);
			जाओ करोne;
		पूर्ण

		hlprblknow += tx_len;
	पूर्ण जबतक (true);

	BT_DBG("Transferring helper image EOF block");

	स_रखो(helperbuf, 0x0, SDIO_BLOCK_SIZE);

	ret = sdio_ग_लिखोsb(card->func, card->ioport, helperbuf,
							SDIO_BLOCK_SIZE);
	अगर (ret < 0) अणु
		BT_ERR("IO error in writing helper image EOF block");
		जाओ करोne;
	पूर्ण

	ret = 0;

करोne:
	kमुक्त(पंचांगphlprbuf);
	release_firmware(fw_helper);
	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_करोwnload_fw_w_helper(काष्ठा bपंचांगrvl_sdio_card *card)
अणु
	स्थिर काष्ठा firmware *fw_firmware = शून्य;
	स्थिर u8 *firmware = शून्य;
	पूर्णांक firmwarelen, पंचांगpfwbufsz, ret;
	अचिन्हित पूर्णांक tries, offset;
	u8 base0, base1;
	व्योम *पंचांगpfwbuf = शून्य;
	u8 *fwbuf;
	u16 len, blksz_dl = card->sd_blksz_fw_dl;
	पूर्णांक txlen = 0, tx_blocks = 0, count = 0;

	ret = request_firmware(&fw_firmware, card->firmware,
							&card->func->dev);
	अगर ((ret < 0) || !fw_firmware) अणु
		BT_ERR("request_firmware(firmware) failed, error code = %d",
									ret);
		ret = -ENOENT;
		जाओ करोne;
	पूर्ण

	firmware = fw_firmware->data;
	firmwarelen = fw_firmware->size;

	BT_DBG("Downloading FW image (%d bytes)", firmwarelen);

	पंचांगpfwbufsz = ALIGN_SZ(BTM_UPLD_SIZE, BTSDIO_DMA_ALIGN);
	पंचांगpfwbuf = kzalloc(पंचांगpfwbufsz, GFP_KERNEL);
	अगर (!पंचांगpfwbuf) अणु
		BT_ERR("Unable to allocate buffer for firmware."
		       " Terminating download");
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Ensure aligned firmware buffer */
	fwbuf = (u8 *) ALIGN_ADDR(पंचांगpfwbuf, BTSDIO_DMA_ALIGN);

	/* Perक्रमm firmware data transfer */
	offset = 0;
	करो अणु
		ret = bपंचांगrvl_sdio_poll_card_status(card,
					CARD_IO_READY | DN_LD_CARD_RDY);
		अगर (ret < 0) अणु
			BT_ERR("FW download with helper poll status"
						" timeout @ %d", offset);
			जाओ करोne;
		पूर्ण

		/* Check अगर there is more data ? */
		अगर (offset >= firmwarelen)
			अवरोध;

		क्रम (tries = 0; tries < MAX_POLL_TRIES; tries++) अणु
			base0 = sdio_पढ़ोb(card->func,
					card->reg->sq_पढ़ो_base_addr_a0, &ret);
			अगर (ret) अणु
				BT_ERR("BASE0 register read failed:"
					" base0 = 0x%04X(%d)."
					" Terminating download",
					base0, base0);
				ret = -EIO;
				जाओ करोne;
			पूर्ण
			base1 = sdio_पढ़ोb(card->func,
					card->reg->sq_पढ़ो_base_addr_a1, &ret);
			अगर (ret) अणु
				BT_ERR("BASE1 register read failed:"
					" base1 = 0x%04X(%d)."
					" Terminating download",
					base1, base1);
				ret = -EIO;
				जाओ करोne;
			पूर्ण

			len = (((u16) base1) << 8) | base0;
			अगर (len)
				अवरोध;

			udelay(10);
		पूर्ण

		अगर (!len)
			अवरोध;
		अन्यथा अगर (len > BTM_UPLD_SIZE) अणु
			BT_ERR("FW download failure @%d, invalid length %d",
								offset, len);
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		txlen = len;

		अगर (len & BIT(0)) अणु
			count++;
			अगर (count > MAX_WRITE_IOMEM_RETRY) अणु
				BT_ERR("FW download failure @%d, "
					"over max retry count", offset);
				ret = -EIO;
				जाओ करोne;
			पूर्ण
			BT_ERR("FW CRC error indicated by the helper: "
				"len = 0x%04X, txlen = %d", len, txlen);
			len &= ~BIT(0);
			/* Set txlen to 0 so as to resend from same offset */
			txlen = 0;
		पूर्ण अन्यथा अणु
			count = 0;

			/* Last block ? */
			अगर (firmwarelen - offset < txlen)
				txlen = firmwarelen - offset;

			tx_blocks = DIV_ROUND_UP(txlen, blksz_dl);

			स_नकल(fwbuf, &firmware[offset], txlen);
		पूर्ण

		ret = sdio_ग_लिखोsb(card->func, card->ioport, fwbuf,
						tx_blocks * blksz_dl);

		अगर (ret < 0) अणु
			BT_ERR("FW download, writesb(%d) failed @%d",
							count, offset);
			sdio_ग_लिखोb(card->func, HOST_CMD53_FIN,
						card->reg->cfg, &ret);
			अगर (ret)
				BT_ERR("writeb failed (CFG)");
		पूर्ण

		offset += txlen;
	पूर्ण जबतक (true);

	BT_INFO("FW download over, size %d bytes", offset);

	ret = 0;

करोne:
	kमुक्त(पंचांगpfwbuf);
	release_firmware(fw_firmware);
	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_card_to_host(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	u16 buf_len = 0;
	पूर्णांक ret, num_blocks, blksz;
	काष्ठा sk_buff *skb = शून्य;
	u32 type;
	u8 *payload;
	काष्ठा hci_dev *hdev = priv->bपंचांगrvl_dev.hcidev;
	काष्ठा bपंचांगrvl_sdio_card *card = priv->bपंचांगrvl_dev.card;

	अगर (!card || !card->func) अणु
		BT_ERR("card or function is NULL!");
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	/* Read the length of data to be transferred */
	ret = bपंचांगrvl_sdio_पढ़ो_rx_len(card, &buf_len);
	अगर (ret < 0) अणु
		BT_ERR("read rx_len failed");
		ret = -EIO;
		जाओ निकास;
	पूर्ण

	blksz = SDIO_BLOCK_SIZE;
	num_blocks = DIV_ROUND_UP(buf_len, blksz);

	अगर (buf_len <= SDIO_HEADER_LEN
	    || (num_blocks * blksz) > ALLOC_BUF_SIZE) अणु
		BT_ERR("invalid packet length: %d", buf_len);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	/* Allocate buffer */
	skb = bt_skb_alloc(num_blocks * blksz + BTSDIO_DMA_ALIGN, GFP_KERNEL);
	अगर (!skb) अणु
		BT_ERR("No free skb");
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	अगर ((अचिन्हित दीर्घ) skb->data & (BTSDIO_DMA_ALIGN - 1)) अणु
		skb_put(skb, (अचिन्हित दीर्घ) skb->data &
					(BTSDIO_DMA_ALIGN - 1));
		skb_pull(skb, (अचिन्हित दीर्घ) skb->data &
					(BTSDIO_DMA_ALIGN - 1));
	पूर्ण

	payload = skb->data;

	ret = sdio_पढ़ोsb(card->func, payload, card->ioport,
			  num_blocks * blksz);
	अगर (ret < 0) अणु
		BT_ERR("readsb failed: %d", ret);
		ret = -EIO;
		जाओ निकास;
	पूर्ण

	/* This is SDIO specअगरic header length: byte[2][1][0], type: byte[3]
	 * (HCI_COMMAND = 1, ACL_DATA = 2, SCO_DATA = 3, 0xFE = Venकरोr)
	 */

	buf_len = payload[0];
	buf_len |= payload[1] << 8;
	buf_len |= payload[2] << 16;

	अगर (buf_len > blksz * num_blocks) अणु
		BT_ERR("Skip incorrect packet: hdrlen %d buffer %d",
		       buf_len, blksz * num_blocks);
		ret = -EIO;
		जाओ निकास;
	पूर्ण

	type = payload[3];

	चयन (type) अणु
	हाल HCI_ACLDATA_PKT:
	हाल HCI_SCODATA_PKT:
	हाल HCI_EVENT_PKT:
		hci_skb_pkt_type(skb) = type;
		skb_put(skb, buf_len);
		skb_pull(skb, SDIO_HEADER_LEN);

		अगर (type == HCI_EVENT_PKT) अणु
			अगर (bपंचांगrvl_check_evtpkt(priv, skb))
				hci_recv_frame(hdev, skb);
		पूर्ण अन्यथा अणु
			hci_recv_frame(hdev, skb);
		पूर्ण

		hdev->stat.byte_rx += buf_len;
		अवरोध;

	हाल MRVL_VENDOR_PKT:
		hci_skb_pkt_type(skb) = HCI_VENDOR_PKT;
		skb_put(skb, buf_len);
		skb_pull(skb, SDIO_HEADER_LEN);

		अगर (bपंचांगrvl_process_event(priv, skb))
			hci_recv_frame(hdev, skb);

		hdev->stat.byte_rx += buf_len;
		अवरोध;

	शेष:
		BT_ERR("Unknown packet type:%d", type);
		BT_ERR("hex: %*ph", blksz * num_blocks, payload);

		kमुक्त_skb(skb);
		skb = शून्य;
		अवरोध;
	पूर्ण

निकास:
	अगर (ret) अणु
		hdev->stat.err_rx++;
		kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_process_पूर्णांक_status(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	uदीर्घ flags;
	u8 ireg;
	काष्ठा bपंचांगrvl_sdio_card *card = priv->bपंचांगrvl_dev.card;

	spin_lock_irqsave(&priv->driver_lock, flags);
	ireg = sdio_ireg;
	sdio_ireg = 0;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	sdio_claim_host(card->func);
	अगर (ireg & DN_LD_HOST_INT_STATUS) अणु
		अगर (priv->bपंचांगrvl_dev.tx_dnld_rdy)
			BT_DBG("tx_done already received: "
				" int_status=0x%x", ireg);
		अन्यथा
			priv->bपंचांगrvl_dev.tx_dnld_rdy = true;
	पूर्ण

	अगर (ireg & UP_LD_HOST_INT_STATUS)
		bपंचांगrvl_sdio_card_to_host(priv);

	sdio_release_host(card->func);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_पढ़ो_to_clear(काष्ठा bपंचांगrvl_sdio_card *card, u8 *ireg)
अणु
	काष्ठा bपंचांगrvl_adapter *adapter = card->priv->adapter;
	पूर्णांक ret;

	ret = sdio_पढ़ोsb(card->func, adapter->hw_regs, 0, SDIO_BLOCK_SIZE);
	अगर (ret) अणु
		BT_ERR("sdio_readsb: read int hw_regs failed: %d", ret);
		वापस ret;
	पूर्ण

	*ireg = adapter->hw_regs[card->reg->host_पूर्णांकstatus];
	BT_DBG("hw_regs[%#x]=%#x", card->reg->host_पूर्णांकstatus, *ireg);

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_ग_लिखो_to_clear(काष्ठा bपंचांगrvl_sdio_card *card, u8 *ireg)
अणु
	पूर्णांक ret;

	*ireg = sdio_पढ़ोb(card->func, card->reg->host_पूर्णांकstatus, &ret);
	अगर (ret) अणु
		BT_ERR("sdio_readb: read int status failed: %d", ret);
		वापस ret;
	पूर्ण

	अगर (*ireg) अणु
		/*
		 * DN_LD_HOST_INT_STATUS and/or UP_LD_HOST_INT_STATUS
		 * Clear the पूर्णांकerrupt status रेजिस्टर and re-enable the
		 * पूर्णांकerrupt.
		 */
		BT_DBG("int_status = 0x%x", *ireg);

		sdio_ग_लिखोb(card->func, ~(*ireg) & (DN_LD_HOST_INT_STATUS |
						    UP_LD_HOST_INT_STATUS),
			    card->reg->host_पूर्णांकstatus, &ret);
		अगर (ret) अणु
			BT_ERR("sdio_writeb: clear int status failed: %d", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bपंचांगrvl_sdio_पूर्णांकerrupt(काष्ठा sdio_func *func)
अणु
	काष्ठा bपंचांगrvl_निजी *priv;
	काष्ठा bपंचांगrvl_sdio_card *card;
	uदीर्घ flags;
	u8 ireg = 0;
	पूर्णांक ret;

	card = sdio_get_drvdata(func);
	अगर (!card || !card->priv) अणु
		BT_ERR("sbi_interrupt(%p) card or priv is NULL, card=%p",
		       func, card);
		वापस;
	पूर्ण

	priv = card->priv;

	अगर (priv->surprise_हटाओd)
		वापस;

	अगर (card->reg->पूर्णांक_पढ़ो_to_clear)
		ret = bपंचांगrvl_sdio_पढ़ो_to_clear(card, &ireg);
	अन्यथा
		ret = bपंचांगrvl_sdio_ग_लिखो_to_clear(card, &ireg);

	अगर (ret)
		वापस;

	spin_lock_irqsave(&priv->driver_lock, flags);
	sdio_ireg |= ireg;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	bपंचांगrvl_पूर्णांकerrupt(priv);
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_रेजिस्टर_dev(काष्ठा bपंचांगrvl_sdio_card *card)
अणु
	काष्ठा sdio_func *func;
	u8 reg;
	पूर्णांक ret;

	अगर (!card || !card->func) अणु
		BT_ERR("Error: card or function is NULL!");
		ret = -EINVAL;
		जाओ failed;
	पूर्ण

	func = card->func;

	sdio_claim_host(func);

	ret = sdio_enable_func(func);
	अगर (ret) अणु
		BT_ERR("sdio_enable_func() failed: ret=%d", ret);
		ret = -EIO;
		जाओ release_host;
	पूर्ण

	ret = sdio_claim_irq(func, bपंचांगrvl_sdio_पूर्णांकerrupt);
	अगर (ret) अणु
		BT_ERR("sdio_claim_irq failed: ret=%d", ret);
		ret = -EIO;
		जाओ disable_func;
	पूर्ण

	ret = sdio_set_block_size(card->func, SDIO_BLOCK_SIZE);
	अगर (ret) अणु
		BT_ERR("cannot set SDIO block size");
		ret = -EIO;
		जाओ release_irq;
	पूर्ण

	reg = sdio_पढ़ोb(func, card->reg->io_port_0, &ret);
	अगर (ret < 0) अणु
		ret = -EIO;
		जाओ release_irq;
	पूर्ण

	card->ioport = reg;

	reg = sdio_पढ़ोb(func, card->reg->io_port_1, &ret);
	अगर (ret < 0) अणु
		ret = -EIO;
		जाओ release_irq;
	पूर्ण

	card->ioport |= (reg << 8);

	reg = sdio_पढ़ोb(func, card->reg->io_port_2, &ret);
	अगर (ret < 0) अणु
		ret = -EIO;
		जाओ release_irq;
	पूर्ण

	card->ioport |= (reg << 16);

	BT_DBG("SDIO FUNC%d IO port: 0x%x", func->num, card->ioport);

	अगर (card->reg->पूर्णांक_पढ़ो_to_clear) अणु
		reg = sdio_पढ़ोb(func, card->reg->host_पूर्णांक_rsr, &ret);
		अगर (ret < 0) अणु
			ret = -EIO;
			जाओ release_irq;
		पूर्ण
		sdio_ग_लिखोb(func, reg | 0x3f, card->reg->host_पूर्णांक_rsr, &ret);
		अगर (ret < 0) अणु
			ret = -EIO;
			जाओ release_irq;
		पूर्ण

		reg = sdio_पढ़ोb(func, card->reg->card_misc_cfg, &ret);
		अगर (ret < 0) अणु
			ret = -EIO;
			जाओ release_irq;
		पूर्ण
		sdio_ग_लिखोb(func, reg | 0x10, card->reg->card_misc_cfg, &ret);
		अगर (ret < 0) अणु
			ret = -EIO;
			जाओ release_irq;
		पूर्ण
	पूर्ण

	sdio_set_drvdata(func, card);

	sdio_release_host(func);

	वापस 0;

release_irq:
	sdio_release_irq(func);

disable_func:
	sdio_disable_func(func);

release_host:
	sdio_release_host(func);

failed:
	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_unरेजिस्टर_dev(काष्ठा bपंचांगrvl_sdio_card *card)
अणु
	अगर (card && card->func) अणु
		sdio_claim_host(card->func);
		sdio_release_irq(card->func);
		sdio_disable_func(card->func);
		sdio_release_host(card->func);
		sdio_set_drvdata(card->func, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_enable_host_पूर्णांक(काष्ठा bपंचांगrvl_sdio_card *card)
अणु
	पूर्णांक ret;

	अगर (!card || !card->func)
		वापस -EINVAL;

	sdio_claim_host(card->func);

	ret = bपंचांगrvl_sdio_enable_host_पूर्णांक_mask(card, HIM_ENABLE);

	bपंचांगrvl_sdio_get_rx_unit(card);

	sdio_release_host(card->func);

	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_disable_host_पूर्णांक(काष्ठा bपंचांगrvl_sdio_card *card)
अणु
	पूर्णांक ret;

	अगर (!card || !card->func)
		वापस -EINVAL;

	sdio_claim_host(card->func);

	ret = bपंचांगrvl_sdio_disable_host_पूर्णांक_mask(card, HIM_DISABLE);

	sdio_release_host(card->func);

	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_host_to_card(काष्ठा bपंचांगrvl_निजी *priv,
				u8 *payload, u16 nb)
अणु
	काष्ठा bपंचांगrvl_sdio_card *card = priv->bपंचांगrvl_dev.card;
	पूर्णांक ret = 0;
	पूर्णांक blksz;
	पूर्णांक i = 0;
	u8 *buf = शून्य;
	व्योम *पंचांगpbuf = शून्य;
	पूर्णांक पंचांगpbufsz;

	अगर (!card || !card->func) अणु
		BT_ERR("card or function is NULL!");
		वापस -EINVAL;
	पूर्ण

	blksz = DIV_ROUND_UP(nb, SDIO_BLOCK_SIZE) * SDIO_BLOCK_SIZE;

	buf = payload;
	अगर ((अचिन्हित दीर्घ) payload & (BTSDIO_DMA_ALIGN - 1) ||
	    nb < blksz) अणु
		पंचांगpbufsz = ALIGN_SZ(blksz, BTSDIO_DMA_ALIGN) +
			   BTSDIO_DMA_ALIGN;
		पंचांगpbuf = kzalloc(पंचांगpbufsz, GFP_KERNEL);
		अगर (!पंचांगpbuf)
			वापस -ENOMEM;
		buf = (u8 *) ALIGN_ADDR(पंचांगpbuf, BTSDIO_DMA_ALIGN);
		स_नकल(buf, payload, nb);
	पूर्ण

	sdio_claim_host(card->func);

	करो अणु
		/* Transfer data to card */
		ret = sdio_ग_लिखोsb(card->func, card->ioport, buf,
				   blksz);
		अगर (ret < 0) अणु
			i++;
			BT_ERR("i=%d writesb failed: %d", i, ret);
			BT_ERR("hex: %*ph", nb, payload);
			ret = -EIO;
			अगर (i > MAX_WRITE_IOMEM_RETRY)
				जाओ निकास;
		पूर्ण
	पूर्ण जबतक (ret);

	priv->bपंचांगrvl_dev.tx_dnld_rdy = false;

निकास:
	sdio_release_host(card->func);
	kमुक्त(पंचांगpbuf);

	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_करोwnload_fw(काष्ठा bपंचांगrvl_sdio_card *card)
अणु
	पूर्णांक ret;
	u8 fws0;
	पूर्णांक pollnum = MAX_POLL_TRIES;

	अगर (!card || !card->func) अणु
		BT_ERR("card or function is NULL!");
		वापस -EINVAL;
	पूर्ण

	अगर (!bपंचांगrvl_sdio_verअगरy_fw_करोwnload(card, 1)) अणु
		BT_DBG("Firmware already downloaded!");
		वापस 0;
	पूर्ण

	sdio_claim_host(card->func);

	/* Check अगर other function driver is करोwnloading the firmware */
	fws0 = sdio_पढ़ोb(card->func, card->reg->card_fw_status0, &ret);
	अगर (ret) अणु
		BT_ERR("Failed to read FW downloading status!");
		ret = -EIO;
		जाओ करोne;
	पूर्ण
	अगर (fws0) अणु
		BT_DBG("BT not the winner (%#x). Skip FW downloading", fws0);

		/* Give other function more समय to करोwnload the firmware */
		pollnum *= 10;
	पूर्ण अन्यथा अणु
		अगर (card->helper) अणु
			ret = bपंचांगrvl_sdio_करोwnload_helper(card);
			अगर (ret) अणु
				BT_ERR("Failed to download helper!");
				ret = -EIO;
				जाओ करोne;
			पूर्ण
		पूर्ण

		अगर (bपंचांगrvl_sdio_करोwnload_fw_w_helper(card)) अणु
			BT_ERR("Failed to download firmware!");
			ret = -EIO;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/*
	 * winner or not, with this test the FW synchronizes when the
	 * module can जारी its initialization
	 */
	अगर (bपंचांगrvl_sdio_verअगरy_fw_करोwnload(card, pollnum)) अणु
		BT_ERR("FW failed to be active in time!");
		ret = -ETIMEDOUT;
		जाओ करोne;
	पूर्ण

	sdio_release_host(card->func);

	वापस 0;

करोne:
	sdio_release_host(card->func);
	वापस ret;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_wakeup_fw(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	काष्ठा bपंचांगrvl_sdio_card *card = priv->bपंचांगrvl_dev.card;
	पूर्णांक ret = 0;

	अगर (!card || !card->func) अणु
		BT_ERR("card or function is NULL!");
		वापस -EINVAL;
	पूर्ण

	sdio_claim_host(card->func);

	sdio_ग_लिखोb(card->func, HOST_POWER_UP, card->reg->cfg, &ret);

	sdio_release_host(card->func);

	BT_DBG("wake up firmware");

	वापस ret;
पूर्ण

अटल व्योम bपंचांगrvl_sdio_dump_regs(काष्ठा bपंचांगrvl_निजी *priv)
अणु
	काष्ठा bपंचांगrvl_sdio_card *card = priv->bपंचांगrvl_dev.card;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक reg, reg_start, reg_end;
	अक्षर buf[256], *ptr;
	u8 loop, func, data;
	पूर्णांक MAX_LOOP = 2;

	bपंचांगrvl_sdio_wakeup_fw(priv);
	sdio_claim_host(card->func);

	क्रम (loop = 0; loop < MAX_LOOP; loop++) अणु
		स_रखो(buf, 0, माप(buf));
		ptr = buf;

		अगर (loop == 0) अणु
			/* Read the रेजिस्टरs of SDIO function0 */
			func = loop;
			reg_start = 0;
			reg_end = 9;
		पूर्ण अन्यथा अणु
			func = 2;
			reg_start = 0;
			reg_end = 0x09;
		पूर्ण

		ptr += प्र_लिखो(ptr, "SDIO Func%d (%#x-%#x): ",
			       func, reg_start, reg_end);
		क्रम (reg = reg_start; reg <= reg_end; reg++) अणु
			अगर (func == 0)
				data = sdio_f0_पढ़ोb(card->func, reg, &ret);
			अन्यथा
				data = sdio_पढ़ोb(card->func, reg, &ret);

			अगर (!ret) अणु
				ptr += प्र_लिखो(ptr, "%02x ", data);
			पूर्ण अन्यथा अणु
				ptr += प्र_लिखो(ptr, "ERR");
				अवरोध;
			पूर्ण
		पूर्ण

		BT_INFO("%s", buf);
	पूर्ण

	sdio_release_host(card->func);
पूर्ण

/* This function पढ़ो/ग_लिखो firmware */
अटल क्रमागत
rdwr_status bपंचांगrvl_sdio_rdwr_firmware(काष्ठा bपंचांगrvl_निजी *priv,
				      u8 करोneflag)
अणु
	काष्ठा bपंचांगrvl_sdio_card *card = priv->bपंचांगrvl_dev.card;
	पूर्णांक ret, tries;
	u8 ctrl_data = 0;

	sdio_ग_लिखोb(card->func, FW_DUMP_HOST_READY, card->reg->fw_dump_ctrl,
		    &ret);

	अगर (ret) अणु
		BT_ERR("SDIO write err");
		वापस RDWR_STATUS_FAILURE;
	पूर्ण

	क्रम (tries = 0; tries < MAX_POLL_TRIES; tries++) अणु
		ctrl_data = sdio_पढ़ोb(card->func, card->reg->fw_dump_ctrl,
				       &ret);

		अगर (ret) अणु
			BT_ERR("SDIO read err");
			वापस RDWR_STATUS_FAILURE;
		पूर्ण

		अगर (ctrl_data == FW_DUMP_DONE)
			अवरोध;
		अगर (करोneflag && ctrl_data == करोneflag)
			वापस RDWR_STATUS_DONE;
		अगर (ctrl_data != FW_DUMP_HOST_READY) अणु
			BT_INFO("The ctrl reg was changed, re-try again!");
			sdio_ग_लिखोb(card->func, FW_DUMP_HOST_READY,
				    card->reg->fw_dump_ctrl, &ret);
			अगर (ret) अणु
				BT_ERR("SDIO write err");
				वापस RDWR_STATUS_FAILURE;
			पूर्ण
		पूर्ण
		usleep_range(100, 200);
	पूर्ण

	अगर (ctrl_data == FW_DUMP_HOST_READY) अणु
		BT_ERR("Fail to pull ctrl_data");
		वापस RDWR_STATUS_FAILURE;
	पूर्ण

	वापस RDWR_STATUS_SUCCESS;
पूर्ण

/* This function dump sdio रेजिस्टर and memory data */
अटल व्योम bपंचांगrvl_sdio_coredump(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा bपंचांगrvl_sdio_card *card;
	काष्ठा bपंचांगrvl_निजी *priv;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक reg, reg_start, reg_end;
	क्रमागत rdwr_status stat;
	u8 *dbg_ptr, *end_ptr, *fw_dump_data, *fw_dump_ptr;
	u8 dump_num = 0, idx, i, पढ़ो_reg, करोneflag = 0;
	u32 memory_size, fw_dump_len = 0;

	card = sdio_get_drvdata(func);
	priv = card->priv;

	/* dump sdio रेजिस्टर first */
	bपंचांगrvl_sdio_dump_regs(priv);

	अगर (!card->supports_fw_dump) अणु
		BT_ERR("Firmware dump not supported for this card!");
		वापस;
	पूर्ण

	क्रम (idx = 0; idx < ARRAY_SIZE(mem_type_mapping_tbl); idx++) अणु
		काष्ठा memory_type_mapping *entry = &mem_type_mapping_tbl[idx];

		अगर (entry->mem_ptr) अणु
			vमुक्त(entry->mem_ptr);
			entry->mem_ptr = शून्य;
		पूर्ण
		entry->mem_size = 0;
	पूर्ण

	bपंचांगrvl_sdio_wakeup_fw(priv);
	sdio_claim_host(card->func);

	BT_INFO("== btmrvl firmware dump start ==");

	stat = bपंचांगrvl_sdio_rdwr_firmware(priv, करोneflag);
	अगर (stat == RDWR_STATUS_FAILURE)
		जाओ करोne;

	reg = card->reg->fw_dump_start;
	/* Read the number of the memories which will dump */
	dump_num = sdio_पढ़ोb(card->func, reg, &ret);

	अगर (ret) अणु
		BT_ERR("SDIO read memory length err");
		जाओ करोne;
	पूर्ण

	/* Read the length of every memory which will dump */
	क्रम (idx = 0; idx < dump_num; idx++) अणु
		काष्ठा memory_type_mapping *entry = &mem_type_mapping_tbl[idx];

		stat = bपंचांगrvl_sdio_rdwr_firmware(priv, करोneflag);
		अगर (stat == RDWR_STATUS_FAILURE)
			जाओ करोne;

		memory_size = 0;
		reg = card->reg->fw_dump_start;
		क्रम (i = 0; i < 4; i++) अणु
			पढ़ो_reg = sdio_पढ़ोb(card->func, reg, &ret);
			अगर (ret) अणु
				BT_ERR("SDIO read err");
				जाओ करोne;
			पूर्ण
			memory_size |= (पढ़ो_reg << i*8);
			reg++;
		पूर्ण

		अगर (memory_size == 0) अणु
			BT_INFO("Firmware dump finished!");
			sdio_ग_लिखोb(card->func, FW_DUMP_READ_DONE,
				    card->reg->fw_dump_ctrl, &ret);
			अगर (ret) अणु
				BT_ERR("SDIO Write MEMDUMP_FINISH ERR");
				जाओ करोne;
			पूर्ण
			अवरोध;
		पूर्ण

		BT_INFO("%s_SIZE=0x%x", entry->mem_name, memory_size);
		entry->mem_ptr = vzalloc(memory_size + 1);
		entry->mem_size = memory_size;
		अगर (!entry->mem_ptr) अणु
			BT_ERR("Vzalloc %s failed", entry->mem_name);
			जाओ करोne;
		पूर्ण

		fw_dump_len += (म_माप("========Start dump ") +
				म_माप(entry->mem_name) +
				म_माप("========\n") +
				(memory_size + 1) +
				म_माप("\n========End dump========\n"));

		dbg_ptr = entry->mem_ptr;
		end_ptr = dbg_ptr + memory_size;

		करोneflag = entry->करोne_flag;
		BT_INFO("Start %s output, please wait...",
			entry->mem_name);

		करो अणु
			stat = bपंचांगrvl_sdio_rdwr_firmware(priv, करोneflag);
			अगर (stat == RDWR_STATUS_FAILURE)
				जाओ करोne;

			reg_start = card->reg->fw_dump_start;
			reg_end = card->reg->fw_dump_end;
			क्रम (reg = reg_start; reg <= reg_end; reg++) अणु
				*dbg_ptr = sdio_पढ़ोb(card->func, reg, &ret);
				अगर (ret) अणु
					BT_ERR("SDIO read err");
					जाओ करोne;
				पूर्ण
				अगर (dbg_ptr < end_ptr)
					dbg_ptr++;
				अन्यथा
					BT_ERR("Allocated buffer not enough");
			पूर्ण

			अगर (stat != RDWR_STATUS_DONE) अणु
				जारी;
			पूर्ण अन्यथा अणु
				BT_INFO("%s done: size=0x%tx",
					entry->mem_name,
					dbg_ptr - entry->mem_ptr);
				अवरोध;
			पूर्ण
		पूर्ण जबतक (1);
	पूर्ण

	BT_INFO("== btmrvl firmware dump end ==");

करोne:
	sdio_release_host(card->func);

	अगर (fw_dump_len == 0)
		वापस;

	fw_dump_data = vzalloc(fw_dump_len+1);
	अगर (!fw_dump_data) अणु
		BT_ERR("Vzalloc fw_dump_data fail!");
		वापस;
	पूर्ण
	fw_dump_ptr = fw_dump_data;

	/* Dump all the memory data पूर्णांकo single file, a userspace script will
	 * be used to split all the memory data to multiple files
	 */
	BT_INFO("== btmrvl firmware dump to /sys/class/devcoredump start");
	क्रम (idx = 0; idx < dump_num; idx++) अणु
		काष्ठा memory_type_mapping *entry = &mem_type_mapping_tbl[idx];

		अगर (entry->mem_ptr) अणु
			म_नकल(fw_dump_ptr, "========Start dump ");
			fw_dump_ptr += म_माप("========Start dump ");

			म_नकल(fw_dump_ptr, entry->mem_name);
			fw_dump_ptr += म_माप(entry->mem_name);

			म_नकल(fw_dump_ptr, "========\n");
			fw_dump_ptr += म_माप("========\n");

			स_नकल(fw_dump_ptr, entry->mem_ptr, entry->mem_size);
			fw_dump_ptr += entry->mem_size;

			म_नकल(fw_dump_ptr, "\n========End dump========\n");
			fw_dump_ptr += म_माप("\n========End dump========\n");

			vमुक्त(mem_type_mapping_tbl[idx].mem_ptr);
			mem_type_mapping_tbl[idx].mem_ptr = शून्य;
		पूर्ण
	पूर्ण

	/* fw_dump_data will be मुक्त in device coredump release function
	 * after 5 min
	 */
	dev_coredumpv(&card->func->dev, fw_dump_data, fw_dump_len, GFP_KERNEL);
	BT_INFO("== btmrvl firmware dump to /sys/class/devcoredump end");
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_probe(काष्ठा sdio_func *func,
					स्थिर काष्ठा sdio_device_id *id)
अणु
	पूर्णांक ret = 0;
	काष्ठा bपंचांगrvl_निजी *priv = शून्य;
	काष्ठा bपंचांगrvl_sdio_card *card = शून्य;

	BT_INFO("vendor=0x%x, device=0x%x, class=%d, fn=%d",
			id->venकरोr, id->device, id->class, func->num);

	card = devm_kzalloc(&func->dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	card->func = func;

	अगर (id->driver_data) अणु
		काष्ठा bपंचांगrvl_sdio_device *data = (व्योम *) id->driver_data;
		card->helper = data->helper;
		card->firmware = data->firmware;
		card->reg = data->reg;
		card->sd_blksz_fw_dl = data->sd_blksz_fw_dl;
		card->support_pscan_win_report = data->support_pscan_win_report;
		card->supports_fw_dump = data->supports_fw_dump;
	पूर्ण

	अगर (bपंचांगrvl_sdio_रेजिस्टर_dev(card) < 0) अणु
		BT_ERR("Failed to register BT device!");
		वापस -ENODEV;
	पूर्ण

	/* Disable the पूर्णांकerrupts on the card */
	bपंचांगrvl_sdio_disable_host_पूर्णांक(card);

	अगर (bपंचांगrvl_sdio_करोwnload_fw(card)) अणु
		BT_ERR("Downloading firmware failed!");
		ret = -ENODEV;
		जाओ unreg_dev;
	पूर्ण

	bपंचांगrvl_sdio_enable_host_पूर्णांक(card);

	/* Device tree node parsing and platक्रमm specअगरic configuration*/
	bपंचांगrvl_sdio_probe_of(&func->dev, card);

	priv = bपंचांगrvl_add_card(card);
	अगर (!priv) अणु
		BT_ERR("Initializing card failed!");
		ret = -ENODEV;
		जाओ disable_host_पूर्णांक;
	पूर्ण

	card->priv = priv;

	/* Initialize the पूर्णांकerface specअगरic function poपूर्णांकers */
	priv->hw_host_to_card = bपंचांगrvl_sdio_host_to_card;
	priv->hw_wakeup_firmware = bपंचांगrvl_sdio_wakeup_fw;
	priv->hw_process_पूर्णांक_status = bपंचांगrvl_sdio_process_पूर्णांक_status;

	अगर (bपंचांगrvl_रेजिस्टर_hdev(priv)) अणु
		BT_ERR("Register hdev failed!");
		ret = -ENODEV;
		जाओ disable_host_पूर्णांक;
	पूर्ण

	वापस 0;

disable_host_पूर्णांक:
	bपंचांगrvl_sdio_disable_host_पूर्णांक(card);
unreg_dev:
	bपंचांगrvl_sdio_unरेजिस्टर_dev(card);
	वापस ret;
पूर्ण

अटल व्योम bपंचांगrvl_sdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा bपंचांगrvl_sdio_card *card;

	अगर (func) अणु
		card = sdio_get_drvdata(func);
		अगर (card) अणु
			/* Send SHUTDOWN command & disable पूर्णांकerrupt
			 * अगर user हटाओs the module.
			 */
			अगर (user_rmmod) अणु
				bपंचांगrvl_send_module_cfg_cmd(card->priv,
							MODULE_SHUTDOWN_REQ);
				bपंचांगrvl_sdio_disable_host_पूर्णांक(card);
			पूर्ण

			BT_DBG("unregister dev");
			card->priv->surprise_हटाओd = true;
			bपंचांगrvl_sdio_unरेजिस्टर_dev(card);
			bपंचांगrvl_हटाओ_card(card->priv);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा bपंचांगrvl_sdio_card *card;
	काष्ठा bपंचांगrvl_निजी *priv;
	mmc_pm_flag_t pm_flags;
	काष्ठा hci_dev *hcidev;

	अगर (func) अणु
		pm_flags = sdio_get_host_pm_caps(func);
		BT_DBG("%s: suspend: PM flags = 0x%x", sdio_func_id(func),
		       pm_flags);
		अगर (!(pm_flags & MMC_PM_KEEP_POWER)) अणु
			BT_ERR("%s: cannot remain alive while suspended",
			       sdio_func_id(func));
			वापस -ENOSYS;
		पूर्ण
		card = sdio_get_drvdata(func);
		अगर (!card || !card->priv) अणु
			BT_ERR("card or priv structure is not valid");
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		BT_ERR("sdio_func is not specified");
		वापस 0;
	पूर्ण

	/* Enable platक्रमm specअगरic wakeup पूर्णांकerrupt */
	अगर (card->plt_wake_cfg && card->plt_wake_cfg->irq_bt >= 0 &&
	    device_may_wakeup(dev)) अणु
		card->plt_wake_cfg->wake_by_bt = false;
		enable_irq(card->plt_wake_cfg->irq_bt);
		enable_irq_wake(card->plt_wake_cfg->irq_bt);
	पूर्ण

	priv = card->priv;
	priv->adapter->is_suspending = true;
	hcidev = priv->bपंचांगrvl_dev.hcidev;
	BT_DBG("%s: SDIO suspend", hcidev->name);
	hci_suspend_dev(hcidev);

	अगर (priv->adapter->hs_state != HS_ACTIVATED) अणु
		अगर (bपंचांगrvl_enable_hs(priv)) अणु
			BT_ERR("HS not activated, suspend failed!");
			/* Disable platक्रमm specअगरic wakeup पूर्णांकerrupt */
			अगर (card->plt_wake_cfg &&
			    card->plt_wake_cfg->irq_bt >= 0 &&
			    device_may_wakeup(dev)) अणु
				disable_irq_wake(card->plt_wake_cfg->irq_bt);
				disable_irq(card->plt_wake_cfg->irq_bt);
			पूर्ण

			priv->adapter->is_suspending = false;
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	priv->adapter->is_suspending = false;
	priv->adapter->is_suspended = true;

	/* We will keep the घातer when hs enabled successfully */
	अगर (priv->adapter->hs_state == HS_ACTIVATED) अणु
		BT_DBG("suspend with MMC_PM_KEEP_POWER");
		वापस sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);
	पूर्ण

	BT_DBG("suspend without MMC_PM_KEEP_POWER");
	वापस 0;
पूर्ण

अटल पूर्णांक bपंचांगrvl_sdio_resume(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा bपंचांगrvl_sdio_card *card;
	काष्ठा bपंचांगrvl_निजी *priv;
	mmc_pm_flag_t pm_flags;
	काष्ठा hci_dev *hcidev;

	अगर (func) अणु
		pm_flags = sdio_get_host_pm_caps(func);
		BT_DBG("%s: resume: PM flags = 0x%x", sdio_func_id(func),
		       pm_flags);
		card = sdio_get_drvdata(func);
		अगर (!card || !card->priv) अणु
			BT_ERR("card or priv structure is not valid");
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		BT_ERR("sdio_func is not specified");
		वापस 0;
	पूर्ण
	priv = card->priv;

	अगर (!priv->adapter->is_suspended) अणु
		BT_DBG("device already resumed");
		वापस 0;
	पूर्ण

	priv->hw_wakeup_firmware(priv);
	priv->adapter->hs_state = HS_DEACTIVATED;
	hcidev = priv->bपंचांगrvl_dev.hcidev;
	BT_DBG("%s: HS DEACTIVATED in resume!", hcidev->name);
	priv->adapter->is_suspended = false;
	BT_DBG("%s: SDIO resume", hcidev->name);
	hci_resume_dev(hcidev);

	/* Disable platक्रमm specअगरic wakeup पूर्णांकerrupt */
	अगर (card->plt_wake_cfg && card->plt_wake_cfg->irq_bt >= 0 &&
	    device_may_wakeup(dev)) अणु
		disable_irq_wake(card->plt_wake_cfg->irq_bt);
		disable_irq(card->plt_wake_cfg->irq_bt);
		अगर (card->plt_wake_cfg->wake_by_bt)
			/* Unकरो our disable, since पूर्णांकerrupt handler alपढ़ोy
			 * did this.
			 */
			enable_irq(card->plt_wake_cfg->irq_bt);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops bपंचांगrvl_sdio_pm_ops = अणु
	.suspend	= bपंचांगrvl_sdio_suspend,
	.resume		= bपंचांगrvl_sdio_resume,
पूर्ण;

अटल काष्ठा sdio_driver bt_mrvl_sdio = अणु
	.name		= "btmrvl_sdio",
	.id_table	= bपंचांगrvl_sdio_ids,
	.probe		= bपंचांगrvl_sdio_probe,
	.हटाओ		= bपंचांगrvl_sdio_हटाओ,
	.drv = अणु
		.owner = THIS_MODULE,
		.coredump = bपंचांगrvl_sdio_coredump,
		.pm = &bपंचांगrvl_sdio_pm_ops,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init bपंचांगrvl_sdio_init_module(व्योम)
अणु
	अगर (sdio_रेजिस्टर_driver(&bt_mrvl_sdio) != 0) अणु
		BT_ERR("SDIO Driver Registration Failed");
		वापस -ENODEV;
	पूर्ण

	/* Clear the flag in हाल user हटाओs the card. */
	user_rmmod = 0;

	वापस 0;
पूर्ण

अटल व्योम __निकास bपंचांगrvl_sdio_निकास_module(व्योम)
अणु
	/* Set the flag as user is removing this module. */
	user_rmmod = 1;

	sdio_unरेजिस्टर_driver(&bt_mrvl_sdio);
पूर्ण

module_init(bपंचांगrvl_sdio_init_module);
module_निकास(bपंचांगrvl_sdio_निकास_module);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell BT-over-SDIO driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL v2");
MODULE_FIRMWARE("mrvl/sd8688_helper.bin");
MODULE_FIRMWARE("mrvl/sd8688.bin");
MODULE_FIRMWARE("mrvl/sd8787_uapsta.bin");
MODULE_FIRMWARE("mrvl/sd8797_uapsta.bin");
MODULE_FIRMWARE("mrvl/sd8887_uapsta.bin");
MODULE_FIRMWARE("mrvl/sd8897_uapsta.bin");
MODULE_FIRMWARE("mrvl/sdsd8977_combo_v2.bin");
MODULE_FIRMWARE("mrvl/sd8987_uapsta.bin");
MODULE_FIRMWARE("mrvl/sdsd8997_combo_v4.bin");
