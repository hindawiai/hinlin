<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_binding_h__
#घोषणा __iwl_fw_api_binding_h__

#समावेश <fw/file.h>
#समावेश <fw/img.h>

#घोषणा MAX_MACS_IN_BINDING	(3)
#घोषणा MAX_BINDINGS		(4)

/**
 * काष्ठा iwl_binding_cmd_v1 - configuring bindings
 * ( BINDING_CONTEXT_CMD = 0x2b )
 * @id_and_color: ID and color of the relevant Binding,
 *	&क्रमागत iwl_ctxt_id_and_color
 * @action: action to perक्रमm, one of FW_CTXT_ACTION_*
 * @macs: array of MAC id and colors which beदीर्घ to the binding,
 *	&क्रमागत iwl_ctxt_id_and_color
 * @phy: PHY id and color which beदीर्घs to the binding,
 *	&क्रमागत iwl_ctxt_id_and_color
 */
काष्ठा iwl_binding_cmd_v1 अणु
	/* COMMON_INDEX_HDR_API_S_VER_1 */
	__le32 id_and_color;
	__le32 action;
	/* BINDING_DATA_API_S_VER_1 */
	__le32 macs[MAX_MACS_IN_BINDING];
	__le32 phy;
पूर्ण __packed; /* BINDING_CMD_API_S_VER_1 */

/**
 * काष्ठा iwl_binding_cmd - configuring bindings
 * ( BINDING_CONTEXT_CMD = 0x2b )
 * @id_and_color: ID and color of the relevant Binding,
 *	&क्रमागत iwl_ctxt_id_and_color
 * @action: action to perक्रमm, one of FW_CTXT_ACTION_*
 * @macs: array of MAC id and colors which beदीर्घ to the binding
 *	&क्रमागत iwl_ctxt_id_and_color
 * @phy: PHY id and color which beदीर्घs to the binding
 *	&क्रमागत iwl_ctxt_id_and_color
 * @lmac_id: the lmac id the binding beदीर्घs to
 */
काष्ठा iwl_binding_cmd अणु
	/* COMMON_INDEX_HDR_API_S_VER_1 */
	__le32 id_and_color;
	__le32 action;
	/* BINDING_DATA_API_S_VER_1 */
	__le32 macs[MAX_MACS_IN_BINDING];
	__le32 phy;
	__le32 lmac_id;
पूर्ण __packed; /* BINDING_CMD_API_S_VER_2 */

#घोषणा IWL_BINDING_CMD_SIZE_V1	माप(काष्ठा iwl_binding_cmd_v1)
#घोषणा IWL_LMAC_24G_INDEX		0
#घोषणा IWL_LMAC_5G_INDEX		1

अटल अंतरभूत u32 iwl_mvm_get_lmac_id(स्थिर काष्ठा iwl_fw *fw,
				      क्रमागत nl80211_band band)अणु
	अगर (!fw_has_capa(&fw->ucode_capa, IWL_UCODE_TLV_CAPA_CDB_SUPPORT) ||
	    band == NL80211_BAND_2GHZ)
		वापस IWL_LMAC_24G_INDEX;
	वापस IWL_LMAC_5G_INDEX;
पूर्ण

/* The maximal number of fragments in the FW's schedule session */
#घोषणा IWL_MVM_MAX_QUOTA 128

/**
 * काष्ठा iwl_समय_quota_data_v1 - configuration of समय quota per binding
 * @id_and_color: ID and color of the relevant Binding,
 *	&क्रमागत iwl_ctxt_id_and_color
 * @quota: असलolute समय quota in TU. The scheduler will try to भागide the
 *	reमुख्यig quota (after Time Events) according to this quota.
 * @max_duration: max unपूर्णांकerrupted context duration in TU
 */
काष्ठा iwl_समय_quota_data_v1 अणु
	__le32 id_and_color;
	__le32 quota;
	__le32 max_duration;
पूर्ण __packed; /* TIME_QUOTA_DATA_API_S_VER_1 */

/**
 * काष्ठा iwl_समय_quota_cmd - configuration of समय quota between bindings
 * ( TIME_QUOTA_CMD = 0x2c )
 * @quotas: allocations per binding
 * Note: on non-CDB the fourth one is the auxilary mac and is
 *	essentially zero.
 *	On CDB the fourth one is a regular binding.
 */
काष्ठा iwl_समय_quota_cmd_v1 अणु
	काष्ठा iwl_समय_quota_data_v1 quotas[MAX_BINDINGS];
पूर्ण __packed; /* TIME_QUOTA_ALLOCATION_CMD_API_S_VER_1 */

क्रमागत iwl_quota_low_latency अणु
	IWL_QUOTA_LOW_LATENCY_NONE = 0,
	IWL_QUOTA_LOW_LATENCY_TX = BIT(0),
	IWL_QUOTA_LOW_LATENCY_RX = BIT(1),
	IWL_QUOTA_LOW_LATENCY_TX_RX =
		IWL_QUOTA_LOW_LATENCY_TX | IWL_QUOTA_LOW_LATENCY_RX,
पूर्ण;

/**
 * काष्ठा iwl_समय_quota_data - configuration of समय quota per binding
 * @id_and_color: ID and color of the relevant Binding.
 * @quota: असलolute समय quota in TU. The scheduler will try to भागide the
 *	reमुख्यig quota (after Time Events) according to this quota.
 * @max_duration: max unपूर्णांकerrupted context duration in TU
 * @low_latency: low latency status, &क्रमागत iwl_quota_low_latency
 */
काष्ठा iwl_समय_quota_data अणु
	__le32 id_and_color;
	__le32 quota;
	__le32 max_duration;
	__le32 low_latency;
पूर्ण __packed; /* TIME_QUOTA_DATA_API_S_VER_2 */

/**
 * काष्ठा iwl_समय_quota_cmd - configuration of समय quota between bindings
 * ( TIME_QUOTA_CMD = 0x2c )
 * Note: on non-CDB the fourth one is the auxilary mac and is essentially zero.
 * On CDB the fourth one is a regular binding.
 *
 * @quotas: allocations per binding
 */
काष्ठा iwl_समय_quota_cmd अणु
	काष्ठा iwl_समय_quota_data quotas[MAX_BINDINGS];
पूर्ण __packed; /* TIME_QUOTA_ALLOCATION_CMD_API_S_VER_2 */

#पूर्ण_अगर /* __iwl_fw_api_binding_h__ */
