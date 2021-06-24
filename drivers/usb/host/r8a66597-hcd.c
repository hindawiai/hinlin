<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R8A66597 HCD (Host Controller Driver)
 *
 * Copyright (C) 2006-2007 Renesas Solutions Corp.
 * Portions Copyright (C) 2004 Psion Teklogix (क्रम NetBook PRO)
 * Portions Copyright (C) 2004-2005 David Brownell
 * Portions Copyright (C) 1999 Roman Weissgaerber
 *
 * Author : Yoshihiro Shimoda <yoshihiro.shimoda.uh@renesas.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "r8a66597.h"

MODULE_DESCRIPTION("R8A66597 USB Host Controller Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yoshihiro Shimoda");
MODULE_ALIAS("platform:r8a66597_hcd");

#घोषणा DRIVER_VERSION	"2009-05-26"

अटल स्थिर अक्षर hcd_name[] = "r8a66597_hcd";

अटल व्योम packet_ग_लिखो(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत);
अटल पूर्णांक r8a66597_get_frame(काष्ठा usb_hcd *hcd);

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम enable_pipe_irq(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत,
			    अचिन्हित दीर्घ reg)
अणु
	u16 पंचांगp;

	पंचांगp = r8a66597_पढ़ो(r8a66597, INTENB0);
	r8a66597_bclr(r8a66597, BEMPE | NRDYE | BRDYE, INTENB0);
	r8a66597_bset(r8a66597, 1 << pipक्रमागत, reg);
	r8a66597_ग_लिखो(r8a66597, पंचांगp, INTENB0);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम disable_pipe_irq(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत,
			     अचिन्हित दीर्घ reg)
अणु
	u16 पंचांगp;

	पंचांगp = r8a66597_पढ़ो(r8a66597, INTENB0);
	r8a66597_bclr(r8a66597, BEMPE | NRDYE | BRDYE, INTENB0);
	r8a66597_bclr(r8a66597, 1 << pipक्रमागत, reg);
	r8a66597_ग_लिखो(r8a66597, पंचांगp, INTENB0);
पूर्ण

अटल व्योम set_devadd_reg(काष्ठा r8a66597 *r8a66597, u8 r8a66597_address,
			   u16 usbspd, u8 upphub, u8 hubport, पूर्णांक port)
अणु
	u16 val;
	अचिन्हित दीर्घ devadd_reg = get_devadd_addr(r8a66597_address);

	val = (upphub << 11) | (hubport << 8) | (usbspd << 6) | (port & 0x0001);
	r8a66597_ग_लिखो(r8a66597, val, devadd_reg);
पूर्ण

अटल पूर्णांक r8a66597_घड़ी_enable(काष्ठा r8a66597 *r8a66597)
अणु
	u16 पंचांगp;
	पूर्णांक i = 0;

	अगर (r8a66597->pdata->on_chip) अणु
		clk_prepare_enable(r8a66597->clk);
		करो अणु
			r8a66597_ग_लिखो(r8a66597, SCKE, SYSCFG0);
			पंचांगp = r8a66597_पढ़ो(r8a66597, SYSCFG0);
			अगर (i++ > 1000) अणु
				prपूर्णांकk(KERN_ERR "r8a66597: reg access fail.\n");
				वापस -ENXIO;
			पूर्ण
		पूर्ण जबतक ((पंचांगp & SCKE) != SCKE);
		r8a66597_ग_लिखो(r8a66597, 0x04, 0x02);
	पूर्ण अन्यथा अणु
		करो अणु
			r8a66597_ग_लिखो(r8a66597, USBE, SYSCFG0);
			पंचांगp = r8a66597_पढ़ो(r8a66597, SYSCFG0);
			अगर (i++ > 1000) अणु
				prपूर्णांकk(KERN_ERR "r8a66597: reg access fail.\n");
				वापस -ENXIO;
			पूर्ण
		पूर्ण जबतक ((पंचांगp & USBE) != USBE);
		r8a66597_bclr(r8a66597, USBE, SYSCFG0);
		r8a66597_mdfy(r8a66597, get_xtal_from_pdata(r8a66597->pdata),
			      XTAL, SYSCFG0);

		i = 0;
		r8a66597_bset(r8a66597, XCKE, SYSCFG0);
		करो अणु
			msleep(1);
			पंचांगp = r8a66597_पढ़ो(r8a66597, SYSCFG0);
			अगर (i++ > 500) अणु
				prपूर्णांकk(KERN_ERR "r8a66597: reg access fail.\n");
				वापस -ENXIO;
			पूर्ण
		पूर्ण जबतक ((पंचांगp & SCKE) != SCKE);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम r8a66597_घड़ी_disable(काष्ठा r8a66597 *r8a66597)
अणु
	r8a66597_bclr(r8a66597, SCKE, SYSCFG0);
	udelay(1);

	अगर (r8a66597->pdata->on_chip) अणु
		clk_disable_unprepare(r8a66597->clk);
	पूर्ण अन्यथा अणु
		r8a66597_bclr(r8a66597, PLLC, SYSCFG0);
		r8a66597_bclr(r8a66597, XCKE, SYSCFG0);
		r8a66597_bclr(r8a66597, USBE, SYSCFG0);
	पूर्ण
पूर्ण

अटल व्योम r8a66597_enable_port(काष्ठा r8a66597 *r8a66597, पूर्णांक port)
अणु
	u16 val;

	val = port ? DRPD : DCFM | DRPD;
	r8a66597_bset(r8a66597, val, get_syscfg_reg(port));
	r8a66597_bset(r8a66597, HSE, get_syscfg_reg(port));

	r8a66597_ग_लिखो(r8a66597, BURST | CPU_ADR_RD_WR, get_dmacfg_reg(port));
	r8a66597_bclr(r8a66597, DTCHE, get_पूर्णांकenb_reg(port));
	r8a66597_bset(r8a66597, ATTCHE, get_पूर्णांकenb_reg(port));
पूर्ण

अटल व्योम r8a66597_disable_port(काष्ठा r8a66597 *r8a66597, पूर्णांक port)
अणु
	u16 val, पंचांगp;

	r8a66597_ग_लिखो(r8a66597, 0, get_पूर्णांकenb_reg(port));
	r8a66597_ग_लिखो(r8a66597, 0, get_पूर्णांकsts_reg(port));

	r8a66597_port_घातer(r8a66597, port, 0);

	करो अणु
		पंचांगp = r8a66597_पढ़ो(r8a66597, SOFCFG) & EDGESTS;
		udelay(640);
	पूर्ण जबतक (पंचांगp == EDGESTS);

	val = port ? DRPD : DCFM | DRPD;
	r8a66597_bclr(r8a66597, val, get_syscfg_reg(port));
	r8a66597_bclr(r8a66597, HSE, get_syscfg_reg(port));
पूर्ण

अटल पूर्णांक enable_controller(काष्ठा r8a66597 *r8a66597)
अणु
	पूर्णांक ret, port;
	u16 vअगर = r8a66597->pdata->vअगर ? LDRV : 0;
	u16 irq_sense = r8a66597->irq_sense_low ? INTL : 0;
	u16 endian = r8a66597->pdata->endian ? BIGEND : 0;

	ret = r8a66597_घड़ी_enable(r8a66597);
	अगर (ret < 0)
		वापस ret;

	r8a66597_bset(r8a66597, vअगर & LDRV, PINCFG);
	r8a66597_bset(r8a66597, USBE, SYSCFG0);

	r8a66597_bset(r8a66597, BEMPE | NRDYE | BRDYE, INTENB0);
	r8a66597_bset(r8a66597, irq_sense & INTL, SOFCFG);
	r8a66597_bset(r8a66597, BRDY0, BRDYENB);
	r8a66597_bset(r8a66597, BEMP0, BEMPENB);

	r8a66597_bset(r8a66597, endian & BIGEND, CFIFOSEL);
	r8a66597_bset(r8a66597, endian & BIGEND, D0FIFOSEL);
	r8a66597_bset(r8a66597, endian & BIGEND, D1FIFOSEL);
	r8a66597_bset(r8a66597, TRNENSEL, SOFCFG);

	r8a66597_bset(r8a66597, SIGNE | SACKE, INTENB1);

	क्रम (port = 0; port < r8a66597->max_root_hub; port++)
		r8a66597_enable_port(r8a66597, port);

	वापस 0;
पूर्ण

अटल व्योम disable_controller(काष्ठा r8a66597 *r8a66597)
अणु
	पूर्णांक port;

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

	क्रम (port = 0; port < r8a66597->max_root_hub; port++)
		r8a66597_disable_port(r8a66597, port);

	r8a66597_घड़ी_disable(r8a66597);
पूर्ण

अटल पूर्णांक get_parent_r8a66597_address(काष्ठा r8a66597 *r8a66597,
				       काष्ठा usb_device *udev)
अणु
	काष्ठा r8a66597_device *dev;

	अगर (udev->parent && udev->parent->devnum != 1)
		udev = udev->parent;

	dev = dev_get_drvdata(&udev->dev);
	अगर (dev)
		वापस dev->address;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक is_child_device(अक्षर *devpath)
अणु
	वापस (devpath[2] ? 1 : 0);
पूर्ण

अटल पूर्णांक is_hub_limit(अक्षर *devpath)
अणु
	वापस ((म_माप(devpath) >= 4) ? 1 : 0);
पूर्ण

अटल व्योम get_port_number(काष्ठा r8a66597 *r8a66597,
			    अक्षर *devpath, u16 *root_port, u16 *hub_port)
अणु
	अगर (root_port) अणु
		*root_port = (devpath[0] & 0x0F) - 1;
		अगर (*root_port >= r8a66597->max_root_hub)
			prपूर्णांकk(KERN_ERR "r8a66597: Illegal root port number.\n");
	पूर्ण
	अगर (hub_port)
		*hub_port = devpath[2] & 0x0F;
पूर्ण

अटल u16 get_r8a66597_usb_speed(क्रमागत usb_device_speed speed)
अणु
	u16 usbspd = 0;

	चयन (speed) अणु
	हाल USB_SPEED_LOW:
		usbspd = LSMODE;
		अवरोध;
	हाल USB_SPEED_FULL:
		usbspd = FSMODE;
		अवरोध;
	हाल USB_SPEED_HIGH:
		usbspd = HSMODE;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "r8a66597: unknown speed\n");
		अवरोध;
	पूर्ण

	वापस usbspd;
पूर्ण

अटल व्योम set_child_connect_map(काष्ठा r8a66597 *r8a66597, पूर्णांक address)
अणु
	पूर्णांक idx;

	idx = address / 32;
	r8a66597->child_connect_map[idx] |= 1 << (address % 32);
पूर्ण

अटल व्योम put_child_connect_map(काष्ठा r8a66597 *r8a66597, पूर्णांक address)
अणु
	पूर्णांक idx;

	idx = address / 32;
	r8a66597->child_connect_map[idx] &= ~(1 << (address % 32));
पूर्ण

अटल व्योम set_pipe_reg_addr(काष्ठा r8a66597_pipe *pipe, u8 dma_ch)
अणु
	u16 pipक्रमागत = pipe->info.pipक्रमागत;
	स्थिर अचिन्हित दीर्घ fअगरoaddr[] = अणुD0FIFO, D1FIFO, CFIFOपूर्ण;
	स्थिर अचिन्हित दीर्घ fअगरosel[] = अणुD0FIFOSEL, D1FIFOSEL, CFIFOSELपूर्ण;
	स्थिर अचिन्हित दीर्घ fअगरoctr[] = अणुD0FIFOCTR, D1FIFOCTR, CFIFOCTRपूर्ण;

	अगर (dma_ch > R8A66597_PIPE_NO_DMA)	/* dma fअगरo not use? */
		dma_ch = R8A66597_PIPE_NO_DMA;

	pipe->fअगरoaddr = fअगरoaddr[dma_ch];
	pipe->fअगरosel = fअगरosel[dma_ch];
	pipe->fअगरoctr = fअगरoctr[dma_ch];

	अगर (pipक्रमागत == 0)
		pipe->pipectr = DCPCTR;
	अन्यथा
		pipe->pipectr = get_pipectr_addr(pipक्रमागत);

	अगर (check_bulk_or_isoc(pipक्रमागत)) अणु
		pipe->pipetre = get_pipetre_addr(pipक्रमागत);
		pipe->pipetrn = get_pipetrn_addr(pipक्रमागत);
	पूर्ण अन्यथा अणु
		pipe->pipetre = 0;
		pipe->pipetrn = 0;
	पूर्ण
