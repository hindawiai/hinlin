<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO PCI config space भवization
 *
 * Copyright (C) 2012 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 *
 * Derived from original vfio:
 * Copyright 2010 Cisco Systems, Inc.  All rights reserved.
 * Author: Tom Lyon, pugs@cisco.com
 */

/*
 * This code handles पढ़ोing and writing of PCI configuration रेजिस्टरs.
 * This is hairy because we want to allow a lot of flexibility to the
 * user driver, but cannot trust it with all of the config fields.
 * Tables determine which fields can be पढ़ो and written, as well as
 * which fields are 'virtualized' - special actions and translations to
 * make it appear to the user that he has control, when in fact things
 * must be negotiated with the underlying OS.
 */

#समावेश <linux/fs.h>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/slab.h>

#समावेश "vfio_pci_private.h"

/* Fake capability ID क्रम standard config space */
#घोषणा PCI_CAP_ID_BASIC	0

#घोषणा is_bar(offset)	\
	((offset >= PCI_BASE_ADDRESS_0 && offset < PCI_BASE_ADDRESS_5 + 4) || \
	 (offset >= PCI_ROM_ADDRESS && offset < PCI_ROM_ADDRESS + 4))

/*
 * Lengths of PCI Config Capabilities
 *   0: Removed from the user visible capability list
 *   FF: Variable length
 */
अटल स्थिर u8 pci_cap_length[PCI_CAP_ID_MAX + 1] = अणु
	[PCI_CAP_ID_BASIC]	= PCI_STD_HEADER_SIZखातापूर्ण, /* pci config header */
	[PCI_CAP_ID_PM]		= PCI_PM_SIZखातापूर्ण,
	[PCI_CAP_ID_AGP]	= PCI_AGP_SIZखातापूर्ण,
	[PCI_CAP_ID_VPD]	= PCI_CAP_VPD_SIZखातापूर्ण,
	[PCI_CAP_ID_SLOTID]	= 0,		/* bridge - करोn't care */
	[PCI_CAP_ID_MSI]	= 0xFF,		/* 10, 14, 20, or 24 */
	[PCI_CAP_ID_CHSWP]	= 0,		/* cpci - not yet */
	[PCI_CAP_ID_PCIX]	= 0xFF,		/* 8 or 24 */
	[PCI_CAP_ID_HT]		= 0xFF,		/* hypertransport */
	[PCI_CAP_ID_VNDR]	= 0xFF,		/* variable */
	[PCI_CAP_ID_DBG]	= 0,		/* debug - करोn't care */
	[PCI_CAP_ID_CCRC]	= 0,		/* cpci - not yet */
	[PCI_CAP_ID_SHPC]	= 0,		/* hotswap - not yet */
	[PCI_CAP_ID_SSVID]	= 0,		/* bridge - करोn't care */
	[PCI_CAP_ID_AGP3]	= 0,		/* AGP8x - not yet */
	[PCI_CAP_ID_SECDEV]	= 0,		/* secure device not yet */
	[PCI_CAP_ID_EXP]	= 0xFF,		/* 20 or 44 */
	[PCI_CAP_ID_MSIX]	= PCI_CAP_MSIX_SIZखातापूर्ण,
	[PCI_CAP_ID_SATA]	= 0xFF,
	[PCI_CAP_ID_AF]		= PCI_CAP_AF_SIZखातापूर्ण,
पूर्ण;

/*
 * Lengths of PCIe/PCI-X Extended Config Capabilities
 *   0: Removed or masked from the user visible capability list
 *   FF: Variable length
 */
अटल स्थिर u16 pci_ext_cap_length[PCI_EXT_CAP_ID_MAX + 1] = अणु
	[PCI_EXT_CAP_ID_ERR]	=	PCI_ERR_ROOT_COMMAND,
	[PCI_EXT_CAP_ID_VC]	=	0xFF,
	[PCI_EXT_CAP_ID_DSN]	=	PCI_EXT_CAP_DSN_SIZखातापूर्ण,
	[PCI_EXT_CAP_ID_PWR]	=	PCI_EXT_CAP_PWR_SIZखातापूर्ण,
	[PCI_EXT_CAP_ID_RCLD]	=	0,	/* root only - करोn't care */
	[PCI_EXT_CAP_ID_RCILC]	=	0,	/* root only - करोn't care */
	[PCI_EXT_CAP_ID_RCEC]	=	0,	/* root only - करोn't care */
	[PCI_EXT_CAP_ID_MFVC]	=	0xFF,
	[PCI_EXT_CAP_ID_VC9]	=	0xFF,	/* same as CAP_ID_VC */
	[PCI_EXT_CAP_ID_RCRB]	=	0,	/* root only - करोn't care */
	[PCI_EXT_CAP_ID_VNDR]	=	0xFF,
	[PCI_EXT_CAP_ID_CAC]	=	0,	/* obsolete */
	[PCI_EXT_CAP_ID_ACS]	=	0xFF,
	[PCI_EXT_CAP_ID_ARI]	=	PCI_EXT_CAP_ARI_SIZखातापूर्ण,
	[PCI_EXT_CAP_ID_ATS]	=	PCI_EXT_CAP_ATS_SIZखातापूर्ण,
	[PCI_EXT_CAP_ID_SRIOV]	=	PCI_EXT_CAP_SRIOV_SIZखातापूर्ण,
	[PCI_EXT_CAP_ID_MRIOV]	=	0,	/* not yet */
	[PCI_EXT_CAP_ID_MCAST]	=	PCI_EXT_CAP_MCAST_ENDPOINT_SIZखातापूर्ण,
	[PCI_EXT_CAP_ID_PRI]	=	PCI_EXT_CAP_PRI_SIZखातापूर्ण,
	[PCI_EXT_CAP_ID_AMD_XXX] =	0,	/* not yet */
	[PCI_EXT_CAP_ID_REBAR]	=	0xFF,
	[PCI_EXT_CAP_ID_DPA]	=	0xFF,
	[PCI_EXT_CAP_ID_TPH]	=	0xFF,
	[PCI_EXT_CAP_ID_LTR]	=	PCI_EXT_CAP_LTR_SIZखातापूर्ण,
	[PCI_EXT_CAP_ID_SECPCI]	=	0,	/* not yet */
	[PCI_EXT_CAP_ID_PMUX]	=	0,	/* not yet */
	[PCI_EXT_CAP_ID_PASID]	=	0,	/* not yet */
पूर्ण;

/*
 * Read/Write Permission Bits - one bit क्रम each bit in capability
 * Any field can be पढ़ो अगर it exists, but what is पढ़ो depends on
 * whether the field is 'virtualized', or just pass through to the
 * hardware.  Any भवized field is also भवized क्रम ग_लिखोs.
 * Writes are only permitted अगर they have a 1 bit here.
 */
काष्ठा perm_bits अणु
	u8	*virt;		/* पढ़ो/ग_लिखो भव data, not hw */
	u8	*ग_लिखो;		/* ग_लिखोable bits */
	पूर्णांक	(*पढ़ोfn)(काष्ठा vfio_pci_device *vdev, पूर्णांक pos, पूर्णांक count,
			  काष्ठा perm_bits *perm, पूर्णांक offset, __le32 *val);
	पूर्णांक	(*ग_लिखोfn)(काष्ठा vfio_pci_device *vdev, पूर्णांक pos, पूर्णांक count,
			   काष्ठा perm_bits *perm, पूर्णांक offset, __le32 val);
पूर्ण;

#घोषणा	NO_VIRT		0
#घोषणा	ALL_VIRT	0xFFFFFFFFU
#घोषणा	NO_WRITE	0
#घोषणा	ALL_WRITE	0xFFFFFFFFU

अटल पूर्णांक vfio_user_config_पढ़ो(काष्ठा pci_dev *pdev, पूर्णांक offset,
				 __le32 *val, पूर्णांक count)
अणु
	पूर्णांक ret = -EINVAL;
	u32 पंचांगp_val = 0;

	चयन (count) अणु
	हाल 1:
	अणु
		u8 पंचांगp;
		ret = pci_user_पढ़ो_config_byte(pdev, offset, &पंचांगp);
		पंचांगp_val = पंचांगp;
		अवरोध;
	पूर्ण
	हाल 2:
	अणु
		u16 पंचांगp;
		ret = pci_user_पढ़ो_config_word(pdev, offset, &पंचांगp);
		पंचांगp_val = पंचांगp;
		अवरोध;
	पूर्ण
	हाल 4:
		ret = pci_user_पढ़ो_config_dword(pdev, offset, &पंचांगp_val);
		अवरोध;
	पूर्ण

	*val = cpu_to_le32(पंचांगp_val);

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_user_config_ग_लिखो(काष्ठा pci_dev *pdev, पूर्णांक offset,
				  __le32 val, पूर्णांक count)
अणु
	पूर्णांक ret = -EINVAL;
	u32 पंचांगp_val = le32_to_cpu(val);

	चयन (count) अणु
	हाल 1:
		ret = pci_user_ग_लिखो_config_byte(pdev, offset, पंचांगp_val);
		अवरोध;
	हाल 2:
		ret = pci_user_ग_लिखो_config_word(pdev, offset, पंचांगp_val);
		अवरोध;
	हाल 4:
		ret = pci_user_ग_लिखो_config_dword(pdev, offset, पंचांगp_val);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_शेष_config_पढ़ो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				    पूर्णांक count, काष्ठा perm_bits *perm,
				    पूर्णांक offset, __le32 *val)
अणु
	__le32 virt = 0;

	स_नकल(val, vdev->vconfig + pos, count);

	स_नकल(&virt, perm->virt + offset, count);

	/* Any non-भवized bits? */
	अगर (cpu_to_le32(~0U >> (32 - (count * 8))) != virt) अणु
		काष्ठा pci_dev *pdev = vdev->pdev;
		__le32 phys_val = 0;
		पूर्णांक ret;

		ret = vfio_user_config_पढ़ो(pdev, pos, &phys_val, count);
		अगर (ret)
			वापस ret;

		*val = (phys_val & ~virt) | (*val & virt);
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक vfio_शेष_config_ग_लिखो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				     पूर्णांक count, काष्ठा perm_bits *perm,
				     पूर्णांक offset, __le32 val)
