<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 */

#घोषणा pr_fmt(fmt)    "fsl-pamu: %s: " fmt, __func__

#समावेश "fsl_pamu.h"

#समावेश <linux/fsl/guts.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/genभाग.स>

#समावेश <यंत्र/mpc85xx.h>

/* define indexes क्रम each operation mapping scenario */
#घोषणा OMI_QMAN        0x00
#घोषणा OMI_FMAN        0x01
#घोषणा OMI_QMAN_PRIV   0x02
#घोषणा OMI_CAAM        0x03

#घोषणा make64(high, low) (((u64)(high) << 32) | (low))

काष्ठा pamu_isr_data अणु
	व्योम __iomem *pamu_reg_base;	/* Base address of PAMU regs */
	अचिन्हित पूर्णांक count;		/* The number of PAMUs */
पूर्ण;

अटल काष्ठा paace *ppaact;
अटल काष्ठा paace *spaact;

अटल bool probed;			/* Has PAMU been probed? */

/*
 * Table क्रम matching compatible strings, क्रम device tree
 * guts node, क्रम QorIQ SOCs.
 * "fsl,qoriq-device-config-2.0" corresponds to T4 & B4
 * SOCs. For the older SOCs "fsl,qoriq-device-config-1.0"
 * string would be used.
 */
अटल स्थिर काष्ठा of_device_id guts_device_ids[] = अणु
	अणु .compatible = "fsl,qoriq-device-config-1.0", पूर्ण,
	अणु .compatible = "fsl,qoriq-device-config-2.0", पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Table क्रम matching compatible strings, क्रम device tree
 * L3 cache controller node.
 * "fsl,t4240-l3-cache-controller" corresponds to T4,
 * "fsl,b4860-l3-cache-controller" corresponds to B4 &
 * "fsl,p4080-l3-cache-controller" corresponds to other,
 * SOCs.
 */
अटल स्थिर काष्ठा of_device_id l3_device_ids[] = अणु
	अणु .compatible = "fsl,t4240-l3-cache-controller", पूर्ण,
	अणु .compatible = "fsl,b4860-l3-cache-controller", पूर्ण,
	अणु .compatible = "fsl,p4080-l3-cache-controller", पूर्ण,
	अणुपूर्ण
पूर्ण;

/* maximum subwinकरोws permitted per liodn */
अटल u32 max_subwinकरोw_count;

/**
 * pamu_get_ppaace() - Return the primary PACCE
 * @liodn: liodn PAACT index क्रम desired PAACE
 *
 * Returns the ppace poपूर्णांकer upon success अन्यथा वापस
 * null.
 */
अटल काष्ठा paace *pamu_get_ppaace(पूर्णांक liodn)
अणु
	अगर (!ppaact || liodn >= PAACE_NUMBER_ENTRIES) अणु
		pr_debug("PPAACT doesn't exist\n");
		वापस शून्य;
	पूर्ण

	वापस &ppaact[liodn];
पूर्ण

/**
 * pamu_enable_liodn() - Set valid bit of PACCE
 * @liodn: liodn PAACT index क्रम desired PAACE
 *
 * Returns 0 upon success अन्यथा error code < 0 वापसed
 */
पूर्णांक pamu_enable_liodn(पूर्णांक liodn)
अणु
	काष्ठा paace *ppaace;

	ppaace = pamu_get_ppaace(liodn);
	अगर (!ppaace) अणु
		pr_debug("Invalid primary paace entry\n");
		वापस -ENOENT;
	पूर्ण

	अगर (!get_bf(ppaace->addr_bitfields, PPAACE_AF_WSE)) अणु
		pr_debug("liodn %d not configured\n", liodn);
		वापस -EINVAL;
	पूर्ण

	/* Ensure that all other stores to the ppaace complete first */
	mb();

	set_bf(ppaace->addr_bitfields, PAACE_AF_V, PAACE_V_VALID);
	mb();

	वापस 0;
पूर्ण

/**
 * pamu_disable_liodn() - Clears valid bit of PACCE
 * @liodn: liodn PAACT index क्रम desired PAACE
 *
 * Returns 0 upon success अन्यथा error code < 0 वापसed
 */
पूर्णांक pamu_disable_liodn(पूर्णांक liodn)
अणु
	काष्ठा paace *ppaace;

	ppaace = pamu_get_ppaace(liodn);
	अगर (!ppaace) अणु
		pr_debug("Invalid primary paace entry\n");
		वापस -ENOENT;
	पूर्ण

	set_bf(ppaace->addr_bitfields, PAACE_AF_V, PAACE_V_INVALID);
	mb();

	वापस 0;
पूर्ण

/* Derive the winकरोw size encoding क्रम a particular PAACE entry */
अटल अचिन्हित पूर्णांक map_addrspace_माप_प्रकारo_wse(phys_addr_t addrspace_size)
अणु
	/* Bug अगर not a घातer of 2 */
	BUG_ON(addrspace_size & (addrspace_size - 1));

	/* winकरोw size is 2^(WSE+1) bytes */
	वापस fls64(addrspace_size) - 2;
