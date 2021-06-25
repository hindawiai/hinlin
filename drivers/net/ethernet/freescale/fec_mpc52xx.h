<शैली गुरु>
/*
 * drivers/net/ethernet/मुक्तscale/fec_mpc52xx.h
 *
 * Driver क्रम the MPC5200 Fast Ethernet Controller
 *
 * Author: Dale Farnsworth <dfarnsworth@mvista.com>
 *
 * 2003-2004 (c) MontaVista, Software, Inc.  This file is licensed under
 * the terms of the GNU General Public License version 2.  This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */

#अगर_अघोषित __DRIVERS_NET_MPC52XX_FEC_H__
#घोषणा __DRIVERS_NET_MPC52XX_FEC_H__

#समावेश <linux/phy.h>

/* Tunable स्थिरant */
/* FEC_RX_BUFFER_SIZE includes 4 bytes क्रम CRC32 */
#घोषणा FEC_RX_BUFFER_SIZE	1522	/* max receive packet size */
#घोषणा FEC_RX_NUM_BD		256
#घोषणा FEC_TX_NUM_BD		64

#घोषणा FEC_RESET_DELAY		50 	/* uS */

#घोषणा FEC_WATCHDOG_TIMEOUT	((400*HZ)/1000)

/* ======================================================================== */
/* Hardware रेजिस्टर sets & bits                                            */
/* ======================================================================== */