अणु
	__le32 virt = 0, ग_लिखो = 0;

	स_नकल(&ग_लिखो, perm->ग_लिखो + offset, count);

	अगर (!ग_लिखो)
		वापस count; /* drop, no writable bits */

	स_नकल(&virt, perm->virt + offset, count);

	/* Virtualized and writable bits go to vconfig */
	अगर (ग_लिखो & virt) अणु
		__le32 virt_val = 0;

		स_नकल(&virt_val, vdev->vconfig + pos, count);

		virt_val &= ~(ग_लिखो & virt);
		virt_val |= (val & (ग_लिखो & virt));

		स_नकल(vdev->vconfig + pos, &virt_val, count);
	पूर्ण

	/* Non-भवzed and writable bits go to hardware */
	अगर (ग_लिखो & ~virt) अणु
		काष्ठा pci_dev *pdev = vdev->pdev;
		__le32 phys_val = 0;
		पूर्णांक ret;

		ret = vfio_user_config_पढ़ो(pdev, pos, &phys_val, count);
		अगर (ret)
			वापस ret;

		phys_val &= ~(ग_लिखो & ~virt);
		phys_val |= (val & (ग_लिखो & ~virt));

		ret = vfio_user_config_ग_लिखो(pdev, pos, phys_val, count);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस count;
पूर्ण

/* Allow direct पढ़ो from hardware, except क्रम capability next poपूर्णांकer */
अटल पूर्णांक vfio_direct_config_पढ़ो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				   पूर्णांक count, काष्ठा perm_bits *perm,
				   पूर्णांक offset, __le32 *val)
अणु
	पूर्णांक ret;

	ret = vfio_user_config_पढ़ो(vdev->pdev, pos, val, count);
	अगर (ret)
		वापस ret;

	अगर (pos >= PCI_CFG_SPACE_SIZE) अणु /* Extended cap header mangling */
		अगर (offset < 4)
			स_नकल(val, vdev->vconfig + pos, count);
	पूर्ण अन्यथा अगर (pos >= PCI_STD_HEADER_SIZखातापूर्ण) अणु /* Std cap mangling */
		अगर (offset == PCI_CAP_LIST_ID && count > 1)
			स_नकल(val, vdev->vconfig + pos,
			       min(PCI_CAP_FLAGS, count));
		अन्यथा अगर (offset == PCI_CAP_LIST_NEXT)
			स_नकल(val, vdev->vconfig + pos, 1);
	पूर्ण

	वापस count;
पूर्ण

/* Raw access skips any kind of भवization */
अटल पूर्णांक vfio_raw_config_ग_लिखो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				 पूर्णांक count, काष्ठा perm_bits *perm,
				 पूर्णांक offset, __le32 val)
अणु
	पूर्णांक ret;

	ret = vfio_user_config_ग_लिखो(vdev->pdev, pos, val, count);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल पूर्णांक vfio_raw_config_पढ़ो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				पूर्णांक count, काष्ठा perm_bits *perm,
				पूर्णांक offset, __le32 *val)
अणु
	पूर्णांक ret;

	ret = vfio_user_config_पढ़ो(vdev->pdev, pos, val, count);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

/* Virt access uses only भवization */
अटल पूर्णांक vfio_virt_config_ग_लिखो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				  पूर्णांक count, काष्ठा perm_bits *perm,
				  पूर्णांक offset, __le32 val)
अणु
	स_नकल(vdev->vconfig + pos, &val, count);
	वापस count;
पूर्ण

अटल पूर्णांक vfio_virt_config_पढ़ो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				 पूर्णांक count, काष्ठा perm_bits *perm,
				 पूर्णांक offset, __le32 *val)
अणु
	स_नकल(val, vdev->vconfig + pos, count);
	वापस count;
पूर्ण

/* Default capability regions to पढ़ो-only, no-भवization */
अटल काष्ठा perm_bits cap_perms[PCI_CAP_ID_MAX + 1] = अणु
	[0 ... PCI_CAP_ID_MAX] = अणु .पढ़ोfn = vfio_direct_config_पढ़ो पूर्ण
पूर्ण;
अटल काष्ठा perm_bits ecap_perms[PCI_EXT_CAP_ID_MAX + 1] = अणु
	[0 ... PCI_EXT_CAP_ID_MAX] = अणु .पढ़ोfn = vfio_direct_config_पढ़ो पूर्ण
पूर्ण;
/*
 * Default unasचिन्हित regions to raw पढ़ो-ग_लिखो access.  Some devices
 * require this to function as they hide रेजिस्टरs between the gaps in
 * config space (be2net).  Like MMIO and I/O port रेजिस्टरs, we have
 * to trust the hardware isolation.
 */
अटल काष्ठा perm_bits unasचिन्हित_perms = अणु
	.पढ़ोfn = vfio_raw_config_पढ़ो,
	.ग_लिखोfn = vfio_raw_config_ग_लिखो
पूर्ण;

अटल काष्ठा perm_bits virt_perms = अणु
	.पढ़ोfn = vfio_virt_config_पढ़ो,
	.ग_लिखोfn = vfio_virt_config_ग_लिखो
पूर्ण;

अटल व्योम मुक्त_perm_bits(काष्ठा perm_bits *perm)
अणु
	kमुक्त(perm->virt);
	kमुक्त(perm->ग_लिखो);
	perm->virt = शून्य;
	perm->ग_लिखो = शून्य;
पूर्ण

अटल पूर्णांक alloc_perm_bits(काष्ठा perm_bits *perm, पूर्णांक size)
अणु
	/*
	 * Round up all permission bits to the next dword, this lets us
	 * ignore whether a पढ़ो/ग_लिखो exceeds the defined capability
	 * काष्ठाure.  We can करो this because:
	 *  - Standard config space is alपढ़ोy dword aligned
	 *  - Capabilities are all dword aligned (bits 0:1 of next reserved)
	 *  - Express capabilities defined as dword aligned
	 */
	size = round_up(size, 4);

	/*
	 * Zero state is
	 * - All Readable, None Writeable, None Virtualized
	 */
	perm->virt = kzalloc(size, GFP_KERNEL);
	perm->ग_लिखो = kzalloc(size, GFP_KERNEL);
	अगर (!perm->virt || !perm->ग_लिखो) अणु
		मुक्त_perm_bits(perm);
		वापस -ENOMEM;
	पूर्ण

	perm->पढ़ोfn = vfio_शेष_config_पढ़ो;
	perm->ग_लिखोfn = vfio_शेष_config_ग_लिखो;

	वापस 0;
पूर्ण

/*
 * Helper functions क्रम filling in permission tables
 */
अटल अंतरभूत व्योम p_setb(काष्ठा perm_bits *p, पूर्णांक off, u8 virt, u8 ग_लिखो)
अणु
	p->virt[off] = virt;
	p->ग_लिखो[off] = ग_लिखो;
पूर्ण

/* Handle endian-ness - pci and tables are little-endian */
अटल अंतरभूत व्योम p_setw(काष्ठा perm_bits *p, पूर्णांक off, u16 virt, u16 ग_लिखो)
अणु
	*(__le16 *)(&p->virt[off]) = cpu_to_le16(virt);
	*(__le16 *)(&p->ग_लिखो[off]) = cpu_to_le16(ग_लिखो);
पूर्ण

/* Handle endian-ness - pci and tables are little-endian */
अटल अंतरभूत व्योम p_setd(काष्ठा perm_bits *p, पूर्णांक off, u32 virt, u32 ग_लिखो)
अणु
	*(__le32 *)(&p->virt[off]) = cpu_to_le32(virt);
	*(__le32 *)(&p->ग_लिखो[off]) = cpu_to_le32(ग_लिखो);
पूर्ण

