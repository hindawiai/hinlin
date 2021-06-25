<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _IAVF_PROTOTYPE_H_
#घोषणा _IAVF_PROTOTYPE_H_

#समावेश "iavf_type.h"
#समावेश "iavf_alloc.h"
#समावेश <linux/avf/virtchnl.h>

/* Prototypes क्रम shared code functions that are not in
 * the standard function poपूर्णांकer काष्ठाures.  These are
 * mostly because they are needed even beक्रमe the init
 * has happened and will assist in the early SW and FW
 * setup.
 */

/* adminq functions */
क्रमागत iavf_status iavf_init_adminq(काष्ठा iavf_hw *hw);
क्रमागत iavf_status iavf_shutकरोwn_adminq(काष्ठा iavf_hw *hw);
व्योम iavf_adminq_init_ring_data(काष्ठा iavf_hw *hw);
क्रमागत iavf_status iavf_clean_arq_element(काष्ठा iavf_hw *hw,
					काष्ठा iavf_arq_event_info *e,
					u16 *events_pending);
क्रमागत iavf_status iavf_asq_send_command(काष्ठा iavf_hw *hw,
				       काष्ठा iavf_aq_desc *desc,
				       व्योम *buff, /* can be शून्य */
				       u16 buff_size,
				       काष्ठा iavf_asq_cmd_details *cmd_details);
bool iavf_asq_करोne(काष्ठा iavf_hw *hw);

/* debug function क्रम adminq */
व्योम iavf_debug_aq(काष्ठा iavf_hw *hw, क्रमागत iavf_debug_mask mask,
		   व्योम *desc, व्योम *buffer, u16 buf_len);

व्योम iavf_idle_aq(काष्ठा iavf_hw *hw);
व्योम iavf_resume_aq(काष्ठा iavf_hw *hw);
bool iavf_check_asq_alive(काष्ठा iavf_hw *hw);
क्रमागत iavf_status iavf_aq_queue_shutकरोwn(काष्ठा iavf_hw *hw, bool unloading);
स्थिर अक्षर *iavf_aq_str(काष्ठा iavf_hw *hw, क्रमागत iavf_admin_queue_err aq_err);
स्थिर अक्षर *iavf_stat_str(काष्ठा iavf_hw *hw, क्रमागत iavf_status stat_err);

क्रमागत iavf_status iavf_aq_get_rss_lut(काष्ठा iavf_hw *hw, u16 seid,
				     bool pf_lut, u8 *lut, u16 lut_size);
क्रमागत iavf_status iavf_aq_set_rss_lut(काष्ठा iavf_hw *hw, u16 seid,
				     bool pf_lut, u8 *lut, u16 lut_size);
क्रमागत iavf_status iavf_aq_get_rss_key(काष्ठा iavf_hw *hw, u16 seid,
				     काष्ठा iavf_aqc_get_set_rss_key_data *key);
क्रमागत iavf_status iavf_aq_set_rss_key(काष्ठा iavf_hw *hw, u16 seid,
				     काष्ठा iavf_aqc_get_set_rss_key_data *key);

क्रमागत iavf_status iavf_set_mac_type(काष्ठा iavf_hw *hw);

बाह्य काष्ठा iavf_rx_ptype_decoded iavf_ptype_lookup[];

अटल अंतरभूत काष्ठा iavf_rx_ptype_decoded decode_rx_desc_ptype(u8 ptype)
अणु
	वापस iavf_ptype_lookup[ptype];
पूर्ण

व्योम iavf_vf_parse_hw_config(काष्ठा iavf_hw *hw,
			     काष्ठा virtchnl_vf_resource *msg);
क्रमागत iavf_status iavf_vf_reset(काष्ठा iavf_hw *hw);
क्रमागत iavf_status iavf_aq_send_msg_to_pf(काष्ठा iavf_hw *hw,
					क्रमागत virtchnl_ops v_opcode,
					क्रमागत iavf_status v_retval,
					u8 *msg, u16 msglen,
					काष्ठा iavf_asq_cmd_details *cmd_details);
#पूर्ण_अगर /* _IAVF_PROTOTYPE_H_ */