काष्ठा mpc52xx_fec अणु
	u32 fec_id;			/* FEC + 0x000 */
	u32 ievent;			/* FEC + 0x004 */
	u32 imask;			/* FEC + 0x008 */

	u32 reserved0[1];		/* FEC + 0x00C */
	u32 r_des_active;		/* FEC + 0x010 */
	u32 x_des_active;		/* FEC + 0x014 */
	u32 r_des_active_cl;		/* FEC + 0x018 */
	u32 x_des_active_cl;		/* FEC + 0x01C */
	u32 ivent_set;			/* FEC + 0x020 */
	u32 ecntrl;			/* FEC + 0x024 */

	u32 reserved1[6];		/* FEC + 0x028-03C */
	u32 mii_data;			/* FEC + 0x040 */
	u32 mii_speed;			/* FEC + 0x044 */
	u32 mii_status;			/* FEC + 0x048 */

	u32 reserved2[5];		/* FEC + 0x04C-05C */
	u32 mib_data;			/* FEC + 0x060 */
	u32 mib_control;		/* FEC + 0x064 */

	u32 reserved3[6];		/* FEC + 0x068-7C */
	u32 r_activate;			/* FEC + 0x080 */
	u32 r_cntrl;			/* FEC + 0x084 */
	u32 r_hash;			/* FEC + 0x088 */
	u32 r_data;			/* FEC + 0x08C */
	u32 ar_करोne;			/* FEC + 0x090 */
	u32 r_test;			/* FEC + 0x094 */
	u32 r_mib;			/* FEC + 0x098 */
	u32 r_da_low;			/* FEC + 0x09C */
	u32 r_da_high;			/* FEC + 0x0A0 */

	u32 reserved4[7];		/* FEC + 0x0A4-0BC */
	u32 x_activate;			/* FEC + 0x0C0 */
	u32 x_cntrl;			/* FEC + 0x0C4 */
	u32 backoff;			/* FEC + 0x0C8 */
	u32 x_data;			/* FEC + 0x0CC */
	u32 x_status;			/* FEC + 0x0D0 */
	u32 x_mib;			/* FEC + 0x0D4 */
	u32 x_test;			/* FEC + 0x0D8 */
	u32 fdxfc_da1;			/* FEC + 0x0DC */
	u32 fdxfc_da2;			/* FEC + 0x0E0 */
	u32 paddr1;			/* FEC + 0x0E4 */
	u32 paddr2;			/* FEC + 0x0E8 */
	u32 op_छोड़ो;			/* FEC + 0x0EC */

	u32 reserved5[4];		/* FEC + 0x0F0-0FC */
	u32 instr_reg;			/* FEC + 0x100 */
	u32 context_reg;		/* FEC + 0x104 */
	u32 test_cntrl;			/* FEC + 0x108 */
	u32 acc_reg;			/* FEC + 0x10C */
	u32 ones;			/* FEC + 0x110 */
	u32 zeros;			/* FEC + 0x114 */
	u32 iaddr1;			/* FEC + 0x118 */
	u32 iaddr2;			/* FEC + 0x11C */
	u32 gaddr1;			/* FEC + 0x120 */
	u32 gaddr2;			/* FEC + 0x124 */
	u32 अक्रमom;			/* FEC + 0x128 */
	u32 अक्रम1;			/* FEC + 0x12C */
	u32 पंचांगp;			/* FEC + 0x130 */

	u32 reserved6[3];		/* FEC + 0x134-13C */
	u32 fअगरo_id;			/* FEC + 0x140 */
	u32 x_wmrk;			/* FEC + 0x144 */
	u32 fcntrl;			/* FEC + 0x148 */
	u32 r_bound;			/* FEC + 0x14C */
	u32 r_fstart;			/* FEC + 0x150 */
	u32 r_count;			/* FEC + 0x154 */
	u32 r_lag;			/* FEC + 0x158 */
	u32 r_पढ़ो;			/* FEC + 0x15C */
	u32 r_ग_लिखो;			/* FEC + 0x160 */
	u32 x_count;			/* FEC + 0x164 */
	u32 x_lag;			/* FEC + 0x168 */
	u32 x_retry;			/* FEC + 0x16C */
	u32 x_ग_लिखो;			/* FEC + 0x170 */
	u32 x_पढ़ो;			/* FEC + 0x174 */

	u32 reserved7[2];		/* FEC + 0x178-17C */
	u32 fm_cntrl;			/* FEC + 0x180 */
	u32 rfअगरo_data;			/* FEC + 0x184 */
	u32 rfअगरo_status;		/* FEC + 0x188 */
	u32 rfअगरo_cntrl;		/* FEC + 0x18C */
	u32 rfअगरo_lrf_ptr;		/* FEC + 0x190 */
	u32 rfअगरo_lwf_ptr;		/* FEC + 0x194 */
	u32 rfअगरo_alarm;		/* FEC + 0x198 */
	u32 rfअगरo_rdptr;		/* FEC + 0x19C */
	u32 rfअगरo_wrptr;		/* FEC + 0x1A0 */
	u32 tfअगरo_data;			/* FEC + 0x1A4 */
	u32 tfअगरo_status;		/* FEC + 0x1A8 */
	u32 tfअगरo_cntrl;		/* FEC + 0x1AC */
	u32 tfअगरo_lrf_ptr;		/* FEC + 0x1B0 */
	u32 tfअगरo_lwf_ptr;		/* FEC + 0x1B4 */
	u32 tfअगरo_alarm;		/* FEC + 0x1B8 */
	u32 tfअगरo_rdptr;		/* FEC + 0x1BC */
	u32 tfअगरo_wrptr;		/* FEC + 0x1C0 */

	u32 reset_cntrl;		/* FEC + 0x1C4 */
	u32 xmit_fsm;			/* FEC + 0x1C8 */

	u32 reserved8[3];		/* FEC + 0x1CC-1D4 */
	u32 rdes_data0;			/* FEC + 0x1D8 */
	u32 rdes_data1;			/* FEC + 0x1DC */
	u32 r_length;			/* FEC + 0x1E0 */
	u32 x_length;			/* FEC + 0x1E4 */
	u32 x_addr;			/* FEC + 0x1E8 */
	u32 cdes_data;			/* FEC + 0x1EC */
	u32 status;			/* FEC + 0x1F0 */
	u32 dma_control;		/* FEC + 0x1F4 */
	u32 des_cmnd;			/* FEC + 0x1F8 */
	u32 data;			/* FEC + 0x1FC */

	u32 rmon_t_drop;		/* FEC + 0x200 */
	u32 rmon_t_packets;		/* FEC + 0x204 */
	u32 rmon_t_bc_pkt;		/* FEC + 0x208 */
	u32 rmon_t_mc_pkt;		/* FEC + 0x20C */
	u32 rmon_t_crc_align;		/* FEC + 0x210 */
	u32 rmon_t_undersize;		/* FEC + 0x214 */
	u32 rmon_t_oversize;		/* FEC + 0x218 */
	u32 rmon_t_frag;		/* FEC + 0x21C */
	u32 rmon_t_jab;			/* FEC + 0x220 */
	u32 rmon_t_col;			/* FEC + 0x224 */
	u32 rmon_t_p64;			/* FEC + 0x228 */
	u32 rmon_t_p65to127;		/* FEC + 0x22C */
	u32 rmon_t_p128to255;		/* FEC + 0x230 */
	u32 rmon_t_p256to511;		/* FEC + 0x234 */
	u32 rmon_t_p512to1023;		/* FEC + 0x238 */
	u32 rmon_t_p1024to2047;		/* FEC + 0x23C */
	u32 rmon_t_p_gte2048;		/* FEC + 0x240 */
	u32 rmon_t_octets;		/* FEC + 0x244 */
	u32 ieee_t_drop;		/* FEC + 0x248 */
	u32 ieee_t_frame_ok;		/* FEC + 0x24C */
	u32 ieee_t_1col;		/* FEC + 0x250 */
	u32 ieee_t_mcol;		/* FEC + 0x254 */
	u32 ieee_t_def;			/* FEC + 0x258 */
	u32 ieee_t_lcol;		/* FEC + 0x25C */
	u32 ieee_t_excol;		/* FEC + 0x260 */
	u32 ieee_t_macerr;		/* FEC + 0x264 */
	u32 ieee_t_cserr;		/* FEC + 0x268 */
	u32 ieee_t_sqe;			/* FEC + 0x26C */
	u32 t_fdxfc;			/* FEC + 0x270 */
	u32 ieee_t_octets_ok;		/* FEC + 0x274 */

	u32 reserved9[2];		/* FEC + 0x278-27C */
	u32 rmon_r_drop;		/* FEC + 0x280 */
	u32 rmon_r_packets;		/* FEC + 0x284 */
	u32 rmon_r_bc_pkt;		/* FEC + 0x288 */
	u32 rmon_r_mc_pkt;		/* FEC + 0x28C */
	u32 rmon_r_crc_align;		/* FEC + 0x290 */
	u32 rmon_r_undersize;		/* FEC + 0x294 */
	u32 rmon_r_oversize;		/* FEC + 0x298 */
	u32 rmon_r_frag;		/* FEC + 0x29C */
	u32 rmon_r_jab;			/* FEC + 0x2A0 */

	u32 rmon_r_resvd_0;		/* FEC + 0x2A4 */

	u32 rmon_r_p64;			/* FEC + 0x2A8 */
	u32 rmon_r_p65to127;		/* FEC + 0x2AC */
	u32 rmon_r_p128to255;		/* FEC + 0x2B0 */
	u32 rmon_r_p256to511;		/* FEC + 0x2B4 */
	u32 rmon_r_p512to1023;		/* FEC + 0x2B8 */
	u32 rmon_r_p1024to2047;		/* FEC + 0x2BC */
	u32 rmon_r_p_gte2048;		/* FEC + 0x2C0 */
	u32 rmon_r_octets;		/* FEC + 0x2C4 */
	u32 ieee_r_drop;		/* FEC + 0x2C8 */
	u32 ieee_r_frame_ok;		/* FEC + 0x2CC */
	u32 ieee_r_crc;			/* FEC + 0x2D0 */
	u32 ieee_r_align;		/* FEC + 0x2D4 */
	u32 r_macerr;			/* FEC + 0x2D8 */
	u32 r_fdxfc;			/* FEC + 0x2DC */
	u32 ieee_r_octets_ok;		/* FEC + 0x2E0 */

	u32 reserved10[7];		/* FEC + 0x2E4-2FC */

	u32 reserved11[64];		/* FEC + 0x300-3FF */