/* Caller should hold memory_lock semaphore */
bool __vfio_pci_memory_enabled(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	u16 cmd = le16_to_cpu(*(__le16 *)&vdev->vconfig[PCI_COMMAND]);

	/*
	 * SR-IOV VF memory enable is handled by the MSE bit in the
	 * PF SR-IOV capability, there's thereक्रमe no need to trigger
	 * faults based on the भव value.
	 */
	वापस pdev->no_command_memory || (cmd & PCI_COMMAND_MEMORY);
पूर्ण

/*
 * Restore the *real* BARs after we detect a FLR or backकरोor reset.
 * (backकरोor = some device specअगरic technique that we didn't catch)
 */
अटल व्योम vfio_bar_restore(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	u32 *rbar = vdev->rbar;
	u16 cmd;
	पूर्णांक i;

	अगर (pdev->is_virtfn)
		वापस;

	pci_info(pdev, "%s: reset recovery - restoring BARs\n", __func__);

	क्रम (i = PCI_BASE_ADDRESS_0; i <= PCI_BASE_ADDRESS_5; i += 4, rbar++)
		pci_user_ग_लिखो_config_dword(pdev, i, *rbar);

	pci_user_ग_लिखो_config_dword(pdev, PCI_ROM_ADDRESS, *rbar);

	अगर (vdev->noपूर्णांकx) अणु
		pci_user_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
		cmd |= PCI_COMMAND_INTX_DISABLE;
		pci_user_ग_लिखो_config_word(pdev, PCI_COMMAND, cmd);
	पूर्ण
पूर्ण

अटल __le32 vfio_generate_bar_flags(काष्ठा pci_dev *pdev, पूर्णांक bar)
अणु
	अचिन्हित दीर्घ flags = pci_resource_flags(pdev, bar);
	u32 val;

	अगर (flags & IORESOURCE_IO)
		वापस cpu_to_le32(PCI_BASE_ADDRESS_SPACE_IO);

	val = PCI_BASE_ADDRESS_SPACE_MEMORY;

	अगर (flags & IORESOURCE_PREFETCH)
		val |= PCI_BASE_ADDRESS_MEM_PREFETCH;

	अगर (flags & IORESOURCE_MEM_64)
		val |= PCI_BASE_ADDRESS_MEM_TYPE_64;

	वापस cpu_to_le32(val);
पूर्ण

/*
 * Pretend we're hardware and tweak the values of the *भव* PCI BARs
 * to reflect the hardware capabilities.  This implements BAR sizing.
 */
अटल व्योम vfio_bar_fixup(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	पूर्णांक i;
	__le32 *vbar;
	u64 mask;

	अगर (!vdev->bardirty)
		वापस;

	vbar = (__le32 *)&vdev->vconfig[PCI_BASE_ADDRESS_0];

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++, vbar++) अणु
		पूर्णांक bar = i + PCI_STD_RESOURCES;

		अगर (!pci_resource_start(pdev, bar)) अणु
			*vbar = 0; /* Unmapped by host = unimplemented to user */
			जारी;
		पूर्ण

		mask = ~(pci_resource_len(pdev, bar) - 1);

		*vbar &= cpu_to_le32((u32)mask);
		*vbar |= vfio_generate_bar_flags(pdev, bar);

		अगर (*vbar & cpu_to_le32(PCI_BASE_ADDRESS_MEM_TYPE_64)) अणु
			vbar++;
			*vbar &= cpu_to_le32((u32)(mask >> 32));
			i++;
		पूर्ण
	पूर्ण

	vbar = (__le32 *)&vdev->vconfig[PCI_ROM_ADDRESS];

	/*
	 * NB. REGION_INFO will have reported zero size अगर we weren't able
	 * to पढ़ो the ROM, but we still वापस the actual BAR size here अगर
	 * it exists (or the shaकरोw ROM space).
	 */
	अगर (pci_resource_start(pdev, PCI_ROM_RESOURCE)) अणु
		mask = ~(pci_resource_len(pdev, PCI_ROM_RESOURCE) - 1);
		mask |= PCI_ROM_ADDRESS_ENABLE;
		*vbar &= cpu_to_le32((u32)mask);
	पूर्ण अन्यथा अगर (pdev->resource[PCI_ROM_RESOURCE].flags &
					IORESOURCE_ROM_SHADOW) अणु
		mask = ~(0x20000 - 1);
		mask |= PCI_ROM_ADDRESS_ENABLE;
		*vbar &= cpu_to_le32((u32)mask);
	पूर्ण अन्यथा
		*vbar = 0;

	vdev->bardirty = false;
पूर्ण

अटल पूर्णांक vfio_basic_config_पढ़ो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				  पूर्णांक count, काष्ठा perm_bits *perm,
				  पूर्णांक offset, __le32 *val)
अणु
	अगर (is_bar(offset)) /* pos == offset क्रम basic config */
		vfio_bar_fixup(vdev);

	count = vfio_शेष_config_पढ़ो(vdev, pos, count, perm, offset, val);

	/* Mask in भव memory enable */
	अगर (offset == PCI_COMMAND && vdev->pdev->no_command_memory) अणु
		u16 cmd = le16_to_cpu(*(__le16 *)&vdev->vconfig[PCI_COMMAND]);
		u32 पंचांगp_val = le32_to_cpu(*val);

		पंचांगp_val |= cmd & PCI_COMMAND_MEMORY;
		*val = cpu_to_le32(पंचांगp_val);
	पूर्ण

	वापस count;
पूर्ण

/* Test whether BARs match the value we think they should contain */
अटल bool vfio_need_bar_restore(काष्ठा vfio_pci_device *vdev)
अणु
	पूर्णांक i = 0, pos = PCI_BASE_ADDRESS_0, ret;
	u32 bar;

	क्रम (; pos <= PCI_BASE_ADDRESS_5; i++, pos += 4) अणु
		अगर (vdev->rbar[i]) अणु
			ret = pci_user_पढ़ो_config_dword(vdev->pdev, pos, &bar);
			अगर (ret || vdev->rbar[i] != bar)
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक vfio_basic_config_ग_लिखो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				   पूर्णांक count, काष्ठा perm_bits *perm,
				   पूर्णांक offset, __le32 val)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	__le16 *virt_cmd;
	u16 new_cmd = 0;
	पूर्णांक ret;

	virt_cmd = (__le16 *)&vdev->vconfig[PCI_COMMAND];

	अगर (offset == PCI_COMMAND) अणु
		bool phys_mem, virt_mem, new_mem, phys_io, virt_io, new_io;
		u16 phys_cmd;

		ret = pci_user_पढ़ो_config_word(pdev, PCI_COMMAND, &phys_cmd);
		अगर (ret)
			वापस ret;

		new_cmd = le32_to_cpu(val);

		phys_io = !!(phys_cmd & PCI_COMMAND_IO);
		virt_io = !!(le16_to_cpu(*virt_cmd) & PCI_COMMAND_IO);
		new_io = !!(new_cmd & PCI_COMMAND_IO);

		phys_mem = !!(phys_cmd & PCI_COMMAND_MEMORY);
		virt_mem = !!(le16_to_cpu(*virt_cmd) & PCI_COMMAND_MEMORY);
		new_mem = !!(new_cmd & PCI_COMMAND_MEMORY);

		अगर (!new_mem)
			vfio_pci_zap_and_करोwn_ग_लिखो_memory_lock(vdev);
		अन्यथा
			करोwn_ग_लिखो(&vdev->memory_lock);

		/*
		 * If the user is writing mem/io enable (new_mem/io) and we
		 * think it's alपढ़ोy enabled (virt_mem/io), but the hardware
		 * shows it disabled (phys_mem/io, then the device has
		 * undergone some kind of backकरोor reset and needs to be
		 * restored beक्रमe we allow it to enable the bars.
		 * SR-IOV devices will trigger this - क्रम mem enable let's
		 * catch this now and क्रम io enable it will be caught later
		 */
		अगर ((new_mem && virt_mem && !phys_mem &&
		     !pdev->no_command_memory) ||
		    (new_io && virt_io && !phys_io) ||
		    vfio_need_bar_restore(vdev))
			vfio_bar_restore(vdev);
	पूर्ण

	count = vfio_शेष_config_ग_लिखो(vdev, pos, count, perm, offset, val);
	अगर (count < 0) अणु
		अगर (offset == PCI_COMMAND)
			up_ग_लिखो(&vdev->memory_lock);
		वापस count;
	पूर्ण

	/*
	 * Save current memory/io enable bits in vconfig to allow क्रम
	 * the test above next समय.
	 */
	अगर (offset == PCI_COMMAND) अणु
		u16 mask = PCI_COMMAND_MEMORY | PCI_COMMAND_IO;

		*virt_cmd &= cpu_to_le16(~mask);
		*virt_cmd |= cpu_to_le16(new_cmd & mask);

		up_ग_लिखो(&vdev->memory_lock);
	पूर्ण

	/* Emulate INTx disable */
	अगर (offset >= PCI_COMMAND && offset <= PCI_COMMAND + 1) अणु
		bool virt_पूर्णांकx_disable;

		virt_पूर्णांकx_disable = !!(le16_to_cpu(*virt_cmd) &
				       PCI_COMMAND_INTX_DISABLE);

		अगर (virt_पूर्णांकx_disable && !vdev->virq_disabled) अणु
			vdev->virq_disabled = true;
			vfio_pci_पूर्णांकx_mask(vdev);
		पूर्ण अन्यथा अगर (!virt_पूर्णांकx_disable && vdev->virq_disabled) अणु
			vdev->virq_disabled = false;
			vfio_pci_पूर्णांकx_unmask(vdev);
		पूर्ण
	पूर्ण

	अगर (is_bar(offset))
		vdev->bardirty = true;

	वापस count;
पूर्ण

/* Permissions क्रम the Basic PCI Header */
अटल पूर्णांक __init init_pci_cap_basic_perm(काष्ठा perm_bits *perm)
अणु
	अगर (alloc_perm_bits(perm, PCI_STD_HEADER_SIZखातापूर्ण))
		वापस -ENOMEM;

	perm->पढ़ोfn = vfio_basic_config_पढ़ो;
	perm->ग_लिखोfn = vfio_basic_config_ग_लिखो;

	/* Virtualized क्रम SR-IOV functions, which just have FFFF */
	p_setw(perm, PCI_VENDOR_ID, (u16)ALL_VIRT, NO_WRITE);
	p_setw(perm, PCI_DEVICE_ID, (u16)ALL_VIRT, NO_WRITE);

	/*
	 * Virtualize INTx disable, we use it पूर्णांकernally क्रम पूर्णांकerrupt
	 * control and can emulate it क्रम non-PCI 2.3 devices.
	 */
	p_setw(perm, PCI_COMMAND, PCI_COMMAND_INTX_DISABLE, (u16)ALL_WRITE);

	/* Virtualize capability list, we might want to skip/disable */
	p_setw(perm, PCI_STATUS, PCI_STATUS_CAP_LIST, NO_WRITE);

	/* No harm to ग_लिखो */
	p_setb(perm, PCI_CACHE_LINE_SIZE, NO_VIRT, (u8)ALL_WRITE);
	p_setb(perm, PCI_LATENCY_TIMER, NO_VIRT, (u8)ALL_WRITE);
	p_setb(perm, PCI_BIST, NO_VIRT, (u8)ALL_WRITE);

	/* Virtualize all bars, can't touch the real ones */
	p_setd(perm, PCI_BASE_ADDRESS_0, ALL_VIRT, ALL_WRITE);
	p_setd(perm, PCI_BASE_ADDRESS_1, ALL_VIRT, ALL_WRITE);
	p_setd(perm, PCI_BASE_ADDRESS_2, ALL_VIRT, ALL_WRITE);
	p_setd(perm, PCI_BASE_ADDRESS_3, ALL_VIRT, ALL_WRITE);
	p_setd(perm, PCI_BASE_ADDRESS_4, ALL_VIRT, ALL_WRITE);
	p_setd(perm, PCI_BASE_ADDRESS_5, ALL_VIRT, ALL_WRITE);
	p_setd(perm, PCI_ROM_ADDRESS, ALL_VIRT, ALL_WRITE);

	/* Allow us to adjust capability chain */
	p_setb(perm, PCI_CAPABILITY_LIST, (u8)ALL_VIRT, NO_WRITE);

	/* Someबार used by sw, just भवize */
	p_setb(perm, PCI_INTERRUPT_LINE, (u8)ALL_VIRT, (u8)ALL_WRITE);

	/* Virtualize पूर्णांकerrupt pin to allow hiding INTx */
	p_setb(perm, PCI_INTERRUPT_PIN, (u8)ALL_VIRT, (u8)NO_WRITE);

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_pm_config_ग_लिखो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				पूर्णांक count, काष्ठा perm_bits *perm,
				पूर्णांक offset, __le32 val)
