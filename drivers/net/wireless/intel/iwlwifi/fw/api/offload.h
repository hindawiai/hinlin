<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_offload_h__
#घोषणा __iwl_fw_api_offload_h__

/**
 * क्रमागत iwl_prot_offload_subcmd_ids - protocol offload commands
 */
क्रमागत iwl_prot_offload_subcmd_ids अणु
	/**
	 * @STORED_BEACON_NTF: &काष्ठा iwl_stored_beacon_notअगर
	 */
	STORED_BEACON_NTF = 0xFF,
पूर्ण;

#घोषणा MAX_STORED_BEACON_SIZE 600

/**
 * काष्ठा iwl_stored_beacon_notअगर - Stored beacon notअगरication
 *
 * @प्रणाली_समय: प्रणाली समय on air rise
 * @tsf: TSF on air rise
 * @beacon_बारtamp: beacon on air rise
 * @band: band, matches &RX_RES_PHY_FLAGS_BAND_24 definition
 * @channel: channel this beacon was received on
 * @rates: rate in ucode पूर्णांकernal क्रमmat
 * @byte_count: frame's byte count
 * @data: beacon data, length in @byte_count
 */
काष्ठा iwl_stored_beacon_notअगर अणु
	__le32 प्रणाली_समय;
	__le64 tsf;
	__le32 beacon_बारtamp;
	__le16 band;
	__le16 channel;
	__le32 rates;
	__le32 byte_count;
	u8 data[MAX_STORED_BEACON_SIZE];
पूर्ण __packed; /* WOWLAN_STROED_BEACON_INFO_S_VER_2 */

#पूर्ण_अगर /* __iwl_fw_api_offload_h__ */
