<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2019 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <linux/firmware.h>
#समावेश <linux/rtnetlink.h>
#समावेश "iwl-trans.h"
#समावेश "iwl-csr.h"
#समावेश "mvm.h"
#समावेश "iwl-eeprom-parse.h"
#समावेश "iwl-eeprom-read.h"
#समावेश "iwl-nvm-parse.h"
#समावेश "iwl-prph.h"
#समावेश "fw/acpi.h"

/* Default NVM size to पढ़ो */
#घोषणा IWL_NVM_DEFAULT_CHUNK_SIZE (2 * 1024)

#घोषणा NVM_WRITE_OPCODE 1
#घोषणा NVM_READ_OPCODE 0

/* load nvm chunk response */
क्रमागत अणु
	READ_NVM_CHUNK_SUCCEED = 0,
	READ_NVM_CHUNK_NOT_VALID_ADDRESS = 1
पूर्ण;

/*
 * prepare the NVM host command w/ the poपूर्णांकers to the nvm buffer
 * and send it to fw
 */
अटल पूर्णांक iwl_nvm_ग_लिखो_chunk(काष्ठा iwl_mvm *mvm, u16 section,
			       u16 offset, u16 length, स्थिर u8 *data)
अणु
	काष्ठा iwl_nvm_access_cmd nvm_access_cmd = अणु
		.offset = cpu_to_le16(offset),
		.length = cpu_to_le16(length),
		.type = cpu_to_le16(section),
		.op_code = NVM_WRITE_OPCODE,
	पूर्ण;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = NVM_ACCESS_CMD,
		.len = अणु माप(काष्ठा iwl_nvm_access_cmd), length पूर्ण,
		.flags = CMD_WANT_SKB | CMD_SEND_IN_RFKILL,
		.data = अणु &nvm_access_cmd, data पूर्ण,
		/* data may come from vदो_स्मृति, so use _DUP */
		.dataflags = अणु 0, IWL_HCMD_DFL_DUP पूर्ण,
	पूर्ण;
	काष्ठा iwl_rx_packet *pkt;
	काष्ठा iwl_nvm_access_resp *nvm_resp;
	पूर्णांक ret;

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	अगर (ret)
		वापस ret;

	pkt = cmd.resp_pkt;
	/* Extract & check NVM ग_लिखो response */
	nvm_resp = (व्योम *)pkt->data;
	अगर (le16_to_cpu(nvm_resp->status) != READ_NVM_CHUNK_SUCCEED) अणु
		IWL_ERR(mvm,
			"NVM access write command failed for section %u (status = 0x%x)\n",
			section, le16_to_cpu(nvm_resp->status));
		ret = -EIO;
	पूर्ण

	iwl_मुक्त_resp(&cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_nvm_पढ़ो_chunk(काष्ठा iwl_mvm *mvm, u16 section,
			      u16 offset, u16 length, u8 *data)
अणु
	काष्ठा iwl_nvm_access_cmd nvm_access_cmd = अणु
		.offset = cpu_to_le16(offset),
		.length = cpu_to_le16(length),
		.type = cpu_to_le16(section),
		.op_code = NVM_READ_OPCODE,
	पूर्ण;
	काष्ठा iwl_nvm_access_resp *nvm_resp;
	काष्ठा iwl_rx_packet *pkt;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = NVM_ACCESS_CMD,
		.flags = CMD_WANT_SKB | CMD_SEND_IN_RFKILL,
		.data = अणु &nvm_access_cmd, पूर्ण,
	पूर्ण;
	पूर्णांक ret, bytes_पढ़ो, offset_पढ़ो;
	u8 *resp_data;

	cmd.len[0] = माप(काष्ठा iwl_nvm_access_cmd);

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	अगर (ret)
		वापस ret;

	pkt = cmd.resp_pkt;

	/* Extract NVM response */
	nvm_resp = (व्योम *)pkt->data;
	ret = le16_to_cpu(nvm_resp->status);
	bytes_पढ़ो = le16_to_cpu(nvm_resp->length);
	offset_पढ़ो = le16_to_cpu(nvm_resp->offset);
	resp_data = nvm_resp->data;
	अगर (ret) अणु
		अगर ((offset != 0) &&
		    (ret == READ_NVM_CHUNK_NOT_VALID_ADDRESS)) अणु
			/*
			 * meaning of NOT_VALID_ADDRESS:
			 * driver try to पढ़ो chunk from address that is
			 * multiple of 2K and got an error since addr is empty.
			 * meaning of (offset != 0): driver alपढ़ोy
			 * पढ़ो valid data from another chunk so this हाल
			 * is not an error.
			 */
			IWL_DEBUG_EEPROM(mvm->trans->dev,
					 "NVM access command failed on offset 0x%x since that section size is multiple 2K\n",
					 offset);
			ret = 0;
		पूर्ण अन्यथा अणु
			IWL_DEBUG_EEPROM(mvm->trans->dev,
					 "NVM access command failed with status %d (device: %s)\n",
					 ret, mvm->trans->name);
			ret = -ENODATA;
		पूर्ण
		जाओ निकास;
	पूर्ण

	अगर (offset_पढ़ो != offset) अणु
		IWL_ERR(mvm, "NVM ACCESS response with invalid offset %d\n",
			offset_पढ़ो);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	/* Write data to NVM */
	स_नकल(data + offset, resp_data, bytes_पढ़ो);
	ret = bytes_पढ़ो;

निकास:
	iwl_मुक्त_resp(&cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_nvm_ग_लिखो_section(काष्ठा iwl_mvm *mvm, u16 section,
				 स्थिर u8 *data, u16 length)
अणु
	पूर्णांक offset = 0;

	/* copy data in chunks of 2k (and reमुख्यder अगर any) */

	जबतक (offset < length) अणु
		पूर्णांक chunk_size, ret;

		chunk_size = min(IWL_NVM_DEFAULT_CHUNK_SIZE,
				 length - offset);

		ret = iwl_nvm_ग_लिखो_chunk(mvm, section, offset,
					  chunk_size, data + offset);
		अगर (ret < 0)
			वापस ret;

		offset += chunk_size;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Reads an NVM section completely.
 * NICs prior to 7000 family करोesn't have a real NVM, but just पढ़ो
 * section 0 which is the EEPROM. Because the EEPROM पढ़ोing is unlimited
 * by uCode, we need to manually check in this हाल that we करोn't
 * overflow and try to पढ़ो more than the EEPROM size.
 * For 7000 family NICs, we supply the maximal size we can पढ़ो, and
 * the uCode fills the response with as much data as we can,
 * without overflowing, so no check is needed.
 */
अटल पूर्णांक iwl_nvm_पढ़ो_section(काष्ठा iwl_mvm *mvm, u16 section,
				u8 *data, u32 size_पढ़ो)
अणु
	u16 length, offset = 0;
	पूर्णांक ret;

	/* Set nvm section पढ़ो length */
	length = IWL_NVM_DEFAULT_CHUNK_SIZE;

	ret = length;

	/* Read the NVM until exhausted (पढ़ोing less than requested) */
	जबतक (ret == length) अणु
		/* Check no memory assumptions fail and cause an overflow */
		अगर ((size_पढ़ो + offset + length) >
		    mvm->trans->trans_cfg->base_params->eeprom_size) अणु
			IWL_ERR(mvm, "EEPROM size is too small for NVM\n");
			वापस -ENOBUFS;
		पूर्ण

		ret = iwl_nvm_पढ़ो_chunk(mvm, section, offset, length, data);
		अगर (ret < 0) अणु
			IWL_DEBUG_EEPROM(mvm->trans->dev,
					 "Cannot read NVM from section %d offset %d, length %d\n",
					 section, offset, length);
			वापस ret;
		पूर्ण
		offset += ret;
	पूर्ण

	iwl_nvm_fixups(mvm->trans->hw_id, section, data, offset);

	IWL_DEBUG_EEPROM(mvm->trans->dev,
			 "NVM section %d read completed\n", section);
	वापस offset;
पूर्ण

अटल काष्ठा iwl_nvm_data *
iwl_parse_nvm_sections(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_nvm_section *sections = mvm->nvm_sections;
	स्थिर __be16 *hw;
	स्थिर __le16 *sw, *calib, *regulatory, *mac_override, *phy_sku;
	पूर्णांक regulatory_type;

	/* Checking क्रम required sections */
	अगर (mvm->trans->cfg->nvm_type == IWL_NVM) अणु
		अगर (!mvm->nvm_sections[NVM_SECTION_TYPE_SW].data ||
		    !mvm->nvm_sections[mvm->cfg->nvm_hw_section_num].data) अणु
			IWL_ERR(mvm, "Can't parse empty OTP/NVM sections\n");
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (mvm->trans->cfg->nvm_type == IWL_NVM_SDP)
			regulatory_type = NVM_SECTION_TYPE_REGULATORY_SDP;
		अन्यथा
			regulatory_type = NVM_SECTION_TYPE_REGULATORY;

		/* SW and REGULATORY sections are mandatory */
		अगर (!mvm->nvm_sections[NVM_SECTION_TYPE_SW].data ||
		    !mvm->nvm_sections[regulatory_type].data) अणु
			IWL_ERR(mvm,
				"Can't parse empty family 8000 OTP/NVM sections\n");
			वापस शून्य;
		पूर्ण
		/* MAC_OVERRIDE or at least HW section must exist */
		अगर (!mvm->nvm_sections[mvm->cfg->nvm_hw_section_num].data &&
		    !mvm->nvm_sections[NVM_SECTION_TYPE_MAC_OVERRIDE].data) अणु
			IWL_ERR(mvm,
				"Can't parse mac_address, empty sections\n");
			वापस शून्य;
		पूर्ण

		/* PHY_SKU section is mandatory in B0 */
		अगर (mvm->trans->cfg->nvm_type == IWL_NVM_EXT &&
		    !mvm->nvm_sections[NVM_SECTION_TYPE_PHY_SKU].data) अणु
			IWL_ERR(mvm,
				"Can't parse phy_sku in B0, empty sections\n");
			वापस शून्य;
		पूर्ण
	पूर्ण

	hw = (स्थिर __be16 *)sections[mvm->cfg->nvm_hw_section_num].data;
	sw = (स्थिर __le16 *)sections[NVM_SECTION_TYPE_SW].data;
	calib = (स्थिर __le16 *)sections[NVM_SECTION_TYPE_CALIBRATION].data;
	mac_override =
		(स्थिर __le16 *)sections[NVM_SECTION_TYPE_MAC_OVERRIDE].data;
	phy_sku = (स्थिर __le16 *)sections[NVM_SECTION_TYPE_PHY_SKU].data;

	regulatory = mvm->trans->cfg->nvm_type == IWL_NVM_SDP ?
		(स्थिर __le16 *)sections[NVM_SECTION_TYPE_REGULATORY_SDP].data :
		(स्थिर __le16 *)sections[NVM_SECTION_TYPE_REGULATORY].data;

	वापस iwl_parse_nvm_data(mvm->trans, mvm->cfg, mvm->fw, hw, sw, calib,
				  regulatory, mac_override, phy_sku,
				  mvm->fw->valid_tx_ant, mvm->fw->valid_rx_ant);
पूर्ण

/* Loads the NVM data stored in mvm->nvm_sections पूर्णांकo the NIC */
पूर्णांक iwl_mvm_load_nvm_to_nic(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा iwl_nvm_section *sections = mvm->nvm_sections;

	IWL_DEBUG_EEPROM(mvm->trans->dev, "'Write to NVM\n");

	क्रम (i = 0; i < ARRAY_SIZE(mvm->nvm_sections); i++) अणु
		अगर (!mvm->nvm_sections[i].data || !mvm->nvm_sections[i].length)
			जारी;
		ret = iwl_nvm_ग_लिखो_section(mvm, i, sections[i].data,
					    sections[i].length);
		अगर (ret < 0) अणु
			IWL_ERR(mvm, "iwl_mvm_send_cmd failed: %d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक iwl_nvm_init(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret, section;
	u32 size_पढ़ो = 0;
	u8 *nvm_buffer, *temp;
	स्थिर अक्षर *nvm_file_C = mvm->cfg->शेष_nvm_file_C_step;

	अगर (WARN_ON_ONCE(mvm->cfg->nvm_hw_section_num >= NVM_MAX_NUM_SECTIONS))
		वापस -EINVAL;

	/* load NVM values from nic */
	/* Read From FW NVM */
	IWL_DEBUG_EEPROM(mvm->trans->dev, "Read from NVM\n");

	nvm_buffer = kदो_स्मृति(mvm->trans->trans_cfg->base_params->eeprom_size,
			     GFP_KERNEL);
	अगर (!nvm_buffer)
		वापस -ENOMEM;
	क्रम (section = 0; section < NVM_MAX_NUM_SECTIONS; section++) अणु
		/* we override the स्थिरness क्रम initial पढ़ो */
		ret = iwl_nvm_पढ़ो_section(mvm, section, nvm_buffer,
					   size_पढ़ो);
		अगर (ret == -ENODATA) अणु
			ret = 0;
			जारी;
		पूर्ण
		अगर (ret < 0)
			अवरोध;
		size_पढ़ो += ret;
		temp = kmemdup(nvm_buffer, ret, GFP_KERNEL);
		अगर (!temp) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		iwl_nvm_fixups(mvm->trans->hw_id, section, temp, ret);

		mvm->nvm_sections[section].data = temp;
		mvm->nvm_sections[section].length = ret;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
		चयन (section) अणु
		हाल NVM_SECTION_TYPE_SW:
			mvm->nvm_sw_blob.data = temp;
			mvm->nvm_sw_blob.size  = ret;
			अवरोध;
		हाल NVM_SECTION_TYPE_CALIBRATION:
			mvm->nvm_calib_blob.data = temp;
			mvm->nvm_calib_blob.size  = ret;
			अवरोध;
		हाल NVM_SECTION_TYPE_PRODUCTION:
			mvm->nvm_prod_blob.data = temp;
			mvm->nvm_prod_blob.size  = ret;
			अवरोध;
		हाल NVM_SECTION_TYPE_PHY_SKU:
			mvm->nvm_phy_sku_blob.data = temp;
			mvm->nvm_phy_sku_blob.size  = ret;
			अवरोध;
		हाल NVM_SECTION_TYPE_REGULATORY_SDP:
		हाल NVM_SECTION_TYPE_REGULATORY:
			mvm->nvm_reg_blob.data = temp;
			mvm->nvm_reg_blob.size  = ret;
			अवरोध;
		शेष:
			अगर (section == mvm->cfg->nvm_hw_section_num) अणु
				mvm->nvm_hw_blob.data = temp;
				mvm->nvm_hw_blob.size = ret;
				अवरोध;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	अगर (!size_पढ़ो)
		IWL_ERR(mvm, "OTP is blank\n");
	kमुक्त(nvm_buffer);

	/* Only अगर PNVM selected in the mod param - load बाह्यal NVM  */
	अगर (mvm->nvm_file_name) अणु
		/* पढ़ो External NVM file from the mod param */
		ret = iwl_पढ़ो_बाह्यal_nvm(mvm->trans, mvm->nvm_file_name,
					    mvm->nvm_sections);
		अगर (ret) अणु
			mvm->nvm_file_name = nvm_file_C;

			अगर ((ret == -EFAULT || ret == -ENOENT) &&
			    mvm->nvm_file_name) अणु
				/* in हाल nvm file was failed try again */
				ret = iwl_पढ़ो_बाह्यal_nvm(mvm->trans,
							    mvm->nvm_file_name,
							    mvm->nvm_sections);
				अगर (ret)
					वापस ret;
			पूर्ण अन्यथा अणु
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	/* parse the relevant nvm sections */
	mvm->nvm_data = iwl_parse_nvm_sections(mvm);
	अगर (!mvm->nvm_data)
		वापस -ENODATA;
	IWL_DEBUG_EEPROM(mvm->trans->dev, "nvm version = %x\n",
			 mvm->nvm_data->nvm_version);

	वापस ret < 0 ? ret : 0;
पूर्ण

काष्ठा iwl_mcc_update_resp *
iwl_mvm_update_mcc(काष्ठा iwl_mvm *mvm, स्थिर अक्षर *alpha2,
		   क्रमागत iwl_mcc_source src_id)
अणु
	काष्ठा iwl_mcc_update_cmd mcc_update_cmd = अणु
		.mcc = cpu_to_le16(alpha2[0] << 8 | alpha2[1]),
		.source_id = (u8)src_id,
	पूर्ण;
	काष्ठा iwl_mcc_update_resp *resp_cp;
	काष्ठा iwl_rx_packet *pkt;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = MCC_UPDATE_CMD,
		.flags = CMD_WANT_SKB,
		.data = अणु &mcc_update_cmd पूर्ण,
	पूर्ण;

	पूर्णांक ret;
	u32 status;
	पूर्णांक resp_len, n_channels;
	u16 mcc;

	अगर (WARN_ON_ONCE(!iwl_mvm_is_lar_supported(mvm)))
		वापस ERR_PTR(-EOPNOTSUPP);

	cmd.len[0] = माप(काष्ठा iwl_mcc_update_cmd);

	IWL_DEBUG_LAR(mvm, "send MCC update to FW with '%c%c' src = %d\n",
		      alpha2[0], alpha2[1], src_id);

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	अगर (ret)
		वापस ERR_PTR(ret);

	pkt = cmd.resp_pkt;

	/* Extract MCC response */
	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_MCC_UPDATE_11AX_SUPPORT)) अणु
		काष्ठा iwl_mcc_update_resp *mcc_resp = (व्योम *)pkt->data;

		n_channels =  __le32_to_cpu(mcc_resp->n_channels);
		resp_len = माप(काष्ठा iwl_mcc_update_resp) +
			   n_channels * माप(__le32);
		resp_cp = kmemdup(mcc_resp, resp_len, GFP_KERNEL);
		अगर (!resp_cp) अणु
			resp_cp = ERR_PTR(-ENOMEM);
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा iwl_mcc_update_resp_v3 *mcc_resp_v3 = (व्योम *)pkt->data;

		n_channels =  __le32_to_cpu(mcc_resp_v3->n_channels);
		resp_len = माप(काष्ठा iwl_mcc_update_resp) +
			   n_channels * माप(__le32);
		resp_cp = kzalloc(resp_len, GFP_KERNEL);
		अगर (!resp_cp) अणु
			resp_cp = ERR_PTR(-ENOMEM);
			जाओ निकास;
		पूर्ण

		resp_cp->status = mcc_resp_v3->status;
		resp_cp->mcc = mcc_resp_v3->mcc;
		resp_cp->cap = cpu_to_le16(mcc_resp_v3->cap);
		resp_cp->source_id = mcc_resp_v3->source_id;
		resp_cp->समय = mcc_resp_v3->समय;
		resp_cp->geo_info = mcc_resp_v3->geo_info;
		resp_cp->n_channels = mcc_resp_v3->n_channels;
		स_नकल(resp_cp->channels, mcc_resp_v3->channels,
		       n_channels * माप(__le32));
	पूर्ण

	status = le32_to_cpu(resp_cp->status);

	mcc = le16_to_cpu(resp_cp->mcc);

	/* W/A क्रम a FW/NVM issue - वापसs 0x00 क्रम the world करोमुख्य */
	अगर (mcc == 0) अणु
		mcc = 0x3030;  /* "00" - world */
		resp_cp->mcc = cpu_to_le16(mcc);
	पूर्ण

	IWL_DEBUG_LAR(mvm,
		      "MCC response status: 0x%x. new MCC: 0x%x ('%c%c') n_chans: %d\n",
		      status, mcc, mcc >> 8, mcc & 0xff, n_channels);

निकास:
	iwl_मुक्त_resp(&cmd);
	वापस resp_cp;
पूर्ण

पूर्णांक iwl_mvm_init_mcc(काष्ठा iwl_mvm *mvm)
अणु
	bool tlv_lar;
	bool nvm_lar;
	पूर्णांक retval;
	काष्ठा ieee80211_regकरोमुख्य *regd;
	अक्षर mcc[3];

	अगर (mvm->cfg->nvm_type == IWL_NVM_EXT) अणु
		tlv_lar = fw_has_capa(&mvm->fw->ucode_capa,
				      IWL_UCODE_TLV_CAPA_LAR_SUPPORT);
		nvm_lar = mvm->nvm_data->lar_enabled;
		अगर (tlv_lar != nvm_lar)
			IWL_INFO(mvm,
				 "Conflict between TLV & NVM regarding enabling LAR (TLV = %s NVM =%s)\n",
				 tlv_lar ? "enabled" : "disabled",
				 nvm_lar ? "enabled" : "disabled");
	पूर्ण

	अगर (!iwl_mvm_is_lar_supported(mvm))
		वापस 0;

	/*
	 * try to replay the last set MCC to FW. If it करोesn't exist,
	 * queue an update to cfg80211 to retrieve the शेष alpha2 from FW.
	 */
	retval = iwl_mvm_init_fw_regd(mvm);
	अगर (retval != -ENOENT)
		वापस retval;

	/*
	 * Driver regulatory hपूर्णांक क्रम initial update, this also inक्रमms the
	 * firmware we support wअगरi location updates.
	 * Disallow scans that might crash the FW जबतक the LAR regकरोमुख्य
	 * is not set.
	 */
	mvm->lar_regकरोm_set = false;

	regd = iwl_mvm_get_current_regकरोमुख्य(mvm, शून्य);
	अगर (IS_ERR_OR_शून्य(regd))
		वापस -EIO;

	अगर (iwl_mvm_is_wअगरi_mcc_supported(mvm) &&
	    !iwl_acpi_get_mcc(mvm->dev, mcc)) अणु
		kमुक्त(regd);
		regd = iwl_mvm_get_regकरोमुख्य(mvm->hw->wiphy, mcc,
					     MCC_SOURCE_BIOS, शून्य);
		अगर (IS_ERR_OR_शून्य(regd))
			वापस -EIO;
	पूर्ण

	retval = regulatory_set_wiphy_regd_sync(mvm->hw->wiphy, regd);
	kमुक्त(regd);
	वापस retval;
पूर्ण

व्योम iwl_mvm_rx_chub_update_mcc(काष्ठा iwl_mvm *mvm,
				काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_mcc_chub_notअगर *notअगर = (व्योम *)pkt->data;
	क्रमागत iwl_mcc_source src;
	अक्षर mcc[3];
	काष्ठा ieee80211_regकरोमुख्य *regd;
	पूर्णांक wgds_tbl_idx;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (iwl_mvm_is_vअगर_assoc(mvm) && notअगर->source_id == MCC_SOURCE_WIFI) अणु
		IWL_DEBUG_LAR(mvm, "Ignore mcc update while associated\n");
		वापस;
	पूर्ण

	अगर (WARN_ON_ONCE(!iwl_mvm_is_lar_supported(mvm)))
		वापस;

	mcc[0] = le16_to_cpu(notअगर->mcc) >> 8;
	mcc[1] = le16_to_cpu(notअगर->mcc) & 0xff;
	mcc[2] = '\0';
	src = notअगर->source_id;

	IWL_DEBUG_LAR(mvm,
		      "RX: received chub update mcc cmd (mcc '%s' src %d)\n",
		      mcc, src);
	regd = iwl_mvm_get_regकरोमुख्य(mvm->hw->wiphy, mcc, src, शून्य);
	अगर (IS_ERR_OR_शून्य(regd))
		वापस;

	wgds_tbl_idx = iwl_mvm_get_sar_geo_profile(mvm);
	अगर (wgds_tbl_idx < 0)
		IWL_DEBUG_INFO(mvm, "SAR WGDS is disabled (%d)\n",
			       wgds_tbl_idx);
	अन्यथा
		IWL_DEBUG_INFO(mvm, "SAR WGDS: geo profile %d is configured\n",
			       wgds_tbl_idx);

	regulatory_set_wiphy_regd(mvm->hw->wiphy, regd);
	kमुक्त(regd);
पूर्ण
