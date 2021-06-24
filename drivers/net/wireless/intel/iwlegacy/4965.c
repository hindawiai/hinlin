<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2003 - 2011 Intel Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/units.h>
#समावेश <net/mac80211.h>
#समावेश <linux/etherdevice.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "common.h"
#समावेश "4965.h"

/*
 * il_verअगरy_inst_sparse - verअगरy runसमय uCode image in card vs. host,
 *   using sample data 100 bytes apart.  If these sample poपूर्णांकs are good,
 *   it's a pretty good bet that everything between them is good, too.
 */
अटल पूर्णांक
il4965_verअगरy_inst_sparse(काष्ठा il_priv *il, __le32 * image, u32 len)
अणु
	u32 val;
	पूर्णांक ret = 0;
	u32 errcnt = 0;
	u32 i;

	D_INFO("ucode inst image size is %u\n", len);

	क्रम (i = 0; i < len; i += 100, image += 100 / माप(u32)) अणु
		/* पढ़ो data comes through single port, स्वतः-incr addr */
		/* NOTE: Use the debugless पढ़ो so we करोn't flood kernel log
		 * अगर IL_DL_IO is set */
		il_wr(il, HBUS_TARG_MEM_RADDR, i + IL4965_RTC_INST_LOWER_BOUND);
		val = _il_rd(il, HBUS_TARG_MEM_RDAT);
		अगर (val != le32_to_cpu(*image)) अणु
			ret = -EIO;
			errcnt++;
			अगर (errcnt >= 3)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * il4965_verअगरy_inst_full - verअगरy runसमय uCode image in card vs. host,
 *     looking at all data.
 */
अटल पूर्णांक
il4965_verअगरy_inst_full(काष्ठा il_priv *il, __le32 * image, u32 len)
अणु
	u32 val;
	u32 save_len = len;
	पूर्णांक ret = 0;
	u32 errcnt;

	D_INFO("ucode inst image size is %u\n", len);

	il_wr(il, HBUS_TARG_MEM_RADDR, IL4965_RTC_INST_LOWER_BOUND);

	errcnt = 0;
	क्रम (; len > 0; len -= माप(u32), image++) अणु
		/* पढ़ो data comes through single port, स्वतः-incr addr */
		/* NOTE: Use the debugless पढ़ो so we करोn't flood kernel log
		 * अगर IL_DL_IO is set */
		val = _il_rd(il, HBUS_TARG_MEM_RDAT);
		अगर (val != le32_to_cpu(*image)) अणु
			IL_ERR("uCode INST section is invalid at "
			       "offset 0x%x, is 0x%x, s/b 0x%x\n",
			       save_len - len, val, le32_to_cpu(*image));
			ret = -EIO;
			errcnt++;
			अगर (errcnt >= 20)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (!errcnt)
		D_INFO("ucode image in INSTRUCTION memory is good\n");

	वापस ret;
पूर्ण

/*
 * il4965_verअगरy_ucode - determine which inकाष्ठाion image is in SRAM,
 *    and verअगरy its contents
 */
पूर्णांक
il4965_verअगरy_ucode(काष्ठा il_priv *il)
अणु
	__le32 *image;
	u32 len;
	पूर्णांक ret;

	/* Try bootstrap */
	image = (__le32 *) il->ucode_boot.v_addr;
	len = il->ucode_boot.len;
	ret = il4965_verअगरy_inst_sparse(il, image, len);
	अगर (!ret) अणु
		D_INFO("Bootstrap uCode is good in inst SRAM\n");
		वापस 0;
	पूर्ण

	/* Try initialize */
	image = (__le32 *) il->ucode_init.v_addr;
	len = il->ucode_init.len;
	ret = il4965_verअगरy_inst_sparse(il, image, len);
	अगर (!ret) अणु
		D_INFO("Initialize uCode is good in inst SRAM\n");
		वापस 0;
	पूर्ण

	/* Try runसमय/protocol */
	image = (__le32 *) il->ucode_code.v_addr;
	len = il->ucode_code.len;
	ret = il4965_verअगरy_inst_sparse(il, image, len);
	अगर (!ret) अणु
		D_INFO("Runtime uCode is good in inst SRAM\n");
		वापस 0;
	पूर्ण

	IL_ERR("NO VALID UCODE IMAGE IN INSTRUCTION SRAM!!\n");

	/* Since nothing seems to match, show first several data entries in
	 * inकाष्ठाion SRAM, so maybe visual inspection will give a clue.
	 * Selection of bootstrap image (vs. other images) is arbitrary. */
	image = (__le32 *) il->ucode_boot.v_addr;
	len = il->ucode_boot.len;
	ret = il4965_verअगरy_inst_full(il, image, len);

	वापस ret;
पूर्ण

/******************************************************************************
 *
 * EEPROM related functions
 *
******************************************************************************/

/*
 * The device's EEPROM semaphore prevents conflicts between driver and uCode
 * when accessing the EEPROM; each access is a series of pulses to/from the
 * EEPROM chip, not a single event, so even पढ़ोs could conflict अगर they
 * weren't arbitrated by the semaphore.
 */
