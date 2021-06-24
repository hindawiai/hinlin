<शैली गुरु>
/*
 * Copyright(c) 2015, 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <linux/firmware.h>

#समावेश "hfi.h"
#समावेश "efivar.h"
#समावेश "eprom.h"

#घोषणा DEFAULT_PLATFORM_CONFIG_NAME "hfi1_platform.dat"

अटल पूर्णांक validate_scratch_checksum(काष्ठा hfi1_devdata *dd)
अणु
	u64 checksum = 0, temp_scratch = 0;
	पूर्णांक i, j, version;

	temp_scratch = पढ़ो_csr(dd, ASIC_CFG_SCRATCH);
	version = (temp_scratch & BITMAP_VERSION_SMASK) >> BITMAP_VERSION_SHIFT;

	/* Prevent घातer on शेष of all zeroes from passing checksum */
	अगर (!version) अणु
		dd_dev_err(dd, "%s: Config bitmap uninitialized\n", __func__);
		dd_dev_err(dd,
			   "%s: Please update your BIOS to support active channels\n",
			   __func__);
		वापस 0;
	पूर्ण

	/*
	 * ASIC scratch 0 only contains the checksum and biपंचांगap version as
	 * fields of पूर्णांकerest, both of which are handled separately from the
	 * loop below, so skip it
	 */
	checksum += version;
	क्रम (i = 1; i < ASIC_NUM_SCRATCH; i++) अणु
		temp_scratch = पढ़ो_csr(dd, ASIC_CFG_SCRATCH + (8 * i));
		क्रम (j = माप(u64); j != 0; j -= 2) अणु
			checksum += (temp_scratch & 0xFFFF);
			temp_scratch >>= 16;
		पूर्ण
	पूर्ण

	जबतक (checksum >> 16)
		checksum = (checksum & CHECKSUM_MASK) + (checksum >> 16);

	temp_scratch = पढ़ो_csr(dd, ASIC_CFG_SCRATCH);
	temp_scratch &= CHECKSUM_SMASK;
	temp_scratch >>= CHECKSUM_SHIFT;

	अगर (checksum + temp_scratch == 0xFFFF)
		वापस 1;

	dd_dev_err(dd, "%s: Configuration bitmap corrupted\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम save_platक्रमm_config_fields(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_pportdata *ppd = dd->pport;
	u64 temp_scratch = 0, temp_dest = 0;

	temp_scratch = पढ़ो_csr(dd, ASIC_CFG_SCRATCH_1);

	temp_dest = temp_scratch &
		    (dd->hfi1_id ? PORT1_PORT_TYPE_SMASK :
		     PORT0_PORT_TYPE_SMASK);
	ppd->port_type = temp_dest >>
			 (dd->hfi1_id ? PORT1_PORT_TYPE_SHIFT :
			  PORT0_PORT_TYPE_SHIFT);

	temp_dest = temp_scratch &
		    (dd->hfi1_id ? PORT1_LOCAL_ATTEN_SMASK :
		     PORT0_LOCAL_ATTEN_SMASK);
	ppd->local_atten = temp_dest >>
			   (dd->hfi1_id ? PORT1_LOCAL_ATTEN_SHIFT :
			    PORT0_LOCAL_ATTEN_SHIFT);

	temp_dest = temp_scratch &
		    (dd->hfi1_id ? PORT1_REMOTE_ATTEN_SMASK :
		     PORT0_REMOTE_ATTEN_SMASK);
	ppd->remote_atten = temp_dest >>
			    (dd->hfi1_id ? PORT1_REMOTE_ATTEN_SHIFT :
			     PORT0_REMOTE_ATTEN_SHIFT);

	temp_dest = temp_scratch &
		    (dd->hfi1_id ? PORT1_DEFAULT_ATTEN_SMASK :
		     PORT0_DEFAULT_ATTEN_SMASK);
	ppd->शेष_atten = temp_dest >>
			     (dd->hfi1_id ? PORT1_DEFAULT_ATTEN_SHIFT :
			      PORT0_DEFAULT_ATTEN_SHIFT);

	temp_scratch = पढ़ो_csr(dd, dd->hfi1_id ? ASIC_CFG_SCRATCH_3 :
				ASIC_CFG_SCRATCH_2);

	ppd->tx_preset_eq = (temp_scratch & TX_EQ_SMASK) >> TX_EQ_SHIFT;
	ppd->tx_preset_noeq = (temp_scratch & TX_NO_EQ_SMASK) >> TX_NO_EQ_SHIFT;
	ppd->rx_preset = (temp_scratch & RX_SMASK) >> RX_SHIFT;

	ppd->max_घातer_class = (temp_scratch & QSFP_MAX_POWER_SMASK) >>
				QSFP_MAX_POWER_SHIFT;

	ppd->config_from_scratch = true;
पूर्ण

व्योम get_platक्रमm_config(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret = 0;
	u8 *temp_platक्रमm_config = शून्य;
	u32 esize;
	स्थिर काष्ठा firmware *platक्रमm_config_file = शून्य;

	अगर (is_पूर्णांकegrated(dd)) अणु
		अगर (validate_scratch_checksum(dd)) अणु
			save_platक्रमm_config_fields(dd);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = eprom_पढ़ो_platक्रमm_config(dd,
						 (व्योम **)&temp_platक्रमm_config,
						 &esize);
		अगर (!ret) अणु
			/* success */
			dd->platक्रमm_config.data = temp_platक्रमm_config;
			dd->platक्रमm_config.size = esize;
			वापस;
		पूर्ण
	पूर्ण
	dd_dev_err(dd,
		   "%s: Failed to get platform config, falling back to sub-optimal default file\n",
		   __func__);

	ret = request_firmware(&platक्रमm_config_file,
			       DEFAULT_PLATFORM_CONFIG_NAME,
			       &dd->pcidev->dev);
	अगर (ret) अणु
		dd_dev_err(dd,
			   "%s: No default platform config file found\n",
			   __func__);
		वापस;
	पूर्ण

	/*
	 * Allocate separate memory block to store data and मुक्त firmware
	 * काष्ठाure. This allows मुक्त_platक्रमm_config to treat EPROM and
	 * fallback configs in the same manner.
	 */
	dd->platक्रमm_config.data = kmemdup(platक्रमm_config_file->data,
					   platक्रमm_config_file->size,
					   GFP_KERNEL);
	dd->platक्रमm_config.size = platक्रमm_config_file->size;
	release_firmware(platक्रमm_config_file);
पूर्ण

व्योम मुक्त_platक्रमm_config(काष्ठा hfi1_devdata *dd)
अणु
	/* Release memory allocated क्रम eprom or fallback file पढ़ो. */
	kमुक्त(dd->platक्रमm_config.data);
	dd->platक्रमm_config.data = शून्य;
पूर्ण

व्योम get_port_type(काष्ठा hfi1_pportdata *ppd)
अणु
	पूर्णांक ret;
	u32 temp;

	ret = get_platक्रमm_config_field(ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
					PORT_TABLE_PORT_TYPE, &temp,
					4);
	अगर (ret) अणु
		ppd->port_type = PORT_TYPE_UNKNOWN;
		वापस;
	पूर्ण
	ppd->port_type = temp;
पूर्ण

पूर्णांक set_qsfp_tx(काष्ठा hfi1_pportdata *ppd, पूर्णांक on)
अणु
	u8 tx_ctrl_byte = on ? 0x0 : 0xF;
	पूर्णांक ret = 0;

	ret = qsfp_ग_लिखो(ppd, ppd->dd->hfi1_id, QSFP_TX_CTRL_BYTE_OFFS,
			 &tx_ctrl_byte, 1);
	/* we expected 1, so consider 0 an error */
	अगर (ret == 0)
		ret = -EIO;
	अन्यथा अगर (ret == 1)
		ret = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक qual_घातer(काष्ठा hfi1_pportdata *ppd)
अणु
	u32 cable_घातer_class = 0, घातer_class_max = 0;
	u8 *cache = ppd->qsfp_info.cache;
	पूर्णांक ret = 0;

	ret = get_platक्रमm_config_field(
		ppd->dd, PLATFORM_CONFIG_SYSTEM_TABLE, 0,
		SYSTEM_TABLE_QSFP_POWER_CLASS_MAX, &घातer_class_max, 4);
	अगर (ret)
		वापस ret;

	cable_घातer_class = get_qsfp_घातer_class(cache[QSFP_MOD_PWR_OFFS]);

	अगर (cable_घातer_class > घातer_class_max)
		ppd->offline_disabled_reason =
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_POWER_POLICY);

	अगर (ppd->offline_disabled_reason ==
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_POWER_POLICY)) अणु
		dd_dev_err(
			ppd->dd,
			"%s: Port disabled due to system power restrictions\n",
			__func__);
		ret = -EPERM;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक qual_bitrate(काष्ठा hfi1_pportdata *ppd)
