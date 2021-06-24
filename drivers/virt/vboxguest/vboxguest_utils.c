<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR CDDL-1.0) */
/*
 * vboxguest vmm-req and hgcm-call code, VBoxGuestR0LibHGCMInternal.cpp,
 * VBoxGuestR0LibGenericRequest.cpp and RTErrConvertToErrno.cpp in vbox svn.
 *
 * Copyright (C) 2006-2016 Oracle Corporation
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/vbox_err.h>
#समावेश <linux/vbox_utils.h>
#समावेश "vboxguest_core.h"

/* Get the poपूर्णांकer to the first parameter of a HGCM call request. */
#घोषणा VMMDEV_HGCM_CALL_PARMS(a) \
	((काष्ठा vmmdev_hgcm_function_parameter *)( \
		(u8 *)(a) + माप(काष्ठा vmmdev_hgcm_call)))

/* The max parameter buffer size क्रम a user request. */
#घोषणा VBG_MAX_HGCM_USER_PARM		(24 * SZ_1M)
/* The max parameter buffer size क्रम a kernel request. */
#घोषणा VBG_MAX_HGCM_KERNEL_PARM	(16 * SZ_1M)

#घोषणा VBG_DEBUG_PORT			0x504

/* This protects vbg_log_buf and serializes VBG_DEBUG_PORT accesses */
अटल DEFINE_SPINLOCK(vbg_log_lock);
अटल अक्षर vbg_log_buf[128];

#घोषणा VBG_LOG(name, pr_func) \
व्योम name(स्थिर अक्षर *fmt, ...)						\
अणु									\
	अचिन्हित दीर्घ flags;						\
	बहु_सूची args;							\
	पूर्णांक i, count;							\
									\
	बहु_शुरू(args, fmt);						\
	spin_lock_irqsave(&vbg_log_lock, flags);			\
									\
	count = vscnम_लिखो(vbg_log_buf, माप(vbg_log_buf), fmt, args);\
	क्रम (i = 0; i < count; i++)					\
		outb(vbg_log_buf[i], VBG_DEBUG_PORT);			\
									\
	pr_func("%s", vbg_log_buf);					\
									\
	spin_unlock_irqrestore(&vbg_log_lock, flags);			\
	बहु_पूर्ण(args);							\
पूर्ण									\
EXPORT_SYMBOL(name)

VBG_LOG(vbg_info, pr_info);
VBG_LOG(vbg_warn, pr_warn);
VBG_LOG(vbg_err, pr_err);
VBG_LOG(vbg_err_ratelimited, pr_err_ratelimited);
#अगर defined(DEBUG) && !defined(CONFIG_DYNAMIC_DEBUG)
VBG_LOG(vbg_debug, pr_debug);
#पूर्ण_अगर

व्योम *vbg_req_alloc(माप_प्रकार len, क्रमागत vmmdev_request_type req_type,
		    u32 requestor)
अणु
	काष्ठा vmmdev_request_header *req;
	पूर्णांक order = get_order(PAGE_ALIGN(len));

	req = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | GFP_DMA32, order);
	अगर (!req)
		वापस शून्य;

	स_रखो(req, 0xaa, len);

	req->size = len;
	req->version = VMMDEV_REQUEST_HEADER_VERSION;
	req->request_type = req_type;
	req->rc = VERR_GENERAL_FAILURE;
	req->reserved1 = 0;
	req->requestor = requestor;

	वापस req;
पूर्ण

व्योम vbg_req_मुक्त(व्योम *req, माप_प्रकार len)
अणु
	अगर (!req)
		वापस;

	मुक्त_pages((अचिन्हित दीर्घ)req, get_order(PAGE_ALIGN(len)));
पूर्ण

/* Note this function वापसs a VBox status code, not a negative त्रुटि_सं!! */
पूर्णांक vbg_req_perक्रमm(काष्ठा vbg_dev *gdev, व्योम *req)
अणु
	अचिन्हित दीर्घ phys_req = virt_to_phys(req);

	outl(phys_req, gdev->io_port + VMMDEV_PORT_OFF_REQUEST);
	/*
	 * The host changes the request as a result of the outl, make sure
	 * the outl and any पढ़ोs of the req happen in the correct order.
	 */
	mb();

	वापस ((काष्ठा vmmdev_request_header *)req)->rc;
