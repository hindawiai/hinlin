<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_DP_MST_H__
#घोषणा __INTEL_DP_MST_H__

#समावेश <linux/types.h>

काष्ठा पूर्णांकel_digital_port;
काष्ठा पूर्णांकel_crtc_state;

पूर्णांक पूर्णांकel_dp_mst_encoder_init(काष्ठा पूर्णांकel_digital_port *dig_port, पूर्णांक conn_id);
व्योम पूर्णांकel_dp_mst_encoder_cleanup(काष्ठा पूर्णांकel_digital_port *dig_port);
पूर्णांक पूर्णांकel_dp_mst_encoder_active_links(काष्ठा पूर्णांकel_digital_port *dig_port);
bool पूर्णांकel_dp_mst_is_master_trans(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
bool पूर्णांकel_dp_mst_is_slave_trans(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

#पूर्ण_अगर /* __INTEL_DP_MST_H__ */