अणु
	u16 lss = ppd->link_speed_supported, lse = ppd->link_speed_enabled;
	u8 *cache = ppd->qsfp_info.cache;

	अगर ((lss & OPA_LINK_SPEED_25G) && (lse & OPA_LINK_SPEED_25G) &&
	    cache[QSFP_NOM_BIT_RATE_250_OFFS] < 0x64)
		ppd->offline_disabled_reason =
			   HFI1_ODR_MASK(OPA_LINKDOWN_REASON_LINKSPEED_POLICY);

	अगर ((lss & OPA_LINK_SPEED_12_5G) && (lse & OPA_LINK_SPEED_12_5G) &&
	    cache[QSFP_NOM_BIT_RATE_100_OFFS] < 0x7D)
		ppd->offline_disabled_reason =
			   HFI1_ODR_MASK(OPA_LINKDOWN_REASON_LINKSPEED_POLICY);

	अगर (ppd->offline_disabled_reason ==
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_LINKSPEED_POLICY)) अणु
		dd_dev_err(
			ppd->dd,
			"%s: Cable failed bitrate check, disabling port\n",
			__func__);
		वापस -EPERM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक set_qsfp_high_घातer(काष्ठा hfi1_pportdata *ppd)
अणु
	u8 cable_घातer_class = 0, घातer_ctrl_byte = 0;
	u8 *cache = ppd->qsfp_info.cache;
	पूर्णांक ret;

	cable_घातer_class = get_qsfp_घातer_class(cache[QSFP_MOD_PWR_OFFS]);

	अगर (cable_घातer_class > QSFP_POWER_CLASS_1) अणु
		घातer_ctrl_byte = cache[QSFP_PWR_CTRL_BYTE_OFFS];

		घातer_ctrl_byte |= 1;
		घातer_ctrl_byte &= ~(0x2);

		ret = qsfp_ग_लिखो(ppd, ppd->dd->hfi1_id,
				 QSFP_PWR_CTRL_BYTE_OFFS,
				 &घातer_ctrl_byte, 1);
		अगर (ret != 1)
			वापस -EIO;

		अगर (cable_घातer_class > QSFP_POWER_CLASS_4) अणु
			घातer_ctrl_byte |= (1 << 2);
			ret = qsfp_ग_लिखो(ppd, ppd->dd->hfi1_id,
					 QSFP_PWR_CTRL_BYTE_OFFS,
					 &घातer_ctrl_byte, 1);
			अगर (ret != 1)
				वापस -EIO;
		पूर्ण

		/* SFF 8679 rev 1.7 LPMode Deनिश्चित समय */
		msleep(300);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम apply_rx_cdr(काष्ठा hfi1_pportdata *ppd,
			 u32 rx_preset_index,
			 u8 *cdr_ctrl_byte)
