<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*****************************************************************************/

/*
 *	baycom_ser_fdx.c  -- baycom ser12 fullduplex radio modem driver.
 *
 *	Copyright (C) 1996-2000  Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *
 *  Please note that the GPL allows you to use the driver, NOT the radio.
 *  In order to use the radio, you need a license from the communications
 *  authority of your country.
 *
 *  Supported modems
 *
 *  ser12:  This is a very simple 1200 baud AFSK modem. The modem consists only
 *          of a modulator/demodulator chip, usually a TI TCM3105. The computer
 *          is responsible क्रम regenerating the receiver bit घड़ी, as well as
 *          क्रम handling the HDLC protocol. The modem connects to a serial port,
 *          hence the name. Since the serial port is not used as an async serial
 *          port, the kernel driver क्रम serial ports cannot be used, and this
 *          driver only supports standard serial hardware (8250, 16450, 16550A)
 *
 *          This modem usually draws its supply current out of the otherwise unused
 *          TXD pin of the serial port. Thus a contiguous stream of 0x00-bytes
 *          is transmitted to achieve a positive supply voltage.
 *
 *  hsk:    This is a 4800 baud FSK modem, deचिन्हित क्रम TNC use. It works fine
 *          in 'baycom-mode' :-)  In contrast to the TCM3105 modem, घातer is
 *          बाह्यally supplied. So there's no need to provide the 0x00-byte-stream
 *          when receiving or idle, which drastically reduces पूर्णांकerrupt load.
 *
 *  Command line options (insmod command line)
 *
 *  mode     ser#    hardware DCD
 *           ser#*   software DCD
 *           ser#+   hardware DCD, inverted संकेत at DCD pin
 *           '#' denotes the baud rate / 100, eg. ser12* is '1200 baud, soft DCD'
 *  iobase   base address of the port; common values are 0x3f8, 0x2f8, 0x3e8, 0x2e8
 *  baud     baud rate (between 300 and 4800)
 *  irq      पूर्णांकerrupt line of the port; common values are 4,3
 *
 *  History:
 *   0.1  26.06.1996  Adapted from baycom.c and made network driver पूर्णांकerface
 *        18.10.1996  Changed to new user space access routines (copy_अणुto,fromपूर्ण_user)
 *   0.3  26.04.1997  init code/data tagged
 *   0.4  08.07.1997  alternative ser12 decoding algorithm (uses delta CTS पूर्णांकs)
 *   0.5  11.11.1997  ser12/par96 split पूर्णांकo separate files
 *   0.6  24.01.1998  Thorsten Kranzkowski, dl8bcu and Thomas Sailer:
 *                    reduced पूर्णांकerrupt load in transmit हाल
 *                    reworked receiver
 *   0.7  03.08.1999  adapt to Linus' new __setup/__initcall
 *   0.8  10.08.1999  use module_init/module_निकास
 *   0.9  12.02.2000  adapted to softnet driver पूर्णांकerface
 *   0.10 03.07.2000  fix पूर्णांकerface name handling
 */

/*****************************************************************************/

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/hdlcdrv.h>
#समावेश <linux/baycom.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समय64.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

/* --------------------------------------------------------------------- */

#घोषणा BAYCOM_DEBUG

/* --------------------------------------------------------------------- */

अटल स्थिर अक्षर bc_drvname[] = "baycom_ser_fdx";
अटल स्थिर अक्षर bc_drvinfo[] = KERN_INFO "baycom_ser_fdx: (C) 1996-2000 Thomas Sailer, HB9JNX/AE4WA\n"
"baycom_ser_fdx: version 0.10\n";

/* --------------------------------------------------------------------- */

#घोषणा NR_PORTS 4

अटल काष्ठा net_device *baycom_device[NR_PORTS];

/* --------------------------------------------------------------------- */

