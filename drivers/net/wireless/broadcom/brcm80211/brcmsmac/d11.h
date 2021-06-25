<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित	_BRCM_D11_H_
#घोषणा	_BRCM_D11_H_

#समावेश <linux/ieee80211.h>

#समावेश <defs.h>
#समावेश "pub.h"
#समावेश "dma.h"

/* RX FIFO numbers */
#घोषणा	RX_FIFO			0	/* data and ctl frames */
#घोषणा	RX_TXSTATUS_FIFO	3	/* RX fअगरo क्रम tx status packages */

/* TX FIFO numbers using WME Access Category */
#घोषणा	TX_AC_BK_FIFO		0	/* Background TX FIFO */
#घोषणा	TX_AC_BE_FIFO		1	/* Best-Efक्रमt TX FIFO */
#घोषणा	TX_AC_VI_FIFO		2	/* Video TX FIFO */
#घोषणा	TX_AC_VO_FIFO		3	/* Voice TX FIFO */
#घोषणा	TX_BCMC_FIFO		4	/* Broadcast/Multicast TX FIFO */
#घोषणा	TX_ATIM_FIFO		5	/* TX fअगरo क्रम ATIM winकरोw info */

/* Addr is byte address used by SW; offset is word offset used by uCode */

/* Per AC TX limit settings */
#घोषणा M_AC_TXLMT_BASE_ADDR         (0x180 * 2)
#घोषणा M_AC_TXLMT_ADDR(_ac)         (M_AC_TXLMT_BASE_ADDR + (2 * (_ac)))

/* Legacy TX FIFO numbers */
#घोषणा	TX_DATA_FIFO		TX_AC_BE_FIFO
#घोषणा	TX_CTL_FIFO		TX_AC_VO_FIFO

#घोषणा WL_RSSI_ANT_MAX		4	/* max possible rx antennas */

काष्ठा पूर्णांकctrlregs अणु
	u32 पूर्णांकstatus;
	u32 पूर्णांकmask;
पूर्ण;

/* PIO काष्ठाure,
 *  support two PIO क्रमmat: 2 bytes access and 4 bytes access
 *  basic FIFO रेजिस्टर set is per channel(transmit or receive)
 *  a pair of channels is defined क्रम convenience
 */
/* 2byte-wide pio रेजिस्टर set per channel(xmt or rcv) */
काष्ठा pio2regs अणु
	u16 fअगरocontrol;
	u16 fअगरodata;
	u16 fअगरoमुक्त;	/* only valid in xmt channel, not in rcv channel */
	u16 PAD;
पूर्ण;

/* a pair of pio channels(tx and rx) */
काष्ठा pio2regp अणु
	काष्ठा pio2regs tx;
	काष्ठा pio2regs rx;
पूर्ण;

/* 4byte-wide pio रेजिस्टर set per channel(xmt or rcv) */
काष्ठा pio4regs अणु
	u32 fअगरocontrol;
	u32 fअगरodata;
पूर्ण;

/* a pair of pio channels(tx and rx) */
काष्ठा pio4regp अणु
	काष्ठा pio4regs tx;
	काष्ठा pio4regs rx;
पूर्ण;

/* पढ़ो: 32-bit रेजिस्टर that can be पढ़ो as 32-bit or as 2 16-bit
 * ग_लिखो: only low 16b-it half can be written
 */
जोड़ pmqreg अणु
	u32 pmqhostdata;	/* पढ़ो only! */
	काष्ठा अणु
		u16 pmqctrlstatus;	/* पढ़ो/ग_लिखो */
		u16 PAD;
	पूर्ण w;
पूर्ण;

काष्ठा fअगरo64 अणु
	काष्ठा dma64regs dmaxmt;	/* dma tx */
	काष्ठा pio4regs piotx;	/* pio tx */
	काष्ठा dma64regs dmarcv;	/* dma rx */
	काष्ठा pio4regs piorx;	/* pio rx */
पूर्ण;

/*
 * Host Interface Registers
 */
काष्ठा d11regs अणु
	/* Device Control ("semi-standard host registers") */
	u32 PAD[3];		/* 0x0 - 0x8 */
	u32 biststatus;	/* 0xC */
	u32 biststatus2;	/* 0x10 */
	u32 PAD;		/* 0x14 */
	u32 gpसमयr;		/* 0x18 */
	u32 useस_समयr;	/* 0x1c *//* क्रम corerev >= 26 */

	/* Interrupt Control *//* 0x20 */
	काष्ठा पूर्णांकctrlregs पूर्णांकctrlregs[8];

	u32 PAD[40];		/* 0x60 - 0xFC */

	u32 पूर्णांकrcvlazy[4];	/* 0x100 - 0x10C */

	u32 PAD[4];		/* 0x110 - 0x11c */

	u32 maccontrol;	/* 0x120 */
	u32 maccommand;	/* 0x124 */
	u32 macपूर्णांकstatus;	/* 0x128 */
	u32 macपूर्णांकmask;	/* 0x12C */

	/* Transmit Template Access */
	u32 tplatewrptr;	/* 0x130 */
	u32 tplatewrdata;	/* 0x134 */
	u32 PAD[2];		/* 0x138 - 0x13C */

	/* PMQ रेजिस्टरs */
	जोड़ pmqreg pmqreg;	/* 0x140 */
	u32 pmqpatl;		/* 0x144 */
	u32 pmqpath;		/* 0x148 */
	u32 PAD;		/* 0x14C */

	u32 chnstatus;	/* 0x150 */
	u32 psmdebug;	/* 0x154 */
	u32 phydebug;	/* 0x158 */
	u32 machwcap;	/* 0x15C */

	/* Extended Internal Objects */
	u32 objaddr;		/* 0x160 */
	u32 objdata;		/* 0x164 */
	u32 PAD[2];		/* 0x168 - 0x16c */

	u32 frmtxstatus;	/* 0x170 */
	u32 frmtxstatus2;	/* 0x174 */
	u32 PAD[2];		/* 0x178 - 0x17c */

	/* TSF host access */
	u32 tsf_समयrlow;	/* 0x180 */
	u32 tsf_समयrhigh;	/* 0x184 */
	u32 tsf_cfprep;	/* 0x188 */
	u32 tsf_cfpstart;	/* 0x18c */
	u32 tsf_cfpmaxdur32;	/* 0x190 */
	u32 PAD[3];		/* 0x194 - 0x19c */

	u32 maccontrol1;	/* 0x1a0 */
	u32 machwcap1;	/* 0x1a4 */
	u32 PAD[14];		/* 0x1a8 - 0x1dc */

	/* Clock control and hardware workarounds*/
	u32 clk_ctl_st;	/* 0x1e0 */
	u32 hw_war;
	u32 d11_phypllctl;	/* the phypll request/avail bits are
				 * moved to clk_ctl_st
				 */
	u32 PAD[5];		/* 0x1ec - 0x1fc */

	/* 0x200-0x37F dma/pio रेजिस्टरs */
	काष्ठा fअगरo64 fअगरo64regs[6];

	/* FIFO diagnostic port access */
	काष्ठा dma32diag dmafअगरo;	/* 0x380 - 0x38C */

	u32 aggfअगरocnt;	/* 0x390 */
	u32 aggfअगरodata;	/* 0x394 */
	u32 PAD[16];		/* 0x398 - 0x3d4 */
	u16 radioregaddr;	/* 0x3d8 */
	u16 radioregdata;	/* 0x3da */

	/*
	 * समय delay between the change on rf disable input and
	 * radio shutकरोwn
	 */
	u32 rfdisabledly;	/* 0x3DC */

	/* PHY रेजिस्टर access */
	u16 phyversion;	/* 0x3e0 - 0x0 */
	u16 phybbconfig;	/* 0x3e2 - 0x1 */
	u16 phyadcbias;	/* 0x3e4 - 0x2  Bphy only */
	u16 phyanacore;	/* 0x3e6 - 0x3  pwwrdwn on aphy */
	u16 phyrxstatus0;	/* 0x3e8 - 0x4 */
	u16 phyrxstatus1;	/* 0x3ea - 0x5 */
	u16 phycrsth;	/* 0x3ec - 0x6 */
	u16 phytxerror;	/* 0x3ee - 0x7 */
	u16 phychannel;	/* 0x3f0 - 0x8 */
	u16 PAD[1];		/* 0x3f2 - 0x9 */
	u16 phytest;		/* 0x3f4 - 0xa */
	u16 phy4waddr;	/* 0x3f6 - 0xb */
	u16 phy4wdatahi;	/* 0x3f8 - 0xc */
	u16 phy4wdatalo;	/* 0x3fa - 0xd */
	u16 phyregaddr;	/* 0x3fc - 0xe */
	u16 phyregdata;	/* 0x3fe - 0xf */

	/* IHR *//* 0x400 - 0x7FE */

	/* RXE Block */
	u16 PAD[3];		/* 0x400 - 0x406 */
	u16 rcv_fअगरo_ctl;	/* 0x406 */
	u16 PAD;		/* 0x408 - 0x40a */
	u16 rcv_frm_cnt;	/* 0x40a */
	u16 PAD[4];		/* 0x40a - 0x414 */
	u16 rssi;		/* 0x414 */
	u16 PAD[5];		/* 0x414 - 0x420 */
	u16 rcm_ctl;		/* 0x420 */
	u16 rcm_mat_data;	/* 0x422 */
	u16 rcm_mat_mask;	/* 0x424 */
	u16 rcm_mat_dly;	/* 0x426 */
	u16 rcm_cond_mask_l;	/* 0x428 */
	u16 rcm_cond_mask_h;	/* 0x42A */
	u16 rcm_cond_dly;	/* 0x42C */
	u16 PAD[1];		/* 0x42E */
	u16 ext_ihr_addr;	/* 0x430 */
	u16 ext_ihr_data;	/* 0x432 */
	u16 rxe_phyrs_2;	/* 0x434 */
	u16 rxe_phyrs_3;	/* 0x436 */
	u16 phy_mode;	/* 0x438 */
	u16 rcmta_ctl;	/* 0x43a */
	u16 rcmta_size;	/* 0x43c */
	u16 rcmta_addr0;	/* 0x43e */
	u16 rcmta_addr1;	/* 0x440 */
	u16 rcmta_addr2;	/* 0x442 */
	u16 PAD[30];		/* 0x444 - 0x480 */

	/* PSM Block *//* 0x480 - 0x500 */

	u16 PAD;		/* 0x480 */
	u16 psm_maccontrol_h;	/* 0x482 */
	u16 psm_macपूर्णांकstatus_l;	/* 0x484 */
	u16 psm_macपूर्णांकstatus_h;	/* 0x486 */
	u16 psm_macपूर्णांकmask_l;	/* 0x488 */
	u16 psm_macपूर्णांकmask_h;	/* 0x48A */
	u16 PAD;		/* 0x48C */
	u16 psm_maccommand;	/* 0x48E */
	u16 psm_brc;		/* 0x490 */
	u16 psm_phy_hdr_param;	/* 0x492 */
	u16 psm_postcard;	/* 0x494 */
	u16 psm_pcard_loc_l;	/* 0x496 */
	u16 psm_pcard_loc_h;	/* 0x498 */
	u16 psm_gpio_in;	/* 0x49A */
	u16 psm_gpio_out;	/* 0x49C */
	u16 psm_gpio_oe;	/* 0x49E */

	u16 psm_bred_0;	/* 0x4A0 */
	u16 psm_bred_1;	/* 0x4A2 */
	u16 psm_bred_2;	/* 0x4A4 */
	u16 psm_bred_3;	/* 0x4A6 */
	u16 psm_brcl_0;	/* 0x4A8 */
	u16 psm_brcl_1;	/* 0x4AA */
	u16 psm_brcl_2;	/* 0x4AC */
	u16 psm_brcl_3;	/* 0x4AE */
	u16 psm_brpo_0;	/* 0x4B0 */
	u16 psm_brpo_1;	/* 0x4B2 */
	u16 psm_brpo_2;	/* 0x4B4 */
	u16 psm_brpo_3;	/* 0x4B6 */
	u16 psm_brwk_0;	/* 0x4B8 */
	u16 psm_brwk_1;	/* 0x4BA */
	u16 psm_brwk_2;	/* 0x4BC */
	u16 psm_brwk_3;	/* 0x4BE */

	u16 psm_base_0;	/* 0x4C0 */
	u16 psm_base_1;	/* 0x4C2 */
	u16 psm_base_2;	/* 0x4C4 */
	u16 psm_base_3;	/* 0x4C6 */
	u16 psm_base_4;	/* 0x4C8 */
	u16 psm_base_5;	/* 0x4CA */
	u16 psm_base_6;	/* 0x4CC */
	u16 psm_pc_reg_0;	/* 0x4CE */
	u16 psm_pc_reg_1;	/* 0x4D0 */
	u16 psm_pc_reg_2;	/* 0x4D2 */
	u16 psm_pc_reg_3;	/* 0x4D4 */
	u16 PAD[0xD];	/* 0x4D6 - 0x4DE */
	u16 psm_corectlsts;	/* 0x4f0 *//* Corerev >= 13 */
	u16 PAD[0x7];	/* 0x4f2 - 0x4fE */

	/* TXE0 Block *//* 0x500 - 0x580 */
	u16 txe_ctl;		/* 0x500 */
	u16 txe_aux;		/* 0x502 */
	u16 txe_ts_loc;	/* 0x504 */
	u16 txe_समय_out;	/* 0x506 */
	u16 txe_wm_0;	/* 0x508 */
	u16 txe_wm_1;	/* 0x50A */
	u16 txe_phyctl;	/* 0x50C */
	u16 txe_status;	/* 0x50E */
	u16 txe_mmplcp0;	/* 0x510 */
	u16 txe_mmplcp1;	/* 0x512 */
	u16 txe_phyctl1;	/* 0x514 */

	u16 PAD[0x05];	/* 0x510 - 0x51E */

	/* Transmit control */
	u16 xmtfअगरodef;	/* 0x520 */
	u16 xmtfअगरo_frame_cnt;	/* 0x522 *//* Corerev >= 16 */
	u16 xmtfअगरo_byte_cnt;	/* 0x524 *//* Corerev >= 16 */
	u16 xmtfअगरo_head;	/* 0x526 *//* Corerev >= 16 */
	u16 xmtfअगरo_rd_ptr;	/* 0x528 *//* Corerev >= 16 */
	u16 xmtfअगरo_wr_ptr;	/* 0x52A *//* Corerev >= 16 */
	u16 xmtfअगरodef1;	/* 0x52C *//* Corerev >= 16 */

	u16 PAD[0x09];	/* 0x52E - 0x53E */

	u16 xmtfअगरocmd;	/* 0x540 */
	u16 xmtfअगरoflush;	/* 0x542 */
	u16 xmtfअगरothresh;	/* 0x544 */
	u16 xmtfअगरordy;	/* 0x546 */
	u16 xmtfअगरoprirdy;	/* 0x548 */
	u16 xmtfअगरorqpri;	/* 0x54A */
	u16 xmttplatetxptr;	/* 0x54C */
	u16 PAD;		/* 0x54E */
	u16 xmttplateptr;	/* 0x550 */
	u16 smpl_clct_strptr;	/* 0x552 *//* Corerev >= 22 */
	u16 smpl_clct_stpptr;	/* 0x554 *//* Corerev >= 22 */
	u16 smpl_clct_curptr;	/* 0x556 *//* Corerev >= 22 */
	u16 PAD[0x04];	/* 0x558 - 0x55E */
	u16 xmttplatedatalo;	/* 0x560 */
	u16 xmttplatedatahi;	/* 0x562 */

	u16 PAD[2];		/* 0x564 - 0x566 */

	u16 xmtsel;		/* 0x568 */
	u16 xmttxcnt;	/* 0x56A */
	u16 xmttxshmaddr;	/* 0x56C */

	u16 PAD[0x09];	/* 0x56E - 0x57E */

	/* TXE1 Block */
	u16 PAD[0x40];	/* 0x580 - 0x5FE */

	/* TSF Block */
	u16 PAD[0X02];	/* 0x600 - 0x602 */
	u16 tsf_cfpstrt_l;	/* 0x604 */
	u16 tsf_cfpstrt_h;	/* 0x606 */
	u16 PAD[0X05];	/* 0x608 - 0x610 */
	u16 tsf_cfppretbtt;	/* 0x612 */
	u16 PAD[0XD];	/* 0x614 - 0x62C */
	u16 tsf_clk_frac_l;	/* 0x62E */
	u16 tsf_clk_frac_h;	/* 0x630 */
	u16 PAD[0X14];	/* 0x632 - 0x658 */
	u16 tsf_अक्रमom;	/* 0x65A */
	u16 PAD[0x05];	/* 0x65C - 0x664 */
	/* GPTimer 2 रेजिस्टरs */
	u16 tsf_gpt2_stat;	/* 0x666 */
	u16 tsf_gpt2_ctr_l;	/* 0x668 */
	u16 tsf_gpt2_ctr_h;	/* 0x66A */
	u16 tsf_gpt2_val_l;	/* 0x66C */
	u16 tsf_gpt2_val_h;	/* 0x66E */
	u16 tsf_gptall_stat;	/* 0x670 */
	u16 PAD[0x07];	/* 0x672 - 0x67E */

	/* IFS Block */
	u16 अगरs_sअगरs_rx_tx_tx;	/* 0x680 */
	u16 अगरs_sअगरs_nav_tx;	/* 0x682 */
	u16 अगरs_slot;	/* 0x684 */
	u16 PAD;		/* 0x686 */
	u16 अगरs_ctl;		/* 0x688 */
	u16 PAD[0x3];	/* 0x68a - 0x68F */
	u16 अगरsstat;		/* 0x690 */
	u16 अगरsmedbusyctl;	/* 0x692 */
	u16 अगरtxdur;		/* 0x694 */
	u16 PAD[0x3];	/* 0x696 - 0x69b */
	/* EDCF support in करोt11macs */
	u16 अगरs_aअगरsn;	/* 0x69c */
	u16 अगरs_ctl1;	/* 0x69e */

	/* slow घड़ी रेजिस्टरs */
	u16 scc_ctl;		/* 0x6a0 */
	u16 scc_समयr_l;	/* 0x6a2 */
	u16 scc_समयr_h;	/* 0x6a4 */
	u16 scc_frac;	/* 0x6a6 */
	u16 scc_fastpwrup_dly;	/* 0x6a8 */
	u16 scc_per;		/* 0x6aa */
	u16 scc_per_frac;	/* 0x6ac */
	u16 scc_cal_समयr_l;	/* 0x6ae */
	u16 scc_cal_समयr_h;	/* 0x6b0 */
	u16 PAD;		/* 0x6b2 */

	u16 PAD[0x26];

	/* NAV Block */
	u16 nav_ctl;		/* 0x700 */
	u16 navstat;		/* 0x702 */
	u16 PAD[0x3e];	/* 0x702 - 0x77E */

	/* WEP/PMQ Block *//* 0x780 - 0x7FE */
	u16 PAD[0x20];	/* 0x780 - 0x7BE */

	u16 wepctl;		/* 0x7C0 */
	u16 wepivloc;	/* 0x7C2 */
	u16 wepivkey;	/* 0x7C4 */
	u16 wepwkey;		/* 0x7C6 */

	u16 PAD[4];		/* 0x7C8 - 0x7CE */
	u16 pcmctl;		/* 0X7D0 */
	u16 pcmstat;		/* 0X7D2 */
	u16 PAD[6];		/* 0x7D4 - 0x7DE */

	u16 pmqctl;		/* 0x7E0 */
	u16 pmqstatus;	/* 0x7E2 */
	u16 pmqpat0;		/* 0x7E4 */
	u16 pmqpat1;		/* 0x7E6 */
	u16 pmqpat2;		/* 0x7E8 */

	u16 pmqdat;		/* 0x7EA */
	u16 pmqdator;	/* 0x7EC */
	u16 pmqhst;		/* 0x7EE */
	u16 pmqpath0;	/* 0x7F0 */
	u16 pmqpath1;	/* 0x7F2 */
	u16 pmqpath2;	/* 0x7F4 */
	u16 pmqdath;		/* 0x7F6 */

	u16 PAD[0x04];	/* 0x7F8 - 0x7FE */

	/* SHM *//* 0x800 - 0xEFE */
	u16 PAD[0x380];	/* 0x800 - 0xEFE */
