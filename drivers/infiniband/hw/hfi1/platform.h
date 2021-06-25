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
#अगर_अघोषित __PLATFORM_H
#घोषणा __PLATFORM_H

#घोषणा METADATA_TABLE_FIELD_START_SHIFT		0
#घोषणा METADATA_TABLE_FIELD_START_LEN_BITS		15
#घोषणा METADATA_TABLE_FIELD_LEN_SHIFT			16
#घोषणा METADATA_TABLE_FIELD_LEN_LEN_BITS		16

/* Header काष्ठाure */
#घोषणा PLATFORM_CONFIG_HEADER_RECORD_IDX_SHIFT			0
#घोषणा PLATFORM_CONFIG_HEADER_RECORD_IDX_LEN_BITS		6
#घोषणा PLATFORM_CONFIG_HEADER_TABLE_LENGTH_SHIFT		16
#घोषणा PLATFORM_CONFIG_HEADER_TABLE_LENGTH_LEN_BITS		12
#घोषणा PLATFORM_CONFIG_HEADER_TABLE_TYPE_SHIFT			28
#घोषणा PLATFORM_CONFIG_HEADER_TABLE_TYPE_LEN_BITS		4

क्रमागत platक्रमm_config_table_type_encoding अणु
	PLATFORM_CONFIG_TABLE_RESERVED,
	PLATFORM_CONFIG_SYSTEM_TABLE,
	PLATFORM_CONFIG_PORT_TABLE,
	PLATFORM_CONFIG_RX_PRESET_TABLE,
	PLATFORM_CONFIG_TX_PRESET_TABLE,
	PLATFORM_CONFIG_QSFP_ATTEN_TABLE,
	PLATFORM_CONFIG_VARIABLE_SETTINGS_TABLE,
	PLATFORM_CONFIG_TABLE_MAX
पूर्ण;

क्रमागत platक्रमm_config_प्रणाली_table_fields अणु
	SYSTEM_TABLE_RESERVED,
	SYSTEM_TABLE_NODE_STRING,
	SYSTEM_TABLE_SYSTEM_IMAGE_GUID,
	SYSTEM_TABLE_NODE_GUID,
	SYSTEM_TABLE_REVISION,
	SYSTEM_TABLE_VENDOR_OUI,
	SYSTEM_TABLE_META_VERSION,
	SYSTEM_TABLE_DEVICE_ID,
	SYSTEM_TABLE_PARTITION_ENFORCEMENT_CAP,
	SYSTEM_TABLE_QSFP_POWER_CLASS_MAX,
	SYSTEM_TABLE_QSFP_ATTENUATION_DEFAULT_12G,
	SYSTEM_TABLE_QSFP_ATTENUATION_DEFAULT_25G,
	SYSTEM_TABLE_VARIABLE_TABLE_ENTRIES_PER_PORT,
	SYSTEM_TABLE_MAX
पूर्ण;

क्रमागत platक्रमm_config_port_table_fields अणु
	PORT_TABLE_RESERVED,
	PORT_TABLE_PORT_TYPE,
	PORT_TABLE_LOCAL_ATTEN_12G,
	PORT_TABLE_LOCAL_ATTEN_25G,
	PORT_TABLE_LINK_SPEED_SUPPORTED,
	PORT_TABLE_LINK_WIDTH_SUPPORTED,
	PORT_TABLE_AUTO_LANE_SHEDDING_ENABLED,
	PORT_TABLE_EXTERNAL_LOOPBACK_ALLOWED,
	PORT_TABLE_VL_CAP,
	PORT_TABLE_MTU_CAP,
	PORT_TABLE_TX_LANE_ENABLE_MASK,
	PORT_TABLE_LOCAL_MAX_TIMEOUT,
	PORT_TABLE_REMOTE_ATTEN_12G,
	PORT_TABLE_REMOTE_ATTEN_25G,
	PORT_TABLE_TX_PRESET_IDX_ACTIVE_NO_EQ,
	PORT_TABLE_TX_PRESET_IDX_ACTIVE_EQ,
	PORT_TABLE_RX_PRESET_IDX,
	PORT_TABLE_CABLE_REACH_CLASS,
	PORT_TABLE_MAX