पूर्ण

अटल काष्ठा r8a66597_device *
get_urb_to_r8a66597_dev(काष्ठा r8a66597 *r8a66597, काष्ठा urb *urb)
अणु
	अगर (usb_pipedevice(urb->pipe) == 0)
		वापस &r8a66597->device0;

	वापस dev_get_drvdata(&urb->dev->dev);
पूर्ण

अटल पूर्णांक make_r8a66597_device(काष्ठा r8a66597 *r8a66597,
				काष्ठा urb *urb, u8 addr)
अणु
	काष्ठा r8a66597_device *dev;
	पूर्णांक usb_address = urb->setup_packet[2];	/* urb->pipe is address 0 */

	dev = kzalloc(माप(काष्ठा r8a66597_device), GFP_ATOMIC);
	अगर (dev == शून्य)
		वापस -ENOMEM;

	dev_set_drvdata(&urb->dev->dev, dev);
	dev->udev = urb->dev;
	dev->address = addr;
	dev->usb_address = usb_address;
	dev->state = USB_STATE_ADDRESS;
	dev->ep_in_toggle = 0;
	dev->ep_out_toggle = 0;
	INIT_LIST_HEAD(&dev->device_list);
	list_add_tail(&dev->device_list, &r8a66597->child_device);

	get_port_number(r8a66597, urb->dev->devpath,
			&dev->root_port, &dev->hub_port);
	अगर (!is_child_device(urb->dev->devpath))
		r8a66597->root_hub[dev->root_port].dev = dev;

	set_devadd_reg(r8a66597, dev->address,
		       get_r8a66597_usb_speed(urb->dev->speed),
		       get_parent_r8a66597_address(r8a66597, urb->dev),
		       dev->hub_port, dev->root_port);

	वापस 0;
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल u8 alloc_usb_address(काष्ठा r8a66597 *r8a66597, काष्ठा urb *urb)
अणु
	u8 addr;	/* R8A66597's address */
	काष्ठा r8a66597_device *dev;

	अगर (is_hub_limit(urb->dev->devpath)) अणु
		dev_err(&urb->dev->dev, "External hub limit reached.\n");
		वापस 0;
	पूर्ण

	dev = get_urb_to_r8a66597_dev(r8a66597, urb);
	अगर (dev && dev->state >= USB_STATE_ADDRESS)
		वापस dev->address;

	क्रम (addr = 1; addr <= R8A66597_MAX_DEVICE; addr++) अणु
		अगर (r8a66597->address_map & (1 << addr))
			जारी;

		dev_dbg(&urb->dev->dev, "alloc_address: r8a66597_addr=%d\n", addr);
		r8a66597->address_map |= 1 << addr;

		अगर (make_r8a66597_device(r8a66597, urb, addr) < 0)
			वापस 0;

		वापस addr;
	पूर्ण

	dev_err(&urb->dev->dev,
		"cannot communicate with a USB device more than 10.(%x)\n",
		r8a66597->address_map);

	वापस 0;
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम मुक्त_usb_address(काष्ठा r8a66597 *r8a66597,
			     काष्ठा r8a66597_device *dev, पूर्णांक reset)
अणु
	पूर्णांक port;

	अगर (!dev)
		वापस;

	dev_dbg(&dev->udev->dev, "free_addr: addr=%d\n", dev->address);

	dev->state = USB_STATE_DEFAULT;
	r8a66597->address_map &= ~(1 << dev->address);
	dev->address = 0;
	/*
	 * Only when resetting USB, it is necessary to erase drvdata. When
	 * a usb device with usb hub is disconnect, "dev->udev" is alपढ़ोy
	 * मुक्तd on usb_desconnect(). So we cannot access the data.
	 */
	अगर (reset)
		dev_set_drvdata(&dev->udev->dev, शून्य);
	list_del(&dev->device_list);
	kमुक्त(dev);

	क्रम (port = 0; port < r8a66597->max_root_hub; port++) अणु
		अगर (r8a66597->root_hub[port].dev == dev) अणु
			r8a66597->root_hub[port].dev = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम r8a66597_reg_रुको(काष्ठा r8a66597 *r8a66597, अचिन्हित दीर्घ reg,
			      u16 mask, u16 loop)
अणु
	u16 पंचांगp;
	पूर्णांक i = 0;

	करो अणु
		पंचांगp = r8a66597_पढ़ो(r8a66597, reg);
		अगर (i++ > 1000000) अणु
			prपूर्णांकk(KERN_ERR "r8a66597: register%lx, loop %x "
			       "is timeout\n", reg, loop);
			अवरोध;
		पूर्ण
		ndelay(1);
	पूर्ण जबतक ((पंचांगp & mask) != loop);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम pipe_start(काष्ठा r8a66597 *r8a66597, काष्ठा r8a66597_pipe *pipe)
अणु
	u16 पंचांगp;

	पंचांगp = r8a66597_पढ़ो(r8a66597, pipe->pipectr) & PID;
	अगर ((pipe->info.pipक्रमागत != 0) & ((पंचांगp & PID_STALL) != 0)) /* stall? */
		r8a66597_mdfy(r8a66597, PID_NAK, PID, pipe->pipectr);
	r8a66597_mdfy(r8a66597, PID_BUF, PID, pipe->pipectr);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम pipe_stop(काष्ठा r8a66597 *r8a66597, काष्ठा r8a66597_pipe *pipe)
अणु
	u16 पंचांगp;

	पंचांगp = r8a66597_पढ़ो(r8a66597, pipe->pipectr) & PID;
	अगर ((पंचांगp & PID_STALL11) != PID_STALL11)	/* क्रमce stall? */
		r8a66597_mdfy(r8a66597, PID_STALL, PID, pipe->pipectr);
	r8a66597_mdfy(r8a66597, PID_NAK, PID, pipe->pipectr);
	r8a66597_reg_रुको(r8a66597, pipe->pipectr, PBUSY, 0);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम clear_all_buffer(काष्ठा r8a66597 *r8a66597,
			     काष्ठा r8a66597_pipe *pipe)
अणु
	अगर (!pipe || pipe->info.pipक्रमागत == 0)
		वापस;

	pipe_stop(r8a66597, pipe);
	r8a66597_bset(r8a66597, ACLRM, pipe->pipectr);
	r8a66597_पढ़ो(r8a66597, pipe->pipectr);
	r8a66597_पढ़ो(r8a66597, pipe->pipectr);
	r8a66597_पढ़ो(r8a66597, pipe->pipectr);
	r8a66597_bclr(r8a66597, ACLRM, pipe->pipectr);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम r8a66597_pipe_toggle(काष्ठा r8a66597 *r8a66597,
				 काष्ठा r8a66597_pipe *pipe, पूर्णांक toggle)
अणु
	अगर (toggle)
		r8a66597_bset(r8a66597, SQSET, pipe->pipectr);
	अन्यथा
		r8a66597_bset(r8a66597, SQCLR, pipe->pipectr);
पूर्ण

अटल अंतरभूत अचिन्हित लघु mbw_value(काष्ठा r8a66597 *r8a66597)
अणु
	अगर (r8a66597->pdata->on_chip)
		वापस MBW_32;
	अन्यथा
		वापस MBW_16;
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल अंतरभूत व्योम cfअगरo_change(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	अचिन्हित लघु mbw = mbw_value(r8a66597);

	r8a66597_mdfy(r8a66597, mbw | pipक्रमागत, mbw | CURPIPE, CFIFOSEL);
	r8a66597_reg_रुको(r8a66597, CFIFOSEL, CURPIPE, pipक्रमागत);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल अंतरभूत व्योम fअगरo_change_from_pipe(काष्ठा r8a66597 *r8a66597,
					 काष्ठा r8a66597_pipe *pipe)
अणु
	अचिन्हित लघु mbw = mbw_value(r8a66597);

	cfअगरo_change(r8a66597, 0);
	r8a66597_mdfy(r8a66597, mbw | 0, mbw | CURPIPE, D0FIFOSEL);
	r8a66597_mdfy(r8a66597, mbw | 0, mbw | CURPIPE, D1FIFOSEL);

	r8a66597_mdfy(r8a66597, mbw | pipe->info.pipक्रमागत, mbw | CURPIPE,
		      pipe->fअगरosel);
	r8a66597_reg_रुको(r8a66597, pipe->fअगरosel, CURPIPE, pipe->info.pipक्रमागत);
पूर्ण

अटल u16 r8a66597_get_pipक्रमागत(काष्ठा urb *urb, काष्ठा usb_host_endpoपूर्णांक *hep)
अणु
	काष्ठा r8a66597_pipe *pipe = hep->hcpriv;

	अगर (usb_pipeendpoपूर्णांक(urb->pipe) == 0)
		वापस 0;
	अन्यथा
		वापस pipe->info.pipक्रमागत;
पूर्ण

अटल u16 get_urb_to_r8a66597_addr(काष्ठा r8a66597 *r8a66597, काष्ठा urb *urb)
अणु
	काष्ठा r8a66597_device *dev = get_urb_to_r8a66597_dev(r8a66597, urb);

	वापस (usb_pipedevice(urb->pipe) == 0) ? 0 : dev->address;
पूर्ण

अटल अचिन्हित लघु *get_toggle_poपूर्णांकer(काष्ठा r8a66597_device *dev,
					  पूर्णांक urb_pipe)
अणु
	अगर (!dev)
		वापस शून्य;

	वापस usb_pipein(urb_pipe) ? &dev->ep_in_toggle : &dev->ep_out_toggle;
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम pipe_toggle_set(काष्ठा r8a66597 *r8a66597,
			    काष्ठा r8a66597_pipe *pipe,
			    काष्ठा urb *urb, पूर्णांक set)
अणु
	काष्ठा r8a66597_device *dev = get_urb_to_r8a66597_dev(r8a66597, urb);
	अचिन्हित अक्षर endpoपूर्णांक = usb_pipeendpoपूर्णांक(urb->pipe);
	अचिन्हित लघु *toggle = get_toggle_poपूर्णांकer(dev, urb->pipe);

	अगर (!toggle)
		वापस;

	अगर (set)
		*toggle |= 1 << endpoपूर्णांक;
	अन्यथा
		*toggle &= ~(1 << endpoपूर्णांक);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम pipe_toggle_save(काष्ठा r8a66597 *r8a66597,
			     काष्ठा r8a66597_pipe *pipe,
			     काष्ठा urb *urb)
अणु
	अगर (r8a66597_पढ़ो(r8a66597, pipe->pipectr) & SQMON)
		pipe_toggle_set(r8a66597, pipe, urb, 1);
	अन्यथा
		pipe_toggle_set(r8a66597, pipe, urb, 0);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम pipe_toggle_restore(काष्ठा r8a66597 *r8a66597,
				काष्ठा r8a66597_pipe *pipe,
				काष्ठा urb *urb)
अणु
	काष्ठा r8a66597_device *dev = get_urb_to_r8a66597_dev(r8a66597, urb);
	अचिन्हित अक्षर endpoपूर्णांक = usb_pipeendpoपूर्णांक(urb->pipe);
	अचिन्हित लघु *toggle = get_toggle_poपूर्णांकer(dev, urb->pipe);

	अगर (!toggle)
		वापस;

	r8a66597_pipe_toggle(r8a66597, pipe, *toggle & (1 << endpoपूर्णांक));
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम pipe_buffer_setting(काष्ठा r8a66597 *r8a66597,
				काष्ठा r8a66597_pipe_info *info)
अणु
	u16 val = 0;

	अगर (info->pipक्रमागत == 0)
		वापस;

	r8a66597_bset(r8a66597, ACLRM, get_pipectr_addr(info->pipक्रमागत));
	r8a66597_bclr(r8a66597, ACLRM, get_pipectr_addr(info->pipक्रमागत));
	r8a66597_ग_लिखो(r8a66597, info->pipक्रमागत, PIPESEL);
	अगर (!info->dir_in)
		val |= R8A66597_सूची;
	अगर (info->type == R8A66597_BULK && info->dir_in)
		val |= R8A66597_DBLB | R8A66597_SHTNAK;
	val |= info->type | info->epnum;
	r8a66597_ग_लिखो(r8a66597, val, PIPECFG);

	r8a66597_ग_लिखो(r8a66597, (info->buf_bsize << 10) | (info->bufnum),
		       PIPEBUF);
	r8a66597_ग_लिखो(r8a66597, make_devsel(info->address) | info->maxpacket,
		       PIPEMAXP);
	r8a66597_ग_लिखो(r8a66597, info->पूर्णांकerval, PIPEPERI);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम pipe_setting(काष्ठा r8a66597 *r8a66597, काष्ठा r8a66597_td *td)
अणु
	काष्ठा r8a66597_pipe_info *info;
	काष्ठा urb *urb = td->urb;

	अगर (td->pipक्रमागत > 0) अणु
		info = &td->pipe->info;
		cfअगरo_change(r8a66597, 0);
		pipe_buffer_setting(r8a66597, info);

		अगर (!usb_gettoggle(urb->dev, usb_pipeendpoपूर्णांक(urb->pipe),
				   usb_pipeout(urb->pipe)) &&
		    !usb_pipecontrol(urb->pipe)) अणु
			r8a66597_pipe_toggle(r8a66597, td->pipe, 0);
			pipe_toggle_set(r8a66597, td->pipe, urb, 0);
			clear_all_buffer(r8a66597, td->pipe);
			usb_settoggle(urb->dev, usb_pipeendpoपूर्णांक(urb->pipe),
				      usb_pipeout(urb->pipe), 1);
		पूर्ण
		pipe_toggle_restore(r8a66597, td->pipe, urb);
	पूर्ण
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल u16 get_empty_pipक्रमागत(काष्ठा r8a66597 *r8a66597,
			     काष्ठा usb_endpoपूर्णांक_descriptor *ep)
अणु
	u16 array[R8A66597_MAX_NUM_PIPE], i = 0, min;

	स_रखो(array, 0, माप(array));
	चयन (usb_endpoपूर्णांक_type(ep)) अणु
	हाल USB_ENDPOINT_XFER_BULK:
		अगर (usb_endpoपूर्णांक_dir_in(ep))
			array[i++] = 4;
		अन्यथा अणु
			array[i++] = 3;
			array[i++] = 5;
		पूर्ण
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		अगर (usb_endpoपूर्णांक_dir_in(ep)) अणु
			array[i++] = 6;
			array[i++] = 7;
			array[i++] = 8;
		पूर्ण अन्यथा
			array[i++] = 9;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (usb_endpoपूर्णांक_dir_in(ep))
			array[i++] = 2;
		अन्यथा
			array[i++] = 1;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "r8a66597: Illegal type\n");
		वापस 0;
	पूर्ण

	i = 1;
	min = array[0];
	जबतक (array[i] != 0) अणु
		अगर (r8a66597->pipe_cnt[min] > r8a66597->pipe_cnt[array[i]])
			min = array[i];
		i++;
	पूर्ण

	वापस min;
