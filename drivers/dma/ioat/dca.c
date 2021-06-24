<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel I/OAT DMA Linux driver
 * Copyright(c) 2007 - 2009 Intel Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dca.h>

/* either a kernel change is needed, or we need something like this in kernel */
#अगर_अघोषित CONFIG_SMP
#समावेश <यंत्र/smp.h>
#अघोषित cpu_physical_id
#घोषणा cpu_physical_id(cpu) (cpuid_ebx(1) >> 24)
#पूर्ण_अगर

#समावेश "dma.h"
#समावेश "registers.h"

/*
 * Bit 7 of a tag map entry is the "valid" bit, अगर it is set then bits 0:6
 * contain the bit number of the APIC ID to map पूर्णांकo the DCA tag.  If the valid
 * bit is not set, then the value must be 0 or 1 and defines the bit in the tag.
 */
#घोषणा DCA_TAG_MAP_VALID 0x80

#घोषणा DCA3_TAG_MAP_BIT_TO_INV 0x80
#घोषणा DCA3_TAG_MAP_BIT_TO_SEL 0x40
#घोषणा DCA3_TAG_MAP_LITERAL_VAL 0x1

#घोषणा DCA_TAG_MAP_MASK 0xDF

/* expected tag map bytes क्रम I/OAT ver.2 */
#घोषणा DCA2_TAG_MAP_BYTE0 0x80
#घोषणा DCA2_TAG_MAP_BYTE1 0x0
#घोषणा DCA2_TAG_MAP_BYTE2 0x81
#घोषणा DCA2_TAG_MAP_BYTE3 0x82
#घोषणा DCA2_TAG_MAP_BYTE4 0x82

/*
 * "Legacy" DCA प्रणालीs करो not implement the DCA रेजिस्टर set in the
 * I/OAT device.  Software needs direct support क्रम their tag mappings.
 */

#घोषणा APICID_BIT(x)		(DCA_TAG_MAP_VALID | (x))
#घोषणा IOAT_TAG_MAP_LEN	8

/* pack PCI B/D/F पूर्णांकo a u16 */
अटल अंतरभूत u16 dcaid_from_pcidev(काष्ठा pci_dev *pci)
अणु
	वापस (pci->bus->number << 8) | pci->devfn;
पूर्ण

अटल पूर्णांक dca_enabled_in_bios(काष्ठा pci_dev *pdev)
अणु
	/* CPUID level 9 वापसs DCA configuration */
	/* Bit 0 indicates DCA enabled by the BIOS */
	अचिन्हित दीर्घ cpuid_level_9;
	पूर्णांक res;

	cpuid_level_9 = cpuid_eax(9);
	res = test_bit(0, &cpuid_level_9);
	अगर (!res)
		dev_dbg(&pdev->dev, "DCA is disabled in BIOS\n");

	वापस res;
पूर्ण

पूर्णांक प्रणाली_has_dca_enabled(काष्ठा pci_dev *pdev)
अणु
	अगर (boot_cpu_has(X86_FEATURE_DCA))
		वापस dca_enabled_in_bios(pdev);

	dev_dbg(&pdev->dev, "boot cpu doesn't have X86_FEATURE_DCA\n");
	वापस 0;
पूर्ण

काष्ठा ioat_dca_slot अणु
	काष्ठा pci_dev *pdev;	/* requester device */
	u16 rid;		/* requester id, as used by IOAT */
पूर्ण;

#घोषणा IOAT_DCA_MAX_REQ 6
#घोषणा IOAT3_DCA_MAX_REQ 2

काष्ठा ioat_dca_priv अणु
	व्योम __iomem		*iobase;
	व्योम __iomem		*dca_base;
	पूर्णांक			 max_requesters;
	पूर्णांक			 requester_count;
	u8			 tag_map[IOAT_TAG_MAP_LEN];
	काष्ठा ioat_dca_slot	 req_slots[];
पूर्ण;

अटल पूर्णांक ioat_dca_dev_managed(काष्ठा dca_provider *dca,
				काष्ठा device *dev)
अणु
	काष्ठा ioat_dca_priv *ioatdca = dca_priv(dca);
	काष्ठा pci_dev *pdev;
	पूर्णांक i;

	pdev = to_pci_dev(dev);
	क्रम (i = 0; i < ioatdca->max_requesters; i++) अणु
		अगर (ioatdca->req_slots[i].pdev == pdev)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ioat_dca_add_requester(काष्ठा dca_provider *dca, काष्ठा device *dev)
