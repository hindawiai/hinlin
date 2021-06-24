<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_OLPC_OFW_H
#घोषणा _ASM_X86_OLPC_OFW_H

/* index पूर्णांकo the page table containing the entry OFW occupies */
#घोषणा OLPC_OFW_PDE_NR 1022

#घोषणा OLPC_OFW_SIG 0x2057464F	/* aka "OFW " */

#अगर_घोषित CONFIG_OLPC

बाह्य bool olpc_ofw_is_installed(व्योम);

/* run an OFW command by calling पूर्णांकo the firmware */
#घोषणा olpc_ofw(name, args, res) \
	__olpc_ofw((name), ARRAY_SIZE(args), args, ARRAY_SIZE(res), res)

बाह्य पूर्णांक __olpc_ofw(स्थिर अक्षर *name, पूर्णांक nr_args, स्थिर व्योम **args, पूर्णांक nr_res,
		व्योम **res);

/* determine whether OFW is available and lives in the proper memory */
बाह्य व्योम olpc_ofw_detect(व्योम);

/* install OFW's pde permanently into the kernel's pgtable */
बाह्य व्योम setup_olpc_ofw_pgd(व्योम);

/* check अगर OFW was detected during boot */
बाह्य bool olpc_ofw_present(व्योम);

बाह्य व्योम olpc_dt_build_devicetree(व्योम);

#अन्यथा /* !CONFIG_OLPC */
अटल अंतरभूत व्योम olpc_ofw_detect(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम setup_olpc_ofw_pgd(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम olpc_dt_build_devicetree(व्योम) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_OLPC */

#पूर्ण_अगर /* _ASM_X86_OLPC_OFW_H */
