<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2015-2017 Netronome Systems, Inc. */

/*
 * nfp_arm.h
 * Definitions क्रम ARM-based रेजिस्टरs and memory spaces
 */

#अगर_अघोषित NFP_ARM_H
#घोषणा NFP_ARM_H

#घोषणा NFP_ARM_QUEUE(_q)              (0x100000 + (0x800 * ((_q) & 0xff)))
#घोषणा NFP_ARM_IM                     0x200000
#घोषणा NFP_ARM_EM                     0x300000
#घोषणा NFP_ARM_GCSR                   0x400000
#घोषणा NFP_ARM_MPCORE                 0x800000
#घोषणा NFP_ARM_PL310                  0xa00000
/* Register Type: BulkBARConfig */
#घोषणा NFP_ARM_GCSR_BULK_BAR(_bar)    (0x0 + (0x4 * ((_bar) & 0x7)))
#घोषणा   NFP_ARM_GCSR_BULK_BAR_TYPE                    (0x1 << 31)
#घोषणा     NFP_ARM_GCSR_BULK_BAR_TYPE_BULK             (0x0)
#घोषणा     NFP_ARM_GCSR_BULK_BAR_TYPE_EXPA             (0x80000000)
#घोषणा   NFP_ARM_GCSR_BULK_BAR_TGT(_x)                 (((_x) & 0xf) << 27)
#घोषणा   NFP_ARM_GCSR_BULK_BAR_TGT_of(_x)              (((_x) >> 27) & 0xf)
#घोषणा   NFP_ARM_GCSR_BULK_BAR_TOK(_x)                 (((_x) & 0x3) << 25)
#घोषणा   NFP_ARM_GCSR_BULK_BAR_TOK_of(_x)              (((_x) >> 25) & 0x3)
#घोषणा   NFP_ARM_GCSR_BULK_BAR_LEN                     (0x1 << 24)
#घोषणा     NFP_ARM_GCSR_BULK_BAR_LEN_32BIT             (0x0)
#घोषणा     NFP_ARM_GCSR_BULK_BAR_LEN_64BIT             (0x1000000)
#घोषणा   NFP_ARM_GCSR_BULK_BAR_ADDR(_x)                ((_x) & 0x7ff)
#घोषणा   NFP_ARM_GCSR_BULK_BAR_ADDR_of(_x)             ((_x) & 0x7ff)
/* Register Type: ExpansionBARConfig */
#घोषणा NFP_ARM_GCSR_EXPA_BAR(_bar)    (0x20 + (0x4 * ((_bar) & 0xf)))
#घोषणा   NFP_ARM_GCSR_EXPA_BAR_TYPE                    (0x1 << 31)
#घोषणा     NFP_ARM_GCSR_EXPA_BAR_TYPE_EXPA             (0x0)
#घोषणा     NFP_ARM_GCSR_EXPA_BAR_TYPE_EXPL             (0x80000000)
#घोषणा   NFP_ARM_GCSR_EXPA_BAR_TGT(_x)                 (((_x) & 0xf) << 27)
#घोषणा   NFP_ARM_GCSR_EXPA_BAR_TGT_of(_x)              (((_x) >> 27) & 0xf)
#घोषणा   NFP_ARM_GCSR_EXPA_BAR_TOK(_x)                 (((_x) & 0x3) << 25)
#घोषणा   NFP_ARM_GCSR_EXPA_BAR_TOK_of(_x)              (((_x) >> 25) & 0x3)
#घोषणा   NFP_ARM_GCSR_EXPA_BAR_LEN                     (0x1 << 24)
#घोषणा     NFP_ARM_GCSR_EXPA_BAR_LEN_32BIT             (0x0)
#घोषणा     NFP_ARM_GCSR_EXPA_BAR_LEN_64BIT             (0x1000000)
#घोषणा   NFP_ARM_GCSR_EXPA_BAR_ACT(_x)                 (((_x) & 0x1f) << 19)
#घोषणा   NFP_ARM_GCSR_EXPA_BAR_ACT_of(_x)              (((_x) >> 19) & 0x1f)
#घोषणा     NFP_ARM_GCSR_EXPA_BAR_ACT_DERIVED           (0)
#घोषणा   NFP_ARM_GCSR_EXPA_BAR_ADDR(_x)                ((_x) & 0x7fff)
#घोषणा   NFP_ARM_GCSR_EXPA_BAR_ADDR_of(_x)             ((_x) & 0x7fff)
/* Register Type: ExplicitBARConfig0_Reg */
#घोषणा NFP_ARM_GCSR_EXPL0_BAR(_bar)   (0x60 + (0x4 * ((_bar) & 0x7)))
#घोषणा   NFP_ARM_GCSR_EXPL0_BAR_ADDR(_x)               ((_x) & 0x3ffff)
#घोषणा   NFP_ARM_GCSR_EXPL0_BAR_ADDR_of(_x)            ((_x) & 0x3ffff)
/* Register Type: ExplicitBARConfig1_Reg */
#घोषणा NFP_ARM_GCSR_EXPL1_BAR(_bar)   (0x80 + (0x4 * ((_bar) & 0x7)))
#घोषणा   NFP_ARM_GCSR_EXPL1_BAR_POSTED                 (0x1 << 31)
#घोषणा   NFP_ARM_GCSR_EXPL1_BAR_SIGNAL_REF(_x)         (((_x) & 0x7f) << 24)
#घोषणा   NFP_ARM_GCSR_EXPL1_BAR_SIGNAL_REF_of(_x)      (((_x) >> 24) & 0x7f)
#घोषणा   NFP_ARM_GCSR_EXPL1_BAR_DATA_MASTER(_x)        (((_x) & 0xff) << 16)
#घोषणा   NFP_ARM_GCSR_EXPL1_BAR_DATA_MASTER_of(_x)     (((_x) >> 16) & 0xff)
#घोषणा   NFP_ARM_GCSR_EXPL1_BAR_DATA_REF(_x)           ((_x) & 0x3fff)
#घोषणा   NFP_ARM_GCSR_EXPL1_BAR_DATA_REF_of(_x)        ((_x) & 0x3fff)
/* Register Type: ExplicitBARConfig2_Reg */
#घोषणा NFP_ARM_GCSR_EXPL2_BAR(_bar)   (0xa0 + (0x4 * ((_bar) & 0x7)))
#घोषणा   NFP_ARM_GCSR_EXPL2_BAR_TGT(_x)                (((_x) & 0xf) << 28)
#घोषणा   NFP_ARM_GCSR_EXPL2_BAR_TGT_of(_x)             (((_x) >> 28) & 0xf)
#घोषणा   NFP_ARM_GCSR_EXPL2_BAR_ACT(_x)                (((_x) & 0x1f) << 23)
#घोषणा   NFP_ARM_GCSR_EXPL2_BAR_ACT_of(_x)             (((_x) >> 23) & 0x1f)
#घोषणा   NFP_ARM_GCSR_EXPL2_BAR_LEN(_x)                (((_x) & 0x1f) << 18)
#घोषणा   NFP_ARM_GCSR_EXPL2_BAR_LEN_of(_x)             (((_x) >> 18) & 0x1f)
#घोषणा   NFP_ARM_GCSR_EXPL2_BAR_BYTE_MASK(_x)          (((_x) & 0xff) << 10)
#घोषणा   NFP_ARM_GCSR_EXPL2_BAR_BYTE_MASK_of(_x)       (((_x) >> 10) & 0xff)
#घोषणा   NFP_ARM_GCSR_EXPL2_BAR_TOK(_x)                (((_x) & 0x3) << 8)
#घोषणा   NFP_ARM_GCSR_EXPL2_BAR_TOK_of(_x)             (((_x) >> 8) & 0x3)
#घोषणा   NFP_ARM_GCSR_EXPL2_BAR_SIGNAL_MASTER(_x)      ((_x) & 0xff)
#घोषणा   NFP_ARM_GCSR_EXPL2_BAR_SIGNAL_MASTER_of(_x)   ((_x) & 0xff)
/* Register Type: PostedCommandSignal */
#घोषणा NFP_ARM_GCSR_EXPL_POST(_bar)   (0xc0 + (0x4 * ((_bar) & 0x7)))
#घोषणा   NFP_ARM_GCSR_EXPL_POST_SIG_B(_x)              (((_x) & 0x7f) << 25)
#घोषणा   NFP_ARM_GCSR_EXPL_POST_SIG_B_of(_x)           (((_x) >> 25) & 0x7f)
#घोषणा   NFP_ARM_GCSR_EXPL_POST_SIG_B_BUS              (0x1 << 24)
#घोषणा     NFP_ARM_GCSR_EXPL_POST_SIG_B_BUS_PULL       (0x0)
#घोषणा     NFP_ARM_GCSR_EXPL_POST_SIG_B_BUS_PUSH       (0x1000000)
#घोषणा   NFP_ARM_GCSR_EXPL_POST_SIG_A(_x)              (((_x) & 0x7f) << 17)
#घोषणा   NFP_ARM_GCSR_EXPL_POST_SIG_A_of(_x)           (((_x) >> 17) & 0x7f)
#घोषणा   NFP_ARM_GCSR_EXPL_POST_SIG_A_BUS              (0x1 << 16)
#घोषणा     NFP_ARM_GCSR_EXPL_POST_SIG_A_BUS_PULL       (0x0)
#घोषणा     NFP_ARM_GCSR_EXPL_POST_SIG_A_BUS_PUSH       (0x10000)
#घोषणा   NFP_ARM_GCSR_EXPL_POST_SIG_B_RCVD             (0x1 << 7)
#घोषणा   NFP_ARM_GCSR_EXPL_POST_SIG_B_VALID            (0x1 << 6)
#घोषणा   NFP_ARM_GCSR_EXPL_POST_SIG_A_RCVD             (0x1 << 5)
#घोषणा   NFP_ARM_GCSR_EXPL_POST_SIG_A_VALID            (0x1 << 4)
#घोषणा   NFP_ARM_GCSR_EXPL_POST_CMD_COMPLETE           (0x1)
/* Register Type: MPCoreBaseAddress */
#घोषणा NFP_ARM_GCSR_MPCORE_BASE       0x00e0
#घोषणा   NFP_ARM_GCSR_MPCORE_BASE_ADDR(_x)             (((_x) & 0x7ffff) << 13)
#घोषणा   NFP_ARM_GCSR_MPCORE_BASE_ADDR_of(_x)          (((_x) >> 13) & 0x7ffff)
/* Register Type: PL310BaseAddress */
#घोषणा NFP_ARM_GCSR_PL310_BASE        0x00e4
#घोषणा   NFP_ARM_GCSR_PL310_BASE_ADDR(_x)              (((_x) & 0xfffff) << 12)
#घोषणा   NFP_ARM_GCSR_PL310_BASE_ADDR_of(_x)           (((_x) >> 12) & 0xfffff)
/* Register Type: MPCoreConfig */
#घोषणा NFP_ARM_GCSR_MP0_CFG           0x00e8
#घोषणा   NFP_ARM_GCSR_MP0_CFG_SPI_BOOT                 (0x1 << 14)
#घोषणा   NFP_ARM_GCSR_MP0_CFG_ENDIAN(_x)               (((_x) & 0x3) << 12)
#घोषणा   NFP_ARM_GCSR_MP0_CFG_ENDIAN_of(_x)            (((_x) >> 12) & 0x3)
#घोषणा     NFP_ARM_GCSR_MP0_CFG_ENDIAN_LITTLE          (0)
#घोषणा     NFP_ARM_GCSR_MP0_CFG_ENDIAN_BIG             (1)
#घोषणा   NFP_ARM_GCSR_MP0_CFG_RESET_VECTOR             (0x1 << 8)
#घोषणा     NFP_ARM_GCSR_MP0_CFG_RESET_VECTOR_LO        (0x0)
#घोषणा     NFP_ARM_GCSR_MP0_CFG_RESET_VECTOR_HI        (0x100)
#घोषणा   NFP_ARM_GCSR_MP0_CFG_OUTCLK_EN(_x)            (((_x) & 0xf) << 4)
#घोषणा   NFP_ARM_GCSR_MP0_CFG_OUTCLK_EN_of(_x)         (((_x) >> 4) & 0xf)
#घोषणा   NFP_ARM_GCSR_MP0_CFG_ARMID(_x)                ((_x) & 0xf)
#घोषणा   NFP_ARM_GCSR_MP0_CFG_ARMID_of(_x)             ((_x) & 0xf)
/* Register Type: MPCoreIDCacheDataError */
#घोषणा NFP_ARM_GCSR_MP0_CACHE_ERR     0x00ec
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_D7             (0x1 << 15)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_D6             (0x1 << 14)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_D5             (0x1 << 13)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_D4             (0x1 << 12)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_D3             (0x1 << 11)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_D2             (0x1 << 10)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_D1             (0x1 << 9)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_D0             (0x1 << 8)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_I7             (0x1 << 7)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_I6             (0x1 << 6)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_I5             (0x1 << 5)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_I4             (0x1 << 4)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_I3             (0x1 << 3)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_I2             (0x1 << 2)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_I1             (0x1 << 1)
#घोषणा   NFP_ARM_GCSR_MP0_CACHE_ERR_MP0_I0             (0x1)
/* Register Type: ARMDFT */
#घोषणा NFP_ARM_GCSR_DFT               0x0100
#घोषणा   NFP_ARM_GCSR_DFT_DBG_REQ                      (0x1 << 20)
#घोषणा   NFP_ARM_GCSR_DFT_DBG_EN                       (0x1 << 19)
#घोषणा   NFP_ARM_GCSR_DFT_WFE_EVT_TRG                  (0x1 << 18)
#घोषणा   NFP_ARM_GCSR_DFT_ETM_WFI_RDY                  (0x1 << 17)
#घोषणा   NFP_ARM_GCSR_DFT_ETM_PWR_ON                   (0x1 << 16)
#घोषणा   NFP_ARM_GCSR_DFT_BIST_FAIL_of(_x)             (((_x) >> 8) & 0xf)
#घोषणा   NFP_ARM_GCSR_DFT_BIST_DONE_of(_x)             (((_x) >> 4) & 0xf)
#घोषणा   NFP_ARM_GCSR_DFT_BIST_RUN(_x)                 ((_x) & 0x7)
#घोषणा   NFP_ARM_GCSR_DFT_BIST_RUN_of(_x)              ((_x) & 0x7)

