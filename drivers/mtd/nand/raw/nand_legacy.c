<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2000 Steven J. Hill (sjhill@realitydiluted.com)
 *		  2002-2006 Thomas Gleixner (tglx@linutronix.de)
 *
 *  Credits:
 *	David Woodhouse क्रम adding multichip support
 *
 *	Aleph One Ltd. and Toby Churchill Ltd. क्रम supporting the
 *	rework क्रम 2K page size chips
 *
 * This file contains all legacy helpers/code that should be हटाओd
 * at some poपूर्णांक.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/nmi.h>

#समावेश "internals.h"

/**
 * nand_पढ़ो_byte - [DEFAULT] पढ़ो one byte from the chip
 * @chip: न_अंकD chip object
 *
 * Default पढ़ो function क्रम 8bit buswidth
 */
अटल uपूर्णांक8_t nand_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	वापस पढ़ोb(chip->legacy.IO_ADDR_R);
पूर्ण

/**
 * nand_पढ़ो_byte16 - [DEFAULT] पढ़ो one byte endianness aware from the chip
 * @chip: न_अंकD chip object
 *
 * Default पढ़ो function क्रम 16bit buswidth with endianness conversion.
 *
 */
अटल uपूर्णांक8_t nand_पढ़ो_byte16(काष्ठा nand_chip *chip)
अणु
	वापस (uपूर्णांक8_t) cpu_to_le16(पढ़ोw(chip->legacy.IO_ADDR_R));
पूर्ण

/**
 * nand_select_chip - [DEFAULT] control CE line
 * @chip: न_अंकD chip object
 * @chipnr: chipnumber to select, -1 क्रम deselect
 *
 * Default select function क्रम 1 chip devices.
 */
अटल व्योम nand_select_chip(काष्ठा nand_chip *chip, पूर्णांक chipnr)
अणु
	चयन (chipnr) अणु
	हाल -1:
		chip->legacy.cmd_ctrl(chip, न_अंकD_CMD_NONE,
				      0 | न_अंकD_CTRL_CHANGE);
		अवरोध;
	हाल 0:
		अवरोध;

	शेष:
		BUG();
	पूर्ण
पूर्ण

/**
 * nand_ग_लिखो_byte - [DEFAULT] ग_लिखो single byte to chip
 * @chip: न_अंकD chip object
 * @byte: value to ग_लिखो
 *
 * Default function to ग_लिखो a byte to I/O[7:0]
 */
अटल व्योम nand_ग_लिखो_byte(काष्ठा nand_chip *chip, uपूर्णांक8_t byte)
अणु
	chip->legacy.ग_लिखो_buf(chip, &byte, 1);
पूर्ण

/**
 * nand_ग_लिखो_byte16 - [DEFAULT] ग_लिखो single byte to a chip with width 16
 * @chip: न_अंकD chip object
 * @byte: value to ग_लिखो
 *
 * Default function to ग_लिखो a byte to I/O[7:0] on a 16-bit wide chip.
 */
अटल व्योम nand_ग_लिखो_byte16(काष्ठा nand_chip *chip, uपूर्णांक8_t byte)
अणु
	uपूर्णांक16_t word = byte;

	/*
	 * It's not entirely clear what should happen to I/O[15:8] when writing
	 * a byte. The ONFi spec (Revision 3.1; 2012-09-19, Section 2.16) पढ़ोs:
	 *
	 *    When the host supports a 16-bit bus width, only data is
	 *    transferred at the 16-bit width. All address and command line
	 *    transfers shall use only the lower 8-bits of the data bus. During
	 *    command transfers, the host may place any value on the upper
	 *    8-bits of the data bus. During address transfers, the host shall
	 *    set the upper 8-bits of the data bus to 00h.
	 *
	 * One user of the ग_लिखो_byte callback is nand_set_features. The
	 * four parameters are specअगरied to be written to I/O[7:0], but this is
	 * neither an address nor a command transfer. Let's assume a 0 on the
	 * upper I/O lines is OK.
	 */
	chip->legacy.ग_लिखो_buf(chip, (uपूर्णांक8_t *)&word, 2);
पूर्ण

/**
 * nand_ग_लिखो_buf - [DEFAULT] ग_लिखो buffer to chip
 * @chip: न_अंकD chip object
 * @buf: data buffer
 * @len: number of bytes to ग_लिखो
 *
 * Default ग_लिखो function क्रम 8bit buswidth.
 */