पूर्ण;

/* d11 रेजिस्टर field offset */
#घोषणा D11REGOFFS(field)	दुरत्व(काष्ठा d11regs, field)

#घोषणा	PIHR_BASE	0x0400	/* byte address of packed IHR region */

/* biststatus */
#घोषणा	BT_DONE		(1U << 31)	/* bist करोne */
#घोषणा	BT_B2S		(1 << 30)	/* bist2 ram summary bit */

/* पूर्णांकstatus and पूर्णांकmask */
#घोषणा	I_PC		(1 << 10)	/* pci descriptor error */
#घोषणा	I_PD		(1 << 11)	/* pci data error */
#घोषणा	I_DE		(1 << 12)	/* descriptor protocol error */
#घोषणा	I_RU		(1 << 13)	/* receive descriptor underflow */
#घोषणा	I_RO		(1 << 14)	/* receive fअगरo overflow */
#घोषणा	I_XU		(1 << 15)	/* transmit fअगरo underflow */
#घोषणा	I_RI		(1 << 16)	/* receive पूर्णांकerrupt */
#घोषणा	I_XI		(1 << 24)	/* transmit पूर्णांकerrupt */

/* पूर्णांकerrupt receive lazy */
#घोषणा	IRL_TO_MASK		0x00ffffff	/* समयout */
#घोषणा	IRL_FC_MASK		0xff000000	/* frame count */
#घोषणा	IRL_FC_SHIFT		24	/* frame count */

/*== maccontrol रेजिस्टर ==*/
#घोषणा	MCTL_GMODE		(1U << 31)
#घोषणा	MCTL_DISCARD_PMQ	(1 << 30)
#घोषणा	MCTL_TBTTHOLD		(1 << 28)
#घोषणा	MCTL_WAKE		(1 << 26)
#घोषणा	MCTL_HPS		(1 << 25)
#घोषणा	MCTL_PROMISC		(1 << 24)
#घोषणा	MCTL_KEEPBADFCS		(1 << 23)
#घोषणा	MCTL_KEEPCONTROL	(1 << 22)
#घोषणा	MCTL_PHYLOCK		(1 << 21)
#घोषणा	MCTL_BCNS_PROMISC	(1 << 20)
#घोषणा	MCTL_LOCK_RADIO		(1 << 19)
#घोषणा	MCTL_AP			(1 << 18)
#घोषणा	MCTL_INFRA		(1 << 17)
#घोषणा	MCTL_BIGEND		(1 << 16)
#घोषणा	MCTL_GPOUT_SEL_MASK	(3 << 14)
#घोषणा	MCTL_GPOUT_SEL_SHIFT	14
#घोषणा	MCTL_EN_PSMDBG		(1 << 13)
#घोषणा	MCTL_IHR_EN		(1 << 10)
#घोषणा	MCTL_SHM_UPPER		(1 <<  9)
#घोषणा	MCTL_SHM_EN		(1 <<  8)
#घोषणा	MCTL_PSM_JMP_0		(1 <<  2)
#घोषणा	MCTL_PSM_RUN		(1 <<  1)
#घोषणा	MCTL_EN_MAC		(1 <<  0)

/*== maccommand रेजिस्टर ==*/
#घोषणा	MCMD_BCN0VLD		(1 <<  0)
#घोषणा	MCMD_BCN1VLD		(1 <<  1)
#घोषणा	MCMD_सूचीFRMQVAL		(1 <<  2)
#घोषणा	MCMD_CCA		(1 <<  3)
#घोषणा	MCMD_BG_NOISE		(1 <<  4)
#घोषणा	MCMD_SKIP_SHMINIT	(1 <<  5)	/* only used क्रम simulation */
#घोषणा MCMD_SAMPLECOLL		MCMD_SKIP_SHMINIT /* reuse क्रम sample collect */

