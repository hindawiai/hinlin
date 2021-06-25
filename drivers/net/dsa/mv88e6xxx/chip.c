<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88e6xxx Ethernet चयन single-chip support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2016 Andrew Lunn <andrew@lunn.ch>
 *
 * Copyright (c) 2016-2017 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/list.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/platक्रमm_data/mv88e6xxx.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/phylink.h>
#समावेश <net/dsa.h>

#समावेश "chip.h"
#समावेश "devlink.h"
#समावेश "global1.h"
#समावेश "global2.h"
#समावेश "hwtstamp.h"
#समावेश "phy.h"
#समावेश "port.h"
#समावेश "ptp.h"
#समावेश "serdes.h"
#समावेश "smi.h"

अटल व्योम निश्चित_reg_lock(काष्ठा mv88e6xxx_chip *chip)
अणु
	अगर (unlikely(!mutex_is_locked(&chip->reg_lock))) अणु
		dev_err(chip->dev, "Switch registers lock not held!\n");
		dump_stack();
	पूर्ण
पूर्ण

पूर्णांक mv88e6xxx_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, पूर्णांक reg, u16 *val)
अणु
	पूर्णांक err;

	निश्चित_reg_lock(chip);

	err = mv88e6xxx_smi_पढ़ो(chip, addr, reg, val);
	अगर (err)
		वापस err;

	dev_dbg(chip->dev, "<- addr: 0x%.2x reg: 0x%.2x val: 0x%.4x\n",
		addr, reg, *val);

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, पूर्णांक reg, u16 val)
अणु
	पूर्णांक err;

	निश्चित_reg_lock(chip);

	err = mv88e6xxx_smi_ग_लिखो(chip, addr, reg, val);
	अगर (err)
		वापस err;

	dev_dbg(chip->dev, "-> addr: 0x%.2x reg: 0x%.2x val: 0x%.4x\n",
		addr, reg, val);

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_रुको_mask(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, पूर्णांक reg,
			u16 mask, u16 val)
अणु
	u16 data;
	पूर्णांक err;
	पूर्णांक i;

	/* There's no bus specअगरic operation to रुको क्रम a mask */
	क्रम (i = 0; i < 16; i++) अणु
		err = mv88e6xxx_पढ़ो(chip, addr, reg, &data);
		अगर (err)
			वापस err;

		अगर ((data & mask) == val)
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण

	dev_err(chip->dev, "Timeout while waiting for switch\n");
	वापस -ETIMEDOUT;
पूर्ण

पूर्णांक mv88e6xxx_रुको_bit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, पूर्णांक reg,
		       पूर्णांक bit, पूर्णांक val)
अणु
	वापस mv88e6xxx_रुको_mask(chip, addr, reg, BIT(bit),
				   val ? BIT(bit) : 0x0000);
पूर्ण

काष्ठा mii_bus *mv88e6xxx_शेष_mdio_bus(काष्ठा mv88e6xxx_chip *chip)
अणु
	काष्ठा mv88e6xxx_mdio_bus *mdio_bus;

	mdio_bus = list_first_entry(&chip->mdios, काष्ठा mv88e6xxx_mdio_bus,
				    list);
	अगर (!mdio_bus)
		वापस शून्य;

	वापस mdio_bus->bus;
पूर्ण

अटल व्योम mv88e6xxx_g1_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा mv88e6xxx_chip *chip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक n = d->hwirq;

	chip->g1_irq.masked |= (1 << n);
पूर्ण

अटल व्योम mv88e6xxx_g1_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा mv88e6xxx_chip *chip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक n = d->hwirq;

	chip->g1_irq.masked &= ~(1 << n);
पूर्ण

अटल irqवापस_t mv88e6xxx_g1_irq_thपढ़ो_work(काष्ठा mv88e6xxx_chip *chip)
अणु
	अचिन्हित पूर्णांक nhandled = 0;
	अचिन्हित पूर्णांक sub_irq;
	अचिन्हित पूर्णांक n;
	u16 reg;
	u16 ctl1;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_STS, &reg);
	mv88e6xxx_reg_unlock(chip);

	अगर (err)
		जाओ out;

	करो अणु
		क्रम (n = 0; n < chip->g1_irq.nirqs; ++n) अणु
			अगर (reg & (1 << n)) अणु
				sub_irq = irq_find_mapping(chip->g1_irq.करोमुख्य,
							   n);
				handle_nested_irq(sub_irq);
				++nhandled;
			पूर्ण
		पूर्ण

		mv88e6xxx_reg_lock(chip);
		err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_CTL1, &ctl1);
		अगर (err)
			जाओ unlock;
		err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_STS, &reg);
unlock:
		mv88e6xxx_reg_unlock(chip);
		अगर (err)
			जाओ out;
		ctl1 &= GENMASK(chip->g1_irq.nirqs, 0);
	पूर्ण जबतक (reg & ctl1);

out:
	वापस (nhandled > 0 ? IRQ_HANDLED : IRQ_NONE);
पूर्ण

अटल irqवापस_t mv88e6xxx_g1_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mv88e6xxx_chip *chip = dev_id;

	वापस mv88e6xxx_g1_irq_thपढ़ो_work(chip);
पूर्ण

अटल व्योम mv88e6xxx_g1_irq_bus_lock(काष्ठा irq_data *d)
अणु
	काष्ठा mv88e6xxx_chip *chip = irq_data_get_irq_chip_data(d);

	mv88e6xxx_reg_lock(chip);
पूर्ण

अटल व्योम mv88e6xxx_g1_irq_bus_sync_unlock(काष्ठा irq_data *d)
अणु
	काष्ठा mv88e6xxx_chip *chip = irq_data_get_irq_chip_data(d);
	u16 mask = GENMASK(chip->g1_irq.nirqs, 0);
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_CTL1, &reg);
	अगर (err)
		जाओ out;

	reg &= ~mask;
	reg |= (~chip->g1_irq.masked & mask);

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_CTL1, reg);
	अगर (err)
		जाओ out;

out:
	mv88e6xxx_reg_unlock(chip);
पूर्ण

अटल स्थिर काष्ठा irq_chip mv88e6xxx_g1_irq_chip = अणु
	.name			= "mv88e6xxx-g1",
	.irq_mask		= mv88e6xxx_g1_irq_mask,
	.irq_unmask		= mv88e6xxx_g1_irq_unmask,
	.irq_bus_lock		= mv88e6xxx_g1_irq_bus_lock,
	.irq_bus_sync_unlock	= mv88e6xxx_g1_irq_bus_sync_unlock,
पूर्ण;

अटल पूर्णांक mv88e6xxx_g1_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d,
				       अचिन्हित पूर्णांक irq,
				       irq_hw_number_t hwirq)
अणु
	काष्ठा mv88e6xxx_chip *chip = d->host_data;

	irq_set_chip_data(irq, d->host_data);
	irq_set_chip_and_handler(irq, &chip->g1_irq.chip, handle_level_irq);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mv88e6xxx_g1_irq_करोमुख्य_ops = अणु
	.map	= mv88e6xxx_g1_irq_करोमुख्य_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

/* To be called with reg_lock held */
अटल व्योम mv88e6xxx_g1_irq_मुक्त_common(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक irq, virq;
	u16 mask;

	mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_CTL1, &mask);
	mask &= ~GENMASK(chip->g1_irq.nirqs, 0);
	mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_CTL1, mask);

	क्रम (irq = 0; irq < chip->g1_irq.nirqs; irq++) अणु
		virq = irq_find_mapping(chip->g1_irq.करोमुख्य, irq);
		irq_dispose_mapping(virq);
	पूर्ण

	irq_करोमुख्य_हटाओ(chip->g1_irq.करोमुख्य);
पूर्ण

अटल व्योम mv88e6xxx_g1_irq_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
	/*
	 * मुक्त_irq must be called without reg_lock taken because the irq
	 * handler takes this lock, too.
	 */
	मुक्त_irq(chip->irq, chip);

	mv88e6xxx_reg_lock(chip);
	mv88e6xxx_g1_irq_मुक्त_common(chip);
	mv88e6xxx_reg_unlock(chip);
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_irq_setup_common(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err, irq, virq;
	u16 reg, mask;

	chip->g1_irq.nirqs = chip->info->g1_irqs;
	chip->g1_irq.करोमुख्य = irq_करोमुख्य_add_simple(
		शून्य, chip->g1_irq.nirqs, 0,
		&mv88e6xxx_g1_irq_करोमुख्य_ops, chip);
	अगर (!chip->g1_irq.करोमुख्य)
		वापस -ENOMEM;

	क्रम (irq = 0; irq < chip->g1_irq.nirqs; irq++)
		irq_create_mapping(chip->g1_irq.करोमुख्य, irq);

	chip->g1_irq.chip = mv88e6xxx_g1_irq_chip;
	chip->g1_irq.masked = ~0;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_CTL1, &mask);
	अगर (err)
		जाओ out_mapping;

	mask &= ~GENMASK(chip->g1_irq.nirqs, 0);

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_CTL1, mask);
	अगर (err)
		जाओ out_disable;

	/* Reading the पूर्णांकerrupt status clears (most of) them */
	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_STS, &reg);
	अगर (err)
		जाओ out_disable;

	वापस 0;

out_disable:
	mask &= ~GENMASK(chip->g1_irq.nirqs, 0);
	mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_CTL1, mask);

out_mapping:
	क्रम (irq = 0; irq < 16; irq++) अणु
		virq = irq_find_mapping(chip->g1_irq.करोमुख्य, irq);
		irq_dispose_mapping(virq);
	पूर्ण

	irq_करोमुख्य_हटाओ(chip->g1_irq.करोमुख्य);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_irq_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	अटल काष्ठा lock_class_key lock_key;
	अटल काष्ठा lock_class_key request_key;
	पूर्णांक err;

	err = mv88e6xxx_g1_irq_setup_common(chip);
	अगर (err)
		वापस err;

	/* These lock classes tells lockdep that global 1 irqs are in
	 * a dअगरferent category than their parent GPIO, so it won't
	 * report false recursion.
	 */
	irq_set_lockdep_class(chip->irq, &lock_key, &request_key);

	snम_लिखो(chip->irq_name, माप(chip->irq_name),
		 "mv88e6xxx-%s", dev_name(chip->dev));

	mv88e6xxx_reg_unlock(chip);
	err = request_thपढ़ोed_irq(chip->irq, शून्य,
				   mv88e6xxx_g1_irq_thपढ़ो_fn,
				   IRQF_ONESHOT | IRQF_SHARED,
				   chip->irq_name, chip);
	mv88e6xxx_reg_lock(chip);
	अगर (err)
		mv88e6xxx_g1_irq_मुक्त_common(chip);

	वापस err;
पूर्ण

