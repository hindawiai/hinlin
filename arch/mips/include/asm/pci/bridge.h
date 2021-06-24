<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * bridge.h - bridge chip header file, derived from IRIX <sys/PCI/bridge.h>,
 * revision 1.76.
 *
 * Copyright (C) 1996, 1999 Silcon Graphics, Inc.
 * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)
 */
#अगर_अघोषित _ASM_PCI_BRIDGE_H
#घोषणा _ASM_PCI_BRIDGE_H

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/xtalk/xwidget.h>		/* generic widget header */
#समावेश <यंत्र/sn/types.h>

/* I/O page size */

#घोषणा IOPFNSHIFT		12	/* 4K per mapped page */

#घोषणा IOPGSIZE		(1 << IOPFNSHIFT)
#घोषणा IOPG(x)			((x) >> IOPFNSHIFT)
#घोषणा IOPGOFF(x)		((x) & (IOPGSIZE-1))

/* Bridge RAM sizes */

#घोषणा BRIDGE_ATE_RAM_SIZE	0x00000400	/* 1kB ATE RAM */

#घोषणा BRIDGE_CONFIG_BASE	0x20000
#घोषणा BRIDGE_CONFIG1_BASE	0x28000
#घोषणा BRIDGE_CONFIG_END	0x30000
#घोषणा BRIDGE_CONFIG_SLOT_SIZE 0x1000

#घोषणा BRIDGE_SSRAM_512K	0x00080000	/* 512kB */
#घोषणा BRIDGE_SSRAM_128K	0x00020000	/* 128kB */
#घोषणा BRIDGE_SSRAM_64K	0x00010000	/* 64kB */
#घोषणा BRIDGE_SSRAM_0K		0x00000000	/* 0kB */

/* ========================================================================
 *    Bridge address map
 */

#अगर_अघोषित __ASSEMBLY__

#घोषणा ATE_V		0x01
#घोषणा ATE_CO		0x02
#घोषणा ATE_PREC	0x04
#घोषणा ATE_PREF	0x08
#घोषणा ATE_BAR		0x10

#घोषणा ATE_PFNSHIFT		12
#घोषणा ATE_TIDSHIFT		8
#घोषणा ATE_RMFSHIFT		48

#घोषणा mkate(xaddr, xid, attr) (((xaddr) & 0x0000fffffffff000ULL) | \
				 ((xid)<<ATE_TIDSHIFT) | \
				 (attr))

#घोषणा BRIDGE_INTERNAL_ATES	128

/*
 * It is generally preferred that hardware रेजिस्टरs on the bridge
 * are located from C code via this काष्ठाure.
 *
 * Generated from Bridge spec dated 04oct95
 */

काष्ठा bridge_regs अणु
	/* Local Registers			       0x000000-0x00FFFF */

	/* standard widget configuration	       0x000000-0x000057 */
	widget_cfg_t	    b_widget;			/* 0x000000 */

	/* helper fieldnames क्रम accessing bridge widget */

#घोषणा b_wid_id			b_widget.w_id
#घोषणा b_wid_stat			b_widget.w_status
#घोषणा b_wid_err_upper			b_widget.w_err_upper_addr
#घोषणा b_wid_err_lower			b_widget.w_err_lower_addr
#घोषणा b_wid_control			b_widget.w_control
#घोषणा b_wid_req_समयout		b_widget.w_req_समयout
#घोषणा b_wid_पूर्णांक_upper			b_widget.w_पूर्णांकdest_upper_addr
#घोषणा b_wid_पूर्णांक_lower			b_widget.w_पूर्णांकdest_lower_addr
#घोषणा b_wid_err_cmdword		b_widget.w_err_cmd_word
#घोषणा b_wid_llp			b_widget.w_llp_cfg
#घोषणा b_wid_tflush			b_widget.w_tflush

	/* bridge-specअगरic widget configuration 0x000058-0x00007F */
	u32	_pad_000058;
	u32	b_wid_aux_err;		/* 0x00005C */
	u32	_pad_000060;
	u32	b_wid_resp_upper;		/* 0x000064 */
	u32	_pad_000068;
	u32	b_wid_resp_lower;		/* 0x00006C */
	u32	_pad_000070;
	u32	 b_wid_tst_pin_ctrl;		/* 0x000074 */
	u32	_pad_000078[2];

	/* PMU & Map 0x000080-0x00008F */
	u32	_pad_000080;
	u32	b_dir_map;			/* 0x000084 */
	u32	_pad_000088[2];

	/* SSRAM 0x000090-0x00009F */
	u32	_pad_000090;
	u32	b_ram_perr;			/* 0x000094 */
	u32	_pad_000098[2];

	/* Arbitration 0x0000A0-0x0000AF */
	u32	_pad_0000A0;
	u32	b_arb;				/* 0x0000A4 */
	u32	_pad_0000A8[2];

	/* Number In A Can 0x0000B0-0x0000BF */
	u32	_pad_0000B0;
	u32	b_nic;				/* 0x0000B4 */
	u32	_pad_0000B8[2];

	/* PCI/GIO 0x0000C0-0x0000FF */
	u32	_pad_0000C0;
	u32	b_bus_समयout;			/* 0x0000C4 */
#घोषणा b_pci_bus_समयout b_bus_समयout

	u32	_pad_0000C8;
	u32	b_pci_cfg;			/* 0x0000CC */
	u32	_pad_0000D0;
	u32	b_pci_err_upper;		/* 0x0000D4 */
	u32	_pad_0000D8;
	u32	b_pci_err_lower;		/* 0x0000DC */
	u32	_pad_0000E0[8];
#घोषणा b_gio_err_lower b_pci_err_lower
#घोषणा b_gio_err_upper b_pci_err_upper

	/* Interrupt 0x000100-0x0001FF */
	u32	_pad_000100;
	u32	b_पूर्णांक_status;			/* 0x000104 */
	u32	_pad_000108;
	u32	b_पूर्णांक_enable;			/* 0x00010C */
	u32	_pad_000110;
	u32	b_पूर्णांक_rst_stat;			/* 0x000114 */
	u32	_pad_000118;
	u32	b_पूर्णांक_mode;			/* 0x00011C */
	u32	_pad_000120;
	u32	b_पूर्णांक_device;			/* 0x000124 */
	u32	_pad_000128;
	u32	b_पूर्णांक_host_err;			/* 0x00012C */

	काष्ठा अणु
		u32	__pad;			/* 0x0001अणु30,,,68पूर्ण */
		u32	addr;			/* 0x0001अणु34,,,6Cपूर्ण */
	पूर्ण b_पूर्णांक_addr[8];				/* 0x000130 */

	u32	_pad_000170[36];

	/* Device 0x000200-0x0003FF */
	काष्ठा अणु
		u32	__pad;			/* 0x0002अणु00,,,38पूर्ण */
		u32	reg;			/* 0x0002अणु04,,,3Cपूर्ण */
	पूर्ण b_device[8];					/* 0x000200 */

	काष्ठा अणु
		u32	__pad;			/* 0x0002अणु40,,,78पूर्ण */
		u32	reg;			/* 0x0002अणु44,,,7Cपूर्ण */
	पूर्ण b_wr_req_buf[8];				/* 0x000240 */

	काष्ठा अणु
		u32	__pad;			/* 0x0002अणु80,,,88पूर्ण */
		u32	reg;			/* 0x0002अणु84,,,8Cपूर्ण */
	पूर्ण b_rrb_map[2];					/* 0x000280 */
