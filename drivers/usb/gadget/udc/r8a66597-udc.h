<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R8A66597 UDC
 *
 * Copyright (C) 2007-2009 Renesas Solutions Corp.
 *
 * Author : Yoshihiro Shimoda <yoshihiro.shimoda.uh@renesas.com>
 */

#अगर_अघोषित __R8A66597_H__
#घोषणा __R8A66597_H__

#समावेश <linux/clk.h>
#समावेश <linux/usb/r8a66597.h>

#घोषणा R8A66597_MAX_SAMPLING	10

#घोषणा R8A66597_MAX_NUM_PIPE	8
#घोषणा R8A66597_MAX_NUM_BULK	3
#घोषणा R8A66597_MAX_NUM_ISOC	2
#घोषणा R8A66597_MAX_NUM_INT	2

#घोषणा R8A66597_BASE_PIPENUM_BULK	3
#घोषणा R8A66597_BASE_PIPENUM_ISOC	1
#घोषणा R8A66597_BASE_PIPENUM_INT	6

#घोषणा R8A66597_BASE_BUFNUM	6
#घोषणा R8A66597_MAX_BUFNUM	0x4F

#घोषणा is_bulk_pipe(pipक्रमागत)	\
	((pipक्रमागत >= R8A66597_BASE_PIPENUM_BULK) && \
	 (pipक्रमागत < (R8A66597_BASE_PIPENUM_BULK + R8A66597_MAX_NUM_BULK)))
#घोषणा is_पूर्णांकerrupt_pipe(pipक्रमागत)	\
	((pipक्रमागत >= R8A66597_BASE_PIPENUM_INT) && \
	 (pipक्रमागत < (R8A66597_BASE_PIPENUM_INT + R8A66597_MAX_NUM_INT)))
#घोषणा is_isoc_pipe(pipक्रमागत)	\
	((pipक्रमागत >= R8A66597_BASE_PIPENUM_ISOC) && \
	 (pipक्रमागत < (R8A66597_BASE_PIPENUM_ISOC + R8A66597_MAX_NUM_ISOC)))

#घोषणा r8a66597_is_sudmac(r8a66597)	(r8a66597->pdata->sudmac)
काष्ठा r8a66597_pipe_info अणु
	u16	pipe;
	u16	epnum;
	u16	maxpacket;
	u16	type;
	u16	पूर्णांकerval;
	u16	dir_in;
पूर्ण;

काष्ठा r8a66597_request अणु
	काष्ठा usb_request	req;
	काष्ठा list_head	queue;
पूर्ण;

काष्ठा r8a66597_ep अणु
	काष्ठा usb_ep		ep;
	काष्ठा r8a66597		*r8a66597;
	काष्ठा r8a66597_dma	*dma;

	काष्ठा list_head	queue;
	अचिन्हित		busy:1;
	अचिन्हित		wedge:1;
	अचिन्हित		पूर्णांकernal_ccpl:1;	/* use only control */

	/* this member can able to after r8a66597_enable */
	अचिन्हित		use_dma:1;
	u16			pipक्रमागत;
	u16			type;

	/* रेजिस्टर address */
	अचिन्हित अक्षर		fअगरoaddr;
	अचिन्हित अक्षर		fअगरosel;
	अचिन्हित अक्षर		fअगरoctr;
	अचिन्हित अक्षर		pipectr;
	अचिन्हित अक्षर		pipetre;
	अचिन्हित अक्षर		pipetrn;
पूर्ण;

काष्ठा r8a66597_dma अणु
	अचिन्हित		used:1;
	अचिन्हित		dir:1;	/* 1 = IN(ग_लिखो), 0 = OUT(पढ़ो) */
पूर्ण;

काष्ठा r8a66597 अणु
	spinlock_t		lock;
	व्योम __iomem		*reg;
	व्योम __iomem		*sudmac_reg;

	काष्ठा clk *clk;
	काष्ठा r8a66597_platdata	*pdata;

	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;

	काष्ठा r8a66597_ep	ep[R8A66597_MAX_NUM_PIPE];
	काष्ठा r8a66597_ep	*pipक्रमागत2ep[R8A66597_MAX_NUM_PIPE];
	काष्ठा r8a66597_ep	*epaddr2ep[16];
	काष्ठा r8a66597_dma	dma;

	काष्ठा समयr_list	समयr;
	काष्ठा usb_request	*ep0_req;	/* क्रम पूर्णांकernal request */
	u16			ep0_data;	/* क्रम पूर्णांकernal request */
	u16			old_vbus;
	u16			scount;
	u16			old_dvsq;
	u16			device_status;	/* क्रम GET_STATUS */

	/* pipe config */
	अचिन्हित अक्षर bulk;
	अचिन्हित अक्षर पूर्णांकerrupt;
	अचिन्हित अक्षर isochronous;
	अचिन्हित अक्षर num_dma;

	अचिन्हित irq_sense_low:1;
