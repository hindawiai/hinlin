<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R8A66597 UDC (USB gadget)
 *
 * Copyright (C) 2006-2009 Renesas Solutions Corp.
 *
 * Author : Yoshihiro Shimoda <yoshihiro.shimoda.uh@renesas.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>

#समावेश "r8a66597-udc.h"

#घोषणा DRIVER_VERSION	"2011-09-26"

अटल स्थिर अक्षर udc_name[] = "r8a66597_udc";
अटल स्थिर अक्षर *r8a66597_ep_name[] = अणु
	"ep0", "ep1", "ep2", "ep3", "ep4", "ep5", "ep6", "ep7",
	"ep8", "ep9",
पूर्ण;

अटल व्योम init_controller(काष्ठा r8a66597 *r8a66597);
अटल व्योम disable_controller(काष्ठा r8a66597 *r8a66597);
अटल व्योम irq_ep0_ग_लिखो(काष्ठा r8a66597_ep *ep, काष्ठा r8a66597_request *req);
अटल व्योम irq_packet_ग_लिखो(काष्ठा r8a66597_ep *ep,
				काष्ठा r8a66597_request *req);
अटल पूर्णांक r8a66597_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
			gfp_t gfp_flags);

अटल व्योम transfer_complete(काष्ठा r8a66597_ep *ep,
		काष्ठा r8a66597_request *req, पूर्णांक status);

/*-------------------------------------------------------------------------*/
अटल अंतरभूत u16 get_usb_speed(काष्ठा r8a66597 *r8a66597)
अणु
	वापस r8a66597_पढ़ो(r8a66597, DVSTCTR0) & RHST;
पूर्ण

अटल व्योम enable_pipe_irq(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत,
		अचिन्हित दीर्घ reg)
अणु
	u16 पंचांगp;

	पंचांगp = r8a66597_पढ़ो(r8a66597, INTENB0);
	r8a66597_bclr(r8a66597, BEMPE | NRDYE | BRDYE,
			INTENB0);
	r8a66597_bset(r8a66597, (1 << pipक्रमागत), reg);
	r8a66597_ग_लिखो(r8a66597, पंचांगp, INTENB0);
पूर्ण

अटल व्योम disable_pipe_irq(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत,
		अचिन्हित दीर्घ reg)
अणु
	u16 पंचांगp;

	पंचांगp = r8a66597_पढ़ो(r8a66597, INTENB0);
	r8a66597_bclr(r8a66597, BEMPE | NRDYE | BRDYE,
			INTENB0);
	r8a66597_bclr(r8a66597, (1 << pipक्रमागत), reg);
	r8a66597_ग_लिखो(r8a66597, पंचांगp, INTENB0);
पूर्ण

अटल व्योम r8a66597_usb_connect(काष्ठा r8a66597 *r8a66597)
अणु
	r8a66597_bset(r8a66597, CTRE, INTENB0);
	r8a66597_bset(r8a66597, BEMPE | BRDYE, INTENB0);

	r8a66597_bset(r8a66597, DPRPU, SYSCFG0);
पूर्ण

अटल व्योम r8a66597_usb_disconnect(काष्ठा r8a66597 *r8a66597)
__releases(r8a66597->lock)
__acquires(r8a66597->lock)
अणु
	r8a66597_bclr(r8a66597, CTRE, INTENB0);
	r8a66597_bclr(r8a66597, BEMPE | BRDYE, INTENB0);
	r8a66597_bclr(r8a66597, DPRPU, SYSCFG0);

	r8a66597->gadget.speed = USB_SPEED_UNKNOWN;
	spin_unlock(&r8a66597->lock);
	r8a66597->driver->disconnect(&r8a66597->gadget);
	spin_lock(&r8a66597->lock);

	disable_controller(r8a66597);
	init_controller(r8a66597);
	r8a66597_bset(r8a66597, VBSE, INTENB0);
	INIT_LIST_HEAD(&r8a66597->ep[0].queue);
पूर्ण

