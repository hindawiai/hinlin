<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Fusb300 UDC (USB gadget)
 *
 * Copyright (C) 2010 Faraday Technology Corp.
 *
 * Author : Yuan-hsin Chen <yhchen@faraday-tech.com>
 */


#अगर_अघोषित __FUSB300_UDC_H__
#घोषणा __FUSB300_UDC_H__

#समावेश <linux/kernel.h>

#घोषणा FUSB300_OFFSET_GCR		0x00
#घोषणा FUSB300_OFFSET_GTM		0x04
#घोषणा FUSB300_OFFSET_DAR		0x08
#घोषणा FUSB300_OFFSET_CSR		0x0C
#घोषणा FUSB300_OFFSET_CXPORT		0x10
#घोषणा FUSB300_OFFSET_EPSET0(n)	(0x20 + (n - 1) * 0x30)
#घोषणा FUSB300_OFFSET_EPSET1(n)	(0x24 + (n - 1) * 0x30)
#घोषणा FUSB300_OFFSET_EPSET2(n)	(0x28 + (n - 1) * 0x30)
#घोषणा FUSB300_OFFSET_EPFFR(n)		(0x2c + (n - 1) * 0x30)
#घोषणा FUSB300_OFFSET_EPSTRID(n)	(0x40 + (n - 1) * 0x30)
#घोषणा FUSB300_OFFSET_HSPTM		0x300
#घोषणा FUSB300_OFFSET_HSCR		0x304
#घोषणा FUSB300_OFFSET_SSCR0		0x308
#घोषणा FUSB300_OFFSET_SSCR1		0x30C
#घोषणा FUSB300_OFFSET_TT		0x310
#घोषणा FUSB300_OFFSET_DEVNOTF		0x314
#घोषणा FUSB300_OFFSET_DNC1		0x318
#घोषणा FUSB300_OFFSET_CS		0x31C
#घोषणा FUSB300_OFFSET_SOF		0x324
#घोषणा FUSB300_OFFSET_EFCS		0x328
#घोषणा FUSB300_OFFSET_IGR0		0x400
#घोषणा FUSB300_OFFSET_IGR1		0x404
#घोषणा FUSB300_OFFSET_IGR2		0x408
#घोषणा FUSB300_OFFSET_IGR3		0x40C
#घोषणा FUSB300_OFFSET_IGR4		0x410
#घोषणा FUSB300_OFFSET_IGR5		0x414
#घोषणा FUSB300_OFFSET_IGER0		0x420
#घोषणा FUSB300_OFFSET_IGER1		0x424
#घोषणा FUSB300_OFFSET_IGER2		0x428
#घोषणा FUSB300_OFFSET_IGER3		0x42C
#घोषणा FUSB300_OFFSET_IGER4		0x430
#घोषणा FUSB300_OFFSET_IGER5		0x434
#घोषणा FUSB300_OFFSET_DMAHMER		0x500
#घोषणा FUSB300_OFFSET_EPPRDRDY		0x504
#घोषणा FUSB300_OFFSET_DMAEPMR		0x508
#घोषणा FUSB300_OFFSET_DMAENR		0x50C
#घोषणा FUSB300_OFFSET_DMAAPR		0x510
#घोषणा FUSB300_OFFSET_AHBCR		0x514
#घोषणा FUSB300_OFFSET_EPPRD_W0(n)	(0x520 + (n - 1) * 0x10)
#घोषणा FUSB300_OFFSET_EPPRD_W1(n)	(0x524 + (n - 1) * 0x10)
#घोषणा FUSB300_OFFSET_EPPRD_W2(n)	(0x528 + (n - 1) * 0x10)
#घोषणा FUSB300_OFFSET_EPRD_PTR(n)	(0x52C + (n - 1) * 0x10)
#घोषणा FUSB300_OFFSET_BUFDBG_START	0x800
#घोषणा FUSB300_OFFSET_BUFDBG_END	0xBFC
#घोषणा FUSB300_OFFSET_EPPORT(n)	(0x1010 + (n - 1) * 0x10)

/*
 * *	Global Control Register (offset = 000H)
 * */
#घोषणा FUSB300_GCR_SF_RST		(1 << 8)
#घोषणा FUSB300_GCR_VBUS_STATUS		(1 << 7)
#घोषणा FUSB300_GCR_FORCE_HS_SUSP	(1 << 6)
#घोषणा FUSB300_GCR_SYNC_FIFO1_CLR	(1 << 5)
#घोषणा FUSB300_GCR_SYNC_FIFO0_CLR	(1 << 4)
#घोषणा FUSB300_GCR_FIFOCLR		(1 << 3)
#घोषणा FUSB300_GCR_GLINTEN		(1 << 2)
#घोषणा FUSB300_GCR_DEVEN_FS		0x3
#घोषणा FUSB300_GCR_DEVEN_HS		0x2
#घोषणा FUSB300_GCR_DEVEN_SS		0x1
#घोषणा FUSB300_GCR_DEVDIS		0x0
#घोषणा FUSB300_GCR_DEVEN_MSK		0x3


/*
 * *Global Test Mode (offset = 004H)
 * */
#घोषणा FUSB300_GTM_TST_DIS_SOFGEN	(1 << 16)
#घोषणा FUSB300_GTM_TST_CUR_EP_ENTRY(n)	((n & 0xF) << 12)
#घोषणा FUSB300_GTM_TST_EP_ENTRY(n)	((n & 0xF) << 8)
#घोषणा FUSB300_GTM_TST_EP_NUM(n)	((n & 0xF) << 4)
#घोषणा FUSB300_GTM_TST_FIFO_DEG	(1 << 1)
#घोषणा FUSB300_GTM_TSTMODE		(1 << 0)

/*
 * * Device Address Register (offset = 008H)
 * */
#घोषणा FUSB300_DAR_SETCONFG	(1 << 7)
#घोषणा FUSB300_DAR_DRVADDR(x)	(x & 0x7F)
#घोषणा FUSB300_DAR_DRVADDR_MSK	0x7F

