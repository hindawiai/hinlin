<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the NXP ISP1761 device controller
 *
 * Copyright 2014 Ideas on Board Oy
 *
 * Contacts:
 *	Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित _ISP1760_UDC_H_
#घोषणा _ISP1760_UDC_H_

#समावेश <linux/ioport.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/usb/gadget.h>

काष्ठा isp1760_device;
काष्ठा isp1760_udc;

क्रमागत isp1760_ctrl_state अणु
	ISP1760_CTRL_SETUP,		/* Waiting क्रम a SETUP transaction */
	ISP1760_CTRL_DATA_IN,		/* Setup received, data IN stage */
	ISP1760_CTRL_DATA_OUT,		/* Setup received, data OUT stage */
	ISP1760_CTRL_STATUS,		/* 0-length request in status stage */
पूर्ण;

काष्ठा isp1760_ep अणु
	काष्ठा isp1760_udc *udc;
	काष्ठा usb_ep ep;

	काष्ठा list_head queue;

	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक maxpacket;
	अक्षर name[7];

	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc;

	bool rx_pending;
	bool halted;
	bool wedged;
पूर्ण;

/**
 * काष्ठा isp1760_udc - UDC state inक्रमmation
 * irq: IRQ number
 * irqname: IRQ name (as passed to request_irq)
 * regs: Base address of the UDC रेजिस्टरs
 * driver: Gadget driver
 * gadget: Gadget device
 * lock: Protects driver, vbus_समयr, ep, ep0_*, DC_EPINDEX रेजिस्टर
 * ep: Array of endpoपूर्णांकs
 * ep0_state: Control request state क्रम endpoपूर्णांक 0
 * ep0_dir: Direction of the current control request
 * ep0_length: Length of the current control request
 * connected: Tracks gadget driver bus connection state
 */
काष्ठा isp1760_udc अणु
#अगर_घोषित CONFIG_USB_ISP1761_UDC
	काष्ठा isp1760_device *isp;

	पूर्णांक irq;
	अक्षर *irqname;
	व्योम __iomem *regs;

	काष्ठा usb_gadget_driver *driver;
	काष्ठा usb_gadget gadget;

	spinlock_t lock;
	काष्ठा समयr_list vbus_समयr;

	काष्ठा isp1760_ep ep[15];

	क्रमागत isp1760_ctrl_state ep0_state;
	u8 ep0_dir;
	u16 ep0_length;

	bool connected;

	अचिन्हित पूर्णांक devstatus;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_USB_ISP1761_UDC
पूर्णांक isp1760_udc_रेजिस्टर(काष्ठा isp1760_device *isp, पूर्णांक irq,
			 अचिन्हित दीर्घ irqflags);
व्योम isp1760_udc_unरेजिस्टर(काष्ठा isp1760_device *isp);
#अन्यथा
अटल अंतरभूत पूर्णांक isp1760_udc_रेजिस्टर(काष्ठा isp1760_device *isp, पूर्णांक irq,
				       अचिन्हित दीर्घ irqflags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम isp1760_udc_unरेजिस्टर(काष्ठा isp1760_device *isp)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
