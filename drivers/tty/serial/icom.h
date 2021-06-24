<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * icom.h
 *
 * Copyright (C) 2001 Michael Anderson, IBM Corporation
 *
 * Serial device driver include file.
 */

#समावेश <linux/serial_core.h>

#घोषणा BAUD_TABLE_LIMIT	((माप(icom_acfg_baud)/माप(पूर्णांक)) - 1)
अटल पूर्णांक icom_acfg_baud[] = अणु
	300,
	600,
	900,
	1200,
	1800,
	2400,
	3600,
	4800,
	7200,
	9600,
	14400,
	19200,
	28800,
	38400,
	57600,
	76800,
	115200,
	153600,
	230400,
	307200,
	460800,
पूर्ण;

काष्ठा icom_regs अणु
	u32 control;		/* Adapter Control Register     */
	u32 पूर्णांकerrupt;		/* Adapter Interrupt Register   */
	u32 पूर्णांक_mask;		/* Adapter Interrupt Mask Reg   */
	u32 पूर्णांक_pri;		/* Adapter Interrupt Priority r */
	u32 पूर्णांक_reg_b;		/* Adapter non-masked Interrupt */
	u32 resvd01;
	u32 resvd02;
	u32 resvd03;
	u32 control_2;		/* Adapter Control Register 2   */
	u32 पूर्णांकerrupt_2;	/* Adapter Interrupt Register 2 */
	u32 पूर्णांक_mask_2;		/* Adapter Interrupt Mask 2     */
	u32 पूर्णांक_pri_2;		/* Adapter Interrupt Prior 2    */
	u32 पूर्णांक_reg_2b;		/* Adapter non-masked 2         */
पूर्ण;

काष्ठा func_dram अणु
	u32 reserved[108];	/* 0-1B0   reserved by personality code */
	u32 RcvStatusAddr;	/* 1B0-1B3 Status Address क्रम Next rcv */
	u8 RcvStnAddr;		/* 1B4     Receive Station Addr */
	u8 IdleState;		/* 1B5     Idle State */
	u8 IdleMonitor;		/* 1B6     Idle Monitor */
	u8 FlagFillIdleTimer;	/* 1B7     Flag Fill Idle Timer */
	u32 XmitStatusAddr;	/* 1B8-1BB Transmit Status Address */
	u8 StartXmitCmd;	/* 1BC     Start Xmit Command */
	u8 HDLCConfigReg;	/* 1BD     Reserved */
	u8 CauseCode;		/* 1BE     Cause code क्रम fatal error */
	u8 xअक्षर;		/* 1BF     High priority send */
	u32 reserved3;		/* 1C0-1C3 Reserved */
	u8 PrevCmdReg;		/* 1C4     Reserved */
	u8 CmdReg;		/* 1C5     Command Register */
	u8 async_config2;	/* 1C6     Async Config Byte 2 */
	u8 async_config3;	/* 1C7     Async Config Byte 3 */
	u8 dce_resvd[20];	/* 1C8-1DB DCE Rsvd           */
	u8 dce_resvd21;		/* 1DC     DCE Rsvd (21st byte */
	u8 misc_flags;		/* 1DD     misc flags         */
#घोषणा V2_HARDWARE     0x40
#घोषणा ICOM_HDW_ACTIVE 0x01
	u8 call_length;		/* 1DE     Phone #/CFI buff ln */
	u8 call_length2;	/* 1DF     Upper byte (unused) */
	u32 call_addr;		/* 1E0-1E3 Phn #/CFI buff addr */
	u16 समयr_value;	/* 1E4-1E5 general समयr value */
	u8 समयr_command;	/* 1E6     general समयr cmd  */
	u8 dce_command;		/* 1E7     dce command reg    */
	u8 dce_cmd_status;	/* 1E8     dce command stat   */
	u8 x21_r1_ioff;		/* 1E9     dce पढ़ोy counter  */
	u8 x21_r0_ioff;		/* 1EA     dce not पढ़ोy ctr  */
	u8 x21_ralt_ioff;	/* 1EB     dce CNR counter    */
	u8 x21_r1_ion;		/* 1EC     dce पढ़ोy I on ctr */
	u8 rsvd_ier;		/* 1ED     Rsvd क्रम IER (अगर ne */
	u8 ier;			/* 1EE     Interrupt Enable   */
	u8 isr;			/* 1EF     Input Signal Reg   */
	u8 osr;			/* 1F0     Output Signal Reg  */
	u8 reset;		/* 1F1     Reset/Reload Reg   */
	u8 disable;		/* 1F2     Disable Reg        */
	u8 sync;		/* 1F3     Sync Reg           */
	u8 error_stat;		/* 1F4     Error Status       */
	u8 cable_id;		/* 1F5     Cable ID           */
	u8 cs_length;		/* 1F6     CS Load Length     */
	u8 mac_length;		/* 1F7     Mac Load Length    */
	u32 cs_load_addr;	/* 1F8-1FB Call Load PCI Addr */
	u32 mac_load_addr;	/* 1FC-1FF Mac Load PCI Addr  */
