<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */

#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>

#समावेश <brcmu_utils.h>
#समावेश <brcmu_wअगरi.h>

#समावेश "core.h"
#समावेश "commonring.h"

व्योम brcmf_commonring_रेजिस्टर_cb(काष्ठा brcmf_commonring *commonring,
				  पूर्णांक (*cr_ring_bell)(व्योम *ctx),
				  पूर्णांक (*cr_update_rptr)(व्योम *ctx),
				  पूर्णांक (*cr_update_wptr)(व्योम *ctx),
				  पूर्णांक (*cr_ग_लिखो_rptr)(व्योम *ctx),
				  पूर्णांक (*cr_ग_लिखो_wptr)(व्योम *ctx), व्योम *ctx)
अणु
	commonring->cr_ring_bell = cr_ring_bell;
	commonring->cr_update_rptr = cr_update_rptr;
	commonring->cr_update_wptr = cr_update_wptr;
	commonring->cr_ग_लिखो_rptr = cr_ग_लिखो_rptr;
	commonring->cr_ग_लिखो_wptr = cr_ग_लिखो_wptr;
	commonring->cr_ctx = ctx;
पूर्ण


व्योम brcmf_commonring_config(काष्ठा brcmf_commonring *commonring, u16 depth,
			     u16 item_len, व्योम *buf_addr)
अणु
	commonring->depth = depth;
	commonring->item_len = item_len;
	commonring->buf_addr = buf_addr;
	अगर (!commonring->inited) अणु
		spin_lock_init(&commonring->lock);
		commonring->inited = true;
	पूर्ण
	commonring->r_ptr = 0;
	अगर (commonring->cr_ग_लिखो_rptr)
		commonring->cr_ग_लिखो_rptr(commonring->cr_ctx);
	commonring->w_ptr = 0;
	अगर (commonring->cr_ग_लिखो_wptr)
		commonring->cr_ग_लिखो_wptr(commonring->cr_ctx);
	commonring->f_ptr = 0;
पूर्ण


व्योम brcmf_commonring_lock(काष्ठा brcmf_commonring *commonring)
		__acquires(&commonring->lock)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&commonring->lock, flags);
	commonring->flags = flags;
पूर्ण


व्योम brcmf_commonring_unlock(काष्ठा brcmf_commonring *commonring)
		__releases(&commonring->lock)
अणु
	spin_unlock_irqrestore(&commonring->lock, commonring->flags);
पूर्ण


bool brcmf_commonring_ग_लिखो_available(काष्ठा brcmf_commonring *commonring)
अणु
	u16 available;
	bool retry = true;

again:
	अगर (commonring->r_ptr <= commonring->w_ptr)
		available = commonring->depth - commonring->w_ptr +
			    commonring->r_ptr;
	अन्यथा
		available = commonring->r_ptr - commonring->w_ptr;

	अगर (available > 1) अणु
		अगर (!commonring->was_full)
			वापस true;
		अगर (available > commonring->depth / 8) अणु
			commonring->was_full = false;
			वापस true;
		पूर्ण
		अगर (retry) अणु
			अगर (commonring->cr_update_rptr)
				commonring->cr_update_rptr(commonring->cr_ctx);
			retry = false;
			जाओ again;
		पूर्ण
		वापस false;
	पूर्ण

	अगर (retry) अणु
		अगर (commonring->cr_update_rptr)
			commonring->cr_update_rptr(commonring->cr_ctx);
		retry = false;
		जाओ again;
	पूर्ण

	commonring->was_full = true;
	वापस false;
पूर्ण


व्योम *brcmf_commonring_reserve_क्रम_ग_लिखो(काष्ठा brcmf_commonring *commonring)
अणु
	व्योम *ret_ptr;
	u16 available;
	bool retry = true;

