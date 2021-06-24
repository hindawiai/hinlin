<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* $Date: 2005/11/12 02:13:49 $ $RCSfile: my3126.c,v $ $Revision: 1.15 $ */
#समावेश "cphy.h"
#समावेश "elmer0.h"
#समावेश "suni1x10gexp_regs.h"

/* Port Reset */
अटल पूर्णांक my3126_reset(काष्ठा cphy *cphy, पूर्णांक रुको)
अणु
	/*
	 * This can be करोne through रेजिस्टरs.  It is not required since
	 * a full chip reset is used.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक my3126_पूर्णांकerrupt_enable(काष्ठा cphy *cphy)
अणु
	schedule_delayed_work(&cphy->phy_update, HZ/30);
	t1_tpi_पढ़ो(cphy->adapter, A_ELMER0_GPO, &cphy->elmer_gpo);
	वापस 0;
पूर्ण

अटल पूर्णांक my3126_पूर्णांकerrupt_disable(काष्ठा cphy *cphy)
अणु
	cancel_delayed_work_sync(&cphy->phy_update);
	वापस 0;
पूर्ण

अटल पूर्णांक my3126_पूर्णांकerrupt_clear(काष्ठा cphy *cphy)
अणु
	वापस 0;
पूर्ण

#घोषणा OFFSET(REG_ADDR)    (REG_ADDR << 2)

अटल पूर्णांक my3126_पूर्णांकerrupt_handler(काष्ठा cphy *cphy)
अणु
	u32 val;
	u16 val16;
	u16 status;
	u32 act_count;
	adapter_t *adapter;
	adapter = cphy->adapter;

	अगर (cphy->count == 50) अणु
		cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &val);
		val16 = (u16) val;
		status = cphy->bmsr ^ val16;

		अगर (status & MDIO_STAT1_LSTATUS)
			t1_link_changed(adapter, 0);
		cphy->bmsr = val16;

		/* We have only enabled link change पूर्णांकerrupts so it
		   must be that
		 */
		cphy->count = 0;
	पूर्ण

	t1_tpi_ग_लिखो(adapter, OFFSET(SUNI1x10GEXP_REG_MSTAT_CONTROL),
		SUNI1x10GEXP_BITMSK_MSTAT_SNAP);
	t1_tpi_पढ़ो(adapter,
		OFFSET(SUNI1x10GEXP_REG_MSTAT_COUNTER_1_LOW), &act_count);
	t1_tpi_पढ़ो(adapter,
		OFFSET(SUNI1x10GEXP_REG_MSTAT_COUNTER_33_LOW), &val);
	act_count += val;

	/* Populate elmer_gpo with the रेजिस्टर value */
	t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	cphy->elmer_gpo = val;

	अगर ( (val & (1 << 8)) || (val & (1 << 19)) ||
	     (cphy->act_count == act_count) || cphy->act_on ) अणु
		अगर (is_T2(adapter))
			val |= (1 << 9);
		अन्यथा अगर (t1_is_T1B(adapter))
			val |= (1 << 20);
		cphy->act_on = 0;
	पूर्ण अन्यथा अणु
		अगर (is_T2(adapter))
			val &= ~(1 << 9);
		अन्यथा अगर (t1_is_T1B(adapter))
			val &= ~(1 << 20);
		cphy->act_on = 1;
	पूर्ण

	t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);

	cphy->elmer_gpo = val;
	cphy->act_count = act_count;
	cphy->count++;

	वापस cphy_cause_link_change;
पूर्ण

अटल व्योम my3126_poll(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cphy *cphy = container_of(work, काष्ठा cphy, phy_update.work);

	my3126_पूर्णांकerrupt_handler(cphy);
पूर्ण

अटल पूर्णांक my3126_set_loopback(काष्ठा cphy *cphy, पूर्णांक on)
अणु
	वापस 0;
पूर्ण

/* To check the activity LED */
अटल पूर्णांक my3126_get_link_status(काष्ठा cphy *cphy,
			पूर्णांक *link_ok, पूर्णांक *speed, पूर्णांक *duplex, पूर्णांक *fc)
अणु
	u32 val;
	u16 val16;
	adapter_t *adapter;

	adapter = cphy->adapter;
	cphy_mdio_पढ़ो(cphy, MDIO_MMD_PMAPMD, MDIO_STAT1, &val);
	val16 = (u16) val;

	/* Populate elmer_gpo with the रेजिस्टर value */
	t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	cphy->elmer_gpo = val;

	*link_ok = (val16 & MDIO_STAT1_LSTATUS);

	अगर (*link_ok) अणु
		/* Turn on the LED. */
		अगर (is_T2(adapter))
			 val &= ~(1 << 8);
		अन्यथा अगर (t1_is_T1B(adapter))
			 val &= ~(1 << 19);
	पूर्ण अन्यथा अणु
		/* Turn off the LED. */
		अगर (is_T2(adapter))
			 val |= (1 << 8);
		अन्यथा अगर (t1_is_T1B(adapter))
			 val |= (1 << 19);
	पूर्ण

	t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	cphy->elmer_gpo = val;
	*speed = SPEED_10000;
	*duplex = DUPLEX_FULL;

	/* need to add flow control */
	अगर (fc)
		*fc = PAUSE_RX | PAUSE_TX;

	वापस 0;
पूर्ण

अटल व्योम my3126_destroy(काष्ठा cphy *cphy)
अणु
	kमुक्त(cphy);
पूर्ण

अटल स्थिर काष्ठा cphy_ops my3126_ops = अणु
	.destroy		= my3126_destroy,
	.reset			= my3126_reset,
	.पूर्णांकerrupt_enable	= my3126_पूर्णांकerrupt_enable,
	.पूर्णांकerrupt_disable	= my3126_पूर्णांकerrupt_disable,
	.पूर्णांकerrupt_clear	= my3126_पूर्णांकerrupt_clear,
	.पूर्णांकerrupt_handler	= my3126_पूर्णांकerrupt_handler,
	.get_link_status	= my3126_get_link_status,
	.set_loopback		= my3126_set_loopback,
	.mmds			= (MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS |
				   MDIO_DEVS_PHYXS),
पूर्ण;

अटल काष्ठा cphy *my3126_phy_create(काष्ठा net_device *dev,
			पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops)
अणु
	काष्ठा cphy *cphy = kzalloc(माप (*cphy), GFP_KERNEL);

	अगर (!cphy)
		वापस शून्य;

	cphy_init(cphy, dev, phy_addr, &my3126_ops, mdio_ops);
	INIT_DELAYED_WORK(&cphy->phy_update, my3126_poll);
	cphy->bmsr = 0;

	वापस cphy;
पूर्ण

/* Chip Reset */
अटल पूर्णांक my3126_phy_reset(adapter_t * adapter)
अणु
	u32 val;

	t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val &= ~4;
	t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	msleep(100);

	t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val | 4);
	msleep(1000);

	/* Now lets enable the Laser. Delay 100us */
	t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
	val |= 0x8000;
	t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);
	udelay(100);
	वापस 0;
पूर्ण

स्थिर काष्ठा gphy t1_my3126_ops = अणु
	.create = my3126_phy_create,
	.reset = my3126_phy_reset
पूर्ण;
