<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mos7720.c
 *   Controls the Moschip 7720 usb to dual port serial converter
 *
 * Copyright 2006 Moschip Semiconductor Tech. Ltd.
 *
 * Developed by:
 * 	Vijaya Kumar <vijaykumar.gn@gmail.com>
 *	Ajay Kumar <naanuajay@yahoo.com>
 *	Gurudeva <ngurudeva@yahoo.com>
 *
 * Cleaned up from the original by:
 *	Greg Kroah-Harपंचांगan <gregkh@suse.de>
 *
 * Originally based on drivers/usb/serial/io_edgeport.c which is:
 *	Copyright (C) 2000 Inside Out Networks, All rights reserved.
 *	Copyright (C) 2001-2002 Greg Kroah-Harपंचांगan <greg@kroah.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/parport.h>

#घोषणा DRIVER_AUTHOR "Aspire Communications pvt Ltd."
#घोषणा DRIVER_DESC "Moschip USB Serial Driver"

/* शेष urb समयout */
#घोषणा MOS_WDR_TIMEOUT	5000

#घोषणा MOS_MAX_PORT	0x02
#घोषणा MOS_WRITE	0x0E
#घोषणा MOS_READ	0x0D

/* Interrupt Routines Defines	*/
#घोषणा SERIAL_IIR_RLS	0x06
#घोषणा SERIAL_IIR_RDA	0x04
#घोषणा SERIAL_IIR_CTI	0x0c
#घोषणा SERIAL_IIR_THR	0x02
#घोषणा SERIAL_IIR_MS	0x00

#घोषणा NUM_URBS			16	/* URB Count */
#घोषणा URB_TRANSFER_BUFFER_SIZE	32	/* URB Size */

/* This काष्ठाure holds all of the local serial port inक्रमmation */
काष्ठा moschip_port अणु
	__u8	shaकरोwLCR;		/* last LCR value received */
	__u8	shaकरोwMCR;		/* last MCR value received */
	__u8	shaकरोwMSR;		/* last MSR value received */
	अक्षर			खोलो;
	काष्ठा usb_serial_port	*port;	/* loop back to the owner */
	काष्ठा urb		*ग_लिखो_urb_pool[NUM_URBS];
पूर्ण;

#घोषणा USB_VENDOR_ID_MOSCHIP		0x9710
#घोषणा MOSCHIP_DEVICE_ID_7720		0x7720
#घोषणा MOSCHIP_DEVICE_ID_7715		0x7715

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_MOSCHIP, MOSCHIP_DEVICE_ID_7720) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_MOSCHIP, MOSCHIP_DEVICE_ID_7715) पूर्ण,
	अणु पूर्ण /* terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

#अगर_घोषित CONFIG_USB_SERIAL_MOS7715_PARPORT

/* initial values क्रम parport regs */
#घोषणा DCR_INIT_VAL       0x0c	/* SLCTIN, nINIT */
#घोषणा ECR_INIT_VAL       0x00	/* SPP mode */

क्रमागत mos7715_pp_modes अणु
	SPP = 0<<5,
	PS2 = 1<<5,      /* moschip calls this 'NIBBLE' mode */
	PPF = 2<<5,	 /* moschip calls this 'CB-FIFO mode */
पूर्ण;

काष्ठा mos7715_parport अणु
	काष्ठा parport          *pp;	       /* back to containing काष्ठा */
	काष्ठा kref             ref_count;     /* to instance of this काष्ठा */
	bool                    msg_pending;   /* usb sync call pending */
	काष्ठा completion       syncmsg_compl; /* usb sync call completed */
	काष्ठा work_काष्ठा      work;          /* restore deferred ग_लिखोs */
	काष्ठा usb_serial       *serial;       /* back to containing काष्ठा */
	__u8	                shaकरोwECR;     /* parallel port regs... */
	__u8	                shaकरोwDCR;
	atomic_t                shaकरोwDSR;     /* updated in पूर्णांक-in callback */
पूर्ण;

/* lock guards against dereferencing शून्य ptr in parport ops callbacks */
अटल DEFINE_SPINLOCK(release_lock);

#पूर्ण_अगर	/* CONFIG_USB_SERIAL_MOS7715_PARPORT */

अटल स्थिर अचिन्हित पूर्णांक dummy; /* क्रम clarity in रेजिस्टर access fns */

क्रमागत mos_regs अणु
	MOS7720_THR,		  /* serial port regs */
	MOS7720_RHR,
	MOS7720_IER,
	MOS7720_FCR,
	MOS7720_ISR,
	MOS7720_LCR,
	MOS7720_MCR,
	MOS7720_LSR,
	MOS7720_MSR,
	MOS7720_SPR,
	MOS7720_DLL,
	MOS7720_DLM,
	MOS7720_DPR,		  /* parallel port regs */
	MOS7720_DSR,
	MOS7720_DCR,
	MOS7720_ECR,
	MOS7720_SP1_REG,	  /* device control regs */
	MOS7720_SP2_REG,	  /* serial port 2 (7720 only) */
	MOS7720_PP_REG,
	MOS7720_SP_CONTROL_REG,
पूर्ण;

/*
 * Return the correct value क्रम the Windex field of the setup packet
 * क्रम a control endpoपूर्णांक message.  See the 7715 datasheet.
 */
अटल अंतरभूत __u16 get_reg_index(क्रमागत mos_regs reg)
अणु
	अटल स्थिर __u16 mos7715_index_lookup_table[] = अणु
		0x00,		/* MOS7720_THR */
		0x00,		/* MOS7720_RHR */
		0x01,		/* MOS7720_IER */
		0x02,		/* MOS7720_FCR */
		0x02,		/* MOS7720_ISR */
		0x03,		/* MOS7720_LCR */
		0x04,		/* MOS7720_MCR */
		0x05,		/* MOS7720_LSR */
		0x06,		/* MOS7720_MSR */
		0x07,		/* MOS7720_SPR */
		0x00,		/* MOS7720_DLL */
		0x01,		/* MOS7720_DLM */
		0x00,		/* MOS7720_DPR */
		0x01,		/* MOS7720_DSR */
		0x02,		/* MOS7720_DCR */
		0x0a,		/* MOS7720_ECR */
		0x01,		/* MOS7720_SP1_REG */
		0x02,		/* MOS7720_SP2_REG (7720 only) */
		0x04,		/* MOS7720_PP_REG (7715 only) */
		0x08,		/* MOS7720_SP_CONTROL_REG */
	पूर्ण;
	वापस mos7715_index_lookup_table[reg];
पूर्ण

/*
 * Return the correct value क्रम the upper byte of the Wvalue field of
 * the setup packet क्रम a control endpoपूर्णांक message.
 */
अटल अंतरभूत __u16 get_reg_value(क्रमागत mos_regs reg,
				  अचिन्हित पूर्णांक serial_portnum)
अणु
	अगर (reg >= MOS7720_SP1_REG)	/* control reg */
		वापस 0x0000;

	अन्यथा अगर (reg >= MOS7720_DPR)	/* parallel port reg (7715 only) */
		वापस 0x0100;

	अन्यथा			      /* serial port reg */
		वापस (serial_portnum + 2) << 8;
पूर्ण

/*
 * Write data byte to the specअगरied device रेजिस्टर.  The data is embedded in
 * the value field of the setup packet. serial_portnum is ignored क्रम रेजिस्टरs
 * not specअगरic to a particular serial port.
 */
अटल पूर्णांक ग_लिखो_mos_reg(काष्ठा usb_serial *serial, अचिन्हित पूर्णांक serial_portnum,
			 क्रमागत mos_regs reg, __u8 data)
अणु
	काष्ठा usb_device *usbdev = serial->dev;
	अचिन्हित पूर्णांक pipe = usb_sndctrlpipe(usbdev, 0);
	__u8 request = (__u8)0x0e;
	__u8 requesttype = (__u8)0x40;
	__u16 index = get_reg_index(reg);
	__u16 value = get_reg_value(reg, serial_portnum) + data;
	पूर्णांक status = usb_control_msg(usbdev, pipe, request, requesttype, value,
				     index, शून्य, 0, MOS_WDR_TIMEOUT);
	अगर (status < 0)
		dev_err(&usbdev->dev,
			"mos7720: usb_control_msg() failed: %d\n", status);
	वापस status;
पूर्ण

/*
 * Read data byte from the specअगरied device रेजिस्टर.  The data वापसed by the
 * device is embedded in the value field of the setup packet.  serial_portnum is
 * ignored क्रम रेजिस्टरs that are not specअगरic to a particular serial port.
 */
अटल पूर्णांक पढ़ो_mos_reg(काष्ठा usb_serial *serial, अचिन्हित पूर्णांक serial_portnum,
			क्रमागत mos_regs reg, __u8 *data)