अणु
	काष्ठा ioat_dca_priv *ioatdca = dca_priv(dca);
	काष्ठा pci_dev *pdev;
	पूर्णांक i;
	u16 id;
	u16 global_req_table;

	/* This implementation only supports PCI-Express */
	अगर (!dev_is_pci(dev))
		वापस -ENODEV;
	pdev = to_pci_dev(dev);
	id = dcaid_from_pcidev(pdev);

	अगर (ioatdca->requester_count == ioatdca->max_requesters)
		वापस -ENODEV;

	क्रम (i = 0; i < ioatdca->max_requesters; i++) अणु
		अगर (ioatdca->req_slots[i].pdev == शून्य) अणु
			/* found an empty slot */
			ioatdca->requester_count++;
			ioatdca->req_slots[i].pdev = pdev;
			ioatdca->req_slots[i].rid = id;
			global_req_table =
			      पढ़ोw(ioatdca->dca_base + IOAT3_DCA_GREQID_OFFSET);
			ग_लिखोl(id | IOAT_DCA_GREQID_VALID,
			       ioatdca->iobase + global_req_table + (i * 4));
			वापस i;
		पूर्ण
	पूर्ण
	/* Error, ioatdma->requester_count is out of whack */
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक ioat_dca_हटाओ_requester(काष्ठा dca_provider *dca,
				      काष्ठा device *dev)
अणु
	काष्ठा ioat_dca_priv *ioatdca = dca_priv(dca);
	काष्ठा pci_dev *pdev;
	पूर्णांक i;
	u16 global_req_table;

	/* This implementation only supports PCI-Express */
	अगर (!dev_is_pci(dev))
		वापस -ENODEV;
	pdev = to_pci_dev(dev);

	क्रम (i = 0; i < ioatdca->max_requesters; i++) अणु
		अगर (ioatdca->req_slots[i].pdev == pdev) अणु
			global_req_table =
			      पढ़ोw(ioatdca->dca_base + IOAT3_DCA_GREQID_OFFSET);
			ग_लिखोl(0, ioatdca->iobase + global_req_table + (i * 4));
			ioatdca->req_slots[i].pdev = शून्य;
			ioatdca->req_slots[i].rid = 0;
			ioatdca->requester_count--;
			वापस i;
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल u8 ioat_dca_get_tag(काष्ठा dca_provider *dca,
			    काष्ठा device *dev,
			    पूर्णांक cpu)
अणु
	u8 tag;

	काष्ठा ioat_dca_priv *ioatdca = dca_priv(dca);
	पूर्णांक i, apic_id, bit, value;
	u8 entry;

	tag = 0;
	apic_id = cpu_physical_id(cpu);

	क्रम (i = 0; i < IOAT_TAG_MAP_LEN; i++) अणु
		entry = ioatdca->tag_map[i];
		अगर (entry & DCA3_TAG_MAP_BIT_TO_SEL) अणु
			bit = entry &
				~(DCA3_TAG_MAP_BIT_TO_SEL | DCA3_TAG_MAP_BIT_TO_INV);
			value = (apic_id & (1 << bit)) ? 1 : 0;
		पूर्ण अन्यथा अगर (entry & DCA3_TAG_MAP_BIT_TO_INV) अणु
			bit = entry & ~DCA3_TAG_MAP_BIT_TO_INV;
			value = (apic_id & (1 << bit)) ? 0 : 1;
		पूर्ण अन्यथा अणु
			value = (entry & DCA3_TAG_MAP_LITERAL_VAL) ? 1 : 0;
		पूर्ण
		tag |= (value << i);
	पूर्ण

	वापस tag;
पूर्ण

अटल स्थिर काष्ठा dca_ops ioat_dca_ops = अणु
	.add_requester		= ioat_dca_add_requester,
	.हटाओ_requester	= ioat_dca_हटाओ_requester,
	.get_tag		= ioat_dca_get_tag,
	.dev_managed		= ioat_dca_dev_managed,
पूर्ण;

अटल पूर्णांक ioat_dca_count_dca_slots(व्योम *iobase, u16 dca_offset)
अणु
	पूर्णांक slots = 0;
	u32 req;
	u16 global_req_table;

	global_req_table = पढ़ोw(iobase + dca_offset + IOAT3_DCA_GREQID_OFFSET);
	अगर (global_req_table == 0)
		वापस 0;

	करो अणु
		req = पढ़ोl(iobase + global_req_table + (slots * माप(u32)));
		slots++;
	पूर्ण जबतक ((req & IOAT_DCA_GREQID_LASTID) == 0);

	वापस slots;
पूर्ण

