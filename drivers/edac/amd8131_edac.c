<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * amd8131_edac.c, AMD8131 hypertransport chip EDAC kernel module
 *
 * Copyright (c) 2008 Wind River Systems, Inc.
 *
 * Authors:	Cao Qingtao <qingtao.cao@windriver.com>
 * 		Benjamin Walsh <benjamin.walsh@windriver.com>
 * 		Hu Yongqi <yongqi.hu@windriver.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/edac.h>
#समावेश <linux/pci_ids.h>

#समावेश "edac_module.h"
#समावेश "amd8131_edac.h"

#घोषणा AMD8131_EDAC_REVISION	" Ver: 1.0.0"
#घोषणा AMD8131_EDAC_MOD_STR	"amd8131_edac"

/* Wrapper functions क्रम accessing PCI configuration space */
अटल व्योम edac_pci_पढ़ो_dword(काष्ठा pci_dev *dev, पूर्णांक reg, u32 *val32)
अणु
	पूर्णांक ret;

	ret = pci_पढ़ो_config_dword(dev, reg, val32);
	अगर (ret != 0)
		prपूर्णांकk(KERN_ERR AMD8131_EDAC_MOD_STR
			" PCI Access Read Error at 0x%x\n", reg);
पूर्ण

अटल व्योम edac_pci_ग_लिखो_dword(काष्ठा pci_dev *dev, पूर्णांक reg, u32 val32)
अणु
	पूर्णांक ret;

	ret = pci_ग_लिखो_config_dword(dev, reg, val32);
	अगर (ret != 0)
		prपूर्णांकk(KERN_ERR AMD8131_EDAC_MOD_STR
			" PCI Access Write Error at 0x%x\n", reg);
पूर्ण

/* Support up to two AMD8131 chipsets on a platक्रमm */
अटल काष्ठा amd8131_dev_info amd8131_devices[] = अणु
	अणु
	.inst = NORTH_A,
	.devfn = DEVFN_PCIX_BRIDGE_NORTH_A,
	.ctl_name = "AMD8131_PCIX_NORTH_A",
	पूर्ण,
	अणु
	.inst = NORTH_B,
	.devfn = DEVFN_PCIX_BRIDGE_NORTH_B,
	.ctl_name = "AMD8131_PCIX_NORTH_B",
	पूर्ण,
	अणु
	.inst = SOUTH_A,
	.devfn = DEVFN_PCIX_BRIDGE_SOUTH_A,
	.ctl_name = "AMD8131_PCIX_SOUTH_A",
	पूर्ण,
	अणु
	.inst = SOUTH_B,
	.devfn = DEVFN_PCIX_BRIDGE_SOUTH_B,
	.ctl_name = "AMD8131_PCIX_SOUTH_B",
	पूर्ण,
	अणु.inst = NO_BRIDGE,पूर्ण,
पूर्ण;

