<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * u_f.h
 *
 * Utility definitions क्रम USB functions
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#अगर_अघोषित __U_F_H__
#घोषणा __U_F_H__

#समावेश <linux/usb/gadget.h>
#समावेश <linux/overflow.h>

/* Variable Length Array Macros **********************************************/
#घोषणा vla_group(groupname) माप_प्रकार groupname##__next = 0
#घोषणा vla_group_size(groupname) groupname##__next

#घोषणा vla_item(groupname, type, name, n) \
	माप_प्रकार groupname##_##name##__offset = (अणु			       \
		माप_प्रकार offset = 0;					       \
		अगर (groupname##__next != SIZE_MAX) अणु			       \
			माप_प्रकार align_mask = __alignof__(type) - 1;	       \
			माप_प्रकार size = array_size(n, माप(type));	       \
			offset = (groupname##__next + align_mask) &	       \
				  ~align_mask;				       \
			अगर (check_add_overflow(offset, size,		       \
					       &groupname##__next)) अणु          \
				groupname##__next = SIZE_MAX;		       \
				offset = 0;				       \
			पूर्ण						       \
		पूर्ण							       \
		offset;							       \
	पूर्ण)

#घोषणा vla_item_with_sz(groupname, type, name, n) \
	माप_प्रकार groupname##_##name##__sz = array_size(n, माप(type));	        \
	माप_प्रकार groupname##_##name##__offset = (अणु			        \
		माप_प्रकार offset = 0;						\
		अगर (groupname##__next != SIZE_MAX) अणु				\
			माप_प्रकार align_mask = __alignof__(type) - 1;		\
			offset = (groupname##__next + align_mask) &		\
				  ~align_mask;					\
			अगर (check_add_overflow(offset, groupname##_##name##__sz,\
							&groupname##__next)) अणु	\
				groupname##__next = SIZE_MAX;			\
				offset = 0;					\
			पूर्ण							\
		पूर्ण								\
		offset;								\
	पूर्ण)

#घोषणा vla_ptr(ptr, groupname, name) \
	((व्योम *) ((अक्षर *)ptr + groupname##_##name##__offset))

काष्ठा usb_ep;
काष्ठा usb_request;

/**
 * alloc_ep_req - वापसs a usb_request allocated by the gadget driver and
 * allocates the request's buffer.
 *
 * @ep: the endpoपूर्णांक to allocate a usb_request
 * @len: usb_requests's buffer suggested size
 *
 * In हाल @ep direction is OUT, the @len will be aligned to ep's
 * wMaxPacketSize. In order to aव्योम memory leaks or drops, *always* use
 * usb_requests's length (req->length) to refer to the allocated buffer size.
 * Requests allocated via alloc_ep_req() *must* be मुक्तd by मुक्त_ep_req().
 */
काष्ठा usb_request *alloc_ep_req(काष्ठा usb_ep *ep, माप_प्रकार len);

/* Frees a usb_request previously allocated by alloc_ep_req() */
अटल अंतरभूत व्योम मुक्त_ep_req(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	WARN_ON(req->buf == शून्य);
	kमुक्त(req->buf);
	req->buf = शून्य;
	usb_ep_मुक्त_request(ep, req);
पूर्ण

#पूर्ण_अगर /* __U_F_H__ */
