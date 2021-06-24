<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* drivers/aपंचांग/firestream.h - FireStream 155 (MB86697) and
 *                            FireStream  50 (MB86695) device driver 
 */
 
/* Written & (C) 2000 by R.E.Wolff@BitWizard.nl 
 * Copied snippets from zaपंचांग.c by Werner Almesberger, EPFL LRC/ICA 
 * and ambassaकरोr.c Copyright (C) 1995-1999  Madge Networks Ltd 
 */

/*
*/


/***********************************************************************
 *                  first the defines क्रम the chip.                    *
 ***********************************************************************/


/********************* General chip parameters. ************************/

#घोषणा FS_NR_FREE_POOLS   8
#घोषणा FS_NR_RX_QUEUES    4


/********************* queues and queue access macros ******************/


/* A queue entry. */
काष्ठा FS_QENTRY अणु
	u32 cmd;
	u32 p0, p1, p2;
पूर्ण;


/* A मुक्तpool entry. */
काष्ठा FS_BPENTRY अणु
	u32 flags;
	u32 next;
	u32 bsa;
	u32 aal_bufsize;

	/* The hardware करोesn't look at this, but we need the SKB somewhere... */
	काष्ठा sk_buff *skb;
	काष्ठा मुक्तpool *fp;
	काष्ठा fs_dev *dev;
पूर्ण;


#घोषणा STATUS_CODE(qe)  ((qe->cmd >> 22) & 0x3f)


/* OFFSETS against the base of a QUEUE... */
#घोषणा QSA     0x00
#घोषणा QEA     0x04
#घोषणा QRP     0x08
#घोषणा QWP     0x0c
#घोषणा QCNF    0x10   /* Only क्रम Release queues! */
/* Not क्रम the transmit pending queue. */


/* OFFSETS against the base of a FREE POOL... */
#घोषणा FPCNF   0x00
#घोषणा FPSA    0x04
#घोषणा FPEA    0x08
#घोषणा FPCNT   0x0c
#घोषणा FPCTU   0x10

#घोषणा Q_SA(b)     (b + QSA )
#घोषणा Q_EA(b)     (b + QEA )
#घोषणा Q_RP(b)     (b + QRP )
#घोषणा Q_WP(b)     (b + QWP )
#घोषणा Q_CNF(b)    (b + QCNF)

#घोषणा FP_CNF(b)   (b + FPCNF)
#घोषणा FP_SA(b)    (b + FPSA)
#घोषणा FP_EA(b)    (b + FPEA)
#घोषणा FP_CNT(b)   (b + FPCNT)
#घोषणा FP_CTU(b)   (b + FPCTU)

/* bits in a queue रेजिस्टर. */
#घोषणा Q_FULL      0x1
#घोषणा Q_EMPTY     0x2
#घोषणा Q_INCWRAP   0x4
#घोषणा Q_ADDR_MASK 0xfffffff0

/* bits in a FreePool config रेजिस्टर */
#घोषणा RBFP_RBS    (0x1 << 16)
#घोषणा RBFP_RBSVAL (0x1 << 15)
#घोषणा RBFP_CME    (0x1 << 12)
#घोषणा RBFP_DLP    (0x1 << 11)
#घोषणा RBFP_BFPWT  (0x1 <<  0)