अटल व्योम nand_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	ioग_लिखो8_rep(chip->legacy.IO_ADDR_W, buf, len);
पूर्ण

/**
 * nand_पढ़ो_buf - [DEFAULT] पढ़ो chip data पूर्णांकo buffer
 * @chip: न_अंकD chip object
 * @buf: buffer to store date
 * @len: number of bytes to पढ़ो
 *
 * Default पढ़ो function क्रम 8bit buswidth.
 */
अटल व्योम nand_पढ़ो_buf(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	ioपढ़ो8_rep(chip->legacy.IO_ADDR_R, buf, len);
पूर्ण

/**
 * nand_ग_लिखो_buf16 - [DEFAULT] ग_लिखो buffer to chip
 * @chip: न_अंकD chip object
 * @buf: data buffer
 * @len: number of bytes to ग_लिखो
 *
 * Default ग_लिखो function क्रम 16bit buswidth.
 */
अटल व्योम nand_ग_लिखो_buf16(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
			     पूर्णांक len)
अणु
	u16 *p = (u16 *) buf;

	ioग_लिखो16_rep(chip->legacy.IO_ADDR_W, p, len >> 1);
पूर्ण

/**
 * nand_पढ़ो_buf16 - [DEFAULT] पढ़ो chip data पूर्णांकo buffer
 * @chip: न_अंकD chip object
 * @buf: buffer to store date
 * @len: number of bytes to पढ़ो
 *
 * Default पढ़ो function क्रम 16bit buswidth.
 */
अटल व्योम nand_पढ़ो_buf16(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	u16 *p = (u16 *) buf;

	ioपढ़ो16_rep(chip->legacy.IO_ADDR_R, p, len >> 1);
पूर्ण

/**
 * panic_nand_रुको_पढ़ोy - [GENERIC] Wait क्रम the पढ़ोy pin after commands.
 * @chip: न_अंकD chip object
 * @समयo: Timeout
 *
 * Helper function क्रम nand_रुको_पढ़ोy used when needing to रुको in पूर्णांकerrupt
 * context.
 */
अटल व्योम panic_nand_रुको_पढ़ोy(काष्ठा nand_chip *chip, अचिन्हित दीर्घ समयo)
अणु
	पूर्णांक i;

	/* Wait क्रम the device to get पढ़ोy */
	क्रम (i = 0; i < समयo; i++) अणु
		अगर (chip->legacy.dev_पढ़ोy(chip))
			अवरोध;
		touch_softlockup_watchकरोg();
		mdelay(1);
	पूर्ण
पूर्ण

/**
 * nand_रुको_पढ़ोy - [GENERIC] Wait क्रम the पढ़ोy pin after commands.
 * @chip: न_अंकD chip object
 *
 * Wait क्रम the पढ़ोy pin after a command, and warn अगर a समयout occurs.
 */
व्योम nand_रुको_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	अचिन्हित दीर्घ समयo = 400;

	अगर (mtd->oops_panic_ग_लिखो)
		वापस panic_nand_रुको_पढ़ोy(chip, समयo);

	/* Wait until command is processed or समयout occurs */
	समयo = jअगरfies + msecs_to_jअगरfies(समयo);
	करो अणु
		अगर (chip->legacy.dev_पढ़ोy(chip))
			वापस;
		cond_resched();
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयo));

	अगर (!chip->legacy.dev_पढ़ोy(chip))
		pr_warn_ratelimited("timeout while waiting for chip to become ready\n");
पूर्ण
EXPORT_SYMBOL_GPL(nand_रुको_पढ़ोy);

/**
 * nand_रुको_status_पढ़ोy - [GENERIC] Wait क्रम the पढ़ोy status after commands.
 * @chip: न_अंकD chip object
 * @समयo: Timeout in ms
 *
 * Wait क्रम status पढ़ोy (i.e. command करोne) or समयout.
 */
अटल व्योम nand_रुको_status_पढ़ोy(काष्ठा nand_chip *chip, अचिन्हित दीर्घ समयo)
अणु
	पूर्णांक ret;

	समयo = jअगरfies + msecs_to_jअगरfies(समयo);
	करो अणु
		u8 status;

		ret = nand_पढ़ो_data_op(chip, &status, माप(status), true,
					false);
		अगर (ret)
			वापस;

		अगर (status & न_अंकD_STATUS_READY)
			अवरोध;
		touch_softlockup_watchकरोg();
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयo));
पूर्ण;

