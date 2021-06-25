<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * M66592 UDC (USB gadget)
 *
 * Copyright (C) 2006-2007 Renesas Solutions Corp.
 *
 * Author : Yoshihiro Shimoda <yoshihiro.shimoda.uh@renesas.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>

#समावेश "m66592-udc.h"

MODULE_DESCRIPTION("M66592 USB gadget driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yoshihiro Shimoda");
MODULE_ALIAS("platform:m66592_udc");

#घोषणा DRIVER_VERSION	"21 July 2009"

अटल स्थिर अक्षर udc_name[] = "m66592_udc";
अटल स्थिर अक्षर *m66592_ep_name[] = अणु
	"ep0", "ep1", "ep2", "ep3", "ep4", "ep5", "ep6", "ep7"
पूर्ण;

अटल व्योम disable_controller(काष्ठा m66592 *m66592);
अटल व्योम irq_ep0_ग_लिखो(काष्ठा m66592_ep *ep, काष्ठा m66592_request *req);
अटल व्योम irq_packet_ग_लिखो(काष्ठा m66592_ep *ep, काष्ठा m66592_request *req);
अटल पूर्णांक m66592_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
			gfp_t gfp_flags);

अटल व्योम transfer_complete(काष्ठा m66592_ep *ep,
		काष्ठा m66592_request *req, पूर्णांक status);

/*-------------------------------------------------------------------------*/
अटल अंतरभूत u16 get_usb_speed(काष्ठा m66592 *m66592)
अणु
	वापस (m66592_पढ़ो(m66592, M66592_DVSTCTR) & M66592_RHST);
पूर्ण

अटल व्योम enable_pipe_irq(काष्ठा m66592 *m66592, u16 pipक्रमागत,
		अचिन्हित दीर्घ reg)
अणु
	u16 पंचांगp;

	पंचांगp = m66592_पढ़ो(m66592, M66592_INTENB0);
	m66592_bclr(m66592, M66592_BEMPE | M66592_NRDYE | M66592_BRDYE,
			M66592_INTENB0);
	m66592_bset(m66592, (1 << pipक्रमागत), reg);
	m66592_ग_लिखो(m66592, पंचांगp, M66592_INTENB0);
पूर्ण

अटल व्योम disable_pipe_irq(काष्ठा m66592 *m66592, u16 pipक्रमागत,
		अचिन्हित दीर्घ reg)
अणु
	u16 पंचांगp;

	पंचांगp = m66592_पढ़ो(m66592, M66592_INTENB0);
	m66592_bclr(m66592, M66592_BEMPE | M66592_NRDYE | M66592_BRDYE,
			M66592_INTENB0);
	m66592_bclr(m66592, (1 << pipक्रमागत), reg);
	m66592_ग_लिखो(m66592, पंचांगp, M66592_INTENB0);
पूर्ण

अटल व्योम m66592_usb_connect(काष्ठा m66592 *m66592)
अणु
	m66592_bset(m66592, M66592_CTRE, M66592_INTENB0);
	m66592_bset(m66592, M66592_WDST | M66592_RDST | M66592_CMPL,
			M66592_INTENB0);
	m66592_bset(m66592, M66592_BEMPE | M66592_BRDYE, M66592_INTENB0);

	m66592_bset(m66592, M66592_DPRPU, M66592_SYSCFG);
पूर्ण

अटल व्योम m66592_usb_disconnect(काष्ठा m66592 *m66592)
__releases(m66592->lock)
__acquires(m66592->lock)
अणु
	m66592_bclr(m66592, M66592_CTRE, M66592_INTENB0);
	m66592_bclr(m66592, M66592_WDST | M66592_RDST | M66592_CMPL,
			M66592_INTENB0);
	m66592_bclr(m66592, M66592_BEMPE | M66592_BRDYE, M66592_INTENB0);
	m66592_bclr(m66592, M66592_DPRPU, M66592_SYSCFG);

	m66592->gadget.speed = USB_SPEED_UNKNOWN;
	spin_unlock(&m66592->lock);
	m66592->driver->disconnect(&m66592->gadget);
	spin_lock(&m66592->lock);

	disable_controller(m66592);
	INIT_LIST_HEAD(&m66592->ep[0].queue);
पूर्ण

अटल अंतरभूत u16 control_reg_get_pid(काष्ठा m66592 *m66592, u16 pipक्रमागत)
अणु
	u16 pid = 0;
	अचिन्हित दीर्घ offset;

	अगर (pipक्रमागत == 0)
		pid = m66592_पढ़ो(m66592, M66592_DCPCTR) & M66592_PID;
	अन्यथा अगर (pipक्रमागत < M66592_MAX_NUM_PIPE) अणु
		offset = get_pipectr_addr(pipक्रमागत);
		pid = m66592_पढ़ो(m66592, offset) & M66592_PID;
	पूर्ण अन्यथा
		pr_err("unexpect pipe num (%d)\n", pipक्रमागत);

	वापस pid;
पूर्ण

अटल अंतरभूत व्योम control_reg_set_pid(काष्ठा m66592 *m66592, u16 pipक्रमागत,
		u16 pid)
अणु
	अचिन्हित दीर्घ offset;

	अगर (pipक्रमागत == 0)
		m66592_mdfy(m66592, pid, M66592_PID, M66592_DCPCTR);
	अन्यथा अगर (pipक्रमागत < M66592_MAX_NUM_PIPE) अणु
		offset = get_pipectr_addr(pipक्रमागत);
		m66592_mdfy(m66592, pid, M66592_PID, offset);
	पूर्ण अन्यथा
		pr_err("unexpect pipe num (%d)\n", pipक्रमागत);
पूर्ण

अटल अंतरभूत व्योम pipe_start(काष्ठा m66592 *m66592, u16 pipक्रमागत)
अणु
	control_reg_set_pid(m66592, pipक्रमागत, M66592_PID_BUF);
पूर्ण

अटल अंतरभूत व्योम pipe_stop(काष्ठा m66592 *m66592, u16 pipक्रमागत)
अणु
	control_reg_set_pid(m66592, pipक्रमागत, M66592_PID_NAK);
पूर्ण

अटल अंतरभूत व्योम pipe_stall(काष्ठा m66592 *m66592, u16 pipक्रमागत)
अणु
	control_reg_set_pid(m66592, pipक्रमागत, M66592_PID_STALL);
पूर्ण

अटल अंतरभूत u16 control_reg_get(काष्ठा m66592 *m66592, u16 pipक्रमागत)
अणु
	u16 ret = 0;
	अचिन्हित दीर्घ offset;

	अगर (pipक्रमागत == 0)
		ret = m66592_पढ़ो(m66592, M66592_DCPCTR);
	अन्यथा अगर (pipक्रमागत < M66592_MAX_NUM_PIPE) अणु
		offset = get_pipectr_addr(pipक्रमागत);
		ret = m66592_पढ़ो(m66592, offset);
	पूर्ण अन्यथा
		pr_err("unexpect pipe num (%d)\n", pipक्रमागत);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम control_reg_sqclr(काष्ठा m66592 *m66592, u16 pipक्रमागत)
अणु
	अचिन्हित दीर्घ offset;

	pipe_stop(m66592, pipक्रमागत);

	अगर (pipक्रमागत == 0)
		m66592_bset(m66592, M66592_SQCLR, M66592_DCPCTR);
	अन्यथा अगर (pipक्रमागत < M66592_MAX_NUM_PIPE) अणु
		offset = get_pipectr_addr(pipक्रमागत);
		m66592_bset(m66592, M66592_SQCLR, offset);
	पूर्ण अन्यथा
		pr_err("unexpect pipe num(%d)\n", pipक्रमागत);
पूर्ण

