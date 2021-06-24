<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Intel(R) 10nm server memory controller.
 * Copyright (c) 2019, Intel Corporation.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/mce.h>
#समावेश "edac_module.h"
#समावेश "skx_common.h"

#घोषणा I10NM_REVISION	"v0.0.4"
#घोषणा EDAC_MOD_STR	"i10nm_edac"

/* Debug macros */
#घोषणा i10nm_prपूर्णांकk(level, fmt, arg...)	\
	edac_prपूर्णांकk(level, "i10nm", fmt, ##arg)

#घोषणा I10NM_GET_SCK_BAR(d, reg)	\
	pci_पढ़ो_config_dword((d)->uracu, 0xd0, &(reg))
#घोषणा I10NM_GET_IMC_BAR(d, i, reg)	\
	pci_पढ़ो_config_dword((d)->uracu, 0xd8 + (i) * 4, &(reg))
#घोषणा I10NM_GET_DIMMMTR(m, i, j)	\
	पढ़ोl((m)->mbase + 0x2080c + (i) * (m)->chan_mmio_sz + (j) * 4)
#घोषणा I10NM_GET_MCDDRTCFG(m, i, j)	\
	पढ़ोl((m)->mbase + 0x20970 + (i) * (m)->chan_mmio_sz + (j) * 4)
#घोषणा I10NM_GET_MCMTR(m, i)		\
	पढ़ोl((m)->mbase + 0x20ef8 + (i) * (m)->chan_mmio_sz)
#घोषणा I10NM_GET_AMAP(m, i)		\
	पढ़ोl((m)->mbase + 0x20814 + (i) * (m)->chan_mmio_sz)

#घोषणा I10NM_GET_SCK_MMIO_BASE(reg)	(GET_BITFIELD(reg, 0, 28) << 23)
#घोषणा I10NM_GET_IMC_MMIO_OFFSET(reg)	(GET_BITFIELD(reg, 0, 10) << 12)
#घोषणा I10NM_GET_IMC_MMIO_SIZE(reg)	((GET_BITFIELD(reg, 13, 23) - \
					 GET_BITFIELD(reg, 0, 10) + 1) << 12)

अटल काष्ठा list_head *i10nm_edac_list;

अटल काष्ठा pci_dev *pci_get_dev_wrapper(पूर्णांक करोm, अचिन्हित पूर्णांक bus,
					   अचिन्हित पूर्णांक dev, अचिन्हित पूर्णांक fun)
अणु
	काष्ठा pci_dev *pdev;

	pdev = pci_get_करोमुख्य_bus_and_slot(करोm, bus, PCI_DEVFN(dev, fun));
	अगर (!pdev) अणु
		edac_dbg(2, "No device %02x:%02x.%x\n",
			 bus, dev, fun);
		वापस शून्य;
	पूर्ण

	अगर (unlikely(pci_enable_device(pdev) < 0)) अणु
		edac_dbg(2, "Failed to enable device %02x:%02x.%x\n",
			 bus, dev, fun);
		वापस शून्य;
	पूर्ण

	pci_dev_get(pdev);

	वापस pdev;
पूर्ण

अटल पूर्णांक i10nm_get_all_munits(व्योम)
अणु
	काष्ठा pci_dev *mdev;
	व्योम __iomem *mbase;
	अचिन्हित दीर्घ size;
	काष्ठा skx_dev *d;
	पूर्णांक i, j = 0;
	u32 reg, off;
	u64 base;

	list_क्रम_each_entry(d, i10nm_edac_list, list) अणु
		d->util_all = pci_get_dev_wrapper(d->seg, d->bus[1], 29, 1);
		अगर (!d->util_all)
			वापस -ENODEV;

		d->uracu = pci_get_dev_wrapper(d->seg, d->bus[0], 0, 1);
		अगर (!d->uracu)
			वापस -ENODEV;

		अगर (I10NM_GET_SCK_BAR(d, reg)) अणु
			i10nm_prपूर्णांकk(KERN_ERR, "Failed to socket bar\n");
			वापस -ENODEV;
		पूर्ण

		base = I10NM_GET_SCK_MMIO_BASE(reg);
		edac_dbg(2, "socket%d mmio base 0x%llx (reg 0x%x)\n",
			 j++, base, reg);

		क्रम (i = 0; i < I10NM_NUM_IMC; i++) अणु
			mdev = pci_get_dev_wrapper(d->seg, d->bus[0],
						   12 + i, 0);
			अगर (i == 0 && !mdev) अणु
				i10nm_prपूर्णांकk(KERN_ERR, "No IMC found\n");
				वापस -ENODEV;
			पूर्ण
			अगर (!mdev)
				जारी;

			d->imc[i].mdev = mdev;

			अगर (I10NM_GET_IMC_BAR(d, i, reg)) अणु
				i10nm_prपूर्णांकk(KERN_ERR, "Failed to get mc bar\n");
				वापस -ENODEV;
			पूर्ण

			off  = I10NM_GET_IMC_MMIO_OFFSET(reg);
			size = I10NM_GET_IMC_MMIO_SIZE(reg);
			edac_dbg(2, "mc%d mmio base 0x%llx size 0x%lx (reg 0x%x)\n",
				 i, base + off, size, reg);

			mbase = ioremap(base + off, size);
			अगर (!mbase) अणु
				i10nm_prपूर्णांकk(KERN_ERR, "Failed to ioremap 0x%llx\n",
					     base + off);
				वापस -ENODEV;
			पूर्ण

			d->imc[i].mbase = mbase;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा res_config i10nm_cfg0 = अणु
	.type			= I10NM,
	.decs_did		= 0x3452,
	.busno_cfg_offset	= 0xcc,
	.ddr_chan_mmio_sz	= 0x4000,