/*
 * *Control Transfer Configuration and Status Register
 * (CX_Config_Status, offset = 00CH)
 * */
#घोषणा FUSB300_CSR_LEN(x)	((x & 0xFFFF) << 8)
#घोषणा FUSB300_CSR_LEN_MSK	(0xFFFF << 8)
#घोषणा FUSB300_CSR_EMP		(1 << 4)
#घोषणा FUSB300_CSR_FUL		(1 << 3)
#घोषणा FUSB300_CSR_CLR		(1 << 2)
#घोषणा FUSB300_CSR_STL		(1 << 1)
#घोषणा FUSB300_CSR_DONE	(1 << 0)

/*
 * * EPn Setting 0 (EPn_SET0, offset = 020H+(n-1)*30H, n=1~15 )
 * */
#घोषणा FUSB300_EPSET0_STL_CLR		(1 << 3)
#घोषणा FUSB300_EPSET0_CLRSEQNUM	(1 << 2)
#घोषणा FUSB300_EPSET0_STL		(1 << 0)

/*
 * * EPn Setting 1 (EPn_SET1, offset = 024H+(n-1)*30H, n=1~15)
 * */
#घोषणा FUSB300_EPSET1_START_ENTRY(x)	((x & 0xFF) << 24)
#घोषणा FUSB300_EPSET1_START_ENTRY_MSK	(0xFF << 24)
#घोषणा FUSB300_EPSET1_FIFOENTRY(x)	((x & 0x1F) << 12)
#घोषणा FUSB300_EPSET1_FIFOENTRY_MSK	(0x1f << 12)
#घोषणा FUSB300_EPSET1_INTERVAL(x)	((x & 0x7) << 6)
#घोषणा FUSB300_EPSET1_BWNUM(x)		((x & 0x3) << 4)
#घोषणा FUSB300_EPSET1_TYPEISO		(1 << 2)
#घोषणा FUSB300_EPSET1_TYPEBLK		(2 << 2)
#घोषणा FUSB300_EPSET1_TYPEINT		(3 << 2)
#घोषणा FUSB300_EPSET1_TYPE(x)		((x & 0x3) << 2)
#घोषणा FUSB300_EPSET1_TYPE_MSK		(0x3 << 2)
#घोषणा FUSB300_EPSET1_सूचीOUT		(0 << 1)
#घोषणा FUSB300_EPSET1_सूचीIN		(1 << 1)
#घोषणा FUSB300_EPSET1_सूची(x)		((x & 0x1) << 1)
#घोषणा FUSB300_EPSET1_सूचीIN		(1 << 1)
#घोषणा FUSB300_EPSET1_सूची_MSK		((0x1) << 1)
#घोषणा FUSB300_EPSET1_ACTDIS		0
#घोषणा FUSB300_EPSET1_ACTEN		1

/*
 * *EPn Setting 2 (EPn_SET2, offset = 028H+(n-1)*30H, n=1~15)
 * */
#घोषणा FUSB300_EPSET2_ADDROFS(x)	((x & 0x7FFF) << 16)
#घोषणा FUSB300_EPSET2_ADDROFS_MSK	(0x7fff << 16)
#घोषणा FUSB300_EPSET2_MPS(x)		(x & 0x7FF)
#घोषणा FUSB300_EPSET2_MPS_MSK		0x7FF

/*
 * * EPn FIFO Register (offset = 2cH+(n-1)*30H)
 * */
#घोषणा FUSB300_FFR_RST		(1 << 31)
#घोषणा FUSB300_FF_FUL		(1 << 30)
#घोषणा FUSB300_FF_EMPTY	(1 << 29)
#घोषणा FUSB300_FFR_BYCNT	0x1FFFF

/*
 * *EPn Stream ID (EPn_STR_ID, offset = 040H+(n-1)*30H, n=1~15)
 * */
#घोषणा FUSB300_STRID_STREN	(1 << 16)
#घोषणा FUSB300_STRID_STRID(x)	(x & 0xFFFF)

/*
 * *HS PHY Test Mode (offset = 300H)
 * */
#घोषणा FUSB300_HSPTM_TSTPKDONE		(1 << 4)
#घोषणा FUSB300_HSPTM_TSTPKT		(1 << 3)
#घोषणा FUSB300_HSPTM_TSTSET0NAK	(1 << 2)
#घोषणा FUSB300_HSPTM_TSTKSTA		(1 << 1)
#घोषणा FUSB300_HSPTM_TSTJSTA		(1 << 0)

/*
 * *HS Control Register (offset = 304H)
 * */
#घोषणा FUSB300_HSCR_HS_LPM_PERMIT	(1 << 8)
#घोषणा FUSB300_HSCR_HS_LPM_RMWKUP	(1 << 7)
#घोषणा FUSB300_HSCR_CAP_LPM_RMWKUP	(1 << 6)
#घोषणा FUSB300_HSCR_HS_GOSUSP		(1 << 5)
#घोषणा FUSB300_HSCR_HS_GORMWKU		(1 << 4)
#घोषणा FUSB300_HSCR_CAP_RMWKUP		(1 << 3)
#घोषणा FUSB300_HSCR_IDLECNT_0MS	0
#घोषणा FUSB300_HSCR_IDLECNT_1MS	1
#घोषणा FUSB300_HSCR_IDLECNT_2MS	2
#घोषणा FUSB300_HSCR_IDLECNT_3MS	3
#घोषणा FUSB300_HSCR_IDLECNT_4MS	4
#घोषणा FUSB300_HSCR_IDLECNT_5MS	5
#घोषणा FUSB300_HSCR_IDLECNT_6MS	6
#घोषणा FUSB300_HSCR_IDLECNT_7MS	7

/*
 * * SS Controller Register 0 (offset = 308H)
 * */
#घोषणा FUSB300_SSCR0_MAX_INTERVAL(x)	((x & 0x7) << 4)
#घोषणा FUSB300_SSCR0_U2_FUN_EN		(1 << 1)
#घोषणा FUSB300_SSCR0_U1_FUN_EN		(1 << 0)