अटल अंतरभूत पूर्णांक get_buffer_size(काष्ठा m66592 *m66592, u16 pipक्रमागत)
अणु
	u16 पंचांगp;
	पूर्णांक size;

	अगर (pipक्रमागत == 0) अणु
		पंचांगp = m66592_पढ़ो(m66592, M66592_DCPCFG);
		अगर ((पंचांगp & M66592_CNTMD) != 0)
			size = 256;
		अन्यथा अणु
			पंचांगp = m66592_पढ़ो(m66592, M66592_DCPMAXP);
			size = पंचांगp & M66592_MAXP;
		पूर्ण
	पूर्ण अन्यथा अणु
		m66592_ग_लिखो(m66592, pipक्रमागत, M66592_PIPESEL);
		पंचांगp = m66592_पढ़ो(m66592, M66592_PIPECFG);
		अगर ((पंचांगp & M66592_CNTMD) != 0) अणु
			पंचांगp = m66592_पढ़ो(m66592, M66592_PIPEBUF);
			size = ((पंचांगp >> 10) + 1) * 64;
		पूर्ण अन्यथा अणु
			पंचांगp = m66592_पढ़ो(m66592, M66592_PIPEMAXP);
			size = पंचांगp & M66592_MXPS;
		पूर्ण
	पूर्ण

	वापस size;
पूर्ण

अटल अंतरभूत व्योम pipe_change(काष्ठा m66592 *m66592, u16 pipक्रमागत)
अणु
	काष्ठा m66592_ep *ep = m66592->pipक्रमागत2ep[pipक्रमागत];
	अचिन्हित लघु mbw;

	अगर (ep->use_dma)
		वापस;

	m66592_mdfy(m66592, pipक्रमागत, M66592_CURPIPE, ep->fअगरosel);

	ndelay(450);

	अगर (m66592->pdata->on_chip)
		mbw = M66592_MBW_32;
	अन्यथा
		mbw = M66592_MBW_16;

	m66592_bset(m66592, mbw, ep->fअगरosel);
पूर्ण

अटल पूर्णांक pipe_buffer_setting(काष्ठा m66592 *m66592,
		काष्ठा m66592_pipe_info *info)
अणु
	u16 bufnum = 0, buf_bsize = 0;
	u16 pipecfg = 0;

	अगर (info->pipe == 0)
		वापस -EINVAL;

	m66592_ग_लिखो(m66592, info->pipe, M66592_PIPESEL);

	अगर (info->dir_in)
		pipecfg |= M66592_सूची;
	pipecfg |= info->type;
	pipecfg |= info->epnum;
	चयन (info->type) अणु
	हाल M66592_INT:
		bufnum = 4 + (info->pipe - M66592_BASE_PIPENUM_INT);
		buf_bsize = 0;
		अवरोध;
	हाल M66592_BULK:
		/* isochronous pipes may be used as bulk pipes */
		अगर (info->pipe >= M66592_BASE_PIPENUM_BULK)
			bufnum = info->pipe - M66592_BASE_PIPENUM_BULK;
		अन्यथा
			bufnum = info->pipe - M66592_BASE_PIPENUM_ISOC;

		bufnum = M66592_BASE_BUFNUM + (bufnum * 16);
		buf_bsize = 7;
		pipecfg |= M66592_DBLB;
		अगर (!info->dir_in)
			pipecfg |= M66592_SHTNAK;
		अवरोध;
	हाल M66592_ISO:
		bufnum = M66592_BASE_BUFNUM +
			 (info->pipe - M66592_BASE_PIPENUM_ISOC) * 16;
		buf_bsize = 7;
		अवरोध;
	पूर्ण

	अगर (buf_bsize && ((bufnum + 16) >= M66592_MAX_BUFNUM)) अणु
		pr_err("m66592 pipe memory is insufficient\n");
		वापस -ENOMEM;
	पूर्ण

	m66592_ग_लिखो(m66592, pipecfg, M66592_PIPECFG);
	m66592_ग_लिखो(m66592, (buf_bsize << 10) | (bufnum), M66592_PIPEBUF);
	m66592_ग_लिखो(m66592, info->maxpacket, M66592_PIPEMAXP);
	अगर (info->पूर्णांकerval)
		info->पूर्णांकerval--;
	m66592_ग_लिखो(m66592, info->पूर्णांकerval, M66592_PIPEPERI);

	वापस 0;
पूर्ण

अटल व्योम pipe_buffer_release(काष्ठा m66592 *m66592,
				काष्ठा m66592_pipe_info *info)
अणु
	अगर (info->pipe == 0)
		वापस;

	अगर (is_bulk_pipe(info->pipe)) अणु
		m66592->bulk--;
	पूर्ण अन्यथा अगर (is_पूर्णांकerrupt_pipe(info->pipe))
		m66592->पूर्णांकerrupt--;
	अन्यथा अगर (is_isoc_pipe(info->pipe)) अणु
		m66592->isochronous--;
		अगर (info->type == M66592_BULK)
			m66592->bulk--;
	पूर्ण अन्यथा
		pr_err("ep_release: unexpect pipenum (%d)\n",
				info->pipe);
पूर्ण

अटल व्योम pipe_initialize(काष्ठा m66592_ep *ep)
अणु
	काष्ठा m66592 *m66592 = ep->m66592;
	अचिन्हित लघु mbw;

	m66592_mdfy(m66592, 0, M66592_CURPIPE, ep->fअगरosel);

	m66592_ग_लिखो(m66592, M66592_ACLRM, ep->pipectr);
	m66592_ग_लिखो(m66592, 0, ep->pipectr);
	m66592_ग_लिखो(m66592, M66592_SQCLR, ep->pipectr);
	अगर (ep->use_dma) अणु
		m66592_mdfy(m66592, ep->pipक्रमागत, M66592_CURPIPE, ep->fअगरosel);

		ndelay(450);

		अगर (m66592->pdata->on_chip)
			mbw = M66592_MBW_32;
		अन्यथा
			mbw = M66592_MBW_16;

		m66592_bset(m66592, mbw, ep->fअगरosel);
	पूर्ण
पूर्ण

अटल व्योम m66592_ep_setting(काष्ठा m66592 *m66592, काष्ठा m66592_ep *ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc,
		u16 pipक्रमागत, पूर्णांक dma)
अणु
	अगर ((pipक्रमागत != 0) && dma) अणु
		अगर (m66592->num_dma == 0) अणु
			m66592->num_dma++;
			ep->use_dma = 1;
			ep->fअगरoaddr = M66592_D0FIFO;
			ep->fअगरosel = M66592_D0FIFOSEL;
			ep->fअगरoctr = M66592_D0FIFOCTR;
			ep->fअगरotrn = M66592_D0FIFOTRN;
		पूर्ण अन्यथा अगर (!m66592->pdata->on_chip && m66592->num_dma == 1) अणु
			m66592->num_dma++;
			ep->use_dma = 1;
			ep->fअगरoaddr = M66592_D1FIFO;
			ep->fअगरosel = M66592_D1FIFOSEL;
			ep->fअगरoctr = M66592_D1FIFOCTR;
			ep->fअगरotrn = M66592_D1FIFOTRN;
		पूर्ण अन्यथा अणु
			ep->use_dma = 0;
			ep->fअगरoaddr = M66592_CFIFO;
			ep->fअगरosel = M66592_CFIFOSEL;
			ep->fअगरoctr = M66592_CFIFOCTR;
			ep->fअगरotrn = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		ep->use_dma = 0;
		ep->fअगरoaddr = M66592_CFIFO;
		ep->fअगरosel = M66592_CFIFOSEL;
		ep->fअगरoctr = M66592_CFIFOCTR;
		ep->fअगरotrn = 0;
	पूर्ण

	ep->pipectr = get_pipectr_addr(pipक्रमागत);
	ep->pipक्रमागत = pipक्रमागत;
	ep->ep.maxpacket = usb_endpoपूर्णांक_maxp(desc);
	m66592->pipक्रमागत2ep[pipक्रमागत] = ep;
	m66592->epaddr2ep[desc->bEndpoपूर्णांकAddress&USB_ENDPOINT_NUMBER_MASK] = ep;
	INIT_LIST_HEAD(&ep->queue);
पूर्ण

