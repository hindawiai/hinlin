<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित INT_BLK_MQ_TAG_H
#घोषणा INT_BLK_MQ_TAG_H

/*
 * Tag address space map.
 */
काष्ठा blk_mq_tags अणु
	अचिन्हित पूर्णांक nr_tags;
	अचिन्हित पूर्णांक nr_reserved_tags;

	atomic_t active_queues;

	काष्ठा sbiपंचांगap_queue *biपंचांगap_tags;
	काष्ठा sbiपंचांगap_queue *breserved_tags;

	काष्ठा sbiपंचांगap_queue __biपंचांगap_tags;
	काष्ठा sbiपंचांगap_queue __breserved_tags;

	काष्ठा request **rqs;
	काष्ठा request **अटल_rqs;
	काष्ठा list_head page_list;
पूर्ण;

बाह्य काष्ठा blk_mq_tags *blk_mq_init_tags(अचिन्हित पूर्णांक nr_tags,
					अचिन्हित पूर्णांक reserved_tags,
					पूर्णांक node, अचिन्हित पूर्णांक flags);
बाह्य व्योम blk_mq_मुक्त_tags(काष्ठा blk_mq_tags *tags, अचिन्हित पूर्णांक flags);

बाह्य पूर्णांक blk_mq_init_shared_sbiपंचांगap(काष्ठा blk_mq_tag_set *set,
				      अचिन्हित पूर्णांक flags);
बाह्य व्योम blk_mq_निकास_shared_sbiपंचांगap(काष्ठा blk_mq_tag_set *set);

बाह्य अचिन्हित पूर्णांक blk_mq_get_tag(काष्ठा blk_mq_alloc_data *data);
बाह्य व्योम blk_mq_put_tag(काष्ठा blk_mq_tags *tags, काष्ठा blk_mq_ctx *ctx,
			   अचिन्हित पूर्णांक tag);
बाह्य पूर्णांक blk_mq_tag_update_depth(काष्ठा blk_mq_hw_ctx *hctx,
					काष्ठा blk_mq_tags **tags,
					अचिन्हित पूर्णांक depth, bool can_grow);
बाह्य व्योम blk_mq_tag_resize_shared_sbiपंचांगap(काष्ठा blk_mq_tag_set *set,
					     अचिन्हित पूर्णांक size);

बाह्य व्योम blk_mq_tag_wakeup_all(काष्ठा blk_mq_tags *tags, bool);
व्योम blk_mq_queue_tag_busy_iter(काष्ठा request_queue *q, busy_iter_fn *fn,
		व्योम *priv);
व्योम blk_mq_all_tag_iter(काष्ठा blk_mq_tags *tags, busy_tag_iter_fn *fn,
		व्योम *priv);

अटल अंतरभूत काष्ठा sbq_रुको_state *bt_रुको_ptr(काष्ठा sbiपंचांगap_queue *bt,
						 काष्ठा blk_mq_hw_ctx *hctx)
अणु
	अगर (!hctx)
		वापस &bt->ws[0];
	वापस sbq_रुको_ptr(bt, &hctx->रुको_index);
पूर्ण

क्रमागत अणु
	BLK_MQ_NO_TAG		= -1U,
	BLK_MQ_TAG_MIN		= 1,
	BLK_MQ_TAG_MAX		= BLK_MQ_NO_TAG - 1,
पूर्ण;

बाह्य bool __blk_mq_tag_busy(काष्ठा blk_mq_hw_ctx *);
बाह्य व्योम __blk_mq_tag_idle(काष्ठा blk_mq_hw_ctx *);

अटल अंतरभूत bool blk_mq_tag_busy(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	अगर (!(hctx->flags & BLK_MQ_F_TAG_QUEUE_SHARED))
		वापस false;

	वापस __blk_mq_tag_busy(hctx);
पूर्ण

अटल अंतरभूत व्योम blk_mq_tag_idle(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	अगर (!(hctx->flags & BLK_MQ_F_TAG_QUEUE_SHARED))
		वापस;

	__blk_mq_tag_idle(hctx);
पूर्ण

अटल अंतरभूत bool blk_mq_tag_is_reserved(काष्ठा blk_mq_tags *tags,
					  अचिन्हित पूर्णांक tag)
अणु
	वापस tag < tags->nr_reserved_tags;
पूर्ण

#पूर्ण_अगर
