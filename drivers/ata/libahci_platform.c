<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AHCI SATA platक्रमm library
 *
 * Copyright 2004-2005  Red Hat, Inc.
 *   Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2010  MontaVista Software, LLC.
 *   Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/libata.h>
#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/reset.h>
#समावेश "ahci.h"

अटल व्योम ahci_host_stop(काष्ठा ata_host *host);

काष्ठा ata_port_operations ahci_platक्रमm_ops = अणु
	.inherits	= &ahci_ops,
	.host_stop	= ahci_host_stop,
पूर्ण;
EXPORT_SYMBOL_GPL(ahci_platक्रमm_ops);

/**
 * ahci_platक्रमm_enable_phys - Enable PHYs
 * @hpriv: host निजी area to store config values
 *
 * This function enables all the PHYs found in hpriv->phys, अगर any.
 * If a PHY fails to be enabled, it disables all the PHYs alपढ़ोy
 * enabled in reverse order and वापसs an error.
 *
 * RETURNS:
 * 0 on success otherwise a negative error code
 */
पूर्णांक ahci_platक्रमm_enable_phys(काष्ठा ahci_host_priv *hpriv)
अणु
	पूर्णांक rc, i;

	क्रम (i = 0; i < hpriv->nports; i++) अणु
		rc = phy_init(hpriv->phys[i]);
		अगर (rc)
			जाओ disable_phys;

		rc = phy_set_mode(hpriv->phys[i], PHY_MODE_SATA);
		अगर (rc) अणु
			phy_निकास(hpriv->phys[i]);
			जाओ disable_phys;
		पूर्ण

		rc = phy_घातer_on(hpriv->phys[i]);
		अगर (rc && !(rc == -EOPNOTSUPP && (hpriv->flags & AHCI_HFLAG_IGN_NOTSUPP_POWER_ON))) अणु
			phy_निकास(hpriv->phys[i]);
			जाओ disable_phys;
		पूर्ण
	पूर्ण

	वापस 0;

disable_phys:
	जबतक (--i >= 0) अणु
		phy_घातer_off(hpriv->phys[i]);
		phy_निकास(hpriv->phys[i]);
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_enable_phys);

/**
 * ahci_platक्रमm_disable_phys - Disable PHYs
 * @hpriv: host निजी area to store config values
 *
 * This function disables all PHYs found in hpriv->phys.
 */
व्योम ahci_platक्रमm_disable_phys(काष्ठा ahci_host_priv *hpriv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hpriv->nports; i++) अणु
		phy_घातer_off(hpriv->phys[i]);
		phy_निकास(hpriv->phys[i]);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_disable_phys);

/**
 * ahci_platक्रमm_enable_clks - Enable platक्रमm घड़ीs
 * @hpriv: host निजी area to store config values
 *
 * This function enables all the clks found in hpriv->clks, starting at
 * index 0. If any clk fails to enable it disables all the clks alपढ़ोy
 * enabled in reverse order, and then वापसs an error.
 *
 * RETURNS:
 * 0 on success otherwise a negative error code
 */
पूर्णांक ahci_platक्रमm_enable_clks(काष्ठा ahci_host_priv *hpriv)
अणु
	पूर्णांक c, rc;

	क्रम (c = 0; c < AHCI_MAX_CLKS && hpriv->clks[c]; c++) अणु
		rc = clk_prepare_enable(hpriv->clks[c]);
		अगर (rc)
			जाओ disable_unprepare_clk;
	पूर्ण
	वापस 0;

disable_unprepare_clk:
	जबतक (--c >= 0)
		clk_disable_unprepare(hpriv->clks[c]);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_enable_clks);

/**
 * ahci_platक्रमm_disable_clks - Disable platक्रमm घड़ीs
 * @hpriv: host निजी area to store config values
 *
 * This function disables all the clks found in hpriv->clks, in reverse
 * order of ahci_platक्रमm_enable_clks (starting at the end of the array).
 */
