<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __IA_CSS_SPCTRL_H__
#घोषणा __IA_CSS_SPCTRL_H__

#समावेश <प्रणाली_global.h>
#समावेश <ia_css_err.h>
#समावेश "ia_css_spctrl_comm.h"

प्रकार काष्ठा अणु
	u32        ddr_data_offset;       /**  posistion of data in DDR */
	u32        dmem_data_addr;        /** data segment address in dmem */
	u32        dmem_bss_addr;         /** bss segment address in dmem  */
	u32        data_size;             /** data segment size            */
	u32        bss_size;              /** bss segment size             */
	u32        spctrl_config_dmem_addr; /* <location of dmem_cfg  in SP dmem */
	u32        spctrl_state_dmem_addr;  /* < location of state  in SP dmem */
	अचिन्हित पूर्णांक    sp_entry;                /* < entry function ptr on SP */
	स्थिर व्योम      *code;                   /** location of firmware */
	u32         code_size;
	अक्षर      *program_name;    /** not used on hardware, only क्रम simulation */
पूर्ण ia_css_spctrl_cfg;

/* Get the code addr in DDR of SP */
ia_css_ptr get_sp_code_addr(sp_ID_t  sp_id);

/* ! Load firmware on to specfied SP
*/
पूर्णांक ia_css_spctrl_load_fw(sp_ID_t sp_id,
				      ia_css_spctrl_cfg *spctrl_cfg);

/* ISP2401 */
/*! Setup रेजिस्टरs क्रम reloading FW */
व्योम sh_css_spctrl_reload_fw(sp_ID_t sp_id);

/*!  Unload/release any memory allocated to hold the firmware
*/
पूर्णांक ia_css_spctrl_unload_fw(sp_ID_t sp_id);

/*! Intilaize dmem_cfg in SP dmem  and  start SP program
*/
पूर्णांक ia_css_spctrl_start(sp_ID_t sp_id);

/*! stop spctrl
*/
पूर्णांक ia_css_spctrl_stop(sp_ID_t sp_id);

/*! Query the state of SP
*/
ia_css_spctrl_sp_sw_state ia_css_spctrl_get_state(sp_ID_t sp_id);

/*! Check अगर SP is idle/पढ़ोy
*/
पूर्णांक ia_css_spctrl_is_idle(sp_ID_t sp_id);

#पूर्ण_अगर /* __IA_CSS_SPCTRL_H__ */
