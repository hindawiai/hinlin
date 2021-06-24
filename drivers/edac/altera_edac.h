<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2017-2018, Intel Corporation
 * Copyright (C) 2015 Altera Corporation
 */

#अगर_अघोषित _ALTERA_EDAC_H
#घोषणा _ALTERA_EDAC_H

#समावेश <linux/arm-smccc.h>
#समावेश <linux/edac.h>
#समावेश <linux/types.h>

/* SDRAM Controller CtrlCfg Register */
#घोषणा CV_CTLCFG_OFST             0x00

/* SDRAM Controller CtrlCfg Register Bit Masks */
#घोषणा CV_CTLCFG_ECC_EN           0x400
#घोषणा CV_CTLCFG_ECC_CORR_EN      0x800
#घोषणा CV_CTLCFG_GEN_SB_ERR       0x2000
#घोषणा CV_CTLCFG_GEN_DB_ERR       0x4000

#घोषणा CV_CTLCFG_ECC_AUTO_EN     (CV_CTLCFG_ECC_EN)

/* SDRAM Controller Address Width Register */
#घोषणा CV_DRAMADDRW_OFST          0x2C

/* SDRAM Controller Address Widths Field Register */
#घोषणा DRAMADDRW_COLBIT_MASK      0x001F
#घोषणा DRAMADDRW_COLBIT_SHIFT     0
#घोषणा DRAMADDRW_ROWBIT_MASK      0x03E0
#घोषणा DRAMADDRW_ROWBIT_SHIFT     5
#घोषणा CV_DRAMADDRW_BANKBIT_MASK  0x1C00
#घोषणा CV_DRAMADDRW_BANKBIT_SHIFT 10
#घोषणा CV_DRAMADDRW_CSBIT_MASK    0xE000
#घोषणा CV_DRAMADDRW_CSBIT_SHIFT   13

/* SDRAM Controller Interface Data Width Register */
#घोषणा CV_DRAMIFWIDTH_OFST        0x30

/* SDRAM Controller Interface Data Width Defines */
#घोषणा CV_DRAMIFWIDTH_16B_ECC     24
#घोषणा CV_DRAMIFWIDTH_32B_ECC     40

/* SDRAM Controller DRAM Status Register */
#घोषणा CV_DRAMSTS_OFST            0x38

/* SDRAM Controller DRAM Status Register Bit Masks */
#घोषणा CV_DRAMSTS_SBEERR          0x04
#घोषणा CV_DRAMSTS_DBEERR          0x08
#घोषणा CV_DRAMSTS_CORR_DROP       0x10

/* SDRAM Controller DRAM IRQ Register */
#घोषणा CV_DRAMINTR_OFST           0x3C

/* SDRAM Controller DRAM IRQ Register Bit Masks */
#घोषणा CV_DRAMINTR_INTREN         0x01
#घोषणा CV_DRAMINTR_SBEMASK        0x02
#घोषणा CV_DRAMINTR_DBEMASK        0x04
#घोषणा CV_DRAMINTR_CORRDROPMASK   0x08
#घोषणा CV_DRAMINTR_INTRCLR        0x10

/* SDRAM Controller Single Bit Error Count Register */
#घोषणा CV_SBECOUNT_OFST           0x40

/* SDRAM Controller Double Bit Error Count Register */
#घोषणा CV_DBECOUNT_OFST           0x44

/* SDRAM Controller ECC Error Address Register */
#घोषणा CV_ERRADDR_OFST            0x48

/*-----------------------------------------*/

/* SDRAM Controller EccCtrl Register */
#घोषणा A10_ECCCTRL1_OFST          0x00

/* SDRAM Controller EccCtrl Register Bit Masks */
#घोषणा A10_ECCCTRL1_ECC_EN        0x001
#घोषणा A10_ECCCTRL1_CNT_RST       0x010
#घोषणा A10_ECCCTRL1_AWB_CNT_RST   0x100
#घोषणा A10_ECC_CNT_RESET_MASK     (A10_ECCCTRL1_CNT_RST | \
				    A10_ECCCTRL1_AWB_CNT_RST)

/* SDRAM Controller Address Width Register */
#घोषणा CV_DRAMADDRW               0xFFC2502C
#घोषणा A10_DRAMADDRW              0xFFCFA0A8
#घोषणा S10_DRAMADDRW              0xF80110E0