#घोषणा b_even_resp	b_rrb_map[0].reg		/* 0x000284 */
#घोषणा b_odd_resp	b_rrb_map[1].reg		/* 0x00028C */

	u32	_pad_000290;
	u32	b_resp_status;			/* 0x000294 */
	u32	_pad_000298;
	u32	b_resp_clear;			/* 0x00029C */

	u32	_pad_0002A0[24];

	अक्षर		_pad_000300[0x10000 - 0x000300];

	/* Internal Address Translation Entry RAM 0x010000-0x0103FF */
	जोड़ अणु
		u64	wr;			/* ग_लिखो-only */
		काष्ठा अणु
			u32	_p_pad;
			u32	rd;		/* पढ़ो-only */
		पूर्ण			hi;
	पूर्ण			    b_पूर्णांक_ate_ram[128];

	अक्षर	_pad_010400[0x11000 - 0x010400];

	/* Internal Address Translation Entry RAM LOW 0x011000-0x0113FF */
	काष्ठा अणु
		u32	_p_pad;
		u32	rd;		/* पढ़ो-only */
	पूर्ण b_पूर्णांक_ate_ram_lo[128];

	अक्षर	_pad_011400[0x20000 - 0x011400];

	/* PCI Device Configuration Spaces 0x020000-0x027FFF */
	जोड़ अणु				/* make all access sizes available. */
		u8	c[0x1000 / 1];
		u16	s[0x1000 / 2];
		u32	l[0x1000 / 4];
		u64	d[0x1000 / 8];
		जोड़ अणु
			u8	c[0x100 / 1];
			u16	s[0x100 / 2];
			u32	l[0x100 / 4];
			u64	d[0x100 / 8];
		पूर्ण f[8];
	पूर्ण b_type0_cfg_dev[8];					/* 0x020000 */

	/* PCI Type 1 Configuration Space 0x028000-0x028FFF */
	जोड़ अणु				/* make all access sizes available. */
		u8	c[0x1000 / 1];
		u16	s[0x1000 / 2];
		u32	l[0x1000 / 4];
		u64	d[0x1000 / 8];
	पूर्ण b_type1_cfg;					/* 0x028000-0x029000 */

	अक्षर	_pad_029000[0x007000];			/* 0x029000-0x030000 */

	/* PCI Interrupt Acknowledge Cycle 0x030000 */
	जोड़ अणु
		u8	c[8 / 1];
		u16	s[8 / 2];
		u32	l[8 / 4];
		u64	d[8 / 8];
	पूर्ण b_pci_iack;						/* 0x030000 */

	u8	_pad_030007[0x04fff8];			/* 0x030008-0x07FFFF */

	/* External Address Translation Entry RAM 0x080000-0x0FFFFF */
	u64	b_ext_ate_ram[0x10000];

	/* Reserved 0x100000-0x1FFFFF */
	अक्षर	_pad_100000[0x200000-0x100000];

	/* PCI/GIO Device Spaces 0x200000-0xBFFFFF */
	जोड़ अणु				/* make all access sizes available. */
		u8	c[0x100000 / 1];
		u16	s[0x100000 / 2];
		u32	l[0x100000 / 4];
		u64	d[0x100000 / 8];
	पूर्ण b_devio_raw[10];				/* 0x200000 */

	/* b_devio macro is a bit strange; it reflects the
	 * fact that the Bridge ASIC provides 2M क्रम the
	 * first two DevIO winकरोws and 1M क्रम the other six.
	 */
#घोषणा b_devio(n)	b_devio_raw[((n)<2)?(n*2):(n+2)]

	/* External Flash Proms 1,0 0xC00000-0xFFFFFF */
	जोड़ अणु		/* make all access sizes available. */
		u8	c[0x400000 / 1];	/* पढ़ो-only */
		u16	s[0x400000 / 2];	/* पढ़ो-ग_लिखो */
		u32	l[0x400000 / 4];	/* पढ़ो-only */
		u64	d[0x400000 / 8];	/* पढ़ो-only */
	पूर्ण b_बाह्यal_flash;			/* 0xC00000 */
पूर्ण;

/*
 * Field क्रमmats क्रम Error Command Word and Auxiliary Error Command Word
 * of bridge.
 */
काष्ठा bridge_err_cmdword अणु
	जोड़ अणु
		u32		cmd_word;
		काष्ठा अणु
			u32	didn:4,		/* Destination ID  */
				sidn:4,		/* Source ID	   */
				pactyp:4,	/* Packet type	   */
				tnum:5,		/* Trans Number	   */
				coh:1,		/* Coh Transaction */
				ds:2,		/* Data size	   */
				gbr:1,		/* GBR enable	   */
				vbpm:1,		/* VBPM message	   */
				error:1,	/* Error occurred  */
				barr:1,		/* Barrier op	   */
				rsvd:8;
		पूर्ण berr_st;
	पूर्ण berr_un;
पूर्ण;

#घोषणा berr_field	berr_un.berr_st
#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * The values of these macros can and should be crosschecked
 * regularly against the offsets of the like-named fields
 * within the bridge_regs काष्ठाure above.
 */

/* Byte offset macros क्रम Bridge पूर्णांकernal रेजिस्टरs */

#घोषणा BRIDGE_WID_ID		WIDGET_ID
#घोषणा BRIDGE_WID_STAT		WIDGET_STATUS
#घोषणा BRIDGE_WID_ERR_UPPER	WIDGET_ERR_UPPER_ADDR
#घोषणा BRIDGE_WID_ERR_LOWER	WIDGET_ERR_LOWER_ADDR
#घोषणा BRIDGE_WID_CONTROL	WIDGET_CONTROL
#घोषणा BRIDGE_WID_REQ_TIMEOUT	WIDGET_REQ_TIMEOUT
#घोषणा BRIDGE_WID_INT_UPPER	WIDGET_INTDEST_UPPER_ADDR
#घोषणा BRIDGE_WID_INT_LOWER	WIDGET_INTDEST_LOWER_ADDR
#घोषणा BRIDGE_WID_ERR_CMDWORD	WIDGET_ERR_CMD_WORD
#घोषणा BRIDGE_WID_LLP		WIDGET_LLP_CFG
#घोषणा BRIDGE_WID_TFLUSH	WIDGET_TFLUSH