पूर्ण

अटल u16 get_r8a66597_type(__u8 type)
अणु
	u16 r8a66597_type;

	चयन (type) अणु
	हाल USB_ENDPOINT_XFER_BULK:
		r8a66597_type = R8A66597_BULK;
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		r8a66597_type = R8A66597_INT;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		r8a66597_type = R8A66597_ISO;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "r8a66597: Illegal type\n");
		r8a66597_type = 0x0000;
		अवरोध;
	पूर्ण

	वापस r8a66597_type;
पूर्ण

अटल u16 get_bufnum(u16 pipक्रमागत)
अणु
	u16 bufnum = 0;

	अगर (pipक्रमागत == 0)
		bufnum = 0;
	अन्यथा अगर (check_bulk_or_isoc(pipक्रमागत))
		bufnum = 8 + (pipक्रमागत - 1) * R8A66597_BUF_BSIZE*2;
	अन्यथा अगर (check_पूर्णांकerrupt(pipक्रमागत))
		bufnum = 4 + (pipक्रमागत - 6);
	अन्यथा
		prपूर्णांकk(KERN_ERR "r8a66597: Illegal pipenum (%d)\n", pipक्रमागत);

	वापस bufnum;
पूर्ण

अटल u16 get_buf_bsize(u16 pipक्रमागत)
अणु
	u16 buf_bsize = 0;

	अगर (pipक्रमागत == 0)
		buf_bsize = 3;
	अन्यथा अगर (check_bulk_or_isoc(pipक्रमागत))
		buf_bsize = R8A66597_BUF_BSIZE - 1;
	अन्यथा अगर (check_पूर्णांकerrupt(pipक्रमागत))
		buf_bsize = 0;
	अन्यथा
		prपूर्णांकk(KERN_ERR "r8a66597: Illegal pipenum (%d)\n", pipक्रमागत);

	वापस buf_bsize;
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम enable_r8a66597_pipe_dma(काष्ठा r8a66597 *r8a66597,
				     काष्ठा r8a66597_device *dev,
				     काष्ठा r8a66597_pipe *pipe,
				     काष्ठा urb *urb)
अणु
	पूर्णांक i;
	काष्ठा r8a66597_pipe_info *info = &pipe->info;
	अचिन्हित लघु mbw = mbw_value(r8a66597);

	/* pipe dma is only क्रम बाह्यal controlles */
	अगर (r8a66597->pdata->on_chip)
		वापस;

	अगर ((pipe->info.pipक्रमागत != 0) && (info->type != R8A66597_INT)) अणु
		क्रम (i = 0; i < R8A66597_MAX_DMA_CHANNEL; i++) अणु
			अगर ((r8a66597->dma_map & (1 << i)) != 0)
				जारी;

			dev_info(&dev->udev->dev,
				 "address %d, EndpointAddress 0x%02x use "
				 "DMA FIFO\n", usb_pipedevice(urb->pipe),
				 info->dir_in ?
				 	USB_ENDPOINT_सूची_MASK + info->epnum
					: info->epnum);

			r8a66597->dma_map |= 1 << i;
			dev->dma_map |= 1 << i;
			set_pipe_reg_addr(pipe, i);

			cfअगरo_change(r8a66597, 0);
			r8a66597_mdfy(r8a66597, mbw | pipe->info.pipक्रमागत,
				      mbw | CURPIPE, pipe->fअगरosel);

			r8a66597_reg_रुको(r8a66597, pipe->fअगरosel, CURPIPE,
					  pipe->info.pipक्रमागत);
			r8a66597_bset(r8a66597, BCLR, pipe->fअगरoctr);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम enable_r8a66597_pipe(काष्ठा r8a66597 *r8a66597, काष्ठा urb *urb,
				 काष्ठा usb_host_endpoपूर्णांक *hep,
				 काष्ठा r8a66597_pipe_info *info)
अणु
	काष्ठा r8a66597_device *dev = get_urb_to_r8a66597_dev(r8a66597, urb);
	काष्ठा r8a66597_pipe *pipe = hep->hcpriv;

	dev_dbg(&dev->udev->dev, "enable_pipe:\n");

	pipe->info = *info;
	set_pipe_reg_addr(pipe, R8A66597_PIPE_NO_DMA);
	r8a66597->pipe_cnt[pipe->info.pipक्रमागत]++;
	dev->pipe_cnt[pipe->info.pipक्रमागत]++;

	enable_r8a66597_pipe_dma(r8a66597, dev, pipe, urb);
पूर्ण

अटल व्योम r8a66597_urb_करोne(काष्ठा r8a66597 *r8a66597, काष्ठा urb *urb,
			      पूर्णांक status)
__releases(r8a66597->lock)
__acquires(r8a66597->lock)
अणु
	अगर (usb_pipein(urb->pipe) && usb_pipetype(urb->pipe) != PIPE_CONTROL) अणु
		व्योम *ptr;

		क्रम (ptr = urb->transfer_buffer;
		     ptr < urb->transfer_buffer + urb->transfer_buffer_length;
		     ptr += PAGE_SIZE)
			flush_dcache_page(virt_to_page(ptr));
	पूर्ण

	usb_hcd_unlink_urb_from_ep(r8a66597_to_hcd(r8a66597), urb);
	spin_unlock(&r8a66597->lock);
	usb_hcd_giveback_urb(r8a66597_to_hcd(r8a66597), urb, status);
	spin_lock(&r8a66597->lock);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम क्रमce_dequeue(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत, u16 address)
अणु
	काष्ठा r8a66597_td *td, *next;
	काष्ठा urb *urb;
	काष्ठा list_head *list = &r8a66597->pipe_queue[pipक्रमागत];

	अगर (list_empty(list))
		वापस;

	list_क्रम_each_entry_safe(td, next, list, queue) अणु
		अगर (td->address != address)
			जारी;

		urb = td->urb;
		list_del(&td->queue);
		kमुक्त(td);

		अगर (urb)
			r8a66597_urb_करोne(r8a66597, urb, -ENODEV);

		अवरोध;
	पूर्ण
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम disable_r8a66597_pipe_all(काष्ठा r8a66597 *r8a66597,
				      काष्ठा r8a66597_device *dev)
अणु
	पूर्णांक check_ep0 = 0;
	u16 pipक्रमागत;

	अगर (!dev)
		वापस;

	क्रम (pipक्रमागत = 1; pipक्रमागत < R8A66597_MAX_NUM_PIPE; pipक्रमागत++) अणु
		अगर (!dev->pipe_cnt[pipक्रमागत])
			जारी;

		अगर (!check_ep0) अणु
			check_ep0 = 1;
			क्रमce_dequeue(r8a66597, 0, dev->address);
		पूर्ण

		r8a66597->pipe_cnt[pipक्रमागत] -= dev->pipe_cnt[pipक्रमागत];
		dev->pipe_cnt[pipक्रमागत] = 0;
		क्रमce_dequeue(r8a66597, pipक्रमागत, dev->address);
	पूर्ण

	dev_dbg(&dev->udev->dev, "disable_pipe\n");

	r8a66597->dma_map &= ~(dev->dma_map);
	dev->dma_map = 0;
पूर्ण

अटल u16 get_पूर्णांकerval(काष्ठा urb *urb, __u8 पूर्णांकerval)
अणु
	u16 समय = 1;
	पूर्णांक i;

	अगर (urb->dev->speed == USB_SPEED_HIGH) अणु
		अगर (पूर्णांकerval > IITV)
			समय = IITV;
		अन्यथा
			समय = पूर्णांकerval ? पूर्णांकerval - 1 : 0;
	पूर्ण अन्यथा अणु
		अगर (पूर्णांकerval > 128) अणु
			समय = IITV;
		पूर्ण अन्यथा अणु
			/* calculate the nearest value क्रम PIPEPERI */
			क्रम (i = 0; i < 7; i++) अणु
				अगर ((1 << i) < पूर्णांकerval &&
				    (1 << (i + 1) > पूर्णांकerval))
					समय = 1 << i;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस समय;
पूर्ण

अटल अचिन्हित दीर्घ get_समयr_पूर्णांकerval(काष्ठा urb *urb, __u8 पूर्णांकerval)
अणु
	__u8 i;
	अचिन्हित दीर्घ समय = 1;

	अगर (usb_pipeisoc(urb->pipe))
		वापस 0;

	अगर (get_r8a66597_usb_speed(urb->dev->speed) == HSMODE) अणु
		क्रम (i = 0; i < (पूर्णांकerval - 1); i++)
			समय *= 2;
		समय = समय * 125 / 1000;	/* uSOF -> msec */
	पूर्ण अन्यथा अणु
		समय = पूर्णांकerval;
	पूर्ण

	वापस समय;
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम init_pipe_info(काष्ठा r8a66597 *r8a66597, काष्ठा urb *urb,
			   काष्ठा usb_host_endpoपूर्णांक *hep,
			   काष्ठा usb_endpoपूर्णांक_descriptor *ep)