पूर्णांक
il4965_eeprom_acquire_semaphore(काष्ठा il_priv *il)
अणु
	u16 count;
	पूर्णांक ret;

	क्रम (count = 0; count < EEPROM_SEM_RETRY_LIMIT; count++) अणु
		/* Request semaphore */
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM);

		/* See अगर we got it */
		ret =
		    _il_poll_bit(il, CSR_HW_IF_CONFIG_REG,
				 CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM,
				 CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM,
				 EEPROM_SEM_TIMEOUT);
		अगर (ret >= 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

व्योम
il4965_eeprom_release_semaphore(काष्ठा il_priv *il)
अणु
	il_clear_bit(il, CSR_HW_IF_CONFIG_REG,
		     CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM);

पूर्ण

पूर्णांक
il4965_eeprom_check_version(काष्ठा il_priv *il)
अणु
	u16 eeprom_ver;
	u16 calib_ver;

	eeprom_ver = il_eeprom_query16(il, EEPROM_VERSION);
	calib_ver = il_eeprom_query16(il, EEPROM_4965_CALIB_VERSION_OFFSET);

	अगर (eeprom_ver < il->cfg->eeprom_ver ||
	    calib_ver < il->cfg->eeprom_calib_ver)
		जाओ err;

	IL_INFO("device EEPROM VER=0x%x, CALIB=0x%x\n", eeprom_ver, calib_ver);

	वापस 0;
err:
	IL_ERR("Unsupported (too old) EEPROM VER=0x%x < 0x%x "
	       "CALIB=0x%x < 0x%x\n", eeprom_ver, il->cfg->eeprom_ver,
	       calib_ver, il->cfg->eeprom_calib_ver);
	वापस -EINVAL;

पूर्ण

व्योम
il4965_eeprom_get_mac(स्थिर काष्ठा il_priv *il, u8 * mac)
अणु
	स्थिर u8 *addr = il_eeprom_query_addr(il,
					      EEPROM_MAC_ADDRESS);
	स_नकल(mac, addr, ETH_ALEN);
पूर्ण

/* Send led command */
अटल पूर्णांक
il4965_send_led_cmd(काष्ठा il_priv *il, काष्ठा il_led_cmd *led_cmd)
अणु
	काष्ठा il_host_cmd cmd = अणु
		.id = C_LEDS,
		.len = माप(काष्ठा il_led_cmd),
		.data = led_cmd,
		.flags = CMD_ASYNC,
		.callback = शून्य,
	पूर्ण;
	u32 reg;

	reg = _il_rd(il, CSR_LED_REG);
	अगर (reg != (reg & CSR_LED_BSM_CTRL_MSK))
		_il_wr(il, CSR_LED_REG, reg & CSR_LED_BSM_CTRL_MSK);

	वापस il_send_cmd(il, &cmd);
पूर्ण

/* Set led रेजिस्टर off */
व्योम
il4965_led_enable(काष्ठा il_priv *il)
अणु
	_il_wr(il, CSR_LED_REG, CSR_LED_REG_TRUN_ON);
पूर्ण

अटल पूर्णांक il4965_send_tx_घातer(काष्ठा il_priv *il);
अटल पूर्णांक il4965_hw_get_temperature(काष्ठा il_priv *il);

/* Highest firmware API version supported */
#घोषणा IL4965_UCODE_API_MAX 2

/* Lowest firmware API version supported */
#घोषणा IL4965_UCODE_API_MIN 2

#घोषणा IL4965_FW_PRE "iwlwifi-4965-"
#घोषणा _IL4965_MODULE_FIRMWARE(api) IL4965_FW_PRE #api ".ucode"
#घोषणा IL4965_MODULE_FIRMWARE(api) _IL4965_MODULE_FIRMWARE(api)

/* check contents of special bootstrap uCode SRAM */
अटल पूर्णांक
il4965_verअगरy_bsm(काष्ठा il_priv *il)
अणु
	__le32 *image = il->ucode_boot.v_addr;
	u32 len = il->ucode_boot.len;
	u32 reg;
	u32 val;

	D_INFO("Begin verify bsm\n");

	/* verअगरy BSM SRAM contents */
	val = il_rd_prph(il, BSM_WR_DWCOUNT_REG);
	क्रम (reg = BSM_SRAM_LOWER_BOUND; reg < BSM_SRAM_LOWER_BOUND + len;
	     reg += माप(u32), image++) अणु
		val = il_rd_prph(il, reg);
		अगर (val != le32_to_cpu(*image)) अणु
			IL_ERR("BSM uCode verification failed at "
			       "addr 0x%08X+%u (of %u), is 0x%x, s/b 0x%x\n",
			       BSM_SRAM_LOWER_BOUND, reg - BSM_SRAM_LOWER_BOUND,
			       len, val, le32_to_cpu(*image));
			वापस -EIO;
		पूर्ण
	पूर्ण

	D_INFO("BSM bootstrap uCode image OK\n");

	वापस 0;
पूर्ण

/*
 * il4965_load_bsm - Load bootstrap inकाष्ठाions
 *
 * BSM operation:
 *
 * The Bootstrap State Machine (BSM) stores a लघु bootstrap uCode program
 * in special SRAM that करोes not घातer करोwn during RFKILL.  When घातering back
 * up after घातer-saving sleeps (or during initial uCode load), the BSM loads
 * the bootstrap program पूर्णांकo the on-board processor, and starts it.
 *
 * The bootstrap program loads (via DMA) inकाष्ठाions and data क्रम a new
 * program from host DRAM locations indicated by the host driver in the
 * BSM_DRAM_* रेजिस्टरs.  Once the new program is loaded, it starts
 * स्वतःmatically.
 *
 * When initializing the NIC, the host driver poपूर्णांकs the BSM to the
 * "initialize" uCode image.  This uCode sets up some पूर्णांकernal data, then
 * notअगरies host via "initialize alive" that it is complete.
 *
 * The host then replaces the BSM_DRAM_* poपूर्णांकer values to poपूर्णांक to the
 * normal runसमय uCode inकाष्ठाions and a backup uCode data cache buffer
 * (filled initially with starting data values क्रम the on-board processor),
 * then triggers the "initialize" uCode to load and launch the runसमय uCode,
 * which begins normal operation.
 *
 * When करोing a घातer-save shutकरोwn, runसमय uCode saves data SRAM पूर्णांकo
 * the backup data cache in DRAM beक्रमe SRAM is घातered करोwn.
 *
 * When घातering back up, the BSM loads the bootstrap program.  This reloads
 * the runसमय uCode inकाष्ठाions and the backup data cache पूर्णांकo SRAM,
 * and re-launches the runसमय uCode from where it left off.
 */
अटल पूर्णांक
il4965_load_bsm(काष्ठा il_priv *il)
अणु
	__le32 *image = il->ucode_boot.v_addr;
	u32 len = il->ucode_boot.len;
	dma_addr_t pinst;
	dma_addr_t pdata;
	u32 inst_len;
	u32 data_len;
	पूर्णांक i;
	u32 करोne;
	u32 reg_offset;
	पूर्णांक ret;

	D_INFO("Begin load bsm\n");

	il->ucode_type = UCODE_RT;

	/* make sure bootstrap program is no larger than BSM's SRAM size */
	अगर (len > IL49_MAX_BSM_SIZE)
		वापस -EINVAL;

	/* Tell bootstrap uCode where to find the "Initialize" uCode
	 *   in host DRAM ... host DRAM physical address bits 35:4 क्रम 4965.
	 * NOTE:  il_init_alive_start() will replace these values,
	 *        after the "initialize" uCode has run, to poपूर्णांक to
	 *        runसमय/protocol inकाष्ठाions and backup data cache.
	 */
	pinst = il->ucode_init.p_addr >> 4;
	pdata = il->ucode_init_data.p_addr >> 4;
	inst_len = il->ucode_init.len;
	data_len = il->ucode_init_data.len;

	il_wr_prph(il, BSM_DRAM_INST_PTR_REG, pinst);
	il_wr_prph(il, BSM_DRAM_DATA_PTR_REG, pdata);
	il_wr_prph(il, BSM_DRAM_INST_BYTECOUNT_REG, inst_len);
	il_wr_prph(il, BSM_DRAM_DATA_BYTECOUNT_REG, data_len);

	/* Fill BSM memory with bootstrap inकाष्ठाions */
	क्रम (reg_offset = BSM_SRAM_LOWER_BOUND;
	     reg_offset < BSM_SRAM_LOWER_BOUND + len;
	     reg_offset += माप(u32), image++)
		_il_wr_prph(il, reg_offset, le32_to_cpu(*image));

	ret = il4965_verअगरy_bsm(il);
	अगर (ret)
		वापस ret;

	/* Tell BSM to copy from BSM SRAM पूर्णांकo inकाष्ठाion SRAM, when asked */
	il_wr_prph(il, BSM_WR_MEM_SRC_REG, 0x0);
	il_wr_prph(il, BSM_WR_MEM_DST_REG, IL49_RTC_INST_LOWER_BOUND);
	il_wr_prph(il, BSM_WR_DWCOUNT_REG, len / माप(u32));

	/* Load bootstrap code पूर्णांकo inकाष्ठाion SRAM now,
	 *   to prepare to load "initialize" uCode */
	il_wr_prph(il, BSM_WR_CTRL_REG, BSM_WR_CTRL_REG_BIT_START);

	/* Wait क्रम load of bootstrap uCode to finish */
	क्रम (i = 0; i < 100; i++) अणु
		करोne = il_rd_prph(il, BSM_WR_CTRL_REG);
		अगर (!(करोne & BSM_WR_CTRL_REG_BIT_START))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (i < 100)
		D_INFO("BSM write complete, poll %d iterations\n", i);
	अन्यथा अणु
		IL_ERR("BSM write did not complete!\n");
		वापस -EIO;
	पूर्ण

	/* Enable future boot loads whenever घातer management unit triggers it
	 *   (e.g. when घातering back up after घातer-save shutकरोwn) */
	il_wr_prph(il, BSM_WR_CTRL_REG, BSM_WR_CTRL_REG_BIT_START_EN);

	वापस 0;
पूर्ण

/*
 * il4965_set_ucode_ptrs - Set uCode address location
 *
 * Tell initialization uCode where to find runसमय uCode.
 *
 * BSM रेजिस्टरs initially contain poपूर्णांकers to initialization uCode.
 * We need to replace them to load runसमय uCode inst and data,
 * and to save runसमय data when घातering करोwn.
 */
अटल पूर्णांक
il4965_set_ucode_ptrs(काष्ठा il_priv *il)
अणु
	dma_addr_t pinst;
	dma_addr_t pdata;

	/* bits 35:4 क्रम 4965 */
	pinst = il->ucode_code.p_addr >> 4;
	pdata = il->ucode_data_backup.p_addr >> 4;

	/* Tell bootstrap uCode where to find image to load */
	il_wr_prph(il, BSM_DRAM_INST_PTR_REG, pinst);
	il_wr_prph(il, BSM_DRAM_DATA_PTR_REG, pdata);
	il_wr_prph(il, BSM_DRAM_DATA_BYTECOUNT_REG, il->ucode_data.len);

	/* Inst byte count must be last to set up, bit 31 संकेतs uCode
	 *   that all new ptr/size info is in place */
	il_wr_prph(il, BSM_DRAM_INST_BYTECOUNT_REG,
		   il->ucode_code.len | BSM_DRAM_INST_LOAD);
	D_INFO("Runtime uCode pointers are set.\n");

	वापस 0;
पूर्ण

/*
 * il4965_init_alive_start - Called after N_ALIVE notअगरication received
 *
 * Called after N_ALIVE notअगरication received from "initialize" uCode.
 *
 * The 4965 "initialize" ALIVE reply contains calibration data क्रम:
 *   Voltage, temperature, and MIMO tx gain correction, now stored in il
 *   (3945 करोes not contain this data).
 *
 * Tell "initialize" uCode to go ahead and load the runसमय uCode.
*/
अटल व्योम
il4965_init_alive_start(काष्ठा il_priv *il)
अणु
	/* Bootstrap uCode has loaded initialize uCode ... verअगरy inst image.
	 * This is a paranoid check, because we would not have gotten the
	 * "initialize" alive अगर code weren't properly loaded.  */
	अगर (il4965_verअगरy_ucode(il)) अणु
		/* Runसमय inकाष्ठाion load was bad;
		 * take it all the way back करोwn so we can try again */
		D_INFO("Bad \"initialize\" uCode load.\n");
		जाओ restart;
	पूर्ण

	/* Calculate temperature */
	il->temperature = il4965_hw_get_temperature(il);

	/* Send poपूर्णांकers to protocol/runसमय uCode image ... init code will
	 * load and launch runसमय uCode, which will send us another "Alive"
	 * notअगरication. */
	D_INFO("Initialization Alive received.\n");
	अगर (il4965_set_ucode_ptrs(il)) अणु
		/* Runसमय inकाष्ठाion load won't happen;
		 * take it all the way back करोwn so we can try again */
		D_INFO("Couldn't set up uCode pointers.\n");
		जाओ restart;
	पूर्ण
	वापस;

restart:
	queue_work(il->workqueue, &il->restart);
पूर्ण

अटल bool
iw4965_is_ht40_channel(__le32 rxon_flags)
अणु
	पूर्णांक chan_mod =
	    le32_to_cpu(rxon_flags & RXON_FLG_CHANNEL_MODE_MSK) >>
	    RXON_FLG_CHANNEL_MODE_POS;
	वापस (chan_mod == CHANNEL_MODE_PURE_40 ||
		chan_mod == CHANNEL_MODE_MIXED);
पूर्ण

व्योम
il4965_nic_config(काष्ठा il_priv *il)
अणु
	अचिन्हित दीर्घ flags;
	u16 radio_cfg;

	spin_lock_irqsave(&il->lock, flags);

	radio_cfg = il_eeprom_query16(il, EEPROM_RADIO_CONFIG);

	/* ग_लिखो radio config values to रेजिस्टर */
	अगर (EEPROM_RF_CFG_TYPE_MSK(radio_cfg) == EEPROM_4965_RF_CFG_TYPE_MAX)
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   EEPROM_RF_CFG_TYPE_MSK(radio_cfg) |
			   EEPROM_RF_CFG_STEP_MSK(radio_cfg) |
			   EEPROM_RF_CFG_DASH_MSK(radio_cfg));

	/* set CSR_HW_CONFIG_REG क्रम uCode use */
	il_set_bit(il, CSR_HW_IF_CONFIG_REG,
		   CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI |
		   CSR_HW_IF_CONFIG_REG_BIT_MAC_SI);

	il->calib_info =
	    (काष्ठा il_eeprom_calib_info *)
	    il_eeprom_query_addr(il, EEPROM_4965_CALIB_TXPOWER_OFFSET);

	spin_unlock_irqrestore(&il->lock, flags);
