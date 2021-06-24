<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * $Id: kernelcapi.h,v 1.8.6.2 2001/02/07 11:31:31 kai Exp $
 * 
 * Kernel CAPI 2.0 Interface क्रम Linux
 * 
 * (c) Copyright 1997 by Carsten Paeth (calle@calle.in-berlin.de)
 * 
 */
#अगर_अघोषित __KERNELCAPI_H__
#घोषणा __KERNELCAPI_H__

#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/notअगरier.h>
#समावेश <uapi/linux/kernelcapi.h>

#घोषणा CAPI_NOERROR                      0x0000

#घोषणा CAPI_TOOMANYAPPLS		  0x1001
#घोषणा CAPI_LOGBLKSIZETOSMALL	          0x1002
#घोषणा CAPI_BUFFEXECEEDS64K 	          0x1003
#घोषणा CAPI_MSGबफ_मानETOOSMALL	          0x1004
#घोषणा CAPI_ANZLOGCONNNOTSUPPORTED	  0x1005
#घोषणा CAPI_REGRESERVED		  0x1006
#घोषणा CAPI_REGBUSY 		          0x1007
#घोषणा CAPI_REGOSRESOURCEERR	          0x1008
#घोषणा CAPI_REGNOTINSTALLED 	          0x1009
#घोषणा CAPI_REGCTRLERNOTSUPPORTEXTEQUIP  0x100a
#घोषणा CAPI_REGCTRLERONLYSUPPORTEXTEQUIP 0x100b

#घोषणा CAPI_ILLAPPNR		          0x1101
#घोषणा CAPI_ILLCMDORSUBCMDORMSGTOSMALL   0x1102
#घोषणा CAPI_SENDQUEUEFULL		  0x1103
#घोषणा CAPI_RECEIVEQUEUEEMPTY	          0x1104
#घोषणा CAPI_RECEIVEOVERFLOW 	          0x1105
#घोषणा CAPI_UNKNOWNNOTPAR		  0x1106
#घोषणा CAPI_MSGBUSY 		          0x1107
#घोषणा CAPI_MSGOSRESOURCEERR	          0x1108
#घोषणा CAPI_MSGNOTINSTALLED 	          0x1109
#घोषणा CAPI_MSGCTRLERNOTSUPPORTEXTEQUIP  0x110a
#घोषणा CAPI_MSGCTRLERONLYSUPPORTEXTEQUIP 0x110b

#पूर्ण_अगर				/* __KERNELCAPI_H__ */
