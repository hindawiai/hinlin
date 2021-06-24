<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * usblp.c
 *
 * Copyright (c) 1999 Michael Gee	<michael@linuxspecअगरic.com>
 * Copyright (c) 1999 Pavel Machek	<pavel@ucw.cz>
 * Copyright (c) 2000 Randy Dunlap	<rdunlap@xenoसमय.net>
 * Copyright (c) 2000 Vojtech Pavlik	<vojtech@suse.cz>
 # Copyright (c) 2001 Pete Zaitcev	<zaitcev@redhat.com>
 # Copyright (c) 2001 David Paschal	<paschal@rcsis.com>
 * Copyright (c) 2006 Oliver Neukum	<oliver@neukum.name>
 *
 * USB Prपूर्णांकer Device Class driver क्रम USB prपूर्णांकers and prपूर्णांकer cables
 *
 * Sponsored by SuSE
 *
 * ChangeLog:
 *	v0.1 - thorough cleaning, URBअगरication, almost a reग_लिखो
 *	v0.2 - some more cleanups
 *	v0.3 - cleaner again, रुकोqueue fixes
 *	v0.4 - fixes in unidirectional mode
 *	v0.5 - add DEVICE_ID string support
 *	v0.6 - never समय out
 *	v0.7 - fixed bulk-IN पढ़ो and poll (David Paschal)
 *	v0.8 - add devfs support
 *	v0.9 - fix unplug-जबतक-खोलो paths
 *	v0.10- हटाओ sleep_on, fix error on oom (oliver@neukum.org)
 *	v0.11 - add proto_bias option (Pete Zaitcev)
 *	v0.12 - add hpoj.sourceक्रमge.net ioctls (David Paschal)
 *	v0.13 - alloc space क्रम statusbuf (<status> not on stack);
 *		use usb_alloc_coherent() क्रम पढ़ो buf & ग_लिखो buf;
 *      none  - Maपूर्णांकained in Linux kernel after v0.13
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/lp.h>
#समावेश <linux/mutex.h>
#अघोषित DEBUG
#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/ratelimit.h>

/*
 * Version Inक्रमmation
 */
#घोषणा DRIVER_AUTHOR "Michael Gee, Pavel Machek, Vojtech Pavlik, Randy Dunlap, Pete Zaitcev, David Paschal"
#घोषणा DRIVER_DESC "USB Printer Device Class driver"

#घोषणा USBLP_BUF_SIZE		8192
#घोषणा USBLP_BUF_SIZE_IN	1024
#घोषणा USBLP_DEVICE_ID_SIZE	1024

/* ioctls: */
#घोषणा IOCNR_GET_DEVICE_ID		1
#घोषणा IOCNR_GET_PROTOCOLS		2
#घोषणा IOCNR_SET_PROTOCOL		3
#घोषणा IOCNR_HP_SET_CHANNEL		4
#घोषणा IOCNR_GET_BUS_ADDRESS		5
#घोषणा IOCNR_GET_VID_PID		6
#घोषणा IOCNR_SOFT_RESET		7
/* Get device_id string: */
#घोषणा LPIOC_GET_DEVICE_ID(len) _IOC(_IOC_READ, 'P', IOCNR_GET_DEVICE_ID, len)
/* The following ioctls were added क्रम http://hpoj.sourceक्रमge.net:
 * Get two-पूर्णांक array:
 * [0]=current protocol
 *     (1=USB_CLASS_PRINTER/1/1, 2=USB_CLASS_PRINTER/1/2,
 *         3=USB_CLASS_PRINTER/1/3),
 * [1]=supported protocol mask (mask&(1<<n)!=0 means
 *     USB_CLASS_PRINTER/1/n supported):
 */
#घोषणा LPIOC_GET_PROTOCOLS(len) _IOC(_IOC_READ, 'P', IOCNR_GET_PROTOCOLS, len)
/*
 * Set protocol
 *     (arg: 1=USB_CLASS_PRINTER/1/1, 2=USB_CLASS_PRINTER/1/2,
 *         3=USB_CLASS_PRINTER/1/3):
 */
#घोषणा LPIOC_SET_PROTOCOL _IOC(_IOC_WRITE, 'P', IOCNR_SET_PROTOCOL, 0)
/* Set channel number (HP Venकरोr-specअगरic command): */
#घोषणा LPIOC_HP_SET_CHANNEL _IOC(_IOC_WRITE, 'P', IOCNR_HP_SET_CHANNEL, 0)
/* Get two-पूर्णांक array: [0]=bus number, [1]=device address: */
#घोषणा LPIOC_GET_BUS_ADDRESS(len) _IOC(_IOC_READ, 'P', IOCNR_GET_BUS_ADDRESS, len)
/* Get two-पूर्णांक array: [0]=venकरोr ID, [1]=product ID: */
#घोषणा LPIOC_GET_VID_PID(len) _IOC(_IOC_READ, 'P', IOCNR_GET_VID_PID, len)
/* Perक्रमm class specअगरic soft reset */
#घोषणा LPIOC_SOFT_RESET _IOC(_IOC_NONE, 'P', IOCNR_SOFT_RESET, 0);

/*
 * A DEVICE_ID string may include the prपूर्णांकer's serial number.
 * It should end with a semi-colon (';').
 * An example from an HP 970C DeskJet prपूर्णांकer is (this is one दीर्घ string,
 * with the serial number changed):
MFG:HEWLETT-PACKARD;MDL:DESKJET 970C;CMD:MLC,PCL,PML;CLASS:PRINTER;DESCRIPTION:Hewlett-Packard DeskJet 970C;SERN:US970CSEPROF;VSTATUS:$HB0$NC0,ff,DN,IDLE,CUT,K1,C0,DP,NR,KP000,CP027;VP:0800,FL,B0;VJ:                    ;
 */

/*
 * USB Prपूर्णांकer Requests
 */

#घोषणा USBLP_REQ_GET_ID			0x00
#घोषणा USBLP_REQ_GET_STATUS			0x01
#घोषणा USBLP_REQ_RESET				0x02
#घोषणा USBLP_REQ_HP_CHANNEL_CHANGE_REQUEST	0x00	/* HP Venकरोr-specअगरic */

#घोषणा USBLP_MINORS		16
#घोषणा USBLP_MINOR_BASE	0

#घोषणा USBLP_CTL_TIMEOUT	5000			/* 5 seconds */

#घोषणा USBLP_FIRST_PROTOCOL	1
#घोषणा USBLP_LAST_PROTOCOL	3
#घोषणा USBLP_MAX_PROTOCOLS	(USBLP_LAST_PROTOCOL+1)

/*
 * some arbitrary status buffer size;
 * need a status buffer that is allocated via kदो_स्मृति(), not on stack
 */
#घोषणा STATUS_BUF_SIZE		8

/*
 * Locks करोwn the locking order:
 * ->wmut locks wstatus.
 * ->mut locks the whole usblp, except [rw]complete, and thus, by indirection,
 * [rw]status. We only touch status when we know the side idle.
 * ->lock locks what पूर्णांकerrupt accesses.
 */
