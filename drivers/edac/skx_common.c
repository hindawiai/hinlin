<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *
 * Shared code by both skx_edac and i10nm_edac. Originally split out
 * from the skx_edac driver.
 *
 * This file is linked पूर्णांकo both skx_edac and i10nm_edac drivers. In
 * order to aव्योम link errors, this file must be like a pure library
 * without including symbols and defines which would otherwise conflict,
 * when linked once पूर्णांकo a module and पूर्णांकo a built-in object, at the
 * same समय. For example, __this_module symbol references when that
 * file is being linked पूर्णांकo a built-in object.
 *
 * Copyright (c) 2018, Intel Corporation.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/adxl.h>
#समावेश <acpi/nfit.h>
#समावेश <यंत्र/mce.h>
#समावेश "edac_module.h"
#समावेश "skx_common.h"

अटल स्थिर अक्षर * स्थिर component_names[] = अणु
	[INDEX_SOCKET]	= "ProcessorSocketId",
	[INDEX_MEMCTRL]	= "MemoryControllerId",
	[INDEX_CHANNEL]	= "ChannelId",
	[INDEX_DIMM]	= "DimmSlotId",
पूर्ण;

अटल पूर्णांक component_indices[ARRAY_SIZE(component_names)];
अटल पूर्णांक adxl_component_count;
अटल स्थिर अक्षर * स्थिर *adxl_component_names;
अटल u64 *adxl_values;
अटल अक्षर *adxl_msg;

अटल अक्षर skx_msg[MSG_SIZE];
अटल skx_decode_f skx_decode;
अटल skx_show_retry_log_f skx_show_retry_rd_err_log;
अटल u64 skx_tolm, skx_tohm;
अटल LIST_HEAD(dev_edac_list);

पूर्णांक __init skx_adxl_get(व्योम)
अणु
	स्थिर अक्षर * स्थिर *names;
	पूर्णांक i, j;

	names = adxl_get_component_names();
	अगर (!names) अणु
		skx_prपूर्णांकk(KERN_NOTICE, "No firmware support for address translation.\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < INDEX_MAX; i++) अणु
		क्रम (j = 0; names[j]; j++) अणु
			अगर (!म_भेद(component_names[i], names[j])) अणु
				component_indices[i] = j;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!names[j])
			जाओ err;
	पूर्ण

	adxl_component_names = names;
	जबतक (*names++)
		adxl_component_count++;

	adxl_values = kसुस्मृति(adxl_component_count, माप(*adxl_values),
			      GFP_KERNEL);
	अगर (!adxl_values) अणु
		adxl_component_count = 0;
		वापस -ENOMEM;
	पूर्ण

	adxl_msg = kzalloc(MSG_SIZE, GFP_KERNEL);
	अगर (!adxl_msg) अणु
		adxl_component_count = 0;
		kमुक्त(adxl_values);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
err:
	skx_prपूर्णांकk(KERN_ERR, "'%s' is not matched from DSM parameters: ",
		   component_names[i]);
	क्रम (j = 0; names[j]; j++)
		skx_prपूर्णांकk(KERN_CONT, "%s ", names[j]);
	skx_prपूर्णांकk(KERN_CONT, "\n");

	वापस -ENODEV;
पूर्ण

व्योम __निकास skx_adxl_put(व्योम)
अणु
	kमुक्त(adxl_values);
	kमुक्त(adxl_msg);
पूर्ण