/**
 * nand_command - [DEFAULT] Send command to न_अंकD device
 * @chip: न_अंकD chip object
 * @command: the command to be sent
 * @column: the column address क्रम this command, -1 अगर none
 * @page_addr: the page address क्रम this command, -1 अगर none
 *
 * Send command to न_अंकD device. This function is used क्रम small page devices
 * (512 Bytes per page).
 */
अटल व्योम nand_command(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक command,
			 पूर्णांक column, पूर्णांक page_addr)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ctrl = न_अंकD_CTRL_CLE | न_अंकD_CTRL_CHANGE;

	/* Write out the command to the device */
	अगर (command == न_अंकD_CMD_SEQIN) अणु
		पूर्णांक पढ़ोcmd;

		अगर (column >= mtd->ग_लिखोsize) अणु
			/* OOB area */
			column -= mtd->ग_लिखोsize;
			पढ़ोcmd = न_अंकD_CMD_READOOB;
		पूर्ण अन्यथा अगर (column < 256) अणु
			/* First 256 bytes --> READ0 */
			पढ़ोcmd = न_अंकD_CMD_READ0;
		पूर्ण अन्यथा अणु
			column -= 256;
			पढ़ोcmd = न_अंकD_CMD_READ1;
		पूर्ण
		chip->legacy.cmd_ctrl(chip, पढ़ोcmd, ctrl);
		ctrl &= ~न_अंकD_CTRL_CHANGE;
	पूर्ण
	अगर (command != न_अंकD_CMD_NONE)
		chip->legacy.cmd_ctrl(chip, command, ctrl);

	/* Address cycle, when necessary */
	ctrl = न_अंकD_CTRL_ALE | न_अंकD_CTRL_CHANGE;
	/* Serially input address */
	अगर (column != -1) अणु
		/* Adjust columns क्रम 16 bit buswidth */
		अगर (chip->options & न_अंकD_BUSWIDTH_16 &&
				!nand_opcode_8bits(command))
			column >>= 1;
		chip->legacy.cmd_ctrl(chip, column, ctrl);
		ctrl &= ~न_अंकD_CTRL_CHANGE;
	पूर्ण
	अगर (page_addr != -1) अणु
		chip->legacy.cmd_ctrl(chip, page_addr, ctrl);
		ctrl &= ~न_अंकD_CTRL_CHANGE;
		chip->legacy.cmd_ctrl(chip, page_addr >> 8, ctrl);
		अगर (chip->options & न_अंकD_ROW_ADDR_3)
			chip->legacy.cmd_ctrl(chip, page_addr >> 16, ctrl);
	पूर्ण
	chip->legacy.cmd_ctrl(chip, न_अंकD_CMD_NONE,
			      न_अंकD_NCE | न_अंकD_CTRL_CHANGE);

	/*
	 * Program and erase have their own busy handlers status and sequential
	 * in needs no delay
	 */
	चयन (command) अणु

	हाल न_अंकD_CMD_NONE:
	हाल न_अंकD_CMD_PAGEPROG:
	हाल न_अंकD_CMD_ERASE1:
	हाल न_अंकD_CMD_ERASE2:
	हाल न_अंकD_CMD_SEQIN:
	हाल न_अंकD_CMD_STATUS:
	हाल न_अंकD_CMD_READID:
	हाल न_अंकD_CMD_SET_FEATURES:
		वापस;

	हाल न_अंकD_CMD_RESET:
		अगर (chip->legacy.dev_पढ़ोy)
			अवरोध;
		udelay(chip->legacy.chip_delay);
		chip->legacy.cmd_ctrl(chip, न_अंकD_CMD_STATUS,
				      न_अंकD_CTRL_CLE | न_अंकD_CTRL_CHANGE);
		chip->legacy.cmd_ctrl(chip, न_अंकD_CMD_NONE,
				      न_अंकD_NCE | न_अंकD_CTRL_CHANGE);
		/* EZ-न_अंकD can take upto 250ms as per ONFi v4.0 */
		nand_रुको_status_पढ़ोy(chip, 250);
		वापस;

		/* This applies to पढ़ो commands */
	हाल न_अंकD_CMD_READ0:
		/*
		 * READ0 is someबार used to निकास GET STATUS mode. When this
		 * is the हाल no address cycles are requested, and we can use
		 * this inक्रमmation to detect that we should not रुको क्रम the
		 * device to be पढ़ोy.
		 */
		अगर (column == -1 && page_addr == -1)
			वापस;
		fallthrough;
	शेष:
		/*
		 * If we करोn't have access to the busy pin, we apply the given
		 * command delay
		 */
		अगर (!chip->legacy.dev_पढ़ोy) अणु
			udelay(chip->legacy.chip_delay);
			वापस;
		पूर्ण
	पूर्ण
	/*
	 * Apply this लघु delay always to ensure that we करो रुको tWB in
	 * any हाल on any machine.
	 */
	ndelay(100);

	nand_रुको_पढ़ोy(chip);
