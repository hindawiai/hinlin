<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#अगर_अघोषित __QLCNIC_HDR_H_
#घोषणा __QLCNIC_HDR_H_

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश "qlcnic_hw.h"

/*
 * The basic unit of access when पढ़ोing/writing control रेजिस्टरs.
 */

क्रमागत अणु
	QLCNIC_HW_H0_CH_HUB_ADR = 0x05,
	QLCNIC_HW_H1_CH_HUB_ADR = 0x0E,
	QLCNIC_HW_H2_CH_HUB_ADR = 0x03,
	QLCNIC_HW_H3_CH_HUB_ADR = 0x01,
	QLCNIC_HW_H4_CH_HUB_ADR = 0x06,
	QLCNIC_HW_H5_CH_HUB_ADR = 0x07,
	QLCNIC_HW_H6_CH_HUB_ADR = 0x08
पूर्ण;

/*  Hub 0 */
क्रमागत अणु
	QLCNIC_HW_MN_CRB_AGT_ADR = 0x15,
	QLCNIC_HW_MS_CRB_AGT_ADR = 0x25
पूर्ण;

/*  Hub 1 */
क्रमागत अणु
	QLCNIC_HW_PS_CRB_AGT_ADR = 0x73,
	QLCNIC_HW_SS_CRB_AGT_ADR = 0x20,
	QLCNIC_HW_RPMX3_CRB_AGT_ADR = 0x0b,
	QLCNIC_HW_QMS_CRB_AGT_ADR = 0x00,
	QLCNIC_HW_SQGS0_CRB_AGT_ADR = 0x01,
	QLCNIC_HW_SQGS1_CRB_AGT_ADR = 0x02,
	QLCNIC_HW_SQGS2_CRB_AGT_ADR = 0x03,
	QLCNIC_HW_SQGS3_CRB_AGT_ADR = 0x04,
	QLCNIC_HW_C2C0_CRB_AGT_ADR = 0x58,
	QLCNIC_HW_C2C1_CRB_AGT_ADR = 0x59,
	QLCNIC_HW_C2C2_CRB_AGT_ADR = 0x5a,
	QLCNIC_HW_RPMX2_CRB_AGT_ADR = 0x0a,
	QLCNIC_HW_RPMX4_CRB_AGT_ADR = 0x0c,
	QLCNIC_HW_RPMX7_CRB_AGT_ADR = 0x0f,
	QLCNIC_HW_RPMX9_CRB_AGT_ADR = 0x12,
	QLCNIC_HW_SMB_CRB_AGT_ADR = 0x18
पूर्ण;

/*  Hub 2 */
क्रमागत अणु
	QLCNIC_HW_NIU_CRB_AGT_ADR = 0x31,
	QLCNIC_HW_I2C0_CRB_AGT_ADR = 0x19,
	QLCNIC_HW_I2C1_CRB_AGT_ADR = 0x29,

	QLCNIC_HW_SN_CRB_AGT_ADR = 0x10,
	QLCNIC_HW_I2Q_CRB_AGT_ADR = 0x20,
	QLCNIC_HW_LPC_CRB_AGT_ADR = 0x22,
	QLCNIC_HW_ROMUSB_CRB_AGT_ADR = 0x21,
	QLCNIC_HW_QM_CRB_AGT_ADR = 0x66,
	QLCNIC_HW_SQG0_CRB_AGT_ADR = 0x60,
	QLCNIC_HW_SQG1_CRB_AGT_ADR = 0x61,
	QLCNIC_HW_SQG2_CRB_AGT_ADR = 0x62,
	QLCNIC_HW_SQG3_CRB_AGT_ADR = 0x63,
	QLCNIC_HW_RPMX1_CRB_AGT_ADR = 0x09,
	QLCNIC_HW_RPMX5_CRB_AGT_ADR = 0x0d,
	QLCNIC_HW_RPMX6_CRB_AGT_ADR = 0x0e,
	QLCNIC_HW_RPMX8_CRB_AGT_ADR = 0x11
पूर्ण;

/*  Hub 3 */
क्रमागत अणु
	QLCNIC_HW_PH_CRB_AGT_ADR = 0x1A,
	QLCNIC_HW_SRE_CRB_AGT_ADR = 0x50,
	QLCNIC_HW_EG_CRB_AGT_ADR = 0x51,
	QLCNIC_HW_RPMX0_CRB_AGT_ADR = 0x08
पूर्ण;

/*  Hub 4 */
क्रमागत अणु
	QLCNIC_HW_PEGN0_CRB_AGT_ADR = 0x40,
	QLCNIC_HW_PEGN1_CRB_AGT_ADR,
	QLCNIC_HW_PEGN2_CRB_AGT_ADR,
	QLCNIC_HW_PEGN3_CRB_AGT_ADR,
	QLCNIC_HW_PEGNI_CRB_AGT_ADR,
	QLCNIC_HW_PEGND_CRB_AGT_ADR,
	QLCNIC_HW_PEGNC_CRB_AGT_ADR,
	QLCNIC_HW_PEGR0_CRB_AGT_ADR,
	QLCNIC_HW_PEGR1_CRB_AGT_ADR,
	QLCNIC_HW_PEGR2_CRB_AGT_ADR,
	QLCNIC_HW_PEGR3_CRB_AGT_ADR,
	QLCNIC_HW_PEGN4_CRB_AGT_ADR
पूर्ण;

/*  Hub 5 */
क्रमागत अणु
	QLCNIC_HW_PEGS0_CRB_AGT_ADR = 0x40,
	QLCNIC_HW_PEGS1_CRB_AGT_ADR,
	QLCNIC_HW_PEGS2_CRB_AGT_ADR,
	QLCNIC_HW_PEGS3_CRB_AGT_ADR,
	QLCNIC_HW_PEGSI_CRB_AGT_ADR,
	QLCNIC_HW_PEGSD_CRB_AGT_ADR,
	QLCNIC_HW_PEGSC_CRB_AGT_ADR
पूर्ण;

/*  Hub 6 */
क्रमागत अणु
	QLCNIC_HW_CAS0_CRB_AGT_ADR = 0x46,
	QLCNIC_HW_CAS1_CRB_AGT_ADR = 0x47,
	QLCNIC_HW_CAS2_CRB_AGT_ADR = 0x48,
	QLCNIC_HW_CAS3_CRB_AGT_ADR = 0x49,
	QLCNIC_HW_NCM_CRB_AGT_ADR = 0x16,
	QLCNIC_HW_TMR_CRB_AGT_ADR = 0x17,
	QLCNIC_HW_XDMA_CRB_AGT_ADR = 0x05,
	QLCNIC_HW_OCM0_CRB_AGT_ADR = 0x06,
	QLCNIC_HW_OCM1_CRB_AGT_ADR = 0x07
पूर्ण;

/*  Floaters - non existent modules */
#घोषणा QLCNIC_HW_EFC_RPMX0_CRB_AGT_ADR	0x67

