<शैली गुरु>
/*
 * AMD 10Gb Ethernet driver
 *
 * This file is available to you under your choice of the following two
 * licenses:
 *
 * License 1: GPLv2
 *
 * Copyright (c) 2014-2016 Advanced Micro Devices, Inc.
 *
 * This file is मुक्त software; you may copy, redistribute and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at
 * your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * License 2: Modअगरied BSD
 *
 * Copyright (c) 2014-2016 Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/property.h>
#समावेश <linux/acpi.h>
#समावेश <linux/mdपन.स>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xgbe_acpi_match[];

अटल काष्ठा xgbe_version_data *xgbe_acpi_vdata(काष्ठा xgbe_prv_data *pdata)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(xgbe_acpi_match, pdata->dev);

	वापस id ? (काष्ठा xgbe_version_data *)id->driver_data : शून्य;
पूर्ण

अटल पूर्णांक xgbe_acpi_support(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा device *dev = pdata->dev;
	u32 property;
	पूर्णांक ret;

	/* Obtain the प्रणाली घड़ी setting */
	ret = device_property_पढ़ो_u32(dev, XGBE_ACPI_DMA_FREQ, &property);
	अगर (ret) अणु
		dev_err(dev, "unable to obtain %s property\n",
			XGBE_ACPI_DMA_FREQ);
		वापस ret;
	पूर्ण
	pdata->sysclk_rate = property;

	/* Obtain the PTP घड़ी setting */
	ret = device_property_पढ़ो_u32(dev, XGBE_ACPI_PTP_FREQ, &property);
	अगर (ret) अणु
		dev_err(dev, "unable to obtain %s property\n",
			XGBE_ACPI_PTP_FREQ);
		वापस ret;
	पूर्ण
	pdata->ptpclk_rate = property;

	वापस 0;