अटल bool skx_adxl_decode(काष्ठा decoded_addr *res)
अणु
	काष्ठा skx_dev *d;
	पूर्णांक i, len = 0;

	अगर (res->addr >= skx_tohm || (res->addr >= skx_tolm &&
				      res->addr < BIT_ULL(32))) अणु
		edac_dbg(0, "Address 0x%llx out of range\n", res->addr);
		वापस false;
	पूर्ण

	अगर (adxl_decode(res->addr, adxl_values)) अणु
		edac_dbg(0, "Failed to decode 0x%llx\n", res->addr);
		वापस false;
	पूर्ण

	res->socket  = (पूर्णांक)adxl_values[component_indices[INDEX_SOCKET]];
	res->imc     = (पूर्णांक)adxl_values[component_indices[INDEX_MEMCTRL]];
	res->channel = (पूर्णांक)adxl_values[component_indices[INDEX_CHANNEL]];
	res->dimm    = (पूर्णांक)adxl_values[component_indices[INDEX_DIMM]];

	अगर (res->imc > NUM_IMC - 1) अणु
		skx_prपूर्णांकk(KERN_ERR, "Bad imc %d\n", res->imc);
		वापस false;
	पूर्ण

	list_क्रम_each_entry(d, &dev_edac_list, list) अणु
		अगर (d->imc[0].src_id == res->socket) अणु
			res->dev = d;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!res->dev) अणु
		skx_prपूर्णांकk(KERN_ERR, "No device for src_id %d imc %d\n",
			   res->socket, res->imc);
		वापस false;
	पूर्ण

	क्रम (i = 0; i < adxl_component_count; i++) अणु
		अगर (adxl_values[i] == ~0x0ull)
			जारी;

		len += snम_लिखो(adxl_msg + len, MSG_SIZE - len, " %s:0x%llx",
				adxl_component_names[i], adxl_values[i]);
		अगर (MSG_SIZE - len <= 0)
			अवरोध;
	पूर्ण

	वापस true;
पूर्ण

व्योम skx_set_decode(skx_decode_f decode, skx_show_retry_log_f show_retry_log)
अणु
	skx_decode = decode;
	skx_show_retry_rd_err_log = show_retry_log;
पूर्ण

पूर्णांक skx_get_src_id(काष्ठा skx_dev *d, पूर्णांक off, u8 *id)
अणु
	u32 reg;

	अगर (pci_पढ़ो_config_dword(d->util_all, off, &reg)) अणु
		skx_prपूर्णांकk(KERN_ERR, "Failed to read src id\n");
		वापस -ENODEV;
	पूर्ण

	*id = GET_BITFIELD(reg, 12, 14);
	वापस 0;
पूर्ण

पूर्णांक skx_get_node_id(काष्ठा skx_dev *d, u8 *id)
अणु
	u32 reg;

	अगर (pci_पढ़ो_config_dword(d->util_all, 0xf4, &reg)) अणु
		skx_prपूर्णांकk(KERN_ERR, "Failed to read node id\n");
		वापस -ENODEV;
	पूर्ण

	*id = GET_BITFIELD(reg, 0, 2);
	वापस 0;
पूर्ण

अटल पूर्णांक get_width(u32 mtr)
अणु
	चयन (GET_BITFIELD(mtr, 8, 9)) अणु
	हाल 0:
		वापस DEV_X4;
	हाल 1:
		वापस DEV_X8;
	हाल 2:
		वापस DEV_X16;
	पूर्ण
	वापस DEV_UNKNOWN;
पूर्ण

/*
 * We use the per-socket device @cfg->did to count how many sockets are present,
 * and to detemine which PCI buses are associated with each socket. Allocate
 * and build the full list of all the skx_dev काष्ठाures that we need here.
 */
पूर्णांक skx_get_all_bus_mappings(काष्ठा res_config *cfg, काष्ठा list_head **list)
अणु
	काष्ठा pci_dev *pdev, *prev;
	काष्ठा skx_dev *d;
	u32 reg;
	पूर्णांक ndev = 0;

	prev = शून्य;
	क्रम (;;) अणु
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL, cfg->decs_did, prev);
		अगर (!pdev)
			अवरोध;
		ndev++;
		d = kzalloc(माप(*d), GFP_KERNEL);
		अगर (!d) अणु
			pci_dev_put(pdev);
			वापस -ENOMEM;
		पूर्ण

		अगर (pci_पढ़ो_config_dword(pdev, cfg->busno_cfg_offset, &reg)) अणु
			kमुक्त(d);
			pci_dev_put(pdev);
			skx_prपूर्णांकk(KERN_ERR, "Failed to read bus idx\n");
			वापस -ENODEV;
		पूर्ण

		d->bus[0] = GET_BITFIELD(reg, 0, 7);
		d->bus[1] = GET_BITFIELD(reg, 8, 15);
		अगर (cfg->type == SKX) अणु
			d->seg = pci_करोमुख्य_nr(pdev->bus);
			d->bus[2] = GET_BITFIELD(reg, 16, 23);
			d->bus[3] = GET_BITFIELD(reg, 24, 31);
		पूर्ण अन्यथा अणु
			d->seg = GET_BITFIELD(reg, 16, 23);
		पूर्ण

		edac_dbg(2, "busses: 0x%x, 0x%x, 0x%x, 0x%x\n",
			 d->bus[0], d->bus[1], d->bus[2], d->bus[3]);
		list_add_tail(&d->list, &dev_edac_list);
		prev = pdev;
	पूर्ण

	अगर (list)
		*list = &dev_edac_list;
	वापस ndev;
