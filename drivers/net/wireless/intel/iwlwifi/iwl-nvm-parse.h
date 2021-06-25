<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2015, 2018-2020 Intel Corporation
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_nvm_parse_h__
#घोषणा __iwl_nvm_parse_h__

#समावेश <net/cfg80211.h>
#समावेश "iwl-eeprom-parse.h"

/**
 * क्रमागत iwl_nvm_sbands_flags - modअगरication flags क्रम the channel profiles
 *
 * @IWL_NVM_SBANDS_FLAGS_LAR: LAR is enabled
 * @IWL_NVM_SBANDS_FLAGS_NO_WIDE_IN_5GHZ: disallow 40, 80 and 160MHz on 5GHz
 */
क्रमागत iwl_nvm_sbands_flags अणु
	IWL_NVM_SBANDS_FLAGS_LAR		= BIT(0),
	IWL_NVM_SBANDS_FLAGS_NO_WIDE_IN_5GHZ	= BIT(1),
पूर्ण;

/**
 * iwl_parse_nvm_data - parse NVM data and वापस values
 *
 * This function parses all NVM values we need and then
 * वापसs a (newly allocated) काष्ठा containing all the
 * relevant values क्रम driver use. The काष्ठा must be मुक्तd
 * later with iwl_मुक्त_nvm_data().
 */
काष्ठा iwl_nvm_data *
iwl_parse_nvm_data(काष्ठा iwl_trans *trans, स्थिर काष्ठा iwl_cfg *cfg,
		   स्थिर काष्ठा iwl_fw *fw,
		   स्थिर __be16 *nvm_hw, स्थिर __le16 *nvm_sw,
		   स्थिर __le16 *nvm_calib, स्थिर __le16 *regulatory,
		   स्थिर __le16 *mac_override, स्थिर __le16 *phy_sku,
		   u8 tx_chains, u8 rx_chains);

/**
 * iwl_parse_mcc_info - parse MCC (mobile country code) info coming from FW
 *
 * This function parses the regulatory channel data received as a
 * MCC_UPDATE_CMD command. It वापसs a newly allocation regulatory करोमुख्य,
 * to be fed पूर्णांकo the regulatory core. In हाल the geo_info is set handle
 * accordingly. An ERR_PTR is वापसed on error.
 * If not given to the regulatory core, the user is responsible क्रम मुक्तing
 * the regकरोमुख्य वापसed here with kमुक्त.
 */
काष्ठा ieee80211_regकरोमुख्य *
iwl_parse_nvm_mcc_info(काष्ठा device *dev, स्थिर काष्ठा iwl_cfg *cfg,
		       पूर्णांक num_of_ch, __le32 *channels, u16 fw_mcc,
		       u16 geo_info, u16 cap, u8 resp_ver);

/**
 * काष्ठा iwl_nvm_section - describes an NVM section in memory.
 *
 * This काष्ठा holds an NVM section पढ़ो from the NIC using NVM_ACCESS_CMD,
 * and saved क्रम later use by the driver. Not all NVM sections are saved
 * this way, only the needed ones.
 */
काष्ठा iwl_nvm_section अणु
	u16 length;
	स्थिर u8 *data;
पूर्ण;

/**
 * iwl_पढ़ो_बाह्यal_nvm - Reads बाह्यal NVM from a file पूर्णांकo nvm_sections
 */
पूर्णांक iwl_पढ़ो_बाह्यal_nvm(काष्ठा iwl_trans *trans,
			  स्थिर अक्षर *nvm_file_name,
			  काष्ठा iwl_nvm_section *nvm_sections);
व्योम iwl_nvm_fixups(u32 hw_id, अचिन्हित पूर्णांक section, u8 *data,
		    अचिन्हित पूर्णांक len);

/**
 * iwl_get_nvm - retrieve NVM data from firmware
 *
 * Allocates a new iwl_nvm_data काष्ठाure, fills it with
 * NVM data, and वापसs it to caller.
 */
काष्ठा iwl_nvm_data *iwl_get_nvm(काष्ठा iwl_trans *trans,
				 स्थिर काष्ठा iwl_fw *fw);

#पूर्ण_अगर /* __iwl_nvm_parse_h__ */
