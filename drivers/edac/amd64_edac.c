<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश "amd64_edac.h"
#समावेश <यंत्र/amd_nb.h>

अटल काष्ठा edac_pci_ctl_info *pci_ctl;

/*
 * Set by command line parameter. If BIOS has enabled the ECC, this override is
 * cleared to prevent re-enabling the hardware by this driver.
 */
अटल पूर्णांक ecc_enable_override;
module_param(ecc_enable_override, पूर्णांक, 0644);

अटल काष्ठा msr __percpu *msrs;

अटल काष्ठा amd64_family_type *fam_type;

/* Per-node stuff */
अटल काष्ठा ecc_settings **ecc_stngs;

/* Device क्रम the PCI component */
अटल काष्ठा device *pci_ctl_dev;

/*
 * Valid scrub rates क्रम the K8 hardware memory scrubber. We map the scrubbing
 * bandwidth to a valid bit pattern. The 'set' operation finds the 'matching-
 * or higher value'.
 *
 *FIXME: Produce a better mapping/linearisation.
 */
अटल स्थिर काष्ठा scrubrate अणु
       u32 scrubval;           /* bit pattern क्रम scrub rate */
       u32 bandwidth;          /* bandwidth consumed (bytes/sec) */
पूर्ण scrubrates[] = अणु
	अणु 0x01, 1600000000ULपूर्ण,
	अणु 0x02, 800000000ULपूर्ण,
	अणु 0x03, 400000000ULपूर्ण,
	अणु 0x04, 200000000ULपूर्ण,
	अणु 0x05, 100000000ULपूर्ण,
	अणु 0x06, 50000000ULपूर्ण,
	अणु 0x07, 25000000ULपूर्ण,
	अणु 0x08, 12284069ULपूर्ण,
	अणु 0x09, 6274509ULपूर्ण,
	अणु 0x0A, 3121951ULपूर्ण,
	अणु 0x0B, 1560975ULपूर्ण,
	अणु 0x0C, 781440ULपूर्ण,
	अणु 0x0D, 390720ULपूर्ण,
	अणु 0x0E, 195300ULपूर्ण,
	अणु 0x0F, 97650ULपूर्ण,
	अणु 0x10, 48854ULपूर्ण,
	अणु 0x11, 24427ULपूर्ण,
	अणु 0x12, 12213ULपूर्ण,
	अणु 0x13, 6101ULपूर्ण,
	अणु 0x14, 3051ULपूर्ण,
	अणु 0x15, 1523ULपूर्ण,
	अणु 0x16, 761ULपूर्ण,
	अणु 0x00, 0ULपूर्ण,        /* scrubbing off */
पूर्ण;

पूर्णांक __amd64_पढ़ो_pci_cfg_dword(काष्ठा pci_dev *pdev, पूर्णांक offset,
			       u32 *val, स्थिर अक्षर *func)
अणु
	पूर्णांक err = 0;

	err = pci_पढ़ो_config_dword(pdev, offset, val);
	अगर (err)
		amd64_warn("%s: error reading F%dx%03x.\n",
			   func, PCI_FUNC(pdev->devfn), offset);

	वापस err;
पूर्ण

पूर्णांक __amd64_ग_लिखो_pci_cfg_dword(काष्ठा pci_dev *pdev, पूर्णांक offset,
				u32 val, स्थिर अक्षर *func)
अणु
	पूर्णांक err = 0;

	err = pci_ग_लिखो_config_dword(pdev, offset, val);
	अगर (err)
		amd64_warn("%s: error writing to F%dx%03x.\n",
			   func, PCI_FUNC(pdev->devfn), offset);

	वापस err;
पूर्ण

/*
 * Select DCT to which PCI cfg accesses are routed
 */
अटल व्योम f15h_select_dct(काष्ठा amd64_pvt *pvt, u8 dct)
अणु
	u32 reg = 0;

	amd64_पढ़ो_pci_cfg(pvt->F1, DCT_CFG_SEL, &reg);
	reg &= (pvt->model == 0x30) ? ~3 : ~1;
	reg |= dct;
	amd64_ग_लिखो_pci_cfg(pvt->F1, DCT_CFG_SEL, reg);
पूर्ण

/*
 *
 * Depending on the family, F2 DCT पढ़ोs need special handling:
 *
 * K8: has a single DCT only and no address offsets >= 0x100
 *
 * F10h: each DCT has its own set of regs
 *	DCT0 -> F2x040..
 *	DCT1 -> F2x140..
 *
 * F16h: has only 1 DCT
 *
 * F15h: we select which DCT we access using F1x10C[DctCfgSel]
 */
अटल अंतरभूत पूर्णांक amd64_पढ़ो_dct_pci_cfg(काष्ठा amd64_pvt *pvt, u8 dct,
					 पूर्णांक offset, u32 *val)
अणु
	चयन (pvt->fam) अणु
	हाल 0xf:
		अगर (dct || offset >= 0x100)
			वापस -EINVAL;
		अवरोध;

	हाल 0x10:
		अगर (dct) अणु
			/*
			 * Note: If ganging is enabled, barring the regs
			 * F2x[1,0]98 and F2x[1,0]9C; पढ़ोs पढ़ोs to F2x1xx
			 * वापस 0. (cf. Section 2.8.1 F10h BKDG)
			 */
			अगर (dct_ganging_enabled(pvt))
				वापस 0;

			offset += 0x100;
		पूर्ण
		अवरोध;

	हाल 0x15:
		/*
		 * F15h: F2x1xx addresses करो not map explicitly to DCT1.
		 * We should select which DCT we access using F1x10C[DctCfgSel]
		 */
		dct = (dct && pvt->model == 0x30) ? 3 : dct;
		f15h_select_dct(pvt, dct);
		अवरोध;

	हाल 0x16:
		अगर (dct)
			वापस -EINVAL;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस amd64_पढ़ो_pci_cfg(pvt->F2, offset, val);
पूर्ण

/*
 * Memory scrubber control पूर्णांकerface. For K8, memory scrubbing is handled by
 * hardware and can involve L2 cache, dcache as well as the मुख्य memory. With
 * F10, this is extended to L3 cache scrubbing on CPU models sporting that
 * functionality.
 *
 * This causes the "units" क्रम the scrubbing speed to vary from 64 byte blocks
 * (dram) over to cache lines. This is nasty, so we will use bandwidth in
 * bytes/sec क्रम the setting.
 *
 * Currently, we only करो dram scrubbing. If the scrubbing is करोne in software on
 * other archs, we might not have access to the caches directly.
 */

अटल अंतरभूत व्योम __f17h_set_scrubval(काष्ठा amd64_pvt *pvt, u32 scrubval)
अणु
	/*
	 * Fam17h supports scrub values between 0x5 and 0x14. Also, the values
	 * are shअगरted करोwn by 0x5, so scrubval 0x5 is written to the रेजिस्टर
	 * as 0x0, scrubval 0x6 as 0x1, etc.
	 */
	अगर (scrubval >= 0x5 && scrubval <= 0x14) अणु
		scrubval -= 0x5;
		pci_ग_लिखो_bits32(pvt->F6, F17H_SCR_LIMIT_ADDR, scrubval, 0xF);
		pci_ग_लिखो_bits32(pvt->F6, F17H_SCR_BASE_ADDR, 1, 0x1);
	पूर्ण अन्यथा अणु
		pci_ग_लिखो_bits32(pvt->F6, F17H_SCR_BASE_ADDR, 0, 0x1);
	पूर्ण
पूर्ण
/*
 * Scan the scrub rate mapping table क्रम a बंद or matching bandwidth value to
 * issue. If requested is too big, then use last maximum value found.
 */
अटल पूर्णांक __set_scrub_rate(काष्ठा amd64_pvt *pvt, u32 new_bw, u32 min_rate)
अणु
	u32 scrubval;
	पूर्णांक i;

	/*
	 * map the configured rate (new_bw) to a value specअगरic to the AMD64
	 * memory controller and apply to रेजिस्टर. Search क्रम the first
	 * bandwidth entry that is greater or equal than the setting requested
	 * and program that. If at last entry, turn off DRAM scrubbing.
	 *
	 * If no suitable bandwidth is found, turn off DRAM scrubbing entirely
	 * by falling back to the last element in scrubrates[].
	 */
	क्रम (i = 0; i < ARRAY_SIZE(scrubrates) - 1; i++) अणु
		/*
		 * skip scrub rates which aren't recommended
		 * (see F10 BKDG, F3x58)
		 */
		अगर (scrubrates[i].scrubval < min_rate)
			जारी;

		अगर (scrubrates[i].bandwidth <= new_bw)
			अवरोध;
	पूर्ण

	scrubval = scrubrates[i].scrubval;

	अगर (pvt->umc) अणु
		__f17h_set_scrubval(pvt, scrubval);
	पूर्ण अन्यथा अगर (pvt->fam == 0x15 && pvt->model == 0x60) अणु
		f15h_select_dct(pvt, 0);
		pci_ग_लिखो_bits32(pvt->F2, F15H_M60H_SCRCTRL, scrubval, 0x001F);
		f15h_select_dct(pvt, 1);
		pci_ग_लिखो_bits32(pvt->F2, F15H_M60H_SCRCTRL, scrubval, 0x001F);
	पूर्ण अन्यथा अणु
		pci_ग_लिखो_bits32(pvt->F3, SCRCTRL, scrubval, 0x001F);
	पूर्ण

	अगर (scrubval)
		वापस scrubrates[i].bandwidth;

	वापस 0;
पूर्ण

अटल पूर्णांक set_scrub_rate(काष्ठा mem_ctl_info *mci, u32 bw)
अणु
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	u32 min_scrubrate = 0x5;

	अगर (pvt->fam == 0xf)
		min_scrubrate = 0x0;

	अगर (pvt->fam == 0x15) अणु
		/* Erratum #505 */
		अगर (pvt->model < 0x10)
			f15h_select_dct(pvt, 0);

		अगर (pvt->model == 0x60)
			min_scrubrate = 0x6;
	पूर्ण
	वापस __set_scrub_rate(pvt, bw, min_scrubrate);
पूर्ण

अटल पूर्णांक get_scrub_rate(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	पूर्णांक i, retval = -EINVAL;
	u32 scrubval = 0;

	अगर (pvt->umc) अणु
		amd64_पढ़ो_pci_cfg(pvt->F6, F17H_SCR_BASE_ADDR, &scrubval);
		अगर (scrubval & BIT(0)) अणु
			amd64_पढ़ो_pci_cfg(pvt->F6, F17H_SCR_LIMIT_ADDR, &scrubval);
			scrubval &= 0xF;
			scrubval += 0x5;
		पूर्ण अन्यथा अणु
			scrubval = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (pvt->fam == 0x15) अणु
		/* Erratum #505 */
		अगर (pvt->model < 0x10)
			f15h_select_dct(pvt, 0);

		अगर (pvt->model == 0x60)
			amd64_पढ़ो_pci_cfg(pvt->F2, F15H_M60H_SCRCTRL, &scrubval);
		अन्यथा
			amd64_पढ़ो_pci_cfg(pvt->F3, SCRCTRL, &scrubval);
	पूर्ण अन्यथा अणु
		amd64_पढ़ो_pci_cfg(pvt->F3, SCRCTRL, &scrubval);
	पूर्ण

	scrubval = scrubval & 0x001F;

	क्रम (i = 0; i < ARRAY_SIZE(scrubrates); i++) अणु
		अगर (scrubrates[i].scrubval == scrubval) अणु
			retval = scrubrates[i].bandwidth;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

/*
 * वापसs true अगर the SysAddr given by sys_addr matches the
 * DRAM base/limit associated with node_id
 */
अटल bool base_limit_match(काष्ठा amd64_pvt *pvt, u64 sys_addr, u8 nid)
अणु
	u64 addr;

	/* The K8 treats this as a 40-bit value.  However, bits 63-40 will be
	 * all ones अगर the most signअगरicant implemented address bit is 1.
	 * Here we discard bits 63-40.  See section 3.4.2 of AMD खुलाation
	 * 24592: AMD x86-64 Architecture Programmer's Manual Volume 1
	 * Application Programming.
	 */
	addr = sys_addr & 0x000000ffffffffffull;

	वापस ((addr >= get_dram_base(pvt, nid)) &&
		(addr <= get_dram_limit(pvt, nid)));
पूर्ण

/*
 * Attempt to map a SysAddr to a node. On success, वापस a poपूर्णांकer to the
 * mem_ctl_info काष्ठाure क्रम the node that the SysAddr maps to.
 *
 * On failure, वापस शून्य.
 */
अटल काष्ठा mem_ctl_info *find_mc_by_sys_addr(काष्ठा mem_ctl_info *mci,
						u64 sys_addr)
अणु
	काष्ठा amd64_pvt *pvt;
	u8 node_id;
	u32 पूर्णांकlv_en, bits;

	/*
	 * Here we use the DRAM Base (section 3.4.4.1) and DRAM Limit (section
	 * 3.4.4.2) रेजिस्टरs to map the SysAddr to a node ID.
	 */
	pvt = mci->pvt_info;

	/*
	 * The value of this field should be the same क्रम all DRAM Base
	 * रेजिस्टरs.  Thereक्रमe we arbitrarily choose to पढ़ो it from the
	 * रेजिस्टर क्रम node 0.
	 */
	पूर्णांकlv_en = dram_पूर्णांकlv_en(pvt, 0);

	अगर (पूर्णांकlv_en == 0) अणु
		क्रम (node_id = 0; node_id < DRAM_RANGES; node_id++) अणु
			अगर (base_limit_match(pvt, sys_addr, node_id))
				जाओ found;
		पूर्ण
		जाओ err_no_match;
	पूर्ण

	अगर (unlikely((पूर्णांकlv_en != 0x01) &&
		     (पूर्णांकlv_en != 0x03) &&
		     (पूर्णांकlv_en != 0x07))) अणु
		amd64_warn("DRAM Base[IntlvEn] junk value: 0x%x, BIOS bug?\n", पूर्णांकlv_en);
		वापस शून्य;
	पूर्ण

	bits = (((u32) sys_addr) >> 12) & पूर्णांकlv_en;

	क्रम (node_id = 0; ; ) अणु
		अगर ((dram_पूर्णांकlv_sel(pvt, node_id) & पूर्णांकlv_en) == bits)
			अवरोध;	/* पूर्णांकlv_sel field matches */

		अगर (++node_id >= DRAM_RANGES)
			जाओ err_no_match;
	पूर्ण

	/* sanity test क्रम sys_addr */
	अगर (unlikely(!base_limit_match(pvt, sys_addr, node_id))) अणु
		amd64_warn("%s: sys_addr 0x%llx falls outside base/limit address"
			   "range for node %d with node interleaving enabled.\n",
			   __func__, sys_addr, node_id);
		वापस शून्य;
	पूर्ण

found:
	वापस edac_mc_find((पूर्णांक)node_id);

err_no_match:
	edac_dbg(2, "sys_addr 0x%lx doesn't match any node\n",
		 (अचिन्हित दीर्घ)sys_addr);

	वापस शून्य;
पूर्ण

/*
 * compute the CS base address of the @csrow on the DRAM controller @dct.
 * For details see F2x[5C:40] in the processor's BKDG
 */
अटल व्योम get_cs_base_and_mask(काष्ठा amd64_pvt *pvt, पूर्णांक csrow, u8 dct,
				 u64 *base, u64 *mask)
अणु
	u64 csbase, csmask, base_bits, mask_bits;
	u8 addr_shअगरt;

	अगर (pvt->fam == 0xf && pvt->ext_model < K8_REV_F) अणु
		csbase		= pvt->csels[dct].csbases[csrow];
		csmask		= pvt->csels[dct].csmasks[csrow];
		base_bits	= GENMASK_ULL(31, 21) | GENMASK_ULL(15, 9);
		mask_bits	= GENMASK_ULL(29, 21) | GENMASK_ULL(15, 9);
		addr_shअगरt	= 4;

	/*
	 * F16h and F15h, models 30h and later need two addr_shअगरt values:
	 * 8 क्रम high and 6 क्रम low (cf. F16h BKDG).
	 */
	पूर्ण अन्यथा अगर (pvt->fam == 0x16 ||
		  (pvt->fam == 0x15 && pvt->model >= 0x30)) अणु
		csbase          = pvt->csels[dct].csbases[csrow];
		csmask          = pvt->csels[dct].csmasks[csrow >> 1];

		*base  = (csbase & GENMASK_ULL(15,  5)) << 6;
		*base |= (csbase & GENMASK_ULL(30, 19)) << 8;

		*mask = ~0ULL;
		/* poke holes क्रम the csmask */
		*mask &= ~((GENMASK_ULL(15, 5)  << 6) |
			   (GENMASK_ULL(30, 19) << 8));

		*mask |= (csmask & GENMASK_ULL(15, 5))  << 6;
		*mask |= (csmask & GENMASK_ULL(30, 19)) << 8;

		वापस;
	पूर्ण अन्यथा अणु
		csbase		= pvt->csels[dct].csbases[csrow];
		csmask		= pvt->csels[dct].csmasks[csrow >> 1];
		addr_shअगरt	= 8;

		अगर (pvt->fam == 0x15)
			base_bits = mask_bits =
				GENMASK_ULL(30,19) | GENMASK_ULL(13,5);
		अन्यथा
			base_bits = mask_bits =
				GENMASK_ULL(28,19) | GENMASK_ULL(13,5);
	पूर्ण

	*base  = (csbase & base_bits) << addr_shअगरt;

	*mask  = ~0ULL;
	/* poke holes क्रम the csmask */
	*mask &= ~(mask_bits << addr_shअगरt);
	/* OR them in */
	*mask |= (csmask & mask_bits) << addr_shअगरt;
पूर्ण

#घोषणा क्रम_each_chip_select(i, dct, pvt) \
	क्रम (i = 0; i < pvt->csels[dct].b_cnt; i++)

#घोषणा chip_select_base(i, dct, pvt) \
	pvt->csels[dct].csbases[i]

#घोषणा क्रम_each_chip_select_mask(i, dct, pvt) \
	क्रम (i = 0; i < pvt->csels[dct].m_cnt; i++)

#घोषणा क्रम_each_umc(i) \
	क्रम (i = 0; i < fam_type->max_mcs; i++)

/*
 * @input_addr is an InputAddr associated with the node given by mci. Return the
 * csrow that input_addr maps to, or -1 on failure (no csrow claims input_addr).
 */
अटल पूर्णांक input_addr_to_csrow(काष्ठा mem_ctl_info *mci, u64 input_addr)
अणु
	काष्ठा amd64_pvt *pvt;
	पूर्णांक csrow;
	u64 base, mask;

	pvt = mci->pvt_info;

	क्रम_each_chip_select(csrow, 0, pvt) अणु
		अगर (!csrow_enabled(csrow, 0, pvt))
			जारी;

		get_cs_base_and_mask(pvt, csrow, 0, &base, &mask);

		mask = ~mask;

		अगर ((input_addr & mask) == (base & mask)) अणु
			edac_dbg(2, "InputAddr 0x%lx matches csrow %d (node %d)\n",
				 (अचिन्हित दीर्घ)input_addr, csrow,
				 pvt->mc_node_id);

			वापस csrow;
		पूर्ण
	पूर्ण
	edac_dbg(2, "no matching csrow for InputAddr 0x%lx (MC node %d)\n",
		 (अचिन्हित दीर्घ)input_addr, pvt->mc_node_id);

	वापस -1;
पूर्ण

/*
 * Obtain info from the DRAM Hole Address Register (section 3.4.8, pub #26094)
 * क्रम the node represented by mci. Info is passed back in *hole_base,
 * *hole_offset, and *hole_size.  Function वापसs 0 अगर info is valid or 1 अगर
 * info is invalid. Info may be invalid क्रम either of the following reasons:
 *
 * - The revision of the node is not E or greater.  In this हाल, the DRAM Hole
 *   Address Register करोes not exist.
 *
 * - The DramHoleValid bit is cleared in the DRAM Hole Address Register,
 *   indicating that its contents are not valid.
 *
 * The values passed back in *hole_base, *hole_offset, and *hole_size are
 * complete 32-bit values despite the fact that the bitfields in the DHAR
 * only represent bits 31-24 of the base and offset values.
 */
अटल पूर्णांक get_dram_hole_info(काष्ठा mem_ctl_info *mci, u64 *hole_base,
			      u64 *hole_offset, u64 *hole_size)
अणु
	काष्ठा amd64_pvt *pvt = mci->pvt_info;

	/* only revE and later have the DRAM Hole Address Register */
	अगर (pvt->fam == 0xf && pvt->ext_model < K8_REV_E) अणु
		edac_dbg(1, "  revision %d for node %d does not support DHAR\n",
			 pvt->ext_model, pvt->mc_node_id);
		वापस 1;
	पूर्ण

	/* valid क्रम Fam10h and above */
	अगर (pvt->fam >= 0x10 && !dhar_mem_hoist_valid(pvt)) अणु
		edac_dbg(1, "  Dram Memory Hoisting is DISABLED on this system\n");
		वापस 1;
	पूर्ण

	अगर (!dhar_valid(pvt)) अणु
		edac_dbg(1, "  Dram Memory Hoisting is DISABLED on this node %d\n",
			 pvt->mc_node_id);
		वापस 1;
	पूर्ण

	/* This node has Memory Hoisting */

	/* +------------------+--------------------+--------------------+-----
	 * | memory           | DRAM hole          | relocated          |
	 * | [0, (x - 1)]     | [x, 0xffffffff]    | addresses from     |
	 * |                  |                    | DRAM hole          |
	 * |                  |                    | [0x100000000,      |
	 * |                  |                    |  (0x100000000+     |
	 * |                  |                    |   (0xffffffff-x))] |
	 * +------------------+--------------------+--------------------+-----
	 *
	 * Above is a diagram of physical memory showing the DRAM hole and the
	 * relocated addresses from the DRAM hole.  As shown, the DRAM hole
	 * starts at address x (the base address) and extends through address
	 * 0xffffffff.  The DRAM Hole Address Register (DHAR) relocates the
	 * addresses in the hole so that they start at 0x100000000.
	 */

	*hole_base = dhar_base(pvt);
	*hole_size = (1ULL << 32) - *hole_base;

	*hole_offset = (pvt->fam > 0xf) ? f10_dhar_offset(pvt)
					: k8_dhar_offset(pvt);

	edac_dbg(1, "  DHAR info for node %d base 0x%lx offset 0x%lx size 0x%lx\n",
		 pvt->mc_node_id, (अचिन्हित दीर्घ)*hole_base,
		 (अचिन्हित दीर्घ)*hole_offset, (अचिन्हित दीर्घ)*hole_size);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_EDAC_DEBUG
#घोषणा EDAC_DCT_ATTR_SHOW(reg)						\
अटल sमाप_प्रकार reg##_show(काष्ठा device *dev,				\
			 काष्ठा device_attribute *mattr, अक्षर *data)	\
