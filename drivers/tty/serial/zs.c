<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * zs.c: Serial port driver क्रम IOASIC DECstations.
 *
 * Derived from drivers/sbus/अक्षर/sunserial.c by Paul Mackerras.
 * Derived from drivers/macपूर्णांकosh/macserial.c by Harald Koerfgen.
 *
 * DECstation changes
 * Copyright (C) 1998-2000 Harald Koerfgen
 * Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2007  Maciej W. Rozycki
 *
 * For the rest of the code the original Copyright applies:
 * Copyright (C) 1996 Paul Mackerras (Paul.Mackerras@cs.anu.edu.au)
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 *
 *
 * Note: क्रम IOASIC प्रणालीs the wiring is as follows:
 *
 * mouse/keyboard:
 * DIN-7 MJ-4  संकेत        SCC
 * 2     1     TxD       <-  A.TxD
 * 3     4     RxD       ->  A.RxD
 *
 * EIA-232/EIA-423:
 * DB-25 MMJ-6 संकेत        SCC
 * 2     2     TxD       <-  B.TxD
 * 3     5     RxD       ->  B.RxD
 * 4           RTS       <- ~A.RTS
 * 5           CTS       -> ~B.CTS
 * 6     6     DSR       -> ~A.SYNC
 * 8           CD        -> ~B.DCD
 * 12          DSRS(DCE) -> ~A.CTS  (*)
 * 15          TxC       ->  B.TxC
 * 17          RxC       ->  B.RxC
 * 20    1     DTR       <- ~A.DTR
 * 22          RI        -> ~A.DCD
 * 23          DSRS(DTE) <- ~B.RTS
 *
 * (*) EIA-232 defines the संकेत at this pin to be SCD, जबतक DSRS(DCE)
 *     is shared with DSRS(DTE) at pin 23.
 *
 * As you can immediately notice the wiring of the RTS, DTR and DSR संकेतs
 * is a bit odd.  This makes the handling of port B unnecessarily
 * complicated and prevents the use of some स्वतःmatic modes of operation.
 */

#समावेश <linux/bug.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/major.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/types.h>

#समावेश <linux/atomic.h>

#समावेश <यंत्र/dec/पूर्णांकerrupts.h>
#समावेश <यंत्र/dec/ioasic_addrs.h>
#समावेश <यंत्र/dec/प्रणाली.h>

#समावेश "zs.h"


MODULE_AUTHOR("Maciej W. Rozycki <macro@linux-mips.org>");
MODULE_DESCRIPTION("DECstation Z85C30 serial driver");
MODULE_LICENSE("GPL");


अटल अक्षर zs_name[] __initdata = "DECstation Z85C30 serial driver version ";
अटल अक्षर zs_version[] __initdata = "0.10";

/*
 * It would be nice to dynamically allocate everything that
 * depends on ZS_NUM_SCCS, so we could support any number of
 * Z85C30s, but क्रम now...
 */
#घोषणा ZS_NUM_SCCS	2		/* Max # of ZS chips supported.  */
#घोषणा ZS_NUM_CHAN	2		/* 2 channels per chip.  */
#घोषणा ZS_CHAN_A	0		/* Index of the channel A.  */
#घोषणा ZS_CHAN_B	1		/* Index of the channel B.  */
#घोषणा ZS_CHAN_IO_SIZE 8		/* IOMEM space size.  */
#घोषणा ZS_CHAN_IO_STRIDE 4		/* Register alignment.  */
#घोषणा ZS_CHAN_IO_OFFSET 1		/* The SCC resides on the high byte
					   of the 16-bit IOBUS.  */
#घोषणा ZS_CLOCK        7372800 	/* Z85C30 PCLK input घड़ी rate.  */

#घोषणा to_zport(uport) container_of(uport, काष्ठा zs_port, port)

काष्ठा zs_parms अणु
	resource_माप_प्रकार scc[ZS_NUM_SCCS];
	पूर्णांक irq[ZS_NUM_SCCS];
पूर्ण;

अटल काष्ठा zs_scc zs_sccs[ZS_NUM_SCCS];

अटल u8 zs_init_regs[ZS_NUM_REGS] __initdata = अणु
	0,				/* ग_लिखो 0 */
	PAR_SPEC,			/* ग_लिखो 1 */
	0,				/* ग_लिखो 2 */
	0,				/* ग_लिखो 3 */
	X16CLK | SB1,			/* ग_लिखो 4 */
	0,				/* ग_लिखो 5 */
	0, 0, 0,			/* ग_लिखो 6, 7, 8 */
	MIE | DLC | NV,			/* ग_लिखो 9 */
	NRZ,				/* ग_लिखो 10 */
	TCBR | RCBR,			/* ग_लिखो 11 */
	0, 0,				/* BRG समय स्थिरant, ग_लिखो 12 + 13 */
	BRSRC | BRENABL,		/* ग_लिखो 14 */
	0,				/* ग_लिखो 15 */
पूर्ण;

/*
 * Debugging.
 */
#अघोषित ZS_DEBUG_REGS


/*
 * Reading and writing Z85C30 रेजिस्टरs.
 */
अटल व्योम recovery_delay(व्योम)
अणु
	udelay(2);
पूर्ण

अटल u8 पढ़ो_zsreg(काष्ठा zs_port *zport, पूर्णांक reg)
अणु
	व्योम __iomem *control = zport->port.membase + ZS_CHAN_IO_OFFSET;
	u8 retval;

	अगर (reg != 0) अणु
		ग_लिखोb(reg & 0xf, control);
		fast_iob();
		recovery_delay();
	पूर्ण
	retval = पढ़ोb(control);
	recovery_delay();
	वापस retval;
पूर्ण

अटल व्योम ग_लिखो_zsreg(काष्ठा zs_port *zport, पूर्णांक reg, u8 value)
अणु
	व्योम __iomem *control = zport->port.membase + ZS_CHAN_IO_OFFSET;

	अगर (reg != 0) अणु
		ग_लिखोb(reg & 0xf, control);
		fast_iob(); recovery_delay();
	पूर्ण
	ग_लिखोb(value, control);
	fast_iob();
	recovery_delay();
	वापस;