#घोषणा BRIDGE_WID_AUX_ERR	0x00005C	/* Aux Error Command Word */
#घोषणा BRIDGE_WID_RESP_UPPER	0x000064	/* Response Buf Upper Addr */
#घोषणा BRIDGE_WID_RESP_LOWER	0x00006C	/* Response Buf Lower Addr */
#घोषणा BRIDGE_WID_TST_PIN_CTRL 0x000074	/* Test pin control */

#घोषणा BRIDGE_सूची_MAP		0x000084	/* Direct Map reg */

#घोषणा BRIDGE_RAM_PERR		0x000094	/* SSRAM Parity Error */

#घोषणा BRIDGE_ARB		0x0000A4	/* Arbitration Priority reg */

#घोषणा BRIDGE_NIC		0x0000B4	/* Number In A Can */

#घोषणा BRIDGE_BUS_TIMEOUT	0x0000C4	/* Bus Timeout Register */
#घोषणा BRIDGE_PCI_BUS_TIMEOUT	BRIDGE_BUS_TIMEOUT
#घोषणा BRIDGE_PCI_CFG		0x0000CC	/* PCI Type 1 Config reg */
#घोषणा BRIDGE_PCI_ERR_UPPER	0x0000D4	/* PCI error Upper Addr */
#घोषणा BRIDGE_PCI_ERR_LOWER	0x0000DC	/* PCI error Lower Addr */

#घोषणा BRIDGE_INT_STATUS	0x000104	/* Interrupt Status */
#घोषणा BRIDGE_INT_ENABLE	0x00010C	/* Interrupt Enables */
#घोषणा BRIDGE_INT_RST_STAT	0x000114	/* Reset Intr Status */
#घोषणा BRIDGE_INT_MODE		0x00011C	/* Interrupt Mode */
#घोषणा BRIDGE_INT_DEVICE	0x000124	/* Interrupt Device */
#घोषणा BRIDGE_INT_HOST_ERR	0x00012C	/* Host Error Field */

#घोषणा BRIDGE_INT_ADDR0	0x000134	/* Host Address Reg */
#घोषणा BRIDGE_INT_ADDR_OFF	0x000008	/* Host Addr offset (1..7) */
#घोषणा BRIDGE_INT_ADDR(x)	(BRIDGE_INT_ADDR0+(x)*BRIDGE_INT_ADDR_OFF)

#घोषणा BRIDGE_DEVICE0		0x000204	/* Device 0 */
#घोषणा BRIDGE_DEVICE_OFF	0x000008	/* Device offset (1..7) */
#घोषणा BRIDGE_DEVICE(x)	(BRIDGE_DEVICE0+(x)*BRIDGE_DEVICE_OFF)

#घोषणा BRIDGE_WR_REQ_BUF0	0x000244	/* Write Request Buffer 0 */
#घोषणा BRIDGE_WR_REQ_BUF_OFF	0x000008	/* Buffer Offset (1..7) */
#घोषणा BRIDGE_WR_REQ_BUF(x)	(BRIDGE_WR_REQ_BUF0+(x)*BRIDGE_WR_REQ_BUF_OFF)

#घोषणा BRIDGE_EVEN_RESP	0x000284	/* Even Device Response Buf */
#घोषणा BRIDGE_ODD_RESP		0x00028C	/* Odd Device Response Buf */

#घोषणा BRIDGE_RESP_STATUS	0x000294	/* Read Response Status reg */
#घोषणा BRIDGE_RESP_CLEAR	0x00029C	/* Read Response Clear reg */

/* Byte offset macros क्रम Bridge I/O space */

#घोषणा BRIDGE_ATE_RAM		0x00010000	/* Internal Addr Xlat Ram */

#घोषणा BRIDGE_TYPE0_CFG_DEV0	0x00020000	/* Type 0 Cfg, Device 0 */
#घोषणा BRIDGE_TYPE0_CFG_SLOT_OFF	0x00001000	/* Type 0 Cfg Slot Offset (1..7) */
#घोषणा BRIDGE_TYPE0_CFG_FUNC_OFF	0x00000100	/* Type 0 Cfg Func Offset (1..7) */
#घोषणा BRIDGE_TYPE0_CFG_DEV(s)		(BRIDGE_TYPE0_CFG_DEV0+\
					 (s)*BRIDGE_TYPE0_CFG_SLOT_OFF)
#घोषणा BRIDGE_TYPE0_CFG_DEVF(s, f)	(BRIDGE_TYPE0_CFG_DEV0+\
					 (s)*BRIDGE_TYPE0_CFG_SLOT_OFF+\
					 (f)*BRIDGE_TYPE0_CFG_FUNC_OFF)

#घोषणा BRIDGE_TYPE1_CFG	0x00028000	/* Type 1 Cfg space */

#घोषणा BRIDGE_PCI_IACK		0x00030000	/* PCI Interrupt Ack */
#घोषणा BRIDGE_EXT_SSRAM	0x00080000	/* Extern SSRAM (ATE) */

/* Byte offset macros क्रम Bridge device IO spaces */

#घोषणा BRIDGE_DEV_CNT		8	/* Up to 8 devices per bridge */
#घोषणा BRIDGE_DEVIO0		0x00200000	/* Device IO 0 Addr */
#घोषणा BRIDGE_DEVIO1		0x00400000	/* Device IO 1 Addr */
#घोषणा BRIDGE_DEVIO2		0x00600000	/* Device IO 2 Addr */
#घोषणा BRIDGE_DEVIO_OFF	0x00100000	/* Device IO Offset (3..7) */

#घोषणा BRIDGE_DEVIO_2MB	0x00200000	/* Device IO Offset (0..1) */
#घोषणा BRIDGE_DEVIO_1MB	0x00100000	/* Device IO Offset (2..7) */

#घोषणा BRIDGE_DEVIO(x)		((x)<=1 ? BRIDGE_DEVIO0+(x)*BRIDGE_DEVIO_2MB : BRIDGE_DEVIO2+((x)-2)*BRIDGE_DEVIO_1MB)

#घोषणा BRIDGE_EXTERNAL_FLASH	0x00C00000	/* External Flash PROMS */

/* ========================================================================
 *    Bridge रेजिस्टर bit field definitions
 */

/* Widget part number of bridge */
#घोषणा BRIDGE_WIDGET_PART_NUM		0xc002
#घोषणा XBRIDGE_WIDGET_PART_NUM		0xd002

/* Manufacturer of bridge */
#घोषणा BRIDGE_WIDGET_MFGR_NUM		0x036
#घोषणा XBRIDGE_WIDGET_MFGR_NUM		0x024

