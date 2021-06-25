<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ARM PL353 SMC Driver Header
 *
 * Copyright (C) 2012 - 2018 Xilinx, Inc
 */

#अगर_अघोषित __LINUX_PL353_SMC_H
#घोषणा __LINUX_PL353_SMC_H

क्रमागत pl353_smc_ecc_mode अणु
	PL353_SMC_ECCMODE_BYPASS = 0,
	PL353_SMC_ECCMODE_APB = 1,
	PL353_SMC_ECCMODE_MEM = 2
पूर्ण;

क्रमागत pl353_smc_mem_width अणु
	PL353_SMC_MEM_WIDTH_8 = 0,
	PL353_SMC_MEM_WIDTH_16 = 1
पूर्ण;

u32 pl353_smc_get_ecc_val(पूर्णांक ecc_reg);
bool pl353_smc_ecc_is_busy(व्योम);
पूर्णांक pl353_smc_get_nand_पूर्णांक_status_raw(व्योम);
व्योम pl353_smc_clr_nand_पूर्णांक(व्योम);
पूर्णांक pl353_smc_set_ecc_mode(क्रमागत pl353_smc_ecc_mode mode);
पूर्णांक pl353_smc_set_ecc_pg_size(अचिन्हित पूर्णांक pg_sz);
पूर्णांक pl353_smc_set_buswidth(अचिन्हित पूर्णांक bw);
व्योम pl353_smc_set_cycles(u32 timings[]);
#पूर्ण_अगर
