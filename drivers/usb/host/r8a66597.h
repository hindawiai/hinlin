<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * R8A66597 HCD (Host Controller Driver)
 *
 * Copyright (C) 2006-2007 Renesas Solutions Corp.
 * Portions Copyright (C) 2004 Psion Teklogix (क्रम NetBook PRO)
 * Portions Copyright (C) 2004-2005 David Brownell
 * Portions Copyright (C) 1999 Roman Weissgaerber
 *
 * Author : Yoshihiro Shimoda <shimoda.yoshihiro@renesas.com>
 */

#अगर_अघोषित __R8A66597_H__
#घोषणा __R8A66597_H__

#समावेश <linux/clk.h>
#समावेश <linux/usb/r8a66597.h>

#घोषणा R8A66597_MAX_NUM_PIPE		10
#घोषणा R8A66597_BUF_BSIZE		8
#घोषणा R8A66597_MAX_DEVICE		10
#घोषणा R8A66597_MAX_ROOT_HUB		2
#घोषणा R8A66597_MAX_SAMPLING		5
#घोषणा R8A66597_RH_POLL_TIME		10
#घोषणा R8A66597_MAX_DMA_CHANNEL	2
#घोषणा R8A66597_PIPE_NO_DMA		R8A66597_MAX_DMA_CHANNEL
#घोषणा check_bulk_or_isoc(pipक्रमागत)	((pipक्रमागत >= 1 && pipक्रमागत <= 5))
#घोषणा check_पूर्णांकerrupt(pipक्रमागत)	((pipक्रमागत >= 6 && pipक्रमागत <= 9))
#घोषणा make_devsel(addr)		(addr << 12)

काष्ठा r8a66597_pipe_info अणु
	अचिन्हित दीर्घ समयr_पूर्णांकerval;
	u16 pipक्रमागत;
	u16 address;	/* R8A66597 HCD usb address */
	u16 epnum;
	u16 maxpacket;
	u16 type;
	u16 bufnum;
	u16 buf_bsize;
	u16 पूर्णांकerval;
	u16 dir_in;
पूर्ण;

काष्ठा r8a66597_pipe अणु
	काष्ठा r8a66597_pipe_info info;

	अचिन्हित दीर्घ fअगरoaddr;
	अचिन्हित दीर्घ fअगरosel;
	अचिन्हित दीर्घ fअगरoctr;
	अचिन्हित दीर्घ pipectr;
	अचिन्हित दीर्घ pipetre;
	अचिन्हित दीर्घ pipetrn;
पूर्ण;

काष्ठा r8a66597_td अणु
	काष्ठा r8a66597_pipe *pipe;
	काष्ठा urb *urb;
	काष्ठा list_head queue;

	u16 type;
	u16 pipक्रमागत;
	पूर्णांक iso_cnt;

	u16 address;		/* R8A66597's USB address */
	u16 maxpacket;

	अचिन्हित zero_packet:1;
	अचिन्हित लघु_packet:1;
	अचिन्हित set_address:1;
पूर्ण;

काष्ठा r8a66597_device अणु
	u16	address;	/* R8A66597's USB address */
	u16	hub_port;
	u16	root_port;

	अचिन्हित लघु ep_in_toggle;
	अचिन्हित लघु ep_out_toggle;
	अचिन्हित अक्षर pipe_cnt[R8A66597_MAX_NUM_PIPE];
	अचिन्हित अक्षर dma_map;

	क्रमागत usb_device_state state;

	काष्ठा usb_device *udev;
	पूर्णांक usb_address;
	काष्ठा list_head device_list;
पूर्ण;

काष्ठा r8a66597_root_hub अणु
	u32 port;
	u16 old_syssts;
	पूर्णांक scount;

	काष्ठा r8a66597_device	*dev;
पूर्ण;

काष्ठा r8a66597;

काष्ठा r8a66597_समयrs अणु
	काष्ठा समयr_list td;
	काष्ठा समयr_list पूर्णांकerval;
	काष्ठा r8a66597 *r8a66597;
पूर्ण;

काष्ठा r8a66597 अणु
	spinlock_t lock;
	व्योम __iomem *reg;
	काष्ठा clk *clk;
	काष्ठा r8a66597_platdata	*pdata;
	काष्ठा r8a66597_device		device0;
	काष्ठा r8a66597_root_hub	root_hub[R8A66597_MAX_ROOT_HUB];
	काष्ठा list_head		pipe_queue[R8A66597_MAX_NUM_PIPE];

	काष्ठा समयr_list rh_समयr;
	काष्ठा r8a66597_समयrs समयrs[R8A66597_MAX_NUM_PIPE];

	अचिन्हित लघु address_map;
	अचिन्हित लघु समयout_map;
	अचिन्हित लघु पूर्णांकerval_map;
	अचिन्हित अक्षर pipe_cnt[R8A66597_MAX_NUM_PIPE];
	अचिन्हित अक्षर dma_map;
	अचिन्हित पूर्णांक max_root_hub;

	काष्ठा list_head child_device;
	अचिन्हित दीर्घ child_connect_map[4];

	अचिन्हित bus_suspended:1;
	अचिन्हित irq_sense_low:1;
पूर्ण;