/* Revision numbers क्रम known Bridge revisions */
#घोषणा BRIDGE_REV_A			0x1
#घोषणा BRIDGE_REV_B			0x2
#घोषणा BRIDGE_REV_C			0x3
#घोषणा BRIDGE_REV_D			0x4

/* Bridge widget status रेजिस्टर bits definition */

#घोषणा BRIDGE_STAT_LLP_REC_CNT		(0xFFu << 24)
#घोषणा BRIDGE_STAT_LLP_TX_CNT		(0xFF << 16)
#घोषणा BRIDGE_STAT_FLASH_SELECT	(0x1 << 6)
#घोषणा BRIDGE_STAT_PCI_GIO_N		(0x1 << 5)
#घोषणा BRIDGE_STAT_PENDING		(0x1F << 0)

/* Bridge widget control रेजिस्टर bits definition */
#घोषणा BRIDGE_CTRL_FLASH_WR_EN		(0x1ul << 31)
#घोषणा BRIDGE_CTRL_EN_CLK50		(0x1 << 30)
#घोषणा BRIDGE_CTRL_EN_CLK40		(0x1 << 29)
#घोषणा BRIDGE_CTRL_EN_CLK33		(0x1 << 28)
#घोषणा BRIDGE_CTRL_RST(n)		((n) << 24)
#घोषणा BRIDGE_CTRL_RST_MASK		(BRIDGE_CTRL_RST(0xF))
#घोषणा BRIDGE_CTRL_RST_PIN(x)		(BRIDGE_CTRL_RST(0x1 << (x)))
#घोषणा BRIDGE_CTRL_IO_SWAP		(0x1 << 23)
#घोषणा BRIDGE_CTRL_MEM_SWAP		(0x1 << 22)
#घोषणा BRIDGE_CTRL_PAGE_SIZE		(0x1 << 21)
#घोषणा BRIDGE_CTRL_SS_PAR_BAD		(0x1 << 20)
#घोषणा BRIDGE_CTRL_SS_PAR_EN		(0x1 << 19)
#घोषणा BRIDGE_CTRL_SSRAM_SIZE(n)	((n) << 17)
#घोषणा BRIDGE_CTRL_SSRAM_SIZE_MASK	(BRIDGE_CTRL_SSRAM_SIZE(0x3))
#घोषणा BRIDGE_CTRL_SSRAM_512K		(BRIDGE_CTRL_SSRAM_SIZE(0x3))
#घोषणा BRIDGE_CTRL_SSRAM_128K		(BRIDGE_CTRL_SSRAM_SIZE(0x2))
#घोषणा BRIDGE_CTRL_SSRAM_64K		(BRIDGE_CTRL_SSRAM_SIZE(0x1))
#घोषणा BRIDGE_CTRL_SSRAM_1K		(BRIDGE_CTRL_SSRAM_SIZE(0x0))
#घोषणा BRIDGE_CTRL_F_BAD_PKT		(0x1 << 16)
#घोषणा BRIDGE_CTRL_LLP_XBAR_CRD(n)	((n) << 12)
#घोषणा BRIDGE_CTRL_LLP_XBAR_CRD_MASK	(BRIDGE_CTRL_LLP_XBAR_CRD(0xf))
#घोषणा BRIDGE_CTRL_CLR_RLLP_CNT	(0x1 << 11)
#घोषणा BRIDGE_CTRL_CLR_TLLP_CNT	(0x1 << 10)
#घोषणा BRIDGE_CTRL_SYS_END		(0x1 << 9)
#घोषणा BRIDGE_CTRL_MAX_TRANS(n)	((n) << 4)
#घोषणा BRIDGE_CTRL_MAX_TRANS_MASK	(BRIDGE_CTRL_MAX_TRANS(0x1f))
#घोषणा BRIDGE_CTRL_WIDGET_ID(n)	((n) << 0)
#घोषणा BRIDGE_CTRL_WIDGET_ID_MASK	(BRIDGE_CTRL_WIDGET_ID(0xf))

/* Bridge Response buffer Error Upper Register bit fields definition */
#घोषणा BRIDGE_RESP_ERRUPPR_DEVNUM_SHFT (20)
#घोषणा BRIDGE_RESP_ERRUPPR_DEVNUM_MASK (0x7 << BRIDGE_RESP_ERRUPPR_DEVNUM_SHFT)
#घोषणा BRIDGE_RESP_ERRUPPR_BUFNUM_SHFT (16)
#घोषणा BRIDGE_RESP_ERRUPPR_BUFNUM_MASK (0xF << BRIDGE_RESP_ERRUPPR_BUFNUM_SHFT)
#घोषणा BRIDGE_RESP_ERRRUPPR_BUFMASK	(0xFFFF)

#घोषणा BRIDGE_RESP_ERRUPPR_BUFNUM(x)	\
			(((x) & BRIDGE_RESP_ERRUPPR_BUFNUM_MASK) >> \
				BRIDGE_RESP_ERRUPPR_BUFNUM_SHFT)

#घोषणा BRIDGE_RESP_ERRUPPR_DEVICE(x)	\
			(((x) &	 BRIDGE_RESP_ERRUPPR_DEVNUM_MASK) >> \
				 BRIDGE_RESP_ERRUPPR_DEVNUM_SHFT)

/* Bridge direct mapping रेजिस्टर bits definition */
#घोषणा BRIDGE_सूचीMAP_W_ID_SHFT		20
#घोषणा BRIDGE_सूचीMAP_W_ID		(0xf << BRIDGE_सूचीMAP_W_ID_SHFT)
#घोषणा BRIDGE_सूचीMAP_RMF_64		(0x1 << 18)
#घोषणा BRIDGE_सूचीMAP_ADD512		(0x1 << 17)
#घोषणा BRIDGE_सूचीMAP_OFF		(0x1ffff << 0)
#घोषणा BRIDGE_सूचीMAP_OFF_ADDRSHFT	(31)	/* lsbit of सूचीMAP_OFF is xtalk address bit 31 */

/* Bridge Arbitration रेजिस्टर bits definition */
#घोषणा BRIDGE_ARB_REQ_WAIT_TICK(x)	((x) << 16)
#घोषणा BRIDGE_ARB_REQ_WAIT_TICK_MASK	BRIDGE_ARB_REQ_WAIT_TICK(0x3)
#घोषणा BRIDGE_ARB_REQ_WAIT_EN(x)	((x) << 8)
#घोषणा BRIDGE_ARB_REQ_WAIT_EN_MASK	BRIDGE_ARB_REQ_WAIT_EN(0xff)
#घोषणा BRIDGE_ARB_FREEZE_GNT		(1 << 6)
#घोषणा BRIDGE_ARB_HPRI_RING_B2		(1 << 5)
#घोषणा BRIDGE_ARB_HPRI_RING_B1		(1 << 4)
#घोषणा BRIDGE_ARB_HPRI_RING_B0		(1 << 3)
#घोषणा BRIDGE_ARB_LPRI_RING_B2		(1 << 2)
#घोषणा BRIDGE_ARB_LPRI_RING_B1		(1 << 1)
#घोषणा BRIDGE_ARB_LPRI_RING_B0		(1 << 0)