#घोषणा RBR(iobase) (iobase+0)
#घोषणा THR(iobase) (iobase+0)
#घोषणा IER(iobase) (iobase+1)
#घोषणा IIR(iobase) (iobase+2)
#घोषणा FCR(iobase) (iobase+2)
#घोषणा LCR(iobase) (iobase+3)
#घोषणा MCR(iobase) (iobase+4)
#घोषणा LSR(iobase) (iobase+5)
#घोषणा MSR(iobase) (iobase+6)
#घोषणा SCR(iobase) (iobase+7)
#घोषणा DLL(iobase) (iobase+0)
#घोषणा DLM(iobase) (iobase+1)

#घोषणा SER12_EXTENT 8

/* ---------------------------------------------------------------------- */
/*
 * Inक्रमmation that need to be kept क्रम each board.
 */

काष्ठा baycom_state अणु
	काष्ठा hdlcdrv_state hdrv;

	अचिन्हित पूर्णांक baud, baud_us, baud_arbभाग, baud_uartभाग, baud_dcdसमयout;
	पूर्णांक opt_dcd;

	काष्ठा modem_state अणु
		अचिन्हित अक्षर flags;
		अचिन्हित अक्षर ptt;
		अचिन्हित पूर्णांक shreg;
		काष्ठा modem_state_ser12 अणु
			अचिन्हित अक्षर tx_bit;
			अचिन्हित अक्षर last_rxbit;
			पूर्णांक dcd_sum0, dcd_sum1, dcd_sum2;
			पूर्णांक dcd_समय;
			अचिन्हित पूर्णांक pll_समय;
			अचिन्हित पूर्णांक txshreg;
		पूर्ण ser12;
	पूर्ण modem;

#अगर_घोषित BAYCOM_DEBUG
	काष्ठा debug_vals अणु
		अचिन्हित दीर्घ last_jअगरfies;
		अचिन्हित cur_पूर्णांकcnt;
		अचिन्हित last_पूर्णांकcnt;
		पूर्णांक cur_pllcorr;
		पूर्णांक last_pllcorr;
	पूर्ण debug_vals;
#पूर्ण_अगर /* BAYCOM_DEBUG */
पूर्ण;

/* --------------------------------------------------------------------- */

अटल अंतरभूत व्योम baycom_पूर्णांक_freq(काष्ठा baycom_state *bc)
अणु
#अगर_घोषित BAYCOM_DEBUG
	अचिन्हित दीर्घ cur_jअगरfies = jअगरfies;
	/*
	 * measure the पूर्णांकerrupt frequency
	 */
	bc->debug_vals.cur_पूर्णांकcnt++;
	अगर (समय_after_eq(cur_jअगरfies, bc->debug_vals.last_jअगरfies + HZ)) अणु
		bc->debug_vals.last_jअगरfies = cur_jअगरfies;
		bc->debug_vals.last_पूर्णांकcnt = bc->debug_vals.cur_पूर्णांकcnt;
		bc->debug_vals.cur_पूर्णांकcnt = 0;
		bc->debug_vals.last_pllcorr = bc->debug_vals.cur_pllcorr;
		bc->debug_vals.cur_pllcorr = 0;
	पूर्ण
#पूर्ण_अगर /* BAYCOM_DEBUG */
पूर्ण

/* --------------------------------------------------------------------- */
/*
 * ===================== SER12 specअगरic routines =========================
 */

/* --------------------------------------------------------------------- */

अटल अंतरभूत व्योम ser12_set_भागisor(काष्ठा net_device *dev,
                                     अचिन्हित पूर्णांक भागisor)
अणु
        outb(0x81, LCR(dev->base_addr));        /* DLAB = 1 */
        outb(भागisor, DLL(dev->base_addr));
        outb(भागisor >> 8, DLM(dev->base_addr));
        outb(0x01, LCR(dev->base_addr));        /* word length = 6 */
        /*
         * make sure the next पूर्णांकerrupt is generated;
         * 0 must be used to घातer the modem; the modem draws its
         * घातer from the TxD line
         */
        outb(0x00, THR(dev->base_addr));
        /*
         * it is important not to set the भागider जबतक transmitting;
         * this reportedly makes some UARTs generating पूर्णांकerrupts
         * in the hundredthousands per second region
         * Reported by: Ignacio.Arenaza@studi.epfl.ch (Ignacio Arenaza Nuno)
         */
