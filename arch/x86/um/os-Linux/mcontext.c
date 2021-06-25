<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <sys/ucontext.h>
#घोषणा __FRAME_OFFSETS
#समावेश <यंत्र/ptrace.h>
#समावेश <sysdep/ptrace.h>

व्योम get_regs_from_mc(काष्ठा uml_pt_regs *regs, mcontext_t *mc)
अणु
#अगर_घोषित __i386__
#घोषणा COPY2(X,Y) regs->gp[X] = mc->gregs[REG_##Y]
#घोषणा COPY(X) regs->gp[X] = mc->gregs[REG_##X]
#घोषणा COPY_SEG(X) regs->gp[X] = mc->gregs[REG_##X] & 0xffff;
#घोषणा COPY_SEG_CPL3(X) regs->gp[X] = (mc->gregs[REG_##X] & 0xffff) | 3;
	COPY_SEG(GS); COPY_SEG(FS); COPY_SEG(ES); COPY_SEG(DS);
	COPY(EDI); COPY(ESI); COPY(EBP);
	COPY2(UESP, ESP); /* sic */
	COPY(EBX); COPY(EDX); COPY(ECX); COPY(EAX);
	COPY(EIP); COPY_SEG_CPL3(CS); COPY(EFL); COPY_SEG_CPL3(SS);
#अन्यथा
#घोषणा COPY2(X,Y) regs->gp[X/माप(अचिन्हित दीर्घ)] = mc->gregs[REG_##Y]
#घोषणा COPY(X) regs->gp[X/माप(अचिन्हित दीर्घ)] = mc->gregs[REG_##X]
	COPY(R8); COPY(R9); COPY(R10); COPY(R11);
	COPY(R12); COPY(R13); COPY(R14); COPY(R15);
	COPY(RDI); COPY(RSI); COPY(RBP); COPY(RBX);
	COPY(RDX); COPY(RAX); COPY(RCX); COPY(RSP);
	COPY(RIP);
	COPY2(EFLAGS, EFL);
	COPY2(CS, CSGSFS);
	regs->gp[CS / माप(अचिन्हित दीर्घ)] &= 0xffff;
	regs->gp[CS / माप(अचिन्हित दीर्घ)] |= 3;
#पूर्ण_अगर
पूर्ण
