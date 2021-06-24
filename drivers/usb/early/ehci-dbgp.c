<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Standalone EHCI usb debug driver
 *
 * Originally written by:
 *  Eric W. Biederman" <ebiederm@xmission.com> and
 *  Yinghai Lu <yhlu.kernel@gmail.com>
 *
 * Changes क्रम early/late prपूर्णांकk and HW errata:
 *  Jason Wessel <jason.wessel@windriver.com>
 *  Copyright (C) 2009 Wind River Systems, Inc.
 *
 */

#समावेश <linux/console.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/ehci_def.h>
#समावेश <linux/delay.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/fixmap.h>

/* The code here is पूर्णांकended to talk directly to the EHCI debug port
 * and करोes not require that you have any kind of USB host controller
 * drivers or USB device drivers compiled पूर्णांकo the kernel.
 *
 * If you make a change to anything in here, the following test हालs
 * need to pass where a USB debug device works in the following
 * configurations.
 *
 * 1. boot args:  earlyprपूर्णांकk=dbgp
 *     o kernel compiled with # CONFIG_USB_EHCI_HCD is not set
 *     o kernel compiled with CONFIG_USB_EHCI_HCD=y
 * 2. boot args: earlyprपूर्णांकk=dbgp,keep
 *     o kernel compiled with # CONFIG_USB_EHCI_HCD is not set
 *     o kernel compiled with CONFIG_USB_EHCI_HCD=y
 * 3. boot args: earlyprपूर्णांकk=dbgp console=ttyUSB0
 *     o kernel has CONFIG_USB_EHCI_HCD=y and
 *       CONFIG_USB_SERIAL_DEBUG=y
 * 4. boot args: earlyprपूर्णांकk=vga,dbgp
 *     o kernel compiled with # CONFIG_USB_EHCI_HCD is not set
 *     o kernel compiled with CONFIG_USB_EHCI_HCD=y
 *
 * For the 4th configuration you can turn on or off the DBGP_DEBUG
 * such that you can debug the dbgp device's driver code.
 */

अटल पूर्णांक dbgp_phys_port = 1;

अटल काष्ठा ehci_caps __iomem *ehci_caps;
अटल काष्ठा ehci_regs __iomem *ehci_regs;
अटल काष्ठा ehci_dbg_port __iomem *ehci_debug;
अटल पूर्णांक dbgp_not_safe; /* Cannot use debug device during ehci reset */
अटल अचिन्हित पूर्णांक dbgp_endpoपूर्णांक_out;
अटल अचिन्हित पूर्णांक dbgp_endpoपूर्णांक_in;

काष्ठा ehci_dev अणु
	u32 bus;
	u32 slot;
	u32 func;
पूर्ण;

अटल काष्ठा ehci_dev ehci_dev;

#घोषणा USB_DEBUG_DEVNUM 127

#अगर_घोषित DBGP_DEBUG
#घोषणा dbgp_prपूर्णांकk prपूर्णांकk
अटल व्योम dbgp_ehci_status(अक्षर *str)
अणु
	अगर (!ehci_debug)
		वापस;
	dbgp_prपूर्णांकk("dbgp: %s\n", str);
	dbgp_prपूर्णांकk("  Debug control: %08x", पढ़ोl(&ehci_debug->control));
	dbgp_prपूर्णांकk("  ehci cmd     : %08x", पढ़ोl(&ehci_regs->command));
	dbgp_prपूर्णांकk("  ehci conf flg: %08x\n",
		    पढ़ोl(&ehci_regs->configured_flag));
	dbgp_prपूर्णांकk("  ehci status  : %08x", पढ़ोl(&ehci_regs->status));
	dbgp_prपूर्णांकk("  ehci portsc  : %08x\n",
		    पढ़ोl(&ehci_regs->port_status[dbgp_phys_port - 1]));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dbgp_ehci_status(अक्षर *str) अणु पूर्ण
अटल अंतरभूत व्योम dbgp_prपूर्णांकk(स्थिर अक्षर *fmt, ...) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u32 dbgp_len_update(u32 x, u32 len)
अणु
	वापस (x & ~0x0f) | (len & 0x0f);
पूर्ण

#अगर_घोषित CONFIG_KGDB
अटल काष्ठा kgdb_io kgdbdbgp_io_ops;
#घोषणा dbgp_kgdb_mode (dbg_io_ops == &kgdbdbgp_io_ops)
#अन्यथा
#घोषणा dbgp_kgdb_mode (0)
#पूर्ण_अगर

/* Local version of HC_LENGTH macro as ehci काष्ठा is not available here */
#घोषणा EARLY_HC_LENGTH(p)	(0x00ff & (p)) /* bits 7 : 0 */

/*
 * USB Packet IDs (PIDs)
 */

/* token */
#घोषणा USB_PID_OUT		0xe1
#घोषणा USB_PID_IN		0x69
#घोषणा USB_PID_SOF		0xa5
#घोषणा USB_PID_SETUP		0x2d
/* handshake */
#घोषणा USB_PID_ACK		0xd2
#घोषणा USB_PID_NAK		0x5a
#घोषणा USB_PID_STALL		0x1e
#घोषणा USB_PID_NYET		0x96
/* data */
#घोषणा USB_PID_DATA0		0xc3
#घोषणा USB_PID_DATA1		0x4b
#घोषणा USB_PID_DATA2		0x87
#घोषणा USB_PID_MDATA		0x0f
/* Special */
#घोषणा USB_PID_PREAMBLE	0x3c
#घोषणा USB_PID_ERR		0x3c
#घोषणा USB_PID_SPLIT		0x78
#घोषणा USB_PID_PING		0xb4
#घोषणा USB_PID_UNDEF_0		0xf0