अटल व्योम amd8131_pcix_init(काष्ठा amd8131_dev_info *dev_info)
अणु
	u32 val32;
	काष्ठा pci_dev *dev = dev_info->dev;

	/* First clear error detection flags */
	edac_pci_पढ़ो_dword(dev, REG_MEM_LIM, &val32);
	अगर (val32 & MEM_LIMIT_MASK)
		edac_pci_ग_लिखो_dword(dev, REG_MEM_LIM, val32);

	/* Clear Discard Timer Timeकरोut flag */
	edac_pci_पढ़ो_dword(dev, REG_INT_CTLR, &val32);
	अगर (val32 & INT_CTLR_DTS)
		edac_pci_ग_लिखो_dword(dev, REG_INT_CTLR, val32);

	/* Clear CRC Error flag on link side A */
	edac_pci_पढ़ो_dword(dev, REG_LNK_CTRL_A, &val32);
	अगर (val32 & LNK_CTRL_CRCERR_A)
		edac_pci_ग_लिखो_dword(dev, REG_LNK_CTRL_A, val32);

	/* Clear CRC Error flag on link side B */
	edac_pci_पढ़ो_dword(dev, REG_LNK_CTRL_B, &val32);
	अगर (val32 & LNK_CTRL_CRCERR_B)
		edac_pci_ग_लिखो_dword(dev, REG_LNK_CTRL_B, val32);

	/*
	 * Then enable all error detections.
	 *
	 * Setup Discard Timer Sync Flood Enable,
	 * System Error Enable and Parity Error Enable.
	 */
	edac_pci_पढ़ो_dword(dev, REG_INT_CTLR, &val32);
	val32 |= INT_CTLR_PERR | INT_CTLR_SERR | INT_CTLR_DTSE;
	edac_pci_ग_लिखो_dword(dev, REG_INT_CTLR, val32);

	/* Enable overall SERR Error detection */
	edac_pci_पढ़ो_dword(dev, REG_STS_CMD, &val32);
	val32 |= STS_CMD_SERREN;
	edac_pci_ग_लिखो_dword(dev, REG_STS_CMD, val32);

	/* Setup CRC Flood Enable क्रम link side A */
	edac_pci_पढ़ो_dword(dev, REG_LNK_CTRL_A, &val32);
	val32 |= LNK_CTRL_CRCFEN;
	edac_pci_ग_लिखो_dword(dev, REG_LNK_CTRL_A, val32);

	/* Setup CRC Flood Enable क्रम link side B */
	edac_pci_पढ़ो_dword(dev, REG_LNK_CTRL_B, &val32);
	val32 |= LNK_CTRL_CRCFEN;
	edac_pci_ग_लिखो_dword(dev, REG_LNK_CTRL_B, val32);
पूर्ण

अटल व्योम amd8131_pcix_निकास(काष्ठा amd8131_dev_info *dev_info)
अणु
	u32 val32;
	काष्ठा pci_dev *dev = dev_info->dev;

	/* Disable SERR, PERR and DTSE Error detection */
	edac_pci_पढ़ो_dword(dev, REG_INT_CTLR, &val32);
	val32 &= ~(INT_CTLR_PERR | INT_CTLR_SERR | INT_CTLR_DTSE);
	edac_pci_ग_लिखो_dword(dev, REG_INT_CTLR, val32);

	/* Disable overall System Error detection */
	edac_pci_पढ़ो_dword(dev, REG_STS_CMD, &val32);
	val32 &= ~STS_CMD_SERREN;
	edac_pci_ग_लिखो_dword(dev, REG_STS_CMD, val32);

	/* Disable CRC Sync Flood on link side A */
	edac_pci_पढ़ो_dword(dev, REG_LNK_CTRL_A, &val32);
	val32 &= ~LNK_CTRL_CRCFEN;
	edac_pci_ग_लिखो_dword(dev, REG_LNK_CTRL_A, val32);

	/* Disable CRC Sync Flood on link side B */
	edac_pci_पढ़ो_dword(dev, REG_LNK_CTRL_B, &val32);
	val32 &= ~LNK_CTRL_CRCFEN;
	edac_pci_ग_लिखो_dword(dev, REG_LNK_CTRL_B, val32);
पूर्ण