/* Gasket CSRs */
/* NOTE: These cannot be remapped, and are always at this location.
 */
#घोषणा NFP_ARM_GCSR_START	(0xd6000000 + NFP_ARM_GCSR)
#घोषणा NFP_ARM_GCSR_SIZE	SZ_64K

/* BAR CSRs
 */
#घोषणा NFP_ARM_GCSR_BULK_BITS	11
#घोषणा NFP_ARM_GCSR_EXPA_BITS	15
#घोषणा NFP_ARM_GCSR_EXPL_BITS	18

#घोषणा NFP_ARM_GCSR_BULK_SHIFT	(40 - 11)
#घोषणा NFP_ARM_GCSR_EXPA_SHIFT	(40 - 15)
#घोषणा NFP_ARM_GCSR_EXPL_SHIFT	(40 - 18)

#घोषणा NFP_ARM_GCSR_BULK_SIZE	(1 << NFP_ARM_GCSR_BULK_SHIFT)
#घोषणा NFP_ARM_GCSR_EXPA_SIZE	(1 << NFP_ARM_GCSR_EXPA_SHIFT)
#घोषणा NFP_ARM_GCSR_EXPL_SIZE	(1 << NFP_ARM_GCSR_EXPL_SHIFT)

#घोषणा NFP_ARM_GCSR_EXPL2_CSR(target, action, length, \
			       byte_mask, token, संकेत_master) \
	(NFP_ARM_GCSR_EXPL2_BAR_TGT(target) | \
	 NFP_ARM_GCSR_EXPL2_BAR_ACT(action) | \
	 NFP_ARM_GCSR_EXPL2_BAR_LEN(length) | \
	 NFP_ARM_GCSR_EXPL2_BAR_BYTE_MASK(byte_mask) | \
	 NFP_ARM_GCSR_EXPL2_BAR_TOK(token) | \
	 NFP_ARM_GCSR_EXPL2_BAR_SIGNAL_MASTER(संकेत_master))