#घोषणा USB_PID_DATA_TOGGLE	0x88
#घोषणा DBGP_CLAIM (DBGP_OWNER | DBGP_ENABLED | DBGP_INUSE)

#घोषणा PCI_CAP_ID_EHCI_DEBUG	0xa

#घोषणा HUB_ROOT_RESET_TIME	50	/* बार are in msec */
#घोषणा HUB_SHORT_RESET_TIME	10
#घोषणा HUB_LONG_RESET_TIME	200
#घोषणा HUB_RESET_TIMEOUT	500

#घोषणा DBGP_MAX_PACKET		8
#घोषणा DBGP_TIMEOUT		(250 * 1000)
#घोषणा DBGP_LOOPS		1000

अटल अंतरभूत u32 dbgp_pid_ग_लिखो_update(u32 x, u32 tok)
अणु
	अटल पूर्णांक data0 = USB_PID_DATA1;
	data0 ^= USB_PID_DATA_TOGGLE;
	वापस (x & 0xffff0000) | (data0 << 8) | (tok & 0xff);
पूर्ण

अटल अंतरभूत u32 dbgp_pid_पढ़ो_update(u32 x, u32 tok)
अणु
	वापस (x & 0xffff0000) | (USB_PID_DATA0 << 8) | (tok & 0xff);
पूर्ण

अटल पूर्णांक dbgp_रुको_until_complete(व्योम)
अणु
	u32 ctrl;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout_atomic(&ehci_debug->control, ctrl,
				(ctrl & DBGP_DONE), 1, DBGP_TIMEOUT);
	अगर (ret)
		वापस -DBGP_TIMEOUT;

	/*
	 * Now that we have observed the completed transaction,
	 * clear the करोne bit.
	 */
	ग_लिखोl(ctrl | DBGP_DONE, &ehci_debug->control);
	वापस (ctrl & DBGP_ERROR) ? -DBGP_ERRCODE(ctrl) : DBGP_LEN(ctrl);
पूर्ण

अटल अंतरभूत व्योम dbgp_mdelay(पूर्णांक ms)
अणु
	पूर्णांक i;

	जबतक (ms--) अणु
		क्रम (i = 0; i < 1000; i++)
			outb(0x1, 0x80);
	पूर्ण
पूर्ण

अटल व्योम dbgp_breath(व्योम)
अणु
	/* Sleep to give the debug port a chance to breathe */
पूर्ण

अटल पूर्णांक dbgp_रुको_until_करोne(अचिन्हित ctrl, पूर्णांक loop)
अणु
	u32 pids, lpid;
	पूर्णांक ret;

retry:
	ग_लिखोl(ctrl | DBGP_GO, &ehci_debug->control);
	ret = dbgp_रुको_until_complete();
	pids = पढ़ोl(&ehci_debug->pids);
	lpid = DBGP_PID_GET(pids);

	अगर (ret < 0) अणु
		/* A -DBGP_TIMEOUT failure here means the device has
		 * failed, perhaps because it was unplugged, in which
		 * हाल we करो not want to hang the प्रणाली so the dbgp
		 * will be marked as unsafe to use.  EHCI reset is the
		 * only way to recover अगर you unplug the dbgp device.
		 */
		अगर (ret == -DBGP_TIMEOUT && !dbgp_not_safe)
			dbgp_not_safe = 1;
		अगर (ret == -DBGP_ERR_BAD && --loop > 0)
			जाओ retry;
		वापस ret;
	पूर्ण

	/*
	 * If the port is getting full or it has dropped data
	 * start pacing ourselves, not necessary but it's मित्रly.
	 */
	अगर ((lpid == USB_PID_NAK) || (lpid == USB_PID_NYET))
		dbgp_breath();

	/* If I get a NACK reissue the transmission */
	अगर (lpid == USB_PID_NAK) अणु
		अगर (--loop > 0)
			जाओ retry;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम dbgp_set_data(स्थिर व्योम *buf, पूर्णांक size)
अणु
	स्थिर अचिन्हित अक्षर *bytes = buf;
	u32 lo, hi;
	पूर्णांक i;

	lo = hi = 0;
	क्रम (i = 0; i < 4 && i < size; i++)
		lo |= bytes[i] << (8*i);
	क्रम (; i < 8 && i < size; i++)
		hi |= bytes[i] << (8*(i - 4));
	ग_लिखोl(lo, &ehci_debug->data03);
	ग_लिखोl(hi, &ehci_debug->data47);
पूर्ण

अटल अंतरभूत व्योम dbgp_get_data(व्योम *buf, पूर्णांक size)
अणु
	अचिन्हित अक्षर *bytes = buf;
	u32 lo, hi;
	पूर्णांक i;

	lo = पढ़ोl(&ehci_debug->data03);
	hi = पढ़ोl(&ehci_debug->data47);
	क्रम (i = 0; i < 4 && i < size; i++)
		bytes[i] = (lo >> (8*i)) & 0xff;
	क्रम (; i < 8 && i < size; i++)
		bytes[i] = (hi >> (8*(i - 4))) & 0xff;
पूर्ण

अटल पूर्णांक dbgp_bulk_ग_लिखो(अचिन्हित devnum, अचिन्हित endpoपूर्णांक,
			 स्थिर अक्षर *bytes, पूर्णांक size)
