<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *
 * Authors: Sylwester Nawrocki <s.nawrocki@samsung.com>
 *          Younghwan Joo <yhwan.joo@samsung.com>
 */
#अगर_अघोषित FIMC_IS_REG_H_
#घोषणा FIMC_IS_REG_H_

/* WDT_ISP रेजिस्टर */
#घोषणा REG_WDT_ISP			0x00170000

/* MCUCTL रेजिस्टरs base offset */
#घोषणा MCUCTL_BASE			0x00180000

/* MCU Controller Register */
#घोषणा MCUCTL_REG_MCUCTRL		(MCUCTL_BASE + 0x00)
#घोषणा MCUCTRL_MSWRST			(1 << 0)

/* Boot Base Offset Address Register */
#घोषणा MCUCTL_REG_BBOAR		(MCUCTL_BASE + 0x04)

/* Interrupt Generation Register 0 from Host CPU to VIC */
#घोषणा MCUCTL_REG_INTGR0		(MCUCTL_BASE + 0x08)
/* __n = 0...9 */
#घोषणा INTGR0_INTGC(__n)		(1 << ((__n) + 16))
/* __n = 0...5 */
#घोषणा INTGR0_INTGD(__n)		(1 << (__n))

/* Interrupt Clear Register 0 from Host CPU to VIC */
#घोषणा MCUCTL_REG_INTCR0		(MCUCTL_BASE + 0x0c)
/* __n = 0...9 */
#घोषणा INTCR0_INTGC(__n)		(1 << ((__n) + 16))
/* __n = 0...5 */
#घोषणा INTCR0_INTCD(__n)		(1 << ((__n) + 16))

/* Interrupt Mask Register 0 from Host CPU to VIC */
#घोषणा MCUCTL_REG_INTMR0		(MCUCTL_BASE + 0x10)
/* __n = 0...9 */
#घोषणा INTMR0_INTMC(__n)		(1 << ((__n) + 16))
/* __n = 0...5 */
#घोषणा INTMR0_INTMD(__n)		(1 << (__n))

/* Interrupt Status Register 0 from Host CPU to VIC */
#घोषणा MCUCTL_REG_INTSR0		(MCUCTL_BASE + 0x14)
/* __n (bit number) = 0...4 */
#घोषणा INTSR0_GET_INTSD(x, __n)	(((x) >> (__n)) & 0x1)
/* __n (bit number) = 0...9 */
#घोषणा INTSR0_GET_INTSC(x, __n)	(((x) >> ((__n) + 16)) & 0x1)

/* Interrupt Mask Status Register 0 from Host CPU to VIC */
#घोषणा MCUCTL_REG_INTMSR0		(MCUCTL_BASE + 0x18)
/* __n (bit number) = 0...4 */
#घोषणा INTMSR0_GET_INTMSD(x, __n)	(((x) >> (__n)) & 0x1)
/* __n (bit number) = 0...9 */
#घोषणा INTMSR0_GET_INTMSC(x, __n)	(((x) >> ((__n) + 16)) & 0x1)

/* Interrupt Generation Register 1 from ISP CPU to Host IC */
#घोषणा MCUCTL_REG_INTGR1		(MCUCTL_BASE + 0x1c)
/* __n = 0...9 */
#घोषणा INTGR1_INTGC(__n)		(1 << (__n))

/* Interrupt Clear Register 1 from ISP CPU to Host IC */
#घोषणा MCUCTL_REG_INTCR1		(MCUCTL_BASE + 0x20)
/* __n = 0...9 */
#घोषणा INTCR1_INTCC(__n)		(1 << (__n))

/* Interrupt Mask Register 1 from ISP CPU to Host IC */
#घोषणा MCUCTL_REG_INTMR1		(MCUCTL_BASE + 0x24)
/* __n = 0...9 */
#घोषणा INTMR1_INTMC(__n)		(1 << (__n))

/* Interrupt Status Register 1 from ISP CPU to Host IC */
#घोषणा MCUCTL_REG_INTSR1		(MCUCTL_BASE + 0x28)
/* Interrupt Mask Status Register 1 from ISP CPU to Host IC */
#घोषणा MCUCTL_REG_INTMSR1		(MCUCTL_BASE + 0x2c)

/* Interrupt Clear Register 2 from ISP BLK's पूर्णांकerrupts to Host IC */
#घोषणा MCUCTL_REG_INTCR2		(MCUCTL_BASE + 0x30)
/* __n = 0...5 */
#घोषणा INTCR2_INTCC(__n)		(1 << ((__n) + 16))

/* Interrupt Mask Register 2 from ISP BLK's पूर्णांकerrupts to Host IC */
#घोषणा MCUCTL_REG_INTMR2		(MCUCTL_BASE + 0x34)
/* __n = 0...25 */
#घोषणा INTMR2_INTMCIS(__n)		(1 << (__n))

