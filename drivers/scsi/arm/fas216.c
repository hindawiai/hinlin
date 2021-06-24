<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/acorn/scsi/fas216.c
 *
 *  Copyright (C) 1997-2003 Russell King
 *
 * Based on inक्रमmation in qlogicfas.c by Tom Zerucha, Michael Grअगरfith, and
 * other sources, including:
 *   the AMD Am53CF94 data sheet
 *   the AMD Am53C94 data sheet
 *
 * This is a generic driver.  To use it, have a look at cumana_2.c.  You
 * should define your own काष्ठाure that overlays FAS216_Info, eg:
 * काष्ठा my_host_data अणु
 *    FAS216_Info info;
 *    ... my host specअगरic data ...
 * पूर्ण;
 *
 * Changelog:
 *  30-08-1997	RMK	Created
 *  14-09-1997	RMK	Started disconnect support
 *  08-02-1998	RMK	Corrected real DMA support
 *  15-02-1998	RMK	Started sync xfer support
 *  06-04-1998	RMK	Tightened conditions क्रम prपूर्णांकing incomplete
 *			transfers
 *  02-05-1998	RMK	Added extra checks in fas216_reset
 *  24-05-1998	RMK	Fixed synchronous transfers with period >= 200ns
 *  27-06-1998	RMK	Changed यंत्र/delay.h to linux/delay.h
 *  26-08-1998	RMK	Improved message support wrt MESSAGE_REJECT
 *  02-04-2000	RMK	Converted to use the new error handling, and
 *			स्वतःmatically request sense data upon check
 *			condition status from tarमाला_लो.
 */
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/ecard.h>

#समावेश "../scsi.h"
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_host.h>
#समावेश "fas216.h"
#समावेश "scsi.h"

/* NOTE: SCSI2 Synchronous transfers *require* DMA according to
 *  the data sheet.  This restriction is crazy, especially when
 *  you only want to send 16 bytes!  What were the guys who
 *  deचिन्हित this chip on at that समय?  Did they पढ़ो the SCSI2
 *  spec at all?  The following sections are taken from the SCSI2
 *  standard (s2r10) concerning this:
 *
 * > IMPLEMENTORS NOTES:
 * >   (1)  Re-negotiation at every selection is not recommended, since a
 * >   signअगरicant perक्रमmance impact is likely.
 *
 * >  The implied synchronous agreement shall reमुख्य in effect until a BUS DEVICE
 * >  RESET message is received, until a hard reset condition occurs, or until one
 * >  of the two SCSI devices elects to modअगरy the agreement.  The शेष data
 * >  transfer mode is asynchronous data transfer mode.  The शेष data transfer
 * >  mode is entered at घातer on, after a BUS DEVICE RESET message, or after a hard
 * >  reset condition.
 *
 *  In total, this means that once you have elected to use synchronous
 *  transfers, you must always use DMA.
 *
 *  I was thinking that this was a good chip until I found this restriction ;(
 */
#घोषणा SCSI2_SYNC
#अघोषित  SCSI2_TAG

#अघोषित DEBUG_CONNECT
#अघोषित DEBUG_MESSAGES

#अघोषित CHECK_STRUCTURE

#घोषणा LOG_CONNECT		(1 << 0)
#घोषणा LOG_BUSSERVICE		(1 << 1)
#घोषणा LOG_FUNCTIONDONE	(1 << 2)
#घोषणा LOG_MESSAGES		(1 << 3)
#घोषणा LOG_BUFFER		(1 << 4)
#घोषणा LOG_ERROR		(1 << 8)

अटल पूर्णांक level_mask = LOG_ERROR;

module_param(level_mask, पूर्णांक, 0644);

#अगर_अघोषित MODULE
अटल पूर्णांक __init fas216_log_setup(अक्षर *str)
अणु
	अक्षर *s;

	level_mask = 0;

	जबतक ((s = strsep(&str, ",")) != शून्य) अणु
		चयन (s[0]) अणु
		हाल 'a':
			अगर (म_भेद(s, "all") == 0)
				level_mask |= -1;
			अवरोध;
		हाल 'b':
			अगर (म_भेदन(s, "bus", 3) == 0)
				level_mask |= LOG_BUSSERVICE;
			अगर (म_भेदन(s, "buf", 3) == 0)
				level_mask |= LOG_BUFFER;
			अवरोध;
		हाल 'c':
			level_mask |= LOG_CONNECT;
			अवरोध;
		हाल 'e':
			level_mask |= LOG_ERROR;
			अवरोध;
		हाल 'm':
			level_mask |= LOG_MESSAGES;
			अवरोध;
		हाल 'n':
			अगर (म_भेद(s, "none") == 0)
				level_mask = 0;
			अवरोध;
		हाल 's':
			level_mask |= LOG_FUNCTIONDONE;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