पूर्ण

अटल __अंतरभूत__ व्योम ser12_rx(काष्ठा net_device *dev, काष्ठा baycom_state *bc, काष्ठा बारpec64 *ts, अचिन्हित अक्षर curs)
अणु
	पूर्णांक समयdअगरf;
	पूर्णांक bdus8 = bc->baud_us >> 3;
	पूर्णांक bdus4 = bc->baud_us >> 2;
	पूर्णांक bdus2 = bc->baud_us >> 1;

	समयdअगरf = 1000000 + ts->tv_nsec / NSEC_PER_USEC -
					bc->modem.ser12.pll_समय;
	जबतक (समयdअगरf >= 500000)
		समयdअगरf -= 1000000;
	जबतक (समयdअगरf >= bdus2) अणु
		समयdअगरf -= bc->baud_us;
		bc->modem.ser12.pll_समय += bc->baud_us;
		bc->modem.ser12.dcd_समय--;
		/* first check अगर there is room to add a bit */
		अगर (bc->modem.shreg & 1) अणु
			hdlcdrv_putbits(&bc->hdrv, (bc->modem.shreg >> 1) ^ 0xffff);
			bc->modem.shreg = 0x10000;
		पूर्ण
		/* add a one bit */
		bc->modem.shreg >>= 1;
	पूर्ण
	अगर (bc->modem.ser12.dcd_समय <= 0) अणु
		अगर (!bc->opt_dcd)
			hdlcdrv_setdcd(&bc->hdrv, (bc->modem.ser12.dcd_sum0 + 
						   bc->modem.ser12.dcd_sum1 + 
						   bc->modem.ser12.dcd_sum2) < 0);
		bc->modem.ser12.dcd_sum2 = bc->modem.ser12.dcd_sum1;
		bc->modem.ser12.dcd_sum1 = bc->modem.ser12.dcd_sum0;
		bc->modem.ser12.dcd_sum0 = 2; /* slight bias */
		bc->modem.ser12.dcd_समय += 120;
	पूर्ण
	अगर (bc->modem.ser12.last_rxbit != curs) अणु
		bc->modem.ser12.last_rxbit = curs;
		bc->modem.shreg |= 0x10000;
		/* adjust the PLL */
		अगर (समयdअगरf > 0)
			bc->modem.ser12.pll_समय += bdus8;
		अन्यथा
			bc->modem.ser12.pll_समय += 1000000 - bdus8;
		/* update DCD */
		अगर (असल(समयdअगरf) > bdus4)
			bc->modem.ser12.dcd_sum0 += 4;
		अन्यथा
			bc->modem.ser12.dcd_sum0--;
#अगर_घोषित BAYCOM_DEBUG
		bc->debug_vals.cur_pllcorr = समयdअगरf;
#पूर्ण_अगर /* BAYCOM_DEBUG */
	पूर्ण
	जबतक (bc->modem.ser12.pll_समय >= 1000000)
		bc->modem.ser12.pll_समय -= 1000000;
पूर्ण

/* --------------------------------------------------------------------- */