अणु
	पूर्णांक ret;
	u32 addr;
	u32 pids, ctrl;

	अगर (size > DBGP_MAX_PACKET)
		वापस -1;

	addr = DBGP_EPADDR(devnum, endpoपूर्णांक);

	pids = पढ़ोl(&ehci_debug->pids);
	pids = dbgp_pid_ग_लिखो_update(pids, USB_PID_OUT);

	ctrl = पढ़ोl(&ehci_debug->control);
	ctrl = dbgp_len_update(ctrl, size);
	ctrl |= DBGP_OUT;
	ctrl |= DBGP_GO;

	dbgp_set_data(bytes, size);
	ग_लिखोl(addr, &ehci_debug->address);
	ग_लिखोl(pids, &ehci_debug->pids);
	ret = dbgp_रुको_until_करोne(ctrl, DBGP_LOOPS);

	वापस ret;
पूर्ण

अटल पूर्णांक dbgp_bulk_पढ़ो(अचिन्हित devnum, अचिन्हित endpoपूर्णांक, व्योम *data,
			  पूर्णांक size, पूर्णांक loops)
अणु
	u32 pids, addr, ctrl;
	पूर्णांक ret;

	अगर (size > DBGP_MAX_PACKET)
		वापस -1;

	addr = DBGP_EPADDR(devnum, endpoपूर्णांक);

	pids = पढ़ोl(&ehci_debug->pids);
	pids = dbgp_pid_पढ़ो_update(pids, USB_PID_IN);

	ctrl = पढ़ोl(&ehci_debug->control);
	ctrl = dbgp_len_update(ctrl, size);
	ctrl &= ~DBGP_OUT;
	ctrl |= DBGP_GO;

	ग_लिखोl(addr, &ehci_debug->address);
	ग_लिखोl(pids, &ehci_debug->pids);
	ret = dbgp_रुको_until_करोne(ctrl, loops);
	अगर (ret < 0)
		वापस ret;

	अगर (size > ret)
		size = ret;
	dbgp_get_data(data, size);
	वापस ret;
पूर्ण

अटल पूर्णांक dbgp_control_msg(अचिन्हित devnum, पूर्णांक requesttype,
	पूर्णांक request, पूर्णांक value, पूर्णांक index, व्योम *data, पूर्णांक size)
अणु
	u32 pids, addr, ctrl;
	काष्ठा usb_ctrlrequest req;
	पूर्णांक पढ़ो;
	पूर्णांक ret;

	पढ़ो = (requesttype & USB_सूची_IN) != 0;
	अगर (size > (पढ़ो ? DBGP_MAX_PACKET : 0))
		वापस -1;

	/* Compute the control message */
	req.bRequestType = requesttype;
	req.bRequest = request;
	req.wValue = cpu_to_le16(value);
	req.wIndex = cpu_to_le16(index);
	req.wLength = cpu_to_le16(size);

	pids = DBGP_PID_SET(USB_PID_DATA0, USB_PID_SETUP);
	addr = DBGP_EPADDR(devnum, 0);

	ctrl = पढ़ोl(&ehci_debug->control);
	ctrl = dbgp_len_update(ctrl, माप(req));
	ctrl |= DBGP_OUT;
	ctrl |= DBGP_GO;

	/* Send the setup message */
	dbgp_set_data(&req, माप(req));
	ग_लिखोl(addr, &ehci_debug->address);
	ग_लिखोl(pids, &ehci_debug->pids);
	ret = dbgp_रुको_until_करोne(ctrl, DBGP_LOOPS);
	अगर (ret < 0)
		वापस ret;

	/* Read the result */
	वापस dbgp_bulk_पढ़ो(devnum, 0, data, size, DBGP_LOOPS);
पूर्ण

/* Find a PCI capability */
अटल u32 __init find_cap(u32 num, u32 slot, u32 func, पूर्णांक cap)
अणु
	u8 pos;
	पूर्णांक bytes;

	अगर (!(पढ़ो_pci_config_16(num, slot, func, PCI_STATUS) &
		PCI_STATUS_CAP_LIST))
		वापस 0;

	pos = पढ़ो_pci_config_byte(num, slot, func, PCI_CAPABILITY_LIST);
	क्रम (bytes = 0; bytes < 48 && pos >= 0x40; bytes++) अणु
		u8 id;

		pos &= ~3;
		id = पढ़ो_pci_config_byte(num, slot, func, pos+PCI_CAP_LIST_ID);
		अगर (id == 0xff)
			अवरोध;
		अगर (id == cap)
			वापस pos;

		pos = पढ़ो_pci_config_byte(num, slot, func,
						 pos+PCI_CAP_LIST_NEXT);
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 __init __find_dbgp(u32 bus, u32 slot, u32 func)
अणु
	u32 class;

	class = पढ़ो_pci_config(bus, slot, func, PCI_CLASS_REVISION);
	अगर ((class >> 8) != PCI_CLASS_SERIAL_USB_EHCI)
		वापस 0;

	वापस find_cap(bus, slot, func, PCI_CAP_ID_EHCI_DEBUG);
पूर्ण

अटल u32 __init find_dbgp(पूर्णांक ehci_num, u32 *rbus, u32 *rslot, u32 *rfunc)
अणु
	u32 bus, slot, func;

	क्रम (bus = 0; bus < 256; bus++) अणु
		क्रम (slot = 0; slot < 32; slot++) अणु
			क्रम (func = 0; func < 8; func++) अणु
				अचिन्हित cap;

				cap = __find_dbgp(bus, slot, func);

				अगर (!cap)
					जारी;
				अगर (ehci_num-- != 0)
					जारी;
				*rbus = bus;
				*rslot = slot;
				*rfunc = func;
				वापस cap;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dbgp_ehci_startup(व्योम)