अणु
	count = vfio_शेष_config_ग_लिखो(vdev, pos, count, perm, offset, val);
	अगर (count < 0)
		वापस count;

	अगर (offset == PCI_PM_CTRL) अणु
		pci_घातer_t state;

		चयन (le32_to_cpu(val) & PCI_PM_CTRL_STATE_MASK) अणु
		हाल 0:
			state = PCI_D0;
			अवरोध;
		हाल 1:
			state = PCI_D1;
			अवरोध;
		हाल 2:
			state = PCI_D2;
			अवरोध;
		हाल 3:
			state = PCI_D3hot;
			अवरोध;
		पूर्ण

		vfio_pci_set_घातer_state(vdev, state);
	पूर्ण

	वापस count;
पूर्ण

/* Permissions क्रम the Power Management capability */
अटल पूर्णांक __init init_pci_cap_pm_perm(काष्ठा perm_bits *perm)
अणु
	अगर (alloc_perm_bits(perm, pci_cap_length[PCI_CAP_ID_PM]))
		वापस -ENOMEM;

	perm->ग_लिखोfn = vfio_pm_config_ग_लिखो;

	/*
	 * We always भवize the next field so we can हटाओ
	 * capabilities from the chain अगर we want to.
	 */
	p_setb(perm, PCI_CAP_LIST_NEXT, (u8)ALL_VIRT, NO_WRITE);

	/*
	 * Power management is defined *per function*, so we can let
	 * the user change घातer state, but we trap and initiate the
	 * change ourselves, so the state bits are पढ़ो-only.
	 */
	p_setd(perm, PCI_PM_CTRL, NO_VIRT, ~PCI_PM_CTRL_STATE_MASK);
	वापस 0;
पूर्ण

अटल पूर्णांक vfio_vpd_config_ग_लिखो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				 पूर्णांक count, काष्ठा perm_bits *perm,
				 पूर्णांक offset, __le32 val)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	__le16 *paddr = (__le16 *)(vdev->vconfig + pos - offset + PCI_VPD_ADDR);
	__le32 *pdata = (__le32 *)(vdev->vconfig + pos - offset + PCI_VPD_DATA);
	u16 addr;
	u32 data;

	/*
	 * Write through to emulation.  If the ग_लिखो includes the upper byte
	 * of PCI_VPD_ADDR, then the PCI_VPD_ADDR_F bit is written and we
	 * have work to करो.
	 */
	count = vfio_शेष_config_ग_लिखो(vdev, pos, count, perm, offset, val);
	अगर (count < 0 || offset > PCI_VPD_ADDR + 1 ||
	    offset + count <= PCI_VPD_ADDR + 1)
		वापस count;

	addr = le16_to_cpu(*paddr);

	अगर (addr & PCI_VPD_ADDR_F) अणु
		data = le32_to_cpu(*pdata);
		अगर (pci_ग_लिखो_vpd(pdev, addr & ~PCI_VPD_ADDR_F, 4, &data) != 4)
			वापस count;
	पूर्ण अन्यथा अणु
		data = 0;
		अगर (pci_पढ़ो_vpd(pdev, addr, 4, &data) < 0)
			वापस count;
		*pdata = cpu_to_le32(data);
	पूर्ण

	/*
	 * Toggle PCI_VPD_ADDR_F in the emulated PCI_VPD_ADDR रेजिस्टर to
	 * संकेत completion.  If an error occurs above, we assume that not
	 * toggling this bit will induce a driver समयout.
	 */
	addr ^= PCI_VPD_ADDR_F;
	*paddr = cpu_to_le16(addr);

	वापस count;
पूर्ण

/* Permissions क्रम Vital Product Data capability */
अटल पूर्णांक __init init_pci_cap_vpd_perm(काष्ठा perm_bits *perm)
अणु
	अगर (alloc_perm_bits(perm, pci_cap_length[PCI_CAP_ID_VPD]))
		वापस -ENOMEM;

	perm->ग_लिखोfn = vfio_vpd_config_ग_लिखो;

	/*
	 * We always भवize the next field so we can हटाओ
	 * capabilities from the chain अगर we want to.
	 */
	p_setb(perm, PCI_CAP_LIST_NEXT, (u8)ALL_VIRT, NO_WRITE);

	/*
	 * Both the address and data रेजिस्टरs are भवized to
	 * enable access through the pci_vpd_पढ़ो/ग_लिखो functions
	 */
	p_setw(perm, PCI_VPD_ADDR, (u16)ALL_VIRT, (u16)ALL_WRITE);
	p_setd(perm, PCI_VPD_DATA, ALL_VIRT, ALL_WRITE);

	वापस 0;
पूर्ण

/* Permissions क्रम PCI-X capability */
अटल पूर्णांक __init init_pci_cap_pcix_perm(काष्ठा perm_bits *perm)
अणु
	/* Alloc 24, but only 8 are used in v0 */
	अगर (alloc_perm_bits(perm, PCI_CAP_PCIX_SIZखातापूर्ण_V2))
		वापस -ENOMEM;

	p_setb(perm, PCI_CAP_LIST_NEXT, (u8)ALL_VIRT, NO_WRITE);

	p_setw(perm, PCI_X_CMD, NO_VIRT, (u16)ALL_WRITE);
	p_setd(perm, PCI_X_ECC_CSR, NO_VIRT, ALL_WRITE);
	वापस 0;
पूर्ण

अटल पूर्णांक vfio_exp_config_ग_लिखो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				 पूर्णांक count, काष्ठा perm_bits *perm,
				 पूर्णांक offset, __le32 val)
अणु
	__le16 *ctrl = (__le16 *)(vdev->vconfig + pos -
				  offset + PCI_EXP_DEVCTL);
	पूर्णांक पढ़ोrq = le16_to_cpu(*ctrl) & PCI_EXP_DEVCTL_READRQ;

	count = vfio_शेष_config_ग_लिखो(vdev, pos, count, perm, offset, val);
	अगर (count < 0)
		वापस count;

	/*
	 * The FLR bit is भवized, अगर set and the device supports PCIe
	 * FLR, issue a reset_function.  Regardless, clear the bit, the spec
	 * requires it to be always पढ़ो as zero.  NB, reset_function might
	 * not use a PCIe FLR, we करोn't have that level of granularity.
	 */
	अगर (*ctrl & cpu_to_le16(PCI_EXP_DEVCTL_BCR_FLR)) अणु
		u32 cap;
		पूर्णांक ret;

		*ctrl &= ~cpu_to_le16(PCI_EXP_DEVCTL_BCR_FLR);

		ret = pci_user_पढ़ो_config_dword(vdev->pdev,
						 pos - offset + PCI_EXP_DEVCAP,
						 &cap);

		अगर (!ret && (cap & PCI_EXP_DEVCAP_FLR)) अणु
			vfio_pci_zap_and_करोwn_ग_लिखो_memory_lock(vdev);
			pci_try_reset_function(vdev->pdev);
			up_ग_लिखो(&vdev->memory_lock);
		पूर्ण
	पूर्ण

	/*
	 * MPS is भवized to the user, ग_लिखोs करो not change the physical
	 * रेजिस्टर since determining a proper MPS value requires a प्रणाली wide
	 * device view.  The MRRS is largely independent of MPS, but since the
	 * user करोes not have that प्रणाली-wide view, they might set a safe, but
	 * inefficiently low value.  Here we allow ग_लिखोs through to hardware,
	 * but we set the न्यूनमान to the physical device MPS setting, so that
	 * we can at least use full TLPs, as defined by the MPS value.
	 *
	 * NB, अगर any devices actually depend on an artअगरicially low MRRS
	 * setting, this will need to be revisited, perhaps with a quirk
	 * though pcie_set_पढ़ोrq().
	 */
	अगर (पढ़ोrq != (le16_to_cpu(*ctrl) & PCI_EXP_DEVCTL_READRQ)) अणु
		पढ़ोrq = 128 <<
			((le16_to_cpu(*ctrl) & PCI_EXP_DEVCTL_READRQ) >> 12);
		पढ़ोrq = max(पढ़ोrq, pcie_get_mps(vdev->pdev));

		pcie_set_पढ़ोrq(vdev->pdev, पढ़ोrq);
	पूर्ण

	वापस count;
पूर्ण

/* Permissions क्रम PCI Express capability */
अटल पूर्णांक __init init_pci_cap_exp_perm(काष्ठा perm_bits *perm)
अणु
	/* Alloc largest of possible sizes */
	अगर (alloc_perm_bits(perm, PCI_CAP_EXP_ENDPOINT_SIZखातापूर्ण_V2))
		वापस -ENOMEM;

	perm->ग_लिखोfn = vfio_exp_config_ग_लिखो;

	p_setb(perm, PCI_CAP_LIST_NEXT, (u8)ALL_VIRT, NO_WRITE);

	/*
	 * Allow ग_लिखोs to device control fields, except devctl_phantom,
	 * which could confuse IOMMU, MPS, which can अवरोध communication
	 * with other physical devices, and the ARI bit in devctl2, which
	 * is set at probe समय.  FLR and MRRS get भवized via our
	 * ग_लिखोfn.
	 */
	p_setw(perm, PCI_EXP_DEVCTL,
	       PCI_EXP_DEVCTL_BCR_FLR | PCI_EXP_DEVCTL_PAYLOAD |
	       PCI_EXP_DEVCTL_READRQ, ~PCI_EXP_DEVCTL_PHANTOM);
	p_setw(perm, PCI_EXP_DEVCTL2, NO_VIRT, ~PCI_EXP_DEVCTL2_ARI);
	वापस 0;
पूर्ण

अटल पूर्णांक vfio_af_config_ग_लिखो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				पूर्णांक count, काष्ठा perm_bits *perm,
				पूर्णांक offset, __le32 val)
