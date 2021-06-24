<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*****************************************************************************/

/*
 *	uss720.c  --  USS720 USB Parport Cable.
 *
 *	Copyright (C) 1999, 2005, 2010
 *	    Thomas Sailer (t.sailer@alumni.ethz.ch)
 *
 *  Based on parport_pc.c
 *
 *  History:
 *   0.1  04.08.1999  Created
 *   0.2  07.08.1999  Some fixes मुख्यly suggested by Tim Waugh
 *		      Interrupt handling currently disabled because
 *		      usb_request_irq crashes somewhere within ohci.c
 *		      क्रम no apparent reason (that is क्रम me, anyway)
 *		      ECP currently untested
 *   0.3  10.08.1999  fixing merge errors
 *   0.4  13.08.1999  Added Venकरोr/Product ID of Brad Hard's cable
 *   0.5  20.09.1999  usb_control_msg wrapper used
 *        Nov01.2000  usb_device_table support by Adam J. Richter
 *        08.04.2001  Identअगरy version on module load.  gb
 *   0.6  02.09.2005  Fix "scheduling in interrupt" problem by making save/restore
 *                    context asynchronous
 *
 */

/*****************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/socket.h>
#समावेश <linux/parport.h>
#समावेश <linux/init.h>
#समावेश <linux/usb.h>
#समावेश <linux/delay.h>
#समावेश <linux/completion.h>
#समावेश <linux/kref.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#घोषणा DRIVER_AUTHOR "Thomas M. Sailer, t.sailer@alumni.ethz.ch"
#घोषणा DRIVER_DESC "USB Parport Cable driver for Cables using the Lucent Technologies USS720 Chip"

/* --------------------------------------------------------------------- */

काष्ठा parport_uss720_निजी अणु
	काष्ठा usb_device *usbdev;
	काष्ठा parport *pp;
	काष्ठा kref ref_count;
	__u8 reg[7];  /* USB रेजिस्टरs */
	काष्ठा list_head asynclist;
	spinlock_t asynघड़ी;
पूर्ण;

काष्ठा uss720_async_request अणु
	काष्ठा parport_uss720_निजी *priv;
	काष्ठा kref ref_count;
	काष्ठा list_head asynclist;
	काष्ठा completion compl;
	काष्ठा urb *urb;
	काष्ठा usb_ctrlrequest *dr;
	__u8 reg[7];
पूर्ण;

/* --------------------------------------------------------------------- */

अटल व्योम destroy_priv(काष्ठा kref *kref)
अणु
	काष्ठा parport_uss720_निजी *priv = container_of(kref, काष्ठा parport_uss720_निजी, ref_count);

	dev_dbg(&priv->usbdev->dev, "destroying priv datastructure\n");
	usb_put_dev(priv->usbdev);
	kमुक्त(priv);
पूर्ण

अटल व्योम destroy_async(काष्ठा kref *kref)
अणु
	काष्ठा uss720_async_request *rq = container_of(kref, काष्ठा uss720_async_request, ref_count);
	काष्ठा parport_uss720_निजी *priv = rq->priv;
	अचिन्हित दीर्घ flags;

	अगर (likely(rq->urb))
		usb_मुक्त_urb(rq->urb);
	kमुक्त(rq->dr);
	spin_lock_irqsave(&priv->asynघड़ी, flags);
	list_del_init(&rq->asynclist);
	spin_unlock_irqrestore(&priv->asynघड़ी, flags);
	kमुक्त(rq);
	kref_put(&priv->ref_count, destroy_priv);
पूर्ण

/* --------------------------------------------------------------------- */

अटल व्योम async_complete(काष्ठा urb *urb)
अणु
	काष्ठा uss720_async_request *rq;
	काष्ठा parport *pp;
	काष्ठा parport_uss720_निजी *priv;
	पूर्णांक status = urb->status;

	rq = urb->context;
	priv = rq->priv;
	pp = priv->pp;
	अगर (status) अणु
		dev_err(&urb->dev->dev, "async_complete: urb error %d\n",
			status);
	पूर्ण अन्यथा अगर (rq->dr->bRequest == 3) अणु
		स_नकल(priv->reg, rq->reg, माप(priv->reg));