पूर्ण

/*
 * Set the PAACE type as primary and set the coherency required करोमुख्य
 * attribute
 */
अटल व्योम pamu_init_ppaace(काष्ठा paace *ppaace)
अणु
	set_bf(ppaace->addr_bitfields, PAACE_AF_PT, PAACE_PT_PRIMARY);

	set_bf(ppaace->करोमुख्य_attr.to_host.coherency_required, PAACE_DA_HOST_CR,
	       PAACE_M_COHERENCE_REQ);
पूर्ण

/*
 * Function used क्रम updating stash destination क्रम the coressponding
 * LIODN.
 */
पूर्णांक pamu_update_paace_stash(पूर्णांक liodn, u32 value)
अणु
	काष्ठा paace *paace;

	paace = pamu_get_ppaace(liodn);
	अगर (!paace) अणु
		pr_debug("Invalid liodn entry\n");
		वापस -ENOENT;
	पूर्ण
	set_bf(paace->impl_attr, PAACE_IA_CID, value);

	mb();

	वापस 0;
पूर्ण

/**
 * pamu_config_paace() - Sets up PPAACE entry क्रम specअगरied liodn
 *
 * @liodn: Logical IO device number
 * @omi: Operation mapping index -- अगर ~omi == 0 then omi not defined
 * @stashid: cache stash id क्रम associated cpu -- अगर ~stashid == 0 then
 *	     stashid not defined
 * @prot: winकरोw permissions
 *
 * Returns 0 upon success अन्यथा error code < 0 वापसed
 */
पूर्णांक pamu_config_ppaace(पूर्णांक liodn, u32 omi, u32 stashid, पूर्णांक prot)
अणु
	काष्ठा paace *ppaace;

	ppaace = pamu_get_ppaace(liodn);
	अगर (!ppaace)
		वापस -ENOENT;

	/* winकरोw size is 2^(WSE+1) bytes */
	set_bf(ppaace->addr_bitfields, PPAACE_AF_WSE,
	       map_addrspace_माप_प्रकारo_wse(1ULL << 36));

	pamu_init_ppaace(ppaace);

	ppaace->wbah = 0;
	set_bf(ppaace->addr_bitfields, PPAACE_AF_WBAL, 0);

	/* set up operation mapping अगर it's configured */
	अगर (omi < OME_NUMBER_ENTRIES) अणु
		set_bf(ppaace->impl_attr, PAACE_IA_OTM, PAACE_OTM_INDEXED);
		ppaace->op_encode.index_ot.omi = omi;
	पूर्ण अन्यथा अगर (~omi != 0) अणु
		pr_debug("bad operation mapping index: %d\n", omi);
		वापस -EINVAL;
	पूर्ण

	/* configure stash id */
	अगर (~stashid != 0)
		set_bf(ppaace->impl_attr, PAACE_IA_CID, stashid);

	set_bf(ppaace->impl_attr, PAACE_IA_ATM, PAACE_ATM_WINDOW_XLATE);
	ppaace->twbah = 0;
	set_bf(ppaace->win_bitfields, PAACE_WIN_TWBAL, 0);
	set_bf(ppaace->addr_bitfields, PAACE_AF_AP, prot);
	set_bf(ppaace->impl_attr, PAACE_IA_WCE, 0);
	set_bf(ppaace->addr_bitfields, PPAACE_AF_MW, 0);
	mb();

	वापस 0;
पूर्ण

/**
 * get_ome_index() - Returns the index in the operation mapping table
 *                   क्रम device.
 * @*omi_index: poपूर्णांकer क्रम storing the index value
 *
 */
व्योम get_ome_index(u32 *omi_index, काष्ठा device *dev)
अणु
	अगर (of_device_is_compatible(dev->of_node, "fsl,qman-portal"))
		*omi_index = OMI_QMAN;
	अगर (of_device_is_compatible(dev->of_node, "fsl,qman"))
		*omi_index = OMI_QMAN_PRIV;
पूर्ण

/**
 * get_stash_id - Returns stash destination id corresponding to a
 *                cache type and vcpu.
 * @stash_dest_hपूर्णांक: L1, L2 or L3
 * @vcpu: vpcu target क्रम a particular cache type.
 *
 * Returs stash on success or ~(u32)0 on failure.
 *
 */
