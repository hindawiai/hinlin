<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 IBM Corp.
 */

#समावेश <linux/pci_regs.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>
#समावेश <linux/pci.h>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/msi_biपंचांगap.h>
#समावेश <यंत्र/pnv-pci.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/reg.h>

#समावेश "cxl.h"
#समावेश <misc/cxl.h>


#घोषणा CXL_PCI_VSEC_ID	0x1280
#घोषणा CXL_VSEC_MIN_SIZE 0x80

#घोषणा CXL_READ_VSEC_LENGTH(dev, vsec, dest)			\
	अणु							\
		pci_पढ़ो_config_word(dev, vsec + 0x6, dest);	\
		*dest >>= 4;					\
	पूर्ण
#घोषणा CXL_READ_VSEC_NAFUS(dev, vsec, dest) \
	pci_पढ़ो_config_byte(dev, vsec + 0x8, dest)

#घोषणा CXL_READ_VSEC_STATUS(dev, vsec, dest) \
	pci_पढ़ो_config_byte(dev, vsec + 0x9, dest)
#घोषणा CXL_STATUS_SECOND_PORT  0x80
#घोषणा CXL_STATUS_MSI_X_FULL   0x40
#घोषणा CXL_STATUS_MSI_X_SINGLE 0x20
#घोषणा CXL_STATUS_FLASH_RW     0x08
#घोषणा CXL_STATUS_FLASH_RO     0x04
#घोषणा CXL_STATUS_LOADABLE_AFU 0x02
#घोषणा CXL_STATUS_LOADABLE_PSL 0x01
/* If we see these features we won't try to use the card */
#घोषणा CXL_UNSUPPORTED_FEATURES \
	(CXL_STATUS_MSI_X_FULL | CXL_STATUS_MSI_X_SINGLE)

#घोषणा CXL_READ_VSEC_MODE_CONTROL(dev, vsec, dest) \
	pci_पढ़ो_config_byte(dev, vsec + 0xa, dest)
#घोषणा CXL_WRITE_VSEC_MODE_CONTROL(dev, vsec, val) \
	pci_ग_लिखो_config_byte(dev, vsec + 0xa, val)
#घोषणा CXL_VSEC_PROTOCOL_MASK   0xe0
#घोषणा CXL_VSEC_PROTOCOL_1024TB 0x80
#घोषणा CXL_VSEC_PROTOCOL_512TB  0x40
#घोषणा CXL_VSEC_PROTOCOL_256TB  0x20 /* Power 8/9 uses this */
#घोषणा CXL_VSEC_PROTOCOL_ENABLE 0x01

#घोषणा CXL_READ_VSEC_PSL_REVISION(dev, vsec, dest) \
	pci_पढ़ो_config_word(dev, vsec + 0xc, dest)
#घोषणा CXL_READ_VSEC_CAIA_MINOR(dev, vsec, dest) \
	pci_पढ़ो_config_byte(dev, vsec + 0xe, dest)
#घोषणा CXL_READ_VSEC_CAIA_MAJOR(dev, vsec, dest) \
	pci_पढ़ो_config_byte(dev, vsec + 0xf, dest)
#घोषणा CXL_READ_VSEC_BASE_IMAGE(dev, vsec, dest) \
	pci_पढ़ो_config_word(dev, vsec + 0x10, dest)

#घोषणा CXL_READ_VSEC_IMAGE_STATE(dev, vsec, dest) \
	pci_पढ़ो_config_byte(dev, vsec + 0x13, dest)
#घोषणा CXL_WRITE_VSEC_IMAGE_STATE(dev, vsec, val) \
	pci_ग_लिखो_config_byte(dev, vsec + 0x13, val)
#घोषणा CXL_VSEC_USER_IMAGE_LOADED 0x80 /* RO */
#घोषणा CXL_VSEC_PERST_LOADS_IMAGE 0x20 /* RW */
#घोषणा CXL_VSEC_PERST_SELECT_USER 0x10 /* RW */

#घोषणा CXL_READ_VSEC_AFU_DESC_OFF(dev, vsec, dest) \
	pci_पढ़ो_config_dword(dev, vsec + 0x20, dest)
#घोषणा CXL_READ_VSEC_AFU_DESC_SIZE(dev, vsec, dest) \
	pci_पढ़ो_config_dword(dev, vsec + 0x24, dest)
#घोषणा CXL_READ_VSEC_PS_OFF(dev, vsec, dest) \
	pci_पढ़ो_config_dword(dev, vsec + 0x28, dest)
#घोषणा CXL_READ_VSEC_PS_SIZE(dev, vsec, dest) \
	pci_पढ़ो_config_dword(dev, vsec + 0x2c, dest)


/* This works a little dअगरferent than the p1/p2 रेजिस्टर accesses to make it
 * easier to pull out inभागidual fields */
#घोषणा AFUD_READ(afu, off)		in_be64(afu->native->afu_desc_mmio + off)
#घोषणा AFUD_READ_LE(afu, off)		in_le64(afu->native->afu_desc_mmio + off)
#घोषणा EXTRACT_PPC_BIT(val, bit)	(!!(val & PPC_BIT(bit)))
#घोषणा EXTRACT_PPC_BITS(val, bs, be)	((val & PPC_BITMASK(bs, be)) >> PPC_BITLSHIFT(be))

#घोषणा AFUD_READ_INFO(afu)		AFUD_READ(afu, 0x0)
#घोषणा   AFUD_NUM_INTS_PER_PROC(val)	EXTRACT_PPC_BITS(val,  0, 15)
#घोषणा   AFUD_NUM_PROCS(val)		EXTRACT_PPC_BITS(val, 16, 31)
#घोषणा   AFUD_NUM_CRS(val)		EXTRACT_PPC_BITS(val, 32, 47)
#घोषणा   AFUD_MULTIMODE(val)		EXTRACT_PPC_BIT(val, 48)
#घोषणा   AFUD_PUSH_BLOCK_TRANSFER(val)	EXTRACT_PPC_BIT(val, 55)
#घोषणा   AFUD_DEDICATED_PROCESS(val)	EXTRACT_PPC_BIT(val, 59)
#घोषणा   AFUD_AFU_सूचीECTED(val)	EXTRACT_PPC_BIT(val, 61)
#घोषणा   AFUD_TIME_SLICED(val)		EXTRACT_PPC_BIT(val, 63)
#घोषणा AFUD_READ_CR(afu)		AFUD_READ(afu, 0x20)
#घोषणा   AFUD_CR_LEN(val)		EXTRACT_PPC_BITS(val, 8, 63)
#घोषणा AFUD_READ_CR_OFF(afu)		AFUD_READ(afu, 0x28)
#घोषणा AFUD_READ_PPPSA(afu)		AFUD_READ(afu, 0x30)
#घोषणा   AFUD_PPPSA_PP(val)		EXTRACT_PPC_BIT(val, 6)
#घोषणा   AFUD_PPPSA_PSA(val)		EXTRACT_PPC_BIT(val, 7)
#घोषणा   AFUD_PPPSA_LEN(val)		EXTRACT_PPC_BITS(val, 8, 63)
#घोषणा AFUD_READ_PPPSA_OFF(afu)	AFUD_READ(afu, 0x38)
#घोषणा AFUD_READ_EB(afu)		AFUD_READ(afu, 0x40)
#घोषणा   AFUD_EB_LEN(val)		EXTRACT_PPC_BITS(val, 8, 63)
#घोषणा AFUD_READ_EB_OFF(afu)		AFUD_READ(afu, 0x48)

अटल स्थिर काष्ठा pci_device_id cxl_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_IBM, 0x0477), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_IBM, 0x044b), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_IBM, 0x04cf), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_IBM, 0x0601), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_IBM, 0x0623), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_IBM, 0x0628), पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, cxl_pci_tbl);


/*
 * Mostly using these wrappers to aव्योम confusion:
 * priv 1 is BAR2, जबतक priv 2 is BAR0
 */
अटल अंतरभूत resource_माप_प्रकार p1_base(काष्ठा pci_dev *dev)
अणु
	वापस pci_resource_start(dev, 2);
पूर्ण

अटल अंतरभूत resource_माप_प्रकार p1_size(काष्ठा pci_dev *dev)
अणु
	वापस pci_resource_len(dev, 2);
पूर्ण

अटल अंतरभूत resource_माप_प्रकार p2_base(काष्ठा pci_dev *dev)
अणु
	वापस pci_resource_start(dev, 0);
पूर्ण

अटल अंतरभूत resource_माप_प्रकार p2_size(काष्ठा pci_dev *dev)
अणु
	वापस pci_resource_len(dev, 0);
पूर्ण

अटल पूर्णांक find_cxl_vsec(काष्ठा pci_dev *dev)
अणु
	पूर्णांक vsec = 0;
	u16 val;

	जबतक ((vsec = pci_find_next_ext_capability(dev, vsec, PCI_EXT_CAP_ID_VNDR))) अणु
		pci_पढ़ो_config_word(dev, vsec + 0x4, &val);
		अगर (val == CXL_PCI_VSEC_ID)
			वापस vsec;
	पूर्ण
	वापस 0;

पूर्ण

अटल व्योम dump_cxl_config_space(काष्ठा pci_dev *dev)
अणु
	पूर्णांक vsec;
	u32 val;

	dev_info(&dev->dev, "dump_cxl_config_space\n");

	pci_पढ़ो_config_dword(dev, PCI_BASE_ADDRESS_0, &val);
	dev_info(&dev->dev, "BAR0: %#.8x\n", val);
	pci_पढ़ो_config_dword(dev, PCI_BASE_ADDRESS_1, &val);
	dev_info(&dev->dev, "BAR1: %#.8x\n", val);
	pci_पढ़ो_config_dword(dev, PCI_BASE_ADDRESS_2, &val);
	dev_info(&dev->dev, "BAR2: %#.8x\n", val);
	pci_पढ़ो_config_dword(dev, PCI_BASE_ADDRESS_3, &val);
	dev_info(&dev->dev, "BAR3: %#.8x\n", val);
	pci_पढ़ो_config_dword(dev, PCI_BASE_ADDRESS_4, &val);
	dev_info(&dev->dev, "BAR4: %#.8x\n", val);
	pci_पढ़ो_config_dword(dev, PCI_BASE_ADDRESS_5, &val);
	dev_info(&dev->dev, "BAR5: %#.8x\n", val);

	dev_info(&dev->dev, "p1 regs: %#llx, len: %#llx\n",
		p1_base(dev), p1_size(dev));
	dev_info(&dev->dev, "p2 regs: %#llx, len: %#llx\n",
		p2_base(dev), p2_size(dev));
	dev_info(&dev->dev, "BAR 4/5: %#llx, len: %#llx\n",
		pci_resource_start(dev, 4), pci_resource_len(dev, 4));

	अगर (!(vsec = find_cxl_vsec(dev)))
		वापस;

