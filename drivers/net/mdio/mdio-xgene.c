<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Applied Micro X-Gene SoC MDIO Driver
 *
 * Copyright (c) 2016, Applied Micro Circuits Corporation
 * Author: Iyappan Subramanian <isubramanian@apm.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/efi.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पन.स>
#समावेश <linux/mdio/mdio-xgene.h>
#समावेश <linux/module.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/prefetch.h>
#समावेश <net/ip.h>

अटल bool xgene_mdio_status;

u32 xgene_mdio_rd_mac(काष्ठा xgene_mdio_pdata *pdata, u32 rd_addr)
अणु
	व्योम __iomem *addr, *rd, *cmd, *cmd_करोne;
	u32 करोne, rd_data = BUSY_MASK;
	u8 रुको = 10;

	addr = pdata->mac_csr_addr + MAC_ADDR_REG_OFFSET;
	rd = pdata->mac_csr_addr + MAC_READ_REG_OFFSET;
	cmd = pdata->mac_csr_addr + MAC_COMMAND_REG_OFFSET;
	cmd_करोne = pdata->mac_csr_addr + MAC_COMMAND_DONE_REG_OFFSET;

	spin_lock(&pdata->mac_lock);
	ioग_लिखो32(rd_addr, addr);
	ioग_लिखो32(XGENE_ENET_RD_CMD, cmd);

	जबतक (!(करोne = ioपढ़ो32(cmd_करोne)) && रुको--)
		udelay(1);

	अगर (करोne)
		rd_data = ioपढ़ो32(rd);

	ioग_लिखो32(0, cmd);
	spin_unlock(&pdata->mac_lock);

	वापस rd_data;
पूर्ण
EXPORT_SYMBOL(xgene_mdio_rd_mac);

व्योम xgene_mdio_wr_mac(काष्ठा xgene_mdio_pdata *pdata, u32 wr_addr, u32 data)
अणु
	व्योम __iomem *addr, *wr, *cmd, *cmd_करोne;
	u8 रुको = 10;
	u32 करोne;

	addr = pdata->mac_csr_addr + MAC_ADDR_REG_OFFSET;
	wr = pdata->mac_csr_addr + MAC_WRITE_REG_OFFSET;
	cmd = pdata->mac_csr_addr + MAC_COMMAND_REG_OFFSET;
	cmd_करोne = pdata->mac_csr_addr + MAC_COMMAND_DONE_REG_OFFSET;

	spin_lock(&pdata->mac_lock);
	ioग_लिखो32(wr_addr, addr);
	ioग_लिखो32(data, wr);
	ioग_लिखो32(XGENE_ENET_WR_CMD, cmd);

	जबतक (!(करोne = ioपढ़ो32(cmd_करोne)) && रुको--)
		udelay(1);

	अगर (!करोne)
		pr_err("MCX mac write failed, addr: 0x%04x\n", wr_addr);

	ioग_लिखो32(0, cmd);
	spin_unlock(&pdata->mac_lock);
पूर्ण
EXPORT_SYMBOL(xgene_mdio_wr_mac);

पूर्णांक xgene_mdio_rgmii_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा xgene_mdio_pdata *pdata = (काष्ठा xgene_mdio_pdata *)bus->priv;
	u32 data, करोne;
	u8 रुको = 10;

	data = SET_VAL(PHY_ADDR, phy_id) | SET_VAL(REG_ADDR, reg);
	xgene_mdio_wr_mac(pdata, MII_MGMT_ADDRESS_ADDR, data);
	xgene_mdio_wr_mac(pdata, MII_MGMT_COMMAND_ADDR, READ_CYCLE_MASK);
	करो अणु
		usleep_range(5, 10);
		करोne = xgene_mdio_rd_mac(pdata, MII_MGMT_INDICATORS_ADDR);
	पूर्ण जबतक ((करोne & BUSY_MASK) && रुको--);

	अगर (करोne & BUSY_MASK) अणु
		dev_err(&bus->dev, "MII_MGMT read failed\n");
		वापस -EBUSY;
	पूर्ण

	data = xgene_mdio_rd_mac(pdata, MII_MGMT_STATUS_ADDR);
	xgene_mdio_wr_mac(pdata, MII_MGMT_COMMAND_ADDR, 0);

	वापस data;
पूर्ण
EXPORT_SYMBOL(xgene_mdio_rgmii_पढ़ो);

