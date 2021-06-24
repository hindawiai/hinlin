<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device driver क्रम the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family 
 * of PCI-SCSI IO processors.
 *
 * Copyright (C) 1999-2001  Gerard Roudier <groudier@मुक्त.fr>
 * Copyright (c) 2003-2005  Matthew Wilcox <matthew@wil.cx>
 *
 * This driver is derived from the Linux sym53c8xx driver.
 * Copyright (C) 1998-2000  Gerard Roudier
 *
 * The sym53c8xx driver is derived from the ncr53c8xx driver that had been 
 * a port of the FreeBSD ncr driver to Linux-1.2.13.
 *
 * The original ncr driver has been written क्रम 386bsd and FreeBSD by
 *         Wolfgang Stanglmeier        <wolf@cologne.de>
 *         Stefan Esser                <se@mi.Uni-Koeln.de>
 * Copyright (C) 1994  Wolfgang Stanglmeier
 *
 * Other major contributions:
 *
 * NVRAM detection and पढ़ोing.
 * Copyright (C) 1997 Riअक्षरd Waltham <करोrmouse@farsrobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#समावेश <linux/slab.h>
#समावेश <यंत्र/param.h>		/* क्रम समयouts in units of HZ */

#समावेश "sym_glue.h"
#समावेश "sym_nvram.h"

#अगर 0
#घोषणा SYM_DEBUG_GENERIC_SUPPORT
#पूर्ण_अगर

/*
 *  Needed function prototypes.
 */
अटल व्योम sym_पूर्णांक_ma (काष्ठा sym_hcb *np);
अटल व्योम sym_पूर्णांक_sir(काष्ठा sym_hcb *);
अटल काष्ठा sym_ccb *sym_alloc_ccb(काष्ठा sym_hcb *np);
अटल काष्ठा sym_ccb *sym_ccb_from_dsa(काष्ठा sym_hcb *np, u32 dsa);
अटल व्योम sym_alloc_lcb_tags (काष्ठा sym_hcb *np, u_अक्षर tn, u_अक्षर ln);
अटल व्योम sym_complete_error (काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp);
अटल व्योम sym_complete_ok (काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp);
अटल पूर्णांक sym_compute_residual(काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp);

/*
 *  Prपूर्णांक a buffer in hexadecimal क्रमmat with a ".\n" at end.
 */
अटल व्योम sym_prपूर्णांकl_hex(u_अक्षर *p, पूर्णांक n)
अणु
	जबतक (n-- > 0)
		म_लिखो (" %x", *p++);
	म_लिखो (".\n");
पूर्ण

अटल व्योम sym_prपूर्णांक_msg(काष्ठा sym_ccb *cp, अक्षर *label, u_अक्षर *msg)
अणु
	sym_prपूर्णांक_addr(cp->cmd, "%s: ", label);

	spi_prपूर्णांक_msg(msg);
	म_लिखो("\n");
पूर्ण

अटल व्योम sym_prपूर्णांक_nego_msg(काष्ठा sym_hcb *np, पूर्णांक target, अक्षर *label, u_अक्षर *msg)
अणु
	काष्ठा sym_tcb *tp = &np->target[target];
	dev_info(&tp->starget->dev, "%s: ", label);

	spi_prपूर्णांक_msg(msg);
	म_लिखो("\n");
पूर्ण

/*
 *  Prपूर्णांक something that tells about extended errors.
 */
व्योम sym_prपूर्णांक_xerr(काष्ठा scsi_cmnd *cmd, पूर्णांक x_status)
अणु
	अगर (x_status & XE_PARITY_ERR) अणु
		sym_prपूर्णांक_addr(cmd, "unrecovered SCSI parity error.\n");
	पूर्ण
	अगर (x_status & XE_EXTRA_DATA) अणु
		sym_prपूर्णांक_addr(cmd, "extraneous data discarded.\n");
	पूर्ण
	अगर (x_status & XE_BAD_PHASE) अणु
		sym_prपूर्णांक_addr(cmd, "illegal scsi phase (4/5).\n");
	पूर्ण
	अगर (x_status & XE_SODL_UNRUN) अणु
		sym_prपूर्णांक_addr(cmd, "ODD transfer in DATA OUT phase.\n");
	पूर्ण
	अगर (x_status & XE_SWIDE_OVRUN) अणु
		sym_prपूर्णांक_addr(cmd, "ODD transfer in DATA IN phase.\n");
	पूर्ण
पूर्ण

/*
 *  Return a string क्रम SCSI BUS mode.
 */
अटल अक्षर *sym_scsi_bus_mode(पूर्णांक mode)
अणु
	चयन(mode) अणु
	हाल SMODE_HVD:	वापस "HVD";
	हाल SMODE_SE:	वापस "SE";
	हाल SMODE_LVD: वापस "LVD";
	पूर्ण
	वापस "??";
पूर्ण

/*
 *  Soft reset the chip.
 *
 *  Raising SRST when the chip is running may cause 
 *  problems on dual function chips (see below).
 *  On the other hand, LVD devices need some delay 
 *  to settle and report actual BUS mode in STEST4.
 */
अटल व्योम sym_chip_reset (काष्ठा sym_hcb *np)
अणु
	OUTB(np, nc_istat, SRST);
	INB(np, nc_mbox1);
	udelay(10);
	OUTB(np, nc_istat, 0);
	INB(np, nc_mbox1);
	udelay(2000);	/* For BUS MODE to settle */
पूर्ण

/*
 *  Really soft reset the chip.:)
 *
 *  Some 896 and 876 chip revisions may hang-up अगर we set 
 *  the SRST (soft reset) bit at the wrong समय when SCRIPTS 
 *  are running.
 *  So, we need to पात the current operation prior to 
 *  soft resetting the chip.
 */
अटल व्योम sym_soft_reset (काष्ठा sym_hcb *np)
अणु
	u_अक्षर istat = 0;
	पूर्णांक i;

	अगर (!(np->features & FE_ISTAT1) || !(INB(np, nc_istat1) & SCRUN))
		जाओ करो_chip_reset;

	OUTB(np, nc_istat, CABRT);
	क्रम (i = 100000 ; i ; --i) अणु
		istat = INB(np, nc_istat);
		अगर (istat & SIP) अणु
			INW(np, nc_sist);
		पूर्ण
		अन्यथा अगर (istat & DIP) अणु
			अगर (INB(np, nc_dstat) & ABRT)
				अवरोध;
		पूर्ण
		udelay(5);
	पूर्ण
	OUTB(np, nc_istat, 0);
	अगर (!i)
		म_लिखो("%s: unable to abort current chip operation, "
		       "ISTAT=0x%02x.\n", sym_name(np), istat);
करो_chip_reset:
	sym_chip_reset(np);
पूर्ण

/*
 *  Start reset process.
 *
 *  The पूर्णांकerrupt handler will reinitialize the chip.
 */
अटल व्योम sym_start_reset(काष्ठा sym_hcb *np)
अणु
	sym_reset_scsi_bus(np, 1);
पूर्ण
 
पूर्णांक sym_reset_scsi_bus(काष्ठा sym_hcb *np, पूर्णांक enab_पूर्णांक)
अणु
	u32 term;
	पूर्णांक retv = 0;

	sym_soft_reset(np);	/* Soft reset the chip */
	अगर (enab_पूर्णांक)
		OUTW(np, nc_sien, RST);
	/*
	 *  Enable Tolerant, reset IRQD अगर present and 
	 *  properly set IRQ mode, prior to resetting the bus.
	 */
	OUTB(np, nc_stest3, TE);
	OUTB(np, nc_dcntl, (np->rv_dcntl & IRQM));
	OUTB(np, nc_scntl1, CRST);
	INB(np, nc_mbox1);
	udelay(200);

	अगर (!SYM_SETUP_SCSI_BUS_CHECK)
		जाओ out;
	/*
	 *  Check क्रम no terminators or SCSI bus लघुs to ground.
	 *  Read SCSI data bus, data parity bits and control संकेतs.
	 *  We are expecting RESET to be TRUE and other संकेतs to be 
	 *  FALSE.
	 */
	term =	INB(np, nc_sstat0);
	term =	((term & 2) << 7) + ((term & 1) << 17);	/* rst sdp0 */
	term |= ((INB(np, nc_sstat2) & 0x01) << 26) |	/* sdp1     */
		((INW(np, nc_sbdl) & 0xff)   << 9)  |	/* d7-0     */
		((INW(np, nc_sbdl) & 0xff00) << 10) |	/* d15-8    */
		INB(np, nc_sbcl);	/* req ack bsy sel atn msg cd io    */

	अगर (!np->maxwide)
		term &= 0x3ffff;

	अगर (term != (2<<7)) अणु
		म_लिखो("%s: suspicious SCSI data while resetting the BUS.\n",
			sym_name(np));
		म_लिखो("%s: %sdp0,d7-0,rst,req,ack,bsy,sel,atn,msg,c/d,i/o = "
			"0x%lx, expecting 0x%lx\n",
			sym_name(np),
			(np->features & FE_WIDE) ? "dp1,d15-8," : "",
			(u_दीर्घ)term, (u_दीर्घ)(2<<7));
		अगर (SYM_SETUP_SCSI_BUS_CHECK == 1)
			retv = 1;
	पूर्ण
out:
	OUTB(np, nc_scntl1, 0);
	वापस retv;
पूर्ण

/*
 *  Select SCSI घड़ी frequency
 */
अटल व्योम sym_selectघड़ी(काष्ठा sym_hcb *np, u_अक्षर scntl3)
अणु
	/*
	 *  If multiplier not present or not selected, leave here.
	 */
	अगर (np->multiplier <= 1) अणु
		OUTB(np, nc_scntl3, scntl3);
		वापस;
	पूर्ण

	अगर (sym_verbose >= 2)
		म_लिखो ("%s: enabling clock multiplier\n", sym_name(np));

	OUTB(np, nc_stest1, DBLEN);	   /* Enable घड़ी multiplier */
	/*
	 *  Wait क्रम the LCKFRQ bit to be set अगर supported by the chip.
	 *  Otherwise रुको 50 micro-seconds (at least).
	 */
	अगर (np->features & FE_LCKFRQ) अणु
		पूर्णांक i = 20;
		जबतक (!(INB(np, nc_stest4) & LCKFRQ) && --i > 0)
			udelay(20);
		अगर (!i)
			म_लिखो("%s: the chip cannot lock the frequency\n",
				sym_name(np));
	पूर्ण अन्यथा अणु
		INB(np, nc_mbox1);
		udelay(50+10);
	पूर्ण
	OUTB(np, nc_stest3, HSC);		/* Halt the scsi घड़ी	*/
	OUTB(np, nc_scntl3, scntl3);
	OUTB(np, nc_stest1, (DBLEN|DBLSEL));/* Select घड़ी multiplier	*/
	OUTB(np, nc_stest3, 0x00);		/* Restart scsi घड़ी 	*/
पूर्ण


/*
 *  Determine the chip's घड़ी frequency.
 *
 *  This is essential क्रम the negotiation of the synchronous 
 *  transfer rate.
 *
 *  Note: we have to वापस the correct value.
 *  THERE IS NO SAFE DEFAULT VALUE.
 *
 *  Most NCR/SYMBIOS boards are delivered with a 40 Mhz घड़ी.
 *  53C860 and 53C875 rev. 1 support fast20 transfers but 
 *  करो not have a घड़ी द्विगुनr and so are provided with a 
 *  80 MHz घड़ी. All other fast20 boards incorporate a द्विगुनr 
 *  and so should be delivered with a 40 MHz घड़ी.
 *  The recent fast40 chips (895/896/895A/1010) use a 40 Mhz base 
 *  घड़ी and provide a घड़ी quadrupler (160 Mhz).
 */

/*
 *  calculate SCSI घड़ी frequency (in KHz)
 */
अटल अचिन्हित getfreq (काष्ठा sym_hcb *np, पूर्णांक gen)
अणु
	अचिन्हित पूर्णांक ms = 0;
	अचिन्हित पूर्णांक f;

	/*
	 * Measure GEN समयr delay in order 
	 * to calculate SCSI घड़ी frequency
	 *
	 * This code will never execute too
	 * many loop iterations (अगर DELAY is 
	 * reasonably correct). It could get
	 * too low a delay (too high a freq.)
	 * अगर the CPU is slow executing the 
	 * loop क्रम some reason (an NMI, क्रम
	 * example). For this reason we will
	 * अगर multiple measurements are to be 
	 * perक्रमmed trust the higher delay 
	 * (lower frequency वापसed).
	 */
	OUTW(np, nc_sien, 0);	/* mask all scsi पूर्णांकerrupts */
	INW(np, nc_sist);	/* clear pending scsi पूर्णांकerrupt */
	OUTB(np, nc_dien, 0);	/* mask all dma पूर्णांकerrupts */
	INW(np, nc_sist);	/* another one, just to be sure :) */
	/*
	 * The C1010-33 core करोes not report GEN in SIST,
	 * अगर this पूर्णांकerrupt is masked in SIEN.
	 * I करोn't know yet अगर the C1010-66 behaves the same way.
	 */
	अगर (np->features & FE_C10) अणु
		OUTW(np, nc_sien, GEN);
		OUTB(np, nc_istat1, SIRQD);
	पूर्ण
	OUTB(np, nc_scntl3, 4);	   /* set pre-scaler to भागide by 3 */
	OUTB(np, nc_sसमय1, 0);	   /* disable general purpose समयr */
	OUTB(np, nc_sसमय1, gen);  /* set to nominal delay of 1<<gen * 125us */
	जबतक (!(INW(np, nc_sist) & GEN) && ms++ < 100000)
		udelay(1000/4);    /* count in 1/4 of ms */
	OUTB(np, nc_sसमय1, 0);    /* disable general purpose समयr */
	/*
	 * Unकरो C1010-33 specअगरic settings.
	 */
	अगर (np->features & FE_C10) अणु
		OUTW(np, nc_sien, 0);
		OUTB(np, nc_istat1, 0);
	पूर्ण
 	/*
 	 * set prescaler to भागide by whatever 0 means
 	 * 0 ought to choose भागide by 2, but appears
 	 * to set भागide by 3.5 mode in my 53c810 ...
 	 */
 	OUTB(np, nc_scntl3, 0);

  	/*
 	 * adjust क्रम prescaler, and convert पूर्णांकo KHz 
  	 */
	f = ms ? ((1 << gen) * (4340*4)) / ms : 0;

	/*
	 * The C1010-33 result is biased by a factor 
	 * of 2/3 compared to earlier chips.
	 */
	अगर (np->features & FE_C10)
		f = (f * 2) / 3;

	अगर (sym_verbose >= 2)
		म_लिखो ("%s: Delay (GEN=%d): %u msec, %u KHz\n",
			sym_name(np), gen, ms/4, f);

	वापस f;
पूर्ण

अटल अचिन्हित sym_getfreq (काष्ठा sym_hcb *np)
अणु
	u_पूर्णांक f1, f2;
	पूर्णांक gen = 8;

	getfreq (np, gen);	/* throw away first result */
	f1 = getfreq (np, gen);
	f2 = getfreq (np, gen);
	अगर (f1 > f2) f1 = f2;		/* trust lower result	*/
	वापस f1;
पूर्ण

/*
 *  Get/probe chip SCSI घड़ी frequency
 */
अटल व्योम sym_अ_लोlock (काष्ठा sym_hcb *np, पूर्णांक mult)
अणु
	अचिन्हित अक्षर scntl3 = np->sv_scntl3;
	अचिन्हित अक्षर stest1 = np->sv_stest1;
	अचिन्हित f1;

	np->multiplier = 1;
	f1 = 40000;
	/*
	 *  True with 875/895/896/895A with घड़ी multiplier selected
	 */
	अगर (mult > 1 && (stest1 & (DBLEN+DBLSEL)) == DBLEN+DBLSEL) अणु
		अगर (sym_verbose >= 2)
			म_लिखो ("%s: clock multiplier found\n", sym_name(np));
		np->multiplier = mult;
	पूर्ण

	/*
	 *  If multiplier not found or scntl3 not 7,5,3,
	 *  reset chip and get frequency from general purpose समयr.
	 *  Otherwise trust scntl3 BIOS setting.
	 */
	अगर (np->multiplier != mult || (scntl3 & 7) < 3 || !(scntl3 & 1)) अणु
		OUTB(np, nc_stest1, 0);		/* make sure द्विगुनr is OFF */
		f1 = sym_getfreq (np);

		अगर (sym_verbose)
			म_लिखो ("%s: chip clock is %uKHz\n", sym_name(np), f1);

		अगर	(f1 <	45000)		f1 =  40000;
		अन्यथा अगर (f1 <	55000)		f1 =  50000;
		अन्यथा				f1 =  80000;

		अगर (f1 < 80000 && mult > 1) अणु
			अगर (sym_verbose >= 2)
				म_लिखो ("%s: clock multiplier assumed\n",
					sym_name(np));
			np->multiplier	= mult;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर	((scntl3 & 7) == 3)	f1 =  40000;
		अन्यथा अगर	((scntl3 & 7) == 5)	f1 =  80000;
		अन्यथा 				f1 = 160000;

		f1 /= np->multiplier;
	पूर्ण

	/*
	 *  Compute controller synchronous parameters.
	 */
	f1		*= np->multiplier;
	np->घड़ी_khz	= f1;
पूर्ण

/*
 *  Get/probe PCI घड़ी frequency
 */
अटल पूर्णांक sym_getpciघड़ी (काष्ठा sym_hcb *np)
अणु
	पूर्णांक f = 0;

	/*
	 *  For now, we only need to know about the actual 
	 *  PCI BUS घड़ी frequency क्रम C1010-66 chips.
	 */
#अगर 1
	अगर (np->features & FE_66MHZ) अणु
#अन्यथा
	अगर (1) अणु
#पूर्ण_अगर
		OUTB(np, nc_stest1, SCLK); /* Use the PCI घड़ी as SCSI घड़ी */
		f = sym_getfreq(np);
		OUTB(np, nc_stest1, 0);
	पूर्ण
	np->pciclk_khz = f;

	वापस f;
पूर्ण

/*
 *  SYMBIOS chip घड़ी भागisor table.
 *
 *  Divisors are multiplied by 10,000,000 in order to make 
 *  calculations more simple.
 */
#घोषणा _5M 5000000
अटल स्थिर u32 भाग_10M[] = अणु2*_5M, 3*_5M, 4*_5M, 6*_5M, 8*_5M, 12*_5M, 16*_5Mपूर्ण;

/*
 *  Get घड़ी factor and sync भागisor क्रम a given 
 *  synchronous factor period.
 */
अटल पूर्णांक 
sym_माला_लोync(काष्ठा sym_hcb *np, u_अक्षर dt, u_अक्षर sfac, u_अक्षर *भागp, u_अक्षर *fakp)
अणु
	u32	clk = np->घड़ी_khz;	/* SCSI घड़ी frequency in kHz	*/
	पूर्णांक	भाग = np->घड़ी_भागn;	/* Number of भागisors supported	*/
	u32	fak;			/* Sync factor in sxfer		*/
	u32	per;			/* Period in tenths of ns	*/
	u32	kpc;			/* (per * clk)			*/
	पूर्णांक	ret;

	/*
	 *  Compute the synchronous period in tenths of nano-seconds
	 */
	अगर (dt && sfac <= 9)	per = 125;
	अन्यथा अगर	(sfac <= 10)	per = 250;
	अन्यथा अगर	(sfac == 11)	per = 303;
	अन्यथा अगर	(sfac == 12)	per = 500;
	अन्यथा			per = 40 * sfac;
	ret = per;

	kpc = per * clk;
	अगर (dt)
		kpc <<= 1;

	/*
	 *  For earliest C10 revision 0, we cannot use extra 
	 *  घड़ीs क्रम the setting of the SCSI घड़ीing.
	 *  Note that this limits the lowest sync data transfer 
	 *  to 5 Mega-transfers per second and may result in
	 *  using higher घड़ी भागisors.
	 */
#अगर 1
	अगर ((np->features & (FE_C10|FE_U3EN)) == FE_C10) अणु
		/*
		 *  Look क्रम the lowest घड़ी भागisor that allows an 
		 *  output speed not faster than the period.
		 */
		जबतक (भाग > 0) अणु
			--भाग;
			अगर (kpc > (भाग_10M[भाग] << 2)) अणु
				++भाग;
				अवरोध;
			पूर्ण
		पूर्ण
		fak = 0;			/* No extra घड़ीs */
		अगर (भाग == np->घड़ी_भागn) अणु	/* Are we too fast ? */
			ret = -1;
		पूर्ण
		*भागp = भाग;
		*fakp = fak;
		वापस ret;
	पूर्ण
#पूर्ण_अगर

	/*
	 *  Look क्रम the greatest घड़ी भागisor that allows an 
	 *  input speed faster than the period.
	 */
	जबतक (--भाग > 0)
		अगर (kpc >= (भाग_10M[भाग] << 2)) अवरोध;

	/*
	 *  Calculate the lowest घड़ी factor that allows an output 
	 *  speed not faster than the period, and the max output speed.
	 *  If fak >= 1 we will set both XCLKH_ST and XCLKH_DT.
	 *  If fak >= 2 we will also set XCLKS_ST and XCLKS_DT.
	 */
	अगर (dt) अणु
		fak = (kpc - 1) / (भाग_10M[भाग] << 1) + 1 - 2;
		/* ret = ((2+fak)*भाग_10M[भाग])/np->घड़ी_khz; */
	पूर्ण अन्यथा अणु
		fak = (kpc - 1) / भाग_10M[भाग] + 1 - 4;
		/* ret = ((4+fak)*भाग_10M[भाग])/np->घड़ी_khz; */
	पूर्ण

	/*
	 *  Check against our hardware limits, or bugs :).
	 */
	अगर (fak > 2) अणु
		fak = 2;
		ret = -1;
	पूर्ण

	/*
	 *  Compute and वापस sync parameters.
	 */
	*भागp = भाग;
	*fakp = fak;

	वापस ret;
पूर्ण

/*
 *  SYMBIOS chips allow burst lengths of 2, 4, 8, 16, 32, 64,
 *  128 transfers. All chips support at least 16 transfers 
 *  bursts. The 825A, 875 and 895 chips support bursts of up 
 *  to 128 transfers and the 895A and 896 support bursts of up
 *  to 64 transfers. All other chips support up to 16 
 *  transfers bursts.
 *
 *  For PCI 32 bit data transfers each transfer is a DWORD.
 *  It is a QUADWORD (8 bytes) क्रम PCI 64 bit data transfers.
 *
 *  We use log base 2 (burst length) as पूर्णांकernal code, with 
 *  value 0 meaning "burst disabled".
 */

/*
 *  Burst length from burst code.
 */
#घोषणा burst_length(bc) (!(bc))? 0 : 1 << (bc)

/*
 *  Burst code from io रेजिस्टर bits.
 */
#घोषणा burst_code(dmode, ctest4, ctest5) \
	(ctest4) & 0x80? 0 : (((dmode) & 0xc0) >> 6) + ((ctest5) & 0x04) + 1

/*
 *  Set initial io रेजिस्टर bits from burst code.
 */
अटल अंतरभूत व्योम sym_init_burst(काष्ठा sym_hcb *np, u_अक्षर bc)
अणु
	np->rv_ctest4	&= ~0x80;
	np->rv_dmode	&= ~(0x3 << 6);
	np->rv_ctest5	&= ~0x4;

	अगर (!bc) अणु
		np->rv_ctest4	|= 0x80;
	पूर्ण
	अन्यथा अणु
		--bc;
		np->rv_dmode	|= ((bc & 0x3) << 6);
		np->rv_ctest5	|= (bc & 0x4);
	पूर्ण
पूर्ण

/*
 *  Save initial settings of some IO रेजिस्टरs.
 *  Assumed to have been set by BIOS.
 *  We cannot reset the chip prior to पढ़ोing the 
 *  IO रेजिस्टरs, since inक्रमmations will be lost.
 *  Since the SCRIPTS processor may be running, this 
 *  is not safe on paper, but it seems to work quite 
 *  well. :)
 */
अटल व्योम sym_save_initial_setting (काष्ठा sym_hcb *np)
अणु
	np->sv_scntl0	= INB(np, nc_scntl0) & 0x0a;
	np->sv_scntl3	= INB(np, nc_scntl3) & 0x07;
	np->sv_dmode	= INB(np, nc_dmode)  & 0xce;
	np->sv_dcntl	= INB(np, nc_dcntl)  & 0xa8;
	np->sv_ctest3	= INB(np, nc_ctest3) & 0x01;
	np->sv_ctest4	= INB(np, nc_ctest4) & 0x80;
	np->sv_gpcntl	= INB(np, nc_gpcntl);
	np->sv_stest1	= INB(np, nc_stest1);
	np->sv_stest2	= INB(np, nc_stest2) & 0x20;
	np->sv_stest4	= INB(np, nc_stest4);
	अगर (np->features & FE_C10) अणु	/* Always large DMA fअगरo + ultra3 */
		np->sv_scntl4	= INB(np, nc_scntl4);
		np->sv_ctest5	= INB(np, nc_ctest5) & 0x04;
	पूर्ण
	अन्यथा
		np->sv_ctest5	= INB(np, nc_ctest5) & 0x24;
पूर्ण

/*
 *  Set SCSI BUS mode.
 *  - LVD capable chips (895/895A/896/1010) report the current BUS mode
 *    through the STEST4 IO रेजिस्टर.
 *  - For previous generation chips (825/825A/875), the user has to tell us
 *    how to check against HVD, since a 100% safe algorithm is not possible.
 */
अटल व्योम sym_set_bus_mode(काष्ठा sym_hcb *np, काष्ठा sym_nvram *nvram)
अणु
	अगर (np->scsi_mode)
		वापस;

	np->scsi_mode = SMODE_SE;
	अगर (np->features & (FE_ULTRA2|FE_ULTRA3))
		np->scsi_mode = (np->sv_stest4 & SMODE);
	अन्यथा अगर	(np->features & FE_DIFF) अणु
		अगर (SYM_SETUP_SCSI_DIFF == 1) अणु
			अगर (np->sv_scntl3) अणु
				अगर (np->sv_stest2 & 0x20)
					np->scsi_mode = SMODE_HVD;
			पूर्ण अन्यथा अगर (nvram->type == SYM_SYMBIOS_NVRAM) अणु
				अगर (!(INB(np, nc_gpreg) & 0x08))
					np->scsi_mode = SMODE_HVD;
			पूर्ण
		पूर्ण अन्यथा अगर (SYM_SETUP_SCSI_DIFF == 2)
			np->scsi_mode = SMODE_HVD;
	पूर्ण
	अगर (np->scsi_mode == SMODE_HVD)
		np->rv_stest2 |= 0x20;
पूर्ण

/*
 *  Prepare io रेजिस्टर values used by sym_start_up() 
 *  according to selected and supported features.
 */