अणु
	u32 rx_preset;
	u8 *cache = ppd->qsfp_info.cache;
	पूर्णांक cable_घातer_class;

	अगर (!((cache[QSFP_MOD_PWR_OFFS] & 0x4) &&
	      (cache[QSFP_CDR_INFO_OFFS] & 0x40)))
		वापस;

	/* RX CDR present, bypass supported */
	cable_घातer_class = get_qsfp_घातer_class(cache[QSFP_MOD_PWR_OFFS]);

	अगर (cable_घातer_class <= QSFP_POWER_CLASS_3) अणु
		/* Power class <= 3, ignore config & turn RX CDR on */
		*cdr_ctrl_byte |= 0xF;
		वापस;
	पूर्ण

	get_platक्रमm_config_field(
		ppd->dd, PLATFORM_CONFIG_RX_PRESET_TABLE,
		rx_preset_index, RX_PRESET_TABLE_QSFP_RX_CDR_APPLY,
		&rx_preset, 4);

	अगर (!rx_preset) अणु
		dd_dev_info(
			ppd->dd,
			"%s: RX_CDR_APPLY is set to disabled\n",
			__func__);
		वापस;
	पूर्ण
	get_platक्रमm_config_field(
		ppd->dd, PLATFORM_CONFIG_RX_PRESET_TABLE,
		rx_preset_index, RX_PRESET_TABLE_QSFP_RX_CDR,
		&rx_preset, 4);

	/* Expand cdr setting to all 4 lanes */
	rx_preset = (rx_preset | (rx_preset << 1) |
			(rx_preset << 2) | (rx_preset << 3));

	अगर (rx_preset) अणु
		*cdr_ctrl_byte |= rx_preset;
	पूर्ण अन्यथा अणु
		*cdr_ctrl_byte &= rx_preset;
		/* Preserve current TX CDR status */
		*cdr_ctrl_byte |= (cache[QSFP_CDR_CTRL_BYTE_OFFS] & 0xF0);
	पूर्ण
पूर्ण

अटल व्योम apply_tx_cdr(काष्ठा hfi1_pportdata *ppd,
			 u32 tx_preset_index,
			 u8 *cdr_ctrl_byte)
अणु
	u32 tx_preset;
	u8 *cache = ppd->qsfp_info.cache;
	पूर्णांक cable_घातer_class;

	अगर (!((cache[QSFP_MOD_PWR_OFFS] & 0x8) &&
	      (cache[QSFP_CDR_INFO_OFFS] & 0x80)))
		वापस;

	/* TX CDR present, bypass supported */
	cable_घातer_class = get_qsfp_घातer_class(cache[QSFP_MOD_PWR_OFFS]);

	अगर (cable_घातer_class <= QSFP_POWER_CLASS_3) अणु
		/* Power class <= 3, ignore config & turn TX CDR on */
		*cdr_ctrl_byte |= 0xF0;
		वापस;
	पूर्ण

	get_platक्रमm_config_field(
		ppd->dd,
		PLATFORM_CONFIG_TX_PRESET_TABLE, tx_preset_index,
		TX_PRESET_TABLE_QSFP_TX_CDR_APPLY, &tx_preset, 4);

	अगर (!tx_preset) अणु
		dd_dev_info(
			ppd->dd,
			"%s: TX_CDR_APPLY is set to disabled\n",
			__func__);
		वापस;
	पूर्ण
	get_platक्रमm_config_field(
		ppd->dd,
		PLATFORM_CONFIG_TX_PRESET_TABLE,
		tx_preset_index,
		TX_PRESET_TABLE_QSFP_TX_CDR, &tx_preset, 4);

	/* Expand cdr setting to all 4 lanes */
	tx_preset = (tx_preset | (tx_preset << 1) |
			(tx_preset << 2) | (tx_preset << 3));

	अगर (tx_preset)
		*cdr_ctrl_byte |= (tx_preset << 4);
	अन्यथा
		/* Preserve current/determined RX CDR status */
		*cdr_ctrl_byte &= ((tx_preset << 4) | 0xF);
पूर्ण

अटल व्योम apply_cdr_settings(
		काष्ठा hfi1_pportdata *ppd, u32 rx_preset_index,
		u32 tx_preset_index)
