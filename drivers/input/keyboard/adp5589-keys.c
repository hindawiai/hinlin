<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Description:  keypad driver क्रम ADP5589, ADP5585
 *		 I2C QWERTY Keypad and IO Expander
 * Bugs: Enter bugs at http://blackfin.uclinux.org/
 *
 * Copyright (C) 2010-2011 Analog Devices Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pm.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/slab.h>

#समावेश <linux/input/adp5589.h>

/* ADP5589/ADP5585 Common Registers */
#घोषणा ADP5589_5_ID			0x00
#घोषणा ADP5589_5_INT_STATUS		0x01
#घोषणा ADP5589_5_STATUS		0x02
#घोषणा ADP5589_5_FIFO_1		0x03
#घोषणा ADP5589_5_FIFO_2		0x04
#घोषणा ADP5589_5_FIFO_3		0x05
#घोषणा ADP5589_5_FIFO_4		0x06
#घोषणा ADP5589_5_FIFO_5		0x07
#घोषणा ADP5589_5_FIFO_6		0x08
#घोषणा ADP5589_5_FIFO_7		0x09
#घोषणा ADP5589_5_FIFO_8		0x0A
#घोषणा ADP5589_5_FIFO_9		0x0B
#घोषणा ADP5589_5_FIFO_10		0x0C
#घोषणा ADP5589_5_FIFO_11		0x0D
#घोषणा ADP5589_5_FIFO_12		0x0E
#घोषणा ADP5589_5_FIFO_13		0x0F
#घोषणा ADP5589_5_FIFO_14		0x10
#घोषणा ADP5589_5_FIFO_15		0x11
#घोषणा ADP5589_5_FIFO_16		0x12
#घोषणा ADP5589_5_GPI_INT_STAT_A	0x13
#घोषणा ADP5589_5_GPI_INT_STAT_B	0x14

/* ADP5589 Registers */
#घोषणा ADP5589_GPI_INT_STAT_C		0x15
#घोषणा ADP5589_GPI_STATUS_A		0x16
#घोषणा ADP5589_GPI_STATUS_B		0x17
#घोषणा ADP5589_GPI_STATUS_C		0x18
#घोषणा ADP5589_RPULL_CONFIG_A		0x19
#घोषणा ADP5589_RPULL_CONFIG_B		0x1A
#घोषणा ADP5589_RPULL_CONFIG_C		0x1B
#घोषणा ADP5589_RPULL_CONFIG_D		0x1C
#घोषणा ADP5589_RPULL_CONFIG_E		0x1D
#घोषणा ADP5589_GPI_INT_LEVEL_A		0x1E
#घोषणा ADP5589_GPI_INT_LEVEL_B		0x1F
#घोषणा ADP5589_GPI_INT_LEVEL_C		0x20
#घोषणा ADP5589_GPI_EVENT_EN_A		0x21
#घोषणा ADP5589_GPI_EVENT_EN_B		0x22
#घोषणा ADP5589_GPI_EVENT_EN_C		0x23
#घोषणा ADP5589_GPI_INTERRUPT_EN_A	0x24
#घोषणा ADP5589_GPI_INTERRUPT_EN_B	0x25
#घोषणा ADP5589_GPI_INTERRUPT_EN_C	0x26
#घोषणा ADP5589_DEBOUNCE_DIS_A		0x27
#घोषणा ADP5589_DEBOUNCE_DIS_B		0x28
#घोषणा ADP5589_DEBOUNCE_DIS_C		0x29
#घोषणा ADP5589_GPO_DATA_OUT_A		0x2A
#घोषणा ADP5589_GPO_DATA_OUT_B		0x2B
#घोषणा ADP5589_GPO_DATA_OUT_C		0x2C
#घोषणा ADP5589_GPO_OUT_MODE_A		0x2D
#घोषणा ADP5589_GPO_OUT_MODE_B		0x2E
#घोषणा ADP5589_GPO_OUT_MODE_C		0x2F
#घोषणा ADP5589_GPIO_सूचीECTION_A	0x30
#घोषणा ADP5589_GPIO_सूचीECTION_B	0x31
#घोषणा ADP5589_GPIO_सूचीECTION_C	0x32
#घोषणा ADP5589_UNLOCK1			0x33
#घोषणा ADP5589_UNLOCK2			0x34
#घोषणा ADP5589_EXT_LOCK_EVENT		0x35
#घोषणा ADP5589_UNLOCK_TIMERS		0x36
#घोषणा ADP5589_LOCK_CFG		0x37
#घोषणा ADP5589_RESET1_EVENT_A		0x38
#घोषणा ADP5589_RESET1_EVENT_B		0x39
#घोषणा ADP5589_RESET1_EVENT_C		0x3A
#घोषणा ADP5589_RESET2_EVENT_A		0x3B
#घोषणा ADP5589_RESET2_EVENT_B		0x3C
#घोषणा ADP5589_RESET_CFG		0x3D
#घोषणा ADP5589_PWM_OFFT_LOW		0x3E
#घोषणा ADP5589_PWM_OFFT_HIGH		0x3F
#घोषणा ADP5589_PWM_ONT_LOW		0x40
#घोषणा ADP5589_PWM_ONT_HIGH		0x41
#घोषणा ADP5589_PWM_CFG			0x42
#घोषणा ADP5589_CLOCK_DIV_CFG		0x43
#घोषणा ADP5589_LOGIC_1_CFG		0x44
#घोषणा ADP5589_LOGIC_2_CFG		0x45
#घोषणा ADP5589_LOGIC_FF_CFG		0x46
#घोषणा ADP5589_LOGIC_INT_EVENT_EN	0x47
#घोषणा ADP5589_POLL_PTIME_CFG		0x48
#घोषणा ADP5589_PIN_CONFIG_A		0x49
#घोषणा ADP5589_PIN_CONFIG_B		0x4A
#घोषणा ADP5589_PIN_CONFIG_C		0x4B
#घोषणा ADP5589_PIN_CONFIG_D		0x4C
#घोषणा ADP5589_GENERAL_CFG		0x4D
#घोषणा ADP5589_INT_EN			0x4E

