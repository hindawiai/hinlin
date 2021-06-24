<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "hmm.h"

#समावेश "ia_css_types.h"
#घोषणा __INLINE_SP__
#समावेश "sp.h"

#समावेश "assert_support.h"
#समावेश "ia_css_spctrl.h"
#समावेश "ia_css_debug.h"

काष्ठा spctrl_context_info अणु
	काष्ठा ia_css_sp_init_dmem_cfg dmem_config;
	u32        spctrl_config_dmem_addr; /* location of dmem_cfg  in SP dmem */
	u32        spctrl_state_dmem_addr;
	अचिन्हित पूर्णांक    sp_entry;           /* entry function ptr on SP */
	ia_css_ptr    code_addr;          /* sp firmware location in host mem-DDR*/
	u32        code_size;
	अक्षर           *program_name;       /* used in हाल of PLATFORM_SIM */
पूर्ण;

अटल काष्ठा spctrl_context_info spctrl_cofig_info[N_SP_ID];
अटल bool spctrl_loaded[N_SP_ID] = अणु0पूर्ण;

/* Load firmware */
पूर्णांक ia_css_spctrl_load_fw(sp_ID_t sp_id, ia_css_spctrl_cfg *spctrl_cfg)
अणु
	ia_css_ptr code_addr = mmgr_शून्य;
	काष्ठा ia_css_sp_init_dmem_cfg *init_dmem_cfg;

	अगर ((sp_id >= N_SP_ID) || (!spctrl_cfg))
		वापस -EINVAL;

	spctrl_cofig_info[sp_id].code_addr = mmgr_शून्य;

	init_dmem_cfg = &spctrl_cofig_info[sp_id].dmem_config;
	init_dmem_cfg->dmem_data_addr = spctrl_cfg->dmem_data_addr;
	init_dmem_cfg->dmem_bss_addr  = spctrl_cfg->dmem_bss_addr;
	init_dmem_cfg->data_size      = spctrl_cfg->data_size;
	init_dmem_cfg->bss_size       = spctrl_cfg->bss_size;
	init_dmem_cfg->sp_id          = sp_id;

	spctrl_cofig_info[sp_id].spctrl_config_dmem_addr =
	    spctrl_cfg->spctrl_config_dmem_addr;
	spctrl_cofig_info[sp_id].spctrl_state_dmem_addr =
	    spctrl_cfg->spctrl_state_dmem_addr;

	/* store code (text + icache) and data to DDR
	 *
	 * Data used to be stored separately, because of access alignment स्थिरraपूर्णांकs,
	 * fix the FW generation instead
	 */
	code_addr = hmm_alloc(spctrl_cfg->code_size, HMM_BO_PRIVATE, 0, शून्य, 0);
	अगर (code_addr == mmgr_शून्य)
		वापस -ENOMEM;
	hmm_store(code_addr, spctrl_cfg->code, spctrl_cfg->code_size);

	अगर (माप(ia_css_ptr) > माप(hrt_data)) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_ERROR,
				    "size of ia_css_ptr can not be greater than hrt_data\n");
		hmm_मुक्त(code_addr);
		code_addr = mmgr_शून्य;
		वापस -EINVAL;
	पूर्ण

	init_dmem_cfg->ddr_data_addr  = code_addr + spctrl_cfg->ddr_data_offset;
	अगर ((init_dmem_cfg->ddr_data_addr % HIVE_ISP_DDR_WORD_BYTES) != 0) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_ERROR,
				    "DDR address pointer is not properly aligned for DMA transfer\n");
		hmm_मुक्त(code_addr);
		code_addr = mmgr_शून्य;
		वापस -EINVAL;
	पूर्ण

	spctrl_cofig_info[sp_id].sp_entry = spctrl_cfg->sp_entry;
	spctrl_cofig_info[sp_id].code_addr = code_addr;
	spctrl_cofig_info[sp_id].program_name = spctrl_cfg->program_name;

	/* now we program the base address पूर्णांकo the icache and
	 * invalidate the cache.
	 */
	sp_ctrl_store(sp_id, SP_ICACHE_ADDR_REG,
		      (hrt_data)spctrl_cofig_info[sp_id].code_addr);
	sp_ctrl_setbit(sp_id, SP_ICACHE_INV_REG, SP_ICACHE_INV_BIT);
	spctrl_loaded[sp_id] = true;
	वापस 0;