अणु
	u32 ctrl, cmd, status;
	पूर्णांक loop;

	/* Claim ownership, but करो not enable yet */
	ctrl = पढ़ोl(&ehci_debug->control);
	ctrl |= DBGP_OWNER;
	ctrl &= ~(DBGP_ENABLED | DBGP_INUSE);
	ग_लिखोl(ctrl, &ehci_debug->control);
	udelay(1);

	dbgp_ehci_status("EHCI startup");
	/* Start the ehci running */
	cmd = पढ़ोl(&ehci_regs->command);
	cmd &= ~(CMD_LRESET | CMD_IAAD | CMD_PSE | CMD_ASE | CMD_RESET);
	cmd |= CMD_RUN;
	ग_लिखोl(cmd, &ehci_regs->command);

	/* Ensure everything is routed to the EHCI */
	ग_लिखोl(FLAG_CF, &ehci_regs->configured_flag);

	/* Wait until the controller is no दीर्घer halted */
	loop = 1000;
	करो अणु
		status = पढ़ोl(&ehci_regs->status);
		अगर (!(status & STS_HALT))
			अवरोध;
		udelay(1);
	पूर्ण जबतक (--loop > 0);

	अगर (!loop) अणु
		dbgp_prपूर्णांकk("ehci can not be started\n");
		वापस -ENODEV;
	पूर्ण
	dbgp_prपूर्णांकk("ehci started\n");
	वापस 0;
पूर्ण

अटल पूर्णांक dbgp_ehci_controller_reset(व्योम)
अणु
	पूर्णांक loop = 250 * 1000;
	u32 cmd;

	/* Reset the EHCI controller */
	cmd = पढ़ोl(&ehci_regs->command);
	cmd |= CMD_RESET;
	ग_लिखोl(cmd, &ehci_regs->command);
	करो अणु
		cmd = पढ़ोl(&ehci_regs->command);
	पूर्ण जबतक ((cmd & CMD_RESET) && (--loop > 0));

	अगर (!loop) अणु
		dbgp_prपूर्णांकk("can not reset ehci\n");
		वापस -1;
	पूर्ण
	dbgp_ehci_status("ehci reset done");
	वापस 0;
पूर्ण
अटल पूर्णांक ehci_रुको_क्रम_port(पूर्णांक port);
/* Return 0 on success
 * Return -ENODEV क्रम any general failure
 * Return -EIO अगर रुको क्रम port fails
 */
अटल पूर्णांक _dbgp_बाह्यal_startup(व्योम)
अणु
	पूर्णांक devnum;
	काष्ठा usb_debug_descriptor dbgp_desc;
	पूर्णांक ret;
	u32 ctrl, portsc, cmd;
	पूर्णांक dbg_port = dbgp_phys_port;
	पूर्णांक tries = 3;
	पूर्णांक reset_port_tries = 1;
	पूर्णांक try_hard_once = 1;

try_port_reset_again:
	ret = dbgp_ehci_startup();
	अगर (ret)
		वापस ret;

	/* Wait क्रम a device to show up in the debug port */
	ret = ehci_रुको_क्रम_port(dbg_port);
	अगर (ret < 0) अणु
		portsc = पढ़ोl(&ehci_regs->port_status[dbg_port - 1]);
		अगर (!(portsc & PORT_CONNECT) && try_hard_once) अणु
			/* Last ditch efक्रमt to try to क्रमce enable
			 * the debug device by using the packet test
			 * ehci command to try and wake it up. */
			try_hard_once = 0;
			cmd = पढ़ोl(&ehci_regs->command);
			cmd &= ~CMD_RUN;
			ग_लिखोl(cmd, &ehci_regs->command);
			portsc = पढ़ोl(&ehci_regs->port_status[dbg_port - 1]);
			portsc |= PORT_TEST_PKT;
			ग_लिखोl(portsc, &ehci_regs->port_status[dbg_port - 1]);
			dbgp_ehci_status("Trying to force debug port online");
			mdelay(50);
			dbgp_ehci_controller_reset();
			जाओ try_port_reset_again;
		पूर्ण अन्यथा अगर (reset_port_tries--) अणु
			जाओ try_port_reset_again;
		पूर्ण
		dbgp_prपूर्णांकk("No device found in debug port\n");
		वापस -EIO;
	पूर्ण
	dbgp_ehci_status("wait for port done");

	/* Enable the debug port */
	ctrl = पढ़ोl(&ehci_debug->control);
	ctrl |= DBGP_CLAIM;
	ग_लिखोl(ctrl, &ehci_debug->control);
	ctrl = पढ़ोl(&ehci_debug->control);
	अगर ((ctrl & DBGP_CLAIM) != DBGP_CLAIM) अणु
		dbgp_prपूर्णांकk("No device in debug port\n");
		ग_लिखोl(ctrl & ~DBGP_CLAIM, &ehci_debug->control);
		वापस -ENODEV;
	पूर्ण
	dbgp_ehci_status("debug ported enabled");

	/* Completely transfer the debug device to the debug controller */
	portsc = पढ़ोl(&ehci_regs->port_status[dbg_port - 1]);
	portsc &= ~PORT_PE;
	ग_लिखोl(portsc, &ehci_regs->port_status[dbg_port - 1]);

	dbgp_mdelay(100);