पूर्ण;

अटल काष्ठा res_config i10nm_cfg1 = अणु
	.type			= I10NM,
	.decs_did		= 0x3452,
	.busno_cfg_offset	= 0xd0,
	.ddr_chan_mmio_sz	= 0x4000,
पूर्ण;

अटल काष्ठा res_config spr_cfg = अणु
	.type			= SPR,
	.decs_did		= 0x3252,
	.busno_cfg_offset	= 0xd0,
	.ddr_chan_mmio_sz	= 0x8000,
	.support_ddr5		= true,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id i10nm_cpuids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(ATOM_TREMONT_D,	X86_STEPPINGS(0x0, 0x3), &i10nm_cfg0),
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(ATOM_TREMONT_D,	X86_STEPPINGS(0x4, 0xf), &i10nm_cfg1),
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(ICELAKE_X,		X86_STEPPINGS(0x0, 0x3), &i10nm_cfg0),
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(ICELAKE_X,		X86_STEPPINGS(0x4, 0xf), &i10nm_cfg1),
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(ICELAKE_D,		X86_STEPPINGS(0x0, 0xf), &i10nm_cfg1),
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(SAPPHIRERAPIDS_X,	X86_STEPPINGS(0x0, 0xf), &spr_cfg),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, i10nm_cpuids);

अटल bool i10nm_check_ecc(काष्ठा skx_imc *imc, पूर्णांक chan)
अणु
	u32 mcmtr;

	mcmtr = I10NM_GET_MCMTR(imc, chan);
	edac_dbg(1, "ch%d mcmtr reg %x\n", chan, mcmtr);

	वापस !!GET_BITFIELD(mcmtr, 2, 2);
पूर्ण

अटल पूर्णांक i10nm_get_dimm_config(काष्ठा mem_ctl_info *mci,
				 काष्ठा res_config *cfg)
अणु
	काष्ठा skx_pvt *pvt = mci->pvt_info;
	काष्ठा skx_imc *imc = pvt->imc;
	u32 mtr, amap, mcddrtcfg;
	काष्ठा dimm_info *dimm;
	पूर्णांक i, j, ndimms;

	क्रम (i = 0; i < I10NM_NUM_CHANNELS; i++) अणु
		अगर (!imc->mbase)
			जारी;

		ndimms = 0;
		amap = I10NM_GET_AMAP(imc, i);
		क्रम (j = 0; j < I10NM_NUM_DIMMS; j++) अणु
			dimm = edac_get_dimm(mci, i, j, 0);
			mtr = I10NM_GET_DIMMMTR(imc, i, j);
			mcddrtcfg = I10NM_GET_MCDDRTCFG(imc, i, j);
			edac_dbg(1, "dimmmtr 0x%x mcddrtcfg 0x%x (mc%d ch%d dimm%d)\n",
				 mtr, mcddrtcfg, imc->mc, i, j);

			अगर (IS_DIMM_PRESENT(mtr))
				ndimms += skx_get_dimm_info(mtr, 0, amap, dimm,
							    imc, i, j, cfg);
			अन्यथा अगर (IS_NVDIMM_PRESENT(mcddrtcfg, j))
				ndimms += skx_get_nvdimm_info(dimm, imc, i, j,
							      EDAC_MOD_STR);
		पूर्ण
		अगर (ndimms && !i10nm_check_ecc(imc, i)) अणु
			i10nm_prपूर्णांकk(KERN_ERR, "ECC is disabled on imc %d channel %d\n",
				     imc->mc, i);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block i10nm_mce_dec = अणु
	.notअगरier_call	= skx_mce_check_error,
	.priority	= MCE_PRIO_EDAC,
पूर्ण;

#अगर_घोषित CONFIG_EDAC_DEBUG
/*
 * Debug feature.
 * Exercise the address decode logic by writing an address to
 * /sys/kernel/debug/edac/i10nm_test/addr.
 */
अटल काष्ठा dentry *i10nm_test;