अणु
	काष्ठा usb_device *usbdev = serial->dev;
	अचिन्हित पूर्णांक pipe = usb_rcvctrlpipe(usbdev, 0);
	__u8 request = (__u8)0x0d;
	__u8 requesttype = (__u8)0xc0;
	__u16 index = get_reg_index(reg);
	__u16 value = get_reg_value(reg, serial_portnum);
	u8 *buf;
	पूर्णांक status;

	buf = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!buf) अणु
		*data = 0;
		वापस -ENOMEM;
	पूर्ण

	status = usb_control_msg(usbdev, pipe, request, requesttype, value,
				     index, buf, 1, MOS_WDR_TIMEOUT);
	अगर (status == 1) अणु
		*data = *buf;
	पूर्ण अन्यथा अणु
		dev_err(&usbdev->dev,
			"mos7720: usb_control_msg() failed: %d\n", status);
		अगर (status >= 0)
			status = -EIO;
		*data = 0;
	पूर्ण

	kमुक्त(buf);

	वापस status;
पूर्ण

#अगर_घोषित CONFIG_USB_SERIAL_MOS7715_PARPORT

अटल अंतरभूत पूर्णांक mos7715_change_mode(काष्ठा mos7715_parport *mos_parport,
				      क्रमागत mos7715_pp_modes mode)
अणु
	mos_parport->shaकरोwECR = mode;
	ग_लिखो_mos_reg(mos_parport->serial, dummy, MOS7720_ECR,
		      mos_parport->shaकरोwECR);
	वापस 0;
पूर्ण

अटल व्योम destroy_mos_parport(काष्ठा kref *kref)
अणु
	काष्ठा mos7715_parport *mos_parport =
		container_of(kref, काष्ठा mos7715_parport, ref_count);

	kमुक्त(mos_parport);
पूर्ण

/*
 * This is the common top part of all parallel port callback operations that
 * send synchronous messages to the device.  This implements convoluted locking
 * that aव्योमs two scenarios: (1) a port operation is called after usbserial
 * has called our release function, at which poपूर्णांक काष्ठा mos7715_parport has
 * been destroyed, and (2) the device has been disconnected, but usbserial has
 * not called the release function yet because someone has a serial port खोलो.
 * The shared release_lock prevents the first, and the mutex and disconnected
 * flag मुख्यtained by usbserial covers the second.  We also use the msg_pending
 * flag to ensure that all synchronous usb message calls have completed beक्रमe
 * our release function can वापस.
 */
अटल पूर्णांक parport_prologue(काष्ठा parport *pp)
अणु
	काष्ठा mos7715_parport *mos_parport;

	spin_lock(&release_lock);
	mos_parport = pp->निजी_data;
	अगर (unlikely(mos_parport == शून्य)) अणु
		/* release fn called, port काष्ठा destroyed */
		spin_unlock(&release_lock);
		वापस -1;
	पूर्ण
	mos_parport->msg_pending = true;   /* synch usb call pending */
	reinit_completion(&mos_parport->syncmsg_compl);
	spin_unlock(&release_lock);

	/* ensure ग_लिखोs from restore are submitted beक्रमe new requests */
	अगर (work_pending(&mos_parport->work))
		flush_work(&mos_parport->work);

	mutex_lock(&mos_parport->serial->disc_mutex);
	अगर (mos_parport->serial->disconnected) अणु
		/* device disconnected */
		mutex_unlock(&mos_parport->serial->disc_mutex);
		mos_parport->msg_pending = false;
		complete(&mos_parport->syncmsg_compl);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This is the common bottom part of all parallel port functions that send
 * synchronous messages to the device.
 */
अटल अंतरभूत व्योम parport_epilogue(काष्ठा parport *pp)
अणु
	काष्ठा mos7715_parport *mos_parport = pp->निजी_data;
	mutex_unlock(&mos_parport->serial->disc_mutex);
	mos_parport->msg_pending = false;
	complete(&mos_parport->syncmsg_compl);
पूर्ण

