<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IBM/3270 Driver - core functions.
 *
 * Author(s):
 *   Original 3270 Code क्रम 2.4 written by Riअक्षरd Hitt (UTS Global)
 *   Rewritten क्रम 2.5 by Martin Schwidefsky <schwidefsky@de.ibm.com>
 *     Copyright IBM Corp. 2003, 2009
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/diag.h>

#समावेश "raw3270.h"

#समावेश <linux/major.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>

काष्ठा class *class3270;

/* The मुख्य 3270 data काष्ठाure. */
काष्ठा raw3270 अणु
	काष्ठा list_head list;
	काष्ठा ccw_device *cdev;
	पूर्णांक minor;

	लघु model, rows, cols;
	अचिन्हित पूर्णांक state;
	अचिन्हित दीर्घ flags;

	काष्ठा list_head req_queue;	/* Request queue. */
	काष्ठा list_head view_list;	/* List of available views. */
	काष्ठा raw3270_view *view;	/* Active view. */

	काष्ठा समयr_list समयr;	/* Device समयr. */

	अचिन्हित अक्षर *ascebc;		/* ascii -> ebcdic table */

	काष्ठा raw3270_view init_view;
	काष्ठा raw3270_request init_reset;
	काष्ठा raw3270_request init_पढ़ोpart;
	काष्ठा raw3270_request init_पढ़ोmod;
	अचिन्हित अक्षर init_data[256];
पूर्ण;

/* raw3270->state */
#घोषणा RAW3270_STATE_INIT	0	/* Initial state */
#घोषणा RAW3270_STATE_RESET	1	/* Reset command is pending */
#घोषणा RAW3270_STATE_W4ATTN	2	/* Wait क्रम attention पूर्णांकerrupt */
#घोषणा RAW3270_STATE_READMOD	3	/* Read partition is pending */
#घोषणा RAW3270_STATE_READY	4	/* Device is usable by views */

/* raw3270->flags */
#घोषणा RAW3270_FLAGS_14BITADDR	0	/* 14-bit buffer addresses */
#घोषणा RAW3270_FLAGS_BUSY	1	/* Device busy, leave it alone */
#घोषणा RAW3270_FLAGS_CONSOLE	2	/* Device is the console. */

/* Semaphore to protect global data of raw3270 (devices, views, etc). */
अटल DEFINE_MUTEX(raw3270_mutex);

/* List of 3270 devices. */
अटल LIST_HEAD(raw3270_devices);

/*
 * Flag to indicate अगर the driver has been रेजिस्टरed. Some operations
 * like रुकोing क्रम the end of i/o need to be करोne dअगरferently as दीर्घ
 * as the kernel is still starting up (console support).
 */
अटल पूर्णांक raw3270_रेजिस्टरed;

/* Module parameters */
अटल bool tubxcorrect;
module_param(tubxcorrect, bool, 0);

/*
 * Wait queue क्रम device init/delete, view delete.
 */
DECLARE_WAIT_QUEUE_HEAD(raw3270_रुको_queue);

अटल व्योम __raw3270_disconnect(काष्ठा raw3270 *rp);

/*
 * Encode array क्रम 12 bit 3270 addresses.
 */
अटल अचिन्हित अक्षर raw3270_ebcgraf[64] =	अणु
	0x40, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
	0xc8, 0xc9, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
	0xd8, 0xd9, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
	0x60, 0x61, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
	0xe8, 0xe9, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
	0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
	0xf8, 0xf9, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f
पूर्ण;

अटल अंतरभूत पूर्णांक raw3270_state_पढ़ोy(काष्ठा raw3270 *rp)
अणु
	वापस rp->state == RAW3270_STATE_READY;
पूर्ण

अटल अंतरभूत पूर्णांक raw3270_state_final(काष्ठा raw3270 *rp)
अणु
	वापस rp->state == RAW3270_STATE_INIT ||
		rp->state == RAW3270_STATE_READY;
पूर्ण

व्योम
raw3270_buffer_address(काष्ठा raw3270 *rp, अक्षर *cp, अचिन्हित लघु addr)
अणु
	अगर (test_bit(RAW3270_FLAGS_14BITADDR, &rp->flags)) अणु
		cp[0] = (addr >> 8) & 0x3f;
		cp[1] = addr & 0xff;
	पूर्ण अन्यथा अणु
		cp[0] = raw3270_ebcgraf[(addr >> 6) & 0x3f];
		cp[1] = raw3270_ebcgraf[addr & 0x3f];
	पूर्ण
पूर्ण

/*
 * Allocate a new 3270 ccw request
 */
काष्ठा raw3270_request *
raw3270_request_alloc(माप_प्रकार size)
अणु
	काष्ठा raw3270_request *rq;

	/* Allocate request काष्ठाure */
	rq = kzalloc(माप(काष्ठा raw3270_request), GFP_KERNEL | GFP_DMA);
	अगर (!rq)
		वापस ERR_PTR(-ENOMEM);

	/* alloc output buffer. */
	अगर (size > 0) अणु
		rq->buffer = kदो_स्मृति(size, GFP_KERNEL | GFP_DMA);
		अगर (!rq->buffer) अणु
			kमुक्त(rq);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण
	rq->size = size;
	INIT_LIST_HEAD(&rq->list);

	/*
	 * Setup ccw.
	 */
	rq->ccw.cda = __pa(rq->buffer);
	rq->ccw.flags = CCW_FLAG_SLI;

	वापस rq;
पूर्ण

/*
 * Free 3270 ccw request
 */
व्योम
raw3270_request_मुक्त (काष्ठा raw3270_request *rq)
अणु
	kमुक्त(rq->buffer);
	kमुक्त(rq);
पूर्ण

/*
 * Reset request to initial state.
 */
