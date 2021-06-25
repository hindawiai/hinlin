<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Defines of the MIPS boards specअगरic address-MAP, रेजिस्टरs, etc.
 *
 * Copyright (C) 2000,2012 MIPS Technologies, Inc.
 * All rights reserved.
 * Authors: Carsten Langgaard <carstenl@mips.com>
 *          Steven J. Hill <sjhill@mips.com>
 */
#अगर_अघोषित __ASM_MIPS_BOARDS_GENERIC_H
#घोषणा __ASM_MIPS_BOARDS_GENERIC_H

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/mips-boards/bonito64.h>

/*
 * Display रेजिस्टर base.
 */
#घोषणा ASCII_DISPLAY_WORD_BASE	   0x1f000410
#घोषणा ASCII_DISPLAY_POS_BASE	   0x1f000418

/*
 * Revision रेजिस्टर.
 */
#घोषणा MIPS_REVISION_REG		   0x1fc00010
#घोषणा MIPS_REVISION_CORID_QED_RM5261	   0
#घोषणा MIPS_REVISION_CORID_CORE_LV	   1
#घोषणा MIPS_REVISION_CORID_BONITO64	   2
#घोषणा MIPS_REVISION_CORID_CORE_20K	   3
#घोषणा MIPS_REVISION_CORID_CORE_FPGA	   4
#घोषणा MIPS_REVISION_CORID_CORE_MSC	   5
#घोषणा MIPS_REVISION_CORID_CORE_EMUL	   6
#घोषणा MIPS_REVISION_CORID_CORE_FPGA2	   7
#घोषणा MIPS_REVISION_CORID_CORE_FPGAR2	   8
#घोषणा MIPS_REVISION_CORID_CORE_FPGA3	   9
#घोषणा MIPS_REVISION_CORID_CORE_24K	   10
#घोषणा MIPS_REVISION_CORID_CORE_FPGA4	   11
#घोषणा MIPS_REVISION_CORID_CORE_FPGA5	   12

/**** Artअगरicial corid defines ****/
/*
 *  CoreEMUL with   Bonito   System Controller is treated like a Core20K
 *  CoreEMUL with SOC-it 101 System Controller is treated like a CoreMSC
 */
#घोषणा MIPS_REVISION_CORID_CORE_EMUL_BON  -1
#घोषणा MIPS_REVISION_CORID_CORE_EMUL_MSC  -2

#घोषणा MIPS_REVISION_CORID (((*(अस्थिर u32 *)ioremap(MIPS_REVISION_REG, 4)) >> 10) & 0x3f)

#घोषणा MIPS_REVISION_SCON_OTHER	   0
#घोषणा MIPS_REVISION_SCON_SOCITSC	   1
#घोषणा MIPS_REVISION_SCON_SOCITSCP	   2

/* Artअगरicial SCON defines क्रम MIPS_REVISION_SCON_OTHER */
#घोषणा MIPS_REVISION_SCON_UNKNOWN	   -1
#घोषणा MIPS_REVISION_SCON_GT64120	   -2
#घोषणा MIPS_REVISION_SCON_BONITO	   -3
#घोषणा MIPS_REVISION_SCON_BRTL		   -4
#घोषणा MIPS_REVISION_SCON_SOCIT	   -5
#घोषणा MIPS_REVISION_SCON_ROCIT	   -6

#घोषणा MIPS_REVISION_SCONID (((*(अस्थिर u32 *)ioremap(MIPS_REVISION_REG, 4)) >> 24) & 0xff)

बाह्य पूर्णांक mips_revision_sconid;

#अगर_घोषित CONFIG_PCI
बाह्य व्योम mips_pcibios_init(व्योम);
#अन्यथा
#घोषणा mips_pcibios_init() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

बाह्य व्योम mips_scroll_message(व्योम);
बाह्य व्योम mips_display_message(स्थिर अक्षर *str);

#पूर्ण_अगर	/* __ASM_MIPS_BOARDS_GENERIC_H */
