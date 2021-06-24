<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Marvell 88E6xxx Switch PTP support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2017 National Instruments
 *      Erik Hons <erik.hons@ni.com>
 *      Bअक्रमon Streअगरf <bअक्रमon.streअगरf@ni.com>
 *      Dane Wagner <dane.wagner@ni.com>
 */

#अगर_अघोषित _MV88E6XXX_PTP_H
#घोषणा _MV88E6XXX_PTP_H

#समावेश "chip.h"

/* Offset 0x00: TAI Global Config */
#घोषणा MV88E6XXX_TAI_CFG			0x00
#घोषणा MV88E6XXX_TAI_CFG_CAP_OVERWRITE		0x8000
#घोषणा MV88E6XXX_TAI_CFG_CAP_CTR_START		0x4000
#घोषणा MV88E6XXX_TAI_CFG_EVREQ_FALLING		0x2000
#घोषणा MV88E6XXX_TAI_CFG_TRIG_ACTIVE_LO	0x1000
#घोषणा MV88E6XXX_TAI_CFG_IRL_ENABLE		0x0400
#घोषणा MV88E6XXX_TAI_CFG_TRIG_IRQ_EN		0x0200
#घोषणा MV88E6XXX_TAI_CFG_EVREQ_IRQ_EN		0x0100
#घोषणा MV88E6XXX_TAI_CFG_TRIG_LOCK		0x0080
#घोषणा MV88E6XXX_TAI_CFG_BLOCK_UPDATE		0x0008
#घोषणा MV88E6XXX_TAI_CFG_MULTI_PTP		0x0004
#घोषणा MV88E6XXX_TAI_CFG_TRIG_MODE_ONESHOT	0x0002
#घोषणा MV88E6XXX_TAI_CFG_TRIG_ENABLE		0x0001

/* Offset 0x01: Timestamp Clock Period (ps) */
#घोषणा MV88E6XXX_TAI_CLOCK_PERIOD		0x01

/* Offset 0x02/0x03: Trigger Generation Amount */
#घोषणा MV88E6XXX_TAI_TRIG_GEN_AMOUNT_LO	0x02
#घोषणा MV88E6XXX_TAI_TRIG_GEN_AMOUNT_HI	0x03

/* Offset 0x04: Clock Compensation */
#घोषणा MV88E6XXX_TAI_TRIG_CLOCK_COMP		0x04

/* Offset 0x05: Trigger Configuration */
#घोषणा MV88E6XXX_TAI_TRIG_CFG			0x05

/* Offset 0x06: Ingress Rate Limiter Clock Generation Amount */
#घोषणा MV88E6XXX_TAI_IRL_AMOUNT		0x06

/* Offset 0x07: Ingress Rate Limiter Compensation */
#घोषणा MV88E6XXX_TAI_IRL_COMP			0x07

/* Offset 0x08: Ingress Rate Limiter Compensation */
#घोषणा MV88E6XXX_TAI_IRL_COMP_PS		0x08

/* Offset 0x09: Event Status */
#घोषणा MV88E6XXX_TAI_EVENT_STATUS		0x09
#घोषणा MV88E6XXX_TAI_EVENT_STATUS_CAP_TRIG	0x4000
#घोषणा MV88E6XXX_TAI_EVENT_STATUS_ERROR	0x0200
#घोषणा MV88E6XXX_TAI_EVENT_STATUS_VALID	0x0100
#घोषणा MV88E6XXX_TAI_EVENT_STATUS_CTR_MASK	0x00ff

/* Offset 0x0A/0x0B: Event Time */
#घोषणा MV88E6XXX_TAI_EVENT_TIME_LO		0x0a
#घोषणा MV88E6XXX_TAI_EVENT_TYPE_HI		0x0b

/* Offset 0x0E/0x0F: PTP Global Time */
#घोषणा MV88E6XXX_TAI_TIME_LO			0x0e
#घोषणा MV88E6XXX_TAI_TIME_HI			0x0f

/* Offset 0x10/0x11: Trig Generation Time */
#घोषणा MV88E6XXX_TAI_TRIG_TIME_LO		0x10
#घोषणा MV88E6XXX_TAI_TRIG_TIME_HI		0x11

/* Offset 0x12: Lock Status */
#घोषणा MV88E6XXX_TAI_LOCK_STATUS		0x12

/* Offset 0x00: Ether Type */
#घोषणा MV88E6XXX_PTP_GC_ETYPE			0x00

/* 6165 Global Control Registers */
/* Offset 0x00: Ether Type */
#घोषणा MV88E6XXX_PTP_GC_ETYPE			0x00

/* Offset 0x01: Message ID */
#घोषणा MV88E6XXX_PTP_GC_MESSAGE_ID		0x01