व्योम ahci_platक्रमm_disable_clks(काष्ठा ahci_host_priv *hpriv)
अणु
	पूर्णांक c;

	क्रम (c = AHCI_MAX_CLKS - 1; c >= 0; c--)
		अगर (hpriv->clks[c])
			clk_disable_unprepare(hpriv->clks[c]);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_disable_clks);

/**
 * ahci_platक्रमm_enable_regulators - Enable regulators
 * @hpriv: host निजी area to store config values
 *
 * This function enables all the regulators found in controller and
 * hpriv->target_pwrs, अगर any.  If a regulator fails to be enabled, it
 * disables all the regulators alपढ़ोy enabled in reverse order and
 * वापसs an error.
 *
 * RETURNS:
 * 0 on success otherwise a negative error code
 */
पूर्णांक ahci_platक्रमm_enable_regulators(काष्ठा ahci_host_priv *hpriv)
अणु
	पूर्णांक rc, i;

	rc = regulator_enable(hpriv->ahci_regulator);
	अगर (rc)
		वापस rc;

	rc = regulator_enable(hpriv->phy_regulator);
	अगर (rc)
		जाओ disable_ahci_pwrs;

	क्रम (i = 0; i < hpriv->nports; i++) अणु
		अगर (!hpriv->target_pwrs[i])
			जारी;

		rc = regulator_enable(hpriv->target_pwrs[i]);
		अगर (rc)
			जाओ disable_target_pwrs;
	पूर्ण

	वापस 0;

disable_target_pwrs:
	जबतक (--i >= 0)
		अगर (hpriv->target_pwrs[i])
			regulator_disable(hpriv->target_pwrs[i]);

	regulator_disable(hpriv->phy_regulator);
disable_ahci_pwrs:
	regulator_disable(hpriv->ahci_regulator);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_enable_regulators);

/**
 * ahci_platक्रमm_disable_regulators - Disable regulators
 * @hpriv: host निजी area to store config values
 *
 * This function disables all regulators found in hpriv->target_pwrs and
 * AHCI controller.
 */
व्योम ahci_platक्रमm_disable_regulators(काष्ठा ahci_host_priv *hpriv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hpriv->nports; i++) अणु
		अगर (!hpriv->target_pwrs[i])
			जारी;
		regulator_disable(hpriv->target_pwrs[i]);
	पूर्ण

	regulator_disable(hpriv->ahci_regulator);
	regulator_disable(hpriv->phy_regulator);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_disable_regulators);
/**
 * ahci_platक्रमm_enable_resources - Enable platक्रमm resources
 * @hpriv: host निजी area to store config values
 *
 * This function enables all ahci_platक्रमm managed resources in the
 * following order:
 * 1) Regulator
 * 2) Clocks (through ahci_platक्रमm_enable_clks)
 * 3) Resets
 * 4) Phys
 *
 * If resource enabling fails at any poपूर्णांक the previous enabled resources
 * are disabled in reverse order.
 *
 * RETURNS:
 * 0 on success otherwise a negative error code
 */
पूर्णांक ahci_platक्रमm_enable_resources(काष्ठा ahci_host_priv *hpriv)
अणु
	पूर्णांक rc;

	rc = ahci_platक्रमm_enable_regulators(hpriv);
	अगर (rc)
		वापस rc;

	rc = ahci_platक्रमm_enable_clks(hpriv);
	अगर (rc)
		जाओ disable_regulator;

	rc = reset_control_deनिश्चित(hpriv->rsts);
	अगर (rc)
		जाओ disable_clks;

	rc = ahci_platक्रमm_enable_phys(hpriv);
	अगर (rc)
		जाओ disable_resets;

	वापस 0;

disable_resets:
	reset_control_निश्चित(hpriv->rsts);

disable_clks:
	ahci_platक्रमm_disable_clks(hpriv);

disable_regulator:
	ahci_platक्रमm_disable_regulators(hpriv);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_enable_resources);