#घोषणा NFP_ARM_GCSR_EXPL1_CSR(posted, संकेत_ref, data_master, data_ref) \
	(((posted) ? NFP_ARM_GCSR_EXPL1_BAR_POSTED : 0) | \
	 NFP_ARM_GCSR_EXPL1_BAR_SIGNAL_REF(संकेत_ref) | \
	 NFP_ARM_GCSR_EXPL1_BAR_DATA_MASTER(data_master) | \
	 NFP_ARM_GCSR_EXPL1_BAR_DATA_REF(data_ref))
#घोषणा NFP_ARM_GCSR_EXPL0_CSR(address) \
	NFP_ARM_GCSR_EXPL0_BAR_ADDR((address) >> NFP_ARM_GCSR_EXPL_SHIFT)
#घोषणा NFP_ARM_GCSR_EXPL_POST_EXPECT_A(sig_ref, is_push, is_required) \
	(NFP_ARM_GCSR_EXPL_POST_SIG_A(sig_ref) | \
	 ((is_push) ? NFP_ARM_GCSR_EXPL_POST_SIG_A_BUS_PUSH : \
		      NFP_ARM_GCSR_EXPL_POST_SIG_A_BUS_PULL) | \
	 ((is_required) ? NFP_ARM_GCSR_EXPL_POST_SIG_A_VALID : 0))