अणु
	u8 *ctrl = vdev->vconfig + pos - offset + PCI_AF_CTRL;

	count = vfio_शेष_config_ग_लिखो(vdev, pos, count, perm, offset, val);
	अगर (count < 0)
		वापस count;

	/*
	 * The FLR bit is भवized, अगर set and the device supports AF
	 * FLR, issue a reset_function.  Regardless, clear the bit, the spec
	 * requires it to be always पढ़ो as zero.  NB, reset_function might
	 * not use an AF FLR, we करोn't have that level of granularity.
	 */
	अगर (*ctrl & PCI_AF_CTRL_FLR) अणु
		u8 cap;
		पूर्णांक ret;

		*ctrl &= ~PCI_AF_CTRL_FLR;

		ret = pci_user_पढ़ो_config_byte(vdev->pdev,
						pos - offset + PCI_AF_CAP,
						&cap);

		अगर (!ret && (cap & PCI_AF_CAP_FLR) && (cap & PCI_AF_CAP_TP)) अणु
			vfio_pci_zap_and_करोwn_ग_लिखो_memory_lock(vdev);
			pci_try_reset_function(vdev->pdev);
			up_ग_लिखो(&vdev->memory_lock);
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

/* Permissions क्रम Advanced Function capability */
अटल पूर्णांक __init init_pci_cap_af_perm(काष्ठा perm_bits *perm)
अणु
	अगर (alloc_perm_bits(perm, pci_cap_length[PCI_CAP_ID_AF]))
		वापस -ENOMEM;

	perm->ग_लिखोfn = vfio_af_config_ग_लिखो;

	p_setb(perm, PCI_CAP_LIST_NEXT, (u8)ALL_VIRT, NO_WRITE);
	p_setb(perm, PCI_AF_CTRL, PCI_AF_CTRL_FLR, PCI_AF_CTRL_FLR);
	वापस 0;
पूर्ण

/* Permissions क्रम Advanced Error Reporting extended capability */
अटल पूर्णांक __init init_pci_ext_cap_err_perm(काष्ठा perm_bits *perm)
अणु
	u32 mask;

	अगर (alloc_perm_bits(perm, pci_ext_cap_length[PCI_EXT_CAP_ID_ERR]))
		वापस -ENOMEM;

	/*
	 * Virtualize the first dword of all express capabilities
	 * because it includes the next poपूर्णांकer.  This lets us later
	 * हटाओ capabilities from the chain अगर we need to.
	 */
	p_setd(perm, 0, ALL_VIRT, NO_WRITE);

	/* Writable bits mask */
	mask =	PCI_ERR_UNC_UND |		/* Undefined */
		PCI_ERR_UNC_DLP |		/* Data Link Protocol */
		PCI_ERR_UNC_SURPDN |		/* Surprise Down */
		PCI_ERR_UNC_POISON_TLP |	/* Poisoned TLP */
		PCI_ERR_UNC_FCP |		/* Flow Control Protocol */
		PCI_ERR_UNC_COMP_TIME |		/* Completion Timeout */
		PCI_ERR_UNC_COMP_ABORT |	/* Completer Abort */
		PCI_ERR_UNC_UNX_COMP |		/* Unexpected Completion */
		PCI_ERR_UNC_RX_OVER |		/* Receiver Overflow */
		PCI_ERR_UNC_MALF_TLP |		/* Malक्रमmed TLP */
		PCI_ERR_UNC_ECRC |		/* ECRC Error Status */
		PCI_ERR_UNC_UNSUP |		/* Unsupported Request */
		PCI_ERR_UNC_ACSV |		/* ACS Violation */
		PCI_ERR_UNC_INTN |		/* पूर्णांकernal error */
		PCI_ERR_UNC_MCBTLP |		/* MC blocked TLP */
		PCI_ERR_UNC_ATOMEG |		/* Atomic egress blocked */
		PCI_ERR_UNC_TLPPRE;		/* TLP prefix blocked */
	p_setd(perm, PCI_ERR_UNCOR_STATUS, NO_VIRT, mask);
	p_setd(perm, PCI_ERR_UNCOR_MASK, NO_VIRT, mask);
	p_setd(perm, PCI_ERR_UNCOR_SEVER, NO_VIRT, mask);

	mask =	PCI_ERR_COR_RCVR |		/* Receiver Error Status */
		PCI_ERR_COR_BAD_TLP |		/* Bad TLP Status */
		PCI_ERR_COR_BAD_DLLP |		/* Bad DLLP Status */
		PCI_ERR_COR_REP_ROLL |		/* REPLAY_NUM Rollover */
		PCI_ERR_COR_REP_TIMER |		/* Replay Timer Timeout */
		PCI_ERR_COR_ADV_NFAT |		/* Advisory Non-Fatal */
		PCI_ERR_COR_INTERNAL |		/* Corrected Internal */
		PCI_ERR_COR_LOG_OVER;		/* Header Log Overflow */
	p_setd(perm, PCI_ERR_COR_STATUS, NO_VIRT, mask);
	p_setd(perm, PCI_ERR_COR_MASK, NO_VIRT, mask);

	mask =	PCI_ERR_CAP_ECRC_GENE |		/* ECRC Generation Enable */
		PCI_ERR_CAP_ECRC_CHKE;		/* ECRC Check Enable */
	p_setd(perm, PCI_ERR_CAP, NO_VIRT, mask);
	वापस 0;
पूर्ण

/* Permissions क्रम Power Budgeting extended capability */
अटल पूर्णांक __init init_pci_ext_cap_pwr_perm(काष्ठा perm_bits *perm)
अणु
	अगर (alloc_perm_bits(perm, pci_ext_cap_length[PCI_EXT_CAP_ID_PWR]))
		वापस -ENOMEM;

	p_setd(perm, 0, ALL_VIRT, NO_WRITE);

	/* Writing the data selector is OK, the info is still पढ़ो-only */
	p_setb(perm, PCI_PWR_DATA, NO_VIRT, (u8)ALL_WRITE);
	वापस 0;
पूर्ण

/*
 * Initialize the shared permission tables
 */
व्योम vfio_pci_uninit_perm_bits(व्योम)
अणु
	मुक्त_perm_bits(&cap_perms[PCI_CAP_ID_BASIC]);

	मुक्त_perm_bits(&cap_perms[PCI_CAP_ID_PM]);
	मुक्त_perm_bits(&cap_perms[PCI_CAP_ID_VPD]);
	मुक्त_perm_bits(&cap_perms[PCI_CAP_ID_PCIX]);
	मुक्त_perm_bits(&cap_perms[PCI_CAP_ID_EXP]);
	मुक्त_perm_bits(&cap_perms[PCI_CAP_ID_AF]);

	मुक्त_perm_bits(&ecap_perms[PCI_EXT_CAP_ID_ERR]);
	मुक्त_perm_bits(&ecap_perms[PCI_EXT_CAP_ID_PWR]);
पूर्ण

पूर्णांक __init vfio_pci_init_perm_bits(व्योम)
अणु
	पूर्णांक ret;

	/* Basic config space */
	ret = init_pci_cap_basic_perm(&cap_perms[PCI_CAP_ID_BASIC]);

	/* Capabilities */
	ret |= init_pci_cap_pm_perm(&cap_perms[PCI_CAP_ID_PM]);
	ret |= init_pci_cap_vpd_perm(&cap_perms[PCI_CAP_ID_VPD]);
	ret |= init_pci_cap_pcix_perm(&cap_perms[PCI_CAP_ID_PCIX]);
	cap_perms[PCI_CAP_ID_VNDR].ग_लिखोfn = vfio_raw_config_ग_लिखो;
	ret |= init_pci_cap_exp_perm(&cap_perms[PCI_CAP_ID_EXP]);
	ret |= init_pci_cap_af_perm(&cap_perms[PCI_CAP_ID_AF]);

	/* Extended capabilities */
	ret |= init_pci_ext_cap_err_perm(&ecap_perms[PCI_EXT_CAP_ID_ERR]);
	ret |= init_pci_ext_cap_pwr_perm(&ecap_perms[PCI_EXT_CAP_ID_PWR]);
	ecap_perms[PCI_EXT_CAP_ID_VNDR].ग_लिखोfn = vfio_raw_config_ग_लिखो;

	अगर (ret)
		vfio_pci_uninit_perm_bits();

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_find_cap_start(काष्ठा vfio_pci_device *vdev, पूर्णांक pos)
अणु
	u8 cap;
	पूर्णांक base = (pos >= PCI_CFG_SPACE_SIZE) ? PCI_CFG_SPACE_SIZE :
						 PCI_STD_HEADER_SIZखातापूर्ण;
	cap = vdev->pci_config_map[pos];

	अगर (cap == PCI_CAP_ID_BASIC)
		वापस 0;

	/* XXX Can we have to abutting capabilities of the same type? */
	जबतक (pos - 1 >= base && vdev->pci_config_map[pos - 1] == cap)
		pos--;

	वापस pos;
पूर्ण

अटल पूर्णांक vfio_msi_config_पढ़ो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				पूर्णांक count, काष्ठा perm_bits *perm,
				पूर्णांक offset, __le32 *val)
अणु
	/* Update max available queue size from msi_qmax */
	अगर (offset <= PCI_MSI_FLAGS && offset + count >= PCI_MSI_FLAGS) अणु
		__le16 *flags;
		पूर्णांक start;

		start = vfio_find_cap_start(vdev, pos);

		flags = (__le16 *)&vdev->vconfig[start];

		*flags &= cpu_to_le16(~PCI_MSI_FLAGS_QMASK);
		*flags |= cpu_to_le16(vdev->msi_qmax << 1);
	पूर्ण

	वापस vfio_शेष_config_पढ़ो(vdev, pos, count, perm, offset, val);
पूर्ण

अटल पूर्णांक vfio_msi_config_ग_लिखो(काष्ठा vfio_pci_device *vdev, पूर्णांक pos,
				 पूर्णांक count, काष्ठा perm_bits *perm,
				 पूर्णांक offset, __le32 val)
अणु
	count = vfio_शेष_config_ग_लिखो(vdev, pos, count, perm, offset, val);
	अगर (count < 0)
		वापस count;

	/* Fixup and ग_लिखो configured queue size and enable to hardware */
	अगर (offset <= PCI_MSI_FLAGS && offset + count >= PCI_MSI_FLAGS) अणु
		__le16 *pflags;
		u16 flags;
		पूर्णांक start, ret;

		start = vfio_find_cap_start(vdev, pos);

		pflags = (__le16 *)&vdev->vconfig[start + PCI_MSI_FLAGS];

		flags = le16_to_cpu(*pflags);

		/* MSI is enabled via ioctl */
		अगर  (!is_msi(vdev))
			flags &= ~PCI_MSI_FLAGS_ENABLE;

		/* Check queue size */
		अगर ((flags & PCI_MSI_FLAGS_QSIZE) >> 4 > vdev->msi_qmax) अणु
			flags &= ~PCI_MSI_FLAGS_QSIZE;
			flags |= vdev->msi_qmax << 4;
		पूर्ण

		/* Write back to virt and to hardware */
		*pflags = cpu_to_le16(flags);
		ret = pci_user_ग_लिखो_config_word(vdev->pdev,
						 start + PCI_MSI_FLAGS,
						 flags);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस count;
