<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000E_MANAGE_H_
#घोषणा _E1000E_MANAGE_H_

bool e1000e_check_mng_mode_generic(काष्ठा e1000_hw *hw);
bool e1000e_enable_tx_pkt_filtering(काष्ठा e1000_hw *hw);
s32 e1000e_mng_ग_लिखो_dhcp_info(काष्ठा e1000_hw *hw, u8 *buffer, u16 length);
bool e1000e_enable_mng_pass_thru(काष्ठा e1000_hw *hw);

क्रमागत e1000_mng_mode अणु
	e1000_mng_mode_none = 0,
	e1000_mng_mode_asf,
	e1000_mng_mode_pt,
	e1000_mng_mode_ipmi,
	e1000_mng_mode_host_अगर_only
पूर्ण;

#घोषणा E1000_FACTPS_MNGCG			0x20000000

#घोषणा E1000_FWSM_MODE_MASK			0xE
#घोषणा E1000_FWSM_MODE_SHIFT			1

#घोषणा E1000_MNG_IAMT_MODE			0x3
#घोषणा E1000_MNG_DHCP_COOKIE_LENGTH		0x10
#घोषणा E1000_MNG_DHCP_COOKIE_OFFSET		0x6F0
#घोषणा E1000_MNG_DHCP_COMMAND_TIMEOUT		10
#घोषणा E1000_MNG_DHCP_TX_PAYLOAD_CMD		64
#घोषणा E1000_MNG_DHCP_COOKIE_STATUS_PARSING	0x1
#घोषणा E1000_MNG_DHCP_COOKIE_STATUS_VLAN	0x2

#घोषणा E1000_VFTA_ENTRY_SHIFT			5
#घोषणा E1000_VFTA_ENTRY_MASK			0x7F
#घोषणा E1000_VFTA_ENTRY_BIT_SHIFT_MASK		0x1F

#घोषणा E1000_HICR_EN			0x01	/* Enable bit - RO */
/* Driver sets this bit when करोne to put command in RAM */
#घोषणा E1000_HICR_C			0x02
#घोषणा E1000_HICR_SV			0x04	/* Status Validity */
#घोषणा E1000_HICR_FW_RESET_ENABLE	0x40
#घोषणा E1000_HICR_FW_RESET		0x80

/* Intel(R) Active Management Technology signature */
#घोषणा E1000_IAMT_SIGNATURE		0x544D4149

#पूर्ण_अगर
