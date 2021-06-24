<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * u_f.c -- USB function utilities क्रम Gadget stack
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#समावेश "u_f.h"
#समावेश <linux/usb/ch9.h>

काष्ठा usb_request *alloc_ep_req(काष्ठा usb_ep *ep, माप_प्रकार len)
अणु
	काष्ठा usb_request      *req;

	req = usb_ep_alloc_request(ep, GFP_ATOMIC);
	अगर (req) अणु
		req->length = usb_endpoपूर्णांक_dir_out(ep->desc) ?
			usb_ep_align(ep, len) : len;
		req->buf = kदो_स्मृति(req->length, GFP_ATOMIC);
		अगर (!req->buf) अणु
			usb_ep_मुक्त_request(ep, req);
			req = शून्य;
		पूर्ण
	पूर्ण
	वापस req;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_ep_req);
