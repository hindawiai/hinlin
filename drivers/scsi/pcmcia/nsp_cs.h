<शैली गुरु>
/*=======================================================/
  Header file क्रम nsp_cs.c
      By: YOKOTA Hiroshi <yokota@netlab.is.tsukuba.ac.jp>

    Ver.1.0 : Cut unused lines.
    Ver 0.1 : Initial version.

    This software may be used and distributed according to the terms of
    the GNU General Public License.

=========================================================*/

#अगर_अघोषित  __nsp_cs__
#घोषणा  __nsp_cs__

/* क्रम debugging */
//#घोषणा NSP_DEBUG 9

/*
#घोषणा अटल
#घोषणा अंतरभूत
*/

/************************************
 * Some useful macros...
 */

/* SCSI initiator must be ID 7 */
#घोषणा NSP_INITIATOR_ID  7

#घोषणा NSP_SELTIMEOUT 200

/***************************************************************************
 * रेजिस्टर definitions
 ***************************************************************************/
/*========================================================================
 * base रेजिस्टर
 ========================================================================*/
#घोषणा	IRQCONTROL	0x00  /* R */
#  define IRQCONTROL_RESELECT_CLEAR     BIT(0)
#  define IRQCONTROL_PHASE_CHANGE_CLEAR BIT(1)
#  define IRQCONTROL_TIMER_CLEAR        BIT(2)
#  define IRQCONTROL_FIFO_CLEAR         BIT(3)
#  define IRQCONTROL_ALLMASK            0xff
#  define IRQCONTROL_ALLCLEAR           (IRQCONTROL_RESELECT_CLEAR     | \
					 IRQCONTROL_PHASE_CHANGE_CLEAR | \
					 IRQCONTROL_TIMER_CLEAR        | \
					 IRQCONTROL_FIFO_CLEAR          )
#  define IRQCONTROL_IRQDISABLE         0xf0

#घोषणा	IRQSTATUS	0x00  /* W */
#  define IRQSTATUS_SCSI  BIT(0)
#  define IRQSTATUS_TIMER BIT(2)
#  define IRQSTATUS_FIFO  BIT(3)
#  define IRQSTATUS_MASK  0x0f

#घोषणा	IFSELECT	0x01 /* W */
#  define IF_IFSEL    BIT(0)
#  define IF_REGSEL   BIT(2)

#घोषणा	FIFOSTATUS	0x01 /* R */
#  define FIFOSTATUS_CHIP_REVISION_MASK 0x0f
#  define FIFOSTATUS_CHIP_ID_MASK       0x70
#  define FIFOSTATUS_FULL_EMPTY         BIT(7)

#घोषणा	INDEXREG	0x02 /* R/W */
#घोषणा	DATAREG		0x03 /* R/W */
#घोषणा	FIFODATA	0x04 /* R/W */
#घोषणा	FIFODATA1	0x05 /* R/W */
#घोषणा	FIFODATA2	0x06 /* R/W */
#घोषणा	FIFODATA3	0x07 /* R/W */

/*====================================================================
 * indexed रेजिस्टर
 ====================================================================*/
#घोषणा EXTBUSCTRL	0x10 /* R/W,deleted */

#घोषणा CLOCKDIV	0x11 /* R/W */
#  define CLOCK_40M 0x02
#  define CLOCK_20M 0x01
#  define FAST_20   BIT(2)

#घोषणा TERMPWRCTRL	0x13 /* R/W */
#  define POWER_ON BIT(0)

#घोषणा SCSIIRQMODE	0x15 /* R/W */
#  define SCSI_PHASE_CHANGE_EI BIT(0)
#  define RESELECT_EI          BIT(4)
#  define FIFO_IRQ_EI          BIT(5)
#  define SCSI_RESET_IRQ_EI    BIT(6)

#घोषणा IRQPHASESENCE	0x16 /* R */
#  define LATCHED_MSG      BIT(0)
#  define LATCHED_IO       BIT(1)
#  define LATCHED_CD       BIT(2)
#  define LATCHED_BUS_FREE BIT(3)
#  define PHASE_CHANGE_IRQ BIT(4)
#  define RESELECT_IRQ     BIT(5)
#  define FIFO_IRQ         BIT(6)
#  define SCSI_RESET_IRQ   BIT(7)

#घोषणा TIMERCOUNT	0x17 /* R/W */

#घोषणा SCSIBUSCTRL	0x18 /* R/W */
#  define SCSI_SEL         BIT(0)
#  define SCSI_RST         BIT(1)
#  define SCSI_DATAOUT_ENB BIT(2)
#  define SCSI_ATN         BIT(3)
#  define SCSI_ACK         BIT(4)
#  define SCSI_BSY         BIT(5)
#  define AUTOसूचीECTION    BIT(6)
#  define ACKENB           BIT(7)

