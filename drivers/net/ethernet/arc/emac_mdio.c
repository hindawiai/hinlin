<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2004-2013 Synopsys, Inc. (www.synopsys.com)
 *
 * MDIO implementation क्रम ARC EMAC
 */

#समावेश <linux/delay.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "emac.h"

/* Number of seconds we रुको क्रम "MDIO complete" flag to appear */
#घोषणा ARC_MDIO_COMPLETE_POLL_COUNT	1

/**
 * arc_mdio_complete_रुको - Waits until MDIO transaction is completed.
 * @priv:	Poपूर्णांकer to ARC EMAC निजी data काष्ठाure.
 *
 * वापसs:	0 on success, -ETIMEDOUT on a समयout.
 */
अटल पूर्णांक arc_mdio_complete_रुको(काष्ठा arc_emac_priv *priv)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARC_MDIO_COMPLETE_POLL_COUNT * 40; i++) अणु
		अचिन्हित पूर्णांक status = arc_reg_get(priv, R_STATUS);

		status &= MDIO_MASK;

		अगर (status) अणु
			/* Reset "MDIO complete" flag */
			arc_reg_set(priv, R_STATUS, status);
			वापस 0;
		पूर्ण

		msleep(25);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

/**
 * arc_mdio_पढ़ो - MDIO पूर्णांकerface पढ़ो function.
 * @bus:	Poपूर्णांकer to MII bus काष्ठाure.
 * @phy_addr:	Address of the PHY device.
 * @reg_num:	PHY रेजिस्टर to पढ़ो.
 *
 * वापसs:	The रेजिस्टर contents on success, -ETIMEDOUT on a समयout.
 *
 * Reads the contents of the requested रेजिस्टर from the requested PHY
 * address.
 */
अटल पूर्णांक arc_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक reg_num)
अणु
	काष्ठा arc_emac_priv *priv = bus->priv;
	अचिन्हित पूर्णांक value;
	पूर्णांक error;

	arc_reg_set(priv, R_MDIO,
		    0x60020000 | (phy_addr << 23) | (reg_num << 18));

	error = arc_mdio_complete_रुको(priv);
	अगर (error < 0)
		वापस error;

	value = arc_reg_get(priv, R_MDIO) & 0xffff;

	dev_dbg(priv->dev, "arc_mdio_read(phy_addr=%i, reg_num=%x) = %x\n",
		phy_addr, reg_num, value);

	वापस value;
पूर्ण

/**
 * arc_mdio_ग_लिखो - MDIO पूर्णांकerface ग_लिखो function.
 * @bus:	Poपूर्णांकer to MII bus काष्ठाure.
 * @phy_addr:	Address of the PHY device.
 * @reg_num:	PHY रेजिस्टर to ग_लिखो to.
 * @value:	Value to be written पूर्णांकo the रेजिस्टर.
 *
 * वापसs:	0 on success, -ETIMEDOUT on a समयout.
 *
 * Writes the value to the requested रेजिस्टर.
 */
अटल पूर्णांक arc_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_addr,
			  पूर्णांक reg_num, u16 value)
अणु
	काष्ठा arc_emac_priv *priv = bus->priv;

	dev_dbg(priv->dev,
		"arc_mdio_write(phy_addr=%i, reg_num=%x, value=%x)\n",
		phy_addr, reg_num, value);

	arc_reg_set(priv, R_MDIO,
		    0x50020000 | (phy_addr << 23) | (reg_num << 18) | value);

	वापस arc_mdio_complete_रुको(priv);
पूर्ण

/**
 * arc_mdio_reset
 * @bus: poपूर्णांकs to the mii_bus काष्ठाure
 * Description: reset the MII bus
 */
अटल पूर्णांक arc_mdio_reset(काष्ठा mii_bus *bus)
अणु
	काष्ठा arc_emac_priv *priv = bus->priv;
	काष्ठा arc_emac_mdio_bus_data *data = &priv->bus_data;

	अगर (data->reset_gpio) अणु
		gpiod_set_value_cansleep(data->reset_gpio, 1);
		msleep(data->msec);
		gpiod_set_value_cansleep(data->reset_gpio, 0);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * arc_mdio_probe - MDIO probe function.
 * @priv:	Poपूर्णांकer to ARC EMAC निजी data काष्ठाure.
 *
 * वापसs:	0 on success, -ENOMEM when mdiobus_alloc
 * (to allocate memory क्रम MII bus काष्ठाure) fails.
 *
 * Sets up and रेजिस्टरs the MDIO पूर्णांकerface.
 */
पूर्णांक arc_mdio_probe(काष्ठा arc_emac_priv *priv)
अणु
	काष्ठा arc_emac_mdio_bus_data *data = &priv->bus_data;
	काष्ठा device_node *np = priv->dev->of_node;
	काष्ठा mii_bus *bus;
	पूर्णांक error;

	bus = mdiobus_alloc();
	अगर (!bus)
		वापस -ENOMEM;

	priv->bus = bus;
	bus->priv = priv;
	bus->parent = priv->dev;
	bus->name = "Synopsys MII Bus";
	bus->पढ़ो = &arc_mdio_पढ़ो;
	bus->ग_लिखो = &arc_mdio_ग_लिखो;
	bus->reset = &arc_mdio_reset;

	/* optional reset-related properties */
	data->reset_gpio = devm_gpiod_get_optional(priv->dev, "phy-reset",
						   GPIOD_OUT_LOW);
	अगर (IS_ERR(data->reset_gpio)) अणु
		error = PTR_ERR(data->reset_gpio);
		dev_err(priv->dev, "Failed to request gpio: %d\n", error);
		mdiobus_मुक्त(bus);
		वापस error;
	पूर्ण

	of_property_पढ़ो_u32(np, "phy-reset-duration", &data->msec);
	/* A sane reset duration should not be दीर्घer than 1s */
	अगर (data->msec > 1000)
		data->msec = 1;

	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s", bus->name);

	error = of_mdiobus_रेजिस्टर(bus, priv->dev->of_node);
	अगर (error) अणु
		dev_err(priv->dev, "cannot register MDIO bus %s\n", bus->name);
		mdiobus_मुक्त(bus);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * arc_mdio_हटाओ - MDIO हटाओ function.
 * @priv:	Poपूर्णांकer to ARC EMAC निजी data काष्ठाure.
 *
 * Unरेजिस्टरs the MDIO and मुक्तs any associate memory क्रम MII bus.
 */
पूर्णांक arc_mdio_हटाओ(काष्ठा arc_emac_priv *priv)
अणु
	mdiobus_unरेजिस्टर(priv->bus);
	mdiobus_मुक्त(priv->bus);
	priv->bus = शून्य;

	वापस 0;
पूर्ण