काष्ठा usblp अणु
	काष्ठा usb_device	*dev;			/* USB device */
	काष्ठा mutex		wmut;
	काष्ठा mutex		mut;
	spinlock_t		lock;		/* locks rcomplete, wcomplete */
	अक्षर			*पढ़ोbuf;		/* पढ़ो transfer_buffer */
	अक्षर			*statusbuf;		/* status transfer_buffer */
	काष्ठा usb_anchor	urbs;
	रुको_queue_head_t	rरुको, wरुको;
	पूर्णांक			पढ़ोcount;		/* Counter क्रम पढ़ोs */
	पूर्णांक			अगरnum;			/* Interface number */
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;			/* The पूर्णांकerface */
	/*
	 * Alternate-setting numbers and endpoपूर्णांकs क्रम each protocol
	 * (USB_CLASS_PRINTER/1/अणुindex=1,2,3पूर्ण) that the device supports:
	 */
	काष्ठा अणु
		पूर्णांक				alt_setting;
		काष्ठा usb_endpoपूर्णांक_descriptor	*epग_लिखो;
		काष्ठा usb_endpoपूर्णांक_descriptor	*epपढ़ो;
	पूर्ण			protocol[USBLP_MAX_PROTOCOLS];
	पूर्णांक			current_protocol;
	पूर्णांक			minor;			/* minor number of device */
	पूर्णांक			wcomplete, rcomplete;
	पूर्णांक			wstatus;	/* bytes written or error */
	पूर्णांक			rstatus;	/* bytes पढ़ोy or error */
	अचिन्हित पूर्णांक		quirks;			/* quirks flags */
	अचिन्हित पूर्णांक		flags;			/* mode flags */
	अचिन्हित अक्षर		used;			/* True अगर खोलो */
	अचिन्हित अक्षर		present;		/* True अगर not disconnected */
	अचिन्हित अक्षर		bidir;			/* पूर्णांकerface is bidirectional */
	अचिन्हित अक्षर		no_paper;		/* Paper Out happened */
	अचिन्हित अक्षर		*device_id_string;	/* IEEE 1284 DEVICE ID string (ptr) */
							/* first 2 bytes are (big-endian) length */
पूर्ण;

#अगर_घोषित DEBUG
अटल व्योम usblp_dump(काष्ठा usblp *usblp)
अणु
	काष्ठा device *dev = &usblp->पूर्णांकf->dev;
	पूर्णांक p;

	dev_dbg(dev, "usblp=0x%p\n", usblp);
	dev_dbg(dev, "dev=0x%p\n", usblp->dev);
	dev_dbg(dev, "present=%d\n", usblp->present);
	dev_dbg(dev, "readbuf=0x%p\n", usblp->पढ़ोbuf);
	dev_dbg(dev, "readcount=%d\n", usblp->पढ़ोcount);
	dev_dbg(dev, "ifnum=%d\n", usblp->अगरnum);
	क्रम (p = USBLP_FIRST_PROTOCOL; p <= USBLP_LAST_PROTOCOL; p++) अणु
		dev_dbg(dev, "protocol[%d].alt_setting=%d\n", p,
			usblp->protocol[p].alt_setting);
		dev_dbg(dev, "protocol[%d].epwrite=%p\n", p,
			usblp->protocol[p].epग_लिखो);
		dev_dbg(dev, "protocol[%d].epread=%p\n", p,
			usblp->protocol[p].epपढ़ो);
	पूर्ण
	dev_dbg(dev, "current_protocol=%d\n", usblp->current_protocol);
	dev_dbg(dev, "minor=%d\n", usblp->minor);
	dev_dbg(dev, "wstatus=%d\n", usblp->wstatus);
	dev_dbg(dev, "rstatus=%d\n", usblp->rstatus);
	dev_dbg(dev, "quirks=%d\n", usblp->quirks);
	dev_dbg(dev, "used=%d\n", usblp->used);
	dev_dbg(dev, "bidir=%d\n", usblp->bidir);
	dev_dbg(dev, "device_id_string=\"%s\"\n",
		usblp->device_id_string ?
			usblp->device_id_string + 2 :
			(अचिन्हित अक्षर *)"(null)");
पूर्ण
#पूर्ण_अगर

/* Quirks: various prपूर्णांकer quirks are handled by this table & its flags. */

काष्ठा quirk_prपूर्णांकer_काष्ठा अणु
	__u16 venकरोrId;
	__u16 productId;
	अचिन्हित पूर्णांक quirks;
पूर्ण;

#घोषणा USBLP_QUIRK_BIसूची	0x1	/* reports bidir but requires unidirectional mode (no INs/पढ़ोs) */
#घोषणा USBLP_QUIRK_USB_INIT	0x2	/* needs venकरोr USB init string */
#घोषणा USBLP_QUIRK_BAD_CLASS	0x4	/* descriptor uses venकरोr-specअगरic Class or SubClass */

अटल स्थिर काष्ठा quirk_prपूर्णांकer_काष्ठा quirk_prपूर्णांकers[] = अणु
	अणु 0x03f0, 0x0004, USBLP_QUIRK_BIसूची पूर्ण, /* HP DeskJet 895C */
	अणु 0x03f0, 0x0104, USBLP_QUIRK_BIसूची पूर्ण, /* HP DeskJet 880C */
	अणु 0x03f0, 0x0204, USBLP_QUIRK_BIसूची पूर्ण, /* HP DeskJet 815C */
	अणु 0x03f0, 0x0304, USBLP_QUIRK_BIसूची पूर्ण, /* HP DeskJet 810C/812C */
	अणु 0x03f0, 0x0404, USBLP_QUIRK_BIसूची पूर्ण, /* HP DeskJet 830C */
	अणु 0x03f0, 0x0504, USBLP_QUIRK_BIसूची पूर्ण, /* HP DeskJet 885C */
	अणु 0x03f0, 0x0604, USBLP_QUIRK_BIसूची पूर्ण, /* HP DeskJet 840C */
	अणु 0x03f0, 0x0804, USBLP_QUIRK_BIसूची पूर्ण, /* HP DeskJet 816C */
	अणु 0x03f0, 0x1104, USBLP_QUIRK_BIसूची पूर्ण, /* HP Deskjet 959C */
	अणु 0x0409, 0xefbe, USBLP_QUIRK_BIसूची पूर्ण, /* NEC Picty900 (HP OEM) */
	अणु 0x0409, 0xbef4, USBLP_QUIRK_BIसूची पूर्ण, /* NEC Picty760 (HP OEM) */
	अणु 0x0409, 0xf0be, USBLP_QUIRK_BIसूची पूर्ण, /* NEC Picty920 (HP OEM) */
	अणु 0x0409, 0xf1be, USBLP_QUIRK_BIसूची पूर्ण, /* NEC Picty800 (HP OEM) */
	अणु 0x0482, 0x0010, USBLP_QUIRK_BIसूची पूर्ण, /* Kyocera Mita FS 820, by zut <kernel@zut.de> */
	अणु 0x04f9, 0x000d, USBLP_QUIRK_BIसूची पूर्ण, /* Brother Industries, Ltd HL-1440 Laser Prपूर्णांकer */
	अणु 0x04b8, 0x0202, USBLP_QUIRK_BAD_CLASS पूर्ण, /* Seiko Epson Receipt Prपूर्णांकer M129C */
	अणु 0, 0 पूर्ण
पूर्ण;

अटल पूर्णांक usblp_wरुको(काष्ठा usblp *usblp, पूर्णांक nonblock);
अटल पूर्णांक usblp_wtest(काष्ठा usblp *usblp, पूर्णांक nonblock);
अटल पूर्णांक usblp_rरुको_and_lock(काष्ठा usblp *usblp, पूर्णांक nonblock);
अटल पूर्णांक usblp_rtest(काष्ठा usblp *usblp, पूर्णांक nonblock);
अटल पूर्णांक usblp_submit_पढ़ो(काष्ठा usblp *usblp);
अटल पूर्णांक usblp_select_alts(काष्ठा usblp *usblp);
अटल पूर्णांक usblp_set_protocol(काष्ठा usblp *usblp, पूर्णांक protocol);
अटल पूर्णांक usblp_cache_device_id_string(काष्ठा usblp *usblp);

/* क्रमward reference to make our lives easier */
अटल काष्ठा usb_driver usblp_driver;
अटल DEFINE_MUTEX(usblp_mutex);	/* locks the existence of usblp's */

