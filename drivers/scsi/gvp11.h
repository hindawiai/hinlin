<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित GVP11_H

/* $Id: gvp11.h,v 1.4 1997/01/19 23:07:12 davem Exp $
 *
 * Header file क्रम the GVP Series II SCSI controller क्रम Linux
 *
 * Written and (C) 1993, Ralf Baechle, see gvp11.c क्रम more info
 * based on a2091.h (C) 1993 by Hamish Macकरोnald
 *
 */

#समावेश <linux/types.h>

#अगर_अघोषित CMD_PER_LUN
#घोषणा CMD_PER_LUN		2
#पूर्ण_अगर

#अगर_अघोषित CAN_QUEUE
#घोषणा CAN_QUEUE		16
#पूर्ण_अगर

/*
 * अगर the transfer address ANDed with this results in a non-zero
 * result, then we can't use DMA.
 */
#घोषणा GVP11_XFER_MASK		(0xff000001)

काष्ठा gvp11_scsiregs अणु
		 अचिन्हित अक्षर	pad1[64];
	अस्थिर अचिन्हित लघु	CNTR;
		 अचिन्हित अक्षर	pad2[31];
	अस्थिर अचिन्हित अक्षर	SASR;
		 अचिन्हित अक्षर	pad3;
	अस्थिर अचिन्हित अक्षर	SCMD;
		 अचिन्हित अक्षर	pad4[4];
	अस्थिर अचिन्हित लघु	BANK;
		 अचिन्हित अक्षर	pad5[6];
	अस्थिर अचिन्हित दीर्घ	ACR;
	अस्थिर अचिन्हित लघु	secret1; /* store 0 here */
	अस्थिर अचिन्हित लघु	ST_DMA;
	अस्थिर अचिन्हित लघु	SP_DMA;
	अस्थिर अचिन्हित लघु	secret2; /* store 1 here */
	अस्थिर अचिन्हित लघु	secret3; /* store 15 here */
पूर्ण;

/* bits in CNTR */
#घोषणा GVP11_DMAC_BUSY		(1<<0)
#घोषणा GVP11_DMAC_INT_PENDING	(1<<1)
#घोषणा GVP11_DMAC_INT_ENABLE	(1<<3)
#घोषणा GVP11_DMAC_सूची_WRITE	(1<<4)

#पूर्ण_अगर /* GVP11_H */
