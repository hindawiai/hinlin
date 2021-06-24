<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Common निजी data क्रम Silicon Lअसल WFx chips.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 * Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 */
#अगर_अघोषित WFX_H
#घोषणा WFX_H

#समावेश <linux/completion.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/nospec.h>
#समावेश <net/mac80211.h>

#समावेश "bh.h"
#समावेश "data_tx.h"
#समावेश "main.h"
#समावेश "queue.h"
#समावेश "hif_tx.h"

#घोषणा USEC_PER_TXOP 32 // see काष्ठा ieee80211_tx_queue_params
#घोषणा USEC_PER_TU 1024

काष्ठा hwbus_ops;

काष्ठा wfx_dev अणु
	काष्ठा wfx_platक्रमm_data pdata;
	काष्ठा device		*dev;
	काष्ठा ieee80211_hw	*hw;
	काष्ठा ieee80211_vअगर	*vअगर[2];
	काष्ठा mac_address	addresses[2];
	स्थिर काष्ठा hwbus_ops	*hwbus_ops;
	व्योम			*hwbus_priv;

	u8			keyset;
	काष्ठा completion	firmware_पढ़ोy;
	काष्ठा hअगर_ind_startup	hw_caps;
	काष्ठा wfx_hअगर		hअगर;
	काष्ठा delayed_work	cooling_समयout_work;
	bool			poll_irq;
	bool			chip_frozen;
	काष्ठा mutex		conf_mutex;

	काष्ठा wfx_hअगर_cmd	hअगर_cmd;
	काष्ठा sk_buff_head	tx_pending;
	रुको_queue_head_t	tx_dequeue;
	atomic_t		tx_lock;

	atomic_t		packet_id;
	u32			key_map;

	काष्ठा hअगर_rx_stats	rx_stats;
	काष्ठा mutex		rx_stats_lock;
	काष्ठा hअगर_tx_घातer_loop_info tx_घातer_loop_info;
	काष्ठा mutex		tx_घातer_loop_info_lock;
	पूर्णांक			क्रमce_ps_समयout;
पूर्ण;

काष्ठा wfx_vअगर अणु
	काष्ठा wfx_dev		*wdev;
	काष्ठा ieee80211_vअगर	*vअगर;
	काष्ठा ieee80211_channel *channel;
	पूर्णांक			id;

	u32			link_id_map;

	bool			after_dtim_tx_allowed;
	bool			join_in_progress;

	काष्ठा delayed_work	beacon_loss_work;

	काष्ठा wfx_queue	tx_queue[4];
	काष्ठा tx_policy_cache	tx_policy_cache;
	काष्ठा work_काष्ठा	tx_policy_upload_work;

	काष्ठा work_काष्ठा	update_tim_work;

	अचिन्हित दीर्घ		uapsd_mask;

	/* aव्योम some operations in parallel with scan */
	काष्ठा mutex		scan_lock;
	काष्ठा work_काष्ठा	scan_work;
	काष्ठा completion	scan_complete;
	bool			scan_पात;
	काष्ठा ieee80211_scan_request *scan_req;

	काष्ठा completion	set_pm_mode_complete;
पूर्ण;

अटल अंतरभूत काष्ठा wfx_vअगर *wdev_to_wvअगर(काष्ठा wfx_dev *wdev, पूर्णांक vअगर_id)
अणु
	अगर (vअगर_id >= ARRAY_SIZE(wdev->vअगर)) अणु
		dev_dbg(wdev->dev, "requesting non-existent vif: %d\n", vअगर_id);
		वापस शून्य;
	पूर्ण
	vअगर_id = array_index_nospec(vअगर_id, ARRAY_SIZE(wdev->vअगर));
	अगर (!wdev->vअगर[vअगर_id]) अणु
		dev_dbg(wdev->dev, "requesting non-allocated vif: %d\n",
			vअगर_id);
		वापस शून्य;
	पूर्ण
	वापस (काष्ठा wfx_vअगर *) wdev->vअगर[vअगर_id]->drv_priv;
पूर्ण

अटल अंतरभूत काष्ठा wfx_vअगर *wvअगर_iterate(काष्ठा wfx_dev *wdev,
					   काष्ठा wfx_vअगर *cur)
अणु
	पूर्णांक i;
	पूर्णांक mark = 0;
	काष्ठा wfx_vअगर *पंचांगp;

	अगर (!cur)
		mark = 1;
	क्रम (i = 0; i < ARRAY_SIZE(wdev->vअगर); i++) अणु
		पंचांगp = wdev_to_wvअगर(wdev, i);
		अगर (mark && पंचांगp)
			वापस पंचांगp;
		अगर (पंचांगp == cur)
			mark = 1;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक wvअगर_count(काष्ठा wfx_dev *wdev)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा wfx_vअगर *wvअगर;

	क्रम (i = 0; i < ARRAY_SIZE(wdev->vअगर); i++) अणु
		wvअगर = wdev_to_wvअगर(wdev, i);
		अगर (wvअगर)
			ret++;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम memreverse(u8 *src, u8 length)
अणु
	u8 *lo = src;
	u8 *hi = src + length - 1;
	u8 swap;

	जबतक (lo < hi) अणु
		swap = *lo;
		*lo++ = *hi;
		*hi-- = swap;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक memzcmp(व्योम *src, अचिन्हित पूर्णांक size)
अणु
	u8 *buf = src;

	अगर (!size)
		वापस 0;
	अगर (*buf)
		वापस 1;
	वापस स_भेद(buf, buf + 1, size - 1);
पूर्ण

#पूर्ण_अगर /* WFX_H */
