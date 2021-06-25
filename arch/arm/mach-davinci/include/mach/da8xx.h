<शैली गुरु>
/*
 * Chip specअगरic defines क्रम DA8XX/OMAP L1XX SoC
 *
 * Author: Mark A. Greer <mgreer@mvista.com>
 *
 * 2007, 2009-2010 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#अगर_अघोषित __ASM_ARCH_DAVINCI_DA8XX_H
#घोषणा __ASM_ARCH_DAVINCI_DA8XX_H

#समावेश <video/da8xx-fb.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/davinci_emac.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/platक्रमm_data/davinci_asp.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>
#समावेश <linux/videodev2.h>

#समावेश <mach/serial.h>
#समावेश <mach/pm.h>
#समावेश <linux/platक्रमm_data/edma.h>
#समावेश <linux/platक्रमm_data/i2c-davinci.h>
#समावेश <linux/platक्रमm_data/mmc-davinci.h>
#समावेश <linux/platक्रमm_data/usb-davinci.h>
#समावेश <linux/platक्रमm_data/spi-davinci.h>
#समावेश <linux/platक्रमm_data/uio_pruss.h>

#समावेश <media/davinci/vpअगर_types.h>

बाह्य व्योम __iomem *da8xx_syscfg0_base;
बाह्य व्योम __iomem *da8xx_syscfg1_base;

/*
 * If the DA850/OMAP-L138/AM18x SoC on board is of a higher speed grade
 * (than the regular 300MHz variant), the board code should set this up
 * with the supported speed beक्रमe calling da850_रेजिस्टर_cpufreq().
 */
बाह्य अचिन्हित पूर्णांक da850_max_speed;

/*
 * The cp_पूर्णांकc पूर्णांकerrupt controller क्रम the da8xx isn't in the same
 * chunk of physical memory space as the other रेजिस्टरs (like it is
 * on the davincis) so it needs to be mapped separately.  It will be
 * mapped early on when the I/O space is mapped and we'll put it just
 * beक्रमe the I/O space in the processor's भव memory space.
 */
#घोषणा DA8XX_CP_INTC_BASE	0xfffee000
#घोषणा DA8XX_CP_INTC_SIZE	SZ_8K
#घोषणा DA8XX_CP_INTC_VIRT	(IO_VIRT - DA8XX_CP_INTC_SIZE - SZ_4K)

#घोषणा DA8XX_SYSCFG0_BASE	(IO_PHYS + 0x14000)
#घोषणा DA8XX_SYSCFG0_VIRT(x)	(da8xx_syscfg0_base + (x))
#घोषणा DA8XX_JTAG_ID_REG	0x18
#घोषणा DA8XX_HOST1CFG_REG	0x44
#घोषणा DA8XX_CHIPSIG_REG	0x174
#घोषणा DA8XX_CFGCHIP0_REG	0x17c
#घोषणा DA8XX_CFGCHIP1_REG	0x180
#घोषणा DA8XX_CFGCHIP2_REG	0x184
#घोषणा DA8XX_CFGCHIP3_REG	0x188
#घोषणा DA8XX_CFGCHIP4_REG	0x18c

#घोषणा DA8XX_SYSCFG1_BASE	(IO_PHYS + 0x22C000)
#घोषणा DA8XX_SYSCFG1_VIRT(x)	(da8xx_syscfg1_base + (x))
#घोषणा DA8XX_DEEPSLEEP_REG	0x8
#घोषणा DA8XX_PWRDN_REG		0x18

#घोषणा DA8XX_PSC0_BASE		0x01c10000
#घोषणा DA8XX_PLL0_BASE		0x01c11000
#घोषणा DA8XX_TIMER64P0_BASE	0x01c20000
#घोषणा DA8XX_TIMER64P1_BASE	0x01c21000
#घोषणा DA8XX_VPIF_BASE		0x01e17000
#घोषणा DA8XX_GPIO_BASE		0x01e26000
#घोषणा DA8XX_PSC1_BASE		0x01e27000

#घोषणा DA8XX_DSP_L2_RAM_BASE	0x11800000
#घोषणा DA8XX_DSP_L1P_RAM_BASE	(DA8XX_DSP_L2_RAM_BASE + 0x600000)
#घोषणा DA8XX_DSP_L1D_RAM_BASE	(DA8XX_DSP_L2_RAM_BASE + 0x700000)

#घोषणा DA8XX_AEMIF_CS2_BASE	0x60000000
#घोषणा DA8XX_AEMIF_CS3_BASE	0x62000000
#घोषणा DA8XX_AEMIF_CTL_BASE	0x68000000
#घोषणा DA8XX_SHARED_RAM_BASE	0x80000000
#घोषणा DA8XX_ARM_RAM_BASE	0xffff0000

व्योम da830_init(व्योम);
व्योम da830_init_irq(व्योम);
व्योम da830_init_समय(व्योम);
व्योम da830_रेजिस्टर_घड़ीs(व्योम);

व्योम da850_init(व्योम);
व्योम da850_init_irq(व्योम);
व्योम da850_init_समय(व्योम);
व्योम da850_रेजिस्टर_घड़ीs(व्योम);