try_again:
	/* Find the debug device and make it device number 127 */
	क्रम (devnum = 0; devnum <= 127; devnum++) अणु
		ret = dbgp_control_msg(devnum,
			USB_सूची_IN | USB_TYPE_STANDARD | USB_RECIP_DEVICE,
			USB_REQ_GET_DESCRIPTOR, (USB_DT_DEBUG << 8), 0,
			&dbgp_desc, माप(dbgp_desc));
		अगर (ret > 0)
			अवरोध;
	पूर्ण
	अगर (devnum > 127) अणु
		dbgp_prपूर्णांकk("Could not find attached debug device\n");
		जाओ err;
	पूर्ण
	dbgp_endpoपूर्णांक_out = dbgp_desc.bDebugOutEndpoपूर्णांक;
	dbgp_endpoपूर्णांक_in = dbgp_desc.bDebugInEndpoपूर्णांक;

	/* Move the device to 127 अगर it isn't alपढ़ोy there */
	अगर (devnum != USB_DEBUG_DEVNUM) अणु
		ret = dbgp_control_msg(devnum,
			USB_सूची_OUT | USB_TYPE_STANDARD | USB_RECIP_DEVICE,
			USB_REQ_SET_ADDRESS, USB_DEBUG_DEVNUM, 0, शून्य, 0);
		अगर (ret < 0) अणु
			dbgp_prपूर्णांकk("Could not move attached device to %d\n",
				USB_DEBUG_DEVNUM);
			जाओ err;
		पूर्ण
		dbgp_prपूर्णांकk("debug device renamed to 127\n");
	पूर्ण

	/* Enable the debug पूर्णांकerface */
	ret = dbgp_control_msg(USB_DEBUG_DEVNUM,
		USB_सूची_OUT | USB_TYPE_STANDARD | USB_RECIP_DEVICE,
		USB_REQ_SET_FEATURE, USB_DEVICE_DEBUG_MODE, 0, शून्य, 0);
	अगर (ret < 0) अणु
		dbgp_prपूर्णांकk(" Could not enable the debug device\n");
		जाओ err;
	पूर्ण
	dbgp_prपूर्णांकk("debug interface enabled\n");
	/* Perक्रमm a small ग_लिखो to get the even/odd data state in sync
	 */
	ret = dbgp_bulk_ग_लिखो(USB_DEBUG_DEVNUM, dbgp_endpoपूर्णांक_out, " ", 1);
	अगर (ret < 0) अणु
		dbgp_prपूर्णांकk("dbgp_bulk_write failed: %d\n", ret);
		जाओ err;
	पूर्ण
	dbgp_prपूर्णांकk("small write done\n");
	dbgp_not_safe = 0;

	वापस 0;
err:
	अगर (tries--)
		जाओ try_again;
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक ehci_reset_port(पूर्णांक port)
अणु
	u32 portsc;
	u32 delay_समय, delay;
	पूर्णांक loop;

	dbgp_ehci_status("reset port");
	/* Reset the usb debug port */
	portsc = पढ़ोl(&ehci_regs->port_status[port - 1]);
	portsc &= ~PORT_PE;
	portsc |= PORT_RESET;
	ग_लिखोl(portsc, &ehci_regs->port_status[port - 1]);

	delay = HUB_ROOT_RESET_TIME;
	क्रम (delay_समय = 0; delay_समय < HUB_RESET_TIMEOUT;
	     delay_समय += delay) अणु
		dbgp_mdelay(delay);
		portsc = पढ़ोl(&ehci_regs->port_status[port - 1]);
		अगर (!(portsc & PORT_RESET))
			अवरोध;
	पूर्ण
	अगर (portsc & PORT_RESET) अणु
		/* क्रमce reset to complete */
		loop = 100 * 1000;
		ग_लिखोl(portsc & ~(PORT_RWC_BITS | PORT_RESET),
			&ehci_regs->port_status[port - 1]);
		करो अणु
			udelay(1);
			portsc = पढ़ोl(&ehci_regs->port_status[port-1]);
		पूर्ण जबतक ((portsc & PORT_RESET) && (--loop > 0));
	पूर्ण

	/* Device went away? */
	अगर (!(portsc & PORT_CONNECT))
		वापस -ENOTCONN;

	/* bomb out completely अगर something weird happened */
	अगर ((portsc & PORT_CSC))
		वापस -EINVAL;

	/* If we've finished resetting, then अवरोध out of the loop */
	अगर (!(portsc & PORT_RESET) && (portsc & PORT_PE))
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक ehci_रुको_क्रम_port(पूर्णांक port)
अणु
	u32 status;
	पूर्णांक ret, reps;

	क्रम (reps = 0; reps < 300; reps++) अणु
		status = पढ़ोl(&ehci_regs->status);
		अगर (status & STS_PCD)
			अवरोध;
		dbgp_mdelay(1);
	पूर्ण
	ret = ehci_reset_port(port);
	अगर (ret == 0)
		वापस 0;
	वापस -ENOTCONN;
पूर्ण

प्रकार व्योम (*set_debug_port_t)(पूर्णांक port);

अटल व्योम __init शेष_set_debug_port(पूर्णांक port)
अणु
पूर्ण

अटल set_debug_port_t __initdata set_debug_port = शेष_set_debug_port;

अटल व्योम __init nvidia_set_debug_port(पूर्णांक port)
अणु
	u32 dword;
	dword = पढ़ो_pci_config(ehci_dev.bus, ehci_dev.slot, ehci_dev.func,
				 0x74);
	dword &= ~(0x0f<<12);
	dword |= ((port & 0x0f)<<12);
	ग_लिखो_pci_config(ehci_dev.bus, ehci_dev.slot, ehci_dev.func, 0x74,
				 dword);
	dbgp_prपूर्णांकk("set debug port to %d\n", port);
