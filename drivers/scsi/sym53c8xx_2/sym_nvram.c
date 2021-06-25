<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device driver क्रम the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family 
 * of PCI-SCSI IO processors.
 *
 * Copyright (C) 1999-2001  Gerard Roudier <groudier@मुक्त.fr>
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

#समावेश "sym_glue.h"
#समावेश "sym_nvram.h"

#अगर_घोषित	SYM_CONF_DEBUG_NVRAM
अटल u_अक्षर Tekram_boot_delay[7] = अणु3, 5, 10, 20, 30, 60, 120पूर्ण;
#पूर्ण_अगर

/*
 *  Get host setup from NVRAM.
 */
व्योम sym_nvram_setup_host(काष्ठा Scsi_Host *shost, काष्ठा sym_hcb *np, काष्ठा sym_nvram *nvram)
अणु
	/*
	 *  Get parity checking, host ID, verbose mode 
	 *  and miscellaneous host flags from NVRAM.
	 */
	चयन (nvram->type) अणु
	हाल SYM_SYMBIOS_NVRAM:
		अगर (!(nvram->data.Symbios.flags & SYMBIOS_PARITY_ENABLE))
			np->rv_scntl0  &= ~0x0a;
		np->myaddr = nvram->data.Symमूलप्रण.सost_id & 0x0f;
		अगर (nvram->data.Symbios.flags & SYMBIOS_VERBOSE_MSGS)
			np->verbose += 1;
		अगर (nvram->data.Symbios.flags1 & SYMBIOS_SCAN_HI_LO)
			shost->reverse_ordering = 1;
		अगर (nvram->data.Symbios.flags2 & SYMBIOS_AVOID_BUS_RESET)
			np->usrflags |= SYM_AVOID_BUS_RESET;
		अवरोध;
	हाल SYM_TEKRAM_NVRAM:
		np->myaddr = nvram->data.Tekram.host_id & 0x0f;
		अवरोध;
#अगर_घोषित CONFIG_PARISC
	हाल SYM_PARISC_PDC:
		अगर (nvram->data.parisc.host_id != -1)
			np->myaddr = nvram->data.parisc.host_id;
		अगर (nvram->data.parisc.factor != -1)
			np->minsync = nvram->data.parisc.factor;
		अगर (nvram->data.parisc.width != -1)
			np->maxwide = nvram->data.parisc.width;
		चयन (nvram->data.parisc.mode) अणु
			हाल 0: np->scsi_mode = SMODE_SE; अवरोध;
			हाल 1: np->scsi_mode = SMODE_HVD; अवरोध;
			हाल 2: np->scsi_mode = SMODE_LVD; अवरोध;
			शेष: अवरोध;
		पूर्ण
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 *  Get target set-up from Symbios क्रमmat NVRAM.
 */
अटल व्योम
sym_Symbios_setup_target(काष्ठा sym_tcb *tp, पूर्णांक target, Symbios_nvram *nvram)
अणु
	Symbios_target *tn = &nvram->target[target];

	अगर (!(tn->flags & SYMBIOS_QUEUE_TAGS_ENABLED))
		tp->usrtags = 0;
	अगर (!(tn->flags & SYMBIOS_DISCONNECT_ENABLE))
		tp->usrflags &= ~SYM_DISC_ENABLED;
	अगर (!(tn->flags & SYMBIOS_SCAN_AT_BOOT_TIME))
		tp->usrflags |= SYM_SCAN_BOOT_DISABLED;
	अगर (!(tn->flags & SYMBIOS_SCAN_LUNS))
		tp->usrflags |= SYM_SCAN_LUNS_DISABLED;
	tp->usr_period = (tn->sync_period + 3) / 4;
	tp->usr_width = (tn->bus_width == 0x8) ? 0 : 1;
पूर्ण

अटल स्थिर अचिन्हित अक्षर Tekram_sync[16] = अणु
	25, 31, 37, 43, 50, 62, 75, 125, 12, 15, 18, 21, 6, 7, 9, 10
पूर्ण;

/*
 *  Get target set-up from Tekram क्रमmat NVRAM.
 */