पूर्ण

/* Reset dअगरferential Rx gains in NIC to prepare क्रम chain noise calibration.
 * Called after every association, but this runs only once!
 *  ... once chain noise is calibrated the first समय, it's good क्रमever.  */
अटल व्योम
il4965_chain_noise_reset(काष्ठा il_priv *il)
अणु
	काष्ठा il_chain_noise_data *data = &(il->chain_noise_data);

	अगर (data->state == IL_CHAIN_NOISE_ALIVE && il_is_any_associated(il)) अणु
		काष्ठा il_calib_dअगरf_gain_cmd cmd;

		/* clear data क्रम chain noise calibration algorithm */
		data->chain_noise_a = 0;
		data->chain_noise_b = 0;
		data->chain_noise_c = 0;
		data->chain_संकेत_a = 0;
		data->chain_संकेत_b = 0;
		data->chain_संकेत_c = 0;
		data->beacon_count = 0;

		स_रखो(&cmd, 0, माप(cmd));
		cmd.hdr.op_code = IL_PHY_CALIBRATE_DIFF_GAIN_CMD;
		cmd.dअगरf_gain_a = 0;
		cmd.dअगरf_gain_b = 0;
		cmd.dअगरf_gain_c = 0;
		अगर (il_send_cmd_pdu(il, C_PHY_CALIBRATION, माप(cmd), &cmd))
			IL_ERR("Could not send C_PHY_CALIBRATION\n");
		data->state = IL_CHAIN_NOISE_ACCUMULATE;
		D_CALIB("Run chain_noise_calibrate\n");
	पूर्ण
पूर्ण

अटल s32
il4965_math_भाग_round(s32 num, s32 denom, s32 * res)
अणु
	s32 sign = 1;

	अगर (num < 0) अणु
		sign = -sign;
		num = -num;
	पूर्ण
	अगर (denom < 0) अणु
		sign = -sign;
		denom = -denom;
	पूर्ण
	*res = ((num * 2 + denom) / (denom * 2)) * sign;

	वापस 1;
पूर्ण

/*
 * il4965_get_voltage_compensation - Power supply voltage comp क्रम txघातer
 *
 * Determines घातer supply voltage compensation क्रम txघातer calculations.
 * Returns number of 1/2-dB steps to subtract from gain table idx,
 * to compensate क्रम dअगरference between घातer supply voltage during
 * factory measurements, vs. current घातer supply voltage.
 *
 * Voltage indication is higher क्रम lower voltage.
 * Lower voltage requires more gain (lower gain table idx).
 */
अटल s32
il4965_get_voltage_compensation(s32 eeprom_voltage, s32 current_voltage)
अणु
	s32 comp = 0;

	अगर (TX_POWER_IL_ILLEGAL_VOLTAGE == eeprom_voltage ||
	    TX_POWER_IL_ILLEGAL_VOLTAGE == current_voltage)
		वापस 0;

	il4965_math_भाग_round(current_voltage - eeprom_voltage,
			      TX_POWER_IL_VOLTAGE_CODES_PER_03V, &comp);

	अगर (current_voltage > eeprom_voltage)
		comp *= 2;
	अगर ((comp < -2) || (comp > 2))
		comp = 0;

	वापस comp;
पूर्ण

अटल s32
il4965_get_tx_atten_grp(u16 channel)
अणु
	अगर (channel >= CALIB_IL_TX_ATTEN_GR5_FCH &&
	    channel <= CALIB_IL_TX_ATTEN_GR5_LCH)
		वापस CALIB_CH_GROUP_5;

	अगर (channel >= CALIB_IL_TX_ATTEN_GR1_FCH &&
	    channel <= CALIB_IL_TX_ATTEN_GR1_LCH)
		वापस CALIB_CH_GROUP_1;

	अगर (channel >= CALIB_IL_TX_ATTEN_GR2_FCH &&
	    channel <= CALIB_IL_TX_ATTEN_GR2_LCH)
		वापस CALIB_CH_GROUP_2;

	अगर (channel >= CALIB_IL_TX_ATTEN_GR3_FCH &&
	    channel <= CALIB_IL_TX_ATTEN_GR3_LCH)
		वापस CALIB_CH_GROUP_3;

	अगर (channel >= CALIB_IL_TX_ATTEN_GR4_FCH &&
	    channel <= CALIB_IL_TX_ATTEN_GR4_LCH)
		वापस CALIB_CH_GROUP_4;

	वापस -EINVAL;
पूर्ण

अटल u32
il4965_get_sub_band(स्थिर काष्ठा il_priv *il, u32 channel)
अणु
	s32 b = -1;

	क्रम (b = 0; b < EEPROM_TX_POWER_BANDS; b++) अणु
		अगर (il->calib_info->band_info[b].ch_from == 0)
			जारी;

		अगर (channel >= il->calib_info->band_info[b].ch_from &&
		    channel <= il->calib_info->band_info[b].ch_to)
			अवरोध;
	पूर्ण

	वापस b;
पूर्ण

अटल s32
il4965_पूर्णांकerpolate_value(s32 x, s32 x1, s32 y1, s32 x2, s32 y2)
अणु
	s32 val;

	अगर (x2 == x1)
		वापस y1;
	अन्यथा अणु
		il4965_math_भाग_round((x2 - x) * (y1 - y2), (x2 - x1), &val);
		वापस val + y2;
	पूर्ण
पूर्ण

/*
 * il4965_पूर्णांकerpolate_chan - Interpolate factory measurements क्रम one channel
 *
 * Interpolates factory measurements from the two sample channels within a
 * sub-band, to apply to channel of पूर्णांकerest.  Interpolation is proportional to
 * dअगरferences in channel frequencies, which is proportional to dअगरferences
 * in channel number.
 */
अटल पूर्णांक
il4965_पूर्णांकerpolate_chan(काष्ठा il_priv *il, u32 channel,
			काष्ठा il_eeprom_calib_ch_info *chan_info)
अणु
	s32 s = -1;
	u32 c;
	u32 m;
	स्थिर काष्ठा il_eeprom_calib_measure *m1;
	स्थिर काष्ठा il_eeprom_calib_measure *m2;
	काष्ठा il_eeprom_calib_measure *omeas;
	u32 ch_i1;
	u32 ch_i2;

	s = il4965_get_sub_band(il, channel);
	अगर (s >= EEPROM_TX_POWER_BANDS) अणु
		IL_ERR("Tx Power can not find channel %d\n", channel);
		वापस -1;
	पूर्ण

	ch_i1 = il->calib_info->band_info[s].ch1.ch_num;
	ch_i2 = il->calib_info->band_info[s].ch2.ch_num;
	chan_info->ch_num = (u8) channel;

	D_TXPOWER("channel %d subband %d factory cal ch %d & %d\n", channel, s,
		  ch_i1, ch_i2);

	क्रम (c = 0; c < EEPROM_TX_POWER_TX_CHAINS; c++) अणु
		क्रम (m = 0; m < EEPROM_TX_POWER_MEASUREMENTS; m++) अणु
			m1 = &(il->calib_info->band_info[s].ch1.
			       measurements[c][m]);
			m2 = &(il->calib_info->band_info[s].ch2.
			       measurements[c][m]);
			omeas = &(chan_info->measurements[c][m]);

			omeas->actual_घात =
			    (u8) il4965_पूर्णांकerpolate_value(channel, ch_i1,
							  m1->actual_घात, ch_i2,
							  m2->actual_घात);
			omeas->gain_idx =
			    (u8) il4965_पूर्णांकerpolate_value(channel, ch_i1,
							  m1->gain_idx, ch_i2,
							  m2->gain_idx);
			omeas->temperature =
			    (u8) il4965_पूर्णांकerpolate_value(channel, ch_i1,
							  m1->temperature,
							  ch_i2,
							  m2->temperature);
			omeas->pa_det =
			    (s8) il4965_पूर्णांकerpolate_value(channel, ch_i1,
							  m1->pa_det, ch_i2,
							  m2->pa_det);

			D_TXPOWER("chain %d meas %d AP1=%d AP2=%d AP=%d\n", c,
				  m, m1->actual_घात, m2->actual_घात,
				  omeas->actual_घात);
			D_TXPOWER("chain %d meas %d NI1=%d NI2=%d NI=%d\n", c,
				  m, m1->gain_idx, m2->gain_idx,
				  omeas->gain_idx);
			D_TXPOWER("chain %d meas %d PA1=%d PA2=%d PA=%d\n", c,
				  m, m1->pa_det, m2->pa_det, omeas->pa_det);
			D_TXPOWER("chain %d meas %d  T1=%d  T2=%d  T=%d\n", c,
				  m, m1->temperature, m2->temperature,
				  omeas->temperature);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* bit-rate-dependent table to prevent Tx distortion, in half-dB units,
 * क्रम OFDM 6, 12, 18, 24, 36, 48, 54, 60 MBit, and CCK all rates. */
अटल s32 back_off_table[] = अणु
	10, 10, 10, 10, 10, 15, 17, 20,	/* OFDM SISO 20 MHz */
	10, 10, 10, 10, 10, 15, 17, 20,	/* OFDM MIMO 20 MHz */
	10, 10, 10, 10, 10, 15, 17, 20,	/* OFDM SISO 40 MHz */
	10, 10, 10, 10, 10, 15, 17, 20,	/* OFDM MIMO 40 MHz */
	10			/* CCK */
पूर्ण;

/* Thermal compensation values क्रम txघातer क्रम various frequency ranges ...
 *   ratios from 3:1 to 4.5:1 of degrees (Celsius) per half-dB gain adjust */
अटल काष्ठा il4965_txघातer_comp_entry अणु
	s32 degrees_per_05db_a;
	s32 degrees_per_05db_a_denom;
