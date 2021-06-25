<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*****************************************************************************/
/*
 *           moxa.c  -- MOXA Intellio family multiport serial driver.
 *
 *      Copyright (C) 1999-2000  Moxa Technologies (support@moxa.com).
 *      Copyright (c) 2007 Jiri Slaby <jirislaby@gmail.com>
 *
 *      This code is loosely based on the Linux serial driver, written by
 *      Linus Torvalds, Theoकरोre T'so and others.
 */

/*
 *    MOXA Intellio Series Driver
 *      क्रम             : LINUX
 *      date            : 1999/1/7
 *      version         : 5.1
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/ioport.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firmware.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/major.h>
#समावेश <linux/माला.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/ratelimit.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#समावेश "moxa.h"

#घोषणा MOXA_VERSION		"6.0k"

#घोषणा MOXA_FW_HDRLEN		32

#घोषणा MOXAMAJOR		172

#घोषणा MAX_BOARDS		4	/* Don't change this value */
#घोषणा MAX_PORTS_PER_BOARD	32	/* Don't change this value */
#घोषणा MAX_PORTS		(MAX_BOARDS * MAX_PORTS_PER_BOARD)

#घोषणा MOXA_IS_320(brd) ((brd)->boardType == MOXA_BOARD_C320_ISA || \
		(brd)->boardType == MOXA_BOARD_C320_PCI)

/*
 *    Define the Moxa PCI venकरोr and device IDs.
 */
#घोषणा MOXA_BUS_TYPE_ISA	0
#घोषणा MOXA_BUS_TYPE_PCI	1

क्रमागत अणु
	MOXA_BOARD_C218_PCI = 1,
	MOXA_BOARD_C218_ISA,
	MOXA_BOARD_C320_PCI,
	MOXA_BOARD_C320_ISA,
	MOXA_BOARD_CP204J,
पूर्ण;

अटल अक्षर *moxa_brdname[] =
अणु
	"C218 Turbo PCI series",
	"C218 Turbo ISA series",
	"C320 Turbo PCI series",
	"C320 Turbo ISA series",
	"CP-204J series",
पूर्ण;

#अगर_घोषित CONFIG_PCI
अटल स्थिर काष्ठा pci_device_id moxa_pcibrds[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_C218),
		.driver_data = MOXA_BOARD_C218_PCI पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_C320),
		.driver_data = MOXA_BOARD_C320_PCI पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MOXA, PCI_DEVICE_ID_MOXA_CP204J),
		.driver_data = MOXA_BOARD_CP204J पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, moxa_pcibrds);
#पूर्ण_अगर /* CONFIG_PCI */

काष्ठा moxa_port;

अटल काष्ठा moxa_board_conf अणु
	पूर्णांक boardType;
	पूर्णांक numPorts;
	पूर्णांक busType;

	अचिन्हित पूर्णांक पढ़ोy;

	काष्ठा moxa_port *ports;

	व्योम __iomem *basemem;
	व्योम __iomem *पूर्णांकNdx;
	व्योम __iomem *पूर्णांकPend;
	व्योम __iomem *पूर्णांकTable;
पूर्ण moxa_boards[MAX_BOARDS];

काष्ठा mxser_mstatus अणु
	tcflag_t cflag;
	पूर्णांक cts;
	पूर्णांक dsr;
	पूर्णांक ri;
	पूर्णांक dcd;
पूर्ण;

काष्ठा moxaq_str अणु
	पूर्णांक inq;
	पूर्णांक outq;
पूर्ण;

काष्ठा moxa_port अणु
	काष्ठा tty_port port;
	काष्ठा moxa_board_conf *board;
	व्योम __iomem *tableAddr;

	पूर्णांक type;
	पूर्णांक cflag;
	अचिन्हित दीर्घ statusflags;

	u8 DCDState;		/* Protected by the port lock */
	u8 lineCtrl;
	u8 lowChkFlag;
पूर्ण;

काष्ठा mon_str अणु
	पूर्णांक tick;
	पूर्णांक rxcnt[MAX_PORTS];
	पूर्णांक txcnt[MAX_PORTS];
पूर्ण;

/* statusflags */
#घोषणा TXSTOPPED	1
#घोषणा LOWWAIT 	2
#घोषणा EMPTYWAIT	3


#घोषणा WAKEUP_CHARS		256

अटल पूर्णांक ttymajor = MOXAMAJOR;
अटल काष्ठा mon_str moxaLog;
अटल अचिन्हित पूर्णांक moxaFuncTout = HZ / 2;
अटल अचिन्हित पूर्णांक moxaLowWaterChk;
अटल DEFINE_MUTEX(moxa_खोलोlock);
अटल DEFINE_SPINLOCK(moxa_lock);

अटल अचिन्हित दीर्घ baseaddr[MAX_BOARDS];
अटल अचिन्हित पूर्णांक type[MAX_BOARDS];
अटल अचिन्हित पूर्णांक numports[MAX_BOARDS];
अटल काष्ठा tty_port moxa_service_port;