/* FireStream commands. */
#घोषणा QE_CMD_शून्य             (0x00 << 22)
#घोषणा QE_CMD_REG_RD           (0x01 << 22)
#घोषणा QE_CMD_REG_RDM          (0x02 << 22)
#घोषणा QE_CMD_REG_WR           (0x03 << 22)
#घोषणा QE_CMD_REG_WRM          (0x04 << 22)
#घोषणा QE_CMD_CONFIG_TX        (0x05 << 22)
#घोषणा QE_CMD_CONFIG_RX        (0x06 << 22)
#घोषणा QE_CMD_PRP_RD           (0x07 << 22)
#घोषणा QE_CMD_PRP_RDM          (0x2a << 22)
#घोषणा QE_CMD_PRP_WR           (0x09 << 22)
#घोषणा QE_CMD_PRP_WRM          (0x2b << 22)
#घोषणा QE_CMD_RX_EN            (0x0a << 22)
#घोषणा QE_CMD_RX_PURGE         (0x0b << 22)
#घोषणा QE_CMD_RX_PURGE_INH     (0x0c << 22)
#घोषणा QE_CMD_TX_EN            (0x0d << 22)
#घोषणा QE_CMD_TX_PURGE         (0x0e << 22)
#घोषणा QE_CMD_TX_PURGE_INH     (0x0f << 22)
#घोषणा QE_CMD_RST_CG           (0x10 << 22)
#घोषणा QE_CMD_SET_CG           (0x11 << 22)
#घोषणा QE_CMD_RST_CLP          (0x12 << 22)
#घोषणा QE_CMD_SET_CLP          (0x13 << 22)
#घोषणा QE_CMD_OVERRIDE         (0x14 << 22)
#घोषणा QE_CMD_ADD_BFP          (0x15 << 22)
#घोषणा QE_CMD_DUMP_TX          (0x16 << 22)
#घोषणा QE_CMD_DUMP_RX          (0x17 << 22)
#घोषणा QE_CMD_LRAM_RD          (0x18 << 22)
#घोषणा QE_CMD_LRAM_RDM         (0x28 << 22)
#घोषणा QE_CMD_LRAM_WR          (0x19 << 22)
#घोषणा QE_CMD_LRAM_WRM         (0x29 << 22)
#घोषणा QE_CMD_LRAM_BSET        (0x1a << 22)
#घोषणा QE_CMD_LRAM_BCLR        (0x1b << 22)
#घोषणा QE_CMD_CONFIG_SEGM      (0x1c << 22)
#घोषणा QE_CMD_READ_SEGM        (0x1d << 22)
#घोषणा QE_CMD_CONFIG_ROUT      (0x1e << 22)
#घोषणा QE_CMD_READ_ROUT        (0x1f << 22)
#घोषणा QE_CMD_CONFIG_TM        (0x20 << 22)
#घोषणा QE_CMD_READ_TM          (0x21 << 22)
#घोषणा QE_CMD_CONFIG_TXBM      (0x22 << 22)
#घोषणा QE_CMD_READ_TXBM        (0x23 << 22)
#घोषणा QE_CMD_CONFIG_RXBM      (0x24 << 22)
#घोषणा QE_CMD_READ_RXBM        (0x25 << 22)
#घोषणा QE_CMD_CONFIG_REAS      (0x26 << 22)
#घोषणा QE_CMD_READ_REAS        (0x27 << 22)

#घोषणा QE_TRANSMIT_DE          (0x0 << 30)
#घोषणा QE_CMD_LINKED           (0x1 << 30)
#घोषणा QE_CMD_IMM              (0x2 << 30)
#घोषणा QE_CMD_IMM_INQ          (0x3 << 30)

#घोषणा TD_EPI                  (0x1 << 27)
#घोषणा TD_COMMAND              (0x1 << 28)

#घोषणा TD_DATA                 (0x0 << 29)
#घोषणा TD_RM_CELL              (0x1 << 29)
#घोषणा TD_OAM_CELL             (0x2 << 29)
#घोषणा TD_OAM_CELL_SEGMENT     (0x3 << 29)

#घोषणा TD_BPI                  (0x1 << 20)

#घोषणा FP_FLAGS_EPI            (0x1 << 27)


#घोषणा TX_PQ(i)  (0x00  + (i) * 0x10)
#घोषणा TXB_RQ    (0x20)
#घोषणा ST_Q      (0x48)
#घोषणा RXB_FP(i) (0x90  + (i) * 0x14)
#घोषणा RXB_RQ(i) (0x134 + (i) * 0x14)


#घोषणा TXQ_HP 0
#घोषणा TXQ_LP 1

/* Phew. You करोn't want to know how many revisions these simple queue
 * address macros went through beक्रमe I got them nice and compact as
 * they are now. -- REW
 */


/* And now क्रम something completely dअगरferent: 
 * The rest of the रेजिस्टरs... */


#घोषणा CMDR0 0x34
#घोषणा CMDR1 0x38
#घोषणा CMDR2 0x3c
#घोषणा CMDR3 0x40


#घोषणा SARMODE0     0x5c