अणु
	काष्ठा r8a66597_pipe_info info;

	info.pipक्रमागत = get_empty_pipक्रमागत(r8a66597, ep);
	info.address = get_urb_to_r8a66597_addr(r8a66597, urb);
	info.epnum = usb_endpoपूर्णांक_num(ep);
	info.maxpacket = usb_endpoपूर्णांक_maxp(ep);
	info.type = get_r8a66597_type(usb_endpoपूर्णांक_type(ep));
	info.bufnum = get_bufnum(info.pipक्रमागत);
	info.buf_bsize = get_buf_bsize(info.pipक्रमागत);
	अगर (info.type == R8A66597_BULK) अणु
		info.पूर्णांकerval = 0;
		info.समयr_पूर्णांकerval = 0;
	पूर्ण अन्यथा अणु
		info.पूर्णांकerval = get_पूर्णांकerval(urb, ep->bInterval);
		info.समयr_पूर्णांकerval = get_समयr_पूर्णांकerval(urb, ep->bInterval);
	पूर्ण
	अगर (usb_endpoपूर्णांक_dir_in(ep))
		info.dir_in = 1;
	अन्यथा
		info.dir_in = 0;

	enable_r8a66597_pipe(r8a66597, urb, hep, &info);
पूर्ण

अटल व्योम init_pipe_config(काष्ठा r8a66597 *r8a66597, काष्ठा urb *urb)
अणु
	काष्ठा r8a66597_device *dev;

	dev = get_urb_to_r8a66597_dev(r8a66597, urb);
	dev->state = USB_STATE_CONFIGURED;
पूर्ण

अटल व्योम pipe_irq_enable(काष्ठा r8a66597 *r8a66597, काष्ठा urb *urb,
			    u16 pipक्रमागत)
अणु
	अगर (pipक्रमागत == 0 && usb_pipeout(urb->pipe))
		enable_irq_empty(r8a66597, pipक्रमागत);
	अन्यथा
		enable_irq_पढ़ोy(r8a66597, pipक्रमागत);

	अगर (!usb_pipeisoc(urb->pipe))
		enable_irq_nrdy(r8a66597, pipक्रमागत);
पूर्ण