MODULE_AUTHOR("William Chen");
MODULE_DESCRIPTION("MOXA Intellio Family Multiport Board Device Driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("c218tunx.cod");
MODULE_FIRMWARE("cp204unx.cod");
MODULE_FIRMWARE("c320tunx.cod");

module_param_array(type, uपूर्णांक, शून्य, 0);
MODULE_PARM_DESC(type, "card type: C218=2, C320=4");
module_param_hw_array(baseaddr, uदीर्घ, ioport, शून्य, 0);
MODULE_PARM_DESC(baseaddr, "base address");
module_param_array(numports, uपूर्णांक, शून्य, 0);
MODULE_PARM_DESC(numports, "numports (ignored for C218)");

module_param(ttymajor, पूर्णांक, 0);

/*
 * अटल functions:
 */
अटल पूर्णांक moxa_खोलो(काष्ठा tty_काष्ठा *, काष्ठा file *);
अटल व्योम moxa_बंद(काष्ठा tty_काष्ठा *, काष्ठा file *);
अटल पूर्णांक moxa_ग_लिखो(काष्ठा tty_काष्ठा *, स्थिर अचिन्हित अक्षर *, पूर्णांक);
अटल पूर्णांक moxa_ग_लिखो_room(काष्ठा tty_काष्ठा *);
अटल व्योम moxa_flush_buffer(काष्ठा tty_काष्ठा *);
अटल पूर्णांक moxa_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *);
अटल व्योम moxa_set_termios(काष्ठा tty_काष्ठा *, काष्ठा ktermios *);
अटल व्योम moxa_stop(काष्ठा tty_काष्ठा *);
अटल व्योम moxa_start(काष्ठा tty_काष्ठा *);
अटल व्योम moxa_hangup(काष्ठा tty_काष्ठा *);
अटल पूर्णांक moxa_tiocmget(काष्ठा tty_काष्ठा *tty);
अटल पूर्णांक moxa_tiocmset(काष्ठा tty_काष्ठा *tty,
			 अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
अटल व्योम moxa_poll(काष्ठा समयr_list *);
अटल व्योम moxa_set_tty_param(काष्ठा tty_काष्ठा *, काष्ठा ktermios *);
अटल व्योम moxa_shutकरोwn(काष्ठा tty_port *);
अटल पूर्णांक moxa_carrier_उठाओd(काष्ठा tty_port *);
अटल व्योम moxa_dtr_rts(काष्ठा tty_port *, पूर्णांक);
/*
 * moxa board पूर्णांकerface functions:
 */
अटल व्योम MoxaPortEnable(काष्ठा moxa_port *);
अटल व्योम MoxaPortDisable(काष्ठा moxa_port *);
अटल पूर्णांक MoxaPortSetTermio(काष्ठा moxa_port *, काष्ठा ktermios *, speed_t);
अटल पूर्णांक MoxaPortGetLineOut(काष्ठा moxa_port *, पूर्णांक *, पूर्णांक *);
अटल व्योम MoxaPortLineCtrl(काष्ठा moxa_port *, पूर्णांक, पूर्णांक);
अटल व्योम MoxaPortFlowCtrl(काष्ठा moxa_port *, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक);
अटल पूर्णांक MoxaPortLineStatus(काष्ठा moxa_port *);
अटल व्योम MoxaPortFlushData(काष्ठा moxa_port *, पूर्णांक);
अटल पूर्णांक MoxaPortWriteData(काष्ठा tty_काष्ठा *, स्थिर अचिन्हित अक्षर *, पूर्णांक);
अटल पूर्णांक MoxaPortReadData(काष्ठा moxa_port *);
अटल पूर्णांक MoxaPortTxQueue(काष्ठा moxa_port *);
अटल पूर्णांक MoxaPortRxQueue(काष्ठा moxa_port *);
अटल पूर्णांक MoxaPortTxFree(काष्ठा moxa_port *);
अटल व्योम MoxaPortTxDisable(काष्ठा moxa_port *);
अटल व्योम MoxaPortTxEnable(काष्ठा moxa_port *);
अटल पूर्णांक moxa_get_serial_info(काष्ठा tty_काष्ठा *, काष्ठा serial_काष्ठा *);
अटल पूर्णांक moxa_set_serial_info(काष्ठा tty_काष्ठा *, काष्ठा serial_काष्ठा *);
अटल व्योम MoxaSetFअगरo(काष्ठा moxa_port *port, पूर्णांक enable);

/*
 * I/O functions
 */

अटल DEFINE_SPINLOCK(moxafunc_lock);

अटल व्योम moxa_रुको_finish(व्योम __iomem *ofsAddr)
अणु
	अचिन्हित दीर्घ end = jअगरfies + moxaFuncTout;

	जबतक (पढ़ोw(ofsAddr + FuncCode) != 0)
		अगर (समय_after(jअगरfies, end))
			वापस;
	अगर (पढ़ोw(ofsAddr + FuncCode) != 0)
		prपूर्णांकk_ratelimited(KERN_WARNING "moxa function expired\n");
पूर्ण

अटल व्योम moxafunc(व्योम __iomem *ofsAddr, u16 cmd, u16 arg)
अणु
        अचिन्हित दीर्घ flags;
        spin_lock_irqsave(&moxafunc_lock, flags);
	ग_लिखोw(arg, ofsAddr + FuncArg);
	ग_लिखोw(cmd, ofsAddr + FuncCode);
	moxa_रुको_finish(ofsAddr);
	spin_unlock_irqrestore(&moxafunc_lock, flags);
पूर्ण

अटल पूर्णांक moxafuncret(व्योम __iomem *ofsAddr, u16 cmd, u16 arg)
अणु
        अचिन्हित दीर्घ flags;
        u16 ret;
        spin_lock_irqsave(&moxafunc_lock, flags);
	ग_लिखोw(arg, ofsAddr + FuncArg);
	ग_लिखोw(cmd, ofsAddr + FuncCode);
	moxa_रुको_finish(ofsAddr);
	ret = पढ़ोw(ofsAddr + FuncArg);
	spin_unlock_irqrestore(&moxafunc_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम moxa_low_water_check(व्योम __iomem *ofsAddr)
अणु
	u16 rptr, wptr, mask, len;

	अगर (पढ़ोb(ofsAddr + FlagStat) & Xoff_state) अणु
		rptr = पढ़ोw(ofsAddr + RXrptr);
		wptr = पढ़ोw(ofsAddr + RXwptr);
		mask = पढ़ोw(ofsAddr + RX_mask);
		len = (wptr - rptr) & mask;
		अगर (len <= Low_water)
			moxafunc(ofsAddr, FC_SendXon, 0);
	पूर्ण
पूर्ण

/*
 * TTY operations
 */

अटल पूर्णांक moxa_ioctl(काष्ठा tty_काष्ठा *tty,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा moxa_port *ch = tty->driver_data;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक status, ret = 0;

	अगर (tty->index == MAX_PORTS) अणु
		अगर (cmd != MOXA_GETDATACOUNT && cmd != MOXA_GET_IOQUEUE &&
				cmd != MOXA_GETMSTATUS)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (!ch)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल MOXA_GETDATACOUNT:
		moxaLog.tick = jअगरfies;
		अगर (copy_to_user(argp, &moxaLog, माप(moxaLog)))
			ret = -EFAULT;
		अवरोध;
	हाल MOXA_FLUSH_QUEUE:
		MoxaPortFlushData(ch, arg);
		अवरोध;
	हाल MOXA_GET_IOQUEUE: अणु
		काष्ठा moxaq_str __user *argm = argp;
		काष्ठा moxaq_str पंचांगp;
		काष्ठा moxa_port *p;
		अचिन्हित पूर्णांक i, j;

		क्रम (i = 0; i < MAX_BOARDS; i++) अणु
			p = moxa_boards[i].ports;
			क्रम (j = 0; j < MAX_PORTS_PER_BOARD; j++, p++, argm++) अणु
				स_रखो(&पंचांगp, 0, माप(पंचांगp));
				spin_lock_bh(&moxa_lock);
				अगर (moxa_boards[i].पढ़ोy) अणु
					पंचांगp.inq = MoxaPortRxQueue(p);
					पंचांगp.outq = MoxaPortTxQueue(p);
				पूर्ण
				spin_unlock_bh(&moxa_lock);
				अगर (copy_to_user(argm, &पंचांगp, माप(पंचांगp)))
					वापस -EFAULT;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण हाल MOXA_GET_OQUEUE:
		status = MoxaPortTxQueue(ch);
		ret = put_user(status, (अचिन्हित दीर्घ __user *)argp);
		अवरोध;
	हाल MOXA_GET_IQUEUE:
		status = MoxaPortRxQueue(ch);
		ret = put_user(status, (अचिन्हित दीर्घ __user *)argp);
		अवरोध;
	हाल MOXA_GETMSTATUS: अणु
		काष्ठा mxser_mstatus __user *argm = argp;
		काष्ठा mxser_mstatus पंचांगp;
		काष्ठा moxa_port *p;
		अचिन्हित पूर्णांक i, j;

		क्रम (i = 0; i < MAX_BOARDS; i++) अणु
			p = moxa_boards[i].ports;
			क्रम (j = 0; j < MAX_PORTS_PER_BOARD; j++, p++, argm++) अणु
				काष्ठा tty_काष्ठा *ttyp;
				स_रखो(&पंचांगp, 0, माप(पंचांगp));
				spin_lock_bh(&moxa_lock);
				अगर (!moxa_boards[i].पढ़ोy) अणु
				        spin_unlock_bh(&moxa_lock);
					जाओ copy;
                                पूर्ण

				status = MoxaPortLineStatus(p);
				spin_unlock_bh(&moxa_lock);

				अगर (status & 1)
					पंचांगp.cts = 1;
				अगर (status & 2)
					पंचांगp.dsr = 1;
				अगर (status & 4)
					पंचांगp.dcd = 1;

				ttyp = tty_port_tty_get(&p->port);
				अगर (!ttyp)
					पंचांगp.cflag = p->cflag;
				अन्यथा
					पंचांगp.cflag = ttyp->termios.c_cflag;
				tty_kref_put(ttyp);
copy:
				अगर (copy_to_user(argm, &पंचांगp, माप(पंचांगp)))
					वापस -EFAULT;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		ret = -ENOIOCTLCMD;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक moxa_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक state)
अणु
	काष्ठा moxa_port *port = tty->driver_data;

	moxafunc(port->tableAddr, state ? FC_SendBreak : FC_StopBreak,
			Magic_code);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tty_operations moxa_ops = अणु
	.खोलो = moxa_खोलो,
	.बंद = moxa_बंद,
	.ग_लिखो = moxa_ग_लिखो,
	.ग_लिखो_room = moxa_ग_लिखो_room,
	.flush_buffer = moxa_flush_buffer,
	.अक्षरs_in_buffer = moxa_अक्षरs_in_buffer,
	.ioctl = moxa_ioctl,
	.set_termios = moxa_set_termios,
	.stop = moxa_stop,
	.start = moxa_start,
	.hangup = moxa_hangup,
	.अवरोध_ctl = moxa_अवरोध_ctl,
	.tiocmget = moxa_tiocmget,
	.tiocmset = moxa_tiocmset,
	.set_serial = moxa_set_serial_info,
	.get_serial = moxa_get_serial_info,
पूर्ण;

अटल स्थिर काष्ठा tty_port_operations moxa_port_ops = अणु
	.carrier_उठाओd = moxa_carrier_उठाओd,
	.dtr_rts = moxa_dtr_rts,
	.shutकरोwn = moxa_shutकरोwn,
पूर्ण;

अटल काष्ठा tty_driver *moxaDriver;
अटल DEFINE_TIMER(moxaTimer, moxa_poll);

/*
 * HW init
 */

अटल पूर्णांक moxa_check_fw_model(काष्ठा moxa_board_conf *brd, u8 model)
अणु
	चयन (brd->boardType) अणु
	हाल MOXA_BOARD_C218_ISA:
	हाल MOXA_BOARD_C218_PCI:
		अगर (model != 1)
			जाओ err;
		अवरोध;
	हाल MOXA_BOARD_CP204J:
		अगर (model != 3)
			जाओ err;
		अवरोध;
	शेष:
		अगर (model != 2)
			जाओ err;
		अवरोध;
	पूर्ण
	वापस 0;
err:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक moxa_check_fw(स्थिर व्योम *ptr)
अणु
	स्थिर __le16 *lptr = ptr;

	अगर (*lptr != cpu_to_le16(0x7980))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक moxa_load_bios(काष्ठा moxa_board_conf *brd, स्थिर u8 *buf,
		माप_प्रकार len)
अणु
	व्योम __iomem *baseAddr = brd->basemem;
	u16 पंचांगp;

	ग_लिखोb(HW_reset, baseAddr + Control_reg);	/* reset */
	msleep(10);
	स_रखो_io(baseAddr, 0, 4096);
	स_नकल_toio(baseAddr, buf, len);	/* करोwnload BIOS */
	ग_लिखोb(0, baseAddr + Control_reg);	/* restart */

	msleep(2000);

	चयन (brd->boardType) अणु
	हाल MOXA_BOARD_C218_ISA:
	हाल MOXA_BOARD_C218_PCI:
		पंचांगp = पढ़ोw(baseAddr + C218_key);
		अगर (पंचांगp != C218_KeyCode)
			जाओ err;
		अवरोध;
	हाल MOXA_BOARD_CP204J:
		पंचांगp = पढ़ोw(baseAddr + C218_key);
		अगर (पंचांगp != CP204J_KeyCode)
			जाओ err;
		अवरोध;
	शेष:
		पंचांगp = पढ़ोw(baseAddr + C320_key);
		अगर (पंचांगp != C320_KeyCode)
			जाओ err;
		पंचांगp = पढ़ोw(baseAddr + C320_status);
		अगर (पंचांगp != STS_init) अणु
			prपूर्णांकk(KERN_ERR "MOXA: bios upload failed -- CPU/Basic "
					"module not found\n");
			वापस -EIO;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
err:
	prपूर्णांकk(KERN_ERR "MOXA: bios upload failed -- board not found\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक moxa_load_320b(काष्ठा moxa_board_conf *brd, स्थिर u8 *ptr,
		माप_प्रकार len)
अणु
	व्योम __iomem *baseAddr = brd->basemem;

	अगर (len < 7168) अणु
		prपूर्णांकk(KERN_ERR "MOXA: invalid 320 bios -- too short\n");
		वापस -EINVAL;
	पूर्ण

	ग_लिखोw(len - 7168 - 2, baseAddr + C320bapi_len);
	ग_लिखोb(1, baseAddr + Control_reg);	/* Select Page 1 */
	स_नकल_toio(baseAddr + DynPage_addr, ptr, 7168);
	ग_लिखोb(2, baseAddr + Control_reg);	/* Select Page 2 */
	स_नकल_toio(baseAddr + DynPage_addr, ptr + 7168, len - 7168);

	वापस 0;
पूर्ण

अटल पूर्णांक moxa_real_load_code(काष्ठा moxa_board_conf *brd, स्थिर व्योम *ptr,
		माप_प्रकार len)
अणु
	व्योम __iomem *baseAddr = brd->basemem;
	स्थिर __le16 *uptr = ptr;
	माप_प्रकार wlen, len2, j;
	अचिन्हित दीर्घ key, loadbuf, loadlen, checksum, checksum_ok;
	अचिन्हित पूर्णांक i, retry;
	u16 usum, keycode;

	keycode = (brd->boardType == MOXA_BOARD_CP204J) ? CP204J_KeyCode :
				C218_KeyCode;

	चयन (brd->boardType) अणु
	हाल MOXA_BOARD_CP204J:
	हाल MOXA_BOARD_C218_ISA:
	हाल MOXA_BOARD_C218_PCI:
		key = C218_key;
		loadbuf = C218_LoadBuf;
		loadlen = C218DLoad_len;
		checksum = C218check_sum;
		checksum_ok = C218chksum_ok;
		अवरोध;
	शेष:
		key = C320_key;
		keycode = C320_KeyCode;
		loadbuf = C320_LoadBuf;
		loadlen = C320DLoad_len;
		checksum = C320check_sum;
		checksum_ok = C320chksum_ok;
		अवरोध;
	पूर्ण

	usum = 0;
	wlen = len >> 1;
	क्रम (i = 0; i < wlen; i++)
		usum += le16_to_cpu(uptr[i]);
	retry = 0;
	करो अणु
		wlen = len >> 1;
		j = 0;
		जबतक (wlen) अणु
			len2 = (wlen > 2048) ? 2048 : wlen;
			wlen -= len2;
			स_नकल_toio(baseAddr + loadbuf, ptr + j, len2 << 1);
			j += len2 << 1;

			ग_लिखोw(len2, baseAddr + loadlen);
			ग_लिखोw(0, baseAddr + key);
			क्रम (i = 0; i < 100; i++) अणु
				अगर (पढ़ोw(baseAddr + key) == keycode)
					अवरोध;
				msleep(10);
			पूर्ण
			अगर (पढ़ोw(baseAddr + key) != keycode)
				वापस -EIO;
		पूर्ण
		ग_लिखोw(0, baseAddr + loadlen);
		ग_लिखोw(usum, baseAddr + checksum);
		ग_लिखोw(0, baseAddr + key);
		क्रम (i = 0; i < 100; i++) अणु
			अगर (पढ़ोw(baseAddr + key) == keycode)
				अवरोध;
			msleep(10);
		पूर्ण
		retry++;
	पूर्ण जबतक ((पढ़ोb(baseAddr + checksum_ok) != 1) && (retry < 3));
	अगर (पढ़ोb(baseAddr + checksum_ok) != 1)
		वापस -EIO;

	ग_लिखोw(0, baseAddr + key);
	क्रम (i = 0; i < 600; i++) अणु
		अगर (पढ़ोw(baseAddr + Magic_no) == Magic_code)
			अवरोध;
		msleep(10);
	पूर्ण
	अगर (पढ़ोw(baseAddr + Magic_no) != Magic_code)
		वापस -EIO;

	अगर (MOXA_IS_320(brd)) अणु
		अगर (brd->busType == MOXA_BUS_TYPE_PCI) अणु	/* ASIC board */
			ग_लिखोw(0x3800, baseAddr + TMS320_PORT1);
			ग_लिखोw(0x3900, baseAddr + TMS320_PORT2);
			ग_लिखोw(28499, baseAddr + TMS320_CLOCK);
		पूर्ण अन्यथा अणु
			ग_लिखोw(0x3200, baseAddr + TMS320_PORT1);
			ग_लिखोw(0x3400, baseAddr + TMS320_PORT2);
			ग_लिखोw(19999, baseAddr + TMS320_CLOCK);
		पूर्ण
	पूर्ण
	ग_लिखोw(1, baseAddr + Disable_IRQ);
	ग_लिखोw(0, baseAddr + Magic_no);
	क्रम (i = 0; i < 500; i++) अणु
		अगर (पढ़ोw(baseAddr + Magic_no) == Magic_code)
			अवरोध;
		msleep(10);
	पूर्ण
	अगर (पढ़ोw(baseAddr + Magic_no) != Magic_code)
		वापस -EIO;

	अगर (MOXA_IS_320(brd)) अणु
		j = पढ़ोw(baseAddr + Module_cnt);
		अगर (j <= 0)
			वापस -EIO;
		brd->numPorts = j * 8;
		ग_लिखोw(j, baseAddr + Module_no);
		ग_लिखोw(0, baseAddr + Magic_no);
		क्रम (i = 0; i < 600; i++) अणु
			अगर (पढ़ोw(baseAddr + Magic_no) == Magic_code)
				अवरोध;
			msleep(10);
		पूर्ण
		अगर (पढ़ोw(baseAddr + Magic_no) != Magic_code)
			वापस -EIO;
	पूर्ण
	brd->पूर्णांकNdx = baseAddr + IRQindex;
	brd->पूर्णांकPend = baseAddr + IRQpending;
	brd->पूर्णांकTable = baseAddr + IRQtable;

	वापस 0;
पूर्ण

अटल पूर्णांक moxa_load_code(काष्ठा moxa_board_conf *brd, स्थिर व्योम *ptr,
		माप_प्रकार len)
अणु
	व्योम __iomem *ofsAddr, *baseAddr = brd->basemem;
	काष्ठा moxa_port *port;
	पूर्णांक retval, i;

	अगर (len % 2) अणु
		prपूर्णांकk(KERN_ERR "MOXA: bios length is not even\n");
		वापस -EINVAL;
	पूर्ण

	retval = moxa_real_load_code(brd, ptr, len); /* may change numPorts */
	अगर (retval)
		वापस retval;

	चयन (brd->boardType) अणु
	हाल MOXA_BOARD_C218_ISA:
	हाल MOXA_BOARD_C218_PCI:
	हाल MOXA_BOARD_CP204J:
		port = brd->ports;
		क्रम (i = 0; i < brd->numPorts; i++, port++) अणु
			port->board = brd;
			port->DCDState = 0;
			port->tableAddr = baseAddr + Extern_table +
					Extern_size * i;
			ofsAddr = port->tableAddr;
			ग_लिखोw(C218rx_mask, ofsAddr + RX_mask);
			ग_लिखोw(C218tx_mask, ofsAddr + TX_mask);
			ग_लिखोw(C218rx_spage + i * C218buf_pageno, ofsAddr + Page_rxb);
			ग_लिखोw(पढ़ोw(ofsAddr + Page_rxb) + C218rx_pageno, ofsAddr + EndPage_rxb);

			ग_लिखोw(C218tx_spage + i * C218buf_pageno, ofsAddr + Page_txb);
			ग_लिखोw(पढ़ोw(ofsAddr + Page_txb) + C218tx_pageno, ofsAddr + EndPage_txb);

		पूर्ण
		अवरोध;
	शेष:
		port = brd->ports;
		क्रम (i = 0; i < brd->numPorts; i++, port++) अणु
			port->board = brd;
			port->DCDState = 0;
			port->tableAddr = baseAddr + Extern_table +
					Extern_size * i;
			ofsAddr = port->tableAddr;
			चयन (brd->numPorts) अणु
			हाल 8:
				ग_लिखोw(C320p8rx_mask, ofsAddr + RX_mask);
				ग_लिखोw(C320p8tx_mask, ofsAddr + TX_mask);
				ग_लिखोw(C320p8rx_spage + i * C320p8buf_pgno, ofsAddr + Page_rxb);
				ग_लिखोw(पढ़ोw(ofsAddr + Page_rxb) + C320p8rx_pgno, ofsAddr + EndPage_rxb);
				ग_लिखोw(C320p8tx_spage + i * C320p8buf_pgno, ofsAddr + Page_txb);
				ग_लिखोw(पढ़ोw(ofsAddr + Page_txb) + C320p8tx_pgno, ofsAddr + EndPage_txb);

				अवरोध;
			हाल 16:
				ग_लिखोw(C320p16rx_mask, ofsAddr + RX_mask);
				ग_लिखोw(C320p16tx_mask, ofsAddr + TX_mask);
				ग_लिखोw(C320p16rx_spage + i * C320p16buf_pgno, ofsAddr + Page_rxb);
				ग_लिखोw(पढ़ोw(ofsAddr + Page_rxb) + C320p16rx_pgno, ofsAddr + EndPage_rxb);
				ग_लिखोw(C320p16tx_spage + i * C320p16buf_pgno, ofsAddr + Page_txb);
				ग_लिखोw(पढ़ोw(ofsAddr + Page_txb) + C320p16tx_pgno, ofsAddr + EndPage_txb);
				अवरोध;

			हाल 24:
				ग_लिखोw(C320p24rx_mask, ofsAddr + RX_mask);
				ग_लिखोw(C320p24tx_mask, ofsAddr + TX_mask);
				ग_लिखोw(C320p24rx_spage + i * C320p24buf_pgno, ofsAddr + Page_rxb);
				ग_लिखोw(पढ़ोw(ofsAddr + Page_rxb) + C320p24rx_pgno, ofsAddr + EndPage_rxb);
				ग_लिखोw(C320p24tx_spage + i * C320p24buf_pgno, ofsAddr + Page_txb);
				ग_लिखोw(पढ़ोw(ofsAddr + Page_txb), ofsAddr + EndPage_txb);
				अवरोध;
			हाल 32:
				ग_लिखोw(C320p32rx_mask, ofsAddr + RX_mask);
				ग_लिखोw(C320p32tx_mask, ofsAddr + TX_mask);
				ग_लिखोw(C320p32tx_ofs, ofsAddr + Ofs_txb);
				ग_लिखोw(C320p32rx_spage + i * C320p32buf_pgno, ofsAddr + Page_rxb);
				ग_लिखोw(पढ़ोb(ofsAddr + Page_rxb), ofsAddr + EndPage_rxb);
				ग_लिखोw(C320p32tx_spage + i * C320p32buf_pgno, ofsAddr + Page_txb);
				ग_लिखोw(पढ़ोw(ofsAddr + Page_txb), ofsAddr + EndPage_txb);
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक moxa_load_fw(काष्ठा moxa_board_conf *brd, स्थिर काष्ठा firmware *fw)
अणु
	स्थिर व्योम *ptr = fw->data;
	अक्षर rsn[64];
	u16 lens[5];
	माप_प्रकार len;
	अचिन्हित पूर्णांक a, lenp, lencnt;
	पूर्णांक ret = -EINVAL;
	काष्ठा अणु
		__le32 magic;	/* 0x34303430 */
		u8 reserved1[2];
		u8 type;	/* UNIX = 3 */
		u8 model;	/* C218T=1, C320T=2, CP204=3 */
		u8 reserved2[8];
		__le16 len[5];
	पूर्ण स्थिर *hdr = ptr;

	BUILD_BUG_ON(ARRAY_SIZE(hdr->len) != ARRAY_SIZE(lens));

	अगर (fw->size < MOXA_FW_HDRLEN) अणु
		म_नकल(rsn, "too short (even header won't fit)");
		जाओ err;
	पूर्ण
	अगर (hdr->magic != cpu_to_le32(0x30343034)) अणु
		प्र_लिखो(rsn, "bad magic: %.8x", le32_to_cpu(hdr->magic));
		जाओ err;
	पूर्ण
	अगर (hdr->type != 3) अणु
		प्र_लिखो(rsn, "not for linux, type is %u", hdr->type);
		जाओ err;
	पूर्ण
	अगर (moxa_check_fw_model(brd, hdr->model)) अणु
		प्र_लिखो(rsn, "not for this card, model is %u", hdr->model);
		जाओ err;
	पूर्ण

	len = MOXA_FW_HDRLEN;
	lencnt = hdr->model == 2 ? 5 : 3;
	क्रम (a = 0; a < ARRAY_SIZE(lens); a++) अणु
		lens[a] = le16_to_cpu(hdr->len[a]);
		अगर (lens[a] && len + lens[a] <= fw->size &&
				moxa_check_fw(&fw->data[len]))
			prपूर्णांकk(KERN_WARNING "MOXA firmware: unexpected input "
				"at offset %u, but going on\n", (u32)len);
		अगर (!lens[a] && a < lencnt) अणु
			प्र_लिखो(rsn, "too few entries in fw file");
			जाओ err;
		पूर्ण
		len += lens[a];
	पूर्ण

	अगर (len != fw->size) अणु
		प्र_लिखो(rsn, "bad length: %u (should be %u)", (u32)fw->size,
				(u32)len);
		जाओ err;
	पूर्ण

	ptr += MOXA_FW_HDRLEN;
	lenp = 0; /* bios */

	म_नकल(rsn, "read above");

	ret = moxa_load_bios(brd, ptr, lens[lenp]);
	अगर (ret)
		जाओ err;

	/* we skip the tty section (lens[1]), since we करोn't need it */
	ptr += lens[lenp] + lens[lenp + 1];
	lenp += 2; /* comm */

	अगर (hdr->model == 2) अणु
		ret = moxa_load_320b(brd, ptr, lens[lenp]);
		अगर (ret)
			जाओ err;
		/* skip another tty */
		ptr += lens[lenp] + lens[lenp + 1];
		lenp += 2;
	पूर्ण

	ret = moxa_load_code(brd, ptr, lens[lenp]);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	prपूर्णांकk(KERN_ERR "firmware failed to load, reason: %s\n", rsn);
	वापस ret;
पूर्ण

अटल पूर्णांक moxa_init_board(काष्ठा moxa_board_conf *brd, काष्ठा device *dev)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *file;
	काष्ठा moxa_port *p;
	अचिन्हित पूर्णांक i, first_idx;
	पूर्णांक ret;

	brd->ports = kसुस्मृति(MAX_PORTS_PER_BOARD, माप(*brd->ports),
			GFP_KERNEL);
	अगर (brd->ports == शून्य) अणु
		prपूर्णांकk(KERN_ERR "cannot allocate memory for ports\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	क्रम (i = 0, p = brd->ports; i < MAX_PORTS_PER_BOARD; i++, p++) अणु
		tty_port_init(&p->port);
		p->port.ops = &moxa_port_ops;
		p->type = PORT_16550A;
		p->cflag = B9600 | CS8 | CREAD | CLOCAL | HUPCL;
	पूर्ण

	चयन (brd->boardType) अणु
	हाल MOXA_BOARD_C218_ISA:
	हाल MOXA_BOARD_C218_PCI:
		file = "c218tunx.cod";
		अवरोध;
	हाल MOXA_BOARD_CP204J:
		file = "cp204unx.cod";
		अवरोध;
	शेष:
		file = "c320tunx.cod";
		अवरोध;
	पूर्ण

	ret = request_firmware(&fw, file, dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "MOXA: request_firmware failed. Make sure "
				"you've placed '%s' file into your firmware "
				"loader directory (e.g. /lib/firmware)\n",
				file);
		जाओ err_मुक्त;
	पूर्ण

	ret = moxa_load_fw(brd, fw);

	release_firmware(fw);

	अगर (ret)
		जाओ err_मुक्त;

	spin_lock_bh(&moxa_lock);
	brd->पढ़ोy = 1;
	अगर (!समयr_pending(&moxaTimer))
		mod_समयr(&moxaTimer, jअगरfies + HZ / 50);
	spin_unlock_bh(&moxa_lock);

	first_idx = (brd - moxa_boards) * MAX_PORTS_PER_BOARD;
	क्रम (i = 0; i < brd->numPorts; i++)
		tty_port_रेजिस्टर_device(&brd->ports[i].port, moxaDriver,
				first_idx + i, dev);

	वापस 0;
err_मुक्त:
	क्रम (i = 0; i < MAX_PORTS_PER_BOARD; i++)
		tty_port_destroy(&brd->ports[i].port);
	kमुक्त(brd->ports);
err:
	वापस ret;
पूर्ण

अटल व्योम moxa_board_deinit(काष्ठा moxa_board_conf *brd)
अणु
	अचिन्हित पूर्णांक a, खोलोed, first_idx;

	mutex_lock(&moxa_खोलोlock);
	spin_lock_bh(&moxa_lock);
	brd->पढ़ोy = 0;
	spin_unlock_bh(&moxa_lock);

	/* pci hot-un-plug support */
	क्रम (a = 0; a < brd->numPorts; a++)
		अगर (tty_port_initialized(&brd->ports[a].port))
			tty_port_tty_hangup(&brd->ports[a].port, false);

	क्रम (a = 0; a < MAX_PORTS_PER_BOARD; a++)
		tty_port_destroy(&brd->ports[a].port);

	जबतक (1) अणु
		खोलोed = 0;
		क्रम (a = 0; a < brd->numPorts; a++)
			अगर (tty_port_initialized(&brd->ports[a].port))
				खोलोed++;
		mutex_unlock(&moxa_खोलोlock);
		अगर (!खोलोed)
			अवरोध;
		msleep(50);
		mutex_lock(&moxa_खोलोlock);
	पूर्ण

	first_idx = (brd - moxa_boards) * MAX_PORTS_PER_BOARD;
	क्रम (a = 0; a < brd->numPorts; a++)
		tty_unरेजिस्टर_device(moxaDriver, first_idx + a);

	iounmap(brd->basemem);
	brd->basemem = शून्य;
	kमुक्त(brd->ports);
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक moxa_pci_probe(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा moxa_board_conf *board;
	अचिन्हित पूर्णांक i;
	पूर्णांक board_type = ent->driver_data;
	पूर्णांक retval;

	retval = pci_enable_device(pdev);
	अगर (retval) अणु
		dev_err(&pdev->dev, "can't enable pci device\n");
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < MAX_BOARDS; i++)
		अगर (moxa_boards[i].basemem == शून्य)
			अवरोध;

	retval = -ENODEV;
	अगर (i >= MAX_BOARDS) अणु
		dev_warn(&pdev->dev, "more than %u MOXA Intellio family boards "
				"found. Board is ignored.\n", MAX_BOARDS);
		जाओ err;
	पूर्ण

	board = &moxa_boards[i];

	retval = pci_request_region(pdev, 2, "moxa-base");
	अगर (retval) अणु
		dev_err(&pdev->dev, "can't request pci region 2\n");
		जाओ err;
	पूर्ण

	board->basemem = ioremap(pci_resource_start(pdev, 2), 0x4000);
	अगर (board->basemem == शून्य) अणु
		dev_err(&pdev->dev, "can't remap io space 2\n");
		retval = -ENOMEM;
		जाओ err_reg;
	पूर्ण

	board->boardType = board_type;
	चयन (board_type) अणु
	हाल MOXA_BOARD_C218_ISA:
	हाल MOXA_BOARD_C218_PCI:
		board->numPorts = 8;
		अवरोध;

	हाल MOXA_BOARD_CP204J:
		board->numPorts = 4;
		अवरोध;
	शेष:
		board->numPorts = 0;
		अवरोध;
	पूर्ण
	board->busType = MOXA_BUS_TYPE_PCI;

	retval = moxa_init_board(board, &pdev->dev);
	अगर (retval)
		जाओ err_base;

	pci_set_drvdata(pdev, board);

	dev_info(&pdev->dev, "board '%s' ready (%u ports, firmware loaded)\n",
			moxa_brdname[board_type - 1], board->numPorts);

	वापस 0;
err_base:
	iounmap(board->basemem);
	board->basemem = शून्य;
err_reg:
	pci_release_region(pdev, 2);
err:
	वापस retval;
पूर्ण

अटल व्योम moxa_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा moxa_board_conf *brd = pci_get_drvdata(pdev);

	moxa_board_deinit(brd);

	pci_release_region(pdev, 2);
पूर्ण

अटल काष्ठा pci_driver moxa_pci_driver = अणु
	.name = "moxa",
	.id_table = moxa_pcibrds,
	.probe = moxa_pci_probe,
	.हटाओ = moxa_pci_हटाओ
पूर्ण;
#पूर्ण_अगर /* CONFIG_PCI */

अटल पूर्णांक __init moxa_init(व्योम)
अणु
	अचिन्हित पूर्णांक isabrds = 0;
	पूर्णांक retval = 0;
	काष्ठा moxa_board_conf *brd = moxa_boards;
	अचिन्हित पूर्णांक i;

	prपूर्णांकk(KERN_INFO "MOXA Intellio family driver version %s\n",
			MOXA_VERSION);

	tty_port_init(&moxa_service_port);

	moxaDriver = tty_alloc_driver(MAX_PORTS + 1,
			TTY_DRIVER_REAL_RAW |
			TTY_DRIVER_DYNAMIC_DEV);
	अगर (IS_ERR(moxaDriver))
		वापस PTR_ERR(moxaDriver);

	moxaDriver->name = "ttyMX";
	moxaDriver->major = ttymajor;
	moxaDriver->minor_start = 0;
	moxaDriver->type = TTY_DRIVER_TYPE_SERIAL;
	moxaDriver->subtype = SERIAL_TYPE_NORMAL;
	moxaDriver->init_termios = tty_std_termios;
	moxaDriver->init_termios.c_cflag = B9600 | CS8 | CREAD | CLOCAL | HUPCL;
	moxaDriver->init_termios.c_ispeed = 9600;
	moxaDriver->init_termios.c_ospeed = 9600;
	tty_set_operations(moxaDriver, &moxa_ops);
	/* Having one more port only क्रम ioctls is ugly */
	tty_port_link_device(&moxa_service_port, moxaDriver, MAX_PORTS);

	अगर (tty_रेजिस्टर_driver(moxaDriver)) अणु
		prपूर्णांकk(KERN_ERR "can't register MOXA Smartio tty driver!\n");
		put_tty_driver(moxaDriver);
		वापस -1;
	पूर्ण

	/* Find the boards defined from module args. */

	क्रम (i = 0; i < MAX_BOARDS; i++) अणु
		अगर (!baseaddr[i])
			अवरोध;
		अगर (type[i] == MOXA_BOARD_C218_ISA ||
				type[i] == MOXA_BOARD_C320_ISA) अणु
			pr_debug("Moxa board %2d: %s board(baseAddr=%lx)\n",
					isabrds + 1, moxa_brdname[type[i] - 1],
					baseaddr[i]);
			brd->boardType = type[i];
			brd->numPorts = type[i] == MOXA_BOARD_C218_ISA ? 8 :
					numports[i];
			brd->busType = MOXA_BUS_TYPE_ISA;
			brd->basemem = ioremap(baseaddr[i], 0x4000);
			अगर (!brd->basemem) अणु
				prपूर्णांकk(KERN_ERR "MOXA: can't remap %lx\n",
						baseaddr[i]);
				जारी;
			पूर्ण
			अगर (moxa_init_board(brd, शून्य)) अणु
				iounmap(brd->basemem);
				brd->basemem = शून्य;
				जारी;
			पूर्ण

			prपूर्णांकk(KERN_INFO "MOXA isa board found at 0x%.8lx and "
					"ready (%u ports, firmware loaded)\n",
					baseaddr[i], brd->numPorts);

			brd++;
			isabrds++;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_PCI
	retval = pci_रेजिस्टर_driver(&moxa_pci_driver);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "Can't register MOXA pci driver!\n");
		अगर (isabrds)
			retval = 0;
	पूर्ण
#पूर्ण_अगर

	वापस retval;
पूर्ण

अटल व्योम __निकास moxa_निकास(व्योम)
अणु
	अचिन्हित पूर्णांक i;

#अगर_घोषित CONFIG_PCI
	pci_unरेजिस्टर_driver(&moxa_pci_driver);
#पूर्ण_अगर

	क्रम (i = 0; i < MAX_BOARDS; i++) /* ISA boards */
		अगर (moxa_boards[i].पढ़ोy)
			moxa_board_deinit(&moxa_boards[i]);

	del_समयr_sync(&moxaTimer);

	tty_unरेजिस्टर_driver(moxaDriver);
	put_tty_driver(moxaDriver);
पूर्ण

module_init(moxa_init);
module_निकास(moxa_निकास);

अटल व्योम moxa_shutकरोwn(काष्ठा tty_port *port)
अणु
	काष्ठा moxa_port *ch = container_of(port, काष्ठा moxa_port, port);
        MoxaPortDisable(ch);
	MoxaPortFlushData(ch, 2);
पूर्ण

अटल पूर्णांक moxa_carrier_उठाओd(काष्ठा tty_port *port)
अणु
	काष्ठा moxa_port *ch = container_of(port, काष्ठा moxa_port, port);
	पूर्णांक dcd;

	spin_lock_irq(&port->lock);
	dcd = ch->DCDState;
	spin_unlock_irq(&port->lock);
	वापस dcd;
पूर्ण

अटल व्योम moxa_dtr_rts(काष्ठा tty_port *port, पूर्णांक onoff)
अणु
	काष्ठा moxa_port *ch = container_of(port, काष्ठा moxa_port, port);
	MoxaPortLineCtrl(ch, onoff, onoff);
पूर्ण


अटल पूर्णांक moxa_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा moxa_board_conf *brd;
	काष्ठा moxa_port *ch;
	पूर्णांक port;

	port = tty->index;
	अगर (port == MAX_PORTS) अणु
		वापस capable(CAP_SYS_ADMIN) ? 0 : -EPERM;
	पूर्ण
	अगर (mutex_lock_पूर्णांकerruptible(&moxa_खोलोlock))
		वापस -ERESTARTSYS;
	brd = &moxa_boards[port / MAX_PORTS_PER_BOARD];
	अगर (!brd->पढ़ोy) अणु
		mutex_unlock(&moxa_खोलोlock);
		वापस -ENODEV;
	पूर्ण

	अगर (port % MAX_PORTS_PER_BOARD >= brd->numPorts) अणु
		mutex_unlock(&moxa_खोलोlock);
		वापस -ENODEV;
	पूर्ण

	ch = &brd->ports[port % MAX_PORTS_PER_BOARD];
	ch->port.count++;
	tty->driver_data = ch;
	tty_port_tty_set(&ch->port, tty);
	mutex_lock(&ch->port.mutex);
	अगर (!tty_port_initialized(&ch->port)) अणु
		ch->statusflags = 0;
		moxa_set_tty_param(tty, &tty->termios);
		MoxaPortLineCtrl(ch, 1, 1);
		MoxaPortEnable(ch);
		MoxaSetFअगरo(ch, ch->type == PORT_16550A);
		tty_port_set_initialized(&ch->port, 1);
	पूर्ण
	mutex_unlock(&ch->port.mutex);
	mutex_unlock(&moxa_खोलोlock);

	वापस tty_port_block_til_पढ़ोy(&ch->port, tty, filp);
पूर्ण

अटल व्योम moxa_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा moxa_port *ch = tty->driver_data;
	ch->cflag = tty->termios.c_cflag;
	tty_port_बंद(&ch->port, tty, filp);
पूर्ण

अटल पूर्णांक moxa_ग_लिखो(काष्ठा tty_काष्ठा *tty,
		      स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा moxa_port *ch = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक len;

	अगर (ch == शून्य)
		वापस 0;

	spin_lock_irqsave(&moxa_lock, flags);
	len = MoxaPortWriteData(tty, buf, count);
	spin_unlock_irqrestore(&moxa_lock, flags);

	set_bit(LOWWAIT, &ch->statusflags);
	वापस len;
पूर्ण

अटल पूर्णांक moxa_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा moxa_port *ch;

	अगर (tty->stopped)
		वापस 0;
	ch = tty->driver_data;
	अगर (ch == शून्य)
		वापस 0;
	वापस MoxaPortTxFree(ch);
पूर्ण

अटल व्योम moxa_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा moxa_port *ch = tty->driver_data;

	अगर (ch == शून्य)
		वापस;
	MoxaPortFlushData(ch, 1);
	tty_wakeup(tty);
पूर्ण

अटल पूर्णांक moxa_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा moxa_port *ch = tty->driver_data;
	पूर्णांक अक्षरs;

	अक्षरs = MoxaPortTxQueue(ch);
	अगर (अक्षरs)
		/*
		 * Make it possible to wakeup anything रुकोing क्रम output
		 * in tty_ioctl.c, etc.
		 */
        	set_bit(EMPTYWAIT, &ch->statusflags);
	वापस अक्षरs;
पूर्ण

अटल पूर्णांक moxa_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा moxa_port *ch = tty->driver_data;
	पूर्णांक flag = 0, dtr, rts;

	MoxaPortGetLineOut(ch, &dtr, &rts);
	अगर (dtr)
		flag |= TIOCM_DTR;
	अगर (rts)
		flag |= TIOCM_RTS;
	dtr = MoxaPortLineStatus(ch);
	अगर (dtr & 1)
		flag |= TIOCM_CTS;
	अगर (dtr & 2)
		flag |= TIOCM_DSR;
	अगर (dtr & 4)
		flag |= TIOCM_CD;
	वापस flag;
पूर्ण

अटल पूर्णांक moxa_tiocmset(काष्ठा tty_काष्ठा *tty,
			 अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा moxa_port *ch;
	पूर्णांक dtr, rts;

	mutex_lock(&moxa_खोलोlock);
	ch = tty->driver_data;
	अगर (!ch) अणु
		mutex_unlock(&moxa_खोलोlock);
		वापस -EINVAL;
	पूर्ण

	MoxaPortGetLineOut(ch, &dtr, &rts);
	अगर (set & TIOCM_RTS)
		rts = 1;
	अगर (set & TIOCM_DTR)
		dtr = 1;
	अगर (clear & TIOCM_RTS)
		rts = 0;
	अगर (clear & TIOCM_DTR)
		dtr = 0;
	MoxaPortLineCtrl(ch, dtr, rts);
	mutex_unlock(&moxa_खोलोlock);
	वापस 0;
पूर्ण

अटल व्योम moxa_set_termios(काष्ठा tty_काष्ठा *tty,
		काष्ठा ktermios *old_termios)
अणु
	काष्ठा moxa_port *ch = tty->driver_data;

	अगर (ch == शून्य)
		वापस;
	moxa_set_tty_param(tty, old_termios);
	अगर (!(old_termios->c_cflag & CLOCAL) && C_CLOCAL(tty))
		wake_up_पूर्णांकerruptible(&ch->port.खोलो_रुको);
पूर्ण

अटल व्योम moxa_stop(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा moxa_port *ch = tty->driver_data;

	अगर (ch == शून्य)
		वापस;
	MoxaPortTxDisable(ch);
	set_bit(TXSTOPPED, &ch->statusflags);
पूर्ण


अटल व्योम moxa_start(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा moxa_port *ch = tty->driver_data;

	अगर (ch == शून्य)
		वापस;

	अगर (!test_bit(TXSTOPPED, &ch->statusflags))
		वापस;

	MoxaPortTxEnable(ch);
	clear_bit(TXSTOPPED, &ch->statusflags);
पूर्ण

अटल व्योम moxa_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा moxa_port *ch = tty->driver_data;
	tty_port_hangup(&ch->port);
पूर्ण

अटल व्योम moxa_new_dcdstate(काष्ठा moxa_port *p, u8 dcd)
अणु
	अचिन्हित दीर्घ flags;
	dcd = !!dcd;

	spin_lock_irqsave(&p->port.lock, flags);
	अगर (dcd != p->DCDState) अणु
        	p->DCDState = dcd;
        	spin_unlock_irqrestore(&p->port.lock, flags);
		अगर (!dcd)
			tty_port_tty_hangup(&p->port, true);
	पूर्ण
	अन्यथा
		spin_unlock_irqrestore(&p->port.lock, flags);
पूर्ण

अटल पूर्णांक moxa_poll_port(काष्ठा moxa_port *p, अचिन्हित पूर्णांक handle,
		u16 __iomem *ip)
अणु
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&p->port);
	व्योम __iomem *ofsAddr;
	अचिन्हित पूर्णांक inited = tty_port_initialized(&p->port);
	u16 पूर्णांकr;

	अगर (tty) अणु
		अगर (test_bit(EMPTYWAIT, &p->statusflags) &&
				MoxaPortTxQueue(p) == 0) अणु
			clear_bit(EMPTYWAIT, &p->statusflags);
			tty_wakeup(tty);
		पूर्ण
		अगर (test_bit(LOWWAIT, &p->statusflags) && !tty->stopped &&
				MoxaPortTxQueue(p) <= WAKEUP_CHARS) अणु
			clear_bit(LOWWAIT, &p->statusflags);
			tty_wakeup(tty);
		पूर्ण

		अगर (inited && !tty_throttled(tty) &&
				MoxaPortRxQueue(p) > 0) अणु /* RX */
			MoxaPortReadData(p);
			tty_schedule_flip(&p->port);
		पूर्ण
	पूर्ण अन्यथा अणु
		clear_bit(EMPTYWAIT, &p->statusflags);
		MoxaPortFlushData(p, 0); /* flush RX */
	पूर्ण

	अगर (!handle) /* nothing अन्यथा to करो */
		जाओ put;

	पूर्णांकr = पढ़ोw(ip); /* port irq status */
	अगर (पूर्णांकr == 0)
		जाओ put;

	ग_लिखोw(0, ip); /* ACK port */
	ofsAddr = p->tableAddr;
	अगर (पूर्णांकr & IntrTx) /* disable tx पूर्णांकr */
		ग_लिखोw(पढ़ोw(ofsAddr + HostStat) & ~WakeupTx,
				ofsAddr + HostStat);

	अगर (!inited)
		जाओ put;

	अगर (tty && (पूर्णांकr & IntrBreak) && !I_IGNBRK(tty)) अणु /* BREAK */
		tty_insert_flip_अक्षर(&p->port, 0, TTY_BREAK);
		tty_schedule_flip(&p->port);
	पूर्ण

	अगर (पूर्णांकr & IntrLine)
		moxa_new_dcdstate(p, पढ़ोb(ofsAddr + FlagStat) & DCD_state);
put:
	tty_kref_put(tty);

	वापस 0;
पूर्ण

अटल व्योम moxa_poll(काष्ठा समयr_list *unused)
अणु
	काष्ठा moxa_board_conf *brd;
	u16 __iomem *ip;
	अचिन्हित पूर्णांक card, port, served = 0;

	spin_lock(&moxa_lock);
	क्रम (card = 0; card < MAX_BOARDS; card++) अणु
		brd = &moxa_boards[card];
		अगर (!brd->पढ़ोy)
			जारी;

		served++;

		ip = शून्य;
		अगर (पढ़ोb(brd->पूर्णांकPend) == 0xff)
			ip = brd->पूर्णांकTable + पढ़ोb(brd->पूर्णांकNdx);

		क्रम (port = 0; port < brd->numPorts; port++)
			moxa_poll_port(&brd->ports[port], !!ip, ip + port);

		अगर (ip)
			ग_लिखोb(0, brd->पूर्णांकPend); /* ACK */

		अगर (moxaLowWaterChk) अणु
			काष्ठा moxa_port *p = brd->ports;
			क्रम (port = 0; port < brd->numPorts; port++, p++)
				अगर (p->lowChkFlag) अणु
					p->lowChkFlag = 0;
					moxa_low_water_check(p->tableAddr);
				पूर्ण
		पूर्ण
	पूर्ण
	moxaLowWaterChk = 0;

	अगर (served)
		mod_समयr(&moxaTimer, jअगरfies + HZ / 50);
	spin_unlock(&moxa_lock);
पूर्ण

/******************************************************************************/

अटल व्योम moxa_set_tty_param(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old_termios)
अणु
	रेजिस्टर काष्ठा ktermios *ts = &tty->termios;
	काष्ठा moxa_port *ch = tty->driver_data;
	पूर्णांक rts, cts, txflow, rxflow, xany, baud;

	rts = cts = txflow = rxflow = xany = 0;
	अगर (ts->c_cflag & CRTSCTS)
		rts = cts = 1;
	अगर (ts->c_अगरlag & IXON)
		txflow = 1;
	अगर (ts->c_अगरlag & IXOFF)
		rxflow = 1;
	अगर (ts->c_अगरlag & IXANY)
		xany = 1;

	MoxaPortFlowCtrl(ch, rts, cts, txflow, rxflow, xany);
	baud = MoxaPortSetTermio(ch, ts, tty_get_baud_rate(tty));
	अगर (baud == -1)
		baud = tty_termios_baud_rate(old_termios);
	/* Not put the baud rate पूर्णांकo the termios data */
	tty_encode_baud_rate(tty, baud, baud);
पूर्ण

/*****************************************************************************
 *	Driver level functions: 					     *
 *****************************************************************************/

अटल व्योम MoxaPortFlushData(काष्ठा moxa_port *port, पूर्णांक mode)
अणु
	व्योम __iomem *ofsAddr;
	अगर (mode < 0 || mode > 2)
		वापस;
	ofsAddr = port->tableAddr;
	moxafunc(ofsAddr, FC_FlushQueue, mode);
	अगर (mode != 1) अणु
		port->lowChkFlag = 0;
		moxa_low_water_check(ofsAddr);
	पूर्ण
पूर्ण

/*
 *    Moxa Port Number Description:
 *
 *      MOXA serial driver supports up to 4 MOXA-C218/C320 boards. And,
 *      the port number using in MOXA driver functions will be 0 to 31 क्रम
 *      first MOXA board, 32 to 63 क्रम second, 64 to 95 क्रम third and 96
 *      to 127 क्रम fourth. For example, अगर you setup three MOXA boards,
 *      first board is C218, second board is C320-16 and third board is
 *      C320-32. The port number of first board (C218 - 8 ports) is from
 *      0 to 7. The port number of second board (C320 - 16 ports) is क्रमm
 *      32 to 47. The port number of third board (C320 - 32 ports) is from
 *      64 to 95. And those port numbers क्रमm 8 to 31, 48 to 63 and 96 to
 *      127 will be invalid.
 *
 *
 *      Moxa Functions Description:
 *
 *      Function 1:     Driver initialization routine, this routine must be
 *                      called when initialized driver.
 *      Syntax:
 *      व्योम MoxaDriverInit();
 *
 *
 *      Function 2:     Moxa driver निजी IOCTL command processing.
 *      Syntax:
 *      पूर्णांक  MoxaDriverIoctl(अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg, पूर्णांक port);
 *
 *           अचिन्हित पूर्णांक cmd   : IOCTL command
 *           अचिन्हित दीर्घ arg  : IOCTL argument
 *           पूर्णांक port           : port number (0 - 127)
 *
 *           वापस:    0  (OK)
 *                      -EINVAL
 *                      -ENOIOCTLCMD
 *
 *
 *      Function 6:     Enable this port to start Tx/Rx data.
 *      Syntax:
 *      व्योम MoxaPortEnable(पूर्णांक port);
 *           पूर्णांक port           : port number (0 - 127)
 *
 *
 *      Function 7:     Disable this port
 *      Syntax:
 *      व्योम MoxaPortDisable(पूर्णांक port);
 *           पूर्णांक port           : port number (0 - 127)
 *
 *
 *      Function 10:    Setting baud rate of this port.
 *      Syntax:
 *      speed_t MoxaPortSetBaud(पूर्णांक port, speed_t baud);
 *           पूर्णांक port           : port number (0 - 127)
 *           दीर्घ baud          : baud rate (50 - 115200)
 *
 *           वापस:    0       : this port is invalid or baud < 50
 *                      50 - 115200 : the real baud rate set to the port, अगर
 *                                    the argument baud is large than maximun
 *                                    available baud rate, the real setting
 *                                    baud rate will be the maximun baud rate.
 *
 *
 *      Function 12:    Configure the port.
 *      Syntax:
 *      पूर्णांक  MoxaPortSetTermio(पूर्णांक port, काष्ठा ktermios *termio, speed_t baud);
 *           पूर्णांक port           : port number (0 - 127)
 *           काष्ठा ktermios * termio : termio काष्ठाure poपूर्णांकer
 *	     speed_t baud	: baud rate
 *
 *           वापस:    -1      : this port is invalid or termio == शून्य
 *                      0       : setting O.K.
 *
 *
 *      Function 13:    Get the DTR/RTS state of this port.
 *      Syntax:
 *      पूर्णांक  MoxaPortGetLineOut(पूर्णांक port, पूर्णांक *dtrState, पूर्णांक *rtsState);
 *           पूर्णांक port           : port number (0 - 127)
 *           पूर्णांक * dtrState     : poपूर्णांकer to INT to receive the current DTR
 *                                state. (अगर शून्य, this function will not
 *                                ग_लिखो to this address)
 *           पूर्णांक * rtsState     : poपूर्णांकer to INT to receive the current RTS
 *                                state. (अगर शून्य, this function will not
 *                                ग_लिखो to this address)
 *
 *           वापस:    -1      : this port is invalid
 *                      0       : O.K.
 *
 *
 *      Function 14:    Setting the DTR/RTS output state of this port.
 *      Syntax:
 *      व्योम MoxaPortLineCtrl(पूर्णांक port, पूर्णांक dtrState, पूर्णांक rtsState);
 *           पूर्णांक port           : port number (0 - 127)
 *           पूर्णांक dtrState       : DTR output state (0: off, 1: on)
 *           पूर्णांक rtsState       : RTS output state (0: off, 1: on)
 *
 *
 *      Function 15:    Setting the flow control of this port.
 *      Syntax:
 *      व्योम MoxaPortFlowCtrl(पूर्णांक port, पूर्णांक rtsFlow, पूर्णांक ctsFlow, पूर्णांक rxFlow,
 *                            पूर्णांक txFlow,पूर्णांक xany);
 *           पूर्णांक port           : port number (0 - 127)
 *           पूर्णांक rtsFlow        : H/W RTS flow control (0: no, 1: yes)
 *           पूर्णांक ctsFlow        : H/W CTS flow control (0: no, 1: yes)
 *           पूर्णांक rxFlow         : S/W Rx XON/XOFF flow control (0: no, 1: yes)
 *           पूर्णांक txFlow         : S/W Tx XON/XOFF flow control (0: no, 1: yes)
 *           पूर्णांक xany           : S/W XANY flow control (0: no, 1: yes)
 *
 *
 *      Function 16:    Get ths line status of this port
 *      Syntax:
 *      पूर्णांक  MoxaPortLineStatus(पूर्णांक port);
 *           पूर्णांक port           : port number (0 - 127)
 *
 *           वापस:    Bit 0 - CTS state (0: off, 1: on)
 *                      Bit 1 - DSR state (0: off, 1: on)
 *                      Bit 2 - DCD state (0: off, 1: on)
 *
 *
 *      Function 19:    Flush the Rx/Tx buffer data of this port.
 *      Syntax:
 *      व्योम MoxaPortFlushData(पूर्णांक port, पूर्णांक mode);
 *           पूर्णांक port           : port number (0 - 127)
 *           पूर्णांक mode    
 *                      0       : flush the Rx buffer 
 *                      1       : flush the Tx buffer 
 *                      2       : flush the Rx and Tx buffer 
 *
 *
 *      Function 20:    Write data.
 *      Syntax:
 *      पूर्णांक  MoxaPortWriteData(पूर्णांक port, अचिन्हित अक्षर * buffer, पूर्णांक length);
 *           पूर्णांक port           : port number (0 - 127)
 *           अचिन्हित अक्षर * buffer     : poपूर्णांकer to ग_लिखो data buffer.
 *           पूर्णांक length         : ग_लिखो data length
 *
 *           वापस:    0 - length      : real ग_लिखो data length
 *
 *
 *      Function 21:    Read data.
 *      Syntax:
 *      पूर्णांक  MoxaPortReadData(पूर्णांक port, काष्ठा tty_काष्ठा *tty);
 *           पूर्णांक port           : port number (0 - 127)
 *	     काष्ठा tty_काष्ठा *tty : tty क्रम data
 *
 *           वापस:    0 - length      : real पढ़ो data length
 *
 *
 *      Function 24:    Get the Tx buffer current queued data bytes
 *      Syntax:
 *      पूर्णांक  MoxaPortTxQueue(पूर्णांक port);
 *           पूर्णांक port           : port number (0 - 127)
 *
 *           वापस:    ..      : Tx buffer current queued data bytes
 *
 *
 *      Function 25:    Get the Tx buffer current मुक्त space
 *      Syntax:
 *      पूर्णांक  MoxaPortTxFree(पूर्णांक port);
 *           पूर्णांक port           : port number (0 - 127)
 *
 *           वापस:    ..      : Tx buffer current मुक्त space
 *
 *
 *      Function 26:    Get the Rx buffer current queued data bytes
 *      Syntax:
 *      पूर्णांक  MoxaPortRxQueue(पूर्णांक port);
 *           पूर्णांक port           : port number (0 - 127)
 *
 *           वापस:    ..      : Rx buffer current queued data bytes
 *
 *
 *      Function 28:    Disable port data transmission.
 *      Syntax:
 *      व्योम MoxaPortTxDisable(पूर्णांक port);
 *           पूर्णांक port           : port number (0 - 127)
 *
 *
 *      Function 29:    Enable port data transmission.
 *      Syntax:
 *      व्योम MoxaPortTxEnable(पूर्णांक port);
 *           पूर्णांक port           : port number (0 - 127)
 *
 *
 *      Function 31:    Get the received BREAK संकेत count and reset it.
 *      Syntax:
 *      पूर्णांक  MoxaPortResetBrkCnt(पूर्णांक port);
 *           पूर्णांक port           : port number (0 - 127)
 *
 *           वापस:    0 - ..  : BREAK संकेत count
 *
 *
 */

अटल व्योम MoxaPortEnable(काष्ठा moxa_port *port)
अणु
	व्योम __iomem *ofsAddr;
	u16 lowwater = 512;

	ofsAddr = port->tableAddr;
	ग_लिखोw(lowwater, ofsAddr + Low_water);
	अगर (MOXA_IS_320(port->board))
		moxafunc(ofsAddr, FC_SetBreakIrq, 0);
	अन्यथा
		ग_लिखोw(पढ़ोw(ofsAddr + HostStat) | WakeupBreak,
				ofsAddr + HostStat);

	moxafunc(ofsAddr, FC_SetLineIrq, Magic_code);
	moxafunc(ofsAddr, FC_FlushQueue, 2);

	moxafunc(ofsAddr, FC_EnableCH, Magic_code);
	MoxaPortLineStatus(port);
पूर्ण

अटल व्योम MoxaPortDisable(काष्ठा moxa_port *port)
अणु
	व्योम __iomem *ofsAddr = port->tableAddr;

	moxafunc(ofsAddr, FC_SetFlowCtl, 0);	/* disable flow control */
	moxafunc(ofsAddr, FC_ClrLineIrq, Magic_code);
	ग_लिखोw(0, ofsAddr + HostStat);
	moxafunc(ofsAddr, FC_DisableCH, Magic_code);
पूर्ण

अटल speed_t MoxaPortSetBaud(काष्ठा moxa_port *port, speed_t baud)
अणु
	व्योम __iomem *ofsAddr = port->tableAddr;
	अचिन्हित पूर्णांक घड़ी, val;
	speed_t max;

	max = MOXA_IS_320(port->board) ? 460800 : 921600;
	अगर (baud < 50)
		वापस 0;
	अगर (baud > max)
		baud = max;
	घड़ी = 921600;
	val = घड़ी / baud;
	moxafunc(ofsAddr, FC_SetBaud, val);
	baud = घड़ी / val;
	वापस baud;
पूर्ण

अटल पूर्णांक MoxaPortSetTermio(काष्ठा moxa_port *port, काष्ठा ktermios *termio,
		speed_t baud)
अणु
	व्योम __iomem *ofsAddr;
	tcflag_t mode = 0;

	ofsAddr = port->tableAddr;

	mode = termio->c_cflag & CSIZE;
	अगर (mode == CS5)
		mode = MX_CS5;
	अन्यथा अगर (mode == CS6)
		mode = MX_CS6;
	अन्यथा अगर (mode == CS7)
		mode = MX_CS7;
	अन्यथा अगर (mode == CS8)
		mode = MX_CS8;

	अगर (termio->c_cflag & CSTOPB) अणु
		अगर (mode == MX_CS5)
			mode |= MX_STOP15;
		अन्यथा
			mode |= MX_STOP2;
	पूर्ण अन्यथा
		mode |= MX_STOP1;

	अगर (termio->c_cflag & PARENB) अणु
		अगर (termio->c_cflag & PARODD) अणु
			अगर (termio->c_cflag & CMSPAR)
				mode |= MX_PARMARK;
			अन्यथा
				mode |= MX_PARODD;
		पूर्ण अन्यथा अणु
			अगर (termio->c_cflag & CMSPAR)
				mode |= MX_PARSPACE;
			अन्यथा
				mode |= MX_PAREVEN;
		पूर्ण
	पूर्ण अन्यथा
		mode |= MX_PARNONE;

	moxafunc(ofsAddr, FC_SetDataMode, (u16)mode);

	अगर (MOXA_IS_320(port->board) && baud >= 921600)
		वापस -1;

	baud = MoxaPortSetBaud(port, baud);

	अगर (termio->c_अगरlag & (IXON | IXOFF | IXANY)) अणु
	        spin_lock_irq(&moxafunc_lock);
		ग_लिखोb(termio->c_cc[VSTART], ofsAddr + FuncArg);
		ग_लिखोb(termio->c_cc[VSTOP], ofsAddr + FuncArg1);
		ग_लिखोb(FC_SetXonXoff, ofsAddr + FuncCode);
		moxa_रुको_finish(ofsAddr);
		spin_unlock_irq(&moxafunc_lock);

	पूर्ण
	वापस baud;
पूर्ण

अटल पूर्णांक MoxaPortGetLineOut(काष्ठा moxa_port *port, पूर्णांक *dtrState,
		पूर्णांक *rtsState)
अणु
	अगर (dtrState)
		*dtrState = !!(port->lineCtrl & DTR_ON);
	अगर (rtsState)
		*rtsState = !!(port->lineCtrl & RTS_ON);

	वापस 0;
पूर्ण

अटल व्योम MoxaPortLineCtrl(काष्ठा moxa_port *port, पूर्णांक dtr, पूर्णांक rts)
अणु
	u8 mode = 0;

	अगर (dtr)
		mode |= DTR_ON;
	अगर (rts)
		mode |= RTS_ON;
	port->lineCtrl = mode;
	moxafunc(port->tableAddr, FC_LineControl, mode);
पूर्ण

अटल व्योम MoxaPortFlowCtrl(काष्ठा moxa_port *port, पूर्णांक rts, पूर्णांक cts,
		पूर्णांक txflow, पूर्णांक rxflow, पूर्णांक txany)
अणु
	पूर्णांक mode = 0;

	अगर (rts)
		mode |= RTS_FlowCtl;
	अगर (cts)
		mode |= CTS_FlowCtl;
	अगर (txflow)
		mode |= Tx_FlowCtl;
	अगर (rxflow)
		mode |= Rx_FlowCtl;
	अगर (txany)
		mode |= IXM_IXANY;
	moxafunc(port->tableAddr, FC_SetFlowCtl, mode);
पूर्ण

अटल पूर्णांक MoxaPortLineStatus(काष्ठा moxa_port *port)
अणु
	व्योम __iomem *ofsAddr;
	पूर्णांक val;

	ofsAddr = port->tableAddr;
	अगर (MOXA_IS_320(port->board))
		val = moxafuncret(ofsAddr, FC_LineStatus, 0);
	अन्यथा
		val = पढ़ोw(ofsAddr + FlagStat) >> 4;
	val &= 0x0B;
	अगर (val & 8)
		val |= 4;
	moxa_new_dcdstate(port, val & 8);
	val &= 7;
	वापस val;
पूर्ण

अटल पूर्णांक MoxaPortWriteData(काष्ठा tty_काष्ठा *tty,
		स्थिर अचिन्हित अक्षर *buffer, पूर्णांक len)
अणु
	काष्ठा moxa_port *port = tty->driver_data;
	व्योम __iomem *baseAddr, *ofsAddr, *ofs;
	अचिन्हित पूर्णांक c, total;
	u16 head, tail, tx_mask, spage, epage;
	u16 pageno, pageofs, bufhead;

	ofsAddr = port->tableAddr;
	baseAddr = port->board->basemem;
	tx_mask = पढ़ोw(ofsAddr + TX_mask);
	spage = पढ़ोw(ofsAddr + Page_txb);
	epage = पढ़ोw(ofsAddr + EndPage_txb);
	tail = पढ़ोw(ofsAddr + TXwptr);
	head = पढ़ोw(ofsAddr + TXrptr);
	c = (head > tail) ? (head - tail - 1) : (head - tail + tx_mask);
	अगर (c > len)
		c = len;
	moxaLog.txcnt[port->port.tty->index] += c;
	total = c;
	अगर (spage == epage) अणु
		bufhead = पढ़ोw(ofsAddr + Ofs_txb);
		ग_लिखोw(spage, baseAddr + Control_reg);
		जबतक (c > 0) अणु
			अगर (head > tail)
				len = head - tail - 1;
			अन्यथा
				len = tx_mask + 1 - tail;
			len = (c > len) ? len : c;
			ofs = baseAddr + DynPage_addr + bufhead + tail;
			स_नकल_toio(ofs, buffer, len);
			buffer += len;
			tail = (tail + len) & tx_mask;
			c -= len;
		पूर्ण
	पूर्ण अन्यथा अणु
		pageno = spage + (tail >> 13);
		pageofs = tail & Page_mask;
		जबतक (c > 0) अणु
			len = Page_size - pageofs;
			अगर (len > c)
				len = c;
			ग_लिखोb(pageno, baseAddr + Control_reg);
			ofs = baseAddr + DynPage_addr + pageofs;
			स_नकल_toio(ofs, buffer, len);
			buffer += len;
			अगर (++pageno == epage)
				pageno = spage;
			pageofs = 0;
			c -= len;
		पूर्ण
		tail = (tail + total) & tx_mask;
	पूर्ण
	ग_लिखोw(tail, ofsAddr + TXwptr);
	ग_लिखोb(1, ofsAddr + CD180TXirq);	/* start to send */
	वापस total;
पूर्ण

अटल पूर्णांक MoxaPortReadData(काष्ठा moxa_port *port)
अणु
	काष्ठा tty_काष्ठा *tty = port->port.tty;
	अचिन्हित अक्षर *dst;
	व्योम __iomem *baseAddr, *ofsAddr, *ofs;
	अचिन्हित पूर्णांक count, len, total;
	u16 tail, rx_mask, spage, epage;
	u16 pageno, pageofs, bufhead, head;

	ofsAddr = port->tableAddr;
	baseAddr = port->board->basemem;
	head = पढ़ोw(ofsAddr + RXrptr);
	tail = पढ़ोw(ofsAddr + RXwptr);
	rx_mask = पढ़ोw(ofsAddr + RX_mask);
	spage = पढ़ोw(ofsAddr + Page_rxb);
	epage = पढ़ोw(ofsAddr + EndPage_rxb);
	count = (tail >= head) ? (tail - head) : (tail - head + rx_mask + 1);
	अगर (count == 0)
		वापस 0;

	total = count;
	moxaLog.rxcnt[tty->index] += total;
	अगर (spage == epage) अणु
		bufhead = पढ़ोw(ofsAddr + Ofs_rxb);
		ग_लिखोw(spage, baseAddr + Control_reg);
		जबतक (count > 0) अणु
			ofs = baseAddr + DynPage_addr + bufhead + head;
			len = (tail >= head) ? (tail - head) :
					(rx_mask + 1 - head);
			len = tty_prepare_flip_string(&port->port, &dst,
					min(len, count));
			स_नकल_fromio(dst, ofs, len);
			head = (head + len) & rx_mask;
			count -= len;
		पूर्ण
	पूर्ण अन्यथा अणु
		pageno = spage + (head >> 13);
		pageofs = head & Page_mask;
		जबतक (count > 0) अणु
			ग_लिखोw(pageno, baseAddr + Control_reg);
			ofs = baseAddr + DynPage_addr + pageofs;
			len = tty_prepare_flip_string(&port->port, &dst,
					min(Page_size - pageofs, count));
			स_नकल_fromio(dst, ofs, len);

			count -= len;
			pageofs = (pageofs + len) & Page_mask;
			अगर (pageofs == 0 && ++pageno == epage)
				pageno = spage;
		पूर्ण
		head = (head + total) & rx_mask;
	पूर्ण
	ग_लिखोw(head, ofsAddr + RXrptr);
	अगर (पढ़ोb(ofsAddr + FlagStat) & Xoff_state) अणु
		moxaLowWaterChk = 1;
		port->lowChkFlag = 1;
	पूर्ण
	वापस total;
पूर्ण


अटल पूर्णांक MoxaPortTxQueue(काष्ठा moxa_port *port)
अणु
	व्योम __iomem *ofsAddr = port->tableAddr;
	u16 rptr, wptr, mask;

	rptr = पढ़ोw(ofsAddr + TXrptr);
	wptr = पढ़ोw(ofsAddr + TXwptr);
	mask = पढ़ोw(ofsAddr + TX_mask);
	वापस (wptr - rptr) & mask;
पूर्ण

अटल पूर्णांक MoxaPortTxFree(काष्ठा moxa_port *port)
अणु
	व्योम __iomem *ofsAddr = port->tableAddr;
	u16 rptr, wptr, mask;

	rptr = पढ़ोw(ofsAddr + TXrptr);
	wptr = पढ़ोw(ofsAddr + TXwptr);
	mask = पढ़ोw(ofsAddr + TX_mask);
	वापस mask - ((wptr - rptr) & mask);
पूर्ण

अटल पूर्णांक MoxaPortRxQueue(काष्ठा moxa_port *port)
अणु
	व्योम __iomem *ofsAddr = port->tableAddr;
	u16 rptr, wptr, mask;

	rptr = पढ़ोw(ofsAddr + RXrptr);
	wptr = पढ़ोw(ofsAddr + RXwptr);
	mask = पढ़ोw(ofsAddr + RX_mask);
	वापस (wptr - rptr) & mask;
पूर्ण

अटल व्योम MoxaPortTxDisable(काष्ठा moxa_port *port)
अणु
	moxafunc(port->tableAddr, FC_SetXoffState, Magic_code);
पूर्ण

अटल व्योम MoxaPortTxEnable(काष्ठा moxa_port *port)
अणु
	moxafunc(port->tableAddr, FC_SetXonState, Magic_code);
पूर्ण

अटल पूर्णांक moxa_get_serial_info(काष्ठा tty_काष्ठा *tty,
		काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा moxa_port *info = tty->driver_data;

	अगर (tty->index == MAX_PORTS)
		वापस -EINVAL;
	अगर (!info)
		वापस -ENODEV;
	mutex_lock(&info->port.mutex);
	ss->type = info->type,
	ss->line = info->port.tty->index,
	ss->flags = info->port.flags,
	ss->baud_base = 921600,
	ss->बंद_delay = jअगरfies_to_msecs(info->port.बंद_delay) / 10;
	mutex_unlock(&info->port.mutex);
	वापस 0;
पूर्ण


अटल पूर्णांक moxa_set_serial_info(काष्ठा tty_काष्ठा *tty,
		काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा moxa_port *info = tty->driver_data;
	अचिन्हित पूर्णांक बंद_delay;

	अगर (tty->index == MAX_PORTS)
		वापस -EINVAL;
	अगर (!info)
		वापस -ENODEV;

	बंद_delay = msecs_to_jअगरfies(ss->बंद_delay * 10);

	mutex_lock(&info->port.mutex);
	अगर (!capable(CAP_SYS_ADMIN)) अणु
		अगर (बंद_delay != info->port.बंद_delay ||
		    ss->type != info->type ||
		    ((ss->flags & ~ASYNC_USR_MASK) !=
		     (info->port.flags & ~ASYNC_USR_MASK))) अणु
			mutex_unlock(&info->port.mutex);
			वापस -EPERM;
		पूर्ण
	पूर्ण अन्यथा अणु
		info->port.बंद_delay = बंद_delay;

		MoxaSetFअगरo(info, ss->type == PORT_16550A);

		info->type = ss->type;
	पूर्ण
	mutex_unlock(&info->port.mutex);
	वापस 0;
पूर्ण



/*****************************************************************************
 *	Static local functions: 					     *
 *****************************************************************************/

अटल व्योम MoxaSetFअगरo(काष्ठा moxa_port *port, पूर्णांक enable)
अणु
	व्योम __iomem *ofsAddr = port->tableAddr;

	अगर (!enable) अणु
		moxafunc(ofsAddr, FC_SetRxFIFOTrig, 0);
		moxafunc(ofsAddr, FC_SetTxFIFOCnt, 1);
	पूर्ण अन्यथा अणु
		moxafunc(ofsAddr, FC_SetRxFIFOTrig, 3);
		moxafunc(ofsAddr, FC_SetTxFIFOCnt, 16);
	पूर्ण
पूर्ण
