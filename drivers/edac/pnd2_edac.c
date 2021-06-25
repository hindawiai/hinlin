<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Pondicherry2 memory controller.
 *
 * Copyright (c) 2016, Intel Corporation.
 *
 * [Derived from sb_edac.c]
 *
 * Translation of प्रणाली physical addresses to DIMM addresses
 * is a two stage process:
 *
 * First the Pondicherry 2 memory controller handles slice and channel पूर्णांकerleaving
 * in "sys2pmi()". This is (almost) completley common between platक्रमms.
 *
 * Then a platक्रमm specअगरic dunit (DIMM unit) completes the process to provide DIMM,
 * rank, bank, row and column using the appropriate "dunit_ops" functions/parameters.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/edac.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/smp.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/math64.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mce.h>

#समावेश "edac_mc.h"
#समावेश "edac_module.h"
#समावेश "pnd2_edac.h"

#घोषणा EDAC_MOD_STR		"pnd2_edac"

#घोषणा APL_NUM_CHANNELS	4
#घोषणा DNV_NUM_CHANNELS	2
#घोषणा DNV_MAX_DIMMS		2 /* Max DIMMs per channel */

क्रमागत type अणु
	APL,
	DNV, /* All requests go to PMI CH0 on each slice (CH1 disabled) */
पूर्ण;

काष्ठा dram_addr अणु
	पूर्णांक chan;
	पूर्णांक dimm;
	पूर्णांक rank;
	पूर्णांक bank;
	पूर्णांक row;
	पूर्णांक col;
पूर्ण;

काष्ठा pnd2_pvt अणु
	पूर्णांक dimm_geom[APL_NUM_CHANNELS];
	u64 tolm, tohm;
पूर्ण;

/*
 * System address space is भागided पूर्णांकo multiple regions with
 * dअगरferent पूर्णांकerleave rules in each. The as0/as1 regions
 * have no पूर्णांकerleaving at all. The as2 region is पूर्णांकerleaved
 * between two channels. The mot region is magic and may overlap
 * other regions, with its पूर्णांकerleave rules taking precedence.
 * Addresses not in any of these regions are पूर्णांकerleaved across
 * all four channels.
 */
अटल काष्ठा region अणु
	u64	base;
	u64	limit;
	u8	enabled;
पूर्ण mot, as0, as1, as2;

अटल काष्ठा dunit_ops अणु
	अक्षर *name;
	क्रमागत type type;
	पूर्णांक pmiaddr_shअगरt;
	पूर्णांक pmiidx_shअगरt;
	पूर्णांक channels;
	पूर्णांक dimms_per_channel;
	पूर्णांक (*rd_reg)(पूर्णांक port, पूर्णांक off, पूर्णांक op, व्योम *data, माप_प्रकार sz, अक्षर *name);
	पूर्णांक (*get_रेजिस्टरs)(व्योम);
	पूर्णांक (*check_ecc)(व्योम);
	व्योम (*mk_region)(अक्षर *name, काष्ठा region *rp, व्योम *asym);
	व्योम (*get_dimm_config)(काष्ठा mem_ctl_info *mci);
	पूर्णांक (*pmi2mem)(काष्ठा mem_ctl_info *mci, u64 pmiaddr, u32 pmiidx,
				   काष्ठा dram_addr *daddr, अक्षर *msg);
पूर्ण *ops;

अटल काष्ठा mem_ctl_info *pnd2_mci;

#घोषणा PND2_MSG_SIZE	256

/* Debug macros */
#घोषणा pnd2_prपूर्णांकk(level, fmt, arg...)			\
	edac_prपूर्णांकk(level, "pnd2", fmt, ##arg)

#घोषणा pnd2_mc_prपूर्णांकk(mci, level, fmt, arg...)	\
	edac_mc_chipset_prपूर्णांकk(mci, level, "pnd2", fmt, ##arg)

#घोषणा MOT_CHAN_INTLV_BIT_1SLC_2CH 12
#घोषणा MOT_CHAN_INTLV_BIT_2SLC_2CH 13
#घोषणा SELECTOR_DISABLED (-1)
#घोषणा _4GB (1ul << 32)

#घोषणा PMI_ADDRESS_WIDTH	31
#घोषणा PND_MAX_PHYS_BIT	39

#घोषणा APL_ASYMSHIFT		28
#घोषणा DNV_ASYMSHIFT		31
#घोषणा CH_HASH_MASK_LSB	6
#घोषणा SLICE_HASH_MASK_LSB	6
#घोषणा MOT_SLC_INTLV_BIT	12
#घोषणा LOG2_PMI_ADDR_GRANULARITY	5
#घोषणा MOT_SHIFT	24

#घोषणा GET_BITFIELD(v, lo, hi)	(((v) & GENMASK_ULL(hi, lo)) >> (lo))
#घोषणा U64_LSHIFT(val, s)	((u64)(val) << (s))

/*
 * On Apollo Lake we access memory controller रेजिस्टरs via a
 * side-band mailbox style पूर्णांकerface in a hidden PCI device
 * configuration space.
 */
अटल काष्ठा pci_bus	*p2sb_bus;
#घोषणा P2SB_DEVFN	PCI_DEVFN(0xd, 0)
#घोषणा P2SB_ADDR_OFF	0xd0
#घोषणा P2SB_DATA_OFF	0xd4
#घोषणा P2SB_STAT_OFF	0xd8
#घोषणा P2SB_ROUT_OFF	0xda
#घोषणा P2SB_EADD_OFF	0xdc
#घोषणा P2SB_HIDE_OFF	0xe1

#घोषणा P2SB_BUSY	1

#घोषणा P2SB_READ(size, off, ptr) \
	pci_bus_पढ़ो_config_##size(p2sb_bus, P2SB_DEVFN, off, ptr)
#घोषणा P2SB_WRITE(size, off, val) \
	pci_bus_ग_लिखो_config_##size(p2sb_bus, P2SB_DEVFN, off, val)

अटल bool p2sb_is_busy(u16 *status)
अणु
	P2SB_READ(word, P2SB_STAT_OFF, status);

	वापस !!(*status & P2SB_BUSY);
पूर्ण

अटल पूर्णांक _apl_rd_reg(पूर्णांक port, पूर्णांक off, पूर्णांक op, u32 *data)
अणु
	पूर्णांक retries = 0xff, ret;
	u16 status;
	u8 hidden;

	/* Unhide the P2SB device, अगर it's hidden */
	P2SB_READ(byte, P2SB_HIDE_OFF, &hidden);
	अगर (hidden)
		P2SB_WRITE(byte, P2SB_HIDE_OFF, 0);

	अगर (p2sb_is_busy(&status)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	P2SB_WRITE(dword, P2SB_ADDR_OFF, (port << 24) | off);
	P2SB_WRITE(dword, P2SB_DATA_OFF, 0);
	P2SB_WRITE(dword, P2SB_EADD_OFF, 0);
	P2SB_WRITE(word, P2SB_ROUT_OFF, 0);
	P2SB_WRITE(word, P2SB_STAT_OFF, (op << 8) | P2SB_BUSY);

	जबतक (p2sb_is_busy(&status)) अणु
		अगर (retries-- == 0) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण

	P2SB_READ(dword, P2SB_DATA_OFF, data);
	ret = (status >> 1) & 0x3;
out:
	/* Hide the P2SB device, अगर it was hidden beक्रमe */
	अगर (hidden)
		P2SB_WRITE(byte, P2SB_HIDE_OFF, hidden);

	वापस ret;
पूर्ण

अटल पूर्णांक apl_rd_reg(पूर्णांक port, पूर्णांक off, पूर्णांक op, व्योम *data, माप_प्रकार sz, अक्षर *name)
अणु
	पूर्णांक ret = 0;

	edac_dbg(2, "Read %s port=%x off=%x op=%x\n", name, port, off, op);
	चयन (sz) अणु
	हाल 8:
		ret = _apl_rd_reg(port, off + 4, op, (u32 *)(data + 4));
		fallthrough;
	हाल 4:
		ret |= _apl_rd_reg(port, off, op, (u32 *)data);
		pnd2_prपूर्णांकk(KERN_DEBUG, "%s=%x%08x ret=%d\n", name,
					sz == 8 ? *((u32 *)(data + 4)) : 0, *((u32 *)data), ret);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल u64 get_mem_ctrl_hub_base_addr(व्योम)
अणु
	काष्ठा b_cr_mchbar_lo_pci lo;
	काष्ठा b_cr_mchbar_hi_pci hi;
	काष्ठा pci_dev *pdev;

	pdev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x1980, शून्य);
	अगर (pdev) अणु
		pci_पढ़ो_config_dword(pdev, 0x48, (u32 *)&lo);
		pci_पढ़ो_config_dword(pdev, 0x4c, (u32 *)&hi);
		pci_dev_put(pdev);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	अगर (!lo.enable) अणु
		edac_dbg(2, "MMIO via memory controller hub base address is disabled!\n");
		वापस 0;
	पूर्ण

	वापस U64_LSHIFT(hi.base, 32) | U64_LSHIFT(lo.base, 15);
पूर्ण

अटल u64 get_sideband_reg_base_addr(व्योम)
अणु
	काष्ठा pci_dev *pdev;
	u32 hi, lo;
	u8 hidden;

	pdev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x19dd, शून्य);
	अगर (pdev) अणु
		/* Unhide the P2SB device, अगर it's hidden */
		pci_पढ़ो_config_byte(pdev, 0xe1, &hidden);
		अगर (hidden)
			pci_ग_लिखो_config_byte(pdev, 0xe1, 0);

		pci_पढ़ो_config_dword(pdev, 0x10, &lo);
		pci_पढ़ो_config_dword(pdev, 0x14, &hi);
		lo &= 0xfffffff0;

		/* Hide the P2SB device, अगर it was hidden beक्रमe */
		अगर (hidden)
			pci_ग_लिखो_config_byte(pdev, 0xe1, hidden);

		pci_dev_put(pdev);
		वापस (U64_LSHIFT(hi, 32) | U64_LSHIFT(lo, 0));
	पूर्ण अन्यथा अणु
		वापस 0xfd000000;
	पूर्ण
पूर्ण

#घोषणा DNV_MCHBAR_SIZE  0x8000
#घोषणा DNV_SB_PORT_SIZE 0x10000
अटल पूर्णांक dnv_rd_reg(पूर्णांक port, पूर्णांक off, पूर्णांक op, व्योम *data, माप_प्रकार sz, अक्षर *name)
अणु
	काष्ठा pci_dev *pdev;
	अक्षर *base;
	u64 addr;
	अचिन्हित दीर्घ size;

	अगर (op == 4) अणु
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x1980, शून्य);
		अगर (!pdev)
			वापस -ENODEV;

		pci_पढ़ो_config_dword(pdev, off, data);
		pci_dev_put(pdev);
	पूर्ण अन्यथा अणु
		/* MMIO via memory controller hub base address */
		अगर (op == 0 && port == 0x4c) अणु
			addr = get_mem_ctrl_hub_base_addr();
			अगर (!addr)
				वापस -ENODEV;
			size = DNV_MCHBAR_SIZE;
		पूर्ण अन्यथा अणु
			/* MMIO via sideband रेजिस्टर base address */
			addr = get_sideband_reg_base_addr();
			अगर (!addr)
				वापस -ENODEV;
			addr += (port << 16);
			size = DNV_SB_PORT_SIZE;
		पूर्ण

		base = ioremap((resource_माप_प्रकार)addr, size);
		अगर (!base)
			वापस -ENODEV;

		अगर (sz == 8)
			*(u32 *)(data + 4) = *(u32 *)(base + off + 4);
		*(u32 *)data = *(u32 *)(base + off);

		iounmap(base);
	पूर्ण

	edac_dbg(2, "Read %s=%.8x_%.8x\n", name,
			(sz == 8) ? *(u32 *)(data + 4) : 0, *(u32 *)data);

	वापस 0;
