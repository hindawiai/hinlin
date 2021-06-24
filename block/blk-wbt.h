<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित WB_THROTTLE_H
#घोषणा WB_THROTTLE_H

#समावेश <linux/kernel.h>
#समावेश <linux/atomic.h>
#समावेश <linux/रुको.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kसमय.स>

#समावेश "blk-stat.h"
#समावेश "blk-rq-qos.h"

क्रमागत wbt_flags अणु
	WBT_TRACKED		= 1,	/* ग_लिखो, tracked क्रम throttling */
	WBT_READ		= 2,	/* पढ़ो */
	WBT_KSWAPD		= 4,	/* ग_लिखो, from kswapd */
	WBT_DISCARD		= 8,	/* discard */

	WBT_NR_BITS		= 4,	/* number of bits */
पूर्ण;

क्रमागत अणु
	WBT_RWQ_BG		= 0,
	WBT_RWQ_KSWAPD,
	WBT_RWQ_DISCARD,
	WBT_NUM_RWQ,
पूर्ण;

/*
 * Enable states. Either off, or on by शेष (करोne at init समय),
 * or on through manual setup in sysfs.
 */
क्रमागत अणु
	WBT_STATE_ON_DEFAULT	= 1,
	WBT_STATE_ON_MANUAL	= 2,
पूर्ण;

काष्ठा rq_wb अणु
	/*
	 * Settings that govern how we throttle
	 */
	अचिन्हित पूर्णांक wb_background;		/* background ग_लिखोback */
	अचिन्हित पूर्णांक wb_normal;			/* normal ग_लिखोback */

	लघु enable_state;			/* WBT_STATE_* */

	/*
	 * Number of consecutive periods where we करोn't have enough
	 * inक्रमmation to make a firm scale up/करोwn decision.
	 */
	अचिन्हित पूर्णांक unknown_cnt;

	u64 win_nsec;				/* शेष winकरोw size */
	u64 cur_win_nsec;			/* current winकरोw size */

	काष्ठा blk_stat_callback *cb;

	u64 sync_issue;
	व्योम *sync_cookie;

	अचिन्हित पूर्णांक wc;

	अचिन्हित दीर्घ last_issue;		/* last non-throttled issue */
	अचिन्हित दीर्घ last_comp;		/* last non-throttled comp */
	अचिन्हित दीर्घ min_lat_nsec;
	काष्ठा rq_qos rqos;
	काष्ठा rq_रुको rq_रुको[WBT_NUM_RWQ];
	काष्ठा rq_depth rq_depth;
पूर्ण;

अटल अंतरभूत काष्ठा rq_wb *RQWB(काष्ठा rq_qos *rqos)
अणु
	वापस container_of(rqos, काष्ठा rq_wb, rqos);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक wbt_inflight(काष्ठा rq_wb *rwb)
अणु
	अचिन्हित पूर्णांक i, ret = 0;

	क्रम (i = 0; i < WBT_NUM_RWQ; i++)
		ret += atomic_पढ़ो(&rwb->rq_रुको[i].inflight);

	वापस ret;
पूर्ण


#अगर_घोषित CONFIG_BLK_WBT

पूर्णांक wbt_init(काष्ठा request_queue *);
व्योम wbt_disable_शेष(काष्ठा request_queue *);
व्योम wbt_enable_शेष(काष्ठा request_queue *);

u64 wbt_get_min_lat(काष्ठा request_queue *q);
व्योम wbt_set_min_lat(काष्ठा request_queue *q, u64 val);

व्योम wbt_set_ग_लिखो_cache(काष्ठा request_queue *, bool);

u64 wbt_शेष_latency_nsec(काष्ठा request_queue *);

#अन्यथा

अटल अंतरभूत व्योम wbt_track(काष्ठा request *rq, क्रमागत wbt_flags flags)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक wbt_init(काष्ठा request_queue *q)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम wbt_disable_शेष(काष्ठा request_queue *q)
अणु
पूर्ण
अटल अंतरभूत व्योम wbt_enable_शेष(काष्ठा request_queue *q)
अणु
पूर्ण
अटल अंतरभूत व्योम wbt_set_ग_लिखो_cache(काष्ठा request_queue *q, bool wc)
अणु
पूर्ण
अटल अंतरभूत u64 wbt_get_min_lat(काष्ठा request_queue *q)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम wbt_set_min_lat(काष्ठा request_queue *q, u64 val)
अणु
पूर्ण
अटल अंतरभूत u64 wbt_शेष_latency_nsec(काष्ठा request_queue *q)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_BLK_WBT */

#पूर्ण_अगर