u32 get_stash_id(u32 stash_dest_hपूर्णांक, u32 vcpu)
अणु
	स्थिर u32 *prop;
	काष्ठा device_node *node;
	u32 cache_level;
	पूर्णांक len, found = 0;
	पूर्णांक i;

	/* Fastpath, निकास early अगर L3/CPC cache is target क्रम stashing */
	अगर (stash_dest_hपूर्णांक == PAMU_ATTR_CACHE_L3) अणु
		node = of_find_matching_node(शून्य, l3_device_ids);
		अगर (node) अणु
			prop = of_get_property(node, "cache-stash-id", शून्य);
			अगर (!prop) अणु
				pr_debug("missing cache-stash-id at %pOF\n",
					 node);
				of_node_put(node);
				वापस ~(u32)0;
			पूर्ण
			of_node_put(node);
			वापस be32_to_cpup(prop);
		पूर्ण
		वापस ~(u32)0;
	पूर्ण

	क्रम_each_of_cpu_node(node) अणु
		prop = of_get_property(node, "reg", &len);
		क्रम (i = 0; i < len / माप(u32); i++) अणु
			अगर (be32_to_cpup(&prop[i]) == vcpu) अणु
				found = 1;
				जाओ found_cpu_node;
			पूर्ण
		पूर्ण
	पूर्ण
found_cpu_node:

	/* find the hwnode that represents the cache */
	क्रम (cache_level = PAMU_ATTR_CACHE_L1; (cache_level < PAMU_ATTR_CACHE_L3) && found; cache_level++) अणु
		अगर (stash_dest_hपूर्णांक == cache_level) अणु
			prop = of_get_property(node, "cache-stash-id", शून्य);
			अगर (!prop) अणु
				pr_debug("missing cache-stash-id at %pOF\n",
					 node);
				of_node_put(node);
				वापस ~(u32)0;
			पूर्ण
			of_node_put(node);
			वापस be32_to_cpup(prop);
		पूर्ण

		prop = of_get_property(node, "next-level-cache", शून्य);
		अगर (!prop) अणु
			pr_debug("can't find next-level-cache at %pOF\n", node);
			of_node_put(node);
			वापस ~(u32)0;  /* can't traverse any further */
		पूर्ण
		of_node_put(node);

		/* advance to next node in cache hierarchy */
		node = of_find_node_by_phandle(*prop);
		अगर (!node) अणु
			pr_debug("Invalid node for cache hierarchy\n");
			वापस ~(u32)0;
		पूर्ण
	पूर्ण

	pr_debug("stash dest not found for %d on vcpu %d\n",
		 stash_dest_hपूर्णांक, vcpu);
	वापस ~(u32)0;
पूर्ण

/* Identअगरy अगर the PAACT table entry beदीर्घs to QMAN, BMAN or QMAN Portal */
#घोषणा QMAN_PAACE 1
#घोषणा QMAN_PORTAL_PAACE 2
#घोषणा BMAN_PAACE 3

/**
 * Setup operation mapping and stash destinations क्रम QMAN and QMAN portal.
 * Memory accesses to QMAN and BMAN निजी memory need not be coherent, so
 * clear the PAACE entry coherency attribute क्रम them.
 */
अटल व्योम setup_qbman_paace(काष्ठा paace *ppaace, पूर्णांक  paace_type)
अणु
	चयन (paace_type) अणु
	हाल QMAN_PAACE:
		set_bf(ppaace->impl_attr, PAACE_IA_OTM, PAACE_OTM_INDEXED);
		ppaace->op_encode.index_ot.omi = OMI_QMAN_PRIV;
		/* setup QMAN Private data stashing क्रम the L3 cache */
		set_bf(ppaace->impl_attr, PAACE_IA_CID, get_stash_id(PAMU_ATTR_CACHE_L3, 0));
		set_bf(ppaace->करोमुख्य_attr.to_host.coherency_required, PAACE_DA_HOST_CR,
		       0);
		अवरोध;
	हाल QMAN_PORTAL_PAACE:
		set_bf(ppaace->impl_attr, PAACE_IA_OTM, PAACE_OTM_INDEXED);
		ppaace->op_encode.index_ot.omi = OMI_QMAN;
		/* Set DQRR and Frame stashing क्रम the L3 cache */
		set_bf(ppaace->impl_attr, PAACE_IA_CID, get_stash_id(PAMU_ATTR_CACHE_L3, 0));
		अवरोध;
	हाल BMAN_PAACE:
		set_bf(ppaace->करोमुख्य_attr.to_host.coherency_required, PAACE_DA_HOST_CR,
		       0);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * Setup the operation mapping table क्रम various devices. This is a अटल
 * table where each table index corresponds to a particular device. PAMU uses
 * this table to translate device transaction to appropriate corenet
 * transaction.
 */