अटल अंतरभूत काष्ठा r8a66597 *hcd_to_r8a66597(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा r8a66597 *)(hcd->hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *r8a66597_to_hcd(काष्ठा r8a66597 *r8a66597)
अणु
	वापस container_of((व्योम *)r8a66597, काष्ठा usb_hcd, hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा r8a66597_td *r8a66597_get_td(काष्ठा r8a66597 *r8a66597,
						  u16 pipक्रमागत)
अणु
	अगर (unlikely(list_empty(&r8a66597->pipe_queue[pipक्रमागत])))
		वापस शून्य;

	वापस list_entry(r8a66597->pipe_queue[pipक्रमागत].next,
			  काष्ठा r8a66597_td, queue);
पूर्ण

अटल अंतरभूत काष्ठा urb *r8a66597_get_urb(काष्ठा r8a66597 *r8a66597,
					   u16 pipक्रमागत)
अणु
	काष्ठा r8a66597_td *td;

	td = r8a66597_get_td(r8a66597, pipक्रमागत);
	वापस (td ? td->urb : शून्य);
पूर्ण

अटल अंतरभूत u16 r8a66597_पढ़ो(काष्ठा r8a66597 *r8a66597, अचिन्हित दीर्घ offset)
अणु
	वापस ioपढ़ो16(r8a66597->reg + offset);
पूर्ण

अटल अंतरभूत व्योम r8a66597_पढ़ो_fअगरo(काष्ठा r8a66597 *r8a66597,
				      अचिन्हित दीर्घ offset, u16 *buf,
				      पूर्णांक len)
अणु
	व्योम __iomem *fअगरoaddr = r8a66597->reg + offset;
	अचिन्हित दीर्घ count;

	अगर (r8a66597->pdata->on_chip) अणु
		count = len / 4;
		ioपढ़ो32_rep(fअगरoaddr, buf, count);

		अगर (len & 0x00000003) अणु
			अचिन्हित दीर्घ पंचांगp = ioपढ़ो32(fअगरoaddr);
			स_नकल((अचिन्हित अक्षर *)buf + count * 4, &पंचांगp,
			       len & 0x03);
		पूर्ण
	पूर्ण अन्यथा अणु
		len = (len + 1) / 2;
		ioपढ़ो16_rep(fअगरoaddr, buf, len);
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
				       काष्ठा r8a66597_pipe *pipe, u16 *buf,
				       पूर्णांक len)
अणु
	व्योम __iomem *fअगरoaddr = r8a66597->reg + pipe->fअगरoaddr;
	अचिन्हित दीर्घ count;
	अचिन्हित अक्षर *pb;
	पूर्णांक i;

	अगर (r8a66597->pdata->on_chip) अणु
		count = len / 4;
		ioग_लिखो32_rep(fअगरoaddr, buf, count);

		अगर (len & 0x00000003) अणु
			pb = (अचिन्हित अक्षर *)buf + count * 4;
			क्रम (i = 0; i < (len & 0x00000003); i++) अणु
				अगर (r8a66597_पढ़ो(r8a66597, CFIFOSEL) & BIGEND)
					ioग_लिखो8(pb[i], fअगरoaddr + i);
				अन्यथा
					ioग_लिखो8(pb[i], fअगरoaddr + 3 - i);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक odd = len & 0x0001;

		len = len / 2;
		ioग_लिखो16_rep(fअगरoaddr, buf, len);
		अगर (unlikely(odd)) अणु
			buf = &buf[len];
			अगर (r8a66597->pdata->wr0_लघुed_to_wr1)
				r8a66597_bclr(r8a66597, MBW_16, pipe->fअगरosel);
			ioग_लिखो8((अचिन्हित अक्षर)*buf, fअगरoaddr);
			अगर (r8a66597->pdata->wr0_लघुed_to_wr1)
				r8a66597_bset(r8a66597, MBW_16, pipe->fअगरosel);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_syscfg_reg(पूर्णांक port)
अणु
	वापस port == 0 ? SYSCFG0 : SYSCFG1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_syssts_reg(पूर्णांक port)
अणु
	वापस port == 0 ? SYSSTS0 : SYSSTS1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_dvstctr_reg(पूर्णांक port)
अणु
	वापस port == 0 ? DVSTCTR0 : DVSTCTR1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_dmacfg_reg(पूर्णांक port)
अणु
	वापस port == 0 ? DMA0CFG : DMA1CFG;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_पूर्णांकenb_reg(पूर्णांक port)
अणु
	वापस port == 0 ? INTENB1 : INTENB2;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_पूर्णांकsts_reg(पूर्णांक port)
अणु
	वापस port == 0 ? INTSTS1 : INTSTS2;
पूर्ण

अटल अंतरभूत u16 get_rh_usb_speed(काष्ठा r8a66597 *r8a66597, पूर्णांक port)
अणु
	अचिन्हित दीर्घ dvstctr_reg = get_dvstctr_reg(port);

	वापस r8a66597_पढ़ो(r8a66597, dvstctr_reg) & RHST;
पूर्ण

अटल अंतरभूत व्योम r8a66597_port_घातer(काष्ठा r8a66597 *r8a66597, पूर्णांक port,
				       पूर्णांक घातer)
अणु
	अचिन्हित दीर्घ dvstctr_reg = get_dvstctr_reg(port);

	अगर (r8a66597->pdata->port_घातer) अणु
		r8a66597->pdata->port_घातer(port, घातer);
	पूर्ण अन्यथा अणु
		अगर (घातer)
			r8a66597_bset(r8a66597, VBOUT, dvstctr_reg);
		अन्यथा
			r8a66597_bclr(r8a66597, VBOUT, dvstctr_reg);
	पूर्ण
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

#घोषणा get_pipectr_addr(pipक्रमागत)	(PIPE1CTR + (pipक्रमागत - 1) * 2)
#घोषणा get_pipetre_addr(pipक्रमागत)	(PIPE1TRE + (pipक्रमागत - 1) * 4)
#घोषणा get_pipetrn_addr(pipक्रमागत)	(PIPE1TRN + (pipक्रमागत - 1) * 4)
#घोषणा get_devadd_addr(address)	(DEVADD0 + address * 2)

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

