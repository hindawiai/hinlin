<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*****************************************************************************/

/*
 *	baycom_ser_hdx.c  -- baycom ser12 halfduplex radio modem driver.
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
 *  Command line options (insmod command line)
 *
 *  mode     ser12    hardware DCD
 *           ser12*   software DCD
 *           ser12@   hardware/software DCD, i.e. no explicit DCD संकेत but hardware
 *                    mutes audio input to the modem
 *           ser12+   hardware DCD, inverted संकेत at DCD pin
 *  iobase   base address of the port; common values are 0x3f8, 0x2f8, 0x3e8, 0x2e8
 *  irq      पूर्णांकerrupt line of the port; common values are 4,3
 *
 *  History:
 *   0.1  26.06.1996  Adapted from baycom.c and made network driver पूर्णांकerface
 *        18.10.1996  Changed to new user space access routines (copy_अणुto,fromपूर्ण_user)
 *   0.3  26.04.1997  init code/data tagged
 *   0.4  08.07.1997  alternative ser12 decoding algorithm (uses delta CTS पूर्णांकs)
 *   0.5  11.11.1997  ser12/par96 split पूर्णांकo separate files
 *   0.6  14.04.1998  cleanups
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
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/hdlcdrv.h>
#समावेश <linux/baycom.h>
#समावेश <linux/jअगरfies.h>

/* --------------------------------------------------------------------- */

#घोषणा BAYCOM_DEBUG

/* --------------------------------------------------------------------- */

अटल स्थिर अक्षर bc_drvname[] = "baycom_ser_hdx";
अटल स्थिर अक्षर bc_drvinfo[] = KERN_INFO "baycom_ser_hdx: (C) 1996-2000 Thomas Sailer, HB9JNX/AE4WA\n"
"baycom_ser_hdx: version 0.10\n";

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

	पूर्णांक opt_dcd;

	काष्ठा modem_state अणु
		लघु arb_भागider;
		अचिन्हित अक्षर flags;
		अचिन्हित पूर्णांक shreg;
		काष्ठा modem_state_ser12 अणु
			अचिन्हित अक्षर tx_bit;
			पूर्णांक dcd_sum0, dcd_sum1, dcd_sum2;
			अचिन्हित अक्षर last_sample;
			अचिन्हित अक्षर last_rxbit;
			अचिन्हित पूर्णांक dcd_shreg;
			अचिन्हित पूर्णांक dcd_समय;
			अचिन्हित पूर्णांक bit_pll;
			अचिन्हित अक्षर पूर्णांकerm_sample;
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

अटल अंतरभूत व्योम ser12_set_भागisor(काष्ठा net_device *dev,
				     अचिन्हित अक्षर भागisor)
अणु
	outb(0x81, LCR(dev->base_addr));	/* DLAB = 1 */
	outb(भागisor, DLL(dev->base_addr));
	outb(0, DLM(dev->base_addr));
	outb(0x01, LCR(dev->base_addr));	/* word length = 6 */
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

/* --------------------------------------------------------------------- */

/*
 * must call the TX arbitrator every 10ms
 */
#घोषणा SER12_ARB_DIVIDER(bc)  (bc->opt_dcd ? 24 : 36)
			       
#घोषणा SER12_DCD_INTERVAL(bc) (bc->opt_dcd ? 12 : 240)

अटल अंतरभूत व्योम ser12_tx(काष्ठा net_device *dev, काष्ठा baycom_state *bc)
अणु
	/* one पूर्णांकerrupt per channel bit */
	ser12_set_भागisor(dev, 12);
	/*
	 * first output the last bit (!) then call HDLC transmitter,
	 * since this may take quite दीर्घ
	 */
	outb(0x0e | (!!bc->modem.ser12.tx_bit), MCR(dev->base_addr));
	अगर (bc->modem.shreg <= 1)
		bc->modem.shreg = 0x10000 | hdlcdrv_getbits(&bc->hdrv);
	bc->modem.ser12.tx_bit = !(bc->modem.ser12.tx_bit ^
				   (bc->modem.shreg & 1));
	bc->modem.shreg >>= 1;
पूर्ण

/* --------------------------------------------------------------------- */