/*== macपूर्णांकstatus/macपूर्णांकmask ==*/
/* gracefully suspended */
#घोषणा	MI_MACSSPNDD		(1 <<  0)
/* beacon ढाँचा available */
#घोषणा	MI_BCNTPL		(1 <<  1)
/* TBTT indication */
#घोषणा	MI_TBTT			(1 <<  2)
/* beacon successfully tx'd */
#घोषणा	MI_BCNSUCCESS		(1 <<  3)
/* beacon canceled (IBSS) */
#घोषणा	MI_BCNCANCLD		(1 <<  4)
/* end of ATIM-winकरोw (IBSS) */
#घोषणा	MI_ATIMWINEND		(1 <<  5)
/* PMQ entries available */
#घोषणा	MI_PMQ			(1 <<  6)
/* non-specअगरic gen-stat bits that are set by PSM */
#घोषणा	MI_NSPECGEN_0		(1 <<  7)
/* non-specअगरic gen-stat bits that are set by PSM */
#घोषणा	MI_NSPECGEN_1		(1 <<  8)
/* MAC level Tx error */
#घोषणा	MI_MACTXERR		(1 <<  9)
/* non-specअगरic gen-stat bits that are set by PSM */
#घोषणा	MI_NSPECGEN_3		(1 << 10)
/* PHY Tx error */
#घोषणा	MI_PHYTXERR		(1 << 11)
/* Power Management Event */
#घोषणा	MI_PME			(1 << 12)
/* General-purpose समयr0 */
#घोषणा	MI_GP0			(1 << 13)
/* General-purpose समयr1 */
#घोषणा	MI_GP1			(1 << 14)
/* (ORed) DMA-पूर्णांकerrupts */
#घोषणा	MI_DMAINT		(1 << 15)
/* MAC has completed a TX FIFO Suspend/Flush */
#घोषणा	MI_TXSTOP		(1 << 16)
/* MAC has completed a CCA measurement */
#घोषणा	MI_CCA			(1 << 17)
/* MAC has collected background noise samples */
#घोषणा	MI_BG_NOISE		(1 << 18)
/* MBSS DTIM TBTT indication */
#घोषणा	MI_DTIM_TBTT		(1 << 19)
/* Probe response queue needs attention */
#घोषणा MI_PRQ			(1 << 20)
/* Radio/PHY has been घातered back up. */
#घोषणा	MI_PWRUP		(1 << 21)
#घोषणा	MI_RESERVED3		(1 << 22)
#घोषणा	MI_RESERVED2		(1 << 23)
#घोषणा MI_RESERVED1		(1 << 25)
/* MAC detected change on RF Disable input*/
#घोषणा MI_RFDISABLE		(1 << 28)
/* MAC has completed a TX */
#घोषणा	MI_TFS			(1 << 29)
/* A phy status change wrt G mode */
#घोषणा	MI_PHYCHANGED		(1 << 30)
/* general purpose समयout */
#घोषणा	MI_TO			(1U << 31)

/* Mac capabilities रेजिस्टरs */
/*== machwcap ==*/
#घोषणा	MCAP_TKIPMIC		0x80000000	/* TKIP MIC hardware present */

/*== pmqhost data ==*/
/* data entry of head pmq entry */
#घोषणा	PMQH_DATA_MASK		0xffff0000
/* PM entry क्रम BSS config */
#घोषणा	PMQH_BSSCFG		0x00100000
/* PM Mode OFF: घातer save off */
#घोषणा	PMQH_PMOFF		0x00010000
/* PM Mode ON: घातer save on */
#घोषणा	PMQH_PMON		0x00020000
/* Dis-associated or De-authenticated */
#घोषणा	PMQH_DASAT		0x00040000
/* ATIM not acknowledged */
#घोषणा	PMQH_ATIMFAIL		0x00080000
/* delete head entry */
#घोषणा	PMQH_DEL_ENTRY		0x00000001
/* delete head entry to cur पढ़ो poपूर्णांकer -1 */
#घोषणा	PMQH_DEL_MULT		0x00000002
/* pmq overflow indication */
#घोषणा	PMQH_OFLO		0x00000004
/* entries are present in pmq */
#घोषणा	PMQH_NOT_EMPTY		0x00000008

/*== phydebug ==*/
/* phy is निश्चितing carrier sense */
#घोषणा	PDBG_CRS		(1 << 0)
/* phy is taking xmit byte from mac this cycle */
#घोषणा	PDBG_TXA		(1 << 1)
/* mac is inकाष्ठाing the phy to transmit a frame */
#घोषणा	PDBG_TXF		(1 << 2)
/* phy is संकेतling a transmit Error to the mac */
#घोषणा	PDBG_TXE		(1 << 3)
/* phy detected the end of a valid frame preamble */
#घोषणा	PDBG_RXF		(1 << 4)
/* phy detected the end of a valid PLCP header */
#घोषणा	PDBG_RXS		(1 << 5)
/* rx start not निश्चितed */
#घोषणा	PDBG_RXFRG		(1 << 6)
/* mac is taking receive byte from phy this cycle */
#घोषणा	PDBG_RXV		(1 << 7)
/* RF portion of the radio is disabled */
#घोषणा	PDBG_RFD		(1 << 16)

/*== objaddr रेजिस्टर ==*/
#घोषणा	OBJADDR_SEL_MASK	0x000F0000
#घोषणा	OBJADDR_UCM_SEL		0x00000000
#घोषणा	OBJADDR_SHM_SEL		0x00010000
#घोषणा	OBJADDR_SCR_SEL		0x00020000
#घोषणा	OBJADDR_IHR_SEL		0x00030000
#घोषणा	OBJADDR_RCMTA_SEL	0x00040000
#घोषणा	OBJADDR_SRCHM_SEL	0x00060000
#घोषणा	OBJADDR_WINC		0x01000000
#घोषणा	OBJADDR_RINC		0x02000000
#घोषणा	OBJADDR_AUTO_INC	0x03000000

#घोषणा	WEP_PCMADDR		0x07d4
#घोषणा	WEP_PCMDATA		0x07d6

/*== frmtxstatus ==*/
#घोषणा	TXS_V			(1 << 0)	/* valid bit */
#घोषणा	TXS_STATUS_MASK		0xffff
#घोषणा	TXS_FID_MASK		0xffff0000
#घोषणा	TXS_FID_SHIFT		16

/*== frmtxstatus2 ==*/
#घोषणा	TXS_SEQ_MASK		0xffff
#घोषणा	TXS_PTX_MASK		0xff0000
#घोषणा	TXS_PTX_SHIFT		16
#घोषणा	TXS_MU_MASK		0x01000000
#घोषणा	TXS_MU_SHIFT		24

/*== clk_ctl_st ==*/
#घोषणा CCS_ERSRC_REQ_D11PLL	0x00000100	/* d11 core pll request */
#घोषणा CCS_ERSRC_REQ_PHYPLL	0x00000200	/* PHY pll request */
#घोषणा CCS_ERSRC_AVAIL_D11PLL	0x01000000	/* d11 core pll available */
#घोषणा CCS_ERSRC_AVAIL_PHYPLL	0x02000000	/* PHY pll available */

/* HT Cloclk Ctrl and Clock Avail क्रम 4313 */
#घोषणा CCS_ERSRC_REQ_HT    0x00000010	/* HT avail request */
#घोषणा CCS_ERSRC_AVAIL_HT  0x00020000	/* HT घड़ी available */

/* tsf_cfprep रेजिस्टर */
#घोषणा	CFPREP_CBI_MASK		0xffffffc0
#घोषणा	CFPREP_CBI_SHIFT	6
#घोषणा	CFPREP_CFPP		0x00000001

/* tx fअगरo sizes values are in terms of 256 byte blocks */
#घोषणा TXFIFOCMD_RESET_MASK	(1 << 15)	/* reset */
#घोषणा TXFIFOCMD_FIFOSEL_SHIFT	8	/* fअगरo */
#घोषणा TXFIFO_FIFOTOP_SHIFT	8	/* fअगरo start */

#घोषणा TXFIFO_START_BLK16	 65	/* Base address + 32 * 512 B/P */
#घोषणा TXFIFO_START_BLK	 6	/* Base address + 6 * 256 B */
#घोषणा TXFIFO_SIZE_UNIT	256	/* one unit corresponds to 256 bytes */
#घोषणा MBSS16_TEMPLMEM_MINBLKS	65	/* one unit corresponds to 256 bytes */

/*== phy versions (PhyVersion:Revision field) ==*/
/* analog block version */
#घोषणा	PV_AV_MASK		0xf000
/* analog block version bitfield offset */
#घोषणा	PV_AV_SHIFT		12
/* phy type */
#घोषणा	PV_PT_MASK		0x0f00
/* phy type bitfield offset */
#घोषणा	PV_PT_SHIFT		8
/* phy version */
#घोषणा	PV_PV_MASK		0x000f
#घोषणा	PHY_TYPE(v)		((v & PV_PT_MASK) >> PV_PT_SHIFT)

/*== phy types (PhyVersion:PhyType field) ==*/
#घोषणा	PHY_TYPE_N		4	/* N-Phy value */
#घोषणा	PHY_TYPE_SSN		6	/* SSLPN-Phy value */
#घोषणा	PHY_TYPE_LCN		8	/* LCN-Phy value */
#घोषणा	PHY_TYPE_LCNXN		9	/* LCNXN-Phy value */
#घोषणा	PHY_TYPE_शून्य		0xf	/* Invalid Phy value */

/*== analog types (PhyVersion:AnalogType field) ==*/
#घोषणा	ANA_11N_013		5

/* 802.11a PLCP header def */
काष्ठा ofdm_phy_hdr अणु
	u8 rlpt[3];		/* rate, length, parity, tail */
	u16 service;
	u8 pad;
पूर्ण __packed;

#घोषणा	D11A_PHY_HDR_GRATE(phdr)	((phdr)->rlpt[0] & 0x0f)
#घोषणा	D11A_PHY_HDR_GRES(phdr)		(((phdr)->rlpt[0] >> 4) & 0x01)
#घोषणा	D11A_PHY_HDR_GLENGTH(phdr)	(((u32 *)((phdr)->rlpt) >> 5) & 0x0fff)
#घोषणा	D11A_PHY_HDR_GPARITY(phdr)	(((phdr)->rlpt[3] >> 1) & 0x01)
#घोषणा	D11A_PHY_HDR_GTAIL(phdr)	(((phdr)->rlpt[3] >> 2) & 0x3f)

/* rate encoded per 802.11a-1999 sec 17.3.4.1 */
#घोषणा	D11A_PHY_HDR_SRATE(phdr, rate)		\
	((phdr)->rlpt[0] = ((phdr)->rlpt[0] & 0xf0) | ((rate) & 0xf))
/* set reserved field to zero */
#घोषणा	D11A_PHY_HDR_SRES(phdr)		((phdr)->rlpt[0] &= 0xef)
/* length is number of octets in PSDU */
#घोषणा	D11A_PHY_HDR_SLENGTH(phdr, length)	\
	(*(u32 *)((phdr)->rlpt) = *(u32 *)((phdr)->rlpt) | \
	(((length) & 0x0fff) << 5))
/* set the tail to all zeros */
#घोषणा	D11A_PHY_HDR_STAIL(phdr)	((phdr)->rlpt[3] &= 0x03)

#घोषणा	D11A_PHY_HDR_LEN_L	3	/* low-rate part of PLCP header */
#घोषणा	D11A_PHY_HDR_LEN_R	2	/* high-rate part of PLCP header */

#घोषणा	D11A_PHY_TX_DELAY	(2)	/* 2.1 usec */

#घोषणा	D11A_PHY_HDR_TIME	(4)	/* low-rate part of PLCP header */
#घोषणा	D11A_PHY_PRE_TIME	(16)
#घोषणा	D11A_PHY_PREHDR_TIME	(D11A_PHY_PRE_TIME + D11A_PHY_HDR_TIME)

/* 802.11b PLCP header def */
काष्ठा cck_phy_hdr अणु
	u8 संकेत;
	u8 service;
	u16 length;
	u16 crc;
पूर्ण __packed;

#घोषणा	D11B_PHY_HDR_LEN	6

#घोषणा	D11B_PHY_TX_DELAY	(3)	/* 3.4 usec */

#घोषणा	D11B_PHY_LHDR_TIME	(D11B_PHY_HDR_LEN << 3)
#घोषणा	D11B_PHY_LPRE_TIME	(144)
#घोषणा	D11B_PHY_LPREHDR_TIME	(D11B_PHY_LPRE_TIME + D11B_PHY_LHDR_TIME)

#घोषणा	D11B_PHY_SHDR_TIME	(D11B_PHY_LHDR_TIME >> 1)
#घोषणा	D11B_PHY_SPRE_TIME	(D11B_PHY_LPRE_TIME >> 1)
#घोषणा	D11B_PHY_SPREHDR_TIME	(D11B_PHY_SPRE_TIME + D11B_PHY_SHDR_TIME)

#घोषणा	D11B_PLCP_SIGNAL_LOCKED	(1 << 2)
#घोषणा	D11B_PLCP_SIGNAL_LE	(1 << 7)

#घोषणा MIMO_PLCP_MCS_MASK	0x7f	/* mcs index */
#घोषणा MIMO_PLCP_40MHZ		0x80	/* 40 Hz frame */
#घोषणा MIMO_PLCP_AMPDU		0x08	/* ampdu */

#घोषणा BRCMS_GET_CCK_PLCP_LEN(plcp) (plcp[4] + (plcp[5] << 8))
#घोषणा BRCMS_GET_MIMO_PLCP_LEN(plcp) (plcp[1] + (plcp[2] << 8))
#घोषणा BRCMS_SET_MIMO_PLCP_LEN(plcp, len) \
	करो अणु \
		plcp[1] = len & 0xff; \
		plcp[2] = ((len >> 8) & 0xff); \
	पूर्ण जबतक (0)

#घोषणा BRCMS_SET_MIMO_PLCP_AMPDU(plcp) (plcp[3] |= MIMO_PLCP_AMPDU)
#घोषणा BRCMS_CLR_MIMO_PLCP_AMPDU(plcp) (plcp[3] &= ~MIMO_PLCP_AMPDU)
#घोषणा BRCMS_IS_MIMO_PLCP_AMPDU(plcp) (plcp[3] & MIMO_PLCP_AMPDU)