पूर्ण

अटल u8 पढ़ो_zsdata(काष्ठा zs_port *zport)
अणु
	व्योम __iomem *data = zport->port.membase +
			     ZS_CHAN_IO_STRIDE + ZS_CHAN_IO_OFFSET;
	u8 retval;

	retval = पढ़ोb(data);
	recovery_delay();
	वापस retval;
पूर्ण

अटल व्योम ग_लिखो_zsdata(काष्ठा zs_port *zport, u8 value)
अणु
	व्योम __iomem *data = zport->port.membase +
			     ZS_CHAN_IO_STRIDE + ZS_CHAN_IO_OFFSET;

	ग_लिखोb(value, data);
	fast_iob();
	recovery_delay();
	वापस;
पूर्ण

#अगर_घोषित ZS_DEBUG_REGS
व्योम zs_dump(व्योम)
अणु
	काष्ठा zs_port *zport;
	पूर्णांक i, j;

	क्रम (i = 0; i < ZS_NUM_SCCS * ZS_NUM_CHAN; i++) अणु
		zport = &zs_sccs[i / ZS_NUM_CHAN].zport[i % ZS_NUM_CHAN];

		अगर (!zport->scc)
			जारी;

		क्रम (j = 0; j < 16; j++)
			prपूर्णांकk("W%-2d = 0x%02x\t", j, zport->regs[j]);
		prपूर्णांकk("\n");
		क्रम (j = 0; j < 16; j++)
			prपूर्णांकk("R%-2d = 0x%02x\t", j, पढ़ो_zsreg(zport, j));
		prपूर्णांकk("\n\n");
	पूर्ण
पूर्ण
#पूर्ण_अगर


अटल व्योम zs_spin_lock_cond_irq(spinlock_t *lock, पूर्णांक irq)
अणु
	अगर (irq)
		spin_lock_irq(lock);
	अन्यथा
		spin_lock(lock);
पूर्ण

अटल व्योम zs_spin_unlock_cond_irq(spinlock_t *lock, पूर्णांक irq)
अणु
	अगर (irq)
		spin_unlock_irq(lock);
	अन्यथा
		spin_unlock(lock);
पूर्ण

अटल पूर्णांक zs_receive_drain(काष्ठा zs_port *zport)
अणु
	पूर्णांक loops = 10000;

	जबतक ((पढ़ो_zsreg(zport, R0) & Rx_CH_AV) && --loops)
		पढ़ो_zsdata(zport);
	वापस loops;
पूर्ण

अटल पूर्णांक zs_transmit_drain(काष्ठा zs_port *zport, पूर्णांक irq)
अणु
	काष्ठा zs_scc *scc = zport->scc;
	पूर्णांक loops = 10000;

	जबतक (!(पढ़ो_zsreg(zport, R0) & Tx_BUF_EMP) && --loops) अणु
		zs_spin_unlock_cond_irq(&scc->zlock, irq);
		udelay(2);
		zs_spin_lock_cond_irq(&scc->zlock, irq);
	पूर्ण
	वापस loops;
पूर्ण

अटल पूर्णांक zs_line_drain(काष्ठा zs_port *zport, पूर्णांक irq)
अणु
	काष्ठा zs_scc *scc = zport->scc;
	पूर्णांक loops = 10000;

	जबतक (!(पढ़ो_zsreg(zport, R1) & ALL_SNT) && --loops) अणु
		zs_spin_unlock_cond_irq(&scc->zlock, irq);
		udelay(2);
		zs_spin_lock_cond_irq(&scc->zlock, irq);
	पूर्ण
	वापस loops;
पूर्ण


अटल व्योम load_zsregs(काष्ठा zs_port *zport, u8 *regs, पूर्णांक irq)
अणु
	/* Let the current transmission finish.  */
	zs_line_drain(zport, irq);
	/* Load 'em up.  */
	ग_लिखो_zsreg(zport, R3, regs[3] & ~RxENABLE);
	ग_लिखो_zsreg(zport, R5, regs[5] & ~TxENAB);
	ग_लिखो_zsreg(zport, R4, regs[4]);
	ग_लिखो_zsreg(zport, R9, regs[9]);
	ग_लिखो_zsreg(zport, R1, regs[1]);
	ग_लिखो_zsreg(zport, R2, regs[2]);
	ग_लिखो_zsreg(zport, R10, regs[10]);
	ग_लिखो_zsreg(zport, R14, regs[14] & ~BRENABL);
	ग_लिखो_zsreg(zport, R11, regs[11]);
	ग_लिखो_zsreg(zport, R12, regs[12]);
	ग_लिखो_zsreg(zport, R13, regs[13]);
	ग_लिखो_zsreg(zport, R14, regs[14]);
	ग_लिखो_zsreg(zport, R15, regs[15]);
	अगर (regs[3] & RxENABLE)
		ग_लिखो_zsreg(zport, R3, regs[3]);
	अगर (regs[5] & TxENAB)
		ग_लिखो_zsreg(zport, R5, regs[5]);
	वापस;
पूर्ण


/*
 * Status handling routines.
 */

/*
 * zs_tx_empty() -- get the transmitter empty status
 *
 * Purpose: Let user call ioctl() to get info when the UART physically
 * 	    is emptied.  On bus types like RS485, the transmitter must
 * 	    release the bus after transmitting.  This must be करोne when
 * 	    the transmit shअगरt रेजिस्टर is empty, not be करोne when the
 * 	    transmit holding रेजिस्टर is empty.  This functionality
 * 	    allows an RS485 driver to be written in user space.
 */
अटल अचिन्हित पूर्णांक zs_tx_empty(काष्ठा uart_port *uport)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	काष्ठा zs_scc *scc = zport->scc;
	अचिन्हित दीर्घ flags;
	u8 status;

	spin_lock_irqsave(&scc->zlock, flags);
	status = पढ़ो_zsreg(zport, R1);
	spin_unlock_irqrestore(&scc->zlock, flags);

	वापस status & ALL_SNT ? TIOCSER_TEMT : 0;
