<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */
#अगर_अघोषित BRCMFMAC_COMMONRING_H
#घोषणा BRCMFMAC_COMMONRING_H


काष्ठा brcmf_commonring अणु
	u16 r_ptr;
	u16 w_ptr;
	u16 f_ptr;
	u16 depth;
	u16 item_len;

	व्योम *buf_addr;

	पूर्णांक (*cr_ring_bell)(व्योम *ctx);
	पूर्णांक (*cr_update_rptr)(व्योम *ctx);
	पूर्णांक (*cr_update_wptr)(व्योम *ctx);
	पूर्णांक (*cr_ग_लिखो_rptr)(व्योम *ctx);
	पूर्णांक (*cr_ग_लिखो_wptr)(व्योम *ctx);

	व्योम *cr_ctx;

	spinlock_t lock;
	अचिन्हित दीर्घ flags;
	bool inited;
	bool was_full;

	atomic_t outstanding_tx;
पूर्ण;


व्योम brcmf_commonring_रेजिस्टर_cb(काष्ठा brcmf_commonring *commonring,
				  पूर्णांक (*cr_ring_bell)(व्योम *ctx),
				  पूर्णांक (*cr_update_rptr)(व्योम *ctx),
				  पूर्णांक (*cr_update_wptr)(व्योम *ctx),
				  पूर्णांक (*cr_ग_लिखो_rptr)(व्योम *ctx),
				  पूर्णांक (*cr_ग_लिखो_wptr)(व्योम *ctx), व्योम *ctx);
व्योम brcmf_commonring_config(काष्ठा brcmf_commonring *commonring, u16 depth,
			     u16 item_len, व्योम *buf_addr);
व्योम brcmf_commonring_lock(काष्ठा brcmf_commonring *commonring);
व्योम brcmf_commonring_unlock(काष्ठा brcmf_commonring *commonring);
bool brcmf_commonring_ग_लिखो_available(काष्ठा brcmf_commonring *commonring);
व्योम *brcmf_commonring_reserve_क्रम_ग_लिखो(काष्ठा brcmf_commonring *commonring);
व्योम *
brcmf_commonring_reserve_क्रम_ग_लिखो_multiple(काष्ठा brcmf_commonring *commonring,
					    u16 n_items, u16 *alloced);
पूर्णांक brcmf_commonring_ग_लिखो_complete(काष्ठा brcmf_commonring *commonring);
व्योम brcmf_commonring_ग_लिखो_cancel(काष्ठा brcmf_commonring *commonring,
				   u16 n_items);
व्योम *brcmf_commonring_get_पढ़ो_ptr(काष्ठा brcmf_commonring *commonring,
				    u16 *n_items);
पूर्णांक brcmf_commonring_पढ़ो_complete(काष्ठा brcmf_commonring *commonring,
				   u16 n_items);

#घोषणा brcmf_commonring_n_items(commonring) (commonring->depth)
#घोषणा brcmf_commonring_len_item(commonring) (commonring->item_len)


#पूर्ण_अगर /* BRCMFMAC_COMMONRING_H */