अटल irqवापस_t ser12_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा baycom_state *bc = netdev_priv(dev);
	काष्ठा बारpec64 ts;
	अचिन्हित अक्षर iir, msr;
	अचिन्हित पूर्णांक txcount = 0;

	अगर (!bc || bc->hdrv.magic != HDLCDRV_MAGIC)
		वापस IRQ_NONE;
	/* fast way out क्रम shared irq */
	अगर ((iir = inb(IIR(dev->base_addr))) & 1) 	
		वापस IRQ_NONE;
	/* get current समय */
	kसमय_get_ts64(&ts);
	msr = inb(MSR(dev->base_addr));
	/* delta DCD */
	अगर ((msr & 8) && bc->opt_dcd)
		hdlcdrv_setdcd(&bc->hdrv, !((msr ^ bc->opt_dcd) & 0x80));
	करो अणु
		चयन (iir & 6) अणु
		हाल 6:
			inb(LSR(dev->base_addr));
			अवरोध;
			
		हाल 4:
			inb(RBR(dev->base_addr));
			अवरोध;
			
		हाल 2:
			/*
			 * make sure the next पूर्णांकerrupt is generated;
			 * 0 must be used to घातer the modem; the modem draws its
			 * घातer from the TxD line
			 */
			outb(0x00, THR(dev->base_addr));
			baycom_पूर्णांक_freq(bc);
			txcount++;
			/*
			 * first output the last bit (!) then call HDLC transmitter,
			 * since this may take quite दीर्घ
			 */
			अगर (bc->modem.ptt)
				outb(0x0e | (!!bc->modem.ser12.tx_bit), MCR(dev->base_addr));
			अन्यथा
				outb(0x0d, MCR(dev->base_addr));       /* transmitter off */
			अवरोध;
			
		शेष:
			msr = inb(MSR(dev->base_addr));
			/* delta DCD */
			अगर ((msr & 8) && bc->opt_dcd) 
				hdlcdrv_setdcd(&bc->hdrv, !((msr ^ bc->opt_dcd) & 0x80));
			अवरोध;
		पूर्ण
		iir = inb(IIR(dev->base_addr));
	पूर्ण जबतक (!(iir & 1));
	ser12_rx(dev, bc, &ts, msr & 0x10); /* CTS */
	अगर (bc->modem.ptt && txcount) अणु
		अगर (bc->modem.ser12.txshreg <= 1) अणु
			bc->modem.ser12.txshreg = 0x10000 | hdlcdrv_getbits(&bc->hdrv);
			अगर (!hdlcdrv_ptt(&bc->hdrv)) अणु
				ser12_set_भागisor(dev, 115200/100/8);
				bc->modem.ptt = 0;
				जाओ end_transmit;
			पूर्ण
		पूर्ण
		bc->modem.ser12.tx_bit = !(bc->modem.ser12.tx_bit ^ (bc->modem.ser12.txshreg & 1));
		bc->modem.ser12.txshreg >>= 1;
	पूर्ण
 end_transmit:
	local_irq_enable();
	अगर (!bc->modem.ptt && txcount) अणु
		hdlcdrv_arbitrate(dev, &bc->hdrv);
		अगर (hdlcdrv_ptt(&bc->hdrv)) अणु
			ser12_set_भागisor(dev, bc->baud_uartभाग);
			bc->modem.ser12.txshreg = 1;
			bc->modem.ptt = 1;
		पूर्ण
	पूर्ण
	hdlcdrv_transmitter(dev, &bc->hdrv);
	hdlcdrv_receiver(dev, &bc->hdrv);
	local_irq_disable();
	वापस IRQ_HANDLED;
पूर्ण

/* --------------------------------------------------------------------- */

क्रमागत uart अणु c_uart_unknown, c_uart_8250,
	    c_uart_16450, c_uart_16550, c_uart_16550Aपूर्ण;
अटल स्थिर अक्षर *uart_str[] = अणु 
	"unknown", "8250", "16450", "16550", "16550A" 
पूर्ण;