अटल व्योम amd8131_pcix_check(काष्ठा edac_pci_ctl_info *edac_dev)
अणु
	काष्ठा amd8131_dev_info *dev_info = edac_dev->pvt_info;
	काष्ठा pci_dev *dev = dev_info->dev;
	u32 val32;

	/* Check PCI-X Bridge Memory Base-Limit Register क्रम errors */
	edac_pci_पढ़ो_dword(dev, REG_MEM_LIM, &val32);
	अगर (val32 & MEM_LIMIT_MASK) अणु
		prपूर्णांकk(KERN_INFO "Error(s) in mem limit register "
			"on %s bridge\n", dev_info->ctl_name);
		prपूर्णांकk(KERN_INFO "DPE: %d, RSE: %d, RMA: %d\n"
			"RTA: %d, STA: %d, MDPE: %d\n",
			val32 & MEM_LIMIT_DPE,
			val32 & MEM_LIMIT_RSE,
			val32 & MEM_LIMIT_RMA,
			val32 & MEM_LIMIT_RTA,
			val32 & MEM_LIMIT_STA,
			val32 & MEM_LIMIT_MDPE);

		val32 |= MEM_LIMIT_MASK;
		edac_pci_ग_लिखो_dword(dev, REG_MEM_LIM, val32);

		edac_pci_handle_npe(edac_dev, edac_dev->ctl_name);
	पूर्ण

	/* Check अगर Discard Timer समयd out */
	edac_pci_पढ़ो_dword(dev, REG_INT_CTLR, &val32);
	अगर (val32 & INT_CTLR_DTS) अणु
		prपूर्णांकk(KERN_INFO "Error(s) in interrupt and control register "
			"on %s bridge\n", dev_info->ctl_name);
		prपूर्णांकk(KERN_INFO "DTS: %d\n", val32 & INT_CTLR_DTS);

		val32 |= INT_CTLR_DTS;
		edac_pci_ग_लिखो_dword(dev, REG_INT_CTLR, val32);

		edac_pci_handle_npe(edac_dev, edac_dev->ctl_name);
	पूर्ण

	/* Check अगर CRC error happens on link side A */
	edac_pci_पढ़ो_dword(dev, REG_LNK_CTRL_A, &val32);
	अगर (val32 & LNK_CTRL_CRCERR_A) अणु
		prपूर्णांकk(KERN_INFO "Error(s) in link conf and control register "
			"on %s bridge\n", dev_info->ctl_name);
		prपूर्णांकk(KERN_INFO "CRCERR: %d\n", val32 & LNK_CTRL_CRCERR_A);

		val32 |= LNK_CTRL_CRCERR_A;
		edac_pci_ग_लिखो_dword(dev, REG_LNK_CTRL_A, val32);

		edac_pci_handle_npe(edac_dev, edac_dev->ctl_name);
	पूर्ण

	/* Check अगर CRC error happens on link side B */
	edac_pci_पढ़ो_dword(dev, REG_LNK_CTRL_B, &val32);
	अगर (val32 & LNK_CTRL_CRCERR_B) अणु
		prपूर्णांकk(KERN_INFO "Error(s) in link conf and control register "
			"on %s bridge\n", dev_info->ctl_name);
		prपूर्णांकk(KERN_INFO "CRCERR: %d\n", val32 & LNK_CTRL_CRCERR_B);

		val32 |= LNK_CTRL_CRCERR_B;
		edac_pci_ग_लिखो_dword(dev, REG_LNK_CTRL_B, val32);

		edac_pci_handle_npe(edac_dev, edac_dev->ctl_name);
	पूर्ण
पूर्ण

अटल काष्ठा amd8131_info amd8131_chipset = अणु
	.err_dev = PCI_DEVICE_ID_AMD_8131_APIC,
	.devices = amd8131_devices,
	.init = amd8131_pcix_init,
	.निकास = amd8131_pcix_निकास,
	.check = amd8131_pcix_check,
पूर्ण;

/*
 * There are 4 PCIX Bridges on ATCA-6101 that share the same PCI Device ID,
 * so amd8131_probe() would be called by kernel 4 बार, with dअगरferent
 * address of pci_dev क्रम each of them each समय.
 */