#अगर 0
		dev_dbg(&priv->usbdev->dev, "async_complete regs %7ph\n",
			priv->reg);
#पूर्ण_अगर
		/* अगर nAck पूर्णांकerrupts are enabled and we have an पूर्णांकerrupt, call the पूर्णांकerrupt procedure */
		अगर (rq->reg[2] & rq->reg[1] & 0x10 && pp)
			parport_generic_irq(pp);
	पूर्ण
	complete(&rq->compl);
	kref_put(&rq->ref_count, destroy_async);
पूर्ण

अटल काष्ठा uss720_async_request *submit_async_request(काष्ठा parport_uss720_निजी *priv,
							 __u8 request, __u8 requesttype, __u16 value, __u16 index,
							 gfp_t mem_flags)
अणु
	काष्ठा usb_device *usbdev;
	काष्ठा uss720_async_request *rq;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!priv)
		वापस शून्य;
	usbdev = priv->usbdev;
	अगर (!usbdev)
		वापस शून्य;
	rq = kzalloc(माप(काष्ठा uss720_async_request), mem_flags);
	अगर (!rq)
		वापस शून्य;
	kref_init(&rq->ref_count);
	INIT_LIST_HEAD(&rq->asynclist);
	init_completion(&rq->compl);
	kref_get(&priv->ref_count);
	rq->priv = priv;
	rq->urb = usb_alloc_urb(0, mem_flags);
	अगर (!rq->urb) अणु
		kref_put(&rq->ref_count, destroy_async);
		वापस शून्य;
	पूर्ण
	rq->dr = kदो_स्मृति(माप(*rq->dr), mem_flags);
	अगर (!rq->dr) अणु
		kref_put(&rq->ref_count, destroy_async);
		वापस शून्य;
	पूर्ण
	rq->dr->bRequestType = requesttype;
	rq->dr->bRequest = request;
	rq->dr->wValue = cpu_to_le16(value);
	rq->dr->wIndex = cpu_to_le16(index);
	rq->dr->wLength = cpu_to_le16((request == 3) ? माप(rq->reg) : 0);
	usb_fill_control_urb(rq->urb, usbdev, (requesttype & 0x80) ? usb_rcvctrlpipe(usbdev, 0) : usb_sndctrlpipe(usbdev, 0),
			     (अचिन्हित अक्षर *)rq->dr,
			     (request == 3) ? rq->reg : शून्य, (request == 3) ? माप(rq->reg) : 0, async_complete, rq);
	/* rq->urb->transfer_flags |= URB_ASYNC_UNLINK; */
	spin_lock_irqsave(&priv->asynघड़ी, flags);
	list_add_tail(&rq->asynclist, &priv->asynclist);
	spin_unlock_irqrestore(&priv->asynघड़ी, flags);
	kref_get(&rq->ref_count);
	ret = usb_submit_urb(rq->urb, mem_flags);
	अगर (!ret)
		वापस rq;
	destroy_async(&rq->ref_count);
	dev_err(&usbdev->dev, "submit_async_request submit_urb failed with %d\n", ret);
	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक समाप्त_all_async_requests_priv(काष्ठा parport_uss720_निजी *priv)
अणु
	काष्ठा uss720_async_request *rq;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ret = 0;

	spin_lock_irqsave(&priv->asynघड़ी, flags);
	list_क्रम_each_entry(rq, &priv->asynclist, asynclist) अणु
		usb_unlink_urb(rq->urb);
		ret++;
	पूर्ण
	spin_unlock_irqrestore(&priv->asynघड़ी, flags);
	वापस ret;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक get_1284_रेजिस्टर(काष्ठा parport *pp, अचिन्हित अक्षर reg, अचिन्हित अक्षर *val, gfp_t mem_flags)
