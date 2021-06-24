<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Tehuti Networks(R) Network Driver
 * Copyright (C) 2007 Tehuti Networks Ltd. All rights reserved
 */

#अगर_अघोषित _TEHUTI_H
#घोषणा _TEHUTI_H

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/crc32.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/sched.h>
#समावेश <linux/tty.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/firmware.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

/* Compile Time Switches */
/* start */
#घोषणा BDX_TSO
#घोषणा BDX_LLTX
#घोषणा BDX_DELAY_WPTR
/* #घोषणा BDX_MSI */
/* end */

#अगर !defined CONFIG_PCI_MSI
#   undef BDX_MSI
#पूर्ण_अगर

#घोषणा BDX_DEF_MSG_ENABLE	(NETIF_MSG_DRV          | \
				NETIF_MSG_PROBE        | \
				NETIF_MSG_LINK)

/* ioctl ops */
#घोषणा BDX_OP_READ  1
#घोषणा BDX_OP_WRITE 2

/* RX copy अवरोध size */
#घोषणा BDX_COPYBREAK    257

#घोषणा DRIVER_AUTHOR     "Tehuti Networks(R)"
#घोषणा BDX_DRV_DESC      "Tehuti Networks(R) Network Driver"
#घोषणा BDX_DRV_NAME      "tehuti"
#घोषणा BDX_NIC_NAME      "Tehuti 10 Giga TOE SmartNIC"
#घोषणा BDX_NIC2PORT_NAME "Tehuti 2-Port 10 Giga TOE SmartNIC"
#घोषणा BDX_DRV_VERSION   "7.29.3"

#अगर_घोषित BDX_MSI
#    define BDX_MSI_STRING "msi "
#अन्यथा
#    define BDX_MSI_STRING ""
#पूर्ण_अगर

/* netdev tx queue len क्रम Luxor. शेष value is, btw, 1000
 * अगरcontig eth1 txqueuelen 3000 - to change it at runसमय */
#घोषणा BDX_NDEV_TXQ_LEN 3000

/* Max MTU क्रम Jumbo Frame mode, per tehutinetworks.net Features FAQ is 16k */
#घोषणा BDX_MAX_MTU	(16 * 1024)

#घोषणा FIFO_SIZE  4096
#घोषणा FIFO_EXTRA_SPACE            1024

#अगर BITS_PER_LONG == 64
#    define H32_64(x)  (u32) ((u64)(x) >> 32)
#    define L32_64(x)  (u32) ((u64)(x) & 0xffffffff)
#या_अगर BITS_PER_LONG == 32
#    define H32_64(x)  0
#    define L32_64(x)  ((u32) (x))
#अन्यथा				/* BITS_PER_LONG == ?? */
#    error BITS_PER_LONG is undefined. Must be 64 or 32
#पूर्ण_अगर				/* BITS_PER_LONG */

#अगर_घोषित __BIG_ENDIAN
#   define CPU_CHIP_SWAP32(x) swab32(x)
#   define CPU_CHIP_SWAP16(x) swab16(x)
#अन्यथा
#   define CPU_CHIP_SWAP32(x) (x)
#   define CPU_CHIP_SWAP16(x) (x)
#पूर्ण_अगर

#घोषणा READ_REG(pp, reg)         पढ़ोl(pp->pBdxRegs + reg)
#घोषणा WRITE_REG(pp, reg, val)   ग_लिखोl(val, pp->pBdxRegs + reg)

#अगर_अघोषित NET_IP_ALIGN
#   define NET_IP_ALIGN 2
#पूर्ण_अगर

#अगर_अघोषित NETDEV_TX_OK
#   define NETDEV_TX_OK 0
#पूर्ण_अगर

#घोषणा LUXOR_MAX_PORT     2
#घोषणा BDX_MAX_RX_DONE    150
#घोषणा BDX_TXF_DESC_SZ    16
#घोषणा BDX_MAX_TX_LEVEL   (priv->txd_fअगरo0.m.memsz - 16)
#घोषणा BDX_MIN_TX_LEVEL   256
#घोषणा BDX_NO_UPD_PACKETS 40

काष्ठा pci_nic अणु
	पूर्णांक port_num;
	व्योम __iomem *regs;
	पूर्णांक irq_type;
	काष्ठा bdx_priv *priv[LUXOR_MAX_PORT];
