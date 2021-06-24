<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * amd8111_edac.c, AMD8111 Hyper Transport chip EDAC kernel module
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
#समावेश <linux/bitops.h>
#समावेश <linux/edac.h>
#समावेश <linux/pci_ids.h>
#समावेश <यंत्र/पन.स>

#समावेश "edac_module.h"
#समावेश "amd8111_edac.h"

#घोषणा AMD8111_EDAC_REVISION	" Ver: 1.0.0"
#घोषणा AMD8111_EDAC_MOD_STR	"amd8111_edac"

#घोषणा PCI_DEVICE_ID_AMD_8111_PCI	0x7460

क्रमागत amd8111_edac_devs अणु
	LPC_BRIDGE = 0,
पूर्ण;

क्रमागत amd8111_edac_pcis अणु
	PCI_BRIDGE = 0,
पूर्ण;

/* Wrapper functions क्रम accessing PCI configuration space */
अटल पूर्णांक edac_pci_पढ़ो_dword(काष्ठा pci_dev *dev, पूर्णांक reg, u32 *val32)
अणु
	पूर्णांक ret;

	ret = pci_पढ़ो_config_dword(dev, reg, val32);
	अगर (ret != 0)
		prपूर्णांकk(KERN_ERR AMD8111_EDAC_MOD_STR
			" PCI Access Read Error at 0x%x\n", reg);

	वापस ret;
पूर्ण

अटल व्योम edac_pci_पढ़ो_byte(काष्ठा pci_dev *dev, पूर्णांक reg, u8 *val8)
अणु
	पूर्णांक ret;

	ret = pci_पढ़ो_config_byte(dev, reg, val8);
	अगर (ret != 0)
		prपूर्णांकk(KERN_ERR AMD8111_EDAC_MOD_STR
			" PCI Access Read Error at 0x%x\n", reg);
पूर्ण

अटल व्योम edac_pci_ग_लिखो_dword(काष्ठा pci_dev *dev, पूर्णांक reg, u32 val32)
अणु
	पूर्णांक ret;

	ret = pci_ग_लिखो_config_dword(dev, reg, val32);
	अगर (ret != 0)
		prपूर्णांकk(KERN_ERR AMD8111_EDAC_MOD_STR
			" PCI Access Write Error at 0x%x\n", reg);
पूर्ण

अटल व्योम edac_pci_ग_लिखो_byte(काष्ठा pci_dev *dev, पूर्णांक reg, u8 val8)
अणु
	पूर्णांक ret;

	ret = pci_ग_लिखो_config_byte(dev, reg, val8);
	अगर (ret != 0)
		prपूर्णांकk(KERN_ERR AMD8111_EDAC_MOD_STR
			" PCI Access Write Error at 0x%x\n", reg);
पूर्ण

/*
 * device-specअगरic methods क्रम amd8111 PCI Bridge Controller
 *
 * Error Reporting and Handling क्रम amd8111 chipset could be found
 * in its datasheet 3.1.2 section, P37
 */
अटल व्योम amd8111_pci_bridge_init(काष्ठा amd8111_pci_info *pci_info)
अणु
	u32 val32;
	काष्ठा pci_dev *dev = pci_info->dev;

	/* First clear error detection flags on the host पूर्णांकerface */

	/* Clear SSE/SMA/STA flags in the global status रेजिस्टर*/
	edac_pci_पढ़ो_dword(dev, REG_PCI_STSCMD, &val32);
	अगर (val32 & PCI_STSCMD_CLEAR_MASK)
		edac_pci_ग_लिखो_dword(dev, REG_PCI_STSCMD, val32);

	/* Clear CRC and Link Fail flags in HT Link Control reg */
	edac_pci_पढ़ो_dword(dev, REG_HT_LINK, &val32);
	अगर (val32 & HT_LINK_CLEAR_MASK)
		edac_pci_ग_लिखो_dword(dev, REG_HT_LINK, val32);

	/* Second clear all fault on the secondary पूर्णांकerface */

	/* Clear error flags in the memory-base limit reg. */
	edac_pci_पढ़ो_dword(dev, REG_MEM_LIM, &val32);
	अगर (val32 & MEM_LIMIT_CLEAR_MASK)
		edac_pci_ग_लिखो_dword(dev, REG_MEM_LIM, val32);

	/* Clear Discard Timer Expired flag in Interrupt/Bridge Control reg */
	edac_pci_पढ़ो_dword(dev, REG_PCI_INTBRG_CTRL, &val32);
	अगर (val32 & PCI_INTBRG_CTRL_CLEAR_MASK)
		edac_pci_ग_लिखो_dword(dev, REG_PCI_INTBRG_CTRL, val32);

	/* Last enable error detections */
	अगर (edac_op_state == EDAC_OPSTATE_POLL) अणु
		/* Enable System Error reporting in global status रेजिस्टर */
		edac_pci_पढ़ो_dword(dev, REG_PCI_STSCMD, &val32);
		val32 |= PCI_STSCMD_SERREN;
		edac_pci_ग_लिखो_dword(dev, REG_PCI_STSCMD, val32);

		/* Enable CRC Sync flood packets to HyperTransport Link */
		edac_pci_पढ़ो_dword(dev, REG_HT_LINK, &val32);
		val32 |= HT_LINK_CRCFEN;
		edac_pci_ग_लिखो_dword(dev, REG_HT_LINK, val32);

		/* Enable SSE reporting etc in Interrupt control reg */
		edac_pci_पढ़ो_dword(dev, REG_PCI_INTBRG_CTRL, &val32);
		val32 |= PCI_INTBRG_CTRL_POLL_MASK;
		edac_pci_ग_लिखो_dword(dev, REG_PCI_INTBRG_CTRL, val32);
	पूर्ण