#घोषणा SARMODE0_TXVCS_0    (0x0 << 0)
#घोषणा SARMODE0_TXVCS_1k   (0x1 << 0)
#घोषणा SARMODE0_TXVCS_2k   (0x2 << 0)
#घोषणा SARMODE0_TXVCS_4k   (0x3 << 0)
#घोषणा SARMODE0_TXVCS_8k   (0x4 << 0)
#घोषणा SARMODE0_TXVCS_16k  (0x5 << 0)
#घोषणा SARMODE0_TXVCS_32k  (0x6 << 0)
#घोषणा SARMODE0_TXVCS_64k  (0x7 << 0)
#घोषणा SARMODE0_TXVCS_32   (0x8 << 0)

#घोषणा SARMODE0_ABRVCS_0   (0x0 << 4)
#घोषणा SARMODE0_ABRVCS_512 (0x1 << 4)
#घोषणा SARMODE0_ABRVCS_1k  (0x2 << 4)
#घोषणा SARMODE0_ABRVCS_2k  (0x3 << 4)
#घोषणा SARMODE0_ABRVCS_4k  (0x4 << 4)
#घोषणा SARMODE0_ABRVCS_8k  (0x5 << 4)
#घोषणा SARMODE0_ABRVCS_16k (0x6 << 4)
#घोषणा SARMODE0_ABRVCS_32k (0x7 << 4)
#घोषणा SARMODE0_ABRVCS_32  (0x9 << 4) /* The others are "8", this one really has to 
					  be 9. Tell me you करोn't believe me. -- REW */

#घोषणा SARMODE0_RXVCS_0    (0x0 << 8)
#घोषणा SARMODE0_RXVCS_1k   (0x1 << 8)
#घोषणा SARMODE0_RXVCS_2k   (0x2 << 8)
#घोषणा SARMODE0_RXVCS_4k   (0x3 << 8)
#घोषणा SARMODE0_RXVCS_8k   (0x4 << 8)
#घोषणा SARMODE0_RXVCS_16k  (0x5 << 8)
#घोषणा SARMODE0_RXVCS_32k  (0x6 << 8)
#घोषणा SARMODE0_RXVCS_64k  (0x7 << 8)
#घोषणा SARMODE0_RXVCS_32   (0x8 << 8) 

#घोषणा SARMODE0_CALSUP_1  (0x0 << 12)
#घोषणा SARMODE0_CALSUP_2  (0x1 << 12)
#घोषणा SARMODE0_CALSUP_3  (0x2 << 12)
#घोषणा SARMODE0_CALSUP_4  (0x3 << 12)

#घोषणा SARMODE0_PRPWT_FS50_0  (0x0 << 14)
#घोषणा SARMODE0_PRPWT_FS50_2  (0x1 << 14)
#घोषणा SARMODE0_PRPWT_FS50_5  (0x2 << 14)
#घोषणा SARMODE0_PRPWT_FS50_11 (0x3 << 14)

#घोषणा SARMODE0_PRPWT_FS155_0 (0x0 << 14)
#घोषणा SARMODE0_PRPWT_FS155_1 (0x1 << 14)
#घोषणा SARMODE0_PRPWT_FS155_2 (0x2 << 14)
#घोषणा SARMODE0_PRPWT_FS155_3 (0x3 << 14)

#घोषणा SARMODE0_SRTS0     (0x1 << 23)
#घोषणा SARMODE0_SRTS1     (0x1 << 24)

#घोषणा SARMODE0_RUN       (0x1 << 25)

#घोषणा SARMODE0_UNLOCK    (0x1 << 26)
#घोषणा SARMODE0_CWRE      (0x1 << 27)


#घोषणा SARMODE0_INTMODE_READCLEAR          (0x0 << 28)
#घोषणा SARMODE0_INTMODE_READNOCLEAR        (0x1 << 28)
#घोषणा SARMODE0_INTMODE_READNOCLEARINHIBIT (0x2 << 28)
#घोषणा SARMODE0_INTMODE_READCLEARINHIBIT   (0x3 << 28)  /* Tell me you करोn't believe me. */

#घोषणा SARMODE0_GINT      (0x1 << 30)
#घोषणा SARMODE0_SHADEN    (0x1 << 31)


