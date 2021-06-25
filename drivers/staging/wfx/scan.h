<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Scan related functions.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#अगर_अघोषित WFX_SCAN_H
#घोषणा WFX_SCAN_H

#समावेश <net/mac80211.h>

काष्ठा wfx_dev;
काष्ठा wfx_vअगर;

व्योम wfx_hw_scan_work(काष्ठा work_काष्ठा *work);
पूर्णांक wfx_hw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		काष्ठा ieee80211_scan_request *req);
व्योम wfx_cancel_hw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
व्योम wfx_scan_complete(काष्ठा wfx_vअगर *wvअगर);

#पूर्ण_अगर /* WFX_SCAN_H */
