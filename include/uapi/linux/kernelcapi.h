<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * $Id: kernelcapi.h,v 1.8.6.2 2001/02/07 11:31:31 kai Exp $
 * 
 * Kernel CAPI 2.0 Interface क्रम Linux
 * 
 * (c) Copyright 1997 by Carsten Paeth (calle@calle.in-berlin.de)
 * 
 */

#अगर_अघोषित _UAPI__KERNELCAPI_H__
#घोषणा _UAPI__KERNELCAPI_H__

#घोषणा CAPI_MAXAPPL	240	/* maximum number of applications  */
#घोषणा CAPI_MAXCONTR	32	/* maximum number of controller    */
#घोषणा CAPI_MAXDATAWINDOW	8


प्रकार काष्ठा kcapi_flagdef अणु
	पूर्णांक contr;
	पूर्णांक flag;
पूर्ण kcapi_flagdef;

प्रकार काष्ठा kcapi_carddef अणु
	अक्षर		driver[32];
	अचिन्हित पूर्णांक	port;
	अचिन्हित	irq;
	अचिन्हित पूर्णांक	membase;
	पूर्णांक		cardnr;
पूर्ण kcapi_carddef;

/* new ioctls >= 10 */
#घोषणा KCAPI_CMD_TRACE		10
#घोषणा KCAPI_CMD_ADDCARD	11	/* OBSOLETE */

/* 
 * flag > 2 => trace also data
 * flag & 1 => show trace
 */
#घोषणा KCAPI_TRACE_OFF			0
#घोषणा KCAPI_TRACE_SHORT_NO_DATA	1
#घोषणा KCAPI_TRACE_FULL_NO_DATA	2
#घोषणा KCAPI_TRACE_SHORT		3
#घोषणा KCAPI_TRACE_FULL		4



#पूर्ण_अगर /* _UAPI__KERNELCAPI_H__ */