अणु
	u8 *cache = ppd->qsfp_info.cache;
	u8 cdr_ctrl_byte = cache[QSFP_CDR_CTRL_BYTE_OFFS];

	apply_rx_cdr(ppd, rx_preset_index, &cdr_ctrl_byte);

	apply_tx_cdr(ppd, tx_preset_index, &cdr_ctrl_byte);

	qsfp_ग_लिखो(ppd, ppd->dd->hfi1_id, QSFP_CDR_CTRL_BYTE_OFFS,
		   &cdr_ctrl_byte, 1);
पूर्ण

अटल व्योम apply_tx_eq_स्वतः(काष्ठा hfi1_pportdata *ppd)
अणु
	u8 *cache = ppd->qsfp_info.cache;
	u8 tx_eq;

	अगर (!(cache[QSFP_EQ_INFO_OFFS] & 0x8))
		वापस;
	/* Disable adaptive TX EQ अगर present */
	tx_eq = cache[(128 * 3) + 241];
	tx_eq &= 0xF0;
	qsfp_ग_लिखो(ppd, ppd->dd->hfi1_id, (256 * 3) + 241, &tx_eq, 1);
पूर्ण

अटल व्योम apply_tx_eq_prog(काष्ठा hfi1_pportdata *ppd, u32 tx_preset_index)
अणु
	u8 *cache = ppd->qsfp_info.cache;
	u32 tx_preset;
	u8 tx_eq;

	अगर (!(cache[QSFP_EQ_INFO_OFFS] & 0x4))
		वापस;

	get_platक्रमm_config_field(
		ppd->dd, PLATFORM_CONFIG_TX_PRESET_TABLE,
		tx_preset_index, TX_PRESET_TABLE_QSFP_TX_EQ_APPLY,
		&tx_preset, 4);
	अगर (!tx_preset) अणु
		dd_dev_info(
			ppd->dd,
			"%s: TX_EQ_APPLY is set to disabled\n",
			__func__);
		वापस;
	पूर्ण
	get_platक्रमm_config_field(
			ppd->dd, PLATFORM_CONFIG_TX_PRESET_TABLE,
			tx_preset_index, TX_PRESET_TABLE_QSFP_TX_EQ,
			&tx_preset, 4);

	अगर (((cache[(128 * 3) + 224] & 0xF0) >> 4) < tx_preset) अणु
		dd_dev_info(
			ppd->dd,
			"%s: TX EQ %x unsupported\n",
			__func__, tx_preset);

		dd_dev_info(
			ppd->dd,
			"%s: Applying EQ %x\n",
			__func__, cache[608] & 0xF0);

		tx_preset = (cache[608] & 0xF0) >> 4;
	पूर्ण

	tx_eq = tx_preset | (tx_preset << 4);
	qsfp_ग_लिखो(ppd, ppd->dd->hfi1_id, (256 * 3) + 234, &tx_eq, 1);
	qsfp_ग_लिखो(ppd, ppd->dd->hfi1_id, (256 * 3) + 235, &tx_eq, 1);
पूर्ण

अटल व्योम apply_rx_eq_emp(काष्ठा hfi1_pportdata *ppd, u32 rx_preset_index)
अणु
	u32 rx_preset;
	u8 rx_eq, *cache = ppd->qsfp_info.cache;

	अगर (!(cache[QSFP_EQ_INFO_OFFS] & 0x2))
		वापस;
	get_platक्रमm_config_field(
			ppd->dd, PLATFORM_CONFIG_RX_PRESET_TABLE,
			rx_preset_index, RX_PRESET_TABLE_QSFP_RX_EMP_APPLY,
			&rx_preset, 4);

	अगर (!rx_preset) अणु
		dd_dev_info(
			ppd->dd,
			"%s: RX_EMP_APPLY is set to disabled\n",
			__func__);
		वापस;
	पूर्ण
	get_platक्रमm_config_field(
		ppd->dd, PLATFORM_CONFIG_RX_PRESET_TABLE,
		rx_preset_index, RX_PRESET_TABLE_QSFP_RX_EMP,
		&rx_preset, 4);

	अगर ((cache[(128 * 3) + 224] & 0xF) < rx_preset) अणु
		dd_dev_info(
			ppd->dd,
			"%s: Requested RX EMP %x\n",
			__func__, rx_preset);

		dd_dev_info(
			ppd->dd,
			"%s: Applying supported EMP %x\n",
			__func__, cache[608] & 0xF);

		rx_preset = cache[608] & 0xF;
	पूर्ण

	rx_eq = rx_preset | (rx_preset << 4);

	qsfp_ग_लिखो(ppd, ppd->dd->hfi1_id, (256 * 3) + 236, &rx_eq, 1);
	qsfp_ग_लिखो(ppd, ppd->dd->hfi1_id, (256 * 3) + 237, &rx_eq, 1);
पूर्ण

अटल व्योम apply_eq_settings(काष्ठा hfi1_pportdata *ppd,
			      u32 rx_preset_index, u32 tx_preset_index)
अणु
	u8 *cache = ppd->qsfp_info.cache;

	/* no poपूर्णांक going on w/o a page 3 */
	अगर (cache[2] & 4) अणु
		dd_dev_info(ppd->dd,
			    "%s: Upper page 03 not present\n",
			    __func__);
		वापस;
	पूर्ण

	apply_tx_eq_स्वतः(ppd);

	apply_tx_eq_prog(ppd, tx_preset_index);

	apply_rx_eq_emp(ppd, rx_preset_index);
