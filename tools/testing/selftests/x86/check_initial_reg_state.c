<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * check_initial_reg_state.c - check that execve sets the correct state
 * Copyright (c) 2014-2016 Andrew Lutomirski
 */

#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>

अचिन्हित दीर्घ ax, bx, cx, dx, si, di, bp, sp, flags;
अचिन्हित दीर्घ r8, r9, r10, r11, r12, r13, r14, r15;

यंत्र (
	".pushsection .text\n\t"
	".type real_start, @function\n\t"
	".global real_start\n\t"
	"real_start:\n\t"
#अगर_घोषित __x86_64__
	"mov %rax, ax\n\t"
	"mov %rbx, bx\n\t"
	"mov %rcx, cx\n\t"
	"mov %rdx, dx\n\t"
	"mov %rsi, si\n\t"
	"mov %rdi, di\n\t"
	"mov %rbp, bp\n\t"
	"mov %rsp, sp\n\t"
	"mov %r8, r8\n\t"
	"mov %r9, r9\n\t"
	"mov %r10, r10\n\t"
	"mov %r11, r11\n\t"
	"mov %r12, r12\n\t"
	"mov %r13, r13\n\t"
	"mov %r14, r14\n\t"
	"mov %r15, r15\n\t"
	"pushfq\n\t"
	"popq flags\n\t"
#अन्यथा
	"mov %eax, ax\n\t"
	"mov %ebx, bx\n\t"
	"mov %ecx, cx\n\t"
	"mov %edx, dx\n\t"
	"mov %esi, si\n\t"
	"mov %edi, di\n\t"
	"mov %ebp, bp\n\t"
	"mov %esp, sp\n\t"
	"pushfl\n\t"
	"popl flags\n\t"
#पूर्ण_अगर
	"jmp _start\n\t"
	".size real_start, . - real_start\n\t"
	".popsection");

पूर्णांक मुख्य()
अणु
	पूर्णांक nerrs = 0;

	अगर (sp == 0) अणु
		म_लिखो("[FAIL]\tTest was built incorrectly\n");
		वापस 1;
	पूर्ण

	अगर (ax || bx || cx || dx || si || di || bp
#अगर_घोषित __x86_64__
	    || r8 || r9 || r10 || r11 || r12 || r13 || r14 || r15
#पूर्ण_अगर
		) अणु
		म_लिखो("[FAIL]\tAll GPRs except SP should be 0\n");
#घोषणा SHOW(x) म_लिखो("\t" #x " = 0x%lx\n", x);
		SHOW(ax);
		SHOW(bx);
		SHOW(cx);
		SHOW(dx);
		SHOW(si);
		SHOW(di);
		SHOW(bp);
		SHOW(sp);
#अगर_घोषित __x86_64__
		SHOW(r8);
		SHOW(r9);
		SHOW(r10);
		SHOW(r11);
		SHOW(r12);
		SHOW(r13);
		SHOW(r14);
		SHOW(r15);
#पूर्ण_अगर
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tAll GPRs except SP are 0\n");
	पूर्ण

	अगर (flags != 0x202) अणु
		म_लिखो("[FAIL]\tFLAGS is 0x%lx, but it should be 0x202\n", flags);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tFLAGS is 0x202\n");
	पूर्ण

	वापस nerrs ? 1 : 0;
पूर्ण