अटल व्योम setup_omt(काष्ठा ome *omt)
अणु
	काष्ठा ome *ome;

	/* Configure OMI_QMAN */
	ome = &omt[OMI_QMAN];

	ome->moe[IOE_READ_IDX] = EOE_VALID | EOE_READ;
	ome->moe[IOE_EREAD0_IDX] = EOE_VALID | EOE_RSA;
	ome->moe[IOE_WRITE_IDX] = EOE_VALID | EOE_WRITE;
	ome->moe[IOE_EWRITE0_IDX] = EOE_VALID | EOE_WWSAO;

	ome->moe[IOE_सूचीECT0_IDX] = EOE_VALID | EOE_LDEC;
	ome->moe[IOE_सूचीECT1_IDX] = EOE_VALID | EOE_LDECPE;

	/* Configure OMI_FMAN */
	ome = &omt[OMI_FMAN];
	ome->moe[IOE_READ_IDX]  = EOE_VALID | EOE_READI;
	ome->moe[IOE_WRITE_IDX] = EOE_VALID | EOE_WRITE;

	/* Configure OMI_QMAN निजी */
	ome = &omt[OMI_QMAN_PRIV];
	ome->moe[IOE_READ_IDX]  = EOE_VALID | EOE_READ;
	ome->moe[IOE_WRITE_IDX] = EOE_VALID | EOE_WRITE;
	ome->moe[IOE_EREAD0_IDX] = EOE_VALID | EOE_RSA;
	ome->moe[IOE_EWRITE0_IDX] = EOE_VALID | EOE_WWSA;

	/* Configure OMI_CAAM */
	ome = &omt[OMI_CAAM];
	ome->moe[IOE_READ_IDX]  = EOE_VALID | EOE_READI;
	ome->moe[IOE_WRITE_IDX] = EOE_VALID | EOE_WRITE;
पूर्ण

/*
 * Get the maximum number of PAACT table entries
 * and subwinकरोws supported by PAMU
 */
अटल व्योम get_pamu_cap_values(अचिन्हित दीर्घ pamu_reg_base)
अणु
	u32 pc_val;

	pc_val = in_be32((u32 *)(pamu_reg_base + PAMU_PC3));
	/* Maximum number of subwinकरोws per liodn */
	max_subwinकरोw_count = 1 << (1 + PAMU_PC3_MWCE(pc_val));
पूर्ण

/* Setup PAMU रेजिस्टरs poपूर्णांकing to PAACT, SPAACT and OMT */
अटल पूर्णांक setup_one_pamu(अचिन्हित दीर्घ pamu_reg_base, अचिन्हित दीर्घ pamu_reg_size,
			  phys_addr_t ppaact_phys, phys_addr_t spaact_phys,
			  phys_addr_t omt_phys)
अणु
	u32 *pc;
	काष्ठा pamu_mmap_regs *pamu_regs;

	pc = (u32 *) (pamu_reg_base + PAMU_PC);
	pamu_regs = (काष्ठा pamu_mmap_regs *)
		(pamu_reg_base + PAMU_MMAP_REGS_BASE);

	/* set up poपूर्णांकers to corenet control blocks */

	out_be32(&pamu_regs->ppbah, upper_32_bits(ppaact_phys));
	out_be32(&pamu_regs->ppbal, lower_32_bits(ppaact_phys));
	ppaact_phys = ppaact_phys + PAACT_SIZE;
	out_be32(&pamu_regs->pplah, upper_32_bits(ppaact_phys));
	out_be32(&pamu_regs->pplal, lower_32_bits(ppaact_phys));

	out_be32(&pamu_regs->spbah, upper_32_bits(spaact_phys));
	out_be32(&pamu_regs->spbal, lower_32_bits(spaact_phys));
	spaact_phys = spaact_phys + SPAACT_SIZE;
	out_be32(&pamu_regs->splah, upper_32_bits(spaact_phys));
	out_be32(&pamu_regs->splal, lower_32_bits(spaact_phys));

	out_be32(&pamu_regs->obah, upper_32_bits(omt_phys));
	out_be32(&pamu_regs->obal, lower_32_bits(omt_phys));
	omt_phys = omt_phys + OMT_SIZE;
	out_be32(&pamu_regs->olah, upper_32_bits(omt_phys));
	out_be32(&pamu_regs->olal, lower_32_bits(omt_phys));

	/*
	 * set PAMU enable bit,
	 * allow ppaact & omt to be cached
	 * & enable PAMU access violation पूर्णांकerrupts.
	 */

	out_be32((u32 *)(pamu_reg_base + PAMU_PICS),
		 PAMU_ACCESS_VIOLATION_ENABLE);
	out_be32(pc, PAMU_PC_PE | PAMU_PC_OCE | PAMU_PC_SPCC | PAMU_PC_PPCC);
	वापस 0;
पूर्ण