#घोषणा SCSIBUSMON	0x19 /* R */

#घोषणा SETARBIT	0x1A /* W */
#  define ARBIT_GO         BIT(0)
#  define ARBIT_FLAG_CLEAR BIT(1)

#घोषणा ARBITSTATUS	0x1A /* R */
/*#  define ARBIT_GO        BIT(0)*/
#  define ARBIT_WIN        BIT(1)
#  define ARBIT_FAIL       BIT(2)
#  define RESELECT_FLAG    BIT(3)

#घोषणा PARITYCTRL	0x1B  /* W */
#घोषणा PARITYSTATUS	0x1B  /* R */

#घोषणा COMMANDCTRL	0x1C  /* W */
#  define CLEAR_COMMAND_POINTER BIT(0)
#  define AUTO_COMMAND_GO       BIT(1)

#घोषणा RESELECTID	0x1C  /* R   */
#घोषणा COMMANDDATA	0x1D  /* R/W */

#घोषणा POINTERCLR	0x1E  /*   W */
#  define POINTER_CLEAR      BIT(0)
#  define ACK_COUNTER_CLEAR  BIT(1)
#  define REQ_COUNTER_CLEAR  BIT(2)
#  define HOST_COUNTER_CLEAR BIT(3)
#  define READ_SOURCE        (BIT(4) | BIT(5))
#    define ACK_COUNTER        (0)
#    define REQ_COUNTER        (BIT(4))
#    define HOST_COUNTER       (BIT(5))

#घोषणा TRANSFERCOUNT	0x1E  /* R   */

#घोषणा TRANSFERMODE	0x20  /* R/W */
#  define MODE_MEM8   BIT(0)
#  define MODE_MEM32  BIT(1)
#  define MODE_ADR24  BIT(2)
#  define MODE_ADR32  BIT(3)
#  define MODE_IO8    BIT(4)
#  define MODE_IO32   BIT(5)
#  define TRANSFER_GO BIT(6)
#  define BRAIND      BIT(7)

#घोषणा SYNCREG		0x21 /* R/W */
#  define SYNCREG_OFFSET_MASK  0x0f
#  define SYNCREG_PERIOD_MASK  0xf0
#  define SYNCREG_PERIOD_SHIFT 4

#घोषणा SCSIDATALATCH	0x22 /*   W */
#घोषणा SCSIDATAIN	0x22 /* R   */
#घोषणा SCSIDATAWITHACK	0x23 /* R/W */
#घोषणा SCAMCONTROL	0x24 /*   W */
#घोषणा SCAMSTATUS	0x24 /* R   */
#घोषणा SCAMDATA	0x25 /* R/W */

#घोषणा OTHERCONTROL	0x26 /* R/W */
#  define TPL_ROM_WRITE_EN BIT(0)
#  define TPWR_OUT         BIT(1)
#  define TPWR_SENSE       BIT(2)
#  define RA8_CONTROL      BIT(3)

#घोषणा ACKWIDTH	0x27 /* R/W */
#घोषणा CLRTESTPNT	0x28 /*   W */
#घोषणा ACKCNTLD	0x29 /*   W */
#घोषणा REQCNTLD	0x2A /*   W */
#घोषणा HSTCNTLD	0x2B /*   W */
#घोषणा CHECKSUM	0x2C /* R/W */

/************************************************************************
 * Input status bit definitions.
 ************************************************************************/
#घोषणा S_MESSAGE	BIT(0)    /* Message line from SCSI bus      */
#घोषणा S_IO		BIT(1)    /* Input/Output line from SCSI bus */
#घोषणा S_CD		BIT(2)    /* Command/Data line from SCSI bus */
#घोषणा S_BUSY		BIT(3)    /* Busy line from SCSI bus         */
#घोषणा S_ACK		BIT(4)    /* Acknowledge line from SCSI bus  */
#घोषणा S_REQUEST	BIT(5)    /* Request line from SCSI bus      */
#घोषणा S_SELECT	BIT(6)	  /*                                 */
#घोषणा S_ATN		BIT(7)	  /*                                 */

/***********************************************************************
 * Useful Bus Monitor status combinations.
 ***********************************************************************/