अटल व्योम deferred_restore_ग_लिखोs(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mos7715_parport *mos_parport;

	mos_parport = container_of(work, काष्ठा mos7715_parport, work);

	mutex_lock(&mos_parport->serial->disc_mutex);

	/* अगर device disconnected, game over */
	अगर (mos_parport->serial->disconnected)
		जाओ करोne;

	ग_लिखो_mos_reg(mos_parport->serial, dummy, MOS7720_DCR,
		      mos_parport->shaकरोwDCR);
	ग_लिखो_mos_reg(mos_parport->serial, dummy, MOS7720_ECR,
		      mos_parport->shaकरोwECR);
करोne:
	mutex_unlock(&mos_parport->serial->disc_mutex);
पूर्ण

अटल व्योम parport_mos7715_ग_लिखो_data(काष्ठा parport *pp, अचिन्हित अक्षर d)
अणु
	काष्ठा mos7715_parport *mos_parport = pp->निजी_data;

	अगर (parport_prologue(pp) < 0)
		वापस;
	mos7715_change_mode(mos_parport, SPP);
	ग_लिखो_mos_reg(mos_parport->serial, dummy, MOS7720_DPR, (__u8)d);
	parport_epilogue(pp);
पूर्ण

अटल अचिन्हित अक्षर parport_mos7715_पढ़ो_data(काष्ठा parport *pp)
अणु
	काष्ठा mos7715_parport *mos_parport = pp->निजी_data;
	अचिन्हित अक्षर d;

	अगर (parport_prologue(pp) < 0)
		वापस 0;
	पढ़ो_mos_reg(mos_parport->serial, dummy, MOS7720_DPR, &d);
	parport_epilogue(pp);
	वापस d;
पूर्ण

अटल व्योम parport_mos7715_ग_लिखो_control(काष्ठा parport *pp, अचिन्हित अक्षर d)
अणु
	काष्ठा mos7715_parport *mos_parport = pp->निजी_data;
	__u8 data;

	अगर (parport_prologue(pp) < 0)
		वापस;
	data = ((__u8)d & 0x0f) | (mos_parport->shaकरोwDCR & 0xf0);
	ग_लिखो_mos_reg(mos_parport->serial, dummy, MOS7720_DCR, data);
	mos_parport->shaकरोwDCR = data;
	parport_epilogue(pp);
पूर्ण

अटल अचिन्हित अक्षर parport_mos7715_पढ़ो_control(काष्ठा parport *pp)
अणु
	काष्ठा mos7715_parport *mos_parport;
	__u8 dcr;

	spin_lock(&release_lock);
	mos_parport = pp->निजी_data;
	अगर (unlikely(mos_parport == शून्य)) अणु
		spin_unlock(&release_lock);
		वापस 0;
	पूर्ण
	dcr = mos_parport->shaकरोwDCR & 0x0f;
	spin_unlock(&release_lock);
	वापस dcr;
पूर्ण

अटल अचिन्हित अक्षर parport_mos7715_frob_control(काष्ठा parport *pp,
						  अचिन्हित अक्षर mask,
						  अचिन्हित अक्षर val)
अणु
	काष्ठा mos7715_parport *mos_parport = pp->निजी_data;
	__u8 dcr;

	mask &= 0x0f;
	val &= 0x0f;
	अगर (parport_prologue(pp) < 0)
		वापस 0;
	mos_parport->shaकरोwDCR = (mos_parport->shaकरोwDCR & (~mask)) ^ val;
	ग_लिखो_mos_reg(mos_parport->serial, dummy, MOS7720_DCR,
		      mos_parport->shaकरोwDCR);
	dcr = mos_parport->shaकरोwDCR & 0x0f;
	parport_epilogue(pp);
	वापस dcr;
पूर्ण

अटल अचिन्हित अक्षर parport_mos7715_पढ़ो_status(काष्ठा parport *pp)
अणु
	अचिन्हित अक्षर status;
	काष्ठा mos7715_parport *mos_parport;

	spin_lock(&release_lock);
	mos_parport = pp->निजी_data;
	अगर (unlikely(mos_parport == शून्य)) अणु	/* release called */
		spin_unlock(&release_lock);
		वापस 0;
	पूर्ण
	status = atomic_पढ़ो(&mos_parport->shaकरोwDSR) & 0xf8;
	spin_unlock(&release_lock);
	वापस status;
पूर्ण

अटल व्योम parport_mos7715_enable_irq(काष्ठा parport *pp)
अणु
पूर्ण

अटल व्योम parport_mos7715_disable_irq(काष्ठा parport *pp)
अणु
पूर्ण

अटल व्योम parport_mos7715_data_क्रमward(काष्ठा parport *pp)
अणु
	काष्ठा mos7715_parport *mos_parport = pp->निजी_data;

	अगर (parport_prologue(pp) < 0)
		वापस;
	mos7715_change_mode(mos_parport, PS2);
	mos_parport->shaकरोwDCR &=  ~0x20;
	ग_लिखो_mos_reg(mos_parport->serial, dummy, MOS7720_DCR,
		      mos_parport->shaकरोwDCR);
	parport_epilogue(pp);
पूर्ण

अटल व्योम parport_mos7715_data_reverse(काष्ठा parport *pp)
अणु
	काष्ठा mos7715_parport *mos_parport = pp->निजी_data;

	अगर (parport_prologue(pp) < 0)
		वापस;
	mos7715_change_mode(mos_parport, PS2);
	mos_parport->shaकरोwDCR |= 0x20;
	ग_लिखो_mos_reg(mos_parport->serial, dummy, MOS7720_DCR,
		      mos_parport->shaकरोwDCR);
	parport_epilogue(pp);
पूर्ण

अटल व्योम parport_mos7715_init_state(काष्ठा pardevice *dev,
				       काष्ठा parport_state *s)
अणु
	s->u.pc.ctr = DCR_INIT_VAL;
	s->u.pc.ecr = ECR_INIT_VAL;
पूर्ण

/* N.B. Parport core code requires that this function not block */
अटल व्योम parport_mos7715_save_state(काष्ठा parport *pp,
				       काष्ठा parport_state *s)
अणु
	काष्ठा mos7715_parport *mos_parport;

	spin_lock(&release_lock);
	mos_parport = pp->निजी_data;
	अगर (unlikely(mos_parport == शून्य)) अणु	/* release called */
		spin_unlock(&release_lock);
		वापस;
	पूर्ण
	s->u.pc.ctr = mos_parport->shaकरोwDCR;
	s->u.pc.ecr = mos_parport->shaकरोwECR;
	spin_unlock(&release_lock);
पूर्ण

/* N.B. Parport core code requires that this function not block */
अटल व्योम parport_mos7715_restore_state(काष्ठा parport *pp,
					  काष्ठा parport_state *s)
अणु
	काष्ठा mos7715_parport *mos_parport;

	spin_lock(&release_lock);
	mos_parport = pp->निजी_data;
	अगर (unlikely(mos_parport == शून्य)) अणु	/* release called */
		spin_unlock(&release_lock);
		वापस;
	पूर्ण
	mos_parport->shaकरोwDCR = s->u.pc.ctr;
	mos_parport->shaकरोwECR = s->u.pc.ecr;

	schedule_work(&mos_parport->work);
	spin_unlock(&release_lock);
पूर्ण

अटल माप_प्रकार parport_mos7715_ग_लिखो_compat(काष्ठा parport *pp,
					   स्थिर व्योम *buffer,
					   माप_प्रकार len, पूर्णांक flags)
अणु
	पूर्णांक retval;
	काष्ठा mos7715_parport *mos_parport = pp->निजी_data;
	पूर्णांक actual_len;

	अगर (parport_prologue(pp) < 0)
		वापस 0;
	mos7715_change_mode(mos_parport, PPF);
	retval = usb_bulk_msg(mos_parport->serial->dev,
			      usb_sndbulkpipe(mos_parport->serial->dev, 2),
			      (व्योम *)buffer, len, &actual_len,
			      MOS_WDR_TIMEOUT);
	parport_epilogue(pp);
	अगर (retval) अणु
		dev_err(&mos_parport->serial->dev->dev,
			"mos7720: usb_bulk_msg() failed: %d\n", retval);
		वापस 0;
	पूर्ण
	वापस actual_len;
पूर्ण

अटल काष्ठा parport_operations parport_mos7715_ops = अणु
	.owner =		THIS_MODULE,
	.ग_लिखो_data =		parport_mos7715_ग_लिखो_data,
	.पढ़ो_data =		parport_mos7715_पढ़ो_data,

	.ग_लिखो_control =	parport_mos7715_ग_लिखो_control,
	.पढ़ो_control =		parport_mos7715_पढ़ो_control,
	.frob_control =		parport_mos7715_frob_control,

	.पढ़ो_status =		parport_mos7715_पढ़ो_status,

	.enable_irq =		parport_mos7715_enable_irq,
	.disable_irq =		parport_mos7715_disable_irq,

	.data_क्रमward =		parport_mos7715_data_क्रमward,
	.data_reverse =		parport_mos7715_data_reverse,

	.init_state =		parport_mos7715_init_state,
	.save_state =		parport_mos7715_save_state,
	.restore_state =	parport_mos7715_restore_state,

	.compat_ग_लिखो_data =	parport_mos7715_ग_लिखो_compat,

	.nibble_पढ़ो_data =	parport_ieee1284_पढ़ो_nibble,
	.byte_पढ़ो_data =	parport_ieee1284_पढ़ो_byte,
पूर्ण;

/*
 * Allocate and initialize parallel port control काष्ठा, initialize
 * the parallel port hardware device, and रेजिस्टर with the parport subप्रणाली.
 */
अटल पूर्णांक mos7715_parport_init(काष्ठा usb_serial *serial)
अणु
	काष्ठा mos7715_parport *mos_parport;

	/* allocate and initialize parallel port control काष्ठा */
	mos_parport = kzalloc(माप(काष्ठा mos7715_parport), GFP_KERNEL);
	अगर (!mos_parport)
		वापस -ENOMEM;

	mos_parport->msg_pending = false;
	kref_init(&mos_parport->ref_count);
	usb_set_serial_data(serial, mos_parport); /* hijack निजी poपूर्णांकer */
	mos_parport->serial = serial;
	INIT_WORK(&mos_parport->work, deferred_restore_ग_लिखोs);
	init_completion(&mos_parport->syncmsg_compl);

	/* cycle parallel port reset bit */
	ग_लिखो_mos_reg(mos_parport->serial, dummy, MOS7720_PP_REG, (__u8)0x80);
	ग_लिखो_mos_reg(mos_parport->serial, dummy, MOS7720_PP_REG, (__u8)0x00);

	/* initialize device रेजिस्टरs */
	mos_parport->shaकरोwDCR = DCR_INIT_VAL;
	ग_लिखो_mos_reg(mos_parport->serial, dummy, MOS7720_DCR,
		      mos_parport->shaकरोwDCR);
	mos_parport->shaकरोwECR = ECR_INIT_VAL;
	ग_लिखो_mos_reg(mos_parport->serial, dummy, MOS7720_ECR,
		      mos_parport->shaकरोwECR);

	/* रेजिस्टर with parport core */
	mos_parport->pp = parport_रेजिस्टर_port(0, PARPORT_IRQ_NONE,
						PARPORT_DMA_NONE,
						&parport_mos7715_ops);
	अगर (mos_parport->pp == शून्य) अणु
		dev_err(&serial->पूर्णांकerface->dev,
			"Could not register parport\n");
		kref_put(&mos_parport->ref_count, destroy_mos_parport);
		वापस -EIO;
	पूर्ण
	mos_parport->pp->निजी_data = mos_parport;
	mos_parport->pp->modes = PARPORT_MODE_COMPAT | PARPORT_MODE_PCSPP;
	mos_parport->pp->dev = &serial->पूर्णांकerface->dev;
	parport_announce_port(mos_parport->pp);

	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_USB_SERIAL_MOS7715_PARPORT */

/*
 * mos7720_पूर्णांकerrupt_callback
 *	this is the callback function क्रम when we have received data on the
 *	पूर्णांकerrupt endpoपूर्णांक.
 */
अटल व्योम mos7720_पूर्णांकerrupt_callback(काष्ठा urb *urb)
अणु
	पूर्णांक result;
	पूर्णांक length;
	पूर्णांक status = urb->status;
	काष्ठा device *dev = &urb->dev->dev;
	__u8 *data;
	__u8 sp1;
	__u8 sp2;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(dev, "%s - urb shutting down with status: %d\n", __func__, status);
		वापस;
	शेष:
		dev_dbg(dev, "%s - nonzero urb status received: %d\n", __func__, status);
		जाओ निकास;
	पूर्ण

	length = urb->actual_length;
	data = urb->transfer_buffer;

	/* Moschip get 4 bytes
	 * Byte 1 IIR Port 1 (port.number is 0)
	 * Byte 2 IIR Port 2 (port.number is 1)
	 * Byte 3 --------------
	 * Byte 4 FIFO status क्रम both */

	/* the above description is inverted
	 * 	oneukum 2007-03-14 */

	अगर (unlikely(length != 4)) अणु
		dev_dbg(dev, "Wrong data !!!\n");
		वापस;
	पूर्ण

	sp1 = data[3];
	sp2 = data[2];

	अगर ((sp1 | sp2) & 0x01) अणु
		/* No Interrupt Pending in both the ports */
		dev_dbg(dev, "No Interrupt !!!\n");
	पूर्ण अन्यथा अणु
		चयन (sp1 & 0x0f) अणु
		हाल SERIAL_IIR_RLS:
			dev_dbg(dev, "Serial Port 1: Receiver status error or address bit detected in 9-bit mode\n");
			अवरोध;
		हाल SERIAL_IIR_CTI:
			dev_dbg(dev, "Serial Port 1: Receiver time out\n");
			अवरोध;
		हाल SERIAL_IIR_MS:
			/* dev_dbg(dev, "Serial Port 1: Modem status change\n"); */
			अवरोध;
		पूर्ण

		चयन (sp2 & 0x0f) अणु
		हाल SERIAL_IIR_RLS:
			dev_dbg(dev, "Serial Port 2: Receiver status error or address bit detected in 9-bit mode\n");
			अवरोध;
		हाल SERIAL_IIR_CTI:
			dev_dbg(dev, "Serial Port 2: Receiver time out\n");
			अवरोध;
		हाल SERIAL_IIR_MS:
			/* dev_dbg(dev, "Serial Port 2: Modem status change\n"); */
			अवरोध;
		पूर्ण
	पूर्ण

निकास:
	result = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (result)
		dev_err(dev, "%s - Error %d submitting control urb\n", __func__, result);
पूर्ण

/*
 * mos7715_पूर्णांकerrupt_callback
 *	this is the 7715's callback function क्रम when we have received data on
 *	the पूर्णांकerrupt endpoपूर्णांक.
 */
अटल व्योम mos7715_पूर्णांकerrupt_callback(काष्ठा urb *urb)
अणु
	पूर्णांक result;
	पूर्णांक length;
	पूर्णांक status = urb->status;
	काष्ठा device *dev = &urb->dev->dev;
	__u8 *data;
	__u8 iir;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -ENODEV:
		/* this urb is terminated, clean up */
		dev_dbg(dev, "%s - urb shutting down with status: %d\n", __func__, status);
		वापस;
	शेष:
		dev_dbg(dev, "%s - nonzero urb status received: %d\n", __func__, status);
		जाओ निकास;
	पूर्ण

	length = urb->actual_length;
	data = urb->transfer_buffer;

	/* Structure of data from 7715 device:
	 * Byte 1: IIR serial Port
	 * Byte 2: unused
	 * Byte 2: DSR parallel port
	 * Byte 4: FIFO status क्रम both */

	अगर (unlikely(length != 4)) अणु
		dev_dbg(dev, "Wrong data !!!\n");
		वापस;
	पूर्ण

	iir = data[0];
	अगर (!(iir & 0x01)) अणु	/* serial port पूर्णांकerrupt pending */
		चयन (iir & 0x0f) अणु
		हाल SERIAL_IIR_RLS:
			dev_dbg(dev, "Serial Port: Receiver status error or address bit detected in 9-bit mode\n");
			अवरोध;
		हाल SERIAL_IIR_CTI:
			dev_dbg(dev, "Serial Port: Receiver time out\n");
			अवरोध;
		हाल SERIAL_IIR_MS:
			/* dev_dbg(dev, "Serial Port: Modem status change\n"); */
			अवरोध;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_USB_SERIAL_MOS7715_PARPORT
	अणु       /* update local copy of DSR reg */
		काष्ठा usb_serial_port *port = urb->context;
		काष्ठा mos7715_parport *mos_parport = port->serial->निजी;
		अगर (unlikely(mos_parport == शून्य))
			वापस;
		atomic_set(&mos_parport->shaकरोwDSR, data[2]);
	पूर्ण
#पूर्ण_अगर

निकास:
	result = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (result)
		dev_err(dev, "%s - Error %d submitting control urb\n", __func__, result);
पूर्ण

/*
 * mos7720_bulk_in_callback
 *	this is the callback function क्रम when we have received data on the
 *	bulk in endpoपूर्णांक.
 */
अटल व्योम mos7720_bulk_in_callback(काष्ठा urb *urb)
अणु
	पूर्णांक retval;
	अचिन्हित अक्षर *data ;
	काष्ठा usb_serial_port *port;
	पूर्णांक status = urb->status;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "nonzero read bulk status received: %d\n", status);
		वापस;
	पूर्ण

	port = urb->context;

	dev_dbg(&port->dev, "Entering...%s\n", __func__);

	data = urb->transfer_buffer;

	अगर (urb->actual_length) अणु
		tty_insert_flip_string(&port->port, data, urb->actual_length);
		tty_flip_buffer_push(&port->port);
	पूर्ण

	अगर (port->पढ़ो_urb->status != -EINPROGRESS) अणु
		retval = usb_submit_urb(port->पढ़ो_urb, GFP_ATOMIC);
		अगर (retval)
			dev_dbg(&port->dev, "usb_submit_urb(read bulk) failed, retval = %d\n", retval);
	पूर्ण
