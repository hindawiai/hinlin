<शैली गुरु>
/*
 * Copyright (C) 2018 ARM Limited
 * Copyright (C) 2015 Imagination Technologies
 * Author: Alex Smith <alex.smith@imgtec.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */
#अगर_अघोषित __ASM_VDSO_GETTIMखातापूर्णDAY_H
#घोषणा __ASM_VDSO_GETTIMखातापूर्णDAY_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/vdso/vdso.h>
#समावेश <यंत्र/घड़ीsource.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/vdso.h>

#घोषणा VDSO_HAS_CLOCK_GETRES		1

#अगर MIPS_ISA_REV < 6
#घोषणा VDSO_SYSCALL_CLOBBERS "hi", "lo",
#अन्यथा
#घोषणा VDSO_SYSCALL_CLOBBERS
#पूर्ण_अगर

अटल __always_अंतरभूत दीर्घ समय_लोofday_fallback(
				काष्ठा __kernel_old_समयval *_tv,
				काष्ठा समयzone *_tz)
अणु
	रेजिस्टर काष्ठा समयzone *tz यंत्र("a1") = _tz;
	रेजिस्टर काष्ठा __kernel_old_समयval *tv यंत्र("a0") = _tv;
	रेजिस्टर दीर्घ ret यंत्र("v0");
	रेजिस्टर दीर्घ nr यंत्र("v0") = __NR_समय_लोofday;
	रेजिस्टर दीर्घ error यंत्र("a3");

	यंत्र अस्थिर(
	"       syscall\n"
	: "=r" (ret), "=r" (error)
	: "r" (tv), "r" (tz), "r" (nr)
	: "$1", "$3", "$8", "$9", "$10", "$11", "$12", "$13",
	  "$14", "$15", "$24", "$25",
	  VDSO_SYSCALL_CLOBBERS
	  "memory");

	वापस error ? -ret : ret;
पूर्ण

अटल __always_अंतरभूत दीर्घ घड़ी_समय_लो_fallback(
					घड़ीid_t _clkid,
					काष्ठा __kernel_बारpec *_ts)