अटल पूर्णांक debugfs_u64_set(व्योम *data, u64 val)
अणु
	काष्ठा mce m;

	pr_warn_once("Fake error to 0x%llx injected via debugfs\n", val);

	स_रखो(&m, 0, माप(m));
	/* ADDRV + MemRd + Unknown channel */
	m.status = MCI_STATUS_ADDRV + 0x90;
	/* One corrected error */
	m.status |= BIT_ULL(MCI_STATUS_CEC_SHIFT);
	m.addr = val;
	skx_mce_check_error(शून्य, 0, &m);

	वापस 0;
पूर्ण
DEFINE_SIMPLE_ATTRIBUTE(fops_u64_wo, शून्य, debugfs_u64_set, "%llu\n");

अटल व्योम setup_i10nm_debug(व्योम)
अणु
	i10nm_test = edac_debugfs_create_dir("i10nm_test");
	अगर (!i10nm_test)
		वापस;

	अगर (!edac_debugfs_create_file("addr", 0200, i10nm_test,
				      शून्य, &fops_u64_wo)) अणु
		debugfs_हटाओ(i10nm_test);
		i10nm_test = शून्य;
	पूर्ण
पूर्ण

अटल व्योम tearकरोwn_i10nm_debug(व्योम)
अणु
	debugfs_हटाओ_recursive(i10nm_test);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम setup_i10nm_debug(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम tearकरोwn_i10nm_debug(व्योम) अणुपूर्ण
#पूर्ण_अगर /*CONFIG_EDAC_DEBUG*/

अटल पूर्णांक __init i10nm_init(व्योम)
अणु
	u8 mc = 0, src_id = 0, node_id = 0;
	स्थिर काष्ठा x86_cpu_id *id;
	काष्ठा res_config *cfg;
	स्थिर अक्षर *owner;
	काष्ठा skx_dev *d;
	पूर्णांक rc, i, off[3] = अणु0xd0, 0xc8, 0xccपूर्ण;
	u64 tolm, tohm;

	edac_dbg(2, "\n");

	owner = edac_get_owner();
	अगर (owner && म_भेदन(owner, EDAC_MOD_STR, माप(EDAC_MOD_STR)))
		वापस -EBUSY;

	id = x86_match_cpu(i10nm_cpuids);
	अगर (!id)
		वापस -ENODEV;

	cfg = (काष्ठा res_config *)id->driver_data;

	rc = skx_get_hi_lo(0x09a2, off, &tolm, &tohm);
	अगर (rc)
		वापस rc;

	rc = skx_get_all_bus_mappings(cfg, &i10nm_edac_list);
	अगर (rc < 0)
		जाओ fail;
	अगर (rc == 0) अणु
		i10nm_prपूर्णांकk(KERN_ERR, "No memory controllers found\n");
		वापस -ENODEV;
	पूर्ण

	rc = i10nm_get_all_munits();
	अगर (rc < 0)
		जाओ fail;

	list_क्रम_each_entry(d, i10nm_edac_list, list) अणु
		rc = skx_get_src_id(d, 0xf8, &src_id);
		अगर (rc < 0)
			जाओ fail;

		rc = skx_get_node_id(d, &node_id);
		अगर (rc < 0)
			जाओ fail;

		edac_dbg(2, "src_id = %d node_id = %d\n", src_id, node_id);
		क्रम (i = 0; i < I10NM_NUM_IMC; i++) अणु
			अगर (!d->imc[i].mdev)
				जारी;

			d->imc[i].mc  = mc++;
			d->imc[i].lmc = i;
			d->imc[i].src_id  = src_id;
			d->imc[i].node_id = node_id;
			d->imc[i].chan_mmio_sz = cfg->ddr_chan_mmio_sz;

			rc = skx_रेजिस्टर_mci(&d->imc[i], d->imc[i].mdev,
					      "Intel_10nm Socket", EDAC_MOD_STR,
					      i10nm_get_dimm_config, cfg);
			अगर (rc < 0)
				जाओ fail;
		पूर्ण
	पूर्ण

	rc = skx_adxl_get();
	अगर (rc)
		जाओ fail;

	opstate_init();
	mce_रेजिस्टर_decode_chain(&i10nm_mce_dec);
	setup_i10nm_debug();

	i10nm_prपूर्णांकk(KERN_INFO, "%s\n", I10NM_REVISION);

	वापस 0;
fail:
	skx_हटाओ();
	वापस rc;
पूर्ण

अटल व्योम __निकास i10nm_निकास(व्योम)
अणु
	edac_dbg(2, "\n");
	tearकरोwn_i10nm_debug();
	mce_unरेजिस्टर_decode_chain(&i10nm_mce_dec);
	skx_adxl_put();
	skx_हटाओ();
पूर्ण

module_init(i10nm_init);
module_निकास(i10nm_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MC Driver for Intel 10nm server processors");