/*
 * * SS Controller Register 1 (offset = 30CH)
 * */
#घोषणा FUSB300_SSCR1_GO_U3_DONE	(1 << 8)
#घोषणा FUSB300_SSCR1_TXDEEMPH_LEVEL	(1 << 7)
#घोषणा FUSB300_SSCR1_DIS_SCRMB		(1 << 6)
#घोषणा FUSB300_SSCR1_FORCE_RECOVERY	(1 << 5)
#घोषणा FUSB300_SSCR1_U3_WAKEUP_EN	(1 << 4)
#घोषणा FUSB300_SSCR1_U2_EXIT_EN	(1 << 3)
#घोषणा FUSB300_SSCR1_U1_EXIT_EN	(1 << 2)
#घोषणा FUSB300_SSCR1_U2_ENTRY_EN	(1 << 1)
#घोषणा FUSB300_SSCR1_U1_ENTRY_EN	(1 << 0)

/*
 * *SS Controller Register 2  (offset = 310H)
 * */
#घोषणा FUSB300_SSCR2_SS_TX_SWING		(1 << 25)
#घोषणा FUSB300_SSCR2_FORCE_LINKPM_ACCEPT	(1 << 24)
#घोषणा FUSB300_SSCR2_U2_INACT_TIMEOUT(x)	((x & 0xFF) << 16)
#घोषणा FUSB300_SSCR2_U1TIMEOUT(x)		((x & 0xFF) << 8)
#घोषणा FUSB300_SSCR2_U2TIMEOUT(x)		(x & 0xFF)

/*
 * *SS Device Notअगरication Control (DEV_NOTF, offset = 314H)
 * */
#घोषणा FUSB300_DEVNOTF_CONTEXT0(x)		((x & 0xFFFFFF) << 8)
#घोषणा FUSB300_DEVNOTF_TYPE_DIS		0
#घोषणा FUSB300_DEVNOTF_TYPE_FUNCWAKE		1
#घोषणा FUSB300_DEVNOTF_TYPE_LTM		2
#घोषणा FUSB300_DEVNOTF_TYPE_BUSINT_ADJMSG	3

/*
 * *BFM Arbiter Priority Register (BFM_ARB offset = 31CH)
 * */
#घोषणा FUSB300_BFMARB_ARB_M1	(1 << 3)
#घोषणा FUSB300_BFMARB_ARB_M0	(1 << 2)
#घोषणा FUSB300_BFMARB_ARB_S1	(1 << 1)
#घोषणा FUSB300_BFMARB_ARB_S0	1

/*
 * *Venकरोr Specअगरic IO Control Register (offset = 320H)
 * */
#घोषणा FUSB300_VSIC_VCTLOAD_N	(1 << 8)
#घोषणा FUSB300_VSIC_VCTL(x)	(x & 0x3F)

/*
 * *SOF Mask Timer (offset = 324H)
 * */
#घोषणा FUSB300_SOF_MASK_TIMER_HS	0x044c
#घोषणा FUSB300_SOF_MASK_TIMER_FS	0x2710

/*
 * *Error Flag and Control Status (offset = 328H)
 * */
#घोषणा FUSB300_EFCS_PM_STATE_U3	3
#घोषणा FUSB300_EFCS_PM_STATE_U2	2
#घोषणा FUSB300_EFCS_PM_STATE_U1	1
#घोषणा FUSB300_EFCS_PM_STATE_U0	0

/*
 * *Interrupt Group 0 Register (offset = 400H)
 * */
#घोषणा FUSB300_IGR0_EP15_PRD_INT	(1 << 31)
#घोषणा FUSB300_IGR0_EP14_PRD_INT	(1 << 30)
#घोषणा FUSB300_IGR0_EP13_PRD_INT	(1 << 29)
#घोषणा FUSB300_IGR0_EP12_PRD_INT	(1 << 28)
#घोषणा FUSB300_IGR0_EP11_PRD_INT	(1 << 27)
#घोषणा FUSB300_IGR0_EP10_PRD_INT	(1 << 26)
#घोषणा FUSB300_IGR0_EP9_PRD_INT	(1 << 25)
#घोषणा FUSB300_IGR0_EP8_PRD_INT	(1 << 24)
#घोषणा FUSB300_IGR0_EP7_PRD_INT	(1 << 23)
#घोषणा FUSB300_IGR0_EP6_PRD_INT	(1 << 22)
#घोषणा FUSB300_IGR0_EP5_PRD_INT	(1 << 21)
#घोषणा FUSB300_IGR0_EP4_PRD_INT	(1 << 20)
#घोषणा FUSB300_IGR0_EP3_PRD_INT	(1 << 19)
#घोषणा FUSB300_IGR0_EP2_PRD_INT	(1 << 18)
#घोषणा FUSB300_IGR0_EP1_PRD_INT	(1 << 17)
#घोषणा FUSB300_IGR0_EPn_PRD_INT(n)	(1 << (n + 16))

#घोषणा FUSB300_IGR0_EP15_FIFO_INT	(1 << 15)
#घोषणा FUSB300_IGR0_EP14_FIFO_INT	(1 << 14)
#घोषणा FUSB300_IGR0_EP13_FIFO_INT	(1 << 13)
#घोषणा FUSB300_IGR0_EP12_FIFO_INT	(1 << 12)
#घोषणा FUSB300_IGR0_EP11_FIFO_INT	(1 << 11)
#घोषणा FUSB300_IGR0_EP10_FIFO_INT	(1 << 10)
#घोषणा FUSB300_IGR0_EP9_FIFO_INT	(1 << 9)
#घोषणा FUSB300_IGR0_EP8_FIFO_INT	(1 << 8)
#घोषणा FUSB300_IGR0_EP7_FIFO_INT	(1 << 7)
#घोषणा FUSB300_IGR0_EP6_FIFO_INT	(1 << 6)
#घोषणा FUSB300_IGR0_EP5_FIFO_INT	(1 << 5)
#घोषणा FUSB300_IGR0_EP4_FIFO_INT	(1 << 4)
#घोषणा FUSB300_IGR0_EP3_FIFO_INT	(1 << 3)
#घोषणा FUSB300_IGR0_EP2_FIFO_INT	(1 << 2)
#घोषणा FUSB300_IGR0_EP1_FIFO_INT	(1 << 1)
#घोषणा FUSB300_IGR0_EPn_FIFO_INT(n)	(1 << n)