पूर्ण

/*
 * MSI determination is per-device, so this routine माला_लो used beyond
 * initialization समय. Don't add __init
 */
अटल पूर्णांक init_pci_cap_msi_perm(काष्ठा perm_bits *perm, पूर्णांक len, u16 flags)
अणु
	अगर (alloc_perm_bits(perm, len))
		वापस -ENOMEM;

	perm->पढ़ोfn = vfio_msi_config_पढ़ो;
	perm->ग_लिखोfn = vfio_msi_config_ग_लिखो;

	p_setb(perm, PCI_CAP_LIST_NEXT, (u8)ALL_VIRT, NO_WRITE);

	/*
	 * The upper byte of the control रेजिस्टर is reserved,
	 * just setup the lower byte.
	 */
	p_setb(perm, PCI_MSI_FLAGS, (u8)ALL_VIRT, (u8)ALL_WRITE);
	p_setd(perm, PCI_MSI_ADDRESS_LO, ALL_VIRT, ALL_WRITE);
	अगर (flags & PCI_MSI_FLAGS_64BIT) अणु
		p_setd(perm, PCI_MSI_ADDRESS_HI, ALL_VIRT, ALL_WRITE);
		p_setw(perm, PCI_MSI_DATA_64, (u16)ALL_VIRT, (u16)ALL_WRITE);
		अगर (flags & PCI_MSI_FLAGS_MASKBIT) अणु
			p_setd(perm, PCI_MSI_MASK_64, NO_VIRT, ALL_WRITE);
			p_setd(perm, PCI_MSI_PENDING_64, NO_VIRT, ALL_WRITE);
		पूर्ण
	पूर्ण अन्यथा अणु
		p_setw(perm, PCI_MSI_DATA_32, (u16)ALL_VIRT, (u16)ALL_WRITE);
		अगर (flags & PCI_MSI_FLAGS_MASKBIT) अणु
			p_setd(perm, PCI_MSI_MASK_32, NO_VIRT, ALL_WRITE);
			p_setd(perm, PCI_MSI_PENDING_32, NO_VIRT, ALL_WRITE);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Determine MSI CAP field length; initialize msi_perms on 1st call per vdev */
अटल पूर्णांक vfio_msi_cap_len(काष्ठा vfio_pci_device *vdev, u8 pos)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	पूर्णांक len, ret;
	u16 flags;

	ret = pci_पढ़ो_config_word(pdev, pos + PCI_MSI_FLAGS, &flags);
	अगर (ret)
		वापस pcibios_err_to_त्रुटि_सं(ret);

	len = 10; /* Minimum size */
	अगर (flags & PCI_MSI_FLAGS_64BIT)
		len += 4;
	अगर (flags & PCI_MSI_FLAGS_MASKBIT)
		len += 10;

	अगर (vdev->msi_perm)
		वापस len;

	vdev->msi_perm = kदो_स्मृति(माप(काष्ठा perm_bits), GFP_KERNEL);
	अगर (!vdev->msi_perm)
		वापस -ENOMEM;

	ret = init_pci_cap_msi_perm(vdev->msi_perm, len, flags);
	अगर (ret) अणु
		kमुक्त(vdev->msi_perm);
		वापस ret;
	पूर्ण

	वापस len;
पूर्ण

/* Determine extended capability length क्रम VC (2 & 9) and MFVC */
अटल पूर्णांक vfio_vc_cap_len(काष्ठा vfio_pci_device *vdev, u16 pos)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	u32 पंचांगp;
	पूर्णांक ret, evcc, phases, vc_arb;
	पूर्णांक len = PCI_CAP_VC_BASE_SIZखातापूर्ण;

	ret = pci_पढ़ो_config_dword(pdev, pos + PCI_VC_PORT_CAP1, &पंचांगp);
	अगर (ret)
		वापस pcibios_err_to_त्रुटि_सं(ret);

	evcc = पंचांगp & PCI_VC_CAP1_EVCC; /* extended vc count */
	ret = pci_पढ़ो_config_dword(pdev, pos + PCI_VC_PORT_CAP2, &पंचांगp);
	अगर (ret)
		वापस pcibios_err_to_त्रुटि_सं(ret);

	अगर (पंचांगp & PCI_VC_CAP2_128_PHASE)
		phases = 128;
	अन्यथा अगर (पंचांगp & PCI_VC_CAP2_64_PHASE)
		phases = 64;
	अन्यथा अगर (पंचांगp & PCI_VC_CAP2_32_PHASE)
		phases = 32;
	अन्यथा
		phases = 0;

	vc_arb = phases * 4;

	/*
	 * Port arbitration tables are root & चयन only;
	 * function arbitration tables are function 0 only.
	 * In either हाल, we'll never let user ग_लिखो them so
	 * we करोn't care how big they are
	 */
	len += (1 + evcc) * PCI_CAP_VC_PER_VC_SIZखातापूर्ण;
	अगर (vc_arb) अणु
		len = round_up(len, 16);
		len += vc_arb / 8;
	पूर्ण
	वापस len;
पूर्ण

