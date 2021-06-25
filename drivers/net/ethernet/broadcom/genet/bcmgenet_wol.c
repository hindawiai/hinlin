<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom GENET (Gigabit Ethernet) Wake-on-LAN support
 *
 * Copyright (c) 2014-2020 Broadcom
 */

#घोषणा pr_fmt(fmt)				"bcmgenet_wol: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <net/arp.h>

#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/phy.h>

#समावेश "bcmgenet.h"

/* ethtool function - get WOL (Wake on LAN) settings, Only Magic Packet
 * Detection is supported through ethtool
 */
व्योम bcmgenet_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);

	wol->supported = WAKE_MAGIC | WAKE_MAGICSECURE | WAKE_FILTER;
	wol->wolopts = priv->wolopts;
	स_रखो(wol->sopass, 0, माप(wol->sopass));

	अगर (wol->wolopts & WAKE_MAGICSECURE)
		स_नकल(wol->sopass, priv->sopass, माप(priv->sopass));
पूर्ण

/* ethtool function - set WOL (Wake on LAN) settings.
 * Only क्रम magic packet detection mode.
 */
पूर्णांक bcmgenet_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा bcmgenet_priv *priv = netdev_priv(dev);
	काष्ठा device *kdev = &priv->pdev->dev;

	अगर (!device_can_wakeup(kdev))
		वापस -ENOTSUPP;

	अगर (wol->wolopts & ~(WAKE_MAGIC | WAKE_MAGICSECURE | WAKE_FILTER))
		वापस -EINVAL;

	अगर (wol->wolopts & WAKE_MAGICSECURE)
		स_नकल(priv->sopass, wol->sopass, माप(priv->sopass));

	/* Flag the device and relevant IRQ as wakeup capable */
	अगर (wol->wolopts) अणु
		device_set_wakeup_enable(kdev, 1);
		/* Aव्योम unbalanced enable_irq_wake calls */
		अगर (priv->wol_irq_disabled)
			enable_irq_wake(priv->wol_irq);
		priv->wol_irq_disabled = false;
	पूर्ण अन्यथा अणु
		device_set_wakeup_enable(kdev, 0);
		/* Aव्योम unbalanced disable_irq_wake calls */
		अगर (!priv->wol_irq_disabled)
			disable_irq_wake(priv->wol_irq);
		priv->wol_irq_disabled = true;
	पूर्ण

	priv->wolopts = wol->wolopts;

	वापस 0;
पूर्ण

अटल पूर्णांक bcmgenet_poll_wol_status(काष्ठा bcmgenet_priv *priv)
अणु
	काष्ठा net_device *dev = priv->dev;
	पूर्णांक retries = 0;

	जबतक (!(bcmgenet_rbuf_पढ़ोl(priv, RBUF_STATUS)
		& RBUF_STATUS_WOL)) अणु
		retries++;
		अगर (retries > 5) अणु
			netdev_crit(dev, "polling wol mode timeout\n");
			वापस -ETIMEDOUT;
		पूर्ण
		mdelay(1);
	पूर्ण

	वापस retries;
पूर्ण

अटल व्योम bcmgenet_set_mpd_password(काष्ठा bcmgenet_priv *priv)
अणु
	bcmgenet_umac_ग_लिखोl(priv, get_unaligned_be16(&priv->sopass[0]),
			     UMAC_MPD_PW_MS);
	bcmgenet_umac_ग_लिखोl(priv, get_unaligned_be32(&priv->sopass[2]),
			     UMAC_MPD_PW_LS);
पूर्ण

पूर्णांक bcmgenet_wol_घातer_करोwn_cfg(काष्ठा bcmgenet_priv *priv,
				क्रमागत bcmgenet_घातer_mode mode)