/**
 * ahci_platक्रमm_disable_resources - Disable platक्रमm resources
 * @hpriv: host निजी area to store config values
 *
 * This function disables all ahci_platक्रमm managed resources in the
 * following order:
 * 1) Phys
 * 2) Resets
 * 3) Clocks (through ahci_platक्रमm_disable_clks)
 * 4) Regulator
 */
व्योम ahci_platक्रमm_disable_resources(काष्ठा ahci_host_priv *hpriv)
अणु
	ahci_platक्रमm_disable_phys(hpriv);

	reset_control_निश्चित(hpriv->rsts);

	ahci_platक्रमm_disable_clks(hpriv);

	ahci_platक्रमm_disable_regulators(hpriv);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_disable_resources);

अटल व्योम ahci_platक्रमm_put_resources(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा ahci_host_priv *hpriv = res;
	पूर्णांक c;

	अगर (hpriv->got_runसमय_pm) अणु
		pm_runसमय_put_sync(dev);
		pm_runसमय_disable(dev);
	पूर्ण

	क्रम (c = 0; c < AHCI_MAX_CLKS && hpriv->clks[c]; c++)
		clk_put(hpriv->clks[c]);
	/*
	 * The regulators are tied to child node device and not to the
	 * SATA device itself. So we can't use devm क्रम स्वतःmatically
	 * releasing them. We have to करो it manually here.
	 */
	क्रम (c = 0; c < hpriv->nports; c++)
		अगर (hpriv->target_pwrs && hpriv->target_pwrs[c])
			regulator_put(hpriv->target_pwrs[c]);

	kमुक्त(hpriv->target_pwrs);
पूर्ण

अटल पूर्णांक ahci_platक्रमm_get_phy(काष्ठा ahci_host_priv *hpriv, u32 port,
				काष्ठा device *dev, काष्ठा device_node *node)
अणु
	पूर्णांक rc;

	hpriv->phys[port] = devm_of_phy_get(dev, node, शून्य);

	अगर (!IS_ERR(hpriv->phys[port]))
		वापस 0;

	rc = PTR_ERR(hpriv->phys[port]);
	चयन (rc) अणु
	हाल -ENOSYS:
		/* No PHY support. Check अगर PHY is required. */
		अगर (of_find_property(node, "phys", शून्य)) अणु
			dev_err(dev,
				"couldn't get PHY in node %pOFn: ENOSYS\n",
				node);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल -ENODEV:
		/* जारी normally */
		hpriv->phys[port] = शून्य;
		rc = 0;
		अवरोध;
	हाल -EPROBE_DEFER:
		/* Do not complain yet */
		अवरोध;

	शेष:
		dev_err(dev,
			"couldn't get PHY in node %pOFn: %d\n",
			node, rc);

		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक ahci_platक्रमm_get_regulator(काष्ठा ahci_host_priv *hpriv, u32 port,
				काष्ठा device *dev)
अणु
	काष्ठा regulator *target_pwr;
	पूर्णांक rc = 0;

	target_pwr = regulator_get(dev, "target");

	अगर (!IS_ERR(target_pwr))
		hpriv->target_pwrs[port] = target_pwr;
	अन्यथा
		rc = PTR_ERR(target_pwr);

	वापस rc;
पूर्ण

/**
 * ahci_platक्रमm_get_resources - Get platक्रमm resources
 * @pdev: platक्रमm device to get resources क्रम
 * @flags: biपंचांगap representing the resource to get
 *
 * This function allocates an ahci_host_priv काष्ठा, and माला_लो the following
 * resources, storing a reference to them inside the वापसed काष्ठा:
 *
 * 1) mmio रेजिस्टरs (IORESOURCE_MEM 0, mandatory)
 * 2) regulator क्रम controlling the tarमाला_लो घातer (optional)
 *    regulator क्रम controlling the AHCI controller (optional)
 * 3) 0 - AHCI_MAX_CLKS घड़ीs, as specअगरied in the devs devicetree node,
 *    or क्रम non devicetree enabled platक्रमms a single घड़ी
 * 4) resets, अगर flags has AHCI_PLATFORM_GET_RESETS (optional)
 * 5) phys (optional)
 *
 * RETURNS:
 * The allocated ahci_host_priv on success, otherwise an ERR_PTR value
 */
काष्ठा ahci_host_priv *ahci_platक्रमm_get_resources(काष्ठा platक्रमm_device *pdev,
						   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ahci_host_priv *hpriv;
	काष्ठा clk *clk;
	काष्ठा device_node *child;
	पूर्णांक i, enabled_ports = 0, rc = -ENOMEM, child_nodes;
	u32 mask_port_map = 0;

	अगर (!devres_खोलो_group(dev, शून्य, GFP_KERNEL))
		वापस ERR_PTR(-ENOMEM);

	hpriv = devres_alloc(ahci_platक्रमm_put_resources, माप(*hpriv),
			     GFP_KERNEL);
	अगर (!hpriv)
		जाओ err_out;

	devres_add(dev, hpriv);

	hpriv->mmio = devm_ioremap_resource(dev,
			      platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0));
	अगर (IS_ERR(hpriv->mmio)) अणु
		rc = PTR_ERR(hpriv->mmio);
		जाओ err_out;
	पूर्ण

	क्रम (i = 0; i < AHCI_MAX_CLKS; i++) अणु
		/*
		 * For now we must use clk_get(dev, शून्य) क्रम the first घड़ी,
		 * because some platक्रमms (da850, spear13xx) are not yet
		 * converted to use devicetree क्रम घड़ीs.  For new platक्रमms
		 * this is equivalent to of_clk_get(dev->of_node, 0).
		 */
		अगर (i == 0)
			clk = clk_get(dev, शून्य);
		अन्यथा
			clk = of_clk_get(dev->of_node, i);

		अगर (IS_ERR(clk)) अणु
			rc = PTR_ERR(clk);
			अगर (rc == -EPROBE_DEFER)
				जाओ err_out;
			अवरोध;
		पूर्ण
		hpriv->clks[i] = clk;
	पूर्ण

	hpriv->ahci_regulator = devm_regulator_get(dev, "ahci");
	अगर (IS_ERR(hpriv->ahci_regulator)) अणु
		rc = PTR_ERR(hpriv->ahci_regulator);
		अगर (rc != 0)
			जाओ err_out;
	पूर्ण

	hpriv->phy_regulator = devm_regulator_get(dev, "phy");
	अगर (IS_ERR(hpriv->phy_regulator)) अणु
		rc = PTR_ERR(hpriv->phy_regulator);
		अगर (rc == -EPROBE_DEFER)
			जाओ err_out;
		rc = 0;
		hpriv->phy_regulator = शून्य;
	पूर्ण

	अगर (flags & AHCI_PLATFORM_GET_RESETS) अणु
		hpriv->rsts = devm_reset_control_array_get_optional_shared(dev);
		अगर (IS_ERR(hpriv->rsts)) अणु
			rc = PTR_ERR(hpriv->rsts);
			जाओ err_out;
		पूर्ण
	पूर्ण

	hpriv->nports = child_nodes = of_get_child_count(dev->of_node);

	/*
	 * If no sub-node was found, we still need to set nports to
	 * one in order to be able to use the
	 * ahci_platक्रमm_[en|dis]able_[phys|regulators] functions.
	 */
	अगर (!child_nodes)
		hpriv->nports = 1;

	hpriv->phys = devm_kसुस्मृति(dev, hpriv->nports, माप(*hpriv->phys), GFP_KERNEL);
	अगर (!hpriv->phys) अणु
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण
	/*
	 * We cannot use devm_ here, since ahci_platक्रमm_put_resources() uses
	 * target_pwrs after devm_ have मुक्तd memory
	 */
	hpriv->target_pwrs = kसुस्मृति(hpriv->nports, माप(*hpriv->target_pwrs), GFP_KERNEL);
	अगर (!hpriv->target_pwrs) अणु
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण

	अगर (child_nodes) अणु
		क्रम_each_child_of_node(dev->of_node, child) अणु
			u32 port;
			काष्ठा platक्रमm_device *port_dev __maybe_unused;

			अगर (!of_device_is_available(child))
				जारी;

			अगर (of_property_पढ़ो_u32(child, "reg", &port)) अणु
				rc = -EINVAL;
				of_node_put(child);
				जाओ err_out;
			पूर्ण

			अगर (port >= hpriv->nports) अणु
				dev_warn(dev, "invalid port number %d\n", port);
				जारी;
			पूर्ण
			mask_port_map |= BIT(port);

#अगर_घोषित CONFIG_OF_ADDRESS
			of_platक्रमm_device_create(child, शून्य, शून्य);

			port_dev = of_find_device_by_node(child);

			अगर (port_dev) अणु
				rc = ahci_platक्रमm_get_regulator(hpriv, port,
								&port_dev->dev);
				अगर (rc == -EPROBE_DEFER) अणु
					of_node_put(child);
					जाओ err_out;
				पूर्ण
			पूर्ण
#पूर्ण_अगर

			rc = ahci_platक्रमm_get_phy(hpriv, port, dev, child);
			अगर (rc) अणु
				of_node_put(child);
				जाओ err_out;
			पूर्ण

			enabled_ports++;
		पूर्ण
		अगर (!enabled_ports) अणु
			dev_warn(dev, "No port enabled\n");
			rc = -ENODEV;
			जाओ err_out;
		पूर्ण

		अगर (!hpriv->mask_port_map)
			hpriv->mask_port_map = mask_port_map;
	पूर्ण अन्यथा अणु
		/*
		 * If no sub-node was found, keep this क्रम device tree
		 * compatibility
		 */
		rc = ahci_platक्रमm_get_phy(hpriv, 0, dev, dev->of_node);
		अगर (rc)
			जाओ err_out;

		rc = ahci_platक्रमm_get_regulator(hpriv, 0, dev);
		अगर (rc == -EPROBE_DEFER)
			जाओ err_out;
	पूर्ण
	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);
	hpriv->got_runसमय_pm = true;

	devres_हटाओ_group(dev, शून्य);
	वापस hpriv;