अटल अंतरभूत व्योम ser12_rx(काष्ठा net_device *dev, काष्ठा baycom_state *bc)
अणु
	अचिन्हित अक्षर cur_s;
	/*
	 * करो demodulator
	 */
	cur_s = inb(MSR(dev->base_addr)) & 0x10;	/* the CTS line */
	hdlcdrv_channelbit(&bc->hdrv, cur_s);
	bc->modem.ser12.dcd_shreg = (bc->modem.ser12.dcd_shreg << 1) |
		(cur_s != bc->modem.ser12.last_sample);
	bc->modem.ser12.last_sample = cur_s;
	अगर(bc->modem.ser12.dcd_shreg & 1) अणु
		अगर (!bc->opt_dcd) अणु
			अचिन्हित पूर्णांक dcdspos, dcdsneg;

			dcdspos = dcdsneg = 0;
			dcdspos += ((bc->modem.ser12.dcd_shreg >> 1) & 1);
			अगर (!(bc->modem.ser12.dcd_shreg & 0x7ffffffe))
				dcdspos += 2;
			dcdsneg += ((bc->modem.ser12.dcd_shreg >> 2) & 1);
			dcdsneg += ((bc->modem.ser12.dcd_shreg >> 3) & 1);
			dcdsneg += ((bc->modem.ser12.dcd_shreg >> 4) & 1);

			bc->modem.ser12.dcd_sum0 += 16*dcdspos - dcdsneg;
		पूर्ण अन्यथा
			bc->modem.ser12.dcd_sum0--;
	पूर्ण
	अगर(!bc->modem.ser12.dcd_समय) अणु
		hdlcdrv_setdcd(&bc->hdrv, (bc->modem.ser12.dcd_sum0 +
					   bc->modem.ser12.dcd_sum1 +
					   bc->modem.ser12.dcd_sum2) < 0);
		bc->modem.ser12.dcd_sum2 = bc->modem.ser12.dcd_sum1;
		bc->modem.ser12.dcd_sum1 = bc->modem.ser12.dcd_sum0;
		/* offset to ensure DCD off on silent input */
		bc->modem.ser12.dcd_sum0 = 2;
		bc->modem.ser12.dcd_समय = SER12_DCD_INTERVAL(bc);
	पूर्ण
	bc->modem.ser12.dcd_समय--;
	अगर (!bc->opt_dcd) अणु
		/*
		 * PLL code क्रम the improved software DCD algorithm
		 */
		अगर (bc->modem.ser12.पूर्णांकerm_sample) अणु
			/*
			 * पूर्णांकermediate sample; set timing correction to normal
			 */
			ser12_set_भागisor(dev, 4);
		पूर्ण अन्यथा अणु
			/*
			 * करो PLL correction and call HDLC receiver
			 */
			चयन (bc->modem.ser12.dcd_shreg & 7) अणु
			हाल 1: /* transition too late */
				ser12_set_भागisor(dev, 5);
#अगर_घोषित BAYCOM_DEBUG
				bc->debug_vals.cur_pllcorr++;
#पूर्ण_अगर /* BAYCOM_DEBUG */
				अवरोध;
			हाल 4:	/* transition too early */
				ser12_set_भागisor(dev, 3);
#अगर_घोषित BAYCOM_DEBUG
				bc->debug_vals.cur_pllcorr--;
#पूर्ण_अगर /* BAYCOM_DEBUG */
				अवरोध;
			शेष:
				ser12_set_भागisor(dev, 4);
				अवरोध;
			पूर्ण
			bc->modem.shreg >>= 1;
			अगर (bc->modem.ser12.last_sample ==
			    bc->modem.ser12.last_rxbit)
				bc->modem.shreg |= 0x10000;
			bc->modem.ser12.last_rxbit =
				bc->modem.ser12.last_sample;
		पूर्ण
		अगर (++bc->modem.ser12.पूर्णांकerm_sample >= 3)
			bc->modem.ser12.पूर्णांकerm_sample = 0;
		/*
		 * DCD stuff
		 */
		अगर (bc->modem.ser12.dcd_shreg & 1) अणु
			अचिन्हित पूर्णांक dcdspos, dcdsneg;

			dcdspos = dcdsneg = 0;
			dcdspos += ((bc->modem.ser12.dcd_shreg >> 1) & 1);
			dcdspos += (!(bc->modem.ser12.dcd_shreg & 0x7ffffffe))
				<< 1;
			dcdsneg += ((bc->modem.ser12.dcd_shreg >> 2) & 1);
			dcdsneg += ((bc->modem.ser12.dcd_shreg >> 3) & 1);
			dcdsneg += ((bc->modem.ser12.dcd_shreg >> 4) & 1);

			bc->modem.ser12.dcd_sum0 += 16*dcdspos - dcdsneg;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * PLL algorithm क्रम the hardware squelch DCD algorithm
		 */
		अगर (bc->modem.ser12.पूर्णांकerm_sample) अणु
			/*
			 * पूर्णांकermediate sample; set timing correction to normal
			 */
			ser12_set_भागisor(dev, 6);
		पूर्ण अन्यथा अणु
			/*
			 * करो PLL correction and call HDLC receiver
			 */
			चयन (bc->modem.ser12.dcd_shreg & 3) अणु
			हाल 1: /* transition too late */
				ser12_set_भागisor(dev, 7);
