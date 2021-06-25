<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित _WG_RATELIMITER_H
#घोषणा _WG_RATELIMITER_H

#समावेश <linux/skbuff.h>

पूर्णांक wg_ratelimiter_init(व्योम);
व्योम wg_ratelimiter_uninit(व्योम);
bool wg_ratelimiter_allow(काष्ठा sk_buff *skb, काष्ठा net *net);

#अगर_घोषित DEBUG
bool wg_ratelimiter_selftest(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर /* _WG_RATELIMITER_H */
