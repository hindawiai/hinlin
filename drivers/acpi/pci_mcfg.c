<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Broadcom
 *	Author: Jayachandran C <jchandra@broadcom.com>
 * Copyright (C) 2016 Semihalf
 * 	Author: Tomasz Nowicki <tn@semihalf.com>
 */

#घोषणा pr_fmt(fmt) "ACPI: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/pci-ecam.h>

/* Structure to hold entries from the MCFG table */
काष्ठा mcfg_entry अणु
	काष्ठा list_head	list;
	phys_addr_t		addr;
	u16			segment;
	u8			bus_start;
	u8			bus_end;
पूर्ण;

#अगर_घोषित CONFIG_PCI_QUIRKS
काष्ठा mcfg_fixup अणु
	अक्षर oem_id[ACPI_OEM_ID_SIZE + 1];
	अक्षर oem_table_id[ACPI_OEM_TABLE_ID_SIZE + 1];
	u32 oem_revision;
	u16 segment;
	काष्ठा resource bus_range;
	स्थिर काष्ठा pci_ecam_ops *ops;
	काष्ठा resource cfgres;
पूर्ण;

#घोषणा MCFG_BUS_RANGE(start, end)	DEFINE_RES_NAMED((start),	\
						((end) - (start) + 1),	\
						शून्य, IORESOURCE_BUS)
#घोषणा MCFG_BUS_ANY			MCFG_BUS_RANGE(0x0, 0xff)

अटल काष्ठा mcfg_fixup mcfg_quirks[] = अणु
/*	अणु OEM_ID, OEM_TABLE_ID, REV, SEGMENT, BUS_RANGE, ops, cfgres पूर्ण, */

#घोषणा AL_ECAM(table_id, rev, seg, ops) \
	अणु "AMAZON", table_id, rev, seg, MCFG_BUS_ANY, ops पूर्ण

	AL_ECAM("GRAVITON", 0, 0, &al_pcie_ops),
	AL_ECAM("GRAVITON", 0, 1, &al_pcie_ops),
	AL_ECAM("GRAVITON", 0, 2, &al_pcie_ops),
	AL_ECAM("GRAVITON", 0, 3, &al_pcie_ops),
	AL_ECAM("GRAVITON", 0, 4, &al_pcie_ops),
	AL_ECAM("GRAVITON", 0, 5, &al_pcie_ops),
	AL_ECAM("GRAVITON", 0, 6, &al_pcie_ops),
	AL_ECAM("GRAVITON", 0, 7, &al_pcie_ops),

#घोषणा QCOM_ECAM32(seg) \
	अणु "QCOM  ", "QDF2432 ", 1, seg, MCFG_BUS_ANY, &pci_32b_ops पूर्ण

	QCOM_ECAM32(0),
	QCOM_ECAM32(1),
	QCOM_ECAM32(2),
	QCOM_ECAM32(3),
	QCOM_ECAM32(4),
	QCOM_ECAM32(5),
	QCOM_ECAM32(6),
	QCOM_ECAM32(7),

#घोषणा HISI_QUAD_DOM(table_id, seg, ops) \
	अणु "HISI  ", table_id, 0, (seg) + 0, MCFG_BUS_ANY, ops पूर्ण, \
	अणु "HISI  ", table_id, 0, (seg) + 1, MCFG_BUS_ANY, ops पूर्ण, \
	अणु "HISI  ", table_id, 0, (seg) + 2, MCFG_BUS_ANY, ops पूर्ण, \
	अणु "HISI  ", table_id, 0, (seg) + 3, MCFG_BUS_ANY, ops पूर्ण

	HISI_QUAD_DOM("HIP05   ",  0, &hisi_pcie_ops),
	HISI_QUAD_DOM("HIP06   ",  0, &hisi_pcie_ops),
	HISI_QUAD_DOM("HIP07   ",  0, &hisi_pcie_ops),
	HISI_QUAD_DOM("HIP07   ",  4, &hisi_pcie_ops),
	HISI_QUAD_DOM("HIP07   ",  8, &hisi_pcie_ops),
	HISI_QUAD_DOM("HIP07   ", 12, &hisi_pcie_ops),

