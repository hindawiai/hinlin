<शैली गुरु>
/*
 * DaVinci CPU type detection
 *
 * Author: Kevin Hilman, Deep Root Systems, LLC
 *
 * Defines the cpu_is_*() macros क्रम runसमय detection of DaVinci
 * device type.  In addition, अगर support क्रम a given device is not
 * compiled in to the kernel, the macros वापस 0 so that
 * resulting code can be optimized out.
 *
 * 2009 (c) Deep Root Systems, LLC. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#अगर_अघोषित _ASM_ARCH_CPU_H
#घोषणा _ASM_ARCH_CPU_H

#समावेश <mach/common.h>

काष्ठा davinci_id अणु
	u8	variant;	/* JTAG ID bits 31:28 */
	u16	part_no;	/* JTAG ID bits 27:12 */
	u16	manufacturer;	/* JTAG ID bits 11:1 */
	u32	cpu_id;
	अक्षर	*name;
पूर्ण;

/* Can use lower 16 bits of cpu id  क्रम a variant when required */
#घोषणा	DAVINCI_CPU_ID_DM6446		0x64460000
#घोषणा	DAVINCI_CPU_ID_DM6467		0x64670000
#घोषणा	DAVINCI_CPU_ID_DM355		0x03550000
#घोषणा	DAVINCI_CPU_ID_DM365		0x03650000
#घोषणा	DAVINCI_CPU_ID_DA830		0x08300000
#घोषणा	DAVINCI_CPU_ID_DA850		0x08500000

#घोषणा IS_DAVINCI_CPU(type, id)					\
अटल अंतरभूत पूर्णांक is_davinci_ ##type(व्योम)				\
अणु									\
	वापस (davinci_soc_info.cpu_id == (id));			\
पूर्ण

IS_DAVINCI_CPU(dm644x, DAVINCI_CPU_ID_DM6446)
IS_DAVINCI_CPU(dm646x, DAVINCI_CPU_ID_DM6467)
IS_DAVINCI_CPU(dm355, DAVINCI_CPU_ID_DM355)
IS_DAVINCI_CPU(dm365, DAVINCI_CPU_ID_DM365)
IS_DAVINCI_CPU(da830, DAVINCI_CPU_ID_DA830)
IS_DAVINCI_CPU(da850, DAVINCI_CPU_ID_DA850)

#अगर_घोषित CONFIG_ARCH_DAVINCI_DM644x
#घोषणा cpu_is_davinci_dm644x() is_davinci_dm644x()
#अन्यथा
#घोषणा cpu_is_davinci_dm644x() 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_DAVINCI_DM646x
#घोषणा cpu_is_davinci_dm646x() is_davinci_dm646x()
#अन्यथा
#घोषणा cpu_is_davinci_dm646x() 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_DAVINCI_DM355
#घोषणा cpu_is_davinci_dm355() is_davinci_dm355()
#अन्यथा
#घोषणा cpu_is_davinci_dm355() 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_DAVINCI_DM365
#घोषणा cpu_is_davinci_dm365() is_davinci_dm365()
#अन्यथा
#घोषणा cpu_is_davinci_dm365() 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_DAVINCI_DA830
#घोषणा cpu_is_davinci_da830() is_davinci_da830()
#अन्यथा
#घोषणा cpu_is_davinci_da830() 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_DAVINCI_DA850
#घोषणा cpu_is_davinci_da850() is_davinci_da850()
#अन्यथा
#घोषणा cpu_is_davinci_da850() 0
#पूर्ण_अगर

#पूर्ण_अगर