/* SDRAM Controller Address Widths Field Register */
#घोषणा DRAMADDRW_COLBIT_MASK      0x001F
#घोषणा DRAMADDRW_COLBIT_SHIFT     0
#घोषणा DRAMADDRW_ROWBIT_MASK      0x03E0
#घोषणा DRAMADDRW_ROWBIT_SHIFT     5
#घोषणा CV_DRAMADDRW_BANKBIT_MASK  0x1C00
#घोषणा CV_DRAMADDRW_BANKBIT_SHIFT 10
#घोषणा CV_DRAMADDRW_CSBIT_MASK    0xE000
#घोषणा CV_DRAMADDRW_CSBIT_SHIFT   13

#घोषणा A10_DRAMADDRW_BANKBIT_MASK  0x3C00
#घोषणा A10_DRAMADDRW_BANKBIT_SHIFT 10
#घोषणा A10_DRAMADDRW_GRPBIT_MASK   0xC000
#घोषणा A10_DRAMADDRW_GRPBIT_SHIFT  14
#घोषणा A10_DRAMADDRW_CSBIT_MASK    0x70000
#घोषणा A10_DRAMADDRW_CSBIT_SHIFT   16

/* SDRAM Controller Interface Data Width Register */
#घोषणा CV_DRAMIFWIDTH             0xFFC25030
#घोषणा A10_DRAMIFWIDTH            0xFFCFB008
#घोषणा S10_DRAMIFWIDTH            0xF8011008

/* SDRAM Controller Interface Data Width Defines */
#घोषणा CV_DRAMIFWIDTH_16B_ECC     24
#घोषणा CV_DRAMIFWIDTH_32B_ECC     40

#घोषणा A10_DRAMIFWIDTH_16B        0x0
#घोषणा A10_DRAMIFWIDTH_32B        0x1
#घोषणा A10_DRAMIFWIDTH_64B        0x2

/* SDRAM Controller DRAM IRQ Register */
#घोषणा A10_ERRINTEN_OFST          0x10

/* SDRAM Controller DRAM IRQ Register Bit Masks */
#घोषणा A10_ERRINTEN_SERRINTEN     0x01
#घोषणा A10_ERRINTEN_DERRINTEN     0x02
#घोषणा A10_ECC_IRQ_EN_MASK        (A10_ERRINTEN_SERRINTEN | \
				    A10_ERRINTEN_DERRINTEN)

/* SDRAM Interrupt Mode Register */
#घोषणा A10_INTMODE_OFST           0x1C
#घोषणा A10_INTMODE_SB_INT         1

/* SDRAM Controller Error Status Register */
#घोषणा A10_INTSTAT_OFST           0x20

/* SDRAM Controller Error Status Register Bit Masks */
#घोषणा A10_INTSTAT_SBEERR         0x01
#घोषणा A10_INTSTAT_DBEERR         0x02

/* SDRAM Controller ECC Error Address Register */
#घोषणा A10_DERRADDR_OFST          0x2C
#घोषणा A10_SERRADDR_OFST          0x30

/* SDRAM Controller ECC Diagnostic Register */
#घोषणा A10_DIAGINTTEST_OFST       0x24

#घोषणा A10_DIAGINT_TSERRA_MASK    0x0001
#घोषणा A10_DIAGINT_TDERRA_MASK    0x0100

#घोषणा A10_SBERR_IRQ              34
#घोषणा A10_DBERR_IRQ              32

/* SDRAM Single Bit Error Count Compare Set Register */
#घोषणा A10_SERRCNTREG_OFST        0x3C

#घोषणा A10_SYMAN_INTMASK_CLR      0xFFD06098
#घोषणा A10_INTMASK_CLR_OFST       0x10
#घोषणा A10_DDR0_IRQ_MASK          BIT(17)

काष्ठा altr_sdram_prv_data अणु
	पूर्णांक ecc_ctrl_offset;
	पूर्णांक ecc_ctl_en_mask;
	पूर्णांक ecc_cecnt_offset;
	पूर्णांक ecc_uecnt_offset;
	पूर्णांक ecc_stat_offset;
	पूर्णांक ecc_stat_ce_mask;
	पूर्णांक ecc_stat_ue_mask;
	पूर्णांक ecc_saddr_offset;
	पूर्णांक ecc_daddr_offset;
	पूर्णांक ecc_irq_en_offset;
	पूर्णांक ecc_irq_en_mask;
	पूर्णांक ecc_irq_clr_offset;
	पूर्णांक ecc_irq_clr_mask;
	पूर्णांक ecc_cnt_rst_offset;
	पूर्णांक ecc_cnt_rst_mask;
	काष्ठा edac_dev_sysfs_attribute *eccmgr_sysfs_attr;
	पूर्णांक ecc_enable_mask;
	पूर्णांक ce_set_mask;
	पूर्णांक ue_set_mask;
	पूर्णांक ce_ue_trgr_offset;
