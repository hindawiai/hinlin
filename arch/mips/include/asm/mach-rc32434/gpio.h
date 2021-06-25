<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2002 Integrated Device Technology, Inc.
 *	All rights reserved.
 *
 * GPIO रेजिस्टर definition.
 *
 * Author : ryan.holmQVist@idt.com
 * Date	  : 20011005
 * Copyright (C) 2001, 2002 Ryan Holm <ryan.holmQVist@idt.com>
 * Copyright (C) 2008 Florian Fainelli <florian@खोलोwrt.org>
 */

#अगर_अघोषित _RC32434_GPIO_H_
#घोषणा _RC32434_GPIO_H_

काष्ठा rb532_gpio_reg अणु
	u32   gpiofunc;	  /* GPIO Function Register
			   * gpiofunc[x]==0 bit = gpio
			   * func[x]==1	 bit = altfunc
			   */
	u32   gpiocfg;	  /* GPIO Configuration Register
			   * gpiocfg[x]==0 bit = input
			   * gpiocfg[x]==1 bit = output
			   */
	u32   gpiod;	  /* GPIO Data Register
			   * gpiod[x] पढ़ो/ग_लिखो gpio pinX status
			   */
	u32   gpioilevel; /* GPIO Interrupt Status Register
			   * पूर्णांकerrupt level (see gpioistat)
			   */
	u32   gpioistat;  /* Gpio Interrupt Status Register
			   * istat[x] = (gpiod[x] == level[x])
			   * cleared in ISR (STICKY bits)
			   */
	u32   gpionmien;  /* GPIO Non-maskable Interrupt Enable Register */
पूर्ण;

/* UART GPIO संकेतs */
#घोषणा RC32434_UART0_SOUT	(1 << 0)
#घोषणा RC32434_UART0_SIN	(1 << 1)
#घोषणा RC32434_UART0_RTS	(1 << 2)
#घोषणा RC32434_UART0_CTS	(1 << 3)

/* M & P bus GPIO संकेतs */
#घोषणा RC32434_MP_BIT_22	(1 << 4)
#घोषणा RC32434_MP_BIT_23	(1 << 5)
#घोषणा RC32434_MP_BIT_24	(1 << 6)
#घोषणा RC32434_MP_BIT_25	(1 << 7)

/* CPU GPIO संकेतs */
#घोषणा RC32434_CPU_GPIO	(1 << 8)

/* Reserved GPIO संकेतs */
#घोषणा RC32434_AF_SPARE_6	(1 << 9)
#घोषणा RC32434_AF_SPARE_4	(1 << 10)
#घोषणा RC32434_AF_SPARE_3	(1 << 11)
#घोषणा RC32434_AF_SPARE_2	(1 << 12)

/* PCI messaging unit */
#घोषणा RC32434_PCI_MSU_GPIO	(1 << 13)

/* न_अंकD GPIO संकेतs */
#घोषणा GPIO_RDY		8
#घोषणा GPIO_WPX	9
#घोषणा GPIO_ALE		10
#घोषणा GPIO_CLE		11

/* Compact Flash GPIO pin */
#घोषणा CF_GPIO_NUM		13

/* S1 button GPIO (shared with UART0_SIN) */
#घोषणा GPIO_BTN_S1		1

बाह्य व्योम rb532_gpio_set_ilevel(पूर्णांक bit, अचिन्हित gpio);
बाह्य व्योम rb532_gpio_set_istat(पूर्णांक bit, अचिन्हित gpio);
बाह्य व्योम rb532_gpio_set_func(अचिन्हित gpio);

#पूर्ण_अगर /* _RC32434_GPIO_H_ */