पूर्ण

/*
 * mos7720_bulk_out_data_callback
 *	this is the callback function क्रम when we have finished sending serial
 *	data on the bulk out endpoपूर्णांक.
 */
अटल व्योम mos7720_bulk_out_data_callback(काष्ठा urb *urb)
अणु
	काष्ठा moschip_port *mos7720_port;
	पूर्णांक status = urb->status;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "nonzero write bulk status received:%d\n", status);
		वापस;
	पूर्ण

	mos7720_port = urb->context;
	अगर (!mos7720_port) अणु
		dev_dbg(&urb->dev->dev, "NULL mos7720_port pointer\n");
		वापस ;
	पूर्ण

	अगर (mos7720_port->खोलो)
		tty_port_tty_wakeup(&mos7720_port->port->port);
पूर्ण

अटल पूर्णांक mos77xx_calc_num_ports(काष्ठा usb_serial *serial,
					काष्ठा usb_serial_endpoपूर्णांकs *epds)
अणु
	u16 product = le16_to_cpu(serial->dev->descriptor.idProduct);

	अगर (product == MOSCHIP_DEVICE_ID_7715) अणु
		/*
		 * The 7715 uses the first bulk in/out endpoपूर्णांक pair क्रम the
		 * parallel port, and the second क्रम the serial port. We swap
		 * the endpoपूर्णांक descriptors here so that the the first and
		 * only रेजिस्टरed port काष्ठाure uses the serial-port
		 * endpoपूर्णांकs.
		 */
		swap(epds->bulk_in[0], epds->bulk_in[1]);
		swap(epds->bulk_out[0], epds->bulk_out[1]);

		वापस 1;
	पूर्ण

	वापस 2;
पूर्ण

अटल पूर्णांक mos7720_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial;
	काष्ठा urb *urb;
	काष्ठा moschip_port *mos7720_port;
	पूर्णांक response;
	पूर्णांक port_number;
	__u8 data;
	पूर्णांक allocated_urbs = 0;
	पूर्णांक j;

	serial = port->serial;

	mos7720_port = usb_get_serial_port_data(port);
	अगर (mos7720_port == शून्य)
		वापस -ENODEV;

	usb_clear_halt(serial->dev, port->ग_लिखो_urb->pipe);
	usb_clear_halt(serial->dev, port->पढ़ो_urb->pipe);

	/* Initialising the ग_लिखो urb pool */
	क्रम (j = 0; j < NUM_URBS; ++j) अणु
		urb = usb_alloc_urb(0, GFP_KERNEL);
		mos7720_port->ग_लिखो_urb_pool[j] = urb;
		अगर (!urb)
			जारी;

		urb->transfer_buffer = kदो_स्मृति(URB_TRANSFER_BUFFER_SIZE,
					       GFP_KERNEL);
		अगर (!urb->transfer_buffer) अणु
			usb_मुक्त_urb(mos7720_port->ग_लिखो_urb_pool[j]);
			mos7720_port->ग_लिखो_urb_pool[j] = शून्य;
			जारी;
		पूर्ण
		allocated_urbs++;
	पूर्ण

	अगर (!allocated_urbs)
		वापस -ENOMEM;

	 /* Initialize MCS7720 -- Write Init values to corresponding Registers
	  *
	  * Register Index
	  * 0 : MOS7720_THR/MOS7720_RHR
	  * 1 : MOS7720_IER
	  * 2 : MOS7720_FCR
	  * 3 : MOS7720_LCR
	  * 4 : MOS7720_MCR
	  * 5 : MOS7720_LSR
	  * 6 : MOS7720_MSR
	  * 7 : MOS7720_SPR
	  *
	  * 0x08 : SP1/2 Control Reg
	  */
	port_number = port->port_number;
	पढ़ो_mos_reg(serial, port_number, MOS7720_LSR, &data);

	dev_dbg(&port->dev, "SS::%p LSR:%x\n", mos7720_port, data);

	ग_लिखो_mos_reg(serial, dummy, MOS7720_SP1_REG, 0x02);
	ग_लिखो_mos_reg(serial, dummy, MOS7720_SP2_REG, 0x02);

	ग_लिखो_mos_reg(serial, port_number, MOS7720_IER, 0x00);
	ग_लिखो_mos_reg(serial, port_number, MOS7720_FCR, 0x00);

	ग_लिखो_mos_reg(serial, port_number, MOS7720_FCR, 0xcf);
	mos7720_port->shaकरोwLCR = 0x03;
	ग_लिखो_mos_reg(serial, port_number, MOS7720_LCR,
		      mos7720_port->shaकरोwLCR);
	mos7720_port->shaकरोwMCR = 0x0b;
	ग_लिखो_mos_reg(serial, port_number, MOS7720_MCR,
		      mos7720_port->shaकरोwMCR);

	ग_लिखो_mos_reg(serial, port_number, MOS7720_SP_CONTROL_REG, 0x00);
	पढ़ो_mos_reg(serial, dummy, MOS7720_SP_CONTROL_REG, &data);
	data = data | (port->port_number + 1);
	ग_लिखो_mos_reg(serial, dummy, MOS7720_SP_CONTROL_REG, data);
	mos7720_port->shaकरोwLCR = 0x83;
	ग_लिखो_mos_reg(serial, port_number, MOS7720_LCR,
		      mos7720_port->shaकरोwLCR);
	ग_लिखो_mos_reg(serial, port_number, MOS7720_THR, 0x0c);
	ग_लिखो_mos_reg(serial, port_number, MOS7720_IER, 0x00);
	mos7720_port->shaकरोwLCR = 0x03;
	ग_लिखो_mos_reg(serial, port_number, MOS7720_LCR,
		      mos7720_port->shaकरोwLCR);
	ग_लिखो_mos_reg(serial, port_number, MOS7720_IER, 0x0c);

	response = usb_submit_urb(port->पढ़ो_urb, GFP_KERNEL);
	अगर (response)
		dev_err(&port->dev, "%s - Error %d submitting read urb\n",
							__func__, response);

	/* initialize our port settings */
	mos7720_port->shaकरोwMCR = UART_MCR_OUT2; /* Must set to enable पूर्णांकs! */

	/* send a खोलो port command */
	mos7720_port->खोलो = 1;

	वापस 0;