पूर्ण

अटल व्योम nand_ccs_delay(काष्ठा nand_chip *chip)
अणु
	स्थिर काष्ठा nand_sdr_timings *sdr =
		nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));

	/*
	 * The controller alपढ़ोy takes care of रुकोing क्रम tCCS when the RNDIN
	 * or RNDOUT command is sent, वापस directly.
	 */
	अगर (!(chip->options & न_अंकD_WAIT_TCCS))
		वापस;

	/*
	 * Wait tCCS_min अगर it is correctly defined, otherwise रुको 500ns
	 * (which should be safe क्रम all न_अंकDs).
	 */
	अगर (nand_controller_can_setup_पूर्णांकerface(chip))
		ndelay(sdr->tCCS_min / 1000);
	अन्यथा
		ndelay(500);
पूर्ण

/**
 * nand_command_lp - [DEFAULT] Send command to न_अंकD large page device
 * @chip: न_अंकD chip object
 * @command: the command to be sent
 * @column: the column address क्रम this command, -1 अगर none
 * @page_addr: the page address क्रम this command, -1 अगर none
 *
 * Send command to न_अंकD device. This is the version क्रम the new large page
 * devices. We करोn't have the separate regions as we have in the small page
 * devices. We must emulate न_अंकD_CMD_READOOB to keep the code compatible.
 */