#अगर_घोषित BAYCOM_DEBUG
				bc->debug_vals.cur_pllcorr++;
#पूर्ण_अगर /* BAYCOM_DEBUG */
				अवरोध;
			हाल 2:	/* transition too early */
				ser12_set_भागisor(dev, 5);
#अगर_घोषित BAYCOM_DEBUG
				bc->debug_vals.cur_pllcorr--;
#पूर्ण_अगर /* BAYCOM_DEBUG */
				अवरोध;
			शेष:
				ser12_set_भागisor(dev, 6);
				अवरोध;
			पूर्ण
			bc->modem.shreg >>= 1;
			अगर (bc->modem.ser12.last_sample ==
			    bc->modem.ser12.last_rxbit)
				bc->modem.shreg |= 0x10000;
			bc->modem.ser12.last_rxbit =
				bc->modem.ser12.last_sample;
		पूर्ण
		bc->modem.ser12.पूर्णांकerm_sample = !bc->modem.ser12.पूर्णांकerm_sample;
		/*
		 * DCD stuff
		 */
		bc->modem.ser12.dcd_sum0 -= (bc->modem.ser12.dcd_shreg & 1);
	पूर्ण
	outb(0x0d, MCR(dev->base_addr));		/* transmitter off */
	अगर (bc->modem.shreg & 1) अणु
		hdlcdrv_putbits(&bc->hdrv, bc->modem.shreg >> 1);
		bc->modem.shreg = 0x10000;
	पूर्ण
	अगर(!bc->modem.ser12.dcd_समय) अणु
		अगर (bc->opt_dcd & 1) 
			hdlcdrv_setdcd(&bc->hdrv, !((inb(MSR(dev->base_addr)) ^ bc->opt_dcd) & 0x80));
		अन्यथा
			hdlcdrv_setdcd(&bc->hdrv, (bc->modem.ser12.dcd_sum0 +
						   bc->modem.ser12.dcd_sum1 +
						   bc->modem.ser12.dcd_sum2) < 0);
		bc->modem.ser12.dcd_sum2 = bc->modem.ser12.dcd_sum1;
		bc->modem.ser12.dcd_sum1 = bc->modem.ser12.dcd_sum0;
		/* offset to ensure DCD off on silent input */
		bc->modem.ser12.dcd_sum0 = 2;
		bc->modem.ser12.dcd_समय = SER12_DCD_INTERVAL(bc);
	पूर्ण
	bc->modem.ser12.dcd_समय--;
पूर्ण

/* --------------------------------------------------------------------- */