#घोषणा show_reg(name, what) \
	dev_info(&dev->dev, "cxl vsec: %30s: %#x\n", name, what)

	pci_पढ़ो_config_dword(dev, vsec + 0x0, &val);
	show_reg("Cap ID", (val >> 0) & 0xffff);
	show_reg("Cap Ver", (val >> 16) & 0xf);
	show_reg("Next Cap Ptr", (val >> 20) & 0xfff);
	pci_पढ़ो_config_dword(dev, vsec + 0x4, &val);
	show_reg("VSEC ID", (val >> 0) & 0xffff);
	show_reg("VSEC Rev", (val >> 16) & 0xf);
	show_reg("VSEC Length",	(val >> 20) & 0xfff);
	pci_पढ़ो_config_dword(dev, vsec + 0x8, &val);
	show_reg("Num AFUs", (val >> 0) & 0xff);
	show_reg("Status", (val >> 8) & 0xff);
	show_reg("Mode Control", (val >> 16) & 0xff);
	show_reg("Reserved", (val >> 24) & 0xff);
	pci_पढ़ो_config_dword(dev, vsec + 0xc, &val);
	show_reg("PSL Rev", (val >> 0) & 0xffff);
	show_reg("CAIA Ver", (val >> 16) & 0xffff);
	pci_पढ़ो_config_dword(dev, vsec + 0x10, &val);
	show_reg("Base Image Rev", (val >> 0) & 0xffff);
	show_reg("Reserved", (val >> 16) & 0x0fff);
	show_reg("Image Control", (val >> 28) & 0x3);
	show_reg("Reserved", (val >> 30) & 0x1);
	show_reg("Image Loaded", (val >> 31) & 0x1);

	pci_पढ़ो_config_dword(dev, vsec + 0x14, &val);
	show_reg("Reserved", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x18, &val);
	show_reg("Reserved", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x1c, &val);
	show_reg("Reserved", val);

	pci_पढ़ो_config_dword(dev, vsec + 0x20, &val);
	show_reg("AFU Descriptor Offset", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x24, &val);
	show_reg("AFU Descriptor Size", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x28, &val);
	show_reg("Problem State Offset", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x2c, &val);
	show_reg("Problem State Size", val);

	pci_पढ़ो_config_dword(dev, vsec + 0x30, &val);
	show_reg("Reserved", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x34, &val);
	show_reg("Reserved", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x38, &val);
	show_reg("Reserved", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x3c, &val);
	show_reg("Reserved", val);

	pci_पढ़ो_config_dword(dev, vsec + 0x40, &val);
	show_reg("PSL Programming Port", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x44, &val);
	show_reg("PSL Programming Control", val);

	pci_पढ़ो_config_dword(dev, vsec + 0x48, &val);
	show_reg("Reserved", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x4c, &val);
	show_reg("Reserved", val);

	pci_पढ़ो_config_dword(dev, vsec + 0x50, &val);
	show_reg("Flash Address Register", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x54, &val);
	show_reg("Flash Size Register", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x58, &val);
	show_reg("Flash Status/Control Register", val);
	pci_पढ़ो_config_dword(dev, vsec + 0x58, &val);
	show_reg("Flash Data Port", val);

#अघोषित show_reg
पूर्ण

अटल व्योम dump_afu_descriptor(काष्ठा cxl_afu *afu)
अणु
	u64 val, afu_cr_num, afu_cr_off, afu_cr_len;
	पूर्णांक i;

#घोषणा show_reg(name, what) \
	dev_info(&afu->dev, "afu desc: %30s: %#llx\n", name, what)

	val = AFUD_READ_INFO(afu);
	show_reg("num_ints_per_process", AFUD_NUM_INTS_PER_PROC(val));
	show_reg("num_of_processes", AFUD_NUM_PROCS(val));
	show_reg("num_of_afu_CRs", AFUD_NUM_CRS(val));
	show_reg("req_prog_mode", val & 0xffffULL);
	afu_cr_num = AFUD_NUM_CRS(val);

	val = AFUD_READ(afu, 0x8);
	show_reg("Reserved", val);
	val = AFUD_READ(afu, 0x10);
	show_reg("Reserved", val);
	val = AFUD_READ(afu, 0x18);
	show_reg("Reserved", val);

	val = AFUD_READ_CR(afu);
	show_reg("Reserved", (val >> (63-7)) & 0xff);
	show_reg("AFU_CR_len", AFUD_CR_LEN(val));
	afu_cr_len = AFUD_CR_LEN(val) * 256;

	val = AFUD_READ_CR_OFF(afu);
	afu_cr_off = val;
	show_reg("AFU_CR_offset", val);

	val = AFUD_READ_PPPSA(afu);
	show_reg("PerProcessPSA_control", (val >> (63-7)) & 0xff);
	show_reg("PerProcessPSA Length", AFUD_PPPSA_LEN(val));

	val = AFUD_READ_PPPSA_OFF(afu);
	show_reg("PerProcessPSA_offset", val);

	val = AFUD_READ_EB(afu);
	show_reg("Reserved", (val >> (63-7)) & 0xff);
	show_reg("AFU_EB_len", AFUD_EB_LEN(val));

	val = AFUD_READ_EB_OFF(afu);
	show_reg("AFU_EB_offset", val);

	क्रम (i = 0; i < afu_cr_num; i++) अणु
		val = AFUD_READ_LE(afu, afu_cr_off + i * afu_cr_len);
		show_reg("CR Vendor", val & 0xffff);
		show_reg("CR Device", (val >> 16) & 0xffff);
	पूर्ण
#अघोषित show_reg
पूर्ण

#घोषणा P8_CAPP_UNIT0_ID 0xBA
#घोषणा P8_CAPP_UNIT1_ID 0XBE
#घोषणा P9_CAPP_UNIT0_ID 0xC0
#घोषणा P9_CAPP_UNIT1_ID 0xE0

अटल पूर्णांक get_phb_index(काष्ठा device_node *np, u32 *phb_index)
अणु
	अगर (of_property_पढ़ो_u32(np, "ibm,phb-index", phb_index))
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल u64 get_capp_unit_id(काष्ठा device_node *np, u32 phb_index)
अणु
	/*
	 * POWER 8:
	 *  - For chips other than POWER8NVL, we only have CAPP 0,
	 *    irrespective of which PHB is used.
	 *  - For POWER8NVL, assume CAPP 0 is attached to PHB0 and
	 *    CAPP 1 is attached to PHB1.
	 */
	अगर (cxl_is_घातer8()) अणु
		अगर (!pvr_version_is(PVR_POWER8NVL))
			वापस P8_CAPP_UNIT0_ID;

		अगर (phb_index == 0)
			वापस P8_CAPP_UNIT0_ID;

		अगर (phb_index == 1)
			वापस P8_CAPP_UNIT1_ID;
	पूर्ण

	/*
	 * POWER 9:
	 *   PEC0 (PHB0). Capp ID = CAPP0 (0b1100_0000)
	 *   PEC1 (PHB1 - PHB2). No capi mode
	 *   PEC2 (PHB3 - PHB4 - PHB5): Capi mode on PHB3 only. Capp ID = CAPP1 (0b1110_0000)
	 */
	अगर (cxl_is_घातer9()) अणु
		अगर (phb_index == 0)
			वापस P9_CAPP_UNIT0_ID;

		अगर (phb_index == 3)
			वापस P9_CAPP_UNIT1_ID;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxl_calc_capp_routing(काष्ठा pci_dev *dev, u64 *chipid,
			     u32 *phb_index, u64 *capp_unit_id)
अणु
	पूर्णांक rc;
	काष्ठा device_node *np;
	स्थिर __be32 *prop;

	अगर (!(np = pnv_pci_get_phb_node(dev)))
		वापस -ENODEV;

	जबतक (np && !(prop = of_get_property(np, "ibm,chip-id", शून्य)))
		np = of_get_next_parent(np);
	अगर (!np)
		वापस -ENODEV;

	*chipid = be32_to_cpup(prop);

	rc = get_phb_index(np, phb_index);
	अगर (rc) अणु
		pr_err("cxl: invalid phb index\n");
		वापस rc;
	पूर्ण

	*capp_unit_id = get_capp_unit_id(np, *phb_index);
	of_node_put(np);
	अगर (!*capp_unit_id) अणु
		pr_err("cxl: No capp unit found for PHB[%lld,%d]. Make sure the adapter is on a capi-compatible slot\n",
		       *chipid, *phb_index);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(indications_mutex);

अटल पूर्णांक get_phb_indications(काष्ठा pci_dev *dev, u64 *capiind, u64 *asnind,
			       u64 *nbwind)
अणु
	अटल u64 nbw, asn, capi = 0;
	काष्ठा device_node *np;
	स्थिर __be32 *prop;

	mutex_lock(&indications_mutex);
	अगर (!capi) अणु
		अगर (!(np = pnv_pci_get_phb_node(dev))) अणु
			mutex_unlock(&indications_mutex);
			वापस -ENODEV;
		पूर्ण

		prop = of_get_property(np, "ibm,phb-indications", शून्य);
		अगर (!prop) अणु
			nbw = 0x0300UL; /* legacy values */
			asn = 0x0400UL;
			capi = 0x0200UL;
		पूर्ण अन्यथा अणु
			nbw = (u64)be32_to_cpu(prop[2]);
			asn = (u64)be32_to_cpu(prop[1]);
			capi = (u64)be32_to_cpu(prop[0]);
		पूर्ण
		of_node_put(np);
	पूर्ण
	*capiind = capi;
	*asnind = asn;
	*nbwind = nbw;
	mutex_unlock(&indications_mutex);
	वापस 0;
पूर्ण

पूर्णांक cxl_get_xsl9_dsnctl(काष्ठा pci_dev *dev, u64 capp_unit_id, u64 *reg)
अणु
	u64 xsl_dsnctl;
	u64 capiind, asnind, nbwind;

	/*
	 * CAPI Identअगरier bits [0:7]
	 * bit 61:60 MSI bits --> 0
	 * bit 59 TVT selector --> 0
	 */
	अगर (get_phb_indications(dev, &capiind, &asnind, &nbwind))
		वापस -ENODEV;

	/*
	 * Tell XSL where to route data to.
	 * The field chipid should match the PHB CAPI_CMPM रेजिस्टर
	 */
	xsl_dsnctl = (capiind << (63-15)); /* Bit 57 */
	xsl_dsnctl |= (capp_unit_id << (63-15));

	/* nMMU_ID Defaults to: bै 000001001ै */
	xsl_dsnctl |= ((u64)0x09 << (63-28));

	/*
	 * Used to identअगरy CAPI packets which should be sorted पूर्णांकo
	 * the Non-Blocking queues by the PHB. This field should match
	 * the PHB PBL_NBW_CMPM रेजिस्टर
	 * nbwind=0x03, bits [57:58], must include capi indicator.
	 * Not supported on P9 DD1.
	 */
	xsl_dsnctl |= (nbwind << (63-55));

	/*
	 * Upper 16b address bits of ASB_Notअगरy messages sent to the
	 * प्रणाली. Need to match the PHBै s ASN Compare/Mask Register.
	 * Not supported on P9 DD1.
	 */
	xsl_dsnctl |= asnind;

	*reg = xsl_dsnctl;
	वापस 0;
पूर्ण

अटल पूर्णांक init_implementation_adapter_regs_psl9(काष्ठा cxl *adapter,
						 काष्ठा pci_dev *dev)