पूर्ण

पूर्णांक skx_get_hi_lo(अचिन्हित पूर्णांक did, पूर्णांक off[], u64 *tolm, u64 *tohm)
अणु
	काष्ठा pci_dev *pdev;
	u32 reg;

	pdev = pci_get_device(PCI_VENDOR_ID_INTEL, did, शून्य);
	अगर (!pdev) अणु
		edac_dbg(2, "Can't get tolm/tohm\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pci_पढ़ो_config_dword(pdev, off[0], &reg)) अणु
		skx_prपूर्णांकk(KERN_ERR, "Failed to read tolm\n");
		जाओ fail;
	पूर्ण
	skx_tolm = reg;

	अगर (pci_पढ़ो_config_dword(pdev, off[1], &reg)) अणु
		skx_prपूर्णांकk(KERN_ERR, "Failed to read lower tohm\n");
		जाओ fail;
	पूर्ण
	skx_tohm = reg;

	अगर (pci_पढ़ो_config_dword(pdev, off[2], &reg)) अणु
		skx_prपूर्णांकk(KERN_ERR, "Failed to read upper tohm\n");
		जाओ fail;
	पूर्ण
	skx_tohm |= (u64)reg << 32;

	pci_dev_put(pdev);
	*tolm = skx_tolm;
	*tohm = skx_tohm;
	edac_dbg(2, "tolm = 0x%llx tohm = 0x%llx\n", skx_tolm, skx_tohm);
	वापस 0;
fail:
	pci_dev_put(pdev);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक skx_get_dimm_attr(u32 reg, पूर्णांक lobit, पूर्णांक hibit, पूर्णांक add,
			     पूर्णांक minval, पूर्णांक maxval, स्थिर अक्षर *name)
अणु
	u32 val = GET_BITFIELD(reg, lobit, hibit);

	अगर (val < minval || val > maxval) अणु
		edac_dbg(2, "bad %s = %d (raw=0x%x)\n", name, val, reg);
		वापस -EINVAL;
	पूर्ण
	वापस val + add;
पूर्ण

#घोषणा numrank(reg)	skx_get_dimm_attr(reg, 12, 13, 0, 0, 2, "ranks")
#घोषणा numrow(reg)	skx_get_dimm_attr(reg, 2, 4, 12, 1, 6, "rows")
#घोषणा numcol(reg)	skx_get_dimm_attr(reg, 0, 1, 10, 0, 2, "cols")

पूर्णांक skx_get_dimm_info(u32 mtr, u32 mcmtr, u32 amap, काष्ठा dimm_info *dimm,
		      काष्ठा skx_imc *imc, पूर्णांक chan, पूर्णांक dimmno,
		      काष्ठा res_config *cfg)
अणु
	पूर्णांक  banks, ranks, rows, cols, npages;
	क्रमागत mem_type mtype;
	u64 size;

	ranks = numrank(mtr);
	rows = numrow(mtr);
	cols = numcol(mtr);

	अगर (cfg->support_ddr5 && (amap & 0x8)) अणु
		banks = 32;
		mtype = MEM_DDR5;
	पूर्ण अन्यथा अणु
		banks = 16;
		mtype = MEM_DDR4;
	पूर्ण

	/*
	 * Compute size in 8-byte (2^3) words, then shअगरt to MiB (2^20)
	 */
	size = ((1ull << (rows + cols + ranks)) * banks) >> (20 - 3);
	npages = MiB_TO_PAGES(size);

	edac_dbg(0, "mc#%d: channel %d, dimm %d, %lld MiB (%d pages) bank: %d, rank: %d, row: 0x%x, col: 0x%x\n",
		 imc->mc, chan, dimmno, size, npages,
		 banks, 1 << ranks, rows, cols);

	imc->chan[chan].dimms[dimmno].बंद_pg = GET_BITFIELD(mcmtr, 0, 0);
	imc->chan[chan].dimms[dimmno].bank_xor_enable = GET_BITFIELD(mcmtr, 9, 9);
	imc->chan[chan].dimms[dimmno].fine_grain_bank = GET_BITFIELD(amap, 0, 0);
	imc->chan[chan].dimms[dimmno].rowbits = rows;
	imc->chan[chan].dimms[dimmno].colbits = cols;

	dimm->nr_pages = npages;
	dimm->grain = 32;
	dimm->dtype = get_width(mtr);
	dimm->mtype = mtype;
	dimm->edac_mode = EDAC_SECDED; /* likely better than this */
	snम_लिखो(dimm->label, माप(dimm->label), "CPU_SrcID#%u_MC#%u_Chan#%u_DIMM#%u",
		 imc->src_id, imc->lmc, chan, dimmno);

	वापस 1;
पूर्ण

पूर्णांक skx_get_nvdimm_info(काष्ठा dimm_info *dimm, काष्ठा skx_imc *imc,
			पूर्णांक chan, पूर्णांक dimmno, स्थिर अक्षर *mod_str)
अणु
	पूर्णांक smbios_handle;
	u32 dev_handle;
	u16 flags;
	u64 size = 0;

	dev_handle = ACPI_NFIT_BUILD_DEVICE_HANDLE(dimmno, chan, imc->lmc,
						   imc->src_id, 0);

	smbios_handle = nfit_get_smbios_id(dev_handle, &flags);
	अगर (smbios_handle == -EOPNOTSUPP) अणु
		pr_warn_once("%s: Can't find size of NVDIMM. Try enabling CONFIG_ACPI_NFIT\n", mod_str);
		जाओ unknown_size;
	पूर्ण

	अगर (smbios_handle < 0) अणु
		skx_prपूर्णांकk(KERN_ERR, "Can't find handle for NVDIMM ADR=0x%x\n", dev_handle);
		जाओ unknown_size;
	पूर्ण

	अगर (flags & ACPI_NFIT_MEM_MAP_FAILED) अणु
		skx_prपूर्णांकk(KERN_ERR, "NVDIMM ADR=0x%x is not mapped\n", dev_handle);
		जाओ unknown_size;
	पूर्ण

	size = dmi_memdev_size(smbios_handle);
	अगर (size == ~0ull)
		skx_prपूर्णांकk(KERN_ERR, "Can't find size for NVDIMM ADR=0x%x/SMBIOS=0x%x\n",
			   dev_handle, smbios_handle);

unknown_size:
	dimm->nr_pages = size >> PAGE_SHIFT;
	dimm->grain = 32;
	dimm->dtype = DEV_UNKNOWN;
	dimm->mtype = MEM_NVDIMM;
	dimm->edac_mode = EDAC_SECDED; /* likely better than this */

	edac_dbg(0, "mc#%d: channel %d, dimm %d, %llu MiB (%u pages)\n",
		 imc->mc, chan, dimmno, size >> 20, dimm->nr_pages);

	snम_लिखो(dimm->label, माप(dimm->label), "CPU_SrcID#%u_MC#%u_Chan#%u_DIMM#%u",
		 imc->src_id, imc->lmc, chan, dimmno);

	वापस (size == 0 || size == ~0ull) ? 0 : 1;
पूर्ण

पूर्णांक skx_रेजिस्टर_mci(काष्ठा skx_imc *imc, काष्ठा pci_dev *pdev,
		     स्थिर अक्षर *ctl_name, स्थिर अक्षर *mod_str,
		     get_dimm_config_f get_dimm_config,
		     काष्ठा res_config *cfg)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा skx_pvt *pvt;
	पूर्णांक rc;

	/* Allocate a new MC control काष्ठाure */
	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = NUM_CHANNELS;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_SLOT;
	layers[1].size = NUM_DIMMS;
	layers[1].is_virt_csrow = true;
	mci = edac_mc_alloc(imc->mc, ARRAY_SIZE(layers), layers,
			    माप(काष्ठा skx_pvt));

	अगर (unlikely(!mci))
		वापस -ENOMEM;

	edac_dbg(0, "MC#%d: mci = %p\n", imc->mc, mci);

	/* Associate skx_dev and mci क्रम future usage */
	imc->mci = mci;
	pvt = mci->pvt_info;
	pvt->imc = imc;

	mci->ctl_name = kaप्र_लिखो(GFP_KERNEL, "%s#%d IMC#%d", ctl_name,
				  imc->node_id, imc->lmc);
	अगर (!mci->ctl_name) अणु
		rc = -ENOMEM;
		जाओ fail0;
	पूर्ण

	mci->mtype_cap = MEM_FLAG_DDR4 | MEM_FLAG_NVDIMM;
	अगर (cfg->support_ddr5)
		mci->mtype_cap |= MEM_FLAG_DDR5;
	mci->edac_ctl_cap = EDAC_FLAG_NONE;
	mci->edac_cap = EDAC_FLAG_NONE;
	mci->mod_name = mod_str;
	mci->dev_name = pci_name(pdev);
	mci->ctl_page_to_phys = शून्य;

	rc = get_dimm_config(mci, cfg);
	अगर (rc < 0)
		जाओ fail;

	/* Record ptr to the generic device */
	mci->pdev = &pdev->dev;

	/* Add this new MC control काष्ठाure to EDAC's list of MCs */
	अगर (unlikely(edac_mc_add_mc(mci))) अणु
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");
		rc = -EINVAL;
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	kमुक्त(mci->ctl_name);
fail0:
	edac_mc_मुक्त(mci);
	imc->mci = शून्य;
	वापस rc;
पूर्ण

अटल व्योम skx_unरेजिस्टर_mci(काष्ठा skx_imc *imc)
अणु
	काष्ठा mem_ctl_info *mci = imc->mci;

	अगर (!mci)
		वापस;

	edac_dbg(0, "MC%d: mci = %p\n", imc->mc, mci);

	/* Remove MC sysfs nodes */
	edac_mc_del_mc(mci->pdev);

	edac_dbg(1, "%s: free mci struct\n", mci->ctl_name);
	kमुक्त(mci->ctl_name);
	edac_mc_मुक्त(mci);
पूर्ण

अटल व्योम skx_mce_output_error(काष्ठा mem_ctl_info *mci,
				 स्थिर काष्ठा mce *m,
				 काष्ठा decoded_addr *res)
अणु
	क्रमागत hw_event_mc_err_type tp_event;
	अक्षर *optype;
	bool ripv = GET_BITFIELD(m->mcgstatus, 0, 0);
	bool overflow = GET_BITFIELD(m->status, 62, 62);
	bool uncorrected_error = GET_BITFIELD(m->status, 61, 61);
	bool recoverable;
	पूर्णांक len;
	u32 core_err_cnt = GET_BITFIELD(m->status, 38, 52);
	u32 mscod = GET_BITFIELD(m->status, 16, 31);
	u32 errcode = GET_BITFIELD(m->status, 0, 15);
	u32 optypक्रमागत = GET_BITFIELD(m->status, 4, 6);

	recoverable = GET_BITFIELD(m->status, 56, 56);

	अगर (uncorrected_error) अणु
		core_err_cnt = 1;
		अगर (ripv) अणु
			tp_event = HW_EVENT_ERR_UNCORRECTED;
		पूर्ण अन्यथा अणु
			tp_event = HW_EVENT_ERR_FATAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		tp_event = HW_EVENT_ERR_CORRECTED;
	पूर्ण

	/*
	 * According to Intel Architecture spec vol 3B,
	 * Table 15-10 "IA32_MCi_Status [15:0] Compound Error Code Encoding"
	 * memory errors should fit one of these masks:
	 *	000f 0000 1mmm cccc (binary)
	 *	000f 0010 1mmm cccc (binary)	[RAM used as cache]
	 * where:
	 *	f = Correction Report Filtering Bit. If 1, subsequent errors
	 *	    won't be shown
	 *	mmm = error type
	 *	cccc = channel
	 * If the mask करोesn't match, report an error to the parsing logic
	 */
	अगर (!((errcode & 0xef80) == 0x80 || (errcode & 0xef80) == 0x280)) अणु
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
	अगर (adxl_component_count) अणु
		len = snम_लिखो(skx_msg, MSG_SIZE, "%s%s err_code:0x%04x:0x%04x %s",
			 overflow ? " OVERFLOW" : "",
			 (uncorrected_error && recoverable) ? " recoverable" : "",
			 mscod, errcode, adxl_msg);
	पूर्ण अन्यथा अणु
		len = snम_लिखो(skx_msg, MSG_SIZE,
			 "%s%s err_code:0x%04x:0x%04x socket:%d imc:%d rank:%d bg:%d ba:%d row:0x%x col:0x%x",
			 overflow ? " OVERFLOW" : "",
			 (uncorrected_error && recoverable) ? " recoverable" : "",
			 mscod, errcode,
			 res->socket, res->imc, res->rank,
			 res->bank_group, res->bank_address, res->row, res->column);
	पूर्ण

	अगर (skx_show_retry_rd_err_log)
		skx_show_retry_rd_err_log(res, skx_msg + len, MSG_SIZE - len);

	edac_dbg(0, "%s\n", skx_msg);

	/* Call the helper to output message */
	edac_mc_handle_error(tp_event, mci, core_err_cnt,
			     m->addr >> PAGE_SHIFT, m->addr & ~PAGE_MASK, 0,
			     res->channel, res->dimm, -1,
			     optype, skx_msg);
पूर्ण

पूर्णांक skx_mce_check_error(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			व्योम *data)
अणु
	काष्ठा mce *mce = (काष्ठा mce *)data;
	काष्ठा decoded_addr res;
	काष्ठा mem_ctl_info *mci;
	अक्षर *type;

	अगर (mce->kflags & MCE_HANDLED_CEC)
		वापस NOTIFY_DONE;

	/* ignore unless this is memory related with an address */
	अगर ((mce->status & 0xefff) >> 7 != 1 || !(mce->status & MCI_STATUS_ADDRV))
		वापस NOTIFY_DONE;

	स_रखो(&res, 0, माप(res));
	res.addr = mce->addr;

	अगर (adxl_component_count) अणु
		अगर (!skx_adxl_decode(&res))
			वापस NOTIFY_DONE;
	पूर्ण अन्यथा अगर (!skx_decode || !skx_decode(&res)) अणु
		वापस NOTIFY_DONE;
	पूर्ण

	mci = res.dev->imc[res.imc].mci;

	अगर (!mci)
		वापस NOTIFY_DONE;

	अगर (mce->mcgstatus & MCG_STATUS_MCIP)
		type = "Exception";
	अन्यथा
		type = "Event";

	skx_mc_prपूर्णांकk(mci, KERN_DEBUG, "HANDLING MCE MEMORY ERROR\n");

	skx_mc_prपूर्णांकk(mci, KERN_DEBUG, "CPU %d: Machine Check %s: 0x%llx "
			   "Bank %d: 0x%llx\n", mce->extcpu, type,
			   mce->mcgstatus, mce->bank, mce->status);
	skx_mc_prपूर्णांकk(mci, KERN_DEBUG, "TSC 0x%llx ", mce->tsc);
	skx_mc_prपूर्णांकk(mci, KERN_DEBUG, "ADDR 0x%llx ", mce->addr);
	skx_mc_prपूर्णांकk(mci, KERN_DEBUG, "MISC 0x%llx ", mce->misc);

	skx_mc_prपूर्णांकk(mci, KERN_DEBUG, "PROCESSOR %u:0x%x TIME %llu SOCKET "
			   "%u APIC 0x%x\n", mce->cpuvenकरोr, mce->cpuid,
			   mce->समय, mce->socketid, mce->apicid);

	skx_mce_output_error(mci, mce, &res);

	mce->kflags |= MCE_HANDLED_EDAC;
	वापस NOTIFY_DONE;
पूर्ण

व्योम skx_हटाओ(व्योम)
अणु
	पूर्णांक i, j;
	काष्ठा skx_dev *d, *पंचांगp;

	edac_dbg(0, "\n");

	list_क्रम_each_entry_safe(d, पंचांगp, &dev_edac_list, list) अणु
		list_del(&d->list);
		क्रम (i = 0; i < NUM_IMC; i++) अणु
			अगर (d->imc[i].mci)
				skx_unरेजिस्टर_mci(&d->imc[i]);

			अगर (d->imc[i].mdev)
				pci_dev_put(d->imc[i].mdev);

			अगर (d->imc[i].mbase)
				iounmap(d->imc[i].mbase);

			क्रम (j = 0; j < NUM_CHANNELS; j++) अणु
				अगर (d->imc[i].chan[j].cdev)
					pci_dev_put(d->imc[i].chan[j].cdev);
			पूर्ण
		पूर्ण
		अगर (d->util_all)
			pci_dev_put(d->util_all);
		अगर (d->sad_all)
			pci_dev_put(d->sad_all);
		अगर (d->uracu)
			pci_dev_put(d->uracu);

		kमुक्त(d);
	पूर्ण
पूर्ण