व्योम
raw3270_request_reset(काष्ठा raw3270_request *rq)
अणु
	BUG_ON(!list_empty(&rq->list));
	rq->ccw.cmd_code = 0;
	rq->ccw.count = 0;
	rq->ccw.cda = __pa(rq->buffer);
	rq->ccw.flags = CCW_FLAG_SLI;
	rq->rescnt = 0;
	rq->rc = 0;
पूर्ण

/*
 * Set command code to ccw of a request.
 */
व्योम
raw3270_request_set_cmd(काष्ठा raw3270_request *rq, u8 cmd)
अणु
	rq->ccw.cmd_code = cmd;
पूर्ण

/*
 * Add data fragment to output buffer.
 */
पूर्णांक
raw3270_request_add_data(काष्ठा raw3270_request *rq, व्योम *data, माप_प्रकार size)
अणु
	अगर (size + rq->ccw.count > rq->size)
		वापस -E2BIG;
	स_नकल(rq->buffer + rq->ccw.count, data, size);
	rq->ccw.count += size;
	वापस 0;
पूर्ण

/*
 * Set address/length pair to ccw of a request.
 */
व्योम
raw3270_request_set_data(काष्ठा raw3270_request *rq, व्योम *data, माप_प्रकार size)
अणु
	rq->ccw.cda = __pa(data);
	rq->ccw.count = size;
पूर्ण

/*
 * Set idal buffer to ccw of a request.
 */
व्योम
raw3270_request_set_idal(काष्ठा raw3270_request *rq, काष्ठा idal_buffer *ib)
अणु
	rq->ccw.cda = __pa(ib->data);
	rq->ccw.count = ib->size;
	rq->ccw.flags |= CCW_FLAG_IDA;
पूर्ण

/*
 * Add the request to the request queue, try to start it अगर the
 * 3270 device is idle. Return without रुकोing क्रम end of i/o.
 */
अटल पूर्णांक
__raw3270_start(काष्ठा raw3270 *rp, काष्ठा raw3270_view *view,
		काष्ठा raw3270_request *rq)
अणु
	rq->view = view;
	raw3270_get_view(view);
	अगर (list_empty(&rp->req_queue) &&
	    !test_bit(RAW3270_FLAGS_BUSY, &rp->flags)) अणु
		/* No other requests are on the queue. Start this one. */
		rq->rc = ccw_device_start(rp->cdev, &rq->ccw,
					       (अचिन्हित दीर्घ) rq, 0, 0);
		अगर (rq->rc) अणु
			raw3270_put_view(view);
			वापस rq->rc;
		पूर्ण
	पूर्ण
	list_add_tail(&rq->list, &rp->req_queue);
	वापस 0;
पूर्ण

पूर्णांक
raw3270_view_active(काष्ठा raw3270_view *view)
अणु
	काष्ठा raw3270 *rp = view->dev;

	वापस rp && rp->view == view;
पूर्ण

पूर्णांक
raw3270_start(काष्ठा raw3270_view *view, काष्ठा raw3270_request *rq)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा raw3270 *rp;
	पूर्णांक rc;

	spin_lock_irqsave(get_ccwdev_lock(view->dev->cdev), flags);
	rp = view->dev;
	अगर (!rp || rp->view != view)
		rc = -EACCES;
	अन्यथा अगर (!raw3270_state_पढ़ोy(rp))
		rc = -EBUSY;
	अन्यथा
		rc =  __raw3270_start(rp, view, rq);
	spin_unlock_irqrestore(get_ccwdev_lock(view->dev->cdev), flags);
	वापस rc;
पूर्ण

पूर्णांक
raw3270_start_locked(काष्ठा raw3270_view *view, काष्ठा raw3270_request *rq)
अणु
	काष्ठा raw3270 *rp;
	पूर्णांक rc;

	rp = view->dev;
	अगर (!rp || rp->view != view)
		rc = -EACCES;
	अन्यथा अगर (!raw3270_state_पढ़ोy(rp))
		rc = -EBUSY;
	अन्यथा
		rc =  __raw3270_start(rp, view, rq);
	वापस rc;
पूर्ण

पूर्णांक
raw3270_start_irq(काष्ठा raw3270_view *view, काष्ठा raw3270_request *rq)
अणु
	काष्ठा raw3270 *rp;

	rp = view->dev;
	rq->view = view;
	raw3270_get_view(view);
	list_add_tail(&rq->list, &rp->req_queue);
	वापस 0;
पूर्ण

/*
 * 3270 पूर्णांकerrupt routine, called from the ccw_device layer
 */
अटल व्योम
raw3270_irq (काष्ठा ccw_device *cdev, अचिन्हित दीर्घ पूर्णांकparm, काष्ठा irb *irb)
अणु
	काष्ठा raw3270 *rp;
	काष्ठा raw3270_view *view;
	काष्ठा raw3270_request *rq;

	rp = dev_get_drvdata(&cdev->dev);
	अगर (!rp)
		वापस;
	rq = (काष्ठा raw3270_request *) पूर्णांकparm;
	view = rq ? rq->view : rp->view;

	अगर (!IS_ERR(irb)) अणु
		/* Handle CE-DE-UE and subsequent UDE */
		अगर (irb->scsw.cmd.dstat & DEV_STAT_DEV_END)
			clear_bit(RAW3270_FLAGS_BUSY, &rp->flags);
		अगर (irb->scsw.cmd.dstat == (DEV_STAT_CHN_END |
					    DEV_STAT_DEV_END |
					    DEV_STAT_UNIT_EXCEP))
			set_bit(RAW3270_FLAGS_BUSY, &rp->flags);
		/* Handle disconnected devices */
		अगर ((irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) &&
		    (irb->ecw[0] & SNS0_INTERVENTION_REQ)) अणु
			set_bit(RAW3270_FLAGS_BUSY, &rp->flags);
			अगर (rp->state > RAW3270_STATE_RESET)
				__raw3270_disconnect(rp);
		पूर्ण
		/* Call पूर्णांकerrupt handler of the view */
		अगर (view)
			view->fn->पूर्णांकv(view, rq, irb);
	पूर्ण

	अगर (test_bit(RAW3270_FLAGS_BUSY, &rp->flags))
		/* Device busy, करो not start I/O */
		वापस;

	अगर (rq && !list_empty(&rq->list)) अणु
		/* The request completed, हटाओ from queue and करो callback. */
		list_del_init(&rq->list);
		अगर (rq->callback)
			rq->callback(rq, rq->callback_data);
		/* Do put_device क्रम get_device in raw3270_start. */
		raw3270_put_view(view);
	पूर्ण

	/*
	 * Try to start each request on request queue until one is
	 * started successful.
	 */
	जबतक (!list_empty(&rp->req_queue)) अणु
		rq = list_entry(rp->req_queue.next,काष्ठा raw3270_request,list);
		rq->rc = ccw_device_start(rp->cdev, &rq->ccw,
					  (अचिन्हित दीर्घ) rq, 0, 0);
		अगर (rq->rc == 0)
			अवरोध;
		/* Start failed. Remove request and करो callback. */
		list_del_init(&rq->list);
		अगर (rq->callback)
			rq->callback(rq, rq->callback_data);
		/* Do put_device क्रम get_device in raw3270_start. */
		raw3270_put_view(view);
	पूर्ण