/*
 * *Interrupt Group 1 Register (offset = 404H)
 * */
#घोषणा FUSB300_IGR1_INTGRP5		(1 << 31)
#घोषणा FUSB300_IGR1_VBUS_CHG_INT	(1 << 30)
#घोषणा FUSB300_IGR1_SYNF1_EMPTY_INT	(1 << 29)
#घोषणा FUSB300_IGR1_SYNF0_EMPTY_INT	(1 << 28)
#घोषणा FUSB300_IGR1_U3_EXIT_FAIL_INT	(1 << 27)
#घोषणा FUSB300_IGR1_U2_EXIT_FAIL_INT	(1 << 26)
#घोषणा FUSB300_IGR1_U1_EXIT_FAIL_INT	(1 << 25)
#घोषणा FUSB300_IGR1_U2_ENTRY_FAIL_INT	(1 << 24)
#घोषणा FUSB300_IGR1_U1_ENTRY_FAIL_INT	(1 << 23)
#घोषणा FUSB300_IGR1_U3_EXIT_INT	(1 << 22)
#घोषणा FUSB300_IGR1_U2_EXIT_INT	(1 << 21)
#घोषणा FUSB300_IGR1_U1_EXIT_INT	(1 << 20)
#घोषणा FUSB300_IGR1_U3_ENTRY_INT	(1 << 19)
#घोषणा FUSB300_IGR1_U2_ENTRY_INT	(1 << 18)
#घोषणा FUSB300_IGR1_U1_ENTRY_INT	(1 << 17)
#घोषणा FUSB300_IGR1_HOT_RST_INT	(1 << 16)
#घोषणा FUSB300_IGR1_WARM_RST_INT	(1 << 15)
#घोषणा FUSB300_IGR1_RESM_INT		(1 << 14)
#घोषणा FUSB300_IGR1_SUSP_INT		(1 << 13)
#घोषणा FUSB300_IGR1_HS_LPM_INT		(1 << 12)
#घोषणा FUSB300_IGR1_USBRST_INT		(1 << 11)
#घोषणा FUSB300_IGR1_DEV_MODE_CHG_INT	(1 << 9)
#घोषणा FUSB300_IGR1_CX_COMABT_INT	(1 << 8)
#घोषणा FUSB300_IGR1_CX_COMFAIL_INT	(1 << 7)
#घोषणा FUSB300_IGR1_CX_CMDEND_INT	(1 << 6)
#घोषणा FUSB300_IGR1_CX_OUT_INT		(1 << 5)
#घोषणा FUSB300_IGR1_CX_IN_INT		(1 << 4)
#घोषणा FUSB300_IGR1_CX_SETUP_INT	(1 << 3)
#घोषणा FUSB300_IGR1_INTGRP4		(1 << 2)
#घोषणा FUSB300_IGR1_INTGRP3		(1 << 1)
#घोषणा FUSB300_IGR1_INTGRP2		(1 << 0)

/*
 * *Interrupt Group 2 Register (offset = 408H)
 * */
#घोषणा FUSB300_IGR2_EP6_STR_ACCEPT_INT		(1 << 29)
#घोषणा FUSB300_IGR2_EP6_STR_RESUME_INT		(1 << 28)
#घोषणा FUSB300_IGR2_EP6_STR_REQ_INT		(1 << 27)
#घोषणा FUSB300_IGR2_EP6_STR_NOTRDY_INT		(1 << 26)
#घोषणा FUSB300_IGR2_EP6_STR_PRIME_INT		(1 << 25)
#घोषणा FUSB300_IGR2_EP5_STR_ACCEPT_INT		(1 << 24)
#घोषणा FUSB300_IGR2_EP5_STR_RESUME_INT		(1 << 23)
#घोषणा FUSB300_IGR2_EP5_STR_REQ_INT		(1 << 22)
#घोषणा FUSB300_IGR2_EP5_STR_NOTRDY_INT		(1 << 21)
#घोषणा FUSB300_IGR2_EP5_STR_PRIME_INT		(1 << 20)
#घोषणा FUSB300_IGR2_EP4_STR_ACCEPT_INT		(1 << 19)
#घोषणा FUSB300_IGR2_EP4_STR_RESUME_INT		(1 << 18)
#घोषणा FUSB300_IGR2_EP4_STR_REQ_INT		(1 << 17)
#घोषणा FUSB300_IGR2_EP4_STR_NOTRDY_INT		(1 << 16)
#घोषणा FUSB300_IGR2_EP4_STR_PRIME_INT		(1 << 15)
#घोषणा FUSB300_IGR2_EP3_STR_ACCEPT_INT		(1 << 14)
#घोषणा FUSB300_IGR2_EP3_STR_RESUME_INT		(1 << 13)
#घोषणा FUSB300_IGR2_EP3_STR_REQ_INT		(1 << 12)
#घोषणा FUSB300_IGR2_EP3_STR_NOTRDY_INT		(1 << 11)
#घोषणा FUSB300_IGR2_EP3_STR_PRIME_INT		(1 << 10)
#घोषणा FUSB300_IGR2_EP2_STR_ACCEPT_INT		(1 << 9)
#घोषणा FUSB300_IGR2_EP2_STR_RESUME_INT		(1 << 8)
#घोषणा FUSB300_IGR2_EP2_STR_REQ_INT		(1 << 7)
#घोषणा FUSB300_IGR2_EP2_STR_NOTRDY_INT		(1 << 6)
#घोषणा FUSB300_IGR2_EP2_STR_PRIME_INT		(1 << 5)
#घोषणा FUSB300_IGR2_EP1_STR_ACCEPT_INT		(1 << 4)
#घोषणा FUSB300_IGR2_EP1_STR_RESUME_INT		(1 << 3)
#घोषणा FUSB300_IGR2_EP1_STR_REQ_INT		(1 << 2)
#घोषणा FUSB300_IGR2_EP1_STR_NOTRDY_INT		(1 << 1)
#घोषणा FUSB300_IGR2_EP1_STR_PRIME_INT		(1 << 0)

