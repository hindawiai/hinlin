<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2002 Broadcom Corporation
 */
#अगर_अघोषित __ASM_SIBYTE_CARMEL_H
#घोषणा __ASM_SIBYTE_CARMEL_H

#समावेश <यंत्र/sibyte/sb1250.h>
#समावेश <यंत्र/sibyte/sb1250_पूर्णांक.h>

#घोषणा SIBYTE_BOARD_NAME "Carmel"

#घोषणा GPIO_PHY_INTERRUPT	2
#घोषणा GPIO_NONMASKABLE_INT	3
#घोषणा GPIO_CF_INSERTED	6
#घोषणा GPIO_MONTEREY_RESET	7
#घोषणा GPIO_QUADUART_INT	8
#घोषणा GPIO_CF_INT		9
#घोषणा GPIO_FPGA_CCLK		10
#घोषणा GPIO_FPGA_DOUT		11
#घोषणा GPIO_FPGA_DIN		12
#घोषणा GPIO_FPGA_PGM		13
#घोषणा GPIO_FPGA_DONE		14
#घोषणा GPIO_FPGA_INIT		15

#घोषणा LEDS_CS			2
#घोषणा LEDS_PHYS		0x100C0000
#घोषणा MLEDS_CS		3
#घोषणा MLEDS_PHYS		0x100A0000
#घोषणा UART_CS			4
#घोषणा UART_PHYS		0x100D0000
#घोषणा ARAVALI_CS		5
#घोषणा ARAVALI_PHYS		0x11000000
#घोषणा IDE_CS			6
#घोषणा IDE_PHYS		0x100B0000
#घोषणा ARAVALI2_CS		7
#घोषणा ARAVALI2_PHYS		0x100E0000

#अगर defined(CONFIG_SIBYTE_CARMEL)
#घोषणा K_GPIO_GB_IDE	9
#घोषणा K_INT_GB_IDE	(K_INT_GPIO_0 + K_GPIO_GB_IDE)
#पूर्ण_अगर


#पूर्ण_अगर /* __ASM_SIBYTE_CARMEL_H */