err_out:
	devres_release_group(dev, शून्य);
	वापस ERR_PTR(rc);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_get_resources);

/**
 * ahci_platक्रमm_init_host - Bring up an ahci-platक्रमm host
 * @pdev: platक्रमm device poपूर्णांकer क्रम the host
 * @hpriv: ahci-host निजी data क्रम the host
 * @pi_ढाँचा: ढाँचा क्रम the ata_port_info to use
 * @sht: scsi_host_ढाँचा to use when रेजिस्टरing
 *
 * This function करोes all the usual steps needed to bring up an
 * ahci-platक्रमm host, note any necessary resources (ie clks, phys, etc.)
 * must be initialized / enabled beक्रमe calling this.
 *
 * RETURNS:
 * 0 on success otherwise a negative error code
 */
पूर्णांक ahci_platक्रमm_init_host(काष्ठा platक्रमm_device *pdev,
			    काष्ठा ahci_host_priv *hpriv,
			    स्थिर काष्ठा ata_port_info *pi_ढाँचा,
			    काष्ठा scsi_host_ढाँचा *sht)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ata_port_info pi = *pi_ढाँचा;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &pi, शून्य पूर्ण;
	काष्ठा ata_host *host;
	पूर्णांक i, irq, n_ports, rc;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		अगर (irq != -EPROBE_DEFER)
			dev_err(dev, "no irq\n");
		वापस irq;
	पूर्ण
	अगर (!irq)
		वापस -EINVAL;

	hpriv->irq = irq;

	/* prepare host */
	pi.निजी_data = (व्योम *)(अचिन्हित दीर्घ)hpriv->flags;

	ahci_save_initial_config(dev, hpriv);

	अगर (hpriv->cap & HOST_CAP_NCQ)
		pi.flags |= ATA_FLAG_NCQ;

	अगर (hpriv->cap & HOST_CAP_PMP)
		pi.flags |= ATA_FLAG_PMP;

	ahci_set_em_messages(hpriv, &pi);

	/* CAP.NP someबार indicate the index of the last enabled
	 * port, at other बार, that of the last possible port, so
	 * determining the maximum port number requires looking at
	 * both CAP.NP and port_map.
	 */
	n_ports = max(ahci_nr_ports(hpriv->cap), fls(hpriv->port_map));

	host = ata_host_alloc_pinfo(dev, ppi, n_ports);
	अगर (!host)
		वापस -ENOMEM;

	host->निजी_data = hpriv;

	अगर (!(hpriv->cap & HOST_CAP_SSS) || ahci_ignore_sss)
		host->flags |= ATA_HOST_PARALLEL_SCAN;
	अन्यथा
		dev_info(dev, "SSS flag set, parallel bus scan disabled\n");

	अगर (pi.flags & ATA_FLAG_EM)
		ahci_reset_em(host);

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		ata_port_desc(ap, "mmio %pR",
			      platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0));
		ata_port_desc(ap, "port 0x%x", 0x100 + ap->port_no * 0x80);

		/* set enclosure management message type */
		अगर (ap->flags & ATA_FLAG_EM)
			ap->em_message_type = hpriv->em_msg_type;

		/* disabled/not-implemented port */
		अगर (!(hpriv->port_map & (1 << i)))
			ap->ops = &ata_dummy_port_ops;
	पूर्ण

	अगर (hpriv->cap & HOST_CAP_64) अणु
		rc = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(64));
		अगर (rc) अणु
			rc = dma_coerce_mask_and_coherent(dev,
							  DMA_BIT_MASK(32));
			अगर (rc) अणु
				dev_err(dev, "Failed to enable 64-bit DMA.\n");
				वापस rc;
			पूर्ण
			dev_warn(dev, "Enable 32-bit DMA instead of 64-bit.\n");
		पूर्ण
	पूर्ण

	rc = ahci_reset_controller(host);
	अगर (rc)
		वापस rc;

	ahci_init_controller(host);
	ahci_prपूर्णांक_info(host, "platform");

	वापस ahci_host_activate(host, sht);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_init_host);