पूर्ण

/*
 * To determine the size of the 3270 device we need to करो:
 * 1) send a 'read partition' data stream to the device
 * 2) रुको क्रम the attn पूर्णांकerrupt that precedes the query reply
 * 3) करो a पढ़ो modअगरied to get the query reply
 * To make things worse we have to cope with पूर्णांकervention
 * required (3270 device चयनed to 'stand-by') and command
 * rejects (old devices that can't do 'read partition').
 */
काष्ठा raw3270_ua अणु	/* Query Reply काष्ठाure क्रम Usable Area */
	काष्ठा अणु	/* Usable Area Query Reply Base */
		लघु l;	/* Length of this काष्ठाured field */
		अक्षर  sfid;	/* 0x81 अगर Query Reply */
		अक्षर  qcode;	/* 0x81 अगर Usable Area */
		अक्षर  flags0;
		अक्षर  flags1;
		लघु w;	/* Width of usable area */
		लघु h;	/* Heigth of usavle area */
		अक्षर  units;	/* 0x00:in; 0x01:mm */
		पूर्णांक   xr;
		पूर्णांक   yr;
		अक्षर  aw;
		अक्षर  ah;
		लघु buffsz;	/* Character buffer size, bytes */
		अक्षर  xmin;
		अक्षर  ymin;
		अक्षर  xmax;
		अक्षर  ymax;
	पूर्ण __attribute__ ((packed)) uab;
	काष्ठा अणु	/* Alternate Usable Area Self-Defining Parameter */
		अक्षर  l;	/* Length of this Self-Defining Parm */
		अक्षर  sdpid;	/* 0x02 अगर Alternate Usable Area */
		अक्षर  res;
		अक्षर  auaid;	/* 0x01 is Id क्रम the A U A */
		लघु wauai;	/* Width of AUAi */
		लघु hauai;	/* Height of AUAi */
		अक्षर  auaunits;	/* 0x00:in, 0x01:mm */
		पूर्णांक   auaxr;
		पूर्णांक   auayr;
		अक्षर  awauai;
		अक्षर  ahauai;
	पूर्ण __attribute__ ((packed)) aua;
पूर्ण __attribute__ ((packed));

अटल व्योम
raw3270_size_device_vm(काष्ठा raw3270 *rp)
अणु
	पूर्णांक rc, model;
	काष्ठा ccw_dev_id dev_id;
	काष्ठा diag210 diag_data;

	ccw_device_get_id(rp->cdev, &dev_id);
	diag_data.vrdcdvno = dev_id.devno;
	diag_data.vrdclen = माप(काष्ठा diag210);
	rc = diag210(&diag_data);
	model = diag_data.vrdccrmd;
	/* Use शेष model 2 अगर the size could not be detected */
	अगर (rc || model < 2 || model > 5)
		model = 2;
	चयन (model) अणु
	हाल 2:
		rp->model = model;
		rp->rows = 24;
		rp->cols = 80;
		अवरोध;
	हाल 3:
		rp->model = model;
		rp->rows = 32;
		rp->cols = 80;
		अवरोध;
	हाल 4:
		rp->model = model;
		rp->rows = 43;
		rp->cols = 80;
		अवरोध;
	हाल 5:
		rp->model = model;
		rp->rows = 27;
		rp->cols = 132;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
raw3270_size_device(काष्ठा raw3270 *rp)
अणु
	काष्ठा raw3270_ua *uap;

	/* Got a Query Reply */
	uap = (काष्ठा raw3270_ua *) (rp->init_data + 1);
	/* Paranoia check. */
	अगर (rp->init_पढ़ोmod.rc || rp->init_data[0] != 0x88 ||
	    uap->uab.qcode != 0x81) अणु
		/* Couldn't detect size. Use शेष model 2. */
		rp->model = 2;
		rp->rows = 24;
		rp->cols = 80;
		वापस;
	पूर्ण
	/* Copy rows/columns of शेष Usable Area */
	rp->rows = uap->uab.h;
	rp->cols = uap->uab.w;
	/* Check क्रम 14 bit addressing */
	अगर ((uap->uab.flags0 & 0x0d) == 0x01)
		set_bit(RAW3270_FLAGS_14BITADDR, &rp->flags);
	/* Check क्रम Alternate Usable Area */
	अगर (uap->uab.l == माप(काष्ठा raw3270_ua) &&
	    uap->aua.sdpid == 0x02) अणु
		rp->rows = uap->aua.hauai;
		rp->cols = uap->aua.wauai;
	पूर्ण
	/* Try to find a model. */
	rp->model = 0;
	अगर (rp->rows == 24 && rp->cols == 80)
		rp->model = 2;
	अगर (rp->rows == 32 && rp->cols == 80)
		rp->model = 3;
	अगर (rp->rows == 43 && rp->cols == 80)
		rp->model = 4;
	अगर (rp->rows == 27 && rp->cols == 132)
		rp->model = 5;