/* Enable all device LIODNS */
अटल व्योम setup_liodns(व्योम)
अणु
	पूर्णांक i, len;
	काष्ठा paace *ppaace;
	काष्ठा device_node *node = शून्य;
	स्थिर u32 *prop;

	क्रम_each_node_with_property(node, "fsl,liodn") अणु
		prop = of_get_property(node, "fsl,liodn", &len);
		क्रम (i = 0; i < len / माप(u32); i++) अणु
			पूर्णांक liodn;

			liodn = be32_to_cpup(&prop[i]);
			अगर (liodn >= PAACE_NUMBER_ENTRIES) अणु
				pr_debug("Invalid LIODN value %d\n", liodn);
				जारी;
			पूर्ण
			ppaace = pamu_get_ppaace(liodn);
			pamu_init_ppaace(ppaace);
			/* winकरोw size is 2^(WSE+1) bytes */
			set_bf(ppaace->addr_bitfields, PPAACE_AF_WSE, 35);
			ppaace->wbah = 0;
			set_bf(ppaace->addr_bitfields, PPAACE_AF_WBAL, 0);
			set_bf(ppaace->impl_attr, PAACE_IA_ATM,
			       PAACE_ATM_NO_XLATE);
			set_bf(ppaace->addr_bitfields, PAACE_AF_AP,
			       PAACE_AP_PERMS_ALL);
			अगर (of_device_is_compatible(node, "fsl,qman-portal"))
				setup_qbman_paace(ppaace, QMAN_PORTAL_PAACE);
			अगर (of_device_is_compatible(node, "fsl,qman"))
				setup_qbman_paace(ppaace, QMAN_PAACE);
			अगर (of_device_is_compatible(node, "fsl,bman"))
				setup_qbman_paace(ppaace, BMAN_PAACE);
			mb();
			pamu_enable_liodn(liodn);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t pamu_av_isr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा pamu_isr_data *data = arg;
	phys_addr_t phys;
	अचिन्हित पूर्णांक i, j, ret;

	pr_emerg("access violation interrupt\n");

	क्रम (i = 0; i < data->count; i++) अणु
		व्योम __iomem *p = data->pamu_reg_base + i * PAMU_OFFSET;
		u32 pics = in_be32(p + PAMU_PICS);

		अगर (pics & PAMU_ACCESS_VIOLATION_STAT) अणु
			u32 avs1 = in_be32(p + PAMU_AVS1);
			काष्ठा paace *paace;

			pr_emerg("POES1=%08x\n", in_be32(p + PAMU_POES1));
			pr_emerg("POES2=%08x\n", in_be32(p + PAMU_POES2));
			pr_emerg("AVS1=%08x\n", avs1);
			pr_emerg("AVS2=%08x\n", in_be32(p + PAMU_AVS2));
			pr_emerg("AVA=%016llx\n",
				 make64(in_be32(p + PAMU_AVAH),
					in_be32(p + PAMU_AVAL)));
			pr_emerg("UDAD=%08x\n", in_be32(p + PAMU_UDAD));
			pr_emerg("POEA=%016llx\n",
				 make64(in_be32(p + PAMU_POEAH),
					in_be32(p + PAMU_POEAL)));

			phys = make64(in_be32(p + PAMU_POEAH),
				      in_be32(p + PAMU_POEAL));

			/* Assume that POEA poपूर्णांकs to a PAACE */
			अगर (phys) अणु
				u32 *paace = phys_to_virt(phys);

				/* Only the first four words are relevant */
				क्रम (j = 0; j < 4; j++)
					pr_emerg("PAACE[%u]=%08x\n",
						 j, in_be32(paace + j));
			पूर्ण

			/* clear access violation condition */
			out_be32(p + PAMU_AVS1, avs1 & PAMU_AV_MASK);
			paace = pamu_get_ppaace(avs1 >> PAMU_AVS1_LIODN_SHIFT);
			BUG_ON(!paace);
			/* check अगर we got a violation क्रम a disabled LIODN */
			अगर (!get_bf(paace->addr_bitfields, PAACE_AF_V)) अणु
				/*
				 * As per hardware erratum A-003638, access
				 * violation can be reported क्रम a disabled
				 * LIODN. If we hit that condition, disable
				 * access violation reporting.
				 */
				pics &= ~PAMU_ACCESS_VIOLATION_ENABLE;
			पूर्ण अन्यथा अणु
				/* Disable the LIODN */
				ret = pamu_disable_liodn(avs1 >> PAMU_AVS1_LIODN_SHIFT);
				BUG_ON(ret);
				pr_emerg("Disabling liodn %x\n",
					 avs1 >> PAMU_AVS1_LIODN_SHIFT);
			पूर्ण
			out_be32((p + PAMU_PICS), pics);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा LAWAR_EN		0x80000000
#घोषणा LAWAR_TARGET_MASK	0x0FF00000
#घोषणा LAWAR_TARGET_SHIFT	20
#घोषणा LAWAR_SIZE_MASK		0x0000003F
#घोषणा LAWAR_CSDID_MASK	0x000FF000
#घोषणा LAWAR_CSDID_SHIFT	12

#घोषणा LAW_SIZE_4K		0xb

काष्ठा ccsr_law अणु
	u32	lawbarh;	/* LAWn base address high */
	u32	lawbarl;	/* LAWn base address low */
	u32	lawar;		/* LAWn attributes */
	u32	reserved;
पूर्ण;

/*
 * Create a coherence subकरोमुख्य क्रम a given memory block.
 */
