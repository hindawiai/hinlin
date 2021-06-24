<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1251
 *
 * Copyright (C) 2008 Nokia Corporation
 */

#समावेश <linux/slab.h>

#समावेश "reg.h"
#समावेश "boot.h"
#समावेश "io.h"
#समावेश "spi.h"
#समावेश "event.h"
#समावेश "acx.h"

व्योम wl1251_boot_target_enable_पूर्णांकerrupts(काष्ठा wl1251 *wl)
अणु
	wl1251_reg_ग_लिखो32(wl, ACX_REG_INTERRUPT_MASK, ~(wl->पूर्णांकr_mask));
	wl1251_reg_ग_लिखो32(wl, HI_CFG, HI_CFG_DEF_VAL);
पूर्ण

पूर्णांक wl1251_boot_soft_reset(काष्ठा wl1251 *wl)
अणु
	अचिन्हित दीर्घ समयout;
	u32 boot_data;

	/* perक्रमm soft reset */
	wl1251_reg_ग_लिखो32(wl, ACX_REG_SLV_SOFT_RESET, ACX_SLV_SOFT_RESET_BIT);

	/* SOFT_RESET is self clearing */
	समयout = jअगरfies + usecs_to_jअगरfies(SOFT_RESET_MAX_TIME);
	जबतक (1) अणु
		boot_data = wl1251_reg_पढ़ो32(wl, ACX_REG_SLV_SOFT_RESET);
		wl1251_debug(DEBUG_BOOT, "soft reset bootdata 0x%x", boot_data);
		अगर ((boot_data & ACX_SLV_SOFT_RESET_BIT) == 0)
			अवरोध;

		अगर (समय_after(jअगरfies, समयout)) अणु
			/* 1.2 check pWhalBus->uSelfClearTime अगर the
			 * समयout was reached */
			wl1251_error("soft reset timeout");
			वापस -1;
		पूर्ण

		udelay(SOFT_RESET_STALL_TIME);
	पूर्ण

	/* disable Rx/Tx */
	wl1251_reg_ग_लिखो32(wl, ENABLE, 0x0);

	/* disable स्वतः calibration on start*/
	wl1251_reg_ग_लिखो32(wl, SPARE_A2, 0xffff);

	वापस 0;
पूर्ण

