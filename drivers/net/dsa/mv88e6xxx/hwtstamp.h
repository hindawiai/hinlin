<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Marvell 88E6xxx Switch hardware बारtamping support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2017 National Instruments
 *      Erik Hons <erik.hons@ni.com>
 *      Bअक्रमon Streअगरf <bअक्रमon.streअगरf@ni.com>
 *      Dane Wagner <dane.wagner@ni.com>
 */

#अगर_अघोषित _MV88E6XXX_HWTSTAMP_H
#घोषणा _MV88E6XXX_HWTSTAMP_H

#समावेश "chip.h"

/* Global 6352 PTP रेजिस्टरs */
/* Offset 0x00: PTP EtherType */
#घोषणा MV88E6XXX_PTP_ETHERTYPE	0x00

/* Offset 0x01: Message Type Timestamp Enables */
#घोषणा MV88E6XXX_PTP_MSGTYPE			0x01
#घोषणा MV88E6XXX_PTP_MSGTYPE_SYNC		0x0001
#घोषणा MV88E6XXX_PTP_MSGTYPE_DELAY_REQ		0x0002
#घोषणा MV88E6XXX_PTP_MSGTYPE_PDLAY_REQ		0x0004
#घोषणा MV88E6XXX_PTP_MSGTYPE_PDLAY_RES		0x0008
#घोषणा MV88E6XXX_PTP_MSGTYPE_ALL_EVENT		0x000f

/* Offset 0x02: Timestamp Arrival Capture Poपूर्णांकers */
#घोषणा MV88E6XXX_PTP_TS_ARRIVAL_PTR	0x02

/* Offset 0x05: PTP Global Configuration */
#घोषणा MV88E6165_PTP_CFG			0x05
#घोषणा MV88E6165_PTP_CFG_TSPEC_MASK		0xf000
#घोषणा MV88E6165_PTP_CFG_DISABLE_TS_OVERWRITE	BIT(1)
#घोषणा MV88E6165_PTP_CFG_DISABLE_PTP		BIT(0)

/* Offset 0x07: PTP Global Configuration */
#घोषणा MV88E6341_PTP_CFG			0x07
#घोषणा MV88E6341_PTP_CFG_UPDATE		0x8000
#घोषणा MV88E6341_PTP_CFG_IDX_MASK		0x7f00
#घोषणा MV88E6341_PTP_CFG_DATA_MASK		0x00ff
#घोषणा MV88E6341_PTP_CFG_MODE_IDX		0x0
#घोषणा MV88E6341_PTP_CFG_MODE_TS_AT_PHY	0x00
#घोषणा MV88E6341_PTP_CFG_MODE_TS_AT_MAC	0x80

/* Offset 0x08: PTP Interrupt Status */
#घोषणा MV88E6XXX_PTP_IRQ_STATUS	0x08

/* Per-Port 6352 PTP Registers */
/* Offset 0x00: PTP Configuration 0 */
#घोषणा MV88E6XXX_PORT_PTP_CFG0				0x00
#घोषणा MV88E6XXX_PORT_PTP_CFG0_TSPEC_SHIFT		12
#घोषणा MV88E6XXX_PORT_PTP_CFG0_TSPEC_MASK		0xf000
#घोषणा MV88E6XXX_PORT_PTP_CFG0_TSPEC_1588		0x0000
#घोषणा MV88E6XXX_PORT_PTP_CFG0_TSPEC_8021AS		0x1000
#घोषणा MV88E6XXX_PORT_PTP_CFG0_DISABLE_TSPEC_MATCH	0x0800
#घोषणा MV88E6XXX_PORT_PTP_CFG0_DISABLE_OVERWRITE	0x0002
#घोषणा MV88E6XXX_PORT_PTP_CFG0_DISABLE_PTP		0x0001

/* Offset 0x01: PTP Configuration 1 */
#घोषणा MV88E6XXX_PORT_PTP_CFG1	0x01

/* Offset 0x02: PTP Configuration 2 */
#घोषणा MV88E6XXX_PORT_PTP_CFG2				0x02
#घोषणा MV88E6XXX_PORT_PTP_CFG2_EMBED_ARRIVAL		0x1000
#घोषणा MV88E6XXX_PORT_PTP_CFG2_DEP_IRQ_EN		0x0002
#घोषणा MV88E6XXX_PORT_PTP_CFG2_ARR_IRQ_EN		0x0001