अटल अंतरभूत पूर्णांक dca3_tag_map_invalid(u8 *tag_map)
अणु
	/*
	 * If the tag map is not programmed by the BIOS the शेष is:
	 * 0x80 0x80 0x80 0x80 0x80 0x00 0x00 0x00
	 *
	 * This an invalid map and will result in only 2 possible tags
	 * 0x1F and 0x00.  0x00 is an invalid DCA tag so we know that
	 * this entire definition is invalid.
	 */
	वापस ((tag_map[0] == DCA_TAG_MAP_VALID) &&
		(tag_map[1] == DCA_TAG_MAP_VALID) &&
		(tag_map[2] == DCA_TAG_MAP_VALID) &&
		(tag_map[3] == DCA_TAG_MAP_VALID) &&
		(tag_map[4] == DCA_TAG_MAP_VALID));
पूर्ण

काष्ठा dca_provider *ioat_dca_init(काष्ठा pci_dev *pdev, व्योम __iomem *iobase)
अणु
	काष्ठा dca_provider *dca;
	काष्ठा ioat_dca_priv *ioatdca;
	पूर्णांक slots;
	पूर्णांक i;
	पूर्णांक err;
	u16 dca_offset;
	u16 csi_fsb_control;
	u16 pcie_control;
	u8 bit;

	जोड़ अणु
		u64 full;
		काष्ठा अणु
			u32 low;
			u32 high;
		पूर्ण;
	पूर्ण tag_map;

	अगर (!प्रणाली_has_dca_enabled(pdev))
		वापस शून्य;

	dca_offset = पढ़ोw(iobase + IOAT_DCAOFFSET_OFFSET);
	अगर (dca_offset == 0)
		वापस शून्य;

	slots = ioat_dca_count_dca_slots(iobase, dca_offset);
	अगर (slots == 0)
		वापस शून्य;

	dca = alloc_dca_provider(&ioat_dca_ops,
				 काष्ठा_size(ioatdca, req_slots, slots));
	अगर (!dca)
		वापस शून्य;

	ioatdca = dca_priv(dca);
	ioatdca->iobase = iobase;
	ioatdca->dca_base = iobase + dca_offset;
	ioatdca->max_requesters = slots;

	/* some bios might not know to turn these on */
	csi_fsb_control = पढ़ोw(ioatdca->dca_base + IOAT3_CSI_CONTROL_OFFSET);
	अगर ((csi_fsb_control & IOAT3_CSI_CONTROL_PREFETCH) == 0) अणु
		csi_fsb_control |= IOAT3_CSI_CONTROL_PREFETCH;
		ग_लिखोw(csi_fsb_control,
		       ioatdca->dca_base + IOAT3_CSI_CONTROL_OFFSET);
	पूर्ण
	pcie_control = पढ़ोw(ioatdca->dca_base + IOAT3_PCI_CONTROL_OFFSET);
	अगर ((pcie_control & IOAT3_PCI_CONTROL_MEMWR) == 0) अणु
		pcie_control |= IOAT3_PCI_CONTROL_MEMWR;
		ग_लिखोw(pcie_control,
		       ioatdca->dca_base + IOAT3_PCI_CONTROL_OFFSET);
	पूर्ण


	/* TODO version, compatibility and configuration checks */

	/* copy out the APIC to DCA tag map */
	tag_map.low =
		पढ़ोl(ioatdca->dca_base + IOAT3_APICID_TAG_MAP_OFFSET_LOW);
	tag_map.high =
		पढ़ोl(ioatdca->dca_base + IOAT3_APICID_TAG_MAP_OFFSET_HIGH);
	क्रम (i = 0; i < 8; i++) अणु
		bit = tag_map.full >> (8 * i);
		ioatdca->tag_map[i] = bit & DCA_TAG_MAP_MASK;
	पूर्ण

	अगर (dca3_tag_map_invalid(ioatdca->tag_map)) अणु
		add_taपूर्णांक(TAINT_FIRMWARE_WORKAROUND, LOCKDEP_STILL_OK);
		pr_warn_once("%s %s: APICID_TAG_MAP set incorrectly by BIOS, disabling DCA\n",
			     dev_driver_string(&pdev->dev),
			     dev_name(&pdev->dev));
		मुक्त_dca_provider(dca);
		वापस शून्य;
	पूर्ण

	err = रेजिस्टर_dca_provider(dca, &pdev->dev);
	अगर (err) अणु
		मुक्त_dca_provider(dca);
		वापस शून्य;
	पूर्ण

	वापस dca;
पूर्ण