अटल व्योम pipe_irq_disable(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	disable_irq_पढ़ोy(r8a66597, pipक्रमागत);
	disable_irq_nrdy(r8a66597, pipक्रमागत);
पूर्ण

अटल व्योम r8a66597_root_hub_start_polling(काष्ठा r8a66597 *r8a66597)
अणु
	mod_समयr(&r8a66597->rh_समयr,
			jअगरfies + msecs_to_jअगरfies(R8A66597_RH_POLL_TIME));
पूर्ण

अटल व्योम start_root_hub_sampling(काष्ठा r8a66597 *r8a66597, पूर्णांक port,
					पूर्णांक connect)
अणु
	काष्ठा r8a66597_root_hub *rh = &r8a66597->root_hub[port];

	rh->old_syssts = r8a66597_पढ़ो(r8a66597, get_syssts_reg(port)) & LNST;
	rh->scount = R8A66597_MAX_SAMPLING;
	अगर (connect)
		rh->port |= USB_PORT_STAT_CONNECTION;
	अन्यथा
		rh->port &= ~USB_PORT_STAT_CONNECTION;
	rh->port |= USB_PORT_STAT_C_CONNECTION << 16;

	r8a66597_root_hub_start_polling(r8a66597);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम r8a66597_check_syssts(काष्ठा r8a66597 *r8a66597, पूर्णांक port,
					u16 syssts)
__releases(r8a66597->lock)
__acquires(r8a66597->lock)
अणु
	अगर (syssts == SE0) अणु
		r8a66597_ग_लिखो(r8a66597, ~ATTCH, get_पूर्णांकsts_reg(port));
		r8a66597_bset(r8a66597, ATTCHE, get_पूर्णांकenb_reg(port));
	पूर्ण अन्यथा अणु
		अगर (syssts == FS_JSTS)
			r8a66597_bset(r8a66597, HSE, get_syscfg_reg(port));
		अन्यथा अगर (syssts == LS_JSTS)
			r8a66597_bclr(r8a66597, HSE, get_syscfg_reg(port));

		r8a66597_ग_लिखो(r8a66597, ~DTCH, get_पूर्णांकsts_reg(port));
		r8a66597_bset(r8a66597, DTCHE, get_पूर्णांकenb_reg(port));

		अगर (r8a66597->bus_suspended)
			usb_hcd_resume_root_hub(r8a66597_to_hcd(r8a66597));
	पूर्ण

	spin_unlock(&r8a66597->lock);
	usb_hcd_poll_rh_status(r8a66597_to_hcd(r8a66597));
	spin_lock(&r8a66597->lock);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम r8a66597_usb_connect(काष्ठा r8a66597 *r8a66597, पूर्णांक port)
अणु
	u16 speed = get_rh_usb_speed(r8a66597, port);
	काष्ठा r8a66597_root_hub *rh = &r8a66597->root_hub[port];

	rh->port &= ~(USB_PORT_STAT_HIGH_SPEED | USB_PORT_STAT_LOW_SPEED);
	अगर (speed == HSMODE)
		rh->port |= USB_PORT_STAT_HIGH_SPEED;
	अन्यथा अगर (speed == LSMODE)
		rh->port |= USB_PORT_STAT_LOW_SPEED;

	rh->port &= ~USB_PORT_STAT_RESET;
	rh->port |= USB_PORT_STAT_ENABLE;
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम r8a66597_usb_disconnect(काष्ठा r8a66597 *r8a66597, पूर्णांक port)
अणु
	काष्ठा r8a66597_device *dev = r8a66597->root_hub[port].dev;

	disable_r8a66597_pipe_all(r8a66597, dev);
	मुक्त_usb_address(r8a66597, dev, 0);

	start_root_hub_sampling(r8a66597, port, 0);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम prepare_setup_packet(काष्ठा r8a66597 *r8a66597,
				 काष्ठा r8a66597_td *td)
अणु
	पूर्णांक i;
	__le16 *p = (__le16 *)td->urb->setup_packet;
	अचिन्हित दीर्घ setup_addr = USBREQ;

	r8a66597_ग_लिखो(r8a66597, make_devsel(td->address) | td->maxpacket,
		       DCPMAXP);
	r8a66597_ग_लिखो(r8a66597, ~(SIGN | SACK), INTSTS1);

	क्रम (i = 0; i < 4; i++) अणु
		r8a66597_ग_लिखो(r8a66597, le16_to_cpu(p[i]), setup_addr);
		setup_addr += 2;
	पूर्ण
	r8a66597_ग_लिखो(r8a66597, SUREQ, DCPCTR);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम prepare_packet_पढ़ो(काष्ठा r8a66597 *r8a66597,
				काष्ठा r8a66597_td *td)
अणु
	काष्ठा urb *urb = td->urb;

	अगर (usb_pipecontrol(urb->pipe)) अणु
		r8a66597_bclr(r8a66597, R8A66597_सूची, DCPCFG);
		r8a66597_mdfy(r8a66597, 0, ISEL | CURPIPE, CFIFOSEL);
		r8a66597_reg_रुको(r8a66597, CFIFOSEL, CURPIPE, 0);
		अगर (urb->actual_length == 0) अणु
			r8a66597_pipe_toggle(r8a66597, td->pipe, 1);
			r8a66597_ग_लिखो(r8a66597, BCLR, CFIFOCTR);
		पूर्ण
		pipe_irq_disable(r8a66597, td->pipक्रमागत);
		pipe_start(r8a66597, td->pipe);
		pipe_irq_enable(r8a66597, urb, td->pipक्रमागत);
	पूर्ण अन्यथा अणु
		अगर (urb->actual_length == 0) अणु
			pipe_irq_disable(r8a66597, td->pipक्रमागत);
			pipe_setting(r8a66597, td);
			pipe_stop(r8a66597, td->pipe);
			r8a66597_ग_लिखो(r8a66597, ~(1 << td->pipक्रमागत), BRDYSTS);

			अगर (td->pipe->pipetre) अणु
				r8a66597_ग_लिखो(r8a66597, TRCLR,
						td->pipe->pipetre);
				r8a66597_ग_लिखो(r8a66597,
						DIV_ROUND_UP
						  (urb->transfer_buffer_length,
						   td->maxpacket),
						td->pipe->pipetrn);
				r8a66597_bset(r8a66597, TRENB,
						td->pipe->pipetre);
			पूर्ण

			pipe_start(r8a66597, td->pipe);
			pipe_irq_enable(r8a66597, urb, td->pipक्रमागत);
		पूर्ण
	पूर्ण
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम prepare_packet_ग_लिखो(काष्ठा r8a66597 *r8a66597,
				 काष्ठा r8a66597_td *td)
अणु
	u16 पंचांगp;
	काष्ठा urb *urb = td->urb;

	अगर (usb_pipecontrol(urb->pipe)) अणु
		pipe_stop(r8a66597, td->pipe);
		r8a66597_bset(r8a66597, R8A66597_सूची, DCPCFG);
		r8a66597_mdfy(r8a66597, ISEL, ISEL | CURPIPE, CFIFOSEL);
		r8a66597_reg_रुको(r8a66597, CFIFOSEL, CURPIPE, 0);
		अगर (urb->actual_length == 0) अणु
			r8a66597_pipe_toggle(r8a66597, td->pipe, 1);
			r8a66597_ग_लिखो(r8a66597, BCLR, CFIFOCTR);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (urb->actual_length == 0)
			pipe_setting(r8a66597, td);
		अगर (td->pipe->pipetre)
			r8a66597_bclr(r8a66597, TRENB, td->pipe->pipetre);
	पूर्ण
	r8a66597_ग_लिखो(r8a66597, ~(1 << td->pipक्रमागत), BRDYSTS);

	fअगरo_change_from_pipe(r8a66597, td->pipe);
	पंचांगp = r8a66597_पढ़ो(r8a66597, td->pipe->fअगरoctr);
	अगर (unlikely((पंचांगp & FRDY) == 0))
		pipe_irq_enable(r8a66597, urb, td->pipक्रमागत);
	अन्यथा
		packet_ग_लिखो(r8a66597, td->pipक्रमागत);
	pipe_start(r8a66597, td->pipe);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम prepare_status_packet(काष्ठा r8a66597 *r8a66597,
				  काष्ठा r8a66597_td *td)
अणु
	काष्ठा urb *urb = td->urb;

	r8a66597_pipe_toggle(r8a66597, td->pipe, 1);
	pipe_stop(r8a66597, td->pipe);

	अगर (urb->setup_packet[0] & USB_ENDPOINT_सूची_MASK) अणु
		r8a66597_bset(r8a66597, R8A66597_सूची, DCPCFG);
		r8a66597_mdfy(r8a66597, ISEL, ISEL | CURPIPE, CFIFOSEL);
		r8a66597_reg_रुको(r8a66597, CFIFOSEL, CURPIPE, 0);
		r8a66597_ग_लिखो(r8a66597, ~BEMP0, BEMPSTS);
		r8a66597_ग_लिखो(r8a66597, BCLR | BVAL, CFIFOCTR);
		enable_irq_empty(r8a66597, 0);
	पूर्ण अन्यथा अणु
		r8a66597_bclr(r8a66597, R8A66597_सूची, DCPCFG);
		r8a66597_mdfy(r8a66597, 0, ISEL | CURPIPE, CFIFOSEL);
		r8a66597_reg_रुको(r8a66597, CFIFOSEL, CURPIPE, 0);
		r8a66597_ग_लिखो(r8a66597, BCLR, CFIFOCTR);
		enable_irq_पढ़ोy(r8a66597, 0);
	पूर्ण
	enable_irq_nrdy(r8a66597, 0);
	pipe_start(r8a66597, td->pipe);
पूर्ण

अटल पूर्णांक is_set_address(अचिन्हित अक्षर *setup_packet)
अणु
	अगर (((setup_packet[0] & USB_TYPE_MASK) == USB_TYPE_STANDARD) &&
			setup_packet[1] == USB_REQ_SET_ADDRESS)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल पूर्णांक start_transfer(काष्ठा r8a66597 *r8a66597, काष्ठा r8a66597_td *td)
अणु
	BUG_ON(!td);

	चयन (td->type) अणु
	हाल USB_PID_SETUP:
		अगर (is_set_address(td->urb->setup_packet)) अणु
			td->set_address = 1;
			td->urb->setup_packet[2] = alloc_usb_address(r8a66597,
								     td->urb);
			अगर (td->urb->setup_packet[2] == 0)
				वापस -EPIPE;
		पूर्ण
		prepare_setup_packet(r8a66597, td);
		अवरोध;
	हाल USB_PID_IN:
		prepare_packet_पढ़ो(r8a66597, td);
		अवरोध;
	हाल USB_PID_OUT:
		prepare_packet_ग_लिखो(r8a66597, td);
		अवरोध;
	हाल USB_PID_ACK:
		prepare_status_packet(r8a66597, td);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "r8a66597: invalid type.\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_transfer_finish(काष्ठा r8a66597_td *td, काष्ठा urb *urb)
अणु
	अगर (usb_pipeisoc(urb->pipe)) अणु
		अगर (urb->number_of_packets == td->iso_cnt)
			वापस 1;
	पूर्ण

	/* control or bulk or पूर्णांकerrupt */
	अगर ((urb->transfer_buffer_length <= urb->actual_length) ||
	    (td->लघु_packet) || (td->zero_packet))
		वापस 1;

	वापस 0;
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम set_td_समयr(काष्ठा r8a66597 *r8a66597, काष्ठा r8a66597_td *td)
अणु
	अचिन्हित दीर्घ समय;

	BUG_ON(!td);

	अगर (!list_empty(&r8a66597->pipe_queue[td->pipक्रमागत]) &&
	    !usb_pipecontrol(td->urb->pipe) && usb_pipein(td->urb->pipe)) अणु
		r8a66597->समयout_map |= 1 << td->pipक्रमागत;
		चयन (usb_pipetype(td->urb->pipe)) अणु
		हाल PIPE_INTERRUPT:
		हाल PIPE_ISOCHRONOUS:
			समय = 30;
			अवरोध;
		शेष:
			समय = 50;
			अवरोध;
		पूर्ण

		mod_समयr(&r8a66597->समयrs[td->pipक्रमागत].td,
			  jअगरfies + msecs_to_jअगरfies(समय));
	पूर्ण
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम finish_request(काष्ठा r8a66597 *r8a66597, काष्ठा r8a66597_td *td,
		u16 pipक्रमागत, काष्ठा urb *urb, पूर्णांक status)
__releases(r8a66597->lock) __acquires(r8a66597->lock)
अणु
	पूर्णांक restart = 0;
	काष्ठा usb_hcd *hcd = r8a66597_to_hcd(r8a66597);

	r8a66597->समयout_map &= ~(1 << pipक्रमागत);

	अगर (likely(td)) अणु
		अगर (td->set_address && (status != 0 || urb->unlinked))
			r8a66597->address_map &= ~(1 << urb->setup_packet[2]);

		pipe_toggle_save(r8a66597, td->pipe, urb);
		list_del(&td->queue);
		kमुक्त(td);
	पूर्ण

	अगर (!list_empty(&r8a66597->pipe_queue[pipक्रमागत]))
		restart = 1;

	अगर (likely(urb)) अणु
		अगर (usb_pipeisoc(urb->pipe))
			urb->start_frame = r8a66597_get_frame(hcd);

		r8a66597_urb_करोne(r8a66597, urb, status);
	पूर्ण

	अगर (restart) अणु
		td = r8a66597_get_td(r8a66597, pipक्रमागत);
		अगर (unlikely(!td))
			वापस;

		start_transfer(r8a66597, td);
		set_td_समयr(r8a66597, td);
	पूर्ण
पूर्ण

अटल व्योम packet_पढ़ो(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	u16 पंचांगp;
	पूर्णांक rcv_len, bufsize, urb_len, size;
	u16 *buf;
	काष्ठा r8a66597_td *td = r8a66597_get_td(r8a66597, pipक्रमागत);
	काष्ठा urb *urb;
	पूर्णांक finish = 0;
	पूर्णांक status = 0;

	अगर (unlikely(!td))
		वापस;
	urb = td->urb;

	fअगरo_change_from_pipe(r8a66597, td->pipe);
	पंचांगp = r8a66597_पढ़ो(r8a66597, td->pipe->fअगरoctr);
	अगर (unlikely((पंचांगp & FRDY) == 0)) अणु
		pipe_stop(r8a66597, td->pipe);
		pipe_irq_disable(r8a66597, pipक्रमागत);
		prपूर्णांकk(KERN_ERR "r8a66597: in fifo not ready (%d)\n", pipक्रमागत);
		finish_request(r8a66597, td, pipक्रमागत, td->urb, -EPIPE);
		वापस;
	पूर्ण

	/* prepare parameters */
	rcv_len = पंचांगp & DTLN;
	अगर (usb_pipeisoc(urb->pipe)) अणु
		buf = (u16 *)(urb->transfer_buffer +
				urb->iso_frame_desc[td->iso_cnt].offset);
		urb_len = urb->iso_frame_desc[td->iso_cnt].length;
	पूर्ण अन्यथा अणु
		buf = (व्योम *)urb->transfer_buffer + urb->actual_length;
		urb_len = urb->transfer_buffer_length - urb->actual_length;
	पूर्ण
	bufsize = min(urb_len, (पूर्णांक) td->maxpacket);
	अगर (rcv_len <= bufsize) अणु
		size = rcv_len;
	पूर्ण अन्यथा अणु
		size = bufsize;
		status = -EOVERFLOW;
		finish = 1;
	पूर्ण

	/* update parameters */
	urb->actual_length += size;
	अगर (rcv_len == 0)
		td->zero_packet = 1;
	अगर (rcv_len < bufsize) अणु
		td->लघु_packet = 1;
	पूर्ण
	अगर (usb_pipeisoc(urb->pipe)) अणु
		urb->iso_frame_desc[td->iso_cnt].actual_length = size;
		urb->iso_frame_desc[td->iso_cnt].status = status;
		td->iso_cnt++;
		finish = 0;
	पूर्ण

	/* check transfer finish */
	अगर (finish || check_transfer_finish(td, urb)) अणु
		pipe_stop(r8a66597, td->pipe);
		pipe_irq_disable(r8a66597, pipक्रमागत);
		finish = 1;
	पूर्ण

	/* पढ़ो fअगरo */
	अगर (urb->transfer_buffer) अणु
		अगर (size == 0)
			r8a66597_ग_लिखो(r8a66597, BCLR, td->pipe->fअगरoctr);
		अन्यथा
			r8a66597_पढ़ो_fअगरo(r8a66597, td->pipe->fअगरoaddr,
					   buf, size);
	पूर्ण

	अगर (finish && pipक्रमागत != 0)
		finish_request(r8a66597, td, pipक्रमागत, urb, status);
पूर्ण

अटल व्योम packet_ग_लिखो(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	u16 पंचांगp;
	पूर्णांक bufsize, size;
	u16 *buf;
	काष्ठा r8a66597_td *td = r8a66597_get_td(r8a66597, pipक्रमागत);
	काष्ठा urb *urb;

	अगर (unlikely(!td))
		वापस;
	urb = td->urb;

	fअगरo_change_from_pipe(r8a66597, td->pipe);
	पंचांगp = r8a66597_पढ़ो(r8a66597, td->pipe->fअगरoctr);
	अगर (unlikely((पंचांगp & FRDY) == 0)) अणु
		pipe_stop(r8a66597, td->pipe);
		pipe_irq_disable(r8a66597, pipक्रमागत);
		prपूर्णांकk(KERN_ERR "r8a66597: out fifo not ready (%d)\n", pipक्रमागत);
		finish_request(r8a66597, td, pipक्रमागत, urb, -EPIPE);
		वापस;
	पूर्ण

	/* prepare parameters */
	bufsize = td->maxpacket;
	अगर (usb_pipeisoc(urb->pipe)) अणु
		buf = (u16 *)(urb->transfer_buffer +
				urb->iso_frame_desc[td->iso_cnt].offset);
		size = min(bufsize,
			   (पूर्णांक)urb->iso_frame_desc[td->iso_cnt].length);
	पूर्ण अन्यथा अणु
		buf = (u16 *)(urb->transfer_buffer + urb->actual_length);
		size = min_t(u32, bufsize,
			   urb->transfer_buffer_length - urb->actual_length);
	पूर्ण

	/* ग_लिखो fअगरo */
	अगर (pipक्रमागत > 0)
		r8a66597_ग_लिखो(r8a66597, ~(1 << pipक्रमागत), BEMPSTS);
	अगर (urb->transfer_buffer) अणु
		r8a66597_ग_लिखो_fअगरo(r8a66597, td->pipe, buf, size);
		अगर (!usb_pipebulk(urb->pipe) || td->maxpacket != size)
			r8a66597_ग_लिखो(r8a66597, BVAL, td->pipe->fअगरoctr);
	पूर्ण

	/* update parameters */
	urb->actual_length += size;
	अगर (usb_pipeisoc(urb->pipe)) अणु
		urb->iso_frame_desc[td->iso_cnt].actual_length = size;
		urb->iso_frame_desc[td->iso_cnt].status = 0;
		td->iso_cnt++;
	पूर्ण

	/* check transfer finish */
	अगर (check_transfer_finish(td, urb)) अणु
		disable_irq_पढ़ोy(r8a66597, pipक्रमागत);
		enable_irq_empty(r8a66597, pipक्रमागत);
		अगर (!usb_pipeisoc(urb->pipe))
			enable_irq_nrdy(r8a66597, pipक्रमागत);
	पूर्ण अन्यथा
		pipe_irq_enable(r8a66597, urb, pipक्रमागत);
पूर्ण


अटल व्योम check_next_phase(काष्ठा r8a66597 *r8a66597, पूर्णांक status)
अणु
	काष्ठा r8a66597_td *td = r8a66597_get_td(r8a66597, 0);
	काष्ठा urb *urb;
	u8 finish = 0;

	अगर (unlikely(!td))
		वापस;
	urb = td->urb;

	चयन (td->type) अणु
	हाल USB_PID_IN:
	हाल USB_PID_OUT:
		अगर (check_transfer_finish(td, urb))
			td->type = USB_PID_ACK;
		अवरोध;
	हाल USB_PID_SETUP:
		अगर (urb->transfer_buffer_length == urb->actual_length)
			td->type = USB_PID_ACK;
		अन्यथा अगर (usb_pipeout(urb->pipe))
			td->type = USB_PID_OUT;
		अन्यथा
			td->type = USB_PID_IN;
		अवरोध;
	हाल USB_PID_ACK:
		finish = 1;
		अवरोध;
	पूर्ण

	अगर (finish || status != 0 || urb->unlinked)
		finish_request(r8a66597, td, 0, urb, status);
	अन्यथा
		start_transfer(r8a66597, td);
पूर्ण

अटल पूर्णांक get_urb_error(काष्ठा r8a66597 *r8a66597, u16 pipक्रमागत)
अणु
	काष्ठा r8a66597_td *td = r8a66597_get_td(r8a66597, pipक्रमागत);

	अगर (td) अणु
		u16 pid = r8a66597_पढ़ो(r8a66597, td->pipe->pipectr) & PID;

		अगर (pid == PID_NAK)
			वापस -ECONNRESET;
		अन्यथा
			वापस -EPIPE;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम irq_pipe_पढ़ोy(काष्ठा r8a66597 *r8a66597)
अणु
	u16 check;
	u16 pipक्रमागत;
	u16 mask;
	काष्ठा r8a66597_td *td;

	mask = r8a66597_पढ़ो(r8a66597, BRDYSTS)
	       & r8a66597_पढ़ो(r8a66597, BRDYENB);
	r8a66597_ग_लिखो(r8a66597, ~mask, BRDYSTS);
	अगर (mask & BRDY0) अणु
		td = r8a66597_get_td(r8a66597, 0);
		अगर (td && td->type == USB_PID_IN)
			packet_पढ़ो(r8a66597, 0);
		अन्यथा
			pipe_irq_disable(r8a66597, 0);
		check_next_phase(r8a66597, 0);
	पूर्ण

	क्रम (pipक्रमागत = 1; pipक्रमागत < R8A66597_MAX_NUM_PIPE; pipक्रमागत++) अणु
		check = 1 << pipक्रमागत;
		अगर (mask & check) अणु
			td = r8a66597_get_td(r8a66597, pipक्रमागत);
			अगर (unlikely(!td))
				जारी;

			अगर (td->type == USB_PID_IN)
				packet_पढ़ो(r8a66597, pipक्रमागत);
			अन्यथा अगर (td->type == USB_PID_OUT)
				packet_ग_लिखो(r8a66597, pipक्रमागत);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम irq_pipe_empty(काष्ठा r8a66597 *r8a66597)
अणु
	u16 पंचांगp;
	u16 check;
	u16 pipक्रमागत;
	u16 mask;
	काष्ठा r8a66597_td *td;

	mask = r8a66597_पढ़ो(r8a66597, BEMPSTS)
	       & r8a66597_पढ़ो(r8a66597, BEMPENB);
	r8a66597_ग_लिखो(r8a66597, ~mask, BEMPSTS);
	अगर (mask & BEMP0) अणु
		cfअगरo_change(r8a66597, 0);
		td = r8a66597_get_td(r8a66597, 0);
		अगर (td && td->type != USB_PID_OUT)
			disable_irq_empty(r8a66597, 0);
		check_next_phase(r8a66597, 0);
	पूर्ण

	क्रम (pipक्रमागत = 1; pipक्रमागत < R8A66597_MAX_NUM_PIPE; pipक्रमागत++) अणु
		check = 1 << pipक्रमागत;
		अगर (mask &  check) अणु
			काष्ठा r8a66597_td *td;
			td = r8a66597_get_td(r8a66597, pipक्रमागत);
			अगर (unlikely(!td))
				जारी;

			पंचांगp = r8a66597_पढ़ो(r8a66597, td->pipe->pipectr);
			अगर ((पंचांगp & INBUFM) == 0) अणु
				disable_irq_empty(r8a66597, pipक्रमागत);
				pipe_irq_disable(r8a66597, pipक्रमागत);
				finish_request(r8a66597, td, pipक्रमागत, td->urb,
						0);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम irq_pipe_nrdy(काष्ठा r8a66597 *r8a66597)
अणु
	u16 check;
	u16 pipक्रमागत;
	u16 mask;
	पूर्णांक status;

	mask = r8a66597_पढ़ो(r8a66597, NRDYSTS)
	       & r8a66597_पढ़ो(r8a66597, NRDYENB);
	r8a66597_ग_लिखो(r8a66597, ~mask, NRDYSTS);
	अगर (mask & NRDY0) अणु
		cfअगरo_change(r8a66597, 0);
		status = get_urb_error(r8a66597, 0);
		pipe_irq_disable(r8a66597, 0);
		check_next_phase(r8a66597, status);
	पूर्ण

	क्रम (pipक्रमागत = 1; pipक्रमागत < R8A66597_MAX_NUM_PIPE; pipक्रमागत++) अणु
		check = 1 << pipक्रमागत;
		अगर (mask & check) अणु
			काष्ठा r8a66597_td *td;
			td = r8a66597_get_td(r8a66597, pipक्रमागत);
			अगर (unlikely(!td))
				जारी;

			status = get_urb_error(r8a66597, pipक्रमागत);
			pipe_irq_disable(r8a66597, pipक्रमागत);
			pipe_stop(r8a66597, td->pipe);
			finish_request(r8a66597, td, pipक्रमागत, td->urb, status);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t r8a66597_irq(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);
	u16 पूर्णांकsts0, पूर्णांकsts1, पूर्णांकsts2;
	u16 पूर्णांकenb0, पूर्णांकenb1, पूर्णांकenb2;
	u16 mask0, mask1, mask2;
	पूर्णांक status;

	spin_lock(&r8a66597->lock);

	पूर्णांकsts0 = r8a66597_पढ़ो(r8a66597, INTSTS0);
	पूर्णांकsts1 = r8a66597_पढ़ो(r8a66597, INTSTS1);
	पूर्णांकsts2 = r8a66597_पढ़ो(r8a66597, INTSTS2);
	पूर्णांकenb0 = r8a66597_पढ़ो(r8a66597, INTENB0);
	पूर्णांकenb1 = r8a66597_पढ़ो(r8a66597, INTENB1);
	पूर्णांकenb2 = r8a66597_पढ़ो(r8a66597, INTENB2);

	mask2 = पूर्णांकsts2 & पूर्णांकenb2;
	mask1 = पूर्णांकsts1 & पूर्णांकenb1;
	mask0 = पूर्णांकsts0 & पूर्णांकenb0 & (BEMP | NRDY | BRDY);
	अगर (mask2) अणु
		अगर (mask2 & ATTCH) अणु
			r8a66597_ग_लिखो(r8a66597, ~ATTCH, INTSTS2);
			r8a66597_bclr(r8a66597, ATTCHE, INTENB2);

			/* start usb bus sampling */
			start_root_hub_sampling(r8a66597, 1, 1);
		पूर्ण
		अगर (mask2 & DTCH) अणु
			r8a66597_ग_लिखो(r8a66597, ~DTCH, INTSTS2);
			r8a66597_bclr(r8a66597, DTCHE, INTENB2);
			r8a66597_usb_disconnect(r8a66597, 1);
		पूर्ण
		अगर (mask2 & BCHG) अणु
			r8a66597_ग_लिखो(r8a66597, ~BCHG, INTSTS2);
			r8a66597_bclr(r8a66597, BCHGE, INTENB2);
			usb_hcd_resume_root_hub(r8a66597_to_hcd(r8a66597));
		पूर्ण
	पूर्ण

	अगर (mask1) अणु
		अगर (mask1 & ATTCH) अणु
			r8a66597_ग_लिखो(r8a66597, ~ATTCH, INTSTS1);
			r8a66597_bclr(r8a66597, ATTCHE, INTENB1);

			/* start usb bus sampling */
			start_root_hub_sampling(r8a66597, 0, 1);
		पूर्ण
		अगर (mask1 & DTCH) अणु
			r8a66597_ग_लिखो(r8a66597, ~DTCH, INTSTS1);
			r8a66597_bclr(r8a66597, DTCHE, INTENB1);
			r8a66597_usb_disconnect(r8a66597, 0);
		पूर्ण
		अगर (mask1 & BCHG) अणु
			r8a66597_ग_लिखो(r8a66597, ~BCHG, INTSTS1);
			r8a66597_bclr(r8a66597, BCHGE, INTENB1);
			usb_hcd_resume_root_hub(r8a66597_to_hcd(r8a66597));
		पूर्ण

		अगर (mask1 & SIGN) अणु
			r8a66597_ग_लिखो(r8a66597, ~SIGN, INTSTS1);
			status = get_urb_error(r8a66597, 0);
			check_next_phase(r8a66597, status);
		पूर्ण
		अगर (mask1 & SACK) अणु
			r8a66597_ग_लिखो(r8a66597, ~SACK, INTSTS1);
			check_next_phase(r8a66597, 0);
		पूर्ण
	पूर्ण
	अगर (mask0) अणु
		अगर (mask0 & BRDY)
			irq_pipe_पढ़ोy(r8a66597);
		अगर (mask0 & BEMP)
			irq_pipe_empty(r8a66597);
		अगर (mask0 & NRDY)
			irq_pipe_nrdy(r8a66597);
	पूर्ण

	spin_unlock(&r8a66597->lock);
	वापस IRQ_HANDLED;
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल व्योम r8a66597_root_hub_control(काष्ठा r8a66597 *r8a66597, पूर्णांक port)
अणु
	u16 पंचांगp;
	काष्ठा r8a66597_root_hub *rh = &r8a66597->root_hub[port];

	अगर (rh->port & USB_PORT_STAT_RESET) अणु
		अचिन्हित दीर्घ dvstctr_reg = get_dvstctr_reg(port);

		पंचांगp = r8a66597_पढ़ो(r8a66597, dvstctr_reg);
		अगर ((पंचांगp & USBRST) == USBRST) अणु
			r8a66597_mdfy(r8a66597, UACT, USBRST | UACT,
				      dvstctr_reg);
			r8a66597_root_hub_start_polling(r8a66597);
		पूर्ण अन्यथा
			r8a66597_usb_connect(r8a66597, port);
	पूर्ण

	अगर (!(rh->port & USB_PORT_STAT_CONNECTION)) अणु
		r8a66597_ग_लिखो(r8a66597, ~ATTCH, get_पूर्णांकsts_reg(port));
		r8a66597_bset(r8a66597, ATTCHE, get_पूर्णांकenb_reg(port));
	पूर्ण

	अगर (rh->scount > 0) अणु
		पंचांगp = r8a66597_पढ़ो(r8a66597, get_syssts_reg(port)) & LNST;
		अगर (पंचांगp == rh->old_syssts) अणु
			rh->scount--;
			अगर (rh->scount == 0)
				r8a66597_check_syssts(r8a66597, port, पंचांगp);
			अन्यथा
				r8a66597_root_hub_start_polling(r8a66597);
		पूर्ण अन्यथा अणु
			rh->scount = R8A66597_MAX_SAMPLING;
			rh->old_syssts = पंचांगp;
			r8a66597_root_hub_start_polling(r8a66597);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम r8a66597_पूर्णांकerval_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा r8a66597_समयrs *समयrs = from_समयr(समयrs, t, पूर्णांकerval);
	काष्ठा r8a66597 *r8a66597 = समयrs->r8a66597;
	अचिन्हित दीर्घ flags;
	u16 pipक्रमागत;
	काष्ठा r8a66597_td *td;

	spin_lock_irqsave(&r8a66597->lock, flags);

	क्रम (pipक्रमागत = 0; pipक्रमागत < R8A66597_MAX_NUM_PIPE; pipक्रमागत++) अणु
		अगर (!(r8a66597->पूर्णांकerval_map & (1 << pipक्रमागत)))
			जारी;
		अगर (समयr_pending(&r8a66597->समयrs[pipक्रमागत].पूर्णांकerval))
			जारी;

		td = r8a66597_get_td(r8a66597, pipक्रमागत);
		अगर (td)
			start_transfer(r8a66597, td);
	पूर्ण

	spin_unlock_irqrestore(&r8a66597->lock, flags);
पूर्ण

अटल व्योम r8a66597_td_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा r8a66597_समयrs *समयrs = from_समयr(समयrs, t, td);
	काष्ठा r8a66597 *r8a66597 = समयrs->r8a66597;
	अचिन्हित दीर्घ flags;
	u16 pipक्रमागत;
	काष्ठा r8a66597_td *td, *new_td = शून्य;
	काष्ठा r8a66597_pipe *pipe;

	spin_lock_irqsave(&r8a66597->lock, flags);
	क्रम (pipक्रमागत = 0; pipक्रमागत < R8A66597_MAX_NUM_PIPE; pipक्रमागत++) अणु
		अगर (!(r8a66597->समयout_map & (1 << pipक्रमागत)))
			जारी;
		अगर (समयr_pending(&r8a66597->समयrs[pipक्रमागत].td))
			जारी;

		td = r8a66597_get_td(r8a66597, pipक्रमागत);
		अगर (!td) अणु
			r8a66597->समयout_map &= ~(1 << pipक्रमागत);
			जारी;
		पूर्ण

		अगर (td->urb->actual_length) अणु
			set_td_समयr(r8a66597, td);
			अवरोध;
		पूर्ण

		pipe = td->pipe;
		pipe_stop(r8a66597, pipe);

		/* Select a dअगरferent address or endpoपूर्णांक */
		new_td = td;
		करो अणु
			list_move_tail(&new_td->queue,
				       &r8a66597->pipe_queue[pipक्रमागत]);
			new_td = r8a66597_get_td(r8a66597, pipक्रमागत);
			अगर (!new_td) अणु
				new_td = td;
				अवरोध;
			पूर्ण
		पूर्ण जबतक (td != new_td && td->address == new_td->address &&
			td->pipe->info.epnum == new_td->pipe->info.epnum);

		start_transfer(r8a66597, new_td);

		अगर (td == new_td)
			r8a66597->समयout_map &= ~(1 << pipक्रमागत);
		अन्यथा
			set_td_समयr(r8a66597, new_td);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&r8a66597->lock, flags);
पूर्ण

अटल व्योम r8a66597_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा r8a66597 *r8a66597 = from_समयr(r8a66597, t, rh_समयr);
	अचिन्हित दीर्घ flags;
	पूर्णांक port;

	spin_lock_irqsave(&r8a66597->lock, flags);

	क्रम (port = 0; port < r8a66597->max_root_hub; port++)
		r8a66597_root_hub_control(r8a66597, port);

	spin_unlock_irqrestore(&r8a66597->lock, flags);
पूर्ण

अटल पूर्णांक check_pipe_config(काष्ठा r8a66597 *r8a66597, काष्ठा urb *urb)
अणु
	काष्ठा r8a66597_device *dev = get_urb_to_r8a66597_dev(r8a66597, urb);

	अगर (dev && dev->address && dev->state != USB_STATE_CONFIGURED &&
	    (urb->dev->state == USB_STATE_CONFIGURED))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक r8a66597_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);

	hcd->state = HC_STATE_RUNNING;
	वापस enable_controller(r8a66597);
पूर्ण

अटल व्योम r8a66597_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);

	disable_controller(r8a66597);
