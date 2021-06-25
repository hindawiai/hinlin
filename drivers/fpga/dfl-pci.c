<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम FPGA Device Feature List (DFL) PCIe device
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Zhang Yi <Yi.Z.Zhang@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 *   Joseph Grecco <joe.grecco@पूर्णांकel.com>
 *   Enno Luebbers <enno.luebbers@पूर्णांकel.com>
 *   Tim Whisonant <tim.whisonant@पूर्णांकel.com>
 *   Ananda Ravuri <ananda.ravuri@पूर्णांकel.com>
 *   Henry Mitchel <henry.mitchel@पूर्णांकel.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/aer.h>

#समावेश "dfl.h"

#घोषणा DRV_VERSION	"0.8"
#घोषणा DRV_NAME	"dfl-pci"

#घोषणा PCI_VSEC_ID_INTEL_DFLS 0x43

#घोषणा PCI_VNDR_DFLS_CNT 0x8
#घोषणा PCI_VNDR_DFLS_RES 0xc

#घोषणा PCI_VNDR_DFLS_RES_BAR_MASK GENMASK(2, 0)
#घोषणा PCI_VNDR_DFLS_RES_OFF_MASK GENMASK(31, 3)

काष्ठा cci_drvdata अणु
	काष्ठा dfl_fpga_cdev *cdev;	/* container device */
पूर्ण;

अटल व्योम __iomem *cci_pci_ioremap_bar0(काष्ठा pci_dev *pcidev)
अणु
	अगर (pcim_iomap_regions(pcidev, BIT(0), DRV_NAME))
		वापस शून्य;

	वापस pcim_iomap_table(pcidev)[0];
पूर्ण

अटल पूर्णांक cci_pci_alloc_irq(काष्ठा pci_dev *pcidev)
अणु
	पूर्णांक ret, nvec = pci_msix_vec_count(pcidev);

	अगर (nvec <= 0) अणु
		dev_dbg(&pcidev->dev, "fpga interrupt not supported\n");
		वापस 0;
	पूर्ण

	ret = pci_alloc_irq_vectors(pcidev, nvec, nvec, PCI_IRQ_MSIX);
	अगर (ret < 0)
		वापस ret;

	वापस nvec;
पूर्ण

अटल व्योम cci_pci_मुक्त_irq(काष्ठा pci_dev *pcidev)
अणु
	pci_मुक्त_irq_vectors(pcidev);
पूर्ण

/* PCI Device ID */
#घोषणा PCIE_DEVICE_ID_PF_INT_5_X		0xBCBD
#घोषणा PCIE_DEVICE_ID_PF_INT_6_X		0xBCC0
#घोषणा PCIE_DEVICE_ID_PF_DSC_1_X		0x09C4
#घोषणा PCIE_DEVICE_ID_INTEL_PAC_N3000		0x0B30
#घोषणा PCIE_DEVICE_ID_INTEL_PAC_D5005		0x0B2B
/* VF Device */
#घोषणा PCIE_DEVICE_ID_VF_INT_5_X		0xBCBF
#घोषणा PCIE_DEVICE_ID_VF_INT_6_X		0xBCC1
#घोषणा PCIE_DEVICE_ID_VF_DSC_1_X		0x09C5
#घोषणा PCIE_DEVICE_ID_INTEL_PAC_D5005_VF	0x0B2C

अटल काष्ठा pci_device_id cci_pcie_id_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCIE_DEVICE_ID_PF_INT_5_X),पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCIE_DEVICE_ID_VF_INT_5_X),पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCIE_DEVICE_ID_PF_INT_6_X),पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCIE_DEVICE_ID_VF_INT_6_X),पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCIE_DEVICE_ID_PF_DSC_1_X),पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCIE_DEVICE_ID_VF_DSC_1_X),पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCIE_DEVICE_ID_INTEL_PAC_N3000),पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCIE_DEVICE_ID_INTEL_PAC_D5005),पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCIE_DEVICE_ID_INTEL_PAC_D5005_VF),पूर्ण,
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cci_pcie_id_tbl);