/*
 * Functions क्रम usblp control messages.
 */

अटल पूर्णांक usblp_ctrl_msg(काष्ठा usblp *usblp, पूर्णांक request, पूर्णांक type, पूर्णांक dir, पूर्णांक recip, पूर्णांक value, व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक retval;
	पूर्णांक index = usblp->अगरnum;

	/* High byte has the पूर्णांकerface index.
	   Low byte has the alternate setting.
	 */
	अगर ((request == USBLP_REQ_GET_ID) && (type == USB_TYPE_CLASS))
		index = (usblp->अगरnum<<8)|usblp->protocol[usblp->current_protocol].alt_setting;

	retval = usb_control_msg(usblp->dev,
		dir ? usb_rcvctrlpipe(usblp->dev, 0) : usb_sndctrlpipe(usblp->dev, 0),
		request, type | dir | recip, value, index, buf, len, USBLP_CTL_TIMEOUT);
	dev_dbg(&usblp->पूर्णांकf->dev,
		"usblp_control_msg: rq: 0x%02x dir: %d recip: %d value: %d idx: %d len: %#x result: %d\n",
		request, !!dir, recip, value, index, len, retval);
	वापस retval < 0 ? retval : 0;
पूर्ण

#घोषणा usblp_पढ़ो_status(usblp, status)\
	usblp_ctrl_msg(usblp, USBLP_REQ_GET_STATUS, USB_TYPE_CLASS, USB_सूची_IN, USB_RECIP_INTERFACE, 0, status, 1)
#घोषणा usblp_get_id(usblp, config, id, maxlen)\
	usblp_ctrl_msg(usblp, USBLP_REQ_GET_ID, USB_TYPE_CLASS, USB_सूची_IN, USB_RECIP_INTERFACE, config, id, maxlen)
#घोषणा usblp_reset(usblp)\
	usblp_ctrl_msg(usblp, USBLP_REQ_RESET, USB_TYPE_CLASS, USB_सूची_OUT, USB_RECIP_OTHER, 0, शून्य, 0)

अटल पूर्णांक usblp_hp_channel_change_request(काष्ठा usblp *usblp, पूर्णांक channel, u8 *new_channel)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kzalloc(1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = usblp_ctrl_msg(usblp, USBLP_REQ_HP_CHANNEL_CHANGE_REQUEST,
			USB_TYPE_VENDOR, USB_सूची_IN, USB_RECIP_INTERFACE,
			channel, buf, 1);
	अगर (ret == 0)
		*new_channel = buf[0];

	kमुक्त(buf);

	वापस ret;
पूर्ण

/*
 * See the description क्रम usblp_select_alts() below क्रम the usage
 * explanation.  Look पूर्णांकo your /sys/kernel/debug/usb/devices and dmesg in
 * हाल of any trouble.
 */
अटल पूर्णांक proto_bias = -1;

/*
 * URB callback.
 */

अटल व्योम usblp_bulk_पढ़ो(काष्ठा urb *urb)
अणु
	काष्ठा usblp *usblp = urb->context;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	अगर (usblp->present && usblp->used) अणु
		अगर (status)
			prपूर्णांकk(KERN_WARNING "usblp%d: "
			    "nonzero read bulk status received: %d\n",
			    usblp->minor, status);
	पूर्ण
	spin_lock_irqsave(&usblp->lock, flags);
	अगर (status < 0)
		usblp->rstatus = status;
	अन्यथा
		usblp->rstatus = urb->actual_length;
	usblp->rcomplete = 1;
	wake_up(&usblp->rरुको);
	spin_unlock_irqrestore(&usblp->lock, flags);

	usb_मुक्त_urb(urb);
पूर्ण

अटल व्योम usblp_bulk_ग_लिखो(काष्ठा urb *urb)
अणु
	काष्ठा usblp *usblp = urb->context;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	अगर (usblp->present && usblp->used) अणु
		अगर (status)
			prपूर्णांकk(KERN_WARNING "usblp%d: "
			    "nonzero write bulk status received: %d\n",
			    usblp->minor, status);
	पूर्ण
	spin_lock_irqsave(&usblp->lock, flags);
	अगर (status < 0)
		usblp->wstatus = status;
	अन्यथा
		usblp->wstatus = urb->actual_length;
	usblp->no_paper = 0;
	usblp->wcomplete = 1;
	wake_up(&usblp->wरुको);
	spin_unlock_irqrestore(&usblp->lock, flags);

	usb_मुक्त_urb(urb);
पूर्ण

/*
 * Get and prपूर्णांक prपूर्णांकer errors.
 */

अटल स्थिर अक्षर *usblp_messages[] = अणु "ok", "out of paper", "off-line", "on fire" पूर्ण;

अटल पूर्णांक usblp_check_status(काष्ठा usblp *usblp, पूर्णांक err)
अणु
	अचिन्हित अक्षर status, newerr = 0;
	पूर्णांक error;

	mutex_lock(&usblp->mut);
	अगर ((error = usblp_पढ़ो_status(usblp, usblp->statusbuf)) < 0) अणु
		mutex_unlock(&usblp->mut);
		prपूर्णांकk_ratelimited(KERN_ERR
				"usblp%d: error %d reading printer status\n",
				usblp->minor, error);
		वापस 0;
	पूर्ण
	status = *usblp->statusbuf;
	mutex_unlock(&usblp->mut);

	अगर (~status & LP_PERRORP)
		newerr = 3;
	अगर (status & LP_POUTPA)
		newerr = 1;
	अगर (~status & LP_PSELECD)
		newerr = 2;

	अगर (newerr != err) अणु
		prपूर्णांकk(KERN_INFO "usblp%d: %s\n",
		   usblp->minor, usblp_messages[newerr]);
	पूर्ण

	वापस newerr;
पूर्ण

अटल पूर्णांक handle_bidir(काष्ठा usblp *usblp)
अणु
	अगर (usblp->bidir && usblp->used) अणु
		अगर (usblp_submit_पढ़ो(usblp) < 0)
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * File op functions.
 */

अटल पूर्णांक usblp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक minor = iminor(inode);
	काष्ठा usblp *usblp;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक retval;

	अगर (minor < 0)
		वापस -ENODEV;

	mutex_lock(&usblp_mutex);

	retval = -ENODEV;
	पूर्णांकf = usb_find_पूर्णांकerface(&usblp_driver, minor);
	अगर (!पूर्णांकf)
		जाओ out;
	usblp = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (!usblp || !usblp->dev || !usblp->present)
		जाओ out;

	retval = -EBUSY;
	अगर (usblp->used)
		जाओ out;

	/*
	 * We करो not implement LP_ABORTOPEN/LPABORTOPEN क्रम two reasons:
	 *  - We करो not want persistent state which बंद(2) करोes not clear
	 *  - It is not used anyway, according to CUPS people
	 */

	retval = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकf);
	अगर (retval < 0)
		जाओ out;
	usblp->used = 1;
	file->निजी_data = usblp;

	usblp->wcomplete = 1; /* we begin ग_लिखोable */
	usblp->wstatus = 0;
	usblp->rcomplete = 0;

	अगर (handle_bidir(usblp) < 0) अणु
		usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकf);
		usblp->used = 0;
		file->निजी_data = शून्य;
		retval = -EIO;
	पूर्ण
out:
	mutex_unlock(&usblp_mutex);
	वापस retval;
पूर्ण

अटल व्योम usblp_cleanup(काष्ठा usblp *usblp)
अणु
	prपूर्णांकk(KERN_INFO "usblp%d: removed\n", usblp->minor);

	kमुक्त(usblp->पढ़ोbuf);
	kमुक्त(usblp->device_id_string);
	kमुक्त(usblp->statusbuf);
	usb_put_पूर्णांकf(usblp->पूर्णांकf);
	kमुक्त(usblp);
