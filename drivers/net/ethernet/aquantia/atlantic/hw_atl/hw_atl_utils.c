<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File hw_atl_utils.c: Definition of common functions क्रम Atlantic hardware
 * असलtraction layer.
 */

#समावेश "../aq_nic.h"
#समावेश "../aq_hw_utils.h"
#समावेश "hw_atl_utils.h"
#समावेश "hw_atl_llh.h"
#समावेश "hw_atl_llh_internal.h"

#समावेश <linux/अक्रमom.h>

#घोषणा HW_ATL_UCP_0X370_REG    0x0370U

#घोषणा HW_ATL_MIF_CMD          0x0200U
#घोषणा HW_ATL_MIF_ADDR         0x0208U
#घोषणा HW_ATL_MIF_VAL          0x020CU

#घोषणा HW_ATL_MPI_RPC_ADDR     0x0334U
#घोषणा HW_ATL_RPC_CONTROL_ADR  0x0338U
#घोषणा HW_ATL_RPC_STATE_ADR    0x033CU

#घोषणा HW_ATL_MPI_FW_VERSION	0x18
#घोषणा HW_ATL_MPI_CONTROL_ADR  0x0368U
#घोषणा HW_ATL_MPI_STATE_ADR    0x036CU

#घोषणा HW_ATL_MPI_STATE_MSK      0x00FFU
#घोषणा HW_ATL_MPI_STATE_SHIFT    0U
#घोषणा HW_ATL_MPI_SPEED_MSK      0x00FF0000U
#घोषणा HW_ATL_MPI_SPEED_SHIFT    16U
#घोषणा HW_ATL_MPI_सूचीTY_WAKE_MSK 0x02000000U

#घोषणा HW_ATL_MPI_DAISY_CHAIN_STATUS	0x704
#घोषणा HW_ATL_MPI_BOOT_EXIT_CODE	0x388

#घोषणा HW_ATL_MAC_PHY_CONTROL	0x4000
#घोषणा HW_ATL_MAC_PHY_MPI_RESET_BIT 0x1D

#घोषणा HW_ATL_FW_VER_1X 0x01050006U
#घोषणा HW_ATL_FW_VER_2X 0x02000000U
#घोषणा HW_ATL_FW_VER_3X 0x03000000U
#घोषणा HW_ATL_FW_VER_4X 0x04000000U

#घोषणा FORCE_FLASHLESS 0

क्रमागत mcp_area अणु
	MCP_AREA_CONFIG = 0x80000000,
	MCP_AREA_SETTINGS = 0x20000000,
पूर्ण;

अटल पूर्णांक hw_atl_utils_mpi_set_state(काष्ठा aq_hw_s *self,
				      क्रमागत hal_atl_utils_fw_state_e state);
अटल u32 hw_atl_utils_get_mpi_mbox_tid(काष्ठा aq_hw_s *self);
अटल u32 hw_atl_utils_mpi_get_state(काष्ठा aq_hw_s *self);
अटल u32 hw_atl_utils_mअगर_cmd_get(काष्ठा aq_hw_s *self);
अटल u32 hw_atl_utils_mअगर_addr_get(काष्ठा aq_hw_s *self);
अटल u32 hw_atl_utils_rpc_state_get(काष्ठा aq_hw_s *self);
अटल u32 aq_fw1x_rpc_get(काष्ठा aq_hw_s *self);

पूर्णांक hw_atl_utils_initfw(काष्ठा aq_hw_s *self, स्थिर काष्ठा aq_fw_ops **fw_ops)
अणु
	पूर्णांक err = 0;

	hw_atl_utils_hw_chip_features_init(self,
					   &self->chip_features);

	self->fw_ver_actual = hw_atl_utils_get_fw_version(self);

	अगर (hw_atl_utils_ver_match(HW_ATL_FW_VER_1X, self->fw_ver_actual)) अणु
		*fw_ops = &aq_fw_1x_ops;
	पूर्ण अन्यथा अगर (hw_atl_utils_ver_match(HW_ATL_FW_VER_2X, self->fw_ver_actual)) अणु
		*fw_ops = &aq_fw_2x_ops;
	पूर्ण अन्यथा अगर (hw_atl_utils_ver_match(HW_ATL_FW_VER_3X, self->fw_ver_actual)) अणु
		*fw_ops = &aq_fw_2x_ops;
	पूर्ण अन्यथा अगर (hw_atl_utils_ver_match(HW_ATL_FW_VER_4X, self->fw_ver_actual)) अणु
		*fw_ops = &aq_fw_2x_ops;
	पूर्ण अन्यथा अणु
		aq_pr_err("Bad FW version detected: %x\n",
			  self->fw_ver_actual);
		वापस -EOPNOTSUPP;
	पूर्ण
	self->aq_fw_ops = *fw_ops;
	err = self->aq_fw_ops->init(self);

	वापस err;
पूर्ण