पूर्ण

/* ISP2401 */
/* reload pre-loaded FW */
व्योम sh_css_spctrl_reload_fw(sp_ID_t sp_id)
अणु
	/* now we program the base address पूर्णांकo the icache and
	 * invalidate the cache.
	 */
	sp_ctrl_store(sp_id, SP_ICACHE_ADDR_REG,
		      (hrt_data)spctrl_cofig_info[sp_id].code_addr);
	sp_ctrl_setbit(sp_id, SP_ICACHE_INV_REG, SP_ICACHE_INV_BIT);
	spctrl_loaded[sp_id] = true;
पूर्ण

ia_css_ptr get_sp_code_addr(sp_ID_t  sp_id)
अणु
	वापस spctrl_cofig_info[sp_id].code_addr;
पूर्ण

पूर्णांक ia_css_spctrl_unload_fw(sp_ID_t sp_id)
अणु
	अगर ((sp_id >= N_SP_ID) || ((sp_id < N_SP_ID) && (!spctrl_loaded[sp_id])))
		वापस -EINVAL;

	/*  मुक्तup the resource */
	अगर (spctrl_cofig_info[sp_id].code_addr) अणु
		hmm_मुक्त(spctrl_cofig_info[sp_id].code_addr);
		spctrl_cofig_info[sp_id].code_addr = mmgr_शून्य;
	पूर्ण
	spctrl_loaded[sp_id] = false;
	वापस 0;
पूर्ण

/* Initialize dmem_cfg in SP dmem  and  start SP program*/
पूर्णांक ia_css_spctrl_start(sp_ID_t sp_id)
अणु
	अगर ((sp_id >= N_SP_ID) || ((sp_id < N_SP_ID) && (!spctrl_loaded[sp_id])))
		वापस -EINVAL;

	/* Set descr in the SP to initialize the SP DMEM */
	/*
	 * The FW stores user-space poपूर्णांकers to the FW, the ISP poपूर्णांकer
	 * is only available here
	 *
	 */
	निश्चित(माप(अचिन्हित पूर्णांक) <= माप(hrt_data));

	sp_dmem_store(sp_id,
		      spctrl_cofig_info[sp_id].spctrl_config_dmem_addr,
		      &spctrl_cofig_info[sp_id].dmem_config,
		      माप(spctrl_cofig_info[sp_id].dmem_config));
	/* set the start address */
	sp_ctrl_store(sp_id, SP_START_ADDR_REG,
		      (hrt_data)spctrl_cofig_info[sp_id].sp_entry);
	sp_ctrl_setbit(sp_id, SP_SC_REG, SP_RUN_BIT);
	sp_ctrl_setbit(sp_id, SP_SC_REG, SP_START_BIT);
	वापस 0;
पूर्ण

/* Query the state of SP1 */
ia_css_spctrl_sp_sw_state ia_css_spctrl_get_state(sp_ID_t sp_id)
अणु
	ia_css_spctrl_sp_sw_state state = 0;
	अचिन्हित पूर्णांक HIVE_ADDR_sp_sw_state;

	अगर (sp_id >= N_SP_ID)
		वापस IA_CSS_SP_SW_TERMINATED;

	HIVE_ADDR_sp_sw_state = spctrl_cofig_info[sp_id].spctrl_state_dmem_addr;
	(व्योम)HIVE_ADDR_sp_sw_state; /* Suppres warnings in CRUN */
	अगर (sp_id == SP0_ID)
		state = sp_dmem_load_uपूर्णांक32(sp_id, (अचिन्हित पूर्णांक)sp_address_of(sp_sw_state));
	वापस state;
पूर्ण

पूर्णांक ia_css_spctrl_is_idle(sp_ID_t sp_id)
अणु
	पूर्णांक state = 0;

	निश्चित(sp_id < N_SP_ID);

	state = sp_ctrl_getbit(sp_id, SP_SC_REG, SP_IDLE_BIT);
	वापस state;
पूर्ण
