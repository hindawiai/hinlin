<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Tracepoपूर्णांक definitions क्रम the s390 zcrypt device driver
 *
 * Copyright IBM Corp. 2016
 * Author(s): Harald Freudenberger <freude@de.ibm.com>
 *
 * Currently there are two tracepoपूर्णांक events defined here.
 * An s390_zcrypt_req request event occurs as soon as the request is
 * recognized by the zcrypt ioctl function. This event may act as some kind
 * of request-processing-starts-now indication.
 * As late as possible within the zcrypt ioctl function there occurs the
 * s390_zcrypt_rep event which may act as the poपूर्णांक in समय where the
 * request has been processed by the kernel and the result is about to be
 * transferred back to userspace.
 * The glue which binds together request and reply event is the ptr
 * parameter, which is the local buffer address where the request from
 * userspace has been stored by the ioctl function.
 *
 * The मुख्य purpose of this zcrypt tracepoपूर्णांक api is to get some data क्रम
 * perक्रमmance measurements together with inक्रमmation about on which card
 * and queue the request has been processed. It is not an ffdc पूर्णांकerface as
 * there is alपढ़ोy code in the zcrypt device driver to serve the s390
 * debug feature पूर्णांकerface.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM s390

#अगर !defined(_TRACE_S390_ZCRYPT_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_S390_ZCRYPT_H

#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा TP_ICARSAMODEXPO  0x0001
#घोषणा TP_ICARSACRT	  0x0002
#घोषणा TB_ZSECSENDCPRB   0x0003
#घोषणा TP_ZSENDEP11CPRB  0x0004
#घोषणा TP_HWRNGCPRB	  0x0005

#घोषणा show_zcrypt_tp_type(type)				\
	__prपूर्णांक_symbolic(type,					\
			 अणु TP_ICARSAMODEXPO, "ICARSAMODEXPO" पूर्ण, \
			 अणु TP_ICARSACRT, "ICARSACRT" पूर्ण,		\
			 अणु TB_ZSECSENDCPRB, "ZSECSENDCPRB" पूर्ण,	\
			 अणु TP_ZSENDEP11CPRB, "ZSENDEP11CPRB" पूर्ण, \
			 अणु TP_HWRNGCPRB, "HWRNGCPRB" पूर्ण)

/**
 * trace_s390_zcrypt_req - zcrypt request tracepoपूर्णांक function
 * @ptr:  Address of the local buffer where the request from userspace
 *	  is stored. Can be used as a unique id to relate together
 *	  request and reply.
 * @type: One of the TP_ defines above.
 *
 * Called when a request from userspace is recognised within the ioctl
 * function of the zcrypt device driver and may act as an entry
 * बारtamp.
 */
TRACE_EVENT(s390_zcrypt_req,
	    TP_PROTO(व्योम *ptr, u32 type),
	    TP_ARGS(ptr, type),
	    TP_STRUCT__entry(
		    __field(व्योम *, ptr)
		    __field(u32, type)),
	    TP_fast_assign(
		    __entry->ptr = ptr;
		    __entry->type = type;),
	    TP_prपूर्णांकk("ptr=%p type=%s",
		      __entry->ptr,
		      show_zcrypt_tp_type(__entry->type))
);

/**
 * trace_s390_zcrypt_rep - zcrypt reply tracepoपूर्णांक function
 * @ptr:  Address of the local buffer where the request from userspace
 *	  is stored. Can be used as a unique id to match together
 *	  request and reply.
 * @fc:   Function code.
 * @rc:   The bare वापसcode as वापसed by the device driver ioctl
 *	  function.
 * @dev:  The adapter nr where this request was actually processed.
 * @करोm:  Doमुख्य id of the device where this request was processed.
 *
 * Called upon recognising the reply from the crypto adapter. This
 * message may act as the निकास बारtamp क्रम the request but also
 * carries some info about on which adapter the request was processed
 * and the वापसcode from the device driver.
 */
TRACE_EVENT(s390_zcrypt_rep,
	    TP_PROTO(व्योम *ptr, u32 fc, u32 rc, u16 dev, u16 करोm),
	    TP_ARGS(ptr, fc, rc, dev, करोm),
	    TP_STRUCT__entry(
		    __field(व्योम *, ptr)
		    __field(u32, fc)
		    __field(u32, rc)
		    __field(u16, device)
		    __field(u16, करोमुख्य)),
	    TP_fast_assign(
		    __entry->ptr = ptr;
		    __entry->fc = fc;
		    __entry->rc = rc;
		    __entry->device = dev;
		    __entry->करोमुख्य = करोm;),
	    TP_prपूर्णांकk("ptr=%p fc=0x%04x rc=%d dev=0x%02hx domain=0x%04hx",
		      __entry->ptr,
		      (अचिन्हित पूर्णांक) __entry->fc,
		      (पूर्णांक) __entry->rc,
		      (अचिन्हित लघु) __entry->device,
		      (अचिन्हित लघु) __entry->करोमुख्य)
);

#पूर्ण_अगर /* _TRACE_S390_ZCRYPT_H */

/* This part must be outside protection */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता

#घोषणा TRACE_INCLUDE_PATH यंत्र/trace
#घोषणा TRACE_INCLUDE_खाता zcrypt

#समावेश <trace/define_trace.h>