अटल पूर्णांक sym_prepare_setting(काष्ठा Scsi_Host *shost, काष्ठा sym_hcb *np, काष्ठा sym_nvram *nvram)
अणु
	काष्ठा sym_data *sym_data = shost_priv(shost);
	काष्ठा pci_dev *pdev = sym_data->pdev;
	u_अक्षर	burst_max;
	u32	period;
	पूर्णांक i;

	np->maxwide = (np->features & FE_WIDE) ? 1 : 0;

	/*
	 *  Guess the frequency of the chip's घड़ी.
	 */
	अगर	(np->features & (FE_ULTRA3 | FE_ULTRA2))
		np->घड़ी_khz = 160000;
	अन्यथा अगर	(np->features & FE_ULTRA)
		np->घड़ी_khz = 80000;
	अन्यथा
		np->घड़ी_khz = 40000;

	/*
	 *  Get the घड़ी multiplier factor.
 	 */
	अगर	(np->features & FE_QUAD)
		np->multiplier	= 4;
	अन्यथा अगर	(np->features & FE_DBLR)
		np->multiplier	= 2;
	अन्यथा
		np->multiplier	= 1;

	/*
	 *  Measure SCSI घड़ी frequency क्रम chips 
	 *  it may vary from assumed one.
	 */
	अगर (np->features & FE_VARCLK)
		sym_अ_लोlock(np, np->multiplier);

	/*
	 * Divisor to be used क्रम async (समयr pre-scaler).
	 */
	i = np->घड़ी_भागn - 1;
	जबतक (--i >= 0) अणु
		अगर (10ul * SYM_CONF_MIN_ASYNC * np->घड़ी_khz > भाग_10M[i]) अणु
			++i;
			अवरोध;
		पूर्ण
	पूर्ण
	np->rv_scntl3 = i+1;

	/*
	 * The C1010 uses hardwired भागisors क्रम async.
	 * So, we just throw away, the async. भागisor.:-)
	 */
	अगर (np->features & FE_C10)
		np->rv_scntl3 = 0;

	/*
	 * Minimum synchronous period factor supported by the chip.
	 * Btw, 'period' is in tenths of nanoseconds.
	 */
	period = (4 * भाग_10M[0] + np->घड़ी_khz - 1) / np->घड़ी_khz;

	अगर	(period <= 250)		np->minsync = 10;
	अन्यथा अगर	(period <= 303)		np->minsync = 11;
	अन्यथा अगर	(period <= 500)		np->minsync = 12;
	अन्यथा				np->minsync = (period + 40 - 1) / 40;

	/*
	 * Check against chip SCSI standard support (SCSI-2,ULTRA,ULTRA2).
	 */
	अगर	(np->minsync < 25 &&
		 !(np->features & (FE_ULTRA|FE_ULTRA2|FE_ULTRA3)))
		np->minsync = 25;
	अन्यथा अगर	(np->minsync < 12 &&
		 !(np->features & (FE_ULTRA2|FE_ULTRA3)))
		np->minsync = 12;

	/*
	 * Maximum synchronous period factor supported by the chip.
	 */
	period = भाग64_ul(11 * भाग_10M[np->घड़ी_भागn - 1], 4 * np->घड़ी_khz);
	np->maxsync = period > 2540 ? 254 : period / 10;

	/*
	 * If chip is a C1010, guess the sync limits in DT mode.
	 */
	अगर ((np->features & (FE_C10|FE_ULTRA3)) == (FE_C10|FE_ULTRA3)) अणु
		अगर (np->घड़ी_khz == 160000) अणु
			np->minsync_dt = 9;
			np->maxsync_dt = 50;
			np->maxoffs_dt = nvram->type ? 62 : 31;
		पूर्ण
	पूर्ण
	
	/*
	 *  64 bit addressing  (895A/896/1010) ?
	 */
	अगर (np->features & FE_DAC) अणु
		अगर (!use_dac(np))
			np->rv_ccntl1 |= (DDAC);
		अन्यथा अगर (SYM_CONF_DMA_ADDRESSING_MODE == 1)
			np->rv_ccntl1 |= (XTIMOD | EXTIBMV);
		अन्यथा अगर (SYM_CONF_DMA_ADDRESSING_MODE == 2)
			np->rv_ccntl1 |= (0 | EXTIBMV);
	पूर्ण

	/*
	 *  Phase mismatch handled by SCRIPTS (895A/896/1010) ?
  	 */
	अगर (np->features & FE_NOPM)
		np->rv_ccntl0	|= (ENPMJ);

 	/*
	 *  C1010-33 Errata: Part Number:609-039638 (rev. 1) is fixed.
	 *  In dual channel mode, contention occurs अगर पूर्णांकernal cycles
	 *  are used. Disable पूर्णांकernal cycles.
	 */
	अगर (pdev->device == PCI_DEVICE_ID_LSI_53C1010_33 &&
	    pdev->revision < 0x1)
		np->rv_ccntl0	|=  DILS;

	/*
	 *  Select burst length (dwords)
	 */
	burst_max	= SYM_SETUP_BURST_ORDER;
	अगर (burst_max == 255)
		burst_max = burst_code(np->sv_dmode, np->sv_ctest4,
				       np->sv_ctest5);
	अगर (burst_max > 7)
		burst_max = 7;
	अगर (burst_max > np->maxburst)
		burst_max = np->maxburst;

	/*
	 *  DEL 352 - 53C810 Rev x11 - Part Number 609-0392140 - ITEM 2.
	 *  This chip and the 860 Rev 1 may wrongly use PCI cache line 
	 *  based transactions on LOAD/STORE inकाष्ठाions. So we have 
	 *  to prevent these chips from using such PCI transactions in 
	 *  this driver. The generic ncr driver that करोes not use 
	 *  LOAD/STORE inकाष्ठाions करोes not need this work-around.
	 */
	अगर ((pdev->device == PCI_DEVICE_ID_NCR_53C810 &&
	     pdev->revision >= 0x10 && pdev->revision <= 0x11) ||
	    (pdev->device == PCI_DEVICE_ID_NCR_53C860 &&
	     pdev->revision <= 0x1))
		np->features &= ~(FE_WRIE|FE_ERL|FE_ERMP);

	/*
	 *  Select all supported special features.
	 *  If we are using on-board RAM क्रम scripts, prefetch (PFEN) 
	 *  करोes not help, but burst op fetch (BOF) करोes.
	 *  Disabling PFEN makes sure BOF will be used.
	 */
	अगर (np->features & FE_ERL)
		np->rv_dmode	|= ERL;		/* Enable Read Line */
	अगर (np->features & FE_BOF)
		np->rv_dmode	|= BOF;		/* Burst Opcode Fetch */
	अगर (np->features & FE_ERMP)
		np->rv_dmode	|= ERMP;	/* Enable Read Multiple */
#अगर 1
	अगर ((np->features & FE_PFEN) && !np->ram_ba)
#अन्यथा
	अगर (np->features & FE_PFEN)
#पूर्ण_अगर
		np->rv_dcntl	|= PFEN;	/* Prefetch Enable */
	अगर (np->features & FE_CLSE)
		np->rv_dcntl	|= CLSE;	/* Cache Line Size Enable */
	अगर (np->features & FE_WRIE)
		np->rv_ctest3	|= WRIE;	/* Write and Invalidate */
	अगर (np->features & FE_DFS)
		np->rv_ctest5	|= DFS;		/* Dma Fअगरo Size */

	/*
	 *  Select some other
	 */
	np->rv_ctest4	|= MPEE; /* Master parity checking */
	np->rv_scntl0	|= 0x0a; /*  full arb., ena parity, par->ATN  */

	/*
	 *  Get parity checking, host ID and verbose mode from NVRAM
	 */
	np->myaddr = 255;
	np->scsi_mode = 0;
	sym_nvram_setup_host(shost, np, nvram);

	/*
	 *  Get SCSI addr of host adapter (set by bios?).
	 */
	अगर (np->myaddr == 255) अणु
		np->myaddr = INB(np, nc_scid) & 0x07;
		अगर (!np->myaddr)
			np->myaddr = SYM_SETUP_HOST_ID;
	पूर्ण

	/*
	 *  Prepare initial io रेजिस्टर bits क्रम burst length
	 */
	sym_init_burst(np, burst_max);

	sym_set_bus_mode(np, nvram);

	/*
	 *  Set LED support from SCRIPTS.
	 *  Ignore this feature क्रम boards known to use a 
	 *  specअगरic GPIO wiring and क्रम the 895A, 896 
	 *  and 1010 that drive the LED directly.
	 */
	अगर ((SYM_SETUP_SCSI_LED || 
	     (nvram->type == SYM_SYMBIOS_NVRAM ||
	      (nvram->type == SYM_TEKRAM_NVRAM &&
	       pdev->device == PCI_DEVICE_ID_NCR_53C895))) &&
	    !(np->features & FE_LEDC) && !(np->sv_gpcntl & 0x01))
		np->features |= FE_LED0;

	/*
	 *  Set irq mode.
	 */
	चयन(SYM_SETUP_IRQ_MODE & 3) अणु
	हाल 2:
		np->rv_dcntl	|= IRQM;
		अवरोध;
	हाल 1:
		np->rv_dcntl	|= (np->sv_dcntl & IRQM);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 *  Configure tarमाला_लो according to driver setup.
	 *  If NVRAM present get tarमाला_लो setup from NVRAM.
	 */
	क्रम (i = 0 ; i < SYM_CONF_MAX_TARGET ; i++) अणु
		काष्ठा sym_tcb *tp = &np->target[i];

		tp->usrflags |= (SYM_DISC_ENABLED | SYM_TAGS_ENABLED);
		tp->usrtags = SYM_SETUP_MAX_TAG;
		tp->usr_width = np->maxwide;
		tp->usr_period = 9;

		sym_nvram_setup_target(tp, i, nvram);

		अगर (!tp->usrtags)
			tp->usrflags &= ~SYM_TAGS_ENABLED;
	पूर्ण

	/*
	 *  Let user know about the settings.
	 */
	म_लिखो("%s: %s, ID %d, Fast-%d, %s, %s\n", sym_name(np),
		sym_nvram_type(nvram), np->myaddr,
		(np->features & FE_ULTRA3) ? 80 : 
		(np->features & FE_ULTRA2) ? 40 : 
		(np->features & FE_ULTRA)  ? 20 : 10,
		sym_scsi_bus_mode(np->scsi_mode),
		(np->rv_scntl0 & 0xa)	? "parity checking" : "NO parity");
	/*
	 *  Tell him more on demand.
	 */
	अगर (sym_verbose) अणु
		म_लिखो("%s: %s IRQ line driver%s\n",
			sym_name(np),
			np->rv_dcntl & IRQM ? "totem pole" : "open drain",
			np->ram_ba ? ", using on-chip SRAM" : "");
		म_लिखो("%s: using %s firmware.\n", sym_name(np), np->fw_name);
		अगर (np->features & FE_NOPM)
			म_लिखो("%s: handling phase mismatch from SCRIPTS.\n", 
			       sym_name(np));
	पूर्ण
	/*
	 *  And still more.
	 */
	अगर (sym_verbose >= 2) अणु
		म_लिखो ("%s: initial SCNTL3/DMODE/DCNTL/CTEST3/4/5 = "
			"(hex) %02x/%02x/%02x/%02x/%02x/%02x\n",
			sym_name(np), np->sv_scntl3, np->sv_dmode, np->sv_dcntl,
			np->sv_ctest3, np->sv_ctest4, np->sv_ctest5);

		म_लिखो ("%s: final   SCNTL3/DMODE/DCNTL/CTEST3/4/5 = "
			"(hex) %02x/%02x/%02x/%02x/%02x/%02x\n",
			sym_name(np), np->rv_scntl3, np->rv_dmode, np->rv_dcntl,
			np->rv_ctest3, np->rv_ctest4, np->rv_ctest5);
	पूर्ण

	वापस 0;
पूर्ण

/*
 *  Test the pci bus snoop logic :-(
 *
 *  Has to be called with पूर्णांकerrupts disabled.
 */
#अगर_घोषित CONFIG_SCSI_SYM53C8XX_MMIO
अटल पूर्णांक sym_regtest(काष्ठा sym_hcb *np)
अणु
	रेजिस्टर अस्थिर u32 data;
	/*
	 *  chip रेजिस्टरs may NOT be cached.
	 *  ग_लिखो 0xffffffff to a पढ़ो only रेजिस्टर area,
	 *  and try to पढ़ो it back.
	 */
	data = 0xffffffff;
	OUTL(np, nc_dstat, data);
	data = INL(np, nc_dstat);
#अगर 1
	अगर (data == 0xffffffff) अणु
#अन्यथा
	अगर ((data & 0xe2f0fffd) != 0x02000080) अणु
#पूर्ण_अगर
		म_लिखो ("CACHE TEST FAILED: reg dstat-sstat2 readback %x.\n",
			(अचिन्हित) data);
		वापस 0x10;
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक sym_regtest(काष्ठा sym_hcb *np)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sym_snooptest(काष्ठा sym_hcb *np)
अणु
	u32 sym_rd, sym_wr, sym_bk, host_rd, host_wr, pc, dstat;
	पूर्णांक i, err;

	err = sym_regtest(np);
	अगर (err)
		वापस err;
restart_test:
	/*
	 *  Enable Master Parity Checking as we पूर्णांकend 
	 *  to enable it क्रम normal operations.
	 */
	OUTB(np, nc_ctest4, (np->rv_ctest4 & MPEE));
	/*
	 *  init
	 */
	pc  = SCRIPTZ_BA(np, snooptest);
	host_wr = 1;
	sym_wr  = 2;
	/*
	 *  Set memory and रेजिस्टर.
	 */
	np->scratch = cpu_to_scr(host_wr);
	OUTL(np, nc_temp, sym_wr);
	/*
	 *  Start script (exchange values)
	 */
	OUTL(np, nc_dsa, np->hcb_ba);
	OUTL_DSP(np, pc);
	/*
	 *  Wait 'til करोne (with समयout)
	 */
	क्रम (i=0; i<SYM_SNOOP_TIMEOUT; i++)
		अगर (INB(np, nc_istat) & (INTF|SIP|DIP))
			अवरोध;
	अगर (i>=SYM_SNOOP_TIMEOUT) अणु
		म_लिखो ("CACHE TEST FAILED: timeout.\n");
		वापस (0x20);
	पूर्ण
	/*
	 *  Check क्रम fatal DMA errors.
	 */
	dstat = INB(np, nc_dstat);
#अगर 1	/* Band aiding क्रम broken hardwares that fail PCI parity */
	अगर ((dstat & MDPE) && (np->rv_ctest4 & MPEE)) अणु
		म_लिखो ("%s: PCI DATA PARITY ERROR DETECTED - "
			"DISABLING MASTER DATA PARITY CHECKING.\n",
			sym_name(np));
		np->rv_ctest4 &= ~MPEE;
		जाओ restart_test;
	पूर्ण
#पूर्ण_अगर
	अगर (dstat & (MDPE|BF|IID)) अणु
		म_लिखो ("CACHE TEST FAILED: DMA error (dstat=0x%02x).", dstat);
		वापस (0x80);
	पूर्ण
	/*
	 *  Save termination position.
	 */
	pc = INL(np, nc_dsp);
	/*
	 *  Read memory and रेजिस्टर.
	 */
	host_rd = scr_to_cpu(np->scratch);
	sym_rd  = INL(np, nc_scratcha);
	sym_bk  = INL(np, nc_temp);
	/*
	 *  Check termination position.
	 */
	अगर (pc != SCRIPTZ_BA(np, snoखोलोd)+8) अणु
		म_लिखो ("CACHE TEST FAILED: script execution failed.\n");
		म_लिखो ("start=%08lx, pc=%08lx, end=%08lx\n", 
			(u_दीर्घ) SCRIPTZ_BA(np, snooptest), (u_दीर्घ) pc,
			(u_दीर्घ) SCRIPTZ_BA(np, snoखोलोd) +8);
		वापस (0x40);
	पूर्ण
	/*
	 *  Show results.
	 */
	अगर (host_wr != sym_rd) अणु
		म_लिखो ("CACHE TEST FAILED: host wrote %d, chip read %d.\n",
			(पूर्णांक) host_wr, (पूर्णांक) sym_rd);
		err |= 1;
	पूर्ण
	अगर (host_rd != sym_wr) अणु
		म_लिखो ("CACHE TEST FAILED: chip wrote %d, host read %d.\n",
			(पूर्णांक) sym_wr, (पूर्णांक) host_rd);
		err |= 2;
	पूर्ण
	अगर (sym_bk != sym_wr) अणु
		म_लिखो ("CACHE TEST FAILED: chip wrote %d, read back %d.\n",
			(पूर्णांक) sym_wr, (पूर्णांक) sym_bk);
		err |= 4;
	पूर्ण

	वापस err;
पूर्ण

/*
 *  log message क्रम real hard errors
 *
 *  sym0 targ 0?: ERROR (ds:si) (so-si-sd) (sx/s3/s4) @ name (dsp:dbc).
 *  	      reg: r0 r1 r2 r3 r4 r5 r6 ..... rf.
 *
 *  exception रेजिस्टर:
 *  	ds:	dstat
 *  	si:	sist
 *
 *  SCSI bus lines:
 *  	so:	control lines as driven by chip.
 *  	si:	control lines as seen by chip.
 *  	sd:	scsi data lines as seen by chip.
 *
 *  wide/fasपंचांगode:
 *  	sx:	sxfer  (see the manual)
 *  	s3:	scntl3 (see the manual)
 *  	s4:	scntl4 (see the manual)
 *
 *  current script command:
 *  	dsp:	script address (relative to start of script).
 *  	dbc:	first word of script command.
 *
 *  First 24 रेजिस्टर of the chip:
 *  	r0..rf
 */
अटल व्योम sym_log_hard_error(काष्ठा Scsi_Host *shost, u_लघु sist, u_अक्षर dstat)
अणु
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	u32	dsp;
	पूर्णांक	script_ofs;
	पूर्णांक	script_size;
	अक्षर	*script_name;
	u_अक्षर	*script_base;
	पूर्णांक	i;

	dsp	= INL(np, nc_dsp);

	अगर	(dsp > np->scripta_ba &&
		 dsp <= np->scripta_ba + np->scripta_sz) अणु
		script_ofs	= dsp - np->scripta_ba;
		script_size	= np->scripta_sz;
		script_base	= (u_अक्षर *) np->scripta0;
		script_name	= "scripta";
	पूर्ण
	अन्यथा अगर (np->scriptb_ba < dsp && 
		 dsp <= np->scriptb_ba + np->scriptb_sz) अणु
		script_ofs	= dsp - np->scriptb_ba;
		script_size	= np->scriptb_sz;
		script_base	= (u_अक्षर *) np->scriptb0;
		script_name	= "scriptb";
	पूर्ण अन्यथा अणु
		script_ofs	= dsp;
		script_size	= 0;
		script_base	= शून्य;
		script_name	= "mem";
	पूर्ण

	म_लिखो ("%s:%d: ERROR (%x:%x) (%x-%x-%x) (%x/%x/%x) @ (%s %x:%08x).\n",
		sym_name(np), (अचिन्हित)INB(np, nc_sdid)&0x0f, dstat, sist,
		(अचिन्हित)INB(np, nc_socl), (अचिन्हित)INB(np, nc_sbcl),
		(अचिन्हित)INB(np, nc_sbdl), (अचिन्हित)INB(np, nc_sxfer),
		(अचिन्हित)INB(np, nc_scntl3),
		(np->features & FE_C10) ?  (अचिन्हित)INB(np, nc_scntl4) : 0,
		script_name, script_ofs,   (अचिन्हित)INL(np, nc_dbc));

	अगर (((script_ofs & 3) == 0) &&
	    (अचिन्हित)script_ofs < script_size) अणु
		म_लिखो ("%s: script cmd = %08x\n", sym_name(np),
			scr_to_cpu((पूर्णांक) *(u32 *)(script_base + script_ofs)));
	पूर्ण

	म_लिखो("%s: regdump:", sym_name(np));
	क्रम (i = 0; i < 24; i++)
		म_लिखो(" %02x", (अचिन्हित)INB_OFF(np, i));
	म_लिखो(".\n");

	/*
	 *  PCI BUS error.
	 */
	अगर (dstat & (MDPE|BF))
		sym_log_bus_error(shost);
पूर्ण