अटल क्रमागत uart ser12_check_uart(अचिन्हित पूर्णांक iobase)
अणु
	अचिन्हित अक्षर b1,b2,b3;
	क्रमागत uart u;
	क्रमागत uart uart_tab[] =
		अणु c_uart_16450, c_uart_unknown, c_uart_16550, c_uart_16550A पूर्ण;

	b1 = inb(MCR(iobase));
	outb(b1 | 0x10, MCR(iobase));	/* loopback mode */
	b2 = inb(MSR(iobase));
	outb(0x1a, MCR(iobase));
	b3 = inb(MSR(iobase)) & 0xf0;
	outb(b1, MCR(iobase));			/* restore old values */
	outb(b2, MSR(iobase));
	अगर (b3 != 0x90)
		वापस c_uart_unknown;
	inb(RBR(iobase));
	inb(RBR(iobase));
	outb(0x01, FCR(iobase));		/* enable FIFOs */
	u = uart_tab[(inb(IIR(iobase)) >> 6) & 3];
	अगर (u == c_uart_16450) अणु
		outb(0x5a, SCR(iobase));
		b1 = inb(SCR(iobase));
		outb(0xa5, SCR(iobase));
		b2 = inb(SCR(iobase));
		अगर ((b1 != 0x5a) || (b2 != 0xa5))
			u = c_uart_8250;
	पूर्ण
	वापस u;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक ser12_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा baycom_state *bc = netdev_priv(dev);
	क्रमागत uart u;

	अगर (!dev || !bc)
		वापस -ENXIO;
	अगर (!dev->base_addr || dev->base_addr > 0xffff-SER12_EXTENT ||
	    dev->irq < 2 || dev->irq > nr_irqs) अणु
		prपूर्णांकk(KERN_INFO "baycom_ser_fdx: invalid portnumber (max %u) "
				"or irq (2 <= irq <= %d)\n",
				0xffff-SER12_EXTENT, nr_irqs);
		वापस -ENXIO;
	पूर्ण
	अगर (bc->baud < 300 || bc->baud > 4800) अणु
		prपूर्णांकk(KERN_INFO "baycom_ser_fdx: invalid baudrate "
				"(300...4800)\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!request_region(dev->base_addr, SER12_EXTENT, "baycom_ser_fdx")) अणु
		prपूर्णांकk(KERN_WARNING "BAYCOM_SER_FSX: I/O port 0x%04lx busy\n",
		       dev->base_addr);
		वापस -EACCES;
	पूर्ण
	स_रखो(&bc->modem, 0, माप(bc->modem));
	bc->hdrv.par.bitrate = bc->baud;
	bc->baud_us = 1000000/bc->baud;
	bc->baud_uartभाग = (115200/8)/bc->baud;
	अगर ((u = ser12_check_uart(dev->base_addr)) == c_uart_unknown)अणु
		release_region(dev->base_addr, SER12_EXTENT);
		वापस -EIO;
	पूर्ण
	outb(0, FCR(dev->base_addr));  /* disable FIFOs */
	outb(0x0d, MCR(dev->base_addr));
	outb(0, IER(dev->base_addr));
	अगर (request_irq(dev->irq, ser12_पूर्णांकerrupt, IRQF_SHARED,
			"baycom_ser_fdx", dev)) अणु
		release_region(dev->base_addr, SER12_EXTENT);
		वापस -EBUSY;
	पूर्ण
	/*
	 * set the SIO to 6 Bits/अक्षरacter; during receive,
	 * the baud rate is set to produce 100 पूर्णांकs/sec
	 * to feed the channel arbitration process,
	 * during transmit to baud पूर्णांकs/sec to run
	 * the transmitter
	 */
	ser12_set_भागisor(dev, 115200/100/8);
	/*
	 * enable transmitter empty पूर्णांकerrupt and modem status पूर्णांकerrupt
	 */
	outb(0x0a, IER(dev->base_addr));
	/*
	 * make sure the next पूर्णांकerrupt is generated;
	 * 0 must be used to घातer the modem; the modem draws its
	 * घातer from the TxD line
	 */
	outb(0x00, THR(dev->base_addr));
	hdlcdrv_setdcd(&bc->hdrv, 0);
	prपूर्णांकk(KERN_INFO "%s: ser_fdx at iobase 0x%lx irq %u baud %u uart %s\n",
	       bc_drvname, dev->base_addr, dev->irq, bc->baud, uart_str[u]);
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक ser12_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा baycom_state *bc = netdev_priv(dev);

	अगर (!dev || !bc)
		वापस -EINVAL;
	/*
	 * disable पूर्णांकerrupts
	 */
	outb(0, IER(dev->base_addr));
	outb(1, MCR(dev->base_addr));
	मुक्त_irq(dev->irq, dev);
	release_region(dev->base_addr, SER12_EXTENT);
	prपूर्णांकk(KERN_INFO "%s: close ser_fdx at iobase 0x%lx irq %u\n",
	       bc_drvname, dev->base_addr, dev->irq);
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */
/*
 * ===================== hdlcdrv driver पूर्णांकerface =========================
 */

/* --------------------------------------------------------------------- */

अटल पूर्णांक baycom_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr,
			काष्ठा hdlcdrv_ioctl *hi, पूर्णांक cmd);