अटल पूर्णांक vfio_cap_len(काष्ठा vfio_pci_device *vdev, u8 cap, u8 pos)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	u32 dword;
	u16 word;
	u8 byte;
	पूर्णांक ret;

	चयन (cap) अणु
	हाल PCI_CAP_ID_MSI:
		वापस vfio_msi_cap_len(vdev, pos);
	हाल PCI_CAP_ID_PCIX:
		ret = pci_पढ़ो_config_word(pdev, pos + PCI_X_CMD, &word);
		अगर (ret)
			वापस pcibios_err_to_त्रुटि_सं(ret);

		अगर (PCI_X_CMD_VERSION(word)) अणु
			अगर (pdev->cfg_size > PCI_CFG_SPACE_SIZE) अणु
				/* Test क्रम extended capabilities */
				pci_पढ़ो_config_dword(pdev, PCI_CFG_SPACE_SIZE,
						      &dword);
				vdev->extended_caps = (dword != 0);
			पूर्ण
			वापस PCI_CAP_PCIX_SIZखातापूर्ण_V2;
		पूर्ण अन्यथा
			वापस PCI_CAP_PCIX_SIZखातापूर्ण_V0;
	हाल PCI_CAP_ID_VNDR:
		/* length follows next field */
		ret = pci_पढ़ो_config_byte(pdev, pos + PCI_CAP_FLAGS, &byte);
		अगर (ret)
			वापस pcibios_err_to_त्रुटि_सं(ret);

		वापस byte;
	हाल PCI_CAP_ID_EXP:
		अगर (pdev->cfg_size > PCI_CFG_SPACE_SIZE) अणु
			/* Test क्रम extended capabilities */
			pci_पढ़ो_config_dword(pdev, PCI_CFG_SPACE_SIZE, &dword);
			vdev->extended_caps = (dword != 0);
		पूर्ण

		/* length based on version and type */
		अगर ((pcie_caps_reg(pdev) & PCI_EXP_FLAGS_VERS) == 1) अणु
			अगर (pci_pcie_type(pdev) == PCI_EXP_TYPE_RC_END)
				वापस 0xc; /* "All Devices" only, no link */
			वापस PCI_CAP_EXP_ENDPOINT_SIZखातापूर्ण_V1;
		पूर्ण अन्यथा अणु
			अगर (pci_pcie_type(pdev) == PCI_EXP_TYPE_RC_END)
				वापस 0x2c; /* No link */
			वापस PCI_CAP_EXP_ENDPOINT_SIZखातापूर्ण_V2;
		पूर्ण
	हाल PCI_CAP_ID_HT:
		ret = pci_पढ़ो_config_byte(pdev, pos + 3, &byte);
		अगर (ret)
			वापस pcibios_err_to_त्रुटि_सं(ret);

		वापस (byte & HT_3BIT_CAP_MASK) ?
			HT_CAP_SIZखातापूर्ण_SHORT : HT_CAP_SIZखातापूर्ण_LONG;
	हाल PCI_CAP_ID_SATA:
		ret = pci_पढ़ो_config_byte(pdev, pos + PCI_SATA_REGS, &byte);
		अगर (ret)
			वापस pcibios_err_to_त्रुटि_सं(ret);

		byte &= PCI_SATA_REGS_MASK;
		अगर (byte == PCI_SATA_REGS_INLINE)
			वापस PCI_SATA_SIZखातापूर्ण_LONG;
		अन्यथा
			वापस PCI_SATA_SIZखातापूर्ण_SHORT;
	शेष:
		pci_warn(pdev, "%s: unknown length for PCI cap %#x@%#x\n",
			 __func__, cap, pos);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_ext_cap_len(काष्ठा vfio_pci_device *vdev, u16 ecap, u16 epos)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	u8 byte;
	u32 dword;
	पूर्णांक ret;

	चयन (ecap) अणु
	हाल PCI_EXT_CAP_ID_VNDR:
		ret = pci_पढ़ो_config_dword(pdev, epos + PCI_VSEC_HDR, &dword);
		अगर (ret)
			वापस pcibios_err_to_त्रुटि_सं(ret);

		वापस dword >> PCI_VSEC_HDR_LEN_SHIFT;
	हाल PCI_EXT_CAP_ID_VC:
	हाल PCI_EXT_CAP_ID_VC9:
	हाल PCI_EXT_CAP_ID_MFVC:
		वापस vfio_vc_cap_len(vdev, epos);
	हाल PCI_EXT_CAP_ID_ACS:
		ret = pci_पढ़ो_config_byte(pdev, epos + PCI_ACS_CAP, &byte);
		अगर (ret)
			वापस pcibios_err_to_त्रुटि_सं(ret);

		अगर (byte & PCI_ACS_EC) अणु
			पूर्णांक bits;

			ret = pci_पढ़ो_config_byte(pdev,
						   epos + PCI_ACS_EGRESS_BITS,
						   &byte);
			अगर (ret)
				वापस pcibios_err_to_त्रुटि_सं(ret);

			bits = byte ? round_up(byte, 32) : 256;
			वापस 8 + (bits / 8);
		पूर्ण
		वापस 8;

	हाल PCI_EXT_CAP_ID_REBAR:
		ret = pci_पढ़ो_config_byte(pdev, epos + PCI_REBAR_CTRL, &byte);
		अगर (ret)
			वापस pcibios_err_to_त्रुटि_सं(ret);

		byte &= PCI_REBAR_CTRL_NBAR_MASK;
		byte >>= PCI_REBAR_CTRL_NBAR_SHIFT;

		वापस 4 + (byte * 8);
	हाल PCI_EXT_CAP_ID_DPA:
		ret = pci_पढ़ो_config_byte(pdev, epos + PCI_DPA_CAP, &byte);
		अगर (ret)
			वापस pcibios_err_to_त्रुटि_सं(ret);

		byte &= PCI_DPA_CAP_SUBSTATE_MASK;
		वापस PCI_DPA_BASE_SIZखातापूर्ण + byte + 1;
	हाल PCI_EXT_CAP_ID_TPH:
		ret = pci_पढ़ो_config_dword(pdev, epos + PCI_TPH_CAP, &dword);
		अगर (ret)
			वापस pcibios_err_to_त्रुटि_सं(ret);

		अगर ((dword & PCI_TPH_CAP_LOC_MASK) == PCI_TPH_LOC_CAP) अणु
			पूर्णांक sts;

			sts = dword & PCI_TPH_CAP_ST_MASK;
			sts >>= PCI_TPH_CAP_ST_SHIFT;
			वापस PCI_TPH_BASE_SIZखातापूर्ण + (sts * 2) + 2;
		पूर्ण
		वापस PCI_TPH_BASE_SIZखातापूर्ण;
	शेष:
		pci_warn(pdev, "%s: unknown length for PCI ecap %#x@%#x\n",
			 __func__, ecap, epos);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_fill_vconfig_bytes(काष्ठा vfio_pci_device *vdev,
				   पूर्णांक offset, पूर्णांक size)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	पूर्णांक ret = 0;

	/*
	 * We try to पढ़ो physical config space in the largest chunks
	 * we can, assuming that all of the fields support dword access.
	 * pci_save_state() makes this same assumption and seems to करो ok.
	 */
	जबतक (size) अणु
		पूर्णांक filled;

		अगर (size >= 4 && !(offset % 4)) अणु
			__le32 *dwordp = (__le32 *)&vdev->vconfig[offset];
			u32 dword;

			ret = pci_पढ़ो_config_dword(pdev, offset, &dword);
			अगर (ret)
				वापस ret;
			*dwordp = cpu_to_le32(dword);
			filled = 4;
		पूर्ण अन्यथा अगर (size >= 2 && !(offset % 2)) अणु
			__le16 *wordp = (__le16 *)&vdev->vconfig[offset];
			u16 word;

			ret = pci_पढ़ो_config_word(pdev, offset, &word);
			अगर (ret)
				वापस ret;
			*wordp = cpu_to_le16(word);
			filled = 2;
		पूर्ण अन्यथा अणु
			u8 *byte = &vdev->vconfig[offset];
			ret = pci_पढ़ो_config_byte(pdev, offset, byte);
			अगर (ret)
				वापस ret;
			filled = 1;
		पूर्ण

		offset += filled;
		size -= filled;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_cap_init(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	u8 *map = vdev->pci_config_map;
	u16 status;
	u8 pos, *prev, cap;
	पूर्णांक loops, ret, caps = 0;

	/* Any capabilities? */
	ret = pci_पढ़ो_config_word(pdev, PCI_STATUS, &status);
	अगर (ret)
		वापस ret;

	अगर (!(status & PCI_STATUS_CAP_LIST))
		वापस 0; /* Done */

	ret = pci_पढ़ो_config_byte(pdev, PCI_CAPABILITY_LIST, &pos);
	अगर (ret)
		वापस ret;

	/* Mark the previous position in हाल we want to skip a capability */
	prev = &vdev->vconfig[PCI_CAPABILITY_LIST];

	/* We can bound our loop, capabilities are dword aligned */
	loops = (PCI_CFG_SPACE_SIZE - PCI_STD_HEADER_SIZखातापूर्ण) / PCI_CAP_SIZखातापूर्ण;
	जबतक (pos && loops--) अणु
		u8 next;
		पूर्णांक i, len = 0;

		ret = pci_पढ़ो_config_byte(pdev, pos, &cap);
		अगर (ret)
			वापस ret;

		ret = pci_पढ़ो_config_byte(pdev,
					   pos + PCI_CAP_LIST_NEXT, &next);
		अगर (ret)
			वापस ret;

		/*
		 * ID 0 is a शून्य capability, conflicting with our fake
		 * PCI_CAP_ID_BASIC.  As it has no content, consider it
		 * hidden क्रम now.
		 */
		अगर (cap && cap <= PCI_CAP_ID_MAX) अणु
			len = pci_cap_length[cap];
			अगर (len == 0xFF) अणु /* Variable length */
				len = vfio_cap_len(vdev, cap, pos);
				अगर (len < 0)
					वापस len;
			पूर्ण
		पूर्ण

		अगर (!len) अणु
			pci_info(pdev, "%s: hiding cap %#x@%#x\n", __func__,
				 cap, pos);
			*prev = next;
			pos = next;
			जारी;
		पूर्ण

		/* Sanity check, करो we overlap other capabilities? */
		क्रम (i = 0; i < len; i++) अणु
			अगर (likely(map[pos + i] == PCI_CAP_ID_INVALID))
				जारी;

			pci_warn(pdev, "%s: PCI config conflict @%#x, was cap %#x now cap %#x\n",
				 __func__, pos + i, map[pos + i], cap);
		पूर्ण

		BUILD_BUG_ON(PCI_CAP_ID_MAX >= PCI_CAP_ID_INVALID_VIRT);

		स_रखो(map + pos, cap, len);
		ret = vfio_fill_vconfig_bytes(vdev, pos, len);
		अगर (ret)
			वापस ret;

		prev = &vdev->vconfig[pos + PCI_CAP_LIST_NEXT];
		pos = next;
		caps++;
	पूर्ण

	/* If we didn't fill any capabilities, clear the status flag */
	अगर (!caps) अणु
		__le16 *vstatus = (__le16 *)&vdev->vconfig[PCI_STATUS];
		*vstatus &= ~cpu_to_le16(PCI_STATUS_CAP_LIST);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_ecap_init(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	u8 *map = vdev->pci_config_map;
	u16 epos;
	__le32 *prev = शून्य;
	पूर्णांक loops, ret, ecaps = 0;

	अगर (!vdev->extended_caps)
		वापस 0;

	epos = PCI_CFG_SPACE_SIZE;

	loops = (pdev->cfg_size - PCI_CFG_SPACE_SIZE) / PCI_CAP_SIZखातापूर्ण;

	जबतक (loops-- && epos >= PCI_CFG_SPACE_SIZE) अणु
		u32 header;
		u16 ecap;
		पूर्णांक i, len = 0;
		bool hidden = false;

		ret = pci_पढ़ो_config_dword(pdev, epos, &header);
		अगर (ret)
			वापस ret;

		ecap = PCI_EXT_CAP_ID(header);

		अगर (ecap <= PCI_EXT_CAP_ID_MAX) अणु
			len = pci_ext_cap_length[ecap];
			अगर (len == 0xFF) अणु
				len = vfio_ext_cap_len(vdev, ecap, epos);
				अगर (len < 0)
					वापस len;
			पूर्ण
		पूर्ण

		अगर (!len) अणु
			pci_info(pdev, "%s: hiding ecap %#x@%#x\n",
				 __func__, ecap, epos);

			/* If not the first in the chain, we can skip over it */
			अगर (prev) अणु
				u32 val = epos = PCI_EXT_CAP_NEXT(header);
				*prev &= cpu_to_le32(~(0xffcU << 20));
				*prev |= cpu_to_le32(val << 20);
				जारी;
			पूर्ण

			/*
			 * Otherwise, fill in a placeholder, the direct
			 * पढ़ोfn will भवize this स्वतःmatically
			 */
			len = PCI_CAP_SIZखातापूर्ण;
			hidden = true;
		पूर्ण

		क्रम (i = 0; i < len; i++) अणु
			अगर (likely(map[epos + i] == PCI_CAP_ID_INVALID))
				जारी;

			pci_warn(pdev, "%s: PCI config conflict @%#x, was ecap %#x now ecap %#x\n",
				 __func__, epos + i, map[epos + i], ecap);
		पूर्ण

		/*
		 * Even though ecap is 2 bytes, we're currently a दीर्घ way
		 * from exceeding 1 byte capabilities.  If we ever make it
		 * up to 0xFE we'll need to up this to a two-byte, byte map.
		 */
		BUILD_BUG_ON(PCI_EXT_CAP_ID_MAX >= PCI_CAP_ID_INVALID_VIRT);

		स_रखो(map + epos, ecap, len);
		ret = vfio_fill_vconfig_bytes(vdev, epos, len);
		अगर (ret)
			वापस ret;

		/*
		 * If we're just using this capability to anchor the list,
		 * hide the real ID.  Only count real ecaps.  XXX PCI spec
		 * indicates to use cap id = 0, version = 0, next = 0 अगर
		 * ecaps are असलent, hope users check all the way to next.
		 */
		अगर (hidden)
			*(__le32 *)&vdev->vconfig[epos] &=
				cpu_to_le32((0xffcU << 20));
		अन्यथा
			ecaps++;

		prev = (__le32 *)&vdev->vconfig[epos];
		epos = PCI_EXT_CAP_NEXT(header);
	पूर्ण

	अगर (!ecaps)
		*(u32 *)&vdev->vconfig[PCI_CFG_SPACE_SIZE] = 0;

	वापस 0;
पूर्ण

/*
 * Nag about hardware bugs, hopefully to have venकरोrs fix them, but at least
 * to collect a list of dependencies क्रम the VF INTx pin quirk below.
 */
अटल स्थिर काष्ठा pci_device_id known_bogus_vf_पूर्णांकx_pin[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x270c) पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * For each device we allocate a pci_config_map that indicates the
 * capability occupying each dword and thus the काष्ठा perm_bits we
 * use क्रम पढ़ो and ग_लिखो.  We also allocate a भवized config
 * space which tracks पढ़ोs and ग_लिखोs to bits that we emulate क्रम
 * the user.  Initial values filled from device.
 *
 * Using shared काष्ठा perm_bits between all vfio-pci devices saves
 * us from allocating cfg_size buffers क्रम virt and ग_लिखो क्रम every
 * device.  We could हटाओ vconfig and allocate inभागidual buffers
 * क्रम each area requiring emulated bits, but the array of poपूर्णांकers
 * would be comparable in size (at least क्रम standard config space).
 */
पूर्णांक vfio_config_init(काष्ठा vfio_pci_device *vdev)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	u8 *map, *vconfig;
	पूर्णांक ret;

	/*
	 * Config space, caps and ecaps are all dword aligned, so we could
	 * use one byte per dword to record the type.  However, there are
	 * no requiremenst on the length of a capability, so the gap between
	 * capabilities needs byte granularity.
	 */
	map = kदो_स्मृति(pdev->cfg_size, GFP_KERNEL);
	अगर (!map)
		वापस -ENOMEM;

	vconfig = kदो_स्मृति(pdev->cfg_size, GFP_KERNEL);
	अगर (!vconfig) अणु
		kमुक्त(map);
		वापस -ENOMEM;
	पूर्ण

	vdev->pci_config_map = map;
	vdev->vconfig = vconfig;

	स_रखो(map, PCI_CAP_ID_BASIC, PCI_STD_HEADER_SIZखातापूर्ण);
	स_रखो(map + PCI_STD_HEADER_SIZखातापूर्ण, PCI_CAP_ID_INVALID,
	       pdev->cfg_size - PCI_STD_HEADER_SIZखातापूर्ण);

	ret = vfio_fill_vconfig_bytes(vdev, 0, PCI_STD_HEADER_SIZखातापूर्ण);
	अगर (ret)
		जाओ out;

	vdev->bardirty = true;

	/*
	 * XXX can we just pci_load_saved_state/pci_restore_state?
	 * may need to rebuild vconfig after that
	 */

	/* For restore after reset */
	vdev->rbar[0] = le32_to_cpu(*(__le32 *)&vconfig[PCI_BASE_ADDRESS_0]);
	vdev->rbar[1] = le32_to_cpu(*(__le32 *)&vconfig[PCI_BASE_ADDRESS_1]);
	vdev->rbar[2] = le32_to_cpu(*(__le32 *)&vconfig[PCI_BASE_ADDRESS_2]);
	vdev->rbar[3] = le32_to_cpu(*(__le32 *)&vconfig[PCI_BASE_ADDRESS_3]);
	vdev->rbar[4] = le32_to_cpu(*(__le32 *)&vconfig[PCI_BASE_ADDRESS_4]);
	vdev->rbar[5] = le32_to_cpu(*(__le32 *)&vconfig[PCI_BASE_ADDRESS_5]);
	vdev->rbar[6] = le32_to_cpu(*(__le32 *)&vconfig[PCI_ROM_ADDRESS]);

	अगर (pdev->is_virtfn) अणु
		*(__le16 *)&vconfig[PCI_VENDOR_ID] = cpu_to_le16(pdev->venकरोr);
		*(__le16 *)&vconfig[PCI_DEVICE_ID] = cpu_to_le16(pdev->device);

		/*
		 * Per SR-IOV spec rev 1.1, 3.4.1.18 the पूर्णांकerrupt pin रेजिस्टर
		 * करोes not apply to VFs and VFs must implement this रेजिस्टर
		 * as पढ़ो-only with value zero.  Userspace is not पढ़ोily able
		 * to identअगरy whether a device is a VF and thus that the pin
		 * definition on the device is bogus should it violate this
		 * requirement.  We alपढ़ोy भवize the pin रेजिस्टर क्रम
		 * other purposes, so we simply need to replace the bogus value
		 * and consider VFs when we determine INTx IRQ count.
		 */
		अगर (vconfig[PCI_INTERRUPT_PIN] &&
		    !pci_match_id(known_bogus_vf_पूर्णांकx_pin, pdev))
			pci_warn(pdev,
				 "Hardware bug: VF reports bogus INTx pin %d\n",
				 vconfig[PCI_INTERRUPT_PIN]);

		vconfig[PCI_INTERRUPT_PIN] = 0; /* Gratuitous क्रम good VFs */
	पूर्ण
	अगर (pdev->no_command_memory) अणु
		/*
		 * VFs and devices that set pdev->no_command_memory करो not
		 * implement the memory enable bit of the COMMAND रेजिस्टर
		 * thereक्रमe we'll not have it set in our initial copy of
		 * config space after pci_enable_device().  For consistency
		 * with PFs, set the भव enable bit here.
		 */
		*(__le16 *)&vconfig[PCI_COMMAND] |=
					cpu_to_le16(PCI_COMMAND_MEMORY);
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_VFIO_PCI_INTX) || vdev->noपूर्णांकx)
		vconfig[PCI_INTERRUPT_PIN] = 0;

	ret = vfio_cap_init(vdev);
	अगर (ret)
		जाओ out;

	ret = vfio_ecap_init(vdev);
	अगर (ret)
		जाओ out;

	वापस 0;

