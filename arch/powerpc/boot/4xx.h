<शैली गुरु>
/*
 * PowerPC 4xx related functions
 *
 * Copyright 2007 IBM Corporation.
 * Josh Boyer <jwboyer@linux.vnet.ibm.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#अगर_अघोषित _POWERPC_BOOT_4XX_H_
#घोषणा _POWERPC_BOOT_4XX_H_

व्योम ibm4xx_sdram_fixup_memsize(व्योम);
व्योम ibm440spe_fixup_memsize(व्योम);
व्योम ibm4xx_denali_fixup_memsize(व्योम);
व्योम ibm44x_dbcr_reset(व्योम);
व्योम ibm40x_dbcr_reset(व्योम);
व्योम ibm4xx_quiesce_eth(u32 *emac0, u32 *emac1);
व्योम ibm4xx_fixup_ebc_ranges(स्थिर अक्षर *ebc);

व्योम ibm405gp_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk, अचिन्हित पूर्णांक ser_clk);
व्योम ibm405ep_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk);
व्योम ibm405ex_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk, अचिन्हित पूर्णांक uart_clk);
व्योम ibm440gp_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk, अचिन्हित पूर्णांक ser_clk);
व्योम ibm440ep_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk, अचिन्हित पूर्णांक ser_clk,
			   अचिन्हित पूर्णांक पंचांगr_clk);
व्योम ibm440gx_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk, अचिन्हित पूर्णांक ser_clk,
			   अचिन्हित पूर्णांक पंचांगr_clk);
व्योम ibm440spe_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk, अचिन्हित पूर्णांक ser_clk,
			    अचिन्हित पूर्णांक पंचांगr_clk);

#पूर्ण_अगर /* _POWERPC_BOOT_4XX_H_ */
