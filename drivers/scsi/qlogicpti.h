<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* qlogicpti.h: Perक्रमmance Technologies QlogicISP sbus card defines.
 *
 * Copyright (C) 1996 David S. Miller (davem@caipfs.rutgers.edu)
 */

#अगर_अघोषित _QLOGICPTI_H
#घोषणा _QLOGICPTI_H

/* Qlogic/SBUS controller रेजिस्टरs. */
#घोषणा SBUS_CFG1	0x006UL
#घोषणा SBUS_CTRL	0x008UL
#घोषणा SBUS_STAT	0x00aUL
#घोषणा SBUS_SEMAPHORE	0x00cUL
#घोषणा CMD_DMA_CTRL	0x022UL
#घोषणा DATA_DMA_CTRL	0x042UL
#घोषणा MBOX0		0x080UL
#घोषणा MBOX1		0x082UL
#घोषणा MBOX2		0x084UL
#घोषणा MBOX3		0x086UL
#घोषणा MBOX4		0x088UL
#घोषणा MBOX5		0x08aUL
#घोषणा CPU_CMD		0x214UL
#घोषणा CPU_ORIDE	0x224UL
#घोषणा CPU_PCTRL	0x272UL
#घोषणा CPU_PDIFF	0x276UL
#घोषणा RISC_PSR	0x420UL
#घोषणा RISC_MTREG	0x42EUL
#घोषणा HCCTRL		0x440UL

/* SCSI parameters क्रम this driver. */
#घोषणा MAX_TARGETS	16
#घोषणा MAX_LUNS	8

/* With the qlogic पूर्णांकerface, every queue slot can hold a SCSI
 * command with up to 4 scatter/gather entries.  If we need more
 * than 4 entries, continuation entries can be used that hold
 * another 7 entries each.  Unlike क्रम other drivers, this means
 * that the maximum number of scatter/gather entries we can
 * support at any given समय is a function of the number of queue
 * slots available.  That is, host->can_queue and host->sg_tablesize
 * are dynamic and _not_ independent.  This all works fine because
 * requests are queued serially and the scatter/gather limit is
 * determined क्रम each queue request anew.
 */
#घोषणा QLOGICPTI_REQ_QUEUE_LEN	255	/* must be घातer of two - 1 */
#घोषणा QLOGICPTI_MAX_SG(ql)	(4 + (((ql) > 0) ? 7*((ql) - 1) : 0))

/* mailbox command complete status codes */
#घोषणा MBOX_COMMAND_COMPLETE		0x4000
#घोषणा INVALID_COMMAND			0x4001
#घोषणा HOST_INTERFACE_ERROR		0x4002
#घोषणा TEST_FAILED			0x4003
#घोषणा COMMAND_ERROR			0x4005
#घोषणा COMMAND_PARAM_ERROR		0x4006

/* async event status codes */
#घोषणा ASYNC_SCSI_BUS_RESET		0x8001
#घोषणा SYSTEM_ERROR			0x8002
#घोषणा REQUEST_TRANSFER_ERROR		0x8003
#घोषणा RESPONSE_TRANSFER_ERROR		0x8004
#घोषणा REQUEST_QUEUE_WAKEUP		0x8005
#घोषणा EXECUTION_TIMEOUT_RESET		0x8006

/* Am I fucking pedantic or what? */
काष्ठा Entry_header अणु
#अगर_घोषित __BIG_ENDIAN
	u8	entry_cnt;
	u8	entry_type;
	u8	flags;
	u8	sys_def_1;
#अन्यथा /* __LITTLE_ENDIAN */
	u8	entry_type;
	u8	entry_cnt;
	u8	sys_def_1;
	u8	flags;
#पूर्ण_अगर
पूर्ण;

/* entry header type commands */
#घोषणा ENTRY_COMMAND		1
#घोषणा ENTRY_CONTINUATION	2
#घोषणा ENTRY_STATUS		3
#घोषणा ENTRY_MARKER		4
#घोषणा ENTRY_EXTENDED_COMMAND	5