पूर्ण

अटल अचिन्हित पूर्णांक zs_raw_get_ab_mctrl(काष्ठा zs_port *zport_a,
					काष्ठा zs_port *zport_b)
अणु
	u8 status_a, status_b;
	अचिन्हित पूर्णांक mctrl;

	status_a = पढ़ो_zsreg(zport_a, R0);
	status_b = पढ़ो_zsreg(zport_b, R0);

	mctrl = ((status_b & CTS) ? TIOCM_CTS : 0) |
		((status_b & DCD) ? TIOCM_CAR : 0) |
		((status_a & DCD) ? TIOCM_RNG : 0) |
		((status_a & SYNC_HUNT) ? TIOCM_DSR : 0);

	वापस mctrl;
पूर्ण

अटल अचिन्हित पूर्णांक zs_raw_get_mctrl(काष्ठा zs_port *zport)
अणु
	काष्ठा zs_port *zport_a = &zport->scc->zport[ZS_CHAN_A];

	वापस zport != zport_a ? zs_raw_get_ab_mctrl(zport_a, zport) : 0;
पूर्ण

अटल अचिन्हित पूर्णांक zs_raw_xor_mctrl(काष्ठा zs_port *zport)
अणु
	काष्ठा zs_port *zport_a = &zport->scc->zport[ZS_CHAN_A];
	अचिन्हित पूर्णांक mmask, mctrl, delta;
	u8 mask_a, mask_b;

	अगर (zport == zport_a)
		वापस 0;

	mask_a = zport_a->regs[15];
	mask_b = zport->regs[15];

	mmask = ((mask_b & CTSIE) ? TIOCM_CTS : 0) |
		((mask_b & DCDIE) ? TIOCM_CAR : 0) |
		((mask_a & DCDIE) ? TIOCM_RNG : 0) |
		((mask_a & SYNCIE) ? TIOCM_DSR : 0);

	mctrl = zport->mctrl;
	अगर (mmask) अणु
		mctrl &= ~mmask;
		mctrl |= zs_raw_get_ab_mctrl(zport_a, zport) & mmask;
	पूर्ण

	delta = mctrl ^ zport->mctrl;
	अगर (delta)
		zport->mctrl = mctrl;

	वापस delta;
पूर्ण

अटल अचिन्हित पूर्णांक zs_get_mctrl(काष्ठा uart_port *uport)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	काष्ठा zs_scc *scc = zport->scc;
	अचिन्हित पूर्णांक mctrl;

	spin_lock(&scc->zlock);
	mctrl = zs_raw_get_mctrl(zport);
	spin_unlock(&scc->zlock);

	वापस mctrl;
पूर्ण

अटल व्योम zs_set_mctrl(काष्ठा uart_port *uport, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	काष्ठा zs_scc *scc = zport->scc;
	काष्ठा zs_port *zport_a = &scc->zport[ZS_CHAN_A];
	u8 oldloop, newloop;

	spin_lock(&scc->zlock);
	अगर (zport != zport_a) अणु
		अगर (mctrl & TIOCM_DTR)
			zport_a->regs[5] |= DTR;
		अन्यथा
			zport_a->regs[5] &= ~DTR;
		अगर (mctrl & TIOCM_RTS)
			zport_a->regs[5] |= RTS;
		अन्यथा
			zport_a->regs[5] &= ~RTS;
		ग_लिखो_zsreg(zport_a, R5, zport_a->regs[5]);
	पूर्ण

	/* Rarely modअगरied, so करोn't poke at hardware unless necessary. */
	oldloop = zport->regs[14];
	newloop = oldloop;
	अगर (mctrl & TIOCM_LOOP)
		newloop |= LOOPBAK;
	अन्यथा
		newloop &= ~LOOPBAK;
	अगर (newloop != oldloop) अणु
		zport->regs[14] = newloop;
		ग_लिखो_zsreg(zport, R14, zport->regs[14]);
	पूर्ण
	spin_unlock(&scc->zlock);
पूर्ण

अटल व्योम zs_raw_stop_tx(काष्ठा zs_port *zport)
अणु
	ग_लिखो_zsreg(zport, R0, RES_Tx_P);
	zport->tx_stopped = 1;
पूर्ण

अटल व्योम zs_stop_tx(काष्ठा uart_port *uport)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	काष्ठा zs_scc *scc = zport->scc;

	spin_lock(&scc->zlock);
	zs_raw_stop_tx(zport);
	spin_unlock(&scc->zlock);
पूर्ण

अटल व्योम zs_raw_transmit_अक्षरs(काष्ठा zs_port *);

अटल व्योम zs_start_tx(काष्ठा uart_port *uport)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	काष्ठा zs_scc *scc = zport->scc;

	spin_lock(&scc->zlock);
	अगर (zport->tx_stopped) अणु
		zs_transmit_drain(zport, 0);
		zport->tx_stopped = 0;
		zs_raw_transmit_अक्षरs(zport);
	पूर्ण
	spin_unlock(&scc->zlock);
पूर्ण

अटल व्योम zs_stop_rx(काष्ठा uart_port *uport)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	काष्ठा zs_scc *scc = zport->scc;
	काष्ठा zs_port *zport_a = &scc->zport[ZS_CHAN_A];

	spin_lock(&scc->zlock);
	zport->regs[15] &= ~BRKIE;
	zport->regs[1] &= ~(RxINT_MASK | TxINT_ENAB);
	zport->regs[1] |= RxINT_DISAB;

	अगर (zport != zport_a) अणु
		/* A-side DCD tracks RI and SYNC tracks DSR.  */
		zport_a->regs[15] &= ~(DCDIE | SYNCIE);
		ग_लिखो_zsreg(zport_a, R15, zport_a->regs[15]);
		अगर (!(zport_a->regs[15] & BRKIE)) अणु
			zport_a->regs[1] &= ~EXT_INT_ENAB;
			ग_लिखो_zsreg(zport_a, R1, zport_a->regs[1]);
		पूर्ण

		/* This-side DCD tracks DCD and CTS tracks CTS.  */
		zport->regs[15] &= ~(DCDIE | CTSIE);
		zport->regs[1] &= ~EXT_INT_ENAB;
	पूर्ण अन्यथा अणु
		/* DCD tracks RI and SYNC tracks DSR क्रम the B side.  */
		अगर (!(zport->regs[15] & (DCDIE | SYNCIE)))
			zport->regs[1] &= ~EXT_INT_ENAB;
	पूर्ण

	ग_लिखो_zsreg(zport, R15, zport->regs[15]);
	ग_लिखो_zsreg(zport, R1, zport->regs[1]);
	spin_unlock(&scc->zlock);
पूर्ण

अटल व्योम zs_enable_ms(काष्ठा uart_port *uport)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	काष्ठा zs_scc *scc = zport->scc;
	काष्ठा zs_port *zport_a = &scc->zport[ZS_CHAN_A];

	अगर (zport == zport_a)
		वापस;

	spin_lock(&scc->zlock);

	/* Clear Ext पूर्णांकerrupts अगर not being handled alपढ़ोy.  */
	अगर (!(zport_a->regs[1] & EXT_INT_ENAB))
		ग_लिखो_zsreg(zport_a, R0, RES_EXT_INT);

	/* A-side DCD tracks RI and SYNC tracks DSR.  */
	zport_a->regs[1] |= EXT_INT_ENAB;
	zport_a->regs[15] |= DCDIE | SYNCIE;

	/* This-side DCD tracks DCD and CTS tracks CTS.  */
	zport->regs[15] |= DCDIE | CTSIE;

	zs_raw_xor_mctrl(zport);

	ग_लिखो_zsreg(zport_a, R1, zport_a->regs[1]);
	ग_लिखो_zsreg(zport_a, R15, zport_a->regs[15]);
	ग_लिखो_zsreg(zport, R15, zport->regs[15]);
	spin_unlock(&scc->zlock);
पूर्ण

अटल व्योम zs_अवरोध_ctl(काष्ठा uart_port *uport, पूर्णांक अवरोध_state)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	काष्ठा zs_scc *scc = zport->scc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&scc->zlock, flags);
	अगर (अवरोध_state == -1)
		zport->regs[5] |= SND_BRK;
	अन्यथा
		zport->regs[5] &= ~SND_BRK;
	ग_लिखो_zsreg(zport, R5, zport->regs[5]);
	spin_unlock_irqrestore(&scc->zlock, flags);
