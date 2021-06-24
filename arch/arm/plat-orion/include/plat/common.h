<शैली गुरु>
/*
 * arch/arm/plat-orion/include/plat/common.h
 *
 * Marvell Orion SoC common setup code used by dअगरferent mach-/common.c
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __PLAT_COMMON_H
#समावेश <linux/mv643xx_eth.h>
#समावेश <linux/platक्रमm_data/usb-ehci-orion.h>

काष्ठा dsa_chip_data;
काष्ठा mv_sata_platक्रमm_data;

व्योम __init orion_uart0_init(व्योम __iomem *membase,
			     resource_माप_प्रकार mapbase,
			     अचिन्हित पूर्णांक irq,
			     काष्ठा clk *clk);

व्योम __init orion_uart1_init(व्योम __iomem *membase,
			     resource_माप_प्रकार mapbase,
			     अचिन्हित पूर्णांक irq,
			     काष्ठा clk *clk);

व्योम __init orion_uart2_init(व्योम __iomem *membase,
			     resource_माप_प्रकार mapbase,
			     अचिन्हित पूर्णांक irq,
			     काष्ठा clk *clk);

व्योम __init orion_uart3_init(व्योम __iomem *membase,
			     resource_माप_प्रकार mapbase,
			     अचिन्हित पूर्णांक irq,
			     काष्ठा clk *clk);

व्योम __init orion_rtc_init(अचिन्हित दीर्घ mapbase,
			   अचिन्हित दीर्घ irq);

व्योम __init orion_ge00_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data,
			    अचिन्हित दीर्घ mapbase,
			    अचिन्हित दीर्घ irq,
			    अचिन्हित दीर्घ irq_err,
			    अचिन्हित पूर्णांक tx_csum_limit);

व्योम __init orion_ge01_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data,
			    अचिन्हित दीर्घ mapbase,
			    अचिन्हित दीर्घ irq,
			    अचिन्हित पूर्णांक tx_csum_limit);

व्योम __init orion_ge10_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data,
			    अचिन्हित दीर्घ mapbase,
			    अचिन्हित दीर्घ irq);

व्योम __init orion_ge11_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data,
			    अचिन्हित दीर्घ mapbase,
			    अचिन्हित दीर्घ irq);

व्योम __init orion_ge00_चयन_init(काष्ठा dsa_chip_data *d);

व्योम __init orion_i2c_init(अचिन्हित दीर्घ mapbase,
			   अचिन्हित दीर्घ irq,
			   अचिन्हित दीर्घ freq_m);

व्योम __init orion_i2c_1_init(अचिन्हित दीर्घ mapbase,
			     अचिन्हित दीर्घ irq,
			     अचिन्हित दीर्घ freq_m);

व्योम __init orion_spi_init(अचिन्हित दीर्घ mapbase);

व्योम __init orion_spi_1_init(अचिन्हित दीर्घ mapbase);

व्योम __init orion_xor0_init(अचिन्हित दीर्घ mapbase_low,
			    अचिन्हित दीर्घ mapbase_high,
			    अचिन्हित दीर्घ irq_0,
			    अचिन्हित दीर्घ irq_1);

व्योम __init orion_xor1_init(अचिन्हित दीर्घ mapbase_low,
			    अचिन्हित दीर्घ mapbase_high,
			    अचिन्हित दीर्घ irq_0,
			    अचिन्हित दीर्घ irq_1);

व्योम __init orion_ehci_init(अचिन्हित दीर्घ mapbase,
			    अचिन्हित दीर्घ irq,
			    क्रमागत orion_ehci_phy_ver phy_version);

व्योम __init orion_ehci_1_init(अचिन्हित दीर्घ mapbase,
			      अचिन्हित दीर्घ irq);

व्योम __init orion_ehci_2_init(अचिन्हित दीर्घ mapbase,
			      अचिन्हित दीर्घ irq);

व्योम __init orion_sata_init(काष्ठा mv_sata_platक्रमm_data *sata_data,
			    अचिन्हित दीर्घ mapbase,
			    अचिन्हित दीर्घ irq);

व्योम __init orion_crypto_init(अचिन्हित दीर्घ mapbase,
			      अचिन्हित दीर्घ srambase,
			      अचिन्हित दीर्घ sram_size,
			      अचिन्हित दीर्घ irq);

व्योम __init orion_clkdev_add(स्थिर अक्षर *con_id, स्थिर अक्षर *dev_id,
			     काष्ठा clk *clk);

व्योम __init orion_clkdev_init(काष्ठा clk *tclk);
#पूर्ण_अगर