#घोषणा THUNDER_PEM_RES(addr, node) \
	DEFINE_RES_MEM((addr) + ((u64) (node) << 44), 0x39 * SZ_16M)

#घोषणा THUNDER_PEM_QUIRK(rev, node) \
	अणु "CAVIUM", "THUNDERX", rev, 4 + (10 * (node)), MCFG_BUS_ANY,	    \
	  &thunder_pem_ecam_ops, THUNDER_PEM_RES(0x88001f000000UL, node) पूर्ण,  \
	अणु "CAVIUM", "THUNDERX", rev, 5 + (10 * (node)), MCFG_BUS_ANY,	    \
	  &thunder_pem_ecam_ops, THUNDER_PEM_RES(0x884057000000UL, node) पूर्ण,  \
	अणु "CAVIUM", "THUNDERX", rev, 6 + (10 * (node)), MCFG_BUS_ANY,	    \
	  &thunder_pem_ecam_ops, THUNDER_PEM_RES(0x88808f000000UL, node) पूर्ण,  \
	अणु "CAVIUM", "THUNDERX", rev, 7 + (10 * (node)), MCFG_BUS_ANY,	    \
	  &thunder_pem_ecam_ops, THUNDER_PEM_RES(0x89001f000000UL, node) पूर्ण,  \
	अणु "CAVIUM", "THUNDERX", rev, 8 + (10 * (node)), MCFG_BUS_ANY,	    \
	  &thunder_pem_ecam_ops, THUNDER_PEM_RES(0x894057000000UL, node) पूर्ण,  \
	अणु "CAVIUM", "THUNDERX", rev, 9 + (10 * (node)), MCFG_BUS_ANY,	    \
	  &thunder_pem_ecam_ops, THUNDER_PEM_RES(0x89808f000000UL, node) पूर्ण

#घोषणा THUNDER_ECAM_QUIRK(rev, seg)					\
	अणु "CAVIUM", "THUNDERX", rev, seg, MCFG_BUS_ANY,			\
	&pci_thunder_ecam_ops पूर्ण

	/* SoC pass2.x */
	THUNDER_PEM_QUIRK(1, 0),
	THUNDER_PEM_QUIRK(1, 1),
	THUNDER_ECAM_QUIRK(1, 10),

	/* SoC pass1.x */
	THUNDER_PEM_QUIRK(2, 0),	/* off-chip devices */
	THUNDER_PEM_QUIRK(2, 1),	/* off-chip devices */
	THUNDER_ECAM_QUIRK(2,  0),
	THUNDER_ECAM_QUIRK(2,  1),
	THUNDER_ECAM_QUIRK(2,  2),
	THUNDER_ECAM_QUIRK(2,  3),
	THUNDER_ECAM_QUIRK(2, 10),
	THUNDER_ECAM_QUIRK(2, 11),
	THUNDER_ECAM_QUIRK(2, 12),
	THUNDER_ECAM_QUIRK(2, 13),

	अणु "NVIDIA", "TEGRA194", 1, 0, MCFG_BUS_ANY, &tegra194_pcie_opsपूर्ण,
	अणु "NVIDIA", "TEGRA194", 1, 1, MCFG_BUS_ANY, &tegra194_pcie_opsपूर्ण,
	अणु "NVIDIA", "TEGRA194", 1, 2, MCFG_BUS_ANY, &tegra194_pcie_opsपूर्ण,
	अणु "NVIDIA", "TEGRA194", 1, 3, MCFG_BUS_ANY, &tegra194_pcie_opsपूर्ण,
	अणु "NVIDIA", "TEGRA194", 1, 4, MCFG_BUS_ANY, &tegra194_pcie_opsपूर्ण,
	अणु "NVIDIA", "TEGRA194", 1, 5, MCFG_BUS_ANY, &tegra194_pcie_opsपूर्ण,

#घोषणा XGENE_V1_ECAM_MCFG(rev, seg) \
	अणु"APM   ", "XGENE   ", rev, seg, MCFG_BUS_ANY, \
		&xgene_v1_pcie_ecam_ops पूर्ण

