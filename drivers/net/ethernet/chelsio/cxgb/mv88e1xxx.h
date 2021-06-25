<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* $Date: 2005/03/07 23:59:05 $ $RCSfile: mv88e1xxx.h,v $ $Revision: 1.13 $ */
#अगर_अघोषित CHELSIO_MV8E1XXX_H
#घोषणा CHELSIO_MV8E1XXX_H

#अगर_अघोषित BMCR_SPEED1000
# define BMCR_SPEED1000 0x40
#पूर्ण_अगर

#अगर_अघोषित ADVERTISE_PAUSE
# define ADVERTISE_PAUSE 0x400
#पूर्ण_अगर
#अगर_अघोषित ADVERTISE_PAUSE_ASYM
# define ADVERTISE_PAUSE_ASYM 0x800
#पूर्ण_अगर

/* Gigabit MII रेजिस्टरs */
#घोषणा MII_GBCR 9       /* 1000Base-T control रेजिस्टर */
#घोषणा MII_GBSR 10      /* 1000Base-T status रेजिस्टर */

/* 1000Base-T control रेजिस्टर fields */
#घोषणा GBCR_ADV_1000HALF         0x100
#घोषणा GBCR_ADV_1000FULL         0x200
#घोषणा GBCR_PREFER_MASTER        0x400
#घोषणा GBCR_MANUAL_AS_MASTER     0x800
#घोषणा GBCR_MANUAL_CONFIG_ENABLE 0x1000

/* 1000Base-T status रेजिस्टर fields */
#घोषणा GBSR_LP_1000HALF  0x400
#घोषणा GBSR_LP_1000FULL  0x800
#घोषणा GBSR_REMOTE_OK    0x1000
#घोषणा GBSR_LOCAL_OK     0x2000
#घोषणा GBSR_LOCAL_MASTER 0x4000
#घोषणा GBSR_MASTER_FAULT 0x8000

/* Marvell PHY पूर्णांकerrupt status bits. */
#घोषणा MV88E1XXX_INTR_JABBER          0x0001
#घोषणा MV88E1XXX_INTR_POLARITY_CHNG   0x0002
#घोषणा MV88E1XXX_INTR_ENG_DETECT_CHNG 0x0010
#घोषणा MV88E1XXX_INTR_DOWNSHIFT       0x0020
#घोषणा MV88E1XXX_INTR_MDI_XOVER_CHNG  0x0040
#घोषणा MV88E1XXX_INTR_FIFO_OVER_UNDER 0x0080
#घोषणा MV88E1XXX_INTR_FALSE_CARRIER   0x0100
#घोषणा MV88E1XXX_INTR_SYMBOL_ERROR    0x0200
#घोषणा MV88E1XXX_INTR_LINK_CHNG       0x0400
#घोषणा MV88E1XXX_INTR_AUTONEG_DONE    0x0800
#घोषणा MV88E1XXX_INTR_PAGE_RECV       0x1000
#घोषणा MV88E1XXX_INTR_DUPLEX_CHNG     0x2000
#घोषणा MV88E1XXX_INTR_SPEED_CHNG      0x4000
#घोषणा MV88E1XXX_INTR_AUTONEG_ERR     0x8000

/* Marvell PHY specअगरic रेजिस्टरs. */
#घोषणा MV88E1XXX_SPECIFIC_CNTRL_REGISTER               16
#घोषणा MV88E1XXX_SPECIFIC_STATUS_REGISTER              17
#घोषणा MV88E1XXX_INTERRUPT_ENABLE_REGISTER             18
#घोषणा MV88E1XXX_INTERRUPT_STATUS_REGISTER             19
#घोषणा MV88E1XXX_EXT_PHY_SPECIFIC_CNTRL_REGISTER       20
#घोषणा MV88E1XXX_RECV_ERR_CNTR_REGISTER                21
#घोषणा MV88E1XXX_RES_REGISTER                          22
#घोषणा MV88E1XXX_GLOBAL_STATUS_REGISTER                23
#घोषणा MV88E1XXX_LED_CONTROL_REGISTER                  24
#घोषणा MV88E1XXX_MANUAL_LED_OVERRIDE_REGISTER          25
#घोषणा MV88E1XXX_EXT_PHY_SPECIFIC_CNTRL_2_REGISTER     26
#घोषणा MV88E1XXX_EXT_PHY_SPECIFIC_STATUS_REGISTER      27
#घोषणा MV88E1XXX_VIRTUAL_CABLE_TESTER_REGISTER         28
#घोषणा MV88E1XXX_EXTENDED_ADDR_REGISTER                29
#घोषणा MV88E1XXX_EXTENDED_REGISTER                     30