/* Offset 0x03: PTP LED Configuration */
#घोषणा MV88E6XXX_PORT_PTP_LED_CFG	0x03

/* Offset 0x08: PTP Arrival 0 Status */
#घोषणा MV88E6XXX_PORT_PTP_ARR0_STS	0x08

/* Offset 0x09/0x0A: PTP Arrival 0 Time */
#घोषणा MV88E6XXX_PORT_PTP_ARR0_TIME_LO	0x09
#घोषणा MV88E6XXX_PORT_PTP_ARR0_TIME_HI	0x0a

/* Offset 0x0B: PTP Arrival 0 Sequence ID */
#घोषणा MV88E6XXX_PORT_PTP_ARR0_SEQID	0x0b

/* Offset 0x0C: PTP Arrival 1 Status */
#घोषणा MV88E6XXX_PORT_PTP_ARR1_STS	0x0c

/* Offset 0x0D/0x0E: PTP Arrival 1 Time */
#घोषणा MV88E6XXX_PORT_PTP_ARR1_TIME_LO	0x0d
#घोषणा MV88E6XXX_PORT_PTP_ARR1_TIME_HI	0x0e

/* Offset 0x0F: PTP Arrival 1 Sequence ID */
#घोषणा MV88E6XXX_PORT_PTP_ARR1_SEQID	0x0f

/* Offset 0x10: PTP Departure Status */
#घोषणा MV88E6XXX_PORT_PTP_DEP_STS	0x10

/* Offset 0x11/0x12: PTP Deperture Time */
#घोषणा MV88E6XXX_PORT_PTP_DEP_TIME_LO	0x11
#घोषणा MV88E6XXX_PORT_PTP_DEP_TIME_HI	0x12

/* Offset 0x13: PTP Departure Sequence ID */
#घोषणा MV88E6XXX_PORT_PTP_DEP_SEQID	0x13

/* Status fields क्रम arrival and depature बारtamp status रेजिस्टरs */
#घोषणा MV88E6XXX_PTP_TS_STATUS_MASK		0x0006
#घोषणा MV88E6XXX_PTP_TS_STATUS_NORMAL		0x0000
#घोषणा MV88E6XXX_PTP_TS_STATUS_OVERWITTEN	0x0002
#घोषणा MV88E6XXX_PTP_TS_STATUS_DISCARDED	0x0004
#घोषणा MV88E6XXX_PTP_TS_VALID			0x0001

#अगर_घोषित CONFIG_NET_DSA_MV88E6XXX_PTP

पूर्णांक mv88e6xxx_port_hwtstamp_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा अगरreq *अगरr);
पूर्णांक mv88e6xxx_port_hwtstamp_get(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा अगरreq *अगरr);

bool mv88e6xxx_port_rxtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा sk_buff *clone, अचिन्हित पूर्णांक type);
व्योम mv88e6xxx_port_txtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा sk_buff *skb);

पूर्णांक mv88e6xxx_get_ts_info(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  काष्ठा ethtool_ts_info *info);

पूर्णांक mv88e6xxx_hwtstamp_setup(काष्ठा mv88e6xxx_chip *chip);
व्योम mv88e6xxx_hwtstamp_मुक्त(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6352_hwtstamp_port_enable(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6352_hwtstamp_port_disable(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6165_global_enable(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6165_global_disable(काष्ठा mv88e6xxx_chip *chip);

#अन्यथा /* !CONFIG_NET_DSA_MV88E6XXX_PTP */

अटल अंतरभूत पूर्णांक mv88e6xxx_port_hwtstamp_set(काष्ठा dsa_चयन *ds,
					      पूर्णांक port, काष्ठा अगरreq *अगरr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक mv88e6xxx_port_hwtstamp_get(काष्ठा dsa_चयन *ds,
					      पूर्णांक port, काष्ठा अगरreq *अगरr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत bool mv88e6xxx_port_rxtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
					   काष्ठा sk_buff *clone,
					   अचिन्हित पूर्णांक type)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम mv88e6xxx_port_txtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
					   काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mv88e6xxx_get_ts_info(काष्ठा dsa_चयन *ds, पूर्णांक port,
					काष्ठा ethtool_ts_info *info)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक mv88e6xxx_hwtstamp_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mv88e6xxx_hwtstamp_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_NET_DSA_MV88E6XXX_PTP */

#पूर्ण_अगर /* _MV88E6XXX_HWTSTAMP_H */