/* entry header flag definitions */
#घोषणा EFLAG_CONTINUATION	1
#घोषणा EFLAG_BUSY		2
#घोषणा EFLAG_BAD_HEADER	4
#घोषणा EFLAG_BAD_PAYLOAD	8

काष्ठा dataseg अणु
	u32	d_base;
	u32	d_count;
पूर्ण;

काष्ठा Command_Entry अणु
	काष्ठा Entry_header	hdr;
	u32			handle;
#अगर_घोषित __BIG_ENDIAN
	u8			target_id;
	u8			target_lun;
#अन्यथा /* __LITTLE_ENDIAN */
	u8			target_lun;
	u8			target_id;
#पूर्ण_अगर
	u16			cdb_length;
	u16			control_flags;
	u16			rsvd;
	u16			समय_out;
	u16			segment_cnt;
	u8			cdb[12];
	काष्ठा dataseg		dataseg[4];
पूर्ण;

/* command entry control flag definitions */
#घोषणा CFLAG_NODISC		0x01
#घोषणा CFLAG_HEAD_TAG		0x02
#घोषणा CFLAG_ORDERED_TAG	0x04
#घोषणा CFLAG_SIMPLE_TAG	0x08
#घोषणा CFLAG_TAR_RTN		0x10
#घोषणा CFLAG_READ		0x20
#घोषणा CFLAG_WRITE		0x40

काष्ठा Ext_Command_Entry अणु
	काष्ठा Entry_header	hdr;
	u32			handle;
#अगर_घोषित __BIG_ENDIAN
	u8			target_id;
	u8			target_lun;
#अन्यथा /* __LITTLE_ENDIAN */
	u8			target_lun;
	u8			target_id;
#पूर्ण_अगर
	u16			cdb_length;
	u16			control_flags;
	u16			rsvd;
	u16			समय_out;
	u16			segment_cnt;
	u8			cdb[44];
पूर्ण;

काष्ठा Continuation_Entry अणु
	काष्ठा Entry_header	hdr;
	u32			reserved;
	काष्ठा dataseg		dataseg[7];
पूर्ण;

काष्ठा Marker_Entry अणु
	काष्ठा Entry_header	hdr;
	u32			reserved;
#अगर_घोषित __BIG_ENDIAN
	u8			target_id;
	u8			target_lun;
#अन्यथा /* __LITTLE_ENDIAN */
	u8			target_lun;
	u8			target_id;
#पूर्ण_अगर
#अगर_घोषित __BIG_ENDIAN
	u8			rsvd;
	u8			modअगरier;
#अन्यथा /* __LITTLE_ENDIAN */
	u8			modअगरier;
	u8			rsvd;
#पूर्ण_अगर
	u8			rsvds[52];
पूर्ण;

/* marker entry modअगरier definitions */
#घोषणा SYNC_DEVICE	0
#घोषणा SYNC_TARGET	1
#घोषणा SYNC_ALL	2

काष्ठा Status_Entry अणु
	काष्ठा Entry_header	hdr;
	u32			handle;
	u16			scsi_status;
	u16			completion_status;
	u16			state_flags;
	u16			status_flags;
	u16			समय;
	u16			req_sense_len;
	u32			residual;
	u8			rsvd[8];
	u8			req_sense_data[32];
पूर्ण;

/* status entry completion status definitions */
#घोषणा CS_COMPLETE			0x0000
#घोषणा CS_INCOMPLETE			0x0001
#घोषणा CS_DMA_ERROR			0x0002
#घोषणा CS_TRANSPORT_ERROR		0x0003
#घोषणा CS_RESET_OCCURRED		0x0004
#घोषणा CS_ABORTED			0x0005
#घोषणा CS_TIMEOUT			0x0006
#घोषणा CS_DATA_OVERRUN			0x0007
#घोषणा CS_COMMAND_OVERRUN		0x0008
#घोषणा CS_STATUS_OVERRUN		0x0009
#घोषणा CS_BAD_MESSAGE			0x000a
#घोषणा CS_NO_MESSAGE_OUT		0x000b
#घोषणा CS_EXT_ID_FAILED		0x000c
#घोषणा CS_IDE_MSG_FAILED		0x000d
#घोषणा CS_ABORT_MSG_FAILED		0x000e
#घोषणा CS_REJECT_MSG_FAILED		0x000f
#घोषणा CS_NOP_MSG_FAILED		0x0010
#घोषणा CS_PARITY_ERROR_MSG_FAILED	0x0011
#घोषणा CS_DEVICE_RESET_MSG_FAILED	0x0012
#घोषणा CS_ID_MSG_FAILED		0x0013
#घोषणा CS_UNEXP_BUS_FREE		0x0014
#घोषणा CS_DATA_UNDERRUN		0x0015
#घोषणा CS_BUS_RESET			0x001c

