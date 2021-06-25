<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_NOPS_H
#घोषणा _ASM_X86_NOPS_H

/*
 * Define nops क्रम use with alternative() and क्रम tracing.
 */

#अगर_अघोषित CONFIG_64BIT

/*
 * Generic 32bit nops from GAS:
 *
 * 1: nop
 * 2: movl %esi,%esi
 * 3: leal 0x0(%esi),%esi
 * 4: leal 0x0(%esi,%eiz,1),%esi
 * 5: leal %ds:0x0(%esi,%eiz,1),%esi
 * 6: leal 0x0(%esi),%esi
 * 7: leal 0x0(%esi,%eiz,1),%esi
 * 8: leal %ds:0x0(%esi,%eiz,1),%esi
 *
 * Except 5 and 8, which are DS prefixed 4 and 7 resp, where GAS would emit 2
 * nop inकाष्ठाions.
 */
#घोषणा BYTES_NOP1	0x90
#घोषणा BYTES_NOP2	0x89,0xf6
#घोषणा BYTES_NOP3	0x8d,0x76,0x00
#घोषणा BYTES_NOP4	0x8d,0x74,0x26,0x00
#घोषणा BYTES_NOP5	0x3e,BYTES_NOP4
#घोषणा BYTES_NOP6	0x8d,0xb6,0x00,0x00,0x00,0x00
#घोषणा BYTES_NOP7	0x8d,0xb4,0x26,0x00,0x00,0x00,0x00
#घोषणा BYTES_NOP8	0x3e,BYTES_NOP7

#अन्यथा

/*
 * Generic 64bit nops from GAS:
 *
 * 1: nop
 * 2: osp nop
 * 3: nopl (%eax)
 * 4: nopl 0x00(%eax)
 * 5: nopl 0x00(%eax,%eax,1)
 * 6: osp nopl 0x00(%eax,%eax,1)
 * 7: nopl 0x00000000(%eax)
 * 8: nopl 0x00000000(%eax,%eax,1)
 */
#घोषणा BYTES_NOP1	0x90
#घोषणा BYTES_NOP2	0x66,BYTES_NOP1
#घोषणा BYTES_NOP3	0x0f,0x1f,0x00
#घोषणा BYTES_NOP4	0x0f,0x1f,0x40,0x00
#घोषणा BYTES_NOP5	0x0f,0x1f,0x44,0x00,0x00
#घोषणा BYTES_NOP6	0x66,BYTES_NOP5
#घोषणा BYTES_NOP7	0x0f,0x1f,0x80,0x00,0x00,0x00,0x00
#घोषणा BYTES_NOP8	0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00

#पूर्ण_अगर /* CONFIG_64BIT */

#अगर_घोषित __ASSEMBLY__
#घोषणा _ASM_MK_NOP(x) .byte x
#अन्यथा
#घोषणा _ASM_MK_NOP(x) ".byte " __stringअगरy(x) "\n"
#पूर्ण_अगर

#घोषणा ASM_NOP1 _ASM_MK_NOP(BYTES_NOP1)
#घोषणा ASM_NOP2 _ASM_MK_NOP(BYTES_NOP2)
#घोषणा ASM_NOP3 _ASM_MK_NOP(BYTES_NOP3)
#घोषणा ASM_NOP4 _ASM_MK_NOP(BYTES_NOP4)
#घोषणा ASM_NOP5 _ASM_MK_NOP(BYTES_NOP5)
#घोषणा ASM_NOP6 _ASM_MK_NOP(BYTES_NOP6)
#घोषणा ASM_NOP7 _ASM_MK_NOP(BYTES_NOP7)
#घोषणा ASM_NOP8 _ASM_MK_NOP(BYTES_NOP8)

#घोषणा ASM_NOP_MAX 8

#अगर_अघोषित __ASSEMBLY__
बाह्य स्थिर अचिन्हित अक्षर * स्थिर x86_nops[];
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_NOPS_H */