पूर्ण

अटल bool hgcm_req_करोne(काष्ठा vbg_dev *gdev,
			  काष्ठा vmmdev_hgcmreq_header *header)
अणु
	अचिन्हित दीर्घ flags;
	bool करोne;

	spin_lock_irqsave(&gdev->event_spinlock, flags);
	करोne = header->flags & VMMDEV_HGCM_REQ_DONE;
	spin_unlock_irqrestore(&gdev->event_spinlock, flags);

	वापस करोne;
पूर्ण

पूर्णांक vbg_hgcm_connect(काष्ठा vbg_dev *gdev, u32 requestor,
		     काष्ठा vmmdev_hgcm_service_location *loc,
		     u32 *client_id, पूर्णांक *vbox_status)
अणु
	काष्ठा vmmdev_hgcm_connect *hgcm_connect = शून्य;
	पूर्णांक rc;

	hgcm_connect = vbg_req_alloc(माप(*hgcm_connect),
				     VMMDEVREQ_HGCM_CONNECT, requestor);
	अगर (!hgcm_connect)
		वापस -ENOMEM;

	hgcm_connect->header.flags = 0;
	स_नकल(&hgcm_connect->loc, loc, माप(*loc));
	hgcm_connect->client_id = 0;

	rc = vbg_req_perक्रमm(gdev, hgcm_connect);

	अगर (rc == VINF_HGCM_ASYNC_EXECUTE)
		रुको_event(gdev->hgcm_wq,
			   hgcm_req_करोne(gdev, &hgcm_connect->header));

	अगर (rc >= 0) अणु
		*client_id = hgcm_connect->client_id;
		rc = hgcm_connect->header.result;
	पूर्ण

	vbg_req_मुक्त(hgcm_connect, माप(*hgcm_connect));

	*vbox_status = rc;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vbg_hgcm_connect);

पूर्णांक vbg_hgcm_disconnect(काष्ठा vbg_dev *gdev, u32 requestor,
			u32 client_id, पूर्णांक *vbox_status)
अणु
	काष्ठा vmmdev_hgcm_disconnect *hgcm_disconnect = शून्य;
	पूर्णांक rc;

	hgcm_disconnect = vbg_req_alloc(माप(*hgcm_disconnect),
					VMMDEVREQ_HGCM_DISCONNECT,
					requestor);
	अगर (!hgcm_disconnect)
		वापस -ENOMEM;

	hgcm_disconnect->header.flags = 0;
	hgcm_disconnect->client_id = client_id;

	rc = vbg_req_perक्रमm(gdev, hgcm_disconnect);

	अगर (rc == VINF_HGCM_ASYNC_EXECUTE)
		रुको_event(gdev->hgcm_wq,
			   hgcm_req_करोne(gdev, &hgcm_disconnect->header));

	अगर (rc >= 0)
		rc = hgcm_disconnect->header.result;

	vbg_req_मुक्त(hgcm_disconnect, माप(*hgcm_disconnect));

	*vbox_status = rc;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vbg_hgcm_disconnect);

अटल u32 hgcm_call_buf_size_in_pages(व्योम *buf, u32 len)
अणु
	u32 size = PAGE_ALIGN(len + ((अचिन्हित दीर्घ)buf & ~PAGE_MASK));

	वापस size >> PAGE_SHIFT;
पूर्ण

अटल व्योम hgcm_call_add_pagelist_size(व्योम *buf, u32 len, माप_प्रकार *extra)
अणु
	u32 page_count;

	page_count = hgcm_call_buf_size_in_pages(buf, len);
	*extra += दुरत्व(काष्ठा vmmdev_hgcm_pagelist, pages[page_count]);
पूर्ण

अटल पूर्णांक hgcm_call_preprocess_linaddr(
	स्थिर काष्ठा vmmdev_hgcm_function_parameter *src_parm,
	व्योम **bounce_buf_ret, माप_प्रकार *extra)
