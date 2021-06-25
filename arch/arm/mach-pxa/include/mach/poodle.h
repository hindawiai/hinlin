<शैली गुरु>
/*
 * arch/arm/mach-pxa/include/mach/poodle.h
 *
 * May be copied or modअगरied under the terms of the GNU General Public
 * License.  See linux/COPYING क्रम more inक्रमmation.
 *
 * Based on:
 *   arch/arm/mach-sa1100/include/mach/collie.h
 *
 * ChangeLog:
 *   04-06-2001 Lineo Japan, Inc.
 *   04-16-2001 SHARP Corporation
 *   Update to 2.6 John Lenz
 */
#अगर_अघोषित __ASM_ARCH_POODLE_H
#घोषणा __ASM_ARCH_POODLE_H  1

#समावेश "irqs.h" /* PXA_GPIO_TO_IRQ */

/*
 * GPIOs
 */
/* PXA GPIOs */
#घोषणा POODLE_GPIO_ON_KEY		(0)
#घोषणा POODLE_GPIO_AC_IN		(1)
#घोषणा POODLE_GPIO_CO			16
#घोषणा POODLE_GPIO_TP_INT		(5)
#घोषणा POODLE_GPIO_TP_CS		(24)
#घोषणा POODLE_GPIO_WAKEUP		(11)	/* change battery */
#घोषणा POODLE_GPIO_GA_INT		(10)
#घोषणा POODLE_GPIO_IR_ON		(22)
#घोषणा POODLE_GPIO_HP_IN		(4)
#घोषणा POODLE_GPIO_CF_IRQ		(17)
#घोषणा POODLE_GPIO_CF_CD		(14)
#घोषणा POODLE_GPIO_CF_STSCHG		(14)
#घोषणा POODLE_GPIO_SD_PWR		(33)
#घोषणा POODLE_GPIO_SD_PWR1		(3)
#घोषणा POODLE_GPIO_nSD_CLK		(6)
#घोषणा POODLE_GPIO_nSD_WP		(7)
#घोषणा POODLE_GPIO_nSD_INT		(8)
#घोषणा POODLE_GPIO_nSD_DETECT		(9)
#घोषणा POODLE_GPIO_MAIN_BAT_LOW	(13)
#घोषणा POODLE_GPIO_BAT_COVER		(13)
#घोषणा POODLE_GPIO_USB_PULLUP		(20)
#घोषणा POODLE_GPIO_ADC_TEMP_ON		(21)
#घोषणा POODLE_GPIO_BYPASS_ON		(36)
#घोषणा POODLE_GPIO_CHRG_ON		(38)
#घोषणा POODLE_GPIO_CHRG_FULL		(16)
#घोषणा POODLE_GPIO_DISCHARGE_ON        (42) /* Enable battery disअक्षरge */

/* PXA GPIOs */
#घोषणा POODLE_IRQ_GPIO_ON_KEY		PXA_GPIO_TO_IRQ(0)
#घोषणा POODLE_IRQ_GPIO_AC_IN		PXA_GPIO_TO_IRQ(1)
#घोषणा POODLE_IRQ_GPIO_HP_IN		PXA_GPIO_TO_IRQ(4)
#घोषणा POODLE_IRQ_GPIO_CO		PXA_GPIO_TO_IRQ(16)
#घोषणा POODLE_IRQ_GPIO_TP_INT		PXA_GPIO_TO_IRQ(5)
#घोषणा POODLE_IRQ_GPIO_WAKEUP		PXA_GPIO_TO_IRQ(11)
#घोषणा POODLE_IRQ_GPIO_GA_INT		PXA_GPIO_TO_IRQ(10)
#घोषणा POODLE_IRQ_GPIO_CF_IRQ		PXA_GPIO_TO_IRQ(17)
#घोषणा POODLE_IRQ_GPIO_CF_CD		PXA_GPIO_TO_IRQ(14)
#घोषणा POODLE_IRQ_GPIO_nSD_INT		PXA_GPIO_TO_IRQ(8)
#घोषणा POODLE_IRQ_GPIO_nSD_DETECT	PXA_GPIO_TO_IRQ(9)
#घोषणा POODLE_IRQ_GPIO_MAIN_BAT_LOW	PXA_GPIO_TO_IRQ(13)

/* SCOOP GPIOs */
#घोषणा POODLE_SCOOP_CHARGE_ON	SCOOP_GPCR_PA11
#घोषणा POODLE_SCOOP_CP401	SCOOP_GPCR_PA13
#घोषणा POODLE_SCOOP_VPEN	SCOOP_GPCR_PA18
#घोषणा POODLE_SCOOP_L_PCLK	SCOOP_GPCR_PA20
#घोषणा POODLE_SCOOP_L_LCLK	SCOOP_GPCR_PA21
#घोषणा POODLE_SCOOP_HS_OUT	SCOOP_GPCR_PA22

#घोषणा POODLE_SCOOP_IO_सूची	( POODLE_SCOOP_VPEN | POODLE_SCOOP_HS_OUT )
#घोषणा POODLE_SCOOP_IO_OUT	( 0 )

#घोषणा POODLE_SCOOP_GPIO_BASE	(PXA_NR_BUILTIN_GPIO)
#घोषणा POODLE_GPIO_CHARGE_ON	(POODLE_SCOOP_GPIO_BASE + 0)
#घोषणा POODLE_GPIO_CP401	(POODLE_SCOOP_GPIO_BASE + 2)
#घोषणा POODLE_GPIO_VPEN	(POODLE_SCOOP_GPIO_BASE + 7)
#घोषणा POODLE_GPIO_L_PCLK	(POODLE_SCOOP_GPIO_BASE + 9)
#घोषणा POODLE_GPIO_L_LCLK	(POODLE_SCOOP_GPIO_BASE + 10)
#घोषणा POODLE_GPIO_HS_OUT	(POODLE_SCOOP_GPIO_BASE + 11)

#घोषणा POODLE_LOCOMO_GPIO_AMP_ON      LOCOMO_GPIO(8)
#घोषणा POODLE_LOCOMO_GPIO_MUTE_L      LOCOMO_GPIO(10)
#घोषणा POODLE_LOCOMO_GPIO_MUTE_R      LOCOMO_GPIO(11)
#घोषणा POODLE_LOCOMO_GPIO_232VCC_ON   LOCOMO_GPIO(12)
#घोषणा POODLE_LOCOMO_GPIO_JK_B        LOCOMO_GPIO(13)

#घोषणा POODLE_NR_IRQS		(IRQ_BOARD_START + 4)	/* 4 क्रम LoCoMo */

बाह्य काष्ठा platक्रमm_device poodle_locomo_device;

#पूर्ण_अगर /* __ASM_ARCH_POODLE_H  */