#घोषणा FUSB300_IGR2_EP_STR_ACCEPT_INT(n)	(1 << (5 * n - 1))
#घोषणा FUSB300_IGR2_EP_STR_RESUME_INT(n)	(1 << (5 * n - 2))
#घोषणा FUSB300_IGR2_EP_STR_REQ_INT(n)		(1 << (5 * n - 3))
#घोषणा FUSB300_IGR2_EP_STR_NOTRDY_INT(n)	(1 << (5 * n - 4))
#घोषणा FUSB300_IGR2_EP_STR_PRIME_INT(n)	(1 << (5 * n - 5))

/*
 * *Interrupt Group 3 Register (offset = 40CH)
 * */
#घोषणा FUSB300_IGR3_EP12_STR_ACCEPT_INT	(1 << 29)
#घोषणा FUSB300_IGR3_EP12_STR_RESUME_INT	(1 << 28)
#घोषणा FUSB300_IGR3_EP12_STR_REQ_INT		(1 << 27)
#घोषणा FUSB300_IGR3_EP12_STR_NOTRDY_INT	(1 << 26)
#घोषणा FUSB300_IGR3_EP12_STR_PRIME_INT		(1 << 25)
#घोषणा FUSB300_IGR3_EP11_STR_ACCEPT_INT	(1 << 24)
#घोषणा FUSB300_IGR3_EP11_STR_RESUME_INT	(1 << 23)
#घोषणा FUSB300_IGR3_EP11_STR_REQ_INT		(1 << 22)
#घोषणा FUSB300_IGR3_EP11_STR_NOTRDY_INT	(1 << 21)
#घोषणा FUSB300_IGR3_EP11_STR_PRIME_INT		(1 << 20)
#घोषणा FUSB300_IGR3_EP10_STR_ACCEPT_INT	(1 << 19)
#घोषणा FUSB300_IGR3_EP10_STR_RESUME_INT	(1 << 18)
#घोषणा FUSB300_IGR3_EP10_STR_REQ_INT		(1 << 17)
#घोषणा FUSB300_IGR3_EP10_STR_NOTRDY_INT	(1 << 16)
#घोषणा FUSB300_IGR3_EP10_STR_PRIME_INT		(1 << 15)
#घोषणा FUSB300_IGR3_EP9_STR_ACCEPT_INT		(1 << 14)
#घोषणा FUSB300_IGR3_EP9_STR_RESUME_INT		(1 << 13)
#घोषणा FUSB300_IGR3_EP9_STR_REQ_INT		(1 << 12)
#घोषणा FUSB300_IGR3_EP9_STR_NOTRDY_INT		(1 << 11)
#घोषणा FUSB300_IGR3_EP9_STR_PRIME_INT		(1 << 10)
#घोषणा FUSB300_IGR3_EP8_STR_ACCEPT_INT		(1 << 9)
#घोषणा FUSB300_IGR3_EP8_STR_RESUME_INT		(1 << 8)
#घोषणा FUSB300_IGR3_EP8_STR_REQ_INT		(1 << 7)
#घोषणा FUSB300_IGR3_EP8_STR_NOTRDY_INT		(1 << 6)
#घोषणा FUSB300_IGR3_EP8_STR_PRIME_INT		(1 << 5)
#घोषणा FUSB300_IGR3_EP7_STR_ACCEPT_INT		(1 << 4)
#घोषणा FUSB300_IGR3_EP7_STR_RESUME_INT		(1 << 3)
#घोषणा FUSB300_IGR3_EP7_STR_REQ_INT		(1 << 2)
#घोषणा FUSB300_IGR3_EP7_STR_NOTRDY_INT		(1 << 1)
#घोषणा FUSB300_IGR3_EP7_STR_PRIME_INT		(1 << 0)

#घोषणा FUSB300_IGR3_EP_STR_ACCEPT_INT(n)	(1 << (5 * (n - 6) - 1))
#घोषणा FUSB300_IGR3_EP_STR_RESUME_INT(n)	(1 << (5 * (n - 6) - 2))
#घोषणा FUSB300_IGR3_EP_STR_REQ_INT(n)		(1 << (5 * (n - 6) - 3))
#घोषणा FUSB300_IGR3_EP_STR_NOTRDY_INT(n)	(1 << (5 * (n - 6) - 4))
#घोषणा FUSB300_IGR3_EP_STR_PRIME_INT(n)	(1 << (5 * (n - 6) - 5))

/*
 * *Interrupt Group 4 Register (offset = 410H)
 * */