पूर्ण

अटल व्योम __init detect_set_debug_port(व्योम)
अणु
	u32 venकरोrid;

	venकरोrid = पढ़ो_pci_config(ehci_dev.bus, ehci_dev.slot, ehci_dev.func,
		 0x00);

	अगर ((venकरोrid & 0xffff) == 0x10de) अणु
		dbgp_prपूर्णांकk("using nvidia set_debug_port\n");
		set_debug_port = nvidia_set_debug_port;
	पूर्ण
पूर्ण

/* The code in early_ehci_bios_hanकरोff() is derived from the usb pci
 * quirk initialization, but altered so as to use the early PCI
 * routines. */
#घोषणा EHCI_USBLEGSUP_BIOS	(1 << 16)	/* BIOS semaphore */
#घोषणा EHCI_USBLEGCTLSTS	4		/* legacy control/status */
अटल व्योम __init early_ehci_bios_hanकरोff(व्योम)
अणु
	u32 hcc_params = पढ़ोl(&ehci_caps->hcc_params);
	पूर्णांक offset = (hcc_params >> 8) & 0xff;
	u32 cap;
	पूर्णांक msec;

	अगर (!offset)
		वापस;

	cap = पढ़ो_pci_config(ehci_dev.bus, ehci_dev.slot,
			      ehci_dev.func, offset);
	dbgp_prपूर्णांकk("dbgp: ehci BIOS state %08x\n", cap);

	अगर ((cap & 0xff) == 1 && (cap & EHCI_USBLEGSUP_BIOS)) अणु
		dbgp_prपूर्णांकk("dbgp: BIOS handoff\n");
		ग_लिखो_pci_config_byte(ehci_dev.bus, ehci_dev.slot,
				      ehci_dev.func, offset + 3, 1);
	पूर्ण

	/* अगर boot firmware now owns EHCI, spin till it hands it over. */
	msec = 1000;
	जबतक ((cap & EHCI_USBLEGSUP_BIOS) && (msec > 0)) अणु
		mdelay(10);
		msec -= 10;
		cap = पढ़ो_pci_config(ehci_dev.bus, ehci_dev.slot,
				      ehci_dev.func, offset);
	पूर्ण

	अगर (cap & EHCI_USBLEGSUP_BIOS) अणु
		/* well, possibly buggy BIOS... try to shut it करोwn,
		 * and hope nothing goes too wrong */
		dbgp_prपूर्णांकk("dbgp: BIOS handoff failed: %08x\n", cap);
		ग_लिखो_pci_config_byte(ehci_dev.bus, ehci_dev.slot,
				      ehci_dev.func, offset + 2, 0);
	पूर्ण

	/* just in हाल, always disable EHCI SMIs */
	ग_लिखो_pci_config_byte(ehci_dev.bus, ehci_dev.slot, ehci_dev.func,
			      offset + EHCI_USBLEGCTLSTS, 0);
पूर्ण

अटल पूर्णांक __init ehci_setup(व्योम)
अणु
	u32 ctrl, portsc, hcs_params;
	u32 debug_port, new_debug_port = 0, n_ports;
	पूर्णांक ret, i;
	पूर्णांक port_map_tried;
	पूर्णांक playबार = 3;

	early_ehci_bios_hanकरोff();

try_next_समय:
	port_map_tried = 0;

try_next_port:

	hcs_params = पढ़ोl(&ehci_caps->hcs_params);
	debug_port = HCS_DEBUG_PORT(hcs_params);
	dbgp_phys_port = debug_port;
	n_ports    = HCS_N_PORTS(hcs_params);

	dbgp_prपूर्णांकk("debug_port: %d\n", debug_port);
	dbgp_prपूर्णांकk("n_ports:    %d\n", n_ports);
	dbgp_ehci_status("");

	क्रम (i = 1; i <= n_ports; i++) अणु
		portsc = पढ़ोl(&ehci_regs->port_status[i-1]);
		dbgp_prपूर्णांकk("portstatus%d: %08x\n", i, portsc);
	पूर्ण

	अगर (port_map_tried && (new_debug_port != debug_port)) अणु
		अगर (--playबार) अणु
			set_debug_port(new_debug_port);
			जाओ try_next_समय;
		पूर्ण
		वापस -1;
	पूर्ण

	/* Only reset the controller अगर it is not alपढ़ोy in the
	 * configured state */
	अगर (!(पढ़ोl(&ehci_regs->configured_flag) & FLAG_CF)) अणु
		अगर (dbgp_ehci_controller_reset() != 0)
			वापस -1;
	पूर्ण अन्यथा अणु
		dbgp_ehci_status("ehci skip - already configured");
	पूर्ण

	ret = _dbgp_बाह्यal_startup();
	अगर (ret == -EIO)
		जाओ next_debug_port;

	अगर (ret < 0) अणु
		/* Things didn't work so हटाओ my claim */
		ctrl = पढ़ोl(&ehci_debug->control);
		ctrl &= ~(DBGP_CLAIM | DBGP_OUT);
		ग_लिखोl(ctrl, &ehci_debug->control);
		वापस -1;
	पूर्ण
	वापस 0;

next_debug_port:
	port_map_tried |= (1<<(debug_port - 1));
	new_debug_port = ((debug_port-1+1)%n_ports) + 1;
	अगर (port_map_tried != ((1<<n_ports) - 1)) अणु
		set_debug_port(new_debug_port);
		जाओ try_next_port;
	पूर्ण
	अगर (--playबार) अणु
		set_debug_port(new_debug_port);
		जाओ try_next_समय;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक __init early_dbgp_init(अक्षर *s)
