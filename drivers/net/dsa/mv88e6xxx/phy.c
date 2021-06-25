<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88e6xxx Ethernet चयन PHY and PPU support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2017 Andrew Lunn <andrew@lunn.ch>
 */

#समावेश <linux/mdपन.स>
#समावेश <linux/module.h>

#समावेश "chip.h"
#समावेश "phy.h"

पूर्णांक mv88e6165_phy_पढ़ो(काष्ठा mv88e6xxx_chip *chip, काष्ठा mii_bus *bus,
		       पूर्णांक addr, पूर्णांक reg, u16 *val)
अणु
	वापस mv88e6xxx_पढ़ो(chip, addr, reg, val);
पूर्ण

पूर्णांक mv88e6165_phy_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, काष्ठा mii_bus *bus,
			पूर्णांक addr, पूर्णांक reg, u16 val)
अणु
	वापस mv88e6xxx_ग_लिखो(chip, addr, reg, val);
पूर्ण

पूर्णांक mv88e6xxx_phy_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक phy, पूर्णांक reg, u16 *val)
अणु
	पूर्णांक addr = phy; /* PHY devices addresses start at 0x0 */
	काष्ठा mii_bus *bus;

	bus = mv88e6xxx_शेष_mdio_bus(chip);
	अगर (!bus)
		वापस -EOPNOTSUPP;

	अगर (!chip->info->ops->phy_पढ़ो)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->phy_पढ़ो(chip, bus, addr, reg, val);
पूर्ण

पूर्णांक mv88e6xxx_phy_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक phy, पूर्णांक reg, u16 val)
अणु
	पूर्णांक addr = phy; /* PHY devices addresses start at 0x0 */
	काष्ठा mii_bus *bus;

	bus = mv88e6xxx_शेष_mdio_bus(chip);
	अगर (!bus)
		वापस -EOPNOTSUPP;

	अगर (!chip->info->ops->phy_ग_लिखो)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->phy_ग_लिखो(chip, bus, addr, reg, val);
पूर्ण

अटल पूर्णांक mv88e6xxx_phy_page_get(काष्ठा mv88e6xxx_chip *chip, पूर्णांक phy, u8 page)
अणु
	वापस mv88e6xxx_phy_ग_लिखो(chip, phy, MV88E6XXX_PHY_PAGE, page);
पूर्ण

अटल व्योम mv88e6xxx_phy_page_put(काष्ठा mv88e6xxx_chip *chip, पूर्णांक phy)
अणु
	पूर्णांक err;

	/* Restore PHY page Copper 0x0 क्रम access via the रेजिस्टरed
	 * MDIO bus
	 */
	err = mv88e6xxx_phy_ग_लिखो(chip, phy, MV88E6XXX_PHY_PAGE,
				  MV88E6XXX_PHY_PAGE_COPPER);
	अगर (unlikely(err)) अणु
		dev_err(chip->dev,
			"failed to restore PHY %d page Copper (%d)\n",
			phy, err);
	पूर्ण
पूर्ण

पूर्णांक mv88e6xxx_phy_page_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक phy,
			    u8 page, पूर्णांक reg, u16 *val)
अणु
	पूर्णांक err;

	/* There is no paging क्रम रेजिस्टरs 22 */
	अगर (reg == MV88E6XXX_PHY_PAGE)
		वापस -EINVAL;

	err = mv88e6xxx_phy_page_get(chip, phy, page);
	अगर (!err) अणु
		err = mv88e6xxx_phy_पढ़ो(chip, phy, reg, val);
		mv88e6xxx_phy_page_put(chip, phy);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक mv88e6xxx_phy_page_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक phy,
			     u8 page, पूर्णांक reg, u16 val)
अणु
	पूर्णांक err;

	/* There is no paging क्रम रेजिस्टरs 22 */
	अगर (reg == MV88E6XXX_PHY_PAGE)
		वापस -EINVAL;

	err = mv88e6xxx_phy_page_get(chip, phy, page);
	अगर (!err) अणु
		err = mv88e6xxx_phy_ग_लिखो(chip, phy, MV88E6XXX_PHY_PAGE, page);
		अगर (!err)
			err = mv88e6xxx_phy_ग_लिखो(chip, phy, reg, val);

		mv88e6xxx_phy_page_put(chip, phy);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_phy_ppu_disable(काष्ठा mv88e6xxx_chip *chip)
अणु
	अगर (!chip->info->ops->ppu_disable)
		वापस 0;

	वापस chip->info->ops->ppu_disable(chip);
पूर्ण