पूर्ण tx_घातer_cmp_tble[CALIB_CH_GROUP_MAX] = अणु
	अणु
	9, 2पूर्ण,			/* group 0 5.2, ch  34-43 */
	अणु
	4, 1पूर्ण,			/* group 1 5.2, ch  44-70 */
	अणु
	4, 1पूर्ण,			/* group 2 5.2, ch  71-124 */
	अणु
	4, 1पूर्ण,			/* group 3 5.2, ch 125-200 */
	अणु
	3, 1पूर्ण			/* group 4 2.4, ch   all */
पूर्ण;

अटल s32
get_min_घातer_idx(s32 rate_घातer_idx, u32 band)
अणु
	अगर (!band) अणु
		अगर ((rate_घातer_idx & 7) <= 4)
			वापस MIN_TX_GAIN_IDX_52GHZ_EXT;
	पूर्ण
	वापस MIN_TX_GAIN_IDX;
पूर्ण

काष्ठा gain_entry अणु
	u8 dsp;
	u8 radio;
पूर्ण;

अटल स्थिर काष्ठा gain_entry gain_table[2][108] = अणु
	/* 5.2GHz घातer gain idx table */
	अणु
	 अणु123, 0x3Fपूर्ण,		/* highest txघातer */
	 अणु117, 0x3Fपूर्ण,
	 अणु110, 0x3Fपूर्ण,
	 अणु104, 0x3Fपूर्ण,
	 अणु98, 0x3Fपूर्ण,
	 अणु110, 0x3Eपूर्ण,
	 अणु104, 0x3Eपूर्ण,
	 अणु98, 0x3Eपूर्ण,
	 अणु110, 0x3Dपूर्ण,
	 अणु104, 0x3Dपूर्ण,
	 अणु98, 0x3Dपूर्ण,
	 अणु110, 0x3Cपूर्ण,
	 अणु104, 0x3Cपूर्ण,
	 अणु98, 0x3Cपूर्ण,
	 अणु110, 0x3Bपूर्ण,
	 अणु104, 0x3Bपूर्ण,
	 अणु98, 0x3Bपूर्ण,
	 अणु110, 0x3Aपूर्ण,
	 अणु104, 0x3Aपूर्ण,
	 अणु98, 0x3Aपूर्ण,
	 अणु110, 0x39पूर्ण,
	 अणु104, 0x39पूर्ण,
	 अणु98, 0x39पूर्ण,
	 अणु110, 0x38पूर्ण,
	 अणु104, 0x38पूर्ण,
	 अणु98, 0x38पूर्ण,
	 अणु110, 0x37पूर्ण,
	 अणु104, 0x37पूर्ण,
	 अणु98, 0x37पूर्ण,
	 अणु110, 0x36पूर्ण,
	 अणु104, 0x36पूर्ण,
	 अणु98, 0x36पूर्ण,
	 अणु110, 0x35पूर्ण,
	 अणु104, 0x35पूर्ण,
	 अणु98, 0x35पूर्ण,
	 अणु110, 0x34पूर्ण,
	 अणु104, 0x34पूर्ण,
	 अणु98, 0x34पूर्ण,
	 अणु110, 0x33पूर्ण,
	 अणु104, 0x33पूर्ण,
	 अणु98, 0x33पूर्ण,
	 अणु110, 0x32पूर्ण,
	 अणु104, 0x32पूर्ण,
	 अणु98, 0x32पूर्ण,
	 अणु110, 0x31पूर्ण,
	 अणु104, 0x31पूर्ण,
	 अणु98, 0x31पूर्ण,
	 अणु110, 0x30पूर्ण,
	 अणु104, 0x30पूर्ण,
	 अणु98, 0x30पूर्ण,
	 अणु110, 0x25पूर्ण,
	 अणु104, 0x25पूर्ण,
	 अणु98, 0x25पूर्ण,
	 अणु110, 0x24पूर्ण,
	 अणु104, 0x24पूर्ण,
	 अणु98, 0x24पूर्ण,
	 अणु110, 0x23पूर्ण,
	 अणु104, 0x23पूर्ण,
	 अणु98, 0x23पूर्ण,
	 अणु110, 0x22पूर्ण,
	 अणु104, 0x18पूर्ण,
	 अणु98, 0x18पूर्ण,
	 अणु110, 0x17पूर्ण,
	 अणु104, 0x17पूर्ण,
	 अणु98, 0x17पूर्ण,
	 अणु110, 0x16पूर्ण,
	 अणु104, 0x16पूर्ण,
	 अणु98, 0x16पूर्ण,
	 अणु110, 0x15पूर्ण,
	 अणु104, 0x15पूर्ण,
	 अणु98, 0x15पूर्ण,
	 अणु110, 0x14पूर्ण,
	 अणु104, 0x14पूर्ण,
	 अणु98, 0x14पूर्ण,
	 अणु110, 0x13पूर्ण,
	 अणु104, 0x13पूर्ण,
	 अणु98, 0x13पूर्ण,
	 अणु110, 0x12पूर्ण,
	 अणु104, 0x08पूर्ण,
	 अणु98, 0x08पूर्ण,
	 अणु110, 0x07पूर्ण,
	 अणु104, 0x07पूर्ण,
	 अणु98, 0x07पूर्ण,
	 अणु110, 0x06पूर्ण,
	 अणु104, 0x06पूर्ण,
	 अणु98, 0x06पूर्ण,
	 अणु110, 0x05पूर्ण,
	 अणु104, 0x05पूर्ण,
	 अणु98, 0x05पूर्ण,
	 अणु110, 0x04पूर्ण,
	 अणु104, 0x04पूर्ण,
	 अणु98, 0x04पूर्ण,
	 अणु110, 0x03पूर्ण,
	 अणु104, 0x03पूर्ण,
	 अणु98, 0x03पूर्ण,
	 अणु110, 0x02पूर्ण,
	 अणु104, 0x02पूर्ण,
	 अणु98, 0x02पूर्ण,
	 अणु110, 0x01पूर्ण,
	 अणु104, 0x01पूर्ण,
	 अणु98, 0x01पूर्ण,
	 अणु110, 0x00पूर्ण,
	 अणु104, 0x00पूर्ण,
	 अणु98, 0x00पूर्ण,
	 अणु93, 0x00पूर्ण,
	 अणु88, 0x00पूर्ण,
	 अणु83, 0x00पूर्ण,
	 अणु78, 0x00पूर्ण,
	 पूर्ण,
	/* 2.4GHz घातer gain idx table */
	अणु
	 अणु110, 0x3fपूर्ण,		/* highest txघातer */
	 अणु104, 0x3fपूर्ण,
	 अणु98, 0x3fपूर्ण,
	 अणु110, 0x3eपूर्ण,
	 अणु104, 0x3eपूर्ण,
	 अणु98, 0x3eपूर्ण,
	 अणु110, 0x3dपूर्ण,
	 अणु104, 0x3dपूर्ण,
	 अणु98, 0x3dपूर्ण,
	 अणु110, 0x3cपूर्ण,
	 अणु104, 0x3cपूर्ण,
	 अणु98, 0x3cपूर्ण,
	 अणु110, 0x3bपूर्ण,
	 अणु104, 0x3bपूर्ण,
	 अणु98, 0x3bपूर्ण,
	 अणु110, 0x3aपूर्ण,
	 अणु104, 0x3aपूर्ण,
	 अणु98, 0x3aपूर्ण,
	 अणु110, 0x39पूर्ण,
	 अणु104, 0x39पूर्ण,
	 अणु98, 0x39पूर्ण,
	 अणु110, 0x38पूर्ण,
	 अणु104, 0x38पूर्ण,
	 अणु98, 0x38पूर्ण,
	 अणु110, 0x37पूर्ण,
	 अणु104, 0x37पूर्ण,
	 अणु98, 0x37पूर्ण,
	 अणु110, 0x36पूर्ण,
	 अणु104, 0x36पूर्ण,
	 अणु98, 0x36पूर्ण,
	 अणु110, 0x35पूर्ण,
	 अणु104, 0x35पूर्ण,
	 अणु98, 0x35पूर्ण,
	 अणु110, 0x34पूर्ण,
	 अणु104, 0x34पूर्ण,
	 अणु98, 0x34पूर्ण,
	 अणु110, 0x33पूर्ण,
	 अणु104, 0x33पूर्ण,
	 अणु98, 0x33पूर्ण,
	 अणु110, 0x32पूर्ण,
	 अणु104, 0x32पूर्ण,
	 अणु98, 0x32पूर्ण,
	 अणु110, 0x31पूर्ण,
	 अणु104, 0x31पूर्ण,
	 अणु98, 0x31पूर्ण,
	 अणु110, 0x30पूर्ण,
	 अणु104, 0x30पूर्ण,
	 अणु98, 0x30पूर्ण,
	 अणु110, 0x6पूर्ण,
	 अणु104, 0x6पूर्ण,
	 अणु98, 0x6पूर्ण,
	 अणु110, 0x5पूर्ण,
	 अणु104, 0x5पूर्ण,
	 अणु98, 0x5पूर्ण,
	 अणु110, 0x4पूर्ण,
	 अणु104, 0x4पूर्ण,
	 अणु98, 0x4पूर्ण,
	 अणु110, 0x3पूर्ण,
	 अणु104, 0x3पूर्ण,
	 अणु98, 0x3पूर्ण,
	 अणु110, 0x2पूर्ण,
	 अणु104, 0x2पूर्ण,
	 अणु98, 0x2पूर्ण,
	 अणु110, 0x1पूर्ण,
	 अणु104, 0x1पूर्ण,
	 अणु98, 0x1पूर्ण,
	 अणु110, 0x0पूर्ण,
	 अणु104, 0x0पूर्ण,
	 अणु98, 0x0पूर्ण,
	 अणु97, 0पूर्ण,
	 अणु96, 0पूर्ण,
	 अणु95, 0पूर्ण,
	 अणु94, 0पूर्ण,
	 अणु93, 0पूर्ण,
	 अणु92, 0पूर्ण,
	 अणु91, 0पूर्ण,
	 अणु90, 0पूर्ण,
	 अणु89, 0पूर्ण,
	 अणु88, 0पूर्ण,
	 अणु87, 0पूर्ण,
	 अणु86, 0पूर्ण,
	 अणु85, 0पूर्ण,
	 अणु84, 0पूर्ण,
	 अणु83, 0पूर्ण,
	 अणु82, 0पूर्ण,
	 अणु81, 0पूर्ण,
	 अणु80, 0पूर्ण,
	 अणु79, 0पूर्ण,
	 अणु78, 0पूर्ण,
	 अणु77, 0पूर्ण,
	 अणु76, 0पूर्ण,
	 अणु75, 0पूर्ण,
	 अणु74, 0पूर्ण,
	 अणु73, 0पूर्ण,
	 अणु72, 0पूर्ण,
	 अणु71, 0पूर्ण,
	 अणु70, 0पूर्ण,
	 अणु69, 0पूर्ण,
	 अणु68, 0पूर्ण,
	 अणु67, 0पूर्ण,
	 अणु66, 0पूर्ण,
	 अणु65, 0पूर्ण,
	 अणु64, 0पूर्ण,
	 अणु63, 0पूर्ण,
	 अणु62, 0पूर्ण,
	 अणु61, 0पूर्ण,
	 अणु60, 0पूर्ण,
	 अणु59, 0पूर्ण,
	 पूर्ण