पूर्ण

अटल व्योम set_address_zero(काष्ठा r8a66597 *r8a66597, काष्ठा urb *urb)
अणु
	अचिन्हित पूर्णांक usb_address = usb_pipedevice(urb->pipe);
	u16 root_port, hub_port;

	अगर (usb_address == 0) अणु
		get_port_number(r8a66597, urb->dev->devpath,
				&root_port, &hub_port);
		set_devadd_reg(r8a66597, 0,
			       get_r8a66597_usb_speed(urb->dev->speed),
			       get_parent_r8a66597_address(r8a66597, urb->dev),
			       hub_port, root_port);
	पूर्ण
पूर्ण

अटल काष्ठा r8a66597_td *r8a66597_make_td(काष्ठा r8a66597 *r8a66597,
					    काष्ठा urb *urb,
					    काष्ठा usb_host_endpoपूर्णांक *hep)
अणु
	काष्ठा r8a66597_td *td;
	u16 pipक्रमागत;

	td = kzalloc(माप(काष्ठा r8a66597_td), GFP_ATOMIC);
	अगर (td == शून्य)
		वापस शून्य;

	pipक्रमागत = r8a66597_get_pipक्रमागत(urb, hep);
	td->pipक्रमागत = pipक्रमागत;
	td->pipe = hep->hcpriv;
	td->urb = urb;
	td->address = get_urb_to_r8a66597_addr(r8a66597, urb);
	td->maxpacket = usb_maxpacket(urb->dev, urb->pipe,
				      !usb_pipein(urb->pipe));
	अगर (usb_pipecontrol(urb->pipe))
		td->type = USB_PID_SETUP;
	अन्यथा अगर (usb_pipein(urb->pipe))
		td->type = USB_PID_IN;
	अन्यथा
		td->type = USB_PID_OUT;
	INIT_LIST_HEAD(&td->queue);

	वापस td;
