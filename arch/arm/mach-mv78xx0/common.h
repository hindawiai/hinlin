<शैली गुरु>
/*
 * arch/arm/mach-mv78xx0/common.h
 *
 * Core functions क्रम Marvell MV78xx0 SoCs
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __ARCH_MV78XX0_COMMON_H
#घोषणा __ARCH_MV78XX0_COMMON_H

#समावेश <linux/reboot.h>

काष्ठा mv643xx_eth_platक्रमm_data;
काष्ठा mv_sata_platक्रमm_data;

/*
 * Basic MV78xx0 init functions used early by machine-setup.
 */
पूर्णांक mv78xx0_core_index(व्योम);
व्योम mv78xx0_map_io(व्योम);
व्योम mv78xx0_init(व्योम);
व्योम mv78xx0_init_early(व्योम);
व्योम mv78xx0_init_irq(व्योम);

व्योम mv78xx0_setup_cpu_mbus(व्योम);
व्योम mv78xx0_setup_pcie_io_win(पूर्णांक winकरोw, u32 base, u32 size,
			       पूर्णांक maj, पूर्णांक min);
व्योम mv78xx0_setup_pcie_mem_win(पूर्णांक winकरोw, u32 base, u32 size,
				पूर्णांक maj, पूर्णांक min);

व्योम mv78xx0_pcie_id(u32 *dev, u32 *rev);

व्योम mv78xx0_ehci0_init(व्योम);
व्योम mv78xx0_ehci1_init(व्योम);
व्योम mv78xx0_ehci2_init(व्योम);
व्योम mv78xx0_ge00_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data);
व्योम mv78xx0_ge01_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data);
व्योम mv78xx0_ge10_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data);
व्योम mv78xx0_ge11_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data);
व्योम mv78xx0_pcie_init(पूर्णांक init_port0, पूर्णांक init_port1);
व्योम mv78xx0_sata_init(काष्ठा mv_sata_platक्रमm_data *sata_data);
व्योम mv78xx0_uart0_init(व्योम);
व्योम mv78xx0_uart1_init(व्योम);
व्योम mv78xx0_uart2_init(व्योम);
व्योम mv78xx0_uart3_init(व्योम);
व्योम mv78xx0_i2c_init(व्योम);
व्योम mv78xx0_restart(क्रमागत reboot_mode, स्थिर अक्षर *);

बाह्य व्योम mv78xx0_समयr_init(व्योम);


#पूर्ण_अगर