पूर्ण

/*
 * mos7720_अक्षरs_in_buffer
 *	this function is called by the tty driver when it wants to know how many
 *	bytes of data we currently have outstanding in the port (data that has
 *	been written, but hasn't made it out the port yet)
 *	If successful, we वापस the number of bytes left to be written in the
 *	प्रणाली,
 *	Otherwise we वापस a negative error number.
 */
अटल पूर्णांक mos7720_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	पूर्णांक i;
	पूर्णांक अक्षरs = 0;
	काष्ठा moschip_port *mos7720_port;

	mos7720_port = usb_get_serial_port_data(port);
	अगर (mos7720_port == शून्य)
		वापस 0;

	क्रम (i = 0; i < NUM_URBS; ++i) अणु
		अगर (mos7720_port->ग_लिखो_urb_pool[i] &&
		    mos7720_port->ग_लिखो_urb_pool[i]->status == -EINPROGRESS)
			अक्षरs += URB_TRANSFER_BUFFER_SIZE;
	पूर्ण
	dev_dbg(&port->dev, "%s - returns %d\n", __func__, अक्षरs);
	वापस अक्षरs;
पूर्ण

अटल व्योम mos7720_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा usb_serial *serial;
	काष्ठा moschip_port *mos7720_port;
	पूर्णांक j;

	serial = port->serial;

	mos7720_port = usb_get_serial_port_data(port);
	अगर (mos7720_port == शून्य)
		वापस;

	क्रम (j = 0; j < NUM_URBS; ++j)
		usb_समाप्त_urb(mos7720_port->ग_लिखो_urb_pool[j]);

	/* Freeing Write URBs */
	क्रम (j = 0; j < NUM_URBS; ++j) अणु
		अगर (mos7720_port->ग_लिखो_urb_pool[j]) अणु
			kमुक्त(mos7720_port->ग_लिखो_urb_pool[j]->transfer_buffer);
			usb_मुक्त_urb(mos7720_port->ग_लिखो_urb_pool[j]);
		पूर्ण
	पूर्ण

	/* While closing port, shutकरोwn all bulk पढ़ो, ग_लिखो  *
	 * and पूर्णांकerrupt पढ़ो अगर they exists, otherwise nop   */
	usb_समाप्त_urb(port->ग_लिखो_urb);
	usb_समाप्त_urb(port->पढ़ो_urb);

	ग_लिखो_mos_reg(serial, port->port_number, MOS7720_MCR, 0x00);
	ग_लिखो_mos_reg(serial, port->port_number, MOS7720_IER, 0x00);

	mos7720_port->खोलो = 0;
पूर्ण

अटल व्योम mos7720_अवरोध(काष्ठा tty_काष्ठा *tty, पूर्णांक अवरोध_state)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	अचिन्हित अक्षर data;
	काष्ठा usb_serial *serial;
	काष्ठा moschip_port *mos7720_port;

	serial = port->serial;

	mos7720_port = usb_get_serial_port_data(port);
	अगर (mos7720_port == शून्य)
		वापस;

	अगर (अवरोध_state == -1)
		data = mos7720_port->shaकरोwLCR | UART_LCR_SBC;
	अन्यथा
		data = mos7720_port->shaकरोwLCR & ~UART_LCR_SBC;

	mos7720_port->shaकरोwLCR  = data;
	ग_लिखो_mos_reg(serial, port->port_number, MOS7720_LCR,
		      mos7720_port->shaकरोwLCR);
पूर्ण

/*
 * mos7720_ग_लिखो_room
 *	this function is called by the tty driver when it wants to know how many
 *	bytes of data we can accept क्रम a specअगरic port.
 *	If successful, we वापस the amount of room that we have क्रम this port
 *	Otherwise we वापस a negative error number.
 */
अटल पूर्णांक mos7720_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा moschip_port *mos7720_port;
	पूर्णांक room = 0;
	पूर्णांक i;

	mos7720_port = usb_get_serial_port_data(port);
	अगर (mos7720_port == शून्य)
		वापस 0;

	/* FIXME: Locking */
	क्रम (i = 0; i < NUM_URBS; ++i) अणु
		अगर (mos7720_port->ग_लिखो_urb_pool[i] &&
		    mos7720_port->ग_लिखो_urb_pool[i]->status != -EINPROGRESS)
			room += URB_TRANSFER_BUFFER_SIZE;
	पूर्ण

	dev_dbg(&port->dev, "%s - returns %d\n", __func__, room);
	वापस room;
पूर्ण

अटल पूर्णांक mos7720_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
				 स्थिर अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	पूर्णांक status;
	पूर्णांक i;
	पूर्णांक bytes_sent = 0;
	पूर्णांक transfer_size;

	काष्ठा moschip_port *mos7720_port;
	काष्ठा usb_serial *serial;
	काष्ठा urb    *urb;
	स्थिर अचिन्हित अक्षर *current_position = data;

	serial = port->serial;

	mos7720_port = usb_get_serial_port_data(port);
	अगर (mos7720_port == शून्य)
		वापस -ENODEV;

	/* try to find a मुक्त urb in the list */
	urb = शून्य;

	क्रम (i = 0; i < NUM_URBS; ++i) अणु
		अगर (mos7720_port->ग_लिखो_urb_pool[i] &&
		    mos7720_port->ग_लिखो_urb_pool[i]->status != -EINPROGRESS) अणु
			urb = mos7720_port->ग_लिखो_urb_pool[i];
			dev_dbg(&port->dev, "URB:%d\n", i);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (urb == शून्य) अणु
		dev_dbg(&port->dev, "%s - no more free urbs\n", __func__);
		जाओ निकास;
	पूर्ण

	अगर (urb->transfer_buffer == शून्य) अणु
		urb->transfer_buffer = kदो_स्मृति(URB_TRANSFER_BUFFER_SIZE,
					       GFP_ATOMIC);
		अगर (!urb->transfer_buffer) अणु
			bytes_sent = -ENOMEM;
			जाओ निकास;
		पूर्ण
	पूर्ण
	transfer_size = min(count, URB_TRANSFER_BUFFER_SIZE);

	स_नकल(urb->transfer_buffer, current_position, transfer_size);
	usb_serial_debug_data(&port->dev, __func__, transfer_size,
			      urb->transfer_buffer);

	/* fill urb with data and submit  */
	usb_fill_bulk_urb(urb, serial->dev,
			  usb_sndbulkpipe(serial->dev,
					port->bulk_out_endpoपूर्णांकAddress),
			  urb->transfer_buffer, transfer_size,
			  mos7720_bulk_out_data_callback, mos7720_port);

	/* send it करोwn the pipe */
	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status) अणु
		dev_err_console(port, "%s - usb_submit_urb(write bulk) failed "
			"with status = %d\n", __func__, status);
		bytes_sent = status;
		जाओ निकास;
	पूर्ण
	bytes_sent = transfer_size;