अणु
	रेजिस्टर काष्ठा __kernel_बारpec *ts यंत्र("a1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("a0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र("v0");
#अगर _MIPS_SIM == _MIPS_SIM_ABI64
	रेजिस्टर दीर्घ nr यंत्र("v0") = __NR_घड़ी_समय_लो;
#अन्यथा
	रेजिस्टर दीर्घ nr यंत्र("v0") = __NR_घड़ी_समय_लो64;
#पूर्ण_अगर
	रेजिस्टर दीर्घ error यंत्र("a3");

	यंत्र अस्थिर(
	"       syscall\n"
	: "=r" (ret), "=r" (error)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "$1", "$3", "$8", "$9", "$10", "$11", "$12", "$13",
	  "$14", "$15", "$24", "$25",
	  VDSO_SYSCALL_CLOBBERS
	  "memory");

	वापस error ? -ret : ret;
पूर्ण

अटल __always_अंतरभूत पूर्णांक घड़ी_getres_fallback(
					घड़ीid_t _clkid,
					काष्ठा __kernel_बारpec *_ts)
अणु
	रेजिस्टर काष्ठा __kernel_बारpec *ts यंत्र("a1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("a0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र("v0");
#अगर _MIPS_SIM == _MIPS_SIM_ABI64
	रेजिस्टर दीर्घ nr यंत्र("v0") = __NR_घड़ी_getres;
#अन्यथा
	रेजिस्टर दीर्घ nr यंत्र("v0") = __NR_घड़ी_getres_समय64;
#पूर्ण_अगर
	रेजिस्टर दीर्घ error यंत्र("a3");

	यंत्र अस्थिर(
	"       syscall\n"
	: "=r" (ret), "=r" (error)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "$1", "$3", "$8", "$9", "$10", "$11", "$12", "$13",
	  "$14", "$15", "$24", "$25",
	  VDSO_SYSCALL_CLOBBERS
	  "memory");

	वापस error ? -ret : ret;
पूर्ण

#अगर _MIPS_SIM != _MIPS_SIM_ABI64

अटल __always_अंतरभूत दीर्घ घड़ी_समय_लो32_fallback(
					घड़ीid_t _clkid,
					काष्ठा old_बारpec32 *_ts)
अणु
	रेजिस्टर काष्ठा old_बारpec32 *ts यंत्र("a1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("a0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र("v0");
	रेजिस्टर दीर्घ nr यंत्र("v0") = __NR_घड़ी_समय_लो;
	रेजिस्टर दीर्घ error यंत्र("a3");

	यंत्र अस्थिर(
	"       syscall\n"
	: "=r" (ret), "=r" (error)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "$1", "$3", "$8", "$9", "$10", "$11", "$12", "$13",
	  "$14", "$15", "$24", "$25",
	  VDSO_SYSCALL_CLOBBERS
	  "memory");

	वापस error ? -ret : ret;
पूर्ण

अटल __always_अंतरभूत पूर्णांक घड़ी_getres32_fallback(
					घड़ीid_t _clkid,
					काष्ठा old_बारpec32 *_ts)
अणु
	रेजिस्टर काष्ठा old_बारpec32 *ts यंत्र("a1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("a0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र("v0");
	रेजिस्टर दीर्घ nr यंत्र("v0") = __NR_घड़ी_getres;
	रेजिस्टर दीर्घ error यंत्र("a3");

	यंत्र अस्थिर(
	"       syscall\n"
	: "=r" (ret), "=r" (error)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "$1", "$3", "$8", "$9", "$10", "$11", "$12", "$13",
	  "$14", "$15", "$24", "$25",
	  VDSO_SYSCALL_CLOBBERS
	  "memory");

	वापस error ? -ret : ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CSRC_R4K

अटल __always_अंतरभूत u64 पढ़ो_r4k_count(व्योम)
अणु
	अचिन्हित पूर्णांक count;

	__यंत्र__ __अस्थिर__(
	"	.set push\n"
	"	.set mips32r2\n"
	"	rdhwr	%0, $2\n"
	"	.set pop\n"
	: "=r" (count));

	वापस count;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_CLKSRC_MIPS_GIC

अटल __always_अंतरभूत u64 पढ़ो_gic_count(स्थिर काष्ठा vdso_data *data)
अणु
	व्योम __iomem *gic = get_gic(data);
	u32 hi, hi2, lo;

	करो अणु
		hi = __raw_पढ़ोl(gic + माप(lo));
		lo = __raw_पढ़ोl(gic);
		hi2 = __raw_पढ़ोl(gic + माप(lo));
	पूर्ण जबतक (hi2 != hi);

	वापस (((u64)hi) << 32) + lo;
पूर्ण

#पूर्ण_अगर

अटल __always_अंतरभूत u64 __arch_get_hw_counter(s32 घड़ी_mode,
						 स्थिर काष्ठा vdso_data *vd)
अणु
#अगर_घोषित CONFIG_CSRC_R4K
	अगर (घड़ी_mode == VDSO_CLOCKMODE_R4K)
		वापस पढ़ो_r4k_count();
#पूर्ण_अगर
#अगर_घोषित CONFIG_CLKSRC_MIPS_GIC
	अगर (घड़ी_mode == VDSO_CLOCKMODE_GIC)
		वापस पढ़ो_gic_count(vd);
#पूर्ण_अगर
	/*
	 * Core checks mode alपढ़ोy. So this raced against a concurrent
	 * update. Return something. Core will करो another round see the
	 * change and fallback to syscall.
	 */
	वापस 0;
पूर्ण

अटल अंतरभूत bool mips_vdso_hres_capable(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_CSRC_R4K) ||
	       IS_ENABLED(CONFIG_CLKSRC_MIPS_GIC);
पूर्ण
#घोषणा __arch_vdso_hres_capable mips_vdso_hres_capable

अटल __always_अंतरभूत स्थिर काष्ठा vdso_data *__arch_get_vdso_data(व्योम)
अणु
	वापस get_vdso_data();
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_GETTIMखातापूर्णDAY_H */