/* status entry state flag definitions */
#घोषणा SF_GOT_BUS			0x0100
#घोषणा SF_GOT_TARGET			0x0200
#घोषणा SF_SENT_CDB			0x0400
#घोषणा SF_TRANSFERRED_DATA		0x0800
#घोषणा SF_GOT_STATUS			0x1000
#घोषणा SF_GOT_SENSE			0x2000

/* status entry status flag definitions */
#घोषणा STF_DISCONNECT			0x0001
#घोषणा STF_SYNCHRONOUS			0x0002
#घोषणा STF_PARITY_ERROR		0x0004
#घोषणा STF_BUS_RESET			0x0008
#घोषणा STF_DEVICE_RESET		0x0010
#घोषणा STF_ABORTED			0x0020
#घोषणा STF_TIMEOUT			0x0040
#घोषणा STF_NEGOTIATION			0x0080

/* mailbox commands */
#घोषणा MBOX_NO_OP			0x0000
#घोषणा MBOX_LOAD_RAM			0x0001
#घोषणा MBOX_EXEC_FIRMWARE		0x0002
#घोषणा MBOX_DUMP_RAM			0x0003
#घोषणा MBOX_WRITE_RAM_WORD		0x0004
#घोषणा MBOX_READ_RAM_WORD		0x0005
#घोषणा MBOX_MAILBOX_REG_TEST		0x0006
#घोषणा MBOX_VERIFY_CHECKSUM		0x0007
#घोषणा MBOX_ABOUT_FIRMWARE		0x0008
#घोषणा MBOX_CHECK_FIRMWARE		0x000e
#घोषणा MBOX_INIT_REQ_QUEUE		0x0010
#घोषणा MBOX_INIT_RES_QUEUE		0x0011
#घोषणा MBOX_EXECUTE_IOCB		0x0012
#घोषणा MBOX_WAKE_UP			0x0013
#घोषणा MBOX_STOP_FIRMWARE		0x0014
#घोषणा MBOX_ABORT			0x0015
#घोषणा MBOX_ABORT_DEVICE		0x0016
#घोषणा MBOX_ABORT_TARGET		0x0017
#घोषणा MBOX_BUS_RESET			0x0018
#घोषणा MBOX_STOP_QUEUE			0x0019
#घोषणा MBOX_START_QUEUE		0x001a
#घोषणा MBOX_SINGLE_STEP_QUEUE		0x001b
#घोषणा MBOX_ABORT_QUEUE		0x001c
#घोषणा MBOX_GET_DEV_QUEUE_STATUS	0x001d
#घोषणा MBOX_GET_FIRMWARE_STATUS	0x001f
#घोषणा MBOX_GET_INIT_SCSI_ID		0x0020
#घोषणा MBOX_GET_SELECT_TIMEOUT		0x0021
#घोषणा MBOX_GET_RETRY_COUNT		0x0022
#घोषणा MBOX_GET_TAG_AGE_LIMIT		0x0023
#घोषणा MBOX_GET_CLOCK_RATE		0x0024
#घोषणा MBOX_GET_ACT_NEG_STATE		0x0025
#घोषणा MBOX_GET_ASYNC_DATA_SETUP_TIME	0x0026
#घोषणा MBOX_GET_SBUS_PARAMS		0x0027
#घोषणा MBOX_GET_TARGET_PARAMS		0x0028
#घोषणा MBOX_GET_DEV_QUEUE_PARAMS	0x0029
#घोषणा MBOX_SET_INIT_SCSI_ID		0x0030
#घोषणा MBOX_SET_SELECT_TIMEOUT		0x0031
#घोषणा MBOX_SET_RETRY_COUNT		0x0032
#घोषणा MBOX_SET_TAG_AGE_LIMIT		0x0033
#घोषणा MBOX_SET_CLOCK_RATE		0x0034
#घोषणा MBOX_SET_ACTIVE_NEG_STATE	0x0035
#घोषणा MBOX_SET_ASYNC_DATA_SETUP_TIME	0x0036
#घोषणा MBOX_SET_SBUS_CONTROL_PARAMS	0x0037
#घोषणा MBOX_SET_TARGET_PARAMS		0x0038
#घोषणा MBOX_SET_DEV_QUEUE_PARAMS	0x0039