पूर्ण
#अन्यथा   /* CONFIG_ACPI */
अटल काष्ठा xgbe_version_data *xgbe_acpi_vdata(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस शून्य;
पूर्ण

अटल पूर्णांक xgbe_acpi_support(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर  /* CONFIG_ACPI */

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id xgbe_of_match[];

अटल काष्ठा xgbe_version_data *xgbe_of_vdata(काष्ठा xgbe_prv_data *pdata)
अणु
	स्थिर काष्ठा of_device_id *id;

	id = of_match_device(xgbe_of_match, pdata->dev);

	वापस id ? (काष्ठा xgbe_version_data *)id->data : शून्य;
पूर्ण

अटल पूर्णांक xgbe_of_support(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा device *dev = pdata->dev;

	/* Obtain the प्रणाली घड़ी setting */
	pdata->sysclk = devm_clk_get(dev, XGBE_DMA_CLOCK);
	अगर (IS_ERR(pdata->sysclk)) अणु
		dev_err(dev, "dma devm_clk_get failed\n");
		वापस PTR_ERR(pdata->sysclk);
	पूर्ण
	pdata->sysclk_rate = clk_get_rate(pdata->sysclk);

	/* Obtain the PTP घड़ी setting */
	pdata->ptpclk = devm_clk_get(dev, XGBE_PTP_CLOCK);
	अगर (IS_ERR(pdata->ptpclk)) अणु
		dev_err(dev, "ptp devm_clk_get failed\n");
		वापस PTR_ERR(pdata->ptpclk);
	पूर्ण
	pdata->ptpclk_rate = clk_get_rate(pdata->ptpclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device *xgbe_of_get_phy_pdev(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा device *dev = pdata->dev;
	काष्ठा device_node *phy_node;
	काष्ठा platक्रमm_device *phy_pdev;

	phy_node = of_parse_phandle(dev->of_node, "phy-handle", 0);
	अगर (phy_node) अणु
		/* Old style device tree:
		 *   The XGBE and PHY resources are separate
		 */
		phy_pdev = of_find_device_by_node(phy_node);
		of_node_put(phy_node);
	पूर्ण अन्यथा अणु
		/* New style device tree:
		 *   The XGBE and PHY resources are grouped together with
		 *   the PHY resources listed last
		 */
		get_device(dev);
		phy_pdev = pdata->platdev;
	पूर्ण

	वापस phy_pdev;
पूर्ण
#अन्यथा   /* CONFIG_OF */
अटल काष्ठा xgbe_version_data *xgbe_of_vdata(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस शून्य;
पूर्ण

अटल पूर्णांक xgbe_of_support(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस -EINVAL;
पूर्ण

अटल काष्ठा platक्रमm_device *xgbe_of_get_phy_pdev(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर  /* CONFIG_OF */

अटल अचिन्हित पूर्णांक xgbe_resource_count(काष्ठा platक्रमm_device *pdev,
					अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक count;
	पूर्णांक i;

	क्रम (i = 0, count = 0; i < pdev->num_resources; i++) अणु
		काष्ठा resource *res = &pdev->resource[i];

		अगर (type == resource_type(res))
			count++;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा platक्रमm_device *xgbe_get_phy_pdev(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा platक्रमm_device *phy_pdev;

	अगर (pdata->use_acpi) अणु
		get_device(pdata->dev);
		phy_pdev = pdata->platdev;
	पूर्ण अन्यथा अणु
		phy_pdev = xgbe_of_get_phy_pdev(pdata);
	पूर्ण

	वापस phy_pdev;
पूर्ण

अटल काष्ठा xgbe_version_data *xgbe_get_vdata(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस pdata->use_acpi ? xgbe_acpi_vdata(pdata)
			       : xgbe_of_vdata(pdata);
पूर्ण

अटल पूर्णांक xgbe_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgbe_prv_data *pdata;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा platक्रमm_device *phy_pdev;
	स्थिर अक्षर *phy_mode;
	अचिन्हित पूर्णांक phy_memnum, phy_irqnum;
	अचिन्हित पूर्णांक dma_irqnum, dma_irqend;
	क्रमागत dev_dma_attr attr;
	पूर्णांक ret;

	pdata = xgbe_alloc_pdata(dev);
	अगर (IS_ERR(pdata)) अणु
		ret = PTR_ERR(pdata);
		जाओ err_alloc;
	पूर्ण

	pdata->platdev = pdev;
	pdata->adev = ACPI_COMPANION(dev);
	platक्रमm_set_drvdata(pdev, pdata);

	/* Check अगर we should use ACPI or DT */
	pdata->use_acpi = dev->of_node ? 0 : 1;

	/* Get the version data */
	pdata->vdata = xgbe_get_vdata(pdata);

	phy_pdev = xgbe_get_phy_pdev(pdata);
	अगर (!phy_pdev) अणु
		dev_err(dev, "unable to obtain phy device\n");
		ret = -EINVAL;
		जाओ err_phydev;
	पूर्ण
	pdata->phy_platdev = phy_pdev;
	pdata->phy_dev = &phy_pdev->dev;

	अगर (pdev == phy_pdev) अणु
		/* New style device tree or ACPI:
		 *   The XGBE and PHY resources are grouped together with
		 *   the PHY resources listed last
		 */
		phy_memnum = xgbe_resource_count(pdev, IORESOURCE_MEM) - 3;
		phy_irqnum = xgbe_resource_count(pdev, IORESOURCE_IRQ) - 1;
		dma_irqnum = 1;
		dma_irqend = phy_irqnum;
	पूर्ण अन्यथा अणु
		/* Old style device tree:
		 *   The XGBE and PHY resources are separate
		 */
		phy_memnum = 0;
		phy_irqnum = 0;
		dma_irqnum = 1;
		dma_irqend = xgbe_resource_count(pdev, IORESOURCE_IRQ);
	पूर्ण

	/* Obtain the mmio areas क्रम the device */
	pdata->xgmac_regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pdata->xgmac_regs)) अणु
		dev_err(dev, "xgmac ioremap failed\n");
		ret = PTR_ERR(pdata->xgmac_regs);
		जाओ err_io;
	पूर्ण
	अगर (netअगर_msg_probe(pdata))
		dev_dbg(dev, "xgmac_regs = %p\n", pdata->xgmac_regs);

	pdata->xpcs_regs = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(pdata->xpcs_regs)) अणु
		dev_err(dev, "xpcs ioremap failed\n");
		ret = PTR_ERR(pdata->xpcs_regs);
		जाओ err_io;
	पूर्ण
	अगर (netअगर_msg_probe(pdata))
		dev_dbg(dev, "xpcs_regs  = %p\n", pdata->xpcs_regs);

	pdata->rxtx_regs = devm_platक्रमm_ioremap_resource(phy_pdev,
							  phy_memnum++);
	अगर (IS_ERR(pdata->rxtx_regs)) अणु
		dev_err(dev, "rxtx ioremap failed\n");
		ret = PTR_ERR(pdata->rxtx_regs);
		जाओ err_io;
	पूर्ण
	अगर (netअगर_msg_probe(pdata))
		dev_dbg(dev, "rxtx_regs  = %p\n", pdata->rxtx_regs);

	pdata->sir0_regs = devm_platक्रमm_ioremap_resource(phy_pdev,
							  phy_memnum++);
	अगर (IS_ERR(pdata->sir0_regs)) अणु
		dev_err(dev, "sir0 ioremap failed\n");
		ret = PTR_ERR(pdata->sir0_regs);
		जाओ err_io;
	पूर्ण
	अगर (netअगर_msg_probe(pdata))
		dev_dbg(dev, "sir0_regs  = %p\n", pdata->sir0_regs);

	pdata->sir1_regs = devm_platक्रमm_ioremap_resource(phy_pdev,
							  phy_memnum++);
	अगर (IS_ERR(pdata->sir1_regs)) अणु
		dev_err(dev, "sir1 ioremap failed\n");
		ret = PTR_ERR(pdata->sir1_regs);
		जाओ err_io;
	पूर्ण
	अगर (netअगर_msg_probe(pdata))
		dev_dbg(dev, "sir1_regs  = %p\n", pdata->sir1_regs);

	/* Retrieve the MAC address */
	ret = device_property_पढ़ो_u8_array(dev, XGBE_MAC_ADDR_PROPERTY,
					    pdata->mac_addr,
					    माप(pdata->mac_addr));
	अगर (ret || !is_valid_ether_addr(pdata->mac_addr)) अणु
		dev_err(dev, "invalid %s property\n", XGBE_MAC_ADDR_PROPERTY);
		अगर (!ret)
			ret = -EINVAL;
		जाओ err_io;
	पूर्ण

	/* Retrieve the PHY mode - it must be "xgmii" */
	ret = device_property_पढ़ो_string(dev, XGBE_PHY_MODE_PROPERTY,
					  &phy_mode);
	अगर (ret || म_भेद(phy_mode, phy_modes(PHY_INTERFACE_MODE_XGMII))) अणु
		dev_err(dev, "invalid %s property\n", XGBE_PHY_MODE_PROPERTY);
		अगर (!ret)
			ret = -EINVAL;
		जाओ err_io;
	पूर्ण
	pdata->phy_mode = PHY_INTERFACE_MODE_XGMII;

	/* Check क्रम per channel पूर्णांकerrupt support */
	अगर (device_property_present(dev, XGBE_DMA_IRQS_PROPERTY)) अणु
		pdata->per_channel_irq = 1;
		pdata->channel_irq_mode = XGBE_IRQ_MODE_EDGE;
	पूर्ण

	/* Obtain device settings unique to ACPI/OF */
	अगर (pdata->use_acpi)
		ret = xgbe_acpi_support(pdata);
	अन्यथा
		ret = xgbe_of_support(pdata);
	अगर (ret)
		जाओ err_io;

	/* Set the DMA coherency values */
	attr = device_get_dma_attr(dev);
	अगर (attr == DEV_DMA_NOT_SUPPORTED) अणु
		dev_err(dev, "DMA is not supported");
		ret = -ENODEV;
		जाओ err_io;
	पूर्ण
	pdata->coherent = (attr == DEV_DMA_COHERENT);
	अगर (pdata->coherent) अणु
		pdata->arcr = XGBE_DMA_OS_ARCR;
		pdata->awcr = XGBE_DMA_OS_AWCR;
	पूर्ण अन्यथा अणु
		pdata->arcr = XGBE_DMA_SYS_ARCR;
		pdata->awcr = XGBE_DMA_SYS_AWCR;
	पूर्ण

	/* Set the maximum fअगरo amounts */
	pdata->tx_max_fअगरo_size = pdata->vdata->tx_max_fअगरo_size;
	pdata->rx_max_fअगरo_size = pdata->vdata->rx_max_fअगरo_size;

	/* Set the hardware channel and queue counts */
	xgbe_set_counts(pdata);

	/* Always have XGMAC and XPCS (स्वतः-negotiation) पूर्णांकerrupts */
	pdata->irq_count = 2;

	/* Get the device पूर्णांकerrupt */
	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ err_io;
	pdata->dev_irq = ret;

	/* Get the per channel DMA पूर्णांकerrupts */
	अगर (pdata->per_channel_irq) अणु
		अचिन्हित पूर्णांक i, max = ARRAY_SIZE(pdata->channel_irq);

		क्रम (i = 0; (i < max) && (dma_irqnum < dma_irqend); i++) अणु
			ret = platक्रमm_get_irq(pdata->platdev, dma_irqnum++);
			अगर (ret < 0)
				जाओ err_io;

			pdata->channel_irq[i] = ret;
		पूर्ण

		pdata->channel_irq_count = max;

		pdata->irq_count += max;
	पूर्ण

	/* Get the स्वतः-negotiation पूर्णांकerrupt */
	ret = platक्रमm_get_irq(phy_pdev, phy_irqnum++);
	अगर (ret < 0)
		जाओ err_io;
	pdata->an_irq = ret;

	/* Configure the netdev resource */
	ret = xgbe_config_netdev(pdata);
	अगर (ret)
		जाओ err_io;

	netdev_notice(pdata->netdev, "net device enabled\n");

	वापस 0;

err_io:
	platक्रमm_device_put(phy_pdev);

err_phydev:
	xgbe_मुक्त_pdata(pdata);

err_alloc:
	dev_notice(dev, "net device not enabled\n");

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgbe_prv_data *pdata = platक्रमm_get_drvdata(pdev);

	xgbe_deconfig_netdev(pdata);

	platक्रमm_device_put(pdata->phy_platdev);

	xgbe_मुक्त_pdata(pdata);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक xgbe_platक्रमm_suspend(काष्ठा device *dev)
अणु
	काष्ठा xgbe_prv_data *pdata = dev_get_drvdata(dev);
	काष्ठा net_device *netdev = pdata->netdev;
	पूर्णांक ret = 0;

	DBGPR("-->xgbe_suspend\n");

	अगर (netअगर_running(netdev))
		ret = xgbe_घातerकरोwn(netdev, XGMAC_DRIVER_CONTEXT);

	pdata->lpm_ctrl = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL1);
	pdata->lpm_ctrl |= MDIO_CTRL1_LPOWER;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, pdata->lpm_ctrl);

	DBGPR("<--xgbe_suspend\n");

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_platक्रमm_resume(काष्ठा device *dev)
अणु
	काष्ठा xgbe_prv_data *pdata = dev_get_drvdata(dev);
	काष्ठा net_device *netdev = pdata->netdev;
	पूर्णांक ret = 0;

	DBGPR("-->xgbe_resume\n");

	pdata->lpm_ctrl &= ~MDIO_CTRL1_LPOWER;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, pdata->lpm_ctrl);

	अगर (netअगर_running(netdev)) अणु
		ret = xgbe_घातerup(netdev, XGMAC_DRIVER_CONTEXT);

		/* Schedule a restart in हाल the link or phy state changed
		 * जबतक we were घातered करोwn.
		 */
		schedule_work(&pdata->restart_work);
	पूर्ण

	DBGPR("<--xgbe_resume\n");

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा xgbe_version_data xgbe_v1 = अणु
	.init_function_ptrs_phy_impl	= xgbe_init_function_ptrs_phy_v1,
	.xpcs_access			= XGBE_XPCS_ACCESS_V1,
	.tx_max_fअगरo_size		= 81920,
	.rx_max_fअगरo_size		= 81920,
	.tx_tstamp_workaround		= 1,
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xgbe_acpi_match[] = अणु
	अणु .id = "AMDI8001",
	  .driver_data = (kernel_uदीर्घ_t)&xgbe_v1 पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, xgbe_acpi_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id xgbe_of_match[] = अणु
	अणु .compatible = "amd,xgbe-seattle-v1a",
	  .data = &xgbe_v1 पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, xgbe_of_match);
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(xgbe_platक्रमm_pm_ops,
			 xgbe_platक्रमm_suspend, xgbe_platक्रमm_resume);

अटल काष्ठा platक्रमm_driver xgbe_driver = अणु
	.driver = अणु
		.name = XGBE_DRV_NAME,
#अगर_घोषित CONFIG_ACPI
		.acpi_match_table = xgbe_acpi_match,
#पूर्ण_अगर
#अगर_घोषित CONFIG_OF
		.of_match_table = xgbe_of_match,
#पूर्ण_अगर
		.pm = &xgbe_platक्रमm_pm_ops,
	पूर्ण,
	.probe = xgbe_platक्रमm_probe,
	.हटाओ = xgbe_platक्रमm_हटाओ,
पूर्ण;

पूर्णांक xgbe_platक्रमm_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&xgbe_driver);
पूर्ण

व्योम xgbe_platक्रमm_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&xgbe_driver);
पूर्ण
