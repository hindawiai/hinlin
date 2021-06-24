<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 STMicroelectronics
 * Author(s): Amelie Delaunay <amelie.delaunay@st.com>.
 */

#अगर_अघोषित MFD_STMFX_H
#घोषणा MFD_STMFX_H

#समावेश <linux/regmap.h>

/* General */
#घोषणा STMFX_REG_CHIP_ID		0x00 /* R */
#घोषणा STMFX_REG_FW_VERSION_MSB	0x01 /* R */
#घोषणा STMFX_REG_FW_VERSION_LSB	0x02 /* R */
#घोषणा STMFX_REG_SYS_CTRL		0x40 /* RW */
/* IRQ output management */
#घोषणा STMFX_REG_IRQ_OUT_PIN		0x41 /* RW */
#घोषणा STMFX_REG_IRQ_SRC_EN		0x42 /* RW */
#घोषणा STMFX_REG_IRQ_PENDING		0x08 /* R */
#घोषणा STMFX_REG_IRQ_ACK		0x44 /* RW */
/* GPIO management */
#घोषणा STMFX_REG_IRQ_GPI_PENDING1	0x0C /* R */
#घोषणा STMFX_REG_IRQ_GPI_PENDING2	0x0D /* R */
#घोषणा STMFX_REG_IRQ_GPI_PENDING3	0x0E /* R */
#घोषणा STMFX_REG_GPIO_STATE1		0x10 /* R */
#घोषणा STMFX_REG_GPIO_STATE2		0x11 /* R */
#घोषणा STMFX_REG_GPIO_STATE3		0x12 /* R */
#घोषणा STMFX_REG_IRQ_GPI_SRC1		0x48 /* RW */
#घोषणा STMFX_REG_IRQ_GPI_SRC2		0x49 /* RW */
#घोषणा STMFX_REG_IRQ_GPI_SRC3		0x4A /* RW */
#घोषणा STMFX_REG_IRQ_GPI_EVT1		0x4C /* RW */
#घोषणा STMFX_REG_IRQ_GPI_EVT2		0x4D /* RW */
#घोषणा STMFX_REG_IRQ_GPI_EVT3		0x4E /* RW */
#घोषणा STMFX_REG_IRQ_GPI_TYPE1		0x50 /* RW */
#घोषणा STMFX_REG_IRQ_GPI_TYPE2		0x51 /* RW */
#घोषणा STMFX_REG_IRQ_GPI_TYPE3		0x52 /* RW */
#घोषणा STMFX_REG_IRQ_GPI_ACK1		0x54 /* RW */
#घोषणा STMFX_REG_IRQ_GPI_ACK2		0x55 /* RW */
#घोषणा STMFX_REG_IRQ_GPI_ACK3		0x56 /* RW */
#घोषणा STMFX_REG_GPIO_सूची1		0x60 /* RW */
#घोषणा STMFX_REG_GPIO_सूची2		0x61 /* RW */
#घोषणा STMFX_REG_GPIO_सूची3		0x62 /* RW */
#घोषणा STMFX_REG_GPIO_TYPE1		0x64 /* RW */
#घोषणा STMFX_REG_GPIO_TYPE2		0x65 /* RW */
#घोषणा STMFX_REG_GPIO_TYPE3		0x66 /* RW */
#घोषणा STMFX_REG_GPIO_PUPD1		0x68 /* RW */
#घोषणा STMFX_REG_GPIO_PUPD2		0x69 /* RW */
#घोषणा STMFX_REG_GPIO_PUPD3		0x6A /* RW */
#घोषणा STMFX_REG_GPO_SET1		0x6C /* RW */
#घोषणा STMFX_REG_GPO_SET2		0x6D /* RW */
#घोषणा STMFX_REG_GPO_SET3		0x6E /* RW */
#घोषणा STMFX_REG_GPO_CLR1		0x70 /* RW */
#घोषणा STMFX_REG_GPO_CLR2		0x71 /* RW */
#घोषणा STMFX_REG_GPO_CLR3		0x72 /* RW */