/* --------------------------------------------------------------------- */

अटल स्थिर काष्ठा hdlcdrv_ops ser12_ops = अणु
	.drvname = bc_drvname,
	.drvinfo = bc_drvinfo,
	.खोलो    = ser12_खोलो,
	.बंद   = ser12_बंद,
	.ioctl   = baycom_ioctl,
पूर्ण;

/* --------------------------------------------------------------------- */

अटल पूर्णांक baycom_seपंचांगode(काष्ठा baycom_state *bc, स्थिर अक्षर *modestr)
अणु
	अचिन्हित पूर्णांक baud;

	अगर (!म_भेदन(modestr, "ser", 3)) अणु
		baud = simple_म_से_अदीर्घ(modestr+3, शून्य, 10);
		अगर (baud >= 3 && baud <= 48)
			bc->baud = baud*100;
	पूर्ण
	अगर (म_अक्षर(modestr, '*'))
		bc->opt_dcd = 0;
	अन्यथा अगर (म_अक्षर(modestr, '+'))
		bc->opt_dcd = -1;
	अन्यथा
		bc->opt_dcd = 1;
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक baycom_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr,
			काष्ठा hdlcdrv_ioctl *hi, पूर्णांक cmd)
अणु
	काष्ठा baycom_state *bc;
	काष्ठा baycom_ioctl bi;

	अगर (!dev)
		वापस -EINVAL;

	bc = netdev_priv(dev);
	BUG_ON(bc->hdrv.magic != HDLCDRV_MAGIC);

	अगर (cmd != SIOCDEVPRIVATE)
		वापस -ENOIOCTLCMD;
	चयन (hi->cmd) अणु
	शेष:
		अवरोध;

	हाल HDLCDRVCTL_GETMODE:
		प्र_लिखो(hi->data.modename, "ser%u", bc->baud / 100);
		अगर (bc->opt_dcd <= 0)
			म_जोड़ो(hi->data.modename, (!bc->opt_dcd) ? "*" : "+");
		अगर (copy_to_user(अगरr->अगरr_data, hi, माप(काष्ठा hdlcdrv_ioctl)))
			वापस -EFAULT;
		वापस 0;

	हाल HDLCDRVCTL_SETMODE:
		अगर (netअगर_running(dev) || !capable(CAP_NET_ADMIN))
			वापस -EACCES;
		hi->data.modename[माप(hi->data.modename)-1] = '\0';
		वापस baycom_seपंचांगode(bc, hi->data.modename);

	हाल HDLCDRVCTL_MODELIST:
		म_नकल(hi->data.modename, "ser12,ser3,ser24");
		अगर (copy_to_user(अगरr->अगरr_data, hi, माप(काष्ठा hdlcdrv_ioctl)))
			वापस -EFAULT;
		वापस 0;

	हाल HDLCDRVCTL_MODEMPARMASK:
		वापस HDLCDRV_PARMASK_IOBASE | HDLCDRV_PARMASK_IRQ;

	पूर्ण

	अगर (copy_from_user(&bi, अगरr->अगरr_data, माप(bi)))
		वापस -EFAULT;
	चयन (bi.cmd) अणु
	शेष:
		वापस -ENOIOCTLCMD;

#अगर_घोषित BAYCOM_DEBUG
	हाल BAYCOMCTL_GETDEBUG:
		bi.data.dbg.debug1 = bc->hdrv.ptt_keyed;
		bi.data.dbg.debug2 = bc->debug_vals.last_पूर्णांकcnt;
		bi.data.dbg.debug3 = bc->debug_vals.last_pllcorr;
		अवरोध;
#पूर्ण_अगर /* BAYCOM_DEBUG */

	पूर्ण
	अगर (copy_to_user(अगरr->अगरr_data, &bi, माप(bi)))
		वापस -EFAULT;
	वापस 0;

पूर्ण

/* --------------------------------------------------------------------- */

/*
 * command line settable parameters
 */