पूर्ण

अटल व्योम
raw3270_size_device_करोne(काष्ठा raw3270 *rp)
अणु
	काष्ठा raw3270_view *view;

	rp->view = शून्य;
	rp->state = RAW3270_STATE_READY;
	/* Notअगरy views about new size */
	list_क्रम_each_entry(view, &rp->view_list, list)
		अगर (view->fn->resize)
			view->fn->resize(view, rp->model, rp->rows, rp->cols);
	/* Setup processing करोne, now activate a view */
	list_क्रम_each_entry(view, &rp->view_list, list) अणु
		rp->view = view;
		अगर (view->fn->activate(view) == 0)
			अवरोध;
		rp->view = शून्य;
	पूर्ण
पूर्ण

अटल व्योम
raw3270_पढ़ो_modअगरied_cb(काष्ठा raw3270_request *rq, व्योम *data)
अणु
	काष्ठा raw3270 *rp = rq->view->dev;

	raw3270_size_device(rp);
	raw3270_size_device_करोne(rp);
पूर्ण

अटल व्योम
raw3270_पढ़ो_modअगरied(काष्ठा raw3270 *rp)
अणु
	अगर (rp->state != RAW3270_STATE_W4ATTN)
		वापस;
	/* Use 'read modified' to get the result of a पढ़ो partition. */
	स_रखो(&rp->init_पढ़ोmod, 0, माप(rp->init_पढ़ोmod));
	स_रखो(&rp->init_data, 0, माप(rp->init_data));
	rp->init_पढ़ोmod.ccw.cmd_code = TC_READMOD;
	rp->init_पढ़ोmod.ccw.flags = CCW_FLAG_SLI;
	rp->init_पढ़ोmod.ccw.count = माप(rp->init_data);
	rp->init_पढ़ोmod.ccw.cda = (__u32) __pa(rp->init_data);
	rp->init_पढ़ोmod.callback = raw3270_पढ़ो_modअगरied_cb;
	rp->state = RAW3270_STATE_READMOD;
	raw3270_start_irq(&rp->init_view, &rp->init_पढ़ोmod);
पूर्ण

अटल व्योम
raw3270_ग_लिखोsf_पढ़ोpart(काष्ठा raw3270 *rp)
अणु
	अटल स्थिर अचिन्हित अक्षर wbuf[] =
		अणु 0x00, 0x07, 0x01, 0xff, 0x03, 0x00, 0x81 पूर्ण;

	/* Store 'read partition' data stream to init_data */
	स_रखो(&rp->init_पढ़ोpart, 0, माप(rp->init_पढ़ोpart));
	स_रखो(&rp->init_data, 0, माप(rp->init_data));
	स_नकल(&rp->init_data, wbuf, माप(wbuf));
	rp->init_पढ़ोpart.ccw.cmd_code = TC_WRITESF;
	rp->init_पढ़ोpart.ccw.flags = CCW_FLAG_SLI;
	rp->init_पढ़ोpart.ccw.count = माप(wbuf);
	rp->init_पढ़ोpart.ccw.cda = (__u32) __pa(&rp->init_data);
	rp->state = RAW3270_STATE_W4ATTN;
	raw3270_start_irq(&rp->init_view, &rp->init_पढ़ोpart);
पूर्ण

/*
 * Device reset
 */
अटल व्योम
raw3270_reset_device_cb(काष्ठा raw3270_request *rq, व्योम *data)
अणु
	काष्ठा raw3270 *rp = rq->view->dev;

	अगर (rp->state != RAW3270_STATE_RESET)
		वापस;
	अगर (rq->rc) अणु
		/* Reset command failed. */
		rp->state = RAW3270_STATE_INIT;
	पूर्ण अन्यथा अगर (MACHINE_IS_VM) अणु
		raw3270_size_device_vm(rp);
		raw3270_size_device_करोne(rp);
	पूर्ण अन्यथा
		raw3270_ग_लिखोsf_पढ़ोpart(rp);
	स_रखो(&rp->init_reset, 0, माप(rp->init_reset));
पूर्ण

अटल पूर्णांक
__raw3270_reset_device(काष्ठा raw3270 *rp)
अणु
	पूर्णांक rc;

	/* Check अगर reset is alपढ़ोy pending */
	अगर (rp->init_reset.view)
		वापस -EBUSY;
	/* Store reset data stream to init_data/init_reset */
	rp->init_data[0] = TW_KR;
	rp->init_reset.ccw.cmd_code = TC_EWRITEA;
	rp->init_reset.ccw.flags = CCW_FLAG_SLI;
	rp->init_reset.ccw.count = 1;
	rp->init_reset.ccw.cda = (__u32) __pa(rp->init_data);
	rp->init_reset.callback = raw3270_reset_device_cb;
	rc = __raw3270_start(rp, &rp->init_view, &rp->init_reset);
	अगर (rc == 0 && rp->state == RAW3270_STATE_INIT)
		rp->state = RAW3270_STATE_RESET;
	वापस rc;
पूर्ण

