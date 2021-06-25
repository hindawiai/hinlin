<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * gadget.h - DesignWare USB3 DRD Gadget Header
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#अगर_अघोषित __DRIVERS_USB_DWC3_GADGET_H
#घोषणा __DRIVERS_USB_DWC3_GADGET_H

#समावेश <linux/list.h>
#समावेश <linux/usb/gadget.h>
#समावेश "io.h"

काष्ठा dwc3;
#घोषणा to_dwc3_ep(ep)		(container_of(ep, काष्ठा dwc3_ep, endpoपूर्णांक))
#घोषणा gadget_to_dwc(g)	(dev_get_platdata(&g->dev))

/* DEPCFG parameter 1 */
#घोषणा DWC3_DEPCFG_INT_NUM(n)		(((n) & 0x1f) << 0)
#घोषणा DWC3_DEPCFG_XFER_COMPLETE_EN	BIT(8)
#घोषणा DWC3_DEPCFG_XFER_IN_PROGRESS_EN	BIT(9)
#घोषणा DWC3_DEPCFG_XFER_NOT_READY_EN	BIT(10)
#घोषणा DWC3_DEPCFG_FIFO_ERROR_EN	BIT(11)
#घोषणा DWC3_DEPCFG_STREAM_EVENT_EN	BIT(13)
#घोषणा DWC3_DEPCFG_BINTERVAL_M1(n)	(((n) & 0xff) << 16)
#घोषणा DWC3_DEPCFG_STREAM_CAPABLE	BIT(24)
#घोषणा DWC3_DEPCFG_EP_NUMBER(n)	(((n) & 0x1f) << 25)
#घोषणा DWC3_DEPCFG_BULK_BASED		BIT(30)
#घोषणा DWC3_DEPCFG_FIFO_BASED		BIT(31)

/* DEPCFG parameter 0 */
#घोषणा DWC3_DEPCFG_EP_TYPE(n)		(((n) & 0x3) << 1)
#घोषणा DWC3_DEPCFG_MAX_PACKET_SIZE(n)	(((n) & 0x7ff) << 3)
#घोषणा DWC3_DEPCFG_FIFO_NUMBER(n)	(((n) & 0x1f) << 17)
#घोषणा DWC3_DEPCFG_BURST_SIZE(n)	(((n) & 0xf) << 22)
#घोषणा DWC3_DEPCFG_DATA_SEQ_NUM(n)	((n) << 26)
/* This applies क्रम core versions earlier than 1.94a */
#घोषणा DWC3_DEPCFG_IGN_SEQ_NUM		BIT(31)
/* These apply क्रम core versions 1.94a and later */
#घोषणा DWC3_DEPCFG_ACTION_INIT		(0 << 30)
#घोषणा DWC3_DEPCFG_ACTION_RESTORE	BIT(30)
#घोषणा DWC3_DEPCFG_ACTION_MODIFY	(2 << 30)

/* DEPXFERCFG parameter 0 */
#घोषणा DWC3_DEPXFERCFG_NUM_XFER_RES(n)	((n) & 0xffff)

/* U1 Device निकास Latency */
#घोषणा DWC3_DEFAULT_U1_DEV_EXIT_LAT	0x0A	/* Less then 10 microsec */

/* U2 Device निकास Latency */
#घोषणा DWC3_DEFAULT_U2_DEV_EXIT_LAT	0x1FF	/* Less then 511 microsec */

/* Frame/Microframe Number Mask */
#घोषणा DWC3_FRNUMBER_MASK		0x3fff
/* -------------------------------------------------------------------------- */

#घोषणा to_dwc3_request(r)	(container_of(r, काष्ठा dwc3_request, request))

/**
 * next_request - माला_लो the next request on the given list
 * @list: the request list to operate on
 *
 * Caller should take care of locking. This function वापस %शून्य or the first
 * request available on @list.
 */
