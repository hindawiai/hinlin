<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित A3000_H
#घोषणा A3000_H

/* $Id: a3000.h,v 1.4 1997/01/19 23:07:10 davem Exp $
 *
 * Header file क्रम the Amiga 3000 built-in SCSI controller क्रम Linux
 *
 * Written and (C) 1993, Hamish Macकरोnald, see a3000.c क्रम more info
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
#घोषणा A3000_XFER_MASK		(0x00000003)

काष्ठा a3000_scsiregs अणु
		 अचिन्हित अक्षर	pad1[2];
	अस्थिर अचिन्हित लघु	DAWR;
	अस्थिर अचिन्हित पूर्णांक	WTC;
		 अचिन्हित अक्षर	pad2[2];
	अस्थिर अचिन्हित लघु	CNTR;
	अस्थिर अचिन्हित दीर्घ	ACR;
		 अचिन्हित अक्षर	pad3[2];
	अस्थिर अचिन्हित लघु	ST_DMA;
		 अचिन्हित अक्षर	pad4[2];
	अस्थिर अचिन्हित लघु	FLUSH;
		 अचिन्हित अक्षर	pad5[2];
	अस्थिर अचिन्हित लघु	CINT;
		 अचिन्हित अक्षर	pad6[2];
	अस्थिर अचिन्हित लघु	ISTR;
		 अचिन्हित अक्षर	pad7[30];
	अस्थिर अचिन्हित लघु	SP_DMA;
		 अचिन्हित अक्षर	pad8;
	अस्थिर अचिन्हित अक्षर	SASR;
		 अचिन्हित अक्षर	pad9;
	अस्थिर अचिन्हित अक्षर	SCMD;
पूर्ण;

#घोषणा DAWR_A3000		(3)

/* CNTR bits. */
#घोषणा CNTR_TCEN		(1<<5)
#घोषणा CNTR_PREST		(1<<4)
#घोषणा CNTR_PDMD		(1<<3)
#घोषणा CNTR_INTEN		(1<<2)
#घोषणा CNTR_Dसूची		(1<<1)
#घोषणा CNTR_IO_DX		(1<<0)

/* ISTR bits. */
#घोषणा ISTR_INTX		(1<<8)
#घोषणा ISTR_INT_F		(1<<7)
#घोषणा ISTR_INTS		(1<<6)
#घोषणा ISTR_E_INT		(1<<5)
#घोषणा ISTR_INT_P		(1<<4)
#घोषणा ISTR_UE_INT		(1<<3)
#घोषणा ISTR_OE_INT		(1<<2)
#घोषणा ISTR_FF_FLG		(1<<1)
#घोषणा ISTR_FE_FLG		(1<<0)

#पूर्ण_अगर /* A3000_H */