/* Offset 0x02: Time Stamp Arrive Time */
#घोषणा MV88E6XXX_PTP_GC_TS_ARR_PTR		0x02

/* Offset 0x03: Port Arrival Interrupt Enable */
#घोषणा MV88E6XXX_PTP_GC_PORT_ARR_INT_EN	0x03

/* Offset 0x04: Port Departure Interrupt Enable */
#घोषणा MV88E6XXX_PTP_GC_PORT_DEP_INT_EN	0x04

/* Offset 0x05: Configuration */
#घोषणा MV88E6XXX_PTP_GC_CONFIG			0x05
#घोषणा MV88E6XXX_PTP_GC_CONFIG_DIS_OVERWRITE	BIT(1)
#घोषणा MV88E6XXX_PTP_GC_CONFIG_DIS_TS		BIT(0)

/* Offset 0x8: Interrupt Status */
#घोषणा MV88E6XXX_PTP_GC_INT_STATUS		0x08

/* Offset 0x9/0xa: Global Time */
#घोषणा MV88E6XXX_PTP_GC_TIME_LO		0x09
#घोषणा MV88E6XXX_PTP_GC_TIME_HI		0x0A

/* 6165 Per Port Registers */
/* Offset 0: Arrival Time 0 Status */
#घोषणा MV88E6165_PORT_PTP_ARR0_STS	0x00

/* Offset 0x01/0x02: PTP Arrival 0 Time */
#घोषणा MV88E6165_PORT_PTP_ARR0_TIME_LO	0x01
#घोषणा MV88E6165_PORT_PTP_ARR0_TIME_HI	0x02

/* Offset 0x03: PTP Arrival 0 Sequence ID */
#घोषणा MV88E6165_PORT_PTP_ARR0_SEQID	0x03

/* Offset 0x04: PTP Arrival 1 Status */
#घोषणा MV88E6165_PORT_PTP_ARR1_STS	0x04

/* Offset 0x05/0x6E: PTP Arrival 1 Time */
#घोषणा MV88E6165_PORT_PTP_ARR1_TIME_LO	0x05
#घोषणा MV88E6165_PORT_PTP_ARR1_TIME_HI	0x06

/* Offset 0x07: PTP Arrival 1 Sequence ID */
#घोषणा MV88E6165_PORT_PTP_ARR1_SEQID	0x07

/* Offset 0x08: PTP Departure Status */
#घोषणा MV88E6165_PORT_PTP_DEP_STS	0x08

/* Offset 0x09/0x0a: PTP Deperture Time */
#घोषणा MV88E6165_PORT_PTP_DEP_TIME_LO	0x09
#घोषणा MV88E6165_PORT_PTP_DEP_TIME_HI	0x0a

/* Offset 0x0b: PTP Departure Sequence ID */
#घोषणा MV88E6165_PORT_PTP_DEP_SEQID	0x0b

/* Offset 0x0d: Port Status */
#घोषणा MV88E6164_PORT_STATUS		0x0d

#अगर_घोषित CONFIG_NET_DSA_MV88E6XXX_PTP

दीर्घ mv88e6xxx_hwtstamp_work(काष्ठा ptp_घड़ी_info *ptp);
पूर्णांक mv88e6xxx_ptp_setup(काष्ठा mv88e6xxx_chip *chip);
व्योम mv88e6xxx_ptp_मुक्त(काष्ठा mv88e6xxx_chip *chip);

#घोषणा ptp_to_chip(ptp) container_of(ptp, काष्ठा mv88e6xxx_chip,	\
				      ptp_घड़ी_info)

बाह्य स्थिर काष्ठा mv88e6xxx_ptp_ops mv88e6165_ptp_ops;
बाह्य स्थिर काष्ठा mv88e6xxx_ptp_ops mv88e6250_ptp_ops;
बाह्य स्थिर काष्ठा mv88e6xxx_ptp_ops mv88e6352_ptp_ops;

#अन्यथा /* !CONFIG_NET_DSA_MV88E6XXX_PTP */

अटल अंतरभूत दीर्घ mv88e6xxx_hwtstamp_work(काष्ठा ptp_घड़ी_info *ptp)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक mv88e6xxx_ptp_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mv88e6xxx_ptp_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
पूर्ण

अटल स्थिर काष्ठा mv88e6xxx_ptp_ops mv88e6165_ptp_ops = अणुपूर्ण;
अटल स्थिर काष्ठा mv88e6xxx_ptp_ops mv88e6250_ptp_ops = अणुपूर्ण;
अटल स्थिर काष्ठा mv88e6xxx_ptp_ops mv88e6352_ptp_ops = अणुपूर्ण;

#पूर्ण_अगर /* CONFIG_NET_DSA_MV88E6XXX_PTP */

#पूर्ण_अगर /* _MV88E6XXX_PTP_H */