/*
 * The करोt11a PLCP header is 5 bytes.  To simplअगरy the software (so that we
 * करोn't need e.g. dअगरferent tx DMA headers क्रम 11a and 11b), the PLCP header
 * has padding added in the ucode.
 */
#घोषणा	D11_PHY_HDR_LEN	6

/* TX DMA buffer header */
काष्ठा d11txh अणु
	__le16 MacTxControlLow;	/* 0x0 */
	__le16 MacTxControlHigh;	/* 0x1 */
	__le16 MacFrameControl;	/* 0x2 */
	__le16 TxFesTimeNormal;	/* 0x3 */
	__le16 PhyTxControlWord;	/* 0x4 */
	__le16 PhyTxControlWord_1;	/* 0x5 */
	__le16 PhyTxControlWord_1_Fbr;	/* 0x6 */
	__le16 PhyTxControlWord_1_Rts;	/* 0x7 */
	__le16 PhyTxControlWord_1_FbrRts;	/* 0x8 */
	__le16 MainRates;	/* 0x9 */
	__le16 XtraFrameTypes;	/* 0xa */
	u8 IV[16];		/* 0x0b - 0x12 */
	u8 TxFrameRA[6];	/* 0x13 - 0x15 */
	__le16 TxFesTimeFallback;	/* 0x16 */
	u8 RTSPLCPFallback[6];	/* 0x17 - 0x19 */
	__le16 RTSDurFallback;	/* 0x1a */
	u8 FragPLCPFallback[6];	/* 0x1b - 1d */
	__le16 FragDurFallback;	/* 0x1e */
	__le16 MModeLen;	/* 0x1f */
	__le16 MModeFbrLen;	/* 0x20 */
	__le16 TstampLow;	/* 0x21 */
	__le16 TstampHigh;	/* 0x22 */
	__le16 ABI_MimoAntSel;	/* 0x23 */
	__le16 PreloadSize;	/* 0x24 */
	__le16 AmpduSeqCtl;	/* 0x25 */
	__le16 TxFrameID;	/* 0x26 */
	__le16 TxStatus;	/* 0x27 */
	__le16 MaxNMpdus;	/* 0x28 */
	__le16 MaxABytes_MRT;	/* 0x29 */
	__le16 MaxABytes_FBR;	/* 0x2a */
	__le16 MinMBytes;	/* 0x2b */
	u8 RTSPhyHeader[D11_PHY_HDR_LEN];	/* 0x2c - 0x2e */
	काष्ठा ieee80211_rts rts_frame;	/* 0x2f - 0x36 */
	u16 PAD;		/* 0x37 */
पूर्ण __packed __aligned(2);

#घोषणा	D11_TXH_LEN		112	/* bytes */

/* Frame Types */
#घोषणा FT_CCK	0
#घोषणा FT_OFDM	1
#घोषणा FT_HT	2
#घोषणा FT_N	3

/*
 * Position of MPDU inside A-MPDU; indicated with bits 10:9
 * of MacTxControlLow
 */
#घोषणा TXC_AMPDU_SHIFT		9	/* shअगरt क्रम ampdu settings */
#घोषणा TXC_AMPDU_NONE		0	/* Regular MPDU, not an A-MPDU */
#घोषणा TXC_AMPDU_FIRST		1	/* first MPDU of an A-MPDU */
#घोषणा TXC_AMPDU_MIDDLE	2	/* पूर्णांकermediate MPDU of an A-MPDU */
#घोषणा TXC_AMPDU_LAST		3	/* last (or single) MPDU of an A-MPDU */

/*== MacTxControlLow ==*/
#घोषणा TXC_AMIC		0x8000
#घोषणा	TXC_SENDCTS		0x0800
#घोषणा TXC_AMPDU_MASK		0x0600
#घोषणा TXC_BW_40		0x0100
#घोषणा TXC_FREQBAND_5G		0x0080
#घोषणा	TXC_DFCS		0x0040
#घोषणा	TXC_IGNOREPMQ		0x0020
#घोषणा	TXC_HWSEQ		0x0010
#घोषणा	TXC_STARTMSDU		0x0008
#घोषणा	TXC_SENDRTS		0x0004
#घोषणा	TXC_LONGFRAME		0x0002
#घोषणा	TXC_IMMEDACK		0x0001

/*== MacTxControlHigh ==*/
/* RTS fallback preamble type 1 = SHORT 0 = LONG */
#घोषणा TXC_PREAMBLE_RTS_FB_SHORT	0x8000
/* RTS मुख्य rate preamble type 1 = SHORT 0 = LONG */
#घोषणा TXC_PREAMBLE_RTS_MAIN_SHORT	0x4000
/*
 * Main fallback rate preamble type
 *   1 = SHORT क्रम OFDM/GF क्रम MIMO
 *   0 = LONG क्रम CCK/MM क्रम MIMO
 */
#घोषणा TXC_PREAMBLE_DATA_FB_SHORT	0x2000

/* TXC_PREAMBLE_DATA_MAIN is in PhyTxControl bit 5 */
/* use fallback rate क्रम this AMPDU */
#घोषणा	TXC_AMPDU_FBR		0x1000
#घोषणा	TXC_SECKEY_MASK		0x0FF0
#घोषणा	TXC_SECKEY_SHIFT	4
/* Use alternate txpwr defined at loc. M_ALT_TXPWR_IDX */
#घोषणा	TXC_ALT_TXPWR		0x0008
#घोषणा	TXC_SECTYPE_MASK	0x0007
#घोषणा	TXC_SECTYPE_SHIFT	0

/* Null delimiter क्रम Fallback rate */
#घोषणा AMPDU_FBR_शून्य_DELIM  5	/* Location of Null delimiter count क्रम AMPDU */

/* PhyTxControl क्रम Mimophy */
#घोषणा	PHY_TXC_PWR_MASK	0xFC00
#घोषणा	PHY_TXC_PWR_SHIFT	10
#घोषणा	PHY_TXC_ANT_MASK	0x03C0	/* bit 6, 7, 8, 9 */
#घोषणा	PHY_TXC_ANT_SHIFT	6
#घोषणा	PHY_TXC_ANT_0_1		0x00C0	/* स्वतः, last rx */
#घोषणा	PHY_TXC_LCNPHY_ANT_LAST	0x0000
#घोषणा	PHY_TXC_ANT_3		0x0200	/* भव antenna 3 */
#घोषणा	PHY_TXC_ANT_2		0x0100	/* भव antenna 2 */
#घोषणा	PHY_TXC_ANT_1		0x0080	/* भव antenna 1 */
#घोषणा	PHY_TXC_ANT_0		0x0040	/* भव antenna 0 */
#घोषणा	PHY_TXC_SHORT_HDR	0x0010

#घोषणा	PHY_TXC_OLD_ANT_0	0x0000
#घोषणा	PHY_TXC_OLD_ANT_1	0x0100
#घोषणा	PHY_TXC_OLD_ANT_LAST	0x0300

/* PhyTxControl_1 क्रम Mimophy */
#घोषणा PHY_TXC1_BW_MASK		0x0007
#घोषणा PHY_TXC1_BW_10MHZ		0
#घोषणा PHY_TXC1_BW_10MHZ_UP		1
#घोषणा PHY_TXC1_BW_20MHZ		2
#घोषणा PHY_TXC1_BW_20MHZ_UP		3
#घोषणा PHY_TXC1_BW_40MHZ		4
#घोषणा PHY_TXC1_BW_40MHZ_DUP		5
#घोषणा PHY_TXC1_MODE_SHIFT		3
#घोषणा PHY_TXC1_MODE_MASK		0x0038
#घोषणा PHY_TXC1_MODE_SISO		0
#घोषणा PHY_TXC1_MODE_CDD		1
#घोषणा PHY_TXC1_MODE_STBC		2
#घोषणा PHY_TXC1_MODE_SDM		3

/* PhyTxControl क्रम HTphy that are dअगरferent from Mimophy */
#घोषणा	PHY_TXC_HTANT_MASK		0x3fC0	/* bits 6-13 */

/* XtraFrameTypes */
#घोषणा XFTS_RTS_FT_SHIFT	2
#घोषणा XFTS_FBRRTS_FT_SHIFT	4
#घोषणा XFTS_CHANNEL_SHIFT	8

/* Antenna भागersity bit in ant_wr_settle */
#घोषणा	PHY_AWS_ANTDIV		0x2000

/* IFS ctl */
#घोषणा IFS_USEEDCF	(1 << 2)

/* IFS ctl1 */
#घोषणा IFS_CTL1_EDCRS	(1 << 3)
#घोषणा IFS_CTL1_EDCRS_20L (1 << 4)
#घोषणा IFS_CTL1_EDCRS_40 (1 << 5)

/* ABI_MimoAntSel */
#घोषणा ABI_MAS_ADDR_BMP_IDX_MASK	0x0f00
#घोषणा ABI_MAS_ADDR_BMP_IDX_SHIFT	8
#घोषणा ABI_MAS_FBR_ANT_PTN_MASK	0x00f0
#घोषणा ABI_MAS_FBR_ANT_PTN_SHIFT	4
#घोषणा ABI_MAS_MRT_ANT_PTN_MASK	0x000f

/* tx status packet */
काष्ठा tx_status अणु
	u16 framelen;
	u16 PAD;
	u16 frameid;
	u16 status;
	u16 lasttxसमय;
	u16 sequence;
	u16 phyerr;
	u16 ackphyrxsh;
पूर्ण __packed;

#घोषणा	TXSTATUS_LEN	16

/* status field bit definitions */
#घोषणा	TX_STATUS_FRM_RTX_MASK	0xF000
#घोषणा	TX_STATUS_FRM_RTX_SHIFT	12
#घोषणा	TX_STATUS_RTS_RTX_MASK	0x0F00
#घोषणा	TX_STATUS_RTS_RTX_SHIFT	8
#घोषणा TX_STATUS_MASK		0x00FE
#घोषणा	TX_STATUS_PMINDCTD	(1 << 7) /* PM mode indicated to AP */
#घोषणा	TX_STATUS_INTERMEDIATE	(1 << 6) /* पूर्णांकermediate or 1st ampdu pkg */
#घोषणा	TX_STATUS_AMPDU		(1 << 5) /* AMPDU status */
#घोषणा TX_STATUS_SUPR_MASK	0x1C	 /* suppress status bits (4:2) */
#घोषणा TX_STATUS_SUPR_SHIFT	2
#घोषणा	TX_STATUS_ACK_RCV	(1 << 1) /* ACK received */
#घोषणा	TX_STATUS_VALID		(1 << 0) /* Tx status valid */
#घोषणा	TX_STATUS_NO_ACK	0

/* suppress status reason codes */
#घोषणा	TX_STATUS_SUPR_PMQ	(1 << 2) /* PMQ entry */
#घोषणा	TX_STATUS_SUPR_FLUSH	(2 << 2) /* flush request */
#घोषणा	TX_STATUS_SUPR_FRAG	(3 << 2) /* previous frag failure */
#घोषणा	TX_STATUS_SUPR_TBTT	(3 << 2) /* SHARED: Probe resp supr क्रम TBTT */
#घोषणा	TX_STATUS_SUPR_BADCH	(4 << 2) /* channel mismatch */
#घोषणा	TX_STATUS_SUPR_EXPTIME	(5 << 2) /* lअगरeसमय expiry */
#घोषणा	TX_STATUS_SUPR_UF	(6 << 2) /* underflow */

/* Unexpected tx status क्रम rate update */
#घोषणा TX_STATUS_UNEXP(status) \
	((((status) & TX_STATUS_INTERMEDIATE) != 0) && \
	 TX_STATUS_UNEXP_AMPDU(status))

/* Unexpected tx status क्रम A-MPDU rate update */
#घोषणा TX_STATUS_UNEXP_AMPDU(status) \
	((((status) & TX_STATUS_SUPR_MASK) != 0) && \
	 (((status) & TX_STATUS_SUPR_MASK) != TX_STATUS_SUPR_EXPTIME))

#घोषणा TX_STATUS_BA_BMAP03_MASK	0xF000	/* ba biपंचांगap 0:3 in 1st pkg */
#घोषणा TX_STATUS_BA_BMAP03_SHIFT	12	/* ba biपंचांगap 0:3 in 1st pkg */
#घोषणा TX_STATUS_BA_BMAP47_MASK	0x001E	/* ba biपंचांगap 4:7 in 2nd pkg */
#घोषणा TX_STATUS_BA_BMAP47_SHIFT	3	/* ba biपंचांगap 4:7 in 2nd pkg */

/* RXE (Receive Engine) */