अणु
	u64 xsl_dsnctl, psl_fircntl;
	u64 chipid;
	u32 phb_index;
	u64 capp_unit_id;
	u64 psl_debug;
	पूर्णांक rc;

	rc = cxl_calc_capp_routing(dev, &chipid, &phb_index, &capp_unit_id);
	अगर (rc)
		वापस rc;

	rc = cxl_get_xsl9_dsnctl(dev, capp_unit_id, &xsl_dsnctl);
	अगर (rc)
		वापस rc;

	cxl_p1_ग_लिखो(adapter, CXL_XSL9_DSNCTL, xsl_dsnctl);

	/* Set fir_cntl to recommended value क्रम production env */
	psl_fircntl = (0x2ULL << (63-3)); /* ce_report */
	psl_fircntl |= (0x1ULL << (63-6)); /* FIR_report */
	psl_fircntl |= 0x1ULL; /* ce_thresh */
	cxl_p1_ग_लिखो(adapter, CXL_PSL9_FIR_CNTL, psl_fircntl);

	/* Setup the PSL to transmit packets on the PCIe beक्रमe the
	 * CAPP is enabled. Make sure that CAPP भव machines are disabled
	 */
	cxl_p1_ग_लिखो(adapter, CXL_PSL9_DSNDCTL, 0x0001001000012A10ULL);

	/*
	 * A response to an ASB_Notअगरy request is वापसed by the
	 * प्रणाली as an MMIO ग_लिखो to the address defined in
	 * the PSL_TNR_ADDR रेजिस्टर.
	 * keep the Reset Value: 0x00020000E0000000
	 */

	/* Enable XSL rty limit */
	cxl_p1_ग_लिखो(adapter, CXL_XSL9_DEF, 0x51F8000000000005ULL);

	/* Change XSL_INV dummy पढ़ो threshold */
	cxl_p1_ग_लिखो(adapter, CXL_XSL9_INV, 0x0000040007FFC200ULL);

	अगर (phb_index == 3) अणु
		/* disable machines 31-47 and 20-27 क्रम DMA */
		cxl_p1_ग_लिखो(adapter, CXL_PSL9_APCDEDTYPE, 0x40000FF3FFFF0000ULL);
	पूर्ण

	/* Snoop machines */
	cxl_p1_ग_लिखो(adapter, CXL_PSL9_APCDEDALLOC, 0x800F000200000000ULL);

	/* Enable NORST and DD2 features */
	cxl_p1_ग_लिखो(adapter, CXL_PSL9_DEBUG, 0xC000000000000000ULL);

	/*
	 * Check अगर PSL has data-cache. We need to flush adapter datacache
	 * when as its about to be हटाओd.
	 */
	psl_debug = cxl_p1_पढ़ो(adapter, CXL_PSL9_DEBUG);
	अगर (psl_debug & CXL_PSL_DEBUG_CDC) अणु
		dev_dbg(&dev->dev, "No data-cache present\n");
		adapter->native->no_data_cache = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_implementation_adapter_regs_psl8(काष्ठा cxl *adapter, काष्ठा pci_dev *dev)
अणु
	u64 psl_dsnctl, psl_fircntl;
	u64 chipid;
	u32 phb_index;
	u64 capp_unit_id;
	पूर्णांक rc;

	rc = cxl_calc_capp_routing(dev, &chipid, &phb_index, &capp_unit_id);
	अगर (rc)
		वापस rc;

	psl_dsnctl = 0x0000900000000000ULL; /* pteupd ttype, scकरोne */
	psl_dsnctl |= (0x2ULL << (63-38)); /* MMIO hang pulse: 256 us */
	/* Tell PSL where to route data to */
	psl_dsnctl |= (chipid << (63-5));
	psl_dsnctl |= (capp_unit_id << (63-13));

	cxl_p1_ग_लिखो(adapter, CXL_PSL_DSNDCTL, psl_dsnctl);
	cxl_p1_ग_लिखो(adapter, CXL_PSL_RESLCKTO, 0x20000000200ULL);
	/* snoop ग_लिखो mask */
	cxl_p1_ग_लिखो(adapter, CXL_PSL_SNWRALLOC, 0x00000000FFFFFFFFULL);
	/* set fir_cntl to recommended value क्रम production env */
	psl_fircntl = (0x2ULL << (63-3)); /* ce_report */
	psl_fircntl |= (0x1ULL << (63-6)); /* FIR_report */
	psl_fircntl |= 0x1ULL; /* ce_thresh */
	cxl_p1_ग_लिखो(adapter, CXL_PSL_FIR_CNTL, psl_fircntl);
	/* क्रम debugging with trace arrays */
	cxl_p1_ग_लिखो(adapter, CXL_PSL_TRACE, 0x0000FF7C00000000ULL);

	वापस 0;
पूर्ण

/* PSL */
#घोषणा TBSYNC_CAL(n) (((u64)n & 0x7) << (63-3))
#घोषणा TBSYNC_CNT(n) (((u64)n & 0x7) << (63-6))
/* For the PSL this is a multiple क्रम 0 < n <= 7: */
#घोषणा PSL_2048_250MHZ_CYCLES 1

अटल व्योम ग_लिखो_समयbase_ctrl_psl8(काष्ठा cxl *adapter)
अणु
	cxl_p1_ग_लिखो(adapter, CXL_PSL_TB_CTLSTAT,
		     TBSYNC_CNT(2 * PSL_2048_250MHZ_CYCLES));
पूर्ण

अटल u64 समयbase_पढ़ो_psl9(काष्ठा cxl *adapter)
अणु
	वापस cxl_p1_पढ़ो(adapter, CXL_PSL9_Timebase);
पूर्ण

अटल u64 समयbase_पढ़ो_psl8(काष्ठा cxl *adapter)
अणु
	वापस cxl_p1_पढ़ो(adapter, CXL_PSL_Timebase);
पूर्ण

अटल व्योम cxl_setup_psl_समयbase(काष्ठा cxl *adapter, काष्ठा pci_dev *dev)
अणु
	काष्ठा device_node *np;

	adapter->psl_समयbase_synced = false;

	अगर (!(np = pnv_pci_get_phb_node(dev)))
		वापस;

	/* Do not fail when CAPP समयbase sync is not supported by OPAL */
	of_node_get(np);
	अगर (! of_get_property(np, "ibm,capp-timebase-sync", शून्य)) अणु
		of_node_put(np);
		dev_info(&dev->dev, "PSL timebase inactive: OPAL support missing\n");
		वापस;
	पूर्ण
	of_node_put(np);

	/*
	 * Setup PSL Timebase Control and Status रेजिस्टर
	 * with the recommended Timebase Sync Count value
	 */
	अगर (adapter->native->sl_ops->ग_लिखो_समयbase_ctrl)
		adapter->native->sl_ops->ग_लिखो_समयbase_ctrl(adapter);

	/* Enable PSL Timebase */
	cxl_p1_ग_लिखो(adapter, CXL_PSL_Control, 0x0000000000000000);
	cxl_p1_ग_लिखो(adapter, CXL_PSL_Control, CXL_PSL_Control_tb);

	वापस;
पूर्ण

अटल पूर्णांक init_implementation_afu_regs_psl9(काष्ठा cxl_afu *afu)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक init_implementation_afu_regs_psl8(काष्ठा cxl_afu *afu)
अणु
	/* पढ़ो/ग_लिखो masks क्रम this slice */
	cxl_p1n_ग_लिखो(afu, CXL_PSL_APCALLOC_A, 0xFFFFFFFEFEFEFEFEULL);
	/* APC पढ़ो/ग_लिखो masks क्रम this slice */
	cxl_p1n_ग_लिखो(afu, CXL_PSL_COALLOC_A, 0xFF000000FEFEFEFEULL);
	/* क्रम debugging with trace arrays */
	cxl_p1n_ग_लिखो(afu, CXL_PSL_SLICE_TRACE, 0x0000FFFF00000000ULL);
	cxl_p1n_ग_लिखो(afu, CXL_PSL_RXCTL_A, CXL_PSL_RXCTL_AFUHP_4S);

	वापस 0;
पूर्ण

पूर्णांक cxl_pci_setup_irq(काष्ठा cxl *adapter, अचिन्हित पूर्णांक hwirq,
		अचिन्हित पूर्णांक virq)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(adapter->dev.parent);

	वापस pnv_cxl_ioda_msi_setup(dev, hwirq, virq);
पूर्ण