निकास:
	वापस bytes_sent;
पूर्ण

अटल व्योम mos7720_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा moschip_port *mos7720_port;
	पूर्णांक status;

	mos7720_port = usb_get_serial_port_data(port);

	अगर (mos7720_port == शून्य)
		वापस;

	अगर (!mos7720_port->खोलो) अणु
		dev_dbg(&port->dev, "%s - port not opened\n", __func__);
		वापस;
	पूर्ण

	/* अगर we are implementing XON/XOFF, send the stop अक्षरacter */
	अगर (I_IXOFF(tty)) अणु
		अचिन्हित अक्षर stop_अक्षर = STOP_CHAR(tty);
		status = mos7720_ग_लिखो(tty, port, &stop_अक्षर, 1);
		अगर (status <= 0)
			वापस;
	पूर्ण

	/* अगर we are implementing RTS/CTS, toggle that line */
	अगर (C_CRTSCTS(tty)) अणु
		mos7720_port->shaकरोwMCR &= ~UART_MCR_RTS;
		ग_लिखो_mos_reg(port->serial, port->port_number, MOS7720_MCR,
			      mos7720_port->shaकरोwMCR);
	पूर्ण
पूर्ण

अटल व्योम mos7720_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा moschip_port *mos7720_port = usb_get_serial_port_data(port);
	पूर्णांक status;

	अगर (mos7720_port == शून्य)
		वापस;

	अगर (!mos7720_port->खोलो) अणु
		dev_dbg(&port->dev, "%s - port not opened\n", __func__);
		वापस;
	पूर्ण

	/* अगर we are implementing XON/XOFF, send the start अक्षरacter */
	अगर (I_IXOFF(tty)) अणु
		अचिन्हित अक्षर start_अक्षर = START_CHAR(tty);
		status = mos7720_ग_लिखो(tty, port, &start_अक्षर, 1);
		अगर (status <= 0)
			वापस;
	पूर्ण

	/* अगर we are implementing RTS/CTS, toggle that line */
	अगर (C_CRTSCTS(tty)) अणु
		mos7720_port->shaकरोwMCR |= UART_MCR_RTS;
		ग_लिखो_mos_reg(port->serial, port->port_number, MOS7720_MCR,
			      mos7720_port->shaकरोwMCR);
	पूर्ण
पूर्ण

/* FIXME: this function करोes not work */
अटल पूर्णांक set_higher_rates(काष्ठा moschip_port *mos7720_port,
			    अचिन्हित पूर्णांक baud)
अणु
	काष्ठा usb_serial_port *port;
	काष्ठा usb_serial *serial;
	पूर्णांक port_number;
	क्रमागत mos_regs sp_reg;
	अगर (mos7720_port == शून्य)
		वापस -EINVAL;

	port = mos7720_port->port;
	serial = port->serial;

	 /***********************************************
	 *      Init Sequence क्रम higher rates
	 ***********************************************/
	dev_dbg(&port->dev, "Sending Setting Commands ..........\n");
	port_number = port->port_number;

	ग_लिखो_mos_reg(serial, port_number, MOS7720_IER, 0x00);
	ग_लिखो_mos_reg(serial, port_number, MOS7720_FCR, 0x00);
	ग_लिखो_mos_reg(serial, port_number, MOS7720_FCR, 0xcf);
	mos7720_port->shaकरोwMCR = 0x0b;
	ग_लिखो_mos_reg(serial, port_number, MOS7720_MCR,
		      mos7720_port->shaकरोwMCR);
	ग_लिखो_mos_reg(serial, dummy, MOS7720_SP_CONTROL_REG, 0x00);

	/***********************************************
	 *              Set क्रम higher rates           *
	 ***********************************************/
	/* writing baud rate verbatum पूर्णांकo uart घड़ी field clearly not right */
	अगर (port_number == 0)
		sp_reg = MOS7720_SP1_REG;
	अन्यथा
		sp_reg = MOS7720_SP2_REG;
	ग_लिखो_mos_reg(serial, dummy, sp_reg, baud * 0x10);
	ग_लिखो_mos_reg(serial, dummy, MOS7720_SP_CONTROL_REG, 0x03);
	mos7720_port->shaकरोwMCR = 0x2b;
	ग_लिखो_mos_reg(serial, port_number, MOS7720_MCR,
		      mos7720_port->shaकरोwMCR);

	/***********************************************
	 *              Set DLL/DLM
	 ***********************************************/
	mos7720_port->shaकरोwLCR = mos7720_port->shaकरोwLCR | UART_LCR_DLAB;
	ग_लिखो_mos_reg(serial, port_number, MOS7720_LCR,
		      mos7720_port->shaकरोwLCR);
	ग_लिखो_mos_reg(serial, port_number, MOS7720_DLL, 0x01);
	ग_लिखो_mos_reg(serial, port_number, MOS7720_DLM, 0x00);
	mos7720_port->shaकरोwLCR = mos7720_port->shaकरोwLCR & ~UART_LCR_DLAB;
	ग_लिखो_mos_reg(serial, port_number, MOS7720_LCR,
		      mos7720_port->shaकरोwLCR);

	वापस 0;
पूर्ण

/* baud rate inक्रमmation */
काष्ठा भागisor_table_entry अणु
	__u32  baudrate;
	__u16  भागisor;
पूर्ण;

/* Define table of भागisors क्रम moschip 7720 hardware	   *
 * These assume a 3.6864MHz crystal, the standard /16, and *
 * MCR.7 = 0.						   */
अटल स्थिर काष्ठा भागisor_table_entry भागisor_table[] = अणु
	अणु   50,		2304पूर्ण,
	अणु   110,	1047पूर्ण,	/* 2094.545455 => 230450   => .0217 % over */
	अणु   134,	857पूर्ण,	/* 1713.011152 => 230398.5 => .00065% under */
	अणु   150,	768पूर्ण,
	अणु   300,	384पूर्ण,
	अणु   600,	192पूर्ण,
	अणु   1200,	96पूर्ण,
	अणु   1800,	64पूर्ण,
	अणु   2400,	48पूर्ण,
	अणु   4800,	24पूर्ण,
	अणु   7200,	16पूर्ण,
	अणु   9600,	12पूर्ण,
	अणु   19200,	6पूर्ण,
	अणु   38400,	3पूर्ण,
	अणु   57600,	2पूर्ण,
	अणु   115200,	1पूर्ण,
पूर्ण;

/*****************************************************************************
 * calc_baud_rate_भागisor
 *	this function calculates the proper baud rate भागisor क्रम the specअगरied
 *	baud rate.
 *****************************************************************************/
अटल पूर्णांक calc_baud_rate_भागisor(काष्ठा usb_serial_port *port, पूर्णांक baudrate, पूर्णांक *भागisor)
अणु
	पूर्णांक i;
	__u16 custom;
	__u16 round1;
	__u16 round;


	dev_dbg(&port->dev, "%s - %d\n", __func__, baudrate);

	क्रम (i = 0; i < ARRAY_SIZE(भागisor_table); i++) अणु
		अगर (भागisor_table[i].baudrate == baudrate) अणु
			*भागisor = भागisor_table[i].भागisor;
			वापस 0;
		पूर्ण
	पूर्ण

	/* After trying क्रम all the standard baud rates    *
	 * Try calculating the भागisor क्रम this baud rate  */
	अगर (baudrate > 75 &&  baudrate < 230400) अणु
		/* get the भागisor */
		custom = (__u16)(230400L  / baudrate);

		/* Check क्रम round off */
		round1 = (__u16)(2304000L / baudrate);
		round = (__u16)(round1 - (custom * 10));
		अगर (round > 4)
			custom++;
		*भागisor = custom;

		dev_dbg(&port->dev, "Baud %d = %d\n", baudrate, custom);
		वापस 0;
	पूर्ण

	dev_dbg(&port->dev, "Baud calculation Failed...\n");
	वापस -EINVAL;
पूर्ण

/*
 * send_cmd_ग_लिखो_baud_rate
 *	this function sends the proper command to change the baud rate of the
 *	specअगरied port.
 */
अटल पूर्णांक send_cmd_ग_लिखो_baud_rate(काष्ठा moschip_port *mos7720_port,
				    पूर्णांक baudrate)
