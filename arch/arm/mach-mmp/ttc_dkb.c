<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/ttc_dkb.c
 *
 *  Support क्रम the Marvell PXA910-based TTC_DKB Development Platक्रमm.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/onenand.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_data/pca953x.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/mfd/88pm860x.h>
#समावेश <linux/platक्रमm_data/mv_usb.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश "addr-map.h"
#समावेश "mfp-pxa910.h"
#समावेश "pxa910.h"
#समावेश "irqs.h"
#समावेश "regs-usb.h"

#समावेश "common.h"

#घोषणा TTCDKB_GPIO_EXT0(x)	(MMP_NR_BUILTIN_GPIO + ((x < 0) ? 0 :	\
				((x < 16) ? x : 15)))
#घोषणा TTCDKB_GPIO_EXT1(x)	(MMP_NR_BUILTIN_GPIO + 16 + ((x < 0) ? 0 : \
				((x < 16) ? x : 15)))

/*
 * 16 board पूर्णांकerrupts -- MAX7312 GPIO expander
 * 16 board पूर्णांकerrupts -- PCA9575 GPIO expander
 * 24 board पूर्णांकerrupts -- 88PM860x PMIC
 */
#घोषणा TTCDKB_NR_IRQS		(MMP_NR_IRQS + 16 + 16 + 24)

अटल अचिन्हित दीर्घ ttc_dkb_pin_config[] __initdata = अणु
	/* UART2 */
	GPIO47_UART2_RXD,
	GPIO48_UART2_TXD,

	/* DFI */
	DF_IO0_ND_IO0,
	DF_IO1_ND_IO1,
	DF_IO2_ND_IO2,
	DF_IO3_ND_IO3,
	DF_IO4_ND_IO4,
	DF_IO5_ND_IO5,
	DF_IO6_ND_IO6,
	DF_IO7_ND_IO7,
	DF_IO8_ND_IO8,
	DF_IO9_ND_IO9,
	DF_IO10_ND_IO10,
	DF_IO11_ND_IO11,
	DF_IO12_ND_IO12,
	DF_IO13_ND_IO13,
	DF_IO14_ND_IO14,
	DF_IO15_ND_IO15,
	DF_nCS0_SM_nCS2_nCS0,
	DF_ALE_SM_WEn_ND_ALE,
	DF_CLE_SM_OEn_ND_CLE,
	DF_WEn_DF_WEn,
	DF_REn_DF_REn,
	DF_RDY0_DF_RDY0,
पूर्ण;

अटल काष्ठा pxa_gpio_platक्रमm_data pxa910_gpio_pdata = अणु
	.irq_base	= MMP_GPIO_TO_IRQ(0),
पूर्ण;

अटल काष्ठा mtd_partition ttc_dkb_onenand_partitions[] = अणु
	अणु
		.name		= "bootloader",
		.offset		= 0,
		.size		= SZ_1M,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "reserved",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_128K,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "reserved",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_8M,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "kernel",
		.offset		= MTDPART_OFS_APPEND,
		.size		= (SZ_2M + SZ_1M),
		.mask_flags	= 0,
	पूर्ण, अणु
		.name		= "filesystem",
		.offset		= MTDPART_OFS_APPEND,
		.size		= SZ_32M + SZ_16M,
		.mask_flags	= 0,
	पूर्ण
पूर्ण;

अटल काष्ठा onenand_platक्रमm_data ttc_dkb_onenand_info = अणु
	.parts		= ttc_dkb_onenand_partitions,
	.nr_parts	= ARRAY_SIZE(ttc_dkb_onenand_partitions),
पूर्ण;