पूर्ण

अटल व्योम amd8111_pci_bridge_निकास(काष्ठा amd8111_pci_info *pci_info)
अणु
	u32 val32;
	काष्ठा pci_dev *dev = pci_info->dev;

	अगर (edac_op_state == EDAC_OPSTATE_POLL) अणु
		/* Disable System Error reporting */
		edac_pci_पढ़ो_dword(dev, REG_PCI_STSCMD, &val32);
		val32 &= ~PCI_STSCMD_SERREN;
		edac_pci_ग_लिखो_dword(dev, REG_PCI_STSCMD, val32);

		/* Disable CRC flood packets */
		edac_pci_पढ़ो_dword(dev, REG_HT_LINK, &val32);
		val32 &= ~HT_LINK_CRCFEN;
		edac_pci_ग_लिखो_dword(dev, REG_HT_LINK, val32);

		/* Disable DTSERREN/MARSP/SERREN in Interrupt Control reg */
		edac_pci_पढ़ो_dword(dev, REG_PCI_INTBRG_CTRL, &val32);
		val32 &= ~PCI_INTBRG_CTRL_POLL_MASK;
		edac_pci_ग_लिखो_dword(dev, REG_PCI_INTBRG_CTRL, val32);
	पूर्ण
पूर्ण

अटल व्योम amd8111_pci_bridge_check(काष्ठा edac_pci_ctl_info *edac_dev)
अणु
	काष्ठा amd8111_pci_info *pci_info = edac_dev->pvt_info;
	काष्ठा pci_dev *dev = pci_info->dev;
	u32 val32;

	/* Check out PCI Bridge Status and Command Register */
	edac_pci_पढ़ो_dword(dev, REG_PCI_STSCMD, &val32);
	अगर (val32 & PCI_STSCMD_CLEAR_MASK) अणु
		prपूर्णांकk(KERN_INFO "Error(s) in PCI bridge status and command"
			"register on device %s\n", pci_info->ctl_name);
		prपूर्णांकk(KERN_INFO "SSE: %d, RMA: %d, RTA: %d\n",
			(val32 & PCI_STSCMD_SSE) != 0,
			(val32 & PCI_STSCMD_RMA) != 0,
			(val32 & PCI_STSCMD_RTA) != 0);

		val32 |= PCI_STSCMD_CLEAR_MASK;
		edac_pci_ग_लिखो_dword(dev, REG_PCI_STSCMD, val32);

		edac_pci_handle_npe(edac_dev, edac_dev->ctl_name);
	पूर्ण

	/* Check out HyperTransport Link Control Register */
	edac_pci_पढ़ो_dword(dev, REG_HT_LINK, &val32);
	अगर (val32 & HT_LINK_LKFAIL) अणु
		prपूर्णांकk(KERN_INFO "Error(s) in hypertransport link control"
			"register on device %s\n", pci_info->ctl_name);
		prपूर्णांकk(KERN_INFO "LKFAIL: %d\n",
			(val32 & HT_LINK_LKFAIL) != 0);

		val32 |= HT_LINK_LKFAIL;
		edac_pci_ग_लिखो_dword(dev, REG_HT_LINK, val32);

		edac_pci_handle_npe(edac_dev, edac_dev->ctl_name);
	पूर्ण

	/* Check out PCI Interrupt and Bridge Control Register */
	edac_pci_पढ़ो_dword(dev, REG_PCI_INTBRG_CTRL, &val32);
	अगर (val32 & PCI_INTBRG_CTRL_DTSTAT) अणु
		prपूर्णांकk(KERN_INFO "Error(s) in PCI interrupt and bridge control"
			"register on device %s\n", pci_info->ctl_name);
		prपूर्णांकk(KERN_INFO "DTSTAT: %d\n",
			(val32 & PCI_INTBRG_CTRL_DTSTAT) != 0);

		val32 |= PCI_INTBRG_CTRL_DTSTAT;
		edac_pci_ग_लिखो_dword(dev, REG_PCI_INTBRG_CTRL, val32);

		edac_pci_handle_npe(edac_dev, edac_dev->ctl_name);
	पूर्ण

	/* Check out PCI Bridge Memory Base-Limit Register */
	edac_pci_पढ़ो_dword(dev, REG_MEM_LIM, &val32);
	अगर (val32 & MEM_LIMIT_CLEAR_MASK) अणु
		prपूर्णांकk(KERN_INFO
			"Error(s) in mem limit register on %s device\n",
			pci_info->ctl_name);
		prपूर्णांकk(KERN_INFO "DPE: %d, RSE: %d, RMA: %d\n"
			"RTA: %d, STA: %d, MDPE: %d\n",
			(val32 & MEM_LIMIT_DPE)  != 0,
			(val32 & MEM_LIMIT_RSE)  != 0,
			(val32 & MEM_LIMIT_RMA)  != 0,
			(val32 & MEM_LIMIT_RTA)  != 0,
			(val32 & MEM_LIMIT_STA)  != 0,
			(val32 & MEM_LIMIT_MDPE) != 0);

		val32 |= MEM_LIMIT_CLEAR_MASK;
		edac_pci_ग_लिखो_dword(dev, REG_MEM_LIM, val32);

		edac_pci_handle_npe(edac_dev, edac_dev->ctl_name);
	पूर्ण