#घोषणा NFP_ARM_GCSR_EXPL_POST_EXPECT_B(sig_ref, is_push, is_required) \
	(NFP_ARM_GCSR_EXPL_POST_SIG_B(sig_ref) | \
	 ((is_push) ? NFP_ARM_GCSR_EXPL_POST_SIG_B_BUS_PUSH : \
		      NFP_ARM_GCSR_EXPL_POST_SIG_B_BUS_PULL) | \
	 ((is_required) ? NFP_ARM_GCSR_EXPL_POST_SIG_B_VALID : 0))

#घोषणा NFP_ARM_GCSR_EXPA_CSR(mode, target, token, is_64, action, address) \
	(((mode) ? NFP_ARM_GCSR_EXPA_BAR_TYPE_EXPL : \
		   NFP_ARM_GCSR_EXPA_BAR_TYPE_EXPA) | \
	 NFP_ARM_GCSR_EXPA_BAR_TGT(target) | \
	 NFP_ARM_GCSR_EXPA_BAR_TOK(token) | \
	 ((is_64) ? NFP_ARM_GCSR_EXPA_BAR_LEN_64BIT : \
		    NFP_ARM_GCSR_EXPA_BAR_LEN_32BIT) | \
	 NFP_ARM_GCSR_EXPA_BAR_ACT(action) | \
	 NFP_ARM_GCSR_EXPA_BAR_ADDR((address) >> NFP_ARM_GCSR_EXPA_SHIFT))

#घोषणा NFP_ARM_GCSR_BULK_CSR(mode, target, token, is_64, address) \
	(((mode) ? NFP_ARM_GCSR_BULK_BAR_TYPE_EXPA : \
		   NFP_ARM_GCSR_BULK_BAR_TYPE_BULK) | \
	 NFP_ARM_GCSR_BULK_BAR_TGT(target) | \
	 NFP_ARM_GCSR_BULK_BAR_TOK(token) | \
	 ((is_64) ? NFP_ARM_GCSR_BULK_BAR_LEN_64BIT : \
		    NFP_ARM_GCSR_BULK_BAR_LEN_32BIT) | \
	 NFP_ARM_GCSR_BULK_BAR_ADDR((address) >> NFP_ARM_GCSR_BULK_SHIFT))

	/* MP Core CSRs */
#घोषणा NFP_ARM_MPCORE_SIZE	SZ_128K

	/* PL320 CSRs */
#घोषणा NFP_ARM_PCSR_SIZE	SZ_64K

#पूर्ण_अगर /* NFP_ARM_H */