पूर्ण;

#घोषणा	FEC_MIB_DISABLE			0x80000000

#घोषणा	FEC_IEVENT_HBERR		0x80000000
#घोषणा	FEC_IEVENT_BABR			0x40000000
#घोषणा	FEC_IEVENT_BABT			0x20000000
#घोषणा	FEC_IEVENT_GRA			0x10000000
#घोषणा	FEC_IEVENT_TFINT		0x08000000
#घोषणा	FEC_IEVENT_MII			0x00800000
#घोषणा	FEC_IEVENT_LATE_COL		0x00200000
#घोषणा	FEC_IEVENT_COL_RETRY_LIM	0x00100000
#घोषणा	FEC_IEVENT_XFIFO_UN		0x00080000
#घोषणा	FEC_IEVENT_XFIFO_ERROR		0x00040000
#घोषणा	FEC_IEVENT_RFIFO_ERROR		0x00020000

#घोषणा	FEC_IMASK_HBERR			0x80000000
#घोषणा	FEC_IMASK_BABR			0x40000000
#घोषणा	FEC_IMASK_BABT			0x20000000
#घोषणा	FEC_IMASK_GRA			0x10000000
#घोषणा	FEC_IMASK_MII			0x00800000
#घोषणा	FEC_IMASK_LATE_COL		0x00200000
#घोषणा	FEC_IMASK_COL_RETRY_LIM		0x00100000
#घोषणा	FEC_IMASK_XFIFO_UN		0x00080000
#घोषणा	FEC_IMASK_XFIFO_ERROR		0x00040000
#घोषणा	FEC_IMASK_RFIFO_ERROR		0x00020000

