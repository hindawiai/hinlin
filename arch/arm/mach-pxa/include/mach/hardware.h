<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-pxa/include/mach/hardware.h
 *
 *  Author:	Nicolas Pitre
 *  Created:	Jun 15, 2001
 *  Copyright:	MontaVista Software Inc.
 */

#अगर_अघोषित __ASM_ARCH_HARDWARE_H
#घोषणा __ASM_ARCH_HARDWARE_H

#समावेश <mach/addr-map.h>

/*
 * Workarounds क्रम at least 2 errata so far require this.
 * The mapping is set in mach-pxa/generic.c.
 */
#घोषणा UNCACHED_PHYS_0		0xfe000000
#घोषणा UNCACHED_PHYS_0_SIZE	0x00100000

/*
 * Intel PXA2xx पूर्णांकernal रेजिस्टर mapping:
 *
 * 0x40000000 - 0x41ffffff <--> 0xf2000000 - 0xf3ffffff
 * 0x44000000 - 0x45ffffff <--> 0xf4000000 - 0xf5ffffff
 * 0x48000000 - 0x49ffffff <--> 0xf6000000 - 0xf7ffffff
 * 0x4c000000 - 0x4dffffff <--> 0xf8000000 - 0xf9ffffff
 * 0x50000000 - 0x51ffffff <--> 0xfa000000 - 0xfbffffff
 * 0x54000000 - 0x55ffffff <--> 0xfc000000 - 0xfdffffff
 * 0x58000000 - 0x59ffffff <--> 0xfe000000 - 0xffffffff
 *
 * Note that not all PXA2xx chips implement all those addresses, and the
 * kernel only maps the minimum needed range of this mapping.
 */
#घोषणा io_v2p(x) (0x3c000000 + ((x) & 0x01ffffff) + (((x) & 0x0e000000) << 1))
#घोषणा io_p2v(x) IOMEM(0xf2000000 + ((x) & 0x01ffffff) + (((x) & 0x1c000000) >> 1))

#अगर_अघोषित __ASSEMBLY__
# define __REG(x)	(*((अस्थिर u32 __iomem *)io_p2v(x)))

/* With indexed regs we करोn't want to feed the index through io_p2v()
   especially अगर it is a variable, otherwise horrible code will result. */
# define __REG2(x,y)	\
	(*(अस्थिर u32 __iomem*)((u32)&__REG(x) + (y)))

# define __PREG(x)	(io_v2p((u32)&(x)))

#अन्यथा

# define __REG(x)	io_p2v(x)
# define __PREG(x)	io_v2p(x)

#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/cputype.h>

/*
 *   CPU     Stepping     CPU_ID         JTAG_ID
 *
 *  PXA210	B0	0x69052922	0x2926C013
 *  PXA210	B1	0x69052923	0x3926C013
 *  PXA210	B2	0x69052924	0x4926C013
 *  PXA210	C0	0x69052D25	0x5926C013
 *
 *  PXA250	A0	0x69052100	0x09264013
 *  PXA250	A1	0x69052101	0x19264013
 *  PXA250	B0	0x69052902	0x29264013
 *  PXA250	B1	0x69052903	0x39264013
 *  PXA250	B2	0x69052904	0x49264013
 *  PXA250	C0	0x69052D05	0x59264013
 *
 *  PXA255	A0	0x69052D06	0x69264013
 *
 *  PXA26x	A0	0x69052903	0x39264013
 *  PXA26x	B0	0x69052D05	0x59264013
 *
 *  PXA27x	A0	0x69054110	0x09265013
 *  PXA27x	A1	0x69054111	0x19265013
 *  PXA27x	B0	0x69054112	0x29265013
 *  PXA27x	B1	0x69054113	0x39265013
 *  PXA27x	C0	0x69054114	0x49265013
 *  PXA27x	C5	0x69054117	0x79265013
 *
 *  PXA30x	A0	0x69056880	0x0E648013
 *  PXA30x	A1	0x69056881	0x1E648013
 *  PXA31x	A0	0x69056890	0x0E649013
 *  PXA31x	A1	0x69056891	0x1E649013
 *  PXA31x	A2	0x69056892	0x2E649013
 *  PXA32x	B1	0x69056825	0x5E642013
 *  PXA32x	B2	0x69056826	0x6E642013
 *
 *  PXA930	B0	0x69056835	0x5E643013
 *  PXA930	B1	0x69056837	0x7E643013
 *  PXA930	B2	0x69056838	0x8E643013
 *
 *  PXA935	A0	0x56056931	0x1E653013
 *  PXA935	B0	0x56056936	0x6E653013
 *  PXA935	B1	0x56056938	0x8E653013
 */
