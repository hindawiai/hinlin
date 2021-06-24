<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DP_CTRL_H_
#घोषणा _DP_CTRL_H_

#समावेश "dp_aux.h"
#समावेश "dp_panel.h"
#समावेश "dp_link.h"
#समावेश "dp_parser.h"
#समावेश "dp_power.h"
#समावेश "dp_catalog.h"

काष्ठा dp_ctrl अणु
	bool orientation;
	atomic_t पातed;
	u32 pixel_rate;
पूर्ण;

पूर्णांक dp_ctrl_host_init(काष्ठा dp_ctrl *dp_ctrl, bool flip, bool reset);
व्योम dp_ctrl_host_deinit(काष्ठा dp_ctrl *dp_ctrl);
पूर्णांक dp_ctrl_on_link(काष्ठा dp_ctrl *dp_ctrl);
पूर्णांक dp_ctrl_on_stream(काष्ठा dp_ctrl *dp_ctrl);
पूर्णांक dp_ctrl_off(काष्ठा dp_ctrl *dp_ctrl);
व्योम dp_ctrl_push_idle(काष्ठा dp_ctrl *dp_ctrl);
व्योम dp_ctrl_isr(काष्ठा dp_ctrl *dp_ctrl);
व्योम dp_ctrl_handle_sink_request(काष्ठा dp_ctrl *dp_ctrl);
काष्ठा dp_ctrl *dp_ctrl_get(काष्ठा device *dev, काष्ठा dp_link *link,
			काष्ठा dp_panel *panel,	काष्ठा drm_dp_aux *aux,
			काष्ठा dp_घातer *घातer, काष्ठा dp_catalog *catalog,
			काष्ठा dp_parser *parser);
व्योम dp_ctrl_put(काष्ठा dp_ctrl *dp_ctrl);

#पूर्ण_अगर /* _DP_CTRL_H_ */