#घोषणा FUSB300_IGR4_EP15_RX0_INT		(1 << 31)
#घोषणा FUSB300_IGR4_EP14_RX0_INT		(1 << 30)
#घोषणा FUSB300_IGR4_EP13_RX0_INT		(1 << 29)
#घोषणा FUSB300_IGR4_EP12_RX0_INT		(1 << 28)
#घोषणा FUSB300_IGR4_EP11_RX0_INT		(1 << 27)
#घोषणा FUSB300_IGR4_EP10_RX0_INT		(1 << 26)
#घोषणा FUSB300_IGR4_EP9_RX0_INT		(1 << 25)
#घोषणा FUSB300_IGR4_EP8_RX0_INT		(1 << 24)
#घोषणा FUSB300_IGR4_EP7_RX0_INT		(1 << 23)
#घोषणा FUSB300_IGR4_EP6_RX0_INT		(1 << 22)
#घोषणा FUSB300_IGR4_EP5_RX0_INT		(1 << 21)
#घोषणा FUSB300_IGR4_EP4_RX0_INT		(1 << 20)
#घोषणा FUSB300_IGR4_EP3_RX0_INT		(1 << 19)
#घोषणा FUSB300_IGR4_EP2_RX0_INT		(1 << 18)
#घोषणा FUSB300_IGR4_EP1_RX0_INT		(1 << 17)
#घोषणा FUSB300_IGR4_EP_RX0_INT(x)		(1 << (x + 16))
#घोषणा FUSB300_IGR4_EP15_STR_ACCEPT_INT	(1 << 14)
#घोषणा FUSB300_IGR4_EP15_STR_RESUME_INT	(1 << 13)
#घोषणा FUSB300_IGR4_EP15_STR_REQ_INT		(1 << 12)
#घोषणा FUSB300_IGR4_EP15_STR_NOTRDY_INT	(1 << 11)
#घोषणा FUSB300_IGR4_EP15_STR_PRIME_INT		(1 << 10)
#घोषणा FUSB300_IGR4_EP14_STR_ACCEPT_INT	(1 << 9)
#घोषणा FUSB300_IGR4_EP14_STR_RESUME_INT	(1 << 8)
#घोषणा FUSB300_IGR4_EP14_STR_REQ_INT		(1 << 7)
#घोषणा FUSB300_IGR4_EP14_STR_NOTRDY_INT	(1 << 6)
#घोषणा FUSB300_IGR4_EP14_STR_PRIME_INT		(1 << 5)
#घोषणा FUSB300_IGR4_EP13_STR_ACCEPT_INT	(1 << 4)
#घोषणा FUSB300_IGR4_EP13_STR_RESUME_INT	(1 << 3)
#घोषणा FUSB300_IGR4_EP13_STR_REQ_INT		(1 << 2)
#घोषणा FUSB300_IGR4_EP13_STR_NOTRDY_INT	(1 << 1)
#घोषणा FUSB300_IGR4_EP13_STR_PRIME_INT		(1 << 0)

#घोषणा FUSB300_IGR4_EP_STR_ACCEPT_INT(n)	(1 << (5 * (n - 12) - 1))
#घोषणा FUSB300_IGR4_EP_STR_RESUME_INT(n)	(1 << (5 * (n - 12) - 2))
#घोषणा FUSB300_IGR4_EP_STR_REQ_INT(n)		(1 << (5 * (n - 12) - 3))
#घोषणा FUSB300_IGR4_EP_STR_NOTRDY_INT(n)	(1 << (5 * (n - 12) - 4))
#घोषणा FUSB300_IGR4_EP_STR_PRIME_INT(n)	(1 << (5 * (n - 12) - 5))

/*
 * *Interrupt Group 5 Register (offset = 414H)
 * */
#घोषणा FUSB300_IGR5_EP_STL_INT(n)	(1 << n)

/*
 * *Interrupt Enable Group 0 Register (offset = 420H)
 * */
#घोषणा FUSB300_IGER0_EEP15_PRD_INT	(1 << 31)
#घोषणा FUSB300_IGER0_EEP14_PRD_INT	(1 << 30)
#घोषणा FUSB300_IGER0_EEP13_PRD_INT	(1 << 29)
#घोषणा FUSB300_IGER0_EEP12_PRD_INT	(1 << 28)
#घोषणा FUSB300_IGER0_EEP11_PRD_INT	(1 << 27)
#घोषणा FUSB300_IGER0_EEP10_PRD_INT	(1 << 26)
#घोषणा FUSB300_IGER0_EEP9_PRD_INT	(1 << 25)
#घोषणा FUSB300_IGER0_EP8_PRD_INT	(1 << 24)
#घोषणा FUSB300_IGER0_EEP7_PRD_INT	(1 << 23)
#घोषणा FUSB300_IGER0_EEP6_PRD_INT	(1 << 22)
#घोषणा FUSB300_IGER0_EEP5_PRD_INT	(1 << 21)
#घोषणा FUSB300_IGER0_EEP4_PRD_INT	(1 << 20)
#घोषणा FUSB300_IGER0_EEP3_PRD_INT	(1 << 19)
#घोषणा FUSB300_IGER0_EEP2_PRD_INT	(1 << 18)
#घोषणा FUSB300_IGER0_EEP1_PRD_INT	(1 << 17)
#घोषणा FUSB300_IGER0_EEPn_PRD_INT(n)	(1 << (n + 16))

#घोषणा FUSB300_IGER0_EEP15_FIFO_INT	(1 << 15)
#घोषणा FUSB300_IGER0_EEP14_FIFO_INT	(1 << 14)
#घोषणा FUSB300_IGER0_EEP13_FIFO_INT	(1 << 13)
#घोषणा FUSB300_IGER0_EEP12_FIFO_INT	(1 << 12)
#घोषणा FUSB300_IGER0_EEP11_FIFO_INT	(1 << 11)
#घोषणा FUSB300_IGER0_EEP10_FIFO_INT	(1 << 10)
#घोषणा FUSB300_IGER0_EEP9_FIFO_INT	(1 << 9)
#घोषणा FUSB300_IGER0_EEP8_FIFO_INT	(1 << 8)
#घोषणा FUSB300_IGER0_EEP7_FIFO_INT	(1 << 7)
#घोषणा FUSB300_IGER0_EEP6_FIFO_INT	(1 << 6)
#घोषणा FUSB300_IGER0_EEP5_FIFO_INT	(1 << 5)
#घोषणा FUSB300_IGER0_EEP4_FIFO_INT	(1 << 4)
#घोषणा FUSB300_IGER0_EEP3_FIFO_INT	(1 << 3)
#घोषणा FUSB300_IGER0_EEP2_FIFO_INT	(1 << 2)
#घोषणा FUSB300_IGER0_EEP1_FIFO_INT	(1 << 1)
#घोषणा FUSB300_IGER0_EEPn_FIFO_INT(n)	(1 << n)

/*
 * *Interrupt Enable Group 1 Register (offset = 424H)
 * */