अणु
	काष्ठा net_device *dev = priv->dev;
	काष्ठा bcmgenet_rxnfc_rule *rule;
	u32 reg, hfb_ctrl_reg, hfb_enable = 0;
	पूर्णांक retries = 0;

	अगर (mode != GENET_POWER_WOL_MAGIC) अणु
		netअगर_err(priv, wol, dev, "unsupported mode: %d\n", mode);
		वापस -EINVAL;
	पूर्ण

	/* Can't suspend with WoL अगर MAC is still in reset */
	reg = bcmgenet_umac_पढ़ोl(priv, UMAC_CMD);
	अगर (reg & CMD_SW_RESET)
		reg &= ~CMD_SW_RESET;

	/* disable RX */
	reg &= ~CMD_RX_EN;
	bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_CMD);
	mdelay(10);

	अगर (priv->wolopts & (WAKE_MAGIC | WAKE_MAGICSECURE)) अणु
		reg = bcmgenet_umac_पढ़ोl(priv, UMAC_MPD_CTRL);
		reg |= MPD_EN;
		अगर (priv->wolopts & WAKE_MAGICSECURE) अणु
			bcmgenet_set_mpd_password(priv);
			reg |= MPD_PW_EN;
		पूर्ण
		bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_MPD_CTRL);
	पूर्ण

	hfb_ctrl_reg = bcmgenet_hfb_reg_पढ़ोl(priv, HFB_CTRL);
	अगर (priv->wolopts & WAKE_FILTER) अणु
		list_क्रम_each_entry(rule, &priv->rxnfc_list, list)
			अगर (rule->fs.ring_cookie == RX_CLS_FLOW_WAKE)
				hfb_enable |= (1 << rule->fs.location);
		reg = (hfb_ctrl_reg & ~RBUF_HFB_EN) | RBUF_ACPI_EN;
		bcmgenet_hfb_reg_ग_लिखोl(priv, reg, HFB_CTRL);
	पूर्ण

	/* Do not leave UniMAC in MPD mode only */
	retries = bcmgenet_poll_wol_status(priv);
	अगर (retries < 0) अणु
		reg = bcmgenet_umac_पढ़ोl(priv, UMAC_MPD_CTRL);
		reg &= ~(MPD_EN | MPD_PW_EN);
		bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_MPD_CTRL);
		bcmgenet_hfb_reg_ग_लिखोl(priv, hfb_ctrl_reg, HFB_CTRL);
		वापस retries;
	पूर्ण

	netअगर_dbg(priv, wol, dev, "MPD WOL-ready status set after %d msec\n",
		  retries);

	clk_prepare_enable(priv->clk_wol);
	priv->wol_active = 1;

	अगर (hfb_enable) अणु
		bcmgenet_hfb_reg_ग_लिखोl(priv, hfb_enable,
					HFB_FLT_ENABLE_V3PLUS + 4);
		hfb_ctrl_reg = RBUF_HFB_EN | RBUF_ACPI_EN;
		bcmgenet_hfb_reg_ग_लिखोl(priv, hfb_ctrl_reg, HFB_CTRL);
	पूर्ण

	/* Enable CRC क्रमward */
	reg = bcmgenet_umac_पढ़ोl(priv, UMAC_CMD);
	priv->crc_fwd_en = 1;
	reg |= CMD_CRC_FWD;

	/* Receiver must be enabled क्रम WOL MP detection */
	reg |= CMD_RX_EN;
	bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_CMD);

	अगर (priv->hw_params->flags & GENET_HAS_EXT) अणु
		reg = bcmgenet_ext_पढ़ोl(priv, EXT_EXT_PWR_MGMT);
		reg &= ~EXT_ENERGY_DET_MASK;
		bcmgenet_ext_ग_लिखोl(priv, reg, EXT_EXT_PWR_MGMT);
	पूर्ण

	reg = UMAC_IRQ_MPD_R;
	अगर (hfb_enable)
		reg |=  UMAC_IRQ_HFB_SM | UMAC_IRQ_HFB_MM;

	bcmgenet_पूर्णांकrl2_0_ग_लिखोl(priv, reg, INTRL2_CPU_MASK_CLEAR);

	वापस 0;
पूर्ण

व्योम bcmgenet_wol_घातer_up_cfg(काष्ठा bcmgenet_priv *priv,
			       क्रमागत bcmgenet_घातer_mode mode)
अणु
	u32 reg;

	अगर (mode != GENET_POWER_WOL_MAGIC) अणु
		netअगर_err(priv, wol, priv->dev, "invalid mode: %d\n", mode);
		वापस;
	पूर्ण

	अगर (!priv->wol_active)
		वापस;	/* failed to suspend so skip the rest */

	priv->wol_active = 0;
	clk_disable_unprepare(priv->clk_wol);
	priv->crc_fwd_en = 0;

	/* Disable Magic Packet Detection */
	अगर (priv->wolopts & (WAKE_MAGIC | WAKE_MAGICSECURE)) अणु
		reg = bcmgenet_umac_पढ़ोl(priv, UMAC_MPD_CTRL);
		अगर (!(reg & MPD_EN))
			वापस;	/* alपढ़ोy reset so skip the rest */
		reg &= ~(MPD_EN | MPD_PW_EN);
		bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_MPD_CTRL);
	पूर्ण

	/* Disable WAKE_FILTER Detection */
	अगर (priv->wolopts & WAKE_FILTER) अणु
		reg = bcmgenet_hfb_reg_पढ़ोl(priv, HFB_CTRL);
		अगर (!(reg & RBUF_ACPI_EN))
			वापस;	/* alपढ़ोy reset so skip the rest */
		reg &= ~(RBUF_HFB_EN | RBUF_ACPI_EN);
		bcmgenet_hfb_reg_ग_लिखोl(priv, reg, HFB_CTRL);
	पूर्ण

	/* Disable CRC Forward */
	reg = bcmgenet_umac_पढ़ोl(priv, UMAC_CMD);
	reg &= ~CMD_CRC_FWD;
	bcmgenet_umac_ग_लिखोl(priv, reg, UMAC_CMD);
पूर्ण