पूर्ण;

क्रमागत platक्रमm_config_rx_preset_table_fields अणु
	RX_PRESET_TABLE_RESERVED,
	RX_PRESET_TABLE_QSFP_RX_CDR_APPLY,
	RX_PRESET_TABLE_QSFP_RX_EMP_APPLY,
	RX_PRESET_TABLE_QSFP_RX_AMP_APPLY,
	RX_PRESET_TABLE_QSFP_RX_CDR,
	RX_PRESET_TABLE_QSFP_RX_EMP,
	RX_PRESET_TABLE_QSFP_RX_AMP,
	RX_PRESET_TABLE_MAX
पूर्ण;

क्रमागत platक्रमm_config_tx_preset_table_fields अणु
	TX_PRESET_TABLE_RESERVED,
	TX_PRESET_TABLE_PRECUR,
	TX_PRESET_TABLE_ATTN,
	TX_PRESET_TABLE_POSTCUR,
	TX_PRESET_TABLE_QSFP_TX_CDR_APPLY,
	TX_PRESET_TABLE_QSFP_TX_EQ_APPLY,
	TX_PRESET_TABLE_QSFP_TX_CDR,
	TX_PRESET_TABLE_QSFP_TX_EQ,
	TX_PRESET_TABLE_MAX
पूर्ण;

क्रमागत platक्रमm_config_qsfp_attn_table_fields अणु
	QSFP_ATTEN_TABLE_RESERVED,
	QSFP_ATTEN_TABLE_TX_PRESET_IDX,
	QSFP_ATTEN_TABLE_RX_PRESET_IDX,
	QSFP_ATTEN_TABLE_MAX
पूर्ण;

क्रमागत platक्रमm_config_variable_settings_table_fields अणु
	VARIABLE_SETTINGS_TABLE_RESERVED,
	VARIABLE_SETTINGS_TABLE_TX_PRESET_IDX,
	VARIABLE_SETTINGS_TABLE_RX_PRESET_IDX,
	VARIABLE_SETTINGS_TABLE_MAX
पूर्ण;

काष्ठा platक्रमm_config अणु
	माप_प्रकार size;
	स्थिर u8 *data;
पूर्ण;

काष्ठा platक्रमm_config_data अणु
	u32 *table;
	u32 *table_metadata;
	u32 num_table;
पूर्ण;

/*
 * This काष्ठा acts as a quick reference पूर्णांकo the platक्रमm_data binary image
 * and is populated by parse_platक्रमm_config(...) depending on the specअगरic
 * META_VERSION
 */
काष्ठा platक्रमm_config_cache अणु
	u8  cache_valid;
	काष्ठा platक्रमm_config_data config_tables[PLATFORM_CONFIG_TABLE_MAX];
पूर्ण;

/* This section defines शेष values and encodings क्रम the
 * fields defined क्रम each table above
 */

/*
 * =====================================================
 *  System table encodings
 * =====================================================
 */
#घोषणा PLATFORM_CONFIG_MAGIC_NUM		0x3d4f5041
#घोषणा PLATFORM_CONFIG_MAGIC_NUMBER_LEN	4

/*
 * These घातer classes are the same as defined in SFF 8636 spec rev 2.4
 * describing byte 129 in table 6-16, except क्रमागतerated in a dअगरferent order
 */
क्रमागत platक्रमm_config_qsfp_घातer_class_encoding अणु
	QSFP_POWER_CLASS_1 = 1,
	QSFP_POWER_CLASS_2,
	QSFP_POWER_CLASS_3,
	QSFP_POWER_CLASS_4,
	QSFP_POWER_CLASS_5,
	QSFP_POWER_CLASS_6,
	QSFP_POWER_CLASS_7
पूर्ण;

/*
 * ====================================================
 *  Port table encodings
 * ====================================================
 */
क्रमागत platक्रमm_config_port_type_encoding अणु
	PORT_TYPE_UNKNOWN,
	PORT_TYPE_DISCONNECTED,
	PORT_TYPE_FIXED,
	PORT_TYPE_VARIABLE,
	PORT_TYPE_QSFP,
	PORT_TYPE_MAX
