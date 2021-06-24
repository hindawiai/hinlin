<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_CPUTYPE_H
#घोषणा __ASM_MACH_CPUTYPE_H

#अगर defined(CONFIG_ARM) || defined(CONFIG_ARM64)
#समावेश <यंत्र/cputype.h>
#पूर्ण_अगर

/*
 *  CPU   Stepping   CPU_ID      CHIP_ID
 *
 * PXA168    S0    0x56158400   0x0000C910
 * PXA168    A0    0x56158400   0x00A0A168
 * PXA910    Y1    0x56158400   0x00F2C920
 * PXA910    A0    0x56158400   0x00F2C910
 * PXA910    A1    0x56158400   0x00A0C910
 * PXA920    Y0    0x56158400   0x00F2C920
 * PXA920    A0    0x56158400   0x00A0C920
 * PXA920    A1    0x56158400   0x00A1C920
 * MMP2	     Z0	   0x560f5811   0x00F00410
 * MMP2      Z1    0x560f5811   0x00E00410
 * MMP2      A0    0x560f5811   0x00A0A610
 * MMP3      A0    0x562f5842   0x00A02128
 * MMP3      B0    0x562f5842   0x00B02128
 */

बाह्य अचिन्हित पूर्णांक mmp_chip_id;

#अगर_घोषित CONFIG_CPU_PXA168
अटल अंतरभूत पूर्णांक cpu_is_pxa168(व्योम)
अणु
	वापस (((पढ़ो_cpuid_id() >> 8) & 0xff) == 0x84) &&
		((mmp_chip_id & 0xfff) == 0x168);
पूर्ण
#अन्यथा
#घोषणा cpu_is_pxa168()	(0)
#पूर्ण_अगर

/* cpu_is_pxa910() is shared on both pxa910 and pxa920 */
#अगर_घोषित CONFIG_CPU_PXA910
अटल अंतरभूत पूर्णांक cpu_is_pxa910(व्योम)
अणु
	वापस (((पढ़ो_cpuid_id() >> 8) & 0xff) == 0x84) &&
		(((mmp_chip_id & 0xfff) == 0x910) ||
		 ((mmp_chip_id & 0xfff) == 0x920));
पूर्ण
#अन्यथा
#घोषणा cpu_is_pxa910()	(0)
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_MMP2) || defined(CONFIG_MACH_MMP2_DT)
अटल अंतरभूत पूर्णांक cpu_is_mmp2(व्योम)
अणु
	वापस (((पढ़ो_cpuid_id() >> 8) & 0xff) == 0x58) &&
		(((mmp_chip_id & 0xfff) == 0x410) ||
		 ((mmp_chip_id & 0xfff) == 0x610));
पूर्ण
#अन्यथा
#घोषणा cpu_is_mmp2()	(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_MMP3_DT
अटल अंतरभूत पूर्णांक cpu_is_mmp3(व्योम)
अणु
	वापस (((पढ़ो_cpuid_id() >> 8) & 0xff) == 0x58) &&
		((mmp_chip_id & 0xffff) == 0x2128);
पूर्ण

अटल अंतरभूत पूर्णांक cpu_is_mmp3_a0(व्योम)
अणु
	वापस (cpu_is_mmp3() &&
		((mmp_chip_id & 0x00ff0000) == 0x00a00000));
पूर्ण

अटल अंतरभूत पूर्णांक cpu_is_mmp3_b0(व्योम)
अणु
	वापस (cpu_is_mmp3() &&
		((mmp_chip_id & 0x00ff0000) == 0x00b00000));
पूर्ण

#अन्यथा
#घोषणा cpu_is_mmp3()		(0)
#घोषणा cpu_is_mmp3_a0()	(0)
#घोषणा cpu_is_mmp3_b0()	(0)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MACH_CPUTYPE_H */
