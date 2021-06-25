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

#अगर_अघोषित __IA_CSS_SPCTRL_COMM_H__
#घोषणा __IA_CSS_SPCTRL_COMM_H__

#समावेश <type_support.h>

/* state of SP */
प्रकार क्रमागत अणु
	IA_CSS_SP_SW_TERMINATED = 0,
	IA_CSS_SP_SW_INITIALIZED,
	IA_CSS_SP_SW_CONNECTED,
	IA_CSS_SP_SW_RUNNING
पूर्ण ia_css_spctrl_sp_sw_state;

/* Structure to encapsulate required arguments क्रम
 * initialization of SP DMEM using the SP itself
 */
काष्ठा ia_css_sp_init_dmem_cfg अणु
	ia_css_ptr      ddr_data_addr;  /** data segment address in ddr  */
	u32        dmem_data_addr; /** data segment address in dmem */
	u32        dmem_bss_addr;  /** bss segment address in dmem  */
	u32        data_size;      /** data segment size            */
	u32        bss_size;       /** bss segment size             */
	sp_ID_t         sp_id;          /* <sp Id */
पूर्ण;

#घोषणा SIZE_OF_IA_CSS_SP_INIT_DMEM_CFG_STRUCT	\
	(1 * SIZE_OF_IA_CSS_PTR) +		\
	(4 * माप(uपूर्णांक32_t)) +		\
	(1 * माप(sp_ID_t))

#पूर्ण_अगर /* __IA_CSS_SPCTRL_COMM_H__ */