काष्ठा host_param अणु
	u_लघु		initiator_scsi_id;
	u_लघु		bus_reset_delay;
	u_लघु		retry_count;
	u_लघु		retry_delay;
	u_लघु		async_data_setup_समय;
	u_लघु		req_ack_active_negation;
	u_लघु		data_line_active_negation;
	u_लघु		data_dma_burst_enable;
	u_लघु		command_dma_burst_enable;
	u_लघु		tag_aging;
	u_लघु		selection_समयout;
	u_लघु		max_queue_depth;
पूर्ण;

/*
 * Device Flags:
 *
 * Bit  Name
 * ---------
 *  7   Disconnect Privilege
 *  6   Parity Checking
 *  5   Wide Data Transfers
 *  4   Synchronous Data Transfers
 *  3   Tagged Queuing
 *  2   Automatic Request Sense
 *  1   Stop Queue on Check Condition
 *  0   Renegotiate on Error
 */

काष्ठा dev_param अणु
	u_लघु		device_flags;
	u_लघु		execution_throttle;
	u_लघु		synchronous_period;
	u_लघु		synchronous_offset;
	u_लघु		device_enable;
	u_लघु		reserved; /* pad */
पूर्ण;

/*
 * The result queue can be quite a bit smaller since continuation entries
 * करो not show up there:
 */
#घोषणा RES_QUEUE_LEN		255	/* Must be घातer of two - 1 */
#घोषणा QUEUE_ENTRY_LEN		64

#घोषणा NEXT_REQ_PTR(wheee)   (((wheee) + 1) & QLOGICPTI_REQ_QUEUE_LEN)
#घोषणा NEXT_RES_PTR(wheee)   (((wheee) + 1) & RES_QUEUE_LEN)
#घोषणा PREV_REQ_PTR(wheee)   (((wheee) - 1) & QLOGICPTI_REQ_QUEUE_LEN)
#घोषणा PREV_RES_PTR(wheee)   (((wheee) - 1) & RES_QUEUE_LEN)

काष्ठा pti_queue_entry अणु
	अक्षर __opaque[QUEUE_ENTRY_LEN];
पूर्ण;

काष्ठा scsi_cmnd;

