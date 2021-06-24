<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Firmware Assisted dump header file.
 *
 * Copyright 2011 IBM Corporation
 * Author: Mahesh Salgaonkar <mahesh@linux.vnet.ibm.com>
 */

#अगर_अघोषित _ASM_POWERPC_FADUMP_H
#घोषणा _ASM_POWERPC_FADUMP_H

#अगर_घोषित CONFIG_FA_DUMP

बाह्य पूर्णांक crashing_cpu;

बाह्य पूर्णांक is_fadump_memory_area(u64 addr, uदीर्घ size);
बाह्य पूर्णांक setup_fadump(व्योम);
बाह्य पूर्णांक is_fadump_active(व्योम);
बाह्य पूर्णांक should_fadump_crash(व्योम);
बाह्य व्योम crash_fadump(काष्ठा pt_regs *, स्थिर अक्षर *);
बाह्य व्योम fadump_cleanup(व्योम);

#अन्यथा	/* CONFIG_FA_DUMP */
अटल अंतरभूत पूर्णांक is_fadump_active(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक should_fadump_crash(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम crash_fadump(काष्ठा pt_regs *regs, स्थिर अक्षर *str) अणु पूर्ण
अटल अंतरभूत व्योम fadump_cleanup(व्योम) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_FA_DUMP */

#अगर defined(CONFIG_FA_DUMP) || defined(CONFIG_PRESERVE_FA_DUMP)
बाह्य पूर्णांक early_init_dt_scan_fw_dump(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				      पूर्णांक depth, व्योम *data);
बाह्य पूर्णांक fadump_reserve_mem(व्योम);
#पूर्ण_अगर
#पूर्ण_अगर /* _ASM_POWERPC_FADUMP_H */
