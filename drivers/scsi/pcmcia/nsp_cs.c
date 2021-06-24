<शैली गुरु>
/*======================================================================

    NinjaSCSI-3 / NinjaSCSI-32Bi PCMCIA SCSI host adapter card driver
      By: YOKOTA Hiroshi <yokota@netlab.is.tsukuba.ac.jp>

    Ver.2.8   Support 32bit MMIO mode
              Support Synchronous Data Transfer Request (SDTR) mode
    Ver.2.0   Support 32bit PIO mode
    Ver.1.1.2 Fix क्रम scatter list buffer exceeds
    Ver.1.1   Support scatter list
    Ver.0.1   Initial version

    This software may be used and distributed according to the terms of
    the GNU General Public License.

======================================================================*/

/***********************************************************************
    This driver is क्रम these PCcards.

	I-O DATA PCSC-F	 (Workbit NinjaSCSI-3)
			"WBT", "NinjaSCSI-3", "R1.0"
	I-O DATA CBSC-II (Workbit NinjaSCSI-32Bi in 16bit mode)
			"IO DATA", "CBSC16	 ", "1"

***********************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/major.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/स्थिति.स>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#समावेश <../drivers/scsi/scsi.h>
#समावेश <scsi/scsi_host.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_ioctl.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ds.h>

#समावेश "nsp_cs.h"

MODULE_AUTHOR("YOKOTA Hiroshi <yokota@netlab.is.tsukuba.ac.jp>");
MODULE_DESCRIPTION("WorkBit NinjaSCSI-3 / NinjaSCSI-32Bi(16bit) PCMCIA SCSI host adapter module");
MODULE_LICENSE("GPL");

#समावेश "nsp_io.h"

/*====================================================================*/
/* Parameters that can be set with 'insmod' */

अटल पूर्णांक       nsp_burst_mode = BURST_MEM32;
module_param(nsp_burst_mode, पूर्णांक, 0);
MODULE_PARM_DESC(nsp_burst_mode, "Burst transfer mode (0=io8, 1=io32, 2=mem32(default))");

/* Release IO ports after configuration? */
अटल bool       मुक्त_ports = 0;
module_param(मुक्त_ports, bool, 0);
MODULE_PARM_DESC(मुक्त_ports, "Release IO ports after configuration? (default: 0 (=no))");

अटल काष्ठा scsi_host_ढाँचा nsp_driver_ढाँचा = अणु
	.proc_name	         = "nsp_cs",
	.show_info		 = nsp_show_info,
	.name			 = "WorkBit NinjaSCSI-3/32Bi(16bit)",
	.info			 = nsp_info,
	.queuecommand		 = nsp_queuecommand,
/*	.eh_पात_handler	 = nsp_eh_पात,*/
	.eh_bus_reset_handler	 = nsp_eh_bus_reset,
	.eh_host_reset_handler	 = nsp_eh_host_reset,
	.can_queue		 = 1,
	.this_id		 = NSP_INITIATOR_ID,
	.sg_tablesize		 = SG_ALL,
	.dma_boundary		 = PAGE_SIZE - 1,
पूर्ण;

अटल nsp_hw_data nsp_data_base; /* attach <-> detect glue */



/*
 * debug, error prपूर्णांक
 */
#अगर_अघोषित NSP_DEBUG
# define NSP_DEBUG_MASK		0x000000
# define nsp_msg(type, args...) nsp_cs_message("", 0, (type), args)
# define nsp_dbg(mask, args...) /* */
#अन्यथा
# define NSP_DEBUG_MASK		0xffffff
# define nsp_msg(type, args...) \
	nsp_cs_message (__func__, __LINE__, (type), args)
# define nsp_dbg(mask, args...) \
	nsp_cs_dmessage(__func__, __LINE__, (mask), args)
#पूर्ण_अगर

#घोषणा NSP_DEBUG_QUEUECOMMAND		BIT(0)
#घोषणा NSP_DEBUG_REGISTER		BIT(1)
#घोषणा NSP_DEBUG_AUTOSCSI		BIT(2)
#घोषणा NSP_DEBUG_INTR			BIT(3)
#घोषणा NSP_DEBUG_SGLIST		BIT(4)
#घोषणा NSP_DEBUG_BUSFREE		BIT(5)
#घोषणा NSP_DEBUG_CDB_CONTENTS		BIT(6)
#घोषणा NSP_DEBUG_RESELECTION		BIT(7)
#घोषणा NSP_DEBUG_MSGINOCCUR		BIT(8)
#घोषणा NSP_DEBUG_EEPROM		BIT(9)
#घोषणा NSP_DEBUG_MSGOUTOCCUR		BIT(10)
#घोषणा NSP_DEBUG_BUSRESET		BIT(11)
#घोषणा NSP_DEBUG_RESTART		BIT(12)
#घोषणा NSP_DEBUG_SYNC			BIT(13)
#घोषणा NSP_DEBUG_WAIT			BIT(14)
#घोषणा NSP_DEBUG_TARGETFLAG		BIT(15)
#घोषणा NSP_DEBUG_PROC			BIT(16)
#घोषणा NSP_DEBUG_INIT			BIT(17)
#घोषणा NSP_DEBUG_DATA_IO      		BIT(18)
#घोषणा NSP_SPECIAL_PRINT_REGISTER	BIT(20)

#घोषणा NSP_DEBUG_BUF_LEN		150

अटल अंतरभूत व्योम nsp_inc_resid(काष्ठा scsi_cmnd *SCpnt, पूर्णांक residInc)
अणु
	scsi_set_resid(SCpnt, scsi_get_resid(SCpnt) + residInc);
पूर्ण

__म_लिखो(4, 5)
अटल व्योम nsp_cs_message(स्थिर अक्षर *func, पूर्णांक line, अक्षर *type, अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर buf[NSP_DEBUG_BUF_LEN];

	बहु_शुरू(args, fmt);
	vsnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);

#अगर_अघोषित NSP_DEBUG
	prपूर्णांकk("%snsp_cs: %s\n", type, buf);
#अन्यथा
	prपूर्णांकk("%snsp_cs: %s (%d): %s\n", type, func, line, buf);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित NSP_DEBUG
अटल व्योम nsp_cs_dmessage(स्थिर अक्षर *func, पूर्णांक line, पूर्णांक mask, अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर buf[NSP_DEBUG_BUF_LEN];

	बहु_शुरू(args, fmt);
	vsnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);

	अगर (mask & NSP_DEBUG_MASK) अणु
		prपूर्णांकk("nsp_cs-debug: 0x%x %s (%d): %s\n", mask, func, line, buf);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/***********************************************************/

/*====================================================
 * Clenaup parameters and call करोne() functions.
 * You must be set SCpnt->result beक्रमe call this function.
 */
