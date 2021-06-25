<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * DA9150 MFD Driver - Core Data
 *
 * Copyright (c) 2014 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#अगर_अघोषित __DA9150_CORE_H
#घोषणा __DA9150_CORE_H

#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>

/* I2C address paging */
#घोषणा DA9150_REG_PAGE_SHIFT	8
#घोषणा DA9150_REG_PAGE_MASK	0xFF

/* IRQs */
#घोषणा DA9150_NUM_IRQ_REGS	4
#घोषणा DA9150_IRQ_VBUS		0
#घोषणा DA9150_IRQ_CHG		1
#घोषणा DA9150_IRQ_TCLASS	2
#घोषणा DA9150_IRQ_TJUNC	3
#घोषणा DA9150_IRQ_VFAULT	4
#घोषणा DA9150_IRQ_CONF		5
#घोषणा DA9150_IRQ_DAT		6
#घोषणा DA9150_IRQ_DTYPE	7
#घोषणा DA9150_IRQ_ID		8
#घोषणा DA9150_IRQ_ADP		9
#घोषणा DA9150_IRQ_SESS_END	10
#घोषणा DA9150_IRQ_SESS_VLD	11
#घोषणा DA9150_IRQ_FG		12
#घोषणा DA9150_IRQ_GP		13
#घोषणा DA9150_IRQ_TBAT		14
#घोषणा DA9150_IRQ_GPIOA	15
#घोषणा DA9150_IRQ_GPIOB	16
#घोषणा DA9150_IRQ_GPIOC	17
#घोषणा DA9150_IRQ_GPIOD	18
#घोषणा DA9150_IRQ_GPADC	19
#घोषणा DA9150_IRQ_WKUP		20

/* I2C sub-device address */
#घोषणा DA9150_QIF_I2C_ADDR_LSB		0x5

काष्ठा da9150_fg_pdata अणु
	u32 update_पूर्णांकerval;	/* msecs */
	u8 warn_soc_lvl;	/* % value */
	u8 crit_soc_lvl;	/* % value */
पूर्ण;

काष्ठा da9150_pdata अणु
	पूर्णांक irq_base;
	काष्ठा da9150_fg_pdata *fg_pdata;
पूर्ण;

काष्ठा da9150 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा i2c_client *core_qअगर;

	काष्ठा regmap_irq_chip_data *regmap_irq_data;
	पूर्णांक irq;
	पूर्णांक irq_base;
पूर्ण;

/* Device I/O - Query Interface क्रम FG and standard रेजिस्टर access */
व्योम da9150_पढ़ो_qअगर(काष्ठा da9150 *da9150, u8 addr, पूर्णांक count, u8 *buf);
व्योम da9150_ग_लिखो_qअगर(काष्ठा da9150 *da9150, u8 addr, पूर्णांक count, स्थिर u8 *buf);

u8 da9150_reg_पढ़ो(काष्ठा da9150 *da9150, u16 reg);
व्योम da9150_reg_ग_लिखो(काष्ठा da9150 *da9150, u16 reg, u8 val);
व्योम da9150_set_bits(काष्ठा da9150 *da9150, u16 reg, u8 mask, u8 val);

व्योम da9150_bulk_पढ़ो(काष्ठा da9150 *da9150, u16 reg, पूर्णांक count, u8 *buf);
व्योम da9150_bulk_ग_लिखो(काष्ठा da9150 *da9150, u16 reg, पूर्णांक count, स्थिर u8 *buf);

#पूर्ण_अगर /* __DA9150_CORE_H */