पूर्णांक wl1251_boot_init_seq(काष्ठा wl1251 *wl)
अणु
	u32 scr_pad6, init_data, पंचांगp, elp_cmd, ref_freq;

	/*
	 * col #1: INTEGER_DIVIDER
	 * col #2: FRACTIONAL_DIVIDER
	 * col #3: ATTN_BB
	 * col #4: ALPHA_BB
	 * col #5: STOP_TIME_BB
	 * col #6: BB_PLL_LOOP_FILTER
	 */
	अटल स्थिर u32 LUT[REF_FREQ_NUM][LUT_PARAM_NUM] = अणु

		अणु   83, 87381,  0xB, 5, 0xF00,  3पूर्ण, /* REF_FREQ_19_2*/
		अणु   61, 141154, 0xB, 5, 0x1450, 2पूर्ण, /* REF_FREQ_26_0*/
		अणु   41, 174763, 0xC, 6, 0x2D00, 1पूर्ण, /* REF_FREQ_38_4*/
		अणु   40, 0,      0xC, 6, 0x2EE0, 1पूर्ण, /* REF_FREQ_40_0*/
		अणु   47, 162280, 0xC, 6, 0x2760, 1पूर्ण  /* REF_FREQ_33_6        */
	पूर्ण;

	/* पढ़ो NVS params */
	scr_pad6 = wl1251_reg_पढ़ो32(wl, SCR_PAD6);
	wl1251_debug(DEBUG_BOOT, "scr_pad6 0x%x", scr_pad6);

	/* पढ़ो ELP_CMD */
	elp_cmd = wl1251_reg_पढ़ो32(wl, ELP_CMD);
	wl1251_debug(DEBUG_BOOT, "elp_cmd 0x%x", elp_cmd);

	/* set the BB calibration समय to be 300 usec (PLL_CAL_TIME) */
	ref_freq = scr_pad6 & 0x000000FF;
	wl1251_debug(DEBUG_BOOT, "ref_freq 0x%x", ref_freq);

	wl1251_reg_ग_लिखो32(wl, PLL_CAL_TIME, 0x9);

	/*
	 * PG 1.2: set the घड़ी buffer समय to be 210 usec (CLK_BUF_TIME)
	 */
	wl1251_reg_ग_लिखो32(wl, CLK_BUF_TIME, 0x6);

	/*
	 * set the घड़ी detect feature to work in the restart wu procedure
	 * (ELP_CFG_MODE[14]) and Select the घड़ी source type
	 * (ELP_CFG_MODE[13:12])
	 */
	पंचांगp = ((scr_pad6 & 0x0000FF00) << 4) | 0x00004000;
	wl1251_reg_ग_लिखो32(wl, ELP_CFG_MODE, पंचांगp);

	/* PG 1.2: enable the BB PLL fix. Enable the PLL_LIMP_CLK_EN_CMD */
	elp_cmd |= 0x00000040;
	wl1251_reg_ग_लिखो32(wl, ELP_CMD, elp_cmd);

	/* PG 1.2: Set the BB PLL stable समय to be 1000usec
	 * (PLL_STABLE_TIME) */
	wl1251_reg_ग_लिखो32(wl, CFG_PLL_SYNC_CNT, 0x20);

	/* PG 1.2: पढ़ो घड़ी request समय */
	init_data = wl1251_reg_पढ़ो32(wl, CLK_REQ_TIME);

	/*
	 * PG 1.2: set the घड़ी request समय to be ref_clk_settling_समय -
	 * 1ms = 4ms
	 */
	अगर (init_data > 0x21)
		पंचांगp = init_data - 0x21;
	अन्यथा
		पंचांगp = 0;
	wl1251_reg_ग_लिखो32(wl, CLK_REQ_TIME, पंचांगp);

	/* set BB PLL configurations in RF AFE */
	wl1251_reg_ग_लिखो32(wl, 0x003058cc, 0x4B5);

	/* set RF_AFE_REG_5 */
	wl1251_reg_ग_लिखो32(wl, 0x003058d4, 0x50);

	/* set RF_AFE_CTRL_REG_2 */
	wl1251_reg_ग_लिखो32(wl, 0x00305948, 0x11c001);

	/*
	 * change RF PLL and BB PLL भागider क्रम VCO घड़ी and adjust VCO
	 * bais current(RF_AFE_REG_13)
	 */
	wl1251_reg_ग_लिखो32(wl, 0x003058f4, 0x1e);

	/* set BB PLL configurations */
	पंचांगp = LUT[ref_freq][LUT_PARAM_INTEGER_DIVIDER] | 0x00017000;
	wl1251_reg_ग_लिखो32(wl, 0x00305840, पंचांगp);

	/* set fractional भागider according to Appendix C-BB PLL
	 * Calculations
	 */
	पंचांगp = LUT[ref_freq][LUT_PARAM_FRACTIONAL_DIVIDER];
	wl1251_reg_ग_लिखो32(wl, 0x00305844, पंचांगp);

	/* set the initial data क्रम the sigma delta */
	wl1251_reg_ग_लिखो32(wl, 0x00305848, 0x3039);

	/*
	 * set the accumulator attenuation value, calibration loop1
	 * (alpha), calibration loop2 (beta), calibration loop3 (gamma) and
	 * the VCO gain
	 */
	पंचांगp = (LUT[ref_freq][LUT_PARAM_ATTN_BB] << 16) |
		(LUT[ref_freq][LUT_PARAM_ALPHA_BB] << 12) | 0x1;
	wl1251_reg_ग_लिखो32(wl, 0x00305854, पंचांगp);

	/*
	 * set the calibration stop समय after holकरोff समय expires and set
	 * settling समय HOLD_OFF_TIME_BB
	 */
	पंचांगp = LUT[ref_freq][LUT_PARAM_STOP_TIME_BB] | 0x000A0000;
	wl1251_reg_ग_लिखो32(wl, 0x00305858, पंचांगp);

	/*
	 * set BB PLL Loop filter capacitor3- BB_C3[2:0] and set BB PLL
	 * स्थिरant leakage current to linearize PFD to 0uA -
	 * BB_ILOOPF[7:3]
	 */
	पंचांगp = LUT[ref_freq][LUT_PARAM_BB_PLL_LOOP_FILTER] | 0x00000030;
	wl1251_reg_ग_लिखो32(wl, 0x003058f8, पंचांगp);

	/*
	 * set regulator output voltage क्रम n भागider to
	 * 1.35-BB_REFDIV[1:0], set अक्षरge pump current- BB_CPGAIN[4:2],
	 * set BB PLL Loop filter capacitor2- BB_C2[7:5], set gain of BB
	 * PLL स्वतः-call to normal mode- BB_CALGAIN_3DB[8]
	 */
	wl1251_reg_ग_लिखो32(wl, 0x003058f0, 0x29);

	/* enable restart wakeup sequence (ELP_CMD[0]) */
	wl1251_reg_ग_लिखो32(wl, ELP_CMD, elp_cmd | 0x1);

	/* restart sequence completed */
	udelay(2000);

	वापस 0;
