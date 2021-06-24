<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_SPARC64_FTRACE
#घोषणा _ASM_SPARC64_FTRACE

#अगर_घोषित CONFIG_MCOUNT
#घोषणा MCOUNT_ADDR		((अचिन्हित दीर्घ)(_mcount))
#घोषणा MCOUNT_INSN_SIZE	4 /* माप mcount call */

#अगर_अघोषित __ASSEMBLY__
व्योम _mcount(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_MCOUNT */

#अगर defined(CONFIG_SPARC64) && !defined(CC_USE_FENTRY)
#घोषणा HAVE_FUNCTION_GRAPH_FP_TEST
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
/* relocation of mcount call site is the same as the address */
अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	वापस addr;
पूर्ण

काष्ठा dyn_arch_ftrace अणु
पूर्ण;
#पूर्ण_अगर /*  CONFIG_DYNAMIC_FTRACE */

अचिन्हित दीर्घ prepare_ftrace_वापस(अचिन्हित दीर्घ parent,
				    अचिन्हित दीर्घ self_addr,
				    अचिन्हित दीर्घ frame_poपूर्णांकer);

#पूर्ण_अगर /* _ASM_SPARC64_FTRACE */
