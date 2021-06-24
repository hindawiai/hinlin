<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _INCLUDE_SHANNON_H
#घोषणा _INCLUDE_SHANNON_H

/* taken from comp.os.inferno Tue, 12 Sep 2000 09:21:50 GMT,
 * written by <क्रमsyth@vitanuova.com> */

#घोषणा SHANNON_GPIO_SPI_FLASH		GPIO_GPIO (0)	/* Output - Driven low, enables SPI to flash */
#घोषणा SHANNON_GPIO_SPI_DSP		GPIO_GPIO (1)	/* Output - Driven low, enables SPI to DSP */
/* lcd lower = GPIO 2-9 */
#घोषणा SHANNON_GPIO_SPI_OUTPUT		GPIO_GPIO (10)	/* Output - SPI output to DSP */
#घोषणा SHANNON_GPIO_SPI_INPUT		GPIO_GPIO (11)	/* Input  - SPI input from DSP */
#घोषणा SHANNON_GPIO_SPI_CLOCK		GPIO_GPIO (12)	/* Output - Clock क्रम SPI */
#घोषणा SHANNON_GPIO_SPI_FRAME		GPIO_GPIO (13)	/* Output - Frame marker - not used */
#घोषणा SHANNON_GPIO_SPI_RTS		GPIO_GPIO (14)	/* Input  - SPI Ready to Send */
#घोषणा SHANNON_IRQ_GPIO_SPI_RTS	IRQ_GPIO14
#घोषणा SHANNON_GPIO_SPI_CTS		GPIO_GPIO (15)	/* Output - SPI Clear to Send */
#घोषणा SHANNON_GPIO_IRQ_CODEC		GPIO_GPIO (16)	/* in, irq from ucb1200 */
#घोषणा SHANNON_IRQ_GPIO_IRQ_CODEC	IRQ_GPIO16
#घोषणा SHANNON_GPIO_DSP_RESET		GPIO_GPIO (17)	/* Output - Drive low to reset the DSP */
#घोषणा SHANNON_GPIO_CODEC_RESET	GPIO_GPIO (18)	/* Output - Drive low to reset the UCB1x00 */
#घोषणा SHANNON_GPIO_U3_RTS		GPIO_GPIO (19)	/* ?? */
#घोषणा SHANNON_GPIO_U3_CTS		GPIO_GPIO (20)	/* ?? */
#घोषणा SHANNON_GPIO_SENSE_12V		GPIO_GPIO (21)	/* Input, 12v flash unprotect detected */
#घोषणा SHANNON_GPIO_DISP_EN		22		/* out */
/* XXX GPIO 23 unaccounted क्रम */
#घोषणा SHANNON_GPIO_EJECT_0		24		/* in */
#घोषणा SHANNON_GPIO_EJECT_1		25		/* in */
#घोषणा SHANNON_GPIO_RDY_0		26		/* in */
#घोषणा SHANNON_GPIO_RDY_1		27		/* in */

/* MCP UCB codec GPIO pins... */

#घोषणा SHANNON_UCB_GPIO_BACKLIGHT	9
#घोषणा SHANNON_UCB_GPIO_BRIGHT_MASK  	7
#घोषणा SHANNON_UCB_GPIO_BRIGHT		6
#घोषणा SHANNON_UCB_GPIO_CONTRAST_MASK	0x3f
#घोषणा SHANNON_UCB_GPIO_CONTRAST	0

#पूर्ण_अगर