अटल पूर्णांक
raw3270_reset_device(काष्ठा raw3270 *rp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(get_ccwdev_lock(rp->cdev), flags);
	rc = __raw3270_reset_device(rp);
	spin_unlock_irqrestore(get_ccwdev_lock(rp->cdev), flags);
	वापस rc;
पूर्ण

पूर्णांक
raw3270_reset(काष्ठा raw3270_view *view)
अणु
	काष्ठा raw3270 *rp;
	पूर्णांक rc;

	rp = view->dev;
	अगर (!rp || rp->view != view)
		rc = -EACCES;
	अन्यथा अगर (!raw3270_state_पढ़ोy(rp))
		rc = -EBUSY;
	अन्यथा
		rc = raw3270_reset_device(view->dev);
	वापस rc;
पूर्ण

अटल व्योम
__raw3270_disconnect(काष्ठा raw3270 *rp)
अणु
	काष्ठा raw3270_request *rq;
	काष्ठा raw3270_view *view;

	rp->state = RAW3270_STATE_INIT;
	rp->view = &rp->init_view;
	/* Cancel all queued requests */
	जबतक (!list_empty(&rp->req_queue)) अणु
		rq = list_entry(rp->req_queue.next,काष्ठा raw3270_request,list);
		view = rq->view;
		rq->rc = -EACCES;
		list_del_init(&rq->list);
		अगर (rq->callback)
			rq->callback(rq, rq->callback_data);
		raw3270_put_view(view);
	पूर्ण
	/* Start from scratch */
	__raw3270_reset_device(rp);
पूर्ण

अटल व्योम
raw3270_init_irq(काष्ठा raw3270_view *view, काष्ठा raw3270_request *rq,
		 काष्ठा irb *irb)
अणु
	काष्ठा raw3270 *rp;

	अगर (rq) अणु
		अगर (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) अणु
			अगर (irb->ecw[0] & SNS0_CMD_REJECT)
				rq->rc = -EOPNOTSUPP;
			अन्यथा
				rq->rc = -EIO;
		पूर्ण
	पूर्ण
	अगर (irb->scsw.cmd.dstat & DEV_STAT_ATTENTION) अणु
		/* Queue पढ़ो modअगरied after attention पूर्णांकerrupt */
		rp = view->dev;
		raw3270_पढ़ो_modअगरied(rp);
	पूर्ण
पूर्ण

अटल काष्ठा raw3270_fn raw3270_init_fn = अणु
	.पूर्णांकv = raw3270_init_irq
पूर्ण;

/*
 * Setup new 3270 device.
 */
अटल पूर्णांक
raw3270_setup_device(काष्ठा ccw_device *cdev, काष्ठा raw3270 *rp, अक्षर *ascebc)
अणु
	काष्ठा list_head *l;
	काष्ठा raw3270 *पंचांगp;
	पूर्णांक minor;

	स_रखो(rp, 0, माप(काष्ठा raw3270));
	/* Copy ebcdic -> ascii translation table. */
	स_नकल(ascebc, _ascebc, 256);
	अगर (tubxcorrect) अणु
		/* correct brackets and circumflex */
		ascebc['['] = 0xad;
		ascebc[']'] = 0xbd;
		ascebc['^'] = 0xb0;
	पूर्ण
	rp->ascebc = ascebc;

	/* Set शेषs. */
	rp->rows = 24;
	rp->cols = 80;

	INIT_LIST_HEAD(&rp->req_queue);
	INIT_LIST_HEAD(&rp->view_list);

	rp->init_view.dev = rp;
	rp->init_view.fn = &raw3270_init_fn;
	rp->view = &rp->init_view;

	/*
	 * Add device to list and find the smallest unused minor
	 * number क्रम it. Note: there is no device with minor 0,
	 * see special हाल क्रम fs3270.c:fs3270_खोलो().
	 */
	mutex_lock(&raw3270_mutex);
	/* Keep the list sorted. */
	minor = RAW3270_FIRSTMINOR;
	rp->minor = -1;
	list_क्रम_each(l, &raw3270_devices) अणु
		पंचांगp = list_entry(l, काष्ठा raw3270, list);
		अगर (पंचांगp->minor > minor) अणु
			rp->minor = minor;
			__list_add(&rp->list, l->prev, l);
			अवरोध;
		पूर्ण
		minor++;
	पूर्ण
	अगर (rp->minor == -1 && minor < RAW3270_MAXDEVS + RAW3270_FIRSTMINOR) अणु
		rp->minor = minor;
		list_add_tail(&rp->list, &raw3270_devices);
	पूर्ण
	mutex_unlock(&raw3270_mutex);
	/* No मुक्त minor number? Then give up. */
	अगर (rp->minor == -1)
		वापस -EUSERS;
	rp->cdev = cdev;
	dev_set_drvdata(&cdev->dev, rp);
	cdev->handler = raw3270_irq;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_TN3270_CONSOLE
/* Tentative definition - see below क्रम actual definition. */
अटल काष्ठा ccw_driver raw3270_ccw_driver;

/*
 * Setup 3270 device configured as console.
 */
काष्ठा raw3270 __init *raw3270_setup_console(व्योम)
अणु
	काष्ठा ccw_device *cdev;
	अचिन्हित दीर्घ flags;
	काष्ठा raw3270 *rp;
	अक्षर *ascebc;
	पूर्णांक rc;

	cdev = ccw_device_create_console(&raw3270_ccw_driver);
	अगर (IS_ERR(cdev))
		वापस ERR_CAST(cdev);

	rp = kzalloc(माप(काष्ठा raw3270), GFP_KERNEL | GFP_DMA);
	ascebc = kzalloc(256, GFP_KERNEL);
	rc = raw3270_setup_device(cdev, rp, ascebc);
	अगर (rc)
		वापस ERR_PTR(rc);
	set_bit(RAW3270_FLAGS_CONSOLE, &rp->flags);

	rc = ccw_device_enable_console(cdev);
	अगर (rc) अणु
		ccw_device_destroy_console(cdev);
		वापस ERR_PTR(rc);
	पूर्ण

	spin_lock_irqsave(get_ccwdev_lock(rp->cdev), flags);
	करो अणु
		__raw3270_reset_device(rp);
		जबतक (!raw3270_state_final(rp)) अणु
			ccw_device_रुको_idle(rp->cdev);
			barrier();
		पूर्ण
	पूर्ण जबतक (rp->state != RAW3270_STATE_READY);
	spin_unlock_irqrestore(get_ccwdev_lock(rp->cdev), flags);
	वापस rp;
पूर्ण

व्योम
raw3270_रुको_cons_dev(काष्ठा raw3270 *rp)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(get_ccwdev_lock(rp->cdev), flags);
	ccw_device_रुको_idle(rp->cdev);
	spin_unlock_irqrestore(get_ccwdev_lock(rp->cdev), flags);
पूर्ण

#पूर्ण_अगर

/*
 * Create a 3270 device काष्ठाure.
 */
अटल काष्ठा raw3270 *
raw3270_create_device(काष्ठा ccw_device *cdev)
अणु
	काष्ठा raw3270 *rp;
	अक्षर *ascebc;
	पूर्णांक rc;

	rp = kzalloc(माप(काष्ठा raw3270), GFP_KERNEL | GFP_DMA);
	अगर (!rp)
		वापस ERR_PTR(-ENOMEM);
	ascebc = kदो_स्मृति(256, GFP_KERNEL);
	अगर (!ascebc) अणु
		kमुक्त(rp);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	rc = raw3270_setup_device(cdev, rp, ascebc);
	अगर (rc) अणु
		kमुक्त(rp->ascebc);
		kमुक्त(rp);
		rp = ERR_PTR(rc);
	पूर्ण
	/* Get reference to ccw_device काष्ठाure. */
	get_device(&cdev->dev);
	वापस rp;
पूर्ण

/*
 * Activate a view.
 */
पूर्णांक
raw3270_activate_view(काष्ठा raw3270_view *view)
अणु
	काष्ठा raw3270 *rp;
	काष्ठा raw3270_view *oldview, *nv;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	rp = view->dev;
	अगर (!rp)
		वापस -ENODEV;
	spin_lock_irqsave(get_ccwdev_lock(rp->cdev), flags);
	अगर (rp->view == view)
		rc = 0;
	अन्यथा अगर (!raw3270_state_पढ़ोy(rp))
		rc = -EBUSY;
	अन्यथा अणु
		oldview = शून्य;
		अगर (rp->view && rp->view->fn->deactivate) अणु
			oldview = rp->view;
			oldview->fn->deactivate(oldview);
		पूर्ण
		rp->view = view;
		rc = view->fn->activate(view);
		अगर (rc) अणु
			/* Didn't work. Try to reactivate the old view. */
			rp->view = oldview;
			अगर (!oldview || oldview->fn->activate(oldview) != 0) अणु
				/* Didn't work as well. Try any other view. */
				list_क्रम_each_entry(nv, &rp->view_list, list)
					अगर (nv != view && nv != oldview) अणु
						rp->view = nv;
						अगर (nv->fn->activate(nv) == 0)
							अवरोध;
						rp->view = शून्य;
					पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(get_ccwdev_lock(rp->cdev), flags);
	वापस rc;
पूर्ण

/*
 * Deactivate current view.
 */
व्योम
raw3270_deactivate_view(काष्ठा raw3270_view *view)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा raw3270 *rp;

	rp = view->dev;
	अगर (!rp)
		वापस;
	spin_lock_irqsave(get_ccwdev_lock(rp->cdev), flags);
	अगर (rp->view == view) अणु
		view->fn->deactivate(view);
		rp->view = शून्य;
		/* Move deactivated view to end of list. */
		list_del_init(&view->list);
		list_add_tail(&view->list, &rp->view_list);
		/* Try to activate another view. */
		अगर (raw3270_state_पढ़ोy(rp)) अणु
			list_क्रम_each_entry(view, &rp->view_list, list) अणु
				rp->view = view;
				अगर (view->fn->activate(view) == 0)
					अवरोध;
				rp->view = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(get_ccwdev_lock(rp->cdev), flags);
पूर्ण

/*
 * Add view to device with minor "minor".
 */
पूर्णांक
raw3270_add_view(काष्ठा raw3270_view *view, काष्ठा raw3270_fn *fn, पूर्णांक minor, पूर्णांक subclass)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा raw3270 *rp;
	पूर्णांक rc;

	अगर (minor <= 0)
		वापस -ENODEV;
	mutex_lock(&raw3270_mutex);
	rc = -ENODEV;
	list_क्रम_each_entry(rp, &raw3270_devices, list) अणु
		अगर (rp->minor != minor)
			जारी;
		spin_lock_irqsave(get_ccwdev_lock(rp->cdev), flags);
		atomic_set(&view->ref_count, 2);
		view->dev = rp;
		view->fn = fn;
		view->model = rp->model;
		view->rows = rp->rows;
		view->cols = rp->cols;
		view->ascebc = rp->ascebc;
		spin_lock_init(&view->lock);
		lockdep_set_subclass(&view->lock, subclass);
		list_add(&view->list, &rp->view_list);
		rc = 0;
		spin_unlock_irqrestore(get_ccwdev_lock(rp->cdev), flags);
		अवरोध;
	पूर्ण
	mutex_unlock(&raw3270_mutex);
	वापस rc;
पूर्ण

/*
 * Find specअगरic view of device with minor "minor".
 */
काष्ठा raw3270_view *
raw3270_find_view(काष्ठा raw3270_fn *fn, पूर्णांक minor)
अणु
	काष्ठा raw3270 *rp;
	काष्ठा raw3270_view *view, *पंचांगp;
	अचिन्हित दीर्घ flags;

	mutex_lock(&raw3270_mutex);
	view = ERR_PTR(-ENODEV);
	list_क्रम_each_entry(rp, &raw3270_devices, list) अणु
		अगर (rp->minor != minor)
			जारी;
		spin_lock_irqsave(get_ccwdev_lock(rp->cdev), flags);
		list_क्रम_each_entry(पंचांगp, &rp->view_list, list) अणु
			अगर (पंचांगp->fn == fn) अणु
				raw3270_get_view(पंचांगp);
				view = पंचांगp;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(get_ccwdev_lock(rp->cdev), flags);
		अवरोध;
	पूर्ण
	mutex_unlock(&raw3270_mutex);
	वापस view;
पूर्ण

/*
 * Remove view from device and मुक्त view काष्ठाure via call to view->fn->मुक्त.
 */
व्योम
raw3270_del_view(काष्ठा raw3270_view *view)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा raw3270 *rp;
	काष्ठा raw3270_view *nv;

	rp = view->dev;
	spin_lock_irqsave(get_ccwdev_lock(rp->cdev), flags);
	अगर (rp->view == view) अणु
		view->fn->deactivate(view);
		rp->view = शून्य;
	पूर्ण
	list_del_init(&view->list);
	अगर (!rp->view && raw3270_state_पढ़ोy(rp)) अणु
		/* Try to activate another view. */
		list_क्रम_each_entry(nv, &rp->view_list, list) अणु
			अगर (nv->fn->activate(nv) == 0) अणु
				rp->view = nv;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(get_ccwdev_lock(rp->cdev), flags);
	/* Wait क्रम reference counter to drop to zero. */
	atomic_dec(&view->ref_count);
	रुको_event(raw3270_रुको_queue, atomic_पढ़ो(&view->ref_count) == 0);
	अगर (view->fn->मुक्त)
		view->fn->मुक्त(view);
पूर्ण

/*
 * Remove a 3270 device काष्ठाure.
 */
अटल व्योम
raw3270_delete_device(काष्ठा raw3270 *rp)
अणु
	काष्ठा ccw_device *cdev;

	/* Remove from device chain. */
	mutex_lock(&raw3270_mutex);
	list_del_init(&rp->list);
	mutex_unlock(&raw3270_mutex);

	/* Disconnect from ccw_device. */
	cdev = rp->cdev;
	rp->cdev = शून्य;
	dev_set_drvdata(&cdev->dev, शून्य);
	cdev->handler = शून्य;

	/* Put ccw_device काष्ठाure. */
	put_device(&cdev->dev);

	/* Now मुक्त raw3270 काष्ठाure. */
	kमुक्त(rp->ascebc);
	kमुक्त(rp);
पूर्ण

अटल पूर्णांक
raw3270_probe (काष्ठा ccw_device *cdev)
अणु
	वापस 0;
पूर्ण

/*
 * Additional attributes क्रम a 3270 device
 */
अटल sमाप_प्रकार
raw3270_model_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%i\n",
			((काष्ठा raw3270 *) dev_get_drvdata(dev))->model);