अटल व्योम nand_command_lp(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक command,
			    पूर्णांक column, पूर्णांक page_addr)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	/* Emulate न_अंकD_CMD_READOOB */
	अगर (command == न_अंकD_CMD_READOOB) अणु
		column += mtd->ग_लिखोsize;
		command = न_अंकD_CMD_READ0;
	पूर्ण

	/* Command latch cycle */
	अगर (command != न_अंकD_CMD_NONE)
		chip->legacy.cmd_ctrl(chip, command,
				      न_अंकD_NCE | न_अंकD_CLE | न_अंकD_CTRL_CHANGE);

	अगर (column != -1 || page_addr != -1) अणु
		पूर्णांक ctrl = न_अंकD_CTRL_CHANGE | न_अंकD_NCE | न_अंकD_ALE;

		/* Serially input address */
		अगर (column != -1) अणु
			/* Adjust columns क्रम 16 bit buswidth */
			अगर (chip->options & न_अंकD_BUSWIDTH_16 &&
					!nand_opcode_8bits(command))
				column >>= 1;
			chip->legacy.cmd_ctrl(chip, column, ctrl);
			ctrl &= ~न_अंकD_CTRL_CHANGE;

			/* Only output a single addr cycle क्रम 8bits opcodes. */
			अगर (!nand_opcode_8bits(command))
				chip->legacy.cmd_ctrl(chip, column >> 8, ctrl);
		पूर्ण
		अगर (page_addr != -1) अणु
			chip->legacy.cmd_ctrl(chip, page_addr, ctrl);
			chip->legacy.cmd_ctrl(chip, page_addr >> 8,
					     न_अंकD_NCE | न_अंकD_ALE);
			अगर (chip->options & न_अंकD_ROW_ADDR_3)
				chip->legacy.cmd_ctrl(chip, page_addr >> 16,
						      न_अंकD_NCE | न_अंकD_ALE);
		पूर्ण
	पूर्ण
	chip->legacy.cmd_ctrl(chip, न_अंकD_CMD_NONE,
			      न_अंकD_NCE | न_अंकD_CTRL_CHANGE);

	/*
	 * Program and erase have their own busy handlers status, sequential
	 * in and status need no delay.
	 */
	चयन (command) अणु

	हाल न_अंकD_CMD_NONE:
	हाल न_अंकD_CMD_CACHEDPROG:
	हाल न_अंकD_CMD_PAGEPROG:
	हाल न_अंकD_CMD_ERASE1:
	हाल न_अंकD_CMD_ERASE2:
	हाल न_अंकD_CMD_SEQIN:
	हाल न_अंकD_CMD_STATUS:
	हाल न_अंकD_CMD_READID:
	हाल न_अंकD_CMD_SET_FEATURES:
		वापस;

	हाल न_अंकD_CMD_RNDIN:
		nand_ccs_delay(chip);
		वापस;

	हाल न_अंकD_CMD_RESET:
		अगर (chip->legacy.dev_पढ़ोy)
			अवरोध;
		udelay(chip->legacy.chip_delay);
		chip->legacy.cmd_ctrl(chip, न_अंकD_CMD_STATUS,
				      न_अंकD_NCE | न_अंकD_CLE | न_अंकD_CTRL_CHANGE);
		chip->legacy.cmd_ctrl(chip, न_अंकD_CMD_NONE,
				      न_अंकD_NCE | न_अंकD_CTRL_CHANGE);
		/* EZ-न_अंकD can take upto 250ms as per ONFi v4.0 */
		nand_रुको_status_पढ़ोy(chip, 250);
		वापस;

	हाल न_अंकD_CMD_RNDOUT:
		/* No पढ़ोy / busy check necessary */
		chip->legacy.cmd_ctrl(chip, न_अंकD_CMD_RNDOUTSTART,
				      न_अंकD_NCE | न_अंकD_CLE | न_अंकD_CTRL_CHANGE);
		chip->legacy.cmd_ctrl(chip, न_अंकD_CMD_NONE,
				      न_अंकD_NCE | न_अंकD_CTRL_CHANGE);

		nand_ccs_delay(chip);
		वापस;

	हाल न_अंकD_CMD_READ0:
		/*
		 * READ0 is someबार used to निकास GET STATUS mode. When this
		 * is the हाल no address cycles are requested, and we can use
		 * this inक्रमmation to detect that READSTART should not be
		 * issued.
		 */
		अगर (column == -1 && page_addr == -1)
			वापस;

		chip->legacy.cmd_ctrl(chip, न_अंकD_CMD_READSTART,
				      न_अंकD_NCE | न_अंकD_CLE | न_अंकD_CTRL_CHANGE);
		chip->legacy.cmd_ctrl(chip, न_अंकD_CMD_NONE,
				      न_अंकD_NCE | न_अंकD_CTRL_CHANGE);
		fallthrough;	/* This applies to पढ़ो commands */
	शेष:
		/*
		 * If we करोn't have access to the busy pin, we apply the given
		 * command delay.
		 */
		अगर (!chip->legacy.dev_पढ़ोy) अणु
			udelay(chip->legacy.chip_delay);
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Apply this लघु delay always to ensure that we करो रुको tWB in
	 * any हाल on any machine.
	 */
	ndelay(100);

	nand_रुको_पढ़ोy(chip);
पूर्ण

/**
 * nand_get_set_features_notsupp - set/get features stub वापसing -ENOTSUPP
 * @chip: nand chip info काष्ठाure
 * @addr: feature address.
 * @subfeature_param: the subfeature parameters, a four bytes array.
 *
 * Should be used by न_अंकD controller drivers that करो not support the SET/GET
 * FEATURES operations.
 */
पूर्णांक nand_get_set_features_notsupp(काष्ठा nand_chip *chip, पूर्णांक addr,
				  u8 *subfeature_param)
अणु
	वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL(nand_get_set_features_notsupp);

/**
 * nand_रुको - [DEFAULT] रुको until the command is करोne
 * @chip: न_अंकD chip काष्ठाure
 *
 * Wait क्रम command करोne. This applies to erase and program only.
 */
