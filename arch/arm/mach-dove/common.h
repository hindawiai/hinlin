<शैली गुरु>
/*
 * arch/arm/mach-करोve/common.h
 *
 * Core functions क्रम Marvell Dove 88AP510 System On Chip
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __ARCH_DOVE_COMMON_H
#घोषणा __ARCH_DOVE_COMMON_H

#समावेश <linux/reboot.h>

काष्ठा mv643xx_eth_platक्रमm_data;
काष्ठा mv_sata_platक्रमm_data;

बाह्य व्योम करोve_समयr_init(व्योम);

/*
 * Basic Dove init functions used early by machine-setup.
 */
व्योम करोve_map_io(व्योम);
व्योम करोve_init(व्योम);
व्योम करोve_init_early(व्योम);
व्योम करोve_init_irq(व्योम);
व्योम करोve_setup_cpu_wins(व्योम);
व्योम करोve_ge00_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data);
व्योम करोve_sata_init(काष्ठा mv_sata_platक्रमm_data *sata_data);
#अगर_घोषित CONFIG_PCI
व्योम करोve_pcie_init(पूर्णांक init_port0, पूर्णांक init_port1);
#अन्यथा
अटल अंतरभूत व्योम करोve_pcie_init(पूर्णांक init_port0, पूर्णांक init_port1) अणु पूर्ण
#पूर्ण_अगर
व्योम करोve_ehci0_init(व्योम);
व्योम करोve_ehci1_init(व्योम);
व्योम करोve_uart0_init(व्योम);
व्योम करोve_uart1_init(व्योम);
व्योम करोve_uart2_init(व्योम);
व्योम करोve_uart3_init(व्योम);
व्योम करोve_spi0_init(व्योम);
व्योम करोve_spi1_init(व्योम);
व्योम करोve_i2c_init(व्योम);
व्योम करोve_sdio0_init(व्योम);
व्योम करोve_sdio1_init(व्योम);
व्योम करोve_restart(क्रमागत reboot_mode, स्थिर अक्षर *);

#पूर्ण_अगर