अणु									\
	काष्ठा mem_ctl_info *mci = to_mci(dev);				\
	काष्ठा amd64_pvt *pvt = mci->pvt_info;				\
									\
	वापस प्र_लिखो(data, "0x%016llx\n", (u64)pvt->reg);		\
पूर्ण

EDAC_DCT_ATTR_SHOW(dhar);
EDAC_DCT_ATTR_SHOW(dbam0);
EDAC_DCT_ATTR_SHOW(top_mem);
EDAC_DCT_ATTR_SHOW(top_mem2);

अटल sमाप_प्रकार hole_show(काष्ठा device *dev, काष्ठा device_attribute *mattr,
			 अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);

	u64 hole_base = 0;
	u64 hole_offset = 0;
	u64 hole_size = 0;

	get_dram_hole_info(mci, &hole_base, &hole_offset, &hole_size);

	वापस प्र_लिखो(data, "%llx %llx %llx\n", hole_base, hole_offset,
						 hole_size);
पूर्ण

/*
 * update NUM_DBG_ATTRS in हाल you add new members
 */
अटल DEVICE_ATTR(dhar, S_IRUGO, dhar_show, शून्य);
अटल DEVICE_ATTR(dbam, S_IRUGO, dbam0_show, शून्य);
अटल DEVICE_ATTR(topmem, S_IRUGO, top_mem_show, शून्य);
अटल DEVICE_ATTR(topmem2, S_IRUGO, top_mem2_show, शून्य);
अटल DEVICE_ATTR(dram_hole, S_IRUGO, hole_show, शून्य);

अटल काष्ठा attribute *dbg_attrs[] = अणु
	&dev_attr_dhar.attr,
	&dev_attr_dbam.attr,
	&dev_attr_topmem.attr,
	&dev_attr_topmem2.attr,
	&dev_attr_dram_hole.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dbg_group = अणु
	.attrs = dbg_attrs,
पूर्ण;

अटल sमाप_प्रकार inject_section_show(काष्ठा device *dev,
				   काष्ठा device_attribute *mattr, अक्षर *buf)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	वापस प्र_लिखो(buf, "0x%x\n", pvt->injection.section);
पूर्ण

/*
 * store error injection section value which refers to one of 4 16-byte sections
 * within a 64-byte cacheline
 *
 * range: 0..3
 */