अणु
	u32 debug_port, bar, offset;
	u32 bus, slot, func, cap;
	व्योम __iomem *ehci_bar;
	u32 dbgp_num;
	u32 bar_val;
	अक्षर *e;
	पूर्णांक ret;
	u8 byte;

	अगर (!early_pci_allowed())
		वापस -1;

	dbgp_num = 0;
	अगर (*s)
		dbgp_num = simple_म_से_अदीर्घ(s, &e, 10);
	dbgp_prपूर्णांकk("dbgp_num: %d\n", dbgp_num);

	cap = find_dbgp(dbgp_num, &bus, &slot, &func);
	अगर (!cap)
		वापस -1;

	dbgp_prपूर्णांकk("Found EHCI debug port on %02x:%02x.%1x\n", bus, slot,
			 func);

	debug_port = पढ़ो_pci_config(bus, slot, func, cap);
	bar = (debug_port >> 29) & 0x7;
	bar = (bar * 4) + 0xc;
	offset = (debug_port >> 16) & 0xfff;
	dbgp_prपूर्णांकk("bar: %02x offset: %03x\n", bar, offset);
	अगर (bar != PCI_BASE_ADDRESS_0) अणु
		dbgp_prपूर्णांकk("only debug ports on bar 1 handled.\n");

		वापस -1;
	पूर्ण

	bar_val = पढ़ो_pci_config(bus, slot, func, PCI_BASE_ADDRESS_0);
	dbgp_prपूर्णांकk("bar_val: %02x offset: %03x\n", bar_val, offset);
	अगर (bar_val & ~PCI_BASE_ADDRESS_MEM_MASK) अणु
		dbgp_prपूर्णांकk("only simple 32bit mmio bars supported\n");

		वापस -1;
	पूर्ण

	/* द्विगुन check अगर the mem space is enabled */
	byte = पढ़ो_pci_config_byte(bus, slot, func, 0x04);
	अगर (!(byte & 0x2)) अणु
		byte  |= 0x02;
		ग_लिखो_pci_config_byte(bus, slot, func, 0x04, byte);
		dbgp_prपूर्णांकk("mmio for ehci enabled\n");
	पूर्ण

	/*
	 * FIXME I करोn't have the bar size so just guess PAGE_SIZE is more
	 * than enough.  1K is the biggest I have seen.
	 */
	set_fixmap_nocache(FIX_DBGP_BASE, bar_val & PAGE_MASK);
	ehci_bar = (व्योम __iomem *)__fix_to_virt(FIX_DBGP_BASE);
	ehci_bar += bar_val & ~PAGE_MASK;
	dbgp_prपूर्णांकk("ehci_bar: %p\n", ehci_bar);

	ehci_caps  = ehci_bar;
	ehci_regs  = ehci_bar + EARLY_HC_LENGTH(पढ़ोl(&ehci_caps->hc_capbase));
	ehci_debug = ehci_bar + offset;
	ehci_dev.bus = bus;
	ehci_dev.slot = slot;
	ehci_dev.func = func;

	detect_set_debug_port();

	ret = ehci_setup();
	अगर (ret < 0) अणु
		dbgp_prपूर्णांकk("ehci_setup failed\n");
		ehci_debug = शून्य;

		वापस -1;
	पूर्ण
	dbgp_ehci_status("early_init_complete");

	वापस 0;
पूर्ण

अटल व्योम early_dbgp_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *str, u32 n)
अणु
	पूर्णांक chunk;
	अक्षर buf[DBGP_MAX_PACKET];
	पूर्णांक use_cr = 0;
	u32 cmd, ctrl;
	पूर्णांक reset_run = 0;

	अगर (!ehci_debug || dbgp_not_safe)
		वापस;

	cmd = पढ़ोl(&ehci_regs->command);
	अगर (unlikely(!(cmd & CMD_RUN))) अणु
		/* If the ehci controller is not in the run state करो extended
		 * checks to see अगर the acpi or some other initialization also
		 * reset the ehci debug port */
		ctrl = पढ़ोl(&ehci_debug->control);
		अगर (!(ctrl & DBGP_ENABLED)) अणु
			dbgp_not_safe = 1;
			_dbgp_बाह्यal_startup();
		पूर्ण अन्यथा अणु
			cmd |= CMD_RUN;
			ग_लिखोl(cmd, &ehci_regs->command);
			reset_run = 1;
		पूर्ण
	पूर्ण
	जबतक (n > 0) अणु
		क्रम (chunk = 0; chunk < DBGP_MAX_PACKET && n > 0;
		     str++, chunk++, n--) अणु
			अगर (!use_cr && *str == '\n') अणु
				use_cr = 1;
				buf[chunk] = '\r';
				str--;
				n++;
				जारी;
			पूर्ण
			अगर (use_cr)
				use_cr = 0;
			buf[chunk] = *str;
		पूर्ण
		अगर (chunk > 0) अणु
			dbgp_bulk_ग_लिखो(USB_DEBUG_DEVNUM,
					dbgp_endpoपूर्णांक_out, buf, chunk);
		पूर्ण
	पूर्ण
	अगर (unlikely(reset_run)) अणु
		cmd = पढ़ोl(&ehci_regs->command);
		cmd &= ~CMD_RUN;
		ग_लिखोl(cmd, &ehci_regs->command);
	पूर्ण
