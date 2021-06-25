<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003, 2004 Ralf Baechle
 * Copyright (C) 2004  Maciej W. Rozycki
 */
#अगर_अघोषित __ASM_CPU_TYPE_H
#घोषणा __ASM_CPU_TYPE_H

#समावेश <linux/smp.h>
#समावेश <linux/compiler.h>

अटल अंतरभूत पूर्णांक __pure __get_cpu_type(स्थिर पूर्णांक cpu_type)
अणु
	चयन (cpu_type) अणु
#अगर defined(CONFIG_SYS_HAS_CPU_LOONGSON2E) || \
    defined(CONFIG_SYS_HAS_CPU_LOONGSON2F)
	हाल CPU_LOONGSON2EF:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_LOONGSON64
	हाल CPU_LOONGSON64:
#पूर्ण_अगर

#अगर defined(CONFIG_SYS_HAS_CPU_LOONGSON1B) || \
    defined(CONFIG_SYS_HAS_CPU_LOONGSON1C)
	हाल CPU_LOONGSON32:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_MIPS32_R1
	हाल CPU_4KC:
	हाल CPU_ALCHEMY:
	हाल CPU_PR4450:
#पूर्ण_अगर

#अगर defined(CONFIG_SYS_HAS_CPU_MIPS32_R1) || \
    defined(CONFIG_SYS_HAS_CPU_MIPS32_R2)
	हाल CPU_4KEC:
	हाल CPU_XBURST:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_MIPS32_R2
	हाल CPU_4KSC:
	हाल CPU_24K:
	हाल CPU_34K:
	हाल CPU_1004K:
	हाल CPU_74K:
	हाल CPU_1074K:
	हाल CPU_M14KC:
	हाल CPU_M14KEC:
	हाल CPU_INTERAPTIV:
	हाल CPU_PROAPTIV:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_MIPS32_R5
	हाल CPU_M5150:
	हाल CPU_P5600:
#पूर्ण_अगर

#अगर defined(CONFIG_SYS_HAS_CPU_MIPS32_R2) || \
    defined(CONFIG_SYS_HAS_CPU_MIPS32_R5) || \
    defined(CONFIG_SYS_HAS_CPU_MIPS32_R6) || \
    defined(CONFIG_SYS_HAS_CPU_MIPS64_R2) || \
    defined(CONFIG_SYS_HAS_CPU_MIPS64_R5) || \
    defined(CONFIG_SYS_HAS_CPU_MIPS64_R6)
	हाल CPU_QEMU_GENERIC:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_MIPS64_R1
	हाल CPU_5KC:
	हाल CPU_5KE:
	हाल CPU_20KC:
	हाल CPU_25KF:
	हाल CPU_SB1:
	हाल CPU_SB1A:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_MIPS64_R2
	/*
	 * All MIPS64 R2 processors have their own special symbols.  That is,
	 * there currently is no pure R2 core
	 */
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_MIPS32_R6
	हाल CPU_M6250:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_MIPS64_R6
	हाल CPU_I6400:
	हाल CPU_I6500:
	हाल CPU_P6600:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_R3000
	हाल CPU_R2000:
	हाल CPU_R3000:
	हाल CPU_R3000A:
	हाल CPU_R3041:
	हाल CPU_R3051:
	हाल CPU_R3052:
	हाल CPU_R3081:
	हाल CPU_R3081E:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_TX39XX
	हाल CPU_TX3912:
	हाल CPU_TX3922:
	हाल CPU_TX3927:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_VR41XX
	हाल CPU_VR41XX:
	हाल CPU_VR4111:
	हाल CPU_VR4121:
	हाल CPU_VR4122:
	हाल CPU_VR4131:
	हाल CPU_VR4133:
	हाल CPU_VR4181:
	हाल CPU_VR4181A:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_R4300
	हाल CPU_R4300:
	हाल CPU_R4310:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_R4X00
	हाल CPU_R4000PC:
	हाल CPU_R4000SC:
	हाल CPU_R4000MC:
	हाल CPU_R4200:
	हाल CPU_R4400PC:
	हाल CPU_R4400SC:
	हाल CPU_R4400MC:
	हाल CPU_R4600:
	हाल CPU_R4700:
	हाल CPU_R4640:
	हाल CPU_R4650:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_TX49XX
	हाल CPU_TX49XX:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_R5000
	हाल CPU_R5000:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_R5500
	हाल CPU_R5500:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_NEVADA
	हाल CPU_NEVADA:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_R10000
	हाल CPU_R10000:
	हाल CPU_R12000:
	हाल CPU_R14000:
	हाल CPU_R16000:
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYS_HAS_CPU_RM7000
	हाल CPU_RM7000:
	हाल CPU_SR71000:
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYS_HAS_CPU_SB1
	हाल CPU_SB1:
	हाल CPU_SB1A:
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYS_HAS_CPU_CAVIUM_OCTEON
	हाल CPU_CAVIUM_OCTEON:
	हाल CPU_CAVIUM_OCTEON_PLUS:
	हाल CPU_CAVIUM_OCTEON2:
	हाल CPU_CAVIUM_OCTEON3:
#पूर्ण_अगर

#अगर defined(CONFIG_SYS_HAS_CPU_BMIPS32_3300) || \
	defined (CONFIG_SYS_HAS_CPU_MIPS32_R1)
	हाल CPU_BMIPS32:
	हाल CPU_BMIPS3300:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_BMIPS4350
	हाल CPU_BMIPS4350:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_BMIPS4380
	हाल CPU_BMIPS4380:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_BMIPS5000
	हाल CPU_BMIPS5000:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_XLP
	हाल CPU_XLP:
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYS_HAS_CPU_XLR
	हाल CPU_XLR:
#पूर्ण_अगर
		अवरोध;
	शेष:
		unreachable();
	पूर्ण

	वापस cpu_type;
पूर्ण

अटल अंतरभूत पूर्णांक __pure current_cpu_type(व्योम)
अणु
	स्थिर पूर्णांक cpu_type = current_cpu_data.cputype;

	वापस __get_cpu_type(cpu_type);
पूर्ण

अटल अंतरभूत पूर्णांक __pure boot_cpu_type(व्योम)
अणु
	स्थिर पूर्णांक cpu_type = cpu_data[0].cputype;

	वापस __get_cpu_type(cpu_type);
पूर्ण

#पूर्ण_अगर /* __ASM_CPU_TYPE_H */