अटल पूर्णांक create_csd(phys_addr_t phys, माप_प्रकार size, u32 csd_port_id)
अणु
	काष्ठा device_node *np;
	स्थिर __be32 *iprop;
	व्योम __iomem *lac = शून्य;	/* Local Access Control रेजिस्टरs */
	काष्ठा ccsr_law __iomem *law;
	व्योम __iomem *ccm = शून्य;
	u32 __iomem *csdids;
	अचिन्हित पूर्णांक i, num_laws, num_csds;
	u32 law_target = 0;
	u32 csd_id = 0;
	पूर्णांक ret = 0;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,corenet-law");
	अगर (!np)
		वापस -ENODEV;

	iprop = of_get_property(np, "fsl,num-laws", शून्य);
	अगर (!iprop) अणु
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	num_laws = be32_to_cpup(iprop);
	अगर (!num_laws) अणु
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	lac = of_iomap(np, 0);
	अगर (!lac) अणु
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	/* LAW रेजिस्टरs are at offset 0xC00 */
	law = lac + 0xC00;

	of_node_put(np);

	np = of_find_compatible_node(शून्य, शून्य, "fsl,corenet-cf");
	अगर (!np) अणु
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	iprop = of_get_property(np, "fsl,ccf-num-csdids", शून्य);
	अगर (!iprop) अणु
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	num_csds = be32_to_cpup(iprop);
	अगर (!num_csds) अणु
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	ccm = of_iomap(np, 0);
	अगर (!ccm) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	/* The unकरोcumented CSDID रेजिस्टरs are at offset 0x600 */
	csdids = ccm + 0x600;

	of_node_put(np);
	np = शून्य;

	/* Find an unused coherence subकरोमुख्य ID */
	क्रम (csd_id = 0; csd_id < num_csds; csd_id++) अणु
		अगर (!csdids[csd_id])
			अवरोध;
	पूर्ण

	/* Store the Port ID in the (unकरोcumented) proper CIDMRxx रेजिस्टर */
	csdids[csd_id] = csd_port_id;

	/* Find the DDR LAW that maps to our buffer. */
	क्रम (i = 0; i < num_laws; i++) अणु
		अगर (law[i].lawar & LAWAR_EN) अणु
			phys_addr_t law_start, law_end;

			law_start = make64(law[i].lawbarh, law[i].lawbarl);
			law_end = law_start +
				(2ULL << (law[i].lawar & LAWAR_SIZE_MASK));

			अगर (law_start <= phys && phys < law_end) अणु
				law_target = law[i].lawar & LAWAR_TARGET_MASK;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (i == 0 || i == num_laws) अणु
		/* This should never happen */
		ret = -ENOENT;
		जाओ error;
	पूर्ण

	/* Find a मुक्त LAW entry */
	जबतक (law[--i].lawar & LAWAR_EN) अणु
		अगर (i == 0) अणु
			/* No higher priority LAW slots available */
			ret = -ENOENT;
			जाओ error;
		पूर्ण
	पूर्ण

	law[i].lawbarh = upper_32_bits(phys);
	law[i].lawbarl = lower_32_bits(phys);
	wmb();
	law[i].lawar = LAWAR_EN | law_target | (csd_id << LAWAR_CSDID_SHIFT) |
		(LAW_SIZE_4K + get_order(size));
	wmb();

error:
	अगर (ccm)
		iounmap(ccm);

	अगर (lac)
		iounmap(lac);

	अगर (np)
		of_node_put(np);

	वापस ret;
पूर्ण

/*
 * Table of SVRs and the corresponding PORT_ID values. Port ID corresponds to a
 * bit map of snoopers क्रम a given range of memory mapped by a LAW.
 *
 * All future CoreNet-enabled SOCs will have this erratum(A-004510) fixed, so this
 * table should never need to be updated.  SVRs are guaranteed to be unique, so
 * there is no worry that a future SOC will inadvertently have one of these
 * values.
 */
अटल स्थिर काष्ठा अणु
	u32 svr;
	u32 port_id;
पूर्ण port_id_map[] = अणु
	अणु(SVR_P2040 << 8) | 0x10, 0xFF000000पूर्ण,	/* P2040 1.0 */
	अणु(SVR_P2040 << 8) | 0x11, 0xFF000000पूर्ण,	/* P2040 1.1 */
	अणु(SVR_P2041 << 8) | 0x10, 0xFF000000पूर्ण,	/* P2041 1.0 */
	अणु(SVR_P2041 << 8) | 0x11, 0xFF000000पूर्ण,	/* P2041 1.1 */
	अणु(SVR_P3041 << 8) | 0x10, 0xFF000000पूर्ण,	/* P3041 1.0 */
	अणु(SVR_P3041 << 8) | 0x11, 0xFF000000पूर्ण,	/* P3041 1.1 */
	अणु(SVR_P4040 << 8) | 0x20, 0xFFF80000पूर्ण,	/* P4040 2.0 */
	अणु(SVR_P4080 << 8) | 0x20, 0xFFF80000पूर्ण,	/* P4080 2.0 */
	अणु(SVR_P5010 << 8) | 0x10, 0xFC000000पूर्ण,	/* P5010 1.0 */
	अणु(SVR_P5010 << 8) | 0x20, 0xFC000000पूर्ण,	/* P5010 2.0 */
	अणु(SVR_P5020 << 8) | 0x10, 0xFC000000पूर्ण,	/* P5020 1.0 */
	अणु(SVR_P5021 << 8) | 0x10, 0xFF800000पूर्ण,	/* P5021 1.0 */
	अणु(SVR_P5040 << 8) | 0x10, 0xFF800000पूर्ण,	/* P5040 1.0 */