/* Bridge Bus समय-out रेजिस्टर bits definition */
#घोषणा BRIDGE_BUS_PCI_RETRY_HLD(x)	((x) << 16)
#घोषणा BRIDGE_BUS_PCI_RETRY_HLD_MASK	BRIDGE_BUS_PCI_RETRY_HLD(0x1f)
#घोषणा BRIDGE_BUS_GIO_TIMEOUT		(1 << 12)
#घोषणा BRIDGE_BUS_PCI_RETRY_CNT(x)	((x) << 0)
#घोषणा BRIDGE_BUS_PCI_RETRY_MASK	BRIDGE_BUS_PCI_RETRY_CNT(0x3ff)

/* Bridge पूर्णांकerrupt status रेजिस्टर bits definition */
#घोषणा BRIDGE_ISR_MULTI_ERR		(0x1u << 31)
#घोषणा BRIDGE_ISR_PMU_ESIZE_FAULT	(0x1 << 30)
#घोषणा BRIDGE_ISR_UNEXP_RESP		(0x1 << 29)
#घोषणा BRIDGE_ISR_BAD_XRESP_PKT	(0x1 << 28)
#घोषणा BRIDGE_ISR_BAD_XREQ_PKT		(0x1 << 27)
#घोषणा BRIDGE_ISR_RESP_XTLK_ERR	(0x1 << 26)
#घोषणा BRIDGE_ISR_REQ_XTLK_ERR		(0x1 << 25)
#घोषणा BRIDGE_ISR_INVLD_ADDR		(0x1 << 24)
#घोषणा BRIDGE_ISR_UNSUPPORTED_XOP	(0x1 << 23)
#घोषणा BRIDGE_ISR_XREQ_FIFO_OFLOW	(0x1 << 22)
#घोषणा BRIDGE_ISR_LLP_REC_SNERR	(0x1 << 21)
#घोषणा BRIDGE_ISR_LLP_REC_CBERR	(0x1 << 20)
#घोषणा BRIDGE_ISR_LLP_RCTY		(0x1 << 19)
#घोषणा BRIDGE_ISR_LLP_TX_RETRY		(0x1 << 18)
#घोषणा BRIDGE_ISR_LLP_TCTY		(0x1 << 17)
#घोषणा BRIDGE_ISR_SSRAM_PERR		(0x1 << 16)
#घोषणा BRIDGE_ISR_PCI_ABORT		(0x1 << 15)
#घोषणा BRIDGE_ISR_PCI_PARITY		(0x1 << 14)
#घोषणा BRIDGE_ISR_PCI_SERR		(0x1 << 13)
#घोषणा BRIDGE_ISR_PCI_PERR		(0x1 << 12)
#घोषणा BRIDGE_ISR_PCI_MST_TIMEOUT	(0x1 << 11)
#घोषणा BRIDGE_ISR_GIO_MST_TIMEOUT	BRIDGE_ISR_PCI_MST_TIMEOUT
#घोषणा BRIDGE_ISR_PCI_RETRY_CNT	(0x1 << 10)
#घोषणा BRIDGE_ISR_XREAD_REQ_TIMEOUT	(0x1 << 9)
#घोषणा BRIDGE_ISR_GIO_B_ENBL_ERR	(0x1 << 8)
#घोषणा BRIDGE_ISR_INT_MSK		(0xff << 0)
#घोषणा BRIDGE_ISR_INT(x)		(0x1 << (x))

#घोषणा BRIDGE_ISR_LINK_ERROR		\
		(BRIDGE_ISR_LLP_REC_SNERR|BRIDGE_ISR_LLP_REC_CBERR|	\
		 BRIDGE_ISR_LLP_RCTY|BRIDGE_ISR_LLP_TX_RETRY|		\
		 BRIDGE_ISR_LLP_TCTY)

#घोषणा BRIDGE_ISR_PCIBUS_PIOERR	\
		(BRIDGE_ISR_PCI_MST_TIMEOUT|BRIDGE_ISR_PCI_ABORT)

#घोषणा BRIDGE_ISR_PCIBUS_ERROR		\
		(BRIDGE_ISR_PCIBUS_PIOERR|BRIDGE_ISR_PCI_PERR|		\
		 BRIDGE_ISR_PCI_SERR|BRIDGE_ISR_PCI_RETRY_CNT|		\
		 BRIDGE_ISR_PCI_PARITY)

#घोषणा BRIDGE_ISR_XTALK_ERROR		\
		(BRIDGE_ISR_XREAD_REQ_TIMEOUT|BRIDGE_ISR_XREQ_FIFO_OFLOW|\
		 BRIDGE_ISR_UNSUPPORTED_XOP|BRIDGE_ISR_INVLD_ADDR|	\
		 BRIDGE_ISR_REQ_XTLK_ERR|BRIDGE_ISR_RESP_XTLK_ERR|	\
		 BRIDGE_ISR_BAD_XREQ_PKT|BRIDGE_ISR_BAD_XRESP_PKT|	\
		 BRIDGE_ISR_UNEXP_RESP)

#घोषणा BRIDGE_ISR_ERRORS		\
		(BRIDGE_ISR_LINK_ERROR|BRIDGE_ISR_PCIBUS_ERROR|		\
		 BRIDGE_ISR_XTALK_ERROR|BRIDGE_ISR_SSRAM_PERR|		\
		 BRIDGE_ISR_PMU_ESIZE_FAULT)

/*
 * List of Errors which are fatal and समाप्त the प्रणाली
 */
#घोषणा BRIDGE_ISR_ERROR_FATAL		\
		((BRIDGE_ISR_XTALK_ERROR & ~BRIDGE_ISR_XREAD_REQ_TIMEOUT)|\
		 BRIDGE_ISR_PCI_SERR|BRIDGE_ISR_PCI_PARITY )

#घोषणा BRIDGE_ISR_ERROR_DUMP		\
		(BRIDGE_ISR_PCIBUS_ERROR|BRIDGE_ISR_PMU_ESIZE_FAULT|	\
		 BRIDGE_ISR_XTALK_ERROR|BRIDGE_ISR_SSRAM_PERR)