पूर्ण;

क्रमागत अणु IRQ_INTX, IRQ_MSI, IRQ_MSIX पूर्ण;

#घोषणा PCK_TH_MULT   128
#घोषणा INT_COAL_MULT 2

#घोषणा BITS_MASK(nbits)			((1<<nbits)-1)
#घोषणा GET_BITS_SHIFT(x, nbits, nshअगरt)	(((x)>>nshअगरt)&BITS_MASK(nbits))
#घोषणा BITS_SHIFT_MASK(nbits, nshअगरt)		(BITS_MASK(nbits)<<nshअगरt)
#घोषणा BITS_SHIFT_VAL(x, nbits, nshअगरt)	(((x)&BITS_MASK(nbits))<<nshअगरt)
#घोषणा BITS_SHIFT_CLEAR(x, nbits, nshअगरt)	\
	((x)&(~BITS_SHIFT_MASK(nbits, nshअगरt)))

#घोषणा GET_INT_COAL(x)				GET_BITS_SHIFT(x, 15, 0)
#घोषणा GET_INT_COAL_RC(x)			GET_BITS_SHIFT(x, 1, 15)
#घोषणा GET_RXF_TH(x)				GET_BITS_SHIFT(x, 4, 16)
#घोषणा GET_PCK_TH(x)				GET_BITS_SHIFT(x, 4, 20)

#घोषणा INT_REG_VAL(coal, coal_rc, rxf_th, pck_th)	\
	((coal)|((coal_rc)<<15)|((rxf_th)<<16)|((pck_th)<<20))

काष्ठा fअगरo अणु
	dma_addr_t da;		/* physical address of fअगरo (used by HW) */
	अक्षर *va;		/* भव address of fअगरo (used by SW) */
	u32 rptr, wptr;		/* cached values of RPTR and WPTR रेजिस्टरs,
				   they're 32 bits on both 32 and 64 archs */
	u16 reg_CFG0, reg_CFG1;
	u16 reg_RPTR, reg_WPTR;
	u16 memsz;		/* memory size allocated क्रम fअगरo */
	u16 size_mask;
	u16 pktsz;		/* skb packet size to allocate */
	u16 rcvno;		/* number of buffers that come from this RXF */
पूर्ण;

काष्ठा txf_fअगरo अणु
	काष्ठा fअगरo m;		/* minimal set of variables used by all fअगरos */
पूर्ण;

काष्ठा txd_fअगरo अणु
	काष्ठा fअगरo m;		/* minimal set of variables used by all fअगरos */
पूर्ण;

काष्ठा rxf_fअगरo अणु
	काष्ठा fअगरo m;		/* minimal set of variables used by all fअगरos */
पूर्ण;

काष्ठा rxd_fअगरo अणु
	काष्ठा fअगरo m;		/* minimal set of variables used by all fअगरos */
पूर्ण;

काष्ठा rx_map अणु
	u64 dma;
	काष्ठा sk_buff *skb;
पूर्ण;

काष्ठा rxdb अणु
	पूर्णांक *stack;
	काष्ठा rx_map *elems;
	पूर्णांक nelem;
	पूर्णांक top;
पूर्ण;

जोड़ bdx_dma_addr अणु
	dma_addr_t dma;
	काष्ठा sk_buff *skb;
पूर्ण;

/* Entry in the db.
 * अगर len == 0 addr is dma
 * अगर len != 0 addr is skb */
काष्ठा tx_map अणु
	जोड़ bdx_dma_addr addr;
	पूर्णांक len;
पूर्ण;

/* tx database - implemented as circular fअगरo buffer*/
काष्ठा txdb अणु
	काष्ठा tx_map *start;	/* poपूर्णांकs to the first element */
	काष्ठा tx_map *end;	/* poपूर्णांकs just AFTER the last element */
	काष्ठा tx_map *rptr;	/* poपूर्णांकs to the next element to पढ़ो */
	काष्ठा tx_map *wptr;	/* poपूर्णांकs to the next element to ग_लिखो */
	पूर्णांक size;		/* number of elements in the db */
पूर्ण;