अटल व्योम mv88e6xxx_irq_poll(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा mv88e6xxx_chip *chip = container_of(work,
						   काष्ठा mv88e6xxx_chip,
						   irq_poll_work.work);
	mv88e6xxx_g1_irq_thपढ़ो_work(chip);

	kthपढ़ो_queue_delayed_work(chip->kworker, &chip->irq_poll_work,
				   msecs_to_jअगरfies(100));
पूर्ण

अटल पूर्णांक mv88e6xxx_irq_poll_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g1_irq_setup_common(chip);
	अगर (err)
		वापस err;

	kthपढ़ो_init_delayed_work(&chip->irq_poll_work,
				  mv88e6xxx_irq_poll);

	chip->kworker = kthपढ़ो_create_worker(0, "%s", dev_name(chip->dev));
	अगर (IS_ERR(chip->kworker))
		वापस PTR_ERR(chip->kworker);

	kthपढ़ो_queue_delayed_work(chip->kworker, &chip->irq_poll_work,
				   msecs_to_jअगरfies(100));

	वापस 0;
पूर्ण

अटल व्योम mv88e6xxx_irq_poll_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
	kthपढ़ो_cancel_delayed_work_sync(&chip->irq_poll_work);
	kthपढ़ो_destroy_worker(chip->kworker);

	mv88e6xxx_reg_lock(chip);
	mv88e6xxx_g1_irq_मुक्त_common(chip);
	mv88e6xxx_reg_unlock(chip);
पूर्ण

अटल पूर्णांक mv88e6xxx_port_config_पूर्णांकerface(काष्ठा mv88e6xxx_chip *chip,
					   पूर्णांक port, phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	पूर्णांक err;

	अगर (chip->info->ops->port_set_rgmii_delay) अणु
		err = chip->info->ops->port_set_rgmii_delay(chip, port,
							    पूर्णांकerface);
		अगर (err && err != -EOPNOTSUPP)
			वापस err;
	पूर्ण

	अगर (chip->info->ops->port_set_cmode) अणु
		err = chip->info->ops->port_set_cmode(chip, port,
						      पूर्णांकerface);
		अगर (err && err != -EOPNOTSUPP)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_setup_mac(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक link, पूर्णांक speed, पूर्णांक duplex, पूर्णांक छोड़ो,
				    phy_पूर्णांकerface_t mode)
अणु
	पूर्णांक err;

	अगर (!chip->info->ops->port_set_link)
		वापस 0;

	/* Port's MAC control must not be changed unless the link is करोwn */
	err = chip->info->ops->port_set_link(chip, port, LINK_FORCED_DOWN);
	अगर (err)
		वापस err;

	अगर (chip->info->ops->port_set_speed_duplex) अणु
		err = chip->info->ops->port_set_speed_duplex(chip, port,
							     speed, duplex);
		अगर (err && err != -EOPNOTSUPP)
			जाओ restore_link;
	पूर्ण

	अगर (speed == SPEED_MAX && chip->info->ops->port_max_speed_mode)
		mode = chip->info->ops->port_max_speed_mode(port);

	अगर (chip->info->ops->port_set_छोड़ो) अणु
		err = chip->info->ops->port_set_छोड़ो(chip, port, छोड़ो);
		अगर (err)
			जाओ restore_link;
	पूर्ण

	err = mv88e6xxx_port_config_पूर्णांकerface(chip, port, mode);
restore_link:
	अगर (chip->info->ops->port_set_link(chip, port, link))
		dev_err(chip->dev, "p%d: failed to restore MAC's link\n", port);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_phy_is_पूर्णांकernal(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;

	वापस port < chip->info->num_पूर्णांकernal_phys;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_ppu_updates(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_STS, &reg);
	अगर (err) अणु
		dev_err(chip->dev,
			"p%d: %s: failed to read port status\n",
			port, __func__);
		वापस err;
	पूर्ण

	वापस !!(reg & MV88E6XXX_PORT_STS_PHY_DETECT);
पूर्ण

अटल पूर्णांक mv88e6xxx_serdes_pcs_get_state(काष्ठा dsa_चयन *ds, पूर्णांक port,
					  काष्ठा phylink_link_state *state)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक lane;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	lane = mv88e6xxx_serdes_get_lane(chip, port);
	अगर (lane >= 0 && chip->info->ops->serdes_pcs_get_state)
		err = chip->info->ops->serdes_pcs_get_state(chip, port, lane,
							    state);
	अन्यथा
		err = -EOPNOTSUPP;
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_serdes_pcs_config(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				       अचिन्हित पूर्णांक mode,
				       phy_पूर्णांकerface_t पूर्णांकerface,
				       स्थिर अचिन्हित दीर्घ *advertise)
अणु
	स्थिर काष्ठा mv88e6xxx_ops *ops = chip->info->ops;
	पूर्णांक lane;

	अगर (ops->serdes_pcs_config) अणु
		lane = mv88e6xxx_serdes_get_lane(chip, port);
		अगर (lane >= 0)
			वापस ops->serdes_pcs_config(chip, port, lane, mode,
						      पूर्णांकerface, advertise);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mv88e6xxx_serdes_pcs_an_restart(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	स्थिर काष्ठा mv88e6xxx_ops *ops;
	पूर्णांक err = 0;
	पूर्णांक lane;

	ops = chip->info->ops;

	अगर (ops->serdes_pcs_an_restart) अणु
		mv88e6xxx_reg_lock(chip);
		lane = mv88e6xxx_serdes_get_lane(chip, port);
		अगर (lane >= 0)
			err = ops->serdes_pcs_an_restart(chip, port, lane);
		mv88e6xxx_reg_unlock(chip);

		अगर (err)
			dev_err(ds->dev, "p%d: failed to restart AN\n", port);
	पूर्ण
पूर्ण

अटल पूर्णांक mv88e6xxx_serdes_pcs_link_up(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					अचिन्हित पूर्णांक mode,
					पूर्णांक speed, पूर्णांक duplex)
अणु
	स्थिर काष्ठा mv88e6xxx_ops *ops = chip->info->ops;
	पूर्णांक lane;

	अगर (!phylink_स्वतःneg_inband(mode) && ops->serdes_pcs_link_up) अणु
		lane = mv88e6xxx_serdes_get_lane(chip, port);
		अगर (lane >= 0)
			वापस ops->serdes_pcs_link_up(chip, port, lane,
						       speed, duplex);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mv88e6065_phylink_validate(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				       अचिन्हित दीर्घ *mask,
				       काष्ठा phylink_link_state *state)
अणु
	अगर (!phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface)) अणु
		/* 10M and 100M are only supported in non-802.3z mode */
		phylink_set(mask, 10baseT_Half);
		phylink_set(mask, 10baseT_Full);
		phylink_set(mask, 100baseT_Half);
		phylink_set(mask, 100baseT_Full);
	पूर्ण
पूर्ण

अटल व्योम mv88e6185_phylink_validate(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				       अचिन्हित दीर्घ *mask,
				       काष्ठा phylink_link_state *state)
अणु
	/* FIXME: अगर the port is in 1000Base-X mode, then it only supports
	 * 1000M FD speeds.  In this हाल, CMODE will indicate 5.
	 */
	phylink_set(mask, 1000baseT_Full);
	phylink_set(mask, 1000baseX_Full);

	mv88e6065_phylink_validate(chip, port, mask, state);
पूर्ण

अटल व्योम mv88e6341_phylink_validate(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				       अचिन्हित दीर्घ *mask,
				       काष्ठा phylink_link_state *state)
अणु
	अगर (port >= 5)
		phylink_set(mask, 2500baseX_Full);

	/* No ethtool bits क्रम 200Mbps */
	phylink_set(mask, 1000baseT_Full);
	phylink_set(mask, 1000baseX_Full);

	mv88e6065_phylink_validate(chip, port, mask, state);
पूर्ण

अटल व्योम mv88e6352_phylink_validate(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				       अचिन्हित दीर्घ *mask,
				       काष्ठा phylink_link_state *state)
अणु
	/* No ethtool bits क्रम 200Mbps */
	phylink_set(mask, 1000baseT_Full);
	phylink_set(mask, 1000baseX_Full);

	mv88e6065_phylink_validate(chip, port, mask, state);
पूर्ण

अटल व्योम mv88e6390_phylink_validate(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				       अचिन्हित दीर्घ *mask,
				       काष्ठा phylink_link_state *state)
अणु
	अगर (port >= 9) अणु
		phylink_set(mask, 2500baseX_Full);
		phylink_set(mask, 2500baseT_Full);
	पूर्ण

	/* No ethtool bits क्रम 200Mbps */
	phylink_set(mask, 1000baseT_Full);
	phylink_set(mask, 1000baseX_Full);

	mv88e6065_phylink_validate(chip, port, mask, state);
पूर्ण

अटल व्योम mv88e6390x_phylink_validate(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					अचिन्हित दीर्घ *mask,
					काष्ठा phylink_link_state *state)
अणु
	अगर (port >= 9) अणु
		phylink_set(mask, 10000baseT_Full);
		phylink_set(mask, 10000baseKR_Full);
	पूर्ण

	mv88e6390_phylink_validate(chip, port, mask, state);
पूर्ण

अटल व्योम mv88e6393x_phylink_validate(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					अचिन्हित दीर्घ *mask,
					काष्ठा phylink_link_state *state)
अणु
	अगर (port == 0 || port == 9 || port == 10) अणु
		phylink_set(mask, 10000baseT_Full);
		phylink_set(mask, 10000baseKR_Full);
		phylink_set(mask, 10000baseCR_Full);
		phylink_set(mask, 10000baseSR_Full);
		phylink_set(mask, 10000baseLR_Full);
		phylink_set(mask, 10000baseLRM_Full);
		phylink_set(mask, 10000baseER_Full);
		phylink_set(mask, 5000baseT_Full);
		phylink_set(mask, 2500baseX_Full);
		phylink_set(mask, 2500baseT_Full);
	पूर्ण

	phylink_set(mask, 1000baseT_Full);
	phylink_set(mask, 1000baseX_Full);

	mv88e6065_phylink_validate(chip, port, mask, state);
पूर्ण

अटल व्योम mv88e6xxx_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       अचिन्हित दीर्घ *supported,
			       काष्ठा phylink_link_state *state)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;
	काष्ठा mv88e6xxx_chip *chip = ds->priv;

	/* Allow all the expected bits */
	phylink_set(mask, Autoneg);
	phylink_set(mask, Pause);
	phylink_set_port_modes(mask);

	अगर (chip->info->ops->phylink_validate)
		chip->info->ops->phylink_validate(chip, port, mask, state);

	biपंचांगap_and(supported, supported, mask, __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);

	/* We can only operate at 2500BaseX or 1000BaseX.  If requested
	 * to advertise both, only report advertising at 2500BaseX.
	 */
	phylink_helper_basex_speed(state);
पूर्ण

अटल व्योम mv88e6xxx_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 अचिन्हित पूर्णांक mode,
				 स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	काष्ठा mv88e6xxx_port *p;
	पूर्णांक err;

	p = &chip->ports[port];

	/* FIXME: is this the correct test? If we're in fixed mode on an
	 * पूर्णांकernal port, why should we process this any dअगरferent from
	 * PHY mode? On the other hand, the port may be स्वतःmedia between
	 * an पूर्णांकernal PHY and the serdes...
	 */
	अगर ((mode == MLO_AN_PHY) && mv88e6xxx_phy_is_पूर्णांकernal(ds, port))
		वापस;

	mv88e6xxx_reg_lock(chip);
	/* In inband mode, the link may come up at any समय जबतक the link
	 * is not क्रमced करोwn. Force the link करोwn जबतक we reconfigure the
	 * पूर्णांकerface mode.
	 */
	अगर (mode == MLO_AN_INBAND && p->पूर्णांकerface != state->पूर्णांकerface &&
	    chip->info->ops->port_set_link)
		chip->info->ops->port_set_link(chip, port, LINK_FORCED_DOWN);

	err = mv88e6xxx_port_config_पूर्णांकerface(chip, port, state->पूर्णांकerface);
	अगर (err && err != -EOPNOTSUPP)
		जाओ err_unlock;

	err = mv88e6xxx_serdes_pcs_config(chip, port, mode, state->पूर्णांकerface,
					  state->advertising);
	/* FIXME: we should restart negotiation अगर something changed - which
	 * is something we get अगर we convert to using phylinks PCS operations.
	 */
	अगर (err > 0)
		err = 0;

	/* Unकरो the क्रमced करोwn state above after completing configuration
	 * irrespective of its state on entry, which allows the link to come up.
	 */
	अगर (mode == MLO_AN_INBAND && p->पूर्णांकerface != state->पूर्णांकerface &&
	    chip->info->ops->port_set_link)
		chip->info->ops->port_set_link(chip, port, LINK_UNFORCED);

	p->पूर्णांकerface = state->पूर्णांकerface;

err_unlock:
	mv88e6xxx_reg_unlock(chip);

	अगर (err && err != -EOPNOTSUPP)
		dev_err(ds->dev, "p%d: failed to configure MAC/PCS\n", port);
पूर्ण

अटल व्योम mv88e6xxx_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    अचिन्हित पूर्णांक mode,
				    phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	स्थिर काष्ठा mv88e6xxx_ops *ops;
	पूर्णांक err = 0;

	ops = chip->info->ops;

	mv88e6xxx_reg_lock(chip);
	अगर ((!mv88e6xxx_port_ppu_updates(chip, port) ||
	     mode == MLO_AN_FIXED) && ops->port_sync_link)
		err = ops->port_sync_link(chip, port, mode, false);
	mv88e6xxx_reg_unlock(chip);

	अगर (err)
		dev_err(chip->dev,
			"p%d: failed to force MAC link down\n", port);
पूर्ण

अटल व्योम mv88e6xxx_mac_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
				  काष्ठा phy_device *phydev,
				  पूर्णांक speed, पूर्णांक duplex,
				  bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	स्थिर काष्ठा mv88e6xxx_ops *ops;
	पूर्णांक err = 0;

	ops = chip->info->ops;

	mv88e6xxx_reg_lock(chip);
	अगर (!mv88e6xxx_port_ppu_updates(chip, port) || mode == MLO_AN_FIXED) अणु
		/* FIXME: क्रम an स्वतःmedia port, should we क्रमce the link
		 * करोwn here - what अगर the link comes up due to "other" media
		 * जबतक we're bringing the port up, how is the exclusivity
		 * handled in the Marvell hardware? E.g. port 2 on 88E6390
		 * shared between पूर्णांकernal PHY and Serdes.
		 */
		err = mv88e6xxx_serdes_pcs_link_up(chip, port, mode, speed,
						   duplex);
		अगर (err)
			जाओ error;

		अगर (ops->port_set_speed_duplex) अणु
			err = ops->port_set_speed_duplex(chip, port,
							 speed, duplex);
			अगर (err && err != -EOPNOTSUPP)
				जाओ error;
		पूर्ण

		अगर (ops->port_sync_link)
			err = ops->port_sync_link(chip, port, mode, true);
	पूर्ण
error:
	mv88e6xxx_reg_unlock(chip);

	अगर (err && err != -EOPNOTSUPP)
		dev_err(ds->dev,
			"p%d: failed to configure MAC link up\n", port);
पूर्ण

अटल पूर्णांक mv88e6xxx_stats_snapshot(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	अगर (!chip->info->ops->stats_snapshot)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->stats_snapshot(chip, port);
पूर्ण

अटल काष्ठा mv88e6xxx_hw_stat mv88e6xxx_hw_stats[] = अणु
	अणु "in_good_octets",		8, 0x00, STATS_TYPE_BANK0, पूर्ण,
	अणु "in_bad_octets",		4, 0x02, STATS_TYPE_BANK0, पूर्ण,
	अणु "in_unicast",			4, 0x04, STATS_TYPE_BANK0, पूर्ण,
	अणु "in_broadcasts",		4, 0x06, STATS_TYPE_BANK0, पूर्ण,
	अणु "in_multicasts",		4, 0x07, STATS_TYPE_BANK0, पूर्ण,
	अणु "in_pause",			4, 0x16, STATS_TYPE_BANK0, पूर्ण,
	अणु "in_undersize",		4, 0x18, STATS_TYPE_BANK0, पूर्ण,
	अणु "in_fragments",		4, 0x19, STATS_TYPE_BANK0, पूर्ण,
	अणु "in_oversize",		4, 0x1a, STATS_TYPE_BANK0, पूर्ण,
	अणु "in_jabber",			4, 0x1b, STATS_TYPE_BANK0, पूर्ण,
	अणु "in_rx_error",		4, 0x1c, STATS_TYPE_BANK0, पूर्ण,
	अणु "in_fcs_error",		4, 0x1d, STATS_TYPE_BANK0, पूर्ण,
	अणु "out_octets",			8, 0x0e, STATS_TYPE_BANK0, पूर्ण,
	अणु "out_unicast",		4, 0x10, STATS_TYPE_BANK0, पूर्ण,
	अणु "out_broadcasts",		4, 0x13, STATS_TYPE_BANK0, पूर्ण,
	अणु "out_multicasts",		4, 0x12, STATS_TYPE_BANK0, पूर्ण,
	अणु "out_pause",			4, 0x15, STATS_TYPE_BANK0, पूर्ण,
	अणु "excessive",			4, 0x11, STATS_TYPE_BANK0, पूर्ण,
	अणु "collisions",			4, 0x1e, STATS_TYPE_BANK0, पूर्ण,
	अणु "deferred",			4, 0x05, STATS_TYPE_BANK0, पूर्ण,
	अणु "single",			4, 0x14, STATS_TYPE_BANK0, पूर्ण,
	अणु "multiple",			4, 0x17, STATS_TYPE_BANK0, पूर्ण,
	अणु "out_fcs_error",		4, 0x03, STATS_TYPE_BANK0, पूर्ण,
	अणु "late",			4, 0x1f, STATS_TYPE_BANK0, पूर्ण,
	अणु "hist_64bytes",		4, 0x08, STATS_TYPE_BANK0, पूर्ण,
	अणु "hist_65_127bytes",		4, 0x09, STATS_TYPE_BANK0, पूर्ण,
	अणु "hist_128_255bytes",		4, 0x0a, STATS_TYPE_BANK0, पूर्ण,
	अणु "hist_256_511bytes",		4, 0x0b, STATS_TYPE_BANK0, पूर्ण,
	अणु "hist_512_1023bytes",		4, 0x0c, STATS_TYPE_BANK0, पूर्ण,
	अणु "hist_1024_max_bytes",	4, 0x0d, STATS_TYPE_BANK0, पूर्ण,
	अणु "sw_in_discards",		4, 0x10, STATS_TYPE_PORT, पूर्ण,
	अणु "sw_in_filtered",		2, 0x12, STATS_TYPE_PORT, पूर्ण,
	अणु "sw_out_filtered",		2, 0x13, STATS_TYPE_PORT, पूर्ण,
	अणु "in_discards",		4, 0x00, STATS_TYPE_BANK1, पूर्ण,
	अणु "in_filtered",		4, 0x01, STATS_TYPE_BANK1, पूर्ण,
	अणु "in_accepted",		4, 0x02, STATS_TYPE_BANK1, पूर्ण,
	अणु "in_bad_accepted",		4, 0x03, STATS_TYPE_BANK1, पूर्ण,
	अणु "in_good_avb_class_a",	4, 0x04, STATS_TYPE_BANK1, पूर्ण,
	अणु "in_good_avb_class_b",	4, 0x05, STATS_TYPE_BANK1, पूर्ण,
	अणु "in_bad_avb_class_a",		4, 0x06, STATS_TYPE_BANK1, पूर्ण,
	अणु "in_bad_avb_class_b",		4, 0x07, STATS_TYPE_BANK1, पूर्ण,
	अणु "tcam_counter_0",		4, 0x08, STATS_TYPE_BANK1, पूर्ण,
	अणु "tcam_counter_1",		4, 0x09, STATS_TYPE_BANK1, पूर्ण,
	अणु "tcam_counter_2",		4, 0x0a, STATS_TYPE_BANK1, पूर्ण,
	अणु "tcam_counter_3",		4, 0x0b, STATS_TYPE_BANK1, पूर्ण,
	अणु "in_da_unknown",		4, 0x0e, STATS_TYPE_BANK1, पूर्ण,
	अणु "in_management",		4, 0x0f, STATS_TYPE_BANK1, पूर्ण,
	अणु "out_queue_0",		4, 0x10, STATS_TYPE_BANK1, पूर्ण,
	अणु "out_queue_1",		4, 0x11, STATS_TYPE_BANK1, पूर्ण,
	अणु "out_queue_2",		4, 0x12, STATS_TYPE_BANK1, पूर्ण,
	अणु "out_queue_3",		4, 0x13, STATS_TYPE_BANK1, पूर्ण,
	अणु "out_queue_4",		4, 0x14, STATS_TYPE_BANK1, पूर्ण,
	अणु "out_queue_5",		4, 0x15, STATS_TYPE_BANK1, पूर्ण,
	अणु "out_queue_6",		4, 0x16, STATS_TYPE_BANK1, पूर्ण,
	अणु "out_queue_7",		4, 0x17, STATS_TYPE_BANK1, पूर्ण,
	अणु "out_cut_through",		4, 0x18, STATS_TYPE_BANK1, पूर्ण,
	अणु "out_octets_a",		4, 0x1a, STATS_TYPE_BANK1, पूर्ण,
	अणु "out_octets_b",		4, 0x1b, STATS_TYPE_BANK1, पूर्ण,
	अणु "out_management",		4, 0x1f, STATS_TYPE_BANK1, पूर्ण,
पूर्ण;

अटल uपूर्णांक64_t _mv88e6xxx_get_ethtool_stat(काष्ठा mv88e6xxx_chip *chip,
					    काष्ठा mv88e6xxx_hw_stat *s,
					    पूर्णांक port, u16 bank1_select,
					    u16 histogram)
अणु
	u32 low;
	u32 high = 0;
	u16 reg = 0;
	पूर्णांक err;
	u64 value;

	चयन (s->type) अणु
	हाल STATS_TYPE_PORT:
		err = mv88e6xxx_port_पढ़ो(chip, port, s->reg, &reg);
		अगर (err)
			वापस U64_MAX;

		low = reg;
		अगर (s->size == 4) अणु
			err = mv88e6xxx_port_पढ़ो(chip, port, s->reg + 1, &reg);
			अगर (err)
				वापस U64_MAX;
			low |= ((u32)reg) << 16;
		पूर्ण
		अवरोध;
	हाल STATS_TYPE_BANK1:
		reg = bank1_select;
		fallthrough;
	हाल STATS_TYPE_BANK0:
		reg |= s->reg | histogram;
		mv88e6xxx_g1_stats_पढ़ो(chip, reg, &low);
		अगर (s->size == 8)
			mv88e6xxx_g1_stats_पढ़ो(chip, reg + 1, &high);
		अवरोध;
	शेष:
		वापस U64_MAX;
	पूर्ण
	value = (((u64)high) << 32) | low;
	वापस value;
पूर्ण

अटल पूर्णांक mv88e6xxx_stats_get_strings(काष्ठा mv88e6xxx_chip *chip,
				       uपूर्णांक8_t *data, पूर्णांक types)
अणु
	काष्ठा mv88e6xxx_hw_stat *stat;
	पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < ARRAY_SIZE(mv88e6xxx_hw_stats); i++) अणु
		stat = &mv88e6xxx_hw_stats[i];
		अगर (stat->type & types) अणु
			स_नकल(data + j * ETH_GSTRING_LEN, stat->string,
			       ETH_GSTRING_LEN);
			j++;
		पूर्ण
	पूर्ण

	वापस j;
पूर्ण

अटल पूर्णांक mv88e6095_stats_get_strings(काष्ठा mv88e6xxx_chip *chip,
				       uपूर्णांक8_t *data)
अणु
	वापस mv88e6xxx_stats_get_strings(chip, data,
					   STATS_TYPE_BANK0 | STATS_TYPE_PORT);
पूर्ण

अटल पूर्णांक mv88e6250_stats_get_strings(काष्ठा mv88e6xxx_chip *chip,
				       uपूर्णांक8_t *data)
अणु
	वापस mv88e6xxx_stats_get_strings(chip, data, STATS_TYPE_BANK0);
पूर्ण

अटल पूर्णांक mv88e6320_stats_get_strings(काष्ठा mv88e6xxx_chip *chip,
				       uपूर्णांक8_t *data)
अणु
	वापस mv88e6xxx_stats_get_strings(chip, data,
					   STATS_TYPE_BANK0 | STATS_TYPE_BANK1);
पूर्ण

अटल स्थिर uपूर्णांक8_t *mv88e6xxx_atu_vtu_stats_strings[] = अणु
	"atu_member_violation",
	"atu_miss_violation",
	"atu_full_violation",
	"vtu_member_violation",
	"vtu_miss_violation",
पूर्ण;

अटल व्योम mv88e6xxx_atu_vtu_get_strings(uपूर्णांक8_t *data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mv88e6xxx_atu_vtu_stats_strings); i++)
		strlcpy(data + i * ETH_GSTRING_LEN,
			mv88e6xxx_atu_vtu_stats_strings[i],
			ETH_GSTRING_LEN);
पूर्ण

अटल व्योम mv88e6xxx_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  u32 stringset, uपूर्णांक8_t *data)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक count = 0;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	mv88e6xxx_reg_lock(chip);

	अगर (chip->info->ops->stats_get_strings)
		count = chip->info->ops->stats_get_strings(chip, data);

	अगर (chip->info->ops->serdes_get_strings) अणु
		data += count * ETH_GSTRING_LEN;
		count = chip->info->ops->serdes_get_strings(chip, port, data);
	पूर्ण

	data += count * ETH_GSTRING_LEN;
	mv88e6xxx_atu_vtu_get_strings(data);

	mv88e6xxx_reg_unlock(chip);
पूर्ण

अटल पूर्णांक mv88e6xxx_stats_get_sset_count(काष्ठा mv88e6xxx_chip *chip,
					  पूर्णांक types)
अणु
	काष्ठा mv88e6xxx_hw_stat *stat;
	पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < ARRAY_SIZE(mv88e6xxx_hw_stats); i++) अणु
		stat = &mv88e6xxx_hw_stats[i];
		अगर (stat->type & types)
			j++;
	पूर्ण
	वापस j;
पूर्ण

