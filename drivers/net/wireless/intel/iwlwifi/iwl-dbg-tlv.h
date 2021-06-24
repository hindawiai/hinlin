<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2018-2020 Intel Corporation
 */
#अगर_अघोषित __iwl_dbg_tlv_h__
#घोषणा __iwl_dbg_tlv_h__

#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <fw/file.h>
#समावेश <fw/api/dbg-tlv.h>

/**
 * काष्ठा iwl_dbg_tlv_node - debug TLV node
 * @list: list of &काष्ठा iwl_dbg_tlv_node
 * @tlv: debug TLV
 */
काष्ठा iwl_dbg_tlv_node अणु
	काष्ठा list_head list;
	काष्ठा iwl_ucode_tlv tlv;
पूर्ण;

/**
 * जोड़ iwl_dbg_tlv_tp_data - data that is given in a समय poपूर्णांक
 * @fw_pkt: a packet received from the FW
 */
जोड़ iwl_dbg_tlv_tp_data अणु
	काष्ठा iwl_rx_packet *fw_pkt;
पूर्ण;

/**
 * काष्ठा iwl_dbg_tlv_समय_poपूर्णांक_data
 * @trig_list: list of triggers
 * @active_trig_list: list of active triggers
 * @hcmd_list: list of host commands
 */
काष्ठा iwl_dbg_tlv_समय_poपूर्णांक_data अणु
	काष्ठा list_head trig_list;
	काष्ठा list_head active_trig_list;
	काष्ठा list_head hcmd_list;
पूर्ण;

काष्ठा iwl_trans;
काष्ठा iwl_fw_runसमय;

व्योम iwl_dbg_tlv_load_bin(काष्ठा device *dev, काष्ठा iwl_trans *trans);
व्योम iwl_dbg_tlv_मुक्त(काष्ठा iwl_trans *trans);
व्योम iwl_dbg_tlv_alloc(काष्ठा iwl_trans *trans, स्थिर काष्ठा iwl_ucode_tlv *tlv,
		       bool ext);
व्योम iwl_dbg_tlv_init(काष्ठा iwl_trans *trans);
व्योम iwl_dbg_tlv_समय_poपूर्णांक(काष्ठा iwl_fw_runसमय *fwrt,
			    क्रमागत iwl_fw_ini_समय_poपूर्णांक tp_id,
			    जोड़ iwl_dbg_tlv_tp_data *tp_data);
व्योम iwl_dbg_tlv_del_समयrs(काष्ठा iwl_trans *trans);

#पूर्ण_अगर /* __iwl_dbg_tlv_h__*/
