<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000E_82571_H_
#घोषणा _E1000E_82571_H_

#घोषणा ID_LED_RESERVED_F746	0xF746
#घोषणा ID_LED_DEFAULT_82573	((ID_LED_DEF1_DEF2 << 12) | \
				 (ID_LED_OFF1_ON2  <<  8) | \
				 (ID_LED_DEF1_DEF2 <<  4) | \
				 (ID_LED_DEF1_DEF2))

#घोषणा E1000_GCR_L1_ACT_WITHOUT_L0S_RX	0x08000000
#घोषणा AN_RETRY_COUNT		5	/* Autoneg Retry Count value */

/* Intr Throttling - RW */
#घोषणा E1000_EITR_82574(_n)	(0x000E8 + (0x4 * (_n)))

#घोषणा E1000_EIAC_82574	0x000DC	/* Ext. Interrupt Auto Clear - RW */
#घोषणा E1000_EIAC_MASK_82574	0x01F00000

#घोषणा E1000_IVAR_INT_ALLOC_VALID	0x8

/* Manageability Operation Mode mask */
#घोषणा E1000_NVM_INIT_CTRL2_MNGM	0x6000

#घोषणा E1000_BASE1000T_STATUS		10
#घोषणा E1000_IDLE_ERROR_COUNT_MASK	0xFF
#घोषणा E1000_RECEIVE_ERROR_COUNTER	21
#घोषणा E1000_RECEIVE_ERROR_MAX		0xFFFF
bool e1000_check_phy_82574(काष्ठा e1000_hw *hw);
bool e1000e_get_laa_state_82571(काष्ठा e1000_hw *hw);
व्योम e1000e_set_laa_state_82571(काष्ठा e1000_hw *hw, bool state);

#पूर्ण_अगर