पूर्ण

अटल पूर्णांक r8a66597_urb_enqueue(काष्ठा usb_hcd *hcd,
				काष्ठा urb *urb,
				gfp_t mem_flags)
अणु
	काष्ठा usb_host_endpoपूर्णांक *hep = urb->ep;
	काष्ठा r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);
	काष्ठा r8a66597_td *td = शून्य;
	पूर्णांक ret, request = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&r8a66597->lock, flags);
	अगर (!get_urb_to_r8a66597_dev(r8a66597, urb)) अणु
		ret = -ENODEV;
		जाओ error_not_linked;
	पूर्ण

	ret = usb_hcd_link_urb_to_ep(hcd, urb);
	अगर (ret)
		जाओ error_not_linked;

	अगर (!hep->hcpriv) अणु
		hep->hcpriv = kzalloc(माप(काष्ठा r8a66597_pipe),
				GFP_ATOMIC);
		अगर (!hep->hcpriv) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
		set_pipe_reg_addr(hep->hcpriv, R8A66597_PIPE_NO_DMA);
		अगर (usb_pipeendpoपूर्णांक(urb->pipe))
			init_pipe_info(r8a66597, urb, hep, &hep->desc);
	पूर्ण

	अगर (unlikely(check_pipe_config(r8a66597, urb)))
		init_pipe_config(r8a66597, urb);

	set_address_zero(r8a66597, urb);
	td = r8a66597_make_td(r8a66597, urb, hep);
	अगर (td == शून्य) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण
	अगर (list_empty(&r8a66597->pipe_queue[td->pipक्रमागत]))
		request = 1;
	list_add_tail(&td->queue, &r8a66597->pipe_queue[td->pipक्रमागत]);
	urb->hcpriv = td;

	अगर (request) अणु
		अगर (td->pipe->info.समयr_पूर्णांकerval) अणु
			r8a66597->पूर्णांकerval_map |= 1 << td->pipक्रमागत;
			mod_समयr(&r8a66597->समयrs[td->pipक्रमागत].पूर्णांकerval,
				  jअगरfies + msecs_to_jअगरfies(
					td->pipe->info.समयr_पूर्णांकerval));
		पूर्ण अन्यथा अणु
			ret = start_transfer(r8a66597, td);
			अगर (ret < 0) अणु
				list_del(&td->queue);
				kमुक्त(td);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		set_td_समयr(r8a66597, td);

error:
	अगर (ret)
		usb_hcd_unlink_urb_from_ep(hcd, urb);
error_not_linked:
	spin_unlock_irqrestore(&r8a66597->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक r8a66597_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
		पूर्णांक status)
अणु
	काष्ठा r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);
	काष्ठा r8a66597_td *td;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&r8a66597->lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (rc)
		जाओ करोne;

	अगर (urb->hcpriv) अणु
		td = urb->hcpriv;
		pipe_stop(r8a66597, td->pipe);
		pipe_irq_disable(r8a66597, td->pipक्रमागत);
		disable_irq_empty(r8a66597, td->pipक्रमागत);
		finish_request(r8a66597, td, td->pipक्रमागत, urb, status);
	पूर्ण
 करोne:
	spin_unlock_irqrestore(&r8a66597->lock, flags);
	वापस rc;
पूर्ण

अटल व्योम r8a66597_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
				      काष्ठा usb_host_endpoपूर्णांक *hep)
__acquires(r8a66597->lock)
__releases(r8a66597->lock)
अणु
	काष्ठा r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);
	काष्ठा r8a66597_pipe *pipe = (काष्ठा r8a66597_pipe *)hep->hcpriv;
	काष्ठा r8a66597_td *td;
	काष्ठा urb *urb = शून्य;
	u16 pipक्रमागत;
	अचिन्हित दीर्घ flags;

	अगर (pipe == शून्य)
		वापस;
	pipक्रमागत = pipe->info.pipक्रमागत;

	spin_lock_irqsave(&r8a66597->lock, flags);
	अगर (pipक्रमागत == 0) अणु
		kमुक्त(hep->hcpriv);
		hep->hcpriv = शून्य;
		spin_unlock_irqrestore(&r8a66597->lock, flags);
		वापस;
	पूर्ण

	pipe_stop(r8a66597, pipe);
	pipe_irq_disable(r8a66597, pipक्रमागत);
	disable_irq_empty(r8a66597, pipक्रमागत);
	td = r8a66597_get_td(r8a66597, pipक्रमागत);
	अगर (td)
		urb = td->urb;
	finish_request(r8a66597, td, pipक्रमागत, urb, -ESHUTDOWN);
	kमुक्त(hep->hcpriv);
	hep->hcpriv = शून्य;
	spin_unlock_irqrestore(&r8a66597->lock, flags);
पूर्ण

अटल पूर्णांक r8a66597_get_frame(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);
	वापस r8a66597_पढ़ो(r8a66597, FRMNUM) & 0x03FF;
पूर्ण

अटल व्योम collect_usb_address_map(काष्ठा usb_device *udev, अचिन्हित दीर्घ *map)
अणु
	पूर्णांक chix;
	काष्ठा usb_device *childdev;

	अगर (udev->state == USB_STATE_CONFIGURED &&
	    udev->parent && udev->parent->devnum > 1 &&
	    udev->parent->descriptor.bDeviceClass == USB_CLASS_HUB)
		map[udev->devnum/32] |= (1 << (udev->devnum % 32));

	usb_hub_क्रम_each_child(udev, chix, childdev)
		collect_usb_address_map(childdev, map);
पूर्ण

/* this function must be called with पूर्णांकerrupt disabled */
अटल काष्ठा r8a66597_device *get_r8a66597_device(काष्ठा r8a66597 *r8a66597,
						   पूर्णांक addr)
अणु
	काष्ठा r8a66597_device *dev;
	काष्ठा list_head *list = &r8a66597->child_device;

	list_क्रम_each_entry(dev, list, device_list) अणु
		अगर (dev->usb_address != addr)
			जारी;

		वापस dev;
	पूर्ण

	prपूर्णांकk(KERN_ERR "r8a66597: get_r8a66597_device fail.(%d)\n", addr);
	वापस शून्य;
पूर्ण

अटल व्योम update_usb_address_map(काष्ठा r8a66597 *r8a66597,
				   काष्ठा usb_device *root_hub,
				   अचिन्हित दीर्घ *map)
अणु
	पूर्णांक i, j, addr;
	अचिन्हित दीर्घ dअगरf;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < 4; i++) अणु
		dअगरf = r8a66597->child_connect_map[i] ^ map[i];
		अगर (!dअगरf)
			जारी;

		क्रम (j = 0; j < 32; j++) अणु
			अगर (!(dअगरf & (1 << j)))
				जारी;

			addr = i * 32 + j;
			अगर (map[i] & (1 << j))
				set_child_connect_map(r8a66597, addr);
			अन्यथा अणु
				काष्ठा r8a66597_device *dev;

				spin_lock_irqsave(&r8a66597->lock, flags);
				dev = get_r8a66597_device(r8a66597, addr);
				disable_r8a66597_pipe_all(r8a66597, dev);
				मुक्त_usb_address(r8a66597, dev, 0);
				put_child_connect_map(r8a66597, addr);
				spin_unlock_irqrestore(&r8a66597->lock, flags);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम r8a66597_check_detect_child(काष्ठा r8a66597 *r8a66597,
					काष्ठा usb_hcd *hcd)
अणु
	काष्ठा usb_bus *bus;
	अचिन्हित दीर्घ now_map[4];

	स_रखो(now_map, 0, माप(now_map));

	mutex_lock(&usb_bus_idr_lock);
	bus = idr_find(&usb_bus_idr, hcd->self.busnum);
	अगर (bus && bus->root_hub) अणु
		collect_usb_address_map(bus->root_hub, now_map);
		update_usb_address_map(r8a66597, bus->root_hub, now_map);
	पूर्ण
	mutex_unlock(&usb_bus_idr_lock);
पूर्ण

अटल पूर्णांक r8a66597_hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	काष्ठा r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	r8a66597_check_detect_child(r8a66597, hcd);

	spin_lock_irqsave(&r8a66597->lock, flags);

	*buf = 0;	/* initialize (no change) */

	क्रम (i = 0; i < r8a66597->max_root_hub; i++) अणु
		अगर (r8a66597->root_hub[i].port & 0xffff0000)
			*buf |= 1 << (i + 1);
	पूर्ण

	spin_unlock_irqrestore(&r8a66597->lock, flags);

	वापस (*buf != 0);
पूर्ण

अटल व्योम r8a66597_hub_descriptor(काष्ठा r8a66597 *r8a66597,
				    काष्ठा usb_hub_descriptor *desc)
अणु
	desc->bDescriptorType = USB_DT_HUB;
	desc->bHubContrCurrent = 0;
	desc->bNbrPorts = r8a66597->max_root_hub;
	desc->bDescLength = 9;
	desc->bPwrOn2PwrGood = 0;
	desc->wHubCharacteristics =
		cpu_to_le16(HUB_CHAR_INDV_PORT_LPSM | HUB_CHAR_NO_OCPM);
	desc->u.hs.DeviceRemovable[0] =
		((1 << r8a66597->max_root_hub) - 1) << 1;
	desc->u.hs.DeviceRemovable[1] = ~0;
पूर्ण