__setup("fas216_logging=", fas216_log_setup);
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित अक्षर fas216_पढ़ोb(FAS216_Info *info, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक off = reg << info->scsi.io_shअगरt;
	वापस पढ़ोb(info->scsi.io_base + off);
पूर्ण

अटल अंतरभूत व्योम fas216_ग_लिखोb(FAS216_Info *info, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक off = reg << info->scsi.io_shअगरt;
	ग_लिखोb(val, info->scsi.io_base + off);
पूर्ण

अटल व्योम fas216_dumpstate(FAS216_Info *info)
अणु
	अचिन्हित अक्षर is, stat, inst;

	is   = fas216_पढ़ोb(info, REG_IS);
	stat = fas216_पढ़ोb(info, REG_STAT);
	inst = fas216_पढ़ोb(info, REG_INST);
	
	prपूर्णांकk("FAS216: CTCL=%02X CTCM=%02X CMD=%02X STAT=%02X"
	       " INST=%02X IS=%02X CFIS=%02X",
		fas216_पढ़ोb(info, REG_CTCL),
		fas216_पढ़ोb(info, REG_CTCM),
		fas216_पढ़ोb(info, REG_CMD),  stat, inst, is,
		fas216_पढ़ोb(info, REG_CFIS));
	prपूर्णांकk(" CNTL1=%02X CNTL2=%02X CNTL3=%02X CTCH=%02X\n",
		fas216_पढ़ोb(info, REG_CNTL1),
		fas216_पढ़ोb(info, REG_CNTL2),
		fas216_पढ़ोb(info, REG_CNTL3),
		fas216_पढ़ोb(info, REG_CTCH));
पूर्ण

अटल व्योम prपूर्णांक_SCp(काष्ठा scsi_poपूर्णांकer *SCp, स्थिर अक्षर *prefix, स्थिर अक्षर *suffix)
अणु
	prपूर्णांकk("%sptr %p this_residual 0x%x buffer %p buffers_residual 0x%x%s",
		prefix, SCp->ptr, SCp->this_residual, SCp->buffer,
		SCp->buffers_residual, suffix);
पूर्ण

#अगर_घोषित CHECK_STRUCTURE
अटल व्योम fas216_dumpinfo(FAS216_Info *info)
अणु
	अटल पूर्णांक used = 0;
	पूर्णांक i;

	अगर (used++)
		वापस;

	prपूर्णांकk("FAS216_Info=\n");
	prपूर्णांकk("  { magic_start=%lX host=%p SCpnt=%p origSCpnt=%p\n",
		info->magic_start, info->host, info->SCpnt,
		info->origSCpnt);
	prपूर्णांकk("    scsi={ io_shift=%X irq=%X cfg={ %X %X %X %X }\n",
		info->scsi.io_shअगरt, info->scsi.irq,
		info->scsi.cfg[0], info->scsi.cfg[1], info->scsi.cfg[2],
		info->scsi.cfg[3]);
	prपूर्णांकk("           type=%p phase=%X\n",
		info->scsi.type, info->scsi.phase);
	prपूर्णांक_SCp(&info->scsi.SCp, "           SCp={ ", " }\n");
	prपूर्णांकk("      msgs async_stp=%X disconnectable=%d aborting=%d }\n",
		info->scsi.async_stp,
		info->scsi.disconnectable, info->scsi.पातing);
	prपूर्णांकk("    stats={ queues=%X removes=%X fins=%X reads=%X writes=%X miscs=%X\n"
	       "            disconnects=%X aborts=%X bus_resets=%X host_resets=%X}\n",
		info->stats.queues, info->stats.हटाओs, info->stats.fins,
		info->stats.पढ़ोs, info->stats.ग_लिखोs, info->stats.miscs,
		info->stats.disconnects, info->stats.पातs, info->stats.bus_resets,
		info->stats.host_resets);
	prपूर्णांकk("    ifcfg={ clockrate=%X select_timeout=%X asyncperiod=%X sync_max_depth=%X }\n",
		info->अगरcfg.घड़ीrate, info->अगरcfg.select_समयout,
		info->अगरcfg.asyncperiod, info->अगरcfg.sync_max_depth);
	क्रम (i = 0; i < 8; i++) अणु
		prपूर्णांकk("    busyluns[%d]=%08lx dev[%d]={ disconnect_ok=%d stp=%X sof=%X sync_state=%X }\n",
			i, info->busyluns[i], i,
			info->device[i].disconnect_ok, info->device[i].stp,
			info->device[i].sof, info->device[i].sync_state);
	पूर्ण
	prपूर्णांकk("    dma={ transfer_type=%X setup=%p pseudo=%p stop=%p }\n",
		info->dma.transfer_type, info->dma.setup,
		info->dma.pseuकरो, info->dma.stop);
	prपूर्णांकk("    internal_done=%X magic_end=%lX }\n",
		info->पूर्णांकernal_करोne, info->magic_end);
पूर्ण

अटल व्योम __fas216_checkmagic(FAS216_Info *info, स्थिर अक्षर *func)
अणु
	पूर्णांक corruption = 0;
	अगर (info->magic_start != MAGIC) अणु
		prपूर्णांकk(KERN_CRIT "FAS216 Error: magic at start corrupted\n");
		corruption++;
	पूर्ण
	अगर (info->magic_end != MAGIC) अणु
		prपूर्णांकk(KERN_CRIT "FAS216 Error: magic at end corrupted\n");
		corruption++;
	पूर्ण
	अगर (corruption) अणु
		fas216_dumpinfo(info);
		panic("scsi memory space corrupted in %s", func);
	पूर्ण
पूर्ण
#घोषणा fas216_checkmagic(info) __fas216_checkmagic((info), __func__)
#अन्यथा
#घोषणा fas216_checkmagic(info)
#पूर्ण_अगर

अटल स्थिर अक्षर *fas216_bus_phase(पूर्णांक stat)
अणु
	अटल स्थिर अक्षर *phases[] = अणु
		"DATA OUT", "DATA IN",
		"COMMAND", "STATUS",
		"MISC OUT", "MISC IN",
		"MESG OUT", "MESG IN"
	पूर्ण;

	वापस phases[stat & STAT_BUSMASK];
पूर्ण

अटल स्थिर अक्षर *fas216_drv_phase(FAS216_Info *info)
अणु
	अटल स्थिर अक्षर *phases[] = अणु
		[PHASE_IDLE]		= "idle",
		[PHASE_SELECTION]	= "selection",
		[PHASE_COMMAND]		= "command",
		[PHASE_DATAOUT]		= "data out",
		[PHASE_DATAIN]		= "data in",
		[PHASE_MSGIN]		= "message in",
		[PHASE_MSGIN_DISCONNECT]= "disconnect",
		[PHASE_MSGOUT_EXPECT]	= "expect message out",
		[PHASE_MSGOUT]		= "message out",
		[PHASE_STATUS]		= "status",
		[PHASE_DONE]		= "done",
	पूर्ण;

	अगर (info->scsi.phase < ARRAY_SIZE(phases) &&
	    phases[info->scsi.phase])
		वापस phases[info->scsi.phase];
	वापस "???";
पूर्ण

अटल अक्षर fas216_target(FAS216_Info *info)
अणु
	अगर (info->SCpnt)
		वापस '0' + info->SCpnt->device->id;
	अन्यथा
		वापस 'H';
पूर्ण

अटल व्योम
fas216_करो_log(FAS216_Info *info, अक्षर target, अक्षर *fmt, बहु_सूची ap)
अणु
	अटल अक्षर buf[1024];

	vsnम_लिखो(buf, माप(buf), fmt, ap);
	prपूर्णांकk("scsi%d.%c: %s", info->host->host_no, target, buf);
पूर्ण

अटल व्योम fas216_log_command(FAS216_Info *info, पूर्णांक level,
			       काष्ठा scsi_cmnd *SCpnt, अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	अगर (level != 0 && !(level & level_mask))
		वापस;

	बहु_शुरू(args, fmt);
	fas216_करो_log(info, '0' + SCpnt->device->id, fmt, args);
	बहु_पूर्ण(args);

	scsi_prपूर्णांक_command(SCpnt);
पूर्ण

अटल व्योम
fas216_log_target(FAS216_Info *info, पूर्णांक level, पूर्णांक target, अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	अगर (level != 0 && !(level & level_mask))
		वापस;

	अगर (target < 0)
		target = 'H';
	अन्यथा
		target += '0';

	बहु_शुरू(args, fmt);
	fas216_करो_log(info, target, fmt, args);
	बहु_पूर्ण(args);

	prपूर्णांकk("\n");
पूर्ण

अटल व्योम fas216_log(FAS216_Info *info, पूर्णांक level, अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	अगर (level != 0 && !(level & level_mask))
		वापस;

	बहु_शुरू(args, fmt);
	fas216_करो_log(info, fas216_target(info), fmt, args);
	बहु_पूर्ण(args);

	prपूर्णांकk("\n");
पूर्ण

#घोषणा PH_SIZE	32

अटल काष्ठा अणु पूर्णांक stat, ssr, isr, ph; पूर्ण ph_list[PH_SIZE];
अटल पूर्णांक ph_ptr;

अटल व्योम add_debug_list(पूर्णांक stat, पूर्णांक ssr, पूर्णांक isr, पूर्णांक ph)
अणु
	ph_list[ph_ptr].stat = stat;
	ph_list[ph_ptr].ssr = ssr;
	ph_list[ph_ptr].isr = isr;
	ph_list[ph_ptr].ph = ph;

	ph_ptr = (ph_ptr + 1) & (PH_SIZE-1);
पूर्ण

अटल काष्ठा अणु पूर्णांक command; व्योम *from; पूर्ण cmd_list[8];
अटल पूर्णांक cmd_ptr;

अटल व्योम fas216_cmd(FAS216_Info *info, अचिन्हित पूर्णांक command)
अणु
	cmd_list[cmd_ptr].command = command;
	cmd_list[cmd_ptr].from = __builtin_वापस_address(0);

	cmd_ptr = (cmd_ptr + 1) & 7;

	fas216_ग_लिखोb(info, REG_CMD, command);
पूर्ण

अटल व्योम prपूर्णांक_debug_list(व्योम)
अणु
	पूर्णांक i;

	i = ph_ptr;

	prपूर्णांकk(KERN_ERR "SCSI IRQ trail\n");
	करो अणु
		prपूर्णांकk(" %02x:%02x:%02x:%1x",
			ph_list[i].stat, ph_list[i].ssr,
			ph_list[i].isr, ph_list[i].ph);
		i = (i + 1) & (PH_SIZE - 1);
		अगर (((i ^ ph_ptr) & 7) == 0)
			prपूर्णांकk("\n");
	पूर्ण जबतक (i != ph_ptr);
	अगर ((i ^ ph_ptr) & 7)
		prपूर्णांकk("\n");

	i = cmd_ptr;
	prपूर्णांकk(KERN_ERR "FAS216 commands: ");
	करो अणु
		prपूर्णांकk("%02x:%p ", cmd_list[i].command, cmd_list[i].from);
		i = (i + 1) & 7;
	पूर्ण जबतक (i != cmd_ptr);
	prपूर्णांकk("\n");
पूर्ण

अटल व्योम fas216_करोne(FAS216_Info *info, अचिन्हित पूर्णांक result);

/**
 * fas216_get_last_msg - retrive last message from the list
 * @info: पूर्णांकerface to search
 * @pos: current fअगरo position
 *
 * Retrieve a last message from the list, using position in fअगरo.
 */
अटल अंतरभूत अचिन्हित लघु
fas216_get_last_msg(FAS216_Info *info, पूर्णांक pos)
अणु
	अचिन्हित लघु packed_msg = NOP;
	काष्ठा message *msg;
	पूर्णांक msgnr = 0;

	जबतक ((msg = msgqueue_geपंचांगsg(&info->scsi.msgs, msgnr++)) != शून्य) अणु
		अगर (pos >= msg->fअगरo)
			अवरोध;
	पूर्ण

	अगर (msg) अणु
		अगर (msg->msg[0] == EXTENDED_MESSAGE)
			packed_msg = EXTENDED_MESSAGE | msg->msg[2] << 8;
		अन्यथा
			packed_msg = msg->msg[0];
	पूर्ण

	fas216_log(info, LOG_MESSAGES,
		"Message: %04x found at position %02x\n", packed_msg, pos);

	वापस packed_msg;
पूर्ण

/**
 * fas216_syncperiod - calculate STP रेजिस्टर value
 * @info: state काष्ठाure क्रम पूर्णांकerface connected to device
 * @ns: period in ns (between subsequent bytes)
 *
 * Calculate value to be loaded पूर्णांकo the STP रेजिस्टर क्रम a given period
 * in ns. Returns a value suitable क्रम REG_STP.
 */
अटल पूर्णांक fas216_syncperiod(FAS216_Info *info, पूर्णांक ns)
अणु
	पूर्णांक value = (info->अगरcfg.घड़ीrate * ns) / 1000;

	fas216_checkmagic(info);

	अगर (value < 4)
		value = 4;
	अन्यथा अगर (value > 35)
		value = 35;

	वापस value & 31;
पूर्ण

/**
 * fas216_set_sync - setup FAS216 chip क्रम specअगरied transfer period.
 * @info: state काष्ठाure क्रम पूर्णांकerface connected to device
 * @target: target
 *
 * Correctly setup FAS216 chip क्रम specअगरied transfer period.
 * Notes   : we need to चयन the chip out of FASTSCSI mode अगर we have
 *           a transfer period >= 200ns - otherwise the chip will violate
 *           the SCSI timings.
 */
अटल व्योम fas216_set_sync(FAS216_Info *info, पूर्णांक target)
अणु
	अचिन्हित पूर्णांक cntl3;

	fas216_ग_लिखोb(info, REG_SOF, info->device[target].sof);
	fas216_ग_लिखोb(info, REG_STP, info->device[target].stp);

	cntl3 = info->scsi.cfg[2];
	अगर (info->device[target].period >= (200 / 4))
		cntl3 = cntl3 & ~CNTL3_FASTSCSI;

	fas216_ग_लिखोb(info, REG_CNTL3, cntl3);
पूर्ण

/* Synchronous transfer support
 *
 * Note: The SCSI II r10 spec says (5.6.12):
 *
 *  (2)  Due to historical problems with early host adapters that could
 *  not accept an SDTR message, some tarमाला_लो may not initiate synchronous
 *  negotiation after a घातer cycle as required by this standard.  Host
 *  adapters that support synchronous mode may aव्योम the ensuing failure
 *  modes when the target is independently घातer cycled by initiating a
 *  synchronous negotiation on each REQUEST SENSE and INQUIRY command.
 *  This approach increases the SCSI bus overhead and is not recommended
 *  क्रम new implementations.  The correct method is to respond to an
 *  SDTR message with a MESSAGE REJECT message अगर the either the
 *  initiator or target devices करोes not support synchronous transfers
 *  or करोes not want to negotiate क्रम synchronous transfers at the समय.
 *  Using the correct method assures compatibility with wide data
 *  transfers and future enhancements.
 *
 * We will always initiate a synchronous transfer negotiation request on
 * every INQUIRY or REQUEST SENSE message, unless the target itself has
 * at some poपूर्णांक perक्रमmed a synchronous transfer negotiation request, or
 * we have synchronous transfers disabled क्रम this device.
 */

/**
 * fas216_handlesync - Handle a synchronous transfer message
 * @info: state काष्ठाure क्रम पूर्णांकerface
 * @msg: message from target
 *
 * Handle a synchronous transfer message from the target
 */
अटल व्योम fas216_handlesync(FAS216_Info *info, अक्षर *msg)
अणु
	काष्ठा fas216_device *dev = &info->device[info->SCpnt->device->id];
	क्रमागत अणु sync, async, none, reject पूर्ण res = none;

#अगर_घोषित SCSI2_SYNC
	चयन (msg[0]) अणु
	हाल MESSAGE_REJECT:
		/* Synchronous transfer request failed.
		 * Note: SCSI II r10:
		 *
		 *  SCSI devices that are capable of synchronous
		 *  data transfers shall not respond to an SDTR
		 *  message with a MESSAGE REJECT message.
		 *
		 * Hence, अगर we get this condition, we disable
		 * negotiation क्रम this device.
		 */
		अगर (dev->sync_state == neg_inprogress) अणु
			dev->sync_state = neg_invalid;
			res = async;
		पूर्ण
		अवरोध;

	हाल EXTENDED_MESSAGE:
		चयन (dev->sync_state) अणु
		/* We करोn't accept synchronous transfer requests.
		 * Respond with a MESSAGE_REJECT to prevent a
		 * synchronous transfer agreement from being reached.
		 */
		हाल neg_invalid:
			res = reject;
			अवरोध;

		/* We were not negotiating a synchronous transfer,
		 * but the device sent us a negotiation request.
		 * Honour the request by sending back a SDTR
		 * message containing our capability, limited by
		 * the tarमाला_लो capability.
		 */
		शेष:
			fas216_cmd(info, CMD_SETATN);
			अगर (msg[4] > info->अगरcfg.sync_max_depth)
				msg[4] = info->अगरcfg.sync_max_depth;
			अगर (msg[3] < 1000 / info->अगरcfg.घड़ीrate)
				msg[3] = 1000 / info->अगरcfg.घड़ीrate;

			msgqueue_flush(&info->scsi.msgs);
			msgqueue_addmsg(&info->scsi.msgs, 5,
					EXTENDED_MESSAGE, 3, EXTENDED_SDTR,
					msg[3], msg[4]);
			info->scsi.phase = PHASE_MSGOUT_EXPECT;

			/* This is wrong.  The agreement is not in effect
			 * until this message is accepted by the device
			 */
			dev->sync_state = neg_targcomplete;
			res = sync;
			अवरोध;

		/* We initiated the synchronous transfer negotiation,
		 * and have successfully received a response from the
		 * target.  The synchronous transfer agreement has been
		 * reached.  Note: अगर the values वापसed are out of our
		 * bounds, we must reject the message.
		 */
		हाल neg_inprogress:
			res = reject;
			अगर (msg[4] <= info->अगरcfg.sync_max_depth &&
			    msg[3] >= 1000 / info->अगरcfg.घड़ीrate) अणु
				dev->sync_state = neg_complete;
				res = sync;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
#अन्यथा
	res = reject;
#पूर्ण_अगर

	चयन (res) अणु
	हाल sync:
		dev->period = msg[3];
		dev->sof    = msg[4];
		dev->stp    = fas216_syncperiod(info, msg[3] * 4);
		fas216_set_sync(info, info->SCpnt->device->id);
		अवरोध;

	हाल reject:
		fas216_cmd(info, CMD_SETATN);
		msgqueue_flush(&info->scsi.msgs);
		msgqueue_addmsg(&info->scsi.msgs, 1, MESSAGE_REJECT);
		info->scsi.phase = PHASE_MSGOUT_EXPECT;
		fallthrough;

	हाल async:
		dev->period = info->अगरcfg.asyncperiod / 4;
		dev->sof    = 0;
		dev->stp    = info->scsi.async_stp;
		fas216_set_sync(info, info->SCpnt->device->id);
		अवरोध;

	हाल none:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * fas216_updateptrs - update data poपूर्णांकers after transfer suspended/छोड़ोd
 * @info: पूर्णांकerface's local poपूर्णांकer to update
 * @bytes_transferred: number of bytes transferred
 *
 * Update data poपूर्णांकers after transfer suspended/छोड़ोd
 */
अटल व्योम fas216_updateptrs(FAS216_Info *info, पूर्णांक bytes_transferred)
अणु
	काष्ठा scsi_poपूर्णांकer *SCp = &info->scsi.SCp;

	fas216_checkmagic(info);

	BUG_ON(bytes_transferred < 0);

	SCp->phase -= bytes_transferred;

	जबतक (bytes_transferred != 0) अणु
		अगर (SCp->this_residual > bytes_transferred)
			अवरोध;
		/*
		 * We have used up this buffer.  Move on to the
		 * next buffer.
		 */
		bytes_transferred -= SCp->this_residual;
		अगर (!next_SCp(SCp) && bytes_transferred) अणु
			prपूर्णांकk(KERN_WARNING "scsi%d.%c: out of buffers\n",
				info->host->host_no, '0' + info->SCpnt->device->id);
			वापस;
		पूर्ण
	पूर्ण

	SCp->this_residual -= bytes_transferred;
	अगर (SCp->this_residual)
		SCp->ptr += bytes_transferred;
	अन्यथा
		SCp->ptr = शून्य;
पूर्ण

/**
 * fas216_pio - transfer data off of/on to card using programmed IO
 * @info: पूर्णांकerface to transfer data to/from
 * @direction: direction to transfer data (DMA_OUT/DMA_IN)
 *
 * Transfer data off of/on to card using programmed IO.
 * Notes: this is incredibly slow.
 */
अटल व्योम fas216_pio(FAS216_Info *info, fasdmadir_t direction)
अणु
	काष्ठा scsi_poपूर्णांकer *SCp = &info->scsi.SCp;

	fas216_checkmagic(info);

	अगर (direction == DMA_OUT)
		fas216_ग_लिखोb(info, REG_FF, get_next_SCp_byte(SCp));
	अन्यथा
		put_next_SCp_byte(SCp, fas216_पढ़ोb(info, REG_FF));

	अगर (SCp->this_residual == 0)
		next_SCp(SCp);
पूर्ण

अटल व्योम fas216_set_stc(FAS216_Info *info, अचिन्हित पूर्णांक length)
अणु
	fas216_ग_लिखोb(info, REG_STCL, length);
	fas216_ग_लिखोb(info, REG_STCM, length >> 8);
	fas216_ग_लिखोb(info, REG_STCH, length >> 16);
पूर्ण

अटल अचिन्हित पूर्णांक fas216_get_ctc(FAS216_Info *info)
अणु
	वापस fas216_पढ़ोb(info, REG_CTCL) +
	       (fas216_पढ़ोb(info, REG_CTCM) << 8) +
	       (fas216_पढ़ोb(info, REG_CTCH) << 16);
पूर्ण

/**
 * fas216_cleanuptransfer - clean up after a transfer has completed.
 * @info: पूर्णांकerface to clean up
 *
 * Update the data poपूर्णांकers according to the number of bytes transferred
 * on the SCSI bus.
 */
अटल व्योम fas216_cleanuptransfer(FAS216_Info *info)
अणु
	अचिन्हित दीर्घ total, residual, fअगरo;
	fasdmatype_t dmatype = info->dma.transfer_type;

	info->dma.transfer_type = fasdma_none;

	/*
	 * PIO transfers करो not need to be cleaned up.
	 */
	अगर (dmatype == fasdma_pio || dmatype == fasdma_none)
		वापस;

	अगर (dmatype == fasdma_real_all)
		total = info->scsi.SCp.phase;
	अन्यथा
		total = info->scsi.SCp.this_residual;

	residual = fas216_get_ctc(info);

	fअगरo = fas216_पढ़ोb(info, REG_CFIS) & CFIS_CF;

	fas216_log(info, LOG_BUFFER, "cleaning up from previous "
		   "transfer: length 0x%06x, residual 0x%x, fifo %d",
		   total, residual, fअगरo);

	/*
	 * If we were perक्रमming Data-Out, the transfer counter
	 * counts करोwn each समय a byte is transferred by the
	 * host to the FIFO.  This means we must include the
	 * bytes left in the FIFO from the transfer counter.
	 */
	अगर (info->scsi.phase == PHASE_DATAOUT)
		residual += fअगरo;

	fas216_updateptrs(info, total - residual);
पूर्ण

/**
 * fas216_transfer - Perक्रमm a DMA/PIO transfer off of/on to card
 * @info: पूर्णांकerface from which device disconnected from
 *
 * Start a DMA/PIO transfer off of/on to card
 */
अटल व्योम fas216_transfer(FAS216_Info *info)
अणु
	fasdmadir_t direction;
	fasdmatype_t dmatype;

	fas216_log(info, LOG_BUFFER,
		   "starttransfer: buffer %p length 0x%06x reqlen 0x%06x",
		   info->scsi.SCp.ptr, info->scsi.SCp.this_residual,
		   info->scsi.SCp.phase);

	अगर (!info->scsi.SCp.ptr) अणु
		fas216_log(info, LOG_ERROR, "null buffer passed to "
			   "fas216_starttransfer");
		prपूर्णांक_SCp(&info->scsi.SCp, "SCp: ", "\n");
		prपूर्णांक_SCp(&info->SCpnt->SCp, "Cmnd SCp: ", "\n");
		वापस;
	पूर्ण

	/*
	 * If we have a synchronous transfer agreement in effect, we must
	 * use DMA mode.  If we are using asynchronous transfers, we may
	 * use DMA mode or PIO mode.
	 */
	अगर (info->device[info->SCpnt->device->id].sof)
		dmatype = fasdma_real_all;
	अन्यथा
		dmatype = fasdma_pio;

	अगर (info->scsi.phase == PHASE_DATAOUT)
		direction = DMA_OUT;
	अन्यथा
		direction = DMA_IN;

	अगर (info->dma.setup)
		dmatype = info->dma.setup(info->host, &info->scsi.SCp,
					  direction, dmatype);
	info->dma.transfer_type = dmatype;

	अगर (dmatype == fasdma_real_all)
		fas216_set_stc(info, info->scsi.SCp.phase);
	अन्यथा
		fas216_set_stc(info, info->scsi.SCp.this_residual);

	चयन (dmatype) अणु
	हाल fasdma_pio:
		fas216_log(info, LOG_BUFFER, "PIO transfer");
		fas216_ग_लिखोb(info, REG_SOF, 0);
		fas216_ग_लिखोb(info, REG_STP, info->scsi.async_stp);
		fas216_cmd(info, CMD_TRANSFERINFO);
		fas216_pio(info, direction);
		अवरोध;

	हाल fasdma_pseuकरो:
		fas216_log(info, LOG_BUFFER, "pseudo transfer");
		fas216_cmd(info, CMD_TRANSFERINFO | CMD_WITHDMA);
		info->dma.pseuकरो(info->host, &info->scsi.SCp,
				 direction, info->SCpnt->transfersize);
		अवरोध;

	हाल fasdma_real_block:
		fas216_log(info, LOG_BUFFER, "block dma transfer");
		fas216_cmd(info, CMD_TRANSFERINFO | CMD_WITHDMA);
		अवरोध;

	हाल fasdma_real_all:
		fas216_log(info, LOG_BUFFER, "total dma transfer");
		fas216_cmd(info, CMD_TRANSFERINFO | CMD_WITHDMA);
		अवरोध;

	शेष:
		fas216_log(info, LOG_BUFFER | LOG_ERROR,
			   "invalid FAS216 DMA type");
		अवरोध;
	पूर्ण
पूर्ण

/**
 * fas216_stoptransfer - Stop a DMA transfer onto / off of the card
 * @info: पूर्णांकerface from which device disconnected from
 *
 * Called when we चयन away from DATA IN or DATA OUT phases.
 */
अटल व्योम fas216_stoptransfer(FAS216_Info *info)
अणु
	fas216_checkmagic(info);

	अगर (info->dma.transfer_type == fasdma_real_all ||
	    info->dma.transfer_type == fasdma_real_block)
		info->dma.stop(info->host, &info->scsi.SCp);

	fas216_cleanuptransfer(info);

	अगर (info->scsi.phase == PHASE_DATAIN) अणु
		अचिन्हित पूर्णांक fअगरo;

		/*
		 * If we were perक्रमming Data-In, then the FIFO counter
		 * contains the number of bytes not transferred via DMA
		 * from the on-board FIFO.  Read them manually.
		 */
		fअगरo = fas216_पढ़ोb(info, REG_CFIS) & CFIS_CF;
		जबतक (fअगरo && info->scsi.SCp.ptr) अणु
			*info->scsi.SCp.ptr = fas216_पढ़ोb(info, REG_FF);
			fas216_updateptrs(info, 1);
			fअगरo--;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * After a Data-Out phase, there may be unsent
		 * bytes left in the FIFO.  Flush them out.
		 */
		fas216_cmd(info, CMD_FLUSHFIFO);
	पूर्ण
पूर्ण

अटल व्योम fas216_पातtransfer(FAS216_Info *info)
अणु
	fas216_checkmagic(info);

	अगर (info->dma.transfer_type == fasdma_real_all ||
	    info->dma.transfer_type == fasdma_real_block)
		info->dma.stop(info->host, &info->scsi.SCp);

	info->dma.transfer_type = fasdma_none;
	fas216_cmd(info, CMD_FLUSHFIFO);
पूर्ण

अटल व्योम fas216_kick(FAS216_Info *info);

/**
 * fas216_disconnected_पूर्णांकr - handle device disconnection
 * @info: पूर्णांकerface from which device disconnected from
 *
 * Handle device disconnection
 */
अटल व्योम fas216_disconnect_पूर्णांकr(FAS216_Info *info)
अणु
	अचिन्हित दीर्घ flags;

	fas216_checkmagic(info);

	fas216_log(info, LOG_CONNECT, "disconnect phase=%02x",
		   info->scsi.phase);

	msgqueue_flush(&info->scsi.msgs);

	चयन (info->scsi.phase) अणु
	हाल PHASE_SELECTION:			/* जबतक selecting - no target		*/
	हाल PHASE_SELSTEPS:
		fas216_करोne(info, DID_NO_CONNECT);
		अवरोध;

	हाल PHASE_MSGIN_DISCONNECT:		/* message in - disconnecting		*/
		info->scsi.disconnectable = 1;
		info->scsi.phase = PHASE_IDLE;
		info->stats.disconnects += 1;
		spin_lock_irqsave(&info->host_lock, flags);
		अगर (info->scsi.phase == PHASE_IDLE)
			fas216_kick(info);
		spin_unlock_irqrestore(&info->host_lock, flags);
		अवरोध;

	हाल PHASE_DONE:			/* at end of command - complete		*/
		fas216_करोne(info, DID_OK);
		अवरोध;

	हाल PHASE_MSGOUT:			/* message out - possible ABORT message	*/
		अगर (fas216_get_last_msg(info, info->scsi.msgin_fअगरo) == ABORT) अणु
			info->scsi.पातing = 0;
			fas216_करोne(info, DID_ABORT);
			अवरोध;
		पूर्ण
		fallthrough;

	शेष:				/* huh?					*/
		prपूर्णांकk(KERN_ERR "scsi%d.%c: unexpected disconnect in phase %s\n",
			info->host->host_no, fas216_target(info), fas216_drv_phase(info));
		prपूर्णांक_debug_list();
		fas216_stoptransfer(info);
		fas216_करोne(info, DID_ERROR);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * fas216_reselected_पूर्णांकr - start reconnection of a device
 * @info: पूर्णांकerface which was reselected
 *
 * Start reconnection of a device
 */
अटल व्योम
fas216_reselected_पूर्णांकr(FAS216_Info *info)
अणु
	अचिन्हित पूर्णांक cfis, i;
	अचिन्हित अक्षर msg[4];
	अचिन्हित अक्षर target, lun, tag;

	fas216_checkmagic(info);

	WARN_ON(info->scsi.phase == PHASE_SELECTION ||
		info->scsi.phase == PHASE_SELSTEPS);

	cfis = fas216_पढ़ोb(info, REG_CFIS);

	fas216_log(info, LOG_CONNECT, "reconnect phase=%02x cfis=%02x",
		   info->scsi.phase, cfis);

	cfis &= CFIS_CF;

	अगर (cfis < 2 || cfis > 4) अणु
		prपूर्णांकk(KERN_ERR "scsi%d.H: incorrect number of bytes after reselect\n",
			info->host->host_no);
		जाओ bad_message;
	पूर्ण

	क्रम (i = 0; i < cfis; i++)
		msg[i] = fas216_पढ़ोb(info, REG_FF);

	अगर (!(msg[0] & (1 << info->host->this_id)) ||
	    !(msg[1] & 0x80))
		जाओ initiator_error;

	target = msg[0] & ~(1 << info->host->this_id);
	target = ffs(target) - 1;
	lun = msg[1] & 7;
	tag = 0;

	अगर (cfis >= 3) अणु
		अगर (msg[2] != SIMPLE_QUEUE_TAG)
			जाओ initiator_error;

		tag = msg[3];
	पूर्ण

	/* set up क्रम synchronous transfers */
	fas216_ग_लिखोb(info, REG_SDID, target);
	fas216_set_sync(info, target);
	msgqueue_flush(&info->scsi.msgs);

	fas216_log(info, LOG_CONNECT, "Reconnected: target %1x lun %1x tag %02x",
		   target, lun, tag);

	अगर (info->scsi.disconnectable && info->SCpnt) अणु
		info->scsi.disconnectable = 0;
		अगर (info->SCpnt->device->id  == target &&
		    info->SCpnt->device->lun == lun &&
		    info->SCpnt->tag         == tag) अणु
			fas216_log(info, LOG_CONNECT, "reconnected previously executing command");
		पूर्ण अन्यथा अणु
			queue_add_cmd_tail(&info->queues.disconnected, info->SCpnt);
			fas216_log(info, LOG_CONNECT, "had to move command to disconnected queue");
			info->SCpnt = शून्य;
		पूर्ण
	पूर्ण
	अगर (!info->SCpnt) अणु
		info->SCpnt = queue_हटाओ_tgtluntag(&info->queues.disconnected,
					target, lun, tag);
		fas216_log(info, LOG_CONNECT, "had to get command");
	पूर्ण

	अगर (info->SCpnt) अणु
		/*
		 * Restore data poपूर्णांकer from SAVED data poपूर्णांकer
		 */
		info->scsi.SCp = info->SCpnt->SCp;

		fas216_log(info, LOG_CONNECT, "data pointers: [%p, %X]",
			info->scsi.SCp.ptr, info->scsi.SCp.this_residual);
		info->scsi.phase = PHASE_MSGIN;
	पूर्ण अन्यथा अणु
		/*
		 * Our command काष्ठाure not found - पात the
		 * command on the target.  Since we have no
		 * record of this command, we can't send
		 * an INITIATOR DETECTED ERROR message.
		 */
		fas216_cmd(info, CMD_SETATN);

#अगर 0
		अगर (tag)
			msgqueue_addmsg(&info->scsi.msgs, 2, ABORT_TAG, tag);
		अन्यथा
#पूर्ण_अगर
			msgqueue_addmsg(&info->scsi.msgs, 1, ABORT);
		info->scsi.phase = PHASE_MSGOUT_EXPECT;
		info->scsi.पातing = 1;
	पूर्ण

	fas216_cmd(info, CMD_MSGACCEPTED);
	वापस;

 initiator_error:
	prपूर्णांकk(KERN_ERR "scsi%d.H: error during reselection: bytes",
		info->host->host_no);
	क्रम (i = 0; i < cfis; i++)
		prपूर्णांकk(" %02x", msg[i]);
	prपूर्णांकk("\n");
 bad_message:
	fas216_cmd(info, CMD_SETATN);
	msgqueue_flush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, INITIATOR_ERROR);
	info->scsi.phase = PHASE_MSGOUT_EXPECT;
	fas216_cmd(info, CMD_MSGACCEPTED);
पूर्ण

अटल व्योम fas216_parse_message(FAS216_Info *info, अचिन्हित अक्षर *message, पूर्णांक msglen)
अणु
	पूर्णांक i;

	चयन (message[0]) अणु
	हाल COMMAND_COMPLETE:
		अगर (msglen != 1)
			जाओ unrecognised;

		prपूर्णांकk(KERN_ERR "scsi%d.%c: command complete with no "
			"status in MESSAGE_IN?\n",
			info->host->host_no, fas216_target(info));
		अवरोध;

	हाल SAVE_POINTERS:
		अगर (msglen != 1)
			जाओ unrecognised;

		/*
		 * Save current data poपूर्णांकer to SAVED data poपूर्णांकer
		 * SCSI II standard says that we must not acknowledge
		 * this until we have really saved poपूर्णांकers.
		 * NOTE: we DO NOT save the command nor status poपूर्णांकers
		 * as required by the SCSI II standard.  These always
		 * poपूर्णांक to the start of their respective areas.
		 */
		info->SCpnt->SCp = info->scsi.SCp;
		info->SCpnt->SCp.sent_command = 0;
		fas216_log(info, LOG_CONNECT | LOG_MESSAGES | LOG_BUFFER,
			"save data pointers: [%p, %X]",
			info->scsi.SCp.ptr, info->scsi.SCp.this_residual);
		अवरोध;

	हाल RESTORE_POINTERS:
		अगर (msglen != 1)
			जाओ unrecognised;

		/*
		 * Restore current data poपूर्णांकer from SAVED data poपूर्णांकer
		 */
		info->scsi.SCp = info->SCpnt->SCp;
		fas216_log(info, LOG_CONNECT | LOG_MESSAGES | LOG_BUFFER,
			"restore data pointers: [%p, 0x%x]",
			info->scsi.SCp.ptr, info->scsi.SCp.this_residual);
		अवरोध;

	हाल DISCONNECT:
		अगर (msglen != 1)
			जाओ unrecognised;

		info->scsi.phase = PHASE_MSGIN_DISCONNECT;
		अवरोध;

	हाल MESSAGE_REJECT:
		अगर (msglen != 1)
			जाओ unrecognised;

		चयन (fas216_get_last_msg(info, info->scsi.msgin_fअगरo)) अणु
		हाल EXTENDED_MESSAGE | EXTENDED_SDTR << 8:
			fas216_handlesync(info, message);
			अवरोध;

		शेष:
			fas216_log(info, 0, "reject, last message 0x%04x",
				fas216_get_last_msg(info, info->scsi.msgin_fअगरo));
		पूर्ण
		अवरोध;

	हाल NOP:
		अवरोध;

	हाल EXTENDED_MESSAGE:
		अगर (msglen < 3)
			जाओ unrecognised;

		चयन (message[2]) अणु
		हाल EXTENDED_SDTR:	/* Sync transfer negotiation request/reply */
			fas216_handlesync(info, message);
			अवरोध;

		शेष:
			जाओ unrecognised;
		पूर्ण
		अवरोध;

	शेष:
		जाओ unrecognised;
	पूर्ण
	वापस;

unrecognised:
	fas216_log(info, 0, "unrecognised message, rejecting");
	prपूर्णांकk("scsi%d.%c: message was", info->host->host_no, fas216_target(info));
	क्रम (i = 0; i < msglen; i++)
		prपूर्णांकk("%s%02X", i & 31 ? " " : "\n  ", message[i]);
	prपूर्णांकk("\n");

	/*
	 * Something strange seems to be happening here -
	 * I can't use SETATN since the chip gives me an
	 * invalid command पूर्णांकerrupt when I करो.  Weird.
	 */
fas216_cmd(info, CMD_NOP);
fas216_dumpstate(info);
	fas216_cmd(info, CMD_SETATN);
	msgqueue_flush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, MESSAGE_REJECT);
	info->scsi.phase = PHASE_MSGOUT_EXPECT;
fas216_dumpstate(info);
पूर्ण

अटल पूर्णांक fas216_रुको_cmd(FAS216_Info *info, पूर्णांक cmd)
अणु
	पूर्णांक tout;
	पूर्णांक stat;

	fas216_cmd(info, cmd);

	क्रम (tout = 1000; tout; tout -= 1) अणु
		stat = fas216_पढ़ोb(info, REG_STAT);
		अगर (stat & (STAT_INT|STAT_PARITYERROR))
			अवरोध;
		udelay(1);
	पूर्ण

	वापस stat;
पूर्ण

अटल पूर्णांक fas216_get_msg_byte(FAS216_Info *info)
अणु
	अचिन्हित पूर्णांक stat = fas216_रुको_cmd(info, CMD_MSGACCEPTED);

	अगर ((stat & STAT_INT) == 0)
		जाओ समयकरोut;

	अगर ((stat & STAT_BUSMASK) != STAT_MESGIN)
		जाओ unexpected_phase_change;

	fas216_पढ़ोb(info, REG_INST);

	stat = fas216_रुको_cmd(info, CMD_TRANSFERINFO);

	अगर ((stat & STAT_INT) == 0)
		जाओ समयकरोut;

	अगर (stat & STAT_PARITYERROR)
		जाओ parity_error;

	अगर ((stat & STAT_BUSMASK) != STAT_MESGIN)
		जाओ unexpected_phase_change;

	fas216_पढ़ोb(info, REG_INST);

	वापस fas216_पढ़ोb(info, REG_FF);

समयकरोut:
	fas216_log(info, LOG_ERROR, "timed out waiting for message byte");
	वापस -1;

unexpected_phase_change:
	fas216_log(info, LOG_ERROR, "unexpected phase change: status = %02x", stat);
	वापस -2;

parity_error:
	fas216_log(info, LOG_ERROR, "parity error during message in phase");
	वापस -3;
पूर्ण

/**
 * fas216_message - handle a function करोne पूर्णांकerrupt from FAS216 chip
 * @info: पूर्णांकerface which caused function करोne पूर्णांकerrupt
 *
 * Handle a function करोne पूर्णांकerrupt from FAS216 chip
 */
अटल व्योम fas216_message(FAS216_Info *info)
अणु
	अचिन्हित अक्षर *message = info->scsi.message;
	अचिन्हित पूर्णांक msglen = 1;
	पूर्णांक msgbyte = 0;

	fas216_checkmagic(info);

	message[0] = fas216_पढ़ोb(info, REG_FF);

	अगर (message[0] == EXTENDED_MESSAGE) अणु
		msgbyte = fas216_get_msg_byte(info);

		अगर (msgbyte >= 0) अणु
			message[1] = msgbyte;

			क्रम (msglen = 2; msglen < message[1] + 2; msglen++) अणु
				msgbyte = fas216_get_msg_byte(info);

				अगर (msgbyte >= 0)
					message[msglen] = msgbyte;
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (msgbyte == -3)
		जाओ parity_error;

#अगर_घोषित DEBUG_MESSAGES
	अणु
		पूर्णांक i;

		prपूर्णांकk("scsi%d.%c: message in: ",
			info->host->host_no, fas216_target(info));
		क्रम (i = 0; i < msglen; i++)
			prपूर्णांकk("%02X ", message[i]);
		prपूर्णांकk("\n");
	पूर्ण
#पूर्ण_अगर

	fas216_parse_message(info, message, msglen);
	fas216_cmd(info, CMD_MSGACCEPTED);
	वापस;

parity_error:
	fas216_cmd(info, CMD_SETATN);
	msgqueue_flush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, MSG_PARITY_ERROR);
	info->scsi.phase = PHASE_MSGOUT_EXPECT;
	fas216_cmd(info, CMD_MSGACCEPTED);
	वापस;
पूर्ण

/**
 * fas216_send_command - send command after all message bytes have been sent
 * @info: पूर्णांकerface which caused bus service
 *
 * Send a command to a target after all message bytes have been sent
 */
अटल व्योम fas216_send_command(FAS216_Info *info)
अणु
	पूर्णांक i;

	fas216_checkmagic(info);

	fas216_cmd(info, CMD_NOP|CMD_WITHDMA);
	fas216_cmd(info, CMD_FLUSHFIFO);

	/* load command */
	क्रम (i = info->scsi.SCp.sent_command; i < info->SCpnt->cmd_len; i++)
		fas216_ग_लिखोb(info, REG_FF, info->SCpnt->cmnd[i]);

	fas216_cmd(info, CMD_TRANSFERINFO);

	info->scsi.phase = PHASE_COMMAND;
पूर्ण

/**
 * fas216_send_messageout - handle bus service to send a message
 * @info: पूर्णांकerface which caused bus service
 *
 * Handle bus service to send a message.
 * Note: We करो not allow the device to change the data direction!
 */
अटल व्योम fas216_send_messageout(FAS216_Info *info, पूर्णांक start)
अणु
	अचिन्हित पूर्णांक tot_msglen = msgqueue_msglength(&info->scsi.msgs);

	fas216_checkmagic(info);

	fas216_cmd(info, CMD_FLUSHFIFO);

	अगर (tot_msglen) अणु
		काष्ठा message *msg;
		पूर्णांक msgnr = 0;

		जबतक ((msg = msgqueue_geपंचांगsg(&info->scsi.msgs, msgnr++)) != शून्य) अणु
			पूर्णांक i;

			क्रम (i = start; i < msg->length; i++)
				fas216_ग_लिखोb(info, REG_FF, msg->msg[i]);

			msg->fअगरo = tot_msglen - (fas216_पढ़ोb(info, REG_CFIS) & CFIS_CF);
			start = 0;
		पूर्ण
	पूर्ण अन्यथा
		fas216_ग_लिखोb(info, REG_FF, NOP);

	fas216_cmd(info, CMD_TRANSFERINFO);

	info->scsi.phase = PHASE_MSGOUT;
पूर्ण

/**
 * fas216_busservice_पूर्णांकr - handle bus service पूर्णांकerrupt from FAS216 chip
 * @info: पूर्णांकerface which caused bus service पूर्णांकerrupt
 * @stat: Status रेजिस्टर contents
 * @is: SCSI Status रेजिस्टर contents
 *
 * Handle a bus service पूर्णांकerrupt from FAS216 chip
 */
अटल व्योम fas216_busservice_पूर्णांकr(FAS216_Info *info, अचिन्हित पूर्णांक stat, अचिन्हित पूर्णांक is)
अणु
	fas216_checkmagic(info);

	fas216_log(info, LOG_BUSSERVICE,
		   "bus service: stat=%02x is=%02x phase=%02x",
		   stat, is, info->scsi.phase);

	चयन (info->scsi.phase) अणु
	हाल PHASE_SELECTION:
		अगर ((is & IS_BITS) != IS_MSGBYTESENT)
			जाओ bad_is;
		अवरोध;

	हाल PHASE_SELSTEPS:
		चयन (is & IS_BITS) अणु
		हाल IS_SELARB:
		हाल IS_MSGBYTESENT:
			जाओ bad_is;

		हाल IS_NOTCOMMAND:
		हाल IS_EARLYPHASE:
			अगर ((stat & STAT_BUSMASK) == STAT_MESGIN)
				अवरोध;
			जाओ bad_is;

		हाल IS_COMPLETE:
			अवरोध;
		पूर्ण

	शेष:
		अवरोध;
	पूर्ण

	fas216_cmd(info, CMD_NOP);

#घोषणा STATE(st,ph) ((ph) << 3 | (st))
	/* This table describes the legal SCSI state transitions,
	 * as described by the SCSI II spec.
	 */
	चयन (STATE(stat & STAT_BUSMASK, info->scsi.phase)) अणु
	हाल STATE(STAT_DATAIN, PHASE_SELSTEPS):/* Sel w/ steps -> Data In      */
	हाल STATE(STAT_DATAIN, PHASE_MSGOUT):  /* Message Out  -> Data In      */
	हाल STATE(STAT_DATAIN, PHASE_COMMAND): /* Command      -> Data In      */
	हाल STATE(STAT_DATAIN, PHASE_MSGIN):   /* Message In   -> Data In      */
		info->scsi.phase = PHASE_DATAIN;
		fas216_transfer(info);
		वापस;

	हाल STATE(STAT_DATAIN, PHASE_DATAIN):  /* Data In      -> Data In      */
	हाल STATE(STAT_DATAOUT, PHASE_DATAOUT):/* Data Out     -> Data Out     */
		fas216_cleanuptransfer(info);
		fas216_transfer(info);
		वापस;

	हाल STATE(STAT_DATAOUT, PHASE_SELSTEPS):/* Sel w/ steps-> Data Out     */
	हाल STATE(STAT_DATAOUT, PHASE_MSGOUT): /* Message Out  -> Data Out     */
	हाल STATE(STAT_DATAOUT, PHASE_COMMAND):/* Command      -> Data Out     */
	हाल STATE(STAT_DATAOUT, PHASE_MSGIN):  /* Message In   -> Data Out     */
		fas216_cmd(info, CMD_FLUSHFIFO);
		info->scsi.phase = PHASE_DATAOUT;
		fas216_transfer(info);
		वापस;

	हाल STATE(STAT_STATUS, PHASE_DATAOUT): /* Data Out     -> Status       */
	हाल STATE(STAT_STATUS, PHASE_DATAIN):  /* Data In      -> Status       */
		fas216_stoptransfer(info);
		fallthrough;

	हाल STATE(STAT_STATUS, PHASE_SELSTEPS):/* Sel w/ steps -> Status       */
	हाल STATE(STAT_STATUS, PHASE_MSGOUT):  /* Message Out  -> Status       */
	हाल STATE(STAT_STATUS, PHASE_COMMAND): /* Command      -> Status       */
	हाल STATE(STAT_STATUS, PHASE_MSGIN):   /* Message In   -> Status       */
		fas216_cmd(info, CMD_INITCMDCOMPLETE);
		info->scsi.phase = PHASE_STATUS;
		वापस;

	हाल STATE(STAT_MESGIN, PHASE_DATAOUT): /* Data Out     -> Message In   */
	हाल STATE(STAT_MESGIN, PHASE_DATAIN):  /* Data In      -> Message In   */
		fas216_stoptransfer(info);
		fallthrough;

	हाल STATE(STAT_MESGIN, PHASE_COMMAND):	/* Command	-> Message In	*/
	हाल STATE(STAT_MESGIN, PHASE_SELSTEPS):/* Sel w/ steps -> Message In   */
	हाल STATE(STAT_MESGIN, PHASE_MSGOUT):  /* Message Out  -> Message In   */
		info->scsi.msgin_fअगरo = fas216_पढ़ोb(info, REG_CFIS) & CFIS_CF;
		fas216_cmd(info, CMD_FLUSHFIFO);
		fas216_cmd(info, CMD_TRANSFERINFO);
		info->scsi.phase = PHASE_MSGIN;
		वापस;

	हाल STATE(STAT_MESGIN, PHASE_MSGIN):
		info->scsi.msgin_fअगरo = fas216_पढ़ोb(info, REG_CFIS) & CFIS_CF;
		fas216_cmd(info, CMD_TRANSFERINFO);
		वापस;

	हाल STATE(STAT_COMMAND, PHASE_MSGOUT): /* Message Out  -> Command      */
	हाल STATE(STAT_COMMAND, PHASE_MSGIN):  /* Message In   -> Command      */
		fas216_send_command(info);
		info->scsi.phase = PHASE_COMMAND;
		वापस;


	/*
	 * Selection    -> Message Out
	 */
	हाल STATE(STAT_MESGOUT, PHASE_SELECTION):
		fas216_send_messageout(info, 1);
		वापस;

	/*
	 * Message Out  -> Message Out
	 */
	हाल STATE(STAT_MESGOUT, PHASE_SELSTEPS):
	हाल STATE(STAT_MESGOUT, PHASE_MSGOUT):
		/*
		 * If we get another message out phase, this usually
		 * means some parity error occurred.  Resend complete
		 * set of messages.  If we have more than one byte to
		 * send, we need to निश्चित ATN again.
		 */
		अगर (info->device[info->SCpnt->device->id].parity_check) अणु
			/*
			 * We were testing... good, the device
			 * supports parity checking.
			 */
			info->device[info->SCpnt->device->id].parity_check = 0;
			info->device[info->SCpnt->device->id].parity_enabled = 1;
			fas216_ग_लिखोb(info, REG_CNTL1, info->scsi.cfg[0]);
		पूर्ण

		अगर (msgqueue_msglength(&info->scsi.msgs) > 1)
			fas216_cmd(info, CMD_SETATN);
		/*FALLTHROUGH*/

	/*
	 * Any          -> Message Out
	 */
	हाल STATE(STAT_MESGOUT, PHASE_MSGOUT_EXPECT):
		fas216_send_messageout(info, 0);
		वापस;

	/* Error recovery rules.
	 *   These either attempt to पात or retry the operation.
	 * TODO: we need more of these
	 */
	हाल STATE(STAT_COMMAND, PHASE_COMMAND):/* Command      -> Command      */
		/* error - we've sent out all the command bytes
		 * we have.
		 * NOTE: we need SAVE DATA POINTERS/RESTORE DATA POINTERS
		 * to include the command bytes sent क्रम this to work
		 * correctly.
		 */
		prपूर्णांकk(KERN_ERR "scsi%d.%c: "
			"target trying to receive more command bytes\n",
			info->host->host_no, fas216_target(info));
		fas216_cmd(info, CMD_SETATN);
		fas216_set_stc(info, 15);
		fas216_cmd(info, CMD_PADBYTES | CMD_WITHDMA);
		msgqueue_flush(&info->scsi.msgs);
		msgqueue_addmsg(&info->scsi.msgs, 1, INITIATOR_ERROR);
		info->scsi.phase = PHASE_MSGOUT_EXPECT;
		वापस;
	पूर्ण

	अगर (info->scsi.phase == PHASE_MSGIN_DISCONNECT) अणु
		prपूर्णांकk(KERN_ERR "scsi%d.%c: disconnect message received, but bus service %s?\n",
			info->host->host_no, fas216_target(info),
			fas216_bus_phase(stat));
		msgqueue_flush(&info->scsi.msgs);
		fas216_cmd(info, CMD_SETATN);
		msgqueue_addmsg(&info->scsi.msgs, 1, INITIATOR_ERROR);
		info->scsi.phase = PHASE_MSGOUT_EXPECT;
		info->scsi.पातing = 1;
		fas216_cmd(info, CMD_TRANSFERINFO);
		वापस;
	पूर्ण
	prपूर्णांकk(KERN_ERR "scsi%d.%c: bus phase %s after %s?\n",
		info->host->host_no, fas216_target(info),
		fas216_bus_phase(stat),
		fas216_drv_phase(info));
	prपूर्णांक_debug_list();
	वापस;

bad_is:
	fas216_log(info, 0, "bus service at step %d?", is & IS_BITS);
	fas216_dumpstate(info);
	prपूर्णांक_debug_list();

	fas216_करोne(info, DID_ERROR);
पूर्ण

/**
 * fas216_funcकरोne_पूर्णांकr - handle a function करोne पूर्णांकerrupt from FAS216 chip
 * @info: पूर्णांकerface which caused function करोne पूर्णांकerrupt
 * @stat: Status रेजिस्टर contents
 * @is: SCSI Status रेजिस्टर contents
 *
 * Handle a function करोne पूर्णांकerrupt from FAS216 chip
 */
अटल व्योम fas216_funcकरोne_पूर्णांकr(FAS216_Info *info, अचिन्हित पूर्णांक stat, अचिन्हित पूर्णांक is)
अणु
	अचिन्हित पूर्णांक fअगरo_len = fas216_पढ़ोb(info, REG_CFIS) & CFIS_CF;

	fas216_checkmagic(info);

	fas216_log(info, LOG_FUNCTIONDONE,
		   "function done: stat=%02x is=%02x phase=%02x",
		   stat, is, info->scsi.phase);

	चयन (info->scsi.phase) अणु
	हाल PHASE_STATUS:			/* status phase - पढ़ो status and msg	*/
		अगर (fअगरo_len != 2) अणु
			fas216_log(info, 0, "odd number of bytes in FIFO: %d", fअगरo_len);
		पूर्ण
		/*
		 * Read status then message byte.
		 */
		info->scsi.SCp.Status = fas216_पढ़ोb(info, REG_FF);
		info->scsi.SCp.Message = fas216_पढ़ोb(info, REG_FF);
		info->scsi.phase = PHASE_DONE;
		fas216_cmd(info, CMD_MSGACCEPTED);
		अवरोध;

	हाल PHASE_IDLE:
	हाल PHASE_SELECTION:
	हाल PHASE_SELSTEPS:
		अवरोध;

	हाल PHASE_MSGIN:			/* message in phase			*/
		अगर ((stat & STAT_BUSMASK) == STAT_MESGIN) अणु
			info->scsi.msgin_fअगरo = fअगरo_len;
			fas216_message(info);
			अवरोध;
		पूर्ण
		fallthrough;

	शेष:
		fas216_log(info, 0, "internal phase %s for function done?"
			"  What do I do with this?",
			fas216_target(info), fas216_drv_phase(info));
	पूर्ण
पूर्ण

अटल व्योम fas216_bus_reset(FAS216_Info *info)
अणु
	neg_t sync_state;
	पूर्णांक i;

	msgqueue_flush(&info->scsi.msgs);

	sync_state = neg_invalid;

#अगर_घोषित SCSI2_SYNC
	अगर (info->अगरcfg.capabilities & (FASCAP_DMA|FASCAP_PSEUDODMA))
		sync_state = neg_रुको;
#पूर्ण_अगर

	info->scsi.phase = PHASE_IDLE;
	info->SCpnt = शून्य; /* bug! */
	स_रखो(&info->scsi.SCp, 0, माप(info->scsi.SCp));

	क्रम (i = 0; i < 8; i++) अणु
		info->device[i].disconnect_ok	= info->अगरcfg.disconnect_ok;
		info->device[i].sync_state	= sync_state;
		info->device[i].period		= info->अगरcfg.asyncperiod / 4;
		info->device[i].stp		= info->scsi.async_stp;
		info->device[i].sof		= 0;
		info->device[i].wide_xfer	= 0;
	पूर्ण

	info->rst_bus_status = 1;
	wake_up(&info->eh_रुको);
पूर्ण

/**
 * fas216_पूर्णांकr - handle पूर्णांकerrupts to progress a command
 * @info: पूर्णांकerface to service
 *
 * Handle पूर्णांकerrupts from the पूर्णांकerface to progress a command
 */
irqवापस_t fas216_पूर्णांकr(FAS216_Info *info)
अणु
	अचिन्हित अक्षर inst, is, stat;
	पूर्णांक handled = IRQ_NONE;

	fas216_checkmagic(info);

	stat = fas216_पढ़ोb(info, REG_STAT);
	is = fas216_पढ़ोb(info, REG_IS);
	inst = fas216_पढ़ोb(info, REG_INST);

	add_debug_list(stat, is, inst, info->scsi.phase);

	अगर (stat & STAT_INT) अणु
		अगर (inst & INST_BUSRESET) अणु
			fas216_log(info, 0, "bus reset detected");
			fas216_bus_reset(info);
			scsi_report_bus_reset(info->host, 0);
		पूर्ण अन्यथा अगर (inst & INST_ILLEGALCMD) अणु
			fas216_log(info, LOG_ERROR, "illegal command given\n");
			fas216_dumpstate(info);
			prपूर्णांक_debug_list();
		पूर्ण अन्यथा अगर (inst & INST_DISCONNECT)
			fas216_disconnect_पूर्णांकr(info);
		अन्यथा अगर (inst & INST_RESELECTED)	/* reselected			*/
			fas216_reselected_पूर्णांकr(info);
		अन्यथा अगर (inst & INST_BUSSERVICE)	/* bus service request		*/
			fas216_busservice_पूर्णांकr(info, stat, is);
		अन्यथा अगर (inst & INST_FUNCDONE)		/* function करोne		*/
			fas216_funcकरोne_पूर्णांकr(info, stat, is);
		अन्यथा
		    	fas216_log(info, 0, "unknown interrupt received:"
				" phase %s inst %02X is %02X stat %02X",
				fas216_drv_phase(info), inst, is, stat);
		handled = IRQ_HANDLED;
	पूर्ण
	वापस handled;
पूर्ण

अटल व्योम __fas216_start_command(FAS216_Info *info, काष्ठा scsi_cmnd *SCpnt)
अणु
	पूर्णांक tot_msglen;

	/* following what the ESP driver says */
	fas216_set_stc(info, 0);
	fas216_cmd(info, CMD_NOP | CMD_WITHDMA);

	/* flush FIFO */
	fas216_cmd(info, CMD_FLUSHFIFO);

	/* load bus-id and समयout */
	fas216_ग_लिखोb(info, REG_SDID, BUSID(SCpnt->device->id));
	fas216_ग_लिखोb(info, REG_STIM, info->अगरcfg.select_समयout);

	/* synchronous transfers */
	fas216_set_sync(info, SCpnt->device->id);

	tot_msglen = msgqueue_msglength(&info->scsi.msgs);

#अगर_घोषित DEBUG_MESSAGES
	अणु
		काष्ठा message *msg;
		पूर्णांक msgnr = 0, i;

		prपूर्णांकk("scsi%d.%c: message out: ",
			info->host->host_no, '0' + SCpnt->device->id);
		जबतक ((msg = msgqueue_geपंचांगsg(&info->scsi.msgs, msgnr++)) != शून्य) अणु
			prपूर्णांकk("{ ");
			क्रम (i = 0; i < msg->length; i++)
				prपूर्णांकk("%02x ", msg->msg[i]);
			prपूर्णांकk("} ");
		पूर्ण
		prपूर्णांकk("\n");
	पूर्ण
#पूर्ण_अगर

	अगर (tot_msglen == 1 || tot_msglen == 3) अणु
		/*
		 * We have an easy message length to send...
		 */
		काष्ठा message *msg;
		पूर्णांक msgnr = 0, i;

		info->scsi.phase = PHASE_SELSTEPS;

		/* load message bytes */
		जबतक ((msg = msgqueue_geपंचांगsg(&info->scsi.msgs, msgnr++)) != शून्य) अणु
			क्रम (i = 0; i < msg->length; i++)
				fas216_ग_लिखोb(info, REG_FF, msg->msg[i]);
			msg->fअगरo = tot_msglen - (fas216_पढ़ोb(info, REG_CFIS) & CFIS_CF);
		पूर्ण

		/* load command */
		क्रम (i = 0; i < SCpnt->cmd_len; i++)
			fas216_ग_लिखोb(info, REG_FF, SCpnt->cmnd[i]);

		अगर (tot_msglen == 1)
			fas216_cmd(info, CMD_SELECTATN);
		अन्यथा
			fas216_cmd(info, CMD_SELECTATN3);
	पूर्ण अन्यथा अणु
		/*
		 * We have an unusual number of message bytes to send.
		 *  Load first byte पूर्णांकo fअगरo, and issue SELECT with ATN and
		 *  stop steps.
		 */
		काष्ठा message *msg = msgqueue_geपंचांगsg(&info->scsi.msgs, 0);

		fas216_ग_लिखोb(info, REG_FF, msg->msg[0]);
		msg->fअगरo = 1;

		fas216_cmd(info, CMD_SELECTATNSTOP);
	पूर्ण
पूर्ण

/*
 * Decide whether we need to perक्रमm a parity test on this device.
 * Can also be used to क्रमce parity error conditions during initial
 * inक्रमmation transfer phase (message out) क्रम test purposes.
 */
अटल पूर्णांक parity_test(FAS216_Info *info, पूर्णांक target)
अणु
#अगर 0
	अगर (target == 3) अणु
		info->device[target].parity_check = 0;
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	वापस info->device[target].parity_check;
पूर्ण

अटल व्योम fas216_start_command(FAS216_Info *info, काष्ठा scsi_cmnd *SCpnt)
अणु
	पूर्णांक disconnect_ok;

	/*
	 * claim host busy
	 */
	info->scsi.phase = PHASE_SELECTION;
	info->scsi.SCp = SCpnt->SCp;
	info->SCpnt = SCpnt;
	info->dma.transfer_type = fasdma_none;

	अगर (parity_test(info, SCpnt->device->id))
		fas216_ग_लिखोb(info, REG_CNTL1, info->scsi.cfg[0] | CNTL1_PTE);
	अन्यथा
		fas216_ग_लिखोb(info, REG_CNTL1, info->scsi.cfg[0]);

	/*
	 * Don't allow request sense commands to disconnect.
	 */
	disconnect_ok = SCpnt->cmnd[0] != REQUEST_SENSE &&
			info->device[SCpnt->device->id].disconnect_ok;

	/*
	 * build outgoing message bytes
	 */
	msgqueue_flush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, IDENTIFY(disconnect_ok, SCpnt->device->lun));

	/*
	 * add tag message अगर required
	 */
	अगर (SCpnt->tag)
		msgqueue_addmsg(&info->scsi.msgs, 2, SIMPLE_QUEUE_TAG, SCpnt->tag);

	करो अणु
#अगर_घोषित SCSI2_SYNC
		अगर ((info->device[SCpnt->device->id].sync_state == neg_रुको ||
		     info->device[SCpnt->device->id].sync_state == neg_complete) &&
		    (SCpnt->cmnd[0] == REQUEST_SENSE ||
		     SCpnt->cmnd[0] == INQUIRY)) अणु
			info->device[SCpnt->device->id].sync_state = neg_inprogress;
			msgqueue_addmsg(&info->scsi.msgs, 5,
					EXTENDED_MESSAGE, 3, EXTENDED_SDTR,
					1000 / info->अगरcfg.घड़ीrate,
					info->अगरcfg.sync_max_depth);
			अवरोध;
		पूर्ण
#पूर्ण_अगर
	पूर्ण जबतक (0);

	__fas216_start_command(info, SCpnt);
पूर्ण

अटल व्योम fas216_allocate_tag(FAS216_Info *info, काष्ठा scsi_cmnd *SCpnt)
अणु
#अगर_घोषित SCSI2_TAG
	/*
	 * tagged queuing - allocate a new tag to this command
	 */
	अगर (SCpnt->device->simple_tags && SCpnt->cmnd[0] != REQUEST_SENSE &&
	    SCpnt->cmnd[0] != INQUIRY) अणु
	    SCpnt->device->current_tag += 1;
		अगर (SCpnt->device->current_tag == 0)
		    SCpnt->device->current_tag = 1;
			SCpnt->tag = SCpnt->device->current_tag;
	पूर्ण अन्यथा
#पूर्ण_अगर
		set_bit(SCpnt->device->id * 8 +
			(u8)(SCpnt->device->lun & 0x7), info->busyluns);

	info->stats.हटाओs += 1;
	चयन (SCpnt->cmnd[0]) अणु
	हाल WRITE_6:
	हाल WRITE_10:
	हाल WRITE_12:
		info->stats.ग_लिखोs += 1;
		अवरोध;
	हाल READ_6:
	हाल READ_10:
	हाल READ_12:
		info->stats.पढ़ोs += 1;
		अवरोध;
	शेष:
		info->stats.miscs += 1;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fas216_करो_bus_device_reset(FAS216_Info *info,
				       काष्ठा scsi_cmnd *SCpnt)
अणु
	काष्ठा message *msg;

	/*
	 * claim host busy
	 */
	info->scsi.phase = PHASE_SELECTION;
	info->scsi.SCp = SCpnt->SCp;
	info->SCpnt = SCpnt;
	info->dma.transfer_type = fasdma_none;

	fas216_log(info, LOG_ERROR, "sending bus device reset");

	msgqueue_flush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, BUS_DEVICE_RESET);

	/* following what the ESP driver says */
	fas216_set_stc(info, 0);
	fas216_cmd(info, CMD_NOP | CMD_WITHDMA);

	/* flush FIFO */
	fas216_cmd(info, CMD_FLUSHFIFO);

	/* load bus-id and समयout */
	fas216_ग_लिखोb(info, REG_SDID, BUSID(SCpnt->device->id));
	fas216_ग_लिखोb(info, REG_STIM, info->अगरcfg.select_समयout);

	/* synchronous transfers */
	fas216_set_sync(info, SCpnt->device->id);

	msg = msgqueue_geपंचांगsg(&info->scsi.msgs, 0);

	fas216_ग_लिखोb(info, REG_FF, BUS_DEVICE_RESET);
	msg->fअगरo = 1;

	fas216_cmd(info, CMD_SELECTATNSTOP);