पूर्ण

अटल व्योम wl1251_boot_set_ecpu_ctrl(काष्ठा wl1251 *wl, u32 flag)
अणु
	u32 cpu_ctrl;

	/* 10.5.0 run the firmware (I) */
	cpu_ctrl = wl1251_reg_पढ़ो32(wl, ACX_REG_ECPU_CONTROL);

	/* 10.5.1 run the firmware (II) */
	cpu_ctrl &= ~flag;
	wl1251_reg_ग_लिखो32(wl, ACX_REG_ECPU_CONTROL, cpu_ctrl);
पूर्ण

पूर्णांक wl1251_boot_run_firmware(काष्ठा wl1251 *wl)
अणु
	पूर्णांक loop, ret;
	u32 chip_id, acx_पूर्णांकr;

	wl1251_boot_set_ecpu_ctrl(wl, ECPU_CONTROL_HALT);

	chip_id = wl1251_reg_पढ़ो32(wl, CHIP_ID_B);

	wl1251_debug(DEBUG_BOOT, "chip id after firmware boot: 0x%x", chip_id);

	अगर (chip_id != wl->chip_id) अणु
		wl1251_error("chip id doesn't match after firmware boot");
		वापस -EIO;
	पूर्ण

	/* रुको क्रम init to complete */
	loop = 0;
	जबतक (loop++ < INIT_LOOP) अणु
		udelay(INIT_LOOP_DELAY);
		acx_पूर्णांकr = wl1251_reg_पढ़ो32(wl, ACX_REG_INTERRUPT_NO_CLEAR);

		अगर (acx_पूर्णांकr == 0xffffffff) अणु
			wl1251_error("error reading hardware complete "
				     "init indication");
			वापस -EIO;
		पूर्ण
		/* check that ACX_INTR_INIT_COMPLETE is enabled */
		अन्यथा अगर (acx_पूर्णांकr & WL1251_ACX_INTR_INIT_COMPLETE) अणु
			wl1251_reg_ग_लिखो32(wl, ACX_REG_INTERRUPT_ACK,
					   WL1251_ACX_INTR_INIT_COMPLETE);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (loop > INIT_LOOP) अणु
		wl1251_error("timeout waiting for the hardware to "
			     "complete initialization");
		वापस -EIO;
	पूर्ण

	/* get hardware config command mail box */
	wl->cmd_box_addr = wl1251_reg_पढ़ो32(wl, REG_COMMAND_MAILBOX_PTR);

	/* get hardware config event mail box */
	wl->event_box_addr = wl1251_reg_पढ़ो32(wl, REG_EVENT_MAILBOX_PTR);

	/* set the working partition to its "running" mode offset */
	wl1251_set_partition(wl, WL1251_PART_WORK_MEM_START,
			     WL1251_PART_WORK_MEM_SIZE,
			     WL1251_PART_WORK_REG_START,
			     WL1251_PART_WORK_REG_SIZE);

	wl1251_debug(DEBUG_MAILBOX, "cmd_box_addr 0x%x event_box_addr 0x%x",
		     wl->cmd_box_addr, wl->event_box_addr);

	wl1251_acx_fw_version(wl, wl->fw_ver, माप(wl->fw_ver));

	/*
	 * in हाल of full asynchronous mode the firmware event must be
	 * पढ़ोy to receive event from the command mailbox
	 */

	/* enable gpio पूर्णांकerrupts */
	wl1251_enable_पूर्णांकerrupts(wl);

	/* Enable target's पूर्णांकerrupts */
	wl->पूर्णांकr_mask = WL1251_ACX_INTR_RX0_DATA |
		WL1251_ACX_INTR_RX1_DATA |
		WL1251_ACX_INTR_TX_RESULT |
		WL1251_ACX_INTR_EVENT_A |
		WL1251_ACX_INTR_EVENT_B |
		WL1251_ACX_INTR_INIT_COMPLETE;
	wl1251_boot_target_enable_पूर्णांकerrupts(wl);

	wl->event_mask = SCAN_COMPLETE_EVENT_ID | BSS_LOSE_EVENT_ID |
		SYNCHRONIZATION_TIMEOUT_EVENT_ID |
		ROAMING_TRIGGER_LOW_RSSI_EVENT_ID |
		ROAMING_TRIGGER_REGAINED_RSSI_EVENT_ID |
		REGAINED_BSS_EVENT_ID | BT_PTA_SENSE_EVENT_ID |
		BT_PTA_PREDICTION_EVENT_ID | JOIN_EVENT_COMPLETE_ID |
		PS_REPORT_EVENT_ID;

	ret = wl1251_event_unmask(wl);
	अगर (ret < 0) अणु
		wl1251_error("EVENT mask setting failed");
		वापस ret;
	पूर्ण

	wl1251_event_mbox_config(wl);

	/* firmware startup completed */
	वापस 0;