पूर्ण
अटल DEVICE_ATTR(model, 0444, raw3270_model_show, शून्य);

अटल sमाप_प्रकार
raw3270_rows_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%i\n",
			((काष्ठा raw3270 *) dev_get_drvdata(dev))->rows);
पूर्ण
अटल DEVICE_ATTR(rows, 0444, raw3270_rows_show, शून्य);

अटल sमाप_प्रकार
raw3270_columns_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%i\n",
			((काष्ठा raw3270 *) dev_get_drvdata(dev))->cols);
पूर्ण
अटल DEVICE_ATTR(columns, 0444, raw3270_columns_show, शून्य);

अटल काष्ठा attribute * raw3270_attrs[] = अणु
	&dev_attr_model.attr,
	&dev_attr_rows.attr,
	&dev_attr_columns.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group raw3270_attr_group = अणु
	.attrs = raw3270_attrs,
पूर्ण;

अटल पूर्णांक raw3270_create_attributes(काष्ठा raw3270 *rp)
अणु
	वापस sysfs_create_group(&rp->cdev->dev.kobj, &raw3270_attr_group);
पूर्ण

/*
 * Notअगरier क्रम device addition/removal
 */
अटल LIST_HEAD(raw3270_notअगरier);

पूर्णांक raw3270_रेजिस्टर_notअगरier(काष्ठा raw3270_notअगरier *notअगरier)
अणु
	काष्ठा raw3270 *rp;

	mutex_lock(&raw3270_mutex);
	list_add_tail(&notअगरier->list, &raw3270_notअगरier);
	list_क्रम_each_entry(rp, &raw3270_devices, list)
		notअगरier->create(rp->minor);
	mutex_unlock(&raw3270_mutex);
	वापस 0;
