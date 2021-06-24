<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO PCI Intel Graphics support
 *
 * Copyright (C) 2016 Red Hat, Inc.  All rights reserved.
 *	Author: Alex Williamson <alex.williamson@redhat.com>
 *
 * Register a device specअगरic region through which to provide पढ़ो-only
 * access to the Intel IGD opregion.  The रेजिस्टर defining the opregion
 * address is also भवized to prevent user modअगरication.
 */

#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vfपन.स>

#समावेश "vfio_pci_private.h"

#घोषणा OPREGION_SIGNATURE	"IntelGraphicsMem"
#घोषणा OPREGION_SIZE		(8 * 1024)
#घोषणा OPREGION_PCI_ADDR	0xfc

#घोषणा OPREGION_RVDA		0x3ba
#घोषणा OPREGION_RVDS		0x3c2
#घोषणा OPREGION_VERSION	0x16

अटल माप_प्रकार vfio_pci_igd_rw(काष्ठा vfio_pci_device *vdev, अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos, bool isग_लिखो)
अणु
	अचिन्हित पूर्णांक i = VFIO_PCI_OFFSET_TO_INDEX(*ppos) - VFIO_PCI_NUM_REGIONS;
	व्योम *base = vdev->region[i].data;
	loff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;

	अगर (pos >= vdev->region[i].size || isग_लिखो)
		वापस -EINVAL;

	count = min(count, (माप_प्रकार)(vdev->region[i].size - pos));

	अगर (copy_to_user(buf, base + pos, count))
		वापस -EFAULT;

	*ppos += count;

	वापस count;
पूर्ण

अटल व्योम vfio_pci_igd_release(काष्ठा vfio_pci_device *vdev,
				 काष्ठा vfio_pci_region *region)
अणु
	memunmap(region->data);
पूर्ण

अटल स्थिर काष्ठा vfio_pci_regops vfio_pci_igd_regops = अणु
	.rw		= vfio_pci_igd_rw,
	.release	= vfio_pci_igd_release,
पूर्ण;