/* ADP5585 Registers */
#घोषणा ADP5585_GPI_STATUS_A		0x15
#घोषणा ADP5585_GPI_STATUS_B		0x16
#घोषणा ADP5585_RPULL_CONFIG_A		0x17
#घोषणा ADP5585_RPULL_CONFIG_B		0x18
#घोषणा ADP5585_RPULL_CONFIG_C		0x19
#घोषणा ADP5585_RPULL_CONFIG_D		0x1A
#घोषणा ADP5585_GPI_INT_LEVEL_A		0x1B
#घोषणा ADP5585_GPI_INT_LEVEL_B		0x1C
#घोषणा ADP5585_GPI_EVENT_EN_A		0x1D
#घोषणा ADP5585_GPI_EVENT_EN_B		0x1E
#घोषणा ADP5585_GPI_INTERRUPT_EN_A	0x1F
#घोषणा ADP5585_GPI_INTERRUPT_EN_B	0x20
#घोषणा ADP5585_DEBOUNCE_DIS_A		0x21
#घोषणा ADP5585_DEBOUNCE_DIS_B		0x22
#घोषणा ADP5585_GPO_DATA_OUT_A		0x23
#घोषणा ADP5585_GPO_DATA_OUT_B		0x24
#घोषणा ADP5585_GPO_OUT_MODE_A		0x25
#घोषणा ADP5585_GPO_OUT_MODE_B		0x26
#घोषणा ADP5585_GPIO_सूचीECTION_A	0x27
#घोषणा ADP5585_GPIO_सूचीECTION_B	0x28
#घोषणा ADP5585_RESET1_EVENT_A		0x29
#घोषणा ADP5585_RESET1_EVENT_B		0x2A
#घोषणा ADP5585_RESET1_EVENT_C		0x2B
#घोषणा ADP5585_RESET2_EVENT_A		0x2C
#घोषणा ADP5585_RESET2_EVENT_B		0x2D
#घोषणा ADP5585_RESET_CFG		0x2E
#घोषणा ADP5585_PWM_OFFT_LOW		0x2F
#घोषणा ADP5585_PWM_OFFT_HIGH		0x30
#घोषणा ADP5585_PWM_ONT_LOW		0x31
#घोषणा ADP5585_PWM_ONT_HIGH		0x32
#घोषणा ADP5585_PWM_CFG			0x33
#घोषणा ADP5585_LOGIC_CFG		0x34
#घोषणा ADP5585_LOGIC_FF_CFG		0x35
#घोषणा ADP5585_LOGIC_INT_EVENT_EN	0x36
#घोषणा ADP5585_POLL_PTIME_CFG		0x37
#घोषणा ADP5585_PIN_CONFIG_A		0x38
#घोषणा ADP5585_PIN_CONFIG_B		0x39
#घोषणा ADP5585_PIN_CONFIG_D		0x3A
#घोषणा ADP5585_GENERAL_CFG		0x3B
#घोषणा ADP5585_INT_EN			0x3C

/* ID Register */
#घोषणा ADP5589_5_DEVICE_ID_MASK	0xF
#घोषणा ADP5589_5_MAN_ID_MASK		0xF
#घोषणा ADP5589_5_MAN_ID_SHIFT		4
#घोषणा ADP5589_5_MAN_ID		0x02

/* GENERAL_CFG Register */
#घोषणा OSC_EN		BIT(7)
#घोषणा CORE_CLK(x)	(((x) & 0x3) << 5)
#घोषणा LCK_TRK_LOGIC	BIT(4)		/* ADP5589 only */
#घोषणा LCK_TRK_GPI	BIT(3)		/* ADP5589 only */
#घोषणा INT_CFG		BIT(1)
#घोषणा RST_CFG		BIT(0)

/* INT_EN Register */
#घोषणा LOGIC2_IEN	BIT(5)		/* ADP5589 only */
#घोषणा LOGIC1_IEN	BIT(4)
#घोषणा LOCK_IEN	BIT(3)		/* ADP5589 only */
#घोषणा OVRFLOW_IEN	BIT(2)
#घोषणा GPI_IEN		BIT(1)
#घोषणा EVENT_IEN	BIT(0)

/* Interrupt Status Register */
#घोषणा LOGIC2_INT	BIT(5)		/* ADP5589 only */
#घोषणा LOGIC1_INT	BIT(4)
#घोषणा LOCK_INT	BIT(3)		/* ADP5589 only */
#घोषणा OVRFLOW_INT	BIT(2)
#घोषणा GPI_INT		BIT(1)
#घोषणा EVENT_INT	BIT(0)

/* STATUS Register */
#घोषणा LOGIC2_STAT	BIT(7)		/* ADP5589 only */
#घोषणा LOGIC1_STAT	BIT(6)
#घोषणा LOCK_STAT	BIT(5)		/* ADP5589 only */
#घोषणा KEC		0x1F

/* PIN_CONFIG_D Register */
#घोषणा C4_EXTEND_CFG	BIT(6)		/* RESET2 */
#घोषणा R4_EXTEND_CFG	BIT(5)		/* RESET1 */

/* LOCK_CFG */
#घोषणा LOCK_EN		BIT(0)

#घोषणा PTIME_MASK	0x3
#घोषणा LTIME_MASK	0x3		/* ADP5589 only */

/* Key Event Register xy */
#घोषणा KEY_EV_PRESSED	BIT(7)
#घोषणा KEY_EV_MASK	0x7F

#घोषणा KEYP_MAX_EVENT		16
#घोषणा ADP5589_MAXGPIO		19
#घोषणा ADP5585_MAXGPIO		11 /* 10 on the ADP5585-01, 11 on ADP5585-02 */