/*Internal stats काष्ठाure*/
काष्ठा bdx_stats अणु
	u64 InUCast;			/* 0x7200 */
	u64 InMCast;			/* 0x7210 */
	u64 InBCast;			/* 0x7220 */
	u64 InPkts;			/* 0x7230 */
	u64 InErrors;			/* 0x7240 */
	u64 InDropped;			/* 0x7250 */
	u64 FrameTooLong;		/* 0x7260 */
	u64 FrameSequenceErrors;	/* 0x7270 */
	u64 InVLAN;			/* 0x7280 */
	u64 InDroppedDFE;		/* 0x7290 */
	u64 InDroppedIntFull;		/* 0x72A0 */
	u64 InFrameAlignErrors;		/* 0x72B0 */

	/* 0x72C0-0x72E0 RSRV */

	u64 OutUCast;			/* 0x72F0 */
	u64 OutMCast;			/* 0x7300 */
	u64 OutBCast;			/* 0x7310 */
	u64 OutPkts;			/* 0x7320 */

	/* 0x7330-0x7360 RSRV */

	u64 OutVLAN;			/* 0x7370 */
	u64 InUCastOctects;		/* 0x7380 */
	u64 OutUCastOctects;		/* 0x7390 */

	/* 0x73A0-0x73B0 RSRV */

	u64 InBCastOctects;		/* 0x73C0 */
	u64 OutBCastOctects;		/* 0x73D0 */
	u64 InOctects;			/* 0x73E0 */
	u64 OutOctects;			/* 0x73F0 */
पूर्ण;

काष्ठा bdx_priv अणु
	व्योम __iomem *pBdxRegs;
	काष्ठा net_device *ndev;

	काष्ठा napi_काष्ठा napi;

	/* RX FIFOs: 1 क्रम data (full) descs, and 2 क्रम मुक्त descs */
	काष्ठा rxd_fअगरo rxd_fअगरo0;
	काष्ठा rxf_fअगरo rxf_fअगरo0;
	काष्ठा rxdb *rxdb;	/* rx dbs to store skb poपूर्णांकers */
	पूर्णांक napi_stop;

	/* Tx FIFOs: 1 क्रम data desc, 1 क्रम empty (acks) desc */
	काष्ठा txd_fअगरo txd_fअगरo0;
	काष्ठा txf_fअगरo txf_fअगरo0;

	काष्ठा txdb txdb;
	पूर्णांक tx_level;
#अगर_घोषित BDX_DELAY_WPTR
	पूर्णांक tx_update_mark;
	पूर्णांक tx_noupd;
#पूर्ण_अगर
	spinlock_t tx_lock;	/* NETIF_F_LLTX mode */

	/* rarely used */
	u8 port;
	u32 msg_enable;
	पूर्णांक stats_flag;
	काष्ठा bdx_stats hw_stats;
	काष्ठा pci_dev *pdev;

	काष्ठा pci_nic *nic;

	u8 txd_size;
	u8 txf_size;
	u8 rxd_size;
	u8 rxf_size;
	u32 rdपूर्णांकcm;
	u32 tdपूर्णांकcm;
पूर्ण;

/* RX FREE descriptor - 64bit*/
काष्ठा rxf_desc अणु
	u32 info;		/* Buffer Count + Info - described below */
	u32 va_lo;		/* VAdr[31:0] */
	u32 va_hi;		/* VAdr[63:32] */
	u32 pa_lo;		/* PAdr[31:0] */
	u32 pa_hi;		/* PAdr[63:32] */
	u32 len;		/* Buffer Length */
पूर्ण;

#घोषणा GET_RXD_BC(x)			GET_BITS_SHIFT((x), 5, 0)
#घोषणा GET_RXD_RXFQ(x)			GET_BITS_SHIFT((x), 2, 8)
#घोषणा GET_RXD_TO(x)			GET_BITS_SHIFT((x), 1, 15)
#घोषणा GET_RXD_TYPE(x)			GET_BITS_SHIFT((x), 4, 16)
#घोषणा GET_RXD_ERR(x)			GET_BITS_SHIFT((x), 6, 21)
#घोषणा GET_RXD_RXP(x)			GET_BITS_SHIFT((x), 1, 27)
#घोषणा GET_RXD_PKT_ID(x)		GET_BITS_SHIFT((x), 3, 28)
#घोषणा GET_RXD_VTAG(x)			GET_BITS_SHIFT((x), 1, 31)
#घोषणा GET_RXD_VLAN_ID(x)		GET_BITS_SHIFT((x), 12, 0)
#घोषणा GET_RXD_VLAN_TCI(x)		GET_BITS_SHIFT((x), 16, 0)
#घोषणा GET_RXD_CFI(x)			GET_BITS_SHIFT((x), 1, 12)
#घोषणा GET_RXD_PRIO(x)			GET_BITS_SHIFT((x), 3, 13)