अटल अक्षर *mode[NR_PORTS] = अणु "ser12*", पूर्ण;
अटल पूर्णांक iobase[NR_PORTS] = अणु 0x3f8, पूर्ण;
अटल पूर्णांक irq[NR_PORTS] = अणु 4, पूर्ण;
अटल पूर्णांक baud[NR_PORTS] = अणु [0 ... NR_PORTS-1] = 1200 पूर्ण;

module_param_array(mode, अक्षरp, शून्य, 0);
MODULE_PARM_DESC(mode, "baycom operating mode; * for software DCD");
module_param_hw_array(iobase, पूर्णांक, ioport, शून्य, 0);
MODULE_PARM_DESC(iobase, "baycom io base address");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
MODULE_PARM_DESC(irq, "baycom irq number");
module_param_array(baud, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(baud, "baycom baud rate (300 to 4800)");

MODULE_AUTHOR("Thomas M. Sailer, sailer@ife.ee.ethz.ch, hb9jnx@hb9w.che.eu");
MODULE_DESCRIPTION("Baycom ser12 full duplex amateur radio modem driver");
MODULE_LICENSE("GPL");

/* --------------------------------------------------------------------- */

अटल पूर्णांक __init init_baycomserfdx(व्योम)
अणु
	पूर्णांक i, found = 0;
	अक्षर set_hw = 1;

	prपूर्णांकk(bc_drvinfo);
	/*
	 * रेजिस्टर net devices
	 */
	क्रम (i = 0; i < NR_PORTS; i++) अणु
		काष्ठा net_device *dev;
		काष्ठा baycom_state *bc;
		अक्षर अगरname[IFNAMSIZ];

		प्र_लिखो(अगरname, "bcsf%d", i);

		अगर (!mode[i])
			set_hw = 0;
		अगर (!set_hw)
			iobase[i] = irq[i] = 0;

		dev = hdlcdrv_रेजिस्टर(&ser12_ops, 
				       माप(काष्ठा baycom_state),
				       अगरname, iobase[i], irq[i], 0);
		अगर (IS_ERR(dev)) 
			अवरोध;

		bc = netdev_priv(dev);
		अगर (set_hw && baycom_seपंचांगode(bc, mode[i]))
			set_hw = 0;
		bc->baud = baud[i];
		found++;
		baycom_device[i] = dev;
	पूर्ण

	अगर (!found)
		वापस -ENXIO;
	वापस 0;
पूर्ण

अटल व्योम __निकास cleanup_baycomserfdx(व्योम)
अणु
	पूर्णांक i;

	क्रम(i = 0; i < NR_PORTS; i++) अणु
		काष्ठा net_device *dev = baycom_device[i];
		अगर (dev) 
			hdlcdrv_unरेजिस्टर(dev);
	पूर्ण
पूर्ण

module_init(init_baycomserfdx);
module_निकास(cleanup_baycomserfdx);

/* --------------------------------------------------------------------- */

#अगर_अघोषित MODULE

/*
 * क्रमmat: baycom_ser_fdx=io,irq,mode
 * mode: ser#    hardware DCD
 *       ser#*   software DCD
 *       ser#+   hardware DCD, inverted संकेत at DCD pin
 * '#' denotes the baud rate / 100, eg. ser12* is '1200 baud, soft DCD'
 */

अटल पूर्णांक __init baycom_ser_fdx_setup(अक्षर *str)
अणु
        अटल अचिन्हित nr_dev;
        पूर्णांक पूर्णांकs[4];

        अगर (nr_dev >= NR_PORTS)
                वापस 0;
        str = get_options(str, 4, पूर्णांकs);
        अगर (पूर्णांकs[0] < 2)
                वापस 0;
        mode[nr_dev] = str;
        iobase[nr_dev] = पूर्णांकs[1];
        irq[nr_dev] = पूर्णांकs[2];
	अगर (पूर्णांकs[0] >= 3)
		baud[nr_dev] = पूर्णांकs[3];
	nr_dev++;
	वापस 1;
पूर्ण

__setup("baycom_ser_fdx=", baycom_ser_fdx_setup);

#पूर्ण_अगर /* MODULE */
/* --------------------------------------------------------------------- */