अटल पूर्णांक vfio_pci_igd_opregion_init(काष्ठा vfio_pci_device *vdev)
अणु
	__le32 *dwordp = (__le32 *)(vdev->vconfig + OPREGION_PCI_ADDR);
	u32 addr, size;
	व्योम *base;
	पूर्णांक ret;
	u16 version;

	ret = pci_पढ़ो_config_dword(vdev->pdev, OPREGION_PCI_ADDR, &addr);
	अगर (ret)
		वापस ret;

	अगर (!addr || !(~addr))
		वापस -ENODEV;

	base = memremap(addr, OPREGION_SIZE, MEMREMAP_WB);
	अगर (!base)
		वापस -ENOMEM;

	अगर (स_भेद(base, OPREGION_SIGNATURE, 16)) अणु
		memunmap(base);
		वापस -EINVAL;
	पूर्ण

	size = le32_to_cpu(*(__le32 *)(base + 16));
	अगर (!size) अणु
		memunmap(base);
		वापस -EINVAL;
	पूर्ण

	size *= 1024; /* In KB */

	/*
	 * Support opregion v2.1+
	 * When VBT data exceeds 6KB size and cannot be within mailbox #4, then
	 * the Extended VBT region next to opregion is used to hold the VBT data.
	 * RVDA (Relative Address of VBT Data from Opregion Base) and RVDS
	 * (Raw VBT Data Size) from opregion काष्ठाure member are used to hold the
	 * address from region base and size of VBT data. RVDA/RVDS are not
	 * defined beक्रमe opregion 2.0.
	 *
	 * opregion 2.1+: RVDA is अचिन्हित, relative offset from
	 * opregion base, and should poपूर्णांक to the end of opregion.
	 * otherwise, exposing to userspace to allow पढ़ो access to everything between
	 * the OpRegion and VBT is not safe.
	 * RVDS is defined as size in bytes.
	 *
	 * opregion 2.0: rvda is the physical VBT address.
	 * Since rvda is HPA it cannot be directly used in guest.
	 * And it should not be practically available क्रम end user,so it is not supported.
	 */
	version = le16_to_cpu(*(__le16 *)(base + OPREGION_VERSION));
	अगर (version >= 0x0200) अणु
		u64 rvda;
		u32 rvds;

		rvda = le64_to_cpu(*(__le64 *)(base + OPREGION_RVDA));
		rvds = le32_to_cpu(*(__le32 *)(base + OPREGION_RVDS));
		अगर (rvda && rvds) अणु
			/* no support क्रम opregion v2.0 with physical VBT address */
			अगर (version == 0x0200) अणु
				memunmap(base);
				pci_err(vdev->pdev,
					"IGD assignment does not support opregion v2.0 with an extended VBT region\n");
				वापस -EINVAL;
			पूर्ण

			अगर (rvda != size) अणु
				memunmap(base);
				pci_err(vdev->pdev,
					"Extended VBT does not follow opregion on version 0x%04x\n",
					version);
				वापस -EINVAL;
			पूर्ण

			/* region size क्रम opregion v2.0+: opregion and VBT size. */
			size += rvds;
		पूर्ण
	पूर्ण

	अगर (size != OPREGION_SIZE) अणु
		memunmap(base);
		base = memremap(addr, size, MEMREMAP_WB);
		अगर (!base)
			वापस -ENOMEM;
	पूर्ण

	ret = vfio_pci_रेजिस्टर_dev_region(vdev,
		PCI_VENDOR_ID_INTEL | VFIO_REGION_TYPE_PCI_VENDOR_TYPE,
		VFIO_REGION_SUBTYPE_INTEL_IGD_OPREGION,
		&vfio_pci_igd_regops, size, VFIO_REGION_INFO_FLAG_READ, base);
	अगर (ret) अणु
		memunmap(base);
		वापस ret;
	पूर्ण

	/* Fill vconfig with the hw value and भवize रेजिस्टर */
	*dwordp = cpu_to_le32(addr);
	स_रखो(vdev->pci_config_map + OPREGION_PCI_ADDR,
	       PCI_CAP_ID_INVALID_VIRT, 4);

	वापस ret;
पूर्ण

अटल माप_प्रकार vfio_pci_igd_cfg_rw(काष्ठा vfio_pci_device *vdev,
				  अक्षर __user *buf, माप_प्रकार count, loff_t *ppos,
				  bool isग_लिखो)
अणु
	अचिन्हित पूर्णांक i = VFIO_PCI_OFFSET_TO_INDEX(*ppos) - VFIO_PCI_NUM_REGIONS;
	काष्ठा pci_dev *pdev = vdev->region[i].data;
	loff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;
	माप_प्रकार size;
	पूर्णांक ret;

	अगर (pos >= vdev->region[i].size || isग_लिखो)
		वापस -EINVAL;

	size = count = min(count, (माप_प्रकार)(vdev->region[i].size - pos));

	अगर ((pos & 1) && size) अणु
		u8 val;

		ret = pci_user_पढ़ो_config_byte(pdev, pos, &val);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user(buf + count - size, &val, 1))
			वापस -EFAULT;

		pos++;
		size--;
	पूर्ण

	अगर ((pos & 3) && size > 2) अणु
		u16 val;

		ret = pci_user_पढ़ो_config_word(pdev, pos, &val);
		अगर (ret)
			वापस ret;

		val = cpu_to_le16(val);
		अगर (copy_to_user(buf + count - size, &val, 2))
			वापस -EFAULT;

		pos += 2;
		size -= 2;
	पूर्ण

	जबतक (size > 3) अणु
		u32 val;

		ret = pci_user_पढ़ो_config_dword(pdev, pos, &val);
		अगर (ret)
			वापस ret;

		val = cpu_to_le32(val);
		अगर (copy_to_user(buf + count - size, &val, 4))
			वापस -EFAULT;

		pos += 4;
		size -= 4;
	पूर्ण

	जबतक (size >= 2) अणु
		u16 val;

		ret = pci_user_पढ़ो_config_word(pdev, pos, &val);
		अगर (ret)
			वापस ret;

		val = cpu_to_le16(val);
		अगर (copy_to_user(buf + count - size, &val, 2))
			वापस -EFAULT;

		pos += 2;
		size -= 2;
	पूर्ण

	जबतक (size) अणु
		u8 val;

		ret = pci_user_पढ़ो_config_byte(pdev, pos, &val);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user(buf + count - size, &val, 1))
			वापस -EFAULT;

		pos++;
		size--;
	पूर्ण

	*ppos += count;

	वापस count;
