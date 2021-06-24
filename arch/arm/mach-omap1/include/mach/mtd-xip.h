<शैली गुरु>
/*
 * MTD primitives क्रम XIP support. Architecture specअगरic functions.
 *
 * Do not include this file directly. It's included from linux/mtd/xip.h
 *
 * Author: Vladimir Barinov <vbarinov@embeddedalley.com>
 *
 * (c) 2005 MontaVista Software, Inc.  This file is licensed under the
 * terms of the GNU General Public License version 2.  This program is
 * licensed "as is" without any warranty of any kind, whether express or
 * implied.
 */

#अगर_अघोषित __ARCH_OMAP_MTD_XIP_H__
#घोषणा __ARCH_OMAP_MTD_XIP_H__

#समावेश <mach/hardware.h>
#घोषणा OMAP_MPU_TIMER_BASE	(0xfffec500)
#घोषणा OMAP_MPU_TIMER_OFFSET	0x100

प्रकार काष्ठा अणु
	u32 cntl;			/* CNTL_TIMER, R/W */
	u32 load_tim;			/* LOAD_TIM,   W */
	u32 पढ़ो_tim;			/* READ_TIM,   R */
पूर्ण xip_omap_mpu_समयr_regs_t;

#घोषणा xip_omap_mpu_समयr_base(n)					\
((अस्थिर xip_omap_mpu_समयr_regs_t*)OMAP1_IO_ADDRESS(OMAP_MPU_TIMER_BASE +	\
	(n)*OMAP_MPU_TIMER_OFFSET))

अटल अंतरभूत अचिन्हित दीर्घ xip_omap_mpu_समयr_पढ़ो(पूर्णांक nr)
अणु
	अस्थिर xip_omap_mpu_समयr_regs_t* समयr = xip_omap_mpu_समयr_base(nr);
	वापस समयr->पढ़ो_tim;
पूर्ण

#घोषणा xip_irqpending()	\
	(omap_पढ़ोl(OMAP_IH1_ITR) & ~omap_पढ़ोl(OMAP_IH1_MIR))
#घोषणा xip_currसमय()		(~xip_omap_mpu_समयr_पढ़ो(0))

/*
 * It's permitted to करो approximation क्रम xip_elapsed_since macro
 * (see linux/mtd/xip.h)
 */

#अगर_घोषित CONFIG_MACH_OMAP_PERSEUS2
#घोषणा xip_elapsed_since(x)	(चिन्हित)((~xip_omap_mpu_समयr_पढ़ो(0) - (x)) / 7)
#अन्यथा
#घोषणा xip_elapsed_since(x)	(चिन्हित)((~xip_omap_mpu_समयr_पढ़ो(0) - (x)) / 6)
#पूर्ण_अगर

/*
 * xip_cpu_idle() is used when रुकोing क्रम a delay equal or larger than
 * the प्रणाली समयr tick period.  This should put the CPU पूर्णांकo idle mode
 * to save घातer and to be woken up only when some पूर्णांकerrupts are pending.
 * As above, this should not rely upon standard kernel code.
 */

#घोषणा xip_cpu_idle()  यंत्र अस्थिर ("mcr p15, 0, %0, c7, c0, 4" :: "r" (1))

#पूर्ण_अगर /* __ARCH_OMAP_MTD_XIP_H__ */