पूर्ण;

अटल पूर्णांक
il4965_fill_txघातer_tbl(काष्ठा il_priv *il, u8 band, u16 channel, u8 is_ht40,
			u8 ctrl_chan_high,
			काष्ठा il4965_tx_घातer_db *tx_घातer_tbl)
अणु
	u8 saturation_घातer;
	s32 target_घातer;
	s32 user_target_घातer;
	s32 घातer_limit;
	s32 current_temp;
	s32 reg_limit;
	s32 current_regulatory;
	s32 txatten_grp = CALIB_CH_GROUP_MAX;
	पूर्णांक i;
	पूर्णांक c;
	स्थिर काष्ठा il_channel_info *ch_info = शून्य;
	काष्ठा il_eeprom_calib_ch_info ch_eeprom_info;
	स्थिर काष्ठा il_eeprom_calib_measure *measurement;
	s16 voltage;
	s32 init_voltage;
	s32 voltage_compensation;
	s32 degrees_per_05db_num;
	s32 degrees_per_05db_denom;
	s32 factory_temp;
	s32 temperature_comp[2];
	s32 factory_gain_idx[2];
	s32 factory_actual_pwr[2];
	s32 घातer_idx;

	/* tx_घातer_user_lmt is in dBm, convert to half-dBm (half-dB units
	 *   are used क्रम idxing पूर्णांकo txघातer table) */
	user_target_घातer = 2 * il->tx_घातer_user_lmt;

	/* Get current (RXON) channel, band, width */
	D_TXPOWER("chan %d band %d is_ht40 %d\n", channel, band, is_ht40);

	ch_info = il_get_channel_info(il, il->band, channel);

	अगर (!il_is_channel_valid(ch_info))
		वापस -EINVAL;

	/* get txatten group, used to select 1) thermal txघातer adjusपंचांगent
	 *   and 2) mimo txघातer balance between Tx chains. */
	txatten_grp = il4965_get_tx_atten_grp(channel);
	अगर (txatten_grp < 0) अणु
		IL_ERR("Can't find txatten group for channel %d.\n", channel);
		वापस txatten_grp;
	पूर्ण

	D_TXPOWER("channel %d belongs to txatten group %d\n", channel,
		  txatten_grp);

	अगर (is_ht40) अणु
		अगर (ctrl_chan_high)
			channel -= 2;
		अन्यथा
			channel += 2;
	पूर्ण

	/* hardware txघातer limits ...
	 * saturation (clipping distortion) txघातers are in half-dBm */
	अगर (band)
		saturation_घातer = il->calib_info->saturation_घातer24;
	अन्यथा
		saturation_घातer = il->calib_info->saturation_घातer52;

	अगर (saturation_घातer < IL_TX_POWER_SATURATION_MIN ||
	    saturation_घातer > IL_TX_POWER_SATURATION_MAX) अणु
		अगर (band)
			saturation_घातer = IL_TX_POWER_DEFAULT_SATURATION_24;
		अन्यथा
			saturation_घातer = IL_TX_POWER_DEFAULT_SATURATION_52;
	पूर्ण

	/* regulatory txघातer limits ... reg_limit values are in half-dBm,
	 *   max_घातer_avg values are in dBm, convert * 2 */
	अगर (is_ht40)
		reg_limit = ch_info->ht40_max_घातer_avg * 2;
	अन्यथा
		reg_limit = ch_info->max_घातer_avg * 2;

	अगर ((reg_limit < IL_TX_POWER_REGULATORY_MIN) ||
	    (reg_limit > IL_TX_POWER_REGULATORY_MAX)) अणु
		अगर (band)
			reg_limit = IL_TX_POWER_DEFAULT_REGULATORY_24;
		अन्यथा
			reg_limit = IL_TX_POWER_DEFAULT_REGULATORY_52;
	पूर्ण

	/* Interpolate txघातer calibration values क्रम this channel,
	 *   based on factory calibration tests on spaced channels. */
	il4965_पूर्णांकerpolate_chan(il, channel, &ch_eeprom_info);

	/* calculate tx gain adjusपंचांगent based on घातer supply voltage */
	voltage = le16_to_cpu(il->calib_info->voltage);
	init_voltage = (s32) le32_to_cpu(il->card_alive_init.voltage);
	voltage_compensation =
	    il4965_get_voltage_compensation(voltage, init_voltage);

	D_TXPOWER("curr volt %d eeprom volt %d volt comp %d\n", init_voltage,
		  voltage, voltage_compensation);

	/* get current temperature (Celsius) */
	current_temp = max(il->temperature, IL_TX_POWER_TEMPERATURE_MIN);
	current_temp = min(il->temperature, IL_TX_POWER_TEMPERATURE_MAX);
	current_temp = kelvin_to_celsius(current_temp);

	/* select thermal txघातer adjusपंचांगent params, based on channel group
	 *   (same frequency group used क्रम mimo txatten adjusपंचांगent) */
	degrees_per_05db_num =
	    tx_घातer_cmp_tble[txatten_grp].degrees_per_05db_a;
	degrees_per_05db_denom =
	    tx_घातer_cmp_tble[txatten_grp].degrees_per_05db_a_denom;

	/* get per-chain txघातer values from factory measurements */
	क्रम (c = 0; c < 2; c++) अणु
		measurement = &ch_eeprom_info.measurements[c][1];

		/* txgain adjusपंचांगent (in half-dB steps) based on dअगरference
		 *   between factory and current temperature */
		factory_temp = measurement->temperature;
		il4965_math_भाग_round((current_temp -
				       factory_temp) * degrees_per_05db_denom,
				      degrees_per_05db_num,
				      &temperature_comp[c]);

		factory_gain_idx[c] = measurement->gain_idx;
		factory_actual_pwr[c] = measurement->actual_घात;

		D_TXPOWER("chain = %d\n", c);
		D_TXPOWER("fctry tmp %d, " "curr tmp %d, comp %d steps\n",
			  factory_temp, current_temp, temperature_comp[c]);

		D_TXPOWER("fctry idx %d, fctry pwr %d\n", factory_gain_idx[c],
			  factory_actual_pwr[c]);
	पूर्ण

	/* क्रम each of 33 bit-rates (including 1 क्रम CCK) */
	क्रम (i = 0; i < POWER_TBL_NUM_ENTRIES; i++) अणु
		u8 is_mimo_rate;
		जोड़ il4965_tx_घातer_dual_stream tx_घातer;

		/* क्रम mimo, reduce each chain's txघातer by half
		 * (3dB, 6 steps), so total output घातer is regulatory
		 * compliant. */
		अगर (i & 0x8) अणु
			current_regulatory =
			    reg_limit -
			    IL_TX_POWER_MIMO_REGULATORY_COMPENSATION;
			is_mimo_rate = 1;
		पूर्ण अन्यथा अणु
			current_regulatory = reg_limit;
			is_mimo_rate = 0;
		पूर्ण

		/* find txघातer limit, either hardware or regulatory */
		घातer_limit = saturation_घातer - back_off_table[i];
		अगर (घातer_limit > current_regulatory)
			घातer_limit = current_regulatory;

		/* reduce user's txघातer request अगर necessary
		 * क्रम this rate on this channel */
		target_घातer = user_target_घातer;
		अगर (target_घातer > घातer_limit)
			target_घातer = घातer_limit;

		D_TXPOWER("rate %d sat %d reg %d usr %d tgt %d\n", i,
			  saturation_घातer - back_off_table[i],
			  current_regulatory, user_target_घातer, target_घातer);

		/* क्रम each of 2 Tx chains (radio transmitters) */
		क्रम (c = 0; c < 2; c++) अणु
			s32 atten_value;

			अगर (is_mimo_rate)
				atten_value =
				    (s32) le32_to_cpu(il->card_alive_init.
						      tx_atten[txatten_grp][c]);
			अन्यथा
				atten_value = 0;

			/* calculate idx; higher idx means lower txघातer */
			घातer_idx =
			    (u8) (factory_gain_idx[c] -
				  (target_घातer - factory_actual_pwr[c]) -
				  temperature_comp[c] - voltage_compensation +
				  atten_value);