पूर्ण


/*
 * Interrupt handling routines.
 */
#घोषणा Rx_BRK 0x0100			/* BREAK event software flag.  */
#घोषणा Rx_SYS 0x0200			/* SysRq event software flag.  */

अटल व्योम zs_receive_अक्षरs(काष्ठा zs_port *zport)
अणु
	काष्ठा uart_port *uport = &zport->port;
	काष्ठा zs_scc *scc = zport->scc;
	काष्ठा uart_icount *icount;
	अचिन्हित पूर्णांक avail, status, ch, flag;
	पूर्णांक count;

	क्रम (count = 16; count; count--) अणु
		spin_lock(&scc->zlock);
		avail = पढ़ो_zsreg(zport, R0) & Rx_CH_AV;
		spin_unlock(&scc->zlock);
		अगर (!avail)
			अवरोध;

		spin_lock(&scc->zlock);
		status = पढ़ो_zsreg(zport, R1) & (Rx_OVR | FRM_ERR | PAR_ERR);
		ch = पढ़ो_zsdata(zport);
		spin_unlock(&scc->zlock);

		flag = TTY_NORMAL;

		icount = &uport->icount;
		icount->rx++;

		/* Handle the null अक्षर got when BREAK is हटाओd.  */
		अगर (!ch)
			status |= zport->tty_अवरोध;
		अगर (unlikely(status &
			     (Rx_OVR | FRM_ERR | PAR_ERR | Rx_SYS | Rx_BRK))) अणु
			zport->tty_अवरोध = 0;

			/* Reset the error indication.  */
			अगर (status & (Rx_OVR | FRM_ERR | PAR_ERR)) अणु
				spin_lock(&scc->zlock);
				ग_लिखो_zsreg(zport, R0, ERR_RES);
				spin_unlock(&scc->zlock);
			पूर्ण

			अगर (status & (Rx_SYS | Rx_BRK)) अणु
				icount->brk++;
				/* SysRq discards the null अक्षर.  */
				अगर (status & Rx_SYS)
					जारी;
			पूर्ण अन्यथा अगर (status & FRM_ERR)
				icount->frame++;
			अन्यथा अगर (status & PAR_ERR)
				icount->parity++;
			अगर (status & Rx_OVR)
				icount->overrun++;

			status &= uport->पढ़ो_status_mask;
			अगर (status & Rx_BRK)
				flag = TTY_BREAK;
			अन्यथा अगर (status & FRM_ERR)
				flag = TTY_FRAME;
			अन्यथा अगर (status & PAR_ERR)
				flag = TTY_PARITY;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(uport, ch))
			जारी;

		uart_insert_अक्षर(uport, status, Rx_OVR, ch, flag);
	पूर्ण

	tty_flip_buffer_push(&uport->state->port);
पूर्ण

अटल व्योम zs_raw_transmit_अक्षरs(काष्ठा zs_port *zport)
अणु
	काष्ठा circ_buf *xmit = &zport->port.state->xmit;

	/* XON/XOFF अक्षरs.  */
	अगर (zport->port.x_अक्षर) अणु
		ग_लिखो_zsdata(zport, zport->port.x_अक्षर);
		zport->port.icount.tx++;
		zport->port.x_अक्षर = 0;
		वापस;
	पूर्ण

	/* If nothing to करो or stopped or hardware stopped.  */
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(&zport->port)) अणु
		zs_raw_stop_tx(zport);
		वापस;
	पूर्ण

	/* Send अक्षर.  */
	ग_लिखो_zsdata(zport, xmit->buf[xmit->tail]);
	xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
	zport->port.icount.tx++;

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&zport->port);

	/* Are we are करोne?  */
	अगर (uart_circ_empty(xmit))
		zs_raw_stop_tx(zport);
