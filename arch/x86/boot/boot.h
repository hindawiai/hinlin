<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author H. Peter Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Header file क्रम the real-mode kernel code
 */

#अगर_अघोषित BOOT_BOOT_H
#घोषणा BOOT_BOOT_H

#घोषणा STACK_SIZE	1024	/* Minimum number of bytes क्रम stack */

#अगर_अघोषित __ASSEMBLY__

#समावेश <मानकतर्क.स>
#समावेश <linux/types.h>
#समावेश <linux/edd.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश "bitops.h"
#समावेश "ctype.h"
#समावेश "cpuflags.h"

/* Useful macros */
#घोषणा ARRAY_SIZE(x) (माप(x) / माप(*(x)))

बाह्य काष्ठा setup_header hdr;
बाह्य काष्ठा boot_params boot_params;

#घोषणा cpu_relax()	यंत्र अस्थिर("rep; nop")

/* Basic port I/O */
अटल अंतरभूत व्योम outb(u8 v, u16 port)
अणु
	यंत्र अस्थिर("outb %0,%1" : : "a" (v), "dN" (port));
पूर्ण
अटल अंतरभूत u8 inb(u16 port)
अणु
	u8 v;
	यंत्र अस्थिर("inb %1,%0" : "=a" (v) : "dN" (port));
	वापस v;
पूर्ण

अटल अंतरभूत व्योम outw(u16 v, u16 port)
अणु
	यंत्र अस्थिर("outw %0,%1" : : "a" (v), "dN" (port));
पूर्ण
अटल अंतरभूत u16 inw(u16 port)
अणु
	u16 v;
	यंत्र अस्थिर("inw %1,%0" : "=a" (v) : "dN" (port));
	वापस v;
पूर्ण

अटल अंतरभूत व्योम outl(u32 v, u16 port)
अणु
	यंत्र अस्थिर("outl %0,%1" : : "a" (v), "dN" (port));
पूर्ण
अटल अंतरभूत u32 inl(u16 port)
अणु
	u32 v;
	यंत्र अस्थिर("inl %1,%0" : "=a" (v) : "dN" (port));
	वापस v;
पूर्ण

अटल अंतरभूत व्योम io_delay(व्योम)
अणु
	स्थिर u16 DELAY_PORT = 0x80;
	यंत्र अस्थिर("outb %%al,%0" : : "dN" (DELAY_PORT));
पूर्ण

/* These functions are used to reference data in other segments. */

अटल अंतरभूत u16 ds(व्योम)
अणु
	u16 seg;
	यंत्र("movw %%ds,%0" : "=rm" (seg));
	वापस seg;
पूर्ण

अटल अंतरभूत व्योम set_fs(u16 seg)
अणु
	यंत्र अस्थिर("movw %0,%%fs" : : "rm" (seg));
पूर्ण
अटल अंतरभूत u16 fs(व्योम)
अणु
	u16 seg;
	यंत्र अस्थिर("movw %%fs,%0" : "=rm" (seg));
	वापस seg;
पूर्ण

अटल अंतरभूत व्योम set_gs(u16 seg)
अणु
	यंत्र अस्थिर("movw %0,%%gs" : : "rm" (seg));
पूर्ण
अटल अंतरभूत u16 gs(व्योम)
अणु
	u16 seg;
	यंत्र अस्थिर("movw %%gs,%0" : "=rm" (seg));
	वापस seg;
पूर्ण

प्रकार अचिन्हित पूर्णांक addr_t;

अटल अंतरभूत u8 rdfs8(addr_t addr)
अणु
	u8 v;
	यंत्र अस्थिर("movb %%fs:%1,%0" : "=q" (v) : "m" (*(u8 *)addr));
	वापस v;
पूर्ण
अटल अंतरभूत u16 rdfs16(addr_t addr)
अणु
	u16 v;
	यंत्र अस्थिर("movw %%fs:%1,%0" : "=r" (v) : "m" (*(u16 *)addr));
	वापस v;
पूर्ण
अटल अंतरभूत u32 rdfs32(addr_t addr)
अणु
	u32 v;
	यंत्र अस्थिर("movl %%fs:%1,%0" : "=r" (v) : "m" (*(u32 *)addr));
	वापस v;
पूर्ण

अटल अंतरभूत व्योम wrfs8(u8 v, addr_t addr)
अणु
	यंत्र अस्थिर("movb %1,%%fs:%0" : "+m" (*(u8 *)addr) : "qi" (v));
पूर्ण
अटल अंतरभूत व्योम wrfs16(u16 v, addr_t addr)
अणु
	यंत्र अस्थिर("movw %1,%%fs:%0" : "+m" (*(u16 *)addr) : "ri" (v));