अटल अंतरभूत u16 control_reg_get_pid(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	u16 pid = 0;
	अचिन्हित दीर्घ offset;

	अगर (pipक्रमागत == 0) अणु
		pid = r8a66597_पढ़ो(r8a66597, DCPCTR) & PID;
	पूर्ण अन्यथा अगर (pipक्रमागत < R8A66597_MAX_NUM_PIPE) अणु
		offset = get_pipectr_addr(pipक्रमागत);
		pid = r8a66597_पढ़ो(r8a66597, offset) & PID;
	पूर्ण अन्यथा अणु
		dev_err(r8a66597_to_dev(r8a66597), "unexpect pipe num (%d)\n",
			pipक्रमागत);
	पूर्ण

	वापस pid;
पूर्ण

अटल अंतरभूत व्योम control_reg_set_pid(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत,
		u16 pid)
अणु
	अचिन्हित दीर्घ offset;

	अगर (pipक्रमागत == 0) अणु
		r8a66597_mdfy(r8a66597, pid, PID, DCPCTR);
	पूर्ण अन्यथा अगर (pipक्रमागत < R8A66597_MAX_NUM_PIPE) अणु
		offset = get_pipectr_addr(pipक्रमागत);
		r8a66597_mdfy(r8a66597, pid, PID, offset);
	पूर्ण अन्यथा अणु
		dev_err(r8a66597_to_dev(r8a66597), "unexpect pipe num (%d)\n",
			pipक्रमागत);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pipe_start(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	control_reg_set_pid(r8a66597, pipक्रमागत, PID_BUF);
पूर्ण

अटल अंतरभूत व्योम pipe_stop(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	control_reg_set_pid(r8a66597, pipक्रमागत, PID_NAK);
पूर्ण

अटल अंतरभूत व्योम pipe_stall(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	control_reg_set_pid(r8a66597, pipक्रमागत, PID_STALL);
पूर्ण

अटल अंतरभूत u16 control_reg_get(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	u16 ret = 0;
	अचिन्हित दीर्घ offset;

	अगर (pipक्रमागत == 0) अणु
		ret = r8a66597_पढ़ो(r8a66597, DCPCTR);
	पूर्ण अन्यथा अगर (pipक्रमागत < R8A66597_MAX_NUM_PIPE) अणु
		offset = get_pipectr_addr(pipक्रमागत);
		ret = r8a66597_पढ़ो(r8a66597, offset);
	पूर्ण अन्यथा अणु
		dev_err(r8a66597_to_dev(r8a66597), "unexpect pipe num (%d)\n",
			pipक्रमागत);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम control_reg_sqclr(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	अचिन्हित दीर्घ offset;

	pipe_stop(r8a66597, pipक्रमागत);

	अगर (pipक्रमागत == 0) अणु
		r8a66597_bset(r8a66597, SQCLR, DCPCTR);
	पूर्ण अन्यथा अगर (pipक्रमागत < R8A66597_MAX_NUM_PIPE) अणु
		offset = get_pipectr_addr(pipक्रमागत);
		r8a66597_bset(r8a66597, SQCLR, offset);
	पूर्ण अन्यथा अणु
		dev_err(r8a66597_to_dev(r8a66597), "unexpect pipe num (%d)\n",
			pipक्रमागत);
	पूर्ण
पूर्ण

अटल व्योम control_reg_sqset(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	अचिन्हित दीर्घ offset;

	pipe_stop(r8a66597, pipक्रमागत);

	अगर (pipक्रमागत == 0) अणु
		r8a66597_bset(r8a66597, SQSET, DCPCTR);
	पूर्ण अन्यथा अगर (pipक्रमागत < R8A66597_MAX_NUM_PIPE) अणु
		offset = get_pipectr_addr(pipक्रमागत);
		r8a66597_bset(r8a66597, SQSET, offset);
	पूर्ण अन्यथा अणु
		dev_err(r8a66597_to_dev(r8a66597),
			"unexpect pipe num(%d)\n", pipक्रमागत);
	पूर्ण
पूर्ण

अटल u16 control_reg_sqmon(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	अचिन्हित दीर्घ offset;

	अगर (pipक्रमागत == 0) अणु
		वापस r8a66597_पढ़ो(r8a66597, DCPCTR) & SQMON;
	पूर्ण अन्यथा अगर (pipक्रमागत < R8A66597_MAX_NUM_PIPE) अणु
		offset = get_pipectr_addr(pipक्रमागत);
		वापस r8a66597_पढ़ो(r8a66597, offset) & SQMON;
	पूर्ण अन्यथा अणु
		dev_err(r8a66597_to_dev(r8a66597),
			"unexpect pipe num(%d)\n", pipक्रमागत);
	पूर्ण

	वापस 0;
पूर्ण

अटल u16 save_usb_toggle(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	वापस control_reg_sqmon(r8a66597, pipक्रमागत);
पूर्ण

अटल व्योम restore_usb_toggle(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत,
			       u16 toggle)
अणु
	अगर (toggle)
		control_reg_sqset(r8a66597, pipक्रमागत);
	अन्यथा
		control_reg_sqclr(r8a66597, pipक्रमागत);
पूर्ण

अटल अंतरभूत पूर्णांक get_buffer_size(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	u16 पंचांगp;
	पूर्णांक size;

	अगर (pipक्रमागत == 0) अणु
		पंचांगp = r8a66597_पढ़ो(r8a66597, DCPCFG);
		अगर ((पंचांगp & R8A66597_CNTMD) != 0)
			size = 256;
		अन्यथा अणु
			पंचांगp = r8a66597_पढ़ो(r8a66597, DCPMAXP);
			size = पंचांगp & MAXP;
		पूर्ण
	पूर्ण अन्यथा अणु
		r8a66597_ग_लिखो(r8a66597, pipक्रमागत, PIPESEL);
		पंचांगp = r8a66597_पढ़ो(r8a66597, PIPECFG);
		अगर ((पंचांगp & R8A66597_CNTMD) != 0) अणु
			पंचांगp = r8a66597_पढ़ो(r8a66597, PIPEBUF);
			size = ((पंचांगp >> 10) + 1) * 64;
		पूर्ण अन्यथा अणु
			पंचांगp = r8a66597_पढ़ो(r8a66597, PIPEMAXP);
			size = पंचांगp & MXPS;
		पूर्ण
	पूर्ण

	वापस size;
पूर्ण

अटल अंतरभूत अचिन्हित लघु mbw_value(काष्ठा r8a66597 *r8a66597)
अणु
	अगर (r8a66597->pdata->on_chip)
		वापस MBW_32;
	अन्यथा
		वापस MBW_16;
पूर्ण

अटल व्योम r8a66597_change_curpipe(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत,
				    u16 isel, u16 fअगरosel)
अणु
	u16 पंचांगp, mask, loop;
	पूर्णांक i = 0;

	अगर (!pipक्रमागत) अणु
		mask = ISEL | CURPIPE;
		loop = isel;
	पूर्ण अन्यथा अणु
		mask = CURPIPE;
		loop = pipक्रमागत;
	पूर्ण
	r8a66597_mdfy(r8a66597, loop, mask, fअगरosel);

	करो अणु
		पंचांगp = r8a66597_पढ़ो(r8a66597, fअगरosel);
		अगर (i++ > 1000000) अणु
			dev_err(r8a66597_to_dev(r8a66597),
				"r8a66597: register%x, loop %x "
				"is timeout\n", fअगरosel, loop);
			अवरोध;
		पूर्ण
		ndelay(1);
	पूर्ण जबतक ((पंचांगp & mask) != loop);
पूर्ण

अटल व्योम pipe_change(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	काष्ठा r8a66597_ep *ep = r8a66597->pipक्रमागत2ep[pipक्रमागत];

	अगर (ep->use_dma)
		r8a66597_bclr(r8a66597, DREQE, ep->fअगरosel);

	r8a66597_mdfy(r8a66597, pipक्रमागत, CURPIPE, ep->fअगरosel);

	ndelay(450);

	अगर (r8a66597_is_sudmac(r8a66597) && ep->use_dma)
		r8a66597_bclr(r8a66597, mbw_value(r8a66597), ep->fअगरosel);
	अन्यथा
		r8a66597_bset(r8a66597, mbw_value(r8a66597), ep->fअगरosel);

	अगर (ep->use_dma)
		r8a66597_bset(r8a66597, DREQE, ep->fअगरosel);
पूर्ण

अटल पूर्णांक pipe_buffer_setting(काष्ठा r8a66597 *r8a66597,
		काष्ठा r8a66597_pipe_info *info)
अणु
	u16 bufnum = 0, buf_bsize = 0;
	u16 pipecfg = 0;

	अगर (info->pipe == 0)
		वापस -EINVAL;

	r8a66597_ग_लिखो(r8a66597, info->pipe, PIPESEL);

	अगर (info->dir_in)
		pipecfg |= R8A66597_सूची;
	pipecfg |= info->type;
	pipecfg |= info->epnum;
	चयन (info->type) अणु
	हाल R8A66597_INT:
		bufnum = 4 + (info->pipe - R8A66597_BASE_PIPENUM_INT);
		buf_bsize = 0;
		अवरोध;
	हाल R8A66597_BULK:
		/* isochronous pipes may be used as bulk pipes */
		अगर (info->pipe >= R8A66597_BASE_PIPENUM_BULK)
			bufnum = info->pipe - R8A66597_BASE_PIPENUM_BULK;
		अन्यथा
			bufnum = info->pipe - R8A66597_BASE_PIPENUM_ISOC;

		bufnum = R8A66597_BASE_BUFNUM + (bufnum * 16);
		buf_bsize = 7;
		pipecfg |= R8A66597_DBLB;
		अगर (!info->dir_in)
			pipecfg |= R8A66597_SHTNAK;
		अवरोध;
	हाल R8A66597_ISO:
		bufnum = R8A66597_BASE_BUFNUM +
			 (info->pipe - R8A66597_BASE_PIPENUM_ISOC) * 16;
		buf_bsize = 7;
		अवरोध;
	पूर्ण

	अगर (buf_bsize && ((bufnum + 16) >= R8A66597_MAX_BUFNUM)) अणु
		pr_err("r8a66597 pipe memory is insufficient\n");
		वापस -ENOMEM;
	पूर्ण

	r8a66597_ग_लिखो(r8a66597, pipecfg, PIPECFG);
	r8a66597_ग_लिखो(r8a66597, (buf_bsize << 10) | (bufnum), PIPEBUF);
	r8a66597_ग_लिखो(r8a66597, info->maxpacket, PIPEMAXP);
	अगर (info->पूर्णांकerval)
		info->पूर्णांकerval--;
	r8a66597_ग_लिखो(r8a66597, info->पूर्णांकerval, PIPEPERI);

	वापस 0;
पूर्ण

अटल व्योम pipe_buffer_release(काष्ठा r8a66597 *r8a66597,
				काष्ठा r8a66597_pipe_info *info)
अणु
	अगर (info->pipe == 0)
		वापस;

	अगर (is_bulk_pipe(info->pipe)) अणु
		r8a66597->bulk--;
	पूर्ण अन्यथा अगर (is_पूर्णांकerrupt_pipe(info->pipe)) अणु
		r8a66597->पूर्णांकerrupt--;
	पूर्ण अन्यथा अगर (is_isoc_pipe(info->pipe)) अणु
		r8a66597->isochronous--;
		अगर (info->type == R8A66597_BULK)
			r8a66597->bulk--;
	पूर्ण अन्यथा अणु
		dev_err(r8a66597_to_dev(r8a66597),
			"ep_release: unexpect pipenum (%d)\n", info->pipe);
	पूर्ण
पूर्ण

अटल व्योम pipe_initialize(काष्ठा r8a66597_ep *ep)
अणु
	काष्ठा r8a66597 *r8a66597 = ep->r8a66597;

	r8a66597_mdfy(r8a66597, 0, CURPIPE, ep->fअगरosel);

	r8a66597_ग_लिखो(r8a66597, ACLRM, ep->pipectr);
	r8a66597_ग_लिखो(r8a66597, 0, ep->pipectr);
	r8a66597_ग_लिखो(r8a66597, SQCLR, ep->pipectr);
	अगर (ep->use_dma) अणु
		r8a66597_mdfy(r8a66597, ep->pipक्रमागत, CURPIPE, ep->fअगरosel);

		ndelay(450);

		r8a66597_bset(r8a66597, mbw_value(r8a66597), ep->fअगरosel);
	पूर्ण
पूर्ण

अटल व्योम r8a66597_ep_setting(काष्ठा r8a66597 *r8a66597,
				काष्ठा r8a66597_ep *ep,
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc,
				u16 pipक्रमागत, पूर्णांक dma)
अणु
	ep->use_dma = 0;
	ep->fअगरoaddr = CFIFO;
	ep->fअगरosel = CFIFOSEL;
	ep->fअगरoctr = CFIFOCTR;

	ep->pipectr = get_pipectr_addr(pipक्रमागत);
	अगर (is_bulk_pipe(pipक्रमागत) || is_isoc_pipe(pipक्रमागत)) अणु
		ep->pipetre = get_pipetre_addr(pipक्रमागत);
		ep->pipetrn = get_pipetrn_addr(pipक्रमागत);
	पूर्ण अन्यथा अणु
		ep->pipetre = 0;
		ep->pipetrn = 0;
	पूर्ण
	ep->pipक्रमागत = pipक्रमागत;
	ep->ep.maxpacket = usb_endpoपूर्णांक_maxp(desc);
	r8a66597->pipक्रमागत2ep[pipक्रमागत] = ep;
	r8a66597->epaddr2ep[usb_endpoपूर्णांक_num(desc)]
		= ep;
	INIT_LIST_HEAD(&ep->queue);
पूर्ण

अटल व्योम r8a66597_ep_release(काष्ठा r8a66597_ep *ep)
अणु
	काष्ठा r8a66597 *r8a66597 = ep->r8a66597;
	u16 pipक्रमागत = ep->pipक्रमागत;

	अगर (pipक्रमागत == 0)
		वापस;

	अगर (ep->use_dma)
		r8a66597->num_dma--;
	ep->pipक्रमागत = 0;
	ep->busy = 0;
	ep->use_dma = 0;
पूर्ण

अटल पूर्णांक alloc_pipe_config(काष्ठा r8a66597_ep *ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा r8a66597 *r8a66597 = ep->r8a66597;
	काष्ठा r8a66597_pipe_info info;
	पूर्णांक dma = 0;
	अचिन्हित अक्षर *counter;
	पूर्णांक ret;

	ep->ep.desc = desc;

	अगर (ep->pipक्रमागत)	/* alपढ़ोy allocated pipe  */
		वापस 0;

	चयन (usb_endpoपूर्णांक_type(desc)) अणु
	हाल USB_ENDPOINT_XFER_BULK:
		अगर (r8a66597->bulk >= R8A66597_MAX_NUM_BULK) अणु
			अगर (r8a66597->isochronous >= R8A66597_MAX_NUM_ISOC) अणु
				dev_err(r8a66597_to_dev(r8a66597),
					"bulk pipe is insufficient\n");
				वापस -ENODEV;
			पूर्ण अन्यथा अणु
				info.pipe = R8A66597_BASE_PIPENUM_ISOC
						+ r8a66597->isochronous;
				counter = &r8a66597->isochronous;
			पूर्ण
		पूर्ण अन्यथा अणु
			info.pipe = R8A66597_BASE_PIPENUM_BULK + r8a66597->bulk;
			counter = &r8a66597->bulk;
		पूर्ण
		info.type = R8A66597_BULK;
		dma = 1;
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		अगर (r8a66597->पूर्णांकerrupt >= R8A66597_MAX_NUM_INT) अणु
			dev_err(r8a66597_to_dev(r8a66597),
				"interrupt pipe is insufficient\n");
			वापस -ENODEV;
		पूर्ण
		info.pipe = R8A66597_BASE_PIPENUM_INT + r8a66597->पूर्णांकerrupt;
		info.type = R8A66597_INT;
		counter = &r8a66597->पूर्णांकerrupt;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (r8a66597->isochronous >= R8A66597_MAX_NUM_ISOC) अणु
			dev_err(r8a66597_to_dev(r8a66597),
				"isochronous pipe is insufficient\n");
			वापस -ENODEV;
		पूर्ण
		info.pipe = R8A66597_BASE_PIPENUM_ISOC + r8a66597->isochronous;
		info.type = R8A66597_ISO;
		counter = &r8a66597->isochronous;
		अवरोध;
	शेष:
		dev_err(r8a66597_to_dev(r8a66597), "unexpect xfer type\n");
		वापस -EINVAL;
	पूर्ण
	ep->type = info.type;

	info.epnum = usb_endpoपूर्णांक_num(desc);
	info.maxpacket = usb_endpoपूर्णांक_maxp(desc);
	info.पूर्णांकerval = desc->bInterval;
	अगर (desc->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK)
		info.dir_in = 1;
	अन्यथा
		info.dir_in = 0;

	ret = pipe_buffer_setting(r8a66597, &info);
	अगर (ret < 0) अणु
		dev_err(r8a66597_to_dev(r8a66597),
			"pipe_buffer_setting fail\n");
		वापस ret;
	पूर्ण

	(*counter)++;
	अगर ((counter == &r8a66597->isochronous) && info.type == R8A66597_BULK)
		r8a66597->bulk++;

	r8a66597_ep_setting(r8a66597, ep, desc, info.pipe, dma);
	pipe_initialize(ep);

	वापस 0;
पूर्ण

अटल पूर्णांक मुक्त_pipe_config(काष्ठा r8a66597_ep *ep)
अणु
	काष्ठा r8a66597 *r8a66597 = ep->r8a66597;
	काष्ठा r8a66597_pipe_info info;

	info.pipe = ep->pipक्रमागत;
	info.type = ep->type;
	pipe_buffer_release(r8a66597, &info);
	r8a66597_ep_release(ep);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम pipe_irq_enable(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	enable_irq_पढ़ोy(r8a66597, pipक्रमागत);
	enable_irq_nrdy(r8a66597, pipक्रमागत);
पूर्ण

अटल व्योम pipe_irq_disable(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	disable_irq_पढ़ोy(r8a66597, pipक्रमागत);
	disable_irq_nrdy(r8a66597, pipक्रमागत);
पूर्ण

/* अगर complete is true, gadget driver complete function is not call */
अटल व्योम control_end(काष्ठा r8a66597 *r8a66597, अचिन्हित ccpl)
अणु
	r8a66597->ep[0].पूर्णांकernal_ccpl = ccpl;
	pipe_start(r8a66597, 0);
	r8a66597_bset(r8a66597, CCPL, DCPCTR);
पूर्ण

अटल व्योम start_ep0_ग_लिखो(काष्ठा r8a66597_ep *ep,
				काष्ठा r8a66597_request *req)
अणु
	काष्ठा r8a66597 *r8a66597 = ep->r8a66597;

	pipe_change(r8a66597, ep->pipक्रमागत);
	r8a66597_mdfy(r8a66597, ISEL, (ISEL | CURPIPE), CFIFOSEL);
	r8a66597_ग_लिखो(r8a66597, BCLR, ep->fअगरoctr);
	अगर (req->req.length == 0) अणु
		r8a66597_bset(r8a66597, BVAL, ep->fअगरoctr);
		pipe_start(r8a66597, 0);
		transfer_complete(ep, req, 0);
	पूर्ण अन्यथा अणु
		r8a66597_ग_लिखो(r8a66597, ~BEMP0, BEMPSTS);
		irq_ep0_ग_लिखो(ep, req);
	पूर्ण
पूर्ण

अटल व्योम disable_fअगरosel(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत,
			    u16 fअगरosel)
अणु
	u16 पंचांगp;

	पंचांगp = r8a66597_पढ़ो(r8a66597, fअगरosel) & CURPIPE;
	अगर (पंचांगp == pipक्रमागत)
		r8a66597_change_curpipe(r8a66597, 0, 0, fअगरosel);
पूर्ण

अटल व्योम change_bfre_mode(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत,
			     पूर्णांक enable)
अणु
	काष्ठा r8a66597_ep *ep = r8a66597->pipक्रमागत2ep[pipक्रमागत];
	u16 पंचांगp, toggle;

	/* check current BFRE bit */
	r8a66597_ग_लिखो(r8a66597, pipक्रमागत, PIPESEL);
	पंचांगp = r8a66597_पढ़ो(r8a66597, PIPECFG) & R8A66597_BFRE;
	अगर ((enable && पंचांगp) || (!enable && !पंचांगp))
		वापस;

	/* change BFRE bit */
	pipe_stop(r8a66597, pipक्रमागत);
	disable_fअगरosel(r8a66597, pipक्रमागत, CFIFOSEL);
	disable_fअगरosel(r8a66597, pipक्रमागत, D0FIFOSEL);
	disable_fअगरosel(r8a66597, pipक्रमागत, D1FIFOSEL);

	toggle = save_usb_toggle(r8a66597, pipक्रमागत);

	r8a66597_ग_लिखो(r8a66597, pipक्रमागत, PIPESEL);
	अगर (enable)
		r8a66597_bset(r8a66597, R8A66597_BFRE, PIPECFG);
	अन्यथा
		r8a66597_bclr(r8a66597, R8A66597_BFRE, PIPECFG);

	/* initialize क्रम पूर्णांकernal BFRE flag */
	r8a66597_bset(r8a66597, ACLRM, ep->pipectr);
	r8a66597_bclr(r8a66597, ACLRM, ep->pipectr);

	restore_usb_toggle(r8a66597, pipक्रमागत, toggle);
पूर्ण

अटल पूर्णांक sudmac_alloc_channel(काष्ठा r8a66597 *r8a66597,
				काष्ठा r8a66597_ep *ep,
				काष्ठा r8a66597_request *req)
अणु
	काष्ठा r8a66597_dma *dma;

	अगर (!r8a66597_is_sudmac(r8a66597))
		वापस -ENODEV;

	/* Check transfer type */
	अगर (!is_bulk_pipe(ep->pipक्रमागत))
		वापस -EIO;

	अगर (r8a66597->dma.used)
		वापस -EBUSY;

	/* set SUDMAC parameters */
	dma = &r8a66597->dma;
	dma->used = 1;
	अगर (ep->ep.desc->bEndpoपूर्णांकAddress & USB_सूची_IN) अणु
		dma->dir = 1;
	पूर्ण अन्यथा अणु
		dma->dir = 0;
		change_bfre_mode(r8a66597, ep->pipक्रमागत, 1);
	पूर्ण

	/* set r8a66597_ep paramters */
	ep->use_dma = 1;
	ep->dma = dma;
	ep->fअगरoaddr = D0FIFO;
	ep->fअगरosel = D0FIFOSEL;
	ep->fअगरoctr = D0FIFOCTR;

	/* dma mapping */
	वापस usb_gadget_map_request(&r8a66597->gadget, &req->req, dma->dir);
पूर्ण

अटल व्योम sudmac_मुक्त_channel(काष्ठा r8a66597 *r8a66597,
				काष्ठा r8a66597_ep *ep,
				काष्ठा r8a66597_request *req)
अणु
	अगर (!r8a66597_is_sudmac(r8a66597))
		वापस;

	usb_gadget_unmap_request(&r8a66597->gadget, &req->req, ep->dma->dir);

	r8a66597_bclr(r8a66597, DREQE, ep->fअगरosel);
	r8a66597_change_curpipe(r8a66597, 0, 0, ep->fअगरosel);

	ep->dma->used = 0;
	ep->use_dma = 0;
	ep->fअगरoaddr = CFIFO;
	ep->fअगरosel = CFIFOSEL;
	ep->fअगरoctr = CFIFOCTR;
पूर्ण

अटल व्योम sudmac_start(काष्ठा r8a66597 *r8a66597, काष्ठा r8a66597_ep *ep,
			 काष्ठा r8a66597_request *req)
अणु
	BUG_ON(req->req.length == 0);

	r8a66597_sudmac_ग_लिखो(r8a66597, LBA_WAIT, CH0CFG);
	r8a66597_sudmac_ग_लिखो(r8a66597, req->req.dma, CH0BA);
	r8a66597_sudmac_ग_लिखो(r8a66597, req->req.length, CH0BBC);
	r8a66597_sudmac_ग_लिखो(r8a66597, CH0ENDE, DINTCTRL);

	r8a66597_sudmac_ग_लिखो(r8a66597, DEN, CH0DEN);
पूर्ण

अटल व्योम start_packet_ग_लिखो(काष्ठा r8a66597_ep *ep,
				काष्ठा r8a66597_request *req)
अणु
	काष्ठा r8a66597 *r8a66597 = ep->r8a66597;
	u16 पंचांगp;

	pipe_change(r8a66597, ep->pipक्रमागत);
	disable_irq_empty(r8a66597, ep->pipक्रमागत);
	pipe_start(r8a66597, ep->pipक्रमागत);

	अगर (req->req.length == 0) अणु
		transfer_complete(ep, req, 0);
	पूर्ण अन्यथा अणु
		r8a66597_ग_लिखो(r8a66597, ~(1 << ep->pipक्रमागत), BRDYSTS);
		अगर (sudmac_alloc_channel(r8a66597, ep, req) < 0) अणु
			/* PIO mode */
			pipe_change(r8a66597, ep->pipक्रमागत);
			disable_irq_empty(r8a66597, ep->pipक्रमागत);
			pipe_start(r8a66597, ep->pipक्रमागत);
			पंचांगp = r8a66597_पढ़ो(r8a66597, ep->fअगरoctr);
			अगर (unlikely((पंचांगp & FRDY) == 0))
				pipe_irq_enable(r8a66597, ep->pipक्रमागत);
			अन्यथा
				irq_packet_ग_लिखो(ep, req);
		पूर्ण अन्यथा अणु
			/* DMA mode */
			pipe_change(r8a66597, ep->pipक्रमागत);
			disable_irq_nrdy(r8a66597, ep->pipक्रमागत);
			pipe_start(r8a66597, ep->pipक्रमागत);
			enable_irq_nrdy(r8a66597, ep->pipक्रमागत);
			sudmac_start(r8a66597, ep, req);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम start_packet_पढ़ो(काष्ठा r8a66597_ep *ep,
				काष्ठा r8a66597_request *req)
अणु
	काष्ठा r8a66597 *r8a66597 = ep->r8a66597;
	u16 pipक्रमागत = ep->pipक्रमागत;

	अगर (ep->pipक्रमागत == 0) अणु
		r8a66597_mdfy(r8a66597, 0, (ISEL | CURPIPE), CFIFOSEL);
		r8a66597_ग_लिखो(r8a66597, BCLR, ep->fअगरoctr);
		pipe_start(r8a66597, pipक्रमागत);
		pipe_irq_enable(r8a66597, pipक्रमागत);
	पूर्ण अन्यथा अणु
		pipe_stop(r8a66597, pipक्रमागत);
		अगर (ep->pipetre) अणु
			enable_irq_nrdy(r8a66597, pipक्रमागत);
			r8a66597_ग_लिखो(r8a66597, TRCLR, ep->pipetre);
			r8a66597_ग_लिखो(r8a66597,
				DIV_ROUND_UP(req->req.length, ep->ep.maxpacket),
				ep->pipetrn);
			r8a66597_bset(r8a66597, TRENB, ep->pipetre);
		पूर्ण

		अगर (sudmac_alloc_channel(r8a66597, ep, req) < 0) अणु
			/* PIO mode */
			change_bfre_mode(r8a66597, ep->pipक्रमागत, 0);
			pipe_start(r8a66597, pipक्रमागत);	/* trigger once */
			pipe_irq_enable(r8a66597, pipक्रमागत);
		पूर्ण अन्यथा अणु
			pipe_change(r8a66597, pipक्रमागत);
			sudmac_start(r8a66597, ep, req);
			pipe_start(r8a66597, pipक्रमागत);	/* trigger once */
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम start_packet(काष्ठा r8a66597_ep *ep, काष्ठा r8a66597_request *req)
अणु
	अगर (ep->ep.desc->bEndpoपूर्णांकAddress & USB_सूची_IN)
		start_packet_ग_लिखो(ep, req);
	अन्यथा
		start_packet_पढ़ो(ep, req);
पूर्ण

अटल व्योम start_ep0(काष्ठा r8a66597_ep *ep, काष्ठा r8a66597_request *req)
अणु
	u16 ctsq;

	ctsq = r8a66597_पढ़ो(ep->r8a66597, INTSTS0) & CTSQ;

	चयन (ctsq) अणु
	हाल CS_RDDS:
		start_ep0_ग_लिखो(ep, req);
		अवरोध;
	हाल CS_WRDS:
		start_packet_पढ़ो(ep, req);
		अवरोध;

	हाल CS_WRND:
		control_end(ep->r8a66597, 0);
		अवरोध;
	शेष:
		dev_err(r8a66597_to_dev(ep->r8a66597),
			"start_ep0: unexpect ctsq(%x)\n", ctsq);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम init_controller(काष्ठा r8a66597 *r8a66597)
अणु
	u16 vअगर = r8a66597->pdata->vअगर ? LDRV : 0;
	u16 irq_sense = r8a66597->irq_sense_low ? INTL : 0;
	u16 endian = r8a66597->pdata->endian ? BIGEND : 0;

	अगर (r8a66597->pdata->on_chip) अणु
		अगर (r8a66597->pdata->busरुको)
			r8a66597_ग_लिखो(r8a66597, r8a66597->pdata->busरुको,
					SYSCFG1);
		अन्यथा
			r8a66597_ग_लिखो(r8a66597, 0x0f, SYSCFG1);
		r8a66597_bset(r8a66597, HSE, SYSCFG0);

		r8a66597_bclr(r8a66597, USBE, SYSCFG0);
		r8a66597_bclr(r8a66597, DPRPU, SYSCFG0);
		r8a66597_bset(r8a66597, USBE, SYSCFG0);

		r8a66597_bset(r8a66597, SCKE, SYSCFG0);

		r8a66597_bset(r8a66597, irq_sense, INTENB1);
		r8a66597_ग_लिखो(r8a66597, BURST | CPU_ADR_RD_WR,
				DMA0CFG);
	पूर्ण अन्यथा अणु
		r8a66597_bset(r8a66597, vअगर | endian, PINCFG);
		r8a66597_bset(r8a66597, HSE, SYSCFG0);		/* High spd */
		r8a66597_mdfy(r8a66597, get_xtal_from_pdata(r8a66597->pdata),
				XTAL, SYSCFG0);

		r8a66597_bclr(r8a66597, USBE, SYSCFG0);
		r8a66597_bclr(r8a66597, DPRPU, SYSCFG0);
		r8a66597_bset(r8a66597, USBE, SYSCFG0);

		r8a66597_bset(r8a66597, XCKE, SYSCFG0);

		mdelay(3);

		r8a66597_bset(r8a66597, PLLC, SYSCFG0);

		mdelay(1);

		r8a66597_bset(r8a66597, SCKE, SYSCFG0);

		r8a66597_bset(r8a66597, irq_sense, INTENB1);
		r8a66597_ग_लिखो(r8a66597, BURST | CPU_ADR_RD_WR,
			       DMA0CFG);
	पूर्ण
पूर्ण

अटल व्योम disable_controller(काष्ठा r8a66597 *r8a66597)
अणु
	अगर (r8a66597->pdata->on_chip) अणु
		r8a66597_bset(r8a66597, SCKE, SYSCFG0);
		r8a66597_bclr(r8a66597, UTST, TESTMODE);

		/* disable पूर्णांकerrupts */
		r8a66597_ग_लिखो(r8a66597, 0, INTENB0);
		r8a66597_ग_लिखो(r8a66597, 0, INTENB1);
		r8a66597_ग_लिखो(r8a66597, 0, BRDYENB);
		r8a66597_ग_लिखो(r8a66597, 0, BEMPENB);
		r8a66597_ग_लिखो(r8a66597, 0, NRDYENB);

		/* clear status */
		r8a66597_ग_लिखो(r8a66597, 0, BRDYSTS);
		r8a66597_ग_लिखो(r8a66597, 0, NRDYSTS);
		r8a66597_ग_लिखो(r8a66597, 0, BEMPSTS);

		r8a66597_bclr(r8a66597, USBE, SYSCFG0);
		r8a66597_bclr(r8a66597, SCKE, SYSCFG0);

	पूर्ण अन्यथा अणु
		r8a66597_bclr(r8a66597, UTST, TESTMODE);
		r8a66597_bclr(r8a66597, SCKE, SYSCFG0);
		udelay(1);
		r8a66597_bclr(r8a66597, PLLC, SYSCFG0);
		udelay(1);
		udelay(1);
		r8a66597_bclr(r8a66597, XCKE, SYSCFG0);
	पूर्ण
पूर्ण

अटल व्योम r8a66597_start_xघड़ी(काष्ठा r8a66597 *r8a66597)
अणु
	u16 पंचांगp;

	अगर (!r8a66597->pdata->on_chip) अणु
		पंचांगp = r8a66597_पढ़ो(r8a66597, SYSCFG0);
		अगर (!(पंचांगp & XCKE))
			r8a66597_bset(r8a66597, XCKE, SYSCFG0);
	पूर्ण
पूर्ण

अटल काष्ठा r8a66597_request *get_request_from_ep(काष्ठा r8a66597_ep *ep)
अणु
	वापस list_entry(ep->queue.next, काष्ठा r8a66597_request, queue);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम transfer_complete(काष्ठा r8a66597_ep *ep,
		काष्ठा r8a66597_request *req, पूर्णांक status)
__releases(r8a66597->lock)
__acquires(r8a66597->lock)
अणु
	पूर्णांक restart = 0;

	अगर (unlikely(ep->pipक्रमागत == 0)) अणु
		अगर (ep->पूर्णांकernal_ccpl) अणु
			ep->पूर्णांकernal_ccpl = 0;
			वापस;
		पूर्ण
	पूर्ण

	list_del_init(&req->queue);
	अगर (ep->r8a66597->gadget.speed == USB_SPEED_UNKNOWN)
		req->req.status = -ESHUTDOWN;
	अन्यथा
		req->req.status = status;

	अगर (!list_empty(&ep->queue))
		restart = 1;

	अगर (ep->use_dma)
		sudmac_मुक्त_channel(ep->r8a66597, ep, req);

	spin_unlock(&ep->r8a66597->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&ep->r8a66597->lock);

	अगर (restart) अणु
		req = get_request_from_ep(ep);
		अगर (ep->ep.desc)
			start_packet(ep, req);
	पूर्ण
पूर्ण

अटल व्योम irq_ep0_ग_लिखो(काष्ठा r8a66597_ep *ep, काष्ठा r8a66597_request *req)
अणु
	पूर्णांक i;
	u16 पंचांगp;
	अचिन्हित bufsize;
	माप_प्रकार size;
	व्योम *buf;
	u16 pipक्रमागत = ep->pipक्रमागत;
	काष्ठा r8a66597 *r8a66597 = ep->r8a66597;

	pipe_change(r8a66597, pipक्रमागत);
	r8a66597_bset(r8a66597, ISEL, ep->fअगरosel);

	i = 0;
	करो अणु
		पंचांगp = r8a66597_पढ़ो(r8a66597, ep->fअगरoctr);
		अगर (i++ > 100000) अणु
			dev_err(r8a66597_to_dev(r8a66597),
				"pipe0 is busy. maybe cpu i/o bus "
				"conflict. please power off this controller.");
			वापस;
		पूर्ण
		ndelay(1);
	पूर्ण जबतक ((पंचांगp & FRDY) == 0);

	/* prepare parameters */
	bufsize = get_buffer_size(r8a66597, pipक्रमागत);
	buf = req->req.buf + req->req.actual;
	size = min(bufsize, req->req.length - req->req.actual);

	/* ग_लिखो fअगरo */
	अगर (req->req.buf) अणु
		अगर (size > 0)
			r8a66597_ग_लिखो_fअगरo(r8a66597, ep, buf, size);
		अगर ((size == 0) || ((size % ep->ep.maxpacket) != 0))
			r8a66597_bset(r8a66597, BVAL, ep->fअगरoctr);
	पूर्ण

	/* update parameters */
	req->req.actual += size;

	/* check transfer finish */
	अगर ((!req->req.zero && (req->req.actual == req->req.length))
			|| (size % ep->ep.maxpacket)
			|| (size == 0)) अणु
		disable_irq_पढ़ोy(r8a66597, pipक्रमागत);
		disable_irq_empty(r8a66597, pipक्रमागत);
	पूर्ण अन्यथा अणु
		disable_irq_पढ़ोy(r8a66597, pipक्रमागत);
		enable_irq_empty(r8a66597, pipक्रमागत);
	पूर्ण
	pipe_start(r8a66597, pipक्रमागत);
पूर्ण

अटल व्योम irq_packet_ग_लिखो(काष्ठा r8a66597_ep *ep,
				काष्ठा r8a66597_request *req)
अणु
	u16 पंचांगp;
	अचिन्हित bufsize;
	माप_प्रकार size;
	व्योम *buf;
	u16 pipक्रमागत = ep->pipक्रमागत;
	काष्ठा r8a66597 *r8a66597 = ep->r8a66597;

	pipe_change(r8a66597, pipक्रमागत);
	पंचांगp = r8a66597_पढ़ो(r8a66597, ep->fअगरoctr);
	अगर (unlikely((पंचांगp & FRDY) == 0)) अणु
		pipe_stop(r8a66597, pipक्रमागत);
		pipe_irq_disable(r8a66597, pipक्रमागत);
		dev_err(r8a66597_to_dev(r8a66597),
			"write fifo not ready. pipnum=%d\n", pipक्रमागत);
		वापस;
	पूर्ण

	/* prepare parameters */
	bufsize = get_buffer_size(r8a66597, pipक्रमागत);
	buf = req->req.buf + req->req.actual;
	size = min(bufsize, req->req.length - req->req.actual);

	/* ग_लिखो fअगरo */
	अगर (req->req.buf) अणु
		r8a66597_ग_लिखो_fअगरo(r8a66597, ep, buf, size);
		अगर ((size == 0)
				|| ((size % ep->ep.maxpacket) != 0)
				|| ((bufsize != ep->ep.maxpacket)
					&& (bufsize > size)))
			r8a66597_bset(r8a66597, BVAL, ep->fअगरoctr);
	पूर्ण

	/* update parameters */
	req->req.actual += size;
	/* check transfer finish */
	अगर ((!req->req.zero && (req->req.actual == req->req.length))
			|| (size % ep->ep.maxpacket)
			|| (size == 0)) अणु
		disable_irq_पढ़ोy(r8a66597, pipक्रमागत);
		enable_irq_empty(r8a66597, pipक्रमागत);
	पूर्ण अन्यथा अणु
		disable_irq_empty(r8a66597, pipक्रमागत);
		pipe_irq_enable(r8a66597, pipक्रमागत);
	पूर्ण
पूर्ण

अटल व्योम irq_packet_पढ़ो(काष्ठा r8a66597_ep *ep,
				काष्ठा r8a66597_request *req)
अणु
	u16 पंचांगp;
	पूर्णांक rcv_len, bufsize, req_len;
	पूर्णांक size;
	व्योम *buf;
	u16 pipक्रमागत = ep->pipक्रमागत;
	काष्ठा r8a66597 *r8a66597 = ep->r8a66597;
	पूर्णांक finish = 0;

	pipe_change(r8a66597, pipक्रमागत);
	पंचांगp = r8a66597_पढ़ो(r8a66597, ep->fअगरoctr);
	अगर (unlikely((पंचांगp & FRDY) == 0)) अणु
		req->req.status = -EPIPE;
		pipe_stop(r8a66597, pipक्रमागत);
		pipe_irq_disable(r8a66597, pipक्रमागत);
		dev_err(r8a66597_to_dev(r8a66597), "read fifo not ready");
		वापस;
	पूर्ण

	/* prepare parameters */
	rcv_len = पंचांगp & DTLN;
	bufsize = get_buffer_size(r8a66597, pipक्रमागत);

	buf = req->req.buf + req->req.actual;
	req_len = req->req.length - req->req.actual;
	अगर (rcv_len < bufsize)
		size = min(rcv_len, req_len);
	अन्यथा
		size = min(bufsize, req_len);

	/* update parameters */
	req->req.actual += size;

	/* check transfer finish */
	अगर ((!req->req.zero && (req->req.actual == req->req.length))
			|| (size % ep->ep.maxpacket)
			|| (size == 0)) अणु
		pipe_stop(r8a66597, pipक्रमागत);
		pipe_irq_disable(r8a66597, pipक्रमागत);
		finish = 1;
	पूर्ण

	/* पढ़ो fअगरo */
	अगर (req->req.buf) अणु
		अगर (size == 0)
			r8a66597_ग_लिखो(r8a66597, BCLR, ep->fअगरoctr);
		अन्यथा
			r8a66597_पढ़ो_fअगरo(r8a66597, ep->fअगरoaddr, buf, size);

	पूर्ण

	अगर ((ep->pipक्रमागत != 0) && finish)
		transfer_complete(ep, req, 0);
पूर्ण

अटल व्योम irq_pipe_पढ़ोy(काष्ठा r8a66597 *r8a66597, u16 status, u16 enb)
अणु
	u16 check;
	u16 pipक्रमागत;
	काष्ठा r8a66597_ep *ep;
	काष्ठा r8a66597_request *req;

	अगर ((status & BRDY0) && (enb & BRDY0)) अणु
		r8a66597_ग_लिखो(r8a66597, ~BRDY0, BRDYSTS);
		r8a66597_mdfy(r8a66597, 0, CURPIPE, CFIFOSEL);

		ep = &r8a66597->ep[0];
		req = get_request_from_ep(ep);
		irq_packet_पढ़ो(ep, req);
	पूर्ण अन्यथा अणु
		क्रम (pipक्रमागत = 1; pipक्रमागत < R8A66597_MAX_NUM_PIPE; pipक्रमागत++) अणु
			check = 1 << pipक्रमागत;
			अगर ((status & check) && (enb & check)) अणु
				r8a66597_ग_लिखो(r8a66597, ~check, BRDYSTS);
				ep = r8a66597->pipक्रमागत2ep[pipक्रमागत];
				req = get_request_from_ep(ep);
				अगर (ep->ep.desc->bEndpoपूर्णांकAddress & USB_सूची_IN)
					irq_packet_ग_लिखो(ep, req);
				अन्यथा
					irq_packet_पढ़ो(ep, req);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम irq_pipe_empty(काष्ठा r8a66597 *r8a66597, u16 status, u16 enb)
अणु
	u16 पंचांगp;
	u16 check;
	u16 pipक्रमागत;
	काष्ठा r8a66597_ep *ep;
	काष्ठा r8a66597_request *req;

	अगर ((status & BEMP0) && (enb & BEMP0)) अणु
		r8a66597_ग_लिखो(r8a66597, ~BEMP0, BEMPSTS);

		ep = &r8a66597->ep[0];
		req = get_request_from_ep(ep);
		irq_ep0_ग_लिखो(ep, req);
	पूर्ण अन्यथा अणु
		क्रम (pipक्रमागत = 1; pipक्रमागत < R8A66597_MAX_NUM_PIPE; pipक्रमागत++) अणु
			check = 1 << pipक्रमागत;
			अगर ((status & check) && (enb & check)) अणु
				r8a66597_ग_लिखो(r8a66597, ~check, BEMPSTS);
				पंचांगp = control_reg_get(r8a66597, pipक्रमागत);
				अगर ((पंचांगp & INBUFM) == 0) अणु
					disable_irq_empty(r8a66597, pipक्रमागत);
					pipe_irq_disable(r8a66597, pipक्रमागत);
					pipe_stop(r8a66597, pipक्रमागत);
					ep = r8a66597->pipक्रमागत2ep[pipक्रमागत];
					req = get_request_from_ep(ep);
					अगर (!list_empty(&ep->queue))
						transfer_complete(ep, req, 0);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम get_status(काष्ठा r8a66597 *r8a66597, काष्ठा usb_ctrlrequest *ctrl)
__releases(r8a66597->lock)
__acquires(r8a66597->lock)
अणु
	काष्ठा r8a66597_ep *ep;
	u16 pid;
	u16 status = 0;
	u16 w_index = le16_to_cpu(ctrl->wIndex);

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		status = r8a66597->device_status;
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		status = 0;
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		ep = r8a66597->epaddr2ep[w_index & USB_ENDPOINT_NUMBER_MASK];
		pid = control_reg_get_pid(r8a66597, ep->pipक्रमागत);
		अगर (pid == PID_STALL)
			status = 1 << USB_ENDPOINT_HALT;
		अन्यथा
			status = 0;
		अवरोध;
	शेष:
		pipe_stall(r8a66597, 0);
		वापस;		/* निकास */
	पूर्ण

	r8a66597->ep0_data = cpu_to_le16(status);
	r8a66597->ep0_req->buf = &r8a66597->ep0_data;
	r8a66597->ep0_req->length = 2;
	/* AV: what happens अगर we get called again beक्रमe that माला_लो through? */
	spin_unlock(&r8a66597->lock);
	r8a66597_queue(r8a66597->gadget.ep0, r8a66597->ep0_req, GFP_ATOMIC);
	spin_lock(&r8a66597->lock);
पूर्ण

अटल व्योम clear_feature(काष्ठा r8a66597 *r8a66597,
				काष्ठा usb_ctrlrequest *ctrl)
अणु
	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		control_end(r8a66597, 1);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		control_end(r8a66597, 1);
		अवरोध;
	हाल USB_RECIP_ENDPOINT: अणु
		काष्ठा r8a66597_ep *ep;
		काष्ठा r8a66597_request *req;
		u16 w_index = le16_to_cpu(ctrl->wIndex);

		ep = r8a66597->epaddr2ep[w_index & USB_ENDPOINT_NUMBER_MASK];
		अगर (!ep->wedge) अणु
			pipe_stop(r8a66597, ep->pipक्रमागत);
			control_reg_sqclr(r8a66597, ep->pipक्रमागत);
			spin_unlock(&r8a66597->lock);
			usb_ep_clear_halt(&ep->ep);
			spin_lock(&r8a66597->lock);
		पूर्ण

		control_end(r8a66597, 1);

		req = get_request_from_ep(ep);
		अगर (ep->busy) अणु
			ep->busy = 0;
			अगर (list_empty(&ep->queue))
				अवरोध;
			start_packet(ep, req);
		पूर्ण अन्यथा अगर (!list_empty(&ep->queue))
			pipe_start(r8a66597, ep->pipक्रमागत);
		पूर्ण
		अवरोध;
	शेष:
		pipe_stall(r8a66597, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम set_feature(काष्ठा r8a66597 *r8a66597, काष्ठा usb_ctrlrequest *ctrl)
अणु
	u16 पंचांगp;
	पूर्णांक समयout = 3000;

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		चयन (le16_to_cpu(ctrl->wValue)) अणु
		हाल USB_DEVICE_TEST_MODE:
			control_end(r8a66597, 1);
			/* Wait क्रम the completion of status stage */
			करो अणु
				पंचांगp = r8a66597_पढ़ो(r8a66597, INTSTS0) & CTSQ;
				udelay(1);
			पूर्ण जबतक (पंचांगp != CS_IDST || समयout-- > 0);

			अगर (पंचांगp == CS_IDST)
				r8a66597_bset(r8a66597,
					      le16_to_cpu(ctrl->wIndex >> 8),
					      TESTMODE);
			अवरोध;
		शेष:
			pipe_stall(r8a66597, 0);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		control_end(r8a66597, 1);
		अवरोध;
	हाल USB_RECIP_ENDPOINT: अणु
		काष्ठा r8a66597_ep *ep;
		u16 w_index = le16_to_cpu(ctrl->wIndex);

		ep = r8a66597->epaddr2ep[w_index & USB_ENDPOINT_NUMBER_MASK];
		pipe_stall(r8a66597, ep->pipक्रमागत);

		control_end(r8a66597, 1);
		पूर्ण
		अवरोध;
	शेष:
		pipe_stall(r8a66597, 0);
		अवरोध;
	पूर्ण
पूर्ण

/* अगर वापस value is true, call class driver's setup() */
अटल पूर्णांक setup_packet(काष्ठा r8a66597 *r8a66597, काष्ठा usb_ctrlrequest *ctrl)
अणु
	u16 *p = (u16 *)ctrl;
	अचिन्हित दीर्घ offset = USBREQ;
	पूर्णांक i, ret = 0;

	/* पढ़ो fअगरo */
	r8a66597_ग_लिखो(r8a66597, ~VALID, INTSTS0);

	क्रम (i = 0; i < 4; i++)
		p[i] = r8a66597_पढ़ो(r8a66597, offset + i*2);

	/* check request */
	अगर ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		चयन (ctrl->bRequest) अणु
		हाल USB_REQ_GET_STATUS:
			get_status(r8a66597, ctrl);
			अवरोध;
		हाल USB_REQ_CLEAR_FEATURE:
			clear_feature(r8a66597, ctrl);
			अवरोध;
		हाल USB_REQ_SET_FEATURE:
			set_feature(r8a66597, ctrl);
			अवरोध;
		शेष:
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		ret = 1;
	वापस ret;
पूर्ण

अटल व्योम r8a66597_update_usb_speed(काष्ठा r8a66597 *r8a66597)
अणु
	u16 speed = get_usb_speed(r8a66597);

	चयन (speed) अणु
	हाल HSMODE:
		r8a66597->gadget.speed = USB_SPEED_HIGH;
		अवरोध;
	हाल FSMODE:
		r8a66597->gadget.speed = USB_SPEED_FULL;
		अवरोध;
	शेष:
		r8a66597->gadget.speed = USB_SPEED_UNKNOWN;
		dev_err(r8a66597_to_dev(r8a66597), "USB speed unknown\n");
	पूर्ण
पूर्ण

अटल व्योम irq_device_state(काष्ठा r8a66597 *r8a66597)
अणु
	u16 dvsq;

	dvsq = r8a66597_पढ़ो(r8a66597, INTSTS0) & DVSQ;
	r8a66597_ग_लिखो(r8a66597, ~DVST, INTSTS0);

	अगर (dvsq == DS_DFLT) अणु
		/* bus reset */
		spin_unlock(&r8a66597->lock);
		usb_gadget_udc_reset(&r8a66597->gadget, r8a66597->driver);
		spin_lock(&r8a66597->lock);
		r8a66597_update_usb_speed(r8a66597);
	पूर्ण
	अगर (r8a66597->old_dvsq == DS_CNFG && dvsq != DS_CNFG)
		r8a66597_update_usb_speed(r8a66597);
	अगर ((dvsq == DS_CNFG || dvsq == DS_ADDS)
			&& r8a66597->gadget.speed == USB_SPEED_UNKNOWN)
		r8a66597_update_usb_speed(r8a66597);

	r8a66597->old_dvsq = dvsq;
पूर्ण

अटल व्योम irq_control_stage(काष्ठा r8a66597 *r8a66597)
__releases(r8a66597->lock)
__acquires(r8a66597->lock)
अणु
	काष्ठा usb_ctrlrequest ctrl;
	u16 ctsq;

	ctsq = r8a66597_पढ़ो(r8a66597, INTSTS0) & CTSQ;
	r8a66597_ग_लिखो(r8a66597, ~CTRT, INTSTS0);

	चयन (ctsq) अणु
	हाल CS_IDST: अणु
		काष्ठा r8a66597_ep *ep;
		काष्ठा r8a66597_request *req;
		ep = &r8a66597->ep[0];
		req = get_request_from_ep(ep);
		transfer_complete(ep, req, 0);
		पूर्ण
		अवरोध;

	हाल CS_RDDS:
	हाल CS_WRDS:
	हाल CS_WRND:
		अगर (setup_packet(r8a66597, &ctrl)) अणु
			spin_unlock(&r8a66597->lock);
			अगर (r8a66597->driver->setup(&r8a66597->gadget, &ctrl)
				< 0)
				pipe_stall(r8a66597, 0);
			spin_lock(&r8a66597->lock);
		पूर्ण
		अवरोध;
	हाल CS_RDSS:
	हाल CS_WRSS:
		control_end(r8a66597, 0);
		अवरोध;
	शेष:
		dev_err(r8a66597_to_dev(r8a66597),
			"ctrl_stage: unexpect ctsq(%x)\n", ctsq);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sudmac_finish(काष्ठा r8a66597 *r8a66597, काष्ठा r8a66597_ep *ep)
अणु
	u16 pipक्रमागत;
	काष्ठा r8a66597_request *req;
	u32 len;
	पूर्णांक i = 0;

	pipक्रमागत = ep->pipक्रमागत;
	pipe_change(r8a66597, pipक्रमागत);

	जबतक (!(r8a66597_पढ़ो(r8a66597, ep->fअगरoctr) & FRDY)) अणु
		udelay(1);
		अगर (unlikely(i++ >= 10000)) अणु	/* समयout = 10 msec */
			dev_err(r8a66597_to_dev(r8a66597),
				"%s: FRDY was not set (%d)\n",
				__func__, pipक्रमागत);
			वापस;
		पूर्ण
	पूर्ण

	r8a66597_bset(r8a66597, BCLR, ep->fअगरoctr);
	req = get_request_from_ep(ep);

	/* prepare parameters */
	len = r8a66597_sudmac_पढ़ो(r8a66597, CH0CBC);
	req->req.actual += len;

	/* clear */
	r8a66597_sudmac_ग_लिखो(r8a66597, CH0STCLR, DSTSCLR);

	/* check transfer finish */
	अगर ((!req->req.zero && (req->req.actual == req->req.length))
			|| (len % ep->ep.maxpacket)) अणु
		अगर (ep->dma->dir) अणु
			disable_irq_पढ़ोy(r8a66597, pipक्रमागत);
			enable_irq_empty(r8a66597, pipक्रमागत);
		पूर्ण अन्यथा अणु
			/* Clear the पूर्णांकerrupt flag क्रम next transfer */
			r8a66597_ग_लिखो(r8a66597, ~(1 << pipक्रमागत), BRDYSTS);
			transfer_complete(ep, req, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम r8a66597_sudmac_irq(काष्ठा r8a66597 *r8a66597)
अणु
	u32 irqsts;
	काष्ठा r8a66597_ep *ep;
	u16 pipक्रमागत;

	irqsts = r8a66597_sudmac_पढ़ो(r8a66597, DINTSTS);
	अगर (irqsts & CH0ENDS) अणु
		r8a66597_sudmac_ग_लिखो(r8a66597, CH0ENDC, DINTSTSCLR);
		pipक्रमागत = (r8a66597_पढ़ो(r8a66597, D0FIFOSEL) & CURPIPE);
		ep = r8a66597->pipक्रमागत2ep[pipक्रमागत];
		sudmac_finish(r8a66597, ep);
	पूर्ण
पूर्ण

अटल irqवापस_t r8a66597_irq(पूर्णांक irq, व्योम *_r8a66597)
अणु
	काष्ठा r8a66597 *r8a66597 = _r8a66597;
	u16 पूर्णांकsts0;
	u16 पूर्णांकenb0;
	u16 savepipe;
	u16 mask0;

	spin_lock(&r8a66597->lock);

	अगर (r8a66597_is_sudmac(r8a66597))
		r8a66597_sudmac_irq(r8a66597);

	पूर्णांकsts0 = r8a66597_पढ़ो(r8a66597, INTSTS0);
	पूर्णांकenb0 = r8a66597_पढ़ो(r8a66597, INTENB0);

	savepipe = r8a66597_पढ़ो(r8a66597, CFIFOSEL);

	mask0 = पूर्णांकsts0 & पूर्णांकenb0;
	अगर (mask0) अणु
		u16 brdysts = r8a66597_पढ़ो(r8a66597, BRDYSTS);
		u16 bempsts = r8a66597_पढ़ो(r8a66597, BEMPSTS);
		u16 brdyenb = r8a66597_पढ़ो(r8a66597, BRDYENB);
		u16 bempenb = r8a66597_पढ़ो(r8a66597, BEMPENB);

		अगर (mask0 & VBINT) अणु
			r8a66597_ग_लिखो(r8a66597,  0xffff & ~VBINT,
					INTSTS0);
			r8a66597_start_xघड़ी(r8a66597);

			/* start vbus sampling */
			r8a66597->old_vbus = r8a66597_पढ़ो(r8a66597, INTSTS0)
					& VBSTS;
			r8a66597->scount = R8A66597_MAX_SAMPLING;

			mod_समयr(&r8a66597->समयr,
					jअगरfies + msecs_to_jअगरfies(50));
		पूर्ण
		अगर (पूर्णांकsts0 & DVSQ)
			irq_device_state(r8a66597);

		अगर ((पूर्णांकsts0 & BRDY) && (पूर्णांकenb0 & BRDYE)
				&& (brdysts & brdyenb))
			irq_pipe_पढ़ोy(r8a66597, brdysts, brdyenb);
		अगर ((पूर्णांकsts0 & BEMP) && (पूर्णांकenb0 & BEMPE)
				&& (bempsts & bempenb))
			irq_pipe_empty(r8a66597, bempsts, bempenb);

		अगर (पूर्णांकsts0 & CTRT)
			irq_control_stage(r8a66597);
	पूर्ण

	r8a66597_ग_लिखो(r8a66597, savepipe, CFIFOSEL);

	spin_unlock(&r8a66597->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम r8a66597_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा r8a66597 *r8a66597 = from_समयr(r8a66597, t, समयr);
	अचिन्हित दीर्घ flags;
	u16 पंचांगp;

	spin_lock_irqsave(&r8a66597->lock, flags);
	पंचांगp = r8a66597_पढ़ो(r8a66597, SYSCFG0);
	अगर (r8a66597->scount > 0) अणु
		पंचांगp = r8a66597_पढ़ो(r8a66597, INTSTS0) & VBSTS;
		अगर (पंचांगp == r8a66597->old_vbus) अणु
			r8a66597->scount--;
			अगर (r8a66597->scount == 0) अणु
				अगर (पंचांगp == VBSTS)
					r8a66597_usb_connect(r8a66597);
				अन्यथा
					r8a66597_usb_disconnect(r8a66597);
			पूर्ण अन्यथा अणु
				mod_समयr(&r8a66597->समयr,
					jअगरfies + msecs_to_jअगरfies(50));
			पूर्ण
		पूर्ण अन्यथा अणु
			r8a66597->scount = R8A66597_MAX_SAMPLING;
			r8a66597->old_vbus = पंचांगp;
			mod_समयr(&r8a66597->समयr,
					jअगरfies + msecs_to_jअगरfies(50));
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&r8a66597->lock, flags);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक r8a66597_enable(काष्ठा usb_ep *_ep,
			 स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा r8a66597_ep *ep;

	ep = container_of(_ep, काष्ठा r8a66597_ep, ep);
	वापस alloc_pipe_config(ep, desc);
पूर्ण

अटल पूर्णांक r8a66597_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा r8a66597_ep *ep;
	काष्ठा r8a66597_request *req;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा r8a66597_ep, ep);
	BUG_ON(!ep);

	जबतक (!list_empty(&ep->queue)) अणु
		req = get_request_from_ep(ep);
		spin_lock_irqsave(&ep->r8a66597->lock, flags);
		transfer_complete(ep, req, -ECONNRESET);
		spin_unlock_irqrestore(&ep->r8a66597->lock, flags);
	पूर्ण

	pipe_irq_disable(ep->r8a66597, ep->pipक्रमागत);
	वापस मुक्त_pipe_config(ep);
पूर्ण

अटल काष्ठा usb_request *r8a66597_alloc_request(काष्ठा usb_ep *_ep,
						gfp_t gfp_flags)
अणु
	काष्ठा r8a66597_request *req;

	req = kzalloc(माप(काष्ठा r8a66597_request), gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

अटल व्योम r8a66597_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा r8a66597_request *req;

	req = container_of(_req, काष्ठा r8a66597_request, req);
	kमुक्त(req);
पूर्ण

अटल पूर्णांक r8a66597_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
			gfp_t gfp_flags)
अणु
	काष्ठा r8a66597_ep *ep;
	काष्ठा r8a66597_request *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक request = 0;

	ep = container_of(_ep, काष्ठा r8a66597_ep, ep);
	req = container_of(_req, काष्ठा r8a66597_request, req);

	अगर (ep->r8a66597->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&ep->r8a66597->lock, flags);

	अगर (list_empty(&ep->queue))
		request = 1;

	list_add_tail(&req->queue, &ep->queue);
	req->req.actual = 0;
	req->req.status = -EINPROGRESS;

	अगर (ep->ep.desc == शून्य)	/* control */
		start_ep0(ep, req);
	अन्यथा अणु
		अगर (request && !ep->busy)
			start_packet(ep, req);
	पूर्ण

	spin_unlock_irqrestore(&ep->r8a66597->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक r8a66597_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा r8a66597_ep *ep;
	काष्ठा r8a66597_request *req;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा r8a66597_ep, ep);
	req = container_of(_req, काष्ठा r8a66597_request, req);

	spin_lock_irqsave(&ep->r8a66597->lock, flags);
	अगर (!list_empty(&ep->queue))
		transfer_complete(ep, req, -ECONNRESET);
	spin_unlock_irqrestore(&ep->r8a66597->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक r8a66597_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा r8a66597_ep *ep = container_of(_ep, काष्ठा r8a66597_ep, ep);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&ep->r8a66597->lock, flags);
	अगर (!list_empty(&ep->queue)) अणु
		ret = -EAGAIN;
	पूर्ण अन्यथा अगर (value) अणु
		ep->busy = 1;
		pipe_stall(ep->r8a66597, ep->pipक्रमागत);
	पूर्ण अन्यथा अणु
		ep->busy = 0;
		ep->wedge = 0;
		pipe_stop(ep->r8a66597, ep->pipक्रमागत);
	पूर्ण
	spin_unlock_irqrestore(&ep->r8a66597->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक r8a66597_set_wedge(काष्ठा usb_ep *_ep)
अणु
	काष्ठा r8a66597_ep *ep;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा r8a66597_ep, ep);

	अगर (!ep || !ep->ep.desc)
		वापस -EINVAL;

	spin_lock_irqsave(&ep->r8a66597->lock, flags);
	ep->wedge = 1;
	spin_unlock_irqrestore(&ep->r8a66597->lock, flags);

	वापस usb_ep_set_halt(_ep);
पूर्ण

अटल व्योम r8a66597_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा r8a66597_ep *ep;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा r8a66597_ep, ep);
	spin_lock_irqsave(&ep->r8a66597->lock, flags);
	अगर (list_empty(&ep->queue) && !ep->busy) अणु
		pipe_stop(ep->r8a66597, ep->pipक्रमागत);
		r8a66597_bclr(ep->r8a66597, BCLR, ep->fअगरoctr);
		r8a66597_ग_लिखो(ep->r8a66597, ACLRM, ep->pipectr);
		r8a66597_ग_लिखो(ep->r8a66597, 0, ep->pipectr);
	पूर्ण
	spin_unlock_irqrestore(&ep->r8a66597->lock, flags);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops r8a66597_ep_ops = अणु
	.enable		= r8a66597_enable,
	.disable	= r8a66597_disable,

	.alloc_request	= r8a66597_alloc_request,
	.मुक्त_request	= r8a66597_मुक्त_request,

	.queue		= r8a66597_queue,
	.dequeue	= r8a66597_dequeue,

	.set_halt	= r8a66597_set_halt,
	.set_wedge	= r8a66597_set_wedge,
	.fअगरo_flush	= r8a66597_fअगरo_flush,
पूर्ण;

/*-------------------------------------------------------------------------*/
अटल पूर्णांक r8a66597_start(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा r8a66597 *r8a66597 = gadget_to_r8a66597(gadget);

	अगर (!driver
			|| driver->max_speed < USB_SPEED_HIGH
			|| !driver->setup)
		वापस -EINVAL;
	अगर (!r8a66597)
		वापस -ENODEV;

	/* hook up the driver */
	r8a66597->driver = driver;

	init_controller(r8a66597);
	r8a66597_bset(r8a66597, VBSE, INTENB0);
	अगर (r8a66597_पढ़ो(r8a66597, INTSTS0) & VBSTS) अणु
		r8a66597_start_xघड़ी(r8a66597);
		/* start vbus sampling */
		r8a66597->old_vbus = r8a66597_पढ़ो(r8a66597,
					 INTSTS0) & VBSTS;
		r8a66597->scount = R8A66597_MAX_SAMPLING;
		mod_समयr(&r8a66597->समयr, jअगरfies + msecs_to_jअगरfies(50));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक r8a66597_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा r8a66597 *r8a66597 = gadget_to_r8a66597(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&r8a66597->lock, flags);
	r8a66597_bclr(r8a66597, VBSE, INTENB0);
	disable_controller(r8a66597);
	spin_unlock_irqrestore(&r8a66597->lock, flags);

	r8a66597->driver = शून्य;
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक r8a66597_get_frame(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा r8a66597 *r8a66597 = gadget_to_r8a66597(_gadget);
	वापस r8a66597_पढ़ो(r8a66597, FRMNUM) & 0x03FF;
पूर्ण

अटल पूर्णांक r8a66597_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा r8a66597 *r8a66597 = gadget_to_r8a66597(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&r8a66597->lock, flags);
	अगर (is_on)
		r8a66597_bset(r8a66597, DPRPU, SYSCFG0);
	अन्यथा
		r8a66597_bclr(r8a66597, DPRPU, SYSCFG0);
	spin_unlock_irqrestore(&r8a66597->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक r8a66597_set_selfघातered(काष्ठा usb_gadget *gadget, पूर्णांक is_self)
अणु
	काष्ठा r8a66597 *r8a66597 = gadget_to_r8a66597(gadget);

	gadget->is_selfघातered = (is_self != 0);
	अगर (is_self)
		r8a66597->device_status |= 1 << USB_DEVICE_SELF_POWERED;
	अन्यथा
		r8a66597->device_status &= ~(1 << USB_DEVICE_SELF_POWERED);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops r8a66597_gadget_ops = अणु
	.get_frame		= r8a66597_get_frame,
	.udc_start		= r8a66597_start,
	.udc_stop		= r8a66597_stop,
	.pullup			= r8a66597_pullup,
	.set_selfघातered	= r8a66597_set_selfघातered,
पूर्ण;

अटल पूर्णांक r8a66597_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा r8a66597		*r8a66597 = platक्रमm_get_drvdata(pdev);

	usb_del_gadget_udc(&r8a66597->gadget);
	del_समयr_sync(&r8a66597->समयr);
	r8a66597_मुक्त_request(&r8a66597->ep[0].ep, r8a66597->ep0_req);

	अगर (r8a66597->pdata->on_chip) अणु
		clk_disable_unprepare(r8a66597->clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nop_completion(काष्ठा usb_ep *ep, काष्ठा usb_request *r)
अणु
पूर्ण

अटल पूर्णांक r8a66597_sudmac_ioremap(काष्ठा r8a66597 *r8a66597,
					  काष्ठा platक्रमm_device *pdev)
अणु
	r8a66597->sudmac_reg =
		devm_platक्रमm_ioremap_resource_byname(pdev, "sudmac");
	वापस PTR_ERR_OR_ZERO(r8a66597->sudmac_reg);
पूर्ण

अटल पूर्णांक r8a66597_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	अक्षर clk_name[8];
	काष्ठा resource *ires;
	पूर्णांक irq;
	व्योम __iomem *reg = शून्य;
	काष्ठा r8a66597 *r8a66597 = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक i;
	अचिन्हित दीर्घ irq_trigger;

	reg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	ires = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!ires)
		वापस -EINVAL;
	irq = ires->start;
	irq_trigger = ires->flags & IRQF_TRIGGER_MASK;

	अगर (irq < 0) अणु
		dev_err(dev, "platform_get_irq error.\n");
		वापस -ENODEV;
	पूर्ण

	/* initialize ucd */
	r8a66597 = devm_kzalloc(dev, माप(काष्ठा r8a66597), GFP_KERNEL);
	अगर (r8a66597 == शून्य)
		वापस -ENOMEM;

	spin_lock_init(&r8a66597->lock);
	platक्रमm_set_drvdata(pdev, r8a66597);
	r8a66597->pdata = dev_get_platdata(dev);
	r8a66597->irq_sense_low = irq_trigger == IRQF_TRIGGER_LOW;

	r8a66597->gadget.ops = &r8a66597_gadget_ops;
	r8a66597->gadget.max_speed = USB_SPEED_HIGH;
	r8a66597->gadget.name = udc_name;

	समयr_setup(&r8a66597->समयr, r8a66597_समयr, 0);
	r8a66597->reg = reg;

	अगर (r8a66597->pdata->on_chip) अणु
		snम_लिखो(clk_name, माप(clk_name), "usb%d", pdev->id);
		r8a66597->clk = devm_clk_get(dev, clk_name);
		अगर (IS_ERR(r8a66597->clk)) अणु
			dev_err(dev, "cannot get clock \"%s\"\n", clk_name);
			वापस PTR_ERR(r8a66597->clk);
		पूर्ण
		clk_prepare_enable(r8a66597->clk);
	पूर्ण

	अगर (r8a66597->pdata->sudmac) अणु
		ret = r8a66597_sudmac_ioremap(r8a66597, pdev);
		अगर (ret < 0)
			जाओ clean_up2;
	पूर्ण

	disable_controller(r8a66597); /* make sure controller is disabled */

	ret = devm_request_irq(dev, irq, r8a66597_irq, IRQF_SHARED,
			       udc_name, r8a66597);
	अगर (ret < 0) अणु
		dev_err(dev, "request_irq error (%d)\n", ret);
		जाओ clean_up2;
	पूर्ण

	INIT_LIST_HEAD(&r8a66597->gadget.ep_list);
	r8a66597->gadget.ep0 = &r8a66597->ep[0].ep;
	INIT_LIST_HEAD(&r8a66597->gadget.ep0->ep_list);
	क्रम (i = 0; i < R8A66597_MAX_NUM_PIPE; i++) अणु
		काष्ठा r8a66597_ep *ep = &r8a66597->ep[i];

		अगर (i != 0) अणु
			INIT_LIST_HEAD(&r8a66597->ep[i].ep.ep_list);
			list_add_tail(&r8a66597->ep[i].ep.ep_list,
					&r8a66597->gadget.ep_list);
		पूर्ण
		ep->r8a66597 = r8a66597;
		INIT_LIST_HEAD(&ep->queue);
		ep->ep.name = r8a66597_ep_name[i];
		ep->ep.ops = &r8a66597_ep_ops;
		usb_ep_set_maxpacket_limit(&ep->ep, 512);

		अगर (i == 0) अणु
			ep->ep.caps.type_control = true;
		पूर्ण अन्यथा अणु
			ep->ep.caps.type_iso = true;
			ep->ep.caps.type_bulk = true;
			ep->ep.caps.type_पूर्णांक = true;
		पूर्ण
		ep->ep.caps.dir_in = true;
		ep->ep.caps.dir_out = true;
	पूर्ण
	usb_ep_set_maxpacket_limit(&r8a66597->ep[0].ep, 64);
	r8a66597->ep[0].pipक्रमागत = 0;
	r8a66597->ep[0].fअगरoaddr = CFIFO;
	r8a66597->ep[0].fअगरosel = CFIFOSEL;
	r8a66597->ep[0].fअगरoctr = CFIFOCTR;
	r8a66597->ep[0].pipectr = get_pipectr_addr(0);
	r8a66597->pipक्रमागत2ep[0] = &r8a66597->ep[0];
	r8a66597->epaddr2ep[0] = &r8a66597->ep[0];

	r8a66597->ep0_req = r8a66597_alloc_request(&r8a66597->ep[0].ep,
							GFP_KERNEL);
	अगर (r8a66597->ep0_req == शून्य) अणु
		ret = -ENOMEM;
		जाओ clean_up2;
	पूर्ण
	r8a66597->ep0_req->complete = nop_completion;

	ret = usb_add_gadget_udc(dev, &r8a66597->gadget);
	अगर (ret)
		जाओ err_add_udc;

	dev_info(dev, "version %s\n", DRIVER_VERSION);
	वापस 0;

err_add_udc:
	r8a66597_मुक्त_request(&r8a66597->ep[0].ep, r8a66597->ep0_req);
clean_up2:
	अगर (r8a66597->pdata->on_chip)
		clk_disable_unprepare(r8a66597->clk);

	अगर (r8a66597->ep0_req)
		r8a66597_मुक्त_request(&r8a66597->ep[0].ep, r8a66597->ep0_req);

	वापस ret;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल काष्ठा platक्रमm_driver r8a66597_driver = अणु
	.हटाओ =	r8a66597_हटाओ,
	.driver		= अणु
		.name =	udc_name,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(r8a66597_driver, r8a66597_probe);

MODULE_DESCRIPTION("R8A66597 USB gadget driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yoshihiro Shimoda");
MODULE_ALIAS("platform:r8a66597_udc");
