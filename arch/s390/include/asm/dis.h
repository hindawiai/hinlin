<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Disassemble s390 inकाष्ठाions.
 *
 * Copyright IBM Corp. 2007
 * Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 */

#अगर_अघोषित __ASM_S390_DIS_H__
#घोषणा __ASM_S390_DIS_H__

#समावेश <यंत्र/dis-defs.h>

अटल अंतरभूत पूर्णांक insn_length(अचिन्हित अक्षर code)
अणु
	वापस ((((पूर्णांक) code + 64) >> 7) + 1) << 1;
पूर्ण

काष्ठा pt_regs;

व्योम show_code(काष्ठा pt_regs *regs);
व्योम prपूर्णांक_fn_code(अचिन्हित अक्षर *code, अचिन्हित दीर्घ len);
काष्ठा s390_insn *find_insn(अचिन्हित अक्षर *code);

अटल अंतरभूत पूर्णांक is_known_insn(अचिन्हित अक्षर *code)
अणु
	वापस !!find_insn(code);
पूर्ण

#पूर्ण_अगर /* __ASM_S390_DIS_H__ */