क्रमागत अणु
	ADP5589,
	ADP5585_01,
	ADP5585_02
पूर्ण;

काष्ठा adp_स्थिरants अणु
	u8 maxgpio;
	u8 keymapsize;
	u8 gpi_pin_row_base;
	u8 gpi_pin_row_end;
	u8 gpi_pin_col_base;
	u8 gpi_pin_base;
	u8 gpi_pin_end;
	u8 gpimapsize_max;
	u8 max_row_num;
	u8 max_col_num;
	u8 row_mask;
	u8 col_mask;
	u8 col_shअगरt;
	u8 c4_extend_cfg;
	u8 (*bank) (u8 offset);
	u8 (*bit) (u8 offset);
	u8 (*reg) (u8 reg);
पूर्ण;

काष्ठा adp5589_kpad अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	स्थिर काष्ठा adp_स्थिरants *var;
	अचिन्हित लघु keycode[ADP5589_KEYMAPSIZE];
	स्थिर काष्ठा adp5589_gpi_map *gpimap;
	अचिन्हित लघु gpimapsize;
	अचिन्हित extend_cfg;
	bool is_adp5585;
	bool support_row5;
#अगर_घोषित CONFIG_GPIOLIB
	अचिन्हित अक्षर gpiomap[ADP5589_MAXGPIO];
	काष्ठा gpio_chip gc;
	काष्ठा mutex gpio_lock;	/* Protect cached dir, dat_out */
	u8 dat_out[3];
	u8 dir[3];
#पूर्ण_अगर
पूर्ण;

/*
 *  ADP5589 / ADP5585 derivative / variant handling
 */


/* ADP5589 */

अटल अचिन्हित अक्षर adp5589_bank(अचिन्हित अक्षर offset)
अणु
	वापस offset >> 3;
पूर्ण

अटल अचिन्हित अक्षर adp5589_bit(अचिन्हित अक्षर offset)
अणु
	वापस 1u << (offset & 0x7);
पूर्ण

अटल अचिन्हित अक्षर adp5589_reg(अचिन्हित अक्षर reg)
अणु
	वापस reg;
पूर्ण

अटल स्थिर काष्ठा adp_स्थिरants स्थिर_adp5589 = अणु
	.maxgpio		= ADP5589_MAXGPIO,
	.keymapsize		= ADP5589_KEYMAPSIZE,
	.gpi_pin_row_base	= ADP5589_GPI_PIN_ROW_BASE,
	.gpi_pin_row_end	= ADP5589_GPI_PIN_ROW_END,
	.gpi_pin_col_base	= ADP5589_GPI_PIN_COL_BASE,
	.gpi_pin_base		= ADP5589_GPI_PIN_BASE,
	.gpi_pin_end		= ADP5589_GPI_PIN_END,
	.gpimapsize_max		= ADP5589_GPIMAPSIZE_MAX,
	.c4_extend_cfg		= 12,
	.max_row_num		= ADP5589_MAX_ROW_NUM,
	.max_col_num		= ADP5589_MAX_COL_NUM,
	.row_mask		= ADP5589_ROW_MASK,
	.col_mask		= ADP5589_COL_MASK,
	.col_shअगरt		= ADP5589_COL_SHIFT,
	.bank			= adp5589_bank,
	.bit			= adp5589_bit,
	.reg			= adp5589_reg,
पूर्ण;

/* ADP5585 */

अटल अचिन्हित अक्षर adp5585_bank(अचिन्हित अक्षर offset)
अणु
	वापस offset > ADP5585_MAX_ROW_NUM;
पूर्ण

अटल अचिन्हित अक्षर adp5585_bit(अचिन्हित अक्षर offset)
अणु
	वापस (offset > ADP5585_MAX_ROW_NUM) ?
		1u << (offset - ADP5585_COL_SHIFT) : 1u << offset;
पूर्ण