पूर्ण

अटल व्योम zs_transmit_अक्षरs(काष्ठा zs_port *zport)
अणु
	काष्ठा zs_scc *scc = zport->scc;

	spin_lock(&scc->zlock);
	zs_raw_transmit_अक्षरs(zport);
	spin_unlock(&scc->zlock);
पूर्ण

अटल व्योम zs_status_handle(काष्ठा zs_port *zport, काष्ठा zs_port *zport_a)
अणु
	काष्ठा uart_port *uport = &zport->port;
	काष्ठा zs_scc *scc = zport->scc;
	अचिन्हित पूर्णांक delta;
	u8 status, brk;

	spin_lock(&scc->zlock);

	/* Get status from Read Register 0.  */
	status = पढ़ो_zsreg(zport, R0);

	अगर (zport->regs[15] & BRKIE) अणु
		brk = status & BRK_ABRT;
		अगर (brk && !zport->brk) अणु
			spin_unlock(&scc->zlock);
			अगर (uart_handle_अवरोध(uport))
				zport->tty_अवरोध = Rx_SYS;
			अन्यथा
				zport->tty_अवरोध = Rx_BRK;
			spin_lock(&scc->zlock);
		पूर्ण
		zport->brk = brk;
	पूर्ण

	अगर (zport != zport_a) अणु
		delta = zs_raw_xor_mctrl(zport);
		spin_unlock(&scc->zlock);

		अगर (delta & TIOCM_CTS)
			uart_handle_cts_change(uport,
					       zport->mctrl & TIOCM_CTS);
		अगर (delta & TIOCM_CAR)
			uart_handle_dcd_change(uport,
					       zport->mctrl & TIOCM_CAR);
		अगर (delta & TIOCM_RNG)
			uport->icount.dsr++;
		अगर (delta & TIOCM_DSR)
			uport->icount.rng++;

		अगर (delta)
			wake_up_पूर्णांकerruptible(&uport->state->port.delta_msr_रुको);

		spin_lock(&scc->zlock);
	पूर्ण

	/* Clear the status condition...  */
	ग_लिखो_zsreg(zport, R0, RES_EXT_INT);

	spin_unlock(&scc->zlock);
पूर्ण

/*
 * This is the Z85C30 driver's generic पूर्णांकerrupt routine.
 */
अटल irqवापस_t zs_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा zs_scc *scc = dev_id;
	काष्ठा zs_port *zport_a = &scc->zport[ZS_CHAN_A];
	काष्ठा zs_port *zport_b = &scc->zport[ZS_CHAN_B];
	irqवापस_t status = IRQ_NONE;
	u8 zs_पूर्णांकreg;
	पूर्णांक count;

	/*
	 * NOTE: The पढ़ो रेजिस्टर 3, which holds the irq status,
	 *       करोes so क्रम both channels on each chip.  Although
	 *       the status value itself must be पढ़ो from the A
	 *       channel and is only valid when पढ़ो from channel A.
	 *       Yes... broken hardware...
	 */
	क्रम (count = 16; count; count--) अणु
		spin_lock(&scc->zlock);
		zs_पूर्णांकreg = पढ़ो_zsreg(zport_a, R3);
		spin_unlock(&scc->zlock);
		अगर (!zs_पूर्णांकreg)
			अवरोध;

		/*
		 * We करो not like losing अक्षरacters, so we prioritise
		 * पूर्णांकerrupt sources a little bit dअगरferently than
		 * the SCC would, was it allowed to.
		 */
		अगर (zs_पूर्णांकreg & CHBRxIP)
			zs_receive_अक्षरs(zport_b);
		अगर (zs_पूर्णांकreg & CHARxIP)
			zs_receive_अक्षरs(zport_a);
		अगर (zs_पूर्णांकreg & CHBEXT)
			zs_status_handle(zport_b, zport_a);
		अगर (zs_पूर्णांकreg & CHAEXT)
			zs_status_handle(zport_a, zport_a);
		अगर (zs_पूर्णांकreg & CHBTxIP)
			zs_transmit_अक्षरs(zport_b);
		अगर (zs_पूर्णांकreg & CHATxIP)
			zs_transmit_अक्षरs(zport_a);

		status = IRQ_HANDLED;
	पूर्ण

	वापस status;
पूर्ण


/*
 * Finally, routines used to initialize the serial port.
 */
अटल पूर्णांक zs_startup(काष्ठा uart_port *uport)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	काष्ठा zs_scc *scc = zport->scc;
	अचिन्हित दीर्घ flags;
	पूर्णांक irq_guard;
	पूर्णांक ret;

	irq_guard = atomic_add_वापस(1, &scc->irq_guard);
	अगर (irq_guard == 1) अणु
		ret = request_irq(zport->port.irq, zs_पूर्णांकerrupt,
				  IRQF_SHARED, "scc", scc);
		अगर (ret) अणु
			atomic_add(-1, &scc->irq_guard);
			prपूर्णांकk(KERN_ERR "zs: can't get irq %d\n",
			       zport->port.irq);
			वापस ret;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&scc->zlock, flags);

	/* Clear the receive FIFO.  */
	zs_receive_drain(zport);

	/* Clear the पूर्णांकerrupt रेजिस्टरs.  */
	ग_लिखो_zsreg(zport, R0, ERR_RES);
	ग_लिखो_zsreg(zport, R0, RES_Tx_P);
	/* But Ext only अगर not being handled alपढ़ोy.  */
	अगर (!(zport->regs[1] & EXT_INT_ENAB))
		ग_लिखो_zsreg(zport, R0, RES_EXT_INT);

	/* Finally, enable sequencing and पूर्णांकerrupts.  */
	zport->regs[1] &= ~RxINT_MASK;
	zport->regs[1] |= RxINT_ALL | TxINT_ENAB | EXT_INT_ENAB;
	zport->regs[3] |= RxENABLE;
	zport->regs[15] |= BRKIE;
	ग_लिखो_zsreg(zport, R1, zport->regs[1]);
	ग_लिखो_zsreg(zport, R3, zport->regs[3]);
	ग_लिखो_zsreg(zport, R5, zport->regs[5]);
	ग_लिखो_zsreg(zport, R15, zport->regs[15]);

	/* Record the current state of RR0.  */
	zport->mctrl = zs_raw_get_mctrl(zport);
	zport->brk = पढ़ो_zsreg(zport, R0) & BRK_ABRT;

	zport->tx_stopped = 1;

	spin_unlock_irqrestore(&scc->zlock, flags);

	वापस 0;