अणु
	काष्ठा parport_uss720_निजी *priv;
	काष्ठा uss720_async_request *rq;
	अटल स्थिर अचिन्हित अक्षर regindex[9] = अणु
		4, 0, 1, 5, 5, 0, 2, 3, 6
	पूर्ण;
	पूर्णांक ret;

	अगर (!pp)
		वापस -EIO;
	priv = pp->निजी_data;
	rq = submit_async_request(priv, 3, 0xc0, ((अचिन्हित पूर्णांक)reg) << 8, 0, mem_flags);
	अगर (!rq) अणु
		dev_err(&priv->usbdev->dev, "get_1284_register(%u) failed",
			(अचिन्हित पूर्णांक)reg);
		वापस -EIO;
	पूर्ण
	अगर (!val) अणु
		kref_put(&rq->ref_count, destroy_async);
		वापस 0;
	पूर्ण
	अगर (रुको_क्रम_completion_समयout(&rq->compl, HZ)) अणु
		ret = rq->urb->status;
		*val = priv->reg[(reg >= 9) ? 0 : regindex[reg]];
		अगर (ret)
			prपूर्णांकk(KERN_WARNING "get_1284_register: "
			       "usb error %d\n", ret);
		kref_put(&rq->ref_count, destroy_async);
		वापस ret;
	पूर्ण
	prपूर्णांकk(KERN_WARNING "get_1284_register timeout\n");
	समाप्त_all_async_requests_priv(priv);
	वापस -EIO;
पूर्ण

अटल पूर्णांक set_1284_रेजिस्टर(काष्ठा parport *pp, अचिन्हित अक्षर reg, अचिन्हित अक्षर val, gfp_t mem_flags)
अणु
	काष्ठा parport_uss720_निजी *priv;
	काष्ठा uss720_async_request *rq;

	अगर (!pp)
		वापस -EIO;
	priv = pp->निजी_data;
	rq = submit_async_request(priv, 4, 0x40, (((अचिन्हित पूर्णांक)reg) << 8) | val, 0, mem_flags);
	अगर (!rq) अणु
		dev_err(&priv->usbdev->dev, "set_1284_register(%u,%u) failed",
			(अचिन्हित पूर्णांक)reg, (अचिन्हित पूर्णांक)val);
		वापस -EIO;
	पूर्ण
	kref_put(&rq->ref_count, destroy_async);
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

/* ECR modes */
#घोषणा ECR_SPP 00
#घोषणा ECR_PS2 01
#घोषणा ECR_PPF 02
#घोषणा ECR_ECP 03
#घोषणा ECR_EPP 04

/* Safely change the mode bits in the ECR */
अटल पूर्णांक change_mode(काष्ठा parport *pp, पूर्णांक m)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;
	पूर्णांक mode;
	__u8 reg;

	अगर (get_1284_रेजिस्टर(pp, 6, &reg, GFP_KERNEL))
		वापस -EIO;
	/* Bits <7:5> contain the mode. */
	mode = (priv->reg[2] >> 5) & 0x7;
	अगर (mode == m)
		वापस 0;
	/* We have to go through mode 000 or 001 */
	अगर (mode > ECR_PS2 && m > ECR_PS2)
		अगर (change_mode(pp, ECR_PS2))
			वापस -EIO;

	अगर (m <= ECR_PS2 && !(priv->reg[1] & 0x20)) अणु
		/* This mode resets the FIFO, so we may
		 * have to रुको क्रम it to drain first. */
		अचिन्हित दीर्घ expire = jअगरfies + pp->physport->cad->समयout;
		चयन (mode) अणु
		हाल ECR_PPF: /* Parallel Port FIFO mode */
		हाल ECR_ECP: /* ECP Parallel Port mode */
			/* Poll slowly. */
			क्रम (;;) अणु
				अगर (get_1284_रेजिस्टर(pp, 6, &reg, GFP_KERNEL))
					वापस -EIO;
				अगर (priv->reg[2] & 0x01)
					अवरोध;
				अगर (समय_after_eq (jअगरfies, expire))
					/* The FIFO is stuck. */
					वापस -EBUSY;
				msleep_पूर्णांकerruptible(10);
				अगर (संकेत_pending (current))
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	/* Set the mode. */
	अगर (set_1284_रेजिस्टर(pp, 6, m << 5, GFP_KERNEL))
		वापस -EIO;
	अगर (get_1284_रेजिस्टर(pp, 6, &reg, GFP_KERNEL))
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * Clear TIMEOUT BIT in EPP MODE
 */