पूर्ण;

/* Altera SDRAM Memory Controller data */
काष्ठा altr_sdram_mc_data अणु
	काष्ठा regmap *mc_vbase;
	पूर्णांक sb_irq;
	पूर्णांक db_irq;
	स्थिर काष्ठा altr_sdram_prv_data *data;
पूर्ण;

/************************** EDAC Device Defines **************************/
/***** General Device Trigger Defines *****/
#घोषणा ALTR_UE_TRIGGER_CHAR            'U'   /* Trigger क्रम UE */
#घोषणा ALTR_TRIGGER_READ_WRD_CNT       32    /* Line size x 4 */
#घोषणा ALTR_TRIG_OCRAM_BYTE_SIZE       128   /* Line size x 4 */
#घोषणा ALTR_TRIG_L2C_BYTE_SIZE         4096  /* Full Page */

/******* Cyclone5 and Arria5 Defines *******/
/* OCRAM ECC Management Group Defines */
#घोषणा ALTR_MAN_GRP_OCRAM_ECC_OFFSET   0x04
#घोषणा ALTR_OCR_ECC_REG_OFFSET         0x00
#घोषणा ALTR_OCR_ECC_EN                 BIT(0)
#घोषणा ALTR_OCR_ECC_INJS               BIT(1)
#घोषणा ALTR_OCR_ECC_INJD               BIT(2)
#घोषणा ALTR_OCR_ECC_SERR               BIT(3)
#घोषणा ALTR_OCR_ECC_DERR               BIT(4)

/* L2 ECC Management Group Defines */
#घोषणा ALTR_MAN_GRP_L2_ECC_OFFSET      0x00
#घोषणा ALTR_L2_ECC_REG_OFFSET          0x00
#घोषणा ALTR_L2_ECC_EN                  BIT(0)
#घोषणा ALTR_L2_ECC_INJS                BIT(1)
#घोषणा ALTR_L2_ECC_INJD                BIT(2)

/* Arria10 General ECC Block Module Defines */
#घोषणा ALTR_A10_ECC_CTRL_OFST          0x08
#घोषणा ALTR_A10_ECC_EN                 BIT(0)
#घोषणा ALTR_A10_ECC_INITA              BIT(16)
#घोषणा ALTR_A10_ECC_INITB              BIT(24)

#घोषणा ALTR_A10_ECC_INITSTAT_OFST      0x0C
#घोषणा ALTR_A10_ECC_INITCOMPLETEA      BIT(0)
#घोषणा ALTR_A10_ECC_INITCOMPLETEB      BIT(8)

#घोषणा ALTR_A10_ECC_ERRINTEN_OFST      0x10
#घोषणा ALTR_A10_ECC_ERRINTENS_OFST     0x14
#घोषणा ALTR_A10_ECC_ERRINTENR_OFST     0x18
#घोषणा ALTR_A10_ECC_SERRINTEN          BIT(0)

#घोषणा ALTR_A10_ECC_INTMODE_OFST       0x1C
#घोषणा ALTR_A10_ECC_INTMODE            BIT(0)

#घोषणा ALTR_A10_ECC_INTSTAT_OFST       0x20
#घोषणा ALTR_A10_ECC_SERRPENA           BIT(0)
#घोषणा ALTR_A10_ECC_DERRPENA           BIT(8)
#घोषणा ALTR_A10_ECC_ERRPENA_MASK       (ALTR_A10_ECC_SERRPENA | \
					 ALTR_A10_ECC_DERRPENA)
#घोषणा ALTR_A10_ECC_SERRPENB           BIT(16)
#घोषणा ALTR_A10_ECC_DERRPENB           BIT(24)
#घोषणा ALTR_A10_ECC_ERRPENB_MASK       (ALTR_A10_ECC_SERRPENB | \
					 ALTR_A10_ECC_DERRPENB)

#घोषणा ALTR_A10_ECC_INTTEST_OFST       0x24
#घोषणा ALTR_A10_ECC_TSERRA             BIT(0)
#घोषणा ALTR_A10_ECC_TDERRA             BIT(8)
#घोषणा ALTR_A10_ECC_TSERRB             BIT(16)
#घोषणा ALTR_A10_ECC_TDERRB             BIT(24)

