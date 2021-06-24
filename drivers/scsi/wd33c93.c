<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 1996 John Shअगरflett, GeoLog Consulting
 *    john@geolog.com
 *    jshअगरfle@netcom.com
 */

/*
 * Drew Eckhardt's excellent 'Generic NCR5380' sources from Linux-PC
 * provided much of the inspiration and some of the code क्रम this
 * driver. Everything I know about Amiga DMA was gleaned from careful
 * पढ़ोing of Hamish Mcकरोnald's original wd33c93 driver; in fact, I
 * borrowed shamelessly from all over that source. Thanks Hamish!
 *
 * _This_ driver is (I feel) an improvement over the old one in
 * several respects:
 *
 *    -  Target Disconnection/Reconnection  is now supported. Any
 *          प्रणाली with more than one device active on the SCSI bus
 *          will benefit from this. The driver शेषs to what I
 *          call 'adaptive disconnect' - meaning that each command
 *          is evaluated inभागidually as to whether or not it should
 *          be run with the option to disconnect/reselect (अगर the
 *          device chooses), or as a "SCSI-bus-hog".
 *
 *    -  Synchronous data transfers are now supported. Because of
 *          a few devices that choke after telling the driver that
 *          they can करो sync transfers, we करोn't स्वतःmatically use
 *          this faster protocol - it can be enabled via the command-
 *          line on a device-by-device basis.
 *
 *    -  Runसमय operating parameters can now be specअगरied through
 *       the 'amiboot' or the 'insmod' command line. For amiboot करो:
 *          "amiboot [usual stuff] wd33c93=blah,blah,blah"
 *       The शेषs should be good क्रम most people. See the comment
 *       क्रम 'setup_strings' below क्रम more details.
 *
 *    -  The old driver relied exclusively on what the Western Digital
 *          करोcs call "Combination Level 2 Commands", which are a great
 *          idea in that the CPU is relieved of a lot of पूर्णांकerrupt
 *          overhead. However, by accepting a certain (user-settable)
 *          amount of additional पूर्णांकerrupts, this driver achieves
 *          better control over the SCSI bus, and data transfers are
 *          almost as fast जबतक being much easier to define, track,
 *          and debug.
 *
 *
 * TODO:
 *       more speed. linked commands.
 *
 *
 * People with bug reports, wish-lists, complaपूर्णांकs, comments,
 * or improvements are asked to pah-leeez email me (John Shअगरflett)
 * at john@geolog.com or jshअगरfle@netcom.com! I'm anxious to get
 * this thing पूर्णांकo as good a shape as possible, and I'm positive
 * there are lots of lurking bugs and "Stupid Places".
 *
 * Updates:
 *
 * Added support क्रम pre -A chips, which करोn't have advanced features
 * and will generate CSR_RESEL rather than CSR_RESEL_AM.
 *	Riअक्षरd Hirst <riअक्षरd@sleepie.demon.co.uk>  August 2000
 *
 * Added support क्रम Burst Mode DMA and Fast SCSI. Enabled the use of
 * शेष_sx_per क्रम asynchronous data transfers. Added adjusपंचांगent
 * of transfer periods in sx_table to the actual input-घड़ी.
 *  peter fuerst <post@pfrst.de>  February 2007
 */

#समावेश <linux/module.h>

#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>

#समावेश <यंत्र/irq.h>

#समावेश "wd33c93.h"

#घोषणा optimum_sx_per(hostdata) (hostdata)->sx_table[1].period_ns


#घोषणा WD33C93_VERSION    "1.26++"
#घोषणा WD33C93_DATE       "10/Feb/2007"

MODULE_AUTHOR("John Shifflett");
MODULE_DESCRIPTION("Generic WD33C93 SCSI driver");
MODULE_LICENSE("GPL");

/*
 * 'setup_strings' is a single string used to pass operating parameters and
 * settings from the kernel/module command-line to the driver. 'setup_args[]'
 * is an array of strings that define the compile-समय शेष values क्रम
 * these settings. If Linux boots with an amiboot or insmod command-line,
 * those settings are combined with 'setup_args[]'. Note that amiboot
 * command-lines are prefixed with "wd33c93=" जबतक insmod uses a
 * "setup_strings=" prefix. The driver recognizes the following keywords
 * (lower हाल required) and arguments:
 *
 * -  nosync:biपंचांगask -biपंचांगask is a byte where the 1st 7 bits correspond with
 *                    the 7 possible SCSI devices. Set a bit to negotiate क्रम
 *                    asynchronous transfers on that device. To मुख्यtain
 *                    backwards compatibility, a command-line such as
 *                    "wd33c93=255" will be स्वतःmatically translated to
 *                    "wd33c93=nosync:0xff".
 * -  nodma:x        -x = 1 to disable DMA, x = 0 to enable it. Argument is
 *                    optional - अगर not present, same as "nodma:1".
 * -  period:ns      -ns is the minimum # of nanoseconds in a SCSI data transfer
 *                    period. Default is 500; acceptable values are 250 - 1000.
 * -  disconnect:x   -x = 0 to never allow disconnects, 2 to always allow them.
 *                    x = 1 करोes 'adaptive' disconnects, which is the शेष
 *                    and generally the best choice.
 * -  debug:x        -If 'DEBUGGING_ON' is defined, x is a bit mask that causes
 *                    various types of debug output to prपूर्णांकed - see the DB_xxx
 *                    defines in wd33c93.h
 * -  घड़ी:x        -x = घड़ी input in MHz क्रम WD33c93 chip. Normal values
 *                    would be from 8 through 20. Default is 8.
 * -  burst:x        -x = 1 to use Burst Mode (or Demand-Mode) DMA, x = 0 to use
 *                    Single Byte DMA, which is the शेष. Argument is
 *                    optional - अगर not present, same as "burst:1".
 * -  fast:x         -x = 1 to enable Fast SCSI, which is only effective with
 *                    input-घड़ी भागisor 4 (WD33C93_FS_16_20), x = 0 to disable
 *                    it, which is the शेष.  Argument is optional - अगर not
 *                    present, same as "fast:1".
 * -  next           -No argument. Used to separate blocks of keywords when
 *                    there's more than one host adapter in the प्रणाली.
 *
 * Syntax Notes:
 * -  Numeric arguments can be decimal or the '0x' क्रमm of hex notation. There
 *    _must_ be a colon between a keyword and its numeric argument, with no
 *    spaces.
 * -  Keywords are separated by commas, no spaces, in the standard kernel
 *    command-line manner.
 * -  A keyword in the 'nth' comma-separated command-line member will overग_लिखो
 *    the 'nth' element of setup_args[]. A blank command-line member (in
 *    other words, a comma with no preceding keyword) will _not_ overग_लिखो
 *    the corresponding setup_args[] element.
 * -  If a keyword is used more than once, the first one applies to the first
 *    SCSI host found, the second to the second card, etc, unless the 'next'
 *    keyword is used to change the order.
 *
 * Some amiboot examples (क्रम insmod, use 'setup_strings' instead of 'wd33c93'):
 * -  wd33c93=nosync:255
 * -  wd33c93=nodma
 * -  wd33c93=nodma:1
 * -  wd33c93=disconnect:2,nosync:0x08,period:250
 * -  wd33c93=debug:0x1c
 */

/* Normally, no शेषs are specअगरied */
अटल अक्षर *setup_args[] = अणु "", "", "", "", "", "", "", "", "", "" पूर्ण;

अटल अक्षर *setup_strings;
module_param(setup_strings, अक्षरp, 0);

अटल व्योम wd33c93_execute(काष्ठा Scsi_Host *instance);

#अगर_घोषित CONFIG_WD33C93_PIO
अटल अंतरभूत uअक्षर
पढ़ो_wd33c93(स्थिर wd33c93_regs regs, uअक्षर reg_num)
अणु
	uअक्षर data;

	outb(reg_num, regs.SASR);
	data = inb(regs.SCMD);
	वापस data;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
पढ़ो_wd33c93_count(स्थिर wd33c93_regs regs)
अणु
	अचिन्हित दीर्घ value;

	outb(WD_TRANSFER_COUNT_MSB, regs.SASR);
	value = inb(regs.SCMD) << 16;
	value |= inb(regs.SCMD) << 8;
	value |= inb(regs.SCMD);
	वापस value;
पूर्ण

अटल अंतरभूत uअक्षर
पढ़ो_aux_stat(स्थिर wd33c93_regs regs)
अणु
	वापस inb(regs.SASR);
पूर्ण

अटल अंतरभूत व्योम
ग_लिखो_wd33c93(स्थिर wd33c93_regs regs, uअक्षर reg_num, uअक्षर value)
अणु
      outb(reg_num, regs.SASR);
      outb(value, regs.SCMD);
पूर्ण

अटल अंतरभूत व्योम
ग_लिखो_wd33c93_count(स्थिर wd33c93_regs regs, अचिन्हित दीर्घ value)
अणु
	outb(WD_TRANSFER_COUNT_MSB, regs.SASR);
	outb((value >> 16) & 0xff, regs.SCMD);
	outb((value >> 8) & 0xff, regs.SCMD);
	outb( value & 0xff, regs.SCMD);
पूर्ण

#घोषणा ग_लिखो_wd33c93_cmd(regs, cmd) \
	ग_लिखो_wd33c93((regs), WD_COMMAND, (cmd))

अटल अंतरभूत व्योम
ग_लिखो_wd33c93_cdb(स्थिर wd33c93_regs regs, uपूर्णांक len, uअक्षर cmnd[])
अणु
	पूर्णांक i;

	outb(WD_CDB_1, regs.SASR);
	क्रम (i=0; i<len; i++)
		outb(cmnd[i], regs.SCMD);
पूर्ण

#अन्यथा /* CONFIG_WD33C93_PIO */
अटल अंतरभूत uअक्षर
पढ़ो_wd33c93(स्थिर wd33c93_regs regs, uअक्षर reg_num)
अणु
	*regs.SASR = reg_num;
	mb();
	वापस (*regs.SCMD);
पूर्ण

अटल अचिन्हित दीर्घ
पढ़ो_wd33c93_count(स्थिर wd33c93_regs regs)
अणु
	अचिन्हित दीर्घ value;

	*regs.SASR = WD_TRANSFER_COUNT_MSB;
	mb();
	value = *regs.SCMD << 16;
	value |= *regs.SCMD << 8;
	value |= *regs.SCMD;
	mb();
	वापस value;
पूर्ण

अटल अंतरभूत uअक्षर
पढ़ो_aux_stat(स्थिर wd33c93_regs regs)
अणु
	वापस *regs.SASR;
पूर्ण

अटल अंतरभूत व्योम
ग_लिखो_wd33c93(स्थिर wd33c93_regs regs, uअक्षर reg_num, uअक्षर value)
अणु
	*regs.SASR = reg_num;
	mb();
	*regs.SCMD = value;
	mb();
पूर्ण

अटल व्योम
ग_लिखो_wd33c93_count(स्थिर wd33c93_regs regs, अचिन्हित दीर्घ value)
अणु
	*regs.SASR = WD_TRANSFER_COUNT_MSB;
	mb();
	*regs.SCMD = value >> 16;
	*regs.SCMD = value >> 8;
	*regs.SCMD = value;
	mb();
पूर्ण

अटल अंतरभूत व्योम
ग_लिखो_wd33c93_cmd(स्थिर wd33c93_regs regs, uअक्षर cmd)
अणु
	*regs.SASR = WD_COMMAND;
	mb();
	*regs.SCMD = cmd;
	mb();
पूर्ण

अटल अंतरभूत व्योम
ग_लिखो_wd33c93_cdb(स्थिर wd33c93_regs regs, uपूर्णांक len, uअक्षर cmnd[])
अणु
	पूर्णांक i;

	*regs.SASR = WD_CDB_1;
	क्रम (i = 0; i < len; i++)
		*regs.SCMD = cmnd[i];
पूर्ण
#पूर्ण_अगर /* CONFIG_WD33C93_PIO */

