<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */
#अगर_अघोषित __QLA_NX_H
#घोषणा __QLA_NX_H

/*
 * Following are the states of the Phantom. Phantom will set them and
 * Host will पढ़ो to check अगर the fields are correct.
*/
#घोषणा PHAN_INITIALIZE_FAILED		0xffff
#घोषणा PHAN_INITIALIZE_COMPLETE	0xff01

/* Host ग_लिखोs the following to notअगरy that it has करोne the init-handshake */
#घोषणा PHAN_INITIALIZE_ACK		0xf00f
#घोषणा PHAN_PEG_RCV_INITIALIZED	0xff01

/*CRB_RELATED*/
#घोषणा QLA82XX_CRB_BASE		(QLA82XX_CAM_RAM(0x200))
#घोषणा QLA82XX_REG(X)			(QLA82XX_CRB_BASE+(X))
#घोषणा CRB_CMDPEG_STATE		QLA82XX_REG(0x50)
#घोषणा CRB_RCVPEG_STATE		QLA82XX_REG(0x13c)
#घोषणा CRB_DMA_SHIFT			QLA82XX_REG(0xcc)
#घोषणा CRB_TEMP_STATE			QLA82XX_REG(0x1b4)
#घोषणा CRB_CMDPEG_CHECK_RETRY_COUNT	60
#घोषणा CRB_CMDPEG_CHECK_DELAY		500

#घोषणा qla82xx_get_temp_val(x)		((x) >> 16)
#घोषणा qla82xx_get_temp_state(x)	((x) & 0xffff)
#घोषणा qla82xx_encode_temp(val, state)	(((val) << 16) | (state))

/*
 * Temperature control.
 */
क्रमागत अणु
	QLA82XX_TEMP_NORMAL = 0x1,	/* Normal operating range */
	QLA82XX_TEMP_WARN,	/* Sound alert, temperature getting high */
	QLA82XX_TEMP_PANIC	/* Fatal error, hardware has shut करोwn. */
पूर्ण;

#घोषणा CRB_NIU_XG_PAUSE_CTL_P0		0x1
#घोषणा CRB_NIU_XG_PAUSE_CTL_P1		0x8

#घोषणा QLA82XX_HW_H0_CH_HUB_ADR	0x05
#घोषणा QLA82XX_HW_H1_CH_HUB_ADR	0x0E
#घोषणा QLA82XX_HW_H2_CH_HUB_ADR	0x03
#घोषणा QLA82XX_HW_H3_CH_HUB_ADR	0x01
#घोषणा QLA82XX_HW_H4_CH_HUB_ADR	0x06
#घोषणा QLA82XX_HW_H5_CH_HUB_ADR	0x07
#घोषणा QLA82XX_HW_H6_CH_HUB_ADR	0x08

/*  Hub 0 */
#घोषणा QLA82XX_HW_MN_CRB_AGT_ADR	0x15
#घोषणा QLA82XX_HW_MS_CRB_AGT_ADR	0x25

/*  Hub 1 */
#घोषणा QLA82XX_HW_PS_CRB_AGT_ADR	0x73
#घोषणा QLA82XX_HW_QMS_CRB_AGT_ADR	0x00
#घोषणा QLA82XX_HW_RPMX3_CRB_AGT_ADR	0x0b
#घोषणा QLA82XX_HW_SQGS0_CRB_AGT_ADR	0x01
#घोषणा QLA82XX_HW_SQGS1_CRB_AGT_ADR	0x02
#घोषणा QLA82XX_HW_SQGS2_CRB_AGT_ADR	0x03
#घोषणा QLA82XX_HW_SQGS3_CRB_AGT_ADR	0x04
#घोषणा QLA82XX_HW_C2C0_CRB_AGT_ADR	0x58
#घोषणा QLA82XX_HW_C2C1_CRB_AGT_ADR	0x59
#घोषणा QLA82XX_HW_C2C2_CRB_AGT_ADR	0x5a
#घोषणा QLA82XX_HW_RPMX2_CRB_AGT_ADR	0x0a
#घोषणा QLA82XX_HW_RPMX4_CRB_AGT_ADR	0x0c
#घोषणा QLA82XX_HW_RPMX7_CRB_AGT_ADR	0x0f
#घोषणा QLA82XX_HW_RPMX9_CRB_AGT_ADR	0x12
#घोषणा QLA82XX_HW_SMB_CRB_AGT_ADR	0x18

/*  Hub 2 */
#घोषणा QLA82XX_HW_NIU_CRB_AGT_ADR	0x31
#घोषणा QLA82XX_HW_I2C0_CRB_AGT_ADR	0x19
#घोषणा QLA82XX_HW_I2C1_CRB_AGT_ADR	0x29

#घोषणा QLA82XX_HW_SN_CRB_AGT_ADR	0x10
#घोषणा QLA82XX_HW_I2Q_CRB_AGT_ADR	0x20
#घोषणा QLA82XX_HW_LPC_CRB_AGT_ADR	0x22
#घोषणा QLA82XX_HW_ROMUSB_CRB_AGT_ADR   0x21
#घोषणा QLA82XX_HW_QM_CRB_AGT_ADR	0x66
#घोषणा QLA82XX_HW_SQG0_CRB_AGT_ADR	0x60
#घोषणा QLA82XX_HW_SQG1_CRB_AGT_ADR	0x61
#घोषणा QLA82XX_HW_SQG2_CRB_AGT_ADR	0x62
#घोषणा QLA82XX_HW_SQG3_CRB_AGT_ADR	0x63
#घोषणा QLA82XX_HW_RPMX1_CRB_AGT_ADR    0x09
#घोषणा QLA82XX_HW_RPMX5_CRB_AGT_ADR    0x0d
#घोषणा QLA82XX_HW_RPMX6_CRB_AGT_ADR    0x0e
#घोषणा QLA82XX_HW_RPMX8_CRB_AGT_ADR    0x11

/*  Hub 3 */
#घोषणा QLA82XX_HW_PH_CRB_AGT_ADR	0x1A
#घोषणा QLA82XX_HW_SRE_CRB_AGT_ADR	0x50
#घोषणा QLA82XX_HW_EG_CRB_AGT_ADR	0x51
#घोषणा QLA82XX_HW_RPMX0_CRB_AGT_ADR	0x08