काष्ठा rxd_desc अणु
	u32 rxd_val1;
	u16 len;
	u16 rxd_vlan;
	u32 va_lo;
	u32 va_hi;
पूर्ण;

/* PBL describes each भव buffer to be */
/* transmitted from the host.*/
काष्ठा pbl अणु
	u32 pa_lo;
	u32 pa_hi;
	u32 len;
पूर्ण;

/* First word क्रम TXD descriptor. It means: type = 3 क्रम regular Tx packet,
 * hw_csum = 7 क्रम ip+udp+tcp hw checksums */
#घोषणा TXD_W1_VAL(bc, checksum, vtag, lgsnd, vlan_id)	\
	((bc) | ((checksum)<<5) | ((vtag)<<8) | \
	((lgsnd)<<9) | (0x30000) | ((vlan_id)<<20))

काष्ठा txd_desc अणु
	u32 txd_val1;
	u16 mss;
	u16 length;
	u32 va_lo;
	u32 va_hi;
	काष्ठा pbl pbl[];	/* Fragments */
पूर्ण __packed;

/* Register region size */
#घोषणा BDX_REGS_SIZE	  0x1000

/* Registers from 0x0000-0x00fc were remapped to 0x4000-0x40fc */
#घोषणा regTXD_CFG1_0   0x4000
#घोषणा regRXF_CFG1_0   0x4010
#घोषणा regRXD_CFG1_0   0x4020
#घोषणा regTXF_CFG1_0   0x4030
#घोषणा regTXD_CFG0_0   0x4040
#घोषणा regRXF_CFG0_0   0x4050
#घोषणा regRXD_CFG0_0   0x4060
#घोषणा regTXF_CFG0_0   0x4070
#घोषणा regTXD_WPTR_0   0x4080
#घोषणा regRXF_WPTR_0   0x4090
#घोषणा regRXD_WPTR_0   0x40A0
#घोषणा regTXF_WPTR_0   0x40B0
#घोषणा regTXD_RPTR_0   0x40C0
#घोषणा regRXF_RPTR_0   0x40D0
#घोषणा regRXD_RPTR_0   0x40E0
#घोषणा regTXF_RPTR_0   0x40F0
#घोषणा regTXF_RPTR_3   0x40FC

/* hardware versioning */
#घोषणा  FW_VER         0x5010
#घोषणा  SROM_VER       0x5020
#घोषणा  FPGA_VER       0x5030
#घोषणा  FPGA_SEED      0x5040

/* Registers from 0x0100-0x0150 were remapped to 0x5100-0x5150 */
#घोषणा regISR regISR0
#घोषणा regISR0          0x5100

#घोषणा regIMR regIMR0
#घोषणा regIMR0          0x5110

#घोषणा regRDINTCM0      0x5120
#घोषणा regRDINTCM2      0x5128

#घोषणा regTDINTCM0      0x5130

#घोषणा regISR_MSK0      0x5140

#घोषणा regINIT_SEMAPHORE 0x5170
#घोषणा regINIT_STATUS    0x5180

#घोषणा regMAC_LNK_STAT  0x0200
#घोषणा MAC_LINK_STAT    0x4	/* Link state */

#घोषणा regGMAC_RXF_A   0x1240

#घोषणा regUNC_MAC0_A   0x1250
#घोषणा regUNC_MAC1_A   0x1260
#घोषणा regUNC_MAC2_A   0x1270

#घोषणा regVLAN_0       0x1800

#घोषणा regMAX_FRAME_A  0x12C0

#घोषणा regRX_MAC_MCST0    0x1A80
#घोषणा regRX_MAC_MCST1    0x1A84
#घोषणा MAC_MCST_NUM       15
#घोषणा regRX_MCST_HASH0   0x1A00
#घोषणा MAC_MCST_HASH_NUM  8

#घोषणा regVPC                  0x2300
#घोषणा regVIC                  0x2320
#घोषणा regVGLB                 0x2340

#घोषणा regCLKPLL               0x5000