अटल पूर्णांक clear_epp_समयout(काष्ठा parport *pp)
अणु
	अचिन्हित अक्षर stat;

	अगर (get_1284_रेजिस्टर(pp, 1, &stat, GFP_KERNEL))
		वापस 1;
	वापस stat & 1;
पूर्ण

/*
 * Access functions.
 */
#अगर 0
अटल पूर्णांक uss720_irq(पूर्णांक usbstatus, व्योम *buffer, पूर्णांक len, व्योम *dev_id)
अणु
	काष्ठा parport *pp = (काष्ठा parport *)dev_id;
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	

	अगर (usbstatus != 0 || len < 4 || !buffer)
		वापस 1;
	स_नकल(priv->reg, buffer, 4);
	/* अगर nAck पूर्णांकerrupts are enabled and we have an पूर्णांकerrupt, call the पूर्णांकerrupt procedure */
	अगर (priv->reg[2] & priv->reg[1] & 0x10)
		parport_generic_irq(pp);
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल व्योम parport_uss720_ग_लिखो_data(काष्ठा parport *pp, अचिन्हित अक्षर d)
अणु
	set_1284_रेजिस्टर(pp, 0, d, GFP_KERNEL);
पूर्ण

अटल अचिन्हित अक्षर parport_uss720_पढ़ो_data(काष्ठा parport *pp)
अणु
	अचिन्हित अक्षर ret;

	अगर (get_1284_रेजिस्टर(pp, 0, &ret, GFP_KERNEL))
		वापस 0;
	वापस ret;
पूर्ण

अटल व्योम parport_uss720_ग_लिखो_control(काष्ठा parport *pp, अचिन्हित अक्षर d)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	

	d = (d & 0xf) | (priv->reg[1] & 0xf0);
	अगर (set_1284_रेजिस्टर(pp, 2, d, GFP_KERNEL))
		वापस;
	priv->reg[1] = d;
पूर्ण

अटल अचिन्हित अक्षर parport_uss720_पढ़ो_control(काष्ठा parport *pp)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	
	वापस priv->reg[1] & 0xf; /* Use soft copy */
पूर्ण