/* Software state क्रम the driver. */
काष्ठा qlogicpti अणु
	/* These are the hot elements in the cache, so they come first. */
	व्योम __iomem             *qregs;                /* Adapter रेजिस्टरs          */
	काष्ठा pti_queue_entry   *res_cpu;              /* Ptr to RESPONSE bufs (CPU) */
	काष्ठा pti_queue_entry   *req_cpu;              /* Ptr to REQUEST bufs (CPU)  */

	u_पूर्णांक	                  req_in_ptr;		/* index of next request slot */
	u_पूर्णांक	                  res_out_ptr;		/* index of next result slot  */
	दीर्घ	                  send_marker;		/* must we send a marker?     */
	काष्ठा platक्रमm_device	 *op;
	अचिन्हित दीर्घ		  __pad;

	पूर्णांक                       cmd_count[MAX_TARGETS];
	अचिन्हित दीर्घ             tag_ages[MAX_TARGETS];

	/* The cmd->handler is only 32-bits, so that things work even on monster
	 * Ex000 sparc64 machines with >4GB of ram we just keep track of the
	 * scsi command poपूर्णांकers here.  This is essentially what Matt Jacob करोes. -DaveM
	 */
	काष्ठा scsi_cmnd         *cmd_slots[QLOGICPTI_REQ_QUEUE_LEN + 1];

	/* The rest of the elements are unimportant क्रम perक्रमmance. */
	काष्ठा qlogicpti         *next;
	dma_addr_t                res_dvma;             /* Ptr to RESPONSE bufs (DVMA)*/
	dma_addr_t                req_dvma;             /* Ptr to REQUEST bufs (DVMA) */
	u_अक्षर	                  fware_majrev, fware_minrev, fware_micrev;
	काष्ठा Scsi_Host         *qhost;
	पूर्णांक                       qpti_id;
	पूर्णांक                       scsi_id;
	पूर्णांक                       prom_node;
	पूर्णांक                       irq;
	अक्षर                      dअगरferential, ultra, घड़ी;
	अचिन्हित अक्षर             bursts;
	काष्ठा	host_param        host_param;
	काष्ठा	dev_param         dev_param[MAX_TARGETS];

	व्योम __iomem              *sreg;
#घोषणा SREG_TPOWER               0x80   /* State of termpwr           */
#घोषणा SREG_FUSE                 0x40   /* State of on board fuse     */
#घोषणा SREG_PDISAB               0x20   /* Disable state क्रम घातer on */
#घोषणा SREG_DSENSE               0x10   /* Sense क्रम dअगरferential     */
#घोषणा SREG_IMASK                0x0c   /* Interrupt level            */
#घोषणा SREG_SPMASK               0x03   /* Mask क्रम चयन pack       */
	अचिन्हित अक्षर             swsreg;
	अचिन्हित पूर्णांक
		gotirq	:	1,	/* this instance got an irq */
		is_pti	: 	1;	/* Non-zero अगर this is a PTI board. */
पूर्ण;

/* How to twiddle them bits... */

/* SBUS config रेजिस्टर one. */
#घोषणा SBUS_CFG1_EPAR          0x0100      /* Enable parity checking           */
#घोषणा SBUS_CFG1_FMASK         0x00f0      /* Forth code cycle mask            */
#घोषणा SBUS_CFG1_BENAB         0x0004      /* Burst dvma enable                */
#घोषणा SBUS_CFG1_B64           0x0003      /* Enable 64byte bursts             */
#घोषणा SBUS_CFG1_B32           0x0002      /* Enable 32byte bursts             */
#घोषणा SBUS_CFG1_B16           0x0001      /* Enable 16byte bursts             */
#घोषणा SBUS_CFG1_B8            0x0008      /* Enable 8byte bursts              */

/* SBUS control रेजिस्टर */
#घोषणा SBUS_CTRL_EसूचीQ         0x0020      /* Enable Data DVMA Interrupts      */
#घोषणा SBUS_CTRL_ECIRQ         0x0010      /* Enable Command DVMA Interrupts   */
#घोषणा SBUS_CTRL_ESIRQ         0x0008      /* Enable SCSI Processor Interrupts */
#घोषणा SBUS_CTRL_ERIRQ         0x0004      /* Enable RISC Processor Interrupts */
#घोषणा SBUS_CTRL_GENAB         0x0002      /* Global Interrupt Enable          */
#घोषणा SBUS_CTRL_RESET         0x0001      /* Soft Reset                       */

/* SBUS status रेजिस्टर */
#घोषणा SBUS_STAT_DINT          0x0020      /* Data DVMA IRQ pending            */
#घोषणा SBUS_STAT_CINT          0x0010      /* Command DVMA IRQ pending         */
#घोषणा SBUS_STAT_SINT          0x0008      /* SCSI Processor IRQ pending       */
#घोषणा SBUS_STAT_RINT          0x0004      /* RISC Processor IRQ pending       */
#घोषणा SBUS_STAT_GINT          0x0002      /* Global IRQ pending               */