पूर्ण

अटल पूर्णांक wl1251_boot_upload_firmware(काष्ठा wl1251 *wl)
अणु
	पूर्णांक addr, chunk_num, partition_limit;
	माप_प्रकार fw_data_len, len;
	u8 *p, *buf;

	/* whal_FwCtrl_LoadFwImageSm() */

	wl1251_debug(DEBUG_BOOT, "chip id before fw upload: 0x%x",
		     wl1251_reg_पढ़ो32(wl, CHIP_ID_B));

	/* 10.0 check firmware length and set partition */
	fw_data_len =  (wl->fw[4] << 24) | (wl->fw[5] << 16) |
		(wl->fw[6] << 8) | (wl->fw[7]);

	wl1251_debug(DEBUG_BOOT, "fw_data_len %zu chunk_size %d", fw_data_len,
		CHUNK_SIZE);

	अगर ((fw_data_len % 4) != 0) अणु
		wl1251_error("firmware length not multiple of four");
		वापस -EIO;
	पूर्ण

	buf = kदो_स्मृति(CHUNK_SIZE, GFP_KERNEL);
	अगर (!buf) अणु
		wl1251_error("allocation for firmware upload chunk failed");
		वापस -ENOMEM;
	पूर्ण

	wl1251_set_partition(wl, WL1251_PART_DOWN_MEM_START,
			     WL1251_PART_DOWN_MEM_SIZE,
			     WL1251_PART_DOWN_REG_START,
			     WL1251_PART_DOWN_REG_SIZE);

	/* 10.1 set partition limit and chunk num */
	chunk_num = 0;
	partition_limit = WL1251_PART_DOWN_MEM_SIZE;

	जबतक (chunk_num < fw_data_len / CHUNK_SIZE) अणु
		/* 10.2 update partition, अगर needed */
		addr = WL1251_PART_DOWN_MEM_START +
			(chunk_num + 2) * CHUNK_SIZE;
		अगर (addr > partition_limit) अणु
			addr = WL1251_PART_DOWN_MEM_START +
				chunk_num * CHUNK_SIZE;
			partition_limit = chunk_num * CHUNK_SIZE +
				WL1251_PART_DOWN_MEM_SIZE;
			wl1251_set_partition(wl,
					     addr,
					     WL1251_PART_DOWN_MEM_SIZE,
					     WL1251_PART_DOWN_REG_START,
					     WL1251_PART_DOWN_REG_SIZE);
		पूर्ण

		/* 10.3 upload the chunk */
		addr = WL1251_PART_DOWN_MEM_START + chunk_num * CHUNK_SIZE;
		p = wl->fw + FW_HDR_SIZE + chunk_num * CHUNK_SIZE;
		wl1251_debug(DEBUG_BOOT, "uploading fw chunk 0x%p to 0x%x",
			     p, addr);

		/* need to copy the chunk क्रम dma */
		len = CHUNK_SIZE;
		स_नकल(buf, p, len);
		wl1251_mem_ग_लिखो(wl, addr, buf, len);

		chunk_num++;
	पूर्ण

	/* 10.4 upload the last chunk */
	addr = WL1251_PART_DOWN_MEM_START + chunk_num * CHUNK_SIZE;
	p = wl->fw + FW_HDR_SIZE + chunk_num * CHUNK_SIZE;

	/* need to copy the chunk क्रम dma */
	len = fw_data_len % CHUNK_SIZE;
	स_नकल(buf, p, len);

	wl1251_debug(DEBUG_BOOT, "uploading fw last chunk (%zu B) 0x%p to 0x%x",
		     len, p, addr);
	wl1251_mem_ग_लिखो(wl, addr, buf, len);

	kमुक्त(buf);

	वापस 0;
