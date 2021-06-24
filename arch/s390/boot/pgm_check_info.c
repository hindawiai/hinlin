<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/boot_data.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/uv.h>
#समावेश <मानकतर्क.स>
#समावेश "boot.h"

स्थिर अक्षर hex_asc[] = "0123456789abcdef";

अटल अक्षर *as_hex(अक्षर *dst, अचिन्हित दीर्घ val, पूर्णांक pad)
अणु
	अक्षर *p, *end = p = dst + max(pad, (पूर्णांक)__fls(val | 1) / 4 + 1);

	क्रम (*p-- = 0; p >= dst; val >>= 4)
		*p-- = hex_asc[val & 0x0f];
	वापस end;
पूर्ण

अटल अक्षर *symstart(अक्षर *p)
अणु
	जबतक (*p)
		p--;
	वापस p + 1;
पूर्ण

बाह्य अक्षर _decompressor_syms_start[], _decompressor_syms_end[];
अटल noअंतरभूत अक्षर *findsym(अचिन्हित दीर्घ ip, अचिन्हित लघु *off, अचिन्हित लघु *len)
अणु
	/* symbol entries are in a क्रमm "10000 c4 startup\0" */
	अक्षर *a = _decompressor_syms_start;
	अक्षर *b = _decompressor_syms_end;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ size;
	अक्षर *pivot;
	अक्षर *endp;

	जबतक (a < b) अणु
		pivot = symstart(a + (b - a) / 2);
		start = simple_म_से_अदीर्घl(pivot, &endp, 16);
		size = simple_म_से_अदीर्घl(endp + 1, &endp, 16);
		अगर (ip < start) अणु
			b = pivot;
			जारी;
		पूर्ण
		अगर (ip > start + size) अणु
			a = pivot + म_माप(pivot) + 1;
			जारी;
		पूर्ण
		*off = ip - start;
		*len = size;
		वापस endp + 1;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल noअंतरभूत अक्षर *strsym(व्योम *ip)
अणु
	अटल अक्षर buf[64];
	अचिन्हित लघु off;
	अचिन्हित लघु len;
	अक्षर *p;

	p = findsym((अचिन्हित दीर्घ)ip, &off, &len);
	अगर (p) अणु
		म_नकलन(buf, p, माप(buf));
		/* reserve 15 bytes क्रम offset/len in symbol+0x1234/0x1234 */
		p = buf + strnlen(buf, माप(buf) - 15);
		म_नकल(p, "+0x");
		p = as_hex(p + 3, off, 0);
		म_नकल(p, "/0x");
		as_hex(p + 3, len, 0);
	पूर्ण अन्यथा अणु
		as_hex(buf, (अचिन्हित दीर्घ)ip, 16);
	पूर्ण
	वापस buf;
पूर्ण

व्योम decompressor_prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	अक्षर buf[1024] = अणु 0 पूर्ण;
	अक्षर *end = buf + माप(buf) - 1; /* make sure buf is 0 terminated */
	अचिन्हित दीर्घ pad;
	अक्षर *p = buf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	क्रम (; p < end && *fmt; fmt++) अणु
		अगर (*fmt != '%') अणु
			*p++ = *fmt;
			जारी;
		पूर्ण
		pad = है_अंक(*++fmt) ? simple_म_से_दीर्घ(fmt, (अक्षर **)&fmt, 10) : 0;
		चयन (*fmt) अणु
		हाल 's':
			p = buf + strlcat(buf, बहु_तर्क(args, अक्षर *), माप(buf));
			अवरोध;
		हाल 'p':
			अगर (*++fmt != 'S')
				जाओ out;
			p = buf + strlcat(buf, strsym(बहु_तर्क(args, व्योम *)), माप(buf));
			अवरोध;
		हाल 'l':
			अगर (*++fmt != 'x' || end - p <= max(माप(दीर्घ) * 2, pad))
				जाओ out;
			p = as_hex(p, बहु_तर्क(args, अचिन्हित दीर्घ), pad);
			अवरोध;
		हाल 'x':
			अगर (end - p <= max(माप(पूर्णांक) * 2, pad))
				जाओ out;
			p = as_hex(p, बहु_तर्क(args, अचिन्हित पूर्णांक), pad);
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
	पूर्ण