अणु
	व्योम *buf, *bounce_buf;
	bool copy_in;
	u32 len;
	पूर्णांक ret;

	buf = (व्योम *)src_parm->u.poपूर्णांकer.u.linear_addr;
	len = src_parm->u.poपूर्णांकer.size;
	copy_in = src_parm->type != VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT;

	अगर (len > VBG_MAX_HGCM_USER_PARM)
		वापस -E2BIG;

	bounce_buf = kvदो_स्मृति(len, GFP_KERNEL);
	अगर (!bounce_buf)
		वापस -ENOMEM;

	*bounce_buf_ret = bounce_buf;

	अगर (copy_in) अणु
		ret = copy_from_user(bounce_buf, (व्योम __user *)buf, len);
		अगर (ret)
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		स_रखो(bounce_buf, 0, len);
	पूर्ण

	hgcm_call_add_pagelist_size(bounce_buf, len, extra);
	वापस 0;
पूर्ण

/**
 * Preprocesses the HGCM call, validate parameters, alloc bounce buffers and
 * figure out how much extra storage we need क्रम page lists.
 * Return: 0 or negative त्रुटि_सं value.
 * @src_parm:         Poपूर्णांकer to source function call parameters
 * @parm_count:       Number of function call parameters.
 * @bounce_bufs_ret:  Where to वापस the allocated bouncebuffer array
 * @extra:            Where to वापस the extra request space needed क्रम
 *                    physical page lists.
 */
अटल पूर्णांक hgcm_call_preprocess(
	स्थिर काष्ठा vmmdev_hgcm_function_parameter *src_parm,
	u32 parm_count, व्योम ***bounce_bufs_ret, माप_प्रकार *extra)
अणु
	व्योम *buf, **bounce_bufs = शून्य;
	u32 i, len;
	पूर्णांक ret;

	क्रम (i = 0; i < parm_count; i++, src_parm++) अणु
		चयन (src_parm->type) अणु
		हाल VMMDEV_HGCM_PARM_TYPE_32BIT:
		हाल VMMDEV_HGCM_PARM_TYPE_64BIT:
			अवरोध;

		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_IN:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT:
			अगर (!bounce_bufs) अणु
				bounce_bufs = kसुस्मृति(parm_count,
						      माप(व्योम *),
						      GFP_KERNEL);
				अगर (!bounce_bufs)
					वापस -ENOMEM;

				*bounce_bufs_ret = bounce_bufs;
			पूर्ण

			ret = hgcm_call_preprocess_linaddr(src_parm,
							   &bounce_bufs[i],
							   extra);
			अगर (ret)
				वापस ret;

			अवरोध;

		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT:
			buf = (व्योम *)src_parm->u.poपूर्णांकer.u.linear_addr;
			len = src_parm->u.poपूर्णांकer.size;
			अगर (WARN_ON(len > VBG_MAX_HGCM_KERNEL_PARM))
				वापस -E2BIG;

			hgcm_call_add_pagelist_size(buf, len, extra);
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * Translates linear address types to page list direction flags.
 *
 * Return: page list flags.
 * @type:  The type.
 */
अटल u32 hgcm_call_linear_addr_type_to_pagelist_flags(
	क्रमागत vmmdev_hgcm_function_parameter_type type)
अणु
	चयन (type) अणु
	शेष:
		WARN_ON(1);
		fallthrough;
	हाल VMMDEV_HGCM_PARM_TYPE_LINADDR:
	हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL:
		वापस VMMDEV_HGCM_F_PARM_सूचीECTION_BOTH;

	हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_IN:
	हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN:
		वापस VMMDEV_HGCM_F_PARM_सूचीECTION_TO_HOST;

	हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT:
	हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT:
		वापस VMMDEV_HGCM_F_PARM_सूचीECTION_FROM_HOST;
	पूर्ण
पूर्ण

अटल व्योम hgcm_call_init_linaddr(काष्ठा vmmdev_hgcm_call *call,
	काष्ठा vmmdev_hgcm_function_parameter *dst_parm, व्योम *buf, u32 len,
	क्रमागत vmmdev_hgcm_function_parameter_type type, u32 *off_extra)