पूर्ण
अटल अंतरभूत व्योम wrfs32(u32 v, addr_t addr)
अणु
	यंत्र अस्थिर("movl %1,%%fs:%0" : "+m" (*(u32 *)addr) : "ri" (v));
पूर्ण

अटल अंतरभूत u8 rdgs8(addr_t addr)
अणु
	u8 v;
	यंत्र अस्थिर("movb %%gs:%1,%0" : "=q" (v) : "m" (*(u8 *)addr));
	वापस v;
पूर्ण
अटल अंतरभूत u16 rdgs16(addr_t addr)
अणु
	u16 v;
	यंत्र अस्थिर("movw %%gs:%1,%0" : "=r" (v) : "m" (*(u16 *)addr));
	वापस v;
पूर्ण
अटल अंतरभूत u32 rdgs32(addr_t addr)
अणु
	u32 v;
	यंत्र अस्थिर("movl %%gs:%1,%0" : "=r" (v) : "m" (*(u32 *)addr));
	वापस v;
पूर्ण

अटल अंतरभूत व्योम wrgs8(u8 v, addr_t addr)
अणु
	यंत्र अस्थिर("movb %1,%%gs:%0" : "+m" (*(u8 *)addr) : "qi" (v));
पूर्ण
अटल अंतरभूत व्योम wrgs16(u16 v, addr_t addr)
अणु
	यंत्र अस्थिर("movw %1,%%gs:%0" : "+m" (*(u16 *)addr) : "ri" (v));
पूर्ण
अटल अंतरभूत व्योम wrgs32(u32 v, addr_t addr)
अणु
	यंत्र अस्थिर("movl %1,%%gs:%0" : "+m" (*(u32 *)addr) : "ri" (v));
पूर्ण

/* Note: these only वापस true/false, not a चिन्हित वापस value! */
अटल अंतरभूत bool स_भेद_fs(स्थिर व्योम *s1, addr_t s2, माप_प्रकार len)
अणु
	bool dअगरf;
	यंत्र अस्थिर("fs; repe; cmpsb" CC_SET(nz)
		     : CC_OUT(nz) (dअगरf), "+D" (s1), "+S" (s2), "+c" (len));
	वापस dअगरf;
पूर्ण
अटल अंतरभूत bool स_भेद_gs(स्थिर व्योम *s1, addr_t s2, माप_प्रकार len)
अणु
	bool dअगरf;
	यंत्र अस्थिर("gs; repe; cmpsb" CC_SET(nz)
		     : CC_OUT(nz) (dअगरf), "+D" (s1), "+S" (s2), "+c" (len));
	वापस dअगरf;
पूर्ण

/* Heap -- available क्रम dynamic lists. */
बाह्य अक्षर _end[];
बाह्य अक्षर *HEAP;
बाह्य अक्षर *heap_end;
#घोषणा RESET_HEAP() ((व्योम *)( HEAP = _end ))
अटल अंतरभूत अक्षर *__get_heap(माप_प्रकार s, माप_प्रकार a, माप_प्रकार n)
अणु
	अक्षर *पंचांगp;

	HEAP = (अक्षर *)(((माप_प्रकार)HEAP+(a-1)) & ~(a-1));
	पंचांगp = HEAP;
	HEAP += s*n;
	वापस पंचांगp;
पूर्ण
#घोषणा GET_HEAP(type, n) \
	((type *)__get_heap(माप(type),__alignof__(type),(n)))

अटल अंतरभूत bool heap_मुक्त(माप_प्रकार n)
अणु
	वापस (पूर्णांक)(heap_end-HEAP) >= (पूर्णांक)n;
पूर्ण

/* copy.S */

व्योम copy_to_fs(addr_t dst, व्योम *src, माप_प्रकार len);
व्योम *copy_from_fs(व्योम *dst, addr_t src, माप_प्रकार len);
व्योम copy_to_gs(addr_t dst, व्योम *src, माप_प्रकार len);
व्योम *copy_from_gs(व्योम *dst, addr_t src, माप_प्रकार len);

/* a20.c */
पूर्णांक enable_a20(व्योम);

/* apm.c */
पूर्णांक query_apm_bios(व्योम);

/* bioscall.c */
काष्ठा biosregs अणु
	जोड़ अणु
		काष्ठा अणु
			u32 edi;
			u32 esi;
			u32 ebp;
			u32 _esp;
			u32 ebx;
			u32 edx;
			u32 ecx;
			u32 eax;
			u32 _fsgs;
			u32 _dses;
			u32 eflags;
		पूर्ण;
		काष्ठा अणु
			u16 di, hdi;
			u16 si, hsi;
			u16 bp, hbp;
			u16 _sp, _hsp;
			u16 bx, hbx;
			u16 dx, hdx;
			u16 cx, hcx;
			u16 ax, hax;
			u16 gs, fs;
			u16 es, ds;
			u16 flags, hflags;
		पूर्ण;
		काष्ठा अणु
			u8 dil, dih, edi2, edi3;
			u8 sil, sih, esi2, esi3;
			u8 bpl, bph, ebp2, ebp3;
			u8 _spl, _sph, _esp2, _esp3;
			u8 bl, bh, ebx2, ebx3;
			u8 dl, dh, edx2, edx3;
			u8 cl, ch, ecx2, ecx3;
			u8 al, ah, eax2, eax3;
		पूर्ण;
	पूर्ण;