पूर्ण

अटल व्योम zs_shutकरोwn(काष्ठा uart_port *uport)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	काष्ठा zs_scc *scc = zport->scc;
	अचिन्हित दीर्घ flags;
	पूर्णांक irq_guard;

	spin_lock_irqsave(&scc->zlock, flags);

	zport->regs[3] &= ~RxENABLE;
	ग_लिखो_zsreg(zport, R5, zport->regs[5]);
	ग_लिखो_zsreg(zport, R3, zport->regs[3]);

	spin_unlock_irqrestore(&scc->zlock, flags);

	irq_guard = atomic_add_वापस(-1, &scc->irq_guard);
	अगर (!irq_guard)
		मुक्त_irq(zport->port.irq, scc);
पूर्ण


अटल व्योम zs_reset(काष्ठा zs_port *zport)
अणु
	काष्ठा zs_scc *scc = zport->scc;
	पूर्णांक irq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&scc->zlock, flags);
	irq = !irqs_disabled_flags(flags);
	अगर (!scc->initialised) अणु
		/* Reset the poपूर्णांकer first, just in हाल...  */
		पढ़ो_zsreg(zport, R0);
		/* And let the current transmission finish.  */
		zs_line_drain(zport, irq);
		ग_लिखो_zsreg(zport, R9, FHWRES);
		udelay(10);
		ग_लिखो_zsreg(zport, R9, 0);
		scc->initialised = 1;
	पूर्ण
	load_zsregs(zport, zport->regs, irq);
	spin_unlock_irqrestore(&scc->zlock, flags);
पूर्ण

अटल व्योम zs_set_termios(काष्ठा uart_port *uport, काष्ठा ktermios *termios,
			   काष्ठा ktermios *old_termios)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	काष्ठा zs_scc *scc = zport->scc;
	काष्ठा zs_port *zport_a = &scc->zport[ZS_CHAN_A];
	पूर्णांक irq;
	अचिन्हित पूर्णांक baud, brg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&scc->zlock, flags);
	irq = !irqs_disabled_flags(flags);

	/* Byte size.  */
	zport->regs[3] &= ~RxNBITS_MASK;
	zport->regs[5] &= ~TxNBITS_MASK;
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		zport->regs[3] |= Rx5;
		zport->regs[5] |= Tx5;
		अवरोध;
	हाल CS6:
		zport->regs[3] |= Rx6;
		zport->regs[5] |= Tx6;
		अवरोध;
	हाल CS7:
		zport->regs[3] |= Rx7;
		zport->regs[5] |= Tx7;
		अवरोध;
	हाल CS8:
	शेष:
		zport->regs[3] |= Rx8;
		zport->regs[5] |= Tx8;
		अवरोध;
	पूर्ण

	/* Parity and stop bits.  */
	zport->regs[4] &= ~(XCLK_MASK | SB_MASK | PAR_ENA | PAR_EVEN);
	अगर (termios->c_cflag & CSTOPB)
		zport->regs[4] |= SB2;
	अन्यथा
		zport->regs[4] |= SB1;
	अगर (termios->c_cflag & PARENB)
		zport->regs[4] |= PAR_ENA;
	अगर (!(termios->c_cflag & PARODD))
		zport->regs[4] |= PAR_EVEN;
	चयन (zport->clk_mode) अणु
	हाल 64:
		zport->regs[4] |= X64CLK;
		अवरोध;
	हाल 32:
		zport->regs[4] |= X32CLK;
		अवरोध;
	हाल 16:
		zport->regs[4] |= X16CLK;
		अवरोध;
	हाल 1:
		zport->regs[4] |= X1CLK;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	baud = uart_get_baud_rate(uport, termios, old_termios, 0,
				  uport->uartclk / zport->clk_mode / 4);

	brg = ZS_BPS_TO_BRG(baud, uport->uartclk / zport->clk_mode);
	zport->regs[12] = brg & 0xff;
	zport->regs[13] = (brg >> 8) & 0xff;

	uart_update_समयout(uport, termios->c_cflag, baud);

	uport->पढ़ो_status_mask = Rx_OVR;
	अगर (termios->c_अगरlag & INPCK)
		uport->पढ़ो_status_mask |= FRM_ERR | PAR_ERR;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		uport->पढ़ो_status_mask |= Rx_BRK;

	uport->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		uport->ignore_status_mask |= FRM_ERR | PAR_ERR;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		uport->ignore_status_mask |= Rx_BRK;
		अगर (termios->c_अगरlag & IGNPAR)
			uport->ignore_status_mask |= Rx_OVR;
	पूर्ण

	अगर (termios->c_cflag & CREAD)
		zport->regs[3] |= RxENABLE;
	अन्यथा
		zport->regs[3] &= ~RxENABLE;

	अगर (zport != zport_a) अणु
		अगर (!(termios->c_cflag & CLOCAL)) अणु
			zport->regs[15] |= DCDIE;
		पूर्ण अन्यथा
			zport->regs[15] &= ~DCDIE;
		अगर (termios->c_cflag & CRTSCTS) अणु
			zport->regs[15] |= CTSIE;
		पूर्ण अन्यथा
			zport->regs[15] &= ~CTSIE;
		zs_raw_xor_mctrl(zport);
	पूर्ण

	/* Load up the new values.  */
	load_zsregs(zport, zport->regs, irq);

	spin_unlock_irqrestore(&scc->zlock, flags);
पूर्ण

/*
 * Hack alert!
 * Required solely so that the initial PROM-based console
 * works undisturbed in parallel with this one.
 */
