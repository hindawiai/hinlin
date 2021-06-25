<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2011 Zhang, Keguang <keguang.zhang@gmail.com>
 */

#अगर_अघोषित __ASM_MACH_LOONGSON32_PLATFORM_H
#घोषणा __ASM_MACH_LOONGSON32_PLATFORM_H

#समावेश <linux/platक्रमm_device.h>

#समावेश <dma.h>
#समावेश <nand.h>

बाह्य काष्ठा platक्रमm_device ls1x_uart_pdev;
बाह्य काष्ठा platक्रमm_device ls1x_cpufreq_pdev;
बाह्य काष्ठा platक्रमm_device ls1x_eth0_pdev;
बाह्य काष्ठा platक्रमm_device ls1x_eth1_pdev;
बाह्य काष्ठा platक्रमm_device ls1x_ehci_pdev;
बाह्य काष्ठा platक्रमm_device ls1x_gpio0_pdev;
बाह्य काष्ठा platक्रमm_device ls1x_gpio1_pdev;
बाह्य काष्ठा platक्रमm_device ls1x_rtc_pdev;
बाह्य काष्ठा platक्रमm_device ls1x_wdt_pdev;

व्योम __init ls1x_clk_init(व्योम);
व्योम __init ls1x_rtc_set_extclk(काष्ठा platक्रमm_device *pdev);
व्योम __init ls1x_serial_set_uartclk(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* __ASM_MACH_LOONGSON32_PLATFORM_H */