/* RCM_CTL */
#घोषणा	RCM_INC_MASK_H		0x0080
#घोषणा	RCM_INC_MASK_L		0x0040
#घोषणा	RCM_INC_DATA		0x0020
#घोषणा	RCM_INDEX_MASK		0x001F
#घोषणा	RCM_SIZE		15

#घोषणा	RCM_MAC_OFFSET		0	/* current MAC address */
#घोषणा	RCM_BSSID_OFFSET	3	/* current BSSID address */
#घोषणा	RCM_F_BSSID_0_OFFSET	6	/* क्रमeign BSS CFP tracking */
#घोषणा	RCM_F_BSSID_1_OFFSET	9	/* क्रमeign BSS CFP tracking */
#घोषणा	RCM_F_BSSID_2_OFFSET	12	/* क्रमeign BSS CFP tracking */

#घोषणा RCM_WEP_TA0_OFFSET	16
#घोषणा RCM_WEP_TA1_OFFSET	19
#घोषणा RCM_WEP_TA2_OFFSET	22
#घोषणा RCM_WEP_TA3_OFFSET	25

/* PSM Block */

/* psm_phy_hdr_param bits */
#घोषणा MAC_PHY_RESET		1
#घोषणा MAC_PHY_CLOCK_EN	2
#घोषणा MAC_PHY_FORCE_CLK	4

/* WEP Block */

/* WEP_WKEY */
#घोषणा	WKEY_START		(1 << 8)
#घोषणा	WKEY_SEL_MASK		0x1F

/* WEP data क्रमmats */

/* the number of RCMTA entries */
#घोषणा RCMTA_SIZE 50

#घोषणा M_ADDR_BMP_BLK		(0x37e * 2)
#घोषणा M_ADDR_BMP_BLK_SZ	12

#घोषणा ADDR_BMP_RA		(1 << 0)	/* Receiver Address (RA) */
#घोषणा ADDR_BMP_TA		(1 << 1)	/* Transmitter Address (TA) */
#घोषणा ADDR_BMP_BSSID		(1 << 2)	/* BSSID */
#घोषणा ADDR_BMP_AP		(1 << 3)	/* Infra-BSS Access Poपूर्णांक */
#घोषणा ADDR_BMP_STA		(1 << 4)	/* Infra-BSS Station */
#घोषणा ADDR_BMP_RESERVED1	(1 << 5)
#घोषणा ADDR_BMP_RESERVED2	(1 << 6)
#घोषणा ADDR_BMP_RESERVED3	(1 << 7)
#घोषणा ADDR_BMP_BSS_IDX_MASK	(3 << 8)	/* BSS control block index */
#घोषणा ADDR_BMP_BSS_IDX_SHIFT	8

#घोषणा	WSEC_MAX_RCMTA_KEYS	54

/* max keys in M_TKMICKEYS_BLK */
#घोषणा	WSEC_MAX_TKMIC_ENGINE_KEYS		12	/* 8 + 4 शेष */

/* max RXE match रेजिस्टरs */
#घोषणा WSEC_MAX_RXE_KEYS	4

/* SECKINDXALGO (Security Key Index & Algorithm Block) word क्रमmat */
/* SKL (Security Key Lookup) */
#घोषणा	SKL_ALGO_MASK		0x0007
#घोषणा	SKL_ALGO_SHIFT		0
#घोषणा	SKL_KEYID_MASK		0x0008
#घोषणा	SKL_KEYID_SHIFT		3
#घोषणा	SKL_INDEX_MASK		0x03F0
#घोषणा	SKL_INDEX_SHIFT		4
#घोषणा	SKL_GRP_ALGO_MASK	0x1c00
#घोषणा	SKL_GRP_ALGO_SHIFT	10

/* additional bits defined क्रम IBSS group key support */
#घोषणा	SKL_IBSS_INDEX_MASK	0x01F0
#घोषणा	SKL_IBSS_INDEX_SHIFT	4
#घोषणा	SKL_IBSS_KEYID1_MASK	0x0600
#घोषणा	SKL_IBSS_KEYID1_SHIFT	9
#घोषणा	SKL_IBSS_KEYID2_MASK	0x1800
#घोषणा	SKL_IBSS_KEYID2_SHIFT	11
#घोषणा	SKL_IBSS_KEYALGO_MASK	0xE000
#घोषणा	SKL_IBSS_KEYALGO_SHIFT	13

#घोषणा	WSEC_MODE_OFF		0
#घोषणा	WSEC_MODE_HW		1
#घोषणा	WSEC_MODE_SW		2

#घोषणा	WSEC_ALGO_OFF		0
#घोषणा	WSEC_ALGO_WEP1		1
#घोषणा	WSEC_ALGO_TKIP		2
#घोषणा	WSEC_ALGO_AES		3
#घोषणा	WSEC_ALGO_WEP128	4
#घोषणा	WSEC_ALGO_AES_LEGACY	5
#घोषणा	WSEC_ALGO_NALG		6

#घोषणा	AES_MODE_NONE		0
#घोषणा	AES_MODE_CCM		1

/* WEP_CTL (Rev 0) */
#घोषणा	WECR0_KEYREG_SHIFT	0
#घोषणा	WECR0_KEYREG_MASK	0x7
#घोषणा	WECR0_DECRYPT		(1 << 3)
#घोषणा	WECR0_IVINLINE		(1 << 4)
#घोषणा	WECR0_WEPALG_SHIFT	5
#घोषणा	WECR0_WEPALG_MASK	(0x7 << 5)
#घोषणा	WECR0_WKEYSEL_SHIFT	8
#घोषणा	WECR0_WKEYSEL_MASK	(0x7 << 8)
#घोषणा	WECR0_WKEYSTART		(1 << 11)
#घोषणा	WECR0_WEPINIT		(1 << 14)
#घोषणा	WECR0_ICVERR		(1 << 15)

/* Frame ढाँचा map byte offsets */
#घोषणा	T_ACTS_TPL_BASE		(0)
#घोषणा	T_शून्य_TPL_BASE		(0xc * 2)
#घोषणा	T_Qशून्य_TPL_BASE	(0x1c * 2)
#घोषणा	T_RR_TPL_BASE		(0x2c * 2)
#घोषणा	T_BCN0_TPL_BASE		(0x34 * 2)
#घोषणा	T_PRS_TPL_BASE		(0x134 * 2)
#घोषणा	T_BCN1_TPL_BASE		(0x234 * 2)
#घोषणा T_TX_FIFO_TXRAM_BASE	(T_ACTS_TPL_BASE + \
				 (TXFIFO_START_BLK * TXFIFO_SIZE_UNIT))

#घोषणा T_BA_TPL_BASE		T_Qशून्य_TPL_BASE /* ढाँचा area क्रम BA */

#घोषणा T_RAM_ACCESS_SZ		4	/* ढाँचा ram is 4 byte access only */

/* Shared Mem byte offsets */

/* Location where the ucode expects the corerev */
#घोषणा	M_MACHW_VER		(0x00b * 2)

/* Location where the ucode expects the MAC capabilities */
#घोषणा	M_MACHW_CAP_L		(0x060 * 2)
#घोषणा	M_MACHW_CAP_H	(0x061 * 2)

/* WME shared memory */
#घोषणा M_EDCF_STATUS_OFF	(0x007 * 2)
#घोषणा M_TXF_CUR_INDEX		(0x018 * 2)
#घोषणा M_EDCF_QINFO		(0x120 * 2)

/* PS-mode related parameters */
#घोषणा	M_DOT11_SLOT		(0x008 * 2)
#घोषणा	M_DOT11_DTIMPERIOD	(0x009 * 2)
#घोषणा	M_NOSLPZNATDTIM		(0x026 * 2)

/* Beacon-related parameters */
#घोषणा	M_BCN0_FRM_BYTESZ	(0x00c * 2)	/* Bcn 0 ढाँचा length */
#घोषणा	M_BCN1_FRM_BYTESZ	(0x00d * 2)	/* Bcn 1 ढाँचा length */
#घोषणा	M_BCN_TXTSF_OFFSET	(0x00e * 2)
#घोषणा	M_TIMBPOS_INBEACON	(0x00f * 2)
#घोषणा	M_SFRMTXCNTFBRTHSD	(0x022 * 2)
#घोषणा	M_LFRMTXCNTFBRTHSD	(0x023 * 2)
#घोषणा	M_BCN_PCTLWD		(0x02a * 2)
#घोषणा M_BCN_LI		(0x05b * 2)	/* beacon listen पूर्णांकerval */

/* MAX Rx Frame len */
#घोषणा M_MAXRXFRM_LEN		(0x010 * 2)

/* ACK/CTS related params */
#घोषणा	M_RSP_PCTLWD		(0x011 * 2)

/* Hardware Power Control */
#घोषणा M_TXPWR_N		(0x012 * 2)
#घोषणा M_TXPWR_TARGET		(0x013 * 2)
#घोषणा M_TXPWR_MAX		(0x014 * 2)
#घोषणा M_TXPWR_CUR		(0x019 * 2)

/* Rx-related parameters */
#घोषणा	M_RX_PAD_DATA_OFFSET	(0x01a * 2)

/* WEP Shared mem data */
#घोषणा	M_SEC_DEFIVLOC		(0x01e * 2)
#घोषणा	M_SEC_VALNUMSOFTMCHTA	(0x01f * 2)
#घोषणा	M_PHYVER		(0x028 * 2)
#घोषणा	M_PHYTYPE		(0x029 * 2)
#घोषणा	M_SECRXKEYS_PTR		(0x02b * 2)
#घोषणा	M_TKMICKEYS_PTR		(0x059 * 2)
#घोषणा	M_SECKINDXALGO_BLK	(0x2ea * 2)
#घोषणा M_SECKINDXALGO_BLK_SZ	54
#घोषणा	M_SECPSMRXTAMCH_BLK	(0x2fa * 2)
#घोषणा	M_TKIP_TSC_TTAK		(0x18c * 2)
#घोषणा	D11_MAX_KEY_SIZE	16

#घोषणा	M_MAX_ANTCNT		(0x02e * 2)	/* antenna swap threshold */

/* Probe response related parameters */
#घोषणा	M_SSIDLEN		(0x024 * 2)
#घोषणा	M_PRB_RESP_FRM_LEN	(0x025 * 2)
#घोषणा	M_PRS_MAXTIME		(0x03a * 2)
#घोषणा	M_SSID			(0xb0 * 2)
#घोषणा	M_CTXPRS_BLK		(0xc0 * 2)
#घोषणा	C_CTX_PCTLWD_POS	(0x4 * 2)

/* Delta between OFDM and CCK घातer in CCK घातer boost mode */
#घोषणा M_OFDM_OFFSET		(0x027 * 2)

/* TSSI क्रम last 4 11b/g CCK packets transmitted */
#घोषणा	M_B_TSSI_0		(0x02c * 2)
#घोषणा	M_B_TSSI_1		(0x02d * 2)

/* Host flags to turn on ucode options */
#घोषणा	M_HOST_FLAGS1		(0x02f * 2)
#घोषणा	M_HOST_FLAGS2		(0x030 * 2)
#घोषणा	M_HOST_FLAGS3		(0x031 * 2)
#घोषणा	M_HOST_FLAGS4		(0x03c * 2)
#घोषणा	M_HOST_FLAGS5		(0x06a * 2)
#घोषणा	M_HOST_FLAGS_SZ		16

#घोषणा M_RADAR_REG		(0x033 * 2)

/* TSSI क्रम last 4 11a OFDM packets transmitted */
#घोषणा	M_A_TSSI_0		(0x034 * 2)
#घोषणा	M_A_TSSI_1		(0x035 * 2)

/* noise पूर्णांकerference measurement */
#घोषणा M_NOISE_IF_COUNT	(0x034 * 2)
#घोषणा M_NOISE_IF_TIMEOUT	(0x035 * 2)

#घोषणा	M_RF_RX_SP_REG1		(0x036 * 2)

/* TSSI क्रम last 4 11g OFDM packets transmitted */
#घोषणा	M_G_TSSI_0		(0x038 * 2)
#घोषणा	M_G_TSSI_1		(0x039 * 2)

/* Background noise measure */
#घोषणा	M_JSSI_0		(0x44 * 2)
#घोषणा	M_JSSI_1		(0x45 * 2)
#घोषणा	M_JSSI_AUX		(0x46 * 2)

#घोषणा	M_CUR_2050_RADIOCODE	(0x47 * 2)

/* TX fअगरo sizes */
#घोषणा M_FIFOSIZE0		(0x4c * 2)
#घोषणा M_FIFOSIZE1		(0x4d * 2)
#घोषणा M_FIFOSIZE2		(0x4e * 2)
#घोषणा M_FIFOSIZE3		(0x4f * 2)
#घोषणा D11_MAX_TX_FRMS		32	/* max frames allowed in tx fअगरo */