अटल पूर्णांक amd8131_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा amd8131_dev_info *dev_info;

	क्रम (dev_info = amd8131_chipset.devices; dev_info->inst != NO_BRIDGE;
		dev_info++)
		अगर (dev_info->devfn == dev->devfn)
			अवरोध;

	अगर (dev_info->inst == NO_BRIDGE) /* should never happen */
		वापस -ENODEV;

	/*
	 * We can't call pci_get_device() as we are used to करो because
	 * there are 4 of them but pci_dev_get() instead.
	 */
	dev_info->dev = pci_dev_get(dev);

	अगर (pci_enable_device(dev_info->dev)) अणु
		pci_dev_put(dev_info->dev);
		prपूर्णांकk(KERN_ERR "failed to enable:"
			"vendor %x, device %x, devfn %x, name %s\n",
			PCI_VENDOR_ID_AMD, amd8131_chipset.err_dev,
			dev_info->devfn, dev_info->ctl_name);
		वापस -ENODEV;
	पूर्ण

	/*
	 * we करो not allocate extra निजी काष्ठाure क्रम
	 * edac_pci_ctl_info, but make use of existing
	 * one instead.
	 */
	dev_info->edac_idx = edac_pci_alloc_index();
	dev_info->edac_dev = edac_pci_alloc_ctl_info(0, dev_info->ctl_name);
	अगर (!dev_info->edac_dev)
		वापस -ENOMEM;

	dev_info->edac_dev->pvt_info = dev_info;
	dev_info->edac_dev->dev = &dev_info->dev->dev;
	dev_info->edac_dev->mod_name = AMD8131_EDAC_MOD_STR;
	dev_info->edac_dev->ctl_name = dev_info->ctl_name;
	dev_info->edac_dev->dev_name = dev_name(&dev_info->dev->dev);

	अगर (edac_op_state == EDAC_OPSTATE_POLL)
		dev_info->edac_dev->edac_check = amd8131_chipset.check;

	अगर (amd8131_chipset.init)
		amd8131_chipset.init(dev_info);

	अगर (edac_pci_add_device(dev_info->edac_dev, dev_info->edac_idx) > 0) अणु
		prपूर्णांकk(KERN_ERR "failed edac_pci_add_device() for %s\n",
			dev_info->ctl_name);
		edac_pci_मुक्त_ctl_info(dev_info->edac_dev);
		वापस -ENODEV;
	पूर्ण

	prपूर्णांकk(KERN_INFO "added one device on AMD8131 "
		"vendor %x, device %x, devfn %x, name %s\n",
		PCI_VENDOR_ID_AMD, amd8131_chipset.err_dev,
		dev_info->devfn, dev_info->ctl_name);

	वापस 0;
पूर्ण

अटल व्योम amd8131_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा amd8131_dev_info *dev_info;

	क्रम (dev_info = amd8131_chipset.devices; dev_info->inst != NO_BRIDGE;
		dev_info++)
		अगर (dev_info->devfn == dev->devfn)
			अवरोध;

	अगर (dev_info->inst == NO_BRIDGE) /* should never happen */
		वापस;

	अगर (dev_info->edac_dev) अणु
		edac_pci_del_device(dev_info->edac_dev->dev);
		edac_pci_मुक्त_ctl_info(dev_info->edac_dev);
	पूर्ण

	अगर (amd8131_chipset.निकास)
		amd8131_chipset.निकास(dev_info);

	pci_dev_put(dev_info->dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id amd8131_edac_pci_tbl[] = अणु
	अणु
	PCI_VEND_DEV(AMD, 8131_BRIDGE),
	.subvenकरोr = PCI_ANY_ID,
	.subdevice = PCI_ANY_ID,
	.class = 0,
	.class_mask = 0,
	.driver_data = 0,
	पूर्ण,
	अणु
	0,
	पूर्ण			/* table is शून्य-terminated */
पूर्ण;
MODULE_DEVICE_TABLE(pci, amd8131_edac_pci_tbl);

अटल काष्ठा pci_driver amd8131_edac_driver = अणु
	.name = AMD8131_EDAC_MOD_STR,
	.probe = amd8131_probe,
	.हटाओ = amd8131_हटाओ,
	.id_table = amd8131_edac_pci_tbl,
पूर्ण;

अटल पूर्णांक __init amd8131_edac_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "AMD8131 EDAC driver " AMD8131_EDAC_REVISION "\n");
	prपूर्णांकk(KERN_INFO "\t(c) 2008 Wind River Systems, Inc.\n");

	/* Only POLL mode supported so far */
	edac_op_state = EDAC_OPSTATE_POLL;

	वापस pci_रेजिस्टर_driver(&amd8131_edac_driver);
पूर्ण

अटल व्योम __निकास amd8131_edac_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&amd8131_edac_driver);
पूर्ण

module_init(amd8131_edac_init);
module_निकास(amd8131_edac_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cao Qingtao <qingtao.cao@windriver.com>\n");
MODULE_DESCRIPTION("AMD8131 HyperTransport PCI-X Tunnel EDAC kernel module");