out:
	kमुक्त(map);
	vdev->pci_config_map = शून्य;
	kमुक्त(vconfig);
	vdev->vconfig = शून्य;
	वापस pcibios_err_to_त्रुटि_सं(ret);
पूर्ण

व्योम vfio_config_मुक्त(काष्ठा vfio_pci_device *vdev)
अणु
	kमुक्त(vdev->vconfig);
	vdev->vconfig = शून्य;
	kमुक्त(vdev->pci_config_map);
	vdev->pci_config_map = शून्य;
	अगर (vdev->msi_perm) अणु
		मुक्त_perm_bits(vdev->msi_perm);
		kमुक्त(vdev->msi_perm);
		vdev->msi_perm = शून्य;
	पूर्ण
पूर्ण

/*
 * Find the reमुख्यing number of bytes in a dword that match the given
 * position.  Stop at either the end of the capability or the dword boundary.
 */
अटल माप_प्रकार vfio_pci_cap_reमुख्यing_dword(काष्ठा vfio_pci_device *vdev,
					   loff_t pos)
अणु
	u8 cap = vdev->pci_config_map[pos];
	माप_प्रकार i;

	क्रम (i = 1; (pos + i) % 4 && vdev->pci_config_map[pos + i] == cap; i++)
		/* nop */;

	वापस i;
पूर्ण

अटल sमाप_प्रकार vfio_config_करो_rw(काष्ठा vfio_pci_device *vdev, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos, bool isग_लिखो)
अणु
	काष्ठा pci_dev *pdev = vdev->pdev;
	काष्ठा perm_bits *perm;
	__le32 val = 0;
	पूर्णांक cap_start = 0, offset;
	u8 cap_id;
	sमाप_प्रकार ret;

	अगर (*ppos < 0 || *ppos >= pdev->cfg_size ||
	    *ppos + count > pdev->cfg_size)
		वापस -EFAULT;

	/*
	 * Chop accesses पूर्णांकo aligned chunks containing no more than a
	 * single capability.  Caller increments to the next chunk.
	 */
	count = min(count, vfio_pci_cap_reमुख्यing_dword(vdev, *ppos));
	अगर (count >= 4 && !(*ppos % 4))
		count = 4;
	अन्यथा अगर (count >= 2 && !(*ppos % 2))
		count = 2;
	अन्यथा
		count = 1;

	ret = count;

	cap_id = vdev->pci_config_map[*ppos];

	अगर (cap_id == PCI_CAP_ID_INVALID) अणु
		perm = &unasचिन्हित_perms;
		cap_start = *ppos;
	पूर्ण अन्यथा अगर (cap_id == PCI_CAP_ID_INVALID_VIRT) अणु
		perm = &virt_perms;
		cap_start = *ppos;
	पूर्ण अन्यथा अणु
		अगर (*ppos >= PCI_CFG_SPACE_SIZE) अणु
			WARN_ON(cap_id > PCI_EXT_CAP_ID_MAX);

			perm = &ecap_perms[cap_id];
			cap_start = vfio_find_cap_start(vdev, *ppos);
		पूर्ण अन्यथा अणु
			WARN_ON(cap_id > PCI_CAP_ID_MAX);

			perm = &cap_perms[cap_id];

			अगर (cap_id == PCI_CAP_ID_MSI)
				perm = vdev->msi_perm;

			अगर (cap_id > PCI_CAP_ID_BASIC)
				cap_start = vfio_find_cap_start(vdev, *ppos);
		पूर्ण
	पूर्ण

	WARN_ON(!cap_start && cap_id != PCI_CAP_ID_BASIC);
	WARN_ON(cap_start > *ppos);

	offset = *ppos - cap_start;

	अगर (isग_लिखो) अणु
		अगर (!perm->ग_लिखोfn)
			वापस ret;

		अगर (copy_from_user(&val, buf, count))
			वापस -EFAULT;

		ret = perm->ग_लिखोfn(vdev, *ppos, count, perm, offset, val);
	पूर्ण अन्यथा अणु
		अगर (perm->पढ़ोfn) अणु
			ret = perm->पढ़ोfn(vdev, *ppos, count,
					   perm, offset, &val);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		अगर (copy_to_user(buf, &val, count))
			वापस -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

sमाप_प्रकार vfio_pci_config_rw(काष्ठा vfio_pci_device *vdev, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos, bool isग_लिखो)
अणु
	माप_प्रकार करोne = 0;
	पूर्णांक ret = 0;
	loff_t pos = *ppos;

	pos &= VFIO_PCI_OFFSET_MASK;

	जबतक (count) अणु
		ret = vfio_config_करो_rw(vdev, buf, count, &pos, isग_लिखो);
		अगर (ret < 0)
			वापस ret;

		count -= ret;
		करोne += ret;
		buf += ret;
		pos += ret;
	पूर्ण

	*ppos += करोne;

	वापस करोne;
पूर्ण