/* Current channel number plus upper bits */
#घोषणा M_CURCHANNEL		(0x50 * 2)
#घोषणा D11_CURCHANNEL_5G	0x0100;
#घोषणा D11_CURCHANNEL_40	0x0200;
#घोषणा D11_CURCHANNEL_MAX	0x00FF;

/* last posted frameid on the bcmc fअगरo */
#घोषणा M_BCMC_FID		(0x54 * 2)
#घोषणा INVALIDFID		0xffff

/* extended beacon phyctl bytes क्रम 11N */
#घोषणा	M_BCN_PCTL1WD		(0x058 * 2)

/* idle busy ratio to duty_cycle requirement  */
#घोषणा M_TX_IDLE_BUSY_RATIO_X_16_CCK  (0x52 * 2)
#घोषणा M_TX_IDLE_BUSY_RATIO_X_16_OFDM (0x5A * 2)

/* CW RSSI क्रम LCNPHY */
#घोषणा M_LCN_RSSI_0		0x1332
#घोषणा M_LCN_RSSI_1		0x1338
#घोषणा M_LCN_RSSI_2		0x133e
#घोषणा M_LCN_RSSI_3		0x1344

/* SNR क्रम LCNPHY */
#घोषणा M_LCN_SNR_A_0	0x1334
#घोषणा M_LCN_SNR_B_0	0x1336

#घोषणा M_LCN_SNR_A_1	0x133a
#घोषणा M_LCN_SNR_B_1	0x133c

#घोषणा M_LCN_SNR_A_2	0x1340
#घोषणा M_LCN_SNR_B_2	0x1342

#घोषणा M_LCN_SNR_A_3	0x1346
#घोषणा M_LCN_SNR_B_3	0x1348

#घोषणा M_LCN_LAST_RESET	(81*2)
#घोषणा M_LCN_LAST_LOC	(63*2)
#घोषणा M_LCNPHY_RESET_STATUS (4902)
#घोषणा M_LCNPHY_DSC_TIME	(0x98d*2)
#घोषणा M_LCNPHY_RESET_CNT_DSC (0x98b*2)
#घोषणा M_LCNPHY_RESET_CNT	(0x98c*2)

/* Rate table offsets */
#घोषणा	M_RT_सूचीMAP_A		(0xe0 * 2)
#घोषणा	M_RT_BBRSMAP_A		(0xf0 * 2)
#घोषणा	M_RT_सूचीMAP_B		(0x100 * 2)
#घोषणा	M_RT_BBRSMAP_B		(0x110 * 2)

/* Rate table entry offsets */
#घोषणा	M_RT_PRS_PLCP_POS	10
#घोषणा	M_RT_PRS_DUR_POS	16
#घोषणा	M_RT_OFDM_PCTL1_POS	18

#घोषणा M_20IN40_IQ			(0x380 * 2)

/* SHM locations where ucode stores the current घातer index */
#घोषणा M_CURR_IDX1		(0x384 * 2)
#घोषणा M_CURR_IDX2		(0x387 * 2)

#घोषणा M_BSCALE_ANT0	(0x5e * 2)
#घोषणा M_BSCALE_ANT1	(0x5f * 2)

/* Antenna Diversity Testing */
#घोषणा M_MIMO_ANTSEL_RXDFLT	(0x63 * 2)
#घोषणा M_ANTSEL_CLKDIV	(0x61 * 2)
#घोषणा M_MIMO_ANTSEL_TXDFLT	(0x64 * 2)

#घोषणा M_MIMO_MAXSYM	(0x5d * 2)
#घोषणा MIMO_MAXSYM_DEF		0x8000	/* 32k */
#घोषणा MIMO_MAXSYM_MAX		0xffff	/* 64k */

#घोषणा M_WATCHDOG_8TU		(0x1e * 2)
#घोषणा WATCHDOG_8TU_DEF	5
#घोषणा WATCHDOG_8TU_MAX	10

/* Manufacturing Test Variables */
/* PER test mode */
#घोषणा M_PKTENG_CTRL		(0x6c * 2)
/* IFS क्रम TX mode */
#घोषणा M_PKTENG_IFS		(0x6d * 2)
/* Lower word of tx frmcnt/rx lostcnt */
#घोषणा M_PKTENG_FRMCNT_LO	(0x6e * 2)
/* Upper word of tx frmcnt/rx lostcnt */
#घोषणा M_PKTENG_FRMCNT_HI	(0x6f * 2)

/* Index variation in vbat ripple */
#घोषणा M_LCN_PWR_IDX_MAX	(0x67 * 2) /* highest index पढ़ो by ucode */
#घोषणा M_LCN_PWR_IDX_MIN	(0x66 * 2) /* lowest index पढ़ो by ucode */

/* M_PKTENG_CTRL bit definitions */
#घोषणा M_PKTENG_MODE_TX		0x0001
#घोषणा M_PKTENG_MODE_TX_RIFS	        0x0004
#घोषणा M_PKTENG_MODE_TX_CTS            0x0008
#घोषणा M_PKTENG_MODE_RX		0x0002
#घोषणा M_PKTENG_MODE_RX_WITH_ACK	0x0402
#घोषणा M_PKTENG_MODE_MASK		0x0003
/* TX frames indicated in the frmcnt reg */
#घोषणा M_PKTENG_FRMCNT_VLD		0x0100

/* Sample Collect parameters (biपंचांगap and type) */
/* Trigger biपंचांगap क्रम sample collect */
#घोषणा M_SMPL_COL_BMP		(0x37d * 2)
/* Sample collect type */
#घोषणा M_SMPL_COL_CTL		(0x3b2 * 2)

#घोषणा ANTSEL_CLKDIV_4MHZ	6
#घोषणा MIMO_ANTSEL_BUSY	0x4000	/* bit 14 (busy) */
#घोषणा MIMO_ANTSEL_SEL		0x8000	/* bit 15 ग_लिखो the value */
#घोषणा MIMO_ANTSEL_WAIT	50	/* 50us रुको */
#घोषणा MIMO_ANTSEL_OVERRIDE	0x8000	/* flag */

काष्ठा shm_acparams अणु
	u16 txop;
	u16 cwmin;
	u16 cwmax;
	u16 cwcur;
	u16 aअगरs;
	u16 bslots;
	u16 reggap;
	u16 status;
	u16 rsvd[8];
पूर्ण __packed;
#घोषणा M_EDCF_QLEN	(16 * 2)

#घोषणा WME_STATUS_NEWAC	(1 << 8)

/* M_HOST_FLAGS */
#घोषणा MHFMAX		5	/* Number of valid hostflag half-word (u16) */
#घोषणा MHF1		0	/* Hostflag 1 index */
#घोषणा MHF2		1	/* Hostflag 2 index */
#घोषणा MHF3		2	/* Hostflag 3 index */
#घोषणा MHF4		3	/* Hostflag 4 index */
#घोषणा MHF5		4	/* Hostflag 5 index */

/* Flags in M_HOST_FLAGS */
/* Enable ucode antenna भागersity help */
#घोषणा	MHF1_ANTDIV		0x0001
/* Enable EDCF access control */
#घोषणा	MHF1_EDCF		0x0100
#घोषणा MHF1_IQSWAP_WAR		0x0200
/* Disable Slow घड़ी request, क्रम corerev < 11 */
#घोषणा	MHF1_FORCEFASTCLK	0x0400

/* Flags in M_HOST_FLAGS2 */

/* Flush BCMC FIFO immediately */
#घोषणा MHF2_TXBCMC_NOW		0x0040
/* Enable ucode/hw घातer control */
#घोषणा MHF2_HWPWRCTL		0x0080
#घोषणा MHF2_NPHY40MHZ_WAR	0x0800

/* Flags in M_HOST_FLAGS3 */
/* enabled mimo antenna selection */
#घोषणा MHF3_ANTSEL_EN		0x0001
/* antenna selection mode: 0: 2x3, 1: 2x4 */
#घोषणा MHF3_ANTSEL_MODE	0x0002
#घोषणा MHF3_RESERVED1		0x0004
#घोषणा MHF3_RESERVED2		0x0008
#घोषणा MHF3_NPHY_MLADV_WAR	0x0010

/* Flags in M_HOST_FLAGS4 */
/* क्रमce bphy Tx on core 0 (board level WAR) */
#घोषणा MHF4_BPHY_TXCORE0	0x0080
/* क्रम 4313A0 FEM boards */
#घोषणा MHF4_EXTPA_ENABLE	0x4000

/* Flags in M_HOST_FLAGS5 */
#घोषणा MHF5_4313_GPIOCTRL	0x0001
#घोषणा MHF5_RESERVED1		0x0002
#घोषणा MHF5_RESERVED2		0x0004
/* Radio घातer setting क्रम ucode */
#घोषणा	M_RADIO_PWR		(0x32 * 2)

/* phy noise recorded by ucode right after tx */
#घोषणा	M_PHY_NOISE		(0x037 * 2)
#घोषणा	PHY_NOISE_MASK		0x00ff

/*
 * Receive Frame Data Header क्रम 802.11b DCF-only frames
 *
 * RxFrameSize: Actual byte length of the frame data received
 * PAD: padding (not used)
 * PhyRxStatus_0: PhyRxStatus 15:0
 * PhyRxStatus_1: PhyRxStatus 31:16
 * PhyRxStatus_2: PhyRxStatus 47:32
 * PhyRxStatus_3: PhyRxStatus 63:48
 * PhyRxStatus_4: PhyRxStatus 79:64
 * PhyRxStatus_5: PhyRxStatus 95:80
 * RxStatus1: MAC Rx Status
 * RxStatus2: extended MAC Rx status
 * RxTSFTime: RxTSFTime समय of first MAC symbol + M_PHY_PLCPRX_DLY
 * RxChan: gain code, channel radio code, and phy type
 */
काष्ठा d11rxhdr_le अणु
	__le16 RxFrameSize;
	u16 PAD;
	__le16 PhyRxStatus_0;
	__le16 PhyRxStatus_1;
	__le16 PhyRxStatus_2;
	__le16 PhyRxStatus_3;
	__le16 PhyRxStatus_4;
	__le16 PhyRxStatus_5;
	__le16 RxStatus1;
	__le16 RxStatus2;
	__le16 RxTSFTime;
	__le16 RxChan;
पूर्ण __packed;

काष्ठा d11rxhdr अणु
	u16 RxFrameSize;
	u16 PAD;
	u16 PhyRxStatus_0;
	u16 PhyRxStatus_1;
	u16 PhyRxStatus_2;
	u16 PhyRxStatus_3;
	u16 PhyRxStatus_4;
	u16 PhyRxStatus_5;
	u16 RxStatus1;
	u16 RxStatus2;
	u16 RxTSFTime;
	u16 RxChan;
पूर्ण __packed;

/* PhyRxStatus_0: */
/* NPHY only: CCK, OFDM, preN, N */
#घोषणा	PRXS0_FT_MASK		0x0003
/* NPHY only: clip count adjusपंचांगent steps by AGC */
#घोषणा	PRXS0_CLIP_MASK		0x000C
#घोषणा	PRXS0_CLIP_SHIFT	2
/* PHY received a frame with unsupported rate */
#घोषणा	PRXS0_UNSRATE		0x0010
/* GPHY: rx ant, NPHY: upper sideband */
#घोषणा	PRXS0_RXANT_UPSUBBAND	0x0020
/* CCK frame only: lost crs during cck frame reception */
#घोषणा	PRXS0_LCRS		0x0040
/* Short Preamble */
#घोषणा	PRXS0_SHORTH		0x0080
/* PLCP violation */
#घोषणा	PRXS0_PLCPFV		0x0100
/* PLCP header पूर्णांकegrity check failed */
#घोषणा	PRXS0_PLCPHCF		0x0200
/* legacy PHY gain control */
#घोषणा	PRXS0_GAIN_CTL		0x4000
/* NPHY: Antennas used क्रम received frame, biपंचांगask */
#घोषणा PRXS0_ANTSEL_MASK	0xF000
#घोषणा PRXS0_ANTSEL_SHIFT	0x12

/* subfield PRXS0_FT_MASK */
#घोषणा	PRXS0_CCK		0x0000
/* valid only क्रम G phy, use rxh->RxChan क्रम A phy */
#घोषणा	PRXS0_OFDM		0x0001
#घोषणा	PRXS0_PREN		0x0002
#घोषणा	PRXS0_STDN		0x0003

/* subfield PRXS0_ANTSEL_MASK */
#घोषणा PRXS0_ANTSEL_0		0x0	/* antenna 0 is used */
#घोषणा PRXS0_ANTSEL_1		0x2	/* antenna 1 is used */
#घोषणा PRXS0_ANTSEL_2		0x4	/* antenna 2 is used */
#घोषणा PRXS0_ANTSEL_3		0x8	/* antenna 3 is used */