/*  Hub 4 */
#घोषणा QLA82XX_HW_PEGN0_CRB_AGT_ADR	0x40
#घोषणा QLA82XX_HW_PEGN1_CRB_AGT_ADR	0x41
#घोषणा QLA82XX_HW_PEGN2_CRB_AGT_ADR	0x42
#घोषणा QLA82XX_HW_PEGN3_CRB_AGT_ADR	0x43
#घोषणा QLA82XX_HW_PEGNI_CRB_AGT_ADR	0x44
#घोषणा QLA82XX_HW_PEGND_CRB_AGT_ADR	0x45
#घोषणा QLA82XX_HW_PEGNC_CRB_AGT_ADR	0x46
#घोषणा QLA82XX_HW_PEGR0_CRB_AGT_ADR	0x47
#घोषणा QLA82XX_HW_PEGR1_CRB_AGT_ADR	0x48
#घोषणा QLA82XX_HW_PEGR2_CRB_AGT_ADR	0x49
#घोषणा QLA82XX_HW_PEGR3_CRB_AGT_ADR	0x4a
#घोषणा QLA82XX_HW_PEGN4_CRB_AGT_ADR	0x4b

/*  Hub 5 */
#घोषणा QLA82XX_HW_PEGS0_CRB_AGT_ADR	0x40
#घोषणा QLA82XX_HW_PEGS1_CRB_AGT_ADR	0x41
#घोषणा QLA82XX_HW_PEGS2_CRB_AGT_ADR	0x42
#घोषणा QLA82XX_HW_PEGS3_CRB_AGT_ADR	0x43

#घोषणा QLA82XX_HW_PEGSI_CRB_AGT_ADR	0x44
#घोषणा QLA82XX_HW_PEGSD_CRB_AGT_ADR	0x45
#घोषणा QLA82XX_HW_PEGSC_CRB_AGT_ADR	0x46

/*  Hub 6 */
#घोषणा QLA82XX_HW_CAS0_CRB_AGT_ADR	0x46
#घोषणा QLA82XX_HW_CAS1_CRB_AGT_ADR	0x47
#घोषणा QLA82XX_HW_CAS2_CRB_AGT_ADR	0x48
#घोषणा QLA82XX_HW_CAS3_CRB_AGT_ADR	0x49
#घोषणा QLA82XX_HW_NCM_CRB_AGT_ADR	0x16
#घोषणा QLA82XX_HW_TMR_CRB_AGT_ADR	0x17
#घोषणा QLA82XX_HW_XDMA_CRB_AGT_ADR	0x05
#घोषणा QLA82XX_HW_OCM0_CRB_AGT_ADR	0x06
#घोषणा QLA82XX_HW_OCM1_CRB_AGT_ADR	0x07

/*  This field defines PCI/X adr [25:20] of agents on the CRB */
/*  */
#घोषणा QLA82XX_HW_PX_MAP_CRB_PH	0
#घोषणा QLA82XX_HW_PX_MAP_CRB_PS	1
#घोषणा QLA82XX_HW_PX_MAP_CRB_MN	2
#घोषणा QLA82XX_HW_PX_MAP_CRB_MS	3
#घोषणा QLA82XX_HW_PX_MAP_CRB_SRE	5
#घोषणा QLA82XX_HW_PX_MAP_CRB_NIU	6
#घोषणा QLA82XX_HW_PX_MAP_CRB_QMN	7
#घोषणा QLA82XX_HW_PX_MAP_CRB_SQN0	8
#घोषणा QLA82XX_HW_PX_MAP_CRB_SQN1	9
#घोषणा QLA82XX_HW_PX_MAP_CRB_SQN2	10
#घोषणा QLA82XX_HW_PX_MAP_CRB_SQN3	11
#घोषणा QLA82XX_HW_PX_MAP_CRB_QMS	12
#घोषणा QLA82XX_HW_PX_MAP_CRB_SQS0	13
#घोषणा QLA82XX_HW_PX_MAP_CRB_SQS1	14
#घोषणा QLA82XX_HW_PX_MAP_CRB_SQS2	15
#घोषणा QLA82XX_HW_PX_MAP_CRB_SQS3	16
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGN0	17
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGN1	18
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGN2	19
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGN3	20
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGN4	QLA82XX_HW_PX_MAP_CRB_SQS2
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGND	21
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGNI	22
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGS0	23
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGS1	24
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGS2	25
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGS3	26
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGSD	27
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGSI	28
#घोषणा QLA82XX_HW_PX_MAP_CRB_SN	29
#घोषणा QLA82XX_HW_PX_MAP_CRB_EG	31
#घोषणा QLA82XX_HW_PX_MAP_CRB_PH2	32
#घोषणा QLA82XX_HW_PX_MAP_CRB_PS2	33
#घोषणा QLA82XX_HW_PX_MAP_CRB_CAM	34
#घोषणा QLA82XX_HW_PX_MAP_CRB_CAS0	35
#घोषणा QLA82XX_HW_PX_MAP_CRB_CAS1	36
#घोषणा QLA82XX_HW_PX_MAP_CRB_CAS2	37
#घोषणा QLA82XX_HW_PX_MAP_CRB_C2C0	38
#घोषणा QLA82XX_HW_PX_MAP_CRB_C2C1	39
#घोषणा QLA82XX_HW_PX_MAP_CRB_TIMR	40
#घोषणा QLA82XX_HW_PX_MAP_CRB_RPMX1	42
#घोषणा QLA82XX_HW_PX_MAP_CRB_RPMX2	43
#घोषणा QLA82XX_HW_PX_MAP_CRB_RPMX3	44
#घोषणा QLA82XX_HW_PX_MAP_CRB_RPMX4	45
#घोषणा QLA82XX_HW_PX_MAP_CRB_RPMX5	46
#घोषणा QLA82XX_HW_PX_MAP_CRB_RPMX6	47
#घोषणा QLA82XX_HW_PX_MAP_CRB_RPMX7	48
#घोषणा QLA82XX_HW_PX_MAP_CRB_XDMA	49
#घोषणा QLA82XX_HW_PX_MAP_CRB_I2Q	50
#घोषणा QLA82XX_HW_PX_MAP_CRB_ROMUSB    51
#घोषणा QLA82XX_HW_PX_MAP_CRB_CAS3	52
#घोषणा QLA82XX_HW_PX_MAP_CRB_RPMX0	53
#घोषणा QLA82XX_HW_PX_MAP_CRB_RPMX8	54
#घोषणा QLA82XX_HW_PX_MAP_CRB_RPMX9	55
#घोषणा QLA82XX_HW_PX_MAP_CRB_OCM0	56
#घोषणा QLA82XX_HW_PX_MAP_CRB_OCM1	57
#घोषणा QLA82XX_HW_PX_MAP_CRB_SMB	58
#घोषणा QLA82XX_HW_PX_MAP_CRB_I2C0	59
#घोषणा QLA82XX_HW_PX_MAP_CRB_I2C1	60
#घोषणा QLA82XX_HW_PX_MAP_CRB_LPC	61
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGNC	62
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGR0	63
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGR1	4
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGR2	30
#घोषणा QLA82XX_HW_PX_MAP_CRB_PGR3	41

