<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARM_MPU_H
#घोषणा __ARM_MPU_H

/* MPUIR layout */
#घोषणा MPUIR_nU		1
#घोषणा MPUIR_DREGION		8
#घोषणा MPUIR_IREGION		16
#घोषणा MPUIR_DREGION_SZMASK	(0xFF << MPUIR_DREGION)
#घोषणा MPUIR_IREGION_SZMASK	(0xFF << MPUIR_IREGION)

/* ID_MMFR0 data relevant to MPU */
#घोषणा MMFR0_PMSA		(0xF << 4)
#घोषणा MMFR0_PMSAv7		(3 << 4)
#घोषणा MMFR0_PMSAv8		(4 << 4)

/* MPU D/I Size Register fields */
#घोषणा PMSAv7_RSR_SZ		1
#घोषणा PMSAv7_RSR_EN		0
#घोषणा PMSAv7_RSR_SD		8

/* Number of subregions (SD) */
#घोषणा PMSAv7_NR_SUBREGS	8
#घोषणा PMSAv7_MIN_SUBREG_SIZE	256

/* The D/I RSR value क्रम an enabled region spanning the whole of memory */
#घोषणा PMSAv7_RSR_ALL_MEM	63

/* Inभागidual bits in the DR/IR ACR */
#घोषणा PMSAv7_ACR_XN		(1 << 12)
#घोषणा PMSAv7_ACR_SHARED	(1 << 2)

/* C, B and TEX[2:0] bits only have semantic meanings when grouped */
#घोषणा PMSAv7_RGN_CACHEABLE		0xB
#घोषणा PMSAv7_RGN_SHARED_CACHEABLE	(PMSAv7_RGN_CACHEABLE | PMSAv7_ACR_SHARED)
#घोषणा PMSAv7_RGN_STRONGLY_ORDERED	0

/* Main region should only be shared क्रम SMP */
#अगर_घोषित CONFIG_SMP
#घोषणा PMSAv7_RGN_NORMAL	(PMSAv7_RGN_CACHEABLE | PMSAv7_ACR_SHARED)
#अन्यथा
#घोषणा PMSAv7_RGN_NORMAL	PMSAv7_RGN_CACHEABLE
#पूर्ण_अगर

/* Access permission bits of ACR (only define those that we use)*/
#घोषणा PMSAv7_AP_PL1RO_PL0NA	(0x5 << 8)
#घोषणा PMSAv7_AP_PL1RW_PL0RW	(0x3 << 8)
#घोषणा PMSAv7_AP_PL1RW_PL0R0	(0x2 << 8)
#घोषणा PMSAv7_AP_PL1RW_PL0NA	(0x1 << 8)

#घोषणा PMSAv8_BAR_XN		1

#घोषणा PMSAv8_LAR_EN		1
#घोषणा PMSAv8_LAR_IDX(n)	(((n) & 0x7) << 1)


#घोषणा PMSAv8_AP_PL1RW_PL0NA	(0 << 1)
#घोषणा PMSAv8_AP_PL1RW_PL0RW	(1 << 1)
#घोषणा PMSAv8_AP_PL1RO_PL0RO	(3 << 1)

#अगर_घोषित CONFIG_SMP
#घोषणा PMSAv8_RGN_SHARED	(3 << 3) // inner sharable
#अन्यथा
#घोषणा PMSAv8_RGN_SHARED	(0 << 3)
#पूर्ण_अगर

#घोषणा PMSAv8_RGN_DEVICE_nGnRnE	0
#घोषणा PMSAv8_RGN_NORMAL		1

#घोषणा PMSAv8_MAIR(attr, mt)	((attr) << ((mt) * 8))

#अगर_घोषित CONFIG_CPU_V7M
#घोषणा PMSAv8_MINALIGN		32
#अन्यथा
#घोषणा PMSAv8_MINALIGN		64
#पूर्ण_अगर

/* For minimal अटल MPU region configurations */
#घोषणा PMSAv7_PROBE_REGION	0
#घोषणा PMSAv7_BG_REGION	1
#घोषणा PMSAv7_RAM_REGION	2
#घोषणा PMSAv7_ROM_REGION	3

/* Fixed क्रम PMSAv8 only */
#घोषणा PMSAv8_XIP_REGION	0
#घोषणा PMSAv8_KERNEL_REGION	1

/* Maximum number of regions Linux is पूर्णांकerested in */
#घोषणा MPU_MAX_REGIONS	16

#घोषणा PMSAv7_DATA_SIDE	0
#घोषणा PMSAv7_INSTR_SIDE	1

#अगर_अघोषित __ASSEMBLY__

काष्ठा mpu_rgn अणु
	/* Assume same attributes क्रम d/i-side  */
	जोड़ अणु
		u32 drbar;   /* PMSAv7 */
		u32 prbar;   /* PMSAv8 */
	पूर्ण;
	जोड़ अणु
		u32 drsr;   /* PMSAv7 */
		u32 prlar;  /* PMSAv8 */
	पूर्ण;
	जोड़ अणु
		u32 dracr;  /* PMSAv7 */
		u32 unused; /* not used in PMSAv8 */
	पूर्ण;
पूर्ण;

काष्ठा mpu_rgn_info अणु
	अचिन्हित पूर्णांक used;
	काष्ठा mpu_rgn rgns[MPU_MAX_REGIONS];
पूर्ण;
बाह्य काष्ठा mpu_rgn_info mpu_rgn_info;

#अगर_घोषित CONFIG_ARM_MPU
बाह्य व्योम __init pmsav7_adjust_lowmem_bounds(व्योम);
बाह्य व्योम __init pmsav8_adjust_lowmem_bounds(व्योम);

बाह्य व्योम __init pmsav7_setup(व्योम);
बाह्य व्योम __init pmsav8_setup(व्योम);
#अन्यथा
अटल अंतरभूत व्योम pmsav7_adjust_lowmem_bounds(व्योम) अणुपूर्ण;
अटल अंतरभूत व्योम pmsav8_adjust_lowmem_bounds(व्योम) अणुपूर्ण;
अटल अंतरभूत व्योम pmsav7_setup(व्योम) अणुपूर्ण;
अटल अंतरभूत व्योम pmsav8_setup(व्योम) अणुपूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
