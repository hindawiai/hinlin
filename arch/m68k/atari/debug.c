<शैली गुरु>
/*
 * linux/arch/m68k/atari/debug.c
 *
 * Atari debugging and serial console stuff
 *
 * Assembled of parts of क्रमmer atari/config.c 97-12-18 by Roman Hodek
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/tty.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atariपूर्णांकs.h>

/* Can be set somewhere, अगर a SCC master reset has alपढ़ोy be करोne and should
 * not be repeated; used by kgdb */
पूर्णांक atari_SCC_reset_करोne;
EXPORT_SYMBOL(atari_SCC_reset_करोne);

अटल काष्ठा console atari_console_driver = अणु
	.name	= "debug",
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
पूर्ण;


अटल अंतरभूत व्योम ata_mfp_out(अक्षर c)
अणु
	जबतक (!(st_mfp.trn_stat & 0x80))	/* रुको क्रम tx buf empty */
		barrier();
	st_mfp.usart_dta = c;
पूर्ण

अटल व्योम atari_mfp_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *str,
				    अचिन्हित पूर्णांक count)
अणु
	जबतक (count--) अणु
		अगर (*str == '\n')
			ata_mfp_out('\r');
		ata_mfp_out(*str++);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ata_scc_out(अक्षर c)
अणु
	करो अणु
		MFPDELAY();
	पूर्ण जबतक (!(atari_scc.cha_b_ctrl & 0x04)); /* रुको क्रम tx buf empty */
	MFPDELAY();
	atari_scc.cha_b_data = c;
पूर्ण

अटल व्योम atari_scc_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *str,
				    अचिन्हित पूर्णांक count)
अणु
	जबतक (count--) अणु
		अगर (*str == '\n')
			ata_scc_out('\r');
		ata_scc_out(*str++);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ata_midi_out(अक्षर c)
अणु
	जबतक (!(acia.mid_ctrl & ACIA_TDRE))	/* रुको क्रम tx buf empty */
		barrier();
	acia.mid_data = c;
पूर्ण

अटल व्योम atari_midi_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *str,
				     अचिन्हित पूर्णांक count)
अणु
	जबतक (count--) अणु
		अगर (*str == '\n')
			ata_midi_out('\r');
		ata_midi_out(*str++);
	पूर्ण
पूर्ण

अटल पूर्णांक ata_par_out(अक्षर c)
अणु
	अचिन्हित अक्षर पंचांगp;
	/* This a some-seconds समयout in हाल no prपूर्णांकer is connected */
	अचिन्हित दीर्घ i = loops_per_jअगरfy > 1 ? loops_per_jअगरfy : 10000000/HZ;

	जबतक ((st_mfp.par_dt_reg & 1) && --i) /* रुको क्रम BUSY == L */
		;
	अगर (!i)
		वापस 0;

	sound_ym.rd_data_reg_sel = 15;	/* select port B */
	sound_ym.wd_data = c;		/* put अक्षर onto port */
	sound_ym.rd_data_reg_sel = 14;	/* select port A */
	पंचांगp = sound_ym.rd_data_reg_sel;
	sound_ym.wd_data = पंचांगp & ~0x20;	/* set strobe L */
	MFPDELAY();			/* रुको a bit */
	sound_ym.wd_data = पंचांगp | 0x20;	/* set strobe H */
	वापस 1;
पूर्ण

अटल व्योम atari_par_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *str,
				    अचिन्हित पूर्णांक count)
अणु
	अटल पूर्णांक prपूर्णांकer_present = 1;

	अगर (!prपूर्णांकer_present)
		वापस;

	जबतक (count--) अणु
		अगर (*str == '\n') अणु
			अगर (!ata_par_out('\r')) अणु
				prपूर्णांकer_present = 0;
				वापस;
			पूर्ण
		पूर्ण
		अगर (!ata_par_out(*str++)) अणु
			prपूर्णांकer_present = 0;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

#अगर 0
पूर्णांक atari_mfp_console_रुको_key(काष्ठा console *co)
अणु
	जबतक (!(st_mfp.rcv_stat & 0x80))	/* रुको क्रम rx buf filled */
		barrier();
	वापस st_mfp.usart_dta;
पूर्ण

पूर्णांक atari_scc_console_रुको_key(काष्ठा console *co)
अणु
	करो अणु
		MFPDELAY();
	पूर्ण जबतक (!(atari_scc.cha_b_ctrl & 0x01)); /* रुको क्रम rx buf filled */
	MFPDELAY();
	वापस atari_scc.cha_b_data;
पूर्ण

पूर्णांक atari_midi_console_रुको_key(काष्ठा console *co)
अणु
	जबतक (!(acia.mid_ctrl & ACIA_RDRF)) /* रुको क्रम rx buf filled */
		barrier();
	वापस acia.mid_data;