पूर्ण

अटल व्योम vfio_pci_igd_cfg_release(काष्ठा vfio_pci_device *vdev,
				     काष्ठा vfio_pci_region *region)
अणु
	काष्ठा pci_dev *pdev = region->data;

	pci_dev_put(pdev);
पूर्ण

अटल स्थिर काष्ठा vfio_pci_regops vfio_pci_igd_cfg_regops = अणु
	.rw		= vfio_pci_igd_cfg_rw,
	.release	= vfio_pci_igd_cfg_release,
पूर्ण;

अटल पूर्णांक vfio_pci_igd_cfg_init(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *host_bridge, *lpc_bridge;
	पूर्णांक ret;

	host_bridge = pci_get_करोमुख्य_bus_and_slot(0, 0, PCI_DEVFN(0, 0));
	अगर (!host_bridge)
		वापस -ENODEV;

	अगर (host_bridge->venकरोr != PCI_VENDOR_ID_INTEL ||
	    host_bridge->class != (PCI_CLASS_BRIDGE_HOST << 8)) अणु
		pci_dev_put(host_bridge);
		वापस -EINVAL;
	पूर्ण

	ret = vfio_pci_रेजिस्टर_dev_region(vdev,
		PCI_VENDOR_ID_INTEL | VFIO_REGION_TYPE_PCI_VENDOR_TYPE,
		VFIO_REGION_SUBTYPE_INTEL_IGD_HOST_CFG,
		&vfio_pci_igd_cfg_regops, host_bridge->cfg_size,
		VFIO_REGION_INFO_FLAG_READ, host_bridge);
	अगर (ret) अणु
		pci_dev_put(host_bridge);
		वापस ret;
	पूर्ण

	lpc_bridge = pci_get_करोमुख्य_bus_and_slot(0, 0, PCI_DEVFN(0x1f, 0));
	अगर (!lpc_bridge)
		वापस -ENODEV;

	अगर (lpc_bridge->venकरोr != PCI_VENDOR_ID_INTEL ||
	    lpc_bridge->class != (PCI_CLASS_BRIDGE_ISA << 8)) अणु
		pci_dev_put(lpc_bridge);
		वापस -EINVAL;
	पूर्ण

	ret = vfio_pci_रेजिस्टर_dev_region(vdev,
		PCI_VENDOR_ID_INTEL | VFIO_REGION_TYPE_PCI_VENDOR_TYPE,
		VFIO_REGION_SUBTYPE_INTEL_IGD_LPC_CFG,
		&vfio_pci_igd_cfg_regops, lpc_bridge->cfg_size,
		VFIO_REGION_INFO_FLAG_READ, lpc_bridge);
	अगर (ret) अणु
		pci_dev_put(lpc_bridge);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vfio_pci_igd_init(काष्ठा vfio_pci_device *vdev)
अणु
	पूर्णांक ret;

	ret = vfio_pci_igd_opregion_init(vdev);
	अगर (ret)
		वापस ret;

	ret = vfio_pci_igd_cfg_init(vdev);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