पूर्ण

अटल व्योम usblp_unlink_urbs(काष्ठा usblp *usblp)
अणु
	usb_समाप्त_anchored_urbs(&usblp->urbs);
पूर्ण

अटल पूर्णांक usblp_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usblp *usblp = file->निजी_data;

	usblp->flags &= ~LP_ABORT;

	mutex_lock(&usblp_mutex);
	usblp->used = 0;
	अगर (usblp->present)
		usblp_unlink_urbs(usblp);

	usb_स्वतःpm_put_पूर्णांकerface(usblp->पूर्णांकf);

	अगर (!usblp->present)		/* finish cleanup from disconnect */
		usblp_cleanup(usblp);	/* any URBs must be dead */

	mutex_unlock(&usblp_mutex);
	वापस 0;
पूर्ण

/* No kernel lock - fine */
अटल __poll_t usblp_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा usblp *usblp = file->निजी_data;
	__poll_t ret = 0;
	अचिन्हित दीर्घ flags;

	/* Should we check file->f_mode & FMODE_WRITE beक्रमe poll_रुको()? */
	poll_रुको(file, &usblp->rरुको, रुको);
	poll_रुको(file, &usblp->wरुको, रुको);

	mutex_lock(&usblp->mut);
	अगर (!usblp->present)
		ret |= EPOLLHUP;
	mutex_unlock(&usblp->mut);

	spin_lock_irqsave(&usblp->lock, flags);
	अगर (usblp->bidir && usblp->rcomplete)
		ret |= EPOLLIN  | EPOLLRDNORM;
	अगर (usblp->no_paper || usblp->wcomplete)
		ret |= EPOLLOUT | EPOLLWRNORM;
	spin_unlock_irqrestore(&usblp->lock, flags);
	वापस ret;
पूर्ण

अटल दीर्घ usblp_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा usblp *usblp = file->निजी_data;
	पूर्णांक length, err, i;
	अचिन्हित अक्षर newChannel;
	पूर्णांक status;
	पूर्णांक twoपूर्णांकs[2];
	पूर्णांक retval = 0;

	mutex_lock(&usblp->mut);
	अगर (!usblp->present) अणु
		retval = -ENODEV;
		जाओ करोne;
	पूर्ण

	dev_dbg(&usblp->पूर्णांकf->dev,
		"usblp_ioctl: cmd=0x%x (%c nr=%d len=%d dir=%d)\n", cmd,
		_IOC_TYPE(cmd), _IOC_NR(cmd), _IOC_SIZE(cmd), _IOC_सूची(cmd));

	अगर (_IOC_TYPE(cmd) == 'P')	/* new-style ioctl number */

		चयन (_IOC_NR(cmd)) अणु

		हाल IOCNR_GET_DEVICE_ID: /* get the DEVICE_ID string */
			अगर (_IOC_सूची(cmd) != _IOC_READ) अणु
				retval = -EINVAL;
				जाओ करोne;
			पूर्ण

			length = usblp_cache_device_id_string(usblp);
			अगर (length < 0) अणु
				retval = length;
				जाओ करोne;
			पूर्ण
			अगर (length > _IOC_SIZE(cmd))
				length = _IOC_SIZE(cmd); /* truncate */

			अगर (copy_to_user((व्योम __user *) arg,
					usblp->device_id_string,
					(अचिन्हित दीर्घ) length)) अणु
				retval = -EFAULT;
				जाओ करोne;
			पूर्ण

			अवरोध;

		हाल IOCNR_GET_PROTOCOLS:
			अगर (_IOC_सूची(cmd) != _IOC_READ ||
			    _IOC_SIZE(cmd) < माप(twoपूर्णांकs)) अणु
				retval = -EINVAL;
				जाओ करोne;
			पूर्ण

			twoपूर्णांकs[0] = usblp->current_protocol;
			twoपूर्णांकs[1] = 0;
			क्रम (i = USBLP_FIRST_PROTOCOL;
			     i <= USBLP_LAST_PROTOCOL; i++) अणु
				अगर (usblp->protocol[i].alt_setting >= 0)
					twoपूर्णांकs[1] |= (1<<i);
			पूर्ण

			अगर (copy_to_user((व्योम __user *)arg,
					(अचिन्हित अक्षर *)twoपूर्णांकs,
					माप(twoपूर्णांकs))) अणु
				retval = -EFAULT;
				जाओ करोne;
			पूर्ण

			अवरोध;

		हाल IOCNR_SET_PROTOCOL:
			अगर (_IOC_सूची(cmd) != _IOC_WRITE) अणु
				retval = -EINVAL;
				जाओ करोne;
			पूर्ण

#अगर_घोषित DEBUG
			अगर (arg == -10) अणु
				usblp_dump(usblp);
				अवरोध;
			पूर्ण
#पूर्ण_अगर

			usblp_unlink_urbs(usblp);
			retval = usblp_set_protocol(usblp, arg);
			अगर (retval < 0) अणु
				usblp_set_protocol(usblp,
					usblp->current_protocol);
			पूर्ण
			अवरोध;

		हाल IOCNR_HP_SET_CHANNEL:
			अगर (_IOC_सूची(cmd) != _IOC_WRITE ||
			    le16_to_cpu(usblp->dev->descriptor.idVenकरोr) != 0x03F0 ||
			    usblp->quirks & USBLP_QUIRK_BIसूची) अणु
				retval = -EINVAL;
				जाओ करोne;
			पूर्ण

			err = usblp_hp_channel_change_request(usblp,
				arg, &newChannel);
			अगर (err < 0) अणु
				dev_err(&usblp->dev->dev,
					"usblp%d: error = %d setting "
					"HP channel\n",
					usblp->minor, err);
				retval = -EIO;
				जाओ करोne;
			पूर्ण

			dev_dbg(&usblp->पूर्णांकf->dev,
				"usblp%d requested/got HP channel %ld/%d\n",
				usblp->minor, arg, newChannel);
			अवरोध;

		हाल IOCNR_GET_BUS_ADDRESS:
			अगर (_IOC_सूची(cmd) != _IOC_READ ||
			    _IOC_SIZE(cmd) < माप(twoपूर्णांकs)) अणु
				retval = -EINVAL;
				जाओ करोne;
			पूर्ण

			twoपूर्णांकs[0] = usblp->dev->bus->busnum;
			twoपूर्णांकs[1] = usblp->dev->devnum;
			अगर (copy_to_user((व्योम __user *)arg,
					(अचिन्हित अक्षर *)twoपूर्णांकs,
					माप(twoपूर्णांकs))) अणु
				retval = -EFAULT;
				जाओ करोne;
			पूर्ण

			dev_dbg(&usblp->पूर्णांकf->dev,
				"usblp%d is bus=%d, device=%d\n",
				usblp->minor, twoपूर्णांकs[0], twoपूर्णांकs[1]);
			अवरोध;

		हाल IOCNR_GET_VID_PID:
			अगर (_IOC_सूची(cmd) != _IOC_READ ||
			    _IOC_SIZE(cmd) < माप(twoपूर्णांकs)) अणु
				retval = -EINVAL;
				जाओ करोne;
			पूर्ण

			twoपूर्णांकs[0] = le16_to_cpu(usblp->dev->descriptor.idVenकरोr);
			twoपूर्णांकs[1] = le16_to_cpu(usblp->dev->descriptor.idProduct);
			अगर (copy_to_user((व्योम __user *)arg,
					(अचिन्हित अक्षर *)twoपूर्णांकs,
					माप(twoपूर्णांकs))) अणु
				retval = -EFAULT;
				जाओ करोne;
			पूर्ण

			dev_dbg(&usblp->पूर्णांकf->dev,
				"usblp%d is VID=0x%4.4X, PID=0x%4.4X\n",
				usblp->minor, twoपूर्णांकs[0], twoपूर्णांकs[1]);
			अवरोध;

		हाल IOCNR_SOFT_RESET:
			अगर (_IOC_सूची(cmd) != _IOC_NONE) अणु
				retval = -EINVAL;
				जाओ करोne;
			पूर्ण
			retval = usblp_reset(usblp);
			अवरोध;
		शेष:
			retval = -ENOTTY;
		पूर्ण
	अन्यथा	/* old-style ioctl value */
		चयन (cmd) अणु

		हाल LPGETSTATUS:
			retval = usblp_पढ़ो_status(usblp, usblp->statusbuf);
			अगर (retval) अणु
				prपूर्णांकk_ratelimited(KERN_ERR "usblp%d:"
					    "failed reading printer status (%d)\n",
					    usblp->minor, retval);
				retval = -EIO;
				जाओ करोne;
			पूर्ण
			status = *usblp->statusbuf;
			अगर (copy_to_user((व्योम __user *)arg, &status, माप(पूर्णांक)))
				retval = -EFAULT;
			अवरोध;

		हाल LPABORT:
			अगर (arg)
				usblp->flags |= LP_ABORT;
			अन्यथा
				usblp->flags &= ~LP_ABORT;
			अवरोध;

		शेष:
			retval = -ENOTTY;
		पूर्ण

