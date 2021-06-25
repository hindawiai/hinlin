<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _I40E_DIAG_H_
#घोषणा _I40E_DIAG_H_

#समावेश "i40e_type.h"

क्रमागत i40e_lb_mode अणु
	I40E_LB_MODE_NONE       = 0x0,
	I40E_LB_MODE_PHY_LOCAL  = I40E_AQ_LB_PHY_LOCAL,
	I40E_LB_MODE_PHY_REMOTE = I40E_AQ_LB_PHY_REMOTE,
	I40E_LB_MODE_MAC_LOCAL  = I40E_AQ_LB_MAC_LOCAL,
पूर्ण;

काष्ठा i40e_diag_reg_test_info अणु
	u32 offset;	/* the base रेजिस्टर */
	u32 mask;	/* bits that can be tested */
	u32 elements;	/* number of elements अगर array */
	u32 stride;	/* bytes between each element */
पूर्ण;

बाह्य काष्ठा i40e_diag_reg_test_info i40e_reg_list[];

i40e_status i40e_diag_reg_test(काष्ठा i40e_hw *hw);
i40e_status i40e_diag_eeprom_test(काष्ठा i40e_hw *hw);

#पूर्ण_अगर /* _I40E_DIAG_H_ */