#घोषणा STMFX_REG_MAX			0xB0

/* MFX boot समय is around 10ms, so after reset, we have to रुको this delay */
#घोषणा STMFX_BOOT_TIME_MS 10

/* STMFX_REG_CHIP_ID bitfields */
#घोषणा STMFX_REG_CHIP_ID_MASK		GENMASK(7, 0)

/* STMFX_REG_SYS_CTRL bitfields */
#घोषणा STMFX_REG_SYS_CTRL_GPIO_EN	BIT(0)
#घोषणा STMFX_REG_SYS_CTRL_TS_EN	BIT(1)
#घोषणा STMFX_REG_SYS_CTRL_IDD_EN	BIT(2)
#घोषणा STMFX_REG_SYS_CTRL_ALTGPIO_EN	BIT(3)
#घोषणा STMFX_REG_SYS_CTRL_SWRST	BIT(7)

/* STMFX_REG_IRQ_OUT_PIN bitfields */
#घोषणा STMFX_REG_IRQ_OUT_PIN_TYPE	BIT(0) /* 0-OD 1-PP */
#घोषणा STMFX_REG_IRQ_OUT_PIN_POL	BIT(1) /* 0-active LOW 1-active HIGH */

/* STMFX_REG_IRQ_(SRC_EN/PENDING/ACK) bit shअगरt */
क्रमागत sपंचांगfx_irqs अणु
	STMFX_REG_IRQ_SRC_EN_GPIO = 0,
	STMFX_REG_IRQ_SRC_EN_IDD,
	STMFX_REG_IRQ_SRC_EN_ERROR,
	STMFX_REG_IRQ_SRC_EN_TS_DET,
	STMFX_REG_IRQ_SRC_EN_TS_NE,
	STMFX_REG_IRQ_SRC_EN_TS_TH,
	STMFX_REG_IRQ_SRC_EN_TS_FULL,
	STMFX_REG_IRQ_SRC_EN_TS_OVF,
	STMFX_REG_IRQ_SRC_MAX,
पूर्ण;

क्रमागत sपंचांगfx_functions अणु
	STMFX_FUNC_GPIO		= BIT(0), /* GPIO[15:0] */
	STMFX_FUNC_ALTGPIO_LOW	= BIT(1), /* aGPIO[3:0] */
	STMFX_FUNC_ALTGPIO_HIGH = BIT(2), /* aGPIO[7:4] */
	STMFX_FUNC_TS		= BIT(3),
	STMFX_FUNC_IDD		= BIT(4),
पूर्ण;

/**
 * काष्ठा sपंचांगfx_ddata - STMFX MFD काष्ठाure
 * @device:		device reference used क्रम logs
 * @map:		रेजिस्टर map
 * @vdd:		STMFX घातer supply
 * @irq_करोमुख्य:		IRQ करोमुख्य
 * @lock:		IRQ bus lock
 * @irq_src:		cache of IRQ_SRC_EN रेजिस्टर क्रम bus_lock
 * @bkp_sysctrl:	backup of SYS_CTRL रेजिस्टर क्रम suspend/resume
 * @bkp_irqoutpin:	backup of IRQ_OUT_PIN रेजिस्टर क्रम suspend/resume
 */
काष्ठा sपंचांगfx अणु
	काष्ठा device *dev;
	काष्ठा regmap *map;
	काष्ठा regulator *vdd;
	पूर्णांक irq;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा mutex lock; /* IRQ bus lock */
	u8 irq_src;
#अगर_घोषित CONFIG_PM
	u8 bkp_sysctrl;
	u8 bkp_irqoutpin;
#पूर्ण_अगर
पूर्ण;

पूर्णांक sपंचांगfx_function_enable(काष्ठा sपंचांगfx *sपंचांगfx, u32 func);
पूर्णांक sपंचांगfx_function_disable(काष्ठा sपंचांगfx *sपंचांगfx, u32 func);
#पूर्ण_अगर