पूर्ण;

क्रमागत platक्रमm_config_link_speed_supported_encoding अणु
	LINK_SPEED_SUPP_12G = 1,
	LINK_SPEED_SUPP_25G,
	LINK_SPEED_SUPP_12G_25G,
	LINK_SPEED_SUPP_MAX
पूर्ण;

/*
 * This is a subset (not strict) of the link करोwngrades
 * supported. The link करोwngrades supported are expected
 * to be supplied to the driver by another entity such as
 * the fabric manager
 */
क्रमागत platक्रमm_config_link_width_supported_encoding अणु
	LINK_WIDTH_SUPP_1X = 1,
	LINK_WIDTH_SUPP_2X,
	LINK_WIDTH_SUPP_2X_1X,
	LINK_WIDTH_SUPP_3X,
	LINK_WIDTH_SUPP_3X_1X,
	LINK_WIDTH_SUPP_3X_2X,
	LINK_WIDTH_SUPP_3X_2X_1X,
	LINK_WIDTH_SUPP_4X,
	LINK_WIDTH_SUPP_4X_1X,
	LINK_WIDTH_SUPP_4X_2X,
	LINK_WIDTH_SUPP_4X_2X_1X,
	LINK_WIDTH_SUPP_4X_3X,
	LINK_WIDTH_SUPP_4X_3X_1X,
	LINK_WIDTH_SUPP_4X_3X_2X,
	LINK_WIDTH_SUPP_4X_3X_2X_1X,
	LINK_WIDTH_SUPP_MAX
पूर्ण;

क्रमागत platक्रमm_config_भव_lane_capability_encoding अणु
	VL_CAP_VL0 = 1,
	VL_CAP_VL0_1,
	VL_CAP_VL0_2,
	VL_CAP_VL0_3,
	VL_CAP_VL0_4,
	VL_CAP_VL0_5,
	VL_CAP_VL0_6,
	VL_CAP_VL0_7,
	VL_CAP_VL0_8,
	VL_CAP_VL0_9,
	VL_CAP_VL0_10,
	VL_CAP_VL0_11,
	VL_CAP_VL0_12,
	VL_CAP_VL0_13,
	VL_CAP_VL0_14,
	VL_CAP_MAX
पूर्ण;

/* Max MTU */
क्रमागत platक्रमm_config_mtu_capability_encoding अणु
	MTU_CAP_256   = 1,
	MTU_CAP_512   = 2,
	MTU_CAP_1024  = 3,
	MTU_CAP_2048  = 4,
	MTU_CAP_4096  = 5,
	MTU_CAP_8192  = 6,
	MTU_CAP_10240 = 7
पूर्ण;

क्रमागत platक्रमm_config_local_max_समयout_encoding अणु
	LOCAL_MAX_TIMEOUT_10_MS = 1,
	LOCAL_MAX_TIMEOUT_100_MS,
	LOCAL_MAX_TIMEOUT_1_S,
	LOCAL_MAX_TIMEOUT_10_S,
	LOCAL_MAX_TIMEOUT_100_S,
	LOCAL_MAX_TIMEOUT_1000_S
पूर्ण;

क्रमागत link_tuning_encoding अणु
	OPA_PASSIVE_TUNING,
	OPA_ACTIVE_TUNING,
	OPA_UNKNOWN_TUNING
पूर्ण;

/*
 * Shअगरts and masks क्रम the link SI tuning values stuffed पूर्णांकo the ASIC scratch
 * रेजिस्टरs क्रम पूर्णांकegrated platक्रमms
 */
#घोषणा PORT0_PORT_TYPE_SHIFT		0
#घोषणा PORT0_LOCAL_ATTEN_SHIFT		4
#घोषणा PORT0_REMOTE_ATTEN_SHIFT	10
#घोषणा PORT0_DEFAULT_ATTEN_SHIFT	32

#घोषणा PORT1_PORT_TYPE_SHIFT		16
#घोषणा PORT1_LOCAL_ATTEN_SHIFT		20
#घोषणा PORT1_REMOTE_ATTEN_SHIFT	26
#घोषणा PORT1_DEFAULT_ATTEN_SHIFT	40