अटल अंतरभूत काष्ठा dwc3_request *next_request(काष्ठा list_head *list)
अणु
	वापस list_first_entry_or_null(list, काष्ठा dwc3_request, list);
पूर्ण

/**
 * dwc3_gadget_move_started_request - move @req to the started_list
 * @req: the request to be moved
 *
 * Caller should take care of locking. This function will move @req from its
 * current list to the endpoपूर्णांक's started_list.
 */
अटल अंतरभूत व्योम dwc3_gadget_move_started_request(काष्ठा dwc3_request *req)
अणु
	काष्ठा dwc3_ep		*dep = req->dep;

	req->status = DWC3_REQUEST_STATUS_STARTED;
	list_move_tail(&req->list, &dep->started_list);
पूर्ण

/**
 * dwc3_gadget_move_cancelled_request - move @req to the cancelled_list
 * @req: the request to be moved
 * @reason: cancelled reason क्रम the dwc3 request
 *
 * Caller should take care of locking. This function will move @req from its
 * current list to the endpoपूर्णांक's cancelled_list.
 */
अटल अंतरभूत व्योम dwc3_gadget_move_cancelled_request(काष्ठा dwc3_request *req,
		अचिन्हित पूर्णांक reason)
अणु
	काष्ठा dwc3_ep		*dep = req->dep;

	req->status = reason;
	list_move_tail(&req->list, &dep->cancelled_list);
पूर्ण

व्योम dwc3_gadget_giveback(काष्ठा dwc3_ep *dep, काष्ठा dwc3_request *req,
		पूर्णांक status);

व्योम dwc3_ep0_पूर्णांकerrupt(काष्ठा dwc3 *dwc,
		स्थिर काष्ठा dwc3_event_depevt *event);
व्योम dwc3_ep0_out_start(काष्ठा dwc3 *dwc);
पूर्णांक __dwc3_gadget_ep0_set_halt(काष्ठा usb_ep *ep, पूर्णांक value);
पूर्णांक dwc3_gadget_ep0_set_halt(काष्ठा usb_ep *ep, पूर्णांक value);
पूर्णांक dwc3_gadget_ep0_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *request,
		gfp_t gfp_flags);
पूर्णांक __dwc3_gadget_ep_set_halt(काष्ठा dwc3_ep *dep, पूर्णांक value, पूर्णांक protocol);
व्योम dwc3_ep0_send_delayed_status(काष्ठा dwc3 *dwc);

/**
 * dwc3_gadget_ep_get_transfer_index - Gets transfer index from HW
 * @dep: dwc3 endpoपूर्णांक
 *
 * Caller should take care of locking. Returns the transfer resource
 * index क्रम a given endpoपूर्णांक.
 */
अटल अंतरभूत व्योम dwc3_gadget_ep_get_transfer_index(काष्ठा dwc3_ep *dep)
अणु
	u32			res_id;

	res_id = dwc3_पढ़ोl(dep->regs, DWC3_DEPCMD);
	dep->resource_index = DWC3_DEPCMD_GET_RSC_IDX(res_id);
पूर्ण

/**
 * dwc3_gadget_dctl_ग_लिखो_safe - ग_लिखो to DCTL safe from link state change
 * @dwc: poपूर्णांकer to our context काष्ठाure
 * @value: value to ग_लिखो to DCTL
 *
 * Use this function when करोing पढ़ो-modअगरy-ग_लिखो to DCTL. It will not
 * send link state change request.
 */
अटल अंतरभूत व्योम dwc3_gadget_dctl_ग_लिखो_safe(काष्ठा dwc3 *dwc, u32 value)
अणु
	value &= ~DWC3_DCTL_ULSTCHNGREQ_MASK;
	dwc3_ग_लिखोl(dwc->regs, DWC3_DCTL, value);
पूर्ण

#पूर्ण_अगर /* __DRIVERS_USB_DWC3_GADGET_H */