अटल अंतरभूत uअक्षर
पढ़ो_1_byte(स्थिर wd33c93_regs regs)
अणु
	uअक्षर asr;
	uअक्षर x = 0;

	ग_लिखो_wd33c93(regs, WD_CONTROL, CTRL_IDI | CTRL_EDI | CTRL_POLLED);
	ग_लिखो_wd33c93_cmd(regs, WD_CMD_TRANS_INFO | 0x80);
	करो अणु
		asr = पढ़ो_aux_stat(regs);
		अगर (asr & ASR_DBR)
			x = पढ़ो_wd33c93(regs, WD_DATA);
	पूर्ण जबतक (!(asr & ASR_INT));
	वापस x;
पूर्ण

अटल पूर्णांक
round_period(अचिन्हित पूर्णांक period, स्थिर काष्ठा sx_period *sx_table)
अणु
	पूर्णांक x;

	क्रम (x = 1; sx_table[x].period_ns; x++) अणु
		अगर ((period <= sx_table[x - 0].period_ns) &&
		    (period > sx_table[x - 1].period_ns)) अणु
			वापस x;
		पूर्ण
	पूर्ण
	वापस 7;
पूर्ण

/*
 * Calculate Synchronous Transfer Register value from SDTR code.
 */
अटल uअक्षर
calc_sync_xfer(अचिन्हित पूर्णांक period, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक fast,
               स्थिर काष्ठा sx_period *sx_table)
अणु
	/* When करोing Fast SCSI synchronous data transfers, the corresponding
	 * value in 'sx_table' is two बार the actually used transfer period.
	 */
	uअक्षर result;

	अगर (offset && fast) अणु
		fast = STR_FSS;
		period *= 2;
	पूर्ण अन्यथा अणु
		fast = 0;
	पूर्ण
	period *= 4;		/* convert SDTR code to ns */
	result = sx_table[round_period(period,sx_table)].reg_value;
	result |= (offset < OPTIMUM_SX_OFF) ? offset : OPTIMUM_SX_OFF;
	result |= fast;
	वापस result;
पूर्ण

/*
 * Calculate SDTR code bytes [3],[4] from period and offset.
 */
अटल अंतरभूत व्योम
calc_sync_msg(अचिन्हित पूर्णांक period, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक fast,
                uअक्षर  msg[2])
अणु
	/* 'period' is a "normal"-mode value, like the ones in 'sx_table'. The
	 * actually used transfer period क्रम Fast SCSI synchronous data
	 * transfers is half that value.
	 */
	period /= 4;
	अगर (offset && fast)
		period /= 2;
	msg[0] = period;
	msg[1] = offset;
पूर्ण