#घोषणा BUSMON_SEL         S_SELECT
#घोषणा BUSMON_BSY         S_BUSY
#घोषणा BUSMON_REQ         S_REQUEST
#घोषणा BUSMON_IO          S_IO
#घोषणा BUSMON_ACK         S_ACK
#घोषणा BUSMON_BUS_FREE    0
#घोषणा BUSMON_COMMAND     ( S_BUSY | S_CD |                    S_REQUEST )
#घोषणा BUSMON_MESSAGE_IN  ( S_BUSY | S_CD | S_IO | S_MESSAGE | S_REQUEST )
#घोषणा BUSMON_MESSAGE_OUT ( S_BUSY | S_CD |        S_MESSAGE | S_REQUEST )
#घोषणा BUSMON_DATA_IN     ( S_BUSY |        S_IO |             S_REQUEST )
#घोषणा BUSMON_DATA_OUT    ( S_BUSY |                           S_REQUEST )
#घोषणा BUSMON_STATUS      ( S_BUSY | S_CD | S_IO |             S_REQUEST )
#घोषणा BUSMON_SELECT      (                 S_IO |                        S_SELECT )
#घोषणा BUSMON_RESELECT    (                 S_IO |                        S_SELECT )
#घोषणा BUSMON_PHASE_MASK  (          S_CD | S_IO | S_MESSAGE |            S_SELECT )

#घोषणा BUSPHASE_SELECT      ( BUSMON_SELECT      & BUSMON_PHASE_MASK )
#घोषणा BUSPHASE_COMMAND     ( BUSMON_COMMAND     & BUSMON_PHASE_MASK )
#घोषणा BUSPHASE_MESSAGE_IN  ( BUSMON_MESSAGE_IN  & BUSMON_PHASE_MASK )
#घोषणा BUSPHASE_MESSAGE_OUT ( BUSMON_MESSAGE_OUT & BUSMON_PHASE_MASK )
#घोषणा BUSPHASE_DATA_IN     ( BUSMON_DATA_IN     & BUSMON_PHASE_MASK )
#घोषणा BUSPHASE_DATA_OUT    ( BUSMON_DATA_OUT    & BUSMON_PHASE_MASK )
#घोषणा BUSPHASE_STATUS      ( BUSMON_STATUS      & BUSMON_PHASE_MASK )

/*====================================================================*/

प्रकार काष्ठा scsi_info_t अणु
	काष्ठा pcmcia_device	*p_dev;
	काष्ठा Scsi_Host      *host;
	पूर्णांक                    stop;
पूर्ण scsi_info_t;


/* synchronous transfer negotiation data */
प्रकार काष्ठा _sync_data अणु
	अचिन्हित पूर्णांक SyncNegotiation;
#घोषणा SYNC_NOT_YET 0
#घोषणा SYNC_OK      1
#घोषणा SYNC_NG      2

	अचिन्हित पूर्णांक  SyncPeriod;
	अचिन्हित पूर्णांक  SyncOffset;
	अचिन्हित अक्षर SyncRegister;
	अचिन्हित अक्षर AckWidth;
पूर्ण sync_data;

प्रकार काष्ठा _nsp_hw_data अणु
	अचिन्हित पूर्णांक  BaseAddress;
	अचिन्हित पूर्णांक  NumAddress;
	अचिन्हित पूर्णांक  IrqNumber;

	अचिन्हित दीर्घ MmioAddress;
#घोषणा NSP_MMIO_OFFSET 0x0800
	अचिन्हित दीर्घ MmioLength;

	अचिन्हित अक्षर ScsiClockDiv;

	अचिन्हित अक्षर TransferMode;

	पूर्णांक           TimerCount;
	पूर्णांक           SelectionTimeOut;
	काष्ठा scsi_cmnd *CurrentSC;
	//पूर्णांक           CurrnetTarget;

	पूर्णांक           FअगरoCount;

#घोषणा MSGBUF_SIZE 20
	अचिन्हित अक्षर MsgBuffer[MSGBUF_SIZE];
	पूर्णांक MsgLen;

#घोषणा N_TARGET 8
	sync_data     Sync[N_TARGET];

	अक्षर nspinfo[110];     /* description */
	spinlock_t Lock;

	scsi_info_t   *ScsiInfo; /* attach <-> detect glue */


#अगर_घोषित NSP_DEBUG
	पूर्णांक CmdId; /* Accepted command serial number.
		      Used क्रम debugging.             */
#पूर्ण_अगर
पूर्ण nsp_hw_data;

/****************************************************************************
 *
 */

/* Card service functions */
अटल व्योम        nsp_cs_detach (काष्ठा pcmcia_device *p_dev);
अटल व्योम        nsp_cs_release(काष्ठा pcmcia_device *link);
अटल पूर्णांक        nsp_cs_config (काष्ठा pcmcia_device *link);