अटल व्योम
sym_Tekram_setup_target(काष्ठा sym_tcb *tp, पूर्णांक target, Tekram_nvram *nvram)
अणु
	काष्ठा Tekram_target *tn = &nvram->target[target];

	अगर (tn->flags & TEKRAM_TAGGED_COMMANDS) अणु
		tp->usrtags = 2 << nvram->max_tags_index;
	पूर्ण

	अगर (tn->flags & TEKRAM_DISCONNECT_ENABLE)
		tp->usrflags |= SYM_DISC_ENABLED;
 
	अगर (tn->flags & TEKRAM_SYNC_NEGO)
		tp->usr_period = Tekram_sync[tn->sync_index & 0xf];
	tp->usr_width = (tn->flags & TEKRAM_WIDE_NEGO) ? 1 : 0;
पूर्ण

/*
 *  Get target setup from NVRAM.
 */
व्योम sym_nvram_setup_target(काष्ठा sym_tcb *tp, पूर्णांक target, काष्ठा sym_nvram *nvp)
अणु
	चयन (nvp->type) अणु
	हाल SYM_SYMBIOS_NVRAM:
		sym_Symbios_setup_target(tp, target, &nvp->data.Symbios);
		अवरोध;
	हाल SYM_TEKRAM_NVRAM:
		sym_Tekram_setup_target(tp, target, &nvp->data.Tekram);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित	SYM_CONF_DEBUG_NVRAM
/*
 *  Dump Symbios क्रमmat NVRAM क्रम debugging purpose.
 */
अटल व्योम sym_display_Symbios_nvram(काष्ठा sym_device *np, Symbios_nvram *nvram)
अणु
	पूर्णांक i;

	/* display Symbios nvram host data */
	म_लिखो("%s: HOST ID=%d%s%s%s%s%s%s\n",
		sym_name(np), nvram->host_id & 0x0f,
		(nvram->flags  & SYMBIOS_SCAM_ENABLE)	? " SCAM"	:"",
		(nvram->flags  & SYMBIOS_PARITY_ENABLE)	? " PARITY"	:"",
		(nvram->flags  & SYMBIOS_VERBOSE_MSGS)	? " VERBOSE"	:"", 
		(nvram->flags  & SYMBIOS_CHS_MAPPING)	? " CHS_ALT"	:"", 
		(nvram->flags2 & SYMBIOS_AVOID_BUS_RESET)?" NO_RESET"	:"",
		(nvram->flags1 & SYMBIOS_SCAN_HI_LO)	? " HI_LO"	:"");

	/* display Symbios nvram drive data */
	क्रम (i = 0 ; i < 15 ; i++) अणु
		काष्ठा Symbios_target *tn = &nvram->target[i];
		म_लिखो("%s-%d:%s%s%s%s WIDTH=%d SYNC=%d TMO=%d\n",
		sym_name(np), i,
		(tn->flags & SYMBIOS_DISCONNECT_ENABLE)	? " DISC"	: "",
		(tn->flags & SYMBIOS_SCAN_AT_BOOT_TIME)	? " SCAN_BOOT"	: "",
		(tn->flags & SYMBIOS_SCAN_LUNS)		? " SCAN_LUNS"	: "",
		(tn->flags & SYMBIOS_QUEUE_TAGS_ENABLED)? " TCQ"	: "",
		tn->bus_width,
		tn->sync_period / 4,
		tn->समयout);
	पूर्ण
पूर्ण

/*
 *  Dump TEKRAM क्रमmat NVRAM क्रम debugging purpose.
 */
