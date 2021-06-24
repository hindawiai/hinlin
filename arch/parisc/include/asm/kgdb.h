<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * PA-RISC KGDB support
 *
 * Copyright (c) 2019 Sven Schnelle <svens@stackframe.org>
 *
 */

#अगर_अघोषित __PARISC_KGDB_H__
#घोषणा __PARISC_KGDB_H__

#घोषणा BREAK_INSTR_SIZE		4
#घोषणा PARISC_KGDB_COMPILED_BREAK_INSN	0x3ffc01f
#घोषणा PARISC_KGDB_BREAK_INSN		0x3ffa01f


#घोषणा NUMREGBYTES			माप(काष्ठा parisc_gdb_regs)
#घोषणा BUFMAX				4096

#घोषणा CACHE_FLUSH_IS_SAFE		1

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	यंत्र(".word %0" : : "i"(PARISC_KGDB_COMPILED_BREAK_INSN) : "memory");
पूर्ण

काष्ठा parisc_gdb_regs अणु
	अचिन्हित दीर्घ gpr[32];
	अचिन्हित दीर्घ sar;
	अचिन्हित दीर्घ iaoq_f;
	अचिन्हित दीर्घ iasq_f;
	अचिन्हित दीर्घ iaoq_b;
	अचिन्हित दीर्घ iasq_b;
	अचिन्हित दीर्घ eiem;
	अचिन्हित दीर्घ iir;
	अचिन्हित दीर्घ isr;
	अचिन्हित दीर्घ ior;
	अचिन्हित दीर्घ ipsw;
	अचिन्हित दीर्घ __unused0;
	अचिन्हित दीर्घ sr4;
	अचिन्हित दीर्घ sr0;
	अचिन्हित दीर्घ sr1;
	अचिन्हित दीर्घ sr2;
	अचिन्हित दीर्घ sr3;
	अचिन्हित दीर्घ sr5;
	अचिन्हित दीर्घ sr6;
	अचिन्हित दीर्घ sr7;
	अचिन्हित दीर्घ cr0;
	अचिन्हित दीर्घ pid1;
	अचिन्हित दीर्घ pid2;
	अचिन्हित दीर्घ scrccr;
	अचिन्हित दीर्घ pid3;
	अचिन्हित दीर्घ pid4;
	अचिन्हित दीर्घ cr24;
	अचिन्हित दीर्घ cr25;
	अचिन्हित दीर्घ cr26;
	अचिन्हित दीर्घ cr27;
	अचिन्हित दीर्घ cr28;
	अचिन्हित दीर्घ cr29;
	अचिन्हित दीर्घ cr30;

	u64 fr[32];
पूर्ण;

#पूर्ण_अगर
#पूर्ण_अगर