#घोषणा FUSB300_IGER1_EINT_GRP5		(1 << 31)
#घोषणा FUSB300_IGER1_VBUS_CHG_INT	(1 << 30)
#घोषणा FUSB300_IGER1_SYNF1_EMPTY_INT	(1 << 29)
#घोषणा FUSB300_IGER1_SYNF0_EMPTY_INT	(1 << 28)
#घोषणा FUSB300_IGER1_U3_EXIT_FAIL_INT	(1 << 27)
#घोषणा FUSB300_IGER1_U2_EXIT_FAIL_INT	(1 << 26)
#घोषणा FUSB300_IGER1_U1_EXIT_FAIL_INT	(1 << 25)
#घोषणा FUSB300_IGER1_U2_ENTRY_FAIL_INT	(1 << 24)
#घोषणा FUSB300_IGER1_U1_ENTRY_FAIL_INT	(1 << 23)
#घोषणा FUSB300_IGER1_U3_EXIT_INT	(1 << 22)
#घोषणा FUSB300_IGER1_U2_EXIT_INT	(1 << 21)
#घोषणा FUSB300_IGER1_U1_EXIT_INT	(1 << 20)
#घोषणा FUSB300_IGER1_U3_ENTRY_INT	(1 << 19)
#घोषणा FUSB300_IGER1_U2_ENTRY_INT	(1 << 18)
#घोषणा FUSB300_IGER1_U1_ENTRY_INT	(1 << 17)
#घोषणा FUSB300_IGER1_HOT_RST_INT	(1 << 16)
#घोषणा FUSB300_IGER1_WARM_RST_INT	(1 << 15)
#घोषणा FUSB300_IGER1_RESM_INT		(1 << 14)
#घोषणा FUSB300_IGER1_SUSP_INT		(1 << 13)
#घोषणा FUSB300_IGER1_LPM_INT		(1 << 12)
#घोषणा FUSB300_IGER1_HS_RST_INT	(1 << 11)
#घोषणा FUSB300_IGER1_EDEV_MODE_CHG_INT	(1 << 9)
#घोषणा FUSB300_IGER1_CX_COMABT_INT	(1 << 8)
#घोषणा FUSB300_IGER1_CX_COMFAIL_INT	(1 << 7)
#घोषणा FUSB300_IGER1_CX_CMDEND_INT	(1 << 6)
#घोषणा FUSB300_IGER1_CX_OUT_INT	(1 << 5)
#घोषणा FUSB300_IGER1_CX_IN_INT		(1 << 4)
#घोषणा FUSB300_IGER1_CX_SETUP_INT	(1 << 3)
#घोषणा FUSB300_IGER1_INTGRP4		(1 << 2)
#घोषणा FUSB300_IGER1_INTGRP3		(1 << 1)
#घोषणा FUSB300_IGER1_INTGRP2		(1 << 0)

/*
 * *Interrupt Enable Group 2 Register (offset = 428H)
 * */
#घोषणा FUSB300_IGER2_EEP_STR_ACCEPT_INT(n)	(1 << (5 * n - 1))
#घोषणा FUSB300_IGER2_EEP_STR_RESUME_INT(n)	(1 << (5 * n - 2))
#घोषणा FUSB300_IGER2_EEP_STR_REQ_INT(n)	(1 << (5 * n - 3))
#घोषणा FUSB300_IGER2_EEP_STR_NOTRDY_INT(n)	(1 << (5 * n - 4))
#घोषणा FUSB300_IGER2_EEP_STR_PRIME_INT(n)	(1 << (5 * n - 5))

/*
 * *Interrupt Enable Group 3 Register (offset = 42CH)
 * */

#घोषणा FUSB300_IGER3_EEP_STR_ACCEPT_INT(n)	(1 << (5 * (n - 6) - 1))
#घोषणा FUSB300_IGER3_EEP_STR_RESUME_INT(n)	(1 << (5 * (n - 6) - 2))
#घोषणा FUSB300_IGER3_EEP_STR_REQ_INT(n)	(1 << (5 * (n - 6) - 3))
#घोषणा FUSB300_IGER3_EEP_STR_NOTRDY_INT(n)	(1 << (5 * (n - 6) - 4))
#घोषणा FUSB300_IGER3_EEP_STR_PRIME_INT(n)	(1 << (5 * (n - 6) - 5))

/*
 * *Interrupt Enable Group 4 Register (offset = 430H)
 * */

#घोषणा FUSB300_IGER4_EEP_RX0_INT(n)		(1 << (n + 16))
#घोषणा FUSB300_IGER4_EEP_STR_ACCEPT_INT(n)	(1 << (5 * (n - 6) - 1))
#घोषणा FUSB300_IGER4_EEP_STR_RESUME_INT(n)	(1 << (5 * (n - 6) - 2))
#घोषणा FUSB300_IGER4_EEP_STR_REQ_INT(n)	(1 << (5 * (n - 6) - 3))
#घोषणा FUSB300_IGER4_EEP_STR_NOTRDY_INT(n)	(1 << (5 * (n - 6) - 4))
#घोषणा FUSB300_IGER4_EEP_STR_PRIME_INT(n)	(1 << (5 * (n - 6) - 5))

/* EP PRD Ready (EP_PRD_RDY, offset = 504H) */

#घोषणा FUSB300_EPPRDR_EP15_PRD_RDY		(1 << 15)
#घोषणा FUSB300_EPPRDR_EP14_PRD_RDY		(1 << 14)
#घोषणा FUSB300_EPPRDR_EP13_PRD_RDY		(1 << 13)
#घोषणा FUSB300_EPPRDR_EP12_PRD_RDY		(1 << 12)
#घोषणा FUSB300_EPPRDR_EP11_PRD_RDY		(1 << 11)
#घोषणा FUSB300_EPPRDR_EP10_PRD_RDY		(1 << 10)
#घोषणा FUSB300_EPPRDR_EP9_PRD_RDY		(1 << 9)
#घोषणा FUSB300_EPPRDR_EP8_PRD_RDY		(1 << 8)
#घोषणा FUSB300_EPPRDR_EP7_PRD_RDY		(1 << 7)
#घोषणा FUSB300_EPPRDR_EP6_PRD_RDY		(1 << 6)
#घोषणा FUSB300_EPPRDR_EP5_PRD_RDY		(1 << 5)
#घोषणा FUSB300_EPPRDR_EP4_PRD_RDY		(1 << 4)
#घोषणा FUSB300_EPPRDR_EP3_PRD_RDY		(1 << 3)
#घोषणा FUSB300_EPPRDR_EP2_PRD_RDY		(1 << 2)
#घोषणा FUSB300_EPPRDR_EP1_PRD_RDY		(1 << 1)
#घोषणा FUSB300_EPPRDR_EP_PRD_RDY(n)		(1 << n)