/* SBUS semaphore रेजिस्टर */
#घोषणा SBUS_SEMAPHORE_STAT     0x0002      /* Semaphore status bit             */
#घोषणा SBUS_SEMAPHORE_LCK      0x0001      /* Semaphore lock bit               */

/* DVMA control रेजिस्टर */
#घोषणा DMA_CTRL_CSUSPEND       0x0010      /* DMA channel suspend              */
#घोषणा DMA_CTRL_CCLEAR         0x0008      /* DMA channel clear and reset      */
#घोषणा DMA_CTRL_FCLEAR         0x0004      /* DMA fअगरo clear                   */
#घोषणा DMA_CTRL_CIRQ           0x0002      /* DMA irq clear                    */
#घोषणा DMA_CTRL_DMASTART       0x0001      /* DMA transfer start               */

/* SCSI processor override रेजिस्टर */
#घोषणा CPU_ORIDE_ETRIG         0x8000      /* External trigger enable          */
#घोषणा CPU_ORIDE_STEP          0x4000      /* Single step mode enable          */
#घोषणा CPU_ORIDE_BKPT          0x2000      /* Breakpoपूर्णांक reg enable            */
#घोषणा CPU_ORIDE_PWRITE        0x1000      /* SCSI pin ग_लिखो enable            */
#घोषणा CPU_ORIDE_OFORCE        0x0800      /* Force outमाला_दो on                 */
#घोषणा CPU_ORIDE_LBACK         0x0400      /* SCSI loopback enable             */
#घोषणा CPU_ORIDE_PTEST         0x0200      /* Parity test enable               */
#घोषणा CPU_ORIDE_TENAB         0x0100      /* SCSI pins tristate enable        */
#घोषणा CPU_ORIDE_TPINS         0x0080      /* SCSI pins enable                 */
#घोषणा CPU_ORIDE_FRESET        0x0008      /* FIFO reset                       */
#घोषणा CPU_ORIDE_CTERM         0x0004      /* Command terminate                */
#घोषणा CPU_ORIDE_RREG          0x0002      /* Reset SCSI processor regs        */
#घोषणा CPU_ORIDE_RMOD          0x0001      /* Reset SCSI processor module      */

/* SCSI processor commands */
#घोषणा CPU_CMD_BRESET          0x300b      /* Reset SCSI bus                   */

/* SCSI processor pin control रेजिस्टर */
#घोषणा CPU_PCTRL_PVALID        0x8000      /* Phase bits are valid             */
#घोषणा CPU_PCTRL_PHI           0x0400      /* Parity bit high                  */
#घोषणा CPU_PCTRL_PLO           0x0200      /* Parity bit low                   */
#घोषणा CPU_PCTRL_REQ           0x0100      /* REQ bus संकेत                   */
#घोषणा CPU_PCTRL_ACK           0x0080      /* ACK bus संकेत                   */
#घोषणा CPU_PCTRL_RST           0x0040      /* RST bus संकेत                   */
#घोषणा CPU_PCTRL_BSY           0x0020      /* BSY bus संकेत                   */
#घोषणा CPU_PCTRL_SEL           0x0010      /* SEL bus संकेत                   */
#घोषणा CPU_PCTRL_ATN           0x0008      /* ATN bus संकेत                   */
#घोषणा CPU_PCTRL_MSG           0x0004      /* MSG bus संकेत                   */
#घोषणा CPU_PCTRL_CD            0x0002      /* CD bus संकेत                    */
#घोषणा CPU_PCTRL_IO            0x0001      /* IO bus संकेत                    */

/* SCSI processor dअगरferential pins रेजिस्टर */
#घोषणा CPU_PDIFF_SENSE         0x0200      /* Dअगरferential sense               */
#घोषणा CPU_PDIFF_MODE          0x0100      /* Dअगरferential mode                */
#घोषणा CPU_PDIFF_OENAB         0x0080      /* Outमाला_दो enable                   */
#घोषणा CPU_PDIFF_PMASK         0x007c      /* Dअगरferential control pins        */
#घोषणा CPU_PDIFF_TGT           0x0002      /* Target mode enable               */
#घोषणा CPU_PDIFF_INIT          0x0001      /* Initiator mode enable            */