/*क्रम 10G only*/
#घोषणा regREVISION        0x6000
#घोषणा regSCRATCH         0x6004
#घोषणा regCTRLST          0x6008
#घोषणा regMAC_ADDR_0      0x600C
#घोषणा regMAC_ADDR_1      0x6010
#घोषणा regFRM_LENGTH      0x6014
#घोषणा regPAUSE_QUANT     0x6018
#घोषणा regRX_FIFO_SECTION 0x601C
#घोषणा regTX_FIFO_SECTION 0x6020
#घोषणा regRX_FULLNESS     0x6024
#घोषणा regTX_FULLNESS     0x6028
#घोषणा regHASHTABLE       0x602C
#घोषणा regMDIO_ST         0x6030
#घोषणा regMDIO_CTL        0x6034
#घोषणा regMDIO_DATA       0x6038
#घोषणा regMDIO_ADDR       0x603C

#घोषणा regRST_PORT        0x7000
#घोषणा regDIS_PORT        0x7010
#घोषणा regRST_QU          0x7020
#घोषणा regDIS_QU          0x7030

#घोषणा regCTRLST_TX_ENA   0x0001
#घोषणा regCTRLST_RX_ENA   0x0002
#घोषणा regCTRLST_PRM_ENA  0x0010
#घोषणा regCTRLST_PAD_ENA  0x0020

#घोषणा regCTRLST_BASE     (regCTRLST_PAD_ENA|regCTRLST_PRM_ENA)

#घोषणा regRX_FLT   0x1400

/* TXD TXF RXF RXD  CONFIG 0x0000 --- 0x007c*/
#घोषणा  TX_RX_CFG1_BASE          0xffffffff	/*0-31 */
#घोषणा  TX_RX_CFG0_BASE          0xfffff000	/*31:12 */
#घोषणा  TX_RX_CFG0_RSVD          0x0ffc	/*11:2 */
#घोषणा  TX_RX_CFG0_SIZE          0x0003	/*1:0 */

/*  TXD TXF RXF RXD  WRITE 0x0080 --- 0x00BC */
#घोषणा  TXF_WPTR_WR_PTR        0x7ff8	/*14:3 */

/*  TXD TXF RXF RXD  READ  0x00CO --- 0x00FC */
#घोषणा  TXF_RPTR_RD_PTR        0x7ff8	/*14:3 */

#घोषणा TXF_WPTR_MASK 0x7ff0	/* last 4 bits are dropped
				 * size is rounded to 16 */

/*  regISR 0x0100 */
/*  regIMR 0x0110 */
#घोषणा  IMR_INPROG   0x80000000	/*31 */
#घोषणा  IR_LNKCHG1   0x10000000	/*28 */
#घोषणा  IR_LNKCHG0   0x08000000	/*27 */
#घोषणा  IR_GPIO      0x04000000	/*26 */
#घोषणा  IR_RFRSH     0x02000000	/*25 */
#घोषणा  IR_RSVD      0x01000000	/*24 */
#घोषणा  IR_SWI       0x00800000	/*23 */
#घोषणा  IR_RX_FREE_3 0x00400000	/*22 */
#घोषणा  IR_RX_FREE_2 0x00200000	/*21 */
#घोषणा  IR_RX_FREE_1 0x00100000	/*20 */
#घोषणा  IR_RX_FREE_0 0x00080000	/*19 */
#घोषणा  IR_TX_FREE_3 0x00040000	/*18 */
#घोषणा  IR_TX_FREE_2 0x00020000	/*17 */
#घोषणा  IR_TX_FREE_1 0x00010000	/*16 */
#घोषणा  IR_TX_FREE_0 0x00008000	/*15 */
#घोषणा  IR_RX_DESC_3 0x00004000	/*14 */
#घोषणा  IR_RX_DESC_2 0x00002000	/*13 */
#घोषणा  IR_RX_DESC_1 0x00001000	/*12 */
#घोषणा  IR_RX_DESC_0 0x00000800	/*11 */
#घोषणा  IR_PSE       0x00000400	/*10 */
#घोषणा  IR_TMR3      0x00000200	/*9 */
#घोषणा  IR_TMR2      0x00000100	/*8 */
#घोषणा  IR_TMR1      0x00000080	/*7 */
#घोषणा  IR_TMR0      0x00000040	/*6 */
#घोषणा  IR_VNT       0x00000020	/*5 */
#घोषणा  IR_RxFL      0x00000010	/*4 */
#घोषणा  IR_SDPERR    0x00000008	/*3 */
#घोषणा  IR_TR        0x00000004	/*2 */
#घोषणा  IR_PCIE_LINK 0x00000002	/*1 */
#घोषणा  IR_PCIE_TOUT 0x00000001	/*0 */