पूर्ण;

/*
 * adapter defines and काष्ठाures
 */
#घोषणा ICOM_CONTROL_START_A         0x00000008
#घोषणा ICOM_CONTROL_STOP_A          0x00000004
#घोषणा ICOM_CONTROL_START_B         0x00000002
#घोषणा ICOM_CONTROL_STOP_B          0x00000001
#घोषणा ICOM_CONTROL_START_C         0x00000008
#घोषणा ICOM_CONTROL_STOP_C          0x00000004
#घोषणा ICOM_CONTROL_START_D         0x00000002
#घोषणा ICOM_CONTROL_STOP_D          0x00000001
#घोषणा ICOM_IRAM_OFFSET             0x1000
#घोषणा ICOM_IRAM_SIZE               0x0C00
#घोषणा ICOM_DCE_IRAM_OFFSET         0x0A00
#घोषणा ICOM_CABLE_ID_VALID          0x01
#घोषणा ICOM_CABLE_ID_MASK           0xF0
#घोषणा ICOM_DISABLE                 0x80
#घोषणा CMD_XMIT_RCV_ENABLE          0xC0
#घोषणा CMD_XMIT_ENABLE              0x40
#घोषणा CMD_RCV_DISABLE              0x00
#घोषणा CMD_RCV_ENABLE               0x80
#घोषणा CMD_RESTART                  0x01
#घोषणा CMD_HOLD_XMIT                0x02
#घोषणा CMD_SND_BREAK                0x04
#घोषणा RS232_CABLE                  0x06
#घोषणा V24_CABLE                    0x0E
#घोषणा V35_CABLE                    0x0C
#घोषणा V36_CABLE                    0x02
#घोषणा NO_CABLE                     0x00
#घोषणा START_DOWNLOAD               0x80
#घोषणा ICOM_INT_MASK_PRC_A          0x00003FFF
#घोषणा ICOM_INT_MASK_PRC_B          0x3FFF0000
#घोषणा ICOM_INT_MASK_PRC_C          0x00003FFF
#घोषणा ICOM_INT_MASK_PRC_D          0x3FFF0000
#घोषणा INT_RCV_COMPLETED            0x1000
#घोषणा INT_XMIT_COMPLETED           0x2000
#घोषणा INT_IDLE_DETECT              0x0800
#घोषणा INT_RCV_DISABLED             0x0400
#घोषणा INT_XMIT_DISABLED            0x0200
#घोषणा INT_RCV_XMIT_SHUTDOWN        0x0100
#घोषणा INT_FATAL_ERROR              0x0080
#घोषणा INT_CABLE_PULL               0x0020
#घोषणा INT_SIGNAL_CHANGE            0x0010
#घोषणा HDLC_PPP_PURE_ASYNC          0x02
#घोषणा HDLC_FF_FILL                 0x00
#घोषणा HDLC_HDW_FLOW                0x01
#घोषणा START_XMIT                   0x80
#घोषणा ICOM_ACFG_DRIVE1             0x20
#घोषणा ICOM_ACFG_NO_PARITY          0x00
#घोषणा ICOM_ACFG_PARITY_ENAB        0x02
#घोषणा ICOM_ACFG_PARITY_ODD         0x01
#घोषणा ICOM_ACFG_8BPC               0x00
#घोषणा ICOM_ACFG_7BPC               0x04
#घोषणा ICOM_ACFG_6BPC               0x08
#घोषणा ICOM_ACFG_5BPC               0x0C
#घोषणा ICOM_ACFG_1STOP_BIT          0x00
#घोषणा ICOM_ACFG_2STOP_BIT          0x10
#घोषणा ICOM_DTR                     0x80
#घोषणा ICOM_RTS                     0x40
#घोषणा ICOM_RI                      0x08
#घोषणा ICOM_DSR                     0x80
#घोषणा ICOM_DCD                     0x20
#घोषणा ICOM_CTS                     0x40

#घोषणा NUM_XBUFFS 1
#घोषणा NUM_RBUFFS 2
#घोषणा RCV_BUFF_SZ 0x0200
#घोषणा XMIT_BUFF_SZ 0x1000
काष्ठा statusArea अणु
    /**********************************************/
	/* Transmit Status Area                       */
    /**********************************************/
	काष्ठा xmit_status_areaअणु
		u32 leNext;	/* Next entry in Little Endian on Adapter */
		u32 leNextASD;
		u32 leBuffer;	/* Buffer क्रम entry in LE क्रम Adapter */
		u16 leLengthASD;
		u16 leOffsetASD;
		u16 leLength;	/* Length of data in segment */
		u16 flags;