पूर्ण

व्योम raw3270_unरेजिस्टर_notअगरier(काष्ठा raw3270_notअगरier *notअगरier)
अणु
	काष्ठा raw3270 *rp;

	mutex_lock(&raw3270_mutex);
	list_क्रम_each_entry(rp, &raw3270_devices, list)
		notअगरier->destroy(rp->minor);
	list_del(&notअगरier->list);
	mutex_unlock(&raw3270_mutex);
पूर्ण

/*
 * Set 3270 device online.
 */
अटल पूर्णांक
raw3270_set_online (काष्ठा ccw_device *cdev)
अणु
	काष्ठा raw3270_notअगरier *np;
	काष्ठा raw3270 *rp;
	पूर्णांक rc;

	rp = raw3270_create_device(cdev);
	अगर (IS_ERR(rp))
		वापस PTR_ERR(rp);
	rc = raw3270_create_attributes(rp);
	अगर (rc)
		जाओ failure;
	raw3270_reset_device(rp);
	mutex_lock(&raw3270_mutex);
	list_क्रम_each_entry(np, &raw3270_notअगरier, list)
		np->create(rp->minor);
	mutex_unlock(&raw3270_mutex);
	वापस 0;

failure:
	raw3270_delete_device(rp);
	वापस rc;
पूर्ण