अटल पूर्णांक nand_रुको(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	अचिन्हित दीर्घ समयo = 400;
	u8 status;
	पूर्णांक ret;

	/*
	 * Apply this लघु delay always to ensure that we करो रुको tWB in any
	 * हाल on any machine.
	 */
	ndelay(100);

	ret = nand_status_op(chip, शून्य);
	अगर (ret)
		वापस ret;

	अगर (mtd->oops_panic_ग_लिखो) अणु
		panic_nand_रुको(chip, समयo);
	पूर्ण अन्यथा अणु
		समयo = jअगरfies + msecs_to_jअगरfies(समयo);
		करो अणु
			अगर (chip->legacy.dev_पढ़ोy) अणु
				अगर (chip->legacy.dev_पढ़ोy(chip))
					अवरोध;
			पूर्ण अन्यथा अणु
				ret = nand_पढ़ो_data_op(chip, &status,
							माप(status), true,
							false);
				अगर (ret)
					वापस ret;

				अगर (status & न_अंकD_STATUS_READY)
					अवरोध;
			पूर्ण
			cond_resched();
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयo));
	पूर्ण

	ret = nand_पढ़ो_data_op(chip, &status, माप(status), true, false);
	अगर (ret)
		वापस ret;

	/* This can happen अगर in हाल of समयout or buggy dev_पढ़ोy */
	WARN_ON(!(status & न_अंकD_STATUS_READY));
	वापस status;
पूर्ण

व्योम nand_legacy_set_शेषs(काष्ठा nand_chip *chip)
अणु
	अचिन्हित पूर्णांक busw = chip->options & न_अंकD_BUSWIDTH_16;

	अगर (nand_has_exec_op(chip))
		वापस;

	/* check क्रम proper chip_delay setup, set 20us अगर not */
	अगर (!chip->legacy.chip_delay)
		chip->legacy.chip_delay = 20;

	/* check, अगर a user supplied command function given */
	अगर (!chip->legacy.cmdfunc)
		chip->legacy.cmdfunc = nand_command;

	/* check, अगर a user supplied रुको function given */
	अगर (chip->legacy.रुकोfunc == शून्य)
		chip->legacy.रुकोfunc = nand_रुको;

	अगर (!chip->legacy.select_chip)
		chip->legacy.select_chip = nand_select_chip;

	/* If called twice, poपूर्णांकers that depend on busw may need to be reset */
	अगर (!chip->legacy.पढ़ो_byte || chip->legacy.पढ़ो_byte == nand_पढ़ो_byte)
		chip->legacy.पढ़ो_byte = busw ? nand_पढ़ो_byte16 : nand_पढ़ो_byte;
	अगर (!chip->legacy.ग_लिखो_buf || chip->legacy.ग_लिखो_buf == nand_ग_लिखो_buf)
		chip->legacy.ग_लिखो_buf = busw ? nand_ग_लिखो_buf16 : nand_ग_लिखो_buf;
	अगर (!chip->legacy.ग_लिखो_byte || chip->legacy.ग_लिखो_byte == nand_ग_लिखो_byte)
		chip->legacy.ग_लिखो_byte = busw ? nand_ग_लिखो_byte16 : nand_ग_लिखो_byte;
	अगर (!chip->legacy.पढ़ो_buf || chip->legacy.पढ़ो_buf == nand_पढ़ो_buf)
		chip->legacy.पढ़ो_buf = busw ? nand_पढ़ो_buf16 : nand_पढ़ो_buf;
पूर्ण

व्योम nand_legacy_adjust_cmdfunc(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	/* Do not replace user supplied command function! */
	अगर (mtd->ग_लिखोsize > 512 && chip->legacy.cmdfunc == nand_command)
		chip->legacy.cmdfunc = nand_command_lp;
पूर्ण

पूर्णांक nand_legacy_check_hooks(काष्ठा nand_chip *chip)
अणु
	/*
	 * ->legacy.cmdfunc() is legacy and will only be used अगर ->exec_op() is
	 * not populated.
	 */
	अगर (nand_has_exec_op(chip))
		वापस 0;

	/*
	 * Default functions asचिन्हित क्रम ->legacy.cmdfunc() and
	 * ->legacy.select_chip() both expect ->legacy.cmd_ctrl() to be
	 *  populated.
	 */
	अगर ((!chip->legacy.cmdfunc || !chip->legacy.select_chip) &&
	    !chip->legacy.cmd_ctrl) अणु
		pr_err("->legacy.cmd_ctrl() should be provided\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