पूर्णांक cxl_update_image_control(काष्ठा cxl *adapter)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(adapter->dev.parent);
	पूर्णांक rc;
	पूर्णांक vsec;
	u8 image_state;

	अगर (!(vsec = find_cxl_vsec(dev))) अणु
		dev_err(&dev->dev, "ABORTING: CXL VSEC not found!\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((rc = CXL_READ_VSEC_IMAGE_STATE(dev, vsec, &image_state))) अणु
		dev_err(&dev->dev, "failed to read image state: %i\n", rc);
		वापस rc;
	पूर्ण

	अगर (adapter->perst_loads_image)
		image_state |= CXL_VSEC_PERST_LOADS_IMAGE;
	अन्यथा
		image_state &= ~CXL_VSEC_PERST_LOADS_IMAGE;

	अगर (adapter->perst_select_user)
		image_state |= CXL_VSEC_PERST_SELECT_USER;
	अन्यथा
		image_state &= ~CXL_VSEC_PERST_SELECT_USER;

	अगर ((rc = CXL_WRITE_VSEC_IMAGE_STATE(dev, vsec, image_state))) अणु
		dev_err(&dev->dev, "failed to update image control: %i\n", rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxl_pci_alloc_one_irq(काष्ठा cxl *adapter)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(adapter->dev.parent);

	वापस pnv_cxl_alloc_hwirqs(dev, 1);
पूर्ण

व्योम cxl_pci_release_one_irq(काष्ठा cxl *adapter, पूर्णांक hwirq)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(adapter->dev.parent);

	वापस pnv_cxl_release_hwirqs(dev, hwirq, 1);
पूर्ण

पूर्णांक cxl_pci_alloc_irq_ranges(काष्ठा cxl_irq_ranges *irqs,
			काष्ठा cxl *adapter, अचिन्हित पूर्णांक num)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(adapter->dev.parent);

	वापस pnv_cxl_alloc_hwirq_ranges(irqs, dev, num);
पूर्ण

व्योम cxl_pci_release_irq_ranges(काष्ठा cxl_irq_ranges *irqs,
				काष्ठा cxl *adapter)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(adapter->dev.parent);

	pnv_cxl_release_hwirq_ranges(irqs, dev);
पूर्ण

अटल पूर्णांक setup_cxl_bars(काष्ठा pci_dev *dev)
अणु
	/* Safety check in हाल we get backported to < 3.17 without M64 */
	अगर ((p1_base(dev) < 0x100000000ULL) ||
	    (p2_base(dev) < 0x100000000ULL)) अणु
		dev_err(&dev->dev, "ABORTING: M32 BAR assignment incompatible with CXL\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * BAR 4/5 has a special meaning क्रम CXL and must be programmed with a
	 * special value corresponding to the CXL protocol address range.
	 * For POWER 8/9 that means bits 48:49 must be set to 10
	 */
	pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_4, 0x00000000);
	pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_5, 0x00020000);

	वापस 0;
पूर्ण

/* pciex node: ibm,opal-m64-winकरोw = <0x3d058 0x0 0x3d058 0x0 0x8 0x0>; */
अटल पूर्णांक चयन_card_to_cxl(काष्ठा pci_dev *dev)
अणु
	पूर्णांक vsec;
	u8 val;
	पूर्णांक rc;

	dev_info(&dev->dev, "switch card to CXL\n");

	अगर (!(vsec = find_cxl_vsec(dev))) अणु
		dev_err(&dev->dev, "ABORTING: CXL VSEC not found!\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((rc = CXL_READ_VSEC_MODE_CONTROL(dev, vsec, &val))) अणु
		dev_err(&dev->dev, "failed to read current mode control: %i", rc);
		वापस rc;
	पूर्ण
	val &= ~CXL_VSEC_PROTOCOL_MASK;
	val |= CXL_VSEC_PROTOCOL_256TB | CXL_VSEC_PROTOCOL_ENABLE;
	अगर ((rc = CXL_WRITE_VSEC_MODE_CONTROL(dev, vsec, val))) अणु
		dev_err(&dev->dev, "failed to enable CXL protocol: %i", rc);
		वापस rc;
	पूर्ण
	/*
	 * The CAIA spec (v0.12 11.6 Bi-modal Device Support) states
	 * we must रुको 100ms after this mode चयन beक्रमe touching
	 * PCIe config space.
	 */
	msleep(100);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_map_slice_regs(काष्ठा cxl_afu *afu, काष्ठा cxl *adapter, काष्ठा pci_dev *dev)
अणु
	u64 p1n_base, p2n_base, afu_desc;
	स्थिर u64 p1n_size = 0x100;
	स्थिर u64 p2n_size = 0x1000;

	p1n_base = p1_base(dev) + 0x10000 + (afu->slice * p1n_size);
	p2n_base = p2_base(dev) + (afu->slice * p2n_size);
	afu->psn_phys = p2_base(dev) + (adapter->native->ps_off + (afu->slice * adapter->ps_size));
	afu_desc = p2_base(dev) + adapter->native->afu_desc_off + (afu->slice * adapter->native->afu_desc_size);

	अगर (!(afu->native->p1n_mmio = ioremap(p1n_base, p1n_size)))
		जाओ err;
	अगर (!(afu->p2n_mmio = ioremap(p2n_base, p2n_size)))
		जाओ err1;
	अगर (afu_desc) अणु
		अगर (!(afu->native->afu_desc_mmio = ioremap(afu_desc, adapter->native->afu_desc_size)))
			जाओ err2;
	पूर्ण

	वापस 0;
err2:
	iounmap(afu->p2n_mmio);
err1:
	iounmap(afu->native->p1n_mmio);
err:
	dev_err(&afu->dev, "Error mapping AFU MMIO regions\n");
	वापस -ENOMEM;
पूर्ण

अटल व्योम pci_unmap_slice_regs(काष्ठा cxl_afu *afu)
अणु
	अगर (afu->p2n_mmio) अणु
		iounmap(afu->p2n_mmio);
		afu->p2n_mmio = शून्य;
	पूर्ण
	अगर (afu->native->p1n_mmio) अणु
		iounmap(afu->native->p1n_mmio);
		afu->native->p1n_mmio = शून्य;
	पूर्ण
	अगर (afu->native->afu_desc_mmio) अणु
		iounmap(afu->native->afu_desc_mmio);
		afu->native->afu_desc_mmio = शून्य;
	पूर्ण
पूर्ण

व्योम cxl_pci_release_afu(काष्ठा device *dev)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(dev);

	pr_devel("%s\n", __func__);

	idr_destroy(&afu->contexts_idr);
	cxl_release_spa(afu);

	kमुक्त(afu->native);
	kमुक्त(afu);
पूर्ण

/* Expects AFU काष्ठा to have recently been zeroed out */
अटल पूर्णांक cxl_पढ़ो_afu_descriptor(काष्ठा cxl_afu *afu)
अणु
	u64 val;

	val = AFUD_READ_INFO(afu);
	afu->pp_irqs = AFUD_NUM_INTS_PER_PROC(val);
	afu->max_procs_भवised = AFUD_NUM_PROCS(val);
	afu->crs_num = AFUD_NUM_CRS(val);

	अगर (AFUD_AFU_सूचीECTED(val))
		afu->modes_supported |= CXL_MODE_सूचीECTED;
	अगर (AFUD_DEDICATED_PROCESS(val))
		afu->modes_supported |= CXL_MODE_DEDICATED;
	अगर (AFUD_TIME_SLICED(val))
		afu->modes_supported |= CXL_MODE_TIME_SLICED;

	val = AFUD_READ_PPPSA(afu);
	afu->pp_size = AFUD_PPPSA_LEN(val) * 4096;
	afu->psa = AFUD_PPPSA_PSA(val);
	अगर ((afu->pp_psa = AFUD_PPPSA_PP(val)))
		afu->native->pp_offset = AFUD_READ_PPPSA_OFF(afu);

	val = AFUD_READ_CR(afu);
	afu->crs_len = AFUD_CR_LEN(val) * 256;
	afu->crs_offset = AFUD_READ_CR_OFF(afu);


	/* eb_len is in multiple of 4K */
	afu->eb_len = AFUD_EB_LEN(AFUD_READ_EB(afu)) * 4096;
	afu->eb_offset = AFUD_READ_EB_OFF(afu);

	/* eb_off is 4K aligned so lower 12 bits are always zero */
	अगर (EXTRACT_PPC_BITS(afu->eb_offset, 0, 11) != 0) अणु
		dev_warn(&afu->dev,
			 "Invalid AFU error buffer offset %Lx\n",
			 afu->eb_offset);
		dev_info(&afu->dev,
			 "Ignoring AFU error buffer in the descriptor\n");
		/* indicate that no afu buffer exists */
		afu->eb_len = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxl_afu_descriptor_looks_ok(काष्ठा cxl_afu *afu)
अणु
	पूर्णांक i, rc;
	u32 val;

	अगर (afu->psa && afu->adapter->ps_size <
			(afu->native->pp_offset + afu->pp_size*afu->max_procs_भवised)) अणु
		dev_err(&afu->dev, "per-process PSA can't fit inside the PSA!\n");
		वापस -ENODEV;
	पूर्ण

	अगर (afu->pp_psa && (afu->pp_size < PAGE_SIZE))
		dev_warn(&afu->dev, "AFU uses pp_size(%#016llx) < PAGE_SIZE per-process PSA!\n", afu->pp_size);

	क्रम (i = 0; i < afu->crs_num; i++) अणु
		rc = cxl_ops->afu_cr_पढ़ो32(afu, i, 0, &val);
		अगर (rc || val == 0) अणु
			dev_err(&afu->dev, "ABORTING: AFU configuration record %i is invalid\n", i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर ((afu->modes_supported & ~CXL_MODE_DEDICATED) && afu->max_procs_भवised == 0) अणु
		/*
		 * We could also check this क्रम the dedicated process model
		 * since the architecture indicates it should be set to 1, but
		 * in that हाल we ignore the value and I'd rather not risk
		 * अवरोधing any existing dedicated process AFUs that left it as
		 * 0 (not that I'm aware of any). It is clearly an error क्रम an
		 * AFU directed AFU to set this to 0, and would have previously
		 * triggered a bug resulting in the maximum not being enक्रमced
		 * at all since idr_alloc treats 0 as no maximum.
		 */
		dev_err(&afu->dev, "AFU does not support any processes\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sanitise_afu_regs_psl9(काष्ठा cxl_afu *afu)
अणु
	u64 reg;

	/*
	 * Clear out any regs that contain either an IVTE or address or may be
	 * रुकोing on an acknowledgment to try to be a bit safer as we bring
	 * it online
	 */
	reg = cxl_p2n_पढ़ो(afu, CXL_AFU_Cntl_An);
	अगर ((reg & CXL_AFU_Cntl_An_ES_MASK) != CXL_AFU_Cntl_An_ES_Disabled) अणु
		dev_warn(&afu->dev, "WARNING: AFU was not disabled: %#016llx\n", reg);
		अगर (cxl_ops->afu_reset(afu))
			वापस -EIO;
		अगर (cxl_afu_disable(afu))
			वापस -EIO;
		अगर (cxl_psl_purge(afu))
			वापस -EIO;
	पूर्ण
	cxl_p1n_ग_लिखो(afu, CXL_PSL_SPAP_An, 0x0000000000000000);
	cxl_p1n_ग_लिखो(afu, CXL_PSL_AMBAR_An, 0x0000000000000000);
	reg = cxl_p2n_पढ़ो(afu, CXL_PSL_DSISR_An);
	अगर (reg) अणु
		dev_warn(&afu->dev, "AFU had pending DSISR: %#016llx\n", reg);
		अगर (reg & CXL_PSL9_DSISR_An_TF)
			cxl_p2n_ग_लिखो(afu, CXL_PSL_TFC_An, CXL_PSL_TFC_An_AE);
		अन्यथा
			cxl_p2n_ग_लिखो(afu, CXL_PSL_TFC_An, CXL_PSL_TFC_An_A);
	पूर्ण
	अगर (afu->adapter->native->sl_ops->रेजिस्टर_serr_irq) अणु
		reg = cxl_p1n_पढ़ो(afu, CXL_PSL_SERR_An);
		अगर (reg) अणु
			अगर (reg & ~0x000000007fffffff)
				dev_warn(&afu->dev, "AFU had pending SERR: %#016llx\n", reg);
			cxl_p1n_ग_लिखो(afu, CXL_PSL_SERR_An, reg & ~0xffff);
		पूर्ण
	पूर्ण
	reg = cxl_p2n_पढ़ो(afu, CXL_PSL_ErrStat_An);
	अगर (reg) अणु
		dev_warn(&afu->dev, "AFU had pending error status: %#016llx\n", reg);
		cxl_p2n_ग_लिखो(afu, CXL_PSL_ErrStat_An, reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sanitise_afu_regs_psl8(काष्ठा cxl_afu *afu)
अणु
	u64 reg;

	/*
	 * Clear out any regs that contain either an IVTE or address or may be
	 * रुकोing on an acknowledgement to try to be a bit safer as we bring
	 * it online
	 */
	reg = cxl_p2n_पढ़ो(afu, CXL_AFU_Cntl_An);
	अगर ((reg & CXL_AFU_Cntl_An_ES_MASK) != CXL_AFU_Cntl_An_ES_Disabled) अणु
		dev_warn(&afu->dev, "WARNING: AFU was not disabled: %#016llx\n", reg);
		अगर (cxl_ops->afu_reset(afu))
			वापस -EIO;
		अगर (cxl_afu_disable(afu))
			वापस -EIO;
		अगर (cxl_psl_purge(afu))
			वापस -EIO;
	पूर्ण
	cxl_p1n_ग_लिखो(afu, CXL_PSL_SPAP_An, 0x0000000000000000);
	cxl_p1n_ग_लिखो(afu, CXL_PSL_IVTE_Limit_An, 0x0000000000000000);
	cxl_p1n_ग_लिखो(afu, CXL_PSL_IVTE_Offset_An, 0x0000000000000000);
	cxl_p1n_ग_लिखो(afu, CXL_PSL_AMBAR_An, 0x0000000000000000);
	cxl_p1n_ग_लिखो(afu, CXL_PSL_SPOffset_An, 0x0000000000000000);
	cxl_p1n_ग_लिखो(afu, CXL_HAURP_An, 0x0000000000000000);
	cxl_p2n_ग_लिखो(afu, CXL_CSRP_An, 0x0000000000000000);
	cxl_p2n_ग_लिखो(afu, CXL_AURP1_An, 0x0000000000000000);
	cxl_p2n_ग_लिखो(afu, CXL_AURP0_An, 0x0000000000000000);
	cxl_p2n_ग_लिखो(afu, CXL_SSTP1_An, 0x0000000000000000);
	cxl_p2n_ग_लिखो(afu, CXL_SSTP0_An, 0x0000000000000000);
	reg = cxl_p2n_पढ़ो(afu, CXL_PSL_DSISR_An);
	अगर (reg) अणु
		dev_warn(&afu->dev, "AFU had pending DSISR: %#016llx\n", reg);
		अगर (reg & CXL_PSL_DSISR_TRANS)
			cxl_p2n_ग_लिखो(afu, CXL_PSL_TFC_An, CXL_PSL_TFC_An_AE);
		अन्यथा
			cxl_p2n_ग_लिखो(afu, CXL_PSL_TFC_An, CXL_PSL_TFC_An_A);
	पूर्ण
	अगर (afu->adapter->native->sl_ops->रेजिस्टर_serr_irq) अणु
		reg = cxl_p1n_पढ़ो(afu, CXL_PSL_SERR_An);
		अगर (reg) अणु
			अगर (reg & ~0xffff)
				dev_warn(&afu->dev, "AFU had pending SERR: %#016llx\n", reg);
			cxl_p1n_ग_लिखो(afu, CXL_PSL_SERR_An, reg & ~0xffff);
		पूर्ण
	पूर्ण
	reg = cxl_p2n_पढ़ो(afu, CXL_PSL_ErrStat_An);
	अगर (reg) अणु
		dev_warn(&afu->dev, "AFU had pending error status: %#016llx\n", reg);
		cxl_p2n_ग_लिखो(afu, CXL_PSL_ErrStat_An, reg);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा ERR_BUFF_MAX_COPY_SIZE PAGE_SIZE
/*
 * afu_eb_पढ़ो:
 * Called from sysfs and पढ़ोs the afu error info buffer. The h/w only supports
 * 4/8 bytes aligned access. So in हाल the requested offset/count arent 8 byte
 * aligned the function uses a bounce buffer which can be max PAGE_SIZE.
 */
sमाप_प्रकार cxl_pci_afu_पढ़ो_err_buffer(काष्ठा cxl_afu *afu, अक्षर *buf,
				loff_t off, माप_प्रकार count)
अणु
	loff_t aligned_start, aligned_end;
	माप_प्रकार aligned_length;
	व्योम *tbuf;
	स्थिर व्योम __iomem *ebuf = afu->native->afu_desc_mmio + afu->eb_offset;

	अगर (count == 0 || off < 0 || (माप_प्रकार)off >= afu->eb_len)
		वापस 0;

	/* calculate aligned पढ़ो winकरोw */
	count = min((माप_प्रकार)(afu->eb_len - off), count);
	aligned_start = round_करोwn(off, 8);
	aligned_end = round_up(off + count, 8);
	aligned_length = aligned_end - aligned_start;

	/* max we can copy in one पढ़ो is PAGE_SIZE */
	अगर (aligned_length > ERR_BUFF_MAX_COPY_SIZE) अणु
		aligned_length = ERR_BUFF_MAX_COPY_SIZE;
		count = ERR_BUFF_MAX_COPY_SIZE - (off & 0x7);
	पूर्ण

	/* use bounce buffer क्रम copy */
	tbuf = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!tbuf)
		वापस -ENOMEM;

	/* perक्रमm aligned पढ़ो from the mmio region */
	स_नकल_fromio(tbuf, ebuf + aligned_start, aligned_length);
	स_नकल(buf, tbuf + (off & 0x7), count);

	मुक्त_page((अचिन्हित दीर्घ)tbuf);

	वापस count;
पूर्ण

अटल पूर्णांक pci_configure_afu(काष्ठा cxl_afu *afu, काष्ठा cxl *adapter, काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;

	अगर ((rc = pci_map_slice_regs(afu, adapter, dev)))
		वापस rc;

	अगर (adapter->native->sl_ops->sanitise_afu_regs) अणु
		rc = adapter->native->sl_ops->sanitise_afu_regs(afu);
		अगर (rc)
			जाओ err1;
	पूर्ण

	/* We need to reset the AFU beक्रमe we can पढ़ो the AFU descriptor */
	अगर ((rc = cxl_ops->afu_reset(afu)))
		जाओ err1;

	अगर (cxl_verbose)
		dump_afu_descriptor(afu);

	अगर ((rc = cxl_पढ़ो_afu_descriptor(afu)))
		जाओ err1;

	अगर ((rc = cxl_afu_descriptor_looks_ok(afu)))
		जाओ err1;

	अगर (adapter->native->sl_ops->afu_regs_init)
		अगर ((rc = adapter->native->sl_ops->afu_regs_init(afu)))
			जाओ err1;

	अगर (adapter->native->sl_ops->रेजिस्टर_serr_irq)
		अगर ((rc = adapter->native->sl_ops->रेजिस्टर_serr_irq(afu)))
			जाओ err1;

	अगर ((rc = cxl_native_रेजिस्टर_psl_irq(afu)))
		जाओ err2;

	atomic_set(&afu->configured_state, 0);
	वापस 0;

err2:
	अगर (adapter->native->sl_ops->release_serr_irq)
		adapter->native->sl_ops->release_serr_irq(afu);
err1:
	pci_unmap_slice_regs(afu);
	वापस rc;
पूर्ण

अटल व्योम pci_deconfigure_afu(काष्ठा cxl_afu *afu)
अणु
	/*
	 * It's okay to deconfigure when AFU is alपढ़ोy locked, otherwise रुको
	 * until there are no पढ़ोers
	 */
	अगर (atomic_पढ़ो(&afu->configured_state) != -1) अणु
		जबतक (atomic_cmpxchg(&afu->configured_state, 0, -1) != -1)
			schedule();
	पूर्ण
	cxl_native_release_psl_irq(afu);
	अगर (afu->adapter->native->sl_ops->release_serr_irq)
		afu->adapter->native->sl_ops->release_serr_irq(afu);
	pci_unmap_slice_regs(afu);
पूर्ण

अटल पूर्णांक pci_init_afu(काष्ठा cxl *adapter, पूर्णांक slice, काष्ठा pci_dev *dev)
अणु
	काष्ठा cxl_afu *afu;
	पूर्णांक rc = -ENOMEM;

	afu = cxl_alloc_afu(adapter, slice);
	अगर (!afu)
		वापस -ENOMEM;

	afu->native = kzalloc(माप(काष्ठा cxl_afu_native), GFP_KERNEL);
	अगर (!afu->native)
		जाओ err_मुक्त_afu;

	mutex_init(&afu->native->spa_mutex);

	rc = dev_set_name(&afu->dev, "afu%i.%i", adapter->adapter_num, slice);
	अगर (rc)
		जाओ err_मुक्त_native;

	rc = pci_configure_afu(afu, adapter, dev);
	अगर (rc)
		जाओ err_मुक्त_native;

	/* Don't care अगर this fails */
	cxl_debugfs_afu_add(afu);

	/*
	 * After we call this function we must not मुक्त the afu directly, even
	 * अगर it वापसs an error!
	 */
	अगर ((rc = cxl_रेजिस्टर_afu(afu)))
		जाओ err_put1;

	अगर ((rc = cxl_sysfs_afu_add(afu)))
		जाओ err_put1;

	adapter->afu[afu->slice] = afu;

	अगर ((rc = cxl_pci_vphb_add(afu)))
		dev_info(&afu->dev, "Can't register vPHB\n");

	वापस 0;

err_put1:
	pci_deconfigure_afu(afu);
	cxl_debugfs_afu_हटाओ(afu);
	device_unरेजिस्टर(&afu->dev);
	वापस rc;

err_मुक्त_native:
	kमुक्त(afu->native);
err_मुक्त_afu:
	kमुक्त(afu);
	वापस rc;

पूर्ण

अटल व्योम cxl_pci_हटाओ_afu(काष्ठा cxl_afu *afu)
अणु
	pr_devel("%s\n", __func__);

	अगर (!afu)
		वापस;

	cxl_pci_vphb_हटाओ(afu);
	cxl_sysfs_afu_हटाओ(afu);
	cxl_debugfs_afu_हटाओ(afu);

	spin_lock(&afu->adapter->afu_list_lock);
	afu->adapter->afu[afu->slice] = शून्य;
	spin_unlock(&afu->adapter->afu_list_lock);

	cxl_context_detach_all(afu);
	cxl_ops->afu_deactivate_mode(afu, afu->current_mode);

	pci_deconfigure_afu(afu);
	device_unरेजिस्टर(&afu->dev);
पूर्ण

पूर्णांक cxl_pci_reset(काष्ठा cxl *adapter)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(adapter->dev.parent);
	पूर्णांक rc;

	अगर (adapter->perst_same_image) अणु
		dev_warn(&dev->dev,
			 "cxl: refusing to reset/reflash when perst_reloads_same_image is set.\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(&dev->dev, "CXL reset\n");

	/*
	 * The adapter is about to be reset, so ignore errors.
	 */
	cxl_data_cache_flush(adapter);

	/* pcie_warm_reset requests a fundamental pci reset which includes a
	 * PERST निश्चित/deनिश्चित.  PERST triggers a loading of the image
	 * अगर "user" or "factory" is selected in sysfs */
	अगर ((rc = pci_set_pcie_reset_state(dev, pcie_warm_reset))) अणु
		dev_err(&dev->dev, "cxl: pcie_warm_reset failed\n");
		वापस rc;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक cxl_map_adapter_regs(काष्ठा cxl *adapter, काष्ठा pci_dev *dev)
अणु
	अगर (pci_request_region(dev, 2, "priv 2 regs"))
		जाओ err1;
	अगर (pci_request_region(dev, 0, "priv 1 regs"))
		जाओ err2;

	pr_devel("cxl_map_adapter_regs: p1: %#016llx %#llx, p2: %#016llx %#llx",
			p1_base(dev), p1_size(dev), p2_base(dev), p2_size(dev));

	अगर (!(adapter->native->p1_mmio = ioremap(p1_base(dev), p1_size(dev))))
		जाओ err3;

	अगर (!(adapter->native->p2_mmio = ioremap(p2_base(dev), p2_size(dev))))
		जाओ err4;

	वापस 0;

err4:
	iounmap(adapter->native->p1_mmio);
	adapter->native->p1_mmio = शून्य;
err3:
	pci_release_region(dev, 0);
err2:
	pci_release_region(dev, 2);
err1:
	वापस -ENOMEM;
पूर्ण

अटल व्योम cxl_unmap_adapter_regs(काष्ठा cxl *adapter)
अणु
	अगर (adapter->native->p1_mmio) अणु
		iounmap(adapter->native->p1_mmio);
		adapter->native->p1_mmio = शून्य;
		pci_release_region(to_pci_dev(adapter->dev.parent), 2);
	पूर्ण
	अगर (adapter->native->p2_mmio) अणु
		iounmap(adapter->native->p2_mmio);
		adapter->native->p2_mmio = शून्य;
		pci_release_region(to_pci_dev(adapter->dev.parent), 0);
	पूर्ण
पूर्ण

अटल पूर्णांक cxl_पढ़ो_vsec(काष्ठा cxl *adapter, काष्ठा pci_dev *dev)
अणु
	पूर्णांक vsec;
	u32 afu_desc_off, afu_desc_size;
	u32 ps_off, ps_size;
	u16 vseclen;
	u8 image_state;

	अगर (!(vsec = find_cxl_vsec(dev))) अणु
		dev_err(&dev->dev, "ABORTING: CXL VSEC not found!\n");
		वापस -ENODEV;
	पूर्ण

	CXL_READ_VSEC_LENGTH(dev, vsec, &vseclen);
	अगर (vseclen < CXL_VSEC_MIN_SIZE) अणु
		dev_err(&dev->dev, "ABORTING: CXL VSEC too short\n");
		वापस -EINVAL;
	पूर्ण

	CXL_READ_VSEC_STATUS(dev, vsec, &adapter->vsec_status);
	CXL_READ_VSEC_PSL_REVISION(dev, vsec, &adapter->psl_rev);
	CXL_READ_VSEC_CAIA_MAJOR(dev, vsec, &adapter->caia_major);
	CXL_READ_VSEC_CAIA_MINOR(dev, vsec, &adapter->caia_minor);
	CXL_READ_VSEC_BASE_IMAGE(dev, vsec, &adapter->base_image);
	CXL_READ_VSEC_IMAGE_STATE(dev, vsec, &image_state);
	adapter->user_image_loaded = !!(image_state & CXL_VSEC_USER_IMAGE_LOADED);
	adapter->perst_select_user = !!(image_state & CXL_VSEC_USER_IMAGE_LOADED);
	adapter->perst_loads_image = !!(image_state & CXL_VSEC_PERST_LOADS_IMAGE);

	CXL_READ_VSEC_NAFUS(dev, vsec, &adapter->slices);
	CXL_READ_VSEC_AFU_DESC_OFF(dev, vsec, &afu_desc_off);
	CXL_READ_VSEC_AFU_DESC_SIZE(dev, vsec, &afu_desc_size);
	CXL_READ_VSEC_PS_OFF(dev, vsec, &ps_off);
	CXL_READ_VSEC_PS_SIZE(dev, vsec, &ps_size);

	/* Convert everything to bytes, because there is NO WAY I'd look at the
	 * code a month later and क्रमget what units these are in ;-) */
	adapter->native->ps_off = ps_off * 64 * 1024;
	adapter->ps_size = ps_size * 64 * 1024;
	adapter->native->afu_desc_off = afu_desc_off * 64 * 1024;
	adapter->native->afu_desc_size = afu_desc_size * 64 * 1024;

	/* Total IRQs - 1 PSL ERROR - #AFU*(1 slice error + 1 DSI) */
	adapter->user_irqs = pnv_cxl_get_irq_count(dev) - 1 - 2*adapter->slices;

	वापस 0;
पूर्ण

/*
 * Workaround a PCIe Host Bridge defect on some cards, that can cause
 * malक्रमmed Transaction Layer Packet (TLP) errors to be erroneously
 * reported. Mask this error in the Uncorrectable Error Mask Register.
 *
 * The upper nibble of the PSL revision is used to distinguish between
 * dअगरferent cards. The affected ones have it set to 0.
 */
अटल व्योम cxl_fixup_malक्रमmed_tlp(काष्ठा cxl *adapter, काष्ठा pci_dev *dev)
अणु
	पूर्णांक aer;
	u32 data;

	अगर (adapter->psl_rev & 0xf000)
		वापस;
	अगर (!(aer = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR)))
		वापस;
	pci_पढ़ो_config_dword(dev, aer + PCI_ERR_UNCOR_MASK, &data);
	अगर (data & PCI_ERR_UNC_MALF_TLP)
		अगर (data & PCI_ERR_UNC_INTN)
			वापस;
	data |= PCI_ERR_UNC_MALF_TLP;
	data |= PCI_ERR_UNC_INTN;
	pci_ग_लिखो_config_dword(dev, aer + PCI_ERR_UNCOR_MASK, data);
पूर्ण

अटल bool cxl_compatible_caia_version(काष्ठा cxl *adapter)
अणु
	अगर (cxl_is_घातer8() && (adapter->caia_major == 1))
		वापस true;

	अगर (cxl_is_घातer9() && (adapter->caia_major == 2))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक cxl_vsec_looks_ok(काष्ठा cxl *adapter, काष्ठा pci_dev *dev)
अणु
	अगर (adapter->vsec_status & CXL_STATUS_SECOND_PORT)
		वापस -EBUSY;

	अगर (adapter->vsec_status & CXL_UNSUPPORTED_FEATURES) अणु
		dev_err(&dev->dev, "ABORTING: CXL requires unsupported features\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!cxl_compatible_caia_version(adapter)) अणु
		dev_info(&dev->dev, "Ignoring card. PSL type is not supported (caia version: %d)\n",
			 adapter->caia_major);
		वापस -ENODEV;
	पूर्ण

	अगर (!adapter->slices) अणु
		/* Once we support dynamic reprogramming we can use the card अगर
		 * it supports loadable AFUs */
		dev_err(&dev->dev, "ABORTING: Device has no AFUs\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!adapter->native->afu_desc_off || !adapter->native->afu_desc_size) अणु
		dev_err(&dev->dev, "ABORTING: VSEC shows no AFU descriptors\n");
		वापस -EINVAL;
	पूर्ण

	अगर (adapter->ps_size > p2_size(dev) - adapter->native->ps_off) अणु
		dev_err(&dev->dev, "ABORTING: Problem state size larger than "
				   "available in BAR2: 0x%llx > 0x%llx\n",
			 adapter->ps_size, p2_size(dev) - adapter->native->ps_off);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

sमाप_प्रकार cxl_pci_पढ़ो_adapter_vpd(काष्ठा cxl *adapter, व्योम *buf, माप_प्रकार len)
अणु
	वापस pci_पढ़ो_vpd(to_pci_dev(adapter->dev.parent), 0, len, buf);
पूर्ण

अटल व्योम cxl_release_adapter(काष्ठा device *dev)
अणु
	काष्ठा cxl *adapter = to_cxl_adapter(dev);

	pr_devel("cxl_release_adapter\n");

	cxl_हटाओ_adapter_nr(adapter);

	kमुक्त(adapter->native);
	kमुक्त(adapter);
पूर्ण

#घोषणा CXL_PSL_ErrIVTE_tberror (0x1ull << (63-31))

अटल पूर्णांक sanitise_adapter_regs(काष्ठा cxl *adapter)
अणु
	पूर्णांक rc = 0;

	/* Clear PSL tberror bit by writing 1 to it */
	cxl_p1_ग_लिखो(adapter, CXL_PSL_ErrIVTE, CXL_PSL_ErrIVTE_tberror);

	अगर (adapter->native->sl_ops->invalidate_all) अणु
		/* करो not invalidate ERAT entries when not reloading on PERST */
		अगर (cxl_is_घातer9() && (adapter->perst_loads_image))
			वापस 0;
		rc = adapter->native->sl_ops->invalidate_all(adapter);
	पूर्ण

	वापस rc;
पूर्ण

/* This should contain *only* operations that can safely be करोne in
 * both creation and recovery.
 */
अटल पूर्णांक cxl_configure_adapter(काष्ठा cxl *adapter, काष्ठा pci_dev *dev)
अणु
	पूर्णांक rc;

	adapter->dev.parent = &dev->dev;
	adapter->dev.release = cxl_release_adapter;
	pci_set_drvdata(dev, adapter);

	rc = pci_enable_device(dev);
	अगर (rc) अणु
		dev_err(&dev->dev, "pci_enable_device failed: %i\n", rc);
		वापस rc;
	पूर्ण

	अगर ((rc = cxl_पढ़ो_vsec(adapter, dev)))
		वापस rc;

	अगर ((rc = cxl_vsec_looks_ok(adapter, dev)))
	        वापस rc;

	cxl_fixup_malक्रमmed_tlp(adapter, dev);

	अगर ((rc = setup_cxl_bars(dev)))
		वापस rc;

	अगर ((rc = चयन_card_to_cxl(dev)))
		वापस rc;

	अगर ((rc = cxl_update_image_control(adapter)))
		वापस rc;

	अगर ((rc = cxl_map_adapter_regs(adapter, dev)))
		वापस rc;

	अगर ((rc = sanitise_adapter_regs(adapter)))
		जाओ err;

	अगर ((rc = adapter->native->sl_ops->adapter_regs_init(adapter, dev)))
		जाओ err;

	/* Required क्रम devices using CAPP DMA mode, harmless क्रम others */
	pci_set_master(dev);

	adapter->tunneled_ops_supported = false;

	अगर (cxl_is_घातer9()) अणु
		अगर (pnv_pci_set_tunnel_bar(dev, 0x00020000E0000000ull, 1))
			dev_info(&dev->dev, "Tunneled operations unsupported\n");
		अन्यथा
			adapter->tunneled_ops_supported = true;
	पूर्ण

	अगर ((rc = pnv_phb_to_cxl_mode(dev, adapter->native->sl_ops->capi_mode)))
		जाओ err;

	/* If recovery happened, the last step is to turn on snooping.
	 * In the non-recovery हाल this has no effect */
	अगर ((rc = pnv_phb_to_cxl_mode(dev, OPAL_PHB_CAPI_MODE_SNOOP_ON)))
		जाओ err;

	/* Ignore error, adapter init is not dependant on समयbase sync */
	cxl_setup_psl_समयbase(adapter, dev);

	अगर ((rc = cxl_native_रेजिस्टर_psl_err_irq(adapter)))
		जाओ err;

	वापस 0;

err:
	cxl_unmap_adapter_regs(adapter);
	वापस rc;

पूर्ण

अटल व्योम cxl_deconfigure_adapter(काष्ठा cxl *adapter)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(adapter->dev.parent);

	अगर (cxl_is_घातer9())
		pnv_pci_set_tunnel_bar(pdev, 0x00020000E0000000ull, 0);

	cxl_native_release_psl_err_irq(adapter);
	cxl_unmap_adapter_regs(adapter);

	pci_disable_device(pdev);
पूर्ण

अटल व्योम cxl_stop_trace_psl9(काष्ठा cxl *adapter)
अणु
	पूर्णांक traceid;
	u64 trace_state, trace_mask;
	काष्ठा pci_dev *dev = to_pci_dev(adapter->dev.parent);

	/* पढ़ो each tracearray state and issue mmio to stop them is needed */
	क्रम (traceid = 0; traceid <= CXL_PSL9_TRACEID_MAX; ++traceid) अणु
		trace_state = cxl_p1_पढ़ो(adapter, CXL_PSL9_CTCCFG);
		trace_mask = (0x3ULL << (62 - traceid * 2));
		trace_state = (trace_state & trace_mask) >> (62 - traceid * 2);
		dev_dbg(&dev->dev, "cxl: Traceid-%d trace_state=0x%0llX\n",
			traceid, trace_state);

		/* issue mmio अगर the trace array isn't in FIN state */
		अगर (trace_state != CXL_PSL9_TRACESTATE_FIN)
			cxl_p1_ग_लिखो(adapter, CXL_PSL9_TRACECFG,
				     0x8400000000000000ULL | traceid);
	पूर्ण
पूर्ण

अटल व्योम cxl_stop_trace_psl8(काष्ठा cxl *adapter)
अणु
	पूर्णांक slice;

	/* Stop the trace */
	cxl_p1_ग_लिखो(adapter, CXL_PSL_TRACE, 0x8000000000000017LL);

	/* Stop the slice traces */
	spin_lock(&adapter->afu_list_lock);
	क्रम (slice = 0; slice < adapter->slices; slice++) अणु
		अगर (adapter->afu[slice])
			cxl_p1n_ग_लिखो(adapter->afu[slice], CXL_PSL_SLICE_TRACE,
				      0x8000000000000000LL);
	पूर्ण
	spin_unlock(&adapter->afu_list_lock);
पूर्ण

अटल स्थिर काष्ठा cxl_service_layer_ops psl9_ops = अणु
	.adapter_regs_init = init_implementation_adapter_regs_psl9,
	.invalidate_all = cxl_invalidate_all_psl9,
	.afu_regs_init = init_implementation_afu_regs_psl9,
	.sanitise_afu_regs = sanitise_afu_regs_psl9,
	.रेजिस्टर_serr_irq = cxl_native_रेजिस्टर_serr_irq,
	.release_serr_irq = cxl_native_release_serr_irq,
	.handle_पूर्णांकerrupt = cxl_irq_psl9,
	.fail_irq = cxl_fail_irq_psl,
	.activate_dedicated_process = cxl_activate_dedicated_process_psl9,
	.attach_afu_directed = cxl_attach_afu_directed_psl9,
	.attach_dedicated_process = cxl_attach_dedicated_process_psl9,
	.update_dedicated_ivtes = cxl_update_dedicated_ivtes_psl9,
	.debugfs_add_adapter_regs = cxl_debugfs_add_adapter_regs_psl9,
	.debugfs_add_afu_regs = cxl_debugfs_add_afu_regs_psl9,
	.psl_irq_dump_रेजिस्टरs = cxl_native_irq_dump_regs_psl9,
	.err_irq_dump_रेजिस्टरs = cxl_native_err_irq_dump_regs_psl9,
	.debugfs_stop_trace = cxl_stop_trace_psl9,
	.समयbase_पढ़ो = समयbase_पढ़ो_psl9,
	.capi_mode = OPAL_PHB_CAPI_MODE_CAPI,
	.needs_reset_beक्रमe_disable = true,
पूर्ण;

अटल स्थिर काष्ठा cxl_service_layer_ops psl8_ops = अणु
	.adapter_regs_init = init_implementation_adapter_regs_psl8,
	.invalidate_all = cxl_invalidate_all_psl8,
	.afu_regs_init = init_implementation_afu_regs_psl8,
	.sanitise_afu_regs = sanitise_afu_regs_psl8,
	.रेजिस्टर_serr_irq = cxl_native_रेजिस्टर_serr_irq,
	.release_serr_irq = cxl_native_release_serr_irq,
	.handle_पूर्णांकerrupt = cxl_irq_psl8,
	.fail_irq = cxl_fail_irq_psl,
	.activate_dedicated_process = cxl_activate_dedicated_process_psl8,
	.attach_afu_directed = cxl_attach_afu_directed_psl8,
	.attach_dedicated_process = cxl_attach_dedicated_process_psl8,
	.update_dedicated_ivtes = cxl_update_dedicated_ivtes_psl8,
	.debugfs_add_adapter_regs = cxl_debugfs_add_adapter_regs_psl8,
	.debugfs_add_afu_regs = cxl_debugfs_add_afu_regs_psl8,
	.psl_irq_dump_रेजिस्टरs = cxl_native_irq_dump_regs_psl8,
	.err_irq_dump_रेजिस्टरs = cxl_native_err_irq_dump_regs_psl8,
	.debugfs_stop_trace = cxl_stop_trace_psl8,
	.ग_लिखो_समयbase_ctrl = ग_लिखो_समयbase_ctrl_psl8,
	.समयbase_पढ़ो = समयbase_पढ़ो_psl8,
	.capi_mode = OPAL_PHB_CAPI_MODE_CAPI,
	.needs_reset_beक्रमe_disable = true,
पूर्ण;

अटल व्योम set_sl_ops(काष्ठा cxl *adapter, काष्ठा pci_dev *dev)
अणु
	अगर (cxl_is_घातer8()) अणु
		dev_info(&dev->dev, "Device uses a PSL8\n");
		adapter->native->sl_ops = &psl8_ops;
	पूर्ण अन्यथा अणु
		dev_info(&dev->dev, "Device uses a PSL9\n");
		adapter->native->sl_ops = &psl9_ops;
	पूर्ण
पूर्ण


अटल काष्ठा cxl *cxl_pci_init_adapter(काष्ठा pci_dev *dev)
अणु
	काष्ठा cxl *adapter;
	पूर्णांक rc;

	adapter = cxl_alloc_adapter();
	अगर (!adapter)
		वापस ERR_PTR(-ENOMEM);

	adapter->native = kzalloc(माप(काष्ठा cxl_native), GFP_KERNEL);
	अगर (!adapter->native) अणु
		rc = -ENOMEM;
		जाओ err_release;
	पूर्ण

	set_sl_ops(adapter, dev);

	/* Set शेषs क्रम parameters which need to persist over
	 * configure/reconfigure
	 */
	adapter->perst_loads_image = true;
	adapter->perst_same_image = false;

	rc = cxl_configure_adapter(adapter, dev);
	अगर (rc) अणु
		pci_disable_device(dev);
		जाओ err_release;
	पूर्ण

	/* Don't care अगर this one fails: */
	cxl_debugfs_adapter_add(adapter);

	/*
	 * After we call this function we must not मुक्त the adapter directly,
	 * even अगर it वापसs an error!
	 */
	अगर ((rc = cxl_रेजिस्टर_adapter(adapter)))
		जाओ err_put1;

	अगर ((rc = cxl_sysfs_adapter_add(adapter)))
		जाओ err_put1;

	/* Release the context lock as adapter is configured */
	cxl_adapter_context_unlock(adapter);

	वापस adapter;

err_put1:
	/* This should mirror cxl_हटाओ_adapter, except without the
	 * sysfs parts
	 */
	cxl_debugfs_adapter_हटाओ(adapter);
	cxl_deconfigure_adapter(adapter);
	device_unरेजिस्टर(&adapter->dev);
	वापस ERR_PTR(rc);

err_release:
	cxl_release_adapter(&adapter->dev);
	वापस ERR_PTR(rc);
पूर्ण

अटल व्योम cxl_pci_हटाओ_adapter(काष्ठा cxl *adapter)
अणु
	pr_devel("cxl_remove_adapter\n");

	cxl_sysfs_adapter_हटाओ(adapter);
	cxl_debugfs_adapter_हटाओ(adapter);

	/*
	 * Flush adapter datacache as its about to be हटाओd.
	 */
	cxl_data_cache_flush(adapter);

	cxl_deconfigure_adapter(adapter);

	device_unरेजिस्टर(&adapter->dev);
पूर्ण

#घोषणा CXL_MAX_PCIEX_PARENT 2

पूर्णांक cxl_slot_is_चयनed(काष्ठा pci_dev *dev)
अणु
	काष्ठा device_node *np;
	पूर्णांक depth = 0;

	अगर (!(np = pci_device_to_OF_node(dev))) अणु
		pr_err("cxl: np = NULL\n");
		वापस -ENODEV;
	पूर्ण
	of_node_get(np);
	जबतक (np) अणु
		np = of_get_next_parent(np);
		अगर (!of_node_is_type(np, "pciex"))
			अवरोध;
		depth++;
	पूर्ण
	of_node_put(np);
	वापस (depth > CXL_MAX_PCIEX_PARENT);
पूर्ण

अटल पूर्णांक cxl_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा cxl *adapter;
	पूर्णांक slice;
	पूर्णांक rc;

	अगर (cxl_pci_is_vphb_device(dev)) अणु
		dev_dbg(&dev->dev, "cxl_init_adapter: Ignoring cxl vphb device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (cxl_slot_is_चयनed(dev)) अणु
		dev_info(&dev->dev, "Ignoring card on incompatible PCI slot\n");
		वापस -ENODEV;
	पूर्ण

	अगर (cxl_is_घातer9() && !radix_enabled()) अणु
		dev_info(&dev->dev, "Only Radix mode supported\n");
		वापस -ENODEV;
	पूर्ण

	अगर (cxl_verbose)
		dump_cxl_config_space(dev);

	adapter = cxl_pci_init_adapter(dev);
	अगर (IS_ERR(adapter)) अणु
		dev_err(&dev->dev, "cxl_init_adapter failed: %li\n", PTR_ERR(adapter));
		वापस PTR_ERR(adapter);
	पूर्ण

	क्रम (slice = 0; slice < adapter->slices; slice++) अणु
		अगर ((rc = pci_init_afu(adapter, slice, dev))) अणु
			dev_err(&dev->dev, "AFU %i failed to initialise: %i\n", slice, rc);
			जारी;
		पूर्ण

		rc = cxl_afu_select_best_mode(adapter->afu[slice]);
		अगर (rc)
			dev_err(&dev->dev, "AFU %i failed to start: %i\n", slice, rc);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cxl_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा cxl *adapter = pci_get_drvdata(dev);
	काष्ठा cxl_afu *afu;
	पूर्णांक i;

	/*
	 * Lock to prevent someone grabbing a ref through the adapter list as
	 * we are removing it
	 */
	क्रम (i = 0; i < adapter->slices; i++) अणु
		afu = adapter->afu[i];
		cxl_pci_हटाओ_afu(afu);
	पूर्ण
	cxl_pci_हटाओ_adapter(adapter);
पूर्ण

अटल pci_ers_result_t cxl_vphb_error_detected(काष्ठा cxl_afu *afu,
						pci_channel_state_t state)
अणु
	काष्ठा pci_dev *afu_dev;
	pci_ers_result_t result = PCI_ERS_RESULT_NEED_RESET;
	pci_ers_result_t afu_result = PCI_ERS_RESULT_NEED_RESET;

	/* There should only be one entry, but go through the list
	 * anyway
	 */
	अगर (afu == शून्य || afu->phb == शून्य)
		वापस result;

	list_क्रम_each_entry(afu_dev, &afu->phb->bus->devices, bus_list) अणु
		अगर (!afu_dev->driver)
			जारी;

		afu_dev->error_state = state;

		अगर (afu_dev->driver->err_handler)
			afu_result = afu_dev->driver->err_handler->error_detected(afu_dev,
										  state);
		/* Disconnect trumps all, NONE trumps NEED_RESET */
		अगर (afu_result == PCI_ERS_RESULT_DISCONNECT)
			result = PCI_ERS_RESULT_DISCONNECT;
		अन्यथा अगर ((afu_result == PCI_ERS_RESULT_NONE) &&
			 (result == PCI_ERS_RESULT_NEED_RESET))
			result = PCI_ERS_RESULT_NONE;
	पूर्ण
	वापस result;
पूर्ण

अटल pci_ers_result_t cxl_pci_error_detected(काष्ठा pci_dev *pdev,
					       pci_channel_state_t state)
अणु
	काष्ठा cxl *adapter = pci_get_drvdata(pdev);
	काष्ठा cxl_afu *afu;
	pci_ers_result_t result = PCI_ERS_RESULT_NEED_RESET;
	pci_ers_result_t afu_result = PCI_ERS_RESULT_NEED_RESET;
	पूर्णांक i;

	/* At this poपूर्णांक, we could still have an पूर्णांकerrupt pending.
	 * Let's try to get them out of the way beक्रमe they करो
	 * anything we करोn't like.
	 */
	schedule();

	/* If we're permanently dead, give up. */
	अगर (state == pci_channel_io_perm_failure) अणु
		spin_lock(&adapter->afu_list_lock);
		क्रम (i = 0; i < adapter->slices; i++) अणु
			afu = adapter->afu[i];
			/*
			 * Tell the AFU drivers; but we करोn't care what they
			 * say, we're going away.
			 */
			cxl_vphb_error_detected(afu, state);
		पूर्ण
		spin_unlock(&adapter->afu_list_lock);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	/* Are we reflashing?
	 *
	 * If we reflash, we could come back as something entirely
	 * dअगरferent, including a non-CAPI card. As such, by शेष
	 * we करोn't participate in the process. We'll be unbound and
	 * the slot re-probed. (TODO: check EEH करोesn't blindly rebind
	 * us!)
	 *
	 * However, this isn't the entire story: क्रम reliablity
	 * reasons, we usually want to reflash the FPGA on PERST in
	 * order to get back to a more reliable known-good state.
	 *
	 * This causes us a bit of a problem: अगर we reflash we can't
	 * trust that we'll come back the same - we could have a new
	 * image and been PERSTed in order to load that
	 * image. However, most of the समय we actually *will* come
	 * back the same - क्रम example a regular EEH event.
	 *
	 * Thereक्रमe, we allow the user to निश्चित that the image is
	 * indeed the same and that we should जारी on पूर्णांकo EEH
	 * anyway.
	 */
	अगर (adapter->perst_loads_image && !adapter->perst_same_image) अणु
		/* TODO take the PHB out of CXL mode */
		dev_info(&pdev->dev, "reflashing, so opting out of EEH!\n");
		वापस PCI_ERS_RESULT_NONE;
	पूर्ण

	/*
	 * At this poपूर्णांक, we want to try to recover.  We'll always
	 * need a complete slot reset: we करोn't trust any other reset.
	 *
	 * Now, we go through each AFU:
	 *  - We send the driver, अगर bound, an error_detected callback.
	 *    We expect it to clean up, but it can also tell us to give
	 *    up and permanently detach the card. To simplअगरy things, अगर
	 *    any bound AFU driver करोesn't support EEH, we give up on EEH.
	 *
	 *  - We detach all contexts associated with the AFU. This
	 *    करोes not मुक्त them, but माला_दो them पूर्णांकo a CLOSED state
	 *    which causes any the associated files to वापस useful
	 *    errors to userland. It also unmaps, but करोes not मुक्त,
	 *    any IRQs.
	 *
	 *  - We clean up our side: releasing and unmapping resources we hold
	 *    so we can wire them up again when the hardware comes back up.
	 *
	 * Driver authors should note:
	 *
	 *  - Any contexts you create in your kernel driver (except
	 *    those associated with anonymous file descriptors) are
	 *    your responsibility to मुक्त and recreate. Likewise with
	 *    any attached resources.
	 *
	 *  - We will take responsibility क्रम re-initialising the
	 *    device context (the one set up क्रम you in
	 *    cxl_pci_enable_device_hook and accessed through
	 *    cxl_get_context). If you've attached IRQs or other
	 *    resources to it, they reमुख्यs yours to मुक्त.
	 *
	 * You can call the same functions to release resources as you
	 * normally would: we make sure that these functions जारी
	 * to work when the hardware is करोwn.
	 *
	 * Two examples:
	 *
	 * 1) If you normally मुक्त all your resources at the end of
	 *    each request, or अगर you use anonymous FDs, your
	 *    error_detected callback can simply set a flag to tell
	 *    your driver not to start any new calls. You can then
	 *    clear the flag in the resume callback.
	 *
	 * 2) If you normally allocate your resources on startup:
	 *     * Set a flag in error_detected as above.
	 *     * Let CXL detach your contexts.
	 *     * In slot_reset, मुक्त the old resources and allocate new ones.
	 *     * In resume, clear the flag to allow things to start.
	 */

	/* Make sure no one अन्यथा changes the afu list */
	spin_lock(&adapter->afu_list_lock);

	क्रम (i = 0; i < adapter->slices; i++) अणु
		afu = adapter->afu[i];

		अगर (afu == शून्य)
			जारी;

		afu_result = cxl_vphb_error_detected(afu, state);
		cxl_context_detach_all(afu);
		cxl_ops->afu_deactivate_mode(afu, afu->current_mode);
		pci_deconfigure_afu(afu);

		/* Disconnect trumps all, NONE trumps NEED_RESET */
		अगर (afu_result == PCI_ERS_RESULT_DISCONNECT)
			result = PCI_ERS_RESULT_DISCONNECT;
		अन्यथा अगर ((afu_result == PCI_ERS_RESULT_NONE) &&
			 (result == PCI_ERS_RESULT_NEED_RESET))
			result = PCI_ERS_RESULT_NONE;
	पूर्ण
	spin_unlock(&adapter->afu_list_lock);

	/* should take the context lock here */
	अगर (cxl_adapter_context_lock(adapter) != 0)
		dev_warn(&adapter->dev,
			 "Couldn't take context lock with %d active-contexts\n",
			 atomic_पढ़ो(&adapter->contexts_num));

	cxl_deconfigure_adapter(adapter);

	वापस result;
पूर्ण

अटल pci_ers_result_t cxl_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cxl *adapter = pci_get_drvdata(pdev);
	काष्ठा cxl_afu *afu;
	काष्ठा cxl_context *ctx;
	काष्ठा pci_dev *afu_dev;
	pci_ers_result_t afu_result = PCI_ERS_RESULT_RECOVERED;
	pci_ers_result_t result = PCI_ERS_RESULT_RECOVERED;
	पूर्णांक i;

	अगर (cxl_configure_adapter(adapter, pdev))
		जाओ err;

	/*
	 * Unlock context activation क्रम the adapter. Ideally this should be
	 * करोne in cxl_pci_resume but cxlflash module tries to activate the
	 * master context as part of slot_reset callback.
	 */
	cxl_adapter_context_unlock(adapter);

	spin_lock(&adapter->afu_list_lock);
	क्रम (i = 0; i < adapter->slices; i++) अणु
		afu = adapter->afu[i];

		अगर (afu == शून्य)
			जारी;

		अगर (pci_configure_afu(afu, adapter, pdev))
			जाओ err_unlock;

		अगर (cxl_afu_select_best_mode(afu))
			जाओ err_unlock;

		अगर (afu->phb == शून्य)
			जारी;

		list_क्रम_each_entry(afu_dev, &afu->phb->bus->devices, bus_list) अणु
			/* Reset the device context.
			 * TODO: make this less disruptive
			 */
			ctx = cxl_get_context(afu_dev);

			अगर (ctx && cxl_release_context(ctx))
				जाओ err_unlock;

			ctx = cxl_dev_context_init(afu_dev);
			अगर (IS_ERR(ctx))
				जाओ err_unlock;

			afu_dev->dev.archdata.cxl_ctx = ctx;

			अगर (cxl_ops->afu_check_and_enable(afu))
				जाओ err_unlock;

			afu_dev->error_state = pci_channel_io_normal;

			/* If there's a driver attached, allow it to
			 * chime in on recovery. Drivers should check
			 * अगर everything has come back OK, but
			 * shouldn't start new work until we call
			 * their resume function.
			 */
			अगर (!afu_dev->driver)
				जारी;

			अगर (afu_dev->driver->err_handler &&
			    afu_dev->driver->err_handler->slot_reset)
				afu_result = afu_dev->driver->err_handler->slot_reset(afu_dev);

			अगर (afu_result == PCI_ERS_RESULT_DISCONNECT)
				result = PCI_ERS_RESULT_DISCONNECT;
		पूर्ण
	पूर्ण

	spin_unlock(&adapter->afu_list_lock);
	वापस result;

err_unlock:
	spin_unlock(&adapter->afu_list_lock);

err:
	/* All the bits that happen in both error_detected and cxl_हटाओ
	 * should be idempotent, so we करोn't need to worry about leaving a mix
	 * of unconfigured and reconfigured resources.
	 */
	dev_err(&pdev->dev, "EEH recovery failed. Asking to be disconnected.\n");
	वापस PCI_ERS_RESULT_DISCONNECT;
पूर्ण

अटल व्योम cxl_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cxl *adapter = pci_get_drvdata(pdev);
	काष्ठा cxl_afu *afu;
	काष्ठा pci_dev *afu_dev;
	पूर्णांक i;

	/* Everything is back now. Drivers should restart work now.
	 * This is not the place to be checking अगर everything came back up
	 * properly, because there's no वापस value: करो that in slot_reset.
	 */
	spin_lock(&adapter->afu_list_lock);
	क्रम (i = 0; i < adapter->slices; i++) अणु
		afu = adapter->afu[i];

		अगर (afu == शून्य || afu->phb == शून्य)
			जारी;

		list_क्रम_each_entry(afu_dev, &afu->phb->bus->devices, bus_list) अणु
			अगर (afu_dev->driver && afu_dev->driver->err_handler &&
			    afu_dev->driver->err_handler->resume)
				afu_dev->driver->err_handler->resume(afu_dev);
		पूर्ण
	पूर्ण
	spin_unlock(&adapter->afu_list_lock);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers cxl_err_handler = अणु
	.error_detected = cxl_pci_error_detected,
	.slot_reset = cxl_pci_slot_reset,
	.resume = cxl_pci_resume,
पूर्ण;

काष्ठा pci_driver cxl_pci_driver = अणु
	.name = "cxl-pci",
	.id_table = cxl_pci_tbl,
	.probe = cxl_probe,
	.हटाओ = cxl_हटाओ,
	.shutकरोwn = cxl_हटाओ,
	.err_handler = &cxl_err_handler,
पूर्ण;
