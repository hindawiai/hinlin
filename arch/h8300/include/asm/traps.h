<शैली गुरु>
/*
 *  linux/include/यंत्र-h8300/traps.h
 *
 *  Copyright (C) 2003 Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _H8300_TRAPS_H
#घोषणा _H8300_TRAPS_H

बाह्य व्योम _प्रणाली_call(व्योम);
बाह्य व्योम _पूर्णांकerrupt_entry(व्योम);
बाह्य व्योम _trace_अवरोध(व्योम);
बाह्य व्योम _nmi(व्योम);
बाह्य व्योम _पूर्णांकerrupt_entry(व्योम);

बाह्य अचिन्हित दीर्घ *_पूर्णांकerrupt_redirect_table;

#घोषणा JMP_OP 0x5a000000
#घोषणा JSR_OP 0x5e000000
#घोषणा VECTOR(address) ((JMP_OP)|((अचिन्हित दीर्घ)address))
#घोषणा REसूचीECT(address) ((JSR_OP)|((अचिन्हित दीर्घ)address))
#घोषणा CPU_VECTOR ((अचिन्हित दीर्घ *)0x000000)
#घोषणा ADDR_MASK (0xffffff)

#घोषणा TRACE_VEC 5

#घोषणा TRAP0_VEC 8
#घोषणा TRAP1_VEC 9
#घोषणा TRAP2_VEC 10
#घोषणा TRAP3_VEC 11

बाह्य अक्षर _start[], _etext[];
#घोषणा check_kernel_text(addr) \
	((addr >= (अचिन्हित दीर्घ)(_start)) && \
	 (addr <  (अचिन्हित दीर्घ)(_etext)) && !(addr & 1))

#पूर्ण_अगर /* _H8300_TRAPS_H */