#घोषणा SARMODE1     0x60


#घोषणा SARMODE1_TRTL_SHIFT 0   /* Program to 0 */
#घोषणा SARMODE1_RRTL_SHIFT 4   /* Program to 0 */

#घोषणा SARMODE1_TAGM       (0x1 <<  8)  /* Program to 0 */

#घोषणा SARMODE1_HECM0      (0x1 <<  9)
#घोषणा SARMODE1_HECM1      (0x1 << 10)
#घोषणा SARMODE1_HECM2      (0x1 << 11)

#घोषणा SARMODE1_GFCE       (0x1 << 14)
#घोषणा SARMODE1_GFCR       (0x1 << 15)
#घोषणा SARMODE1_PMS        (0x1 << 18)
#घोषणा SARMODE1_GPRI       (0x1 << 19)
#घोषणा SARMODE1_GPAS       (0x1 << 20)
#घोषणा SARMODE1_GVAS       (0x1 << 21)
#घोषणा SARMODE1_GNAM       (0x1 << 22)
#घोषणा SARMODE1_GPLEN      (0x1 << 23)
#घोषणा SARMODE1_DUMPE      (0x1 << 24)
#घोषणा SARMODE1_OAMCRC     (0x1 << 25)
#घोषणा SARMODE1_DCOAM      (0x1 << 26)
#घोषणा SARMODE1_DCRM       (0x1 << 27)
#घोषणा SARMODE1_TSTLP      (0x1 << 28)
#घोषणा SARMODE1_DEFHEC     (0x1 << 29)


#घोषणा ISR      0x64
#घोषणा IUSR     0x68
#घोषणा IMR      0x6c

#घोषणा ISR_LPCO          (0x1 <<  0)
#घोषणा ISR_DPCO          (0x1 <<  1)
#घोषणा ISR_RBRQ0_W       (0x1 <<  2)
#घोषणा ISR_RBRQ1_W       (0x1 <<  3)
#घोषणा ISR_RBRQ2_W       (0x1 <<  4)
#घोषणा ISR_RBRQ3_W       (0x1 <<  5)
#घोषणा ISR_RBRQ0_NF      (0x1 <<  6)
#घोषणा ISR_RBRQ1_NF      (0x1 <<  7)
#घोषणा ISR_RBRQ2_NF      (0x1 <<  8)
#घोषणा ISR_RBRQ3_NF      (0x1 <<  9)
#घोषणा ISR_BFP_SC        (0x1 << 10)
#घोषणा ISR_INIT          (0x1 << 11)
#घोषणा ISR_INIT_ERR      (0x1 << 12) /* Documented as "reserved" */
#घोषणा ISR_USCEO         (0x1 << 13)
#घोषणा ISR_UPEC0         (0x1 << 14)
#घोषणा ISR_VPFCO         (0x1 << 15)
#घोषणा ISR_CRCCO         (0x1 << 16)
#घोषणा ISR_HECO          (0x1 << 17)
#घोषणा ISR_TBRQ_W        (0x1 << 18)
#घोषणा ISR_TBRQ_NF       (0x1 << 19)
#घोषणा ISR_CTPQ_E        (0x1 << 20)
#घोषणा ISR_GFC_C0        (0x1 << 21)
#घोषणा ISR_PCI_FTL       (0x1 << 22)
#घोषणा ISR_CSQ_W         (0x1 << 23)
#घोषणा ISR_CSQ_NF        (0x1 << 24)
#घोषणा ISR_EXT_INT       (0x1 << 25)
#घोषणा ISR_RXDMA_S       (0x1 << 26)


#घोषणा TMCONF 0x78
/* Bits? */


#घोषणा CALPRESCALE 0x7c
/* Bits? */

#घोषणा CELLOSCONF 0x84
#घोषणा CELLOSCONF_COTS   (0x1 << 28)
#घोषणा CELLOSCONF_CEN    (0x1 << 27)
#घोषणा CELLOSCONF_SC8    (0x3 << 24)
#घोषणा CELLOSCONF_SC4    (0x2 << 24)
#घोषणा CELLOSCONF_SC2    (0x1 << 24)
#घोषणा CELLOSCONF_SC1    (0x0 << 24)