पूर्ण;

#घोषणा gadget_to_r8a66597(_gadget)	\
		container_of(_gadget, काष्ठा r8a66597, gadget)
#घोषणा r8a66597_to_gadget(r8a66597) (&r8a66597->gadget)
#घोषणा r8a66597_to_dev(r8a66597)	(r8a66597->gadget.dev.parent)

अटल अंतरभूत u16 r8a66597_पढ़ो(काष्ठा r8a66597 *r8a66597, अचिन्हित दीर्घ offset)
अणु
	वापस ioपढ़ो16(r8a66597->reg + offset);
पूर्ण

अटल अंतरभूत व्योम r8a66597_पढ़ो_fअगरo(काष्ठा r8a66597 *r8a66597,
				      अचिन्हित दीर्घ offset,
				      अचिन्हित अक्षर *buf,
				      पूर्णांक len)
अणु
	व्योम __iomem *fअगरoaddr = r8a66597->reg + offset;
	अचिन्हित पूर्णांक data = 0;
	पूर्णांक i;

	अगर (r8a66597->pdata->on_chip) अणु
		/* 32-bit accesses क्रम on_chip controllers */

		/* aligned buf हाल */
		अगर (len >= 4 && !((अचिन्हित दीर्घ)buf & 0x03)) अणु
			ioपढ़ो32_rep(fअगरoaddr, buf, len / 4);
			buf += len & ~0x03;
			len &= 0x03;
		पूर्ण

		/* unaligned buf हाल */
		क्रम (i = 0; i < len; i++) अणु
			अगर (!(i & 0x03))
				data = ioपढ़ो32(fअगरoaddr);

			buf[i] = (data >> ((i & 0x03) * 8)) & 0xff;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* 16-bit accesses क्रम बाह्यal controllers */

		/* aligned buf हाल */
		अगर (len >= 2 && !((अचिन्हित दीर्घ)buf & 0x01)) अणु
			ioपढ़ो16_rep(fअगरoaddr, buf, len / 2);
			buf += len & ~0x01;
			len &= 0x01;
		पूर्ण

		/* unaligned buf हाल */
		क्रम (i = 0; i < len; i++) अणु
			अगर (!(i & 0x01))
				data = ioपढ़ो16(fअगरoaddr);

			buf[i] = (data >> ((i & 0x01) * 8)) & 0xff;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम r8a66597_ग_लिखो(काष्ठा r8a66597 *r8a66597, u16 val,
				  अचिन्हित दीर्घ offset)
अणु
	ioग_लिखो16(val, r8a66597->reg + offset);
पूर्ण

अटल अंतरभूत व्योम r8a66597_mdfy(काष्ठा r8a66597 *r8a66597,
				 u16 val, u16 pat, अचिन्हित दीर्घ offset)
अणु
	u16 पंचांगp;
	पंचांगp = r8a66597_पढ़ो(r8a66597, offset);
	पंचांगp = पंचांगp & (~pat);
	पंचांगp = पंचांगp | val;
	r8a66597_ग_लिखो(r8a66597, पंचांगp, offset);
पूर्ण

#घोषणा r8a66597_bclr(r8a66597, val, offset)	\
			r8a66597_mdfy(r8a66597, 0, val, offset)
#घोषणा r8a66597_bset(r8a66597, val, offset)	\
			r8a66597_mdfy(r8a66597, val, 0, offset)

अटल अंतरभूत व्योम r8a66597_ग_लिखो_fअगरo(काष्ठा r8a66597 *r8a66597,
				       काष्ठा r8a66597_ep *ep,
				       अचिन्हित अक्षर *buf,
				       पूर्णांक len)