पूर्ण;
व्योम पूर्णांकcall(u8 पूर्णांक_no, स्थिर काष्ठा biosregs *ireg, काष्ठा biosregs *oreg);

/* cmdline.c */
पूर्णांक __cmdline_find_option(अचिन्हित दीर्घ cmdline_ptr, स्थिर अक्षर *option, अक्षर *buffer, पूर्णांक bufsize);
पूर्णांक __cmdline_find_option_bool(अचिन्हित दीर्घ cmdline_ptr, स्थिर अक्षर *option);
अटल अंतरभूत पूर्णांक cmdline_find_option(स्थिर अक्षर *option, अक्षर *buffer, पूर्णांक bufsize)
अणु
	अचिन्हित दीर्घ cmd_line_ptr = boot_params.hdr.cmd_line_ptr;

	अगर (cmd_line_ptr >= 0x100000)
		वापस -1;      /* inaccessible */

	वापस __cmdline_find_option(cmd_line_ptr, option, buffer, bufsize);
पूर्ण

अटल अंतरभूत पूर्णांक cmdline_find_option_bool(स्थिर अक्षर *option)
अणु
	अचिन्हित दीर्घ cmd_line_ptr = boot_params.hdr.cmd_line_ptr;

	अगर (cmd_line_ptr >= 0x100000)
		वापस -1;      /* inaccessible */

	वापस __cmdline_find_option_bool(cmd_line_ptr, option);
पूर्ण

/* cpu.c, cpucheck.c */
पूर्णांक check_cpu(पूर्णांक *cpu_level_ptr, पूर्णांक *req_level_ptr, u32 **err_flags_ptr);
पूर्णांक check_knl_erratum(व्योम);
पूर्णांक validate_cpu(व्योम);

/* early_serial_console.c */
बाह्य पूर्णांक early_serial_base;
व्योम console_init(व्योम);

/* edd.c */
व्योम query_edd(व्योम);

/* header.S */
व्योम __attribute__((noवापस)) die(व्योम);

/* memory.c */
व्योम detect_memory(व्योम);

/* pm.c */
व्योम __attribute__((noवापस)) go_to_रक्षित_mode(व्योम);

/* pmjump.S */
व्योम __attribute__((noवापस))
	रक्षित_mode_jump(u32 entrypoपूर्णांक, u32 bootparams);

/* म_लिखो.c */
पूर्णांक प्र_लिखो(अक्षर *buf, स्थिर अक्षर *fmt, ...);
पूर्णांक भम_लिखो(अक्षर *buf, स्थिर अक्षर *fmt, बहु_सूची args);
पूर्णांक म_लिखो(स्थिर अक्षर *fmt, ...);

/* regs.c */
व्योम initregs(काष्ठा biosregs *regs);

/* string.c */
पूर्णांक म_भेद(स्थिर अक्षर *str1, स्थिर अक्षर *str2);
पूर्णांक म_भेदन(स्थिर अक्षर *cs, स्थिर अक्षर *ct, माप_प्रकार count);
माप_प्रकार strnlen(स्थिर अक्षर *s, माप_प्रकार maxlen);
अचिन्हित पूर्णांक atou(स्थिर अक्षर *s);
अचिन्हित दीर्घ दीर्घ simple_म_से_अदीर्घl(स्थिर अक्षर *cp, अक्षर **endp, अचिन्हित पूर्णांक base);
माप_प्रकार म_माप(स्थिर अक्षर *s);
अक्षर *म_अक्षर(स्थिर अक्षर *s, पूर्णांक c);

/* tty.c */
व्योम माला_दो(स्थिर अक्षर *);
व्योम अक्षर_दो(पूर्णांक);
पूर्णांक अक्षर_लो(व्योम);
व्योम kbd_flush(व्योम);
पूर्णांक अक्षर_लो_समयout(व्योम);

/* video.c */
व्योम set_video(व्योम);

/* video-mode.c */
पूर्णांक set_mode(u16 mode);
पूर्णांक mode_defined(u16 mode);
व्योम probe_cards(पूर्णांक unsafe);

/* video-vesa.c */
व्योम vesa_store_edid(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* BOOT_BOOT_H */
