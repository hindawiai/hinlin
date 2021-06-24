<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_TC_H__
#घोषणा __INTEL_TC_H__

#समावेश <linux/mutex.h>
#समावेश <linux/types.h>

काष्ठा पूर्णांकel_digital_port;
काष्ठा पूर्णांकel_encoder;

bool पूर्णांकel_tc_port_connected(काष्ठा पूर्णांकel_encoder *encoder);
u32 पूर्णांकel_tc_port_get_lane_mask(काष्ठा पूर्णांकel_digital_port *dig_port);
u32 पूर्णांकel_tc_port_get_pin_assignment_mask(काष्ठा पूर्णांकel_digital_port *dig_port);
पूर्णांक पूर्णांकel_tc_port_fia_max_lane_count(काष्ठा पूर्णांकel_digital_port *dig_port);
व्योम पूर्णांकel_tc_port_set_fia_lane_count(काष्ठा पूर्णांकel_digital_port *dig_port,
				      पूर्णांक required_lanes);

व्योम पूर्णांकel_tc_port_sanitize(काष्ठा पूर्णांकel_digital_port *dig_port);
व्योम पूर्णांकel_tc_port_lock(काष्ठा पूर्णांकel_digital_port *dig_port);
व्योम पूर्णांकel_tc_port_unlock(काष्ठा पूर्णांकel_digital_port *dig_port);
व्योम पूर्णांकel_tc_port_get_link(काष्ठा पूर्णांकel_digital_port *dig_port,
			    पूर्णांक required_lanes);
व्योम पूर्णांकel_tc_port_put_link(काष्ठा पूर्णांकel_digital_port *dig_port);
bool पूर्णांकel_tc_port_ref_held(काष्ठा पूर्णांकel_digital_port *dig_port);

व्योम पूर्णांकel_tc_port_init(काष्ठा पूर्णांकel_digital_port *dig_port, bool is_legacy);

#पूर्ण_अगर /* __INTEL_TC_H__ */