पूर्ण;

#घोषणा SVR_SECURITY	0x80000	/* The Security (E) bit */

अटल पूर्णांक fsl_pamu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *pamu_regs = शून्य;
	काष्ठा ccsr_guts __iomem *guts_regs = शून्य;
	u32 pamubypenr, pamu_counter;
	अचिन्हित दीर्घ pamu_reg_off;
	अचिन्हित दीर्घ pamu_reg_base;
	काष्ठा pamu_isr_data *data = शून्य;
	काष्ठा device_node *guts_node;
	u64 size;
	काष्ठा page *p;
	पूर्णांक ret = 0;
	पूर्णांक irq;
	phys_addr_t ppaact_phys;
	phys_addr_t spaact_phys;
	काष्ठा ome *omt;
	phys_addr_t omt_phys;
	माप_प्रकार mem_size = 0;
	अचिन्हित पूर्णांक order = 0;
	u32 csd_port_id = 0;
	अचिन्हित i;
	/*
	 * क्रमागतerate all PAMUs and allocate and setup PAMU tables
	 * क्रम each of them,
	 * NOTE : All PAMUs share the same LIODN tables.
	 */

	अगर (WARN_ON(probed))
		वापस -EBUSY;

	pamu_regs = of_iomap(dev->of_node, 0);
	अगर (!pamu_regs) अणु
		dev_err(dev, "ioremap of PAMU node failed\n");
		वापस -ENOMEM;
	पूर्ण
	of_get_address(dev->of_node, 0, &size, शून्य);

	irq = irq_of_parse_and_map(dev->of_node, 0);
	अगर (irq == NO_IRQ) अणु
		dev_warn(dev, "no interrupts listed in PAMU node\n");
		जाओ error;
	पूर्ण

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण
	data->pamu_reg_base = pamu_regs;
	data->count = size / PAMU_OFFSET;

	/* The ISR needs access to the regs, so we won't iounmap them */
	ret = request_irq(irq, pamu_av_isr, 0, "pamu", data);
	अगर (ret < 0) अणु
		dev_err(dev, "error %i installing ISR for irq %i\n", ret, irq);
		जाओ error;
	पूर्ण

	guts_node = of_find_matching_node(शून्य, guts_device_ids);
	अगर (!guts_node) अणु
		dev_err(dev, "could not find GUTS node %pOF\n", dev->of_node);
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	guts_regs = of_iomap(guts_node, 0);
	of_node_put(guts_node);
	अगर (!guts_regs) अणु
		dev_err(dev, "ioremap of GUTS node failed\n");
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	/* पढ़ो in the PAMU capability रेजिस्टरs */
	get_pamu_cap_values((अचिन्हित दीर्घ)pamu_regs);
	/*
	 * To simplअगरy the allocation of a coherency करोमुख्य, we allocate the
	 * PAACT and the OMT in the same memory buffer.  Unक्रमtunately, this
	 * wastes more memory compared to allocating the buffers separately.
	 */
	/* Determine how much memory we need */
	mem_size = (PAGE_SIZE << get_order(PAACT_SIZE)) +
		(PAGE_SIZE << get_order(SPAACT_SIZE)) +
		(PAGE_SIZE << get_order(OMT_SIZE));
	order = get_order(mem_size);

	p = alloc_pages(GFP_KERNEL | __GFP_ZERO, order);
	अगर (!p) अणु
		dev_err(dev, "unable to allocate PAACT/SPAACT/OMT block\n");
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	ppaact = page_address(p);
	ppaact_phys = page_to_phys(p);

	/* Make sure the memory is naturally aligned */
	अगर (ppaact_phys & ((PAGE_SIZE << order) - 1)) अणु
		dev_err(dev, "PAACT/OMT block is unaligned\n");
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	spaact = (व्योम *)ppaact + (PAGE_SIZE << get_order(PAACT_SIZE));
	omt = (व्योम *)spaact + (PAGE_SIZE << get_order(SPAACT_SIZE));

	dev_dbg(dev, "ppaact virt=%p phys=%pa\n", ppaact, &ppaact_phys);

	/* Check to see अगर we need to implement the work-around on this SOC */

	/* Determine the Port ID क्रम our coherence subकरोमुख्य */
	क्रम (i = 0; i < ARRAY_SIZE(port_id_map); i++) अणु
		अगर (port_id_map[i].svr == (mfspr(SPRN_SVR) & ~SVR_SECURITY)) अणु
			csd_port_id = port_id_map[i].port_id;
			dev_dbg(dev, "found matching SVR %08x\n",
				port_id_map[i].svr);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (csd_port_id) अणु
		dev_dbg(dev, "creating coherency subdomain at address %pa, size %zu, port id 0x%08x",
			&ppaact_phys, mem_size, csd_port_id);

		ret = create_csd(ppaact_phys, mem_size, csd_port_id);
		अगर (ret) अणु
			dev_err(dev, "could not create coherence subdomain\n");
			वापस ret;
		पूर्ण
	पूर्ण

	spaact_phys = virt_to_phys(spaact);
	omt_phys = virt_to_phys(omt);

	pamubypenr = in_be32(&guts_regs->pamubypenr);

	क्रम (pamu_reg_off = 0, pamu_counter = 0x80000000; pamu_reg_off < size;
	     pamu_reg_off += PAMU_OFFSET, pamu_counter >>= 1) अणु

		pamu_reg_base = (अचिन्हित दीर्घ)pamu_regs + pamu_reg_off;
		setup_one_pamu(pamu_reg_base, pamu_reg_off, ppaact_phys,
			       spaact_phys, omt_phys);
		/* Disable PAMU bypass क्रम this PAMU */
		pamubypenr &= ~pamu_counter;
	पूर्ण

	setup_omt(omt);

	/* Enable all relevant PAMU(s) */
	out_be32(&guts_regs->pamubypenr, pamubypenr);

	iounmap(guts_regs);

	/* Enable DMA क्रम the LIODNs in the device tree */

	setup_liodns();

	probed = true;

	वापस 0;