/*  This field defines PCI/X adr [25:20] of agents on the CRB */
क्रमागत अणु
	QLCNIC_HW_PX_MAP_CRB_PH = 0,
	QLCNIC_HW_PX_MAP_CRB_PS,
	QLCNIC_HW_PX_MAP_CRB_MN,
	QLCNIC_HW_PX_MAP_CRB_MS,
	QLCNIC_HW_PX_MAP_CRB_PGR1,
	QLCNIC_HW_PX_MAP_CRB_SRE,
	QLCNIC_HW_PX_MAP_CRB_NIU,
	QLCNIC_HW_PX_MAP_CRB_QMN,
	QLCNIC_HW_PX_MAP_CRB_SQN0,
	QLCNIC_HW_PX_MAP_CRB_SQN1,
	QLCNIC_HW_PX_MAP_CRB_SQN2,
	QLCNIC_HW_PX_MAP_CRB_SQN3,
	QLCNIC_HW_PX_MAP_CRB_QMS,
	QLCNIC_HW_PX_MAP_CRB_SQS0,
	QLCNIC_HW_PX_MAP_CRB_SQS1,
	QLCNIC_HW_PX_MAP_CRB_SQS2,
	QLCNIC_HW_PX_MAP_CRB_SQS3,
	QLCNIC_HW_PX_MAP_CRB_PGN0,
	QLCNIC_HW_PX_MAP_CRB_PGN1,
	QLCNIC_HW_PX_MAP_CRB_PGN2,
	QLCNIC_HW_PX_MAP_CRB_PGN3,
	QLCNIC_HW_PX_MAP_CRB_PGND,
	QLCNIC_HW_PX_MAP_CRB_PGNI,
	QLCNIC_HW_PX_MAP_CRB_PGS0,
	QLCNIC_HW_PX_MAP_CRB_PGS1,
	QLCNIC_HW_PX_MAP_CRB_PGS2,
	QLCNIC_HW_PX_MAP_CRB_PGS3,
	QLCNIC_HW_PX_MAP_CRB_PGSD,
	QLCNIC_HW_PX_MAP_CRB_PGSI,
	QLCNIC_HW_PX_MAP_CRB_SN,
	QLCNIC_HW_PX_MAP_CRB_PGR2,
	QLCNIC_HW_PX_MAP_CRB_EG,
	QLCNIC_HW_PX_MAP_CRB_PH2,
	QLCNIC_HW_PX_MAP_CRB_PS2,
	QLCNIC_HW_PX_MAP_CRB_CAM,
	QLCNIC_HW_PX_MAP_CRB_CAS0,
	QLCNIC_HW_PX_MAP_CRB_CAS1,
	QLCNIC_HW_PX_MAP_CRB_CAS2,
	QLCNIC_HW_PX_MAP_CRB_C2C0,
	QLCNIC_HW_PX_MAP_CRB_C2C1,
	QLCNIC_HW_PX_MAP_CRB_TIMR,
	QLCNIC_HW_PX_MAP_CRB_PGR3,
	QLCNIC_HW_PX_MAP_CRB_RPMX1,
	QLCNIC_HW_PX_MAP_CRB_RPMX2,
	QLCNIC_HW_PX_MAP_CRB_RPMX3,
	QLCNIC_HW_PX_MAP_CRB_RPMX4,
	QLCNIC_HW_PX_MAP_CRB_RPMX5,
	QLCNIC_HW_PX_MAP_CRB_RPMX6,
	QLCNIC_HW_PX_MAP_CRB_RPMX7,
	QLCNIC_HW_PX_MAP_CRB_XDMA,
	QLCNIC_HW_PX_MAP_CRB_I2Q,
	QLCNIC_HW_PX_MAP_CRB_ROMUSB,
	QLCNIC_HW_PX_MAP_CRB_CAS3,
	QLCNIC_HW_PX_MAP_CRB_RPMX0,
	QLCNIC_HW_PX_MAP_CRB_RPMX8,
	QLCNIC_HW_PX_MAP_CRB_RPMX9,
	QLCNIC_HW_PX_MAP_CRB_OCM0,
	QLCNIC_HW_PX_MAP_CRB_OCM1,
	QLCNIC_HW_PX_MAP_CRB_SMB,
	QLCNIC_HW_PX_MAP_CRB_I2C0,
	QLCNIC_HW_PX_MAP_CRB_I2C1,
	QLCNIC_HW_PX_MAP_CRB_LPC,
	QLCNIC_HW_PX_MAP_CRB_PGNC,
	QLCNIC_HW_PX_MAP_CRB_PGR0
पूर्ण;

#घोषणा	BIT_0	0x1
#घोषणा	BIT_1	0x2
#घोषणा	BIT_2	0x4
#घोषणा	BIT_3	0x8
#घोषणा	BIT_4	0x10
#घोषणा	BIT_5	0x20
#घोषणा	BIT_6	0x40
#घोषणा	BIT_7	0x80
#घोषणा	BIT_8	0x100
#घोषणा	BIT_9	0x200
#घोषणा	BIT_10	0x400
#घोषणा	BIT_11	0x800
#घोषणा	BIT_12	0x1000
#घोषणा	BIT_13	0x2000
#घोषणा	BIT_14	0x4000
#घोषणा	BIT_15	0x8000
#घोषणा	BIT_16	0x10000
#घोषणा	BIT_17	0x20000
#घोषणा	BIT_18	0x40000
#घोषणा	BIT_19	0x80000
#घोषणा	BIT_20	0x100000
#घोषणा	BIT_21	0x200000
#घोषणा	BIT_22	0x400000
#घोषणा	BIT_23	0x800000
#घोषणा	BIT_24	0x1000000
#घोषणा	BIT_25	0x2000000
#घोषणा	BIT_26	0x4000000
#घोषणा	BIT_27	0x8000000
#घोषणा	BIT_28	0x10000000
#घोषणा	BIT_29	0x20000000
#घोषणा	BIT_30	0x40000000
#घोषणा	BIT_31	0x80000000

/*  This field defines CRB adr [31:20] of the agents */

