<शैली गुरु>
/*
 * AMD 10Gb Ethernet driver
 *
 * This file is available to you under your choice of the following two
 * licenses:
 *
 * License 1: GPLv2
 *
 * Copyright (c) 2016 Advanced Micro Devices, Inc.
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
 * Copyright (c) 2016 Advanced Micro Devices, Inc.
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
#समावेश <linux/pci.h>
#समावेश <linux/log2.h>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

अटल पूर्णांक xgbe_config_multi_msi(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक vector_count;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret;

	vector_count = XGBE_MSI_BASE_COUNT;
	vector_count += max(pdata->rx_ring_count,
			    pdata->tx_ring_count);

	ret = pci_alloc_irq_vectors(pdata->pcidev, XGBE_MSI_MIN_COUNT,
				    vector_count, PCI_IRQ_MSI | PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		dev_info(pdata->dev, "multi MSI/MSI-X enablement failed\n");
		वापस ret;
	पूर्ण

	pdata->isr_as_tasklet = 1;
	pdata->irq_count = ret;

	pdata->dev_irq = pci_irq_vector(pdata->pcidev, 0);
	pdata->ecc_irq = pci_irq_vector(pdata->pcidev, 1);
	pdata->i2c_irq = pci_irq_vector(pdata->pcidev, 2);
	pdata->an_irq = pci_irq_vector(pdata->pcidev, 3);

	क्रम (i = XGBE_MSI_BASE_COUNT, j = 0; i < ret; i++, j++)
		pdata->channel_irq[j] = pci_irq_vector(pdata->pcidev, i);
	pdata->channel_irq_count = j;

	pdata->per_channel_irq = 1;
	pdata->channel_irq_mode = XGBE_IRQ_MODE_LEVEL;

	अगर (netअगर_msg_probe(pdata))
		dev_dbg(pdata->dev, "multi %s interrupts enabled\n",
			pdata->pcidev->msix_enabled ? "MSI-X" : "MSI");

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_config_irqs(काष्ठा xgbe_prv_data *pdata)
अणु
	पूर्णांक ret;

	ret = xgbe_config_multi_msi(pdata);
	अगर (!ret)
		जाओ out;

	ret = pci_alloc_irq_vectors(pdata->pcidev, 1, 1,
				    PCI_IRQ_LEGACY | PCI_IRQ_MSI);
	अगर (ret < 0) अणु
		dev_info(pdata->dev, "single IRQ enablement failed\n");
		वापस ret;
	पूर्ण

	pdata->isr_as_tasklet = pdata->pcidev->msi_enabled ? 1 : 0;
	pdata->irq_count = 1;
	pdata->channel_irq_count = 1;

	pdata->dev_irq = pci_irq_vector(pdata->pcidev, 0);
	pdata->ecc_irq = pci_irq_vector(pdata->pcidev, 0);
	pdata->i2c_irq = pci_irq_vector(pdata->pcidev, 0);
	pdata->an_irq = pci_irq_vector(pdata->pcidev, 0);

	अगर (netअगर_msg_probe(pdata))
		dev_dbg(pdata->dev, "single %s interrupt enabled\n",
			pdata->pcidev->msi_enabled ?  "MSI" : "legacy");

out:
	अगर (netअगर_msg_probe(pdata)) अणु
		अचिन्हित पूर्णांक i;

		dev_dbg(pdata->dev, " dev irq=%d\n", pdata->dev_irq);
		dev_dbg(pdata->dev, " ecc irq=%d\n", pdata->ecc_irq);
		dev_dbg(pdata->dev, " i2c irq=%d\n", pdata->i2c_irq);
		dev_dbg(pdata->dev, "  an irq=%d\n", pdata->an_irq);
		क्रम (i = 0; i < pdata->channel_irq_count; i++)
			dev_dbg(pdata->dev, " dma%u irq=%d\n",
				i, pdata->channel_irq[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा xgbe_prv_data *pdata;
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem * स्थिर *iomap_table;
	काष्ठा pci_dev *rdev;
	अचिन्हित पूर्णांक ma_lo, ma_hi;
	अचिन्हित पूर्णांक reg;
	पूर्णांक bar_mask;
	पूर्णांक ret;

	pdata = xgbe_alloc_pdata(dev);
	अगर (IS_ERR(pdata)) अणु
		ret = PTR_ERR(pdata);
		जाओ err_alloc;
	पूर्ण

	pdata->pcidev = pdev;
	pci_set_drvdata(pdev, pdata);

	/* Get the version data */
	pdata->vdata = (काष्ठा xgbe_version_data *)id->driver_data;

	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(dev, "pcim_enable_device failed\n");
		जाओ err_pci_enable;
	पूर्ण

	/* Obtain the mmio areas क्रम the device */
	bar_mask = pci_select_bars(pdev, IORESOURCE_MEM);
	ret = pcim_iomap_regions(pdev, bar_mask, XGBE_DRV_NAME);
	अगर (ret) अणु
		dev_err(dev, "pcim_iomap_regions failed\n");
		जाओ err_pci_enable;
	पूर्ण

	iomap_table = pcim_iomap_table(pdev);
	अगर (!iomap_table) अणु
		dev_err(dev, "pcim_iomap_table failed\n");
		ret = -ENOMEM;
		जाओ err_pci_enable;
	पूर्ण

	pdata->xgmac_regs = iomap_table[XGBE_XGMAC_BAR];
	अगर (!pdata->xgmac_regs) अणु
		dev_err(dev, "xgmac ioremap failed\n");
		ret = -ENOMEM;
		जाओ err_pci_enable;
	पूर्ण
	pdata->xprop_regs = pdata->xgmac_regs + XGBE_MAC_PROP_OFFSET;
	pdata->xi2c_regs = pdata->xgmac_regs + XGBE_I2C_CTRL_OFFSET;
	अगर (netअगर_msg_probe(pdata)) अणु
		dev_dbg(dev, "xgmac_regs = %p\n", pdata->xgmac_regs);
		dev_dbg(dev, "xprop_regs = %p\n", pdata->xprop_regs);
		dev_dbg(dev, "xi2c_regs  = %p\n", pdata->xi2c_regs);
	पूर्ण

	pdata->xpcs_regs = iomap_table[XGBE_XPCS_BAR];
	अगर (!pdata->xpcs_regs) अणु
		dev_err(dev, "xpcs ioremap failed\n");
		ret = -ENOMEM;
		जाओ err_pci_enable;
	पूर्ण
	अगर (netअगर_msg_probe(pdata))
		dev_dbg(dev, "xpcs_regs  = %p\n", pdata->xpcs_regs);

	/* Set the PCS indirect addressing definition रेजिस्टरs */
	rdev = pci_get_करोमुख्य_bus_and_slot(0, 0, PCI_DEVFN(0, 0));
	अगर (rdev &&
	    (rdev->venकरोr == PCI_VENDOR_ID_AMD) && (rdev->device == 0x15d0)) अणु
		pdata->xpcs_winकरोw_def_reg = PCS_V2_RV_WINDOW_DEF;
		pdata->xpcs_winकरोw_sel_reg = PCS_V2_RV_WINDOW_SELECT;
	पूर्ण अन्यथा अणु
		pdata->xpcs_winकरोw_def_reg = PCS_V2_WINDOW_DEF;
		pdata->xpcs_winकरोw_sel_reg = PCS_V2_WINDOW_SELECT;
	पूर्ण
	pci_dev_put(rdev);

	/* Configure the PCS indirect addressing support */
	reg = XPCS32_IOREAD(pdata, pdata->xpcs_winकरोw_def_reg);
	pdata->xpcs_winकरोw = XPCS_GET_BITS(reg, PCS_V2_WINDOW_DEF, OFFSET);
	pdata->xpcs_winकरोw <<= 6;
	pdata->xpcs_winकरोw_size = XPCS_GET_BITS(reg, PCS_V2_WINDOW_DEF, SIZE);
	pdata->xpcs_winकरोw_size = 1 << (pdata->xpcs_winकरोw_size + 7);
	pdata->xpcs_winकरोw_mask = pdata->xpcs_winकरोw_size - 1;
	अगर (netअगर_msg_probe(pdata)) अणु
		dev_dbg(dev, "xpcs window def  = %#010x\n",
			pdata->xpcs_winकरोw_def_reg);
		dev_dbg(dev, "xpcs window sel  = %#010x\n",
			pdata->xpcs_winकरोw_sel_reg);
		dev_dbg(dev, "xpcs window      = %#010x\n",
			pdata->xpcs_winकरोw);
		dev_dbg(dev, "xpcs window size = %#010x\n",
			pdata->xpcs_winकरोw_size);
		dev_dbg(dev, "xpcs window mask = %#010x\n",
			pdata->xpcs_winकरोw_mask);
	पूर्ण

	pci_set_master(pdev);

	/* Enable all पूर्णांकerrupts in the hardware */
	XP_IOWRITE(pdata, XP_INT_EN, 0x1fffff);

	/* Retrieve the MAC address */
	ma_lo = XP_IOREAD(pdata, XP_MAC_ADDR_LO);
	ma_hi = XP_IOREAD(pdata, XP_MAC_ADDR_HI);
	pdata->mac_addr[0] = ma_lo & 0xff;
	pdata->mac_addr[1] = (ma_lo >> 8) & 0xff;
	pdata->mac_addr[2] = (ma_lo >> 16) & 0xff;
	pdata->mac_addr[3] = (ma_lo >> 24) & 0xff;
	pdata->mac_addr[4] = ma_hi & 0xff;
	pdata->mac_addr[5] = (ma_hi >> 8) & 0xff;
	अगर (!XP_GET_BITS(ma_hi, XP_MAC_ADDR_HI, VALID) ||
	    !is_valid_ether_addr(pdata->mac_addr)) अणु
		dev_err(dev, "invalid mac address\n");
		ret = -EINVAL;
		जाओ err_pci_enable;
	पूर्ण

	/* Clock settings */
	pdata->sysclk_rate = XGBE_V2_DMA_CLOCK_FREQ;
	pdata->ptpclk_rate = XGBE_V2_PTP_CLOCK_FREQ;

	/* Set the DMA coherency values */
	pdata->coherent = 1;
	pdata->arcr = XGBE_DMA_PCI_ARCR;
	pdata->awcr = XGBE_DMA_PCI_AWCR;
	pdata->awarcr = XGBE_DMA_PCI_AWARCR;

	/* Read the port property रेजिस्टरs */
	pdata->pp0 = XP_IOREAD(pdata, XP_PROP_0);
	pdata->pp1 = XP_IOREAD(pdata, XP_PROP_1);
	pdata->pp2 = XP_IOREAD(pdata, XP_PROP_2);
	pdata->pp3 = XP_IOREAD(pdata, XP_PROP_3);
	pdata->pp4 = XP_IOREAD(pdata, XP_PROP_4);
	अगर (netअगर_msg_probe(pdata)) अणु
		dev_dbg(dev, "port property 0 = %#010x\n", pdata->pp0);
		dev_dbg(dev, "port property 1 = %#010x\n", pdata->pp1);
		dev_dbg(dev, "port property 2 = %#010x\n", pdata->pp2);
		dev_dbg(dev, "port property 3 = %#010x\n", pdata->pp3);
		dev_dbg(dev, "port property 4 = %#010x\n", pdata->pp4);
	पूर्ण

	/* Set the maximum channels and queues */
	pdata->tx_max_channel_count = XP_GET_BITS(pdata->pp1, XP_PROP_1,
						  MAX_TX_DMA);
	pdata->rx_max_channel_count = XP_GET_BITS(pdata->pp1, XP_PROP_1,
						  MAX_RX_DMA);
	pdata->tx_max_q_count = XP_GET_BITS(pdata->pp1, XP_PROP_1,
					    MAX_TX_QUEUES);
	pdata->rx_max_q_count = XP_GET_BITS(pdata->pp1, XP_PROP_1,
					    MAX_RX_QUEUES);
	अगर (netअगर_msg_probe(pdata)) अणु
		dev_dbg(dev, "max tx/rx channel count = %u/%u\n",
			pdata->tx_max_channel_count,
			pdata->rx_max_channel_count);
		dev_dbg(dev, "max tx/rx hw queue count = %u/%u\n",
			pdata->tx_max_q_count, pdata->rx_max_q_count);
	पूर्ण

	/* Set the hardware channel and queue counts */
	xgbe_set_counts(pdata);

	/* Set the maximum fअगरo amounts */
	pdata->tx_max_fअगरo_size = XP_GET_BITS(pdata->pp2, XP_PROP_2,
					      TX_FIFO_SIZE);
	pdata->tx_max_fअगरo_size *= 16384;
	pdata->tx_max_fअगरo_size = min(pdata->tx_max_fअगरo_size,
				      pdata->vdata->tx_max_fअगरo_size);
	pdata->rx_max_fअगरo_size = XP_GET_BITS(pdata->pp2, XP_PROP_2,
					      RX_FIFO_SIZE);
	pdata->rx_max_fअगरo_size *= 16384;
	pdata->rx_max_fअगरo_size = min(pdata->rx_max_fअगरo_size,
				      pdata->vdata->rx_max_fअगरo_size);
	अगर (netअगर_msg_probe(pdata))
		dev_dbg(dev, "max tx/rx max fifo size = %u/%u\n",
			pdata->tx_max_fअगरo_size, pdata->rx_max_fअगरo_size);

	/* Configure पूर्णांकerrupt support */
	ret = xgbe_config_irqs(pdata);
	अगर (ret)
		जाओ err_pci_enable;

	/* Configure the netdev resource */
	ret = xgbe_config_netdev(pdata);
	अगर (ret)
		जाओ err_irq_vectors;

	netdev_notice(pdata->netdev, "net device enabled\n");

	वापस 0;