अटल व्योम m66592_ep_release(काष्ठा m66592_ep *ep)
अणु
	काष्ठा m66592 *m66592 = ep->m66592;
	u16 pipक्रमागत = ep->pipक्रमागत;

	अगर (pipक्रमागत == 0)
		वापस;

	अगर (ep->use_dma)
		m66592->num_dma--;
	ep->pipक्रमागत = 0;
	ep->busy = 0;
	ep->use_dma = 0;
पूर्ण

अटल पूर्णांक alloc_pipe_config(काष्ठा m66592_ep *ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा m66592 *m66592 = ep->m66592;
	काष्ठा m66592_pipe_info info;
	पूर्णांक dma = 0;
	पूर्णांक *counter;
	पूर्णांक ret;

	ep->ep.desc = desc;

	BUG_ON(ep->pipक्रमागत);

	चयन (desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) अणु
	हाल USB_ENDPOINT_XFER_BULK:
		अगर (m66592->bulk >= M66592_MAX_NUM_BULK) अणु
			अगर (m66592->isochronous >= M66592_MAX_NUM_ISOC) अणु
				pr_err("bulk pipe is insufficient\n");
				वापस -ENODEV;
			पूर्ण अन्यथा अणु
				info.pipe = M66592_BASE_PIPENUM_ISOC
						+ m66592->isochronous;
				counter = &m66592->isochronous;
			पूर्ण
		पूर्ण अन्यथा अणु
			info.pipe = M66592_BASE_PIPENUM_BULK + m66592->bulk;
			counter = &m66592->bulk;
		पूर्ण
		info.type = M66592_BULK;
		dma = 1;
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		अगर (m66592->पूर्णांकerrupt >= M66592_MAX_NUM_INT) अणु
			pr_err("interrupt pipe is insufficient\n");
			वापस -ENODEV;
		पूर्ण
		info.pipe = M66592_BASE_PIPENUM_INT + m66592->पूर्णांकerrupt;
		info.type = M66592_INT;
		counter = &m66592->पूर्णांकerrupt;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (m66592->isochronous >= M66592_MAX_NUM_ISOC) अणु
			pr_err("isochronous pipe is insufficient\n");
			वापस -ENODEV;
		पूर्ण
		info.pipe = M66592_BASE_PIPENUM_ISOC + m66592->isochronous;
		info.type = M66592_ISO;
		counter = &m66592->isochronous;
		अवरोध;
	शेष:
		pr_err("unexpect xfer type\n");
		वापस -EINVAL;
	पूर्ण
	ep->type = info.type;

	info.epnum = desc->bEndpoपूर्णांकAddress & USB_ENDPOINT_NUMBER_MASK;
	info.maxpacket = usb_endpoपूर्णांक_maxp(desc);
	info.पूर्णांकerval = desc->bInterval;
	अगर (desc->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK)
		info.dir_in = 1;
	अन्यथा
		info.dir_in = 0;

	ret = pipe_buffer_setting(m66592, &info);
	अगर (ret < 0) अणु
		pr_err("pipe_buffer_setting fail\n");
		वापस ret;
	पूर्ण

	(*counter)++;
	अगर ((counter == &m66592->isochronous) && info.type == M66592_BULK)
		m66592->bulk++;

	m66592_ep_setting(m66592, ep, desc, info.pipe, dma);
	pipe_initialize(ep);

	वापस 0;
पूर्ण

अटल पूर्णांक मुक्त_pipe_config(काष्ठा m66592_ep *ep)
अणु
	काष्ठा m66592 *m66592 = ep->m66592;
	काष्ठा m66592_pipe_info info;

	info.pipe = ep->pipक्रमागत;
	info.type = ep->type;
	pipe_buffer_release(m66592, &info);
	m66592_ep_release(ep);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम pipe_irq_enable(काष्ठा m66592 *m66592, u16 pipक्रमागत)
अणु
	enable_irq_पढ़ोy(m66592, pipक्रमागत);
	enable_irq_nrdy(m66592, pipक्रमागत);
पूर्ण

अटल व्योम pipe_irq_disable(काष्ठा m66592 *m66592, u16 pipक्रमागत)
अणु
	disable_irq_पढ़ोy(m66592, pipक्रमागत);
	disable_irq_nrdy(m66592, pipक्रमागत);
पूर्ण

/* अगर complete is true, gadget driver complete function is not call */
अटल व्योम control_end(काष्ठा m66592 *m66592, अचिन्हित ccpl)
अणु
	m66592->ep[0].पूर्णांकernal_ccpl = ccpl;
	pipe_start(m66592, 0);
	m66592_bset(m66592, M66592_CCPL, M66592_DCPCTR);
पूर्ण

अटल व्योम start_ep0_ग_लिखो(काष्ठा m66592_ep *ep, काष्ठा m66592_request *req)
अणु
	काष्ठा m66592 *m66592 = ep->m66592;

	pipe_change(m66592, ep->pipक्रमागत);
	m66592_mdfy(m66592, M66592_ISEL | M66592_PIPE0,
			(M66592_ISEL | M66592_CURPIPE),
			M66592_CFIFOSEL);
	m66592_ग_लिखो(m66592, M66592_BCLR, ep->fअगरoctr);
	अगर (req->req.length == 0) अणु
		m66592_bset(m66592, M66592_BVAL, ep->fअगरoctr);
		pipe_start(m66592, 0);
		transfer_complete(ep, req, 0);
	पूर्ण अन्यथा अणु
		m66592_ग_लिखो(m66592, ~M66592_BEMP0, M66592_BEMPSTS);
		irq_ep0_ग_लिखो(ep, req);
	पूर्ण
पूर्ण

अटल व्योम start_packet_ग_लिखो(काष्ठा m66592_ep *ep, काष्ठा m66592_request *req)
अणु
	काष्ठा m66592 *m66592 = ep->m66592;
	u16 पंचांगp;

	pipe_change(m66592, ep->pipक्रमागत);
	disable_irq_empty(m66592, ep->pipक्रमागत);
	pipe_start(m66592, ep->pipक्रमागत);

	पंचांगp = m66592_पढ़ो(m66592, ep->fअगरoctr);
	अगर (unlikely((पंचांगp & M66592_FRDY) == 0))
		pipe_irq_enable(m66592, ep->pipक्रमागत);
	अन्यथा
		irq_packet_ग_लिखो(ep, req);
पूर्ण

अटल व्योम start_packet_पढ़ो(काष्ठा m66592_ep *ep, काष्ठा m66592_request *req)
अणु
	काष्ठा m66592 *m66592 = ep->m66592;
	u16 pipक्रमागत = ep->pipक्रमागत;

	अगर (ep->pipक्रमागत == 0) अणु
		m66592_mdfy(m66592, M66592_PIPE0,
				(M66592_ISEL | M66592_CURPIPE),
				M66592_CFIFOSEL);
		m66592_ग_लिखो(m66592, M66592_BCLR, ep->fअगरoctr);
		pipe_start(m66592, pipक्रमागत);
		pipe_irq_enable(m66592, pipक्रमागत);
	पूर्ण अन्यथा अणु
		अगर (ep->use_dma) अणु
			m66592_bset(m66592, M66592_TRCLR, ep->fअगरosel);
			pipe_change(m66592, pipक्रमागत);
			m66592_bset(m66592, M66592_TRENB, ep->fअगरosel);
			m66592_ग_लिखो(m66592,
				(req->req.length + ep->ep.maxpacket - 1)
					/ ep->ep.maxpacket,
				ep->fअगरotrn);
		पूर्ण
		pipe_start(m66592, pipक्रमागत);	/* trigger once */
		pipe_irq_enable(m66592, pipक्रमागत);
	पूर्ण
पूर्ण

अटल व्योम start_packet(काष्ठा m66592_ep *ep, काष्ठा m66592_request *req)
अणु
	अगर (ep->ep.desc->bEndpoपूर्णांकAddress & USB_सूची_IN)
		start_packet_ग_लिखो(ep, req);
	अन्यथा
		start_packet_पढ़ो(ep, req);
पूर्ण

अटल व्योम start_ep0(काष्ठा m66592_ep *ep, काष्ठा m66592_request *req)
अणु
	u16 ctsq;

	ctsq = m66592_पढ़ो(ep->m66592, M66592_INTSTS0) & M66592_CTSQ;

	चयन (ctsq) अणु
	हाल M66592_CS_RDDS:
		start_ep0_ग_लिखो(ep, req);
		अवरोध;
	हाल M66592_CS_WRDS:
		start_packet_पढ़ो(ep, req);
		अवरोध;

	हाल M66592_CS_WRND:
		control_end(ep->m66592, 0);
		अवरोध;
	शेष:
		pr_err("start_ep0: unexpect ctsq(%x)\n", ctsq);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम init_controller(काष्ठा m66592 *m66592)
अणु
	अचिन्हित पूर्णांक endian;

	अगर (m66592->pdata->on_chip) अणु
		अगर (m66592->pdata->endian)
			endian = 0; /* big endian */
		अन्यथा
			endian = M66592_LITTLE; /* little endian */

		m66592_bset(m66592, M66592_HSE, M66592_SYSCFG);	/* High spd */
		m66592_bclr(m66592, M66592_USBE, M66592_SYSCFG);
		m66592_bclr(m66592, M66592_DPRPU, M66592_SYSCFG);
		m66592_bset(m66592, M66592_USBE, M66592_SYSCFG);

		/* This is a workaound क्रम SH7722 2nd cut */
		m66592_bset(m66592, 0x8000, M66592_DVSTCTR);
		m66592_bset(m66592, 0x1000, M66592_TESTMODE);
		m66592_bclr(m66592, 0x8000, M66592_DVSTCTR);

		m66592_bset(m66592, M66592_INTL, M66592_INTENB1);

		m66592_ग_लिखो(m66592, 0, M66592_CFBCFG);
		m66592_ग_लिखो(m66592, 0, M66592_D0FBCFG);
		m66592_bset(m66592, endian, M66592_CFBCFG);
		m66592_bset(m66592, endian, M66592_D0FBCFG);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक घड़ी, vअगर, irq_sense;

		अगर (m66592->pdata->endian)
			endian = M66592_BIGEND; /* big endian */
		अन्यथा
			endian = 0; /* little endian */

		अगर (m66592->pdata->vअगर)
			vअगर = M66592_LDRV; /* 3.3v */
		अन्यथा
			vअगर = 0; /* 1.5v */

		चयन (m66592->pdata->xtal) अणु
		हाल M66592_PLATDATA_XTAL_12MHZ:
			घड़ी = M66592_XTAL12;
			अवरोध;
		हाल M66592_PLATDATA_XTAL_24MHZ:
			घड़ी = M66592_XTAL24;
			अवरोध;
		हाल M66592_PLATDATA_XTAL_48MHZ:
			घड़ी = M66592_XTAL48;
			अवरोध;
		शेष:
			pr_warn("m66592-udc: xtal configuration error\n");
			घड़ी = 0;
		पूर्ण

		चयन (m66592->irq_trigger) अणु
		हाल IRQF_TRIGGER_LOW:
			irq_sense = M66592_INTL;
			अवरोध;
		हाल IRQF_TRIGGER_FALLING:
			irq_sense = 0;
			अवरोध;
		शेष:
			pr_warn("m66592-udc: irq trigger config error\n");
			irq_sense = 0;
		पूर्ण

		m66592_bset(m66592,
			    (vअगर & M66592_LDRV) | (endian & M66592_BIGEND),
			    M66592_PINCFG);
		m66592_bset(m66592, M66592_HSE, M66592_SYSCFG);	/* High spd */
		m66592_mdfy(m66592, घड़ी & M66592_XTAL, M66592_XTAL,
			    M66592_SYSCFG);
		m66592_bclr(m66592, M66592_USBE, M66592_SYSCFG);
		m66592_bclr(m66592, M66592_DPRPU, M66592_SYSCFG);
		m66592_bset(m66592, M66592_USBE, M66592_SYSCFG);

		m66592_bset(m66592, M66592_XCKE, M66592_SYSCFG);

		msleep(3);

		m66592_bset(m66592, M66592_RCKE | M66592_PLLC, M66592_SYSCFG);

		msleep(1);

		m66592_bset(m66592, M66592_SCKE, M66592_SYSCFG);

		m66592_bset(m66592, irq_sense & M66592_INTL, M66592_INTENB1);
		m66592_ग_लिखो(m66592, M66592_BURST | M66592_CPU_ADR_RD_WR,
			     M66592_DMA0CFG);
	पूर्ण
पूर्ण

अटल व्योम disable_controller(काष्ठा m66592 *m66592)
अणु
	m66592_bclr(m66592, M66592_UTST, M66592_TESTMODE);
	अगर (!m66592->pdata->on_chip) अणु
		m66592_bclr(m66592, M66592_SCKE, M66592_SYSCFG);
		udelay(1);
		m66592_bclr(m66592, M66592_PLLC, M66592_SYSCFG);
		udelay(1);
		m66592_bclr(m66592, M66592_RCKE, M66592_SYSCFG);
		udelay(1);
		m66592_bclr(m66592, M66592_XCKE, M66592_SYSCFG);
	पूर्ण
पूर्ण

अटल व्योम m66592_start_xघड़ी(काष्ठा m66592 *m66592)
अणु
	u16 पंचांगp;

	अगर (!m66592->pdata->on_chip) अणु
		पंचांगp = m66592_पढ़ो(m66592, M66592_SYSCFG);
		अगर (!(पंचांगp & M66592_XCKE))
			m66592_bset(m66592, M66592_XCKE, M66592_SYSCFG);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/
अटल व्योम transfer_complete(काष्ठा m66592_ep *ep,
		काष्ठा m66592_request *req, पूर्णांक status)
__releases(m66592->lock)
__acquires(m66592->lock)
अणु
	पूर्णांक restart = 0;

	अगर (unlikely(ep->pipक्रमागत == 0)) अणु
		अगर (ep->पूर्णांकernal_ccpl) अणु
			ep->पूर्णांकernal_ccpl = 0;
			वापस;
		पूर्ण
	पूर्ण

	list_del_init(&req->queue);
	अगर (ep->m66592->gadget.speed == USB_SPEED_UNKNOWN)
		req->req.status = -ESHUTDOWN;
	अन्यथा
		req->req.status = status;

	अगर (!list_empty(&ep->queue))
		restart = 1;

	spin_unlock(&ep->m66592->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&ep->m66592->lock);

	अगर (restart) अणु
		req = list_entry(ep->queue.next, काष्ठा m66592_request, queue);
		अगर (ep->ep.desc)
			start_packet(ep, req);
	पूर्ण
पूर्ण

अटल व्योम irq_ep0_ग_लिखो(काष्ठा m66592_ep *ep, काष्ठा m66592_request *req)
अणु
	पूर्णांक i;
	u16 पंचांगp;
	अचिन्हित bufsize;
	माप_प्रकार size;
	व्योम *buf;
	u16 pipक्रमागत = ep->pipक्रमागत;
	काष्ठा m66592 *m66592 = ep->m66592;

	pipe_change(m66592, pipक्रमागत);
	m66592_bset(m66592, M66592_ISEL, ep->fअगरosel);

	i = 0;
	करो अणु
		पंचांगp = m66592_पढ़ो(m66592, ep->fअगरoctr);
		अगर (i++ > 100000) अणु
			pr_err("pipe0 is busy. maybe cpu i/o bus "
				"conflict. please power off this controller.");
			वापस;
		पूर्ण
		ndelay(1);
	पूर्ण जबतक ((पंचांगp & M66592_FRDY) == 0);

	/* prepare parameters */
	bufsize = get_buffer_size(m66592, pipक्रमागत);
	buf = req->req.buf + req->req.actual;
	size = min(bufsize, req->req.length - req->req.actual);

	/* ग_लिखो fअगरo */
	अगर (req->req.buf) अणु
		अगर (size > 0)
			m66592_ग_लिखो_fअगरo(m66592, ep, buf, size);
		अगर ((size == 0) || ((size % ep->ep.maxpacket) != 0))
			m66592_bset(m66592, M66592_BVAL, ep->fअगरoctr);
	पूर्ण

	/* update parameters */
	req->req.actual += size;

	/* check transfer finish */
	अगर ((!req->req.zero && (req->req.actual == req->req.length))
			|| (size % ep->ep.maxpacket)
			|| (size == 0)) अणु
		disable_irq_पढ़ोy(m66592, pipक्रमागत);
		disable_irq_empty(m66592, pipक्रमागत);
	पूर्ण अन्यथा अणु
		disable_irq_पढ़ोy(m66592, pipक्रमागत);
		enable_irq_empty(m66592, pipक्रमागत);
	पूर्ण
	pipe_start(m66592, pipक्रमागत);
पूर्ण

अटल व्योम irq_packet_ग_लिखो(काष्ठा m66592_ep *ep, काष्ठा m66592_request *req)
अणु
	u16 पंचांगp;
	अचिन्हित bufsize;
	माप_प्रकार size;
	व्योम *buf;
	u16 pipक्रमागत = ep->pipक्रमागत;
	काष्ठा m66592 *m66592 = ep->m66592;

	pipe_change(m66592, pipक्रमागत);
	पंचांगp = m66592_पढ़ो(m66592, ep->fअगरoctr);
	अगर (unlikely((पंचांगp & M66592_FRDY) == 0)) अणु
		pipe_stop(m66592, pipक्रमागत);
		pipe_irq_disable(m66592, pipक्रमागत);
		pr_err("write fifo not ready. pipnum=%d\n", pipक्रमागत);
		वापस;
	पूर्ण

	/* prepare parameters */
	bufsize = get_buffer_size(m66592, pipक्रमागत);
	buf = req->req.buf + req->req.actual;
	size = min(bufsize, req->req.length - req->req.actual);

	/* ग_लिखो fअगरo */
	अगर (req->req.buf) अणु
		m66592_ग_लिखो_fअगरo(m66592, ep, buf, size);
		अगर ((size == 0)
				|| ((size % ep->ep.maxpacket) != 0)
				|| ((bufsize != ep->ep.maxpacket)
					&& (bufsize > size)))
			m66592_bset(m66592, M66592_BVAL, ep->fअगरoctr);
	पूर्ण

	/* update parameters */
	req->req.actual += size;
	/* check transfer finish */
	अगर ((!req->req.zero && (req->req.actual == req->req.length))
			|| (size % ep->ep.maxpacket)
			|| (size == 0)) अणु
		disable_irq_पढ़ोy(m66592, pipक्रमागत);
		enable_irq_empty(m66592, pipक्रमागत);
	पूर्ण अन्यथा अणु
		disable_irq_empty(m66592, pipक्रमागत);
		pipe_irq_enable(m66592, pipक्रमागत);
	पूर्ण
पूर्ण

अटल व्योम irq_packet_पढ़ो(काष्ठा m66592_ep *ep, काष्ठा m66592_request *req)
अणु
	u16 पंचांगp;
	पूर्णांक rcv_len, bufsize, req_len;
	पूर्णांक size;
	व्योम *buf;
	u16 pipक्रमागत = ep->pipक्रमागत;
	काष्ठा m66592 *m66592 = ep->m66592;
	पूर्णांक finish = 0;

	pipe_change(m66592, pipक्रमागत);
	पंचांगp = m66592_पढ़ो(m66592, ep->fअगरoctr);
	अगर (unlikely((पंचांगp & M66592_FRDY) == 0)) अणु
		req->req.status = -EPIPE;
		pipe_stop(m66592, pipक्रमागत);
		pipe_irq_disable(m66592, pipक्रमागत);
		pr_err("read fifo not ready");
		वापस;
	पूर्ण

	/* prepare parameters */
	rcv_len = पंचांगp & M66592_DTLN;
	bufsize = get_buffer_size(m66592, pipक्रमागत);

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
		pipe_stop(m66592, pipक्रमागत);
		pipe_irq_disable(m66592, pipक्रमागत);
		finish = 1;
	पूर्ण

	/* पढ़ो fअगरo */
	अगर (req->req.buf) अणु
		अगर (size == 0)
			m66592_ग_लिखो(m66592, M66592_BCLR, ep->fअगरoctr);
		अन्यथा
			m66592_पढ़ो_fअगरo(m66592, ep->fअगरoaddr, buf, size);
	पूर्ण

	अगर ((ep->pipक्रमागत != 0) && finish)
		transfer_complete(ep, req, 0);
पूर्ण

अटल व्योम irq_pipe_पढ़ोy(काष्ठा m66592 *m66592, u16 status, u16 enb)
अणु
	u16 check;
	u16 pipक्रमागत;
	काष्ठा m66592_ep *ep;
	काष्ठा m66592_request *req;

	अगर ((status & M66592_BRDY0) && (enb & M66592_BRDY0)) अणु
		m66592_ग_लिखो(m66592, ~M66592_BRDY0, M66592_BRDYSTS);
		m66592_mdfy(m66592, M66592_PIPE0, M66592_CURPIPE,
				M66592_CFIFOSEL);

		ep = &m66592->ep[0];
		req = list_entry(ep->queue.next, काष्ठा m66592_request, queue);
		irq_packet_पढ़ो(ep, req);
	पूर्ण अन्यथा अणु
		क्रम (pipक्रमागत = 1; pipक्रमागत < M66592_MAX_NUM_PIPE; pipक्रमागत++) अणु
			check = 1 << pipक्रमागत;
			अगर ((status & check) && (enb & check)) अणु
				m66592_ग_लिखो(m66592, ~check, M66592_BRDYSTS);
				ep = m66592->pipक्रमागत2ep[pipक्रमागत];
				req = list_entry(ep->queue.next,
						 काष्ठा m66592_request, queue);
				अगर (ep->ep.desc->bEndpoपूर्णांकAddress & USB_सूची_IN)
					irq_packet_ग_लिखो(ep, req);
				अन्यथा
					irq_packet_पढ़ो(ep, req);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम irq_pipe_empty(काष्ठा m66592 *m66592, u16 status, u16 enb)
अणु
	u16 पंचांगp;
	u16 check;
	u16 pipक्रमागत;
	काष्ठा m66592_ep *ep;
	काष्ठा m66592_request *req;

	अगर ((status & M66592_BEMP0) && (enb & M66592_BEMP0)) अणु
		m66592_ग_लिखो(m66592, ~M66592_BEMP0, M66592_BEMPSTS);

		ep = &m66592->ep[0];
		req = list_entry(ep->queue.next, काष्ठा m66592_request, queue);
		irq_ep0_ग_लिखो(ep, req);
	पूर्ण अन्यथा अणु
		क्रम (pipक्रमागत = 1; pipक्रमागत < M66592_MAX_NUM_PIPE; pipक्रमागत++) अणु
			check = 1 << pipक्रमागत;
			अगर ((status & check) && (enb & check)) अणु
				m66592_ग_लिखो(m66592, ~check, M66592_BEMPSTS);
				पंचांगp = control_reg_get(m66592, pipक्रमागत);
				अगर ((पंचांगp & M66592_INBUFM) == 0) अणु
					disable_irq_empty(m66592, pipक्रमागत);
					pipe_irq_disable(m66592, pipक्रमागत);
					pipe_stop(m66592, pipक्रमागत);
					ep = m66592->pipक्रमागत2ep[pipक्रमागत];
					req = list_entry(ep->queue.next,
							 काष्ठा m66592_request,
							 queue);
					अगर (!list_empty(&ep->queue))
						transfer_complete(ep, req, 0);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम get_status(काष्ठा m66592 *m66592, काष्ठा usb_ctrlrequest *ctrl)
__releases(m66592->lock)
__acquires(m66592->lock)
अणु
	काष्ठा m66592_ep *ep;
	u16 pid;
	u16 status = 0;
	u16 w_index = le16_to_cpu(ctrl->wIndex);

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		status = 1 << USB_DEVICE_SELF_POWERED;
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		status = 0;
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		ep = m66592->epaddr2ep[w_index & USB_ENDPOINT_NUMBER_MASK];
		pid = control_reg_get_pid(m66592, ep->pipक्रमागत);
		अगर (pid == M66592_PID_STALL)
			status = 1 << USB_ENDPOINT_HALT;
		अन्यथा
			status = 0;
		अवरोध;
	शेष:
		pipe_stall(m66592, 0);
		वापस;		/* निकास */
	पूर्ण

	m66592->ep0_data = cpu_to_le16(status);
	m66592->ep0_req->buf = &m66592->ep0_data;
	m66592->ep0_req->length = 2;
	/* AV: what happens अगर we get called again beक्रमe that माला_लो through? */
	spin_unlock(&m66592->lock);
	m66592_queue(m66592->gadget.ep0, m66592->ep0_req, GFP_KERNEL);
	spin_lock(&m66592->lock);
पूर्ण

अटल व्योम clear_feature(काष्ठा m66592 *m66592, काष्ठा usb_ctrlrequest *ctrl)
अणु
	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		control_end(m66592, 1);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		control_end(m66592, 1);
		अवरोध;
	हाल USB_RECIP_ENDPOINT: अणु
		काष्ठा m66592_ep *ep;
		काष्ठा m66592_request *req;
		u16 w_index = le16_to_cpu(ctrl->wIndex);

		ep = m66592->epaddr2ep[w_index & USB_ENDPOINT_NUMBER_MASK];
		pipe_stop(m66592, ep->pipक्रमागत);
		control_reg_sqclr(m66592, ep->pipक्रमागत);

		control_end(m66592, 1);

		req = list_entry(ep->queue.next,
		काष्ठा m66592_request, queue);
		अगर (ep->busy) अणु
			ep->busy = 0;
			अगर (list_empty(&ep->queue))
				अवरोध;
			start_packet(ep, req);
		पूर्ण अन्यथा अगर (!list_empty(&ep->queue))
			pipe_start(m66592, ep->pipक्रमागत);
		पूर्ण
		अवरोध;
	शेष:
		pipe_stall(m66592, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम set_feature(काष्ठा m66592 *m66592, काष्ठा usb_ctrlrequest *ctrl)
अणु
	u16 पंचांगp;
	पूर्णांक समयout = 3000;

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		चयन (le16_to_cpu(ctrl->wValue)) अणु
		हाल USB_DEVICE_TEST_MODE:
			control_end(m66592, 1);
			/* Wait क्रम the completion of status stage */
			करो अणु
				पंचांगp = m66592_पढ़ो(m66592, M66592_INTSTS0) &
								M66592_CTSQ;
				udelay(1);
			पूर्ण जबतक (पंचांगp != M66592_CS_IDST && समयout-- > 0);

			अगर (पंचांगp == M66592_CS_IDST)
				m66592_bset(m66592,
					    le16_to_cpu(ctrl->wIndex >> 8),
					    M66592_TESTMODE);
			अवरोध;
		शेष:
			pipe_stall(m66592, 0);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		control_end(m66592, 1);
		अवरोध;
	हाल USB_RECIP_ENDPOINT: अणु
		काष्ठा m66592_ep *ep;
		u16 w_index = le16_to_cpu(ctrl->wIndex);

		ep = m66592->epaddr2ep[w_index & USB_ENDPOINT_NUMBER_MASK];
		pipe_stall(m66592, ep->pipक्रमागत);

		control_end(m66592, 1);
		पूर्ण
		अवरोध;
	शेष:
		pipe_stall(m66592, 0);
		अवरोध;
	पूर्ण
पूर्ण

/* अगर वापस value is true, call class driver's setup() */
अटल पूर्णांक setup_packet(काष्ठा m66592 *m66592, काष्ठा usb_ctrlrequest *ctrl)
अणु
	u16 *p = (u16 *)ctrl;
	अचिन्हित दीर्घ offset = M66592_USBREQ;
	पूर्णांक i, ret = 0;

	/* पढ़ो fअगरo */
	m66592_ग_लिखो(m66592, ~M66592_VALID, M66592_INTSTS0);

	क्रम (i = 0; i < 4; i++)
		p[i] = m66592_पढ़ो(m66592, offset + i*2);

	/* check request */
	अगर ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		चयन (ctrl->bRequest) अणु
		हाल USB_REQ_GET_STATUS:
			get_status(m66592, ctrl);
			अवरोध;
		हाल USB_REQ_CLEAR_FEATURE:
			clear_feature(m66592, ctrl);
			अवरोध;
		हाल USB_REQ_SET_FEATURE:
			set_feature(m66592, ctrl);
			अवरोध;
		शेष:
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		ret = 1;
	वापस ret;
पूर्ण

अटल व्योम m66592_update_usb_speed(काष्ठा m66592 *m66592)
अणु
	u16 speed = get_usb_speed(m66592);

	चयन (speed) अणु
	हाल M66592_HSMODE:
		m66592->gadget.speed = USB_SPEED_HIGH;
		अवरोध;
	हाल M66592_FSMODE:
		m66592->gadget.speed = USB_SPEED_FULL;
		अवरोध;
	शेष:
		m66592->gadget.speed = USB_SPEED_UNKNOWN;
		pr_err("USB speed unknown\n");
	पूर्ण
पूर्ण

अटल व्योम irq_device_state(काष्ठा m66592 *m66592)
अणु
	u16 dvsq;

	dvsq = m66592_पढ़ो(m66592, M66592_INTSTS0) & M66592_DVSQ;
	m66592_ग_लिखो(m66592, ~M66592_DVST, M66592_INTSTS0);

	अगर (dvsq == M66592_DS_DFLT) अणु	/* bus reset */
		usb_gadget_udc_reset(&m66592->gadget, m66592->driver);
		m66592_update_usb_speed(m66592);
	पूर्ण
	अगर (m66592->old_dvsq == M66592_DS_CNFG && dvsq != M66592_DS_CNFG)
		m66592_update_usb_speed(m66592);
	अगर ((dvsq == M66592_DS_CNFG || dvsq == M66592_DS_ADDS)
			&& m66592->gadget.speed == USB_SPEED_UNKNOWN)
		m66592_update_usb_speed(m66592);

	m66592->old_dvsq = dvsq;
पूर्ण

अटल व्योम irq_control_stage(काष्ठा m66592 *m66592)
__releases(m66592->lock)
__acquires(m66592->lock)
अणु
	काष्ठा usb_ctrlrequest ctrl;
	u16 ctsq;

	ctsq = m66592_पढ़ो(m66592, M66592_INTSTS0) & M66592_CTSQ;
	m66592_ग_लिखो(m66592, ~M66592_CTRT, M66592_INTSTS0);

	चयन (ctsq) अणु
	हाल M66592_CS_IDST: अणु
		काष्ठा m66592_ep *ep;
		काष्ठा m66592_request *req;
		ep = &m66592->ep[0];
		req = list_entry(ep->queue.next, काष्ठा m66592_request, queue);
		transfer_complete(ep, req, 0);
		पूर्ण
		अवरोध;

	हाल M66592_CS_RDDS:
	हाल M66592_CS_WRDS:
	हाल M66592_CS_WRND:
		अगर (setup_packet(m66592, &ctrl)) अणु
			spin_unlock(&m66592->lock);
			अगर (m66592->driver->setup(&m66592->gadget, &ctrl) < 0)
				pipe_stall(m66592, 0);
			spin_lock(&m66592->lock);
		पूर्ण
		अवरोध;
	हाल M66592_CS_RDSS:
	हाल M66592_CS_WRSS:
		control_end(m66592, 0);
		अवरोध;
	शेष:
		pr_err("ctrl_stage: unexpect ctsq(%x)\n", ctsq);
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t m66592_irq(पूर्णांक irq, व्योम *_m66592)
अणु
	काष्ठा m66592 *m66592 = _m66592;
	u16 पूर्णांकsts0;
	u16 पूर्णांकenb0;
	u16 savepipe;
	u16 mask0;

	spin_lock(&m66592->lock);

	पूर्णांकsts0 = m66592_पढ़ो(m66592, M66592_INTSTS0);
	पूर्णांकenb0 = m66592_पढ़ो(m66592, M66592_INTENB0);

	अगर (m66592->pdata->on_chip && !पूर्णांकsts0 && !पूर्णांकenb0) अणु
		/*
		 * When USB घड़ी stops, it cannot पढ़ो रेजिस्टर. Even अगर a
		 * घड़ी stops, the पूर्णांकerrupt occurs. So this driver turn on
		 * a घड़ी by this timing and करो re-पढ़ोing of रेजिस्टर.
		 */
		m66592_start_xघड़ी(m66592);
		पूर्णांकsts0 = m66592_पढ़ो(m66592, M66592_INTSTS0);
		पूर्णांकenb0 = m66592_पढ़ो(m66592, M66592_INTENB0);
	पूर्ण

	savepipe = m66592_पढ़ो(m66592, M66592_CFIFOSEL);

	mask0 = पूर्णांकsts0 & पूर्णांकenb0;
	अगर (mask0) अणु
		u16 brdysts = m66592_पढ़ो(m66592, M66592_BRDYSTS);
		u16 bempsts = m66592_पढ़ो(m66592, M66592_BEMPSTS);
		u16 brdyenb = m66592_पढ़ो(m66592, M66592_BRDYENB);
		u16 bempenb = m66592_पढ़ो(m66592, M66592_BEMPENB);

		अगर (mask0 & M66592_VBINT) अणु
			m66592_ग_लिखो(m66592,  0xffff & ~M66592_VBINT,
					M66592_INTSTS0);
			m66592_start_xघड़ी(m66592);

			/* start vbus sampling */
			m66592->old_vbus = m66592_पढ़ो(m66592, M66592_INTSTS0)
					& M66592_VBSTS;
			m66592->scount = M66592_MAX_SAMPLING;

			mod_समयr(&m66592->समयr,
					jअगरfies + msecs_to_jअगरfies(50));
		पूर्ण
		अगर (पूर्णांकsts0 & M66592_DVSQ)
			irq_device_state(m66592);

		अगर ((पूर्णांकsts0 & M66592_BRDY) && (पूर्णांकenb0 & M66592_BRDYE)
				&& (brdysts & brdyenb)) अणु
			irq_pipe_पढ़ोy(m66592, brdysts, brdyenb);
		पूर्ण
		अगर ((पूर्णांकsts0 & M66592_BEMP) && (पूर्णांकenb0 & M66592_BEMPE)
				&& (bempsts & bempenb)) अणु
			irq_pipe_empty(m66592, bempsts, bempenb);
		पूर्ण

		अगर (पूर्णांकsts0 & M66592_CTRT)
			irq_control_stage(m66592);
	पूर्ण

	m66592_ग_लिखो(m66592, savepipe, M66592_CFIFOSEL);

	spin_unlock(&m66592->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम m66592_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा m66592 *m66592 = from_समयr(m66592, t, समयr);
	अचिन्हित दीर्घ flags;
	u16 पंचांगp;

	spin_lock_irqsave(&m66592->lock, flags);
	पंचांगp = m66592_पढ़ो(m66592, M66592_SYSCFG);
	अगर (!(पंचांगp & M66592_RCKE)) अणु
		m66592_bset(m66592, M66592_RCKE | M66592_PLLC, M66592_SYSCFG);
		udelay(10);
		m66592_bset(m66592, M66592_SCKE, M66592_SYSCFG);
	पूर्ण
	अगर (m66592->scount > 0) अणु
		पंचांगp = m66592_पढ़ो(m66592, M66592_INTSTS0) & M66592_VBSTS;
		अगर (पंचांगp == m66592->old_vbus) अणु
			m66592->scount--;
			अगर (m66592->scount == 0) अणु
				अगर (पंचांगp == M66592_VBSTS)
					m66592_usb_connect(m66592);
				अन्यथा
					m66592_usb_disconnect(m66592);
			पूर्ण अन्यथा अणु
				mod_समयr(&m66592->समयr,
					jअगरfies + msecs_to_jअगरfies(50));
			पूर्ण
		पूर्ण अन्यथा अणु
			m66592->scount = M66592_MAX_SAMPLING;
			m66592->old_vbus = पंचांगp;
			mod_समयr(&m66592->समयr,
					jअगरfies + msecs_to_jअगरfies(50));
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&m66592->lock, flags);
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक m66592_enable(काष्ठा usb_ep *_ep,
			 स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा m66592_ep *ep;

	ep = container_of(_ep, काष्ठा m66592_ep, ep);
	वापस alloc_pipe_config(ep, desc);
पूर्ण

अटल पूर्णांक m66592_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा m66592_ep *ep;
	काष्ठा m66592_request *req;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा m66592_ep, ep);
	BUG_ON(!ep);

	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next, काष्ठा m66592_request, queue);
		spin_lock_irqsave(&ep->m66592->lock, flags);
		transfer_complete(ep, req, -ECONNRESET);
		spin_unlock_irqrestore(&ep->m66592->lock, flags);
	पूर्ण

	pipe_irq_disable(ep->m66592, ep->pipक्रमागत);
	वापस मुक्त_pipe_config(ep);
पूर्ण

अटल काष्ठा usb_request *m66592_alloc_request(काष्ठा usb_ep *_ep,
						gfp_t gfp_flags)
अणु
	काष्ठा m66592_request *req;

	req = kzalloc(माप(काष्ठा m66592_request), gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

अटल व्योम m66592_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा m66592_request *req;

	req = container_of(_req, काष्ठा m66592_request, req);
	kमुक्त(req);
पूर्ण

अटल पूर्णांक m66592_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
			gfp_t gfp_flags)
अणु
	काष्ठा m66592_ep *ep;
	काष्ठा m66592_request *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक request = 0;

	ep = container_of(_ep, काष्ठा m66592_ep, ep);
	req = container_of(_req, काष्ठा m66592_request, req);

	अगर (ep->m66592->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&ep->m66592->lock, flags);

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

	spin_unlock_irqrestore(&ep->m66592->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक m66592_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा m66592_ep *ep;
	काष्ठा m66592_request *req;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा m66592_ep, ep);
	req = container_of(_req, काष्ठा m66592_request, req);

	spin_lock_irqsave(&ep->m66592->lock, flags);
	अगर (!list_empty(&ep->queue))
		transfer_complete(ep, req, -ECONNRESET);
	spin_unlock_irqrestore(&ep->m66592->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक m66592_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा m66592_ep *ep = container_of(_ep, काष्ठा m66592_ep, ep);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&ep->m66592->lock, flags);
	अगर (!list_empty(&ep->queue)) अणु
		ret = -EAGAIN;
	पूर्ण अन्यथा अगर (value) अणु
		ep->busy = 1;
		pipe_stall(ep->m66592, ep->pipक्रमागत);
	पूर्ण अन्यथा अणु
		ep->busy = 0;
		pipe_stop(ep->m66592, ep->pipक्रमागत);
	पूर्ण
	spin_unlock_irqrestore(&ep->m66592->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम m66592_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा m66592_ep *ep;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा m66592_ep, ep);
	spin_lock_irqsave(&ep->m66592->lock, flags);
	अगर (list_empty(&ep->queue) && !ep->busy) अणु
		pipe_stop(ep->m66592, ep->pipक्रमागत);
		m66592_bclr(ep->m66592, M66592_BCLR, ep->fअगरoctr);
	पूर्ण
	spin_unlock_irqrestore(&ep->m66592->lock, flags);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops m66592_ep_ops = अणु
	.enable		= m66592_enable,
	.disable	= m66592_disable,

	.alloc_request	= m66592_alloc_request,
	.मुक्त_request	= m66592_मुक्त_request,

	.queue		= m66592_queue,
	.dequeue	= m66592_dequeue,

	.set_halt	= m66592_set_halt,
	.fअगरo_flush	= m66592_fअगरo_flush,
पूर्ण;

/*-------------------------------------------------------------------------*/
अटल पूर्णांक m66592_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा m66592 *m66592 = to_m66592(g);

	/* hook up the driver */
	driver->driver.bus = शून्य;
	m66592->driver = driver;

	m66592_bset(m66592, M66592_VBSE | M66592_URST, M66592_INTENB0);
	अगर (m66592_पढ़ो(m66592, M66592_INTSTS0) & M66592_VBSTS) अणु
		m66592_start_xघड़ी(m66592);
		/* start vbus sampling */
		m66592->old_vbus = m66592_पढ़ो(m66592,
					 M66592_INTSTS0) & M66592_VBSTS;
		m66592->scount = M66592_MAX_SAMPLING;
		mod_समयr(&m66592->समयr, jअगरfies + msecs_to_jअगरfies(50));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक m66592_udc_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा m66592 *m66592 = to_m66592(g);

	m66592_bclr(m66592, M66592_VBSE | M66592_URST, M66592_INTENB0);

	init_controller(m66592);
	disable_controller(m66592);

	m66592->driver = शून्य;

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल पूर्णांक m66592_get_frame(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा m66592 *m66592 = gadget_to_m66592(_gadget);
	वापस m66592_पढ़ो(m66592, M66592_FRMNUM) & 0x03FF;
पूर्ण

अटल पूर्णांक m66592_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा m66592 *m66592 = gadget_to_m66592(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&m66592->lock, flags);
	अगर (is_on)
		m66592_bset(m66592, M66592_DPRPU, M66592_SYSCFG);
	अन्यथा
		m66592_bclr(m66592, M66592_DPRPU, M66592_SYSCFG);
	spin_unlock_irqrestore(&m66592->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops m66592_gadget_ops = अणु
	.get_frame		= m66592_get_frame,
	.udc_start		= m66592_udc_start,
	.udc_stop		= m66592_udc_stop,
	.pullup			= m66592_pullup,
पूर्ण;

अटल पूर्णांक m66592_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा m66592		*m66592 = platक्रमm_get_drvdata(pdev);

	usb_del_gadget_udc(&m66592->gadget);

	del_समयr_sync(&m66592->समयr);
	iounmap(m66592->reg);
	मुक्त_irq(platक्रमm_get_irq(pdev, 0), m66592);
	m66592_मुक्त_request(&m66592->ep[0].ep, m66592->ep0_req);
	अगर (m66592->pdata->on_chip) अणु
		clk_disable(m66592->clk);
		clk_put(m66592->clk);
	पूर्ण
	kमुक्त(m66592);
	वापस 0;
पूर्ण

अटल व्योम nop_completion(काष्ठा usb_ep *ep, काष्ठा usb_request *r)
अणु
पूर्ण

अटल पूर्णांक m66592_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res, *ires;
	व्योम __iomem *reg = शून्य;
	काष्ठा m66592 *m66592 = शून्य;
	अक्षर clk_name[8];
	पूर्णांक ret = 0;
	पूर्णांक i;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -ENODEV;
		pr_err("platform_get_resource error.\n");
		जाओ clean_up;
	पूर्ण

	ires = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!ires) अणु
		ret = -ENODEV;
		dev_err(&pdev->dev,
			"platform_get_resource IORESOURCE_IRQ error.\n");
		जाओ clean_up;
	पूर्ण

	reg = ioremap(res->start, resource_size(res));
	अगर (reg == शून्य) अणु
		ret = -ENOMEM;
		pr_err("ioremap error.\n");
		जाओ clean_up;
	पूर्ण

	अगर (dev_get_platdata(&pdev->dev) == शून्य) अणु
		dev_err(&pdev->dev, "no platform data\n");
		ret = -ENODEV;
		जाओ clean_up;
	पूर्ण

	/* initialize ucd */
	m66592 = kzalloc(माप(काष्ठा m66592), GFP_KERNEL);
	अगर (m66592 == शून्य) अणु
		ret = -ENOMEM;
		जाओ clean_up;
	पूर्ण

	m66592->pdata = dev_get_platdata(&pdev->dev);
	m66592->irq_trigger = ires->flags & IRQF_TRIGGER_MASK;

	spin_lock_init(&m66592->lock);
	platक्रमm_set_drvdata(pdev, m66592);

	m66592->gadget.ops = &m66592_gadget_ops;
	m66592->gadget.max_speed = USB_SPEED_HIGH;
	m66592->gadget.name = udc_name;

	समयr_setup(&m66592->समयr, m66592_समयr, 0);
	m66592->reg = reg;

	ret = request_irq(ires->start, m66592_irq, IRQF_SHARED,
			udc_name, m66592);
	अगर (ret < 0) अणु
		pr_err("request_irq error (%d)\n", ret);
		जाओ clean_up;
	पूर्ण

	अगर (m66592->pdata->on_chip) अणु
		snम_लिखो(clk_name, माप(clk_name), "usbf%d", pdev->id);
		m66592->clk = clk_get(&pdev->dev, clk_name);
		अगर (IS_ERR(m66592->clk)) अणु
			dev_err(&pdev->dev, "cannot get clock \"%s\"\n",
				clk_name);
			ret = PTR_ERR(m66592->clk);
			जाओ clean_up2;
		पूर्ण
		clk_enable(m66592->clk);
	पूर्ण

	INIT_LIST_HEAD(&m66592->gadget.ep_list);
	m66592->gadget.ep0 = &m66592->ep[0].ep;
	INIT_LIST_HEAD(&m66592->gadget.ep0->ep_list);
	क्रम (i = 0; i < M66592_MAX_NUM_PIPE; i++) अणु
		काष्ठा m66592_ep *ep = &m66592->ep[i];

		अगर (i != 0) अणु
			INIT_LIST_HEAD(&m66592->ep[i].ep.ep_list);
			list_add_tail(&m66592->ep[i].ep.ep_list,
					&m66592->gadget.ep_list);
		पूर्ण
		ep->m66592 = m66592;
		INIT_LIST_HEAD(&ep->queue);
		ep->ep.name = m66592_ep_name[i];
		ep->ep.ops = &m66592_ep_ops;
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
	usb_ep_set_maxpacket_limit(&m66592->ep[0].ep, 64);
	m66592->ep[0].pipक्रमागत = 0;
	m66592->ep[0].fअगरoaddr = M66592_CFIFO;
	m66592->ep[0].fअगरosel = M66592_CFIFOSEL;
	m66592->ep[0].fअगरoctr = M66592_CFIFOCTR;
	m66592->ep[0].fअगरotrn = 0;
	m66592->ep[0].pipectr = get_pipectr_addr(0);
	m66592->pipक्रमागत2ep[0] = &m66592->ep[0];
	m66592->epaddr2ep[0] = &m66592->ep[0];

	m66592->ep0_req = m66592_alloc_request(&m66592->ep[0].ep, GFP_KERNEL);
	अगर (m66592->ep0_req == शून्य) अणु
		ret = -ENOMEM;
		जाओ clean_up3;
	पूर्ण
	m66592->ep0_req->complete = nop_completion;

	init_controller(m66592);

	ret = usb_add_gadget_udc(&pdev->dev, &m66592->gadget);
	अगर (ret)
		जाओ err_add_udc;

	dev_info(&pdev->dev, "version %s\n", DRIVER_VERSION);
	वापस 0;

err_add_udc:
	m66592_मुक्त_request(&m66592->ep[0].ep, m66592->ep0_req);
	m66592->ep0_req = शून्य;
clean_up3:
	अगर (m66592->pdata->on_chip) अणु
		clk_disable(m66592->clk);
		clk_put(m66592->clk);
	पूर्ण
clean_up2:
	मुक्त_irq(ires->start, m66592);
clean_up:
	अगर (m66592) अणु
		अगर (m66592->ep0_req)
			m66592_मुक्त_request(&m66592->ep[0].ep, m66592->ep0_req);
		kमुक्त(m66592);
	पूर्ण
	अगर (reg)
		iounmap(reg);

	वापस ret;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल काष्ठा platक्रमm_driver m66592_driver = अणु
	.हटाओ =	m66592_हटाओ,
	.driver		= अणु
		.name =	udc_name,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(m66592_driver, m66592_probe);