अटल पूर्णांक mv88e6095_stats_get_sset_count(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_stats_get_sset_count(chip, STATS_TYPE_BANK0 |
					      STATS_TYPE_PORT);
पूर्ण

अटल पूर्णांक mv88e6250_stats_get_sset_count(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_stats_get_sset_count(chip, STATS_TYPE_BANK0);
पूर्ण

अटल पूर्णांक mv88e6320_stats_get_sset_count(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस mv88e6xxx_stats_get_sset_count(chip, STATS_TYPE_BANK0 |
					      STATS_TYPE_BANK1);
पूर्ण

अटल पूर्णांक mv88e6xxx_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक serdes_count = 0;
	पूर्णांक count = 0;

	अगर (sset != ETH_SS_STATS)
		वापस 0;

	mv88e6xxx_reg_lock(chip);
	अगर (chip->info->ops->stats_get_sset_count)
		count = chip->info->ops->stats_get_sset_count(chip);
	अगर (count < 0)
		जाओ out;

	अगर (chip->info->ops->serdes_get_sset_count)
		serdes_count = chip->info->ops->serdes_get_sset_count(chip,
								      port);
	अगर (serdes_count < 0) अणु
		count = serdes_count;
		जाओ out;
	पूर्ण
	count += serdes_count;
	count += ARRAY_SIZE(mv88e6xxx_atu_vtu_stats_strings);

out:
	mv88e6xxx_reg_unlock(chip);

	वापस count;
पूर्ण

अटल पूर्णांक mv88e6xxx_stats_get_stats(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     uपूर्णांक64_t *data, पूर्णांक types,
				     u16 bank1_select, u16 histogram)
अणु
	काष्ठा mv88e6xxx_hw_stat *stat;
	पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < ARRAY_SIZE(mv88e6xxx_hw_stats); i++) अणु
		stat = &mv88e6xxx_hw_stats[i];
		अगर (stat->type & types) अणु
			mv88e6xxx_reg_lock(chip);
			data[j] = _mv88e6xxx_get_ethtool_stat(chip, stat, port,
							      bank1_select,
							      histogram);
			mv88e6xxx_reg_unlock(chip);

			j++;
		पूर्ण
	पूर्ण
	वापस j;
पूर्ण

अटल पूर्णांक mv88e6095_stats_get_stats(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     uपूर्णांक64_t *data)
अणु
	वापस mv88e6xxx_stats_get_stats(chip, port, data,
					 STATS_TYPE_BANK0 | STATS_TYPE_PORT,
					 0, MV88E6XXX_G1_STATS_OP_HIST_RX_TX);
पूर्ण

अटल पूर्णांक mv88e6250_stats_get_stats(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     uपूर्णांक64_t *data)
अणु
	वापस mv88e6xxx_stats_get_stats(chip, port, data, STATS_TYPE_BANK0,
					 0, MV88E6XXX_G1_STATS_OP_HIST_RX_TX);
पूर्ण

अटल पूर्णांक mv88e6320_stats_get_stats(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     uपूर्णांक64_t *data)
अणु
	वापस mv88e6xxx_stats_get_stats(chip, port, data,
					 STATS_TYPE_BANK0 | STATS_TYPE_BANK1,
					 MV88E6XXX_G1_STATS_OP_BANK_1_BIT_9,
					 MV88E6XXX_G1_STATS_OP_HIST_RX_TX);
पूर्ण

अटल पूर्णांक mv88e6390_stats_get_stats(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     uपूर्णांक64_t *data)
अणु
	वापस mv88e6xxx_stats_get_stats(chip, port, data,
					 STATS_TYPE_BANK0 | STATS_TYPE_BANK1,
					 MV88E6XXX_G1_STATS_OP_BANK_1_BIT_10,
					 0);
पूर्ण

अटल व्योम mv88e6xxx_atu_vtu_get_stats(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					uपूर्णांक64_t *data)
अणु
	*data++ = chip->ports[port].atu_member_violation;
	*data++ = chip->ports[port].atu_miss_violation;
	*data++ = chip->ports[port].atu_full_violation;
	*data++ = chip->ports[port].vtu_member_violation;
	*data++ = chip->ports[port].vtu_miss_violation;
पूर्ण

अटल व्योम mv88e6xxx_get_stats(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				uपूर्णांक64_t *data)
अणु
	पूर्णांक count = 0;

	अगर (chip->info->ops->stats_get_stats)
		count = chip->info->ops->stats_get_stats(chip, port, data);

	mv88e6xxx_reg_lock(chip);
	अगर (chip->info->ops->serdes_get_stats) अणु
		data += count;
		count = chip->info->ops->serdes_get_stats(chip, port, data);
	पूर्ण
	data += count;
	mv88e6xxx_atu_vtu_get_stats(chip, port, data);
	mv88e6xxx_reg_unlock(chip);
पूर्ण

अटल व्योम mv88e6xxx_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
					uपूर्णांक64_t *data)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक ret;

	mv88e6xxx_reg_lock(chip);

	ret = mv88e6xxx_stats_snapshot(chip, port);
	mv88e6xxx_reg_unlock(chip);

	अगर (ret < 0)
		वापस;

	mv88e6xxx_get_stats(chip, port, data);

पूर्ण

अटल पूर्णांक mv88e6xxx_get_regs_len(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक len;

	len = 32 * माप(u16);
	अगर (chip->info->ops->serdes_get_regs_len)
		len += chip->info->ops->serdes_get_regs_len(chip, port);

	वापस len;
पूर्ण

अटल व्योम mv88e6xxx_get_regs(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा ethtool_regs *regs, व्योम *_p)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;
	u16 reg;
	u16 *p = _p;
	पूर्णांक i;

	regs->version = chip->info->prod_num;

	स_रखो(p, 0xff, 32 * माप(u16));

	mv88e6xxx_reg_lock(chip);

	क्रम (i = 0; i < 32; i++) अणु

		err = mv88e6xxx_port_पढ़ो(chip, port, i, &reg);
		अगर (!err)
			p[i] = reg;
	पूर्ण

	अगर (chip->info->ops->serdes_get_regs)
		chip->info->ops->serdes_get_regs(chip, port, &p[i]);

	mv88e6xxx_reg_unlock(chip);
पूर्ण

अटल पूर्णांक mv88e6xxx_get_mac_eee(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा ethtool_eee *e)
अणु
	/* Nothing to करो on the port's MAC */
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_set_mac_eee(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा ethtool_eee *e)
अणु
	/* Nothing to करो on the port's MAC */
	वापस 0;
पूर्ण

/* Mask of the local ports allowed to receive frames from a given fabric port */
अटल u16 mv88e6xxx_port_vlan(काष्ठा mv88e6xxx_chip *chip, पूर्णांक dev, पूर्णांक port)
अणु
	काष्ठा dsa_चयन *ds = chip->ds;
	काष्ठा dsa_चयन_tree *dst = ds->dst;
	काष्ठा net_device *br;
	काष्ठा dsa_port *dp;
	bool found = false;
	u16 pvlan;

	list_क्रम_each_entry(dp, &dst->ports, list) अणु
		अगर (dp->ds->index == dev && dp->index == port) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Prevent frames from unknown चयन or port */
	अगर (!found)
		वापस 0;

	/* Frames from DSA links and CPU ports can egress any local port */
	अगर (dp->type == DSA_PORT_TYPE_CPU || dp->type == DSA_PORT_TYPE_DSA)
		वापस mv88e6xxx_port_mask(chip);

	br = dp->bridge_dev;
	pvlan = 0;

	/* Frames from user ports can egress any local DSA links and CPU ports,
	 * as well as any local member of their bridge group.
	 */
	list_क्रम_each_entry(dp, &dst->ports, list)
		अगर (dp->ds == ds &&
		    (dp->type == DSA_PORT_TYPE_CPU ||
		     dp->type == DSA_PORT_TYPE_DSA ||
		     (br && dp->bridge_dev == br)))
			pvlan |= BIT(dp->index);

	वापस pvlan;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_vlan_map(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	u16 output_ports = mv88e6xxx_port_vlan(chip, chip->ds->index, port);

	/* prevent frames from going back out of the port they came in on */
	output_ports &= ~BIT(port);

	वापस mv88e6xxx_port_set_vlan_map(chip, port, output_ports);
पूर्ण

अटल व्योम mv88e6xxx_port_stp_state_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
					 u8 state)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_set_state(chip, port, state);
	mv88e6xxx_reg_unlock(chip);

	अगर (err)
		dev_err(ds->dev, "p%d: failed to update state\n", port);
पूर्ण

अटल पूर्णांक mv88e6xxx_pri_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	अगर (chip->info->ops->ieee_pri_map) अणु
		err = chip->info->ops->ieee_pri_map(chip);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (chip->info->ops->ip_pri_map) अणु
		err = chip->info->ops->ip_pri_map(chip);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_devmap_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	काष्ठा dsa_चयन *ds = chip->ds;
	पूर्णांक target, port;
	पूर्णांक err;

	अगर (!chip->info->global2_addr)
		वापस 0;

	/* Initialize the routing port to the 32 possible target devices */
	क्रम (target = 0; target < 32; target++) अणु
		port = dsa_routing_port(ds, target);
		अगर (port == ds->num_ports)
			port = 0x1f;

		err = mv88e6xxx_g2_device_mapping_ग_लिखो(chip, target, port);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (chip->info->ops->set_cascade_port) अणु
		port = MV88E6XXX_CASCADE_PORT_MULTIPLE;
		err = chip->info->ops->set_cascade_port(chip, port);
		अगर (err)
			वापस err;
	पूर्ण

	err = mv88e6xxx_g1_set_device_number(chip, chip->ds->index);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_trunk_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	/* Clear all trunk masks and mapping */
	अगर (chip->info->global2_addr)
		वापस mv88e6xxx_g2_trunk_clear(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_rmu_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	अगर (chip->info->ops->rmu_disable)
		वापस chip->info->ops->rmu_disable(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_pot_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	अगर (chip->info->ops->pot_clear)
		वापस chip->info->ops->pot_clear(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_rsvd2cpu_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	अगर (chip->info->ops->mgmt_rsvd2cpu)
		वापस chip->info->ops->mgmt_rsvd2cpu(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_atu_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g1_atu_flush(chip, 0, true);
	अगर (err)
		वापस err;

	/* The chips that have a "learn2all" bit in Global1, ATU
	 * Control are precisely those whose port रेजिस्टरs have a
	 * Message Port bit in Port Control 1 and hence implement
	 * ->port_setup_message_port.
	 */
	अगर (chip->info->ops->port_setup_message_port) अणु
		err = mv88e6xxx_g1_atu_set_learn2all(chip, true);
		अगर (err)
			वापस err;
	पूर्ण

	वापस mv88e6xxx_g1_atu_set_age_समय(chip, 300000);
पूर्ण

अटल पूर्णांक mv88e6xxx_irl_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक port;
	पूर्णांक err;

	अगर (!chip->info->ops->irl_init_all)
		वापस 0;

	क्रम (port = 0; port < mv88e6xxx_num_ports(chip); port++) अणु
		/* Disable ingress rate limiting by resetting all per port
		 * ingress rate limit resources to their initial state.
		 */
		err = chip->info->ops->irl_init_all(chip, port);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_mac_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	अगर (chip->info->ops->set_चयन_mac) अणु
		u8 addr[ETH_ALEN];

		eth_अक्रमom_addr(addr);

		वापस chip->info->ops->set_चयन_mac(chip, addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_pvt_map(काष्ठा mv88e6xxx_chip *chip, पूर्णांक dev, पूर्णांक port)
अणु
	काष्ठा dsa_चयन_tree *dst = chip->ds->dst;
	काष्ठा dsa_चयन *ds;
	काष्ठा dsa_port *dp;
	u16 pvlan = 0;

	अगर (!mv88e6xxx_has_pvt(chip))
		वापस 0;

	/* Skip the local source device, which uses in-chip port VLAN */
	अगर (dev != chip->ds->index) अणु
		pvlan = mv88e6xxx_port_vlan(chip, dev, port);

		ds = dsa_चयन_find(dst->index, dev);
		dp = ds ? dsa_to_port(ds, port) : शून्य;
		अगर (dp && dp->lag_dev) अणु
			/* As the PVT is used to limit flooding of
			 * FORWARD frames, which use the LAG ID as the
			 * source port, we must translate dev/port to
			 * the special "LAG device" in the PVT, using
			 * the LAG ID as the port number.
			 */
			dev = MV88E6XXX_G2_PVT_ADDR_DEV_TRUNK;
			port = dsa_lag_id(dst, dp->lag_dev);
		पूर्ण
	पूर्ण

	वापस mv88e6xxx_g2_pvt_ग_लिखो(chip, dev, port, pvlan);
पूर्ण

अटल पूर्णांक mv88e6xxx_pvt_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक dev, port;
	पूर्णांक err;

	अगर (!mv88e6xxx_has_pvt(chip))
		वापस 0;

	/* Clear 5 Bit Port क्रम usage with Marvell Link Street devices:
	 * use 4 bits क्रम the Src_Port/Src_Trunk and 5 bits क्रम the Src_Dev.
	 */
	err = mv88e6xxx_g2_misc_4_bit_port(chip);
	अगर (err)
		वापस err;

	क्रम (dev = 0; dev < MV88E6XXX_MAX_PVT_SWITCHES; ++dev) अणु
		क्रम (port = 0; port < MV88E6XXX_MAX_PVT_PORTS; ++port) अणु
			err = mv88e6xxx_pvt_map(chip, dev, port);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mv88e6xxx_port_fast_age(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	अगर (dsa_to_port(ds, port)->lag_dev)
		/* Hardware is incapable of fast-aging a LAG through a
		 * regular ATU move operation. Until we have something
		 * more fancy in place this is a no-op.
		 */
		वापस;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_g1_atu_हटाओ(chip, 0, port, false);
	mv88e6xxx_reg_unlock(chip);

	अगर (err)
		dev_err(ds->dev, "p%d: failed to flush ATU\n", port);
पूर्ण

अटल पूर्णांक mv88e6xxx_vtu_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	अगर (!mv88e6xxx_max_vid(chip))
		वापस 0;

	वापस mv88e6xxx_g1_vtu_flush(chip);
पूर्ण

अटल पूर्णांक mv88e6xxx_vtu_get(काष्ठा mv88e6xxx_chip *chip, u16 vid,
			     काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	पूर्णांक err;

	अगर (!chip->info->ops->vtu_getnext)
		वापस -EOPNOTSUPP;

	entry->vid = vid ? vid - 1 : mv88e6xxx_max_vid(chip);
	entry->valid = false;

	err = chip->info->ops->vtu_getnext(chip, entry);

	अगर (entry->vid != vid)
		entry->valid = false;

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_vtu_walk(काष्ठा mv88e6xxx_chip *chip,
			      पूर्णांक (*cb)(काष्ठा mv88e6xxx_chip *chip,
					स्थिर काष्ठा mv88e6xxx_vtu_entry *entry,
					व्योम *priv),
			      व्योम *priv)
अणु
	काष्ठा mv88e6xxx_vtu_entry entry = अणु
		.vid = mv88e6xxx_max_vid(chip),
		.valid = false,
	पूर्ण;
	पूर्णांक err;

	अगर (!chip->info->ops->vtu_getnext)
		वापस -EOPNOTSUPP;

	करो अणु
		err = chip->info->ops->vtu_getnext(chip, &entry);
		अगर (err)
			वापस err;

		अगर (!entry.valid)
			अवरोध;

		err = cb(chip, &entry, priv);
		अगर (err)
			वापस err;
	पूर्ण जबतक (entry.vid < mv88e6xxx_max_vid(chip));

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_vtu_loadpurge(काष्ठा mv88e6xxx_chip *chip,
				   काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	अगर (!chip->info->ops->vtu_loadpurge)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->vtu_loadpurge(chip, entry);
पूर्ण

अटल पूर्णांक mv88e6xxx_fid_map_vlan(काष्ठा mv88e6xxx_chip *chip,
				  स्थिर काष्ठा mv88e6xxx_vtu_entry *entry,
				  व्योम *_fid_biपंचांगap)
अणु
	अचिन्हित दीर्घ *fid_biपंचांगap = _fid_biपंचांगap;

	set_bit(entry->fid, fid_biपंचांगap);
	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_fid_map(काष्ठा mv88e6xxx_chip *chip, अचिन्हित दीर्घ *fid_biपंचांगap)
अणु
	पूर्णांक i, err;
	u16 fid;

	biपंचांगap_zero(fid_biपंचांगap, MV88E6XXX_N_FID);

	/* Set every FID bit used by the (un)bridged ports */
	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); ++i) अणु
		err = mv88e6xxx_port_get_fid(chip, i, &fid);
		अगर (err)
			वापस err;

		set_bit(fid, fid_biपंचांगap);
	पूर्ण

	/* Set every FID bit used by the VLAN entries */
	वापस mv88e6xxx_vtu_walk(chip, mv88e6xxx_fid_map_vlan, fid_biपंचांगap);
पूर्ण

अटल पूर्णांक mv88e6xxx_atu_new(काष्ठा mv88e6xxx_chip *chip, u16 *fid)
अणु
	DECLARE_BITMAP(fid_biपंचांगap, MV88E6XXX_N_FID);
	पूर्णांक err;

	err = mv88e6xxx_fid_map(chip, fid_biपंचांगap);
	अगर (err)
		वापस err;

	/* The reset value 0x000 is used to indicate that multiple address
	 * databases are not needed. Return the next positive available.
	 */
	*fid = find_next_zero_bit(fid_biपंचांगap, MV88E6XXX_N_FID, 1);
	अगर (unlikely(*fid >= mv88e6xxx_num_databases(chip)))
		वापस -ENOSPC;

	/* Clear the database */
	वापस mv88e6xxx_g1_atu_flush(chip, *fid, true);
पूर्ण

अटल पूर्णांक mv88e6xxx_port_check_hw_vlan(काष्ठा dsa_चयन *ds, पूर्णांक port,
					u16 vid)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	काष्ठा mv88e6xxx_vtu_entry vlan;
	पूर्णांक i, err;

	अगर (!vid)
		वापस -EOPNOTSUPP;

	/* DSA and CPU ports have to be members of multiple vlans */
	अगर (dsa_is_dsa_port(ds, port) || dsa_is_cpu_port(ds, port))
		वापस 0;

	err = mv88e6xxx_vtu_get(chip, vid, &vlan);
	अगर (err)
		वापस err;

	अगर (!vlan.valid)
		वापस 0;

	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); ++i) अणु
		अगर (dsa_is_dsa_port(ds, i) || dsa_is_cpu_port(ds, i))
			जारी;

		अगर (!dsa_to_port(ds, i)->slave)
			जारी;

		अगर (vlan.member[i] ==
		    MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_NON_MEMBER)
			जारी;

		अगर (dsa_to_port(ds, i)->bridge_dev ==
		    dsa_to_port(ds, port)->bridge_dev)
			अवरोध; /* same bridge, check next VLAN */

		अगर (!dsa_to_port(ds, i)->bridge_dev)
			जारी;

		dev_err(ds->dev, "p%d: hw VLAN %d already used by port %d in %s\n",
			port, vlan.vid, i,
			netdev_name(dsa_to_port(ds, i)->bridge_dev));
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port,
					 bool vlan_filtering,
					 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	u16 mode = vlan_filtering ? MV88E6XXX_PORT_CTL2_8021Q_MODE_SECURE :
		MV88E6XXX_PORT_CTL2_8021Q_MODE_DISABLED;
	पूर्णांक err;

	अगर (!mv88e6xxx_max_vid(chip))
		वापस -EOPNOTSUPP;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_set_8021q_mode(chip, port, mode);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक
mv88e6xxx_port_vlan_prepare(काष्ठा dsa_चयन *ds, पूर्णांक port,
			    स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	अगर (!mv88e6xxx_max_vid(chip))
		वापस -EOPNOTSUPP;

	/* If the requested port करोesn't beदीर्घ to the same bridge as the VLAN
	 * members, करो not support it (yet) and fallback to software VLAN.
	 */
	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_check_hw_vlan(ds, port, vlan->vid);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_db_load_purge(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					स्थिर अचिन्हित अक्षर *addr, u16 vid,
					u8 state)
अणु
	काष्ठा mv88e6xxx_atu_entry entry;
	काष्ठा mv88e6xxx_vtu_entry vlan;
	u16 fid;
	पूर्णांक err;

	/* Null VLAN ID corresponds to the port निजी database */
	अगर (vid == 0) अणु
		err = mv88e6xxx_port_get_fid(chip, port, &fid);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		err = mv88e6xxx_vtu_get(chip, vid, &vlan);
		अगर (err)
			वापस err;

		/* चयनdev expects -EOPNOTSUPP to honor software VLANs */
		अगर (!vlan.valid)
			वापस -EOPNOTSUPP;

		fid = vlan.fid;
	पूर्ण

	entry.state = 0;
	ether_addr_copy(entry.mac, addr);
	eth_addr_dec(entry.mac);

	err = mv88e6xxx_g1_atu_getnext(chip, fid, &entry);
	अगर (err)
		वापस err;

	/* Initialize a fresh ATU entry अगर it isn't found */
	अगर (!entry.state || !ether_addr_equal(entry.mac, addr)) अणु
		स_रखो(&entry, 0, माप(entry));
		ether_addr_copy(entry.mac, addr);
	पूर्ण

	/* Purge the ATU entry only अगर no port is using it anymore */
	अगर (!state) अणु
		entry.portvec &= ~BIT(port);
		अगर (!entry.portvec)
			entry.state = 0;
	पूर्ण अन्यथा अणु
		अगर (state == MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC)
			entry.portvec = BIT(port);
		अन्यथा
			entry.portvec |= BIT(port);

		entry.state = state;
	पूर्ण

	वापस mv88e6xxx_g1_atu_loadpurge(chip, fid, &entry);
पूर्ण

अटल पूर्णांक mv88e6xxx_policy_apply(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  स्थिर काष्ठा mv88e6xxx_policy *policy)
अणु
	क्रमागत mv88e6xxx_policy_mapping mapping = policy->mapping;
	क्रमागत mv88e6xxx_policy_action action = policy->action;
	स्थिर u8 *addr = policy->addr;
	u16 vid = policy->vid;
	u8 state;
	पूर्णांक err;
	पूर्णांक id;

	अगर (!chip->info->ops->port_set_policy)
		वापस -EOPNOTSUPP;

	चयन (mapping) अणु
	हाल MV88E6XXX_POLICY_MAPPING_DA:
	हाल MV88E6XXX_POLICY_MAPPING_SA:
		अगर (action == MV88E6XXX_POLICY_ACTION_NORMAL)
			state = 0; /* Dissociate the port and address */
		अन्यथा अगर (action == MV88E6XXX_POLICY_ACTION_DISCARD &&
			 is_multicast_ether_addr(addr))
			state = MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_POLICY;
		अन्यथा अगर (action == MV88E6XXX_POLICY_ACTION_DISCARD &&
			 is_unicast_ether_addr(addr))
			state = MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_POLICY;
		अन्यथा
			वापस -EOPNOTSUPP;

		err = mv88e6xxx_port_db_load_purge(chip, port, addr, vid,
						   state);
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Skip the port's policy clearing अगर the mapping is still in use */
	अगर (action == MV88E6XXX_POLICY_ACTION_NORMAL)
		idr_क्रम_each_entry(&chip->policies, policy, id)
			अगर (policy->port == port &&
			    policy->mapping == mapping &&
			    policy->action != action)
				वापस 0;

	वापस chip->info->ops->port_set_policy(chip, port, mapping, action);
पूर्ण

अटल पूर्णांक mv88e6xxx_policy_insert(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethhdr *mac_entry = &fs->h_u.ether_spec;
	काष्ठा ethhdr *mac_mask = &fs->m_u.ether_spec;
	क्रमागत mv88e6xxx_policy_mapping mapping;
	क्रमागत mv88e6xxx_policy_action action;
	काष्ठा mv88e6xxx_policy *policy;
	u16 vid = 0;
	u8 *addr;
	पूर्णांक err;
	पूर्णांक id;

	अगर (fs->location != RX_CLS_LOC_ANY)
		वापस -EINVAL;

	अगर (fs->ring_cookie == RX_CLS_FLOW_DISC)
		action = MV88E6XXX_POLICY_ACTION_DISCARD;
	अन्यथा
		वापस -EOPNOTSUPP;

	चयन (fs->flow_type & ~FLOW_EXT) अणु
	हाल ETHER_FLOW:
		अगर (!is_zero_ether_addr(mac_mask->h_dest) &&
		    is_zero_ether_addr(mac_mask->h_source)) अणु
			mapping = MV88E6XXX_POLICY_MAPPING_DA;
			addr = mac_entry->h_dest;
		पूर्ण अन्यथा अगर (is_zero_ether_addr(mac_mask->h_dest) &&
		    !is_zero_ether_addr(mac_mask->h_source)) अणु
			mapping = MV88E6XXX_POLICY_MAPPING_SA;
			addr = mac_entry->h_source;
		पूर्ण अन्यथा अणु
			/* Cannot support DA and SA mapping in the same rule */
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((fs->flow_type & FLOW_EXT) && fs->m_ext.vlan_tci) अणु
		अगर (fs->m_ext.vlan_tci != htons(0xffff))
			वापस -EOPNOTSUPP;
		vid = be16_to_cpu(fs->h_ext.vlan_tci) & VLAN_VID_MASK;
	पूर्ण

	idr_क्रम_each_entry(&chip->policies, policy, id) अणु
		अगर (policy->port == port && policy->mapping == mapping &&
		    policy->action == action && policy->vid == vid &&
		    ether_addr_equal(policy->addr, addr))
			वापस -EEXIST;
	पूर्ण

	policy = devm_kzalloc(chip->dev, माप(*policy), GFP_KERNEL);
	अगर (!policy)
		वापस -ENOMEM;

	fs->location = 0;
	err = idr_alloc_u32(&chip->policies, policy, &fs->location, 0xffffffff,
			    GFP_KERNEL);
	अगर (err) अणु
		devm_kमुक्त(chip->dev, policy);
		वापस err;
	पूर्ण

	स_नकल(&policy->fs, fs, माप(*fs));
	ether_addr_copy(policy->addr, addr);
	policy->mapping = mapping;
	policy->action = action;
	policy->port = port;
	policy->vid = vid;

	err = mv88e6xxx_policy_apply(chip, port, policy);
	अगर (err) अणु
		idr_हटाओ(&chip->policies, fs->location);
		devm_kमुक्त(chip->dev, policy);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_get_rxnfc(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा ethtool_rxnfc *rxnfc, u32 *rule_locs)
अणु
	काष्ठा ethtool_rx_flow_spec *fs = &rxnfc->fs;
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	काष्ठा mv88e6xxx_policy *policy;
	पूर्णांक err;
	पूर्णांक id;

	mv88e6xxx_reg_lock(chip);

	चयन (rxnfc->cmd) अणु
	हाल ETHTOOL_GRXCLSRLCNT:
		rxnfc->data = 0;
		rxnfc->data |= RX_CLS_LOC_SPECIAL;
		rxnfc->rule_cnt = 0;
		idr_क्रम_each_entry(&chip->policies, policy, id)
			अगर (policy->port == port)
				rxnfc->rule_cnt++;
		err = 0;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		err = -ENOENT;
		policy = idr_find(&chip->policies, fs->location);
		अगर (policy) अणु
			स_नकल(fs, &policy->fs, माप(*fs));
			err = 0;
		पूर्ण
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		rxnfc->data = 0;
		rxnfc->rule_cnt = 0;
		idr_क्रम_each_entry(&chip->policies, policy, id)
			अगर (policy->port == port)
				rule_locs[rxnfc->rule_cnt++] = id;
		err = 0;
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_set_rxnfc(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा ethtool_rxnfc *rxnfc)
अणु
	काष्ठा ethtool_rx_flow_spec *fs = &rxnfc->fs;
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	काष्ठा mv88e6xxx_policy *policy;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);

	चयन (rxnfc->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		err = mv88e6xxx_policy_insert(chip, port, fs);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		err = -ENOENT;
		policy = idr_हटाओ(&chip->policies, fs->location);
		अगर (policy) अणु
			policy->action = MV88E6XXX_POLICY_ACTION_NORMAL;
			err = mv88e6xxx_policy_apply(chip, port, policy);
			devm_kमुक्त(chip->dev, policy);
		पूर्ण
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_add_broadcast(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					u16 vid)
अणु
	u8 state = MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC;
	u8 broadcast[ETH_ALEN];

	eth_broadcast_addr(broadcast);

	वापस mv88e6xxx_port_db_load_purge(chip, port, broadcast, vid, state);
पूर्ण

अटल पूर्णांक mv88e6xxx_broadcast_setup(काष्ठा mv88e6xxx_chip *chip, u16 vid)
अणु
	पूर्णांक port;
	पूर्णांक err;

	क्रम (port = 0; port < mv88e6xxx_num_ports(chip); port++) अणु
		काष्ठा dsa_port *dp = dsa_to_port(chip->ds, port);
		काष्ठा net_device *brport;

		अगर (dsa_is_unused_port(chip->ds, port))
			जारी;

		brport = dsa_port_to_bridge_port(dp);
		अगर (brport && !br_port_flag_is_set(brport, BR_BCAST_FLOOD))
			/* Skip bridged user ports where broadcast
			 * flooding is disabled.
			 */
			जारी;

		err = mv88e6xxx_port_add_broadcast(chip, port, vid);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा mv88e6xxx_port_broadcast_sync_ctx अणु
	पूर्णांक port;
	bool flood;
पूर्ण;

अटल पूर्णांक
mv88e6xxx_port_broadcast_sync_vlan(काष्ठा mv88e6xxx_chip *chip,
				   स्थिर काष्ठा mv88e6xxx_vtu_entry *vlan,
				   व्योम *_ctx)
अणु
	काष्ठा mv88e6xxx_port_broadcast_sync_ctx *ctx = _ctx;
	u8 broadcast[ETH_ALEN];
	u8 state;

	अगर (ctx->flood)
		state = MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC;
	अन्यथा
		state = MV88E6XXX_G1_ATU_DATA_STATE_MC_UNUSED;

	eth_broadcast_addr(broadcast);

	वापस mv88e6xxx_port_db_load_purge(chip, ctx->port, broadcast,
					    vlan->vid, state);
पूर्ण

अटल पूर्णांक mv88e6xxx_port_broadcast_sync(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					 bool flood)
अणु
	काष्ठा mv88e6xxx_port_broadcast_sync_ctx ctx = अणु
		.port = port,
		.flood = flood,
	पूर्ण;
	काष्ठा mv88e6xxx_vtu_entry vid0 = अणु
		.vid = 0,
	पूर्ण;
	पूर्णांक err;

	/* Update the port's निजी database... */
	err = mv88e6xxx_port_broadcast_sync_vlan(chip, &vid0, &ctx);
	अगर (err)
		वापस err;

	/* ...and the database क्रम all VLANs. */
	वापस mv88e6xxx_vtu_walk(chip, mv88e6xxx_port_broadcast_sync_vlan,
				  &ctx);
पूर्ण

अटल पूर्णांक mv88e6xxx_port_vlan_join(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    u16 vid, u8 member, bool warn)
अणु
	स्थिर u8 non_member = MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_NON_MEMBER;
	काष्ठा mv88e6xxx_vtu_entry vlan;
	पूर्णांक i, err;

	err = mv88e6xxx_vtu_get(chip, vid, &vlan);
	अगर (err)
		वापस err;

	अगर (!vlan.valid) अणु
		स_रखो(&vlan, 0, माप(vlan));

		err = mv88e6xxx_atu_new(chip, &vlan.fid);
		अगर (err)
			वापस err;

		क्रम (i = 0; i < mv88e6xxx_num_ports(chip); ++i)
			अगर (i == port)
				vlan.member[i] = member;
			अन्यथा
				vlan.member[i] = non_member;

		vlan.vid = vid;
		vlan.valid = true;

		err = mv88e6xxx_vtu_loadpurge(chip, &vlan);
		अगर (err)
			वापस err;

		err = mv88e6xxx_broadcast_setup(chip, vlan.vid);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (vlan.member[port] != member) अणु
		vlan.member[port] = member;

		err = mv88e6xxx_vtu_loadpurge(chip, &vlan);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (warn) अणु
		dev_info(chip->dev, "p%d: already a member of VLAN %d\n",
			 port, vid);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	bool warn;
	u8 member;
	पूर्णांक err;

	err = mv88e6xxx_port_vlan_prepare(ds, port, vlan);
	अगर (err)
		वापस err;

	अगर (dsa_is_dsa_port(ds, port) || dsa_is_cpu_port(ds, port))
		member = MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_UNMODIFIED;
	अन्यथा अगर (untagged)
		member = MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_UNTAGGED;
	अन्यथा
		member = MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_TAGGED;

	/* net/dsa/slave.c will call dsa_port_vlan_add() क्रम the affected port
	 * and then the CPU port. Do not warn क्रम duplicates क्रम the CPU port.
	 */
	warn = !dsa_is_cpu_port(ds, port) && !dsa_is_dsa_port(ds, port);

	mv88e6xxx_reg_lock(chip);

	err = mv88e6xxx_port_vlan_join(chip, port, vlan->vid, member, warn);
	अगर (err) अणु
		dev_err(ds->dev, "p%d: failed to add VLAN %d%c\n", port,
			vlan->vid, untagged ? 'u' : 't');
		जाओ out;
	पूर्ण

	अगर (pvid) अणु
		err = mv88e6xxx_port_set_pvid(chip, port, vlan->vid);
		अगर (err) अणु
			dev_err(ds->dev, "p%d: failed to set PVID %d\n",
				port, vlan->vid);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_vlan_leave(काष्ठा mv88e6xxx_chip *chip,
				     पूर्णांक port, u16 vid)
अणु
	काष्ठा mv88e6xxx_vtu_entry vlan;
	पूर्णांक i, err;

	अगर (!vid)
		वापस -EOPNOTSUPP;

	err = mv88e6xxx_vtu_get(chip, vid, &vlan);
	अगर (err)
		वापस err;

	/* If the VLAN करोesn't exist in hardware or the port isn't a member,
	 * tell चयनdev that this VLAN is likely handled in software.
	 */
	अगर (!vlan.valid ||
	    vlan.member[port] == MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_NON_MEMBER)
		वापस -EOPNOTSUPP;

	vlan.member[port] = MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_NON_MEMBER;

	/* keep the VLAN unless all ports are excluded */
	vlan.valid = false;
	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); ++i) अणु
		अगर (vlan.member[i] !=
		    MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_NON_MEMBER) अणु
			vlan.valid = true;
			अवरोध;
		पूर्ण
	पूर्ण

	err = mv88e6xxx_vtu_loadpurge(chip, &vlan);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g1_atu_हटाओ(chip, vlan.fid, port, false);
पूर्ण

अटल पूर्णांक mv88e6xxx_port_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err = 0;
	u16 pvid;

	अगर (!mv88e6xxx_max_vid(chip))
		वापस -EOPNOTSUPP;

	mv88e6xxx_reg_lock(chip);

	err = mv88e6xxx_port_get_pvid(chip, port, &pvid);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_port_vlan_leave(chip, port, vlan->vid);
	अगर (err)
		जाओ unlock;

	अगर (vlan->vid == pvid) अणु
		err = mv88e6xxx_port_set_pvid(chip, port, 0);
		अगर (err)
			जाओ unlock;
	पूर्ण

unlock:
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_db_load_purge(chip, port, addr, vid,
					   MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_db_load_purge(chip, port, addr, vid, 0);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_db_dump_fid(काष्ठा mv88e6xxx_chip *chip,
				      u16 fid, u16 vid, पूर्णांक port,
				      dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा mv88e6xxx_atu_entry addr;
	bool is_अटल;
	पूर्णांक err;

	addr.state = 0;
	eth_broadcast_addr(addr.mac);

	करो अणु
		err = mv88e6xxx_g1_atu_getnext(chip, fid, &addr);
		अगर (err)
			वापस err;

		अगर (!addr.state)
			अवरोध;

		अगर (addr.trunk || (addr.portvec & BIT(port)) == 0)
			जारी;

		अगर (!is_unicast_ether_addr(addr.mac))
			जारी;

		is_अटल = (addr.state ==
			     MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC);
		err = cb(addr.mac, vid, is_अटल, data);
		अगर (err)
			वापस err;
	पूर्ण जबतक (!is_broadcast_ether_addr(addr.mac));

	वापस err;
पूर्ण

काष्ठा mv88e6xxx_port_db_dump_vlan_ctx अणु
	पूर्णांक port;
	dsa_fdb_dump_cb_t *cb;
	व्योम *data;
पूर्ण;

अटल पूर्णांक mv88e6xxx_port_db_dump_vlan(काष्ठा mv88e6xxx_chip *chip,
				       स्थिर काष्ठा mv88e6xxx_vtu_entry *entry,
				       व्योम *_data)
अणु
	काष्ठा mv88e6xxx_port_db_dump_vlan_ctx *ctx = _data;

	वापस mv88e6xxx_port_db_dump_fid(chip, entry->fid, entry->vid,
					  ctx->port, ctx->cb, ctx->data);
पूर्ण

अटल पूर्णांक mv88e6xxx_port_db_dump(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा mv88e6xxx_port_db_dump_vlan_ctx ctx = अणु
		.port = port,
		.cb = cb,
		.data = data,
	पूर्ण;
	u16 fid;
	पूर्णांक err;

	/* Dump port's शेष Filtering Inक्रमmation Database (VLAN ID 0) */
	err = mv88e6xxx_port_get_fid(chip, port, &fid);
	अगर (err)
		वापस err;

	err = mv88e6xxx_port_db_dump_fid(chip, fid, 0, port, cb, data);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_vtu_walk(chip, mv88e6xxx_port_db_dump_vlan, &ctx);
पूर्ण

अटल पूर्णांक mv88e6xxx_port_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_db_dump(chip, port, cb, data);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_bridge_map(काष्ठा mv88e6xxx_chip *chip,
				काष्ठा net_device *br)
अणु
	काष्ठा dsa_चयन *ds = chip->ds;
	काष्ठा dsa_चयन_tree *dst = ds->dst;
	काष्ठा dsa_port *dp;
	पूर्णांक err;

	list_क्रम_each_entry(dp, &dst->ports, list) अणु
		अगर (dp->bridge_dev == br) अणु
			अगर (dp->ds == ds) अणु
				/* This is a local bridge group member,
				 * remap its Port VLAN Map.
				 */
				err = mv88e6xxx_port_vlan_map(chip, dp->index);
				अगर (err)
					वापस err;
			पूर्ण अन्यथा अणु
				/* This is an बाह्यal bridge group member,
				 * remap its cross-chip Port VLAN Table entry.
				 */
				err = mv88e6xxx_pvt_map(chip, dp->ds->index,
							dp->index);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_bridge_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      काष्ठा net_device *br)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_bridge_map(chip, br);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल व्योम mv88e6xxx_port_bridge_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
					काष्ठा net_device *br)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;

	mv88e6xxx_reg_lock(chip);
	अगर (mv88e6xxx_bridge_map(chip, br) ||
	    mv88e6xxx_port_vlan_map(chip, port))
		dev_err(ds->dev, "failed to remap in-chip Port VLAN\n");
	mv88e6xxx_reg_unlock(chip);
पूर्ण

अटल पूर्णांक mv88e6xxx_crosschip_bridge_join(काष्ठा dsa_चयन *ds,
					   पूर्णांक tree_index, पूर्णांक sw_index,
					   पूर्णांक port, काष्ठा net_device *br)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	अगर (tree_index != ds->dst->index)
		वापस 0;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_pvt_map(chip, sw_index, port);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल व्योम mv88e6xxx_crosschip_bridge_leave(काष्ठा dsa_चयन *ds,
					     पूर्णांक tree_index, पूर्णांक sw_index,
					     पूर्णांक port, काष्ठा net_device *br)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;

	अगर (tree_index != ds->dst->index)
		वापस;

	mv88e6xxx_reg_lock(chip);
	अगर (mv88e6xxx_pvt_map(chip, sw_index, port))
		dev_err(ds->dev, "failed to remap cross-chip Port VLAN\n");
	mv88e6xxx_reg_unlock(chip);
पूर्ण

अटल पूर्णांक mv88e6xxx_software_reset(काष्ठा mv88e6xxx_chip *chip)
अणु
	अगर (chip->info->ops->reset)
		वापस chip->info->ops->reset(chip);

	वापस 0;
पूर्ण

अटल व्योम mv88e6xxx_hardware_reset(काष्ठा mv88e6xxx_chip *chip)
अणु
	काष्ठा gpio_desc *gpiod = chip->reset;

	/* If there is a GPIO connected to the reset pin, toggle it */
	अगर (gpiod) अणु
		gpiod_set_value_cansleep(gpiod, 1);
		usleep_range(10000, 20000);
		gpiod_set_value_cansleep(gpiod, 0);
		usleep_range(10000, 20000);

		mv88e6xxx_g1_रुको_eeprom_करोne(chip);
	पूर्ण
पूर्ण

अटल पूर्णांक mv88e6xxx_disable_ports(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक i, err;

	/* Set all ports to the Disabled state */
	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); i++) अणु
		err = mv88e6xxx_port_set_state(chip, i, BR_STATE_DISABLED);
		अगर (err)
			वापस err;
	पूर्ण

	/* Wait क्रम transmit queues to drain,
	 * i.e. 2ms क्रम a maximum frame to be transmitted at 10 Mbps.
	 */
	usleep_range(2000, 4000);

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_चयन_reset(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	err = mv88e6xxx_disable_ports(chip);
	अगर (err)
		वापस err;

	mv88e6xxx_hardware_reset(chip);

	वापस mv88e6xxx_software_reset(chip);
पूर्ण

अटल पूर्णांक mv88e6xxx_set_port_mode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   क्रमागत mv88e6xxx_frame_mode frame,
				   क्रमागत mv88e6xxx_egress_mode egress, u16 etype)
अणु
	पूर्णांक err;

	अगर (!chip->info->ops->port_set_frame_mode)
		वापस -EOPNOTSUPP;

	err = mv88e6xxx_port_set_egress_mode(chip, port, egress);
	अगर (err)
		वापस err;

	err = chip->info->ops->port_set_frame_mode(chip, port, frame);
	अगर (err)
		वापस err;

	अगर (chip->info->ops->port_set_ether_type)
		वापस chip->info->ops->port_set_ether_type(chip, port, etype);

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_set_port_mode_normal(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस mv88e6xxx_set_port_mode(chip, port, MV88E6XXX_FRAME_MODE_NORMAL,
				       MV88E6XXX_EGRESS_MODE_UNMODIFIED,
				       MV88E6XXX_PORT_ETH_TYPE_DEFAULT);
पूर्ण

अटल पूर्णांक mv88e6xxx_set_port_mode_dsa(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस mv88e6xxx_set_port_mode(chip, port, MV88E6XXX_FRAME_MODE_DSA,
				       MV88E6XXX_EGRESS_MODE_UNMODIFIED,
				       MV88E6XXX_PORT_ETH_TYPE_DEFAULT);
पूर्ण

अटल पूर्णांक mv88e6xxx_set_port_mode_edsa(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस mv88e6xxx_set_port_mode(chip, port,
				       MV88E6XXX_FRAME_MODE_ETHERTYPE,
				       MV88E6XXX_EGRESS_MODE_ETHERTYPE,
				       ETH_P_EDSA);
पूर्ण

अटल पूर्णांक mv88e6xxx_setup_port_mode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	अगर (dsa_is_dsa_port(chip->ds, port))
		वापस mv88e6xxx_set_port_mode_dsa(chip, port);

	अगर (dsa_is_user_port(chip->ds, port))
		वापस mv88e6xxx_set_port_mode_normal(chip, port);

	/* Setup CPU port mode depending on its supported tag क्रमmat */
	अगर (chip->tag_protocol == DSA_TAG_PROTO_DSA)
		वापस mv88e6xxx_set_port_mode_dsa(chip, port);

	अगर (chip->tag_protocol == DSA_TAG_PROTO_EDSA)
		वापस mv88e6xxx_set_port_mode_edsa(chip, port);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mv88e6xxx_setup_message_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	bool message = dsa_is_dsa_port(chip->ds, port);

	वापस mv88e6xxx_port_set_message_port(chip, port, message);
पूर्ण

अटल पूर्णांक mv88e6xxx_setup_egress_floods(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	पूर्णांक err;

	अगर (chip->info->ops->port_set_ucast_flood) अणु
		err = chip->info->ops->port_set_ucast_flood(chip, port, true);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (chip->info->ops->port_set_mcast_flood) अणु
		err = chip->info->ops->port_set_mcast_flood(chip, port, true);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t mv88e6xxx_serdes_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mv88e6xxx_port *mvp = dev_id;
	काष्ठा mv88e6xxx_chip *chip = mvp->chip;
	irqवापस_t ret = IRQ_NONE;
	पूर्णांक port = mvp->port;
	पूर्णांक lane;

	mv88e6xxx_reg_lock(chip);
	lane = mv88e6xxx_serdes_get_lane(chip, port);
	अगर (lane >= 0)
		ret = mv88e6xxx_serdes_irq_status(chip, port, lane);
	mv88e6xxx_reg_unlock(chip);

	वापस ret;
पूर्ण

अटल पूर्णांक mv88e6xxx_serdes_irq_request(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					पूर्णांक lane)
अणु
	काष्ठा mv88e6xxx_port *dev_id = &chip->ports[port];
	अचिन्हित पूर्णांक irq;
	पूर्णांक err;

	/* Nothing to request अगर this SERDES port has no IRQ */
	irq = mv88e6xxx_serdes_irq_mapping(chip, port);
	अगर (!irq)
		वापस 0;

	snम_लिखो(dev_id->serdes_irq_name, माप(dev_id->serdes_irq_name),
		 "mv88e6xxx-%s-serdes-%d", dev_name(chip->dev), port);

	/* Requesting the IRQ will trigger IRQ callbacks, so release the lock */
	mv88e6xxx_reg_unlock(chip);
	err = request_thपढ़ोed_irq(irq, शून्य, mv88e6xxx_serdes_irq_thपढ़ो_fn,
				   IRQF_ONESHOT, dev_id->serdes_irq_name,
				   dev_id);
	mv88e6xxx_reg_lock(chip);
	अगर (err)
		वापस err;

	dev_id->serdes_irq = irq;

	वापस mv88e6xxx_serdes_irq_enable(chip, port, lane);
पूर्ण

अटल पूर्णांक mv88e6xxx_serdes_irq_मुक्त(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     पूर्णांक lane)
अणु
	काष्ठा mv88e6xxx_port *dev_id = &chip->ports[port];
	अचिन्हित पूर्णांक irq = dev_id->serdes_irq;
	पूर्णांक err;

	/* Nothing to मुक्त अगर no IRQ has been requested */
	अगर (!irq)
		वापस 0;

	err = mv88e6xxx_serdes_irq_disable(chip, port, lane);

	/* Freeing the IRQ will trigger IRQ callbacks, so release the lock */
	mv88e6xxx_reg_unlock(chip);
	मुक्त_irq(irq, dev_id);
	mv88e6xxx_reg_lock(chip);

	dev_id->serdes_irq = 0;

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_serdes_घातer(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  bool on)
अणु
	पूर्णांक lane;
	पूर्णांक err;

	lane = mv88e6xxx_serdes_get_lane(chip, port);
	अगर (lane < 0)
		वापस 0;

	अगर (on) अणु
		err = mv88e6xxx_serdes_घातer_up(chip, port, lane);
		अगर (err)
			वापस err;

		err = mv88e6xxx_serdes_irq_request(chip, port, lane);
	पूर्ण अन्यथा अणु
		err = mv88e6xxx_serdes_irq_मुक्त(chip, port, lane);
		अगर (err)
			वापस err;

		err = mv88e6xxx_serdes_घातer_करोwn(chip, port, lane);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_set_egress_port(काष्ठा mv88e6xxx_chip *chip,
				     क्रमागत mv88e6xxx_egress_direction direction,
				     पूर्णांक port)
अणु
	पूर्णांक err;

	अगर (!chip->info->ops->set_egress_port)
		वापस -EOPNOTSUPP;

	err = chip->info->ops->set_egress_port(chip, direction, port);
	अगर (err)
		वापस err;

	अगर (direction == MV88E6XXX_EGRESS_सूची_INGRESS)
		chip->ingress_dest_port = port;
	अन्यथा
		chip->egress_dest_port = port;

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_setup_upstream_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	काष्ठा dsa_चयन *ds = chip->ds;
	पूर्णांक upstream_port;
	पूर्णांक err;

	upstream_port = dsa_upstream_port(ds, port);
	अगर (chip->info->ops->port_set_upstream_port) अणु
		err = chip->info->ops->port_set_upstream_port(chip, port,
							      upstream_port);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (port == upstream_port) अणु
		अगर (chip->info->ops->set_cpu_port) अणु
			err = chip->info->ops->set_cpu_port(chip,
							    upstream_port);
			अगर (err)
				वापस err;
		पूर्ण

		err = mv88e6xxx_set_egress_port(chip,
						MV88E6XXX_EGRESS_सूची_INGRESS,
						upstream_port);
		अगर (err && err != -EOPNOTSUPP)
			वापस err;

		err = mv88e6xxx_set_egress_port(chip,
						MV88E6XXX_EGRESS_सूची_EGRESS,
						upstream_port);
		अगर (err && err != -EOPNOTSUPP)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_setup_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	काष्ठा dsa_चयन *ds = chip->ds;
	पूर्णांक err;
	u16 reg;

	chip->ports[port].chip = chip;
	chip->ports[port].port = port;

	/* MAC Forcing रेजिस्टर: करोn't क्रमce link, speed, duplex or flow control
	 * state to any particular values on physical ports, but क्रमce the CPU
	 * port and all DSA ports to their maximum bandwidth and full duplex.
	 */
	अगर (dsa_is_cpu_port(ds, port) || dsa_is_dsa_port(ds, port))
		err = mv88e6xxx_port_setup_mac(chip, port, LINK_FORCED_UP,
					       SPEED_MAX, DUPLEX_FULL,
					       PAUSE_OFF,
					       PHY_INTERFACE_MODE_NA);
	अन्यथा
		err = mv88e6xxx_port_setup_mac(chip, port, LINK_UNFORCED,
					       SPEED_UNFORCED, DUPLEX_UNFORCED,
					       PAUSE_ON,
					       PHY_INTERFACE_MODE_NA);
	अगर (err)
		वापस err;

	/* Port Control: disable Drop-on-Unlock, disable Drop-on-Lock,
	 * disable Header mode, enable IGMP/MLD snooping, disable VLAN
	 * tunneling, determine priority by looking at 802.1p and IP
	 * priority fields (IP prio has precedence), and set STP state
	 * to Forwarding.
	 *
	 * If this is the CPU link, use DSA or EDSA tagging depending
	 * on which tagging mode was configured.
	 *
	 * If this is a link to another चयन, use DSA tagging mode.
	 *
	 * If this is the upstream port क्रम this चयन, enable
	 * क्रमwarding of unknown unicasts and multicasts.
	 */
	reg = MV88E6XXX_PORT_CTL0_IGMP_MLD_SNOOP |
		MV88E6185_PORT_CTL0_USE_TAG | MV88E6185_PORT_CTL0_USE_IP |
		MV88E6XXX_PORT_CTL0_STATE_FORWARDING;
	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL0, reg);
	अगर (err)
		वापस err;

	err = mv88e6xxx_setup_port_mode(chip, port);
	अगर (err)
		वापस err;

	err = mv88e6xxx_setup_egress_floods(chip, port);
	अगर (err)
		वापस err;

	/* Port Control 2: करोn't क्रमce a good FCS, set the maximum frame size to
	 * 10240 bytes, disable 802.1q tags checking, करोn't discard tagged or
	 * untagged frames on this port, करो a destination address lookup on all
	 * received packets as usual, disable ARP mirroring and करोn't send a
	 * copy of all transmitted/received frames on this port to the CPU.
	 */
	err = mv88e6xxx_port_set_map_da(chip, port);
	अगर (err)
		वापस err;

	err = mv88e6xxx_setup_upstream_port(chip, port);
	अगर (err)
		वापस err;

	err = mv88e6xxx_port_set_8021q_mode(chip, port,
				MV88E6XXX_PORT_CTL2_8021Q_MODE_DISABLED);
	अगर (err)
		वापस err;

	अगर (chip->info->ops->port_set_jumbo_size) अणु
		err = chip->info->ops->port_set_jumbo_size(chip, port, 10240);
		अगर (err)
			वापस err;
	पूर्ण

	/* Port Association Vector: disable स्वतःmatic address learning
	 * on all user ports since they start out in standalone
	 * mode. When joining a bridge, learning will be configured to
	 * match the bridge port settings. Enable learning on all
	 * DSA/CPU ports. NOTE: FROM_CPU frames always bypass the
	 * learning process.
	 *
	 * Disable HoldAt1, IntOnAgeOut, LockedPort, IgnoreWrongData,
	 * and RefreshLocked. I.e. setup standard स्वतःmatic learning.
	 */
	अगर (dsa_is_user_port(ds, port))
		reg = 0;
	अन्यथा
		reg = 1 << port;

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_ASSOC_VECTOR,
				   reg);
	अगर (err)
		वापस err;

	/* Egress rate control 2: disable egress rate control. */
	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_EGRESS_RATE_CTL2,
				   0x0000);
	अगर (err)
		वापस err;

	अगर (chip->info->ops->port_छोड़ो_limit) अणु
		err = chip->info->ops->port_छोड़ो_limit(chip, port, 0, 0);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (chip->info->ops->port_disable_learn_limit) अणु
		err = chip->info->ops->port_disable_learn_limit(chip, port);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (chip->info->ops->port_disable_pri_override) अणु
		err = chip->info->ops->port_disable_pri_override(chip, port);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (chip->info->ops->port_tag_remap) अणु
		err = chip->info->ops->port_tag_remap(chip, port);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (chip->info->ops->port_egress_rate_limiting) अणु
		err = chip->info->ops->port_egress_rate_limiting(chip, port);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (chip->info->ops->port_setup_message_port) अणु
		err = chip->info->ops->port_setup_message_port(chip, port);
		अगर (err)
			वापस err;
	पूर्ण

	/* Port based VLAN map: give each port the same शेष address
	 * database, and allow bidirectional communication between the
	 * CPU and DSA port(s), and the other ports.
	 */
	err = mv88e6xxx_port_set_fid(chip, port, 0);
	अगर (err)
		वापस err;

	err = mv88e6xxx_port_vlan_map(chip, port);
	अगर (err)
		वापस err;

	/* Default VLAN ID and priority: करोn't set a शेष VLAN
	 * ID, and set the शेष packet priority to zero.
	 */
	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_DEFAULT_VLAN, 0);
पूर्ण

अटल पूर्णांक mv88e6xxx_get_max_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;

	अगर (chip->info->ops->port_set_jumbo_size)
		वापस 10240;
	अन्यथा अगर (chip->info->ops->set_max_frame_size)
		वापस 1632;
	वापस 1522;
पूर्ण

अटल पूर्णांक mv88e6xxx_change_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक new_mtu)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक ret = 0;

	mv88e6xxx_reg_lock(chip);
	अगर (chip->info->ops->port_set_jumbo_size)
		ret = chip->info->ops->port_set_jumbo_size(chip, port, new_mtu);
	अन्यथा अगर (chip->info->ops->set_max_frame_size)
		ret = chip->info->ops->set_max_frame_size(chip, new_mtu);
	अन्यथा
		अगर (new_mtu > 1522)
			ret = -EINVAL;
	mv88e6xxx_reg_unlock(chip);

	वापस ret;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_enable(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा phy_device *phydev)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_serdes_घातer(chip, port, true);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल व्योम mv88e6xxx_port_disable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;

	mv88e6xxx_reg_lock(chip);
	अगर (mv88e6xxx_serdes_घातer(chip, port, false))
		dev_err(chip->dev, "failed to power off SERDES\n");
	mv88e6xxx_reg_unlock(chip);
पूर्ण

अटल पूर्णांक mv88e6xxx_set_ageing_समय(काष्ठा dsa_चयन *ds,
				     अचिन्हित पूर्णांक ageing_समय)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_g1_atu_set_age_समय(chip, ageing_समय);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_stats_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	/* Initialize the statistics unit */
	अगर (chip->info->ops->stats_set_histogram) अणु
		err = chip->info->ops->stats_set_histogram(chip);
		अगर (err)
			वापस err;
	पूर्ण

	वापस mv88e6xxx_g1_stats_clear(chip);
पूर्ण

/* Check अगर the errata has alपढ़ोy been applied. */
अटल bool mv88e6390_setup_errata_applied(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक port;
	पूर्णांक err;
	u16 val;

	क्रम (port = 0; port < mv88e6xxx_num_ports(chip); port++) अणु
		err = mv88e6xxx_port_hidden_पढ़ो(chip, 0xf, port, 0, &val);
		अगर (err) अणु
			dev_err(chip->dev,
				"Error reading hidden register: %d\n", err);
			वापस false;
		पूर्ण
		अगर (val != 0x01c0)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* The 6390 copper ports have an errata which require poking magic
 * values पूर्णांकo unकरोcumented hidden रेजिस्टरs and then perक्रमming a
 * software reset.
 */
अटल पूर्णांक mv88e6390_setup_errata(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक port;
	पूर्णांक err;

	अगर (mv88e6390_setup_errata_applied(chip))
		वापस 0;

	/* Set the ports पूर्णांकo blocking mode */
	क्रम (port = 0; port < mv88e6xxx_num_ports(chip); port++) अणु
		err = mv88e6xxx_port_set_state(chip, port, BR_STATE_DISABLED);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (port = 0; port < mv88e6xxx_num_ports(chip); port++) अणु
		err = mv88e6xxx_port_hidden_ग_लिखो(chip, 0xf, port, 0, 0x01c0);
		अगर (err)
			वापस err;
	पूर्ण

	वापस mv88e6xxx_software_reset(chip);
पूर्ण

अटल व्योम mv88e6xxx_tearकरोwn(काष्ठा dsa_चयन *ds)
अणु
	mv88e6xxx_tearकरोwn_devlink_params(ds);
	dsa_devlink_resources_unरेजिस्टर(ds);
	mv88e6xxx_tearकरोwn_devlink_regions(ds);
पूर्ण

अटल पूर्णांक mv88e6xxx_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	u8 cmode;
	पूर्णांक err;
	पूर्णांक i;

	chip->ds = ds;
	ds->slave_mii_bus = mv88e6xxx_शेष_mdio_bus(chip);

	mv88e6xxx_reg_lock(chip);

	अगर (chip->info->ops->setup_errata) अणु
		err = chip->info->ops->setup_errata(chip);
		अगर (err)
			जाओ unlock;
	पूर्ण

	/* Cache the cmode of each port. */
	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); i++) अणु
		अगर (chip->info->ops->port_get_cmode) अणु
			err = chip->info->ops->port_get_cmode(chip, i, &cmode);
			अगर (err)
				जाओ unlock;

			chip->ports[i].cmode = cmode;
		पूर्ण
	पूर्ण

	/* Setup Switch Port Registers */
	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); i++) अणु
		अगर (dsa_is_unused_port(ds, i))
			जारी;

		/* Prevent the use of an invalid port. */
		अगर (mv88e6xxx_is_invalid_port(chip, i)) अणु
			dev_err(chip->dev, "port %d is invalid\n", i);
			err = -EINVAL;
			जाओ unlock;
		पूर्ण

		err = mv88e6xxx_setup_port(chip, i);
		अगर (err)
			जाओ unlock;
	पूर्ण

	err = mv88e6xxx_irl_setup(chip);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_mac_setup(chip);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_phy_setup(chip);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_vtu_setup(chip);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_pvt_setup(chip);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_atu_setup(chip);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_broadcast_setup(chip, 0);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_pot_setup(chip);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_rmu_setup(chip);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_rsvd2cpu_setup(chip);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_trunk_setup(chip);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_devmap_setup(chip);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_pri_setup(chip);
	अगर (err)
		जाओ unlock;

	/* Setup PTP Hardware Clock and बारtamping */
	अगर (chip->info->ptp_support) अणु
		err = mv88e6xxx_ptp_setup(chip);
		अगर (err)
			जाओ unlock;

		err = mv88e6xxx_hwtstamp_setup(chip);
		अगर (err)
			जाओ unlock;
	पूर्ण

	err = mv88e6xxx_stats_setup(chip);
	अगर (err)
		जाओ unlock;

unlock:
	mv88e6xxx_reg_unlock(chip);

	अगर (err)
		वापस err;

	/* Have to be called without holding the रेजिस्टर lock, since
	 * they take the devlink lock, and we later take the locks in
	 * the reverse order when getting/setting parameters or
	 * resource occupancy.
	 */
	err = mv88e6xxx_setup_devlink_resources(ds);
	अगर (err)
		वापस err;

	err = mv88e6xxx_setup_devlink_params(ds);
	अगर (err)
		जाओ out_resources;

	err = mv88e6xxx_setup_devlink_regions(ds);
	अगर (err)
		जाओ out_params;

	वापस 0;

out_params:
	mv88e6xxx_tearकरोwn_devlink_params(ds);
out_resources:
	dsa_devlink_resources_unरेजिस्टर(ds);

	वापस err;
पूर्ण

/* prod_id क्रम चयन families which करो not have a PHY model number */
अटल स्थिर u16 family_prod_id_table[] = अणु
	[MV88E6XXX_FAMILY_6341] = MV88E6XXX_PORT_SWITCH_ID_PROD_6341,
	[MV88E6XXX_FAMILY_6390] = MV88E6XXX_PORT_SWITCH_ID_PROD_6390,
	[MV88E6XXX_FAMILY_6393] = MV88E6XXX_PORT_SWITCH_ID_PROD_6393X,
पूर्ण;

अटल पूर्णांक mv88e6xxx_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg)
अणु
	काष्ठा mv88e6xxx_mdio_bus *mdio_bus = bus->priv;
	काष्ठा mv88e6xxx_chip *chip = mdio_bus->chip;
	u16 prod_id;
	u16 val;
	पूर्णांक err;

	अगर (!chip->info->ops->phy_पढ़ो)
		वापस -EOPNOTSUPP;

	mv88e6xxx_reg_lock(chip);
	err = chip->info->ops->phy_पढ़ो(chip, bus, phy, reg, &val);
	mv88e6xxx_reg_unlock(chip);

	/* Some पूर्णांकernal PHYs करोn't have a model number. */
	अगर (reg == MII_PHYSID2 && !(val & 0x3f0) &&
	    chip->info->family < ARRAY_SIZE(family_prod_id_table)) अणु
		prod_id = family_prod_id_table[chip->info->family];
		अगर (prod_id)
			val |= prod_id >> 4;
	पूर्ण

	वापस err ? err : val;
पूर्ण

अटल पूर्णांक mv88e6xxx_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg, u16 val)
अणु
	काष्ठा mv88e6xxx_mdio_bus *mdio_bus = bus->priv;
	काष्ठा mv88e6xxx_chip *chip = mdio_bus->chip;
	पूर्णांक err;

	अगर (!chip->info->ops->phy_ग_लिखो)
		वापस -EOPNOTSUPP;

	mv88e6xxx_reg_lock(chip);
	err = chip->info->ops->phy_ग_लिखो(chip, bus, phy, reg, val);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_mdio_रेजिस्टर(काष्ठा mv88e6xxx_chip *chip,
				   काष्ठा device_node *np,
				   bool बाह्यal)
अणु
	अटल पूर्णांक index;
	काष्ठा mv88e6xxx_mdio_bus *mdio_bus;
	काष्ठा mii_bus *bus;
	पूर्णांक err;

	अगर (बाह्यal) अणु
		mv88e6xxx_reg_lock(chip);
		err = mv88e6xxx_g2_scratch_gpio_set_smi(chip, true);
		mv88e6xxx_reg_unlock(chip);

		अगर (err)
			वापस err;
	पूर्ण

	bus = devm_mdiobus_alloc_size(chip->dev, माप(*mdio_bus));
	अगर (!bus)
		वापस -ENOMEM;

	mdio_bus = bus->priv;
	mdio_bus->bus = bus;
	mdio_bus->chip = chip;
	INIT_LIST_HEAD(&mdio_bus->list);
	mdio_bus->बाह्यal = बाह्यal;

	अगर (np) अणु
		bus->name = np->full_name;
		snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%pOF", np);
	पूर्ण अन्यथा अणु
		bus->name = "mv88e6xxx SMI";
		snम_लिखो(bus->id, MII_BUS_ID_SIZE, "mv88e6xxx-%d", index++);
	पूर्ण

	bus->पढ़ो = mv88e6xxx_mdio_पढ़ो;
	bus->ग_लिखो = mv88e6xxx_mdio_ग_लिखो;
	bus->parent = chip->dev;

	अगर (!बाह्यal) अणु
		err = mv88e6xxx_g2_irq_mdio_setup(chip, bus);
		अगर (err)
			वापस err;
	पूर्ण

	err = of_mdiobus_रेजिस्टर(bus, np);
	अगर (err) अणु
		dev_err(chip->dev, "Cannot register MDIO bus (%d)\n", err);
		mv88e6xxx_g2_irq_mdio_मुक्त(chip, bus);
		वापस err;
	पूर्ण

	अगर (बाह्यal)
		list_add_tail(&mdio_bus->list, &chip->mdios);
	अन्यथा
		list_add(&mdio_bus->list, &chip->mdios);

	वापस 0;
पूर्ण

अटल व्योम mv88e6xxx_mdios_unरेजिस्टर(काष्ठा mv88e6xxx_chip *chip)

अणु
	काष्ठा mv88e6xxx_mdio_bus *mdio_bus;
	काष्ठा mii_bus *bus;

	list_क्रम_each_entry(mdio_bus, &chip->mdios, list) अणु
		bus = mdio_bus->bus;

		अगर (!mdio_bus->बाह्यal)
			mv88e6xxx_g2_irq_mdio_मुक्त(chip, bus);

		mdiobus_unरेजिस्टर(bus);
	पूर्ण
पूर्ण

अटल पूर्णांक mv88e6xxx_mdios_रेजिस्टर(काष्ठा mv88e6xxx_chip *chip,
				    काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	पूर्णांक err;

	/* Always रेजिस्टर one mdio bus क्रम the पूर्णांकernal/शेष mdio
	 * bus. This maybe represented in the device tree, but is
	 * optional.
	 */
	child = of_get_child_by_name(np, "mdio");
	err = mv88e6xxx_mdio_रेजिस्टर(chip, child, false);
	अगर (err)
		वापस err;

	/* Walk the device tree, and see अगर there are any other nodes
	 * which say they are compatible with the बाह्यal mdio
	 * bus.
	 */
	क्रम_each_available_child_of_node(np, child) अणु
		अगर (of_device_is_compatible(
			    child, "marvell,mv88e6xxx-mdio-external")) अणु
			err = mv88e6xxx_mdio_रेजिस्टर(chip, child, true);
			अगर (err) अणु
				mv88e6xxx_mdios_unरेजिस्टर(chip);
				of_node_put(child);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_get_eeprom_len(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;

	वापस chip->eeprom_len;
पूर्ण

अटल पूर्णांक mv88e6xxx_get_eeprom(काष्ठा dsa_चयन *ds,
				काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	अगर (!chip->info->ops->get_eeprom)
		वापस -EOPNOTSUPP;

	mv88e6xxx_reg_lock(chip);
	err = chip->info->ops->get_eeprom(chip, eeprom, data);
	mv88e6xxx_reg_unlock(chip);

	अगर (err)
		वापस err;

	eeprom->magic = 0xc3ec4951;

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_set_eeprom(काष्ठा dsa_चयन *ds,
				काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	अगर (!chip->info->ops->set_eeprom)
		वापस -EOPNOTSUPP;

	अगर (eeprom->magic != 0xc3ec4951)
		वापस -EINVAL;

	mv88e6xxx_reg_lock(chip);
	err = chip->info->ops->set_eeprom(chip, eeprom, data);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6085_ops = अणु
	/* MV88E6XXX_FAMILY_6097 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.set_चयन_mac = mv88e6xxx_g1_set_चयन_mac,
	.phy_पढ़ो = mv88e6185_phy_ppu_पढ़ो,
	.phy_ग_लिखो = mv88e6185_phy_ppu_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6185_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.ppu_enable = mv88e6185_g1_ppu_enable,
	.ppu_disable = mv88e6185_g1_ppu_disable,
	.reset = mv88e6185_g1_reset,
	.rmu_disable = mv88e6085_g1_rmu_disable,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.phylink_validate = mv88e6185_phylink_validate,
	.set_max_frame_size = mv88e6185_g1_set_max_frame_size,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6095_ops = अणु
	/* MV88E6XXX_FAMILY_6095 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.set_चयन_mac = mv88e6xxx_g1_set_चयन_mac,
	.phy_पढ़ो = mv88e6185_phy_ppu_पढ़ो,
	.phy_ग_लिखो = mv88e6185_phy_ppu_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6185_port_sync_link,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_set_frame_mode = mv88e6085_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6185_port_set_क्रमward_unknown,
	.port_set_mcast_flood = mv88e6185_port_set_शेष_क्रमward,
	.port_set_upstream_port = mv88e6095_port_set_upstream_port,
	.port_get_cmode = mv88e6185_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.mgmt_rsvd2cpu = mv88e6185_g2_mgmt_rsvd2cpu,
	.serdes_घातer = mv88e6185_serdes_घातer,
	.serdes_get_lane = mv88e6185_serdes_get_lane,
	.serdes_pcs_get_state = mv88e6185_serdes_pcs_get_state,
	.ppu_enable = mv88e6185_g1_ppu_enable,
	.ppu_disable = mv88e6185_g1_ppu_disable,
	.reset = mv88e6185_g1_reset,
	.vtu_getnext = mv88e6185_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6185_g1_vtu_loadpurge,
	.phylink_validate = mv88e6185_phylink_validate,
	.set_max_frame_size = mv88e6185_g1_set_max_frame_size,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6097_ops = अणु
	/* MV88E6XXX_FAMILY_6097 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6185_port_sync_link,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_egress_rate_limiting = mv88e6095_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6185_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.serdes_घातer = mv88e6185_serdes_घातer,
	.serdes_get_lane = mv88e6185_serdes_get_lane,
	.serdes_pcs_get_state = mv88e6185_serdes_pcs_get_state,
	.serdes_irq_mapping = mv88e6390_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6097_serdes_irq_enable,
	.serdes_irq_status = mv88e6097_serdes_irq_status,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.rmu_disable = mv88e6085_g1_rmu_disable,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.phylink_validate = mv88e6185_phylink_validate,
	.set_max_frame_size = mv88e6185_g1_set_max_frame_size,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6123_ops = अणु
	/* MV88E6XXX_FAMILY_6165 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_set_frame_mode = mv88e6085_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6185_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.phylink_validate = mv88e6185_phylink_validate,
	.set_max_frame_size = mv88e6185_g1_set_max_frame_size,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6131_ops = अणु
	/* MV88E6XXX_FAMILY_6185 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.set_चयन_mac = mv88e6xxx_g1_set_चयन_mac,
	.phy_पढ़ो = mv88e6185_phy_ppu_पढ़ो,
	.phy_ग_लिखो = mv88e6185_phy_ppu_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6185_port_set_क्रमward_unknown,
	.port_set_mcast_flood = mv88e6185_port_set_शेष_क्रमward,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_upstream_port = mv88e6095_port_set_upstream_port,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_set_छोड़ो = mv88e6185_port_set_छोड़ो,
	.port_get_cmode = mv88e6185_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6185_g2_mgmt_rsvd2cpu,
	.ppu_enable = mv88e6185_g1_ppu_enable,
	.set_cascade_port = mv88e6185_g1_set_cascade_port,
	.ppu_disable = mv88e6185_g1_ppu_disable,
	.reset = mv88e6185_g1_reset,
	.vtu_getnext = mv88e6185_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6185_g1_vtu_loadpurge,
	.phylink_validate = mv88e6185_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6141_ops = अणु
	/* MV88E6XXX_FAMILY_6341 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom8,
	.set_eeprom = mv88e6xxx_g2_set_eeprom8,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6390_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6341_port_set_speed_duplex,
	.port_max_speed_mode = mv88e6341_port_max_speed_mode,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_set_cmode = mv88e6341_port_set_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_strings = mv88e6320_stats_get_strings,
	.stats_get_stats = mv88e6390_stats_get_stats,
	.set_cpu_port = mv88e6390_g1_set_cpu_port,
	.set_egress_port = mv88e6390_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6390_watchकरोg_ops,
	.mgmt_rsvd2cpu =  mv88e6390_g1_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.serdes_घातer = mv88e6390_serdes_घातer,
	.serdes_get_lane = mv88e6341_serdes_get_lane,
	/* Check status रेजिस्टर छोड़ो & lpa रेजिस्टर */
	.serdes_pcs_get_state = mv88e6390_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6390_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6390_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6390_serdes_pcs_link_up,
	.serdes_irq_mapping = mv88e6390_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6390_serdes_irq_enable,
	.serdes_irq_status = mv88e6390_serdes_irq_status,
	.gpio_ops = &mv88e6352_gpio_ops,
	.phylink_validate = mv88e6341_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6161_ops = अणु
	/* MV88E6XXX_FAMILY_6165 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6185_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.avb_ops = &mv88e6165_avb_ops,
	.ptp_ops = &mv88e6165_ptp_ops,
	.phylink_validate = mv88e6185_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6165_ops = अणु
	/* MV88E6XXX_FAMILY_6165 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6165_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6165_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6185_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.avb_ops = &mv88e6165_avb_ops,
	.ptp_ops = &mv88e6165_ptp_ops,
	.phylink_validate = mv88e6185_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6171_ops = अणु
	/* MV88E6XXX_FAMILY_6351 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6352_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.phylink_validate = mv88e6185_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6172_ops = अणु
	/* MV88E6XXX_FAMILY_6352 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom16,
	.set_eeprom = mv88e6xxx_g2_set_eeprom16,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6352_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6352_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_policy = mv88e6352_port_set_policy,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.rmu_disable = mv88e6352_g1_rmu_disable,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.serdes_get_lane = mv88e6352_serdes_get_lane,
	.serdes_pcs_get_state = mv88e6352_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6352_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6352_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6352_serdes_pcs_link_up,
	.serdes_घातer = mv88e6352_serdes_घातer,
	.serdes_get_regs_len = mv88e6352_serdes_get_regs_len,
	.serdes_get_regs = mv88e6352_serdes_get_regs,
	.gpio_ops = &mv88e6352_gpio_ops,
	.phylink_validate = mv88e6352_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6175_ops = अणु
	/* MV88E6XXX_FAMILY_6351 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6352_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.phylink_validate = mv88e6185_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6176_ops = अणु
	/* MV88E6XXX_FAMILY_6352 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom16,
	.set_eeprom = mv88e6xxx_g2_set_eeprom16,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6352_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6352_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_policy = mv88e6352_port_set_policy,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.rmu_disable = mv88e6352_g1_rmu_disable,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.serdes_get_lane = mv88e6352_serdes_get_lane,
	.serdes_pcs_get_state = mv88e6352_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6352_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6352_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6352_serdes_pcs_link_up,
	.serdes_घातer = mv88e6352_serdes_घातer,
	.serdes_irq_mapping = mv88e6352_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6352_serdes_irq_enable,
	.serdes_irq_status = mv88e6352_serdes_irq_status,
	.serdes_get_regs_len = mv88e6352_serdes_get_regs_len,
	.serdes_get_regs = mv88e6352_serdes_get_regs,
	.gpio_ops = &mv88e6352_gpio_ops,
	.phylink_validate = mv88e6352_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6185_ops = अणु
	/* MV88E6XXX_FAMILY_6185 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.set_चयन_mac = mv88e6xxx_g1_set_चयन_mac,
	.phy_पढ़ो = mv88e6185_phy_ppu_पढ़ो,
	.phy_ग_लिखो = mv88e6185_phy_ppu_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6185_port_sync_link,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_set_frame_mode = mv88e6085_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6185_port_set_क्रमward_unknown,
	.port_set_mcast_flood = mv88e6185_port_set_शेष_क्रमward,
	.port_egress_rate_limiting = mv88e6095_port_egress_rate_limiting,
	.port_set_upstream_port = mv88e6095_port_set_upstream_port,
	.port_set_छोड़ो = mv88e6185_port_set_छोड़ो,
	.port_get_cmode = mv88e6185_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6185_g2_mgmt_rsvd2cpu,
	.serdes_घातer = mv88e6185_serdes_घातer,
	.serdes_get_lane = mv88e6185_serdes_get_lane,
	.serdes_pcs_get_state = mv88e6185_serdes_pcs_get_state,
	.set_cascade_port = mv88e6185_g1_set_cascade_port,
	.ppu_enable = mv88e6185_g1_ppu_enable,
	.ppu_disable = mv88e6185_g1_ppu_disable,
	.reset = mv88e6185_g1_reset,
	.vtu_getnext = mv88e6185_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6185_g1_vtu_loadpurge,
	.phylink_validate = mv88e6185_phylink_validate,
	.set_max_frame_size = mv88e6185_g1_set_max_frame_size,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6190_ops = अणु
	/* MV88E6XXX_FAMILY_6390 */
	.setup_errata = mv88e6390_setup_errata,
	.irl_init_all = mv88e6390_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom8,
	.set_eeprom = mv88e6xxx_g2_set_eeprom8,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6390_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6390_port_set_speed_duplex,
	.port_max_speed_mode = mv88e6390_port_max_speed_mode,
	.port_tag_remap = mv88e6390_port_tag_remap,
	.port_set_policy = mv88e6352_port_set_policy,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_छोड़ो_limit = mv88e6390_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_set_cmode = mv88e6390_port_set_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogram = mv88e6390_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_strings = mv88e6320_stats_get_strings,
	.stats_get_stats = mv88e6390_stats_get_stats,
	.set_cpu_port = mv88e6390_g1_set_cpu_port,
	.set_egress_port = mv88e6390_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6390_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6390_g1_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.rmu_disable = mv88e6390_g1_rmu_disable,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6390_g1_vtu_loadpurge,
	.serdes_घातer = mv88e6390_serdes_घातer,
	.serdes_get_lane = mv88e6390_serdes_get_lane,
	/* Check status रेजिस्टर छोड़ो & lpa रेजिस्टर */
	.serdes_pcs_get_state = mv88e6390_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6390_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6390_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6390_serdes_pcs_link_up,
	.serdes_irq_mapping = mv88e6390_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6390_serdes_irq_enable,
	.serdes_irq_status = mv88e6390_serdes_irq_status,
	.serdes_get_strings = mv88e6390_serdes_get_strings,
	.serdes_get_stats = mv88e6390_serdes_get_stats,
	.serdes_get_regs_len = mv88e6390_serdes_get_regs_len,
	.serdes_get_regs = mv88e6390_serdes_get_regs,
	.gpio_ops = &mv88e6352_gpio_ops,
	.phylink_validate = mv88e6390_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6190x_ops = अणु
	/* MV88E6XXX_FAMILY_6390 */
	.setup_errata = mv88e6390_setup_errata,
	.irl_init_all = mv88e6390_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom8,
	.set_eeprom = mv88e6xxx_g2_set_eeprom8,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6390_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6390x_port_set_speed_duplex,
	.port_max_speed_mode = mv88e6390x_port_max_speed_mode,
	.port_tag_remap = mv88e6390_port_tag_remap,
	.port_set_policy = mv88e6352_port_set_policy,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_छोड़ो_limit = mv88e6390_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_set_cmode = mv88e6390x_port_set_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogram = mv88e6390_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_strings = mv88e6320_stats_get_strings,
	.stats_get_stats = mv88e6390_stats_get_stats,
	.set_cpu_port = mv88e6390_g1_set_cpu_port,
	.set_egress_port = mv88e6390_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6390_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6390_g1_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.rmu_disable = mv88e6390_g1_rmu_disable,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6390_g1_vtu_loadpurge,
	.serdes_घातer = mv88e6390_serdes_घातer,
	.serdes_get_lane = mv88e6390x_serdes_get_lane,
	/* Check status रेजिस्टर छोड़ो & lpa रेजिस्टर */
	.serdes_pcs_get_state = mv88e6390_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6390_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6390_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6390_serdes_pcs_link_up,
	.serdes_irq_mapping = mv88e6390_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6390_serdes_irq_enable,
	.serdes_irq_status = mv88e6390_serdes_irq_status,
	.serdes_get_strings = mv88e6390_serdes_get_strings,
	.serdes_get_stats = mv88e6390_serdes_get_stats,
	.serdes_get_regs_len = mv88e6390_serdes_get_regs_len,
	.serdes_get_regs = mv88e6390_serdes_get_regs,
	.gpio_ops = &mv88e6352_gpio_ops,
	.phylink_validate = mv88e6390x_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6191_ops = अणु
	/* MV88E6XXX_FAMILY_6390 */
	.setup_errata = mv88e6390_setup_errata,
	.irl_init_all = mv88e6390_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom8,
	.set_eeprom = mv88e6xxx_g2_set_eeprom8,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6390_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6390_port_set_speed_duplex,
	.port_max_speed_mode = mv88e6390_port_max_speed_mode,
	.port_tag_remap = mv88e6390_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_छोड़ो_limit = mv88e6390_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_set_cmode = mv88e6390_port_set_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogram = mv88e6390_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_strings = mv88e6320_stats_get_strings,
	.stats_get_stats = mv88e6390_stats_get_stats,
	.set_cpu_port = mv88e6390_g1_set_cpu_port,
	.set_egress_port = mv88e6390_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6390_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6390_g1_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.rmu_disable = mv88e6390_g1_rmu_disable,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6390_g1_vtu_loadpurge,
	.serdes_घातer = mv88e6390_serdes_घातer,
	.serdes_get_lane = mv88e6390_serdes_get_lane,
	/* Check status रेजिस्टर छोड़ो & lpa रेजिस्टर */
	.serdes_pcs_get_state = mv88e6390_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6390_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6390_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6390_serdes_pcs_link_up,
	.serdes_irq_mapping = mv88e6390_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6390_serdes_irq_enable,
	.serdes_irq_status = mv88e6390_serdes_irq_status,
	.serdes_get_strings = mv88e6390_serdes_get_strings,
	.serdes_get_stats = mv88e6390_serdes_get_stats,
	.serdes_get_regs_len = mv88e6390_serdes_get_regs_len,
	.serdes_get_regs = mv88e6390_serdes_get_regs,
	.avb_ops = &mv88e6390_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phylink_validate = mv88e6390_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6240_ops = अणु
	/* MV88E6XXX_FAMILY_6352 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom16,
	.set_eeprom = mv88e6xxx_g2_set_eeprom16,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6352_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6352_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_policy = mv88e6352_port_set_policy,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.rmu_disable = mv88e6352_g1_rmu_disable,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.serdes_get_lane = mv88e6352_serdes_get_lane,
	.serdes_pcs_get_state = mv88e6352_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6352_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6352_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6352_serdes_pcs_link_up,
	.serdes_घातer = mv88e6352_serdes_घातer,
	.serdes_irq_mapping = mv88e6352_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6352_serdes_irq_enable,
	.serdes_irq_status = mv88e6352_serdes_irq_status,
	.serdes_get_regs_len = mv88e6352_serdes_get_regs_len,
	.serdes_get_regs = mv88e6352_serdes_get_regs,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6352_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phylink_validate = mv88e6352_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6250_ops = अणु
	/* MV88E6XXX_FAMILY_6250 */
	.ieee_pri_map = mv88e6250_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom16,
	.set_eeprom = mv88e6xxx_g2_set_eeprom16,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6352_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6250_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6250_stats_get_sset_count,
	.stats_get_strings = mv88e6250_stats_get_strings,
	.stats_get_stats = mv88e6250_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6250_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6250_g1_reset,
	.vtu_getnext = mv88e6185_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6185_g1_vtu_loadpurge,
	.avb_ops = &mv88e6352_avb_ops,
	.ptp_ops = &mv88e6250_ptp_ops,
	.phylink_validate = mv88e6065_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6290_ops = अणु
	/* MV88E6XXX_FAMILY_6390 */
	.setup_errata = mv88e6390_setup_errata,
	.irl_init_all = mv88e6390_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom8,
	.set_eeprom = mv88e6xxx_g2_set_eeprom8,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6390_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6390_port_set_speed_duplex,
	.port_max_speed_mode = mv88e6390_port_max_speed_mode,
	.port_tag_remap = mv88e6390_port_tag_remap,
	.port_set_policy = mv88e6352_port_set_policy,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_छोड़ो_limit = mv88e6390_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_set_cmode = mv88e6390_port_set_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogram = mv88e6390_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_strings = mv88e6320_stats_get_strings,
	.stats_get_stats = mv88e6390_stats_get_stats,
	.set_cpu_port = mv88e6390_g1_set_cpu_port,
	.set_egress_port = mv88e6390_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6390_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6390_g1_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.rmu_disable = mv88e6390_g1_rmu_disable,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6390_g1_vtu_loadpurge,
	.serdes_घातer = mv88e6390_serdes_घातer,
	.serdes_get_lane = mv88e6390_serdes_get_lane,
	/* Check status रेजिस्टर छोड़ो & lpa रेजिस्टर */
	.serdes_pcs_get_state = mv88e6390_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6390_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6390_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6390_serdes_pcs_link_up,
	.serdes_irq_mapping = mv88e6390_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6390_serdes_irq_enable,
	.serdes_irq_status = mv88e6390_serdes_irq_status,
	.serdes_get_strings = mv88e6390_serdes_get_strings,
	.serdes_get_stats = mv88e6390_serdes_get_stats,
	.serdes_get_regs_len = mv88e6390_serdes_get_regs_len,
	.serdes_get_regs = mv88e6390_serdes_get_regs,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6390_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phylink_validate = mv88e6390_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6320_ops = अणु
	/* MV88E6XXX_FAMILY_6320 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom16,
	.set_eeprom = mv88e6xxx_g2_set_eeprom16,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_strings = mv88e6320_stats_get_strings,
	.stats_get_stats = mv88e6320_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6390_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.vtu_getnext = mv88e6185_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6185_g1_vtu_loadpurge,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6352_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phylink_validate = mv88e6185_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6321_ops = अणु
	/* MV88E6XXX_FAMILY_6320 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom16,
	.set_eeprom = mv88e6xxx_g2_set_eeprom16,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_strings = mv88e6320_stats_get_strings,
	.stats_get_stats = mv88e6320_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6390_watchकरोg_ops,
	.reset = mv88e6352_g1_reset,
	.vtu_getnext = mv88e6185_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6185_g1_vtu_loadpurge,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6352_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phylink_validate = mv88e6185_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6341_ops = अणु
	/* MV88E6XXX_FAMILY_6341 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom8,
	.set_eeprom = mv88e6xxx_g2_set_eeprom8,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6390_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6341_port_set_speed_duplex,
	.port_max_speed_mode = mv88e6341_port_max_speed_mode,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_set_cmode = mv88e6341_port_set_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_strings = mv88e6320_stats_get_strings,
	.stats_get_stats = mv88e6390_stats_get_stats,
	.set_cpu_port = mv88e6390_g1_set_cpu_port,
	.set_egress_port = mv88e6390_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6390_watchकरोg_ops,
	.mgmt_rsvd2cpu =  mv88e6390_g1_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.serdes_घातer = mv88e6390_serdes_घातer,
	.serdes_get_lane = mv88e6341_serdes_get_lane,
	/* Check status रेजिस्टर छोड़ो & lpa रेजिस्टर */
	.serdes_pcs_get_state = mv88e6390_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6390_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6390_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6390_serdes_pcs_link_up,
	.serdes_irq_mapping = mv88e6390_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6390_serdes_irq_enable,
	.serdes_irq_status = mv88e6390_serdes_irq_status,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6390_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phylink_validate = mv88e6341_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6350_ops = अणु
	/* MV88E6XXX_FAMILY_6351 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6352_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.phylink_validate = mv88e6185_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6351_ops = अणु
	/* MV88E6XXX_FAMILY_6351 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6352_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6185_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.avb_ops = &mv88e6352_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phylink_validate = mv88e6185_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6352_ops = अणु
	/* MV88E6XXX_FAMILY_6352 */
	.ieee_pri_map = mv88e6085_g1_ieee_pri_map,
	.ip_pri_map = mv88e6085_g1_ip_pri_map,
	.irl_init_all = mv88e6352_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom16,
	.set_eeprom = mv88e6xxx_g2_set_eeprom16,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6352_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6352_port_set_speed_duplex,
	.port_tag_remap = mv88e6095_port_tag_remap,
	.port_set_policy = mv88e6352_port_set_policy,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6097_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogram = mv88e6095_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_strings = mv88e6095_stats_get_strings,
	.stats_get_stats = mv88e6095_stats_get_stats,
	.set_cpu_port = mv88e6095_g1_set_cpu_port,
	.set_egress_port = mv88e6095_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6097_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6352_g2_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.rmu_disable = mv88e6352_g1_rmu_disable,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6352_g1_vtu_loadpurge,
	.serdes_get_lane = mv88e6352_serdes_get_lane,
	.serdes_pcs_get_state = mv88e6352_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6352_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6352_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6352_serdes_pcs_link_up,
	.serdes_घातer = mv88e6352_serdes_घातer,
	.serdes_irq_mapping = mv88e6352_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6352_serdes_irq_enable,
	.serdes_irq_status = mv88e6352_serdes_irq_status,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6352_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.serdes_get_sset_count = mv88e6352_serdes_get_sset_count,
	.serdes_get_strings = mv88e6352_serdes_get_strings,
	.serdes_get_stats = mv88e6352_serdes_get_stats,
	.serdes_get_regs_len = mv88e6352_serdes_get_regs_len,
	.serdes_get_regs = mv88e6352_serdes_get_regs,
	.phylink_validate = mv88e6352_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6390_ops = अणु
	/* MV88E6XXX_FAMILY_6390 */
	.setup_errata = mv88e6390_setup_errata,
	.irl_init_all = mv88e6390_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom8,
	.set_eeprom = mv88e6xxx_g2_set_eeprom8,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6390_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6390_port_set_speed_duplex,
	.port_max_speed_mode = mv88e6390_port_max_speed_mode,
	.port_tag_remap = mv88e6390_port_tag_remap,
	.port_set_policy = mv88e6352_port_set_policy,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6390_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_set_cmode = mv88e6390_port_set_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogram = mv88e6390_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_strings = mv88e6320_stats_get_strings,
	.stats_get_stats = mv88e6390_stats_get_stats,
	.set_cpu_port = mv88e6390_g1_set_cpu_port,
	.set_egress_port = mv88e6390_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6390_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6390_g1_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.rmu_disable = mv88e6390_g1_rmu_disable,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6390_g1_vtu_loadpurge,
	.serdes_घातer = mv88e6390_serdes_घातer,
	.serdes_get_lane = mv88e6390_serdes_get_lane,
	/* Check status रेजिस्टर छोड़ो & lpa रेजिस्टर */
	.serdes_pcs_get_state = mv88e6390_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6390_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6390_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6390_serdes_pcs_link_up,
	.serdes_irq_mapping = mv88e6390_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6390_serdes_irq_enable,
	.serdes_irq_status = mv88e6390_serdes_irq_status,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6390_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.serdes_get_sset_count = mv88e6390_serdes_get_sset_count,
	.serdes_get_strings = mv88e6390_serdes_get_strings,
	.serdes_get_stats = mv88e6390_serdes_get_stats,
	.serdes_get_regs_len = mv88e6390_serdes_get_regs_len,
	.serdes_get_regs = mv88e6390_serdes_get_regs,
	.phylink_validate = mv88e6390_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6390x_ops = अणु
	/* MV88E6XXX_FAMILY_6390 */
	.setup_errata = mv88e6390_setup_errata,
	.irl_init_all = mv88e6390_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom8,
	.set_eeprom = mv88e6xxx_g2_set_eeprom8,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6390_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6390x_port_set_speed_duplex,
	.port_max_speed_mode = mv88e6390x_port_max_speed_mode,
	.port_tag_remap = mv88e6390_port_tag_remap,
	.port_set_policy = mv88e6352_port_set_policy,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6351_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6390_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_set_cmode = mv88e6390x_port_set_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogram = mv88e6390_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_strings = mv88e6320_stats_get_strings,
	.stats_get_stats = mv88e6390_stats_get_stats,
	.set_cpu_port = mv88e6390_g1_set_cpu_port,
	.set_egress_port = mv88e6390_g1_set_egress_port,
	.watchकरोg_ops = &mv88e6390_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6390_g1_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.rmu_disable = mv88e6390_g1_rmu_disable,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6390_g1_vtu_loadpurge,
	.serdes_घातer = mv88e6390_serdes_घातer,
	.serdes_get_lane = mv88e6390x_serdes_get_lane,
	.serdes_pcs_get_state = mv88e6390_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6390_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6390_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6390_serdes_pcs_link_up,
	.serdes_irq_mapping = mv88e6390_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6390_serdes_irq_enable,
	.serdes_irq_status = mv88e6390_serdes_irq_status,
	.serdes_get_sset_count = mv88e6390_serdes_get_sset_count,
	.serdes_get_strings = mv88e6390_serdes_get_strings,
	.serdes_get_stats = mv88e6390_serdes_get_stats,
	.serdes_get_regs_len = mv88e6390_serdes_get_regs_len,
	.serdes_get_regs = mv88e6390_serdes_get_regs,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6390_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phylink_validate = mv88e6390x_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_ops mv88e6393x_ops = अणु
	/* MV88E6XXX_FAMILY_6393 */
	.setup_errata = mv88e6393x_serdes_setup_errata,
	.irl_init_all = mv88e6390_g2_irl_init_all,
	.get_eeprom = mv88e6xxx_g2_get_eeprom8,
	.set_eeprom = mv88e6xxx_g2_set_eeprom8,
	.set_चयन_mac = mv88e6xxx_g2_set_चयन_mac,
	.phy_पढ़ो = mv88e6xxx_g2_smi_phy_पढ़ो,
	.phy_ग_लिखो = mv88e6xxx_g2_smi_phy_ग_लिखो,
	.port_set_link = mv88e6xxx_port_set_link,
	.port_sync_link = mv88e6xxx_port_sync_link,
	.port_set_rgmii_delay = mv88e6390_port_set_rgmii_delay,
	.port_set_speed_duplex = mv88e6393x_port_set_speed_duplex,
	.port_max_speed_mode = mv88e6393x_port_max_speed_mode,
	.port_tag_remap = mv88e6390_port_tag_remap,
	.port_set_policy = mv88e6393x_port_set_policy,
	.port_set_frame_mode = mv88e6351_port_set_frame_mode,
	.port_set_ucast_flood = mv88e6352_port_set_ucast_flood,
	.port_set_mcast_flood = mv88e6352_port_set_mcast_flood,
	.port_set_ether_type = mv88e6393x_port_set_ether_type,
	.port_set_jumbo_size = mv88e6165_port_set_jumbo_size,
	.port_egress_rate_limiting = mv88e6097_port_egress_rate_limiting,
	.port_छोड़ो_limit = mv88e6390_port_छोड़ो_limit,
	.port_disable_learn_limit = mv88e6xxx_port_disable_learn_limit,
	.port_disable_pri_override = mv88e6xxx_port_disable_pri_override,
	.port_get_cmode = mv88e6352_port_get_cmode,
	.port_set_cmode = mv88e6393x_port_set_cmode,
	.port_setup_message_port = mv88e6xxx_setup_message_port,
	.port_set_upstream_port = mv88e6393x_port_set_upstream_port,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogram = mv88e6390_g1_stats_set_histogram,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_strings = mv88e6320_stats_get_strings,
	.stats_get_stats = mv88e6390_stats_get_stats,
	/* .set_cpu_port is missing because this family करोes not support a global
	 * CPU port, only per port CPU port which is set via
	 * .port_set_upstream_port method.
	 */
	.set_egress_port = mv88e6393x_set_egress_port,
	.watchकरोg_ops = &mv88e6390_watchकरोg_ops,
	.mgmt_rsvd2cpu = mv88e6393x_port_mgmt_rsvd2cpu,
	.pot_clear = mv88e6xxx_g2_pot_clear,
	.reset = mv88e6352_g1_reset,
	.rmu_disable = mv88e6390_g1_rmu_disable,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_loadpurge = mv88e6390_g1_vtu_loadpurge,
	.serdes_घातer = mv88e6393x_serdes_घातer,
	.serdes_get_lane = mv88e6393x_serdes_get_lane,
	.serdes_pcs_get_state = mv88e6393x_serdes_pcs_get_state,
	.serdes_pcs_config = mv88e6390_serdes_pcs_config,
	.serdes_pcs_an_restart = mv88e6390_serdes_pcs_an_restart,
	.serdes_pcs_link_up = mv88e6390_serdes_pcs_link_up,
	.serdes_irq_mapping = mv88e6390_serdes_irq_mapping,
	.serdes_irq_enable = mv88e6393x_serdes_irq_enable,
	.serdes_irq_status = mv88e6393x_serdes_irq_status,
	/* TODO: serdes stats */
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6390_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phylink_validate = mv88e6393x_phylink_validate,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_info mv88e6xxx_table[] = अणु
	[MV88E6085] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6085,
		.family = MV88E6XXX_FAMILY_6097,
		.name = "Marvell 88E6085",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 10,
		.num_पूर्णांकernal_phys = 5,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 8,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.ops = &mv88e6085_ops,
	पूर्ण,

	[MV88E6095] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6095,
		.family = MV88E6XXX_FAMILY_6095,
		.name = "Marvell 88E6095/88E6095F",
		.num_databases = 256,
		.num_macs = 8192,
		.num_ports = 11,
		.num_पूर्णांकernal_phys = 0,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 8,
		.atu_move_port_mask = 0xf,
		.multi_chip = true,
		.ops = &mv88e6095_ops,
	पूर्ण,

	[MV88E6097] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6097,
		.family = MV88E6XXX_FAMILY_6097,
		.name = "Marvell 88E6097/88E6097F",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 11,
		.num_पूर्णांकernal_phys = 8,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 8,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ops = &mv88e6097_ops,
	पूर्ण,

	[MV88E6123] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6123,
		.family = MV88E6XXX_FAMILY_6165,
		.name = "Marvell 88E6123",
		.num_databases = 4096,
		.num_macs = 1024,
		.num_ports = 3,
		.num_पूर्णांकernal_phys = 5,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ops = &mv88e6123_ops,
	पूर्ण,

	[MV88E6131] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6131,
		.family = MV88E6XXX_FAMILY_6185,
		.name = "Marvell 88E6131",
		.num_databases = 256,
		.num_macs = 8192,
		.num_ports = 8,
		.num_पूर्णांकernal_phys = 0,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.atu_move_port_mask = 0xf,
		.multi_chip = true,
		.ops = &mv88e6131_ops,
	पूर्ण,

	[MV88E6141] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6141,
		.family = MV88E6XXX_FAMILY_6341,
		.name = "Marvell 88E6141",
		.num_databases = 4096,
		.num_macs = 2048,
		.num_ports = 6,
		.num_पूर्णांकernal_phys = 5,
		.num_gpio = 11,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x10,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 3750,
		.atu_move_port_mask = 0x1f,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ops = &mv88e6141_ops,
	पूर्ण,

	[MV88E6161] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6161,
		.family = MV88E6XXX_FAMILY_6165,
		.name = "Marvell 88E6161",
		.num_databases = 4096,
		.num_macs = 1024,
		.num_ports = 6,
		.num_पूर्णांकernal_phys = 5,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ptp_support = true,
		.ops = &mv88e6161_ops,
	पूर्ण,

	[MV88E6165] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6165,
		.family = MV88E6XXX_FAMILY_6165,
		.name = "Marvell 88E6165",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 6,
		.num_पूर्णांकernal_phys = 0,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.ptp_support = true,
		.ops = &mv88e6165_ops,
	पूर्ण,

	[MV88E6171] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6171,
		.family = MV88E6XXX_FAMILY_6351,
		.name = "Marvell 88E6171",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 7,
		.num_पूर्णांकernal_phys = 5,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ops = &mv88e6171_ops,
	पूर्ण,

	[MV88E6172] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6172,
		.family = MV88E6XXX_FAMILY_6352,
		.name = "Marvell 88E6172",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 7,
		.num_पूर्णांकernal_phys = 5,
		.num_gpio = 15,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ops = &mv88e6172_ops,
	पूर्ण,

	[MV88E6175] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6175,
		.family = MV88E6XXX_FAMILY_6351,
		.name = "Marvell 88E6175",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 7,
		.num_पूर्णांकernal_phys = 5,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ops = &mv88e6175_ops,
	पूर्ण,

	[MV88E6176] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6176,
		.family = MV88E6XXX_FAMILY_6352,
		.name = "Marvell 88E6176",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 7,
		.num_पूर्णांकernal_phys = 5,
		.num_gpio = 15,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ops = &mv88e6176_ops,
	पूर्ण,

	[MV88E6185] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6185,
		.family = MV88E6XXX_FAMILY_6185,
		.name = "Marvell 88E6185",
		.num_databases = 256,
		.num_macs = 8192,
		.num_ports = 10,
		.num_पूर्णांकernal_phys = 0,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 8,
		.atu_move_port_mask = 0xf,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ops = &mv88e6185_ops,
	पूर्ण,

	[MV88E6190] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6190,
		.family = MV88E6XXX_FAMILY_6390,
		.name = "Marvell 88E6190",
		.num_databases = 4096,
		.num_macs = 16384,
		.num_ports = 11,	/* 10 + Z80 */
		.num_पूर्णांकernal_phys = 9,
		.num_gpio = 16,
		.max_vid = 8191,
		.port_base_addr = 0x0,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 3750,
		.g1_irqs = 9,
		.g2_irqs = 14,
		.pvt = true,
		.multi_chip = true,
		.atu_move_port_mask = 0x1f,
		.ops = &mv88e6190_ops,
	पूर्ण,

	[MV88E6190X] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6190X,
		.family = MV88E6XXX_FAMILY_6390,
		.name = "Marvell 88E6190X",
		.num_databases = 4096,
		.num_macs = 16384,
		.num_ports = 11,	/* 10 + Z80 */
		.num_पूर्णांकernal_phys = 9,
		.num_gpio = 16,
		.max_vid = 8191,
		.port_base_addr = 0x0,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 3750,
		.g1_irqs = 9,
		.g2_irqs = 14,
		.atu_move_port_mask = 0x1f,
		.pvt = true,
		.multi_chip = true,
		.ops = &mv88e6190x_ops,
	पूर्ण,

	[MV88E6191] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6191,
		.family = MV88E6XXX_FAMILY_6390,
		.name = "Marvell 88E6191",
		.num_databases = 4096,
		.num_macs = 16384,
		.num_ports = 11,	/* 10 + Z80 */
		.num_पूर्णांकernal_phys = 9,
		.max_vid = 8191,
		.port_base_addr = 0x0,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 3750,
		.g1_irqs = 9,
		.g2_irqs = 14,
		.atu_move_port_mask = 0x1f,
		.pvt = true,
		.multi_chip = true,
		.ptp_support = true,
		.ops = &mv88e6191_ops,
	पूर्ण,

	[MV88E6191X] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6191X,
		.family = MV88E6XXX_FAMILY_6393,
		.name = "Marvell 88E6191X",
		.num_databases = 4096,
		.num_ports = 11,	/* 10 + Z80 */
		.num_पूर्णांकernal_phys = 9,
		.max_vid = 8191,
		.port_base_addr = 0x0,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 3750,
		.g1_irqs = 10,
		.g2_irqs = 14,
		.atu_move_port_mask = 0x1f,
		.pvt = true,
		.multi_chip = true,
		.ptp_support = true,
		.ops = &mv88e6393x_ops,
	पूर्ण,

	[MV88E6193X] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6193X,
		.family = MV88E6XXX_FAMILY_6393,
		.name = "Marvell 88E6193X",
		.num_databases = 4096,
		.num_ports = 11,	/* 10 + Z80 */
		.num_पूर्णांकernal_phys = 9,
		.max_vid = 8191,
		.port_base_addr = 0x0,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 3750,
		.g1_irqs = 10,
		.g2_irqs = 14,
		.atu_move_port_mask = 0x1f,
		.pvt = true,
		.multi_chip = true,
		.ptp_support = true,
		.ops = &mv88e6393x_ops,
	पूर्ण,

	[MV88E6220] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6220,
		.family = MV88E6XXX_FAMILY_6250,
		.name = "Marvell 88E6220",
		.num_databases = 64,

		/* Ports 2-4 are not routed to pins
		 * => usable ports 0, 1, 5, 6
		 */
		.num_ports = 7,
		.num_पूर्णांकernal_phys = 2,
		.invalid_port_mask = BIT(2) | BIT(3) | BIT(4),
		.max_vid = 4095,
		.port_base_addr = 0x08,
		.phy_base_addr = 0x00,
		.global1_addr = 0x0f,
		.global2_addr = 0x07,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.dual_chip = true,
		.ptp_support = true,
		.ops = &mv88e6250_ops,
	पूर्ण,

	[MV88E6240] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6240,
		.family = MV88E6XXX_FAMILY_6352,
		.name = "Marvell 88E6240",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 7,
		.num_पूर्णांकernal_phys = 5,
		.num_gpio = 15,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ptp_support = true,
		.ops = &mv88e6240_ops,
	पूर्ण,

	[MV88E6250] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6250,
		.family = MV88E6XXX_FAMILY_6250,
		.name = "Marvell 88E6250",
		.num_databases = 64,
		.num_ports = 7,
		.num_पूर्णांकernal_phys = 5,
		.max_vid = 4095,
		.port_base_addr = 0x08,
		.phy_base_addr = 0x00,
		.global1_addr = 0x0f,
		.global2_addr = 0x07,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.dual_chip = true,
		.ptp_support = true,
		.ops = &mv88e6250_ops,
	पूर्ण,

	[MV88E6290] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6290,
		.family = MV88E6XXX_FAMILY_6390,
		.name = "Marvell 88E6290",
		.num_databases = 4096,
		.num_ports = 11,	/* 10 + Z80 */
		.num_पूर्णांकernal_phys = 9,
		.num_gpio = 16,
		.max_vid = 8191,
		.port_base_addr = 0x0,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 3750,
		.g1_irqs = 9,
		.g2_irqs = 14,
		.atu_move_port_mask = 0x1f,
		.pvt = true,
		.multi_chip = true,
		.ptp_support = true,
		.ops = &mv88e6290_ops,
	पूर्ण,

	[MV88E6320] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6320,
		.family = MV88E6XXX_FAMILY_6320,
		.name = "Marvell 88E6320",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 7,
		.num_पूर्णांकernal_phys = 5,
		.num_gpio = 15,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 8,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ptp_support = true,
		.ops = &mv88e6320_ops,
	पूर्ण,

	[MV88E6321] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6321,
		.family = MV88E6XXX_FAMILY_6320,
		.name = "Marvell 88E6321",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 7,
		.num_पूर्णांकernal_phys = 5,
		.num_gpio = 15,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 8,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ptp_support = true,
		.ops = &mv88e6321_ops,
	पूर्ण,

	[MV88E6341] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6341,
		.family = MV88E6XXX_FAMILY_6341,
		.name = "Marvell 88E6341",
		.num_databases = 4096,
		.num_macs = 2048,
		.num_पूर्णांकernal_phys = 5,
		.num_ports = 6,
		.num_gpio = 11,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x10,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 3750,
		.atu_move_port_mask = 0x1f,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ptp_support = true,
		.ops = &mv88e6341_ops,
	पूर्ण,

	[MV88E6350] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6350,
		.family = MV88E6XXX_FAMILY_6351,
		.name = "Marvell 88E6350",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 7,
		.num_पूर्णांकernal_phys = 5,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ops = &mv88e6350_ops,
	पूर्ण,

	[MV88E6351] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6351,
		.family = MV88E6XXX_FAMILY_6351,
		.name = "Marvell 88E6351",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 7,
		.num_पूर्णांकernal_phys = 5,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ops = &mv88e6351_ops,
	पूर्ण,

	[MV88E6352] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6352,
		.family = MV88E6XXX_FAMILY_6352,
		.name = "Marvell 88E6352",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_ports = 7,
		.num_पूर्णांकernal_phys = 5,
		.num_gpio = 15,
		.max_vid = 4095,
		.port_base_addr = 0x10,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 15000,
		.g1_irqs = 9,
		.g2_irqs = 10,
		.atu_move_port_mask = 0xf,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_SUPPORTED,
		.ptp_support = true,
		.ops = &mv88e6352_ops,
	पूर्ण,
	[MV88E6390] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6390,
		.family = MV88E6XXX_FAMILY_6390,
		.name = "Marvell 88E6390",
		.num_databases = 4096,
		.num_macs = 16384,
		.num_ports = 11,	/* 10 + Z80 */
		.num_पूर्णांकernal_phys = 9,
		.num_gpio = 16,
		.max_vid = 8191,
		.port_base_addr = 0x0,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 3750,
		.g1_irqs = 9,
		.g2_irqs = 14,
		.atu_move_port_mask = 0x1f,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_UNDOCUMENTED,
		.ptp_support = true,
		.ops = &mv88e6390_ops,
	पूर्ण,
	[MV88E6390X] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6390X,
		.family = MV88E6XXX_FAMILY_6390,
		.name = "Marvell 88E6390X",
		.num_databases = 4096,
		.num_macs = 16384,
		.num_ports = 11,	/* 10 + Z80 */
		.num_पूर्णांकernal_phys = 9,
		.num_gpio = 16,
		.max_vid = 8191,
		.port_base_addr = 0x0,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 3750,
		.g1_irqs = 9,
		.g2_irqs = 14,
		.atu_move_port_mask = 0x1f,
		.pvt = true,
		.multi_chip = true,
		.edsa_support = MV88E6XXX_EDSA_UNDOCUMENTED,
		.ptp_support = true,
		.ops = &mv88e6390x_ops,
	पूर्ण,

	[MV88E6393X] = अणु
		.prod_num = MV88E6XXX_PORT_SWITCH_ID_PROD_6393X,
		.family = MV88E6XXX_FAMILY_6393,
		.name = "Marvell 88E6393X",
		.num_databases = 4096,
		.num_ports = 11,	/* 10 + Z80 */
		.num_पूर्णांकernal_phys = 9,
		.max_vid = 8191,
		.port_base_addr = 0x0,
		.phy_base_addr = 0x0,
		.global1_addr = 0x1b,
		.global2_addr = 0x1c,
		.age_समय_coeff = 3750,
		.g1_irqs = 10,
		.g2_irqs = 14,
		.atu_move_port_mask = 0x1f,
		.pvt = true,
		.multi_chip = true,
		.ptp_support = true,
		.ops = &mv88e6393x_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mv88e6xxx_info *mv88e6xxx_lookup_info(अचिन्हित पूर्णांक prod_num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mv88e6xxx_table); ++i)
		अगर (mv88e6xxx_table[i].prod_num == prod_num)
			वापस &mv88e6xxx_table[i];

	वापस शून्य;
पूर्ण

अटल पूर्णांक mv88e6xxx_detect(काष्ठा mv88e6xxx_chip *chip)
अणु
	स्थिर काष्ठा mv88e6xxx_info *info;
	अचिन्हित पूर्णांक prod_num, rev;
	u16 id;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_पढ़ो(chip, 0, MV88E6XXX_PORT_SWITCH_ID, &id);
	mv88e6xxx_reg_unlock(chip);
	अगर (err)
		वापस err;

	prod_num = id & MV88E6XXX_PORT_SWITCH_ID_PROD_MASK;
	rev = id & MV88E6XXX_PORT_SWITCH_ID_REV_MASK;

	info = mv88e6xxx_lookup_info(prod_num);
	अगर (!info)
		वापस -ENODEV;

	/* Update the compatible info with the probed one */
	chip->info = info;

	dev_info(chip->dev, "switch 0x%x detected: %s, revision %u\n",
		 chip->info->prod_num, chip->info->name, rev);

	वापस 0;
पूर्ण

अटल काष्ठा mv88e6xxx_chip *mv88e6xxx_alloc_chip(काष्ठा device *dev)
अणु
	काष्ठा mv88e6xxx_chip *chip;

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस शून्य;

	chip->dev = dev;

	mutex_init(&chip->reg_lock);
	INIT_LIST_HEAD(&chip->mdios);
	idr_init(&chip->policies);

	वापस chip;
पूर्ण

अटल क्रमागत dsa_tag_protocol mv88e6xxx_get_tag_protocol(काष्ठा dsa_चयन *ds,
							पूर्णांक port,
							क्रमागत dsa_tag_protocol m)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;

	वापस chip->tag_protocol;
पूर्ण

अटल पूर्णांक mv88e6xxx_change_tag_protocol(काष्ठा dsa_चयन *ds, पूर्णांक port,
					 क्रमागत dsa_tag_protocol proto)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	क्रमागत dsa_tag_protocol old_protocol;
	पूर्णांक err;

	चयन (proto) अणु
	हाल DSA_TAG_PROTO_EDSA:
		चयन (chip->info->edsa_support) अणु
		हाल MV88E6XXX_EDSA_UNSUPPORTED:
			वापस -EPROTONOSUPPORT;
		हाल MV88E6XXX_EDSA_UNDOCUMENTED:
			dev_warn(chip->dev, "Relying on undocumented EDSA tagging behavior\n");
			fallthrough;
		हाल MV88E6XXX_EDSA_SUPPORTED:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DSA_TAG_PROTO_DSA:
		अवरोध;
	शेष:
		वापस -EPROTONOSUPPORT;
	पूर्ण

	old_protocol = chip->tag_protocol;
	chip->tag_protocol = proto;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_setup_port_mode(chip, port);
	mv88e6xxx_reg_unlock(chip);

	अगर (err)
		chip->tag_protocol = old_protocol;

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_mdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_db_load_purge(chip, port, mdb->addr, mdb->vid,
					   MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_mdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_db_load_purge(chip, port, mdb->addr, mdb->vid, 0);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_mirror_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     काष्ठा dsa_mall_mirror_tc_entry *mirror,
				     bool ingress)
अणु
	क्रमागत mv88e6xxx_egress_direction direction = ingress ?
						MV88E6XXX_EGRESS_सूची_INGRESS :
						MV88E6XXX_EGRESS_सूची_EGRESS;
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	bool other_mirrors = false;
	पूर्णांक i;
	पूर्णांक err;

	mutex_lock(&chip->reg_lock);
	अगर ((ingress ? chip->ingress_dest_port : chip->egress_dest_port) !=
	    mirror->to_local_port) अणु
		क्रम (i = 0; i < mv88e6xxx_num_ports(chip); i++)
			other_mirrors |= ingress ?
					 chip->ports[i].mirror_ingress :
					 chip->ports[i].mirror_egress;

		/* Can't change egress port when other mirror is active */
		अगर (other_mirrors) अणु
			err = -EBUSY;
			जाओ out;
		पूर्ण

		err = mv88e6xxx_set_egress_port(chip, direction,
						mirror->to_local_port);
		अगर (err)
			जाओ out;
	पूर्ण

	err = mv88e6xxx_port_set_mirror(chip, port, direction, true);
out:
	mutex_unlock(&chip->reg_lock);

	वापस err;
पूर्ण

अटल व्योम mv88e6xxx_port_mirror_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      काष्ठा dsa_mall_mirror_tc_entry *mirror)
अणु
	क्रमागत mv88e6xxx_egress_direction direction = mirror->ingress ?
						MV88E6XXX_EGRESS_सूची_INGRESS :
						MV88E6XXX_EGRESS_सूची_EGRESS;
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	bool other_mirrors = false;
	पूर्णांक i;

	mutex_lock(&chip->reg_lock);
	अगर (mv88e6xxx_port_set_mirror(chip, port, direction, false))
		dev_err(ds->dev, "p%d: failed to disable mirroring\n", port);

	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); i++)
		other_mirrors |= mirror->ingress ?
				 chip->ports[i].mirror_ingress :
				 chip->ports[i].mirror_egress;

	/* Reset egress port when no other mirror is active */
	अगर (!other_mirrors) अणु
		अगर (mv88e6xxx_set_egress_port(chip, direction,
					      dsa_upstream_port(ds, port)))
			dev_err(ds->dev, "failed to set egress port\n");
	पूर्ण

	mutex_unlock(&chip->reg_lock);
पूर्ण

अटल पूर्णांक mv88e6xxx_port_pre_bridge_flags(काष्ठा dsa_चयन *ds, पूर्णांक port,
					   काष्ठा चयनdev_brport_flags flags,
					   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	स्थिर काष्ठा mv88e6xxx_ops *ops;

	अगर (flags.mask & ~(BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD |
			   BR_BCAST_FLOOD))
		वापस -EINVAL;

	ops = chip->info->ops;

	अगर ((flags.mask & BR_FLOOD) && !ops->port_set_ucast_flood)
		वापस -EINVAL;

	अगर ((flags.mask & BR_MCAST_FLOOD) && !ops->port_set_mcast_flood)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_bridge_flags(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       काष्ठा चयनdev_brport_flags flags,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	bool करो_fast_age = false;
	पूर्णांक err = -EOPNOTSUPP;

	mv88e6xxx_reg_lock(chip);

	अगर (flags.mask & BR_LEARNING) अणु
		bool learning = !!(flags.val & BR_LEARNING);
		u16 pav = learning ? (1 << port) : 0;

		err = mv88e6xxx_port_set_assoc_vector(chip, port, pav);
		अगर (err)
			जाओ out;

		अगर (!learning)
			करो_fast_age = true;
	पूर्ण

	अगर (flags.mask & BR_FLOOD) अणु
		bool unicast = !!(flags.val & BR_FLOOD);

		err = chip->info->ops->port_set_ucast_flood(chip, port,
							    unicast);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (flags.mask & BR_MCAST_FLOOD) अणु
		bool multicast = !!(flags.val & BR_MCAST_FLOOD);

		err = chip->info->ops->port_set_mcast_flood(chip, port,
							    multicast);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (flags.mask & BR_BCAST_FLOOD) अणु
		bool broadcast = !!(flags.val & BR_BCAST_FLOOD);

		err = mv88e6xxx_port_broadcast_sync(chip, port, broadcast);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	mv88e6xxx_reg_unlock(chip);

	अगर (करो_fast_age)
		mv88e6xxx_port_fast_age(ds, port);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_set_mrouter(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      bool mrouter,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	अगर (!chip->info->ops->port_set_mcast_flood)
		वापस -EOPNOTSUPP;

	mv88e6xxx_reg_lock(chip);
	err = chip->info->ops->port_set_mcast_flood(chip, port, mrouter);
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल bool mv88e6xxx_lag_can_offload(काष्ठा dsa_चयन *ds,
				      काष्ठा net_device *lag,
				      काष्ठा netdev_lag_upper_info *info)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	काष्ठा dsa_port *dp;
	पूर्णांक id, members = 0;

	अगर (!mv88e6xxx_has_lag(chip))
		वापस false;

	id = dsa_lag_id(ds->dst, lag);
	अगर (id < 0 || id >= ds->num_lag_ids)
		वापस false;

	dsa_lag_क्रमeach_port(dp, ds->dst, lag)
		/* Includes the port joining the LAG */
		members++;

	अगर (members > 8)
		वापस false;

	/* We could potentially relax this to include active
	 * backup in the future.
	 */
	अगर (info->tx_type != NETDEV_LAG_TX_TYPE_HASH)
		वापस false;

	/* Ideally we would also validate that the hash type matches
	 * the hardware. Alas, this is always set to unknown on team
	 * पूर्णांकerfaces.
	 */
	वापस true;
पूर्ण

अटल पूर्णांक mv88e6xxx_lag_sync_map(काष्ठा dsa_चयन *ds, काष्ठा net_device *lag)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	काष्ठा dsa_port *dp;
	u16 map = 0;
	पूर्णांक id;

	id = dsa_lag_id(ds->dst, lag);

	/* Build the map of all ports to distribute flows destined क्रम
	 * this LAG. This can be either a local user port, or a DSA
	 * port अगर the LAG port is on a remote chip.
	 */
	dsa_lag_क्रमeach_port(dp, ds->dst, lag)
		map |= BIT(dsa_towards_port(ds, dp->ds->index, dp->index));

	वापस mv88e6xxx_g2_trunk_mapping_ग_लिखो(chip, id, map);
पूर्ण

अटल स्थिर u8 mv88e6xxx_lag_mask_table[8][8] = अणु
	/* Row number corresponds to the number of active members in a
	 * LAG. Each column states which of the eight hash buckets are
	 * mapped to the column:th port in the LAG.
	 *
	 * Example: In a LAG with three active ports, the second port
	 * ([2][1]) would be selected क्रम traffic mapped to buckets
	 * 3,4,5 (0x38).
	 */
	अणु 0xff,    0,    0,    0,    0,    0,    0,    0 पूर्ण,
	अणु 0x0f, 0xf0,    0,    0,    0,    0,    0,    0 पूर्ण,
	अणु 0x07, 0x38, 0xc0,    0,    0,    0,    0,    0 पूर्ण,
	अणु 0x03, 0x0c, 0x30, 0xc0,    0,    0,    0,    0 पूर्ण,
	अणु 0x03, 0x0c, 0x30, 0x40, 0x80,    0,    0,    0 पूर्ण,
	अणु 0x03, 0x0c, 0x10, 0x20, 0x40, 0x80,    0,    0 पूर्ण,
	अणु 0x03, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,    0 पूर्ण,
	अणु 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 पूर्ण,
पूर्ण;

अटल व्योम mv88e6xxx_lag_set_port_mask(u16 *mask, पूर्णांक port,
					पूर्णांक num_tx, पूर्णांक nth)
अणु
	u8 active = 0;
	पूर्णांक i;

	num_tx = num_tx <= 8 ? num_tx : 8;
	अगर (nth < num_tx)
		active = mv88e6xxx_lag_mask_table[num_tx - 1][nth];

	क्रम (i = 0; i < 8; i++) अणु
		अगर (BIT(i) & active)
			mask[i] |= BIT(port);
	पूर्ण
पूर्ण

अटल पूर्णांक mv88e6xxx_lag_sync_masks(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	अचिन्हित पूर्णांक id, num_tx;
	काष्ठा net_device *lag;
	काष्ठा dsa_port *dp;
	पूर्णांक i, err, nth;
	u16 mask[8];
	u16 ivec;

	/* Assume no port is a member of any LAG. */
	ivec = BIT(mv88e6xxx_num_ports(chip)) - 1;

	/* Disable all masks क्रम ports that _are_ members of a LAG. */
	list_क्रम_each_entry(dp, &ds->dst->ports, list) अणु
		अगर (!dp->lag_dev || dp->ds != ds)
			जारी;

		ivec &= ~BIT(dp->index);
	पूर्ण

	क्रम (i = 0; i < 8; i++)
		mask[i] = ivec;

	/* Enable the correct subset of masks क्रम all LAG ports that
	 * are in the Tx set.
	 */
	dsa_lags_क्रमeach_id(id, ds->dst) अणु
		lag = dsa_lag_dev(ds->dst, id);
		अगर (!lag)
			जारी;

		num_tx = 0;
		dsa_lag_क्रमeach_port(dp, ds->dst, lag) अणु
			अगर (dp->lag_tx_enabled)
				num_tx++;
		पूर्ण

		अगर (!num_tx)
			जारी;

		nth = 0;
		dsa_lag_क्रमeach_port(dp, ds->dst, lag) अणु
			अगर (!dp->lag_tx_enabled)
				जारी;

			अगर (dp->ds == ds)
				mv88e6xxx_lag_set_port_mask(mask, dp->index,
							    num_tx, nth);

			nth++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		err = mv88e6xxx_g2_trunk_mask_ग_लिखो(chip, i, true, mask[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_lag_sync_masks_map(काष्ठा dsa_चयन *ds,
					काष्ठा net_device *lag)
अणु
	पूर्णांक err;

	err = mv88e6xxx_lag_sync_masks(ds);

	अगर (!err)
		err = mv88e6xxx_lag_sync_map(ds, lag);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_lag_change(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_lag_sync_masks(ds);
	mv88e6xxx_reg_unlock(chip);
	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_lag_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   काष्ठा net_device *lag,
				   काष्ठा netdev_lag_upper_info *info)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err, id;

	अगर (!mv88e6xxx_lag_can_offload(ds, lag, info))
		वापस -EOPNOTSUPP;

	id = dsa_lag_id(ds->dst, lag);

	mv88e6xxx_reg_lock(chip);

	err = mv88e6xxx_port_set_trunk(chip, port, true, id);
	अगर (err)
		जाओ err_unlock;

	err = mv88e6xxx_lag_sync_masks_map(ds, lag);
	अगर (err)
		जाओ err_clear_trunk;

	mv88e6xxx_reg_unlock(chip);
	वापस 0;

err_clear_trunk:
	mv88e6xxx_port_set_trunk(chip, port, false, 0);
err_unlock:
	mv88e6xxx_reg_unlock(chip);
	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_lag_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    काष्ठा net_device *lag)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err_sync, err_trunk;

	mv88e6xxx_reg_lock(chip);
	err_sync = mv88e6xxx_lag_sync_masks_map(ds, lag);
	err_trunk = mv88e6xxx_port_set_trunk(chip, port, false, 0);
	mv88e6xxx_reg_unlock(chip);
	वापस err_sync ? : err_trunk;
पूर्ण

अटल पूर्णांक mv88e6xxx_crosschip_lag_change(काष्ठा dsa_चयन *ds, पूर्णांक sw_index,
					  पूर्णांक port)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_lag_sync_masks(ds);
	mv88e6xxx_reg_unlock(chip);
	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_crosschip_lag_join(काष्ठा dsa_चयन *ds, पूर्णांक sw_index,
					पूर्णांक port, काष्ठा net_device *lag,
					काष्ठा netdev_lag_upper_info *info)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err;

	अगर (!mv88e6xxx_lag_can_offload(ds, lag, info))
		वापस -EOPNOTSUPP;

	mv88e6xxx_reg_lock(chip);

	err = mv88e6xxx_lag_sync_masks_map(ds, lag);
	अगर (err)
		जाओ unlock;

	err = mv88e6xxx_pvt_map(chip, sw_index, port);

unlock:
	mv88e6xxx_reg_unlock(chip);
	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_crosschip_lag_leave(काष्ठा dsa_चयन *ds, पूर्णांक sw_index,
					 पूर्णांक port, काष्ठा net_device *lag)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	पूर्णांक err_sync, err_pvt;

	mv88e6xxx_reg_lock(chip);
	err_sync = mv88e6xxx_lag_sync_masks_map(ds, lag);
	err_pvt = mv88e6xxx_pvt_map(chip, sw_index, port);
	mv88e6xxx_reg_unlock(chip);
	वापस err_sync ? : err_pvt;
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops mv88e6xxx_चयन_ops = अणु
	.get_tag_protocol	= mv88e6xxx_get_tag_protocol,
	.change_tag_protocol	= mv88e6xxx_change_tag_protocol,
	.setup			= mv88e6xxx_setup,
	.tearकरोwn		= mv88e6xxx_tearकरोwn,
	.phylink_validate	= mv88e6xxx_validate,
	.phylink_mac_link_state	= mv88e6xxx_serdes_pcs_get_state,
	.phylink_mac_config	= mv88e6xxx_mac_config,
	.phylink_mac_an_restart	= mv88e6xxx_serdes_pcs_an_restart,
	.phylink_mac_link_करोwn	= mv88e6xxx_mac_link_करोwn,
	.phylink_mac_link_up	= mv88e6xxx_mac_link_up,
	.get_strings		= mv88e6xxx_get_strings,
	.get_ethtool_stats	= mv88e6xxx_get_ethtool_stats,
	.get_sset_count		= mv88e6xxx_get_sset_count,
	.port_enable		= mv88e6xxx_port_enable,
	.port_disable		= mv88e6xxx_port_disable,
	.port_max_mtu		= mv88e6xxx_get_max_mtu,
	.port_change_mtu	= mv88e6xxx_change_mtu,
	.get_mac_eee		= mv88e6xxx_get_mac_eee,
	.set_mac_eee		= mv88e6xxx_set_mac_eee,
	.get_eeprom_len		= mv88e6xxx_get_eeprom_len,
	.get_eeprom		= mv88e6xxx_get_eeprom,
	.set_eeprom		= mv88e6xxx_set_eeprom,
	.get_regs_len		= mv88e6xxx_get_regs_len,
	.get_regs		= mv88e6xxx_get_regs,
	.get_rxnfc		= mv88e6xxx_get_rxnfc,
	.set_rxnfc		= mv88e6xxx_set_rxnfc,
	.set_ageing_समय	= mv88e6xxx_set_ageing_समय,
	.port_bridge_join	= mv88e6xxx_port_bridge_join,
	.port_bridge_leave	= mv88e6xxx_port_bridge_leave,
	.port_pre_bridge_flags	= mv88e6xxx_port_pre_bridge_flags,
	.port_bridge_flags	= mv88e6xxx_port_bridge_flags,
	.port_set_mrouter	= mv88e6xxx_port_set_mrouter,
	.port_stp_state_set	= mv88e6xxx_port_stp_state_set,
	.port_fast_age		= mv88e6xxx_port_fast_age,
	.port_vlan_filtering	= mv88e6xxx_port_vlan_filtering,
	.port_vlan_add		= mv88e6xxx_port_vlan_add,
	.port_vlan_del		= mv88e6xxx_port_vlan_del,
	.port_fdb_add           = mv88e6xxx_port_fdb_add,
	.port_fdb_del           = mv88e6xxx_port_fdb_del,
	.port_fdb_dump          = mv88e6xxx_port_fdb_dump,
	.port_mdb_add           = mv88e6xxx_port_mdb_add,
	.port_mdb_del           = mv88e6xxx_port_mdb_del,
	.port_mirror_add	= mv88e6xxx_port_mirror_add,
	.port_mirror_del	= mv88e6xxx_port_mirror_del,
	.crosschip_bridge_join	= mv88e6xxx_crosschip_bridge_join,
	.crosschip_bridge_leave	= mv88e6xxx_crosschip_bridge_leave,
	.port_hwtstamp_set	= mv88e6xxx_port_hwtstamp_set,
	.port_hwtstamp_get	= mv88e6xxx_port_hwtstamp_get,
	.port_txtstamp		= mv88e6xxx_port_txtstamp,
	.port_rxtstamp		= mv88e6xxx_port_rxtstamp,
	.get_ts_info		= mv88e6xxx_get_ts_info,
	.devlink_param_get	= mv88e6xxx_devlink_param_get,
	.devlink_param_set	= mv88e6xxx_devlink_param_set,
	.devlink_info_get	= mv88e6xxx_devlink_info_get,
	.port_lag_change	= mv88e6xxx_port_lag_change,
	.port_lag_join		= mv88e6xxx_port_lag_join,
	.port_lag_leave		= mv88e6xxx_port_lag_leave,
	.crosschip_lag_change	= mv88e6xxx_crosschip_lag_change,
	.crosschip_lag_join	= mv88e6xxx_crosschip_lag_join,
	.crosschip_lag_leave	= mv88e6xxx_crosschip_lag_leave,
पूर्ण;

अटल पूर्णांक mv88e6xxx_रेजिस्टर_चयन(काष्ठा mv88e6xxx_chip *chip)
अणु
	काष्ठा device *dev = chip->dev;
	काष्ठा dsa_चयन *ds;

	ds = devm_kzalloc(dev, माप(*ds), GFP_KERNEL);
	अगर (!ds)
		वापस -ENOMEM;

	ds->dev = dev;
	ds->num_ports = mv88e6xxx_num_ports(chip);
	ds->priv = chip;
	ds->dev = dev;
	ds->ops = &mv88e6xxx_चयन_ops;
	ds->ageing_समय_min = chip->info->age_समय_coeff;
	ds->ageing_समय_max = chip->info->age_समय_coeff * U8_MAX;

	/* Some chips support up to 32, but that requires enabling the
	 * 5-bit port mode, which we करो not support. 640k^W16 ought to
	 * be enough क्रम anyone.
	 */
	ds->num_lag_ids = mv88e6xxx_has_lag(chip) ? 16 : 0;

	dev_set_drvdata(dev, ds);

	वापस dsa_रेजिस्टर_चयन(ds);
पूर्ण

अटल व्योम mv88e6xxx_unरेजिस्टर_चयन(काष्ठा mv88e6xxx_chip *chip)
अणु
	dsa_unरेजिस्टर_चयन(chip->ds);
पूर्ण

अटल स्थिर व्योम *pdata_device_get_match_data(काष्ठा device *dev)
अणु
	स्थिर काष्ठा of_device_id *matches = dev->driver->of_match_table;
	स्थिर काष्ठा dsa_mv88e6xxx_pdata *pdata = dev->platक्रमm_data;

	क्रम (; matches->name[0] || matches->type[0] || matches->compatible[0];
	     matches++) अणु
		अगर (!म_भेद(pdata->compatible, matches->compatible))
			वापस matches->data;
	पूर्ण
	वापस शून्य;
पूर्ण

/* There is no suspend to RAM support at DSA level yet, the चयन configuration
 * would be lost after a घातer cycle so prevent it to be suspended.
 */
अटल पूर्णांक __maybe_unused mv88e6xxx_suspend(काष्ठा device *dev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक __maybe_unused mv88e6xxx_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mv88e6xxx_pm_ops, mv88e6xxx_suspend, mv88e6xxx_resume);

अटल पूर्णांक mv88e6xxx_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा dsa_mv88e6xxx_pdata *pdata = mdiodev->dev.platक्रमm_data;
	स्थिर काष्ठा mv88e6xxx_info *compat_info = शून्य;
	काष्ठा device *dev = &mdiodev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा mv88e6xxx_chip *chip;
	पूर्णांक port;
	पूर्णांक err;

	अगर (!np && !pdata)
		वापस -EINVAL;

	अगर (np)
		compat_info = of_device_get_match_data(dev);

	अगर (pdata) अणु
		compat_info = pdata_device_get_match_data(dev);

		अगर (!pdata->netdev)
			वापस -EINVAL;

		क्रम (port = 0; port < DSA_MAX_PORTS; port++) अणु
			अगर (!(pdata->enabled_ports & (1 << port)))
				जारी;
			अगर (म_भेद(pdata->cd.port_names[port], "cpu"))
				जारी;
			pdata->cd.netdev[port] = &pdata->netdev->dev;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!compat_info)
		वापस -EINVAL;

	chip = mv88e6xxx_alloc_chip(dev);
	अगर (!chip) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	chip->info = compat_info;

	err = mv88e6xxx_smi_init(chip, mdiodev->bus, mdiodev->addr);
	अगर (err)
		जाओ out;

	chip->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(chip->reset)) अणु
		err = PTR_ERR(chip->reset);
		जाओ out;
	पूर्ण
	अगर (chip->reset)
		usleep_range(1000, 2000);

	err = mv88e6xxx_detect(chip);
	अगर (err)
		जाओ out;

	अगर (chip->info->edsa_support == MV88E6XXX_EDSA_SUPPORTED)
		chip->tag_protocol = DSA_TAG_PROTO_EDSA;
	अन्यथा
		chip->tag_protocol = DSA_TAG_PROTO_DSA;

	mv88e6xxx_phy_init(chip);

	अगर (chip->info->ops->get_eeprom) अणु
		अगर (np)
			of_property_पढ़ो_u32(np, "eeprom-length",
					     &chip->eeprom_len);
		अन्यथा
			chip->eeprom_len = pdata->eeprom_len;
	पूर्ण

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_चयन_reset(chip);
	mv88e6xxx_reg_unlock(chip);
	अगर (err)
		जाओ out;

	अगर (np) अणु
		chip->irq = of_irq_get(np, 0);
		अगर (chip->irq == -EPROBE_DEFER) अणु
			err = chip->irq;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (pdata)
		chip->irq = pdata->irq;

	/* Has to be perक्रमmed beक्रमe the MDIO bus is created, because
	 * the PHYs will link their पूर्णांकerrupts to these पूर्णांकerrupt
	 * controllers
	 */
	mv88e6xxx_reg_lock(chip);
	अगर (chip->irq > 0)
		err = mv88e6xxx_g1_irq_setup(chip);
	अन्यथा
		err = mv88e6xxx_irq_poll_setup(chip);
	mv88e6xxx_reg_unlock(chip);

	अगर (err)
		जाओ out;

	अगर (chip->info->g2_irqs > 0) अणु
		err = mv88e6xxx_g2_irq_setup(chip);
		अगर (err)
			जाओ out_g1_irq;
	पूर्ण

	err = mv88e6xxx_g1_atu_prob_irq_setup(chip);
	अगर (err)
		जाओ out_g2_irq;

	err = mv88e6xxx_g1_vtu_prob_irq_setup(chip);
	अगर (err)
		जाओ out_g1_atu_prob_irq;

	err = mv88e6xxx_mdios_रेजिस्टर(chip, np);
	अगर (err)
		जाओ out_g1_vtu_prob_irq;

	err = mv88e6xxx_रेजिस्टर_चयन(chip);
	अगर (err)
		जाओ out_mdio;

	वापस 0;

out_mdio:
	mv88e6xxx_mdios_unरेजिस्टर(chip);
out_g1_vtu_prob_irq:
	mv88e6xxx_g1_vtu_prob_irq_मुक्त(chip);
out_g1_atu_prob_irq:
	mv88e6xxx_g1_atu_prob_irq_मुक्त(chip);
out_g2_irq:
	अगर (chip->info->g2_irqs > 0)
		mv88e6xxx_g2_irq_मुक्त(chip);
out_g1_irq:
	अगर (chip->irq > 0)
		mv88e6xxx_g1_irq_मुक्त(chip);
	अन्यथा
		mv88e6xxx_irq_poll_मुक्त(chip);
out:
	अगर (pdata)
		dev_put(pdata->netdev);

	वापस err;
पूर्ण

अटल व्योम mv88e6xxx_हटाओ(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा dsa_चयन *ds = dev_get_drvdata(&mdiodev->dev);
	काष्ठा mv88e6xxx_chip *chip = ds->priv;

	अगर (chip->info->ptp_support) अणु
		mv88e6xxx_hwtstamp_मुक्त(chip);
		mv88e6xxx_ptp_मुक्त(chip);
	पूर्ण

	mv88e6xxx_phy_destroy(chip);
	mv88e6xxx_unरेजिस्टर_चयन(chip);
	mv88e6xxx_mdios_unरेजिस्टर(chip);

	mv88e6xxx_g1_vtu_prob_irq_मुक्त(chip);
	mv88e6xxx_g1_atu_prob_irq_मुक्त(chip);

	अगर (chip->info->g2_irqs > 0)
		mv88e6xxx_g2_irq_मुक्त(chip);

	अगर (chip->irq > 0)
		mv88e6xxx_g1_irq_मुक्त(chip);
	अन्यथा
		mv88e6xxx_irq_poll_मुक्त(chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id mv88e6xxx_of_match[] = अणु
	अणु
		.compatible = "marvell,mv88e6085",
		.data = &mv88e6xxx_table[MV88E6085],
	पूर्ण,
	अणु
		.compatible = "marvell,mv88e6190",
		.data = &mv88e6xxx_table[MV88E6190],
	पूर्ण,
	अणु
		.compatible = "marvell,mv88e6250",
		.data = &mv88e6xxx_table[MV88E6250],
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, mv88e6xxx_of_match);

अटल काष्ठा mdio_driver mv88e6xxx_driver = अणु
	.probe	= mv88e6xxx_probe,
	.हटाओ = mv88e6xxx_हटाओ,
	.mdiodrv.driver = अणु
		.name = "mv88e6085",
		.of_match_table = mv88e6xxx_of_match,
		.pm = &mv88e6xxx_pm_ops,
	पूर्ण,
पूर्ण;

mdio_module_driver(mv88e6xxx_driver);

MODULE_AUTHOR("Lennert Buytenhek <buytenh@wantstofly.org>");
MODULE_DESCRIPTION("Driver for Marvell 88E6XXX ethernet switch chips");
MODULE_LICENSE("GPL");