पूर्ण

अटल व्योम apply_rx_amplitude_settings(
		काष्ठा hfi1_pportdata *ppd, u32 rx_preset_index,
		u32 tx_preset_index)
अणु
	u32 rx_preset;
	u8 rx_amp = 0, i = 0, preferred = 0, *cache = ppd->qsfp_info.cache;

	/* no poपूर्णांक going on w/o a page 3 */
	अगर (cache[2] & 4) अणु
		dd_dev_info(ppd->dd,
			    "%s: Upper page 03 not present\n",
			    __func__);
		वापस;
	पूर्ण
	अगर (!(cache[QSFP_EQ_INFO_OFFS] & 0x1)) अणु
		dd_dev_info(ppd->dd,
			    "%s: RX_AMP_APPLY is set to disabled\n",
			    __func__);
		वापस;
	पूर्ण

	get_platक्रमm_config_field(ppd->dd,
				  PLATFORM_CONFIG_RX_PRESET_TABLE,
				  rx_preset_index,
				  RX_PRESET_TABLE_QSFP_RX_AMP_APPLY,
				  &rx_preset, 4);

	अगर (!rx_preset) अणु
		dd_dev_info(ppd->dd,
			    "%s: RX_AMP_APPLY is set to disabled\n",
			    __func__);
		वापस;
	पूर्ण
	get_platक्रमm_config_field(ppd->dd,
				  PLATFORM_CONFIG_RX_PRESET_TABLE,
				  rx_preset_index,
				  RX_PRESET_TABLE_QSFP_RX_AMP,
				  &rx_preset, 4);

	dd_dev_info(ppd->dd,
		    "%s: Requested RX AMP %x\n",
		    __func__,
		    rx_preset);

	क्रम (i = 0; i < 4; i++) अणु
		अगर (cache[(128 * 3) + 225] & (1 << i)) अणु
			preferred = i;
			अगर (preferred == rx_preset)
				अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Verअगरy that preferred RX amplitude is not just a
	 * fall through of the शेष
	 */
	अगर (!preferred && !(cache[(128 * 3) + 225] & 0x1)) अणु
		dd_dev_info(ppd->dd, "No supported RX AMP, not applying\n");
		वापस;
	पूर्ण

	dd_dev_info(ppd->dd,
		    "%s: Applying RX AMP %x\n", __func__, preferred);

	rx_amp = preferred | (preferred << 4);
	qsfp_ग_लिखो(ppd, ppd->dd->hfi1_id, (256 * 3) + 238, &rx_amp, 1);
	qsfp_ग_लिखो(ppd, ppd->dd->hfi1_id, (256 * 3) + 239, &rx_amp, 1);
पूर्ण

#घोषणा OPA_INVALID_INDEX 0xFFF

अटल व्योम apply_tx_lanes(काष्ठा hfi1_pportdata *ppd, u8 field_id,
			   u32 config_data, स्थिर अक्षर *message)
अणु
	u8 i;
	पूर्णांक ret;

	क्रम (i = 0; i < 4; i++) अणु
		ret = load_8051_config(ppd->dd, field_id, i, config_data);
		अगर (ret != HCMD_SUCCESS) अणु
			dd_dev_err(
				ppd->dd,
				"%s: %s for lane %u failed\n",
				message, __func__, i);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Return a special SerDes setting क्रम low घातer AOC cables.  The घातer class
 * threshold and setting being used were all found by empirical testing.
 *
 * Summary of the logic:
 *
 * अगर (QSFP and QSFP_TYPE == AOC and QSFP_POWER_CLASS < 4)
 *     वापस 0xe
 * वापस 0; // leave at शेष
 */
अटल u8 aoc_low_घातer_setting(काष्ठा hfi1_pportdata *ppd)
अणु
	u8 *cache = ppd->qsfp_info.cache;
	पूर्णांक घातer_class;

	/* QSFP only */
	अगर (ppd->port_type != PORT_TYPE_QSFP)
		वापस 0; /* leave at शेष */

	/* active optical cables only */
	चयन ((cache[QSFP_MOD_TECH_OFFS] & 0xF0) >> 4) अणु
	हाल 0x0 ... 0x9: fallthrough;
	हाल 0xC: fallthrough;
	हाल 0xE:
		/* active AOC */
		घातer_class = get_qsfp_घातer_class(cache[QSFP_MOD_PWR_OFFS]);
		अगर (घातer_class < QSFP_POWER_CLASS_4)
			वापस 0xe;
	पूर्ण
	वापस 0; /* leave at शेष */
पूर्ण

अटल व्योम apply_tunings(
		काष्ठा hfi1_pportdata *ppd, u32 tx_preset_index,
		u8 tuning_method, u32 total_atten, u8 limiting_active)
