<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 */

#समावेश "mt7601u.h"

व्योम mt76_हटाओ_hdr_pad(काष्ठा sk_buff *skb)
अणु
	पूर्णांक len = ieee80211_get_hdrlen_from_skb(skb);

	स_हटाओ(skb->data + 2, skb->data, len);
	skb_pull(skb, 2);
पूर्ण

पूर्णांक mt76_insert_hdr_pad(काष्ठा sk_buff *skb)
अणु
	पूर्णांक len = ieee80211_get_hdrlen_from_skb(skb);
	पूर्णांक ret;

	अगर (len % 4 == 0)
		वापस 0;

	ret = skb_cow(skb, 2);
	अगर (ret)
		वापस ret;

	skb_push(skb, 2);
	स_हटाओ(skb->data, skb->data + 2, len);

	skb->data[len] = 0;
	skb->data[len + 1] = 0;
	वापस 0;
पूर्ण