/*
 * Remove 3270 device काष्ठाure.
 */
अटल व्योम
raw3270_हटाओ (काष्ठा ccw_device *cdev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा raw3270 *rp;
	काष्ठा raw3270_view *v;
	काष्ठा raw3270_notअगरier *np;

	rp = dev_get_drvdata(&cdev->dev);
	/*
	 * _हटाओ is the opposite of _probe; it's probe that
	 * should set up rp.  raw3270_हटाओ माला_लो entered क्रम
	 * devices even अगर they haven't been varied online.
	 * Thus, rp may validly be शून्य here.
	 */
	अगर (rp == शून्य)
		वापस;

	sysfs_हटाओ_group(&cdev->dev.kobj, &raw3270_attr_group);

	/* Deactivate current view and हटाओ all views. */
	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	अगर (rp->view) अणु
		अगर (rp->view->fn->deactivate)
			rp->view->fn->deactivate(rp->view);
		rp->view = शून्य;
	पूर्ण
	जबतक (!list_empty(&rp->view_list)) अणु
		v = list_entry(rp->view_list.next, काष्ठा raw3270_view, list);
		अगर (v->fn->release)
			v->fn->release(v);
		spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
		raw3270_del_view(v);
		spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	पूर्ण
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);

	mutex_lock(&raw3270_mutex);
	list_क्रम_each_entry(np, &raw3270_notअगरier, list)
		np->destroy(rp->minor);
	mutex_unlock(&raw3270_mutex);

	/* Reset 3270 device. */
	raw3270_reset_device(rp);
	/* And finally हटाओ it. */
	raw3270_delete_device(rp);
पूर्ण

/*
 * Set 3270 device offline.
 */
अटल पूर्णांक
raw3270_set_offline (काष्ठा ccw_device *cdev)
अणु
	काष्ठा raw3270 *rp;

	rp = dev_get_drvdata(&cdev->dev);
	अगर (test_bit(RAW3270_FLAGS_CONSOLE, &rp->flags))
		वापस -EBUSY;
	raw3270_हटाओ(cdev);
	वापस 0;
पूर्ण

अटल काष्ठा ccw_device_id raw3270_id[] = अणु
	अणु CCW_DEVICE(0x3270, 0) पूर्ण,
	अणु CCW_DEVICE(0x3271, 0) पूर्ण,
	अणु CCW_DEVICE(0x3272, 0) पूर्ण,
	अणु CCW_DEVICE(0x3273, 0) पूर्ण,
	अणु CCW_DEVICE(0x3274, 0) पूर्ण,
	अणु CCW_DEVICE(0x3275, 0) पूर्ण,
	अणु CCW_DEVICE(0x3276, 0) पूर्ण,
	अणु CCW_DEVICE(0x3277, 0) पूर्ण,
	अणु CCW_DEVICE(0x3278, 0) पूर्ण,
	अणु CCW_DEVICE(0x3279, 0) पूर्ण,
	अणु CCW_DEVICE(0x3174, 0) पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

अटल काष्ठा ccw_driver raw3270_ccw_driver = अणु
	.driver = अणु
		.name	= "3270",
		.owner	= THIS_MODULE,
	पूर्ण,
	.ids		= raw3270_id,
	.probe		= &raw3270_probe,
	.हटाओ		= &raw3270_हटाओ,
	.set_online	= &raw3270_set_online,
	.set_offline	= &raw3270_set_offline,
	.पूर्णांक_class	= IRQIO_C70,
पूर्ण;

अटल पूर्णांक
raw3270_init(व्योम)
अणु
	काष्ठा raw3270 *rp;
	पूर्णांक rc;

	अगर (raw3270_रेजिस्टरed)
		वापस 0;
	raw3270_रेजिस्टरed = 1;
	rc = ccw_driver_रेजिस्टर(&raw3270_ccw_driver);
	अगर (rc == 0) अणु
		/* Create attributes क्रम early (= console) device. */
		mutex_lock(&raw3270_mutex);
		class3270 = class_create(THIS_MODULE, "3270");
		list_क्रम_each_entry(rp, &raw3270_devices, list) अणु
			get_device(&rp->cdev->dev);
			raw3270_create_attributes(rp);
		पूर्ण
		mutex_unlock(&raw3270_mutex);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम
raw3270_निकास(व्योम)
अणु
	ccw_driver_unरेजिस्टर(&raw3270_ccw_driver);
	class_destroy(class3270);
पूर्ण

MODULE_LICENSE("GPL");

module_init(raw3270_init);
module_निकास(raw3270_निकास);

EXPORT_SYMBOL(class3270);
EXPORT_SYMBOL(raw3270_request_alloc);
EXPORT_SYMBOL(raw3270_request_मुक्त);
EXPORT_SYMBOL(raw3270_request_reset);
EXPORT_SYMBOL(raw3270_request_set_cmd);
EXPORT_SYMBOL(raw3270_request_add_data);
EXPORT_SYMBOL(raw3270_request_set_data);
EXPORT_SYMBOL(raw3270_request_set_idal);
EXPORT_SYMBOL(raw3270_buffer_address);
EXPORT_SYMBOL(raw3270_add_view);
EXPORT_SYMBOL(raw3270_del_view);
EXPORT_SYMBOL(raw3270_find_view);
EXPORT_SYMBOL(raw3270_activate_view);
EXPORT_SYMBOL(raw3270_deactivate_view);
EXPORT_SYMBOL(raw3270_start);
EXPORT_SYMBOL(raw3270_start_locked);
EXPORT_SYMBOL(raw3270_start_irq);
EXPORT_SYMBOL(raw3270_reset);
EXPORT_SYMBOL(raw3270_रेजिस्टर_notअगरier);
EXPORT_SYMBOL(raw3270_unरेजिस्टर_notअगरier);
EXPORT_SYMBOL(raw3270_रुको_queue);