अटल पूर्णांक r8a66597_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
				u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);
	पूर्णांक ret;
	पूर्णांक port = (wIndex & 0x00FF) - 1;
	काष्ठा r8a66597_root_hub *rh = &r8a66597->root_hub[port];
	अचिन्हित दीर्घ flags;

	ret = 0;

	spin_lock_irqsave(&r8a66597->lock, flags);
	चयन (typeReq) अणु
	हाल ClearHubFeature:
	हाल SetHubFeature:
		चयन (wValue) अणु
		हाल C_HUB_OVER_CURRENT:
		हाल C_HUB_LOCAL_POWER:
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		अवरोध;
	हाल ClearPortFeature:
		अगर (wIndex > r8a66597->max_root_hub)
			जाओ error;
		अगर (wLength != 0)
			जाओ error;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_ENABLE:
			rh->port &= ~USB_PORT_STAT_POWER;
			अवरोध;
		हाल USB_PORT_FEAT_SUSPEND:
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			r8a66597_port_घातer(r8a66597, port, 0);
			अवरोध;
		हाल USB_PORT_FEAT_C_ENABLE:
		हाल USB_PORT_FEAT_C_SUSPEND:
		हाल USB_PORT_FEAT_C_CONNECTION:
		हाल USB_PORT_FEAT_C_OVER_CURRENT:
		हाल USB_PORT_FEAT_C_RESET:
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		rh->port &= ~(1 << wValue);
		अवरोध;
	हाल GetHubDescriptor:
		r8a66597_hub_descriptor(r8a66597,
					(काष्ठा usb_hub_descriptor *)buf);
		अवरोध;
	हाल GetHubStatus:
		*buf = 0x00;
		अवरोध;
	हाल GetPortStatus:
		अगर (wIndex > r8a66597->max_root_hub)
			जाओ error;
		*(__le32 *)buf = cpu_to_le32(rh->port);
		अवरोध;
	हाल SetPortFeature:
		अगर (wIndex > r8a66597->max_root_hub)
			जाओ error;
		अगर (wLength != 0)
			जाओ error;

		चयन (wValue) अणु
		हाल USB_PORT_FEAT_SUSPEND:
			अवरोध;
		हाल USB_PORT_FEAT_POWER:
			r8a66597_port_घातer(r8a66597, port, 1);
			rh->port |= USB_PORT_STAT_POWER;
			अवरोध;
		हाल USB_PORT_FEAT_RESET: अणु
			काष्ठा r8a66597_device *dev = rh->dev;

			rh->port |= USB_PORT_STAT_RESET;

			disable_r8a66597_pipe_all(r8a66597, dev);
			मुक्त_usb_address(r8a66597, dev, 1);

			r8a66597_mdfy(r8a66597, USBRST, USBRST | UACT,
				      get_dvstctr_reg(port));
			mod_समयr(&r8a66597->rh_समयr,
				  jअगरfies + msecs_to_jअगरfies(50));
			पूर्ण
			अवरोध;
		शेष:
			जाओ error;
		पूर्ण
		rh->port |= 1 << wValue;
		अवरोध;
	शेष:
error:
		ret = -EPIPE;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&r8a66597->lock, flags);
	वापस ret;
पूर्ण

#अगर defined(CONFIG_PM)
अटल पूर्णांक r8a66597_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);
	पूर्णांक port;

	dev_dbg(&r8a66597->device0.udev->dev, "%s\n", __func__);

	क्रम (port = 0; port < r8a66597->max_root_hub; port++) अणु
		काष्ठा r8a66597_root_hub *rh = &r8a66597->root_hub[port];
		अचिन्हित दीर्घ dvstctr_reg = get_dvstctr_reg(port);

		अगर (!(rh->port & USB_PORT_STAT_ENABLE))
			जारी;

		dev_dbg(&rh->dev->udev->dev, "suspend port = %d\n", port);
		r8a66597_bclr(r8a66597, UACT, dvstctr_reg);	/* suspend */
		rh->port |= USB_PORT_STAT_SUSPEND;

		अगर (rh->dev->udev->करो_remote_wakeup) अणु
			msleep(3);	/* रुकोing last SOF */
			r8a66597_bset(r8a66597, RWUPE, dvstctr_reg);
			r8a66597_ग_लिखो(r8a66597, ~BCHG, get_पूर्णांकsts_reg(port));
			r8a66597_bset(r8a66597, BCHGE, get_पूर्णांकenb_reg(port));
		पूर्ण
	पूर्ण

	r8a66597->bus_suspended = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक r8a66597_bus_resume(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);
	पूर्णांक port;

	dev_dbg(&r8a66597->device0.udev->dev, "%s\n", __func__);

	क्रम (port = 0; port < r8a66597->max_root_hub; port++) अणु
		काष्ठा r8a66597_root_hub *rh = &r8a66597->root_hub[port];
		अचिन्हित दीर्घ dvstctr_reg = get_dvstctr_reg(port);

		अगर (!(rh->port & USB_PORT_STAT_SUSPEND))
			जारी;

		dev_dbg(&rh->dev->udev->dev, "resume port = %d\n", port);
		rh->port &= ~USB_PORT_STAT_SUSPEND;
		rh->port |= USB_PORT_STAT_C_SUSPEND << 16;
		r8a66597_mdfy(r8a66597, RESUME, RESUME | UACT, dvstctr_reg);
		msleep(USB_RESUME_TIMEOUT);
		r8a66597_mdfy(r8a66597, UACT, RESUME | UACT, dvstctr_reg);
	पूर्ण

	वापस 0;

पूर्ण
#अन्यथा
#घोषणा	r8a66597_bus_suspend	शून्य
#घोषणा	r8a66597_bus_resume	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा hc_driver r8a66597_hc_driver = अणु
	.description =		hcd_name,
	.hcd_priv_size =	माप(काष्ठा r8a66597),
	.irq =			r8a66597_irq,

	/*
	 * generic hardware linkage
	 */
	.flags =		HCD_USB2,

	.start =		r8a66597_start,
	.stop =			r8a66597_stop,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue =		r8a66597_urb_enqueue,
	.urb_dequeue =		r8a66597_urb_dequeue,
	.endpoपूर्णांक_disable =	r8a66597_endpoपूर्णांक_disable,

	/*
	 * periodic schedule support
	 */
	.get_frame_number =	r8a66597_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data =	r8a66597_hub_status_data,
	.hub_control =		r8a66597_hub_control,
	.bus_suspend =		r8a66597_bus_suspend,
	.bus_resume =		r8a66597_bus_resume,
पूर्ण;

#अगर defined(CONFIG_PM)
अटल पूर्णांक r8a66597_suspend(काष्ठा device *dev)
अणु
	काष्ठा r8a66597		*r8a66597 = dev_get_drvdata(dev);
	पूर्णांक port;

	dev_dbg(dev, "%s\n", __func__);

	disable_controller(r8a66597);

	क्रम (port = 0; port < r8a66597->max_root_hub; port++) अणु
		काष्ठा r8a66597_root_hub *rh = &r8a66597->root_hub[port];

		rh->port = 0x00000000;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक r8a66597_resume(काष्ठा device *dev)
अणु
	काष्ठा r8a66597		*r8a66597 = dev_get_drvdata(dev);
	काष्ठा usb_hcd		*hcd = r8a66597_to_hcd(r8a66597);

	dev_dbg(dev, "%s\n", __func__);

	enable_controller(r8a66597);
	usb_root_hub_lost_घातer(hcd->self.root_hub);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops r8a66597_dev_pm_ops = अणु
	.suspend = r8a66597_suspend,
	.resume = r8a66597_resume,
	.घातeroff = r8a66597_suspend,
	.restore = r8a66597_resume,
पूर्ण;

#घोषणा R8A66597_DEV_PM_OPS	(&r8a66597_dev_pm_ops)
#अन्यथा	/* अगर defined(CONFIG_PM) */
#घोषणा R8A66597_DEV_PM_OPS	शून्य
#पूर्ण_अगर

अटल पूर्णांक r8a66597_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा r8a66597		*r8a66597 = platक्रमm_get_drvdata(pdev);
	काष्ठा usb_hcd		*hcd = r8a66597_to_hcd(r8a66597);

	del_समयr_sync(&r8a66597->rh_समयr);
	usb_हटाओ_hcd(hcd);
	iounmap(r8a66597->reg);
	अगर (r8a66597->pdata->on_chip)
		clk_put(r8a66597->clk);
	usb_put_hcd(hcd);
	वापस 0;
पूर्ण

अटल पूर्णांक r8a66597_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अक्षर clk_name[8];
	काष्ठा resource *res = शून्य, *ires;
	पूर्णांक irq = -1;
	व्योम __iomem *reg = शून्य;
	काष्ठा usb_hcd *hcd = शून्य;
	काष्ठा r8a66597 *r8a66597;
	पूर्णांक ret = 0;
	पूर्णांक i;
	अचिन्हित दीर्घ irq_trigger;

	अगर (usb_disabled())
		वापस -ENODEV;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -ENODEV;
		dev_err(&pdev->dev, "platform_get_resource error.\n");
		जाओ clean_up;
	पूर्ण

	ires = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!ires) अणु
		ret = -ENODEV;
		dev_err(&pdev->dev,
			"platform_get_resource IORESOURCE_IRQ error.\n");
		जाओ clean_up;
	पूर्ण

	irq = ires->start;
	irq_trigger = ires->flags & IRQF_TRIGGER_MASK;

	reg = ioremap(res->start, resource_size(res));
	अगर (reg == शून्य) अणु
		ret = -ENOMEM;
		dev_err(&pdev->dev, "ioremap error.\n");
		जाओ clean_up;
	पूर्ण

	अगर (pdev->dev.platक्रमm_data == शून्य) अणु
		dev_err(&pdev->dev, "no platform data\n");
		ret = -ENODEV;
		जाओ clean_up;
	पूर्ण

	/* initialize hcd */
	hcd = usb_create_hcd(&r8a66597_hc_driver, &pdev->dev, (अक्षर *)hcd_name);
	अगर (!hcd) अणु
		ret = -ENOMEM;
		dev_err(&pdev->dev, "Failed to create hcd\n");
		जाओ clean_up;
	पूर्ण
	r8a66597 = hcd_to_r8a66597(hcd);
	स_रखो(r8a66597, 0, माप(काष्ठा r8a66597));
	platक्रमm_set_drvdata(pdev, r8a66597);
	r8a66597->pdata = dev_get_platdata(&pdev->dev);
	r8a66597->irq_sense_low = irq_trigger == IRQF_TRIGGER_LOW;

	अगर (r8a66597->pdata->on_chip) अणु
		snम_लिखो(clk_name, माप(clk_name), "usb%d", pdev->id);
		r8a66597->clk = clk_get(&pdev->dev, clk_name);
		अगर (IS_ERR(r8a66597->clk)) अणु
			dev_err(&pdev->dev, "cannot get clock \"%s\"\n",
				clk_name);
			ret = PTR_ERR(r8a66597->clk);
			जाओ clean_up2;
		पूर्ण
		r8a66597->max_root_hub = 1;
	पूर्ण अन्यथा
		r8a66597->max_root_hub = 2;

	spin_lock_init(&r8a66597->lock);
	समयr_setup(&r8a66597->rh_समयr, r8a66597_समयr, 0);
	r8a66597->reg = reg;

	/* make sure no पूर्णांकerrupts are pending */
	ret = r8a66597_घड़ी_enable(r8a66597);
	अगर (ret < 0)
		जाओ clean_up3;
	disable_controller(r8a66597);

	क्रम (i = 0; i < R8A66597_MAX_NUM_PIPE; i++) अणु
		INIT_LIST_HEAD(&r8a66597->pipe_queue[i]);
		r8a66597->समयrs[i].r8a66597 = r8a66597;
		समयr_setup(&r8a66597->समयrs[i].td, r8a66597_td_समयr, 0);
		समयr_setup(&r8a66597->समयrs[i].पूर्णांकerval,
			    r8a66597_पूर्णांकerval_समयr, 0);
	पूर्ण
	INIT_LIST_HEAD(&r8a66597->child_device);

	hcd->rsrc_start = res->start;
	hcd->has_tt = 1;

	ret = usb_add_hcd(hcd, irq, irq_trigger);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to add hcd\n");
		जाओ clean_up3;
	पूर्ण
	device_wakeup_enable(hcd->self.controller);

	वापस 0;

clean_up3:
	अगर (r8a66597->pdata->on_chip)
		clk_put(r8a66597->clk);
clean_up2:
	usb_put_hcd(hcd);

clean_up:
	अगर (reg)
		iounmap(reg);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver r8a66597_driver = अणु
	.probe =	r8a66597_probe,
	.हटाओ =	r8a66597_हटाओ,
	.driver		= अणु
		.name = hcd_name,
		.pm	= R8A66597_DEV_PM_OPS,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(r8a66597_driver);