अटल irqवापस_t ser12_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा baycom_state *bc = netdev_priv(dev);
	अचिन्हित अक्षर iir;

	अगर (!dev || !bc || bc->hdrv.magic != HDLCDRV_MAGIC)
		वापस IRQ_NONE;
	/* fast way out */
	अगर ((iir = inb(IIR(dev->base_addr))) & 1)
		वापस IRQ_NONE;
	baycom_पूर्णांक_freq(bc);
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
			 * check अगर transmitter active
			 */
			अगर (hdlcdrv_ptt(&bc->hdrv))
				ser12_tx(dev, bc);
			अन्यथा अणु
				ser12_rx(dev, bc);
				bc->modem.arb_भागider--;
			पूर्ण
			outb(0x00, THR(dev->base_addr));
			अवरोध;
			
		शेष:
			inb(MSR(dev->base_addr));
			अवरोध;
		पूर्ण
		iir = inb(IIR(dev->base_addr));
	पूर्ण जबतक (!(iir & 1));
	अगर (bc->modem.arb_भागider <= 0) अणु
		bc->modem.arb_भागider = SER12_ARB_DIVIDER(bc);
		local_irq_enable();
		hdlcdrv_arbitrate(dev, &bc->hdrv);
	पूर्ण
	local_irq_enable();
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
	अगर (!dev->base_addr || dev->base_addr > 0x1000-SER12_EXTENT ||
	    dev->irq < 2 || dev->irq > 15)
		वापस -ENXIO;
	अगर (!request_region(dev->base_addr, SER12_EXTENT, "baycom_ser12"))
		वापस -EACCES;
	स_रखो(&bc->modem, 0, माप(bc->modem));
	bc->hdrv.par.bitrate = 1200;
	अगर ((u = ser12_check_uart(dev->base_addr)) == c_uart_unknown) अणु
		release_region(dev->base_addr, SER12_EXTENT);       
		वापस -EIO;
	पूर्ण
	outb(0, FCR(dev->base_addr));  /* disable FIFOs */
	outb(0x0d, MCR(dev->base_addr));
	outb(0, IER(dev->base_addr));
	अगर (request_irq(dev->irq, ser12_पूर्णांकerrupt, IRQF_SHARED,
			"baycom_ser12", dev)) अणु
		release_region(dev->base_addr, SER12_EXTENT);       
		वापस -EBUSY;
	पूर्ण
	/*
	 * enable transmitter empty पूर्णांकerrupt
	 */
	outb(2, IER(dev->base_addr));
	/*
	 * set the SIO to 6 Bits/अक्षरacter and 19200 or 28800 baud, so that
	 * we get exactly (hopefully) 2 or 3 पूर्णांकerrupts per radio symbol,
	 * depending on the usage of the software DCD routine
	 */
	ser12_set_भागisor(dev, bc->opt_dcd ? 6 : 4);
	prपूर्णांकk(KERN_INFO "%s: ser12 at iobase 0x%lx irq %u uart %s\n", 
	       bc_drvname, dev->base_addr, dev->irq, uart_str[u]);
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
	prपूर्णांकk(KERN_INFO "%s: close ser12 at iobase 0x%lx irq %u\n",
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
	अगर (म_अक्षर(modestr, '*'))
		bc->opt_dcd = 0;
	अन्यथा अगर (म_अक्षर(modestr, '+'))
		bc->opt_dcd = -1;
	अन्यथा अगर (म_अक्षर(modestr, '@'))
		bc->opt_dcd = -2;
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
		म_नकल(hi->data.modename, "ser12");
		अगर (bc->opt_dcd <= 0)
			म_जोड़ो(hi->data.modename, (!bc->opt_dcd) ? "*" : (bc->opt_dcd == -2) ? "@" : "+");
		अगर (copy_to_user(अगरr->अगरr_data, hi, माप(काष्ठा hdlcdrv_ioctl)))
			वापस -EFAULT;
		वापस 0;

	हाल HDLCDRVCTL_SETMODE:
		अगर (netअगर_running(dev) || !capable(CAP_NET_ADMIN))
			वापस -EACCES;
		hi->data.modename[माप(hi->data.modename)-1] = '\0';
		वापस baycom_seपंचांगode(bc, hi->data.modename);

	हाल HDLCDRVCTL_MODELIST:
		म_नकल(hi->data.modename, "ser12");
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

module_param_array(mode, अक्षरp, शून्य, 0);
MODULE_PARM_DESC(mode, "baycom operating mode; * for software DCD");
module_param_hw_array(iobase, पूर्णांक, ioport, शून्य, 0);
MODULE_PARM_DESC(iobase, "baycom io base address");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
MODULE_PARM_DESC(irq, "baycom irq number");

MODULE_AUTHOR("Thomas M. Sailer, sailer@ife.ee.ethz.ch, hb9jnx@hb9w.che.eu");
MODULE_DESCRIPTION("Baycom ser12 half duplex amateur radio modem driver");
MODULE_LICENSE("GPL");

/* --------------------------------------------------------------------- */

अटल पूर्णांक __init init_baycomserhdx(व्योम)
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

		प्र_लिखो(अगरname, "bcsh%d", i);

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
		found++;
		baycom_device[i] = dev;
	पूर्ण

	अगर (!found)
		वापस -ENXIO;
	वापस 0;
पूर्ण

अटल व्योम __निकास cleanup_baycomserhdx(व्योम)
अणु
	पूर्णांक i;

	क्रम(i = 0; i < NR_PORTS; i++) अणु
		काष्ठा net_device *dev = baycom_device[i];

		अगर (dev)
			hdlcdrv_unरेजिस्टर(dev);
	पूर्ण
पूर्ण

module_init(init_baycomserhdx);
module_निकास(cleanup_baycomserhdx);

/* --------------------------------------------------------------------- */

#अगर_अघोषित MODULE

/*
 * क्रमmat: baycom_ser_hdx=io,irq,mode
 * mode: ser12    hardware DCD
 *       ser12*   software DCD
 *       ser12@   hardware/software DCD, i.e. no explicit DCD संकेत but hardware
 *                mutes audio input to the modem
 *       ser12+   hardware DCD, inverted संकेत at DCD pin
 */

अटल पूर्णांक __init baycom_ser_hdx_setup(अक्षर *str)
अणु
        अटल अचिन्हित nr_dev;
	पूर्णांक पूर्णांकs[3];

        अगर (nr_dev >= NR_PORTS)
                वापस 0;
	str = get_options(str, 3, पूर्णांकs);
	अगर (पूर्णांकs[0] < 2)
		वापस 0;
	mode[nr_dev] = str;
	iobase[nr_dev] = पूर्णांकs[1];
	irq[nr_dev] = पूर्णांकs[2];
	nr_dev++;
	वापस 1;
पूर्ण

__setup("baycom_ser_hdx=", baycom_ser_hdx_setup);

#पूर्ण_अगर /* MODULE */
/* --------------------------------------------------------------------- */
