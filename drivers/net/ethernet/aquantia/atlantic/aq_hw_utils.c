<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_hw_utils.c: Definitions of helper functions used across
 * hardware layer.
 */

#समावेश "aq_hw_utils.h"

#समावेश <linux/io-64-nonatomic-lo-hi.h>

#समावेश "aq_hw.h"
#समावेश "aq_nic.h"

व्योम aq_hw_ग_लिखो_reg_bit(काष्ठा aq_hw_s *aq_hw, u32 addr, u32 msk,
			 u32 shअगरt, u32 val)
अणु
	अगर (msk ^ ~0) अणु
		u32 reg_old, reg_new;

		reg_old = aq_hw_पढ़ो_reg(aq_hw, addr);
		reg_new = (reg_old & (~msk)) | (val << shअगरt);

		अगर (reg_old != reg_new)
			aq_hw_ग_लिखो_reg(aq_hw, addr, reg_new);
	पूर्ण अन्यथा अणु
		aq_hw_ग_लिखो_reg(aq_hw, addr, val);
	पूर्ण
पूर्ण

u32 aq_hw_पढ़ो_reg_bit(काष्ठा aq_hw_s *aq_hw, u32 addr, u32 msk, u32 shअगरt)
अणु
	वापस ((aq_hw_पढ़ो_reg(aq_hw, addr) & msk) >> shअगरt);
पूर्ण

u32 aq_hw_पढ़ो_reg(काष्ठा aq_hw_s *hw, u32 reg)
अणु
	u32 value = पढ़ोl(hw->mmio + reg);

	अगर (value == U32_MAX &&
	    पढ़ोl(hw->mmio + hw->aq_nic_cfg->aq_hw_caps->hw_alive_check_addr) == U32_MAX)
		aq_utils_obj_set(&hw->flags, AQ_HW_FLAG_ERR_UNPLUG);

	वापस value;
पूर्ण

व्योम aq_hw_ग_लिखो_reg(काष्ठा aq_hw_s *hw, u32 reg, u32 value)
अणु
	ग_लिखोl(value, hw->mmio + reg);
पूर्ण

/* Most of 64-bit रेजिस्टरs are in LSW, MSW क्रमm.
   Counters are normally implemented by HW as latched pairs:
   पढ़ोing LSW first locks MSW, to overcome LSW overflow
 */
u64 aq_hw_पढ़ो_reg64(काष्ठा aq_hw_s *hw, u32 reg)
अणु
	u64 value = U64_MAX;

	अगर (hw->aq_nic_cfg->aq_hw_caps->op64bit)
		value = पढ़ोq(hw->mmio + reg);
	अन्यथा
		value = lo_hi_पढ़ोq(hw->mmio + reg);

	अगर (value == U64_MAX &&
	    पढ़ोl(hw->mmio + hw->aq_nic_cfg->aq_hw_caps->hw_alive_check_addr) == U32_MAX)
		aq_utils_obj_set(&hw->flags, AQ_HW_FLAG_ERR_UNPLUG);

	वापस value;
पूर्ण

व्योम aq_hw_ग_लिखो_reg64(काष्ठा aq_hw_s *hw, u32 reg, u64 value)
अणु
	अगर (hw->aq_nic_cfg->aq_hw_caps->op64bit)
		ग_लिखोq(value, hw->mmio + reg);
	अन्यथा
		lo_hi_ग_लिखोq(value, hw->mmio + reg);
पूर्ण

पूर्णांक aq_hw_err_from_flags(काष्ठा aq_hw_s *hw)
अणु
	पूर्णांक err = 0;

	अगर (aq_utils_obj_test(&hw->flags, AQ_HW_FLAG_ERR_UNPLUG)) अणु
		err = -ENXIO;
		जाओ err_निकास;
	पूर्ण
	अगर (aq_utils_obj_test(&hw->flags, AQ_HW_FLAG_ERR_HW)) अणु
		err = -EIO;
		जाओ err_निकास;
	पूर्ण

err_निकास:
	वापस err;
पूर्ण

पूर्णांक aq_hw_num_tcs(काष्ठा aq_hw_s *hw)
अणु
	चयन (hw->aq_nic_cfg->tc_mode) अणु
	हाल AQ_TC_MODE_8TCS:
		वापस 8;
	हाल AQ_TC_MODE_4TCS:
		वापस 4;
	शेष:
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक aq_hw_q_per_tc(काष्ठा aq_hw_s *hw)
अणु
	चयन (hw->aq_nic_cfg->tc_mode) अणु
	हाल AQ_TC_MODE_8TCS:
		वापस 4;
	हाल AQ_TC_MODE_4TCS:
		वापस 8;
	शेष:
		वापस 4;
	पूर्ण
पूर्ण