अटल व्योम ahci_host_stop(काष्ठा ata_host *host)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;

	ahci_platक्रमm_disable_resources(hpriv);
पूर्ण

/**
 * ahci_platक्रमm_shutकरोwn - Disable पूर्णांकerrupts and stop DMA क्रम host ports
 * @pdev: platक्रमm device poपूर्णांकer क्रम the host
 *
 * This function is called during प्रणाली shutकरोwn and perक्रमms the minimal
 * deconfiguration required to ensure that an ahci_platक्रमm host cannot
 * corrupt or otherwise पूर्णांकerfere with a new kernel being started with kexec.
 */
व्योम ahci_platक्रमm_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	पूर्णांक i;

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		/* Disable port पूर्णांकerrupts */
		अगर (ap->ops->मुक्तze)
			ap->ops->मुक्तze(ap);

		/* Stop the port DMA engines */
		अगर (ap->ops->port_stop)
			ap->ops->port_stop(ap);
	पूर्ण

	/* Disable and clear host पूर्णांकerrupts */
	ग_लिखोl(पढ़ोl(mmio + HOST_CTL) & ~HOST_IRQ_EN, mmio + HOST_CTL);
	पढ़ोl(mmio + HOST_CTL); /* flush */
	ग_लिखोl(GENMASK(host->n_ports, 0), mmio + HOST_IRQ_STAT);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_shutकरोwn);