/* PhyRxStatus_1: */
#घोषणा	PRXS1_JSSI_MASK		0x00FF
#घोषणा	PRXS1_JSSI_SHIFT	0
#घोषणा	PRXS1_SQ_MASK		0xFF00
#घोषणा	PRXS1_SQ_SHIFT		8

/* nphy PhyRxStatus_1: */
#घोषणा PRXS1_nphy_PWR0_MASK	0x00FF
#घोषणा PRXS1_nphy_PWR1_MASK	0xFF00

/* HTPHY Rx Status defines */
/* htphy PhyRxStatus_0: those bit are overlapped with PhyRxStatus_0 */
#घोषणा PRXS0_BAND	        0x0400	/* 0 = 2.4G, 1 = 5G */
#घोषणा PRXS0_RSVD	        0x0800	/* reserved; set to 0 */
#घोषणा PRXS0_UNUSED	        0xF000	/* unused and not defined; set to 0 */

/* htphy PhyRxStatus_1: */
/* core enables क्रम अणु3..0पूर्ण, 0=disabled, 1=enabled */
#घोषणा PRXS1_HTPHY_CORE_MASK	0x000F
/* antenna configuration */
#घोषणा PRXS1_HTPHY_ANTCFG_MASK	0x00F0
/* Mixmode PLCP Length low byte mask */
#घोषणा PRXS1_HTPHY_MMPLCPLenL_MASK	0xFF00

/* htphy PhyRxStatus_2: */
/* Mixmode PLCP Length high byte maskw */
#घोषणा PRXS2_HTPHY_MMPLCPLenH_MASK	0x000F
/* Mixmode PLCP rate mask */
#घोषणा PRXS2_HTPHY_MMPLCH_RATE_MASK	0x00F0
/* Rx घातer on core 0 */
#घोषणा PRXS2_HTPHY_RXPWR_ANT0	0xFF00

/* htphy PhyRxStatus_3: */
/* Rx घातer on core 1 */
#घोषणा PRXS3_HTPHY_RXPWR_ANT1	0x00FF
/* Rx घातer on core 2 */
#घोषणा PRXS3_HTPHY_RXPWR_ANT2	0xFF00

/* htphy PhyRxStatus_4: */
/* Rx घातer on core 3 */
#घोषणा PRXS4_HTPHY_RXPWR_ANT3	0x00FF
/* Coarse frequency offset */
#घोषणा PRXS4_HTPHY_CFO		0xFF00

/* htphy PhyRxStatus_5: */
/* Fine frequency offset */
#घोषणा PRXS5_HTPHY_FFO	        0x00FF
/* Advance Retard */
#घोषणा PRXS5_HTPHY_AR	        0xFF00

#घोषणा HTPHY_MMPLCPLen(rxs) \
	((((rxs)->PhyRxStatus_1 & PRXS1_HTPHY_MMPLCPLenL_MASK) >> 8) | \
	(((rxs)->PhyRxStatus_2 & PRXS2_HTPHY_MMPLCPLenH_MASK) << 8))
/* Get Rx घातer on core 0 */
#घोषणा HTPHY_RXPWR_ANT0(rxs) \
	((((rxs)->PhyRxStatus_2) & PRXS2_HTPHY_RXPWR_ANT0) >> 8)
/* Get Rx घातer on core 1 */
#घोषणा HTPHY_RXPWR_ANT1(rxs) \
	(((rxs)->PhyRxStatus_3) & PRXS3_HTPHY_RXPWR_ANT1)
/* Get Rx घातer on core 2 */
#घोषणा HTPHY_RXPWR_ANT2(rxs) \
	((((rxs)->PhyRxStatus_3) & PRXS3_HTPHY_RXPWR_ANT2) >> 8)

/* ucode RxStatus1: */
#घोषणा	RXS_BCNSENT		0x8000
#घोषणा	RXS_SECKINDX_MASK	0x07e0
#घोषणा	RXS_SECKINDX_SHIFT	5
#घोषणा	RXS_DECERR		(1 << 4)
#घोषणा	RXS_DECATMPT		(1 << 3)
/* PAD bytes to make IP data 4 bytes aligned */
#घोषणा	RXS_PBPRES		(1 << 2)
#घोषणा	RXS_RESPFRAMETX		(1 << 1)
#घोषणा	RXS_FCSERR		(1 << 0)

/* ucode RxStatus2: */
#घोषणा RXS_AMSDU_MASK		1
#घोषणा	RXS_AGGTYPE_MASK	0x6
#घोषणा	RXS_AGGTYPE_SHIFT	1
#घोषणा	RXS_PHYRXST_VALID	(1 << 8)
#घोषणा RXS_RXANT_MASK		0x3
#घोषणा RXS_RXANT_SHIFT		12

/* RxChan */
#घोषणा RXS_CHAN_40		0x1000
#घोषणा RXS_CHAN_5G		0x0800
#घोषणा	RXS_CHAN_ID_MASK	0x07f8
#घोषणा	RXS_CHAN_ID_SHIFT	3
#घोषणा	RXS_CHAN_PHYTYPE_MASK	0x0007
#घोषणा	RXS_CHAN_PHYTYPE_SHIFT	0

/* Index of attenuations used during ucode घातer control. */
#घोषणा M_PWRIND_BLKS	(0x184 * 2)
#घोषणा M_PWRIND_MAP0	(M_PWRIND_BLKS + 0x0)
#घोषणा M_PWRIND_MAP1	(M_PWRIND_BLKS + 0x2)
#घोषणा M_PWRIND_MAP2	(M_PWRIND_BLKS + 0x4)
#घोषणा M_PWRIND_MAP3	(M_PWRIND_BLKS + 0x6)
/* M_PWRIND_MAP(core) macro */
#घोषणा M_PWRIND_MAP(core)  (M_PWRIND_BLKS + ((core)<<1))

/* PSM SHM variable offsets */
#घोषणा	M_PSM_SOFT_REGS	0x0
#घोषणा	M_BOM_REV_MAJOR	(M_PSM_SOFT_REGS + 0x0)
#घोषणा	M_BOM_REV_MINOR	(M_PSM_SOFT_REGS + 0x2)
#घोषणा	M_UCODE_DBGST	(M_PSM_SOFT_REGS + 0x40) /* ucode debug status code */
#घोषणा	M_UCODE_MACSTAT	(M_PSM_SOFT_REGS + 0xE0) /* macstat counters */

#घोषणा M_AGING_THRSH	(0x3e * 2) /* max समय रुकोing क्रम medium beक्रमe tx */
#घोषणा	M_MBURST_SIZE	(0x40 * 2) /* max frames in a frameburst */
#घोषणा	M_MBURST_TXOP	(0x41 * 2) /* max frameburst TXOP in unit of us */
#घोषणा M_SYNTHPU_DLY	(0x4a * 2) /* pre-wakeup क्रम synthpu, शेष: 500 */
#घोषणा	M_PRETBTT	(0x4b * 2)

/* offset to the target txpwr */
#घोषणा M_ALT_TXPWR_IDX		(M_PSM_SOFT_REGS + (0x3b * 2))
#घोषणा M_PHY_TX_FLT_PTR	(M_PSM_SOFT_REGS + (0x3d * 2))
#घोषणा M_CTS_DURATION		(M_PSM_SOFT_REGS + (0x5c * 2))
#घोषणा M_LP_RCCAL_OVR		(M_PSM_SOFT_REGS + (0x6b * 2))

/* PKTENG Rx Stats Block */
#घोषणा M_RXSTATS_BLK_PTR	(M_PSM_SOFT_REGS + (0x65 * 2))

/* ucode debug status codes */
/* not valid really */
#घोषणा	DBGST_INACTIVE		0
/* after zeroing SHM, beक्रमe suspending at init */
#घोषणा	DBGST_INIT		1
/* "normal" state */
#घोषणा	DBGST_ACTIVE		2
/* suspended */
#घोषणा	DBGST_SUSPENDED		3
/* asleep (PS mode) */
#घोषणा	DBGST_ASLEEP		4

/* Scratch Reg defs */
क्रमागत _ePsmScratchPadRegDefinitions अणु
	S_RSV0 = 0,
	S_RSV1,
	S_RSV2,

	/* offset 0x03: scratch रेजिस्टरs क्रम Dot11-contants */
	S_DOT11_CWMIN,		/* CW-minimum */
	S_DOT11_CWMAX,		/* CW-maximum */
	S_DOT11_CWCUR,		/* CW-current */
	S_DOT11_SRC_LMT,	/* लघु retry count limit */
	S_DOT11_LRC_LMT,	/* दीर्घ retry count limit */
	S_DOT11_DTIMCOUNT,	/* DTIM-count */

	/* offset 0x09: Tx-side scratch रेजिस्टरs */
	S_SEQ_NUM,		/* hardware sequence number reg */
	S_SEQ_NUM_FRAG,		/* seq num क्रम frags (at the start of MSDU) */
	S_FRMRETX_CNT,		/* frame retx count */
	S_SSRC,			/* Station लघु retry count */
	S_SLRC,			/* Station दीर्घ retry count */
	S_EXP_RSP,		/* Expected response frame */
	S_OLD_BREM,		/* Reमुख्यing backoff ctr */
	S_OLD_CWWIN,		/* saved-off CW-cur */
	S_TXECTL,		/* TXE-Ctl word स्थिरructed in scr-pad */
	S_CTXTST,		/* frm type-subtype as पढ़ो from Tx-descr */

	/* offset 0x13: Rx-side scratch रेजिस्टरs */
	S_RXTST,		/* Type and subtype in Rxframe */

	/* Global state रेजिस्टर */
	S_STREG,		/* state storage actual bit maps below */

	S_TXPWR_SUM,		/* Tx घातer control: accumulator */
	S_TXPWR_ITER,		/* Tx घातer control: iteration */
	S_RX_FRMTYPE,		/* Rate and PHY type क्रम frames */
	S_THIS_AGG,		/* Size of this AGG (A-MSDU) */

	S_KEYINDX,
	S_RXFRMLEN,		/* Receive MPDU length in bytes */

	/* offset 0x1B: Receive TSF समय stored in SCR */
	S_RXTSFTMRVAL_WD3,	/* TSF value at the start of rx */
	S_RXTSFTMRVAL_WD2,	/* TSF value at the start of rx */
	S_RXTSFTMRVAL_WD1,	/* TSF value at the start of rx */
	S_RXTSFTMRVAL_WD0,	/* TSF value at the start of rx */
	S_RXSSN,		/* Received start seq number क्रम A-MPDU BA */
	S_RXQOSFLD,		/* Rx-QoS field (अगर present) */

	/* offset 0x21: Scratch pad regs used in microcode as temp storage */
	S_TMP0,			/* sपंचांगp0 */
	S_TMP1,			/* sपंचांगp1 */
	S_TMP2,			/* sपंचांगp2 */
	S_TMP3,			/* sपंचांगp3 */
	S_TMP4,			/* sपंचांगp4 */
	S_TMP5,			/* sपंचांगp5 */
	S_PRQPENALTY_CTR,	/* Probe response queue penalty counter */
	S_ANTCNT,		/* unsuccessful attempts on current ant. */
	S_SYMBOL,		/* flag क्रम possible symbol ctl frames */
	S_RXTP,			/* rx frame type */
	S_STREG2,		/* extra state storage */
	S_STREG3,		/* even more extra state storage */
	S_STREG4,		/* ... */
	S_STREG5,		/* remember to initialize it to zero */

	S_ADJPWR_IDX,
	S_CUR_PTR,		/* Temp poपूर्णांकer क्रम A-MPDU re-Tx SHM table */
	S_REVID4,		/* 0x33 */
	S_INDX,			/* 0x34 */
	S_ADDR0,		/* 0x35 */
	S_ADDR1,		/* 0x36 */
	S_ADDR2,		/* 0x37 */
	S_ADDR3,		/* 0x38 */
	S_ADDR4,		/* 0x39 */
	S_ADDR5,		/* 0x3A */
	S_TMP6,			/* 0x3B */
	S_KEYINDX_BU,		/* Backup क्रम Key index */
	S_MFGTEST_TMP0,		/* Temp regs used क्रम RX test calculations */
	S_RXESN,		/* Received end sequence number क्रम A-MPDU BA */
	S_STREG6,		/* 0x3F */
पूर्ण;

#घोषणा S_BEACON_INDX	S_OLD_BREM
#घोषणा S_PRS_INDX	S_OLD_CWWIN
#घोषणा S_PHYTYPE	S_SSRC
#घोषणा S_PHYVER	S_SLRC

/* IHR SLOW_CTRL values */
#घोषणा SLOW_CTRL_PDE		(1 << 0)
#घोषणा SLOW_CTRL_FD		(1 << 8)