/*  This field defines CRB adr [31:20] of the agents */
/*  */

#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_MN	((QLA82XX_HW_H0_CH_HUB_ADR << 7) | \
					QLA82XX_HW_MN_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PH	((QLA82XX_HW_H0_CH_HUB_ADR << 7) | \
					QLA82XX_HW_PH_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_MS	((QLA82XX_HW_H0_CH_HUB_ADR << 7) | \
					QLA82XX_HW_MS_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PS	((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					QLA82XX_HW_PS_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_SS	((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					QLA82XX_HW_SS_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX3    ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_RPMX3_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_QMS	    ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_QMS_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_SQS0     ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_SQGS0_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_SQS1     ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_SQGS1_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_SQS2     ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_SQGS2_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_SQS3     ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_SQGS3_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_C2C0     ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_C2C0_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_C2C1     ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_C2C1_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX2    ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_RPMX2_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX4    ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_RPMX4_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX7    ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_RPMX7_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX9    ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_RPMX9_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_SMB	    ((QLA82XX_HW_H1_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_SMB_CRB_AGT_ADR)

#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_NIU      ((QLA82XX_HW_H2_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_NIU_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_I2C0     ((QLA82XX_HW_H2_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_I2C0_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_I2C1     ((QLA82XX_HW_H2_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_I2C1_CRB_AGT_ADR)

#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_SRE      ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_SRE_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_EG       ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_EG_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX0    ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_RPMX0_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_QMN      ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_QM_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_SQN0     ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_SQG0_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_SQN1     ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_SQG1_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_SQN2     ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_SQG2_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_SQN3     ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_SQG3_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX1    ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_RPMX1_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX5    ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_RPMX5_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX6    ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_RPMX6_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_RPMX8    ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_RPMX8_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_CAS0     ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_CAS0_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_CAS1     ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_CAS1_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_CAS2     ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_CAS2_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_CAS3     ((QLA82XX_HW_H3_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_CAS3_CRB_AGT_ADR)

#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGNI     ((QLA82XX_HW_H4_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGNI_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGND     ((QLA82XX_HW_H4_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGND_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGN0     ((QLA82XX_HW_H4_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGN0_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGN1     ((QLA82XX_HW_H4_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGN1_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGN2     ((QLA82XX_HW_H4_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGN2_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGN3     ((QLA82XX_HW_H4_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGN3_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGN4     ((QLA82XX_HW_H4_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGN4_CRB_AGT_ADR)

#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGNC     ((QLA82XX_HW_H4_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGNC_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGR0     ((QLA82XX_HW_H4_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGR0_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGR1     ((QLA82XX_HW_H4_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGR1_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGR2     ((QLA82XX_HW_H4_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGR2_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGR3     ((QLA82XX_HW_H4_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGR3_CRB_AGT_ADR)

#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGSI     ((QLA82XX_HW_H5_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGSI_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGSD     ((QLA82XX_HW_H5_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGSD_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGS0     ((QLA82XX_HW_H5_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGS0_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGS1     ((QLA82XX_HW_H5_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGS1_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGS2     ((QLA82XX_HW_H5_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGS2_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGS3     ((QLA82XX_HW_H5_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGS3_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_PGSC     ((QLA82XX_HW_H5_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_PEGSC_CRB_AGT_ADR)

#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_CAM      ((QLA82XX_HW_H6_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_NCM_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_TIMR     ((QLA82XX_HW_H6_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_TMR_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_XDMA     ((QLA82XX_HW_H6_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_XDMA_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_SN       ((QLA82XX_HW_H6_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_SN_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_I2Q      ((QLA82XX_HW_H6_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_I2Q_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_ROMUSB   ((QLA82XX_HW_H6_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_ROMUSB_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_OCM0     ((QLA82XX_HW_H6_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_OCM0_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_OCM1     ((QLA82XX_HW_H6_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_OCM1_CRB_AGT_ADR)
#घोषणा QLA82XX_HW_CRB_HUB_AGT_ADR_LPC      ((QLA82XX_HW_H6_CH_HUB_ADR << 7) | \
					    QLA82XX_HW_LPC_CRB_AGT_ADR)

#घोषणा ROMUSB_GLB	(QLA82XX_CRB_ROMUSB + 0x00000)
#घोषणा QLA82XX_ROMUSB_GLB_PEGTUNE_DONE		(ROMUSB_GLB + 0x005c)
#घोषणा QLA82XX_ROMUSB_GLB_STATUS		(ROMUSB_GLB + 0x0004)
#घोषणा QLA82XX_ROMUSB_GLB_SW_RESET		(ROMUSB_GLB + 0x0008)
#घोषणा QLA82XX_ROMUSB_ROM_ADDRESS		(ROMUSB_ROM + 0x0008)
#घोषणा QLA82XX_ROMUSB_ROM_WDATA		(ROMUSB_ROM + 0x000c)
#घोषणा QLA82XX_ROMUSB_ROM_ABYTE_CNT		(ROMUSB_ROM + 0x0010)
#घोषणा QLA82XX_ROMUSB_ROM_DUMMY_BYTE_CNT	(ROMUSB_ROM + 0x0014)
#घोषणा QLA82XX_ROMUSB_ROM_RDATA		(ROMUSB_ROM + 0x0018)

#घोषणा ROMUSB_ROM	(QLA82XX_CRB_ROMUSB + 0x10000)
#घोषणा QLA82XX_ROMUSB_ROM_INSTR_OPCODE	(ROMUSB_ROM + 0x0004)
#घोषणा QLA82XX_ROMUSB_GLB_CAS_RST	(ROMUSB_GLB + 0x0038)

/* Lock IDs क्रम ROM lock */
#घोषणा ROM_LOCK_DRIVER		0x0d417340

#घोषणा QLA82XX_PCI_CRB_WINDOWSIZE	0x00100000    /* all are 1MB winकरोws */
#घोषणा QLA82XX_PCI_CRB_WINDOW(A)	(QLA82XX_PCI_CRBSPACE + \
					(A)*QLA82XX_PCI_CRB_WINDOWSIZE)

#घोषणा QLA82XX_CRB_C2C_0 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_C2C0)
#घोषणा QLA82XX_CRB_C2C_1 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_C2C1)
#घोषणा QLA82XX_CRB_C2C_2 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_C2C2)
#घोषणा QLA82XX_CRB_CAM	\
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_CAM)
#घोषणा QLA82XX_CRB_CASPER \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_CAS)
#घोषणा QLA82XX_CRB_CASPER_0 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_CAS0)
#घोषणा QLA82XX_CRB_CASPER_1 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_CAS1)
#घोषणा QLA82XX_CRB_CASPER_2 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_CAS2)
#घोषणा QLA82XX_CRB_DDR_MD \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_MS)
#घोषणा QLA82XX_CRB_DDR_NET \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_MN)
#घोषणा QLA82XX_CRB_EPG \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_EG)
#घोषणा QLA82XX_CRB_I2Q \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_I2Q)
#घोषणा QLA82XX_CRB_NIU	\
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_NIU)
/* HACK upon HACK upon HACK (क्रम PCIE builds) */
#घोषणा QLA82XX_CRB_PCIX_HOST \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PH)
#घोषणा QLA82XX_CRB_PCIX_HOST2 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PH2)
#घोषणा QLA82XX_CRB_PCIX_MD \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PS)
#घोषणा QLA82XX_CRB_PCIE	QLA82XX_CRB_PCIX_MD
/* winकरोw 1 pcie slot */
#घोषणा QLA82XX_CRB_PCIE2 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PS2)

#घोषणा QLA82XX_CRB_PEG_MD_0 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGS0)
#घोषणा QLA82XX_CRB_PEG_MD_1 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGS1)
#घोषणा QLA82XX_CRB_PEG_MD_2 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGS2)
#घोषणा QLA82XX_CRB_PEG_MD_3 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGS3)
#घोषणा QLA82XX_CRB_PEG_MD_3 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGS3)
#घोषणा QLA82XX_CRB_PEG_MD_D \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGSD)
#घोषणा QLA82XX_CRB_PEG_MD_I \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGSI)
#घोषणा QLA82XX_CRB_PEG_NET_0 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGN0)
#घोषणा QLA82XX_CRB_PEG_NET_1 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGN1)
#घोषणा QLA82XX_CRB_PEG_NET_2 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGN2)
#घोषणा QLA82XX_CRB_PEG_NET_3 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGN3)
#घोषणा QLA82XX_CRB_PEG_NET_4 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGN4)
#घोषणा QLA82XX_CRB_PEG_NET_D \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGND)
#घोषणा QLA82XX_CRB_PEG_NET_I \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_PGNI)
#घोषणा QLA82XX_CRB_PQM_MD \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_QMS)
#घोषणा QLA82XX_CRB_PQM_NET \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_QMN)
#घोषणा QLA82XX_CRB_QDR_MD \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_SS)
#घोषणा QLA82XX_CRB_QDR_NET \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_SN)
#घोषणा QLA82XX_CRB_ROMUSB \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_ROMUSB)
#घोषणा QLA82XX_CRB_RPMX_0 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_RPMX0)
#घोषणा QLA82XX_CRB_RPMX_1 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_RPMX1)
#घोषणा QLA82XX_CRB_RPMX_2 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_RPMX2)
#घोषणा QLA82XX_CRB_RPMX_3 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_RPMX3)
#घोषणा QLA82XX_CRB_RPMX_4 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_RPMX4)
#घोषणा QLA82XX_CRB_RPMX_5 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_RPMX5)
#घोषणा QLA82XX_CRB_RPMX_6 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_RPMX6)
#घोषणा QLA82XX_CRB_RPMX_7 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_RPMX7)
#घोषणा QLA82XX_CRB_SQM_MD_0 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_SQS0)
#घोषणा QLA82XX_CRB_SQM_MD_1 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_SQS1)
#घोषणा QLA82XX_CRB_SQM_MD_2 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_SQS2)
#घोषणा QLA82XX_CRB_SQM_MD_3 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_SQS3)
#घोषणा QLA82XX_CRB_SQM_NET_0 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_SQN0)
#घोषणा QLA82XX_CRB_SQM_NET_1 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_SQN1)
#घोषणा QLA82XX_CRB_SQM_NET_2 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_SQN2)
#घोषणा QLA82XX_CRB_SQM_NET_3 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_SQN3)
#घोषणा QLA82XX_CRB_SRE \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_SRE)
#घोषणा QLA82XX_CRB_TIMER \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_TIMR)
#घोषणा QLA82XX_CRB_XDMA \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_XDMA)
#घोषणा QLA82XX_CRB_I2C0 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_I2C0)
#घोषणा QLA82XX_CRB_I2C1 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_I2C1)
#घोषणा QLA82XX_CRB_OCM0 \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_OCM0)
#घोषणा QLA82XX_CRB_SMB \
	QLA82XX_PCI_CRB_WINDOW(QLA82XX_HW_PX_MAP_CRB_SMB)

#घोषणा QLA82XX_CRB_MAX		QLA82XX_PCI_CRB_WINDOW(64)

/*
 * ====================== BASE ADDRESSES ON-CHIP ======================
 * Base addresses of major components on-chip.
 * ====================== BASE ADDRESSES ON-CHIP ======================
 */
#घोषणा QLA8XXX_ADDR_DDR_NET		(0x0000000000000000ULL)
#घोषणा QLA8XXX_ADDR_DDR_NET_MAX	(0x000000000fffffffULL)

/* Imbus address bit used to indicate a host address. This bit is
 * eliminated by the pcie bar and bar select beक्रमe presentation
 * over pcie. */
/* host memory via IMBUS */
#घोषणा QLA82XX_P2_ADDR_PCIE	(0x0000000800000000ULL)
#घोषणा QLA82XX_P3_ADDR_PCIE	(0x0000008000000000ULL)
#घोषणा QLA82XX_ADDR_PCIE_MAX	(0x0000000FFFFFFFFFULL)
#घोषणा QLA8XXX_ADDR_OCM0	(0x0000000200000000ULL)
#घोषणा QLA8XXX_ADDR_OCM0_MAX	(0x00000002000fffffULL)
#घोषणा QLA8XXX_ADDR_OCM1	(0x0000000200400000ULL)
#घोषणा QLA8XXX_ADDR_OCM1_MAX	(0x00000002004fffffULL)
#घोषणा QLA8XXX_ADDR_QDR_NET	(0x0000000300000000ULL)

#घोषणा QLA82XX_P2_ADDR_QDR_NET_MAX	(0x00000003001fffffULL)
#घोषणा QLA82XX_P3_ADDR_QDR_NET_MAX	(0x0000000303ffffffULL)
#घोषणा QLA8XXX_ADDR_QDR_NET_MAX	(0x0000000307ffffffULL)

#घोषणा QLA82XX_PCI_CRBSPACE		(अचिन्हित दीर्घ)0x06000000
#घोषणा QLA82XX_PCI_सूचीECT_CRB		(अचिन्हित दीर्घ)0x04400000
#घोषणा QLA82XX_PCI_CAMQM		(अचिन्हित दीर्घ)0x04800000
#घोषणा QLA82XX_PCI_CAMQM_MAX		(अचिन्हित दीर्घ)0x04ffffff
#घोषणा QLA82XX_PCI_DDR_NET		(अचिन्हित दीर्घ)0x00000000
#घोषणा QLA82XX_PCI_QDR_NET		(अचिन्हित दीर्घ)0x04000000
#घोषणा QLA82XX_PCI_QDR_NET_MAX		(अचिन्हित दीर्घ)0x043fffff

/*  PCI Winकरोwing क्रम DDR regions.  */
#घोषणा QLA8XXX_ADDR_IN_RANGE(addr, low, high)            \
	(((addr) <= (high)) && ((addr) >= (low)))

/*
 *   Register offsets क्रम MN
 */
#घोषणा MIU_CONTROL			(0x000)
#घोषणा MIU_TAG				(0x004)
#घोषणा MIU_TEST_AGT_CTRL		(0x090)
#घोषणा MIU_TEST_AGT_ADDR_LO		(0x094)
#घोषणा MIU_TEST_AGT_ADDR_HI		(0x098)
#घोषणा MIU_TEST_AGT_WRDATA_LO		(0x0a0)
#घोषणा MIU_TEST_AGT_WRDATA_HI		(0x0a4)
#घोषणा MIU_TEST_AGT_WRDATA(i)		(0x0a0+(4*(i)))
#घोषणा MIU_TEST_AGT_RDDATA_LO		(0x0a8)
#घोषणा MIU_TEST_AGT_RDDATA_HI		(0x0ac)
#घोषणा MIU_TEST_AGT_RDDATA(i)		(0x0a8+(4*(i)))
#घोषणा MIU_TEST_AGT_ADDR_MASK		0xfffffff8
#घोषणा MIU_TEST_AGT_UPPER_ADDR(off)	(0)

/* MIU_TEST_AGT_CTRL flags. work क्रम SIU as well */
#घोषणा MIU_TA_CTL_START	1
#घोषणा MIU_TA_CTL_ENABLE	2
#घोषणा MIU_TA_CTL_WRITE	4
#घोषणा MIU_TA_CTL_BUSY		8

#घोषणा MIU_TA_CTL_WRITE_ENABLE		(MIU_TA_CTL_WRITE | MIU_TA_CTL_ENABLE)
#घोषणा MIU_TA_CTL_WRITE_START		(MIU_TA_CTL_WRITE | MIU_TA_CTL_ENABLE |\
					 MIU_TA_CTL_START)
#घोषणा MIU_TA_CTL_START_ENABLE		(MIU_TA_CTL_START | MIU_TA_CTL_ENABLE)

/*CAM RAM */
# define QLA82XX_CAM_RAM_BASE	(QLA82XX_CRB_CAM + 0x02000)
# define QLA82XX_CAM_RAM(reg)	(QLA82XX_CAM_RAM_BASE + (reg))

#घोषणा QLA82XX_PORT_MODE_ADDR		(QLA82XX_CAM_RAM(0x24))
#घोषणा QLA82XX_PEG_HALT_STATUS1	(QLA82XX_CAM_RAM(0xa8))
#घोषणा QLA82XX_PEG_HALT_STATUS2	(QLA82XX_CAM_RAM(0xac))
#घोषणा QLA82XX_PEG_ALIVE_COUNTER	(QLA82XX_CAM_RAM(0xb0))
#घोषणा QLA82XX_CAM_RAM_DB1		(QLA82XX_CAM_RAM(0x1b0))
#घोषणा QLA82XX_CAM_RAM_DB2		(QLA82XX_CAM_RAM(0x1b4))

#घोषणा HALT_STATUS_UNRECOVERABLE	0x80000000
#घोषणा HALT_STATUS_RECOVERABLE		0x40000000


#घोषणा QLA82XX_ROM_LOCK_ID		(QLA82XX_CAM_RAM(0x100))
#घोषणा QLA82XX_CRB_WIN_LOCK_ID		(QLA82XX_CAM_RAM(0x124))
#घोषणा QLA82XX_FW_VERSION_MAJOR	(QLA82XX_CAM_RAM(0x150))
#घोषणा QLA82XX_FW_VERSION_MINOR	(QLA82XX_CAM_RAM(0x154))
#घोषणा QLA82XX_FW_VERSION_SUB		(QLA82XX_CAM_RAM(0x158))
#घोषणा QLA82XX_PCIE_REG(reg)		(QLA82XX_CRB_PCIE + (reg))

/* Driver Coexistence Defines */
#घोषणा QLA82XX_CRB_DRV_ACTIVE		(QLA82XX_CAM_RAM(0x138))
#घोषणा QLA82XX_CRB_DEV_STATE		(QLA82XX_CAM_RAM(0x140))
#घोषणा QLA82XX_CRB_DRV_STATE		(QLA82XX_CAM_RAM(0x144))
#घोषणा QLA82XX_CRB_DRV_SCRATCH		(QLA82XX_CAM_RAM(0x148))
#घोषणा QLA82XX_CRB_DEV_PART_INFO	(QLA82XX_CAM_RAM(0x14c))
#घोषणा QLA82XX_CRB_DRV_IDC_VERSION	(QLA82XX_CAM_RAM(0x174))

क्रमागत qla_regs अणु
	QLA8XXX_PEG_HALT_STATUS1 = 0,
	QLA8XXX_PEG_HALT_STATUS2,
	QLA8XXX_PEG_ALIVE_COUNTER,
	QLA8XXX_CRB_DRV_ACTIVE,
	QLA8XXX_CRB_DEV_STATE,
	QLA8XXX_CRB_DRV_STATE,
	QLA8XXX_CRB_DRV_SCRATCH,
	QLA8XXX_CRB_DEV_PART_INFO,
	QLA8XXX_CRB_DRV_IDC_VERSION,
	QLA8XXX_FW_VERSION_MAJOR,
	QLA8XXX_FW_VERSION_MINOR,
	QLA8XXX_FW_VERSION_SUB,
	QLA8XXX_CRB_CMDPEG_STATE,
	QLA8XXX_CRB_TEMP_STATE,
पूर्ण;

/* Every driver should use these Device State */
#घोषणा QLA8XXX_DEV_COLD		1
#घोषणा QLA8XXX_DEV_INITIALIZING	2
#घोषणा QLA8XXX_DEV_READY		3
#घोषणा QLA8XXX_DEV_NEED_RESET		4
#घोषणा QLA8XXX_DEV_NEED_QUIESCENT	5
#घोषणा QLA8XXX_DEV_FAILED		6
#घोषणा QLA8XXX_DEV_QUIESCENT		7
#घोषणा MAX_STATES			8 /* Increment अगर new state added */

#घोषणा QLA82XX_IDC_VERSION		0x1
#घोषणा ROM_DEV_INIT_TIMEOUT		30
#घोषणा ROM_DRV_RESET_ACK_TIMEOUT	10

#घोषणा PCIE_SETUP_FUNCTION		(0x12040)
#घोषणा PCIE_SETUP_FUNCTION2		(0x12048)

#घोषणा QLA82XX_PCIX_PS_REG(reg)	(QLA82XX_CRB_PCIX_MD + (reg))
#घोषणा QLA82XX_PCIX_PS2_REG(reg)	(QLA82XX_CRB_PCIE2 + (reg))

#घोषणा PCIE_SEM2_LOCK		(0x1c010)  /* Flash lock   */
#घोषणा PCIE_SEM2_UNLOCK	(0x1c014)  /* Flash unlock */
#घोषणा PCIE_SEM5_LOCK		(0x1c028)  /* Coexistence lock   */
#घोषणा PCIE_SEM5_UNLOCK	(0x1c02c)  /* Coexistence unlock */
#घोषणा PCIE_SEM7_LOCK		(0x1c038)  /* crb win lock */
#घोषणा PCIE_SEM7_UNLOCK	(0x1c03c)  /* crbwin unlock*/

/*
 * The PCI VenकरोrID and DeviceID क्रम our board.
 */
#घोषणा QLA82XX_MSIX_TBL_SPACE		8192
#घोषणा QLA82XX_PCI_REG_MSIX_TBL	0x44
#घोषणा QLA82XX_PCI_MSIX_CONTROL	0x40

काष्ठा crb_128M_2M_sub_block_map अणु
	अचिन्हित valid;
	अचिन्हित start_128M;
	अचिन्हित end_128M;
	अचिन्हित start_2M;
पूर्ण;

काष्ठा crb_128M_2M_block_map अणु
	काष्ठा crb_128M_2M_sub_block_map sub_block[16];
पूर्ण;

काष्ठा crb_addr_pair अणु
	दीर्घ addr;
	दीर्घ data;
पूर्ण;

#घोषणा ADDR_ERROR	((अचिन्हित दीर्घ) 0xffffffff)
#घोषणा MAX_CTL_CHECK	1000
#घोषणा QLA82XX_FWERROR_CODE(code)	((code >> 8) & 0x1fffff)

/***************************************************************************
 *		PCI related defines.
 **************************************************************************/

/*
 * Interrupt related defines.
 */
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

/*
 * Message Signaled Interrupts
 */
#घोषणा PCIX_MSI_F0		(0x13000)
#घोषणा PCIX_MSI_F1		(0x13004)
#घोषणा PCIX_MSI_F2		(0x13008)
#घोषणा PCIX_MSI_F3		(0x1300c)
#घोषणा PCIX_MSI_F4		(0x13010)
#घोषणा PCIX_MSI_F5		(0x13014)
#घोषणा PCIX_MSI_F6		(0x13018)
#घोषणा PCIX_MSI_F7		(0x1301c)
#घोषणा PCIX_MSI_F(FUNC)	(0x13000 + ((FUNC) * 4))

/*
 *
 */
#घोषणा PCIX_INT_VECTOR		(0x10100)
#घोषणा PCIX_INT_MASK		(0x10104)

/*
 * Interrupt state machine and other bits.
 */
#घोषणा PCIE_MISCCFG_RC		(0x1206c)


#घोषणा ISR_INT_TARGET_STATUS \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_STATUS))
#घोषणा ISR_INT_TARGET_STATUS_F1 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_STATUS_F1))
#घोषणा ISR_INT_TARGET_STATUS_F2 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_STATUS_F2))
#घोषणा ISR_INT_TARGET_STATUS_F3 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_STATUS_F3))
#घोषणा ISR_INT_TARGET_STATUS_F4 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_STATUS_F4))
#घोषणा ISR_INT_TARGET_STATUS_F5 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_STATUS_F5))
#घोषणा ISR_INT_TARGET_STATUS_F6 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_STATUS_F6))
#घोषणा ISR_INT_TARGET_STATUS_F7 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_STATUS_F7))

#घोषणा ISR_INT_TARGET_MASK \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_MASK))
#घोषणा ISR_INT_TARGET_MASK_F1 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_MASK_F1))
#घोषणा ISR_INT_TARGET_MASK_F2 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_MASK_F2))
#घोषणा ISR_INT_TARGET_MASK_F3 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_MASK_F3))
#घोषणा ISR_INT_TARGET_MASK_F4 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_MASK_F4))
#घोषणा ISR_INT_TARGET_MASK_F5 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_MASK_F5))
#घोषणा ISR_INT_TARGET_MASK_F6 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_MASK_F6))
#घोषणा ISR_INT_TARGET_MASK_F7 \
	(QLA82XX_PCIX_PS_REG(PCIX_TARGET_MASK_F7))

#घोषणा ISR_INT_VECTOR			(QLA82XX_PCIX_PS_REG(PCIX_INT_VECTOR))
#घोषणा ISR_INT_MASK			(QLA82XX_PCIX_PS_REG(PCIX_INT_MASK))
#घोषणा ISR_INT_STATE_REG		(QLA82XX_PCIX_PS_REG(PCIE_MISCCFG_RC))

#घोषणा	ISR_MSI_INT_TRIGGER(FUNC)	(QLA82XX_PCIX_PS_REG(PCIX_MSI_F(FUNC)))


#घोषणा	ISR_IS_LEGACY_INTR_IDLE(VAL)		(((VAL) & 0x300) == 0)
#घोषणा	ISR_IS_LEGACY_INTR_TRIGGERED(VAL)	(((VAL) & 0x300) == 0x200)

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

/* काष्ठा qla4_8xxx_legacy_पूर्णांकr_set defined in ql4_def.h */

#घोषणा QLA82XX_LEGACY_INTR_CONFIG                                      \
अणु                                                                       \
	अणु                                                               \
		.पूर्णांक_vec_bit    =	PCIX_INT_VECTOR_BIT_F0,         \
		.tgt_status_reg =	ISR_INT_TARGET_STATUS,          \
		.tgt_mask_reg   =	ISR_INT_TARGET_MASK,            \
		.pci_पूर्णांक_reg    =	ISR_MSI_INT_TRIGGER(0) पूर्ण,       \
									\
	अणु								\
		.पूर्णांक_vec_bit    =	PCIX_INT_VECTOR_BIT_F1,         \
		.tgt_status_reg =	ISR_INT_TARGET_STATUS_F1,       \
		.tgt_mask_reg   =	ISR_INT_TARGET_MASK_F1,         \
		.pci_पूर्णांक_reg    =	ISR_MSI_INT_TRIGGER(1) पूर्ण,       \
									\
	अणु								\
		.पूर्णांक_vec_bit    =	PCIX_INT_VECTOR_BIT_F2,         \
		.tgt_status_reg =	ISR_INT_TARGET_STATUS_F2,       \
		.tgt_mask_reg   =	ISR_INT_TARGET_MASK_F2,         \
		.pci_पूर्णांक_reg    =	ISR_MSI_INT_TRIGGER(2) पूर्ण,       \
									\
	अणु								\
		.पूर्णांक_vec_bit    =	PCIX_INT_VECTOR_BIT_F3,         \
		.tgt_status_reg =	ISR_INT_TARGET_STATUS_F3,       \
		.tgt_mask_reg   =	ISR_INT_TARGET_MASK_F3,         \
		.pci_पूर्णांक_reg    =	ISR_MSI_INT_TRIGGER(3) पूर्ण,       \
									\
	अणु								\
		.पूर्णांक_vec_bit    =	PCIX_INT_VECTOR_BIT_F4,         \
		.tgt_status_reg =	ISR_INT_TARGET_STATUS_F4,       \
		.tgt_mask_reg   =	ISR_INT_TARGET_MASK_F4,         \
		.pci_पूर्णांक_reg    =	ISR_MSI_INT_TRIGGER(4) पूर्ण,       \
									\
	अणु								\
		.पूर्णांक_vec_bit    =	PCIX_INT_VECTOR_BIT_F5,         \
		.tgt_status_reg =	ISR_INT_TARGET_STATUS_F5,       \
		.tgt_mask_reg   =	ISR_INT_TARGET_MASK_F5,         \
		.pci_पूर्णांक_reg    =	ISR_MSI_INT_TRIGGER(5) पूर्ण,       \
									\
	अणु								\
		.पूर्णांक_vec_bit    =	PCIX_INT_VECTOR_BIT_F6,         \
		.tgt_status_reg =	ISR_INT_TARGET_STATUS_F6,       \
		.tgt_mask_reg   =	ISR_INT_TARGET_MASK_F6,         \
		.pci_पूर्णांक_reg    =	ISR_MSI_INT_TRIGGER(6) पूर्ण,       \
									\
	अणु								\
		.पूर्णांक_vec_bit    =	PCIX_INT_VECTOR_BIT_F7,         \
		.tgt_status_reg =	ISR_INT_TARGET_STATUS_F7,       \
		.tgt_mask_reg   =	ISR_INT_TARGET_MASK_F7,         \
		.pci_पूर्णांक_reg    =	ISR_MSI_INT_TRIGGER(7) पूर्ण,       \
पूर्ण

/* Magic number to let user know flash is programmed */
#घोषणा	QLA82XX_BDINFO_MAGIC	0x12345678
#घोषणा FW_SIZE_OFFSET		(0x3e840c)

/* QLA82XX additions */
#घोषणा MIU_TEST_AGT_WRDATA_UPPER_LO	(0x0b0)
#घोषणा	MIU_TEST_AGT_WRDATA_UPPER_HI	(0x0b4)

/* Minidump related */

/* Entry Type Defines */
#घोषणा QLA8XXX_RDNOP	0
#घोषणा QLA8XXX_RDCRB	1
#घोषणा QLA8XXX_RDMUX	2
#घोषणा QLA8XXX_QUEUE	3
#घोषणा QLA8XXX_BOARD	4
#घोषणा QLA8XXX_RDOCM	6
#घोषणा QLA8XXX_PREGS	7
#घोषणा QLA8XXX_L1DTG	8
#घोषणा QLA8XXX_L1ITG	9
#घोषणा QLA8XXX_L1DAT	11
#घोषणा QLA8XXX_L1INS	12
#घोषणा QLA8XXX_L2DTG	21
#घोषणा QLA8XXX_L2ITG	22
#घोषणा QLA8XXX_L2DAT	23
#घोषणा QLA8XXX_L2INS	24
#घोषणा QLA83XX_POLLRD	35
#घोषणा QLA83XX_RDMUX2	36
#घोषणा QLA83XX_POLLRDMWR  37
#घोषणा QLA8044_RDDFE	38
#घोषणा QLA8044_RDMDIO	39
#घोषणा QLA8044_POLLWR	40
#घोषणा QLA8XXX_RDROM	71
#घोषणा QLA8XXX_RDMEM	72
#घोषणा QLA8XXX_CNTRL	98
#घोषणा QLA83XX_TLHDR	99
#घोषणा QLA8XXX_RDEND	255

/* Opcodes क्रम Control Entries.
 * These Flags are bit fields.
 */
#घोषणा QLA8XXX_DBG_OPCODE_WR		0x01
#घोषणा QLA8XXX_DBG_OPCODE_RW		0x02
#घोषणा QLA8XXX_DBG_OPCODE_AND		0x04
#घोषणा QLA8XXX_DBG_OPCODE_OR		0x08
#घोषणा QLA8XXX_DBG_OPCODE_POLL		0x10
#घोषणा QLA8XXX_DBG_OPCODE_RDSTATE	0x20
#घोषणा QLA8XXX_DBG_OPCODE_WRSTATE	0x40
#घोषणा QLA8XXX_DBG_OPCODE_MDSTATE	0x80

/* Driver Flags */
#घोषणा QLA8XXX_DBG_SKIPPED_FLAG	0x80 /* driver skipped this entry  */
#घोषणा QLA8XXX_DBG_SIZE_ERR_FLAG	0x40 /* Entry vs Capture size
					      * mismatch */

/* Driver_code is क्रम driver to ग_लिखो some info about the entry
 * currently not used.
 */
काष्ठा qla8xxx_minidump_entry_hdr अणु
	uपूर्णांक32_t entry_type;
	uपूर्णांक32_t entry_size;
	uपूर्णांक32_t entry_capture_size;
	काष्ठा अणु
		uपूर्णांक8_t entry_capture_mask;
		uपूर्णांक8_t entry_code;
		uपूर्णांक8_t driver_code;
		uपूर्णांक8_t driver_flags;
	पूर्ण d_ctrl;
पूर्ण;

/*  Read CRB entry header */
काष्ठा qla8xxx_minidump_entry_crb अणु
	काष्ठा qla8xxx_minidump_entry_hdr h;
	uपूर्णांक32_t addr;
	काष्ठा अणु
		uपूर्णांक8_t addr_stride;
		uपूर्णांक8_t state_index_a;
		uपूर्णांक16_t poll_समयout;
	पूर्ण crb_strd;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t op_count;

	काष्ठा अणु
		uपूर्णांक8_t opcode;
		uपूर्णांक8_t state_index_v;
		uपूर्णांक8_t shl;
		uपूर्णांक8_t shr;
	पूर्ण crb_ctrl;

	uपूर्णांक32_t value_1;
	uपूर्णांक32_t value_2;
	uपूर्णांक32_t value_3;
पूर्ण;

काष्ठा qla8xxx_minidump_entry_cache अणु
	काष्ठा qla8xxx_minidump_entry_hdr h;
	uपूर्णांक32_t tag_reg_addr;
	काष्ठा अणु
		uपूर्णांक16_t tag_value_stride;
		uपूर्णांक16_t init_tag_value;
	पूर्ण addr_ctrl;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t op_count;
	uपूर्णांक32_t control_addr;
	काष्ठा अणु
		uपूर्णांक16_t ग_लिखो_value;
		uपूर्णांक8_t poll_mask;
		uपूर्णांक8_t poll_रुको;
	पूर्ण cache_ctrl;
	uपूर्णांक32_t पढ़ो_addr;
	काष्ठा अणु
		uपूर्णांक8_t पढ़ो_addr_stride;
		uपूर्णांक8_t पढ़ो_addr_cnt;
		uपूर्णांक16_t rsvd_1;
	पूर्ण पढ़ो_ctrl;
पूर्ण;

/* Read OCM */
काष्ठा qla8xxx_minidump_entry_rकरोcm अणु
	काष्ठा qla8xxx_minidump_entry_hdr h;
	uपूर्णांक32_t rsvd_0;
	uपूर्णांक32_t rsvd_1;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t op_count;
	uपूर्णांक32_t rsvd_2;
	uपूर्णांक32_t rsvd_3;
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक32_t पढ़ो_addr_stride;
पूर्ण;

/* Read Memory */
काष्ठा qla8xxx_minidump_entry_rdmem अणु
	काष्ठा qla8xxx_minidump_entry_hdr h;
	uपूर्णांक32_t rsvd[6];
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक32_t पढ़ो_data_size;
पूर्ण;

/* Read ROM */
काष्ठा qla8xxx_minidump_entry_rdrom अणु
	काष्ठा qla8xxx_minidump_entry_hdr h;
	uपूर्णांक32_t rsvd[6];
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक32_t पढ़ो_data_size;
पूर्ण;

/* Mux entry */
काष्ठा qla8xxx_minidump_entry_mux अणु
	काष्ठा qla8xxx_minidump_entry_hdr h;
	uपूर्णांक32_t select_addr;
	uपूर्णांक32_t rsvd_0;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t op_count;
	uपूर्णांक32_t select_value;
	uपूर्णांक32_t select_value_stride;
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक32_t rsvd_1;
पूर्ण;

/* Queue entry */
काष्ठा qla8xxx_minidump_entry_queue अणु
	काष्ठा qla8xxx_minidump_entry_hdr h;
	uपूर्णांक32_t select_addr;
	काष्ठा अणु
		uपूर्णांक16_t queue_id_stride;
		uपूर्णांक16_t rsvd_0;
	पूर्ण q_strd;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t op_count;
	uपूर्णांक32_t rsvd_1;
	uपूर्णांक32_t rsvd_2;
	uपूर्णांक32_t पढ़ो_addr;
	काष्ठा अणु
		uपूर्णांक8_t पढ़ो_addr_stride;
		uपूर्णांक8_t पढ़ो_addr_cnt;
		uपूर्णांक16_t rsvd_3;
	पूर्ण rd_strd;
पूर्ण;

#घोषणा MBC_DIAGNOSTIC_MINIDUMP_TEMPLATE	0x129
#घोषणा RQST_TMPLT_SIZE				0x0
#घोषणा RQST_TMPLT				0x1
#घोषणा MD_सूचीECT_ROM_WINDOW			0x42110030
#घोषणा MD_सूचीECT_ROM_READ_BASE			0x42150000
#घोषणा MD_MIU_TEST_AGT_CTRL			0x41000090
#घोषणा MD_MIU_TEST_AGT_ADDR_LO			0x41000094
#घोषणा MD_MIU_TEST_AGT_ADDR_HI			0x41000098

#घोषणा MD_MIU_TEST_AGT_WRDATA_LO		0x410000A0
#घोषणा MD_MIU_TEST_AGT_WRDATA_HI		0x410000A4
#घोषणा MD_MIU_TEST_AGT_WRDATA_ULO		0x410000B0
#घोषणा MD_MIU_TEST_AGT_WRDATA_UHI		0x410000B4

#पूर्ण_अगर