अटल पूर्णांक cci_init_drvdata(काष्ठा pci_dev *pcidev)
अणु
	काष्ठा cci_drvdata *drvdata;

	drvdata = devm_kzalloc(&pcidev->dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	pci_set_drvdata(pcidev, drvdata);

	वापस 0;
पूर्ण

अटल व्योम cci_हटाओ_feature_devs(काष्ठा pci_dev *pcidev)
अणु
	काष्ठा cci_drvdata *drvdata = pci_get_drvdata(pcidev);

	/* हटाओ all children feature devices */
	dfl_fpga_feature_devs_हटाओ(drvdata->cdev);
	cci_pci_मुक्त_irq(pcidev);
पूर्ण

अटल पूर्णांक *cci_pci_create_irq_table(काष्ठा pci_dev *pcidev, अचिन्हित पूर्णांक nvec)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक *table;

	table = kसुस्मृति(nvec, माप(पूर्णांक), GFP_KERNEL);
	अगर (!table)
		वापस table;

	क्रम (i = 0; i < nvec; i++)
		table[i] = pci_irq_vector(pcidev, i);

	वापस table;
पूर्ण

अटल पूर्णांक find_dfls_by_vsec(काष्ठा pci_dev *pcidev, काष्ठा dfl_fpga_क्रमागत_info *info)
अणु
	u32 bir, offset, vndr_hdr, dfl_cnt, dfl_res;
	पूर्णांक dfl_res_off, i, bars, voff = 0;
	resource_माप_प्रकार start, len;

	जबतक ((voff = pci_find_next_ext_capability(pcidev, voff, PCI_EXT_CAP_ID_VNDR))) अणु
		vndr_hdr = 0;
		pci_पढ़ो_config_dword(pcidev, voff + PCI_VNDR_HEADER, &vndr_hdr);

		अगर (PCI_VNDR_HEADER_ID(vndr_hdr) == PCI_VSEC_ID_INTEL_DFLS &&
		    pcidev->venकरोr == PCI_VENDOR_ID_INTEL)
			अवरोध;
	पूर्ण

	अगर (!voff) अणु
		dev_dbg(&pcidev->dev, "%s no DFL VSEC found\n", __func__);
		वापस -ENODEV;
	पूर्ण

	dfl_cnt = 0;
	pci_पढ़ो_config_dword(pcidev, voff + PCI_VNDR_DFLS_CNT, &dfl_cnt);
	अगर (dfl_cnt > PCI_STD_NUM_BARS) अणु
		dev_err(&pcidev->dev, "%s too many DFLs %d > %d\n",
			__func__, dfl_cnt, PCI_STD_NUM_BARS);
		वापस -EINVAL;
	पूर्ण

	dfl_res_off = voff + PCI_VNDR_DFLS_RES;
	अगर (dfl_res_off + (dfl_cnt * माप(u32)) > PCI_CFG_SPACE_EXP_SIZE) अणु
		dev_err(&pcidev->dev, "%s DFL VSEC too big for PCIe config space\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0, bars = 0; i < dfl_cnt; i++, dfl_res_off += माप(u32)) अणु
		dfl_res = GENMASK(31, 0);
		pci_पढ़ो_config_dword(pcidev, dfl_res_off, &dfl_res);

		bir = dfl_res & PCI_VNDR_DFLS_RES_BAR_MASK;
		अगर (bir >= PCI_STD_NUM_BARS) अणु
			dev_err(&pcidev->dev, "%s bad bir number %d\n",
				__func__, bir);
			वापस -EINVAL;
		पूर्ण

		अगर (bars & BIT(bir)) अणु
			dev_err(&pcidev->dev, "%s DFL for BAR %d already specified\n",
				__func__, bir);
			वापस -EINVAL;
		पूर्ण

		bars |= BIT(bir);

		len = pci_resource_len(pcidev, bir);
		offset = dfl_res & PCI_VNDR_DFLS_RES_OFF_MASK;
		अगर (offset >= len) अणु
			dev_err(&pcidev->dev, "%s bad offset %u >= %pa\n",
				__func__, offset, &len);
			वापस -EINVAL;
		पूर्ण

		dev_dbg(&pcidev->dev, "%s BAR %d offset 0x%x\n", __func__, bir, offset);

		len -= offset;

		start = pci_resource_start(pcidev, bir) + offset;

		dfl_fpga_क्रमागत_info_add_dfl(info, start, len);
	पूर्ण

	वापस 0;
पूर्ण

/* शेष method of finding dfls starting at offset 0 of bar 0 */
अटल पूर्णांक find_dfls_by_शेष(काष्ठा pci_dev *pcidev,
				काष्ठा dfl_fpga_क्रमागत_info *info)
अणु
	पूर्णांक port_num, bar, i, ret = 0;
	resource_माप_प्रकार start, len;
	व्योम __iomem *base;
	u32 offset;
	u64 v;

	/* start to find Device Feature List from Bar 0 */
	base = cci_pci_ioremap_bar0(pcidev);
	अगर (!base)
		वापस -ENOMEM;

	/*
	 * PF device has FME and Ports/AFUs, and VF device only has one
	 * Port/AFU. Check them and add related "Device Feature List" info
	 * क्रम the next step क्रमागतeration.
	 */
	अगर (dfl_feature_is_fme(base)) अणु
		start = pci_resource_start(pcidev, 0);
		len = pci_resource_len(pcidev, 0);

		dfl_fpga_क्रमागत_info_add_dfl(info, start, len);

		/*
		 * find more Device Feature Lists (e.g. Ports) per inक्रमmation
		 * indicated by FME module.
		 */
		v = पढ़ोq(base + FME_HDR_CAP);
		port_num = FIELD_GET(FME_CAP_NUM_PORTS, v);

		WARN_ON(port_num > MAX_DFL_FPGA_PORT_NUM);

		क्रम (i = 0; i < port_num; i++) अणु
			v = पढ़ोq(base + FME_HDR_PORT_OFST(i));

			/* skip ports which are not implemented. */
			अगर (!(v & FME_PORT_OFST_IMP))
				जारी;

			/*
			 * add Port's Device Feature List inक्रमmation क्रम next
			 * step क्रमागतeration.
			 */
			bar = FIELD_GET(FME_PORT_OFST_BAR_ID, v);
			offset = FIELD_GET(FME_PORT_OFST_DFH_OFST, v);
			start = pci_resource_start(pcidev, bar) + offset;
			len = pci_resource_len(pcidev, bar) - offset;

			dfl_fpga_क्रमागत_info_add_dfl(info, start, len);
		पूर्ण
	पूर्ण अन्यथा अगर (dfl_feature_is_port(base)) अणु
		start = pci_resource_start(pcidev, 0);
		len = pci_resource_len(pcidev, 0);

		dfl_fpga_क्रमागत_info_add_dfl(info, start, len);
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
	पूर्ण

	/* release I/O mappings क्रम next step क्रमागतeration */
	pcim_iounmap_regions(pcidev, BIT(0));

	वापस ret;
पूर्ण

/* क्रमागतerate feature devices under pci device */
अटल पूर्णांक cci_क्रमागतerate_feature_devs(काष्ठा pci_dev *pcidev)
अणु
	काष्ठा cci_drvdata *drvdata = pci_get_drvdata(pcidev);
	काष्ठा dfl_fpga_क्रमागत_info *info;
	काष्ठा dfl_fpga_cdev *cdev;
	पूर्णांक nvec, ret = 0;
	पूर्णांक *irq_table;

	/* allocate क्रमागतeration info via pci_dev */
	info = dfl_fpga_क्रमागत_info_alloc(&pcidev->dev);
	अगर (!info)
		वापस -ENOMEM;

	/* add irq info क्रम क्रमागतeration अगर the device support irq */
	nvec = cci_pci_alloc_irq(pcidev);
	अगर (nvec < 0) अणु
		dev_err(&pcidev->dev, "Fail to alloc irq %d.\n", nvec);
		ret = nvec;
		जाओ क्रमागत_info_मुक्त_निकास;
	पूर्ण अन्यथा अगर (nvec) अणु
		irq_table = cci_pci_create_irq_table(pcidev, nvec);
		अगर (!irq_table) अणु
			ret = -ENOMEM;
			जाओ irq_मुक्त_निकास;
		पूर्ण

		ret = dfl_fpga_क्रमागत_info_add_irq(info, nvec, irq_table);
		kमुक्त(irq_table);
		अगर (ret)
			जाओ irq_मुक्त_निकास;
	पूर्ण

	ret = find_dfls_by_vsec(pcidev, info);
	अगर (ret == -ENODEV)
		ret = find_dfls_by_शेष(pcidev, info);

	अगर (ret)
		जाओ irq_मुक्त_निकास;

	/* start क्रमागतeration with prepared क्रमागतeration inक्रमmation */
	cdev = dfl_fpga_feature_devs_क्रमागतerate(info);
	अगर (IS_ERR(cdev)) अणु
		dev_err(&pcidev->dev, "Enumeration failure\n");
		ret = PTR_ERR(cdev);
		जाओ irq_मुक्त_निकास;
	पूर्ण

	drvdata->cdev = cdev;

irq_मुक्त_निकास:
	अगर (ret)
		cci_pci_मुक्त_irq(pcidev);
क्रमागत_info_मुक्त_निकास:
	dfl_fpga_क्रमागत_info_मुक्त(info);

	वापस ret;
पूर्ण

अटल
पूर्णांक cci_pci_probe(काष्ठा pci_dev *pcidev, स्थिर काष्ठा pci_device_id *pcidevid)
अणु
	पूर्णांक ret;

	ret = pcim_enable_device(pcidev);
	अगर (ret < 0) अणु
		dev_err(&pcidev->dev, "Failed to enable device %d.\n", ret);
		वापस ret;
	पूर्ण

	ret = pci_enable_pcie_error_reporting(pcidev);
	अगर (ret && ret != -EINVAL)
		dev_info(&pcidev->dev, "PCIE AER unavailable %d.\n", ret);

	pci_set_master(pcidev);

	अगर (!pci_set_dma_mask(pcidev, DMA_BIT_MASK(64))) अणु
		ret = pci_set_consistent_dma_mask(pcidev, DMA_BIT_MASK(64));
		अगर (ret)
			जाओ disable_error_report_निकास;
	पूर्ण अन्यथा अगर (!pci_set_dma_mask(pcidev, DMA_BIT_MASK(32))) अणु
		ret = pci_set_consistent_dma_mask(pcidev, DMA_BIT_MASK(32));
		अगर (ret)
			जाओ disable_error_report_निकास;
	पूर्ण अन्यथा अणु
		ret = -EIO;
		dev_err(&pcidev->dev, "No suitable DMA support available.\n");
		जाओ disable_error_report_निकास;
	पूर्ण

	ret = cci_init_drvdata(pcidev);
	अगर (ret) अणु
		dev_err(&pcidev->dev, "Fail to init drvdata %d.\n", ret);
		जाओ disable_error_report_निकास;
	पूर्ण

	ret = cci_क्रमागतerate_feature_devs(pcidev);
	अगर (!ret)
		वापस ret;

	dev_err(&pcidev->dev, "enumeration failure %d.\n", ret);

disable_error_report_निकास:
	pci_disable_pcie_error_reporting(pcidev);
	वापस ret;
पूर्ण

अटल पूर्णांक cci_pci_sriov_configure(काष्ठा pci_dev *pcidev, पूर्णांक num_vfs)
अणु
	काष्ठा cci_drvdata *drvdata = pci_get_drvdata(pcidev);
	काष्ठा dfl_fpga_cdev *cdev = drvdata->cdev;

	अगर (!num_vfs) अणु
		/*
		 * disable SRIOV and then put released ports back to शेष
		 * PF access mode.
		 */
		pci_disable_sriov(pcidev);

		dfl_fpga_cdev_config_ports_pf(cdev);

	पूर्ण अन्यथा अणु
		पूर्णांक ret;

		/*
		 * beक्रमe enable SRIOV, put released ports पूर्णांकo VF access mode
		 * first of all.
		 */
		ret = dfl_fpga_cdev_config_ports_vf(cdev, num_vfs);
		अगर (ret)
			वापस ret;

		ret = pci_enable_sriov(pcidev, num_vfs);
		अगर (ret) अणु
			dfl_fpga_cdev_config_ports_pf(cdev);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस num_vfs;
पूर्ण

अटल व्योम cci_pci_हटाओ(काष्ठा pci_dev *pcidev)
अणु
	अगर (dev_is_pf(&pcidev->dev))
		cci_pci_sriov_configure(pcidev, 0);

	cci_हटाओ_feature_devs(pcidev);
	pci_disable_pcie_error_reporting(pcidev);
पूर्ण

अटल काष्ठा pci_driver cci_pci_driver = अणु
	.name = DRV_NAME,
	.id_table = cci_pcie_id_tbl,
	.probe = cci_pci_probe,
	.हटाओ = cci_pci_हटाओ,
	.sriov_configure = cci_pci_sriov_configure,
पूर्ण;

module_pci_driver(cci_pci_driver);

MODULE_DESCRIPTION("FPGA DFL PCIe Device Driver");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