/* ECC Manager Defines */
#घोषणा A10_SYSMGR_ECC_INTMASK_SET_OFST   0x94
#घोषणा A10_SYSMGR_ECC_INTMASK_CLR_OFST   0x98
#घोषणा A10_SYSMGR_ECC_INTMASK_OCRAM      BIT(1)

#घोषणा A10_SYSMGR_ECC_INTSTAT_SERR_OFST  0x9C
#घोषणा A10_SYSMGR_ECC_INTSTAT_DERR_OFST  0xA0
#घोषणा A10_SYSMGR_ECC_INTSTAT_L2         BIT(0)
#घोषणा A10_SYSMGR_ECC_INTSTAT_OCRAM      BIT(1)

#घोषणा A10_SYSGMR_MPU_CLEAR_L2_ECC_OFST  0xA8
#घोषणा A10_SYSGMR_MPU_CLEAR_L2_ECC_SB    BIT(15)
#घोषणा A10_SYSGMR_MPU_CLEAR_L2_ECC_MB    BIT(31)

/* Arria 10 L2 ECC Management Group Defines */
#घोषणा ALTR_A10_L2_ECC_CTL_OFST        0x0
#घोषणा ALTR_A10_L2_ECC_EN_CTL          BIT(0)

#घोषणा ALTR_A10_L2_ECC_STATUS          0xFFD060A4
#घोषणा ALTR_A10_L2_ECC_STAT_OFST       0xA4
#घोषणा ALTR_A10_L2_ECC_SERR_PEND       BIT(0)
#घोषणा ALTR_A10_L2_ECC_MERR_PEND       BIT(0)

#घोषणा ALTR_A10_L2_ECC_CLR_OFST        0x4
#घोषणा ALTR_A10_L2_ECC_SERR_CLR        BIT(15)
#घोषणा ALTR_A10_L2_ECC_MERR_CLR        BIT(31)

#घोषणा ALTR_A10_L2_ECC_INJ_OFST        ALTR_A10_L2_ECC_CTL_OFST
#घोषणा ALTR_A10_L2_ECC_CE_INJ_MASK     0x00000101
#घोषणा ALTR_A10_L2_ECC_UE_INJ_MASK     0x00010101

/* Arria 10 OCRAM ECC Management Group Defines */
#घोषणा ALTR_A10_OCRAM_ECC_EN_CTL       (BIT(1) | BIT(0))

/* Arria 10 Ethernet ECC Management Group Defines */
#घोषणा ALTR_A10_COMMON_ECC_EN_CTL      BIT(0)

/* Arria 10 SDMMC ECC Management Group Defines */
#घोषणा ALTR_A10_SDMMC_IRQ_MASK         (BIT(16) | BIT(15))

/* A10 ECC Controller memory initialization समयout */
#घोषणा ALTR_A10_ECC_INIT_WATCHDOG_10US      10000

/************* Stratix10 Defines **************/
#घोषणा ALTR_S10_ECC_CTRL_SDRAM_OFST      0x00
#घोषणा ALTR_S10_ECC_EN                   BIT(0)

#घोषणा ALTR_S10_ECC_ERRINTEN_OFST        0x10
#घोषणा ALTR_S10_ECC_ERRINTENS_OFST       0x14
#घोषणा ALTR_S10_ECC_ERRINTENR_OFST       0x18
#घोषणा ALTR_S10_ECC_SERRINTEN            BIT(0)

#घोषणा ALTR_S10_ECC_INTMODE_OFST         0x1C
#घोषणा ALTR_S10_ECC_INTMODE              BIT(0)

#घोषणा ALTR_S10_ECC_INTSTAT_OFST         0x20
#घोषणा ALTR_S10_ECC_SERRPENA             BIT(0)
#घोषणा ALTR_S10_ECC_DERRPENA             BIT(8)
#घोषणा ALTR_S10_ECC_ERRPENA_MASK         (ALTR_S10_ECC_SERRPENA | \
					   ALTR_S10_ECC_DERRPENA)

#घोषणा ALTR_S10_ECC_INTTEST_OFST         0x24
#घोषणा ALTR_S10_ECC_TSERRA               BIT(0)
#घोषणा ALTR_S10_ECC_TDERRA               BIT(8)
#घोषणा ALTR_S10_ECC_TSERRB               BIT(16)
#घोषणा ALTR_S10_ECC_TDERRB               BIT(24)