अणु
	काष्ठा vmmdev_hgcm_pagelist *dst_pg_lst;
	काष्ठा page *page;
	bool is_vदो_स्मृति;
	u32 i, page_count;

	dst_parm->type = type;

	अगर (len == 0) अणु
		dst_parm->u.poपूर्णांकer.size = 0;
		dst_parm->u.poपूर्णांकer.u.linear_addr = 0;
		वापस;
	पूर्ण

	dst_pg_lst = (व्योम *)call + *off_extra;
	page_count = hgcm_call_buf_size_in_pages(buf, len);
	is_vदो_स्मृति = is_vदो_स्मृति_addr(buf);

	dst_parm->type = VMMDEV_HGCM_PARM_TYPE_PAGELIST;
	dst_parm->u.page_list.size = len;
	dst_parm->u.page_list.offset = *off_extra;
	dst_pg_lst->flags = hgcm_call_linear_addr_type_to_pagelist_flags(type);
	dst_pg_lst->offset_first_page = (अचिन्हित दीर्घ)buf & ~PAGE_MASK;
	dst_pg_lst->page_count = page_count;

	क्रम (i = 0; i < page_count; i++) अणु
		अगर (is_vदो_स्मृति)
			page = vदो_स्मृति_to_page(buf);
		अन्यथा
			page = virt_to_page(buf);

		dst_pg_lst->pages[i] = page_to_phys(page);
		buf += PAGE_SIZE;
	पूर्ण

	*off_extra += दुरत्व(काष्ठा vmmdev_hgcm_pagelist, pages[page_count]);
पूर्ण

/**
 * Initializes the call request that we're sending to the host.
 * @call:            The call to initialize.
 * @client_id:       The client ID of the caller.
 * @function:        The function number of the function to call.
 * @src_parm:        Poपूर्णांकer to source function call parameters.
 * @parm_count:      Number of function call parameters.
 * @bounce_bufs:     The bouncebuffer array.
 */
अटल व्योम hgcm_call_init_call(
	काष्ठा vmmdev_hgcm_call *call, u32 client_id, u32 function,
	स्थिर काष्ठा vmmdev_hgcm_function_parameter *src_parm,
	u32 parm_count, व्योम **bounce_bufs)
अणु
	काष्ठा vmmdev_hgcm_function_parameter *dst_parm =
		VMMDEV_HGCM_CALL_PARMS(call);
	u32 i, off_extra = (uपूर्णांकptr_t)(dst_parm + parm_count) - (uपूर्णांकptr_t)call;
	व्योम *buf;

	call->header.flags = 0;
	call->header.result = VINF_SUCCESS;
	call->client_id = client_id;
	call->function = function;
	call->parm_count = parm_count;

	क्रम (i = 0; i < parm_count; i++, src_parm++, dst_parm++) अणु
		चयन (src_parm->type) अणु
		हाल VMMDEV_HGCM_PARM_TYPE_32BIT:
		हाल VMMDEV_HGCM_PARM_TYPE_64BIT:
			*dst_parm = *src_parm;
			अवरोध;

		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_IN:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT:
			hgcm_call_init_linaddr(call, dst_parm, bounce_bufs[i],
					       src_parm->u.poपूर्णांकer.size,
					       src_parm->type, &off_extra);
			अवरोध;

		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT:
			buf = (व्योम *)src_parm->u.poपूर्णांकer.u.linear_addr;
			hgcm_call_init_linaddr(call, dst_parm, buf,
					       src_parm->u.poपूर्णांकer.size,
					       src_parm->type, &off_extra);
			अवरोध;

		शेष:
			WARN_ON(1);
			dst_parm->type = VMMDEV_HGCM_PARM_TYPE_INVALID;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * Tries to cancel a pending HGCM call.
 *
 * Return: VBox status code
 */
अटल पूर्णांक hgcm_cancel_call(काष्ठा vbg_dev *gdev, काष्ठा vmmdev_hgcm_call *call)
अणु
	पूर्णांक rc;

	/*
	 * We use a pre-allocated request क्रम cancellations, which is
	 * रक्षित by cancel_req_mutex. This means that all cancellations
	 * get serialized, this should be fine since they should be rare.
	 */
	mutex_lock(&gdev->cancel_req_mutex);
	gdev->cancel_req->phys_req_to_cancel = virt_to_phys(call);
	rc = vbg_req_perक्रमm(gdev, gdev->cancel_req);
	mutex_unlock(&gdev->cancel_req_mutex);

	अगर (rc == VERR_NOT_IMPLEMENTED) अणु
		call->header.flags |= VMMDEV_HGCM_REQ_CANCELLED;
		call->header.header.request_type = VMMDEVREQ_HGCM_CANCEL;

		rc = vbg_req_perक्रमm(gdev, call);
		अगर (rc == VERR_INVALID_PARAMETER)
			rc = VERR_NOT_FOUND;
	पूर्ण

	अगर (rc >= 0)
		call->header.flags |= VMMDEV_HGCM_REQ_CANCELLED;

	वापस rc;