/* RISC processor status रेजिस्टर */
#घोषणा RISC_PSR_FTRUE          0x8000      /* Force true                       */
#घोषणा RISC_PSR_LCD            0x4000      /* Loop counter shows करोne status   */
#घोषणा RISC_PSR_RIRQ           0x2000      /* RISC irq status                  */
#घोषणा RISC_PSR_TOFLOW         0x1000      /* Timer overflow (rollover)        */
#घोषणा RISC_PSR_AOFLOW         0x0800      /* Arithmetic overflow              */
#घोषणा RISC_PSR_AMSB           0x0400      /* Arithmetic big endian            */
#घोषणा RISC_PSR_ACARRY         0x0200      /* Arithmetic carry                 */
#घोषणा RISC_PSR_AZERO          0x0100      /* Arithmetic zero                  */
#घोषणा RISC_PSR_ULTRA          0x0020      /* Ultra mode                       */
#घोषणा RISC_PSR_सूचीQ           0x0010      /* DVMA पूर्णांकerrupt                   */
#घोषणा RISC_PSR_SIRQ           0x0008      /* SCSI processor पूर्णांकerrupt         */
#घोषणा RISC_PSR_HIRQ           0x0004      /* Host पूर्णांकerrupt                   */
#घोषणा RISC_PSR_IPEND          0x0002      /* Interrupt pending                */
#घोषणा RISC_PSR_FFALSE         0x0001      /* Force false                      */

/* RISC processor memory timing रेजिस्टर */
#घोषणा RISC_MTREG_P1DFLT       0x1200      /* Default पढ़ो/ग_लिखो timing, pg1   */
#घोषणा RISC_MTREG_P0DFLT       0x0012      /* Default पढ़ो/ग_लिखो timing, pg0   */
#घोषणा RISC_MTREG_P1ULTRA      0x2300      /* Ultra-mode rw timing, pg1        */
#घोषणा RISC_MTREG_P0ULTRA      0x0023      /* Ultra-mode rw timing, pg0        */

/* Host command/ctrl रेजिस्टर */
#घोषणा HCCTRL_NOP              0x0000      /* CMD: No operation                */
#घोषणा HCCTRL_RESET            0x1000      /* CMD: Reset RISC cpu              */
#घोषणा HCCTRL_PAUSE            0x2000      /* CMD: Pause RISC cpu              */
#घोषणा HCCTRL_REL              0x3000      /* CMD: Release छोड़ोd RISC cpu     */
#घोषणा HCCTRL_STEP             0x4000      /* CMD: Single step RISC cpu        */
#घोषणा HCCTRL_SHIRQ            0x5000      /* CMD: Set host irq                */
#घोषणा HCCTRL_CHIRQ            0x6000      /* CMD: Clear host irq              */
#घोषणा HCCTRL_CRIRQ            0x7000      /* CMD: Clear RISC cpu irq          */
#घोषणा HCCTRL_BKPT             0x8000      /* CMD: Breakpoपूर्णांक enables change   */
#घोषणा HCCTRL_TMODE            0xf000      /* CMD: Enable test mode            */
#घोषणा HCCTRL_HIRQ             0x0080      /* Host IRQ pending                 */
#घोषणा HCCTRL_RRIP             0x0040      /* RISC cpu reset in happening now  */
#घोषणा HCCTRL_RPAUSED          0x0020      /* RISC cpu is छोड़ोd now           */
#घोषणा HCCTRL_EBENAB           0x0010      /* External अवरोधpoपूर्णांक enable       */
#घोषणा HCCTRL_B1ENAB           0x0008      /* Breakpoपूर्णांक 1 enable              */
#घोषणा HCCTRL_B0ENAB           0x0004      /* Breakpoपूर्णांक 0 enable              */

/* For our पूर्णांकerrupt engine. */
#घोषणा क्रम_each_qlogicpti(qp) \
        क्रम((qp) = qptichain; (qp); (qp) = (qp)->next)

#पूर्ण_अगर /* !(_QLOGICPTI_H) */