/* PHY specअगरic control रेजिस्टर fields */
#घोषणा S_PSCR_MDI_XOVER_MODE    5
#घोषणा M_PSCR_MDI_XOVER_MODE    0x3
#घोषणा V_PSCR_MDI_XOVER_MODE(x) ((x) << S_PSCR_MDI_XOVER_MODE)
#घोषणा G_PSCR_MDI_XOVER_MODE(x) (((x) >> S_PSCR_MDI_XOVER_MODE) & M_PSCR_MDI_XOVER_MODE)

/* Extended PHY specअगरic control रेजिस्टर fields */
#घोषणा S_DOWNSHIFT_ENABLE 8
#घोषणा V_DOWNSHIFT_ENABLE (1 << S_DOWNSHIFT_ENABLE)

#घोषणा S_DOWNSHIFT_CNT    9
#घोषणा M_DOWNSHIFT_CNT    0x7
#घोषणा V_DOWNSHIFT_CNT(x) ((x) << S_DOWNSHIFT_CNT)
#घोषणा G_DOWNSHIFT_CNT(x) (((x) >> S_DOWNSHIFT_CNT) & M_DOWNSHIFT_CNT)

/* PHY specअगरic status रेजिस्टर fields */
#घोषणा S_PSSR_JABBER 0
#घोषणा V_PSSR_JABBER (1 << S_PSSR_JABBER)

#घोषणा S_PSSR_POLARITY 1
#घोषणा V_PSSR_POLARITY (1 << S_PSSR_POLARITY)

#घोषणा S_PSSR_RX_PAUSE 2
#घोषणा V_PSSR_RX_PAUSE (1 << S_PSSR_RX_PAUSE)

#घोषणा S_PSSR_TX_PAUSE 3
#घोषणा V_PSSR_TX_PAUSE (1 << S_PSSR_TX_PAUSE)

#घोषणा S_PSSR_ENERGY_DETECT 4
#घोषणा V_PSSR_ENERGY_DETECT (1 << S_PSSR_ENERGY_DETECT)

#घोषणा S_PSSR_DOWNSHIFT_STATUS 5
#घोषणा V_PSSR_DOWNSHIFT_STATUS (1 << S_PSSR_DOWNSHIFT_STATUS)

#घोषणा S_PSSR_MDI 6
#घोषणा V_PSSR_MDI (1 << S_PSSR_MDI)

#घोषणा S_PSSR_CABLE_LEN    7
#घोषणा M_PSSR_CABLE_LEN    0x7
#घोषणा V_PSSR_CABLE_LEN(x) ((x) << S_PSSR_CABLE_LEN)
#घोषणा G_PSSR_CABLE_LEN(x) (((x) >> S_PSSR_CABLE_LEN) & M_PSSR_CABLE_LEN)

#घोषणा S_PSSR_LINK 10
#घोषणा V_PSSR_LINK (1 << S_PSSR_LINK)

#घोषणा S_PSSR_STATUS_RESOLVED 11
#घोषणा V_PSSR_STATUS_RESOLVED (1 << S_PSSR_STATUS_RESOLVED)

#घोषणा S_PSSR_PAGE_RECEIVED 12
#घोषणा V_PSSR_PAGE_RECEIVED (1 << S_PSSR_PAGE_RECEIVED)

#घोषणा S_PSSR_DUPLEX 13
#घोषणा V_PSSR_DUPLEX (1 << S_PSSR_DUPLEX)

#घोषणा S_PSSR_SPEED    14
#घोषणा M_PSSR_SPEED    0x3
#घोषणा V_PSSR_SPEED(x) ((x) << S_PSSR_SPEED)
#घोषणा G_PSSR_SPEED(x) (((x) >> S_PSSR_SPEED) & M_PSSR_SPEED)

#पूर्ण_अगर