#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_MN	\
	((QLCNIC_HW_H0_CH_HUB_ADR << 7) | QLCNIC_HW_MN_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PH	\
	((QLCNIC_HW_H0_CH_HUB_ADR << 7) | QLCNIC_HW_PH_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_MS	\
	((QLCNIC_HW_H0_CH_HUB_ADR << 7) | QLCNIC_HW_MS_CRB_AGT_ADR)

#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PS	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_PS_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_SS	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_SS_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX3	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_RPMX3_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_QMS	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_QMS_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_SQS0	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_SQGS0_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_SQS1	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_SQGS1_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_SQS2	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_SQGS2_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_SQS3	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_SQGS3_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_C2C0	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_C2C0_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_C2C1	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_C2C1_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX2	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_RPMX2_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX4	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_RPMX4_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX7	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_RPMX7_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX9	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_RPMX9_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_SMB	\
	((QLCNIC_HW_H1_CH_HUB_ADR << 7) | QLCNIC_HW_SMB_CRB_AGT_ADR)

#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_NIU	\
	((QLCNIC_HW_H2_CH_HUB_ADR << 7) | QLCNIC_HW_NIU_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_I2C0	\
	((QLCNIC_HW_H2_CH_HUB_ADR << 7) | QLCNIC_HW_I2C0_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_I2C1	\
	((QLCNIC_HW_H2_CH_HUB_ADR << 7) | QLCNIC_HW_I2C1_CRB_AGT_ADR)

#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_SRE	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_SRE_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_EG	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_EG_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX0	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_RPMX0_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_QMN	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_QM_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_SQN0	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_SQG0_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_SQN1	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_SQG1_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_SQN2	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_SQG2_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_SQN3	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_SQG3_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX1	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_RPMX1_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX5	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_RPMX5_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX6	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_RPMX6_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_RPMX8	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_RPMX8_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_CAS0	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_CAS0_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_CAS1	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_CAS1_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_CAS2	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_CAS2_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_CAS3	\
	((QLCNIC_HW_H3_CH_HUB_ADR << 7) | QLCNIC_HW_CAS3_CRB_AGT_ADR)

#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGNI	\
	((QLCNIC_HW_H4_CH_HUB_ADR << 7) | QLCNIC_HW_PEGNI_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGND	\
	((QLCNIC_HW_H4_CH_HUB_ADR << 7) | QLCNIC_HW_PEGND_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGN0	\
	((QLCNIC_HW_H4_CH_HUB_ADR << 7) | QLCNIC_HW_PEGN0_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGN1	\
	((QLCNIC_HW_H4_CH_HUB_ADR << 7) | QLCNIC_HW_PEGN1_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGN2	\
	((QLCNIC_HW_H4_CH_HUB_ADR << 7) | QLCNIC_HW_PEGN2_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGN3	\
	((QLCNIC_HW_H4_CH_HUB_ADR << 7) | QLCNIC_HW_PEGN3_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGN4	\
	((QLCNIC_HW_H4_CH_HUB_ADR << 7) | QLCNIC_HW_PEGN4_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGNC	\
	((QLCNIC_HW_H4_CH_HUB_ADR << 7) | QLCNIC_HW_PEGNC_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGR0	\
	((QLCNIC_HW_H4_CH_HUB_ADR << 7) | QLCNIC_HW_PEGR0_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGR1	\
	((QLCNIC_HW_H4_CH_HUB_ADR << 7) | QLCNIC_HW_PEGR1_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGR2	\
	((QLCNIC_HW_H4_CH_HUB_ADR << 7) | QLCNIC_HW_PEGR2_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGR3	\
	((QLCNIC_HW_H4_CH_HUB_ADR << 7) | QLCNIC_HW_PEGR3_CRB_AGT_ADR)

#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGSI	\
	((QLCNIC_HW_H5_CH_HUB_ADR << 7) | QLCNIC_HW_PEGSI_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGSD	\
	((QLCNIC_HW_H5_CH_HUB_ADR << 7) | QLCNIC_HW_PEGSD_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGS0	\
	((QLCNIC_HW_H5_CH_HUB_ADR << 7) | QLCNIC_HW_PEGS0_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGS1	\
	((QLCNIC_HW_H5_CH_HUB_ADR << 7) | QLCNIC_HW_PEGS1_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGS2	\
	((QLCNIC_HW_H5_CH_HUB_ADR << 7) | QLCNIC_HW_PEGS2_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGS3	\
	((QLCNIC_HW_H5_CH_HUB_ADR << 7) | QLCNIC_HW_PEGS3_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_PGSC	\
	((QLCNIC_HW_H5_CH_HUB_ADR << 7) | QLCNIC_HW_PEGSC_CRB_AGT_ADR)

#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_CAM	\
	((QLCNIC_HW_H6_CH_HUB_ADR << 7) | QLCNIC_HW_NCM_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_TIMR	\
	((QLCNIC_HW_H6_CH_HUB_ADR << 7) | QLCNIC_HW_TMR_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_XDMA	\
	((QLCNIC_HW_H6_CH_HUB_ADR << 7) | QLCNIC_HW_XDMA_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_SN	\
	((QLCNIC_HW_H6_CH_HUB_ADR << 7) | QLCNIC_HW_SN_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_I2Q	\
	((QLCNIC_HW_H6_CH_HUB_ADR << 7) | QLCNIC_HW_I2Q_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_ROMUSB	\
	((QLCNIC_HW_H6_CH_HUB_ADR << 7) | QLCNIC_HW_ROMUSB_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_OCM0	\
	((QLCNIC_HW_H6_CH_HUB_ADR << 7) | QLCNIC_HW_OCM0_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_OCM1	\
	((QLCNIC_HW_H6_CH_HUB_ADR << 7) | QLCNIC_HW_OCM1_CRB_AGT_ADR)
#घोषणा QLCNIC_HW_CRB_HUB_AGT_ADR_LPC	\
	((QLCNIC_HW_H6_CH_HUB_ADR << 7) | QLCNIC_HW_LPC_CRB_AGT_ADR)

#घोषणा QLCNIC_SRE_MISC		(QLCNIC_CRB_SRE + 0x0002c)

#घोषणा QLCNIC_I2Q_CLR_PCI_HI	(QLCNIC_CRB_I2Q + 0x00034)

#घोषणा ROMUSB_GLB		(QLCNIC_CRB_ROMUSB + 0x00000)
#घोषणा ROMUSB_ROM		(QLCNIC_CRB_ROMUSB + 0x10000)

#घोषणा QLCNIC_ROMUSB_GLB_STATUS	(ROMUSB_GLB + 0x0004)
#घोषणा QLCNIC_ROMUSB_GLB_SW_RESET	(ROMUSB_GLB + 0x0008)
#घोषणा QLCNIC_ROMUSB_GLB_PAD_GPIO_I	(ROMUSB_GLB + 0x000c)
#घोषणा QLCNIC_ROMUSB_GLB_CAS_RST	(ROMUSB_GLB + 0x0038)
#घोषणा QLCNIC_ROMUSB_GLB_TEST_MUX_SEL	(ROMUSB_GLB + 0x0044)
#घोषणा QLCNIC_ROMUSB_GLB_PEGTUNE_DONE	(ROMUSB_GLB + 0x005c)
#घोषणा QLCNIC_ROMUSB_GLB_CHIP_CLK_CTRL	(ROMUSB_GLB + 0x00A8)

#घोषणा QLCNIC_ROMUSB_GPIO(n)		(ROMUSB_GLB + 0x60 + (4 * (n)))

#घोषणा QLCNIC_ROMUSB_ROM_INSTR_OPCODE	(ROMUSB_ROM + 0x0004)
#घोषणा QLCNIC_ROMUSB_ROM_ADDRESS	(ROMUSB_ROM + 0x0008)
#घोषणा QLCNIC_ROMUSB_ROM_WDATA		(ROMUSB_ROM + 0x000c)
#घोषणा QLCNIC_ROMUSB_ROM_ABYTE_CNT	(ROMUSB_ROM + 0x0010)
#घोषणा QLCNIC_ROMUSB_ROM_DUMMY_BYTE_CNT (ROMUSB_ROM + 0x0014)
#घोषणा QLCNIC_ROMUSB_ROM_RDATA		(ROMUSB_ROM + 0x0018)

/******************************************************************************
*
*    Definitions specअगरic to M25P flash
*
*******************************************************************************
*/

/* all are 1MB winकरोws */

#घोषणा QLCNIC_PCI_CRB_WINDOWSIZE	0x00100000
#घोषणा QLCNIC_PCI_CRB_WINDOW(A)	\
	(QLCNIC_PCI_CRBSPACE + (A)*QLCNIC_PCI_CRB_WINDOWSIZE)

#घोषणा QLCNIC_CRB_NIU		QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_NIU)
#घोषणा QLCNIC_CRB_SRE		QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_SRE)
#घोषणा QLCNIC_CRB_ROMUSB	\
	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_ROMUSB)
#घोषणा QLCNIC_CRB_EPG		QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_EG)
#घोषणा QLCNIC_CRB_I2Q		QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_I2Q)
#घोषणा QLCNIC_CRB_TIMER	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_TIMR)
#घोषणा QLCNIC_CRB_I2C0 	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_I2C0)
#घोषणा QLCNIC_CRB_SMB		QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_SMB)
#घोषणा QLCNIC_CRB_MAX		QLCNIC_PCI_CRB_WINDOW(64)

#घोषणा QLCNIC_CRB_PCIX_HOST	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_PH)
#घोषणा QLCNIC_CRB_PCIX_HOST2	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_PH2)
#घोषणा QLCNIC_CRB_PEG_NET_0	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_PGN0)
#घोषणा QLCNIC_CRB_PEG_NET_1	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_PGN1)
#घोषणा QLCNIC_CRB_PEG_NET_2	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_PGN2)
#घोषणा QLCNIC_CRB_PEG_NET_3	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_PGN3)
#घोषणा QLCNIC_CRB_PEG_NET_4	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_SQS2)
#घोषणा QLCNIC_CRB_PEG_NET_D	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_PGND)
#घोषणा QLCNIC_CRB_PEG_NET_I	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_PGNI)
#घोषणा QLCNIC_CRB_DDR_NET	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_MN)
#घोषणा QLCNIC_CRB_QDR_NET	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_SN)

#घोषणा QLCNIC_CRB_PCIX_MD	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_PS)
#घोषणा QLCNIC_CRB_PCIE 	QLCNIC_CRB_PCIX_MD

#घोषणा ISR_INT_VECTOR		(QLCNIC_PCIX_PS_REG(PCIX_INT_VECTOR))
#घोषणा ISR_INT_MASK		(QLCNIC_PCIX_PS_REG(PCIX_INT_MASK))
#घोषणा ISR_INT_MASK_SLOW	(QLCNIC_PCIX_PS_REG(PCIX_INT_MASK))
#घोषणा ISR_INT_TARGET_STATUS	(QLCNIC_PCIX_PS_REG(PCIX_TARGET_STATUS))
#घोषणा ISR_INT_TARGET_MASK	(QLCNIC_PCIX_PS_REG(PCIX_TARGET_MASK))
#घोषणा ISR_INT_TARGET_STATUS_F1   (QLCNIC_PCIX_PS_REG(PCIX_TARGET_STATUS_F1))
#घोषणा ISR_INT_TARGET_MASK_F1     (QLCNIC_PCIX_PS_REG(PCIX_TARGET_MASK_F1))
#घोषणा ISR_INT_TARGET_STATUS_F2   (QLCNIC_PCIX_PS_REG(PCIX_TARGET_STATUS_F2))
#घोषणा ISR_INT_TARGET_MASK_F2     (QLCNIC_PCIX_PS_REG(PCIX_TARGET_MASK_F2))
#घोषणा ISR_INT_TARGET_STATUS_F3   (QLCNIC_PCIX_PS_REG(PCIX_TARGET_STATUS_F3))
#घोषणा ISR_INT_TARGET_MASK_F3     (QLCNIC_PCIX_PS_REG(PCIX_TARGET_MASK_F3))
#घोषणा ISR_INT_TARGET_STATUS_F4   (QLCNIC_PCIX_PS_REG(PCIX_TARGET_STATUS_F4))
#घोषणा ISR_INT_TARGET_MASK_F4     (QLCNIC_PCIX_PS_REG(PCIX_TARGET_MASK_F4))
#घोषणा ISR_INT_TARGET_STATUS_F5   (QLCNIC_PCIX_PS_REG(PCIX_TARGET_STATUS_F5))
#घोषणा ISR_INT_TARGET_MASK_F5     (QLCNIC_PCIX_PS_REG(PCIX_TARGET_MASK_F5))
#घोषणा ISR_INT_TARGET_STATUS_F6   (QLCNIC_PCIX_PS_REG(PCIX_TARGET_STATUS_F6))
#घोषणा ISR_INT_TARGET_MASK_F6     (QLCNIC_PCIX_PS_REG(PCIX_TARGET_MASK_F6))
#घोषणा ISR_INT_TARGET_STATUS_F7   (QLCNIC_PCIX_PS_REG(PCIX_TARGET_STATUS_F7))
#घोषणा ISR_INT_TARGET_MASK_F7     (QLCNIC_PCIX_PS_REG(PCIX_TARGET_MASK_F7))

#घोषणा QLCNIC_PCI_OCM0_2M	(0x000c0000UL)
#घोषणा QLCNIC_PCI_CRBSPACE	(0x06000000UL)
#घोषणा QLCNIC_PCI_CAMQM	(0x04800000UL)
#घोषणा QLCNIC_PCI_CAMQM_END	(0x04800800UL)
#घोषणा QLCNIC_PCI_CAMQM_2M_BASE	(0x000ff800UL)

#घोषणा QLCNIC_CRB_CAM	QLCNIC_PCI_CRB_WINDOW(QLCNIC_HW_PX_MAP_CRB_CAM)

#घोषणा QLCNIC_ADDR_DDR_NET	(0x0000000000000000ULL)
#घोषणा QLCNIC_ADDR_DDR_NET_MAX (0x000000000fffffffULL)
#घोषणा QLCNIC_ADDR_OCM0	(0x0000000200000000ULL)
#घोषणा QLCNIC_ADDR_OCM0_MAX	(0x00000002000fffffULL)
#घोषणा QLCNIC_ADDR_OCM1	(0x0000000200400000ULL)
#घोषणा QLCNIC_ADDR_OCM1_MAX	(0x00000002004fffffULL)
#घोषणा QLCNIC_ADDR_QDR_NET	(0x0000000300000000ULL)
#घोषणा QLCNIC_ADDR_QDR_NET_MAX (0x0000000307ffffffULL)

/*
 *   Register offsets क्रम MN
 */
#घोषणा QLCNIC_MIU_CONTROL	(0x000)
#घोषणा QLCNIC_MIU_MN_CONTROL	(QLCNIC_CRB_DDR_NET+QLCNIC_MIU_CONTROL)

/* 200ms delay in each loop */
#घोषणा QLCNIC_NIU_PHY_WAITLEN		200000
/* 10 seconds beक्रमe we give up */
#घोषणा QLCNIC_NIU_PHY_WAITMAX		50
#घोषणा QLCNIC_NIU_MAX_GBE_PORTS	4
#घोषणा QLCNIC_NIU_MAX_XG_PORTS		2

#घोषणा QLCNIC_NIU_MODE			(QLCNIC_CRB_NIU + 0x00000)
#घोषणा QLCNIC_NIU_GB_PAUSE_CTL		(QLCNIC_CRB_NIU + 0x0030c)
#घोषणा QLCNIC_NIU_XG_PAUSE_CTL		(QLCNIC_CRB_NIU + 0x00098)

#घोषणा QLCNIC_NIU_GB_MAC_CONFIG_0(I)		\
		(QLCNIC_CRB_NIU + 0x30000 + (I)*0x10000)
#घोषणा QLCNIC_NIU_GB_MAC_CONFIG_1(I)		\
		(QLCNIC_CRB_NIU + 0x30004 + (I)*0x10000)

#घोषणा MAX_CTL_CHECK	1000
#घोषणा TEST_AGT_CTRL	(0x00)

#घोषणा TA_CTL_START	BIT_0
#घोषणा TA_CTL_ENABLE	BIT_1
#घोषणा TA_CTL_WRITE	BIT_2
#घोषणा TA_CTL_BUSY	BIT_3

/* XG Link status */
#घोषणा XG_LINK_UP	0x10
#घोषणा XG_LINK_DOWN	0x20

#घोषणा XG_LINK_UP_P3P	0x01
#घोषणा XG_LINK_DOWN_P3P	0x02
#घोषणा XG_LINK_STATE_P3P_MASK 0xf
#घोषणा XG_LINK_STATE_P3P(pcअगरn, val) \
	(((val) >> ((pcअगरn) * 4)) & XG_LINK_STATE_P3P_MASK)

#घोषणा P3P_LINK_SPEED_MHZ	100
#घोषणा P3P_LINK_SPEED_MASK	0xff
#घोषणा P3P_LINK_SPEED_REG(pcअगरn)	\
	(CRB_PF_LINK_SPEED_1 + (((pcअगरn) / 4) * 4))
#घोषणा P3P_LINK_SPEED_VAL(pcअगरn, reg)	\
	(((reg) >> (8 * ((pcअगरn) & 0x3))) & P3P_LINK_SPEED_MASK)

#घोषणा QLCNIC_CAM_RAM_BASE	(QLCNIC_CRB_CAM + 0x02000)
#घोषणा QLCNIC_CAM_RAM(reg)	(QLCNIC_CAM_RAM_BASE + (reg))
#घोषणा QLCNIC_ROM_LOCK_ID	(QLCNIC_CAM_RAM(0x100))
#घोषणा QLCNIC_PHY_LOCK_ID	(QLCNIC_CAM_RAM(0x120))
#घोषणा QLCNIC_CRB_WIN_LOCK_ID	(QLCNIC_CAM_RAM(0x124))

#घोषणा NIC_CRB_BASE		(QLCNIC_CAM_RAM(0x200))
#घोषणा NIC_CRB_BASE_2		(QLCNIC_CAM_RAM(0x700))
#घोषणा QLCNIC_REG(X)		(NIC_CRB_BASE+(X))
#घोषणा QLCNIC_REG_2(X) 	(NIC_CRB_BASE_2+(X))

#घोषणा QLCNIC_CDRP_MAX_ARGS	4
#घोषणा QLCNIC_CDRP_ARG(i)	(QLCNIC_REG(0x18 + ((i) * 4)))

#घोषणा QLCNIC_CDRP_CRB_OFFSET		(QLCNIC_REG(0x18))
#घोषणा QLCNIC_SIGN_CRB_OFFSET		(QLCNIC_REG(0x28))

#घोषणा CRB_XG_STATE_P3P		(QLCNIC_REG(0x98))
#घोषणा CRB_PF_LINK_SPEED_1		(QLCNIC_REG(0xe8))
#घोषणा CRB_DRIVER_VERSION		(QLCNIC_REG(0x2a0))

#घोषणा CRB_FW_CAPABILITIES_2		(QLCNIC_CAM_RAM(0x12c))

/*
 * CrbPortPhanCntrHi/Lo is used to pass the address of HostPhantomIndex address
 * which can be पढ़ो by the Phantom host to get producer/consumer indexes from
 * Phantom/Casper. If it is not HOST_SHARED_MEMORY, then the following
 * रेजिस्टरs will be used क्रम the addresses of the ring's shared memory
 * on the Phantom.
 */

#घोषणा qlcnic_get_temp_val(x)		((x) >> 16)
#घोषणा qlcnic_get_temp_state(x)	((x) & 0xffff)
#घोषणा qlcnic_encode_temp(val, state)	(((val) << 16) | (state))

/*
 * Temperature control.
 */
क्रमागत अणु
	QLCNIC_TEMP_NORMAL = 0x1,	/* Normal operating range */
	QLCNIC_TEMP_WARN,	/* Sound alert, temperature getting high */
	QLCNIC_TEMP_PANIC	/* Fatal error, hardware has shut करोwn. */
पूर्ण;


/* Lock IDs क्रम PHY lock */
#घोषणा PHY_LOCK_DRIVER		0x44524956

#घोषणा PCIX_INT_VECTOR 	(0x10100)
#घोषणा PCIX_INT_MASK		(0x10104)

#घोषणा PCIX_OCM_WINDOW		(0x10800)
#घोषणा PCIX_OCM_WINDOW_REG(func)	(PCIX_OCM_WINDOW + 0x4 * (func))

#घोषणा PCIX_TARGET_STATUS	(0x10118)
#घोषणा PCIX_TARGET_STATUS_F1	(0x10160)
#घोषणा PCIX_TARGET_STATUS_F2	(0x10164)
#घोषणा PCIX_TARGET_STATUS_F3	(0x10168)
#घोषणा PCIX_TARGET_STATUS_F4	(0x10360)
#घोषणा PCIX_TARGET_STATUS_F5	(0x10364)
#घोषणा PCIX_TARGET_STATUS_F6	(0x10368)
#घोषणा PCIX_TARGET_STATUS_F7	(0x1036c)

#घोषणा PCIX_TARGET_MASK	(0x10128)
#घोषणा PCIX_TARGET_MASK_F1	(0x10170)
#घोषणा PCIX_TARGET_MASK_F2	(0x10174)
#घोषणा PCIX_TARGET_MASK_F3	(0x10178)
#घोषणा PCIX_TARGET_MASK_F4	(0x10370)
#घोषणा PCIX_TARGET_MASK_F5	(0x10374)
#घोषणा PCIX_TARGET_MASK_F6	(0x10378)
#घोषणा PCIX_TARGET_MASK_F7	(0x1037c)

#घोषणा PCIX_MSI_F(i)		(0x13000+((i)*4))

#घोषणा QLCNIC_PCIX_PH_REG(reg)	(QLCNIC_CRB_PCIE + (reg))
#घोषणा QLCNIC_PCIX_PS_REG(reg)	(QLCNIC_CRB_PCIX_MD + (reg))
#घोषणा QLCNIC_PCIE_REG(reg)	(QLCNIC_CRB_PCIE + (reg))

#घोषणा PCIE_SEM0_LOCK		(0x1c000)
#घोषणा PCIE_SEM0_UNLOCK	(0x1c004)
#घोषणा PCIE_SEM_LOCK(N)	(PCIE_SEM0_LOCK + 8*(N))
#घोषणा PCIE_SEM_UNLOCK(N)	(PCIE_SEM0_UNLOCK + 8*(N))

#घोषणा PCIE_SETUP_FUNCTION	(0x12040)
#घोषणा PCIE_SETUP_FUNCTION2	(0x12048)
#घोषणा PCIE_MISCCFG_RC         (0x1206c)
#घोषणा PCIE_TGT_SPLIT_CHICKEN	(0x12080)
#घोषणा PCIE_CHICKEN3		(0x120c8)

#घोषणा ISR_INT_STATE_REG       (QLCNIC_PCIX_PS_REG(PCIE_MISCCFG_RC))
#घोषणा PCIE_MAX_MASTER_SPLIT	(0x14048)

#घोषणा QLCNIC_PORT_MODE_NONE		0
#घोषणा QLCNIC_PORT_MODE_XG		1
#घोषणा QLCNIC_PORT_MODE_GB		2
#घोषणा QLCNIC_PORT_MODE_802_3_AP	3
#घोषणा QLCNIC_PORT_MODE_AUTO_NEG	4
#घोषणा QLCNIC_PORT_MODE_AUTO_NEG_1G	5
#घोषणा QLCNIC_PORT_MODE_AUTO_NEG_XG	6
#घोषणा QLCNIC_PORT_MODE_ADDR		(QLCNIC_CAM_RAM(0x24))
#घोषणा QLCNIC_WOL_PORT_MODE		(QLCNIC_CAM_RAM(0x198))

#घोषणा QLCNIC_WOL_CONFIG_NV		(QLCNIC_CAM_RAM(0x184))
#घोषणा QLCNIC_WOL_CONFIG		(QLCNIC_CAM_RAM(0x188))

#घोषणा QLCNIC_PEG_TUNE_MN_PRESENT	0x1
#घोषणा QLCNIC_PEG_TUNE_CAPABILITY	(QLCNIC_CAM_RAM(0x02c))

#घोषणा QLCNIC_DMA_WATCHDOG_CTRL	(QLCNIC_CAM_RAM(0x14))
#घोषणा QLCNIC_ROM_DEV_INIT_TIMEOUT	(0x3e885c)
#घोषणा QLCNIC_ROM_DRV_RESET_TIMEOUT	(0x3e8860)

/* Device State */
#घोषणा QLCNIC_DEV_COLD			0x1
#घोषणा QLCNIC_DEV_INITIALIZING		0x2
#घोषणा QLCNIC_DEV_READY		0x3
#घोषणा QLCNIC_DEV_NEED_RESET		0x4
#घोषणा QLCNIC_DEV_NEED_QUISCENT	0x5
#घोषणा QLCNIC_DEV_FAILED		0x6
#घोषणा QLCNIC_DEV_QUISCENT		0x7

#घोषणा QLCNIC_DEV_BADBAD		0xbad0bad0

#घोषणा QLCNIC_DEV_NPAR_NON_OPER	0 /* NON Operational */
#घोषणा QLCNIC_DEV_NPAR_OPER		1 /* NPAR Operational */
#घोषणा QLCNIC_DEV_NPAR_OPER_TIMEO	30 /* Operational समय out */

#घोषणा QLC_DEV_SET_REF_CNT(VAL, FN)		((VAL) |= (1 << (FN * 4)))
#घोषणा QLC_DEV_CLR_REF_CNT(VAL, FN)		((VAL) &= ~(1 << (FN * 4)))
#घोषणा QLC_DEV_SET_RST_RDY(VAL, FN)		((VAL) |= (1 << (FN * 4)))
#घोषणा QLC_DEV_SET_QSCNT_RDY(VAL, FN)		((VAL) |= (2 << (FN * 4)))
#घोषणा QLC_DEV_CLR_RST_QSCNT(VAL, FN)		((VAL) &= ~(3 << (FN * 4)))

#घोषणा QLC_DEV_GET_DRV(VAL, FN)		(0xf & ((VAL) >> (FN * 4)))
#घोषणा QLC_DEV_SET_DRV(VAL, FN)		((VAL) << (FN * 4))

#घोषणा QLCNIC_TYPE_NIC		1
#घोषणा QLCNIC_TYPE_FCOE		2
#घोषणा QLCNIC_TYPE_ISCSI		3

#घोषणा QLCNIC_RCODE_DRIVER_INFO		0x20000000
#घोषणा QLCNIC_RCODE_DRIVER_CAN_RELOAD		BIT_30
#घोषणा QLCNIC_RCODE_FATAL_ERROR		BIT_31
#घोषणा QLCNIC_FWERROR_PEGNUM(code)		((code) & 0xff)
#घोषणा QLCNIC_FWERROR_CODE(code)		((code >> 8) & 0x1fffff)
#घोषणा QLCNIC_FWERROR_FAN_FAILURE		0x16

#घोषणा FW_POLL_DELAY		(1 * HZ)
#घोषणा FW_FAIL_THRESH		2

#घोषणा QLCNIC_RESET_TIMEOUT_SECS	10
#घोषणा QLCNIC_INIT_TIMEOUT_SECS	30
#घोषणा QLCNIC_RCVPEG_CHECK_RETRY_COUNT	2000
#घोषणा QLCNIC_RCVPEG_CHECK_DELAY	10
#घोषणा QLCNIC_CMDPEG_CHECK_RETRY_COUNT	60
#घोषणा QLCNIC_CMDPEG_CHECK_DELAY	500
#घोषणा QLCNIC_HEARTBEAT_PERIOD_MSECS	200
#घोषणा QLCNIC_HEARTBEAT_CHECK_RETRY_COUNT	10

#घोषणा QLCNIC_MAX_MC_COUNT		38
#घोषणा QLCNIC_MAX_UC_COUNT		512
#घोषणा QLCNIC_WATCHDOG_TIMEOUTVALUE	5

#घोषणा	ISR_MSI_INT_TRIGGER(FUNC) (QLCNIC_PCIX_PS_REG(PCIX_MSI_F(FUNC)))
#घोषणा ISR_LEGACY_INT_TRIGGERED(VAL)	(((VAL) & 0x300) == 0x200)

/*
 * PCI Interrupt Vector Values.
 */
#घोषणा	PCIX_INT_VECTOR_BIT_F0	0x0080
#घोषणा	PCIX_INT_VECTOR_BIT_F1	0x0100
#घोषणा	PCIX_INT_VECTOR_BIT_F2	0x0200
#घोषणा	PCIX_INT_VECTOR_BIT_F3	0x0400
#घोषणा	PCIX_INT_VECTOR_BIT_F4	0x0800
#घोषणा	PCIX_INT_VECTOR_BIT_F5	0x1000
#घोषणा	PCIX_INT_VECTOR_BIT_F6	0x2000
#घोषणा	PCIX_INT_VECTOR_BIT_F7	0x4000

काष्ठा qlcnic_legacy_पूर्णांकr_set अणु
	u32	पूर्णांक_vec_bit;
	u32	tgt_status_reg;
	u32	tgt_mask_reg;
	u32	pci_पूर्णांक_reg;
पूर्ण;

#घोषणा QLCNIC_MSIX_BASE	0x132110
#घोषणा QLCNIC_MAX_VLAN_FILTERS	64

#घोषणा FLASH_ROM_WINDOW	0x42110030
#घोषणा FLASH_ROM_DATA		0x42150000

#घोषणा QLCNIC_FW_DUMP_REG1	0x00130060
#घोषणा QLCNIC_FW_DUMP_REG2	0x001e0000
#घोषणा QLCNIC_FLASH_SEM2_LK	0x0013C010
#घोषणा QLCNIC_FLASH_SEM2_ULK	0x0013C014
#घोषणा QLCNIC_FLASH_LOCK_ID	0x001B2100

/* PCI function operational mode */
क्रमागत अणु
	QLCNIC_MGMT_FUNC	= 0,
	QLCNIC_PRIV_FUNC	= 1,
	QLCNIC_NON_PRIV_FUNC	= 2,
	QLCNIC_SRIOV_PF_FUNC	= 3,
	QLCNIC_SRIOV_VF_FUNC	= 4,
	QLCNIC_UNKNOWN_FUNC_MODE = 5
पूर्ण;

क्रमागत अणु
	QLCNIC_PORT_DEFAULTS	= 0,
	QLCNIC_ADD_VLAN	= 1,
	QLCNIC_DEL_VLAN	= 2
पूर्ण;

#घोषणा QLC_DEV_DRV_DEFAULT 0x11111111

#घोषणा LSB(x)	((uपूर्णांक8_t)(x))
#घोषणा MSB(x)	((uपूर्णांक8_t)((uपूर्णांक16_t)(x) >> 8))

#घोषणा LSW(x)  ((uपूर्णांक16_t)((uपूर्णांक32_t)(x)))
#घोषणा MSW(x)  ((uपूर्णांक16_t)((uपूर्णांक32_t)(x) >> 16))

#घोषणा LSD(x)  ((uपूर्णांक32_t)((uपूर्णांक64_t)(x)))
#घोषणा MSD(x)  ((uपूर्णांक32_t)((((uपूर्णांक64_t)(x)) >> 16) >> 16))

#घोषणा QLCNIC_MS_CTRL			0x41000090
#घोषणा QLCNIC_MS_ADDR_LO		0x41000094
#घोषणा QLCNIC_MS_ADDR_HI		0x41000098
#घोषणा QLCNIC_MS_WRTDATA_LO		0x410000A0
#घोषणा QLCNIC_MS_WRTDATA_HI		0x410000A4
#घोषणा QLCNIC_MS_WRTDATA_ULO		0x410000B0
#घोषणा QLCNIC_MS_WRTDATA_UHI		0x410000B4
#घोषणा QLCNIC_MS_RDDATA_LO		0x410000A8
#घोषणा QLCNIC_MS_RDDATA_HI		0x410000AC
#घोषणा QLCNIC_MS_RDDATA_ULO		0x410000B8
#घोषणा QLCNIC_MS_RDDATA_UHI		0x410000BC

#घोषणा QLCNIC_TA_WRITE_ENABLE	(TA_CTL_ENABLE | TA_CTL_WRITE)
#घोषणा QLCNIC_TA_WRITE_START	(TA_CTL_START | TA_CTL_ENABLE | TA_CTL_WRITE)
#घोषणा QLCNIC_TA_START_ENABLE	(TA_CTL_START | TA_CTL_ENABLE)

#घोषणा	QLCNIC_LEGACY_INTR_CONFIG					\
अणु									\
	अणु								\
		.पूर्णांक_vec_bit	=	PCIX_INT_VECTOR_BIT_F0,		\
		.tgt_status_reg	=	ISR_INT_TARGET_STATUS,		\
		.tgt_mask_reg	=	ISR_INT_TARGET_MASK, पूर्ण,		\
									\
	अणु								\
		.पूर्णांक_vec_bit	=	PCIX_INT_VECTOR_BIT_F1,		\
		.tgt_status_reg	=	ISR_INT_TARGET_STATUS_F1,	\
		.tgt_mask_reg	=	ISR_INT_TARGET_MASK_F1, पूर्ण,	\
									\
	अणु								\
		.पूर्णांक_vec_bit	=	PCIX_INT_VECTOR_BIT_F2,		\
		.tgt_status_reg	=	ISR_INT_TARGET_STATUS_F2,	\
		.tgt_mask_reg	=	ISR_INT_TARGET_MASK_F2, पूर्ण,	\
									\
	अणु								\
		.पूर्णांक_vec_bit	=	PCIX_INT_VECTOR_BIT_F3,		\
		.tgt_status_reg	=	ISR_INT_TARGET_STATUS_F3,	\
		.tgt_mask_reg	=	ISR_INT_TARGET_MASK_F3, पूर्ण,	\
									\
	अणु								\
		.पूर्णांक_vec_bit	=	PCIX_INT_VECTOR_BIT_F4,		\
		.tgt_status_reg	=	ISR_INT_TARGET_STATUS_F4,	\
		.tgt_mask_reg	=	ISR_INT_TARGET_MASK_F4, पूर्ण,	\
									\
	अणु								\
		.पूर्णांक_vec_bit	=	PCIX_INT_VECTOR_BIT_F5,		\
		.tgt_status_reg	=	ISR_INT_TARGET_STATUS_F5,	\
		.tgt_mask_reg	=	ISR_INT_TARGET_MASK_F5, पूर्ण,	\
									\
	अणु								\
		.पूर्णांक_vec_bit	=	PCIX_INT_VECTOR_BIT_F6,		\
		.tgt_status_reg	=	ISR_INT_TARGET_STATUS_F6,	\
		.tgt_mask_reg	=	ISR_INT_TARGET_MASK_F6, पूर्ण,	\
									\
	अणु								\
		.पूर्णांक_vec_bit	=	PCIX_INT_VECTOR_BIT_F7,		\
		.tgt_status_reg	=	ISR_INT_TARGET_STATUS_F7,	\
		.tgt_mask_reg	=	ISR_INT_TARGET_MASK_F7, पूर्ण,	\
पूर्ण

/* NIU REGS */

#घोषणा _qlcnic_crb_get_bit(var, bit)  ((var >> bit) & 0x1)

/*
 * NIU GB MAC Config Register 0 (applies to GB0, GB1, GB2, GB3)
 *
 *	Bit 0 : enable_tx => 1:enable frame xmit, 0:disable
 *	Bit 1 : tx_synced => R/O: xmit enable synched to xmit stream
 *	Bit 2 : enable_rx => 1:enable frame recv, 0:disable
 *	Bit 3 : rx_synced => R/O: recv enable synched to recv stream
 *	Bit 4 : tx_flowctl => 1:enable छोड़ो frame generation, 0:disable
 *	Bit 5 : rx_flowctl => 1:act on recv'd छोड़ो frames, 0:ignore
 *	Bit 8 : loopback => 1:loop MAC xmits to MAC recvs, 0:normal
 *	Bit 16: tx_reset_pb => 1:reset frame xmit protocol blk, 0:no-op
 *	Bit 17: rx_reset_pb => 1:reset frame recv protocol blk, 0:no-op
 *	Bit 18: tx_reset_mac => 1:reset data/ctl multiplexer blk, 0:no-op
 *	Bit 19: rx_reset_mac => 1:reset ctl frames & समयrs blk, 0:no-op
 *	Bit 31: soft_reset => 1:reset the MAC and the SERDES, 0:no-op
 */
#घोषणा qlcnic_gb_rx_flowctl(config_word)	\
	((config_word) |= 1 << 5)
#घोषणा qlcnic_gb_get_rx_flowctl(config_word)	\
	_qlcnic_crb_get_bit((config_word), 5)
#घोषणा qlcnic_gb_unset_rx_flowctl(config_word)	\
	((config_word) &= ~(1 << 5))

/*
 * NIU GB Pause Ctl Register
 */

#घोषणा qlcnic_gb_set_gb0_mask(config_word)    \
	((config_word) |= 1 << 0)
#घोषणा qlcnic_gb_set_gb1_mask(config_word)    \
	((config_word) |= 1 << 2)
#घोषणा qlcnic_gb_set_gb2_mask(config_word)    \
	((config_word) |= 1 << 4)
#घोषणा qlcnic_gb_set_gb3_mask(config_word)    \
	((config_word) |= 1 << 6)

#घोषणा qlcnic_gb_get_gb0_mask(config_word)    \
	_qlcnic_crb_get_bit((config_word), 0)
#घोषणा qlcnic_gb_get_gb1_mask(config_word)    \
	_qlcnic_crb_get_bit((config_word), 2)
#घोषणा qlcnic_gb_get_gb2_mask(config_word)    \
	_qlcnic_crb_get_bit((config_word), 4)
#घोषणा qlcnic_gb_get_gb3_mask(config_word)    \
	_qlcnic_crb_get_bit((config_word), 6)

#घोषणा qlcnic_gb_unset_gb0_mask(config_word)  \
	((config_word) &= ~(1 << 0))
#घोषणा qlcnic_gb_unset_gb1_mask(config_word)  \
	((config_word) &= ~(1 << 2))
#घोषणा qlcnic_gb_unset_gb2_mask(config_word)  \
	((config_word) &= ~(1 << 4))
#घोषणा qlcnic_gb_unset_gb3_mask(config_word)  \
	((config_word) &= ~(1 << 6))

/*
 * NIU XG Pause Ctl Register
 *
 *      Bit 0       : xg0_mask => 1:disable tx छोड़ो frames
 *      Bit 1       : xg0_request => 1:request single छोड़ो frame
 *      Bit 2       : xg0_on_off => 1:request is छोड़ो on, 0:off
 *      Bit 3       : xg1_mask => 1:disable tx छोड़ो frames
 *      Bit 4       : xg1_request => 1:request single छोड़ो frame
 *      Bit 5       : xg1_on_off => 1:request is छोड़ो on, 0:off
 */

#घोषणा qlcnic_xg_set_xg0_mask(config_word)    \
	((config_word) |= 1 << 0)
#घोषणा qlcnic_xg_set_xg1_mask(config_word)    \
	((config_word) |= 1 << 3)

#घोषणा qlcnic_xg_get_xg0_mask(config_word)    \
	_qlcnic_crb_get_bit((config_word), 0)
#घोषणा qlcnic_xg_get_xg1_mask(config_word)    \
	_qlcnic_crb_get_bit((config_word), 3)

#घोषणा qlcnic_xg_unset_xg0_mask(config_word)  \
	((config_word) &= ~(1 << 0))
#घोषणा qlcnic_xg_unset_xg1_mask(config_word)  \
	((config_word) &= ~(1 << 3))

/*
 * NIU XG Pause Ctl Register
 *
 *      Bit 0       : xg0_mask => 1:disable tx छोड़ो frames
 *      Bit 1       : xg0_request => 1:request single छोड़ो frame
 *      Bit 2       : xg0_on_off => 1:request is छोड़ो on, 0:off
 *      Bit 3       : xg1_mask => 1:disable tx छोड़ो frames
 *      Bit 4       : xg1_request => 1:request single छोड़ो frame
 *      Bit 5       : xg1_on_off => 1:request is छोड़ो on, 0:off
 */

/*
 * PHY-Specअगरic MII control/status रेजिस्टरs.
 */
#घोषणा QLCNIC_NIU_GB_MII_MGMT_ADDR_AUTONEG		4
#घोषणा QLCNIC_NIU_GB_MII_MGMT_ADDR_PHY_STATUS		17

/*
 * PHY-Specअगरic Status Register (reg 17).
 *
 * Bit 0      : jabber => 1:jabber detected, 0:not
 * Bit 1      : polarity => 1:polarity reversed, 0:normal
 * Bit 2      : recvछोड़ो => 1:receive छोड़ो enabled, 0:disabled
 * Bit 3      : xmitछोड़ो => 1:transmit छोड़ो enabled, 0:disabled
 * Bit 4      : energydetect => 1:sleep, 0:active
 * Bit 5      : करोwnshअगरt => 1:करोwnshअगरt, 0:no करोwnshअगरt
 * Bit 6      : crossover => 1:MDIX (crossover), 0:MDI (no crossover)
 * Bits 7-9   : cablelen => not valid in 10Mb/s mode
 *			0:<50m, 1:50-80m, 2:80-110m, 3:110-140m, 4:>140m
 * Bit 10     : link => 1:link up, 0:link करोwn
 * Bit 11     : resolved => 1:speed and duplex resolved, 0:not yet
 * Bit 12     : pagercvd => 1:page received, 0:page not received
 * Bit 13     : duplex => 1:full duplex, 0:half duplex
 * Bits 14-15 : speed => 0:10Mb/s, 1:100Mb/s, 2:1000Mb/s, 3:rsvd
 */

#घोषणा qlcnic_get_phy_speed(config_word) (((config_word) >> 14) & 0x03)

#घोषणा qlcnic_set_phy_speed(config_word, val)	\
		((config_word) |= ((val & 0x03) << 14))
#घोषणा qlcnic_set_phy_duplex(config_word)	\
		((config_word) |= 1 << 13)
#घोषणा qlcnic_clear_phy_duplex(config_word)	\
		((config_word) &= ~(1 << 13))

#घोषणा qlcnic_get_phy_link(config_word)	\
		_qlcnic_crb_get_bit(config_word, 10)
#घोषणा qlcnic_get_phy_duplex(config_word)	\
		_qlcnic_crb_get_bit(config_word, 13)

#घोषणा QLCNIC_NIU_NON_PROMISC_MODE	0
#घोषणा QLCNIC_NIU_PROMISC_MODE		1
#घोषणा QLCNIC_NIU_ALLMULTI_MODE	2

#घोषणा QLCNIC_PCIE_SEM_TIMEOUT	10000

काष्ठा crb_128M_2M_sub_block_map अणु
	अचिन्हित valid;
	अचिन्हित start_128M;
	अचिन्हित end_128M;
	अचिन्हित start_2M;
पूर्ण;

काष्ठा crb_128M_2M_block_mapअणु
	काष्ठा crb_128M_2M_sub_block_map sub_block[16];
पूर्ण;
#पूर्ण_अगर				/* __QLCNIC_HDR_H_ */