अणु
	काष्ठा usb_serial_port *port;
	काष्ठा usb_serial *serial;
	पूर्णांक भागisor;
	पूर्णांक status;
	अचिन्हित अक्षर number;

	अगर (mos7720_port == शून्य)
		वापस -1;

	port = mos7720_port->port;
	serial = port->serial;

	number = port->port_number;
	dev_dbg(&port->dev, "%s - baud = %d\n", __func__, baudrate);

	/* Calculate the Divisor */
	status = calc_baud_rate_भागisor(port, baudrate, &भागisor);
	अगर (status) अणु
		dev_err(&port->dev, "%s - bad baud rate\n", __func__);
		वापस status;
	पूर्ण

	/* Enable access to भागisor latch */
	mos7720_port->shaकरोwLCR = mos7720_port->shaकरोwLCR | UART_LCR_DLAB;
	ग_लिखो_mos_reg(serial, number, MOS7720_LCR, mos7720_port->shaकरोwLCR);

	/* Write the भागisor */
	ग_लिखो_mos_reg(serial, number, MOS7720_DLL, (__u8)(भागisor & 0xff));
	ग_लिखो_mos_reg(serial, number, MOS7720_DLM,
		      (__u8)((भागisor & 0xff00) >> 8));

	/* Disable access to भागisor latch */
	mos7720_port->shaकरोwLCR = mos7720_port->shaकरोwLCR & ~UART_LCR_DLAB;
	ग_लिखो_mos_reg(serial, number, MOS7720_LCR, mos7720_port->shaकरोwLCR);

	वापस status;
पूर्ण

/*
 * change_port_settings
 *	This routine is called to set the UART on the device to match
 *      the specअगरied new settings.
 */
अटल व्योम change_port_settings(काष्ठा tty_काष्ठा *tty,
				 काष्ठा moschip_port *mos7720_port,
				 काष्ठा ktermios *old_termios)
अणु
	काष्ठा usb_serial_port *port;
	काष्ठा usb_serial *serial;
	पूर्णांक baud;
	अचिन्हित cflag;
	__u8 lData;
	__u8 lParity;
	__u8 lStop;
	पूर्णांक status;
	पूर्णांक port_number;

	अगर (mos7720_port == शून्य)
		वापस ;

	port = mos7720_port->port;
	serial = port->serial;
	port_number = port->port_number;

	अगर (!mos7720_port->खोलो) अणु
		dev_dbg(&port->dev, "%s - port not opened\n", __func__);
		वापस;
	पूर्ण

	lData = UART_LCR_WLEN8;
	lStop = 0x00;	/* 1 stop bit */
	lParity = 0x00;	/* No parity */

	cflag = tty->termios.c_cflag;

	/* Change the number of bits */
	चयन (cflag & CSIZE) अणु
	हाल CS5:
		lData = UART_LCR_WLEN5;
		अवरोध;

	हाल CS6:
		lData = UART_LCR_WLEN6;
		अवरोध;

	हाल CS7:
		lData = UART_LCR_WLEN7;
		अवरोध;
	शेष:
	हाल CS8:
		lData = UART_LCR_WLEN8;
		अवरोध;
	पूर्ण

	/* Change the Parity bit */
	अगर (cflag & PARENB) अणु
		अगर (cflag & PARODD) अणु
			lParity = UART_LCR_PARITY;
			dev_dbg(&port->dev, "%s - parity = odd\n", __func__);
		पूर्ण अन्यथा अणु
			lParity = (UART_LCR_EPAR | UART_LCR_PARITY);
			dev_dbg(&port->dev, "%s - parity = even\n", __func__);
		पूर्ण

	पूर्ण अन्यथा अणु
		dev_dbg(&port->dev, "%s - parity = none\n", __func__);
	पूर्ण

	अगर (cflag & CMSPAR)
		lParity = lParity | 0x20;

	/* Change the Stop bit */
	अगर (cflag & CSTOPB) अणु
		lStop = UART_LCR_STOP;
		dev_dbg(&port->dev, "%s - stop bits = 2\n", __func__);
	पूर्ण अन्यथा अणु
		lStop = 0x00;
		dev_dbg(&port->dev, "%s - stop bits = 1\n", __func__);
	पूर्ण

#घोषणा LCR_BITS_MASK		0x03	/* Mask क्रम bits/अक्षर field */
#घोषणा LCR_STOP_MASK		0x04	/* Mask क्रम stop bits field */
#घोषणा LCR_PAR_MASK		0x38	/* Mask क्रम parity field */

	/* Update the LCR with the correct value */
	mos7720_port->shaकरोwLCR &=
		~(LCR_BITS_MASK | LCR_STOP_MASK | LCR_PAR_MASK);
	mos7720_port->shaकरोwLCR |= (lData | lParity | lStop);


	/* Disable Interrupts */
	ग_लिखो_mos_reg(serial, port_number, MOS7720_IER, 0x00);
	ग_लिखो_mos_reg(serial, port_number, MOS7720_FCR, 0x00);
	ग_लिखो_mos_reg(serial, port_number, MOS7720_FCR, 0xcf);

	/* Send the updated LCR value to the mos7720 */
	ग_लिखो_mos_reg(serial, port_number, MOS7720_LCR,
		      mos7720_port->shaकरोwLCR);
	mos7720_port->shaकरोwMCR = 0x0b;
	ग_लिखो_mos_reg(serial, port_number, MOS7720_MCR,
		      mos7720_port->shaकरोwMCR);

	/* set up the MCR रेजिस्टर and send it to the mos7720 */
	mos7720_port->shaकरोwMCR = UART_MCR_OUT2;
	अगर (cflag & CBAUD)
		mos7720_port->shaकरोwMCR |= (UART_MCR_DTR | UART_MCR_RTS);

	अगर (cflag & CRTSCTS) अणु
		mos7720_port->shaकरोwMCR |= (UART_MCR_XOन_अंकY);
		/* To set hardware flow control to the specअगरied *
		 * serial port, in SP1/2_CONTROL_REG             */
		अगर (port_number)
			ग_लिखो_mos_reg(serial, dummy, MOS7720_SP_CONTROL_REG,
				      0x01);
		अन्यथा
			ग_लिखो_mos_reg(serial, dummy, MOS7720_SP_CONTROL_REG,
				      0x02);

	पूर्ण अन्यथा
		mos7720_port->shaकरोwMCR &= ~(UART_MCR_XOन_अंकY);

	ग_लिखो_mos_reg(serial, port_number, MOS7720_MCR,
		      mos7720_port->shaकरोwMCR);

	/* Determine भागisor based on baud rate */
	baud = tty_get_baud_rate(tty);
	अगर (!baud) अणु
		/* pick a शेष, any शेष... */
		dev_dbg(&port->dev, "Picked default baud...\n");
		baud = 9600;
	पूर्ण

	अगर (baud >= 230400) अणु
		set_higher_rates(mos7720_port, baud);
		/* Enable Interrupts */
		ग_लिखो_mos_reg(serial, port_number, MOS7720_IER, 0x0c);
		वापस;
	पूर्ण

	dev_dbg(&port->dev, "%s - baud rate = %d\n", __func__, baud);
	status = send_cmd_ग_लिखो_baud_rate(mos7720_port, baud);
	/* FIXME: needs to ग_लिखो actual resulting baud back not just
	   blindly करो so */
	अगर (cflag & CBAUD)
		tty_encode_baud_rate(tty, baud, baud);
	/* Enable Interrupts */
	ग_लिखो_mos_reg(serial, port_number, MOS7720_IER, 0x0c);

	अगर (port->पढ़ो_urb->status != -EINPROGRESS) अणु
		status = usb_submit_urb(port->पढ़ो_urb, GFP_KERNEL);
		अगर (status)
			dev_dbg(&port->dev, "usb_submit_urb(read bulk) failed, status = %d\n", status);
	पूर्ण
पूर्ण

/*
 * mos7720_set_termios
 *	this function is called by the tty driver when it wants to change the
 *	termios काष्ठाure.
 */
अटल व्योम mos7720_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा usb_serial_port *port, काष्ठा ktermios *old_termios)
अणु
	पूर्णांक status;
	काष्ठा moschip_port *mos7720_port;

	mos7720_port = usb_get_serial_port_data(port);

	अगर (mos7720_port == शून्य)
		वापस;

	अगर (!mos7720_port->खोलो) अणु
		dev_dbg(&port->dev, "%s - port not opened\n", __func__);
		वापस;
	पूर्ण

	/* change the port settings to the new ones specअगरied */
	change_port_settings(tty, mos7720_port, old_termios);

	अगर (port->पढ़ो_urb->status != -EINPROGRESS) अणु
		status = usb_submit_urb(port->पढ़ो_urb, GFP_KERNEL);
		अगर (status)
			dev_dbg(&port->dev, "usb_submit_urb(read bulk) failed, status = %d\n", status);
	पूर्ण
पूर्ण