/* all but MII, which is enabled separately */
#घोषणा FEC_IMASK_ENABLE	(FEC_IMASK_HBERR | FEC_IMASK_BABR | \
		FEC_IMASK_BABT | FEC_IMASK_GRA | FEC_IMASK_LATE_COL | \
		FEC_IMASK_COL_RETRY_LIM | FEC_IMASK_XFIFO_UN | \
		FEC_IMASK_XFIFO_ERROR | FEC_IMASK_RFIFO_ERROR)

#घोषणा	FEC_RCNTRL_MAX_FL_SHIFT		16
#घोषणा	FEC_RCNTRL_LOOP			0x01
#घोषणा	FEC_RCNTRL_DRT			0x02
#घोषणा	FEC_RCNTRL_MII_MODE		0x04
#घोषणा	FEC_RCNTRL_PROM			0x08
#घोषणा	FEC_RCNTRL_BC_REJ		0x10
#घोषणा	FEC_RCNTRL_FCE			0x20

#घोषणा	FEC_TCNTRL_GTS			0x00000001
#घोषणा	FEC_TCNTRL_HBC			0x00000002
#घोषणा	FEC_TCNTRL_FDEN			0x00000004
#घोषणा	FEC_TCNTRL_TFC_PAUSE		0x00000008
#घोषणा	FEC_TCNTRL_RFC_PAUSE		0x00000010

#घोषणा	FEC_ECNTRL_RESET		0x00000001
#घोषणा	FEC_ECNTRL_ETHER_EN		0x00000002

#घोषणा FEC_MII_DATA_ST			0x40000000	/* Start frame */
#घोषणा FEC_MII_DATA_OP_RD		0x20000000	/* Perक्रमm पढ़ो */
#घोषणा FEC_MII_DATA_OP_WR		0x10000000	/* Perक्रमm ग_लिखो */
#घोषणा FEC_MII_DATA_PA_MSK		0x0f800000	/* PHY Address mask */
#घोषणा FEC_MII_DATA_RA_MSK		0x007c0000	/* PHY Register mask */
#घोषणा FEC_MII_DATA_TA			0x00020000	/* Turnaround */
#घोषणा FEC_MII_DATA_DATAMSK		0x0000ffff	/* PHY data mask */

#घोषणा FEC_MII_READ_FRAME	(FEC_MII_DATA_ST | FEC_MII_DATA_OP_RD | FEC_MII_DATA_TA)
#घोषणा FEC_MII_WRITE_FRAME	(FEC_MII_DATA_ST | FEC_MII_DATA_OP_WR | FEC_MII_DATA_TA)

#घोषणा FEC_MII_DATA_RA_SHIFT		0x12		/* MII reg addr bits */
#घोषणा FEC_MII_DATA_PA_SHIFT		0x17		/* MII PHY addr bits */

#घोषणा FEC_PADDR2_TYPE			0x8808

#घोषणा FEC_OP_PAUSE_OPCODE		0x00010000

#घोषणा FEC_FIFO_WMRK_256B		0x3

#घोषणा FEC_FIFO_STATUS_ERR		0x00400000
#घोषणा FEC_FIFO_STATUS_UF		0x00200000
#घोषणा FEC_FIFO_STATUS_OF		0x00100000

#घोषणा FEC_FIFO_CNTRL_FRAME		0x08000000
#घोषणा FEC_FIFO_CNTRL_LTG_7		0x07000000

#घोषणा FEC_RESET_CNTRL_RESET_FIFO	0x02000000
#घोषणा FEC_RESET_CNTRL_ENABLE_IS_RESET	0x01000000

#घोषणा FEC_XMIT_FSM_APPEND_CRC		0x02000000
#घोषणा FEC_XMIT_FSM_ENABLE_CRC		0x01000000


बाह्य काष्ठा platक्रमm_driver mpc52xx_fec_mdio_driver;

#पूर्ण_अगर	/* __DRIVERS_NET_MPC52XX_FEC_H__ */