err_irq_vectors:
	pci_मुक्त_irq_vectors(pdata->pcidev);

err_pci_enable:
	xgbe_मुक्त_pdata(pdata);

err_alloc:
	dev_notice(dev, "net device not enabled\n");

	वापस ret;
पूर्ण

अटल व्योम xgbe_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा xgbe_prv_data *pdata = pci_get_drvdata(pdev);

	xgbe_deconfig_netdev(pdata);

	pci_मुक्त_irq_vectors(pdata->pcidev);

	xgbe_मुक्त_pdata(pdata);
पूर्ण

अटल पूर्णांक __maybe_unused xgbe_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा xgbe_prv_data *pdata = dev_get_drvdata(dev);
	काष्ठा net_device *netdev = pdata->netdev;
	पूर्णांक ret = 0;

	अगर (netअगर_running(netdev))
		ret = xgbe_घातerकरोwn(netdev, XGMAC_DRIVER_CONTEXT);

	pdata->lpm_ctrl = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL1);
	pdata->lpm_ctrl |= MDIO_CTRL1_LPOWER;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, pdata->lpm_ctrl);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused xgbe_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा xgbe_prv_data *pdata = dev_get_drvdata(dev);
	काष्ठा net_device *netdev = pdata->netdev;
	पूर्णांक ret = 0;

	XP_IOWRITE(pdata, XP_INT_EN, 0x1fffff);

	pdata->lpm_ctrl &= ~MDIO_CTRL1_LPOWER;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, pdata->lpm_ctrl);

	अगर (netअगर_running(netdev)) अणु
		ret = xgbe_घातerup(netdev, XGMAC_DRIVER_CONTEXT);

		/* Schedule a restart in हाल the link or phy state changed
		 * जबतक we were घातered करोwn.
		 */
		schedule_work(&pdata->restart_work);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा xgbe_version_data xgbe_v2a = अणु
	.init_function_ptrs_phy_impl	= xgbe_init_function_ptrs_phy_v2,
	.xpcs_access			= XGBE_XPCS_ACCESS_V2,
	.mmc_64bit			= 1,
	.tx_max_fअगरo_size		= 229376,
	.rx_max_fअगरo_size		= 229376,
	.tx_tstamp_workaround		= 1,
	.ecc_support			= 1,
	.i2c_support			= 1,
	.irq_reissue_support		= 1,
	.tx_desc_prefetch		= 5,
	.rx_desc_prefetch		= 5,
	.an_cdr_workaround		= 1,