पूर्ण
#पूर्ण_अगर

/*
 * The following two functions करो a quick'n'dirty initialization of the MFP or
 * SCC serial ports. They're used by the debugging पूर्णांकerface, kgdb, and the
 * serial console code.
 */
अटल व्योम __init atari_init_mfp_port(पूर्णांक cflag)
अणु
	/*
	 * समयr values क्रम 1200...115200 bps; > 38400 select 110, 134, or 150
	 * bps, resp., and work only correct अगर there's a RSVE or RSSPEED
	 */
	अटल पूर्णांक baud_table[9] = अणु 16, 11, 8, 4, 2, 1, 175, 143, 128 पूर्ण;
	पूर्णांक baud = cflag & CBAUD;
	पूर्णांक parity = (cflag & PARENB) ? ((cflag & PARODD) ? 0x04 : 0x06) : 0;
	पूर्णांक csize = ((cflag & CSIZE) == CS7) ? 0x20 : 0x00;

	अगर (cflag & CBAUDEX)
		baud += B38400;
	अगर (baud < B1200 || baud > B38400+2)
		baud = B9600;		/* use शेष 9600bps क्रम non-implemented rates */
	baud -= B1200;			/* baud_table[] starts at 1200bps */

	st_mfp.trn_stat &= ~0x01;	/* disable TX */
	st_mfp.usart_ctr = parity | csize | 0x88; /* 1:16 clk mode, 1 stop bit */
	st_mfp.tim_ct_cd &= 0x70;	/* stop समयr D */
	st_mfp.tim_dt_d = baud_table[baud];
	st_mfp.tim_ct_cd |= 0x01;	/* start समयr D, 1:4 */
	st_mfp.trn_stat |= 0x01;	/* enable TX */
पूर्ण

#घोषणा SCC_WRITE(reg, val)				\
	करो अणु						\
		atari_scc.cha_b_ctrl = (reg);		\
		MFPDELAY();				\
		atari_scc.cha_b_ctrl = (val);		\
		MFPDELAY();				\
	पूर्ण जबतक (0)

/* loops_per_jअगरfy isn't initialized yet, so we can't use udelay(). This करोes a
 * delay of ~ 60us. */
#घोषणा LONG_DELAY()					\
	करो अणु						\
		पूर्णांक i;					\
		क्रम (i = 100; i > 0; --i)		\
			MFPDELAY();			\
	पूर्ण जबतक (0)

अटल व्योम __init atari_init_scc_port(पूर्णांक cflag)
अणु
	अटल पूर्णांक clksrc_table[9] =
		/* reg 11: 0x50 = BRG, 0x00 = RTxC, 0x28 = TRxC */
		अणु 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x00, 0x00 पूर्ण;
	अटल पूर्णांक brgsrc_table[9] =
		/* reg 14: 0 = RTxC, 2 = PCLK */
		अणु 2, 2, 2, 2, 2, 2, 0, 2, 2 पूर्ण;
	अटल पूर्णांक clkmode_table[9] =
		/* reg 4: 0x40 = x16, 0x80 = x32, 0xc0 = x64 */
		अणु 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc0, 0x80 पूर्ण;
	अटल पूर्णांक भाग_प्रकारable[9] =
		/* reg12 (BRG low) */
		अणु 208, 138, 103, 50, 24, 11, 1, 0, 0 पूर्ण;

	पूर्णांक baud = cflag & CBAUD;
	पूर्णांक clksrc, clkmode, भाग, reg3, reg5;

	अगर (cflag & CBAUDEX)
		baud += B38400;
	अगर (baud < B1200 || baud > B38400+2)
		baud = B9600;		/* use शेष 9600bps क्रम non-implemented rates */
	baud -= B1200;			/* tables starts at 1200bps */

	clksrc  = clksrc_table[baud];
	clkmode = clkmode_table[baud];
	भाग     = भाग_प्रकारable[baud];
	अगर (ATARIHW_PRESENT(TT_MFP) && baud >= 6) अणु
		/* special treaपंचांगent क्रम TT, where rates >= 38400 are करोne via TRxC */
		clksrc = 0x28;		/* TRxC */
		clkmode = baud == 6 ? 0xc0 :
			  baud == 7 ? 0x80 : /* really 76800bps */
				      0x40;  /* really 153600bps */
		भाग = 0;
	पूर्ण

	reg3 = (cflag & CSIZE) == CS8 ? 0xc0 : 0x40;
	reg5 = (cflag & CSIZE) == CS8 ? 0x60 : 0x20 | 0x82 /* निश्चित DTR/RTS */;

	(व्योम)atari_scc.cha_b_ctrl;	/* reset reg poपूर्णांकer */
	SCC_WRITE(9, 0xc0);		/* reset */
	LONG_DELAY();			/* extra delay after WR9 access */
	SCC_WRITE(4, (cflag & PARENB) ? ((cflag & PARODD) ? 0x01 : 0x03)
				      : 0 | 0x04 /* 1 stopbit */ | clkmode);
	SCC_WRITE(3, reg3);
	SCC_WRITE(5, reg5);
	SCC_WRITE(9, 0);		/* no पूर्णांकerrupts */
	LONG_DELAY();			/* extra delay after WR9 access */
	SCC_WRITE(10, 0);		/* NRZ mode */
	SCC_WRITE(11, clksrc);		/* मुख्य घड़ी source */
	SCC_WRITE(12, भाग);		/* BRG value */
	SCC_WRITE(13, 0);		/* BRG high byte */
	SCC_WRITE(14, brgsrc_table[baud]);
	SCC_WRITE(14, brgsrc_table[baud] | (भाग ? 1 : 0));
	SCC_WRITE(3, reg3 | 1);
	SCC_WRITE(5, reg5 | 8);

	atari_SCC_reset_करोne = 1;