/* Bridge पूर्णांकerrupt enable रेजिस्टर bits definition */
#घोषणा BRIDGE_IMR_UNEXP_RESP		BRIDGE_ISR_UNEXP_RESP
#घोषणा BRIDGE_IMR_PMU_ESIZE_FAULT	BRIDGE_ISR_PMU_ESIZE_FAULT
#घोषणा BRIDGE_IMR_BAD_XRESP_PKT	BRIDGE_ISR_BAD_XRESP_PKT
#घोषणा BRIDGE_IMR_BAD_XREQ_PKT		BRIDGE_ISR_BAD_XREQ_PKT
#घोषणा BRIDGE_IMR_RESP_XTLK_ERR	BRIDGE_ISR_RESP_XTLK_ERR
#घोषणा BRIDGE_IMR_REQ_XTLK_ERR		BRIDGE_ISR_REQ_XTLK_ERR
#घोषणा BRIDGE_IMR_INVLD_ADDR		BRIDGE_ISR_INVLD_ADDR
#घोषणा BRIDGE_IMR_UNSUPPORTED_XOP	BRIDGE_ISR_UNSUPPORTED_XOP
#घोषणा BRIDGE_IMR_XREQ_FIFO_OFLOW	BRIDGE_ISR_XREQ_FIFO_OFLOW
#घोषणा BRIDGE_IMR_LLP_REC_SNERR	BRIDGE_ISR_LLP_REC_SNERR
#घोषणा BRIDGE_IMR_LLP_REC_CBERR	BRIDGE_ISR_LLP_REC_CBERR
#घोषणा BRIDGE_IMR_LLP_RCTY		BRIDGE_ISR_LLP_RCTY
#घोषणा BRIDGE_IMR_LLP_TX_RETRY		BRIDGE_ISR_LLP_TX_RETRY
#घोषणा BRIDGE_IMR_LLP_TCTY		BRIDGE_ISR_LLP_TCTY
#घोषणा BRIDGE_IMR_SSRAM_PERR		BRIDGE_ISR_SSRAM_PERR
#घोषणा BRIDGE_IMR_PCI_ABORT		BRIDGE_ISR_PCI_ABORT
#घोषणा BRIDGE_IMR_PCI_PARITY		BRIDGE_ISR_PCI_PARITY
#घोषणा BRIDGE_IMR_PCI_SERR		BRIDGE_ISR_PCI_SERR
#घोषणा BRIDGE_IMR_PCI_PERR		BRIDGE_ISR_PCI_PERR
#घोषणा BRIDGE_IMR_PCI_MST_TIMEOUT	BRIDGE_ISR_PCI_MST_TIMEOUT
#घोषणा BRIDGE_IMR_GIO_MST_TIMEOUT	BRIDGE_ISR_GIO_MST_TIMEOUT
#घोषणा BRIDGE_IMR_PCI_RETRY_CNT	BRIDGE_ISR_PCI_RETRY_CNT
#घोषणा BRIDGE_IMR_XREAD_REQ_TIMEOUT	BRIDGE_ISR_XREAD_REQ_TIMEOUT
#घोषणा BRIDGE_IMR_GIO_B_ENBL_ERR	BRIDGE_ISR_GIO_B_ENBL_ERR
#घोषणा BRIDGE_IMR_INT_MSK		BRIDGE_ISR_INT_MSK
#घोषणा BRIDGE_IMR_INT(x)		BRIDGE_ISR_INT(x)

/* Bridge पूर्णांकerrupt reset रेजिस्टर bits definition */
#घोषणा BRIDGE_IRR_MULTI_CLR		(0x1 << 6)
#घोषणा BRIDGE_IRR_CRP_GRP_CLR		(0x1 << 5)
#घोषणा BRIDGE_IRR_RESP_BUF_GRP_CLR	(0x1 << 4)
#घोषणा BRIDGE_IRR_REQ_DSP_GRP_CLR	(0x1 << 3)
#घोषणा BRIDGE_IRR_LLP_GRP_CLR		(0x1 << 2)
#घोषणा BRIDGE_IRR_SSRAM_GRP_CLR	(0x1 << 1)
#घोषणा BRIDGE_IRR_PCI_GRP_CLR		(0x1 << 0)
#घोषणा BRIDGE_IRR_GIO_GRP_CLR		(0x1 << 0)
#घोषणा BRIDGE_IRR_ALL_CLR		0x7f

#घोषणा BRIDGE_IRR_CRP_GRP		(BRIDGE_ISR_UNEXP_RESP | \
					 BRIDGE_ISR_XREQ_FIFO_OFLOW)
#घोषणा BRIDGE_IRR_RESP_BUF_GRP		(BRIDGE_ISR_BAD_XRESP_PKT | \
					 BRIDGE_ISR_RESP_XTLK_ERR | \
					 BRIDGE_ISR_XREAD_REQ_TIMEOUT)
#घोषणा BRIDGE_IRR_REQ_DSP_GRP		(BRIDGE_ISR_UNSUPPORTED_XOP | \
					 BRIDGE_ISR_BAD_XREQ_PKT | \
					 BRIDGE_ISR_REQ_XTLK_ERR | \
					 BRIDGE_ISR_INVLD_ADDR)
#घोषणा BRIDGE_IRR_LLP_GRP		(BRIDGE_ISR_LLP_REC_SNERR | \
					 BRIDGE_ISR_LLP_REC_CBERR | \
					 BRIDGE_ISR_LLP_RCTY | \
					 BRIDGE_ISR_LLP_TX_RETRY | \
					 BRIDGE_ISR_LLP_TCTY)
#घोषणा BRIDGE_IRR_SSRAM_GRP		(BRIDGE_ISR_SSRAM_PERR | \
					 BRIDGE_ISR_PMU_ESIZE_FAULT)
#घोषणा BRIDGE_IRR_PCI_GRP		(BRIDGE_ISR_PCI_ABORT | \
					 BRIDGE_ISR_PCI_PARITY | \
					 BRIDGE_ISR_PCI_SERR | \
					 BRIDGE_ISR_PCI_PERR | \
					 BRIDGE_ISR_PCI_MST_TIMEOUT | \
					 BRIDGE_ISR_PCI_RETRY_CNT)

#घोषणा BRIDGE_IRR_GIO_GRP		(BRIDGE_ISR_GIO_B_ENBL_ERR | \
					 BRIDGE_ISR_GIO_MST_TIMEOUT)

/* Bridge INT_DEV रेजिस्टर bits definition */
#घोषणा BRIDGE_INT_DEV_SHFT(n)		((n)*3)
#घोषणा BRIDGE_INT_DEV_MASK(n)		(0x7 << BRIDGE_INT_DEV_SHFT(n))
#घोषणा BRIDGE_INT_DEV_SET(_dev, _line) (_dev << BRIDGE_INT_DEV_SHFT(_line))

/* Bridge पूर्णांकerrupt(x) रेजिस्टर bits definition */
#घोषणा BRIDGE_INT_ADDR_HOST		0x0003FF00
#घोषणा BRIDGE_INT_ADDR_FLD		0x000000FF