करोne:
	mutex_unlock(&usblp->mut);
	वापस retval;
पूर्ण

अटल काष्ठा urb *usblp_new_ग_लिखोurb(काष्ठा usblp *usblp, पूर्णांक transfer_length)
अणु
	काष्ठा urb *urb;
	अक्षर *ग_लिखोbuf;

	ग_लिखोbuf = kदो_स्मृति(transfer_length, GFP_KERNEL);
	अगर (ग_लिखोbuf == शून्य)
		वापस शून्य;
	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (urb == शून्य) अणु
		kमुक्त(ग_लिखोbuf);
		वापस शून्य;
	पूर्ण

	usb_fill_bulk_urb(urb, usblp->dev,
		usb_sndbulkpipe(usblp->dev,
		 usblp->protocol[usblp->current_protocol].epग_लिखो->bEndpoपूर्णांकAddress),
		ग_लिखोbuf, transfer_length, usblp_bulk_ग_लिखो, usblp);
	urb->transfer_flags |= URB_FREE_BUFFER;

	वापस urb;
पूर्ण

अटल sमाप_प्रकार usblp_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा usblp *usblp = file->निजी_data;
	काष्ठा urb *ग_लिखोurb;
	पूर्णांक rv;
	पूर्णांक transfer_length;
	sमाप_प्रकार ग_लिखोcount = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&usblp->wmut)) अणु
		rv = -EINTR;
		जाओ उठाओ_biglock;
	पूर्ण
	अगर ((rv = usblp_wरुको(usblp, !!(file->f_flags & O_NONBLOCK))) < 0)
		जाओ उठाओ_रुको;

	जबतक (ग_लिखोcount < count) अणु
		/*
		 * Step 1: Submit next block.
		 */
		अगर ((transfer_length = count - ग_लिखोcount) > USBLP_BUF_SIZE)
			transfer_length = USBLP_BUF_SIZE;

		rv = -ENOMEM;
		ग_लिखोurb = usblp_new_ग_लिखोurb(usblp, transfer_length);
		अगर (ग_लिखोurb == शून्य)
			जाओ उठाओ_urb;
		usb_anchor_urb(ग_लिखोurb, &usblp->urbs);

		अगर (copy_from_user(ग_लिखोurb->transfer_buffer,
				   buffer + ग_लिखोcount, transfer_length)) अणु
			rv = -EFAULT;
			जाओ उठाओ_badaddr;
		पूर्ण

		spin_lock_irq(&usblp->lock);
		usblp->wcomplete = 0;
		spin_unlock_irq(&usblp->lock);
		अगर ((rv = usb_submit_urb(ग_लिखोurb, GFP_KERNEL)) < 0) अणु
			usblp->wstatus = 0;
			spin_lock_irq(&usblp->lock);
			usblp->no_paper = 0;
			usblp->wcomplete = 1;
			wake_up(&usblp->wरुको);
			spin_unlock_irq(&usblp->lock);
			अगर (rv != -ENOMEM)
				rv = -EIO;
			जाओ उठाओ_submit;
		पूर्ण

		/*
		 * Step 2: Wait क्रम transfer to end, collect results.
		 */
		rv = usblp_wरुको(usblp, !!(file->f_flags&O_NONBLOCK));
		अगर (rv < 0) अणु
			अगर (rv == -EAGAIN) अणु
				/* Presume that it's going to complete well. */
				ग_लिखोcount += transfer_length;
			पूर्ण
			अगर (rv == -ENOSPC) अणु
				spin_lock_irq(&usblp->lock);
				usblp->no_paper = 1;	/* Mark क्रम poll(2) */
				spin_unlock_irq(&usblp->lock);
				ग_लिखोcount += transfer_length;
			पूर्ण
			/* Leave URB dangling, to be cleaned on बंद. */
			जाओ collect_error;
		पूर्ण

		अगर (usblp->wstatus < 0) अणु
			rv = -EIO;
			जाओ collect_error;
		पूर्ण
		/*
		 * This is critical: it must be our URB, not other ग_लिखोr's.
		 * The wmut exists मुख्यly to cover us here.
		 */
		ग_लिखोcount += usblp->wstatus;
	पूर्ण

	mutex_unlock(&usblp->wmut);
	वापस ग_लिखोcount;

उठाओ_submit:
उठाओ_badaddr:
	usb_unanchor_urb(ग_लिखोurb);
	usb_मुक्त_urb(ग_लिखोurb);
उठाओ_urb:
उठाओ_रुको:
collect_error:		/* Out of उठाओ sequence */
	mutex_unlock(&usblp->wmut);
उठाओ_biglock:
	वापस ग_लिखोcount ? ग_लिखोcount : rv;
पूर्ण

/*
 * Notice that we fail to restart in a few हालs: on EFAULT, on restart
 * error, etc. This is the historical behaviour. In all such हालs we वापस
 * EIO, and applications loop in order to get the new पढ़ो going.
 */
अटल sमाप_प्रकार usblp_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा usblp *usblp = file->निजी_data;
	sमाप_प्रकार count;
	sमाप_प्रकार avail;
	पूर्णांक rv;

	अगर (!usblp->bidir)
		वापस -EINVAL;

	rv = usblp_rरुको_and_lock(usblp, !!(file->f_flags & O_NONBLOCK));
	अगर (rv < 0)
		वापस rv;

	अगर (!usblp->present) अणु
		count = -ENODEV;
		जाओ करोne;
	पूर्ण

	अगर ((avail = usblp->rstatus) < 0) अणु
		prपूर्णांकk(KERN_ERR "usblp%d: error %d reading from printer\n",
		    usblp->minor, (पूर्णांक)avail);
		usblp_submit_पढ़ो(usblp);
		count = -EIO;
		जाओ करोne;
	पूर्ण

	count = len < avail - usblp->पढ़ोcount ? len : avail - usblp->पढ़ोcount;
	अगर (count != 0 &&
	    copy_to_user(buffer, usblp->पढ़ोbuf + usblp->पढ़ोcount, count)) अणु
		count = -EFAULT;
		जाओ करोne;
	पूर्ण

	अगर ((usblp->पढ़ोcount += count) == avail) अणु
		अगर (usblp_submit_पढ़ो(usblp) < 0) अणु
			/* We करोn't want to leak USB वापस codes पूर्णांकo त्रुटि_सं. */
			अगर (count == 0)
				count = -EIO;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	mutex_unlock(&usblp->mut);
	वापस count;