पूर्ण

#घोषणा RD_REGP(regp, regname, port)	\
	ops->rd_reg(port,					\
		regname##_offset,				\
		regname##_r_opcode,				\
		regp, माप(काष्ठा regname),	\
		#regname)

#घोषणा RD_REG(regp, regname)			\
	ops->rd_reg(regname ## _port,		\
		regname##_offset,				\
		regname##_r_opcode,				\
		regp, माप(काष्ठा regname),	\
		#regname)

अटल u64 top_lm, top_hm;
अटल bool two_slices;
अटल bool two_channels; /* Both PMI channels in one slice enabled */

अटल u8 sym_chan_mask;
अटल u8 asym_chan_mask;
अटल u8 chan_mask;

अटल पूर्णांक slice_selector = -1;
अटल पूर्णांक chan_selector = -1;
अटल u64 slice_hash_mask;
अटल u64 chan_hash_mask;

अटल व्योम mk_region(अक्षर *name, काष्ठा region *rp, u64 base, u64 limit)
अणु
	rp->enabled = 1;
	rp->base = base;
	rp->limit = limit;
	edac_dbg(2, "Region:%s [%llx, %llx]\n", name, base, limit);
पूर्ण

अटल व्योम mk_region_mask(अक्षर *name, काष्ठा region *rp, u64 base, u64 mask)
अणु
	अगर (mask == 0) अणु
		pr_info(FW_BUG "MOT mask cannot be zero\n");
		वापस;
	पूर्ण
	अगर (mask != GENMASK_ULL(PND_MAX_PHYS_BIT, __ffs(mask))) अणु
		pr_info(FW_BUG "MOT mask not power of two\n");
		वापस;
	पूर्ण
	अगर (base & ~mask) अणु
		pr_info(FW_BUG "MOT region base/mask alignment error\n");
		वापस;
	पूर्ण
	rp->base = base;
	rp->limit = (base | ~mask) & GENMASK_ULL(PND_MAX_PHYS_BIT, 0);
	rp->enabled = 1;
	edac_dbg(2, "Region:%s [%llx, %llx]\n", name, base, rp->limit);
पूर्ण

अटल bool in_region(काष्ठा region *rp, u64 addr)
अणु
	अगर (!rp->enabled)
		वापस false;

	वापस rp->base <= addr && addr <= rp->limit;
पूर्ण

अटल पूर्णांक gen_sym_mask(काष्ठा b_cr_slice_channel_hash *p)
अणु
	पूर्णांक mask = 0;

	अगर (!p->slice_0_mem_disabled)
		mask |= p->sym_slice0_channel_enabled;

	अगर (!p->slice_1_disabled)
		mask |= p->sym_slice1_channel_enabled << 2;

	अगर (p->ch_1_disabled || p->enable_pmi_dual_data_mode)
		mask &= 0x5;

	वापस mask;
पूर्ण

अटल पूर्णांक gen_asym_mask(काष्ठा b_cr_slice_channel_hash *p,
			 काष्ठा b_cr_asym_mem_region0_mchbar *as0,
			 काष्ठा b_cr_asym_mem_region1_mchbar *as1,
			 काष्ठा b_cr_asym_2way_mem_region_mchbar *as2way)
अणु
	स्थिर पूर्णांक पूर्णांकlv[] = अणु 0x5, 0xA, 0x3, 0xC पूर्ण;
	पूर्णांक mask = 0;

	अगर (as2way->asym_2way_पूर्णांकerleave_enable)
		mask = पूर्णांकlv[as2way->asym_2way_पूर्णांकlv_mode];
	अगर (as0->slice0_asym_enable)
		mask |= (1 << as0->slice0_asym_channel_select);
	अगर (as1->slice1_asym_enable)
		mask |= (4 << as1->slice1_asym_channel_select);
	अगर (p->slice_0_mem_disabled)
		mask &= 0xc;
	अगर (p->slice_1_disabled)
		mask &= 0x3;
	अगर (p->ch_1_disabled || p->enable_pmi_dual_data_mode)
		mask &= 0x5;

	वापस mask;
पूर्ण

अटल काष्ठा b_cr_tolud_pci tolud;
अटल काष्ठा b_cr_touud_lo_pci touud_lo;
अटल काष्ठा b_cr_touud_hi_pci touud_hi;
अटल काष्ठा b_cr_asym_mem_region0_mchbar asym0;
अटल काष्ठा b_cr_asym_mem_region1_mchbar asym1;
अटल काष्ठा b_cr_asym_2way_mem_region_mchbar asym_2way;
अटल काष्ठा b_cr_mot_out_base_mchbar mot_base;
अटल काष्ठा b_cr_mot_out_mask_mchbar mot_mask;
अटल काष्ठा b_cr_slice_channel_hash chash;

/* Apollo Lake dunit */
/*
 * Validated on board with just two DIMMs in the [0] and [2] positions
 * in this array. Other port number matches करोcumentation, but caution
 * advised.
 */
अटल स्थिर पूर्णांक apl_dports[APL_NUM_CHANNELS] = अणु 0x18, 0x10, 0x11, 0x19 पूर्ण;
अटल काष्ठा d_cr_drp0 drp0[APL_NUM_CHANNELS];

/* Denverton dunit */
अटल स्थिर पूर्णांक dnv_dports[DNV_NUM_CHANNELS] = अणु 0x10, 0x12 पूर्ण;
अटल काष्ठा d_cr_dsch dsch;
अटल काष्ठा d_cr_ecc_ctrl ecc_ctrl[DNV_NUM_CHANNELS];
अटल काष्ठा d_cr_drp drp[DNV_NUM_CHANNELS];
अटल काष्ठा d_cr_dmap dmap[DNV_NUM_CHANNELS];
अटल काष्ठा d_cr_dmap1 dmap1[DNV_NUM_CHANNELS];
अटल काष्ठा d_cr_dmap2 dmap2[DNV_NUM_CHANNELS];
अटल काष्ठा d_cr_dmap3 dmap3[DNV_NUM_CHANNELS];
अटल काष्ठा d_cr_dmap4 dmap4[DNV_NUM_CHANNELS];
अटल काष्ठा d_cr_dmap5 dmap5[DNV_NUM_CHANNELS];

अटल व्योम apl_mk_region(अक्षर *name, काष्ठा region *rp, व्योम *asym)
अणु
	काष्ठा b_cr_asym_mem_region0_mchbar *a = asym;

	mk_region(name, rp,
			  U64_LSHIFT(a->slice0_asym_base, APL_ASYMSHIFT),
			  U64_LSHIFT(a->slice0_asym_limit, APL_ASYMSHIFT) +
			  GENMASK_ULL(APL_ASYMSHIFT - 1, 0));
पूर्ण

अटल व्योम dnv_mk_region(अक्षर *name, काष्ठा region *rp, व्योम *asym)
अणु
	काष्ठा b_cr_asym_mem_region_denverton *a = asym;

	mk_region(name, rp,
			  U64_LSHIFT(a->slice_asym_base, DNV_ASYMSHIFT),
			  U64_LSHIFT(a->slice_asym_limit, DNV_ASYMSHIFT) +
			  GENMASK_ULL(DNV_ASYMSHIFT - 1, 0));
पूर्ण

अटल पूर्णांक apl_get_रेजिस्टरs(व्योम)
अणु
	पूर्णांक ret = -ENODEV;
	पूर्णांक i;

	अगर (RD_REG(&asym_2way, b_cr_asym_2way_mem_region_mchbar))
		वापस -ENODEV;

	/*
	 * RD_REGP() will fail क्रम unpopulated or non-existent
	 * DIMM slots. Return success अगर we find at least one DIMM.
	 */
	क्रम (i = 0; i < APL_NUM_CHANNELS; i++)
		अगर (!RD_REGP(&drp0[i], d_cr_drp0, apl_dports[i]))
			ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक dnv_get_रेजिस्टरs(व्योम)
अणु
	पूर्णांक i;

	अगर (RD_REG(&dsch, d_cr_dsch))
		वापस -ENODEV;

	क्रम (i = 0; i < DNV_NUM_CHANNELS; i++)
		अगर (RD_REGP(&ecc_ctrl[i], d_cr_ecc_ctrl, dnv_dports[i]) ||
			RD_REGP(&drp[i], d_cr_drp, dnv_dports[i]) ||
			RD_REGP(&dmap[i], d_cr_dmap, dnv_dports[i]) ||
			RD_REGP(&dmap1[i], d_cr_dmap1, dnv_dports[i]) ||
			RD_REGP(&dmap2[i], d_cr_dmap2, dnv_dports[i]) ||
			RD_REGP(&dmap3[i], d_cr_dmap3, dnv_dports[i]) ||
			RD_REGP(&dmap4[i], d_cr_dmap4, dnv_dports[i]) ||
			RD_REGP(&dmap5[i], d_cr_dmap5, dnv_dports[i]))
			वापस -ENODEV;

	वापस 0;
पूर्ण

/*
 * Read all the h/w config रेजिस्टरs once here (they करोn't
 * change at run समय. Figure out which address ranges have
 * which पूर्णांकerleave अक्षरacteristics.
 */
अटल पूर्णांक get_रेजिस्टरs(व्योम)
अणु
	स्थिर पूर्णांक पूर्णांकlv[] = अणु 10, 11, 12, 12 पूर्ण;

	अगर (RD_REG(&tolud, b_cr_tolud_pci) ||
		RD_REG(&touud_lo, b_cr_touud_lo_pci) ||
		RD_REG(&touud_hi, b_cr_touud_hi_pci) ||
		RD_REG(&asym0, b_cr_asym_mem_region0_mchbar) ||
		RD_REG(&asym1, b_cr_asym_mem_region1_mchbar) ||
		RD_REG(&mot_base, b_cr_mot_out_base_mchbar) ||
		RD_REG(&mot_mask, b_cr_mot_out_mask_mchbar) ||
		RD_REG(&chash, b_cr_slice_channel_hash))
		वापस -ENODEV;

	अगर (ops->get_रेजिस्टरs())
		वापस -ENODEV;

	अगर (ops->type == DNV) अणु
		/* PMI channel idx (always 0) क्रम asymmetric region */
		asym0.slice0_asym_channel_select = 0;
		asym1.slice1_asym_channel_select = 0;
		/* PMI channel biपंचांगap (always 1) क्रम symmetric region */
		chash.sym_slice0_channel_enabled = 0x1;
		chash.sym_slice1_channel_enabled = 0x1;
	पूर्ण

	अगर (asym0.slice0_asym_enable)
		ops->mk_region("as0", &as0, &asym0);

	अगर (asym1.slice1_asym_enable)
		ops->mk_region("as1", &as1, &asym1);

	अगर (asym_2way.asym_2way_पूर्णांकerleave_enable) अणु
		mk_region("as2way", &as2,
				  U64_LSHIFT(asym_2way.asym_2way_base, APL_ASYMSHIFT),
				  U64_LSHIFT(asym_2way.asym_2way_limit, APL_ASYMSHIFT) +
				  GENMASK_ULL(APL_ASYMSHIFT - 1, 0));
	पूर्ण

	अगर (mot_base.imr_en) अणु
		mk_region_mask("mot", &mot,
					   U64_LSHIFT(mot_base.mot_out_base, MOT_SHIFT),
					   U64_LSHIFT(mot_mask.mot_out_mask, MOT_SHIFT));
	पूर्ण

	top_lm = U64_LSHIFT(tolud.tolud, 20);
	top_hm = U64_LSHIFT(touud_hi.touud, 32) | U64_LSHIFT(touud_lo.touud, 20);

	two_slices = !chash.slice_1_disabled &&
				 !chash.slice_0_mem_disabled &&
				 (chash.sym_slice0_channel_enabled != 0) &&
				 (chash.sym_slice1_channel_enabled != 0);
	two_channels = !chash.ch_1_disabled &&
				 !chash.enable_pmi_dual_data_mode &&
				 ((chash.sym_slice0_channel_enabled == 3) ||
				 (chash.sym_slice1_channel_enabled == 3));

	sym_chan_mask = gen_sym_mask(&chash);
	asym_chan_mask = gen_asym_mask(&chash, &asym0, &asym1, &asym_2way);
	chan_mask = sym_chan_mask | asym_chan_mask;

	अगर (two_slices && !two_channels) अणु
		अगर (chash.hvm_mode)
			slice_selector = 29;
		अन्यथा
			slice_selector = पूर्णांकlv[chash.पूर्णांकerleave_mode];
	पूर्ण अन्यथा अगर (!two_slices && two_channels) अणु
		अगर (chash.hvm_mode)
			chan_selector = 29;
		अन्यथा
			chan_selector = पूर्णांकlv[chash.पूर्णांकerleave_mode];
	पूर्ण अन्यथा अगर (two_slices && two_channels) अणु
		अगर (chash.hvm_mode) अणु
			slice_selector = 29;
			chan_selector = 30;
		पूर्ण अन्यथा अणु
			slice_selector = पूर्णांकlv[chash.पूर्णांकerleave_mode];
			chan_selector = पूर्णांकlv[chash.पूर्णांकerleave_mode] + 1;
		पूर्ण
	पूर्ण

	अगर (two_slices) अणु
		अगर (!chash.hvm_mode)
			slice_hash_mask = chash.slice_hash_mask << SLICE_HASH_MASK_LSB;
		अगर (!two_channels)
			slice_hash_mask |= BIT_ULL(slice_selector);
	पूर्ण

	अगर (two_channels) अणु
		अगर (!chash.hvm_mode)
			chan_hash_mask = chash.ch_hash_mask << CH_HASH_MASK_LSB;
		अगर (!two_slices)
			chan_hash_mask |= BIT_ULL(chan_selector);
	पूर्ण

	वापस 0;
पूर्ण

/* Get a contiguous memory address (हटाओ the MMIO gap) */
अटल u64 हटाओ_mmio_gap(u64 sys)
अणु
	वापस (sys < _4GB) ? sys : sys - (_4GB - top_lm);
पूर्ण

/* Squeeze out one address bit, shअगरt upper part करोwn to fill gap */
अटल व्योम हटाओ_addr_bit(u64 *addr, पूर्णांक bitidx)
अणु
	u64	mask;

	अगर (bitidx == -1)
		वापस;

	mask = (1ull << bitidx) - 1;
	*addr = ((*addr >> 1) & ~mask) | (*addr & mask);
पूर्ण

/* XOR all the bits from addr specअगरied in mask */
अटल पूर्णांक hash_by_mask(u64 addr, u64 mask)
अणु
	u64 result = addr & mask;

	result = (result >> 32) ^ result;
	result = (result >> 16) ^ result;
	result = (result >> 8) ^ result;
	result = (result >> 4) ^ result;
	result = (result >> 2) ^ result;
	result = (result >> 1) ^ result;

	वापस (पूर्णांक)result & 1;
पूर्ण

/*
 * First stage decode. Take the प्रणाली address and figure out which
 * second stage will deal with it based on पूर्णांकerleave modes.
 */
अटल पूर्णांक sys2pmi(स्थिर u64 addr, u32 *pmiidx, u64 *pmiaddr, अक्षर *msg)
अणु
	u64 contig_addr, contig_base, contig_offset, contig_base_adj;
	पूर्णांक mot_पूर्णांकlv_bit = two_slices ? MOT_CHAN_INTLV_BIT_2SLC_2CH :
						MOT_CHAN_INTLV_BIT_1SLC_2CH;
	पूर्णांक slice_पूर्णांकlv_bit_rm = SELECTOR_DISABLED;
	पूर्णांक chan_पूर्णांकlv_bit_rm = SELECTOR_DISABLED;
	/* Determine अगर address is in the MOT region. */
	bool mot_hit = in_region(&mot, addr);
	/* Calculate the number of symmetric regions enabled. */
	पूर्णांक sym_channels = hweight8(sym_chan_mask);

	/*
	 * The amount we need to shअगरt the asym base can be determined by the
	 * number of enabled symmetric channels.
	 * NOTE: This can only work because symmetric memory is not supposed
	 * to करो a 3-way पूर्णांकerleave.
	 */
	पूर्णांक sym_chan_shअगरt = sym_channels >> 1;

	/* Give up अगर address is out of range, or in MMIO gap */
	अगर (addr >= (1ul << PND_MAX_PHYS_BIT) ||
	   (addr >= top_lm && addr < _4GB) || addr >= top_hm) अणु
		snम_लिखो(msg, PND2_MSG_SIZE, "Error address 0x%llx is not DRAM", addr);
		वापस -EINVAL;
	पूर्ण

	/* Get a contiguous memory address (हटाओ the MMIO gap) */
	contig_addr = हटाओ_mmio_gap(addr);

	अगर (in_region(&as0, addr)) अणु
		*pmiidx = asym0.slice0_asym_channel_select;

		contig_base = हटाओ_mmio_gap(as0.base);
		contig_offset = contig_addr - contig_base;
		contig_base_adj = (contig_base >> sym_chan_shअगरt) *
						  ((chash.sym_slice0_channel_enabled >> (*pmiidx & 1)) & 1);
		contig_addr = contig_offset + ((sym_channels > 0) ? contig_base_adj : 0ull);
	पूर्ण अन्यथा अगर (in_region(&as1, addr)) अणु
		*pmiidx = 2u + asym1.slice1_asym_channel_select;

		contig_base = हटाओ_mmio_gap(as1.base);
		contig_offset = contig_addr - contig_base;
		contig_base_adj = (contig_base >> sym_chan_shअगरt) *
						  ((chash.sym_slice1_channel_enabled >> (*pmiidx & 1)) & 1);
		contig_addr = contig_offset + ((sym_channels > 0) ? contig_base_adj : 0ull);
	पूर्ण अन्यथा अगर (in_region(&as2, addr) && (asym_2way.asym_2way_पूर्णांकlv_mode == 0x3ul)) अणु
		bool channel1;

		mot_पूर्णांकlv_bit = MOT_CHAN_INTLV_BIT_1SLC_2CH;
		*pmiidx = (asym_2way.asym_2way_पूर्णांकlv_mode & 1) << 1;
		channel1 = mot_hit ? ((bool)((addr >> mot_पूर्णांकlv_bit) & 1)) :
			hash_by_mask(contig_addr, chan_hash_mask);
		*pmiidx |= (u32)channel1;

		contig_base = हटाओ_mmio_gap(as2.base);
		chan_पूर्णांकlv_bit_rm = mot_hit ? mot_पूर्णांकlv_bit : chan_selector;
		contig_offset = contig_addr - contig_base;
		हटाओ_addr_bit(&contig_offset, chan_पूर्णांकlv_bit_rm);
		contig_addr = (contig_base >> sym_chan_shअगरt) + contig_offset;
	पूर्ण अन्यथा अणु
		/* Otherwise we're in normal, boring symmetric mode. */
		*pmiidx = 0u;

		अगर (two_slices) अणु
			bool slice1;

			अगर (mot_hit) अणु
				slice_पूर्णांकlv_bit_rm = MOT_SLC_INTLV_BIT;
				slice1 = (addr >> MOT_SLC_INTLV_BIT) & 1;
			पूर्ण अन्यथा अणु
				slice_पूर्णांकlv_bit_rm = slice_selector;
				slice1 = hash_by_mask(addr, slice_hash_mask);
			पूर्ण

			*pmiidx = (u32)slice1 << 1;
		पूर्ण

		अगर (two_channels) अणु
			bool channel1;

			mot_पूर्णांकlv_bit = two_slices ? MOT_CHAN_INTLV_BIT_2SLC_2CH :
							MOT_CHAN_INTLV_BIT_1SLC_2CH;

			अगर (mot_hit) अणु
				chan_पूर्णांकlv_bit_rm = mot_पूर्णांकlv_bit;
				channel1 = (addr >> mot_पूर्णांकlv_bit) & 1;
			पूर्ण अन्यथा अणु
				chan_पूर्णांकlv_bit_rm = chan_selector;
				channel1 = hash_by_mask(contig_addr, chan_hash_mask);
			पूर्ण

			*pmiidx |= (u32)channel1;
		पूर्ण
	पूर्ण

	/* Remove the chan_selector bit first */
	हटाओ_addr_bit(&contig_addr, chan_पूर्णांकlv_bit_rm);
	/* Remove the slice bit (we हटाओ it second because it must be lower */
	हटाओ_addr_bit(&contig_addr, slice_पूर्णांकlv_bit_rm);
	*pmiaddr = contig_addr;

	वापस 0;
पूर्ण

/* Translate PMI address to memory (rank, row, bank, column) */
#घोषणा C(n) (0x10 | (n))	/* column */
#घोषणा B(n) (0x20 | (n))	/* bank */
#घोषणा R(n) (0x40 | (n))	/* row */
#घोषणा RS   (0x80)			/* rank */

/* addrdec values */
#घोषणा AMAP_1KB	0
#घोषणा AMAP_2KB	1
#घोषणा AMAP_4KB	2
#घोषणा AMAP_RSVD	3

/* dden values */
#घोषणा DEN_4Gb		0
#घोषणा DEN_8Gb		2

/* dwid values */
#घोषणा X8		0
#घोषणा X16		1

अटल काष्ठा dimm_geometry अणु
	u8	addrdec;
	u8	dden;
	u8	dwid;
	u8	rowbits, colbits;
	u16	bits[PMI_ADDRESS_WIDTH];
पूर्ण dimms[] = अणु
	अणु
		.addrdec = AMAP_1KB, .dden = DEN_4Gb, .dwid = X16,
		.rowbits = 15, .colbits = 10,
		.bits = अणु
			C(2),  C(3),  C(4),  C(5),  C(6),  B(0),  B(1),  B(2),  R(0),
			R(1),  R(2),  R(3),  R(4),  R(5),  R(6),  R(7),  R(8),  R(9),
			R(10), C(7),  C(8),  C(9),  R(11), RS,    R(12), R(13), R(14),
			0,     0,     0,     0
		पूर्ण
	पूर्ण,
	अणु
		.addrdec = AMAP_1KB, .dden = DEN_4Gb, .dwid = X8,
		.rowbits = 16, .colbits = 10,
		.bits = अणु
			C(2),  C(3),  C(4),  C(5),  C(6),  B(0),  B(1),  B(2),  R(0),
			R(1),  R(2),  R(3),  R(4),  R(5),  R(6),  R(7),  R(8),  R(9),
			R(10), C(7),  C(8),  C(9),  R(11), RS,    R(12), R(13), R(14),
			R(15), 0,     0,     0
		पूर्ण
	पूर्ण,
	अणु
		.addrdec = AMAP_1KB, .dden = DEN_8Gb, .dwid = X16,
		.rowbits = 16, .colbits = 10,
		.bits = अणु
			C(2),  C(3),  C(4),  C(5),  C(6),  B(0),  B(1),  B(2),  R(0),
			R(1),  R(2),  R(3),  R(4),  R(5),  R(6),  R(7),  R(8),  R(9),
			R(10), C(7),  C(8),  C(9),  R(11), RS,    R(12), R(13), R(14),
			R(15), 0,     0,     0
		पूर्ण
	पूर्ण,
	अणु
		.addrdec = AMAP_1KB, .dden = DEN_8Gb, .dwid = X8,
		.rowbits = 16, .colbits = 11,
		.bits = अणु
			C(2),  C(3),  C(4),  C(5),  C(6),  B(0),  B(1),  B(2),  R(0),
			R(1),  R(2),  R(3),  R(4),  R(5),  R(6),  R(7),  R(8),  R(9),
			R(10), C(7),  C(8),  C(9),  R(11), RS,    C(11), R(12), R(13),
			R(14), R(15), 0,     0
		पूर्ण
	पूर्ण,
	अणु
		.addrdec = AMAP_2KB, .dden = DEN_4Gb, .dwid = X16,
		.rowbits = 15, .colbits = 10,
		.bits = अणु
			C(2),  C(3),  C(4),  C(5),  C(6),  C(7),  B(0),  B(1),  B(2),
			R(0),  R(1),  R(2),  R(3),  R(4),  R(5),  R(6),  R(7),  R(8),
			R(9),  R(10), C(8),  C(9),  R(11), RS,    R(12), R(13), R(14),
			0,     0,     0,     0
		पूर्ण
	पूर्ण,
	अणु
		.addrdec = AMAP_2KB, .dden = DEN_4Gb, .dwid = X8,
		.rowbits = 16, .colbits = 10,
		.bits = अणु
			C(2),  C(3),  C(4),  C(5),  C(6),  C(7),  B(0),  B(1),  B(2),
			R(0),  R(1),  R(2),  R(3),  R(4),  R(5),  R(6),  R(7),  R(8),
			R(9),  R(10), C(8),  C(9),  R(11), RS,    R(12), R(13), R(14),
			R(15), 0,     0,     0
		पूर्ण
	पूर्ण,
	अणु
		.addrdec = AMAP_2KB, .dden = DEN_8Gb, .dwid = X16,
		.rowbits = 16, .colbits = 10,
		.bits = अणु
			C(2),  C(3),  C(4),  C(5),  C(6),  C(7),  B(0),  B(1),  B(2),
			R(0),  R(1),  R(2),  R(3),  R(4),  R(5),  R(6),  R(7),  R(8),
			R(9),  R(10), C(8),  C(9),  R(11), RS,    R(12), R(13), R(14),
			R(15), 0,     0,     0
		पूर्ण
	पूर्ण,
	अणु
		.addrdec = AMAP_2KB, .dden = DEN_8Gb, .dwid = X8,
		.rowbits = 16, .colbits = 11,
		.bits = अणु
			C(2),  C(3),  C(4),  C(5),  C(6),  C(7),  B(0),  B(1),  B(2),
			R(0),  R(1),  R(2),  R(3),  R(4),  R(5),  R(6),  R(7),  R(8),
			R(9),  R(10), C(8),  C(9),  R(11), RS,    C(11), R(12), R(13),
			R(14), R(15), 0,     0
		पूर्ण
	पूर्ण,
	अणु
		.addrdec = AMAP_4KB, .dden = DEN_4Gb, .dwid = X16,
		.rowbits = 15, .colbits = 10,
		.bits = अणु
			C(2),  C(3),  C(4),  C(5),  C(6),  C(7),  C(8),  B(0),  B(1),
			B(2),  R(0),  R(1),  R(2),  R(3),  R(4),  R(5),  R(6),  R(7),
			R(8),  R(9),  R(10), C(9),  R(11), RS,    R(12), R(13), R(14),
			0,     0,     0,     0
		पूर्ण
	पूर्ण,
	अणु
		.addrdec = AMAP_4KB, .dden = DEN_4Gb, .dwid = X8,
		.rowbits = 16, .colbits = 10,
		.bits = अणु
			C(2),  C(3),  C(4),  C(5),  C(6),  C(7),  C(8),  B(0),  B(1),
			B(2),  R(0),  R(1),  R(2),  R(3),  R(4),  R(5),  R(6),  R(7),
			R(8),  R(9),  R(10), C(9),  R(11), RS,    R(12), R(13), R(14),
			R(15), 0,     0,     0
		पूर्ण
	पूर्ण,
	अणु
		.addrdec = AMAP_4KB, .dden = DEN_8Gb, .dwid = X16,
		.rowbits = 16, .colbits = 10,
		.bits = अणु
			C(2),  C(3),  C(4),  C(5),  C(6),  C(7),  C(8),  B(0),  B(1),
			B(2),  R(0),  R(1),  R(2),  R(3),  R(4),  R(5),  R(6),  R(7),
			R(8),  R(9),  R(10), C(9),  R(11), RS,    R(12), R(13), R(14),
			R(15), 0,     0,     0
		पूर्ण
	पूर्ण,
	अणु
		.addrdec = AMAP_4KB, .dden = DEN_8Gb, .dwid = X8,
		.rowbits = 16, .colbits = 11,
		.bits = अणु
			C(2),  C(3),  C(4),  C(5),  C(6),  C(7),  C(8),  B(0),  B(1),
			B(2),  R(0),  R(1),  R(2),  R(3),  R(4),  R(5),  R(6),  R(7),
			R(8),  R(9),  R(10), C(9),  R(11), RS,    C(11), R(12), R(13),
			R(14), R(15), 0,     0
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक bank_hash(u64 pmiaddr, पूर्णांक idx, पूर्णांक shft)
अणु
	पूर्णांक bhash = 0;

	चयन (idx) अणु
	हाल 0:
		bhash ^= ((pmiaddr >> (12 + shft)) ^ (pmiaddr >> (9 + shft))) & 1;
		अवरोध;
	हाल 1:
		bhash ^= (((pmiaddr >> (10 + shft)) ^ (pmiaddr >> (8 + shft))) & 1) << 1;
		bhash ^= ((pmiaddr >> 22) & 1) << 1;
		अवरोध;
	हाल 2:
		bhash ^= (((pmiaddr >> (13 + shft)) ^ (pmiaddr >> (11 + shft))) & 1) << 2;
		अवरोध;
	पूर्ण

	वापस bhash;
पूर्ण

अटल पूर्णांक rank_hash(u64 pmiaddr)
अणु
	वापस ((pmiaddr >> 16) ^ (pmiaddr >> 10)) & 1;
पूर्ण

/* Second stage decode. Compute rank, bank, row & column. */
अटल पूर्णांक apl_pmi2mem(काष्ठा mem_ctl_info *mci, u64 pmiaddr, u32 pmiidx,
		       काष्ठा dram_addr *daddr, अक्षर *msg)
अणु
	काष्ठा d_cr_drp0 *cr_drp0 = &drp0[pmiidx];
	काष्ठा pnd2_pvt *pvt = mci->pvt_info;
	पूर्णांक g = pvt->dimm_geom[pmiidx];
	काष्ठा dimm_geometry *d = &dimms[g];
	पूर्णांक column = 0, bank = 0, row = 0, rank = 0;
	पूर्णांक i, idx, type, skiprs = 0;

	क्रम (i = 0; i < PMI_ADDRESS_WIDTH; i++) अणु
		पूर्णांक	bit = (pmiaddr >> i) & 1;

		अगर (i + skiprs >= PMI_ADDRESS_WIDTH) अणु
			snम_लिखो(msg, PND2_MSG_SIZE, "Bad dimm_geometry[] table\n");
			वापस -EINVAL;
		पूर्ण

		type = d->bits[i + skiprs] & ~0xf;
		idx = d->bits[i + skiprs] & 0xf;

		/*
		 * On single rank DIMMs ignore the rank select bit
		 * and shअगरt reमुख्यder of "bits[]" करोwn one place.
		 */
		अगर (type == RS && (cr_drp0->rken0 + cr_drp0->rken1) == 1) अणु
			skiprs = 1;
			type = d->bits[i + skiprs] & ~0xf;
			idx = d->bits[i + skiprs] & 0xf;
		पूर्ण

		चयन (type) अणु
		हाल C(0):
			column |= (bit << idx);
			अवरोध;
		हाल B(0):
			bank |= (bit << idx);
			अगर (cr_drp0->bahen)
				bank ^= bank_hash(pmiaddr, idx, d->addrdec);
			अवरोध;
		हाल R(0):
			row |= (bit << idx);
			अवरोध;
		हाल RS:
			rank = bit;
			अगर (cr_drp0->rsien)
				rank ^= rank_hash(pmiaddr);
			अवरोध;
		शेष:
			अगर (bit) अणु
				snम_लिखो(msg, PND2_MSG_SIZE, "Bad translation\n");
				वापस -EINVAL;
			पूर्ण
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	daddr->col = column;
	daddr->bank = bank;
	daddr->row = row;
	daddr->rank = rank;
	daddr->dimm = 0;

	वापस 0;
पूर्ण

/* Pluck bit "in" from pmiaddr and वापस value shअगरted to bit "out" */
#घोषणा dnv_get_bit(pmi, in, out) ((पूर्णांक)(((pmi) >> (in)) & 1u) << (out))

अटल पूर्णांक dnv_pmi2mem(काष्ठा mem_ctl_info *mci, u64 pmiaddr, u32 pmiidx,
					   काष्ठा dram_addr *daddr, अक्षर *msg)
अणु
	/* Rank 0 or 1 */
	daddr->rank = dnv_get_bit(pmiaddr, dmap[pmiidx].rs0 + 13, 0);
	/* Rank 2 or 3 */
	daddr->rank |= dnv_get_bit(pmiaddr, dmap[pmiidx].rs1 + 13, 1);

	/*
	 * Normally ranks 0,1 are DIMM0, and 2,3 are DIMM1, but we
	 * flip them अगर DIMM1 is larger than DIMM0.
	 */
	daddr->dimm = (daddr->rank >= 2) ^ drp[pmiidx].dimmflip;

	daddr->bank = dnv_get_bit(pmiaddr, dmap[pmiidx].ba0 + 6, 0);
	daddr->bank |= dnv_get_bit(pmiaddr, dmap[pmiidx].ba1 + 6, 1);
	daddr->bank |= dnv_get_bit(pmiaddr, dmap[pmiidx].bg0 + 6, 2);
	अगर (dsch.ddr4en)
		daddr->bank |= dnv_get_bit(pmiaddr, dmap[pmiidx].bg1 + 6, 3);
	अगर (dmap1[pmiidx].bxor) अणु
		अगर (dsch.ddr4en) अणु
			daddr->bank ^= dnv_get_bit(pmiaddr, dmap3[pmiidx].row6 + 6, 0);
			daddr->bank ^= dnv_get_bit(pmiaddr, dmap3[pmiidx].row7 + 6, 1);
			अगर (dsch.chan_width == 0)
				/* 64/72 bit dram channel width */
				daddr->bank ^= dnv_get_bit(pmiaddr, dmap5[pmiidx].ca3 + 6, 2);
			अन्यथा
				/* 32/40 bit dram channel width */
				daddr->bank ^= dnv_get_bit(pmiaddr, dmap5[pmiidx].ca4 + 6, 2);
			daddr->bank ^= dnv_get_bit(pmiaddr, dmap2[pmiidx].row2 + 6, 3);
		पूर्ण अन्यथा अणु
			daddr->bank ^= dnv_get_bit(pmiaddr, dmap2[pmiidx].row2 + 6, 0);
			daddr->bank ^= dnv_get_bit(pmiaddr, dmap3[pmiidx].row6 + 6, 1);
			अगर (dsch.chan_width == 0)
				daddr->bank ^= dnv_get_bit(pmiaddr, dmap5[pmiidx].ca3 + 6, 2);
			अन्यथा
				daddr->bank ^= dnv_get_bit(pmiaddr, dmap5[pmiidx].ca4 + 6, 2);
		पूर्ण
	पूर्ण

	daddr->row = dnv_get_bit(pmiaddr, dmap2[pmiidx].row0 + 6, 0);
	daddr->row |= dnv_get_bit(pmiaddr, dmap2[pmiidx].row1 + 6, 1);
	daddr->row |= dnv_get_bit(pmiaddr, dmap2[pmiidx].row2 + 6, 2);
	daddr->row |= dnv_get_bit(pmiaddr, dmap2[pmiidx].row3 + 6, 3);
	daddr->row |= dnv_get_bit(pmiaddr, dmap2[pmiidx].row4 + 6, 4);
	daddr->row |= dnv_get_bit(pmiaddr, dmap2[pmiidx].row5 + 6, 5);
	daddr->row |= dnv_get_bit(pmiaddr, dmap3[pmiidx].row6 + 6, 6);
	daddr->row |= dnv_get_bit(pmiaddr, dmap3[pmiidx].row7 + 6, 7);
	daddr->row |= dnv_get_bit(pmiaddr, dmap3[pmiidx].row8 + 6, 8);
	daddr->row |= dnv_get_bit(pmiaddr, dmap3[pmiidx].row9 + 6, 9);
	daddr->row |= dnv_get_bit(pmiaddr, dmap3[pmiidx].row10 + 6, 10);
	daddr->row |= dnv_get_bit(pmiaddr, dmap3[pmiidx].row11 + 6, 11);
	daddr->row |= dnv_get_bit(pmiaddr, dmap4[pmiidx].row12 + 6, 12);
	daddr->row |= dnv_get_bit(pmiaddr, dmap4[pmiidx].row13 + 6, 13);
	अगर (dmap4[pmiidx].row14 != 31)
		daddr->row |= dnv_get_bit(pmiaddr, dmap4[pmiidx].row14 + 6, 14);
	अगर (dmap4[pmiidx].row15 != 31)
		daddr->row |= dnv_get_bit(pmiaddr, dmap4[pmiidx].row15 + 6, 15);
	अगर (dmap4[pmiidx].row16 != 31)
		daddr->row |= dnv_get_bit(pmiaddr, dmap4[pmiidx].row16 + 6, 16);
	अगर (dmap4[pmiidx].row17 != 31)
		daddr->row |= dnv_get_bit(pmiaddr, dmap4[pmiidx].row17 + 6, 17);

	daddr->col = dnv_get_bit(pmiaddr, dmap5[pmiidx].ca3 + 6, 3);
	daddr->col |= dnv_get_bit(pmiaddr, dmap5[pmiidx].ca4 + 6, 4);
	daddr->col |= dnv_get_bit(pmiaddr, dmap5[pmiidx].ca5 + 6, 5);
	daddr->col |= dnv_get_bit(pmiaddr, dmap5[pmiidx].ca6 + 6, 6);
	daddr->col |= dnv_get_bit(pmiaddr, dmap5[pmiidx].ca7 + 6, 7);
	daddr->col |= dnv_get_bit(pmiaddr, dmap5[pmiidx].ca8 + 6, 8);
	daddr->col |= dnv_get_bit(pmiaddr, dmap5[pmiidx].ca9 + 6, 9);
	अगर (!dsch.ddr4en && dmap1[pmiidx].ca11 != 0x3f)
		daddr->col |= dnv_get_bit(pmiaddr, dmap1[pmiidx].ca11 + 13, 11);

	वापस 0;
पूर्ण

अटल पूर्णांक check_channel(पूर्णांक ch)
अणु
	अगर (drp0[ch].dramtype != 0) अणु
		pnd2_prपूर्णांकk(KERN_INFO, "Unsupported DIMM in channel %d\n", ch);
		वापस 1;
	पूर्ण अन्यथा अगर (drp0[ch].eccen == 0) अणु
		pnd2_prपूर्णांकk(KERN_INFO, "ECC disabled on channel %d\n", ch);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक apl_check_ecc_active(व्योम)
अणु
	पूर्णांक	i, ret = 0;

	/* Check dramtype and ECC mode क्रम each present DIMM */
	क्रम (i = 0; i < APL_NUM_CHANNELS; i++)
		अगर (chan_mask & BIT(i))
			ret += check_channel(i);
	वापस ret ? -EINVAL : 0;
पूर्ण

#घोषणा DIMMS_PRESENT(d) ((d)->rken0 + (d)->rken1 + (d)->rken2 + (d)->rken3)

अटल पूर्णांक check_unit(पूर्णांक ch)
अणु
	काष्ठा d_cr_drp *d = &drp[ch];

	अगर (DIMMS_PRESENT(d) && !ecc_ctrl[ch].eccen) अणु
		pnd2_prपूर्णांकk(KERN_INFO, "ECC disabled on channel %d\n", ch);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dnv_check_ecc_active(व्योम)
अणु
	पूर्णांक	i, ret = 0;

	क्रम (i = 0; i < DNV_NUM_CHANNELS; i++)
		ret += check_unit(i);
	वापस ret ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक get_memory_error_data(काष्ठा mem_ctl_info *mci, u64 addr,
								 काष्ठा dram_addr *daddr, अक्षर *msg)
अणु
	u64	pmiaddr;
	u32	pmiidx;
	पूर्णांक	ret;

	ret = sys2pmi(addr, &pmiidx, &pmiaddr, msg);
	अगर (ret)
		वापस ret;

	pmiaddr >>= ops->pmiaddr_shअगरt;
	/* pmi channel idx to dimm channel idx */
	pmiidx >>= ops->pmiidx_shअगरt;
	daddr->chan = pmiidx;

	ret = ops->pmi2mem(mci, pmiaddr, pmiidx, daddr, msg);
	अगर (ret)
		वापस ret;

	edac_dbg(0, "SysAddr=%llx PmiAddr=%llx Channel=%d DIMM=%d Rank=%d Bank=%d Row=%d Column=%d\n",
			 addr, pmiaddr, daddr->chan, daddr->dimm, daddr->rank, daddr->bank, daddr->row, daddr->col);

	वापस 0;
पूर्ण

अटल व्योम pnd2_mce_output_error(काष्ठा mem_ctl_info *mci, स्थिर काष्ठा mce *m,
				  काष्ठा dram_addr *daddr)
अणु
	क्रमागत hw_event_mc_err_type tp_event;
	अक्षर *optype, msg[PND2_MSG_SIZE];
	bool ripv = m->mcgstatus & MCG_STATUS_RIPV;
	bool overflow = m->status & MCI_STATUS_OVER;
	bool uc_err = m->status & MCI_STATUS_UC;
	bool recov = m->status & MCI_STATUS_S;
	u32 core_err_cnt = GET_BITFIELD(m->status, 38, 52);
	u32 mscod = GET_BITFIELD(m->status, 16, 31);
	u32 errcode = GET_BITFIELD(m->status, 0, 15);
	u32 optypक्रमागत = GET_BITFIELD(m->status, 4, 6);
	पूर्णांक rc;

	tp_event = uc_err ? (ripv ? HW_EVENT_ERR_UNCORRECTED : HW_EVENT_ERR_FATAL) :
						 HW_EVENT_ERR_CORRECTED;

	/*
	 * According with Table 15-9 of the Intel Architecture spec vol 3A,
	 * memory errors should fit in this mask:
	 *	000f 0000 1mmm cccc (binary)
	 * where:
	 *	f = Correction Report Filtering Bit. If 1, subsequent errors
	 *	    won't be shown
	 *	mmm = error type
	 *	cccc = channel
	 * If the mask करोesn't match, report an error to the parsing logic
	 */
	अगर (!((errcode & 0xef80) == 0x80)) अणु
		optype = "Can't parse: it is not a mem";
	पूर्ण अन्यथा अणु
		चयन (optypक्रमागत) अणु
		हाल 0:
			optype = "generic undef request error";
			अवरोध;
		हाल 1:
			optype = "memory read error";
			अवरोध;
		हाल 2:
			optype = "memory write error";
			अवरोध;
		हाल 3:
			optype = "addr/cmd error";
			अवरोध;
		हाल 4:
			optype = "memory scrubbing error";
			अवरोध;
		शेष:
			optype = "reserved";
			अवरोध;
		पूर्ण
	पूर्ण

	/* Only decode errors with an valid address (ADDRV) */
	अगर (!(m->status & MCI_STATUS_ADDRV))
		वापस;

	rc = get_memory_error_data(mci, m->addr, daddr, msg);
	अगर (rc)
		जाओ address_error;

	snम_लिखो(msg, माप(msg),
		 "%s%s err_code:%04x:%04x channel:%d DIMM:%d rank:%d row:%d bank:%d col:%d",
		 overflow ? " OVERFLOW" : "", (uc_err && recov) ? " recoverable" : "", mscod,
		 errcode, daddr->chan, daddr->dimm, daddr->rank, daddr->row, daddr->bank, daddr->col);

	edac_dbg(0, "%s\n", msg);

	/* Call the helper to output message */
	edac_mc_handle_error(tp_event, mci, core_err_cnt, m->addr >> PAGE_SHIFT,
						 m->addr & ~PAGE_MASK, 0, daddr->chan, daddr->dimm, -1, optype, msg);

	वापस;

address_error:
	edac_mc_handle_error(tp_event, mci, core_err_cnt, 0, 0, 0, -1, -1, -1, msg, "");
पूर्ण

अटल व्योम apl_get_dimm_config(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा pnd2_pvt	*pvt = mci->pvt_info;
	काष्ठा dimm_info *dimm;
	काष्ठा d_cr_drp0 *d;
	u64	capacity;
	पूर्णांक	i, g;

	क्रम (i = 0; i < APL_NUM_CHANNELS; i++) अणु
		अगर (!(chan_mask & BIT(i)))
			जारी;

		dimm = edac_get_dimm(mci, i, 0, 0);
		अगर (!dimm) अणु
			edac_dbg(0, "No allocated DIMM for channel %d\n", i);
			जारी;
		पूर्ण

		d = &drp0[i];
		क्रम (g = 0; g < ARRAY_SIZE(dimms); g++)
			अगर (dimms[g].addrdec == d->addrdec &&
			    dimms[g].dden == d->dden &&
			    dimms[g].dwid == d->dwid)
				अवरोध;

		अगर (g == ARRAY_SIZE(dimms)) अणु
			edac_dbg(0, "Channel %d: unrecognized DIMM\n", i);
			जारी;
		पूर्ण

		pvt->dimm_geom[i] = g;
		capacity = (d->rken0 + d->rken1) * 8 * (1ul << dimms[g].rowbits) *
				   (1ul << dimms[g].colbits);
		edac_dbg(0, "Channel %d: %lld MByte DIMM\n", i, capacity >> (20 - 3));
		dimm->nr_pages = MiB_TO_PAGES(capacity >> (20 - 3));
		dimm->grain = 32;
		dimm->dtype = (d->dwid == 0) ? DEV_X8 : DEV_X16;
		dimm->mtype = MEM_DDR3;
		dimm->edac_mode = EDAC_SECDED;
		snम_लिखो(dimm->label, माप(dimm->label), "Slice#%d_Chan#%d", i / 2, i % 2);
	पूर्ण
पूर्ण

अटल स्थिर पूर्णांक dnv_dtypes[] = अणु
	DEV_X8, DEV_X4, DEV_X16, DEV_UNKNOWN
पूर्ण;

अटल व्योम dnv_get_dimm_config(काष्ठा mem_ctl_info *mci)
अणु
	पूर्णांक	i, j, ranks_of_dimm[DNV_MAX_DIMMS], banks, rowbits, colbits, memtype;
	काष्ठा dimm_info *dimm;
	काष्ठा d_cr_drp *d;
	u64	capacity;

	अगर (dsch.ddr4en) अणु
		memtype = MEM_DDR4;
		banks = 16;
		colbits = 10;
	पूर्ण अन्यथा अणु
		memtype = MEM_DDR3;
		banks = 8;
	पूर्ण

	क्रम (i = 0; i < DNV_NUM_CHANNELS; i++) अणु
		अगर (dmap4[i].row14 == 31)
			rowbits = 14;
		अन्यथा अगर (dmap4[i].row15 == 31)
			rowbits = 15;
		अन्यथा अगर (dmap4[i].row16 == 31)
			rowbits = 16;
		अन्यथा अगर (dmap4[i].row17 == 31)
			rowbits = 17;
		अन्यथा
			rowbits = 18;

		अगर (memtype == MEM_DDR3) अणु
			अगर (dmap1[i].ca11 != 0x3f)
				colbits = 12;
			अन्यथा
				colbits = 10;
		पूर्ण

		d = &drp[i];
		/* DIMM0 is present अगर rank0 and/or rank1 is enabled */
		ranks_of_dimm[0] = d->rken0 + d->rken1;
		/* DIMM1 is present अगर rank2 and/or rank3 is enabled */
		ranks_of_dimm[1] = d->rken2 + d->rken3;

		क्रम (j = 0; j < DNV_MAX_DIMMS; j++) अणु
			अगर (!ranks_of_dimm[j])
				जारी;

			dimm = edac_get_dimm(mci, i, j, 0);
			अगर (!dimm) अणु
				edac_dbg(0, "No allocated DIMM for channel %d DIMM %d\n", i, j);
				जारी;
			पूर्ण

			capacity = ranks_of_dimm[j] * banks * (1ul << rowbits) * (1ul << colbits);
			edac_dbg(0, "Channel %d DIMM %d: %lld MByte DIMM\n", i, j, capacity >> (20 - 3));
			dimm->nr_pages = MiB_TO_PAGES(capacity >> (20 - 3));
			dimm->grain = 32;
			dimm->dtype = dnv_dtypes[j ? d->dimmdwid0 : d->dimmdwid1];
			dimm->mtype = memtype;
			dimm->edac_mode = EDAC_SECDED;
			snम_लिखो(dimm->label, माप(dimm->label), "Chan#%d_DIMM#%d", i, j);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pnd2_रेजिस्टर_mci(काष्ठा mem_ctl_info **ppmci)
अणु
	काष्ठा edac_mc_layer layers[2];
	काष्ठा mem_ctl_info *mci;
	काष्ठा pnd2_pvt *pvt;
	पूर्णांक rc;

	rc = ops->check_ecc();
	अगर (rc < 0)
		वापस rc;

	/* Allocate a new MC control काष्ठाure */
	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = ops->channels;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_SLOT;
	layers[1].size = ops->dimms_per_channel;
	layers[1].is_virt_csrow = true;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, माप(*pvt));
	अगर (!mci)
		वापस -ENOMEM;

	pvt = mci->pvt_info;
	स_रखो(pvt, 0, माप(*pvt));

	mci->mod_name = EDAC_MOD_STR;
	mci->dev_name = ops->name;
	mci->ctl_name = "Pondicherry2";

	/* Get dimm basic config and the memory layout */
	ops->get_dimm_config(mci);

	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");
		edac_mc_मुक्त(mci);
		वापस -EINVAL;
	पूर्ण

	*ppmci = mci;

	वापस 0;
पूर्ण

अटल व्योम pnd2_unरेजिस्टर_mci(काष्ठा mem_ctl_info *mci)
अणु
	अगर (unlikely(!mci || !mci->pvt_info)) अणु
		pnd2_prपूर्णांकk(KERN_ERR, "Couldn't find mci handler\n");
		वापस;
	पूर्ण

	/* Remove MC sysfs nodes */
	edac_mc_del_mc(शून्य);
	edac_dbg(1, "%s: free mci struct\n", mci->ctl_name);
	edac_mc_मुक्त(mci);
पूर्ण

/*
 * Callback function रेजिस्टरed with core kernel mce code.
 * Called once क्रम each logged error.
 */
अटल पूर्णांक pnd2_mce_check_error(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा mce *mce = (काष्ठा mce *)data;
	काष्ठा mem_ctl_info *mci;
	काष्ठा dram_addr daddr;
	अक्षर *type;

	mci = pnd2_mci;
	अगर (!mci || (mce->kflags & MCE_HANDLED_CEC))
		वापस NOTIFY_DONE;

	/*
	 * Just let mcelog handle it अगर the error is
	 * outside the memory controller. A memory error
	 * is indicated by bit 7 = 1 and bits = 8-11,13-15 = 0.
	 * bit 12 has an special meaning.
	 */
	अगर ((mce->status & 0xefff) >> 7 != 1)
		वापस NOTIFY_DONE;

	अगर (mce->mcgstatus & MCG_STATUS_MCIP)
		type = "Exception";
	अन्यथा
		type = "Event";

	pnd2_mc_prपूर्णांकk(mci, KERN_INFO, "HANDLING MCE MEMORY ERROR\n");
	pnd2_mc_prपूर्णांकk(mci, KERN_INFO, "CPU %u: Machine Check %s: %llx Bank %u: %llx\n",
				   mce->extcpu, type, mce->mcgstatus, mce->bank, mce->status);
	pnd2_mc_prपूर्णांकk(mci, KERN_INFO, "TSC %llx ", mce->tsc);
	pnd2_mc_prपूर्णांकk(mci, KERN_INFO, "ADDR %llx ", mce->addr);
	pnd2_mc_prपूर्णांकk(mci, KERN_INFO, "MISC %llx ", mce->misc);
	pnd2_mc_prपूर्णांकk(mci, KERN_INFO, "PROCESSOR %u:%x TIME %llu SOCKET %u APIC %x\n",
				   mce->cpuvenकरोr, mce->cpuid, mce->समय, mce->socketid, mce->apicid);

	pnd2_mce_output_error(mci, mce, &daddr);

	/* Advice mcelog that the error were handled */
	mce->kflags |= MCE_HANDLED_EDAC;
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block pnd2_mce_dec = अणु
	.notअगरier_call	= pnd2_mce_check_error,
	.priority	= MCE_PRIO_EDAC,
पूर्ण;

#अगर_घोषित CONFIG_EDAC_DEBUG
/*
 * Write an address to this file to exercise the address decode
 * logic in this driver.
 */
अटल u64 pnd2_fake_addr;
#घोषणा PND2_BLOB_SIZE 1024
अटल अक्षर pnd2_result[PND2_BLOB_SIZE];
अटल काष्ठा dentry *pnd2_test;
अटल काष्ठा debugfs_blob_wrapper pnd2_blob = अणु
	.data = pnd2_result,
	.size = 0
पूर्ण;

अटल पूर्णांक debugfs_u64_set(व्योम *data, u64 val)
अणु
	काष्ठा dram_addr daddr;
	काष्ठा mce m;

	*(u64 *)data = val;
	m.mcgstatus = 0;
	/* ADDRV + MemRd + Unknown channel */
	m.status = MCI_STATUS_ADDRV + 0x9f;
	m.addr = val;
	pnd2_mce_output_error(pnd2_mci, &m, &daddr);
	snम_लिखो(pnd2_blob.data, PND2_BLOB_SIZE,
			 "SysAddr=%llx Channel=%d DIMM=%d Rank=%d Bank=%d Row=%d Column=%d\n",
			 m.addr, daddr.chan, daddr.dimm, daddr.rank, daddr.bank, daddr.row, daddr.col);
	pnd2_blob.size = म_माप(pnd2_blob.data);

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_u64_wo, शून्य, debugfs_u64_set, "%llu\n");

अटल व्योम setup_pnd2_debug(व्योम)
अणु
	pnd2_test = edac_debugfs_create_dir("pnd2_test");
	edac_debugfs_create_file("pnd2_debug_addr", 0200, pnd2_test,
							 &pnd2_fake_addr, &fops_u64_wo);
	debugfs_create_blob("pnd2_debug_results", 0400, pnd2_test, &pnd2_blob);
पूर्ण

अटल व्योम tearकरोwn_pnd2_debug(व्योम)
अणु
	debugfs_हटाओ_recursive(pnd2_test);
पूर्ण
#अन्यथा
अटल व्योम setup_pnd2_debug(व्योम)	अणुपूर्ण
अटल व्योम tearकरोwn_pnd2_debug(व्योम)	अणुपूर्ण
#पूर्ण_अगर /* CONFIG_EDAC_DEBUG */


अटल पूर्णांक pnd2_probe(व्योम)
अणु
	पूर्णांक rc;

	edac_dbg(2, "\n");
	rc = get_रेजिस्टरs();
	अगर (rc)
		वापस rc;

	वापस pnd2_रेजिस्टर_mci(&pnd2_mci);
पूर्ण

अटल व्योम pnd2_हटाओ(व्योम)
अणु
	edac_dbg(0, "\n");
	pnd2_unरेजिस्टर_mci(pnd2_mci);
पूर्ण

अटल काष्ठा dunit_ops apl_ops = अणु
		.name			= "pnd2/apl",
		.type			= APL,
		.pmiaddr_shअगरt		= LOG2_PMI_ADDR_GRANULARITY,
		.pmiidx_shअगरt		= 0,
		.channels		= APL_NUM_CHANNELS,
		.dimms_per_channel	= 1,
		.rd_reg			= apl_rd_reg,
		.get_रेजिस्टरs		= apl_get_रेजिस्टरs,
		.check_ecc		= apl_check_ecc_active,
		.mk_region		= apl_mk_region,
		.get_dimm_config	= apl_get_dimm_config,
		.pmi2mem		= apl_pmi2mem,
पूर्ण;

अटल काष्ठा dunit_ops dnv_ops = अणु
		.name			= "pnd2/dnv",
		.type			= DNV,
		.pmiaddr_shअगरt		= 0,
		.pmiidx_shअगरt		= 1,
		.channels		= DNV_NUM_CHANNELS,
		.dimms_per_channel	= 2,
		.rd_reg			= dnv_rd_reg,
		.get_रेजिस्टरs		= dnv_get_रेजिस्टरs,
		.check_ecc		= dnv_check_ecc_active,
		.mk_region		= dnv_mk_region,
		.get_dimm_config	= dnv_get_dimm_config,
		.pmi2mem		= dnv_pmi2mem,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id pnd2_cpuids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT,	&apl_ops),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_GOLDMONT_D,	&dnv_ops),
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, pnd2_cpuids);