पूर्ण

अटल काष्ठा resource *legacy_io_res;
अटल पूर्णांक at_compat_reg_broken;
#घोषणा LEGACY_NR_PORTS	1

/* device-specअगरic methods क्रम amd8111 LPC Bridge device */
अटल व्योम amd8111_lpc_bridge_init(काष्ठा amd8111_dev_info *dev_info)
अणु
	u8 val8;
	काष्ठा pci_dev *dev = dev_info->dev;

	/* First clear REG_AT_COMPAT[SERR, IOCHK] अगर necessary */
	legacy_io_res = request_region(REG_AT_COMPAT, LEGACY_NR_PORTS,
					AMD8111_EDAC_MOD_STR);
	अगर (!legacy_io_res)
		prपूर्णांकk(KERN_INFO "%s: failed to request legacy I/O region "
			"start %d, len %d\n", __func__,
			REG_AT_COMPAT, LEGACY_NR_PORTS);
	अन्यथा अणु
		val8 = __करो_inb(REG_AT_COMPAT);
		अगर (val8 == 0xff) अणु /* buggy port */
			prपूर्णांकk(KERN_INFO "%s: port %d is buggy, not supported"
				" by hardware?\n", __func__, REG_AT_COMPAT);
			at_compat_reg_broken = 1;
			release_region(REG_AT_COMPAT, LEGACY_NR_PORTS);
			legacy_io_res = शून्य;
		पूर्ण अन्यथा अणु
			u8 out8 = 0;
			अगर (val8 & AT_COMPAT_SERR)
				out8 = AT_COMPAT_CLRSERR;
			अगर (val8 & AT_COMPAT_IOCHK)
				out8 |= AT_COMPAT_CLRIOCHK;
			अगर (out8 > 0)
				__करो_outb(out8, REG_AT_COMPAT);
		पूर्ण
	पूर्ण

	/* Second clear error flags on LPC bridge */
	edac_pci_पढ़ो_byte(dev, REG_IO_CTRL_1, &val8);
	अगर (val8 & IO_CTRL_1_CLEAR_MASK)
		edac_pci_ग_लिखो_byte(dev, REG_IO_CTRL_1, val8);