#घोषणा SA_FLAGS_DONE           0x0080	/* Done with Segment */
#घोषणा SA_FLAGS_CONTINUED      0x8000	/* More Segments */
#घोषणा SA_FLAGS_IDLE           0x4000	/* Mark IDLE after frm */
#घोषणा SA_FLAGS_READY_TO_XMIT  0x0800
#घोषणा SA_FLAGS_STAT_MASK      0x007F
	पूर्ण xmit[NUM_XBUFFS];

    /**********************************************/
	/* Receive Status Area                        */
    /**********************************************/
	काष्ठा अणु
		u32 leNext;	/* Next entry in Little Endian on Adapter */
		u32 leNextASD;
		u32 leBuffer;	/* Buffer क्रम entry in LE क्रम Adapter */
		u16 WorkingLength;	/* size of segment */
		u16 reserv01;
		u16 leLength;	/* Length of data in segment */
		u16 flags;
#घोषणा SA_FL_RCV_DONE           0x0010	/* Data पढ़ोy */
#घोषणा SA_FLAGS_OVERRUN         0x0040
#घोषणा SA_FLAGS_PARITY_ERROR    0x0080
#घोषणा SA_FLAGS_FRAME_ERROR     0x0001
#घोषणा SA_FLAGS_FRAME_TRUNC     0x0002
#घोषणा SA_FLAGS_BREAK_DET       0x0004	/* set conditionally by device driver, not hardware */
#घोषणा SA_FLAGS_RCV_MASK        0xFFE6
	पूर्ण rcv[NUM_RBUFFS];
पूर्ण;

काष्ठा icom_adapter;


#घोषणा ICOM_MAJOR       243
#घोषणा ICOM_MINOR_START 0

काष्ठा icom_port अणु
	काष्ठा uart_port uart_port;
	u8 imbed_modem;
#घोषणा ICOM_UNKNOWN		1
#घोषणा ICOM_RVX		2
#घोषणा ICOM_IMBED_MODEM	3
	अचिन्हित अक्षर cable_id;
	अचिन्हित अक्षर पढ़ो_status_mask;
	अचिन्हित अक्षर ignore_status_mask;
	व्योम __iomem * पूर्णांक_reg;
	काष्ठा icom_regs __iomem *global_reg;
	काष्ठा func_dram __iomem *dram;
	पूर्णांक port;
	काष्ठा statusArea *statStg;
	dma_addr_t statStg_pci;
	u32 *xmitRestart;
	dma_addr_t xmitRestart_pci;
	अचिन्हित अक्षर *xmit_buf;
	dma_addr_t xmit_buf_pci;
	अचिन्हित अक्षर *recv_buf;
	dma_addr_t recv_buf_pci;
	पूर्णांक next_rcv;
	पूर्णांक put_length;
	पूर्णांक status;
#घोषणा ICOM_PORT_ACTIVE	1	/* Port exists. */
#घोषणा ICOM_PORT_OFF		0	/* Port करोes not exist. */
	पूर्णांक load_in_progress;
	काष्ठा icom_adapter *adapter;
पूर्ण;

काष्ठा icom_adapter अणु
	व्योम __iomem * base_addr;
	अचिन्हित दीर्घ base_addr_pci;
	काष्ठा pci_dev *pci_dev;
	काष्ठा icom_port port_info[4];
	पूर्णांक index;
	पूर्णांक version;
#घोषणा ADAPTER_V1	0x0001
#घोषणा ADAPTER_V2	0x0002
	u32 subप्रणाली_id;
#घोषणा FOUR_PORT_MODEL				0x0252
#घोषणा V2_TWO_PORTS_RVX			0x021A
#घोषणा V2_ONE_PORT_RVX_ONE_PORT_IMBED_MDM	0x0251
	पूर्णांक numb_ports;
	काष्ठा list_head icom_adapter_entry;
	काष्ठा kref kref;
पूर्ण;

/* prototype */
बाह्य व्योम iCom_sercons_init(व्योम);

काष्ठा lookup_proc_table अणु
	u32	__iomem *global_control_reg;
	अचिन्हित दीर्घ	processor_id;
पूर्ण;

काष्ठा lookup_पूर्णांक_table अणु
	u32	__iomem *global_पूर्णांक_mask;
	अचिन्हित दीर्घ	processor_id;
पूर्ण;
