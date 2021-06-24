<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#समावेश <linux/iopoll.h>

#समावेश "aq_hw_utils.h"
#समावेश "hw_atl/hw_atl_utils.h"
#समावेश "hw_atl2_utils.h"
#समावेश "hw_atl2_llh.h"
#समावेश "hw_atl2_llh_internal.h"

#घोषणा HW_ATL2_FW_VER_1X          0x01000000U

#घोषणा AQ_A2_BOOT_STARTED         BIT(0x18)
#घोषणा AQ_A2_CRASH_INIT           BIT(0x1B)
#घोषणा AQ_A2_BOOT_CODE_FAILED     BIT(0x1C)
#घोषणा AQ_A2_FW_INIT_FAILED       BIT(0x1D)
#घोषणा AQ_A2_FW_INIT_COMP_SUCCESS BIT(0x1F)

#घोषणा AQ_A2_FW_BOOT_FAILED_MASK (AQ_A2_CRASH_INIT | \
				   AQ_A2_BOOT_CODE_FAILED | \
				   AQ_A2_FW_INIT_FAILED)
#घोषणा AQ_A2_FW_BOOT_COMPLETE_MASK (AQ_A2_FW_BOOT_FAILED_MASK | \
				     AQ_A2_FW_INIT_COMP_SUCCESS)

#घोषणा AQ_A2_FW_BOOT_REQ_REBOOT        BIT(0x0)
#घोषणा AQ_A2_FW_BOOT_REQ_HOST_BOOT     BIT(0x8)
#घोषणा AQ_A2_FW_BOOT_REQ_MAC_FAST_BOOT BIT(0xA)
#घोषणा AQ_A2_FW_BOOT_REQ_PHY_FAST_BOOT BIT(0xB)

पूर्णांक hw_atl2_utils_initfw(काष्ठा aq_hw_s *self, स्थिर काष्ठा aq_fw_ops **fw_ops)
अणु
	पूर्णांक err;

	self->fw_ver_actual = hw_atl2_utils_get_fw_version(self);

	अगर (hw_atl_utils_ver_match(HW_ATL2_FW_VER_1X, self->fw_ver_actual)) अणु
		*fw_ops = &aq_a2_fw_ops;
	पूर्ण अन्यथा अणु
		aq_pr_err("Bad FW version detected: %x, but continue\n",
			  self->fw_ver_actual);
		*fw_ops = &aq_a2_fw_ops;
	पूर्ण
	aq_pr_trace("Detect ATL2FW %x\n", self->fw_ver_actual);
	self->aq_fw_ops = *fw_ops;
	err = self->aq_fw_ops->init(self);

	self->chip_features |= ATL_HW_CHIP_ANTIGUA;

	वापस err;
पूर्ण

अटल bool hw_atl2_mcp_boot_complete(काष्ठा aq_hw_s *self)
अणु
	u32 rbl_status;

	rbl_status = hw_atl2_mअगर_mcp_boot_reg_get(self);
	अगर (rbl_status & AQ_A2_FW_BOOT_COMPLETE_MASK)
		वापस true;

	/* Host boot requested */
	अगर (hw_atl2_mअगर_host_req_पूर्णांक_get(self) & HW_ATL2_MCP_HOST_REQ_INT_READY)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक hw_atl2_utils_soft_reset(काष्ठा aq_hw_s *self)
अणु
	bool rbl_complete = false;
	u32 rbl_status = 0;
	u32 rbl_request;
	पूर्णांक err;

	hw_atl2_mअगर_host_req_पूर्णांक_clr(self, 0x01);
	rbl_request = AQ_A2_FW_BOOT_REQ_REBOOT;
#अगर_घोषित AQ_CFG_FAST_START
	rbl_request |= AQ_A2_FW_BOOT_REQ_MAC_FAST_BOOT;
#पूर्ण_अगर
	hw_atl2_mअगर_mcp_boot_reg_set(self, rbl_request);

	/* Wait क्रम RBL boot */
	err = पढ़ोx_poll_समयout_atomic(hw_atl2_mअगर_mcp_boot_reg_get, self,
				rbl_status,
				((rbl_status & AQ_A2_BOOT_STARTED) &&
				 (rbl_status != 0xFFFFFFFFu)),
				10, 200000);
	अगर (err) अणु
		aq_pr_err("Boot code hanged");
		जाओ err_निकास;
	पूर्ण

	err = पढ़ोx_poll_समयout_atomic(hw_atl2_mcp_boot_complete, self,
					rbl_complete,
					rbl_complete,
					10, 2000000);

	अगर (err) अणु
		aq_pr_err("FW Restart timed out");
		जाओ err_निकास;
	पूर्ण

	rbl_status = hw_atl2_mअगर_mcp_boot_reg_get(self);

	अगर (rbl_status & AQ_A2_FW_BOOT_FAILED_MASK) अणु
		err = -EIO;
		aq_pr_err("FW Restart failed");
		जाओ err_निकास;
	पूर्ण

	अगर (hw_atl2_mअगर_host_req_पूर्णांक_get(self) &
	    HW_ATL2_MCP_HOST_REQ_INT_READY) अणु
		err = -EIO;
		aq_pr_err("No FW detected. Dynamic FW load not implemented");
		जाओ err_निकास;
	पूर्ण

	अगर (self->aq_fw_ops) अणु
		err = self->aq_fw_ops->init(self);
		अगर (err) अणु
			aq_pr_err("FW Init failed");
			जाओ err_निकास;
		पूर्ण
	पूर्ण

err_निकास:
	वापस err;
पूर्ण