अटल व्योम sym_display_Tekram_nvram(काष्ठा sym_device *np, Tekram_nvram *nvram)
अणु
	पूर्णांक i, tags, boot_delay;
	अक्षर *rem;

	/* display Tekram nvram host data */
	tags = 2 << nvram->max_tags_index;
	boot_delay = 0;
	अगर (nvram->boot_delay_index < 6)
		boot_delay = Tekram_boot_delay[nvram->boot_delay_index];
	चयन ((nvram->flags & TEKRAM_REMOVABLE_FLAGS) >> 6) अणु
	शेष:
	हाल 0:	rem = "";			अवरोध;
	हाल 1: rem = " REMOVABLE=boot device";	अवरोध;
	हाल 2: rem = " REMOVABLE=all";		अवरोध;
	पूर्ण

	म_लिखो("%s: HOST ID=%d%s%s%s%s%s%s%s%s%s BOOT DELAY=%d tags=%d\n",
		sym_name(np), nvram->host_id & 0x0f,
		(nvram->flags1 & SYMBIOS_SCAM_ENABLE)	? " SCAM"	:"",
		(nvram->flags & TEKRAM_MORE_THAN_2_DRIVES) ? " >2DRIVES":"",
		(nvram->flags & TEKRAM_DRIVES_SUP_1GB)	? " >1GB"	:"",
		(nvram->flags & TEKRAM_RESET_ON_POWER_ON) ? " RESET"	:"",
		(nvram->flags & TEKRAM_ACTIVE_NEGATION)	? " ACT_NEG"	:"",
		(nvram->flags & TEKRAM_IMMEDIATE_SEEK)	? " IMM_SEEK"	:"",
		(nvram->flags & TEKRAM_SCAN_LUNS)	? " SCAN_LUNS"	:"",
		(nvram->flags1 & TEKRAM_F2_F6_ENABLED)	? " F2_F6"	:"",
		rem, boot_delay, tags);

	/* display Tekram nvram drive data */
	क्रम (i = 0; i <= 15; i++) अणु
		पूर्णांक sync, j;
		काष्ठा Tekram_target *tn = &nvram->target[i];
		j = tn->sync_index & 0xf;
		sync = Tekram_sync[j];
		म_लिखो("%s-%d:%s%s%s%s%s%s PERIOD=%d\n",
		sym_name(np), i,
		(tn->flags & TEKRAM_PARITY_CHECK)	? " PARITY"	: "",
		(tn->flags & TEKRAM_SYNC_NEGO)		? " SYNC"	: "",
		(tn->flags & TEKRAM_DISCONNECT_ENABLE)	? " DISC"	: "",
		(tn->flags & TEKRAM_START_CMD)		? " START"	: "",
		(tn->flags & TEKRAM_TAGGED_COMMANDS)	? " TCQ"	: "",
		(tn->flags & TEKRAM_WIDE_NEGO)		? " WIDE"	: "",
		sync);
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम sym_display_Symbios_nvram(काष्ठा sym_device *np, Symbios_nvram *nvram) अणु (व्योम)np; (व्योम)nvram; पूर्ण
अटल व्योम sym_display_Tekram_nvram(काष्ठा sym_device *np, Tekram_nvram *nvram) अणु (व्योम)np; (व्योम)nvram; पूर्ण
#पूर्ण_अगर	/* SYM_CONF_DEBUG_NVRAM */


/*
 *  24C16 EEPROM पढ़ोing.
 *
 *  GPIO0 - data in/data out
 *  GPIO1 - घड़ी
 *  Symbios NVRAM wiring now also used by Tekram.
 */

#घोषणा SET_BIT 0
#घोषणा CLR_BIT 1
#घोषणा SET_CLK 2
#घोषणा CLR_CLK 3

/*
 *  Set/clear data/घड़ी bit in GPIO0
 */
अटल व्योम S24C16_set_bit(काष्ठा sym_device *np, u_अक्षर ग_लिखो_bit, u_अक्षर *gpreg, 
			  पूर्णांक bit_mode)
अणु
	udelay(5);
	चयन (bit_mode) अणु
	हाल SET_BIT:
		*gpreg |= ग_लिखो_bit;
		अवरोध;
	हाल CLR_BIT:
		*gpreg &= 0xfe;
		अवरोध;
	हाल SET_CLK:
		*gpreg |= 0x02;
		अवरोध;
	हाल CLR_CLK:
		*gpreg &= 0xfd;
		अवरोध;

	पूर्ण
	OUTB(np, nc_gpreg, *gpreg);
	INB(np, nc_mbox1);
	udelay(5);
पूर्ण

/*
 *  Send START condition to NVRAM to wake it up.
 */