#घोषणा BRIDGE_TMO_PCI_RETRY_HLD_MASK	0x1f0000
#घोषणा BRIDGE_TMO_GIO_TIMEOUT_MASK	0x001000
#घोषणा BRIDGE_TMO_PCI_RETRY_CNT_MASK	0x0003ff

#घोषणा BRIDGE_TMO_PCI_RETRY_CNT_MAX	0x3ff

/*
 * The NASID should be shअगरted by this amount and stored पूर्णांकo the
 * पूर्णांकerrupt(x) रेजिस्टर.
 */
#घोषणा BRIDGE_INT_ADDR_NASID_SHFT	8

/*
 * The BRIDGE_INT_ADDR_DEST_IO bit should be set to send an पूर्णांकerrupt to
 * memory.
 */
#घोषणा BRIDGE_INT_ADDR_DEST_IO		(1 << 17)
#घोषणा BRIDGE_INT_ADDR_DEST_MEM	0
#घोषणा BRIDGE_INT_ADDR_MASK		(1 << 17)

/* Bridge device(x) रेजिस्टर bits definition */
#घोषणा BRIDGE_DEV_ERR_LOCK_EN		0x10000000
#घोषणा BRIDGE_DEV_PAGE_CHK_DIS		0x08000000
#घोषणा BRIDGE_DEV_FORCE_PCI_PAR	0x04000000
#घोषणा BRIDGE_DEV_VIRTUAL_EN		0x02000000
#घोषणा BRIDGE_DEV_PMU_WRGA_EN		0x01000000
#घोषणा BRIDGE_DEV_सूची_WRGA_EN		0x00800000
#घोषणा BRIDGE_DEV_DEV_SIZE		0x00400000
#घोषणा BRIDGE_DEV_RT			0x00200000
#घोषणा BRIDGE_DEV_SWAP_PMU		0x00100000
#घोषणा BRIDGE_DEV_SWAP_सूची		0x00080000
#घोषणा BRIDGE_DEV_PREF			0x00040000
#घोषणा BRIDGE_DEV_PRECISE		0x00020000
#घोषणा BRIDGE_DEV_COH			0x00010000
#घोषणा BRIDGE_DEV_BARRIER		0x00008000
#घोषणा BRIDGE_DEV_GBR			0x00004000
#घोषणा BRIDGE_DEV_DEV_SWAP		0x00002000
#घोषणा BRIDGE_DEV_DEV_IO_MEM		0x00001000
#घोषणा BRIDGE_DEV_OFF_MASK		0x00000fff
#घोषणा BRIDGE_DEV_OFF_ADDR_SHFT	20

#घोषणा BRIDGE_DEV_PMU_BITS		(BRIDGE_DEV_PMU_WRGA_EN		| \
					 BRIDGE_DEV_SWAP_PMU)
#घोषणा BRIDGE_DEV_D32_BITS		(BRIDGE_DEV_सूची_WRGA_EN		| \
					 BRIDGE_DEV_SWAP_सूची		| \
					 BRIDGE_DEV_PREF		| \
					 BRIDGE_DEV_PRECISE		| \
					 BRIDGE_DEV_COH			| \
					 BRIDGE_DEV_BARRIER)
#घोषणा BRIDGE_DEV_D64_BITS		(BRIDGE_DEV_सूची_WRGA_EN		| \
					 BRIDGE_DEV_SWAP_सूची		| \
					 BRIDGE_DEV_COH			| \
					 BRIDGE_DEV_BARRIER)

/* Bridge Error Upper रेजिस्टर bit field definition */
#घोषणा BRIDGE_ERRUPPR_DEVMASTER	(0x1 << 20)	/* Device was master */
#घोषणा BRIDGE_ERRUPPR_PCIVDEV		(0x1 << 19)	/* Virtual Req value */
#घोषणा BRIDGE_ERRUPPR_DEVNUM_SHFT	(16)
#घोषणा BRIDGE_ERRUPPR_DEVNUM_MASK	(0x7 << BRIDGE_ERRUPPR_DEVNUM_SHFT)
#घोषणा BRIDGE_ERRUPPR_DEVICE(err)	(((err) >> BRIDGE_ERRUPPR_DEVNUM_SHFT) & 0x7)
#घोषणा BRIDGE_ERRUPPR_ADDRMASK		(0xFFFF)

/* Bridge पूर्णांकerrupt mode रेजिस्टर bits definition */
#घोषणा BRIDGE_INTMODE_CLR_PKT_EN(x)	(0x1 << (x))

/* this should be written to the xbow's link_control(x) रेजिस्टर */
#घोषणा BRIDGE_CREDIT	3

/* RRB assignment रेजिस्टर */
#घोषणा BRIDGE_RRB_EN	0x8	/* after shअगरting करोwn */
#घोषणा BRIDGE_RRB_DEV	0x7	/* after shअगरting करोwn */
#घोषणा BRIDGE_RRB_VDEV 0x4	/* after shअगरting करोwn */
#घोषणा BRIDGE_RRB_PDEV 0x3	/* after shअगरting करोwn */

/* RRB status रेजिस्टर */
#घोषणा BRIDGE_RRB_VALID(r)	(0x00010000<<(r))
#घोषणा BRIDGE_RRB_INUSE(r)	(0x00000001<<(r))

/* RRB clear रेजिस्टर */
#घोषणा BRIDGE_RRB_CLEAR(r)	(0x00000001<<(r))

/* xbox प्रणाली controller declarations */
#घोषणा XBOX_BRIDGE_WID		8
#घोषणा FLASH_PROM1_BASE	0xE00000 /* To पढ़ो the xbox sysctlr status */
#घोषणा XBOX_RPS_EXISTS		1 << 6	 /* RPS bit in status रेजिस्टर */
#घोषणा XBOX_RPS_FAIL		1 << 4	 /* RPS status bit in रेजिस्टर */

/* ========================================================================
 */
/*
 * Macros क्रम Xtalk to Bridge bus (PCI/GIO) PIO
 * refer to section 4.2.1 of Bridge Spec क्रम xtalk to PCI/GIO PIO mappings
 */
/* XTALK addresses that map पूर्णांकo Bridge Bus addr space */
#घोषणा BRIDGE_PIO32_XTALK_ALIAS_BASE	0x000040000000L
#घोषणा BRIDGE_PIO32_XTALK_ALIAS_LIMIT	0x00007FFFFFFFL
#घोषणा BRIDGE_PIO64_XTALK_ALIAS_BASE	0x000080000000L
#घोषणा BRIDGE_PIO64_XTALK_ALIAS_LIMIT	0x0000BFFFFFFFL
#घोषणा BRIDGE_PCIIO_XTALK_ALIAS_BASE	0x000100000000L
#घोषणा BRIDGE_PCIIO_XTALK_ALIAS_LIMIT	0x0001FFFFFFFFL

