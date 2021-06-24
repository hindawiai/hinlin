<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __PS_H__
#घोषणा __PS_H__

#समावेश "wlcore.h"
#समावेश "acx.h"

पूर्णांक wl1271_ps_set_mode(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		       क्रमागत wl1271_cmd_ps_mode mode);
व्योम wl12xx_ps_link_start(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			  u8 hlid, bool clean_queues);
व्योम wl12xx_ps_link_end(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 hlid);

#घोषणा WL1271_PS_COMPLETE_TIMEOUT 500

#पूर्ण_अगर /* __WL1271_PS_H__ */