/* AHB Bus Control Register (offset = 514H) */
#घोषणा FUSB300_AHBBCR_S1_SPLIT_ON		(1 << 17)
#घोषणा FUSB300_AHBBCR_S0_SPLIT_ON		(1 << 16)
#घोषणा FUSB300_AHBBCR_S1_1entry		(0 << 12)
#घोषणा FUSB300_AHBBCR_S1_4entry		(3 << 12)
#घोषणा FUSB300_AHBBCR_S1_8entry		(5 << 12)
#घोषणा FUSB300_AHBBCR_S1_16entry		(7 << 12)
#घोषणा FUSB300_AHBBCR_S0_1entry		(0 << 8)
#घोषणा FUSB300_AHBBCR_S0_4entry		(3 << 8)
#घोषणा FUSB300_AHBBCR_S0_8entry		(5 << 8)
#घोषणा FUSB300_AHBBCR_S0_16entry		(7 << 8)
#घोषणा FUSB300_AHBBCR_M1_BURST_SINGLE		(0 << 4)
#घोषणा FUSB300_AHBBCR_M1_BURST_INCR		(1 << 4)
#घोषणा FUSB300_AHBBCR_M1_BURST_INCR4		(3 << 4)
#घोषणा FUSB300_AHBBCR_M1_BURST_INCR8		(5 << 4)
#घोषणा FUSB300_AHBBCR_M1_BURST_INCR16		(7 << 4)
#घोषणा FUSB300_AHBBCR_M0_BURST_SINGLE		0
#घोषणा FUSB300_AHBBCR_M0_BURST_INCR		1
#घोषणा FUSB300_AHBBCR_M0_BURST_INCR4		3
#घोषणा FUSB300_AHBBCR_M0_BURST_INCR8		5
#घोषणा FUSB300_AHBBCR_M0_BURST_INCR16		7
#घोषणा FUSB300_IGER5_EEP_STL_INT(n)		(1 << n)

/* WORD 0 Data Structure of PRD Table */
#घोषणा FUSB300_EPPRD0_M			(1 << 30)
#घोषणा FUSB300_EPPRD0_O			(1 << 29)
/* The finished prd */
#घोषणा FUSB300_EPPRD0_F			(1 << 28)
#घोषणा FUSB300_EPPRD0_I			(1 << 27)
#घोषणा FUSB300_EPPRD0_A			(1 << 26)
/* To decide HW poपूर्णांक to first prd at next समय */
#घोषणा FUSB300_EPPRD0_L			(1 << 25)
#घोषणा FUSB300_EPPRD0_H			(1 << 24)
#घोषणा FUSB300_EPPRD0_BTC(n)			(n & 0xFFFFFF)

/*----------------------------------------------------------------------*/
#घोषणा FUSB300_MAX_NUM_EP		16

#घोषणा FUSB300_FIFO_ENTRY_NUM		8
#घोषणा FUSB300_MAX_FIFO_ENTRY		8

#घोषणा SS_CTL_MAX_PACKET_SIZE		0x200
#घोषणा SS_BULK_MAX_PACKET_SIZE		0x400
#घोषणा SS_पूर्णांक_उच्च_PACKET_SIZE		0x400
#घोषणा SS_ISO_MAX_PACKET_SIZE		0x400

#घोषणा HS_BULK_MAX_PACKET_SIZE		0x200
#घोषणा HS_CTL_MAX_PACKET_SIZE		0x40
#घोषणा HS_पूर्णांक_उच्च_PACKET_SIZE		0x400
#घोषणा HS_ISO_MAX_PACKET_SIZE		0x400

काष्ठा fusb300_ep_info अणु
	u8	epnum;
	u8	type;
	u8	पूर्णांकerval;
	u8	dir_in;
	u16	maxpacket;
	u16	addrofs;
	u16	bw_num;
पूर्ण;

काष्ठा fusb300_request अणु

	काष्ठा usb_request	req;
	काष्ठा list_head	queue;
पूर्ण;


काष्ठा fusb300_ep अणु
	काष्ठा usb_ep		ep;
	काष्ठा fusb300		*fusb300;

	काष्ठा list_head	queue;
	अचिन्हित		stall:1;
	अचिन्हित		wedged:1;
	अचिन्हित		use_dma:1;

	अचिन्हित अक्षर		epnum;
	अचिन्हित अक्षर		type;
पूर्ण;

काष्ठा fusb300 अणु
	spinlock_t		lock;
	व्योम __iomem		*reg;

	अचिन्हित दीर्घ		irq_trigger;

	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;

	काष्ठा fusb300_ep	*ep[FUSB300_MAX_NUM_EP];

	काष्ठा usb_request	*ep0_req;	/* क्रम पूर्णांकernal request */
	__le16			ep0_data;
	u32			ep0_length;	/* क्रम पूर्णांकernal request */
	u8			ep0_dir;	/* 0/0x80  out/in */

	u8			fअगरo_entry_num;	/* next start fअगरo entry */
	u32			addrofs;	/* next fअगरo address offset */
	u8			reक्रमागत;		/* अगर re-क्रमागतeration */
पूर्ण;

#घोषणा to_fusb300(g)		(container_of((g), काष्ठा fusb300, gadget))

#पूर्ण_अगर