/* Ranges of PCI bus space that can be accessed via PIO from xtalk */
#घोषणा BRIDGE_MIN_PIO_ADDR_MEM		0x00000000	/* 1G PCI memory space */
#घोषणा BRIDGE_MAX_PIO_ADDR_MEM		0x3fffffff
#घोषणा BRIDGE_MIN_PIO_ADDR_IO		0x00000000	/* 4G PCI IO space */
#घोषणा BRIDGE_MAX_PIO_ADDR_IO		0xffffffff

/* XTALK addresses that map पूर्णांकo PCI addresses */
#घोषणा BRIDGE_PCI_MEM32_BASE		BRIDGE_PIO32_XTALK_ALIAS_BASE
#घोषणा BRIDGE_PCI_MEM32_LIMIT		BRIDGE_PIO32_XTALK_ALIAS_LIMIT
#घोषणा BRIDGE_PCI_MEM64_BASE		BRIDGE_PIO64_XTALK_ALIAS_BASE
#घोषणा BRIDGE_PCI_MEM64_LIMIT		BRIDGE_PIO64_XTALK_ALIAS_LIMIT
#घोषणा BRIDGE_PCI_IO_BASE		BRIDGE_PCIIO_XTALK_ALIAS_BASE
#घोषणा BRIDGE_PCI_IO_LIMIT		BRIDGE_PCIIO_XTALK_ALIAS_LIMIT

/*
 * Macros क्रम Bridge bus (PCI/GIO) to Xtalk DMA
 */
/* Bridge Bus DMA addresses */
#घोषणा BRIDGE_LOCAL_BASE		0
#घोषणा BRIDGE_DMA_MAPPED_BASE		0x40000000
#घोषणा BRIDGE_DMA_MAPPED_SIZE		0x40000000	/* 1G Bytes */
#घोषणा BRIDGE_DMA_सूचीECT_BASE		0x80000000
#घोषणा BRIDGE_DMA_सूचीECT_SIZE		0x80000000	/* 2G Bytes */

#घोषणा PCI32_LOCAL_BASE		BRIDGE_LOCAL_BASE

/* PCI addresses of regions decoded by Bridge क्रम DMA */
#घोषणा PCI32_MAPPED_BASE		BRIDGE_DMA_MAPPED_BASE
#घोषणा PCI32_सूचीECT_BASE		BRIDGE_DMA_सूचीECT_BASE

#घोषणा IS_PCI32_LOCAL(x)	((uदीर्घ_t)(x) < PCI32_MAPPED_BASE)
#घोषणा IS_PCI32_MAPPED(x)	((uदीर्घ_t)(x) < PCI32_सूचीECT_BASE && \
					(uदीर्घ_t)(x) >= PCI32_MAPPED_BASE)
#घोषणा IS_PCI32_सूचीECT(x)	((uदीर्घ_t)(x) >= PCI32_MAPPED_BASE)
#घोषणा IS_PCI64(x)		((uदीर्घ_t)(x) >= PCI64_BASE)

/*
 * The GIO address space.
 */
/* Xtalk to GIO PIO */
#घोषणा BRIDGE_GIO_MEM32_BASE		BRIDGE_PIO32_XTALK_ALIAS_BASE
#घोषणा BRIDGE_GIO_MEM32_LIMIT		BRIDGE_PIO32_XTALK_ALIAS_LIMIT

#घोषणा GIO_LOCAL_BASE			BRIDGE_LOCAL_BASE

/* GIO addresses of regions decoded by Bridge क्रम DMA */
#घोषणा GIO_MAPPED_BASE			BRIDGE_DMA_MAPPED_BASE
#घोषणा GIO_सूचीECT_BASE			BRIDGE_DMA_सूचीECT_BASE

#घोषणा IS_GIO_LOCAL(x)		((uदीर्घ_t)(x) < GIO_MAPPED_BASE)
#घोषणा IS_GIO_MAPPED(x)	((uदीर्घ_t)(x) < GIO_सूचीECT_BASE && \
					(uदीर्घ_t)(x) >= GIO_MAPPED_BASE)
#घोषणा IS_GIO_सूचीECT(x)	((uदीर्घ_t)(x) >= GIO_MAPPED_BASE)

/* PCI to xtalk mapping */

/* given a सूची_OFF value and a pci/gio 32 bits direct address, determine
 * which xtalk address is accessed
 */
#घोषणा BRIDGE_सूचीECT_32_SEG_SIZE	BRIDGE_DMA_सूचीECT_SIZE
#घोषणा BRIDGE_सूचीECT_32_TO_XTALK(dir_off,adr)		\
	((dir_off) * BRIDGE_सूचीECT_32_SEG_SIZE +	\
		((adr) & (BRIDGE_सूचीECT_32_SEG_SIZE - 1)) + PHYS_RAMBASE)

/* 64-bit address attribute masks */
#घोषणा PCI64_ATTR_TARG_MASK	0xf000000000000000
#घोषणा PCI64_ATTR_TARG_SHFT	60
#घोषणा PCI64_ATTR_PREF		0x0800000000000000
#घोषणा PCI64_ATTR_PREC		0x0400000000000000
#घोषणा PCI64_ATTR_VIRTUAL	0x0200000000000000
#घोषणा PCI64_ATTR_BAR		0x0100000000000000
#घोषणा PCI64_ATTR_RMF_MASK	0x00ff000000000000
#घोषणा PCI64_ATTR_RMF_SHFT	48

काष्ठा bridge_controller अणु
	काष्ठा resource		busn;
	काष्ठा bridge_regs	*base;
	अचिन्हित दीर्घ		baddr;
	अचिन्हित दीर्घ		पूर्णांकr_addr;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	अचिन्हित पूर्णांक		pci_पूर्णांक[8][2];
	अचिन्हित पूर्णांक		पूर्णांक_mapping[8][2];
	u32			ioc3_sid[8];
	nasid_t			nasid;
पूर्ण;

#घोषणा BRIDGE_CONTROLLER(bus) \
	((काष्ठा bridge_controller *)((bus)->sysdata))

#घोषणा bridge_पढ़ो(bc, reg)		__raw_पढ़ोl(&bc->base->reg)
#घोषणा bridge_ग_लिखो(bc, reg, val)	__raw_ग_लिखोl(val, &bc->base->reg)
#घोषणा bridge_set(bc, reg, val)	\
	__raw_ग_लिखोl(__raw_पढ़ोl(&bc->base->reg) | (val), &bc->base->reg)
#घोषणा bridge_clr(bc, reg, val)	\
	__raw_ग_लिखोl(__raw_पढ़ोl(&bc->base->reg) & ~(val), &bc->base->reg)

#पूर्ण_अगर /* _ASM_PCI_BRIDGE_H */