#घोषणा XGENE_V2_ECAM_MCFG(rev, seg) \
	अणु"APM   ", "XGENE   ", rev, seg, MCFG_BUS_ANY, \
		&xgene_v2_pcie_ecam_ops पूर्ण

	/* X-Gene SoC with v1 PCIe controller */
	XGENE_V1_ECAM_MCFG(1, 0),
	XGENE_V1_ECAM_MCFG(1, 1),
	XGENE_V1_ECAM_MCFG(1, 2),
	XGENE_V1_ECAM_MCFG(1, 3),
	XGENE_V1_ECAM_MCFG(1, 4),
	XGENE_V1_ECAM_MCFG(2, 0),
	XGENE_V1_ECAM_MCFG(2, 1),
	XGENE_V1_ECAM_MCFG(2, 2),
	XGENE_V1_ECAM_MCFG(2, 3),
	XGENE_V1_ECAM_MCFG(2, 4),
	/* X-Gene SoC with v2.1 PCIe controller */
	XGENE_V2_ECAM_MCFG(3, 0),
	XGENE_V2_ECAM_MCFG(3, 1),
	/* X-Gene SoC with v2.2 PCIe controller */
	XGENE_V2_ECAM_MCFG(4, 0),
	XGENE_V2_ECAM_MCFG(4, 1),
	XGENE_V2_ECAM_MCFG(4, 2),

#घोषणा ALTRA_ECAM_QUIRK(rev, seg) \
	अणु "Ampere", "Altra   ", rev, seg, MCFG_BUS_ANY, &pci_32b_पढ़ो_ops पूर्ण

	ALTRA_ECAM_QUIRK(1, 0),
	ALTRA_ECAM_QUIRK(1, 1),
	ALTRA_ECAM_QUIRK(1, 2),
	ALTRA_ECAM_QUIRK(1, 3),
	ALTRA_ECAM_QUIRK(1, 4),
	ALTRA_ECAM_QUIRK(1, 5),
	ALTRA_ECAM_QUIRK(1, 6),
	ALTRA_ECAM_QUIRK(1, 7),
	ALTRA_ECAM_QUIRK(1, 8),
	ALTRA_ECAM_QUIRK(1, 9),
	ALTRA_ECAM_QUIRK(1, 10),
	ALTRA_ECAM_QUIRK(1, 11),
	ALTRA_ECAM_QUIRK(1, 12),
	ALTRA_ECAM_QUIRK(1, 13),
	ALTRA_ECAM_QUIRK(1, 14),
	ALTRA_ECAM_QUIRK(1, 15),
पूर्ण;

अटल अक्षर mcfg_oem_id[ACPI_OEM_ID_SIZE];
अटल अक्षर mcfg_oem_table_id[ACPI_OEM_TABLE_ID_SIZE];
अटल u32 mcfg_oem_revision;

अटल पूर्णांक pci_mcfg_quirk_matches(काष्ठा mcfg_fixup *f, u16 segment,
				  काष्ठा resource *bus_range)
अणु
	अगर (!स_भेद(f->oem_id, mcfg_oem_id, ACPI_OEM_ID_SIZE) &&
	    !स_भेद(f->oem_table_id, mcfg_oem_table_id,
		    ACPI_OEM_TABLE_ID_SIZE) &&
	    f->oem_revision == mcfg_oem_revision &&
	    f->segment == segment &&
	    resource_contains(&f->bus_range, bus_range))
		वापस 1;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम pci_mcfg_apply_quirks(काष्ठा acpi_pci_root *root,
				  काष्ठा resource *cfgres,
				  स्थिर काष्ठा pci_ecam_ops **ecam_ops)
अणु
#अगर_घोषित CONFIG_PCI_QUIRKS
	u16 segment = root->segment;
	काष्ठा resource *bus_range = &root->secondary;
	काष्ठा mcfg_fixup *f;
	पूर्णांक i;

	क्रम (i = 0, f = mcfg_quirks; i < ARRAY_SIZE(mcfg_quirks); i++, f++) अणु
		अगर (pci_mcfg_quirk_matches(f, segment, bus_range)) अणु
			अगर (f->cfgres.start)
				*cfgres = f->cfgres;
			अगर (f->ops)
				*ecam_ops =  f->ops;
			dev_info(&root->device->dev, "MCFG quirk: ECAM at %pR for %pR with %ps\n",
				 cfgres, bus_range, *ecam_ops);
			वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* List to save MCFG entries */