अटल व्योम nsp_scsi_करोne(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	data->CurrentSC = शून्य;

	SCpnt->scsi_करोne(SCpnt);
पूर्ण

अटल पूर्णांक nsp_queuecommand_lck(काष्ठा scsi_cmnd *SCpnt,
			    व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
#अगर_घोषित NSP_DEBUG
	/*अचिन्हित पूर्णांक host_id = SCpnt->device->host->this_id;*/
	/*अचिन्हित पूर्णांक base    = SCpnt->device->host->io_port;*/
	अचिन्हित अक्षर target = scmd_id(SCpnt);
#पूर्ण_अगर
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	nsp_dbg(NSP_DEBUG_QUEUECOMMAND,
		"SCpnt=0x%p target=%d lun=%llu sglist=0x%p bufflen=%d sg_count=%d",
		SCpnt, target, SCpnt->device->lun, scsi_sglist(SCpnt),
		scsi_bufflen(SCpnt), scsi_sg_count(SCpnt));
	//nsp_dbg(NSP_DEBUG_QUEUECOMMAND, "before CurrentSC=0x%p", data->CurrentSC);

	SCpnt->scsi_करोne	= करोne;

	अगर (data->CurrentSC != शून्य) अणु
		nsp_msg(KERN_DEBUG, "CurrentSC!=NULL this can't be happen");
		SCpnt->result   = DID_BAD_TARGET << 16;
		nsp_scsi_करोne(SCpnt);
		वापस 0;
	पूर्ण

#अगर 0
	/* XXX: pcmcia-cs generates SCSI command with "scsi_info" utility.
	        This makes kernel crash when suspending... */
	अगर (data->ScsiInfo->stop != 0) अणु
		nsp_msg(KERN_INFO, "suspending device. reject command.");
		SCpnt->result  = DID_BAD_TARGET << 16;
		nsp_scsi_करोne(SCpnt);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण
#पूर्ण_अगर

	show_command(SCpnt);

	data->CurrentSC		= SCpnt;

	SCpnt->SCp.Status	= CHECK_CONDITION;
	SCpnt->SCp.Message	= 0;
	SCpnt->SCp.have_data_in = IO_UNKNOWN;
	SCpnt->SCp.sent_command = 0;
	SCpnt->SCp.phase	= PH_UNDETERMINED;
	scsi_set_resid(SCpnt, scsi_bufflen(SCpnt));

	/* setup scratch area
	   SCp.ptr		: buffer poपूर्णांकer
	   SCp.this_residual	: buffer length
	   SCp.buffer		: next buffer
	   SCp.buffers_residual : left buffers in list
	   SCp.phase		: current state of the command */
	अगर (scsi_bufflen(SCpnt)) अणु
		SCpnt->SCp.buffer	    = scsi_sglist(SCpnt);
		SCpnt->SCp.ptr		    = BUFFER_ADDR;
		SCpnt->SCp.this_residual    = SCpnt->SCp.buffer->length;
		SCpnt->SCp.buffers_residual = scsi_sg_count(SCpnt) - 1;
	पूर्ण अन्यथा अणु
		SCpnt->SCp.ptr		    = शून्य;
		SCpnt->SCp.this_residual    = 0;
		SCpnt->SCp.buffer	    = शून्य;
		SCpnt->SCp.buffers_residual = 0;
	पूर्ण

	अगर (nsphw_start_selection(SCpnt) == FALSE) अणु
		nsp_dbg(NSP_DEBUG_QUEUECOMMAND, "selection fail");
		SCpnt->result   = DID_BUS_BUSY << 16;
		nsp_scsi_करोne(SCpnt);
		वापस 0;
	पूर्ण


	//nsp_dbg(NSP_DEBUG_QUEUECOMMAND, "out");
#अगर_घोषित NSP_DEBUG
	data->CmdId++;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(nsp_queuecommand)

/*
 * setup PIO FIFO transfer mode and enable/disable to data out
 */
अटल व्योम nsp_setup_fअगरo(nsp_hw_data *data, पूर्णांक enabled)
अणु
	अचिन्हित पूर्णांक  base = data->BaseAddress;
	अचिन्हित अक्षर transfer_mode_reg;

	//nsp_dbg(NSP_DEBUG_DATA_IO, "enabled=%d", enabled);

	अगर (enabled != FALSE) अणु
		transfer_mode_reg = TRANSFER_GO | BRAIND;
	पूर्ण अन्यथा अणु
		transfer_mode_reg = 0;
	पूर्ण

	transfer_mode_reg |= data->TransferMode;

	nsp_index_ग_लिखो(base, TRANSFERMODE, transfer_mode_reg);
पूर्ण

अटल व्योम nsphw_init_sync(nsp_hw_data *data)
अणु
	sync_data पंचांगp_sync = अणु .SyncNegotiation = SYNC_NOT_YET,
			       .SyncPeriod      = 0,
			       .SyncOffset      = 0
	पूर्ण;
	पूर्णांक i;

	/* setup sync data */
	क्रम ( i = 0; i < ARRAY_SIZE(data->Sync); i++ ) अणु
		data->Sync[i] = पंचांगp_sync;
	पूर्ण
पूर्ण

/*
 * Initialize Ninja hardware
 */
अटल पूर्णांक nsphw_init(nsp_hw_data *data)
अणु
	अचिन्हित पूर्णांक base     = data->BaseAddress;

	nsp_dbg(NSP_DEBUG_INIT, "in base=0x%x", base);

	data->ScsiClockDiv = CLOCK_40M | FAST_20;
	data->CurrentSC    = शून्य;
	data->FअगरoCount    = 0;
	data->TransferMode = MODE_IO8;

	nsphw_init_sync(data);

	/* block all पूर्णांकerrupts */
	nsp_ग_लिखो(base,	      IRQCONTROL,   IRQCONTROL_ALLMASK);

	/* setup SCSI पूर्णांकerface */
	nsp_ग_लिखो(base,	      IFSELECT,	    IF_IFSEL);

	nsp_index_ग_लिखो(base, SCSIIRQMODE,  0);

	nsp_index_ग_लिखो(base, TRANSFERMODE, MODE_IO8);
	nsp_index_ग_लिखो(base, CLOCKDIV,	    data->ScsiClockDiv);

	nsp_index_ग_लिखो(base, PARITYCTRL,   0);
	nsp_index_ग_लिखो(base, POINTERCLR,   POINTER_CLEAR     |
					    ACK_COUNTER_CLEAR |
					    REQ_COUNTER_CLEAR |
					    HOST_COUNTER_CLEAR);

	/* setup fअगरo asic */
	nsp_ग_लिखो(base,	      IFSELECT,	    IF_REGSEL);
	nsp_index_ग_लिखो(base, TERMPWRCTRL,  0);
	अगर ((nsp_index_पढ़ो(base, OTHERCONTROL) & TPWR_SENSE) == 0) अणु
		nsp_msg(KERN_INFO, "terminator power on");
		nsp_index_ग_लिखो(base, TERMPWRCTRL, POWER_ON);
	पूर्ण

	nsp_index_ग_लिखो(base, TIMERCOUNT,   0);
	nsp_index_ग_लिखो(base, TIMERCOUNT,   0); /* requires 2 बार!! */

	nsp_index_ग_लिखो(base, SYNCREG,	    0);
	nsp_index_ग_लिखो(base, ACKWIDTH,	    0);

	/* enable पूर्णांकerrupts and ack them */
	nsp_index_ग_लिखो(base, SCSIIRQMODE,  SCSI_PHASE_CHANGE_EI |
					    RESELECT_EI		 |
					    SCSI_RESET_IRQ_EI	 );
	nsp_ग_लिखो(base,	      IRQCONTROL,   IRQCONTROL_ALLCLEAR);

	nsp_setup_fअगरo(data, FALSE);

	वापस TRUE;
पूर्ण

/*
 * Start selection phase
 */
अटल पूर्णांक nsphw_start_selection(काष्ठा scsi_cmnd *SCpnt)
अणु
	अचिन्हित पूर्णांक  host_id	 = SCpnt->device->host->this_id;
	अचिन्हित पूर्णांक  base	 = SCpnt->device->host->io_port;
	अचिन्हित अक्षर target	 = scmd_id(SCpnt);
	nsp_hw_data  *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	पूर्णांक	      समय_out;
	अचिन्हित अक्षर phase, arbit;

	//nsp_dbg(NSP_DEBUG_RESELECTION, "in");

	phase = nsp_index_पढ़ो(base, SCSIBUSMON);
	अगर(phase != BUSMON_BUS_FREE) अणु
		//nsp_dbg(NSP_DEBUG_RESELECTION, "bus busy");
		वापस FALSE;
	पूर्ण

	/* start arbitration */
	//nsp_dbg(NSP_DEBUG_RESELECTION, "start arbit");
	SCpnt->SCp.phase = PH_ARBSTART;
	nsp_index_ग_लिखो(base, SETARBIT, ARBIT_GO);

	समय_out = 1000;
	करो अणु
		/* XXX: what a stupid chip! */
		arbit = nsp_index_पढ़ो(base, ARBITSTATUS);
		//nsp_dbg(NSP_DEBUG_RESELECTION, "arbit=%d, wait_count=%d", arbit, रुको_count);
		udelay(1); /* hold 1.2us */
	पूर्ण जबतक((arbit & (ARBIT_WIN | ARBIT_FAIL)) == 0 &&
		(समय_out-- != 0));

	अगर (!(arbit & ARBIT_WIN)) अणु
		//nsp_dbg(NSP_DEBUG_RESELECTION, "arbit fail");
		nsp_index_ग_लिखो(base, SETARBIT, ARBIT_FLAG_CLEAR);
		वापस FALSE;
	पूर्ण

	/* निश्चित select line */
	//nsp_dbg(NSP_DEBUG_RESELECTION, "assert SEL line");
	SCpnt->SCp.phase = PH_SELSTART;
	udelay(3); /* रुको 2.4us */
	nsp_index_ग_लिखो(base, SCSIDATALATCH, BIT(host_id) | BIT(target));
	nsp_index_ग_लिखो(base, SCSIBUSCTRL,   SCSI_SEL | SCSI_BSY                    | SCSI_ATN);
	udelay(2); /* रुको >1.2us */
	nsp_index_ग_लिखो(base, SCSIBUSCTRL,   SCSI_SEL | SCSI_BSY | SCSI_DATAOUT_ENB | SCSI_ATN);
	nsp_index_ग_लिखो(base, SETARBIT,	     ARBIT_FLAG_CLEAR);
	/*udelay(1);*/ /* रुको >90ns */
	nsp_index_ग_लिखो(base, SCSIBUSCTRL,   SCSI_SEL            | SCSI_DATAOUT_ENB | SCSI_ATN);

	/* check selection समयout */
	nsp_start_समयr(SCpnt, 1000/51);
	data->SelectionTimeOut = 1;

	वापस TRUE;
पूर्ण

काष्ठा nsp_sync_table अणु
	अचिन्हित पूर्णांक min_period;
	अचिन्हित पूर्णांक max_period;
	अचिन्हित पूर्णांक chip_period;
	अचिन्हित पूर्णांक ack_width;
पूर्ण;

अटल काष्ठा nsp_sync_table nsp_sync_table_40M[] = अणु
	अणु0x0c, 0x0c, 0x1, 0पूर्ण,	/* 20MB	  50ns*/
	अणु0x19, 0x19, 0x3, 1पूर्ण,	/* 10MB	 100ns*/ 
	अणु0x1a, 0x25, 0x5, 2पूर्ण,	/* 7.5MB 150ns*/ 
	अणु0x26, 0x32, 0x7, 3पूर्ण,	/* 5MB	 200ns*/
	अणु   0,    0,   0, 0पूर्ण,
पूर्ण;

अटल काष्ठा nsp_sync_table nsp_sync_table_20M[] = अणु
	अणु0x19, 0x19, 0x1, 0पूर्ण,	/* 10MB	 100ns*/ 
	अणु0x1a, 0x25, 0x2, 0पूर्ण,	/* 7.5MB 150ns*/ 
	अणु0x26, 0x32, 0x3, 1पूर्ण,	/* 5MB	 200ns*/
	अणु   0,    0,   0, 0पूर्ण,
पूर्ण;

/*
 * setup synchronous data transfer mode
 */
अटल पूर्णांक nsp_analyze_sdtr(काष्ठा scsi_cmnd *SCpnt)
अणु
	अचिन्हित अक्षर	       target = scmd_id(SCpnt);
//	अचिन्हित अक्षर	       lun    = SCpnt->device->lun;
	nsp_hw_data           *data   = (nsp_hw_data *)SCpnt->device->host->hostdata;
	sync_data	      *sync   = &(data->Sync[target]);
	काष्ठा nsp_sync_table *sync_table;
	अचिन्हित पूर्णांक	       period, offset;
	पूर्णांक		       i;


	nsp_dbg(NSP_DEBUG_SYNC, "in");

	period = sync->SyncPeriod;
	offset = sync->SyncOffset;

	nsp_dbg(NSP_DEBUG_SYNC, "period=0x%x, offset=0x%x", period, offset);

	अगर ((data->ScsiClockDiv & (BIT(0)|BIT(1))) == CLOCK_20M) अणु
		sync_table = nsp_sync_table_20M;
	पूर्ण अन्यथा अणु
		sync_table = nsp_sync_table_40M;
	पूर्ण

	क्रम ( i = 0; sync_table->max_period != 0; i++, sync_table++) अणु
		अगर ( period >= sync_table->min_period &&
		     period <= sync_table->max_period	 ) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (period != 0 && sync_table->max_period == 0) अणु
		/*
		 * No proper period/offset found
		 */
		nsp_dbg(NSP_DEBUG_SYNC, "no proper period/offset");

		sync->SyncPeriod      = 0;
		sync->SyncOffset      = 0;
		sync->SyncRegister    = 0;
		sync->AckWidth	      = 0;

		वापस FALSE;
	पूर्ण

	sync->SyncRegister    = (sync_table->chip_period << SYNCREG_PERIOD_SHIFT) |
		                (offset & SYNCREG_OFFSET_MASK);
	sync->AckWidth	      = sync_table->ack_width;

	nsp_dbg(NSP_DEBUG_SYNC, "sync_reg=0x%x, ack_width=0x%x", sync->SyncRegister, sync->AckWidth);

	वापस TRUE;
पूर्ण


/*
 * start ninja hardware समयr
 */
अटल व्योम nsp_start_समयr(काष्ठा scsi_cmnd *SCpnt, पूर्णांक समय)
अणु
	अचिन्हित पूर्णांक base = SCpnt->device->host->io_port;
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	//nsp_dbg(NSP_DEBUG_INTR, "in SCpnt=0x%p, time=%d", SCpnt, समय);
	data->TimerCount = समय;
	nsp_index_ग_लिखो(base, TIMERCOUNT, समय);
पूर्ण

/*
 * रुको क्रम bus phase change
 */
अटल पूर्णांक nsp_negate_संकेत(काष्ठा scsi_cmnd *SCpnt, अचिन्हित अक्षर mask,
			     अक्षर *str)
अणु
	अचिन्हित पूर्णांक  base = SCpnt->device->host->io_port;
	अचिन्हित अक्षर reg;
	पूर्णांक	      समय_out;

	//nsp_dbg(NSP_DEBUG_INTR, "in");

	समय_out = 100;

	करो अणु
		reg = nsp_index_पढ़ो(base, SCSIBUSMON);
		अगर (reg == 0xff) अणु
			अवरोध;
		पूर्ण
	पूर्ण जबतक ((--समय_out != 0) && (reg & mask) != 0);

	अगर (समय_out == 0) अणु
		nsp_msg(KERN_DEBUG, " %s signal off timeout", str);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * expect Ninja Irq
 */
अटल पूर्णांक nsp_expect_संकेत(काष्ठा scsi_cmnd *SCpnt,
			     अचिन्हित अक्षर current_phase,
			     अचिन्हित अक्षर mask)
अणु
	अचिन्हित पूर्णांक  base	 = SCpnt->device->host->io_port;
	पूर्णांक	      समय_out;
	अचिन्हित अक्षर phase, i_src;

	//nsp_dbg(NSP_DEBUG_INTR, "current_phase=0x%x, mask=0x%x", current_phase, mask);

	समय_out = 100;
	करो अणु
		phase = nsp_index_पढ़ो(base, SCSIBUSMON);
		अगर (phase == 0xff) अणु
			//nsp_dbg(NSP_DEBUG_INTR, "ret -1");
			वापस -1;
		पूर्ण
		i_src = nsp_पढ़ो(base, IRQSTATUS);
		अगर (i_src & IRQSTATUS_SCSI) अणु
			//nsp_dbg(NSP_DEBUG_INTR, "ret 0 found scsi signal");
			वापस 0;
		पूर्ण
		अगर ((phase & mask) != 0 && (phase & BUSMON_PHASE_MASK) == current_phase) अणु
			//nsp_dbg(NSP_DEBUG_INTR, "ret 1 phase=0x%x", phase);
			वापस 1;
		पूर्ण
	पूर्ण जबतक(समय_out-- != 0);

	//nsp_dbg(NSP_DEBUG_INTR, "timeout");
	वापस -1;
पूर्ण

/*
 * transfer SCSI message
 */
अटल पूर्णांक nsp_xfer(काष्ठा scsi_cmnd *SCpnt, पूर्णांक phase)
अणु
	अचिन्हित पूर्णांक  base = SCpnt->device->host->io_port;
	nsp_hw_data  *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	अक्षर	     *buf  = data->MsgBuffer;
	पूर्णांक	      len  = min(MSGBUF_SIZE, data->MsgLen);
	पूर्णांक	      ptr;
	पूर्णांक	      ret;

	//nsp_dbg(NSP_DEBUG_DATA_IO, "in");
	क्रम (ptr = 0; len > 0; len--, ptr++) अणु

		ret = nsp_expect_संकेत(SCpnt, phase, BUSMON_REQ);
		अगर (ret <= 0) अणु
			nsp_dbg(NSP_DEBUG_DATA_IO, "xfer quit");
			वापस 0;
		पूर्ण

		/* अगर last byte, negate ATN */
		अगर (len == 1 && SCpnt->SCp.phase == PH_MSG_OUT) अणु
			nsp_index_ग_लिखो(base, SCSIBUSCTRL, AUTOसूचीECTION | ACKENB);
		पूर्ण

		/* पढ़ो & ग_लिखो message */
		अगर (phase & BUSMON_IO) अणु
			nsp_dbg(NSP_DEBUG_DATA_IO, "read msg");
			buf[ptr] = nsp_index_पढ़ो(base, SCSIDATAWITHACK);
		पूर्ण अन्यथा अणु
			nsp_dbg(NSP_DEBUG_DATA_IO, "write msg");
			nsp_index_ग_लिखो(base, SCSIDATAWITHACK, buf[ptr]);
		पूर्ण
		nsp_negate_संकेत(SCpnt, BUSMON_ACK, "xfer<ack>");

	पूर्ण
	वापस len;
पूर्ण

/*
 * get extra SCSI data from fअगरo
 */
अटल पूर्णांक nsp_dataphase_bypass(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	अचिन्हित पूर्णांक count;

	//nsp_dbg(NSP_DEBUG_DATA_IO, "in");

	अगर (SCpnt->SCp.have_data_in != IO_IN) अणु
		वापस 0;
	पूर्ण

	count = nsp_fअगरo_count(SCpnt);
	अगर (data->FअगरoCount == count) अणु
		//nsp_dbg(NSP_DEBUG_DATA_IO, "not use bypass quirk");
		वापस 0;
	पूर्ण

	/*
	 * XXX: NSP_QUIRK
	 * data phase skip only occures in हाल of SCSI_LOW_READ
	 */
	nsp_dbg(NSP_DEBUG_DATA_IO, "use bypass quirk");
	SCpnt->SCp.phase = PH_DATA;
	nsp_pio_पढ़ो(SCpnt);
	nsp_setup_fअगरo(data, FALSE);

	वापस 0;
पूर्ण

/*
 * accept reselection
 */
अटल पूर्णांक nsp_reselected(काष्ठा scsi_cmnd *SCpnt)
अणु
	अचिन्हित पूर्णांक  base    = SCpnt->device->host->io_port;
	अचिन्हित पूर्णांक  host_id = SCpnt->device->host->this_id;
	//nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	अचिन्हित अक्षर bus_reg;
	अचिन्हित अक्षर id_reg, पंचांगp;
	पूर्णांक target;

	nsp_dbg(NSP_DEBUG_RESELECTION, "in");

	id_reg = nsp_index_पढ़ो(base, RESELECTID);
	पंचांगp    = id_reg & (~BIT(host_id));
	target = 0;
	जबतक(पंचांगp != 0) अणु
		अगर (पंचांगp & BIT(0)) अणु
			अवरोध;
		पूर्ण
		पंचांगp >>= 1;
		target++;
	पूर्ण

	अगर (scmd_id(SCpnt) != target) अणु
		nsp_msg(KERN_ERR, "XXX: reselect ID must be %d in this implementation.", target);
	पूर्ण

	nsp_negate_संकेत(SCpnt, BUSMON_SEL, "reselect<SEL>");

	nsp_nexus(SCpnt);
	bus_reg = nsp_index_पढ़ो(base, SCSIBUSCTRL) & ~(SCSI_BSY | SCSI_ATN);
	nsp_index_ग_लिखो(base, SCSIBUSCTRL, bus_reg);
	nsp_index_ग_लिखो(base, SCSIBUSCTRL, bus_reg | AUTOसूचीECTION | ACKENB);

	वापस TRUE;
पूर्ण

/*
 * count how many data transferd
 */
अटल पूर्णांक nsp_fअगरo_count(काष्ठा scsi_cmnd *SCpnt)
अणु
	अचिन्हित पूर्णांक base = SCpnt->device->host->io_port;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक l, m, h;

	nsp_index_ग_लिखो(base, POINTERCLR, POINTER_CLEAR | ACK_COUNTER);

	l     = nsp_index_पढ़ो(base, TRANSFERCOUNT);
	m     = nsp_index_पढ़ो(base, TRANSFERCOUNT);
	h     = nsp_index_पढ़ो(base, TRANSFERCOUNT);
	nsp_index_पढ़ो(base, TRANSFERCOUNT); /* required this! */

	count = (h << 16) | (m << 8) | (l << 0);

	//nsp_dbg(NSP_DEBUG_DATA_IO, "count=0x%x", count);

	वापस count;
पूर्ण

/* fअगरo size */
#घोषणा RFIFO_CRIT 64
#घोषणा WFIFO_CRIT 64

/*
 * पढ़ो data in DATA IN phase
 */
अटल व्योम nsp_pio_पढ़ो(काष्ठा scsi_cmnd *SCpnt)
अणु
	अचिन्हित पूर्णांक  base      = SCpnt->device->host->io_port;
	अचिन्हित दीर्घ mmio_base = SCpnt->device->host->base;
	nsp_hw_data  *data      = (nsp_hw_data *)SCpnt->device->host->hostdata;
	दीर्घ	      समय_out;
	पूर्णांक	      ocount, res;
	अचिन्हित अक्षर stat, fअगरo_stat;

	ocount = data->FअगरoCount;

	nsp_dbg(NSP_DEBUG_DATA_IO, "in SCpnt=0x%p resid=%d ocount=%d ptr=0x%p this_residual=%d buffers=0x%p nbuf=%d",
		SCpnt, scsi_get_resid(SCpnt), ocount, SCpnt->SCp.ptr,
		SCpnt->SCp.this_residual, SCpnt->SCp.buffer,
		SCpnt->SCp.buffers_residual);

	समय_out = 1000;

	जबतक ((समय_out-- != 0) &&
	       (SCpnt->SCp.this_residual > 0 || SCpnt->SCp.buffers_residual > 0 ) ) अणु

		stat = nsp_index_पढ़ो(base, SCSIBUSMON);
		stat &= BUSMON_PHASE_MASK;


		res = nsp_fअगरo_count(SCpnt) - ocount;
		//nsp_dbg(NSP_DEBUG_DATA_IO, "ptr=0x%p this=0x%x ocount=0x%x res=0x%x", SCpnt->SCp.ptr, SCpnt->SCp.this_residual, ocount, res);
		अगर (res == 0) अणु /* अगर some data available ? */
			अगर (stat == BUSPHASE_DATA_IN) अणु /* phase changed? */
				//nsp_dbg(NSP_DEBUG_DATA_IO, " wait for data this=%d", SCpnt->SCp.this_residual);
				जारी;
			पूर्ण अन्यथा अणु
				nsp_dbg(NSP_DEBUG_DATA_IO, "phase changed stat=0x%x", stat);
				अवरोध;
			पूर्ण
		पूर्ण

		fअगरo_stat = nsp_पढ़ो(base, FIFOSTATUS);
		अगर ((fअगरo_stat & FIFOSTATUS_FULL_EMPTY) == 0 &&
		    stat                                == BUSPHASE_DATA_IN) अणु
			जारी;
		पूर्ण

		res = min(res, SCpnt->SCp.this_residual);

		चयन (data->TransferMode) अणु
		हाल MODE_IO32:
			res &= ~(BIT(1)|BIT(0)); /* align 4 */
			nsp_fअगरo32_पढ़ो(base, SCpnt->SCp.ptr, res >> 2);
			अवरोध;
		हाल MODE_IO8:
			nsp_fअगरo8_पढ़ो (base, SCpnt->SCp.ptr, res     );
			अवरोध;

		हाल MODE_MEM32:
			res &= ~(BIT(1)|BIT(0)); /* align 4 */
			nsp_mmio_fअगरo32_पढ़ो(mmio_base, SCpnt->SCp.ptr, res >> 2);
			अवरोध;

		शेष:
			nsp_dbg(NSP_DEBUG_DATA_IO, "unknown read mode");
			वापस;
		पूर्ण

		nsp_inc_resid(SCpnt, -res);
		SCpnt->SCp.ptr		 += res;
		SCpnt->SCp.this_residual -= res;
		ocount			 += res;
		//nsp_dbg(NSP_DEBUG_DATA_IO, "ptr=0x%p this_residual=0x%x ocount=0x%x", SCpnt->SCp.ptr, SCpnt->SCp.this_residual, ocount);

		/* go to next scatter list अगर available */
		अगर (SCpnt->SCp.this_residual	== 0 &&
		    SCpnt->SCp.buffers_residual != 0 ) अणु
			//nsp_dbg(NSP_DEBUG_DATA_IO, "scatterlist next timeout=%d", समय_out);
			SCpnt->SCp.buffers_residual--;
			SCpnt->SCp.buffer = sg_next(SCpnt->SCp.buffer);
			SCpnt->SCp.ptr		 = BUFFER_ADDR;
			SCpnt->SCp.this_residual = SCpnt->SCp.buffer->length;
			समय_out = 1000;

			//nsp_dbg(NSP_DEBUG_DATA_IO, "page: 0x%p, off: 0x%x", SCpnt->SCp.buffer->page, SCpnt->SCp.buffer->offset);
		पूर्ण
	पूर्ण

	data->FअगरoCount = ocount;

	अगर (समय_out < 0) अणु
		nsp_msg(KERN_DEBUG, "pio read timeout resid=%d this_residual=%d buffers_residual=%d",
			scsi_get_resid(SCpnt), SCpnt->SCp.this_residual,
			SCpnt->SCp.buffers_residual);
	पूर्ण
	nsp_dbg(NSP_DEBUG_DATA_IO, "read ocount=0x%x", ocount);
	nsp_dbg(NSP_DEBUG_DATA_IO, "r cmd=%d resid=0x%x\n", data->CmdId,
	                                                scsi_get_resid(SCpnt));
पूर्ण

/*
 * ग_लिखो data in DATA OUT phase
 */
अटल व्योम nsp_pio_ग_लिखो(काष्ठा scsi_cmnd *SCpnt)
अणु
	अचिन्हित पूर्णांक  base      = SCpnt->device->host->io_port;
	अचिन्हित दीर्घ mmio_base = SCpnt->device->host->base;
	nsp_hw_data  *data      = (nsp_hw_data *)SCpnt->device->host->hostdata;
	पूर्णांक	      समय_out;
	पूर्णांक           ocount, res;
	अचिन्हित अक्षर stat;

	ocount	 = data->FअगरoCount;

	nsp_dbg(NSP_DEBUG_DATA_IO, "in fifocount=%d ptr=0x%p this_residual=%d buffers=0x%p nbuf=%d resid=0x%x",
		data->FअगरoCount, SCpnt->SCp.ptr, SCpnt->SCp.this_residual,
		SCpnt->SCp.buffer, SCpnt->SCp.buffers_residual,
		scsi_get_resid(SCpnt));

	समय_out = 1000;

	जबतक ((समय_out-- != 0) &&
	       (SCpnt->SCp.this_residual > 0 || SCpnt->SCp.buffers_residual > 0)) अणु
		stat = nsp_index_पढ़ो(base, SCSIBUSMON);
		stat &= BUSMON_PHASE_MASK;

		अगर (stat != BUSPHASE_DATA_OUT) अणु
			res = ocount - nsp_fअगरo_count(SCpnt);

			nsp_dbg(NSP_DEBUG_DATA_IO, "phase changed stat=0x%x, res=%d\n", stat, res);
			/* Put back poपूर्णांकer */
			nsp_inc_resid(SCpnt, res);
			SCpnt->SCp.ptr		 -= res;
			SCpnt->SCp.this_residual += res;
			ocount			 -= res;

			अवरोध;
		पूर्ण

		res = ocount - nsp_fअगरo_count(SCpnt);
		अगर (res > 0) अणु /* ग_लिखो all data? */
			nsp_dbg(NSP_DEBUG_DATA_IO, "wait for all data out. ocount=0x%x res=%d", ocount, res);
			जारी;
		पूर्ण

		res = min(SCpnt->SCp.this_residual, WFIFO_CRIT);

		//nsp_dbg(NSP_DEBUG_DATA_IO, "ptr=0x%p this=0x%x res=0x%x", SCpnt->SCp.ptr, SCpnt->SCp.this_residual, res);
		चयन (data->TransferMode) अणु
		हाल MODE_IO32:
			res &= ~(BIT(1)|BIT(0)); /* align 4 */
			nsp_fअगरo32_ग_लिखो(base, SCpnt->SCp.ptr, res >> 2);
			अवरोध;
		हाल MODE_IO8:
			nsp_fअगरo8_ग_लिखो (base, SCpnt->SCp.ptr, res     );
			अवरोध;

		हाल MODE_MEM32:
			res &= ~(BIT(1)|BIT(0)); /* align 4 */
			nsp_mmio_fअगरo32_ग_लिखो(mmio_base, SCpnt->SCp.ptr, res >> 2);
			अवरोध;

		शेष:
			nsp_dbg(NSP_DEBUG_DATA_IO, "unknown write mode");
			अवरोध;
		पूर्ण

		nsp_inc_resid(SCpnt, -res);
		SCpnt->SCp.ptr		 += res;
		SCpnt->SCp.this_residual -= res;
		ocount			 += res;

		/* go to next scatter list अगर available */
		अगर (SCpnt->SCp.this_residual	== 0 &&
		    SCpnt->SCp.buffers_residual != 0 ) अणु
			//nsp_dbg(NSP_DEBUG_DATA_IO, "scatterlist next");
			SCpnt->SCp.buffers_residual--;
			SCpnt->SCp.buffer = sg_next(SCpnt->SCp.buffer);
			SCpnt->SCp.ptr		 = BUFFER_ADDR;
			SCpnt->SCp.this_residual = SCpnt->SCp.buffer->length;
			समय_out = 1000;
		पूर्ण
	पूर्ण

	data->FअगरoCount = ocount;

	अगर (समय_out < 0) अणु
		nsp_msg(KERN_DEBUG, "pio write timeout resid=0x%x",
		                                        scsi_get_resid(SCpnt));
	पूर्ण
	nsp_dbg(NSP_DEBUG_DATA_IO, "write ocount=0x%x", ocount);
	nsp_dbg(NSP_DEBUG_DATA_IO, "w cmd=%d resid=0x%x\n", data->CmdId,
	                                                scsi_get_resid(SCpnt));
पूर्ण
#अघोषित RFIFO_CRIT
#अघोषित WFIFO_CRIT

/*
 * setup synchronous/asynchronous data transfer mode
 */
अटल पूर्णांक nsp_nexus(काष्ठा scsi_cmnd *SCpnt)
अणु
	अचिन्हित पूर्णांक   base   = SCpnt->device->host->io_port;
	अचिन्हित अक्षर  target = scmd_id(SCpnt);
//	अचिन्हित अक्षर  lun    = SCpnt->device->lun;
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	sync_data     *sync   = &(data->Sync[target]);

	//nsp_dbg(NSP_DEBUG_DATA_IO, "in SCpnt=0x%p", SCpnt);

	/* setup synch transfer रेजिस्टरs */
	nsp_index_ग_लिखो(base, SYNCREG,	sync->SyncRegister);
	nsp_index_ग_लिखो(base, ACKWIDTH, sync->AckWidth);

	अगर (scsi_get_resid(SCpnt) % 4 != 0 ||
	    scsi_get_resid(SCpnt) <= PAGE_SIZE ) अणु
		data->TransferMode = MODE_IO8;
	पूर्ण अन्यथा अगर (nsp_burst_mode == BURST_MEM32) अणु
		data->TransferMode = MODE_MEM32;
	पूर्ण अन्यथा अगर (nsp_burst_mode == BURST_IO32) अणु
		data->TransferMode = MODE_IO32;
	पूर्ण अन्यथा अणु
		data->TransferMode = MODE_IO8;
	पूर्ण

	/* setup pdma fअगरo */
	nsp_setup_fअगरo(data, TRUE);

	/* clear ack counter */
 	data->FअगरoCount = 0;
	nsp_index_ग_लिखो(base, POINTERCLR, POINTER_CLEAR	    |
					  ACK_COUNTER_CLEAR |
					  REQ_COUNTER_CLEAR |
					  HOST_COUNTER_CLEAR);

	वापस 0;
पूर्ण

#समावेश "nsp_message.c"
/*
 * पूर्णांकerrupt handler
 */
अटल irqवापस_t nspपूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक   base;
	अचिन्हित अक्षर  irq_status, irq_phase, phase;
	काष्ठा scsi_cmnd *पंचांगpSC;
	अचिन्हित अक्षर  target, lun;
	अचिन्हित पूर्णांक  *sync_neg;
	पूर्णांक            i, पंचांगp;
	nsp_hw_data   *data;


	//nsp_dbg(NSP_DEBUG_INTR, "dev_id=0x%p", dev_id);
	//nsp_dbg(NSP_DEBUG_INTR, "host=0x%p", ((scsi_info_t *)dev_id)->host);

	अगर (                dev_id        != शून्य &&
	    ((scsi_info_t *)dev_id)->host != शून्य  ) अणु
		scsi_info_t *info = (scsi_info_t *)dev_id;

		data = (nsp_hw_data *)info->host->hostdata;
	पूर्ण अन्यथा अणु
		nsp_dbg(NSP_DEBUG_INTR, "host data wrong");
		वापस IRQ_NONE;
	पूर्ण

	//nsp_dbg(NSP_DEBUG_INTR, "&nsp_data_base=0x%p, dev_id=0x%p", &nsp_data_base, dev_id);

	base = data->BaseAddress;
	//nsp_dbg(NSP_DEBUG_INTR, "base=0x%x", base);

	/*
	 * पूर्णांकerrupt check
	 */
	nsp_ग_लिखो(base, IRQCONTROL, IRQCONTROL_IRQDISABLE);
	irq_status = nsp_पढ़ो(base, IRQSTATUS);
	//nsp_dbg(NSP_DEBUG_INTR, "irq_status=0x%x", irq_status);
	अगर ((irq_status == 0xff) || ((irq_status & IRQSTATUS_MASK) == 0)) अणु
		nsp_ग_लिखो(base, IRQCONTROL, 0);
		//nsp_dbg(NSP_DEBUG_INTR, "no irq/shared irq");
		वापस IRQ_NONE;
	पूर्ण

	/* XXX: IMPORTANT
	 * Do not पढ़ो an irq_phase रेजिस्टर अगर no scsi phase पूर्णांकerrupt.
	 * Unless, you should lose a scsi phase पूर्णांकerrupt.
	 */
	phase = nsp_index_पढ़ो(base, SCSIBUSMON);
	अगर((irq_status & IRQSTATUS_SCSI) != 0) अणु
		irq_phase = nsp_index_पढ़ो(base, IRQPHASESENCE);
	पूर्ण अन्यथा अणु
		irq_phase = 0;
	पूर्ण

	//nsp_dbg(NSP_DEBUG_INTR, "irq_phase=0x%x", irq_phase);

	/*
	 * समयr पूर्णांकerrupt handler (scsi vs समयr पूर्णांकerrupts)
	 */
	//nsp_dbg(NSP_DEBUG_INTR, "timercount=%d", data->TimerCount);
	अगर (data->TimerCount != 0) अणु
		//nsp_dbg(NSP_DEBUG_INTR, "stop timer");
		nsp_index_ग_लिखो(base, TIMERCOUNT, 0);
		nsp_index_ग_लिखो(base, TIMERCOUNT, 0);
		data->TimerCount = 0;
	पूर्ण

	अगर ((irq_status & IRQSTATUS_MASK) == IRQSTATUS_TIMER &&
	    data->SelectionTimeOut == 0) अणु
		//nsp_dbg(NSP_DEBUG_INTR, "timer start");
		nsp_ग_लिखो(base, IRQCONTROL, IRQCONTROL_TIMER_CLEAR);
		वापस IRQ_HANDLED;
	पूर्ण

	nsp_ग_लिखो(base, IRQCONTROL, IRQCONTROL_TIMER_CLEAR | IRQCONTROL_FIFO_CLEAR);

	अगर ((irq_status & IRQSTATUS_SCSI) &&
	    (irq_phase  & SCSI_RESET_IRQ)) अणु
		nsp_msg(KERN_ERR, "bus reset (power off?)");

		nsphw_init(data);
		nsp_bus_reset(data);

		अगर(data->CurrentSC != शून्य) अणु
			पंचांगpSC = data->CurrentSC;
			पंचांगpSC->result  = (DID_RESET                   << 16) |
				         ((पंचांगpSC->SCp.Message & 0xff) <<  8) |
				         ((पंचांगpSC->SCp.Status  & 0xff) <<  0);
			nsp_scsi_करोne(पंचांगpSC);
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (data->CurrentSC == शून्य) अणु
		nsp_msg(KERN_ERR, "CurrentSC==NULL irq_status=0x%x phase=0x%x irq_phase=0x%x this can't be happen. reset everything", irq_status, phase, irq_phase);
		nsphw_init(data);
		nsp_bus_reset(data);
		वापस IRQ_HANDLED;
	पूर्ण

	पंचांगpSC    = data->CurrentSC;
	target   = पंचांगpSC->device->id;
	lun      = पंचांगpSC->device->lun;
	sync_neg = &(data->Sync[target].SyncNegotiation);

	/*
	 * parse hardware SCSI irq reasons रेजिस्टर
	 */
	अगर (irq_status & IRQSTATUS_SCSI) अणु
		अगर (irq_phase & RESELECT_IRQ) अणु
			nsp_dbg(NSP_DEBUG_INTR, "reselect");
			nsp_ग_लिखो(base, IRQCONTROL, IRQCONTROL_RESELECT_CLEAR);
			अगर (nsp_reselected(पंचांगpSC) != FALSE) अणु
				वापस IRQ_HANDLED;
			पूर्ण
		पूर्ण

		अगर ((irq_phase & (PHASE_CHANGE_IRQ | LATCHED_BUS_FREE)) == 0) अणु
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण

	//show_phase(पंचांगpSC);

	चयन(पंचांगpSC->SCp.phase) अणु
	हाल PH_SELSTART:
		// *sync_neg = SYNC_NOT_YET;
		अगर ((phase & BUSMON_BSY) == 0) अणु
			//nsp_dbg(NSP_DEBUG_INTR, "selection count=%d", data->SelectionTimeOut);
			अगर (data->SelectionTimeOut >= NSP_SELTIMEOUT) अणु
				nsp_dbg(NSP_DEBUG_INTR, "selection time out");
				data->SelectionTimeOut = 0;
				nsp_index_ग_लिखो(base, SCSIBUSCTRL, 0);

				पंचांगpSC->result   = DID_TIME_OUT << 16;
				nsp_scsi_करोne(पंचांगpSC);

				वापस IRQ_HANDLED;
			पूर्ण
			data->SelectionTimeOut += 1;
			nsp_start_समयr(पंचांगpSC, 1000/51);
			वापस IRQ_HANDLED;
		पूर्ण

		/* attention निश्चित */
		//nsp_dbg(NSP_DEBUG_INTR, "attention assert");
		data->SelectionTimeOut = 0;
		पंचांगpSC->SCp.phase       = PH_SELECTED;
		nsp_index_ग_लिखो(base, SCSIBUSCTRL, SCSI_ATN);
		udelay(1);
		nsp_index_ग_लिखो(base, SCSIBUSCTRL, SCSI_ATN | AUTOसूचीECTION | ACKENB);
		वापस IRQ_HANDLED;

	हाल PH_RESELECT:
		//nsp_dbg(NSP_DEBUG_INTR, "phase reselect");
		// *sync_neg = SYNC_NOT_YET;
		अगर ((phase & BUSMON_PHASE_MASK) != BUSPHASE_MESSAGE_IN) अणु

			पंचांगpSC->result	= DID_ABORT << 16;
			nsp_scsi_करोne(पंचांगpSC);
			वापस IRQ_HANDLED;
		पूर्ण
		fallthrough;
	शेष:
		अगर ((irq_status & (IRQSTATUS_SCSI | IRQSTATUS_FIFO)) == 0) अणु
			वापस IRQ_HANDLED;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 * SCSI sequencer
	 */
	//nsp_dbg(NSP_DEBUG_INTR, "start scsi seq");

	/* normal disconnect */
	अगर (((पंचांगpSC->SCp.phase == PH_MSG_IN) || (पंचांगpSC->SCp.phase == PH_MSG_OUT)) &&
	    (irq_phase & LATCHED_BUS_FREE) != 0 ) अणु
		nsp_dbg(NSP_DEBUG_INTR, "normal disconnect irq_status=0x%x, phase=0x%x, irq_phase=0x%x", irq_status, phase, irq_phase);

		//*sync_neg       = SYNC_NOT_YET;

		/* all command complete and वापस status */
		अगर (पंचांगpSC->SCp.Message == COMMAND_COMPLETE) अणु
			पंचांगpSC->result = (DID_OK		             << 16) |
					((पंचांगpSC->SCp.Message & 0xff) <<  8) |
					((पंचांगpSC->SCp.Status  & 0xff) <<  0);
			nsp_dbg(NSP_DEBUG_INTR, "command complete result=0x%x", पंचांगpSC->result);
			nsp_scsi_करोne(पंचांगpSC);

			वापस IRQ_HANDLED;
		पूर्ण

		वापस IRQ_HANDLED;
	पूर्ण


	/* check unexpected bus मुक्त state */
	अगर (phase == 0) अणु
		nsp_msg(KERN_DEBUG, "unexpected bus free. irq_status=0x%x, phase=0x%x, irq_phase=0x%x", irq_status, phase, irq_phase);

		*sync_neg       = SYNC_NG;
		पंचांगpSC->result   = DID_ERROR << 16;
		nsp_scsi_करोne(पंचांगpSC);
		वापस IRQ_HANDLED;
	पूर्ण

	चयन (phase & BUSMON_PHASE_MASK) अणु
	हाल BUSPHASE_COMMAND:
		nsp_dbg(NSP_DEBUG_INTR, "BUSPHASE_COMMAND");
		अगर ((phase & BUSMON_REQ) == 0) अणु
			nsp_dbg(NSP_DEBUG_INTR, "REQ == 0");
			वापस IRQ_HANDLED;
		पूर्ण

		पंचांगpSC->SCp.phase = PH_COMMAND;

		nsp_nexus(पंचांगpSC);

		/* ग_लिखो scsi command */
		nsp_dbg(NSP_DEBUG_INTR, "cmd_len=%d", पंचांगpSC->cmd_len);
		nsp_index_ग_लिखो(base, COMMANDCTRL, CLEAR_COMMAND_POINTER);
		क्रम (i = 0; i < पंचांगpSC->cmd_len; i++) अणु
			nsp_index_ग_लिखो(base, COMMANDDATA, पंचांगpSC->cmnd[i]);
		पूर्ण
		nsp_index_ग_लिखो(base, COMMANDCTRL, CLEAR_COMMAND_POINTER | AUTO_COMMAND_GO);
		अवरोध;

	हाल BUSPHASE_DATA_OUT:
		nsp_dbg(NSP_DEBUG_INTR, "BUSPHASE_DATA_OUT");

		पंचांगpSC->SCp.phase        = PH_DATA;
		पंचांगpSC->SCp.have_data_in = IO_OUT;

		nsp_pio_ग_लिखो(पंचांगpSC);

		अवरोध;

	हाल BUSPHASE_DATA_IN:
		nsp_dbg(NSP_DEBUG_INTR, "BUSPHASE_DATA_IN");

		पंचांगpSC->SCp.phase        = PH_DATA;
		पंचांगpSC->SCp.have_data_in = IO_IN;

		nsp_pio_पढ़ो(पंचांगpSC);

		अवरोध;

	हाल BUSPHASE_STATUS:
		nsp_dataphase_bypass(पंचांगpSC);
		nsp_dbg(NSP_DEBUG_INTR, "BUSPHASE_STATUS");

		पंचांगpSC->SCp.phase = PH_STATUS;

		पंचांगpSC->SCp.Status = nsp_index_पढ़ो(base, SCSIDATAWITHACK);
		nsp_dbg(NSP_DEBUG_INTR, "message=0x%x status=0x%x", पंचांगpSC->SCp.Message, पंचांगpSC->SCp.Status);

		अवरोध;

	हाल BUSPHASE_MESSAGE_OUT:
		nsp_dbg(NSP_DEBUG_INTR, "BUSPHASE_MESSAGE_OUT");
		अगर ((phase & BUSMON_REQ) == 0) अणु
			जाओ समयr_out;
		पूर्ण

		पंचांगpSC->SCp.phase = PH_MSG_OUT;

		//*sync_neg = SYNC_NOT_YET;

		data->MsgLen = i = 0;
		data->MsgBuffer[i] = IDENTIFY(TRUE, lun); i++;

		अगर (*sync_neg == SYNC_NOT_YET) अणु
			data->Sync[target].SyncPeriod = 0;
			data->Sync[target].SyncOffset = 0;

			/**/
			data->MsgBuffer[i] = EXTENDED_MESSAGE; i++;
			data->MsgBuffer[i] = 3;            i++;
			data->MsgBuffer[i] = EXTENDED_SDTR; i++;
			data->MsgBuffer[i] = 0x0c;         i++;
			data->MsgBuffer[i] = 15;           i++;
			/**/
		पूर्ण
		data->MsgLen = i;

		nsp_analyze_sdtr(पंचांगpSC);
		show_message(data);
		nsp_message_out(पंचांगpSC);
		अवरोध;

	हाल BUSPHASE_MESSAGE_IN:
		nsp_dataphase_bypass(पंचांगpSC);
		nsp_dbg(NSP_DEBUG_INTR, "BUSPHASE_MESSAGE_IN");
		अगर ((phase & BUSMON_REQ) == 0) अणु
			जाओ समयr_out;
		पूर्ण

		पंचांगpSC->SCp.phase = PH_MSG_IN;
		nsp_message_in(पंचांगpSC);

		/**/
		अगर (*sync_neg == SYNC_NOT_YET) अणु
			//nsp_dbg(NSP_DEBUG_INTR, "sync target=%d,lun=%d",target,lun);

			अगर (data->MsgLen       >= 5            &&
			    data->MsgBuffer[0] == EXTENDED_MESSAGE &&
			    data->MsgBuffer[1] == 3            &&
			    data->MsgBuffer[2] == EXTENDED_SDTR ) अणु
				data->Sync[target].SyncPeriod = data->MsgBuffer[3];
				data->Sync[target].SyncOffset = data->MsgBuffer[4];
				//nsp_dbg(NSP_DEBUG_INTR, "sync ok, %d %d", data->MsgBuffer[3], data->MsgBuffer[4]);
				*sync_neg = SYNC_OK;
			पूर्ण अन्यथा अणु
				data->Sync[target].SyncPeriod = 0;
				data->Sync[target].SyncOffset = 0;
				*sync_neg = SYNC_NG;
			पूर्ण
			nsp_analyze_sdtr(पंचांगpSC);
		पूर्ण
		/**/

		/* search last messeage byte */
		पंचांगp = -1;
		क्रम (i = 0; i < data->MsgLen; i++) अणु
			पंचांगp = data->MsgBuffer[i];
			अगर (data->MsgBuffer[i] == EXTENDED_MESSAGE) अणु
				i += (1 + data->MsgBuffer[i+1]);
			पूर्ण
		पूर्ण
		पंचांगpSC->SCp.Message = पंचांगp;

		nsp_dbg(NSP_DEBUG_INTR, "message=0x%x len=%d", पंचांगpSC->SCp.Message, data->MsgLen);
		show_message(data);

		अवरोध;

	हाल BUSPHASE_SELECT:
	शेष:
		nsp_dbg(NSP_DEBUG_INTR, "BUSPHASE other");

		अवरोध;
	पूर्ण

	//nsp_dbg(NSP_DEBUG_INTR, "out");
	वापस IRQ_HANDLED; 	

समयr_out:
	nsp_start_समयr(पंचांगpSC, 1000/102);
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित NSP_DEBUG
#समावेश "nsp_debug.c"
#पूर्ण_अगर	/* NSP_DEBUG */

/*----------------------------------------------------------------*/
/* look क्रम ninja3 card and init अगर found			  */
/*----------------------------------------------------------------*/
अटल काष्ठा Scsi_Host *nsp_detect(काष्ठा scsi_host_ढाँचा *sht)
अणु
	काष्ठा Scsi_Host *host;	/* रेजिस्टरed host काष्ठाure */
	nsp_hw_data *data_b = &nsp_data_base, *data;

	nsp_dbg(NSP_DEBUG_INIT, "this_id=%d", sht->this_id);
	host = scsi_host_alloc(&nsp_driver_ढाँचा, माप(nsp_hw_data));
	अगर (host == शून्य) अणु
		nsp_dbg(NSP_DEBUG_INIT, "host failed");
		वापस शून्य;
	पूर्ण

	स_नकल(host->hostdata, data_b, माप(nsp_hw_data));
	data = (nsp_hw_data *)host->hostdata;
	data->ScsiInfo->host = host;
#अगर_घोषित NSP_DEBUG
	data->CmdId = 0;
#पूर्ण_अगर

	nsp_dbg(NSP_DEBUG_INIT, "irq=%d,%d", data_b->IrqNumber, ((nsp_hw_data *)host->hostdata)->IrqNumber);

	host->unique_id	  = data->BaseAddress;
	host->io_port	  = data->BaseAddress;
	host->n_io_port	  = data->NumAddress;
	host->irq	  = data->IrqNumber;
	host->base        = data->MmioAddress;

	spin_lock_init(&(data->Lock));

	snम_लिखो(data->nspinfo,
		 माप(data->nspinfo),
		 "NinjaSCSI-3/32Bi Driver $Revision: 1.23 $ IO:0x%04lx-0x%04lx MMIO(virt addr):0x%04lx IRQ:%02d",
		 host->io_port, host->io_port + host->n_io_port - 1,
		 host->base,
		 host->irq);
	sht->name	  = data->nspinfo;

	nsp_dbg(NSP_DEBUG_INIT, "end");


	वापस host; /* detect करोne. */
पूर्ण

/*----------------------------------------------------------------*/
/* वापस info string						  */
/*----------------------------------------------------------------*/
अटल स्थिर अक्षर *nsp_info(काष्ठा Scsi_Host *shpnt)
अणु
	nsp_hw_data *data = (nsp_hw_data *)shpnt->hostdata;

	वापस data->nspinfo;
पूर्ण

अटल पूर्णांक nsp_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	पूर्णांक id;
	पूर्णांक speed;
	अचिन्हित दीर्घ flags;
	nsp_hw_data *data;
	पूर्णांक hostno;

	hostno = host->host_no;
	data = (nsp_hw_data *)host->hostdata;

	seq_माला_दो(m, "NinjaSCSI status\n\n"
		"Driver version:        $Revision: 1.23 $\n");
	seq_म_लिखो(m, "SCSI host No.:         %d\n",          hostno);
	seq_म_लिखो(m, "IRQ:                   %d\n",          host->irq);
	seq_म_लिखो(m, "IO:                    0x%lx-0x%lx\n", host->io_port, host->io_port + host->n_io_port - 1);
	seq_म_लिखो(m, "MMIO(virtual address): 0x%lx-0x%lx\n", host->base, host->base + data->MmioLength - 1);
	seq_म_लिखो(m, "sg_tablesize:          %d\n",          host->sg_tablesize);

	seq_माला_दो(m, "burst transfer mode:   ");
	चयन (nsp_burst_mode) अणु
	हाल BURST_IO8:
		seq_माला_दो(m, "io8");
		अवरोध;
	हाल BURST_IO32:
		seq_माला_दो(m, "io32");
		अवरोध;
	हाल BURST_MEM32:
		seq_माला_दो(m, "mem32");
		अवरोध;
	शेष:
		seq_माला_दो(m, "???");
		अवरोध;
	पूर्ण
	seq_अ_दो(m, '\n');


	spin_lock_irqsave(&(data->Lock), flags);
	seq_म_लिखो(m, "CurrentSC:             0x%p\n\n",      data->CurrentSC);
	spin_unlock_irqrestore(&(data->Lock), flags);

	seq_माला_दो(m, "SDTR status\n");
	क्रम(id = 0; id < ARRAY_SIZE(data->Sync); id++) अणु

		seq_म_लिखो(m, "id %d: ", id);

		अगर (id == host->this_id) अणु
			seq_माला_दो(m, "----- NinjaSCSI-3 host adapter\n");
			जारी;
		पूर्ण

		चयन(data->Sync[id].SyncNegotiation) अणु
		हाल SYNC_OK:
			seq_माला_दो(m, " sync");
			अवरोध;
		हाल SYNC_NG:
			seq_माला_दो(m, "async");
			अवरोध;
		हाल SYNC_NOT_YET:
			seq_माला_दो(m, " none");
			अवरोध;
		शेष:
			seq_माला_दो(m, "?????");
			अवरोध;
		पूर्ण

		अगर (data->Sync[id].SyncPeriod != 0) अणु
			speed = 1000000 / (data->Sync[id].SyncPeriod * 4);

			seq_म_लिखो(m, " transfer %d.%dMB/s, offset %d",
				speed / 1000,
				speed % 1000,
				data->Sync[id].SyncOffset
				);
		पूर्ण
		seq_अ_दो(m, '\n');
	पूर्ण
	वापस 0;
पूर्ण

/*---------------------------------------------------------------*/
/* error handler                                                 */
/*---------------------------------------------------------------*/

/*
अटल पूर्णांक nsp_eh_पात(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp_dbg(NSP_DEBUG_BUSRESET, "SCpnt=0x%p", SCpnt);

	वापस nsp_eh_bus_reset(SCpnt);
पूर्ण*/

अटल पूर्णांक nsp_bus_reset(nsp_hw_data *data)
अणु
	अचिन्हित पूर्णांक base = data->BaseAddress;
	पूर्णांक	     i;

	nsp_ग_लिखो(base, IRQCONTROL, IRQCONTROL_ALLMASK);

	nsp_index_ग_लिखो(base, SCSIBUSCTRL, SCSI_RST);
	mdelay(100); /* 100ms */
	nsp_index_ग_लिखो(base, SCSIBUSCTRL, 0);
	क्रम(i = 0; i < 5; i++) अणु
		nsp_index_पढ़ो(base, IRQPHASESENCE); /* dummy पढ़ो */
	पूर्ण

	nsphw_init_sync(data);

	nsp_ग_लिखो(base, IRQCONTROL, IRQCONTROL_ALLCLEAR);

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक nsp_eh_bus_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	nsp_dbg(NSP_DEBUG_BUSRESET, "SCpnt=0x%p", SCpnt);

	वापस nsp_bus_reset(data);
पूर्ण

अटल पूर्णांक nsp_eh_host_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	nsp_hw_data *data = (nsp_hw_data *)SCpnt->device->host->hostdata;

	nsp_dbg(NSP_DEBUG_BUSRESET, "in");

	nsphw_init(data);

	वापस SUCCESS;
पूर्ण


/**********************************************************************
  PCMCIA functions
**********************************************************************/

अटल पूर्णांक nsp_cs_probe(काष्ठा pcmcia_device *link)
अणु
	scsi_info_t  *info;
	nsp_hw_data  *data = &nsp_data_base;
	पूर्णांक ret;

	nsp_dbg(NSP_DEBUG_INIT, "in");

	/* Create new SCSI device */
	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (info == शून्य) अणु वापस -ENOMEM; पूर्ण
	info->p_dev = link;
	link->priv = info;
	data->ScsiInfo = info;

	nsp_dbg(NSP_DEBUG_INIT, "info=0x%p", info);

	ret = nsp_cs_config(link);

	nsp_dbg(NSP_DEBUG_INIT, "link=0x%p", link);
	वापस ret;
पूर्ण /* nsp_cs_attach */


अटल व्योम nsp_cs_detach(काष्ठा pcmcia_device *link)
अणु
	nsp_dbg(NSP_DEBUG_INIT, "in, link=0x%p", link);

	((scsi_info_t *)link->priv)->stop = 1;
	nsp_cs_release(link);

	kमुक्त(link->priv);
	link->priv = शून्य;
पूर्ण /* nsp_cs_detach */


अटल पूर्णांक nsp_cs_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	nsp_hw_data		*data = priv_data;

	अगर (p_dev->config_index == 0)
		वापस -ENODEV;

	/* This reserves IO space but करोesn't actually enable it */
	अगर (pcmcia_request_io(p_dev) != 0)
		जाओ next_entry;

	अगर (resource_size(p_dev->resource[2])) अणु
		p_dev->resource[2]->flags |= (WIN_DATA_WIDTH_16 |
					WIN_MEMORY_TYPE_CM |
					WIN_ENABLE);
		अगर (p_dev->resource[2]->end < 0x1000)
			p_dev->resource[2]->end = 0x1000;
		अगर (pcmcia_request_winकरोw(p_dev, p_dev->resource[2], 0) != 0)
			जाओ next_entry;
		अगर (pcmcia_map_mem_page(p_dev, p_dev->resource[2],
						p_dev->card_addr) != 0)
			जाओ next_entry;

		data->MmioAddress = (अचिन्हित दीर्घ)
			ioremap(p_dev->resource[2]->start,
					resource_size(p_dev->resource[2]));
		data->MmioLength  = resource_size(p_dev->resource[2]);
	पूर्ण
	/* If we got this far, we're cool! */
	वापस 0;

next_entry:
	nsp_dbg(NSP_DEBUG_INIT, "next");
	pcmcia_disable_device(p_dev);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक nsp_cs_config(काष्ठा pcmcia_device *link)
अणु
	पूर्णांक		  ret;
	scsi_info_t	 *info	 = link->priv;
	काष्ठा Scsi_Host *host;
	nsp_hw_data      *data = &nsp_data_base;

	nsp_dbg(NSP_DEBUG_INIT, "in");

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_CHECK_VCC |
		CONF_AUTO_SET_VPP | CONF_AUTO_AUDIO | CONF_AUTO_SET_IOMEM |
		CONF_AUTO_SET_IO;

	ret = pcmcia_loop_config(link, nsp_cs_config_check, data);
	अगर (ret)
		जाओ cs_failed;

	अगर (pcmcia_request_irq(link, nspपूर्णांकr))
		जाओ cs_failed;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ cs_failed;

	अगर (मुक्त_ports) अणु
		अगर (link->resource[0]) अणु
			release_region(link->resource[0]->start,
					resource_size(link->resource[0]));
		पूर्ण
		अगर (link->resource[1]) अणु
			release_region(link->resource[1]->start,
					resource_size(link->resource[1]));
		पूर्ण
	पूर्ण

	/* Set port and IRQ */
	data->BaseAddress = link->resource[0]->start;
	data->NumAddress  = resource_size(link->resource[0]);
	data->IrqNumber   = link->irq;

	nsp_dbg(NSP_DEBUG_INIT, "I/O[0x%x+0x%x] IRQ %d",
		data->BaseAddress, data->NumAddress, data->IrqNumber);

	अगर(nsphw_init(data) == FALSE) अणु
		जाओ cs_failed;
	पूर्ण

	host = nsp_detect(&nsp_driver_ढाँचा);

	अगर (host == शून्य) अणु
		nsp_dbg(NSP_DEBUG_INIT, "detect failed");
		जाओ cs_failed;
	पूर्ण


	ret = scsi_add_host (host, शून्य);
	अगर (ret)
		जाओ cs_failed;

	scsi_scan_host(host);

	info->host = host;

	वापस 0;

 cs_failed:
	nsp_dbg(NSP_DEBUG_INIT, "config fail");
	nsp_cs_release(link);

	वापस -ENODEV;
पूर्ण /* nsp_cs_config */


अटल व्योम nsp_cs_release(काष्ठा pcmcia_device *link)
अणु
	scsi_info_t *info = link->priv;
	nsp_hw_data *data = शून्य;

	अगर (info->host == शून्य) अणु
		nsp_msg(KERN_DEBUG, "unexpected card release call.");
	पूर्ण अन्यथा अणु
		data = (nsp_hw_data *)info->host->hostdata;
	पूर्ण

	nsp_dbg(NSP_DEBUG_INIT, "link=0x%p", link);

	/* Unlink the device chain */
	अगर (info->host != शून्य) अणु
		scsi_हटाओ_host(info->host);
	पूर्ण

	अगर (resource_size(link->resource[2])) अणु
		अगर (data != शून्य) अणु
			iounmap((व्योम *)(data->MmioAddress));
		पूर्ण
	पूर्ण
	pcmcia_disable_device(link);

	अगर (info->host != शून्य) अणु
		scsi_host_put(info->host);
	पूर्ण
पूर्ण /* nsp_cs_release */

अटल पूर्णांक nsp_cs_suspend(काष्ठा pcmcia_device *link)
अणु
	scsi_info_t *info = link->priv;
	nsp_hw_data *data;

	nsp_dbg(NSP_DEBUG_INIT, "event: suspend");

	अगर (info->host != शून्य) अणु
		nsp_msg(KERN_INFO, "clear SDTR status");

		data = (nsp_hw_data *)info->host->hostdata;

		nsphw_init_sync(data);
	पूर्ण

	info->stop = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक nsp_cs_resume(काष्ठा pcmcia_device *link)
अणु
	scsi_info_t *info = link->priv;
	nsp_hw_data *data;

	nsp_dbg(NSP_DEBUG_INIT, "event: resume");

	info->stop = 0;

	अगर (info->host != शून्य) अणु
		nsp_msg(KERN_INFO, "reset host and bus");

		data = (nsp_hw_data *)info->host->hostdata;

		nsphw_init   (data);
		nsp_bus_reset(data);
	पूर्ण

	वापस 0;
पूर्ण

/*======================================================================*
 *	module entry poपूर्णांक
 *====================================================================*/
अटल स्थिर काष्ठा pcmcia_device_id nsp_cs_ids[] = अणु
	PCMCIA_DEVICE_PROD_ID123("IO DATA", "CBSC16       ", "1", 0x547e66dc, 0x0d63a3fd, 0x51de003a),
	PCMCIA_DEVICE_PROD_ID123("KME    ", "SCSI-CARD-001", "1", 0x534c02bc, 0x52008408, 0x51de003a),
	PCMCIA_DEVICE_PROD_ID123("KME    ", "SCSI-CARD-002", "1", 0x534c02bc, 0xcb09d5b2, 0x51de003a),
	PCMCIA_DEVICE_PROD_ID123("KME    ", "SCSI-CARD-003", "1", 0x534c02bc, 0xbc0ee524, 0x51de003a),
	PCMCIA_DEVICE_PROD_ID123("KME    ", "SCSI-CARD-004", "1", 0x534c02bc, 0x226a7087, 0x51de003a),
	PCMCIA_DEVICE_PROD_ID123("WBT", "NinjaSCSI-3", "R1.0", 0xc7ba805f, 0xfdc7c97d, 0x6973710e),
	PCMCIA_DEVICE_PROD_ID123("WORKBIT", "UltraNinja-16", "1", 0x28191418, 0xb70f4b09, 0x51de003a),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, nsp_cs_ids);

अटल काष्ठा pcmcia_driver nsp_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "nsp_cs",
	.probe		= nsp_cs_probe,
	.हटाओ		= nsp_cs_detach,
	.id_table	= nsp_cs_ids,
	.suspend	= nsp_cs_suspend,
	.resume		= nsp_cs_resume,
पूर्ण;
module_pcmcia_driver(nsp_driver);

/* end */