अटल व्योम S24C16_start(काष्ठा sym_device *np, u_अक्षर *gpreg)
अणु
	S24C16_set_bit(np, 1, gpreg, SET_BIT);
	S24C16_set_bit(np, 0, gpreg, SET_CLK);
	S24C16_set_bit(np, 0, gpreg, CLR_BIT);
	S24C16_set_bit(np, 0, gpreg, CLR_CLK);
पूर्ण

/*
 *  Send STOP condition to NVRAM - माला_दो NVRAM to sleep... ZZzzzz!!
 */
अटल व्योम S24C16_stop(काष्ठा sym_device *np, u_अक्षर *gpreg)
अणु
	S24C16_set_bit(np, 0, gpreg, SET_CLK);
	S24C16_set_bit(np, 1, gpreg, SET_BIT);
पूर्ण

/*
 *  Read or ग_लिखो a bit to the NVRAM,
 *  पढ़ो अगर GPIO0 input अन्यथा ग_लिखो अगर GPIO0 output
 */
अटल व्योम S24C16_करो_bit(काष्ठा sym_device *np, u_अक्षर *पढ़ो_bit, u_अक्षर ग_लिखो_bit, 
			 u_अक्षर *gpreg)
अणु
	S24C16_set_bit(np, ग_लिखो_bit, gpreg, SET_BIT);
	S24C16_set_bit(np, 0, gpreg, SET_CLK);
	अगर (पढ़ो_bit)
		*पढ़ो_bit = INB(np, nc_gpreg);
	S24C16_set_bit(np, 0, gpreg, CLR_CLK);
	S24C16_set_bit(np, 0, gpreg, CLR_BIT);
पूर्ण

/*
 *  Output an ACK to the NVRAM after पढ़ोing,
 *  change GPIO0 to output and when करोne back to an input
 */
अटल व्योम S24C16_ग_लिखो_ack(काष्ठा sym_device *np, u_अक्षर ग_लिखो_bit, u_अक्षर *gpreg, 
			    u_अक्षर *gpcntl)
अणु
	OUTB(np, nc_gpcntl, *gpcntl & 0xfe);
	S24C16_करो_bit(np, शून्य, ग_लिखो_bit, gpreg);
	OUTB(np, nc_gpcntl, *gpcntl);
पूर्ण

/*
 *  Input an ACK from NVRAM after writing,
 *  change GPIO0 to input and when करोne back to an output
 */
अटल व्योम S24C16_पढ़ो_ack(काष्ठा sym_device *np, u_अक्षर *पढ़ो_bit, u_अक्षर *gpreg, 
			   u_अक्षर *gpcntl)
अणु
	OUTB(np, nc_gpcntl, *gpcntl | 0x01);
	S24C16_करो_bit(np, पढ़ो_bit, 1, gpreg);
	OUTB(np, nc_gpcntl, *gpcntl);
पूर्ण

/*
 *  WRITE a byte to the NVRAM and then get an ACK to see it was accepted OK,
 *  GPIO0 must alपढ़ोy be set as an output
 */
अटल व्योम S24C16_ग_लिखो_byte(काष्ठा sym_device *np, u_अक्षर *ack_data, u_अक्षर ग_लिखो_data, 
			     u_अक्षर *gpreg, u_अक्षर *gpcntl)
अणु
	पूर्णांक x;
	
	क्रम (x = 0; x < 8; x++)
		S24C16_करो_bit(np, शून्य, (ग_लिखो_data >> (7 - x)) & 0x01, gpreg);
		
	S24C16_पढ़ो_ack(np, ack_data, gpreg, gpcntl);
पूर्ण

/*
 *  READ a byte from the NVRAM and then send an ACK to say we have got it,
 *  GPIO0 must alपढ़ोy be set as an input
 */
अटल व्योम S24C16_पढ़ो_byte(काष्ठा sym_device *np, u_अक्षर *पढ़ो_data, u_अक्षर ack_data, 
			    u_अक्षर *gpreg, u_अक्षर *gpcntl)
अणु
	पूर्णांक x;
	u_अक्षर पढ़ो_bit;

	*पढ़ो_data = 0;
	क्रम (x = 0; x < 8; x++) अणु
		S24C16_करो_bit(np, &पढ़ो_bit, 1, gpreg);
		*पढ़ो_data |= ((पढ़ो_bit & 0x01) << (7 - x));
	पूर्ण

	S24C16_ग_लिखो_ack(np, ack_data, gpreg, gpcntl);