पूर्ण;

अटल स्थिर काष्ठा xgbe_version_data xgbe_v2b = अणु
	.init_function_ptrs_phy_impl	= xgbe_init_function_ptrs_phy_v2,
	.xpcs_access			= XGBE_XPCS_ACCESS_V2,
	.mmc_64bit			= 1,
	.tx_max_fअगरo_size		= 65536,
	.rx_max_fअगरo_size		= 65536,
	.tx_tstamp_workaround		= 1,
	.ecc_support			= 1,
	.i2c_support			= 1,
	.irq_reissue_support		= 1,
	.tx_desc_prefetch		= 5,
	.rx_desc_prefetch		= 5,
	.an_cdr_workaround		= 1,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id xgbe_pci_table[] = अणु
	अणु PCI_VDEVICE(AMD, 0x1458),
	  .driver_data = (kernel_uदीर्घ_t)&xgbe_v2a पूर्ण,
	अणु PCI_VDEVICE(AMD, 0x1459),
	  .driver_data = (kernel_uदीर्घ_t)&xgbe_v2b पूर्ण,
	/* Last entry must be zero */
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, xgbe_pci_table);

अटल SIMPLE_DEV_PM_OPS(xgbe_pci_pm_ops, xgbe_pci_suspend, xgbe_pci_resume);

अटल काष्ठा pci_driver xgbe_driver = अणु
	.name = XGBE_DRV_NAME,
	.id_table = xgbe_pci_table,
	.probe = xgbe_pci_probe,
	.हटाओ = xgbe_pci_हटाओ,
	.driver = अणु
		.pm = &xgbe_pci_pm_ops,
	पूर्ण
पूर्ण;

पूर्णांक xgbe_pci_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&xgbe_driver);
पूर्ण

व्योम xgbe_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&xgbe_driver);
पूर्ण