अटल sमाप_प्रकार inject_section_store(काष्ठा device *dev,
				    काष्ठा device_attribute *mattr,
				    स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(data, 10, &value);
	अगर (ret < 0)
		वापस ret;

	अगर (value > 3) अणु
		amd64_warn("%s: invalid section 0x%lx\n", __func__, value);
		वापस -EINVAL;
	पूर्ण

	pvt->injection.section = (u32) value;
	वापस count;
पूर्ण

अटल sमाप_प्रकार inject_word_show(काष्ठा device *dev,
				काष्ठा device_attribute *mattr, अक्षर *buf)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	वापस प्र_लिखो(buf, "0x%x\n", pvt->injection.word);
पूर्ण

/*
 * store error injection word value which refers to one of 9 16-bit word of the
 * 16-byte (128-bit + ECC bits) section
 *
 * range: 0..8
 */
अटल sमाप_प्रकार inject_word_store(काष्ठा device *dev,
				 काष्ठा device_attribute *mattr,
				 स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(data, 10, &value);
	अगर (ret < 0)
		वापस ret;

	अगर (value > 8) अणु
		amd64_warn("%s: invalid word 0x%lx\n", __func__, value);
		वापस -EINVAL;
	पूर्ण

	pvt->injection.word = (u32) value;
	वापस count;
पूर्ण

अटल sमाप_प्रकार inject_ecc_vector_show(काष्ठा device *dev,
				      काष्ठा device_attribute *mattr,
				      अक्षर *buf)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	वापस प्र_लिखो(buf, "0x%x\n", pvt->injection.bit_map);
पूर्ण

/*
 * store 16 bit error injection vector which enables injecting errors to the
 * corresponding bit within the error injection word above. When used during a
 * DRAM ECC पढ़ो, it holds the contents of the of the DRAM ECC bits.
 */
अटल sमाप_प्रकार inject_ecc_vector_store(काष्ठा device *dev,
				       काष्ठा device_attribute *mattr,
				       स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(data, 16, &value);
	अगर (ret < 0)
		वापस ret;

	अगर (value & 0xFFFF0000) अणु
		amd64_warn("%s: invalid EccVector: 0x%lx\n", __func__, value);
		वापस -EINVAL;
	पूर्ण

	pvt->injection.bit_map = (u32) value;
	वापस count;
पूर्ण

/*
 * Do a DRAM ECC पढ़ो. Assemble staged values in the pvt area, क्रमmat पूर्णांकo
 * fields needed by the injection रेजिस्टरs and पढ़ो the NB Array Data Port.
 */
अटल sमाप_प्रकार inject_पढ़ो_store(काष्ठा device *dev,
				 काष्ठा device_attribute *mattr,
				 स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	अचिन्हित दीर्घ value;
	u32 section, word_bits;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(data, 10, &value);
	अगर (ret < 0)
		वापस ret;

	/* Form value to choose 16-byte section of cacheline */
	section = F10_NB_ARRAY_DRAM | SET_NB_ARRAY_ADDR(pvt->injection.section);

	amd64_ग_लिखो_pci_cfg(pvt->F3, F10_NB_ARRAY_ADDR, section);

	word_bits = SET_NB_DRAM_INJECTION_READ(pvt->injection);

	/* Issue 'word' and 'bit' aदीर्घ with the READ request */
	amd64_ग_लिखो_pci_cfg(pvt->F3, F10_NB_ARRAY_DATA, word_bits);

	edac_dbg(0, "section=0x%x word_bits=0x%x\n", section, word_bits);

	वापस count;
पूर्ण

/*
 * Do a DRAM ECC ग_लिखो. Assemble staged values in the pvt area and क्रमmat पूर्णांकo
 * fields needed by the injection रेजिस्टरs.
 */
अटल sमाप_प्रकार inject_ग_लिखो_store(काष्ठा device *dev,
				  काष्ठा device_attribute *mattr,
				  स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	u32 section, word_bits, पंचांगp;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(data, 10, &value);
	अगर (ret < 0)
		वापस ret;

	/* Form value to choose 16-byte section of cacheline */
	section = F10_NB_ARRAY_DRAM | SET_NB_ARRAY_ADDR(pvt->injection.section);

	amd64_ग_लिखो_pci_cfg(pvt->F3, F10_NB_ARRAY_ADDR, section);

	word_bits = SET_NB_DRAM_INJECTION_WRITE(pvt->injection);

	pr_notice_once("Don't forget to decrease MCE polling interval in\n"
			"/sys/bus/machinecheck/devices/machinecheck<CPUNUM>/check_interval\n"
			"so that you can get the error report faster.\n");

	on_each_cpu(disable_caches, शून्य, 1);

	/* Issue 'word' and 'bit' aदीर्घ with the READ request */
	amd64_ग_लिखो_pci_cfg(pvt->F3, F10_NB_ARRAY_DATA, word_bits);

 retry:
	/* रुको until injection happens */
	amd64_पढ़ो_pci_cfg(pvt->F3, F10_NB_ARRAY_DATA, &पंचांगp);
	अगर (पंचांगp & F10_NB_ARR_ECC_WR_REQ) अणु
		cpu_relax();
		जाओ retry;
	पूर्ण

	on_each_cpu(enable_caches, शून्य, 1);

	edac_dbg(0, "section=0x%x word_bits=0x%x\n", section, word_bits);

	वापस count;
पूर्ण

/*
 * update NUM_INJ_ATTRS in हाल you add new members
 */

अटल DEVICE_ATTR(inject_section, S_IRUGO | S_IWUSR,
		   inject_section_show, inject_section_store);
अटल DEVICE_ATTR(inject_word, S_IRUGO | S_IWUSR,
		   inject_word_show, inject_word_store);
अटल DEVICE_ATTR(inject_ecc_vector, S_IRUGO | S_IWUSR,
		   inject_ecc_vector_show, inject_ecc_vector_store);
अटल DEVICE_ATTR(inject_ग_लिखो, S_IWUSR,
		   शून्य, inject_ग_लिखो_store);
अटल DEVICE_ATTR(inject_पढ़ो,  S_IWUSR,
		   शून्य, inject_पढ़ो_store);

अटल काष्ठा attribute *inj_attrs[] = अणु
	&dev_attr_inject_section.attr,
	&dev_attr_inject_word.attr,
	&dev_attr_inject_ecc_vector.attr,
	&dev_attr_inject_ग_लिखो.attr,
	&dev_attr_inject_पढ़ो.attr,
	शून्य
पूर्ण;

अटल umode_t inj_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा mem_ctl_info *mci = container_of(dev, काष्ठा mem_ctl_info, dev);
	काष्ठा amd64_pvt *pvt = mci->pvt_info;

	/* Families which have that injection hw */
	अगर (pvt->fam >= 0x10 && pvt->fam <= 0x16)
		वापस attr->mode;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group inj_group = अणु
	.attrs = inj_attrs,
	.is_visible = inj_is_visible,
पूर्ण;
#पूर्ण_अगर /* CONFIG_EDAC_DEBUG */

/*
 * Return the DramAddr that the SysAddr given by @sys_addr maps to.  It is
 * assumed that sys_addr maps to the node given by mci.
 *
 * The first part of section 3.4.4 (p. 70) shows how the DRAM Base (section
 * 3.4.4.1) and DRAM Limit (section 3.4.4.2) रेजिस्टरs are used to translate a
 * SysAddr to a DramAddr. If the DRAM Hole Address Register (DHAR) is enabled,
 * then it is also involved in translating a SysAddr to a DramAddr. Sections
 * 3.4.8 and 3.5.8.2 describe the DHAR and how it is used क्रम memory hoisting.
 * These parts of the करोcumentation are unclear. I पूर्णांकerpret them as follows:
 *
 * When node n receives a SysAddr, it processes the SysAddr as follows:
 *
 * 1. It extracts the DRAMBase and DRAMLimit values from the DRAM Base and DRAM
 *    Limit रेजिस्टरs क्रम node n. If the SysAddr is not within the range
 *    specअगरied by the base and limit values, then node n ignores the Sysaddr
 *    (since it करोes not map to node n). Otherwise जारी to step 2 below.
 *
 * 2. If the DramHoleValid bit of the DHAR क्रम node n is clear, the DHAR is
 *    disabled so skip to step 3 below. Otherwise see अगर the SysAddr is within
 *    the range of relocated addresses (starting at 0x100000000) from the DRAM
 *    hole. If not, skip to step 3 below. Else get the value of the
 *    DramHoleOffset field from the DHAR. To obtain the DramAddr, subtract the
 *    offset defined by this value from the SysAddr.
 *
 * 3. Obtain the base address क्रम node n from the DRAMBase field of the DRAM
 *    Base रेजिस्टर क्रम node n. To obtain the DramAddr, subtract the base
 *    address from the SysAddr, as shown near the start of section 3.4.4 (p.70).
 */
अटल u64 sys_addr_to_dram_addr(काष्ठा mem_ctl_info *mci, u64 sys_addr)
अणु
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	u64 dram_base, hole_base, hole_offset, hole_size, dram_addr;
	पूर्णांक ret;

	dram_base = get_dram_base(pvt, pvt->mc_node_id);

	ret = get_dram_hole_info(mci, &hole_base, &hole_offset, &hole_size);
	अगर (!ret) अणु
		अगर ((sys_addr >= (1ULL << 32)) &&
		    (sys_addr < ((1ULL << 32) + hole_size))) अणु
			/* use DHAR to translate SysAddr to DramAddr */
			dram_addr = sys_addr - hole_offset;

			edac_dbg(2, "using DHAR to translate SysAddr 0x%lx to DramAddr 0x%lx\n",
				 (अचिन्हित दीर्घ)sys_addr,
				 (अचिन्हित दीर्घ)dram_addr);

			वापस dram_addr;
		पूर्ण
	पूर्ण

	/*
	 * Translate the SysAddr to a DramAddr as shown near the start of
	 * section 3.4.4 (p. 70).  Although sys_addr is a 64-bit value, the k8
	 * only deals with 40-bit values.  Thereक्रमe we discard bits 63-40 of
	 * sys_addr below.  If bit 39 of sys_addr is 1 then the bits we
	 * discard are all 1s.  Otherwise the bits we discard are all 0s.  See
	 * section 3.4.2 of AMD खुलाation 24592: AMD x86-64 Architecture
	 * Programmer's Manual Volume 1 Application Programming.
	 */
	dram_addr = (sys_addr & GENMASK_ULL(39, 0)) - dram_base;

	edac_dbg(2, "using DRAM Base register to translate SysAddr 0x%lx to DramAddr 0x%lx\n",
		 (अचिन्हित दीर्घ)sys_addr, (अचिन्हित दीर्घ)dram_addr);
	वापस dram_addr;
पूर्ण

/*
 * @पूर्णांकlv_en is the value of the IntlvEn field from a DRAM Base रेजिस्टर
 * (section 3.4.4.1).  Return the number of bits from a SysAddr that are used
 * क्रम node पूर्णांकerleaving.
 */
अटल पूर्णांक num_node_पूर्णांकerleave_bits(अचिन्हित पूर्णांकlv_en)
अणु
	अटल स्थिर पूर्णांक पूर्णांकlv_shअगरt_table[] = अणु 0, 1, 0, 2, 0, 0, 0, 3 पूर्ण;
	पूर्णांक n;

	BUG_ON(पूर्णांकlv_en > 7);
	n = पूर्णांकlv_shअगरt_table[पूर्णांकlv_en];
	वापस n;
पूर्ण

/* Translate the DramAddr given by @dram_addr to an InputAddr. */
अटल u64 dram_addr_to_input_addr(काष्ठा mem_ctl_info *mci, u64 dram_addr)
अणु
	काष्ठा amd64_pvt *pvt;
	पूर्णांक पूर्णांकlv_shअगरt;
	u64 input_addr;

	pvt = mci->pvt_info;

	/*
	 * See the start of section 3.4.4 (p. 70, BKDG #26094, K8, revA-E)
	 * concerning translating a DramAddr to an InputAddr.
	 */
	पूर्णांकlv_shअगरt = num_node_पूर्णांकerleave_bits(dram_पूर्णांकlv_en(pvt, 0));
	input_addr = ((dram_addr >> पूर्णांकlv_shअगरt) & GENMASK_ULL(35, 12)) +
		      (dram_addr & 0xfff);

	edac_dbg(2, "  Intlv Shift=%d DramAddr=0x%lx maps to InputAddr=0x%lx\n",
		 पूर्णांकlv_shअगरt, (अचिन्हित दीर्घ)dram_addr,
		 (अचिन्हित दीर्घ)input_addr);

	वापस input_addr;
पूर्ण

/*
 * Translate the SysAddr represented by @sys_addr to an InputAddr.  It is
 * assumed that @sys_addr maps to the node given by mci.
 */
अटल u64 sys_addr_to_input_addr(काष्ठा mem_ctl_info *mci, u64 sys_addr)
अणु
	u64 input_addr;

	input_addr =
	    dram_addr_to_input_addr(mci, sys_addr_to_dram_addr(mci, sys_addr));

	edac_dbg(2, "SysAddr 0x%lx translates to InputAddr 0x%lx\n",
		 (अचिन्हित दीर्घ)sys_addr, (अचिन्हित दीर्घ)input_addr);

	वापस input_addr;
पूर्ण

/* Map the Error address to a PAGE and PAGE OFFSET. */
अटल अंतरभूत व्योम error_address_to_page_and_offset(u64 error_address,
						    काष्ठा err_info *err)
अणु
	err->page = (u32) (error_address >> PAGE_SHIFT);
	err->offset = ((u32) error_address) & ~PAGE_MASK;
पूर्ण

/*
 * @sys_addr is an error address (a SysAddr) extracted from the MCA NB Address
 * Low (section 3.6.4.5) and MCA NB Address High (section 3.6.4.6) रेजिस्टरs
 * of a node that detected an ECC memory error.  mci represents the node that
 * the error address maps to (possibly dअगरferent from the node that detected
 * the error).  Return the number of the csrow that sys_addr maps to, or -1 on
 * error.
 */
अटल पूर्णांक sys_addr_to_csrow(काष्ठा mem_ctl_info *mci, u64 sys_addr)
अणु
	पूर्णांक csrow;

	csrow = input_addr_to_csrow(mci, sys_addr_to_input_addr(mci, sys_addr));

	अगर (csrow == -1)
		amd64_mc_err(mci, "Failed to translate InputAddr to csrow for "
				  "address 0x%lx\n", (अचिन्हित दीर्घ)sys_addr);
	वापस csrow;
पूर्ण

अटल पूर्णांक get_channel_from_ecc_syndrome(काष्ठा mem_ctl_info *, u16);

/*
 * Determine अगर the DIMMs have ECC enabled. ECC is enabled ONLY अगर all the DIMMs
 * are ECC capable.
 */
अटल अचिन्हित दीर्घ determine_edac_cap(काष्ठा amd64_pvt *pvt)
अणु
	अचिन्हित दीर्घ edac_cap = EDAC_FLAG_NONE;
	u8 bit;

	अगर (pvt->umc) अणु
		u8 i, umc_en_mask = 0, dimm_ecc_en_mask = 0;

		क्रम_each_umc(i) अणु
			अगर (!(pvt->umc[i].sdp_ctrl & UMC_SDP_INIT))
				जारी;

			umc_en_mask |= BIT(i);

			/* UMC Configuration bit 12 (DimmEccEn) */
			अगर (pvt->umc[i].umc_cfg & BIT(12))
				dimm_ecc_en_mask |= BIT(i);
		पूर्ण

		अगर (umc_en_mask == dimm_ecc_en_mask)
			edac_cap = EDAC_FLAG_SECDED;
	पूर्ण अन्यथा अणु
		bit = (pvt->fam > 0xf || pvt->ext_model >= K8_REV_F)
			? 19
			: 17;

		अगर (pvt->dclr0 & BIT(bit))
			edac_cap = EDAC_FLAG_SECDED;
	पूर्ण

	वापस edac_cap;
पूर्ण

अटल व्योम debug_display_dimm_sizes(काष्ठा amd64_pvt *, u8);

अटल व्योम debug_dump_dramcfg_low(काष्ठा amd64_pvt *pvt, u32 dclr, पूर्णांक chan)
अणु
	edac_dbg(1, "F2x%d90 (DRAM Cfg Low): 0x%08x\n", chan, dclr);

	अगर (pvt->dram_type == MEM_LRDDR3) अणु
		u32 dcsm = pvt->csels[chan].csmasks[0];
		/*
		 * It's assumed all LRDIMMs in a DCT are going to be of
		 * same 'type' until proven otherwise. So, use a cs
		 * value of '0' here to get dcsm value.
		 */
		edac_dbg(1, " LRDIMM %dx rank multiply\n", (dcsm & 0x3));
	पूर्ण

	edac_dbg(1, "All DIMMs support ECC:%s\n",
		    (dclr & BIT(19)) ? "yes" : "no");


	edac_dbg(1, "  PAR/ERR parity: %s\n",
		 (dclr & BIT(8)) ?  "enabled" : "disabled");

	अगर (pvt->fam == 0x10)
		edac_dbg(1, "  DCT 128bit mode width: %s\n",
			 (dclr & BIT(11)) ?  "128b" : "64b");

	edac_dbg(1, "  x4 logical DIMMs present: L0: %s L1: %s L2: %s L3: %s\n",
		 (dclr & BIT(12)) ?  "yes" : "no",
		 (dclr & BIT(13)) ?  "yes" : "no",
		 (dclr & BIT(14)) ?  "yes" : "no",
		 (dclr & BIT(15)) ?  "yes" : "no");
पूर्ण

#घोषणा CS_EVEN_PRIMARY		BIT(0)
#घोषणा CS_ODD_PRIMARY		BIT(1)
#घोषणा CS_EVEN_SECONDARY	BIT(2)
#घोषणा CS_ODD_SECONDARY	BIT(3)

#घोषणा CS_EVEN			(CS_EVEN_PRIMARY | CS_EVEN_SECONDARY)
#घोषणा CS_ODD			(CS_ODD_PRIMARY | CS_ODD_SECONDARY)

अटल पूर्णांक f17_get_cs_mode(पूर्णांक dimm, u8 ctrl, काष्ठा amd64_pvt *pvt)
अणु
	पूर्णांक cs_mode = 0;

	अगर (csrow_enabled(2 * dimm, ctrl, pvt))
		cs_mode |= CS_EVEN_PRIMARY;

	अगर (csrow_enabled(2 * dimm + 1, ctrl, pvt))
		cs_mode |= CS_ODD_PRIMARY;

	/* Asymmetric dual-rank DIMM support. */
	अगर (csrow_sec_enabled(2 * dimm + 1, ctrl, pvt))
		cs_mode |= CS_ODD_SECONDARY;

	वापस cs_mode;
पूर्ण

अटल व्योम debug_display_dimm_sizes_df(काष्ठा amd64_pvt *pvt, u8 ctrl)
अणु
	पूर्णांक dimm, size0, size1, cs0, cs1, cs_mode;

	edac_prपूर्णांकk(KERN_DEBUG, EDAC_MC, "UMC%d chip selects:\n", ctrl);

	क्रम (dimm = 0; dimm < 2; dimm++) अणु
		cs0 = dimm * 2;
		cs1 = dimm * 2 + 1;

		cs_mode = f17_get_cs_mode(dimm, ctrl, pvt);

		size0 = pvt->ops->dbam_to_cs(pvt, ctrl, cs_mode, cs0);
		size1 = pvt->ops->dbam_to_cs(pvt, ctrl, cs_mode, cs1);

		amd64_info(EDAC_MC ": %d: %5dMB %d: %5dMB\n",
				cs0,	size0,
				cs1,	size1);
	पूर्ण
पूर्ण

अटल व्योम __dump_misc_regs_df(काष्ठा amd64_pvt *pvt)
अणु
	काष्ठा amd64_umc *umc;
	u32 i, पंचांगp, umc_base;

	क्रम_each_umc(i) अणु
		umc_base = get_umc_base(i);
		umc = &pvt->umc[i];

		edac_dbg(1, "UMC%d DIMM cfg: 0x%x\n", i, umc->dimm_cfg);
		edac_dbg(1, "UMC%d UMC cfg: 0x%x\n", i, umc->umc_cfg);
		edac_dbg(1, "UMC%d SDP ctrl: 0x%x\n", i, umc->sdp_ctrl);
		edac_dbg(1, "UMC%d ECC ctrl: 0x%x\n", i, umc->ecc_ctrl);

		amd_smn_पढ़ो(pvt->mc_node_id, umc_base + UMCCH_ECC_BAD_SYMBOL, &पंचांगp);
		edac_dbg(1, "UMC%d ECC bad symbol: 0x%x\n", i, पंचांगp);

		amd_smn_पढ़ो(pvt->mc_node_id, umc_base + UMCCH_UMC_CAP, &पंचांगp);
		edac_dbg(1, "UMC%d UMC cap: 0x%x\n", i, पंचांगp);
		edac_dbg(1, "UMC%d UMC cap high: 0x%x\n", i, umc->umc_cap_hi);

		edac_dbg(1, "UMC%d ECC capable: %s, ChipKill ECC capable: %s\n",
				i, (umc->umc_cap_hi & BIT(30)) ? "yes" : "no",
				    (umc->umc_cap_hi & BIT(31)) ? "yes" : "no");
		edac_dbg(1, "UMC%d All DIMMs support ECC: %s\n",
				i, (umc->umc_cfg & BIT(12)) ? "yes" : "no");
		edac_dbg(1, "UMC%d x4 DIMMs present: %s\n",
				i, (umc->dimm_cfg & BIT(6)) ? "yes" : "no");
		edac_dbg(1, "UMC%d x16 DIMMs present: %s\n",
				i, (umc->dimm_cfg & BIT(7)) ? "yes" : "no");

		अगर (pvt->dram_type == MEM_LRDDR4) अणु
			amd_smn_पढ़ो(pvt->mc_node_id, umc_base + UMCCH_ADDR_CFG, &पंचांगp);
			edac_dbg(1, "UMC%d LRDIMM %dx rank multiply\n",
					i, 1 << ((पंचांगp >> 4) & 0x3));
		पूर्ण

		debug_display_dimm_sizes_df(pvt, i);
	पूर्ण

	edac_dbg(1, "F0x104 (DRAM Hole Address): 0x%08x, base: 0x%08x\n",
		 pvt->dhar, dhar_base(pvt));
पूर्ण

/* Display and decode various NB रेजिस्टरs क्रम debug purposes. */
अटल व्योम __dump_misc_regs(काष्ठा amd64_pvt *pvt)
अणु
	edac_dbg(1, "F3xE8 (NB Cap): 0x%08x\n", pvt->nbcap);

	edac_dbg(1, "  NB two channel DRAM capable: %s\n",
		 (pvt->nbcap & NBCAP_DCT_DUAL) ? "yes" : "no");

	edac_dbg(1, "  ECC capable: %s, ChipKill ECC capable: %s\n",
		 (pvt->nbcap & NBCAP_SECDED) ? "yes" : "no",
		 (pvt->nbcap & NBCAP_CHIPKILL) ? "yes" : "no");

	debug_dump_dramcfg_low(pvt, pvt->dclr0, 0);

	edac_dbg(1, "F3xB0 (Online Spare): 0x%08x\n", pvt->online_spare);

	edac_dbg(1, "F1xF0 (DRAM Hole Address): 0x%08x, base: 0x%08x, offset: 0x%08x\n",
		 pvt->dhar, dhar_base(pvt),
		 (pvt->fam == 0xf) ? k8_dhar_offset(pvt)
				   : f10_dhar_offset(pvt));

	debug_display_dimm_sizes(pvt, 0);

	/* everything below this poपूर्णांक is Fam10h and above */
	अगर (pvt->fam == 0xf)
		वापस;

	debug_display_dimm_sizes(pvt, 1);

	/* Only अगर NOT ganged करोes dclr1 have valid info */
	अगर (!dct_ganging_enabled(pvt))
		debug_dump_dramcfg_low(pvt, pvt->dclr1, 1);
पूर्ण

/* Display and decode various NB रेजिस्टरs क्रम debug purposes. */
अटल व्योम dump_misc_regs(काष्ठा amd64_pvt *pvt)
अणु
	अगर (pvt->umc)
		__dump_misc_regs_df(pvt);
	अन्यथा
		__dump_misc_regs(pvt);

	edac_dbg(1, "  DramHoleValid: %s\n", dhar_valid(pvt) ? "yes" : "no");

	amd64_info("using x%u syndromes.\n", pvt->ecc_sym_sz);
पूर्ण

/*
 * See BKDG, F2x[1,0][5C:40], F2[1,0][6C:60]
 */
अटल व्योम prep_chip_selects(काष्ठा amd64_pvt *pvt)
अणु
	अगर (pvt->fam == 0xf && pvt->ext_model < K8_REV_F) अणु
		pvt->csels[0].b_cnt = pvt->csels[1].b_cnt = 8;
		pvt->csels[0].m_cnt = pvt->csels[1].m_cnt = 8;
	पूर्ण अन्यथा अगर (pvt->fam == 0x15 && pvt->model == 0x30) अणु
		pvt->csels[0].b_cnt = pvt->csels[1].b_cnt = 4;
		pvt->csels[0].m_cnt = pvt->csels[1].m_cnt = 2;
	पूर्ण अन्यथा अगर (pvt->fam >= 0x17) अणु
		पूर्णांक umc;

		क्रम_each_umc(umc) अणु
			pvt->csels[umc].b_cnt = 4;
			pvt->csels[umc].m_cnt = 2;
		पूर्ण

	पूर्ण अन्यथा अणु
		pvt->csels[0].b_cnt = pvt->csels[1].b_cnt = 8;
		pvt->csels[0].m_cnt = pvt->csels[1].m_cnt = 4;
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_umc_base_mask(काष्ठा amd64_pvt *pvt)
अणु
	u32 umc_base_reg, umc_base_reg_sec;
	u32 umc_mask_reg, umc_mask_reg_sec;
	u32 base_reg, base_reg_sec;
	u32 mask_reg, mask_reg_sec;
	u32 *base, *base_sec;
	u32 *mask, *mask_sec;
	पूर्णांक cs, umc;

	क्रम_each_umc(umc) अणु
		umc_base_reg = get_umc_base(umc) + UMCCH_BASE_ADDR;
		umc_base_reg_sec = get_umc_base(umc) + UMCCH_BASE_ADDR_SEC;

		क्रम_each_chip_select(cs, umc, pvt) अणु
			base = &pvt->csels[umc].csbases[cs];
			base_sec = &pvt->csels[umc].csbases_sec[cs];

			base_reg = umc_base_reg + (cs * 4);
			base_reg_sec = umc_base_reg_sec + (cs * 4);

			अगर (!amd_smn_पढ़ो(pvt->mc_node_id, base_reg, base))
				edac_dbg(0, "  DCSB%d[%d]=0x%08x reg: 0x%x\n",
					 umc, cs, *base, base_reg);

			अगर (!amd_smn_पढ़ो(pvt->mc_node_id, base_reg_sec, base_sec))
				edac_dbg(0, "    DCSB_SEC%d[%d]=0x%08x reg: 0x%x\n",
					 umc, cs, *base_sec, base_reg_sec);
		पूर्ण

		umc_mask_reg = get_umc_base(umc) + UMCCH_ADDR_MASK;
		umc_mask_reg_sec = get_umc_base(umc) + UMCCH_ADDR_MASK_SEC;

		क्रम_each_chip_select_mask(cs, umc, pvt) अणु
			mask = &pvt->csels[umc].csmasks[cs];
			mask_sec = &pvt->csels[umc].csmasks_sec[cs];

			mask_reg = umc_mask_reg + (cs * 4);
			mask_reg_sec = umc_mask_reg_sec + (cs * 4);

			अगर (!amd_smn_पढ़ो(pvt->mc_node_id, mask_reg, mask))
				edac_dbg(0, "  DCSM%d[%d]=0x%08x reg: 0x%x\n",
					 umc, cs, *mask, mask_reg);

			अगर (!amd_smn_पढ़ो(pvt->mc_node_id, mask_reg_sec, mask_sec))
				edac_dbg(0, "    DCSM_SEC%d[%d]=0x%08x reg: 0x%x\n",
					 umc, cs, *mask_sec, mask_reg_sec);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Function 2 Offset F10_DCSB0; पढ़ो in the DCS Base and DCS Mask रेजिस्टरs
 */
अटल व्योम पढ़ो_dct_base_mask(काष्ठा amd64_pvt *pvt)
अणु
	पूर्णांक cs;

	prep_chip_selects(pvt);

	अगर (pvt->umc)
		वापस पढ़ो_umc_base_mask(pvt);

	क्रम_each_chip_select(cs, 0, pvt) अणु
		पूर्णांक reg0   = DCSB0 + (cs * 4);
		पूर्णांक reg1   = DCSB1 + (cs * 4);
		u32 *base0 = &pvt->csels[0].csbases[cs];
		u32 *base1 = &pvt->csels[1].csbases[cs];

		अगर (!amd64_पढ़ो_dct_pci_cfg(pvt, 0, reg0, base0))
			edac_dbg(0, "  DCSB0[%d]=0x%08x reg: F2x%x\n",
				 cs, *base0, reg0);

		अगर (pvt->fam == 0xf)
			जारी;

		अगर (!amd64_पढ़ो_dct_pci_cfg(pvt, 1, reg0, base1))
			edac_dbg(0, "  DCSB1[%d]=0x%08x reg: F2x%x\n",
				 cs, *base1, (pvt->fam == 0x10) ? reg1
							: reg0);
	पूर्ण

	क्रम_each_chip_select_mask(cs, 0, pvt) अणु
		पूर्णांक reg0   = DCSM0 + (cs * 4);
		पूर्णांक reg1   = DCSM1 + (cs * 4);
		u32 *mask0 = &pvt->csels[0].csmasks[cs];
		u32 *mask1 = &pvt->csels[1].csmasks[cs];

		अगर (!amd64_पढ़ो_dct_pci_cfg(pvt, 0, reg0, mask0))
			edac_dbg(0, "    DCSM0[%d]=0x%08x reg: F2x%x\n",
				 cs, *mask0, reg0);

		अगर (pvt->fam == 0xf)
			जारी;

		अगर (!amd64_पढ़ो_dct_pci_cfg(pvt, 1, reg0, mask1))
			edac_dbg(0, "    DCSM1[%d]=0x%08x reg: F2x%x\n",
				 cs, *mask1, (pvt->fam == 0x10) ? reg1
							: reg0);
	पूर्ण
पूर्ण

अटल व्योम determine_memory_type(काष्ठा amd64_pvt *pvt)
अणु
	u32 dram_ctrl, dcsm;

	अगर (pvt->umc) अणु
		अगर ((pvt->umc[0].dimm_cfg | pvt->umc[1].dimm_cfg) & BIT(5))
			pvt->dram_type = MEM_LRDDR4;
		अन्यथा अगर ((pvt->umc[0].dimm_cfg | pvt->umc[1].dimm_cfg) & BIT(4))
			pvt->dram_type = MEM_RDDR4;
		अन्यथा
			pvt->dram_type = MEM_DDR4;
		वापस;
	पूर्ण

	चयन (pvt->fam) अणु
	हाल 0xf:
		अगर (pvt->ext_model >= K8_REV_F)
			जाओ ddr3;

		pvt->dram_type = (pvt->dclr0 & BIT(18)) ? MEM_DDR : MEM_RDDR;
		वापस;

	हाल 0x10:
		अगर (pvt->dchr0 & DDR3_MODE)
			जाओ ddr3;

		pvt->dram_type = (pvt->dclr0 & BIT(16)) ? MEM_DDR2 : MEM_RDDR2;
		वापस;

	हाल 0x15:
		अगर (pvt->model < 0x60)
			जाओ ddr3;

		/*
		 * Model 0x60h needs special handling:
		 *
		 * We use a Chip Select value of '0' to obtain dcsm.
		 * Theoretically, it is possible to populate LRDIMMs of dअगरferent
		 * 'Rank' value on a DCT. But this is not the common हाल. So,
		 * it's reasonable to assume all DIMMs are going to be of same
		 * 'type' until proven otherwise.
		 */
		amd64_पढ़ो_dct_pci_cfg(pvt, 0, DRAM_CONTROL, &dram_ctrl);
		dcsm = pvt->csels[0].csmasks[0];

		अगर (((dram_ctrl >> 8) & 0x7) == 0x2)
			pvt->dram_type = MEM_DDR4;
		अन्यथा अगर (pvt->dclr0 & BIT(16))
			pvt->dram_type = MEM_DDR3;
		अन्यथा अगर (dcsm & 0x3)
			pvt->dram_type = MEM_LRDDR3;
		अन्यथा
			pvt->dram_type = MEM_RDDR3;

		वापस;

	हाल 0x16:
		जाओ ddr3;

	शेष:
		WARN(1, KERN_ERR "%s: Family??? 0x%x\n", __func__, pvt->fam);
		pvt->dram_type = MEM_EMPTY;
	पूर्ण
	वापस;

ddr3:
	pvt->dram_type = (pvt->dclr0 & BIT(16)) ? MEM_DDR3 : MEM_RDDR3;
पूर्ण

/* Get the number of DCT channels the memory controller is using. */
अटल पूर्णांक k8_early_channel_count(काष्ठा amd64_pvt *pvt)
अणु
	पूर्णांक flag;

	अगर (pvt->ext_model >= K8_REV_F)
		/* RevF (NPT) and later */
		flag = pvt->dclr0 & WIDTH_128;
	अन्यथा
		/* RevE and earlier */
		flag = pvt->dclr0 & REVE_WIDTH_128;

	/* not used */
	pvt->dclr1 = 0;

	वापस (flag) ? 2 : 1;
पूर्ण

/* On F10h and later ErrAddr is MC4_ADDR[47:1] */
अटल u64 get_error_address(काष्ठा amd64_pvt *pvt, काष्ठा mce *m)
अणु
	u16 mce_nid = topology_die_id(m->extcpu);
	काष्ठा mem_ctl_info *mci;
	u8 start_bit = 1;
	u8 end_bit   = 47;
	u64 addr;

	mci = edac_mc_find(mce_nid);
	अगर (!mci)
		वापस 0;

	pvt = mci->pvt_info;

	अगर (pvt->fam == 0xf) अणु
		start_bit = 3;
		end_bit   = 39;
	पूर्ण

	addr = m->addr & GENMASK_ULL(end_bit, start_bit);

	/*
	 * Erratum 637 workaround
	 */
	अगर (pvt->fam == 0x15) अणु
		u64 cc6_base, पंचांगp_addr;
		u32 पंचांगp;
		u8 पूर्णांकlv_en;

		अगर ((addr & GENMASK_ULL(47, 24)) >> 24 != 0x00fdf7)
			वापस addr;


		amd64_पढ़ो_pci_cfg(pvt->F1, DRAM_LOCAL_NODE_LIM, &पंचांगp);
		पूर्णांकlv_en = पंचांगp >> 21 & 0x7;

		/* add [47:27] + 3 trailing bits */
		cc6_base  = (पंचांगp & GENMASK_ULL(20, 0)) << 3;

		/* reverse and add DramIntlvEn */
		cc6_base |= पूर्णांकlv_en ^ 0x7;

		/* pin at [47:24] */
		cc6_base <<= 24;

		अगर (!पूर्णांकlv_en)
			वापस cc6_base | (addr & GENMASK_ULL(23, 0));

		amd64_पढ़ो_pci_cfg(pvt->F1, DRAM_LOCAL_NODE_BASE, &पंचांगp);

							/* faster log2 */
		पंचांगp_addr  = (addr & GENMASK_ULL(23, 12)) << __fls(पूर्णांकlv_en + 1);

		/* OR DramIntlvSel पूर्णांकo bits [14:12] */
		पंचांगp_addr |= (पंचांगp & GENMASK_ULL(23, 21)) >> 9;

		/* add reमुख्यing [11:0] bits from original MC4_ADDR */
		पंचांगp_addr |= addr & GENMASK_ULL(11, 0);

		वापस cc6_base | पंचांगp_addr;
	पूर्ण

	वापस addr;
पूर्ण

अटल काष्ठा pci_dev *pci_get_related_function(अचिन्हित पूर्णांक venकरोr,
						अचिन्हित पूर्णांक device,
						काष्ठा pci_dev *related)
अणु
	काष्ठा pci_dev *dev = शून्य;

	जबतक ((dev = pci_get_device(venकरोr, device, dev))) अणु
		अगर (pci_करोमुख्य_nr(dev->bus) == pci_करोमुख्य_nr(related->bus) &&
		    (dev->bus->number == related->bus->number) &&
		    (PCI_SLOT(dev->devfn) == PCI_SLOT(related->devfn)))
			अवरोध;
	पूर्ण

	वापस dev;
पूर्ण

अटल व्योम पढ़ो_dram_base_limit_regs(काष्ठा amd64_pvt *pvt, अचिन्हित range)
अणु
	काष्ठा amd_northbridge *nb;
	काष्ठा pci_dev *f1 = शून्य;
	अचिन्हित पूर्णांक pci_func;
	पूर्णांक off = range << 3;
	u32 llim;

	amd64_पढ़ो_pci_cfg(pvt->F1, DRAM_BASE_LO + off,  &pvt->ranges[range].base.lo);
	amd64_पढ़ो_pci_cfg(pvt->F1, DRAM_LIMIT_LO + off, &pvt->ranges[range].lim.lo);

	अगर (pvt->fam == 0xf)
		वापस;

	अगर (!dram_rw(pvt, range))
		वापस;

	amd64_पढ़ो_pci_cfg(pvt->F1, DRAM_BASE_HI + off,  &pvt->ranges[range].base.hi);
	amd64_पढ़ो_pci_cfg(pvt->F1, DRAM_LIMIT_HI + off, &pvt->ranges[range].lim.hi);

	/* F15h: factor in CC6 save area by पढ़ोing dst node's limit reg */
	अगर (pvt->fam != 0x15)
		वापस;

	nb = node_to_amd_nb(dram_dst_node(pvt, range));
	अगर (WARN_ON(!nb))
		वापस;

	अगर (pvt->model == 0x60)
		pci_func = PCI_DEVICE_ID_AMD_15H_M60H_NB_F1;
	अन्यथा अगर (pvt->model == 0x30)
		pci_func = PCI_DEVICE_ID_AMD_15H_M30H_NB_F1;
	अन्यथा
		pci_func = PCI_DEVICE_ID_AMD_15H_NB_F1;

	f1 = pci_get_related_function(nb->misc->venकरोr, pci_func, nb->misc);
	अगर (WARN_ON(!f1))
		वापस;

	amd64_पढ़ो_pci_cfg(f1, DRAM_LOCAL_NODE_LIM, &llim);

	pvt->ranges[range].lim.lo &= GENMASK_ULL(15, 0);

				    /* अणु[39:27],111bपूर्ण */
	pvt->ranges[range].lim.lo |= ((llim & 0x1fff) << 3 | 0x7) << 16;

	pvt->ranges[range].lim.hi &= GENMASK_ULL(7, 0);

				    /* [47:40] */
	pvt->ranges[range].lim.hi |= llim >> 13;

	pci_dev_put(f1);
पूर्ण

अटल व्योम k8_map_sysaddr_to_csrow(काष्ठा mem_ctl_info *mci, u64 sys_addr,
				    काष्ठा err_info *err)
अणु
	काष्ठा amd64_pvt *pvt = mci->pvt_info;

	error_address_to_page_and_offset(sys_addr, err);

	/*
	 * Find out which node the error address beदीर्घs to. This may be
	 * dअगरferent from the node that detected the error.
	 */
	err->src_mci = find_mc_by_sys_addr(mci, sys_addr);
	अगर (!err->src_mci) अणु
		amd64_mc_err(mci, "failed to map error addr 0x%lx to a node\n",
			     (अचिन्हित दीर्घ)sys_addr);
		err->err_code = ERR_NODE;
		वापस;
	पूर्ण

	/* Now map the sys_addr to a CSROW */
	err->csrow = sys_addr_to_csrow(err->src_mci, sys_addr);
	अगर (err->csrow < 0) अणु
		err->err_code = ERR_CSROW;
		वापस;
	पूर्ण

	/* CHIPKILL enabled */
	अगर (pvt->nbcfg & NBCFG_CHIPKILL) अणु
		err->channel = get_channel_from_ecc_syndrome(mci, err->syndrome);
		अगर (err->channel < 0) अणु
			/*
			 * Syndrome didn't map, so we don't know which of the
			 * 2 DIMMs is in error. So we need to ID 'both' of them
			 * as suspect.
			 */
			amd64_mc_warn(err->src_mci, "unknown syndrome 0x%04x - "
				      "possible error reporting race\n",
				      err->syndrome);
			err->err_code = ERR_CHANNEL;
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * non-chipसमाप्त ecc mode
		 *
		 * The k8 करोcumentation is unclear about how to determine the
		 * channel number when using non-chipसमाप्त memory.  This method
		 * was obtained from email communication with someone at AMD.
		 * (Wish the email was placed in this comment - norsk)
		 */
		err->channel = ((sys_addr & BIT(3)) != 0);
	पूर्ण
पूर्ण

अटल पूर्णांक ddr2_cs_size(अचिन्हित i, bool dct_width)
अणु
	अचिन्हित shअगरt = 0;

	अगर (i <= 2)
		shअगरt = i;
	अन्यथा अगर (!(i & 0x1))
		shअगरt = i >> 1;
	अन्यथा
		shअगरt = (i + 1) >> 1;

	वापस 128 << (shअगरt + !!dct_width);
पूर्ण

अटल पूर्णांक k8_dbam_to_chip_select(काष्ठा amd64_pvt *pvt, u8 dct,
				  अचिन्हित cs_mode, पूर्णांक cs_mask_nr)
अणु
	u32 dclr = dct ? pvt->dclr1 : pvt->dclr0;

	अगर (pvt->ext_model >= K8_REV_F) अणु
		WARN_ON(cs_mode > 11);
		वापस ddr2_cs_size(cs_mode, dclr & WIDTH_128);
	पूर्ण
	अन्यथा अगर (pvt->ext_model >= K8_REV_D) अणु
		अचिन्हित dअगरf;
		WARN_ON(cs_mode > 10);

		/*
		 * the below calculation, besides trying to win an obfuscated C
		 * contest, maps cs_mode values to DIMM chip select sizes. The
		 * mappings are:
		 *
		 * cs_mode	CS size (mb)
		 * =======	============
		 * 0		32
		 * 1		64
		 * 2		128
		 * 3		128
		 * 4		256
		 * 5		512
		 * 6		256
		 * 7		512
		 * 8		1024
		 * 9		1024
		 * 10		2048
		 *
		 * Basically, it calculates a value with which to shअगरt the
		 * smallest CS size of 32MB.
		 *
		 * ddr[23]_cs_size have a similar purpose.
		 */
		dअगरf = cs_mode/3 + (अचिन्हित)(cs_mode > 5);

		वापस 32 << (cs_mode - dअगरf);
	पूर्ण
	अन्यथा अणु
		WARN_ON(cs_mode > 6);
		वापस 32 << cs_mode;
	पूर्ण
पूर्ण

/*
 * Get the number of DCT channels in use.
 *
 * Return:
 *	number of Memory Channels in operation
 * Pass back:
 *	contents of the DCL0_LOW रेजिस्टर
 */
अटल पूर्णांक f1x_early_channel_count(काष्ठा amd64_pvt *pvt)
अणु
	पूर्णांक i, j, channels = 0;

	/* On F10h, अगर we are in 128 bit mode, then we are using 2 channels */
	अगर (pvt->fam == 0x10 && (pvt->dclr0 & WIDTH_128))
		वापस 2;

	/*
	 * Need to check अगर in unganged mode: In such, there are 2 channels,
	 * but they are not in 128 bit mode and thus the above 'dclr0' status
	 * bit will be OFF.
	 *
	 * Need to check DCT0[0] and DCT1[0] to see अगर only one of them has
	 * their CSEnable bit on. If so, then SINGLE DIMM हाल.
	 */
	edac_dbg(0, "Data width is not 128 bits - need more decoding\n");

	/*
	 * Check DRAM Bank Address Mapping values क्रम each DIMM to see अगर there
	 * is more than just one DIMM present in unganged mode. Need to check
	 * both controllers since DIMMs can be placed in either one.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		u32 dbam = (i ? pvt->dbam1 : pvt->dbam0);

		क्रम (j = 0; j < 4; j++) अणु
			अगर (DBAM_DIMM(j, dbam) > 0) अणु
				channels++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (channels > 2)
		channels = 2;

	amd64_info("MCT channel count: %d\n", channels);

	वापस channels;
पूर्ण

अटल पूर्णांक f17_early_channel_count(काष्ठा amd64_pvt *pvt)
अणु
	पूर्णांक i, channels = 0;

	/* SDP Control bit 31 (SdpInit) is clear क्रम unused UMC channels */
	क्रम_each_umc(i)
		channels += !!(pvt->umc[i].sdp_ctrl & UMC_SDP_INIT);

	amd64_info("MCT channel count: %d\n", channels);

	वापस channels;
पूर्ण

अटल पूर्णांक ddr3_cs_size(अचिन्हित i, bool dct_width)
अणु
	अचिन्हित shअगरt = 0;
	पूर्णांक cs_size = 0;

	अगर (i == 0 || i == 3 || i == 4)
		cs_size = -1;
	अन्यथा अगर (i <= 2)
		shअगरt = i;
	अन्यथा अगर (i == 12)
		shअगरt = 7;
	अन्यथा अगर (!(i & 0x1))
		shअगरt = i >> 1;
	अन्यथा
		shअगरt = (i + 1) >> 1;

	अगर (cs_size != -1)
		cs_size = (128 * (1 << !!dct_width)) << shअगरt;

	वापस cs_size;
पूर्ण

अटल पूर्णांक ddr3_lrdimm_cs_size(अचिन्हित i, अचिन्हित rank_multiply)
अणु
	अचिन्हित shअगरt = 0;
	पूर्णांक cs_size = 0;

	अगर (i < 4 || i == 6)
		cs_size = -1;
	अन्यथा अगर (i == 12)
		shअगरt = 7;
	अन्यथा अगर (!(i & 0x1))
		shअगरt = i >> 1;
	अन्यथा
		shअगरt = (i + 1) >> 1;

	अगर (cs_size != -1)
		cs_size = rank_multiply * (128 << shअगरt);

	वापस cs_size;
पूर्ण

अटल पूर्णांक ddr4_cs_size(अचिन्हित i)
अणु
	पूर्णांक cs_size = 0;

	अगर (i == 0)
		cs_size = -1;
	अन्यथा अगर (i == 1)
		cs_size = 1024;
	अन्यथा
		/* Min cs_size = 1G */
		cs_size = 1024 * (1 << (i >> 1));

	वापस cs_size;
पूर्ण

अटल पूर्णांक f10_dbam_to_chip_select(काष्ठा amd64_pvt *pvt, u8 dct,
				   अचिन्हित cs_mode, पूर्णांक cs_mask_nr)
अणु
	u32 dclr = dct ? pvt->dclr1 : pvt->dclr0;

	WARN_ON(cs_mode > 11);

	अगर (pvt->dchr0 & DDR3_MODE || pvt->dchr1 & DDR3_MODE)
		वापस ddr3_cs_size(cs_mode, dclr & WIDTH_128);
	अन्यथा
		वापस ddr2_cs_size(cs_mode, dclr & WIDTH_128);
पूर्ण

/*
 * F15h supports only 64bit DCT पूर्णांकerfaces
 */
अटल पूर्णांक f15_dbam_to_chip_select(काष्ठा amd64_pvt *pvt, u8 dct,
				   अचिन्हित cs_mode, पूर्णांक cs_mask_nr)
अणु
	WARN_ON(cs_mode > 12);

	वापस ddr3_cs_size(cs_mode, false);
पूर्ण

/* F15h M60h supports DDR4 mapping as well.. */
अटल पूर्णांक f15_m60h_dbam_to_chip_select(काष्ठा amd64_pvt *pvt, u8 dct,
					अचिन्हित cs_mode, पूर्णांक cs_mask_nr)
अणु
	पूर्णांक cs_size;
	u32 dcsm = pvt->csels[dct].csmasks[cs_mask_nr];

	WARN_ON(cs_mode > 12);

	अगर (pvt->dram_type == MEM_DDR4) अणु
		अगर (cs_mode > 9)
			वापस -1;

		cs_size = ddr4_cs_size(cs_mode);
	पूर्ण अन्यथा अगर (pvt->dram_type == MEM_LRDDR3) अणु
		अचिन्हित rank_multiply = dcsm & 0xf;

		अगर (rank_multiply == 3)
			rank_multiply = 4;
		cs_size = ddr3_lrdimm_cs_size(cs_mode, rank_multiply);
	पूर्ण अन्यथा अणु
		/* Minimum cs size is 512mb क्रम F15hM60h*/
		अगर (cs_mode == 0x1)
			वापस -1;

		cs_size = ddr3_cs_size(cs_mode, false);
	पूर्ण

	वापस cs_size;
पूर्ण

/*
 * F16h and F15h model 30h have only limited cs_modes.
 */
अटल पूर्णांक f16_dbam_to_chip_select(काष्ठा amd64_pvt *pvt, u8 dct,
				अचिन्हित cs_mode, पूर्णांक cs_mask_nr)
अणु
	WARN_ON(cs_mode > 12);

	अगर (cs_mode == 6 || cs_mode == 8 ||
	    cs_mode == 9 || cs_mode == 12)
		वापस -1;
	अन्यथा
		वापस ddr3_cs_size(cs_mode, false);
पूर्ण

अटल पूर्णांक f17_addr_mask_to_cs_size(काष्ठा amd64_pvt *pvt, u8 umc,
				    अचिन्हित पूर्णांक cs_mode, पूर्णांक csrow_nr)
अणु
	u32 addr_mask_orig, addr_mask_deपूर्णांकerleaved;
	u32 msb, weight, num_zero_bits;
	पूर्णांक dimm, size = 0;

	/* No Chip Selects are enabled. */
	अगर (!cs_mode)
		वापस size;

	/* Requested size of an even CS but none are enabled. */
	अगर (!(cs_mode & CS_EVEN) && !(csrow_nr & 1))
		वापस size;

	/* Requested size of an odd CS but none are enabled. */
	अगर (!(cs_mode & CS_ODD) && (csrow_nr & 1))
		वापस size;

	/*
	 * There is one mask per DIMM, and two Chip Selects per DIMM.
	 *	CS0 and CS1 -> DIMM0
	 *	CS2 and CS3 -> DIMM1
	 */
	dimm = csrow_nr >> 1;

	/* Asymmetric dual-rank DIMM support. */
	अगर ((csrow_nr & 1) && (cs_mode & CS_ODD_SECONDARY))
		addr_mask_orig = pvt->csels[umc].csmasks_sec[dimm];
	अन्यथा
		addr_mask_orig = pvt->csels[umc].csmasks[dimm];

	/*
	 * The number of zero bits in the mask is equal to the number of bits
	 * in a full mask minus the number of bits in the current mask.
	 *
	 * The MSB is the number of bits in the full mask because BIT[0] is
	 * always 0.
	 */
	msb = fls(addr_mask_orig) - 1;
	weight = hweight_दीर्घ(addr_mask_orig);
	num_zero_bits = msb - weight;

	/* Take the number of zero bits off from the top of the mask. */
	addr_mask_deपूर्णांकerleaved = GENMASK_ULL(msb - num_zero_bits, 1);

	edac_dbg(1, "CS%d DIMM%d AddrMasks:\n", csrow_nr, dimm);
	edac_dbg(1, "  Original AddrMask: 0x%x\n", addr_mask_orig);
	edac_dbg(1, "  Deinterleaved AddrMask: 0x%x\n", addr_mask_deपूर्णांकerleaved);

	/* Register [31:1] = Address [39:9]. Size is in kBs here. */
	size = (addr_mask_deपूर्णांकerleaved >> 2) + 1;

	/* Return size in MBs. */
	वापस size >> 10;
पूर्ण

अटल व्योम पढ़ो_dram_ctl_रेजिस्टर(काष्ठा amd64_pvt *pvt)
अणु

	अगर (pvt->fam == 0xf)
		वापस;

	अगर (!amd64_पढ़ो_pci_cfg(pvt->F2, DCT_SEL_LO, &pvt->dct_sel_lo)) अणु
		edac_dbg(0, "F2x110 (DCTSelLow): 0x%08x, High range addrs at: 0x%x\n",
			 pvt->dct_sel_lo, dct_sel_baseaddr(pvt));

		edac_dbg(0, "  DCTs operate in %s mode\n",
			 (dct_ganging_enabled(pvt) ? "ganged" : "unganged"));

		अगर (!dct_ganging_enabled(pvt))
			edac_dbg(0, "  Address range split per DCT: %s\n",
				 (dct_high_range_enabled(pvt) ? "yes" : "no"));

		edac_dbg(0, "  data interleave for ECC: %s, DRAM cleared since last warm reset: %s\n",
			 (dct_data_पूर्णांकlv_enabled(pvt) ? "enabled" : "disabled"),
			 (dct_memory_cleared(pvt) ? "yes" : "no"));

		edac_dbg(0, "  channel interleave: %s, "
			 "interleave bits selector: 0x%x\n",
			 (dct_पूर्णांकerleave_enabled(pvt) ? "enabled" : "disabled"),
			 dct_sel_पूर्णांकerleave_addr(pvt));
	पूर्ण

	amd64_पढ़ो_pci_cfg(pvt->F2, DCT_SEL_HI, &pvt->dct_sel_hi);
पूर्ण

/*
 * Determine channel (DCT) based on the पूर्णांकerleaving mode (see F15h M30h BKDG,
 * 2.10.12 Memory Interleaving Modes).
 */
अटल u8 f15_m30h_determine_channel(काष्ठा amd64_pvt *pvt, u64 sys_addr,
				     u8 पूर्णांकlv_en, पूर्णांक num_dcts_पूर्णांकlv,
				     u32 dct_sel)
अणु
	u8 channel = 0;
	u8 select;

	अगर (!(पूर्णांकlv_en))
		वापस (u8)(dct_sel);

	अगर (num_dcts_पूर्णांकlv == 2) अणु
		select = (sys_addr >> 8) & 0x3;
		channel = select ? 0x3 : 0;
	पूर्ण अन्यथा अगर (num_dcts_पूर्णांकlv == 4) अणु
		u8 पूर्णांकlv_addr = dct_sel_पूर्णांकerleave_addr(pvt);
		चयन (पूर्णांकlv_addr) अणु
		हाल 0x4:
			channel = (sys_addr >> 8) & 0x3;
			अवरोध;
		हाल 0x5:
			channel = (sys_addr >> 9) & 0x3;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस channel;
पूर्ण

/*
 * Determine channel (DCT) based on the पूर्णांकerleaving mode: F10h BKDG, 2.8.9 Memory
 * Interleaving Modes.
 */
अटल u8 f1x_determine_channel(काष्ठा amd64_pvt *pvt, u64 sys_addr,
				bool hi_range_sel, u8 पूर्णांकlv_en)
अणु
	u8 dct_sel_high = (pvt->dct_sel_lo >> 1) & 1;

	अगर (dct_ganging_enabled(pvt))
		वापस 0;

	अगर (hi_range_sel)
		वापस dct_sel_high;

	/*
	 * see F2x110[DctSelIntLvAddr] - channel पूर्णांकerleave mode
	 */
	अगर (dct_पूर्णांकerleave_enabled(pvt)) अणु
		u8 पूर्णांकlv_addr = dct_sel_पूर्णांकerleave_addr(pvt);

		/* वापस DCT select function: 0=DCT0, 1=DCT1 */
		अगर (!पूर्णांकlv_addr)
			वापस sys_addr >> 6 & 1;

		अगर (पूर्णांकlv_addr & 0x2) अणु
			u8 shअगरt = पूर्णांकlv_addr & 0x1 ? 9 : 6;
			u32 temp = hweight_दीर्घ((u32) ((sys_addr >> 16) & 0x1F)) & 1;

			वापस ((sys_addr >> shअगरt) & 1) ^ temp;
		पूर्ण

		अगर (पूर्णांकlv_addr & 0x4) अणु
			u8 shअगरt = पूर्णांकlv_addr & 0x1 ? 9 : 8;

			वापस (sys_addr >> shअगरt) & 1;
		पूर्ण

		वापस (sys_addr >> (12 + hweight8(पूर्णांकlv_en))) & 1;
	पूर्ण

	अगर (dct_high_range_enabled(pvt))
		वापस ~dct_sel_high & 1;

	वापस 0;
पूर्ण

/* Convert the sys_addr to the normalized DCT address */
अटल u64 f1x_get_norm_dct_addr(काष्ठा amd64_pvt *pvt, u8 range,
				 u64 sys_addr, bool hi_rng,
				 u32 dct_sel_base_addr)
अणु
	u64 chan_off;
	u64 dram_base		= get_dram_base(pvt, range);
	u64 hole_off		= f10_dhar_offset(pvt);
	u64 dct_sel_base_off	= (u64)(pvt->dct_sel_hi & 0xFFFFFC00) << 16;

	अगर (hi_rng) अणु
		/*
		 * अगर
		 * base address of high range is below 4Gb
		 * (bits [47:27] at [31:11])
		 * DRAM address space on this DCT is hoisted above 4Gb	&&
		 * sys_addr > 4Gb
		 *
		 *	हटाओ hole offset from sys_addr
		 * अन्यथा
		 *	हटाओ high range offset from sys_addr
		 */
		अगर ((!(dct_sel_base_addr >> 16) ||
		     dct_sel_base_addr < dhar_base(pvt)) &&
		    dhar_valid(pvt) &&
		    (sys_addr >= BIT_64(32)))
			chan_off = hole_off;
		अन्यथा
			chan_off = dct_sel_base_off;
	पूर्ण अन्यथा अणु
		/*
		 * अगर
		 * we have a valid hole		&&
		 * sys_addr > 4Gb
		 *
		 *	हटाओ hole
		 * अन्यथा
		 *	हटाओ dram base to normalize to DCT address
		 */
		अगर (dhar_valid(pvt) && (sys_addr >= BIT_64(32)))
			chan_off = hole_off;
		अन्यथा
			chan_off = dram_base;
	पूर्ण

	वापस (sys_addr & GENMASK_ULL(47,6)) - (chan_off & GENMASK_ULL(47,23));
पूर्ण

/*
 * checks अगर the csrow passed in is marked as SPARED, अगर so वापसs the new
 * spare row
 */
अटल पूर्णांक f10_process_possible_spare(काष्ठा amd64_pvt *pvt, u8 dct, पूर्णांक csrow)
अणु
	पूर्णांक पंचांगp_cs;

	अगर (online_spare_swap_करोne(pvt, dct) &&
	    csrow == online_spare_bad_dramcs(pvt, dct)) अणु

		क्रम_each_chip_select(पंचांगp_cs, dct, pvt) अणु
			अगर (chip_select_base(पंचांगp_cs, dct, pvt) & 0x2) अणु
				csrow = पंचांगp_cs;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस csrow;
पूर्ण

/*
 * Iterate over the DRAM DCT "base" and "mask" रेजिस्टरs looking क्रम a
 * SystemAddr match on the specअगरied 'ChannelSelect' and 'NodeID'
 *
 * Return:
 *	-EINVAL:  NOT FOUND
 *	0..csrow = Chip-Select Row
 */
अटल पूर्णांक f1x_lookup_addr_in_dct(u64 in_addr, u8 nid, u8 dct)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा amd64_pvt *pvt;
	u64 cs_base, cs_mask;
	पूर्णांक cs_found = -EINVAL;
	पूर्णांक csrow;

	mci = edac_mc_find(nid);
	अगर (!mci)
		वापस cs_found;

	pvt = mci->pvt_info;

	edac_dbg(1, "input addr: 0x%llx, DCT: %d\n", in_addr, dct);

	क्रम_each_chip_select(csrow, dct, pvt) अणु
		अगर (!csrow_enabled(csrow, dct, pvt))
			जारी;

		get_cs_base_and_mask(pvt, csrow, dct, &cs_base, &cs_mask);

		edac_dbg(1, "    CSROW=%d CSBase=0x%llx CSMask=0x%llx\n",
			 csrow, cs_base, cs_mask);

		cs_mask = ~cs_mask;

		edac_dbg(1, "    (InputAddr & ~CSMask)=0x%llx (CSBase & ~CSMask)=0x%llx\n",
			 (in_addr & cs_mask), (cs_base & cs_mask));

		अगर ((in_addr & cs_mask) == (cs_base & cs_mask)) अणु
			अगर (pvt->fam == 0x15 && pvt->model >= 0x30) अणु
				cs_found =  csrow;
				अवरोध;
			पूर्ण
			cs_found = f10_process_possible_spare(pvt, dct, csrow);

			edac_dbg(1, " MATCH csrow=%d\n", cs_found);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस cs_found;
पूर्ण

/*
 * See F2x10C. Non-पूर्णांकerleaved graphics framebuffer memory under the 16G is
 * swapped with a region located at the bottom of memory so that the GPU can use
 * the पूर्णांकerleaved region and thus two channels.
 */
अटल u64 f1x_swap_पूर्णांकerleaved_region(काष्ठा amd64_pvt *pvt, u64 sys_addr)
अणु
	u32 swap_reg, swap_base, swap_limit, rgn_size, पंचांगp_addr;

	अगर (pvt->fam == 0x10) अणु
		/* only revC3 and revE have that feature */
		अगर (pvt->model < 4 || (pvt->model < 0xa && pvt->stepping < 3))
			वापस sys_addr;
	पूर्ण

	amd64_पढ़ो_pci_cfg(pvt->F2, SWAP_INTLV_REG, &swap_reg);

	अगर (!(swap_reg & 0x1))
		वापस sys_addr;

	swap_base	= (swap_reg >> 3) & 0x7f;
	swap_limit	= (swap_reg >> 11) & 0x7f;
	rgn_size	= (swap_reg >> 20) & 0x7f;
	पंचांगp_addr	= sys_addr >> 27;

	अगर (!(sys_addr >> 34) &&
	    (((पंचांगp_addr >= swap_base) &&
	     (पंचांगp_addr <= swap_limit)) ||
	     (पंचांगp_addr < rgn_size)))
		वापस sys_addr ^ (u64)swap_base << 27;

	वापस sys_addr;
पूर्ण

/* For a given @dram_range, check अगर @sys_addr falls within it. */
अटल पूर्णांक f1x_match_to_this_node(काष्ठा amd64_pvt *pvt, अचिन्हित range,
				  u64 sys_addr, पूर्णांक *chan_sel)
अणु
	पूर्णांक cs_found = -EINVAL;
	u64 chan_addr;
	u32 dct_sel_base;
	u8 channel;
	bool high_range = false;

	u8 node_id    = dram_dst_node(pvt, range);
	u8 पूर्णांकlv_en   = dram_पूर्णांकlv_en(pvt, range);
	u32 पूर्णांकlv_sel = dram_पूर्णांकlv_sel(pvt, range);

	edac_dbg(1, "(range %d) SystemAddr= 0x%llx Limit=0x%llx\n",
		 range, sys_addr, get_dram_limit(pvt, range));

	अगर (dhar_valid(pvt) &&
	    dhar_base(pvt) <= sys_addr &&
	    sys_addr < BIT_64(32)) अणु
		amd64_warn("Huh? Address is in the MMIO hole: 0x%016llx\n",
			    sys_addr);
		वापस -EINVAL;
	पूर्ण

	अगर (पूर्णांकlv_en && (पूर्णांकlv_sel != ((sys_addr >> 12) & पूर्णांकlv_en)))
		वापस -EINVAL;

	sys_addr = f1x_swap_पूर्णांकerleaved_region(pvt, sys_addr);

	dct_sel_base = dct_sel_baseaddr(pvt);

	/*
	 * check whether addresses >= DctSelBaseAddr[47:27] are to be used to
	 * select between DCT0 and DCT1.
	 */
	अगर (dct_high_range_enabled(pvt) &&
	   !dct_ganging_enabled(pvt) &&
	   ((sys_addr >> 27) >= (dct_sel_base >> 11)))
		high_range = true;

	channel = f1x_determine_channel(pvt, sys_addr, high_range, पूर्णांकlv_en);

	chan_addr = f1x_get_norm_dct_addr(pvt, range, sys_addr,
					  high_range, dct_sel_base);

	/* Remove node पूर्णांकerleaving, see F1x120 */
	अगर (पूर्णांकlv_en)
		chan_addr = ((chan_addr >> (12 + hweight8(पूर्णांकlv_en))) << 12) |
			    (chan_addr & 0xfff);

	/* हटाओ channel पूर्णांकerleave */
	अगर (dct_पूर्णांकerleave_enabled(pvt) &&
	   !dct_high_range_enabled(pvt) &&
	   !dct_ganging_enabled(pvt)) अणु

		अगर (dct_sel_पूर्णांकerleave_addr(pvt) != 1) अणु
			अगर (dct_sel_पूर्णांकerleave_addr(pvt) == 0x3)
				/* hash 9 */
				chan_addr = ((chan_addr >> 10) << 9) |
					     (chan_addr & 0x1ff);
			अन्यथा
				/* A[6] or hash 6 */
				chan_addr = ((chan_addr >> 7) << 6) |
					     (chan_addr & 0x3f);
		पूर्ण अन्यथा
			/* A[12] */
			chan_addr = ((chan_addr >> 13) << 12) |
				     (chan_addr & 0xfff);
	पूर्ण

	edac_dbg(1, "   Normalized DCT addr: 0x%llx\n", chan_addr);

	cs_found = f1x_lookup_addr_in_dct(chan_addr, node_id, channel);

	अगर (cs_found >= 0)
		*chan_sel = channel;

	वापस cs_found;
पूर्ण

अटल पूर्णांक f15_m30h_match_to_this_node(काष्ठा amd64_pvt *pvt, अचिन्हित range,
					u64 sys_addr, पूर्णांक *chan_sel)
अणु
	पूर्णांक cs_found = -EINVAL;
	पूर्णांक num_dcts_पूर्णांकlv = 0;
	u64 chan_addr, chan_offset;
	u64 dct_base, dct_limit;
	u32 dct_cont_base_reg, dct_cont_limit_reg, पंचांगp;
	u8 channel, alias_channel, leg_mmio_hole, dct_sel, dct_offset_en;

	u64 dhar_offset		= f10_dhar_offset(pvt);
	u8 पूर्णांकlv_addr		= dct_sel_पूर्णांकerleave_addr(pvt);
	u8 node_id		= dram_dst_node(pvt, range);
	u8 पूर्णांकlv_en		= dram_पूर्णांकlv_en(pvt, range);

	amd64_पढ़ो_pci_cfg(pvt->F1, DRAM_CONT_BASE, &dct_cont_base_reg);
	amd64_पढ़ो_pci_cfg(pvt->F1, DRAM_CONT_LIMIT, &dct_cont_limit_reg);

	dct_offset_en		= (u8) ((dct_cont_base_reg >> 3) & BIT(0));
	dct_sel			= (u8) ((dct_cont_base_reg >> 4) & 0x7);

	edac_dbg(1, "(range %d) SystemAddr= 0x%llx Limit=0x%llx\n",
		 range, sys_addr, get_dram_limit(pvt, range));

	अगर (!(get_dram_base(pvt, range)  <= sys_addr) &&
	    !(get_dram_limit(pvt, range) >= sys_addr))
		वापस -EINVAL;

	अगर (dhar_valid(pvt) &&
	    dhar_base(pvt) <= sys_addr &&
	    sys_addr < BIT_64(32)) अणु
		amd64_warn("Huh? Address is in the MMIO hole: 0x%016llx\n",
			    sys_addr);
		वापस -EINVAL;
	पूर्ण

	/* Verअगरy sys_addr is within DCT Range. */
	dct_base = (u64) dct_sel_baseaddr(pvt);
	dct_limit = (dct_cont_limit_reg >> 11) & 0x1FFF;

	अगर (!(dct_cont_base_reg & BIT(0)) &&
	    !(dct_base <= (sys_addr >> 27) &&
	      dct_limit >= (sys_addr >> 27)))
		वापस -EINVAL;

	/* Verअगरy number of dct's that participate in channel पूर्णांकerleaving. */
	num_dcts_पूर्णांकlv = (पूर्णांक) hweight8(पूर्णांकlv_en);

	अगर (!(num_dcts_पूर्णांकlv % 2 == 0) || (num_dcts_पूर्णांकlv > 4))
		वापस -EINVAL;

	अगर (pvt->model >= 0x60)
		channel = f1x_determine_channel(pvt, sys_addr, false, पूर्णांकlv_en);
	अन्यथा
		channel = f15_m30h_determine_channel(pvt, sys_addr, पूर्णांकlv_en,
						     num_dcts_पूर्णांकlv, dct_sel);

	/* Verअगरy we stay within the MAX number of channels allowed */
	अगर (channel > 3)
		वापस -EINVAL;

	leg_mmio_hole = (u8) (dct_cont_base_reg >> 1 & BIT(0));

	/* Get normalized DCT addr */
	अगर (leg_mmio_hole && (sys_addr >= BIT_64(32)))
		chan_offset = dhar_offset;
	अन्यथा
		chan_offset = dct_base << 27;

	chan_addr = sys_addr - chan_offset;

	/* हटाओ channel पूर्णांकerleave */
	अगर (num_dcts_पूर्णांकlv == 2) अणु
		अगर (पूर्णांकlv_addr == 0x4)
			chan_addr = ((chan_addr >> 9) << 8) |
						(chan_addr & 0xff);
		अन्यथा अगर (पूर्णांकlv_addr == 0x5)
			chan_addr = ((chan_addr >> 10) << 9) |
						(chan_addr & 0x1ff);
		अन्यथा
			वापस -EINVAL;

	पूर्ण अन्यथा अगर (num_dcts_पूर्णांकlv == 4) अणु
		अगर (पूर्णांकlv_addr == 0x4)
			chan_addr = ((chan_addr >> 10) << 8) |
							(chan_addr & 0xff);
		अन्यथा अगर (पूर्णांकlv_addr == 0x5)
			chan_addr = ((chan_addr >> 11) << 9) |
							(chan_addr & 0x1ff);
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (dct_offset_en) अणु
		amd64_पढ़ो_pci_cfg(pvt->F1,
				   DRAM_CONT_HIGH_OFF + (पूर्णांक) channel * 4,
				   &पंचांगp);
		chan_addr +=  (u64) ((पंचांगp >> 11) & 0xfff) << 27;
	पूर्ण

	f15h_select_dct(pvt, channel);

	edac_dbg(1, "   Normalized DCT addr: 0x%llx\n", chan_addr);

	/*
	 * Find Chip select:
	 * अगर channel = 3, then alias it to 1. This is because, in F15 M30h,
	 * there is support क्रम 4 DCT's, but only 2 are currently functional.
	 * They are DCT0 and DCT3. But we have पढ़ो all रेजिस्टरs of DCT3 पूर्णांकo
	 * pvt->csels[1]. So we need to use '1' here to get correct info.
	 * Refer F15 M30h BKDG Section 2.10 and 2.10.3 क्रम clarअगरications.
	 */
	alias_channel =  (channel == 3) ? 1 : channel;

	cs_found = f1x_lookup_addr_in_dct(chan_addr, node_id, alias_channel);

	अगर (cs_found >= 0)
		*chan_sel = alias_channel;

	वापस cs_found;
पूर्ण

अटल पूर्णांक f1x_translate_sysaddr_to_cs(काष्ठा amd64_pvt *pvt,
					u64 sys_addr,
					पूर्णांक *chan_sel)
अणु
	पूर्णांक cs_found = -EINVAL;
	अचिन्हित range;

	क्रम (range = 0; range < DRAM_RANGES; range++) अणु
		अगर (!dram_rw(pvt, range))
			जारी;

		अगर (pvt->fam == 0x15 && pvt->model >= 0x30)
			cs_found = f15_m30h_match_to_this_node(pvt, range,
							       sys_addr,
							       chan_sel);

		अन्यथा अगर ((get_dram_base(pvt, range)  <= sys_addr) &&
			 (get_dram_limit(pvt, range) >= sys_addr)) अणु
			cs_found = f1x_match_to_this_node(pvt, range,
							  sys_addr, chan_sel);
			अगर (cs_found >= 0)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस cs_found;
पूर्ण

/*
 * For reference see "2.8.5 Routing DRAM Requests" in F10 BKDG. This code maps
 * a @sys_addr to NodeID, DCT (channel) and chip select (CSROW).
 *
 * The @sys_addr is usually an error address received from the hardware
 * (MCX_ADDR).
 */
अटल व्योम f1x_map_sysaddr_to_csrow(काष्ठा mem_ctl_info *mci, u64 sys_addr,
				     काष्ठा err_info *err)
अणु
	काष्ठा amd64_pvt *pvt = mci->pvt_info;

	error_address_to_page_and_offset(sys_addr, err);

	err->csrow = f1x_translate_sysaddr_to_cs(pvt, sys_addr, &err->channel);
	अगर (err->csrow < 0) अणु
		err->err_code = ERR_CSROW;
		वापस;
	पूर्ण

	/*
	 * We need the syndromes क्रम channel detection only when we're
	 * ganged. Otherwise @chan should alपढ़ोy contain the channel at
	 * this poपूर्णांक.
	 */
	अगर (dct_ganging_enabled(pvt))
		err->channel = get_channel_from_ecc_syndrome(mci, err->syndrome);
पूर्ण

/*
 * debug routine to display the memory sizes of all logical DIMMs and its
 * CSROWs
 */
अटल व्योम debug_display_dimm_sizes(काष्ठा amd64_pvt *pvt, u8 ctrl)
अणु
	पूर्णांक dimm, size0, size1;
	u32 *dcsb = ctrl ? pvt->csels[1].csbases : pvt->csels[0].csbases;
	u32 dbam  = ctrl ? pvt->dbam1 : pvt->dbam0;

	अगर (pvt->fam == 0xf) अणु
		/* K8 families < revF not supported yet */
	       अगर (pvt->ext_model < K8_REV_F)
			वापस;
	       अन्यथा
		       WARN_ON(ctrl != 0);
	पूर्ण

	अगर (pvt->fam == 0x10) अणु
		dbam = (ctrl && !dct_ganging_enabled(pvt)) ? pvt->dbam1
							   : pvt->dbam0;
		dcsb = (ctrl && !dct_ganging_enabled(pvt)) ?
				 pvt->csels[1].csbases :
				 pvt->csels[0].csbases;
	पूर्ण अन्यथा अगर (ctrl) अणु
		dbam = pvt->dbam0;
		dcsb = pvt->csels[1].csbases;
	पूर्ण
	edac_dbg(1, "F2x%d80 (DRAM Bank Address Mapping): 0x%08x\n",
		 ctrl, dbam);

	edac_prपूर्णांकk(KERN_DEBUG, EDAC_MC, "DCT%d chip selects:\n", ctrl);

	/* Dump memory sizes क्रम DIMM and its CSROWs */
	क्रम (dimm = 0; dimm < 4; dimm++) अणु

		size0 = 0;
		अगर (dcsb[dimm*2] & DCSB_CS_ENABLE)
			/*
			 * For F15m60h, we need multiplier क्रम LRDIMM cs_size
			 * calculation. We pass dimm value to the dbam_to_cs
			 * mapper so we can find the multiplier from the
			 * corresponding DCSM.
			 */
			size0 = pvt->ops->dbam_to_cs(pvt, ctrl,
						     DBAM_DIMM(dimm, dbam),
						     dimm);

		size1 = 0;
		अगर (dcsb[dimm*2 + 1] & DCSB_CS_ENABLE)
			size1 = pvt->ops->dbam_to_cs(pvt, ctrl,
						     DBAM_DIMM(dimm, dbam),
						     dimm);

		amd64_info(EDAC_MC ": %d: %5dMB %d: %5dMB\n",
				dimm * 2,     size0,
				dimm * 2 + 1, size1);
	पूर्ण
पूर्ण

अटल काष्ठा amd64_family_type family_types[] = अणु
	[K8_CPUS] = अणु
		.ctl_name = "K8",
		.f1_id = PCI_DEVICE_ID_AMD_K8_NB_ADDRMAP,
		.f2_id = PCI_DEVICE_ID_AMD_K8_NB_MEMCTL,
		.max_mcs = 2,
		.ops = अणु
			.early_channel_count	= k8_early_channel_count,
			.map_sysaddr_to_csrow	= k8_map_sysaddr_to_csrow,
			.dbam_to_cs		= k8_dbam_to_chip_select,
		पूर्ण
	पूर्ण,
	[F10_CPUS] = अणु
		.ctl_name = "F10h",
		.f1_id = PCI_DEVICE_ID_AMD_10H_NB_MAP,
		.f2_id = PCI_DEVICE_ID_AMD_10H_NB_DRAM,
		.max_mcs = 2,
		.ops = अणु
			.early_channel_count	= f1x_early_channel_count,
			.map_sysaddr_to_csrow	= f1x_map_sysaddr_to_csrow,
			.dbam_to_cs		= f10_dbam_to_chip_select,
		पूर्ण
	पूर्ण,
	[F15_CPUS] = अणु
		.ctl_name = "F15h",
		.f1_id = PCI_DEVICE_ID_AMD_15H_NB_F1,
		.f2_id = PCI_DEVICE_ID_AMD_15H_NB_F2,
		.max_mcs = 2,
		.ops = अणु
			.early_channel_count	= f1x_early_channel_count,
			.map_sysaddr_to_csrow	= f1x_map_sysaddr_to_csrow,
			.dbam_to_cs		= f15_dbam_to_chip_select,
		पूर्ण
	पूर्ण,
	[F15_M30H_CPUS] = अणु
		.ctl_name = "F15h_M30h",
		.f1_id = PCI_DEVICE_ID_AMD_15H_M30H_NB_F1,
		.f2_id = PCI_DEVICE_ID_AMD_15H_M30H_NB_F2,
		.max_mcs = 2,
		.ops = अणु
			.early_channel_count	= f1x_early_channel_count,
			.map_sysaddr_to_csrow	= f1x_map_sysaddr_to_csrow,
			.dbam_to_cs		= f16_dbam_to_chip_select,
		पूर्ण
	पूर्ण,
	[F15_M60H_CPUS] = अणु
		.ctl_name = "F15h_M60h",
		.f1_id = PCI_DEVICE_ID_AMD_15H_M60H_NB_F1,
		.f2_id = PCI_DEVICE_ID_AMD_15H_M60H_NB_F2,
		.max_mcs = 2,
		.ops = अणु
			.early_channel_count	= f1x_early_channel_count,
			.map_sysaddr_to_csrow	= f1x_map_sysaddr_to_csrow,
			.dbam_to_cs		= f15_m60h_dbam_to_chip_select,
		पूर्ण
	पूर्ण,
	[F16_CPUS] = अणु
		.ctl_name = "F16h",
		.f1_id = PCI_DEVICE_ID_AMD_16H_NB_F1,
		.f2_id = PCI_DEVICE_ID_AMD_16H_NB_F2,
		.max_mcs = 2,
		.ops = अणु
			.early_channel_count	= f1x_early_channel_count,
			.map_sysaddr_to_csrow	= f1x_map_sysaddr_to_csrow,
			.dbam_to_cs		= f16_dbam_to_chip_select,
		पूर्ण
	पूर्ण,
	[F16_M30H_CPUS] = अणु
		.ctl_name = "F16h_M30h",
		.f1_id = PCI_DEVICE_ID_AMD_16H_M30H_NB_F1,
		.f2_id = PCI_DEVICE_ID_AMD_16H_M30H_NB_F2,
		.max_mcs = 2,
		.ops = अणु
			.early_channel_count	= f1x_early_channel_count,
			.map_sysaddr_to_csrow	= f1x_map_sysaddr_to_csrow,
			.dbam_to_cs		= f16_dbam_to_chip_select,
		पूर्ण
	पूर्ण,
	[F17_CPUS] = अणु
		.ctl_name = "F17h",
		.f0_id = PCI_DEVICE_ID_AMD_17H_DF_F0,
		.f6_id = PCI_DEVICE_ID_AMD_17H_DF_F6,
		.max_mcs = 2,
		.ops = अणु
			.early_channel_count	= f17_early_channel_count,
			.dbam_to_cs		= f17_addr_mask_to_cs_size,
		पूर्ण
	पूर्ण,
	[F17_M10H_CPUS] = अणु
		.ctl_name = "F17h_M10h",
		.f0_id = PCI_DEVICE_ID_AMD_17H_M10H_DF_F0,
		.f6_id = PCI_DEVICE_ID_AMD_17H_M10H_DF_F6,
		.max_mcs = 2,
		.ops = अणु
			.early_channel_count	= f17_early_channel_count,
			.dbam_to_cs		= f17_addr_mask_to_cs_size,
		पूर्ण
	पूर्ण,
	[F17_M30H_CPUS] = अणु
		.ctl_name = "F17h_M30h",
		.f0_id = PCI_DEVICE_ID_AMD_17H_M30H_DF_F0,
		.f6_id = PCI_DEVICE_ID_AMD_17H_M30H_DF_F6,
		.max_mcs = 8,
		.ops = अणु
			.early_channel_count	= f17_early_channel_count,
			.dbam_to_cs		= f17_addr_mask_to_cs_size,
		पूर्ण
	पूर्ण,
	[F17_M60H_CPUS] = अणु
		.ctl_name = "F17h_M60h",
		.f0_id = PCI_DEVICE_ID_AMD_17H_M60H_DF_F0,
		.f6_id = PCI_DEVICE_ID_AMD_17H_M60H_DF_F6,
		.max_mcs = 2,
		.ops = अणु
			.early_channel_count	= f17_early_channel_count,
			.dbam_to_cs		= f17_addr_mask_to_cs_size,
		पूर्ण
	पूर्ण,
	[F17_M70H_CPUS] = अणु
		.ctl_name = "F17h_M70h",
		.f0_id = PCI_DEVICE_ID_AMD_17H_M70H_DF_F0,
		.f6_id = PCI_DEVICE_ID_AMD_17H_M70H_DF_F6,
		.max_mcs = 2,
		.ops = अणु
			.early_channel_count	= f17_early_channel_count,
			.dbam_to_cs		= f17_addr_mask_to_cs_size,
		पूर्ण
	पूर्ण,
	[F19_CPUS] = अणु
		.ctl_name = "F19h",
		.f0_id = PCI_DEVICE_ID_AMD_19H_DF_F0,
		.f6_id = PCI_DEVICE_ID_AMD_19H_DF_F6,
		.max_mcs = 8,
		.ops = अणु
			.early_channel_count	= f17_early_channel_count,
			.dbam_to_cs		= f17_addr_mask_to_cs_size,
		पूर्ण
	पूर्ण,
पूर्ण;

/*
 * These are tables of eigenvectors (one per line) which can be used क्रम the
 * स्थिरruction of the syndrome tables. The modअगरied syndrome search algorithm
 * uses those to find the symbol in error and thus the DIMM.
 *
 * Algorithm courtesy of Ross LaFetra from AMD.
 */
अटल स्थिर u16 x4_vectors[] = अणु
	0x2f57, 0x1afe, 0x66cc, 0xdd88,
	0x11eb, 0x3396, 0x7f4c, 0xeac8,
	0x0001, 0x0002, 0x0004, 0x0008,
	0x1013, 0x3032, 0x4044, 0x8088,
	0x106b, 0x30d6, 0x70fc, 0xe0a8,
	0x4857, 0xc4fe, 0x13cc, 0x3288,
	0x1ac5, 0x2f4a, 0x5394, 0xa1e8,
	0x1f39, 0x251e, 0xbd6c, 0x6bd8,
	0x15c1, 0x2a42, 0x89ac, 0x4758,
	0x2b03, 0x1602, 0x4f0c, 0xca08,
	0x1f07, 0x3a0e, 0x6b04, 0xbd08,
	0x8ba7, 0x465e, 0x244c, 0x1cc8,
	0x2b87, 0x164e, 0x642c, 0xdc18,
	0x40b9, 0x80de, 0x1094, 0x20e8,
	0x27db, 0x1eb6, 0x9dac, 0x7b58,
	0x11c1, 0x2242, 0x84ac, 0x4c58,
	0x1be5, 0x2d7a, 0x5e34, 0xa718,
	0x4b39, 0x8d1e, 0x14b4, 0x28d8,
	0x4c97, 0xc87e, 0x11fc, 0x33a8,
	0x8e97, 0x497e, 0x2ffc, 0x1aa8,
	0x16b3, 0x3d62, 0x4f34, 0x8518,
	0x1e2f, 0x391a, 0x5cac, 0xf858,
	0x1d9f, 0x3b7a, 0x572c, 0xfe18,
	0x15f5, 0x2a5a, 0x5264, 0xa3b8,
	0x1dbb, 0x3b66, 0x715c, 0xe3f8,
	0x4397, 0xc27e, 0x17fc, 0x3ea8,
	0x1617, 0x3d3e, 0x6464, 0xb8b8,
	0x23ff, 0x12aa, 0xab6c, 0x56d8,
	0x2dfb, 0x1ba6, 0x913c, 0x7328,
	0x185d, 0x2ca6, 0x7914, 0x9e28,
	0x171b, 0x3e36, 0x7d7c, 0xebe8,
	0x4199, 0x82ee, 0x19f4, 0x2e58,
	0x4807, 0xc40e, 0x130c, 0x3208,
	0x1905, 0x2e0a, 0x5804, 0xac08,
	0x213f, 0x132a, 0xadfc, 0x5ba8,
	0x19a9, 0x2efe, 0xb5cc, 0x6f88,
पूर्ण;

अटल स्थिर u16 x8_vectors[] = अणु
	0x0145, 0x028a, 0x2374, 0x43c8, 0xa1f0, 0x0520, 0x0a40, 0x1480,
	0x0211, 0x0422, 0x0844, 0x1088, 0x01b0, 0x44e0, 0x23c0, 0xed80,
	0x1011, 0x0116, 0x022c, 0x0458, 0x08b0, 0x8c60, 0x2740, 0x4e80,
	0x0411, 0x0822, 0x1044, 0x0158, 0x02b0, 0x2360, 0x46c0, 0xab80,
	0x0811, 0x1022, 0x012c, 0x0258, 0x04b0, 0x4660, 0x8cc0, 0x2780,
	0x2071, 0x40e2, 0xa0c4, 0x0108, 0x0210, 0x0420, 0x0840, 0x1080,
	0x4071, 0x80e2, 0x0104, 0x0208, 0x0410, 0x0820, 0x1040, 0x2080,
	0x8071, 0x0102, 0x0204, 0x0408, 0x0810, 0x1020, 0x2040, 0x4080,
	0x019d, 0x03d6, 0x136c, 0x2198, 0x50b0, 0xb2e0, 0x0740, 0x0e80,
	0x0189, 0x03ea, 0x072c, 0x0e58, 0x1cb0, 0x56e0, 0x37c0, 0xf580,
	0x01fd, 0x0376, 0x06ec, 0x0bb8, 0x1110, 0x2220, 0x4440, 0x8880,
	0x0163, 0x02c6, 0x1104, 0x0758, 0x0eb0, 0x2be0, 0x6140, 0xc280,
	0x02fd, 0x01c6, 0x0b5c, 0x1108, 0x07b0, 0x25a0, 0x8840, 0x6180,
	0x0801, 0x012e, 0x025c, 0x04b8, 0x1370, 0x26e0, 0x57c0, 0xb580,
	0x0401, 0x0802, 0x015c, 0x02b8, 0x22b0, 0x13e0, 0x7140, 0xe280,
	0x0201, 0x0402, 0x0804, 0x01b8, 0x11b0, 0x31a0, 0x8040, 0x7180,
	0x0101, 0x0202, 0x0404, 0x0808, 0x1010, 0x2020, 0x4040, 0x8080,
	0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
	0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000,
पूर्ण;

अटल पूर्णांक decode_syndrome(u16 syndrome, स्थिर u16 *vectors, अचिन्हित num_vecs,
			   अचिन्हित v_dim)
अणु
	अचिन्हित पूर्णांक i, err_sym;

	क्रम (err_sym = 0; err_sym < num_vecs / v_dim; err_sym++) अणु
		u16 s = syndrome;
		अचिन्हित v_idx =  err_sym * v_dim;
		अचिन्हित v_end = (err_sym + 1) * v_dim;

		/* walk over all 16 bits of the syndrome */
		क्रम (i = 1; i < (1U << 16); i <<= 1) अणु

			/* अगर bit is set in that eigenvector... */
			अगर (v_idx < v_end && vectors[v_idx] & i) अणु
				u16 ev_comp = vectors[v_idx++];

				/* ... and bit set in the modअगरied syndrome, */
				अगर (s & i) अणु
					/* हटाओ it. */
					s ^= ev_comp;

					अगर (!s)
						वापस err_sym;
				पूर्ण

			पूर्ण अन्यथा अगर (s & i)
				/* can't get to zero, move to next symbol */
				अवरोध;
		पूर्ण
	पूर्ण

	edac_dbg(0, "syndrome(%x) not found\n", syndrome);
	वापस -1;
पूर्ण

अटल पूर्णांक map_err_sym_to_channel(पूर्णांक err_sym, पूर्णांक sym_size)
अणु
	अगर (sym_size == 4)
		चयन (err_sym) अणु
		हाल 0x20:
		हाल 0x21:
			वापस 0;
		हाल 0x22:
		हाल 0x23:
			वापस 1;
		शेष:
			वापस err_sym >> 4;
		पूर्ण
	/* x8 symbols */
	अन्यथा
		चयन (err_sym) अणु
		/* imaginary bits not in a DIMM */
		हाल 0x10:
			WARN(1, KERN_ERR "Invalid error symbol: 0x%x\n",
					  err_sym);
			वापस -1;
		हाल 0x11:
			वापस 0;
		हाल 0x12:
			वापस 1;
		शेष:
			वापस err_sym >> 3;
		पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक get_channel_from_ecc_syndrome(काष्ठा mem_ctl_info *mci, u16 syndrome)
अणु
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	पूर्णांक err_sym = -1;

	अगर (pvt->ecc_sym_sz == 8)
		err_sym = decode_syndrome(syndrome, x8_vectors,
					  ARRAY_SIZE(x8_vectors),
					  pvt->ecc_sym_sz);
	अन्यथा अगर (pvt->ecc_sym_sz == 4)
		err_sym = decode_syndrome(syndrome, x4_vectors,
					  ARRAY_SIZE(x4_vectors),
					  pvt->ecc_sym_sz);
	अन्यथा अणु
		amd64_warn("Illegal syndrome type: %u\n", pvt->ecc_sym_sz);
		वापस err_sym;
	पूर्ण

	वापस map_err_sym_to_channel(err_sym, pvt->ecc_sym_sz);
पूर्ण

अटल व्योम __log_ecc_error(काष्ठा mem_ctl_info *mci, काष्ठा err_info *err,
			    u8 ecc_type)
अणु
	क्रमागत hw_event_mc_err_type err_type;
	स्थिर अक्षर *string;

	अगर (ecc_type == 2)
		err_type = HW_EVENT_ERR_CORRECTED;
	अन्यथा अगर (ecc_type == 1)
		err_type = HW_EVENT_ERR_UNCORRECTED;
	अन्यथा अगर (ecc_type == 3)
		err_type = HW_EVENT_ERR_DEFERRED;
	अन्यथा अणु
		WARN(1, "Something is rotten in the state of Denmark.\n");
		वापस;
	पूर्ण

	चयन (err->err_code) अणु
	हाल DECODE_OK:
		string = "";
		अवरोध;
	हाल ERR_NODE:
		string = "Failed to map error addr to a node";
		अवरोध;
	हाल ERR_CSROW:
		string = "Failed to map error addr to a csrow";
		अवरोध;
	हाल ERR_CHANNEL:
		string = "Unknown syndrome - possible error reporting race";
		अवरोध;
	हाल ERR_SYND:
		string = "MCA_SYND not valid - unknown syndrome and csrow";
		अवरोध;
	हाल ERR_NORM_ADDR:
		string = "Cannot decode normalized address";
		अवरोध;
	शेष:
		string = "WTF error";
		अवरोध;
	पूर्ण

	edac_mc_handle_error(err_type, mci, 1,
			     err->page, err->offset, err->syndrome,
			     err->csrow, err->channel, -1,
			     string, "");
पूर्ण

अटल अंतरभूत व्योम decode_bus_error(पूर्णांक node_id, काष्ठा mce *m)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा amd64_pvt *pvt;
	u8 ecc_type = (m->status >> 45) & 0x3;
	u8 xec = XEC(m->status, 0x1f);
	u16 ec = EC(m->status);
	u64 sys_addr;
	काष्ठा err_info err;

	mci = edac_mc_find(node_id);
	अगर (!mci)
		वापस;

	pvt = mci->pvt_info;

	/* Bail out early अगर this was an 'observed' error */
	अगर (PP(ec) == NBSL_PP_OBS)
		वापस;

	/* Do only ECC errors */
	अगर (xec && xec != F10_NBSL_EXT_ERR_ECC)
		वापस;

	स_रखो(&err, 0, माप(err));

	sys_addr = get_error_address(pvt, m);

	अगर (ecc_type == 2)
		err.syndrome = extract_syndrome(m->status);

	pvt->ops->map_sysaddr_to_csrow(mci, sys_addr, &err);

	__log_ecc_error(mci, &err, ecc_type);
पूर्ण

/*
 * To find the UMC channel represented by this bank we need to match on its
 * instance_id. The instance_id of a bank is held in the lower 32 bits of its
 * IPID.
 *
 * Currently, we can derive the channel number by looking at the 6th nibble in
 * the instance_id. For example, instance_id=0xYXXXXX where Y is the channel
 * number.
 */
अटल पूर्णांक find_umc_channel(काष्ठा mce *m)
अणु
	वापस (m->ipid & GENMASK(31, 0)) >> 20;
पूर्ण

अटल व्योम decode_umc_error(पूर्णांक node_id, काष्ठा mce *m)
अणु
	u8 ecc_type = (m->status >> 45) & 0x3;
	काष्ठा mem_ctl_info *mci;
	काष्ठा amd64_pvt *pvt;
	काष्ठा err_info err;
	u64 sys_addr;

	mci = edac_mc_find(node_id);
	अगर (!mci)
		वापस;

	pvt = mci->pvt_info;

	स_रखो(&err, 0, माप(err));

	अगर (m->status & MCI_STATUS_DEFERRED)
		ecc_type = 3;

	err.channel = find_umc_channel(m);

	अगर (!(m->status & MCI_STATUS_SYNDV)) अणु
		err.err_code = ERR_SYND;
		जाओ log_error;
	पूर्ण

	अगर (ecc_type == 2) अणु
		u8 length = (m->synd >> 18) & 0x3f;

		अगर (length)
			err.syndrome = (m->synd >> 32) & GENMASK(length - 1, 0);
		अन्यथा
			err.err_code = ERR_CHANNEL;
	पूर्ण

	err.csrow = m->synd & 0x7;

	अगर (umc_normaddr_to_sysaddr(m->addr, pvt->mc_node_id, err.channel, &sys_addr)) अणु
		err.err_code = ERR_NORM_ADDR;
		जाओ log_error;
	पूर्ण

	error_address_to_page_and_offset(sys_addr, &err);

log_error:
	__log_ecc_error(mci, &err, ecc_type);
पूर्ण

/*
 * Use pvt->F3 which contains the F3 CPU PCI device to get the related
 * F1 (AddrMap) and F2 (Dct) devices. Return negative value on error.
 * Reserve F0 and F6 on प्रणालीs with a UMC.
 */
अटल पूर्णांक
reserve_mc_sibling_devs(काष्ठा amd64_pvt *pvt, u16 pci_id1, u16 pci_id2)
अणु
	अगर (pvt->umc) अणु
		pvt->F0 = pci_get_related_function(pvt->F3->venकरोr, pci_id1, pvt->F3);
		अगर (!pvt->F0) अणु
			edac_dbg(1, "F0 not found, device 0x%x\n", pci_id1);
			वापस -ENODEV;
		पूर्ण

		pvt->F6 = pci_get_related_function(pvt->F3->venकरोr, pci_id2, pvt->F3);
		अगर (!pvt->F6) अणु
			pci_dev_put(pvt->F0);
			pvt->F0 = शून्य;

			edac_dbg(1, "F6 not found: device 0x%x\n", pci_id2);
			वापस -ENODEV;
		पूर्ण

		अगर (!pci_ctl_dev)
			pci_ctl_dev = &pvt->F0->dev;

		edac_dbg(1, "F0: %s\n", pci_name(pvt->F0));
		edac_dbg(1, "F3: %s\n", pci_name(pvt->F3));
		edac_dbg(1, "F6: %s\n", pci_name(pvt->F6));

		वापस 0;
	पूर्ण

	/* Reserve the ADDRESS MAP Device */
	pvt->F1 = pci_get_related_function(pvt->F3->venकरोr, pci_id1, pvt->F3);
	अगर (!pvt->F1) अणु
		edac_dbg(1, "F1 not found: device 0x%x\n", pci_id1);
		वापस -ENODEV;
	पूर्ण

	/* Reserve the DCT Device */
	pvt->F2 = pci_get_related_function(pvt->F3->venकरोr, pci_id2, pvt->F3);
	अगर (!pvt->F2) अणु
		pci_dev_put(pvt->F1);
		pvt->F1 = शून्य;

		edac_dbg(1, "F2 not found: device 0x%x\n", pci_id2);
		वापस -ENODEV;
	पूर्ण

	अगर (!pci_ctl_dev)
		pci_ctl_dev = &pvt->F2->dev;

	edac_dbg(1, "F1: %s\n", pci_name(pvt->F1));
	edac_dbg(1, "F2: %s\n", pci_name(pvt->F2));
	edac_dbg(1, "F3: %s\n", pci_name(pvt->F3));

	वापस 0;
पूर्ण

अटल व्योम मुक्त_mc_sibling_devs(काष्ठा amd64_pvt *pvt)
अणु
	अगर (pvt->umc) अणु
		pci_dev_put(pvt->F0);
		pci_dev_put(pvt->F6);
	पूर्ण अन्यथा अणु
		pci_dev_put(pvt->F1);
		pci_dev_put(pvt->F2);
	पूर्ण
पूर्ण

अटल व्योम determine_ecc_sym_sz(काष्ठा amd64_pvt *pvt)
अणु
	pvt->ecc_sym_sz = 4;

	अगर (pvt->umc) अणु
		u8 i;

		क्रम_each_umc(i) अणु
			/* Check enabled channels only: */
			अगर (pvt->umc[i].sdp_ctrl & UMC_SDP_INIT) अणु
				अगर (pvt->umc[i].ecc_ctrl & BIT(9)) अणु
					pvt->ecc_sym_sz = 16;
					वापस;
				पूर्ण अन्यथा अगर (pvt->umc[i].ecc_ctrl & BIT(7)) अणु
					pvt->ecc_sym_sz = 8;
					वापस;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (pvt->fam >= 0x10) अणु
		u32 पंचांगp;

		amd64_पढ़ो_pci_cfg(pvt->F3, EXT_NB_MCA_CFG, &पंचांगp);
		/* F16h has only DCT0, so no need to पढ़ो dbam1. */
		अगर (pvt->fam != 0x16)
			amd64_पढ़ो_dct_pci_cfg(pvt, 1, DBAM0, &pvt->dbam1);

		/* F10h, revD and later can करो x8 ECC too. */
		अगर ((pvt->fam > 0x10 || pvt->model > 7) && पंचांगp & BIT(25))
			pvt->ecc_sym_sz = 8;
	पूर्ण
पूर्ण

/*
 * Retrieve the hardware रेजिस्टरs of the memory controller.
 */
अटल व्योम __पढ़ो_mc_regs_df(काष्ठा amd64_pvt *pvt)
अणु
	u8 nid = pvt->mc_node_id;
	काष्ठा amd64_umc *umc;
	u32 i, umc_base;

	/* Read रेजिस्टरs from each UMC */
	क्रम_each_umc(i) अणु

		umc_base = get_umc_base(i);
		umc = &pvt->umc[i];

		amd_smn_पढ़ो(nid, umc_base + UMCCH_DIMM_CFG, &umc->dimm_cfg);
		amd_smn_पढ़ो(nid, umc_base + UMCCH_UMC_CFG, &umc->umc_cfg);
		amd_smn_पढ़ो(nid, umc_base + UMCCH_SDP_CTRL, &umc->sdp_ctrl);
		amd_smn_पढ़ो(nid, umc_base + UMCCH_ECC_CTRL, &umc->ecc_ctrl);
		amd_smn_पढ़ो(nid, umc_base + UMCCH_UMC_CAP_HI, &umc->umc_cap_hi);
	पूर्ण
पूर्ण

/*
 * Retrieve the hardware रेजिस्टरs of the memory controller (this includes the
 * 'Address Map' and 'Misc' device regs)
 */
अटल व्योम पढ़ो_mc_regs(काष्ठा amd64_pvt *pvt)
अणु
	अचिन्हित पूर्णांक range;
	u64 msr_val;

	/*
	 * Retrieve TOP_MEM and TOP_MEM2; no masking off of reserved bits since
	 * those are Read-As-Zero.
	 */
	rdmsrl(MSR_K8_TOP_MEM1, pvt->top_mem);
	edac_dbg(0, "  TOP_MEM:  0x%016llx\n", pvt->top_mem);

	/* Check first whether TOP_MEM2 is enabled: */
	rdmsrl(MSR_AMD64_SYSCFG, msr_val);
	अगर (msr_val & BIT(21)) अणु
		rdmsrl(MSR_K8_TOP_MEM2, pvt->top_mem2);
		edac_dbg(0, "  TOP_MEM2: 0x%016llx\n", pvt->top_mem2);
	पूर्ण अन्यथा अणु
		edac_dbg(0, "  TOP_MEM2 disabled\n");
	पूर्ण

	अगर (pvt->umc) अणु
		__पढ़ो_mc_regs_df(pvt);
		amd64_पढ़ो_pci_cfg(pvt->F0, DF_DHAR, &pvt->dhar);

		जाओ skip;
	पूर्ण

	amd64_पढ़ो_pci_cfg(pvt->F3, NBCAP, &pvt->nbcap);

	पढ़ो_dram_ctl_रेजिस्टर(pvt);

	क्रम (range = 0; range < DRAM_RANGES; range++) अणु
		u8 rw;

		/* पढ़ो settings क्रम this DRAM range */
		पढ़ो_dram_base_limit_regs(pvt, range);

		rw = dram_rw(pvt, range);
		अगर (!rw)
			जारी;

		edac_dbg(1, "  DRAM range[%d], base: 0x%016llx; limit: 0x%016llx\n",
			 range,
			 get_dram_base(pvt, range),
			 get_dram_limit(pvt, range));

		edac_dbg(1, "   IntlvEn=%s; Range access: %s%s IntlvSel=%d DstNode=%d\n",
			 dram_पूर्णांकlv_en(pvt, range) ? "Enabled" : "Disabled",
			 (rw & 0x1) ? "R" : "-",
			 (rw & 0x2) ? "W" : "-",
			 dram_पूर्णांकlv_sel(pvt, range),
			 dram_dst_node(pvt, range));
	पूर्ण

	amd64_पढ़ो_pci_cfg(pvt->F1, DHAR, &pvt->dhar);
	amd64_पढ़ो_dct_pci_cfg(pvt, 0, DBAM0, &pvt->dbam0);

	amd64_पढ़ो_pci_cfg(pvt->F3, F10_ONLINE_SPARE, &pvt->online_spare);

	amd64_पढ़ो_dct_pci_cfg(pvt, 0, DCLR0, &pvt->dclr0);
	amd64_पढ़ो_dct_pci_cfg(pvt, 0, DCHR0, &pvt->dchr0);

	अगर (!dct_ganging_enabled(pvt)) अणु
		amd64_पढ़ो_dct_pci_cfg(pvt, 1, DCLR0, &pvt->dclr1);
		amd64_पढ़ो_dct_pci_cfg(pvt, 1, DCHR0, &pvt->dchr1);
	पूर्ण

skip:
	पढ़ो_dct_base_mask(pvt);

	determine_memory_type(pvt);
	edac_dbg(1, "  DIMM type: %s\n", edac_mem_types[pvt->dram_type]);

	determine_ecc_sym_sz(pvt);
पूर्ण

/*
 * NOTE: CPU Revision Dependent code
 *
 * Input:
 *	@csrow_nr ChipSelect Row Number (0..NUM_CHIPSELECTS-1)
 *	k8 निजी poपूर्णांकer to -->
 *			DRAM Bank Address mapping रेजिस्टर
 *			node_id
 *			DCL रेजिस्टर where dual_channel_active is
 *
 * The DBAM रेजिस्टर consists of 4 sets of 4 bits each definitions:
 *
 * Bits:	CSROWs
 * 0-3		CSROWs 0 and 1
 * 4-7		CSROWs 2 and 3
 * 8-11		CSROWs 4 and 5
 * 12-15	CSROWs 6 and 7
 *
 * Values range from: 0 to 15
 * The meaning of the values depends on CPU revision and dual-channel state,
 * see relevant BKDG more info.
 *
 * The memory controller provides क्रम total of only 8 CSROWs in its current
 * architecture. Each "pair" of CSROWs normally represents just one DIMM in
 * single channel or two (2) DIMMs in dual channel mode.
 *
 * The following code logic collapses the various tables क्रम CSROW based on CPU
 * revision.
 *
 * Returns:
 *	The number of PAGE_SIZE pages on the specअगरied CSROW number it
 *	encompasses
 *
 */
अटल u32 get_csrow_nr_pages(काष्ठा amd64_pvt *pvt, u8 dct, पूर्णांक csrow_nr_orig)
अणु
	u32 dbam = dct ? pvt->dbam1 : pvt->dbam0;
	पूर्णांक csrow_nr = csrow_nr_orig;
	u32 cs_mode, nr_pages;

	अगर (!pvt->umc) अणु
		csrow_nr >>= 1;
		cs_mode = DBAM_DIMM(csrow_nr, dbam);
	पूर्ण अन्यथा अणु
		cs_mode = f17_get_cs_mode(csrow_nr >> 1, dct, pvt);
	पूर्ण

	nr_pages   = pvt->ops->dbam_to_cs(pvt, dct, cs_mode, csrow_nr);
	nr_pages <<= 20 - PAGE_SHIFT;

	edac_dbg(0, "csrow: %d, channel: %d, DBAM idx: %d\n",
		    csrow_nr_orig, dct,  cs_mode);
	edac_dbg(0, "nr_pages/channel: %u\n", nr_pages);

	वापस nr_pages;
पूर्ण

अटल पूर्णांक init_csrows_df(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	क्रमागत edac_type edac_mode = EDAC_NONE;
	क्रमागत dev_type dev_type = DEV_UNKNOWN;
	काष्ठा dimm_info *dimm;
	पूर्णांक empty = 1;
	u8 umc, cs;

	अगर (mci->edac_ctl_cap & EDAC_FLAG_S16ECD16ED) अणु
		edac_mode = EDAC_S16ECD16ED;
		dev_type = DEV_X16;
	पूर्ण अन्यथा अगर (mci->edac_ctl_cap & EDAC_FLAG_S8ECD8ED) अणु
		edac_mode = EDAC_S8ECD8ED;
		dev_type = DEV_X8;
	पूर्ण अन्यथा अगर (mci->edac_ctl_cap & EDAC_FLAG_S4ECD4ED) अणु
		edac_mode = EDAC_S4ECD4ED;
		dev_type = DEV_X4;
	पूर्ण अन्यथा अगर (mci->edac_ctl_cap & EDAC_FLAG_SECDED) अणु
		edac_mode = EDAC_SECDED;
	पूर्ण

	क्रम_each_umc(umc) अणु
		क्रम_each_chip_select(cs, umc, pvt) अणु
			अगर (!csrow_enabled(cs, umc, pvt))
				जारी;

			empty = 0;
			dimm = mci->csrows[cs]->channels[umc]->dimm;

			edac_dbg(1, "MC node: %d, csrow: %d\n",
					pvt->mc_node_id, cs);

			dimm->nr_pages = get_csrow_nr_pages(pvt, umc, cs);
			dimm->mtype = pvt->dram_type;
			dimm->edac_mode = edac_mode;
			dimm->dtype = dev_type;
			dimm->grain = 64;
		पूर्ण
	पूर्ण

	वापस empty;
पूर्ण

/*
 * Initialize the array of csrow attribute instances, based on the values
 * from pci config hardware रेजिस्टरs.
 */
अटल पूर्णांक init_csrows(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा amd64_pvt *pvt = mci->pvt_info;
	क्रमागत edac_type edac_mode = EDAC_NONE;
	काष्ठा csrow_info *csrow;
	काष्ठा dimm_info *dimm;
	पूर्णांक i, j, empty = 1;
	पूर्णांक nr_pages = 0;
	u32 val;

	अगर (pvt->umc)
		वापस init_csrows_df(mci);

	amd64_पढ़ो_pci_cfg(pvt->F3, NBCFG, &val);

	pvt->nbcfg = val;

	edac_dbg(0, "node %d, NBCFG=0x%08x[ChipKillEccCap: %d|DramEccEn: %d]\n",
		 pvt->mc_node_id, val,
		 !!(val & NBCFG_CHIPKILL), !!(val & NBCFG_ECC_ENABLE));

	/*
	 * We iterate over DCT0 here but we look at DCT1 in parallel, अगर needed.
	 */
	क्रम_each_chip_select(i, 0, pvt) अणु
		bool row_dct0 = !!csrow_enabled(i, 0, pvt);
		bool row_dct1 = false;

		अगर (pvt->fam != 0xf)
			row_dct1 = !!csrow_enabled(i, 1, pvt);

		अगर (!row_dct0 && !row_dct1)
			जारी;

		csrow = mci->csrows[i];
		empty = 0;

		edac_dbg(1, "MC node: %d, csrow: %d\n",
			    pvt->mc_node_id, i);

		अगर (row_dct0) अणु
			nr_pages = get_csrow_nr_pages(pvt, 0, i);
			csrow->channels[0]->dimm->nr_pages = nr_pages;
		पूर्ण

		/* K8 has only one DCT */
		अगर (pvt->fam != 0xf && row_dct1) अणु
			पूर्णांक row_dct1_pages = get_csrow_nr_pages(pvt, 1, i);

			csrow->channels[1]->dimm->nr_pages = row_dct1_pages;
			nr_pages += row_dct1_pages;
		पूर्ण

		edac_dbg(1, "Total csrow%d pages: %u\n", i, nr_pages);

		/* Determine DIMM ECC mode: */
		अगर (pvt->nbcfg & NBCFG_ECC_ENABLE) अणु
			edac_mode = (pvt->nbcfg & NBCFG_CHIPKILL)
					? EDAC_S4ECD4ED
					: EDAC_SECDED;
		पूर्ण

		क्रम (j = 0; j < pvt->channel_count; j++) अणु
			dimm = csrow->channels[j]->dimm;
			dimm->mtype = pvt->dram_type;
			dimm->edac_mode = edac_mode;
			dimm->grain = 64;
		पूर्ण
	पूर्ण

	वापस empty;
पूर्ण

/* get all cores on this DCT */
अटल व्योम get_cpus_on_this_dct_cpumask(काष्ठा cpumask *mask, u16 nid)
अणु
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu)
		अगर (topology_die_id(cpu) == nid)
			cpumask_set_cpu(cpu, mask);
पूर्ण

/* check MCG_CTL on all the cpus on this node */
अटल bool nb_mce_bank_enabled_on_node(u16 nid)
अणु
	cpumask_var_t mask;
	पूर्णांक cpu, nbe;
	bool ret = false;

	अगर (!zalloc_cpumask_var(&mask, GFP_KERNEL)) अणु
		amd64_warn("%s: Error allocating mask\n", __func__);
		वापस false;
	पूर्ण

	get_cpus_on_this_dct_cpumask(mask, nid);

	rdmsr_on_cpus(mask, MSR_IA32_MCG_CTL, msrs);

	क्रम_each_cpu(cpu, mask) अणु
		काष्ठा msr *reg = per_cpu_ptr(msrs, cpu);
		nbe = reg->l & MSR_MCGCTL_NBE;

		edac_dbg(0, "core: %u, MCG_CTL: 0x%llx, NB MSR is %s\n",
			 cpu, reg->q,
			 (nbe ? "enabled" : "disabled"));

		अगर (!nbe)
			जाओ out;
	पूर्ण
	ret = true;

out:
	मुक्त_cpumask_var(mask);
	वापस ret;
पूर्ण

अटल पूर्णांक toggle_ecc_err_reporting(काष्ठा ecc_settings *s, u16 nid, bool on)
अणु
	cpumask_var_t cmask;
	पूर्णांक cpu;

	अगर (!zalloc_cpumask_var(&cmask, GFP_KERNEL)) अणु
		amd64_warn("%s: error allocating mask\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	get_cpus_on_this_dct_cpumask(cmask, nid);

	rdmsr_on_cpus(cmask, MSR_IA32_MCG_CTL, msrs);

	क्रम_each_cpu(cpu, cmask) अणु

		काष्ठा msr *reg = per_cpu_ptr(msrs, cpu);

		अगर (on) अणु
			अगर (reg->l & MSR_MCGCTL_NBE)
				s->flags.nb_mce_enable = 1;

			reg->l |= MSR_MCGCTL_NBE;
		पूर्ण अन्यथा अणु
			/*
			 * Turn off NB MCE reporting only when it was off beक्रमe
			 */
			अगर (!s->flags.nb_mce_enable)
				reg->l &= ~MSR_MCGCTL_NBE;
		पूर्ण
	पूर्ण
	wrmsr_on_cpus(cmask, MSR_IA32_MCG_CTL, msrs);

	मुक्त_cpumask_var(cmask);

	वापस 0;
पूर्ण

अटल bool enable_ecc_error_reporting(काष्ठा ecc_settings *s, u16 nid,
				       काष्ठा pci_dev *F3)
अणु
	bool ret = true;
	u32 value, mask = 0x3;		/* UECC/CECC enable */

	अगर (toggle_ecc_err_reporting(s, nid, ON)) अणु
		amd64_warn("Error enabling ECC reporting over MCGCTL!\n");
		वापस false;
	पूर्ण

	amd64_पढ़ो_pci_cfg(F3, NBCTL, &value);

	s->old_nbctl   = value & mask;
	s->nbctl_valid = true;

	value |= mask;
	amd64_ग_लिखो_pci_cfg(F3, NBCTL, value);

	amd64_पढ़ो_pci_cfg(F3, NBCFG, &value);

	edac_dbg(0, "1: node %d, NBCFG=0x%08x[DramEccEn: %d]\n",
		 nid, value, !!(value & NBCFG_ECC_ENABLE));

	अगर (!(value & NBCFG_ECC_ENABLE)) अणु
		amd64_warn("DRAM ECC disabled on this node, enabling...\n");

		s->flags.nb_ecc_prev = 0;

		/* Attempt to turn on DRAM ECC Enable */
		value |= NBCFG_ECC_ENABLE;
		amd64_ग_लिखो_pci_cfg(F3, NBCFG, value);

		amd64_पढ़ो_pci_cfg(F3, NBCFG, &value);

		अगर (!(value & NBCFG_ECC_ENABLE)) अणु
			amd64_warn("Hardware rejected DRAM ECC enable,"
				   "check memory DIMM configuration.\n");
			ret = false;
		पूर्ण अन्यथा अणु
			amd64_info("Hardware accepted DRAM ECC Enable\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		s->flags.nb_ecc_prev = 1;
	पूर्ण

	edac_dbg(0, "2: node %d, NBCFG=0x%08x[DramEccEn: %d]\n",
		 nid, value, !!(value & NBCFG_ECC_ENABLE));

	वापस ret;
पूर्ण

अटल व्योम restore_ecc_error_reporting(काष्ठा ecc_settings *s, u16 nid,
					काष्ठा pci_dev *F3)
अणु
	u32 value, mask = 0x3;		/* UECC/CECC enable */

	अगर (!s->nbctl_valid)
		वापस;

	amd64_पढ़ो_pci_cfg(F3, NBCTL, &value);
	value &= ~mask;
	value |= s->old_nbctl;

	amd64_ग_लिखो_pci_cfg(F3, NBCTL, value);

	/* restore previous BIOS DRAM ECC "off" setting we क्रमce-enabled */
	अगर (!s->flags.nb_ecc_prev) अणु
		amd64_पढ़ो_pci_cfg(F3, NBCFG, &value);
		value &= ~NBCFG_ECC_ENABLE;
		amd64_ग_लिखो_pci_cfg(F3, NBCFG, value);
	पूर्ण

	/* restore the NB Enable MCGCTL bit */
	अगर (toggle_ecc_err_reporting(s, nid, OFF))
		amd64_warn("Error restoring NB MCGCTL settings!\n");
पूर्ण

अटल bool ecc_enabled(काष्ठा amd64_pvt *pvt)
अणु
	u16 nid = pvt->mc_node_id;
	bool nb_mce_en = false;
	u8 ecc_en = 0, i;
	u32 value;

	अगर (boot_cpu_data.x86 >= 0x17) अणु
		u8 umc_en_mask = 0, ecc_en_mask = 0;
		काष्ठा amd64_umc *umc;

		क्रम_each_umc(i) अणु
			umc = &pvt->umc[i];

			/* Only check enabled UMCs. */
			अगर (!(umc->sdp_ctrl & UMC_SDP_INIT))
				जारी;

			umc_en_mask |= BIT(i);

			अगर (umc->umc_cap_hi & UMC_ECC_ENABLED)
				ecc_en_mask |= BIT(i);
		पूर्ण

		/* Check whether at least one UMC is enabled: */
		अगर (umc_en_mask)
			ecc_en = umc_en_mask == ecc_en_mask;
		अन्यथा
			edac_dbg(0, "Node %d: No enabled UMCs.\n", nid);

		/* Assume UMC MCA banks are enabled. */
		nb_mce_en = true;
	पूर्ण अन्यथा अणु
		amd64_पढ़ो_pci_cfg(pvt->F3, NBCFG, &value);

		ecc_en = !!(value & NBCFG_ECC_ENABLE);

		nb_mce_en = nb_mce_bank_enabled_on_node(nid);
		अगर (!nb_mce_en)
			edac_dbg(0, "NB MCE bank disabled, set MSR 0x%08x[4] on node %d to enable.\n",
				     MSR_IA32_MCG_CTL, nid);
	पूर्ण

	edac_dbg(3, "Node %d: DRAM ECC %s.\n", nid, (ecc_en ? "enabled" : "disabled"));

	अगर (!ecc_en || !nb_mce_en)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल अंतरभूत व्योम
f17h_determine_edac_ctl_cap(काष्ठा mem_ctl_info *mci, काष्ठा amd64_pvt *pvt)
अणु
	u8 i, ecc_en = 1, cpk_en = 1, dev_x4 = 1, dev_x16 = 1;

	क्रम_each_umc(i) अणु
		अगर (pvt->umc[i].sdp_ctrl & UMC_SDP_INIT) अणु
			ecc_en &= !!(pvt->umc[i].umc_cap_hi & UMC_ECC_ENABLED);
			cpk_en &= !!(pvt->umc[i].umc_cap_hi & UMC_ECC_CHIPKILL_CAP);

			dev_x4  &= !!(pvt->umc[i].dimm_cfg & BIT(6));
			dev_x16 &= !!(pvt->umc[i].dimm_cfg & BIT(7));
		पूर्ण
	पूर्ण

	/* Set chipसमाप्त only अगर ECC is enabled: */
	अगर (ecc_en) अणु
		mci->edac_ctl_cap |= EDAC_FLAG_SECDED;

		अगर (!cpk_en)
			वापस;

		अगर (dev_x4)
			mci->edac_ctl_cap |= EDAC_FLAG_S4ECD4ED;
		अन्यथा अगर (dev_x16)
			mci->edac_ctl_cap |= EDAC_FLAG_S16ECD16ED;
		अन्यथा
			mci->edac_ctl_cap |= EDAC_FLAG_S8ECD8ED;
	पूर्ण
पूर्ण

अटल व्योम setup_mci_misc_attrs(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा amd64_pvt *pvt = mci->pvt_info;

	mci->mtype_cap		= MEM_FLAG_DDR2 | MEM_FLAG_RDDR2;
	mci->edac_ctl_cap	= EDAC_FLAG_NONE;

	अगर (pvt->umc) अणु
		f17h_determine_edac_ctl_cap(mci, pvt);
	पूर्ण अन्यथा अणु
		अगर (pvt->nbcap & NBCAP_SECDED)
			mci->edac_ctl_cap |= EDAC_FLAG_SECDED;

		अगर (pvt->nbcap & NBCAP_CHIPKILL)
			mci->edac_ctl_cap |= EDAC_FLAG_S4ECD4ED;
	पूर्ण

	mci->edac_cap		= determine_edac_cap(pvt);
	mci->mod_name		= EDAC_MOD_STR;
	mci->ctl_name		= fam_type->ctl_name;
	mci->dev_name		= pci_name(pvt->F3);
	mci->ctl_page_to_phys	= शून्य;

	/* memory scrubber पूर्णांकerface */
	mci->set_sdram_scrub_rate = set_scrub_rate;
	mci->get_sdram_scrub_rate = get_scrub_rate;
पूर्ण

/*
 * वापसs a poपूर्णांकer to the family descriptor on success, शून्य otherwise.
 */
अटल काष्ठा amd64_family_type *per_family_init(काष्ठा amd64_pvt *pvt)
अणु
	pvt->ext_model  = boot_cpu_data.x86_model >> 4;
	pvt->stepping	= boot_cpu_data.x86_stepping;
	pvt->model	= boot_cpu_data.x86_model;
	pvt->fam	= boot_cpu_data.x86;

	चयन (pvt->fam) अणु
	हाल 0xf:
		fam_type	= &family_types[K8_CPUS];
		pvt->ops	= &family_types[K8_CPUS].ops;
		अवरोध;

	हाल 0x10:
		fam_type	= &family_types[F10_CPUS];
		pvt->ops	= &family_types[F10_CPUS].ops;
		अवरोध;

	हाल 0x15:
		अगर (pvt->model == 0x30) अणु
			fam_type = &family_types[F15_M30H_CPUS];
			pvt->ops = &family_types[F15_M30H_CPUS].ops;
			अवरोध;
		पूर्ण अन्यथा अगर (pvt->model == 0x60) अणु
			fam_type = &family_types[F15_M60H_CPUS];
			pvt->ops = &family_types[F15_M60H_CPUS].ops;
			अवरोध;
		/* Richland is only client */
		पूर्ण अन्यथा अगर (pvt->model == 0x13) अणु
			वापस शून्य;
		पूर्ण अन्यथा अणु
			fam_type	= &family_types[F15_CPUS];
			pvt->ops	= &family_types[F15_CPUS].ops;
		पूर्ण
		अवरोध;

	हाल 0x16:
		अगर (pvt->model == 0x30) अणु
			fam_type = &family_types[F16_M30H_CPUS];
			pvt->ops = &family_types[F16_M30H_CPUS].ops;
			अवरोध;
		पूर्ण
		fam_type	= &family_types[F16_CPUS];
		pvt->ops	= &family_types[F16_CPUS].ops;
		अवरोध;

	हाल 0x17:
		अगर (pvt->model >= 0x10 && pvt->model <= 0x2f) अणु
			fam_type = &family_types[F17_M10H_CPUS];
			pvt->ops = &family_types[F17_M10H_CPUS].ops;
			अवरोध;
		पूर्ण अन्यथा अगर (pvt->model >= 0x30 && pvt->model <= 0x3f) अणु
			fam_type = &family_types[F17_M30H_CPUS];
			pvt->ops = &family_types[F17_M30H_CPUS].ops;
			अवरोध;
		पूर्ण अन्यथा अगर (pvt->model >= 0x60 && pvt->model <= 0x6f) अणु
			fam_type = &family_types[F17_M60H_CPUS];
			pvt->ops = &family_types[F17_M60H_CPUS].ops;
			अवरोध;
		पूर्ण अन्यथा अगर (pvt->model >= 0x70 && pvt->model <= 0x7f) अणु
			fam_type = &family_types[F17_M70H_CPUS];
			pvt->ops = &family_types[F17_M70H_CPUS].ops;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल 0x18:
		fam_type	= &family_types[F17_CPUS];
		pvt->ops	= &family_types[F17_CPUS].ops;

		अगर (pvt->fam == 0x18)
			family_types[F17_CPUS].ctl_name = "F18h";
		अवरोध;

	हाल 0x19:
		अगर (pvt->model >= 0x20 && pvt->model <= 0x2f) अणु
			fam_type = &family_types[F17_M70H_CPUS];
			pvt->ops = &family_types[F17_M70H_CPUS].ops;
			fam_type->ctl_name = "F19h_M20h";
			अवरोध;
		पूर्ण
		fam_type	= &family_types[F19_CPUS];
		pvt->ops	= &family_types[F19_CPUS].ops;
		family_types[F19_CPUS].ctl_name = "F19h";
		अवरोध;

	शेष:
		amd64_err("Unsupported family!\n");
		वापस शून्य;
	पूर्ण

	वापस fam_type;
पूर्ण

अटल स्थिर काष्ठा attribute_group *amd64_edac_attr_groups[] = अणु
#अगर_घोषित CONFIG_EDAC_DEBUG
	&dbg_group,
	&inj_group,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल पूर्णांक hw_info_get(काष्ठा amd64_pvt *pvt)
अणु
	u16 pci_id1, pci_id2;
	पूर्णांक ret;

	अगर (pvt->fam >= 0x17) अणु
		pvt->umc = kसुस्मृति(fam_type->max_mcs, माप(काष्ठा amd64_umc), GFP_KERNEL);
		अगर (!pvt->umc)
			वापस -ENOMEM;

		pci_id1 = fam_type->f0_id;
		pci_id2 = fam_type->f6_id;
	पूर्ण अन्यथा अणु
		pci_id1 = fam_type->f1_id;
		pci_id2 = fam_type->f2_id;
	पूर्ण

	ret = reserve_mc_sibling_devs(pvt, pci_id1, pci_id2);
	अगर (ret)
		वापस ret;

	पढ़ो_mc_regs(pvt);

	वापस 0;
पूर्ण

अटल व्योम hw_info_put(काष्ठा amd64_pvt *pvt)
अणु
	अगर (pvt->F0 || pvt->F1)
		मुक्त_mc_sibling_devs(pvt);

	kमुक्त(pvt->umc);
पूर्ण

अटल पूर्णांक init_one_instance(काष्ठा amd64_pvt *pvt)
अणु
	काष्ठा mem_ctl_info *mci = शून्य;
	काष्ठा edac_mc_layer layers[2];
	पूर्णांक ret = -EINVAL;

	/*
	 * We need to determine how many memory channels there are. Then use
	 * that inक्रमmation क्रम calculating the size of the dynamic instance
	 * tables in the 'mci' काष्ठाure.
	 */
	pvt->channel_count = pvt->ops->early_channel_count(pvt);
	अगर (pvt->channel_count < 0)
		वापस ret;

	ret = -ENOMEM;
	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = pvt->csels[0].b_cnt;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;

	/*
	 * Always allocate two channels since we can have setups with DIMMs on
	 * only one channel. Also, this simplअगरies handling later क्रम the price
	 * of a couple of KBs tops.
	 */
	layers[1].size = fam_type->max_mcs;
	layers[1].is_virt_csrow = false;

	mci = edac_mc_alloc(pvt->mc_node_id, ARRAY_SIZE(layers), layers, 0);
	अगर (!mci)
		वापस ret;

	mci->pvt_info = pvt;
	mci->pdev = &pvt->F3->dev;

	setup_mci_misc_attrs(mci);

	अगर (init_csrows(mci))
		mci->edac_cap = EDAC_FLAG_NONE;

	ret = -ENODEV;
	अगर (edac_mc_add_mc_with_groups(mci, amd64_edac_attr_groups)) अणु
		edac_dbg(1, "failed edac_mc_add_mc()\n");
		edac_mc_मुक्त(mci);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool instance_has_memory(काष्ठा amd64_pvt *pvt)
अणु
	bool cs_enabled = false;
	पूर्णांक cs = 0, dct = 0;

	क्रम (dct = 0; dct < fam_type->max_mcs; dct++) अणु
		क्रम_each_chip_select(cs, dct, pvt)
			cs_enabled |= csrow_enabled(cs, dct, pvt);
	पूर्ण

	वापस cs_enabled;
पूर्ण

अटल पूर्णांक probe_one_instance(अचिन्हित पूर्णांक nid)
अणु
	काष्ठा pci_dev *F3 = node_to_amd_nb(nid)->misc;
	काष्ठा amd64_pvt *pvt = शून्य;
	काष्ठा ecc_settings *s;
	पूर्णांक ret;

	ret = -ENOMEM;
	s = kzalloc(माप(काष्ठा ecc_settings), GFP_KERNEL);
	अगर (!s)
		जाओ err_out;

	ecc_stngs[nid] = s;

	pvt = kzalloc(माप(काष्ठा amd64_pvt), GFP_KERNEL);
	अगर (!pvt)
		जाओ err_settings;

	pvt->mc_node_id	= nid;
	pvt->F3 = F3;

	ret = -ENODEV;
	fam_type = per_family_init(pvt);
	अगर (!fam_type)
		जाओ err_enable;

	ret = hw_info_get(pvt);
	अगर (ret < 0)
		जाओ err_enable;

	ret = 0;
	अगर (!instance_has_memory(pvt)) अणु
		amd64_info("Node %d: No DIMMs detected.\n", nid);
		जाओ err_enable;
	पूर्ण

	अगर (!ecc_enabled(pvt)) अणु
		ret = -ENODEV;

		अगर (!ecc_enable_override)
			जाओ err_enable;

		अगर (boot_cpu_data.x86 >= 0x17) अणु
			amd64_warn("Forcing ECC on is not recommended on newer systems. Please enable ECC in BIOS.");
			जाओ err_enable;
		पूर्ण अन्यथा
			amd64_warn("Forcing ECC on!\n");

		अगर (!enable_ecc_error_reporting(s, nid, F3))
			जाओ err_enable;
	पूर्ण

	ret = init_one_instance(pvt);
	अगर (ret < 0) अणु
		amd64_err("Error probing instance: %d\n", nid);

		अगर (boot_cpu_data.x86 < 0x17)
			restore_ecc_error_reporting(s, nid, F3);

		जाओ err_enable;
	पूर्ण

	amd64_info("%s %sdetected (node %d).\n", fam_type->ctl_name,
		     (pvt->fam == 0xf ?
				(pvt->ext_model >= K8_REV_F  ? "revF or later "
							     : "revE or earlier ")
				 : ""), pvt->mc_node_id);

	dump_misc_regs(pvt);

	वापस ret;

err_enable:
	hw_info_put(pvt);
	kमुक्त(pvt);

err_settings:
	kमुक्त(s);
	ecc_stngs[nid] = शून्य;

err_out:
	वापस ret;
पूर्ण

अटल व्योम हटाओ_one_instance(अचिन्हित पूर्णांक nid)
अणु
	काष्ठा pci_dev *F3 = node_to_amd_nb(nid)->misc;
	काष्ठा ecc_settings *s = ecc_stngs[nid];
	काष्ठा mem_ctl_info *mci;
	काष्ठा amd64_pvt *pvt;

	/* Remove from EDAC CORE tracking list */
	mci = edac_mc_del_mc(&F3->dev);
	अगर (!mci)
		वापस;

	pvt = mci->pvt_info;

	restore_ecc_error_reporting(s, nid, F3);

	kमुक्त(ecc_stngs[nid]);
	ecc_stngs[nid] = शून्य;

	/* Free the EDAC CORE resources */
	mci->pvt_info = शून्य;

	hw_info_put(pvt);
	kमुक्त(pvt);
	edac_mc_मुक्त(mci);
पूर्ण

अटल व्योम setup_pci_device(व्योम)
अणु
	अगर (pci_ctl)
		वापस;

	pci_ctl = edac_pci_create_generic_ctl(pci_ctl_dev, EDAC_MOD_STR);
	अगर (!pci_ctl) अणु
		pr_warn("%s(): Unable to create PCI control\n", __func__);
		pr_warn("%s(): PCI error report via EDAC not set\n", __func__);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id amd64_cpuids[] = अणु
	X86_MATCH_VENDOR_FAM(AMD,	0x0F, शून्य),
	X86_MATCH_VENDOR_FAM(AMD,	0x10, शून्य),
	X86_MATCH_VENDOR_FAM(AMD,	0x15, शून्य),
	X86_MATCH_VENDOR_FAM(AMD,	0x16, शून्य),
	X86_MATCH_VENDOR_FAM(AMD,	0x17, शून्य),
	X86_MATCH_VENDOR_FAM(HYGON,	0x18, शून्य),
	X86_MATCH_VENDOR_FAM(AMD,	0x19, शून्य),
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, amd64_cpuids);

अटल पूर्णांक __init amd64_edac_init(व्योम)
अणु
	स्थिर अक्षर *owner;
	पूर्णांक err = -ENODEV;
	पूर्णांक i;

	owner = edac_get_owner();
	अगर (owner && म_भेदन(owner, EDAC_MOD_STR, माप(EDAC_MOD_STR)))
		वापस -EBUSY;

	अगर (!x86_match_cpu(amd64_cpuids))
		वापस -ENODEV;

	अगर (amd_cache_northbridges() < 0)
		वापस -ENODEV;

	opstate_init();

	err = -ENOMEM;
	ecc_stngs = kसुस्मृति(amd_nb_num(), माप(ecc_stngs[0]), GFP_KERNEL);
	अगर (!ecc_stngs)
		जाओ err_मुक्त;

	msrs = msrs_alloc();
	अगर (!msrs)
		जाओ err_मुक्त;

	क्रम (i = 0; i < amd_nb_num(); i++) अणु
		err = probe_one_instance(i);
		अगर (err) अणु
			/* unwind properly */
			जबतक (--i >= 0)
				हटाओ_one_instance(i);

			जाओ err_pci;
		पूर्ण
	पूर्ण

	अगर (!edac_has_mcs()) अणु
		err = -ENODEV;
		जाओ err_pci;
	पूर्ण

	/* रेजिस्टर stuff with EDAC MCE */
	अगर (boot_cpu_data.x86 >= 0x17)
		amd_रेजिस्टर_ecc_decoder(decode_umc_error);
	अन्यथा
		amd_रेजिस्टर_ecc_decoder(decode_bus_error);

	setup_pci_device();

#अगर_घोषित CONFIG_X86_32
	amd64_err("%s on 32-bit is unsupported. USE AT YOUR OWN RISK!\n", EDAC_MOD_STR);
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO "AMD64 EDAC driver v%s\n", EDAC_AMD64_VERSION);

	वापस 0;

err_pci:
	pci_ctl_dev = शून्य;

	msrs_मुक्त(msrs);
	msrs = शून्य;

err_मुक्त:
	kमुक्त(ecc_stngs);
	ecc_stngs = शून्य;

	वापस err;
पूर्ण

अटल व्योम __निकास amd64_edac_निकास(व्योम)
अणु
	पूर्णांक i;

	अगर (pci_ctl)
		edac_pci_release_generic_ctl(pci_ctl);

	/* unरेजिस्टर from EDAC MCE */
	अगर (boot_cpu_data.x86 >= 0x17)
		amd_unरेजिस्टर_ecc_decoder(decode_umc_error);
	अन्यथा
		amd_unरेजिस्टर_ecc_decoder(decode_bus_error);

	क्रम (i = 0; i < amd_nb_num(); i++)
		हटाओ_one_instance(i);

	kमुक्त(ecc_stngs);
	ecc_stngs = शून्य;

	pci_ctl_dev = शून्य;

	msrs_मुक्त(msrs);
	msrs = शून्य;
पूर्ण

module_init(amd64_edac_init);
module_निकास(amd64_edac_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SoftwareBitMaker: Doug Thompson, "
		"Dave Peterson, Thayne Harbaugh");
MODULE_DESCRIPTION("MC support for AMD64 memory controllers - "
		EDAC_AMD64_VERSION);

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