पूर्णांक da830_रेजिस्टर_edma(काष्ठा edma_rsv_info *rsv);
पूर्णांक da850_रेजिस्टर_edma(काष्ठा edma_rsv_info *rsv[2]);
पूर्णांक da8xx_रेजिस्टर_i2c(पूर्णांक instance, काष्ठा davinci_i2c_platक्रमm_data *pdata);
पूर्णांक da8xx_रेजिस्टर_spi_bus(पूर्णांक instance, अचिन्हित num_chipselect);
पूर्णांक da8xx_रेजिस्टर_watchकरोg(व्योम);
पूर्णांक da8xx_रेजिस्टर_usb_phy(व्योम);
पूर्णांक da8xx_रेजिस्टर_usb20(अचिन्हित mA, अचिन्हित potpgt);
पूर्णांक da8xx_रेजिस्टर_usb11(काष्ठा da8xx_ohci_root_hub *pdata);
पूर्णांक da8xx_रेजिस्टर_usb_phy_घड़ीs(व्योम);
पूर्णांक da850_रेजिस्टर_sata_refclk(पूर्णांक rate);
पूर्णांक da8xx_रेजिस्टर_emac(व्योम);
पूर्णांक da8xx_रेजिस्टर_uio_pruss(व्योम);
पूर्णांक da8xx_रेजिस्टर_lcdc(काष्ठा da8xx_lcdc_platक्रमm_data *pdata);
पूर्णांक da8xx_रेजिस्टर_mmcsd0(काष्ठा davinci_mmc_config *config);
पूर्णांक da850_रेजिस्टर_mmcsd1(काष्ठा davinci_mmc_config *config);
व्योम da8xx_रेजिस्टर_mcasp(पूर्णांक id, काष्ठा snd_platक्रमm_data *pdata);
पूर्णांक da8xx_रेजिस्टर_rtc(व्योम);
पूर्णांक da8xx_रेजिस्टर_gpio(व्योम *pdata);
पूर्णांक da850_रेजिस्टर_cpufreq(अक्षर *async_clk);
पूर्णांक da8xx_रेजिस्टर_cpuidle(व्योम);
व्योम __iomem *da8xx_get_mem_ctlr(व्योम);
पूर्णांक da850_रेजिस्टर_sata(अचिन्हित दीर्घ refclkpn);
पूर्णांक da850_रेजिस्टर_vpअगर(व्योम);
पूर्णांक da850_रेजिस्टर_vpअगर_display
			(काष्ठा vpअगर_display_config *display_config);
पूर्णांक da850_रेजिस्टर_vpअगर_capture
			(काष्ठा vpअगर_capture_config *capture_config);
व्योम da8xx_rproc_reserve_cma(व्योम);
पूर्णांक da8xx_रेजिस्टर_rproc(व्योम);
पूर्णांक da850_रेजिस्टर_gpio(व्योम);
पूर्णांक da830_रेजिस्टर_gpio(व्योम);
काष्ठा regmap *da8xx_get_cfgchip(व्योम);

बाह्य काष्ठा platक्रमm_device da8xx_serial_device[];
बाह्य काष्ठा emac_platक्रमm_data da8xx_emac_pdata;
बाह्य काष्ठा da8xx_lcdc_platक्रमm_data sharp_lcd035q3dg01_pdata;
बाह्य काष्ठा da8xx_lcdc_platक्रमm_data sharp_lk043t1dg01_pdata;


बाह्य स्थिर लघु da830_emअगर25_pins[];
बाह्य स्थिर लघु da830_spi0_pins[];
बाह्य स्थिर लघु da830_spi1_pins[];
बाह्य स्थिर लघु da830_mmc_sd_pins[];
बाह्य स्थिर लघु da830_uart0_pins[];
बाह्य स्थिर लघु da830_uart1_pins[];
बाह्य स्थिर लघु da830_uart2_pins[];
बाह्य स्थिर लघु da830_usb20_pins[];
बाह्य स्थिर लघु da830_usb11_pins[];
बाह्य स्थिर लघु da830_uhpi_pins[];
बाह्य स्थिर लघु da830_cpgmac_pins[];
बाह्य स्थिर लघु da830_emअगर3c_pins[];
बाह्य स्थिर लघु da830_mcasp0_pins[];
बाह्य स्थिर लघु da830_mcasp1_pins[];
बाह्य स्थिर लघु da830_mcasp2_pins[];
बाह्य स्थिर लघु da830_i2c0_pins[];
बाह्य स्थिर लघु da830_i2c1_pins[];
बाह्य स्थिर लघु da830_lcdcntl_pins[];
बाह्य स्थिर लघु da830_pwm_pins[];
बाह्य स्थिर लघु da830_ecap0_pins[];
बाह्य स्थिर लघु da830_ecap1_pins[];
बाह्य स्थिर लघु da830_ecap2_pins[];
बाह्य स्थिर लघु da830_eqep0_pins[];
बाह्य स्थिर लघु da830_eqep1_pins[];
बाह्य स्थिर लघु da850_vpअगर_capture_pins[];
बाह्य स्थिर लघु da850_vpअगर_display_pins[];

बाह्य स्थिर लघु da850_i2c0_pins[];
बाह्य स्थिर लघु da850_i2c1_pins[];
बाह्य स्थिर लघु da850_lcdcntl_pins[];

#पूर्ण_अगर /* __ASM_ARCH_DAVINCI_DA8XX_H */