#घोषणा PORT0_PORT_TYPE_MASK		0xFUL
#घोषणा PORT0_LOCAL_ATTEN_MASK		0x3FUL
#घोषणा PORT0_REMOTE_ATTEN_MASK		0x3FUL
#घोषणा PORT0_DEFAULT_ATTEN_MASK	0xFFUL

#घोषणा PORT1_PORT_TYPE_MASK		0xFUL
#घोषणा PORT1_LOCAL_ATTEN_MASK		0x3FUL
#घोषणा PORT1_REMOTE_ATTEN_MASK		0x3FUL
#घोषणा PORT1_DEFAULT_ATTEN_MASK	0xFFUL

#घोषणा PORT0_PORT_TYPE_SMASK		(PORT0_PORT_TYPE_MASK << \
					 PORT0_PORT_TYPE_SHIFT)
#घोषणा PORT0_LOCAL_ATTEN_SMASK		(PORT0_LOCAL_ATTEN_MASK << \
					 PORT0_LOCAL_ATTEN_SHIFT)
#घोषणा PORT0_REMOTE_ATTEN_SMASK	(PORT0_REMOTE_ATTEN_MASK << \
					 PORT0_REMOTE_ATTEN_SHIFT)
#घोषणा PORT0_DEFAULT_ATTEN_SMASK	(PORT0_DEFAULT_ATTEN_MASK << \
					 PORT0_DEFAULT_ATTEN_SHIFT)

#घोषणा PORT1_PORT_TYPE_SMASK		(PORT1_PORT_TYPE_MASK << \
					 PORT1_PORT_TYPE_SHIFT)
#घोषणा PORT1_LOCAL_ATTEN_SMASK		(PORT1_LOCAL_ATTEN_MASK << \
					 PORT1_LOCAL_ATTEN_SHIFT)
#घोषणा PORT1_REMOTE_ATTEN_SMASK	(PORT1_REMOTE_ATTEN_MASK << \
					 PORT1_REMOTE_ATTEN_SHIFT)
#घोषणा PORT1_DEFAULT_ATTEN_SMASK	(PORT1_DEFAULT_ATTEN_MASK << \
					 PORT1_DEFAULT_ATTEN_SHIFT)

#घोषणा QSFP_MAX_POWER_SHIFT		0
#घोषणा TX_NO_EQ_SHIFT			4
#घोषणा TX_EQ_SHIFT			25
#घोषणा RX_SHIFT			46

#घोषणा QSFP_MAX_POWER_MASK		0xFUL
#घोषणा TX_NO_EQ_MASK			0x1FFFFFUL
#घोषणा TX_EQ_MASK			0x1FFFFFUL
#घोषणा RX_MASK				0xFFFFUL

#घोषणा QSFP_MAX_POWER_SMASK		(QSFP_MAX_POWER_MASK << \
					 QSFP_MAX_POWER_SHIFT)
#घोषणा TX_NO_EQ_SMASK			(TX_NO_EQ_MASK << TX_NO_EQ_SHIFT)
#घोषणा TX_EQ_SMASK			(TX_EQ_MASK << TX_EQ_SHIFT)
#घोषणा RX_SMASK			(RX_MASK << RX_SHIFT)

#घोषणा TX_PRECUR_SHIFT			0
#घोषणा TX_ATTN_SHIFT			4
#घोषणा QSFP_TX_CDR_APPLY_SHIFT		9
#घोषणा QSFP_TX_EQ_APPLY_SHIFT		10
#घोषणा QSFP_TX_CDR_SHIFT		11
#घोषणा QSFP_TX_EQ_SHIFT		12
#घोषणा TX_POSTCUR_SHIFT		16

#घोषणा TX_PRECUR_MASK			0xFUL
#घोषणा TX_ATTN_MASK			0x1FUL
#घोषणा QSFP_TX_CDR_APPLY_MASK		0x1UL
#घोषणा QSFP_TX_EQ_APPLY_MASK		0x1UL
#घोषणा QSFP_TX_CDR_MASK		0x1UL
#घोषणा QSFP_TX_EQ_MASK			0xFUL
#घोषणा TX_POSTCUR_MASK			0x1FUL