पूर्ण

#अगर_घोषित SYM_CONF_NVRAM_WRITE_SUPPORT
/*
 *  Write 'len' bytes starting at 'offset'.
 */
अटल पूर्णांक sym_ग_लिखो_S24C16_nvram(काष्ठा sym_device *np, पूर्णांक offset,
		u_अक्षर *data, पूर्णांक len)
अणु
	u_अक्षर	gpcntl, gpreg;
	u_अक्षर	old_gpcntl, old_gpreg;
	u_अक्षर	ack_data;
	पूर्णांक	x;

	/* save current state of GPCNTL and GPREG */
	old_gpreg	= INB(np, nc_gpreg);
	old_gpcntl	= INB(np, nc_gpcntl);
	gpcntl		= old_gpcntl & 0x1c;

	/* set up GPREG & GPCNTL to set GPIO0 and GPIO1 in to known state */
	OUTB(np, nc_gpreg,  old_gpreg);
	OUTB(np, nc_gpcntl, gpcntl);

	/* this is to set NVRAM पूर्णांकo a known state with GPIO0/1 both low */
	gpreg = old_gpreg;
	S24C16_set_bit(np, 0, &gpreg, CLR_CLK);
	S24C16_set_bit(np, 0, &gpreg, CLR_BIT);
		
	/* now set NVRAM inactive with GPIO0/1 both high */
	S24C16_stop(np, &gpreg);

	/* NVRAM has to be written in segments of 16 bytes */
	क्रम (x = 0; x < len ; x += 16) अणु
		करो अणु
			S24C16_start(np, &gpreg);
			S24C16_ग_लिखो_byte(np, &ack_data,
					  0xa0 | (((offset+x) >> 7) & 0x0e),
					  &gpreg, &gpcntl);
		पूर्ण जबतक (ack_data & 0x01);

		S24C16_ग_लिखो_byte(np, &ack_data, (offset+x) & 0xff, 
				  &gpreg, &gpcntl);

		क्रम (y = 0; y < 16; y++)
			S24C16_ग_लिखो_byte(np, &ack_data, data[x+y], 
					  &gpreg, &gpcntl);
		S24C16_stop(np, &gpreg);
	पूर्ण

	/* वापस GPIO0/1 to original states after having accessed NVRAM */
	OUTB(np, nc_gpcntl, old_gpcntl);
	OUTB(np, nc_gpreg,  old_gpreg);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* SYM_CONF_NVRAM_WRITE_SUPPORT */

/*
 *  Read 'len' bytes starting at 'offset'.
 */