पूर्ण

/**
 * fas216_kick - kick a command to the पूर्णांकerface
 * @info: our host पूर्णांकerface to kick
 *
 * Kick a command to the पूर्णांकerface, पूर्णांकerface should be idle.
 * Notes: Interrupts are always disabled!
 */
अटल व्योम fas216_kick(FAS216_Info *info)
अणु
	काष्ठा scsi_cmnd *SCpnt = शून्य;
#घोषणा TYPE_OTHER	0
#घोषणा TYPE_RESET	1
#घोषणा TYPE_QUEUE	2
	पूर्णांक where_from = TYPE_OTHER;

	fas216_checkmagic(info);

	/*
	 * Obtain the next command to process.
	 */
	करो अणु
		अगर (info->rstSCpnt) अणु
			SCpnt = info->rstSCpnt;
			/* करोn't हटाओ it */
			where_from = TYPE_RESET;
			अवरोध;
		पूर्ण

		अगर (info->reqSCpnt) अणु
			SCpnt = info->reqSCpnt;
			info->reqSCpnt = शून्य;
			अवरोध;
		पूर्ण

		अगर (info->origSCpnt) अणु
			SCpnt = info->origSCpnt;
			info->origSCpnt = शून्य;
			अवरोध;
		पूर्ण

		/* retrieve next command */
		अगर (!SCpnt) अणु
			SCpnt = queue_हटाओ_exclude(&info->queues.issue,
						     info->busyluns);
			where_from = TYPE_QUEUE;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (0);

	अगर (!SCpnt) अणु
		/*
		 * no command pending, so enable reselection.
		 */
		fas216_cmd(info, CMD_ENABLESEL);
		वापस;
	पूर्ण

	/*
	 * We're going to start a command, so disable reselection
	 */
	fas216_cmd(info, CMD_DISABLESEL);

	अगर (info->scsi.disconnectable && info->SCpnt) अणु
		fas216_log(info, LOG_CONNECT,
			"moved command for %d to disconnected queue",
			info->SCpnt->device->id);
		queue_add_cmd_tail(&info->queues.disconnected, info->SCpnt);
		info->scsi.disconnectable = 0;
		info->SCpnt = शून्य;
	पूर्ण

	fas216_log_command(info, LOG_CONNECT | LOG_MESSAGES, SCpnt,
			   "starting");

	चयन (where_from) अणु
	हाल TYPE_QUEUE:
		fas216_allocate_tag(info, SCpnt);
		fallthrough;
	हाल TYPE_OTHER:
		fas216_start_command(info, SCpnt);
		अवरोध;
	हाल TYPE_RESET:
		fas216_करो_bus_device_reset(info, SCpnt);
		अवरोध;
	पूर्ण

	fas216_log(info, LOG_CONNECT, "select: data pointers [%p, %X]",
		info->scsi.SCp.ptr, info->scsi.SCp.this_residual);

	/*
	 * should now get either DISCONNECT or
	 * (FUNCTION DONE with BUS SERVICE) पूर्णांकerrupt
	 */