अणु
	पूर्णांक ret = 0;
	u32 config_data = 0, tx_preset = 0;
	u8 precur = 0, attn = 0, postcur = 0, बाह्यal_device_config = 0;
	u8 *cache = ppd->qsfp_info.cache;

	/* Pass tuning method to 8051 */
	पढ़ो_8051_config(ppd->dd, LINK_TUNING_PARAMETERS, GENERAL_CONFIG,
			 &config_data);
	config_data &= ~(0xff << TUNING_METHOD_SHIFT);
	config_data |= ((u32)tuning_method << TUNING_METHOD_SHIFT);
	ret = load_8051_config(ppd->dd, LINK_TUNING_PARAMETERS, GENERAL_CONFIG,
			       config_data);
	अगर (ret != HCMD_SUCCESS)
		dd_dev_err(ppd->dd, "%s: Failed to set tuning method\n",
			   __func__);

	/* Set same channel loss क्रम both TX and RX */
	config_data = 0 | (total_atten << 16) | (total_atten << 24);
	apply_tx_lanes(ppd, CHANNEL_LOSS_SETTINGS, config_data,
		       "Setting channel loss");

	/* Inक्रमm 8051 of cable capabilities */
	अगर (ppd->qsfp_info.cache_valid) अणु
		बाह्यal_device_config =
			((cache[QSFP_MOD_PWR_OFFS] & 0x4) << 3) |
			((cache[QSFP_MOD_PWR_OFFS] & 0x8) << 2) |
			((cache[QSFP_EQ_INFO_OFFS] & 0x2) << 1) |
			(cache[QSFP_EQ_INFO_OFFS] & 0x4);
		ret = पढ़ो_8051_config(ppd->dd, DC_HOST_COMM_SETTINGS,
				       GENERAL_CONFIG, &config_data);
		/* Clear, then set the बाह्यal device config field */
		config_data &= ~(u32)0xFF;
		config_data |= बाह्यal_device_config;
		ret = load_8051_config(ppd->dd, DC_HOST_COMM_SETTINGS,
				       GENERAL_CONFIG, config_data);
		अगर (ret != HCMD_SUCCESS)
			dd_dev_err(ppd->dd,
				   "%s: Failed set ext device config params\n",
				   __func__);
	पूर्ण

	अगर (tx_preset_index == OPA_INVALID_INDEX) अणु
		अगर (ppd->port_type == PORT_TYPE_QSFP && limiting_active)
			dd_dev_err(ppd->dd, "%s: Invalid Tx preset index\n",
				   __func__);
		वापस;
	पूर्ण

	/* Following क्रम limiting active channels only */
	get_platक्रमm_config_field(
		ppd->dd, PLATFORM_CONFIG_TX_PRESET_TABLE, tx_preset_index,
		TX_PRESET_TABLE_PRECUR, &tx_preset, 4);
	precur = tx_preset;

	get_platक्रमm_config_field(
		ppd->dd, PLATFORM_CONFIG_TX_PRESET_TABLE,
		tx_preset_index, TX_PRESET_TABLE_ATTN, &tx_preset, 4);
	attn = tx_preset;

	get_platक्रमm_config_field(
		ppd->dd, PLATFORM_CONFIG_TX_PRESET_TABLE,
		tx_preset_index, TX_PRESET_TABLE_POSTCUR, &tx_preset, 4);
	postcur = tx_preset;

	/*
	 * NOTES:
	 * o The aoc_low_घातer_setting is applied to all lanes even
	 *   though only lane 0's value is examined by the firmware.
	 * o A lingering low घातer setting after a cable swap करोes
	 *   not occur.  On cable unplug the 8051 is reset and
	 *   restarted on cable insert.  This resets all settings to
	 *   their शेष, erasing any previous low घातer setting.
	 */
	config_data = precur | (attn << 8) | (postcur << 16) |
			(aoc_low_घातer_setting(ppd) << 24);

	apply_tx_lanes(ppd, TX_EQ_SETTINGS, config_data,
		       "Applying TX settings");
पूर्ण

/* Must be holding the QSFP i2c resource */
अटल पूर्णांक tune_active_qsfp(काष्ठा hfi1_pportdata *ppd, u32 *ptr_tx_preset,
			    u32 *ptr_rx_preset, u32 *ptr_total_atten)