पूर्ण

अटल पूर्णांक wl1251_boot_upload_nvs(काष्ठा wl1251 *wl)
अणु
	माप_प्रकार nvs_len, nvs_bytes_written, burst_len;
	पूर्णांक nvs_start, i;
	u32 dest_addr, val;
	u8 *nvs_ptr, *nvs;

	nvs = wl->nvs;
	अगर (nvs == शून्य)
		वापस -ENODEV;

	nvs_ptr = nvs;

	nvs_len = wl->nvs_len;
	nvs_start = wl->fw_len;

	/*
	 * Layout beक्रमe the actual NVS tables:
	 * 1 byte : burst length.
	 * 2 bytes: destination address.
	 * n bytes: data to burst copy.
	 *
	 * This is ended by a 0 length, then the NVS tables.
	 */

	जबतक (nvs_ptr[0]) अणु
		burst_len = nvs_ptr[0];
		dest_addr = (nvs_ptr[1] & 0xfe) | ((u32)(nvs_ptr[2] << 8));

		/* We move our poपूर्णांकer to the data */
		nvs_ptr += 3;

		क्रम (i = 0; i < burst_len; i++) अणु
			val = (nvs_ptr[0] | (nvs_ptr[1] << 8)
			       | (nvs_ptr[2] << 16) | (nvs_ptr[3] << 24));

			wl1251_debug(DEBUG_BOOT,
				     "nvs burst write 0x%x: 0x%x",
				     dest_addr, val);
			wl1251_mem_ग_लिखो32(wl, dest_addr, val);

			nvs_ptr += 4;
			dest_addr += 4;
		पूर्ण
	पूर्ण

	/*
	 * We've reached the first zero length, the first NVS table
	 * is 7 bytes further.
	 */
	nvs_ptr += 7;
	nvs_len -= nvs_ptr - nvs;
	nvs_len = ALIGN(nvs_len, 4);

	/* Now we must set the partition correctly */
	wl1251_set_partition(wl, nvs_start,
			     WL1251_PART_DOWN_MEM_SIZE,
			     WL1251_PART_DOWN_REG_START,
			     WL1251_PART_DOWN_REG_SIZE);

	/* And finally we upload the NVS tables */
	nvs_bytes_written = 0;
	जबतक (nvs_bytes_written < nvs_len) अणु
		val = (nvs_ptr[0] | (nvs_ptr[1] << 8)
		       | (nvs_ptr[2] << 16) | (nvs_ptr[3] << 24));

		wl1251_debug(DEBUG_BOOT,
			     "nvs write table 0x%x: 0x%x",
			     nvs_start, val);
		wl1251_mem_ग_लिखो32(wl, nvs_start, val);

		nvs_ptr += 4;
		nvs_bytes_written += 4;
		nvs_start += 4;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wl1251_boot(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret = 0, minor_minor_e2_ver;
	u32 पंचांगp, boot_data;

	/* halt embedded ARM CPU जबतक loading firmware */
	wl1251_reg_ग_लिखो32(wl, ACX_REG_ECPU_CONTROL, ECPU_CONTROL_HALT);

	ret = wl1251_boot_soft_reset(wl);
	अगर (ret < 0)
		जाओ out;

	/* 2. start processing NVS file */
	अगर (wl->use_eeprom) अणु
		wl1251_reg_ग_लिखो32(wl, ACX_REG_EE_START, START_EEPROM_MGR);
		/* Wait क्रम EEPROM NVS burst पढ़ो to complete */
		msleep(40);
		wl1251_reg_ग_लिखो32(wl, ACX_EEPROMLESS_IND_REG, USE_EEPROM);
	पूर्ण अन्यथा अणु
		ret = wl1251_boot_upload_nvs(wl);
		अगर (ret < 0)
			जाओ out;

		/* ग_लिखो firmware's last address (ie. it's length) to
		 * ACX_EEPROMLESS_IND_REG */
		wl1251_reg_ग_लिखो32(wl, ACX_EEPROMLESS_IND_REG, wl->fw_len);
	पूर्ण

	/* 6. पढ़ो the EEPROM parameters */
	पंचांगp = wl1251_reg_पढ़ो32(wl, SCR_PAD2);

	/* 7. पढ़ो bootdata */
	wl->boot_attr.radio_type = (पंचांगp & 0x0000FF00) >> 8;
	wl->boot_attr.major = (पंचांगp & 0x00FF0000) >> 16;
	पंचांगp = wl1251_reg_पढ़ो32(wl, SCR_PAD3);

	/* 8. check bootdata and call restart sequence */
	wl->boot_attr.minor = (पंचांगp & 0x00FF0000) >> 16;
	minor_minor_e2_ver = (पंचांगp & 0xFF000000) >> 24;

	wl1251_debug(DEBUG_BOOT, "radioType 0x%x majorE2Ver 0x%x "
		     "minorE2Ver 0x%x minor_minor_e2_ver 0x%x",
		     wl->boot_attr.radio_type, wl->boot_attr.major,
		     wl->boot_attr.minor, minor_minor_e2_ver);

	ret = wl1251_boot_init_seq(wl);
	अगर (ret < 0)
		जाओ out;

	/* 9. NVS processing करोne */
	boot_data = wl1251_reg_पढ़ो32(wl, ACX_REG_ECPU_CONTROL);

	wl1251_debug(DEBUG_BOOT, "halt boot_data 0x%x", boot_data);

	/* 10. check that ECPU_CONTROL_HALT bits are set in
	 * pWhalBus->uBootData and start uploading firmware
	 */
	अगर ((boot_data & ECPU_CONTROL_HALT) == 0) अणु
		wl1251_error("boot failed, ECPU_CONTROL_HALT not set");
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret = wl1251_boot_upload_firmware(wl);
	अगर (ret < 0)
		जाओ out;

	/* 10.5 start firmware */
	ret = wl1251_boot_run_firmware(wl);
	अगर (ret < 0)
		जाओ out;

out:
	वापस ret;
पूर्ण