अटल स्थिर अचिन्हित अक्षर adp5585_reg_lut[] = अणु
	[ADP5589_GPI_STATUS_A]		= ADP5585_GPI_STATUS_A,
	[ADP5589_GPI_STATUS_B]		= ADP5585_GPI_STATUS_B,
	[ADP5589_RPULL_CONFIG_A]	= ADP5585_RPULL_CONFIG_A,
	[ADP5589_RPULL_CONFIG_B]	= ADP5585_RPULL_CONFIG_B,
	[ADP5589_RPULL_CONFIG_C]	= ADP5585_RPULL_CONFIG_C,
	[ADP5589_RPULL_CONFIG_D]	= ADP5585_RPULL_CONFIG_D,
	[ADP5589_GPI_INT_LEVEL_A]	= ADP5585_GPI_INT_LEVEL_A,
	[ADP5589_GPI_INT_LEVEL_B]	= ADP5585_GPI_INT_LEVEL_B,
	[ADP5589_GPI_EVENT_EN_A]	= ADP5585_GPI_EVENT_EN_A,
	[ADP5589_GPI_EVENT_EN_B]	= ADP5585_GPI_EVENT_EN_B,
	[ADP5589_GPI_INTERRUPT_EN_A]	= ADP5585_GPI_INTERRUPT_EN_A,
	[ADP5589_GPI_INTERRUPT_EN_B]	= ADP5585_GPI_INTERRUPT_EN_B,
	[ADP5589_DEBOUNCE_DIS_A]	= ADP5585_DEBOUNCE_DIS_A,
	[ADP5589_DEBOUNCE_DIS_B]	= ADP5585_DEBOUNCE_DIS_B,
	[ADP5589_GPO_DATA_OUT_A]	= ADP5585_GPO_DATA_OUT_A,
	[ADP5589_GPO_DATA_OUT_B]	= ADP5585_GPO_DATA_OUT_B,
	[ADP5589_GPO_OUT_MODE_A]	= ADP5585_GPO_OUT_MODE_A,
	[ADP5589_GPO_OUT_MODE_B]	= ADP5585_GPO_OUT_MODE_B,
	[ADP5589_GPIO_सूचीECTION_A]	= ADP5585_GPIO_सूचीECTION_A,
	[ADP5589_GPIO_सूचीECTION_B]	= ADP5585_GPIO_सूचीECTION_B,
	[ADP5589_RESET1_EVENT_A]	= ADP5585_RESET1_EVENT_A,
	[ADP5589_RESET1_EVENT_B]	= ADP5585_RESET1_EVENT_B,
	[ADP5589_RESET1_EVENT_C]	= ADP5585_RESET1_EVENT_C,
	[ADP5589_RESET2_EVENT_A]	= ADP5585_RESET2_EVENT_A,
	[ADP5589_RESET2_EVENT_B]	= ADP5585_RESET2_EVENT_B,
	[ADP5589_RESET_CFG]		= ADP5585_RESET_CFG,
	[ADP5589_PWM_OFFT_LOW]		= ADP5585_PWM_OFFT_LOW,
	[ADP5589_PWM_OFFT_HIGH]		= ADP5585_PWM_OFFT_HIGH,
	[ADP5589_PWM_ONT_LOW]		= ADP5585_PWM_ONT_LOW,
	[ADP5589_PWM_ONT_HIGH]		= ADP5585_PWM_ONT_HIGH,
	[ADP5589_PWM_CFG]		= ADP5585_PWM_CFG,
	[ADP5589_LOGIC_1_CFG]		= ADP5585_LOGIC_CFG,
	[ADP5589_LOGIC_FF_CFG]		= ADP5585_LOGIC_FF_CFG,
	[ADP5589_LOGIC_INT_EVENT_EN]	= ADP5585_LOGIC_INT_EVENT_EN,
	[ADP5589_POLL_PTIME_CFG]	= ADP5585_POLL_PTIME_CFG,
	[ADP5589_PIN_CONFIG_A]		= ADP5585_PIN_CONFIG_A,
	[ADP5589_PIN_CONFIG_B]		= ADP5585_PIN_CONFIG_B,
	[ADP5589_PIN_CONFIG_D]		= ADP5585_PIN_CONFIG_D,
	[ADP5589_GENERAL_CFG]		= ADP5585_GENERAL_CFG,
	[ADP5589_INT_EN]		= ADP5585_INT_EN,
पूर्ण;

अटल अचिन्हित अक्षर adp5585_reg(अचिन्हित अक्षर reg)
अणु
	वापस adp5585_reg_lut[reg];
पूर्ण

अटल स्थिर काष्ठा adp_स्थिरants स्थिर_adp5585 = अणु
	.maxgpio		= ADP5585_MAXGPIO,
	.keymapsize		= ADP5585_KEYMAPSIZE,
	.gpi_pin_row_base	= ADP5585_GPI_PIN_ROW_BASE,
	.gpi_pin_row_end	= ADP5585_GPI_PIN_ROW_END,
	.gpi_pin_col_base	= ADP5585_GPI_PIN_COL_BASE,
	.gpi_pin_base		= ADP5585_GPI_PIN_BASE,
	.gpi_pin_end		= ADP5585_GPI_PIN_END,
	.gpimapsize_max		= ADP5585_GPIMAPSIZE_MAX,
	.c4_extend_cfg		= 10,
	.max_row_num		= ADP5585_MAX_ROW_NUM,
	.max_col_num		= ADP5585_MAX_COL_NUM,
	.row_mask		= ADP5585_ROW_MASK,
	.col_mask		= ADP5585_COL_MASK,
	.col_shअगरt		= ADP5585_COL_SHIFT,
	.bank			= adp5585_bank,
	.bit			= adp5585_bit,
	.reg			= adp5585_reg,
पूर्ण;

अटल पूर्णांक adp5589_पढ़ो(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, reg);

	अगर (ret < 0)
		dev_err(&client->dev, "Read Error\n");

	वापस ret;
पूर्ण

अटल पूर्णांक adp5589_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, val);
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
अटल पूर्णांक adp5589_gpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित off)
अणु
	काष्ठा adp5589_kpad *kpad = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक bank = kpad->var->bank(kpad->gpiomap[off]);
	अचिन्हित पूर्णांक bit = kpad->var->bit(kpad->gpiomap[off]);

	वापस !!(adp5589_पढ़ो(kpad->client,
			       kpad->var->reg(ADP5589_GPI_STATUS_A) + bank) &
			       bit);
पूर्ण

अटल व्योम adp5589_gpio_set_value(काष्ठा gpio_chip *chip,
				   अचिन्हित off, पूर्णांक val)
अणु
	काष्ठा adp5589_kpad *kpad = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक bank = kpad->var->bank(kpad->gpiomap[off]);
	अचिन्हित पूर्णांक bit = kpad->var->bit(kpad->gpiomap[off]);

	mutex_lock(&kpad->gpio_lock);

	अगर (val)
		kpad->dat_out[bank] |= bit;
	अन्यथा
		kpad->dat_out[bank] &= ~bit;

	adp5589_ग_लिखो(kpad->client, kpad->var->reg(ADP5589_GPO_DATA_OUT_A) +
		      bank, kpad->dat_out[bank]);

	mutex_unlock(&kpad->gpio_lock);
पूर्ण

अटल पूर्णांक adp5589_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित off)
अणु
	काष्ठा adp5589_kpad *kpad = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक bank = kpad->var->bank(kpad->gpiomap[off]);
	अचिन्हित पूर्णांक bit = kpad->var->bit(kpad->gpiomap[off]);
	पूर्णांक ret;

	mutex_lock(&kpad->gpio_lock);

	kpad->dir[bank] &= ~bit;
	ret = adp5589_ग_लिखो(kpad->client,
			    kpad->var->reg(ADP5589_GPIO_सूचीECTION_A) + bank,
			    kpad->dir[bank]);

	mutex_unlock(&kpad->gpio_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक adp5589_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित off, पूर्णांक val)