पूर्ण

/*
 * Wait क्रम the ग_लिखो path to come idle.
 * This is called under the ->wmut, so the idle path stays idle.
 *
 * Our ग_लिखो path has a peculiar property: it करोes not buffer like a tty,
 * but रुकोs क्रम the ग_लिखो to succeed. This allows our ->release to bug out
 * without रुकोing क्रम ग_लिखोs to drain. But it obviously करोes not work
 * when O_NONBLOCK is set. So, applications setting O_NONBLOCK must use
 * select(2) or poll(2) to रुको क्रम the buffer to drain beक्रमe closing.
 * Alternatively, set blocking mode with fcntl and issue a zero-size ग_लिखो.
 */
अटल पूर्णांक usblp_wरुको(काष्ठा usblp *usblp, पूर्णांक nonblock)
अणु
	DECLARE_WAITQUEUE(रुकोa, current);
	पूर्णांक rc;
	पूर्णांक err = 0;

	add_रुको_queue(&usblp->wरुको, &रुकोa);
	क्रम (;;) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&usblp->mut)) अणु
			rc = -EINTR;
			अवरोध;
		पूर्ण
		set_current_state(TASK_INTERRUPTIBLE);
		rc = usblp_wtest(usblp, nonblock);
		mutex_unlock(&usblp->mut);
		अगर (rc <= 0)
			अवरोध;

		अगर (schedule_समयout(msecs_to_jअगरfies(1500)) == 0) अणु
			अगर (usblp->flags & LP_ABORT) अणु
				err = usblp_check_status(usblp, err);
				अगर (err == 1) अणु	/* Paper out */
					rc = -ENOSPC;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Prod the prपूर्णांकer, Gentoo#251237. */
				mutex_lock(&usblp->mut);
				usblp_पढ़ो_status(usblp, usblp->statusbuf);
				mutex_unlock(&usblp->mut);
			पूर्ण
		पूर्ण
	पूर्ण
	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&usblp->wरुको, &रुकोa);
	वापस rc;
पूर्ण

अटल पूर्णांक usblp_wtest(काष्ठा usblp *usblp, पूर्णांक nonblock)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!usblp->present)
		वापस -ENODEV;
	अगर (संकेत_pending(current))
		वापस -EINTR;
	spin_lock_irqsave(&usblp->lock, flags);
	अगर (usblp->wcomplete) अणु
		spin_unlock_irqrestore(&usblp->lock, flags);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&usblp->lock, flags);
	अगर (nonblock)
		वापस -EAGAIN;
	वापस 1;
पूर्ण

/*
 * Wait क्रम पढ़ो bytes to become available. This probably should have been
 * called usblp_r_lock_and_रुको(), because we lock first. But it's a traditional
 * name क्रम functions which lock and वापस.
 *
 * We करो not use रुको_event_पूर्णांकerruptible because it makes locking अगरfy.
 */
अटल पूर्णांक usblp_rरुको_and_lock(काष्ठा usblp *usblp, पूर्णांक nonblock)
अणु
	DECLARE_WAITQUEUE(रुकोa, current);
	पूर्णांक rc;

	add_रुको_queue(&usblp->rरुको, &रुकोa);
	क्रम (;;) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&usblp->mut)) अणु
			rc = -EINTR;
			अवरोध;
		पूर्ण
		set_current_state(TASK_INTERRUPTIBLE);
		अगर ((rc = usblp_rtest(usblp, nonblock)) < 0) अणु
			mutex_unlock(&usblp->mut);
			अवरोध;
		पूर्ण
		अगर (rc == 0)	/* Keep it locked */
			अवरोध;
		mutex_unlock(&usblp->mut);
		schedule();
	पूर्ण
	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&usblp->rरुको, &रुकोa);
	वापस rc;
पूर्ण

अटल पूर्णांक usblp_rtest(काष्ठा usblp *usblp, पूर्णांक nonblock)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!usblp->present)
		वापस -ENODEV;
	अगर (संकेत_pending(current))
		वापस -EINTR;
	spin_lock_irqsave(&usblp->lock, flags);
	अगर (usblp->rcomplete) अणु
		spin_unlock_irqrestore(&usblp->lock, flags);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&usblp->lock, flags);
	अगर (nonblock)
		वापस -EAGAIN;
	वापस 1;
पूर्ण

/*
 * Please check ->bidir and other such things outside क्रम now.
 */
अटल पूर्णांक usblp_submit_पढ़ो(काष्ठा usblp *usblp)
अणु
	काष्ठा urb *urb;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	rc = -ENOMEM;
	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (urb == शून्य)
		जाओ उठाओ_urb;

	usb_fill_bulk_urb(urb, usblp->dev,
		usb_rcvbulkpipe(usblp->dev,
		  usblp->protocol[usblp->current_protocol].epपढ़ो->bEndpoपूर्णांकAddress),
		usblp->पढ़ोbuf, USBLP_BUF_SIZE_IN,
		usblp_bulk_पढ़ो, usblp);
	usb_anchor_urb(urb, &usblp->urbs);

	spin_lock_irqsave(&usblp->lock, flags);
	usblp->पढ़ोcount = 0; /* XXX Why here? */
	usblp->rcomplete = 0;
	spin_unlock_irqrestore(&usblp->lock, flags);
	अगर ((rc = usb_submit_urb(urb, GFP_KERNEL)) < 0) अणु
		dev_dbg(&usblp->पूर्णांकf->dev, "error submitting urb (%d)\n", rc);
		spin_lock_irqsave(&usblp->lock, flags);
		usblp->rstatus = rc;
		usblp->rcomplete = 1;
		spin_unlock_irqrestore(&usblp->lock, flags);
		जाओ उठाओ_submit;
	पूर्ण

	वापस 0;

उठाओ_submit:
	usb_unanchor_urb(urb);
	usb_मुक्त_urb(urb);
उठाओ_urb:
	वापस rc;
पूर्ण

/*
 * Checks क्रम prपूर्णांकers that have quirks, such as requiring unidirectional
 * communication but reporting bidirectional; currently some HP prपूर्णांकers
 * have this flaw (HP 810, 880, 895, etc.), or needing an init string
 * sent at each खोलो (like some Epsons).
 * Returns 1 अगर found, 0 अगर not found.
 *
 * HP recommended that we use the bidirectional पूर्णांकerface but
 * करोn't attempt any bulk IN transfers from the IN endpoपूर्णांक.
 * Here's some more detail on the problem:
 * The problem is not that it isn't bidirectional though. The problem
 * is that अगर you request a device ID, or status inक्रमmation, जबतक
 * the buffers are full, the वापस data will end up in the prपूर्णांक data
 * buffer. For example अगर you make sure you never request the device ID
 * जबतक you are sending prपूर्णांक data, and you करोn't try to query the
 * prपूर्णांकer status every couple of milliseconds, you will probably be OK.
 */
अटल अचिन्हित पूर्णांक usblp_quirks(__u16 venकरोr, __u16 product)
अणु
	पूर्णांक i;

	क्रम (i = 0; quirk_prपूर्णांकers[i].venकरोrId; i++) अणु
		अगर (venकरोr == quirk_prपूर्णांकers[i].venकरोrId &&
		    product == quirk_prपूर्णांकers[i].productId)
			वापस quirk_prपूर्णांकers[i].quirks;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations usblp_fops = अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		usblp_पढ़ो,
	.ग_लिखो =	usblp_ग_लिखो,
	.poll =		usblp_poll,
	.unlocked_ioctl =	usblp_ioctl,
	.compat_ioctl =		usblp_ioctl,
	.खोलो =		usblp_खोलो,
	.release =	usblp_release,
	.llseek =	noop_llseek,