again:
	अगर (commonring->r_ptr <= commonring->w_ptr)
		available = commonring->depth - commonring->w_ptr +
			    commonring->r_ptr;
	अन्यथा
		available = commonring->r_ptr - commonring->w_ptr;

	अगर (available > 1) अणु
		ret_ptr = commonring->buf_addr +
			  (commonring->w_ptr * commonring->item_len);
		commonring->w_ptr++;
		अगर (commonring->w_ptr == commonring->depth)
			commonring->w_ptr = 0;
		वापस ret_ptr;
	पूर्ण

	अगर (retry) अणु
		अगर (commonring->cr_update_rptr)
			commonring->cr_update_rptr(commonring->cr_ctx);
		retry = false;
		जाओ again;
	पूर्ण

	commonring->was_full = true;
	वापस शून्य;
पूर्ण


व्योम *
brcmf_commonring_reserve_क्रम_ग_लिखो_multiple(काष्ठा brcmf_commonring *commonring,
					    u16 n_items, u16 *alloced)
अणु
	व्योम *ret_ptr;
	u16 available;
	bool retry = true;

again:
	अगर (commonring->r_ptr <= commonring->w_ptr)
		available = commonring->depth - commonring->w_ptr +
			    commonring->r_ptr;
	अन्यथा
		available = commonring->r_ptr - commonring->w_ptr;

	अगर (available > 1) अणु
		ret_ptr = commonring->buf_addr +
			  (commonring->w_ptr * commonring->item_len);
		*alloced = min_t(u16, n_items, available - 1);
		अगर (*alloced + commonring->w_ptr > commonring->depth)
			*alloced = commonring->depth - commonring->w_ptr;
		commonring->w_ptr += *alloced;
		अगर (commonring->w_ptr == commonring->depth)
			commonring->w_ptr = 0;
		वापस ret_ptr;
	पूर्ण

	अगर (retry) अणु
		अगर (commonring->cr_update_rptr)
			commonring->cr_update_rptr(commonring->cr_ctx);
		retry = false;
		जाओ again;
	पूर्ण

	commonring->was_full = true;
	वापस शून्य;
पूर्ण


पूर्णांक brcmf_commonring_ग_लिखो_complete(काष्ठा brcmf_commonring *commonring)
अणु
	अगर (commonring->f_ptr > commonring->w_ptr)
		commonring->f_ptr = 0;

	commonring->f_ptr = commonring->w_ptr;

	अगर (commonring->cr_ग_लिखो_wptr)
		commonring->cr_ग_लिखो_wptr(commonring->cr_ctx);
	अगर (commonring->cr_ring_bell)
		वापस commonring->cr_ring_bell(commonring->cr_ctx);

	वापस -EIO;
पूर्ण


व्योम brcmf_commonring_ग_लिखो_cancel(काष्ठा brcmf_commonring *commonring,
				   u16 n_items)
अणु
	अगर (commonring->w_ptr == 0)
		commonring->w_ptr = commonring->depth - n_items;
	अन्यथा
		commonring->w_ptr -= n_items;
पूर्ण


व्योम *brcmf_commonring_get_पढ़ो_ptr(काष्ठा brcmf_commonring *commonring,
				    u16 *n_items)
अणु
	अगर (commonring->cr_update_wptr)
		commonring->cr_update_wptr(commonring->cr_ctx);

	*n_items = (commonring->w_ptr >= commonring->r_ptr) ?
				(commonring->w_ptr - commonring->r_ptr) :
				(commonring->depth - commonring->r_ptr);

	अगर (*n_items == 0)
		वापस शून्य;

	वापस commonring->buf_addr +
	       (commonring->r_ptr * commonring->item_len);
पूर्ण


पूर्णांक brcmf_commonring_पढ़ो_complete(काष्ठा brcmf_commonring *commonring,
				   u16 n_items)
अणु
	commonring->r_ptr += n_items;
	अगर (commonring->r_ptr == commonring->depth)
		commonring->r_ptr = 0;

	अगर (commonring->cr_ग_लिखो_rptr)
		वापस commonring->cr_ग_लिखो_rptr(commonring->cr_ctx);

	वापस -EIO;
पूर्ण