#अगर_घोषित CONFIG_PXA25x
#घोषणा __cpu_is_pxa210(id)				\
	(अणु						\
		अचिन्हित पूर्णांक _id = (id) & 0xf3f0;	\
		_id == 0x2120;				\
	पूर्ण)

#घोषणा __cpu_is_pxa250(id)				\
	(अणु						\
		अचिन्हित पूर्णांक _id = (id) & 0xf3ff;	\
		_id <= 0x2105;				\
	पूर्ण)

#घोषणा __cpu_is_pxa255(id)				\
	(अणु						\
		अचिन्हित पूर्णांक _id = (id) & 0xffff;	\
		_id == 0x2d06;				\
	पूर्ण)

#घोषणा __cpu_is_pxa25x(id)				\
	(अणु						\
		अचिन्हित पूर्णांक _id = (id) & 0xf300;	\
		_id == 0x2100;				\
	पूर्ण)
#अन्यथा
#घोषणा __cpu_is_pxa210(id)	(0)
#घोषणा __cpu_is_pxa250(id)	(0)
#घोषणा __cpu_is_pxa255(id)	(0)
#घोषणा __cpu_is_pxa25x(id)	(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PXA27x
#घोषणा __cpu_is_pxa27x(id)				\
	(अणु						\
		अचिन्हित पूर्णांक _id = (id) >> 4 & 0xfff;	\
		_id == 0x411;				\
	पूर्ण)
#अन्यथा
#घोषणा __cpu_is_pxa27x(id)	(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_PXA300
#घोषणा __cpu_is_pxa300(id)				\
	(अणु						\
		अचिन्हित पूर्णांक _id = (id) >> 4 & 0xfff;	\
		_id == 0x688;				\
	 पूर्ण)
#अन्यथा
#घोषणा __cpu_is_pxa300(id)	(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_PXA310
#घोषणा __cpu_is_pxa310(id)				\
	(अणु						\
		अचिन्हित पूर्णांक _id = (id) >> 4 & 0xfff;	\
		_id == 0x689;				\
	 पूर्ण)
#अन्यथा
#घोषणा __cpu_is_pxa310(id)	(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_PXA320
#घोषणा __cpu_is_pxa320(id)				\
	(अणु						\
		अचिन्हित पूर्णांक _id = (id) >> 4 & 0xfff;	\
		_id == 0x603 || _id == 0x682;		\
	 पूर्ण)
#अन्यथा
#घोषणा __cpu_is_pxa320(id)	(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_PXA930
#घोषणा __cpu_is_pxa930(id)				\
	(अणु						\
		अचिन्हित पूर्णांक _id = (id) >> 4 & 0xfff;	\
		_id == 0x683;				\
	 पूर्ण)
#अन्यथा
#घोषणा __cpu_is_pxa930(id)	(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_PXA935
#घोषणा __cpu_is_pxa935(id)				\
	(अणु						\
		अचिन्हित पूर्णांक _id = (id) >> 4 & 0xfff;	\
		_id == 0x693;				\
	 पूर्ण)
#अन्यथा
#घोषणा __cpu_is_pxa935(id)	(0)
#पूर्ण_अगर