#अगर_घोषित CONFIG_PM_SLEEP
/**
 * ahci_platक्रमm_suspend_host - Suspend an ahci-platक्रमm host
 * @dev: device poपूर्णांकer क्रम the host
 *
 * This function करोes all the usual steps needed to suspend an
 * ahci-platक्रमm host, note any necessary resources (ie clks, phys, etc.)
 * must be disabled after calling this.
 *
 * RETURNS:
 * 0 on success otherwise a negative error code
 */
पूर्णांक ahci_platक्रमm_suspend_host(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	u32 ctl;

	अगर (hpriv->flags & AHCI_HFLAG_NO_SUSPEND) अणु
		dev_err(dev, "firmware update required for suspend/resume\n");
		वापस -EIO;
	पूर्ण

	/*
	 * AHCI spec rev1.1 section 8.3.3:
	 * Software must disable पूर्णांकerrupts prior to requesting a
	 * transition of the HBA to D3 state.
	 */
	ctl = पढ़ोl(mmio + HOST_CTL);
	ctl &= ~HOST_IRQ_EN;
	ग_लिखोl(ctl, mmio + HOST_CTL);
	पढ़ोl(mmio + HOST_CTL); /* flush */

	अगर (hpriv->flags & AHCI_HFLAG_SUSPEND_PHYS)
		ahci_platक्रमm_disable_phys(hpriv);

	वापस ata_host_suspend(host, PMSG_SUSPEND);
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_suspend_host);