पूर्ण

अटल व्योम __init atari_init_midi_port(पूर्णांक cflag)
अणु
	पूर्णांक baud = cflag & CBAUD;
	पूर्णांक csize = ((cflag & CSIZE) == CS8) ? 0x10 : 0x00;
	/* warning 7N1 isn't possible! (instead 7O2 is used...) */
	पूर्णांक parity = (cflag & PARENB) ? ((cflag & PARODD) ? 0x0c : 0x08) : 0x04;
	पूर्णांक भाग;

	/* 4800 selects 7812.5, 115200 selects 500000, all other (incl. 9600 as
	 * शेष) the standard MIDI speed 31250. */
	अगर (cflag & CBAUDEX)
		baud += B38400;
	अगर (baud == B4800)
		भाग = ACIA_DIV64;	/* really 7812.5 bps */
	अन्यथा अगर (baud == B38400+2 /* 115200 */)
		भाग = ACIA_DIV1;	/* really 500 kbps (करोes that work??) */
	अन्यथा
		भाग = ACIA_DIV16;	/* 31250 bps, standard क्रम MIDI */

	/* RTS low, पूर्णांकs disabled */
	acia.mid_ctrl = भाग | csize | parity |
		    ((atari_चयनes & ATARI_SWITCH_MIDI) ?
		     ACIA_RHTID : ACIA_RLTID);
पूर्ण

अटल पूर्णांक __init atari_debug_setup(अक्षर *arg)
अणु
	bool रेजिस्टरed;

	अगर (!MACH_IS_ATARI)
		वापस 0;

	अगर (!म_भेद(arg, "ser"))
		/* शेषs to ser2 क्रम a Falcon and ser1 otherwise */
		arg = MACH_IS_FALCON ? "ser2" : "ser1";

	रेजिस्टरed = !!atari_console_driver.ग_लिखो;
	अगर (!म_भेद(arg, "ser1")) अणु
		/* ST-MFP Modem1 serial port */
		atari_init_mfp_port(B9600|CS8);
		atari_console_driver.ग_लिखो = atari_mfp_console_ग_लिखो;
	पूर्ण अन्यथा अगर (!म_भेद(arg, "ser2")) अणु
		/* SCC Modem2 serial port */
		atari_init_scc_port(B9600|CS8);
		atari_console_driver.ग_लिखो = atari_scc_console_ग_लिखो;
	पूर्ण अन्यथा अगर (!म_भेद(arg, "midi")) अणु
		/* MIDI port */
		atari_init_midi_port(B9600|CS8);
		atari_console_driver.ग_लिखो = atari_midi_console_ग_लिखो;
	पूर्ण अन्यथा अगर (!म_भेद(arg, "par")) अणु
		/* parallel prपूर्णांकer */
		atari_turnoff_irq(IRQ_MFP_BUSY); /* aव्योम पूर्णांकs */
		sound_ym.rd_data_reg_sel = 7;	/* select mixer control */
		sound_ym.wd_data = 0xff;	/* sound off, ports are output */
		sound_ym.rd_data_reg_sel = 15;	/* select port B */
		sound_ym.wd_data = 0;		/* no अक्षर */
		sound_ym.rd_data_reg_sel = 14;	/* select port A */
		sound_ym.wd_data = sound_ym.rd_data_reg_sel | 0x20; /* strobe H */
		atari_console_driver.ग_लिखो = atari_par_console_ग_लिखो;
	पूर्ण
	अगर (atari_console_driver.ग_लिखो && !रेजिस्टरed)
		रेजिस्टर_console(&atari_console_driver);

	वापस 0;
पूर्ण

early_param("debug", atari_debug_setup);