अटल काष्ठा resource ttc_dkb_resource_onenand[] = अणु
	[0] = अणु
		.start	= SMC_CS0_PHYS_BASE,
		.end	= SMC_CS0_PHYS_BASE + SZ_1M,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ttc_dkb_device_onenand = अणु
	.name		= "onenand-flash",
	.id		= -1,
	.resource	= ttc_dkb_resource_onenand,
	.num_resources	= ARRAY_SIZE(ttc_dkb_resource_onenand),
	.dev		= अणु
		.platक्रमm_data	= &ttc_dkb_onenand_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *ttc_dkb_devices[] = अणु
	&pxa910_device_gpio,
	&pxa910_device_rtc,
	&ttc_dkb_device_onenand,
पूर्ण;

अटल काष्ठा pca953x_platक्रमm_data max7312_data[] = अणु
	अणु
		.gpio_base	= TTCDKB_GPIO_EXT0(0),
		.irq_base	= MMP_NR_IRQS,
	पूर्ण,
पूर्ण;

अटल काष्ठा pm860x_platक्रमm_data ttc_dkb_pm8607_info = अणु
	.irq_base       = IRQ_BOARD_START,
पूर्ण;

अटल काष्ठा i2c_board_info ttc_dkb_i2c_info[] = अणु
	अणु
		.type           = "88PM860x",
		.addr           = 0x34,
		.platक्रमm_data  = &ttc_dkb_pm8607_info,
		.irq            = IRQ_PXA910_PMIC_INT,
	पूर्ण,
	अणु
		.type		= "max7312",
		.addr		= 0x23,
		.irq		= MMP_GPIO_TO_IRQ(80),
		.platक्रमm_data	= &max7312_data,
	पूर्ण,
पूर्ण;

#अगर IS_ENABLED(CONFIG_USB_SUPPORT)
#अगर IS_ENABLED(CONFIG_USB_MV_UDC) || IS_ENABLED(CONFIG_USB_EHCI_MV_U2O)

अटल काष्ठा mv_usb_platक्रमm_data ttc_usb_pdata = अणु
	.vbus		= शून्य,
	.mode		= MV_USB_MODE_OTG,
	.otg_क्रमce_a_bus_req = 1,
	.phy_init	= pxa_usb_phy_init,
	.phy_deinit	= pxa_usb_phy_deinit,
	.set_vbus	= शून्य,
पूर्ण;
#पूर्ण_अगर
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_MARVELL)
अटल काष्ठा pxa3xx_nand_platक्रमm_data dkb_nand_info = अणुपूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MMP_DISP)
/* path config */
#घोषणा CFG_IOPADMODE(iopad)   (iopad)  /* 0x0 ~ 0xd */
#घोषणा SCLK_SOURCE_SELECT(x)  (x << 30) /* 0x0 ~ 0x3 */
/* link config */
#घोषणा CFG_DUMBMODE(mode)     (mode << 28) /* 0x0 ~ 0x6*/
अटल काष्ठा mmp_mach_path_config dkb_disp_config[] = अणु
	[0] = अणु
		.name = "mmp-parallel",
		.overlay_num = 2,
		.output_type = PATH_OUT_PARALLEL,
		.path_config = CFG_IOPADMODE(0x1)
			| SCLK_SOURCE_SELECT(0x1),
		.link_config = CFG_DUMBMODE(0x2),
	पूर्ण,
पूर्ण;

अटल काष्ठा mmp_mach_plat_info dkb_disp_info = अणु
	.name = "mmp-disp",
	.clk_name = "disp0",
	.path_num = 1,
	.paths = dkb_disp_config,
पूर्ण;

अटल काष्ठा mmp_buffer_driver_mach_info dkb_fb_info = अणु
	.name = "mmp-fb",
	.path_name = "mmp-parallel",
	.overlay_id = 0,
	.dmafetch_id = 1,
	.शेष_pixfmt = PIXFMT_RGB565,
पूर्ण;