अटल पूर्णांक sym_पढ़ो_S24C16_nvram(काष्ठा sym_device *np, पूर्णांक offset, u_अक्षर *data, पूर्णांक len)
अणु
	u_अक्षर	gpcntl, gpreg;
	u_अक्षर	old_gpcntl, old_gpreg;
	u_अक्षर	ack_data;
	पूर्णांक	retv = 1;
	पूर्णांक	x;

	/* save current state of GPCNTL and GPREG */
	old_gpreg	= INB(np, nc_gpreg);
	old_gpcntl	= INB(np, nc_gpcntl);
	gpcntl		= old_gpcntl & 0x1c;

	/* set up GPREG & GPCNTL to set GPIO0 and GPIO1 in to known state */
	OUTB(np, nc_gpreg,  old_gpreg);
	OUTB(np, nc_gpcntl, gpcntl);

	/* this is to set NVRAM पूर्णांकo a known state with GPIO0/1 both low */
	gpreg = old_gpreg;
	S24C16_set_bit(np, 0, &gpreg, CLR_CLK);
	S24C16_set_bit(np, 0, &gpreg, CLR_BIT);
		
	/* now set NVRAM inactive with GPIO0/1 both high */
	S24C16_stop(np, &gpreg);
	
	/* activate NVRAM */
	S24C16_start(np, &gpreg);

	/* ग_लिखो device code and अक्रमom address MSB */
	S24C16_ग_लिखो_byte(np, &ack_data,
		0xa0 | ((offset >> 7) & 0x0e), &gpreg, &gpcntl);
	अगर (ack_data & 0x01)
		जाओ out;

	/* ग_लिखो अक्रमom address LSB */
	S24C16_ग_लिखो_byte(np, &ack_data,
		offset & 0xff, &gpreg, &gpcntl);
	अगर (ack_data & 0x01)
		जाओ out;

	/* regenerate START state to set up क्रम पढ़ोing */
	S24C16_start(np, &gpreg);
	
	/* reग_लिखो device code and address MSB with पढ़ो bit set (lsb = 0x01) */
	S24C16_ग_लिखो_byte(np, &ack_data,
		0xa1 | ((offset >> 7) & 0x0e), &gpreg, &gpcntl);
	अगर (ack_data & 0x01)
		जाओ out;

	/* now set up GPIO0 क्रम inputting data */
	gpcntl |= 0x01;
	OUTB(np, nc_gpcntl, gpcntl);
		
	/* input all requested data - only part of total NVRAM */
	क्रम (x = 0; x < len; x++) 
		S24C16_पढ़ो_byte(np, &data[x], (x == (len-1)), &gpreg, &gpcntl);

	/* finally put NVRAM back in inactive mode */
	gpcntl &= 0xfe;
	OUTB(np, nc_gpcntl, gpcntl);
	S24C16_stop(np, &gpreg);
	retv = 0;
out:
	/* वापस GPIO0/1 to original states after having accessed NVRAM */
	OUTB(np, nc_gpcntl, old_gpcntl);
	OUTB(np, nc_gpreg,  old_gpreg);

	वापस retv;
पूर्ण

#अघोषित SET_BIT
#अघोषित CLR_BIT
#अघोषित SET_CLK
#अघोषित CLR_CLK

/*
 *  Try पढ़ोing Symbios NVRAM.
 *  Return 0 अगर OK.
 */
अटल पूर्णांक sym_पढ़ो_Symbios_nvram(काष्ठा sym_device *np, Symbios_nvram *nvram)
अणु
	अटल u_अक्षर Symbios_trailer[6] = अणु0xfe, 0xfe, 0, 0, 0, 0पूर्ण;
	u_अक्षर *data = (u_अक्षर *) nvram;
	पूर्णांक len  = माप(*nvram);
	u_लघु	csum;
	पूर्णांक x;

	/* probe the 24c16 and पढ़ो the SYMBIOS 24c16 area */
	अगर (sym_पढ़ो_S24C16_nvram (np, SYMBIOS_NVRAM_ADDRESS, data, len))
		वापस 1;

	/* check valid NVRAM signature, verअगरy byte count and checksum */
	अगर (nvram->type != 0 ||
	    स_भेद(nvram->trailer, Symbios_trailer, 6) ||
	    nvram->byte_count != len - 12)
		वापस 1;

	/* verअगरy checksum */
	क्रम (x = 6, csum = 0; x < len - 6; x++)
		csum += data[x];
	अगर (csum != nvram->checksum)
		वापस 1;

	वापस 0;
पूर्ण

/*
 *  93C46 EEPROM पढ़ोing.
 *
 *  GPIO0 - data in
 *  GPIO1 - data out
 *  GPIO2 - घड़ी
 *  GPIO4 - chip select
 *
 *  Used by Tekram.
 */

/*
 *  Pulse घड़ी bit in GPIO0
 */
अटल व्योम T93C46_Clk(काष्ठा sym_device *np, u_अक्षर *gpreg)
अणु
	OUTB(np, nc_gpreg, *gpreg | 0x04);
	INB(np, nc_mbox1);
	udelay(2);
	OUTB(np, nc_gpreg, *gpreg);
पूर्ण

/* 
 *  Read bit from NVRAM
 */
अटल व्योम T93C46_Read_Bit(काष्ठा sym_device *np, u_अक्षर *पढ़ो_bit, u_अक्षर *gpreg)
अणु
	udelay(2);
	T93C46_Clk(np, gpreg);
	*पढ़ो_bit = INB(np, nc_gpreg);
पूर्ण