अटल पूर्णांक hw_atl_utils_soft_reset_flb(काष्ठा aq_hw_s *self)
अणु
	u32 gsr, val;
	पूर्णांक k = 0;

	aq_hw_ग_लिखो_reg(self, 0x404, 0x40e1);
	AQ_HW_SLEEP(50);

	/* Cleanup SPI */
	val = aq_hw_पढ़ो_reg(self, 0x53C);
	aq_hw_ग_लिखो_reg(self, 0x53C, val | 0x10);

	gsr = aq_hw_पढ़ो_reg(self, HW_ATL_GLB_SOFT_RES_ADR);
	aq_hw_ग_लिखो_reg(self, HW_ATL_GLB_SOFT_RES_ADR, (gsr & 0xBFFF) | 0x8000);

	/* Kickstart MAC */
	aq_hw_ग_लिखो_reg(self, 0x404, 0x80e0);
	aq_hw_ग_लिखो_reg(self, 0x32a8, 0x0);
	aq_hw_ग_लिखो_reg(self, 0x520, 0x1);

	/* Reset SPI again because of possible पूर्णांकerrupted SPI burst */
	val = aq_hw_पढ़ो_reg(self, 0x53C);
	aq_hw_ग_लिखो_reg(self, 0x53C, val | 0x10);
	AQ_HW_SLEEP(10);
	/* Clear SPI reset state */
	aq_hw_ग_लिखो_reg(self, 0x53C, val & ~0x10);

	aq_hw_ग_लिखो_reg(self, 0x404, 0x180e0);

	क्रम (k = 0; k < 1000; k++) अणु
		u32 flb_status = aq_hw_पढ़ो_reg(self,
						HW_ATL_MPI_DAISY_CHAIN_STATUS);

		flb_status = flb_status & 0x10;
		अगर (flb_status)
			अवरोध;
		AQ_HW_SLEEP(10);
	पूर्ण
	अगर (k == 1000) अणु
		aq_pr_err("MAC kickstart failed\n");
		वापस -EIO;
	पूर्ण

	/* FW reset */
	aq_hw_ग_लिखो_reg(self, 0x404, 0x80e0);
	AQ_HW_SLEEP(50);
	aq_hw_ग_लिखो_reg(self, 0x3a0, 0x1);

	/* Kickstart PHY - skipped */

	/* Global software reset*/
	hw_atl_rx_rx_reg_res_dis_set(self, 0U);
	hw_atl_tx_tx_reg_res_dis_set(self, 0U);
	aq_hw_ग_लिखो_reg_bit(self, HW_ATL_MAC_PHY_CONTROL,
			    BIT(HW_ATL_MAC_PHY_MPI_RESET_BIT),
			    HW_ATL_MAC_PHY_MPI_RESET_BIT, 0x0);
	gsr = aq_hw_पढ़ो_reg(self, HW_ATL_GLB_SOFT_RES_ADR);
	aq_hw_ग_लिखो_reg(self, HW_ATL_GLB_SOFT_RES_ADR, (gsr & 0xBFFF) | 0x8000);

	क्रम (k = 0; k < 1000; k++) अणु
		u32 fw_state = aq_hw_पढ़ो_reg(self, HW_ATL_MPI_FW_VERSION);

		अगर (fw_state)
			अवरोध;
		AQ_HW_SLEEP(10);
	पूर्ण
	अगर (k == 1000) अणु
		aq_pr_err("FW kickstart failed\n");
		वापस -EIO;
	पूर्ण
	/* Old FW requires fixed delay after init */
	AQ_HW_SLEEP(15);

	वापस 0;
पूर्ण