#घोषणा  IR_EXTRA (IR_RX_FREE_0 | IR_LNKCHG0 | IR_PSE | \
    IR_TMR0 | IR_PCIE_LINK | IR_PCIE_TOUT)
#घोषणा  IR_RUN (IR_EXTRA | IR_RX_DESC_0 | IR_TX_FREE_0)
#घोषणा  IR_ALL 0xfdfffff7

#घोषणा  IR_LNKCHG0_ofst        27

#घोषणा  GMAC_RX_FILTER_OSEN  0x1000	/* shared OS enable */
#घोषणा  GMAC_RX_FILTER_TXFC  0x0400	/* Tx flow control */
#घोषणा  GMAC_RX_FILTER_RSV0  0x0200	/* reserved */
#घोषणा  GMAC_RX_FILTER_FDA   0x0100	/* filter out direct address */
#घोषणा  GMAC_RX_FILTER_AOF   0x0080	/* accept over run */
#घोषणा  GMAC_RX_FILTER_ACF   0x0040	/* accept control frames */
#घोषणा  GMAC_RX_FILTER_ARUNT 0x0020	/* accept under run */
#घोषणा  GMAC_RX_FILTER_ACRC  0x0010	/* accept crc error */
#घोषणा  GMAC_RX_FILTER_AM    0x0008	/* accept multicast */
#घोषणा  GMAC_RX_FILTER_AB    0x0004	/* accept broadcast */
#घोषणा  GMAC_RX_FILTER_PRM   0x0001	/* [0:1] promiscuous mode */

#घोषणा  MAX_FRAME_AB_VAL       0x3fff	/* 13:0 */

#घोषणा  CLKPLL_PLLLKD          0x0200	/*9 */
#घोषणा  CLKPLL_RSTEND          0x0100	/*8 */
#घोषणा  CLKPLL_SFTRST          0x0001	/*0 */

#घोषणा  CLKPLL_LKD             (CLKPLL_PLLLKD|CLKPLL_RSTEND)

/*
 * PCI-E Device Control Register (Offset 0x88)
 * Source: Luxor Data Sheet, 7.1.3.3.3
 */
#घोषणा PCI_DEV_CTRL_REG 0x88
#घोषणा GET_DEV_CTRL_MAXPL(x)           GET_BITS_SHIFT(x, 3, 5)
#घोषणा GET_DEV_CTRL_MRRS(x)            GET_BITS_SHIFT(x, 3, 12)

/*
 * PCI-E Link Status Register (Offset 0x92)
 * Source: Luxor Data Sheet, 7.1.3.3.7
 */
#घोषणा PCI_LINK_STATUS_REG 0x92
#घोषणा GET_LINK_STATUS_LANES(x)		GET_BITS_SHIFT(x, 6, 4)

/* Debugging Macros */

#घोषणा DBG2(fmt, args...)					\
	pr_err("%s:%-5d: " fmt, __func__, __LINE__, ## args)

#घोषणा BDX_ASSERT(x) BUG_ON(x)

#अगर_घोषित DEBUG

#घोषणा ENTER						\
करो अणु							\
	pr_err("%s:%-5d: ENTER\n", __func__, __LINE__); \
पूर्ण जबतक (0)

#घोषणा RET(args...)					 \
करो अणु							 \
	pr_err("%s:%-5d: RETURN\n", __func__, __LINE__); \
	वापस args;					 \
पूर्ण जबतक (0)

#घोषणा DBG(fmt, args...)					\
	pr_err("%s:%-5d: " fmt, __func__, __LINE__, ## args)
#अन्यथा
#घोषणा ENTER करो अणु  पूर्ण जबतक (0)
#घोषणा RET(args...)   वापस args
#घोषणा DBG(fmt, args...)			\
करो अणु						\
	अगर (0)					\
		pr_err(fmt, ##args);		\
पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* _BDX__H */