out:
	बहु_पूर्ण(args);
	sclp_early_prपूर्णांकk(buf);
पूर्ण

अटल noअंतरभूत व्योम prपूर्णांक_stacktrace(व्योम)
अणु
	काष्ठा stack_info boot_stack = अणु STACK_TYPE_TASK, BOOT_STACK_OFFSET,
					 BOOT_STACK_OFFSET + BOOT_STACK_SIZE पूर्ण;
	अचिन्हित दीर्घ sp = S390_lowcore.gpregs_save_area[15];
	bool first = true;

	decompressor_prपूर्णांकk("Call Trace:\n");
	जबतक (!(sp & 0x7) && on_stack(&boot_stack, sp, माप(काष्ठा stack_frame))) अणु
		काष्ठा stack_frame *sf = (काष्ठा stack_frame *)sp;

		decompressor_prपूर्णांकk(first ? "(sp:%016lx [<%016lx>] %pS)\n" :
					    " sp:%016lx [<%016lx>] %pS\n",
				    sp, sf->gprs[8], (व्योम *)sf->gprs[8]);
		अगर (sf->back_chain <= sp)
			अवरोध;
		sp = sf->back_chain;
		first = false;
	पूर्ण
पूर्ण

व्योम prपूर्णांक_pgm_check_info(व्योम)
अणु
	अचिन्हित दीर्घ *gpregs = (अचिन्हित दीर्घ *)S390_lowcore.gpregs_save_area;
	काष्ठा psw_bits *psw = &psw_bits(S390_lowcore.psw_save_area);

	decompressor_prपूर्णांकk("Linux version %s\n", kernel_version);
	अगर (!is_prot_virt_guest() && early_command_line[0])
		decompressor_prपूर्णांकk("Kernel command line: %s\n", early_command_line);
	decompressor_prपूर्णांकk("Kernel fault: interruption code %04x ilc:%x\n",
			    S390_lowcore.pgm_code, S390_lowcore.pgm_ilc >> 1);
	अगर (kaslr_enabled)
		decompressor_prपूर्णांकk("Kernel random base: %lx\n", __kaslr_offset);
	decompressor_prपूर्णांकk("PSW : %016lx %016lx (%pS)\n",
			    S390_lowcore.psw_save_area.mask,
			    S390_lowcore.psw_save_area.addr,
			    (व्योम *)S390_lowcore.psw_save_area.addr);
	decompressor_prपूर्णांकk(
		"      R:%x T:%x IO:%x EX:%x Key:%x M:%x W:%x P:%x AS:%x CC:%x PM:%x RI:%x EA:%x\n",
		psw->per, psw->dat, psw->io, psw->ext, psw->key, psw->mcheck,
		psw->रुको, psw->pstate, psw->as, psw->cc, psw->pm, psw->ri,
		psw->eaba);
	decompressor_prपूर्णांकk("GPRS: %016lx %016lx %016lx %016lx\n",
			    gpregs[0], gpregs[1], gpregs[2], gpregs[3]);
	decompressor_prपूर्णांकk("      %016lx %016lx %016lx %016lx\n",
			    gpregs[4], gpregs[5], gpregs[6], gpregs[7]);
	decompressor_prपूर्णांकk("      %016lx %016lx %016lx %016lx\n",
			    gpregs[8], gpregs[9], gpregs[10], gpregs[11]);
	decompressor_prपूर्णांकk("      %016lx %016lx %016lx %016lx\n",
			    gpregs[12], gpregs[13], gpregs[14], gpregs[15]);
	prपूर्णांक_stacktrace();
	decompressor_prपूर्णांकk("Last Breaking-Event-Address:\n");
	decompressor_prपूर्णांकk(" [<%016lx>] %pS\n", (अचिन्हित दीर्घ)S390_lowcore.अवरोधing_event_addr,
			    (व्योम *)S390_lowcore.अवरोधing_event_addr);
पूर्ण