/**
 * ahci_platक्रमm_resume_host - Resume an ahci-platक्रमm host
 * @dev: device poपूर्णांकer क्रम the host
 *
 * This function करोes all the usual steps needed to resume an ahci-platक्रमm
 * host, note any necessary resources (ie clks, phys, etc.)  must be
 * initialized / enabled beक्रमe calling this.
 *
 * RETURNS:
 * 0 on success otherwise a negative error code
 */
पूर्णांक ahci_platक्रमm_resume_host(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	पूर्णांक rc;

	अगर (dev->घातer.घातer_state.event == PM_EVENT_SUSPEND) अणु
		rc = ahci_reset_controller(host);
		अगर (rc)
			वापस rc;

		ahci_init_controller(host);
	पूर्ण

	अगर (hpriv->flags & AHCI_HFLAG_SUSPEND_PHYS)
		ahci_platक्रमm_enable_phys(hpriv);

	ata_host_resume(host);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_resume_host);

/**
 * ahci_platक्रमm_suspend - Suspend an ahci-platक्रमm device
 * @dev: the platक्रमm device to suspend
 *
 * This function suspends the host associated with the device, followed by
 * disabling all the resources of the device.
 *
 * RETURNS:
 * 0 on success otherwise a negative error code
 */
पूर्णांक ahci_platक्रमm_suspend(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	पूर्णांक rc;

	rc = ahci_platक्रमm_suspend_host(dev);
	अगर (rc)
		वापस rc;

	ahci_platक्रमm_disable_resources(hpriv);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_suspend);

/**
 * ahci_platक्रमm_resume - Resume an ahci-platक्रमm device
 * @dev: the platक्रमm device to resume
 *
 * This function enables all the resources of the device followed by
 * resuming the host associated with the device.
 *
 * RETURNS:
 * 0 on success otherwise a negative error code
 */
पूर्णांक ahci_platक्रमm_resume(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	पूर्णांक rc;

	rc = ahci_platक्रमm_enable_resources(hpriv);
	अगर (rc)
		वापस rc;

	rc = ahci_platक्रमm_resume_host(dev);
	अगर (rc)
		जाओ disable_resources;

	/* We resumed so update PM runसमय state */
	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;

disable_resources:
	ahci_platक्रमm_disable_resources(hpriv);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ahci_platक्रमm_resume);
#पूर्ण_अगर

MODULE_DESCRIPTION("AHCI SATA platform library");
MODULE_AUTHOR("Anton Vorontsov <avorontsov@ru.mvista.com>");
MODULE_LICENSE("GPL");
