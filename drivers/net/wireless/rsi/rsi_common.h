<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित __RSI_COMMON_H__
#घोषणा __RSI_COMMON_H__

#समावेश <linux/kthपढ़ो.h>

#घोषणा EVENT_WAIT_FOREVER              0
#घोषणा FIRMWARE_RSI9113                "rs9113_wlan_qspi.rps"
#घोषणा QUEUE_NOT_FULL                  1
#घोषणा QUEUE_FULL                      0

अटल अंतरभूत पूर्णांक rsi_init_event(काष्ठा rsi_event *pevent)
अणु
	atomic_set(&pevent->event_condition, 1);
	init_रुकोqueue_head(&pevent->event_queue);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rsi_रुको_event(काष्ठा rsi_event *event, u32 समयout)
अणु
	पूर्णांक status = 0;

	अगर (!समयout)
		status = रुको_event_पूर्णांकerruptible(event->event_queue,
				(atomic_पढ़ो(&event->event_condition) == 0));
	अन्यथा
		status = रुको_event_पूर्णांकerruptible_समयout(event->event_queue,
				(atomic_पढ़ो(&event->event_condition) == 0),
				समयout);
	वापस status;
पूर्ण

अटल अंतरभूत व्योम rsi_set_event(काष्ठा rsi_event *event)
अणु
	atomic_set(&event->event_condition, 0);
	wake_up_पूर्णांकerruptible(&event->event_queue);
पूर्ण

अटल अंतरभूत व्योम rsi_reset_event(काष्ठा rsi_event *event)
अणु
	atomic_set(&event->event_condition, 1);
पूर्ण

अटल अंतरभूत पूर्णांक rsi_create_kthपढ़ो(काष्ठा rsi_common *common,
				     काष्ठा rsi_thपढ़ो *thपढ़ो,
				     व्योम *func_ptr,
				     u8 *name)
अणु
	init_completion(&thपढ़ो->completion);
	atomic_set(&thपढ़ो->thपढ़ो_करोne, 0);
	thपढ़ो->task = kthपढ़ो_run(func_ptr, common, "%s", name);
	अगर (IS_ERR(thपढ़ो->task))
		वापस (पूर्णांक)PTR_ERR(thपढ़ो->task);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rsi_समाप्त_thपढ़ो(काष्ठा rsi_thपढ़ो *handle)
अणु
	atomic_inc(&handle->thपढ़ो_करोne);
	rsi_set_event(&handle->event);

	वापस kthपढ़ो_stop(handle->task);
पूर्ण

व्योम rsi_mac80211_detach(काष्ठा rsi_hw *hw);
u16 rsi_get_connected_channel(काष्ठा ieee80211_vअगर *vअगर);
काष्ठा rsi_hw *rsi_91x_init(u16 oper_mode);
व्योम rsi_91x_deinit(काष्ठा rsi_hw *adapter);
पूर्णांक rsi_पढ़ो_pkt(काष्ठा rsi_common *common, u8 *rx_pkt, s32 rcv_pkt_len);
#अगर_घोषित CONFIG_PM
पूर्णांक rsi_config_wowlan(काष्ठा rsi_hw *adapter, काष्ठा cfg80211_wowlan *wowlan);
#पूर्ण_अगर
काष्ठा rsi_sta *rsi_find_sta(काष्ठा rsi_common *common, u8 *mac_addr);
काष्ठा ieee80211_vअगर *rsi_get_vअगर(काष्ठा rsi_hw *adapter, u8 *mac);
व्योम rsi_roc_समयout(काष्ठा समयr_list *t);
#पूर्ण_अगर