अणु
	पूर्णांक ret;
	u16 lss = ppd->link_speed_supported, lse = ppd->link_speed_enabled;
	u8 *cache = ppd->qsfp_info.cache;

	ppd->qsfp_info.limiting_active = 1;

	ret = set_qsfp_tx(ppd, 0);
	अगर (ret)
		वापस ret;

	ret = qual_घातer(ppd);
	अगर (ret)
		वापस ret;

	ret = qual_bitrate(ppd);
	अगर (ret)
		वापस ret;

	/*
	 * We'll change the QSFP memory contents from here on out, thus we set a
	 * flag here to remind ourselves to reset the QSFP module. This prevents
	 * reuse of stale settings established in our previous pass through.
	 */
	अगर (ppd->qsfp_info.reset_needed) अणु
		ret = reset_qsfp(ppd);
		अगर (ret)
			वापस ret;
		refresh_qsfp_cache(ppd, &ppd->qsfp_info);
	पूर्ण अन्यथा अणु
		ppd->qsfp_info.reset_needed = 1;
	पूर्ण

	ret = set_qsfp_high_घातer(ppd);
	अगर (ret)
		वापस ret;

	अगर (cache[QSFP_EQ_INFO_OFFS] & 0x4) अणु
		ret = get_platक्रमm_config_field(
			ppd->dd,
			PLATFORM_CONFIG_PORT_TABLE, 0,
			PORT_TABLE_TX_PRESET_IDX_ACTIVE_EQ,
			ptr_tx_preset, 4);
		अगर (ret) अणु
			*ptr_tx_preset = OPA_INVALID_INDEX;
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = get_platक्रमm_config_field(
			ppd->dd,
			PLATFORM_CONFIG_PORT_TABLE, 0,
			PORT_TABLE_TX_PRESET_IDX_ACTIVE_NO_EQ,
			ptr_tx_preset, 4);
		अगर (ret) अणु
			*ptr_tx_preset = OPA_INVALID_INDEX;
			वापस ret;
		पूर्ण
	पूर्ण

	ret = get_platक्रमm_config_field(
		ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
		PORT_TABLE_RX_PRESET_IDX, ptr_rx_preset, 4);
	अगर (ret) अणु
		*ptr_rx_preset = OPA_INVALID_INDEX;
		वापस ret;
	पूर्ण

	अगर ((lss & OPA_LINK_SPEED_25G) && (lse & OPA_LINK_SPEED_25G))
		get_platक्रमm_config_field(
			ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
			PORT_TABLE_LOCAL_ATTEN_25G, ptr_total_atten, 4);
	अन्यथा अगर ((lss & OPA_LINK_SPEED_12_5G) && (lse & OPA_LINK_SPEED_12_5G))
		get_platक्रमm_config_field(
			ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
			PORT_TABLE_LOCAL_ATTEN_12G, ptr_total_atten, 4);

	apply_cdr_settings(ppd, *ptr_rx_preset, *ptr_tx_preset);

	apply_eq_settings(ppd, *ptr_rx_preset, *ptr_tx_preset);

	apply_rx_amplitude_settings(ppd, *ptr_rx_preset, *ptr_tx_preset);

	ret = set_qsfp_tx(ppd, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक tune_qsfp(काष्ठा hfi1_pportdata *ppd,
		     u32 *ptr_tx_preset, u32 *ptr_rx_preset,
		     u8 *ptr_tuning_method, u32 *ptr_total_atten)
अणु
	u32 cable_atten = 0, remote_atten = 0, platक्रमm_atten = 0;
	u16 lss = ppd->link_speed_supported, lse = ppd->link_speed_enabled;
	पूर्णांक ret = 0;
	u8 *cache = ppd->qsfp_info.cache;

	चयन ((cache[QSFP_MOD_TECH_OFFS] & 0xF0) >> 4) अणु
	हाल 0xA ... 0xB:
		ret = get_platक्रमm_config_field(
			ppd->dd,
			PLATFORM_CONFIG_PORT_TABLE, 0,
			PORT_TABLE_LOCAL_ATTEN_25G,
			&platक्रमm_atten, 4);
		अगर (ret)
			वापस ret;

		अगर ((lss & OPA_LINK_SPEED_25G) && (lse & OPA_LINK_SPEED_25G))
			cable_atten = cache[QSFP_CU_ATTEN_12G_OFFS];
		अन्यथा अगर ((lss & OPA_LINK_SPEED_12_5G) &&
			 (lse & OPA_LINK_SPEED_12_5G))
			cable_atten = cache[QSFP_CU_ATTEN_7G_OFFS];

		/* Fallback to configured attenuation अगर cable memory is bad */
		अगर (cable_atten == 0 || cable_atten > 36) अणु
			ret = get_platक्रमm_config_field(
				ppd->dd,
				PLATFORM_CONFIG_SYSTEM_TABLE, 0,
				SYSTEM_TABLE_QSFP_ATTENUATION_DEFAULT_25G,
				&cable_atten, 4);
			अगर (ret)
				वापस ret;
		पूर्ण

		ret = get_platक्रमm_config_field(
			ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
			PORT_TABLE_REMOTE_ATTEN_25G, &remote_atten, 4);
		अगर (ret)
			वापस ret;

		*ptr_total_atten = platक्रमm_atten + cable_atten + remote_atten;

		*ptr_tuning_method = OPA_PASSIVE_TUNING;
		अवरोध;
	हाल 0x0 ... 0x9: fallthrough;
	हाल 0xC: fallthrough;
	हाल 0xE:
		ret = tune_active_qsfp(ppd, ptr_tx_preset, ptr_rx_preset,
				       ptr_total_atten);
		अगर (ret)
			वापस ret;

		*ptr_tuning_method = OPA_ACTIVE_TUNING;
		अवरोध;
	हाल 0xD: fallthrough;
	हाल 0xF:
	शेष:
		dd_dev_warn(ppd->dd, "%s: Unknown/unsupported cable\n",
			    __func__);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * This function communicates its success or failure via ppd->driver_link_पढ़ोy
 * Thus, it depends on its association with start_link(...) which checks
 * driver_link_पढ़ोy beक्रमe proceeding with the link negotiation and
 * initialization process.
 */
व्योम tune_serdes(काष्ठा hfi1_pportdata *ppd)
अणु
	पूर्णांक ret = 0;
	u32 total_atten = 0;
	u32 remote_atten = 0, platक्रमm_atten = 0;
	u32 rx_preset_index, tx_preset_index;
	u8 tuning_method = 0, limiting_active = 0;
	काष्ठा hfi1_devdata *dd = ppd->dd;

	rx_preset_index = OPA_INVALID_INDEX;
	tx_preset_index = OPA_INVALID_INDEX;

	/* the link शेषs to enabled */
	ppd->link_enabled = 1;
	/* the driver link पढ़ोy state शेषs to not पढ़ोy */
	ppd->driver_link_पढ़ोy = 0;
	ppd->offline_disabled_reason = HFI1_ODR_MASK(OPA_LINKDOWN_REASON_NONE);

	/* Skip the tuning क्रम testing (loopback != none) and simulations */
	अगर (loopback != LOOPBACK_NONE ||
	    ppd->dd->icode == ICODE_FUNCTIONAL_SIMULATOR) अणु
		ppd->driver_link_पढ़ोy = 1;

		अगर (qsfp_mod_present(ppd)) अणु
			ret = acquire_chip_resource(ppd->dd,
						    qsfp_resource(ppd->dd),
						    QSFP_WAIT);
			अगर (ret) अणु
				dd_dev_err(ppd->dd, "%s: hfi%d: cannot lock i2c chain\n",
					   __func__, (पूर्णांक)ppd->dd->hfi1_id);
				जाओ bail;
			पूर्ण

			refresh_qsfp_cache(ppd, &ppd->qsfp_info);
			release_chip_resource(ppd->dd, qsfp_resource(ppd->dd));
		पूर्ण

		वापस;
	पूर्ण

	चयन (ppd->port_type) अणु
	हाल PORT_TYPE_DISCONNECTED:
		ppd->offline_disabled_reason =
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_DISCONNECTED);
		dd_dev_warn(dd, "%s: Port disconnected, disabling port\n",
			    __func__);
		जाओ bail;
	हाल PORT_TYPE_FIXED:
		/* platक्रमm_atten, remote_atten pre-zeroed to catch error */
		get_platक्रमm_config_field(
			ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
			PORT_TABLE_LOCAL_ATTEN_25G, &platक्रमm_atten, 4);

		get_platक्रमm_config_field(
			ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
			PORT_TABLE_REMOTE_ATTEN_25G, &remote_atten, 4);

		total_atten = platक्रमm_atten + remote_atten;

		tuning_method = OPA_PASSIVE_TUNING;
		अवरोध;
	हाल PORT_TYPE_VARIABLE:
		अगर (qsfp_mod_present(ppd)) अणु
			/*
			 * platक्रमm_atten, remote_atten pre-zeroed to
			 * catch error
			 */
			get_platक्रमm_config_field(
				ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
				PORT_TABLE_LOCAL_ATTEN_25G,
				&platक्रमm_atten, 4);

			get_platक्रमm_config_field(
				ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
				PORT_TABLE_REMOTE_ATTEN_25G,
				&remote_atten, 4);

			total_atten = platक्रमm_atten + remote_atten;

			tuning_method = OPA_PASSIVE_TUNING;
		पूर्ण अन्यथा अणु
			ppd->offline_disabled_reason =
			     HFI1_ODR_MASK(OPA_LINKDOWN_REASON_CHASSIS_CONFIG);
			जाओ bail;
		पूर्ण
		अवरोध;
	हाल PORT_TYPE_QSFP:
		अगर (qsfp_mod_present(ppd)) अणु
			ret = acquire_chip_resource(ppd->dd,
						    qsfp_resource(ppd->dd),
						    QSFP_WAIT);
			अगर (ret) अणु
				dd_dev_err(ppd->dd, "%s: hfi%d: cannot lock i2c chain\n",
					   __func__, (पूर्णांक)ppd->dd->hfi1_id);
				जाओ bail;
			पूर्ण
			refresh_qsfp_cache(ppd, &ppd->qsfp_info);

			अगर (ppd->qsfp_info.cache_valid) अणु
				ret = tune_qsfp(ppd,
						&tx_preset_index,
						&rx_preset_index,
						&tuning_method,
						&total_atten);

				/*
				 * We may have modअगरied the QSFP memory, so
				 * update the cache to reflect the changes
				 */
				refresh_qsfp_cache(ppd, &ppd->qsfp_info);
				limiting_active =
						ppd->qsfp_info.limiting_active;
			पूर्ण अन्यथा अणु
				dd_dev_err(dd,
					   "%s: Reading QSFP memory failed\n",
					   __func__);
				ret = -EINVAL; /* a fail indication */
			पूर्ण
			release_chip_resource(ppd->dd, qsfp_resource(ppd->dd));
			अगर (ret)
				जाओ bail;
		पूर्ण अन्यथा अणु
			ppd->offline_disabled_reason =
			   HFI1_ODR_MASK(
				OPA_LINKDOWN_REASON_LOCAL_MEDIA_NOT_INSTALLED);
			जाओ bail;
		पूर्ण
		अवरोध;
	शेष:
		dd_dev_warn(ppd->dd, "%s: Unknown port type\n", __func__);
		ppd->port_type = PORT_TYPE_UNKNOWN;
		tuning_method = OPA_UNKNOWN_TUNING;
		total_atten = 0;
		limiting_active = 0;
		tx_preset_index = OPA_INVALID_INDEX;
		अवरोध;
	पूर्ण

	अगर (ppd->offline_disabled_reason ==
			HFI1_ODR_MASK(OPA_LINKDOWN_REASON_NONE))
		apply_tunings(ppd, tx_preset_index, tuning_method,
			      total_atten, limiting_active);

	अगर (!ret)
		ppd->driver_link_पढ़ोy = 1;

	वापस;
bail:
	ppd->driver_link_पढ़ोy = 0;
पूर्ण