/*			D_TXPOWER("calculated txpower idx %d\n",
						घातer_idx); */

			अगर (घातer_idx < get_min_घातer_idx(i, band))
				घातer_idx = get_min_घातer_idx(i, band);

			/* adjust 5 GHz idx to support negative idxes */
			अगर (!band)
				घातer_idx += 9;

			/* CCK, rate 32, reduce txघातer क्रम CCK */
			अगर (i == POWER_TBL_CCK_ENTRY)
				घातer_idx +=
				    IL_TX_POWER_CCK_COMPENSATION_C_STEP;

			/* stay within the table! */
			अगर (घातer_idx > 107) अणु
				IL_WARN("txpower idx %d > 107\n", घातer_idx);
				घातer_idx = 107;
			पूर्ण
			अगर (घातer_idx < 0) अणु
				IL_WARN("txpower idx %d < 0\n", घातer_idx);
				घातer_idx = 0;
			पूर्ण

			/* fill txघातer command क्रम this rate/chain */
			tx_घातer.s.radio_tx_gain[c] =
			    gain_table[band][घातer_idx].radio;
			tx_घातer.s.dsp_predis_atten[c] =
			    gain_table[band][घातer_idx].dsp;

			D_TXPOWER("chain %d mimo %d idx %d "
				  "gain 0x%02x dsp %d\n", c, atten_value,
				  घातer_idx, tx_घातer.s.radio_tx_gain[c],
				  tx_घातer.s.dsp_predis_atten[c]);
		पूर्ण		/* क्रम each chain */

		tx_घातer_tbl->घातer_tbl[i].dw = cpu_to_le32(tx_घातer.dw);

	पूर्ण			/* क्रम each rate */

	वापस 0;
पूर्ण

/*
 * il4965_send_tx_घातer - Configure the TXPOWER level user limit
 *
 * Uses the active RXON क्रम channel, band, and अक्षरacteristics (ht40, high)
 * The घातer limit is taken from il->tx_घातer_user_lmt.
 */
अटल पूर्णांक
il4965_send_tx_घातer(काष्ठा il_priv *il)
अणु
	काष्ठा il4965_txघातertable_cmd cmd = अणु 0 पूर्ण;
	पूर्णांक ret;
	u8 band = 0;
	bool is_ht40 = false;
	u8 ctrl_chan_high = 0;

	अगर (WARN_ONCE
	    (test_bit(S_SCAN_HW, &il->status),
	     "TX Power requested while scanning!\n"))
		वापस -EAGAIN;

	band = il->band == NL80211_BAND_2GHZ;

	is_ht40 = iw4965_is_ht40_channel(il->active.flags);

	अगर (is_ht40 && (il->active.flags & RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK))
		ctrl_chan_high = 1;

	cmd.band = band;
	cmd.channel = il->active.channel;

	ret =
	    il4965_fill_txघातer_tbl(il, band, le16_to_cpu(il->active.channel),
				    is_ht40, ctrl_chan_high, &cmd.tx_घातer);
	अगर (ret)
		जाओ out;

	ret = il_send_cmd_pdu(il, C_TX_PWR_TBL, माप(cmd), &cmd);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक
il4965_send_rxon_assoc(काष्ठा il_priv *il)
अणु
	पूर्णांक ret = 0;
	काष्ठा il4965_rxon_assoc_cmd rxon_assoc;
	स्थिर काष्ठा il_rxon_cmd *rxon1 = &il->staging;
	स्थिर काष्ठा il_rxon_cmd *rxon2 = &il->active;

	lockdep_निश्चित_held(&il->mutex);

	अगर (rxon1->flags == rxon2->flags &&
	    rxon1->filter_flags == rxon2->filter_flags &&
	    rxon1->cck_basic_rates == rxon2->cck_basic_rates &&
	    rxon1->ofdm_ht_single_stream_basic_rates ==
	    rxon2->ofdm_ht_single_stream_basic_rates &&
	    rxon1->ofdm_ht_dual_stream_basic_rates ==
	    rxon2->ofdm_ht_dual_stream_basic_rates &&
	    rxon1->rx_chain == rxon2->rx_chain &&
	    rxon1->ofdm_basic_rates == rxon2->ofdm_basic_rates) अणु
		D_INFO("Using current RXON_ASSOC.  Not resending.\n");
		वापस 0;
	पूर्ण

	rxon_assoc.flags = il->staging.flags;
	rxon_assoc.filter_flags = il->staging.filter_flags;
	rxon_assoc.ofdm_basic_rates = il->staging.ofdm_basic_rates;
	rxon_assoc.cck_basic_rates = il->staging.cck_basic_rates;
	rxon_assoc.reserved = 0;
	rxon_assoc.ofdm_ht_single_stream_basic_rates =
	    il->staging.ofdm_ht_single_stream_basic_rates;
	rxon_assoc.ofdm_ht_dual_stream_basic_rates =
	    il->staging.ofdm_ht_dual_stream_basic_rates;
	rxon_assoc.rx_chain_select_flags = il->staging.rx_chain;

	ret =
	    il_send_cmd_pdu_async(il, C_RXON_ASSOC, माप(rxon_assoc),
				  &rxon_assoc, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक
il4965_commit_rxon(काष्ठा il_priv *il)
अणु
	/* cast away the स्थिर क्रम active_rxon in this function */
	काष्ठा il_rxon_cmd *active_rxon = (व्योम *)&il->active;
	पूर्णांक ret;
	bool new_assoc = !!(il->staging.filter_flags & RXON_FILTER_ASSOC_MSK);

	अगर (!il_is_alive(il))
		वापस -EBUSY;

	/* always get बारtamp with Rx frame */
	il->staging.flags |= RXON_FLG_TSF2HOST_MSK;

	ret = il_check_rxon_cmd(il);
	अगर (ret) अणु
		IL_ERR("Invalid RXON configuration.  Not committing.\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * receive commit_rxon request
	 * पात any previous channel चयन अगर still in process
	 */
	अगर (test_bit(S_CHANNEL_SWITCH_PENDING, &il->status) &&
	    il->चयन_channel != il->staging.channel) अणु
		D_11H("abort channel switch on %d\n",
		      le16_to_cpu(il->चयन_channel));
		il_chचयन_करोne(il, false);
	पूर्ण

	/* If we करोn't need to send a full RXON, we can use
	 * il_rxon_assoc_cmd which is used to reconfigure filter
	 * and other flags क्रम the current radio configuration. */
	अगर (!il_full_rxon_required(il)) अणु
		ret = il_send_rxon_assoc(il);
		अगर (ret) अणु
			IL_ERR("Error setting RXON_ASSOC (%d)\n", ret);
			वापस ret;
		पूर्ण

		स_नकल(active_rxon, &il->staging, माप(*active_rxon));
		il_prपूर्णांक_rx_config_cmd(il);
		/*
		 * We करो not commit tx घातer settings जबतक channel changing,
		 * करो it now अगर tx घातer changed.
		 */
		il_set_tx_घातer(il, il->tx_घातer_next, false);
		वापस 0;
	पूर्ण

	/* If we are currently associated and the new config requires
	 * an RXON_ASSOC and the new config wants the associated mask enabled,
	 * we must clear the associated from the active configuration
	 * beक्रमe we apply the new config */
	अगर (il_is_associated(il) && new_assoc) अणु
		D_INFO("Toggling associated bit on current RXON\n");
		active_rxon->filter_flags &= ~RXON_FILTER_ASSOC_MSK;

		ret =
		    il_send_cmd_pdu(il, C_RXON,
				    माप(काष्ठा il_rxon_cmd), active_rxon);

		/* If the mask clearing failed then we set
		 * active_rxon back to what it was previously */
		अगर (ret) अणु
			active_rxon->filter_flags |= RXON_FILTER_ASSOC_MSK;
			IL_ERR("Error clearing ASSOC_MSK (%d)\n", ret);
			वापस ret;
		पूर्ण
		il_clear_ucode_stations(il);
		il_restore_stations(il);
		ret = il4965_restore_शेष_wep_keys(il);
		अगर (ret) अणु
			IL_ERR("Failed to restore WEP keys (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	D_INFO("Sending RXON\n" "* with%s RXON_FILTER_ASSOC_MSK\n"
	       "* channel = %d\n" "* bssid = %pM\n", (new_assoc ? "" : "out"),
	       le16_to_cpu(il->staging.channel), il->staging.bssid_addr);

	il_set_rxon_hwcrypto(il, !il->cfg->mod_params->sw_crypto);

	/* Apply the new configuration
	 * RXON unassoc clears the station table in uCode so restoration of
	 * stations is needed after it (the RXON command) completes
	 */
	अगर (!new_assoc) अणु
		ret =
		    il_send_cmd_pdu(il, C_RXON,
				    माप(काष्ठा il_rxon_cmd), &il->staging);
		अगर (ret) अणु
			IL_ERR("Error setting new RXON (%d)\n", ret);
			वापस ret;
		पूर्ण
		D_INFO("Return from !new_assoc RXON.\n");
		स_नकल(active_rxon, &il->staging, माप(*active_rxon));
		il_clear_ucode_stations(il);
		il_restore_stations(il);
		ret = il4965_restore_शेष_wep_keys(il);
		अगर (ret) अणु
			IL_ERR("Failed to restore WEP keys (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण
	अगर (new_assoc) अणु
		il->start_calib = 0;
		/* Apply the new configuration
		 * RXON assoc करोesn't clear the station table in uCode,
		 */
		ret =
		    il_send_cmd_pdu(il, C_RXON,
				    माप(काष्ठा il_rxon_cmd), &il->staging);
		अगर (ret) अणु
			IL_ERR("Error setting new RXON (%d)\n", ret);
			वापस ret;
		पूर्ण
		स_नकल(active_rxon, &il->staging, माप(*active_rxon));
	पूर्ण
	il_prपूर्णांक_rx_config_cmd(il);

	il4965_init_sensitivity(il);

	/* If we issue a new RXON command which required a tune then we must
	 * send a new TXPOWER command or we won't be able to Tx any frames */
	ret = il_set_tx_घातer(il, il->tx_घातer_next, true);
	अगर (ret) अणु
		IL_ERR("Error sending TX power (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
il4965_hw_channel_चयन(काष्ठा il_priv *il,
			 काष्ठा ieee80211_channel_चयन *ch_चयन)
अणु
	पूर्णांक rc;
	u8 band = 0;
	bool is_ht40 = false;
	u8 ctrl_chan_high = 0;
	काष्ठा il4965_channel_चयन_cmd cmd;
	स्थिर काष्ठा il_channel_info *ch_info;
	u32 चयन_समय_in_usec, ucode_चयन_समय;
	u16 ch;
	u32 tsf_low;
	u8 चयन_count;
	u16 beacon_पूर्णांकerval = le16_to_cpu(il->timing.beacon_पूर्णांकerval);
	काष्ठा ieee80211_vअगर *vअगर = il->vअगर;
	band = (il->band == NL80211_BAND_2GHZ);

	अगर (WARN_ON_ONCE(vअगर == शून्य))
		वापस -EIO;

	is_ht40 = iw4965_is_ht40_channel(il->staging.flags);

	अगर (is_ht40 && (il->staging.flags & RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK))
		ctrl_chan_high = 1;

	cmd.band = band;
	cmd.expect_beacon = 0;
	ch = ch_चयन->chandef.chan->hw_value;
	cmd.channel = cpu_to_le16(ch);
	cmd.rxon_flags = il->staging.flags;
	cmd.rxon_filter_flags = il->staging.filter_flags;
	चयन_count = ch_चयन->count;
	tsf_low = ch_चयन->बारtamp & 0x0ffffffff;
	/*
	 * calculate the ucode channel चयन समय
	 * adding TSF as one of the factor क्रम when to चयन
	 */
	अगर (il->ucode_beacon_समय > tsf_low && beacon_पूर्णांकerval) अणु
		अगर (चयन_count >
		    ((il->ucode_beacon_समय - tsf_low) / beacon_पूर्णांकerval)) अणु
			चयन_count -=
			    (il->ucode_beacon_समय - tsf_low) / beacon_पूर्णांकerval;
		पूर्ण अन्यथा
			चयन_count = 0;
	पूर्ण
	अगर (चयन_count <= 1)
		cmd.चयन_समय = cpu_to_le32(il->ucode_beacon_समय);
	अन्यथा अणु
		चयन_समय_in_usec =
		    vअगर->bss_conf.beacon_पूर्णांक * चयन_count * TIME_UNIT;
		ucode_चयन_समय =
		    il_usecs_to_beacons(il, चयन_समय_in_usec,
					beacon_पूर्णांकerval);
		cmd.चयन_समय =
		    il_add_beacon_समय(il, il->ucode_beacon_समय,
				       ucode_चयन_समय, beacon_पूर्णांकerval);
	पूर्ण
	D_11H("uCode time for the switch is 0x%x\n", cmd.चयन_समय);
	ch_info = il_get_channel_info(il, il->band, ch);
	अगर (ch_info)
		cmd.expect_beacon = il_is_channel_radar(ch_info);
	अन्यथा अणु
		IL_ERR("invalid channel switch from %u to %u\n",
		       il->active.channel, ch);
		वापस -EFAULT;
	पूर्ण

	rc = il4965_fill_txघातer_tbl(il, band, ch, is_ht40, ctrl_chan_high,
				     &cmd.tx_घातer);
	अगर (rc) अणु
		D_11H("error:%d  fill txpower_tbl\n", rc);
		वापस rc;
	पूर्ण

	वापस il_send_cmd_pdu(il, C_CHANNEL_SWITCH, माप(cmd), &cmd);
पूर्ण

/*
 * il4965_txq_update_byte_cnt_tbl - Set up entry in Tx byte-count array
 */
अटल व्योम
il4965_txq_update_byte_cnt_tbl(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq,
			       u16 byte_cnt)
अणु
	काष्ठा il4965_scd_bc_tbl *scd_bc_tbl = il->scd_bc_tbls.addr;
	पूर्णांक txq_id = txq->q.id;
	पूर्णांक ग_लिखो_ptr = txq->q.ग_लिखो_ptr;
	पूर्णांक len = byte_cnt + IL_TX_CRC_SIZE + IL_TX_DELIMITER_SIZE;
	__le16 bc_ent;

	WARN_ON(len > 0xFFF || ग_लिखो_ptr >= TFD_QUEUE_SIZE_MAX);

	bc_ent = cpu_to_le16(len & 0xFFF);
	/* Set up byte count within first 256 entries */
	scd_bc_tbl[txq_id].tfd_offset[ग_लिखो_ptr] = bc_ent;

	/* If within first 64 entries, duplicate at end */
	अगर (ग_लिखो_ptr < TFD_QUEUE_SIZE_BC_DUP)
		scd_bc_tbl[txq_id].tfd_offset[TFD_QUEUE_SIZE_MAX + ग_लिखो_ptr] =
		    bc_ent;
पूर्ण

/*
 * il4965_hw_get_temperature - वापस the calibrated temperature (in Kelvin)
 *
 * A वापस of <0 indicates bogus data in the stats
 */
अटल पूर्णांक
il4965_hw_get_temperature(काष्ठा il_priv *il)
अणु
	s32 temperature;
	s32 vt;
	s32 R1, R2, R3;
	u32 R4;

	अगर (test_bit(S_TEMPERATURE, &il->status) &&
	    (il->_4965.stats.flag & STATS_REPLY_FLG_HT40_MODE_MSK)) अणु
		D_TEMP("Running HT40 temperature calibration\n");
		R1 = (s32) le32_to_cpu(il->card_alive_init.therm_r1[1]);
		R2 = (s32) le32_to_cpu(il->card_alive_init.therm_r2[1]);
		R3 = (s32) le32_to_cpu(il->card_alive_init.therm_r3[1]);
		R4 = le32_to_cpu(il->card_alive_init.therm_r4[1]);
	पूर्ण अन्यथा अणु
		D_TEMP("Running temperature calibration\n");
		R1 = (s32) le32_to_cpu(il->card_alive_init.therm_r1[0]);
		R2 = (s32) le32_to_cpu(il->card_alive_init.therm_r2[0]);
		R3 = (s32) le32_to_cpu(il->card_alive_init.therm_r3[0]);
		R4 = le32_to_cpu(il->card_alive_init.therm_r4[0]);
	पूर्ण

	/*
	 * Temperature is only 23 bits, so sign extend out to 32.
	 *
	 * NOTE If we haven't received a stats notअगरication yet
	 * with an updated temperature, use R4 provided to us in the
	 * "initialize" ALIVE response.
	 */
	अगर (!test_bit(S_TEMPERATURE, &il->status))
		vt = sign_extend32(R4, 23);
	अन्यथा
		vt = sign_extend32(le32_to_cpu
				   (il->_4965.stats.general.common.temperature),
				   23);

	D_TEMP("Calib values R[1-3]: %d %d %d R4: %d\n", R1, R2, R3, vt);

	अगर (R3 == R1) अणु
		IL_ERR("Calibration conflict R1 == R3\n");
		वापस -1;
	पूर्ण

	/* Calculate temperature in degrees Kelvin, adjust by 97%.
	 * Add offset to center the adjusपंचांगent around 0 degrees Centigrade. */
	temperature = TEMPERATURE_CALIB_A_VAL * (vt - R2);
	temperature /= (R3 - R1);
	temperature =
	    (temperature * 97) / 100 + TEMPERATURE_CALIB_KELVIN_OFFSET;

	D_TEMP("Calibrated temperature: %dK, %ldC\n", temperature,
	       kelvin_to_celsius(temperature));

	वापस temperature;
पूर्ण

/* Adjust Txघातer only अगर temperature variance is greater than threshold. */
#घोषणा IL_TEMPERATURE_THRESHOLD   3

/*
 * il4965_is_temp_calib_needed - determines अगर new calibration is needed
 *
 * If the temperature changed has changed sufficiently, then a recalibration
 * is needed.
 *
 * Assumes caller will replace il->last_temperature once calibration
 * executed.
 */
अटल पूर्णांक
il4965_is_temp_calib_needed(काष्ठा il_priv *il)
अणु
	पूर्णांक temp_dअगरf;

	अगर (!test_bit(S_STATS, &il->status)) अणु
		D_TEMP("Temperature not updated -- no stats.\n");
		वापस 0;
	पूर्ण

	temp_dअगरf = il->temperature - il->last_temperature;

	/* get असलolute value */
	अगर (temp_dअगरf < 0) अणु
		D_POWER("Getting cooler, delta %d\n", temp_dअगरf);
		temp_dअगरf = -temp_dअगरf;
	पूर्ण अन्यथा अगर (temp_dअगरf == 0)
		D_POWER("Temperature unchanged\n");
	अन्यथा
		D_POWER("Getting warmer, delta %d\n", temp_dअगरf);

	अगर (temp_dअगरf < IL_TEMPERATURE_THRESHOLD) अणु
		D_POWER(" => thermal txpower calib not needed\n");
		वापस 0;
	पूर्ण

	D_POWER(" => thermal txpower calib needed\n");

	वापस 1;
पूर्ण

व्योम
il4965_temperature_calib(काष्ठा il_priv *il)
अणु
	s32 temp;

	temp = il4965_hw_get_temperature(il);
	अगर (IL_TX_POWER_TEMPERATURE_OUT_OF_RANGE(temp))
		वापस;

	अगर (il->temperature != temp) अणु
		अगर (il->temperature)
			D_TEMP("Temperature changed " "from %ldC to %ldC\n",
			       kelvin_to_celsius(il->temperature),
			       kelvin_to_celsius(temp));
		अन्यथा
			D_TEMP("Temperature " "initialized to %ldC\n",
			       kelvin_to_celsius(temp));
	पूर्ण

	il->temperature = temp;
	set_bit(S_TEMPERATURE, &il->status);

	अगर (!il->disable_tx_घातer_cal &&
	    unlikely(!test_bit(S_SCANNING, &il->status)) &&
	    il4965_is_temp_calib_needed(il))
		queue_work(il->workqueue, &il->txघातer_work);
पूर्ण

अटल u16
il4965_get_hcmd_size(u8 cmd_id, u16 len)
अणु
	चयन (cmd_id) अणु
	हाल C_RXON:
		वापस (u16) माप(काष्ठा il4965_rxon_cmd);
	शेष:
		वापस len;
	पूर्ण
पूर्ण

अटल u16
il4965_build_addsta_hcmd(स्थिर काष्ठा il_addsta_cmd *cmd, u8 * data)
अणु
	काष्ठा il4965_addsta_cmd *addsta = (काष्ठा il4965_addsta_cmd *)data;
	addsta->mode = cmd->mode;
	स_नकल(&addsta->sta, &cmd->sta, माप(काष्ठा sta_id_modअगरy));
	स_नकल(&addsta->key, &cmd->key, माप(काष्ठा il4965_keyinfo));
	addsta->station_flags = cmd->station_flags;
	addsta->station_flags_msk = cmd->station_flags_msk;
	addsta->tid_disable_tx = cmd->tid_disable_tx;
	addsta->add_immediate_ba_tid = cmd->add_immediate_ba_tid;
	addsta->हटाओ_immediate_ba_tid = cmd->हटाओ_immediate_ba_tid;
	addsta->add_immediate_ba_ssn = cmd->add_immediate_ba_ssn;
	addsta->sleep_tx_count = cmd->sleep_tx_count;
	addsta->reserved1 = cpu_to_le16(0);
	addsta->reserved2 = cpu_to_le16(0);

	वापस (u16) माप(काष्ठा il4965_addsta_cmd);
पूर्ण

अटल व्योम
il4965_post_scan(काष्ठा il_priv *il)
अणु
	/*
	 * Since setting the RXON may have been deferred जबतक
	 * perक्रमming the scan, fire one off अगर needed
	 */
	अगर (स_भेद(&il->staging, &il->active, माप(il->staging)))
		il_commit_rxon(il);
पूर्ण

अटल व्योम
il4965_post_associate(काष्ठा il_priv *il)
अणु
	काष्ठा ieee80211_vअगर *vअगर = il->vअगर;
	पूर्णांक ret = 0;

	अगर (!vअगर || !il->is_खोलो)
		वापस;

	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस;

	il_scan_cancel_समयout(il, 200);

	il->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	il_commit_rxon(il);

	ret = il_send_rxon_timing(il);
	अगर (ret)
		IL_WARN("RXON timing - " "Attempting to continue.\n");

	il->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;

	il_set_rxon_ht(il, &il->current_ht_config);

	अगर (il->ops->set_rxon_chain)
		il->ops->set_rxon_chain(il);

	il->staging.assoc_id = cpu_to_le16(vअगर->bss_conf.aid);

	D_ASSOC("assoc id %d beacon interval %d\n", vअगर->bss_conf.aid,
		vअगर->bss_conf.beacon_पूर्णांक);

	अगर (vअगर->bss_conf.use_लघु_preamble)
		il->staging.flags |= RXON_FLG_SHORT_PREAMBLE_MSK;
	अन्यथा
		il->staging.flags &= ~RXON_FLG_SHORT_PREAMBLE_MSK;

	अगर (il->staging.flags & RXON_FLG_BAND_24G_MSK) अणु
		अगर (vअगर->bss_conf.use_लघु_slot)
			il->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
		अन्यथा
			il->staging.flags &= ~RXON_FLG_SHORT_SLOT_MSK;
	पूर्ण

	il_commit_rxon(il);

	D_ASSOC("Associated as %d to: %pM\n", vअगर->bss_conf.aid,
		il->active.bssid_addr);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		il4965_send_beacon_cmd(il);
		अवरोध;
	शेष:
		IL_ERR("%s Should not be called in %d mode\n", __func__,
		       vअगर->type);
		अवरोध;
	पूर्ण

	/* the chain noise calibration will enabled PM upon completion
	 * If chain noise has alपढ़ोy been run, then we need to enable
	 * घातer management here */
	अगर (il->chain_noise_data.state == IL_CHAIN_NOISE_DONE)
		il_घातer_update_mode(il, false);

	/* Enable Rx dअगरferential gain and sensitivity calibrations */
	il4965_chain_noise_reset(il);
	il->start_calib = 1;
पूर्ण

अटल व्योम
il4965_config_ap(काष्ठा il_priv *il)
अणु
	काष्ठा ieee80211_vअगर *vअगर = il->vअगर;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&il->mutex);

	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस;

	/* The following should be करोne only at AP bring up */
	अगर (!il_is_associated(il)) अणु

		/* RXON - unassoc (to set timing command) */
		il->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;
		il_commit_rxon(il);

		/* RXON Timing */
		ret = il_send_rxon_timing(il);
		अगर (ret)
			IL_WARN("RXON timing failed - "
				"Attempting to continue.\n");

		/* AP has all antennas */
		il->chain_noise_data.active_chains = il->hw_params.valid_rx_ant;
		il_set_rxon_ht(il, &il->current_ht_config);
		अगर (il->ops->set_rxon_chain)
			il->ops->set_rxon_chain(il);

		il->staging.assoc_id = 0;

		अगर (vअगर->bss_conf.use_लघु_preamble)
			il->staging.flags |= RXON_FLG_SHORT_PREAMBLE_MSK;
		अन्यथा
			il->staging.flags &= ~RXON_FLG_SHORT_PREAMBLE_MSK;

		अगर (il->staging.flags & RXON_FLG_BAND_24G_MSK) अणु
			अगर (vअगर->bss_conf.use_लघु_slot)
				il->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
			अन्यथा
				il->staging.flags &= ~RXON_FLG_SHORT_SLOT_MSK;
		पूर्ण
		/* need to send beacon cmd beक्रमe committing assoc RXON! */
		il4965_send_beacon_cmd(il);
		/* restore RXON assoc */
		il->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;
		il_commit_rxon(il);
	पूर्ण
	il4965_send_beacon_cmd(il);
पूर्ण

स्थिर काष्ठा il_ops il4965_ops = अणु
	.txq_update_byte_cnt_tbl = il4965_txq_update_byte_cnt_tbl,
	.txq_attach_buf_to_tfd = il4965_hw_txq_attach_buf_to_tfd,
	.txq_मुक्त_tfd = il4965_hw_txq_मुक्त_tfd,
	.txq_init = il4965_hw_tx_queue_init,
	.is_valid_rtc_data_addr = il4965_hw_valid_rtc_data_addr,
	.init_alive_start = il4965_init_alive_start,
	.load_ucode = il4965_load_bsm,
	.dump_nic_error_log = il4965_dump_nic_error_log,
	.dump_fh = il4965_dump_fh,
	.set_channel_चयन = il4965_hw_channel_चयन,
	.apm_init = il_apm_init,
	.send_tx_घातer = il4965_send_tx_घातer,
	.update_chain_flags = il4965_update_chain_flags,
	.eeprom_acquire_semaphore = il4965_eeprom_acquire_semaphore,
	.eeprom_release_semaphore = il4965_eeprom_release_semaphore,

	.rxon_assoc = il4965_send_rxon_assoc,
	.commit_rxon = il4965_commit_rxon,
	.set_rxon_chain = il4965_set_rxon_chain,

	.get_hcmd_size = il4965_get_hcmd_size,
	.build_addsta_hcmd = il4965_build_addsta_hcmd,
	.request_scan = il4965_request_scan,
	.post_scan = il4965_post_scan,

	.post_associate = il4965_post_associate,
	.config_ap = il4965_config_ap,
	.manage_ibss_station = il4965_manage_ibss_station,
	.update_bcast_stations = il4965_update_bcast_stations,

	.send_led_cmd = il4965_send_led_cmd,
पूर्ण;

काष्ठा il_cfg il4965_cfg = अणु
	.name = "Intel(R) Wireless WiFi Link 4965AGN",
	.fw_name_pre = IL4965_FW_PRE,
	.ucode_api_max = IL4965_UCODE_API_MAX,
	.ucode_api_min = IL4965_UCODE_API_MIN,
	.sku = IL_SKU_A | IL_SKU_G | IL_SKU_N,
	.valid_tx_ant = ANT_AB,
	.valid_rx_ant = ANT_ABC,
	.eeprom_ver = EEPROM_4965_EEPROM_VERSION,
	.eeprom_calib_ver = EEPROM_4965_TX_POWER_VERSION,
	.mod_params = &il4965_mod_params,
	.led_mode = IL_LED_BLINK,
	/*
	 * Force use of chains B and C क्रम scan RX on 5 GHz band
	 * because the device has off-channel reception on chain A.
	 */
	.scan_rx_antennas[NL80211_BAND_5GHZ] = ANT_BC,

	.eeprom_size = IL4965_EEPROM_IMG_SIZE,
	.num_of_queues = IL49_NUM_QUEUES,
	.num_of_ampdu_queues = IL49_NUM_AMPDU_QUEUES,
	.pll_cfg_val = 0,
	.set_l0s = true,
	.use_bsm = true,
	.led_compensation = 61,
	.chain_noise_num_beacons = IL4965_CAL_NUM_BEACONS,
	.wd_समयout = IL_DEF_WD_TIMEOUT,
	.temperature_kelvin = true,
	.ucode_tracing = true,
	.sensitivity_calib_by_driver = true,
	.chain_noise_calib_by_driver = true,

	.regulatory_bands = अणु
		EEPROM_REGULATORY_BAND_1_CHANNELS,
		EEPROM_REGULATORY_BAND_2_CHANNELS,
		EEPROM_REGULATORY_BAND_3_CHANNELS,
		EEPROM_REGULATORY_BAND_4_CHANNELS,
		EEPROM_REGULATORY_BAND_5_CHANNELS,
		EEPROM_4965_REGULATORY_BAND_24_HT40_CHANNELS,
		EEPROM_4965_REGULATORY_BAND_52_HT40_CHANNELS
	पूर्ण,

पूर्ण;

/* Module firmware */
MODULE_FIRMWARE(IL4965_MODULE_FIRMWARE(IL4965_UCODE_API_MAX));