#घोषणा ALTR_S10_DERR_ADDRA_OFST          0x2C

/* Stratix10 ECC Manager Defines */
#घोषणा S10_SYSMGR_ECC_INTMASK_CLR_OFST   0x98
#घोषणा S10_SYSMGR_ECC_INTSTAT_DERR_OFST  0xA0

/* Sticky रेजिस्टरs क्रम Uncorrected Errors */
#घोषणा S10_SYSMGR_UE_VAL_OFST            0x220
#घोषणा S10_SYSMGR_UE_ADDR_OFST           0x224

#घोषणा S10_DDR0_IRQ_MASK                 BIT(16)
#घोषणा S10_DBE_IRQ_MASK                  0x3FFFE

/* Define ECC Block Offsets क्रम peripherals */
#घोषणा ECC_BLK_ADDRESS_OFST              0x40
#घोषणा ECC_BLK_RDATA0_OFST               0x44
#घोषणा ECC_BLK_RDATA1_OFST               0x48
#घोषणा ECC_BLK_RDATA2_OFST               0x4C
#घोषणा ECC_BLK_RDATA3_OFST               0x50
#घोषणा ECC_BLK_WDATA0_OFST               0x54
#घोषणा ECC_BLK_WDATA1_OFST               0x58
#घोषणा ECC_BLK_WDATA2_OFST               0x5C
#घोषणा ECC_BLK_WDATA3_OFST               0x60
#घोषणा ECC_BLK_RECC0_OFST                0x64
#घोषणा ECC_BLK_RECC1_OFST                0x68
#घोषणा ECC_BLK_WECC0_OFST                0x6C
#घोषणा ECC_BLK_WECC1_OFST                0x70
#घोषणा ECC_BLK_DBYTECTRL_OFST            0x74
#घोषणा ECC_BLK_ACCCTRL_OFST              0x78
#घोषणा ECC_BLK_STARTACC_OFST             0x7C

#घोषणा ECC_XACT_KICK                     0x10000
#घोषणा ECC_WORD_WRITE                    0xFF
#घोषणा ECC_WRITE_DOVR                    0x101
#घोषणा ECC_WRITE_EDOVR                   0x103
#घोषणा ECC_READ_EOVR                     0x2
#घोषणा ECC_READ_EDOVR                    0x3

काष्ठा altr_edac_device_dev;

काष्ठा edac_device_prv_data अणु
	पूर्णांक (*setup)(काष्ठा altr_edac_device_dev *device);
	पूर्णांक ce_clear_mask;
	पूर्णांक ue_clear_mask;
	पूर्णांक irq_status_mask;
	व्योम * (*alloc_mem)(माप_प्रकार size, व्योम **other);
	व्योम (*मुक्त_mem)(व्योम *p, माप_प्रकार size, व्योम *other);
	पूर्णांक ecc_enable_mask;
	पूर्णांक ecc_en_ofst;
	पूर्णांक ce_set_mask;
	पूर्णांक ue_set_mask;
	पूर्णांक set_err_ofst;
	irqवापस_t (*ecc_irq_handler)(पूर्णांक irq, व्योम *dev_id);
	पूर्णांक trig_alloc_sz;
	स्थिर काष्ठा file_operations *inject_fops;
	bool panic;
पूर्ण;

काष्ठा altr_edac_device_dev अणु
	काष्ठा list_head next;
	व्योम __iomem *base;
	पूर्णांक sb_irq;
	पूर्णांक db_irq;
	स्थिर काष्ठा edac_device_prv_data *data;
	काष्ठा dentry *debugfs_dir;
	अक्षर *edac_dev_name;
	काष्ठा altr_arria10_edac *edac;
	काष्ठा edac_device_ctl_info *edac_dev;
	काष्ठा device ddev;
	पूर्णांक edac_idx;
पूर्ण;

काष्ठा altr_arria10_edac अणु
	काष्ठा device		*dev;
	काष्ठा regmap		*ecc_mgr_map;
	पूर्णांक sb_irq;
	पूर्णांक db_irq;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	काष्ठा irq_chip		irq_chip;
	काष्ठा list_head	a10_ecc_devices;
	काष्ठा notअगरier_block	panic_notअगरier;
पूर्ण;

#पूर्ण_अगर	/* #अगर_अघोषित _ALTERA_EDAC_H */