पूर्ण

/**
 * Perक्रमms the call and completion रुको.
 * Return: 0 or negative त्रुटि_सं value.
 * @gdev:        The VBoxGuest device extension.
 * @call:        The call to execute.
 * @समयout_ms:  Timeout in ms.
 * @leak_it:     Where to वापस the leak it / मुक्त it, indicator.
 *               Cancellation fun.
 */
अटल पूर्णांक vbg_hgcm_करो_call(काष्ठा vbg_dev *gdev, काष्ठा vmmdev_hgcm_call *call,
			    u32 समयout_ms, bool पूर्णांकerruptible, bool *leak_it)
अणु
	पूर्णांक rc, cancel_rc, ret;
	दीर्घ समयout;

	*leak_it = false;

	rc = vbg_req_perक्रमm(gdev, call);

	/*
	 * If the call failed, then pretend success. Upper layers will
	 * पूर्णांकerpret the result code in the packet.
	 */
	अगर (rc < 0) अणु
		call->header.result = rc;
		वापस 0;
	पूर्ण

	अगर (rc != VINF_HGCM_ASYNC_EXECUTE)
		वापस 0;

	/* Host decided to process the request asynchronously, रुको क्रम it */
	अगर (समयout_ms == U32_MAX)
		समयout = MAX_SCHEDULE_TIMEOUT;
	अन्यथा
		समयout = msecs_to_jअगरfies(समयout_ms);

	अगर (पूर्णांकerruptible) अणु
		समयout = रुको_event_पूर्णांकerruptible_समयout(gdev->hgcm_wq,
							   hgcm_req_करोne(gdev, &call->header),
							   समयout);
	पूर्ण अन्यथा अणु
		समयout = रुको_event_समयout(gdev->hgcm_wq,
					     hgcm_req_करोne(gdev, &call->header),
					     समयout);
	पूर्ण

	/* समयout > 0 means hgcm_req_करोne has वापसed true, so success */
	अगर (समयout > 0)
		वापस 0;

	अगर (समयout == 0)
		ret = -ETIMEDOUT;
	अन्यथा
		ret = -EINTR;

	/* Cancel the request */
	cancel_rc = hgcm_cancel_call(gdev, call);
	अगर (cancel_rc >= 0)
		वापस ret;

	/*
	 * Failed to cancel, this should mean that the cancel has lost the
	 * race with normal completion, रुको जबतक the host completes it.
	 */
	अगर (cancel_rc == VERR_NOT_FOUND || cancel_rc == VERR_SEM_DESTROYED)
		समयout = msecs_to_jअगरfies(500);
	अन्यथा
		समयout = msecs_to_jअगरfies(2000);

	समयout = रुको_event_समयout(gdev->hgcm_wq,
				     hgcm_req_करोne(gdev, &call->header),
				     समयout);

	अगर (WARN_ON(समयout == 0)) अणु
		/* We really should never get here */
		vbg_err("%s: Call timedout and cancellation failed, leaking the request\n",
			__func__);
		*leak_it = true;
		वापस ret;
	पूर्ण

	/* The call has completed normally after all */
	वापस 0;
पूर्ण

/**
 * Copies the result of the call back to the caller info काष्ठाure and user
 * buffers.
 * Return: 0 or negative त्रुटि_सं value.
 * @call:            HGCM call request.
 * @dst_parm:        Poपूर्णांकer to function call parameters destination.
 * @parm_count:      Number of function call parameters.
 * @bounce_bufs:     The bouncebuffer array.
 */
अटल पूर्णांक hgcm_call_copy_back_result(
	स्थिर काष्ठा vmmdev_hgcm_call *call,
	काष्ठा vmmdev_hgcm_function_parameter *dst_parm,
	u32 parm_count, व्योम **bounce_bufs)