अटल पूर्णांक
wd33c93_queuecommand_lck(काष्ठा scsi_cmnd *cmd,
		व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा WD33C93_hostdata *hostdata;
	काष्ठा scsi_cmnd *पंचांगp;

	hostdata = (काष्ठा WD33C93_hostdata *) cmd->device->host->hostdata;

	DB(DB_QUEUE_COMMAND,
	   prपूर्णांकk("Q-%d-%02x( ", cmd->device->id, cmd->cmnd[0]))

/* Set up a few fields in the scsi_cmnd काष्ठाure क्रम our own use:
 *  - host_scribble is the poपूर्णांकer to the next cmd in the input queue
 *  - scsi_करोne poपूर्णांकs to the routine we call when a cmd is finished
 *  - result is what you'd expect
 */
	cmd->host_scribble = शून्य;
	cmd->scsi_करोne = करोne;
	cmd->result = 0;

/* We use the Scsi_Poपूर्णांकer काष्ठाure that's included with each command
 * as a scratchpad (as it's पूर्णांकended to be used!). The handy thing about
 * the SCp.xxx fields is that they're always associated with a given
 * cmd, and are preserved across disconnect-reselect. This means we
 * can pretty much ignore SAVE_POINTERS and RESTORE_POINTERS messages
 * अगर we keep all the critical poपूर्णांकers and counters in SCp:
 *  - SCp.ptr is the poपूर्णांकer पूर्णांकo the RAM buffer
 *  - SCp.this_residual is the size of that buffer
 *  - SCp.buffer poपूर्णांकs to the current scatter-gather buffer
 *  - SCp.buffers_residual tells us how many S.G. buffers there are
 *  - SCp.have_data_in is not used
 *  - SCp.sent_command is not used
 *  - SCp.phase records this command's SRCID_ER bit setting
 */

	अगर (scsi_bufflen(cmd)) अणु
		cmd->SCp.buffer = scsi_sglist(cmd);
		cmd->SCp.buffers_residual = scsi_sg_count(cmd) - 1;
		cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
		cmd->SCp.this_residual = cmd->SCp.buffer->length;
	पूर्ण अन्यथा अणु
		cmd->SCp.buffer = शून्य;
		cmd->SCp.buffers_residual = 0;
		cmd->SCp.ptr = शून्य;
		cmd->SCp.this_residual = 0;
	पूर्ण

/* WD करोcs state that at the conclusion of a "LEVEL2" command, the
 * status byte can be retrieved from the LUN रेजिस्टर. Apparently,
 * this is the हाल only क्रम *unपूर्णांकerrupted* LEVEL2 commands! If
 * there are any unexpected phases entered, even अगर they are 100%
 * legal (dअगरferent devices may choose to करो things dअगरferently),
 * the LEVEL2 command sequence is निकासed. This often occurs prior
 * to receiving the status byte, in which हाल the driver करोes a
 * status phase पूर्णांकerrupt and माला_लो the status byte on its own.
 * While such a command can then be "resumed" (ie restarted to
 * finish up as a LEVEL2 command), the LUN रेजिस्टर will NOT be
 * a valid status byte at the command's conclusion, and we must
 * use the byte obtained during the earlier पूर्णांकerrupt. Here, we
 * preset SCp.Status to an illegal value (0xff) so that when
 * this command finally completes, we can tell where the actual
 * status byte is stored.
 */

	cmd->SCp.Status = ILLEGAL_STATUS_BYTE;

	/*
	 * Add the cmd to the end of 'input_Q'. Note that REQUEST SENSE
	 * commands are added to the head of the queue so that the desired
	 * sense data is not lost beक्रमe REQUEST_SENSE executes.
	 */

	spin_lock_irq(&hostdata->lock);

	अगर (!(hostdata->input_Q) || (cmd->cmnd[0] == REQUEST_SENSE)) अणु
		cmd->host_scribble = (uअक्षर *) hostdata->input_Q;
		hostdata->input_Q = cmd;
	पूर्ण अन्यथा अणु		/* find the end of the queue */
		क्रम (पंचांगp = (काष्ठा scsi_cmnd *) hostdata->input_Q;
		     पंचांगp->host_scribble;
		     पंचांगp = (काष्ठा scsi_cmnd *) पंचांगp->host_scribble) ;
		पंचांगp->host_scribble = (uअक्षर *) cmd;
	पूर्ण

/* We know that there's at least one command in 'input_Q' now.
 * Go see अगर any of them are runnable!
 */

	wd33c93_execute(cmd->device->host);

	DB(DB_QUEUE_COMMAND, prपूर्णांकk(")Q "))

	spin_unlock_irq(&hostdata->lock);
	वापस 0;
पूर्ण

DEF_SCSI_QCMD(wd33c93_queuecommand)

/*
 * This routine attempts to start a scsi command. If the host_card is
 * alपढ़ोy connected, we give up immediately. Otherwise, look through
 * the input_Q, using the first command we find that's पूर्णांकended
 * क्रम a currently non-busy target/lun.
 *
 * wd33c93_execute() is always called with पूर्णांकerrupts disabled or from
 * the wd33c93_पूर्णांकr itself, which means that a wd33c93 पूर्णांकerrupt
 * cannot occur जबतक we are in here.
 */
अटल व्योम
wd33c93_execute(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा WD33C93_hostdata *hostdata =
	    (काष्ठा WD33C93_hostdata *) instance->hostdata;
	स्थिर wd33c93_regs regs = hostdata->regs;
	काष्ठा scsi_cmnd *cmd, *prev;

	DB(DB_EXECUTE, prपूर्णांकk("EX("))
	अगर (hostdata->selecting || hostdata->connected) अणु
		DB(DB_EXECUTE, prपूर्णांकk(")EX-0 "))
		वापस;
	पूर्ण

	/*
	 * Search through the input_Q क्रम a command destined
	 * क्रम an idle target/lun.
	 */

	cmd = (काष्ठा scsi_cmnd *) hostdata->input_Q;
	prev = शून्य;
	जबतक (cmd) अणु
		अगर (!(hostdata->busy[cmd->device->id] &
		      (1 << (cmd->device->lun & 0xff))))
			अवरोध;
		prev = cmd;
		cmd = (काष्ठा scsi_cmnd *) cmd->host_scribble;
	पूर्ण

	/* quit अगर queue empty or all possible tarमाला_लो are busy */

	अगर (!cmd) अणु
		DB(DB_EXECUTE, prपूर्णांकk(")EX-1 "))
		वापस;
	पूर्ण

	/*  हटाओ command from queue */

	अगर (prev)
		prev->host_scribble = cmd->host_scribble;
	अन्यथा
		hostdata->input_Q = (काष्ठा scsi_cmnd *) cmd->host_scribble;

#अगर_घोषित PROC_STATISTICS
	hostdata->cmd_cnt[cmd->device->id]++;
#पूर्ण_अगर

	/*
	 * Start the selection process
	 */

	अगर (cmd->sc_data_direction == DMA_TO_DEVICE)
		ग_लिखो_wd33c93(regs, WD_DESTINATION_ID, cmd->device->id);
	अन्यथा
		ग_लिखो_wd33c93(regs, WD_DESTINATION_ID, cmd->device->id | DSTID_DPD);

/* Now we need to figure out whether or not this command is a good
 * candidate क्रम disconnect/reselect. We guess to the best of our
 * ability, based on a set of hierarchical rules. When several
 * devices are operating simultaneously, disconnects are usually
 * an advantage. In a single device प्रणाली, or अगर only 1 device
 * is being accessed, transfers usually go faster अगर disconnects
 * are not allowed:
 *
 * + Commands should NEVER disconnect अगर hostdata->disconnect =
 *   DIS_NEVER (this holds क्रम tape drives also), and ALWAYS
 *   disconnect अगर hostdata->disconnect = DIS_ALWAYS.
 * + Tape drive commands should always be allowed to disconnect.
 * + Disconnect should be allowed अगर disconnected_Q isn't empty.
 * + Commands should NOT disconnect अगर input_Q is empty.
 * + Disconnect should be allowed अगर there are commands in input_Q
 *   क्रम a dअगरferent target/lun. In this हाल, the other commands
 *   should be made disconnect-able, अगर not alपढ़ोy.
 *
 * I know, I know - this code would flunk me out of any
 * "C Programming 101" class ever offered. But it's easy
 * to change around and experiment with क्रम now.
 */

	cmd->SCp.phase = 0;	/* assume no disconnect */
	अगर (hostdata->disconnect == DIS_NEVER)
		जाओ no;
	अगर (hostdata->disconnect == DIS_ALWAYS)
		जाओ yes;
	अगर (cmd->device->type == 1)	/* tape drive? */
		जाओ yes;
	अगर (hostdata->disconnected_Q)	/* other commands disconnected? */
		जाओ yes;
	अगर (!(hostdata->input_Q))	/* input_Q empty? */
		जाओ no;
	क्रम (prev = (काष्ठा scsi_cmnd *) hostdata->input_Q; prev;
	     prev = (काष्ठा scsi_cmnd *) prev->host_scribble) अणु
		अगर ((prev->device->id != cmd->device->id) ||
		    (prev->device->lun != cmd->device->lun)) अणु
			क्रम (prev = (काष्ठा scsi_cmnd *) hostdata->input_Q; prev;
			     prev = (काष्ठा scsi_cmnd *) prev->host_scribble)
				prev->SCp.phase = 1;
			जाओ yes;
		पूर्ण
	पूर्ण

	जाओ no;

 yes:
	cmd->SCp.phase = 1;

#अगर_घोषित PROC_STATISTICS
	hostdata->disc_allowed_cnt[cmd->device->id]++;
#पूर्ण_अगर

 no:

	ग_लिखो_wd33c93(regs, WD_SOURCE_ID, ((cmd->SCp.phase) ? SRCID_ER : 0));

	ग_लिखो_wd33c93(regs, WD_TARGET_LUN, (u8)cmd->device->lun);
	ग_लिखो_wd33c93(regs, WD_SYNCHRONOUS_TRANSFER,
		      hostdata->sync_xfer[cmd->device->id]);
	hostdata->busy[cmd->device->id] |= (1 << (cmd->device->lun & 0xFF));

	अगर ((hostdata->level2 == L2_NONE) ||
	    (hostdata->sync_stat[cmd->device->id] == SS_UNSET)) अणु

		/*
		 * Do a 'Select-With-ATN' command. This will end with
		 * one of the following पूर्णांकerrupts:
		 *    CSR_RESEL_AM:  failure - can try again later.
		 *    CSR_TIMEOUT:   failure - give up.
		 *    CSR_SELECT:    success - proceed.
		 */

		hostdata->selecting = cmd;

/* Every target has its own synchronous transfer setting, kept in the
 * sync_xfer array, and a corresponding status byte in sync_stat[].
 * Each target's sync_stat[] entry is initialized to SX_UNSET, and its
 * sync_xfer[] entry is initialized to the शेष/safe value. SS_UNSET
 * means that the parameters are undetermined as yet, and that we
 * need to send an SDTR message to this device after selection is
 * complete: We set SS_FIRST to tell the पूर्णांकerrupt routine to करो so.
 * If we've been asked not to try synchronous transfers on this
 * target (and _all_ luns within it), we'll still send the SDTR message
 * later, but at that समय we'll negotiate क्रम async by specअगरying a
 * sync fअगरo depth of 0.
 */
		अगर (hostdata->sync_stat[cmd->device->id] == SS_UNSET)
			hostdata->sync_stat[cmd->device->id] = SS_FIRST;
		hostdata->state = S_SELECTING;
		ग_लिखो_wd33c93_count(regs, 0);	/* guarantee a DATA_PHASE पूर्णांकerrupt */
		ग_लिखो_wd33c93_cmd(regs, WD_CMD_SEL_ATN);
	पूर्ण अन्यथा अणु

		/*
		 * Do a 'Select-With-ATN-Xfer' command. This will end with
		 * one of the following पूर्णांकerrupts:
		 *    CSR_RESEL_AM:  failure - can try again later.
		 *    CSR_TIMEOUT:   failure - give up.
		 *    anything अन्यथा: success - proceed.
		 */

		hostdata->connected = cmd;
		ग_लिखो_wd33c93(regs, WD_COMMAND_PHASE, 0);

		/* copy command_descriptor_block पूर्णांकo WD chip
		 * (take advantage of स्वतः-incrementing)
		 */

		ग_लिखो_wd33c93_cdb(regs, cmd->cmd_len, cmd->cmnd);

		/* The wd33c93 only knows about Group 0, 1, and 5 commands when
		 * it's doing a 'select-and-transfer'. To be safe, we ग_लिखो the
		 * size of the CDB पूर्णांकo the OWN_ID रेजिस्टर क्रम every हाल. This
		 * way there won't be problems with venकरोr-unique, audio, etc.
		 */

		ग_लिखो_wd33c93(regs, WD_OWN_ID, cmd->cmd_len);

		/* When करोing a non-disconnect command with DMA, we can save
		 * ourselves a DATA phase पूर्णांकerrupt later by setting everything
		 * up ahead of समय.
		 */

		अगर ((cmd->SCp.phase == 0) && (hostdata->no_dma == 0)) अणु
			अगर (hostdata->dma_setup(cmd,
			    (cmd->sc_data_direction == DMA_TO_DEVICE) ?
			     DATA_OUT_सूची : DATA_IN_सूची))
				ग_लिखो_wd33c93_count(regs, 0);	/* guarantee a DATA_PHASE पूर्णांकerrupt */
			अन्यथा अणु
				ग_लिखो_wd33c93_count(regs,
						    cmd->SCp.this_residual);
				ग_लिखो_wd33c93(regs, WD_CONTROL,
					      CTRL_IDI | CTRL_EDI | hostdata->dma_mode);
				hostdata->dma = D_DMA_RUNNING;
			पूर्ण
		पूर्ण अन्यथा
			ग_लिखो_wd33c93_count(regs, 0);	/* guarantee a DATA_PHASE पूर्णांकerrupt */

		hostdata->state = S_RUNNING_LEVEL2;
		ग_लिखो_wd33c93_cmd(regs, WD_CMD_SEL_ATN_XFER);
	पूर्ण

	/*
	 * Since the SCSI bus can handle only 1 connection at a समय,
	 * we get out of here now. If the selection fails, or when
	 * the command disconnects, we'll come back to this routine
	 * to search the input_Q again...
	 */

	DB(DB_EXECUTE,
	   prपूर्णांकk("%s)EX-2 ", (cmd->SCp.phase) ? "d:" : ""))
पूर्ण

अटल व्योम
transfer_pio(स्थिर wd33c93_regs regs, uअक्षर * buf, पूर्णांक cnt,
	     पूर्णांक data_in_dir, काष्ठा WD33C93_hostdata *hostdata)
अणु
	uअक्षर asr;

	DB(DB_TRANSFER,
	   prपूर्णांकk("(%p,%d,%s:", buf, cnt, data_in_dir ? "in" : "out"))

	ग_लिखो_wd33c93(regs, WD_CONTROL, CTRL_IDI | CTRL_EDI | CTRL_POLLED);
	ग_लिखो_wd33c93_count(regs, cnt);
	ग_लिखो_wd33c93_cmd(regs, WD_CMD_TRANS_INFO);
	अगर (data_in_dir) अणु
		करो अणु
			asr = पढ़ो_aux_stat(regs);
			अगर (asr & ASR_DBR)
				*buf++ = पढ़ो_wd33c93(regs, WD_DATA);
		पूर्ण जबतक (!(asr & ASR_INT));
	पूर्ण अन्यथा अणु
		करो अणु
			asr = पढ़ो_aux_stat(regs);
			अगर (asr & ASR_DBR)
				ग_लिखो_wd33c93(regs, WD_DATA, *buf++);
		पूर्ण जबतक (!(asr & ASR_INT));
	पूर्ण

	/* Note: we are वापसing with the पूर्णांकerrupt UN-cleared.
	 * Since (presumably) an entire I/O operation has
	 * completed, the bus phase is probably dअगरferent, and
	 * the पूर्णांकerrupt routine will discover this when it
	 * responds to the uncleared पूर्णांक.
	 */

पूर्ण

अटल व्योम
transfer_bytes(स्थिर wd33c93_regs regs, काष्ठा scsi_cmnd *cmd,
		पूर्णांक data_in_dir)
अणु
	काष्ठा WD33C93_hostdata *hostdata;
	अचिन्हित दीर्घ length;

	hostdata = (काष्ठा WD33C93_hostdata *) cmd->device->host->hostdata;

/* Normally, you'd expect 'this_residual' to be non-zero here.
 * In a series of scatter-gather transfers, however, this
 * routine will usually be called with 'this_residual' equal
 * to 0 and 'buffers_residual' non-zero. This means that a
 * previous transfer completed, clearing 'this_residual', and
 * now we need to setup the next scatter-gather buffer as the
 * source or destination क्रम THIS transfer.
 */
	अगर (!cmd->SCp.this_residual && cmd->SCp.buffers_residual) अणु
		cmd->SCp.buffer = sg_next(cmd->SCp.buffer);
		--cmd->SCp.buffers_residual;
		cmd->SCp.this_residual = cmd->SCp.buffer->length;
		cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
	पूर्ण
	अगर (!cmd->SCp.this_residual) /* aव्योम bogus setups */
		वापस;

	ग_लिखो_wd33c93(regs, WD_SYNCHRONOUS_TRANSFER,
		      hostdata->sync_xfer[cmd->device->id]);

/* 'hostdata->no_dma' is TRUE if we don't even want to try DMA.
 * Update 'this_residual' and 'ptr' after 'transfer_pio()' वापसs.
 */

	अगर (hostdata->no_dma || hostdata->dma_setup(cmd, data_in_dir)) अणु
#अगर_घोषित PROC_STATISTICS
		hostdata->pio_cnt++;
#पूर्ण_अगर
		transfer_pio(regs, (uअक्षर *) cmd->SCp.ptr,
			     cmd->SCp.this_residual, data_in_dir, hostdata);
		length = cmd->SCp.this_residual;
		cmd->SCp.this_residual = पढ़ो_wd33c93_count(regs);
		cmd->SCp.ptr += (length - cmd->SCp.this_residual);
	पूर्ण

/* We are able to करो DMA (in fact, the Amiga hardware is
 * alपढ़ोy going!), so start up the wd33c93 in DMA mode.
 * We set 'hostdata->dma' = D_DMA_RUNNING so that when the
 * transfer completes and causes an पूर्णांकerrupt, we're
 * reminded to tell the Amiga to shut करोwn its end. We'll
 * postpone the updating of 'this_residual' and 'ptr'
 * until then.
 */

	अन्यथा अणु
#अगर_घोषित PROC_STATISTICS
		hostdata->dma_cnt++;
#पूर्ण_अगर
		ग_लिखो_wd33c93(regs, WD_CONTROL, CTRL_IDI | CTRL_EDI | hostdata->dma_mode);
		ग_लिखो_wd33c93_count(regs, cmd->SCp.this_residual);

		अगर ((hostdata->level2 >= L2_DATA) ||
		    (hostdata->level2 == L2_BASIC && cmd->SCp.phase == 0)) अणु
			ग_लिखो_wd33c93(regs, WD_COMMAND_PHASE, 0x45);
			ग_लिखो_wd33c93_cmd(regs, WD_CMD_SEL_ATN_XFER);
			hostdata->state = S_RUNNING_LEVEL2;
		पूर्ण अन्यथा
			ग_लिखो_wd33c93_cmd(regs, WD_CMD_TRANS_INFO);

		hostdata->dma = D_DMA_RUNNING;
	पूर्ण
पूर्ण

व्योम
wd33c93_पूर्णांकr(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा WD33C93_hostdata *hostdata =
	    (काष्ठा WD33C93_hostdata *) instance->hostdata;
	स्थिर wd33c93_regs regs = hostdata->regs;
	काष्ठा scsi_cmnd *patch, *cmd;
	uअक्षर asr, sr, phs, id, lun, *ucp, msg;
	अचिन्हित दीर्घ length, flags;

	asr = पढ़ो_aux_stat(regs);
	अगर (!(asr & ASR_INT) || (asr & ASR_BSY))
		वापस;

	spin_lock_irqsave(&hostdata->lock, flags);

#अगर_घोषित PROC_STATISTICS
	hostdata->पूर्णांक_cnt++;
#पूर्ण_अगर

	cmd = (काष्ठा scsi_cmnd *) hostdata->connected;	/* assume we're connected */
	sr = पढ़ो_wd33c93(regs, WD_SCSI_STATUS);	/* clear the पूर्णांकerrupt */
	phs = पढ़ो_wd33c93(regs, WD_COMMAND_PHASE);

	DB(DB_INTR, prपूर्णांकk("{%02x:%02x-", asr, sr))

/* After starting a DMA transfer, the next पूर्णांकerrupt
 * is guaranteed to be in response to completion of
 * the transfer. Since the Amiga DMA hardware runs in
 * in an खोलो-ended fashion, it needs to be told when
 * to stop; करो that here अगर D_DMA_RUNNING is true.
 * Also, we have to update 'this_residual' and 'ptr'
 * based on the contents of the TRANSFER_COUNT रेजिस्टर,
 * in हाल the device decided to करो an पूर्णांकermediate
 * disconnect (a device may करो this अगर it has to करो a
 * seek, or just to be nice and let other devices have
 * some bus समय during दीर्घ transfers). After करोing
 * whatever is needed, we go on and service the WD3393
 * पूर्णांकerrupt normally.
 */
	    अगर (hostdata->dma == D_DMA_RUNNING) अणु
		DB(DB_TRANSFER,
		   prपूर्णांकk("[%p/%d:", cmd->SCp.ptr, cmd->SCp.this_residual))
		    hostdata->dma_stop(cmd->device->host, cmd, 1);
		hostdata->dma = D_DMA_OFF;
		length = cmd->SCp.this_residual;
		cmd->SCp.this_residual = पढ़ो_wd33c93_count(regs);
		cmd->SCp.ptr += (length - cmd->SCp.this_residual);
		DB(DB_TRANSFER,
		   prपूर्णांकk("%p/%d]", cmd->SCp.ptr, cmd->SCp.this_residual))
	पूर्ण

/* Respond to the specअगरic WD3393 पूर्णांकerrupt - there are quite a few! */
	चयन (sr) अणु
	हाल CSR_TIMEOUT:
		DB(DB_INTR, prपूर्णांकk("TIMEOUT"))

		    अगर (hostdata->state == S_RUNNING_LEVEL2)
			hostdata->connected = शून्य;
		अन्यथा अणु
			cmd = (काष्ठा scsi_cmnd *) hostdata->selecting;	/* get a valid cmd */
			hostdata->selecting = शून्य;
		पूर्ण

		cmd->result = DID_NO_CONNECT << 16;
		hostdata->busy[cmd->device->id] &= ~(1 << (cmd->device->lun & 0xff));
		hostdata->state = S_UNCONNECTED;
		cmd->scsi_करोne(cmd);

		/* From esp.c:
		 * There is a winकरोw of समय within the scsi_करोne() path
		 * of execution where पूर्णांकerrupts are turned back on full
		 * blast and left that way.  During that समय we could
		 * reconnect to a disconnected command, then we'd bomb
		 * out below.  We could also end up executing two commands
		 * at _once_.  ...just so you know why the restore_flags()
		 * is here...
		 */

		spin_unlock_irqrestore(&hostdata->lock, flags);

/* We are not connected to a target - check to see अगर there
 * are commands रुकोing to be executed.
 */

		wd33c93_execute(instance);
		अवरोध;

/* Note: this पूर्णांकerrupt should not occur in a LEVEL2 command */

	हाल CSR_SELECT:
		DB(DB_INTR, prपूर्णांकk("SELECT"))
		    hostdata->connected = cmd =
		    (काष्ठा scsi_cmnd *) hostdata->selecting;
		hostdata->selecting = शून्य;

		/* स्थिरruct an IDENTIFY message with correct disconnect bit */

		hostdata->outgoing_msg[0] = IDENTIFY(0, cmd->device->lun);
		अगर (cmd->SCp.phase)
			hostdata->outgoing_msg[0] |= 0x40;

		अगर (hostdata->sync_stat[cmd->device->id] == SS_FIRST) अणु

			hostdata->sync_stat[cmd->device->id] = SS_WAITING;

/* Tack on a 2nd message to ask about synchronous transfers. If we've
 * been asked to करो only asynchronous transfers on this device, we
 * request a fअगरo depth of 0, which is equivalent to async - should
 * solve the problems some people have had with GVP's Guru ROM.
 */

			hostdata->outgoing_msg[1] = EXTENDED_MESSAGE;
			hostdata->outgoing_msg[2] = 3;
			hostdata->outgoing_msg[3] = EXTENDED_SDTR;
			अगर (hostdata->no_sync & (1 << cmd->device->id)) अणु
				calc_sync_msg(hostdata->शेष_sx_per, 0,
						0, hostdata->outgoing_msg + 4);
			पूर्ण अन्यथा अणु
				calc_sync_msg(optimum_sx_per(hostdata),
						OPTIMUM_SX_OFF,
						hostdata->fast,
						hostdata->outgoing_msg + 4);
			पूर्ण
			hostdata->outgoing_len = 6;
#अगर_घोषित SYNC_DEBUG
			ucp = hostdata->outgoing_msg + 1;
			prपूर्णांकk(" sending SDTR %02x03%02x%02x%02x ",
				ucp[0], ucp[2], ucp[3], ucp[4]);
#पूर्ण_अगर
		पूर्ण अन्यथा
			hostdata->outgoing_len = 1;

		hostdata->state = S_CONNECTED;
		spin_unlock_irqrestore(&hostdata->lock, flags);
		अवरोध;

	हाल CSR_XFER_DONE | PHS_DATA_IN:
	हाल CSR_UNEXP | PHS_DATA_IN:
	हाल CSR_SRV_REQ | PHS_DATA_IN:
		DB(DB_INTR,
		   prपूर्णांकk("IN-%d.%d", cmd->SCp.this_residual,
			  cmd->SCp.buffers_residual))
		    transfer_bytes(regs, cmd, DATA_IN_सूची);
		अगर (hostdata->state != S_RUNNING_LEVEL2)
			hostdata->state = S_CONNECTED;
		spin_unlock_irqrestore(&hostdata->lock, flags);
		अवरोध;

	हाल CSR_XFER_DONE | PHS_DATA_OUT:
	हाल CSR_UNEXP | PHS_DATA_OUT:
	हाल CSR_SRV_REQ | PHS_DATA_OUT:
		DB(DB_INTR,
		   prपूर्णांकk("OUT-%d.%d", cmd->SCp.this_residual,
			  cmd->SCp.buffers_residual))
		    transfer_bytes(regs, cmd, DATA_OUT_सूची);
		अगर (hostdata->state != S_RUNNING_LEVEL2)
			hostdata->state = S_CONNECTED;
		spin_unlock_irqrestore(&hostdata->lock, flags);
		अवरोध;

/* Note: this पूर्णांकerrupt should not occur in a LEVEL2 command */

	हाल CSR_XFER_DONE | PHS_COMMAND:
	हाल CSR_UNEXP | PHS_COMMAND:
	हाल CSR_SRV_REQ | PHS_COMMAND:
		DB(DB_INTR, prपूर्णांकk("CMND-%02x", cmd->cmnd[0]))
		    transfer_pio(regs, cmd->cmnd, cmd->cmd_len, DATA_OUT_सूची,
				 hostdata);
		hostdata->state = S_CONNECTED;
		spin_unlock_irqrestore(&hostdata->lock, flags);
		अवरोध;

	हाल CSR_XFER_DONE | PHS_STATUS:
	हाल CSR_UNEXP | PHS_STATUS:
	हाल CSR_SRV_REQ | PHS_STATUS:
		DB(DB_INTR, prपूर्णांकk("STATUS="))
		cmd->SCp.Status = पढ़ो_1_byte(regs);
		DB(DB_INTR, prपूर्णांकk("%02x", cmd->SCp.Status))
		    अगर (hostdata->level2 >= L2_BASIC) अणु
			sr = पढ़ो_wd33c93(regs, WD_SCSI_STATUS);	/* clear पूर्णांकerrupt */
			udelay(7);
			hostdata->state = S_RUNNING_LEVEL2;
			ग_लिखो_wd33c93(regs, WD_COMMAND_PHASE, 0x50);
			ग_लिखो_wd33c93_cmd(regs, WD_CMD_SEL_ATN_XFER);
		पूर्ण अन्यथा अणु
			hostdata->state = S_CONNECTED;
		पूर्ण
		spin_unlock_irqrestore(&hostdata->lock, flags);
		अवरोध;

	हाल CSR_XFER_DONE | PHS_MESS_IN:
	हाल CSR_UNEXP | PHS_MESS_IN:
	हाल CSR_SRV_REQ | PHS_MESS_IN:
		DB(DB_INTR, prपूर्णांकk("MSG_IN="))

		msg = पढ़ो_1_byte(regs);
		sr = पढ़ो_wd33c93(regs, WD_SCSI_STATUS);	/* clear पूर्णांकerrupt */
		udelay(7);

		hostdata->incoming_msg[hostdata->incoming_ptr] = msg;
		अगर (hostdata->incoming_msg[0] == EXTENDED_MESSAGE)
			msg = EXTENDED_MESSAGE;
		अन्यथा
			hostdata->incoming_ptr = 0;

		cmd->SCp.Message = msg;
		चयन (msg) अणु

		हाल COMMAND_COMPLETE:
			DB(DB_INTR, prपूर्णांकk("CCMP"))
			    ग_लिखो_wd33c93_cmd(regs, WD_CMD_NEGATE_ACK);
			hostdata->state = S_PRE_CMP_DISC;
			अवरोध;

		हाल SAVE_POINTERS:
			DB(DB_INTR, prपूर्णांकk("SDP"))
			    ग_लिखो_wd33c93_cmd(regs, WD_CMD_NEGATE_ACK);
			hostdata->state = S_CONNECTED;
			अवरोध;

		हाल RESTORE_POINTERS:
			DB(DB_INTR, prपूर्णांकk("RDP"))
			    अगर (hostdata->level2 >= L2_BASIC) अणु
				ग_लिखो_wd33c93(regs, WD_COMMAND_PHASE, 0x45);
				ग_लिखो_wd33c93_cmd(regs, WD_CMD_SEL_ATN_XFER);
				hostdata->state = S_RUNNING_LEVEL2;
			पूर्ण अन्यथा अणु
				ग_लिखो_wd33c93_cmd(regs, WD_CMD_NEGATE_ACK);
				hostdata->state = S_CONNECTED;
			पूर्ण
			अवरोध;

		हाल DISCONNECT:
			DB(DB_INTR, prपूर्णांकk("DIS"))
			    cmd->device->disconnect = 1;
			ग_लिखो_wd33c93_cmd(regs, WD_CMD_NEGATE_ACK);
			hostdata->state = S_PRE_TMP_DISC;
			अवरोध;

		हाल MESSAGE_REJECT:
			DB(DB_INTR, prपूर्णांकk("REJ"))
#अगर_घोषित SYNC_DEBUG
			    prपूर्णांकk("-REJ-");
#पूर्ण_अगर
			अगर (hostdata->sync_stat[cmd->device->id] == SS_WAITING) अणु
				hostdata->sync_stat[cmd->device->id] = SS_SET;
				/* we want शेष_sx_per, not DEFAULT_SX_PER */
				hostdata->sync_xfer[cmd->device->id] =
					calc_sync_xfer(hostdata->शेष_sx_per
						/ 4, 0, 0, hostdata->sx_table);
			पूर्ण
			ग_लिखो_wd33c93_cmd(regs, WD_CMD_NEGATE_ACK);
			hostdata->state = S_CONNECTED;
			अवरोध;

		हाल EXTENDED_MESSAGE:
			DB(DB_INTR, prपूर्णांकk("EXT"))

			    ucp = hostdata->incoming_msg;

#अगर_घोषित SYNC_DEBUG
			prपूर्णांकk("%02x", ucp[hostdata->incoming_ptr]);
#पूर्ण_अगर
			/* Is this the last byte of the extended message? */

			अगर ((hostdata->incoming_ptr >= 2) &&
			    (hostdata->incoming_ptr == (ucp[1] + 1))) अणु

				चयन (ucp[2]) अणु	/* what's the EXTENDED code? */
				हाल EXTENDED_SDTR:
					/* शेष to शेष async period */
					id = calc_sync_xfer(hostdata->
							शेष_sx_per / 4, 0,
							0, hostdata->sx_table);
					अगर (hostdata->sync_stat[cmd->device->id] !=
					    SS_WAITING) अणु

/* A device has sent an unsolicited SDTR message; rather than go
 * through the efक्रमt of decoding it and then figuring out what
 * our reply should be, we're just gonna say that we have a
 * synchronous fअगरo depth of 0. This will result in asynchronous
 * transfers - not ideal but so much easier.
 * Actually, this is OK because it assures us that अगर we करोn't
 * specअगरically ask क्रम sync transfers, we won't करो any.
 */

						ग_लिखो_wd33c93_cmd(regs, WD_CMD_ASSERT_ATN);	/* want MESS_OUT */
						hostdata->outgoing_msg[0] =
						    EXTENDED_MESSAGE;
						hostdata->outgoing_msg[1] = 3;
						hostdata->outgoing_msg[2] =
						    EXTENDED_SDTR;
						calc_sync_msg(hostdata->
							शेष_sx_per, 0,
							0, hostdata->outgoing_msg + 3);
						hostdata->outgoing_len = 5;
					पूर्ण अन्यथा अणु
						अगर (ucp[4]) /* well, sync transfer */
							id = calc_sync_xfer(ucp[3], ucp[4],
									hostdata->fast,
									hostdata->sx_table);
						अन्यथा अगर (ucp[3]) /* very unlikely... */
							id = calc_sync_xfer(ucp[3], ucp[4],
									0, hostdata->sx_table);
					पूर्ण
					hostdata->sync_xfer[cmd->device->id] = id;
#अगर_घोषित SYNC_DEBUG
					prपूर्णांकk(" sync_xfer=%02x\n",
					       hostdata->sync_xfer[cmd->device->id]);
#पूर्ण_अगर
					hostdata->sync_stat[cmd->device->id] =
					    SS_SET;
					ग_लिखो_wd33c93_cmd(regs,
							  WD_CMD_NEGATE_ACK);
					hostdata->state = S_CONNECTED;
					अवरोध;
				हाल EXTENDED_WDTR:
					ग_लिखो_wd33c93_cmd(regs, WD_CMD_ASSERT_ATN);	/* want MESS_OUT */
					prपूर्णांकk("sending WDTR ");
					hostdata->outgoing_msg[0] =
					    EXTENDED_MESSAGE;
					hostdata->outgoing_msg[1] = 2;
					hostdata->outgoing_msg[2] =
					    EXTENDED_WDTR;
					hostdata->outgoing_msg[3] = 0;	/* 8 bit transfer width */
					hostdata->outgoing_len = 4;
					ग_लिखो_wd33c93_cmd(regs,
							  WD_CMD_NEGATE_ACK);
					hostdata->state = S_CONNECTED;
					अवरोध;
				शेष:
					ग_लिखो_wd33c93_cmd(regs, WD_CMD_ASSERT_ATN);	/* want MESS_OUT */
					prपूर्णांकk
					    ("Rejecting Unknown Extended Message(%02x). ",
					     ucp[2]);
					hostdata->outgoing_msg[0] =
					    MESSAGE_REJECT;
					hostdata->outgoing_len = 1;
					ग_लिखो_wd33c93_cmd(regs,
							  WD_CMD_NEGATE_ACK);
					hostdata->state = S_CONNECTED;
					अवरोध;
				पूर्ण
				hostdata->incoming_ptr = 0;
			पूर्ण

			/* We need to पढ़ो more MESS_IN bytes क्रम the extended message */

			अन्यथा अणु
				hostdata->incoming_ptr++;
				ग_लिखो_wd33c93_cmd(regs, WD_CMD_NEGATE_ACK);
				hostdata->state = S_CONNECTED;
			पूर्ण
			अवरोध;

		शेष:
			prपूर्णांकk("Rejecting Unknown Message(%02x) ", msg);
			ग_लिखो_wd33c93_cmd(regs, WD_CMD_ASSERT_ATN);	/* want MESS_OUT */
			hostdata->outgoing_msg[0] = MESSAGE_REJECT;
			hostdata->outgoing_len = 1;
			ग_लिखो_wd33c93_cmd(regs, WD_CMD_NEGATE_ACK);
			hostdata->state = S_CONNECTED;
		पूर्ण
		spin_unlock_irqrestore(&hostdata->lock, flags);
		अवरोध;

/* Note: this पूर्णांकerrupt will occur only after a LEVEL2 command */

	हाल CSR_SEL_XFER_DONE:

/* Make sure that reselection is enabled at this poपूर्णांक - it may
 * have been turned off क्रम the command that just completed.
 */

		ग_लिखो_wd33c93(regs, WD_SOURCE_ID, SRCID_ER);
		अगर (phs == 0x60) अणु
			DB(DB_INTR, prपूर्णांकk("SX-DONE"))
			    cmd->SCp.Message = COMMAND_COMPLETE;
			lun = पढ़ो_wd33c93(regs, WD_TARGET_LUN);
			DB(DB_INTR, prपूर्णांकk(":%d.%d", cmd->SCp.Status, lun))
			    hostdata->connected = शून्य;
			hostdata->busy[cmd->device->id] &= ~(1 << (cmd->device->lun & 0xff));
			hostdata->state = S_UNCONNECTED;
			अगर (cmd->SCp.Status == ILLEGAL_STATUS_BYTE)
				cmd->SCp.Status = lun;
			अगर (cmd->cmnd[0] == REQUEST_SENSE
			    && cmd->SCp.Status != SAM_STAT_GOOD)
				cmd->result =
				    (cmd->
				     result & 0x00ffff) | (DID_ERROR << 16);
			अन्यथा
				cmd->result =
				    cmd->SCp.Status | (cmd->SCp.Message << 8);
			cmd->scsi_करोne(cmd);

/* We are no दीर्घer  connected to a target - check to see अगर
 * there are commands रुकोing to be executed.
 */
			spin_unlock_irqrestore(&hostdata->lock, flags);
			wd33c93_execute(instance);
		पूर्ण अन्यथा अणु
			prपूर्णांकk
			    ("%02x:%02x:%02x: Unknown SEL_XFER_DONE phase!!---",
			     asr, sr, phs);
			spin_unlock_irqrestore(&hostdata->lock, flags);
		पूर्ण
		अवरोध;

/* Note: this पूर्णांकerrupt will occur only after a LEVEL2 command */

	हाल CSR_SDP:
		DB(DB_INTR, prपूर्णांकk("SDP"))
		    hostdata->state = S_RUNNING_LEVEL2;
		ग_लिखो_wd33c93(regs, WD_COMMAND_PHASE, 0x41);
		ग_लिखो_wd33c93_cmd(regs, WD_CMD_SEL_ATN_XFER);
		spin_unlock_irqrestore(&hostdata->lock, flags);
		अवरोध;

	हाल CSR_XFER_DONE | PHS_MESS_OUT:
	हाल CSR_UNEXP | PHS_MESS_OUT:
	हाल CSR_SRV_REQ | PHS_MESS_OUT:
		DB(DB_INTR, prपूर्णांकk("MSG_OUT="))

/* To get here, we've probably requested MESSAGE_OUT and have
 * alपढ़ोy put the correct bytes in outgoing_msg[] and filled
 * in outgoing_len. We simply send them out to the SCSI bus.
 * Someबार we get MESSAGE_OUT phase when we're not expecting
 * it - like when our SDTR message is rejected by a target. Some
 * tarमाला_लो send the REJECT beक्रमe receiving all of the extended
 * message, and then seem to go back to MESSAGE_OUT क्रम a byte
 * or two. Not sure why, or अगर I'm करोing something wrong to
 * cause this to happen. Regardless, it seems that sending
 * NOP messages in these situations results in no harm and
 * makes everyone happy.
 */
		    अगर (hostdata->outgoing_len == 0) अणु
			hostdata->outgoing_len = 1;
			hostdata->outgoing_msg[0] = NOP;
		पूर्ण
		transfer_pio(regs, hostdata->outgoing_msg,
			     hostdata->outgoing_len, DATA_OUT_सूची, hostdata);
		DB(DB_INTR, prपूर्णांकk("%02x", hostdata->outgoing_msg[0]))
		    hostdata->outgoing_len = 0;
		hostdata->state = S_CONNECTED;
		spin_unlock_irqrestore(&hostdata->lock, flags);
		अवरोध;

	हाल CSR_UNEXP_DISC:

/* I think I've seen this after a request-sense that was in response
 * to an error condition, but not sure. We certainly need to करो
 * something when we get this पूर्णांकerrupt - the question is 'what?'.
 * Let's think positively, and assume some command has finished
 * in a legal manner (like a command that provokes a request-sense),
 * so we treat it as a normal command-complete-disconnect.
 */

/* Make sure that reselection is enabled at this poपूर्णांक - it may
 * have been turned off क्रम the command that just completed.
 */

		ग_लिखो_wd33c93(regs, WD_SOURCE_ID, SRCID_ER);
		अगर (cmd == शून्य) अणु
			prपूर्णांकk(" - Already disconnected! ");
			hostdata->state = S_UNCONNECTED;
			spin_unlock_irqrestore(&hostdata->lock, flags);
			वापस;
		पूर्ण
		DB(DB_INTR, prपूर्णांकk("UNEXP_DISC"))
		    hostdata->connected = शून्य;
		hostdata->busy[cmd->device->id] &= ~(1 << (cmd->device->lun & 0xff));
		hostdata->state = S_UNCONNECTED;
		अगर (cmd->cmnd[0] == REQUEST_SENSE && cmd->SCp.Status != SAM_STAT_GOOD)
			cmd->result =
			    (cmd->result & 0x00ffff) | (DID_ERROR << 16);
		अन्यथा
			cmd->result = cmd->SCp.Status | (cmd->SCp.Message << 8);
		cmd->scsi_करोne(cmd);

/* We are no दीर्घer connected to a target - check to see अगर
 * there are commands रुकोing to be executed.
 */
		/* look above क्रम comments on scsi_करोne() */
		spin_unlock_irqrestore(&hostdata->lock, flags);
		wd33c93_execute(instance);
		अवरोध;

	हाल CSR_DISC:

/* Make sure that reselection is enabled at this poपूर्णांक - it may
 * have been turned off क्रम the command that just completed.
 */

		ग_लिखो_wd33c93(regs, WD_SOURCE_ID, SRCID_ER);
		DB(DB_INTR, prपूर्णांकk("DISC"))
		    अगर (cmd == शून्य) अणु
			prपूर्णांकk(" - Already disconnected! ");
			hostdata->state = S_UNCONNECTED;
		पूर्ण
		चयन (hostdata->state) अणु
		हाल S_PRE_CMP_DISC:
			hostdata->connected = शून्य;
			hostdata->busy[cmd->device->id] &= ~(1 << (cmd->device->lun & 0xff));
			hostdata->state = S_UNCONNECTED;
			DB(DB_INTR, prपूर्णांकk(":%d", cmd->SCp.Status))
			    अगर (cmd->cmnd[0] == REQUEST_SENSE
				&& cmd->SCp.Status != SAM_STAT_GOOD)
				cmd->result =
				    (cmd->
				     result & 0x00ffff) | (DID_ERROR << 16);
			अन्यथा
				cmd->result =
				    cmd->SCp.Status | (cmd->SCp.Message << 8);
			cmd->scsi_करोne(cmd);
			अवरोध;
		हाल S_PRE_TMP_DISC:
		हाल S_RUNNING_LEVEL2:
			cmd->host_scribble = (uअक्षर *) hostdata->disconnected_Q;
			hostdata->disconnected_Q = cmd;
			hostdata->connected = शून्य;
			hostdata->state = S_UNCONNECTED;

#अगर_घोषित PROC_STATISTICS
			hostdata->disc_करोne_cnt[cmd->device->id]++;
#पूर्ण_अगर

			अवरोध;
		शेष:
			prपूर्णांकk("*** Unexpected DISCONNECT interrupt! ***");
			hostdata->state = S_UNCONNECTED;
		पूर्ण

/* We are no दीर्घer connected to a target - check to see अगर
 * there are commands रुकोing to be executed.
 */
		spin_unlock_irqrestore(&hostdata->lock, flags);
		wd33c93_execute(instance);
		अवरोध;

	हाल CSR_RESEL_AM:
	हाल CSR_RESEL:
		DB(DB_INTR, prपूर्णांकk("RESEL%s", sr == CSR_RESEL_AM ? "_AM" : ""))

		    /* Old chips (pre -A ???) करोn't have advanced features and will
		     * generate CSR_RESEL.  In that हाल we have to extract the LUN the
		     * hard way (see below).
		     * First we have to make sure this reselection didn't
		     * happen during Arbitration/Selection of some other device.
		     * If yes, put losing command back on top of input_Q.
		     */
		    अगर (hostdata->level2 <= L2_NONE) अणु

			अगर (hostdata->selecting) अणु
				cmd = (काष्ठा scsi_cmnd *) hostdata->selecting;
				hostdata->selecting = शून्य;
				hostdata->busy[cmd->device->id] &= ~(1 << (cmd->device->lun & 0xff));
				cmd->host_scribble =
				    (uअक्षर *) hostdata->input_Q;
				hostdata->input_Q = cmd;
			पूर्ण
		पूर्ण

		अन्यथा अणु

			अगर (cmd) अणु
				अगर (phs == 0x00) अणु
					hostdata->busy[cmd->device->id] &=
						~(1 << (cmd->device->lun & 0xff));
					cmd->host_scribble =
					    (uअक्षर *) hostdata->input_Q;
					hostdata->input_Q = cmd;
				पूर्ण अन्यथा अणु
					prपूर्णांकk
					    ("---%02x:%02x:%02x-TROUBLE: Intrusive ReSelect!---",
					     asr, sr, phs);
					जबतक (1)
						prपूर्णांकk("\r");
				पूर्ण
			पूर्ण

		पूर्ण

		/* OK - find out which device reselected us. */

		id = पढ़ो_wd33c93(regs, WD_SOURCE_ID);
		id &= SRCID_MASK;

		/* and extract the lun from the ID message. (Note that we करोn't
		 * bother to check क्रम a valid message here - I guess this is
		 * not the right way to go, but...)
		 */

		अगर (sr == CSR_RESEL_AM) अणु
			lun = पढ़ो_wd33c93(regs, WD_DATA);
			अगर (hostdata->level2 < L2_RESELECT)
				ग_लिखो_wd33c93_cmd(regs, WD_CMD_NEGATE_ACK);
			lun &= 7;
		पूर्ण अन्यथा अणु
			/* Old chip; रुको क्रम msgin phase to pick up the LUN. */
			क्रम (lun = 255; lun; lun--) अणु
				अगर ((asr = पढ़ो_aux_stat(regs)) & ASR_INT)
					अवरोध;
				udelay(10);
			पूर्ण
			अगर (!(asr & ASR_INT)) अणु
				prपूर्णांकk
				    ("wd33c93: Reselected without IDENTIFY\n");
				lun = 0;
			पूर्ण अन्यथा अणु
				/* Verअगरy this is a change to MSG_IN and पढ़ो the message */
				sr = पढ़ो_wd33c93(regs, WD_SCSI_STATUS);
				udelay(7);
				अगर (sr == (CSR_ABORT | PHS_MESS_IN) ||
				    sr == (CSR_UNEXP | PHS_MESS_IN) ||
				    sr == (CSR_SRV_REQ | PHS_MESS_IN)) अणु
					/* Got MSG_IN, grab target LUN */
					lun = पढ़ो_1_byte(regs);
					/* Now we expect a 'paused with ACK asserted' पूर्णांक.. */
					asr = पढ़ो_aux_stat(regs);
					अगर (!(asr & ASR_INT)) अणु
						udelay(10);
						asr = पढ़ो_aux_stat(regs);
						अगर (!(asr & ASR_INT))
							prपूर्णांकk
							    ("wd33c93: No int after LUN on RESEL (%02x)\n",
							     asr);
					पूर्ण
					sr = पढ़ो_wd33c93(regs, WD_SCSI_STATUS);
					udelay(7);
					अगर (sr != CSR_MSGIN)
						prपूर्णांकk
						    ("wd33c93: Not paused with ACK on RESEL (%02x)\n",
						     sr);
					lun &= 7;
					ग_लिखो_wd33c93_cmd(regs,
							  WD_CMD_NEGATE_ACK);
				पूर्ण अन्यथा अणु
					prपूर्णांकk
					    ("wd33c93: Not MSG_IN on reselect (%02x)\n",
					     sr);
					lun = 0;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Now we look क्रम the command that's reconnecting. */

		cmd = (काष्ठा scsi_cmnd *) hostdata->disconnected_Q;
		patch = शून्य;
		जबतक (cmd) अणु
			अगर (id == cmd->device->id && lun == (u8)cmd->device->lun)
				अवरोध;
			patch = cmd;
			cmd = (काष्ठा scsi_cmnd *) cmd->host_scribble;
		पूर्ण

		/* Hmm. Couldn't find a valid command.... What to करो? */

		अगर (!cmd) अणु
			prपूर्णांकk
			    ("---TROUBLE: target %d.%d not in disconnect queue---",
			     id, (u8)lun);
			spin_unlock_irqrestore(&hostdata->lock, flags);
			वापस;
		पूर्ण

		/* Ok, found the command - now start it up again. */

		अगर (patch)
			patch->host_scribble = cmd->host_scribble;
		अन्यथा
			hostdata->disconnected_Q =
			    (काष्ठा scsi_cmnd *) cmd->host_scribble;
		hostdata->connected = cmd;

		/* We करोn't need to worry about 'initialize_SCp()' or 'hostdata->busy[]'
		 * because these things are preserved over a disconnect.
		 * But we DO need to fix the DPD bit so it's correct क्रम this command.
		 */

		अगर (cmd->sc_data_direction == DMA_TO_DEVICE)
			ग_लिखो_wd33c93(regs, WD_DESTINATION_ID, cmd->device->id);
		अन्यथा
			ग_लिखो_wd33c93(regs, WD_DESTINATION_ID,
				      cmd->device->id | DSTID_DPD);
		अगर (hostdata->level2 >= L2_RESELECT) अणु
			ग_लिखो_wd33c93_count(regs, 0);	/* we want a DATA_PHASE पूर्णांकerrupt */
			ग_लिखो_wd33c93(regs, WD_COMMAND_PHASE, 0x45);
			ग_लिखो_wd33c93_cmd(regs, WD_CMD_SEL_ATN_XFER);
			hostdata->state = S_RUNNING_LEVEL2;
		पूर्ण अन्यथा
			hostdata->state = S_CONNECTED;

		    spin_unlock_irqrestore(&hostdata->lock, flags);
		अवरोध;

	शेष:
		prपूर्णांकk("--UNKNOWN INTERRUPT:%02x:%02x:%02x--", asr, sr, phs);
		spin_unlock_irqrestore(&hostdata->lock, flags);
	पूर्ण

	DB(DB_INTR, prपूर्णांकk("} "))

पूर्ण

अटल व्योम
reset_wd33c93(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा WD33C93_hostdata *hostdata =
	    (काष्ठा WD33C93_hostdata *) instance->hostdata;
	स्थिर wd33c93_regs regs = hostdata->regs;
	uअक्षर sr;

#अगर_घोषित CONFIG_SGI_IP22
	अणु
		पूर्णांक busycount = 0;
		बाह्य व्योम sgiwd93_reset(अचिन्हित दीर्घ);
		/* रुको 'til the chip माला_लो some समय क्रम us */
		जबतक ((पढ़ो_aux_stat(regs) & ASR_BSY) && busycount++ < 100)
			udelay (10);
	/*
 	 * there are scsi devices out there, which manage to lock up
	 * the wd33c93 in a busy condition. In this state it won't
	 * accept the reset command. The only way to solve this is to
 	 * give the chip a hardware reset (अगर possible). The code below
	 * करोes this क्रम the SGI Indy, where this is possible
	 */
	/* still busy ? */
	अगर (पढ़ो_aux_stat(regs) & ASR_BSY)
		sgiwd93_reset(instance->base); /* yeah, give it the hard one */
	पूर्ण
#पूर्ण_अगर

	ग_लिखो_wd33c93(regs, WD_OWN_ID, OWNID_EAF | OWNID_RAF |
		      instance->this_id | hostdata->घड़ी_freq);
	ग_लिखो_wd33c93(regs, WD_CONTROL, CTRL_IDI | CTRL_EDI | CTRL_POLLED);
	ग_लिखो_wd33c93(regs, WD_SYNCHRONOUS_TRANSFER,
		      calc_sync_xfer(hostdata->शेष_sx_per / 4,
				     DEFAULT_SX_OFF, 0, hostdata->sx_table));
	ग_लिखो_wd33c93(regs, WD_COMMAND, WD_CMD_RESET);


#अगर_घोषित CONFIG_MVME147_SCSI
	udelay(25);		/* The old wd33c93 on MVME147 needs this, at least */
#पूर्ण_अगर

	जबतक (!(पढ़ो_aux_stat(regs) & ASR_INT))
		;
	sr = पढ़ो_wd33c93(regs, WD_SCSI_STATUS);

	hostdata->microcode = पढ़ो_wd33c93(regs, WD_CDB_1);
	अगर (sr == 0x00)
		hostdata->chip = C_WD33C93;
	अन्यथा अगर (sr == 0x01) अणु
		ग_लिखो_wd33c93(regs, WD_QUEUE_TAG, 0xa5);	/* any अक्रमom number */
		sr = पढ़ो_wd33c93(regs, WD_QUEUE_TAG);
		अगर (sr == 0xa5) अणु
			hostdata->chip = C_WD33C93B;
			ग_लिखो_wd33c93(regs, WD_QUEUE_TAG, 0);
		पूर्ण अन्यथा
			hostdata->chip = C_WD33C93A;
	पूर्ण अन्यथा
		hostdata->chip = C_UNKNOWN_CHIP;

	अगर (hostdata->chip != C_WD33C93B)	/* Fast SCSI unavailable */
		hostdata->fast = 0;

	ग_लिखो_wd33c93(regs, WD_TIMEOUT_PERIOD, TIMEOUT_PERIOD_VALUE);
	ग_लिखो_wd33c93(regs, WD_CONTROL, CTRL_IDI | CTRL_EDI | CTRL_POLLED);
पूर्ण

पूर्णांक
wd33c93_host_reset(काष्ठा scsi_cmnd * SCpnt)
अणु
	काष्ठा Scsi_Host *instance;
	काष्ठा WD33C93_hostdata *hostdata;
	पूर्णांक i;

	instance = SCpnt->device->host;
	spin_lock_irq(instance->host_lock);
	hostdata = (काष्ठा WD33C93_hostdata *) instance->hostdata;

	prपूर्णांकk("scsi%d: reset. ", instance->host_no);
	disable_irq(instance->irq);

	hostdata->dma_stop(instance, शून्य, 0);
	क्रम (i = 0; i < 8; i++) अणु
		hostdata->busy[i] = 0;
		hostdata->sync_xfer[i] =
			calc_sync_xfer(DEFAULT_SX_PER / 4, DEFAULT_SX_OFF,
					0, hostdata->sx_table);
		hostdata->sync_stat[i] = SS_UNSET;	/* using शेष sync values */
	पूर्ण
	hostdata->input_Q = शून्य;
	hostdata->selecting = शून्य;
	hostdata->connected = शून्य;
	hostdata->disconnected_Q = शून्य;
	hostdata->state = S_UNCONNECTED;
	hostdata->dma = D_DMA_OFF;
	hostdata->incoming_ptr = 0;
	hostdata->outgoing_len = 0;

	reset_wd33c93(instance);
	SCpnt->result = DID_RESET << 16;
	enable_irq(instance->irq);
	spin_unlock_irq(instance->host_lock);
	वापस SUCCESS;
पूर्ण

पूर्णांक
wd33c93_पात(काष्ठा scsi_cmnd * cmd)
अणु
	काष्ठा Scsi_Host *instance;
	काष्ठा WD33C93_hostdata *hostdata;
	wd33c93_regs regs;
	काष्ठा scsi_cmnd *पंचांगp, *prev;

	disable_irq(cmd->device->host->irq);

	instance = cmd->device->host;
	hostdata = (काष्ठा WD33C93_hostdata *) instance->hostdata;
	regs = hostdata->regs;

/*
 * Case 1 : If the command hasn't been issued yet, we simply हटाओ it
 *     from the input_Q.
 */

	पंचांगp = (काष्ठा scsi_cmnd *) hostdata->input_Q;
	prev = शून्य;
	जबतक (पंचांगp) अणु
		अगर (पंचांगp == cmd) अणु
			अगर (prev)
				prev->host_scribble = cmd->host_scribble;
			अन्यथा
				hostdata->input_Q =
				    (काष्ठा scsi_cmnd *) cmd->host_scribble;
			cmd->host_scribble = शून्य;
			cmd->result = DID_ABORT << 16;
			prपूर्णांकk
			    ("scsi%d: Abort - removing command from input_Q. ",
			     instance->host_no);
			enable_irq(cmd->device->host->irq);
			cmd->scsi_करोne(cmd);
			वापस SUCCESS;
		पूर्ण
		prev = पंचांगp;
		पंचांगp = (काष्ठा scsi_cmnd *) पंचांगp->host_scribble;
	पूर्ण

/*
 * Case 2 : If the command is connected, we're going to fail the पात
 *     and let the high level SCSI driver retry at a later समय or
 *     issue a reset.
 *
 *     Timeouts, and thereक्रमe पातed commands, will be highly unlikely
 *     and handling them cleanly in this situation would make the common
 *     हाल of noresets less efficient, and would pollute our code.  So,
 *     we fail.
 */

	अगर (hostdata->connected == cmd) अणु
		uअक्षर sr, asr;
		अचिन्हित दीर्घ समयout;

		prपूर्णांकk("scsi%d: Aborting connected command - ",
		       instance->host_no);

		prपूर्णांकk("stopping DMA - ");
		अगर (hostdata->dma == D_DMA_RUNNING) अणु
			hostdata->dma_stop(instance, cmd, 0);
			hostdata->dma = D_DMA_OFF;
		पूर्ण

		prपूर्णांकk("sending wd33c93 ABORT command - ");
		ग_लिखो_wd33c93(regs, WD_CONTROL,
			      CTRL_IDI | CTRL_EDI | CTRL_POLLED);
		ग_लिखो_wd33c93_cmd(regs, WD_CMD_ABORT);

/* Now we have to attempt to flush out the FIFO... */

		prपूर्णांकk("flushing fifo - ");
		समयout = 1000000;
		करो अणु
			asr = पढ़ो_aux_stat(regs);
			अगर (asr & ASR_DBR)
				पढ़ो_wd33c93(regs, WD_DATA);
		पूर्ण जबतक (!(asr & ASR_INT) && समयout-- > 0);
		sr = पढ़ो_wd33c93(regs, WD_SCSI_STATUS);
		prपूर्णांकk
		    ("asr=%02x, sr=%02x, %ld bytes un-transferred (timeout=%ld) - ",
		     asr, sr, पढ़ो_wd33c93_count(regs), समयout);

		/*
		 * Abort command processed.
		 * Still connected.
		 * We must disconnect.
		 */

		prपूर्णांकk("sending wd33c93 DISCONNECT command - ");
		ग_लिखो_wd33c93_cmd(regs, WD_CMD_DISCONNECT);

		समयout = 1000000;
		asr = पढ़ो_aux_stat(regs);
		जबतक ((asr & ASR_CIP) && समयout-- > 0)
			asr = पढ़ो_aux_stat(regs);
		sr = पढ़ो_wd33c93(regs, WD_SCSI_STATUS);
		prपूर्णांकk("asr=%02x, sr=%02x.", asr, sr);

		hostdata->busy[cmd->device->id] &= ~(1 << (cmd->device->lun & 0xff));
		hostdata->connected = शून्य;
		hostdata->state = S_UNCONNECTED;
		cmd->result = DID_ABORT << 16;

/*      sti();*/
		wd33c93_execute(instance);

		enable_irq(cmd->device->host->irq);
		cmd->scsi_करोne(cmd);
		वापस SUCCESS;
	पूर्ण

/*
 * Case 3: If the command is currently disconnected from the bus,
 * we're not going to expend much effort here: Let's just वापस
 * an ABORT_SNOOZE and hope क्रम the best...
 */

	पंचांगp = (काष्ठा scsi_cmnd *) hostdata->disconnected_Q;
	जबतक (पंचांगp) अणु
		अगर (पंचांगp == cmd) अणु
			prपूर्णांकk
			    ("scsi%d: Abort - command found on disconnected_Q - ",
			     instance->host_no);
			prपूर्णांकk("Abort SNOOZE. ");
			enable_irq(cmd->device->host->irq);
			वापस FAILED;
		पूर्ण
		पंचांगp = (काष्ठा scsi_cmnd *) पंचांगp->host_scribble;
	पूर्ण

/*
 * Case 4 : If we reached this poपूर्णांक, the command was not found in any of
 *     the queues.
 *
 * We probably reached this poपूर्णांक because of an unlikely race condition
 * between the command completing successfully and the पातion code,
 * so we won't panic, but we will notअगरy the user in हाल something really
 * broke.
 */

/*   sti();*/
	wd33c93_execute(instance);

	enable_irq(cmd->device->host->irq);
	prपूर्णांकk("scsi%d: warning : SCSI command probably completed successfully"
	       "         before abortion. ", instance->host_no);
	वापस FAILED;
पूर्ण

#घोषणा MAX_WD33C93_HOSTS 4
#घोषणा MAX_SETUP_ARGS ARRAY_SIZE(setup_args)
#घोषणा SETUP_BUFFER_SIZE 200
अटल अक्षर setup_buffer[SETUP_BUFFER_SIZE];
अटल अक्षर setup_used[MAX_SETUP_ARGS];
अटल पूर्णांक करोne_setup = 0;

अटल पूर्णांक
wd33c93_setup(अक्षर *str)
अणु
	पूर्णांक i;
	अक्षर *p1, *p2;

	/* The kernel करोes some processing of the command-line beक्रमe calling
	 * this function: If it begins with any decimal or hex number arguments,
	 * पूर्णांकs[0] = how many numbers found and पूर्णांकs[1] through [n] are the values
	 * themselves. str poपूर्णांकs to where the non-numeric arguments (अगर any)
	 * start: We करो our own parsing of those. We स्थिरruct synthetic 'nosync'
	 * keywords out of numeric args (to मुख्यtain compatibility with older
	 * versions) and then add the rest of the arguments.
	 */

	p1 = setup_buffer;
	*p1 = '\0';
	अगर (str)
		म_नकलन(p1, str, SETUP_BUFFER_SIZE - म_माप(setup_buffer));
	setup_buffer[SETUP_BUFFER_SIZE - 1] = '\0';
	p1 = setup_buffer;
	i = 0;
	जबतक (*p1 && (i < MAX_SETUP_ARGS)) अणु
		p2 = म_अक्षर(p1, ',');
		अगर (p2) अणु
			*p2 = '\0';
			अगर (p1 != p2)
				setup_args[i] = p1;
			p1 = p2 + 1;
			i++;
		पूर्ण अन्यथा अणु
			setup_args[i] = p1;
			अवरोध;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < MAX_SETUP_ARGS; i++)
		setup_used[i] = 0;
	करोne_setup = 1;

	वापस 1;
पूर्ण
__setup("wd33c93=", wd33c93_setup);

/* check_setup_args() वापसs index अगर key found, 0 अगर not
 */
अटल पूर्णांक
check_setup_args(अक्षर *key, पूर्णांक *flags, पूर्णांक *val, अक्षर *buf)
अणु
	पूर्णांक x;
	अक्षर *cp;

	क्रम (x = 0; x < MAX_SETUP_ARGS; x++) अणु
		अगर (setup_used[x])
			जारी;
		अगर (!म_भेदन(setup_args[x], key, म_माप(key)))
			अवरोध;
		अगर (!म_भेदन(setup_args[x], "next", म_माप("next")))
			वापस 0;
	पूर्ण
	अगर (x == MAX_SETUP_ARGS)
		वापस 0;
	setup_used[x] = 1;
	cp = setup_args[x] + म_माप(key);
	*val = -1;
	अगर (*cp != ':')
		वापस ++x;
	cp++;
	अगर ((*cp >= '0') && (*cp <= '9')) अणु
		*val = simple_म_से_अदीर्घ(cp, शून्य, 0);
	पूर्ण
	वापस ++x;
पूर्ण

/*
 * Calculate पूर्णांकernal data-transfer-घड़ी cycle from input-घड़ी
 * frequency (/MHz) and fill 'sx_table'.
 *
 * The original driver used to rely on a fixed sx_table, containing periods
 * क्रम (only) the lower limits of the respective input-घड़ी-frequency ranges
 * (8-10/12-15/16-20 MHz). Although it seems, that no problems occurred with
 * this setting so far, it might be desirable to adjust the transfer periods
 * बंदr to the really attached, possibly 25% higher, input-घड़ी, since
 * - the wd33c93 may really use a signअगरicant लघुer period, than it has
 *   negotiated (eg. thrashing the target, which expects 4/8MHz, with 5/10MHz
 *   instead).
 * - the wd33c93 may ask the target क्रम a lower transfer rate, than the target
 *   is capable of (eg. negotiating क्रम an assumed minimum of 252ns instead of
 *   possible 200ns, which indeed shows up in tests as an approx. 10% lower
 *   transfer rate).
 */
अटल अंतरभूत अचिन्हित पूर्णांक
round_4(अचिन्हित पूर्णांक x)
अणु
	चयन (x & 3) अणु
		हाल 1: --x;
			अवरोध;
		हाल 2: ++x;
			fallthrough;
		हाल 3: ++x;
	पूर्ण
	वापस x;
पूर्ण

अटल व्योम
calc_sx_table(अचिन्हित पूर्णांक mhz, काष्ठा sx_period sx_table[9])
अणु
	अचिन्हित पूर्णांक d, i;
	अगर (mhz < 11)
		d = 2;	/* भागisor क्रम  8-10 MHz input-घड़ी */
	अन्यथा अगर (mhz < 16)
		d = 3;	/* भागisor क्रम 12-15 MHz input-घड़ी */
	अन्यथा
		d = 4;	/* भागisor क्रम 16-20 MHz input-घड़ी */

	d = (100000 * d) / 2 / mhz; /* 100 x DTCC / nanosec */

	sx_table[0].period_ns = 1;
	sx_table[0].reg_value = 0x20;
	क्रम (i = 1; i < 8; i++) अणु
		sx_table[i].period_ns = round_4((i+1)*d / 100);
		sx_table[i].reg_value = (i+1)*0x10;
	पूर्ण
	sx_table[7].reg_value = 0;
	sx_table[8].period_ns = 0;
	sx_table[8].reg_value = 0;
पूर्ण

/*
 * check and, maybe, map an init- or "clock:"- argument.
 */
अटल uअक्षर
set_clk_freq(पूर्णांक freq, पूर्णांक *mhz)
अणु
	पूर्णांक x = freq;
	अगर (WD33C93_FS_8_10 == freq)
		freq = 8;
	अन्यथा अगर (WD33C93_FS_12_15 == freq)
		freq = 12;
	अन्यथा अगर (WD33C93_FS_16_20 == freq)
		freq = 16;
	अन्यथा अगर (freq > 7 && freq < 11)
		x = WD33C93_FS_8_10;
		अन्यथा अगर (freq > 11 && freq < 16)
		x = WD33C93_FS_12_15;
		अन्यथा अगर (freq > 15 && freq < 21)
		x = WD33C93_FS_16_20;
	अन्यथा अणु
			/* Hmm, wouldn't it be safer to assume highest freq here? */
		x = WD33C93_FS_8_10;
		freq = 8;
	पूर्ण
	*mhz = freq;
	वापस x;
पूर्ण

/*
 * to be used with the resync: fast: ... options
 */
अटल अंतरभूत व्योम set_resync ( काष्ठा WD33C93_hostdata *hd, पूर्णांक mask )
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 8; i++)
		अगर (mask & (1 << i))
			hd->sync_stat[i] = SS_UNSET;
पूर्ण

व्योम
wd33c93_init(काष्ठा Scsi_Host *instance, स्थिर wd33c93_regs regs,
	     dma_setup_t setup, dma_stop_t stop, पूर्णांक घड़ी_freq)
अणु
	काष्ठा WD33C93_hostdata *hostdata;
	पूर्णांक i;
	पूर्णांक flags;
	पूर्णांक val;
	अक्षर buf[32];

	अगर (!करोne_setup && setup_strings)
		wd33c93_setup(setup_strings);

	hostdata = (काष्ठा WD33C93_hostdata *) instance->hostdata;

	hostdata->regs = regs;
	hostdata->घड़ी_freq = set_clk_freq(घड़ी_freq, &i);
	calc_sx_table(i, hostdata->sx_table);
	hostdata->dma_setup = setup;
	hostdata->dma_stop = stop;
	hostdata->dma_bounce_buffer = शून्य;
	hostdata->dma_bounce_len = 0;
	क्रम (i = 0; i < 8; i++) अणु
		hostdata->busy[i] = 0;
		hostdata->sync_xfer[i] =
			calc_sync_xfer(DEFAULT_SX_PER / 4, DEFAULT_SX_OFF,
					0, hostdata->sx_table);
		hostdata->sync_stat[i] = SS_UNSET;	/* using शेष sync values */
#अगर_घोषित PROC_STATISTICS
		hostdata->cmd_cnt[i] = 0;
		hostdata->disc_allowed_cnt[i] = 0;
		hostdata->disc_करोne_cnt[i] = 0;
#पूर्ण_अगर
	पूर्ण
	hostdata->input_Q = शून्य;
	hostdata->selecting = शून्य;
	hostdata->connected = शून्य;
	hostdata->disconnected_Q = शून्य;
	hostdata->state = S_UNCONNECTED;
	hostdata->dma = D_DMA_OFF;
	hostdata->level2 = L2_BASIC;
	hostdata->disconnect = DIS_ADAPTIVE;
	hostdata->args = DEBUG_DEFAULTS;
	hostdata->incoming_ptr = 0;
	hostdata->outgoing_len = 0;
	hostdata->शेष_sx_per = DEFAULT_SX_PER;
	hostdata->no_dma = 0;	/* शेष is DMA enabled */

#अगर_घोषित PROC_INTERFACE
	hostdata->proc = PR_VERSION | PR_INFO | PR_STATISTICS |
	    PR_CONNECTED | PR_INPUTQ | PR_DISCQ | PR_STOP;
#अगर_घोषित PROC_STATISTICS
	hostdata->dma_cnt = 0;
	hostdata->pio_cnt = 0;
	hostdata->पूर्णांक_cnt = 0;
#पूर्ण_अगर
#पूर्ण_अगर

	अगर (check_setup_args("clock", &flags, &val, buf)) अणु
		hostdata->घड़ी_freq = set_clk_freq(val, &val);
		calc_sx_table(val, hostdata->sx_table);
	पूर्ण

	अगर (check_setup_args("nosync", &flags, &val, buf))
		hostdata->no_sync = val;

	अगर (check_setup_args("nodma", &flags, &val, buf))
		hostdata->no_dma = (val == -1) ? 1 : val;

	अगर (check_setup_args("period", &flags, &val, buf))
		hostdata->शेष_sx_per =
		    hostdata->sx_table[round_period((अचिन्हित पूर्णांक) val,
		                                    hostdata->sx_table)].period_ns;

	अगर (check_setup_args("disconnect", &flags, &val, buf)) अणु
		अगर ((val >= DIS_NEVER) && (val <= DIS_ALWAYS))
			hostdata->disconnect = val;
		अन्यथा
			hostdata->disconnect = DIS_ADAPTIVE;
	पूर्ण

	अगर (check_setup_args("level2", &flags, &val, buf))
		hostdata->level2 = val;

	अगर (check_setup_args("debug", &flags, &val, buf))
		hostdata->args = val & DB_MASK;

	अगर (check_setup_args("burst", &flags, &val, buf))
		hostdata->dma_mode = val ? CTRL_BURST:CTRL_DMA;

	अगर (WD33C93_FS_16_20 == hostdata->घड़ी_freq /* भागisor 4 */
		&& check_setup_args("fast", &flags, &val, buf))
		hostdata->fast = !!val;

	अगर ((i = check_setup_args("next", &flags, &val, buf))) अणु
		जबतक (i)
			setup_used[--i] = 1;
	पूर्ण
#अगर_घोषित PROC_INTERFACE
	अगर (check_setup_args("proc", &flags, &val, buf))
		hostdata->proc = val;
#पूर्ण_अगर

	spin_lock_irq(&hostdata->lock);
	reset_wd33c93(instance);
	spin_unlock_irq(&hostdata->lock);

	prपूर्णांकk("wd33c93-%d: chip=%s/%d no_sync=0x%x no_dma=%d",
	       instance->host_no,
	       (hostdata->chip == C_WD33C93) ? "WD33c93" : (hostdata->chip ==
							    C_WD33C93A) ?
	       "WD33c93A" : (hostdata->chip ==
			     C_WD33C93B) ? "WD33c93B" : "unknown",
	       hostdata->microcode, hostdata->no_sync, hostdata->no_dma);
#अगर_घोषित DEBUGGING_ON
	prपूर्णांकk(" debug_flags=0x%02x\n", hostdata->args);
#अन्यथा
	prपूर्णांकk(" debugging=OFF\n");
#पूर्ण_अगर
	prपूर्णांकk("           setup_args=");
	क्रम (i = 0; i < MAX_SETUP_ARGS; i++)
		prपूर्णांकk("%s,", setup_args[i]);
	prपूर्णांकk("\n");
	prपूर्णांकk("           Version %s - %s\n", WD33C93_VERSION, WD33C93_DATE);
पूर्ण

पूर्णांक wd33c93_ग_लिखो_info(काष्ठा Scsi_Host *instance, अक्षर *buf, पूर्णांक len)
अणु
#अगर_घोषित PROC_INTERFACE
	अक्षर *bp;
	काष्ठा WD33C93_hostdata *hd;
	पूर्णांक x;

	hd = (काष्ठा WD33C93_hostdata *) instance->hostdata;

/* We accept the following
 * keywords (same क्रमmat as command-line, but arguments are not optional):
 *    debug
 *    disconnect
 *    period
 *    resync
 *    proc
 *    nodma
 *    level2
 *    burst
 *    fast
 *    nosync
 */

	buf[len] = '\0';
	क्रम (bp = buf; *bp; ) अणु
		जबतक (',' == *bp || ' ' == *bp)
			++bp;
	अगर (!म_भेदन(bp, "debug:", 6)) अणु
			hd->args = simple_म_से_अदीर्घ(bp+6, &bp, 0) & DB_MASK;
	पूर्ण अन्यथा अगर (!म_भेदन(bp, "disconnect:", 11)) अणु
			x = simple_म_से_अदीर्घ(bp+11, &bp, 0);
		अगर (x < DIS_NEVER || x > DIS_ALWAYS)
			x = DIS_ADAPTIVE;
		hd->disconnect = x;
	पूर्ण अन्यथा अगर (!म_भेदन(bp, "period:", 7)) अणु
		x = simple_म_से_अदीर्घ(bp+7, &bp, 0);
		hd->शेष_sx_per =
			hd->sx_table[round_period((अचिन्हित पूर्णांक) x,
						  hd->sx_table)].period_ns;
	पूर्ण अन्यथा अगर (!म_भेदन(bp, "resync:", 7)) अणु
			set_resync(hd, (पूर्णांक)simple_म_से_अदीर्घ(bp+7, &bp, 0));
	पूर्ण अन्यथा अगर (!म_भेदन(bp, "proc:", 5)) अणु
			hd->proc = simple_म_से_अदीर्घ(bp+5, &bp, 0);
	पूर्ण अन्यथा अगर (!म_भेदन(bp, "nodma:", 6)) अणु
			hd->no_dma = simple_म_से_अदीर्घ(bp+6, &bp, 0);
	पूर्ण अन्यथा अगर (!म_भेदन(bp, "level2:", 7)) अणु
			hd->level2 = simple_म_से_अदीर्घ(bp+7, &bp, 0);
		पूर्ण अन्यथा अगर (!म_भेदन(bp, "burst:", 6)) अणु
			hd->dma_mode =
				simple_म_से_दीर्घ(bp+6, &bp, 0) ? CTRL_BURST:CTRL_DMA;
		पूर्ण अन्यथा अगर (!म_भेदन(bp, "fast:", 5)) अणु
			x = !!simple_म_से_दीर्घ(bp+5, &bp, 0);
			अगर (x != hd->fast)
				set_resync(hd, 0xff);
			hd->fast = x;
		पूर्ण अन्यथा अगर (!म_भेदन(bp, "nosync:", 7)) अणु
			x = simple_म_से_अदीर्घ(bp+7, &bp, 0);
			set_resync(hd, x ^ hd->no_sync);
			hd->no_sync = x;
		पूर्ण अन्यथा अणु
			अवरोध; /* unknown keyword,syntax-error,... */
		पूर्ण
	पूर्ण
	वापस len;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

पूर्णांक
wd33c93_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *instance)
अणु
#अगर_घोषित PROC_INTERFACE
	काष्ठा WD33C93_hostdata *hd;
	काष्ठा scsi_cmnd *cmd;
	पूर्णांक x;

	hd = (काष्ठा WD33C93_hostdata *) instance->hostdata;

	spin_lock_irq(&hd->lock);
	अगर (hd->proc & PR_VERSION)
		seq_म_लिखो(m, "\nVersion %s - %s.",
			WD33C93_VERSION, WD33C93_DATE);

	अगर (hd->proc & PR_INFO) अणु
		seq_म_लिखो(m, "\nclock_freq=%02x no_sync=%02x no_dma=%d"
			" dma_mode=%02x fast=%d",
			hd->घड़ी_freq, hd->no_sync, hd->no_dma, hd->dma_mode, hd->fast);
		seq_माला_दो(m, "\nsync_xfer[] =       ");
		क्रम (x = 0; x < 7; x++)
			seq_म_लिखो(m, "\t%02x", hd->sync_xfer[x]);
		seq_माला_दो(m, "\nsync_stat[] =       ");
		क्रम (x = 0; x < 7; x++)
			seq_म_लिखो(m, "\t%02x", hd->sync_stat[x]);
	पूर्ण
#अगर_घोषित PROC_STATISTICS
	अगर (hd->proc & PR_STATISTICS) अणु
		seq_माला_दो(m, "\ncommands issued:    ");
		क्रम (x = 0; x < 7; x++)
			seq_म_लिखो(m, "\t%ld", hd->cmd_cnt[x]);
		seq_माला_दो(m, "\ndisconnects allowed:");
		क्रम (x = 0; x < 7; x++)
			seq_म_लिखो(m, "\t%ld", hd->disc_allowed_cnt[x]);
		seq_माला_दो(m, "\ndisconnects done:   ");
		क्रम (x = 0; x < 7; x++)
			seq_म_लिखो(m, "\t%ld", hd->disc_करोne_cnt[x]);
		seq_म_लिखो(m,
			"\ninterrupts: %ld, DATA_PHASE ints: %ld DMA, %ld PIO",
			hd->पूर्णांक_cnt, hd->dma_cnt, hd->pio_cnt);
	पूर्ण
#पूर्ण_अगर
	अगर (hd->proc & PR_CONNECTED) अणु
		seq_माला_दो(m, "\nconnected:     ");
		अगर (hd->connected) अणु
			cmd = (काष्ठा scsi_cmnd *) hd->connected;
			seq_म_लिखो(m, " %d:%llu(%02x)",
				cmd->device->id, cmd->device->lun, cmd->cmnd[0]);
		पूर्ण
	पूर्ण
	अगर (hd->proc & PR_INPUTQ) अणु
		seq_माला_दो(m, "\ninput_Q:       ");
		cmd = (काष्ठा scsi_cmnd *) hd->input_Q;
		जबतक (cmd) अणु
			seq_म_लिखो(m, " %d:%llu(%02x)",
				cmd->device->id, cmd->device->lun, cmd->cmnd[0]);
			cmd = (काष्ठा scsi_cmnd *) cmd->host_scribble;
		पूर्ण
	पूर्ण
	अगर (hd->proc & PR_DISCQ) अणु
		seq_माला_दो(m, "\ndisconnected_Q:");
		cmd = (काष्ठा scsi_cmnd *) hd->disconnected_Q;
		जबतक (cmd) अणु
			seq_म_लिखो(m, " %d:%llu(%02x)",
				cmd->device->id, cmd->device->lun, cmd->cmnd[0]);
			cmd = (काष्ठा scsi_cmnd *) cmd->host_scribble;
		पूर्ण
	पूर्ण
	seq_अ_दो(m, '\n');
	spin_unlock_irq(&hd->lock);
#पूर्ण_अगर				/* PROC_INTERFACE */
	वापस 0;
पूर्ण

EXPORT_SYMBOL(wd33c93_host_reset);
EXPORT_SYMBOL(wd33c93_init);
EXPORT_SYMBOL(wd33c93_पात);
EXPORT_SYMBOL(wd33c93_queuecommand);
EXPORT_SYMBOL(wd33c93_पूर्णांकr);
EXPORT_SYMBOL(wd33c93_show_info);
EXPORT_SYMBOL(wd33c93_ग_लिखो_info);