error:
	अगर (irq != NO_IRQ)
		मुक्त_irq(irq, data);

	kमुक्त_sensitive(data);

	अगर (pamu_regs)
		iounmap(pamu_regs);

	अगर (guts_regs)
		iounmap(guts_regs);

	अगर (ppaact)
		मुक्त_pages((अचिन्हित दीर्घ)ppaact, order);

	ppaact = शून्य;

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver fsl_of_pamu_driver = अणु
	.driver = अणु
		.name = "fsl-of-pamu",
	पूर्ण,
	.probe = fsl_pamu_probe,
पूर्ण;

अटल __init पूर्णांक fsl_pamu_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev = शून्य;
	काष्ठा device_node *np;
	पूर्णांक ret;

	/*
	 * The normal OF process calls the probe function at some
	 * indeterminate later समय, after most drivers have loaded.  This is
	 * too late क्रम us, because PAMU clients (like the Qman driver)
	 * depend on PAMU being initialized early.
	 *
	 * So instead, we "manually" call our probe function by creating the
	 * platक्रमm devices ourselves.
	 */

	/*
	 * We assume that there is only one PAMU node in the device tree.  A
	 * single PAMU node represents all of the PAMU devices in the SOC
	 * alपढ़ोy.   Everything अन्यथा alपढ़ोy makes that assumption, and the
	 * binding क्रम the PAMU nodes करोesn't allow क्रम any parent-child
	 * relationships anyway.  In other words, support क्रम more than one
	 * PAMU node would require signअगरicant changes to a lot of code.
	 */

	np = of_find_compatible_node(शून्य, शून्य, "fsl,pamu");
	अगर (!np) अणु
		pr_err("could not find a PAMU node\n");
		वापस -ENODEV;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&fsl_of_pamu_driver);
	अगर (ret) अणु
		pr_err("could not register driver (err=%i)\n", ret);
		जाओ error_driver_रेजिस्टर;
	पूर्ण

	pdev = platक्रमm_device_alloc("fsl-of-pamu", 0);
	अगर (!pdev) अणु
		pr_err("could not allocate device %pOF\n", np);
		ret = -ENOMEM;
		जाओ error_device_alloc;
	पूर्ण
	pdev->dev.of_node = of_node_get(np);

	ret = pamu_करोमुख्य_init();
	अगर (ret)
		जाओ error_device_add;

	ret = platक्रमm_device_add(pdev);
	अगर (ret) अणु
		pr_err("could not add device %pOF (err=%i)\n", np, ret);
		जाओ error_device_add;
	पूर्ण

	वापस 0;

error_device_add:
	of_node_put(pdev->dev.of_node);
	pdev->dev.of_node = शून्य;

	platक्रमm_device_put(pdev);

error_device_alloc:
	platक्रमm_driver_unरेजिस्टर(&fsl_of_pamu_driver);

error_driver_रेजिस्टर:
	of_node_put(np);

	वापस ret;
पूर्ण
arch_initcall(fsl_pamu_init);