अणु
	व्योम __iomem *fअगरoaddr = r8a66597->reg + ep->fअगरoaddr;
	पूर्णांक adj = 0;
	पूर्णांक i;

	अगर (r8a66597->pdata->on_chip) अणु
		/* 32-bit access only अगर buf is 32-bit aligned */
		अगर (len >= 4 && !((अचिन्हित दीर्घ)buf & 0x03)) अणु
			ioग_लिखो32_rep(fअगरoaddr, buf, len / 4);
			buf += len & ~0x03;
			len &= 0x03;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* 16-bit access only अगर buf is 16-bit aligned */
		अगर (len >= 2 && !((अचिन्हित दीर्घ)buf & 0x01)) अणु
			ioग_लिखो16_rep(fअगरoaddr, buf, len / 2);
			buf += len & ~0x01;
			len &= 0x01;
		पूर्ण
	पूर्ण

	/* adjust fअगरo address in the little endian हाल */
	अगर (!(r8a66597_पढ़ो(r8a66597, CFIFOSEL) & BIGEND)) अणु
		अगर (r8a66597->pdata->on_chip)
			adj = 0x03; /* 32-bit wide */
		अन्यथा
			adj = 0x01; /* 16-bit wide */
	पूर्ण

	अगर (r8a66597->pdata->wr0_लघुed_to_wr1)
		r8a66597_bclr(r8a66597, MBW_16, ep->fअगरosel);
	क्रम (i = 0; i < len; i++)
		ioग_लिखो8(buf[i], fअगरoaddr + adj - (i & adj));
	अगर (r8a66597->pdata->wr0_लघुed_to_wr1)
		r8a66597_bclr(r8a66597, MBW_16, ep->fअगरosel);
पूर्ण

अटल अंतरभूत u16 get_xtal_from_pdata(काष्ठा r8a66597_platdata *pdata)
अणु
	u16 घड़ी = 0;

	चयन (pdata->xtal) अणु
	हाल R8A66597_PLATDATA_XTAL_12MHZ:
		घड़ी = XTAL12;
		अवरोध;
	हाल R8A66597_PLATDATA_XTAL_24MHZ:
		घड़ी = XTAL24;
		अवरोध;
	हाल R8A66597_PLATDATA_XTAL_48MHZ:
		घड़ी = XTAL48;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "r8a66597: platdata clock is wrong.\n");
		अवरोध;
	पूर्ण

	वापस घड़ी;
पूर्ण

अटल अंतरभूत u32 r8a66597_sudmac_पढ़ो(काष्ठा r8a66597 *r8a66597,
				       अचिन्हित दीर्घ offset)
अणु
	वापस ioपढ़ो32(r8a66597->sudmac_reg + offset);
पूर्ण

अटल अंतरभूत व्योम r8a66597_sudmac_ग_लिखो(काष्ठा r8a66597 *r8a66597, u32 val,
					 अचिन्हित दीर्घ offset)
अणु
	ioग_लिखो32(val, r8a66597->sudmac_reg + offset);
पूर्ण

#घोषणा get_pipectr_addr(pipक्रमागत)	(PIPE1CTR + (pipक्रमागत - 1) * 2)
#घोषणा get_pipetre_addr(pipक्रमागत)	(PIPE1TRE + (pipक्रमागत - 1) * 4)
#घोषणा get_pipetrn_addr(pipक्रमागत)	(PIPE1TRN + (pipक्रमागत - 1) * 4)

#घोषणा enable_irq_पढ़ोy(r8a66597, pipक्रमागत)	\
	enable_pipe_irq(r8a66597, pipक्रमागत, BRDYENB)
#घोषणा disable_irq_पढ़ोy(r8a66597, pipक्रमागत)	\
	disable_pipe_irq(r8a66597, pipक्रमागत, BRDYENB)
#घोषणा enable_irq_empty(r8a66597, pipक्रमागत)	\
	enable_pipe_irq(r8a66597, pipक्रमागत, BEMPENB)
#घोषणा disable_irq_empty(r8a66597, pipक्रमागत)	\
	disable_pipe_irq(r8a66597, pipक्रमागत, BEMPENB)
#घोषणा enable_irq_nrdy(r8a66597, pipक्रमागत)	\
	enable_pipe_irq(r8a66597, pipक्रमागत, NRDYENB)
#घोषणा disable_irq_nrdy(r8a66597, pipक्रमागत)	\
	disable_pipe_irq(r8a66597, pipक्रमागत, NRDYENB)

#पूर्ण_अगर	/* __R8A66597_H__ */