अणु
	काष्ठा adp5589_kpad *kpad = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक bank = kpad->var->bank(kpad->gpiomap[off]);
	अचिन्हित पूर्णांक bit = kpad->var->bit(kpad->gpiomap[off]);
	पूर्णांक ret;

	mutex_lock(&kpad->gpio_lock);

	kpad->dir[bank] |= bit;

	अगर (val)
		kpad->dat_out[bank] |= bit;
	अन्यथा
		kpad->dat_out[bank] &= ~bit;

	ret = adp5589_ग_लिखो(kpad->client, kpad->var->reg(ADP5589_GPO_DATA_OUT_A)
			    + bank, kpad->dat_out[bank]);
	ret |= adp5589_ग_लिखो(kpad->client,
			     kpad->var->reg(ADP5589_GPIO_सूचीECTION_A) + bank,
			     kpad->dir[bank]);

	mutex_unlock(&kpad->gpio_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक adp5589_build_gpiomap(काष्ठा adp5589_kpad *kpad,
				स्थिर काष्ठा adp5589_kpad_platक्रमm_data *pdata)
अणु
	bool pin_used[ADP5589_MAXGPIO];
	पूर्णांक n_unused = 0;
	पूर्णांक i;

	स_रखो(pin_used, false, माप(pin_used));

	क्रम (i = 0; i < kpad->var->maxgpio; i++)
		अगर (pdata->keypad_en_mask & BIT(i))
			pin_used[i] = true;

	क्रम (i = 0; i < kpad->gpimapsize; i++)
		pin_used[kpad->gpimap[i].pin - kpad->var->gpi_pin_base] = true;

	अगर (kpad->extend_cfg & R4_EXTEND_CFG)
		pin_used[4] = true;

	अगर (kpad->extend_cfg & C4_EXTEND_CFG)
		pin_used[kpad->var->c4_extend_cfg] = true;

	अगर (!kpad->support_row5)
		pin_used[5] = true;

	क्रम (i = 0; i < kpad->var->maxgpio; i++)
		अगर (!pin_used[i])
			kpad->gpiomap[n_unused++] = i;

	वापस n_unused;
पूर्ण

अटल पूर्णांक adp5589_gpio_add(काष्ठा adp5589_kpad *kpad)
अणु
	काष्ठा device *dev = &kpad->client->dev;
	स्थिर काष्ठा adp5589_kpad_platक्रमm_data *pdata = dev_get_platdata(dev);
	स्थिर काष्ठा adp5589_gpio_platक्रमm_data *gpio_data = pdata->gpio_data;
	पूर्णांक i, error;

	अगर (!gpio_data)
		वापस 0;

	kpad->gc.parent = dev;
	kpad->gc.ngpio = adp5589_build_gpiomap(kpad, pdata);
	अगर (kpad->gc.ngpio == 0) अणु
		dev_info(dev, "No unused gpios left to export\n");
		वापस 0;
	पूर्ण

	kpad->gc.direction_input = adp5589_gpio_direction_input;
	kpad->gc.direction_output = adp5589_gpio_direction_output;
	kpad->gc.get = adp5589_gpio_get_value;
	kpad->gc.set = adp5589_gpio_set_value;
	kpad->gc.can_sleep = 1;

	kpad->gc.base = gpio_data->gpio_start;
	kpad->gc.label = kpad->client->name;
	kpad->gc.owner = THIS_MODULE;

	mutex_init(&kpad->gpio_lock);

	error = devm_gpiochip_add_data(dev, &kpad->gc, kpad);
	अगर (error)
		वापस error;

	क्रम (i = 0; i <= kpad->var->bank(kpad->var->maxgpio); i++) अणु
		kpad->dat_out[i] = adp5589_पढ़ो(kpad->client, kpad->var->reg(
						ADP5589_GPO_DATA_OUT_A) + i);
		kpad->dir[i] = adp5589_पढ़ो(kpad->client, kpad->var->reg(
					    ADP5589_GPIO_सूचीECTION_A) + i);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक adp5589_gpio_add(काष्ठा adp5589_kpad *kpad)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम adp5589_report_चयनes(काष्ठा adp5589_kpad *kpad,
				    पूर्णांक key, पूर्णांक key_val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < kpad->gpimapsize; i++) अणु
		अगर (key_val == kpad->gpimap[i].pin) अणु
			input_report_चयन(kpad->input,
					    kpad->gpimap[i].sw_evt,
					    key & KEY_EV_PRESSED);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम adp5589_report_events(काष्ठा adp5589_kpad *kpad, पूर्णांक ev_cnt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ev_cnt; i++) अणु
		पूर्णांक key = adp5589_पढ़ो(kpad->client, ADP5589_5_FIFO_1 + i);
		पूर्णांक key_val = key & KEY_EV_MASK;

		अगर (key_val >= kpad->var->gpi_pin_base &&
		    key_val <= kpad->var->gpi_pin_end) अणु
			adp5589_report_चयनes(kpad, key, key_val);
		पूर्ण अन्यथा अणु
			input_report_key(kpad->input,
					 kpad->keycode[key_val - 1],
					 key & KEY_EV_PRESSED);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t adp5589_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा adp5589_kpad *kpad = handle;
	काष्ठा i2c_client *client = kpad->client;
	पूर्णांक status, ev_cnt;

	status = adp5589_पढ़ो(client, ADP5589_5_INT_STATUS);

	अगर (status & OVRFLOW_INT)	/* Unlikely and should never happen */
		dev_err(&client->dev, "Event Overflow Error\n");

	अगर (status & EVENT_INT) अणु
		ev_cnt = adp5589_पढ़ो(client, ADP5589_5_STATUS) & KEC;
		अगर (ev_cnt) अणु
			adp5589_report_events(kpad, ev_cnt);
			input_sync(kpad->input);
		पूर्ण
	पूर्ण

	adp5589_ग_लिखो(client, ADP5589_5_INT_STATUS, status); /* Status is W1C */

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adp5589_get_evcode(काष्ठा adp5589_kpad *kpad, अचिन्हित लघु key)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < kpad->var->keymapsize; i++)
		अगर (key == kpad->keycode[i])
			वापस (i + 1) | KEY_EV_PRESSED;

	dev_err(&kpad->client->dev, "RESET/UNLOCK key not in keycode map\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adp5589_setup(काष्ठा adp5589_kpad *kpad)
अणु
	काष्ठा i2c_client *client = kpad->client;
	स्थिर काष्ठा adp5589_kpad_platक्रमm_data *pdata =
		dev_get_platdata(&client->dev);
	u8 (*reg) (u8) = kpad->var->reg;
	अचिन्हित अक्षर evt_mode1 = 0, evt_mode2 = 0, evt_mode3 = 0;
	अचिन्हित अक्षर pull_mask = 0;
	पूर्णांक i, ret;

	ret = adp5589_ग_लिखो(client, reg(ADP5589_PIN_CONFIG_A),
			    pdata->keypad_en_mask & kpad->var->row_mask);
	ret |= adp5589_ग_लिखो(client, reg(ADP5589_PIN_CONFIG_B),
			     (pdata->keypad_en_mask >> kpad->var->col_shअगरt) &
			     kpad->var->col_mask);

	अगर (!kpad->is_adp5585)
		ret |= adp5589_ग_लिखो(client, ADP5589_PIN_CONFIG_C,
				     (pdata->keypad_en_mask >> 16) & 0xFF);

	अगर (!kpad->is_adp5585 && pdata->en_keylock) अणु
		ret |= adp5589_ग_लिखो(client, ADP5589_UNLOCK1,
				     pdata->unlock_key1);
		ret |= adp5589_ग_लिखो(client, ADP5589_UNLOCK2,
				     pdata->unlock_key2);
		ret |= adp5589_ग_लिखो(client, ADP5589_UNLOCK_TIMERS,
				     pdata->unlock_समयr & LTIME_MASK);
		ret |= adp5589_ग_लिखो(client, ADP5589_LOCK_CFG, LOCK_EN);
	पूर्ण

	क्रम (i = 0; i < KEYP_MAX_EVENT; i++)
		ret |= adp5589_पढ़ो(client, ADP5589_5_FIFO_1 + i);

	क्रम (i = 0; i < pdata->gpimapsize; i++) अणु
		अचिन्हित लघु pin = pdata->gpimap[i].pin;

		अगर (pin <= kpad->var->gpi_pin_row_end) अणु
			evt_mode1 |= BIT(pin - kpad->var->gpi_pin_row_base);
		पूर्ण अन्यथा अणु
			evt_mode2 |=
			    BIT(pin - kpad->var->gpi_pin_col_base) & 0xFF;
			अगर (!kpad->is_adp5585)
				evt_mode3 |=
				    BIT(pin - kpad->var->gpi_pin_col_base) >> 8;
		पूर्ण
	पूर्ण

	अगर (pdata->gpimapsize) अणु
		ret |= adp5589_ग_लिखो(client, reg(ADP5589_GPI_EVENT_EN_A),
				     evt_mode1);
		ret |= adp5589_ग_लिखो(client, reg(ADP5589_GPI_EVENT_EN_B),
				     evt_mode2);
		अगर (!kpad->is_adp5585)
			ret |= adp5589_ग_लिखो(client,
					     reg(ADP5589_GPI_EVENT_EN_C),
					     evt_mode3);
	पूर्ण

	अगर (pdata->pull_dis_mask & pdata->pullup_en_100k &
		pdata->pullup_en_300k & pdata->pullकरोwn_en_300k)
		dev_warn(&client->dev, "Conflicting pull resistor config\n");

	क्रम (i = 0; i <= kpad->var->max_row_num; i++) अणु
		अचिन्हित पूर्णांक val = 0, bit = BIT(i);
		अगर (pdata->pullup_en_300k & bit)
			val = 0;
		अन्यथा अगर (pdata->pullकरोwn_en_300k & bit)
			val = 1;
		अन्यथा अगर (pdata->pullup_en_100k & bit)
			val = 2;
		अन्यथा अगर (pdata->pull_dis_mask & bit)
			val = 3;

		pull_mask |= val << (2 * (i & 0x3));

		अगर (i % 4 == 3 || i == kpad->var->max_row_num) अणु
			ret |= adp5589_ग_लिखो(client, reg(ADP5585_RPULL_CONFIG_A)
					     + (i >> 2), pull_mask);
			pull_mask = 0;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i <= kpad->var->max_col_num; i++) अणु
		अचिन्हित पूर्णांक val = 0, bit = BIT(i + kpad->var->col_shअगरt);
		अगर (pdata->pullup_en_300k & bit)
			val = 0;
		अन्यथा अगर (pdata->pullकरोwn_en_300k & bit)
			val = 1;
		अन्यथा अगर (pdata->pullup_en_100k & bit)
			val = 2;
		अन्यथा अगर (pdata->pull_dis_mask & bit)
			val = 3;

		pull_mask |= val << (2 * (i & 0x3));

		अगर (i % 4 == 3 || i == kpad->var->max_col_num) अणु
			ret |= adp5589_ग_लिखो(client,
					     reg(ADP5585_RPULL_CONFIG_C) +
					     (i >> 2), pull_mask);
			pull_mask = 0;
		पूर्ण
	पूर्ण

	अगर (pdata->reset1_key_1 && pdata->reset1_key_2 && pdata->reset1_key_3) अणु
		ret |= adp5589_ग_लिखो(client, reg(ADP5589_RESET1_EVENT_A),
				     adp5589_get_evcode(kpad,
							pdata->reset1_key_1));
		ret |= adp5589_ग_लिखो(client, reg(ADP5589_RESET1_EVENT_B),
				     adp5589_get_evcode(kpad,
							pdata->reset1_key_2));
		ret |= adp5589_ग_लिखो(client, reg(ADP5589_RESET1_EVENT_C),
				     adp5589_get_evcode(kpad,
							pdata->reset1_key_3));
		kpad->extend_cfg |= R4_EXTEND_CFG;
	पूर्ण

	अगर (pdata->reset2_key_1 && pdata->reset2_key_2) अणु
		ret |= adp5589_ग_लिखो(client, reg(ADP5589_RESET2_EVENT_A),
				     adp5589_get_evcode(kpad,
							pdata->reset2_key_1));
		ret |= adp5589_ग_लिखो(client, reg(ADP5589_RESET2_EVENT_B),
				     adp5589_get_evcode(kpad,
							pdata->reset2_key_2));
		kpad->extend_cfg |= C4_EXTEND_CFG;
	पूर्ण

	अगर (kpad->extend_cfg) अणु
		ret |= adp5589_ग_लिखो(client, reg(ADP5589_RESET_CFG),
				     pdata->reset_cfg);
		ret |= adp5589_ग_लिखो(client, reg(ADP5589_PIN_CONFIG_D),
				     kpad->extend_cfg);
	पूर्ण

	ret |= adp5589_ग_लिखो(client, reg(ADP5589_DEBOUNCE_DIS_A),
			    pdata->debounce_dis_mask & kpad->var->row_mask);

	ret |= adp5589_ग_लिखो(client, reg(ADP5589_DEBOUNCE_DIS_B),
			     (pdata->debounce_dis_mask >> kpad->var->col_shअगरt)
			     & kpad->var->col_mask);

	अगर (!kpad->is_adp5585)
		ret |= adp5589_ग_लिखो(client, reg(ADP5589_DEBOUNCE_DIS_C),
				     (pdata->debounce_dis_mask >> 16) & 0xFF);

	ret |= adp5589_ग_लिखो(client, reg(ADP5589_POLL_PTIME_CFG),
			     pdata->scan_cycle_समय & PTIME_MASK);
	ret |= adp5589_ग_लिखो(client, ADP5589_5_INT_STATUS,
			     (kpad->is_adp5585 ? 0 : LOGIC2_INT) |
			     LOGIC1_INT | OVRFLOW_INT |
			     (kpad->is_adp5585 ? 0 : LOCK_INT) |
			     GPI_INT | EVENT_INT);	/* Status is W1C */

	ret |= adp5589_ग_लिखो(client, reg(ADP5589_GENERAL_CFG),
			     INT_CFG | OSC_EN | CORE_CLK(3));
	ret |= adp5589_ग_लिखो(client, reg(ADP5589_INT_EN),
			     OVRFLOW_IEN | GPI_IEN | EVENT_IEN);

	अगर (ret < 0) अणु
		dev_err(&client->dev, "Write Error\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adp5589_report_चयन_state(काष्ठा adp5589_kpad *kpad)
अणु
	पूर्णांक gpi_stat_पंचांगp, pin_loc;
	पूर्णांक i;
	पूर्णांक gpi_stat1 = adp5589_पढ़ो(kpad->client,
				     kpad->var->reg(ADP5589_GPI_STATUS_A));
	पूर्णांक gpi_stat2 = adp5589_पढ़ो(kpad->client,
				     kpad->var->reg(ADP5589_GPI_STATUS_B));
	पूर्णांक gpi_stat3 = !kpad->is_adp5585 ?
			adp5589_पढ़ो(kpad->client, ADP5589_GPI_STATUS_C) : 0;

	क्रम (i = 0; i < kpad->gpimapsize; i++) अणु
		अचिन्हित लघु pin = kpad->gpimap[i].pin;

		अगर (pin <= kpad->var->gpi_pin_row_end) अणु
			gpi_stat_पंचांगp = gpi_stat1;
			pin_loc = pin - kpad->var->gpi_pin_row_base;
		पूर्ण अन्यथा अगर ((pin - kpad->var->gpi_pin_col_base) < 8) अणु
			gpi_stat_पंचांगp = gpi_stat2;
			pin_loc = pin - kpad->var->gpi_pin_col_base;
		पूर्ण अन्यथा अणु
			gpi_stat_पंचांगp = gpi_stat3;
			pin_loc = pin - kpad->var->gpi_pin_col_base - 8;
		पूर्ण

		अगर (gpi_stat_पंचांगp < 0) अणु
			dev_err(&kpad->client->dev,
				"Can't read GPIO_DAT_STAT switch %d, default to OFF\n",
				pin);
			gpi_stat_पंचांगp = 0;
		पूर्ण

		input_report_चयन(kpad->input,
				    kpad->gpimap[i].sw_evt,
				    !(gpi_stat_पंचांगp & BIT(pin_loc)));
	पूर्ण

	input_sync(kpad->input);
पूर्ण

अटल पूर्णांक adp5589_keypad_add(काष्ठा adp5589_kpad *kpad, अचिन्हित पूर्णांक revid)
अणु
	काष्ठा i2c_client *client = kpad->client;
	स्थिर काष्ठा adp5589_kpad_platक्रमm_data *pdata =
		dev_get_platdata(&client->dev);
	काष्ठा input_dev *input;
	अचिन्हित पूर्णांक i;
	पूर्णांक error;

	अगर (!((pdata->keypad_en_mask & kpad->var->row_mask) &&
			(pdata->keypad_en_mask >> kpad->var->col_shअगरt)) ||
			!pdata->keymap) अणु
		dev_err(&client->dev, "no rows, cols or keymap from pdata\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->keymapsize != kpad->var->keymapsize) अणु
		dev_err(&client->dev, "invalid keymapsize\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pdata->gpimap && pdata->gpimapsize) अणु
		dev_err(&client->dev, "invalid gpimap from pdata\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->gpimapsize > kpad->var->gpimapsize_max) अणु
		dev_err(&client->dev, "invalid gpimapsize\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < pdata->gpimapsize; i++) अणु
		अचिन्हित लघु pin = pdata->gpimap[i].pin;

		अगर (pin < kpad->var->gpi_pin_base ||
				pin > kpad->var->gpi_pin_end) अणु
			dev_err(&client->dev, "invalid gpi pin data\n");
			वापस -EINVAL;
		पूर्ण

		अगर (BIT(pin - kpad->var->gpi_pin_row_base) &
				pdata->keypad_en_mask) अणु
			dev_err(&client->dev, "invalid gpi row/col data\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!client->irq) अणु
		dev_err(&client->dev, "no IRQ?\n");
		वापस -EINVAL;
	पूर्ण

	input = devm_input_allocate_device(&client->dev);
	अगर (!input)
		वापस -ENOMEM;

	kpad->input = input;

	input->name = client->name;
	input->phys = "adp5589-keys/input0";
	input->dev.parent = &client->dev;

	input_set_drvdata(input, kpad);

	input->id.bustype = BUS_I2C;
	input->id.venकरोr = 0x0001;
	input->id.product = 0x0001;
	input->id.version = revid;

	input->keycodesize = माप(kpad->keycode[0]);
	input->keycodemax = pdata->keymapsize;
	input->keycode = kpad->keycode;

	स_नकल(kpad->keycode, pdata->keymap,
	       pdata->keymapsize * input->keycodesize);

	kpad->gpimap = pdata->gpimap;
	kpad->gpimapsize = pdata->gpimapsize;

	/* setup input device */
	__set_bit(EV_KEY, input->evbit);

	अगर (pdata->repeat)
		__set_bit(EV_REP, input->evbit);

	क्रम (i = 0; i < input->keycodemax; i++)
		अगर (kpad->keycode[i] <= KEY_MAX)
			__set_bit(kpad->keycode[i], input->keybit);
	__clear_bit(KEY_RESERVED, input->keybit);

	अगर (kpad->gpimapsize)
		__set_bit(EV_SW, input->evbit);
	क्रम (i = 0; i < kpad->gpimapsize; i++)
		__set_bit(kpad->gpimap[i].sw_evt, input->swbit);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&client->dev, "unable to register input device\n");
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, adp5589_irq,
					  IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					  client->dev.driver->name, kpad);
	अगर (error) अणु
		dev_err(&client->dev, "unable to request irq %d\n", client->irq);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adp5589_clear_config(व्योम *data)
अणु
	काष्ठा i2c_client *client = data;
	काष्ठा adp5589_kpad *kpad = i2c_get_clientdata(client);

	adp5589_ग_लिखो(client, kpad->var->reg(ADP5589_GENERAL_CFG), 0);
पूर्ण

अटल पूर्णांक adp5589_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adp5589_kpad *kpad;
	स्थिर काष्ठा adp5589_kpad_platक्रमm_data *pdata =
		dev_get_platdata(&client->dev);
	अचिन्हित पूर्णांक revid;
	पूर्णांक error, ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&client->dev, "SMBUS Byte Data not Supported\n");
		वापस -EIO;
	पूर्ण

	अगर (!pdata) अणु
		dev_err(&client->dev, "no platform data?\n");
		वापस -EINVAL;
	पूर्ण

	kpad = devm_kzalloc(&client->dev, माप(*kpad), GFP_KERNEL);
	अगर (!kpad)
		वापस -ENOMEM;

	kpad->client = client;

	चयन (id->driver_data) अणु
	हाल ADP5585_02:
		kpad->support_row5 = true;
		fallthrough;
	हाल ADP5585_01:
		kpad->is_adp5585 = true;
		kpad->var = &स्थिर_adp5585;
		अवरोध;
	हाल ADP5589:
		kpad->support_row5 = true;
		kpad->var = &स्थिर_adp5589;
		अवरोध;
	पूर्ण

	error = devm_add_action_or_reset(&client->dev, adp5589_clear_config,
					 client);
	अगर (error)
		वापस error;

	ret = adp5589_पढ़ो(client, ADP5589_5_ID);
	अगर (ret < 0)
		वापस ret;

	revid = (u8) ret & ADP5589_5_DEVICE_ID_MASK;

	अगर (pdata->keymapsize) अणु
		error = adp5589_keypad_add(kpad, revid);
		अगर (error)
			वापस error;
	पूर्ण

	error = adp5589_setup(kpad);
	अगर (error)
		वापस error;

	अगर (kpad->gpimapsize)
		adp5589_report_चयन_state(kpad);

	error = adp5589_gpio_add(kpad);
	अगर (error)
		वापस error;

	i2c_set_clientdata(client, kpad);

	dev_info(&client->dev, "Rev.%d keypad, irq %d\n", revid, client->irq);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused adp5589_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा adp5589_kpad *kpad = i2c_get_clientdata(client);

	अगर (kpad->input)
		disable_irq(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused adp5589_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा adp5589_kpad *kpad = i2c_get_clientdata(client);

	अगर (kpad->input)
		enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(adp5589_dev_pm_ops, adp5589_suspend, adp5589_resume);

अटल स्थिर काष्ठा i2c_device_id adp5589_id[] = अणु
	अणु"adp5589-keys", ADP5589पूर्ण,
	अणु"adp5585-keys", ADP5585_01पूर्ण,
	अणु"adp5585-02-keys", ADP5585_02पूर्ण, /* Adds ROW5 to ADP5585 */
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, adp5589_id);

अटल काष्ठा i2c_driver adp5589_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.pm = &adp5589_dev_pm_ops,
	पूर्ण,
	.probe = adp5589_probe,
	.id_table = adp5589_id,
पूर्ण;

module_i2c_driver(adp5589_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michael Hennerich <hennerich@blackfin.uclinux.org>");
MODULE_DESCRIPTION("ADP5589/ADP5585 Keypad driver");