#घोषणा CELLOSCONF_COBS   (0x1 << 16)
#घोषणा CELLOSCONF_COPK   (0x1 <<  8)
#घोषणा CELLOSCONF_COST   (0x1 <<  0)
/* Bits? */

#घोषणा RAS0 0x1bc
#घोषणा RAS0_DCD_XHLT (0x1 << 31)

#घोषणा RAS0_VPSEL    (0x1 << 16)
#घोषणा RAS0_VCSEL    (0x1 <<  0)

#घोषणा RAS1 0x1c0
#घोषणा RAS1_UTREG    (0x1 << 5)


#घोषणा DMAMR 0x1cc
#घोषणा DMAMR_TX_MODE_FULL (0x0 << 0)
#घोषणा DMAMR_TX_MODE_PART (0x1 << 0)
#घोषणा DMAMR_TX_MODE_NONE (0x2 << 0) /* And 3 */



#घोषणा RAS2 0x280

#घोषणा RAS2_NNI  (0x1 << 0)
#घोषणा RAS2_USEL (0x1 << 1)
#घोषणा RAS2_UBS  (0x1 << 2)



काष्ठा fs_transmit_config अणु
	u32 flags;
	u32 aपंचांग_hdr;
	u32 TMC[4];
	u32 spec;
	u32 rtag[3];
पूर्ण;

#घोषणा TC_FLAGS_AAL5      (0x0 << 29)
#घोषणा TC_FLAGS_TRANSPARENT_PAYLOAD (0x1 << 29)
#घोषणा TC_FLAGS_TRANSPARENT_CELL    (0x2 << 29)
#घोषणा TC_FLAGS_STREAMING (0x1 << 28)
#घोषणा TC_FLAGS_PACKET    (0x0) 
#घोषणा TC_FLAGS_TYPE_ABR  (0x0 << 22)
#घोषणा TC_FLAGS_TYPE_CBR  (0x1 << 22)
#घोषणा TC_FLAGS_TYPE_VBR  (0x2 << 22)
#घोषणा TC_FLAGS_TYPE_UBR  (0x3 << 22)
#घोषणा TC_FLAGS_CAL0      (0x0 << 20)
#घोषणा TC_FLAGS_CAL1      (0x1 << 20)
#घोषणा TC_FLAGS_CAL2      (0x2 << 20)
#घोषणा TC_FLAGS_CAL3      (0x3 << 20)


#घोषणा RC_FLAGS_NAM        (0x1 << 13)
#घोषणा RC_FLAGS_RXBM_PSB   (0x0 << 14)
#घोषणा RC_FLAGS_RXBM_CIF   (0x1 << 14)
#घोषणा RC_FLAGS_RXBM_PMB   (0x2 << 14)
#घोषणा RC_FLAGS_RXBM_STR   (0x4 << 14)
#घोषणा RC_FLAGS_RXBM_SAF   (0x6 << 14)
#घोषणा RC_FLAGS_RXBM_POS   (0x6 << 14)
#घोषणा RC_FLAGS_BFPS       (0x1 << 17)

#घोषणा RC_FLAGS_BFPS_BFP   (0x1 << 17)

#घोषणा RC_FLAGS_BFPS_BFP0  (0x0 << 17)
#घोषणा RC_FLAGS_BFPS_BFP1  (0x1 << 17)
#घोषणा RC_FLAGS_BFPS_BFP2  (0x2 << 17)
#घोषणा RC_FLAGS_BFPS_BFP3  (0x3 << 17)
#घोषणा RC_FLAGS_BFPS_BFP4  (0x4 << 17)
#घोषणा RC_FLAGS_BFPS_BFP5  (0x5 << 17)
#घोषणा RC_FLAGS_BFPS_BFP6  (0x6 << 17)
#घोषणा RC_FLAGS_BFPS_BFP7  (0x7 << 17)
#घोषणा RC_FLAGS_BFPS_BFP01 (0x8 << 17)
#घोषणा RC_FLAGS_BFPS_BFP23 (0x9 << 17)
#घोषणा RC_FLAGS_BFPS_BFP45 (0xa << 17)
#घोषणा RC_FLAGS_BFPS_BFP67 (0xb << 17)
#घोषणा RC_FLAGS_BFPS_BFP07 (0xc << 17)
#घोषणा RC_FLAGS_BFPS_BFP27 (0xd << 17)
#घोषणा RC_FLAGS_BFPS_BFP47 (0xe << 17)