अटल अचिन्हित अक्षर parport_uss720_frob_control(काष्ठा parport *pp, अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	
	अचिन्हित अक्षर d;

	mask &= 0x0f;
	val &= 0x0f;
	d = (priv->reg[1] & (~mask)) ^ val;
	अगर (set_1284_रेजिस्टर(pp, 2, d, GFP_ATOMIC))
		वापस 0;
	priv->reg[1] = d;
	वापस d & 0xf;
पूर्ण

अटल अचिन्हित अक्षर parport_uss720_पढ़ो_status(काष्ठा parport *pp)
अणु
	अचिन्हित अक्षर ret;

	अगर (get_1284_रेजिस्टर(pp, 1, &ret, GFP_ATOMIC))
		वापस 0;
	वापस ret & 0xf8;
पूर्ण

अटल व्योम parport_uss720_disable_irq(काष्ठा parport *pp)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	
	अचिन्हित अक्षर d;

	d = priv->reg[1] & ~0x10;
	अगर (set_1284_रेजिस्टर(pp, 2, d, GFP_KERNEL))
		वापस;
	priv->reg[1] = d;
पूर्ण

अटल व्योम parport_uss720_enable_irq(काष्ठा parport *pp)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	
	अचिन्हित अक्षर d;

	d = priv->reg[1] | 0x10;
	अगर (set_1284_रेजिस्टर(pp, 2, d, GFP_KERNEL))
		वापस;
	priv->reg[1] = d;
पूर्ण

अटल व्योम parport_uss720_data_क्रमward (काष्ठा parport *pp)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	
	अचिन्हित अक्षर d;

	d = priv->reg[1] & ~0x20;
	अगर (set_1284_रेजिस्टर(pp, 2, d, GFP_KERNEL))
		वापस;
	priv->reg[1] = d;
पूर्ण

अटल व्योम parport_uss720_data_reverse (काष्ठा parport *pp)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	
	अचिन्हित अक्षर d;

	d = priv->reg[1] | 0x20;
	अगर (set_1284_रेजिस्टर(pp, 2, d, GFP_KERNEL))
		वापस;
	priv->reg[1] = d;
पूर्ण

अटल व्योम parport_uss720_init_state(काष्ठा pardevice *dev, काष्ठा parport_state *s)
अणु
	s->u.pc.ctr = 0xc | (dev->irq_func ? 0x10 : 0x0);
	s->u.pc.ecr = 0x24;
पूर्ण

अटल व्योम parport_uss720_save_state(काष्ठा parport *pp, काष्ठा parport_state *s)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	

#अगर 0
	अगर (get_1284_रेजिस्टर(pp, 2, शून्य, GFP_ATOMIC))
		वापस;
#पूर्ण_अगर
	s->u.pc.ctr = priv->reg[1];
	s->u.pc.ecr = priv->reg[2];
पूर्ण

अटल व्योम parport_uss720_restore_state(काष्ठा parport *pp, काष्ठा parport_state *s)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;

	set_1284_रेजिस्टर(pp, 2, s->u.pc.ctr, GFP_ATOMIC);
	set_1284_रेजिस्टर(pp, 6, s->u.pc.ecr, GFP_ATOMIC);
	get_1284_रेजिस्टर(pp, 2, शून्य, GFP_ATOMIC);
	priv->reg[1] = s->u.pc.ctr;
	priv->reg[2] = s->u.pc.ecr;
पूर्ण

अटल माप_प्रकार parport_uss720_epp_पढ़ो_data(काष्ठा parport *pp, व्योम *buf, माप_प्रकार length, पूर्णांक flags)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	
	माप_प्रकार got = 0;

	अगर (change_mode(pp, ECR_EPP))
		वापस 0;
	क्रम (; got < length; got++) अणु
		अगर (get_1284_रेजिस्टर(pp, 4, (अक्षर *)buf, GFP_KERNEL))
			अवरोध;
		buf++;
		अगर (priv->reg[0] & 0x01) अणु
			clear_epp_समयout(pp);
			अवरोध;
		पूर्ण
	पूर्ण
	change_mode(pp, ECR_PS2);
	वापस got;
पूर्ण

अटल माप_प्रकार parport_uss720_epp_ग_लिखो_data(काष्ठा parport *pp, स्थिर व्योम *buf, माप_प्रकार length, पूर्णांक flags)
अणु
#अगर 0
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	
	माप_प्रकार written = 0;

	अगर (change_mode(pp, ECR_EPP))
		वापस 0;
	क्रम (; written < length; written++) अणु
		अगर (set_1284_रेजिस्टर(pp, 4, (अक्षर *)buf, GFP_KERNEL))
			अवरोध;
		((अक्षर*)buf)++;
		अगर (get_1284_रेजिस्टर(pp, 1, शून्य, GFP_KERNEL))
			अवरोध;
		अगर (priv->reg[0] & 0x01) अणु
			clear_epp_समयout(pp);
			अवरोध;
		पूर्ण
	पूर्ण
	change_mode(pp, ECR_PS2);
	वापस written;
#अन्यथा
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;
	काष्ठा usb_device *usbdev = priv->usbdev;
	पूर्णांक rlen;
	पूर्णांक i;

	अगर (!usbdev)
		वापस 0;
	अगर (change_mode(pp, ECR_EPP))
		वापस 0;
	i = usb_bulk_msg(usbdev, usb_sndbulkpipe(usbdev, 1), (व्योम *)buf, length, &rlen, 20000);
	अगर (i)
		prपूर्णांकk(KERN_ERR "uss720: sendbulk ep 1 buf %p len %zu rlen %u\n", buf, length, rlen);
	change_mode(pp, ECR_PS2);
	वापस rlen;
#पूर्ण_अगर
पूर्ण

अटल माप_प्रकार parport_uss720_epp_पढ़ो_addr(काष्ठा parport *pp, व्योम *buf, माप_प्रकार length, पूर्णांक flags)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	
	माप_प्रकार got = 0;

	अगर (change_mode(pp, ECR_EPP))
		वापस 0;
	क्रम (; got < length; got++) अणु
		अगर (get_1284_रेजिस्टर(pp, 3, (अक्षर *)buf, GFP_KERNEL))
			अवरोध;
		buf++;
		अगर (priv->reg[0] & 0x01) अणु
			clear_epp_समयout(pp);
			अवरोध;
		पूर्ण
	पूर्ण
	change_mode(pp, ECR_PS2);
	वापस got;
पूर्ण

अटल माप_प्रकार parport_uss720_epp_ग_लिखो_addr(काष्ठा parport *pp, स्थिर व्योम *buf, माप_प्रकार length, पूर्णांक flags)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;	
	माप_प्रकार written = 0;

	अगर (change_mode(pp, ECR_EPP))
		वापस 0;
	क्रम (; written < length; written++) अणु
		अगर (set_1284_रेजिस्टर(pp, 3, *(अक्षर *)buf, GFP_KERNEL))
			अवरोध;
		buf++;
		अगर (get_1284_रेजिस्टर(pp, 1, शून्य, GFP_KERNEL))
			अवरोध;
		अगर (priv->reg[0] & 0x01) अणु
			clear_epp_समयout(pp);
			अवरोध;
		पूर्ण
	पूर्ण
	change_mode(pp, ECR_PS2);
	वापस written;
पूर्ण

अटल माप_प्रकार parport_uss720_ecp_ग_लिखो_data(काष्ठा parport *pp, स्थिर व्योम *buffer, माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;
	काष्ठा usb_device *usbdev = priv->usbdev;
	पूर्णांक rlen;
	पूर्णांक i;

	अगर (!usbdev)
		वापस 0;
	अगर (change_mode(pp, ECR_ECP))
		वापस 0;
	i = usb_bulk_msg(usbdev, usb_sndbulkpipe(usbdev, 1), (व्योम *)buffer, len, &rlen, 20000);
	अगर (i)
		prपूर्णांकk(KERN_ERR "uss720: sendbulk ep 1 buf %p len %zu rlen %u\n", buffer, len, rlen);
	change_mode(pp, ECR_PS2);
	वापस rlen;
पूर्ण

अटल माप_प्रकार parport_uss720_ecp_पढ़ो_data(काष्ठा parport *pp, व्योम *buffer, माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;
	काष्ठा usb_device *usbdev = priv->usbdev;
	पूर्णांक rlen;
	पूर्णांक i;

	अगर (!usbdev)
		वापस 0;
	अगर (change_mode(pp, ECR_ECP))
		वापस 0;
	i = usb_bulk_msg(usbdev, usb_rcvbulkpipe(usbdev, 2), buffer, len, &rlen, 20000);
	अगर (i)
		prपूर्णांकk(KERN_ERR "uss720: recvbulk ep 2 buf %p len %zu rlen %u\n", buffer, len, rlen);
	change_mode(pp, ECR_PS2);
	वापस rlen;
पूर्ण

अटल माप_प्रकार parport_uss720_ecp_ग_लिखो_addr(काष्ठा parport *pp, स्थिर व्योम *buffer, माप_प्रकार len, पूर्णांक flags)
अणु
	माप_प्रकार written = 0;

	अगर (change_mode(pp, ECR_ECP))
		वापस 0;
	क्रम (; written < len; written++) अणु
		अगर (set_1284_रेजिस्टर(pp, 5, *(अक्षर *)buffer, GFP_KERNEL))
			अवरोध;
		buffer++;
	पूर्ण
	change_mode(pp, ECR_PS2);
	वापस written;
पूर्ण

अटल माप_प्रकार parport_uss720_ग_लिखो_compat(काष्ठा parport *pp, स्थिर व्योम *buffer, माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा parport_uss720_निजी *priv = pp->निजी_data;
	काष्ठा usb_device *usbdev = priv->usbdev;
	पूर्णांक rlen;
	पूर्णांक i;

	अगर (!usbdev)
		वापस 0;
	अगर (change_mode(pp, ECR_PPF))
		वापस 0;
	i = usb_bulk_msg(usbdev, usb_sndbulkpipe(usbdev, 1), (व्योम *)buffer, len, &rlen, 20000);
	अगर (i)
		prपूर्णांकk(KERN_ERR "uss720: sendbulk ep 1 buf %p len %zu rlen %u\n", buffer, len, rlen);
	change_mode(pp, ECR_PS2);
	वापस rlen;
पूर्ण

/* --------------------------------------------------------------------- */

अटल काष्ठा parport_operations parport_uss720_ops = 
अणु
	.owner =		THIS_MODULE,
	.ग_लिखो_data =		parport_uss720_ग_लिखो_data,
	.पढ़ो_data =		parport_uss720_पढ़ो_data,

	.ग_लिखो_control =	parport_uss720_ग_लिखो_control,
	.पढ़ो_control =		parport_uss720_पढ़ो_control,
	.frob_control =		parport_uss720_frob_control,

	.पढ़ो_status =		parport_uss720_पढ़ो_status,

	.enable_irq =		parport_uss720_enable_irq,
	.disable_irq =		parport_uss720_disable_irq,

	.data_क्रमward =		parport_uss720_data_क्रमward,
	.data_reverse =		parport_uss720_data_reverse,

	.init_state =		parport_uss720_init_state,
	.save_state =		parport_uss720_save_state,
	.restore_state =	parport_uss720_restore_state,

	.epp_ग_लिखो_data =	parport_uss720_epp_ग_लिखो_data,
	.epp_पढ़ो_data =	parport_uss720_epp_पढ़ो_data,
	.epp_ग_लिखो_addr =	parport_uss720_epp_ग_लिखो_addr,
	.epp_पढ़ो_addr =	parport_uss720_epp_पढ़ो_addr,

	.ecp_ग_लिखो_data =	parport_uss720_ecp_ग_लिखो_data,
	.ecp_पढ़ो_data =	parport_uss720_ecp_पढ़ो_data,
	.ecp_ग_लिखो_addr =	parport_uss720_ecp_ग_लिखो_addr,

	.compat_ग_लिखो_data =	parport_uss720_ग_लिखो_compat,
	.nibble_पढ़ो_data =	parport_ieee1284_पढ़ो_nibble,
	.byte_पढ़ो_data =	parport_ieee1284_पढ़ो_byte,
पूर्ण;

/* --------------------------------------------------------------------- */

अटल पूर्णांक uss720_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usbdev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface;
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;
	काष्ठा parport_uss720_निजी *priv;
	काष्ठा parport *pp;
	अचिन्हित अक्षर reg;
	पूर्णांक i;

	dev_dbg(&पूर्णांकf->dev, "probe: vendor id 0x%x, device id 0x%x\n",
		le16_to_cpu(usbdev->descriptor.idVenकरोr),
		le16_to_cpu(usbdev->descriptor.idProduct));

	/* our known पूर्णांकerfaces have 3 alternate settings */
	अगर (पूर्णांकf->num_altsetting != 3) अणु
		usb_put_dev(usbdev);
		वापस -ENODEV;
	पूर्ण
	i = usb_set_पूर्णांकerface(usbdev, पूर्णांकf->altsetting->desc.bInterfaceNumber, 2);
	dev_dbg(&पूर्णांकf->dev, "set interface result %d\n", i);

	पूर्णांकerface = पूर्णांकf->cur_altsetting;

	अगर (पूर्णांकerface->desc.bNumEndpoपूर्णांकs < 3) अणु
		usb_put_dev(usbdev);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Allocate parport पूर्णांकerface 
	 */
	priv = kzalloc(माप(काष्ठा parport_uss720_निजी), GFP_KERNEL);
	अगर (!priv) अणु
		usb_put_dev(usbdev);
		वापस -ENOMEM;
	पूर्ण
	priv->pp = शून्य;
	priv->usbdev = usbdev;
	kref_init(&priv->ref_count);
	spin_lock_init(&priv->asynघड़ी);
	INIT_LIST_HEAD(&priv->asynclist);
	pp = parport_रेजिस्टर_port(0, PARPORT_IRQ_NONE, PARPORT_DMA_NONE, &parport_uss720_ops);
	अगर (!pp) अणु
		prपूर्णांकk(KERN_WARNING "uss720: could not register parport\n");
		जाओ probe_पात;
	पूर्ण

	priv->pp = pp;
	pp->निजी_data = priv;
	pp->modes = PARPORT_MODE_PCSPP | PARPORT_MODE_TRISTATE | PARPORT_MODE_EPP | PARPORT_MODE_ECP | PARPORT_MODE_COMPAT;

	/* set the USS720 control रेजिस्टर to manual mode, no ECP compression, enable all पूर्णांकs */
	set_1284_रेजिस्टर(pp, 7, 0x00, GFP_KERNEL);
	set_1284_रेजिस्टर(pp, 6, 0x30, GFP_KERNEL);  /* PS/2 mode */
	set_1284_रेजिस्टर(pp, 2, 0x0c, GFP_KERNEL);
	/* debugging */
	get_1284_रेजिस्टर(pp, 0, &reg, GFP_KERNEL);
	dev_dbg(&पूर्णांकf->dev, "reg: %7ph\n", priv->reg);

	i = usb_find_last_पूर्णांक_in_endpoपूर्णांक(पूर्णांकerface, &epd);
	अगर (!i) अणु
		dev_dbg(&पूर्णांकf->dev, "epaddr %d interval %d\n",
				epd->bEndpoपूर्णांकAddress, epd->bInterval);
	पूर्ण
	parport_announce_port(pp);

	usb_set_पूर्णांकfdata(पूर्णांकf, pp);
	usb_put_dev(usbdev);
	वापस 0;

probe_पात:
	समाप्त_all_async_requests_priv(priv);
	kref_put(&priv->ref_count, destroy_priv);
	वापस -ENODEV;
पूर्ण

अटल व्योम uss720_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा parport *pp = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा parport_uss720_निजी *priv;

	dev_dbg(&पूर्णांकf->dev, "disconnect\n");
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (pp) अणु
		priv = pp->निजी_data;
		priv->usbdev = शून्य;
		priv->pp = शून्य;
		dev_dbg(&पूर्णांकf->dev, "parport_remove_port\n");
		parport_हटाओ_port(pp);
		parport_put_port(pp);
		समाप्त_all_async_requests_priv(priv);
		kref_put(&priv->ref_count, destroy_priv);
	पूर्ण
	dev_dbg(&पूर्णांकf->dev, "disconnect done\n");
पूर्ण

/* table of cables that work through this driver */
अटल स्थिर काष्ठा usb_device_id uss720_table[] = अणु
	अणु USB_DEVICE(0x047e, 0x1001) पूर्ण,
	अणु USB_DEVICE(0x04b8, 0x0002) पूर्ण,
	अणु USB_DEVICE(0x04b8, 0x0003) पूर्ण,
	अणु USB_DEVICE(0x050d, 0x0002) पूर्ण,
	अणु USB_DEVICE(0x050d, 0x1202) पूर्ण,
	अणु USB_DEVICE(0x0557, 0x2001) पूर्ण,
	अणु USB_DEVICE(0x05ab, 0x0002) पूर्ण,
	अणु USB_DEVICE(0x06c6, 0x0100) पूर्ण,
	अणु USB_DEVICE(0x0729, 0x1284) पूर्ण,
	अणु USB_DEVICE(0x1293, 0x0002) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE (usb, uss720_table);


अटल काष्ठा usb_driver uss720_driver = अणु
	.name =		"uss720",
	.probe =	uss720_probe,
	.disconnect =	uss720_disconnect,
	.id_table =	uss720_table,
पूर्ण;

/* --------------------------------------------------------------------- */

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

अटल पूर्णांक __init uss720_init(व्योम)
अणु
	पूर्णांक retval;
	retval = usb_रेजिस्टर(&uss720_driver);
	अगर (retval)
		जाओ out;

	prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": " DRIVER_DESC "\n");
	prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": NOTE: this is a special purpose "
	       "driver to allow nonstandard\n");
	prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": protocols (eg. bitbang) over "
	       "USS720 usb to parallel cables\n");
	prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": If you just want to connect to a "
	       "printer, use usblp instead\n");
out:
	वापस retval;
पूर्ण

अटल व्योम __निकास uss720_cleanup(व्योम)
अणु
	usb_deरेजिस्टर(&uss720_driver);
पूर्ण

module_init(uss720_init);
module_निकास(uss720_cleanup);

/* --------------------------------------------------------------------- */