पूर्ण;

अटल अक्षर *usblp_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "usb/%s", dev_name(dev));
पूर्ण

अटल काष्ठा usb_class_driver usblp_class = अणु
	.name =		"lp%d",
	.devnode =	usblp_devnode,
	.fops =		&usblp_fops,
	.minor_base =	USBLP_MINOR_BASE,
पूर्ण;

अटल sमाप_प्रकार ieee1284_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usblp *usblp = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (usblp->device_id_string[0] == 0 &&
	    usblp->device_id_string[1] == 0)
		वापस 0;

	वापस प्र_लिखो(buf, "%s", usblp->device_id_string+2);
पूर्ण

अटल DEVICE_ATTR_RO(ieee1284_id);

अटल काष्ठा attribute *usblp_attrs[] = अणु
	&dev_attr_ieee1284_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(usblp);

अटल पूर्णांक usblp_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usblp *usblp;
	पूर्णांक protocol;
	पूर्णांक retval;

	/* Malloc and start initializing usblp काष्ठाure so we can use it
	 * directly. */
	usblp = kzalloc(माप(काष्ठा usblp), GFP_KERNEL);
	अगर (!usblp) अणु
		retval = -ENOMEM;
		जाओ पात_ret;
	पूर्ण
	usblp->dev = dev;
	mutex_init(&usblp->wmut);
	mutex_init(&usblp->mut);
	spin_lock_init(&usblp->lock);
	init_रुकोqueue_head(&usblp->rरुको);
	init_रुकोqueue_head(&usblp->wरुको);
	init_usb_anchor(&usblp->urbs);
	usblp->अगरnum = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;
	usblp->पूर्णांकf = usb_get_पूर्णांकf(पूर्णांकf);

	/* Malloc device ID string buffer to the largest expected length,
	 * since we can re-query it on an ioctl and a dynamic string
	 * could change in length. */
	अगर (!(usblp->device_id_string = kदो_स्मृति(USBLP_DEVICE_ID_SIZE, GFP_KERNEL))) अणु
		retval = -ENOMEM;
		जाओ पात;
	पूर्ण

	/*
	 * Allocate पढ़ो buffer. We somewhat wastefully
	 * दो_स्मृति both regardless of bidirectionality, because the
	 * alternate setting can be changed later via an ioctl.
	 */
	अगर (!(usblp->पढ़ोbuf = kदो_स्मृति(USBLP_BUF_SIZE_IN, GFP_KERNEL))) अणु
		retval = -ENOMEM;
		जाओ पात;
	पूर्ण

	/* Allocate buffer क्रम prपूर्णांकer status */
	usblp->statusbuf = kदो_स्मृति(STATUS_BUF_SIZE, GFP_KERNEL);
	अगर (!usblp->statusbuf) अणु
		retval = -ENOMEM;
		जाओ पात;
	पूर्ण

	/* Lookup quirks क्रम this prपूर्णांकer. */
	usblp->quirks = usblp_quirks(
		le16_to_cpu(dev->descriptor.idVenकरोr),
		le16_to_cpu(dev->descriptor.idProduct));

	/* Analyze and pick initial alternate settings and endpoपूर्णांकs. */
	protocol = usblp_select_alts(usblp);
	अगर (protocol < 0) अणु
		dev_dbg(&पूर्णांकf->dev,
			"incompatible printer-class device 0x%4.4X/0x%4.4X\n",
			le16_to_cpu(dev->descriptor.idVenकरोr),
			le16_to_cpu(dev->descriptor.idProduct));
		retval = -ENODEV;
		जाओ पात;
	पूर्ण

	/* Setup the selected alternate setting and endpoपूर्णांकs. */
	अगर (usblp_set_protocol(usblp, protocol) < 0) अणु
		retval = -ENODEV;	/* ->probe isn't ->ioctl */
		जाओ पात;
	पूर्ण

	/* Retrieve and store the device ID string. */
	usblp_cache_device_id_string(usblp);

#अगर_घोषित DEBUG
	usblp_check_status(usblp, 0);
#पूर्ण_अगर

	usb_set_पूर्णांकfdata(पूर्णांकf, usblp);

	usblp->present = 1;

	retval = usb_रेजिस्टर_dev(पूर्णांकf, &usblp_class);
	अगर (retval) अणु
		dev_err(&पूर्णांकf->dev,
			"usblp: Not able to get a minor (base %u, slice default): %d\n",
			USBLP_MINOR_BASE, retval);
		जाओ पात_पूर्णांकfdata;
	पूर्ण
	usblp->minor = पूर्णांकf->minor;
	dev_info(&पूर्णांकf->dev,
		"usblp%d: USB %sdirectional printer dev %d if %d alt %d proto %d vid 0x%4.4X pid 0x%4.4X\n",
		usblp->minor, usblp->bidir ? "Bi" : "Uni", dev->devnum,
		usblp->अगरnum,
		usblp->protocol[usblp->current_protocol].alt_setting,
		usblp->current_protocol,
		le16_to_cpu(usblp->dev->descriptor.idVenकरोr),
		le16_to_cpu(usblp->dev->descriptor.idProduct));

	वापस 0;

पात_पूर्णांकfdata:
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
पात:
	kमुक्त(usblp->पढ़ोbuf);
	kमुक्त(usblp->statusbuf);
	kमुक्त(usblp->device_id_string);
	usb_put_पूर्णांकf(usblp->पूर्णांकf);
	kमुक्त(usblp);
पात_ret:
	वापस retval;
पूर्ण

/*
 * We are a "new" style driver with usb_device_id table,
 * but our requirements are too पूर्णांकricate क्रम simple match to handle.
 *
 * The "proto_bias" option may be used to specअगरy the preferred protocol
 * क्रम all USB prपूर्णांकers (1=USB_CLASS_PRINTER/1/1, 2=USB_CLASS_PRINTER/1/2,
 * 3=USB_CLASS_PRINTER/1/3).  If the device supports the preferred protocol,
 * then we bind to it.
 *
 * The best पूर्णांकerface क्रम us is USB_CLASS_PRINTER/1/2, because it
 * is compatible with a stream of अक्षरacters. If we find it, we bind to it.
 *
 * Note that the people from hpoj.sourceक्रमge.net need to be able to
 * bind to USB_CLASS_PRINTER/1/3 (MLC/1284.4), so we provide them ioctls
 * क्रम this purpose.
 *
 * Failing USB_CLASS_PRINTER/1/2, we look क्रम USB_CLASS_PRINTER/1/3,
 * even though it's probably not stream-compatible, because this matches
 * the behaviour of the old code.
 *
 * If nothing अन्यथा, we bind to USB_CLASS_PRINTER/1/1
 * - the unidirectional पूर्णांकerface.
 */