#घोषणा cpu_is_pxa210()					\
	(अणु						\
		__cpu_is_pxa210(पढ़ो_cpuid_id());	\
	पूर्ण)

#घोषणा cpu_is_pxa250()					\
	(अणु						\
		__cpu_is_pxa250(पढ़ो_cpuid_id());	\
	पूर्ण)

#घोषणा cpu_is_pxa255()                                 \
	(अणु                                              \
		__cpu_is_pxa255(पढ़ो_cpuid_id());       \
	पूर्ण)

#घोषणा cpu_is_pxa25x()					\
	(अणु						\
		__cpu_is_pxa25x(पढ़ो_cpuid_id());	\
	पूर्ण)

#घोषणा cpu_is_pxa27x()					\
	(अणु						\
		__cpu_is_pxa27x(पढ़ो_cpuid_id());	\
	पूर्ण)

#घोषणा cpu_is_pxa300()					\
	(अणु						\
		__cpu_is_pxa300(पढ़ो_cpuid_id());	\
	 पूर्ण)

#घोषणा cpu_is_pxa310()					\
	(अणु						\
		__cpu_is_pxa310(पढ़ो_cpuid_id());	\
	 पूर्ण)

#घोषणा cpu_is_pxa320()					\
	(अणु						\
		__cpu_is_pxa320(पढ़ो_cpuid_id());	\
	 पूर्ण)

#घोषणा cpu_is_pxa930()					\
	(अणु						\
		__cpu_is_pxa930(पढ़ो_cpuid_id());	\
	 पूर्ण)

#घोषणा cpu_is_pxa935()					\
	(अणु						\
		__cpu_is_pxa935(पढ़ो_cpuid_id());	\
	 पूर्ण)



/*
 * CPUID Core Generation Bit
 * <= 0x2 क्रम pxa21x/pxa25x/pxa26x/pxa27x
 */
#अगर defined(CONFIG_PXA25x) || defined(CONFIG_PXA27x)
#घोषणा __cpu_is_pxa2xx(id)				\
	(अणु						\
		अचिन्हित पूर्णांक _id = (id) >> 13 & 0x7;	\
		_id <= 0x2;				\
	 पूर्ण)
#अन्यथा
#घोषणा __cpu_is_pxa2xx(id)	(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PXA3xx
#घोषणा __cpu_is_pxa3xx(id)				\
	(अणु						\
		__cpu_is_pxa300(id)			\
			|| __cpu_is_pxa310(id)		\
			|| __cpu_is_pxa320(id)		\
			|| __cpu_is_pxa93x(id);		\
	 पूर्ण)
#अन्यथा
#घोषणा __cpu_is_pxa3xx(id)	(0)
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_PXA930) || defined(CONFIG_CPU_PXA935)
#घोषणा __cpu_is_pxa93x(id)				\
	(अणु						\
		__cpu_is_pxa930(id)			\
			|| __cpu_is_pxa935(id);		\
	 पूर्ण)
#अन्यथा
#घोषणा __cpu_is_pxa93x(id)	(0)
#पूर्ण_अगर

#घोषणा cpu_is_pxa2xx()					\
	(अणु						\
		__cpu_is_pxa2xx(पढ़ो_cpuid_id());	\
	 पूर्ण)

#घोषणा cpu_is_pxa3xx()					\
	(अणु						\
		__cpu_is_pxa3xx(पढ़ो_cpuid_id());	\
	 पूर्ण)

#घोषणा cpu_is_pxa93x()					\
	(अणु						\
		__cpu_is_pxa93x(पढ़ो_cpuid_id());	\
	 पूर्ण)


/*
 * वापस current memory and LCD घड़ी frequency in units of 10kHz
 */
बाह्य अचिन्हित पूर्णांक get_memclk_frequency_10khz(व्योम);

#पूर्ण_अगर

#पूर्ण_अगर  /* _ASM_ARCH_HARDWARE_H */