अटल पूर्णांक hw_atl_utils_soft_reset_rbl(काष्ठा aq_hw_s *self)
अणु
	u32 gsr, val, rbl_status;
	पूर्णांक k;

	aq_hw_ग_लिखो_reg(self, 0x404, 0x40e1);
	aq_hw_ग_लिखो_reg(self, 0x3a0, 0x1);
	aq_hw_ग_लिखो_reg(self, 0x32a8, 0x0);

	/* Alter RBL status */
	aq_hw_ग_लिखो_reg(self, 0x388, 0xDEAD);

	/* Cleanup SPI */
	val = aq_hw_पढ़ो_reg(self, 0x53C);
	aq_hw_ग_लिखो_reg(self, 0x53C, val | 0x10);

	/* Global software reset*/
	hw_atl_rx_rx_reg_res_dis_set(self, 0U);
	hw_atl_tx_tx_reg_res_dis_set(self, 0U);
	aq_hw_ग_लिखो_reg_bit(self, HW_ATL_MAC_PHY_CONTROL,
			    BIT(HW_ATL_MAC_PHY_MPI_RESET_BIT),
			    HW_ATL_MAC_PHY_MPI_RESET_BIT, 0x0);
	gsr = aq_hw_पढ़ो_reg(self, HW_ATL_GLB_SOFT_RES_ADR);
	aq_hw_ग_लिखो_reg(self, HW_ATL_GLB_SOFT_RES_ADR,
			(gsr & 0xFFFFBFFF) | 0x8000);

	अगर (FORCE_FLASHLESS)
		aq_hw_ग_लिखो_reg(self, 0x534, 0x0);

	aq_hw_ग_लिखो_reg(self, 0x404, 0x40e0);

	/* Wait क्रम RBL boot */
	क्रम (k = 0; k < 1000; k++) अणु
		rbl_status = aq_hw_पढ़ो_reg(self, 0x388) & 0xFFFF;
		अगर (rbl_status && rbl_status != 0xDEAD)
			अवरोध;
		AQ_HW_SLEEP(10);
	पूर्ण
	अगर (!rbl_status || rbl_status == 0xDEAD) अणु
		aq_pr_err("RBL Restart failed");
		वापस -EIO;
	पूर्ण

	/* Restore NVR */
	अगर (FORCE_FLASHLESS)
		aq_hw_ग_लिखो_reg(self, 0x534, 0xA0);

	अगर (rbl_status == 0xF1A7) अणु
		aq_pr_err("No FW detected. Dynamic FW load not implemented\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	क्रम (k = 0; k < 1000; k++) अणु
		u32 fw_state = aq_hw_पढ़ो_reg(self, HW_ATL_MPI_FW_VERSION);

		अगर (fw_state)
			अवरोध;
		AQ_HW_SLEEP(10);
	पूर्ण
	अगर (k == 1000) अणु
		aq_pr_err("FW kickstart failed\n");
		वापस -EIO;
	पूर्ण
	/* Old FW requires fixed delay after init */
	AQ_HW_SLEEP(15);

	वापस 0;
पूर्ण

पूर्णांक hw_atl_utils_soft_reset(काष्ठा aq_hw_s *self)
अणु
	पूर्णांक ver = hw_atl_utils_get_fw_version(self);
	u32 boot_निकास_code = 0;
	u32 val;
	पूर्णांक k;

	क्रम (k = 0; k < 1000; ++k) अणु
		u32 flb_status = aq_hw_पढ़ो_reg(self,
						HW_ATL_MPI_DAISY_CHAIN_STATUS);
		boot_निकास_code = aq_hw_पढ़ो_reg(self,
						HW_ATL_MPI_BOOT_EXIT_CODE);
		अगर (flb_status != 0x06000000 || boot_निकास_code != 0)
			अवरोध;
	पूर्ण

	अगर (k == 1000) अणु
		aq_pr_err("Neither RBL nor FLB firmware started\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	self->rbl_enabled = (boot_निकास_code != 0);

	अगर (hw_atl_utils_ver_match(HW_ATL_FW_VER_1X, ver)) अणु
		पूर्णांक err = 0;

		/* FW 1.x may bootup in an invalid POWER state (WOL feature).
		 * We should work around this by क्रमcing its state back to DEINIT
		 */
		hw_atl_utils_mpi_set_state(self, MPI_DEINIT);
		err = पढ़ोx_poll_समयout_atomic(hw_atl_utils_mpi_get_state,
						self, val,
						(val & HW_ATL_MPI_STATE_MSK) ==
						 MPI_DEINIT,
						10, 10000U);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (hw_atl_utils_ver_match(HW_ATL_FW_VER_4X, ver)) अणु
		u64 sem_समयout = aq_hw_पढ़ो_reg(self, HW_ATL_MIF_RESET_TIMEOUT_ADR);

		/* Acquire 2 semaphores beक्रमe issuing reset क्रम FW 4.x */
		अगर (sem_समयout > 3000)
			sem_समयout = 3000;
		sem_समयout = sem_समयout * 1000;

		अगर (sem_समयout != 0) अणु
			पूर्णांक err;

			err = पढ़ोx_poll_समयout_atomic(hw_atl_sem_reset1_get, self, val,
							val == 1U, 1U, sem_समयout);
			अगर (err)
				aq_pr_err("reset sema1 timeout");

			err = पढ़ोx_poll_समयout_atomic(hw_atl_sem_reset2_get, self, val,
							val == 1U, 1U, sem_समयout);
			अगर (err)
				aq_pr_err("reset sema2 timeout");
		पूर्ण
	पूर्ण

	अगर (self->rbl_enabled)
		वापस hw_atl_utils_soft_reset_rbl(self);
	अन्यथा
		वापस hw_atl_utils_soft_reset_flb(self);
पूर्ण

पूर्णांक hw_atl_utils_fw_करोwnld_dwords(काष्ठा aq_hw_s *self, u32 a,
				  u32 *p, u32 cnt)
अणु
	पूर्णांक err = 0;
	u32 val;

	err = पढ़ोx_poll_समयout_atomic(hw_atl_sem_ram_get,
					self, val, val == 1U,
					1U, 10000U);

	अगर (err < 0) अणु
		bool is_locked;

		hw_atl_reg_glb_cpu_sem_set(self, 1U, HW_ATL_FW_SM_RAM);
		is_locked = hw_atl_sem_ram_get(self);
		अगर (!is_locked) अणु
			err = -ETIME;
			जाओ err_निकास;
		पूर्ण
	पूर्ण

	aq_hw_ग_लिखो_reg(self, HW_ATL_MIF_ADDR, a);

	क्रम (++cnt; --cnt && !err;) अणु
		aq_hw_ग_लिखो_reg(self, HW_ATL_MIF_CMD, 0x00008000U);

		अगर (ATL_HW_IS_CHIP_FEATURE(self, REVISION_B1))
			err = पढ़ोx_poll_समयout_atomic(hw_atl_utils_mअगर_addr_get,
							self, val, val != a,
							1U, 1000U);
		अन्यथा
			err = पढ़ोx_poll_समयout_atomic(hw_atl_utils_mअगर_cmd_get,
							self, val,
							!(val & 0x100),
							1U, 1000U);

		*(p++) = aq_hw_पढ़ो_reg(self, HW_ATL_MIF_VAL);
		a += 4;
	पूर्ण

	hw_atl_reg_glb_cpu_sem_set(self, 1U, HW_ATL_FW_SM_RAM);

err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक hw_atl_utils_ग_लिखो_b1_mbox(काष्ठा aq_hw_s *self, u32 addr,
				      u32 *p, u32 cnt, क्रमागत mcp_area area)
अणु
	u32 data_offset = 0;
	u32 offset = addr;
	पूर्णांक err = 0;
	u32 val;

	चयन (area) अणु
	हाल MCP_AREA_CONFIG:
		offset -= self->rpc_addr;
		अवरोध;

	हाल MCP_AREA_SETTINGS:
		offset -= self->settings_addr;
		अवरोध;
	पूर्ण

	offset = offset / माप(u32);

	क्रम (; data_offset < cnt; ++data_offset, ++offset) अणु
		aq_hw_ग_लिखो_reg(self, 0x328, p[data_offset]);
		aq_hw_ग_लिखो_reg(self, 0x32C,
				(area | (0xFFFF & (offset * 4))));
		hw_atl_mcp_up_क्रमce_पूर्णांकr_set(self, 1);
		/* 1000 बार by 10us = 10ms */
		err = पढ़ोx_poll_समयout_atomic(hw_atl_scrpad12_get,
						self, val,
						(val & 0xF0000000) !=
						area,
						10U, 10000U);

		अगर (err < 0)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hw_atl_utils_ग_लिखो_b0_mbox(काष्ठा aq_hw_s *self, u32 addr,
				      u32 *p, u32 cnt)
अणु
	u32 offset = 0;
	पूर्णांक err = 0;
	u32 val;

	aq_hw_ग_लिखो_reg(self, 0x208, addr);

	क्रम (; offset < cnt; ++offset) अणु
		aq_hw_ग_लिखो_reg(self, 0x20C, p[offset]);
		aq_hw_ग_लिखो_reg(self, 0x200, 0xC000);

		err = पढ़ोx_poll_समयout_atomic(hw_atl_utils_mअगर_cmd_get,
						self, val,
						(val & 0x100) == 0U,
						10U, 10000U);

		अगर (err < 0)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hw_atl_utils_fw_upload_dwords(काष्ठा aq_hw_s *self, u32 addr, u32 *p,
					 u32 cnt, क्रमागत mcp_area area)
अणु
	पूर्णांक err = 0;
	u32 val;

	err = पढ़ोx_poll_समयout_atomic(hw_atl_sem_ram_get, self,
					val, val == 1U,
					10U, 100000U);
	अगर (err < 0)
		जाओ err_निकास;

	अगर (ATL_HW_IS_CHIP_FEATURE(self, REVISION_B1))
		err = hw_atl_utils_ग_लिखो_b1_mbox(self, addr, p, cnt, area);
	अन्यथा
		err = hw_atl_utils_ग_लिखो_b0_mbox(self, addr, p, cnt);

	hw_atl_reg_glb_cpu_sem_set(self, 1U, HW_ATL_FW_SM_RAM);

	अगर (err < 0)
		जाओ err_निकास;

	err = aq_hw_err_from_flags(self);

err_निकास:
	वापस err;
पूर्ण

पूर्णांक hw_atl_ग_लिखो_fwcfg_dwords(काष्ठा aq_hw_s *self, u32 *p, u32 cnt)
अणु
	वापस hw_atl_utils_fw_upload_dwords(self, self->rpc_addr, p,
					     cnt, MCP_AREA_CONFIG);
पूर्ण

पूर्णांक hw_atl_ग_लिखो_fwsettings_dwords(काष्ठा aq_hw_s *self, u32 offset, u32 *p,
				   u32 cnt)
अणु
	वापस hw_atl_utils_fw_upload_dwords(self, self->settings_addr + offset,
					     p, cnt, MCP_AREA_SETTINGS);
पूर्ण

bool hw_atl_utils_ver_match(u32 ver_expected, u32 ver_actual)
अणु
	स्थिर u32 dw_major_mask = 0xff000000U;
	स्थिर u32 dw_minor_mask = 0x00ffffffU;
	bool ver_match;

	ver_match = (dw_major_mask & (ver_expected ^ ver_actual)) ? false : true;
	अगर (!ver_match)
		जाओ err_निकास;
	ver_match = ((dw_minor_mask & ver_expected) > (dw_minor_mask & ver_actual)) ?
		false : true;

err_निकास:
	वापस ver_match;
पूर्ण

अटल पूर्णांक hw_atl_utils_init_ucp(काष्ठा aq_hw_s *self,
				 स्थिर काष्ठा aq_hw_caps_s *aq_hw_caps)
अणु
	पूर्णांक err = 0;

	अगर (!aq_hw_पढ़ो_reg(self, 0x370U)) अणु
		अचिन्हित पूर्णांक rnd = 0U;
		अचिन्हित पूर्णांक ucp_0x370 = 0U;

		get_अक्रमom_bytes(&rnd, माप(अचिन्हित पूर्णांक));

		ucp_0x370 = 0x02020202U | (0xFEFEFEFEU & rnd);
		aq_hw_ग_लिखो_reg(self, HW_ATL_UCP_0X370_REG, ucp_0x370);
	पूर्ण

	hw_atl_reg_glb_cpu_scratch_scp_set(self, 0x00000000U, 25U);

	/* check 10 बार by 1ms */
	err = पढ़ोx_poll_समयout_atomic(hw_atl_scrpad25_get,
					self, self->mbox_addr,
					self->mbox_addr != 0U,
					1000U, 10000U);
	err = पढ़ोx_poll_समयout_atomic(aq_fw1x_rpc_get, self,
					self->rpc_addr,
					self->rpc_addr != 0U,
					1000U, 100000U);

	वापस err;
पूर्ण

काष्ठा aq_hw_atl_utils_fw_rpc_tid_s अणु
	जोड़ अणु
		u32 val;
		काष्ठा अणु
			u16 tid;
			u16 len;
		पूर्ण;
	पूर्ण;
पूर्ण;

#घोषणा hw_atl_utils_fw_rpc_init(_H_) hw_atl_utils_fw_rpc_रुको(_H_, शून्य)

पूर्णांक hw_atl_utils_fw_rpc_call(काष्ठा aq_hw_s *self, अचिन्हित पूर्णांक rpc_size)
अणु
	काष्ठा aq_hw_atl_utils_fw_rpc_tid_s sw;
	पूर्णांक err = 0;

	अगर (!ATL_HW_IS_CHIP_FEATURE(self, MIPS)) अणु
		err = -1;
		जाओ err_निकास;
	पूर्ण
	err = hw_atl_ग_लिखो_fwcfg_dwords(self, (u32 *)(व्योम *)&self->rpc,
					(rpc_size + माप(u32) -
					 माप(u8)) / माप(u32));
	अगर (err < 0)
		जाओ err_निकास;

	sw.tid = 0xFFFFU & (++self->rpc_tid);
	sw.len = (u16)rpc_size;
	aq_hw_ग_लिखो_reg(self, HW_ATL_RPC_CONTROL_ADR, sw.val);

err_निकास:
	वापस err;
पूर्ण

पूर्णांक hw_atl_utils_fw_rpc_रुको(काष्ठा aq_hw_s *self,
			     काष्ठा hw_atl_utils_fw_rpc **rpc)
अणु
	काष्ठा aq_hw_atl_utils_fw_rpc_tid_s sw;
	काष्ठा aq_hw_atl_utils_fw_rpc_tid_s fw;
	पूर्णांक err = 0;

	करो अणु
		sw.val = aq_hw_पढ़ो_reg(self, HW_ATL_RPC_CONTROL_ADR);

		self->rpc_tid = sw.tid;

		err = पढ़ोx_poll_समयout_atomic(hw_atl_utils_rpc_state_get,
						self, fw.val,
						sw.tid == fw.tid,
						1000U, 100000U);
		अगर (err < 0)
			जाओ err_निकास;

		err = aq_hw_err_from_flags(self);
		अगर (err < 0)
			जाओ err_निकास;

		अगर (fw.len == 0xFFFFU) अणु
			err = hw_atl_utils_fw_rpc_call(self, sw.len);
			अगर (err < 0)
				जाओ err_निकास;
		पूर्ण
	पूर्ण जबतक (sw.tid != fw.tid || 0xFFFFU == fw.len);

	अगर (rpc) अणु
		अगर (fw.len) अणु
			err =
			hw_atl_utils_fw_करोwnld_dwords(self,
						      self->rpc_addr,
						      (u32 *)(व्योम *)
						      &self->rpc,
						      (fw.len + माप(u32) -
						       माप(u8)) /
						      माप(u32));
			अगर (err < 0)
				जाओ err_निकास;
		पूर्ण

		*rpc = &self->rpc;
	पूर्ण

err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक hw_atl_utils_mpi_create(काष्ठा aq_hw_s *self)
अणु
	पूर्णांक err = 0;

	err = hw_atl_utils_init_ucp(self, self->aq_nic_cfg->aq_hw_caps);
	अगर (err < 0)
		जाओ err_निकास;

	err = hw_atl_utils_fw_rpc_init(self);
	अगर (err < 0)
		जाओ err_निकास;

err_निकास:
	वापस err;
पूर्ण

पूर्णांक hw_atl_utils_mpi_पढ़ो_mbox(काष्ठा aq_hw_s *self,
			       काष्ठा hw_atl_utils_mbox_header *pmbox)
अणु
	वापस hw_atl_utils_fw_करोwnld_dwords(self,
					     self->mbox_addr,
					     (u32 *)(व्योम *)pmbox,
					     माप(*pmbox) / माप(u32));
पूर्ण

व्योम hw_atl_utils_mpi_पढ़ो_stats(काष्ठा aq_hw_s *self,
				 काष्ठा hw_atl_utils_mbox *pmbox)
अणु
	पूर्णांक err = 0;

	err = hw_atl_utils_fw_करोwnld_dwords(self,
					    self->mbox_addr,
					    (u32 *)(व्योम *)pmbox,
					    माप(*pmbox) / माप(u32));
	अगर (err < 0)
		जाओ err_निकास;

	अगर (ATL_HW_IS_CHIP_FEATURE(self, REVISION_A0)) अणु
		अचिन्हित पूर्णांक mtu = self->aq_nic_cfg ?
					self->aq_nic_cfg->mtu : 1514U;
		pmbox->stats.ubrc = pmbox->stats.uprc * mtu;
		pmbox->stats.ubtc = pmbox->stats.uptc * mtu;
		pmbox->stats.dpc = atomic_पढ़ो(&self->dpc);
	पूर्ण अन्यथा अणु
		pmbox->stats.dpc = hw_atl_rpb_rx_dma_drop_pkt_cnt_get(self);
	पूर्ण

err_निकास:;
पूर्ण

अटल पूर्णांक hw_atl_utils_mpi_set_speed(काष्ठा aq_hw_s *self, u32 speed)
अणु
	u32 val = aq_hw_पढ़ो_reg(self, HW_ATL_MPI_CONTROL_ADR);

	val = val & ~HW_ATL_MPI_SPEED_MSK;
	val |= speed << HW_ATL_MPI_SPEED_SHIFT;
	aq_hw_ग_लिखो_reg(self, HW_ATL_MPI_CONTROL_ADR, val);

	वापस 0;
पूर्ण

अटल पूर्णांक hw_atl_utils_mpi_set_state(काष्ठा aq_hw_s *self,
				      क्रमागत hal_atl_utils_fw_state_e state)
अणु
	u32 val = aq_hw_पढ़ो_reg(self, HW_ATL_MPI_CONTROL_ADR);
	काष्ठा hw_atl_utils_mbox_header mbox;
	u32 transaction_id = 0;
	पूर्णांक err = 0;

	अगर (state == MPI_RESET) अणु
		hw_atl_utils_mpi_पढ़ो_mbox(self, &mbox);

		transaction_id = mbox.transaction_id;

		err = पढ़ोx_poll_समयout_atomic(hw_atl_utils_get_mpi_mbox_tid,
						self, mbox.transaction_id,
						transaction_id !=
						mbox.transaction_id,
						1000U, 100000U);
		अगर (err < 0)
			जाओ err_निकास;
	पूर्ण
	/* On पूर्णांकerface DEINIT we disable DW (उठाओ bit)
	 * Otherwise enable DW (clear bit)
	 */
	अगर (state == MPI_DEINIT || state == MPI_POWER)
		val |= HW_ATL_MPI_सूचीTY_WAKE_MSK;
	अन्यथा
		val &= ~HW_ATL_MPI_सूचीTY_WAKE_MSK;

	/* Set new state bits */
	val = val & ~HW_ATL_MPI_STATE_MSK;
	val |= state & HW_ATL_MPI_STATE_MSK;

	aq_hw_ग_लिखो_reg(self, HW_ATL_MPI_CONTROL_ADR, val);

err_निकास:
	वापस err;
पूर्ण

पूर्णांक hw_atl_utils_mpi_get_link_status(काष्ठा aq_hw_s *self)
अणु
	काष्ठा aq_hw_link_status_s *link_status = &self->aq_link_status;
	u32 mpi_state;
	u32 speed;

	mpi_state = hw_atl_utils_mpi_get_state(self);
	speed = mpi_state >> HW_ATL_MPI_SPEED_SHIFT;

	अगर (!speed) अणु
		link_status->mbps = 0U;
	पूर्ण अन्यथा अणु
		चयन (speed) अणु
		हाल HAL_ATLANTIC_RATE_10G:
			link_status->mbps = 10000U;
			अवरोध;

		हाल HAL_ATLANTIC_RATE_5G:
		हाल HAL_ATLANTIC_RATE_5GSR:
			link_status->mbps = 5000U;
			अवरोध;

		हाल HAL_ATLANTIC_RATE_2G5:
			link_status->mbps = 2500U;
			अवरोध;

		हाल HAL_ATLANTIC_RATE_1G:
			link_status->mbps = 1000U;
			अवरोध;

		हाल HAL_ATLANTIC_RATE_100M:
			link_status->mbps = 100U;
			अवरोध;

		शेष:
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	link_status->full_duplex = true;

	वापस 0;
पूर्ण

पूर्णांक hw_atl_utils_get_mac_permanent(काष्ठा aq_hw_s *self,
				   u8 *mac)
अणु
	u32 mac_addr[2];
	u32 efuse_addr;
	पूर्णांक err = 0;
	u32 h = 0U;
	u32 l = 0U;

	अगर (!aq_hw_पढ़ो_reg(self, HW_ATL_UCP_0X370_REG)) अणु
		अचिन्हित पूर्णांक ucp_0x370 = 0;
		अचिन्हित पूर्णांक rnd = 0;

		get_अक्रमom_bytes(&rnd, माप(अचिन्हित पूर्णांक));

		ucp_0x370 = 0x02020202 | (0xFEFEFEFE & rnd);
		aq_hw_ग_लिखो_reg(self, HW_ATL_UCP_0X370_REG, ucp_0x370);
	पूर्ण

	efuse_addr = aq_hw_पढ़ो_reg(self, 0x00000374U);

	err = hw_atl_utils_fw_करोwnld_dwords(self, efuse_addr + (40U * 4U),
					    mac_addr, ARRAY_SIZE(mac_addr));
	अगर (err < 0) अणु
		mac_addr[0] = 0U;
		mac_addr[1] = 0U;
		err = 0;
	पूर्ण अन्यथा अणु
		mac_addr[0] = __swab32(mac_addr[0]);
		mac_addr[1] = __swab32(mac_addr[1]);
	पूर्ण

	ether_addr_copy(mac, (u8 *)mac_addr);

	अगर ((mac[0] & 0x01U) || ((mac[0] | mac[1] | mac[2]) == 0x00U)) अणु
		/* chip revision */
		l = 0xE3000000U |
		    (0xFFFFU & aq_hw_पढ़ो_reg(self, HW_ATL_UCP_0X370_REG)) |
		    (0x00 << 16);
		h = 0x8001300EU;

		mac[5] = (u8)(0xFFU & l);
		l >>= 8;
		mac[4] = (u8)(0xFFU & l);
		l >>= 8;
		mac[3] = (u8)(0xFFU & l);
		l >>= 8;
		mac[2] = (u8)(0xFFU & l);
		mac[1] = (u8)(0xFFU & h);
		h >>= 8;
		mac[0] = (u8)(0xFFU & h);
	पूर्ण

	वापस err;
पूर्ण

अचिन्हित पूर्णांक hw_atl_utils_mbps_2_speed_index(अचिन्हित पूर्णांक mbps)
अणु
	अचिन्हित पूर्णांक ret = 0U;

	चयन (mbps) अणु
	हाल 100U:
		ret = 5U;
		अवरोध;

	हाल 1000U:
		ret = 4U;
		अवरोध;

	हाल 2500U:
		ret = 3U;
		अवरोध;

	हाल 5000U:
		ret = 1U;
		अवरोध;

	हाल 10000U:
		ret = 0U;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

व्योम hw_atl_utils_hw_chip_features_init(काष्ठा aq_hw_s *self, u32 *p)
अणु
	u32 val = hw_atl_reg_glb_mअगर_id_get(self);
	u32 mअगर_rev = val & 0xFFU;
	u32 chip_features = 0U;

	chip_features |= ATL_HW_CHIP_ATLANTIC;

	अगर ((0xFU & mअगर_rev) == 1U) अणु
		chip_features |= ATL_HW_CHIP_REVISION_A0 |
			ATL_HW_CHIP_MPI_AQ |
			ATL_HW_CHIP_MIPS;
	पूर्ण अन्यथा अगर ((0xFU & mअगर_rev) == 2U) अणु
		chip_features |= ATL_HW_CHIP_REVISION_B0 |
			ATL_HW_CHIP_MPI_AQ |
			ATL_HW_CHIP_MIPS |
			ATL_HW_CHIP_TPO2 |
			ATL_HW_CHIP_RPF2;
	पूर्ण अन्यथा अगर ((0xFU & mअगर_rev) == 0xAU) अणु
		chip_features |= ATL_HW_CHIP_REVISION_B1 |
			ATL_HW_CHIP_MPI_AQ |
			ATL_HW_CHIP_MIPS |
			ATL_HW_CHIP_TPO2 |
			ATL_HW_CHIP_RPF2;
	पूर्ण

	*p = chip_features;
पूर्ण

अटल पूर्णांक hw_atl_fw1x_deinit(काष्ठा aq_hw_s *self)
अणु
	hw_atl_utils_mpi_set_speed(self, 0);
	hw_atl_utils_mpi_set_state(self, MPI_DEINIT);

	वापस 0;
पूर्ण

पूर्णांक hw_atl_utils_update_stats(काष्ठा aq_hw_s *self)
अणु
	काष्ठा aq_stats_s *cs = &self->curr_stats;
	काष्ठा hw_atl_utils_mbox mbox;

	hw_atl_utils_mpi_पढ़ो_stats(self, &mbox);

#घोषणा AQ_SDELTA(_N_) (self->curr_stats._N_ += \
			mbox.stats._N_ - self->last_stats._N_)

	अगर (self->aq_link_status.mbps) अणु
		AQ_SDELTA(uprc);
		AQ_SDELTA(mprc);
		AQ_SDELTA(bprc);
		AQ_SDELTA(erpt);

		AQ_SDELTA(uptc);
		AQ_SDELTA(mptc);
		AQ_SDELTA(bptc);
		AQ_SDELTA(erpr);

		AQ_SDELTA(ubrc);
		AQ_SDELTA(ubtc);
		AQ_SDELTA(mbrc);
		AQ_SDELTA(mbtc);
		AQ_SDELTA(bbrc);
		AQ_SDELTA(bbtc);
		AQ_SDELTA(dpc);
	पूर्ण
#अघोषित AQ_SDELTA

	cs->dma_pkt_rc = hw_atl_stats_rx_dma_good_pkt_counter_get(self);
	cs->dma_pkt_tc = hw_atl_stats_tx_dma_good_pkt_counter_get(self);
	cs->dma_oct_rc = hw_atl_stats_rx_dma_good_octet_counter_get(self);
	cs->dma_oct_tc = hw_atl_stats_tx_dma_good_octet_counter_get(self);

	स_नकल(&self->last_stats, &mbox.stats, माप(mbox.stats));

	वापस 0;
पूर्ण

काष्ठा aq_stats_s *hw_atl_utils_get_hw_stats(काष्ठा aq_hw_s *self)
अणु
	वापस &self->curr_stats;
पूर्ण

अटल स्थिर u32 hw_atl_utils_hw_mac_regs[] = अणु
	0x00005580U, 0x00005590U, 0x000055B0U, 0x000055B4U,
	0x000055C0U, 0x00005B00U, 0x00005B04U, 0x00005B08U,
	0x00005B0CU, 0x00005B10U, 0x00005B14U, 0x00005B18U,
	0x00005B1CU, 0x00005B20U, 0x00005B24U, 0x00005B28U,
	0x00005B2CU, 0x00005B30U, 0x00005B34U, 0x00005B38U,
	0x00005B3CU, 0x00005B40U, 0x00005B44U, 0x00005B48U,
	0x00005B4CU, 0x00005B50U, 0x00005B54U, 0x00005B58U,
	0x00005B5CU, 0x00005B60U, 0x00005B64U, 0x00005B68U,
	0x00005B6CU, 0x00005B70U, 0x00005B74U, 0x00005B78U,
	0x00005B7CU, 0x00007C00U, 0x00007C04U, 0x00007C08U,
	0x00007C0CU, 0x00007C10U, 0x00007C14U, 0x00007C18U,
	0x00007C1CU, 0x00007C20U, 0x00007C40U, 0x00007C44U,
	0x00007C48U, 0x00007C4CU, 0x00007C50U, 0x00007C54U,
	0x00007C58U, 0x00007C5CU, 0x00007C60U, 0x00007C80U,
	0x00007C84U, 0x00007C88U, 0x00007C8CU, 0x00007C90U,
	0x00007C94U, 0x00007C98U, 0x00007C9CU, 0x00007CA0U,
	0x00007CC0U, 0x00007CC4U, 0x00007CC8U, 0x00007CCCU,
	0x00007CD0U, 0x00007CD4U, 0x00007CD8U, 0x00007CDCU,
	0x00007CE0U, 0x00000300U, 0x00000304U, 0x00000308U,
	0x0000030cU, 0x00000310U, 0x00000314U, 0x00000318U,
	0x0000031cU, 0x00000360U, 0x00000364U, 0x00000368U,
	0x0000036cU, 0x00000370U, 0x00000374U, 0x00006900U,
पूर्ण;

पूर्णांक hw_atl_utils_hw_get_regs(काष्ठा aq_hw_s *self,
			     स्थिर काष्ठा aq_hw_caps_s *aq_hw_caps,
			     u32 *regs_buff)
अणु
	अचिन्हित पूर्णांक i = 0U;

	क्रम (i = 0; i < aq_hw_caps->mac_regs_count; i++)
		regs_buff[i] = aq_hw_पढ़ो_reg(self,
					      hw_atl_utils_hw_mac_regs[i]);

	वापस 0;
पूर्ण

u32 hw_atl_utils_get_fw_version(काष्ठा aq_hw_s *self)
अणु
	वापस aq_hw_पढ़ो_reg(self, HW_ATL_MPI_FW_VERSION);
पूर्ण

अटल पूर्णांक aq_fw1x_set_wake_magic(काष्ठा aq_hw_s *self, bool wol_enabled,
				  u8 *mac)
अणु
	काष्ठा hw_atl_utils_fw_rpc *prpc = शून्य;
	अचिन्हित पूर्णांक rpc_size = 0U;
	पूर्णांक err = 0;

	err = hw_atl_utils_fw_rpc_रुको(self, &prpc);
	अगर (err < 0)
		जाओ err_निकास;

	स_रखो(prpc, 0, माप(*prpc));

	अगर (wol_enabled) अणु
		rpc_size = दुरत्व(काष्ठा hw_atl_utils_fw_rpc, msg_wol_add) +
			   माप(prpc->msg_wol_add);


		prpc->msg_id = HAL_ATLANTIC_UTILS_FW_MSG_WOL_ADD;
		prpc->msg_wol_add.priority =
				HAL_ATLANTIC_UTILS_FW_MSG_WOL_PRIOR;
		prpc->msg_wol_add.pattern_id =
				HAL_ATLANTIC_UTILS_FW_MSG_WOL_PATTERN;
		prpc->msg_wol_add.packet_type =
				HAL_ATLANTIC_UTILS_FW_MSG_WOL_MAG_PKT;

		ether_addr_copy((u8 *)&prpc->msg_wol_add.magic_packet_pattern,
				mac);
	पूर्ण अन्यथा अणु
		rpc_size = माप(prpc->msg_wol_हटाओ) +
			   दुरत्व(काष्ठा hw_atl_utils_fw_rpc, msg_wol_हटाओ);

		prpc->msg_id = HAL_ATLANTIC_UTILS_FW_MSG_WOL_DEL;
		prpc->msg_wol_add.pattern_id =
				HAL_ATLANTIC_UTILS_FW_MSG_WOL_PATTERN;
	पूर्ण

	err = hw_atl_utils_fw_rpc_call(self, rpc_size);

err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक aq_fw1x_set_घातer(काष्ठा aq_hw_s *self, अचिन्हित पूर्णांक घातer_state,
			     u8 *mac)
अणु
	काष्ठा hw_atl_utils_fw_rpc *prpc = शून्य;
	अचिन्हित पूर्णांक rpc_size = 0U;
	पूर्णांक err = 0;

	अगर (self->aq_nic_cfg->wol & WAKE_MAGIC) अणु
		err = aq_fw1x_set_wake_magic(self, 1, mac);

		अगर (err < 0)
			जाओ err_निकास;

		rpc_size = माप(prpc->msg_id) +
			   माप(prpc->msg_enable_wakeup);

		err = hw_atl_utils_fw_rpc_रुको(self, &prpc);

		अगर (err < 0)
			जाओ err_निकास;

		स_रखो(prpc, 0, rpc_size);

		prpc->msg_id = HAL_ATLANTIC_UTILS_FW_MSG_ENABLE_WAKEUP;
		prpc->msg_enable_wakeup.pattern_mask = 0x00000002;

		err = hw_atl_utils_fw_rpc_call(self, rpc_size);
		अगर (err < 0)
			जाओ err_निकास;
	पूर्ण
	hw_atl_utils_mpi_set_speed(self, 0);
	hw_atl_utils_mpi_set_state(self, MPI_POWER);

err_निकास:
	वापस err;
पूर्ण

अटल u32 hw_atl_utils_get_mpi_mbox_tid(काष्ठा aq_hw_s *self)
अणु
	काष्ठा hw_atl_utils_mbox_header mbox;

	hw_atl_utils_mpi_पढ़ो_mbox(self, &mbox);

	वापस mbox.transaction_id;
पूर्ण

अटल u32 hw_atl_utils_mpi_get_state(काष्ठा aq_hw_s *self)
अणु
	वापस aq_hw_पढ़ो_reg(self, HW_ATL_MPI_STATE_ADR);
पूर्ण

अटल u32 hw_atl_utils_mअगर_cmd_get(काष्ठा aq_hw_s *self)
अणु
	वापस aq_hw_पढ़ो_reg(self, HW_ATL_MIF_CMD);
पूर्ण

अटल u32 hw_atl_utils_mअगर_addr_get(काष्ठा aq_hw_s *self)
अणु
	वापस aq_hw_पढ़ो_reg(self, HW_ATL_MIF_ADDR);
पूर्ण

अटल u32 hw_atl_utils_rpc_state_get(काष्ठा aq_hw_s *self)
अणु
	वापस aq_hw_पढ़ो_reg(self, HW_ATL_RPC_STATE_ADR);
पूर्ण

अटल u32 aq_fw1x_rpc_get(काष्ठा aq_hw_s *self)
अणु
	वापस aq_hw_पढ़ो_reg(self, HW_ATL_MPI_RPC_ADDR);
पूर्ण

स्थिर काष्ठा aq_fw_ops aq_fw_1x_ops = अणु
	.init = hw_atl_utils_mpi_create,
	.deinit = hw_atl_fw1x_deinit,
	.reset = शून्य,
	.get_mac_permanent = hw_atl_utils_get_mac_permanent,
	.set_link_speed = hw_atl_utils_mpi_set_speed,
	.set_state = hw_atl_utils_mpi_set_state,
	.update_link_status = hw_atl_utils_mpi_get_link_status,
	.update_stats = hw_atl_utils_update_stats,
	.get_mac_temp = शून्य,
	.get_phy_temp = शून्य,
	.set_घातer = aq_fw1x_set_घातer,
	.set_eee_rate = शून्य,
	.get_eee_rate = शून्य,
	.set_flow_control = शून्य,
	.send_fw_request = शून्य,
	.enable_ptp = शून्य,
	.led_control = शून्य,
पूर्ण;