पूर्ण

अटल व्योम amd8111_lpc_bridge_निकास(काष्ठा amd8111_dev_info *dev_info)
अणु
	अगर (legacy_io_res)
		release_region(REG_AT_COMPAT, LEGACY_NR_PORTS);
पूर्ण

अटल व्योम amd8111_lpc_bridge_check(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा amd8111_dev_info *dev_info = edac_dev->pvt_info;
	काष्ठा pci_dev *dev = dev_info->dev;
	u8 val8;

	edac_pci_पढ़ो_byte(dev, REG_IO_CTRL_1, &val8);
	अगर (val8 & IO_CTRL_1_CLEAR_MASK) अणु
		prपूर्णांकk(KERN_INFO
			"Error(s) in IO control register on %s device\n",
			dev_info->ctl_name);
		prपूर्णांकk(KERN_INFO "LPC ERR: %d, PW2LPC: %d\n",
			(val8 & IO_CTRL_1_LPC_ERR) != 0,
			(val8 & IO_CTRL_1_PW2LPC) != 0);

		val8 |= IO_CTRL_1_CLEAR_MASK;
		edac_pci_ग_लिखो_byte(dev, REG_IO_CTRL_1, val8);

		edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
	पूर्ण

	अगर (at_compat_reg_broken == 0) अणु
		u8 out8 = 0;
		val8 = __करो_inb(REG_AT_COMPAT);
		अगर (val8 & AT_COMPAT_SERR)
			out8 = AT_COMPAT_CLRSERR;
		अगर (val8 & AT_COMPAT_IOCHK)
			out8 |= AT_COMPAT_CLRIOCHK;
		अगर (out8 > 0) अणु
			__करो_outb(out8, REG_AT_COMPAT);
			edac_device_handle_ue(edac_dev, 0, 0,
						edac_dev->ctl_name);
		पूर्ण
	पूर्ण
पूर्ण

/* General devices represented by edac_device_ctl_info */
अटल काष्ठा amd8111_dev_info amd8111_devices[] = अणु
	[LPC_BRIDGE] = अणु
		.err_dev = PCI_DEVICE_ID_AMD_8111_LPC,
		.ctl_name = "lpc",
		.init = amd8111_lpc_bridge_init,
		.निकास = amd8111_lpc_bridge_निकास,
		.check = amd8111_lpc_bridge_check,
	पूर्ण,
	अणु0पूर्ण,
पूर्ण;

/* PCI controllers represented by edac_pci_ctl_info */
अटल काष्ठा amd8111_pci_info amd8111_pcis[] = अणु
	[PCI_BRIDGE] = अणु
		.err_dev = PCI_DEVICE_ID_AMD_8111_PCI,
		.ctl_name = "AMD8111_PCI_Controller",
		.init = amd8111_pci_bridge_init,
		.निकास = amd8111_pci_bridge_निकास,
		.check = amd8111_pci_bridge_check,
	पूर्ण,
	अणु0पूर्ण,
पूर्ण;

अटल पूर्णांक amd8111_dev_probe(काष्ठा pci_dev *dev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा amd8111_dev_info *dev_info = &amd8111_devices[id->driver_data];
	पूर्णांक ret = -ENODEV;

	dev_info->dev = pci_get_device(PCI_VENDOR_ID_AMD,
					dev_info->err_dev, शून्य);

	अगर (!dev_info->dev) अणु
		prपूर्णांकk(KERN_ERR "EDAC device not found:"
			"vendor %x, device %x, name %s\n",
			PCI_VENDOR_ID_AMD, dev_info->err_dev,
			dev_info->ctl_name);
		जाओ err;
	पूर्ण

	अगर (pci_enable_device(dev_info->dev)) अणु
		prपूर्णांकk(KERN_ERR "failed to enable:"
			"vendor %x, device %x, name %s\n",
			PCI_VENDOR_ID_AMD, dev_info->err_dev,
			dev_info->ctl_name);
		जाओ err_dev_put;
	पूर्ण

	/*
	 * we करो not allocate extra निजी काष्ठाure क्रम
	 * edac_device_ctl_info, but make use of existing
	 * one instead.
	*/
	dev_info->edac_idx = edac_device_alloc_index();
	dev_info->edac_dev =
		edac_device_alloc_ctl_info(0, dev_info->ctl_name, 1,
					   शून्य, 0, 0,
					   शून्य, 0, dev_info->edac_idx);
	अगर (!dev_info->edac_dev) अणु
		ret = -ENOMEM;
		जाओ err_dev_put;
	पूर्ण

	dev_info->edac_dev->pvt_info = dev_info;
	dev_info->edac_dev->dev = &dev_info->dev->dev;
	dev_info->edac_dev->mod_name = AMD8111_EDAC_MOD_STR;
	dev_info->edac_dev->ctl_name = dev_info->ctl_name;
	dev_info->edac_dev->dev_name = dev_name(&dev_info->dev->dev);

	अगर (edac_op_state == EDAC_OPSTATE_POLL)
		dev_info->edac_dev->edac_check = dev_info->check;

	अगर (dev_info->init)
		dev_info->init(dev_info);

	अगर (edac_device_add_device(dev_info->edac_dev) > 0) अणु
		prपूर्णांकk(KERN_ERR "failed to add edac_dev for %s\n",
			dev_info->ctl_name);
		जाओ err_edac_मुक्त_ctl;
	पूर्ण

	prपूर्णांकk(KERN_INFO "added one edac_dev on AMD8111 "
		"vendor %x, device %x, name %s\n",
		PCI_VENDOR_ID_AMD, dev_info->err_dev,
		dev_info->ctl_name);

	वापस 0;

err_edac_मुक्त_ctl:
	edac_device_मुक्त_ctl_info(dev_info->edac_dev);
err_dev_put:
	pci_dev_put(dev_info->dev);
err:
	वापस ret;
पूर्ण

अटल व्योम amd8111_dev_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा amd8111_dev_info *dev_info;

	क्रम (dev_info = amd8111_devices; dev_info->err_dev; dev_info++)
		अगर (dev_info->dev->device == dev->device)
			अवरोध;

	अगर (!dev_info->err_dev)	/* should never happen */
		वापस;

	अगर (dev_info->edac_dev) अणु
		edac_device_del_device(dev_info->edac_dev->dev);
		edac_device_मुक्त_ctl_info(dev_info->edac_dev);
	पूर्ण

	अगर (dev_info->निकास)
		dev_info->निकास(dev_info);

	pci_dev_put(dev_info->dev);
पूर्ण

अटल पूर्णांक amd8111_pci_probe(काष्ठा pci_dev *dev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा amd8111_pci_info *pci_info = &amd8111_pcis[id->driver_data];
	पूर्णांक ret = -ENODEV;

	pci_info->dev = pci_get_device(PCI_VENDOR_ID_AMD,
					pci_info->err_dev, शून्य);

	अगर (!pci_info->dev) अणु
		prपूर्णांकk(KERN_ERR "EDAC device not found:"
			"vendor %x, device %x, name %s\n",
			PCI_VENDOR_ID_AMD, pci_info->err_dev,
			pci_info->ctl_name);
		जाओ err;
	पूर्ण

	अगर (pci_enable_device(pci_info->dev)) अणु
		prपूर्णांकk(KERN_ERR "failed to enable:"
			"vendor %x, device %x, name %s\n",
			PCI_VENDOR_ID_AMD, pci_info->err_dev,
			pci_info->ctl_name);
		जाओ err_dev_put;
	पूर्ण

	/*
	 * we करो not allocate extra निजी काष्ठाure क्रम
	 * edac_pci_ctl_info, but make use of existing
	 * one instead.
	*/
	pci_info->edac_idx = edac_pci_alloc_index();
	pci_info->edac_dev = edac_pci_alloc_ctl_info(0, pci_info->ctl_name);
	अगर (!pci_info->edac_dev) अणु
		ret = -ENOMEM;
		जाओ err_dev_put;
	पूर्ण

	pci_info->edac_dev->pvt_info = pci_info;
	pci_info->edac_dev->dev = &pci_info->dev->dev;
	pci_info->edac_dev->mod_name = AMD8111_EDAC_MOD_STR;
	pci_info->edac_dev->ctl_name = pci_info->ctl_name;
	pci_info->edac_dev->dev_name = dev_name(&pci_info->dev->dev);

	अगर (edac_op_state == EDAC_OPSTATE_POLL)
		pci_info->edac_dev->edac_check = pci_info->check;

	अगर (pci_info->init)
		pci_info->init(pci_info);

	अगर (edac_pci_add_device(pci_info->edac_dev, pci_info->edac_idx) > 0) अणु
		prपूर्णांकk(KERN_ERR "failed to add edac_pci for %s\n",
			pci_info->ctl_name);
		जाओ err_edac_मुक्त_ctl;
	पूर्ण

	prपूर्णांकk(KERN_INFO "added one edac_pci on AMD8111 "
		"vendor %x, device %x, name %s\n",
		PCI_VENDOR_ID_AMD, pci_info->err_dev,
		pci_info->ctl_name);

	वापस 0;

err_edac_मुक्त_ctl:
	edac_pci_मुक्त_ctl_info(pci_info->edac_dev);
err_dev_put:
	pci_dev_put(pci_info->dev);
err:
	वापस ret;
पूर्ण

अटल व्योम amd8111_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा amd8111_pci_info *pci_info;

	क्रम (pci_info = amd8111_pcis; pci_info->err_dev; pci_info++)
		अगर (pci_info->dev->device == dev->device)
			अवरोध;

	अगर (!pci_info->err_dev)	/* should never happen */
		वापस;

	अगर (pci_info->edac_dev) अणु
		edac_pci_del_device(pci_info->edac_dev->dev);
		edac_pci_मुक्त_ctl_info(pci_info->edac_dev);
	पूर्ण

	अगर (pci_info->निकास)
		pci_info->निकास(pci_info);

	pci_dev_put(pci_info->dev);
पूर्ण

/* PCI Device ID talbe क्रम general EDAC device */
अटल स्थिर काष्ठा pci_device_id amd8111_edac_dev_tbl[] = अणु
	अणु
	PCI_VEND_DEV(AMD, 8111_LPC),
	.subvenकरोr = PCI_ANY_ID,
	.subdevice = PCI_ANY_ID,
	.class = 0,
	.class_mask = 0,
	.driver_data = LPC_BRIDGE,
	पूर्ण,
	अणु
	0,
	पूर्ण			/* table is शून्य-terminated */
पूर्ण;
MODULE_DEVICE_TABLE(pci, amd8111_edac_dev_tbl);

अटल काष्ठा pci_driver amd8111_edac_dev_driver = अणु
	.name = "AMD8111_EDAC_DEV",
	.probe = amd8111_dev_probe,
	.हटाओ = amd8111_dev_हटाओ,
	.id_table = amd8111_edac_dev_tbl,
पूर्ण;

/* PCI Device ID table क्रम EDAC PCI controller */
अटल स्थिर काष्ठा pci_device_id amd8111_edac_pci_tbl[] = अणु
	अणु
	PCI_VEND_DEV(AMD, 8111_PCI),
	.subvenकरोr = PCI_ANY_ID,
	.subdevice = PCI_ANY_ID,
	.class = 0,
	.class_mask = 0,
	.driver_data = PCI_BRIDGE,
	पूर्ण,
	अणु
	0,
	पूर्ण			/* table is शून्य-terminated */
पूर्ण;
MODULE_DEVICE_TABLE(pci, amd8111_edac_pci_tbl);

अटल काष्ठा pci_driver amd8111_edac_pci_driver = अणु
	.name = "AMD8111_EDAC_PCI",
	.probe = amd8111_pci_probe,
	.हटाओ = amd8111_pci_हटाओ,
	.id_table = amd8111_edac_pci_tbl,
पूर्ण;

अटल पूर्णांक __init amd8111_edac_init(व्योम)
अणु
	पूर्णांक val;

	prपूर्णांकk(KERN_INFO "AMD8111 EDAC driver "	AMD8111_EDAC_REVISION "\n");
	prपूर्णांकk(KERN_INFO "\t(c) 2008 Wind River Systems, Inc.\n");

	/* Only POLL mode supported so far */
	edac_op_state = EDAC_OPSTATE_POLL;

	val = pci_रेजिस्टर_driver(&amd8111_edac_dev_driver);
	val |= pci_रेजिस्टर_driver(&amd8111_edac_pci_driver);

	वापस val;
पूर्ण

अटल व्योम __निकास amd8111_edac_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&amd8111_edac_pci_driver);
	pci_unरेजिस्टर_driver(&amd8111_edac_dev_driver);
पूर्ण


module_init(amd8111_edac_init);
module_निकास(amd8111_edac_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cao Qingtao <qingtao.cao@windriver.com>\n");
MODULE_DESCRIPTION("AMD8111 HyperTransport I/O Hub EDAC kernel module");
