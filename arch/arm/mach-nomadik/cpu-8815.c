<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright STMicroelectronics, 2007.
 */

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/mach-types.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>

/*
 * These are the only hard-coded address offsets we still have to use.
 */
#घोषणा NOMADIK_FSMC_BASE	0x10100000	/* FSMC रेजिस्टरs */
#घोषणा NOMADIK_SDRAMC_BASE	0x10110000	/* SDRAM Controller */
#घोषणा NOMADIK_CLCDC_BASE	0x10120000	/* CLCD Controller */
#घोषणा NOMADIK_MDIF_BASE	0x10120000	/* MDIF */
#घोषणा NOMADIK_DMA0_BASE	0x10130000	/* DMA0 Controller */
#घोषणा NOMADIK_IC_BASE		0x10140000	/* Vectored Irq Controller */
#घोषणा NOMADIK_DMA1_BASE	0x10150000	/* DMA1 Controller */
#घोषणा NOMADIK_USB_BASE	0x10170000	/* USB-OTG conf reg base */
#घोषणा NOMADIK_CRYP_BASE	0x10180000	/* Crypto processor */
#घोषणा NOMADIK_SHA1_BASE	0x10190000	/* SHA-1 Processor */
#घोषणा NOMADIK_XTI_BASE	0x101A0000	/* XTI */
#घोषणा NOMADIK_RNG_BASE	0x101B0000	/* Ranकरोm number generator */
#घोषणा NOMADIK_SRC_BASE	0x101E0000	/* SRC base */
#घोषणा NOMADIK_WDOG_BASE	0x101E1000	/* Watchकरोg */
#घोषणा NOMADIK_MTU0_BASE	0x101E2000	/* Multiple Timer 0 */
#घोषणा NOMADIK_MTU1_BASE	0x101E3000	/* Multiple Timer 1 */
#घोषणा NOMADIK_GPIO0_BASE	0x101E4000	/* GPIO0 */
#घोषणा NOMADIK_GPIO1_BASE	0x101E5000	/* GPIO1 */
#घोषणा NOMADIK_GPIO2_BASE	0x101E6000	/* GPIO2 */
#घोषणा NOMADIK_GPIO3_BASE	0x101E7000	/* GPIO3 */
#घोषणा NOMADIK_RTC_BASE	0x101E8000	/* Real Time Clock base */
#घोषणा NOMADIK_PMU_BASE	0x101E9000	/* Power Management Unit */
#घोषणा NOMADIK_OWM_BASE	0x101EA000	/* One wire master */
#घोषणा NOMADIK_SCR_BASE	0x101EF000	/* Secure Control रेजिस्टरs */
#घोषणा NOMADIK_MSP2_BASE	0x101F0000	/* MSP 2 पूर्णांकerface */
#घोषणा NOMADIK_MSP1_BASE	0x101F1000	/* MSP 1 पूर्णांकerface */
#घोषणा NOMADIK_UART2_BASE	0x101F2000	/* UART 2 पूर्णांकerface */
#घोषणा NOMADIK_SSIRx_BASE	0x101F3000	/* SSI 8-ch rx पूर्णांकerface */
#घोषणा NOMADIK_SSITx_BASE	0x101F4000	/* SSI 8-ch tx पूर्णांकerface */
#घोषणा NOMADIK_MSHC_BASE	0x101F5000	/* Memory Stick(Pro) Host */
#घोषणा NOMADIK_SDI_BASE	0x101F6000	/* SD-card/MM-Card */
#घोषणा NOMADIK_I2C1_BASE	0x101F7000	/* I2C1 पूर्णांकerface */
#घोषणा NOMADIK_I2C0_BASE	0x101F8000	/* I2C0 पूर्णांकerface */
#घोषणा NOMADIK_MSP0_BASE	0x101F9000	/* MSP 0 पूर्णांकerface */
#घोषणा NOMADIK_FIRDA_BASE	0x101FA000	/* FIrDA पूर्णांकerface */
#घोषणा NOMADIK_UART1_BASE	0x101FB000	/* UART 1 पूर्णांकerface */
#घोषणा NOMADIK_SSP_BASE	0x101FC000	/* SSP पूर्णांकerface */
#घोषणा NOMADIK_UART0_BASE	0x101FD000	/* UART 0 पूर्णांकerface */
#घोषणा NOMADIK_SGA_BASE	0x101FE000	/* SGA पूर्णांकerface */
#घोषणा NOMADIK_L2CC_BASE	0x10210000	/* L2 Cache controller */
#घोषणा NOMADIK_UART1_VBASE	0xF01FB000

/* This is needed क्रम LL-debug/earlyprपूर्णांकk/debug-macro.S */
अटल काष्ठा map_desc cpu8815_io_desc[] __initdata = अणु
	अणु
		.भव =	NOMADIK_UART1_VBASE,
		.pfn =		__phys_to_pfn(NOMADIK_UART1_BASE),
		.length =	SZ_4K,
		.type =		MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल व्योम __init cpu8815_map_io(व्योम)
अणु
	iotable_init(cpu8815_io_desc, ARRAY_SIZE(cpu8815_io_desc));
पूर्ण

अटल व्योम cpu8815_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	व्योम __iomem *srcbase = ioremap(NOMADIK_SRC_BASE, SZ_4K);

	/* FIXME: use egpio when implemented */

	/* Write anything to Reset status रेजिस्टर */
	ग_लिखोl(1, srcbase + 0x18);
पूर्ण

अटल स्थिर अक्षर * cpu8815_board_compat[] = अणु
	"st,nomadik-nhk-15",
	"calaosystems,usb-s8815",
	शून्य,
पूर्ण;

DT_MACHINE_START(NOMADIK_DT, "Nomadik STn8815")
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.map_io		= cpu8815_map_io,
	.restart	= cpu8815_restart,
	.dt_compat      = cpu8815_board_compat,
MACHINE_END