अटल पूर्णांक mv88e6xxx_phy_ppu_enable(काष्ठा mv88e6xxx_chip *chip)
अणु
	अगर (!chip->info->ops->ppu_enable)
		वापस 0;

	वापस chip->info->ops->ppu_enable(chip);
पूर्ण

अटल व्योम mv88e6xxx_phy_ppu_reenable_work(काष्ठा work_काष्ठा *ugly)
अणु
	काष्ठा mv88e6xxx_chip *chip;

	chip = container_of(ugly, काष्ठा mv88e6xxx_chip, ppu_work);

	mv88e6xxx_reg_lock(chip);

	अगर (mutex_trylock(&chip->ppu_mutex)) अणु
		अगर (mv88e6xxx_phy_ppu_enable(chip) == 0)
			chip->ppu_disabled = 0;
		mutex_unlock(&chip->ppu_mutex);
	पूर्ण

	mv88e6xxx_reg_unlock(chip);
पूर्ण

अटल व्योम mv88e6xxx_phy_ppu_reenable_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mv88e6xxx_chip *chip = from_समयr(chip, t, ppu_समयr);

	schedule_work(&chip->ppu_work);
पूर्ण

अटल पूर्णांक mv88e6xxx_phy_ppu_access_get(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक ret;

	mutex_lock(&chip->ppu_mutex);

	/* If the PHY polling unit is enabled, disable it so that
	 * we can access the PHY रेजिस्टरs.  If it was alपढ़ोy
	 * disabled, cancel the समयr that is going to re-enable
	 * it.
	 */
	अगर (!chip->ppu_disabled) अणु
		ret = mv88e6xxx_phy_ppu_disable(chip);
		अगर (ret < 0) अणु
			mutex_unlock(&chip->ppu_mutex);
			वापस ret;
		पूर्ण
		chip->ppu_disabled = 1;
	पूर्ण अन्यथा अणु
		del_समयr(&chip->ppu_समयr);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम mv88e6xxx_phy_ppu_access_put(काष्ठा mv88e6xxx_chip *chip)
अणु
	/* Schedule a समयr to re-enable the PHY polling unit. */
	mod_समयr(&chip->ppu_समयr, jअगरfies + msecs_to_jअगरfies(10));
	mutex_unlock(&chip->ppu_mutex);
पूर्ण

अटल व्योम mv88e6xxx_phy_ppu_state_init(काष्ठा mv88e6xxx_chip *chip)
अणु
	mutex_init(&chip->ppu_mutex);
	INIT_WORK(&chip->ppu_work, mv88e6xxx_phy_ppu_reenable_work);
	समयr_setup(&chip->ppu_समयr, mv88e6xxx_phy_ppu_reenable_समयr, 0);
पूर्ण

अटल व्योम mv88e6xxx_phy_ppu_state_destroy(काष्ठा mv88e6xxx_chip *chip)
अणु
	del_समयr_sync(&chip->ppu_समयr);
पूर्ण

पूर्णांक mv88e6185_phy_ppu_पढ़ो(काष्ठा mv88e6xxx_chip *chip, काष्ठा mii_bus *bus,
			   पूर्णांक addr, पूर्णांक reg, u16 *val)
अणु
	पूर्णांक err;

	err = mv88e6xxx_phy_ppu_access_get(chip);
	अगर (!err) अणु
		err = mv88e6xxx_पढ़ो(chip, addr, reg, val);
		mv88e6xxx_phy_ppu_access_put(chip);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक mv88e6185_phy_ppu_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, काष्ठा mii_bus *bus,
			    पूर्णांक addr, पूर्णांक reg, u16 val)
अणु
	पूर्णांक err;

	err = mv88e6xxx_phy_ppu_access_get(chip);
	अगर (!err) अणु
		err = mv88e6xxx_ग_लिखो(chip, addr, reg, val);
		mv88e6xxx_phy_ppu_access_put(chip);
	पूर्ण

	वापस err;
पूर्ण

व्योम mv88e6xxx_phy_init(काष्ठा mv88e6xxx_chip *chip)
अणु
	अगर (chip->info->ops->ppu_enable && chip->info->ops->ppu_disable)
		mv88e6xxx_phy_ppu_state_init(chip);
पूर्ण

व्योम mv88e6xxx_phy_destroy(काष्ठा mv88e6xxx_chip *chip)
अणु
	अगर (chip->info->ops->ppu_enable && chip->info->ops->ppu_disable)
		mv88e6xxx_phy_ppu_state_destroy(chip);
पूर्ण

पूर्णांक mv88e6xxx_phy_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_phy_ppu_enable(chip);
पूर्ण