/* ucode mac statistic counters in shared memory */
काष्ठा macstat अणु
	u16 txallfrm;	/* 0x80 */
	u16 txrtsfrm;	/* 0x82 */
	u16 txctsfrm;	/* 0x84 */
	u16 txackfrm;	/* 0x86 */
	u16 txdnlfrm;	/* 0x88 */
	u16 txbcnfrm;	/* 0x8a */
	u16 txfunfl[8];	/* 0x8c - 0x9b */
	u16 txtplunfl;	/* 0x9c */
	u16 txphyerr;	/* 0x9e */
	u16 pktengrxducast;	/* 0xa0 */
	u16 pktengrxdmcast;	/* 0xa2 */
	u16 rxfrmtooदीर्घ;	/* 0xa4 */
	u16 rxfrmtooshrt;	/* 0xa6 */
	u16 rxinvmachdr;	/* 0xa8 */
	u16 rxbadfcs;	/* 0xaa */
	u16 rxbadplcp;	/* 0xac */
	u16 rxcrsglitch;	/* 0xae */
	u16 rxstrt;		/* 0xb0 */
	u16 rxdfrmucasपंचांगbss;	/* 0xb2 */
	u16 rxmfrmucasपंचांगbss;	/* 0xb4 */
	u16 rxcfrmucast;	/* 0xb6 */
	u16 rxrtsucast;	/* 0xb8 */
	u16 rxctsucast;	/* 0xba */
	u16 rxackucast;	/* 0xbc */
	u16 rxdfrmocast;	/* 0xbe */
	u16 rxmfrmocast;	/* 0xc0 */
	u16 rxcfrmocast;	/* 0xc2 */
	u16 rxrtsocast;	/* 0xc4 */
	u16 rxctsocast;	/* 0xc6 */
	u16 rxdfrmmcast;	/* 0xc8 */
	u16 rxmfrmmcast;	/* 0xca */
	u16 rxcfrmmcast;	/* 0xcc */
	u16 rxbeaconmbss;	/* 0xce */
	u16 rxdfrmucastobss;	/* 0xd0 */
	u16 rxbeaconobss;	/* 0xd2 */
	u16 rxrspपंचांगout;	/* 0xd4 */
	u16 bcntxcancl;	/* 0xd6 */
	u16 PAD;
	u16 rxf0ovfl;	/* 0xda */
	u16 rxf1ovfl;	/* 0xdc */
	u16 rxf2ovfl;	/* 0xde */
	u16 txsfovfl;	/* 0xe0 */
	u16 pmqovfl;		/* 0xe2 */
	u16 rxcgprqfrm;	/* 0xe4 */
	u16 rxcgprsqovfl;	/* 0xe6 */
	u16 txcgprsfail;	/* 0xe8 */
	u16 txcgprssuc;	/* 0xea */
	u16 prs_समयout;	/* 0xec */
	u16 rxnack;
	u16 frmscons;
	u16 txnack;
	u16 txglitch_nack;
	u16 txburst;		/* 0xf6 # tx bursts */
	u16 bphy_rxcrsglitch;	/* bphy rx crs glitch */
	u16 phywatchकरोg;	/* 0xfa # of phy watchकरोg events */
	u16 PAD;
	u16 bphy_badplcp;	/* bphy bad plcp */
पूर्ण;

/* करोt11 core-specअगरic control flags */
#घोषणा	SICF_PCLKE		0x0004	/* PHY घड़ी enable */
#घोषणा	SICF_PRST		0x0008	/* PHY reset */
#घोषणा	SICF_MPCLKE		0x0010	/* MAC PHY घड़ीcontrol enable */
#घोषणा	SICF_FREF		0x0020	/* PLL FreqRefSelect */
/* NOTE: the following bw bits only apply when the core is attached
 * to a NPHY
 */
#घोषणा	SICF_BWMASK		0x00c0	/* phy घड़ी mask (b6 & b7) */
#घोषणा	SICF_BW40		0x0080	/* 40MHz BW (160MHz phyclk) */
#घोषणा	SICF_BW20		0x0040	/* 20MHz BW (80MHz phyclk) */
#घोषणा	SICF_BW10		0x0000	/* 10MHz BW (40MHz phyclk) */
#घोषणा	SICF_GMODE		0x2000	/* gmode enable */

/* करोt11 core-specअगरic status flags */
#घोषणा	SISF_2G_PHY		0x0001	/* 2.4G capable phy */
#घोषणा	SISF_5G_PHY		0x0002	/* 5G capable phy */
#घोषणा	SISF_FCLKA		0x0004	/* FastClkAvailable */
#घोषणा	SISF_DB_PHY		0x0008	/* Dualband phy */

/* === End of MAC reg, Beginning of PHY(b/a/g/n) reg === */
/* radio and LPPHY regs are separated */

#घोषणा	BPHY_REG_OFT_BASE	0x0
/* offsets क्रम indirect access to bphy रेजिस्टरs */
#घोषणा	BPHY_BB_CONFIG		0x01
#घोषणा	BPHY_ADCBIAS		0x02
#घोषणा	BPHY_ANACORE		0x03
#घोषणा	BPHY_PHYCRSTH		0x06
#घोषणा	BPHY_TEST		0x0a
#घोषणा	BPHY_PA_TX_TO		0x10
#घोषणा	BPHY_SYNTH_DC_TO	0x11
#घोषणा	BPHY_PA_TX_TIME_UP	0x12
#घोषणा	BPHY_RX_FLTR_TIME_UP	0x13
#घोषणा	BPHY_TX_POWER_OVERRIDE	0x14
#घोषणा	BPHY_RF_OVERRIDE	0x15
#घोषणा	BPHY_RF_TR_LOOKUP1	0x16
#घोषणा	BPHY_RF_TR_LOOKUP2	0x17
#घोषणा	BPHY_COEFFS		0x18
#घोषणा	BPHY_PLL_OUT		0x19
#घोषणा	BPHY_REFRESH_MAIN	0x1a
#घोषणा	BPHY_REFRESH_TO0	0x1b
#घोषणा	BPHY_REFRESH_TO1	0x1c
#घोषणा	BPHY_RSSI_TRESH		0x20
#घोषणा	BPHY_IQ_TRESH_HH	0x21
#घोषणा	BPHY_IQ_TRESH_H		0x22
#घोषणा	BPHY_IQ_TRESH_L		0x23
#घोषणा	BPHY_IQ_TRESH_LL	0x24
#घोषणा	BPHY_GAIN		0x25
#घोषणा	BPHY_LNA_GAIN_RANGE	0x26
#घोषणा	BPHY_JSSI		0x27
#घोषणा	BPHY_TSSI_CTL		0x28
#घोषणा	BPHY_TSSI		0x29
#घोषणा	BPHY_TR_LOSS_CTL	0x2a
#घोषणा	BPHY_LO_LEAKAGE		0x2b
#घोषणा	BPHY_LO_RSSI_ACC	0x2c
#घोषणा	BPHY_LO_IQMAG_ACC	0x2d
#घोषणा	BPHY_TX_DC_OFF1		0x2e
#घोषणा	BPHY_TX_DC_OFF2		0x2f
#घोषणा	BPHY_PEAK_CNT_THRESH	0x30
#घोषणा	BPHY_FREQ_OFFSET	0x31
#घोषणा	BPHY_DIVERSITY_CTL	0x32
#घोषणा	BPHY_PEAK_ENERGY_LO	0x33
#घोषणा	BPHY_PEAK_ENERGY_HI	0x34
#घोषणा	BPHY_SYNC_CTL		0x35
#घोषणा	BPHY_TX_PWR_CTRL	0x36
#घोषणा BPHY_TX_EST_PWR		0x37
#घोषणा	BPHY_STEP		0x38
#घोषणा	BPHY_WARMUP		0x39
#घोषणा	BPHY_LMS_CFF_READ	0x3a
#घोषणा	BPHY_LMS_COEFF_I	0x3b
#घोषणा	BPHY_LMS_COEFF_Q	0x3c
#घोषणा	BPHY_SIG_POW		0x3d
#घोषणा	BPHY_RFDC_CANCEL_CTL	0x3e
#घोषणा	BPHY_HDR_TYPE		0x40
#घोषणा	BPHY_SFD_TO		0x41
#घोषणा	BPHY_SFD_CTL		0x42
#घोषणा	BPHY_DEBUG		0x43
#घोषणा	BPHY_RX_DELAY_COMP	0x44
#घोषणा	BPHY_CRS_DROP_TO	0x45
#घोषणा	BPHY_SHORT_SFD_NZEROS	0x46
#घोषणा	BPHY_DSSS_COEFF1	0x48
#घोषणा	BPHY_DSSS_COEFF2	0x49
#घोषणा	BPHY_CCK_COEFF1		0x4a
#घोषणा	BPHY_CCK_COEFF2		0x4b
#घोषणा	BPHY_TR_CORR		0x4c
#घोषणा	BPHY_ANGLE_SCALE	0x4d
#घोषणा	BPHY_TX_PWR_BASE_IDX	0x4e
#घोषणा	BPHY_OPTIONAL_MODES2	0x4f
#घोषणा	BPHY_CCK_LMS_STEP	0x50
#घोषणा	BPHY_BYPASS		0x51
#घोषणा	BPHY_CCK_DELAY_LONG	0x52
#घोषणा	BPHY_CCK_DELAY_SHORT	0x53
#घोषणा	BPHY_PPROC_CHAN_DELAY	0x54
#घोषणा	BPHY_DDFS_ENABLE	0x58
#घोषणा	BPHY_PHASE_SCALE	0x59
#घोषणा	BPHY_FREQ_CONTROL	0x5a
#घोषणा	BPHY_LNA_GAIN_RANGE_10	0x5b
#घोषणा	BPHY_LNA_GAIN_RANGE_32	0x5c
#घोषणा	BPHY_OPTIONAL_MODES	0x5d
#घोषणा	BPHY_RX_STATUS2		0x5e
#घोषणा	BPHY_RX_STATUS3		0x5f
#घोषणा	BPHY_DAC_CONTROL	0x60
#घोषणा	BPHY_ANA11G_FILT_CTRL	0x62
#घोषणा	BPHY_REFRESH_CTRL	0x64
#घोषणा	BPHY_RF_OVERRIDE2	0x65
#घोषणा	BPHY_SPUR_CANCEL_CTRL	0x66
#घोषणा	BPHY_FINE_DIGIGAIN_CTRL	0x67
#घोषणा	BPHY_RSSI_LUT		0x88
#घोषणा	BPHY_RSSI_LUT_END	0xa7
#घोषणा	BPHY_TSSI_LUT		0xa8
#घोषणा	BPHY_TSSI_LUT_END	0xc7
#घोषणा	BPHY_TSSI2PWR_LUT	0x380
#घोषणा	BPHY_TSSI2PWR_LUT_END	0x39f
#घोषणा	BPHY_LOCOMP_LUT		0x3a0
#घोषणा	BPHY_LOCOMP_LUT_END	0x3bf
#घोषणा	BPHY_TXGAIN_LUT		0x3c0
#घोषणा	BPHY_TXGAIN_LUT_END	0x3ff

/* Bits in BB_CONFIG: */
#घोषणा	PHY_BBC_ANT_MASK	0x0180
#घोषणा	PHY_BBC_ANT_SHIFT	7
#घोषणा	BB_DARWIN		0x1000
#घोषणा BBCFG_RESETCCA		0x4000
#घोषणा BBCFG_RESETRX		0x8000

/* Bits in phytest(0x0a): */
#घोषणा	TST_DDFS		0x2000
#घोषणा	TST_TXFILT1		0x0800
#घोषणा	TST_UNSCRAM		0x0400
#घोषणा	TST_CARR_SUPP		0x0200
#घोषणा	TST_DC_COMP_LOOP	0x0100
#घोषणा	TST_LOOPBACK		0x0080
#घोषणा	TST_TXFILT0		0x0040
#घोषणा	TST_TXTEST_ENABLE	0x0020
#घोषणा	TST_TXTEST_RATE		0x0018
#घोषणा	TST_TXTEST_PHASE	0x0007

/* phytest txTestRate values */
#घोषणा	TST_TXTEST_RATE_1MBPS	0
#घोषणा	TST_TXTEST_RATE_2MBPS	1
#घोषणा	TST_TXTEST_RATE_5_5MBPS	2
#घोषणा	TST_TXTEST_RATE_11MBPS	3
#घोषणा	TST_TXTEST_RATE_SHIFT	3

#घोषणा SHM_BYT_CNT	0x2	/* IHR location */
#घोषणा MAX_BYT_CNT	0x600	/* Maximum frame len */

काष्ठा d11cnt अणु
	u32 txfrag;
	u32 txmulti;
	u32 txfail;
	u32 txretry;
	u32 txretrie;
	u32 rxdup;
	u32 txrts;
	u32 txnocts;
	u32 txnoack;
	u32 rxfrag;
	u32 rxmulti;
	u32 rxcrc;
	u32 txfrmsnt;
	u32 rxundec;
पूर्ण;

#पूर्ण_अगर				/* _BRCM_D11_H_ */