/*
 *  Write bit to GPIO0
 */
अटल व्योम T93C46_Write_Bit(काष्ठा sym_device *np, u_अक्षर ग_लिखो_bit, u_अक्षर *gpreg)
अणु
	अगर (ग_लिखो_bit & 0x01)
		*gpreg |= 0x02;
	अन्यथा
		*gpreg &= 0xfd;
		
	*gpreg |= 0x10;
		
	OUTB(np, nc_gpreg, *gpreg);
	INB(np, nc_mbox1);
	udelay(2);

	T93C46_Clk(np, gpreg);
पूर्ण

/*
 *  Send STOP condition to NVRAM - माला_दो NVRAM to sleep... ZZZzzz!!
 */
अटल व्योम T93C46_Stop(काष्ठा sym_device *np, u_अक्षर *gpreg)
अणु
	*gpreg &= 0xef;
	OUTB(np, nc_gpreg, *gpreg);
	INB(np, nc_mbox1);
	udelay(2);

	T93C46_Clk(np, gpreg);
पूर्ण

/*
 *  Send पढ़ो command and address to NVRAM
 */
अटल व्योम T93C46_Send_Command(काष्ठा sym_device *np, u_लघु ग_लिखो_data, 
				u_अक्षर *पढ़ो_bit, u_अक्षर *gpreg)
अणु
	पूर्णांक x;

	/* send 9 bits, start bit (1), command (2), address (6)  */
	क्रम (x = 0; x < 9; x++)
		T93C46_Write_Bit(np, (u_अक्षर) (ग_लिखो_data >> (8 - x)), gpreg);

	*पढ़ो_bit = INB(np, nc_gpreg);
पूर्ण

/*
 *  READ 2 bytes from the NVRAM
 */
अटल व्योम T93C46_Read_Word(काष्ठा sym_device *np,
		अचिन्हित लघु *nvram_data, अचिन्हित अक्षर *gpreg)
अणु
	पूर्णांक x;
	u_अक्षर पढ़ो_bit;

	*nvram_data = 0;
	क्रम (x = 0; x < 16; x++) अणु
		T93C46_Read_Bit(np, &पढ़ो_bit, gpreg);

		अगर (पढ़ो_bit & 0x01)
			*nvram_data |=  (0x01 << (15 - x));
		अन्यथा
			*nvram_data &= ~(0x01 << (15 - x));
	पूर्ण
पूर्ण

/*
 *  Read Tekram NvRAM data.
 */
अटल पूर्णांक T93C46_Read_Data(काष्ठा sym_device *np, अचिन्हित लघु *data,
		पूर्णांक len, अचिन्हित अक्षर *gpreg)
अणु
	पूर्णांक x;

	क्रम (x = 0; x < len; x++)  अणु
		अचिन्हित अक्षर पढ़ो_bit;
		/* output पढ़ो command and address */
		T93C46_Send_Command(np, 0x180 | x, &पढ़ो_bit, gpreg);
		अगर (पढ़ो_bit & 0x01)
			वापस 1; /* Bad */
		T93C46_Read_Word(np, &data[x], gpreg);
		T93C46_Stop(np, gpreg);
	पूर्ण

	वापस 0;
पूर्ण

/*
 *  Try पढ़ोing 93C46 Tekram NVRAM.
 */
अटल पूर्णांक sym_पढ़ो_T93C46_nvram(काष्ठा sym_device *np, Tekram_nvram *nvram)
अणु
	u_अक्षर gpcntl, gpreg;
	u_अक्षर old_gpcntl, old_gpreg;
	पूर्णांक retv;

	/* save current state of GPCNTL and GPREG */
	old_gpreg	= INB(np, nc_gpreg);
	old_gpcntl	= INB(np, nc_gpcntl);

	/* set up GPREG & GPCNTL to set GPIO0/1/2/4 in to known state, 0 in,
	   1/2/4 out */
	gpreg = old_gpreg & 0xe9;
	OUTB(np, nc_gpreg, gpreg);
	gpcntl = (old_gpcntl & 0xe9) | 0x09;
	OUTB(np, nc_gpcntl, gpcntl);

	/* input all of NVRAM, 64 words */
	retv = T93C46_Read_Data(np, (u_लघु *) nvram,
				माप(*nvram) / माप(लघु), &gpreg);
	
	/* वापस GPIO0/1/2/4 to original states after having accessed NVRAM */
	OUTB(np, nc_gpcntl, old_gpcntl);
	OUTB(np, nc_gpreg,  old_gpreg);

	वापस retv;