अटल LIST_HEAD(pci_mcfg_list);

पूर्णांक pci_mcfg_lookup(काष्ठा acpi_pci_root *root, काष्ठा resource *cfgres,
		    स्थिर काष्ठा pci_ecam_ops **ecam_ops)
अणु
	स्थिर काष्ठा pci_ecam_ops *ops = &pci_generic_ecam_ops;
	काष्ठा resource *bus_res = &root->secondary;
	u16 seg = root->segment;
	काष्ठा mcfg_entry *e;
	काष्ठा resource res;

	/* Use address from _CBA अगर present, otherwise lookup MCFG */
	अगर (root->mcfg_addr)
		जाओ skip_lookup;

	/*
	 * We expect the range in bus_res in the coverage of MCFG bus range.
	 */
	list_क्रम_each_entry(e, &pci_mcfg_list, list) अणु
		अगर (e->segment == seg && e->bus_start <= bus_res->start &&
		    e->bus_end >= bus_res->end) अणु
			root->mcfg_addr = e->addr;
		पूर्ण

	पूर्ण

skip_lookup:
	स_रखो(&res, 0, माप(res));
	अगर (root->mcfg_addr) अणु
		res.start = root->mcfg_addr + (bus_res->start << 20);
		res.end = res.start + (resource_size(bus_res) << 20) - 1;
		res.flags = IORESOURCE_MEM;
	पूर्ण

	/*
	 * Allow quirks to override शेष ECAM ops and CFG resource
	 * range.  This may even fabricate a CFG resource range in हाल
	 * MCFG करोes not have it.  Invalid CFG start address means MCFG
	 * firmware bug or we need another quirk in array.
	 */
	pci_mcfg_apply_quirks(root, &res, &ops);
	अगर (!res.start)
		वापस -ENXIO;

	*cfgres = res;
	*ecam_ops = ops;
	वापस 0;
पूर्ण

अटल __init पूर्णांक pci_mcfg_parse(काष्ठा acpi_table_header *header)
अणु
	काष्ठा acpi_table_mcfg *mcfg;
	काष्ठा acpi_mcfg_allocation *mptr;
	काष्ठा mcfg_entry *e, *arr;
	पूर्णांक i, n;

	अगर (header->length < माप(काष्ठा acpi_table_mcfg))
		वापस -EINVAL;

	n = (header->length - माप(काष्ठा acpi_table_mcfg)) /
					माप(काष्ठा acpi_mcfg_allocation);
	mcfg = (काष्ठा acpi_table_mcfg *)header;
	mptr = (काष्ठा acpi_mcfg_allocation *) &mcfg[1];

	arr = kसुस्मृति(n, माप(*arr), GFP_KERNEL);
	अगर (!arr)
		वापस -ENOMEM;

	क्रम (i = 0, e = arr; i < n; i++, mptr++, e++) अणु
		e->segment = mptr->pci_segment;
		e->addr =  mptr->address;
		e->bus_start = mptr->start_bus_number;
		e->bus_end = mptr->end_bus_number;
		list_add(&e->list, &pci_mcfg_list);
	पूर्ण

#अगर_घोषित CONFIG_PCI_QUIRKS
	/* Save MCFG IDs and revision क्रम quirks matching */
	स_नकल(mcfg_oem_id, header->oem_id, ACPI_OEM_ID_SIZE);
	स_नकल(mcfg_oem_table_id, header->oem_table_id, ACPI_OEM_TABLE_ID_SIZE);
	mcfg_oem_revision = header->oem_revision;
#पूर्ण_अगर

	pr_info("MCFG table detected, %d entries\n", n);
	वापस 0;
पूर्ण

/* Interface called by ACPI - parse and save MCFG table */
व्योम __init pci_mmcfg_late_init(व्योम)
अणु
	पूर्णांक err = acpi_table_parse(ACPI_SIG_MCFG, pci_mcfg_parse);
	अगर (err)
		pr_debug("Failed to parse MCFG (%d)\n", err);
पूर्ण