अटल पूर्णांक usblp_select_alts(काष्ठा usblp *usblp)
अणु
	काष्ठा usb_पूर्णांकerface *अगर_alt;
	काष्ठा usb_host_पूर्णांकerface *अगरd;
	काष्ठा usb_endpoपूर्णांक_descriptor *epग_लिखो, *epपढ़ो;
	पूर्णांक p, i;
	पूर्णांक res;

	अगर_alt = usblp->पूर्णांकf;

	क्रम (p = 0; p < USBLP_MAX_PROTOCOLS; p++)
		usblp->protocol[p].alt_setting = -1;

	/* Find out what we have. */
	क्रम (i = 0; i < अगर_alt->num_altsetting; i++) अणु
		अगरd = &अगर_alt->altsetting[i];

		अगर (अगरd->desc.bInterfaceClass != USB_CLASS_PRINTER ||
		    अगरd->desc.bInterfaceSubClass != 1)
			अगर (!(usblp->quirks & USBLP_QUIRK_BAD_CLASS))
				जारी;

		अगर (अगरd->desc.bInterfaceProtocol < USBLP_FIRST_PROTOCOL ||
		    अगरd->desc.bInterfaceProtocol > USBLP_LAST_PROTOCOL)
			जारी;

		/* Look क्रम the expected bulk endpoपूर्णांकs. */
		अगर (अगरd->desc.bInterfaceProtocol > 1) अणु
			res = usb_find_common_endpoपूर्णांकs(अगरd,
					&epपढ़ो, &epग_लिखो, शून्य, शून्य);
		पूर्ण अन्यथा अणु
			epपढ़ो = शून्य;
			res = usb_find_bulk_out_endpoपूर्णांक(अगरd, &epग_लिखो);
		पूर्ण

		/* Ignore buggy hardware without the right endpoपूर्णांकs. */
		अगर (res)
			जारी;

		/* Turn off पढ़ोs क्रम buggy bidirectional prपूर्णांकers. */
		अगर (usblp->quirks & USBLP_QUIRK_BIसूची) अणु
			prपूर्णांकk(KERN_INFO "usblp%d: Disabling reads from "
			    "problematic bidirectional printer\n",
			    usblp->minor);
			epपढ़ो = शून्य;
		पूर्ण

		usblp->protocol[अगरd->desc.bInterfaceProtocol].alt_setting =
				अगरd->desc.bAlternateSetting;
		usblp->protocol[अगरd->desc.bInterfaceProtocol].epग_लिखो = epग_लिखो;
		usblp->protocol[अगरd->desc.bInterfaceProtocol].epपढ़ो = epपढ़ो;
	पूर्ण

	/* If our requested protocol is supported, then use it. */
	अगर (proto_bias >= USBLP_FIRST_PROTOCOL &&
	    proto_bias <= USBLP_LAST_PROTOCOL &&
	    usblp->protocol[proto_bias].alt_setting != -1)
		वापस proto_bias;

	/* Ordering is important here. */
	अगर (usblp->protocol[2].alt_setting != -1)
		वापस 2;
	अगर (usblp->protocol[1].alt_setting != -1)
		वापस 1;
	अगर (usblp->protocol[3].alt_setting != -1)
		वापस 3;

	/* If nothing is available, then करोn't bind to this device. */
	वापस -1;
पूर्ण

अटल पूर्णांक usblp_set_protocol(काष्ठा usblp *usblp, पूर्णांक protocol)
अणु
	पूर्णांक r, alts;

	अगर (protocol < USBLP_FIRST_PROTOCOL || protocol > USBLP_LAST_PROTOCOL)
		वापस -EINVAL;

	/* Don't unnecessarily set the interface if there's a single alt. */
	अगर (usblp->पूर्णांकf->num_altsetting > 1) अणु
		alts = usblp->protocol[protocol].alt_setting;
		अगर (alts < 0)
			वापस -EINVAL;
		r = usb_set_पूर्णांकerface(usblp->dev, usblp->अगरnum, alts);
		अगर (r < 0) अणु
			prपूर्णांकk(KERN_ERR "usblp: can't set desired altsetting %d on interface %d\n",
				alts, usblp->अगरnum);
			वापस r;
		पूर्ण
	पूर्ण

	usblp->bidir = (usblp->protocol[protocol].epपढ़ो != शून्य);
	usblp->current_protocol = protocol;
	dev_dbg(&usblp->पूर्णांकf->dev, "usblp%d set protocol %d\n",
		usblp->minor, protocol);
	वापस 0;
पूर्ण

/* Retrieves and caches device ID string.
 * Returns length, including length bytes but not null terminator.
 * On error, वापसs a negative त्रुटि_सं value. */
अटल पूर्णांक usblp_cache_device_id_string(काष्ठा usblp *usblp)
अणु
	पूर्णांक err, length;

	err = usblp_get_id(usblp, 0, usblp->device_id_string, USBLP_DEVICE_ID_SIZE - 1);
	अगर (err < 0) अणु
		dev_dbg(&usblp->पूर्णांकf->dev,
			"usblp%d: error = %d reading IEEE-1284 Device ID string\n",
			usblp->minor, err);
		usblp->device_id_string[0] = usblp->device_id_string[1] = '\0';
		वापस -EIO;
	पूर्ण

	/* First two bytes are length in big-endian.
	 * They count themselves, and we copy them पूर्णांकo
	 * the user's buffer. */
	length = be16_to_cpu(*((__be16 *)usblp->device_id_string));
	अगर (length < 2)
		length = 2;
	अन्यथा अगर (length >= USBLP_DEVICE_ID_SIZE)
		length = USBLP_DEVICE_ID_SIZE - 1;
	usblp->device_id_string[length] = '\0';

	dev_dbg(&usblp->पूर्णांकf->dev, "usblp%d Device ID string [len=%d]=\"%s\"\n",
		usblp->minor, length, &usblp->device_id_string[2]);

	वापस length;
पूर्ण

अटल व्योम usblp_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usblp *usblp = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_deरेजिस्टर_dev(पूर्णांकf, &usblp_class);

	अगर (!usblp || !usblp->dev) अणु
		dev_err(&पूर्णांकf->dev, "bogus disconnect\n");
		BUG();
	पूर्ण

	mutex_lock(&usblp_mutex);
	mutex_lock(&usblp->mut);
	usblp->present = 0;
	wake_up(&usblp->wरुको);
	wake_up(&usblp->rरुको);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	usblp_unlink_urbs(usblp);
	mutex_unlock(&usblp->mut);
	usb_poison_anchored_urbs(&usblp->urbs);

	अगर (!usblp->used)
		usblp_cleanup(usblp);

	mutex_unlock(&usblp_mutex);
पूर्ण

अटल पूर्णांक usblp_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usblp *usblp = usb_get_पूर्णांकfdata(पूर्णांकf);

	usblp_unlink_urbs(usblp);
#अगर 0 /* XXX Do we want this? What अगर someone is पढ़ोing, should we fail? */
	/* not strictly necessary, but just in हाल */
	wake_up(&usblp->wरुको);
	wake_up(&usblp->rरुको);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक usblp_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usblp *usblp = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक r;

	r = handle_bidir(usblp);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा usb_device_id usblp_ids[] = अणु
	अणु USB_DEVICE_INFO(USB_CLASS_PRINTER, 1, 1) पूर्ण,
	अणु USB_DEVICE_INFO(USB_CLASS_PRINTER, 1, 2) पूर्ण,
	अणु USB_DEVICE_INFO(USB_CLASS_PRINTER, 1, 3) पूर्ण,
	अणु USB_INTERFACE_INFO(USB_CLASS_PRINTER, 1, 1) पूर्ण,
	अणु USB_INTERFACE_INFO(USB_CLASS_PRINTER, 1, 2) पूर्ण,
	अणु USB_INTERFACE_INFO(USB_CLASS_PRINTER, 1, 3) पूर्ण,
	अणु USB_DEVICE(0x04b8, 0x0202) पूर्ण,	/* Seiko Epson Receipt Prपूर्णांकer M129C */
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, usblp_ids);

अटल काष्ठा usb_driver usblp_driver = अणु
	.name =		"usblp",
	.probe =	usblp_probe,
	.disconnect =	usblp_disconnect,
	.suspend =	usblp_suspend,
	.resume =	usblp_resume,
	.id_table =	usblp_ids,
	.dev_groups =	usblp_groups,
	.supports_स्वतःsuspend =	1,
पूर्ण;

module_usb_driver(usblp_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
module_param(proto_bias, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(proto_bias, "Favourite protocol number");
MODULE_LICENSE("GPL");