अटल व्योम dkb_tpo_panel_घातer(पूर्णांक on)
अणु
	पूर्णांक err;
	u32 spi_reset = mfp_to_gpio(MFP_PIN_GPIO106);

	अगर (on) अणु
		err = gpio_request(spi_reset, "TPO_LCD_SPI_RESET");
		अगर (err) अणु
			pr_err("failed to request GPIO for TPO LCD RESET\n");
			वापस;
		पूर्ण
		gpio_direction_output(spi_reset, 0);
		udelay(100);
		gpio_set_value(spi_reset, 1);
		gpio_मुक्त(spi_reset);
	पूर्ण अन्यथा अणु
		err = gpio_request(spi_reset, "TPO_LCD_SPI_RESET");
		अगर (err) अणु
			pr_err("failed to request LCD RESET gpio\n");
			वापस;
		पूर्ण
		gpio_set_value(spi_reset, 0);
		gpio_मुक्त(spi_reset);
	पूर्ण
पूर्ण

अटल काष्ठा mmp_mach_panel_info dkb_tpo_panel_info = अणु
	.name = "tpo-hvga",
	.plat_path_name = "mmp-parallel",
	.plat_set_onoff = dkb_tpo_panel_घातer,
पूर्ण;

अटल काष्ठा spi_board_info spi_board_info[] __initdata = अणु
	अणु
		.modalias       = "tpo-hvga",
		.platक्रमm_data  = &dkb_tpo_panel_info,
		.bus_num        = 5,
	पूर्ण
पूर्ण;

अटल व्योम __init add_disp(व्योम)
अणु
	pxa_रेजिस्टर_device(&pxa910_device_disp,
		&dkb_disp_info, माप(dkb_disp_info));
	spi_रेजिस्टर_board_info(spi_board_info, ARRAY_SIZE(spi_board_info));
	pxa_रेजिस्टर_device(&pxa910_device_fb,
		&dkb_fb_info, माप(dkb_fb_info));
	pxa_रेजिस्टर_device(&pxa910_device_panel,
		&dkb_tpo_panel_info, माप(dkb_tpo_panel_info));
पूर्ण
#पूर्ण_अगर

अटल व्योम __init ttc_dkb_init(व्योम)
अणु
	mfp_config(ARRAY_AND_SIZE(ttc_dkb_pin_config));

	/* on-chip devices */
	pxa910_add_uart(1);
#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_MARVELL)
	pxa910_add_nand(&dkb_nand_info);
#पूर्ण_अगर

	/* off-chip devices */
	pxa910_add_twsi(0, शून्य, ARRAY_AND_SIZE(ttc_dkb_i2c_info));
	platक्रमm_device_add_data(&pxa910_device_gpio, &pxa910_gpio_pdata,
				 माप(काष्ठा pxa_gpio_platक्रमm_data));
	platक्रमm_add_devices(ARRAY_AND_SIZE(ttc_dkb_devices));

#अगर IS_ENABLED(CONFIG_USB_SUPPORT)
#अगर IS_ENABLED(CONFIG_PHY_PXA_USB)
	platक्रमm_device_रेजिस्टर(&pxa168_device_usb_phy);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_USB_MV_UDC)
	pxa168_device_u2o.dev.platक्रमm_data = &ttc_usb_pdata;
	platक्रमm_device_रेजिस्टर(&pxa168_device_u2o);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_USB_EHCI_MV_U2O)
	pxa168_device_u2oehci.dev.platक्रमm_data = &ttc_usb_pdata;
	platक्रमm_device_रेजिस्टर(&pxa168_device_u2oehci);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_USB_MV_OTG)
	pxa168_device_u2ootg.dev.platक्रमm_data = &ttc_usb_pdata;
	platक्रमm_device_रेजिस्टर(&pxa168_device_u2ootg);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MMP_DISP)
	add_disp();
#पूर्ण_अगर
पूर्ण

MACHINE_START(TTC_DKB, "PXA910-based TTC_DKB Development Platform")
	.map_io		= mmp_map_io,
	.nr_irqs	= TTCDKB_NR_IRQS,
	.init_irq       = pxa910_init_irq,
	.init_समय	= pxa910_समयr_init,
	.init_machine   = ttc_dkb_init,
	.restart	= mmp_restart,
MACHINE_END