पूर्ण

/*
 *  Try पढ़ोing Tekram NVRAM.
 *  Return 0 अगर OK.
 */
अटल पूर्णांक sym_पढ़ो_Tekram_nvram (काष्ठा sym_device *np, Tekram_nvram *nvram)
अणु
	u_अक्षर *data = (u_अक्षर *) nvram;
	पूर्णांक len = माप(*nvram);
	u_लघु	csum;
	पूर्णांक x;

	चयन (np->pdev->device) अणु
	हाल PCI_DEVICE_ID_NCR_53C885:
	हाल PCI_DEVICE_ID_NCR_53C895:
	हाल PCI_DEVICE_ID_NCR_53C896:
		x = sym_पढ़ो_S24C16_nvram(np, TEKRAM_24C16_NVRAM_ADDRESS,
					  data, len);
		अवरोध;
	हाल PCI_DEVICE_ID_NCR_53C875:
		x = sym_पढ़ो_S24C16_nvram(np, TEKRAM_24C16_NVRAM_ADDRESS,
					  data, len);
		अगर (!x)
			अवरोध;
		fallthrough;
	शेष:
		x = sym_पढ़ो_T93C46_nvram(np, nvram);
		अवरोध;
	पूर्ण
	अगर (x)
		वापस 1;

	/* verअगरy checksum */
	क्रम (x = 0, csum = 0; x < len - 1; x += 2)
		csum += data[x] + (data[x+1] << 8);
	अगर (csum != 0x1234)
		वापस 1;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PARISC
/*
 * Host firmware (PDC) keeps a table क्रम altering SCSI capabilities.
 * Many newer machines export one channel of 53c896 chip as SE, 50-pin HD.
 * Also used क्रम Multi-initiator SCSI clusters to set the SCSI Initiator ID.
 */
अटल पूर्णांक sym_पढ़ो_parisc_pdc(काष्ठा sym_device *np, काष्ठा pdc_initiator *pdc)
अणु
	काष्ठा hardware_path hwpath;
	get_pci_node_path(np->pdev, &hwpath);
	अगर (!pdc_get_initiator(&hwpath, pdc))
		वापस 0;

	वापस SYM_PARISC_PDC;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक sym_पढ़ो_parisc_pdc(काष्ठा sym_device *np,
					काष्ठा pdc_initiator *x)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 *  Try पढ़ोing Symbios or Tekram NVRAM
 */
पूर्णांक sym_पढ़ो_nvram(काष्ठा sym_device *np, काष्ठा sym_nvram *nvp)
अणु
	अगर (!sym_पढ़ो_Symbios_nvram(np, &nvp->data.Symbios)) अणु
		nvp->type = SYM_SYMBIOS_NVRAM;
		sym_display_Symbios_nvram(np, &nvp->data.Symbios);
	पूर्ण अन्यथा अगर (!sym_पढ़ो_Tekram_nvram(np, &nvp->data.Tekram)) अणु
		nvp->type = SYM_TEKRAM_NVRAM;
		sym_display_Tekram_nvram(np, &nvp->data.Tekram);
	पूर्ण अन्यथा अणु
		nvp->type = sym_पढ़ो_parisc_pdc(np, &nvp->data.parisc);
	पूर्ण
	वापस nvp->type;
पूर्ण

अक्षर *sym_nvram_type(काष्ठा sym_nvram *nvp)
अणु
	चयन (nvp->type) अणु
	हाल SYM_SYMBIOS_NVRAM:
		वापस "Symbios NVRAM";
	हाल SYM_TEKRAM_NVRAM:
		वापस "Tekram NVRAM";
	हाल SYM_PARISC_PDC:
		वापस "PA-RISC Firmware";
	शेष:
		वापस "No NVRAM";
	पूर्ण
पूर्ण