अटल व्योम zs_pm(काष्ठा uart_port *uport, अचिन्हित पूर्णांक state,
		  अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा zs_port *zport = to_zport(uport);

	अगर (state < 3)
		zport->regs[5] |= TxENAB;
	अन्यथा
		zport->regs[5] &= ~TxENAB;
	ग_लिखो_zsreg(zport, R5, zport->regs[5]);
पूर्ण


अटल स्थिर अक्षर *zs_type(काष्ठा uart_port *uport)
अणु
	वापस "Z85C30 SCC";
पूर्ण

अटल व्योम zs_release_port(काष्ठा uart_port *uport)
अणु
	iounmap(uport->membase);
	uport->membase = 0;
	release_mem_region(uport->mapbase, ZS_CHAN_IO_SIZE);
पूर्ण

अटल पूर्णांक zs_map_port(काष्ठा uart_port *uport)
अणु
	अगर (!uport->membase)
		uport->membase = ioremap(uport->mapbase,
						 ZS_CHAN_IO_SIZE);
	अगर (!uport->membase) अणु
		prपूर्णांकk(KERN_ERR "zs: Cannot map MMIO\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक zs_request_port(काष्ठा uart_port *uport)
अणु
	पूर्णांक ret;

	अगर (!request_mem_region(uport->mapbase, ZS_CHAN_IO_SIZE, "scc")) अणु
		prपूर्णांकk(KERN_ERR "zs: Unable to reserve MMIO resource\n");
		वापस -EBUSY;
	पूर्ण
	ret = zs_map_port(uport);
	अगर (ret) अणु
		release_mem_region(uport->mapbase, ZS_CHAN_IO_SIZE);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम zs_config_port(काष्ठा uart_port *uport, पूर्णांक flags)
अणु
	काष्ठा zs_port *zport = to_zport(uport);

	अगर (flags & UART_CONFIG_TYPE) अणु
		अगर (zs_request_port(uport))
			वापस;

		uport->type = PORT_ZS;

		zs_reset(zport);
	पूर्ण
पूर्ण

अटल पूर्णांक zs_verअगरy_port(काष्ठा uart_port *uport, काष्ठा serial_काष्ठा *ser)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	पूर्णांक ret = 0;

	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_ZS)
		ret = -EINVAL;
	अगर (ser->irq != uport->irq)
		ret = -EINVAL;
	अगर (ser->baud_base != uport->uartclk / zport->clk_mode / 4)
		ret = -EINVAL;
	वापस ret;
पूर्ण


अटल स्थिर काष्ठा uart_ops zs_ops = अणु
	.tx_empty	= zs_tx_empty,
	.set_mctrl	= zs_set_mctrl,
	.get_mctrl	= zs_get_mctrl,
	.stop_tx	= zs_stop_tx,
	.start_tx	= zs_start_tx,
	.stop_rx	= zs_stop_rx,
	.enable_ms	= zs_enable_ms,
	.अवरोध_ctl	= zs_अवरोध_ctl,
	.startup	= zs_startup,
	.shutकरोwn	= zs_shutकरोwn,
	.set_termios	= zs_set_termios,
	.pm		= zs_pm,
	.type		= zs_type,
	.release_port	= zs_release_port,
	.request_port	= zs_request_port,
	.config_port	= zs_config_port,
	.verअगरy_port	= zs_verअगरy_port,
पूर्ण;

/*
 * Initialize Z85C30 port काष्ठाures.
 */
अटल पूर्णांक __init zs_probe_sccs(व्योम)
अणु
	अटल पूर्णांक probed;
	काष्ठा zs_parms zs_parms;
	पूर्णांक chip, side, irq;
	पूर्णांक n_chips = 0;
	पूर्णांक i;

	अगर (probed)
		वापस 0;

	irq = dec_पूर्णांकerrupt[DEC_IRQ_SCC0];
	अगर (irq >= 0) अणु
		zs_parms.scc[n_chips] = IOASIC_SCC0;
		zs_parms.irq[n_chips] = dec_पूर्णांकerrupt[DEC_IRQ_SCC0];
		n_chips++;
	पूर्ण
	irq = dec_पूर्णांकerrupt[DEC_IRQ_SCC1];
	अगर (irq >= 0) अणु
		zs_parms.scc[n_chips] = IOASIC_SCC1;
		zs_parms.irq[n_chips] = dec_पूर्णांकerrupt[DEC_IRQ_SCC1];
		n_chips++;
	पूर्ण
	अगर (!n_chips)
		वापस -ENXIO;

	probed = 1;

	क्रम (chip = 0; chip < n_chips; chip++) अणु
		spin_lock_init(&zs_sccs[chip].zlock);
		क्रम (side = 0; side < ZS_NUM_CHAN; side++) अणु
			काष्ठा zs_port *zport = &zs_sccs[chip].zport[side];
			काष्ठा uart_port *uport = &zport->port;

			zport->scc	= &zs_sccs[chip];
			zport->clk_mode	= 16;

			uport->has_sysrq = IS_ENABLED(CONFIG_SERIAL_ZS_CONSOLE);
			uport->irq	= zs_parms.irq[chip];
			uport->uartclk	= ZS_CLOCK;
			uport->fअगरosize	= 1;
			uport->iotype	= UPIO_MEM;
			uport->flags	= UPF_BOOT_AUTOCONF;
			uport->ops	= &zs_ops;
			uport->line	= chip * ZS_NUM_CHAN + side;
			uport->mapbase	= dec_kn_slot_base +
					  zs_parms.scc[chip] +
					  (side ^ ZS_CHAN_B) * ZS_CHAN_IO_SIZE;

			क्रम (i = 0; i < ZS_NUM_REGS; i++)
				zport->regs[i] = zs_init_regs[i];
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_SERIAL_ZS_CONSOLE
अटल व्योम zs_console_अक्षर_दो(काष्ठा uart_port *uport, पूर्णांक ch)
अणु
	काष्ठा zs_port *zport = to_zport(uport);
	काष्ठा zs_scc *scc = zport->scc;
	पूर्णांक irq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&scc->zlock, flags);
	irq = !irqs_disabled_flags(flags);
	अगर (zs_transmit_drain(zport, irq))
		ग_लिखो_zsdata(zport, ch);
	spin_unlock_irqrestore(&scc->zlock, flags);