पूर्ण

/*
 * Clean up from issuing a BUS DEVICE RESET message to a device.
 */
अटल व्योम fas216_devicereset_करोne(FAS216_Info *info, काष्ठा scsi_cmnd *SCpnt,
				    अचिन्हित पूर्णांक result)
अणु
	fas216_log(info, LOG_ERROR, "fas216 device reset complete");

	info->rstSCpnt = शून्य;
	info->rst_dev_status = 1;
	wake_up(&info->eh_रुको);
पूर्ण

/**
 * fas216_rq_sns_करोne - Finish processing स्वतःmatic request sense command
 * @info: पूर्णांकerface that completed
 * @SCpnt: command that completed
 * @result: driver byte of result
 *
 * Finish processing स्वतःmatic request sense command
 */
अटल व्योम fas216_rq_sns_करोne(FAS216_Info *info, काष्ठा scsi_cmnd *SCpnt,
			       अचिन्हित पूर्णांक result)
अणु
	fas216_log_target(info, LOG_CONNECT, SCpnt->device->id,
		   "request sense complete, result=0x%04x%02x%02x",
		   result, SCpnt->SCp.Message, SCpnt->SCp.Status);

	अगर (result != DID_OK || SCpnt->SCp.Status != GOOD)
		/*
		 * Something went wrong.  Make sure that we करोn't
		 * have valid data in the sense buffer that could
		 * confuse the higher levels.
		 */
		स_रखो(SCpnt->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
//prपूर्णांकk("scsi%d.%c: sense buffer: ", info->host->host_no, '0' + SCpnt->device->id);
//अणु पूर्णांक i; क्रम (i = 0; i < 32; i++) prपूर्णांकk("%02x ", SCpnt->sense_buffer[i]); prपूर्णांकk("\n"); पूर्ण
	/*
	 * Note that we करोn't set SCpnt->result, since that should
	 * reflect the status of the command that we were asked by
	 * the upper layers to process.  This would have been set
	 * correctly by fas216_std_करोne.
	 */
	scsi_eh_restore_cmnd(SCpnt, &info->ses);
	SCpnt->scsi_करोne(SCpnt);
पूर्ण

/**
 * fas216_std_करोne - finish processing of standard command
 * @info: पूर्णांकerface that completed
 * @SCpnt: command that completed
 * @result: driver byte of result
 *
 * Finish processing of standard command
 */
अटल व्योम
fas216_std_करोne(FAS216_Info *info, काष्ठा scsi_cmnd *SCpnt, अचिन्हित पूर्णांक result)
अणु
	info->stats.fins += 1;

	SCpnt->result = result << 16 | info->scsi.SCp.Message << 8 |
			info->scsi.SCp.Status;

	fas216_log_command(info, LOG_CONNECT, SCpnt,
		"command complete, result=0x%08x", SCpnt->result);

	/*
	 * If the driver detected an error, we're all करोne.
	 */
	अगर (host_byte(SCpnt->result) != DID_OK ||
	    msg_byte(SCpnt->result) != COMMAND_COMPLETE)
		जाओ करोne;

	/*
	 * If the command वापसed CHECK_CONDITION or COMMAND_TERMINATED
	 * status, request the sense inक्रमmation.
	 */
	अगर (status_byte(SCpnt->result) == CHECK_CONDITION ||
	    status_byte(SCpnt->result) == COMMAND_TERMINATED)
		जाओ request_sense;

	/*
	 * If the command did not complete with GOOD status,
	 * we are all करोne here.
	 */
	अगर (status_byte(SCpnt->result) != GOOD)
		जाओ करोne;

	/*
	 * We have successfully completed a command.  Make sure that
	 * we करो not have any buffers left to transfer.  The world
	 * is not perfect, and we seem to occasionally hit this.
	 * It can be indicative of a buggy driver, target or the upper
	 * levels of the SCSI code.
	 */
	अगर (info->scsi.SCp.ptr) अणु
		चयन (SCpnt->cmnd[0]) अणु
		हाल INQUIRY:
		हाल START_STOP:
		हाल MODE_SENSE:
			अवरोध;

		शेष:
			scmd_prपूर्णांकk(KERN_ERR, SCpnt,
				    "incomplete data transfer detected: res=%08X ptr=%p len=%X\n",
				    SCpnt->result, info->scsi.SCp.ptr,
				    info->scsi.SCp.this_residual);
			scsi_prपूर्णांक_command(SCpnt);
			set_host_byte(SCpnt, DID_ERROR);
			जाओ request_sense;
		पूर्ण
	पूर्ण

करोne:
	अगर (SCpnt->scsi_करोne) अणु
		SCpnt->scsi_करोne(SCpnt);
		वापस;
	पूर्ण

	panic("scsi%d.H: null scsi_done function in fas216_done",
		info->host->host_no);


request_sense:
	अगर (SCpnt->cmnd[0] == REQUEST_SENSE)
		जाओ करोne;

	scsi_eh_prep_cmnd(SCpnt, &info->ses, शून्य, 0, ~0);
	fas216_log_target(info, LOG_CONNECT, SCpnt->device->id,
			  "requesting sense");
	init_SCp(SCpnt);
	SCpnt->SCp.Message = 0;
	SCpnt->SCp.Status = 0;
	SCpnt->tag = 0;
	SCpnt->host_scribble = (व्योम *)fas216_rq_sns_करोne;

	/*
	 * Place this command पूर्णांकo the high priority "request
	 * sense" slot.  This will be the very next command
	 * executed, unless a target connects to us.
	 */
	अगर (info->reqSCpnt)
		prपूर्णांकk(KERN_WARNING "scsi%d.%c: losing request command\n",
			info->host->host_no, '0' + SCpnt->device->id);
	info->reqSCpnt = SCpnt;
पूर्ण

/**
 * fas216_करोne - complete processing क्रम current command
 * @info: पूर्णांकerface that completed
 * @result: driver byte of result
 *
 * Complete processing क्रम current command
 */
अटल व्योम fas216_करोne(FAS216_Info *info, अचिन्हित पूर्णांक result)
अणु
	व्योम (*fn)(FAS216_Info *, काष्ठा scsi_cmnd *, अचिन्हित पूर्णांक);
	काष्ठा scsi_cmnd *SCpnt;
	अचिन्हित दीर्घ flags;

	fas216_checkmagic(info);

	अगर (!info->SCpnt)
		जाओ no_command;

	SCpnt = info->SCpnt;
	info->SCpnt = शून्य;
    	info->scsi.phase = PHASE_IDLE;

	अगर (info->scsi.पातing) अणु
		fas216_log(info, 0, "uncaught abort - returning DID_ABORT");
		result = DID_ABORT;
		info->scsi.पातing = 0;
	पूर्ण

	/*
	 * Sanity check the completion - अगर we have zero bytes left
	 * to transfer, we should not have a valid poपूर्णांकer.
	 */
	अगर (info->scsi.SCp.ptr && info->scsi.SCp.this_residual == 0) अणु
		scmd_prपूर्णांकk(KERN_INFO, SCpnt,
			    "zero bytes left to transfer, but buffer pointer still valid: ptr=%p len=%08x\n",
			    info->scsi.SCp.ptr, info->scsi.SCp.this_residual);
		info->scsi.SCp.ptr = शून्य;
		scsi_prपूर्णांक_command(SCpnt);
	पूर्ण

	/*
	 * Clear करोwn this command as completed.  If we need to request
	 * the sense inक्रमmation, fas216_kick will re-निश्चित the busy
	 * status.
	 */
	info->device[SCpnt->device->id].parity_check = 0;
	clear_bit(SCpnt->device->id * 8 +
		  (u8)(SCpnt->device->lun & 0x7), info->busyluns);

	fn = (व्योम (*)(FAS216_Info *, काष्ठा scsi_cmnd *, अचिन्हित पूर्णांक))SCpnt->host_scribble;
	fn(info, SCpnt, result);

	अगर (info->scsi.irq) अणु
		spin_lock_irqsave(&info->host_lock, flags);
		अगर (info->scsi.phase == PHASE_IDLE)
			fas216_kick(info);
		spin_unlock_irqrestore(&info->host_lock, flags);
	पूर्ण
	वापस;

no_command:
	panic("scsi%d.H: null command in fas216_done",
		info->host->host_no);
पूर्ण

/**
 * fas216_queue_command - queue a command क्रम adapter to process.
 * @SCpnt: Command to queue
 * @करोne: करोne function to call once command is complete
 *
 * Queue a command क्रम adapter to process.
 * Returns: 0 on success, अन्यथा error.
 * Notes: io_request_lock is held, पूर्णांकerrupts are disabled.
 */
अटल पूर्णांक fas216_queue_command_lck(काष्ठा scsi_cmnd *SCpnt,
			 व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;
	पूर्णांक result;

	fas216_checkmagic(info);

	fas216_log_command(info, LOG_CONNECT, SCpnt,
			   "received command (%p)", SCpnt);

	SCpnt->scsi_करोne = करोne;
	SCpnt->host_scribble = (व्योम *)fas216_std_करोne;
	SCpnt->result = 0;

	init_SCp(SCpnt);

	info->stats.queues += 1;
	SCpnt->tag = 0;

	spin_lock(&info->host_lock);

	/*
	 * Add command पूर्णांकo execute queue and let it complete under
	 * whatever scheme we're using.
	 */
	result = !queue_add_cmd_ordered(&info->queues.issue, SCpnt);

	/*
	 * If we successfully added the command,
	 * kick the पूर्णांकerface to get it moving.
	 */
	अगर (result == 0 && info->scsi.phase == PHASE_IDLE)
		fas216_kick(info);
	spin_unlock(&info->host_lock);

	fas216_log_target(info, LOG_CONNECT, -1, "queue %s",
		result ? "failure" : "success");

	वापस result;
पूर्ण

DEF_SCSI_QCMD(fas216_queue_command)

/**
 * fas216_पूर्णांकernal_करोne - trigger restart of a रुकोing thपढ़ो in fas216_noqueue_command
 * @SCpnt: Command to wake
 *
 * Trigger restart of a रुकोing thपढ़ो in fas216_command
 */
अटल व्योम fas216_पूर्णांकernal_करोne(काष्ठा scsi_cmnd *SCpnt)
अणु
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;

	fas216_checkmagic(info);

	info->पूर्णांकernal_करोne = 1;
पूर्ण

/**
 * fas216_noqueue_command - process a command क्रम the adapter.
 * @SCpnt: Command to queue
 *
 * Queue a command क्रम adapter to process.
 * Returns: scsi result code.
 * Notes: io_request_lock is held, पूर्णांकerrupts are disabled.
 */
अटल पूर्णांक fas216_noqueue_command_lck(काष्ठा scsi_cmnd *SCpnt,
			   व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;

	fas216_checkmagic(info);

	/*
	 * We should only be using this अगर we करोn't have an पूर्णांकerrupt.
	 * Provide some "incentive" to use the queueing code.
	 */
	BUG_ON(info->scsi.irq);

	info->पूर्णांकernal_करोne = 0;
	fas216_queue_command_lck(SCpnt, fas216_पूर्णांकernal_करोne);

	/*
	 * This wastes समय, since we can't वापस until the command is
	 * complete. We can't sleep either since we may get re-entered!
	 * However, we must re-enable पूर्णांकerrupts, or अन्यथा we'll be
	 * रुकोing क्रमever.
	 */
	spin_unlock_irq(info->host->host_lock);

	जबतक (!info->पूर्णांकernal_करोne) अणु
		/*
		 * If we करोn't have an IRQ, then we must poll the card क्रम
		 * it's interrupt, and use that to call this driver's
		 * पूर्णांकerrupt routine.  That way, we keep the command
		 * progressing.  Maybe we can add some पूर्णांकelligence here
		 * and go to sleep अगर we know that the device is going
		 * to be some समय (eg, disconnected).
		 */
		अगर (fas216_पढ़ोb(info, REG_STAT) & STAT_INT) अणु
			spin_lock_irq(info->host->host_lock);
			fas216_पूर्णांकr(info);
			spin_unlock_irq(info->host->host_lock);
		पूर्ण
	पूर्ण

	spin_lock_irq(info->host->host_lock);

	करोne(SCpnt);

	वापस 0;
पूर्ण

DEF_SCSI_QCMD(fas216_noqueue_command)

/*
 * Error handler समयout function.  Indicate that we समयd out,
 * and wake up any error handler process so it can जारी.
 */
अटल व्योम fas216_eh_समयr(काष्ठा समयr_list *t)
अणु
	FAS216_Info *info = from_समयr(info, t, eh_समयr);

	fas216_log(info, LOG_ERROR, "error handling timed out\n");

	del_समयr(&info->eh_समयr);

	अगर (info->rst_bus_status == 0)
		info->rst_bus_status = -1;
	अगर (info->rst_dev_status == 0)
		info->rst_dev_status = -1;

	wake_up(&info->eh_रुको);
पूर्ण

क्रमागत res_find अणु
	res_failed,		/* not found			*/
	res_success,		/* command on issue queue	*/
	res_hw_पात		/* command on disconnected dev	*/
पूर्ण;

/**
 * fas216_करो_पात - decide how to पात a command
 * @SCpnt: command to पात
 *
 * Decide how to पात a command.
 * Returns: पात status
 */
अटल क्रमागत res_find fas216_find_command(FAS216_Info *info,
					 काष्ठा scsi_cmnd *SCpnt)
अणु
	क्रमागत res_find res = res_failed;

	अगर (queue_हटाओ_cmd(&info->queues.issue, SCpnt)) अणु
		/*
		 * The command was on the issue queue, and has not been
		 * issued yet.  We can हटाओ the command from the queue,
		 * and acknowledge the पात.  Neither the device nor the
		 * पूर्णांकerface know about the command.
		 */
		prपूर्णांकk("on issue queue ");

		res = res_success;
	पूर्ण अन्यथा अगर (queue_हटाओ_cmd(&info->queues.disconnected, SCpnt)) अणु
		/*
		 * The command was on the disconnected queue.  We must
		 * reconnect with the device अगर possible, and send it
		 * an पात message.
		 */
		prपूर्णांकk("on disconnected queue ");

		res = res_hw_पात;
	पूर्ण अन्यथा अगर (info->SCpnt == SCpnt) अणु
		prपूर्णांकk("executing ");

		चयन (info->scsi.phase) अणु
		/*
		 * If the पूर्णांकerface is idle, and the command is 'disconnectable',
		 * then it is the same as on the disconnected queue.
		 */
		हाल PHASE_IDLE:
			अगर (info->scsi.disconnectable) अणु
				info->scsi.disconnectable = 0;
				info->SCpnt = शून्य;
				res = res_hw_पात;
			पूर्ण
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (info->origSCpnt == SCpnt) अणु
		/*
		 * The command will be executed next, but a command
		 * is currently using the पूर्णांकerface.  This is similar to
		 * being on the issue queue, except the busylun bit has
		 * been set.
		 */
		info->origSCpnt = शून्य;
		clear_bit(SCpnt->device->id * 8 +
			  (u8)(SCpnt->device->lun & 0x7), info->busyluns);
		prपूर्णांकk("waiting for execution ");
		res = res_success;
	पूर्ण अन्यथा
		prपूर्णांकk("unknown ");

	वापस res;
पूर्ण

/**
 * fas216_eh_पात - पात this command
 * @SCpnt: command to पात
 *
 * Abort this command.
 * Returns: FAILED अगर unable to पात
 * Notes: io_request_lock is taken, and irqs are disabled
 */
पूर्णांक fas216_eh_पात(काष्ठा scsi_cmnd *SCpnt)
अणु
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;
	पूर्णांक result = FAILED;

	fas216_checkmagic(info);

	info->stats.पातs += 1;

	scmd_prपूर्णांकk(KERN_WARNING, SCpnt, "abort command\n");

	prपूर्णांक_debug_list();
	fas216_dumpstate(info);

	चयन (fas216_find_command(info, SCpnt)) अणु
	/*
	 * We found the command, and cleared it out.  Either
	 * the command is still known to be executing on the
	 * target, or the busylun bit is not set.
	 */
	हाल res_success:
		scmd_prपूर्णांकk(KERN_WARNING, SCpnt, "abort %p success\n", SCpnt);
		result = SUCCESS;
		अवरोध;

	/*
	 * We need to reconnect to the target and send it an
	 * ABORT or ABORT_TAG message.  We can only करो this
	 * अगर the bus is मुक्त.
	 */
	हाल res_hw_पात:

	/*
	 * We are unable to पात the command क्रम some reason.
	 */
	शेष:
	हाल res_failed:
		scmd_prपूर्णांकk(KERN_WARNING, SCpnt, "abort %p failed\n", SCpnt);
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

/**
 * fas216_eh_device_reset - Reset the device associated with this command
 * @SCpnt: command specअगरing device to reset
 *
 * Reset the device associated with this command.
 * Returns: FAILED अगर unable to reset.
 * Notes: We won't be re-entered, so we'll only have one device
 * reset on the go at one समय.
 */
पूर्णांक fas216_eh_device_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, res = FAILED, target = SCpnt->device->id;

	fas216_log(info, LOG_ERROR, "device reset for target %d", target);

	spin_lock_irqsave(&info->host_lock, flags);

	करो अणु
		/*
		 * If we are currently connected to a device, and
		 * it is the device we want to reset, there is
		 * nothing we can करो here.  Chances are it is stuck,
		 * and we need a bus reset.
		 */
		अगर (info->SCpnt && !info->scsi.disconnectable &&
		    info->SCpnt->device->id == SCpnt->device->id)
			अवरोध;

		/*
		 * We're going to be resetting this device.  Remove
		 * all pending commands from the driver.  By करोing
		 * so, we guarantee that we won't touch the command
		 * काष्ठाures except to process the reset request.
		 */
		queue_हटाओ_all_target(&info->queues.issue, target);
		queue_हटाओ_all_target(&info->queues.disconnected, target);
		अगर (info->origSCpnt && info->origSCpnt->device->id == target)
			info->origSCpnt = शून्य;
		अगर (info->reqSCpnt && info->reqSCpnt->device->id == target)
			info->reqSCpnt = शून्य;
		क्रम (i = 0; i < 8; i++)
			clear_bit(target * 8 + i, info->busyluns);

		/*
		 * Hijack this SCSI command काष्ठाure to send
		 * a bus device reset message to this device.
		 */
		SCpnt->host_scribble = (व्योम *)fas216_devicereset_करोne;

		info->rst_dev_status = 0;
		info->rstSCpnt = SCpnt;

		अगर (info->scsi.phase == PHASE_IDLE)
			fas216_kick(info);

		mod_समयr(&info->eh_समयr, jअगरfies + 30 * HZ);
		spin_unlock_irqrestore(&info->host_lock, flags);

		/*
		 * Wait up to 30 seconds क्रम the reset to complete.
		 */
		रुको_event(info->eh_रुको, info->rst_dev_status);

		del_समयr_sync(&info->eh_समयr);
		spin_lock_irqsave(&info->host_lock, flags);
		info->rstSCpnt = शून्य;

		अगर (info->rst_dev_status == 1)
			res = SUCCESS;
	पूर्ण जबतक (0);

	SCpnt->host_scribble = शून्य;
	spin_unlock_irqrestore(&info->host_lock, flags);

	fas216_log(info, LOG_ERROR, "device reset complete: %s\n",
		   res == SUCCESS ? "success" : "failed");

	वापस res;
पूर्ण

/**
 * fas216_eh_bus_reset - Reset the bus associated with the command
 * @SCpnt: command specअगरing bus to reset
 *
 * Reset the bus associated with the command.
 * Returns: FAILED अगर unable to reset.
 * Notes: Further commands are blocked.
 */
पूर्णांक fas216_eh_bus_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_device *SDpnt;

	fas216_checkmagic(info);
	fas216_log(info, LOG_ERROR, "resetting bus");

	info->stats.bus_resets += 1;

	spin_lock_irqsave(&info->host_lock, flags);

	/*
	 * Stop all activity on this पूर्णांकerface.
	 */
	fas216_पातtransfer(info);
	fas216_ग_लिखोb(info, REG_CNTL3, info->scsi.cfg[2]);

	/*
	 * Clear any pending पूर्णांकerrupts.
	 */
	जबतक (fas216_पढ़ोb(info, REG_STAT) & STAT_INT)
		fas216_पढ़ोb(info, REG_INST);

	info->rst_bus_status = 0;

	/*
	 * For each attached hard-reset device, clear out
	 * all command काष्ठाures.  Leave the running
	 * command in place.
	 */
	shost_क्रम_each_device(SDpnt, info->host) अणु
		पूर्णांक i;

		अगर (SDpnt->soft_reset)
			जारी;

		queue_हटाओ_all_target(&info->queues.issue, SDpnt->id);
		queue_हटाओ_all_target(&info->queues.disconnected, SDpnt->id);
		अगर (info->origSCpnt && info->origSCpnt->device->id == SDpnt->id)
			info->origSCpnt = शून्य;
		अगर (info->reqSCpnt && info->reqSCpnt->device->id == SDpnt->id)
			info->reqSCpnt = शून्य;
		info->SCpnt = शून्य;

		क्रम (i = 0; i < 8; i++)
			clear_bit(SDpnt->id * 8 + i, info->busyluns);
	पूर्ण

	info->scsi.phase = PHASE_IDLE;

	/*
	 * Reset the SCSI bus.  Device cleanup happens in
	 * the पूर्णांकerrupt handler.
	 */
	fas216_cmd(info, CMD_RESETSCSI);

	mod_समयr(&info->eh_समयr, jअगरfies + HZ);
	spin_unlock_irqrestore(&info->host_lock, flags);

	/*
	 * Wait one second क्रम the पूर्णांकerrupt.
	 */
	रुको_event(info->eh_रुको, info->rst_bus_status);
	del_समयr_sync(&info->eh_समयr);

	fas216_log(info, LOG_ERROR, "bus reset complete: %s\n",
		   info->rst_bus_status == 1 ? "success" : "failed");

	वापस info->rst_bus_status == 1 ? SUCCESS : FAILED;
पूर्ण

/**
 * fas216_init_chip - Initialise FAS216 state after reset
 * @info: state काष्ठाure क्रम पूर्णांकerface
 *
 * Initialise FAS216 state after reset
 */
अटल व्योम fas216_init_chip(FAS216_Info *info)
अणु
	अचिन्हित पूर्णांक घड़ी = ((info->अगरcfg.घड़ीrate - 1) / 5 + 1) & 7;
	fas216_ग_लिखोb(info, REG_CLKF, घड़ी);
	fas216_ग_लिखोb(info, REG_CNTL1, info->scsi.cfg[0]);
	fas216_ग_लिखोb(info, REG_CNTL2, info->scsi.cfg[1]);
	fas216_ग_लिखोb(info, REG_CNTL3, info->scsi.cfg[2]);
	fas216_ग_लिखोb(info, REG_STIM, info->अगरcfg.select_समयout);
	fas216_ग_लिखोb(info, REG_SOF, 0);
	fas216_ग_लिखोb(info, REG_STP, info->scsi.async_stp);
	fas216_ग_लिखोb(info, REG_CNTL1, info->scsi.cfg[0]);
पूर्ण

/**
 * fas216_eh_host_reset - Reset the host associated with this command
 * @SCpnt: command specअगरing host to reset
 *
 * Reset the host associated with this command.
 * Returns: FAILED अगर unable to reset.
 * Notes: io_request_lock is taken, and irqs are disabled
 */
पूर्णांक fas216_eh_host_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	FAS216_Info *info = (FAS216_Info *)SCpnt->device->host->hostdata;

	spin_lock_irq(info->host->host_lock);

	fas216_checkmagic(info);

	fas216_log(info, LOG_ERROR, "resetting host");

	/*
	 * Reset the SCSI chip.
	 */
	fas216_cmd(info, CMD_RESETCHIP);

	/*
	 * Ugly ugly ugly!
	 * We need to release the host_lock and enable
	 * IRQs अगर we sleep, but we must relock and disable
	 * IRQs after the sleep.
	 */
	spin_unlock_irq(info->host->host_lock);
	msleep(50 * 1000/100);
	spin_lock_irq(info->host->host_lock);

	/*
	 * Release the SCSI reset.
	 */
	fas216_cmd(info, CMD_NOP);

	fas216_init_chip(info);

	spin_unlock_irq(info->host->host_lock);
	वापस SUCCESS;
पूर्ण

#घोषणा TYPE_UNKNOWN	0
#घोषणा TYPE_NCR53C90	1
#घोषणा TYPE_NCR53C90A	2
#घोषणा TYPE_NCR53C9x	3
#घोषणा TYPE_Am53CF94	4
#घोषणा TYPE_EmFAS216	5
#घोषणा TYPE_QLFAS216	6

अटल अक्षर *chip_types[] = अणु
	"unknown",
	"NS NCR53C90",
	"NS NCR53C90A",
	"NS NCR53C9x",
	"AMD Am53CF94",
	"Emulex FAS216",
	"QLogic FAS216"
पूर्ण;

अटल पूर्णांक fas216_detect_type(FAS216_Info *info)
अणु
	पूर्णांक family, rev;

	/*
	 * Reset the chip.
	 */
	fas216_ग_लिखोb(info, REG_CMD, CMD_RESETCHIP);
	udelay(50);
	fas216_ग_लिखोb(info, REG_CMD, CMD_NOP);

	/*
	 * Check to see अगर control reg 2 is present.
	 */
	fas216_ग_लिखोb(info, REG_CNTL3, 0);
	fas216_ग_लिखोb(info, REG_CNTL2, CNTL2_S2FE);

	/*
	 * If we are unable to पढ़ो back control reg 2
	 * correctly, it is not present, and we have a
	 * NCR53C90.
	 */
	अगर ((fas216_पढ़ोb(info, REG_CNTL2) & (~0xe0)) != CNTL2_S2FE)
		वापस TYPE_NCR53C90;

	/*
	 * Now, check control रेजिस्टर 3
	 */
	fas216_ग_लिखोb(info, REG_CNTL2, 0);
	fas216_ग_लिखोb(info, REG_CNTL3, 0);
	fas216_ग_लिखोb(info, REG_CNTL3, 5);

	/*
	 * If we are unable to पढ़ो the रेजिस्टर back
	 * correctly, we have a NCR53C90A
	 */
	अगर (fas216_पढ़ोb(info, REG_CNTL3) != 5)
		वापस TYPE_NCR53C90A;

	/*
	 * Now पढ़ो the ID from the chip.
	 */
	fas216_ग_लिखोb(info, REG_CNTL3, 0);

	fas216_ग_लिखोb(info, REG_CNTL3, CNTL3_ADIDCHK);
	fas216_ग_लिखोb(info, REG_CNTL3, 0);

	fas216_ग_लिखोb(info, REG_CMD, CMD_RESETCHIP);
	udelay(50);
	fas216_ग_लिखोb(info, REG_CMD, CMD_WITHDMA | CMD_NOP);

	fas216_ग_लिखोb(info, REG_CNTL2, CNTL2_ENF);
	fas216_ग_लिखोb(info, REG_CMD, CMD_RESETCHIP);
	udelay(50);
	fas216_ग_लिखोb(info, REG_CMD, CMD_NOP);

	rev     = fas216_पढ़ोb(info, REG_ID);
	family  = rev >> 3;
	rev    &= 7;

	चयन (family) अणु
	हाल 0x01:
		अगर (rev == 4)
			वापस TYPE_Am53CF94;
		अवरोध;

	हाल 0x02:
		चयन (rev) अणु
		हाल 2:
			वापस TYPE_EmFAS216;
		हाल 3:
			वापस TYPE_QLFAS216;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	prपूर्णांकk("family %x rev %x\n", family, rev);
	वापस TYPE_NCR53C9x;
पूर्ण

/**
 * fas216_reset_state - Initialise driver पूर्णांकernal state
 * @info: state to initialise
 *
 * Initialise driver पूर्णांकernal state
 */
अटल व्योम fas216_reset_state(FAS216_Info *info)
अणु
	पूर्णांक i;

	fas216_checkmagic(info);

	fas216_bus_reset(info);

	/*
	 * Clear out all stale info in our state काष्ठाure
	 */
	स_रखो(info->busyluns, 0, माप(info->busyluns));
	info->scsi.disconnectable = 0;
	info->scsi.पातing = 0;

	क्रम (i = 0; i < 8; i++) अणु
		info->device[i].parity_enabled	= 0;
		info->device[i].parity_check	= 1;
	पूर्ण

	/*
	 * Drain all commands on disconnected queue
	 */
	जबतक (queue_हटाओ(&info->queues.disconnected) != शून्य);

	/*
	 * Remove executing commands.
	 */
	info->SCpnt     = शून्य;
	info->reqSCpnt  = शून्य;
	info->rstSCpnt  = शून्य;
	info->origSCpnt = शून्य;
पूर्ण

/**
 * fas216_init - initialise FAS/NCR/AMD SCSI काष्ठाures.
 * @host: a driver-specअगरic filled-out काष्ठाure
 *
 * Initialise FAS/NCR/AMD SCSI काष्ठाures.
 * Returns: 0 on success
 */
पूर्णांक fas216_init(काष्ठा Scsi_Host *host)
अणु
	FAS216_Info *info = (FAS216_Info *)host->hostdata;

	info->magic_start    = MAGIC;
	info->magic_end      = MAGIC;
	info->host           = host;
	info->scsi.cfg[0]    = host->this_id | CNTL1_PERE;
	info->scsi.cfg[1]    = CNTL2_ENF | CNTL2_S2FE;
	info->scsi.cfg[2]    = info->अगरcfg.cntl3 |
			       CNTL3_ADIDCHK | CNTL3_QTAG | CNTL3_G2CB | CNTL3_LBTM;
	info->scsi.async_stp = fas216_syncperiod(info, info->अगरcfg.asyncperiod);

	info->rst_dev_status = -1;
	info->rst_bus_status = -1;
	init_रुकोqueue_head(&info->eh_रुको);
	समयr_setup(&info->eh_समयr, fas216_eh_समयr, 0);
	
	spin_lock_init(&info->host_lock);

	स_रखो(&info->stats, 0, माप(info->stats));

	msgqueue_initialise(&info->scsi.msgs);

	अगर (!queue_initialise(&info->queues.issue))
		वापस -ENOMEM;

	अगर (!queue_initialise(&info->queues.disconnected)) अणु
		queue_मुक्त(&info->queues.issue);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fas216_add - initialise FAS/NCR/AMD SCSI ic.
 * @host: a driver-specअगरic filled-out काष्ठाure
 * @dev: parent device
 *
 * Initialise FAS/NCR/AMD SCSI ic.
 * Returns: 0 on success
 */
पूर्णांक fas216_add(काष्ठा Scsi_Host *host, काष्ठा device *dev)
अणु
	FAS216_Info *info = (FAS216_Info *)host->hostdata;
	पूर्णांक type, ret;

	अगर (info->अगरcfg.घड़ीrate <= 10 || info->अगरcfg.घड़ीrate > 40) अणु
		prपूर्णांकk(KERN_CRIT "fas216: invalid clock rate %u MHz\n",
			info->अगरcfg.घड़ीrate);
		वापस -EINVAL;
	पूर्ण

	fas216_reset_state(info);
	type = fas216_detect_type(info);
	info->scsi.type = chip_types[type];

	udelay(300);

	/*
	 * Initialise the chip correctly.
	 */
	fas216_init_chip(info);

	/*
	 * Reset the SCSI bus.  We करोn't want to see
	 * the resulting reset पूर्णांकerrupt, so mask it
	 * out.
	 */
	fas216_ग_लिखोb(info, REG_CNTL1, info->scsi.cfg[0] | CNTL1_DISR);
	fas216_ग_लिखोb(info, REG_CMD, CMD_RESETSCSI);

	/*
	 * scsi standard says रुको 250ms
	 */
	spin_unlock_irq(info->host->host_lock);
	msleep(100*1000/100);
	spin_lock_irq(info->host->host_lock);

	fas216_ग_लिखोb(info, REG_CNTL1, info->scsi.cfg[0]);
	fas216_पढ़ोb(info, REG_INST);

	fas216_checkmagic(info);

	ret = scsi_add_host(host, dev);
	अगर (ret)
		fas216_ग_लिखोb(info, REG_CMD, CMD_RESETCHIP);
	अन्यथा
		scsi_scan_host(host);

	वापस ret;
पूर्ण

व्योम fas216_हटाओ(काष्ठा Scsi_Host *host)
अणु
	FAS216_Info *info = (FAS216_Info *)host->hostdata;

	fas216_checkmagic(info);
	scsi_हटाओ_host(host);

	fas216_ग_लिखोb(info, REG_CMD, CMD_RESETCHIP);
	scsi_host_put(host);
पूर्ण

/**
 * fas216_release - release all resources क्रम FAS/NCR/AMD SCSI ic.
 * @host: a driver-specअगरic filled-out काष्ठाure
 *
 * release all resources and put everything to bed क्रम FAS/NCR/AMD SCSI ic.
 */
व्योम fas216_release(काष्ठा Scsi_Host *host)
अणु
	FAS216_Info *info = (FAS216_Info *)host->hostdata;

	queue_मुक्त(&info->queues.disconnected);
	queue_मुक्त(&info->queues.issue);
पूर्ण

व्योम fas216_prपूर्णांक_host(FAS216_Info *info, काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m,
			"\n"
			"Chip    : %s\n"
			" Address: 0x%p\n"
			" IRQ    : %d\n"
			" DMA    : %d\n",
			info->scsi.type, info->scsi.io_base,
			info->scsi.irq, info->scsi.dma);
पूर्ण

व्योम fas216_prपूर्णांक_stats(FAS216_Info *info, काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "\n"
			"Command Statistics:\n"
			" Queued     : %u\n"
			" Issued     : %u\n"
			" Completed  : %u\n"
			" Reads      : %u\n"
			" Writes     : %u\n"
			" Others     : %u\n"
			" Disconnects: %u\n"
			" Aborts     : %u\n"
			" Bus resets : %u\n"
			" Host resets: %u\n",
			info->stats.queues,	 info->stats.हटाओs,
			info->stats.fins,	 info->stats.पढ़ोs,
			info->stats.ग_लिखोs,	 info->stats.miscs,
			info->stats.disconnects, info->stats.पातs,
			info->stats.bus_resets,	 info->stats.host_resets);
पूर्ण

व्योम fas216_prपूर्णांक_devices(FAS216_Info *info, काष्ठा seq_file *m)
अणु
	काष्ठा fas216_device *dev;
	काष्ठा scsi_device *scd;

	seq_माला_दो(m, "Device/Lun TaggedQ       Parity   Sync\n");

	shost_क्रम_each_device(scd, info->host) अणु
		dev = &info->device[scd->id];
		seq_म_लिखो(m, "     %d/%llu   ", scd->id, scd->lun);
		अगर (scd->tagged_supported)
			seq_म_लिखो(m, "%3sabled(%3d) ",
				     scd->simple_tags ? "en" : "dis",
				     scd->current_tag);
		अन्यथा
			seq_माला_दो(m, "unsupported   ");

		seq_म_लिखो(m, "%3sabled ", dev->parity_enabled ? "en" : "dis");

		अगर (dev->sof)
			seq_म_लिखो(m, "offset %d, %d ns\n",
				     dev->sof, dev->period * 4);
		अन्यथा
			seq_माला_दो(m, "async\n");
	पूर्ण
पूर्ण

EXPORT_SYMBOL(fas216_init);
EXPORT_SYMBOL(fas216_add);
EXPORT_SYMBOL(fas216_queue_command);
EXPORT_SYMBOL(fas216_noqueue_command);
EXPORT_SYMBOL(fas216_पूर्णांकr);
EXPORT_SYMBOL(fas216_हटाओ);
EXPORT_SYMBOL(fas216_release);
EXPORT_SYMBOL(fas216_eh_पात);
EXPORT_SYMBOL(fas216_eh_device_reset);
EXPORT_SYMBOL(fas216_eh_bus_reset);
EXPORT_SYMBOL(fas216_eh_host_reset);
EXPORT_SYMBOL(fas216_prपूर्णांक_host);
EXPORT_SYMBOL(fas216_prपूर्णांक_stats);
EXPORT_SYMBOL(fas216_prपूर्णांक_devices);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("Generic FAS216/NCR53C9x driver core");
MODULE_LICENSE("GPL");