अणु
	स्थिर काष्ठा vmmdev_hgcm_function_parameter *src_parm =
		VMMDEV_HGCM_CALL_PARMS(call);
	व्योम __user *p;
	पूर्णांक ret;
	u32 i;

	/* Copy back parameters. */
	क्रम (i = 0; i < parm_count; i++, src_parm++, dst_parm++) अणु
		चयन (dst_parm->type) अणु
		हाल VMMDEV_HGCM_PARM_TYPE_32BIT:
		हाल VMMDEV_HGCM_PARM_TYPE_64BIT:
			*dst_parm = *src_parm;
			अवरोध;

		हाल VMMDEV_HGCM_PARM_TYPE_PAGELIST:
			dst_parm->u.page_list.size = src_parm->u.page_list.size;
			अवरोध;

		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_IN:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT:
			dst_parm->u.poपूर्णांकer.size = src_parm->u.poपूर्णांकer.size;
			अवरोध;

		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT:
			dst_parm->u.poपूर्णांकer.size = src_parm->u.poपूर्णांकer.size;

			p = (व्योम __user *)dst_parm->u.poपूर्णांकer.u.linear_addr;
			ret = copy_to_user(p, bounce_bufs[i],
					   min(src_parm->u.poपूर्णांकer.size,
					       dst_parm->u.poपूर्णांकer.size));
			अगर (ret)
				वापस -EFAULT;
			अवरोध;

		शेष:
			WARN_ON(1);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vbg_hgcm_call(काष्ठा vbg_dev *gdev, u32 requestor, u32 client_id,
		  u32 function, u32 समयout_ms,
		  काष्ठा vmmdev_hgcm_function_parameter *parms, u32 parm_count,
		  पूर्णांक *vbox_status)
अणु
	काष्ठा vmmdev_hgcm_call *call;
	व्योम **bounce_bufs = शून्य;
	bool leak_it;
	माप_प्रकार size;
	पूर्णांक i, ret;

	size = माप(काष्ठा vmmdev_hgcm_call) +
		   parm_count * माप(काष्ठा vmmdev_hgcm_function_parameter);
	/*
	 * Validate and buffer the parameters क्रम the call. This also increases
	 * call_size with the amount of extra space needed क्रम page lists.
	 */
	ret = hgcm_call_preprocess(parms, parm_count, &bounce_bufs, &size);
	अगर (ret) अणु
		/* Even on error bounce bufs may still have been allocated */
		जाओ मुक्त_bounce_bufs;
	पूर्ण

	call = vbg_req_alloc(size, VMMDEVREQ_HGCM_CALL, requestor);
	अगर (!call) अणु
		ret = -ENOMEM;
		जाओ मुक्त_bounce_bufs;
	पूर्ण

	hgcm_call_init_call(call, client_id, function, parms, parm_count,
			    bounce_bufs);

	ret = vbg_hgcm_करो_call(gdev, call, समयout_ms,
			       requestor & VMMDEV_REQUESTOR_USERMODE, &leak_it);
	अगर (ret == 0) अणु
		*vbox_status = call->header.result;
		ret = hgcm_call_copy_back_result(call, parms, parm_count,
						 bounce_bufs);
	पूर्ण

	अगर (!leak_it)
		vbg_req_मुक्त(call, size);

मुक्त_bounce_bufs:
	अगर (bounce_bufs) अणु
		क्रम (i = 0; i < parm_count; i++)
			kvमुक्त(bounce_bufs[i]);
		kमुक्त(bounce_bufs);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vbg_hgcm_call);

#अगर_घोषित CONFIG_COMPAT
पूर्णांक vbg_hgcm_call32(
	काष्ठा vbg_dev *gdev, u32 requestor, u32 client_id, u32 function,
	u32 समयout_ms, काष्ठा vmmdev_hgcm_function_parameter32 *parm32,
	u32 parm_count, पूर्णांक *vbox_status)