पूर्ण

/*
 * Prपूर्णांक a string to the serial port trying not to disturb
 * any possible real use of the port...
 */
अटल व्योम zs_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
			     अचिन्हित पूर्णांक count)
अणु
	पूर्णांक chip = co->index / ZS_NUM_CHAN, side = co->index % ZS_NUM_CHAN;
	काष्ठा zs_port *zport = &zs_sccs[chip].zport[side];
	काष्ठा zs_scc *scc = zport->scc;
	अचिन्हित दीर्घ flags;
	u8 txपूर्णांक, txenb;
	पूर्णांक irq;

	/* Disable transmit पूर्णांकerrupts and enable the transmitter. */
	spin_lock_irqsave(&scc->zlock, flags);
	txपूर्णांक = zport->regs[1];
	txenb = zport->regs[5];
	अगर (txपूर्णांक & TxINT_ENAB) अणु
		zport->regs[1] = txपूर्णांक & ~TxINT_ENAB;
		ग_लिखो_zsreg(zport, R1, zport->regs[1]);
	पूर्ण
	अगर (!(txenb & TxENAB)) अणु
		zport->regs[5] = txenb | TxENAB;
		ग_लिखो_zsreg(zport, R5, zport->regs[5]);
	पूर्ण
	spin_unlock_irqrestore(&scc->zlock, flags);

	uart_console_ग_लिखो(&zport->port, s, count, zs_console_अक्षर_दो);

	/* Restore transmit पूर्णांकerrupts and the transmitter enable. */
	spin_lock_irqsave(&scc->zlock, flags);
	irq = !irqs_disabled_flags(flags);
	zs_line_drain(zport, irq);
	अगर (!(txenb & TxENAB)) अणु
		zport->regs[5] &= ~TxENAB;
		ग_लिखो_zsreg(zport, R5, zport->regs[5]);
	पूर्ण
	अगर (txपूर्णांक & TxINT_ENAB) अणु
		zport->regs[1] |= TxINT_ENAB;
		ग_लिखो_zsreg(zport, R1, zport->regs[1]);

		/* Resume any transmission as the TxIP bit won't be set.  */
		अगर (!zport->tx_stopped)
			zs_raw_transmit_अक्षरs(zport);
	पूर्ण
	spin_unlock_irqrestore(&scc->zlock, flags);
पूर्ण

/*
 * Setup serial console baud/bits/parity.  We करो two things here:
 * - स्थिरruct a cflag setting क्रम the first uart_खोलो()
 * - initialise the serial port
 * Return non-zero अगर we didn't find a serial port.
 */
अटल पूर्णांक __init zs_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	पूर्णांक chip = co->index / ZS_NUM_CHAN, side = co->index % ZS_NUM_CHAN;
	काष्ठा zs_port *zport = &zs_sccs[chip].zport[side];
	काष्ठा uart_port *uport = &zport->port;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret;

	ret = zs_map_port(uport);
	अगर (ret)
		वापस ret;

	zs_reset(zport);
	zs_pm(uport, 0, -1);

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	वापस uart_set_options(uport, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver zs_reg;
अटल काष्ठा console zs_console = अणु
	.name	= "ttyS",
	.ग_लिखो	= zs_console_ग_लिखो,
	.device	= uart_console_device,
	.setup	= zs_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
	.data	= &zs_reg,
पूर्ण;

/*
 *	Register console.
 */
अटल पूर्णांक __init zs_serial_console_init(व्योम)
अणु
	पूर्णांक ret;

	ret = zs_probe_sccs();
	अगर (ret)
		वापस ret;
	रेजिस्टर_console(&zs_console);

	वापस 0;
पूर्ण

console_initcall(zs_serial_console_init);

#घोषणा SERIAL_ZS_CONSOLE	&zs_console
#अन्यथा
#घोषणा SERIAL_ZS_CONSOLE	शून्य
#पूर्ण_अगर /* CONFIG_SERIAL_ZS_CONSOLE */

अटल काष्ठा uart_driver zs_reg = अणु
	.owner			= THIS_MODULE,
	.driver_name		= "serial",
	.dev_name		= "ttyS",
	.major			= TTY_MAJOR,
	.minor			= 64,
	.nr			= ZS_NUM_SCCS * ZS_NUM_CHAN,
	.cons			= SERIAL_ZS_CONSOLE,
पूर्ण;

/* zs_init inits the driver. */
अटल पूर्णांक __init zs_init(व्योम)
अणु
	पूर्णांक i, ret;

	pr_info("%s%s\n", zs_name, zs_version);

	/* Find out how many Z85C30 SCCs we have.  */
	ret = zs_probe_sccs();
	अगर (ret)
		वापस ret;

	ret = uart_रेजिस्टर_driver(&zs_reg);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ZS_NUM_SCCS * ZS_NUM_CHAN; i++) अणु
		काष्ठा zs_scc *scc = &zs_sccs[i / ZS_NUM_CHAN];
		काष्ठा zs_port *zport = &scc->zport[i % ZS_NUM_CHAN];
		काष्ठा uart_port *uport = &zport->port;

		अगर (zport->scc)
			uart_add_one_port(&zs_reg, uport);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास zs_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = ZS_NUM_SCCS * ZS_NUM_CHAN - 1; i >= 0; i--) अणु
		काष्ठा zs_scc *scc = &zs_sccs[i / ZS_NUM_CHAN];
		काष्ठा zs_port *zport = &scc->zport[i % ZS_NUM_CHAN];
		काष्ठा uart_port *uport = &zport->port;

		अगर (zport->scc)
			uart_हटाओ_one_port(&zs_reg, uport);
	पूर्ण

	uart_unरेजिस्टर_driver(&zs_reg);
पूर्ण

module_init(zs_init);
module_निकास(zs_निकास);
