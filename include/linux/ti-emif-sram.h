<शैली गुरु>
/*
 * TI AM33XX EMIF Routines
 *
 * Copyright (C) 2016-2017 Texas Instruments Inc.
 *	Dave Gerlach
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#अगर_अघोषित __LINUX_TI_EMIF_H
#घोषणा __LINUX_TI_EMIF_H

#समावेश <linux/kbuild.h>
#समावेश <linux/types.h>
#अगर_अघोषित __ASSEMBLY__

काष्ठा emअगर_regs_amx3 अणु
	u32 emअगर_sdcfg_val;
	u32 emअगर_timing1_val;
	u32 emअगर_timing2_val;
	u32 emअगर_timing3_val;
	u32 emअगर_ref_ctrl_val;
	u32 emअगर_zqcfg_val;
	u32 emअगर_pmcr_val;
	u32 emअगर_pmcr_shdw_val;
	u32 emअगर_rd_wr_level_ramp_ctrl;
	u32 emअगर_rd_wr_exec_thresh;
	u32 emअगर_cos_config;
	u32 emअगर_priority_to_cos_mapping;
	u32 emअगर_connect_id_serv_1_map;
	u32 emअगर_connect_id_serv_2_map;
	u32 emअगर_ocp_config_val;
	u32 emअगर_lpddr2_nvm_tim;
	u32 emअगर_lpddr2_nvm_tim_shdw;
	u32 emअगर_dll_calib_ctrl_val;
	u32 emअगर_dll_calib_ctrl_val_shdw;
	u32 emअगर_ddr_phy_ctlr_1;
	u32 emअगर_ext_phy_ctrl_vals[120];
पूर्ण;

काष्ठा ti_emअगर_pm_data अणु
	व्योम __iomem *ti_emअगर_base_addr_virt;
	phys_addr_t ti_emअगर_base_addr_phys;
	अचिन्हित दीर्घ ti_emअगर_sram_config;
	काष्ठा emअगर_regs_amx3 *regs_virt;
	phys_addr_t regs_phys;
पूर्ण __packed __aligned(8);

काष्ठा ti_emअगर_pm_functions अणु
	u32 save_context;
	u32 restore_context;
	u32 run_hw_leveling;
	u32 enter_sr;
	u32 निकास_sr;
	u32 पात_sr;
पूर्ण __packed __aligned(8);

अटल अंतरभूत व्योम ti_emअगर_यंत्र_offsets(व्योम)
अणु
	DEFINE(EMIF_SDCFG_VAL_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_sdcfg_val));
	DEFINE(EMIF_TIMING1_VAL_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_timing1_val));
	DEFINE(EMIF_TIMING2_VAL_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_timing2_val));
	DEFINE(EMIF_TIMING3_VAL_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_timing3_val));
	DEFINE(EMIF_REF_CTRL_VAL_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_ref_ctrl_val));
	DEFINE(EMIF_ZQCFG_VAL_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_zqcfg_val));
	DEFINE(EMIF_PMCR_VAL_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_pmcr_val));
	DEFINE(EMIF_PMCR_SHDW_VAL_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_pmcr_shdw_val));
	DEFINE(EMIF_RD_WR_LEVEL_RAMP_CTRL_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_rd_wr_level_ramp_ctrl));
	DEFINE(EMIF_RD_WR_EXEC_THRESH_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_rd_wr_exec_thresh));
	DEFINE(EMIF_COS_CONFIG_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_cos_config));
	DEFINE(EMIF_PRIORITY_TO_COS_MAPPING_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_priority_to_cos_mapping));
	DEFINE(EMIF_CONNECT_ID_SERV_1_MAP_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_connect_id_serv_1_map));
	DEFINE(EMIF_CONNECT_ID_SERV_2_MAP_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_connect_id_serv_2_map));
	DEFINE(EMIF_OCP_CONFIG_VAL_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_ocp_config_val));
	DEFINE(EMIF_LPDDR2_NVM_TIM_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_lpddr2_nvm_tim));
	DEFINE(EMIF_LPDDR2_NVM_TIM_SHDW_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_lpddr2_nvm_tim_shdw));
	DEFINE(EMIF_DLL_CALIB_CTRL_VAL_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_dll_calib_ctrl_val));
	DEFINE(EMIF_DLL_CALIB_CTRL_VAL_SHDW_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_dll_calib_ctrl_val_shdw));
	DEFINE(EMIF_DDR_PHY_CTLR_1_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_ddr_phy_ctlr_1));
	DEFINE(EMIF_EXT_PHY_CTRL_VALS_OFFSET,
	       दुरत्व(काष्ठा emअगर_regs_amx3, emअगर_ext_phy_ctrl_vals));
	DEFINE(EMIF_REGS_AMX3_SIZE, माप(काष्ठा emअगर_regs_amx3));

	BLANK();

	DEFINE(EMIF_PM_BASE_ADDR_VIRT_OFFSET,
	       दुरत्व(काष्ठा ti_emअगर_pm_data, ti_emअगर_base_addr_virt));
	DEFINE(EMIF_PM_BASE_ADDR_PHYS_OFFSET,
	       दुरत्व(काष्ठा ti_emअगर_pm_data, ti_emअगर_base_addr_phys));
	DEFINE(EMIF_PM_CONFIG_OFFSET,
	       दुरत्व(काष्ठा ti_emअगर_pm_data, ti_emअगर_sram_config));
	DEFINE(EMIF_PM_REGS_VIRT_OFFSET,
	       दुरत्व(काष्ठा ti_emअगर_pm_data, regs_virt));
	DEFINE(EMIF_PM_REGS_PHYS_OFFSET,
	       दुरत्व(काष्ठा ti_emअगर_pm_data, regs_phys));
	DEFINE(EMIF_PM_DATA_SIZE, माप(काष्ठा ti_emअगर_pm_data));

	BLANK();

	DEFINE(EMIF_PM_SAVE_CONTEXT_OFFSET,
	       दुरत्व(काष्ठा ti_emअगर_pm_functions, save_context));
	DEFINE(EMIF_PM_RESTORE_CONTEXT_OFFSET,
	       दुरत्व(काष्ठा ti_emअगर_pm_functions, restore_context));
	DEFINE(EMIF_PM_RUN_HW_LEVELING,
	       दुरत्व(काष्ठा ti_emअगर_pm_functions, run_hw_leveling));
	DEFINE(EMIF_PM_ENTER_SR_OFFSET,
	       दुरत्व(काष्ठा ti_emअगर_pm_functions, enter_sr));
	DEFINE(EMIF_PM_EXIT_SR_OFFSET,
	       दुरत्व(काष्ठा ti_emअगर_pm_functions, निकास_sr));
	DEFINE(EMIF_PM_ABORT_SR_OFFSET,
	       दुरत्व(काष्ठा ti_emअगर_pm_functions, पात_sr));
	DEFINE(EMIF_PM_FUNCTIONS_SIZE, माप(काष्ठा ti_emअगर_pm_functions));
पूर्ण

काष्ठा gen_pool;

पूर्णांक ti_emअगर_copy_pm_function_table(काष्ठा gen_pool *sram_pool, व्योम *dst);
पूर्णांक ti_emअगर_get_mem_type(व्योम);

#पूर्ण_अगर
#पूर्ण_अगर /* __LINUX_TI_EMIF_H */
