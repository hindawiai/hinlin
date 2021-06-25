<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* MCP23S08 SPI/I2C GPIO driver */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/irq.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/types.h>

/*
 * MCP types supported by driver
 */
#घोषणा MCP_TYPE_S08	1
#घोषणा MCP_TYPE_S17	2
#घोषणा MCP_TYPE_008	3
#घोषणा MCP_TYPE_017	4
#घोषणा MCP_TYPE_S18	5
#घोषणा MCP_TYPE_018	6

काष्ठा device;
काष्ठा regmap;

काष्ठा pinctrl_dev;

काष्ठा mcp23s08 अणु
	u8			addr;
	bool			irq_active_high;
	bool			reg_shअगरt;

	u16			irq_rise;
	u16			irq_fall;
	पूर्णांक			irq;
	bool			irq_controller;
	पूर्णांक			cached_gpio;
	/* lock protects regmap access with bypass/cache flags */
	काष्ठा mutex		lock;

	काष्ठा gpio_chip	chip;
	काष्ठा irq_chip		irq_chip;

	काष्ठा regmap		*regmap;
	काष्ठा device		*dev;

	काष्ठा pinctrl_dev	*pctldev;
	काष्ठा pinctrl_desc	pinctrl_desc;
पूर्ण;

बाह्य स्थिर काष्ठा regmap_config mcp23x08_regmap;
बाह्य स्थिर काष्ठा regmap_config mcp23x17_regmap;

पूर्णांक mcp23s08_probe_one(काष्ठा mcp23s08 *mcp, काष्ठा device *dev,
		       अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक base);