पूर्णांक xgene_mdio_rgmii_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg, u16 data)
अणु
	काष्ठा xgene_mdio_pdata *pdata = (काष्ठा xgene_mdio_pdata *)bus->priv;
	u32 val, करोne;
	u8 रुको = 10;

	val = SET_VAL(PHY_ADDR, phy_id) | SET_VAL(REG_ADDR, reg);
	xgene_mdio_wr_mac(pdata, MII_MGMT_ADDRESS_ADDR, val);

	xgene_mdio_wr_mac(pdata, MII_MGMT_CONTROL_ADDR, data);
	करो अणु
		usleep_range(5, 10);
		करोne = xgene_mdio_rd_mac(pdata, MII_MGMT_INDICATORS_ADDR);
	पूर्ण जबतक ((करोne & BUSY_MASK) && रुको--);

	अगर (करोne & BUSY_MASK) अणु
		dev_err(&bus->dev, "MII_MGMT write failed\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(xgene_mdio_rgmii_ग_लिखो);

अटल u32 xgene_menet_rd_diag_csr(काष्ठा xgene_mdio_pdata *pdata, u32 offset)
अणु
	वापस ioपढ़ो32(pdata->diag_csr_addr + offset);
पूर्ण

अटल व्योम xgene_menet_wr_diag_csr(काष्ठा xgene_mdio_pdata *pdata,
				    u32 offset, u32 val)
अणु
	ioग_लिखो32(val, pdata->diag_csr_addr + offset);
पूर्ण

अटल पूर्णांक xgene_enet_ecc_init(काष्ठा xgene_mdio_pdata *pdata)
अणु
	u32 data;
	u8 रुको = 10;

	xgene_menet_wr_diag_csr(pdata, MENET_CFG_MEM_RAM_SHUTDOWN_ADDR, 0x0);
	करो अणु
		usleep_range(100, 110);
		data = xgene_menet_rd_diag_csr(pdata, MENET_BLOCK_MEM_RDY_ADDR);
	पूर्ण जबतक ((data != 0xffffffff) && रुको--);

	अगर (data != 0xffffffff) अणु
		dev_err(pdata->dev, "Failed to release memory from shutdown\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xgene_gmac_reset(काष्ठा xgene_mdio_pdata *pdata)
अणु
	xgene_mdio_wr_mac(pdata, MAC_CONFIG_1_ADDR, SOFT_RESET);
	xgene_mdio_wr_mac(pdata, MAC_CONFIG_1_ADDR, 0);
पूर्ण

अटल पूर्णांक xgene_mdio_reset(काष्ठा xgene_mdio_pdata *pdata)
अणु
	पूर्णांक ret;

	अगर (pdata->dev->of_node) अणु
		clk_prepare_enable(pdata->clk);
		udelay(5);
		clk_disable_unprepare(pdata->clk);
		udelay(5);
		clk_prepare_enable(pdata->clk);
		udelay(5);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_ACPI
		acpi_evaluate_object(ACPI_HANDLE(pdata->dev),
				     "_RST", शून्य, शून्य);
#पूर्ण_अगर
	पूर्ण

	ret = xgene_enet_ecc_init(pdata);
	अगर (ret) अणु
		अगर (pdata->dev->of_node)
			clk_disable_unprepare(pdata->clk);
		वापस ret;
	पूर्ण
	xgene_gmac_reset(pdata);

	वापस 0;
पूर्ण

अटल व्योम xgene_enet_rd_mdio_csr(व्योम __iomem *base_addr,
				   u32 offset, u32 *val)
अणु
	व्योम __iomem *addr = base_addr  + offset;

	*val = ioपढ़ो32(addr);
पूर्ण

अटल व्योम xgene_enet_wr_mdio_csr(व्योम __iomem *base_addr,
				   u32 offset, u32 val)
अणु
	व्योम __iomem *addr = base_addr  + offset;

	ioग_लिखो32(val, addr);
पूर्ण

अटल पूर्णांक xgene_xfi_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id,
				पूर्णांक reg, u16 data)
अणु
	व्योम __iomem *addr = (व्योम __iomem *)bus->priv;
	पूर्णांक समयout = 100;
	u32 status, val;

	val = SET_VAL(HSTPHYADX, phy_id) | SET_VAL(HSTREGADX, reg) |
	      SET_VAL(HSTMIIMWRDAT, data);
	xgene_enet_wr_mdio_csr(addr, MIIM_FIELD_ADDR, val);

	val = HSTLDCMD | SET_VAL(HSTMIIMCMD, MIIM_CMD_LEGACY_WRITE);
	xgene_enet_wr_mdio_csr(addr, MIIM_COMMAND_ADDR, val);

	करो अणु
		usleep_range(5, 10);
		xgene_enet_rd_mdio_csr(addr, MIIM_INDICATOR_ADDR, &status);
	पूर्ण जबतक ((status & BUSY_MASK) && समयout--);

	xgene_enet_wr_mdio_csr(addr, MIIM_COMMAND_ADDR, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_xfi_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	व्योम __iomem *addr = (व्योम __iomem *)bus->priv;
	u32 data, status, val;
	पूर्णांक समयout = 100;

	val = SET_VAL(HSTPHYADX, phy_id) | SET_VAL(HSTREGADX, reg);
	xgene_enet_wr_mdio_csr(addr, MIIM_FIELD_ADDR, val);

	val = HSTLDCMD | SET_VAL(HSTMIIMCMD, MIIM_CMD_LEGACY_READ);
	xgene_enet_wr_mdio_csr(addr, MIIM_COMMAND_ADDR, val);

	करो अणु
		usleep_range(5, 10);
		xgene_enet_rd_mdio_csr(addr, MIIM_INDICATOR_ADDR, &status);
	पूर्ण जबतक ((status & BUSY_MASK) && समयout--);

	अगर (status & BUSY_MASK) अणु
		pr_err("XGENET_MII_MGMT write failed\n");
		वापस -EBUSY;
	पूर्ण

	xgene_enet_rd_mdio_csr(addr, MIIMRD_FIELD_ADDR, &data);
	xgene_enet_wr_mdio_csr(addr, MIIM_COMMAND_ADDR, 0);

	वापस data;
पूर्ण

काष्ठा phy_device *xgene_enet_phy_रेजिस्टर(काष्ठा mii_bus *bus, पूर्णांक phy_addr)
अणु
	काष्ठा phy_device *phy_dev;

	phy_dev = get_phy_device(bus, phy_addr, false);
	अगर (!phy_dev || IS_ERR(phy_dev))
		वापस शून्य;

	अगर (phy_device_रेजिस्टर(phy_dev))
		phy_device_मुक्त(phy_dev);

	वापस phy_dev;
पूर्ण
EXPORT_SYMBOL(xgene_enet_phy_रेजिस्टर);

#अगर_घोषित CONFIG_ACPI
अटल acpi_status acpi_रेजिस्टर_phy(acpi_handle handle, u32 lvl,
				     व्योम *context, व्योम **ret)
अणु
	काष्ठा mii_bus *mdio = context;
	काष्ठा acpi_device *adev;
	काष्ठा phy_device *phy_dev;
	स्थिर जोड़ acpi_object *obj;
	u32 phy_addr;

	अगर (acpi_bus_get_device(handle, &adev))
		वापस AE_OK;

	अगर (acpi_dev_get_property(adev, "phy-channel", ACPI_TYPE_INTEGER, &obj))
		वापस AE_OK;
	phy_addr = obj->पूर्णांकeger.value;

	phy_dev = xgene_enet_phy_रेजिस्टर(mdio, phy_addr);
	adev->driver_data = phy_dev;

	वापस AE_OK;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id xgene_mdio_of_match[] = अणु
	अणु
		.compatible = "apm,xgene-mdio-rgmii",
		.data = (व्योम *)XGENE_MDIO_RGMII
	पूर्ण,
	अणु
		.compatible = "apm,xgene-mdio-xfi",
		.data = (व्योम *)XGENE_MDIO_XFI
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xgene_mdio_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xgene_mdio_acpi_match[] = अणु
	अणु "APMC0D65", XGENE_MDIO_RGMII पूर्ण,
	अणु "APMC0D66", XGENE_MDIO_XFI पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, xgene_mdio_acpi_match);
#पूर्ण_अगर


अटल पूर्णांक xgene_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mii_bus *mdio_bus;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा xgene_mdio_pdata *pdata;
	व्योम __iomem *csr_base;
	पूर्णांक mdio_id = 0, ret = 0;

	of_id = of_match_device(xgene_mdio_of_match, &pdev->dev);
	अगर (of_id) अणु
		mdio_id = (क्रमागत xgene_mdio_id)of_id->data;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_ACPI
		स्थिर काष्ठा acpi_device_id *acpi_id;

		acpi_id = acpi_match_device(xgene_mdio_acpi_match, &pdev->dev);
		अगर (acpi_id)
			mdio_id = (क्रमागत xgene_mdio_id)acpi_id->driver_data;
#पूर्ण_अगर
	पूर्ण

	अगर (!mdio_id)
		वापस -ENODEV;

	pdata = devm_kzalloc(dev, माप(काष्ठा xgene_mdio_pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;
	pdata->mdio_id = mdio_id;
	pdata->dev = dev;

	csr_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(csr_base))
		वापस PTR_ERR(csr_base);
	pdata->mac_csr_addr = csr_base;
	pdata->mdio_csr_addr = csr_base + BLOCK_XG_MDIO_CSR_OFFSET;
	pdata->diag_csr_addr = csr_base + BLOCK_DIAG_CSR_OFFSET;

	अगर (mdio_id == XGENE_MDIO_RGMII)
		spin_lock_init(&pdata->mac_lock);

	अगर (dev->of_node) अणु
		pdata->clk = devm_clk_get(dev, शून्य);
		अगर (IS_ERR(pdata->clk)) अणु
			dev_err(dev, "Unable to retrieve clk\n");
			वापस PTR_ERR(pdata->clk);
		पूर्ण
	पूर्ण

	ret = xgene_mdio_reset(pdata);
	अगर (ret)
		वापस ret;

	mdio_bus = mdiobus_alloc();
	अगर (!mdio_bus) अणु
		ret = -ENOMEM;
		जाओ out_clk;
	पूर्ण

	mdio_bus->name = "APM X-Gene MDIO bus";

	अगर (mdio_id == XGENE_MDIO_RGMII) अणु
		mdio_bus->पढ़ो = xgene_mdio_rgmii_पढ़ो;
		mdio_bus->ग_लिखो = xgene_mdio_rgmii_ग_लिखो;
		mdio_bus->priv = (व्योम __क्रमce *)pdata;
		snम_लिखो(mdio_bus->id, MII_BUS_ID_SIZE, "%s",
			 "xgene-mii-rgmii");
	पूर्ण अन्यथा अणु
		mdio_bus->पढ़ो = xgene_xfi_mdio_पढ़ो;
		mdio_bus->ग_लिखो = xgene_xfi_mdio_ग_लिखो;
		mdio_bus->priv = (व्योम __क्रमce *)pdata->mdio_csr_addr;
		snम_लिखो(mdio_bus->id, MII_BUS_ID_SIZE, "%s",
			 "xgene-mii-xfi");
	पूर्ण

	mdio_bus->parent = dev;
	platक्रमm_set_drvdata(pdev, pdata);

	अगर (dev->of_node) अणु
		ret = of_mdiobus_रेजिस्टर(mdio_bus, dev->of_node);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_ACPI
		/* Mask out all PHYs from स्वतः probing. */
		mdio_bus->phy_mask = ~0;
		ret = mdiobus_रेजिस्टर(mdio_bus);
		अगर (ret)
			जाओ out_mdiobus;

		acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_HANDLE(dev), 1,
				    acpi_रेजिस्टर_phy, शून्य, mdio_bus, शून्य);
#पूर्ण_अगर
	पूर्ण

	अगर (ret)
		जाओ out_mdiobus;

	pdata->mdio_bus = mdio_bus;
	xgene_mdio_status = true;

	वापस 0;

out_mdiobus:
	mdiobus_मुक्त(mdio_bus);

out_clk:
	अगर (dev->of_node)
		clk_disable_unprepare(pdata->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक xgene_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_mdio_pdata *pdata = platक्रमm_get_drvdata(pdev);
	काष्ठा mii_bus *mdio_bus = pdata->mdio_bus;
	काष्ठा device *dev = &pdev->dev;

	mdiobus_unरेजिस्टर(mdio_bus);
	mdiobus_मुक्त(mdio_bus);

	अगर (dev->of_node)
		clk_disable_unprepare(pdata->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xgene_mdio_driver = अणु
	.driver = अणु
		.name = "xgene-mdio",
		.of_match_table = of_match_ptr(xgene_mdio_of_match),
		.acpi_match_table = ACPI_PTR(xgene_mdio_acpi_match),
	पूर्ण,
	.probe = xgene_mdio_probe,
	.हटाओ = xgene_mdio_हटाओ,
पूर्ण;

module_platक्रमm_driver(xgene_mdio_driver);

MODULE_DESCRIPTION("APM X-Gene SoC MDIO driver");
MODULE_AUTHOR("Iyappan Subramanian <isubramanian@apm.com>");
MODULE_LICENSE("GPL");