पूर्ण

काष्ठा console early_dbgp_console = अणु
	.name =		"earlydbg",
	.ग_लिखो =	early_dbgp_ग_लिखो,
	.flags =	CON_PRINTBUFFER,
	.index =	-1,
पूर्ण;

#अगर IS_ENABLED(CONFIG_USB)
पूर्णांक dbgp_reset_prep(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक ret = xen_dbgp_reset_prep(hcd);
	u32 ctrl;

	अगर (ret)
		वापस ret;

	dbgp_not_safe = 1;
	अगर (!ehci_debug)
		वापस 0;

	अगर ((early_dbgp_console.index != -1 &&
	     !(early_dbgp_console.flags & CON_BOOT)) ||
	    dbgp_kgdb_mode)
		वापस 1;
	/* This means the console is not initialized, or should get
	 * shutकरोwn so as to allow क्रम reuse of the usb device, which
	 * means it is समय to shutकरोwn the usb debug port. */
	ctrl = पढ़ोl(&ehci_debug->control);
	अगर (ctrl & DBGP_ENABLED) अणु
		ctrl &= ~(DBGP_CLAIM);
		ग_लिखोl(ctrl, &ehci_debug->control);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dbgp_reset_prep);

पूर्णांक dbgp_बाह्यal_startup(काष्ठा usb_hcd *hcd)
अणु
	वापस xen_dbgp_बाह्यal_startup(hcd) ?: _dbgp_बाह्यal_startup();
पूर्ण
EXPORT_SYMBOL_GPL(dbgp_बाह्यal_startup);
#पूर्ण_अगर /* USB */

#अगर_घोषित CONFIG_KGDB

अटल अक्षर kgdbdbgp_buf[DBGP_MAX_PACKET];
अटल पूर्णांक kgdbdbgp_buf_sz;
अटल पूर्णांक kgdbdbgp_buf_idx;
अटल पूर्णांक kgdbdbgp_loop_cnt = DBGP_LOOPS;

अटल पूर्णांक kgdbdbgp_पढ़ो_अक्षर(व्योम)
अणु
	पूर्णांक ret;

	अगर (kgdbdbgp_buf_idx < kgdbdbgp_buf_sz) अणु
		अक्षर ch = kgdbdbgp_buf[kgdbdbgp_buf_idx++];
		वापस ch;
	पूर्ण

	ret = dbgp_bulk_पढ़ो(USB_DEBUG_DEVNUM, dbgp_endpoपूर्णांक_in,
			     &kgdbdbgp_buf, DBGP_MAX_PACKET,
			     kgdbdbgp_loop_cnt);
	अगर (ret <= 0)
		वापस NO_POLL_CHAR;
	kgdbdbgp_buf_sz = ret;
	kgdbdbgp_buf_idx = 1;
	वापस kgdbdbgp_buf[0];
पूर्ण

अटल व्योम kgdbdbgp_ग_लिखो_अक्षर(u8 chr)
अणु
	early_dbgp_ग_लिखो(शून्य, &chr, 1);
पूर्ण

अटल काष्ठा kgdb_io kgdbdbgp_io_ops = अणु
	.name = "kgdbdbgp",
	.पढ़ो_अक्षर = kgdbdbgp_पढ़ो_अक्षर,
	.ग_लिखो_अक्षर = kgdbdbgp_ग_लिखो_अक्षर,
पूर्ण;

अटल पूर्णांक kgdbdbgp_रुको_समय;

अटल पूर्णांक __init kgdbdbgp_parse_config(अक्षर *str)
अणु
	अक्षर *ptr;

	अगर (!ehci_debug) अणु
		अगर (early_dbgp_init(str))
			वापस -1;
	पूर्ण
	ptr = म_अक्षर(str, ',');
	अगर (ptr) अणु
		ptr++;
		kgdbdbgp_रुको_समय = simple_म_से_अदीर्घ(ptr, &ptr, 10);
	पूर्ण
	kgdb_रेजिस्टर_io_module(&kgdbdbgp_io_ops);
	अगर (early_dbgp_console.index != -1)
		kgdbdbgp_io_ops.cons = &early_dbgp_console;

	वापस 0;
पूर्ण
early_param("kgdbdbgp", kgdbdbgp_parse_config);

अटल पूर्णांक kgdbdbgp_पढ़ोer_thपढ़ो(व्योम *ptr)
अणु
	पूर्णांक ret;

	जबतक (पढ़ोl(&ehci_debug->control) & DBGP_ENABLED) अणु
		kgdbdbgp_loop_cnt = 1;
		ret = kgdbdbgp_पढ़ो_अक्षर();
		kgdbdbgp_loop_cnt = DBGP_LOOPS;
		अगर (ret != NO_POLL_CHAR) अणु
			अगर (ret == 0x3 || ret == '$') अणु
				अगर (ret == '$')
					kgdbdbgp_buf_idx--;
				kgdb_अवरोधpoपूर्णांक();
			पूर्ण
			जारी;
		पूर्ण
		schedule_समयout_पूर्णांकerruptible(kgdbdbgp_रुको_समय * HZ);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init kgdbdbgp_start_thपढ़ो(व्योम)
अणु
	अगर (dbgp_kgdb_mode && kgdbdbgp_रुको_समय)
		kthपढ़ो_run(kgdbdbgp_पढ़ोer_thपढ़ो, शून्य, "%s", "dbgp");

	वापस 0;
पूर्ण
device_initcall(kgdbdbgp_start_thपढ़ो);
#पूर्ण_अगर /* CONFIG_KGDB */