अणु
	काष्ठा vmmdev_hgcm_function_parameter *parm64 = शून्य;
	u32 i, size;
	पूर्णांक ret = 0;

	/* KISS allocate a temporary request and convert the parameters. */
	size = parm_count * माप(काष्ठा vmmdev_hgcm_function_parameter);
	parm64 = kzalloc(size, GFP_KERNEL);
	अगर (!parm64)
		वापस -ENOMEM;

	क्रम (i = 0; i < parm_count; i++) अणु
		चयन (parm32[i].type) अणु
		हाल VMMDEV_HGCM_PARM_TYPE_32BIT:
			parm64[i].type = VMMDEV_HGCM_PARM_TYPE_32BIT;
			parm64[i].u.value32 = parm32[i].u.value32;
			अवरोध;

		हाल VMMDEV_HGCM_PARM_TYPE_64BIT:
			parm64[i].type = VMMDEV_HGCM_PARM_TYPE_64BIT;
			parm64[i].u.value64 = parm32[i].u.value64;
			अवरोध;

		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_IN:
			parm64[i].type = parm32[i].type;
			parm64[i].u.poपूर्णांकer.size = parm32[i].u.poपूर्णांकer.size;
			parm64[i].u.poपूर्णांकer.u.linear_addr =
			    parm32[i].u.poपूर्णांकer.u.linear_addr;
			अवरोध;

		शेष:
			ret = -EINVAL;
		पूर्ण
		अगर (ret < 0)
			जाओ out_मुक्त;
	पूर्ण

	ret = vbg_hgcm_call(gdev, requestor, client_id, function, समयout_ms,
			    parm64, parm_count, vbox_status);
	अगर (ret < 0)
		जाओ out_मुक्त;

	/* Copy back. */
	क्रम (i = 0; i < parm_count; i++, parm32++, parm64++) अणु
		चयन (parm64[i].type) अणु
		हाल VMMDEV_HGCM_PARM_TYPE_32BIT:
			parm32[i].u.value32 = parm64[i].u.value32;
			अवरोध;

		हाल VMMDEV_HGCM_PARM_TYPE_64BIT:
			parm32[i].u.value64 = parm64[i].u.value64;
			अवरोध;

		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR:
		हाल VMMDEV_HGCM_PARM_TYPE_LINADDR_IN:
			parm32[i].u.poपूर्णांकer.size = parm64[i].u.poपूर्णांकer.size;
			अवरोध;

		शेष:
			WARN_ON(1);
			ret = -EINVAL;
		पूर्ण
	पूर्ण