अटल पूर्णांक __init pnd2_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	स्थिर अक्षर *owner;
	पूर्णांक rc;

	edac_dbg(2, "\n");

	owner = edac_get_owner();
	अगर (owner && म_भेदन(owner, EDAC_MOD_STR, माप(EDAC_MOD_STR)))
		वापस -EBUSY;

	id = x86_match_cpu(pnd2_cpuids);
	अगर (!id)
		वापस -ENODEV;

	ops = (काष्ठा dunit_ops *)id->driver_data;

	अगर (ops->type == APL) अणु
		p2sb_bus = pci_find_bus(0, 0);
		अगर (!p2sb_bus)
			वापस -ENODEV;
	पूर्ण

	/* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
	opstate_init();

	rc = pnd2_probe();
	अगर (rc < 0) अणु
		pnd2_prपूर्णांकk(KERN_ERR, "Failed to register device with error %d.\n", rc);
		वापस rc;
	पूर्ण

	अगर (!pnd2_mci)
		वापस -ENODEV;

	mce_रेजिस्टर_decode_chain(&pnd2_mce_dec);
	setup_pnd2_debug();

	वापस 0;
पूर्ण

अटल व्योम __निकास pnd2_निकास(व्योम)
अणु
	edac_dbg(2, "\n");
	tearकरोwn_pnd2_debug();
	mce_unरेजिस्टर_decode_chain(&pnd2_mce_dec);
	pnd2_हटाओ();
पूर्ण

module_init(pnd2_init);
module_निकास(pnd2_निकास);

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Tony Luck");
MODULE_DESCRIPTION("MC Driver for Intel SoC using Pondicherry memory controller");
