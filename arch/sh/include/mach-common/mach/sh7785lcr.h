<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_RENESAS_SH7785LCR_H
#घोषणा __ASM_SH_RENESAS_SH7785LCR_H

/*
 * This board has 2 physical memory maps.
 * It can be changed with DIP चयन(S2-5).
 *
 * phys address			| S2-5 = OFF	| S2-5 = ON
 * -----------------------------+---------------+---------------
 * 0x00000000 - 0x03ffffff(CS0)	| NOR Flash	| NOR Flash
 * 0x04000000 - 0x05ffffff(CS1)	| PLD		| PLD
 * 0x06000000 - 0x07ffffff(CS1)	| I2C		| I2C
 * 0x08000000 - 0x0bffffff(CS2)	| USB		| DDR SDRAM
 * 0x0c000000 - 0x0fffffff(CS3)	| SD		| DDR SDRAM
 * 0x10000000 - 0x13ffffff(CS4)	| SM107		| SM107
 * 0x14000000 - 0x17ffffff(CS5)	| reserved	| USB
 * 0x18000000 - 0x1bffffff(CS6)	| reserved	| SD
 * 0x40000000 - 0x5fffffff	| DDR SDRAM	| (cannot use)
 *
 */

#घोषणा NOR_FLASH_ADDR		0x00000000
#घोषणा NOR_FLASH_SIZE		0x04000000

#घोषणा PLD_BASE_ADDR		0x04000000
#घोषणा PLD_PCICR		(PLD_BASE_ADDR + 0x00)
#घोषणा PLD_LCD_BK_CONTR	(PLD_BASE_ADDR + 0x02)
#घोषणा PLD_LOCALCR		(PLD_BASE_ADDR + 0x04)
#घोषणा PLD_POFCR		(PLD_BASE_ADDR + 0x06)
#घोषणा PLD_LEDCR		(PLD_BASE_ADDR + 0x08)
#घोषणा PLD_SWSR		(PLD_BASE_ADDR + 0x0a)
#घोषणा PLD_VERSR		(PLD_BASE_ADDR + 0x0c)
#घोषणा PLD_MMSR		(PLD_BASE_ADDR + 0x0e)

#घोषणा PCA9564_ADDR		0x06000000	/* I2C */
#घोषणा PCA9564_SIZE		0x00000100

#घोषणा PCA9564_PROTO_32BIT_ADDR	0x14000000

#घोषणा SM107_MEM_ADDR		0x10000000
#घोषणा SM107_MEM_SIZE		0x00e00000
#घोषणा SM107_REG_ADDR		0x13e00000
#घोषणा SM107_REG_SIZE		0x00200000

#अगर defined(CONFIG_SH_SH7785LCR_29BIT_PHYSMAPS)
#घोषणा R8A66597_ADDR		0x14000000	/* USB */
#घोषणा CG200_ADDR		0x18000000	/* SD */
#अन्यथा
#घोषणा R8A66597_ADDR		0x08000000
#घोषणा CG200_ADDR		0x0c000000
#पूर्ण_अगर

#घोषणा R8A66597_SIZE		0x00000100
#घोषणा CG200_SIZE		0x00010000

#पूर्ण_अगर  /* __ASM_SH_RENESAS_SH7785LCR_H */