व्योम sym_dump_रेजिस्टरs(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	u_लघु sist;
	u_अक्षर dstat;

	sist = INW(np, nc_sist);
	dstat = INB(np, nc_dstat);
	sym_log_hard_error(shost, sist, dstat);
पूर्ण

अटल काष्ठा sym_chip sym_dev_table[] = अणु
 अणुPCI_DEVICE_ID_NCR_53C810, 0x0f, "810", 4, 8, 4, 64,
 FE_ERLपूर्ण
 ,
#अगर_घोषित SYM_DEBUG_GENERIC_SUPPORT
 अणुPCI_DEVICE_ID_NCR_53C810, 0xff, "810a", 4,  8, 4, 1,
 FE_BOFपूर्ण
 ,
#अन्यथा
 अणुPCI_DEVICE_ID_NCR_53C810, 0xff, "810a", 4,  8, 4, 1,
 FE_CACHE_SET|FE_LDSTR|FE_PFEN|FE_BOFपूर्ण
 ,
#पूर्ण_अगर
 अणुPCI_DEVICE_ID_NCR_53C815, 0xff, "815", 4,  8, 4, 64,
 FE_BOF|FE_ERLपूर्ण
 ,
 अणुPCI_DEVICE_ID_NCR_53C825, 0x0f, "825", 6,  8, 4, 64,
 FE_WIDE|FE_BOF|FE_ERL|FE_DIFFपूर्ण
 ,
 अणुPCI_DEVICE_ID_NCR_53C825, 0xff, "825a", 6,  8, 4, 2,
 FE_WIDE|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_RAM|FE_DIFFपूर्ण
 ,
 अणुPCI_DEVICE_ID_NCR_53C860, 0xff, "860", 4,  8, 5, 1,
 FE_ULTRA|FE_CACHE_SET|FE_BOF|FE_LDSTR|FE_PFENपूर्ण
 ,
 अणुPCI_DEVICE_ID_NCR_53C875, 0x01, "875", 6, 16, 5, 2,
 FE_WIDE|FE_ULTRA|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|
 FE_RAM|FE_DIFF|FE_VARCLKपूर्ण
 ,
 अणुPCI_DEVICE_ID_NCR_53C875, 0xff, "875", 6, 16, 5, 2,
 FE_WIDE|FE_ULTRA|FE_DBLR|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|
 FE_RAM|FE_DIFF|FE_VARCLKपूर्ण
 ,
 अणुPCI_DEVICE_ID_NCR_53C875J, 0xff, "875J", 6, 16, 5, 2,
 FE_WIDE|FE_ULTRA|FE_DBLR|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|
 FE_RAM|FE_DIFF|FE_VARCLKपूर्ण
 ,
 अणुPCI_DEVICE_ID_NCR_53C885, 0xff, "885", 6, 16, 5, 2,
 FE_WIDE|FE_ULTRA|FE_DBLR|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|
 FE_RAM|FE_DIFF|FE_VARCLKपूर्ण
 ,
#अगर_घोषित SYM_DEBUG_GENERIC_SUPPORT
 अणुPCI_DEVICE_ID_NCR_53C895, 0xff, "895", 6, 31, 7, 2,
 FE_WIDE|FE_ULTRA2|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|
 FE_RAM|FE_LCKFRQपूर्ण
 ,
#अन्यथा
 अणुPCI_DEVICE_ID_NCR_53C895, 0xff, "895", 6, 31, 7, 2,
 FE_WIDE|FE_ULTRA2|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|
 FE_RAM|FE_LCKFRQपूर्ण
 ,
#पूर्ण_अगर
 अणुPCI_DEVICE_ID_NCR_53C896, 0xff, "896", 6, 31, 7, 4,
 FE_WIDE|FE_ULTRA2|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|
 FE_RAM|FE_RAM8K|FE_64BIT|FE_DAC|FE_IO256|FE_NOPM|FE_LEDC|FE_LCKFRQपूर्ण
 ,
 अणुPCI_DEVICE_ID_LSI_53C895A, 0xff, "895a", 6, 31, 7, 4,
 FE_WIDE|FE_ULTRA2|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|
 FE_RAM|FE_RAM8K|FE_DAC|FE_IO256|FE_NOPM|FE_LEDC|FE_LCKFRQपूर्ण
 ,
 अणुPCI_DEVICE_ID_LSI_53C875A, 0xff, "875a", 6, 31, 7, 4,
 FE_WIDE|FE_ULTRA|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|
 FE_RAM|FE_DAC|FE_IO256|FE_NOPM|FE_LEDC|FE_LCKFRQपूर्ण
 ,
 अणुPCI_DEVICE_ID_LSI_53C1010_33, 0x00, "1010-33", 6, 31, 7, 8,
 FE_WIDE|FE_ULTRA3|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFBC|FE_LDSTR|FE_PFEN|
 FE_RAM|FE_RAM8K|FE_64BIT|FE_DAC|FE_IO256|FE_NOPM|FE_LEDC|FE_CRC|
 FE_C10पूर्ण
 ,
 अणुPCI_DEVICE_ID_LSI_53C1010_33, 0xff, "1010-33", 6, 31, 7, 8,
 FE_WIDE|FE_ULTRA3|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFBC|FE_LDSTR|FE_PFEN|
 FE_RAM|FE_RAM8K|FE_64BIT|FE_DAC|FE_IO256|FE_NOPM|FE_LEDC|FE_CRC|
 FE_C10|FE_U3ENपूर्ण
 ,
 अणुPCI_DEVICE_ID_LSI_53C1010_66, 0xff, "1010-66", 6, 31, 7, 8,
 FE_WIDE|FE_ULTRA3|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFBC|FE_LDSTR|FE_PFEN|
 FE_RAM|FE_RAM8K|FE_64BIT|FE_DAC|FE_IO256|FE_NOPM|FE_LEDC|FE_66MHZ|FE_CRC|
 FE_C10|FE_U3ENपूर्ण
 ,
 अणुPCI_DEVICE_ID_LSI_53C1510, 0xff, "1510d", 6, 31, 7, 4,
 FE_WIDE|FE_ULTRA2|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|
 FE_RAM|FE_IO256|FE_LEDCपूर्ण
पूर्ण;

#घोषणा sym_num_devs (ARRAY_SIZE(sym_dev_table))

/*
 *  Look up the chip table.
 *
 *  Return a poपूर्णांकer to the chip entry अगर found, 
 *  zero otherwise.
 */
काष्ठा sym_chip *
sym_lookup_chip_table (u_लघु device_id, u_अक्षर revision)
अणु
	काष्ठा	sym_chip *chip;
	पूर्णांक	i;

	क्रम (i = 0; i < sym_num_devs; i++) अणु
		chip = &sym_dev_table[i];
		अगर (device_id != chip->device_id)
			जारी;
		अगर (revision > chip->revision_id)
			जारी;
		वापस chip;
	पूर्ण

	वापस शून्य;
पूर्ण

#अगर SYM_CONF_DMA_ADDRESSING_MODE == 2
/*
 *  Lookup the 64 bit DMA segments map.
 *  This is only used अगर the direct mapping 
 *  has been unsuccessful.
 */
पूर्णांक sym_lookup_dmap(काष्ठा sym_hcb *np, u32 h, पूर्णांक s)
अणु
	पूर्णांक i;

	अगर (!use_dac(np))
		जाओ weird;

	/* Look up existing mappings */
	क्रम (i = SYM_DMAP_SIZE-1; i > 0; i--) अणु
		अगर (h == np->dmap_bah[i])
			वापस i;
	पूर्ण
	/* If direct mapping is मुक्त, get it */
	अगर (!np->dmap_bah[s])
		जाओ new;
	/* Collision -> lookup मुक्त mappings */
	क्रम (s = SYM_DMAP_SIZE-1; s > 0; s--) अणु
		अगर (!np->dmap_bah[s])
			जाओ new;
	पूर्ण
weird:
	panic("sym: ran out of 64 bit DMA segment registers");
	वापस -1;
new:
	np->dmap_bah[s] = h;
	np->dmap_dirty = 1;
	वापस s;
पूर्ण

/*
 *  Update IO रेजिस्टरs scratch C..R so they will be 
 *  in sync. with queued CCB expectations.
 */
अटल व्योम sym_update_dmap_regs(काष्ठा sym_hcb *np)
अणु
	पूर्णांक o, i;

	अगर (!np->dmap_dirty)
		वापस;
	o = दुरत्व(काष्ठा sym_reg, nc_scrx[0]);
	क्रम (i = 0; i < SYM_DMAP_SIZE; i++) अणु
		OUTL_OFF(np, o, np->dmap_bah[i]);
		o += 4;
	पूर्ण
	np->dmap_dirty = 0;
पूर्ण
#पूर्ण_अगर

/* Enक्रमce all the fiddly SPI rules and the chip limitations */
अटल व्योम sym_check_goals(काष्ठा sym_hcb *np, काष्ठा scsi_target *starget,
		काष्ठा sym_trans *goal)
अणु
	अगर (!spi_support_wide(starget))
		goal->width = 0;

	अगर (!spi_support_sync(starget)) अणु
		goal->iu = 0;
		goal->dt = 0;
		goal->qas = 0;
		goal->offset = 0;
		वापस;
	पूर्ण

	अगर (spi_support_dt(starget)) अणु
		अगर (spi_support_dt_only(starget))
			goal->dt = 1;

		अगर (goal->offset == 0)
			goal->dt = 0;
	पूर्ण अन्यथा अणु
		goal->dt = 0;
	पूर्ण

	/* Some tarमाला_लो fail to properly negotiate DT in SE mode */
	अगर ((np->scsi_mode != SMODE_LVD) || !(np->features & FE_U3EN))
		goal->dt = 0;

	अगर (goal->dt) अणु
		/* all DT transfers must be wide */
		goal->width = 1;
		अगर (goal->offset > np->maxoffs_dt)
			goal->offset = np->maxoffs_dt;
		अगर (goal->period < np->minsync_dt)
			goal->period = np->minsync_dt;
		अगर (goal->period > np->maxsync_dt)
			goal->period = np->maxsync_dt;
	पूर्ण अन्यथा अणु
		goal->iu = goal->qas = 0;
		अगर (goal->offset > np->maxoffs)
			goal->offset = np->maxoffs;
		अगर (goal->period < np->minsync)
			goal->period = np->minsync;
		अगर (goal->period > np->maxsync)
			goal->period = np->maxsync;
	पूर्ण
पूर्ण

/*
 *  Prepare the next negotiation message अगर needed.
 *
 *  Fill in the part of message buffer that contains the 
 *  negotiation and the nego_status field of the CCB.
 *  Returns the size of the message in bytes.
 */
अटल पूर्णांक sym_prepare_nego(काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp, u_अक्षर *msgptr)
अणु
	काष्ठा sym_tcb *tp = &np->target[cp->target];
	काष्ठा scsi_target *starget = tp->starget;
	काष्ठा sym_trans *goal = &tp->tgoal;
	पूर्णांक msglen = 0;
	पूर्णांक nego;

	sym_check_goals(np, starget, goal);

	/*
	 * Many devices implement PPR in a buggy way, so only use it अगर we
	 * really want to.
	 */
	अगर (goal->renego == NS_PPR || (goal->offset &&
	    (goal->iu || goal->dt || goal->qas || (goal->period < 0xa)))) अणु
		nego = NS_PPR;
	पूर्ण अन्यथा अगर (goal->renego == NS_WIDE || goal->width) अणु
		nego = NS_WIDE;
	पूर्ण अन्यथा अगर (goal->renego == NS_SYNC || goal->offset) अणु
		nego = NS_SYNC;
	पूर्ण अन्यथा अणु
		goal->check_nego = 0;
		nego = 0;
	पूर्ण

	चयन (nego) अणु
	हाल NS_SYNC:
		msglen += spi_populate_sync_msg(msgptr + msglen, goal->period,
				goal->offset);
		अवरोध;
	हाल NS_WIDE:
		msglen += spi_populate_width_msg(msgptr + msglen, goal->width);
		अवरोध;
	हाल NS_PPR:
		msglen += spi_populate_ppr_msg(msgptr + msglen, goal->period,
				goal->offset, goal->width,
				(goal->iu ? PPR_OPT_IU : 0) |
					(goal->dt ? PPR_OPT_DT : 0) |
					(goal->qas ? PPR_OPT_QAS : 0));
		अवरोध;
	पूर्ण

	cp->nego_status = nego;

	अगर (nego) अणु
		tp->nego_cp = cp; /* Keep track a nego will be perक्रमmed */
		अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
			sym_prपूर्णांक_nego_msg(np, cp->target, 
					  nego == NS_SYNC ? "sync msgout" :
					  nego == NS_WIDE ? "wide msgout" :
					  "ppr msgout", msgptr);
		पूर्ण
	पूर्ण

	वापस msglen;
पूर्ण

/*
 *  Insert a job पूर्णांकo the start queue.
 */
व्योम sym_put_start_queue(काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp)
अणु
	u_लघु	qidx;

#अगर_घोषित SYM_CONF_IARB_SUPPORT
	/*
	 *  If the previously queued CCB is not yet करोne, 
	 *  set the IARB hपूर्णांक. The SCRIPTS will go with IARB 
	 *  क्रम this job when starting the previous one.
	 *  We leave devices a chance to win arbitration by 
	 *  not using more than 'iarb_max' consecutive 
	 *  immediate arbitrations.
	 */
	अगर (np->last_cp && np->iarb_count < np->iarb_max) अणु
		np->last_cp->host_flags |= HF_HINT_IARB;
		++np->iarb_count;
	पूर्ण
	अन्यथा
		np->iarb_count = 0;
	np->last_cp = cp;
#पूर्ण_अगर

#अगर   SYM_CONF_DMA_ADDRESSING_MODE == 2
	/*
	 *  Make SCRIPTS aware of the 64 bit DMA 
	 *  segment रेजिस्टरs not being up-to-date.
	 */
	अगर (np->dmap_dirty)
		cp->host_xflags |= HX_DMAP_सूचीTY;
#पूर्ण_अगर

	/*
	 *  Insert first the idle task and then our job.
	 *  The MBs should ensure proper ordering.
	 */
	qidx = np->squeueput + 2;
	अगर (qidx >= MAX_QUEUE*2) qidx = 0;

	np->squeue [qidx]	   = cpu_to_scr(np->idletask_ba);
	MEMORY_WRITE_BARRIER();
	np->squeue [np->squeueput] = cpu_to_scr(cp->ccb_ba);

	np->squeueput = qidx;

	अगर (DEBUG_FLAGS & DEBUG_QUEUE)
		scmd_prपूर्णांकk(KERN_DEBUG, cp->cmd, "queuepos=%d\n",
							np->squeueput);

	/*
	 *  Script processor may be रुकोing क्रम reselect.
	 *  Wake it up.
	 */
	MEMORY_WRITE_BARRIER();
	OUTB(np, nc_istat, SIGP|np->istat_sem);
पूर्ण

#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
/*
 *  Start next पढ़ोy-to-start CCBs.
 */
व्योम sym_start_next_ccbs(काष्ठा sym_hcb *np, काष्ठा sym_lcb *lp, पूर्णांक maxn)
अणु
	SYM_QUEHEAD *qp;
	काष्ठा sym_ccb *cp;

	/* 
	 *  Paranoia, as usual. :-)
	 */
	निश्चित(!lp->started_tags || !lp->started_no_tag);

	/*
	 *  Try to start as many commands as asked by caller.
	 *  Prevent from having both tagged and untagged 
	 *  commands queued to the device at the same समय.
	 */
	जबतक (maxn--) अणु
		qp = sym_remque_head(&lp->रुकोing_ccbq);
		अगर (!qp)
			अवरोध;
		cp = sym_que_entry(qp, काष्ठा sym_ccb, link2_ccbq);
		अगर (cp->tag != NO_TAG) अणु
			अगर (lp->started_no_tag ||
			    lp->started_tags >= lp->started_max) अणु
				sym_insque_head(qp, &lp->रुकोing_ccbq);
				अवरोध;
			पूर्ण
			lp->itlq_tbl[cp->tag] = cpu_to_scr(cp->ccb_ba);
			lp->head.resel_sa =
				cpu_to_scr(SCRIPTA_BA(np, resel_tag));
			++lp->started_tags;
		पूर्ण अन्यथा अणु
			अगर (lp->started_no_tag || lp->started_tags) अणु
				sym_insque_head(qp, &lp->रुकोing_ccbq);
				अवरोध;
			पूर्ण
			lp->head.itl_task_sa = cpu_to_scr(cp->ccb_ba);
			lp->head.resel_sa =
			      cpu_to_scr(SCRIPTA_BA(np, resel_no_tag));
			++lp->started_no_tag;
		पूर्ण
		cp->started = 1;
		sym_insque_tail(qp, &lp->started_ccbq);
		sym_put_start_queue(np, cp);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* SYM_OPT_HANDLE_DEVICE_QUEUEING */

/*
 *  The chip may have completed jobs. Look at the DONE QUEUE.
 *
 *  On paper, memory पढ़ो barriers may be needed here to 
 *  prevent out of order LOADs by the CPU from having 
 *  prefetched stale data prior to DMA having occurred.
 */
अटल पूर्णांक sym_wakeup_करोne (काष्ठा sym_hcb *np)
अणु
	काष्ठा sym_ccb *cp;
	पूर्णांक i, n;
	u32 dsa;

	n = 0;
	i = np->dqueueget;

	/* MEMORY_READ_BARRIER(); */
	जबतक (1) अणु
		dsa = scr_to_cpu(np->dqueue[i]);
		अगर (!dsa)
			अवरोध;
		np->dqueue[i] = 0;
		अगर ((i = i+2) >= MAX_QUEUE*2)
			i = 0;

		cp = sym_ccb_from_dsa(np, dsa);
		अगर (cp) अणु
			MEMORY_READ_BARRIER();
			sym_complete_ok (np, cp);
			++n;
		पूर्ण
		अन्यथा
			म_लिखो ("%s: bad DSA (%x) in done queue.\n",
				sym_name(np), (u_पूर्णांक) dsa);
	पूर्ण
	np->dqueueget = i;

	वापस n;
पूर्ण

/*
 *  Complete all CCBs queued to the COMP queue.
 *
 *  These CCBs are assumed:
 *  - Not to be referenced either by devices or 
 *    SCRIPTS-related queues and datas.
 *  - To have to be completed with an error condition 
 *    or requeued.
 *
 *  The device queue मुक्तze count is incremented 
 *  क्रम each CCB that करोes not prevent this.
 *  This function is called when all CCBs involved 
 *  in error handling/recovery have been reaped.
 */
अटल व्योम sym_flush_comp_queue(काष्ठा sym_hcb *np, पूर्णांक cam_status)
अणु
	SYM_QUEHEAD *qp;
	काष्ठा sym_ccb *cp;

	जबतक ((qp = sym_remque_head(&np->comp_ccbq)) != शून्य) अणु
		काष्ठा scsi_cmnd *cmd;
		cp = sym_que_entry(qp, काष्ठा sym_ccb, link_ccbq);
		sym_insque_tail(&cp->link_ccbq, &np->busy_ccbq);
		/* Leave quiet CCBs रुकोing क्रम resources */
		अगर (cp->host_status == HS_WAIT)
			जारी;
		cmd = cp->cmd;
		अगर (cam_status)
			sym_set_cam_status(cmd, cam_status);
#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
		अगर (sym_get_cam_status(cmd) == DID_SOFT_ERROR) अणु
			काष्ठा sym_tcb *tp = &np->target[cp->target];
			काष्ठा sym_lcb *lp = sym_lp(tp, cp->lun);
			अगर (lp) अणु
				sym_remque(&cp->link2_ccbq);
				sym_insque_tail(&cp->link2_ccbq,
				                &lp->रुकोing_ccbq);
				अगर (cp->started) अणु
					अगर (cp->tag != NO_TAG)
						--lp->started_tags;
					अन्यथा
						--lp->started_no_tag;
				पूर्ण
			पूर्ण
			cp->started = 0;
			जारी;
		पूर्ण
#पूर्ण_अगर
		sym_मुक्त_ccb(np, cp);
		sym_xpt_करोne(np, cmd);
	पूर्ण
पूर्ण

/*
 *  Complete all active CCBs with error.
 *  Used on CHIP/SCSI RESET.
 */
अटल व्योम sym_flush_busy_queue (काष्ठा sym_hcb *np, पूर्णांक cam_status)
अणु
	/*
	 *  Move all active CCBs to the COMP queue 
	 *  and flush this queue.
	 */
	sym_que_splice(&np->busy_ccbq, &np->comp_ccbq);
	sym_que_init(&np->busy_ccbq);
	sym_flush_comp_queue(np, cam_status);
पूर्ण

/*
 *  Start chip.
 *
 *  'reason' means:
 *     0: initialisation.
 *     1: SCSI BUS RESET delivered or received.
 *     2: SCSI BUS MODE changed.
 */
व्योम sym_start_up(काष्ठा Scsi_Host *shost, पूर्णांक reason)
अणु
	काष्ठा sym_data *sym_data = shost_priv(shost);
	काष्ठा pci_dev *pdev = sym_data->pdev;
	काष्ठा sym_hcb *np = sym_data->ncb;
 	पूर्णांक	i;
	u32	phys;

 	/*
	 *  Reset chip अगर asked, otherwise just clear fअगरos.
 	 */
	अगर (reason == 1)
		sym_soft_reset(np);
	अन्यथा अणु
		OUTB(np, nc_stest3, TE|CSF);
		OUTONB(np, nc_ctest3, CLF);
	पूर्ण
 
	/*
	 *  Clear Start Queue
	 */
	phys = np->squeue_ba;
	क्रम (i = 0; i < MAX_QUEUE*2; i += 2) अणु
		np->squeue[i]   = cpu_to_scr(np->idletask_ba);
		np->squeue[i+1] = cpu_to_scr(phys + (i+2)*4);
	पूर्ण
	np->squeue[MAX_QUEUE*2-1] = cpu_to_scr(phys);

	/*
	 *  Start at first entry.
	 */
	np->squeueput = 0;

	/*
	 *  Clear Done Queue
	 */
	phys = np->dqueue_ba;
	क्रम (i = 0; i < MAX_QUEUE*2; i += 2) अणु
		np->dqueue[i]   = 0;
		np->dqueue[i+1] = cpu_to_scr(phys + (i+2)*4);
	पूर्ण
	np->dqueue[MAX_QUEUE*2-1] = cpu_to_scr(phys);

	/*
	 *  Start at first entry.
	 */
	np->dqueueget = 0;

	/*
	 *  Install patches in scripts.
	 *  This also let poपूर्णांक to first position the start 
	 *  and करोne queue poपूर्णांकers used from SCRIPTS.
	 */
	np->fw_patch(shost);

	/*
	 *  Wakeup all pending jobs.
	 */
	sym_flush_busy_queue(np, DID_RESET);

	/*
	 *  Init chip.
	 */
	OUTB(np, nc_istat,  0x00);			/*  Remove Reset, पात */
	INB(np, nc_mbox1);
	udelay(2000); /* The 895 needs समय क्रम the bus mode to settle */

	OUTB(np, nc_scntl0, np->rv_scntl0 | 0xc0);
					/*  full arb., ena parity, par->ATN  */
	OUTB(np, nc_scntl1, 0x00);		/*  odd parity, and हटाओ CRST!! */

	sym_selectघड़ी(np, np->rv_scntl3);	/* Select SCSI घड़ी */

	OUTB(np, nc_scid  , RRE|np->myaddr);	/* Adapter SCSI address */
	OUTW(np, nc_respid, 1ul<<np->myaddr);	/* Id to respond to */
	OUTB(np, nc_istat , SIGP	);		/*  Signal Process */
	OUTB(np, nc_dmode , np->rv_dmode);		/* Burst length, dma mode */
	OUTB(np, nc_ctest5, np->rv_ctest5);	/* Large fअगरo + large burst */

	OUTB(np, nc_dcntl , NOCOM|np->rv_dcntl);	/* Protect SFBR */
	OUTB(np, nc_ctest3, np->rv_ctest3);	/* Write and invalidate */
	OUTB(np, nc_ctest4, np->rv_ctest4);	/* Master parity checking */

	/* Extended Sreq/Sack filtering not supported on the C10 */
	अगर (np->features & FE_C10)
		OUTB(np, nc_stest2, np->rv_stest2);
	अन्यथा
		OUTB(np, nc_stest2, EXT|np->rv_stest2);

	OUTB(np, nc_stest3, TE);			/* TolerANT enable */
	OUTB(np, nc_sसमय0, 0x0c);			/* HTH disabled  STO 0.25 sec */

	/*
	 *  For now, disable AIP generation on C1010-66.
	 */
	अगर (pdev->device == PCI_DEVICE_ID_LSI_53C1010_66)
		OUTB(np, nc_aipcntl1, DISAIP);

	/*
	 *  C10101 rev. 0 errata.
	 *  Errant SGE's when in narrow. Write bits 4 & 5 of
	 *  STEST1 रेजिस्टर to disable SGE. We probably should करो 
	 *  that from SCRIPTS क्रम each selection/reselection, but 
	 *  I just करोn't want. :)
	 */
	अगर (pdev->device == PCI_DEVICE_ID_LSI_53C1010_33 &&
	    pdev->revision < 1)
		OUTB(np, nc_stest1, INB(np, nc_stest1) | 0x30);

	/*
	 *  DEL 441 - 53C876 Rev 5 - Part Number 609-0392787/2788 - ITEM 2.
	 *  Disable overlapped arbitration क्रम some dual function devices, 
	 *  regardless revision id (kind of post-chip-design feature. ;-))
	 */
	अगर (pdev->device == PCI_DEVICE_ID_NCR_53C875)
		OUTB(np, nc_ctest0, (1<<5));
	अन्यथा अगर (pdev->device == PCI_DEVICE_ID_NCR_53C896)
		np->rv_ccntl0 |= DPR;

	/*
	 *  Write CCNTL0/CCNTL1 क्रम chips capable of 64 bit addressing 
	 *  and/or hardware phase mismatch, since only such chips 
	 *  seem to support those IO रेजिस्टरs.
	 */
	अगर (np->features & (FE_DAC|FE_NOPM)) अणु
		OUTB(np, nc_ccntl0, np->rv_ccntl0);
		OUTB(np, nc_ccntl1, np->rv_ccntl1);
	पूर्ण

#अगर	SYM_CONF_DMA_ADDRESSING_MODE == 2
	/*
	 *  Set up scratch C and DRS IO रेजिस्टरs to map the 32 bit 
	 *  DMA address range our data काष्ठाures are located in.
	 */
	अगर (use_dac(np)) अणु
		np->dmap_bah[0] = 0;	/* ??? */
		OUTL(np, nc_scrx[0], np->dmap_bah[0]);
		OUTL(np, nc_drs, np->dmap_bah[0]);
	पूर्ण
#पूर्ण_अगर

	/*
	 *  If phase mismatch handled by scripts (895A/896/1010),
	 *  set PM jump addresses.
	 */
	अगर (np->features & FE_NOPM) अणु
		OUTL(np, nc_pmjad1, SCRIPTB_BA(np, pm_handle));
		OUTL(np, nc_pmjad2, SCRIPTB_BA(np, pm_handle));
	पूर्ण

	/*
	 *    Enable GPIO0 pin क्रम writing अगर LED support from SCRIPTS.
	 *    Also set GPIO5 and clear GPIO6 अगर hardware LED control.
	 */
	अगर (np->features & FE_LED0)
		OUTB(np, nc_gpcntl, INB(np, nc_gpcntl) & ~0x01);
	अन्यथा अगर (np->features & FE_LEDC)
		OUTB(np, nc_gpcntl, (INB(np, nc_gpcntl) & ~0x41) | 0x20);

	/*
	 *      enable पूर्णांकs
	 */
	OUTW(np, nc_sien , STO|HTH|MA|SGE|UDC|RST|PAR);
	OUTB(np, nc_dien , MDPE|BF|SSI|SIR|IID);

	/*
	 *  For 895/6 enable SBMC पूर्णांकerrupt and save current SCSI bus mode.
	 *  Try to eat the spurious SBMC पूर्णांकerrupt that may occur when 
	 *  we reset the chip but not the SCSI BUS (at initialization).
	 */
	अगर (np->features & (FE_ULTRA2|FE_ULTRA3)) अणु
		OUTONW(np, nc_sien, SBMC);
		अगर (reason == 0) अणु
			INB(np, nc_mbox1);
			mdelay(100);
			INW(np, nc_sist);
		पूर्ण
		np->scsi_mode = INB(np, nc_stest4) & SMODE;
	पूर्ण

	/*
	 *  Fill in target काष्ठाure.
	 *  Reinitialize usrsync.
	 *  Reinitialize usrwide.
	 *  Prepare sync negotiation according to actual SCSI bus mode.
	 */
	क्रम (i=0;i<SYM_CONF_MAX_TARGET;i++) अणु
		काष्ठा sym_tcb *tp = &np->target[i];

		tp->to_reset  = 0;
		tp->head.sval = 0;
		tp->head.wval = np->rv_scntl3;
		tp->head.uval = 0;
		अगर (tp->lun0p)
			tp->lun0p->to_clear = 0;
		अगर (tp->lunmp) अणु
			पूर्णांक ln;

			क्रम (ln = 1; ln < SYM_CONF_MAX_LUN; ln++)
				अगर (tp->lunmp[ln])
					tp->lunmp[ln]->to_clear = 0;
		पूर्ण
	पूर्ण

	/*
	 *  Download SCSI SCRIPTS to on-chip RAM अगर present,
	 *  and start script processor.
	 *  We करो the करोwnload preferently from the CPU.
	 *  For platक्रमms that may not support PCI memory mapping,
	 *  we use simple SCRIPTS that perक्रमms MEMORY MOVEs.
	 */
	phys = SCRIPTA_BA(np, init);
	अगर (np->ram_ba) अणु
		अगर (sym_verbose >= 2)
			म_लिखो("%s: Downloading SCSI SCRIPTS.\n", sym_name(np));
		स_नकल_toio(np->s.ramaddr, np->scripta0, np->scripta_sz);
		अगर (np->features & FE_RAM8K) अणु
			स_नकल_toio(np->s.ramaddr + 4096, np->scriptb0, np->scriptb_sz);
			phys = scr_to_cpu(np->scr_ram_seg);
			OUTL(np, nc_mmws, phys);
			OUTL(np, nc_mmrs, phys);
			OUTL(np, nc_sfs,  phys);
			phys = SCRIPTB_BA(np, start64);
		पूर्ण
	पूर्ण

	np->istat_sem = 0;

	OUTL(np, nc_dsa, np->hcb_ba);
	OUTL_DSP(np, phys);

	/*
	 *  Notअगरy the XPT about the RESET condition.
	 */
	अगर (reason != 0)
		sym_xpt_async_bus_reset(np);
पूर्ण

/*
 *  Switch trans mode क्रम current job and its target.
 */
अटल व्योम sym_settrans(काष्ठा sym_hcb *np, पूर्णांक target, u_अक्षर opts, u_अक्षर ofs,
			 u_अक्षर per, u_अक्षर wide, u_अक्षर भाग, u_अक्षर fak)
अणु
	SYM_QUEHEAD *qp;
	u_अक्षर sval, wval, uval;
	काष्ठा sym_tcb *tp = &np->target[target];

	निश्चित(target == (INB(np, nc_sdid) & 0x0f));

	sval = tp->head.sval;
	wval = tp->head.wval;
	uval = tp->head.uval;

#अगर 0
	म_लिखो("XXXX sval=%x wval=%x uval=%x (%x)\n", 
		sval, wval, uval, np->rv_scntl3);
#पूर्ण_अगर
	/*
	 *  Set the offset.
	 */
	अगर (!(np->features & FE_C10))
		sval = (sval & ~0x1f) | ofs;
	अन्यथा
		sval = (sval & ~0x3f) | ofs;

	/*
	 *  Set the sync भागisor and extra घड़ी factor.
	 */
	अगर (ofs != 0) अणु
		wval = (wval & ~0x70) | ((भाग+1) << 4);
		अगर (!(np->features & FE_C10))
			sval = (sval & ~0xe0) | (fak << 5);
		अन्यथा अणु
			uval = uval & ~(XCLKH_ST|XCLKH_DT|XCLKS_ST|XCLKS_DT);
			अगर (fak >= 1) uval |= (XCLKH_ST|XCLKH_DT);
			अगर (fak >= 2) uval |= (XCLKS_ST|XCLKS_DT);
		पूर्ण
	पूर्ण

	/*
	 *  Set the bus width.
	 */
	wval = wval & ~EWS;
	अगर (wide != 0)
		wval |= EWS;

	/*
	 *  Set misc. ultra enable bits.
	 */
	अगर (np->features & FE_C10) अणु
		uval = uval & ~(U3EN|AIPCKEN);
		अगर (opts)	अणु
			निश्चित(np->features & FE_U3EN);
			uval |= U3EN;
		पूर्ण
	पूर्ण अन्यथा अणु
		wval = wval & ~ULTRA;
		अगर (per <= 12)	wval |= ULTRA;
	पूर्ण

	/*
	 *   Stop there अगर sync parameters are unchanged.
	 */
	अगर (tp->head.sval == sval && 
	    tp->head.wval == wval &&
	    tp->head.uval == uval)
		वापस;
	tp->head.sval = sval;
	tp->head.wval = wval;
	tp->head.uval = uval;

	/*
	 *  Disable extended Sreq/Sack filtering अगर per < 50.
	 *  Not supported on the C1010.
	 */
	अगर (per < 50 && !(np->features & FE_C10))
		OUTOFFB(np, nc_stest2, EXT);

	/*
	 *  set actual value and sync_status
	 */
	OUTB(np, nc_sxfer,  tp->head.sval);
	OUTB(np, nc_scntl3, tp->head.wval);

	अगर (np->features & FE_C10) अणु
		OUTB(np, nc_scntl4, tp->head.uval);
	पूर्ण

	/*
	 *  patch ALL busy ccbs of this target.
	 */
	FOR_EACH_QUEUED_ELEMENT(&np->busy_ccbq, qp) अणु
		काष्ठा sym_ccb *cp;
		cp = sym_que_entry(qp, काष्ठा sym_ccb, link_ccbq);
		अगर (cp->target != target)
			जारी;
		cp->phys.select.sel_scntl3 = tp->head.wval;
		cp->phys.select.sel_sxfer  = tp->head.sval;
		अगर (np->features & FE_C10) अणु
			cp->phys.select.sel_scntl4 = tp->head.uval;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sym_announce_transfer_rate(काष्ठा sym_tcb *tp)
अणु
	काष्ठा scsi_target *starget = tp->starget;

	अगर (tp->tprपूर्णांक.period != spi_period(starget) ||
	    tp->tprपूर्णांक.offset != spi_offset(starget) ||
	    tp->tprपूर्णांक.width != spi_width(starget) ||
	    tp->tprपूर्णांक.iu != spi_iu(starget) ||
	    tp->tprपूर्णांक.dt != spi_dt(starget) ||
	    tp->tprपूर्णांक.qas != spi_qas(starget) ||
	    !tp->tprपूर्णांक.check_nego) अणु
		tp->tprपूर्णांक.period = spi_period(starget);
		tp->tprपूर्णांक.offset = spi_offset(starget);
		tp->tprपूर्णांक.width = spi_width(starget);
		tp->tprपूर्णांक.iu = spi_iu(starget);
		tp->tprपूर्णांक.dt = spi_dt(starget);
		tp->tprपूर्णांक.qas = spi_qas(starget);
		tp->tprपूर्णांक.check_nego = 1;

		spi_display_xfer_agreement(starget);
	पूर्ण
पूर्ण

/*
 *  We received a WDTR.
 *  Let everything be aware of the changes.
 */
अटल व्योम sym_setwide(काष्ठा sym_hcb *np, पूर्णांक target, u_अक्षर wide)
अणु
	काष्ठा sym_tcb *tp = &np->target[target];
	काष्ठा scsi_target *starget = tp->starget;

	sym_settrans(np, target, 0, 0, 0, wide, 0, 0);

	अगर (wide)
		tp->tgoal.renego = NS_WIDE;
	अन्यथा
		tp->tgoal.renego = 0;
	tp->tgoal.check_nego = 0;
	tp->tgoal.width = wide;
	spi_offset(starget) = 0;
	spi_period(starget) = 0;
	spi_width(starget) = wide;
	spi_iu(starget) = 0;
	spi_dt(starget) = 0;
	spi_qas(starget) = 0;

	अगर (sym_verbose >= 3)
		sym_announce_transfer_rate(tp);
पूर्ण

/*
 *  We received a SDTR.
 *  Let everything be aware of the changes.
 */
अटल व्योम
sym_setsync(काष्ठा sym_hcb *np, पूर्णांक target,
            u_अक्षर ofs, u_अक्षर per, u_अक्षर भाग, u_अक्षर fak)
अणु
	काष्ठा sym_tcb *tp = &np->target[target];
	काष्ठा scsi_target *starget = tp->starget;
	u_अक्षर wide = (tp->head.wval & EWS) ? BUS_16_BIT : BUS_8_BIT;

	sym_settrans(np, target, 0, ofs, per, wide, भाग, fak);

	अगर (wide)
		tp->tgoal.renego = NS_WIDE;
	अन्यथा अगर (ofs)
		tp->tgoal.renego = NS_SYNC;
	अन्यथा
		tp->tgoal.renego = 0;
	spi_period(starget) = per;
	spi_offset(starget) = ofs;
	spi_iu(starget) = spi_dt(starget) = spi_qas(starget) = 0;

	अगर (!tp->tgoal.dt && !tp->tgoal.iu && !tp->tgoal.qas) अणु
		tp->tgoal.period = per;
		tp->tgoal.offset = ofs;
		tp->tgoal.check_nego = 0;
	पूर्ण

	sym_announce_transfer_rate(tp);
पूर्ण

/*
 *  We received a PPR.
 *  Let everything be aware of the changes.
 */
अटल व्योम 
sym_setpprot(काष्ठा sym_hcb *np, पूर्णांक target, u_अक्षर opts, u_अक्षर ofs,
             u_अक्षर per, u_अक्षर wide, u_अक्षर भाग, u_अक्षर fak)
अणु
	काष्ठा sym_tcb *tp = &np->target[target];
	काष्ठा scsi_target *starget = tp->starget;

	sym_settrans(np, target, opts, ofs, per, wide, भाग, fak);

	अगर (wide || ofs)
		tp->tgoal.renego = NS_PPR;
	अन्यथा
		tp->tgoal.renego = 0;
	spi_width(starget) = tp->tgoal.width = wide;
	spi_period(starget) = tp->tgoal.period = per;
	spi_offset(starget) = tp->tgoal.offset = ofs;
	spi_iu(starget) = tp->tgoal.iu = !!(opts & PPR_OPT_IU);
	spi_dt(starget) = tp->tgoal.dt = !!(opts & PPR_OPT_DT);
	spi_qas(starget) = tp->tgoal.qas = !!(opts & PPR_OPT_QAS);
	tp->tgoal.check_nego = 0;

	sym_announce_transfer_rate(tp);
पूर्ण

/*
 *  generic recovery from scsi पूर्णांकerrupt
 *
 *  The करोc says that when the chip माला_लो an SCSI पूर्णांकerrupt,
 *  it tries to stop in an orderly fashion, by completing 
 *  an inकाष्ठाion fetch that had started or by flushing 
 *  the DMA fअगरo क्रम a ग_लिखो to memory that was executing.
 *  Such a fashion is not enough to know अगर the inकाष्ठाion 
 *  that was just beक्रमe the current DSP value has been 
 *  executed or not.
 *
 *  There are some small SCRIPTS sections that deal with 
 *  the start queue and the करोne queue that may अवरोध any 
 *  assomption from the C code अगर we are पूर्णांकerrupted 
 *  inside, so we reset अगर this happens. Btw, since these 
 *  SCRIPTS sections are executed जबतक the SCRIPTS hasn't 
 *  started SCSI operations, it is very unlikely to happen.
 *
 *  All the driver data काष्ठाures are supposed to be 
 *  allocated from the same 4 GB memory winकरोw, so there 
 *  is a 1 to 1 relationship between DSA and driver data 
 *  काष्ठाures. Since we are careful :) to invalidate the 
 *  DSA when we complete a command or when the SCRIPTS 
 *  pushes a DSA पूर्णांकo a queue, we can trust it when it 
 *  poपूर्णांकs to a CCB.
 */
अटल व्योम sym_recover_scsi_पूर्णांक (काष्ठा sym_hcb *np, u_अक्षर hsts)
अणु
	u32	dsp	= INL(np, nc_dsp);
	u32	dsa	= INL(np, nc_dsa);
	काष्ठा sym_ccb *cp	= sym_ccb_from_dsa(np, dsa);

	/*
	 *  If we haven't been पूर्णांकerrupted inside the SCRIPTS 
	 *  critical pathes, we can safely restart the SCRIPTS 
	 *  and trust the DSA value अगर it matches a CCB.
	 */
	अगर ((!(dsp > SCRIPTA_BA(np, getjob_begin) &&
	       dsp < SCRIPTA_BA(np, getjob_end) + 1)) &&
	    (!(dsp > SCRIPTA_BA(np, ungetjob) &&
	       dsp < SCRIPTA_BA(np, reselect) + 1)) &&
	    (!(dsp > SCRIPTB_BA(np, sel_क्रम_पात) &&
	       dsp < SCRIPTB_BA(np, sel_क्रम_पात_1) + 1)) &&
	    (!(dsp > SCRIPTA_BA(np, करोne) &&
	       dsp < SCRIPTA_BA(np, करोne_end) + 1))) अणु
		OUTB(np, nc_ctest3, np->rv_ctest3 | CLF); /* clear dma fअगरo  */
		OUTB(np, nc_stest3, TE|CSF);		/* clear scsi fअगरo */
		/*
		 *  If we have a CCB, let the SCRIPTS call us back क्रम 
		 *  the handling of the error with SCRATCHA filled with 
		 *  STARTPOS. This way, we will be able to मुक्तze the 
		 *  device queue and requeue aरुकोing IOs.
		 */
		अगर (cp) अणु
			cp->host_status = hsts;
			OUTL_DSP(np, SCRIPTA_BA(np, complete_error));
		पूर्ण
		/*
		 *  Otherwise just restart the SCRIPTS.
		 */
		अन्यथा अणु
			OUTL(np, nc_dsa, 0xffffff);
			OUTL_DSP(np, SCRIPTA_BA(np, start));
		पूर्ण
	पूर्ण
	अन्यथा
		जाओ reset_all;

	वापस;

reset_all:
	sym_start_reset(np);
पूर्ण

/*
 *  chip exception handler क्रम selection समयout
 */
अटल व्योम sym_पूर्णांक_sto (काष्ठा sym_hcb *np)
अणु
	u32 dsp	= INL(np, nc_dsp);

	अगर (DEBUG_FLAGS & DEBUG_TINY) म_लिखो ("T");

	अगर (dsp == SCRIPTA_BA(np, wf_sel_करोne) + 8)
		sym_recover_scsi_पूर्णांक(np, HS_SEL_TIMEOUT);
	अन्यथा
		sym_start_reset(np);
पूर्ण

/*
 *  chip exception handler क्रम unexpected disconnect
 */
अटल व्योम sym_पूर्णांक_udc (काष्ठा sym_hcb *np)
अणु
	म_लिखो ("%s: unexpected disconnect\n", sym_name(np));
	sym_recover_scsi_पूर्णांक(np, HS_UNEXPECTED);
पूर्ण

/*
 *  chip exception handler क्रम SCSI bus mode change
 *
 *  spi2-r12 11.2.3 says a transceiver mode change must 
 *  generate a reset event and a device that detects a reset 
 *  event shall initiate a hard reset. It says also that a
 *  device that detects a mode change shall set data transfer 
 *  mode to eight bit asynchronous, etc...
 *  So, just reinitializing all except chip should be enough.
 */
अटल व्योम sym_पूर्णांक_sbmc(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	u_अक्षर scsi_mode = INB(np, nc_stest4) & SMODE;

	/*
	 *  Notअगरy user.
	 */
	म_लिखो("%s: SCSI BUS mode change from %s to %s.\n", sym_name(np),
		sym_scsi_bus_mode(np->scsi_mode), sym_scsi_bus_mode(scsi_mode));

	/*
	 *  Should suspend command processing क्रम a few seconds and 
	 *  reinitialize all except the chip.
	 */
	sym_start_up(shost, 2);
पूर्ण

/*
 *  chip exception handler क्रम SCSI parity error.
 *
 *  When the chip detects a SCSI parity error and is 
 *  currently executing a (CH)MOV inकाष्ठाion, it करोes 
 *  not पूर्णांकerrupt immediately, but tries to finish the 
 *  transfer of the current scatter entry beक्रमe 
 *  पूर्णांकerrupting. The following situations may occur:
 *
 *  - The complete scatter entry has been transferred 
 *    without the device having changed phase.
 *    The chip will then पूर्णांकerrupt with the DSP poपूर्णांकing 
 *    to the inकाष्ठाion that follows the MOV.
 *
 *  - A phase mismatch occurs beक्रमe the MOV finished 
 *    and phase errors are to be handled by the C code.
 *    The chip will then पूर्णांकerrupt with both PAR and MA 
 *    conditions set.
 *
 *  - A phase mismatch occurs beक्रमe the MOV finished and 
 *    phase errors are to be handled by SCRIPTS.
 *    The chip will load the DSP with the phase mismatch 
 *    JUMP address and पूर्णांकerrupt the host processor.
 */
अटल व्योम sym_पूर्णांक_par (काष्ठा sym_hcb *np, u_लघु sist)
अणु
	u_अक्षर	hsts	= INB(np, HS_PRT);
	u32	dsp	= INL(np, nc_dsp);
	u32	dbc	= INL(np, nc_dbc);
	u32	dsa	= INL(np, nc_dsa);
	u_अक्षर	sbcl	= INB(np, nc_sbcl);
	u_अक्षर	cmd	= dbc >> 24;
	पूर्णांक phase	= cmd & 7;
	काष्ठा sym_ccb *cp	= sym_ccb_from_dsa(np, dsa);

	अगर (prपूर्णांकk_ratelimit())
		म_लिखो("%s: SCSI parity error detected: SCR1=%d DBC=%x SBCL=%x\n",
			sym_name(np), hsts, dbc, sbcl);

	/*
	 *  Check that the chip is connected to the SCSI BUS.
	 */
	अगर (!(INB(np, nc_scntl1) & ISCON)) अणु
		sym_recover_scsi_पूर्णांक(np, HS_UNEXPECTED);
		वापस;
	पूर्ण

	/*
	 *  If the nexus is not clearly identअगरied, reset the bus.
	 *  We will try to करो better later.
	 */
	अगर (!cp)
		जाओ reset_all;

	/*
	 *  Check inकाष्ठाion was a MOV, direction was INPUT and 
	 *  ATN is निश्चितed.
	 */
	अगर ((cmd & 0xc0) || !(phase & 1) || !(sbcl & 0x8))
		जाओ reset_all;

	/*
	 *  Keep track of the parity error.
	 */
	OUTONB(np, HF_PRT, HF_EXT_ERR);
	cp->xerr_status |= XE_PARITY_ERR;

	/*
	 *  Prepare the message to send to the device.
	 */
	np->msgout[0] = (phase == 7) ? M_PARITY : M_ID_ERROR;

	/*
	 *  If the old phase was DATA IN phase, we have to deal with
	 *  the 3 situations described above.
	 *  For other input phases (MSG IN and STATUS), the device 
	 *  must resend the whole thing that failed parity checking 
	 *  or संकेत error. So, jumping to dispatcher should be OK.
	 */
	अगर (phase == 1 || phase == 5) अणु
		/* Phase mismatch handled by SCRIPTS */
		अगर (dsp == SCRIPTB_BA(np, pm_handle))
			OUTL_DSP(np, dsp);
		/* Phase mismatch handled by the C code */
		अन्यथा अगर (sist & MA)
			sym_पूर्णांक_ma (np);
		/* No phase mismatch occurred */
		अन्यथा अणु
			sym_set_script_dp (np, cp, dsp);
			OUTL_DSP(np, SCRIPTA_BA(np, dispatch));
		पूर्ण
	पूर्ण
	अन्यथा अगर (phase == 7)	/* We definitely cannot handle parity errors */
#अगर 1				/* in message-in phase due to the relection  */
		जाओ reset_all; /* path and various message anticipations.   */
#अन्यथा
		OUTL_DSP(np, SCRIPTA_BA(np, clrack));
#पूर्ण_अगर
	अन्यथा
		OUTL_DSP(np, SCRIPTA_BA(np, dispatch));
	वापस;

reset_all:
	sym_start_reset(np);
	वापस;
पूर्ण

/*
 *  chip exception handler क्रम phase errors.
 *
 *  We have to स्थिरruct a new transfer descriptor,
 *  to transfer the rest of the current block.
 */
अटल व्योम sym_पूर्णांक_ma (काष्ठा sym_hcb *np)
अणु
	u32	dbc;
	u32	rest;
	u32	dsp;
	u32	dsa;
	u32	nxtdsp;
	u32	*vdsp;
	u32	oadr, olen;
	u32	*tblp;
        u32	newcmd;
	u_पूर्णांक	delta;
	u_अक्षर	cmd;
	u_अक्षर	hflags, hflags0;
	काष्ठा	sym_pmc *pm;
	काष्ठा sym_ccb *cp;

	dsp	= INL(np, nc_dsp);
	dbc	= INL(np, nc_dbc);
	dsa	= INL(np, nc_dsa);

	cmd	= dbc >> 24;
	rest	= dbc & 0xffffff;
	delta	= 0;

	/*
	 *  locate matching cp अगर any.
	 */
	cp = sym_ccb_from_dsa(np, dsa);

	/*
	 *  Donnot take पूर्णांकo account dma fअगरo and various buffers in 
	 *  INPUT phase since the chip flushes everything beक्रमe 
	 *  raising the MA पूर्णांकerrupt क्रम पूर्णांकerrupted INPUT phases.
	 *  For DATA IN phase, we will check क्रम the SWIDE later.
	 */
	अगर ((cmd & 7) != 1 && (cmd & 7) != 5) अणु
		u_अक्षर ss0, ss2;

		अगर (np->features & FE_DFBC)
			delta = INW(np, nc_dfbc);
		अन्यथा अणु
			u32 dfअगरo;

			/*
			 * Read DFIFO, CTEST[4-6] using 1 PCI bus ownership.
			 */
			dfअगरo = INL(np, nc_dfअगरo);

			/*
			 *  Calculate reमुख्यing bytes in DMA fअगरo.
			 *  (CTEST5 = dfअगरo >> 16)
			 */
			अगर (dfअगरo & (DFS << 16))
				delta = ((((dfअगरo >> 8) & 0x300) |
				          (dfअगरo & 0xff)) - rest) & 0x3ff;
			अन्यथा
				delta = ((dfअगरo & 0xff) - rest) & 0x7f;
		पूर्ण

		/*
		 *  The data in the dma fअगरo has not been transferred to
		 *  the target -> add the amount to the rest
		 *  and clear the data.
		 *  Check the sstat2 रेजिस्टर in हाल of wide transfer.
		 */
		rest += delta;
		ss0  = INB(np, nc_sstat0);
		अगर (ss0 & OLF) rest++;
		अगर (!(np->features & FE_C10))
			अगर (ss0 & ORF) rest++;
		अगर (cp && (cp->phys.select.sel_scntl3 & EWS)) अणु
			ss2 = INB(np, nc_sstat2);
			अगर (ss2 & OLF1) rest++;
			अगर (!(np->features & FE_C10))
				अगर (ss2 & ORF1) rest++;
		पूर्ण

		/*
		 *  Clear fअगरos.
		 */
		OUTB(np, nc_ctest3, np->rv_ctest3 | CLF);	/* dma fअगरo  */
		OUTB(np, nc_stest3, TE|CSF);		/* scsi fअगरo */
	पूर्ण

	/*
	 *  log the inक्रमmation
	 */
	अगर (DEBUG_FLAGS & (DEBUG_TINY|DEBUG_PHASE))
		म_लिखो ("P%x%x RL=%d D=%d ", cmd&7, INB(np, nc_sbcl)&7,
			(अचिन्हित) rest, (अचिन्हित) delta);

	/*
	 *  try to find the पूर्णांकerrupted script command,
	 *  and the address at which to जारी.
	 */
	vdsp	= शून्य;
	nxtdsp	= 0;
	अगर	(dsp >  np->scripta_ba &&
		 dsp <= np->scripta_ba + np->scripta_sz) अणु
		vdsp = (u32 *)((अक्षर*)np->scripta0 + (dsp-np->scripta_ba-8));
		nxtdsp = dsp;
	पूर्ण
	अन्यथा अगर	(dsp >  np->scriptb_ba &&
		 dsp <= np->scriptb_ba + np->scriptb_sz) अणु
		vdsp = (u32 *)((अक्षर*)np->scriptb0 + (dsp-np->scriptb_ba-8));
		nxtdsp = dsp;
	पूर्ण

	/*
	 *  log the inक्रमmation
	 */
	अगर (DEBUG_FLAGS & DEBUG_PHASE) अणु
		म_लिखो ("\nCP=%p DSP=%x NXT=%x VDSP=%p CMD=%x ",
			cp, (अचिन्हित)dsp, (अचिन्हित)nxtdsp, vdsp, cmd);
	पूर्ण

	अगर (!vdsp) अणु
		म_लिखो ("%s: interrupted SCRIPT address not found.\n", 
			sym_name (np));
		जाओ reset_all;
	पूर्ण

	अगर (!cp) अणु
		म_लिखो ("%s: SCSI phase error fixup: CCB already dequeued.\n", 
			sym_name (np));
		जाओ reset_all;
	पूर्ण

	/*
	 *  get old startaddress and old length.
	 */
	oadr = scr_to_cpu(vdsp[1]);

	अगर (cmd & 0x10) अणु	/* Table indirect */
		tblp = (u32 *) ((अक्षर*) &cp->phys + oadr);
		olen = scr_to_cpu(tblp[0]);
		oadr = scr_to_cpu(tblp[1]);
	पूर्ण अन्यथा अणु
		tblp = (u32 *) 0;
		olen = scr_to_cpu(vdsp[0]) & 0xffffff;
	पूर्ण

	अगर (DEBUG_FLAGS & DEBUG_PHASE) अणु
		म_लिखो ("OCMD=%x\nTBLP=%p OLEN=%x OADR=%x\n",
			(अचिन्हित) (scr_to_cpu(vdsp[0]) >> 24),
			tblp,
			(अचिन्हित) olen,
			(अचिन्हित) oadr);
	पूर्ण

	/*
	 *  check cmd against assumed पूर्णांकerrupted script command.
	 *  If dt data phase, the MOVE inकाष्ठाion hasn't bit 4 of 
	 *  the phase.
	 */
	अगर (((cmd & 2) ? cmd : (cmd & ~4)) != (scr_to_cpu(vdsp[0]) >> 24)) अणु
		sym_prपूर्णांक_addr(cp->cmd,
			"internal error: cmd=%02x != %02x=(vdsp[0] >> 24)\n",
			cmd, scr_to_cpu(vdsp[0]) >> 24);

		जाओ reset_all;
	पूर्ण

	/*
	 *  अगर old phase not dataphase, leave here.
	 */
	अगर (cmd & 2) अणु
		sym_prपूर्णांक_addr(cp->cmd,
			"phase change %x-%x %d@%08x resid=%d.\n",
			cmd&7, INB(np, nc_sbcl)&7, (अचिन्हित)olen,
			(अचिन्हित)oadr, (अचिन्हित)rest);
		जाओ unexpected_phase;
	पूर्ण

	/*
	 *  Choose the correct PM save area.
	 *
	 *  Look at the PM_SAVE SCRIPT अगर you want to understand 
	 *  this stuff. The equivalent code is implemented in 
	 *  SCRIPTS क्रम the 895A, 896 and 1010 that are able to 
	 *  handle PM from the SCRIPTS processor.
	 */
	hflags0 = INB(np, HF_PRT);
	hflags = hflags0;

	अगर (hflags & (HF_IN_PM0 | HF_IN_PM1 | HF_DP_SAVED)) अणु
		अगर (hflags & HF_IN_PM0)
			nxtdsp = scr_to_cpu(cp->phys.pm0.ret);
		अन्यथा अगर	(hflags & HF_IN_PM1)
			nxtdsp = scr_to_cpu(cp->phys.pm1.ret);

		अगर (hflags & HF_DP_SAVED)
			hflags ^= HF_ACT_PM;
	पूर्ण

	अगर (!(hflags & HF_ACT_PM)) अणु
		pm = &cp->phys.pm0;
		newcmd = SCRIPTA_BA(np, pm0_data);
	पूर्ण
	अन्यथा अणु
		pm = &cp->phys.pm1;
		newcmd = SCRIPTA_BA(np, pm1_data);
	पूर्ण

	hflags &= ~(HF_IN_PM0 | HF_IN_PM1 | HF_DP_SAVED);
	अगर (hflags != hflags0)
		OUTB(np, HF_PRT, hflags);

	/*
	 *  fillin the phase mismatch context
	 */
	pm->sg.addr = cpu_to_scr(oadr + olen - rest);
	pm->sg.size = cpu_to_scr(rest);
	pm->ret     = cpu_to_scr(nxtdsp);

	/*
	 *  If we have a SWIDE,
	 *  - prepare the address to ग_लिखो the SWIDE from SCRIPTS,
	 *  - compute the SCRIPTS address to restart from,
	 *  - move current data poपूर्णांकer context by one byte.
	 */
	nxtdsp = SCRIPTA_BA(np, dispatch);
	अगर ((cmd & 7) == 1 && cp && (cp->phys.select.sel_scntl3 & EWS) &&
	    (INB(np, nc_scntl2) & WSR)) अणु
		u32 पंचांगp;

		/*
		 *  Set up the table indirect क्रम the MOVE
		 *  of the residual byte and adjust the data 
		 *  poपूर्णांकer context.
		 */
		पंचांगp = scr_to_cpu(pm->sg.addr);
		cp->phys.wresid.addr = cpu_to_scr(पंचांगp);
		pm->sg.addr = cpu_to_scr(पंचांगp + 1);
		पंचांगp = scr_to_cpu(pm->sg.size);
		cp->phys.wresid.size = cpu_to_scr((पंचांगp&0xff000000) | 1);
		pm->sg.size = cpu_to_scr(पंचांगp - 1);

		/*
		 *  If only the residual byte is to be moved, 
		 *  no PM context is needed.
		 */
		अगर ((पंचांगp&0xffffff) == 1)
			newcmd = pm->ret;

		/*
		 *  Prepare the address of SCRIPTS that will 
		 *  move the residual byte to memory.
		 */
		nxtdsp = SCRIPTB_BA(np, wsr_ma_helper);
	पूर्ण

	अगर (DEBUG_FLAGS & DEBUG_PHASE) अणु
		sym_prपूर्णांक_addr(cp->cmd, "PM %x %x %x / %x %x %x.\n",
			hflags0, hflags, newcmd,
			(अचिन्हित)scr_to_cpu(pm->sg.addr),
			(अचिन्हित)scr_to_cpu(pm->sg.size),
			(अचिन्हित)scr_to_cpu(pm->ret));
	पूर्ण

	/*
	 *  Restart the SCRIPTS processor.
	 */
	sym_set_script_dp (np, cp, newcmd);
	OUTL_DSP(np, nxtdsp);
	वापस;

	/*
	 *  Unexpected phase changes that occurs when the current phase 
	 *  is not a DATA IN or DATA OUT phase are due to error conditions.
	 *  Such event may only happen when the SCRIPTS is using a 
	 *  multibyte SCSI MOVE.
	 *
	 *  Phase change		Some possible cause
	 *
	 *  COMMAND  --> MSG IN	SCSI parity error detected by target.
	 *  COMMAND  --> STATUS	Bad command or refused by target.
	 *  MSG OUT  --> MSG IN     Message rejected by target.
	 *  MSG OUT  --> COMMAND    Bogus target that discards extended
	 *  			negotiation messages.
	 *
	 *  The code below करोes not care of the new phase and so 
	 *  trusts the target. Why to annoy it ?
	 *  If the पूर्णांकerrupted phase is COMMAND phase, we restart at
	 *  dispatcher.
	 *  If a target करोes not get all the messages after selection, 
	 *  the code assumes blindly that the target discards extended 
	 *  messages and clears the negotiation status.
	 *  If the target करोes not want all our response to negotiation,
	 *  we क्रमce a SIR_NEGO_PROTO पूर्णांकerrupt (it is a hack that aव्योमs 
	 *  bloat क्रम such a should_not_happen situation).
	 *  In all other situation, we reset the BUS.
	 *  Are these assumptions reasonable ? (Wait and see ...)
	 */
unexpected_phase:
	dsp -= 8;
	nxtdsp = 0;

	चयन (cmd & 7) अणु
	हाल 2:	/* COMMAND phase */
		nxtdsp = SCRIPTA_BA(np, dispatch);
		अवरोध;
#अगर 0
	हाल 3:	/* STATUS  phase */
		nxtdsp = SCRIPTA_BA(np, dispatch);
		अवरोध;
#पूर्ण_अगर
	हाल 6:	/* MSG OUT phase */
		/*
		 *  If the device may want to use untagged when we want 
		 *  tagged, we prepare an IDENTIFY without disc. granted, 
		 *  since we will not be able to handle reselect.
		 *  Otherwise, we just करोn't care.
		 */
		अगर	(dsp == SCRIPTA_BA(np, send_ident)) अणु
			अगर (cp->tag != NO_TAG && olen - rest <= 3) अणु
				cp->host_status = HS_BUSY;
				np->msgout[0] = IDENTIFY(0, cp->lun);
				nxtdsp = SCRIPTB_BA(np, ident_अवरोध_atn);
			पूर्ण
			अन्यथा
				nxtdsp = SCRIPTB_BA(np, ident_अवरोध);
		पूर्ण
		अन्यथा अगर	(dsp == SCRIPTB_BA(np, send_wdtr) ||
			 dsp == SCRIPTB_BA(np, send_sdtr) ||
			 dsp == SCRIPTB_BA(np, send_ppr)) अणु
			nxtdsp = SCRIPTB_BA(np, nego_bad_phase);
			अगर (dsp == SCRIPTB_BA(np, send_ppr)) अणु
				काष्ठा scsi_device *dev = cp->cmd->device;
				dev->ppr = 0;
			पूर्ण
		पूर्ण
		अवरोध;
#अगर 0
	हाल 7:	/* MSG IN  phase */
		nxtdsp = SCRIPTA_BA(np, clrack);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	अगर (nxtdsp) अणु
		OUTL_DSP(np, nxtdsp);
		वापस;
	पूर्ण

reset_all:
	sym_start_reset(np);
पूर्ण

/*
 *  chip पूर्णांकerrupt handler
 *
 *  In normal situations, पूर्णांकerrupt conditions occur one at 
 *  a समय. But when something bad happens on the SCSI BUS, 
 *  the chip may उठाओ several पूर्णांकerrupt flags beक्रमe 
 *  stopping and पूर्णांकerrupting the CPU. The additionnal 
 *  पूर्णांकerrupt flags are stacked in some extra रेजिस्टरs 
 *  after the SIP and/or DIP flag has been उठाओd in the 
 *  ISTAT. After the CPU has पढ़ो the पूर्णांकerrupt condition 
 *  flag from SIST or DSTAT, the chip unstacks the other 
 *  पूर्णांकerrupt flags and sets the corresponding bits in 
 *  SIST or DSTAT. Since the chip starts stacking once the 
 *  SIP or DIP flag is set, there is a small winकरोw of समय 
 *  where the stacking करोes not occur.
 *
 *  Typically, multiple पूर्णांकerrupt conditions may happen in 
 *  the following situations:
 *
 *  - SCSI parity error + Phase mismatch  (PAR|MA)
 *    When an parity error is detected in input phase 
 *    and the device चयनes to msg-in phase inside a 
 *    block MOV.
 *  - SCSI parity error + Unexpected disconnect (PAR|UDC)
 *    When a stupid device करोes not want to handle the 
 *    recovery of an SCSI parity error.
 *  - Some combinations of STO, PAR, UDC, ...
 *    When using non compliant SCSI stuff, when user is 
 *    करोing non compliant hot tampering on the BUS, when 
 *    something really bad happens to a device, etc ...
 *
 *  The heuristic suggested by SYMBIOS to handle 
 *  multiple पूर्णांकerrupts is to try unstacking all 
 *  पूर्णांकerrupts conditions and to handle them on some 
 *  priority based on error severity.
 *  This will work when the unstacking has been 
 *  successful, but we cannot be 100 % sure of that, 
 *  since the CPU may have been faster to unstack than 
 *  the chip is able to stack. Hmmm ... But it seems that 
 *  such a situation is very unlikely to happen.
 *
 *  If this happen, क्रम example STO caught by the CPU 
 *  then UDC happenning beक्रमe the CPU have restarted 
 *  the SCRIPTS, the driver may wrongly complete the 
 *  same command on UDC, since the SCRIPTS didn't restart 
 *  and the DSA still poपूर्णांकs to the same command.
 *  We aव्योम this situation by setting the DSA to an 
 *  invalid value when the CCB is completed and beक्रमe 
 *  restarting the SCRIPTS.
 *
 *  Another issue is that we need some section of our 
 *  recovery procedures to be somehow unपूर्णांकerruptible but 
 *  the SCRIPTS processor करोes not provides such a 
 *  feature. For this reason, we handle recovery preferently 
 *  from the C code and check against some SCRIPTS critical 
 *  sections from the C code.
 *
 *  Hopefully, the पूर्णांकerrupt handling of the driver is now 
 *  able to resist to weird BUS error conditions, but करोnnot 
 *  ask me क्रम any guarantee that it will never fail. :-)
 *  Use at your own decision and risk.
 */

irqवापस_t sym_पूर्णांकerrupt(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा sym_data *sym_data = shost_priv(shost);
	काष्ठा sym_hcb *np = sym_data->ncb;
	काष्ठा pci_dev *pdev = sym_data->pdev;
	u_अक्षर	istat, istatc;
	u_अक्षर	dstat;
	u_लघु	sist;

	/*
	 *  पूर्णांकerrupt on the fly ?
	 *  (SCRIPTS may still be running)
	 *
	 *  A `dummy पढ़ो' is needed to ensure that the 
	 *  clear of the INTF flag reaches the device 
	 *  and that posted ग_लिखोs are flushed to memory
	 *  beक्रमe the scanning of the DONE queue.
	 *  Note that SCRIPTS also (dummy) पढ़ो to memory 
	 *  prior to deliver the INTF पूर्णांकerrupt condition.
	 */
	istat = INB(np, nc_istat);
	अगर (istat & INTF) अणु
		OUTB(np, nc_istat, (istat & SIGP) | INTF | np->istat_sem);
		istat |= INB(np, nc_istat);		/* DUMMY READ */
		अगर (DEBUG_FLAGS & DEBUG_TINY) म_लिखो ("F ");
		sym_wakeup_करोne(np);
	पूर्ण

	अगर (!(istat & (SIP|DIP)))
		वापस (istat & INTF) ? IRQ_HANDLED : IRQ_NONE;

#अगर 0	/* We should never get this one */
	अगर (istat & CABRT)
		OUTB(np, nc_istat, CABRT);
#पूर्ण_अगर

	/*
	 *  PAR and MA पूर्णांकerrupts may occur at the same समय,
	 *  and we need to know of both in order to handle 
	 *  this situation properly. We try to unstack SCSI 
	 *  पूर्णांकerrupts क्रम that reason. BTW, I dislike a LOT 
	 *  such a loop inside the पूर्णांकerrupt routine.
	 *  Even अगर DMA पूर्णांकerrupt stacking is very unlikely to 
	 *  happen, we also try unstacking these ones, since 
	 *  this has no perक्रमmance impact.
	 */
	sist	= 0;
	dstat	= 0;
	istatc	= istat;
	करो अणु
		अगर (istatc & SIP)
			sist  |= INW(np, nc_sist);
		अगर (istatc & DIP)
			dstat |= INB(np, nc_dstat);
		istatc = INB(np, nc_istat);
		istat |= istatc;

		/* Prevent deadlock रुकोing on a condition that may
		 * never clear. */
		अगर (unlikely(sist == 0xffff && dstat == 0xff)) अणु
			अगर (pci_channel_offline(pdev))
				वापस IRQ_NONE;
		पूर्ण
	पूर्ण जबतक (istatc & (SIP|DIP));

	अगर (DEBUG_FLAGS & DEBUG_TINY)
		म_लिखो ("<%d|%x:%x|%x:%x>",
			(पूर्णांक)INB(np, nc_scr0),
			dstat,sist,
			(अचिन्हित)INL(np, nc_dsp),
			(अचिन्हित)INL(np, nc_dbc));
	/*
	 *  On paper, a memory पढ़ो barrier may be needed here to 
	 *  prevent out of order LOADs by the CPU from having 
	 *  prefetched stale data prior to DMA having occurred.
	 *  And since we are paranoid ... :)
	 */
	MEMORY_READ_BARRIER();

	/*
	 *  First, पूर्णांकerrupts we want to service cleanly.
	 *
	 *  Phase mismatch (MA) is the most frequent पूर्णांकerrupt 
	 *  क्रम chip earlier than the 896 and so we have to service 
	 *  it as quickly as possible.
	 *  A SCSI parity error (PAR) may be combined with a phase 
	 *  mismatch condition (MA).
	 *  Programmed पूर्णांकerrupts (SIR) are used to call the C code 
	 *  from SCRIPTS.
	 *  The single step पूर्णांकerrupt (SSI) is not used in this 
	 *  driver.
	 */
	अगर (!(sist  & (STO|GEN|HTH|SGE|UDC|SBMC|RST)) &&
	    !(dstat & (MDPE|BF|ABRT|IID))) अणु
		अगर	(sist & PAR)	sym_पूर्णांक_par (np, sist);
		अन्यथा अगर (sist & MA)	sym_पूर्णांक_ma (np);
		अन्यथा अगर (dstat & SIR)	sym_पूर्णांक_sir(np);
		अन्यथा अगर (dstat & SSI)	OUTONB_STD();
		अन्यथा			जाओ unknown_पूर्णांक;
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 *  Now, पूर्णांकerrupts that करोnnot happen in normal 
	 *  situations and that we may need to recover from.
	 *
	 *  On SCSI RESET (RST), we reset everything.
	 *  On SCSI BUS MODE CHANGE (SBMC), we complete all 
	 *  active CCBs with RESET status, prepare all devices 
	 *  क्रम negotiating again and restart the SCRIPTS.
	 *  On STO and UDC, we complete the CCB with the corres- 
	 *  ponding status and restart the SCRIPTS.
	 */
	अगर (sist & RST) अणु
		म_लिखो("%s: SCSI BUS reset detected.\n", sym_name(np));
		sym_start_up(shost, 1);
		वापस IRQ_HANDLED;
	पूर्ण

	OUTB(np, nc_ctest3, np->rv_ctest3 | CLF);	/* clear dma fअगरo  */
	OUTB(np, nc_stest3, TE|CSF);		/* clear scsi fअगरo */

	अगर (!(sist  & (GEN|HTH|SGE)) &&
	    !(dstat & (MDPE|BF|ABRT|IID))) अणु
		अगर	(sist & SBMC)	sym_पूर्णांक_sbmc(shost);
		अन्यथा अगर (sist & STO)	sym_पूर्णांक_sto (np);
		अन्यथा अगर (sist & UDC)	sym_पूर्णांक_udc (np);
		अन्यथा			जाओ unknown_पूर्णांक;
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 *  Now, पूर्णांकerrupts we are not able to recover cleanly.
	 *
	 *  Log message क्रम hard errors.
	 *  Reset everything.
	 */

	sym_log_hard_error(shost, sist, dstat);

	अगर ((sist & (GEN|HTH|SGE)) ||
		(dstat & (MDPE|BF|ABRT|IID))) अणु
		sym_start_reset(np);
		वापस IRQ_HANDLED;
	पूर्ण

unknown_पूर्णांक:
	/*
	 *  We just miss the cause of the पूर्णांकerrupt. :(
	 *  Prपूर्णांक a message. The समयout will करो the real work.
	 */
	म_लिखो(	"%s: unknown interrupt(s) ignored, "
		"ISTAT=0x%x DSTAT=0x%x SIST=0x%x\n",
		sym_name(np), istat, dstat, sist);
	वापस IRQ_NONE;
पूर्ण

/*
 *  Dequeue from the START queue all CCBs that match 
 *  a given target/lun/task condition (-1 means all),
 *  and move them from the BUSY queue to the COMP queue 
 *  with DID_SOFT_ERROR status condition.
 *  This function is used during error handling/recovery.
 *  It is called with SCRIPTS not running.
 */
अटल पूर्णांक 
sym_dequeue_from_squeue(काष्ठा sym_hcb *np, पूर्णांक i, पूर्णांक target, पूर्णांक lun, पूर्णांक task)
अणु
	पूर्णांक j;
	काष्ठा sym_ccb *cp;

	/*
	 *  Make sure the starting index is within range.
	 */
	निश्चित((i >= 0) && (i < 2*MAX_QUEUE));

	/*
	 *  Walk until end of START queue and dequeue every job 
	 *  that matches the target/lun/task condition.
	 */
	j = i;
	जबतक (i != np->squeueput) अणु
		cp = sym_ccb_from_dsa(np, scr_to_cpu(np->squeue[i]));
		निश्चित(cp);
#अगर_घोषित SYM_CONF_IARB_SUPPORT
		/* Forget hपूर्णांकs क्रम IARB, they may be no दीर्घer relevant */
		cp->host_flags &= ~HF_HINT_IARB;
#पूर्ण_अगर
		अगर ((target == -1 || cp->target == target) &&
		    (lun    == -1 || cp->lun    == lun)    &&
		    (task   == -1 || cp->tag    == task)) अणु
#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
			sym_set_cam_status(cp->cmd, DID_SOFT_ERROR);
#अन्यथा
			sym_set_cam_status(cp->cmd, DID_REQUEUE);
#पूर्ण_अगर
			sym_remque(&cp->link_ccbq);
			sym_insque_tail(&cp->link_ccbq, &np->comp_ccbq);
		पूर्ण
		अन्यथा अणु
			अगर (i != j)
				np->squeue[j] = np->squeue[i];
			अगर ((j += 2) >= MAX_QUEUE*2) j = 0;
		पूर्ण
		अगर ((i += 2) >= MAX_QUEUE*2) i = 0;
	पूर्ण
	अगर (i != j)		/* Copy back the idle task अगर needed */
		np->squeue[j] = np->squeue[i];
	np->squeueput = j;	/* Update our current start queue poपूर्णांकer */

	वापस (i - j) / 2;
पूर्ण

/*
 *  chip handler क्रम bad SCSI status condition
 *
 *  In हाल of bad SCSI status, we unqueue all the tasks 
 *  currently queued to the controller but not yet started 
 *  and then restart the SCRIPTS processor immediately.
 *
 *  QUEUE FULL and BUSY conditions are handled the same way.
 *  Basically all the not yet started tasks are requeued in 
 *  device queue and the queue is frozen until a completion.
 *
 *  For CHECK CONDITION and COMMAND TERMINATED status, we use 
 *  the CCB of the failed command to prepare a REQUEST SENSE 
 *  SCSI command and queue it to the controller queue.
 *
 *  SCRATCHA is assumed to have been loaded with STARTPOS 
 *  beक्रमe the SCRIPTS called the C code.
 */
अटल व्योम sym_sir_bad_scsi_status(काष्ठा sym_hcb *np, पूर्णांक num, काष्ठा sym_ccb *cp)
अणु
	u32		startp;
	u_अक्षर		s_status = cp->ssss_status;
	u_अक्षर		h_flags  = cp->host_flags;
	पूर्णांक		msglen;
	पूर्णांक		i;

	/*
	 *  Compute the index of the next job to start from SCRIPTS.
	 */
	i = (INL(np, nc_scratcha) - np->squeue_ba) / 4;

	/*
	 *  The last CCB queued used क्रम IARB hपूर्णांक may be 
	 *  no दीर्घer relevant. Forget it.
	 */
#अगर_घोषित SYM_CONF_IARB_SUPPORT
	अगर (np->last_cp)
		np->last_cp = 0;
#पूर्ण_अगर

	/*
	 *  Now deal with the SCSI status.
	 */
	चयन(s_status) अणु
	हाल S_BUSY:
	हाल S_QUEUE_FULL:
		अगर (sym_verbose >= 2) अणु
			sym_prपूर्णांक_addr(cp->cmd, "%s\n",
			        s_status == S_BUSY ? "BUSY" : "QUEUE FULL\n");
		पूर्ण
		fallthrough;
	शेष:	/* S_INT, S_INT_COND_MET, S_CONFLICT */
		sym_complete_error (np, cp);
		अवरोध;
	हाल S_TERMINATED:
	हाल S_CHECK_COND:
		/*
		 *  If we get an SCSI error when requesting sense, give up.
		 */
		अगर (h_flags & HF_SENSE) अणु
			sym_complete_error (np, cp);
			अवरोध;
		पूर्ण

		/*
		 *  Dequeue all queued CCBs क्रम that device not yet started,
		 *  and restart the SCRIPTS processor immediately.
		 */
		sym_dequeue_from_squeue(np, i, cp->target, cp->lun, -1);
		OUTL_DSP(np, SCRIPTA_BA(np, start));

 		/*
		 *  Save some info of the actual IO.
		 *  Compute the data residual.
		 */
		cp->sv_scsi_status = cp->ssss_status;
		cp->sv_xerr_status = cp->xerr_status;
		cp->sv_resid = sym_compute_residual(np, cp);

		/*
		 *  Prepare all needed data काष्ठाures क्रम 
		 *  requesting sense data.
		 */

		cp->scsi_smsg2[0] = IDENTIFY(0, cp->lun);
		msglen = 1;

		/*
		 *  If we are currently using anything dअगरferent from 
		 *  async. 8 bit data transfers with that target,
		 *  start a negotiation, since the device may want 
		 *  to report us a UNIT ATTENTION condition due to 
		 *  a cause we currently ignore, and we करोnnot want 
		 *  to be stuck with WIDE and/or SYNC data transfer.
		 *
		 *  cp->nego_status is filled by sym_prepare_nego().
		 */
		cp->nego_status = 0;
		msglen += sym_prepare_nego(np, cp, &cp->scsi_smsg2[msglen]);
		/*
		 *  Message table indirect काष्ठाure.
		 */
		cp->phys.smsg.addr	= CCB_BA(cp, scsi_smsg2);
		cp->phys.smsg.size	= cpu_to_scr(msglen);

		/*
		 *  sense command
		 */
		cp->phys.cmd.addr	= CCB_BA(cp, sensecmd);
		cp->phys.cmd.size	= cpu_to_scr(6);

		/*
		 *  patch requested size पूर्णांकo sense command
		 */
		cp->sensecmd[0]		= REQUEST_SENSE;
		cp->sensecmd[1]		= 0;
		अगर (cp->cmd->device->scsi_level <= SCSI_2 && cp->lun <= 7)
			cp->sensecmd[1]	= cp->lun << 5;
		cp->sensecmd[4]		= SYM_SNS_BBUF_LEN;
		cp->data_len		= SYM_SNS_BBUF_LEN;

		/*
		 *  sense data
		 */
		स_रखो(cp->sns_bbuf, 0, SYM_SNS_BBUF_LEN);
		cp->phys.sense.addr	= CCB_BA(cp, sns_bbuf);
		cp->phys.sense.size	= cpu_to_scr(SYM_SNS_BBUF_LEN);

		/*
		 *  requeue the command.
		 */
		startp = SCRIPTB_BA(np, sdata_in);

		cp->phys.head.savep	= cpu_to_scr(startp);
		cp->phys.head.lastp	= cpu_to_scr(startp);
		cp->startp		= cpu_to_scr(startp);
		cp->goalp		= cpu_to_scr(startp + 16);

		cp->host_xflags = 0;
		cp->host_status	= cp->nego_status ? HS_NEGOTIATE : HS_BUSY;
		cp->ssss_status = S_ILLEGAL;
		cp->host_flags	= (HF_SENSE|HF_DATA_IN);
		cp->xerr_status = 0;
		cp->extra_bytes = 0;

		cp->phys.head.go.start = cpu_to_scr(SCRIPTA_BA(np, select));

		/*
		 *  Requeue the command.
		 */
		sym_put_start_queue(np, cp);

		/*
		 *  Give back to upper layer everything we have dequeued.
		 */
		sym_flush_comp_queue(np, 0);
		अवरोध;
	पूर्ण
पूर्ण

/*
 *  After a device has accepted some management message 
 *  as BUS DEVICE RESET, ABORT TASK, etc ..., or when 
 *  a device संकेतs a UNIT ATTENTION condition, some 
 *  tasks are thrown away by the device. We are required 
 *  to reflect that on our tasks list since the device 
 *  will never complete these tasks.
 *
 *  This function move from the BUSY queue to the COMP 
 *  queue all disconnected CCBs क्रम a given target that 
 *  match the following criteria:
 *  - lun=-1  means any logical UNIT otherwise a given one.
 *  - task=-1 means any task, otherwise a given one.
 */
पूर्णांक sym_clear_tasks(काष्ठा sym_hcb *np, पूर्णांक cam_status, पूर्णांक target, पूर्णांक lun, पूर्णांक task)
अणु
	SYM_QUEHEAD qपंचांगp, *qp;
	पूर्णांक i = 0;
	काष्ठा sym_ccb *cp;

	/*
	 *  Move the entire BUSY queue to our temporary queue.
	 */
	sym_que_init(&qपंचांगp);
	sym_que_splice(&np->busy_ccbq, &qपंचांगp);
	sym_que_init(&np->busy_ccbq);

	/*
	 *  Put all CCBs that matches our criteria पूर्णांकo 
	 *  the COMP queue and put back other ones पूर्णांकo 
	 *  the BUSY queue.
	 */
	जबतक ((qp = sym_remque_head(&qपंचांगp)) != शून्य) अणु
		काष्ठा scsi_cmnd *cmd;
		cp = sym_que_entry(qp, काष्ठा sym_ccb, link_ccbq);
		cmd = cp->cmd;
		अगर (cp->host_status != HS_DISCONNECT ||
		    cp->target != target	     ||
		    (lun  != -1 && cp->lun != lun)   ||
		    (task != -1 && 
			(cp->tag != NO_TAG && cp->scsi_smsg[2] != task))) अणु
			sym_insque_tail(&cp->link_ccbq, &np->busy_ccbq);
			जारी;
		पूर्ण
		sym_insque_tail(&cp->link_ccbq, &np->comp_ccbq);

		/* Preserve the software समयout condition */
		अगर (sym_get_cam_status(cmd) != DID_TIME_OUT)
			sym_set_cam_status(cmd, cam_status);
		++i;
#अगर 0
म_लिखो("XXXX TASK @%p CLEARED\n", cp);
#पूर्ण_अगर
	पूर्ण
	वापस i;
पूर्ण

/*
 *  chip handler क्रम TASKS recovery
 *
 *  We cannot safely पात a command, जबतक the SCRIPTS 
 *  processor is running, since we just would be in race 
 *  with it.
 *
 *  As दीर्घ as we have tasks to पात, we keep the SEM 
 *  bit set in the ISTAT. When this bit is set, the 
 *  SCRIPTS processor पूर्णांकerrupts (SIR_SCRIPT_STOPPED) 
 *  each समय it enters the scheduler.
 *
 *  If we have to reset a target, clear tasks of a unit,
 *  or to perक्रमm the पात of a disconnected job, we 
 *  restart the SCRIPTS क्रम selecting the target. Once 
 *  selected, the SCRIPTS पूर्णांकerrupts (SIR_TARGET_SELECTED).
 *  If it loses arbitration, the SCRIPTS will पूर्णांकerrupt again 
 *  the next समय it will enter its scheduler, and so on ...
 *
 *  On SIR_TARGET_SELECTED, we scan क्रम the more 
 *  appropriate thing to करो:
 *
 *  - If nothing, we just sent a M_ABORT message to the 
 *    target to get rid of the useless SCSI bus ownership.
 *    According to the specs, no tasks shall be affected.
 *  - If the target is to be reset, we send it a M_RESET 
 *    message.
 *  - If a logical UNIT is to be cleared , we send the 
 *    IDENTIFY(lun) + M_ABORT.
 *  - If an untagged task is to be पातed, we send the 
 *    IDENTIFY(lun) + M_ABORT.
 *  - If a tagged task is to be पातed, we send the 
 *    IDENTIFY(lun) + task attributes + M_ABORT_TAG.
 *
 *  Once our 'kiss of death' :) message has been accepted 
 *  by the target, the SCRIPTS पूर्णांकerrupts again 
 *  (SIR_ABORT_SENT). On this पूर्णांकerrupt, we complete 
 *  all the CCBs that should have been पातed by the 
 *  target according to our message.
 */
अटल व्योम sym_sir_task_recovery(काष्ठा sym_hcb *np, पूर्णांक num)
अणु
	SYM_QUEHEAD *qp;
	काष्ठा sym_ccb *cp;
	काष्ठा sym_tcb *tp = शून्य; /* gcc isn't quite smart enough yet */
	काष्ठा scsi_target *starget;
	पूर्णांक target=-1, lun=-1, task;
	पूर्णांक i, k;

	चयन(num) अणु
	/*
	 *  The SCRIPTS processor stopped beक्रमe starting
	 *  the next command in order to allow us to perक्रमm 
	 *  some task recovery.
	 */
	हाल SIR_SCRIPT_STOPPED:
		/*
		 *  Do we have any target to reset or unit to clear ?
		 */
		क्रम (i = 0 ; i < SYM_CONF_MAX_TARGET ; i++) अणु
			tp = &np->target[i];
			अगर (tp->to_reset || 
			    (tp->lun0p && tp->lun0p->to_clear)) अणु
				target = i;
				अवरोध;
			पूर्ण
			अगर (!tp->lunmp)
				जारी;
			क्रम (k = 1 ; k < SYM_CONF_MAX_LUN ; k++) अणु
				अगर (tp->lunmp[k] && tp->lunmp[k]->to_clear) अणु
					target	= i;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (target != -1)
				अवरोध;
		पूर्ण

		/*
		 *  If not, walk the busy queue क्रम any 
		 *  disconnected CCB to be पातed.
		 */
		अगर (target == -1) अणु
			FOR_EACH_QUEUED_ELEMENT(&np->busy_ccbq, qp) अणु
				cp = sym_que_entry(qp,काष्ठा sym_ccb,link_ccbq);
				अगर (cp->host_status != HS_DISCONNECT)
					जारी;
				अगर (cp->to_पात) अणु
					target = cp->target;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 *  If some target is to be selected, 
		 *  prepare and start the selection.
		 */
		अगर (target != -1) अणु
			tp = &np->target[target];
			np->abrt_sel.sel_id	= target;
			np->abrt_sel.sel_scntl3 = tp->head.wval;
			np->abrt_sel.sel_sxfer  = tp->head.sval;
			OUTL(np, nc_dsa, np->hcb_ba);
			OUTL_DSP(np, SCRIPTB_BA(np, sel_क्रम_पात));
			वापस;
		पूर्ण

		/*
		 *  Now look क्रम a CCB to पात that haven't started yet.
		 *  Btw, the SCRIPTS processor is still stopped, so 
		 *  we are not in race.
		 */
		i = 0;
		cp = शून्य;
		FOR_EACH_QUEUED_ELEMENT(&np->busy_ccbq, qp) अणु
			cp = sym_que_entry(qp, काष्ठा sym_ccb, link_ccbq);
			अगर (cp->host_status != HS_BUSY &&
			    cp->host_status != HS_NEGOTIATE)
				जारी;
			अगर (!cp->to_पात)
				जारी;
#अगर_घोषित SYM_CONF_IARB_SUPPORT
			/*
			 *    If we are using IMMEDIATE ARBITRATION, we करोnnot 
			 *    want to cancel the last queued CCB, since the 
			 *    SCRIPTS may have anticipated the selection.
			 */
			अगर (cp == np->last_cp) अणु
				cp->to_पात = 0;
				जारी;
			पूर्ण
#पूर्ण_अगर
			i = 1;	/* Means we have found some */
			अवरोध;
		पूर्ण
		अगर (!i) अणु
			/*
			 *  We are करोne, so we करोnnot need 
			 *  to synchronize with the SCRIPTS anyदीर्घer.
			 *  Remove the SEM flag from the ISTAT.
			 */
			np->istat_sem = 0;
			OUTB(np, nc_istat, SIGP);
			अवरोध;
		पूर्ण
		/*
		 *  Compute index of next position in the start 
		 *  queue the SCRIPTS पूर्णांकends to start and dequeue 
		 *  all CCBs क्रम that device that haven't been started.
		 */
		i = (INL(np, nc_scratcha) - np->squeue_ba) / 4;
		i = sym_dequeue_from_squeue(np, i, cp->target, cp->lun, -1);

		/*
		 *  Make sure at least our IO to पात has been dequeued.
		 */
#अगर_अघोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
		निश्चित(i && sym_get_cam_status(cp->cmd) == DID_SOFT_ERROR);
#अन्यथा
		sym_remque(&cp->link_ccbq);
		sym_insque_tail(&cp->link_ccbq, &np->comp_ccbq);
#पूर्ण_अगर
		/*
		 *  Keep track in cam status of the reason of the पात.
		 */
		अगर (cp->to_पात == 2)
			sym_set_cam_status(cp->cmd, DID_TIME_OUT);
		अन्यथा
			sym_set_cam_status(cp->cmd, DID_ABORT);

		/*
		 *  Complete with error everything that we have dequeued.
	 	 */
		sym_flush_comp_queue(np, 0);
		अवरोध;
	/*
	 *  The SCRIPTS processor has selected a target 
	 *  we may have some manual recovery to perक्रमm क्रम.
	 */
	हाल SIR_TARGET_SELECTED:
		target = INB(np, nc_sdid) & 0xf;
		tp = &np->target[target];

		np->abrt_tbl.addr = cpu_to_scr(vtobus(np->abrt_msg));

		/*
		 *  If the target is to be reset, prepare a 
		 *  M_RESET message and clear the to_reset flag 
		 *  since we करोnnot expect this operation to fail.
		 */
		अगर (tp->to_reset) अणु
			np->abrt_msg[0] = M_RESET;
			np->abrt_tbl.size = 1;
			tp->to_reset = 0;
			अवरोध;
		पूर्ण

		/*
		 *  Otherwise, look क्रम some logical unit to be cleared.
		 */
		अगर (tp->lun0p && tp->lun0p->to_clear)
			lun = 0;
		अन्यथा अगर (tp->lunmp) अणु
			क्रम (k = 1 ; k < SYM_CONF_MAX_LUN ; k++) अणु
				अगर (tp->lunmp[k] && tp->lunmp[k]->to_clear) अणु
					lun = k;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 *  If a logical unit is to be cleared, prepare 
		 *  an IDENTIFY(lun) + ABORT MESSAGE.
		 */
		अगर (lun != -1) अणु
			काष्ठा sym_lcb *lp = sym_lp(tp, lun);
			lp->to_clear = 0; /* We करोn't expect to fail here */
			np->abrt_msg[0] = IDENTIFY(0, lun);
			np->abrt_msg[1] = M_ABORT;
			np->abrt_tbl.size = 2;
			अवरोध;
		पूर्ण

		/*
		 *  Otherwise, look क्रम some disconnected job to 
		 *  पात क्रम this target.
		 */
		i = 0;
		cp = शून्य;
		FOR_EACH_QUEUED_ELEMENT(&np->busy_ccbq, qp) अणु
			cp = sym_que_entry(qp, काष्ठा sym_ccb, link_ccbq);
			अगर (cp->host_status != HS_DISCONNECT)
				जारी;
			अगर (cp->target != target)
				जारी;
			अगर (!cp->to_पात)
				जारी;
			i = 1;	/* Means we have some */
			अवरोध;
		पूर्ण

		/*
		 *  If we have none, probably since the device has 
		 *  completed the command beक्रमe we won abitration,
		 *  send a M_ABORT message without IDENTIFY.
		 *  According to the specs, the device must just 
		 *  disconnect the BUS and not पात any task.
		 */
		अगर (!i) अणु
			np->abrt_msg[0] = M_ABORT;
			np->abrt_tbl.size = 1;
			अवरोध;
		पूर्ण

		/*
		 *  We have some task to पात.
		 *  Set the IDENTIFY(lun)
		 */
		np->abrt_msg[0] = IDENTIFY(0, cp->lun);

		/*
		 *  If we want to पात an untagged command, we 
		 *  will send a IDENTIFY + M_ABORT.
		 *  Otherwise (tagged command), we will send 
		 *  a IDENTITFY + task attributes + ABORT TAG.
		 */
		अगर (cp->tag == NO_TAG) अणु
			np->abrt_msg[1] = M_ABORT;
			np->abrt_tbl.size = 2;
		पूर्ण अन्यथा अणु
			np->abrt_msg[1] = cp->scsi_smsg[1];
			np->abrt_msg[2] = cp->scsi_smsg[2];
			np->abrt_msg[3] = M_ABORT_TAG;
			np->abrt_tbl.size = 4;
		पूर्ण
		/*
		 *  Keep track of software समयout condition, since the 
		 *  peripheral driver may not count retries on पात 
		 *  conditions not due to समयout.
		 */
		अगर (cp->to_पात == 2)
			sym_set_cam_status(cp->cmd, DID_TIME_OUT);
		cp->to_पात = 0; /* We करोnnot expect to fail here */
		अवरोध;

	/*
	 *  The target has accepted our message and चयनed 
	 *  to BUS FREE phase as we expected.
	 */
	हाल SIR_ABORT_SENT:
		target = INB(np, nc_sdid) & 0xf;
		tp = &np->target[target];
		starget = tp->starget;
		
		/*
		**  If we didn't पात anything, leave here.
		*/
		अगर (np->abrt_msg[0] == M_ABORT)
			अवरोध;

		/*
		 *  If we sent a M_RESET, then a hardware reset has 
		 *  been perक्रमmed by the target.
		 *  - Reset everything to async 8 bit
		 *  - Tell ourself to negotiate next समय :-)
		 *  - Prepare to clear all disconnected CCBs क्रम 
		 *    this target from our task list (lun=task=-1)
		 */
		lun = -1;
		task = -1;
		अगर (np->abrt_msg[0] == M_RESET) अणु
			tp->head.sval = 0;
			tp->head.wval = np->rv_scntl3;
			tp->head.uval = 0;
			spi_period(starget) = 0;
			spi_offset(starget) = 0;
			spi_width(starget) = 0;
			spi_iu(starget) = 0;
			spi_dt(starget) = 0;
			spi_qas(starget) = 0;
			tp->tgoal.check_nego = 1;
			tp->tgoal.renego = 0;
		पूर्ण

		/*
		 *  Otherwise, check क्रम the LUN and TASK(s) 
		 *  concerned by the cancelation.
		 *  If it is not ABORT_TAG then it is CLEAR_QUEUE 
		 *  or an ABORT message :-)
		 */
		अन्यथा अणु
			lun = np->abrt_msg[0] & 0x3f;
			अगर (np->abrt_msg[1] == M_ABORT_TAG)
				task = np->abrt_msg[2];
		पूर्ण

		/*
		 *  Complete all the CCBs the device should have 
		 *  पातed due to our 'kiss of death' message.
		 */
		i = (INL(np, nc_scratcha) - np->squeue_ba) / 4;
		sym_dequeue_from_squeue(np, i, target, lun, -1);
		sym_clear_tasks(np, DID_ABORT, target, lun, task);
		sym_flush_comp_queue(np, 0);

 		/*
		 *  If we sent a BDR, make upper layer aware of that.
 		 */
		अगर (np->abrt_msg[0] == M_RESET)
			starget_prपूर्णांकk(KERN_NOTICE, starget,
							"has been reset\n");
		अवरोध;
	पूर्ण

	/*
	 *  Prपूर्णांक to the log the message we पूर्णांकend to send.
	 */
	अगर (num == SIR_TARGET_SELECTED) अणु
		dev_info(&tp->starget->dev, "control msgout:");
		sym_prपूर्णांकl_hex(np->abrt_msg, np->abrt_tbl.size);
		np->abrt_tbl.size = cpu_to_scr(np->abrt_tbl.size);
	पूर्ण

	/*
	 *  Let the SCRIPTS processor जारी.
	 */
	OUTONB_STD();
पूर्ण

/*
 *  Gerard's alchemy:) that deals with with the data 
 *  poपूर्णांकer क्रम both MDP and the residual calculation.
 *
 *  I didn't want to bloat the code by more than 200 
 *  lines क्रम the handling of both MDP and the residual.
 *  This has been achieved by using a data poपूर्णांकer 
 *  representation consisting in an index in the data 
 *  array (dp_sg) and a negative offset (dp_ofs) that 
 *  have the following meaning:
 *
 *  - dp_sg = SYM_CONF_MAX_SG
 *    we are at the end of the data script.
 *  - dp_sg < SYM_CONF_MAX_SG
 *    dp_sg poपूर्णांकs to the next entry of the scatter array 
 *    we want to transfer.
 *  - dp_ofs < 0
 *    dp_ofs represents the residual of bytes of the 
 *    previous entry scatter entry we will send first.
 *  - dp_ofs = 0
 *    no residual to send first.
 *
 *  The function sym_evaluate_dp() accepts an arbitray 
 *  offset (basically from the MDP message) and वापसs 
 *  the corresponding values of dp_sg and dp_ofs.
 */

अटल पूर्णांक sym_evaluate_dp(काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp, u32 scr, पूर्णांक *ofs)
अणु
	u32	dp_scr;
	पूर्णांक	dp_ofs, dp_sg, dp_sgmin;
	पूर्णांक	पंचांगp;
	काष्ठा sym_pmc *pm;

	/*
	 *  Compute the resulted data poपूर्णांकer in term of a script 
	 *  address within some DATA script and a चिन्हित byte offset.
	 */
	dp_scr = scr;
	dp_ofs = *ofs;
	अगर	(dp_scr == SCRIPTA_BA(np, pm0_data))
		pm = &cp->phys.pm0;
	अन्यथा अगर (dp_scr == SCRIPTA_BA(np, pm1_data))
		pm = &cp->phys.pm1;
	अन्यथा
		pm = शून्य;

	अगर (pm) अणु
		dp_scr  = scr_to_cpu(pm->ret);
		dp_ofs -= scr_to_cpu(pm->sg.size) & 0x00ffffff;
	पूर्ण

	/*
	 *  If we are स्वतः-sensing, then we are करोne.
	 */
	अगर (cp->host_flags & HF_SENSE) अणु
		*ofs = dp_ofs;
		वापस 0;
	पूर्ण

	/*
	 *  Deduce the index of the sg entry.
	 *  Keep track of the index of the first valid entry.
	 *  If result is dp_sg = SYM_CONF_MAX_SG, then we are at the 
	 *  end of the data.
	 */
	पंचांगp = scr_to_cpu(cp->goalp);
	dp_sg = SYM_CONF_MAX_SG;
	अगर (dp_scr != पंचांगp)
		dp_sg -= (पंचांगp - 8 - (पूर्णांक)dp_scr) / (2*4);
	dp_sgmin = SYM_CONF_MAX_SG - cp->segments;

	/*
	 *  Move to the sg entry the data poपूर्णांकer beदीर्घs to.
	 *
	 *  If we are inside the data area, we expect result to be:
	 *
	 *  Either,
	 *      dp_ofs = 0 and dp_sg is the index of the sg entry
	 *      the data poपूर्णांकer beदीर्घs to (or the end of the data)
	 *  Or,
	 *      dp_ofs < 0 and dp_sg is the index of the sg entry 
	 *      the data poपूर्णांकer beदीर्घs to + 1.
	 */
	अगर (dp_ofs < 0) अणु
		पूर्णांक n;
		जबतक (dp_sg > dp_sgmin) अणु
			--dp_sg;
			पंचांगp = scr_to_cpu(cp->phys.data[dp_sg].size);
			n = dp_ofs + (पंचांगp & 0xffffff);
			अगर (n > 0) अणु
				++dp_sg;
				अवरोध;
			पूर्ण
			dp_ofs = n;
		पूर्ण
	पूर्ण
	अन्यथा अगर (dp_ofs > 0) अणु
		जबतक (dp_sg < SYM_CONF_MAX_SG) अणु
			पंचांगp = scr_to_cpu(cp->phys.data[dp_sg].size);
			dp_ofs -= (पंचांगp & 0xffffff);
			++dp_sg;
			अगर (dp_ofs <= 0)
				अवरोध;
		पूर्ण
	पूर्ण

	/*
	 *  Make sure the data poपूर्णांकer is inside the data area.
	 *  If not, वापस some error.
	 */
	अगर	(dp_sg < dp_sgmin || (dp_sg == dp_sgmin && dp_ofs < 0))
		जाओ out_err;
	अन्यथा अगर	(dp_sg > SYM_CONF_MAX_SG ||
		 (dp_sg == SYM_CONF_MAX_SG && dp_ofs > 0))
		जाओ out_err;

	/*
	 *  Save the extreme poपूर्णांकer अगर needed.
	 */
	अगर (dp_sg > cp->ext_sg ||
            (dp_sg == cp->ext_sg && dp_ofs > cp->ext_ofs)) अणु
		cp->ext_sg  = dp_sg;
		cp->ext_ofs = dp_ofs;
	पूर्ण

	/*
	 *  Return data.
	 */
	*ofs = dp_ofs;
	वापस dp_sg;

out_err:
	वापस -1;
पूर्ण

/*
 *  chip handler क्रम MODIFY DATA POINTER MESSAGE
 *
 *  We also call this function on IGNORE WIDE RESIDUE 
 *  messages that करो not match a SWIDE full condition.
 *  Btw, we assume in that situation that such a message 
 *  is equivalent to a MODIFY DATA POINTER (offset=-1).
 */

अटल व्योम sym_modअगरy_dp(काष्ठा sym_hcb *np, काष्ठा sym_tcb *tp, काष्ठा sym_ccb *cp, पूर्णांक ofs)
अणु
	पूर्णांक dp_ofs	= ofs;
	u32	dp_scr	= sym_get_script_dp (np, cp);
	u32	dp_ret;
	u32	पंचांगp;
	u_अक्षर	hflags;
	पूर्णांक	dp_sg;
	काष्ठा	sym_pmc *pm;

	/*
	 *  Not supported क्रम स्वतः-sense.
	 */
	अगर (cp->host_flags & HF_SENSE)
		जाओ out_reject;

	/*
	 *  Apply our alchemy:) (see comments in sym_evaluate_dp()), 
	 *  to the resulted data poपूर्णांकer.
	 */
	dp_sg = sym_evaluate_dp(np, cp, dp_scr, &dp_ofs);
	अगर (dp_sg < 0)
		जाओ out_reject;

	/*
	 *  And our alchemy:) allows to easily calculate the data 
	 *  script address we want to वापस क्रम the next data phase.
	 */
	dp_ret = cpu_to_scr(cp->goalp);
	dp_ret = dp_ret - 8 - (SYM_CONF_MAX_SG - dp_sg) * (2*4);

	/*
	 *  If offset / scatter entry is zero we करोnnot need 
	 *  a context क्रम the new current data poपूर्णांकer.
	 */
	अगर (dp_ofs == 0) अणु
		dp_scr = dp_ret;
		जाओ out_ok;
	पूर्ण

	/*
	 *  Get a context क्रम the new current data poपूर्णांकer.
	 */
	hflags = INB(np, HF_PRT);

	अगर (hflags & HF_DP_SAVED)
		hflags ^= HF_ACT_PM;

	अगर (!(hflags & HF_ACT_PM)) अणु
		pm  = &cp->phys.pm0;
		dp_scr = SCRIPTA_BA(np, pm0_data);
	पूर्ण
	अन्यथा अणु
		pm = &cp->phys.pm1;
		dp_scr = SCRIPTA_BA(np, pm1_data);
	पूर्ण

	hflags &= ~(HF_DP_SAVED);

	OUTB(np, HF_PRT, hflags);

	/*
	 *  Set up the new current data poपूर्णांकer.
	 *  ofs < 0 there, and क्रम the next data phase, we 
	 *  want to transfer part of the data of the sg entry 
	 *  corresponding to index dp_sg-1 prior to वापसing 
	 *  to the मुख्य data script.
	 */
	pm->ret = cpu_to_scr(dp_ret);
	पंचांगp  = scr_to_cpu(cp->phys.data[dp_sg-1].addr);
	पंचांगp += scr_to_cpu(cp->phys.data[dp_sg-1].size) + dp_ofs;
	pm->sg.addr = cpu_to_scr(पंचांगp);
	pm->sg.size = cpu_to_scr(-dp_ofs);

out_ok:
	sym_set_script_dp (np, cp, dp_scr);
	OUTL_DSP(np, SCRIPTA_BA(np, clrack));
	वापस;

out_reject:
	OUTL_DSP(np, SCRIPTB_BA(np, msg_bad));
पूर्ण


/*
 *  chip calculation of the data residual.
 *
 *  As I used to say, the requirement of data residual 
 *  in SCSI is broken, useless and cannot be achieved 
 *  without huge complनिकासy.
 *  But most OSes and even the official CAM require it.
 *  When stupidity happens to be so widely spपढ़ो inside 
 *  a community, it माला_लो hard to convince.
 *
 *  Anyway, I करोn't care, since I am not going to use 
 *  any software that considers this data residual as 
 *  a relevant inक्रमmation. :)
 */

पूर्णांक sym_compute_residual(काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp)
अणु
	पूर्णांक dp_sg, resid = 0;
	पूर्णांक dp_ofs = 0;

	/*
	 *  Check क्रम some data lost or just thrown away.
	 *  We are not required to be quite accurate in this 
	 *  situation. Btw, अगर we are odd क्रम output and the 
	 *  device claims some more data, it may well happen 
	 *  than our residual be zero. :-)
	 */
	अगर (cp->xerr_status & (XE_EXTRA_DATA|XE_SODL_UNRUN|XE_SWIDE_OVRUN)) अणु
		अगर (cp->xerr_status & XE_EXTRA_DATA)
			resid -= cp->extra_bytes;
		अगर (cp->xerr_status & XE_SODL_UNRUN)
			++resid;
		अगर (cp->xerr_status & XE_SWIDE_OVRUN)
			--resid;
	पूर्ण

	/*
	 *  If all data has been transferred,
	 *  there is no residual.
	 */
	अगर (cp->phys.head.lastp == cp->goalp)
		वापस resid;

	/*
	 *  If no data transfer occurs, or अगर the data
	 *  poपूर्णांकer is weird, वापस full residual.
	 */
	अगर (cp->startp == cp->phys.head.lastp ||
	    sym_evaluate_dp(np, cp, scr_to_cpu(cp->phys.head.lastp),
			    &dp_ofs) < 0) अणु
		वापस cp->data_len - cp->odd_byte_adjusपंचांगent;
	पूर्ण

	/*
	 *  If we were स्वतः-sensing, then we are करोne.
	 */
	अगर (cp->host_flags & HF_SENSE) अणु
		वापस -dp_ofs;
	पूर्ण

	/*
	 *  We are now full comक्रमtable in the computation 
	 *  of the data residual (2's complement).
	 */
	resid = -cp->ext_ofs;
	क्रम (dp_sg = cp->ext_sg; dp_sg < SYM_CONF_MAX_SG; ++dp_sg) अणु
		u_पूर्णांक पंचांगp = scr_to_cpu(cp->phys.data[dp_sg].size);
		resid += (पंचांगp & 0xffffff);
	पूर्ण

	resid -= cp->odd_byte_adjusपंचांगent;

	/*
	 *  Hopefully, the result is not too wrong.
	 */
	वापस resid;
पूर्ण

/*
 *  Negotiation क्रम WIDE and SYNCHRONOUS DATA TRANSFER.
 *
 *  When we try to negotiate, we append the negotiation message
 *  to the identअगरy and (maybe) simple tag message.
 *  The host status field is set to HS_NEGOTIATE to mark this
 *  situation.
 *
 *  If the target करोesn't answer this message immediately
 *  (as required by the standard), the SIR_NEGO_FAILED पूर्णांकerrupt
 *  will be उठाओd eventually.
 *  The handler हटाओs the HS_NEGOTIATE status, and sets the
 *  negotiated value to the शेष (async / nowide).
 *
 *  If we receive a matching answer immediately, we check it
 *  क्रम validity, and set the values.
 *
 *  If we receive a Reject message immediately, we assume the
 *  negotiation has failed, and fall back to standard values.
 *
 *  If we receive a negotiation message जबतक not in HS_NEGOTIATE
 *  state, it's a target initiated negotiation. We prepare a
 *  (hopefully) valid answer, set our parameters, and send back 
 *  this answer to the target.
 *
 *  If the target करोesn't fetch the answer (no message out phase),
 *  we assume the negotiation has failed, and fall back to शेष
 *  settings (SIR_NEGO_PROTO पूर्णांकerrupt).
 *
 *  When we set the values, we adjust them in all ccbs beदीर्घing 
 *  to this target, in the controller's रेजिस्टर, and in the "phys"
 *  field of the controller's काष्ठा sym_hcb.
 */

/*
 *  chip handler क्रम SYNCHRONOUS DATA TRANSFER REQUEST (SDTR) message.
 */
अटल पूर्णांक  
sym_sync_nego_check(काष्ठा sym_hcb *np, पूर्णांक req, काष्ठा sym_ccb *cp)
अणु
	पूर्णांक target = cp->target;
	u_अक्षर	chg, ofs, per, fak, भाग;

	अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
		sym_prपूर्णांक_nego_msg(np, target, "sync msgin", np->msgin);
	पूर्ण

	/*
	 *  Get requested values.
	 */
	chg = 0;
	per = np->msgin[3];
	ofs = np->msgin[4];

	/*
	 *  Check values against our limits.
	 */
	अगर (ofs) अणु
		अगर (ofs > np->maxoffs)
			अणुchg = 1; ofs = np->maxoffs;पूर्ण
	पूर्ण

	अगर (ofs) अणु
		अगर (per < np->minsync)
			अणुchg = 1; per = np->minsync;पूर्ण
	पूर्ण

	/*
	 *  Get new chip synchronous parameters value.
	 */
	भाग = fak = 0;
	अगर (ofs && sym_माला_लोync(np, 0, per, &भाग, &fak) < 0)
		जाओ reject_it;

	अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
		sym_prपूर्णांक_addr(cp->cmd,
				"sdtr: ofs=%d per=%d div=%d fak=%d chg=%d.\n",
				ofs, per, भाग, fak, chg);
	पूर्ण

	/*
	 *  If it was an answer we want to change, 
	 *  then it isn't acceptable. Reject it.
	 */
	अगर (!req && chg)
		जाओ reject_it;

	/*
	 *  Apply new values.
	 */
	sym_setsync (np, target, ofs, per, भाग, fak);

	/*
	 *  It was an answer. We are करोne.
	 */
	अगर (!req)
		वापस 0;

	/*
	 *  It was a request. Prepare an answer message.
	 */
	spi_populate_sync_msg(np->msgout, per, ofs);

	अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
		sym_prपूर्णांक_nego_msg(np, target, "sync msgout", np->msgout);
	पूर्ण

	np->msgin [0] = M_NOOP;

	वापस 0;

reject_it:
	sym_setsync (np, target, 0, 0, 0, 0);
	वापस -1;
पूर्ण

अटल व्योम sym_sync_nego(काष्ठा sym_hcb *np, काष्ठा sym_tcb *tp, काष्ठा sym_ccb *cp)
अणु
	पूर्णांक req = 1;
	पूर्णांक result;

	/*
	 *  Request or answer ?
	 */
	अगर (INB(np, HS_PRT) == HS_NEGOTIATE) अणु
		OUTB(np, HS_PRT, HS_BUSY);
		अगर (cp->nego_status && cp->nego_status != NS_SYNC)
			जाओ reject_it;
		req = 0;
	पूर्ण

	/*
	 *  Check and apply new values.
	 */
	result = sym_sync_nego_check(np, req, cp);
	अगर (result)	/* Not acceptable, reject it */
		जाओ reject_it;
	अगर (req) अणु	/* Was a request, send response. */
		cp->nego_status = NS_SYNC;
		OUTL_DSP(np, SCRIPTB_BA(np, sdtr_resp));
	पूर्ण
	अन्यथा		/* Was a response, we are करोne. */
		OUTL_DSP(np, SCRIPTA_BA(np, clrack));
	वापस;

reject_it:
	OUTL_DSP(np, SCRIPTB_BA(np, msg_bad));
पूर्ण

/*
 *  chip handler क्रम PARALLEL PROTOCOL REQUEST (PPR) message.
 */
अटल पूर्णांक 
sym_ppr_nego_check(काष्ठा sym_hcb *np, पूर्णांक req, पूर्णांक target)
अणु
	काष्ठा sym_tcb *tp = &np->target[target];
	अचिन्हित अक्षर fak, भाग;
	पूर्णांक dt, chg = 0;

	अचिन्हित अक्षर per = np->msgin[3];
	अचिन्हित अक्षर ofs = np->msgin[5];
	अचिन्हित अक्षर wide = np->msgin[6];
	अचिन्हित अक्षर opts = np->msgin[7] & PPR_OPT_MASK;

	अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
		sym_prपूर्णांक_nego_msg(np, target, "ppr msgin", np->msgin);
	पूर्ण

	/*
	 *  Check values against our limits.
	 */
	अगर (wide > np->maxwide) अणु
		chg = 1;
		wide = np->maxwide;
	पूर्ण
	अगर (!wide || !(np->features & FE_U3EN))
		opts = 0;

	अगर (opts != (np->msgin[7] & PPR_OPT_MASK))
		chg = 1;

	dt = opts & PPR_OPT_DT;

	अगर (ofs) अणु
		अचिन्हित अक्षर maxoffs = dt ? np->maxoffs_dt : np->maxoffs;
		अगर (ofs > maxoffs) अणु
			chg = 1;
			ofs = maxoffs;
		पूर्ण
	पूर्ण

	अगर (ofs) अणु
		अचिन्हित अक्षर minsync = dt ? np->minsync_dt : np->minsync;
		अगर (per < minsync) अणु
			chg = 1;
			per = minsync;
		पूर्ण
	पूर्ण

	/*
	 *  Get new chip synchronous parameters value.
	 */
	भाग = fak = 0;
	अगर (ofs && sym_माला_लोync(np, dt, per, &भाग, &fak) < 0)
		जाओ reject_it;

	/*
	 *  If it was an answer we want to change, 
	 *  then it isn't acceptable. Reject it.
	 */
	अगर (!req && chg)
		जाओ reject_it;

	/*
	 *  Apply new values.
	 */
	sym_setpprot(np, target, opts, ofs, per, wide, भाग, fak);

	/*
	 *  It was an answer. We are करोne.
	 */
	अगर (!req)
		वापस 0;

	/*
	 *  It was a request. Prepare an answer message.
	 */
	spi_populate_ppr_msg(np->msgout, per, ofs, wide, opts);

	अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
		sym_prपूर्णांक_nego_msg(np, target, "ppr msgout", np->msgout);
	पूर्ण

	np->msgin [0] = M_NOOP;

	वापस 0;

reject_it:
	sym_setpprot (np, target, 0, 0, 0, 0, 0, 0);
	/*
	 *  If it is a device response that should result in  
	 *  ST, we may want to try a legacy negotiation later.
	 */
	अगर (!req && !opts) अणु
		tp->tgoal.period = per;
		tp->tgoal.offset = ofs;
		tp->tgoal.width = wide;
		tp->tgoal.iu = tp->tgoal.dt = tp->tgoal.qas = 0;
		tp->tgoal.check_nego = 1;
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम sym_ppr_nego(काष्ठा sym_hcb *np, काष्ठा sym_tcb *tp, काष्ठा sym_ccb *cp)
अणु
	पूर्णांक req = 1;
	पूर्णांक result;

	/*
	 *  Request or answer ?
	 */
	अगर (INB(np, HS_PRT) == HS_NEGOTIATE) अणु
		OUTB(np, HS_PRT, HS_BUSY);
		अगर (cp->nego_status && cp->nego_status != NS_PPR)
			जाओ reject_it;
		req = 0;
	पूर्ण

	/*
	 *  Check and apply new values.
	 */
	result = sym_ppr_nego_check(np, req, cp->target);
	अगर (result)	/* Not acceptable, reject it */
		जाओ reject_it;
	अगर (req) अणु	/* Was a request, send response. */
		cp->nego_status = NS_PPR;
		OUTL_DSP(np, SCRIPTB_BA(np, ppr_resp));
	पूर्ण
	अन्यथा		/* Was a response, we are करोne. */
		OUTL_DSP(np, SCRIPTA_BA(np, clrack));
	वापस;

reject_it:
	OUTL_DSP(np, SCRIPTB_BA(np, msg_bad));
पूर्ण

/*
 *  chip handler क्रम WIDE DATA TRANSFER REQUEST (WDTR) message.
 */
अटल पूर्णांक  
sym_wide_nego_check(काष्ठा sym_hcb *np, पूर्णांक req, काष्ठा sym_ccb *cp)
अणु
	पूर्णांक target = cp->target;
	u_अक्षर	chg, wide;

	अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
		sym_prपूर्णांक_nego_msg(np, target, "wide msgin", np->msgin);
	पूर्ण

	/*
	 *  Get requested values.
	 */
	chg  = 0;
	wide = np->msgin[3];

	/*
	 *  Check values against our limits.
	 */
	अगर (wide > np->maxwide) अणु
		chg = 1;
		wide = np->maxwide;
	पूर्ण

	अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
		sym_prपूर्णांक_addr(cp->cmd, "wdtr: wide=%d chg=%d.\n",
				wide, chg);
	पूर्ण

	/*
	 *  If it was an answer we want to change, 
	 *  then it isn't acceptable. Reject it.
	 */
	अगर (!req && chg)
		जाओ reject_it;

	/*
	 *  Apply new values.
	 */
	sym_setwide (np, target, wide);

	/*
	 *  It was an answer. We are करोne.
	 */
	अगर (!req)
		वापस 0;

	/*
	 *  It was a request. Prepare an answer message.
	 */
	spi_populate_width_msg(np->msgout, wide);

	np->msgin [0] = M_NOOP;

	अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
		sym_prपूर्णांक_nego_msg(np, target, "wide msgout", np->msgout);
	पूर्ण

	वापस 0;

reject_it:
	वापस -1;
पूर्ण

अटल व्योम sym_wide_nego(काष्ठा sym_hcb *np, काष्ठा sym_tcb *tp, काष्ठा sym_ccb *cp)
अणु
	पूर्णांक req = 1;
	पूर्णांक result;

	/*
	 *  Request or answer ?
	 */
	अगर (INB(np, HS_PRT) == HS_NEGOTIATE) अणु
		OUTB(np, HS_PRT, HS_BUSY);
		अगर (cp->nego_status && cp->nego_status != NS_WIDE)
			जाओ reject_it;
		req = 0;
	पूर्ण

	/*
	 *  Check and apply new values.
	 */
	result = sym_wide_nego_check(np, req, cp);
	अगर (result)	/* Not acceptable, reject it */
		जाओ reject_it;
	अगर (req) अणु	/* Was a request, send response. */
		cp->nego_status = NS_WIDE;
		OUTL_DSP(np, SCRIPTB_BA(np, wdtr_resp));
	पूर्ण अन्यथा अणु		/* Was a response. */
		/*
		 * Negotiate क्रम SYNC immediately after WIDE response.
		 * This allows to negotiate क्रम both WIDE and SYNC on 
		 * a single SCSI command (Suggested by Justin Gibbs).
		 */
		अगर (tp->tgoal.offset) अणु
			spi_populate_sync_msg(np->msgout, tp->tgoal.period,
					tp->tgoal.offset);

			अगर (DEBUG_FLAGS & DEBUG_NEGO) अणु
				sym_prपूर्णांक_nego_msg(np, cp->target,
				                   "sync msgout", np->msgout);
			पूर्ण

			cp->nego_status = NS_SYNC;
			OUTB(np, HS_PRT, HS_NEGOTIATE);
			OUTL_DSP(np, SCRIPTB_BA(np, sdtr_resp));
			वापस;
		पूर्ण अन्यथा
			OUTL_DSP(np, SCRIPTA_BA(np, clrack));
	पूर्ण

	वापस;

reject_it:
	OUTL_DSP(np, SCRIPTB_BA(np, msg_bad));
पूर्ण

/*
 *  Reset DT, SYNC or WIDE to शेष settings.
 *
 *  Called when a negotiation करोes not succeed either 
 *  on rejection or on protocol error.
 *
 *  A target that understands a PPR message should never 
 *  reject it, and messing with it is very unlikely.
 *  So, अगर a PPR makes problems, we may just want to 
 *  try a legacy negotiation later.
 */
अटल व्योम sym_nego_शेष(काष्ठा sym_hcb *np, काष्ठा sym_tcb *tp, काष्ठा sym_ccb *cp)
अणु
	चयन (cp->nego_status) अणु
	हाल NS_PPR:
#अगर 0
		sym_setpprot (np, cp->target, 0, 0, 0, 0, 0, 0);
#अन्यथा
		अगर (tp->tgoal.period < np->minsync)
			tp->tgoal.period = np->minsync;
		अगर (tp->tgoal.offset > np->maxoffs)
			tp->tgoal.offset = np->maxoffs;
		tp->tgoal.iu = tp->tgoal.dt = tp->tgoal.qas = 0;
		tp->tgoal.check_nego = 1;
#पूर्ण_अगर
		अवरोध;
	हाल NS_SYNC:
		sym_setsync (np, cp->target, 0, 0, 0, 0);
		अवरोध;
	हाल NS_WIDE:
		sym_setwide (np, cp->target, 0);
		अवरोध;
	पूर्ण
	np->msgin [0] = M_NOOP;
	np->msgout[0] = M_NOOP;
	cp->nego_status = 0;
पूर्ण

/*
 *  chip handler क्रम MESSAGE REJECT received in response to 
 *  PPR, WIDE or SYNCHRONOUS negotiation.
 */
अटल व्योम sym_nego_rejected(काष्ठा sym_hcb *np, काष्ठा sym_tcb *tp, काष्ठा sym_ccb *cp)
अणु
	sym_nego_शेष(np, tp, cp);
	OUTB(np, HS_PRT, HS_BUSY);
पूर्ण

#घोषणा sym_prपूर्णांकk(lvl, tp, cp, fmt, v...) करो अणु \
	अगर (cp)							\
		scmd_prपूर्णांकk(lvl, cp->cmd, fmt, ##v);		\
	अन्यथा							\
		starget_prपूर्णांकk(lvl, tp->starget, fmt, ##v);	\
पूर्ण जबतक (0)

/*
 *  chip exception handler क्रम programmed पूर्णांकerrupts.
 */
अटल व्योम sym_पूर्णांक_sir(काष्ठा sym_hcb *np)
अणु
	u_अक्षर	num	= INB(np, nc_dsps);
	u32	dsa	= INL(np, nc_dsa);
	काष्ठा sym_ccb *cp	= sym_ccb_from_dsa(np, dsa);
	u_अक्षर	target	= INB(np, nc_sdid) & 0x0f;
	काष्ठा sym_tcb *tp	= &np->target[target];
	पूर्णांक	पंचांगp;

	अगर (DEBUG_FLAGS & DEBUG_TINY) म_लिखो ("I#%d", num);

	चयन (num) अणु
#अगर   SYM_CONF_DMA_ADDRESSING_MODE == 2
	/*
	 *  SCRIPTS tell us that we may have to update 
	 *  64 bit DMA segment रेजिस्टरs.
	 */
	हाल SIR_DMAP_सूचीTY:
		sym_update_dmap_regs(np);
		जाओ out;
#पूर्ण_अगर
	/*
	 *  Command has been completed with error condition 
	 *  or has been स्वतः-sensed.
	 */
	हाल SIR_COMPLETE_ERROR:
		sym_complete_error(np, cp);
		वापस;
	/*
	 *  The C code is currently trying to recover from something.
	 *  Typically, user want to पात some command.
	 */
	हाल SIR_SCRIPT_STOPPED:
	हाल SIR_TARGET_SELECTED:
	हाल SIR_ABORT_SENT:
		sym_sir_task_recovery(np, num);
		वापस;
	/*
	 *  The device didn't go to MSG OUT phase after having 
	 *  been selected with ATN.  We करो not want to handle that.
	 */
	हाल SIR_SEL_ATN_NO_MSG_OUT:
		sym_prपूर्णांकk(KERN_WARNING, tp, cp,
				"No MSG OUT phase after selection with ATN\n");
		जाओ out_stuck;
	/*
	 *  The device didn't चयन to MSG IN phase after 
	 *  having reselected the initiator.
	 */
	हाल SIR_RESEL_NO_MSG_IN:
		sym_prपूर्णांकk(KERN_WARNING, tp, cp,
				"No MSG IN phase after reselection\n");
		जाओ out_stuck;
	/*
	 *  After reselection, the device sent a message that wasn't 
	 *  an IDENTIFY.
	 */
	हाल SIR_RESEL_NO_IDENTIFY:
		sym_prपूर्णांकk(KERN_WARNING, tp, cp,
				"No IDENTIFY after reselection\n");
		जाओ out_stuck;
	/*
	 *  The device reselected a LUN we करो not know about.
	 */
	हाल SIR_RESEL_BAD_LUN:
		np->msgout[0] = M_RESET;
		जाओ out;
	/*
	 *  The device reselected क्रम an untagged nexus and we 
	 *  haven't any.
	 */
	हाल SIR_RESEL_BAD_I_T_L:
		np->msgout[0] = M_ABORT;
		जाओ out;
	/*
	 * The device reselected क्रम a tagged nexus that we करो not have.
	 */
	हाल SIR_RESEL_BAD_I_T_L_Q:
		np->msgout[0] = M_ABORT_TAG;
		जाओ out;
	/*
	 *  The SCRIPTS let us know that the device has grabbed 
	 *  our message and will पात the job.
	 */
	हाल SIR_RESEL_ABORTED:
		np->lasपंचांगsg = np->msgout[0];
		np->msgout[0] = M_NOOP;
		sym_prपूर्णांकk(KERN_WARNING, tp, cp,
			"message %x sent on bad reselection\n", np->lasपंचांगsg);
		जाओ out;
	/*
	 *  The SCRIPTS let us know that a message has been 
	 *  successfully sent to the device.
	 */
	हाल SIR_MSG_OUT_DONE:
		np->lasपंचांगsg = np->msgout[0];
		np->msgout[0] = M_NOOP;
		/* Should we really care of that */
		अगर (np->lasपंचांगsg == M_PARITY || np->lasपंचांगsg == M_ID_ERROR) अणु
			अगर (cp) अणु
				cp->xerr_status &= ~XE_PARITY_ERR;
				अगर (!cp->xerr_status)
					OUTOFFB(np, HF_PRT, HF_EXT_ERR);
			पूर्ण
		पूर्ण
		जाओ out;
	/*
	 *  The device didn't send a GOOD SCSI status.
	 *  We may have some work to करो prior to allow 
	 *  the SCRIPTS processor to जारी.
	 */
	हाल SIR_BAD_SCSI_STATUS:
		अगर (!cp)
			जाओ out;
		sym_sir_bad_scsi_status(np, num, cp);
		वापस;
	/*
	 *  We are asked by the SCRIPTS to prepare a 
	 *  REJECT message.
	 */
	हाल SIR_REJECT_TO_SEND:
		sym_prपूर्णांक_msg(cp, "M_REJECT to send for ", np->msgin);
		np->msgout[0] = M_REJECT;
		जाओ out;
	/*
	 *  We have been ODD at the end of a DATA IN 
	 *  transfer and the device didn't send a 
	 *  IGNORE WIDE RESIDUE message.
	 *  It is a data overrun condition.
	 */
	हाल SIR_SWIDE_OVERRUN:
		अगर (cp) अणु
			OUTONB(np, HF_PRT, HF_EXT_ERR);
			cp->xerr_status |= XE_SWIDE_OVRUN;
		पूर्ण
		जाओ out;
	/*
	 *  We have been ODD at the end of a DATA OUT 
	 *  transfer.
	 *  It is a data underrun condition.
	 */
	हाल SIR_SODL_UNDERRUN:
		अगर (cp) अणु
			OUTONB(np, HF_PRT, HF_EXT_ERR);
			cp->xerr_status |= XE_SODL_UNRUN;
		पूर्ण
		जाओ out;
	/*
	 *  The device wants us to tranfer more data than 
	 *  expected or in the wrong direction.
	 *  The number of extra bytes is in scratcha.
	 *  It is a data overrun condition.
	 */
	हाल SIR_DATA_OVERRUN:
		अगर (cp) अणु
			OUTONB(np, HF_PRT, HF_EXT_ERR);
			cp->xerr_status |= XE_EXTRA_DATA;
			cp->extra_bytes += INL(np, nc_scratcha);
		पूर्ण
		जाओ out;
	/*
	 *  The device चयनed to an illegal phase (4/5).
	 */
	हाल SIR_BAD_PHASE:
		अगर (cp) अणु
			OUTONB(np, HF_PRT, HF_EXT_ERR);
			cp->xerr_status |= XE_BAD_PHASE;
		पूर्ण
		जाओ out;
	/*
	 *  We received a message.
	 */
	हाल SIR_MSG_RECEIVED:
		अगर (!cp)
			जाओ out_stuck;
		चयन (np->msgin [0]) अणु
		/*
		 *  We received an extended message.
		 *  We handle MODIFY DATA POINTER, SDTR, WDTR 
		 *  and reject all other extended messages.
		 */
		हाल M_EXTENDED:
			चयन (np->msgin [2]) अणु
			हाल M_X_MODIFY_DP:
				अगर (DEBUG_FLAGS & DEBUG_POINTER)
					sym_prपूर्णांक_msg(cp, "extended msg ",
						      np->msgin);
				पंचांगp = (np->msgin[3]<<24) + (np->msgin[4]<<16) + 
				      (np->msgin[5]<<8)  + (np->msgin[6]);
				sym_modअगरy_dp(np, tp, cp, पंचांगp);
				वापस;
			हाल M_X_SYNC_REQ:
				sym_sync_nego(np, tp, cp);
				वापस;
			हाल M_X_PPR_REQ:
				sym_ppr_nego(np, tp, cp);
				वापस;
			हाल M_X_WIDE_REQ:
				sym_wide_nego(np, tp, cp);
				वापस;
			शेष:
				जाओ out_reject;
			पूर्ण
			अवरोध;
		/*
		 *  We received a 1/2 byte message not handled from SCRIPTS.
		 *  We are only expecting MESSAGE REJECT and IGNORE WIDE 
		 *  RESIDUE messages that haven't been anticipated by 
		 *  SCRIPTS on SWIDE full condition. Unanticipated IGNORE 
		 *  WIDE RESIDUE messages are aliased as MODIFY DP (-1).
		 */
		हाल M_IGN_RESIDUE:
			अगर (DEBUG_FLAGS & DEBUG_POINTER)
				sym_prपूर्णांक_msg(cp, "1 or 2 byte ", np->msgin);
			अगर (cp->host_flags & HF_SENSE)
				OUTL_DSP(np, SCRIPTA_BA(np, clrack));
			अन्यथा
				sym_modअगरy_dp(np, tp, cp, -1);
			वापस;
		हाल M_REJECT:
			अगर (INB(np, HS_PRT) == HS_NEGOTIATE)
				sym_nego_rejected(np, tp, cp);
			अन्यथा अणु
				sym_prपूर्णांक_addr(cp->cmd,
					"M_REJECT received (%x:%x).\n",
					scr_to_cpu(np->lasपंचांगsg), np->msgout[0]);
			पूर्ण
			जाओ out_clrack;
		शेष:
			जाओ out_reject;
		पूर्ण
		अवरोध;
	/*
	 *  We received an unknown message.
	 *  Ignore all MSG IN phases and reject it.
	 */
	हाल SIR_MSG_WEIRD:
		sym_prपूर्णांक_msg(cp, "WEIRD message received", np->msgin);
		OUTL_DSP(np, SCRIPTB_BA(np, msg_weird));
		वापस;
	/*
	 *  Negotiation failed.
	 *  Target करोes not send us the reply.
	 *  Remove the HS_NEGOTIATE status.
	 */
	हाल SIR_NEGO_FAILED:
		OUTB(np, HS_PRT, HS_BUSY);
	/*
	 *  Negotiation failed.
	 *  Target करोes not want answer message.
	 */
		fallthrough;
	हाल SIR_NEGO_PROTO:
		sym_nego_शेष(np, tp, cp);
		जाओ out;
	पूर्ण

out:
	OUTONB_STD();
	वापस;
out_reject:
	OUTL_DSP(np, SCRIPTB_BA(np, msg_bad));
	वापस;
out_clrack:
	OUTL_DSP(np, SCRIPTA_BA(np, clrack));
	वापस;
out_stuck:
	वापस;
पूर्ण

/*
 *  Acquire a control block
 */
काष्ठा sym_ccb *sym_get_ccb (काष्ठा sym_hcb *np, काष्ठा scsi_cmnd *cmd, u_अक्षर tag_order)
अणु
	u_अक्षर tn = cmd->device->id;
	u_अक्षर ln = cmd->device->lun;
	काष्ठा sym_tcb *tp = &np->target[tn];
	काष्ठा sym_lcb *lp = sym_lp(tp, ln);
	u_लघु tag = NO_TAG;
	SYM_QUEHEAD *qp;
	काष्ठा sym_ccb *cp = शून्य;

	/*
	 *  Look क्रम a मुक्त CCB
	 */
	अगर (sym_que_empty(&np->मुक्त_ccbq))
		sym_alloc_ccb(np);
	qp = sym_remque_head(&np->मुक्त_ccbq);
	अगर (!qp)
		जाओ out;
	cp = sym_que_entry(qp, काष्ठा sym_ccb, link_ccbq);

	अणु
		/*
		 *  If we have been asked क्रम a tagged command.
		 */
		अगर (tag_order) अणु
			/*
			 *  Debugging purpose.
			 */
#अगर_अघोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
			अगर (lp->busy_itl != 0)
				जाओ out_मुक्त;
#पूर्ण_अगर
			/*
			 *  Allocate resources क्रम tags अगर not yet.
			 */
			अगर (!lp->cb_tags) अणु
				sym_alloc_lcb_tags(np, tn, ln);
				अगर (!lp->cb_tags)
					जाओ out_मुक्त;
			पूर्ण
			/*
			 *  Get a tag क्रम this SCSI IO and set up
			 *  the CCB bus address क्रम reselection, 
			 *  and count it क्रम this LUN.
			 *  Toggle reselect path to tagged.
			 */
			अगर (lp->busy_itlq < SYM_CONF_MAX_TASK) अणु
				tag = lp->cb_tags[lp->ia_tag];
				अगर (++lp->ia_tag == SYM_CONF_MAX_TASK)
					lp->ia_tag = 0;
				++lp->busy_itlq;
#अगर_अघोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
				lp->itlq_tbl[tag] = cpu_to_scr(cp->ccb_ba);
				lp->head.resel_sa =
					cpu_to_scr(SCRIPTA_BA(np, resel_tag));
#पूर्ण_अगर
#अगर_घोषित SYM_OPT_LIMIT_COMMAND_REORDERING
				cp->tags_si = lp->tags_si;
				++lp->tags_sum[cp->tags_si];
				++lp->tags_since;
#पूर्ण_अगर
			पूर्ण
			अन्यथा
				जाओ out_मुक्त;
		पूर्ण
		/*
		 *  This command will not be tagged.
		 *  If we alपढ़ोy have either a tagged or untagged 
		 *  one, refuse to overlap this untagged one.
		 */
		अन्यथा अणु
			/*
			 *  Debugging purpose.
			 */
#अगर_अघोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
			अगर (lp->busy_itl != 0 || lp->busy_itlq != 0)
				जाओ out_मुक्त;
#पूर्ण_अगर
			/*
			 *  Count this nexus क्रम this LUN.
			 *  Set up the CCB bus address क्रम reselection.
			 *  Toggle reselect path to untagged.
			 */
			++lp->busy_itl;
#अगर_अघोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
			अगर (lp->busy_itl == 1) अणु
				lp->head.itl_task_sa = cpu_to_scr(cp->ccb_ba);
				lp->head.resel_sa =
				      cpu_to_scr(SCRIPTA_BA(np, resel_no_tag));
			पूर्ण
			अन्यथा
				जाओ out_मुक्त;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	/*
	 *  Put the CCB पूर्णांकo the busy queue.
	 */
	sym_insque_tail(&cp->link_ccbq, &np->busy_ccbq);
#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	अगर (lp) अणु
		sym_remque(&cp->link2_ccbq);
		sym_insque_tail(&cp->link2_ccbq, &lp->रुकोing_ccbq);
	पूर्ण

#पूर्ण_अगर
	cp->to_पात = 0;
	cp->odd_byte_adjusपंचांगent = 0;
	cp->tag	   = tag;
	cp->order  = tag_order;
	cp->target = tn;
	cp->lun    = ln;

	अगर (DEBUG_FLAGS & DEBUG_TAGS) अणु
		sym_prपूर्णांक_addr(cmd, "ccb @%p using tag %d.\n", cp, tag);
	पूर्ण

out:
	वापस cp;
out_मुक्त:
	sym_insque_head(&cp->link_ccbq, &np->मुक्त_ccbq);
	वापस शून्य;
पूर्ण

/*
 *  Release one control block
 */
व्योम sym_मुक्त_ccb (काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp)
अणु
	काष्ठा sym_tcb *tp = &np->target[cp->target];
	काष्ठा sym_lcb *lp = sym_lp(tp, cp->lun);

	अगर (DEBUG_FLAGS & DEBUG_TAGS) अणु
		sym_prपूर्णांक_addr(cp->cmd, "ccb @%p freeing tag %d.\n",
				cp, cp->tag);
	पूर्ण

	/*
	 *  If LCB available,
	 */
	अगर (lp) अणु
		/*
		 *  If tagged, release the tag, set the relect path 
		 */
		अगर (cp->tag != NO_TAG) अणु
#अगर_घोषित SYM_OPT_LIMIT_COMMAND_REORDERING
			--lp->tags_sum[cp->tags_si];
#पूर्ण_अगर
			/*
			 *  Free the tag value.
			 */
			lp->cb_tags[lp->अगर_tag] = cp->tag;
			अगर (++lp->अगर_tag == SYM_CONF_MAX_TASK)
				lp->अगर_tag = 0;
			/*
			 *  Make the reselect path invalid, 
			 *  and uncount this CCB.
			 */
			lp->itlq_tbl[cp->tag] = cpu_to_scr(np->bad_itlq_ba);
			--lp->busy_itlq;
		पूर्ण अन्यथा अणु	/* Untagged */
			/*
			 *  Make the reselect path invalid, 
			 *  and uncount this CCB.
			 */
			lp->head.itl_task_sa = cpu_to_scr(np->bad_itl_ba);
			--lp->busy_itl;
		पूर्ण
		/*
		 *  If no JOB active, make the LUN reselect path invalid.
		 */
		अगर (lp->busy_itlq == 0 && lp->busy_itl == 0)
			lp->head.resel_sa =
				cpu_to_scr(SCRIPTB_BA(np, resel_bad_lun));
	पूर्ण

	/*
	 *  We करोnnot queue more than 1 ccb per target 
	 *  with negotiation at any समय. If this ccb was 
	 *  used क्रम negotiation, clear this info in the tcb.
	 */
	अगर (cp == tp->nego_cp)
		tp->nego_cp = शून्य;

#अगर_घोषित SYM_CONF_IARB_SUPPORT
	/*
	 *  If we just complete the last queued CCB,
	 *  clear this info that is no दीर्घer relevant.
	 */
	अगर (cp == np->last_cp)
		np->last_cp = 0;
#पूर्ण_अगर

	/*
	 *  Make this CCB available.
	 */
	cp->cmd = शून्य;
	cp->host_status = HS_IDLE;
	sym_remque(&cp->link_ccbq);
	sym_insque_head(&cp->link_ccbq, &np->मुक्त_ccbq);

#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	अगर (lp) अणु
		sym_remque(&cp->link2_ccbq);
		sym_insque_tail(&cp->link2_ccbq, &np->dummy_ccbq);
		अगर (cp->started) अणु
			अगर (cp->tag != NO_TAG)
				--lp->started_tags;
			अन्यथा
				--lp->started_no_tag;
		पूर्ण
	पूर्ण
	cp->started = 0;
#पूर्ण_अगर
पूर्ण

/*
 *  Allocate a CCB from memory and initialize its fixed part.
 */
अटल काष्ठा sym_ccb *sym_alloc_ccb(काष्ठा sym_hcb *np)
अणु
	काष्ठा sym_ccb *cp = शून्य;
	पूर्णांक hcode;

	/*
	 *  Prevent from allocating more CCBs than we can 
	 *  queue to the controller.
	 */
	अगर (np->actccbs >= SYM_CONF_MAX_START)
		वापस शून्य;

	/*
	 *  Allocate memory क्रम this CCB.
	 */
	cp = sym_सुस्मृति_dma(माप(काष्ठा sym_ccb), "CCB");
	अगर (!cp)
		जाओ out_मुक्त;

	/*
	 *  Count it.
	 */
	np->actccbs++;

	/*
	 *  Compute the bus address of this ccb.
	 */
	cp->ccb_ba = vtobus(cp);

	/*
	 *  Insert this ccb पूर्णांकo the hashed list.
	 */
	hcode = CCB_HASH_CODE(cp->ccb_ba);
	cp->link_ccbh = np->ccbh[hcode];
	np->ccbh[hcode] = cp;

	/*
	 *  Initialyze the start and restart actions.
	 */
	cp->phys.head.go.start   = cpu_to_scr(SCRIPTA_BA(np, idle));
	cp->phys.head.go.restart = cpu_to_scr(SCRIPTB_BA(np, bad_i_t_l));

 	/*
	 *  Initilialyze some other fields.
	 */
	cp->phys.smsg_ext.addr = cpu_to_scr(HCB_BA(np, msgin[2]));

	/*
	 *  Chain पूर्णांकo मुक्त ccb queue.
	 */
	sym_insque_head(&cp->link_ccbq, &np->मुक्त_ccbq);

	/*
	 *  Chain पूर्णांकo optionnal lists.
	 */
#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	sym_insque_head(&cp->link2_ccbq, &np->dummy_ccbq);
#पूर्ण_अगर
	वापस cp;
out_मुक्त:
	अगर (cp)
		sym_mमुक्त_dma(cp, माप(*cp), "CCB");
	वापस शून्य;
पूर्ण

/*
 *  Look up a CCB from a DSA value.
 */
अटल काष्ठा sym_ccb *sym_ccb_from_dsa(काष्ठा sym_hcb *np, u32 dsa)
अणु
	पूर्णांक hcode;
	काष्ठा sym_ccb *cp;

	hcode = CCB_HASH_CODE(dsa);
	cp = np->ccbh[hcode];
	जबतक (cp) अणु
		अगर (cp->ccb_ba == dsa)
			अवरोध;
		cp = cp->link_ccbh;
	पूर्ण

	वापस cp;
पूर्ण

/*
 *  Target control block initialisation.
 *  Nothing important to करो at the moment.
 */
अटल व्योम sym_init_tcb (काष्ठा sym_hcb *np, u_अक्षर tn)
अणु
#अगर 0	/*  Hmmm... this checking looks paranoid. */
	/*
	 *  Check some alignments required by the chip.
	 */	
	निश्चित (((दुरत्व(काष्ठा sym_reg, nc_sxfer) ^
		दुरत्व(काष्ठा sym_tcb, head.sval)) &3) == 0);
	निश्चित (((दुरत्व(काष्ठा sym_reg, nc_scntl3) ^
		दुरत्व(काष्ठा sym_tcb, head.wval)) &3) == 0);
#पूर्ण_अगर
पूर्ण

/*
 *  Lun control block allocation and initialization.
 */
काष्ठा sym_lcb *sym_alloc_lcb (काष्ठा sym_hcb *np, u_अक्षर tn, u_अक्षर ln)
अणु
	काष्ठा sym_tcb *tp = &np->target[tn];
	काष्ठा sym_lcb *lp = शून्य;

	/*
	 *  Initialize the target control block अगर not yet.
	 */
	sym_init_tcb (np, tn);

	/*
	 *  Allocate the LCB bus address array.
	 *  Compute the bus address of this table.
	 */
	अगर (ln && !tp->luntbl) अणु
		tp->luntbl = sym_सुस्मृति_dma(256, "LUNTBL");
		अगर (!tp->luntbl)
			जाओ fail;
		स_रखो32(tp->luntbl, cpu_to_scr(vtobus(&np->badlun_sa)), 64);
		tp->head.luntbl_sa = cpu_to_scr(vtobus(tp->luntbl));
	पूर्ण

	/*
	 *  Allocate the table of poपूर्णांकers क्रम LUN(s) > 0, अगर needed.
	 */
	अगर (ln && !tp->lunmp) अणु
		tp->lunmp = kसुस्मृति(SYM_CONF_MAX_LUN, माप(काष्ठा sym_lcb *),
				GFP_ATOMIC);
		अगर (!tp->lunmp)
			जाओ fail;
	पूर्ण

	/*
	 *  Allocate the lcb.
	 *  Make it available to the chip.
	 */
	lp = sym_सुस्मृति_dma(माप(काष्ठा sym_lcb), "LCB");
	अगर (!lp)
		जाओ fail;
	अगर (ln) अणु
		tp->lunmp[ln] = lp;
		tp->luntbl[ln] = cpu_to_scr(vtobus(lp));
	पूर्ण
	अन्यथा अणु
		tp->lun0p = lp;
		tp->head.lun0_sa = cpu_to_scr(vtobus(lp));
	पूर्ण
	tp->nlcb++;

	/*
	 *  Let the itl task poपूर्णांक to error handling.
	 */
	lp->head.itl_task_sa = cpu_to_scr(np->bad_itl_ba);

	/*
	 *  Set the reselect pattern to our शेष. :)
	 */
	lp->head.resel_sa = cpu_to_scr(SCRIPTB_BA(np, resel_bad_lun));

	/*
	 *  Set user capabilities.
	 */
	lp->user_flags = tp->usrflags & (SYM_DISC_ENABLED | SYM_TAGS_ENABLED);

#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	/*
	 *  Initialize device queueing.
	 */
	sym_que_init(&lp->रुकोing_ccbq);
	sym_que_init(&lp->started_ccbq);
	lp->started_max   = SYM_CONF_MAX_TASK;
	lp->started_limit = SYM_CONF_MAX_TASK;
#पूर्ण_अगर

fail:
	वापस lp;
पूर्ण

/*
 *  Allocate LCB resources क्रम tagged command queuing.
 */
अटल व्योम sym_alloc_lcb_tags (काष्ठा sym_hcb *np, u_अक्षर tn, u_अक्षर ln)
अणु
	काष्ठा sym_tcb *tp = &np->target[tn];
	काष्ठा sym_lcb *lp = sym_lp(tp, ln);
	पूर्णांक i;

	/*
	 *  Allocate the task table and and the tag allocation 
	 *  circular buffer. We want both or none.
	 */
	lp->itlq_tbl = sym_सुस्मृति_dma(SYM_CONF_MAX_TASK*4, "ITLQ_TBL");
	अगर (!lp->itlq_tbl)
		जाओ fail;
	lp->cb_tags = kसुस्मृति(SYM_CONF_MAX_TASK, 1, GFP_ATOMIC);
	अगर (!lp->cb_tags) अणु
		sym_mमुक्त_dma(lp->itlq_tbl, SYM_CONF_MAX_TASK*4, "ITLQ_TBL");
		lp->itlq_tbl = शून्य;
		जाओ fail;
	पूर्ण

	/*
	 *  Initialize the task table with invalid entries.
	 */
	स_रखो32(lp->itlq_tbl, cpu_to_scr(np->notask_ba), SYM_CONF_MAX_TASK);

	/*
	 *  Fill up the tag buffer with tag numbers.
	 */
	क्रम (i = 0 ; i < SYM_CONF_MAX_TASK ; i++)
		lp->cb_tags[i] = i;

	/*
	 *  Make the task table available to SCRIPTS, 
	 *  And accept tagged commands now.
	 */
	lp->head.itlq_tbl_sa = cpu_to_scr(vtobus(lp->itlq_tbl));

	वापस;
fail:
	वापस;
पूर्ण

/*
 *  Lun control block deallocation. Returns the number of valid reमुख्यing LCBs
 *  क्रम the target.
 */
पूर्णांक sym_मुक्त_lcb(काष्ठा sym_hcb *np, u_अक्षर tn, u_अक्षर ln)
अणु
	काष्ठा sym_tcb *tp = &np->target[tn];
	काष्ठा sym_lcb *lp = sym_lp(tp, ln);

	tp->nlcb--;

	अगर (ln) अणु
		अगर (!tp->nlcb) अणु
			kमुक्त(tp->lunmp);
			sym_mमुक्त_dma(tp->luntbl, 256, "LUNTBL");
			tp->lunmp = शून्य;
			tp->luntbl = शून्य;
			tp->head.luntbl_sa = cpu_to_scr(vtobus(np->badluntbl));
		पूर्ण अन्यथा अणु
			tp->luntbl[ln] = cpu_to_scr(vtobus(&np->badlun_sa));
			tp->lunmp[ln] = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		tp->lun0p = शून्य;
		tp->head.lun0_sa = cpu_to_scr(vtobus(&np->badlun_sa));
	पूर्ण

	अगर (lp->itlq_tbl) अणु
		sym_mमुक्त_dma(lp->itlq_tbl, SYM_CONF_MAX_TASK*4, "ITLQ_TBL");
		kमुक्त(lp->cb_tags);
	पूर्ण

	sym_mमुक्त_dma(lp, माप(*lp), "LCB");

	वापस tp->nlcb;
पूर्ण

/*
 *  Queue a SCSI IO to the controller.
 */
पूर्णांक sym_queue_scsiio(काष्ठा sym_hcb *np, काष्ठा scsi_cmnd *cmd, काष्ठा sym_ccb *cp)
अणु
	काष्ठा scsi_device *sdev = cmd->device;
	काष्ठा sym_tcb *tp;
	काष्ठा sym_lcb *lp;
	u_अक्षर	*msgptr;
	u_पूर्णांक   msglen;
	पूर्णांक can_disconnect;

	/*
	 *  Keep track of the IO in our CCB.
	 */
	cp->cmd = cmd;

	/*
	 *  Retrieve the target descriptor.
	 */
	tp = &np->target[cp->target];

	/*
	 *  Retrieve the lun descriptor.
	 */
	lp = sym_lp(tp, sdev->lun);

	can_disconnect = (cp->tag != NO_TAG) ||
		(lp && (lp->curr_flags & SYM_DISC_ENABLED));

	msgptr = cp->scsi_smsg;
	msglen = 0;
	msgptr[msglen++] = IDENTIFY(can_disconnect, sdev->lun);

	/*
	 *  Build the tag message अगर present.
	 */
	अगर (cp->tag != NO_TAG) अणु
		u_अक्षर order = cp->order;

		चयन(order) अणु
		हाल M_ORDERED_TAG:
			अवरोध;
		हाल M_HEAD_TAG:
			अवरोध;
		शेष:
			order = M_SIMPLE_TAG;
		पूर्ण
#अगर_घोषित SYM_OPT_LIMIT_COMMAND_REORDERING
		/*
		 *  Aव्योम too much reordering of SCSI commands.
		 *  The algorithm tries to prevent completion of any 
		 *  tagged command from being delayed against more 
		 *  than 3 बार the max number of queued commands.
		 */
		अगर (lp && lp->tags_since > 3*SYM_CONF_MAX_TAG) अणु
			lp->tags_si = !(lp->tags_si);
			अगर (lp->tags_sum[lp->tags_si]) अणु
				order = M_ORDERED_TAG;
				अगर ((DEBUG_FLAGS & DEBUG_TAGS)||sym_verbose>1) अणु
					sym_prपूर्णांक_addr(cmd,
						"ordered tag forced.\n");
				पूर्ण
			पूर्ण
			lp->tags_since = 0;
		पूर्ण
#पूर्ण_अगर
		msgptr[msglen++] = order;

		/*
		 *  For less than 128 tags, actual tags are numbered 
		 *  1,3,5,..2*MAXTAGS+1,since we may have to deal 
		 *  with devices that have problems with #TAG 0 or too 
		 *  great #TAG numbers. For more tags (up to 256), 
		 *  we use directly our tag number.
		 */
#अगर SYM_CONF_MAX_TASK > (512/4)
		msgptr[msglen++] = cp->tag;
#अन्यथा
		msgptr[msglen++] = (cp->tag << 1) + 1;
#पूर्ण_अगर
	पूर्ण

	/*
	 *  Build a negotiation message अगर needed.
	 *  (nego_status is filled by sym_prepare_nego())
	 *
	 *  Always negotiate on INQUIRY and REQUEST SENSE.
	 *
	 */
	cp->nego_status = 0;
	अगर ((tp->tgoal.check_nego ||
	     cmd->cmnd[0] == INQUIRY || cmd->cmnd[0] == REQUEST_SENSE) &&
	    !tp->nego_cp && lp) अणु
		msglen += sym_prepare_nego(np, cp, msgptr + msglen);
	पूर्ण

	/*
	 *  Startqueue
	 */
	cp->phys.head.go.start   = cpu_to_scr(SCRIPTA_BA(np, select));
	cp->phys.head.go.restart = cpu_to_scr(SCRIPTA_BA(np, resel_dsa));

	/*
	 *  select
	 */
	cp->phys.select.sel_id		= cp->target;
	cp->phys.select.sel_scntl3	= tp->head.wval;
	cp->phys.select.sel_sxfer	= tp->head.sval;
	cp->phys.select.sel_scntl4	= tp->head.uval;

	/*
	 *  message
	 */
	cp->phys.smsg.addr	= CCB_BA(cp, scsi_smsg);
	cp->phys.smsg.size	= cpu_to_scr(msglen);

	/*
	 *  status
	 */
	cp->host_xflags		= 0;
	cp->host_status		= cp->nego_status ? HS_NEGOTIATE : HS_BUSY;
	cp->ssss_status		= S_ILLEGAL;
	cp->xerr_status		= 0;
	cp->host_flags		= 0;
	cp->extra_bytes		= 0;

	/*
	 *  extreme data poपूर्णांकer.
	 *  shall be positive, so -1 is lower than lowest.:)
	 */
	cp->ext_sg  = -1;
	cp->ext_ofs = 0;

	/*
	 *  Build the CDB and DATA descriptor block 
	 *  and start the IO.
	 */
	वापस sym_setup_data_and_start(np, cmd, cp);
पूर्ण

/*
 *  Reset a SCSI target (all LUNs of this target).
 */
पूर्णांक sym_reset_scsi_target(काष्ठा sym_hcb *np, पूर्णांक target)
अणु
	काष्ठा sym_tcb *tp;

	अगर (target == np->myaddr || (u_पूर्णांक)target >= SYM_CONF_MAX_TARGET)
		वापस -1;

	tp = &np->target[target];
	tp->to_reset = 1;

	np->istat_sem = SEM;
	OUTB(np, nc_istat, SIGP|SEM);

	वापस 0;
पूर्ण

/*
 *  Abort a SCSI IO.
 */
अटल पूर्णांक sym_पात_ccb(काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp, पूर्णांक समयd_out)
अणु
	/*
	 *  Check that the IO is active.
	 */
	अगर (!cp || !cp->host_status || cp->host_status == HS_WAIT)
		वापस -1;

	/*
	 *  If a previous पात didn't succeed in समय,
	 *  perक्रमm a BUS reset.
	 */
	अगर (cp->to_पात) अणु
		sym_reset_scsi_bus(np, 1);
		वापस 0;
	पूर्ण

	/*
	 *  Mark the CCB क्रम पात and allow समय क्रम.
	 */
	cp->to_पात = समयd_out ? 2 : 1;

	/*
	 *  Tell the SCRIPTS processor to stop and synchronize with us.
	 */
	np->istat_sem = SEM;
	OUTB(np, nc_istat, SIGP|SEM);
	वापस 0;
पूर्ण

पूर्णांक sym_पात_scsiio(काष्ठा sym_hcb *np, काष्ठा scsi_cmnd *cmd, पूर्णांक समयd_out)
अणु
	काष्ठा sym_ccb *cp;
	SYM_QUEHEAD *qp;

	/*
	 *  Look up our CCB control block.
	 */
	cp = शून्य;
	FOR_EACH_QUEUED_ELEMENT(&np->busy_ccbq, qp) अणु
		काष्ठा sym_ccb *cp2 = sym_que_entry(qp, काष्ठा sym_ccb, link_ccbq);
		अगर (cp2->cmd == cmd) अणु
			cp = cp2;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस sym_पात_ccb(np, cp, समयd_out);
पूर्ण

/*
 *  Complete execution of a SCSI command with extended 
 *  error, SCSI status error, or having been स्वतः-sensed.
 *
 *  The SCRIPTS processor is not running there, so we 
 *  can safely access IO रेजिस्टरs and हटाओ JOBs from  
 *  the START queue.
 *  SCRATCHA is assumed to have been loaded with STARTPOS 
 *  beक्रमe the SCRIPTS called the C code.
 */
व्योम sym_complete_error(काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp)
अणु
	काष्ठा scsi_device *sdev;
	काष्ठा scsi_cmnd *cmd;
#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	काष्ठा sym_tcb *tp;
	काष्ठा sym_lcb *lp;
#पूर्ण_अगर
	पूर्णांक resid;
	पूर्णांक i;

	/*
	 *  Paranoid check. :)
	 */
	अगर (!cp || !cp->cmd)
		वापस;

	cmd = cp->cmd;
	sdev = cmd->device;
	अगर (DEBUG_FLAGS & (DEBUG_TINY|DEBUG_RESULT)) अणु
		dev_info(&sdev->sdev_gendev, "CCB=%p STAT=%x/%x/%x\n", cp,
			cp->host_status, cp->ssss_status, cp->host_flags);
	पूर्ण

#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	/*
	 *  Get target and lun poपूर्णांकers.
	 */
	tp = &np->target[cp->target];
	lp = sym_lp(tp, sdev->lun);
#पूर्ण_अगर

	/*
	 *  Check क्रम extended errors.
	 */
	अगर (cp->xerr_status) अणु
		अगर (sym_verbose)
			sym_prपूर्णांक_xerr(cmd, cp->xerr_status);
		अगर (cp->host_status == HS_COMPLETE)
			cp->host_status = HS_COMP_ERR;
	पूर्ण

	/*
	 *  Calculate the residual.
	 */
	resid = sym_compute_residual(np, cp);

	अगर (!SYM_SETUP_RESIDUAL_SUPPORT) अणु/* If user करोes not want residuals */
		resid  = 0;		 /* throw them away. :)		    */
		cp->sv_resid = 0;
	पूर्ण
#अगर_घोषित DEBUG_2_0_X
अगर (resid)
	म_लिखो("XXXX RESID= %d - 0x%x\n", resid, resid);
#पूर्ण_अगर

	/*
	 *  Dequeue all queued CCBs क्रम that device 
	 *  not yet started by SCRIPTS.
	 */
	i = (INL(np, nc_scratcha) - np->squeue_ba) / 4;
	i = sym_dequeue_from_squeue(np, i, cp->target, sdev->lun, -1);

	/*
	 *  Restart the SCRIPTS processor.
	 */
	OUTL_DSP(np, SCRIPTA_BA(np, start));

#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	अगर (cp->host_status == HS_COMPLETE &&
	    cp->ssss_status == S_QUEUE_FULL) अणु
		अगर (!lp || lp->started_tags - i < 2)
			जाओ weirdness;
		/*
		 *  Decrease queue depth as needed.
		 */
		lp->started_max = lp->started_tags - i - 1;
		lp->num_sgood = 0;

		अगर (sym_verbose >= 2) अणु
			sym_prपूर्णांक_addr(cmd, " queue depth is now %d\n",
					lp->started_max);
		पूर्ण

		/*
		 *  Repair the CCB.
		 */
		cp->host_status = HS_BUSY;
		cp->ssss_status = S_ILLEGAL;

		/*
		 *  Let's requeue it to device.
		 */
		sym_set_cam_status(cmd, DID_SOFT_ERROR);
		जाओ finish;
	पूर्ण
weirdness:
#पूर्ण_अगर
	/*
	 *  Build result in CAM ccb.
	 */
	sym_set_cam_result_error(np, cp, resid);

#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
finish:
#पूर्ण_अगर
	/*
	 *  Add this one to the COMP queue.
	 */
	sym_remque(&cp->link_ccbq);
	sym_insque_head(&cp->link_ccbq, &np->comp_ccbq);

	/*
	 *  Complete all those commands with either error 
	 *  or requeue condition.
	 */
	sym_flush_comp_queue(np, 0);

#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	/*
	 *  Donnot start more than 1 command after an error.
	 */
	sym_start_next_ccbs(np, lp, 1);
#पूर्ण_अगर
पूर्ण

/*
 *  Complete execution of a successful SCSI command.
 *
 *  Only successful commands go to the DONE queue, 
 *  since we need to have the SCRIPTS processor 
 *  stopped on any error condition.
 *  The SCRIPTS processor is running जबतक we are 
 *  completing successful commands.
 */
व्योम sym_complete_ok (काष्ठा sym_hcb *np, काष्ठा sym_ccb *cp)
अणु
#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	काष्ठा sym_tcb *tp;
	काष्ठा sym_lcb *lp;
#पूर्ण_अगर
	काष्ठा scsi_cmnd *cmd;
	पूर्णांक resid;

	/*
	 *  Paranoid check. :)
	 */
	अगर (!cp || !cp->cmd)
		वापस;
	निश्चित (cp->host_status == HS_COMPLETE);

	/*
	 *  Get user command.
	 */
	cmd = cp->cmd;

#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	/*
	 *  Get target and lun poपूर्णांकers.
	 */
	tp = &np->target[cp->target];
	lp = sym_lp(tp, cp->lun);
#पूर्ण_अगर

	/*
	 *  If all data have been transferred, given than no
	 *  extended error did occur, there is no residual.
	 */
	resid = 0;
	अगर (cp->phys.head.lastp != cp->goalp)
		resid = sym_compute_residual(np, cp);

	/*
	 *  Wrong transfer residuals may be worse than just always 
	 *  वापसing zero. User can disable this feature in 
	 *  sym53c8xx.h. Residual support is enabled by शेष.
	 */
	अगर (!SYM_SETUP_RESIDUAL_SUPPORT)
		resid  = 0;
#अगर_घोषित DEBUG_2_0_X
अगर (resid)
	म_लिखो("XXXX RESID= %d - 0x%x\n", resid, resid);
#पूर्ण_अगर

	/*
	 *  Build result in CAM ccb.
	 */
	sym_set_cam_result_ok(cp, cmd, resid);

#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	/*
	 *  If max number of started ccbs had been reduced,
	 *  increase it अगर 200 good status received.
	 */
	अगर (lp && lp->started_max < lp->started_limit) अणु
		++lp->num_sgood;
		अगर (lp->num_sgood >= 200) अणु
			lp->num_sgood = 0;
			++lp->started_max;
			अगर (sym_verbose >= 2) अणु
				sym_prपूर्णांक_addr(cmd, " queue depth is now %d\n",
				       lp->started_max);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 *  Free our CCB.
	 */
	sym_मुक्त_ccb (np, cp);

#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	/*
	 *  Requeue a couple of aरुकोing scsi commands.
	 */
	अगर (!sym_que_empty(&lp->रुकोing_ccbq))
		sym_start_next_ccbs(np, lp, 2);
#पूर्ण_अगर
	/*
	 *  Complete the command.
	 */
	sym_xpt_करोne(np, cmd);
पूर्ण

/*
 *  Soft-attach the controller.
 */
पूर्णांक sym_hcb_attach(काष्ठा Scsi_Host *shost, काष्ठा sym_fw *fw, काष्ठा sym_nvram *nvram)
अणु
	काष्ठा sym_hcb *np = sym_get_hcb(shost);
	पूर्णांक i;

	/*
	 *  Get some info about the firmware.
	 */
	np->scripta_sz	 = fw->a_size;
	np->scriptb_sz	 = fw->b_size;
	np->scriptz_sz	 = fw->z_size;
	np->fw_setup	 = fw->setup;
	np->fw_patch	 = fw->patch;
	np->fw_name	 = fw->name;

	/*
	 *  Save setting of some IO रेजिस्टरs, so we will 
	 *  be able to probe specअगरic implementations.
	 */
	sym_save_initial_setting (np);

	/*
	 *  Reset the chip now, since it has been reported 
	 *  that SCSI घड़ी calibration may not work properly 
	 *  अगर the chip is currently active.
	 */
	sym_chip_reset(np);

	/*
	 *  Prepare controller and devices settings, according 
	 *  to chip features, user set-up and driver set-up.
	 */
	sym_prepare_setting(shost, np, nvram);

	/*
	 *  Check the PCI घड़ी frequency.
	 *  Must be perक्रमmed after prepare_setting since it destroys 
	 *  STEST1 that is used to probe क्रम the घड़ी द्विगुनr.
	 */
	i = sym_getpciघड़ी(np);
	अगर (i > 37000 && !(np->features & FE_66MHZ))
		म_लिखो("%s: PCI BUS clock seems too high: %u KHz.\n",
			sym_name(np), i);

	/*
	 *  Allocate the start queue.
	 */
	np->squeue = sym_सुस्मृति_dma(माप(u32)*(MAX_QUEUE*2),"SQUEUE");
	अगर (!np->squeue)
		जाओ attach_failed;
	np->squeue_ba = vtobus(np->squeue);

	/*
	 *  Allocate the करोne queue.
	 */
	np->dqueue = sym_सुस्मृति_dma(माप(u32)*(MAX_QUEUE*2),"DQUEUE");
	अगर (!np->dqueue)
		जाओ attach_failed;
	np->dqueue_ba = vtobus(np->dqueue);

	/*
	 *  Allocate the target bus address array.
	 */
	np->targtbl = sym_सुस्मृति_dma(256, "TARGTBL");
	अगर (!np->targtbl)
		जाओ attach_failed;
	np->targtbl_ba = vtobus(np->targtbl);

	/*
	 *  Allocate SCRIPTS areas.
	 */
	np->scripta0 = sym_सुस्मृति_dma(np->scripta_sz, "SCRIPTA0");
	np->scriptb0 = sym_सुस्मृति_dma(np->scriptb_sz, "SCRIPTB0");
	np->scriptz0 = sym_सुस्मृति_dma(np->scriptz_sz, "SCRIPTZ0");
	अगर (!np->scripta0 || !np->scriptb0 || !np->scriptz0)
		जाओ attach_failed;

	/*
	 *  Allocate the array of lists of CCBs hashed by DSA.
	 */
	np->ccbh = kसुस्मृति(CCB_HASH_SIZE, माप(*np->ccbh), GFP_KERNEL);
	अगर (!np->ccbh)
		जाओ attach_failed;

	/*
	 *  Initialyze the CCB मुक्त and busy queues.
	 */
	sym_que_init(&np->मुक्त_ccbq);
	sym_que_init(&np->busy_ccbq);
	sym_que_init(&np->comp_ccbq);

	/*
	 *  Initialization क्रम optional handling 
	 *  of device queueing.
	 */
#अगर_घोषित SYM_OPT_HANDLE_DEVICE_QUEUEING
	sym_que_init(&np->dummy_ccbq);
#पूर्ण_अगर
	/*
	 *  Allocate some CCB. We need at least ONE.
	 */
	अगर (!sym_alloc_ccb(np))
		जाओ attach_failed;

	/*
	 *  Calculate BUS addresses where we are going 
	 *  to load the SCRIPTS.
	 */
	np->scripta_ba	= vtobus(np->scripta0);
	np->scriptb_ba	= vtobus(np->scriptb0);
	np->scriptz_ba	= vtobus(np->scriptz0);

	अगर (np->ram_ba) अणु
		np->scripta_ba = np->ram_ba;
		अगर (np->features & FE_RAM8K) अणु
			np->scriptb_ba = np->scripta_ba + 4096;
#अगर 0	/* May get useful क्रम 64 BIT PCI addressing */
			np->scr_ram_seg = cpu_to_scr(np->scripta_ba >> 32);
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	/*
	 *  Copy scripts to controller instance.
	 */
	स_नकल(np->scripta0, fw->a_base, np->scripta_sz);
	स_नकल(np->scriptb0, fw->b_base, np->scriptb_sz);
	स_नकल(np->scriptz0, fw->z_base, np->scriptz_sz);

	/*
	 *  Setup variable parts in scripts and compute
	 *  scripts bus addresses used from the C code.
	 */
	np->fw_setup(np, fw);

	/*
	 *  Bind SCRIPTS with physical addresses usable by the 
	 *  SCRIPTS processor (as seen from the BUS = BUS addresses).
	 */
	sym_fw_bind_script(np, (u32 *) np->scripta0, np->scripta_sz);
	sym_fw_bind_script(np, (u32 *) np->scriptb0, np->scriptb_sz);
	sym_fw_bind_script(np, (u32 *) np->scriptz0, np->scriptz_sz);

#अगर_घोषित SYM_CONF_IARB_SUPPORT
	/*
	 *    If user wants IARB to be set when we win arbitration 
	 *    and have other jobs, compute the max number of consecutive 
	 *    settings of IARB hपूर्णांकs beक्रमe we leave devices a chance to 
	 *    arbitrate क्रम reselection.
	 */
#अगर_घोषित	SYM_SETUP_IARB_MAX
	np->iarb_max = SYM_SETUP_IARB_MAX;
#अन्यथा
	np->iarb_max = 4;
#पूर्ण_अगर
#पूर्ण_अगर

	/*
	 *  Prepare the idle and invalid task actions.
	 */
	np->idletask.start	= cpu_to_scr(SCRIPTA_BA(np, idle));
	np->idletask.restart	= cpu_to_scr(SCRIPTB_BA(np, bad_i_t_l));
	np->idletask_ba		= vtobus(&np->idletask);

	np->notask.start	= cpu_to_scr(SCRIPTA_BA(np, idle));
	np->notask.restart	= cpu_to_scr(SCRIPTB_BA(np, bad_i_t_l));
	np->notask_ba		= vtobus(&np->notask);

	np->bad_itl.start	= cpu_to_scr(SCRIPTA_BA(np, idle));
	np->bad_itl.restart	= cpu_to_scr(SCRIPTB_BA(np, bad_i_t_l));
	np->bad_itl_ba		= vtobus(&np->bad_itl);

	np->bad_itlq.start	= cpu_to_scr(SCRIPTA_BA(np, idle));
	np->bad_itlq.restart	= cpu_to_scr(SCRIPTB_BA(np,bad_i_t_l_q));
	np->bad_itlq_ba		= vtobus(&np->bad_itlq);

	/*
	 *  Allocate and prepare the lun JUMP table that is used 
	 *  क्रम a target prior the probing of devices (bad lun table).
	 *  A निजी table will be allocated क्रम the target on the 
	 *  first INQUIRY response received.
	 */
	np->badluntbl = sym_सुस्मृति_dma(256, "BADLUNTBL");
	अगर (!np->badluntbl)
		जाओ attach_failed;

	np->badlun_sa = cpu_to_scr(SCRIPTB_BA(np, resel_bad_lun));
	स_रखो32(np->badluntbl, cpu_to_scr(vtobus(&np->badlun_sa)), 64);

	/*
	 *  Prepare the bus address array that contains the bus 
	 *  address of each target control block.
	 *  For now, assume all logical units are wrong. :)
	 */
	क्रम (i = 0 ; i < SYM_CONF_MAX_TARGET ; i++) अणु
		np->targtbl[i] = cpu_to_scr(vtobus(&np->target[i]));
		np->target[i].head.luntbl_sa =
				cpu_to_scr(vtobus(np->badluntbl));
		np->target[i].head.lun0_sa =
				cpu_to_scr(vtobus(&np->badlun_sa));
	पूर्ण

	/*
	 *  Now check the cache handling of the pci chipset.
	 */
	अगर (sym_snooptest (np)) अणु
		म_लिखो("%s: CACHE INCORRECTLY CONFIGURED.\n", sym_name(np));
		जाओ attach_failed;
	पूर्ण

	/*
	 *  Sigh! we are करोne.
	 */
	वापस 0;

attach_failed:
	वापस -ENXIO;
पूर्ण

/*
 *  Free everything that has been allocated क्रम this device.
 */
व्योम sym_hcb_मुक्त(काष्ठा sym_hcb *np)
अणु
	SYM_QUEHEAD *qp;
	काष्ठा sym_ccb *cp;
	काष्ठा sym_tcb *tp;
	पूर्णांक target;

	अगर (np->scriptz0)
		sym_mमुक्त_dma(np->scriptz0, np->scriptz_sz, "SCRIPTZ0");
	अगर (np->scriptb0)
		sym_mमुक्त_dma(np->scriptb0, np->scriptb_sz, "SCRIPTB0");
	अगर (np->scripta0)
		sym_mमुक्त_dma(np->scripta0, np->scripta_sz, "SCRIPTA0");
	अगर (np->squeue)
		sym_mमुक्त_dma(np->squeue, माप(u32)*(MAX_QUEUE*2), "SQUEUE");
	अगर (np->dqueue)
		sym_mमुक्त_dma(np->dqueue, माप(u32)*(MAX_QUEUE*2), "DQUEUE");

	अगर (np->actccbs) अणु
		जबतक ((qp = sym_remque_head(&np->मुक्त_ccbq)) != शून्य) अणु
			cp = sym_que_entry(qp, काष्ठा sym_ccb, link_ccbq);
			sym_mमुक्त_dma(cp, माप(*cp), "CCB");
		पूर्ण
	पूर्ण
	kमुक्त(np->ccbh);

	अगर (np->badluntbl)
		sym_mमुक्त_dma(np->badluntbl, 256,"BADLUNTBL");

	क्रम (target = 0; target < SYM_CONF_MAX_TARGET ; target++) अणु
		tp = &np->target[target];
		अगर (tp->luntbl)
			sym_mमुक्त_dma(tp->luntbl, 256, "LUNTBL");
#अगर SYM_CONF_MAX_LUN > 1
		kमुक्त(tp->lunmp);
#पूर्ण_अगर 
	पूर्ण
	अगर (np->targtbl)
		sym_mमुक्त_dma(np->targtbl, 256, "TARGTBL");
पूर्ण