/* Interrupt Status Register 2 from ISP BLK's पूर्णांकerrupts to Host IC */
#घोषणा MCUCTL_REG_INTSR2		(MCUCTL_BASE + 0x38)
/* Interrupt Mask Status Register 2 from ISP BLK's पूर्णांकerrupts to Host IC */
#घोषणा MCUCTL_REG_INTMSR2		(MCUCTL_BASE + 0x3c)

/* General Purpose Output Control Register (0~17) */
#घोषणा MCUCTL_REG_GPOCTLR		(MCUCTL_BASE + 0x40)
/* __n = 0...17 */
#घोषणा GPOCTLR_GPOG(__n)		(1 << (__n))

/* General Purpose Pad Output Enable Register (0~17) */
#घोषणा MCUCTL_REG_GPOENCTLR		(MCUCTL_BASE + 0x44)
/* __n = 0...17 */
#घोषणा GPOENCTLR_GPOEN(__n)		(1 << (__n))

/* General Purpose Input Control Register (0~17) */
#घोषणा MCUCTL_REG_GPICTLR		(MCUCTL_BASE + 0x48)

/* Shared रेजिस्टरs between ISP CPU and the host CPU - ISSRxx */

/* ISSR(1): Command Host -> IS */
/* ISSR(1): Sensor ID क्रम Command, ISSR2...5 = Parameter 1...4 */

/* ISSR(10): Reply IS -> Host */
/* ISSR(11): Sensor ID क्रम Reply, ISSR12...15 = Parameter 1...4 */

/* ISSR(20): ISP_FRAME_DONE : SENSOR ID */
/* ISSR(21): ISP_FRAME_DONE : PARAMETER 1 */

/* ISSR(24): SCALERC_FRAME_DONE : SENSOR ID */
/* ISSR(25): SCALERC_FRAME_DONE : PARAMETER 1 */

/* ISSR(28): 3DNR_FRAME_DONE : SENSOR ID */
/* ISSR(29): 3DNR_FRAME_DONE : PARAMETER 1 */

/* ISSR(32): SCALERP_FRAME_DONE : SENSOR ID */
/* ISSR(33): SCALERP_FRAME_DONE : PARAMETER 1 */

/* __n = 0...63 */
#घोषणा MCUCTL_REG_ISSR(__n)		(MCUCTL_BASE + 0x80 + ((__n) * 4))

/* PMU ISP रेजिस्टर offsets */
#घोषणा REG_CMU_RESET_ISP_SYS_PWR_REG	0x1174
#घोषणा REG_CMU_SYSCLK_ISP_SYS_PWR_REG	0x13b8
#घोषणा REG_PMU_ISP_ARM_SYS		0x1050
#घोषणा REG_PMU_ISP_ARM_CONFIGURATION	0x2280
#घोषणा REG_PMU_ISP_ARM_STATUS		0x2284
#घोषणा REG_PMU_ISP_ARM_OPTION		0x2288

व्योम fimc_is_fw_clear_irq1(काष्ठा fimc_is *is, अचिन्हित पूर्णांक bit);
व्योम fimc_is_fw_clear_irq2(काष्ठा fimc_is *is);
पूर्णांक fimc_is_hw_get_params(काष्ठा fimc_is *is, अचिन्हित पूर्णांक num);

व्योम fimc_is_hw_set_पूर्णांकgr0_gd0(काष्ठा fimc_is *is);
पूर्णांक fimc_is_hw_रुको_पूर्णांकmsr0_पूर्णांकmsd0(काष्ठा fimc_is *is);
व्योम fimc_is_hw_set_sensor_num(काष्ठा fimc_is *is);
व्योम fimc_is_hw_set_isp_buf_mask(काष्ठा fimc_is *is, अचिन्हित पूर्णांक mask);
व्योम fimc_is_hw_stream_on(काष्ठा fimc_is *is);
व्योम fimc_is_hw_stream_off(काष्ठा fimc_is *is);
पूर्णांक fimc_is_hw_set_param(काष्ठा fimc_is *is);
पूर्णांक fimc_is_hw_change_mode(काष्ठा fimc_is *is);

व्योम fimc_is_hw_बंद_sensor(काष्ठा fimc_is *is, अचिन्हित पूर्णांक index);
व्योम fimc_is_hw_get_setfile_addr(काष्ठा fimc_is *is);
व्योम fimc_is_hw_load_setfile(काष्ठा fimc_is *is);
व्योम fimc_is_hw_subip_घातer_off(काष्ठा fimc_is *is);

पूर्णांक fimc_is_itf_s_param(काष्ठा fimc_is *is, bool update);
पूर्णांक fimc_is_itf_mode_change(काष्ठा fimc_is *is);

#पूर्ण_अगर /* FIMC_IS_REG_H_ */
