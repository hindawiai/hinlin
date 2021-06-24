<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _POWERPC_XMON_DIS_ASM_H
#घोषणा _POWERPC_XMON_DIS_ASM_H
/*
 * Copyright (C) 2006 Michael Ellerman, IBM Corporation.
 */

बाह्य व्योम prपूर्णांक_address (अचिन्हित दीर्घ memaddr);

#अगर_घोषित CONFIG_XMON_DISASSEMBLY
बाह्य पूर्णांक prपूर्णांक_insn_घातerpc(अचिन्हित दीर्घ insn, अचिन्हित दीर्घ memaddr);
बाह्य पूर्णांक prपूर्णांक_insn_spu(अचिन्हित दीर्घ insn, अचिन्हित दीर्घ memaddr);
#अन्यथा
अटल अंतरभूत पूर्णांक prपूर्णांक_insn_घातerpc(अचिन्हित दीर्घ insn, अचिन्हित दीर्घ memaddr)
अणु
	म_लिखो("%.8lx", insn);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक prपूर्णांक_insn_spu(अचिन्हित दीर्घ insn, अचिन्हित दीर्घ memaddr)
अणु
	म_लिखो("%.8lx", insn);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _POWERPC_XMON_DIS_ASM_H */