#घोषणा TX_PRECUR_SMASK			(TX_PRECUR_MASK << TX_PRECUR_SHIFT)
#घोषणा TX_ATTN_SMASK			(TX_ATTN_MASK << TX_ATTN_SHIFT)
#घोषणा QSFP_TX_CDR_APPLY_SMASK		(QSFP_TX_CDR_APPLY_MASK << \
					 QSFP_TX_CDR_APPLY_SHIFT)
#घोषणा QSFP_TX_EQ_APPLY_SMASK		(QSFP_TX_EQ_APPLY_MASK << \
					 QSFP_TX_EQ_APPLY_SHIFT)
#घोषणा QSFP_TX_CDR_SMASK		(QSFP_TX_CDR_MASK << QSFP_TX_CDR_SHIFT)
#घोषणा QSFP_TX_EQ_SMASK		(QSFP_TX_EQ_MASK << QSFP_TX_EQ_SHIFT)
#घोषणा TX_POSTCUR_SMASK		(TX_POSTCUR_MASK << TX_POSTCUR_SHIFT)

#घोषणा QSFP_RX_CDR_APPLY_SHIFT		0
#घोषणा QSFP_RX_EMP_APPLY_SHIFT		1
#घोषणा QSFP_RX_AMP_APPLY_SHIFT		2
#घोषणा QSFP_RX_CDR_SHIFT		3
#घोषणा QSFP_RX_EMP_SHIFT		4
#घोषणा QSFP_RX_AMP_SHIFT		8

#घोषणा QSFP_RX_CDR_APPLY_MASK		0x1UL
#घोषणा QSFP_RX_EMP_APPLY_MASK		0x1UL
#घोषणा QSFP_RX_AMP_APPLY_MASK		0x1UL
#घोषणा QSFP_RX_CDR_MASK		0x1UL
#घोषणा QSFP_RX_EMP_MASK		0xFUL
#घोषणा QSFP_RX_AMP_MASK		0x3UL

#घोषणा QSFP_RX_CDR_APPLY_SMASK		(QSFP_RX_CDR_APPLY_MASK << \
					 QSFP_RX_CDR_APPLY_SHIFT)
#घोषणा QSFP_RX_EMP_APPLY_SMASK		(QSFP_RX_EMP_APPLY_MASK << \
					 QSFP_RX_EMP_APPLY_SHIFT)
#घोषणा QSFP_RX_AMP_APPLY_SMASK		(QSFP_RX_AMP_APPLY_MASK << \
					 QSFP_RX_AMP_APPLY_SHIFT)
#घोषणा QSFP_RX_CDR_SMASK		(QSFP_RX_CDR_MASK << QSFP_RX_CDR_SHIFT)
#घोषणा QSFP_RX_EMP_SMASK		(QSFP_RX_EMP_MASK << QSFP_RX_EMP_SHIFT)
#घोषणा QSFP_RX_AMP_SMASK		(QSFP_RX_AMP_MASK << QSFP_RX_AMP_SHIFT)

#घोषणा BITMAP_VERSION			1
#घोषणा BITMAP_VERSION_SHIFT		44
#घोषणा BITMAP_VERSION_MASK		0xFUL
#घोषणा BITMAP_VERSION_SMASK		(BITMAP_VERSION_MASK << \
					 BITMAP_VERSION_SHIFT)
#घोषणा CHECKSUM_SHIFT			48
#घोषणा CHECKSUM_MASK			0xFFFFUL
#घोषणा CHECKSUM_SMASK			(CHECKSUM_MASK << CHECKSUM_SHIFT)

/* platक्रमm.c */
व्योम get_platक्रमm_config(काष्ठा hfi1_devdata *dd);
व्योम मुक्त_platक्रमm_config(काष्ठा hfi1_devdata *dd);
व्योम get_port_type(काष्ठा hfi1_pportdata *ppd);
पूर्णांक set_qsfp_tx(काष्ठा hfi1_pportdata *ppd, पूर्णांक on);
व्योम tune_serdes(काष्ठा hfi1_pportdata *ppd);

#पूर्ण_अगर			/*__PLATFORM_H*/