out_मुक्त:
	kमुक्त(parm64);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर पूर्णांक vbg_status_code_to_त्रुटि_सं_table[] = अणु
	[-VERR_ACCESS_DENIED]                            = -EPERM,
	[-VERR_खाता_NOT_FOUND]                           = -ENOENT,
	[-VERR_PROCESS_NOT_FOUND]                        = -ESRCH,
	[-VERR_INTERRUPTED]                              = -EINTR,
	[-VERR_DEV_IO_ERROR]                             = -EIO,
	[-VERR_TOO_MUCH_DATA]                            = -E2BIG,
	[-VERR_BAD_EXE_FORMAT]                           = -ENOEXEC,
	[-VERR_INVALID_HANDLE]                           = -EBADF,
	[-VERR_TRY_AGAIN]                                = -EAGAIN,
	[-VERR_NO_MEMORY]                                = -ENOMEM,
	[-VERR_INVALID_POINTER]                          = -EFAULT,
	[-VERR_RESOURCE_BUSY]                            = -EBUSY,
	[-VERR_ALREADY_EXISTS]                           = -EEXIST,
	[-VERR_NOT_SAME_DEVICE]                          = -EXDEV,
	[-VERR_NOT_A_सूचीECTORY]                          = -ENOTसूची,
	[-VERR_PATH_NOT_FOUND]                           = -ENOTसूची,
	[-VERR_INVALID_NAME]                             = -ENOENT,
	[-VERR_IS_A_सूचीECTORY]                           = -EISसूची,
	[-VERR_INVALID_PARAMETER]                        = -EINVAL,
	[-VERR_TOO_MANY_OPEN_खाताS]                      = -ENखाता,
	[-VERR_INVALID_FUNCTION]                         = -ENOTTY,
	[-VERR_SHARING_VIOLATION]                        = -ETXTBSY,
	[-VERR_खाता_TOO_BIG]                             = -EFBIG,
	[-VERR_DISK_FULL]                                = -ENOSPC,
	[-VERR_SEEK_ON_DEVICE]                           = -ESPIPE,
	[-VERR_WRITE_PROTECT]                            = -EROFS,
	[-VERR_BROKEN_PIPE]                              = -EPIPE,
	[-VERR_DEADLOCK]                                 = -EDEADLK,
	[-VERR_खाताNAME_TOO_LONG]                        = -ENAMETOOLONG,
	[-VERR_खाता_LOCK_FAILED]                         = -ENOLCK,
	[-VERR_NOT_IMPLEMENTED]                          = -ENOSYS,
	[-VERR_NOT_SUPPORTED]                            = -ENOSYS,
	[-VERR_सूची_NOT_EMPTY]                            = -ENOTEMPTY,
	[-VERR_TOO_MANY_SYMLINKS]                        = -ELOOP,
	[-VERR_NO_MORE_खाताS]				 = -ENODATA,
	[-VERR_NO_DATA]                                  = -ENODATA,
	[-VERR_NET_NO_NETWORK]                           = -ENONET,
	[-VERR_NET_NOT_UNIQUE_NAME]                      = -ENOTUNIQ,
	[-VERR_NO_TRANSLATION]                           = -EILSEQ,
	[-VERR_NET_NOT_SOCKET]                           = -ENOTSOCK,
	[-VERR_NET_DEST_ADDRESS_REQUIRED]                = -EDESTADDRREQ,
	[-VERR_NET_MSG_SIZE]                             = -EMSGSIZE,
	[-VERR_NET_PROTOCOL_TYPE]                        = -EPROTOTYPE,
	[-VERR_NET_PROTOCOL_NOT_AVAILABLE]               = -ENOPROTOOPT,
	[-VERR_NET_PROTOCOL_NOT_SUPPORTED]               = -EPROTONOSUPPORT,
	[-VERR_NET_SOCKET_TYPE_NOT_SUPPORTED]            = -ESOCKTNOSUPPORT,
	[-VERR_NET_OPERATION_NOT_SUPPORTED]              = -EOPNOTSUPP,
	[-VERR_NET_PROTOCOL_FAMILY_NOT_SUPPORTED]        = -EPFNOSUPPORT,
	[-VERR_NET_ADDRESS_FAMILY_NOT_SUPPORTED]         = -EAFNOSUPPORT,
	[-VERR_NET_ADDRESS_IN_USE]                       = -EADDRINUSE,
	[-VERR_NET_ADDRESS_NOT_AVAILABLE]                = -EADDRNOTAVAIL,
	[-VERR_NET_DOWN]                                 = -ENETDOWN,
	[-VERR_NET_UNREACHABLE]                          = -ENETUNREACH,
	[-VERR_NET_CONNECTION_RESET]                     = -ENETRESET,
	[-VERR_NET_CONNECTION_ABORTED]                   = -ECONNABORTED,
	[-VERR_NET_CONNECTION_RESET_BY_PEER]             = -ECONNRESET,
	[-VERR_NET_NO_BUFFER_SPACE]                      = -ENOBUFS,
	[-VERR_NET_ALREADY_CONNECTED]                    = -EISCONN,
	[-VERR_NET_NOT_CONNECTED]                        = -ENOTCONN,
	[-VERR_NET_SHUTDOWN]                             = -ESHUTDOWN,
	[-VERR_NET_TOO_MANY_REFERENCES]                  = -ETOOMANYREFS,
	[-VERR_TIMEOUT]                                  = -ETIMEDOUT,
	[-VERR_NET_CONNECTION_REFUSED]                   = -ECONNREFUSED,
	[-VERR_NET_HOST_DOWN]                            = -EHOSTDOWN,
	[-VERR_NET_HOST_UNREACHABLE]                     = -EHOSTUNREACH,
	[-VERR_NET_ALREADY_IN_PROGRESS]                  = -EALREADY,
	[-VERR_NET_IN_PROGRESS]                          = -EINPROGRESS,
	[-VERR_MEDIA_NOT_PRESENT]                        = -ENOMEDIUM,
	[-VERR_MEDIA_NOT_RECOGNIZED]                     = -EMEDIUMTYPE,
पूर्ण;

पूर्णांक vbg_status_code_to_त्रुटि_सं(पूर्णांक rc)
अणु
	अगर (rc >= 0)
		वापस 0;

	rc = -rc;
	अगर (rc >= ARRAY_SIZE(vbg_status_code_to_त्रुटि_सं_table) ||
	    vbg_status_code_to_त्रुटि_सं_table[rc] == 0) अणु
		vbg_warn("%s: Unhandled err %d\n", __func__, -rc);
		वापस -EPROTO;
	पूर्ण

	वापस vbg_status_code_to_त्रुटि_सं_table[rc];
पूर्ण
EXPORT_SYMBOL(vbg_status_code_to_त्रुटि_सं);
