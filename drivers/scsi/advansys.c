<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * advansys.c - Linux Host Driver क्रम AdvanSys SCSI Adapters
 *
 * Copyright (c) 1995-2000 Advanced System Products, Inc.
 * Copyright (c) 2000-2001 ConnectCom Solutions, Inc.
 * Copyright (c) 2007 Matthew Wilcox <matthew@wil.cx>
 * Copyright (c) 2014 Hannes Reinecke <hare@suse.de>
 * All Rights Reserved.
 */

/*
 * As of March 8, 2000 Advanced System Products, Inc. (AdvanSys)
 * changed its name to ConnectCom Solutions, Inc.
 * On June 18, 2001 Initio Corp. acquired ConnectCom's SCSI assets
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/isa.h>
#समावेश <linux/eisa.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/dmapool.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>

#घोषणा DRV_NAME "advansys"
#घोषणा ASC_VERSION "3.5"	/* AdvanSys Driver Version */

/* FIXME:
 *
 *  1. Use scsi_transport_spi
 *  2. advansys_info is not safe against multiple simultaneous callers
 *  3. Add module_param to override ISA/VLB ioport array
 */

/* Enable driver /proc statistics. */
#घोषणा ADVANSYS_STATS

/* Enable driver tracing. */
#अघोषित ADVANSYS_DEBUG

प्रकार अचिन्हित अक्षर uअक्षर;

#घोषणा isodd_word(val)   ((((uपूर्णांक)val) & (uपूर्णांक)0x0001) != 0)

#घोषणा PCI_VENDOR_ID_ASP		0x10cd
#घोषणा PCI_DEVICE_ID_ASP_1200A		0x1100
#घोषणा PCI_DEVICE_ID_ASP_ABP940	0x1200
#घोषणा PCI_DEVICE_ID_ASP_ABP940U	0x1300
#घोषणा PCI_DEVICE_ID_ASP_ABP940UW	0x2300
#घोषणा PCI_DEVICE_ID_38C0800_REV1	0x2500
#घोषणा PCI_DEVICE_ID_38C1600_REV1	0x2700

#घोषणा PortAddr                 अचिन्हित पूर्णांक	/* port address size  */
#घोषणा inp(port)                inb(port)
#घोषणा outp(port, byte)         outb((byte), (port))

#घोषणा inpw(port)               inw(port)
#घोषणा outpw(port, word)        outw((word), (port))

#घोषणा ASC_MAX_SG_QUEUE    7
#घोषणा ASC_MAX_SG_LIST     255

#घोषणा ASC_CS_TYPE  अचिन्हित लघु

#घोषणा ASC_IS_EISA         (0x0002)
#घोषणा ASC_IS_PCI          (0x0004)
#घोषणा ASC_IS_PCI_ULTRA    (0x0104)
#घोषणा ASC_IS_PCMCIA       (0x0008)
#घोषणा ASC_IS_MCA          (0x0020)
#घोषणा ASC_IS_VL           (0x0040)
#घोषणा ASC_IS_WIDESCSI_16  (0x0100)
#घोषणा ASC_IS_WIDESCSI_32  (0x0200)
#घोषणा ASC_IS_BIG_ENDIAN   (0x8000)

#घोषणा ASC_CHIP_MIN_VER_VL      (0x01)
#घोषणा ASC_CHIP_MAX_VER_VL      (0x07)
#घोषणा ASC_CHIP_MIN_VER_PCI     (0x09)
#घोषणा ASC_CHIP_MAX_VER_PCI     (0x0F)
#घोषणा ASC_CHIP_VER_PCI_BIT     (0x08)
#घोषणा ASC_CHIP_VER_ASYN_BUG    (0x21)
#घोषणा ASC_CHIP_VER_PCI             0x08
#घोषणा ASC_CHIP_VER_PCI_ULTRA_3150  (ASC_CHIP_VER_PCI | 0x02)
#घोषणा ASC_CHIP_VER_PCI_ULTRA_3050  (ASC_CHIP_VER_PCI | 0x03)
#घोषणा ASC_CHIP_MIN_VER_EISA (0x41)
#घोषणा ASC_CHIP_MAX_VER_EISA (0x47)
#घोषणा ASC_CHIP_VER_EISA_BIT (0x40)
#घोषणा ASC_CHIP_LATEST_VER_EISA   ((ASC_CHIP_MIN_VER_EISA - 1) + 3)
#घोषणा ASC_MAX_VL_DMA_COUNT    (0x07FFFFFFL)
#घोषणा ASC_MAX_PCI_DMA_COUNT   (0xFFFFFFFFL)

#घोषणा ASC_SCSI_ID_BITS  3
#घोषणा ASC_SCSI_TIX_TYPE     uअक्षर
#घोषणा ASC_ALL_DEVICE_BIT_SET  0xFF
#घोषणा ASC_SCSI_BIT_ID_TYPE  uअक्षर
#घोषणा ASC_MAX_TID       7
#घोषणा ASC_MAX_LUN       7
#घोषणा ASC_SCSI_WIDTH_BIT_SET  0xFF
#घोषणा ASC_MAX_SENSE_LEN   32
#घोषणा ASC_MIN_SENSE_LEN   14
#घोषणा ASC_SCSI_RESET_HOLD_TIME_US  60

/*
 * Narrow boards only support 12-byte commands, जबतक wide boards
 * extend to 16-byte commands.
 */
#घोषणा ASC_MAX_CDB_LEN     12
#घोषणा ADV_MAX_CDB_LEN     16

#घोषणा MS_SDTR_LEN    0x03
#घोषणा MS_WDTR_LEN    0x02

#घोषणा ASC_SG_LIST_PER_Q   7
#घोषणा QS_FREE        0x00
#घोषणा QS_READY       0x01
#घोषणा QS_DISC1       0x02
#घोषणा QS_DISC2       0x04
#घोषणा QS_BUSY        0x08
#घोषणा QS_ABORTED     0x40
#घोषणा QS_DONE        0x80
#घोषणा QC_NO_CALLBACK   0x01
#घोषणा QC_SG_SWAP_QUEUE 0x02
#घोषणा QC_SG_HEAD       0x04
#घोषणा QC_DATA_IN       0x08
#घोषणा QC_DATA_OUT      0x10
#घोषणा QC_URGENT        0x20
#घोषणा QC_MSG_OUT       0x40
#घोषणा QC_REQ_SENSE     0x80
#घोषणा QCSG_SG_XFER_LIST  0x02
#घोषणा QCSG_SG_XFER_MORE  0x04
#घोषणा QCSG_SG_XFER_END   0x08
#घोषणा QD_IN_PROGRESS       0x00
#घोषणा QD_NO_ERROR          0x01
#घोषणा QD_ABORTED_BY_HOST   0x02
#घोषणा QD_WITH_ERROR        0x04
#घोषणा QD_INVALID_REQUEST   0x80
#घोषणा QD_INVALID_HOST_NUM  0x81
#घोषणा QD_INVALID_DEVICE    0x82
#घोषणा QD_ERR_INTERNAL      0xFF
#घोषणा QHSTA_NO_ERROR               0x00
#घोषणा QHSTA_M_SEL_TIMEOUT          0x11
#घोषणा QHSTA_M_DATA_OVER_RUN        0x12
#घोषणा QHSTA_M_DATA_UNDER_RUN       0x12
#घोषणा QHSTA_M_UNEXPECTED_BUS_FREE  0x13
#घोषणा QHSTA_M_BAD_BUS_PHASE_SEQ    0x14
#घोषणा QHSTA_D_QDONE_SG_LIST_CORRUPTED 0x21
#घोषणा QHSTA_D_ASC_DVC_ERROR_CODE_SET  0x22
#घोषणा QHSTA_D_HOST_ABORT_FAILED       0x23
#घोषणा QHSTA_D_EXE_SCSI_Q_FAILED       0x24
#घोषणा QHSTA_D_EXE_SCSI_Q_BUSY_TIMEOUT 0x25
#घोषणा QHSTA_D_ASPI_NO_BUF_POOL        0x26
#घोषणा QHSTA_M_WTM_TIMEOUT         0x41
#घोषणा QHSTA_M_BAD_CMPL_STATUS_IN  0x42
#घोषणा QHSTA_M_NO_AUTO_REQ_SENSE   0x43
#घोषणा QHSTA_M_AUTO_REQ_SENSE_FAIL 0x44
#घोषणा QHSTA_M_TARGET_STATUS_BUSY  0x45
#घोषणा QHSTA_M_BAD_TAG_CODE        0x46
#घोषणा QHSTA_M_BAD_QUEUE_FULL_OR_BUSY  0x47
#घोषणा QHSTA_M_HUNG_REQ_SCSI_BUS_RESET 0x48
#घोषणा QHSTA_D_LRAM_CMP_ERROR        0x81
#घोषणा QHSTA_M_MICRO_CODE_ERROR_HALT 0xA1
#घोषणा ASC_FLAG_SCSIQ_REQ        0x01
#घोषणा ASC_FLAG_BIOS_SCSIQ_REQ   0x02
#घोषणा ASC_FLAG_BIOS_ASYNC_IO    0x04
#घोषणा ASC_FLAG_SRB_LINEAR_ADDR  0x08
#घोषणा ASC_FLAG_WIN16            0x10
#घोषणा ASC_FLAG_WIN32            0x20
#घोषणा ASC_FLAG_DOS_VM_CALLBACK  0x80
#घोषणा ASC_TAG_FLAG_EXTRA_BYTES               0x10
#घोषणा ASC_TAG_FLAG_DISABLE_DISCONNECT        0x04
#घोषणा ASC_TAG_FLAG_DISABLE_ASYN_USE_SYN_FIX  0x08
#घोषणा ASC_TAG_FLAG_DISABLE_CHK_COND_INT_HOST 0x40
#घोषणा ASC_SCSIQ_CPY_BEG              4
#घोषणा ASC_SCSIQ_SGHD_CPY_BEG         2
#घोषणा ASC_SCSIQ_B_FWD                0
#घोषणा ASC_SCSIQ_B_BWD                1
#घोषणा ASC_SCSIQ_B_STATUS             2
#घोषणा ASC_SCSIQ_B_QNO                3
#घोषणा ASC_SCSIQ_B_CNTL               4
#घोषणा ASC_SCSIQ_B_SG_QUEUE_CNT       5
#घोषणा ASC_SCSIQ_D_DATA_ADDR          8
#घोषणा ASC_SCSIQ_D_DATA_CNT          12
#घोषणा ASC_SCSIQ_B_SENSE_LEN         20
#घोषणा ASC_SCSIQ_DONE_INFO_BEG       22
#घोषणा ASC_SCSIQ_D_SRBPTR            22
#घोषणा ASC_SCSIQ_B_TARGET_IX         26
#घोषणा ASC_SCSIQ_B_CDB_LEN           28
#घोषणा ASC_SCSIQ_B_TAG_CODE          29
#घोषणा ASC_SCSIQ_W_VM_ID             30
#घोषणा ASC_SCSIQ_DONE_STATUS         32
#घोषणा ASC_SCSIQ_HOST_STATUS         33
#घोषणा ASC_SCSIQ_SCSI_STATUS         34
#घोषणा ASC_SCSIQ_CDB_BEG             36
#घोषणा ASC_SCSIQ_DW_REMAIN_XFER_ADDR 56
#घोषणा ASC_SCSIQ_DW_REMAIN_XFER_CNT  60
#घोषणा ASC_SCSIQ_B_FIRST_SG_WK_QP    48
#घोषणा ASC_SCSIQ_B_SG_WK_QP          49
#घोषणा ASC_SCSIQ_B_SG_WK_IX          50
#घोषणा ASC_SCSIQ_W_ALT_DC1           52
#घोषणा ASC_SCSIQ_B_LIST_CNT          6
#घोषणा ASC_SCSIQ_B_CUR_LIST_CNT      7
#घोषणा ASC_SGQ_B_SG_CNTL             4
#घोषणा ASC_SGQ_B_SG_HEAD_QP          5
#घोषणा ASC_SGQ_B_SG_LIST_CNT         6
#घोषणा ASC_SGQ_B_SG_CUR_LIST_CNT     7
#घोषणा ASC_SGQ_LIST_BEG              8
#घोषणा ASC_DEF_SCSI1_QNG    4
#घोषणा ASC_MAX_SCSI1_QNG    4
#घोषणा ASC_DEF_SCSI2_QNG    16
#घोषणा ASC_MAX_SCSI2_QNG    32
#घोषणा ASC_TAG_CODE_MASK    0x23
#घोषणा ASC_STOP_REQ_RISC_STOP      0x01
#घोषणा ASC_STOP_ACK_RISC_STOP      0x03
#घोषणा ASC_STOP_CLEAN_UP_BUSY_Q    0x10
#घोषणा ASC_STOP_CLEAN_UP_DISC_Q    0x20
#घोषणा ASC_STOP_HOST_REQ_RISC_HALT 0x40
#घोषणा ASC_TIDLUN_TO_IX(tid, lun)  (ASC_SCSI_TIX_TYPE)((tid) + ((lun)<<ASC_SCSI_ID_BITS))
#घोषणा ASC_TID_TO_TARGET_ID(tid)   (ASC_SCSI_BIT_ID_TYPE)(0x01 << (tid))
#घोषणा ASC_TIX_TO_TARGET_ID(tix)   (0x01 << ((tix) & ASC_MAX_TID))
#घोषणा ASC_TIX_TO_TID(tix)         ((tix) & ASC_MAX_TID)
#घोषणा ASC_TID_TO_TIX(tid)         ((tid) & ASC_MAX_TID)
#घोषणा ASC_TIX_TO_LUN(tix)         (((tix) >> ASC_SCSI_ID_BITS) & ASC_MAX_LUN)
#घोषणा ASC_QNO_TO_QADDR(q_no)      ((ASC_QADR_BEG)+((पूर्णांक)(q_no) << 6))

प्रकार काष्ठा asc_scsiq_1 अणु
	uअक्षर status;
	uअक्षर q_no;
	uअक्षर cntl;
	uअक्षर sg_queue_cnt;
	uअक्षर target_id;
	uअक्षर target_lun;
	__le32 data_addr;
	__le32 data_cnt;
	__le32 sense_addr;
	uअक्षर sense_len;
	uअक्षर extra_bytes;
पूर्ण ASC_SCSIQ_1;

प्रकार काष्ठा asc_scsiq_2 अणु
	u32 srb_tag;
	uअक्षर target_ix;
	uअक्षर flag;
	uअक्षर cdb_len;
	uअक्षर tag_code;
	uलघु vm_id;
पूर्ण ASC_SCSIQ_2;

प्रकार काष्ठा asc_scsiq_3 अणु
	uअक्षर करोne_stat;
	uअक्षर host_stat;
	uअक्षर scsi_stat;
	uअक्षर scsi_msg;
पूर्ण ASC_SCSIQ_3;

प्रकार काष्ठा asc_scsiq_4 अणु
	uअक्षर cdb[ASC_MAX_CDB_LEN];
	uअक्षर y_first_sg_list_qp;
	uअक्षर y_working_sg_qp;
	uअक्षर y_working_sg_ix;
	uअक्षर y_res;
	uलघु x_req_count;
	uलघु x_reconnect_rtn;
	__le32 x_saved_data_addr;
	__le32 x_saved_data_cnt;
पूर्ण ASC_SCSIQ_4;

प्रकार काष्ठा asc_q_करोne_info अणु
	ASC_SCSIQ_2 d2;
	ASC_SCSIQ_3 d3;
	uअक्षर q_status;
	uअक्षर q_no;
	uअक्षर cntl;
	uअक्षर sense_len;
	uअक्षर extra_bytes;
	uअक्षर res;
	u32 reमुख्य_bytes;
पूर्ण ASC_QDONE_INFO;

प्रकार काष्ठा asc_sg_list अणु
	__le32 addr;
	__le32 bytes;
पूर्ण ASC_SG_LIST;

प्रकार काष्ठा asc_sg_head अणु
	uलघु entry_cnt;
	uलघु queue_cnt;
	uलघु entry_to_copy;
	uलघु res;
	ASC_SG_LIST sg_list[];
पूर्ण ASC_SG_HEAD;

प्रकार काष्ठा asc_scsi_q अणु
	ASC_SCSIQ_1 q1;
	ASC_SCSIQ_2 q2;
	uअक्षर *cdbptr;
	ASC_SG_HEAD *sg_head;
	uलघु reमुख्य_sg_entry_cnt;
	uलघु next_sg_index;
पूर्ण ASC_SCSI_Q;

प्रकार काष्ठा asc_scsi_bios_req_q अणु
	ASC_SCSIQ_1 r1;
	ASC_SCSIQ_2 r2;
	uअक्षर *cdbptr;
	ASC_SG_HEAD *sg_head;
	uअक्षर *sense_ptr;
	ASC_SCSIQ_3 r3;
	uअक्षर cdb[ASC_MAX_CDB_LEN];
	uअक्षर sense[ASC_MIN_SENSE_LEN];
पूर्ण ASC_SCSI_BIOS_REQ_Q;

प्रकार काष्ठा asc_risc_q अणु
	uअक्षर fwd;
	uअक्षर bwd;
	ASC_SCSIQ_1 i1;
	ASC_SCSIQ_2 i2;
	ASC_SCSIQ_3 i3;
	ASC_SCSIQ_4 i4;
पूर्ण ASC_RISC_Q;

प्रकार काष्ठा asc_sg_list_q अणु
	uअक्षर seq_no;
	uअक्षर q_no;
	uअक्षर cntl;
	uअक्षर sg_head_qp;
	uअक्षर sg_list_cnt;
	uअक्षर sg_cur_list_cnt;
पूर्ण ASC_SG_LIST_Q;

प्रकार काष्ठा asc_risc_sg_list_q अणु
	uअक्षर fwd;
	uअक्षर bwd;
	ASC_SG_LIST_Q sg;
	ASC_SG_LIST sg_list[7];
पूर्ण ASC_RISC_SG_LIST_Q;

#घोषणा ASCQ_ERR_Q_STATUS             0x0D
#घोषणा ASCQ_ERR_CUR_QNG              0x17
#घोषणा ASCQ_ERR_SG_Q_LINKS           0x18
#घोषणा ASCQ_ERR_ISR_RE_ENTRY         0x1A
#घोषणा ASCQ_ERR_CRITICAL_RE_ENTRY    0x1B
#घोषणा ASCQ_ERR_ISR_ON_CRITICAL      0x1C

/*
 * Warning code values are set in ASC_DVC_VAR  'warn_code'.
 */
#घोषणा ASC_WARN_NO_ERROR             0x0000
#घोषणा ASC_WARN_IO_PORT_ROTATE       0x0001
#घोषणा ASC_WARN_EEPROM_CHKSUM        0x0002
#घोषणा ASC_WARN_IRQ_MODIFIED         0x0004
#घोषणा ASC_WARN_AUTO_CONFIG          0x0008
#घोषणा ASC_WARN_CMD_QNG_CONFLICT     0x0010
#घोषणा ASC_WARN_EEPROM_RECOVER       0x0020
#घोषणा ASC_WARN_CFG_MSW_RECOVER      0x0040

/*
 * Error code values are set in अणुASC/ADVपूर्ण_DVC_VAR  'err_code'.
 */
#घोषणा ASC_IERR_NO_CARRIER		0x0001	/* No more carrier memory */
#घोषणा ASC_IERR_MCODE_CHKSUM		0x0002	/* micro code check sum error */
#घोषणा ASC_IERR_SET_PC_ADDR		0x0004
#घोषणा ASC_IERR_START_STOP_CHIP	0x0008	/* start/stop chip failed */
#घोषणा ASC_IERR_ILLEGAL_CONNECTION	0x0010	/* Illegal cable connection */
#घोषणा ASC_IERR_SINGLE_END_DEVICE	0x0020	/* SE device on DIFF bus */
#घोषणा ASC_IERR_REVERSED_CABLE		0x0040	/* Narrow flat cable reversed */
#घोषणा ASC_IERR_SET_SCSI_ID		0x0080	/* set SCSI ID failed */
#घोषणा ASC_IERR_HVD_DEVICE		0x0100	/* HVD device on LVD port */
#घोषणा ASC_IERR_BAD_SIGNATURE		0x0200	/* signature not found */
#घोषणा ASC_IERR_NO_BUS_TYPE		0x0400
#घोषणा ASC_IERR_BIST_PRE_TEST		0x0800	/* BIST pre-test error */
#घोषणा ASC_IERR_BIST_RAM_TEST		0x1000	/* BIST RAM test error */
#घोषणा ASC_IERR_BAD_CHIPTYPE		0x2000	/* Invalid chip_type setting */

#घोषणा ASC_DEF_MAX_TOTAL_QNG   (0xF0)
#घोषणा ASC_MIN_TAG_Q_PER_DVC   (0x04)
#घोषणा ASC_MIN_FREE_Q        (0x02)
#घोषणा ASC_MIN_TOTAL_QNG     ((ASC_MAX_SG_QUEUE)+(ASC_MIN_FREE_Q))
#घोषणा ASC_MAX_TOTAL_QNG 240
#घोषणा ASC_MAX_PCI_ULTRA_INRAM_TOTAL_QNG 16
#घोषणा ASC_MAX_PCI_ULTRA_INRAM_TAG_QNG   8
#घोषणा ASC_MAX_PCI_INRAM_TOTAL_QNG  20
#घोषणा ASC_MAX_INRAM_TAG_QNG   16
#घोषणा ASC_IOADR_GAP   0x10
#घोषणा ASC_SYN_MAX_OFFSET         0x0F
#घोषणा ASC_DEF_SDTR_OFFSET        0x0F
#घोषणा ASC_SDTR_ULTRA_PCI_10MB_INDEX  0x02
#घोषणा ASYN_SDTR_DATA_FIX_PCI_REV_AB 0x41

/* The narrow chip only supports a limited selection of transfer rates.
 * These are encoded in the range 0..7 or 0..15 depending whether the chip
 * is Ultra-capable or not.  These tables let us convert from one to the other.
 */
अटल स्थिर अचिन्हित अक्षर asc_syn_xfer_period[8] = अणु
	25, 30, 35, 40, 50, 60, 70, 85
पूर्ण;

अटल स्थिर अचिन्हित अक्षर asc_syn_ultra_xfer_period[16] = अणु
	12, 19, 25, 32, 38, 44, 50, 57, 63, 69, 75, 82, 88, 94, 100, 107
पूर्ण;

प्रकार काष्ठा ext_msg अणु
	uअक्षर msg_type;
	uअक्षर msg_len;
	uअक्षर msg_req;
	जोड़ अणु
		काष्ठा अणु
			uअक्षर sdtr_xfer_period;
			uअक्षर sdtr_req_ack_offset;
		पूर्ण sdtr;
		काष्ठा अणु
			uअक्षर wdtr_width;
		पूर्ण wdtr;
		काष्ठा अणु
			uअक्षर mdp_b3;
			uअक्षर mdp_b2;
			uअक्षर mdp_b1;
			uअक्षर mdp_b0;
		पूर्ण mdp;
	पूर्ण u_ext_msg;
	uअक्षर res;
पूर्ण EXT_MSG;

#घोषणा xfer_period     u_ext_msg.sdtr.sdtr_xfer_period
#घोषणा req_ack_offset  u_ext_msg.sdtr.sdtr_req_ack_offset
#घोषणा wdtr_width      u_ext_msg.wdtr.wdtr_width
#घोषणा mdp_b3          u_ext_msg.mdp_b3
#घोषणा mdp_b2          u_ext_msg.mdp_b2
#घोषणा mdp_b1          u_ext_msg.mdp_b1
#घोषणा mdp_b0          u_ext_msg.mdp_b0

प्रकार काष्ठा asc_dvc_cfg अणु
	ASC_SCSI_BIT_ID_TYPE can_tagged_qng;
	ASC_SCSI_BIT_ID_TYPE cmd_qng_enabled;
	ASC_SCSI_BIT_ID_TYPE disc_enable;
	ASC_SCSI_BIT_ID_TYPE sdtr_enable;
	uअक्षर chip_scsi_id;
	uअक्षर chip_version;
	uलघु mcode_date;
	uलघु mcode_version;
	uअक्षर max_tag_qng[ASC_MAX_TID + 1];
	uअक्षर sdtr_period_offset[ASC_MAX_TID + 1];
	uअक्षर adapter_info[6];
पूर्ण ASC_DVC_CFG;

#घोषणा ASC_DEF_DVC_CNTL       0xFFFF
#घोषणा ASC_DEF_CHIP_SCSI_ID   7
#घोषणा ASC_DEF_ISA_DMA_SPEED  4
#घोषणा ASC_INIT_STATE_BEG_GET_CFG   0x0001
#घोषणा ASC_INIT_STATE_END_GET_CFG   0x0002
#घोषणा ASC_INIT_STATE_BEG_SET_CFG   0x0004
#घोषणा ASC_INIT_STATE_END_SET_CFG   0x0008
#घोषणा ASC_INIT_STATE_BEG_LOAD_MC   0x0010
#घोषणा ASC_INIT_STATE_END_LOAD_MC   0x0020
#घोषणा ASC_INIT_STATE_BEG_INQUIRY   0x0040
#घोषणा ASC_INIT_STATE_END_INQUIRY   0x0080
#घोषणा ASC_INIT_RESET_SCSI_DONE     0x0100
#घोषणा ASC_INIT_STATE_WITHOUT_EEP   0x8000
#घोषणा ASC_BUG_FIX_IF_NOT_DWB       0x0001
#घोषणा ASC_BUG_FIX_ASYN_USE_SYN     0x0002
#घोषणा ASC_MIN_TAGGED_CMD  7
#घोषणा ASC_MAX_SCSI_RESET_WAIT      30
#घोषणा ASC_OVERRUN_BSIZE		64

काष्ठा asc_dvc_var;		/* Forward Declaration. */

प्रकार काष्ठा asc_dvc_var अणु
	PortAddr iop_base;
	uलघु err_code;
	uलघु dvc_cntl;
	uलघु bug_fix_cntl;
	uलघु bus_type;
	ASC_SCSI_BIT_ID_TYPE init_sdtr;
	ASC_SCSI_BIT_ID_TYPE sdtr_करोne;
	ASC_SCSI_BIT_ID_TYPE use_tagged_qng;
	ASC_SCSI_BIT_ID_TYPE unit_not_पढ़ोy;
	ASC_SCSI_BIT_ID_TYPE queue_full_or_busy;
	ASC_SCSI_BIT_ID_TYPE start_motor;
	uअक्षर *overrun_buf;
	dma_addr_t overrun_dma;
	uअक्षर scsi_reset_रुको;
	uअक्षर chip_no;
	bool is_in_पूर्णांक;
	uअक्षर max_total_qng;
	uअक्षर cur_total_qng;
	uअक्षर in_critical_cnt;
	uअक्षर last_q_लघुage;
	uलघु init_state;
	uअक्षर cur_dvc_qng[ASC_MAX_TID + 1];
	uअक्षर max_dvc_qng[ASC_MAX_TID + 1];
	ASC_SCSI_Q *scsiq_busy_head[ASC_MAX_TID + 1];
	ASC_SCSI_Q *scsiq_busy_tail[ASC_MAX_TID + 1];
	स्थिर uअक्षर *sdtr_period_tbl;
	ASC_DVC_CFG *cfg;
	ASC_SCSI_BIT_ID_TYPE pci_fix_asyn_xfer_always;
	अक्षर reकरो_scam;
	uलघु res2;
	uअक्षर करोs_पूर्णांक13_table[ASC_MAX_TID + 1];
	अचिन्हित पूर्णांक max_dma_count;
	ASC_SCSI_BIT_ID_TYPE no_scam;
	ASC_SCSI_BIT_ID_TYPE pci_fix_asyn_xfer;
	uअक्षर min_sdtr_index;
	uअक्षर max_sdtr_index;
	काष्ठा asc_board *drv_ptr;
	अचिन्हित पूर्णांक uc_अवरोध;
पूर्ण ASC_DVC_VAR;

प्रकार काष्ठा asc_dvc_inq_info अणु
	uअक्षर type[ASC_MAX_TID + 1][ASC_MAX_LUN + 1];
पूर्ण ASC_DVC_INQ_INFO;

प्रकार काष्ठा asc_cap_info अणु
	u32 lba;
	u32 blk_size;
पूर्ण ASC_CAP_INFO;

प्रकार काष्ठा asc_cap_info_array अणु
	ASC_CAP_INFO cap_info[ASC_MAX_TID + 1][ASC_MAX_LUN + 1];
पूर्ण ASC_CAP_INFO_ARRAY;

#घोषणा ASC_MCNTL_NO_SEL_TIMEOUT  (uलघु)0x0001
#घोषणा ASC_MCNTL_शून्य_TARGET     (uलघु)0x0002
#घोषणा ASC_CNTL_INITIATOR         (uलघु)0x0001
#घोषणा ASC_CNTL_BIOS_GT_1GB       (uलघु)0x0002
#घोषणा ASC_CNTL_BIOS_GT_2_DISK    (uलघु)0x0004
#घोषणा ASC_CNTL_BIOS_REMOVABLE    (uलघु)0x0008
#घोषणा ASC_CNTL_NO_SCAM           (uलघु)0x0010
#घोषणा ASC_CNTL_INT_MULTI_Q       (uलघु)0x0080
#घोषणा ASC_CNTL_NO_LUN_SUPPORT    (uलघु)0x0040
#घोषणा ASC_CNTL_NO_VERIFY_COPY    (uलघु)0x0100
#घोषणा ASC_CNTL_RESET_SCSI        (uलघु)0x0200
#घोषणा ASC_CNTL_INIT_INQUIRY      (uलघु)0x0400
#घोषणा ASC_CNTL_INIT_VERBOSE      (uलघु)0x0800
#घोषणा ASC_CNTL_SCSI_PARITY       (uलघु)0x1000
#घोषणा ASC_CNTL_BURST_MODE        (uलघु)0x2000
#घोषणा ASC_CNTL_SDTR_ENABLE_ULTRA (uलघु)0x4000
#घोषणा ASC_EEP_DVC_CFG_BEG_VL    2
#घोषणा ASC_EEP_MAX_DVC_ADDR_VL   15
#घोषणा ASC_EEP_DVC_CFG_BEG      32
#घोषणा ASC_EEP_MAX_DVC_ADDR     45
#घोषणा ASC_EEP_MAX_RETRY        20

/*
 * These macros keep the chip SCSI id  bitfields in board order. C bitfields
 * aren't portable between big and little-endian platक्रमms so they are not used.
 */

#घोषणा ASC_EEP_GET_CHIP_ID(cfg)    ((cfg)->id_speed & 0x0f)
#घोषणा ASC_EEP_GET_DMA_SPD(cfg)    (((cfg)->id_speed & 0xf0) >> 4)
#घोषणा ASC_EEP_SET_CHIP_ID(cfg, sid) \
   ((cfg)->id_speed = ((cfg)->id_speed & 0xf0) | ((sid) & ASC_MAX_TID))
#घोषणा ASC_EEP_SET_DMA_SPD(cfg, spd) \
   ((cfg)->id_speed = ((cfg)->id_speed & 0x0f) | ((spd) & 0x0f) << 4)

प्रकार काष्ठा asceep_config अणु
	uलघु cfg_lsw;
	uलघु cfg_msw;
	uअक्षर init_sdtr;
	uअक्षर disc_enable;
	uअक्षर use_cmd_qng;
	uअक्षर start_motor;
	uअक्षर max_total_qng;
	uअक्षर max_tag_qng;
	uअक्षर bios_scan;
	uअक्षर घातer_up_रुको;
	uअक्षर no_scam;
	uअक्षर id_speed;		/* low order 4 bits is chip scsi id */
	/* high order 4 bits is isa dma speed */
	uअक्षर करोs_पूर्णांक13_table[ASC_MAX_TID + 1];
	uअक्षर adapter_info[6];
	uलघु cntl;
	uलघु chksum;
पूर्ण ASCEEP_CONFIG;

#घोषणा ASC_EEP_CMD_READ          0x80
#घोषणा ASC_EEP_CMD_WRITE         0x40
#घोषणा ASC_EEP_CMD_WRITE_ABLE    0x30
#घोषणा ASC_EEP_CMD_WRITE_DISABLE 0x00
#घोषणा ASCV_MSGOUT_BEG         0x0000
#घोषणा ASCV_MSGOUT_SDTR_PERIOD (ASCV_MSGOUT_BEG+3)
#घोषणा ASCV_MSGOUT_SDTR_OFFSET (ASCV_MSGOUT_BEG+4)
#घोषणा ASCV_BREAK_SAVED_CODE   (uलघु)0x0006
#घोषणा ASCV_MSGIN_BEG          (ASCV_MSGOUT_BEG+8)
#घोषणा ASCV_MSGIN_SDTR_PERIOD  (ASCV_MSGIN_BEG+3)
#घोषणा ASCV_MSGIN_SDTR_OFFSET  (ASCV_MSGIN_BEG+4)
#घोषणा ASCV_SDTR_DATA_BEG      (ASCV_MSGIN_BEG+8)
#घोषणा ASCV_SDTR_DONE_BEG      (ASCV_SDTR_DATA_BEG+8)
#घोषणा ASCV_MAX_DVC_QNG_BEG    (uलघु)0x0020
#घोषणा ASCV_BREAK_ADDR           (uलघु)0x0028
#घोषणा ASCV_BREAK_NOTIFY_COUNT   (uलघु)0x002A
#घोषणा ASCV_BREAK_CONTROL        (uलघु)0x002C
#घोषणा ASCV_BREAK_HIT_COUNT      (uलघु)0x002E

#घोषणा ASCV_ASCDVC_ERR_CODE_W  (uलघु)0x0030
#घोषणा ASCV_MCODE_CHKSUM_W   (uलघु)0x0032
#घोषणा ASCV_MCODE_SIZE_W     (uलघु)0x0034
#घोषणा ASCV_STOP_CODE_B      (uलघु)0x0036
#घोषणा ASCV_DVC_ERR_CODE_B   (uलघु)0x0037
#घोषणा ASCV_OVERRUN_PADDR_D  (uलघु)0x0038
#घोषणा ASCV_OVERRUN_BSIZE_D  (uलघु)0x003C
#घोषणा ASCV_HALTCODE_W       (uलघु)0x0040
#घोषणा ASCV_CHKSUM_W         (uलघु)0x0042
#घोषणा ASCV_MC_DATE_W        (uलघु)0x0044
#घोषणा ASCV_MC_VER_W         (uलघु)0x0046
#घोषणा ASCV_NEXTRDY_B        (uलघु)0x0048
#घोषणा ASCV_DONENEXT_B       (uलघु)0x0049
#घोषणा ASCV_USE_TAGGED_QNG_B (uलघु)0x004A
#घोषणा ASCV_SCSIBUSY_B       (uलघु)0x004B
#घोषणा ASCV_Q_DONE_IN_PROGRESS_B  (uलघु)0x004C
#घोषणा ASCV_CURCDB_B         (uलघु)0x004D
#घोषणा ASCV_RCLUN_B          (uलघु)0x004E
#घोषणा ASCV_BUSY_QHEAD_B     (uलघु)0x004F
#घोषणा ASCV_DISC1_QHEAD_B    (uलघु)0x0050
#घोषणा ASCV_DISC_ENABLE_B    (uलघु)0x0052
#घोषणा ASCV_CAN_TAGGED_QNG_B (uलघु)0x0053
#घोषणा ASCV_HOSTSCSI_ID_B    (uलघु)0x0055
#घोषणा ASCV_MCODE_CNTL_B     (uलघु)0x0056
#घोषणा ASCV_शून्य_TARGET_B    (uलघु)0x0057
#घोषणा ASCV_FREE_Q_HEAD_W    (uलघु)0x0058
#घोषणा ASCV_DONE_Q_TAIL_W    (uलघु)0x005A
#घोषणा ASCV_FREE_Q_HEAD_B    (uलघु)(ASCV_FREE_Q_HEAD_W+1)
#घोषणा ASCV_DONE_Q_TAIL_B    (uलघु)(ASCV_DONE_Q_TAIL_W+1)
#घोषणा ASCV_HOST_FLAG_B      (uलघु)0x005D
#घोषणा ASCV_TOTAL_READY_Q_B  (uलघु)0x0064
#घोषणा ASCV_VER_SERIAL_B     (uलघु)0x0065
#घोषणा ASCV_HALTCODE_SAVED_W (uलघु)0x0066
#घोषणा ASCV_WTM_FLAG_B       (uलघु)0x0068
#घोषणा ASCV_RISC_FLAG_B      (uलघु)0x006A
#घोषणा ASCV_REQ_SG_LIST_QP   (uलघु)0x006B
#घोषणा ASC_HOST_FLAG_IN_ISR        0x01
#घोषणा ASC_HOST_FLAG_ACK_INT       0x02
#घोषणा ASC_RISC_FLAG_GEN_INT      0x01
#घोषणा ASC_RISC_FLAG_REQ_SG_LIST  0x02
#घोषणा IOP_CTRL         (0x0F)
#घोषणा IOP_STATUS       (0x0E)
#घोषणा IOP_INT_ACK      IOP_STATUS
#घोषणा IOP_REG_IFC      (0x0D)
#घोषणा IOP_SYN_OFFSET    (0x0B)
#घोषणा IOP_EXTRA_CONTROL (0x0D)
#घोषणा IOP_REG_PC        (0x0C)
#घोषणा IOP_RAM_ADDR      (0x0A)
#घोषणा IOP_RAM_DATA      (0x08)
#घोषणा IOP_EEP_DATA      (0x06)
#घोषणा IOP_EEP_CMD       (0x07)
#घोषणा IOP_VERSION       (0x03)
#घोषणा IOP_CONFIG_HIGH   (0x04)
#घोषणा IOP_CONFIG_LOW    (0x02)
#घोषणा IOP_SIG_BYTE      (0x01)
#घोषणा IOP_SIG_WORD      (0x00)
#घोषणा IOP_REG_DC1      (0x0E)
#घोषणा IOP_REG_DC0      (0x0C)
#घोषणा IOP_REG_SB       (0x0B)
#घोषणा IOP_REG_DA1      (0x0A)
#घोषणा IOP_REG_DA0      (0x08)
#घोषणा IOP_REG_SC       (0x09)
#घोषणा IOP_DMA_SPEED    (0x07)
#घोषणा IOP_REG_FLAG     (0x07)
#घोषणा IOP_FIFO_H       (0x06)
#घोषणा IOP_FIFO_L       (0x04)
#घोषणा IOP_REG_ID       (0x05)
#घोषणा IOP_REG_QP       (0x03)
#घोषणा IOP_REG_IH       (0x02)
#घोषणा IOP_REG_IX       (0x01)
#घोषणा IOP_REG_AX       (0x00)
#घोषणा IFC_REG_LOCK      (0x00)
#घोषणा IFC_REG_UNLOCK    (0x09)
#घोषणा IFC_WR_EN_FILTER  (0x10)
#घोषणा IFC_RD_NO_EEPROM  (0x10)
#घोषणा IFC_SLEW_RATE     (0x20)
#घोषणा IFC_ACT_NEG       (0x40)
#घोषणा IFC_INP_FILTER    (0x80)
#घोषणा IFC_INIT_DEFAULT  (IFC_ACT_NEG | IFC_REG_UNLOCK)
#घोषणा SC_SEL   (uअक्षर)(0x80)
#घोषणा SC_BSY   (uअक्षर)(0x40)
#घोषणा SC_ACK   (uअक्षर)(0x20)
#घोषणा SC_REQ   (uअक्षर)(0x10)
#घोषणा SC_ATN   (uअक्षर)(0x08)
#घोषणा SC_IO    (uअक्षर)(0x04)
#घोषणा SC_CD    (uअक्षर)(0x02)
#घोषणा SC_MSG   (uअक्षर)(0x01)
#घोषणा SEC_SCSI_CTL         (uअक्षर)(0x80)
#घोषणा SEC_ACTIVE_NEGATE    (uअक्षर)(0x40)
#घोषणा SEC_SLEW_RATE        (uअक्षर)(0x20)
#घोषणा SEC_ENABLE_FILTER    (uअक्षर)(0x10)
#घोषणा ASC_HALT_EXTMSG_IN     (uलघु)0x8000
#घोषणा ASC_HALT_CHK_CONDITION (uलघु)0x8100
#घोषणा ASC_HALT_SS_QUEUE_FULL (uलघु)0x8200
#घोषणा ASC_HALT_DISABLE_ASYN_USE_SYN_FIX  (uलघु)0x8300
#घोषणा ASC_HALT_ENABLE_ASYN_USE_SYN_FIX   (uलघु)0x8400
#घोषणा ASC_HALT_SDTR_REJECTED (uलघु)0x4000
#घोषणा ASC_HALT_HOST_COPY_SG_LIST_TO_RISC ( uलघु )0x2000
#घोषणा ASC_MAX_QNO        0xF8
#घोषणा ASC_DATA_SEC_BEG   (uलघु)0x0080
#घोषणा ASC_DATA_SEC_END   (uलघु)0x0080
#घोषणा ASC_CODE_SEC_BEG   (uलघु)0x0080
#घोषणा ASC_CODE_SEC_END   (uलघु)0x0080
#घोषणा ASC_QADR_BEG       (0x4000)
#घोषणा ASC_QADR_USED      (uलघु)(ASC_MAX_QNO * 64)
#घोषणा ASC_QADR_END       (uलघु)0x7FFF
#घोषणा ASC_QLAST_ADR      (uलघु)0x7FC0
#घोषणा ASC_QBLK_SIZE      0x40
#घोषणा ASC_BIOS_DATA_QBEG 0xF8
#घोषणा ASC_MIN_ACTIVE_QNO 0x01
#घोषणा ASC_QLINK_END      0xFF
#घोषणा ASC_EEPROM_WORDS   0x10
#घोषणा ASC_MAX_MGS_LEN    0x10
#घोषणा ASC_BIOS_ADDR_DEF  0xDC00
#घोषणा ASC_BIOS_SIZE      0x3800
#घोषणा ASC_BIOS_RAM_OFF   0x3800
#घोषणा ASC_BIOS_RAM_SIZE  0x800
#घोषणा ASC_BIOS_MIN_ADDR  0xC000
#घोषणा ASC_BIOS_MAX_ADDR  0xEC00
#घोषणा ASC_BIOS_BANK_SIZE 0x0400
#घोषणा ASC_MCODE_START_ADDR  0x0080
#घोषणा ASC_CFG0_HOST_INT_ON    0x0020
#घोषणा ASC_CFG0_BIOS_ON        0x0040
#घोषणा ASC_CFG0_VERA_BURST_ON  0x0080
#घोषणा ASC_CFG0_SCSI_PARITY_ON 0x0800
#घोषणा ASC_CFG1_SCSI_TARGET_ON 0x0080
#घोषणा ASC_CFG1_LRAM_8BITS_ON  0x0800
#घोषणा ASC_CFG_MSW_CLR_MASK    0x3080
#घोषणा CSW_TEST1             (ASC_CS_TYPE)0x8000
#घोषणा CSW_AUTO_CONFIG       (ASC_CS_TYPE)0x4000
#घोषणा CSW_RESERVED1         (ASC_CS_TYPE)0x2000
#घोषणा CSW_IRQ_WRITTEN       (ASC_CS_TYPE)0x1000
#घोषणा CSW_33MHZ_SELECTED    (ASC_CS_TYPE)0x0800
#घोषणा CSW_TEST2             (ASC_CS_TYPE)0x0400
#घोषणा CSW_TEST3             (ASC_CS_TYPE)0x0200
#घोषणा CSW_RESERVED2         (ASC_CS_TYPE)0x0100
#घोषणा CSW_DMA_DONE          (ASC_CS_TYPE)0x0080
#घोषणा CSW_FIFO_RDY          (ASC_CS_TYPE)0x0040
#घोषणा CSW_EEP_READ_DONE     (ASC_CS_TYPE)0x0020
#घोषणा CSW_HALTED            (ASC_CS_TYPE)0x0010
#घोषणा CSW_SCSI_RESET_ACTIVE (ASC_CS_TYPE)0x0008
#घोषणा CSW_PARITY_ERR        (ASC_CS_TYPE)0x0004
#घोषणा CSW_SCSI_RESET_LATCH  (ASC_CS_TYPE)0x0002
#घोषणा CSW_INT_PENDING       (ASC_CS_TYPE)0x0001
#घोषणा CIW_CLR_SCSI_RESET_INT (ASC_CS_TYPE)0x1000
#घोषणा CIW_INT_ACK      (ASC_CS_TYPE)0x0100
#घोषणा CIW_TEST1        (ASC_CS_TYPE)0x0200
#घोषणा CIW_TEST2        (ASC_CS_TYPE)0x0400
#घोषणा CIW_SEL_33MHZ    (ASC_CS_TYPE)0x0800
#घोषणा CIW_IRQ_ACT      (ASC_CS_TYPE)0x1000
#घोषणा CC_CHIP_RESET   (uअक्षर)0x80
#घोषणा CC_SCSI_RESET   (uअक्षर)0x40
#घोषणा CC_HALT         (uअक्षर)0x20
#घोषणा CC_SINGLE_STEP  (uअक्षर)0x10
#घोषणा CC_DMA_ABLE     (uअक्षर)0x08
#घोषणा CC_TEST         (uअक्षर)0x04
#घोषणा CC_BANK_ONE     (uअक्षर)0x02
#घोषणा CC_DIAG         (uअक्षर)0x01
#घोषणा ASC_1000_ID0W      0x04C1
#घोषणा ASC_1000_ID0W_FIX  0x00C1
#घोषणा ASC_1000_ID1B      0x25
#घोषणा ASC_EISA_REV_IOP_MASK  (0x0C83)
#घोषणा ASC_EISA_CFG_IOP_MASK  (0x0C86)
#घोषणा ASC_GET_EISA_SLOT(iop)  (PortAddr)((iop) & 0xF000)
#घोषणा INS_HALTINT        (uलघु)0x6281
#घोषणा INS_HALT           (uलघु)0x6280
#घोषणा INS_SINT           (uलघु)0x6200
#घोषणा INS_RFLAG_WTM      (uलघु)0x7380
#घोषणा ASC_MC_SAVE_CODE_WSIZE  0x500
#घोषणा ASC_MC_SAVE_DATA_WSIZE  0x40

प्रकार काष्ठा asc_mc_saved अणु
	uलघु data[ASC_MC_SAVE_DATA_WSIZE];
	uलघु code[ASC_MC_SAVE_CODE_WSIZE];
पूर्ण ASC_MC_SAVED;

#घोषणा AscGetQDoneInProgress(port)         AscReadLramByte((port), ASCV_Q_DONE_IN_PROGRESS_B)
#घोषणा AscPutQDoneInProgress(port, val)    AscWriteLramByte((port), ASCV_Q_DONE_IN_PROGRESS_B, val)
#घोषणा AscGetVarFreeQHead(port)            AscReadLramWord((port), ASCV_FREE_Q_HEAD_W)
#घोषणा AscGetVarDoneQTail(port)            AscReadLramWord((port), ASCV_DONE_Q_TAIL_W)
#घोषणा AscPutVarFreeQHead(port, val)       AscWriteLramWord((port), ASCV_FREE_Q_HEAD_W, val)
#घोषणा AscPutVarDoneQTail(port, val)       AscWriteLramWord((port), ASCV_DONE_Q_TAIL_W, val)
#घोषणा AscGetRiscVarFreeQHead(port)        AscReadLramByte((port), ASCV_NEXTRDY_B)
#घोषणा AscGetRiscVarDoneQTail(port)        AscReadLramByte((port), ASCV_DONENEXT_B)
#घोषणा AscPutRiscVarFreeQHead(port, val)   AscWriteLramByte((port), ASCV_NEXTRDY_B, val)
#घोषणा AscPutRiscVarDoneQTail(port, val)   AscWriteLramByte((port), ASCV_DONENEXT_B, val)
#घोषणा AscPutMCodeSDTRDoneAtID(port, id, data)  AscWriteLramByte((port), (uलघु)((uलघु)ASCV_SDTR_DONE_BEG+(uलघु)id), (data))
#घोषणा AscGetMCodeSDTRDoneAtID(port, id)        AscReadLramByte((port), (uलघु)((uलघु)ASCV_SDTR_DONE_BEG+(uलघु)id))
#घोषणा AscPutMCodeInitSDTRAtID(port, id, data)  AscWriteLramByte((port), (uलघु)((uलघु)ASCV_SDTR_DATA_BEG+(uलघु)id), data)
#घोषणा AscGetMCodeInitSDTRAtID(port, id)        AscReadLramByte((port), (uलघु)((uलघु)ASCV_SDTR_DATA_BEG+(uलघु)id))
#घोषणा AscGetChipSignatureByte(port)     (uअक्षर)inp((port)+IOP_SIG_BYTE)
#घोषणा AscGetChipSignatureWord(port)     (uलघु)inpw((port)+IOP_SIG_WORD)
#घोषणा AscGetChipVerNo(port)             (uअक्षर)inp((port)+IOP_VERSION)
#घोषणा AscGetChipCfgLsw(port)            (uलघु)inpw((port)+IOP_CONFIG_LOW)
#घोषणा AscGetChipCfgMsw(port)            (uलघु)inpw((port)+IOP_CONFIG_HIGH)
#घोषणा AscSetChipCfgLsw(port, data)      outpw((port)+IOP_CONFIG_LOW, data)
#घोषणा AscSetChipCfgMsw(port, data)      outpw((port)+IOP_CONFIG_HIGH, data)
#घोषणा AscGetChipEEPCmd(port)            (uअक्षर)inp((port)+IOP_EEP_CMD)
#घोषणा AscSetChipEEPCmd(port, data)      outp((port)+IOP_EEP_CMD, data)
#घोषणा AscGetChipEEPData(port)           (uलघु)inpw((port)+IOP_EEP_DATA)
#घोषणा AscSetChipEEPData(port, data)     outpw((port)+IOP_EEP_DATA, data)
#घोषणा AscGetChipLramAddr(port)          (uलघु)inpw((PortAddr)((port)+IOP_RAM_ADDR))
#घोषणा AscSetChipLramAddr(port, addr)    outpw((PortAddr)((port)+IOP_RAM_ADDR), addr)
#घोषणा AscGetChipLramData(port)          (uलघु)inpw((port)+IOP_RAM_DATA)
#घोषणा AscSetChipLramData(port, data)    outpw((port)+IOP_RAM_DATA, data)
#घोषणा AscGetChipIFC(port)               (uअक्षर)inp((port)+IOP_REG_IFC)
#घोषणा AscSetChipIFC(port, data)          outp((port)+IOP_REG_IFC, data)
#घोषणा AscGetChipStatus(port)            (ASC_CS_TYPE)inpw((port)+IOP_STATUS)
#घोषणा AscSetChipStatus(port, cs_val)    outpw((port)+IOP_STATUS, cs_val)
#घोषणा AscGetChipControl(port)           (uअक्षर)inp((port)+IOP_CTRL)
#घोषणा AscSetChipControl(port, cc_val)   outp((port)+IOP_CTRL, cc_val)
#घोषणा AscGetChipSyn(port)               (uअक्षर)inp((port)+IOP_SYN_OFFSET)
#घोषणा AscSetChipSyn(port, data)         outp((port)+IOP_SYN_OFFSET, data)
#घोषणा AscSetPCAddr(port, data)          outpw((port)+IOP_REG_PC, data)
#घोषणा AscGetPCAddr(port)                (uलघु)inpw((port)+IOP_REG_PC)
#घोषणा AscIsIntPending(port)             (AscGetChipStatus(port) & (CSW_INT_PENDING | CSW_SCSI_RESET_LATCH))
#घोषणा AscGetChipScsiID(port)            ((AscGetChipCfgLsw(port) >> 8) & ASC_MAX_TID)
#घोषणा AscGetExtraControl(port)          (uअक्षर)inp((port)+IOP_EXTRA_CONTROL)
#घोषणा AscSetExtraControl(port, data)    outp((port)+IOP_EXTRA_CONTROL, data)
#घोषणा AscReadChipAX(port)               (uलघु)inpw((port)+IOP_REG_AX)
#घोषणा AscWriteChipAX(port, data)        outpw((port)+IOP_REG_AX, data)
#घोषणा AscReadChipIX(port)               (uअक्षर)inp((port)+IOP_REG_IX)
#घोषणा AscWriteChipIX(port, data)        outp((port)+IOP_REG_IX, data)
#घोषणा AscReadChipIH(port)               (uलघु)inpw((port)+IOP_REG_IH)
#घोषणा AscWriteChipIH(port, data)        outpw((port)+IOP_REG_IH, data)
#घोषणा AscReadChipQP(port)               (uअक्षर)inp((port)+IOP_REG_QP)
#घोषणा AscWriteChipQP(port, data)        outp((port)+IOP_REG_QP, data)
#घोषणा AscReadChipFIFO_L(port)           (uलघु)inpw((port)+IOP_REG_FIFO_L)
#घोषणा AscWriteChipFIFO_L(port, data)    outpw((port)+IOP_REG_FIFO_L, data)
#घोषणा AscReadChipFIFO_H(port)           (uलघु)inpw((port)+IOP_REG_FIFO_H)
#घोषणा AscWriteChipFIFO_H(port, data)    outpw((port)+IOP_REG_FIFO_H, data)
#घोषणा AscReadChipDmaSpeed(port)         (uअक्षर)inp((port)+IOP_DMA_SPEED)
#घोषणा AscWriteChipDmaSpeed(port, data)  outp((port)+IOP_DMA_SPEED, data)
#घोषणा AscReadChipDA0(port)              (uलघु)inpw((port)+IOP_REG_DA0)
#घोषणा AscWriteChipDA0(port)             outpw((port)+IOP_REG_DA0, data)
#घोषणा AscReadChipDA1(port)              (uलघु)inpw((port)+IOP_REG_DA1)
#घोषणा AscWriteChipDA1(port)             outpw((port)+IOP_REG_DA1, data)
#घोषणा AscReadChipDC0(port)              (uलघु)inpw((port)+IOP_REG_DC0)
#घोषणा AscWriteChipDC0(port)             outpw((port)+IOP_REG_DC0, data)
#घोषणा AscReadChipDC1(port)              (uलघु)inpw((port)+IOP_REG_DC1)
#घोषणा AscWriteChipDC1(port)             outpw((port)+IOP_REG_DC1, data)
#घोषणा AscReadChipDvcID(port)            (uअक्षर)inp((port)+IOP_REG_ID)
#घोषणा AscWriteChipDvcID(port, data)     outp((port)+IOP_REG_ID, data)

#घोषणा AdvPortAddr  व्योम __iomem *	/* Virtual memory address size */

/*
 * Define Adv Library required memory access macros.
 */
#घोषणा ADV_MEM_READB(addr) पढ़ोb(addr)
#घोषणा ADV_MEM_READW(addr) पढ़ोw(addr)
#घोषणा ADV_MEM_WRITEB(addr, byte) ग_लिखोb(byte, addr)
#घोषणा ADV_MEM_WRITEW(addr, word) ग_लिखोw(word, addr)
#घोषणा ADV_MEM_WRITEDW(addr, dword) ग_लिखोl(dword, addr)

/*
 * Define total number of simultaneous maximum element scatter-gather
 * request blocks per wide adapter. ASC_DEF_MAX_HOST_QNG (253) is the
 * maximum number of outstanding commands per wide host adapter. Each
 * command uses one or more ADV_SG_BLOCK each with 15 scatter-gather
 * elements. Allow each command to have at least one ADV_SG_BLOCK काष्ठाure.
 * This allows about 15 commands to have the maximum 17 ADV_SG_BLOCK
 * काष्ठाures or 255 scatter-gather elements.
 */
#घोषणा ADV_TOT_SG_BLOCK        ASC_DEF_MAX_HOST_QNG

/*
 * Define maximum number of scatter-gather elements per request.
 */
#घोषणा ADV_MAX_SG_LIST         255
#घोषणा NO_OF_SG_PER_BLOCK              15

#घोषणा ADV_EEP_DVC_CFG_BEGIN           (0x00)
#घोषणा ADV_EEP_DVC_CFG_END             (0x15)
#घोषणा ADV_EEP_DVC_CTL_BEGIN           (0x16)	/* location of OEM name */
#घोषणा ADV_EEP_MAX_WORD_ADDR           (0x1E)

#घोषणा ADV_EEP_DELAY_MS                100

#घोषणा ADV_EEPROM_BIG_ENDIAN          0x8000	/* EEPROM Bit 15 */
#घोषणा ADV_EEPROM_BIOS_ENABLE         0x4000	/* EEPROM Bit 14 */
/*
 * For the ASC3550 Bit 13 is Termination Polarity control bit.
 * For later ICs Bit 13 controls whether the CIS (Card Inक्रमmation
 * Service Section) is loaded from EEPROM.
 */
#घोषणा ADV_EEPROM_TERM_POL            0x2000	/* EEPROM Bit 13 */
#घोषणा ADV_EEPROM_CIS_LD              0x2000	/* EEPROM Bit 13 */
/*
 * ASC38C1600 Bit 11
 *
 * If EEPROM Bit 11 is 0 क्रम Function 0, then Function 0 will specअगरy
 * INT A in the PCI Configuration Space Int Pin field. If it is 1, then
 * Function 0 will specअगरy INT B.
 *
 * If EEPROM Bit 11 is 0 क्रम Function 1, then Function 1 will specअगरy
 * INT B in the PCI Configuration Space Int Pin field. If it is 1, then
 * Function 1 will specअगरy INT A.
 */
#घोषणा ADV_EEPROM_INTAB               0x0800	/* EEPROM Bit 11 */

प्रकार काष्ठा adveep_3550_config अणु
	/* Word Offset, Description */

	uलघु cfg_lsw;		/* 00 घातer up initialization */
	/*  bit 13 set - Term Polarity Control */
	/*  bit 14 set - BIOS Enable */
	/*  bit 15 set - Big Endian Mode */
	uलघु cfg_msw;		/* 01 unused      */
	uलघु disc_enable;	/* 02 disconnect enable */
	uलघु wdtr_able;	/* 03 Wide DTR able */
	uलघु sdtr_able;	/* 04 Synchronous DTR able */
	uलघु start_motor;	/* 05 send start up motor */
	uलघु tagqng_able;	/* 06 tag queuing able */
	uलघु bios_scan;	/* 07 BIOS device control */
	uलघु scam_tolerant;	/* 08 no scam */

	uअक्षर adapter_scsi_id;	/* 09 Host Adapter ID */
	uअक्षर bios_boot_delay;	/*    घातer up रुको */

	uअक्षर scsi_reset_delay;	/* 10 reset delay */
	uअक्षर bios_id_lun;	/*    first boot device scsi id & lun */
	/*    high nibble is lun */
	/*    low nibble is scsi id */

	uअक्षर termination;	/* 11 0 - स्वतःmatic */
	/*    1 - low off / high off */
	/*    2 - low off / high on */
	/*    3 - low on  / high on */
	/*    There is no low on  / high off */

	uअक्षर reserved1;	/*    reserved byte (not used) */

	uलघु bios_ctrl;	/* 12 BIOS control bits */
	/*  bit 0  BIOS करोn't act as initiator. */
	/*  bit 1  BIOS > 1 GB support */
	/*  bit 2  BIOS > 2 Disk Support */
	/*  bit 3  BIOS करोn't support removables */
	/*  bit 4  BIOS support bootable CD */
	/*  bit 5  BIOS scan enabled */
	/*  bit 6  BIOS support multiple LUNs */
	/*  bit 7  BIOS display of message */
	/*  bit 8  SCAM disabled */
	/*  bit 9  Reset SCSI bus during init. */
	/*  bit 10 */
	/*  bit 11 No verbose initialization. */
	/*  bit 12 SCSI parity enabled */
	/*  bit 13 */
	/*  bit 14 */
	/*  bit 15 */
	uलघु ultra_able;	/* 13 ULTRA speed able */
	uलघु reserved2;	/* 14 reserved */
	uअक्षर max_host_qng;	/* 15 maximum host queuing */
	uअक्षर max_dvc_qng;	/*    maximum per device queuing */
	uलघु dvc_cntl;	/* 16 control bit क्रम driver */
	uलघु bug_fix;		/* 17 control bit क्रम bug fix */
	uलघु serial_number_word1;	/* 18 Board serial number word 1 */
	uलघु serial_number_word2;	/* 19 Board serial number word 2 */
	uलघु serial_number_word3;	/* 20 Board serial number word 3 */
	uलघु check_sum;	/* 21 EEP check sum */
	uअक्षर oem_name[16];	/* 22 OEM name */
	uलघु dvc_err_code;	/* 30 last device driver error code */
	uलघु adv_err_code;	/* 31 last uc and Adv Lib error code */
	uलघु adv_err_addr;	/* 32 last uc error address */
	uलघु saved_dvc_err_code;	/* 33 saved last dev. driver error code   */
	uलघु saved_adv_err_code;	/* 34 saved last uc and Adv Lib error code */
	uलघु saved_adv_err_addr;	/* 35 saved last uc error address         */
	uलघु num_of_err;	/* 36 number of error */
पूर्ण ADVEEP_3550_CONFIG;

प्रकार काष्ठा adveep_38C0800_config अणु
	/* Word Offset, Description */

	uलघु cfg_lsw;		/* 00 घातer up initialization */
	/*  bit 13 set - Load CIS */
	/*  bit 14 set - BIOS Enable */
	/*  bit 15 set - Big Endian Mode */
	uलघु cfg_msw;		/* 01 unused      */
	uलघु disc_enable;	/* 02 disconnect enable */
	uलघु wdtr_able;	/* 03 Wide DTR able */
	uलघु sdtr_speed1;	/* 04 SDTR Speed TID 0-3 */
	uलघु start_motor;	/* 05 send start up motor */
	uलघु tagqng_able;	/* 06 tag queuing able */
	uलघु bios_scan;	/* 07 BIOS device control */
	uलघु scam_tolerant;	/* 08 no scam */

	uअक्षर adapter_scsi_id;	/* 09 Host Adapter ID */
	uअक्षर bios_boot_delay;	/*    घातer up रुको */

	uअक्षर scsi_reset_delay;	/* 10 reset delay */
	uअक्षर bios_id_lun;	/*    first boot device scsi id & lun */
	/*    high nibble is lun */
	/*    low nibble is scsi id */

	uअक्षर termination_se;	/* 11 0 - स्वतःmatic */
	/*    1 - low off / high off */
	/*    2 - low off / high on */
	/*    3 - low on  / high on */
	/*    There is no low on  / high off */

	uअक्षर termination_lvd;	/* 11 0 - स्वतःmatic */
	/*    1 - low off / high off */
	/*    2 - low off / high on */
	/*    3 - low on  / high on */
	/*    There is no low on  / high off */

	uलघु bios_ctrl;	/* 12 BIOS control bits */
	/*  bit 0  BIOS करोn't act as initiator. */
	/*  bit 1  BIOS > 1 GB support */
	/*  bit 2  BIOS > 2 Disk Support */
	/*  bit 3  BIOS करोn't support removables */
	/*  bit 4  BIOS support bootable CD */
	/*  bit 5  BIOS scan enabled */
	/*  bit 6  BIOS support multiple LUNs */
	/*  bit 7  BIOS display of message */
	/*  bit 8  SCAM disabled */
	/*  bit 9  Reset SCSI bus during init. */
	/*  bit 10 */
	/*  bit 11 No verbose initialization. */
	/*  bit 12 SCSI parity enabled */
	/*  bit 13 */
	/*  bit 14 */
	/*  bit 15 */
	uलघु sdtr_speed2;	/* 13 SDTR speed TID 4-7 */
	uलघु sdtr_speed3;	/* 14 SDTR speed TID 8-11 */
	uअक्षर max_host_qng;	/* 15 maximum host queueing */
	uअक्षर max_dvc_qng;	/*    maximum per device queuing */
	uलघु dvc_cntl;	/* 16 control bit क्रम driver */
	uलघु sdtr_speed4;	/* 17 SDTR speed 4 TID 12-15 */
	uलघु serial_number_word1;	/* 18 Board serial number word 1 */
	uलघु serial_number_word2;	/* 19 Board serial number word 2 */
	uलघु serial_number_word3;	/* 20 Board serial number word 3 */
	uलघु check_sum;	/* 21 EEP check sum */
	uअक्षर oem_name[16];	/* 22 OEM name */
	uलघु dvc_err_code;	/* 30 last device driver error code */
	uलघु adv_err_code;	/* 31 last uc and Adv Lib error code */
	uलघु adv_err_addr;	/* 32 last uc error address */
	uलघु saved_dvc_err_code;	/* 33 saved last dev. driver error code   */
	uलघु saved_adv_err_code;	/* 34 saved last uc and Adv Lib error code */
	uलघु saved_adv_err_addr;	/* 35 saved last uc error address         */
	uलघु reserved36;	/* 36 reserved */
	uलघु reserved37;	/* 37 reserved */
	uलघु reserved38;	/* 38 reserved */
	uलघु reserved39;	/* 39 reserved */
	uलघु reserved40;	/* 40 reserved */
	uलघु reserved41;	/* 41 reserved */
	uलघु reserved42;	/* 42 reserved */
	uलघु reserved43;	/* 43 reserved */
	uलघु reserved44;	/* 44 reserved */
	uलघु reserved45;	/* 45 reserved */
	uलघु reserved46;	/* 46 reserved */
	uलघु reserved47;	/* 47 reserved */
	uलघु reserved48;	/* 48 reserved */
	uलघु reserved49;	/* 49 reserved */
	uलघु reserved50;	/* 50 reserved */
	uलघु reserved51;	/* 51 reserved */
	uलघु reserved52;	/* 52 reserved */
	uलघु reserved53;	/* 53 reserved */
	uलघु reserved54;	/* 54 reserved */
	uलघु reserved55;	/* 55 reserved */
	uलघु cisptr_lsw;	/* 56 CIS PTR LSW */
	uलघु cisprt_msw;	/* 57 CIS PTR MSW */
	uलघु subsysvid;	/* 58 SubSystem Venकरोr ID */
	uलघु subsysid;	/* 59 SubSystem ID */
	uलघु reserved60;	/* 60 reserved */
	uलघु reserved61;	/* 61 reserved */
	uलघु reserved62;	/* 62 reserved */
	uलघु reserved63;	/* 63 reserved */
पूर्ण ADVEEP_38C0800_CONFIG;

प्रकार काष्ठा adveep_38C1600_config अणु
	/* Word Offset, Description */

	uलघु cfg_lsw;		/* 00 घातer up initialization */
	/*  bit 11 set - Func. 0 INTB, Func. 1 INTA */
	/*       clear - Func. 0 INTA, Func. 1 INTB */
	/*  bit 13 set - Load CIS */
	/*  bit 14 set - BIOS Enable */
	/*  bit 15 set - Big Endian Mode */
	uलघु cfg_msw;		/* 01 unused */
	uलघु disc_enable;	/* 02 disconnect enable */
	uलघु wdtr_able;	/* 03 Wide DTR able */
	uलघु sdtr_speed1;	/* 04 SDTR Speed TID 0-3 */
	uलघु start_motor;	/* 05 send start up motor */
	uलघु tagqng_able;	/* 06 tag queuing able */
	uलघु bios_scan;	/* 07 BIOS device control */
	uलघु scam_tolerant;	/* 08 no scam */

	uअक्षर adapter_scsi_id;	/* 09 Host Adapter ID */
	uअक्षर bios_boot_delay;	/*    घातer up रुको */

	uअक्षर scsi_reset_delay;	/* 10 reset delay */
	uअक्षर bios_id_lun;	/*    first boot device scsi id & lun */
	/*    high nibble is lun */
	/*    low nibble is scsi id */

	uअक्षर termination_se;	/* 11 0 - स्वतःmatic */
	/*    1 - low off / high off */
	/*    2 - low off / high on */
	/*    3 - low on  / high on */
	/*    There is no low on  / high off */

	uअक्षर termination_lvd;	/* 11 0 - स्वतःmatic */
	/*    1 - low off / high off */
	/*    2 - low off / high on */
	/*    3 - low on  / high on */
	/*    There is no low on  / high off */

	uलघु bios_ctrl;	/* 12 BIOS control bits */
	/*  bit 0  BIOS करोn't act as initiator. */
	/*  bit 1  BIOS > 1 GB support */
	/*  bit 2  BIOS > 2 Disk Support */
	/*  bit 3  BIOS करोn't support removables */
	/*  bit 4  BIOS support bootable CD */
	/*  bit 5  BIOS scan enabled */
	/*  bit 6  BIOS support multiple LUNs */
	/*  bit 7  BIOS display of message */
	/*  bit 8  SCAM disabled */
	/*  bit 9  Reset SCSI bus during init. */
	/*  bit 10 Basic Integrity Checking disabled */
	/*  bit 11 No verbose initialization. */
	/*  bit 12 SCSI parity enabled */
	/*  bit 13 AIPP (Asyn. Info. Ph. Prot.) dis. */
	/*  bit 14 */
	/*  bit 15 */
	uलघु sdtr_speed2;	/* 13 SDTR speed TID 4-7 */
	uलघु sdtr_speed3;	/* 14 SDTR speed TID 8-11 */
	uअक्षर max_host_qng;	/* 15 maximum host queueing */
	uअक्षर max_dvc_qng;	/*    maximum per device queuing */
	uलघु dvc_cntl;	/* 16 control bit क्रम driver */
	uलघु sdtr_speed4;	/* 17 SDTR speed 4 TID 12-15 */
	uलघु serial_number_word1;	/* 18 Board serial number word 1 */
	uलघु serial_number_word2;	/* 19 Board serial number word 2 */
	uलघु serial_number_word3;	/* 20 Board serial number word 3 */
	uलघु check_sum;	/* 21 EEP check sum */
	uअक्षर oem_name[16];	/* 22 OEM name */
	uलघु dvc_err_code;	/* 30 last device driver error code */
	uलघु adv_err_code;	/* 31 last uc and Adv Lib error code */
	uलघु adv_err_addr;	/* 32 last uc error address */
	uलघु saved_dvc_err_code;	/* 33 saved last dev. driver error code   */
	uलघु saved_adv_err_code;	/* 34 saved last uc and Adv Lib error code */
	uलघु saved_adv_err_addr;	/* 35 saved last uc error address         */
	uलघु reserved36;	/* 36 reserved */
	uलघु reserved37;	/* 37 reserved */
	uलघु reserved38;	/* 38 reserved */
	uलघु reserved39;	/* 39 reserved */
	uलघु reserved40;	/* 40 reserved */
	uलघु reserved41;	/* 41 reserved */
	uलघु reserved42;	/* 42 reserved */
	uलघु reserved43;	/* 43 reserved */
	uलघु reserved44;	/* 44 reserved */
	uलघु reserved45;	/* 45 reserved */
	uलघु reserved46;	/* 46 reserved */
	uलघु reserved47;	/* 47 reserved */
	uलघु reserved48;	/* 48 reserved */
	uलघु reserved49;	/* 49 reserved */
	uलघु reserved50;	/* 50 reserved */
	uलघु reserved51;	/* 51 reserved */
	uलघु reserved52;	/* 52 reserved */
	uलघु reserved53;	/* 53 reserved */
	uलघु reserved54;	/* 54 reserved */
	uलघु reserved55;	/* 55 reserved */
	uलघु cisptr_lsw;	/* 56 CIS PTR LSW */
	uलघु cisprt_msw;	/* 57 CIS PTR MSW */
	uलघु subsysvid;	/* 58 SubSystem Venकरोr ID */
	uलघु subsysid;	/* 59 SubSystem ID */
	uलघु reserved60;	/* 60 reserved */
	uलघु reserved61;	/* 61 reserved */
	uलघु reserved62;	/* 62 reserved */
	uलघु reserved63;	/* 63 reserved */
पूर्ण ADVEEP_38C1600_CONFIG;

/*
 * EEPROM Commands
 */
#घोषणा ASC_EEP_CMD_DONE             0x0200

/* bios_ctrl */
#घोषणा BIOS_CTRL_BIOS               0x0001
#घोषणा BIOS_CTRL_EXTENDED_XLAT      0x0002
#घोषणा BIOS_CTRL_GT_2_DISK          0x0004
#घोषणा BIOS_CTRL_BIOS_REMOVABLE     0x0008
#घोषणा BIOS_CTRL_BOOTABLE_CD        0x0010
#घोषणा BIOS_CTRL_MULTIPLE_LUN       0x0040
#घोषणा BIOS_CTRL_DISPLAY_MSG        0x0080
#घोषणा BIOS_CTRL_NO_SCAM            0x0100
#घोषणा BIOS_CTRL_RESET_SCSI_BUS     0x0200
#घोषणा BIOS_CTRL_INIT_VERBOSE       0x0800
#घोषणा BIOS_CTRL_SCSI_PARITY        0x1000
#घोषणा BIOS_CTRL_AIPP_DIS           0x2000

#घोषणा ADV_3550_MEMSIZE   0x2000	/* 8 KB Internal Memory */

#घोषणा ADV_38C0800_MEMSIZE  0x4000	/* 16 KB Internal Memory */

/*
 * XXX - Since ASC38C1600 Rev.3 has a local RAM failure issue, there is
 * a special 16K Adv Library and Microcode version. After the issue is
 * resolved, should restore 32K support.
 *
 * #घोषणा ADV_38C1600_MEMSIZE  0x8000L   * 32 KB Internal Memory *
 */
#घोषणा ADV_38C1600_MEMSIZE  0x4000	/* 16 KB Internal Memory */

/*
 * Byte I/O रेजिस्टर address from base of 'iop_base'.
 */
#घोषणा IOPB_INTR_STATUS_REG    0x00
#घोषणा IOPB_CHIP_ID_1          0x01
#घोषणा IOPB_INTR_ENABLES       0x02
#घोषणा IOPB_CHIP_TYPE_REV      0x03
#घोषणा IOPB_RES_ADDR_4         0x04
#घोषणा IOPB_RES_ADDR_5         0x05
#घोषणा IOPB_RAM_DATA           0x06
#घोषणा IOPB_RES_ADDR_7         0x07
#घोषणा IOPB_FLAG_REG           0x08
#घोषणा IOPB_RES_ADDR_9         0x09
#घोषणा IOPB_RISC_CSR           0x0A
#घोषणा IOPB_RES_ADDR_B         0x0B
#घोषणा IOPB_RES_ADDR_C         0x0C
#घोषणा IOPB_RES_ADDR_D         0x0D
#घोषणा IOPB_SOFT_OVER_WR       0x0E
#घोषणा IOPB_RES_ADDR_F         0x0F
#घोषणा IOPB_MEM_CFG            0x10
#घोषणा IOPB_RES_ADDR_11        0x11
#घोषणा IOPB_GPIO_DATA          0x12
#घोषणा IOPB_RES_ADDR_13        0x13
#घोषणा IOPB_FLASH_PAGE         0x14
#घोषणा IOPB_RES_ADDR_15        0x15
#घोषणा IOPB_GPIO_CNTL          0x16
#घोषणा IOPB_RES_ADDR_17        0x17
#घोषणा IOPB_FLASH_DATA         0x18
#घोषणा IOPB_RES_ADDR_19        0x19
#घोषणा IOPB_RES_ADDR_1A        0x1A
#घोषणा IOPB_RES_ADDR_1B        0x1B
#घोषणा IOPB_RES_ADDR_1C        0x1C
#घोषणा IOPB_RES_ADDR_1D        0x1D
#घोषणा IOPB_RES_ADDR_1E        0x1E
#घोषणा IOPB_RES_ADDR_1F        0x1F
#घोषणा IOPB_DMA_CFG0           0x20
#घोषणा IOPB_DMA_CFG1           0x21
#घोषणा IOPB_TICKLE             0x22
#घोषणा IOPB_DMA_REG_WR         0x23
#घोषणा IOPB_SDMA_STATUS        0x24
#घोषणा IOPB_SCSI_BYTE_CNT      0x25
#घोषणा IOPB_HOST_BYTE_CNT      0x26
#घोषणा IOPB_BYTE_LEFT_TO_XFER  0x27
#घोषणा IOPB_BYTE_TO_XFER_0     0x28
#घोषणा IOPB_BYTE_TO_XFER_1     0x29
#घोषणा IOPB_BYTE_TO_XFER_2     0x2A
#घोषणा IOPB_BYTE_TO_XFER_3     0x2B
#घोषणा IOPB_ACC_GRP            0x2C
#घोषणा IOPB_RES_ADDR_2D        0x2D
#घोषणा IOPB_DEV_ID             0x2E
#घोषणा IOPB_RES_ADDR_2F        0x2F
#घोषणा IOPB_SCSI_DATA          0x30
#घोषणा IOPB_RES_ADDR_31        0x31
#घोषणा IOPB_RES_ADDR_32        0x32
#घोषणा IOPB_SCSI_DATA_HSHK     0x33
#घोषणा IOPB_SCSI_CTRL          0x34
#घोषणा IOPB_RES_ADDR_35        0x35
#घोषणा IOPB_RES_ADDR_36        0x36
#घोषणा IOPB_RES_ADDR_37        0x37
#घोषणा IOPB_RAM_BIST           0x38
#घोषणा IOPB_PLL_TEST           0x39
#घोषणा IOPB_PCI_INT_CFG        0x3A
#घोषणा IOPB_RES_ADDR_3B        0x3B
#घोषणा IOPB_RFIFO_CNT          0x3C
#घोषणा IOPB_RES_ADDR_3D        0x3D
#घोषणा IOPB_RES_ADDR_3E        0x3E
#घोषणा IOPB_RES_ADDR_3F        0x3F

/*
 * Word I/O रेजिस्टर address from base of 'iop_base'.
 */
#घोषणा IOPW_CHIP_ID_0          0x00	/* CID0  */
#घोषणा IOPW_CTRL_REG           0x02	/* CC    */
#घोषणा IOPW_RAM_ADDR           0x04	/* LA    */
#घोषणा IOPW_RAM_DATA           0x06	/* LD    */
#घोषणा IOPW_RES_ADDR_08        0x08
#घोषणा IOPW_RISC_CSR           0x0A	/* CSR   */
#घोषणा IOPW_SCSI_CFG0          0x0C	/* CFG0  */
#घोषणा IOPW_SCSI_CFG1          0x0E	/* CFG1  */
#घोषणा IOPW_RES_ADDR_10        0x10
#घोषणा IOPW_SEL_MASK           0x12	/* SM    */
#घोषणा IOPW_RES_ADDR_14        0x14
#घोषणा IOPW_FLASH_ADDR         0x16	/* FA    */
#घोषणा IOPW_RES_ADDR_18        0x18
#घोषणा IOPW_EE_CMD             0x1A	/* EC    */
#घोषणा IOPW_EE_DATA            0x1C	/* ED    */
#घोषणा IOPW_SFIFO_CNT          0x1E	/* SFC   */
#घोषणा IOPW_RES_ADDR_20        0x20
#घोषणा IOPW_Q_BASE             0x22	/* QB    */
#घोषणा IOPW_QP                 0x24	/* QP    */
#घोषणा IOPW_IX                 0x26	/* IX    */
#घोषणा IOPW_SP                 0x28	/* SP    */
#घोषणा IOPW_PC                 0x2A	/* PC    */
#घोषणा IOPW_RES_ADDR_2C        0x2C
#घोषणा IOPW_RES_ADDR_2E        0x2E
#घोषणा IOPW_SCSI_DATA          0x30	/* SD    */
#घोषणा IOPW_SCSI_DATA_HSHK     0x32	/* SDH   */
#घोषणा IOPW_SCSI_CTRL          0x34	/* SC    */
#घोषणा IOPW_HSHK_CFG           0x36	/* HCFG  */
#घोषणा IOPW_SXFR_STATUS        0x36	/* SXS   */
#घोषणा IOPW_SXFR_CNTL          0x38	/* SXL   */
#घोषणा IOPW_SXFR_CNTH          0x3A	/* SXH   */
#घोषणा IOPW_RES_ADDR_3C        0x3C
#घोषणा IOPW_RFIFO_DATA         0x3E	/* RFD   */

/*
 * Doubleword I/O रेजिस्टर address from base of 'iop_base'.
 */
#घोषणा IOPDW_RES_ADDR_0         0x00
#घोषणा IOPDW_RAM_DATA           0x04
#घोषणा IOPDW_RES_ADDR_8         0x08
#घोषणा IOPDW_RES_ADDR_C         0x0C
#घोषणा IOPDW_RES_ADDR_10        0x10
#घोषणा IOPDW_COMMA              0x14
#घोषणा IOPDW_COMMB              0x18
#घोषणा IOPDW_RES_ADDR_1C        0x1C
#घोषणा IOPDW_SDMA_ADDR0         0x20
#घोषणा IOPDW_SDMA_ADDR1         0x24
#घोषणा IOPDW_SDMA_COUNT         0x28
#घोषणा IOPDW_SDMA_ERROR         0x2C
#घोषणा IOPDW_RDMA_ADDR0         0x30
#घोषणा IOPDW_RDMA_ADDR1         0x34
#घोषणा IOPDW_RDMA_COUNT         0x38
#घोषणा IOPDW_RDMA_ERROR         0x3C

#घोषणा ADV_CHIP_ID_BYTE         0x25
#घोषणा ADV_CHIP_ID_WORD         0x04C1

#घोषणा ADV_INTR_ENABLE_HOST_INTR                   0x01
#घोषणा ADV_INTR_ENABLE_SEL_INTR                    0x02
#घोषणा ADV_INTR_ENABLE_DPR_INTR                    0x04
#घोषणा ADV_INTR_ENABLE_RTA_INTR                    0x08
#घोषणा ADV_INTR_ENABLE_RMA_INTR                    0x10
#घोषणा ADV_INTR_ENABLE_RST_INTR                    0x20
#घोषणा ADV_INTR_ENABLE_DPE_INTR                    0x40
#घोषणा ADV_INTR_ENABLE_GLOBAL_INTR                 0x80

#घोषणा ADV_INTR_STATUS_INTRA            0x01
#घोषणा ADV_INTR_STATUS_INTRB            0x02
#घोषणा ADV_INTR_STATUS_INTRC            0x04

#घोषणा ADV_RISC_CSR_STOP           (0x0000)
#घोषणा ADV_RISC_TEST_COND          (0x2000)
#घोषणा ADV_RISC_CSR_RUN            (0x4000)
#घोषणा ADV_RISC_CSR_SINGLE_STEP    (0x8000)

#घोषणा ADV_CTRL_REG_HOST_INTR      0x0100
#घोषणा ADV_CTRL_REG_SEL_INTR       0x0200
#घोषणा ADV_CTRL_REG_DPR_INTR       0x0400
#घोषणा ADV_CTRL_REG_RTA_INTR       0x0800
#घोषणा ADV_CTRL_REG_RMA_INTR       0x1000
#घोषणा ADV_CTRL_REG_RES_BIT14      0x2000
#घोषणा ADV_CTRL_REG_DPE_INTR       0x4000
#घोषणा ADV_CTRL_REG_POWER_DONE     0x8000
#घोषणा ADV_CTRL_REG_ANY_INTR       0xFF00

#घोषणा ADV_CTRL_REG_CMD_RESET             0x00C6
#घोषणा ADV_CTRL_REG_CMD_WR_IO_REG         0x00C5
#घोषणा ADV_CTRL_REG_CMD_RD_IO_REG         0x00C4
#घोषणा ADV_CTRL_REG_CMD_WR_PCI_CFG_SPACE  0x00C3
#घोषणा ADV_CTRL_REG_CMD_RD_PCI_CFG_SPACE  0x00C2

#घोषणा ADV_TICKLE_NOP                      0x00
#घोषणा ADV_TICKLE_A                        0x01
#घोषणा ADV_TICKLE_B                        0x02
#घोषणा ADV_TICKLE_C                        0x03

#घोषणा AdvIsIntPending(port) \
    (AdvReadWordRegister(port, IOPW_CTRL_REG) & ADV_CTRL_REG_HOST_INTR)

/*
 * SCSI_CFG0 Register bit definitions
 */
#घोषणा TIMER_MODEAB    0xC000	/* Watchकरोg, Second, and Select. Timer Ctrl. */
#घोषणा PARITY_EN       0x2000	/* Enable SCSI Parity Error detection */
#घोषणा EVEN_PARITY     0x1000	/* Select Even Parity */
#घोषणा WD_LONG         0x0800	/* Watchकरोg Interval, 1: 57 min, 0: 13 sec */
#घोषणा QUEUE_128       0x0400	/* Queue Size, 1: 128 byte, 0: 64 byte */
#घोषणा PRIM_MODE       0x0100	/* Primitive SCSI mode */
#घोषणा SCAM_EN         0x0080	/* Enable SCAM selection */
#घोषणा SEL_TMO_LONG    0x0040	/* Sel/Resel Timeout, 1: 400 ms, 0: 1.6 ms */
#घोषणा CFRM_ID         0x0020	/* SCAM id sel. confirm., 1: fast, 0: 6.4 ms */
#घोषणा OUR_ID_EN       0x0010	/* Enable OUR_ID bits */
#घोषणा OUR_ID          0x000F	/* SCSI ID */

/*
 * SCSI_CFG1 Register bit definitions
 */
#घोषणा BIG_ENDIAN      0x8000	/* Enable Big Endian Mode MIO:15, EEP:15 */
#घोषणा TERM_POL        0x2000	/* Terminator Polarity Ctrl. MIO:13, EEP:13 */
#घोषणा SLEW_RATE       0x1000	/* SCSI output buffer slew rate */
#घोषणा FILTER_SEL      0x0C00	/* Filter Period Selection */
#घोषणा  FLTR_DISABLE    0x0000	/* Input Filtering Disabled */
#घोषणा  FLTR_11_TO_20NS 0x0800	/* Input Filtering 11ns to 20ns */
#घोषणा  FLTR_21_TO_39NS 0x0C00	/* Input Filtering 21ns to 39ns */
#घोषणा ACTIVE_DBL      0x0200	/* Disable Active Negation */
#घोषणा DIFF_MODE       0x0100	/* SCSI dअगरferential Mode (Read-Only) */
#घोषणा DIFF_SENSE      0x0080	/* 1: No SE cables, 0: SE cable (Read-Only) */
#घोषणा TERM_CTL_SEL    0x0040	/* Enable TERM_CTL_H and TERM_CTL_L */
#घोषणा TERM_CTL        0x0030	/* External SCSI Termination Bits */
#घोषणा  TERM_CTL_H      0x0020	/* Enable External SCSI Upper Termination */
#घोषणा  TERM_CTL_L      0x0010	/* Enable External SCSI Lower Termination */
#घोषणा CABLE_DETECT    0x000F	/* External SCSI Cable Connection Status */

/*
 * Addendum क्रम ASC-38C0800 Chip
 *
 * The ASC-38C1600 Chip uses the same definitions except that the
 * bus mode override bits [12:10] have been moved to byte रेजिस्टर
 * offset 0xE (IOPB_SOFT_OVER_WR) bits [12:10]. The [12:10] bits in
 * SCSI_CFG1 are पढ़ो-only and always available. Bit 14 (DIS_TERM_DRV)
 * is not needed. The [12:10] bits in IOPB_SOFT_OVER_WR are ग_लिखो-only.
 * Also each ASC-38C1600 function or channel uses only cable bits [5:4]
 * and [1:0]. Bits [14], [7:6], [3:2] are unused.
 */
#घोषणा DIS_TERM_DRV    0x4000	/* 1: Read c_det[3:0], 0: cannot पढ़ो */
#घोषणा HVD_LVD_SE      0x1C00	/* Device Detect Bits */
#घोषणा  HVD             0x1000	/* HVD Device Detect */
#घोषणा  LVD             0x0800	/* LVD Device Detect */
#घोषणा  SE              0x0400	/* SE Device Detect */
#घोषणा TERM_LVD        0x00C0	/* LVD Termination Bits */
#घोषणा  TERM_LVD_HI     0x0080	/* Enable LVD Upper Termination */
#घोषणा  TERM_LVD_LO     0x0040	/* Enable LVD Lower Termination */
#घोषणा TERM_SE         0x0030	/* SE Termination Bits */
#घोषणा  TERM_SE_HI      0x0020	/* Enable SE Upper Termination */
#घोषणा  TERM_SE_LO      0x0010	/* Enable SE Lower Termination */
#घोषणा C_DET_LVD       0x000C	/* LVD Cable Detect Bits */
#घोषणा  C_DET3          0x0008	/* Cable Detect क्रम LVD External Wide */
#घोषणा  C_DET2          0x0004	/* Cable Detect क्रम LVD Internal Wide */
#घोषणा C_DET_SE        0x0003	/* SE Cable Detect Bits */
#घोषणा  C_DET1          0x0002	/* Cable Detect क्रम SE Internal Wide */
#घोषणा  C_DET0          0x0001	/* Cable Detect क्रम SE Internal Narrow */

#घोषणा CABLE_ILLEGAL_A 0x7
    /* x 0 0 0  | on  on | Illegal (all 3 connectors are used) */

#घोषणा CABLE_ILLEGAL_B 0xB
    /* 0 x 0 0  | on  on | Illegal (all 3 connectors are used) */

/*
 * MEM_CFG Register bit definitions
 */
#घोषणा BIOS_EN         0x40	/* BIOS Enable MIO:14,EEP:14 */
#घोषणा FAST_EE_CLK     0x20	/* Diagnostic Bit */
#घोषणा RAM_SZ          0x1C	/* Specअगरy size of RAM to RISC */
#घोषणा  RAM_SZ_2KB      0x00	/* 2 KB */
#घोषणा  RAM_SZ_4KB      0x04	/* 4 KB */
#घोषणा  RAM_SZ_8KB      0x08	/* 8 KB */
#घोषणा  RAM_SZ_16KB     0x0C	/* 16 KB */
#घोषणा  RAM_SZ_32KB     0x10	/* 32 KB */
#घोषणा  RAM_SZ_64KB     0x14	/* 64 KB */

/*
 * DMA_CFG0 Register bit definitions
 *
 * This रेजिस्टर is only accessible to the host.
 */
#घोषणा BC_THRESH_ENB   0x80	/* PCI DMA Start Conditions */
#घोषणा FIFO_THRESH     0x70	/* PCI DMA FIFO Threshold */
#घोषणा  FIFO_THRESH_16B  0x00	/* 16 bytes */
#घोषणा  FIFO_THRESH_32B  0x20	/* 32 bytes */
#घोषणा  FIFO_THRESH_48B  0x30	/* 48 bytes */
#घोषणा  FIFO_THRESH_64B  0x40	/* 64 bytes */
#घोषणा  FIFO_THRESH_80B  0x50	/* 80 bytes (शेष) */
#घोषणा  FIFO_THRESH_96B  0x60	/* 96 bytes */
#घोषणा  FIFO_THRESH_112B 0x70	/* 112 bytes */
#घोषणा START_CTL       0x0C	/* DMA start conditions */
#घोषणा  START_CTL_TH    0x00	/* Wait threshold level (शेष) */
#घोषणा  START_CTL_ID    0x04	/* Wait SDMA/SBUS idle */
#घोषणा  START_CTL_THID  0x08	/* Wait threshold and SDMA/SBUS idle */
#घोषणा  START_CTL_EMFU  0x0C	/* Wait SDMA FIFO empty/full */
#घोषणा READ_CMD        0x03	/* Memory Read Method */
#घोषणा  READ_CMD_MR     0x00	/* Memory Read */
#घोषणा  READ_CMD_MRL    0x02	/* Memory Read Long */
#घोषणा  READ_CMD_MRM    0x03	/* Memory Read Multiple (शेष) */

/*
 * ASC-38C0800 RAM BIST Register bit definitions
 */
#घोषणा RAM_TEST_MODE         0x80
#घोषणा PRE_TEST_MODE         0x40
#घोषणा NORMAL_MODE           0x00
#घोषणा RAM_TEST_DONE         0x10
#घोषणा RAM_TEST_STATUS       0x0F
#घोषणा  RAM_TEST_HOST_ERROR   0x08
#घोषणा  RAM_TEST_INTRAM_ERROR 0x04
#घोषणा  RAM_TEST_RISC_ERROR   0x02
#घोषणा  RAM_TEST_SCSI_ERROR   0x01
#घोषणा  RAM_TEST_SUCCESS      0x00
#घोषणा PRE_TEST_VALUE        0x05
#घोषणा NORMAL_VALUE          0x00

/*
 * ASC38C1600 Definitions
 *
 * IOPB_PCI_INT_CFG Bit Field Definitions
 */

#घोषणा INTAB_LD        0x80	/* Value loaded from EEPROM Bit 11. */

/*
 * Bit 1 can be set to change the पूर्णांकerrupt क्रम the Function to operate in
 * Totem Pole mode. By शेष Bit 1 is 0 and the पूर्णांकerrupt operates in
 * Open Drain mode. Both functions of the ASC38C1600 must be set to the same
 * mode, otherwise the operating mode is undefined.
 */
#घोषणा TOTEMPOLE       0x02

/*
 * Bit 0 can be used to change the Int Pin क्रम the Function. The value is
 * 0 by शेष क्रम both Functions with Function 0 using INT A and Function
 * B using INT B. For Function 0 अगर set, INT B is used. For Function 1 अगर set,
 * INT A is used.
 *
 * EEPROM Word 0 Bit 11 क्रम each Function may change the initial Int Pin
 * value specअगरied in the PCI Configuration Space.
 */
#घोषणा INTAB           0x01

/*
 * Adv Library Status Definitions
 */
#घोषणा ADV_TRUE        1
#घोषणा ADV_FALSE       0
#घोषणा ADV_SUCCESS     1
#घोषणा ADV_BUSY        0
#घोषणा ADV_ERROR       (-1)

/*
 * ADV_DVC_VAR 'warn_code' values
 */
#घोषणा ASC_WARN_BUSRESET_ERROR         0x0001	/* SCSI Bus Reset error */
#घोषणा ASC_WARN_EEPROM_CHKSUM          0x0002	/* EEP check sum error */
#घोषणा ASC_WARN_EEPROM_TERMINATION     0x0004	/* EEP termination bad field */
#घोषणा ASC_WARN_ERROR                  0xFFFF	/* ADV_ERROR वापस */

#घोषणा ADV_MAX_TID                     15	/* max. target identअगरier */
#घोषणा ADV_MAX_LUN                     7	/* max. logical unit number */

/*
 * Fixed locations of microcode operating variables.
 */
#घोषणा ASC_MC_CODE_BEGIN_ADDR          0x0028	/* microcode start address */
#घोषणा ASC_MC_CODE_END_ADDR            0x002A	/* microcode end address */
#घोषणा ASC_MC_CODE_CHK_SUM             0x002C	/* microcode code checksum */
#घोषणा ASC_MC_VERSION_DATE             0x0038	/* microcode version */
#घोषणा ASC_MC_VERSION_NUM              0x003A	/* microcode number */
#घोषणा ASC_MC_BIOSMEM                  0x0040	/* BIOS RISC Memory Start */
#घोषणा ASC_MC_BIOSLEN                  0x0050	/* BIOS RISC Memory Length */
#घोषणा ASC_MC_BIOS_SIGNATURE           0x0058	/* BIOS Signature 0x55AA */
#घोषणा ASC_MC_BIOS_VERSION             0x005A	/* BIOS Version (2 bytes) */
#घोषणा ASC_MC_SDTR_SPEED1              0x0090	/* SDTR Speed क्रम TID 0-3 */
#घोषणा ASC_MC_SDTR_SPEED2              0x0092	/* SDTR Speed क्रम TID 4-7 */
#घोषणा ASC_MC_SDTR_SPEED3              0x0094	/* SDTR Speed क्रम TID 8-11 */
#घोषणा ASC_MC_SDTR_SPEED4              0x0096	/* SDTR Speed क्रम TID 12-15 */
#घोषणा ASC_MC_CHIP_TYPE                0x009A
#घोषणा ASC_MC_INTRB_CODE               0x009B
#घोषणा ASC_MC_WDTR_ABLE                0x009C
#घोषणा ASC_MC_SDTR_ABLE                0x009E
#घोषणा ASC_MC_TAGQNG_ABLE              0x00A0
#घोषणा ASC_MC_DISC_ENABLE              0x00A2
#घोषणा ASC_MC_IDLE_CMD_STATUS          0x00A4
#घोषणा ASC_MC_IDLE_CMD                 0x00A6
#घोषणा ASC_MC_IDLE_CMD_PARAMETER       0x00A8
#घोषणा ASC_MC_DEFAULT_SCSI_CFG0        0x00AC
#घोषणा ASC_MC_DEFAULT_SCSI_CFG1        0x00AE
#घोषणा ASC_MC_DEFAULT_MEM_CFG          0x00B0
#घोषणा ASC_MC_DEFAULT_SEL_MASK         0x00B2
#घोषणा ASC_MC_SDTR_DONE                0x00B6
#घोषणा ASC_MC_NUMBER_OF_QUEUED_CMD     0x00C0
#घोषणा ASC_MC_NUMBER_OF_MAX_CMD        0x00D0
#घोषणा ASC_MC_DEVICE_HSHK_CFG_TABLE    0x0100
#घोषणा ASC_MC_CONTROL_FLAG             0x0122	/* Microcode control flag. */
#घोषणा ASC_MC_WDTR_DONE                0x0124
#घोषणा ASC_MC_CAM_MODE_MASK            0x015E	/* CAM mode TID biपंचांगask. */
#घोषणा ASC_MC_ICQ                      0x0160
#घोषणा ASC_MC_IRQ                      0x0164
#घोषणा ASC_MC_PPR_ABLE                 0x017A

/*
 * BIOS LRAM variable असलolute offsets.
 */
#घोषणा BIOS_CODESEG    0x54
#घोषणा BIOS_CODELEN    0x56
#घोषणा BIOS_SIGNATURE  0x58
#घोषणा BIOS_VERSION    0x5A

/*
 * Microcode Control Flags
 *
 * Flags set by the Adv Library in RISC variable 'control_flag' (0x122)
 * and handled by the microcode.
 */
#घोषणा CONTROL_FLAG_IGNORE_PERR        0x0001	/* Ignore DMA Parity Errors */
#घोषणा CONTROL_FLAG_ENABLE_AIPP        0x0002	/* Enabled AIPP checking. */

/*
 * ASC_MC_DEVICE_HSHK_CFG_TABLE microcode table or HSHK_CFG रेजिस्टर क्रमmat
 */
#घोषणा HSHK_CFG_WIDE_XFR       0x8000
#घोषणा HSHK_CFG_RATE           0x0F00
#घोषणा HSHK_CFG_OFFSET         0x001F

#घोषणा ASC_DEF_MAX_HOST_QNG    0xFD	/* Max. number of host commands (253) */
#घोषणा ASC_DEF_MIN_HOST_QNG    0x10	/* Min. number of host commands (16) */
#घोषणा ASC_DEF_MAX_DVC_QNG     0x3F	/* Max. number commands per device (63) */
#घोषणा ASC_DEF_MIN_DVC_QNG     0x04	/* Min. number commands per device (4) */

#घोषणा ASC_QC_DATA_CHECK  0x01	/* Require ASC_QC_DATA_OUT set or clear. */
#घोषणा ASC_QC_DATA_OUT    0x02	/* Data out DMA transfer. */
#घोषणा ASC_QC_START_MOTOR 0x04	/* Send स्वतः-start motor beक्रमe request. */
#घोषणा ASC_QC_NO_OVERRUN  0x08	/* Don't report overrun. */
#घोषणा ASC_QC_FREEZE_TIDQ 0x10	/* Freeze TID queue after request. XXX TBD */

#घोषणा ASC_QSC_NO_DISC     0x01	/* Don't allow disconnect क्रम request. */
#घोषणा ASC_QSC_NO_TAGMSG   0x02	/* Don't allow tag queuing क्रम request. */
#घोषणा ASC_QSC_NO_SYNC     0x04	/* Don't use Synch. transfer on request. */
#घोषणा ASC_QSC_NO_WIDE     0x08	/* Don't use Wide transfer on request. */
#घोषणा ASC_QSC_REDO_DTR    0x10	/* Renegotiate WDTR/SDTR beक्रमe request. */
/*
 * Note: If a Tag Message is to be sent and neither ASC_QSC_HEAD_TAG or
 * ASC_QSC_ORDERED_TAG is set, then a Simple Tag Message (0x20) is used.
 */
#घोषणा ASC_QSC_HEAD_TAG    0x40	/* Use Head Tag Message (0x21). */
#घोषणा ASC_QSC_ORDERED_TAG 0x80	/* Use Ordered Tag Message (0x22). */

/*
 * All fields here are accessed by the board microcode and need to be
 * little-endian.
 */
प्रकार काष्ठा adv_carr_t अणु
	__le32 carr_va;	/* Carrier Virtual Address */
	__le32 carr_pa;	/* Carrier Physical Address */
	__le32 areq_vpa;	/* ADV_SCSI_REQ_Q Virtual or Physical Address */
	/*
	 * next_vpa [31:4]            Carrier Virtual or Physical Next Poपूर्णांकer
	 *
	 * next_vpa [3:1]             Reserved Bits
	 * next_vpa [0]               Done Flag set in Response Queue.
	 */
	__le32 next_vpa;
पूर्ण ADV_CARR_T;

/*
 * Mask used to eliminate low 4 bits of carrier 'next_vpa' field.
 */
#घोषणा ADV_NEXT_VPA_MASK       0xFFFFFFF0

#घोषणा ADV_RQ_DONE             0x00000001
#घोषणा ADV_RQ_GOOD             0x00000002
#घोषणा ADV_CQ_STOPPER          0x00000000

#घोषणा ADV_GET_CARRP(carrp) ((carrp) & ADV_NEXT_VPA_MASK)

/*
 * Each carrier is 64 bytes, and we need three additional
 * carrier क्रम icq, irq, and the termination carrier.
 */
#घोषणा ADV_CARRIER_COUNT (ASC_DEF_MAX_HOST_QNG + 3)

#घोषणा ADV_CARRIER_बफ_मानE \
	(ADV_CARRIER_COUNT * माप(ADV_CARR_T))

#घोषणा ADV_CHIP_ASC3550          0x01	/* Ultra-Wide IC */
#घोषणा ADV_CHIP_ASC38C0800       0x02	/* Ultra2-Wide/LVD IC */
#घोषणा ADV_CHIP_ASC38C1600       0x03	/* Ultra3-Wide/LVD2 IC */

/*
 * Adapter temporary configuration काष्ठाure
 *
 * This काष्ठाure can be discarded after initialization. Don't add
 * fields here needed after initialization.
 *
 * Field naming convention:
 *
 *  *_enable indicates the field enables or disables a feature. The
 *  value of the field is never reset.
 */
प्रकार काष्ठा adv_dvc_cfg अणु
	uलघु disc_enable;	/* enable disconnection */
	uअक्षर chip_version;	/* chip version */
	uअक्षर termination;	/* Term. Ctrl. bits 6-5 of SCSI_CFG1 रेजिस्टर */
	uलघु control_flag;	/* Microcode Control Flag */
	uलघु mcode_date;	/* Microcode date */
	uलघु mcode_version;	/* Microcode version */
	uलघु serial1;		/* EEPROM serial number word 1 */
	uलघु serial2;		/* EEPROM serial number word 2 */
	uलघु serial3;		/* EEPROM serial number word 3 */
पूर्ण ADV_DVC_CFG;

काष्ठा adv_dvc_var;
काष्ठा adv_scsi_req_q;

प्रकार काष्ठा adv_sg_block अणु
	uअक्षर reserved1;
	uअक्षर reserved2;
	uअक्षर reserved3;
	uअक्षर sg_cnt;		/* Valid entries in block. */
	__le32 sg_ptr;	/* Poपूर्णांकer to next sg block. */
	काष्ठा अणु
		__le32 sg_addr;	/* SG element address. */
		__le32 sg_count;	/* SG element count. */
	पूर्ण sg_list[NO_OF_SG_PER_BLOCK];
पूर्ण ADV_SG_BLOCK;

/*
 * ADV_SCSI_REQ_Q - microcode request काष्ठाure
 *
 * All fields in this काष्ठाure up to byte 60 are used by the microcode.
 * The microcode makes assumptions about the size and ordering of fields
 * in this काष्ठाure. Do not change the काष्ठाure definition here without
 * coordinating the change with the microcode.
 *
 * All fields accessed by microcode must be मुख्यtained in little_endian
 * order.
 */
प्रकार काष्ठा adv_scsi_req_q अणु
	uअक्षर cntl;		/* Ucode flags and state (ASC_MC_QC_*). */
	uअक्षर target_cmd;
	uअक्षर target_id;	/* Device target identअगरier. */
	uअक्षर target_lun;	/* Device target logical unit number. */
	__le32 data_addr;	/* Data buffer physical address. */
	__le32 data_cnt;	/* Data count. Ucode sets to residual. */
	__le32 sense_addr;
	__le32 carr_pa;
	uअक्षर mflag;
	uअक्षर sense_len;
	uअक्षर cdb_len;		/* SCSI CDB length. Must <= 16 bytes. */
	uअक्षर scsi_cntl;
	uअक्षर करोne_status;	/* Completion status. */
	uअक्षर scsi_status;	/* SCSI status byte. */
	uअक्षर host_status;	/* Ucode host status. */
	uअक्षर sg_working_ix;
	uअक्षर cdb[12];		/* SCSI CDB bytes 0-11. */
	__le32 sg_real_addr;	/* SG list physical address. */
	__le32 scsiq_rptr;
	uअक्षर cdb16[4];		/* SCSI CDB bytes 12-15. */
	__le32 scsiq_ptr;
	__le32 carr_va;
	/*
	 * End of microcode काष्ठाure - 60 bytes. The rest of the काष्ठाure
	 * is used by the Adv Library and ignored by the microcode.
	 */
	u32 srb_tag;
	ADV_SG_BLOCK *sg_list_ptr;	/* SG list भव address. */
पूर्ण ADV_SCSI_REQ_Q;

/*
 * The following two काष्ठाures are used to process Wide Board requests.
 *
 * The ADV_SCSI_REQ_Q काष्ठाure in adv_req_t is passed to the Adv Library
 * and microcode with the ADV_SCSI_REQ_Q field 'srb_tag' set to the
 * SCSI request tag. The adv_req_t काष्ठाure 'cmndp' field in turn poपूर्णांकs
 * to the Mid-Level SCSI request काष्ठाure.
 *
 * Zero or more ADV_SG_BLOCK are used with each ADV_SCSI_REQ_Q. Each
 * ADV_SG_BLOCK काष्ठाure holds 15 scatter-gather elements. Under Linux
 * up to 255 scatter-gather elements may be used per request or
 * ADV_SCSI_REQ_Q.
 *
 * Both काष्ठाures must be 32 byte aligned.
 */
प्रकार काष्ठा adv_sgblk अणु
	ADV_SG_BLOCK sg_block;	/* Sgblock काष्ठाure. */
	dma_addr_t sg_addr;	/* Physical address */
	काष्ठा adv_sgblk *next_sgblkp;	/* Next scatter-gather काष्ठाure. */
पूर्ण adv_sgblk_t;

प्रकार काष्ठा adv_req अणु
	ADV_SCSI_REQ_Q scsi_req_q;	/* Adv Library request काष्ठाure. */
	uअक्षर align[24];	/* Request काष्ठाure padding. */
	काष्ठा scsi_cmnd *cmndp;	/* Mid-Level SCSI command poपूर्णांकer. */
	dma_addr_t req_addr;
	adv_sgblk_t *sgblkp;	/* Adv Library scatter-gather poपूर्णांकer. */
पूर्ण adv_req_t __aligned(32);

/*
 * Adapter operation variable काष्ठाure.
 *
 * One काष्ठाure is required per host adapter.
 *
 * Field naming convention:
 *
 *  *_able indicates both whether a feature should be enabled or disabled
 *  and whether a device is capable of the feature. At initialization
 *  this field may be set, but later अगर a device is found to be incapable
 *  of the feature, the field is cleared.
 */
प्रकार काष्ठा adv_dvc_var अणु
	AdvPortAddr iop_base;	/* I/O port address */
	uलघु err_code;	/* fatal error code */
	uलघु bios_ctrl;	/* BIOS control word, EEPROM word 12 */
	uलघु wdtr_able;	/* try WDTR क्रम a device */
	uलघु sdtr_able;	/* try SDTR क्रम a device */
	uलघु ultra_able;	/* try SDTR Ultra speed क्रम a device */
	uलघु sdtr_speed1;	/* EEPROM SDTR Speed क्रम TID 0-3   */
	uलघु sdtr_speed2;	/* EEPROM SDTR Speed क्रम TID 4-7   */
	uलघु sdtr_speed3;	/* EEPROM SDTR Speed क्रम TID 8-11  */
	uलघु sdtr_speed4;	/* EEPROM SDTR Speed क्रम TID 12-15 */
	uलघु tagqng_able;	/* try tagged queuing with a device */
	uलघु ppr_able;	/* PPR message capable per TID biपंचांगask. */
	uअक्षर max_dvc_qng;	/* maximum number of tagged commands per device */
	uलघु start_motor;	/* start motor command allowed */
	uअक्षर scsi_reset_रुको;	/* delay in seconds after scsi bus reset */
	uअक्षर chip_no;		/* should be asचिन्हित by caller */
	uअक्षर max_host_qng;	/* maximum number of Q'ed command allowed */
	uलघु no_scam;		/* scam_tolerant of EEPROM */
	काष्ठा asc_board *drv_ptr;	/* driver poपूर्णांकer to निजी काष्ठाure */
	uअक्षर chip_scsi_id;	/* chip SCSI target ID */
	uअक्षर chip_type;
	uअक्षर bist_err_code;
	ADV_CARR_T *carrier;
	ADV_CARR_T *carr_मुक्तlist;	/* Carrier मुक्त list. */
	dma_addr_t carrier_addr;
	ADV_CARR_T *icq_sp;	/* Initiator command queue stopper poपूर्णांकer. */
	ADV_CARR_T *irq_sp;	/* Initiator response queue stopper poपूर्णांकer. */
	uलघु carr_pending_cnt;	/* Count of pending carriers. */
	/*
	 * Note: The following fields will not be used after initialization. The
	 * driver may discard the buffer after initialization is करोne.
	 */
	ADV_DVC_CFG *cfg;	/* temporary configuration काष्ठाure  */
पूर्ण ADV_DVC_VAR;

/*
 * Microcode idle loop commands
 */
#घोषणा IDLE_CMD_COMPLETED           0
#घोषणा IDLE_CMD_STOP_CHIP           0x0001
#घोषणा IDLE_CMD_STOP_CHIP_SEND_INT  0x0002
#घोषणा IDLE_CMD_SEND_INT            0x0004
#घोषणा IDLE_CMD_ABORT               0x0008
#घोषणा IDLE_CMD_DEVICE_RESET        0x0010
#घोषणा IDLE_CMD_SCSI_RESET_START    0x0020	/* Assert SCSI Bus Reset */
#घोषणा IDLE_CMD_SCSI_RESET_END      0x0040	/* Deनिश्चित SCSI Bus Reset */
#घोषणा IDLE_CMD_SCSIREQ             0x0080

#घोषणा IDLE_CMD_STATUS_SUCCESS      0x0001
#घोषणा IDLE_CMD_STATUS_FAILURE      0x0002

/*
 * AdvSendIdleCmd() flag definitions.
 */
#घोषणा ADV_NOWAIT     0x01

/*
 * Wait loop समय out values.
 */
#घोषणा SCSI_WAIT_100_MSEC           100UL	/* 100 milliseconds */
#घोषणा SCSI_US_PER_MSEC             1000	/* microseconds per millisecond */
#घोषणा SCSI_MAX_RETRY               10	/* retry count */

#घोषणा ADV_ASYNC_RDMA_FAILURE          0x01	/* Fatal RDMA failure. */
#घोषणा ADV_ASYNC_SCSI_BUS_RESET_DET    0x02	/* Detected SCSI Bus Reset. */
#घोषणा ADV_ASYNC_CARRIER_READY_FAILURE 0x03	/* Carrier Ready failure. */
#घोषणा ADV_RDMA_IN_CARR_AND_Q_INVALID  0x04	/* RDMAed-in data invalid. */

#घोषणा ADV_HOST_SCSI_BUS_RESET      0x80	/* Host Initiated SCSI Bus Reset. */

/* Read byte from a रेजिस्टर. */
#घोषणा AdvReadByteRegister(iop_base, reg_off) \
     (ADV_MEM_READB((iop_base) + (reg_off)))

/* Write byte to a रेजिस्टर. */
#घोषणा AdvWriteByteRegister(iop_base, reg_off, byte) \
     (ADV_MEM_WRITEB((iop_base) + (reg_off), (byte)))

/* Read word (2 bytes) from a रेजिस्टर. */
#घोषणा AdvReadWordRegister(iop_base, reg_off) \
     (ADV_MEM_READW((iop_base) + (reg_off)))

/* Write word (2 bytes) to a रेजिस्टर. */
#घोषणा AdvWriteWordRegister(iop_base, reg_off, word) \
     (ADV_MEM_WRITEW((iop_base) + (reg_off), (word)))

/* Write dword (4 bytes) to a रेजिस्टर. */
#घोषणा AdvWriteDWordRegister(iop_base, reg_off, dword) \
     (ADV_MEM_WRITEDW((iop_base) + (reg_off), (dword)))

/* Read byte from LRAM. */
#घोषणा AdvReadByteLram(iop_base, addr, byte) \
करो अणु \
    ADV_MEM_WRITEW((iop_base) + IOPW_RAM_ADDR, (addr)); \
    (byte) = ADV_MEM_READB((iop_base) + IOPB_RAM_DATA); \
पूर्ण जबतक (0)

/* Write byte to LRAM. */
#घोषणा AdvWriteByteLram(iop_base, addr, byte) \
    (ADV_MEM_WRITEW((iop_base) + IOPW_RAM_ADDR, (addr)), \
     ADV_MEM_WRITEB((iop_base) + IOPB_RAM_DATA, (byte)))

/* Read word (2 bytes) from LRAM. */
#घोषणा AdvReadWordLram(iop_base, addr, word) \
करो अणु \
    ADV_MEM_WRITEW((iop_base) + IOPW_RAM_ADDR, (addr)); \
    (word) = (ADV_MEM_READW((iop_base) + IOPW_RAM_DATA)); \
पूर्ण जबतक (0)

/* Write word (2 bytes) to LRAM. */
#घोषणा AdvWriteWordLram(iop_base, addr, word) \
    (ADV_MEM_WRITEW((iop_base) + IOPW_RAM_ADDR, (addr)), \
     ADV_MEM_WRITEW((iop_base) + IOPW_RAM_DATA, (word)))

/* Write little-endian द्विगुन word (4 bytes) to LRAM */
/* Because of unspecअगरied C language ordering करोn't use स्वतः-increment. */
#घोषणा AdvWriteDWordLramNoSwap(iop_base, addr, dword) \
    ((ADV_MEM_WRITEW((iop_base) + IOPW_RAM_ADDR, (addr)), \
      ADV_MEM_WRITEW((iop_base) + IOPW_RAM_DATA, \
                     cpu_to_le16((uलघु) ((dword) & 0xFFFF)))), \
     (ADV_MEM_WRITEW((iop_base) + IOPW_RAM_ADDR, (addr) + 2), \
      ADV_MEM_WRITEW((iop_base) + IOPW_RAM_DATA, \
                     cpu_to_le16((uलघु) ((dword >> 16) & 0xFFFF)))))

/* Read word (2 bytes) from LRAM assuming that the address is alपढ़ोy set. */
#घोषणा AdvReadWordAutoIncLram(iop_base) \
     (ADV_MEM_READW((iop_base) + IOPW_RAM_DATA))

/* Write word (2 bytes) to LRAM assuming that the address is alपढ़ोy set. */
#घोषणा AdvWriteWordAutoIncLram(iop_base, word) \
     (ADV_MEM_WRITEW((iop_base) + IOPW_RAM_DATA, (word)))

/*
 * Define macro to check क्रम Conकरोr signature.
 *
 * Evaluate to ADV_TRUE अगर a Conकरोr chip is found the specअगरied port
 * address 'iop_base'. Otherwise evalue to ADV_FALSE.
 */
#घोषणा AdvFindSignature(iop_base) \
    (((AdvReadByteRegister((iop_base), IOPB_CHIP_ID_1) == \
    ADV_CHIP_ID_BYTE) && \
     (AdvReadWordRegister((iop_base), IOPW_CHIP_ID_0) == \
    ADV_CHIP_ID_WORD)) ?  ADV_TRUE : ADV_FALSE)

/*
 * Define macro to Return the version number of the chip at 'iop_base'.
 *
 * The second parameter 'bus_type' is currently unused.
 */
#घोषणा AdvGetChipVersion(iop_base, bus_type) \
    AdvReadByteRegister((iop_base), IOPB_CHIP_TYPE_REV)

/*
 * Abort an SRB in the chip's RISC Memory. The 'srb_tag' argument must
 * match the ADV_SCSI_REQ_Q 'srb_tag' field.
 *
 * If the request has not yet been sent to the device it will simply be
 * पातed from RISC memory. If the request is disconnected it will be
 * पातed on reselection by sending an Abort Message to the target ID.
 *
 * Return value:
 *      ADV_TRUE(1) - Queue was successfully पातed.
 *      ADV_FALSE(0) - Queue was not found on the active queue list.
 */
#घोषणा AdvAbortQueue(asc_dvc, srb_tag) \
     AdvSendIdleCmd((asc_dvc), (uलघु) IDLE_CMD_ABORT, \
		    (ADV_DCNT) (srb_tag))

/*
 * Send a Bus Device Reset Message to the specअगरied target ID.
 *
 * All outstanding commands will be purged अगर sending the
 * Bus Device Reset Message is successful.
 *
 * Return Value:
 *      ADV_TRUE(1) - All requests on the target are purged.
 *      ADV_FALSE(0) - Couldn't issue Bus Device Reset Message; Requests
 *                     are not purged.
 */
#घोषणा AdvResetDevice(asc_dvc, target_id) \
     AdvSendIdleCmd((asc_dvc), (uलघु) IDLE_CMD_DEVICE_RESET,	\
		    (ADV_DCNT) (target_id))

/*
 * SCSI Wide Type definition.
 */
#घोषणा ADV_SCSI_BIT_ID_TYPE   uलघु

/*
 * AdvInitScsiTarget() 'cntl_flag' options.
 */
#घोषणा ADV_SCAN_LUN           0x01
#घोषणा ADV_CAPINFO_NOLUN      0x02

/*
 * Convert target id to target id bit mask.
 */
#घोषणा ADV_TID_TO_TIDMASK(tid)   (0x01 << ((tid) & ADV_MAX_TID))

/*
 * ADV_SCSI_REQ_Q 'done_status' and 'host_status' वापस values.
 */

#घोषणा QD_NO_STATUS         0x00	/* Request not completed yet. */
#घोषणा QD_NO_ERROR          0x01
#घोषणा QD_ABORTED_BY_HOST   0x02
#घोषणा QD_WITH_ERROR        0x04

#घोषणा QHSTA_NO_ERROR              0x00
#घोषणा QHSTA_M_SEL_TIMEOUT         0x11
#घोषणा QHSTA_M_DATA_OVER_RUN       0x12
#घोषणा QHSTA_M_UNEXPECTED_BUS_FREE 0x13
#घोषणा QHSTA_M_QUEUE_ABORTED       0x15
#घोषणा QHSTA_M_SXFR_SDMA_ERR       0x16	/* SXFR_STATUS SCSI DMA Error */
#घोषणा QHSTA_M_SXFR_SXFR_PERR      0x17	/* SXFR_STATUS SCSI Bus Parity Error */
#घोषणा QHSTA_M_RDMA_PERR           0x18	/* RISC PCI DMA parity error */
#घोषणा QHSTA_M_SXFR_OFF_UFLW       0x19	/* SXFR_STATUS Offset Underflow */
#घोषणा QHSTA_M_SXFR_OFF_OFLW       0x20	/* SXFR_STATUS Offset Overflow */
#घोषणा QHSTA_M_SXFR_WD_TMO         0x21	/* SXFR_STATUS Watchकरोg Timeout */
#घोषणा QHSTA_M_SXFR_DESELECTED     0x22	/* SXFR_STATUS Deselected */
/* Note: QHSTA_M_SXFR_XFR_OFLW is identical to QHSTA_M_DATA_OVER_RUN. */
#घोषणा QHSTA_M_SXFR_XFR_OFLW       0x12	/* SXFR_STATUS Transfer Overflow */
#घोषणा QHSTA_M_SXFR_XFR_PH_ERR     0x24	/* SXFR_STATUS Transfer Phase Error */
#घोषणा QHSTA_M_SXFR_UNKNOWN_ERROR  0x25	/* SXFR_STATUS Unknown Error */
#घोषणा QHSTA_M_SCSI_BUS_RESET      0x30	/* Request पातed from SBR */
#घोषणा QHSTA_M_SCSI_BUS_RESET_UNSOL 0x31	/* Request पातed from unsol. SBR */
#घोषणा QHSTA_M_BUS_DEVICE_RESET    0x32	/* Request पातed from BDR */
#घोषणा QHSTA_M_सूचीECTION_ERR       0x35	/* Data Phase mismatch */
#घोषणा QHSTA_M_सूचीECTION_ERR_HUNG  0x36	/* Data Phase mismatch and bus hang */
#घोषणा QHSTA_M_WTM_TIMEOUT         0x41
#घोषणा QHSTA_M_BAD_CMPL_STATUS_IN  0x42
#घोषणा QHSTA_M_NO_AUTO_REQ_SENSE   0x43
#घोषणा QHSTA_M_AUTO_REQ_SENSE_FAIL 0x44
#घोषणा QHSTA_M_INVALID_DEVICE      0x45	/* Bad target ID */
#घोषणा QHSTA_M_FROZEN_TIDQ         0x46	/* TID Queue frozen. */
#घोषणा QHSTA_M_SGBACKUP_ERROR      0x47	/* Scatter-Gather backup error */

/* Return the address that is aligned at the next द्विगुनword >= to 'addr'. */
#घोषणा ADV_32BALIGN(addr)     (((uदीर्घ) (addr) + 0x1F) & ~0x1F)

/*
 * Total contiguous memory needed क्रम driver SG blocks.
 *
 * ADV_MAX_SG_LIST must be defined by a driver. It is the maximum
 * number of scatter-gather elements the driver supports in a
 * single request.
 */

#घोषणा ADV_SG_LIST_MAX_BYTE_SIZE \
         (माप(ADV_SG_BLOCK) * \
          ((ADV_MAX_SG_LIST + (NO_OF_SG_PER_BLOCK - 1))/NO_OF_SG_PER_BLOCK))

/* काष्ठा asc_board flags */
#घोषणा ASC_IS_WIDE_BOARD       0x04	/* AdvanSys Wide Board */

#घोषणा ASC_NARROW_BOARD(boardp) (((boardp)->flags & ASC_IS_WIDE_BOARD) == 0)

#घोषणा NO_ISA_DMA              0xff	/* No ISA DMA Channel Used */

#घोषणा ASC_INFO_SIZE           128	/* advansys_info() line size */

/* Asc Library वापस codes */
#घोषणा ASC_TRUE        1
#घोषणा ASC_FALSE       0
#घोषणा ASC_NOERROR     1
#घोषणा ASC_BUSY        0
#घोषणा ASC_ERROR       (-1)

#घोषणा ASC_STATS(shost, counter) ASC_STATS_ADD(shost, counter, 1)
#अगर_अघोषित ADVANSYS_STATS
#घोषणा ASC_STATS_ADD(shost, counter, count)
#अन्यथा /* ADVANSYS_STATS */
#घोषणा ASC_STATS_ADD(shost, counter, count) \
	(((काष्ठा asc_board *) shost_priv(shost))->asc_stats.counter += (count))
#पूर्ण_अगर /* ADVANSYS_STATS */

/* If the result wraps when calculating tenths, वापस 0. */
#घोषणा ASC_TENTHS(num, den) \
    (((10 * ((num)/(den))) > (((num) * 10)/(den))) ? \
    0 : ((((num) * 10)/(den)) - (10 * ((num)/(den)))))

/*
 * Display a message to the console.
 */
#घोषणा ASC_PRINT(s) \
    अणु \
        prपूर्णांकk("advansys: "); \
        prपूर्णांकk(s); \
    पूर्ण

#घोषणा ASC_PRINT1(s, a1) \
    अणु \
        prपूर्णांकk("advansys: "); \
        prपूर्णांकk((s), (a1)); \
    पूर्ण

#घोषणा ASC_PRINT2(s, a1, a2) \
    अणु \
        prपूर्णांकk("advansys: "); \
        prपूर्णांकk((s), (a1), (a2)); \
    पूर्ण

#घोषणा ASC_PRINT3(s, a1, a2, a3) \
    अणु \
        prपूर्णांकk("advansys: "); \
        prपूर्णांकk((s), (a1), (a2), (a3)); \
    पूर्ण

#घोषणा ASC_PRINT4(s, a1, a2, a3, a4) \
    अणु \
        prपूर्णांकk("advansys: "); \
        prपूर्णांकk((s), (a1), (a2), (a3), (a4)); \
    पूर्ण

#अगर_अघोषित ADVANSYS_DEBUG

#घोषणा ASC_DBG(lvl, s...)
#घोषणा ASC_DBG_PRT_SCSI_HOST(lvl, s)
#घोषणा ASC_DBG_PRT_ASC_SCSI_Q(lvl, scsiqp)
#घोषणा ASC_DBG_PRT_ADV_SCSI_REQ_Q(lvl, scsiqp)
#घोषणा ASC_DBG_PRT_ASC_QDONE_INFO(lvl, qकरोne)
#घोषणा ADV_DBG_PRT_ADV_SCSI_REQ_Q(lvl, scsiqp)
#घोषणा ASC_DBG_PRT_HEX(lvl, name, start, length)
#घोषणा ASC_DBG_PRT_CDB(lvl, cdb, len)
#घोषणा ASC_DBG_PRT_SENSE(lvl, sense, len)
#घोषणा ASC_DBG_PRT_INQUIRY(lvl, inq, len)

#अन्यथा /* ADVANSYS_DEBUG */

/*
 * Debugging Message Levels:
 * 0: Errors Only
 * 1: High-Level Tracing
 * 2-N: Verbose Tracing
 */

#घोषणा ASC_DBG(lvl, क्रमmat, arg...) अणु					\
	अगर (asc_dbglvl >= (lvl))					\
		prपूर्णांकk(KERN_DEBUG "%s: %s: " क्रमmat, DRV_NAME,		\
			__func__ , ## arg);				\
पूर्ण

#घोषणा ASC_DBG_PRT_SCSI_HOST(lvl, s) \
    अणु \
        अगर (asc_dbglvl >= (lvl)) अणु \
            asc_prt_scsi_host(s); \
        पूर्ण \
    पूर्ण

#घोषणा ASC_DBG_PRT_ASC_SCSI_Q(lvl, scsiqp) \
    अणु \
        अगर (asc_dbglvl >= (lvl)) अणु \
            asc_prt_asc_scsi_q(scsiqp); \
        पूर्ण \
    पूर्ण

#घोषणा ASC_DBG_PRT_ASC_QDONE_INFO(lvl, qकरोne) \
    अणु \
        अगर (asc_dbglvl >= (lvl)) अणु \
            asc_prt_asc_qकरोne_info(qकरोne); \
        पूर्ण \
    पूर्ण

#घोषणा ASC_DBG_PRT_ADV_SCSI_REQ_Q(lvl, scsiqp) \
    अणु \
        अगर (asc_dbglvl >= (lvl)) अणु \
            asc_prt_adv_scsi_req_q(scsiqp); \
        पूर्ण \
    पूर्ण

#घोषणा ASC_DBG_PRT_HEX(lvl, name, start, length) \
    अणु \
        अगर (asc_dbglvl >= (lvl)) अणु \
            asc_prt_hex((name), (start), (length)); \
        पूर्ण \
    पूर्ण

#घोषणा ASC_DBG_PRT_CDB(lvl, cdb, len) \
        ASC_DBG_PRT_HEX((lvl), "CDB", (uअक्षर *) (cdb), (len));

#घोषणा ASC_DBG_PRT_SENSE(lvl, sense, len) \
        ASC_DBG_PRT_HEX((lvl), "SENSE", (uअक्षर *) (sense), (len));

#घोषणा ASC_DBG_PRT_INQUIRY(lvl, inq, len) \
        ASC_DBG_PRT_HEX((lvl), "INQUIRY", (uअक्षर *) (inq), (len));
#पूर्ण_अगर /* ADVANSYS_DEBUG */

#अगर_घोषित ADVANSYS_STATS

/* Per board statistics काष्ठाure */
काष्ठा asc_stats अणु
	/* Driver Entrypoपूर्णांक Statistics */
	अचिन्हित पूर्णांक queuecommand;	/* # calls to advansys_queuecommand() */
	अचिन्हित पूर्णांक reset;		/* # calls to advansys_eh_bus_reset() */
	अचिन्हित पूर्णांक biosparam;	/* # calls to advansys_biosparam() */
	अचिन्हित पूर्णांक पूर्णांकerrupt;	/* # advansys_पूर्णांकerrupt() calls */
	अचिन्हित पूर्णांक callback;	/* # calls to asc/adv_isr_callback() */
	अचिन्हित पूर्णांक करोne;		/* # calls to request's scsi_करोne function */
	अचिन्हित पूर्णांक build_error;	/* # asc/adv_build_req() ASC_ERROR वापसs. */
	अचिन्हित पूर्णांक adv_build_noreq;	/* # adv_build_req() adv_req_t alloc. fail. */
	अचिन्हित पूर्णांक adv_build_nosg;	/* # adv_build_req() adv_sgblk_t alloc. fail. */
	/* AscExeScsiQueue()/AdvExeScsiQueue() Statistics */
	अचिन्हित पूर्णांक exe_noerror;	/* # ASC_NOERROR वापसs. */
	अचिन्हित पूर्णांक exe_busy;	/* # ASC_BUSY वापसs. */
	अचिन्हित पूर्णांक exe_error;	/* # ASC_ERROR वापसs. */
	अचिन्हित पूर्णांक exe_unknown;	/* # unknown वापसs. */
	/* Data Transfer Statistics */
	अचिन्हित पूर्णांक xfer_cnt;	/* # I/O requests received */
	अचिन्हित पूर्णांक xfer_elem;	/* # scatter-gather elements */
	अचिन्हित पूर्णांक xfer_sect;	/* # 512-byte blocks */
पूर्ण;
#पूर्ण_अगर /* ADVANSYS_STATS */

/*
 * Structure allocated क्रम each board.
 *
 * This काष्ठाure is allocated by scsi_host_alloc() at the end
 * of the 'Scsi_Host' structure starting at the 'hostdata'
 * field. It is guaranteed to be allocated from DMA-able memory.
 */
काष्ठा asc_board अणु
	काष्ठा device *dev;
	काष्ठा Scsi_Host *shost;
	uपूर्णांक flags;		/* Board flags */
	अचिन्हित पूर्णांक irq;
	जोड़ अणु
		ASC_DVC_VAR asc_dvc_var;	/* Narrow board */
		ADV_DVC_VAR adv_dvc_var;	/* Wide board */
	पूर्ण dvc_var;
	जोड़ अणु
		ASC_DVC_CFG asc_dvc_cfg;	/* Narrow board */
		ADV_DVC_CFG adv_dvc_cfg;	/* Wide board */
	पूर्ण dvc_cfg;
	uलघु asc_n_io_port;	/* Number I/O ports. */
	ADV_SCSI_BIT_ID_TYPE init_tidmask;	/* Target init./valid mask */
	uलघु reqcnt[ADV_MAX_TID + 1];	/* Starvation request count */
	ADV_SCSI_BIT_ID_TYPE queue_full;	/* Queue full mask */
	uलघु queue_full_cnt[ADV_MAX_TID + 1];	/* Queue full count */
	जोड़ अणु
		ASCEEP_CONFIG asc_eep;	/* Narrow EEPROM config. */
		ADVEEP_3550_CONFIG adv_3550_eep;	/* 3550 EEPROM config. */
		ADVEEP_38C0800_CONFIG adv_38C0800_eep;	/* 38C0800 EEPROM config. */
		ADVEEP_38C1600_CONFIG adv_38C1600_eep;	/* 38C1600 EEPROM config. */
	पूर्ण eep_config;
	/* /proc/scsi/advansys/[0...] */
#अगर_घोषित ADVANSYS_STATS
	काष्ठा asc_stats asc_stats;	/* Board statistics */
#पूर्ण_अगर				/* ADVANSYS_STATS */
	/*
	 * The following fields are used only क्रम Narrow Boards.
	 */
	uअक्षर sdtr_data[ASC_MAX_TID + 1];	/* SDTR inक्रमmation */
	/*
	 * The following fields are used only क्रम Wide Boards.
	 */
	व्योम __iomem *ioremap_addr;	/* I/O Memory remap address. */
	uलघु ioport;		/* I/O Port address. */
	adv_req_t *adv_reqp;	/* Request काष्ठाures. */
	dma_addr_t adv_reqp_addr;
	माप_प्रकार adv_reqp_size;
	काष्ठा dma_pool *adv_sgblk_pool;	/* Scatter-gather काष्ठाures. */
	uलघु bios_signature;	/* BIOS Signature. */
	uलघु bios_version;	/* BIOS Version. */
	uलघु bios_codeseg;	/* BIOS Code Segment. */
	uलघु bios_codelen;	/* BIOS Code Segment Length. */
पूर्ण;

#घोषणा asc_dvc_to_board(asc_dvc) container_of(asc_dvc, काष्ठा asc_board, \
							dvc_var.asc_dvc_var)
#घोषणा adv_dvc_to_board(adv_dvc) container_of(adv_dvc, काष्ठा asc_board, \
							dvc_var.adv_dvc_var)
#घोषणा adv_dvc_to_pdev(adv_dvc) to_pci_dev(adv_dvc_to_board(adv_dvc)->dev)

#अगर_घोषित ADVANSYS_DEBUG
अटल पूर्णांक asc_dbglvl = 3;

/*
 * asc_prt_asc_dvc_var()
 */
अटल व्योम asc_prt_asc_dvc_var(ASC_DVC_VAR *h)
अणु
	prपूर्णांकk("ASC_DVC_VAR at addr 0x%lx\n", (uदीर्घ)h);

	prपूर्णांकk(" iop_base 0x%x, err_code 0x%x, dvc_cntl 0x%x, bug_fix_cntl "
	       "%d,\n", h->iop_base, h->err_code, h->dvc_cntl, h->bug_fix_cntl);

	prपूर्णांकk(" bus_type %d, init_sdtr 0x%x,\n", h->bus_type,
		(अचिन्हित)h->init_sdtr);

	prपूर्णांकk(" sdtr_done 0x%x, use_tagged_qng 0x%x, unit_not_ready 0x%x, "
	       "chip_no 0x%x,\n", (अचिन्हित)h->sdtr_करोne,
	       (अचिन्हित)h->use_tagged_qng, (अचिन्हित)h->unit_not_पढ़ोy,
	       (अचिन्हित)h->chip_no);

	prपूर्णांकk(" queue_full_or_busy 0x%x, start_motor 0x%x, scsi_reset_wait "
	       "%u,\n", (अचिन्हित)h->queue_full_or_busy,
	       (अचिन्हित)h->start_motor, (अचिन्हित)h->scsi_reset_रुको);

	prपूर्णांकk(" is_in_int %u, max_total_qng %u, cur_total_qng %u, "
	       "in_critical_cnt %u,\n", (अचिन्हित)h->is_in_पूर्णांक,
	       (अचिन्हित)h->max_total_qng, (अचिन्हित)h->cur_total_qng,
	       (अचिन्हित)h->in_critical_cnt);

	prपूर्णांकk(" last_q_shortage %u, init_state 0x%x, no_scam 0x%x, "
	       "pci_fix_asyn_xfer 0x%x,\n", (अचिन्हित)h->last_q_लघुage,
	       (अचिन्हित)h->init_state, (अचिन्हित)h->no_scam,
	       (अचिन्हित)h->pci_fix_asyn_xfer);

	prपूर्णांकk(" cfg 0x%lx\n", (uदीर्घ)h->cfg);
पूर्ण

/*
 * asc_prt_asc_dvc_cfg()
 */
अटल व्योम asc_prt_asc_dvc_cfg(ASC_DVC_CFG *h)
अणु
	prपूर्णांकk("ASC_DVC_CFG at addr 0x%lx\n", (uदीर्घ)h);

	prपूर्णांकk(" can_tagged_qng 0x%x, cmd_qng_enabled 0x%x,\n",
	       h->can_tagged_qng, h->cmd_qng_enabled);
	prपूर्णांकk(" disc_enable 0x%x, sdtr_enable 0x%x,\n",
	       h->disc_enable, h->sdtr_enable);

	prपूर्णांकk(" chip_scsi_id %d, chip_version %d,\n",
	       h->chip_scsi_id, h->chip_version);

	prपूर्णांकk(" mcode_date 0x%x, mcode_version %d\n",
		h->mcode_date, h->mcode_version);
पूर्ण

/*
 * asc_prt_adv_dvc_var()
 *
 * Display an ADV_DVC_VAR काष्ठाure.
 */
अटल व्योम asc_prt_adv_dvc_var(ADV_DVC_VAR *h)
अणु
	prपूर्णांकk(" ADV_DVC_VAR at addr 0x%lx\n", (uदीर्घ)h);

	prपूर्णांकk("  iop_base 0x%lx, err_code 0x%x, ultra_able 0x%x\n",
	       (uदीर्घ)h->iop_base, h->err_code, (अचिन्हित)h->ultra_able);

	prपूर्णांकk("  sdtr_able 0x%x, wdtr_able 0x%x\n",
	       (अचिन्हित)h->sdtr_able, (अचिन्हित)h->wdtr_able);

	prपूर्णांकk("  start_motor 0x%x, scsi_reset_wait 0x%x\n",
	       (अचिन्हित)h->start_motor, (अचिन्हित)h->scsi_reset_रुको);

	prपूर्णांकk("  max_host_qng %u, max_dvc_qng %u, carr_freelist 0x%p\n",
	       (अचिन्हित)h->max_host_qng, (अचिन्हित)h->max_dvc_qng,
	       h->carr_मुक्तlist);

	prपूर्णांकk("  icq_sp 0x%p, irq_sp 0x%p\n", h->icq_sp, h->irq_sp);

	prपूर्णांकk("  no_scam 0x%x, tagqng_able 0x%x\n",
	       (अचिन्हित)h->no_scam, (अचिन्हित)h->tagqng_able);

	prपूर्णांकk("  chip_scsi_id 0x%x, cfg 0x%lx\n",
	       (अचिन्हित)h->chip_scsi_id, (uदीर्घ)h->cfg);
पूर्ण

/*
 * asc_prt_adv_dvc_cfg()
 *
 * Display an ADV_DVC_CFG काष्ठाure.
 */
अटल व्योम asc_prt_adv_dvc_cfg(ADV_DVC_CFG *h)
अणु
	prपूर्णांकk(" ADV_DVC_CFG at addr 0x%lx\n", (uदीर्घ)h);

	prपूर्णांकk("  disc_enable 0x%x, termination 0x%x\n",
	       h->disc_enable, h->termination);

	prपूर्णांकk("  chip_version 0x%x, mcode_date 0x%x\n",
	       h->chip_version, h->mcode_date);

	prपूर्णांकk("  mcode_version 0x%x, control_flag 0x%x\n",
	       h->mcode_version, h->control_flag);
पूर्ण

/*
 * asc_prt_scsi_host()
 */
अटल व्योम asc_prt_scsi_host(काष्ठा Scsi_Host *s)
अणु
	काष्ठा asc_board *boardp = shost_priv(s);

	prपूर्णांकk("Scsi_Host at addr 0x%p, device %s\n", s, dev_name(boardp->dev));
	prपूर्णांकk(" host_busy %d, host_no %d,\n",
	       scsi_host_busy(s), s->host_no);

	prपूर्णांकk(" base 0x%lx, io_port 0x%lx, irq %d,\n",
	       (uदीर्घ)s->base, (uदीर्घ)s->io_port, boardp->irq);

	prपूर्णांकk(" dma_channel %d, this_id %d, can_queue %d,\n",
	       s->dma_channel, s->this_id, s->can_queue);

	prपूर्णांकk(" cmd_per_lun %d, sg_tablesize %d\n",
	       s->cmd_per_lun, s->sg_tablesize);

	अगर (ASC_NARROW_BOARD(boardp)) अणु
		asc_prt_asc_dvc_var(&boardp->dvc_var.asc_dvc_var);
		asc_prt_asc_dvc_cfg(&boardp->dvc_cfg.asc_dvc_cfg);
	पूर्ण अन्यथा अणु
		asc_prt_adv_dvc_var(&boardp->dvc_var.adv_dvc_var);
		asc_prt_adv_dvc_cfg(&boardp->dvc_cfg.adv_dvc_cfg);
	पूर्ण
पूर्ण

/*
 * asc_prt_hex()
 *
 * Prपूर्णांक hexadecimal output in 4 byte groupings 32 bytes
 * or 8 द्विगुन-words per line.
 */
अटल व्योम asc_prt_hex(अक्षर *f, uअक्षर *s, पूर्णांक l)
अणु
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक k;
	पूर्णांक m;

	prपूर्णांकk("%s: (%d bytes)\n", f, l);

	क्रम (i = 0; i < l; i += 32) अणु

		/* Display a maximum of 8 द्विगुन-words per line. */
		अगर ((k = (l - i) / 4) >= 8) अणु
			k = 8;
			m = 0;
		पूर्ण अन्यथा अणु
			m = (l - i) % 4;
		पूर्ण

		क्रम (j = 0; j < k; j++) अणु
			prपूर्णांकk(" %2.2X%2.2X%2.2X%2.2X",
			       (अचिन्हित)s[i + (j * 4)],
			       (अचिन्हित)s[i + (j * 4) + 1],
			       (अचिन्हित)s[i + (j * 4) + 2],
			       (अचिन्हित)s[i + (j * 4) + 3]);
		पूर्ण

		चयन (m) अणु
		हाल 0:
		शेष:
			अवरोध;
		हाल 1:
			prपूर्णांकk(" %2.2X", (अचिन्हित)s[i + (j * 4)]);
			अवरोध;
		हाल 2:
			prपूर्णांकk(" %2.2X%2.2X",
			       (अचिन्हित)s[i + (j * 4)],
			       (अचिन्हित)s[i + (j * 4) + 1]);
			अवरोध;
		हाल 3:
			prपूर्णांकk(" %2.2X%2.2X%2.2X",
			       (अचिन्हित)s[i + (j * 4) + 1],
			       (अचिन्हित)s[i + (j * 4) + 2],
			       (अचिन्हित)s[i + (j * 4) + 3]);
			अवरोध;
		पूर्ण

		prपूर्णांकk("\n");
	पूर्ण
पूर्ण

/*
 * asc_prt_asc_scsi_q()
 */
अटल व्योम asc_prt_asc_scsi_q(ASC_SCSI_Q *q)
अणु
	ASC_SG_HEAD *sgp;
	पूर्णांक i;

	prपूर्णांकk("ASC_SCSI_Q at addr 0x%lx\n", (uदीर्घ)q);

	prपूर्णांकk
	    (" target_ix 0x%x, target_lun %u, srb_tag 0x%x, tag_code 0x%x,\n",
	     q->q2.target_ix, q->q1.target_lun, q->q2.srb_tag,
	     q->q2.tag_code);

	prपूर्णांकk
	    (" data_addr 0x%lx, data_cnt %lu, sense_addr 0x%lx, sense_len %u,\n",
	     (uदीर्घ)le32_to_cpu(q->q1.data_addr),
	     (uदीर्घ)le32_to_cpu(q->q1.data_cnt),
	     (uदीर्घ)le32_to_cpu(q->q1.sense_addr), q->q1.sense_len);

	prपूर्णांकk(" cdbptr 0x%lx, cdb_len %u, sg_head 0x%lx, sg_queue_cnt %u\n",
	       (uदीर्घ)q->cdbptr, q->q2.cdb_len,
	       (uदीर्घ)q->sg_head, q->q1.sg_queue_cnt);

	अगर (q->sg_head) अणु
		sgp = q->sg_head;
		prपूर्णांकk("ASC_SG_HEAD at addr 0x%lx\n", (uदीर्घ)sgp);
		prपूर्णांकk(" entry_cnt %u, queue_cnt %u\n", sgp->entry_cnt,
		       sgp->queue_cnt);
		क्रम (i = 0; i < sgp->entry_cnt; i++) अणु
			prपूर्णांकk(" [%u]: addr 0x%lx, bytes %lu\n",
			       i, (uदीर्घ)le32_to_cpu(sgp->sg_list[i].addr),
			       (uदीर्घ)le32_to_cpu(sgp->sg_list[i].bytes));
		पूर्ण

	पूर्ण
पूर्ण

/*
 * asc_prt_asc_qकरोne_info()
 */
अटल व्योम asc_prt_asc_qकरोne_info(ASC_QDONE_INFO *q)
अणु
	prपूर्णांकk("ASC_QDONE_INFO at addr 0x%lx\n", (uदीर्घ)q);
	prपूर्णांकk(" srb_tag 0x%x, target_ix %u, cdb_len %u, tag_code %u,\n",
	       q->d2.srb_tag, q->d2.target_ix, q->d2.cdb_len,
	       q->d2.tag_code);
	prपूर्णांकk
	    (" done_stat 0x%x, host_stat 0x%x, scsi_stat 0x%x, scsi_msg 0x%x\n",
	     q->d3.करोne_stat, q->d3.host_stat, q->d3.scsi_stat, q->d3.scsi_msg);
पूर्ण

/*
 * asc_prt_adv_sgblock()
 *
 * Display an ADV_SG_BLOCK काष्ठाure.
 */
अटल व्योम asc_prt_adv_sgblock(पूर्णांक sgblockno, ADV_SG_BLOCK *b)
अणु
	पूर्णांक i;

	prपूर्णांकk(" ADV_SG_BLOCK at addr 0x%lx (sgblockno %d)\n",
	       (uदीर्घ)b, sgblockno);
	prपूर्णांकk("  sg_cnt %u, sg_ptr 0x%x\n",
	       b->sg_cnt, (u32)le32_to_cpu(b->sg_ptr));
	BUG_ON(b->sg_cnt > NO_OF_SG_PER_BLOCK);
	अगर (b->sg_ptr != 0)
		BUG_ON(b->sg_cnt != NO_OF_SG_PER_BLOCK);
	क्रम (i = 0; i < b->sg_cnt; i++) अणु
		prपूर्णांकk("  [%u]: sg_addr 0x%x, sg_count 0x%x\n",
		       i, (u32)le32_to_cpu(b->sg_list[i].sg_addr),
		       (u32)le32_to_cpu(b->sg_list[i].sg_count));
	पूर्ण
पूर्ण

/*
 * asc_prt_adv_scsi_req_q()
 *
 * Display an ADV_SCSI_REQ_Q काष्ठाure.
 */
अटल व्योम asc_prt_adv_scsi_req_q(ADV_SCSI_REQ_Q *q)
अणु
	पूर्णांक sg_blk_cnt;
	काष्ठा adv_sg_block *sg_ptr;
	adv_sgblk_t *sgblkp;

	prपूर्णांकk("ADV_SCSI_REQ_Q at addr 0x%lx\n", (uदीर्घ)q);

	prपूर्णांकk("  target_id %u, target_lun %u, srb_tag 0x%x\n",
	       q->target_id, q->target_lun, q->srb_tag);

	prपूर्णांकk("  cntl 0x%x, data_addr 0x%lx\n",
	       q->cntl, (uदीर्घ)le32_to_cpu(q->data_addr));

	prपूर्णांकk("  data_cnt %lu, sense_addr 0x%lx, sense_len %u,\n",
	       (uदीर्घ)le32_to_cpu(q->data_cnt),
	       (uदीर्घ)le32_to_cpu(q->sense_addr), q->sense_len);

	prपूर्णांकk
	    ("  cdb_len %u, done_status 0x%x, host_status 0x%x, scsi_status 0x%x\n",
	     q->cdb_len, q->करोne_status, q->host_status, q->scsi_status);

	prपूर्णांकk("  sg_working_ix 0x%x, target_cmd %u\n",
	       q->sg_working_ix, q->target_cmd);

	prपूर्णांकk("  scsiq_rptr 0x%lx, sg_real_addr 0x%lx, sg_list_ptr 0x%lx\n",
	       (uदीर्घ)le32_to_cpu(q->scsiq_rptr),
	       (uदीर्घ)le32_to_cpu(q->sg_real_addr), (uदीर्घ)q->sg_list_ptr);

	/* Display the request's ADV_SG_BLOCK काष्ठाures. */
	अगर (q->sg_list_ptr != शून्य) अणु
		sgblkp = container_of(q->sg_list_ptr, adv_sgblk_t, sg_block);
		sg_blk_cnt = 0;
		जबतक (sgblkp) अणु
			sg_ptr = &sgblkp->sg_block;
			asc_prt_adv_sgblock(sg_blk_cnt, sg_ptr);
			अगर (sg_ptr->sg_ptr == 0) अणु
				अवरोध;
			पूर्ण
			sgblkp = sgblkp->next_sgblkp;
			sg_blk_cnt++;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* ADVANSYS_DEBUG */

/*
 * advansys_info()
 *
 * Return suitable क्रम prपूर्णांकing on the console with the argument
 * adapter's configuration inक्रमmation.
 *
 * Note: The inक्रमmation line should not exceed ASC_INFO_SIZE bytes,
 * otherwise the अटल 'info' array will be overrun.
 */
अटल स्थिर अक्षर *advansys_info(काष्ठा Scsi_Host *shost)
अणु
	अटल अक्षर info[ASC_INFO_SIZE];
	काष्ठा asc_board *boardp = shost_priv(shost);
	ASC_DVC_VAR *asc_dvc_varp;
	ADV_DVC_VAR *adv_dvc_varp;
	अक्षर *busname;
	अक्षर *widename = शून्य;

	अगर (ASC_NARROW_BOARD(boardp)) अणु
		asc_dvc_varp = &boardp->dvc_var.asc_dvc_var;
		ASC_DBG(1, "begin\n");

		अगर (asc_dvc_varp->bus_type & ASC_IS_VL) अणु
			busname = "VL";
		पूर्ण अन्यथा अगर (asc_dvc_varp->bus_type & ASC_IS_EISA) अणु
			busname = "EISA";
		पूर्ण अन्यथा अगर (asc_dvc_varp->bus_type & ASC_IS_PCI) अणु
			अगर ((asc_dvc_varp->bus_type & ASC_IS_PCI_ULTRA)
			    == ASC_IS_PCI_ULTRA) अणु
				busname = "PCI Ultra";
			पूर्ण अन्यथा अणु
				busname = "PCI";
			पूर्ण
		पूर्ण अन्यथा अणु
			busname = "?";
			shost_prपूर्णांकk(KERN_ERR, shost, "unknown bus "
				"type %d\n", asc_dvc_varp->bus_type);
		पूर्ण
		प्र_लिखो(info,
			"AdvanSys SCSI %s: %s: IO 0x%lX-0x%lX, IRQ 0x%X",
			ASC_VERSION, busname, (uदीर्घ)shost->io_port,
			(uदीर्घ)shost->io_port + ASC_IOADR_GAP - 1,
			boardp->irq);
	पूर्ण अन्यथा अणु
		/*
		 * Wide Adapter Inक्रमmation
		 *
		 * Memory-mapped I/O is used instead of I/O space to access
		 * the adapter, but display the I/O Port range. The Memory
		 * I/O address is displayed through the driver /proc file.
		 */
		adv_dvc_varp = &boardp->dvc_var.adv_dvc_var;
		अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550) अणु
			widename = "Ultra-Wide";
		पूर्ण अन्यथा अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800) अणु
			widename = "Ultra2-Wide";
		पूर्ण अन्यथा अणु
			widename = "Ultra3-Wide";
		पूर्ण
		प्र_लिखो(info,
			"AdvanSys SCSI %s: PCI %s: PCIMEM 0x%lX-0x%lX, IRQ 0x%X",
			ASC_VERSION, widename, (uदीर्घ)adv_dvc_varp->iop_base,
			(uदीर्घ)adv_dvc_varp->iop_base + boardp->asc_n_io_port - 1, boardp->irq);
	पूर्ण
	BUG_ON(म_माप(info) >= ASC_INFO_SIZE);
	ASC_DBG(1, "end\n");
	वापस info;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

/*
 * asc_prt_board_devices()
 *
 * Prपूर्णांक driver inक्रमmation क्रम devices attached to the board.
 */
अटल व्योम asc_prt_board_devices(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *boardp = shost_priv(shost);
	पूर्णांक chip_scsi_id;
	पूर्णांक i;

	seq_म_लिखो(m,
		   "\nDevice Information for AdvanSys SCSI Host %d:\n",
		   shost->host_no);

	अगर (ASC_NARROW_BOARD(boardp)) अणु
		chip_scsi_id = boardp->dvc_cfg.asc_dvc_cfg.chip_scsi_id;
	पूर्ण अन्यथा अणु
		chip_scsi_id = boardp->dvc_var.adv_dvc_var.chip_scsi_id;
	पूर्ण

	seq_माला_दो(m, "Target IDs Detected:");
	क्रम (i = 0; i <= ADV_MAX_TID; i++) अणु
		अगर (boardp->init_tidmask & ADV_TID_TO_TIDMASK(i))
			seq_म_लिखो(m, " %X,", i);
	पूर्ण
	seq_म_लिखो(m, " (%X=Host Adapter)\n", chip_scsi_id);
पूर्ण

/*
 * Display Wide Board BIOS Inक्रमmation.
 */
अटल व्योम asc_prt_adv_bios(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *boardp = shost_priv(shost);
	uलघु major, minor, letter;

	seq_माला_दो(m, "\nROM BIOS Version: ");

	/*
	 * If the BIOS saved a valid signature, then fill in
	 * the BIOS code segment base address.
	 */
	अगर (boardp->bios_signature != 0x55AA) अणु
		seq_माला_दो(m, "Disabled or Pre-3.1\n"
			"BIOS either disabled or Pre-3.1. If it is pre-3.1, then a newer version\n"
			"can be found at the ConnectCom FTP site: ftp://ftp.connectcom.net/pub\n");
	पूर्ण अन्यथा अणु
		major = (boardp->bios_version >> 12) & 0xF;
		minor = (boardp->bios_version >> 8) & 0xF;
		letter = (boardp->bios_version & 0xFF);

		seq_म_लिखो(m, "%d.%d%c\n",
				   major, minor,
				   letter >= 26 ? '?' : letter + 'A');
		/*
		 * Current available ROM BIOS release is 3.1I क्रम UW
		 * and 3.2I क्रम U2W. This code करोesn't dअगरferentiate
		 * UW and U2W boards.
		 */
		अगर (major < 3 || (major <= 3 && minor < 1) ||
		    (major <= 3 && minor <= 1 && letter < ('I' - 'A'))) अणु
			seq_माला_दो(m, "Newer version of ROM BIOS is available at the ConnectCom FTP site:\n"
				"ftp://ftp.connectcom.net/pub\n");
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Add serial number to inक्रमmation bar अगर signature AAh
 * is found in at bit 15-9 (7 bits) of word 1.
 *
 * Serial Number consists fo 12 alpha-numeric digits.
 *
 *       1 - Product type (A,B,C,D..)  Word0: 15-13 (3 bits)
 *       2 - MFG Location (A,B,C,D..)  Word0: 12-10 (3 bits)
 *     3-4 - Product ID (0-99)         Word0: 9-0 (10 bits)
 *       5 - Product revision (A-J)    Word0:  "         "
 *
 *           Signature                 Word1: 15-9 (7 bits)
 *       6 - Year (0-9)                Word1: 8-6 (3 bits) & Word2: 15 (1 bit)
 *     7-8 - Week of the year (1-52)   Word1: 5-0 (6 bits)
 *
 *    9-12 - Serial Number (A001-Z999) Word2: 14-0 (15 bits)
 *
 * Note 1: Only production cards will have a serial number.
 *
 * Note 2: Signature is most signअगरicant 7 bits (0xFE).
 *
 * Returns ASC_TRUE अगर serial number found, otherwise वापसs ASC_FALSE.
 */
अटल पूर्णांक asc_get_eeprom_string(uलघु *serialnum, uअक्षर *cp)
अणु
	uलघु w, num;

	अगर ((serialnum[1] & 0xFE00) != ((uलघु)0xAA << 8)) अणु
		वापस ASC_FALSE;
	पूर्ण अन्यथा अणु
		/*
		 * First word - 6 digits.
		 */
		w = serialnum[0];

		/* Product type - 1st digit. */
		अगर ((*cp = 'A' + ((w & 0xE000) >> 13)) == 'H') अणु
			/* Product type is P=Prototype */
			*cp += 0x8;
		पूर्ण
		cp++;

		/* Manufacturing location - 2nd digit. */
		*cp++ = 'A' + ((w & 0x1C00) >> 10);

		/* Product ID - 3rd, 4th digits. */
		num = w & 0x3FF;
		*cp++ = '0' + (num / 100);
		num %= 100;
		*cp++ = '0' + (num / 10);

		/* Product revision - 5th digit. */
		*cp++ = 'A' + (num % 10);

		/*
		 * Second word
		 */
		w = serialnum[1];

		/*
		 * Year - 6th digit.
		 *
		 * If bit 15 of third word is set, then the
		 * last digit of the year is greater than 7.
		 */
		अगर (serialnum[2] & 0x8000) अणु
			*cp++ = '8' + ((w & 0x1C0) >> 6);
		पूर्ण अन्यथा अणु
			*cp++ = '0' + ((w & 0x1C0) >> 6);
		पूर्ण

		/* Week of year - 7th, 8th digits. */
		num = w & 0x003F;
		*cp++ = '0' + num / 10;
		num %= 10;
		*cp++ = '0' + num;

		/*
		 * Third word
		 */
		w = serialnum[2] & 0x7FFF;

		/* Serial number - 9th digit. */
		*cp++ = 'A' + (w / 1000);

		/* 10th, 11th, 12th digits. */
		num = w % 1000;
		*cp++ = '0' + num / 100;
		num %= 100;
		*cp++ = '0' + num / 10;
		num %= 10;
		*cp++ = '0' + num;

		*cp = '\0';	/* Null Terminate the string. */
		वापस ASC_TRUE;
	पूर्ण
पूर्ण

/*
 * asc_prt_asc_board_eeprom()
 *
 * Prपूर्णांक board EEPROM configuration.
 */
अटल व्योम asc_prt_asc_board_eeprom(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *boardp = shost_priv(shost);
	ASCEEP_CONFIG *ep;
	पूर्णांक i;
	uअक्षर serialstr[13];

	ep = &boardp->eep_config.asc_eep;

	seq_म_लिखो(m,
		   "\nEEPROM Settings for AdvanSys SCSI Host %d:\n",
		   shost->host_no);

	अगर (asc_get_eeprom_string((uलघु *)&ep->adapter_info[0], serialstr)
	    == ASC_TRUE)
		seq_म_लिखो(m, " Serial Number: %s\n", serialstr);
	अन्यथा अगर (ep->adapter_info[5] == 0xBB)
		seq_माला_दो(m,
			 " Default Settings Used for EEPROM-less Adapter.\n");
	अन्यथा
		seq_माला_दो(m, " Serial Number Signature Not Present.\n");

	seq_म_लिखो(m,
		   " Host SCSI ID: %u, Host Queue Size: %u, Device Queue Size: %u\n",
		   ASC_EEP_GET_CHIP_ID(ep), ep->max_total_qng,
		   ep->max_tag_qng);

	seq_म_लिखो(m,
		   " cntl 0x%x, no_scam 0x%x\n", ep->cntl, ep->no_scam);

	seq_माला_दो(m, " Target ID:           ");
	क्रम (i = 0; i <= ASC_MAX_TID; i++)
		seq_म_लिखो(m, " %d", i);

	seq_माला_दो(m, "\n Disconnects:         ");
	क्रम (i = 0; i <= ASC_MAX_TID; i++)
		seq_म_लिखो(m, " %c",
			   (ep->disc_enable & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');

	seq_माला_दो(m, "\n Command Queuing:     ");
	क्रम (i = 0; i <= ASC_MAX_TID; i++)
		seq_म_लिखो(m, " %c",
			   (ep->use_cmd_qng & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');

	seq_माला_दो(m, "\n Start Motor:         ");
	क्रम (i = 0; i <= ASC_MAX_TID; i++)
		seq_म_लिखो(m, " %c",
			   (ep->start_motor & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');

	seq_माला_दो(m, "\n Synchronous Transfer:");
	क्रम (i = 0; i <= ASC_MAX_TID; i++)
		seq_म_लिखो(m, " %c",
			   (ep->init_sdtr & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');
	seq_अ_दो(m, '\n');
पूर्ण

/*
 * asc_prt_adv_board_eeprom()
 *
 * Prपूर्णांक board EEPROM configuration.
 */
अटल व्योम asc_prt_adv_board_eeprom(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *boardp = shost_priv(shost);
	ADV_DVC_VAR *adv_dvc_varp;
	पूर्णांक i;
	अक्षर *termstr;
	uअक्षर serialstr[13];
	ADVEEP_3550_CONFIG *ep_3550 = शून्य;
	ADVEEP_38C0800_CONFIG *ep_38C0800 = शून्य;
	ADVEEP_38C1600_CONFIG *ep_38C1600 = शून्य;
	uलघु word;
	uलघु *wordp;
	uलघु sdtr_speed = 0;

	adv_dvc_varp = &boardp->dvc_var.adv_dvc_var;
	अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550) अणु
		ep_3550 = &boardp->eep_config.adv_3550_eep;
	पूर्ण अन्यथा अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800) अणु
		ep_38C0800 = &boardp->eep_config.adv_38C0800_eep;
	पूर्ण अन्यथा अणु
		ep_38C1600 = &boardp->eep_config.adv_38C1600_eep;
	पूर्ण

	seq_म_लिखो(m,
		   "\nEEPROM Settings for AdvanSys SCSI Host %d:\n",
		   shost->host_no);

	अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550) अणु
		wordp = &ep_3550->serial_number_word1;
	पूर्ण अन्यथा अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800) अणु
		wordp = &ep_38C0800->serial_number_word1;
	पूर्ण अन्यथा अणु
		wordp = &ep_38C1600->serial_number_word1;
	पूर्ण

	अगर (asc_get_eeprom_string(wordp, serialstr) == ASC_TRUE)
		seq_म_लिखो(m, " Serial Number: %s\n", serialstr);
	अन्यथा
		seq_माला_दो(m, " Serial Number Signature Not Present.\n");

	अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550)
		seq_म_लिखो(m,
			   " Host SCSI ID: %u, Host Queue Size: %u, Device Queue Size: %u\n",
			   ep_3550->adapter_scsi_id,
			   ep_3550->max_host_qng, ep_3550->max_dvc_qng);
	अन्यथा अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800)
		seq_म_लिखो(m,
			   " Host SCSI ID: %u, Host Queue Size: %u, Device Queue Size: %u\n",
			   ep_38C0800->adapter_scsi_id,
			   ep_38C0800->max_host_qng,
			   ep_38C0800->max_dvc_qng);
	अन्यथा
		seq_म_लिखो(m,
			   " Host SCSI ID: %u, Host Queue Size: %u, Device Queue Size: %u\n",
			   ep_38C1600->adapter_scsi_id,
			   ep_38C1600->max_host_qng,
			   ep_38C1600->max_dvc_qng);
	अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550) अणु
		word = ep_3550->termination;
	पूर्ण अन्यथा अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800) अणु
		word = ep_38C0800->termination_lvd;
	पूर्ण अन्यथा अणु
		word = ep_38C1600->termination_lvd;
	पूर्ण
	चयन (word) अणु
	हाल 1:
		termstr = "Low Off/High Off";
		अवरोध;
	हाल 2:
		termstr = "Low Off/High On";
		अवरोध;
	हाल 3:
		termstr = "Low On/High On";
		अवरोध;
	शेष:
	हाल 0:
		termstr = "Automatic";
		अवरोध;
	पूर्ण

	अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550)
		seq_म_लिखो(m,
			   " termination: %u (%s), bios_ctrl: 0x%x\n",
			   ep_3550->termination, termstr,
			   ep_3550->bios_ctrl);
	अन्यथा अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800)
		seq_म_लिखो(m,
			   " termination: %u (%s), bios_ctrl: 0x%x\n",
			   ep_38C0800->termination_lvd, termstr,
			   ep_38C0800->bios_ctrl);
	अन्यथा
		seq_म_लिखो(m,
			   " termination: %u (%s), bios_ctrl: 0x%x\n",
			   ep_38C1600->termination_lvd, termstr,
			   ep_38C1600->bios_ctrl);

	seq_माला_दो(m, " Target ID:           ");
	क्रम (i = 0; i <= ADV_MAX_TID; i++)
		seq_म_लिखो(m, " %X", i);
	seq_अ_दो(m, '\n');

	अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550) अणु
		word = ep_3550->disc_enable;
	पूर्ण अन्यथा अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800) अणु
		word = ep_38C0800->disc_enable;
	पूर्ण अन्यथा अणु
		word = ep_38C1600->disc_enable;
	पूर्ण
	seq_माला_दो(m, " Disconnects:         ");
	क्रम (i = 0; i <= ADV_MAX_TID; i++)
		seq_म_लिखो(m, " %c",
			   (word & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');
	seq_अ_दो(m, '\n');

	अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550) अणु
		word = ep_3550->tagqng_able;
	पूर्ण अन्यथा अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800) अणु
		word = ep_38C0800->tagqng_able;
	पूर्ण अन्यथा अणु
		word = ep_38C1600->tagqng_able;
	पूर्ण
	seq_माला_दो(m, " Command Queuing:     ");
	क्रम (i = 0; i <= ADV_MAX_TID; i++)
		seq_म_लिखो(m, " %c",
			   (word & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');
	seq_अ_दो(m, '\n');

	अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550) अणु
		word = ep_3550->start_motor;
	पूर्ण अन्यथा अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800) अणु
		word = ep_38C0800->start_motor;
	पूर्ण अन्यथा अणु
		word = ep_38C1600->start_motor;
	पूर्ण
	seq_माला_दो(m, " Start Motor:         ");
	क्रम (i = 0; i <= ADV_MAX_TID; i++)
		seq_म_लिखो(m, " %c",
			   (word & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');
	seq_अ_दो(m, '\n');

	अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550) अणु
		seq_माला_दो(m, " Synchronous Transfer:");
		क्रम (i = 0; i <= ADV_MAX_TID; i++)
			seq_म_लिखो(m, " %c",
				   (ep_3550->sdtr_able & ADV_TID_TO_TIDMASK(i)) ?
				   'Y' : 'N');
		seq_अ_दो(m, '\n');
	पूर्ण

	अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550) अणु
		seq_माला_दो(m, " Ultra Transfer:      ");
		क्रम (i = 0; i <= ADV_MAX_TID; i++)
			seq_म_लिखो(m, " %c",
				   (ep_3550->ultra_able & ADV_TID_TO_TIDMASK(i))
				   ? 'Y' : 'N');
		seq_अ_दो(m, '\n');
	पूर्ण

	अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550) अणु
		word = ep_3550->wdtr_able;
	पूर्ण अन्यथा अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800) अणु
		word = ep_38C0800->wdtr_able;
	पूर्ण अन्यथा अणु
		word = ep_38C1600->wdtr_able;
	पूर्ण
	seq_माला_दो(m, " Wide Transfer:       ");
	क्रम (i = 0; i <= ADV_MAX_TID; i++)
		seq_म_लिखो(m, " %c",
			   (word & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');
	seq_अ_दो(m, '\n');

	अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800 ||
	    adv_dvc_varp->chip_type == ADV_CHIP_ASC38C1600) अणु
		seq_माला_दो(m, " Synchronous Transfer Speed (Mhz):\n  ");
		क्रम (i = 0; i <= ADV_MAX_TID; i++) अणु
			अक्षर *speed_str;

			अगर (i == 0) अणु
				sdtr_speed = adv_dvc_varp->sdtr_speed1;
			पूर्ण अन्यथा अगर (i == 4) अणु
				sdtr_speed = adv_dvc_varp->sdtr_speed2;
			पूर्ण अन्यथा अगर (i == 8) अणु
				sdtr_speed = adv_dvc_varp->sdtr_speed3;
			पूर्ण अन्यथा अगर (i == 12) अणु
				sdtr_speed = adv_dvc_varp->sdtr_speed4;
			पूर्ण
			चयन (sdtr_speed & ADV_MAX_TID) अणु
			हाल 0:
				speed_str = "Off";
				अवरोध;
			हाल 1:
				speed_str = "  5";
				अवरोध;
			हाल 2:
				speed_str = " 10";
				अवरोध;
			हाल 3:
				speed_str = " 20";
				अवरोध;
			हाल 4:
				speed_str = " 40";
				अवरोध;
			हाल 5:
				speed_str = " 80";
				अवरोध;
			शेष:
				speed_str = "Unk";
				अवरोध;
			पूर्ण
			seq_म_लिखो(m, "%X:%s ", i, speed_str);
			अगर (i == 7)
				seq_माला_दो(m, "\n  ");
			sdtr_speed >>= 4;
		पूर्ण
		seq_अ_दो(m, '\n');
	पूर्ण
पूर्ण

/*
 * asc_prt_driver_conf()
 */
अटल व्योम asc_prt_driver_conf(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *boardp = shost_priv(shost);

	seq_म_लिखो(m,
		"\nLinux Driver Configuration and Information for AdvanSys SCSI Host %d:\n",
		shost->host_no);

	seq_म_लिखो(m,
		   " host_busy %d, max_id %u, max_lun %llu, max_channel %u\n",
		   scsi_host_busy(shost), shost->max_id,
		   shost->max_lun, shost->max_channel);

	seq_म_लिखो(m,
		   " unique_id %d, can_queue %d, this_id %d, sg_tablesize %u, cmd_per_lun %u\n",
		   shost->unique_id, shost->can_queue, shost->this_id,
		   shost->sg_tablesize, shost->cmd_per_lun);

	seq_म_लिखो(m,
		   " flags 0x%x, last_reset 0x%lx, jiffies 0x%lx, asc_n_io_port 0x%x\n",
		   boardp->flags, shost->last_reset, jअगरfies,
		   boardp->asc_n_io_port);

	seq_म_लिखो(m, " io_port 0x%lx\n", shost->io_port);
पूर्ण

/*
 * asc_prt_asc_board_info()
 *
 * Prपूर्णांक dynamic board configuration inक्रमmation.
 */
अटल व्योम asc_prt_asc_board_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *boardp = shost_priv(shost);
	पूर्णांक chip_scsi_id;
	ASC_DVC_VAR *v;
	ASC_DVC_CFG *c;
	पूर्णांक i;
	पूर्णांक renegotiate = 0;

	v = &boardp->dvc_var.asc_dvc_var;
	c = &boardp->dvc_cfg.asc_dvc_cfg;
	chip_scsi_id = c->chip_scsi_id;

	seq_म_लिखो(m,
		   "\nAsc Library Configuration and Statistics for AdvanSys SCSI Host %d:\n",
		   shost->host_no);

	seq_म_लिखो(m, " chip_version %u, mcode_date 0x%x, "
		   "mcode_version 0x%x, err_code %u\n",
		   c->chip_version, c->mcode_date, c->mcode_version,
		   v->err_code);

	/* Current number of commands रुकोing क्रम the host. */
	seq_म_लिखो(m,
		   " Total Command Pending: %d\n", v->cur_total_qng);

	seq_माला_दो(m, " Command Queuing:");
	क्रम (i = 0; i <= ASC_MAX_TID; i++) अणु
		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण
		seq_म_लिखो(m, " %X:%c",
			   i,
			   (v->use_tagged_qng & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');
	पूर्ण

	/* Current number of commands रुकोing क्रम a device. */
	seq_माला_दो(m, "\n Command Queue Pending:");
	क्रम (i = 0; i <= ASC_MAX_TID; i++) अणु
		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण
		seq_म_लिखो(m, " %X:%u", i, v->cur_dvc_qng[i]);
	पूर्ण

	/* Current limit on number of commands that can be sent to a device. */
	seq_माला_दो(m, "\n Command Queue Limit:");
	क्रम (i = 0; i <= ASC_MAX_TID; i++) अणु
		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण
		seq_म_लिखो(m, " %X:%u", i, v->max_dvc_qng[i]);
	पूर्ण

	/* Indicate whether the device has वापसed queue full status. */
	seq_माला_दो(m, "\n Command Queue Full:");
	क्रम (i = 0; i <= ASC_MAX_TID; i++) अणु
		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण
		अगर (boardp->queue_full & ADV_TID_TO_TIDMASK(i))
			seq_म_लिखो(m, " %X:Y-%d",
				   i, boardp->queue_full_cnt[i]);
		अन्यथा
			seq_म_लिखो(m, " %X:N", i);
	पूर्ण

	seq_माला_दो(m, "\n Synchronous Transfer:");
	क्रम (i = 0; i <= ASC_MAX_TID; i++) अणु
		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण
		seq_म_लिखो(m, " %X:%c",
			   i,
			   (v->sdtr_करोne & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');
	पूर्ण
	seq_अ_दो(m, '\n');

	क्रम (i = 0; i <= ASC_MAX_TID; i++) अणु
		uअक्षर syn_period_ix;

		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0) ||
		    ((v->init_sdtr & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण

		seq_म_लिखो(m, "  %X:", i);

		अगर ((boardp->sdtr_data[i] & ASC_SYN_MAX_OFFSET) == 0) अणु
			seq_माला_दो(m, " Asynchronous");
		पूर्ण अन्यथा अणु
			syn_period_ix =
			    (boardp->sdtr_data[i] >> 4) & (v->max_sdtr_index -
							   1);

			seq_म_लिखो(m,
				   " Transfer Period Factor: %d (%d.%d Mhz),",
				   v->sdtr_period_tbl[syn_period_ix],
				   250 / v->sdtr_period_tbl[syn_period_ix],
				   ASC_TENTHS(250,
					      v->sdtr_period_tbl[syn_period_ix]));

			seq_म_लिखो(m, " REQ/ACK Offset: %d",
				   boardp->sdtr_data[i] & ASC_SYN_MAX_OFFSET);
		पूर्ण

		अगर ((v->sdtr_करोne & ADV_TID_TO_TIDMASK(i)) == 0) अणु
			seq_माला_दो(m, "*\n");
			renegotiate = 1;
		पूर्ण अन्यथा अणु
			seq_अ_दो(m, '\n');
		पूर्ण
	पूर्ण

	अगर (renegotiate) अणु
		seq_माला_दो(m, " * = Re-negotiation pending before next command.\n");
	पूर्ण
पूर्ण

/*
 * asc_prt_adv_board_info()
 *
 * Prपूर्णांक dynamic board configuration inक्रमmation.
 */
अटल व्योम asc_prt_adv_board_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *boardp = shost_priv(shost);
	पूर्णांक i;
	ADV_DVC_VAR *v;
	ADV_DVC_CFG *c;
	AdvPortAddr iop_base;
	uलघु chip_scsi_id;
	uलघु lramword;
	uअक्षर lrambyte;
	uलघु tagqng_able;
	uलघु sdtr_able, wdtr_able;
	uलघु wdtr_करोne, sdtr_करोne;
	uलघु period = 0;
	पूर्णांक renegotiate = 0;

	v = &boardp->dvc_var.adv_dvc_var;
	c = &boardp->dvc_cfg.adv_dvc_cfg;
	iop_base = v->iop_base;
	chip_scsi_id = v->chip_scsi_id;

	seq_म_लिखो(m,
		   "\nAdv Library Configuration and Statistics for AdvanSys SCSI Host %d:\n",
		   shost->host_no);

	seq_म_लिखो(m,
		   " iop_base 0x%lx, cable_detect: %X, err_code %u\n",
		   (अचिन्हित दीर्घ)v->iop_base,
		   AdvReadWordRegister(iop_base,IOPW_SCSI_CFG1) & CABLE_DETECT,
		   v->err_code);

	seq_म_लिखो(m, " chip_version %u, mcode_date 0x%x, "
		   "mcode_version 0x%x\n", c->chip_version,
		   c->mcode_date, c->mcode_version);

	AdvReadWordLram(iop_base, ASC_MC_TAGQNG_ABLE, tagqng_able);
	seq_माला_दो(m, " Queuing Enabled:");
	क्रम (i = 0; i <= ADV_MAX_TID; i++) अणु
		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण

		seq_म_लिखो(m, " %X:%c",
			   i,
			   (tagqng_able & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');
	पूर्ण

	seq_माला_दो(m, "\n Queue Limit:");
	क्रम (i = 0; i <= ADV_MAX_TID; i++) अणु
		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण

		AdvReadByteLram(iop_base, ASC_MC_NUMBER_OF_MAX_CMD + i,
				lrambyte);

		seq_म_लिखो(m, " %X:%d", i, lrambyte);
	पूर्ण

	seq_माला_दो(m, "\n Command Pending:");
	क्रम (i = 0; i <= ADV_MAX_TID; i++) अणु
		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण

		AdvReadByteLram(iop_base, ASC_MC_NUMBER_OF_QUEUED_CMD + i,
				lrambyte);

		seq_म_लिखो(m, " %X:%d", i, lrambyte);
	पूर्ण
	seq_अ_दो(m, '\n');

	AdvReadWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
	seq_माला_दो(m, " Wide Enabled:");
	क्रम (i = 0; i <= ADV_MAX_TID; i++) अणु
		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण

		seq_म_लिखो(m, " %X:%c",
			   i,
			   (wdtr_able & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');
	पूर्ण
	seq_अ_दो(m, '\n');

	AdvReadWordLram(iop_base, ASC_MC_WDTR_DONE, wdtr_करोne);
	seq_माला_दो(m, " Transfer Bit Width:");
	क्रम (i = 0; i <= ADV_MAX_TID; i++) अणु
		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण

		AdvReadWordLram(iop_base,
				ASC_MC_DEVICE_HSHK_CFG_TABLE + (2 * i),
				lramword);

		seq_म_लिखो(m, " %X:%d",
			   i, (lramword & 0x8000) ? 16 : 8);

		अगर ((wdtr_able & ADV_TID_TO_TIDMASK(i)) &&
		    (wdtr_करोne & ADV_TID_TO_TIDMASK(i)) == 0) अणु
			seq_अ_दो(m, '*');
			renegotiate = 1;
		पूर्ण
	पूर्ण
	seq_अ_दो(m, '\n');

	AdvReadWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
	seq_माला_दो(m, " Synchronous Enabled:");
	क्रम (i = 0; i <= ADV_MAX_TID; i++) अणु
		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण

		seq_म_लिखो(m, " %X:%c",
			   i,
			   (sdtr_able & ADV_TID_TO_TIDMASK(i)) ? 'Y' : 'N');
	पूर्ण
	seq_अ_दो(m, '\n');

	AdvReadWordLram(iop_base, ASC_MC_SDTR_DONE, sdtr_करोne);
	क्रम (i = 0; i <= ADV_MAX_TID; i++) अणु

		AdvReadWordLram(iop_base,
				ASC_MC_DEVICE_HSHK_CFG_TABLE + (2 * i),
				lramword);
		lramword &= ~0x8000;

		अगर ((chip_scsi_id == i) ||
		    ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(i)) == 0) ||
		    ((sdtr_able & ADV_TID_TO_TIDMASK(i)) == 0)) अणु
			जारी;
		पूर्ण

		seq_म_लिखो(m, "  %X:", i);

		अगर ((lramword & 0x1F) == 0) अणु	/* Check क्रम REQ/ACK Offset 0. */
			seq_माला_दो(m, " Asynchronous");
		पूर्ण अन्यथा अणु
			seq_माला_दो(m, " Transfer Period Factor: ");

			अगर ((lramword & 0x1F00) == 0x1100) अणु	/* 80 Mhz */
				seq_माला_दो(m, "9 (80.0 Mhz),");
			पूर्ण अन्यथा अगर ((lramword & 0x1F00) == 0x1000) अणु	/* 40 Mhz */
				seq_माला_दो(m, "10 (40.0 Mhz),");
			पूर्ण अन्यथा अणु	/* 20 Mhz or below. */

				period = (((lramword >> 8) * 25) + 50) / 4;

				अगर (period == 0) अणु	/* Should never happen. */
					seq_म_लिखो(m, "%d (? Mhz), ", period);
				पूर्ण अन्यथा अणु
					seq_म_लिखो(m,
						   "%d (%d.%d Mhz),",
						   period, 250 / period,
						   ASC_TENTHS(250, period));
				पूर्ण
			पूर्ण

			seq_म_लिखो(m, " REQ/ACK Offset: %d",
				   lramword & 0x1F);
		पूर्ण

		अगर ((sdtr_करोne & ADV_TID_TO_TIDMASK(i)) == 0) अणु
			seq_माला_दो(m, "*\n");
			renegotiate = 1;
		पूर्ण अन्यथा अणु
			seq_अ_दो(m, '\n');
		पूर्ण
	पूर्ण

	अगर (renegotiate) अणु
		seq_माला_दो(m, " * = Re-negotiation pending before next command.\n");
	पूर्ण
पूर्ण

#अगर_घोषित ADVANSYS_STATS
/*
 * asc_prt_board_stats()
 */
अटल व्योम asc_prt_board_stats(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *boardp = shost_priv(shost);
	काष्ठा asc_stats *s = &boardp->asc_stats;

	seq_म_लिखो(m,
		   "\nLinux Driver Statistics for AdvanSys SCSI Host %d:\n",
		   shost->host_no);

	seq_म_लिखो(m,
		   " queuecommand %u, reset %u, biosparam %u, interrupt %u\n",
		   s->queuecommand, s->reset, s->biosparam,
		   s->पूर्णांकerrupt);

	seq_म_लिखो(m,
		   " callback %u, done %u, build_error %u, build_noreq %u, build_nosg %u\n",
		   s->callback, s->करोne, s->build_error,
		   s->adv_build_noreq, s->adv_build_nosg);

	seq_म_लिखो(m,
		   " exe_noerror %u, exe_busy %u, exe_error %u, exe_unknown %u\n",
		   s->exe_noerror, s->exe_busy, s->exe_error,
		   s->exe_unknown);

	/*
	 * Display data transfer statistics.
	 */
	अगर (s->xfer_cnt > 0) अणु
		seq_म_लिखो(m, " xfer_cnt %u, xfer_elem %u, ",
			   s->xfer_cnt, s->xfer_elem);

		seq_म_लिखो(m, "xfer_bytes %u.%01u kb\n",
			   s->xfer_sect / 2, ASC_TENTHS(s->xfer_sect, 2));

		/* Scatter gather transfer statistics */
		seq_म_लिखो(m, " avg_num_elem %u.%01u, ",
			   s->xfer_elem / s->xfer_cnt,
			   ASC_TENTHS(s->xfer_elem, s->xfer_cnt));

		seq_म_लिखो(m, "avg_elem_size %u.%01u kb, ",
			   (s->xfer_sect / 2) / s->xfer_elem,
			   ASC_TENTHS((s->xfer_sect / 2), s->xfer_elem));

		seq_म_लिखो(m, "avg_xfer_size %u.%01u kb\n",
			   (s->xfer_sect / 2) / s->xfer_cnt,
			   ASC_TENTHS((s->xfer_sect / 2), s->xfer_cnt));
	पूर्ण
पूर्ण
#पूर्ण_अगर /* ADVANSYS_STATS */

/*
 * advansys_show_info() - /proc/scsi/advansys/अणु0,1,2,3,...पूर्ण
 *
 * m: seq_file to prपूर्णांक पूर्णांकo
 * shost: Scsi_Host
 *
 * Return the number of bytes पढ़ो from or written to a
 * /proc/scsi/advansys/[0...] file.
 */
अटल पूर्णांक
advansys_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *boardp = shost_priv(shost);

	ASC_DBG(1, "begin\n");

	/*
	 * User पढ़ो of /proc/scsi/advansys/[0...] file.
	 */

	/*
	 * Get board configuration inक्रमmation.
	 *
	 * advansys_info() वापसs the board string from its own अटल buffer.
	 */
	/* Copy board inक्रमmation. */
	seq_म_लिखो(m, "%s\n", (अक्षर *)advansys_info(shost));
	/*
	 * Display Wide Board BIOS Inक्रमmation.
	 */
	अगर (!ASC_NARROW_BOARD(boardp))
		asc_prt_adv_bios(m, shost);

	/*
	 * Display driver inक्रमmation क्रम each device attached to the board.
	 */
	asc_prt_board_devices(m, shost);

	/*
	 * Display EEPROM configuration क्रम the board.
	 */
	अगर (ASC_NARROW_BOARD(boardp))
		asc_prt_asc_board_eeprom(m, shost);
	अन्यथा
		asc_prt_adv_board_eeprom(m, shost);

	/*
	 * Display driver configuration and inक्रमmation क्रम the board.
	 */
	asc_prt_driver_conf(m, shost);

#अगर_घोषित ADVANSYS_STATS
	/*
	 * Display driver statistics क्रम the board.
	 */
	asc_prt_board_stats(m, shost);
#पूर्ण_अगर /* ADVANSYS_STATS */

	/*
	 * Display Asc Library dynamic configuration inक्रमmation
	 * क्रम the board.
	 */
	अगर (ASC_NARROW_BOARD(boardp))
		asc_prt_asc_board_info(m, shost);
	अन्यथा
		asc_prt_adv_board_info(m, shost);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल व्योम asc_scsi_करोne(काष्ठा scsi_cmnd *scp)
अणु
	scsi_dma_unmap(scp);
	ASC_STATS(scp->device->host, करोne);
	scp->scsi_करोne(scp);
पूर्ण

अटल व्योम AscSetBank(PortAddr iop_base, uअक्षर bank)
अणु
	uअक्षर val;

	val = AscGetChipControl(iop_base) &
	    (~
	     (CC_SINGLE_STEP | CC_TEST | CC_DIAG | CC_SCSI_RESET |
	      CC_CHIP_RESET));
	अगर (bank == 1) अणु
		val |= CC_BANK_ONE;
	पूर्ण अन्यथा अगर (bank == 2) अणु
		val |= CC_DIAG | CC_BANK_ONE;
	पूर्ण अन्यथा अणु
		val &= ~CC_BANK_ONE;
	पूर्ण
	AscSetChipControl(iop_base, val);
पूर्ण

अटल व्योम AscSetChipIH(PortAddr iop_base, uलघु ins_code)
अणु
	AscSetBank(iop_base, 1);
	AscWriteChipIH(iop_base, ins_code);
	AscSetBank(iop_base, 0);
पूर्ण

अटल पूर्णांक AscStartChip(PortAddr iop_base)
अणु
	AscSetChipControl(iop_base, 0);
	अगर ((AscGetChipStatus(iop_base) & CSW_HALTED) != 0) अणु
		वापस (0);
	पूर्ण
	वापस (1);
पूर्ण

अटल bool AscStopChip(PortAddr iop_base)
अणु
	uअक्षर cc_val;

	cc_val =
	    AscGetChipControl(iop_base) &
	    (~(CC_SINGLE_STEP | CC_TEST | CC_DIAG));
	AscSetChipControl(iop_base, (uअक्षर)(cc_val | CC_HALT));
	AscSetChipIH(iop_base, INS_HALT);
	AscSetChipIH(iop_base, INS_RFLAG_WTM);
	अगर ((AscGetChipStatus(iop_base) & CSW_HALTED) == 0) अणु
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool AscIsChipHalted(PortAddr iop_base)
अणु
	अगर ((AscGetChipStatus(iop_base) & CSW_HALTED) != 0) अणु
		अगर ((AscGetChipControl(iop_base) & CC_HALT) != 0) अणु
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल bool AscResetChipAndScsiBus(ASC_DVC_VAR *asc_dvc)
अणु
	PortAddr iop_base;
	पूर्णांक i = 10;

	iop_base = asc_dvc->iop_base;
	जबतक ((AscGetChipStatus(iop_base) & CSW_SCSI_RESET_ACTIVE)
	       && (i-- > 0)) अणु
		mdelay(100);
	पूर्ण
	AscStopChip(iop_base);
	AscSetChipControl(iop_base, CC_CHIP_RESET | CC_SCSI_RESET | CC_HALT);
	udelay(60);
	AscSetChipIH(iop_base, INS_RFLAG_WTM);
	AscSetChipIH(iop_base, INS_HALT);
	AscSetChipControl(iop_base, CC_CHIP_RESET | CC_HALT);
	AscSetChipControl(iop_base, CC_HALT);
	mdelay(200);
	AscSetChipStatus(iop_base, CIW_CLR_SCSI_RESET_INT);
	AscSetChipStatus(iop_base, 0);
	वापस (AscIsChipHalted(iop_base));
पूर्ण

अटल पूर्णांक AscFindSignature(PortAddr iop_base)
अणु
	uलघु sig_word;

	ASC_DBG(1, "AscGetChipSignatureByte(0x%x) 0x%x\n",
		 iop_base, AscGetChipSignatureByte(iop_base));
	अगर (AscGetChipSignatureByte(iop_base) == (uअक्षर)ASC_1000_ID1B) अणु
		ASC_DBG(1, "AscGetChipSignatureWord(0x%x) 0x%x\n",
			 iop_base, AscGetChipSignatureWord(iop_base));
		sig_word = AscGetChipSignatureWord(iop_base);
		अगर ((sig_word == (uलघु)ASC_1000_ID0W) ||
		    (sig_word == (uलघु)ASC_1000_ID0W_FIX)) अणु
			वापस (1);
		पूर्ण
	पूर्ण
	वापस (0);
पूर्ण

अटल व्योम AscEnableInterrupt(PortAddr iop_base)
अणु
	uलघु cfg;

	cfg = AscGetChipCfgLsw(iop_base);
	AscSetChipCfgLsw(iop_base, cfg | ASC_CFG0_HOST_INT_ON);
पूर्ण

अटल व्योम AscDisableInterrupt(PortAddr iop_base)
अणु
	uलघु cfg;

	cfg = AscGetChipCfgLsw(iop_base);
	AscSetChipCfgLsw(iop_base, cfg & (~ASC_CFG0_HOST_INT_ON));
पूर्ण

अटल uअक्षर AscReadLramByte(PortAddr iop_base, uलघु addr)
अणु
	अचिन्हित अक्षर byte_data;
	अचिन्हित लघु word_data;

	अगर (isodd_word(addr)) अणु
		AscSetChipLramAddr(iop_base, addr - 1);
		word_data = AscGetChipLramData(iop_base);
		byte_data = (word_data >> 8) & 0xFF;
	पूर्ण अन्यथा अणु
		AscSetChipLramAddr(iop_base, addr);
		word_data = AscGetChipLramData(iop_base);
		byte_data = word_data & 0xFF;
	पूर्ण
	वापस byte_data;
पूर्ण

अटल uलघु AscReadLramWord(PortAddr iop_base, uलघु addr)
अणु
	uलघु word_data;

	AscSetChipLramAddr(iop_base, addr);
	word_data = AscGetChipLramData(iop_base);
	वापस (word_data);
पूर्ण

अटल व्योम
AscMemWordSetLram(PortAddr iop_base, uलघु s_addr, uलघु set_wval, पूर्णांक words)
अणु
	पूर्णांक i;

	AscSetChipLramAddr(iop_base, s_addr);
	क्रम (i = 0; i < words; i++) अणु
		AscSetChipLramData(iop_base, set_wval);
	पूर्ण
पूर्ण

अटल व्योम AscWriteLramWord(PortAddr iop_base, uलघु addr, uलघु word_val)
अणु
	AscSetChipLramAddr(iop_base, addr);
	AscSetChipLramData(iop_base, word_val);
पूर्ण

अटल व्योम AscWriteLramByte(PortAddr iop_base, uलघु addr, uअक्षर byte_val)
अणु
	uलघु word_data;

	अगर (isodd_word(addr)) अणु
		addr--;
		word_data = AscReadLramWord(iop_base, addr);
		word_data &= 0x00FF;
		word_data |= (((uलघु)byte_val << 8) & 0xFF00);
	पूर्ण अन्यथा अणु
		word_data = AscReadLramWord(iop_base, addr);
		word_data &= 0xFF00;
		word_data |= ((uलघु)byte_val & 0x00FF);
	पूर्ण
	AscWriteLramWord(iop_base, addr, word_data);
पूर्ण

/*
 * Copy 2 bytes to LRAM.
 *
 * The source data is assumed to be in little-endian order in memory
 * and is मुख्यtained in little-endian order when written to LRAM.
 */
अटल व्योम
AscMemWordCopyPtrToLram(PortAddr iop_base, uलघु s_addr,
			स्थिर uअक्षर *s_buffer, पूर्णांक words)
अणु
	पूर्णांक i;

	AscSetChipLramAddr(iop_base, s_addr);
	क्रम (i = 0; i < 2 * words; i += 2) अणु
		/*
		 * On a little-endian प्रणाली the second argument below
		 * produces a little-endian uलघु which is written to
		 * LRAM in little-endian order. On a big-endian प्रणाली
		 * the second argument produces a big-endian uलघु which
		 * is "transparently" byte-swapped by outpw() and written
		 * in little-endian order to LRAM.
		 */
		outpw(iop_base + IOP_RAM_DATA,
		      ((uलघु)s_buffer[i + 1] << 8) | s_buffer[i]);
	पूर्ण
पूर्ण

/*
 * Copy 4 bytes to LRAM.
 *
 * The source data is assumed to be in little-endian order in memory
 * and is मुख्यtained in little-endian order when written to LRAM.
 */
अटल व्योम
AscMemDWordCopyPtrToLram(PortAddr iop_base,
			 uलघु s_addr, uअक्षर *s_buffer, पूर्णांक dwords)
अणु
	पूर्णांक i;

	AscSetChipLramAddr(iop_base, s_addr);
	क्रम (i = 0; i < 4 * dwords; i += 4) अणु
		outpw(iop_base + IOP_RAM_DATA, ((uलघु)s_buffer[i + 1] << 8) | s_buffer[i]);	/* LSW */
		outpw(iop_base + IOP_RAM_DATA, ((uलघु)s_buffer[i + 3] << 8) | s_buffer[i + 2]);	/* MSW */
	पूर्ण
पूर्ण

/*
 * Copy 2 bytes from LRAM.
 *
 * The source data is assumed to be in little-endian order in LRAM
 * and is मुख्यtained in little-endian order when written to memory.
 */
अटल व्योम
AscMemWordCopyPtrFromLram(PortAddr iop_base,
			  uलघु s_addr, uअक्षर *d_buffer, पूर्णांक words)
अणु
	पूर्णांक i;
	uलघु word;

	AscSetChipLramAddr(iop_base, s_addr);
	क्रम (i = 0; i < 2 * words; i += 2) अणु
		word = inpw(iop_base + IOP_RAM_DATA);
		d_buffer[i] = word & 0xff;
		d_buffer[i + 1] = (word >> 8) & 0xff;
	पूर्ण
पूर्ण

अटल u32 AscMemSumLramWord(PortAddr iop_base, uलघु s_addr, पूर्णांक words)
अणु
	u32 sum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < words; i++, s_addr += 2) अणु
		sum += AscReadLramWord(iop_base, s_addr);
	पूर्ण
	वापस (sum);
पूर्ण

अटल व्योम AscInitLram(ASC_DVC_VAR *asc_dvc)
अणु
	uअक्षर i;
	uलघु s_addr;
	PortAddr iop_base;

	iop_base = asc_dvc->iop_base;
	AscMemWordSetLram(iop_base, ASC_QADR_BEG, 0,
			  (uलघु)(((पूर्णांक)(asc_dvc->max_total_qng + 2 + 1) *
				    64) >> 1));
	i = ASC_MIN_ACTIVE_QNO;
	s_addr = ASC_QADR_BEG + ASC_QBLK_SIZE;
	AscWriteLramByte(iop_base, (uलघु)(s_addr + ASC_SCSIQ_B_FWD),
			 (uअक्षर)(i + 1));
	AscWriteLramByte(iop_base, (uलघु)(s_addr + ASC_SCSIQ_B_BWD),
			 (uअक्षर)(asc_dvc->max_total_qng));
	AscWriteLramByte(iop_base, (uलघु)(s_addr + ASC_SCSIQ_B_QNO),
			 (uअक्षर)i);
	i++;
	s_addr += ASC_QBLK_SIZE;
	क्रम (; i < asc_dvc->max_total_qng; i++, s_addr += ASC_QBLK_SIZE) अणु
		AscWriteLramByte(iop_base, (uलघु)(s_addr + ASC_SCSIQ_B_FWD),
				 (uअक्षर)(i + 1));
		AscWriteLramByte(iop_base, (uलघु)(s_addr + ASC_SCSIQ_B_BWD),
				 (uअक्षर)(i - 1));
		AscWriteLramByte(iop_base, (uलघु)(s_addr + ASC_SCSIQ_B_QNO),
				 (uअक्षर)i);
	पूर्ण
	AscWriteLramByte(iop_base, (uलघु)(s_addr + ASC_SCSIQ_B_FWD),
			 (uअक्षर)ASC_QLINK_END);
	AscWriteLramByte(iop_base, (uलघु)(s_addr + ASC_SCSIQ_B_BWD),
			 (uअक्षर)(asc_dvc->max_total_qng - 1));
	AscWriteLramByte(iop_base, (uलघु)(s_addr + ASC_SCSIQ_B_QNO),
			 (uअक्षर)asc_dvc->max_total_qng);
	i++;
	s_addr += ASC_QBLK_SIZE;
	क्रम (; i <= (uअक्षर)(asc_dvc->max_total_qng + 3);
	     i++, s_addr += ASC_QBLK_SIZE) अणु
		AscWriteLramByte(iop_base,
				 (uलघु)(s_addr + (uलघु)ASC_SCSIQ_B_FWD), i);
		AscWriteLramByte(iop_base,
				 (uलघु)(s_addr + (uलघु)ASC_SCSIQ_B_BWD), i);
		AscWriteLramByte(iop_base,
				 (uलघु)(s_addr + (uलघु)ASC_SCSIQ_B_QNO), i);
	पूर्ण
पूर्ण

अटल u32
AscLoadMicroCode(PortAddr iop_base, uलघु s_addr,
		 स्थिर uअक्षर *mcode_buf, uलघु mcode_size)
अणु
	u32 chksum;
	uलघु mcode_word_size;
	uलघु mcode_chksum;

	/* Write the microcode buffer starting at LRAM address 0. */
	mcode_word_size = (uलघु)(mcode_size >> 1);
	AscMemWordSetLram(iop_base, s_addr, 0, mcode_word_size);
	AscMemWordCopyPtrToLram(iop_base, s_addr, mcode_buf, mcode_word_size);

	chksum = AscMemSumLramWord(iop_base, s_addr, mcode_word_size);
	ASC_DBG(1, "chksum 0x%lx\n", (uदीर्घ)chksum);
	mcode_chksum = (uलघु)AscMemSumLramWord(iop_base,
						 (uलघु)ASC_CODE_SEC_BEG,
						 (uलघु)((mcode_size -
							   s_addr - (uलघु)
							   ASC_CODE_SEC_BEG) /
							  2));
	ASC_DBG(1, "mcode_chksum 0x%lx\n", (uदीर्घ)mcode_chksum);
	AscWriteLramWord(iop_base, ASCV_MCODE_CHKSUM_W, mcode_chksum);
	AscWriteLramWord(iop_base, ASCV_MCODE_SIZE_W, mcode_size);
	वापस chksum;
पूर्ण

अटल व्योम AscInitQLinkVar(ASC_DVC_VAR *asc_dvc)
अणु
	PortAddr iop_base;
	पूर्णांक i;
	uलघु lram_addr;

	iop_base = asc_dvc->iop_base;
	AscPutRiscVarFreeQHead(iop_base, 1);
	AscPutRiscVarDoneQTail(iop_base, asc_dvc->max_total_qng);
	AscPutVarFreeQHead(iop_base, 1);
	AscPutVarDoneQTail(iop_base, asc_dvc->max_total_qng);
	AscWriteLramByte(iop_base, ASCV_BUSY_QHEAD_B,
			 (uअक्षर)((पूर्णांक)asc_dvc->max_total_qng + 1));
	AscWriteLramByte(iop_base, ASCV_DISC1_QHEAD_B,
			 (uअक्षर)((पूर्णांक)asc_dvc->max_total_qng + 2));
	AscWriteLramByte(iop_base, (uलघु)ASCV_TOTAL_READY_Q_B,
			 asc_dvc->max_total_qng);
	AscWriteLramWord(iop_base, ASCV_ASCDVC_ERR_CODE_W, 0);
	AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
	AscWriteLramByte(iop_base, ASCV_STOP_CODE_B, 0);
	AscWriteLramByte(iop_base, ASCV_SCSIBUSY_B, 0);
	AscWriteLramByte(iop_base, ASCV_WTM_FLAG_B, 0);
	AscPutQDoneInProgress(iop_base, 0);
	lram_addr = ASC_QADR_BEG;
	क्रम (i = 0; i < 32; i++, lram_addr += 2) अणु
		AscWriteLramWord(iop_base, lram_addr, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक AscInitMicroCodeVar(ASC_DVC_VAR *asc_dvc)
अणु
	पूर्णांक i;
	पूर्णांक warn_code;
	PortAddr iop_base;
	__le32 phy_addr;
	__le32 phy_size;
	काष्ठा asc_board *board = asc_dvc_to_board(asc_dvc);

	iop_base = asc_dvc->iop_base;
	warn_code = 0;
	क्रम (i = 0; i <= ASC_MAX_TID; i++) अणु
		AscPutMCodeInitSDTRAtID(iop_base, i,
					asc_dvc->cfg->sdtr_period_offset[i]);
	पूर्ण

	AscInitQLinkVar(asc_dvc);
	AscWriteLramByte(iop_base, ASCV_DISC_ENABLE_B,
			 asc_dvc->cfg->disc_enable);
	AscWriteLramByte(iop_base, ASCV_HOSTSCSI_ID_B,
			 ASC_TID_TO_TARGET_ID(asc_dvc->cfg->chip_scsi_id));

	/* Ensure overrun buffer is aligned on an 8 byte boundary. */
	BUG_ON((अचिन्हित दीर्घ)asc_dvc->overrun_buf & 7);
	asc_dvc->overrun_dma = dma_map_single(board->dev, asc_dvc->overrun_buf,
					ASC_OVERRUN_BSIZE, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(board->dev, asc_dvc->overrun_dma)) अणु
		warn_code = -ENOMEM;
		जाओ err_dma_map;
	पूर्ण
	phy_addr = cpu_to_le32(asc_dvc->overrun_dma);
	AscMemDWordCopyPtrToLram(iop_base, ASCV_OVERRUN_PADDR_D,
				 (uअक्षर *)&phy_addr, 1);
	phy_size = cpu_to_le32(ASC_OVERRUN_BSIZE);
	AscMemDWordCopyPtrToLram(iop_base, ASCV_OVERRUN_BSIZE_D,
				 (uअक्षर *)&phy_size, 1);

	asc_dvc->cfg->mcode_date =
	    AscReadLramWord(iop_base, (uलघु)ASCV_MC_DATE_W);
	asc_dvc->cfg->mcode_version =
	    AscReadLramWord(iop_base, (uलघु)ASCV_MC_VER_W);

	AscSetPCAddr(iop_base, ASC_MCODE_START_ADDR);
	अगर (AscGetPCAddr(iop_base) != ASC_MCODE_START_ADDR) अणु
		asc_dvc->err_code |= ASC_IERR_SET_PC_ADDR;
		warn_code = -EINVAL;
		जाओ err_mcode_start;
	पूर्ण
	अगर (AscStartChip(iop_base) != 1) अणु
		asc_dvc->err_code |= ASC_IERR_START_STOP_CHIP;
		warn_code = -EIO;
		जाओ err_mcode_start;
	पूर्ण

	वापस warn_code;

err_mcode_start:
	dma_unmap_single(board->dev, asc_dvc->overrun_dma,
			 ASC_OVERRUN_BSIZE, DMA_FROM_DEVICE);
err_dma_map:
	asc_dvc->overrun_dma = 0;
	वापस warn_code;
पूर्ण

अटल पूर्णांक AscInitAsc1000Driver(ASC_DVC_VAR *asc_dvc)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर fwname[] = "advansys/mcode.bin";
	पूर्णांक err;
	अचिन्हित दीर्घ chksum;
	पूर्णांक warn_code;
	PortAddr iop_base;

	iop_base = asc_dvc->iop_base;
	warn_code = 0;
	अगर ((asc_dvc->dvc_cntl & ASC_CNTL_RESET_SCSI) &&
	    !(asc_dvc->init_state & ASC_INIT_RESET_SCSI_DONE)) अणु
		AscResetChipAndScsiBus(asc_dvc);
		mdelay(asc_dvc->scsi_reset_रुको * 1000); /* XXX: msleep? */
	पूर्ण
	asc_dvc->init_state |= ASC_INIT_STATE_BEG_LOAD_MC;
	अगर (asc_dvc->err_code != 0)
		वापस ASC_ERROR;
	अगर (!AscFindSignature(asc_dvc->iop_base)) अणु
		asc_dvc->err_code = ASC_IERR_BAD_SIGNATURE;
		वापस warn_code;
	पूर्ण
	AscDisableInterrupt(iop_base);
	AscInitLram(asc_dvc);

	err = request_firmware(&fw, fwname, asc_dvc->drv_ptr->dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Failed to load image \"%s\" err %d\n",
		       fwname, err);
		asc_dvc->err_code |= ASC_IERR_MCODE_CHKSUM;
		वापस err;
	पूर्ण
	अगर (fw->size < 4) अणु
		prपूर्णांकk(KERN_ERR "Bogus length %zu in image \"%s\"\n",
		       fw->size, fwname);
		release_firmware(fw);
		asc_dvc->err_code |= ASC_IERR_MCODE_CHKSUM;
		वापस -EINVAL;
	पूर्ण
	chksum = (fw->data[3] << 24) | (fw->data[2] << 16) |
		 (fw->data[1] << 8) | fw->data[0];
	ASC_DBG(1, "_asc_mcode_chksum 0x%lx\n", (uदीर्घ)chksum);
	अगर (AscLoadMicroCode(iop_base, 0, &fw->data[4],
			     fw->size - 4) != chksum) अणु
		asc_dvc->err_code |= ASC_IERR_MCODE_CHKSUM;
		release_firmware(fw);
		वापस warn_code;
	पूर्ण
	release_firmware(fw);
	warn_code |= AscInitMicroCodeVar(asc_dvc);
	अगर (!asc_dvc->overrun_dma)
		वापस warn_code;
	asc_dvc->init_state |= ASC_INIT_STATE_END_LOAD_MC;
	AscEnableInterrupt(iop_base);
	वापस warn_code;
पूर्ण

/*
 * Load the Microcode
 *
 * Write the microcode image to RISC memory starting at address 0.
 *
 * The microcode is stored compressed in the following क्रमmat:
 *
 *  254 word (508 byte) table indexed by byte code followed
 *  by the following byte codes:
 *
 *    1-Byte Code:
 *      00: Emit word 0 in table.
 *      01: Emit word 1 in table.
 *      .
 *      FD: Emit word 253 in table.
 *
 *    Multi-Byte Code:
 *      FE WW WW: (3 byte code) Word to emit is the next word WW WW.
 *      FF BB WW WW: (4 byte code) Emit BB count बार next word WW WW.
 *
 * Returns 0 or an error अगर the checksum करोesn't match
 */
अटल पूर्णांक AdvLoadMicrocode(AdvPortAddr iop_base, स्थिर अचिन्हित अक्षर *buf,
			    पूर्णांक size, पूर्णांक memsize, पूर्णांक chksum)
अणु
	पूर्णांक i, j, end, len = 0;
	u32 sum;

	AdvWriteWordRegister(iop_base, IOPW_RAM_ADDR, 0);

	क्रम (i = 253 * 2; i < size; i++) अणु
		अगर (buf[i] == 0xff) अणु
			अचिन्हित लघु word = (buf[i + 3] << 8) | buf[i + 2];
			क्रम (j = 0; j < buf[i + 1]; j++) अणु
				AdvWriteWordAutoIncLram(iop_base, word);
				len += 2;
			पूर्ण
			i += 3;
		पूर्ण अन्यथा अगर (buf[i] == 0xfe) अणु
			अचिन्हित लघु word = (buf[i + 2] << 8) | buf[i + 1];
			AdvWriteWordAutoIncLram(iop_base, word);
			i += 2;
			len += 2;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक off = buf[i] * 2;
			अचिन्हित लघु word = (buf[off + 1] << 8) | buf[off];
			AdvWriteWordAutoIncLram(iop_base, word);
			len += 2;
		पूर्ण
	पूर्ण

	end = len;

	जबतक (len < memsize) अणु
		AdvWriteWordAutoIncLram(iop_base, 0);
		len += 2;
	पूर्ण

	/* Verअगरy the microcode checksum. */
	sum = 0;
	AdvWriteWordRegister(iop_base, IOPW_RAM_ADDR, 0);

	क्रम (len = 0; len < end; len += 2) अणु
		sum += AdvReadWordAutoIncLram(iop_base);
	पूर्ण

	अगर (sum != chksum)
		वापस ASC_IERR_MCODE_CHKSUM;

	वापस 0;
पूर्ण

अटल व्योम AdvBuildCarrierFreelist(काष्ठा adv_dvc_var *adv_dvc)
अणु
	off_t carr_offset = 0, next_offset;
	dma_addr_t carr_paddr;
	पूर्णांक carr_num = ADV_CARRIER_बफ_मानE / माप(ADV_CARR_T), i;

	क्रम (i = 0; i < carr_num; i++) अणु
		carr_offset = i * माप(ADV_CARR_T);
		/* Get physical address of the carrier 'carrp'. */
		carr_paddr = adv_dvc->carrier_addr + carr_offset;

		adv_dvc->carrier[i].carr_pa = cpu_to_le32(carr_paddr);
		adv_dvc->carrier[i].carr_va = cpu_to_le32(carr_offset);
		adv_dvc->carrier[i].areq_vpa = 0;
		next_offset = carr_offset + माप(ADV_CARR_T);
		अगर (i == carr_num)
			next_offset = ~0;
		adv_dvc->carrier[i].next_vpa = cpu_to_le32(next_offset);
	पूर्ण
	/*
	 * We cannot have a carrier with 'carr_va' of '0', as
	 * a reference to this carrier would be पूर्णांकerpreted as
	 * list termination.
	 * So start at carrier 1 with the मुक्तlist.
	 */
	adv_dvc->carr_मुक्तlist = &adv_dvc->carrier[1];
पूर्ण

अटल ADV_CARR_T *adv_get_carrier(काष्ठा adv_dvc_var *adv_dvc, u32 offset)
अणु
	पूर्णांक index;

	BUG_ON(offset > ADV_CARRIER_बफ_मानE);

	index = offset / माप(ADV_CARR_T);
	वापस &adv_dvc->carrier[index];
पूर्ण

अटल ADV_CARR_T *adv_get_next_carrier(काष्ठा adv_dvc_var *adv_dvc)
अणु
	ADV_CARR_T *carrp = adv_dvc->carr_मुक्तlist;
	u32 next_vpa = le32_to_cpu(carrp->next_vpa);

	अगर (next_vpa == 0 || next_vpa == ~0) अणु
		ASC_DBG(1, "invalid vpa offset 0x%x\n", next_vpa);
		वापस शून्य;
	पूर्ण

	adv_dvc->carr_मुक्तlist = adv_get_carrier(adv_dvc, next_vpa);
	/*
	 * insert stopper carrier to terminate list
	 */
	carrp->next_vpa = cpu_to_le32(ADV_CQ_STOPPER);

	वापस carrp;
पूर्ण

/*
 * 'offset' is the index in the request poपूर्णांकer array
 */
अटल adv_req_t * adv_get_reqp(काष्ठा adv_dvc_var *adv_dvc, u32 offset)
अणु
	काष्ठा asc_board *boardp = adv_dvc->drv_ptr;

	BUG_ON(offset > adv_dvc->max_host_qng);
	वापस &boardp->adv_reqp[offset];
पूर्ण

/*
 * Send an idle command to the chip and रुको क्रम completion.
 *
 * Command completion is polled क्रम once per microsecond.
 *
 * The function can be called from anywhere including an पूर्णांकerrupt handler.
 * But the function is not re-entrant, so it uses the DvcEnter/LeaveCritical()
 * functions to prevent reentrancy.
 *
 * Return Values:
 *   ADV_TRUE - command completed successfully
 *   ADV_FALSE - command failed
 *   ADV_ERROR - command समयd out
 */
अटल पूर्णांक
AdvSendIdleCmd(ADV_DVC_VAR *asc_dvc,
	       uलघु idle_cmd, u32 idle_cmd_parameter)
अणु
	पूर्णांक result, i, j;
	AdvPortAddr iop_base;

	iop_base = asc_dvc->iop_base;

	/*
	 * Clear the idle command status which is set by the microcode
	 * to a non-zero value to indicate when the command is completed.
	 * The non-zero result is one of the IDLE_CMD_STATUS_* values
	 */
	AdvWriteWordLram(iop_base, ASC_MC_IDLE_CMD_STATUS, (uलघु)0);

	/*
	 * Write the idle command value after the idle command parameter
	 * has been written to aव्योम a race condition. If the order is not
	 * followed, the microcode may process the idle command beक्रमe the
	 * parameters have been written to LRAM.
	 */
	AdvWriteDWordLramNoSwap(iop_base, ASC_MC_IDLE_CMD_PARAMETER,
				cpu_to_le32(idle_cmd_parameter));
	AdvWriteWordLram(iop_base, ASC_MC_IDLE_CMD, idle_cmd);

	/*
	 * Tickle the RISC to tell it to process the idle command.
	 */
	AdvWriteByteRegister(iop_base, IOPB_TICKLE, ADV_TICKLE_B);
	अगर (asc_dvc->chip_type == ADV_CHIP_ASC3550) अणु
		/*
		 * Clear the tickle value. In the ASC-3550 the RISC flag
		 * command 'clr_tickle_b' करोes not work unless the host
		 * value is cleared.
		 */
		AdvWriteByteRegister(iop_base, IOPB_TICKLE, ADV_TICKLE_NOP);
	पूर्ण

	/* Wait क्रम up to 100 millisecond क्रम the idle command to समयout. */
	क्रम (i = 0; i < SCSI_WAIT_100_MSEC; i++) अणु
		/* Poll once each microsecond क्रम command completion. */
		क्रम (j = 0; j < SCSI_US_PER_MSEC; j++) अणु
			AdvReadWordLram(iop_base, ASC_MC_IDLE_CMD_STATUS,
					result);
			अगर (result != 0)
				वापस result;
			udelay(1);
		पूर्ण
	पूर्ण

	BUG();		/* The idle command should never समयout. */
	वापस ADV_ERROR;
पूर्ण

/*
 * Reset SCSI Bus and purge all outstanding requests.
 *
 * Return Value:
 *      ADV_TRUE(1) -   All requests are purged and SCSI Bus is reset.
 *      ADV_FALSE(0) -  Microcode command failed.
 *      ADV_ERROR(-1) - Microcode command समयd-out. Microcode or IC
 *                      may be hung which requires driver recovery.
 */
अटल पूर्णांक AdvResetSB(ADV_DVC_VAR *asc_dvc)
अणु
	पूर्णांक status;

	/*
	 * Send the SCSI Bus Reset idle start idle command which निश्चितs
	 * the SCSI Bus Reset संकेत.
	 */
	status = AdvSendIdleCmd(asc_dvc, (uलघु)IDLE_CMD_SCSI_RESET_START, 0L);
	अगर (status != ADV_TRUE) अणु
		वापस status;
	पूर्ण

	/*
	 * Delay क्रम the specअगरied SCSI Bus Reset hold समय.
	 *
	 * The hold समय delay is करोne on the host because the RISC has no
	 * microsecond accurate समयr.
	 */
	udelay(ASC_SCSI_RESET_HOLD_TIME_US);

	/*
	 * Send the SCSI Bus Reset end idle command which de-निश्चितs
	 * the SCSI Bus Reset संकेत and purges any pending requests.
	 */
	status = AdvSendIdleCmd(asc_dvc, (uलघु)IDLE_CMD_SCSI_RESET_END, 0L);
	अगर (status != ADV_TRUE) अणु
		वापस status;
	पूर्ण

	mdelay(asc_dvc->scsi_reset_रुको * 1000);	/* XXX: msleep? */

	वापस status;
पूर्ण

/*
 * Initialize the ASC-3550.
 *
 * On failure set the ADV_DVC_VAR field 'err_code' and वापस ADV_ERROR.
 *
 * For a non-fatal error वापस a warning code. If there are no warnings
 * then 0 is वापसed.
 *
 * Needed after initialization क्रम error recovery.
 */
अटल पूर्णांक AdvInitAsc3550Driver(ADV_DVC_VAR *asc_dvc)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर fwname[] = "advansys/3550.bin";
	AdvPortAddr iop_base;
	uलघु warn_code;
	पूर्णांक begin_addr;
	पूर्णांक end_addr;
	uलघु code_sum;
	पूर्णांक word;
	पूर्णांक i;
	पूर्णांक err;
	अचिन्हित दीर्घ chksum;
	uलघु scsi_cfg1;
	uअक्षर tid;
	uलघु bios_mem[ASC_MC_BIOSLEN / 2];	/* BIOS RISC Memory 0x40-0x8F. */
	uलघु wdtr_able = 0, sdtr_able, tagqng_able;
	uअक्षर max_cmd[ADV_MAX_TID + 1];

	/* If there is alपढ़ोy an error, करोn't जारी. */
	अगर (asc_dvc->err_code != 0)
		वापस ADV_ERROR;

	/*
	 * The caller must set 'chip_type' to ADV_CHIP_ASC3550.
	 */
	अगर (asc_dvc->chip_type != ADV_CHIP_ASC3550) अणु
		asc_dvc->err_code = ASC_IERR_BAD_CHIPTYPE;
		वापस ADV_ERROR;
	पूर्ण

	warn_code = 0;
	iop_base = asc_dvc->iop_base;

	/*
	 * Save the RISC memory BIOS region beक्रमe writing the microcode.
	 * The BIOS may alपढ़ोy be loaded and using its RISC LRAM region
	 * so its region must be saved and restored.
	 *
	 * Note: This code makes the assumption, which is currently true,
	 * that a chip reset करोes not clear RISC LRAM.
	 */
	क्रम (i = 0; i < ASC_MC_BIOSLEN / 2; i++) अणु
		AdvReadWordLram(iop_base, ASC_MC_BIOSMEM + (2 * i),
				bios_mem[i]);
	पूर्ण

	/*
	 * Save current per TID negotiated values.
	 */
	अगर (bios_mem[(ASC_MC_BIOS_SIGNATURE - ASC_MC_BIOSMEM) / 2] == 0x55AA) अणु
		uलघु bios_version, major, minor;

		bios_version =
		    bios_mem[(ASC_MC_BIOS_VERSION - ASC_MC_BIOSMEM) / 2];
		major = (bios_version >> 12) & 0xF;
		minor = (bios_version >> 8) & 0xF;
		अगर (major < 3 || (major == 3 && minor == 1)) अणु
			/* BIOS 3.1 and earlier location of 'wdtr_able' variable. */
			AdvReadWordLram(iop_base, 0x120, wdtr_able);
		पूर्ण अन्यथा अणु
			AdvReadWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
		पूर्ण
	पूर्ण
	AdvReadWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
	AdvReadWordLram(iop_base, ASC_MC_TAGQNG_ABLE, tagqng_able);
	क्रम (tid = 0; tid <= ADV_MAX_TID; tid++) अणु
		AdvReadByteLram(iop_base, ASC_MC_NUMBER_OF_MAX_CMD + tid,
				max_cmd[tid]);
	पूर्ण

	err = request_firmware(&fw, fwname, asc_dvc->drv_ptr->dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Failed to load image \"%s\" err %d\n",
		       fwname, err);
		asc_dvc->err_code = ASC_IERR_MCODE_CHKSUM;
		वापस err;
	पूर्ण
	अगर (fw->size < 4) अणु
		prपूर्णांकk(KERN_ERR "Bogus length %zu in image \"%s\"\n",
		       fw->size, fwname);
		release_firmware(fw);
		asc_dvc->err_code = ASC_IERR_MCODE_CHKSUM;
		वापस -EINVAL;
	पूर्ण
	chksum = (fw->data[3] << 24) | (fw->data[2] << 16) |
		 (fw->data[1] << 8) | fw->data[0];
	asc_dvc->err_code = AdvLoadMicrocode(iop_base, &fw->data[4],
					     fw->size - 4, ADV_3550_MEMSIZE,
					     chksum);
	release_firmware(fw);
	अगर (asc_dvc->err_code)
		वापस ADV_ERROR;

	/*
	 * Restore the RISC memory BIOS region.
	 */
	क्रम (i = 0; i < ASC_MC_BIOSLEN / 2; i++) अणु
		AdvWriteWordLram(iop_base, ASC_MC_BIOSMEM + (2 * i),
				 bios_mem[i]);
	पूर्ण

	/*
	 * Calculate and ग_लिखो the microcode code checksum to the microcode
	 * code checksum location ASC_MC_CODE_CHK_SUM (0x2C).
	 */
	AdvReadWordLram(iop_base, ASC_MC_CODE_BEGIN_ADDR, begin_addr);
	AdvReadWordLram(iop_base, ASC_MC_CODE_END_ADDR, end_addr);
	code_sum = 0;
	AdvWriteWordRegister(iop_base, IOPW_RAM_ADDR, begin_addr);
	क्रम (word = begin_addr; word < end_addr; word += 2) अणु
		code_sum += AdvReadWordAutoIncLram(iop_base);
	पूर्ण
	AdvWriteWordLram(iop_base, ASC_MC_CODE_CHK_SUM, code_sum);

	/*
	 * Read and save microcode version and date.
	 */
	AdvReadWordLram(iop_base, ASC_MC_VERSION_DATE,
			asc_dvc->cfg->mcode_date);
	AdvReadWordLram(iop_base, ASC_MC_VERSION_NUM,
			asc_dvc->cfg->mcode_version);

	/*
	 * Set the chip type to indicate the ASC3550.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_CHIP_TYPE, ADV_CHIP_ASC3550);

	/*
	 * If the PCI Configuration Command Register "Parity Error Response
	 * Control" Bit was clear (0), then set the microcode variable
	 * 'control_flag' CONTROL_FLAG_IGNORE_PERR flag to tell the microcode
	 * to ignore DMA parity errors.
	 */
	अगर (asc_dvc->cfg->control_flag & CONTROL_FLAG_IGNORE_PERR) अणु
		AdvReadWordLram(iop_base, ASC_MC_CONTROL_FLAG, word);
		word |= CONTROL_FLAG_IGNORE_PERR;
		AdvWriteWordLram(iop_base, ASC_MC_CONTROL_FLAG, word);
	पूर्ण

	/*
	 * For ASC-3550, setting the START_CTL_EMFU [3:2] bits sets a FIFO
	 * threshold of 128 bytes. This रेजिस्टर is only accessible to the host.
	 */
	AdvWriteByteRegister(iop_base, IOPB_DMA_CFG0,
			     START_CTL_EMFU | READ_CMD_MRM);

	/*
	 * Microcode operating variables क्रम WDTR, SDTR, and command tag
	 * queuing will be set in slave_configure() based on what a
	 * device reports it is capable of in Inquiry byte 7.
	 *
	 * If SCSI Bus Resets have been disabled, then directly set
	 * SDTR and WDTR from the EEPROM configuration. This will allow
	 * the BIOS and warm boot to work without a SCSI bus hang on
	 * the Inquiry caused by host and target mismatched DTR values.
	 * Without the SCSI Bus Reset, beक्रमe an Inquiry a device can't
	 * be assumed to be in Asynchronous, Narrow mode.
	 */
	अगर ((asc_dvc->bios_ctrl & BIOS_CTRL_RESET_SCSI_BUS) == 0) अणु
		AdvWriteWordLram(iop_base, ASC_MC_WDTR_ABLE,
				 asc_dvc->wdtr_able);
		AdvWriteWordLram(iop_base, ASC_MC_SDTR_ABLE,
				 asc_dvc->sdtr_able);
	पूर्ण

	/*
	 * Set microcode operating variables क्रम SDTR_SPEED1, SDTR_SPEED2,
	 * SDTR_SPEED3, and SDTR_SPEED4 based on the ULTRA EEPROM per TID
	 * biपंचांगask. These values determine the maximum SDTR speed negotiated
	 * with a device.
	 *
	 * The SDTR per TID biपंचांगask overrides the SDTR_SPEED1, SDTR_SPEED2,
	 * SDTR_SPEED3, and SDTR_SPEED4 values so it is safe to set them
	 * without determining here whether the device supports SDTR.
	 *
	 * 4-bit speed  SDTR speed name
	 * ===========  ===============
	 * 0000b (0x0)  SDTR disabled
	 * 0001b (0x1)  5 Mhz
	 * 0010b (0x2)  10 Mhz
	 * 0011b (0x3)  20 Mhz (Ultra)
	 * 0100b (0x4)  40 Mhz (LVD/Ultra2)
	 * 0101b (0x5)  80 Mhz (LVD2/Ultra3)
	 * 0110b (0x6)  Undefined
	 * .
	 * 1111b (0xF)  Undefined
	 */
	word = 0;
	क्रम (tid = 0; tid <= ADV_MAX_TID; tid++) अणु
		अगर (ADV_TID_TO_TIDMASK(tid) & asc_dvc->ultra_able) अणु
			/* Set Ultra speed क्रम TID 'tid'. */
			word |= (0x3 << (4 * (tid % 4)));
		पूर्ण अन्यथा अणु
			/* Set Fast speed क्रम TID 'tid'. */
			word |= (0x2 << (4 * (tid % 4)));
		पूर्ण
		अगर (tid == 3) अणु	/* Check अगर करोne with sdtr_speed1. */
			AdvWriteWordLram(iop_base, ASC_MC_SDTR_SPEED1, word);
			word = 0;
		पूर्ण अन्यथा अगर (tid == 7) अणु	/* Check अगर करोne with sdtr_speed2. */
			AdvWriteWordLram(iop_base, ASC_MC_SDTR_SPEED2, word);
			word = 0;
		पूर्ण अन्यथा अगर (tid == 11) अणु	/* Check अगर करोne with sdtr_speed3. */
			AdvWriteWordLram(iop_base, ASC_MC_SDTR_SPEED3, word);
			word = 0;
		पूर्ण अन्यथा अगर (tid == 15) अणु	/* Check अगर करोne with sdtr_speed4. */
			AdvWriteWordLram(iop_base, ASC_MC_SDTR_SPEED4, word);
			/* End of loop. */
		पूर्ण
	पूर्ण

	/*
	 * Set microcode operating variable क्रम the disconnect per TID biपंचांगask.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DISC_ENABLE,
			 asc_dvc->cfg->disc_enable);

	/*
	 * Set SCSI_CFG0 Microcode Default Value.
	 *
	 * The microcode will set the SCSI_CFG0 रेजिस्टर using this value
	 * after it is started below.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_SCSI_CFG0,
			 PARITY_EN | QUEUE_128 | SEL_TMO_LONG | OUR_ID_EN |
			 asc_dvc->chip_scsi_id);

	/*
	 * Determine SCSI_CFG1 Microcode Default Value.
	 *
	 * The microcode will set the SCSI_CFG1 रेजिस्टर using this value
	 * after it is started below.
	 */

	/* Read current SCSI_CFG1 Register value. */
	scsi_cfg1 = AdvReadWordRegister(iop_base, IOPW_SCSI_CFG1);

	/*
	 * If all three connectors are in use, वापस an error.
	 */
	अगर ((scsi_cfg1 & CABLE_ILLEGAL_A) == 0 ||
	    (scsi_cfg1 & CABLE_ILLEGAL_B) == 0) अणु
		asc_dvc->err_code |= ASC_IERR_ILLEGAL_CONNECTION;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * If the पूर्णांकernal narrow cable is reversed all of the SCSI_CTRL
	 * रेजिस्टर संकेतs will be set. Check क्रम and वापस an error अगर
	 * this condition is found.
	 */
	अगर ((AdvReadWordRegister(iop_base, IOPW_SCSI_CTRL) & 0x3F07) == 0x3F07) अणु
		asc_dvc->err_code |= ASC_IERR_REVERSED_CABLE;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * If this is a dअगरferential board and a single-ended device
	 * is attached to one of the connectors, वापस an error.
	 */
	अगर ((scsi_cfg1 & DIFF_MODE) && (scsi_cfg1 & DIFF_SENSE) == 0) अणु
		asc_dvc->err_code |= ASC_IERR_SINGLE_END_DEVICE;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * If स्वतःmatic termination control is enabled, then set the
	 * termination value based on a table listed in a_conकरोr.h.
	 *
	 * If manual termination was specअगरied with an EEPROM setting
	 * then 'termination' was set-up in AdvInitFrom3550EEPROM() and
	 * is पढ़ोy to be 'ored' पूर्णांकo SCSI_CFG1.
	 */
	अगर (asc_dvc->cfg->termination == 0) अणु
		/*
		 * The software always controls termination by setting TERM_CTL_SEL.
		 * If TERM_CTL_SEL were set to 0, the hardware would set termination.
		 */
		asc_dvc->cfg->termination |= TERM_CTL_SEL;

		चयन (scsi_cfg1 & CABLE_DETECT) अणु
			/* TERM_CTL_H: on, TERM_CTL_L: on */
		हाल 0x3:
		हाल 0x7:
		हाल 0xB:
		हाल 0xD:
		हाल 0xE:
		हाल 0xF:
			asc_dvc->cfg->termination |= (TERM_CTL_H | TERM_CTL_L);
			अवरोध;

			/* TERM_CTL_H: on, TERM_CTL_L: off */
		हाल 0x1:
		हाल 0x5:
		हाल 0x9:
		हाल 0xA:
		हाल 0xC:
			asc_dvc->cfg->termination |= TERM_CTL_H;
			अवरोध;

			/* TERM_CTL_H: off, TERM_CTL_L: off */
		हाल 0x2:
		हाल 0x6:
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Clear any set TERM_CTL_H and TERM_CTL_L bits.
	 */
	scsi_cfg1 &= ~TERM_CTL;

	/*
	 * Invert the TERM_CTL_H and TERM_CTL_L bits and then
	 * set 'scsi_cfg1'. The TERM_POL bit करोes not need to be
	 * referenced, because the hardware पूर्णांकernally inverts
	 * the Termination High and Low bits अगर TERM_POL is set.
	 */
	scsi_cfg1 |= (TERM_CTL_SEL | (~asc_dvc->cfg->termination & TERM_CTL));

	/*
	 * Set SCSI_CFG1 Microcode Default Value
	 *
	 * Set filter value and possibly modअगरied termination control
	 * bits in the Microcode SCSI_CFG1 Register Value.
	 *
	 * The microcode will set the SCSI_CFG1 रेजिस्टर using this value
	 * after it is started below.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_SCSI_CFG1,
			 FLTR_DISABLE | scsi_cfg1);

	/*
	 * Set MEM_CFG Microcode Default Value
	 *
	 * The microcode will set the MEM_CFG रेजिस्टर using this value
	 * after it is started below.
	 *
	 * MEM_CFG may be accessed as a word or byte, but only bits 0-7
	 * are defined.
	 *
	 * ASC-3550 has 8KB पूर्णांकernal memory.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_MEM_CFG,
			 BIOS_EN | RAM_SZ_8KB);

	/*
	 * Set SEL_MASK Microcode Default Value
	 *
	 * The microcode will set the SEL_MASK रेजिस्टर using this value
	 * after it is started below.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_SEL_MASK,
			 ADV_TID_TO_TIDMASK(asc_dvc->chip_scsi_id));

	AdvBuildCarrierFreelist(asc_dvc);

	/*
	 * Set-up the Host->RISC Initiator Command Queue (ICQ).
	 */

	asc_dvc->icq_sp = adv_get_next_carrier(asc_dvc);
	अगर (!asc_dvc->icq_sp) अणु
		asc_dvc->err_code |= ASC_IERR_NO_CARRIER;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * Set RISC ICQ physical address start value.
	 */
	AdvWriteDWordLramNoSwap(iop_base, ASC_MC_ICQ, asc_dvc->icq_sp->carr_pa);

	/*
	 * Set-up the RISC->Host Initiator Response Queue (IRQ).
	 */
	asc_dvc->irq_sp = adv_get_next_carrier(asc_dvc);
	अगर (!asc_dvc->irq_sp) अणु
		asc_dvc->err_code |= ASC_IERR_NO_CARRIER;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * Set RISC IRQ physical address start value.
	 */
	AdvWriteDWordLramNoSwap(iop_base, ASC_MC_IRQ, asc_dvc->irq_sp->carr_pa);
	asc_dvc->carr_pending_cnt = 0;

	AdvWriteByteRegister(iop_base, IOPB_INTR_ENABLES,
			     (ADV_INTR_ENABLE_HOST_INTR |
			      ADV_INTR_ENABLE_GLOBAL_INTR));

	AdvReadWordLram(iop_base, ASC_MC_CODE_BEGIN_ADDR, word);
	AdvWriteWordRegister(iop_base, IOPW_PC, word);

	/* finally, finally, gentlemen, start your engine */
	AdvWriteWordRegister(iop_base, IOPW_RISC_CSR, ADV_RISC_CSR_RUN);

	/*
	 * Reset the SCSI Bus अगर the EEPROM indicates that SCSI Bus
	 * Resets should be perक्रमmed. The RISC has to be running
	 * to issue a SCSI Bus Reset.
	 */
	अगर (asc_dvc->bios_ctrl & BIOS_CTRL_RESET_SCSI_BUS) अणु
		/*
		 * If the BIOS Signature is present in memory, restore the
		 * BIOS Handshake Configuration Table and करो not perक्रमm
		 * a SCSI Bus Reset.
		 */
		अगर (bios_mem[(ASC_MC_BIOS_SIGNATURE - ASC_MC_BIOSMEM) / 2] ==
		    0x55AA) अणु
			/*
			 * Restore per TID negotiated values.
			 */
			AdvWriteWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
			AdvWriteWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
			AdvWriteWordLram(iop_base, ASC_MC_TAGQNG_ABLE,
					 tagqng_able);
			क्रम (tid = 0; tid <= ADV_MAX_TID; tid++) अणु
				AdvWriteByteLram(iop_base,
						 ASC_MC_NUMBER_OF_MAX_CMD + tid,
						 max_cmd[tid]);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (AdvResetSB(asc_dvc) != ADV_TRUE) अणु
				warn_code = ASC_WARN_BUSRESET_ERROR;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस warn_code;
पूर्ण

/*
 * Initialize the ASC-38C0800.
 *
 * On failure set the ADV_DVC_VAR field 'err_code' and वापस ADV_ERROR.
 *
 * For a non-fatal error वापस a warning code. If there are no warnings
 * then 0 is वापसed.
 *
 * Needed after initialization क्रम error recovery.
 */
अटल पूर्णांक AdvInitAsc38C0800Driver(ADV_DVC_VAR *asc_dvc)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर fwname[] = "advansys/38C0800.bin";
	AdvPortAddr iop_base;
	uलघु warn_code;
	पूर्णांक begin_addr;
	पूर्णांक end_addr;
	uलघु code_sum;
	पूर्णांक word;
	पूर्णांक i;
	पूर्णांक err;
	अचिन्हित दीर्घ chksum;
	uलघु scsi_cfg1;
	uअक्षर byte;
	uअक्षर tid;
	uलघु bios_mem[ASC_MC_BIOSLEN / 2];	/* BIOS RISC Memory 0x40-0x8F. */
	uलघु wdtr_able, sdtr_able, tagqng_able;
	uअक्षर max_cmd[ADV_MAX_TID + 1];

	/* If there is alपढ़ोy an error, करोn't जारी. */
	अगर (asc_dvc->err_code != 0)
		वापस ADV_ERROR;

	/*
	 * The caller must set 'chip_type' to ADV_CHIP_ASC38C0800.
	 */
	अगर (asc_dvc->chip_type != ADV_CHIP_ASC38C0800) अणु
		asc_dvc->err_code = ASC_IERR_BAD_CHIPTYPE;
		वापस ADV_ERROR;
	पूर्ण

	warn_code = 0;
	iop_base = asc_dvc->iop_base;

	/*
	 * Save the RISC memory BIOS region beक्रमe writing the microcode.
	 * The BIOS may alपढ़ोy be loaded and using its RISC LRAM region
	 * so its region must be saved and restored.
	 *
	 * Note: This code makes the assumption, which is currently true,
	 * that a chip reset करोes not clear RISC LRAM.
	 */
	क्रम (i = 0; i < ASC_MC_BIOSLEN / 2; i++) अणु
		AdvReadWordLram(iop_base, ASC_MC_BIOSMEM + (2 * i),
				bios_mem[i]);
	पूर्ण

	/*
	 * Save current per TID negotiated values.
	 */
	AdvReadWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
	AdvReadWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
	AdvReadWordLram(iop_base, ASC_MC_TAGQNG_ABLE, tagqng_able);
	क्रम (tid = 0; tid <= ADV_MAX_TID; tid++) अणु
		AdvReadByteLram(iop_base, ASC_MC_NUMBER_OF_MAX_CMD + tid,
				max_cmd[tid]);
	पूर्ण

	/*
	 * RAM BIST (RAM Built-In Self Test)
	 *
	 * Address : I/O base + offset 0x38h रेजिस्टर (byte).
	 * Function: Bit 7-6(RW) : RAM mode
	 *                          Normal Mode   : 0x00
	 *                          Pre-test Mode : 0x40
	 *                          RAM Test Mode : 0x80
	 *           Bit 5       : unused
	 *           Bit 4(RO)   : Done bit
	 *           Bit 3-0(RO) : Status
	 *                          Host Error    : 0x08
	 *                          Int_RAM Error : 0x04
	 *                          RISC Error    : 0x02
	 *                          SCSI Error    : 0x01
	 *                          No Error      : 0x00
	 *
	 * Note: RAM BIST code should be put right here, beक्रमe loading the
	 * microcode and after saving the RISC memory BIOS region.
	 */

	/*
	 * LRAM Pre-test
	 *
	 * Write PRE_TEST_MODE (0x40) to रेजिस्टर and रुको क्रम 10 milliseconds.
	 * If Done bit not set or low nibble not PRE_TEST_VALUE (0x05), वापस
	 * an error. Reset to NORMAL_MODE (0x00) and करो again. If cannot reset
	 * to NORMAL_MODE, वापस an error too.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		AdvWriteByteRegister(iop_base, IOPB_RAM_BIST, PRE_TEST_MODE);
		mdelay(10);	/* Wait क्रम 10ms beक्रमe पढ़ोing back. */
		byte = AdvReadByteRegister(iop_base, IOPB_RAM_BIST);
		अगर ((byte & RAM_TEST_DONE) == 0
		    || (byte & 0x0F) != PRE_TEST_VALUE) अणु
			asc_dvc->err_code = ASC_IERR_BIST_PRE_TEST;
			वापस ADV_ERROR;
		पूर्ण

		AdvWriteByteRegister(iop_base, IOPB_RAM_BIST, NORMAL_MODE);
		mdelay(10);	/* Wait क्रम 10ms beक्रमe पढ़ोing back. */
		अगर (AdvReadByteRegister(iop_base, IOPB_RAM_BIST)
		    != NORMAL_VALUE) अणु
			asc_dvc->err_code = ASC_IERR_BIST_PRE_TEST;
			वापस ADV_ERROR;
		पूर्ण
	पूर्ण

	/*
	 * LRAM Test - It takes about 1.5 ms to run through the test.
	 *
	 * Write RAM_TEST_MODE (0x80) to रेजिस्टर and रुको क्रम 10 milliseconds.
	 * If Done bit not set or Status not 0, save रेजिस्टर byte, set the
	 * err_code, and वापस an error.
	 */
	AdvWriteByteRegister(iop_base, IOPB_RAM_BIST, RAM_TEST_MODE);
	mdelay(10);	/* Wait क्रम 10ms beक्रमe checking status. */

	byte = AdvReadByteRegister(iop_base, IOPB_RAM_BIST);
	अगर ((byte & RAM_TEST_DONE) == 0 || (byte & RAM_TEST_STATUS) != 0) अणु
		/* Get here अगर Done bit not set or Status not 0. */
		asc_dvc->bist_err_code = byte;	/* क्रम BIOS display message */
		asc_dvc->err_code = ASC_IERR_BIST_RAM_TEST;
		वापस ADV_ERROR;
	पूर्ण

	/* We need to reset back to normal mode after LRAM test passes. */
	AdvWriteByteRegister(iop_base, IOPB_RAM_BIST, NORMAL_MODE);

	err = request_firmware(&fw, fwname, asc_dvc->drv_ptr->dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Failed to load image \"%s\" err %d\n",
		       fwname, err);
		asc_dvc->err_code = ASC_IERR_MCODE_CHKSUM;
		वापस err;
	पूर्ण
	अगर (fw->size < 4) अणु
		prपूर्णांकk(KERN_ERR "Bogus length %zu in image \"%s\"\n",
		       fw->size, fwname);
		release_firmware(fw);
		asc_dvc->err_code = ASC_IERR_MCODE_CHKSUM;
		वापस -EINVAL;
	पूर्ण
	chksum = (fw->data[3] << 24) | (fw->data[2] << 16) |
		 (fw->data[1] << 8) | fw->data[0];
	asc_dvc->err_code = AdvLoadMicrocode(iop_base, &fw->data[4],
					     fw->size - 4, ADV_38C0800_MEMSIZE,
					     chksum);
	release_firmware(fw);
	अगर (asc_dvc->err_code)
		वापस ADV_ERROR;

	/*
	 * Restore the RISC memory BIOS region.
	 */
	क्रम (i = 0; i < ASC_MC_BIOSLEN / 2; i++) अणु
		AdvWriteWordLram(iop_base, ASC_MC_BIOSMEM + (2 * i),
				 bios_mem[i]);
	पूर्ण

	/*
	 * Calculate and ग_लिखो the microcode code checksum to the microcode
	 * code checksum location ASC_MC_CODE_CHK_SUM (0x2C).
	 */
	AdvReadWordLram(iop_base, ASC_MC_CODE_BEGIN_ADDR, begin_addr);
	AdvReadWordLram(iop_base, ASC_MC_CODE_END_ADDR, end_addr);
	code_sum = 0;
	AdvWriteWordRegister(iop_base, IOPW_RAM_ADDR, begin_addr);
	क्रम (word = begin_addr; word < end_addr; word += 2) अणु
		code_sum += AdvReadWordAutoIncLram(iop_base);
	पूर्ण
	AdvWriteWordLram(iop_base, ASC_MC_CODE_CHK_SUM, code_sum);

	/*
	 * Read microcode version and date.
	 */
	AdvReadWordLram(iop_base, ASC_MC_VERSION_DATE,
			asc_dvc->cfg->mcode_date);
	AdvReadWordLram(iop_base, ASC_MC_VERSION_NUM,
			asc_dvc->cfg->mcode_version);

	/*
	 * Set the chip type to indicate the ASC38C0800.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_CHIP_TYPE, ADV_CHIP_ASC38C0800);

	/*
	 * Write 1 to bit 14 'DIS_TERM_DRV' in the SCSI_CFG1 रेजिस्टर.
	 * When DIS_TERM_DRV set to 1, C_DET[3:0] will reflect current
	 * cable detection and then we are able to पढ़ो C_DET[3:0].
	 *
	 * Note: We will reset DIS_TERM_DRV to 0 in the 'Set SCSI_CFG1
	 * Microcode Default Value' section below.
	 */
	scsi_cfg1 = AdvReadWordRegister(iop_base, IOPW_SCSI_CFG1);
	AdvWriteWordRegister(iop_base, IOPW_SCSI_CFG1,
			     scsi_cfg1 | DIS_TERM_DRV);

	/*
	 * If the PCI Configuration Command Register "Parity Error Response
	 * Control" Bit was clear (0), then set the microcode variable
	 * 'control_flag' CONTROL_FLAG_IGNORE_PERR flag to tell the microcode
	 * to ignore DMA parity errors.
	 */
	अगर (asc_dvc->cfg->control_flag & CONTROL_FLAG_IGNORE_PERR) अणु
		AdvReadWordLram(iop_base, ASC_MC_CONTROL_FLAG, word);
		word |= CONTROL_FLAG_IGNORE_PERR;
		AdvWriteWordLram(iop_base, ASC_MC_CONTROL_FLAG, word);
	पूर्ण

	/*
	 * For ASC-38C0800, set FIFO_THRESH_80B [6:4] bits and START_CTL_TH [3:2]
	 * bits क्रम the शेष FIFO threshold.
	 *
	 * Note: ASC-38C0800 FIFO threshold has been changed to 256 bytes.
	 *
	 * For DMA Errata #4 set the BC_THRESH_ENB bit.
	 */
	AdvWriteByteRegister(iop_base, IOPB_DMA_CFG0,
			     BC_THRESH_ENB | FIFO_THRESH_80B | START_CTL_TH |
			     READ_CMD_MRM);

	/*
	 * Microcode operating variables क्रम WDTR, SDTR, and command tag
	 * queuing will be set in slave_configure() based on what a
	 * device reports it is capable of in Inquiry byte 7.
	 *
	 * If SCSI Bus Resets have been disabled, then directly set
	 * SDTR and WDTR from the EEPROM configuration. This will allow
	 * the BIOS and warm boot to work without a SCSI bus hang on
	 * the Inquiry caused by host and target mismatched DTR values.
	 * Without the SCSI Bus Reset, beक्रमe an Inquiry a device can't
	 * be assumed to be in Asynchronous, Narrow mode.
	 */
	अगर ((asc_dvc->bios_ctrl & BIOS_CTRL_RESET_SCSI_BUS) == 0) अणु
		AdvWriteWordLram(iop_base, ASC_MC_WDTR_ABLE,
				 asc_dvc->wdtr_able);
		AdvWriteWordLram(iop_base, ASC_MC_SDTR_ABLE,
				 asc_dvc->sdtr_able);
	पूर्ण

	/*
	 * Set microcode operating variables क्रम DISC and SDTR_SPEED1,
	 * SDTR_SPEED2, SDTR_SPEED3, and SDTR_SPEED4 based on the EEPROM
	 * configuration values.
	 *
	 * The SDTR per TID biपंचांगask overrides the SDTR_SPEED1, SDTR_SPEED2,
	 * SDTR_SPEED3, and SDTR_SPEED4 values so it is safe to set them
	 * without determining here whether the device supports SDTR.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DISC_ENABLE,
			 asc_dvc->cfg->disc_enable);
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_SPEED1, asc_dvc->sdtr_speed1);
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_SPEED2, asc_dvc->sdtr_speed2);
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_SPEED3, asc_dvc->sdtr_speed3);
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_SPEED4, asc_dvc->sdtr_speed4);

	/*
	 * Set SCSI_CFG0 Microcode Default Value.
	 *
	 * The microcode will set the SCSI_CFG0 रेजिस्टर using this value
	 * after it is started below.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_SCSI_CFG0,
			 PARITY_EN | QUEUE_128 | SEL_TMO_LONG | OUR_ID_EN |
			 asc_dvc->chip_scsi_id);

	/*
	 * Determine SCSI_CFG1 Microcode Default Value.
	 *
	 * The microcode will set the SCSI_CFG1 रेजिस्टर using this value
	 * after it is started below.
	 */

	/* Read current SCSI_CFG1 Register value. */
	scsi_cfg1 = AdvReadWordRegister(iop_base, IOPW_SCSI_CFG1);

	/*
	 * If the पूर्णांकernal narrow cable is reversed all of the SCSI_CTRL
	 * रेजिस्टर संकेतs will be set. Check क्रम and वापस an error अगर
	 * this condition is found.
	 */
	अगर ((AdvReadWordRegister(iop_base, IOPW_SCSI_CTRL) & 0x3F07) == 0x3F07) अणु
		asc_dvc->err_code |= ASC_IERR_REVERSED_CABLE;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * All kind of combinations of devices attached to one of four
	 * connectors are acceptable except HVD device attached. For example,
	 * LVD device can be attached to SE connector जबतक SE device attached
	 * to LVD connector.  If LVD device attached to SE connector, it only
	 * runs up to Ultra speed.
	 *
	 * If an HVD device is attached to one of LVD connectors, वापस an
	 * error.  However, there is no way to detect HVD device attached to
	 * SE connectors.
	 */
	अगर (scsi_cfg1 & HVD) अणु
		asc_dvc->err_code = ASC_IERR_HVD_DEVICE;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * If either SE or LVD स्वतःmatic termination control is enabled, then
	 * set the termination value based on a table listed in a_conकरोr.h.
	 *
	 * If manual termination was specअगरied with an EEPROM setting then
	 * 'termination' was set-up in AdvInitFrom38C0800EEPROM() and is पढ़ोy
	 * to be 'ored' पूर्णांकo SCSI_CFG1.
	 */
	अगर ((asc_dvc->cfg->termination & TERM_SE) == 0) अणु
		/* SE स्वतःmatic termination control is enabled. */
		चयन (scsi_cfg1 & C_DET_SE) अणु
			/* TERM_SE_HI: on, TERM_SE_LO: on */
		हाल 0x1:
		हाल 0x2:
		हाल 0x3:
			asc_dvc->cfg->termination |= TERM_SE;
			अवरोध;

			/* TERM_SE_HI: on, TERM_SE_LO: off */
		हाल 0x0:
			asc_dvc->cfg->termination |= TERM_SE_HI;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((asc_dvc->cfg->termination & TERM_LVD) == 0) अणु
		/* LVD स्वतःmatic termination control is enabled. */
		चयन (scsi_cfg1 & C_DET_LVD) अणु
			/* TERM_LVD_HI: on, TERM_LVD_LO: on */
		हाल 0x4:
		हाल 0x8:
		हाल 0xC:
			asc_dvc->cfg->termination |= TERM_LVD;
			अवरोध;

			/* TERM_LVD_HI: off, TERM_LVD_LO: off */
		हाल 0x0:
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Clear any set TERM_SE and TERM_LVD bits.
	 */
	scsi_cfg1 &= (~TERM_SE & ~TERM_LVD);

	/*
	 * Invert the TERM_SE and TERM_LVD bits and then set 'scsi_cfg1'.
	 */
	scsi_cfg1 |= (~asc_dvc->cfg->termination & 0xF0);

	/*
	 * Clear BIG_ENDIAN, DIS_TERM_DRV, Terminator Polarity and HVD/LVD/SE
	 * bits and set possibly modअगरied termination control bits in the
	 * Microcode SCSI_CFG1 Register Value.
	 */
	scsi_cfg1 &= (~BIG_ENDIAN & ~DIS_TERM_DRV & ~TERM_POL & ~HVD_LVD_SE);

	/*
	 * Set SCSI_CFG1 Microcode Default Value
	 *
	 * Set possibly modअगरied termination control and reset DIS_TERM_DRV
	 * bits in the Microcode SCSI_CFG1 Register Value.
	 *
	 * The microcode will set the SCSI_CFG1 रेजिस्टर using this value
	 * after it is started below.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_SCSI_CFG1, scsi_cfg1);

	/*
	 * Set MEM_CFG Microcode Default Value
	 *
	 * The microcode will set the MEM_CFG रेजिस्टर using this value
	 * after it is started below.
	 *
	 * MEM_CFG may be accessed as a word or byte, but only bits 0-7
	 * are defined.
	 *
	 * ASC-38C0800 has 16KB पूर्णांकernal memory.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_MEM_CFG,
			 BIOS_EN | RAM_SZ_16KB);

	/*
	 * Set SEL_MASK Microcode Default Value
	 *
	 * The microcode will set the SEL_MASK रेजिस्टर using this value
	 * after it is started below.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_SEL_MASK,
			 ADV_TID_TO_TIDMASK(asc_dvc->chip_scsi_id));

	AdvBuildCarrierFreelist(asc_dvc);

	/*
	 * Set-up the Host->RISC Initiator Command Queue (ICQ).
	 */

	asc_dvc->icq_sp = adv_get_next_carrier(asc_dvc);
	अगर (!asc_dvc->icq_sp) अणु
		ASC_DBG(0, "Failed to get ICQ carrier\n");
		asc_dvc->err_code |= ASC_IERR_NO_CARRIER;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * Set RISC ICQ physical address start value.
	 * carr_pa is LE, must be native beक्रमe ग_लिखो
	 */
	AdvWriteDWordLramNoSwap(iop_base, ASC_MC_ICQ, asc_dvc->icq_sp->carr_pa);

	/*
	 * Set-up the RISC->Host Initiator Response Queue (IRQ).
	 */
	asc_dvc->irq_sp = adv_get_next_carrier(asc_dvc);
	अगर (!asc_dvc->irq_sp) अणु
		ASC_DBG(0, "Failed to get IRQ carrier\n");
		asc_dvc->err_code |= ASC_IERR_NO_CARRIER;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * Set RISC IRQ physical address start value.
	 *
	 * carr_pa is LE, must be native beक्रमe ग_लिखो *
	 */
	AdvWriteDWordLramNoSwap(iop_base, ASC_MC_IRQ, asc_dvc->irq_sp->carr_pa);
	asc_dvc->carr_pending_cnt = 0;

	AdvWriteByteRegister(iop_base, IOPB_INTR_ENABLES,
			     (ADV_INTR_ENABLE_HOST_INTR |
			      ADV_INTR_ENABLE_GLOBAL_INTR));

	AdvReadWordLram(iop_base, ASC_MC_CODE_BEGIN_ADDR, word);
	AdvWriteWordRegister(iop_base, IOPW_PC, word);

	/* finally, finally, gentlemen, start your engine */
	AdvWriteWordRegister(iop_base, IOPW_RISC_CSR, ADV_RISC_CSR_RUN);

	/*
	 * Reset the SCSI Bus अगर the EEPROM indicates that SCSI Bus
	 * Resets should be perक्रमmed. The RISC has to be running
	 * to issue a SCSI Bus Reset.
	 */
	अगर (asc_dvc->bios_ctrl & BIOS_CTRL_RESET_SCSI_BUS) अणु
		/*
		 * If the BIOS Signature is present in memory, restore the
		 * BIOS Handshake Configuration Table and करो not perक्रमm
		 * a SCSI Bus Reset.
		 */
		अगर (bios_mem[(ASC_MC_BIOS_SIGNATURE - ASC_MC_BIOSMEM) / 2] ==
		    0x55AA) अणु
			/*
			 * Restore per TID negotiated values.
			 */
			AdvWriteWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
			AdvWriteWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
			AdvWriteWordLram(iop_base, ASC_MC_TAGQNG_ABLE,
					 tagqng_able);
			क्रम (tid = 0; tid <= ADV_MAX_TID; tid++) अणु
				AdvWriteByteLram(iop_base,
						 ASC_MC_NUMBER_OF_MAX_CMD + tid,
						 max_cmd[tid]);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (AdvResetSB(asc_dvc) != ADV_TRUE) अणु
				warn_code = ASC_WARN_BUSRESET_ERROR;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस warn_code;
पूर्ण

/*
 * Initialize the ASC-38C1600.
 *
 * On failure set the ASC_DVC_VAR field 'err_code' and वापस ADV_ERROR.
 *
 * For a non-fatal error वापस a warning code. If there are no warnings
 * then 0 is वापसed.
 *
 * Needed after initialization क्रम error recovery.
 */
अटल पूर्णांक AdvInitAsc38C1600Driver(ADV_DVC_VAR *asc_dvc)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर fwname[] = "advansys/38C1600.bin";
	AdvPortAddr iop_base;
	uलघु warn_code;
	पूर्णांक begin_addr;
	पूर्णांक end_addr;
	uलघु code_sum;
	दीर्घ word;
	पूर्णांक i;
	पूर्णांक err;
	अचिन्हित दीर्घ chksum;
	uलघु scsi_cfg1;
	uअक्षर byte;
	uअक्षर tid;
	uलघु bios_mem[ASC_MC_BIOSLEN / 2];	/* BIOS RISC Memory 0x40-0x8F. */
	uलघु wdtr_able, sdtr_able, ppr_able, tagqng_able;
	uअक्षर max_cmd[ASC_MAX_TID + 1];

	/* If there is alपढ़ोy an error, करोn't जारी. */
	अगर (asc_dvc->err_code != 0) अणु
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * The caller must set 'chip_type' to ADV_CHIP_ASC38C1600.
	 */
	अगर (asc_dvc->chip_type != ADV_CHIP_ASC38C1600) अणु
		asc_dvc->err_code = ASC_IERR_BAD_CHIPTYPE;
		वापस ADV_ERROR;
	पूर्ण

	warn_code = 0;
	iop_base = asc_dvc->iop_base;

	/*
	 * Save the RISC memory BIOS region beक्रमe writing the microcode.
	 * The BIOS may alपढ़ोy be loaded and using its RISC LRAM region
	 * so its region must be saved and restored.
	 *
	 * Note: This code makes the assumption, which is currently true,
	 * that a chip reset करोes not clear RISC LRAM.
	 */
	क्रम (i = 0; i < ASC_MC_BIOSLEN / 2; i++) अणु
		AdvReadWordLram(iop_base, ASC_MC_BIOSMEM + (2 * i),
				bios_mem[i]);
	पूर्ण

	/*
	 * Save current per TID negotiated values.
	 */
	AdvReadWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
	AdvReadWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
	AdvReadWordLram(iop_base, ASC_MC_PPR_ABLE, ppr_able);
	AdvReadWordLram(iop_base, ASC_MC_TAGQNG_ABLE, tagqng_able);
	क्रम (tid = 0; tid <= ASC_MAX_TID; tid++) अणु
		AdvReadByteLram(iop_base, ASC_MC_NUMBER_OF_MAX_CMD + tid,
				max_cmd[tid]);
	पूर्ण

	/*
	 * RAM BIST (Built-In Self Test)
	 *
	 * Address : I/O base + offset 0x38h रेजिस्टर (byte).
	 * Function: Bit 7-6(RW) : RAM mode
	 *                          Normal Mode   : 0x00
	 *                          Pre-test Mode : 0x40
	 *                          RAM Test Mode : 0x80
	 *           Bit 5       : unused
	 *           Bit 4(RO)   : Done bit
	 *           Bit 3-0(RO) : Status
	 *                          Host Error    : 0x08
	 *                          Int_RAM Error : 0x04
	 *                          RISC Error    : 0x02
	 *                          SCSI Error    : 0x01
	 *                          No Error      : 0x00
	 *
	 * Note: RAM BIST code should be put right here, beक्रमe loading the
	 * microcode and after saving the RISC memory BIOS region.
	 */

	/*
	 * LRAM Pre-test
	 *
	 * Write PRE_TEST_MODE (0x40) to रेजिस्टर and रुको क्रम 10 milliseconds.
	 * If Done bit not set or low nibble not PRE_TEST_VALUE (0x05), वापस
	 * an error. Reset to NORMAL_MODE (0x00) and करो again. If cannot reset
	 * to NORMAL_MODE, वापस an error too.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		AdvWriteByteRegister(iop_base, IOPB_RAM_BIST, PRE_TEST_MODE);
		mdelay(10);	/* Wait क्रम 10ms beक्रमe पढ़ोing back. */
		byte = AdvReadByteRegister(iop_base, IOPB_RAM_BIST);
		अगर ((byte & RAM_TEST_DONE) == 0
		    || (byte & 0x0F) != PRE_TEST_VALUE) अणु
			asc_dvc->err_code = ASC_IERR_BIST_PRE_TEST;
			वापस ADV_ERROR;
		पूर्ण

		AdvWriteByteRegister(iop_base, IOPB_RAM_BIST, NORMAL_MODE);
		mdelay(10);	/* Wait क्रम 10ms beक्रमe पढ़ोing back. */
		अगर (AdvReadByteRegister(iop_base, IOPB_RAM_BIST)
		    != NORMAL_VALUE) अणु
			asc_dvc->err_code = ASC_IERR_BIST_PRE_TEST;
			वापस ADV_ERROR;
		पूर्ण
	पूर्ण

	/*
	 * LRAM Test - It takes about 1.5 ms to run through the test.
	 *
	 * Write RAM_TEST_MODE (0x80) to रेजिस्टर and रुको क्रम 10 milliseconds.
	 * If Done bit not set or Status not 0, save रेजिस्टर byte, set the
	 * err_code, and वापस an error.
	 */
	AdvWriteByteRegister(iop_base, IOPB_RAM_BIST, RAM_TEST_MODE);
	mdelay(10);	/* Wait क्रम 10ms beक्रमe checking status. */

	byte = AdvReadByteRegister(iop_base, IOPB_RAM_BIST);
	अगर ((byte & RAM_TEST_DONE) == 0 || (byte & RAM_TEST_STATUS) != 0) अणु
		/* Get here अगर Done bit not set or Status not 0. */
		asc_dvc->bist_err_code = byte;	/* क्रम BIOS display message */
		asc_dvc->err_code = ASC_IERR_BIST_RAM_TEST;
		वापस ADV_ERROR;
	पूर्ण

	/* We need to reset back to normal mode after LRAM test passes. */
	AdvWriteByteRegister(iop_base, IOPB_RAM_BIST, NORMAL_MODE);

	err = request_firmware(&fw, fwname, asc_dvc->drv_ptr->dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Failed to load image \"%s\" err %d\n",
		       fwname, err);
		asc_dvc->err_code = ASC_IERR_MCODE_CHKSUM;
		वापस err;
	पूर्ण
	अगर (fw->size < 4) अणु
		prपूर्णांकk(KERN_ERR "Bogus length %zu in image \"%s\"\n",
		       fw->size, fwname);
		release_firmware(fw);
		asc_dvc->err_code = ASC_IERR_MCODE_CHKSUM;
		वापस -EINVAL;
	पूर्ण
	chksum = (fw->data[3] << 24) | (fw->data[2] << 16) |
		 (fw->data[1] << 8) | fw->data[0];
	asc_dvc->err_code = AdvLoadMicrocode(iop_base, &fw->data[4],
					     fw->size - 4, ADV_38C1600_MEMSIZE,
					     chksum);
	release_firmware(fw);
	अगर (asc_dvc->err_code)
		वापस ADV_ERROR;

	/*
	 * Restore the RISC memory BIOS region.
	 */
	क्रम (i = 0; i < ASC_MC_BIOSLEN / 2; i++) अणु
		AdvWriteWordLram(iop_base, ASC_MC_BIOSMEM + (2 * i),
				 bios_mem[i]);
	पूर्ण

	/*
	 * Calculate and ग_लिखो the microcode code checksum to the microcode
	 * code checksum location ASC_MC_CODE_CHK_SUM (0x2C).
	 */
	AdvReadWordLram(iop_base, ASC_MC_CODE_BEGIN_ADDR, begin_addr);
	AdvReadWordLram(iop_base, ASC_MC_CODE_END_ADDR, end_addr);
	code_sum = 0;
	AdvWriteWordRegister(iop_base, IOPW_RAM_ADDR, begin_addr);
	क्रम (word = begin_addr; word < end_addr; word += 2) अणु
		code_sum += AdvReadWordAutoIncLram(iop_base);
	पूर्ण
	AdvWriteWordLram(iop_base, ASC_MC_CODE_CHK_SUM, code_sum);

	/*
	 * Read microcode version and date.
	 */
	AdvReadWordLram(iop_base, ASC_MC_VERSION_DATE,
			asc_dvc->cfg->mcode_date);
	AdvReadWordLram(iop_base, ASC_MC_VERSION_NUM,
			asc_dvc->cfg->mcode_version);

	/*
	 * Set the chip type to indicate the ASC38C1600.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_CHIP_TYPE, ADV_CHIP_ASC38C1600);

	/*
	 * Write 1 to bit 14 'DIS_TERM_DRV' in the SCSI_CFG1 रेजिस्टर.
	 * When DIS_TERM_DRV set to 1, C_DET[3:0] will reflect current
	 * cable detection and then we are able to पढ़ो C_DET[3:0].
	 *
	 * Note: We will reset DIS_TERM_DRV to 0 in the 'Set SCSI_CFG1
	 * Microcode Default Value' section below.
	 */
	scsi_cfg1 = AdvReadWordRegister(iop_base, IOPW_SCSI_CFG1);
	AdvWriteWordRegister(iop_base, IOPW_SCSI_CFG1,
			     scsi_cfg1 | DIS_TERM_DRV);

	/*
	 * If the PCI Configuration Command Register "Parity Error Response
	 * Control" Bit was clear (0), then set the microcode variable
	 * 'control_flag' CONTROL_FLAG_IGNORE_PERR flag to tell the microcode
	 * to ignore DMA parity errors.
	 */
	अगर (asc_dvc->cfg->control_flag & CONTROL_FLAG_IGNORE_PERR) अणु
		AdvReadWordLram(iop_base, ASC_MC_CONTROL_FLAG, word);
		word |= CONTROL_FLAG_IGNORE_PERR;
		AdvWriteWordLram(iop_base, ASC_MC_CONTROL_FLAG, word);
	पूर्ण

	/*
	 * If the BIOS control flag AIPP (Asynchronous Inक्रमmation
	 * Phase Protection) disable bit is not set, then set the firmware
	 * 'control_flag' CONTROL_FLAG_ENABLE_AIPP bit to enable
	 * AIPP checking and encoding.
	 */
	अगर ((asc_dvc->bios_ctrl & BIOS_CTRL_AIPP_DIS) == 0) अणु
		AdvReadWordLram(iop_base, ASC_MC_CONTROL_FLAG, word);
		word |= CONTROL_FLAG_ENABLE_AIPP;
		AdvWriteWordLram(iop_base, ASC_MC_CONTROL_FLAG, word);
	पूर्ण

	/*
	 * For ASC-38C1600 use DMA_CFG0 शेष values: FIFO_THRESH_80B [6:4],
	 * and START_CTL_TH [3:2].
	 */
	AdvWriteByteRegister(iop_base, IOPB_DMA_CFG0,
			     FIFO_THRESH_80B | START_CTL_TH | READ_CMD_MRM);

	/*
	 * Microcode operating variables क्रम WDTR, SDTR, and command tag
	 * queuing will be set in slave_configure() based on what a
	 * device reports it is capable of in Inquiry byte 7.
	 *
	 * If SCSI Bus Resets have been disabled, then directly set
	 * SDTR and WDTR from the EEPROM configuration. This will allow
	 * the BIOS and warm boot to work without a SCSI bus hang on
	 * the Inquiry caused by host and target mismatched DTR values.
	 * Without the SCSI Bus Reset, beक्रमe an Inquiry a device can't
	 * be assumed to be in Asynchronous, Narrow mode.
	 */
	अगर ((asc_dvc->bios_ctrl & BIOS_CTRL_RESET_SCSI_BUS) == 0) अणु
		AdvWriteWordLram(iop_base, ASC_MC_WDTR_ABLE,
				 asc_dvc->wdtr_able);
		AdvWriteWordLram(iop_base, ASC_MC_SDTR_ABLE,
				 asc_dvc->sdtr_able);
	पूर्ण

	/*
	 * Set microcode operating variables क्रम DISC and SDTR_SPEED1,
	 * SDTR_SPEED2, SDTR_SPEED3, and SDTR_SPEED4 based on the EEPROM
	 * configuration values.
	 *
	 * The SDTR per TID biपंचांगask overrides the SDTR_SPEED1, SDTR_SPEED2,
	 * SDTR_SPEED3, and SDTR_SPEED4 values so it is safe to set them
	 * without determining here whether the device supports SDTR.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DISC_ENABLE,
			 asc_dvc->cfg->disc_enable);
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_SPEED1, asc_dvc->sdtr_speed1);
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_SPEED2, asc_dvc->sdtr_speed2);
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_SPEED3, asc_dvc->sdtr_speed3);
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_SPEED4, asc_dvc->sdtr_speed4);

	/*
	 * Set SCSI_CFG0 Microcode Default Value.
	 *
	 * The microcode will set the SCSI_CFG0 रेजिस्टर using this value
	 * after it is started below.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_SCSI_CFG0,
			 PARITY_EN | QUEUE_128 | SEL_TMO_LONG | OUR_ID_EN |
			 asc_dvc->chip_scsi_id);

	/*
	 * Calculate SCSI_CFG1 Microcode Default Value.
	 *
	 * The microcode will set the SCSI_CFG1 रेजिस्टर using this value
	 * after it is started below.
	 *
	 * Each ASC-38C1600 function has only two cable detect bits.
	 * The bus mode override bits are in IOPB_SOFT_OVER_WR.
	 */
	scsi_cfg1 = AdvReadWordRegister(iop_base, IOPW_SCSI_CFG1);

	/*
	 * If the cable is reversed all of the SCSI_CTRL रेजिस्टर संकेतs
	 * will be set. Check क्रम and वापस an error अगर this condition is
	 * found.
	 */
	अगर ((AdvReadWordRegister(iop_base, IOPW_SCSI_CTRL) & 0x3F07) == 0x3F07) अणु
		asc_dvc->err_code |= ASC_IERR_REVERSED_CABLE;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * Each ASC-38C1600 function has two connectors. Only an HVD device
	 * can not be connected to either connector. An LVD device or SE device
	 * may be connected to either connecor. If an SE device is connected,
	 * then at most Ultra speed (20 Mhz) can be used on both connectors.
	 *
	 * If an HVD device is attached, वापस an error.
	 */
	अगर (scsi_cfg1 & HVD) अणु
		asc_dvc->err_code |= ASC_IERR_HVD_DEVICE;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * Each function in the ASC-38C1600 uses only the SE cable detect and
	 * termination because there are two connectors क्रम each function. Each
	 * function may use either LVD or SE mode. Corresponding the SE स्वतःmatic
	 * termination control EEPROM bits are used क्रम each function. Each
	 * function has its own EEPROM. If SE स्वतःmatic control is enabled क्रम
	 * the function, then set the termination value based on a table listed
	 * in a_conकरोr.h.
	 *
	 * If manual termination is specअगरied in the EEPROM क्रम the function,
	 * then 'termination' was set-up in AscInitFrom38C1600EEPROM() and is
	 * पढ़ोy to be 'ored' पूर्णांकo SCSI_CFG1.
	 */
	अगर ((asc_dvc->cfg->termination & TERM_SE) == 0) अणु
		काष्ठा pci_dev *pdev = adv_dvc_to_pdev(asc_dvc);
		/* SE स्वतःmatic termination control is enabled. */
		चयन (scsi_cfg1 & C_DET_SE) अणु
			/* TERM_SE_HI: on, TERM_SE_LO: on */
		हाल 0x1:
		हाल 0x2:
		हाल 0x3:
			asc_dvc->cfg->termination |= TERM_SE;
			अवरोध;

		हाल 0x0:
			अगर (PCI_FUNC(pdev->devfn) == 0) अणु
				/* Function 0 - TERM_SE_HI: off, TERM_SE_LO: off */
			पूर्ण अन्यथा अणु
				/* Function 1 - TERM_SE_HI: on, TERM_SE_LO: off */
				asc_dvc->cfg->termination |= TERM_SE_HI;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Clear any set TERM_SE bits.
	 */
	scsi_cfg1 &= ~TERM_SE;

	/*
	 * Invert the TERM_SE bits and then set 'scsi_cfg1'.
	 */
	scsi_cfg1 |= (~asc_dvc->cfg->termination & TERM_SE);

	/*
	 * Clear Big Endian and Terminator Polarity bits and set possibly
	 * modअगरied termination control bits in the Microcode SCSI_CFG1
	 * Register Value.
	 *
	 * Big Endian bit is not used even on big endian machines.
	 */
	scsi_cfg1 &= (~BIG_ENDIAN & ~DIS_TERM_DRV & ~TERM_POL);

	/*
	 * Set SCSI_CFG1 Microcode Default Value
	 *
	 * Set possibly modअगरied termination control bits in the Microcode
	 * SCSI_CFG1 Register Value.
	 *
	 * The microcode will set the SCSI_CFG1 रेजिस्टर using this value
	 * after it is started below.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_SCSI_CFG1, scsi_cfg1);

	/*
	 * Set MEM_CFG Microcode Default Value
	 *
	 * The microcode will set the MEM_CFG रेजिस्टर using this value
	 * after it is started below.
	 *
	 * MEM_CFG may be accessed as a word or byte, but only bits 0-7
	 * are defined.
	 *
	 * ASC-38C1600 has 32KB पूर्णांकernal memory.
	 *
	 * XXX - Since ASC38C1600 Rev.3 has a Local RAM failure issue, we come
	 * out a special 16K Adv Library and Microcode version. After the issue
	 * resolved, we should turn back to the 32K support. Both a_conकरोr.h and
	 * mcode.sas files also need to be updated.
	 *
	 * AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_MEM_CFG,
	 *  BIOS_EN | RAM_SZ_32KB);
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_MEM_CFG,
			 BIOS_EN | RAM_SZ_16KB);

	/*
	 * Set SEL_MASK Microcode Default Value
	 *
	 * The microcode will set the SEL_MASK रेजिस्टर using this value
	 * after it is started below.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_DEFAULT_SEL_MASK,
			 ADV_TID_TO_TIDMASK(asc_dvc->chip_scsi_id));

	AdvBuildCarrierFreelist(asc_dvc);

	/*
	 * Set-up the Host->RISC Initiator Command Queue (ICQ).
	 */
	asc_dvc->icq_sp = adv_get_next_carrier(asc_dvc);
	अगर (!asc_dvc->icq_sp) अणु
		asc_dvc->err_code |= ASC_IERR_NO_CARRIER;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * Set RISC ICQ physical address start value. Initialize the
	 * COMMA रेजिस्टर to the same value otherwise the RISC will
	 * prematurely detect a command is available.
	 */
	AdvWriteDWordLramNoSwap(iop_base, ASC_MC_ICQ, asc_dvc->icq_sp->carr_pa);
	AdvWriteDWordRegister(iop_base, IOPDW_COMMA,
			      le32_to_cpu(asc_dvc->icq_sp->carr_pa));

	/*
	 * Set-up the RISC->Host Initiator Response Queue (IRQ).
	 */
	asc_dvc->irq_sp = adv_get_next_carrier(asc_dvc);
	अगर (!asc_dvc->irq_sp) अणु
		asc_dvc->err_code |= ASC_IERR_NO_CARRIER;
		वापस ADV_ERROR;
	पूर्ण

	/*
	 * Set RISC IRQ physical address start value.
	 */
	AdvWriteDWordLramNoSwap(iop_base, ASC_MC_IRQ, asc_dvc->irq_sp->carr_pa);
	asc_dvc->carr_pending_cnt = 0;

	AdvWriteByteRegister(iop_base, IOPB_INTR_ENABLES,
			     (ADV_INTR_ENABLE_HOST_INTR |
			      ADV_INTR_ENABLE_GLOBAL_INTR));
	AdvReadWordLram(iop_base, ASC_MC_CODE_BEGIN_ADDR, word);
	AdvWriteWordRegister(iop_base, IOPW_PC, word);

	/* finally, finally, gentlemen, start your engine */
	AdvWriteWordRegister(iop_base, IOPW_RISC_CSR, ADV_RISC_CSR_RUN);

	/*
	 * Reset the SCSI Bus अगर the EEPROM indicates that SCSI Bus
	 * Resets should be perक्रमmed. The RISC has to be running
	 * to issue a SCSI Bus Reset.
	 */
	अगर (asc_dvc->bios_ctrl & BIOS_CTRL_RESET_SCSI_BUS) अणु
		/*
		 * If the BIOS Signature is present in memory, restore the
		 * per TID microcode operating variables.
		 */
		अगर (bios_mem[(ASC_MC_BIOS_SIGNATURE - ASC_MC_BIOSMEM) / 2] ==
		    0x55AA) अणु
			/*
			 * Restore per TID negotiated values.
			 */
			AdvWriteWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
			AdvWriteWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
			AdvWriteWordLram(iop_base, ASC_MC_PPR_ABLE, ppr_able);
			AdvWriteWordLram(iop_base, ASC_MC_TAGQNG_ABLE,
					 tagqng_able);
			क्रम (tid = 0; tid <= ASC_MAX_TID; tid++) अणु
				AdvWriteByteLram(iop_base,
						 ASC_MC_NUMBER_OF_MAX_CMD + tid,
						 max_cmd[tid]);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (AdvResetSB(asc_dvc) != ADV_TRUE) अणु
				warn_code = ASC_WARN_BUSRESET_ERROR;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस warn_code;
पूर्ण

/*
 * Reset chip and SCSI Bus.
 *
 * Return Value:
 *      ADV_TRUE(1) -   Chip re-initialization and SCSI Bus Reset successful.
 *      ADV_FALSE(0) -  Chip re-initialization and SCSI Bus Reset failure.
 */
अटल पूर्णांक AdvResetChipAndSB(ADV_DVC_VAR *asc_dvc)
अणु
	पूर्णांक status;
	uलघु wdtr_able, sdtr_able, tagqng_able;
	uलघु ppr_able = 0;
	uअक्षर tid, max_cmd[ADV_MAX_TID + 1];
	AdvPortAddr iop_base;
	uलघु bios_sig;

	iop_base = asc_dvc->iop_base;

	/*
	 * Save current per TID negotiated values.
	 */
	AdvReadWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
	AdvReadWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
	अगर (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) अणु
		AdvReadWordLram(iop_base, ASC_MC_PPR_ABLE, ppr_able);
	पूर्ण
	AdvReadWordLram(iop_base, ASC_MC_TAGQNG_ABLE, tagqng_able);
	क्रम (tid = 0; tid <= ADV_MAX_TID; tid++) अणु
		AdvReadByteLram(iop_base, ASC_MC_NUMBER_OF_MAX_CMD + tid,
				max_cmd[tid]);
	पूर्ण

	/*
	 * Force the AdvInitAsc3550/38C0800Driver() function to
	 * perक्रमm a SCSI Bus Reset by clearing the BIOS signature word.
	 * The initialization functions assumes a SCSI Bus Reset is not
	 * needed अगर the BIOS signature word is present.
	 */
	AdvReadWordLram(iop_base, ASC_MC_BIOS_SIGNATURE, bios_sig);
	AdvWriteWordLram(iop_base, ASC_MC_BIOS_SIGNATURE, 0);

	/*
	 * Stop chip and reset it.
	 */
	AdvWriteWordRegister(iop_base, IOPW_RISC_CSR, ADV_RISC_CSR_STOP);
	AdvWriteWordRegister(iop_base, IOPW_CTRL_REG, ADV_CTRL_REG_CMD_RESET);
	mdelay(100);
	AdvWriteWordRegister(iop_base, IOPW_CTRL_REG,
			     ADV_CTRL_REG_CMD_WR_IO_REG);

	/*
	 * Reset Adv Library error code, अगर any, and try
	 * re-initializing the chip.
	 */
	asc_dvc->err_code = 0;
	अगर (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) अणु
		status = AdvInitAsc38C1600Driver(asc_dvc);
	पूर्ण अन्यथा अगर (asc_dvc->chip_type == ADV_CHIP_ASC38C0800) अणु
		status = AdvInitAsc38C0800Driver(asc_dvc);
	पूर्ण अन्यथा अणु
		status = AdvInitAsc3550Driver(asc_dvc);
	पूर्ण

	/* Translate initialization वापस value to status value. */
	अगर (status == 0) अणु
		status = ADV_TRUE;
	पूर्ण अन्यथा अणु
		status = ADV_FALSE;
	पूर्ण

	/*
	 * Restore the BIOS signature word.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_BIOS_SIGNATURE, bios_sig);

	/*
	 * Restore per TID negotiated values.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
	अगर (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) अणु
		AdvWriteWordLram(iop_base, ASC_MC_PPR_ABLE, ppr_able);
	पूर्ण
	AdvWriteWordLram(iop_base, ASC_MC_TAGQNG_ABLE, tagqng_able);
	क्रम (tid = 0; tid <= ADV_MAX_TID; tid++) अणु
		AdvWriteByteLram(iop_base, ASC_MC_NUMBER_OF_MAX_CMD + tid,
				 max_cmd[tid]);
	पूर्ण

	वापस status;
पूर्ण

/*
 * adv_async_callback() - Adv Library asynchronous event callback function.
 */
अटल व्योम adv_async_callback(ADV_DVC_VAR *adv_dvc_varp, uअक्षर code)
अणु
	चयन (code) अणु
	हाल ADV_ASYNC_SCSI_BUS_RESET_DET:
		/*
		 * The firmware detected a SCSI Bus reset.
		 */
		ASC_DBG(0, "ADV_ASYNC_SCSI_BUS_RESET_DET\n");
		अवरोध;

	हाल ADV_ASYNC_RDMA_FAILURE:
		/*
		 * Handle RDMA failure by resetting the SCSI Bus and
		 * possibly the chip अगर it is unresponsive. Log the error
		 * with a unique code.
		 */
		ASC_DBG(0, "ADV_ASYNC_RDMA_FAILURE\n");
		AdvResetChipAndSB(adv_dvc_varp);
		अवरोध;

	हाल ADV_HOST_SCSI_BUS_RESET:
		/*
		 * Host generated SCSI bus reset occurred.
		 */
		ASC_DBG(0, "ADV_HOST_SCSI_BUS_RESET\n");
		अवरोध;

	शेष:
		ASC_DBG(0, "unknown code 0x%x\n", code);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * adv_isr_callback() - Second Level Interrupt Handler called by AdvISR().
 *
 * Callback function क्रम the Wide SCSI Adv Library.
 */
अटल व्योम adv_isr_callback(ADV_DVC_VAR *adv_dvc_varp, ADV_SCSI_REQ_Q *scsiqp)
अणु
	काष्ठा asc_board *boardp = adv_dvc_varp->drv_ptr;
	adv_req_t *reqp;
	adv_sgblk_t *sgblkp;
	काष्ठा scsi_cmnd *scp;
	u32 resid_cnt;
	dma_addr_t sense_addr;

	ASC_DBG(1, "adv_dvc_varp 0x%p, scsiqp 0x%p\n",
		adv_dvc_varp, scsiqp);
	ASC_DBG_PRT_ADV_SCSI_REQ_Q(2, scsiqp);

	/*
	 * Get the adv_req_t काष्ठाure क्रम the command that has been
	 * completed. The adv_req_t काष्ठाure actually contains the
	 * completed ADV_SCSI_REQ_Q काष्ठाure.
	 */
	scp = scsi_host_find_tag(boardp->shost, scsiqp->srb_tag);

	ASC_DBG(1, "scp 0x%p\n", scp);
	अगर (scp == शून्य) अणु
		ASC_PRINT
		    ("adv_isr_callback: scp is NULL; adv_req_t dropped.\n");
		वापस;
	पूर्ण
	ASC_DBG_PRT_CDB(2, scp->cmnd, scp->cmd_len);

	reqp = (adv_req_t *)scp->host_scribble;
	ASC_DBG(1, "reqp 0x%lx\n", (uदीर्घ)reqp);
	अगर (reqp == शून्य) अणु
		ASC_PRINT("adv_isr_callback: reqp is NULL\n");
		वापस;
	पूर्ण
	/*
	 * Remove backreferences to aव्योम duplicate
	 * command completions.
	 */
	scp->host_scribble = शून्य;
	reqp->cmndp = शून्य;

	ASC_STATS(boardp->shost, callback);
	ASC_DBG(1, "shost 0x%p\n", boardp->shost);

	sense_addr = le32_to_cpu(scsiqp->sense_addr);
	dma_unmap_single(boardp->dev, sense_addr,
			 SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);

	/*
	 * 'done_status' contains the command's ending status.
	 */
	scp->result = 0;
	चयन (scsiqp->करोne_status) अणु
	हाल QD_NO_ERROR:
		ASC_DBG(2, "QD_NO_ERROR\n");

		/*
		 * Check क्रम an underrun condition.
		 *
		 * If there was no error and an underrun condition, then
		 * then वापस the number of underrun bytes.
		 */
		resid_cnt = le32_to_cpu(scsiqp->data_cnt);
		अगर (scsi_bufflen(scp) != 0 && resid_cnt != 0 &&
		    resid_cnt <= scsi_bufflen(scp)) अणु
			ASC_DBG(1, "underrun condition %lu bytes\n",
				 (uदीर्घ)resid_cnt);
			scsi_set_resid(scp, resid_cnt);
		पूर्ण
		अवरोध;

	हाल QD_WITH_ERROR:
		ASC_DBG(2, "QD_WITH_ERROR\n");
		चयन (scsiqp->host_status) अणु
		हाल QHSTA_NO_ERROR:
			set_status_byte(scp, scsiqp->scsi_status);
			अगर (scsiqp->scsi_status == SAM_STAT_CHECK_CONDITION) अणु
				ASC_DBG(2, "SAM_STAT_CHECK_CONDITION\n");
				ASC_DBG_PRT_SENSE(2, scp->sense_buffer,
						  SCSI_SENSE_BUFFERSIZE);
				set_driver_byte(scp, DRIVER_SENSE);
			पूर्ण
			अवरोध;

		शेष:
			/* Some other QHSTA error occurred. */
			ASC_DBG(1, "host_status 0x%x\n", scsiqp->host_status);
			set_host_byte(scp, DID_BAD_TARGET);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल QD_ABORTED_BY_HOST:
		ASC_DBG(1, "QD_ABORTED_BY_HOST\n");
		set_status_byte(scp, scsiqp->scsi_status);
		set_host_byte(scp, DID_ABORT);
		अवरोध;

	शेष:
		ASC_DBG(1, "done_status 0x%x\n", scsiqp->करोne_status);
		set_status_byte(scp, scsiqp->scsi_status);
		set_host_byte(scp, DID_ERROR);
		अवरोध;
	पूर्ण

	/*
	 * If the 'init_tidmask' bit isn't alपढ़ोy set क्रम the target and the
	 * current request finished normally, then set the bit क्रम the target
	 * to indicate that a device is present.
	 */
	अगर ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(scp->device->id)) == 0 &&
	    scsiqp->करोne_status == QD_NO_ERROR &&
	    scsiqp->host_status == QHSTA_NO_ERROR) अणु
		boardp->init_tidmask |= ADV_TID_TO_TIDMASK(scp->device->id);
	पूर्ण

	asc_scsi_करोne(scp);

	/*
	 * Free all 'adv_sgblk_t' काष्ठाures allocated क्रम the request.
	 */
	जबतक ((sgblkp = reqp->sgblkp) != शून्य) अणु
		/* Remove 'sgblkp' from the request list. */
		reqp->sgblkp = sgblkp->next_sgblkp;

		dma_pool_मुक्त(boardp->adv_sgblk_pool, sgblkp,
			      sgblkp->sg_addr);
	पूर्ण

	ASC_DBG(1, "done\n");
पूर्ण

/*
 * Adv Library Interrupt Service Routine
 *
 *  This function is called by a driver's पूर्णांकerrupt service routine.
 *  The function disables and re-enables पूर्णांकerrupts.
 *
 *  When a microcode idle command is completed, the ADV_DVC_VAR
 *  'idle_cmd_done' field is set to ADV_TRUE.
 *
 *  Note: AdvISR() can be called when पूर्णांकerrupts are disabled or even
 *  when there is no hardware पूर्णांकerrupt condition present. It will
 *  always check क्रम completed idle commands and microcode requests.
 *  This is an important feature that shouldn't be changed because it
 *  allows commands to be completed from polling mode loops.
 *
 * Return:
 *   ADV_TRUE(1) - पूर्णांकerrupt was pending
 *   ADV_FALSE(0) - no पूर्णांकerrupt was pending
 */
अटल पूर्णांक AdvISR(ADV_DVC_VAR *asc_dvc)
अणु
	AdvPortAddr iop_base;
	uअक्षर पूर्णांक_stat;
	ADV_CARR_T *मुक्त_carrp;
	__le32 irq_next_vpa;
	ADV_SCSI_REQ_Q *scsiq;
	adv_req_t *reqp;

	iop_base = asc_dvc->iop_base;

	/* Reading the रेजिस्टर clears the पूर्णांकerrupt. */
	पूर्णांक_stat = AdvReadByteRegister(iop_base, IOPB_INTR_STATUS_REG);

	अगर ((पूर्णांक_stat & (ADV_INTR_STATUS_INTRA | ADV_INTR_STATUS_INTRB |
			 ADV_INTR_STATUS_INTRC)) == 0) अणु
		वापस ADV_FALSE;
	पूर्ण

	/*
	 * Notअगरy the driver of an asynchronous microcode condition by
	 * calling the adv_async_callback function. The function
	 * is passed the microcode ASC_MC_INTRB_CODE byte value.
	 */
	अगर (पूर्णांक_stat & ADV_INTR_STATUS_INTRB) अणु
		uअक्षर पूर्णांकrb_code;

		AdvReadByteLram(iop_base, ASC_MC_INTRB_CODE, पूर्णांकrb_code);

		अगर (asc_dvc->chip_type == ADV_CHIP_ASC3550 ||
		    asc_dvc->chip_type == ADV_CHIP_ASC38C0800) अणु
			अगर (पूर्णांकrb_code == ADV_ASYNC_CARRIER_READY_FAILURE &&
			    asc_dvc->carr_pending_cnt != 0) अणु
				AdvWriteByteRegister(iop_base, IOPB_TICKLE,
						     ADV_TICKLE_A);
				अगर (asc_dvc->chip_type == ADV_CHIP_ASC3550) अणु
					AdvWriteByteRegister(iop_base,
							     IOPB_TICKLE,
							     ADV_TICKLE_NOP);
				पूर्ण
			पूर्ण
		पूर्ण

		adv_async_callback(asc_dvc, पूर्णांकrb_code);
	पूर्ण

	/*
	 * Check अगर the IRQ stopper carrier contains a completed request.
	 */
	जबतक (((irq_next_vpa =
		 le32_to_cpu(asc_dvc->irq_sp->next_vpa)) & ADV_RQ_DONE) != 0) अणु
		/*
		 * Get a poपूर्णांकer to the newly completed ADV_SCSI_REQ_Q काष्ठाure.
		 * The RISC will have set 'areq_vpa' to a भव address.
		 *
		 * The firmware will have copied the ADV_SCSI_REQ_Q.scsiq_ptr
		 * field to the carrier ADV_CARR_T.areq_vpa field. The conversion
		 * below complements the conversion of ADV_SCSI_REQ_Q.scsiq_ptr'
		 * in AdvExeScsiQueue().
		 */
		u32 pa_offset = le32_to_cpu(asc_dvc->irq_sp->areq_vpa);
		ASC_DBG(1, "irq_sp %p areq_vpa %u\n",
			asc_dvc->irq_sp, pa_offset);
		reqp = adv_get_reqp(asc_dvc, pa_offset);
		scsiq = &reqp->scsi_req_q;

		/*
		 * Request finished with good status and the queue was not
		 * DMAed to host memory by the firmware. Set all status fields
		 * to indicate good status.
		 */
		अगर ((irq_next_vpa & ADV_RQ_GOOD) != 0) अणु
			scsiq->करोne_status = QD_NO_ERROR;
			scsiq->host_status = scsiq->scsi_status = 0;
			scsiq->data_cnt = 0L;
		पूर्ण

		/*
		 * Advance the stopper poपूर्णांकer to the next carrier
		 * ignoring the lower four bits. Free the previous
		 * stopper carrier.
		 */
		मुक्त_carrp = asc_dvc->irq_sp;
		asc_dvc->irq_sp = adv_get_carrier(asc_dvc,
						  ADV_GET_CARRP(irq_next_vpa));

		मुक्त_carrp->next_vpa = asc_dvc->carr_मुक्तlist->carr_va;
		asc_dvc->carr_मुक्तlist = मुक्त_carrp;
		asc_dvc->carr_pending_cnt--;

		/*
		 * Clear request microcode control flag.
		 */
		scsiq->cntl = 0;

		/*
		 * Notअगरy the driver of the completed request by passing
		 * the ADV_SCSI_REQ_Q poपूर्णांकer to its callback function.
		 */
		adv_isr_callback(asc_dvc, scsiq);
		/*
		 * Note: After the driver callback function is called, 'scsiq'
		 * can no दीर्घer be referenced.
		 *
		 * Fall through and जारी processing other completed
		 * requests...
		 */
	पूर्ण
	वापस ADV_TRUE;
पूर्ण

अटल पूर्णांक AscSetLibErrorCode(ASC_DVC_VAR *asc_dvc, uलघु err_code)
अणु
	अगर (asc_dvc->err_code == 0) अणु
		asc_dvc->err_code = err_code;
		AscWriteLramWord(asc_dvc->iop_base, ASCV_ASCDVC_ERR_CODE_W,
				 err_code);
	पूर्ण
	वापस err_code;
पूर्ण

अटल व्योम AscAckInterrupt(PortAddr iop_base)
अणु
	uअक्षर host_flag;
	uअक्षर risc_flag;
	uलघु loop;

	loop = 0;
	करो अणु
		risc_flag = AscReadLramByte(iop_base, ASCV_RISC_FLAG_B);
		अगर (loop++ > 0x7FFF) अणु
			अवरोध;
		पूर्ण
	पूर्ण जबतक ((risc_flag & ASC_RISC_FLAG_GEN_INT) != 0);
	host_flag =
	    AscReadLramByte(iop_base,
			    ASCV_HOST_FLAG_B) & (~ASC_HOST_FLAG_ACK_INT);
	AscWriteLramByte(iop_base, ASCV_HOST_FLAG_B,
			 (uअक्षर)(host_flag | ASC_HOST_FLAG_ACK_INT));
	AscSetChipStatus(iop_base, CIW_INT_ACK);
	loop = 0;
	जबतक (AscGetChipStatus(iop_base) & CSW_INT_PENDING) अणु
		AscSetChipStatus(iop_base, CIW_INT_ACK);
		अगर (loop++ > 3) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	AscWriteLramByte(iop_base, ASCV_HOST_FLAG_B, host_flag);
पूर्ण

अटल uअक्षर AscGetSynPeriodIndex(ASC_DVC_VAR *asc_dvc, uअक्षर syn_समय)
अणु
	स्थिर uअक्षर *period_table;
	पूर्णांक max_index;
	पूर्णांक min_index;
	पूर्णांक i;

	period_table = asc_dvc->sdtr_period_tbl;
	max_index = (पूर्णांक)asc_dvc->max_sdtr_index;
	min_index = (पूर्णांक)asc_dvc->min_sdtr_index;
	अगर ((syn_समय <= period_table[max_index])) अणु
		क्रम (i = min_index; i < (max_index - 1); i++) अणु
			अगर (syn_समय <= period_table[i]) अणु
				वापस (uअक्षर)i;
			पूर्ण
		पूर्ण
		वापस (uअक्षर)max_index;
	पूर्ण अन्यथा अणु
		वापस (uअक्षर)(max_index + 1);
	पूर्ण
पूर्ण

अटल uअक्षर
AscMsgOutSDTR(ASC_DVC_VAR *asc_dvc, uअक्षर sdtr_period, uअक्षर sdtr_offset)
अणु
	PortAddr iop_base = asc_dvc->iop_base;
	uअक्षर sdtr_period_index = AscGetSynPeriodIndex(asc_dvc, sdtr_period);
	EXT_MSG sdtr_buf = अणु
		.msg_type = EXTENDED_MESSAGE,
		.msg_len = MS_SDTR_LEN,
		.msg_req = EXTENDED_SDTR,
		.xfer_period = sdtr_period,
		.req_ack_offset = sdtr_offset,
	पूर्ण;
	sdtr_offset &= ASC_SYN_MAX_OFFSET;

	अगर (sdtr_period_index <= asc_dvc->max_sdtr_index) अणु
		AscMemWordCopyPtrToLram(iop_base, ASCV_MSGOUT_BEG,
					(uअक्षर *)&sdtr_buf,
					माप(EXT_MSG) >> 1);
		वापस ((sdtr_period_index << 4) | sdtr_offset);
	पूर्ण अन्यथा अणु
		sdtr_buf.req_ack_offset = 0;
		AscMemWordCopyPtrToLram(iop_base, ASCV_MSGOUT_BEG,
					(uअक्षर *)&sdtr_buf,
					माप(EXT_MSG) >> 1);
		वापस 0;
	पूर्ण
पूर्ण

अटल uअक्षर
AscCalSDTRData(ASC_DVC_VAR *asc_dvc, uअक्षर sdtr_period, uअक्षर syn_offset)
अणु
	uअक्षर byte;
	uअक्षर sdtr_period_ix;

	sdtr_period_ix = AscGetSynPeriodIndex(asc_dvc, sdtr_period);
	अगर (sdtr_period_ix > asc_dvc->max_sdtr_index)
		वापस 0xFF;
	byte = (sdtr_period_ix << 4) | (syn_offset & ASC_SYN_MAX_OFFSET);
	वापस byte;
पूर्ण

अटल bool AscSetChipSynRegAtID(PortAddr iop_base, uअक्षर id, uअक्षर sdtr_data)
अणु
	ASC_SCSI_BIT_ID_TYPE org_id;
	पूर्णांक i;
	bool sta = true;

	AscSetBank(iop_base, 1);
	org_id = AscReadChipDvcID(iop_base);
	क्रम (i = 0; i <= ASC_MAX_TID; i++) अणु
		अगर (org_id == (0x01 << i))
			अवरोध;
	पूर्ण
	org_id = (ASC_SCSI_BIT_ID_TYPE) i;
	AscWriteChipDvcID(iop_base, id);
	अगर (AscReadChipDvcID(iop_base) == (0x01 << id)) अणु
		AscSetBank(iop_base, 0);
		AscSetChipSyn(iop_base, sdtr_data);
		अगर (AscGetChipSyn(iop_base) != sdtr_data) अणु
			sta = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		sta = false;
	पूर्ण
	AscSetBank(iop_base, 1);
	AscWriteChipDvcID(iop_base, org_id);
	AscSetBank(iop_base, 0);
	वापस (sta);
पूर्ण

अटल व्योम AscSetChipSDTR(PortAddr iop_base, uअक्षर sdtr_data, uअक्षर tid_no)
अणु
	AscSetChipSynRegAtID(iop_base, tid_no, sdtr_data);
	AscPutMCodeSDTRDoneAtID(iop_base, tid_no, sdtr_data);
पूर्ण

अटल व्योम AscIsrChipHalted(ASC_DVC_VAR *asc_dvc)
अणु
	EXT_MSG ext_msg;
	EXT_MSG out_msg;
	uलघु halt_q_addr;
	bool sdtr_accept;
	uलघु पूर्णांक_halt_code;
	ASC_SCSI_BIT_ID_TYPE scsi_busy;
	ASC_SCSI_BIT_ID_TYPE target_id;
	PortAddr iop_base;
	uअक्षर tag_code;
	uअक्षर q_status;
	uअक्षर halt_qp;
	uअक्षर sdtr_data;
	uअक्षर target_ix;
	uअक्षर q_cntl, tid_no;
	uअक्षर cur_dvc_qng;
	uअक्षर asyn_sdtr;
	uअक्षर scsi_status;
	काष्ठा asc_board *boardp;

	BUG_ON(!asc_dvc->drv_ptr);
	boardp = asc_dvc->drv_ptr;

	iop_base = asc_dvc->iop_base;
	पूर्णांक_halt_code = AscReadLramWord(iop_base, ASCV_HALTCODE_W);

	halt_qp = AscReadLramByte(iop_base, ASCV_CURCDB_B);
	halt_q_addr = ASC_QNO_TO_QADDR(halt_qp);
	target_ix = AscReadLramByte(iop_base,
				    (uलघु)(halt_q_addr +
					     (uलघु)ASC_SCSIQ_B_TARGET_IX));
	q_cntl = AscReadLramByte(iop_base,
			    (uलघु)(halt_q_addr + (uलघु)ASC_SCSIQ_B_CNTL));
	tid_no = ASC_TIX_TO_TID(target_ix);
	target_id = (uअक्षर)ASC_TID_TO_TARGET_ID(tid_no);
	अगर (asc_dvc->pci_fix_asyn_xfer & target_id) अणु
		asyn_sdtr = ASYN_SDTR_DATA_FIX_PCI_REV_AB;
	पूर्ण अन्यथा अणु
		asyn_sdtr = 0;
	पूर्ण
	अगर (पूर्णांक_halt_code == ASC_HALT_DISABLE_ASYN_USE_SYN_FIX) अणु
		अगर (asc_dvc->pci_fix_asyn_xfer & target_id) अणु
			AscSetChipSDTR(iop_base, 0, tid_no);
			boardp->sdtr_data[tid_no] = 0;
		पूर्ण
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		वापस;
	पूर्ण अन्यथा अगर (पूर्णांक_halt_code == ASC_HALT_ENABLE_ASYN_USE_SYN_FIX) अणु
		अगर (asc_dvc->pci_fix_asyn_xfer & target_id) अणु
			AscSetChipSDTR(iop_base, asyn_sdtr, tid_no);
			boardp->sdtr_data[tid_no] = asyn_sdtr;
		पूर्ण
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		वापस;
	पूर्ण अन्यथा अगर (पूर्णांक_halt_code == ASC_HALT_EXTMSG_IN) अणु
		AscMemWordCopyPtrFromLram(iop_base,
					  ASCV_MSGIN_BEG,
					  (uअक्षर *)&ext_msg,
					  माप(EXT_MSG) >> 1);

		अगर (ext_msg.msg_type == EXTENDED_MESSAGE &&
		    ext_msg.msg_req == EXTENDED_SDTR &&
		    ext_msg.msg_len == MS_SDTR_LEN) अणु
			sdtr_accept = true;
			अगर ((ext_msg.req_ack_offset > ASC_SYN_MAX_OFFSET)) अणु

				sdtr_accept = false;
				ext_msg.req_ack_offset = ASC_SYN_MAX_OFFSET;
			पूर्ण
			अगर ((ext_msg.xfer_period <
			     asc_dvc->sdtr_period_tbl[asc_dvc->min_sdtr_index])
			    || (ext_msg.xfer_period >
				asc_dvc->sdtr_period_tbl[asc_dvc->
							 max_sdtr_index])) अणु
				sdtr_accept = false;
				ext_msg.xfer_period =
				    asc_dvc->sdtr_period_tbl[asc_dvc->
							     min_sdtr_index];
			पूर्ण
			अगर (sdtr_accept) अणु
				sdtr_data =
				    AscCalSDTRData(asc_dvc, ext_msg.xfer_period,
						   ext_msg.req_ack_offset);
				अगर (sdtr_data == 0xFF) अणु

					q_cntl |= QC_MSG_OUT;
					asc_dvc->init_sdtr &= ~target_id;
					asc_dvc->sdtr_करोne &= ~target_id;
					AscSetChipSDTR(iop_base, asyn_sdtr,
						       tid_no);
					boardp->sdtr_data[tid_no] = asyn_sdtr;
				पूर्ण
			पूर्ण
			अगर (ext_msg.req_ack_offset == 0) अणु

				q_cntl &= ~QC_MSG_OUT;
				asc_dvc->init_sdtr &= ~target_id;
				asc_dvc->sdtr_करोne &= ~target_id;
				AscSetChipSDTR(iop_base, asyn_sdtr, tid_no);
			पूर्ण अन्यथा अणु
				अगर (sdtr_accept && (q_cntl & QC_MSG_OUT)) अणु
					q_cntl &= ~QC_MSG_OUT;
					asc_dvc->sdtr_करोne |= target_id;
					asc_dvc->init_sdtr |= target_id;
					asc_dvc->pci_fix_asyn_xfer &=
					    ~target_id;
					sdtr_data =
					    AscCalSDTRData(asc_dvc,
							   ext_msg.xfer_period,
							   ext_msg.
							   req_ack_offset);
					AscSetChipSDTR(iop_base, sdtr_data,
						       tid_no);
					boardp->sdtr_data[tid_no] = sdtr_data;
				पूर्ण अन्यथा अणु
					q_cntl |= QC_MSG_OUT;
					AscMsgOutSDTR(asc_dvc,
						      ext_msg.xfer_period,
						      ext_msg.req_ack_offset);
					asc_dvc->pci_fix_asyn_xfer &=
					    ~target_id;
					sdtr_data =
					    AscCalSDTRData(asc_dvc,
							   ext_msg.xfer_period,
							   ext_msg.
							   req_ack_offset);
					AscSetChipSDTR(iop_base, sdtr_data,
						       tid_no);
					boardp->sdtr_data[tid_no] = sdtr_data;
					asc_dvc->sdtr_करोne |= target_id;
					asc_dvc->init_sdtr |= target_id;
				पूर्ण
			पूर्ण

			AscWriteLramByte(iop_base,
					 (uलघु)(halt_q_addr +
						  (uलघु)ASC_SCSIQ_B_CNTL),
					 q_cntl);
			AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
			वापस;
		पूर्ण अन्यथा अगर (ext_msg.msg_type == EXTENDED_MESSAGE &&
			   ext_msg.msg_req == EXTENDED_WDTR &&
			   ext_msg.msg_len == MS_WDTR_LEN) अणु

			ext_msg.wdtr_width = 0;
			AscMemWordCopyPtrToLram(iop_base,
						ASCV_MSGOUT_BEG,
						(uअक्षर *)&ext_msg,
						माप(EXT_MSG) >> 1);
			q_cntl |= QC_MSG_OUT;
			AscWriteLramByte(iop_base,
					 (uलघु)(halt_q_addr +
						  (uलघु)ASC_SCSIQ_B_CNTL),
					 q_cntl);
			AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
			वापस;
		पूर्ण अन्यथा अणु

			ext_msg.msg_type = MESSAGE_REJECT;
			AscMemWordCopyPtrToLram(iop_base,
						ASCV_MSGOUT_BEG,
						(uअक्षर *)&ext_msg,
						माप(EXT_MSG) >> 1);
			q_cntl |= QC_MSG_OUT;
			AscWriteLramByte(iop_base,
					 (uलघु)(halt_q_addr +
						  (uलघु)ASC_SCSIQ_B_CNTL),
					 q_cntl);
			AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (पूर्णांक_halt_code == ASC_HALT_CHK_CONDITION) अणु

		q_cntl |= QC_REQ_SENSE;

		अगर ((asc_dvc->init_sdtr & target_id) != 0) अणु

			asc_dvc->sdtr_करोne &= ~target_id;

			sdtr_data = AscGetMCodeInitSDTRAtID(iop_base, tid_no);
			q_cntl |= QC_MSG_OUT;
			AscMsgOutSDTR(asc_dvc,
				      asc_dvc->
				      sdtr_period_tbl[(sdtr_data >> 4) &
						      (uअक्षर)(asc_dvc->
							      max_sdtr_index -
							      1)],
				      (uअक्षर)(sdtr_data & (uअक्षर)
					      ASC_SYN_MAX_OFFSET));
		पूर्ण

		AscWriteLramByte(iop_base,
				 (uलघु)(halt_q_addr +
					  (uलघु)ASC_SCSIQ_B_CNTL), q_cntl);

		tag_code = AscReadLramByte(iop_base,
					   (uलघु)(halt_q_addr + (uलघु)
						    ASC_SCSIQ_B_TAG_CODE));
		tag_code &= 0xDC;
		अगर ((asc_dvc->pci_fix_asyn_xfer & target_id)
		    && !(asc_dvc->pci_fix_asyn_xfer_always & target_id)
		    ) अणु

			tag_code |= (ASC_TAG_FLAG_DISABLE_DISCONNECT
				     | ASC_TAG_FLAG_DISABLE_ASYN_USE_SYN_FIX);

		पूर्ण
		AscWriteLramByte(iop_base,
				 (uलघु)(halt_q_addr +
					  (uलघु)ASC_SCSIQ_B_TAG_CODE),
				 tag_code);

		q_status = AscReadLramByte(iop_base,
					   (uलघु)(halt_q_addr + (uलघु)
						    ASC_SCSIQ_B_STATUS));
		q_status |= (QS_READY | QS_BUSY);
		AscWriteLramByte(iop_base,
				 (uलघु)(halt_q_addr +
					  (uलघु)ASC_SCSIQ_B_STATUS),
				 q_status);

		scsi_busy = AscReadLramByte(iop_base, (uलघु)ASCV_SCSIBUSY_B);
		scsi_busy &= ~target_id;
		AscWriteLramByte(iop_base, (uलघु)ASCV_SCSIBUSY_B, scsi_busy);

		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		वापस;
	पूर्ण अन्यथा अगर (पूर्णांक_halt_code == ASC_HALT_SDTR_REJECTED) अणु

		AscMemWordCopyPtrFromLram(iop_base,
					  ASCV_MSGOUT_BEG,
					  (uअक्षर *)&out_msg,
					  माप(EXT_MSG) >> 1);

		अगर ((out_msg.msg_type == EXTENDED_MESSAGE) &&
		    (out_msg.msg_len == MS_SDTR_LEN) &&
		    (out_msg.msg_req == EXTENDED_SDTR)) अणु

			asc_dvc->init_sdtr &= ~target_id;
			asc_dvc->sdtr_करोne &= ~target_id;
			AscSetChipSDTR(iop_base, asyn_sdtr, tid_no);
			boardp->sdtr_data[tid_no] = asyn_sdtr;
		पूर्ण
		q_cntl &= ~QC_MSG_OUT;
		AscWriteLramByte(iop_base,
				 (uलघु)(halt_q_addr +
					  (uलघु)ASC_SCSIQ_B_CNTL), q_cntl);
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		वापस;
	पूर्ण अन्यथा अगर (पूर्णांक_halt_code == ASC_HALT_SS_QUEUE_FULL) अणु

		scsi_status = AscReadLramByte(iop_base,
					      (uलघु)((uलघु)halt_q_addr +
						       (uलघु)
						       ASC_SCSIQ_SCSI_STATUS));
		cur_dvc_qng =
		    AscReadLramByte(iop_base,
				    (uलघु)((uलघु)ASC_QADR_BEG +
					     (uलघु)target_ix));
		अगर ((cur_dvc_qng > 0) && (asc_dvc->cur_dvc_qng[tid_no] > 0)) अणु

			scsi_busy = AscReadLramByte(iop_base,
						    (uलघु)ASCV_SCSIBUSY_B);
			scsi_busy |= target_id;
			AscWriteLramByte(iop_base,
					 (uलघु)ASCV_SCSIBUSY_B, scsi_busy);
			asc_dvc->queue_full_or_busy |= target_id;

			अगर (scsi_status == SAM_STAT_TASK_SET_FULL) अणु
				अगर (cur_dvc_qng > ASC_MIN_TAGGED_CMD) अणु
					cur_dvc_qng -= 1;
					asc_dvc->max_dvc_qng[tid_no] =
					    cur_dvc_qng;

					AscWriteLramByte(iop_base,
							 (uलघु)((uलघु)
								  ASCV_MAX_DVC_QNG_BEG
								  + (uलघु)
								  tid_no),
							 cur_dvc_qng);

					/*
					 * Set the device queue depth to the
					 * number of active requests when the
					 * QUEUE FULL condition was encountered.
					 */
					boardp->queue_full |= target_id;
					boardp->queue_full_cnt[tid_no] =
					    cur_dvc_qng;
				पूर्ण
			पूर्ण
		पूर्ण
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		वापस;
	पूर्ण
	वापस;
पूर्ण

/*
 * व्योम
 * DvcGetQinfo(PortAddr iop_base, uलघु s_addr, uअक्षर *inbuf, पूर्णांक words)
 *
 * Calling/Exit State:
 *    none
 *
 * Description:
 *     Input an ASC_QDONE_INFO काष्ठाure from the chip
 */
अटल व्योम
DvcGetQinfo(PortAddr iop_base, uलघु s_addr, uअक्षर *inbuf, पूर्णांक words)
अणु
	पूर्णांक i;
	uलघु word;

	AscSetChipLramAddr(iop_base, s_addr);
	क्रम (i = 0; i < 2 * words; i += 2) अणु
		अगर (i == 10) अणु
			जारी;
		पूर्ण
		word = inpw(iop_base + IOP_RAM_DATA);
		inbuf[i] = word & 0xff;
		inbuf[i + 1] = (word >> 8) & 0xff;
	पूर्ण
	ASC_DBG_PRT_HEX(2, "DvcGetQinfo", inbuf, 2 * words);
पूर्ण

अटल uअक्षर
_AscCopyLramScsiDoneQ(PortAddr iop_base,
		      uलघु q_addr,
		      ASC_QDONE_INFO *scsiq, अचिन्हित पूर्णांक max_dma_count)
अणु
	uलघु _val;
	uअक्षर sg_queue_cnt;

	DvcGetQinfo(iop_base,
		    q_addr + ASC_SCSIQ_DONE_INFO_BEG,
		    (uअक्षर *)scsiq,
		    (माप(ASC_SCSIQ_2) + माप(ASC_SCSIQ_3)) / 2);

	_val = AscReadLramWord(iop_base,
			       (uलघु)(q_addr + (uलघु)ASC_SCSIQ_B_STATUS));
	scsiq->q_status = (uअक्षर)_val;
	scsiq->q_no = (uअक्षर)(_val >> 8);
	_val = AscReadLramWord(iop_base,
			       (uलघु)(q_addr + (uलघु)ASC_SCSIQ_B_CNTL));
	scsiq->cntl = (uअक्षर)_val;
	sg_queue_cnt = (uअक्षर)(_val >> 8);
	_val = AscReadLramWord(iop_base,
			       (uलघु)(q_addr +
					(uलघु)ASC_SCSIQ_B_SENSE_LEN));
	scsiq->sense_len = (uअक्षर)_val;
	scsiq->extra_bytes = (uअक्षर)(_val >> 8);

	/*
	 * Read high word of reमुख्य bytes from alternate location.
	 */
	scsiq->reमुख्य_bytes = (((u32)AscReadLramWord(iop_base,
						     (uलघु)(q_addr +
							      (uलघु)
							      ASC_SCSIQ_W_ALT_DC1)))
			       << 16);
	/*
	 * Read low word of reमुख्य bytes from original location.
	 */
	scsiq->reमुख्य_bytes += AscReadLramWord(iop_base,
					       (uलघु)(q_addr + (uलघु)
							ASC_SCSIQ_DW_REMAIN_XFER_CNT));

	scsiq->reमुख्य_bytes &= max_dma_count;
	वापस sg_queue_cnt;
पूर्ण

/*
 * asc_isr_callback() - Second Level Interrupt Handler called by AscISR().
 *
 * Interrupt callback function क्रम the Narrow SCSI Asc Library.
 */
अटल व्योम asc_isr_callback(ASC_DVC_VAR *asc_dvc_varp, ASC_QDONE_INFO *qकरोnep)
अणु
	काष्ठा asc_board *boardp = asc_dvc_varp->drv_ptr;
	u32 srb_tag;
	काष्ठा scsi_cmnd *scp;

	ASC_DBG(1, "asc_dvc_varp 0x%p, qdonep 0x%p\n", asc_dvc_varp, qकरोnep);
	ASC_DBG_PRT_ASC_QDONE_INFO(2, qकरोnep);

	/*
	 * Decrease the srb_tag by 1 to find the SCSI command
	 */
	srb_tag = qकरोnep->d2.srb_tag - 1;
	scp = scsi_host_find_tag(boardp->shost, srb_tag);
	अगर (!scp)
		वापस;

	ASC_DBG_PRT_CDB(2, scp->cmnd, scp->cmd_len);

	ASC_STATS(boardp->shost, callback);

	dma_unmap_single(boardp->dev, scp->SCp.dma_handle,
			 SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
	/*
	 * 'qdonep' contains the command's ending status.
	 */
	scp->result = 0;
	चयन (qकरोnep->d3.करोne_stat) अणु
	हाल QD_NO_ERROR:
		ASC_DBG(2, "QD_NO_ERROR\n");

		/*
		 * Check क्रम an underrun condition.
		 *
		 * If there was no error and an underrun condition, then
		 * वापस the number of underrun bytes.
		 */
		अगर (scsi_bufflen(scp) != 0 && qकरोnep->reमुख्य_bytes != 0 &&
		    qकरोnep->reमुख्य_bytes <= scsi_bufflen(scp)) अणु
			ASC_DBG(1, "underrun condition %u bytes\n",
				 (अचिन्हित)qकरोnep->reमुख्य_bytes);
			scsi_set_resid(scp, qकरोnep->reमुख्य_bytes);
		पूर्ण
		अवरोध;

	हाल QD_WITH_ERROR:
		ASC_DBG(2, "QD_WITH_ERROR\n");
		चयन (qकरोnep->d3.host_stat) अणु
		हाल QHSTA_NO_ERROR:
			set_status_byte(scp, qकरोnep->d3.scsi_stat);
			अगर (qकरोnep->d3.scsi_stat == SAM_STAT_CHECK_CONDITION) अणु
				ASC_DBG(2, "SAM_STAT_CHECK_CONDITION\n");
				ASC_DBG_PRT_SENSE(2, scp->sense_buffer,
						  SCSI_SENSE_BUFFERSIZE);
				set_driver_byte(scp, DRIVER_SENSE);
			पूर्ण
			अवरोध;

		शेष:
			/* QHSTA error occurred */
			ASC_DBG(1, "host_stat 0x%x\n", qकरोnep->d3.host_stat);
			set_host_byte(scp, DID_BAD_TARGET);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल QD_ABORTED_BY_HOST:
		ASC_DBG(1, "QD_ABORTED_BY_HOST\n");
		set_status_byte(scp, qकरोnep->d3.scsi_stat);
		set_msg_byte(scp, qकरोnep->d3.scsi_msg);
		set_host_byte(scp, DID_ABORT);
		अवरोध;

	शेष:
		ASC_DBG(1, "done_stat 0x%x\n", qकरोnep->d3.करोne_stat);
		set_status_byte(scp, qकरोnep->d3.scsi_stat);
		set_msg_byte(scp, qकरोnep->d3.scsi_msg);
		set_host_byte(scp, DID_ERROR);
		अवरोध;
	पूर्ण

	/*
	 * If the 'init_tidmask' bit isn't alपढ़ोy set क्रम the target and the
	 * current request finished normally, then set the bit क्रम the target
	 * to indicate that a device is present.
	 */
	अगर ((boardp->init_tidmask & ADV_TID_TO_TIDMASK(scp->device->id)) == 0 &&
	    qकरोnep->d3.करोne_stat == QD_NO_ERROR &&
	    qकरोnep->d3.host_stat == QHSTA_NO_ERROR) अणु
		boardp->init_tidmask |= ADV_TID_TO_TIDMASK(scp->device->id);
	पूर्ण

	asc_scsi_करोne(scp);
पूर्ण

अटल पूर्णांक AscIsrQDone(ASC_DVC_VAR *asc_dvc)
अणु
	uअक्षर next_qp;
	uअक्षर n_q_used;
	uअक्षर sg_list_qp;
	uअक्षर sg_queue_cnt;
	uअक्षर q_cnt;
	uअक्षर करोne_q_tail;
	uअक्षर tid_no;
	ASC_SCSI_BIT_ID_TYPE scsi_busy;
	ASC_SCSI_BIT_ID_TYPE target_id;
	PortAddr iop_base;
	uलघु q_addr;
	uलघु sg_q_addr;
	uअक्षर cur_target_qng;
	ASC_QDONE_INFO scsiq_buf;
	ASC_QDONE_INFO *scsiq;
	bool false_overrun;

	iop_base = asc_dvc->iop_base;
	n_q_used = 1;
	scsiq = (ASC_QDONE_INFO *)&scsiq_buf;
	करोne_q_tail = (uअक्षर)AscGetVarDoneQTail(iop_base);
	q_addr = ASC_QNO_TO_QADDR(करोne_q_tail);
	next_qp = AscReadLramByte(iop_base,
				  (uलघु)(q_addr + (uलघु)ASC_SCSIQ_B_FWD));
	अगर (next_qp != ASC_QLINK_END) अणु
		AscPutVarDoneQTail(iop_base, next_qp);
		q_addr = ASC_QNO_TO_QADDR(next_qp);
		sg_queue_cnt = _AscCopyLramScsiDoneQ(iop_base, q_addr, scsiq,
						     asc_dvc->max_dma_count);
		AscWriteLramByte(iop_base,
				 (uलघु)(q_addr +
					  (uलघु)ASC_SCSIQ_B_STATUS),
				 (uअक्षर)(scsiq->
					 q_status & (uअक्षर)~(QS_READY |
							     QS_ABORTED)));
		tid_no = ASC_TIX_TO_TID(scsiq->d2.target_ix);
		target_id = ASC_TIX_TO_TARGET_ID(scsiq->d2.target_ix);
		अगर ((scsiq->cntl & QC_SG_HEAD) != 0) अणु
			sg_q_addr = q_addr;
			sg_list_qp = next_qp;
			क्रम (q_cnt = 0; q_cnt < sg_queue_cnt; q_cnt++) अणु
				sg_list_qp = AscReadLramByte(iop_base,
							     (uलघु)(sg_q_addr
								      + (uलघु)
								      ASC_SCSIQ_B_FWD));
				sg_q_addr = ASC_QNO_TO_QADDR(sg_list_qp);
				अगर (sg_list_qp == ASC_QLINK_END) अणु
					AscSetLibErrorCode(asc_dvc,
							   ASCQ_ERR_SG_Q_LINKS);
					scsiq->d3.करोne_stat = QD_WITH_ERROR;
					scsiq->d3.host_stat =
					    QHSTA_D_QDONE_SG_LIST_CORRUPTED;
					जाओ FATAL_ERR_QDONE;
				पूर्ण
				AscWriteLramByte(iop_base,
						 (uलघु)(sg_q_addr + (uलघु)
							  ASC_SCSIQ_B_STATUS),
						 QS_FREE);
			पूर्ण
			n_q_used = sg_queue_cnt + 1;
			AscPutVarDoneQTail(iop_base, sg_list_qp);
		पूर्ण
		अगर (asc_dvc->queue_full_or_busy & target_id) अणु
			cur_target_qng = AscReadLramByte(iop_base,
							 (uलघु)((uलघु)
								  ASC_QADR_BEG
								  + (uलघु)
								  scsiq->d2.
								  target_ix));
			अगर (cur_target_qng < asc_dvc->max_dvc_qng[tid_no]) अणु
				scsi_busy = AscReadLramByte(iop_base, (uलघु)
							    ASCV_SCSIBUSY_B);
				scsi_busy &= ~target_id;
				AscWriteLramByte(iop_base,
						 (uलघु)ASCV_SCSIBUSY_B,
						 scsi_busy);
				asc_dvc->queue_full_or_busy &= ~target_id;
			पूर्ण
		पूर्ण
		अगर (asc_dvc->cur_total_qng >= n_q_used) अणु
			asc_dvc->cur_total_qng -= n_q_used;
			अगर (asc_dvc->cur_dvc_qng[tid_no] != 0) अणु
				asc_dvc->cur_dvc_qng[tid_no]--;
			पूर्ण
		पूर्ण अन्यथा अणु
			AscSetLibErrorCode(asc_dvc, ASCQ_ERR_CUR_QNG);
			scsiq->d3.करोne_stat = QD_WITH_ERROR;
			जाओ FATAL_ERR_QDONE;
		पूर्ण
		अगर ((scsiq->d2.srb_tag == 0UL) ||
		    ((scsiq->q_status & QS_ABORTED) != 0)) अणु
			वापस (0x11);
		पूर्ण अन्यथा अगर (scsiq->q_status == QS_DONE) अणु
			/*
			 * This is also curious.
			 * false_overrun will _always_ be set to 'false'
			 */
			false_overrun = false;
			अगर (scsiq->extra_bytes != 0) अणु
				scsiq->reमुख्य_bytes += scsiq->extra_bytes;
			पूर्ण
			अगर (scsiq->d3.करोne_stat == QD_WITH_ERROR) अणु
				अगर (scsiq->d3.host_stat ==
				    QHSTA_M_DATA_OVER_RUN) अणु
					अगर ((scsiq->
					     cntl & (QC_DATA_IN | QC_DATA_OUT))
					    == 0) अणु
						scsiq->d3.करोne_stat =
						    QD_NO_ERROR;
						scsiq->d3.host_stat =
						    QHSTA_NO_ERROR;
					पूर्ण अन्यथा अगर (false_overrun) अणु
						scsiq->d3.करोne_stat =
						    QD_NO_ERROR;
						scsiq->d3.host_stat =
						    QHSTA_NO_ERROR;
					पूर्ण
				पूर्ण अन्यथा अगर (scsiq->d3.host_stat ==
					   QHSTA_M_HUNG_REQ_SCSI_BUS_RESET) अणु
					AscStopChip(iop_base);
					AscSetChipControl(iop_base,
							  (uअक्षर)(CC_SCSI_RESET
								  | CC_HALT));
					udelay(60);
					AscSetChipControl(iop_base, CC_HALT);
					AscSetChipStatus(iop_base,
							 CIW_CLR_SCSI_RESET_INT);
					AscSetChipStatus(iop_base, 0);
					AscSetChipControl(iop_base, 0);
				पूर्ण
			पूर्ण
			अगर ((scsiq->cntl & QC_NO_CALLBACK) == 0) अणु
				asc_isr_callback(asc_dvc, scsiq);
			पूर्ण अन्यथा अणु
				अगर ((AscReadLramByte(iop_base,
						     (uलघु)(q_addr + (uलघु)
							      ASC_SCSIQ_CDB_BEG))
				     == START_STOP)) अणु
					asc_dvc->unit_not_पढ़ोy &= ~target_id;
					अगर (scsiq->d3.करोne_stat != QD_NO_ERROR) अणु
						asc_dvc->start_motor &=
						    ~target_id;
					पूर्ण
				पूर्ण
			पूर्ण
			वापस (1);
		पूर्ण अन्यथा अणु
			AscSetLibErrorCode(asc_dvc, ASCQ_ERR_Q_STATUS);
 FATAL_ERR_QDONE:
			अगर ((scsiq->cntl & QC_NO_CALLBACK) == 0) अणु
				asc_isr_callback(asc_dvc, scsiq);
			पूर्ण
			वापस (0x80);
		पूर्ण
	पूर्ण
	वापस (0);
पूर्ण

अटल पूर्णांक AscISR(ASC_DVC_VAR *asc_dvc)
अणु
	ASC_CS_TYPE chipstat;
	PortAddr iop_base;
	uलघु saved_ram_addr;
	uअक्षर ctrl_reg;
	uअक्षर saved_ctrl_reg;
	पूर्णांक पूर्णांक_pending;
	पूर्णांक status;
	uअक्षर host_flag;

	iop_base = asc_dvc->iop_base;
	पूर्णांक_pending = ASC_FALSE;

	अगर (AscIsIntPending(iop_base) == 0)
		वापस पूर्णांक_pending;

	अगर ((asc_dvc->init_state & ASC_INIT_STATE_END_LOAD_MC) == 0) अणु
		वापस ASC_ERROR;
	पूर्ण
	अगर (asc_dvc->in_critical_cnt != 0) अणु
		AscSetLibErrorCode(asc_dvc, ASCQ_ERR_ISR_ON_CRITICAL);
		वापस ASC_ERROR;
	पूर्ण
	अगर (asc_dvc->is_in_पूर्णांक) अणु
		AscSetLibErrorCode(asc_dvc, ASCQ_ERR_ISR_RE_ENTRY);
		वापस ASC_ERROR;
	पूर्ण
	asc_dvc->is_in_पूर्णांक = true;
	ctrl_reg = AscGetChipControl(iop_base);
	saved_ctrl_reg = ctrl_reg & (~(CC_SCSI_RESET | CC_CHIP_RESET |
				       CC_SINGLE_STEP | CC_DIAG | CC_TEST));
	chipstat = AscGetChipStatus(iop_base);
	अगर (chipstat & CSW_SCSI_RESET_LATCH) अणु
		अगर (!(asc_dvc->bus_type & (ASC_IS_VL | ASC_IS_EISA))) अणु
			पूर्णांक i = 10;
			पूर्णांक_pending = ASC_TRUE;
			asc_dvc->sdtr_करोne = 0;
			saved_ctrl_reg &= (uअक्षर)(~CC_HALT);
			जबतक ((AscGetChipStatus(iop_base) &
				CSW_SCSI_RESET_ACTIVE) && (i-- > 0)) अणु
				mdelay(100);
			पूर्ण
			AscSetChipControl(iop_base, (CC_CHIP_RESET | CC_HALT));
			AscSetChipControl(iop_base, CC_HALT);
			AscSetChipStatus(iop_base, CIW_CLR_SCSI_RESET_INT);
			AscSetChipStatus(iop_base, 0);
			chipstat = AscGetChipStatus(iop_base);
		पूर्ण
	पूर्ण
	saved_ram_addr = AscGetChipLramAddr(iop_base);
	host_flag = AscReadLramByte(iop_base,
				    ASCV_HOST_FLAG_B) &
	    (uअक्षर)(~ASC_HOST_FLAG_IN_ISR);
	AscWriteLramByte(iop_base, ASCV_HOST_FLAG_B,
			 (uअक्षर)(host_flag | (uअक्षर)ASC_HOST_FLAG_IN_ISR));
	अगर ((chipstat & CSW_INT_PENDING) || (पूर्णांक_pending)) अणु
		AscAckInterrupt(iop_base);
		पूर्णांक_pending = ASC_TRUE;
		अगर ((chipstat & CSW_HALTED) && (ctrl_reg & CC_SINGLE_STEP)) अणु
			AscIsrChipHalted(asc_dvc);
			saved_ctrl_reg &= (uअक्षर)(~CC_HALT);
		पूर्ण अन्यथा अणु
			अगर ((asc_dvc->dvc_cntl & ASC_CNTL_INT_MULTI_Q) != 0) अणु
				जबतक (((status =
					 AscIsrQDone(asc_dvc)) & 0x01) != 0) अणु
				पूर्ण
			पूर्ण अन्यथा अणु
				करो अणु
					अगर ((status =
					     AscIsrQDone(asc_dvc)) == 1) अणु
						अवरोध;
					पूर्ण
				पूर्ण जबतक (status == 0x11);
			पूर्ण
			अगर ((status & 0x80) != 0)
				पूर्णांक_pending = ASC_ERROR;
		पूर्ण
	पूर्ण
	AscWriteLramByte(iop_base, ASCV_HOST_FLAG_B, host_flag);
	AscSetChipLramAddr(iop_base, saved_ram_addr);
	AscSetChipControl(iop_base, saved_ctrl_reg);
	asc_dvc->is_in_पूर्णांक = false;
	वापस पूर्णांक_pending;
पूर्ण

/*
 * advansys_reset()
 *
 * Reset the host associated with the command 'scp'.
 *
 * This function runs its own thपढ़ो. Interrupts must be blocked but
 * sleeping is allowed and no locking other than क्रम host काष्ठाures is
 * required. Returns SUCCESS or FAILED.
 */
अटल पूर्णांक advansys_reset(काष्ठा scsi_cmnd *scp)
अणु
	काष्ठा Scsi_Host *shost = scp->device->host;
	काष्ठा asc_board *boardp = shost_priv(shost);
	अचिन्हित दीर्घ flags;
	पूर्णांक status;
	पूर्णांक ret = SUCCESS;

	ASC_DBG(1, "0x%p\n", scp);

	ASC_STATS(shost, reset);

	scmd_prपूर्णांकk(KERN_INFO, scp, "SCSI host reset started...\n");

	अगर (ASC_NARROW_BOARD(boardp)) अणु
		ASC_DVC_VAR *asc_dvc = &boardp->dvc_var.asc_dvc_var;

		/* Reset the chip and SCSI bus. */
		ASC_DBG(1, "before AscInitAsc1000Driver()\n");
		status = AscInitAsc1000Driver(asc_dvc);

		/* Refer to ASC_IERR_* definitions क्रम meaning of 'err_code'. */
		अगर (asc_dvc->err_code || !asc_dvc->overrun_dma) अणु
			scmd_prपूर्णांकk(KERN_INFO, scp, "SCSI host reset error: "
				    "0x%x, status: 0x%x\n", asc_dvc->err_code,
				    status);
			ret = FAILED;
		पूर्ण अन्यथा अगर (status) अणु
			scmd_prपूर्णांकk(KERN_INFO, scp, "SCSI host reset warning: "
				    "0x%x\n", status);
		पूर्ण अन्यथा अणु
			scmd_prपूर्णांकk(KERN_INFO, scp, "SCSI host reset "
				    "successful\n");
		पूर्ण

		ASC_DBG(1, "after AscInitAsc1000Driver()\n");
	पूर्ण अन्यथा अणु
		/*
		 * If the suggest reset bus flags are set, then reset the bus.
		 * Otherwise only reset the device.
		 */
		ADV_DVC_VAR *adv_dvc = &boardp->dvc_var.adv_dvc_var;

		/*
		 * Reset the chip and SCSI bus.
		 */
		ASC_DBG(1, "before AdvResetChipAndSB()\n");
		चयन (AdvResetChipAndSB(adv_dvc)) अणु
		हाल ASC_TRUE:
			scmd_prपूर्णांकk(KERN_INFO, scp, "SCSI host reset "
				    "successful\n");
			अवरोध;
		हाल ASC_FALSE:
		शेष:
			scmd_prपूर्णांकk(KERN_INFO, scp, "SCSI host reset error\n");
			ret = FAILED;
			अवरोध;
		पूर्ण
		spin_lock_irqsave(shost->host_lock, flags);
		AdvISR(adv_dvc);
		spin_unlock_irqrestore(shost->host_lock, flags);
	पूर्ण

	ASC_DBG(1, "ret %d\n", ret);

	वापस ret;
पूर्ण

/*
 * advansys_biosparam()
 *
 * Translate disk drive geometry अगर the "BIOS greater than 1 GB"
 * support is enabled क्रम a drive.
 *
 * ip (inक्रमmation poपूर्णांकer) is an पूर्णांक array with the following definition:
 * ip[0]: heads
 * ip[1]: sectors
 * ip[2]: cylinders
 */
अटल पूर्णांक
advansys_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
		   sector_t capacity, पूर्णांक ip[])
अणु
	काष्ठा asc_board *boardp = shost_priv(sdev->host);

	ASC_DBG(1, "begin\n");
	ASC_STATS(sdev->host, biosparam);
	अगर (ASC_NARROW_BOARD(boardp)) अणु
		अगर ((boardp->dvc_var.asc_dvc_var.dvc_cntl &
		     ASC_CNTL_BIOS_GT_1GB) && capacity > 0x200000) अणु
			ip[0] = 255;
			ip[1] = 63;
		पूर्ण अन्यथा अणु
			ip[0] = 64;
			ip[1] = 32;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((boardp->dvc_var.adv_dvc_var.bios_ctrl &
		     BIOS_CTRL_EXTENDED_XLAT) && capacity > 0x200000) अणु
			ip[0] = 255;
			ip[1] = 63;
		पूर्ण अन्यथा अणु
			ip[0] = 64;
			ip[1] = 32;
		पूर्ण
	पूर्ण
	ip[2] = (अचिन्हित दीर्घ)capacity / (ip[0] * ip[1]);
	ASC_DBG(1, "end\n");
	वापस 0;
पूर्ण

/*
 * First-level पूर्णांकerrupt handler.
 *
 * 'dev_id' is a pointer to the interrupting adapter's Scsi_Host.
 */
अटल irqवापस_t advansys_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा Scsi_Host *shost = dev_id;
	काष्ठा asc_board *boardp = shost_priv(shost);
	irqवापस_t result = IRQ_NONE;
	अचिन्हित दीर्घ flags;

	ASC_DBG(2, "boardp 0x%p\n", boardp);
	spin_lock_irqsave(shost->host_lock, flags);
	अगर (ASC_NARROW_BOARD(boardp)) अणु
		अगर (AscIsIntPending(shost->io_port)) अणु
			result = IRQ_HANDLED;
			ASC_STATS(shost, पूर्णांकerrupt);
			ASC_DBG(1, "before AscISR()\n");
			AscISR(&boardp->dvc_var.asc_dvc_var);
		पूर्ण
	पूर्ण अन्यथा अणु
		ASC_DBG(1, "before AdvISR()\n");
		अगर (AdvISR(&boardp->dvc_var.adv_dvc_var)) अणु
			result = IRQ_HANDLED;
			ASC_STATS(shost, पूर्णांकerrupt);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);

	ASC_DBG(1, "end\n");
	वापस result;
पूर्ण

अटल bool AscHostReqRiscHalt(PortAddr iop_base)
अणु
	पूर्णांक count = 0;
	bool sta = false;
	uअक्षर saved_stop_code;

	अगर (AscIsChipHalted(iop_base))
		वापस true;
	saved_stop_code = AscReadLramByte(iop_base, ASCV_STOP_CODE_B);
	AscWriteLramByte(iop_base, ASCV_STOP_CODE_B,
			 ASC_STOP_HOST_REQ_RISC_HALT | ASC_STOP_REQ_RISC_STOP);
	करो अणु
		अगर (AscIsChipHalted(iop_base)) अणु
			sta = true;
			अवरोध;
		पूर्ण
		mdelay(100);
	पूर्ण जबतक (count++ < 20);
	AscWriteLramByte(iop_base, ASCV_STOP_CODE_B, saved_stop_code);
	वापस sta;
पूर्ण

अटल bool
AscSetRunChipSynRegAtID(PortAddr iop_base, uअक्षर tid_no, uअक्षर sdtr_data)
अणु
	bool sta = false;

	अगर (AscHostReqRiscHalt(iop_base)) अणु
		sta = AscSetChipSynRegAtID(iop_base, tid_no, sdtr_data);
		AscStartChip(iop_base);
	पूर्ण
	वापस sta;
पूर्ण

अटल व्योम AscAsyncFix(ASC_DVC_VAR *asc_dvc, काष्ठा scsi_device *sdev)
अणु
	अक्षर type = sdev->type;
	ASC_SCSI_BIT_ID_TYPE tid_bits = 1 << sdev->id;

	अगर (!(asc_dvc->bug_fix_cntl & ASC_BUG_FIX_ASYN_USE_SYN))
		वापस;
	अगर (asc_dvc->init_sdtr & tid_bits)
		वापस;

	अगर ((type == TYPE_ROM) && (म_भेदन(sdev->venकरोr, "HP ", 3) == 0))
		asc_dvc->pci_fix_asyn_xfer_always |= tid_bits;

	asc_dvc->pci_fix_asyn_xfer |= tid_bits;
	अगर ((type == TYPE_PROCESSOR) || (type == TYPE_SCANNER) ||
	    (type == TYPE_ROM) || (type == TYPE_TAPE))
		asc_dvc->pci_fix_asyn_xfer &= ~tid_bits;

	अगर (asc_dvc->pci_fix_asyn_xfer & tid_bits)
		AscSetRunChipSynRegAtID(asc_dvc->iop_base, sdev->id,
					ASYN_SDTR_DATA_FIX_PCI_REV_AB);
पूर्ण

अटल व्योम
advansys_narrow_slave_configure(काष्ठा scsi_device *sdev, ASC_DVC_VAR *asc_dvc)
अणु
	ASC_SCSI_BIT_ID_TYPE tid_bit = 1 << sdev->id;
	ASC_SCSI_BIT_ID_TYPE orig_use_tagged_qng = asc_dvc->use_tagged_qng;

	अगर (sdev->lun == 0) अणु
		ASC_SCSI_BIT_ID_TYPE orig_init_sdtr = asc_dvc->init_sdtr;
		अगर ((asc_dvc->cfg->sdtr_enable & tid_bit) && sdev->sdtr) अणु
			asc_dvc->init_sdtr |= tid_bit;
		पूर्ण अन्यथा अणु
			asc_dvc->init_sdtr &= ~tid_bit;
		पूर्ण

		अगर (orig_init_sdtr != asc_dvc->init_sdtr)
			AscAsyncFix(asc_dvc, sdev);
	पूर्ण

	अगर (sdev->tagged_supported) अणु
		अगर (asc_dvc->cfg->cmd_qng_enabled & tid_bit) अणु
			अगर (sdev->lun == 0) अणु
				asc_dvc->cfg->can_tagged_qng |= tid_bit;
				asc_dvc->use_tagged_qng |= tid_bit;
			पूर्ण
			scsi_change_queue_depth(sdev, 
						asc_dvc->max_dvc_qng[sdev->id]);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (sdev->lun == 0) अणु
			asc_dvc->cfg->can_tagged_qng &= ~tid_bit;
			asc_dvc->use_tagged_qng &= ~tid_bit;
		पूर्ण
	पूर्ण

	अगर ((sdev->lun == 0) &&
	    (orig_use_tagged_qng != asc_dvc->use_tagged_qng)) अणु
		AscWriteLramByte(asc_dvc->iop_base, ASCV_DISC_ENABLE_B,
				 asc_dvc->cfg->disc_enable);
		AscWriteLramByte(asc_dvc->iop_base, ASCV_USE_TAGGED_QNG_B,
				 asc_dvc->use_tagged_qng);
		AscWriteLramByte(asc_dvc->iop_base, ASCV_CAN_TAGGED_QNG_B,
				 asc_dvc->cfg->can_tagged_qng);

		asc_dvc->max_dvc_qng[sdev->id] =
					asc_dvc->cfg->max_tag_qng[sdev->id];
		AscWriteLramByte(asc_dvc->iop_base,
				 (uलघु)(ASCV_MAX_DVC_QNG_BEG + sdev->id),
				 asc_dvc->max_dvc_qng[sdev->id]);
	पूर्ण
पूर्ण

/*
 * Wide Transfers
 *
 * If the EEPROM enabled WDTR क्रम the device and the device supports wide
 * bus (16 bit) transfers, then turn on the device's 'wdtr_able' bit and
 * ग_लिखो the new value to the microcode.
 */
अटल व्योम
advansys_wide_enable_wdtr(AdvPortAddr iop_base, अचिन्हित लघु tidmask)
अणु
	अचिन्हित लघु cfg_word;
	AdvReadWordLram(iop_base, ASC_MC_WDTR_ABLE, cfg_word);
	अगर ((cfg_word & tidmask) != 0)
		वापस;

	cfg_word |= tidmask;
	AdvWriteWordLram(iop_base, ASC_MC_WDTR_ABLE, cfg_word);

	/*
	 * Clear the microcode SDTR and WDTR negotiation करोne indicators क्रम
	 * the target to cause it to negotiate with the new setting set above.
	 * WDTR when accepted causes the target to enter asynchronous mode, so
	 * SDTR must be negotiated.
	 */
	AdvReadWordLram(iop_base, ASC_MC_SDTR_DONE, cfg_word);
	cfg_word &= ~tidmask;
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_DONE, cfg_word);
	AdvReadWordLram(iop_base, ASC_MC_WDTR_DONE, cfg_word);
	cfg_word &= ~tidmask;
	AdvWriteWordLram(iop_base, ASC_MC_WDTR_DONE, cfg_word);
पूर्ण

/*
 * Synchronous Transfers
 *
 * If the EEPROM enabled SDTR क्रम the device and the device
 * supports synchronous transfers, then turn on the device's
 * 'sdtr_able' bit. Write the new value to the microcode.
 */
अटल व्योम
advansys_wide_enable_sdtr(AdvPortAddr iop_base, अचिन्हित लघु tidmask)
अणु
	अचिन्हित लघु cfg_word;
	AdvReadWordLram(iop_base, ASC_MC_SDTR_ABLE, cfg_word);
	अगर ((cfg_word & tidmask) != 0)
		वापस;

	cfg_word |= tidmask;
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_ABLE, cfg_word);

	/*
	 * Clear the microcode "SDTR negotiation" करोne indicator क्रम the
	 * target to cause it to negotiate with the new setting set above.
	 */
	AdvReadWordLram(iop_base, ASC_MC_SDTR_DONE, cfg_word);
	cfg_word &= ~tidmask;
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_DONE, cfg_word);
पूर्ण

/*
 * PPR (Parallel Protocol Request) Capable
 *
 * If the device supports DT mode, then it must be PPR capable.
 * The PPR message will be used in place of the SDTR and WDTR
 * messages to negotiate synchronous speed and offset, transfer
 * width, and protocol options.
 */
अटल व्योम advansys_wide_enable_ppr(ADV_DVC_VAR *adv_dvc,
				AdvPortAddr iop_base, अचिन्हित लघु tidmask)
अणु
	AdvReadWordLram(iop_base, ASC_MC_PPR_ABLE, adv_dvc->ppr_able);
	adv_dvc->ppr_able |= tidmask;
	AdvWriteWordLram(iop_base, ASC_MC_PPR_ABLE, adv_dvc->ppr_able);
पूर्ण

अटल व्योम
advansys_wide_slave_configure(काष्ठा scsi_device *sdev, ADV_DVC_VAR *adv_dvc)
अणु
	AdvPortAddr iop_base = adv_dvc->iop_base;
	अचिन्हित लघु tidmask = 1 << sdev->id;

	अगर (sdev->lun == 0) अणु
		/*
		 * Handle WDTR, SDTR, and Tag Queuing. If the feature
		 * is enabled in the EEPROM and the device supports the
		 * feature, then enable it in the microcode.
		 */

		अगर ((adv_dvc->wdtr_able & tidmask) && sdev->wdtr)
			advansys_wide_enable_wdtr(iop_base, tidmask);
		अगर ((adv_dvc->sdtr_able & tidmask) && sdev->sdtr)
			advansys_wide_enable_sdtr(iop_base, tidmask);
		अगर (adv_dvc->chip_type == ADV_CHIP_ASC38C1600 && sdev->ppr)
			advansys_wide_enable_ppr(adv_dvc, iop_base, tidmask);

		/*
		 * Tag Queuing is disabled क्रम the BIOS which runs in polled
		 * mode and would see no benefit from Tag Queuing. Also by
		 * disabling Tag Queuing in the BIOS devices with Tag Queuing
		 * bugs will at least work with the BIOS.
		 */
		अगर ((adv_dvc->tagqng_able & tidmask) &&
		    sdev->tagged_supported) अणु
			अचिन्हित लघु cfg_word;
			AdvReadWordLram(iop_base, ASC_MC_TAGQNG_ABLE, cfg_word);
			cfg_word |= tidmask;
			AdvWriteWordLram(iop_base, ASC_MC_TAGQNG_ABLE,
					 cfg_word);
			AdvWriteByteLram(iop_base,
					 ASC_MC_NUMBER_OF_MAX_CMD + sdev->id,
					 adv_dvc->max_dvc_qng);
		पूर्ण
	पूर्ण

	अगर ((adv_dvc->tagqng_able & tidmask) && sdev->tagged_supported)
		scsi_change_queue_depth(sdev, adv_dvc->max_dvc_qng);
पूर्ण

/*
 * Set the number of commands to queue per device क्रम the
 * specअगरied host adapter.
 */
अटल पूर्णांक advansys_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा asc_board *boardp = shost_priv(sdev->host);

	अगर (ASC_NARROW_BOARD(boardp))
		advansys_narrow_slave_configure(sdev,
						&boardp->dvc_var.asc_dvc_var);
	अन्यथा
		advansys_wide_slave_configure(sdev,
						&boardp->dvc_var.adv_dvc_var);

	वापस 0;
पूर्ण

अटल __le32 asc_get_sense_buffer_dma(काष्ठा scsi_cmnd *scp)
अणु
	काष्ठा asc_board *board = shost_priv(scp->device->host);

	scp->SCp.dma_handle = dma_map_single(board->dev, scp->sense_buffer,
					     SCSI_SENSE_BUFFERSIZE,
					     DMA_FROM_DEVICE);
	अगर (dma_mapping_error(board->dev, scp->SCp.dma_handle)) अणु
		ASC_DBG(1, "failed to map sense buffer\n");
		वापस 0;
	पूर्ण
	वापस cpu_to_le32(scp->SCp.dma_handle);
पूर्ण

अटल पूर्णांक asc_build_req(काष्ठा asc_board *boardp, काष्ठा scsi_cmnd *scp,
			काष्ठा asc_scsi_q *asc_scsi_q)
अणु
	काष्ठा asc_dvc_var *asc_dvc = &boardp->dvc_var.asc_dvc_var;
	पूर्णांक use_sg;
	u32 srb_tag;

	स_रखो(asc_scsi_q, 0, माप(*asc_scsi_q));

	/*
	 * Set the srb_tag to the command tag + 1, as
	 * srb_tag '0' is used पूर्णांकernally by the chip.
	 */
	srb_tag = scp->request->tag + 1;
	asc_scsi_q->q2.srb_tag = srb_tag;

	/*
	 * Build the ASC_SCSI_Q request.
	 */
	asc_scsi_q->cdbptr = &scp->cmnd[0];
	asc_scsi_q->q2.cdb_len = scp->cmd_len;
	asc_scsi_q->q1.target_id = ASC_TID_TO_TARGET_ID(scp->device->id);
	asc_scsi_q->q1.target_lun = scp->device->lun;
	asc_scsi_q->q2.target_ix =
	    ASC_TIDLUN_TO_IX(scp->device->id, scp->device->lun);
	asc_scsi_q->q1.sense_addr = asc_get_sense_buffer_dma(scp);
	asc_scsi_q->q1.sense_len = SCSI_SENSE_BUFFERSIZE;
	अगर (!asc_scsi_q->q1.sense_addr)
		वापस ASC_BUSY;

	/*
	 * If there are any outstanding requests क्रम the current target,
	 * then every 255th request send an ORDERED request. This heuristic
	 * tries to retain the benefit of request sorting जबतक preventing
	 * request starvation. 255 is the max number of tags or pending commands
	 * a device may have outstanding.
	 *
	 * The request count is incremented below क्रम every successfully
	 * started request.
	 *
	 */
	अगर ((asc_dvc->cur_dvc_qng[scp->device->id] > 0) &&
	    (boardp->reqcnt[scp->device->id] % 255) == 0) अणु
		asc_scsi_q->q2.tag_code = ORDERED_QUEUE_TAG;
	पूर्ण अन्यथा अणु
		asc_scsi_q->q2.tag_code = SIMPLE_QUEUE_TAG;
	पूर्ण

	/* Build ASC_SCSI_Q */
	use_sg = scsi_dma_map(scp);
	अगर (use_sg < 0) अणु
		ASC_DBG(1, "failed to map sglist\n");
		वापस ASC_BUSY;
	पूर्ण अन्यथा अगर (use_sg > 0) अणु
		पूर्णांक sgcnt;
		काष्ठा scatterlist *slp;
		काष्ठा asc_sg_head *asc_sg_head;

		अगर (use_sg > scp->device->host->sg_tablesize) अणु
			scmd_prपूर्णांकk(KERN_ERR, scp, "use_sg %d > "
				"sg_tablesize %d\n", use_sg,
				scp->device->host->sg_tablesize);
			scsi_dma_unmap(scp);
			set_host_byte(scp, DID_ERROR);
			वापस ASC_ERROR;
		पूर्ण

		asc_sg_head = kzalloc(माप(asc_scsi_q->sg_head) +
			use_sg * माप(काष्ठा asc_sg_list), GFP_ATOMIC);
		अगर (!asc_sg_head) अणु
			scsi_dma_unmap(scp);
			set_host_byte(scp, DID_SOFT_ERROR);
			वापस ASC_ERROR;
		पूर्ण

		asc_scsi_q->q1.cntl |= QC_SG_HEAD;
		asc_scsi_q->sg_head = asc_sg_head;
		asc_scsi_q->q1.data_cnt = 0;
		asc_scsi_q->q1.data_addr = 0;
		/* This is a byte value, otherwise it would need to be swapped. */
		asc_sg_head->entry_cnt = asc_scsi_q->q1.sg_queue_cnt = use_sg;
		ASC_STATS_ADD(scp->device->host, xfer_elem,
			      asc_sg_head->entry_cnt);

		/*
		 * Convert scatter-gather list पूर्णांकo ASC_SG_HEAD list.
		 */
		scsi_क्रम_each_sg(scp, slp, use_sg, sgcnt) अणु
			asc_sg_head->sg_list[sgcnt].addr =
			    cpu_to_le32(sg_dma_address(slp));
			asc_sg_head->sg_list[sgcnt].bytes =
			    cpu_to_le32(sg_dma_len(slp));
			ASC_STATS_ADD(scp->device->host, xfer_sect,
				      DIV_ROUND_UP(sg_dma_len(slp), 512));
		पूर्ण
	पूर्ण

	ASC_STATS(scp->device->host, xfer_cnt);

	ASC_DBG_PRT_ASC_SCSI_Q(2, asc_scsi_q);
	ASC_DBG_PRT_CDB(1, scp->cmnd, scp->cmd_len);

	वापस ASC_NOERROR;
पूर्ण

/*
 * Build scatter-gather list क्रम Adv Library (Wide Board).
 *
 * Additional ADV_SG_BLOCK काष्ठाures will need to be allocated
 * अगर the total number of scatter-gather elements exceeds
 * NO_OF_SG_PER_BLOCK (15). The ADV_SG_BLOCK काष्ठाures are
 * assumed to be physically contiguous.
 *
 * Return:
 *      ADV_SUCCESS(1) - SG List successfully created
 *      ADV_ERROR(-1) - SG List creation failed
 */
अटल पूर्णांक
adv_get_sglist(काष्ठा asc_board *boardp, adv_req_t *reqp,
	       ADV_SCSI_REQ_Q *scsiqp, काष्ठा scsi_cmnd *scp, पूर्णांक use_sg)
अणु
	adv_sgblk_t *sgblkp, *prev_sgblkp;
	काष्ठा scatterlist *slp;
	पूर्णांक sg_elem_cnt;
	ADV_SG_BLOCK *sg_block, *prev_sg_block;
	dma_addr_t sgblk_paddr;
	पूर्णांक i;

	slp = scsi_sglist(scp);
	sg_elem_cnt = use_sg;
	prev_sgblkp = शून्य;
	prev_sg_block = शून्य;
	reqp->sgblkp = शून्य;

	क्रम (;;) अणु
		/*
		 * Allocate a 'adv_sgblk_t' काष्ठाure from the board मुक्त
		 * list. One 'adv_sgblk_t' काष्ठाure holds NO_OF_SG_PER_BLOCK
		 * (15) scatter-gather elements.
		 */
		sgblkp = dma_pool_alloc(boardp->adv_sgblk_pool, GFP_ATOMIC,
					&sgblk_paddr);
		अगर (!sgblkp) अणु
			ASC_DBG(1, "no free adv_sgblk_t\n");
			ASC_STATS(scp->device->host, adv_build_nosg);

			/*
			 * Allocation failed. Free 'adv_sgblk_t' काष्ठाures
			 * alपढ़ोy allocated क्रम the request.
			 */
			जबतक ((sgblkp = reqp->sgblkp) != शून्य) अणु
				/* Remove 'sgblkp' from the request list. */
				reqp->sgblkp = sgblkp->next_sgblkp;
				sgblkp->next_sgblkp = शून्य;
				dma_pool_मुक्त(boardp->adv_sgblk_pool, sgblkp,
					      sgblkp->sg_addr);
			पूर्ण
			वापस ASC_BUSY;
		पूर्ण
		/* Complete 'adv_sgblk_t' board allocation. */
		sgblkp->sg_addr = sgblk_paddr;
		sgblkp->next_sgblkp = शून्य;
		sg_block = &sgblkp->sg_block;

		/*
		 * Check अगर this is the first 'adv_sgblk_t' क्रम the
		 * request.
		 */
		अगर (reqp->sgblkp == शून्य) अणु
			/* Request's first scatter-gather block. */
			reqp->sgblkp = sgblkp;

			/*
			 * Set ADV_SCSI_REQ_T ADV_SG_BLOCK भव and physical
			 * address poपूर्णांकers.
			 */
			scsiqp->sg_list_ptr = sg_block;
			scsiqp->sg_real_addr = cpu_to_le32(sgblk_paddr);
		पूर्ण अन्यथा अणु
			/* Request's second or later scatter-gather block. */
			prev_sgblkp->next_sgblkp = sgblkp;

			/*
			 * Poपूर्णांक the previous ADV_SG_BLOCK काष्ठाure to
			 * the newly allocated ADV_SG_BLOCK काष्ठाure.
			 */
			prev_sg_block->sg_ptr = cpu_to_le32(sgblk_paddr);
		पूर्ण

		क्रम (i = 0; i < NO_OF_SG_PER_BLOCK; i++) अणु
			sg_block->sg_list[i].sg_addr =
					cpu_to_le32(sg_dma_address(slp));
			sg_block->sg_list[i].sg_count =
					cpu_to_le32(sg_dma_len(slp));
			ASC_STATS_ADD(scp->device->host, xfer_sect,
				      DIV_ROUND_UP(sg_dma_len(slp), 512));

			अगर (--sg_elem_cnt == 0) अणु
				/*
				 * Last ADV_SG_BLOCK and scatter-gather entry.
				 */
				sg_block->sg_cnt = i + 1;
				sg_block->sg_ptr = 0L; /* Last ADV_SG_BLOCK in list. */
				वापस ADV_SUCCESS;
			पूर्ण
			slp = sg_next(slp);
		पूर्ण
		sg_block->sg_cnt = NO_OF_SG_PER_BLOCK;
		prev_sg_block = sg_block;
		prev_sgblkp = sgblkp;
	पूर्ण
पूर्ण

/*
 * Build a request काष्ठाure क्रम the Adv Library (Wide Board).
 *
 * If an adv_req_t can not be allocated to issue the request,
 * then वापस ASC_BUSY. If an error occurs, then वापस ASC_ERROR.
 *
 * Multi-byte fields in the ADV_SCSI_REQ_Q that are used by the
 * microcode क्रम DMA addresses or math operations are byte swapped
 * to little-endian order.
 */
अटल पूर्णांक
adv_build_req(काष्ठा asc_board *boardp, काष्ठा scsi_cmnd *scp,
	      adv_req_t **adv_reqpp)
अणु
	u32 srb_tag = scp->request->tag;
	adv_req_t *reqp;
	ADV_SCSI_REQ_Q *scsiqp;
	पूर्णांक ret;
	पूर्णांक use_sg;
	dma_addr_t sense_addr;

	/*
	 * Allocate an adv_req_t काष्ठाure from the board to execute
	 * the command.
	 */
	reqp = &boardp->adv_reqp[srb_tag];
	अगर (reqp->cmndp && reqp->cmndp != scp ) अणु
		ASC_DBG(1, "no free adv_req_t\n");
		ASC_STATS(scp->device->host, adv_build_noreq);
		वापस ASC_BUSY;
	पूर्ण

	reqp->req_addr = boardp->adv_reqp_addr + (srb_tag * माप(adv_req_t));

	scsiqp = &reqp->scsi_req_q;

	/*
	 * Initialize the काष्ठाure.
	 */
	scsiqp->cntl = scsiqp->scsi_cntl = scsiqp->करोne_status = 0;

	/*
	 * Set the srb_tag to the command tag.
	 */
	scsiqp->srb_tag = srb_tag;

	/*
	 * Set 'host_scribble' to poपूर्णांक to the adv_req_t काष्ठाure.
	 */
	reqp->cmndp = scp;
	scp->host_scribble = (व्योम *)reqp;

	/*
	 * Build the ADV_SCSI_REQ_Q request.
	 */

	/* Set CDB length and copy it to the request काष्ठाure.  */
	scsiqp->cdb_len = scp->cmd_len;
	/* Copy first 12 CDB bytes to cdb[]. */
	स_नकल(scsiqp->cdb, scp->cmnd, scp->cmd_len < 12 ? scp->cmd_len : 12);
	/* Copy last 4 CDB bytes, अगर present, to cdb16[]. */
	अगर (scp->cmd_len > 12) अणु
		पूर्णांक cdb16_len = scp->cmd_len - 12;

		स_नकल(scsiqp->cdb16, &scp->cmnd[12], cdb16_len);
	पूर्ण

	scsiqp->target_id = scp->device->id;
	scsiqp->target_lun = scp->device->lun;

	sense_addr = dma_map_single(boardp->dev, scp->sense_buffer,
				    SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(boardp->dev, sense_addr)) अणु
		ASC_DBG(1, "failed to map sense buffer\n");
		ASC_STATS(scp->device->host, adv_build_noreq);
		वापस ASC_BUSY;
	पूर्ण
	scsiqp->sense_addr = cpu_to_le32(sense_addr);
	scsiqp->sense_len = SCSI_SENSE_BUFFERSIZE;

	/* Build ADV_SCSI_REQ_Q */

	use_sg = scsi_dma_map(scp);
	अगर (use_sg < 0) अणु
		ASC_DBG(1, "failed to map SG list\n");
		ASC_STATS(scp->device->host, adv_build_noreq);
		वापस ASC_BUSY;
	पूर्ण अन्यथा अगर (use_sg == 0) अणु
		/* Zero-length transfer */
		reqp->sgblkp = शून्य;
		scsiqp->data_cnt = 0;

		scsiqp->data_addr = 0;
		scsiqp->sg_list_ptr = शून्य;
		scsiqp->sg_real_addr = 0;
	पूर्ण अन्यथा अणु
		अगर (use_sg > ADV_MAX_SG_LIST) अणु
			scmd_prपूर्णांकk(KERN_ERR, scp, "use_sg %d > "
				   "ADV_MAX_SG_LIST %d\n", use_sg,
				   scp->device->host->sg_tablesize);
			scsi_dma_unmap(scp);
			set_host_byte(scp, DID_ERROR);
			reqp->cmndp = शून्य;
			scp->host_scribble = शून्य;

			वापस ASC_ERROR;
		पूर्ण

		scsiqp->data_cnt = cpu_to_le32(scsi_bufflen(scp));

		ret = adv_get_sglist(boardp, reqp, scsiqp, scp, use_sg);
		अगर (ret != ADV_SUCCESS) अणु
			scsi_dma_unmap(scp);
			set_host_byte(scp, DID_ERROR);
			reqp->cmndp = शून्य;
			scp->host_scribble = शून्य;

			वापस ret;
		पूर्ण

		ASC_STATS_ADD(scp->device->host, xfer_elem, use_sg);
	पूर्ण

	ASC_STATS(scp->device->host, xfer_cnt);

	ASC_DBG_PRT_ADV_SCSI_REQ_Q(2, scsiqp);
	ASC_DBG_PRT_CDB(1, scp->cmnd, scp->cmd_len);

	*adv_reqpp = reqp;

	वापस ASC_NOERROR;
पूर्ण

अटल पूर्णांक AscSgListToQueue(पूर्णांक sg_list)
अणु
	पूर्णांक n_sg_list_qs;

	n_sg_list_qs = ((sg_list - 1) / ASC_SG_LIST_PER_Q);
	अगर (((sg_list - 1) % ASC_SG_LIST_PER_Q) != 0)
		n_sg_list_qs++;
	वापस n_sg_list_qs + 1;
पूर्ण

अटल uपूर्णांक
AscGetNumOfFreeQueue(ASC_DVC_VAR *asc_dvc, uअक्षर target_ix, uअक्षर n_qs)
अणु
	uपूर्णांक cur_used_qs;
	uपूर्णांक cur_मुक्त_qs;
	ASC_SCSI_BIT_ID_TYPE target_id;
	uअक्षर tid_no;

	target_id = ASC_TIX_TO_TARGET_ID(target_ix);
	tid_no = ASC_TIX_TO_TID(target_ix);
	अगर ((asc_dvc->unit_not_पढ़ोy & target_id) ||
	    (asc_dvc->queue_full_or_busy & target_id)) अणु
		वापस 0;
	पूर्ण
	अगर (n_qs == 1) अणु
		cur_used_qs = (uपूर्णांक) asc_dvc->cur_total_qng +
		    (uपूर्णांक) asc_dvc->last_q_लघुage + (uपूर्णांक) ASC_MIN_FREE_Q;
	पूर्ण अन्यथा अणु
		cur_used_qs = (uपूर्णांक) asc_dvc->cur_total_qng +
		    (uपूर्णांक) ASC_MIN_FREE_Q;
	पूर्ण
	अगर ((uपूर्णांक) (cur_used_qs + n_qs) <= (uपूर्णांक) asc_dvc->max_total_qng) अणु
		cur_मुक्त_qs = (uपूर्णांक) asc_dvc->max_total_qng - cur_used_qs;
		अगर (asc_dvc->cur_dvc_qng[tid_no] >=
		    asc_dvc->max_dvc_qng[tid_no]) अणु
			वापस 0;
		पूर्ण
		वापस cur_मुक्त_qs;
	पूर्ण
	अगर (n_qs > 1) अणु
		अगर ((n_qs > asc_dvc->last_q_लघुage)
		    && (n_qs <= (asc_dvc->max_total_qng - ASC_MIN_FREE_Q))) अणु
			asc_dvc->last_q_लघुage = n_qs;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल uअक्षर AscAllocFreeQueue(PortAddr iop_base, uअक्षर मुक्त_q_head)
अणु
	uलघु q_addr;
	uअक्षर next_qp;
	uअक्षर q_status;

	q_addr = ASC_QNO_TO_QADDR(मुक्त_q_head);
	q_status = (uअक्षर)AscReadLramByte(iop_base,
					  (uलघु)(q_addr +
						   ASC_SCSIQ_B_STATUS));
	next_qp = AscReadLramByte(iop_base, (uलघु)(q_addr + ASC_SCSIQ_B_FWD));
	अगर (((q_status & QS_READY) == 0) && (next_qp != ASC_QLINK_END))
		वापस next_qp;
	वापस ASC_QLINK_END;
पूर्ण

अटल uअक्षर
AscAllocMultipleFreeQueue(PortAddr iop_base, uअक्षर मुक्त_q_head, uअक्षर n_मुक्त_q)
अणु
	uअक्षर i;

	क्रम (i = 0; i < n_मुक्त_q; i++) अणु
		मुक्त_q_head = AscAllocFreeQueue(iop_base, मुक्त_q_head);
		अगर (मुक्त_q_head == ASC_QLINK_END)
			अवरोध;
	पूर्ण
	वापस मुक्त_q_head;
पूर्ण

/*
 * व्योम
 * DvcPutScsiQ(PortAddr iop_base, uलघु s_addr, uअक्षर *outbuf, पूर्णांक words)
 *
 * Calling/Exit State:
 *    none
 *
 * Description:
 *     Output an ASC_SCSI_Q काष्ठाure to the chip
 */
अटल व्योम
DvcPutScsiQ(PortAddr iop_base, uलघु s_addr, uअक्षर *outbuf, पूर्णांक words)
अणु
	पूर्णांक i;

	ASC_DBG_PRT_HEX(2, "DvcPutScsiQ", outbuf, 2 * words);
	AscSetChipLramAddr(iop_base, s_addr);
	क्रम (i = 0; i < 2 * words; i += 2) अणु
		अगर (i == 4 || i == 20) अणु
			जारी;
		पूर्ण
		outpw(iop_base + IOP_RAM_DATA,
		      ((uलघु)outbuf[i + 1] << 8) | outbuf[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक AscPutReadyQueue(ASC_DVC_VAR *asc_dvc, ASC_SCSI_Q *scsiq, uअक्षर q_no)
अणु
	uलघु q_addr;
	uअक्षर tid_no;
	uअक्षर sdtr_data;
	uअक्षर syn_period_ix;
	uअक्षर syn_offset;
	PortAddr iop_base;

	iop_base = asc_dvc->iop_base;
	अगर (((asc_dvc->init_sdtr & scsiq->q1.target_id) != 0) &&
	    ((asc_dvc->sdtr_करोne & scsiq->q1.target_id) == 0)) अणु
		tid_no = ASC_TIX_TO_TID(scsiq->q2.target_ix);
		sdtr_data = AscGetMCodeInitSDTRAtID(iop_base, tid_no);
		syn_period_ix =
		    (sdtr_data >> 4) & (asc_dvc->max_sdtr_index - 1);
		syn_offset = sdtr_data & ASC_SYN_MAX_OFFSET;
		AscMsgOutSDTR(asc_dvc,
			      asc_dvc->sdtr_period_tbl[syn_period_ix],
			      syn_offset);
		scsiq->q1.cntl |= QC_MSG_OUT;
	पूर्ण
	q_addr = ASC_QNO_TO_QADDR(q_no);
	अगर ((scsiq->q1.target_id & asc_dvc->use_tagged_qng) == 0) अणु
		scsiq->q2.tag_code &= ~SIMPLE_QUEUE_TAG;
	पूर्ण
	scsiq->q1.status = QS_FREE;
	AscMemWordCopyPtrToLram(iop_base,
				q_addr + ASC_SCSIQ_CDB_BEG,
				(uअक्षर *)scsiq->cdbptr, scsiq->q2.cdb_len >> 1);

	DvcPutScsiQ(iop_base,
		    q_addr + ASC_SCSIQ_CPY_BEG,
		    (uअक्षर *)&scsiq->q1.cntl,
		    ((माप(ASC_SCSIQ_1) + माप(ASC_SCSIQ_2)) / 2) - 1);
	AscWriteLramWord(iop_base,
			 (uलघु)(q_addr + (uलघु)ASC_SCSIQ_B_STATUS),
			 (uलघु)(((uलघु)scsiq->q1.
				   q_no << 8) | (uलघु)QS_READY));
	वापस 1;
पूर्ण

अटल पूर्णांक
AscPutReadySgListQueue(ASC_DVC_VAR *asc_dvc, ASC_SCSI_Q *scsiq, uअक्षर q_no)
अणु
	पूर्णांक sta;
	पूर्णांक i;
	ASC_SG_HEAD *sg_head;
	ASC_SG_LIST_Q scsi_sg_q;
	__le32 saved_data_addr;
	__le32 saved_data_cnt;
	PortAddr iop_base;
	uलघु sg_list_dwords;
	uलघु sg_index;
	uलघु sg_entry_cnt;
	uलघु q_addr;
	uअक्षर next_qp;

	iop_base = asc_dvc->iop_base;
	sg_head = scsiq->sg_head;
	saved_data_addr = scsiq->q1.data_addr;
	saved_data_cnt = scsiq->q1.data_cnt;
	scsiq->q1.data_addr = cpu_to_le32(sg_head->sg_list[0].addr);
	scsiq->q1.data_cnt = cpu_to_le32(sg_head->sg_list[0].bytes);
	/*
	 * Set sg_entry_cnt to be the number of SG elements that
	 * will fit in the allocated SG queues. It is minus 1, because
	 * the first SG element is handled above.
	 */
	sg_entry_cnt = sg_head->entry_cnt - 1;

	अगर (sg_entry_cnt != 0) अणु
		scsiq->q1.cntl |= QC_SG_HEAD;
		q_addr = ASC_QNO_TO_QADDR(q_no);
		sg_index = 1;
		scsiq->q1.sg_queue_cnt = sg_head->queue_cnt;
		scsi_sg_q.sg_head_qp = q_no;
		scsi_sg_q.cntl = QCSG_SG_XFER_LIST;
		क्रम (i = 0; i < sg_head->queue_cnt; i++) अणु
			scsi_sg_q.seq_no = i + 1;
			अगर (sg_entry_cnt > ASC_SG_LIST_PER_Q) अणु
				sg_list_dwords = (uअक्षर)(ASC_SG_LIST_PER_Q * 2);
				sg_entry_cnt -= ASC_SG_LIST_PER_Q;
				अगर (i == 0) अणु
					scsi_sg_q.sg_list_cnt =
					    ASC_SG_LIST_PER_Q;
					scsi_sg_q.sg_cur_list_cnt =
					    ASC_SG_LIST_PER_Q;
				पूर्ण अन्यथा अणु
					scsi_sg_q.sg_list_cnt =
					    ASC_SG_LIST_PER_Q - 1;
					scsi_sg_q.sg_cur_list_cnt =
					    ASC_SG_LIST_PER_Q - 1;
				पूर्ण
			पूर्ण अन्यथा अणु
				scsi_sg_q.cntl |= QCSG_SG_XFER_END;
				sg_list_dwords = sg_entry_cnt << 1;
				अगर (i == 0) अणु
					scsi_sg_q.sg_list_cnt = sg_entry_cnt;
					scsi_sg_q.sg_cur_list_cnt =
					    sg_entry_cnt;
				पूर्ण अन्यथा अणु
					scsi_sg_q.sg_list_cnt =
					    sg_entry_cnt - 1;
					scsi_sg_q.sg_cur_list_cnt =
					    sg_entry_cnt - 1;
				पूर्ण
				sg_entry_cnt = 0;
			पूर्ण
			next_qp = AscReadLramByte(iop_base,
						  (uलघु)(q_addr +
							   ASC_SCSIQ_B_FWD));
			scsi_sg_q.q_no = next_qp;
			q_addr = ASC_QNO_TO_QADDR(next_qp);
			AscMemWordCopyPtrToLram(iop_base,
						q_addr + ASC_SCSIQ_SGHD_CPY_BEG,
						(uअक्षर *)&scsi_sg_q,
						माप(ASC_SG_LIST_Q) >> 1);
			AscMemDWordCopyPtrToLram(iop_base,
						 q_addr + ASC_SGQ_LIST_BEG,
						 (uअक्षर *)&sg_head->
						 sg_list[sg_index],
						 sg_list_dwords);
			sg_index += ASC_SG_LIST_PER_Q;
			scsiq->next_sg_index = sg_index;
		पूर्ण
	पूर्ण अन्यथा अणु
		scsiq->q1.cntl &= ~QC_SG_HEAD;
	पूर्ण
	sta = AscPutReadyQueue(asc_dvc, scsiq, q_no);
	scsiq->q1.data_addr = saved_data_addr;
	scsiq->q1.data_cnt = saved_data_cnt;
	वापस (sta);
पूर्ण

अटल पूर्णांक
AscSendScsiQueue(ASC_DVC_VAR *asc_dvc, ASC_SCSI_Q *scsiq, uअक्षर n_q_required)
अणु
	PortAddr iop_base;
	uअक्षर मुक्त_q_head;
	uअक्षर next_qp;
	uअक्षर tid_no;
	uअक्षर target_ix;
	पूर्णांक sta;

	iop_base = asc_dvc->iop_base;
	target_ix = scsiq->q2.target_ix;
	tid_no = ASC_TIX_TO_TID(target_ix);
	sta = 0;
	मुक्त_q_head = (uअक्षर)AscGetVarFreeQHead(iop_base);
	अगर (n_q_required > 1) अणु
		next_qp = AscAllocMultipleFreeQueue(iop_base, मुक्त_q_head,
						    (uअक्षर)n_q_required);
		अगर (next_qp != ASC_QLINK_END) अणु
			asc_dvc->last_q_लघुage = 0;
			scsiq->sg_head->queue_cnt = n_q_required - 1;
			scsiq->q1.q_no = मुक्त_q_head;
			sta = AscPutReadySgListQueue(asc_dvc, scsiq,
						     मुक्त_q_head);
		पूर्ण
	पूर्ण अन्यथा अगर (n_q_required == 1) अणु
		next_qp = AscAllocFreeQueue(iop_base, मुक्त_q_head);
		अगर (next_qp != ASC_QLINK_END) अणु
			scsiq->q1.q_no = मुक्त_q_head;
			sta = AscPutReadyQueue(asc_dvc, scsiq, मुक्त_q_head);
		पूर्ण
	पूर्ण
	अगर (sta == 1) अणु
		AscPutVarFreeQHead(iop_base, next_qp);
		asc_dvc->cur_total_qng += n_q_required;
		asc_dvc->cur_dvc_qng[tid_no]++;
	पूर्ण
	वापस sta;
पूर्ण

#घोषणा ASC_SYN_OFFSET_ONE_DISABLE_LIST  16
अटल uअक्षर _syn_offset_one_disable_cmd[ASC_SYN_OFFSET_ONE_DISABLE_LIST] = अणु
	INQUIRY,
	REQUEST_SENSE,
	READ_CAPACITY,
	READ_TOC,
	MODE_SELECT,
	MODE_SENSE,
	MODE_SELECT_10,
	MODE_SENSE_10,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF
पूर्ण;

अटल पूर्णांक AscExeScsiQueue(ASC_DVC_VAR *asc_dvc, ASC_SCSI_Q *scsiq)
अणु
	PortAddr iop_base;
	पूर्णांक sta;
	पूर्णांक n_q_required;
	bool disable_syn_offset_one_fix;
	पूर्णांक i;
	u32 addr;
	uलघु sg_entry_cnt = 0;
	uलघु sg_entry_cnt_minus_one = 0;
	uअक्षर target_ix;
	uअक्षर tid_no;
	uअक्षर sdtr_data;
	uअक्षर extra_bytes;
	uअक्षर scsi_cmd;
	uअक्षर disable_cmd;
	ASC_SG_HEAD *sg_head;
	अचिन्हित दीर्घ data_cnt;

	iop_base = asc_dvc->iop_base;
	sg_head = scsiq->sg_head;
	अगर (asc_dvc->err_code != 0)
		वापस ASC_ERROR;
	scsiq->q1.q_no = 0;
	अगर ((scsiq->q2.tag_code & ASC_TAG_FLAG_EXTRA_BYTES) == 0) अणु
		scsiq->q1.extra_bytes = 0;
	पूर्ण
	sta = 0;
	target_ix = scsiq->q2.target_ix;
	tid_no = ASC_TIX_TO_TID(target_ix);
	n_q_required = 1;
	अगर (scsiq->cdbptr[0] == REQUEST_SENSE) अणु
		अगर ((asc_dvc->init_sdtr & scsiq->q1.target_id) != 0) अणु
			asc_dvc->sdtr_करोne &= ~scsiq->q1.target_id;
			sdtr_data = AscGetMCodeInitSDTRAtID(iop_base, tid_no);
			AscMsgOutSDTR(asc_dvc,
				      asc_dvc->
				      sdtr_period_tbl[(sdtr_data >> 4) &
						      (uअक्षर)(asc_dvc->
							      max_sdtr_index -
							      1)],
				      (uअक्षर)(sdtr_data & (uअक्षर)
					      ASC_SYN_MAX_OFFSET));
			scsiq->q1.cntl |= (QC_MSG_OUT | QC_URGENT);
		पूर्ण
	पूर्ण
	अगर (asc_dvc->in_critical_cnt != 0) अणु
		AscSetLibErrorCode(asc_dvc, ASCQ_ERR_CRITICAL_RE_ENTRY);
		वापस ASC_ERROR;
	पूर्ण
	asc_dvc->in_critical_cnt++;
	अगर ((scsiq->q1.cntl & QC_SG_HEAD) != 0) अणु
		अगर ((sg_entry_cnt = sg_head->entry_cnt) == 0) अणु
			asc_dvc->in_critical_cnt--;
			वापस ASC_ERROR;
		पूर्ण
		अगर (sg_entry_cnt > ASC_MAX_SG_LIST) अणु
			asc_dvc->in_critical_cnt--;
			वापस ASC_ERROR;
		पूर्ण
		अगर (sg_entry_cnt == 1) अणु
			scsiq->q1.data_addr = cpu_to_le32(sg_head->sg_list[0].addr);
			scsiq->q1.data_cnt = cpu_to_le32(sg_head->sg_list[0].bytes);
			scsiq->q1.cntl &= ~(QC_SG_HEAD | QC_SG_SWAP_QUEUE);
		पूर्ण
		sg_entry_cnt_minus_one = sg_entry_cnt - 1;
	पूर्ण
	scsi_cmd = scsiq->cdbptr[0];
	disable_syn_offset_one_fix = false;
	अगर ((asc_dvc->pci_fix_asyn_xfer & scsiq->q1.target_id) &&
	    !(asc_dvc->pci_fix_asyn_xfer_always & scsiq->q1.target_id)) अणु
		अगर (scsiq->q1.cntl & QC_SG_HEAD) अणु
			data_cnt = 0;
			क्रम (i = 0; i < sg_entry_cnt; i++) अणु
				data_cnt += le32_to_cpu(sg_head->sg_list[i].
							bytes);
			पूर्ण
		पूर्ण अन्यथा अणु
			data_cnt = le32_to_cpu(scsiq->q1.data_cnt);
		पूर्ण
		अगर (data_cnt != 0UL) अणु
			अगर (data_cnt < 512UL) अणु
				disable_syn_offset_one_fix = true;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < ASC_SYN_OFFSET_ONE_DISABLE_LIST;
				     i++) अणु
					disable_cmd =
					    _syn_offset_one_disable_cmd[i];
					अगर (disable_cmd == 0xFF) अणु
						अवरोध;
					पूर्ण
					अगर (scsi_cmd == disable_cmd) अणु
						disable_syn_offset_one_fix =
						    true;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (disable_syn_offset_one_fix) अणु
		scsiq->q2.tag_code &= ~SIMPLE_QUEUE_TAG;
		scsiq->q2.tag_code |= (ASC_TAG_FLAG_DISABLE_ASYN_USE_SYN_FIX |
				       ASC_TAG_FLAG_DISABLE_DISCONNECT);
	पूर्ण अन्यथा अणु
		scsiq->q2.tag_code &= 0x27;
	पूर्ण
	अगर ((scsiq->q1.cntl & QC_SG_HEAD) != 0) अणु
		अगर (asc_dvc->bug_fix_cntl) अणु
			अगर (asc_dvc->bug_fix_cntl & ASC_BUG_FIX_IF_NOT_DWB) अणु
				अगर ((scsi_cmd == READ_6) ||
				    (scsi_cmd == READ_10)) अणु
					addr = le32_to_cpu(sg_head->
								   sg_list
								   [sg_entry_cnt_minus_one].
								   addr) +
						le32_to_cpu(sg_head->
								  sg_list
								  [sg_entry_cnt_minus_one].
								  bytes);
					extra_bytes =
					    (uअक्षर)((uलघु)addr & 0x0003);
					अगर ((extra_bytes != 0)
					    &&
					    ((scsiq->q2.
					      tag_code &
					      ASC_TAG_FLAG_EXTRA_BYTES)
					     == 0)) अणु
						scsiq->q2.tag_code |=
						    ASC_TAG_FLAG_EXTRA_BYTES;
						scsiq->q1.extra_bytes =
						    extra_bytes;
						data_cnt =
						    le32_to_cpu(sg_head->
								sg_list
								[sg_entry_cnt_minus_one].
								bytes);
						data_cnt -= extra_bytes;
						sg_head->
						    sg_list
						    [sg_entry_cnt_minus_one].
						    bytes =
						    cpu_to_le32(data_cnt);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		sg_head->entry_to_copy = sg_head->entry_cnt;
		n_q_required = AscSgListToQueue(sg_entry_cnt);
		अगर ((AscGetNumOfFreeQueue(asc_dvc, target_ix, n_q_required) >=
		     (uपूर्णांक) n_q_required)
		    || ((scsiq->q1.cntl & QC_URGENT) != 0)) अणु
			अगर ((sta =
			     AscSendScsiQueue(asc_dvc, scsiq,
					      n_q_required)) == 1) अणु
				asc_dvc->in_critical_cnt--;
				वापस (sta);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (asc_dvc->bug_fix_cntl) अणु
			अगर (asc_dvc->bug_fix_cntl & ASC_BUG_FIX_IF_NOT_DWB) अणु
				अगर ((scsi_cmd == READ_6) ||
				    (scsi_cmd == READ_10)) अणु
					addr =
					    le32_to_cpu(scsiq->q1.data_addr) +
					    le32_to_cpu(scsiq->q1.data_cnt);
					extra_bytes =
					    (uअक्षर)((uलघु)addr & 0x0003);
					अगर ((extra_bytes != 0)
					    &&
					    ((scsiq->q2.
					      tag_code &
					      ASC_TAG_FLAG_EXTRA_BYTES)
					     == 0)) अणु
						data_cnt =
						    le32_to_cpu(scsiq->q1.
								data_cnt);
						अगर (((uलघु)data_cnt & 0x01FF)
						    == 0) अणु
							scsiq->q2.tag_code |=
							    ASC_TAG_FLAG_EXTRA_BYTES;
							data_cnt -= extra_bytes;
							scsiq->q1.data_cnt =
							    cpu_to_le32
							    (data_cnt);
							scsiq->q1.extra_bytes =
							    extra_bytes;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		n_q_required = 1;
		अगर ((AscGetNumOfFreeQueue(asc_dvc, target_ix, 1) >= 1) ||
		    ((scsiq->q1.cntl & QC_URGENT) != 0)) अणु
			अगर ((sta = AscSendScsiQueue(asc_dvc, scsiq,
						    n_q_required)) == 1) अणु
				asc_dvc->in_critical_cnt--;
				वापस (sta);
			पूर्ण
		पूर्ण
	पूर्ण
	asc_dvc->in_critical_cnt--;
	वापस (sta);
पूर्ण

/*
 * AdvExeScsiQueue() - Send a request to the RISC microcode program.
 *
 *   Allocate a carrier काष्ठाure, poपूर्णांक the carrier to the ADV_SCSI_REQ_Q,
 *   add the carrier to the ICQ (Initiator Command Queue), and tickle the
 *   RISC to notअगरy it a new command is पढ़ोy to be executed.
 *
 * If 'done_status' is not set to QD_DO_RETRY, then 'error_retry' will be
 * set to SCSI_MAX_RETRY.
 *
 * Multi-byte fields in the ADV_SCSI_REQ_Q that are used by the microcode
 * क्रम DMA addresses or math operations are byte swapped to little-endian
 * order.
 *
 * Return:
 *      ADV_SUCCESS(1) - The request was successfully queued.
 *      ADV_BUSY(0) -    Resource unavailable; Retry again after pending
 *                       request completes.
 *      ADV_ERROR(-1) -  Invalid ADV_SCSI_REQ_Q request काष्ठाure
 *                       host IC error.
 */
अटल पूर्णांक AdvExeScsiQueue(ADV_DVC_VAR *asc_dvc, adv_req_t *reqp)
अणु
	AdvPortAddr iop_base;
	ADV_CARR_T *new_carrp;
	ADV_SCSI_REQ_Q *scsiq = &reqp->scsi_req_q;

	/*
	 * The ADV_SCSI_REQ_Q 'target_id' field should never exceed ADV_MAX_TID.
	 */
	अगर (scsiq->target_id > ADV_MAX_TID) अणु
		scsiq->host_status = QHSTA_M_INVALID_DEVICE;
		scsiq->करोne_status = QD_WITH_ERROR;
		वापस ADV_ERROR;
	पूर्ण

	iop_base = asc_dvc->iop_base;

	/*
	 * Allocate a carrier ensuring at least one carrier always
	 * reमुख्यs on the मुक्तlist and initialize fields.
	 */
	new_carrp = adv_get_next_carrier(asc_dvc);
	अगर (!new_carrp) अणु
		ASC_DBG(1, "No free carriers\n");
		वापस ADV_BUSY;
	पूर्ण

	asc_dvc->carr_pending_cnt++;

	/* Save भव and physical address of ADV_SCSI_REQ_Q and carrier. */
	scsiq->scsiq_ptr = cpu_to_le32(scsiq->srb_tag);
	scsiq->scsiq_rptr = cpu_to_le32(reqp->req_addr);

	scsiq->carr_va = asc_dvc->icq_sp->carr_va;
	scsiq->carr_pa = asc_dvc->icq_sp->carr_pa;

	/*
	 * Use the current stopper to send the ADV_SCSI_REQ_Q command to
	 * the microcode. The newly allocated stopper will become the new
	 * stopper.
	 */
	asc_dvc->icq_sp->areq_vpa = scsiq->scsiq_rptr;

	/*
	 * Set the 'next_vpa' poपूर्णांकer क्रम the old stopper to be the
	 * physical address of the new stopper. The RISC can only
	 * follow physical addresses.
	 */
	asc_dvc->icq_sp->next_vpa = new_carrp->carr_pa;

	/*
	 * Set the host adapter stopper poपूर्णांकer to poपूर्णांक to the new carrier.
	 */
	asc_dvc->icq_sp = new_carrp;

	अगर (asc_dvc->chip_type == ADV_CHIP_ASC3550 ||
	    asc_dvc->chip_type == ADV_CHIP_ASC38C0800) अणु
		/*
		 * Tickle the RISC to tell it to पढ़ो its Command Queue Head poपूर्णांकer.
		 */
		AdvWriteByteRegister(iop_base, IOPB_TICKLE, ADV_TICKLE_A);
		अगर (asc_dvc->chip_type == ADV_CHIP_ASC3550) अणु
			/*
			 * Clear the tickle value. In the ASC-3550 the RISC flag
			 * command 'clr_tickle_a' करोes not work unless the host
			 * value is cleared.
			 */
			AdvWriteByteRegister(iop_base, IOPB_TICKLE,
					     ADV_TICKLE_NOP);
		पूर्ण
	पूर्ण अन्यथा अगर (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) अणु
		/*
		 * Notअगरy the RISC a carrier is पढ़ोy by writing the physical
		 * address of the new carrier stopper to the COMMA रेजिस्टर.
		 */
		AdvWriteDWordRegister(iop_base, IOPDW_COMMA,
				      le32_to_cpu(new_carrp->carr_pa));
	पूर्ण

	वापस ADV_SUCCESS;
पूर्ण

/*
 * Execute a single 'struct scsi_cmnd'.
 */
अटल पूर्णांक asc_execute_scsi_cmnd(काष्ठा scsi_cmnd *scp)
अणु
	पूर्णांक ret, err_code;
	काष्ठा asc_board *boardp = shost_priv(scp->device->host);

	ASC_DBG(1, "scp 0x%p\n", scp);

	अगर (ASC_NARROW_BOARD(boardp)) अणु
		ASC_DVC_VAR *asc_dvc = &boardp->dvc_var.asc_dvc_var;
		काष्ठा asc_scsi_q asc_scsi_q;

		ret = asc_build_req(boardp, scp, &asc_scsi_q);
		अगर (ret != ASC_NOERROR) अणु
			ASC_STATS(scp->device->host, build_error);
			वापस ret;
		पूर्ण

		ret = AscExeScsiQueue(asc_dvc, &asc_scsi_q);
		kमुक्त(asc_scsi_q.sg_head);
		err_code = asc_dvc->err_code;
	पूर्ण अन्यथा अणु
		ADV_DVC_VAR *adv_dvc = &boardp->dvc_var.adv_dvc_var;
		adv_req_t *adv_reqp;

		चयन (adv_build_req(boardp, scp, &adv_reqp)) अणु
		हाल ASC_NOERROR:
			ASC_DBG(3, "adv_build_req ASC_NOERROR\n");
			अवरोध;
		हाल ASC_BUSY:
			ASC_DBG(1, "adv_build_req ASC_BUSY\n");
			/*
			 * The asc_stats fields 'adv_build_noreq' and
			 * 'adv_build_nosg' count wide board busy conditions.
			 * They are updated in adv_build_req and
			 * adv_get_sglist, respectively.
			 */
			वापस ASC_BUSY;
		हाल ASC_ERROR:
		शेष:
			ASC_DBG(1, "adv_build_req ASC_ERROR\n");
			ASC_STATS(scp->device->host, build_error);
			वापस ASC_ERROR;
		पूर्ण

		ret = AdvExeScsiQueue(adv_dvc, adv_reqp);
		err_code = adv_dvc->err_code;
	पूर्ण

	चयन (ret) अणु
	हाल ASC_NOERROR:
		ASC_STATS(scp->device->host, exe_noerror);
		/*
		 * Increment monotonically increasing per device
		 * successful request counter. Wrapping करोesn't matter.
		 */
		boardp->reqcnt[scp->device->id]++;
		ASC_DBG(1, "ExeScsiQueue() ASC_NOERROR\n");
		अवरोध;
	हाल ASC_BUSY:
		ASC_DBG(1, "ExeScsiQueue() ASC_BUSY\n");
		ASC_STATS(scp->device->host, exe_busy);
		अवरोध;
	हाल ASC_ERROR:
		scmd_prपूर्णांकk(KERN_ERR, scp, "ExeScsiQueue() ASC_ERROR, "
			"err_code 0x%x\n", err_code);
		ASC_STATS(scp->device->host, exe_error);
		set_host_byte(scp, DID_ERROR);
		अवरोध;
	शेष:
		scmd_prपूर्णांकk(KERN_ERR, scp, "ExeScsiQueue() unknown, "
			"err_code 0x%x\n", err_code);
		ASC_STATS(scp->device->host, exe_unknown);
		set_host_byte(scp, DID_ERROR);
		अवरोध;
	पूर्ण

	ASC_DBG(1, "end\n");
	वापस ret;
पूर्ण

/*
 * advansys_queuecommand() - पूर्णांकerrupt-driven I/O entrypoपूर्णांक.
 *
 * This function always वापसs 0. Command वापस status is saved
 * in the 'scp' result field.
 */
अटल पूर्णांक
advansys_queuecommand_lck(काष्ठा scsi_cmnd *scp, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा Scsi_Host *shost = scp->device->host;
	पूर्णांक asc_res, result = 0;

	ASC_STATS(shost, queuecommand);
	scp->scsi_करोne = करोne;

	asc_res = asc_execute_scsi_cmnd(scp);

	चयन (asc_res) अणु
	हाल ASC_NOERROR:
		अवरोध;
	हाल ASC_BUSY:
		result = SCSI_MLQUEUE_HOST_BUSY;
		अवरोध;
	हाल ASC_ERROR:
	शेष:
		asc_scsi_करोne(scp);
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल DEF_SCSI_QCMD(advansys_queuecommand)

अटल uलघु AscGetEisaChipCfg(PortAddr iop_base)
अणु
	PortAddr eisa_cfg_iop = (PortAddr) ASC_GET_EISA_SLOT(iop_base) |
	    (PortAddr) (ASC_EISA_CFG_IOP_MASK);
	वापस inpw(eisa_cfg_iop);
पूर्ण

/*
 * Return the BIOS address of the adapter at the specअगरied
 * I/O port and with the specअगरied bus type.
 */
अटल अचिन्हित लघु AscGetChipBiosAddress(PortAddr iop_base,
					    अचिन्हित लघु bus_type)
अणु
	अचिन्हित लघु cfg_lsw;
	अचिन्हित लघु bios_addr;

	/*
	 * The PCI BIOS is re-located by the motherboard BIOS. Because
	 * of this the driver can not determine where a PCI BIOS is
	 * loaded and executes.
	 */
	अगर (bus_type & ASC_IS_PCI)
		वापस 0;

	अगर ((bus_type & ASC_IS_EISA) != 0) अणु
		cfg_lsw = AscGetEisaChipCfg(iop_base);
		cfg_lsw &= 0x000F;
		bios_addr = ASC_BIOS_MIN_ADDR + cfg_lsw * ASC_BIOS_BANK_SIZE;
		वापस bios_addr;
	पूर्ण

	cfg_lsw = AscGetChipCfgLsw(iop_base);
	bios_addr = ASC_BIOS_MIN_ADDR + (cfg_lsw >> 12) * ASC_BIOS_BANK_SIZE;
	वापस bios_addr;
पूर्ण

अटल uअक्षर AscSetChipScsiID(PortAddr iop_base, uअक्षर new_host_id)
अणु
	uलघु cfg_lsw;

	अगर (AscGetChipScsiID(iop_base) == new_host_id) अणु
		वापस (new_host_id);
	पूर्ण
	cfg_lsw = AscGetChipCfgLsw(iop_base);
	cfg_lsw &= 0xF8FF;
	cfg_lsw |= (uलघु)((new_host_id & ASC_MAX_TID) << 8);
	AscSetChipCfgLsw(iop_base, cfg_lsw);
	वापस (AscGetChipScsiID(iop_base));
पूर्ण

अटल अचिन्हित अक्षर AscGetChipScsiCtrl(PortAddr iop_base)
अणु
	अचिन्हित अक्षर sc;

	AscSetBank(iop_base, 1);
	sc = inp(iop_base + IOP_REG_SC);
	AscSetBank(iop_base, 0);
	वापस sc;
पूर्ण

अटल अचिन्हित अक्षर AscGetChipVersion(PortAddr iop_base,
				       अचिन्हित लघु bus_type)
अणु
	अगर (bus_type & ASC_IS_EISA) अणु
		PortAddr eisa_iop;
		अचिन्हित अक्षर revision;
		eisa_iop = (PortAddr) ASC_GET_EISA_SLOT(iop_base) |
		    (PortAddr) ASC_EISA_REV_IOP_MASK;
		revision = inp(eisa_iop);
		वापस ASC_CHIP_MIN_VER_EISA - 1 + revision;
	पूर्ण
	वापस AscGetChipVerNo(iop_base);
पूर्ण

अटल पूर्णांक AscStopQueueExe(PortAddr iop_base)
अणु
	पूर्णांक count = 0;

	अगर (AscReadLramByte(iop_base, ASCV_STOP_CODE_B) == 0) अणु
		AscWriteLramByte(iop_base, ASCV_STOP_CODE_B,
				 ASC_STOP_REQ_RISC_STOP);
		करो अणु
			अगर (AscReadLramByte(iop_base, ASCV_STOP_CODE_B) &
			    ASC_STOP_ACK_RISC_STOP) अणु
				वापस (1);
			पूर्ण
			mdelay(100);
		पूर्ण जबतक (count++ < 20);
	पूर्ण
	वापस (0);
पूर्ण

अटल अचिन्हित पूर्णांक AscGetMaxDmaCount(uलघु bus_type)
अणु
	अगर (bus_type & (ASC_IS_EISA | ASC_IS_VL))
		वापस ASC_MAX_VL_DMA_COUNT;
	वापस ASC_MAX_PCI_DMA_COUNT;
पूर्ण

अटल व्योम AscInitAscDvcVar(ASC_DVC_VAR *asc_dvc)
अणु
	पूर्णांक i;
	PortAddr iop_base;
	uअक्षर chip_version;

	iop_base = asc_dvc->iop_base;
	asc_dvc->err_code = 0;
	अगर ((asc_dvc->bus_type &
	     (ASC_IS_PCI | ASC_IS_EISA | ASC_IS_VL)) == 0) अणु
		asc_dvc->err_code |= ASC_IERR_NO_BUS_TYPE;
	पूर्ण
	AscSetChipControl(iop_base, CC_HALT);
	AscSetChipStatus(iop_base, 0);
	asc_dvc->bug_fix_cntl = 0;
	asc_dvc->pci_fix_asyn_xfer = 0;
	asc_dvc->pci_fix_asyn_xfer_always = 0;
	/* asc_dvc->init_state initialized in AscInitGetConfig(). */
	asc_dvc->sdtr_करोne = 0;
	asc_dvc->cur_total_qng = 0;
	asc_dvc->is_in_पूर्णांक = false;
	asc_dvc->in_critical_cnt = 0;
	asc_dvc->last_q_लघुage = 0;
	asc_dvc->use_tagged_qng = 0;
	asc_dvc->no_scam = 0;
	asc_dvc->unit_not_पढ़ोy = 0;
	asc_dvc->queue_full_or_busy = 0;
	asc_dvc->reकरो_scam = 0;
	asc_dvc->res2 = 0;
	asc_dvc->min_sdtr_index = 0;
	asc_dvc->cfg->can_tagged_qng = 0;
	asc_dvc->cfg->cmd_qng_enabled = 0;
	asc_dvc->dvc_cntl = ASC_DEF_DVC_CNTL;
	asc_dvc->init_sdtr = 0;
	asc_dvc->max_total_qng = ASC_DEF_MAX_TOTAL_QNG;
	asc_dvc->scsi_reset_रुको = 3;
	asc_dvc->start_motor = ASC_SCSI_WIDTH_BIT_SET;
	asc_dvc->max_dma_count = AscGetMaxDmaCount(asc_dvc->bus_type);
	asc_dvc->cfg->sdtr_enable = ASC_SCSI_WIDTH_BIT_SET;
	asc_dvc->cfg->disc_enable = ASC_SCSI_WIDTH_BIT_SET;
	asc_dvc->cfg->chip_scsi_id = ASC_DEF_CHIP_SCSI_ID;
	chip_version = AscGetChipVersion(iop_base, asc_dvc->bus_type);
	asc_dvc->cfg->chip_version = chip_version;
	asc_dvc->sdtr_period_tbl = asc_syn_xfer_period;
	asc_dvc->max_sdtr_index = 7;
	अगर ((asc_dvc->bus_type & ASC_IS_PCI) &&
	    (chip_version >= ASC_CHIP_VER_PCI_ULTRA_3150)) अणु
		asc_dvc->bus_type = ASC_IS_PCI_ULTRA;
		asc_dvc->sdtr_period_tbl = asc_syn_ultra_xfer_period;
		asc_dvc->max_sdtr_index = 15;
		अगर (chip_version == ASC_CHIP_VER_PCI_ULTRA_3150) अणु
			AscSetExtraControl(iop_base,
					   (SEC_ACTIVE_NEGATE | SEC_SLEW_RATE));
		पूर्ण अन्यथा अगर (chip_version >= ASC_CHIP_VER_PCI_ULTRA_3050) अणु
			AscSetExtraControl(iop_base,
					   (SEC_ACTIVE_NEGATE |
					    SEC_ENABLE_FILTER));
		पूर्ण
	पूर्ण
	अगर (asc_dvc->bus_type == ASC_IS_PCI) अणु
		AscSetExtraControl(iop_base,
				   (SEC_ACTIVE_NEGATE | SEC_SLEW_RATE));
	पूर्ण

	क्रम (i = 0; i <= ASC_MAX_TID; i++) अणु
		asc_dvc->cur_dvc_qng[i] = 0;
		asc_dvc->max_dvc_qng[i] = ASC_MAX_SCSI1_QNG;
		asc_dvc->scsiq_busy_head[i] = (ASC_SCSI_Q *)0L;
		asc_dvc->scsiq_busy_tail[i] = (ASC_SCSI_Q *)0L;
		asc_dvc->cfg->max_tag_qng[i] = ASC_MAX_INRAM_TAG_QNG;
	पूर्ण
पूर्ण

अटल पूर्णांक AscWriteEEPCmdReg(PortAddr iop_base, uअक्षर cmd_reg)
अणु
	पूर्णांक retry;

	क्रम (retry = 0; retry < ASC_EEP_MAX_RETRY; retry++) अणु
		अचिन्हित अक्षर पढ़ो_back;
		AscSetChipEEPCmd(iop_base, cmd_reg);
		mdelay(1);
		पढ़ो_back = AscGetChipEEPCmd(iop_base);
		अगर (पढ़ो_back == cmd_reg)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम AscWaitEEPRead(व्योम)
अणु
	mdelay(1);
पूर्ण

अटल uलघु AscReadEEPWord(PortAddr iop_base, uअक्षर addr)
अणु
	uलघु पढ़ो_wval;
	uअक्षर cmd_reg;

	AscWriteEEPCmdReg(iop_base, ASC_EEP_CMD_WRITE_DISABLE);
	AscWaitEEPRead();
	cmd_reg = addr | ASC_EEP_CMD_READ;
	AscWriteEEPCmdReg(iop_base, cmd_reg);
	AscWaitEEPRead();
	पढ़ो_wval = AscGetChipEEPData(iop_base);
	AscWaitEEPRead();
	वापस पढ़ो_wval;
पूर्ण

अटल uलघु AscGetEEPConfig(PortAddr iop_base, ASCEEP_CONFIG *cfg_buf,
			      uलघु bus_type)
अणु
	uलघु wval;
	uलघु sum;
	uलघु *wbuf;
	पूर्णांक cfg_beg;
	पूर्णांक cfg_end;
	पूर्णांक uअक्षर_end_in_config = ASC_EEP_MAX_DVC_ADDR - 2;
	पूर्णांक s_addr;

	wbuf = (uलघु *)cfg_buf;
	sum = 0;
	/* Read two config words; Byte-swapping करोne by AscReadEEPWord(). */
	क्रम (s_addr = 0; s_addr < 2; s_addr++, wbuf++) अणु
		*wbuf = AscReadEEPWord(iop_base, (uअक्षर)s_addr);
		sum += *wbuf;
	पूर्ण
	अगर (bus_type & ASC_IS_VL) अणु
		cfg_beg = ASC_EEP_DVC_CFG_BEG_VL;
		cfg_end = ASC_EEP_MAX_DVC_ADDR_VL;
	पूर्ण अन्यथा अणु
		cfg_beg = ASC_EEP_DVC_CFG_BEG;
		cfg_end = ASC_EEP_MAX_DVC_ADDR;
	पूर्ण
	क्रम (s_addr = cfg_beg; s_addr <= (cfg_end - 1); s_addr++, wbuf++) अणु
		wval = AscReadEEPWord(iop_base, (uअक्षर)s_addr);
		अगर (s_addr <= uअक्षर_end_in_config) अणु
			/*
			 * Swap all अक्षर fields - must unswap bytes alपढ़ोy swapped
			 * by AscReadEEPWord().
			 */
			*wbuf = le16_to_cpu(wval);
		पूर्ण अन्यथा अणु
			/* Don't swap word field at the end - cntl field. */
			*wbuf = wval;
		पूर्ण
		sum += wval;	/* Checksum treats all EEPROM data as words. */
	पूर्ण
	/*
	 * Read the checksum word which will be compared against 'sum'
	 * by the caller. Word field alपढ़ोy swapped.
	 */
	*wbuf = AscReadEEPWord(iop_base, (uअक्षर)s_addr);
	वापस sum;
पूर्ण

अटल पूर्णांक AscTestExternalLram(ASC_DVC_VAR *asc_dvc)
अणु
	PortAddr iop_base;
	uलघु q_addr;
	uलघु saved_word;
	पूर्णांक sta;

	iop_base = asc_dvc->iop_base;
	sta = 0;
	q_addr = ASC_QNO_TO_QADDR(241);
	saved_word = AscReadLramWord(iop_base, q_addr);
	AscSetChipLramAddr(iop_base, q_addr);
	AscSetChipLramData(iop_base, 0x55AA);
	mdelay(10);
	AscSetChipLramAddr(iop_base, q_addr);
	अगर (AscGetChipLramData(iop_base) == 0x55AA) अणु
		sta = 1;
		AscWriteLramWord(iop_base, q_addr, saved_word);
	पूर्ण
	वापस (sta);
पूर्ण

अटल व्योम AscWaitEEPWrite(व्योम)
अणु
	mdelay(20);
पूर्ण

अटल पूर्णांक AscWriteEEPDataReg(PortAddr iop_base, uलघु data_reg)
अणु
	uलघु पढ़ो_back;
	पूर्णांक retry;

	retry = 0;
	जबतक (true) अणु
		AscSetChipEEPData(iop_base, data_reg);
		mdelay(1);
		पढ़ो_back = AscGetChipEEPData(iop_base);
		अगर (पढ़ो_back == data_reg) अणु
			वापस (1);
		पूर्ण
		अगर (retry++ > ASC_EEP_MAX_RETRY) अणु
			वापस (0);
		पूर्ण
	पूर्ण
पूर्ण

अटल uलघु AscWriteEEPWord(PortAddr iop_base, uअक्षर addr, uलघु word_val)
अणु
	uलघु पढ़ो_wval;

	पढ़ो_wval = AscReadEEPWord(iop_base, addr);
	अगर (पढ़ो_wval != word_val) अणु
		AscWriteEEPCmdReg(iop_base, ASC_EEP_CMD_WRITE_ABLE);
		AscWaitEEPRead();
		AscWriteEEPDataReg(iop_base, word_val);
		AscWaitEEPRead();
		AscWriteEEPCmdReg(iop_base,
				  (uअक्षर)((uअक्षर)ASC_EEP_CMD_WRITE | addr));
		AscWaitEEPWrite();
		AscWriteEEPCmdReg(iop_base, ASC_EEP_CMD_WRITE_DISABLE);
		AscWaitEEPRead();
		वापस (AscReadEEPWord(iop_base, addr));
	पूर्ण
	वापस (पढ़ो_wval);
पूर्ण

अटल पूर्णांक AscSetEEPConfigOnce(PortAddr iop_base, ASCEEP_CONFIG *cfg_buf,
			       uलघु bus_type)
अणु
	पूर्णांक n_error;
	uलघु *wbuf;
	uलघु word;
	uलघु sum;
	पूर्णांक s_addr;
	पूर्णांक cfg_beg;
	पूर्णांक cfg_end;
	पूर्णांक uअक्षर_end_in_config = ASC_EEP_MAX_DVC_ADDR - 2;

	wbuf = (uलघु *)cfg_buf;
	n_error = 0;
	sum = 0;
	/* Write two config words; AscWriteEEPWord() will swap bytes. */
	क्रम (s_addr = 0; s_addr < 2; s_addr++, wbuf++) अणु
		sum += *wbuf;
		अगर (*wbuf != AscWriteEEPWord(iop_base, (uअक्षर)s_addr, *wbuf)) अणु
			n_error++;
		पूर्ण
	पूर्ण
	अगर (bus_type & ASC_IS_VL) अणु
		cfg_beg = ASC_EEP_DVC_CFG_BEG_VL;
		cfg_end = ASC_EEP_MAX_DVC_ADDR_VL;
	पूर्ण अन्यथा अणु
		cfg_beg = ASC_EEP_DVC_CFG_BEG;
		cfg_end = ASC_EEP_MAX_DVC_ADDR;
	पूर्ण
	क्रम (s_addr = cfg_beg; s_addr <= (cfg_end - 1); s_addr++, wbuf++) अणु
		अगर (s_addr <= uअक्षर_end_in_config) अणु
			/*
			 * This is a अक्षर field. Swap अक्षर fields beक्रमe they are
			 * swapped again by AscWriteEEPWord().
			 */
			word = cpu_to_le16(*wbuf);
			अगर (word !=
			    AscWriteEEPWord(iop_base, (uअक्षर)s_addr, word)) अणु
				n_error++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Don't swap word field at the end - cntl field. */
			अगर (*wbuf !=
			    AscWriteEEPWord(iop_base, (uअक्षर)s_addr, *wbuf)) अणु
				n_error++;
			पूर्ण
		पूर्ण
		sum += *wbuf;	/* Checksum calculated from word values. */
	पूर्ण
	/* Write checksum word. It will be swapped by AscWriteEEPWord(). */
	*wbuf = sum;
	अगर (sum != AscWriteEEPWord(iop_base, (uअक्षर)s_addr, sum)) अणु
		n_error++;
	पूर्ण

	/* Read EEPROM back again. */
	wbuf = (uलघु *)cfg_buf;
	/*
	 * Read two config words; Byte-swapping करोne by AscReadEEPWord().
	 */
	क्रम (s_addr = 0; s_addr < 2; s_addr++, wbuf++) अणु
		अगर (*wbuf != AscReadEEPWord(iop_base, (uअक्षर)s_addr)) अणु
			n_error++;
		पूर्ण
	पूर्ण
	अगर (bus_type & ASC_IS_VL) अणु
		cfg_beg = ASC_EEP_DVC_CFG_BEG_VL;
		cfg_end = ASC_EEP_MAX_DVC_ADDR_VL;
	पूर्ण अन्यथा अणु
		cfg_beg = ASC_EEP_DVC_CFG_BEG;
		cfg_end = ASC_EEP_MAX_DVC_ADDR;
	पूर्ण
	क्रम (s_addr = cfg_beg; s_addr <= (cfg_end - 1); s_addr++, wbuf++) अणु
		अगर (s_addr <= uअक्षर_end_in_config) अणु
			/*
			 * Swap all अक्षर fields. Must unswap bytes alपढ़ोy swapped
			 * by AscReadEEPWord().
			 */
			word =
			    le16_to_cpu(AscReadEEPWord
					(iop_base, (uअक्षर)s_addr));
		पूर्ण अन्यथा अणु
			/* Don't swap word field at the end - cntl field. */
			word = AscReadEEPWord(iop_base, (uअक्षर)s_addr);
		पूर्ण
		अगर (*wbuf != word) अणु
			n_error++;
		पूर्ण
	पूर्ण
	/* Read checksum; Byte swapping not needed. */
	अगर (AscReadEEPWord(iop_base, (uअक्षर)s_addr) != sum) अणु
		n_error++;
	पूर्ण
	वापस n_error;
पूर्ण

अटल पूर्णांक AscSetEEPConfig(PortAddr iop_base, ASCEEP_CONFIG *cfg_buf,
			   uलघु bus_type)
अणु
	पूर्णांक retry;
	पूर्णांक n_error;

	retry = 0;
	जबतक (true) अणु
		अगर ((n_error = AscSetEEPConfigOnce(iop_base, cfg_buf,
						   bus_type)) == 0) अणु
			अवरोध;
		पूर्ण
		अगर (++retry > ASC_EEP_MAX_RETRY) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	वापस n_error;
पूर्ण

अटल पूर्णांक AscInitFromEEP(ASC_DVC_VAR *asc_dvc)
अणु
	ASCEEP_CONFIG eep_config_buf;
	ASCEEP_CONFIG *eep_config;
	PortAddr iop_base;
	uलघु chksum;
	uलघु warn_code;
	uलघु cfg_msw, cfg_lsw;
	पूर्णांक i;
	पूर्णांक ग_लिखो_eep = 0;

	iop_base = asc_dvc->iop_base;
	warn_code = 0;
	AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0x00FE);
	AscStopQueueExe(iop_base);
	अगर ((AscStopChip(iop_base)) ||
	    (AscGetChipScsiCtrl(iop_base) != 0)) अणु
		asc_dvc->init_state |= ASC_INIT_RESET_SCSI_DONE;
		AscResetChipAndScsiBus(asc_dvc);
		mdelay(asc_dvc->scsi_reset_रुको * 1000); /* XXX: msleep? */
	पूर्ण
	अगर (!AscIsChipHalted(iop_base)) अणु
		asc_dvc->err_code |= ASC_IERR_START_STOP_CHIP;
		वापस (warn_code);
	पूर्ण
	AscSetPCAddr(iop_base, ASC_MCODE_START_ADDR);
	अगर (AscGetPCAddr(iop_base) != ASC_MCODE_START_ADDR) अणु
		asc_dvc->err_code |= ASC_IERR_SET_PC_ADDR;
		वापस (warn_code);
	पूर्ण
	eep_config = (ASCEEP_CONFIG *)&eep_config_buf;
	cfg_msw = AscGetChipCfgMsw(iop_base);
	cfg_lsw = AscGetChipCfgLsw(iop_base);
	अगर ((cfg_msw & ASC_CFG_MSW_CLR_MASK) != 0) अणु
		cfg_msw &= ~ASC_CFG_MSW_CLR_MASK;
		warn_code |= ASC_WARN_CFG_MSW_RECOVER;
		AscSetChipCfgMsw(iop_base, cfg_msw);
	पूर्ण
	chksum = AscGetEEPConfig(iop_base, eep_config, asc_dvc->bus_type);
	ASC_DBG(1, "chksum 0x%x\n", chksum);
	अगर (chksum == 0) अणु
		chksum = 0xaa55;
	पूर्ण
	अगर (AscGetChipStatus(iop_base) & CSW_AUTO_CONFIG) अणु
		warn_code |= ASC_WARN_AUTO_CONFIG;
		अगर (asc_dvc->cfg->chip_version == 3) अणु
			अगर (eep_config->cfg_lsw != cfg_lsw) अणु
				warn_code |= ASC_WARN_EEPROM_RECOVER;
				eep_config->cfg_lsw =
				    AscGetChipCfgLsw(iop_base);
			पूर्ण
			अगर (eep_config->cfg_msw != cfg_msw) अणु
				warn_code |= ASC_WARN_EEPROM_RECOVER;
				eep_config->cfg_msw =
				    AscGetChipCfgMsw(iop_base);
			पूर्ण
		पूर्ण
	पूर्ण
	eep_config->cfg_msw &= ~ASC_CFG_MSW_CLR_MASK;
	eep_config->cfg_lsw |= ASC_CFG0_HOST_INT_ON;
	ASC_DBG(1, "eep_config->chksum 0x%x\n", eep_config->chksum);
	अगर (chksum != eep_config->chksum) अणु
		अगर (AscGetChipVersion(iop_base, asc_dvc->bus_type) ==
		    ASC_CHIP_VER_PCI_ULTRA_3050) अणु
			ASC_DBG(1, "chksum error ignored; EEPROM-less board\n");
			eep_config->init_sdtr = 0xFF;
			eep_config->disc_enable = 0xFF;
			eep_config->start_motor = 0xFF;
			eep_config->use_cmd_qng = 0;
			eep_config->max_total_qng = 0xF0;
			eep_config->max_tag_qng = 0x20;
			eep_config->cntl = 0xBFFF;
			ASC_EEP_SET_CHIP_ID(eep_config, 7);
			eep_config->no_scam = 0;
			eep_config->adapter_info[0] = 0;
			eep_config->adapter_info[1] = 0;
			eep_config->adapter_info[2] = 0;
			eep_config->adapter_info[3] = 0;
			eep_config->adapter_info[4] = 0;
			/* Indicate EEPROM-less board. */
			eep_config->adapter_info[5] = 0xBB;
		पूर्ण अन्यथा अणु
			ASC_PRINT
			    ("AscInitFromEEP: EEPROM checksum error; Will try to re-write EEPROM.\n");
			ग_लिखो_eep = 1;
			warn_code |= ASC_WARN_EEPROM_CHKSUM;
		पूर्ण
	पूर्ण
	asc_dvc->cfg->sdtr_enable = eep_config->init_sdtr;
	asc_dvc->cfg->disc_enable = eep_config->disc_enable;
	asc_dvc->cfg->cmd_qng_enabled = eep_config->use_cmd_qng;
	asc_dvc->start_motor = eep_config->start_motor;
	asc_dvc->dvc_cntl = eep_config->cntl;
	asc_dvc->no_scam = eep_config->no_scam;
	asc_dvc->cfg->adapter_info[0] = eep_config->adapter_info[0];
	asc_dvc->cfg->adapter_info[1] = eep_config->adapter_info[1];
	asc_dvc->cfg->adapter_info[2] = eep_config->adapter_info[2];
	asc_dvc->cfg->adapter_info[3] = eep_config->adapter_info[3];
	asc_dvc->cfg->adapter_info[4] = eep_config->adapter_info[4];
	asc_dvc->cfg->adapter_info[5] = eep_config->adapter_info[5];
	अगर (!AscTestExternalLram(asc_dvc)) अणु
		अगर (((asc_dvc->bus_type & ASC_IS_PCI_ULTRA) ==
		     ASC_IS_PCI_ULTRA)) अणु
			eep_config->max_total_qng =
			    ASC_MAX_PCI_ULTRA_INRAM_TOTAL_QNG;
			eep_config->max_tag_qng =
			    ASC_MAX_PCI_ULTRA_INRAM_TAG_QNG;
		पूर्ण अन्यथा अणु
			eep_config->cfg_msw |= 0x0800;
			cfg_msw |= 0x0800;
			AscSetChipCfgMsw(iop_base, cfg_msw);
			eep_config->max_total_qng = ASC_MAX_PCI_INRAM_TOTAL_QNG;
			eep_config->max_tag_qng = ASC_MAX_INRAM_TAG_QNG;
		पूर्ण
	पूर्ण अन्यथा अणु
	पूर्ण
	अगर (eep_config->max_total_qng < ASC_MIN_TOTAL_QNG) अणु
		eep_config->max_total_qng = ASC_MIN_TOTAL_QNG;
	पूर्ण
	अगर (eep_config->max_total_qng > ASC_MAX_TOTAL_QNG) अणु
		eep_config->max_total_qng = ASC_MAX_TOTAL_QNG;
	पूर्ण
	अगर (eep_config->max_tag_qng > eep_config->max_total_qng) अणु
		eep_config->max_tag_qng = eep_config->max_total_qng;
	पूर्ण
	अगर (eep_config->max_tag_qng < ASC_MIN_TAG_Q_PER_DVC) अणु
		eep_config->max_tag_qng = ASC_MIN_TAG_Q_PER_DVC;
	पूर्ण
	asc_dvc->max_total_qng = eep_config->max_total_qng;
	अगर ((eep_config->use_cmd_qng & eep_config->disc_enable) !=
	    eep_config->use_cmd_qng) अणु
		eep_config->disc_enable = eep_config->use_cmd_qng;
		warn_code |= ASC_WARN_CMD_QNG_CONFLICT;
	पूर्ण
	ASC_EEP_SET_CHIP_ID(eep_config,
			    ASC_EEP_GET_CHIP_ID(eep_config) & ASC_MAX_TID);
	asc_dvc->cfg->chip_scsi_id = ASC_EEP_GET_CHIP_ID(eep_config);
	अगर (((asc_dvc->bus_type & ASC_IS_PCI_ULTRA) == ASC_IS_PCI_ULTRA) &&
	    !(asc_dvc->dvc_cntl & ASC_CNTL_SDTR_ENABLE_ULTRA)) अणु
		asc_dvc->min_sdtr_index = ASC_SDTR_ULTRA_PCI_10MB_INDEX;
	पूर्ण

	क्रम (i = 0; i <= ASC_MAX_TID; i++) अणु
		asc_dvc->करोs_पूर्णांक13_table[i] = eep_config->करोs_पूर्णांक13_table[i];
		asc_dvc->cfg->max_tag_qng[i] = eep_config->max_tag_qng;
		asc_dvc->cfg->sdtr_period_offset[i] =
		    (uअक्षर)(ASC_DEF_SDTR_OFFSET |
			    (asc_dvc->min_sdtr_index << 4));
	पूर्ण
	eep_config->cfg_msw = AscGetChipCfgMsw(iop_base);
	अगर (ग_लिखो_eep) अणु
		अगर ((i = AscSetEEPConfig(iop_base, eep_config,
				     asc_dvc->bus_type)) != 0) अणु
			ASC_PRINT1
			    ("AscInitFromEEP: Failed to re-write EEPROM with %d errors.\n",
			     i);
		पूर्ण अन्यथा अणु
			ASC_PRINT
			    ("AscInitFromEEP: Successfully re-wrote EEPROM.\n");
		पूर्ण
	पूर्ण
	वापस (warn_code);
पूर्ण

अटल पूर्णांक AscInitGetConfig(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *board = shost_priv(shost);
	ASC_DVC_VAR *asc_dvc = &board->dvc_var.asc_dvc_var;
	अचिन्हित लघु warn_code = 0;

	asc_dvc->init_state = ASC_INIT_STATE_BEG_GET_CFG;
	अगर (asc_dvc->err_code != 0)
		वापस asc_dvc->err_code;

	अगर (AscFindSignature(asc_dvc->iop_base)) अणु
		AscInitAscDvcVar(asc_dvc);
		warn_code = AscInitFromEEP(asc_dvc);
		asc_dvc->init_state |= ASC_INIT_STATE_END_GET_CFG;
		अगर (asc_dvc->scsi_reset_रुको > ASC_MAX_SCSI_RESET_WAIT)
			asc_dvc->scsi_reset_रुको = ASC_MAX_SCSI_RESET_WAIT;
	पूर्ण अन्यथा अणु
		asc_dvc->err_code = ASC_IERR_BAD_SIGNATURE;
	पूर्ण

	चयन (warn_code) अणु
	हाल 0:	/* No error */
		अवरोध;
	हाल ASC_WARN_IO_PORT_ROTATE:
		shost_prपूर्णांकk(KERN_WARNING, shost, "I/O port address "
				"modified\n");
		अवरोध;
	हाल ASC_WARN_AUTO_CONFIG:
		shost_prपूर्णांकk(KERN_WARNING, shost, "I/O port increment switch "
				"enabled\n");
		अवरोध;
	हाल ASC_WARN_EEPROM_CHKSUM:
		shost_prपूर्णांकk(KERN_WARNING, shost, "EEPROM checksum error\n");
		अवरोध;
	हाल ASC_WARN_IRQ_MODIFIED:
		shost_prपूर्णांकk(KERN_WARNING, shost, "IRQ modified\n");
		अवरोध;
	हाल ASC_WARN_CMD_QNG_CONFLICT:
		shost_prपूर्णांकk(KERN_WARNING, shost, "tag queuing enabled w/o "
				"disconnects\n");
		अवरोध;
	शेष:
		shost_prपूर्णांकk(KERN_WARNING, shost, "unknown warning: 0x%x\n",
				warn_code);
		अवरोध;
	पूर्ण

	अगर (asc_dvc->err_code != 0)
		shost_prपूर्णांकk(KERN_ERR, shost, "error 0x%x at init_state "
			"0x%x\n", asc_dvc->err_code, asc_dvc->init_state);

	वापस asc_dvc->err_code;
पूर्ण

अटल पूर्णांक AscInitSetConfig(काष्ठा pci_dev *pdev, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *board = shost_priv(shost);
	ASC_DVC_VAR *asc_dvc = &board->dvc_var.asc_dvc_var;
	PortAddr iop_base = asc_dvc->iop_base;
	अचिन्हित लघु cfg_msw;
	अचिन्हित लघु warn_code = 0;

	asc_dvc->init_state |= ASC_INIT_STATE_BEG_SET_CFG;
	अगर (asc_dvc->err_code != 0)
		वापस asc_dvc->err_code;
	अगर (!AscFindSignature(asc_dvc->iop_base)) अणु
		asc_dvc->err_code = ASC_IERR_BAD_SIGNATURE;
		वापस asc_dvc->err_code;
	पूर्ण

	cfg_msw = AscGetChipCfgMsw(iop_base);
	अगर ((cfg_msw & ASC_CFG_MSW_CLR_MASK) != 0) अणु
		cfg_msw &= ~ASC_CFG_MSW_CLR_MASK;
		warn_code |= ASC_WARN_CFG_MSW_RECOVER;
		AscSetChipCfgMsw(iop_base, cfg_msw);
	पूर्ण
	अगर ((asc_dvc->cfg->cmd_qng_enabled & asc_dvc->cfg->disc_enable) !=
	    asc_dvc->cfg->cmd_qng_enabled) अणु
		asc_dvc->cfg->disc_enable = asc_dvc->cfg->cmd_qng_enabled;
		warn_code |= ASC_WARN_CMD_QNG_CONFLICT;
	पूर्ण
	अगर (AscGetChipStatus(iop_base) & CSW_AUTO_CONFIG) अणु
		warn_code |= ASC_WARN_AUTO_CONFIG;
	पूर्ण
#अगर_घोषित CONFIG_PCI
	अगर (asc_dvc->bus_type & ASC_IS_PCI) अणु
		cfg_msw &= 0xFFC0;
		AscSetChipCfgMsw(iop_base, cfg_msw);
		अगर ((asc_dvc->bus_type & ASC_IS_PCI_ULTRA) == ASC_IS_PCI_ULTRA) अणु
		पूर्ण अन्यथा अणु
			अगर ((pdev->device == PCI_DEVICE_ID_ASP_1200A) ||
			    (pdev->device == PCI_DEVICE_ID_ASP_ABP940)) अणु
				asc_dvc->bug_fix_cntl |= ASC_BUG_FIX_IF_NOT_DWB;
				asc_dvc->bug_fix_cntl |=
				    ASC_BUG_FIX_ASYN_USE_SYN;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर /* CONFIG_PCI */
	अगर (AscSetChipScsiID(iop_base, asc_dvc->cfg->chip_scsi_id) !=
	    asc_dvc->cfg->chip_scsi_id) अणु
		asc_dvc->err_code |= ASC_IERR_SET_SCSI_ID;
	पूर्ण

	asc_dvc->init_state |= ASC_INIT_STATE_END_SET_CFG;

	चयन (warn_code) अणु
	हाल 0:	/* No error. */
		अवरोध;
	हाल ASC_WARN_IO_PORT_ROTATE:
		shost_prपूर्णांकk(KERN_WARNING, shost, "I/O port address "
				"modified\n");
		अवरोध;
	हाल ASC_WARN_AUTO_CONFIG:
		shost_prपूर्णांकk(KERN_WARNING, shost, "I/O port increment switch "
				"enabled\n");
		अवरोध;
	हाल ASC_WARN_EEPROM_CHKSUM:
		shost_prपूर्णांकk(KERN_WARNING, shost, "EEPROM checksum error\n");
		अवरोध;
	हाल ASC_WARN_IRQ_MODIFIED:
		shost_prपूर्णांकk(KERN_WARNING, shost, "IRQ modified\n");
		अवरोध;
	हाल ASC_WARN_CMD_QNG_CONFLICT:
		shost_prपूर्णांकk(KERN_WARNING, shost, "tag queuing w/o "
				"disconnects\n");
		अवरोध;
	शेष:
		shost_prपूर्णांकk(KERN_WARNING, shost, "unknown warning: 0x%x\n",
				warn_code);
		अवरोध;
	पूर्ण

	अगर (asc_dvc->err_code != 0)
		shost_prपूर्णांकk(KERN_ERR, shost, "error 0x%x at init_state "
			"0x%x\n", asc_dvc->err_code, asc_dvc->init_state);

	वापस asc_dvc->err_code;
पूर्ण

/*
 * EEPROM Configuration.
 *
 * All drivers should use this काष्ठाure to set the शेष EEPROM
 * configuration. The BIOS now uses this काष्ठाure when it is built.
 * Additional काष्ठाure inक्रमmation can be found in a_conकरोr.h where
 * the काष्ठाure is defined.
 *
 * The *_Field_IsChar काष्ठाs are needed to correct क्रम endianness.
 * These values are पढ़ो from the board 16 bits at a समय directly
 * पूर्णांकo the काष्ठाs. Because some fields are अक्षर, the values will be
 * in the wrong order. The *_Field_IsChar tells when to flip the
 * bytes. Data पढ़ो and written to PCI memory is स्वतःmatically swapped
 * on big-endian platक्रमms so अक्षर fields पढ़ो as words are actually being
 * unswapped on big-endian platक्रमms.
 */
#अगर_घोषित CONFIG_PCI
अटल ADVEEP_3550_CONFIG Default_3550_EEPROM_Config = अणु
	ADV_EEPROM_BIOS_ENABLE,	/* cfg_lsw */
	0x0000,			/* cfg_msw */
	0xFFFF,			/* disc_enable */
	0xFFFF,			/* wdtr_able */
	0xFFFF,			/* sdtr_able */
	0xFFFF,			/* start_motor */
	0xFFFF,			/* tagqng_able */
	0xFFFF,			/* bios_scan */
	0,			/* scam_tolerant */
	7,			/* adapter_scsi_id */
	0,			/* bios_boot_delay */
	3,			/* scsi_reset_delay */
	0,			/* bios_id_lun */
	0,			/* termination */
	0,			/* reserved1 */
	0xFFE7,			/* bios_ctrl */
	0xFFFF,			/* ultra_able */
	0,			/* reserved2 */
	ASC_DEF_MAX_HOST_QNG,	/* max_host_qng */
	ASC_DEF_MAX_DVC_QNG,	/* max_dvc_qng */
	0,			/* dvc_cntl */
	0,			/* bug_fix */
	0,			/* serial_number_word1 */
	0,			/* serial_number_word2 */
	0,			/* serial_number_word3 */
	0,			/* check_sum */
	अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण
	,			/* oem_name[16] */
	0,			/* dvc_err_code */
	0,			/* adv_err_code */
	0,			/* adv_err_addr */
	0,			/* saved_dvc_err_code */
	0,			/* saved_adv_err_code */
	0,			/* saved_adv_err_addr */
	0			/* num_of_err */
पूर्ण;

अटल ADVEEP_3550_CONFIG ADVEEP_3550_Config_Field_IsChar = अणु
	0,			/* cfg_lsw */
	0,			/* cfg_msw */
	0,			/* -disc_enable */
	0,			/* wdtr_able */
	0,			/* sdtr_able */
	0,			/* start_motor */
	0,			/* tagqng_able */
	0,			/* bios_scan */
	0,			/* scam_tolerant */
	1,			/* adapter_scsi_id */
	1,			/* bios_boot_delay */
	1,			/* scsi_reset_delay */
	1,			/* bios_id_lun */
	1,			/* termination */
	1,			/* reserved1 */
	0,			/* bios_ctrl */
	0,			/* ultra_able */
	0,			/* reserved2 */
	1,			/* max_host_qng */
	1,			/* max_dvc_qng */
	0,			/* dvc_cntl */
	0,			/* bug_fix */
	0,			/* serial_number_word1 */
	0,			/* serial_number_word2 */
	0,			/* serial_number_word3 */
	0,			/* check_sum */
	अणु1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1पूर्ण
	,			/* oem_name[16] */
	0,			/* dvc_err_code */
	0,			/* adv_err_code */
	0,			/* adv_err_addr */
	0,			/* saved_dvc_err_code */
	0,			/* saved_adv_err_code */
	0,			/* saved_adv_err_addr */
	0			/* num_of_err */
पूर्ण;

अटल ADVEEP_38C0800_CONFIG Default_38C0800_EEPROM_Config = अणु
	ADV_EEPROM_BIOS_ENABLE,	/* 00 cfg_lsw */
	0x0000,			/* 01 cfg_msw */
	0xFFFF,			/* 02 disc_enable */
	0xFFFF,			/* 03 wdtr_able */
	0x4444,			/* 04 sdtr_speed1 */
	0xFFFF,			/* 05 start_motor */
	0xFFFF,			/* 06 tagqng_able */
	0xFFFF,			/* 07 bios_scan */
	0,			/* 08 scam_tolerant */
	7,			/* 09 adapter_scsi_id */
	0,			/*    bios_boot_delay */
	3,			/* 10 scsi_reset_delay */
	0,			/*    bios_id_lun */
	0,			/* 11 termination_se */
	0,			/*    termination_lvd */
	0xFFE7,			/* 12 bios_ctrl */
	0x4444,			/* 13 sdtr_speed2 */
	0x4444,			/* 14 sdtr_speed3 */
	ASC_DEF_MAX_HOST_QNG,	/* 15 max_host_qng */
	ASC_DEF_MAX_DVC_QNG,	/*    max_dvc_qng */
	0,			/* 16 dvc_cntl */
	0x4444,			/* 17 sdtr_speed4 */
	0,			/* 18 serial_number_word1 */
	0,			/* 19 serial_number_word2 */
	0,			/* 20 serial_number_word3 */
	0,			/* 21 check_sum */
	अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण
	,			/* 22-29 oem_name[16] */
	0,			/* 30 dvc_err_code */
	0,			/* 31 adv_err_code */
	0,			/* 32 adv_err_addr */
	0,			/* 33 saved_dvc_err_code */
	0,			/* 34 saved_adv_err_code */
	0,			/* 35 saved_adv_err_addr */
	0,			/* 36 reserved */
	0,			/* 37 reserved */
	0,			/* 38 reserved */
	0,			/* 39 reserved */
	0,			/* 40 reserved */
	0,			/* 41 reserved */
	0,			/* 42 reserved */
	0,			/* 43 reserved */
	0,			/* 44 reserved */
	0,			/* 45 reserved */
	0,			/* 46 reserved */
	0,			/* 47 reserved */
	0,			/* 48 reserved */
	0,			/* 49 reserved */
	0,			/* 50 reserved */
	0,			/* 51 reserved */
	0,			/* 52 reserved */
	0,			/* 53 reserved */
	0,			/* 54 reserved */
	0,			/* 55 reserved */
	0,			/* 56 cisptr_lsw */
	0,			/* 57 cisprt_msw */
	PCI_VENDOR_ID_ASP,	/* 58 subsysvid */
	PCI_DEVICE_ID_38C0800_REV1,	/* 59 subsysid */
	0,			/* 60 reserved */
	0,			/* 61 reserved */
	0,			/* 62 reserved */
	0			/* 63 reserved */
पूर्ण;

अटल ADVEEP_38C0800_CONFIG ADVEEP_38C0800_Config_Field_IsChar = अणु
	0,			/* 00 cfg_lsw */
	0,			/* 01 cfg_msw */
	0,			/* 02 disc_enable */
	0,			/* 03 wdtr_able */
	0,			/* 04 sdtr_speed1 */
	0,			/* 05 start_motor */
	0,			/* 06 tagqng_able */
	0,			/* 07 bios_scan */
	0,			/* 08 scam_tolerant */
	1,			/* 09 adapter_scsi_id */
	1,			/*    bios_boot_delay */
	1,			/* 10 scsi_reset_delay */
	1,			/*    bios_id_lun */
	1,			/* 11 termination_se */
	1,			/*    termination_lvd */
	0,			/* 12 bios_ctrl */
	0,			/* 13 sdtr_speed2 */
	0,			/* 14 sdtr_speed3 */
	1,			/* 15 max_host_qng */
	1,			/*    max_dvc_qng */
	0,			/* 16 dvc_cntl */
	0,			/* 17 sdtr_speed4 */
	0,			/* 18 serial_number_word1 */
	0,			/* 19 serial_number_word2 */
	0,			/* 20 serial_number_word3 */
	0,			/* 21 check_sum */
	अणु1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1पूर्ण
	,			/* 22-29 oem_name[16] */
	0,			/* 30 dvc_err_code */
	0,			/* 31 adv_err_code */
	0,			/* 32 adv_err_addr */
	0,			/* 33 saved_dvc_err_code */
	0,			/* 34 saved_adv_err_code */
	0,			/* 35 saved_adv_err_addr */
	0,			/* 36 reserved */
	0,			/* 37 reserved */
	0,			/* 38 reserved */
	0,			/* 39 reserved */
	0,			/* 40 reserved */
	0,			/* 41 reserved */
	0,			/* 42 reserved */
	0,			/* 43 reserved */
	0,			/* 44 reserved */
	0,			/* 45 reserved */
	0,			/* 46 reserved */
	0,			/* 47 reserved */
	0,			/* 48 reserved */
	0,			/* 49 reserved */
	0,			/* 50 reserved */
	0,			/* 51 reserved */
	0,			/* 52 reserved */
	0,			/* 53 reserved */
	0,			/* 54 reserved */
	0,			/* 55 reserved */
	0,			/* 56 cisptr_lsw */
	0,			/* 57 cisprt_msw */
	0,			/* 58 subsysvid */
	0,			/* 59 subsysid */
	0,			/* 60 reserved */
	0,			/* 61 reserved */
	0,			/* 62 reserved */
	0			/* 63 reserved */
पूर्ण;

अटल ADVEEP_38C1600_CONFIG Default_38C1600_EEPROM_Config = अणु
	ADV_EEPROM_BIOS_ENABLE,	/* 00 cfg_lsw */
	0x0000,			/* 01 cfg_msw */
	0xFFFF,			/* 02 disc_enable */
	0xFFFF,			/* 03 wdtr_able */
	0x5555,			/* 04 sdtr_speed1 */
	0xFFFF,			/* 05 start_motor */
	0xFFFF,			/* 06 tagqng_able */
	0xFFFF,			/* 07 bios_scan */
	0,			/* 08 scam_tolerant */
	7,			/* 09 adapter_scsi_id */
	0,			/*    bios_boot_delay */
	3,			/* 10 scsi_reset_delay */
	0,			/*    bios_id_lun */
	0,			/* 11 termination_se */
	0,			/*    termination_lvd */
	0xFFE7,			/* 12 bios_ctrl */
	0x5555,			/* 13 sdtr_speed2 */
	0x5555,			/* 14 sdtr_speed3 */
	ASC_DEF_MAX_HOST_QNG,	/* 15 max_host_qng */
	ASC_DEF_MAX_DVC_QNG,	/*    max_dvc_qng */
	0,			/* 16 dvc_cntl */
	0x5555,			/* 17 sdtr_speed4 */
	0,			/* 18 serial_number_word1 */
	0,			/* 19 serial_number_word2 */
	0,			/* 20 serial_number_word3 */
	0,			/* 21 check_sum */
	अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण
	,			/* 22-29 oem_name[16] */
	0,			/* 30 dvc_err_code */
	0,			/* 31 adv_err_code */
	0,			/* 32 adv_err_addr */
	0,			/* 33 saved_dvc_err_code */
	0,			/* 34 saved_adv_err_code */
	0,			/* 35 saved_adv_err_addr */
	0,			/* 36 reserved */
	0,			/* 37 reserved */
	0,			/* 38 reserved */
	0,			/* 39 reserved */
	0,			/* 40 reserved */
	0,			/* 41 reserved */
	0,			/* 42 reserved */
	0,			/* 43 reserved */
	0,			/* 44 reserved */
	0,			/* 45 reserved */
	0,			/* 46 reserved */
	0,			/* 47 reserved */
	0,			/* 48 reserved */
	0,			/* 49 reserved */
	0,			/* 50 reserved */
	0,			/* 51 reserved */
	0,			/* 52 reserved */
	0,			/* 53 reserved */
	0,			/* 54 reserved */
	0,			/* 55 reserved */
	0,			/* 56 cisptr_lsw */
	0,			/* 57 cisprt_msw */
	PCI_VENDOR_ID_ASP,	/* 58 subsysvid */
	PCI_DEVICE_ID_38C1600_REV1,	/* 59 subsysid */
	0,			/* 60 reserved */
	0,			/* 61 reserved */
	0,			/* 62 reserved */
	0			/* 63 reserved */
पूर्ण;

अटल ADVEEP_38C1600_CONFIG ADVEEP_38C1600_Config_Field_IsChar = अणु
	0,			/* 00 cfg_lsw */
	0,			/* 01 cfg_msw */
	0,			/* 02 disc_enable */
	0,			/* 03 wdtr_able */
	0,			/* 04 sdtr_speed1 */
	0,			/* 05 start_motor */
	0,			/* 06 tagqng_able */
	0,			/* 07 bios_scan */
	0,			/* 08 scam_tolerant */
	1,			/* 09 adapter_scsi_id */
	1,			/*    bios_boot_delay */
	1,			/* 10 scsi_reset_delay */
	1,			/*    bios_id_lun */
	1,			/* 11 termination_se */
	1,			/*    termination_lvd */
	0,			/* 12 bios_ctrl */
	0,			/* 13 sdtr_speed2 */
	0,			/* 14 sdtr_speed3 */
	1,			/* 15 max_host_qng */
	1,			/*    max_dvc_qng */
	0,			/* 16 dvc_cntl */
	0,			/* 17 sdtr_speed4 */
	0,			/* 18 serial_number_word1 */
	0,			/* 19 serial_number_word2 */
	0,			/* 20 serial_number_word3 */
	0,			/* 21 check_sum */
	अणु1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1पूर्ण
	,			/* 22-29 oem_name[16] */
	0,			/* 30 dvc_err_code */
	0,			/* 31 adv_err_code */
	0,			/* 32 adv_err_addr */
	0,			/* 33 saved_dvc_err_code */
	0,			/* 34 saved_adv_err_code */
	0,			/* 35 saved_adv_err_addr */
	0,			/* 36 reserved */
	0,			/* 37 reserved */
	0,			/* 38 reserved */
	0,			/* 39 reserved */
	0,			/* 40 reserved */
	0,			/* 41 reserved */
	0,			/* 42 reserved */
	0,			/* 43 reserved */
	0,			/* 44 reserved */
	0,			/* 45 reserved */
	0,			/* 46 reserved */
	0,			/* 47 reserved */
	0,			/* 48 reserved */
	0,			/* 49 reserved */
	0,			/* 50 reserved */
	0,			/* 51 reserved */
	0,			/* 52 reserved */
	0,			/* 53 reserved */
	0,			/* 54 reserved */
	0,			/* 55 reserved */
	0,			/* 56 cisptr_lsw */
	0,			/* 57 cisprt_msw */
	0,			/* 58 subsysvid */
	0,			/* 59 subsysid */
	0,			/* 60 reserved */
	0,			/* 61 reserved */
	0,			/* 62 reserved */
	0			/* 63 reserved */
पूर्ण;

/*
 * Wait क्रम EEPROM command to complete
 */
अटल व्योम AdvWaitEEPCmd(AdvPortAddr iop_base)
अणु
	पूर्णांक eep_delay_ms;

	क्रम (eep_delay_ms = 0; eep_delay_ms < ADV_EEP_DELAY_MS; eep_delay_ms++) अणु
		अगर (AdvReadWordRegister(iop_base, IOPW_EE_CMD) &
		    ASC_EEP_CMD_DONE) अणु
			अवरोध;
		पूर्ण
		mdelay(1);
	पूर्ण
	अगर ((AdvReadWordRegister(iop_base, IOPW_EE_CMD) & ASC_EEP_CMD_DONE) ==
	    0)
		BUG();
पूर्ण

/*
 * Read the EEPROM from specअगरied location
 */
अटल uलघु AdvReadEEPWord(AdvPortAddr iop_base, पूर्णांक eep_word_addr)
अणु
	AdvWriteWordRegister(iop_base, IOPW_EE_CMD,
			     ASC_EEP_CMD_READ | eep_word_addr);
	AdvWaitEEPCmd(iop_base);
	वापस AdvReadWordRegister(iop_base, IOPW_EE_DATA);
पूर्ण

/*
 * Write the EEPROM from 'cfg_buf'.
 */
अटल व्योम AdvSet3550EEPConfig(AdvPortAddr iop_base,
				ADVEEP_3550_CONFIG *cfg_buf)
अणु
	uलघु *wbuf;
	uलघु addr, chksum;
	uलघु *अक्षरfields;

	wbuf = (uलघु *)cfg_buf;
	अक्षरfields = (uलघु *)&ADVEEP_3550_Config_Field_IsChar;
	chksum = 0;

	AdvWriteWordRegister(iop_base, IOPW_EE_CMD, ASC_EEP_CMD_WRITE_ABLE);
	AdvWaitEEPCmd(iop_base);

	/*
	 * Write EEPROM from word 0 to word 20.
	 */
	क्रम (addr = ADV_EEP_DVC_CFG_BEGIN;
	     addr < ADV_EEP_DVC_CFG_END; addr++, wbuf++) अणु
		uलघु word;

		अगर (*अक्षरfields++) अणु
			word = cpu_to_le16(*wbuf);
		पूर्ण अन्यथा अणु
			word = *wbuf;
		पूर्ण
		chksum += *wbuf;	/* Checksum is calculated from word values. */
		AdvWriteWordRegister(iop_base, IOPW_EE_DATA, word);
		AdvWriteWordRegister(iop_base, IOPW_EE_CMD,
				     ASC_EEP_CMD_WRITE | addr);
		AdvWaitEEPCmd(iop_base);
		mdelay(ADV_EEP_DELAY_MS);
	पूर्ण

	/*
	 * Write EEPROM checksum at word 21.
	 */
	AdvWriteWordRegister(iop_base, IOPW_EE_DATA, chksum);
	AdvWriteWordRegister(iop_base, IOPW_EE_CMD, ASC_EEP_CMD_WRITE | addr);
	AdvWaitEEPCmd(iop_base);
	wbuf++;
	अक्षरfields++;

	/*
	 * Write EEPROM OEM name at words 22 to 29.
	 */
	क्रम (addr = ADV_EEP_DVC_CTL_BEGIN;
	     addr < ADV_EEP_MAX_WORD_ADDR; addr++, wbuf++) अणु
		uलघु word;

		अगर (*अक्षरfields++) अणु
			word = cpu_to_le16(*wbuf);
		पूर्ण अन्यथा अणु
			word = *wbuf;
		पूर्ण
		AdvWriteWordRegister(iop_base, IOPW_EE_DATA, word);
		AdvWriteWordRegister(iop_base, IOPW_EE_CMD,
				     ASC_EEP_CMD_WRITE | addr);
		AdvWaitEEPCmd(iop_base);
	पूर्ण
	AdvWriteWordRegister(iop_base, IOPW_EE_CMD, ASC_EEP_CMD_WRITE_DISABLE);
	AdvWaitEEPCmd(iop_base);
पूर्ण

/*
 * Write the EEPROM from 'cfg_buf'.
 */
अटल व्योम AdvSet38C0800EEPConfig(AdvPortAddr iop_base,
				   ADVEEP_38C0800_CONFIG *cfg_buf)
अणु
	uलघु *wbuf;
	uलघु *अक्षरfields;
	uलघु addr, chksum;

	wbuf = (uलघु *)cfg_buf;
	अक्षरfields = (uलघु *)&ADVEEP_38C0800_Config_Field_IsChar;
	chksum = 0;

	AdvWriteWordRegister(iop_base, IOPW_EE_CMD, ASC_EEP_CMD_WRITE_ABLE);
	AdvWaitEEPCmd(iop_base);

	/*
	 * Write EEPROM from word 0 to word 20.
	 */
	क्रम (addr = ADV_EEP_DVC_CFG_BEGIN;
	     addr < ADV_EEP_DVC_CFG_END; addr++, wbuf++) अणु
		uलघु word;

		अगर (*अक्षरfields++) अणु
			word = cpu_to_le16(*wbuf);
		पूर्ण अन्यथा अणु
			word = *wbuf;
		पूर्ण
		chksum += *wbuf;	/* Checksum is calculated from word values. */
		AdvWriteWordRegister(iop_base, IOPW_EE_DATA, word);
		AdvWriteWordRegister(iop_base, IOPW_EE_CMD,
				     ASC_EEP_CMD_WRITE | addr);
		AdvWaitEEPCmd(iop_base);
		mdelay(ADV_EEP_DELAY_MS);
	पूर्ण

	/*
	 * Write EEPROM checksum at word 21.
	 */
	AdvWriteWordRegister(iop_base, IOPW_EE_DATA, chksum);
	AdvWriteWordRegister(iop_base, IOPW_EE_CMD, ASC_EEP_CMD_WRITE | addr);
	AdvWaitEEPCmd(iop_base);
	wbuf++;
	अक्षरfields++;

	/*
	 * Write EEPROM OEM name at words 22 to 29.
	 */
	क्रम (addr = ADV_EEP_DVC_CTL_BEGIN;
	     addr < ADV_EEP_MAX_WORD_ADDR; addr++, wbuf++) अणु
		uलघु word;

		अगर (*अक्षरfields++) अणु
			word = cpu_to_le16(*wbuf);
		पूर्ण अन्यथा अणु
			word = *wbuf;
		पूर्ण
		AdvWriteWordRegister(iop_base, IOPW_EE_DATA, word);
		AdvWriteWordRegister(iop_base, IOPW_EE_CMD,
				     ASC_EEP_CMD_WRITE | addr);
		AdvWaitEEPCmd(iop_base);
	पूर्ण
	AdvWriteWordRegister(iop_base, IOPW_EE_CMD, ASC_EEP_CMD_WRITE_DISABLE);
	AdvWaitEEPCmd(iop_base);
पूर्ण

/*
 * Write the EEPROM from 'cfg_buf'.
 */
अटल व्योम AdvSet38C1600EEPConfig(AdvPortAddr iop_base,
				   ADVEEP_38C1600_CONFIG *cfg_buf)
अणु
	uलघु *wbuf;
	uलघु *अक्षरfields;
	uलघु addr, chksum;

	wbuf = (uलघु *)cfg_buf;
	अक्षरfields = (uलघु *)&ADVEEP_38C1600_Config_Field_IsChar;
	chksum = 0;

	AdvWriteWordRegister(iop_base, IOPW_EE_CMD, ASC_EEP_CMD_WRITE_ABLE);
	AdvWaitEEPCmd(iop_base);

	/*
	 * Write EEPROM from word 0 to word 20.
	 */
	क्रम (addr = ADV_EEP_DVC_CFG_BEGIN;
	     addr < ADV_EEP_DVC_CFG_END; addr++, wbuf++) अणु
		uलघु word;

		अगर (*अक्षरfields++) अणु
			word = cpu_to_le16(*wbuf);
		पूर्ण अन्यथा अणु
			word = *wbuf;
		पूर्ण
		chksum += *wbuf;	/* Checksum is calculated from word values. */
		AdvWriteWordRegister(iop_base, IOPW_EE_DATA, word);
		AdvWriteWordRegister(iop_base, IOPW_EE_CMD,
				     ASC_EEP_CMD_WRITE | addr);
		AdvWaitEEPCmd(iop_base);
		mdelay(ADV_EEP_DELAY_MS);
	पूर्ण

	/*
	 * Write EEPROM checksum at word 21.
	 */
	AdvWriteWordRegister(iop_base, IOPW_EE_DATA, chksum);
	AdvWriteWordRegister(iop_base, IOPW_EE_CMD, ASC_EEP_CMD_WRITE | addr);
	AdvWaitEEPCmd(iop_base);
	wbuf++;
	अक्षरfields++;

	/*
	 * Write EEPROM OEM name at words 22 to 29.
	 */
	क्रम (addr = ADV_EEP_DVC_CTL_BEGIN;
	     addr < ADV_EEP_MAX_WORD_ADDR; addr++, wbuf++) अणु
		uलघु word;

		अगर (*अक्षरfields++) अणु
			word = cpu_to_le16(*wbuf);
		पूर्ण अन्यथा अणु
			word = *wbuf;
		पूर्ण
		AdvWriteWordRegister(iop_base, IOPW_EE_DATA, word);
		AdvWriteWordRegister(iop_base, IOPW_EE_CMD,
				     ASC_EEP_CMD_WRITE | addr);
		AdvWaitEEPCmd(iop_base);
	पूर्ण
	AdvWriteWordRegister(iop_base, IOPW_EE_CMD, ASC_EEP_CMD_WRITE_DISABLE);
	AdvWaitEEPCmd(iop_base);
पूर्ण

/*
 * Read EEPROM configuration पूर्णांकo the specअगरied buffer.
 *
 * Return a checksum based on the EEPROM configuration पढ़ो.
 */
अटल uलघु AdvGet3550EEPConfig(AdvPortAddr iop_base,
				  ADVEEP_3550_CONFIG *cfg_buf)
अणु
	uलघु wval, chksum;
	uलघु *wbuf;
	पूर्णांक eep_addr;
	uलघु *अक्षरfields;

	अक्षरfields = (uलघु *)&ADVEEP_3550_Config_Field_IsChar;
	wbuf = (uलघु *)cfg_buf;
	chksum = 0;

	क्रम (eep_addr = ADV_EEP_DVC_CFG_BEGIN;
	     eep_addr < ADV_EEP_DVC_CFG_END; eep_addr++, wbuf++) अणु
		wval = AdvReadEEPWord(iop_base, eep_addr);
		chksum += wval;	/* Checksum is calculated from word values. */
		अगर (*अक्षरfields++) अणु
			*wbuf = le16_to_cpu(wval);
		पूर्ण अन्यथा अणु
			*wbuf = wval;
		पूर्ण
	पूर्ण
	/* Read checksum word. */
	*wbuf = AdvReadEEPWord(iop_base, eep_addr);
	wbuf++;
	अक्षरfields++;

	/* Read rest of EEPROM not covered by the checksum. */
	क्रम (eep_addr = ADV_EEP_DVC_CTL_BEGIN;
	     eep_addr < ADV_EEP_MAX_WORD_ADDR; eep_addr++, wbuf++) अणु
		*wbuf = AdvReadEEPWord(iop_base, eep_addr);
		अगर (*अक्षरfields++) अणु
			*wbuf = le16_to_cpu(*wbuf);
		पूर्ण
	पूर्ण
	वापस chksum;
पूर्ण

/*
 * Read EEPROM configuration पूर्णांकo the specअगरied buffer.
 *
 * Return a checksum based on the EEPROM configuration पढ़ो.
 */
अटल uलघु AdvGet38C0800EEPConfig(AdvPortAddr iop_base,
				     ADVEEP_38C0800_CONFIG *cfg_buf)
अणु
	uलघु wval, chksum;
	uलघु *wbuf;
	पूर्णांक eep_addr;
	uलघु *अक्षरfields;

	अक्षरfields = (uलघु *)&ADVEEP_38C0800_Config_Field_IsChar;
	wbuf = (uलघु *)cfg_buf;
	chksum = 0;

	क्रम (eep_addr = ADV_EEP_DVC_CFG_BEGIN;
	     eep_addr < ADV_EEP_DVC_CFG_END; eep_addr++, wbuf++) अणु
		wval = AdvReadEEPWord(iop_base, eep_addr);
		chksum += wval;	/* Checksum is calculated from word values. */
		अगर (*अक्षरfields++) अणु
			*wbuf = le16_to_cpu(wval);
		पूर्ण अन्यथा अणु
			*wbuf = wval;
		पूर्ण
	पूर्ण
	/* Read checksum word. */
	*wbuf = AdvReadEEPWord(iop_base, eep_addr);
	wbuf++;
	अक्षरfields++;

	/* Read rest of EEPROM not covered by the checksum. */
	क्रम (eep_addr = ADV_EEP_DVC_CTL_BEGIN;
	     eep_addr < ADV_EEP_MAX_WORD_ADDR; eep_addr++, wbuf++) अणु
		*wbuf = AdvReadEEPWord(iop_base, eep_addr);
		अगर (*अक्षरfields++) अणु
			*wbuf = le16_to_cpu(*wbuf);
		पूर्ण
	पूर्ण
	वापस chksum;
पूर्ण

/*
 * Read EEPROM configuration पूर्णांकo the specअगरied buffer.
 *
 * Return a checksum based on the EEPROM configuration पढ़ो.
 */
अटल uलघु AdvGet38C1600EEPConfig(AdvPortAddr iop_base,
				     ADVEEP_38C1600_CONFIG *cfg_buf)
अणु
	uलघु wval, chksum;
	uलघु *wbuf;
	पूर्णांक eep_addr;
	uलघु *अक्षरfields;

	अक्षरfields = (uलघु *)&ADVEEP_38C1600_Config_Field_IsChar;
	wbuf = (uलघु *)cfg_buf;
	chksum = 0;

	क्रम (eep_addr = ADV_EEP_DVC_CFG_BEGIN;
	     eep_addr < ADV_EEP_DVC_CFG_END; eep_addr++, wbuf++) अणु
		wval = AdvReadEEPWord(iop_base, eep_addr);
		chksum += wval;	/* Checksum is calculated from word values. */
		अगर (*अक्षरfields++) अणु
			*wbuf = le16_to_cpu(wval);
		पूर्ण अन्यथा अणु
			*wbuf = wval;
		पूर्ण
	पूर्ण
	/* Read checksum word. */
	*wbuf = AdvReadEEPWord(iop_base, eep_addr);
	wbuf++;
	अक्षरfields++;

	/* Read rest of EEPROM not covered by the checksum. */
	क्रम (eep_addr = ADV_EEP_DVC_CTL_BEGIN;
	     eep_addr < ADV_EEP_MAX_WORD_ADDR; eep_addr++, wbuf++) अणु
		*wbuf = AdvReadEEPWord(iop_base, eep_addr);
		अगर (*अक्षरfields++) अणु
			*wbuf = le16_to_cpu(*wbuf);
		पूर्ण
	पूर्ण
	वापस chksum;
पूर्ण

/*
 * Read the board's EEPROM configuration. Set fields in ADV_DVC_VAR and
 * ADV_DVC_CFG based on the EEPROM settings. The chip is stopped जबतक
 * all of this is करोne.
 *
 * On failure set the ADV_DVC_VAR field 'err_code' and वापस ADV_ERROR.
 *
 * For a non-fatal error वापस a warning code. If there are no warnings
 * then 0 is वापसed.
 *
 * Note: Chip is stopped on entry.
 */
अटल पूर्णांक AdvInitFrom3550EEP(ADV_DVC_VAR *asc_dvc)
अणु
	AdvPortAddr iop_base;
	uलघु warn_code;
	ADVEEP_3550_CONFIG eep_config;

	iop_base = asc_dvc->iop_base;

	warn_code = 0;

	/*
	 * Read the board's EEPROM configuration.
	 *
	 * Set शेष values अगर a bad checksum is found.
	 */
	अगर (AdvGet3550EEPConfig(iop_base, &eep_config) != eep_config.check_sum) अणु
		warn_code |= ASC_WARN_EEPROM_CHKSUM;

		/*
		 * Set EEPROM शेष values.
		 */
		स_नकल(&eep_config, &Default_3550_EEPROM_Config,
			माप(ADVEEP_3550_CONFIG));

		/*
		 * Assume the 6 byte board serial number that was पढ़ो from
		 * EEPROM is correct even अगर the EEPROM checksum failed.
		 */
		eep_config.serial_number_word3 =
		    AdvReadEEPWord(iop_base, ADV_EEP_DVC_CFG_END - 1);

		eep_config.serial_number_word2 =
		    AdvReadEEPWord(iop_base, ADV_EEP_DVC_CFG_END - 2);

		eep_config.serial_number_word1 =
		    AdvReadEEPWord(iop_base, ADV_EEP_DVC_CFG_END - 3);

		AdvSet3550EEPConfig(iop_base, &eep_config);
	पूर्ण
	/*
	 * Set ASC_DVC_VAR and ASC_DVC_CFG variables from the
	 * EEPROM configuration that was पढ़ो.
	 *
	 * This is the mapping of EEPROM fields to Adv Library fields.
	 */
	asc_dvc->wdtr_able = eep_config.wdtr_able;
	asc_dvc->sdtr_able = eep_config.sdtr_able;
	asc_dvc->ultra_able = eep_config.ultra_able;
	asc_dvc->tagqng_able = eep_config.tagqng_able;
	asc_dvc->cfg->disc_enable = eep_config.disc_enable;
	asc_dvc->max_host_qng = eep_config.max_host_qng;
	asc_dvc->max_dvc_qng = eep_config.max_dvc_qng;
	asc_dvc->chip_scsi_id = (eep_config.adapter_scsi_id & ADV_MAX_TID);
	asc_dvc->start_motor = eep_config.start_motor;
	asc_dvc->scsi_reset_रुको = eep_config.scsi_reset_delay;
	asc_dvc->bios_ctrl = eep_config.bios_ctrl;
	asc_dvc->no_scam = eep_config.scam_tolerant;
	asc_dvc->cfg->serial1 = eep_config.serial_number_word1;
	asc_dvc->cfg->serial2 = eep_config.serial_number_word2;
	asc_dvc->cfg->serial3 = eep_config.serial_number_word3;

	/*
	 * Set the host maximum queuing (max. 253, min. 16) and the per device
	 * maximum queuing (max. 63, min. 4).
	 */
	अगर (eep_config.max_host_qng > ASC_DEF_MAX_HOST_QNG) अणु
		eep_config.max_host_qng = ASC_DEF_MAX_HOST_QNG;
	पूर्ण अन्यथा अगर (eep_config.max_host_qng < ASC_DEF_MIN_HOST_QNG) अणु
		/* If the value is zero, assume it is uninitialized. */
		अगर (eep_config.max_host_qng == 0) अणु
			eep_config.max_host_qng = ASC_DEF_MAX_HOST_QNG;
		पूर्ण अन्यथा अणु
			eep_config.max_host_qng = ASC_DEF_MIN_HOST_QNG;
		पूर्ण
	पूर्ण

	अगर (eep_config.max_dvc_qng > ASC_DEF_MAX_DVC_QNG) अणु
		eep_config.max_dvc_qng = ASC_DEF_MAX_DVC_QNG;
	पूर्ण अन्यथा अगर (eep_config.max_dvc_qng < ASC_DEF_MIN_DVC_QNG) अणु
		/* If the value is zero, assume it is uninitialized. */
		अगर (eep_config.max_dvc_qng == 0) अणु
			eep_config.max_dvc_qng = ASC_DEF_MAX_DVC_QNG;
		पूर्ण अन्यथा अणु
			eep_config.max_dvc_qng = ASC_DEF_MIN_DVC_QNG;
		पूर्ण
	पूर्ण

	/*
	 * If 'max_dvc_qng' is greater than 'max_host_qng', then
	 * set 'max_dvc_qng' to 'max_host_qng'.
	 */
	अगर (eep_config.max_dvc_qng > eep_config.max_host_qng) अणु
		eep_config.max_dvc_qng = eep_config.max_host_qng;
	पूर्ण

	/*
	 * Set ADV_DVC_VAR 'max_host_qng' and ADV_DVC_VAR 'max_dvc_qng'
	 * values based on possibly adjusted EEPROM values.
	 */
	asc_dvc->max_host_qng = eep_config.max_host_qng;
	asc_dvc->max_dvc_qng = eep_config.max_dvc_qng;

	/*
	 * If the EEPROM 'termination' field is set to स्वतःmatic (0), then set
	 * the ADV_DVC_CFG 'termination' field to स्वतःmatic also.
	 *
	 * If the termination is specअगरied with a non-zero 'termination'
	 * value check that a legal value is set and set the ADV_DVC_CFG
	 * 'termination' field appropriately.
	 */
	अगर (eep_config.termination == 0) अणु
		asc_dvc->cfg->termination = 0;	/* स्वतः termination */
	पूर्ण अन्यथा अणु
		/* Enable manual control with low off / high off. */
		अगर (eep_config.termination == 1) अणु
			asc_dvc->cfg->termination = TERM_CTL_SEL;

			/* Enable manual control with low off / high on. */
		पूर्ण अन्यथा अगर (eep_config.termination == 2) अणु
			asc_dvc->cfg->termination = TERM_CTL_SEL | TERM_CTL_H;

			/* Enable manual control with low on / high on. */
		पूर्ण अन्यथा अगर (eep_config.termination == 3) अणु
			asc_dvc->cfg->termination =
			    TERM_CTL_SEL | TERM_CTL_H | TERM_CTL_L;
		पूर्ण अन्यथा अणु
			/*
			 * The EEPROM 'termination' field contains a bad value. Use
			 * स्वतःmatic termination instead.
			 */
			asc_dvc->cfg->termination = 0;
			warn_code |= ASC_WARN_EEPROM_TERMINATION;
		पूर्ण
	पूर्ण

	वापस warn_code;
पूर्ण

/*
 * Read the board's EEPROM configuration. Set fields in ADV_DVC_VAR and
 * ADV_DVC_CFG based on the EEPROM settings. The chip is stopped जबतक
 * all of this is करोne.
 *
 * On failure set the ADV_DVC_VAR field 'err_code' and वापस ADV_ERROR.
 *
 * For a non-fatal error वापस a warning code. If there are no warnings
 * then 0 is वापसed.
 *
 * Note: Chip is stopped on entry.
 */
अटल पूर्णांक AdvInitFrom38C0800EEP(ADV_DVC_VAR *asc_dvc)
अणु
	AdvPortAddr iop_base;
	uलघु warn_code;
	ADVEEP_38C0800_CONFIG eep_config;
	uअक्षर tid, termination;
	uलघु sdtr_speed = 0;

	iop_base = asc_dvc->iop_base;

	warn_code = 0;

	/*
	 * Read the board's EEPROM configuration.
	 *
	 * Set शेष values अगर a bad checksum is found.
	 */
	अगर (AdvGet38C0800EEPConfig(iop_base, &eep_config) !=
	    eep_config.check_sum) अणु
		warn_code |= ASC_WARN_EEPROM_CHKSUM;

		/*
		 * Set EEPROM शेष values.
		 */
		स_नकल(&eep_config, &Default_38C0800_EEPROM_Config,
			माप(ADVEEP_38C0800_CONFIG));

		/*
		 * Assume the 6 byte board serial number that was पढ़ो from
		 * EEPROM is correct even अगर the EEPROM checksum failed.
		 */
		eep_config.serial_number_word3 =
		    AdvReadEEPWord(iop_base, ADV_EEP_DVC_CFG_END - 1);

		eep_config.serial_number_word2 =
		    AdvReadEEPWord(iop_base, ADV_EEP_DVC_CFG_END - 2);

		eep_config.serial_number_word1 =
		    AdvReadEEPWord(iop_base, ADV_EEP_DVC_CFG_END - 3);

		AdvSet38C0800EEPConfig(iop_base, &eep_config);
	पूर्ण
	/*
	 * Set ADV_DVC_VAR and ADV_DVC_CFG variables from the
	 * EEPROM configuration that was पढ़ो.
	 *
	 * This is the mapping of EEPROM fields to Adv Library fields.
	 */
	asc_dvc->wdtr_able = eep_config.wdtr_able;
	asc_dvc->sdtr_speed1 = eep_config.sdtr_speed1;
	asc_dvc->sdtr_speed2 = eep_config.sdtr_speed2;
	asc_dvc->sdtr_speed3 = eep_config.sdtr_speed3;
	asc_dvc->sdtr_speed4 = eep_config.sdtr_speed4;
	asc_dvc->tagqng_able = eep_config.tagqng_able;
	asc_dvc->cfg->disc_enable = eep_config.disc_enable;
	asc_dvc->max_host_qng = eep_config.max_host_qng;
	asc_dvc->max_dvc_qng = eep_config.max_dvc_qng;
	asc_dvc->chip_scsi_id = (eep_config.adapter_scsi_id & ADV_MAX_TID);
	asc_dvc->start_motor = eep_config.start_motor;
	asc_dvc->scsi_reset_रुको = eep_config.scsi_reset_delay;
	asc_dvc->bios_ctrl = eep_config.bios_ctrl;
	asc_dvc->no_scam = eep_config.scam_tolerant;
	asc_dvc->cfg->serial1 = eep_config.serial_number_word1;
	asc_dvc->cfg->serial2 = eep_config.serial_number_word2;
	asc_dvc->cfg->serial3 = eep_config.serial_number_word3;

	/*
	 * For every Target ID अगर any of its 'sdtr_speed[1234]' bits
	 * are set, then set an 'sdtr_able' bit क्रम it.
	 */
	asc_dvc->sdtr_able = 0;
	क्रम (tid = 0; tid <= ADV_MAX_TID; tid++) अणु
		अगर (tid == 0) अणु
			sdtr_speed = asc_dvc->sdtr_speed1;
		पूर्ण अन्यथा अगर (tid == 4) अणु
			sdtr_speed = asc_dvc->sdtr_speed2;
		पूर्ण अन्यथा अगर (tid == 8) अणु
			sdtr_speed = asc_dvc->sdtr_speed3;
		पूर्ण अन्यथा अगर (tid == 12) अणु
			sdtr_speed = asc_dvc->sdtr_speed4;
		पूर्ण
		अगर (sdtr_speed & ADV_MAX_TID) अणु
			asc_dvc->sdtr_able |= (1 << tid);
		पूर्ण
		sdtr_speed >>= 4;
	पूर्ण

	/*
	 * Set the host maximum queuing (max. 253, min. 16) and the per device
	 * maximum queuing (max. 63, min. 4).
	 */
	अगर (eep_config.max_host_qng > ASC_DEF_MAX_HOST_QNG) अणु
		eep_config.max_host_qng = ASC_DEF_MAX_HOST_QNG;
	पूर्ण अन्यथा अगर (eep_config.max_host_qng < ASC_DEF_MIN_HOST_QNG) अणु
		/* If the value is zero, assume it is uninitialized. */
		अगर (eep_config.max_host_qng == 0) अणु
			eep_config.max_host_qng = ASC_DEF_MAX_HOST_QNG;
		पूर्ण अन्यथा अणु
			eep_config.max_host_qng = ASC_DEF_MIN_HOST_QNG;
		पूर्ण
	पूर्ण

	अगर (eep_config.max_dvc_qng > ASC_DEF_MAX_DVC_QNG) अणु
		eep_config.max_dvc_qng = ASC_DEF_MAX_DVC_QNG;
	पूर्ण अन्यथा अगर (eep_config.max_dvc_qng < ASC_DEF_MIN_DVC_QNG) अणु
		/* If the value is zero, assume it is uninitialized. */
		अगर (eep_config.max_dvc_qng == 0) अणु
			eep_config.max_dvc_qng = ASC_DEF_MAX_DVC_QNG;
		पूर्ण अन्यथा अणु
			eep_config.max_dvc_qng = ASC_DEF_MIN_DVC_QNG;
		पूर्ण
	पूर्ण

	/*
	 * If 'max_dvc_qng' is greater than 'max_host_qng', then
	 * set 'max_dvc_qng' to 'max_host_qng'.
	 */
	अगर (eep_config.max_dvc_qng > eep_config.max_host_qng) अणु
		eep_config.max_dvc_qng = eep_config.max_host_qng;
	पूर्ण

	/*
	 * Set ADV_DVC_VAR 'max_host_qng' and ADV_DVC_VAR 'max_dvc_qng'
	 * values based on possibly adjusted EEPROM values.
	 */
	asc_dvc->max_host_qng = eep_config.max_host_qng;
	asc_dvc->max_dvc_qng = eep_config.max_dvc_qng;

	/*
	 * If the EEPROM 'termination' field is set to स्वतःmatic (0), then set
	 * the ADV_DVC_CFG 'termination' field to स्वतःmatic also.
	 *
	 * If the termination is specअगरied with a non-zero 'termination'
	 * value check that a legal value is set and set the ADV_DVC_CFG
	 * 'termination' field appropriately.
	 */
	अगर (eep_config.termination_se == 0) अणु
		termination = 0;	/* स्वतः termination क्रम SE */
	पूर्ण अन्यथा अणु
		/* Enable manual control with low off / high off. */
		अगर (eep_config.termination_se == 1) अणु
			termination = 0;

			/* Enable manual control with low off / high on. */
		पूर्ण अन्यथा अगर (eep_config.termination_se == 2) अणु
			termination = TERM_SE_HI;

			/* Enable manual control with low on / high on. */
		पूर्ण अन्यथा अगर (eep_config.termination_se == 3) अणु
			termination = TERM_SE;
		पूर्ण अन्यथा अणु
			/*
			 * The EEPROM 'termination_se' field contains a bad value.
			 * Use स्वतःmatic termination instead.
			 */
			termination = 0;
			warn_code |= ASC_WARN_EEPROM_TERMINATION;
		पूर्ण
	पूर्ण

	अगर (eep_config.termination_lvd == 0) अणु
		asc_dvc->cfg->termination = termination;	/* स्वतः termination क्रम LVD */
	पूर्ण अन्यथा अणु
		/* Enable manual control with low off / high off. */
		अगर (eep_config.termination_lvd == 1) अणु
			asc_dvc->cfg->termination = termination;

			/* Enable manual control with low off / high on. */
		पूर्ण अन्यथा अगर (eep_config.termination_lvd == 2) अणु
			asc_dvc->cfg->termination = termination | TERM_LVD_HI;

			/* Enable manual control with low on / high on. */
		पूर्ण अन्यथा अगर (eep_config.termination_lvd == 3) अणु
			asc_dvc->cfg->termination = termination | TERM_LVD;
		पूर्ण अन्यथा अणु
			/*
			 * The EEPROM 'termination_lvd' field contains a bad value.
			 * Use स्वतःmatic termination instead.
			 */
			asc_dvc->cfg->termination = termination;
			warn_code |= ASC_WARN_EEPROM_TERMINATION;
		पूर्ण
	पूर्ण

	वापस warn_code;
पूर्ण

/*
 * Read the board's EEPROM configuration. Set fields in ASC_DVC_VAR and
 * ASC_DVC_CFG based on the EEPROM settings. The chip is stopped जबतक
 * all of this is करोne.
 *
 * On failure set the ASC_DVC_VAR field 'err_code' and वापस ADV_ERROR.
 *
 * For a non-fatal error वापस a warning code. If there are no warnings
 * then 0 is वापसed.
 *
 * Note: Chip is stopped on entry.
 */
अटल पूर्णांक AdvInitFrom38C1600EEP(ADV_DVC_VAR *asc_dvc)
अणु
	AdvPortAddr iop_base;
	uलघु warn_code;
	ADVEEP_38C1600_CONFIG eep_config;
	uअक्षर tid, termination;
	uलघु sdtr_speed = 0;

	iop_base = asc_dvc->iop_base;

	warn_code = 0;

	/*
	 * Read the board's EEPROM configuration.
	 *
	 * Set शेष values अगर a bad checksum is found.
	 */
	अगर (AdvGet38C1600EEPConfig(iop_base, &eep_config) !=
	    eep_config.check_sum) अणु
		काष्ठा pci_dev *pdev = adv_dvc_to_pdev(asc_dvc);
		warn_code |= ASC_WARN_EEPROM_CHKSUM;

		/*
		 * Set EEPROM शेष values.
		 */
		स_नकल(&eep_config, &Default_38C1600_EEPROM_Config,
			माप(ADVEEP_38C1600_CONFIG));

		अगर (PCI_FUNC(pdev->devfn) != 0) अणु
			u8 पूर्णांकs;
			/*
			 * Disable Bit 14 (BIOS_ENABLE) to fix SPARC Ultra 60
			 * and old Mac प्रणाली booting problem. The Expansion
			 * ROM must be disabled in Function 1 क्रम these प्रणालीs
			 */
			eep_config.cfg_lsw &= ~ADV_EEPROM_BIOS_ENABLE;
			/*
			 * Clear the INTAB (bit 11) अगर the GPIO 0 input
			 * indicates the Function 1 पूर्णांकerrupt line is wired
			 * to INTB.
			 *
			 * Set/Clear Bit 11 (INTAB) from the GPIO bit 0 input:
			 *   1 - Function 1 पूर्णांकerrupt line wired to INT A.
			 *   0 - Function 1 पूर्णांकerrupt line wired to INT B.
			 *
			 * Note: Function 0 is always wired to INTA.
			 * Put all 5 GPIO bits in input mode and then पढ़ो
			 * their input values.
			 */
			AdvWriteByteRegister(iop_base, IOPB_GPIO_CNTL, 0);
			पूर्णांकs = AdvReadByteRegister(iop_base, IOPB_GPIO_DATA);
			अगर ((पूर्णांकs & 0x01) == 0)
				eep_config.cfg_lsw &= ~ADV_EEPROM_INTAB;
		पूर्ण

		/*
		 * Assume the 6 byte board serial number that was पढ़ो from
		 * EEPROM is correct even अगर the EEPROM checksum failed.
		 */
		eep_config.serial_number_word3 =
			AdvReadEEPWord(iop_base, ADV_EEP_DVC_CFG_END - 1);
		eep_config.serial_number_word2 =
			AdvReadEEPWord(iop_base, ADV_EEP_DVC_CFG_END - 2);
		eep_config.serial_number_word1 =
			AdvReadEEPWord(iop_base, ADV_EEP_DVC_CFG_END - 3);

		AdvSet38C1600EEPConfig(iop_base, &eep_config);
	पूर्ण

	/*
	 * Set ASC_DVC_VAR and ASC_DVC_CFG variables from the
	 * EEPROM configuration that was पढ़ो.
	 *
	 * This is the mapping of EEPROM fields to Adv Library fields.
	 */
	asc_dvc->wdtr_able = eep_config.wdtr_able;
	asc_dvc->sdtr_speed1 = eep_config.sdtr_speed1;
	asc_dvc->sdtr_speed2 = eep_config.sdtr_speed2;
	asc_dvc->sdtr_speed3 = eep_config.sdtr_speed3;
	asc_dvc->sdtr_speed4 = eep_config.sdtr_speed4;
	asc_dvc->ppr_able = 0;
	asc_dvc->tagqng_able = eep_config.tagqng_able;
	asc_dvc->cfg->disc_enable = eep_config.disc_enable;
	asc_dvc->max_host_qng = eep_config.max_host_qng;
	asc_dvc->max_dvc_qng = eep_config.max_dvc_qng;
	asc_dvc->chip_scsi_id = (eep_config.adapter_scsi_id & ASC_MAX_TID);
	asc_dvc->start_motor = eep_config.start_motor;
	asc_dvc->scsi_reset_रुको = eep_config.scsi_reset_delay;
	asc_dvc->bios_ctrl = eep_config.bios_ctrl;
	asc_dvc->no_scam = eep_config.scam_tolerant;

	/*
	 * For every Target ID अगर any of its 'sdtr_speed[1234]' bits
	 * are set, then set an 'sdtr_able' bit क्रम it.
	 */
	asc_dvc->sdtr_able = 0;
	क्रम (tid = 0; tid <= ASC_MAX_TID; tid++) अणु
		अगर (tid == 0) अणु
			sdtr_speed = asc_dvc->sdtr_speed1;
		पूर्ण अन्यथा अगर (tid == 4) अणु
			sdtr_speed = asc_dvc->sdtr_speed2;
		पूर्ण अन्यथा अगर (tid == 8) अणु
			sdtr_speed = asc_dvc->sdtr_speed3;
		पूर्ण अन्यथा अगर (tid == 12) अणु
			sdtr_speed = asc_dvc->sdtr_speed4;
		पूर्ण
		अगर (sdtr_speed & ASC_MAX_TID) अणु
			asc_dvc->sdtr_able |= (1 << tid);
		पूर्ण
		sdtr_speed >>= 4;
	पूर्ण

	/*
	 * Set the host maximum queuing (max. 253, min. 16) and the per device
	 * maximum queuing (max. 63, min. 4).
	 */
	अगर (eep_config.max_host_qng > ASC_DEF_MAX_HOST_QNG) अणु
		eep_config.max_host_qng = ASC_DEF_MAX_HOST_QNG;
	पूर्ण अन्यथा अगर (eep_config.max_host_qng < ASC_DEF_MIN_HOST_QNG) अणु
		/* If the value is zero, assume it is uninitialized. */
		अगर (eep_config.max_host_qng == 0) अणु
			eep_config.max_host_qng = ASC_DEF_MAX_HOST_QNG;
		पूर्ण अन्यथा अणु
			eep_config.max_host_qng = ASC_DEF_MIN_HOST_QNG;
		पूर्ण
	पूर्ण

	अगर (eep_config.max_dvc_qng > ASC_DEF_MAX_DVC_QNG) अणु
		eep_config.max_dvc_qng = ASC_DEF_MAX_DVC_QNG;
	पूर्ण अन्यथा अगर (eep_config.max_dvc_qng < ASC_DEF_MIN_DVC_QNG) अणु
		/* If the value is zero, assume it is uninitialized. */
		अगर (eep_config.max_dvc_qng == 0) अणु
			eep_config.max_dvc_qng = ASC_DEF_MAX_DVC_QNG;
		पूर्ण अन्यथा अणु
			eep_config.max_dvc_qng = ASC_DEF_MIN_DVC_QNG;
		पूर्ण
	पूर्ण

	/*
	 * If 'max_dvc_qng' is greater than 'max_host_qng', then
	 * set 'max_dvc_qng' to 'max_host_qng'.
	 */
	अगर (eep_config.max_dvc_qng > eep_config.max_host_qng) अणु
		eep_config.max_dvc_qng = eep_config.max_host_qng;
	पूर्ण

	/*
	 * Set ASC_DVC_VAR 'max_host_qng' and ASC_DVC_VAR 'max_dvc_qng'
	 * values based on possibly adjusted EEPROM values.
	 */
	asc_dvc->max_host_qng = eep_config.max_host_qng;
	asc_dvc->max_dvc_qng = eep_config.max_dvc_qng;

	/*
	 * If the EEPROM 'termination' field is set to स्वतःmatic (0), then set
	 * the ASC_DVC_CFG 'termination' field to स्वतःmatic also.
	 *
	 * If the termination is specअगरied with a non-zero 'termination'
	 * value check that a legal value is set and set the ASC_DVC_CFG
	 * 'termination' field appropriately.
	 */
	अगर (eep_config.termination_se == 0) अणु
		termination = 0;	/* स्वतः termination क्रम SE */
	पूर्ण अन्यथा अणु
		/* Enable manual control with low off / high off. */
		अगर (eep_config.termination_se == 1) अणु
			termination = 0;

			/* Enable manual control with low off / high on. */
		पूर्ण अन्यथा अगर (eep_config.termination_se == 2) अणु
			termination = TERM_SE_HI;

			/* Enable manual control with low on / high on. */
		पूर्ण अन्यथा अगर (eep_config.termination_se == 3) अणु
			termination = TERM_SE;
		पूर्ण अन्यथा अणु
			/*
			 * The EEPROM 'termination_se' field contains a bad value.
			 * Use स्वतःmatic termination instead.
			 */
			termination = 0;
			warn_code |= ASC_WARN_EEPROM_TERMINATION;
		पूर्ण
	पूर्ण

	अगर (eep_config.termination_lvd == 0) अणु
		asc_dvc->cfg->termination = termination;	/* स्वतः termination क्रम LVD */
	पूर्ण अन्यथा अणु
		/* Enable manual control with low off / high off. */
		अगर (eep_config.termination_lvd == 1) अणु
			asc_dvc->cfg->termination = termination;

			/* Enable manual control with low off / high on. */
		पूर्ण अन्यथा अगर (eep_config.termination_lvd == 2) अणु
			asc_dvc->cfg->termination = termination | TERM_LVD_HI;

			/* Enable manual control with low on / high on. */
		पूर्ण अन्यथा अगर (eep_config.termination_lvd == 3) अणु
			asc_dvc->cfg->termination = termination | TERM_LVD;
		पूर्ण अन्यथा अणु
			/*
			 * The EEPROM 'termination_lvd' field contains a bad value.
			 * Use स्वतःmatic termination instead.
			 */
			asc_dvc->cfg->termination = termination;
			warn_code |= ASC_WARN_EEPROM_TERMINATION;
		पूर्ण
	पूर्ण

	वापस warn_code;
पूर्ण

/*
 * Initialize the ADV_DVC_VAR काष्ठाure.
 *
 * On failure set the ADV_DVC_VAR field 'err_code' and वापस ADV_ERROR.
 *
 * For a non-fatal error वापस a warning code. If there are no warnings
 * then 0 is वापसed.
 */
अटल पूर्णांक AdvInitGetConfig(काष्ठा pci_dev *pdev, काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *board = shost_priv(shost);
	ADV_DVC_VAR *asc_dvc = &board->dvc_var.adv_dvc_var;
	अचिन्हित लघु warn_code = 0;
	AdvPortAddr iop_base = asc_dvc->iop_base;
	u16 cmd;
	पूर्णांक status;

	asc_dvc->err_code = 0;

	/*
	 * Save the state of the PCI Configuration Command Register
	 * "Parity Error Response Control" Bit. If the bit is clear (0),
	 * in AdvInitAsc3550/38C0800Driver() tell the microcode to ignore
	 * DMA parity errors.
	 */
	asc_dvc->cfg->control_flag = 0;
	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
	अगर ((cmd & PCI_COMMAND_PARITY) == 0)
		asc_dvc->cfg->control_flag |= CONTROL_FLAG_IGNORE_PERR;

	asc_dvc->cfg->chip_version =
	    AdvGetChipVersion(iop_base, asc_dvc->bus_type);

	ASC_DBG(1, "iopb_chip_id_1: 0x%x 0x%x\n",
		 (uलघु)AdvReadByteRegister(iop_base, IOPB_CHIP_ID_1),
		 (uलघु)ADV_CHIP_ID_BYTE);

	ASC_DBG(1, "iopw_chip_id_0: 0x%x 0x%x\n",
		 (uलघु)AdvReadWordRegister(iop_base, IOPW_CHIP_ID_0),
		 (uलघु)ADV_CHIP_ID_WORD);

	/*
	 * Reset the chip to start and allow रेजिस्टर ग_लिखोs.
	 */
	अगर (AdvFindSignature(iop_base) == 0) अणु
		asc_dvc->err_code = ASC_IERR_BAD_SIGNATURE;
		वापस ADV_ERROR;
	पूर्ण अन्यथा अणु
		/*
		 * The caller must set 'chip_type' to a valid setting.
		 */
		अगर (asc_dvc->chip_type != ADV_CHIP_ASC3550 &&
		    asc_dvc->chip_type != ADV_CHIP_ASC38C0800 &&
		    asc_dvc->chip_type != ADV_CHIP_ASC38C1600) अणु
			asc_dvc->err_code |= ASC_IERR_BAD_CHIPTYPE;
			वापस ADV_ERROR;
		पूर्ण

		/*
		 * Reset Chip.
		 */
		AdvWriteWordRegister(iop_base, IOPW_CTRL_REG,
				     ADV_CTRL_REG_CMD_RESET);
		mdelay(100);
		AdvWriteWordRegister(iop_base, IOPW_CTRL_REG,
				     ADV_CTRL_REG_CMD_WR_IO_REG);

		अगर (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) अणु
			status = AdvInitFrom38C1600EEP(asc_dvc);
		पूर्ण अन्यथा अगर (asc_dvc->chip_type == ADV_CHIP_ASC38C0800) अणु
			status = AdvInitFrom38C0800EEP(asc_dvc);
		पूर्ण अन्यथा अणु
			status = AdvInitFrom3550EEP(asc_dvc);
		पूर्ण
		warn_code |= status;
	पूर्ण

	अगर (warn_code != 0)
		shost_prपूर्णांकk(KERN_WARNING, shost, "warning: 0x%x\n", warn_code);

	अगर (asc_dvc->err_code)
		shost_prपूर्णांकk(KERN_ERR, shost, "error code 0x%x\n",
				asc_dvc->err_code);

	वापस asc_dvc->err_code;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा scsi_host_ढाँचा advansys_ढाँचा = अणु
	.proc_name = DRV_NAME,
#अगर_घोषित CONFIG_PROC_FS
	.show_info = advansys_show_info,
#पूर्ण_अगर
	.name = DRV_NAME,
	.info = advansys_info,
	.queuecommand = advansys_queuecommand,
	.eh_host_reset_handler = advansys_reset,
	.bios_param = advansys_biosparam,
	.slave_configure = advansys_slave_configure,
पूर्ण;

अटल पूर्णांक advansys_wide_init_chip(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *board = shost_priv(shost);
	काष्ठा adv_dvc_var *adv_dvc = &board->dvc_var.adv_dvc_var;
	माप_प्रकार sgblk_pool_size;
	पूर्णांक warn_code, err_code;

	/*
	 * Allocate buffer carrier काष्ठाures. The total size
	 * is about 8 KB, so allocate all at once.
	 */
	adv_dvc->carrier = dma_alloc_coherent(board->dev,
		ADV_CARRIER_बफ_मानE, &adv_dvc->carrier_addr, GFP_KERNEL);
	ASC_DBG(1, "carrier 0x%p\n", adv_dvc->carrier);

	अगर (!adv_dvc->carrier)
		जाओ kदो_स्मृति_failed;

	/*
	 * Allocate up to 'max_host_qng' request काष्ठाures क्रम the Wide
	 * board. The total size is about 16 KB, so allocate all at once.
	 * If the allocation fails decrement and try again.
	 */
	board->adv_reqp_size = adv_dvc->max_host_qng * माप(adv_req_t);
	अगर (board->adv_reqp_size & 0x1f) अणु
		ASC_DBG(1, "unaligned reqp %lu bytes\n", माप(adv_req_t));
		board->adv_reqp_size = ADV_32BALIGN(board->adv_reqp_size);
	पूर्ण
	board->adv_reqp = dma_alloc_coherent(board->dev, board->adv_reqp_size,
		&board->adv_reqp_addr, GFP_KERNEL);

	अगर (!board->adv_reqp)
		जाओ kदो_स्मृति_failed;

	ASC_DBG(1, "reqp 0x%p, req_cnt %d, bytes %lu\n", board->adv_reqp,
		adv_dvc->max_host_qng, board->adv_reqp_size);

	/*
	 * Allocate up to ADV_TOT_SG_BLOCK request काष्ठाures क्रम
	 * the Wide board. Each काष्ठाure is about 136 bytes.
	 */
	sgblk_pool_size = माप(adv_sgblk_t) * ADV_TOT_SG_BLOCK;
	board->adv_sgblk_pool = dma_pool_create("adv_sgblk", board->dev,
						sgblk_pool_size, 32, 0);

	ASC_DBG(1, "sg_cnt %d * %lu = %lu bytes\n", ADV_TOT_SG_BLOCK,
		माप(adv_sgblk_t), sgblk_pool_size);

	अगर (!board->adv_sgblk_pool)
		जाओ kदो_स्मृति_failed;

	अगर (adv_dvc->chip_type == ADV_CHIP_ASC3550) अणु
		ASC_DBG(2, "AdvInitAsc3550Driver()\n");
		warn_code = AdvInitAsc3550Driver(adv_dvc);
	पूर्ण अन्यथा अगर (adv_dvc->chip_type == ADV_CHIP_ASC38C0800) अणु
		ASC_DBG(2, "AdvInitAsc38C0800Driver()\n");
		warn_code = AdvInitAsc38C0800Driver(adv_dvc);
	पूर्ण अन्यथा अणु
		ASC_DBG(2, "AdvInitAsc38C1600Driver()\n");
		warn_code = AdvInitAsc38C1600Driver(adv_dvc);
	पूर्ण
	err_code = adv_dvc->err_code;

	अगर (warn_code || err_code) अणु
		shost_prपूर्णांकk(KERN_WARNING, shost, "error: warn 0x%x, error "
			"0x%x\n", warn_code, err_code);
	पूर्ण

	जाओ निकास;

 kदो_स्मृति_failed:
	shost_prपूर्णांकk(KERN_ERR, shost, "error: kmalloc() failed\n");
	err_code = ADV_ERROR;
 निकास:
	वापस err_code;
पूर्ण

अटल व्योम advansys_wide_मुक्त_mem(काष्ठा asc_board *board)
अणु
	काष्ठा adv_dvc_var *adv_dvc = &board->dvc_var.adv_dvc_var;

	अगर (adv_dvc->carrier) अणु
		dma_मुक्त_coherent(board->dev, ADV_CARRIER_बफ_मानE,
				  adv_dvc->carrier, adv_dvc->carrier_addr);
		adv_dvc->carrier = शून्य;
	पूर्ण
	अगर (board->adv_reqp) अणु
		dma_मुक्त_coherent(board->dev, board->adv_reqp_size,
				  board->adv_reqp, board->adv_reqp_addr);
		board->adv_reqp = शून्य;
	पूर्ण
	अगर (board->adv_sgblk_pool) अणु
		dma_pool_destroy(board->adv_sgblk_pool);
		board->adv_sgblk_pool = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक advansys_board_found(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक iop,
				पूर्णांक bus_type)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा asc_board *boardp = shost_priv(shost);
	ASC_DVC_VAR *asc_dvc_varp = शून्य;
	ADV_DVC_VAR *adv_dvc_varp = शून्य;
	पूर्णांक share_irq, warn_code, ret;

	pdev = (bus_type == ASC_IS_PCI) ? to_pci_dev(boardp->dev) : शून्य;

	अगर (ASC_NARROW_BOARD(boardp)) अणु
		ASC_DBG(1, "narrow board\n");
		asc_dvc_varp = &boardp->dvc_var.asc_dvc_var;
		asc_dvc_varp->bus_type = bus_type;
		asc_dvc_varp->drv_ptr = boardp;
		asc_dvc_varp->cfg = &boardp->dvc_cfg.asc_dvc_cfg;
		asc_dvc_varp->iop_base = iop;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_PCI
		adv_dvc_varp = &boardp->dvc_var.adv_dvc_var;
		adv_dvc_varp->drv_ptr = boardp;
		adv_dvc_varp->cfg = &boardp->dvc_cfg.adv_dvc_cfg;
		अगर (pdev->device == PCI_DEVICE_ID_ASP_ABP940UW) अणु
			ASC_DBG(1, "wide board ASC-3550\n");
			adv_dvc_varp->chip_type = ADV_CHIP_ASC3550;
		पूर्ण अन्यथा अगर (pdev->device == PCI_DEVICE_ID_38C0800_REV1) अणु
			ASC_DBG(1, "wide board ASC-38C0800\n");
			adv_dvc_varp->chip_type = ADV_CHIP_ASC38C0800;
		पूर्ण अन्यथा अणु
			ASC_DBG(1, "wide board ASC-38C1600\n");
			adv_dvc_varp->chip_type = ADV_CHIP_ASC38C1600;
		पूर्ण

		boardp->asc_n_io_port = pci_resource_len(pdev, 1);
		boardp->ioremap_addr = pci_ioremap_bar(pdev, 1);
		अगर (!boardp->ioremap_addr) अणु
			shost_prपूर्णांकk(KERN_ERR, shost, "ioremap(%lx, %d) "
					"returned NULL\n",
					(दीर्घ)pci_resource_start(pdev, 1),
					boardp->asc_n_io_port);
			ret = -ENODEV;
			जाओ err_shost;
		पूर्ण
		adv_dvc_varp->iop_base = (AdvPortAddr)boardp->ioremap_addr;
		ASC_DBG(1, "iop_base: 0x%p\n", adv_dvc_varp->iop_base);

		/*
		 * Even though it isn't used to access wide boards, other
		 * than क्रम the debug line below, save I/O Port address so
		 * that it can be reported.
		 */
		boardp->ioport = iop;

		ASC_DBG(1, "iopb_chip_id_1 0x%x, iopw_chip_id_0 0x%x\n",
				(uलघु)inp(iop + 1), (uलघु)inpw(iop));
#पूर्ण_अगर /* CONFIG_PCI */
	पूर्ण

	अगर (ASC_NARROW_BOARD(boardp)) अणु
		/*
		 * Set the board bus type and PCI IRQ beक्रमe
		 * calling AscInitGetConfig().
		 */
		चयन (asc_dvc_varp->bus_type) अणु
#अगर_घोषित CONFIG_ISA
		हाल ASC_IS_VL:
			share_irq = 0;
			अवरोध;
		हाल ASC_IS_EISA:
			share_irq = IRQF_SHARED;
			अवरोध;
#पूर्ण_अगर /* CONFIG_ISA */
#अगर_घोषित CONFIG_PCI
		हाल ASC_IS_PCI:
			share_irq = IRQF_SHARED;
			अवरोध;
#पूर्ण_अगर /* CONFIG_PCI */
		शेष:
			shost_prपूर्णांकk(KERN_ERR, shost, "unknown adapter type: "
					"%d\n", asc_dvc_varp->bus_type);
			share_irq = 0;
			अवरोध;
		पूर्ण

		/*
		 * NOTE: AscInitGetConfig() may change the board's
		 * bus_type value. The bus_type value should no
		 * दीर्घer be used. If the bus_type field must be
		 * referenced only use the bit-wise AND चालक "&".
		 */
		ASC_DBG(2, "AscInitGetConfig()\n");
		ret = AscInitGetConfig(shost) ? -ENODEV : 0;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_PCI
		/*
		 * For Wide boards set PCI inक्रमmation beक्रमe calling
		 * AdvInitGetConfig().
		 */
		share_irq = IRQF_SHARED;
		ASC_DBG(2, "AdvInitGetConfig()\n");

		ret = AdvInitGetConfig(pdev, shost) ? -ENODEV : 0;
#अन्यथा
		share_irq = 0;
		ret = -ENODEV;
#पूर्ण_अगर /* CONFIG_PCI */
	पूर्ण

	अगर (ret)
		जाओ err_unmap;

	/*
	 * Save the EEPROM configuration so that it can be displayed
	 * from /proc/scsi/advansys/[0...].
	 */
	अगर (ASC_NARROW_BOARD(boardp)) अणु

		ASCEEP_CONFIG *ep;

		/*
		 * Set the adapter's target id bit in the 'init_tidmask' field.
		 */
		boardp->init_tidmask |=
		    ADV_TID_TO_TIDMASK(asc_dvc_varp->cfg->chip_scsi_id);

		/*
		 * Save EEPROM settings क्रम the board.
		 */
		ep = &boardp->eep_config.asc_eep;

		ep->init_sdtr = asc_dvc_varp->cfg->sdtr_enable;
		ep->disc_enable = asc_dvc_varp->cfg->disc_enable;
		ep->use_cmd_qng = asc_dvc_varp->cfg->cmd_qng_enabled;
		ASC_EEP_SET_DMA_SPD(ep, ASC_DEF_ISA_DMA_SPEED);
		ep->start_motor = asc_dvc_varp->start_motor;
		ep->cntl = asc_dvc_varp->dvc_cntl;
		ep->no_scam = asc_dvc_varp->no_scam;
		ep->max_total_qng = asc_dvc_varp->max_total_qng;
		ASC_EEP_SET_CHIP_ID(ep, asc_dvc_varp->cfg->chip_scsi_id);
		/* 'max_tag_qng' is set to the same value क्रम every device. */
		ep->max_tag_qng = asc_dvc_varp->cfg->max_tag_qng[0];
		ep->adapter_info[0] = asc_dvc_varp->cfg->adapter_info[0];
		ep->adapter_info[1] = asc_dvc_varp->cfg->adapter_info[1];
		ep->adapter_info[2] = asc_dvc_varp->cfg->adapter_info[2];
		ep->adapter_info[3] = asc_dvc_varp->cfg->adapter_info[3];
		ep->adapter_info[4] = asc_dvc_varp->cfg->adapter_info[4];
		ep->adapter_info[5] = asc_dvc_varp->cfg->adapter_info[5];

		/*
		 * Modअगरy board configuration.
		 */
		ASC_DBG(2, "AscInitSetConfig()\n");
		ret = AscInitSetConfig(pdev, shost) ? -ENODEV : 0;
		अगर (ret)
			जाओ err_unmap;
	पूर्ण अन्यथा अणु
		ADVEEP_3550_CONFIG *ep_3550;
		ADVEEP_38C0800_CONFIG *ep_38C0800;
		ADVEEP_38C1600_CONFIG *ep_38C1600;

		/*
		 * Save Wide EEP Configuration Inक्रमmation.
		 */
		अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC3550) अणु
			ep_3550 = &boardp->eep_config.adv_3550_eep;

			ep_3550->adapter_scsi_id = adv_dvc_varp->chip_scsi_id;
			ep_3550->max_host_qng = adv_dvc_varp->max_host_qng;
			ep_3550->max_dvc_qng = adv_dvc_varp->max_dvc_qng;
			ep_3550->termination = adv_dvc_varp->cfg->termination;
			ep_3550->disc_enable = adv_dvc_varp->cfg->disc_enable;
			ep_3550->bios_ctrl = adv_dvc_varp->bios_ctrl;
			ep_3550->wdtr_able = adv_dvc_varp->wdtr_able;
			ep_3550->sdtr_able = adv_dvc_varp->sdtr_able;
			ep_3550->ultra_able = adv_dvc_varp->ultra_able;
			ep_3550->tagqng_able = adv_dvc_varp->tagqng_able;
			ep_3550->start_motor = adv_dvc_varp->start_motor;
			ep_3550->scsi_reset_delay =
			    adv_dvc_varp->scsi_reset_रुको;
			ep_3550->serial_number_word1 =
			    adv_dvc_varp->cfg->serial1;
			ep_3550->serial_number_word2 =
			    adv_dvc_varp->cfg->serial2;
			ep_3550->serial_number_word3 =
			    adv_dvc_varp->cfg->serial3;
		पूर्ण अन्यथा अगर (adv_dvc_varp->chip_type == ADV_CHIP_ASC38C0800) अणु
			ep_38C0800 = &boardp->eep_config.adv_38C0800_eep;

			ep_38C0800->adapter_scsi_id =
			    adv_dvc_varp->chip_scsi_id;
			ep_38C0800->max_host_qng = adv_dvc_varp->max_host_qng;
			ep_38C0800->max_dvc_qng = adv_dvc_varp->max_dvc_qng;
			ep_38C0800->termination_lvd =
			    adv_dvc_varp->cfg->termination;
			ep_38C0800->disc_enable =
			    adv_dvc_varp->cfg->disc_enable;
			ep_38C0800->bios_ctrl = adv_dvc_varp->bios_ctrl;
			ep_38C0800->wdtr_able = adv_dvc_varp->wdtr_able;
			ep_38C0800->tagqng_able = adv_dvc_varp->tagqng_able;
			ep_38C0800->sdtr_speed1 = adv_dvc_varp->sdtr_speed1;
			ep_38C0800->sdtr_speed2 = adv_dvc_varp->sdtr_speed2;
			ep_38C0800->sdtr_speed3 = adv_dvc_varp->sdtr_speed3;
			ep_38C0800->sdtr_speed4 = adv_dvc_varp->sdtr_speed4;
			ep_38C0800->tagqng_able = adv_dvc_varp->tagqng_able;
			ep_38C0800->start_motor = adv_dvc_varp->start_motor;
			ep_38C0800->scsi_reset_delay =
			    adv_dvc_varp->scsi_reset_रुको;
			ep_38C0800->serial_number_word1 =
			    adv_dvc_varp->cfg->serial1;
			ep_38C0800->serial_number_word2 =
			    adv_dvc_varp->cfg->serial2;
			ep_38C0800->serial_number_word3 =
			    adv_dvc_varp->cfg->serial3;
		पूर्ण अन्यथा अणु
			ep_38C1600 = &boardp->eep_config.adv_38C1600_eep;

			ep_38C1600->adapter_scsi_id =
			    adv_dvc_varp->chip_scsi_id;
			ep_38C1600->max_host_qng = adv_dvc_varp->max_host_qng;
			ep_38C1600->max_dvc_qng = adv_dvc_varp->max_dvc_qng;
			ep_38C1600->termination_lvd =
			    adv_dvc_varp->cfg->termination;
			ep_38C1600->disc_enable =
			    adv_dvc_varp->cfg->disc_enable;
			ep_38C1600->bios_ctrl = adv_dvc_varp->bios_ctrl;
			ep_38C1600->wdtr_able = adv_dvc_varp->wdtr_able;
			ep_38C1600->tagqng_able = adv_dvc_varp->tagqng_able;
			ep_38C1600->sdtr_speed1 = adv_dvc_varp->sdtr_speed1;
			ep_38C1600->sdtr_speed2 = adv_dvc_varp->sdtr_speed2;
			ep_38C1600->sdtr_speed3 = adv_dvc_varp->sdtr_speed3;
			ep_38C1600->sdtr_speed4 = adv_dvc_varp->sdtr_speed4;
			ep_38C1600->tagqng_able = adv_dvc_varp->tagqng_able;
			ep_38C1600->start_motor = adv_dvc_varp->start_motor;
			ep_38C1600->scsi_reset_delay =
			    adv_dvc_varp->scsi_reset_रुको;
			ep_38C1600->serial_number_word1 =
			    adv_dvc_varp->cfg->serial1;
			ep_38C1600->serial_number_word2 =
			    adv_dvc_varp->cfg->serial2;
			ep_38C1600->serial_number_word3 =
			    adv_dvc_varp->cfg->serial3;
		पूर्ण

		/*
		 * Set the adapter's target id bit in the 'init_tidmask' field.
		 */
		boardp->init_tidmask |=
		    ADV_TID_TO_TIDMASK(adv_dvc_varp->chip_scsi_id);
	पूर्ण

	/*
	 * Channels are numbered beginning with 0. For AdvanSys one host
	 * काष्ठाure supports one channel. Multi-channel boards have a
	 * separate host काष्ठाure क्रम each channel.
	 */
	shost->max_channel = 0;
	अगर (ASC_NARROW_BOARD(boardp)) अणु
		shost->max_id = ASC_MAX_TID + 1;
		shost->max_lun = ASC_MAX_LUN + 1;
		shost->max_cmd_len = ASC_MAX_CDB_LEN;

		shost->io_port = asc_dvc_varp->iop_base;
		boardp->asc_n_io_port = ASC_IOADR_GAP;
		shost->this_id = asc_dvc_varp->cfg->chip_scsi_id;

		/* Set maximum number of queues the adapter can handle. */
		shost->can_queue = asc_dvc_varp->max_total_qng;
	पूर्ण अन्यथा अणु
		shost->max_id = ADV_MAX_TID + 1;
		shost->max_lun = ADV_MAX_LUN + 1;
		shost->max_cmd_len = ADV_MAX_CDB_LEN;

		/*
		 * Save the I/O Port address and length even though
		 * I/O ports are not used to access Wide boards.
		 * Instead the Wide boards are accessed with
		 * PCI Memory Mapped I/O.
		 */
		shost->io_port = iop;

		shost->this_id = adv_dvc_varp->chip_scsi_id;

		/* Set maximum number of queues the adapter can handle. */
		shost->can_queue = adv_dvc_varp->max_host_qng;
	पूर्ण

	/*
	 * Set the maximum number of scatter-gather elements the
	 * adapter can handle.
	 */
	अगर (ASC_NARROW_BOARD(boardp)) अणु
		/*
		 * Allow two commands with 'sg_tablesize' scatter-gather
		 * elements to be executed simultaneously. This value is
		 * the theoretical hardware limit. It may be decreased
		 * below.
		 */
		shost->sg_tablesize =
		    (((asc_dvc_varp->max_total_qng - 2) / 2) *
		     ASC_SG_LIST_PER_Q) + 1;
	पूर्ण अन्यथा अणु
		shost->sg_tablesize = ADV_MAX_SG_LIST;
	पूर्ण

	/*
	 * The value of 'sg_tablesize' can not exceed the SCSI
	 * mid-level driver definition of SG_ALL. SG_ALL also
	 * must not be exceeded, because it is used to define the
	 * size of the scatter-gather table in 'struct asc_sg_head'.
	 */
	अगर (shost->sg_tablesize > SG_ALL) अणु
		shost->sg_tablesize = SG_ALL;
	पूर्ण

	ASC_DBG(1, "sg_tablesize: %d\n", shost->sg_tablesize);

	/* BIOS start address. */
	अगर (ASC_NARROW_BOARD(boardp)) अणु
		shost->base = AscGetChipBiosAddress(asc_dvc_varp->iop_base,
						    asc_dvc_varp->bus_type);
	पूर्ण अन्यथा अणु
		/*
		 * Fill-in BIOS board variables. The Wide BIOS saves
		 * inक्रमmation in LRAM that is used by the driver.
		 */
		AdvReadWordLram(adv_dvc_varp->iop_base,
				BIOS_SIGNATURE, boardp->bios_signature);
		AdvReadWordLram(adv_dvc_varp->iop_base,
				BIOS_VERSION, boardp->bios_version);
		AdvReadWordLram(adv_dvc_varp->iop_base,
				BIOS_CODESEG, boardp->bios_codeseg);
		AdvReadWordLram(adv_dvc_varp->iop_base,
				BIOS_CODELEN, boardp->bios_codelen);

		ASC_DBG(1, "bios_signature 0x%x, bios_version 0x%x\n",
			 boardp->bios_signature, boardp->bios_version);

		ASC_DBG(1, "bios_codeseg 0x%x, bios_codelen 0x%x\n",
			 boardp->bios_codeseg, boardp->bios_codelen);

		/*
		 * If the BIOS saved a valid signature, then fill in
		 * the BIOS code segment base address.
		 */
		अगर (boardp->bios_signature == 0x55AA) अणु
			/*
			 * Convert x86 realmode code segment to a linear
			 * address by shअगरting left 4.
			 */
			shost->base = ((uदीर्घ)boardp->bios_codeseg << 4);
		पूर्ण अन्यथा अणु
			shost->base = 0;
		पूर्ण
	पूर्ण

	/*
	 * Register Board Resources - I/O Port, DMA, IRQ
	 */

	/* Register DMA Channel क्रम Narrow boards. */
	shost->dma_channel = NO_ISA_DMA;	/* Default to no ISA DMA. */

	/* Register IRQ Number. */
	ASC_DBG(2, "request_irq(%d, %p)\n", boardp->irq, shost);

	ret = request_irq(boardp->irq, advansys_पूर्णांकerrupt, share_irq,
			  DRV_NAME, shost);

	अगर (ret) अणु
		अगर (ret == -EBUSY) अणु
			shost_prपूर्णांकk(KERN_ERR, shost, "request_irq(): IRQ 0x%x "
					"already in use\n", boardp->irq);
		पूर्ण अन्यथा अगर (ret == -EINVAL) अणु
			shost_prपूर्णांकk(KERN_ERR, shost, "request_irq(): IRQ 0x%x "
					"not valid\n", boardp->irq);
		पूर्ण अन्यथा अणु
			shost_prपूर्णांकk(KERN_ERR, shost, "request_irq(): IRQ 0x%x "
					"failed with %d\n", boardp->irq, ret);
		पूर्ण
		जाओ err_unmap;
	पूर्ण

	/*
	 * Initialize board RISC chip and enable पूर्णांकerrupts.
	 */
	अगर (ASC_NARROW_BOARD(boardp)) अणु
		ASC_DBG(2, "AscInitAsc1000Driver()\n");

		asc_dvc_varp->overrun_buf = kzalloc(ASC_OVERRUN_BSIZE, GFP_KERNEL);
		अगर (!asc_dvc_varp->overrun_buf) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_irq;
		पूर्ण
		warn_code = AscInitAsc1000Driver(asc_dvc_varp);

		अगर (warn_code || asc_dvc_varp->err_code) अणु
			shost_prपूर्णांकk(KERN_ERR, shost, "error: init_state 0x%x, "
					"warn 0x%x, error 0x%x\n",
					asc_dvc_varp->init_state, warn_code,
					asc_dvc_varp->err_code);
			अगर (!asc_dvc_varp->overrun_dma) अणु
				ret = -ENODEV;
				जाओ err_मुक्त_mem;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (advansys_wide_init_chip(shost)) अणु
			ret = -ENODEV;
			जाओ err_मुक्त_mem;
		पूर्ण
	पूर्ण

	ASC_DBG_PRT_SCSI_HOST(2, shost);

	ret = scsi_add_host(shost, boardp->dev);
	अगर (ret)
		जाओ err_मुक्त_mem;

	scsi_scan_host(shost);
	वापस 0;

 err_मुक्त_mem:
	अगर (ASC_NARROW_BOARD(boardp)) अणु
		अगर (asc_dvc_varp->overrun_dma)
			dma_unmap_single(boardp->dev, asc_dvc_varp->overrun_dma,
					 ASC_OVERRUN_BSIZE, DMA_FROM_DEVICE);
		kमुक्त(asc_dvc_varp->overrun_buf);
	पूर्ण अन्यथा
		advansys_wide_मुक्त_mem(boardp);
 err_मुक्त_irq:
	मुक्त_irq(boardp->irq, shost);
 err_unmap:
	अगर (boardp->ioremap_addr)
		iounmap(boardp->ioremap_addr);
#अगर_घोषित CONFIG_PCI
 err_shost:
#पूर्ण_अगर
	वापस ret;
पूर्ण

/*
 * advansys_release()
 *
 * Release resources allocated क्रम a single AdvanSys adapter.
 */
अटल पूर्णांक advansys_release(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा asc_board *board = shost_priv(shost);
	ASC_DBG(1, "begin\n");
	scsi_हटाओ_host(shost);
	मुक्त_irq(board->irq, shost);

	अगर (ASC_NARROW_BOARD(board)) अणु
		dma_unmap_single(board->dev,
					board->dvc_var.asc_dvc_var.overrun_dma,
					ASC_OVERRUN_BSIZE, DMA_FROM_DEVICE);
		kमुक्त(board->dvc_var.asc_dvc_var.overrun_buf);
	पूर्ण अन्यथा अणु
		iounmap(board->ioremap_addr);
		advansys_wide_मुक्त_mem(board);
	पूर्ण
	scsi_host_put(shost);
	ASC_DBG(1, "end\n");
	वापस 0;
पूर्ण

#घोषणा ASC_IOADR_TABLE_MAX_IX  11

अटल PortAddr _asc_def_iop_base[ASC_IOADR_TABLE_MAX_IX] = अणु
	0x100, 0x0110, 0x120, 0x0130, 0x140, 0x0150, 0x0190,
	0x0210, 0x0230, 0x0250, 0x0330
पूर्ण;

अटल व्योम advansys_vlb_हटाओ(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	पूर्णांक ioport = _asc_def_iop_base[id];
	advansys_release(dev_get_drvdata(dev));
	release_region(ioport, ASC_IOADR_GAP);
पूर्ण

/*
 * The VLB IRQ number is found in bits 2 to 4 of the CfgLsw.  It decodes as:
 * 000: invalid
 * 001: 10
 * 010: 11
 * 011: 12
 * 100: invalid
 * 101: 14
 * 110: 15
 * 111: invalid
 */
अटल अचिन्हित पूर्णांक advansys_vlb_irq_no(PortAddr iop_base)
अणु
	अचिन्हित लघु cfg_lsw = AscGetChipCfgLsw(iop_base);
	अचिन्हित पूर्णांक chip_irq = ((cfg_lsw >> 2) & 0x07) + 9;
	अगर ((chip_irq < 10) || (chip_irq == 13) || (chip_irq > 15))
		वापस 0;
	वापस chip_irq;
पूर्ण

अटल पूर्णांक advansys_vlb_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	पूर्णांक err = -ENODEV;
	PortAddr iop_base = _asc_def_iop_base[id];
	काष्ठा Scsi_Host *shost;
	काष्ठा asc_board *board;

	अगर (!request_region(iop_base, ASC_IOADR_GAP, DRV_NAME)) अणु
		ASC_DBG(1, "I/O port 0x%x busy\n", iop_base);
		वापस -ENODEV;
	पूर्ण
	ASC_DBG(1, "probing I/O port 0x%x\n", iop_base);
	अगर (!AscFindSignature(iop_base))
		जाओ release_region;
	/*
	 * I करोn't think this condition can actually happen, but the old
	 * driver did it, and the chances of finding a VLB setup in 2007
	 * to करो testing with is slight to none.
	 */
	अगर (AscGetChipVersion(iop_base, ASC_IS_VL) > ASC_CHIP_MAX_VER_VL)
		जाओ release_region;

	err = -ENOMEM;
	shost = scsi_host_alloc(&advansys_ढाँचा, माप(*board));
	अगर (!shost)
		जाओ release_region;

	board = shost_priv(shost);
	board->irq = advansys_vlb_irq_no(iop_base);
	board->dev = dev;
	board->shost = shost;

	err = advansys_board_found(shost, iop_base, ASC_IS_VL);
	अगर (err)
		जाओ मुक्त_host;

	dev_set_drvdata(dev, shost);
	वापस 0;

 मुक्त_host:
	scsi_host_put(shost);
 release_region:
	release_region(iop_base, ASC_IOADR_GAP);
	वापस -ENODEV;
पूर्ण

अटल काष्ठा isa_driver advansys_vlb_driver = अणु
	.probe		= advansys_vlb_probe,
	.हटाओ		= advansys_vlb_हटाओ,
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= "advansys_vlb",
	पूर्ण,
पूर्ण;

अटल काष्ठा eisa_device_id advansys_eisa_table[] = अणु
	अणु "ABP7401" पूर्ण,
	अणु "ABP7501" पूर्ण,
	अणु "" पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(eisa, advansys_eisa_table);

/*
 * EISA is a little more tricky than PCI; each EISA device may have two
 * channels, and this driver is written to make each channel its own Scsi_Host
 */
काष्ठा eisa_scsi_data अणु
	काष्ठा Scsi_Host *host[2];
पूर्ण;

/*
 * The EISA IRQ number is found in bits 8 to 10 of the CfgLsw.  It decodes as:
 * 000: 10
 * 001: 11
 * 010: 12
 * 011: invalid
 * 100: 14
 * 101: 15
 * 110: invalid
 * 111: invalid
 */
अटल अचिन्हित पूर्णांक advansys_eisa_irq_no(काष्ठा eisa_device *edev)
अणु
	अचिन्हित लघु cfg_lsw = inw(edev->base_addr + 0xc86);
	अचिन्हित पूर्णांक chip_irq = ((cfg_lsw >> 8) & 0x07) + 10;
	अगर ((chip_irq == 13) || (chip_irq > 15))
		वापस 0;
	वापस chip_irq;
पूर्ण

अटल पूर्णांक advansys_eisa_probe(काष्ठा device *dev)
अणु
	पूर्णांक i, ioport, irq = 0;
	पूर्णांक err;
	काष्ठा eisa_device *edev = to_eisa_device(dev);
	काष्ठा eisa_scsi_data *data;

	err = -ENOMEM;
	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		जाओ fail;
	ioport = edev->base_addr + 0xc30;

	err = -ENODEV;
	क्रम (i = 0; i < 2; i++, ioport += 0x20) अणु
		काष्ठा asc_board *board;
		काष्ठा Scsi_Host *shost;
		अगर (!request_region(ioport, ASC_IOADR_GAP, DRV_NAME)) अणु
			prपूर्णांकk(KERN_WARNING "Region %x-%x busy\n", ioport,
			       ioport + ASC_IOADR_GAP - 1);
			जारी;
		पूर्ण
		अगर (!AscFindSignature(ioport)) अणु
			release_region(ioport, ASC_IOADR_GAP);
			जारी;
		पूर्ण

		/*
		 * I करोn't know why we need to करो this क्रम EISA chips, but
		 * not क्रम any others.  It looks to be equivalent to
		 * AscGetChipCfgMsw, but I may have overlooked something,
		 * so I'm not converting it until I get an EISA board to
		 * test with.
		 */
		inw(ioport + 4);

		अगर (!irq)
			irq = advansys_eisa_irq_no(edev);

		err = -ENOMEM;
		shost = scsi_host_alloc(&advansys_ढाँचा, माप(*board));
		अगर (!shost)
			जाओ release_region;

		board = shost_priv(shost);
		board->irq = irq;
		board->dev = dev;
		board->shost = shost;

		err = advansys_board_found(shost, ioport, ASC_IS_EISA);
		अगर (!err) अणु
			data->host[i] = shost;
			जारी;
		पूर्ण

		scsi_host_put(shost);
 release_region:
		release_region(ioport, ASC_IOADR_GAP);
		अवरोध;
	पूर्ण

	अगर (err)
		जाओ मुक्त_data;
	dev_set_drvdata(dev, data);
	वापस 0;

 मुक्त_data:
	kमुक्त(data->host[0]);
	kमुक्त(data->host[1]);
	kमुक्त(data);
 fail:
	वापस err;
पूर्ण

अटल पूर्णांक advansys_eisa_हटाओ(काष्ठा device *dev)
अणु
	पूर्णांक i;
	काष्ठा eisa_scsi_data *data = dev_get_drvdata(dev);

	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक ioport;
		काष्ठा Scsi_Host *shost = data->host[i];
		अगर (!shost)
			जारी;
		ioport = shost->io_port;
		advansys_release(shost);
		release_region(ioport, ASC_IOADR_GAP);
	पूर्ण

	kमुक्त(data);
	वापस 0;
पूर्ण

अटल काष्ठा eisa_driver advansys_eisa_driver = अणु
	.id_table =		advansys_eisa_table,
	.driver = अणु
		.name =		DRV_NAME,
		.probe =	advansys_eisa_probe,
		.हटाओ =	advansys_eisa_हटाओ,
	पूर्ण
पूर्ण;

/* PCI Devices supported by this driver */
अटल काष्ठा pci_device_id advansys_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_ASP, PCI_DEVICE_ID_ASP_1200A,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_ASP, PCI_DEVICE_ID_ASP_ABP940,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_ASP, PCI_DEVICE_ID_ASP_ABP940U,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_ASP, PCI_DEVICE_ID_ASP_ABP940UW,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_ASP, PCI_DEVICE_ID_38C0800_REV1,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_ASP, PCI_DEVICE_ID_38C1600_REV1,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, advansys_pci_tbl);

अटल व्योम advansys_set_latency(काष्ठा pci_dev *pdev)
अणु
	अगर ((pdev->device == PCI_DEVICE_ID_ASP_1200A) ||
	    (pdev->device == PCI_DEVICE_ID_ASP_ABP940)) अणु
		pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0);
	पूर्ण अन्यथा अणु
		u8 latency;
		pci_पढ़ो_config_byte(pdev, PCI_LATENCY_TIMER, &latency);
		अगर (latency < 0x20)
			pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0x20);
	पूर्ण
पूर्ण

अटल पूर्णांक advansys_pci_probe(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err, ioport;
	काष्ठा Scsi_Host *shost;
	काष्ठा asc_board *board;

	err = pci_enable_device(pdev);
	अगर (err)
		जाओ fail;
	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err)
		जाओ disable_device;
	pci_set_master(pdev);
	advansys_set_latency(pdev);

	err = -ENODEV;
	अगर (pci_resource_len(pdev, 0) == 0)
		जाओ release_region;

	ioport = pci_resource_start(pdev, 0);

	err = -ENOMEM;
	shost = scsi_host_alloc(&advansys_ढाँचा, माप(*board));
	अगर (!shost)
		जाओ release_region;

	board = shost_priv(shost);
	board->irq = pdev->irq;
	board->dev = &pdev->dev;
	board->shost = shost;

	अगर (pdev->device == PCI_DEVICE_ID_ASP_ABP940UW ||
	    pdev->device == PCI_DEVICE_ID_38C0800_REV1 ||
	    pdev->device == PCI_DEVICE_ID_38C1600_REV1) अणु
		board->flags |= ASC_IS_WIDE_BOARD;
	पूर्ण

	err = advansys_board_found(shost, ioport, ASC_IS_PCI);
	अगर (err)
		जाओ मुक्त_host;

	pci_set_drvdata(pdev, shost);
	वापस 0;

 मुक्त_host:
	scsi_host_put(shost);
 release_region:
	pci_release_regions(pdev);
 disable_device:
	pci_disable_device(pdev);
 fail:
	वापस err;
पूर्ण

अटल व्योम advansys_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	advansys_release(pci_get_drvdata(pdev));
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver advansys_pci_driver = अणु
	.name =		DRV_NAME,
	.id_table =	advansys_pci_tbl,
	.probe =	advansys_pci_probe,
	.हटाओ =	advansys_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init advansys_init(व्योम)
अणु
	पूर्णांक error;

	error = isa_रेजिस्टर_driver(&advansys_vlb_driver,
				    ASC_IOADR_TABLE_MAX_IX);
	अगर (error)
		जाओ fail;

	error = eisa_driver_रेजिस्टर(&advansys_eisa_driver);
	अगर (error)
		जाओ unरेजिस्टर_vlb;

	error = pci_रेजिस्टर_driver(&advansys_pci_driver);
	अगर (error)
		जाओ unरेजिस्टर_eisa;

	वापस 0;

 unरेजिस्टर_eisa:
	eisa_driver_unरेजिस्टर(&advansys_eisa_driver);
 unरेजिस्टर_vlb:
	isa_unरेजिस्टर_driver(&advansys_vlb_driver);
 fail:
	वापस error;
पूर्ण

अटल व्योम __निकास advansys_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&advansys_pci_driver);
	eisa_driver_unरेजिस्टर(&advansys_eisa_driver);
	isa_unरेजिस्टर_driver(&advansys_vlb_driver);
पूर्ण

module_init(advansys_init);
module_निकास(advansys_निकास);

MODULE_LICENSE("GPL");
MODULE_FIRMWARE("advansys/mcode.bin");
MODULE_FIRMWARE("advansys/3550.bin");
MODULE_FIRMWARE("advansys/38C0800.bin");
MODULE_FIRMWARE("advansys/38C1600.bin");
