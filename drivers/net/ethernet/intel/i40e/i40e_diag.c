<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "i40e_diag.h"
#समावेश "i40e_prototype.h"

/**
 * i40e_diag_reg_pattern_test
 * @hw: poपूर्णांकer to the hw काष्ठा
 * @reg: reg to be tested
 * @mask: bits to be touched
 **/
अटल i40e_status i40e_diag_reg_pattern_test(काष्ठा i40e_hw *hw,
							u32 reg, u32 mask)
अणु
	अटल स्थिर u32 patterns[] = अणु
		0x5A5A5A5A, 0xA5A5A5A5, 0x00000000, 0xFFFFFFFF
	पूर्ण;
	u32 pat, val, orig_val;
	पूर्णांक i;

	orig_val = rd32(hw, reg);
	क्रम (i = 0; i < ARRAY_SIZE(patterns); i++) अणु
		pat = patterns[i];
		wr32(hw, reg, (pat & mask));
		val = rd32(hw, reg);
		अगर ((val & mask) != (pat & mask)) अणु
			i40e_debug(hw, I40E_DEBUG_DIAG,
				   "%s: reg pattern test failed - reg 0x%08x pat 0x%08x val 0x%08x\n",
				   __func__, reg, pat, val);
			वापस I40E_ERR_DIAG_TEST_FAILED;
		पूर्ण
	पूर्ण

	wr32(hw, reg, orig_val);
	val = rd32(hw, reg);
	अगर (val != orig_val) अणु
		i40e_debug(hw, I40E_DEBUG_DIAG,
			   "%s: reg restore test failed - reg 0x%08x orig_val 0x%08x val 0x%08x\n",
			   __func__, reg, orig_val, val);
		वापस I40E_ERR_DIAG_TEST_FAILED;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा i40e_diag_reg_test_info i40e_reg_list[] = अणु
	/* offset               mask         elements   stride */
	अणुI40E_QTX_CTL(0),       0x0000FFBF, 1,
		I40E_QTX_CTL(1) - I40E_QTX_CTL(0)पूर्ण,
	अणुI40E_PFINT_ITR0(0),    0x00000FFF, 3,
		I40E_PFINT_ITR0(1) - I40E_PFINT_ITR0(0)पूर्ण,
	अणुI40E_PFINT_ITRN(0, 0), 0x00000FFF, 1,
		I40E_PFINT_ITRN(0, 1) - I40E_PFINT_ITRN(0, 0)पूर्ण,
	अणुI40E_PFINT_ITRN(1, 0), 0x00000FFF, 1,
		I40E_PFINT_ITRN(1, 1) - I40E_PFINT_ITRN(1, 0)पूर्ण,
	अणुI40E_PFINT_ITRN(2, 0), 0x00000FFF, 1,
		I40E_PFINT_ITRN(2, 1) - I40E_PFINT_ITRN(2, 0)पूर्ण,
	अणुI40E_PFINT_STAT_CTL0,  0x0000000C, 1, 0पूर्ण,
	अणुI40E_PFINT_LNKLST0,    0x00001FFF, 1, 0पूर्ण,
	अणुI40E_PFINT_LNKLSTN(0), 0x000007FF, 1,
		I40E_PFINT_LNKLSTN(1) - I40E_PFINT_LNKLSTN(0)पूर्ण,
	अणुI40E_QINT_TQCTL(0),    0x000000FF, 1,
		I40E_QINT_TQCTL(1) - I40E_QINT_TQCTL(0)पूर्ण,
	अणुI40E_QINT_RQCTL(0),    0x000000FF, 1,
		I40E_QINT_RQCTL(1) - I40E_QINT_RQCTL(0)पूर्ण,
	अणुI40E_PFINT_ICR0_ENA,   0xF7F20000, 1, 0पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/**
 * i40e_diag_reg_test
 * @hw: poपूर्णांकer to the hw काष्ठा
 *
 * Perक्रमm रेजिस्टरs diagnostic test
 **/
i40e_status i40e_diag_reg_test(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code = 0;
	u32 reg, mask;
	u32 i, j;

	क्रम (i = 0; i40e_reg_list[i].offset != 0 &&
					     !ret_code; i++) अणु

		/* set actual reg range क्रम dynamically allocated resources */
		अगर (i40e_reg_list[i].offset == I40E_QTX_CTL(0) &&
		    hw->func_caps.num_tx_qp != 0)
			i40e_reg_list[i].elements = hw->func_caps.num_tx_qp;
		अगर ((i40e_reg_list[i].offset == I40E_PFINT_ITRN(0, 0) ||
		     i40e_reg_list[i].offset == I40E_PFINT_ITRN(1, 0) ||
		     i40e_reg_list[i].offset == I40E_PFINT_ITRN(2, 0) ||
		     i40e_reg_list[i].offset == I40E_QINT_TQCTL(0) ||
		     i40e_reg_list[i].offset == I40E_QINT_RQCTL(0)) &&
		    hw->func_caps.num_msix_vectors != 0)
			i40e_reg_list[i].elements =
				hw->func_caps.num_msix_vectors - 1;

		/* test रेजिस्टर access */
		mask = i40e_reg_list[i].mask;
		क्रम (j = 0; j < i40e_reg_list[i].elements && !ret_code; j++) अणु
			reg = i40e_reg_list[i].offset +
			      (j * i40e_reg_list[i].stride);
			ret_code = i40e_diag_reg_pattern_test(hw, reg, mask);
		पूर्ण
	पूर्ण

	वापस ret_code;
पूर्ण

/**
 * i40e_diag_eeprom_test
 * @hw: poपूर्णांकer to the hw काष्ठा
 *
 * Perक्रमm EEPROM diagnostic test
 **/
i40e_status i40e_diag_eeprom_test(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code;
	u16 reg_val;

	/* पढ़ो NVM control word and अगर NVM valid, validate EEPROM checksum*/
	ret_code = i40e_पढ़ो_nvm_word(hw, I40E_SR_NVM_CONTROL_WORD, &reg_val);
	अगर (!ret_code &&
	    ((reg_val & I40E_SR_CONTROL_WORD_1_MASK) ==
	     BIT(I40E_SR_CONTROL_WORD_1_SHIFT)))
		वापस i40e_validate_nvm_checksum(hw, शून्य);
	अन्यथा
		वापस I40E_ERR_DIAG_TEST_FAILED;
पूर्ण