#घोषणा RC_FLAGS_BFPP       (0x1 << 21)
#घोषणा RC_FLAGS_TEVC       (0x1 << 22)
#घोषणा RC_FLAGS_TEP        (0x1 << 23)
#घोषणा RC_FLAGS_AAL5       (0x0 << 24)
#घोषणा RC_FLAGS_TRANSP     (0x1 << 24)
#घोषणा RC_FLAGS_TRANSC     (0x2 << 24)
#घोषणा RC_FLAGS_ML         (0x1 << 27)
#घोषणा RC_FLAGS_TRBRM      (0x1 << 28)
#घोषणा RC_FLAGS_PRI        (0x1 << 29)
#घोषणा RC_FLAGS_HOAM       (0x1 << 30)
#घोषणा RC_FLAGS_CRC10      (0x1 << 31)


#घोषणा RAC 0x1c8
#घोषणा RAM 0x1c4



/************************************************************************
 *         Then the dataकाष्ठाures that the DRIVER uses.                *
 ************************************************************************/

#घोषणा TXQ_NENTRIES  32
#घोषणा RXRQ_NENTRIES 1024


काष्ठा fs_vcc अणु
	पूर्णांक channo;
	रुको_queue_head_t बंद_रुको;
	काष्ठा sk_buff *last_skb;
पूर्ण;


काष्ठा queue अणु
	काष्ठा FS_QENTRY *sa, *ea;  
	पूर्णांक offset;
पूर्ण;

काष्ठा मुक्तpool अणु
	पूर्णांक offset;
	पूर्णांक bufsize;
	पूर्णांक nr_buffers;
	पूर्णांक n;
पूर्ण;


काष्ठा fs_dev अणु
	काष्ठा fs_dev *next;		/* other FS devices */
	पूर्णांक flags;

	अचिन्हित अक्षर irq;		/* IRQ */
	काष्ठा pci_dev *pci_dev;	/* PCI stuff */
	काष्ठा aपंचांग_dev *aपंचांग_dev;
	काष्ठा समयr_list समयr;

	अचिन्हित दीर्घ hw_base;		/* mem base address */
	व्योम __iomem *base;             /* Mapping of base address */
	पूर्णांक channo;
	अचिन्हित दीर्घ channel_mask;

	काष्ठा queue    hp_txq, lp_txq, tx_relq, st_q;
	काष्ठा मुक्तpool rx_fp[FS_NR_FREE_POOLS];
	काष्ठा queue    rx_rq[FS_NR_RX_QUEUES];

	पूर्णांक nchannels;
	काष्ठा aपंचांग_vcc **aपंचांग_vccs;
	व्योम *tx_inuse;
	पूर्णांक ntxpckts;
पूर्ण;




/* Number of channesl that the FS50 supports. */
#घोषणा FS50_CHANNEL_BITS  5
#घोषणा FS50_NR_CHANNELS      (1 << FS50_CHANNEL_BITS)

         
#घोषणा FS_DEV(aपंचांग_dev) ((काष्ठा fs_dev *) (aपंचांग_dev)->dev_data)
#घोषणा FS_VCC(aपंचांग_vcc) ((काष्ठा fs_vcc *) (aपंचांग_vcc)->dev_data)


#घोषणा FS_IS50  0x1
#घोषणा FS_IS155 0x2

#घोषणा IS_FS50(dev)  (dev->flags & FS_IS50)
#घोषणा IS_FS155(dev) (dev->flags & FS_IS155)
 
/* Within limits this is user-configurable. */
/* Note: Currently the sum (10 -> 1k channels) is hardcoded in the driver. */
#घोषणा FS155_VPI_BITS 4
#घोषणा FS155_VCI_BITS 6

#घोषणा FS155_CHANNEL_BITS  (FS155_VPI_BITS + FS155_VCI_BITS)
#घोषणा FS155_NR_CHANNELS   (1 << FS155_CHANNEL_BITS)