/* Linux SCSI subप्रणाली specअगरic functions */
अटल काष्ठा Scsi_Host *nsp_detect     (काष्ठा scsi_host_ढाँचा *sht);
अटल स्थिर  अक्षर      *nsp_info       (काष्ठा Scsi_Host *shpnt);
अटल        पूर्णांक        nsp_show_info  (काष्ठा seq_file *m,
	                                 काष्ठा Scsi_Host *host);
अटल पूर्णांक nsp_queuecommand(काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd *SCpnt);

/* Error handler */
/*अटल पूर्णांक nsp_eh_पात       (काष्ठा scsi_cmnd *SCpnt);*/
/*अटल पूर्णांक nsp_eh_device_reset(काष्ठा scsi_cmnd *SCpnt);*/
अटल पूर्णांक nsp_eh_bus_reset    (काष्ठा scsi_cmnd *SCpnt);
अटल पूर्णांक nsp_eh_host_reset   (काष्ठा scsi_cmnd *SCpnt);
अटल पूर्णांक nsp_bus_reset       (nsp_hw_data *data);

/* */
अटल पूर्णांक  nsphw_init           (nsp_hw_data *data);
अटल पूर्णांक  nsphw_start_selection(काष्ठा scsi_cmnd *SCpnt);
अटल व्योम nsp_start_समयr      (काष्ठा scsi_cmnd *SCpnt, पूर्णांक समय);
अटल पूर्णांक  nsp_fअगरo_count       (काष्ठा scsi_cmnd *SCpnt);
अटल व्योम nsp_pio_पढ़ो         (काष्ठा scsi_cmnd *SCpnt);
अटल व्योम nsp_pio_ग_लिखो        (काष्ठा scsi_cmnd *SCpnt);
अटल पूर्णांक  nsp_nexus            (काष्ठा scsi_cmnd *SCpnt);
अटल व्योम nsp_scsi_करोne        (काष्ठा scsi_cmnd *SCpnt);
अटल पूर्णांक  nsp_analyze_sdtr     (काष्ठा scsi_cmnd *SCpnt);
अटल पूर्णांक  nsp_negate_संकेत    (काष्ठा scsi_cmnd *SCpnt,
				  अचिन्हित अक्षर mask, अक्षर *str);
अटल पूर्णांक  nsp_expect_संकेत    (काष्ठा scsi_cmnd *SCpnt,
				  अचिन्हित अक्षर current_phase,
				  अचिन्हित अक्षर  mask);
अटल पूर्णांक  nsp_xfer             (काष्ठा scsi_cmnd *SCpnt, पूर्णांक phase);
अटल पूर्णांक  nsp_dataphase_bypass (काष्ठा scsi_cmnd *SCpnt);
अटल पूर्णांक  nsp_reselected       (काष्ठा scsi_cmnd *SCpnt);
अटल काष्ठा Scsi_Host *nsp_detect(काष्ठा scsi_host_ढाँचा *sht);

/* Interrupt handler */
//अटल irqवापस_t nspपूर्णांकr(पूर्णांक irq, व्योम *dev_id);

/* Debug */
#अगर_घोषित NSP_DEBUG
अटल व्योम show_command (काष्ठा scsi_cmnd *SCpnt);
अटल व्योम show_phase   (काष्ठा scsi_cmnd *SCpnt);
अटल व्योम show_busphase(अचिन्हित अक्षर stat);
अटल व्योम show_message (nsp_hw_data *data);
#अन्यथा
# define show_command(ptr)   /* */
# define show_phase(SCpnt)   /* */
# define show_busphase(stat) /* */
# define show_message(data)  /* */
#पूर्ण_अगर

/*
 * SCSI phase
 */
क्रमागत _scsi_phase अणु
	PH_UNDETERMINED ,
	PH_ARBSTART     ,
	PH_SELSTART     ,
	PH_SELECTED     ,
	PH_COMMAND      ,
	PH_DATA         ,
	PH_STATUS       ,
	PH_MSG_IN       ,
	PH_MSG_OUT      ,
	PH_DISCONNECT   ,
	PH_RESELECT     ,
	PH_ABORT        ,
	PH_RESET
पूर्ण;

क्रमागत _data_in_out अणु
	IO_UNKNOWN,
	IO_IN,
	IO_OUT
पूर्ण;

क्रमागत _burst_mode अणु
	BURST_IO8   = 0,
	BURST_IO32  = 1,
	BURST_MEM32 = 2,
पूर्ण;

/* scatter-gather table */
#  define BUFFER_ADDR ((अक्षर *)((sg_virt(SCpnt->SCp.buffer))))

#पूर्ण_अगर  /*__nsp_cs__*/
/* end */