/*
 * get_lsr_info - get line status रेजिस्टर info
 *
 * Purpose: Let user call ioctl() to get info when the UART physically
 * 	    is emptied.  On bus types like RS485, the transmitter must
 * 	    release the bus after transmitting. This must be करोne when
 * 	    the transmit shअगरt रेजिस्टर is empty, not be करोne when the
 * 	    transmit holding रेजिस्टर is empty.  This functionality
 * 	    allows an RS485 driver to be written in user space.
 */
अटल पूर्णांक get_lsr_info(काष्ठा tty_काष्ठा *tty,
		काष्ठा moschip_port *mos7720_port, अचिन्हित पूर्णांक __user *value)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	अचिन्हित पूर्णांक result = 0;
	अचिन्हित अक्षर data = 0;
	पूर्णांक port_number = port->port_number;
	पूर्णांक count;

	count = mos7720_अक्षरs_in_buffer(tty);
	अगर (count == 0) अणु
		पढ़ो_mos_reg(port->serial, port_number, MOS7720_LSR, &data);
		अगर ((data & (UART_LSR_TEMT | UART_LSR_THRE))
					== (UART_LSR_TEMT | UART_LSR_THRE)) अणु
			dev_dbg(&port->dev, "%s -- Empty\n", __func__);
			result = TIOCSER_TEMT;
		पूर्ण
	पूर्ण
	अगर (copy_to_user(value, &result, माप(पूर्णांक)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक mos7720_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा moschip_port *mos7720_port = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक result = 0;
	अचिन्हित पूर्णांक mcr ;
	अचिन्हित पूर्णांक msr ;

	mcr = mos7720_port->shaकरोwMCR;
	msr = mos7720_port->shaकरोwMSR;

	result = ((mcr & UART_MCR_DTR)  ? TIOCM_DTR : 0)   /* 0x002 */
	  | ((mcr & UART_MCR_RTS)   ? TIOCM_RTS : 0)   /* 0x004 */
	  | ((msr & UART_MSR_CTS)   ? TIOCM_CTS : 0)   /* 0x020 */
	  | ((msr & UART_MSR_DCD)   ? TIOCM_CAR : 0)   /* 0x040 */
	  | ((msr & UART_MSR_RI)    ? TIOCM_RI :  0)   /* 0x080 */
	  | ((msr & UART_MSR_DSR)   ? TIOCM_DSR : 0);  /* 0x100 */

	वापस result;
पूर्ण

अटल पूर्णांक mos7720_tiocmset(काष्ठा tty_काष्ठा *tty,
			    अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा moschip_port *mos7720_port = usb_get_serial_port_data(port);
	अचिन्हित पूर्णांक mcr ;

	mcr = mos7720_port->shaकरोwMCR;

	अगर (set & TIOCM_RTS)
		mcr |= UART_MCR_RTS;
	अगर (set & TIOCM_DTR)
		mcr |= UART_MCR_DTR;
	अगर (set & TIOCM_LOOP)
		mcr |= UART_MCR_LOOP;

	अगर (clear & TIOCM_RTS)
		mcr &= ~UART_MCR_RTS;
	अगर (clear & TIOCM_DTR)
		mcr &= ~UART_MCR_DTR;
	अगर (clear & TIOCM_LOOP)
		mcr &= ~UART_MCR_LOOP;

	mos7720_port->shaकरोwMCR = mcr;
	ग_लिखो_mos_reg(port->serial, port->port_number, MOS7720_MCR,
		      mos7720_port->shaकरोwMCR);

	वापस 0;
पूर्ण

अटल पूर्णांक mos7720_ioctl(काष्ठा tty_काष्ठा *tty,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा moschip_port *mos7720_port;

	mos7720_port = usb_get_serial_port_data(port);
	अगर (mos7720_port == शून्य)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल TIOCSERGETLSR:
		dev_dbg(&port->dev, "%s TIOCSERGETLSR\n", __func__);
		वापस get_lsr_info(tty, mos7720_port,
					(अचिन्हित पूर्णांक __user *)arg);
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

अटल पूर्णांक mos7720_startup(काष्ठा usb_serial *serial)
अणु
	काष्ठा usb_device *dev;
	अक्षर data;
	u16 product;
	पूर्णांक ret_val;

	product = le16_to_cpu(serial->dev->descriptor.idProduct);
	dev = serial->dev;

	अगर (product == MOSCHIP_DEVICE_ID_7715) अणु
		काष्ठा urb *urb = serial->port[0]->पूर्णांकerrupt_in_urb;

		urb->complete = mos7715_पूर्णांकerrupt_callback;

#अगर_घोषित CONFIG_USB_SERIAL_MOS7715_PARPORT
		ret_val = mos7715_parport_init(serial);
		अगर (ret_val < 0)
			वापस ret_val;
#पूर्ण_अगर
	पूर्ण
	/* start the पूर्णांकerrupt urb */
	ret_val = usb_submit_urb(serial->port[0]->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (ret_val) अणु
		dev_err(&dev->dev, "failed to submit interrupt urb: %d\n",
			ret_val);
	पूर्ण

	/* LSR For Port 1 */
	पढ़ो_mos_reg(serial, 0, MOS7720_LSR, &data);
	dev_dbg(&dev->dev, "LSR:%x\n", data);

	वापस 0;
पूर्ण

अटल व्योम mos7720_release(काष्ठा usb_serial *serial)
अणु
	usb_समाप्त_urb(serial->port[0]->पूर्णांकerrupt_in_urb);

#अगर_घोषित CONFIG_USB_SERIAL_MOS7715_PARPORT
	/* बंद the parallel port */

	अगर (le16_to_cpu(serial->dev->descriptor.idProduct)
	    == MOSCHIP_DEVICE_ID_7715) अणु
		काष्ठा mos7715_parport *mos_parport =
			usb_get_serial_data(serial);

		/* prevent शून्य ptr dereference in port callbacks */
		spin_lock(&release_lock);
		mos_parport->pp->निजी_data = शून्य;
		spin_unlock(&release_lock);

		/* रुको क्रम synchronous usb calls to वापस */
		अगर (mos_parport->msg_pending)
			रुको_क्रम_completion_समयout(&mos_parport->syncmsg_compl,
					    msecs_to_jअगरfies(MOS_WDR_TIMEOUT));
		/*
		 * If delayed work is currently scheduled, रुको क्रम it to
		 * complete. This also implies barriers that ensure the
		 * below serial clearing is not hoisted above the ->work.
		 */
		cancel_work_sync(&mos_parport->work);

		parport_हटाओ_port(mos_parport->pp);
		usb_set_serial_data(serial, शून्य);
		mos_parport->serial = शून्य;

		parport_del_port(mos_parport->pp);

		kref_put(&mos_parport->ref_count, destroy_mos_parport);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक mos7720_port_probe(काष्ठा usb_serial_port *port)
अणु
	काष्ठा moschip_port *mos7720_port;

	mos7720_port = kzalloc(माप(*mos7720_port), GFP_KERNEL);
	अगर (!mos7720_port)
		वापस -ENOMEM;

	mos7720_port->port = port;

	usb_set_serial_port_data(port, mos7720_port);

	वापस 0;
पूर्ण

अटल व्योम mos7720_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा moschip_port *mos7720_port;

	mos7720_port = usb_get_serial_port_data(port);
	kमुक्त(mos7720_port);
पूर्ण

अटल काष्ठा usb_serial_driver moschip7720_2port_driver = अणु
	.driver = अणु
		.owner =	THIS_MODULE,
		.name =		"moschip7720",
	पूर्ण,
	.description		= "Moschip 2 port adapter",
	.id_table		= id_table,
	.num_bulk_in		= 2,
	.num_bulk_out		= 2,
	.num_पूर्णांकerrupt_in	= 1,
	.calc_num_ports		= mos77xx_calc_num_ports,
	.खोलो			= mos7720_खोलो,
	.बंद			= mos7720_बंद,
	.throttle		= mos7720_throttle,
	.unthrottle		= mos7720_unthrottle,
	.attach			= mos7720_startup,
	.release		= mos7720_release,
	.port_probe		= mos7720_port_probe,
	.port_हटाओ		= mos7720_port_हटाओ,
	.ioctl			= mos7720_ioctl,
	.tiocmget		= mos7720_tiocmget,
	.tiocmset		= mos7720_tiocmset,
	.set_termios		= mos7720_set_termios,
	.ग_लिखो			= mos7720_ग_लिखो,
	.ग_लिखो_room		= mos7720_ग_लिखो_room,
	.अक्षरs_in_buffer	= mos7720_अक्षरs_in_buffer,
	.अवरोध_ctl		= mos7720_अवरोध,
	.पढ़ो_bulk_callback	= mos7720_bulk_in_callback,
	.पढ़ो_पूर्णांक_callback	= mos7720_पूर्णांकerrupt_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&moschip7720_2port_driver, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL v2");
