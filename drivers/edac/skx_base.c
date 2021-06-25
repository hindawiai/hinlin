<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * EDAC driver क्रम Intel(R) Xeon(R) Skylake processors
 * Copyright (c) 2016, Intel Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/processor.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/mce.h>

#समावेश "edac_module.h"
#समावेश "skx_common.h"

#घोषणा EDAC_MOD_STR    "skx_edac"

/*
 * Debug macros
 */
#घोषणा skx_prपूर्णांकk(level, fmt, arg...)			\
	edac_prपूर्णांकk(level, "skx", fmt, ##arg)

#घोषणा skx_mc_prपूर्णांकk(mci, level, fmt, arg...)		\
	edac_mc_chipset_prपूर्णांकk(mci, level, "skx", fmt, ##arg)

अटल काष्ठा list_head *skx_edac_list;

अटल u64 skx_tolm, skx_tohm;
अटल पूर्णांक skx_num_sockets;
अटल अचिन्हित पूर्णांक nvdimm_count;

#घोषणा	MASK26	0x3FFFFFF		/* Mask क्रम 2^26 */
#घोषणा MASK29	0x1FFFFFFF		/* Mask क्रम 2^29 */

अटल काष्ठा skx_dev *get_skx_dev(काष्ठा pci_bus *bus, u8 idx)
अणु
	काष्ठा skx_dev *d;

	list_क्रम_each_entry(d, skx_edac_list, list) अणु
		अगर (d->seg == pci_करोमुख्य_nr(bus) && d->bus[idx] == bus->number)
			वापस d;
	पूर्ण

	वापस शून्य;
पूर्ण

क्रमागत munittype अणु
	CHAN0, CHAN1, CHAN2, SAD_ALL, UTIL_ALL, SAD,
	ERRCHAN0, ERRCHAN1, ERRCHAN2,
पूर्ण;

काष्ठा munit अणु
	u16	did;
	u16	devfn[SKX_NUM_IMC];
	u8	busidx;
	u8	per_socket;
	क्रमागत munittype mtype;
पूर्ण;

/*
 * List of PCI device ids that we need together with some device
 * number and function numbers to tell which memory controller the
 * device beदीर्घs to.
 */
अटल स्थिर काष्ठा munit skx_all_munits[] = अणु
	अणु 0x2054, अणु पूर्ण, 1, 1, SAD_ALL पूर्ण,
	अणु 0x2055, अणु पूर्ण, 1, 1, UTIL_ALL पूर्ण,
	अणु 0x2040, अणु PCI_DEVFN(10, 0), PCI_DEVFN(12, 0) पूर्ण, 2, 2, CHAN0 पूर्ण,
	अणु 0x2044, अणु PCI_DEVFN(10, 4), PCI_DEVFN(12, 4) पूर्ण, 2, 2, CHAN1 पूर्ण,
	अणु 0x2048, अणु PCI_DEVFN(11, 0), PCI_DEVFN(13, 0) पूर्ण, 2, 2, CHAN2 पूर्ण,
	अणु 0x2043, अणु PCI_DEVFN(10, 3), PCI_DEVFN(12, 3) पूर्ण, 2, 2, ERRCHAN0 पूर्ण,
	अणु 0x2047, अणु PCI_DEVFN(10, 7), PCI_DEVFN(12, 7) पूर्ण, 2, 2, ERRCHAN1 पूर्ण,
	अणु 0x204b, अणु PCI_DEVFN(11, 3), PCI_DEVFN(13, 3) पूर्ण, 2, 2, ERRCHAN2 पूर्ण,
	अणु 0x208e, अणु पूर्ण, 1, 0, SAD पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक get_all_munits(स्थिर काष्ठा munit *m)
अणु
	काष्ठा pci_dev *pdev, *prev;
	काष्ठा skx_dev *d;
	u32 reg;
	पूर्णांक i = 0, ndev = 0;

	prev = शून्य;
	क्रम (;;) अणु
		pdev = pci_get_device(PCI_VENDOR_ID_INTEL, m->did, prev);
		अगर (!pdev)
			अवरोध;
		ndev++;
		अगर (m->per_socket == SKX_NUM_IMC) अणु
			क्रम (i = 0; i < SKX_NUM_IMC; i++)
				अगर (m->devfn[i] == pdev->devfn)
					अवरोध;
			अगर (i == SKX_NUM_IMC)
				जाओ fail;
		पूर्ण
		d = get_skx_dev(pdev->bus, m->busidx);
		अगर (!d)
			जाओ fail;

		/* Be sure that the device is enabled */
		अगर (unlikely(pci_enable_device(pdev) < 0)) अणु
			skx_prपूर्णांकk(KERN_ERR, "Couldn't enable device %04x:%04x\n",
				   PCI_VENDOR_ID_INTEL, m->did);
			जाओ fail;
		पूर्ण

		चयन (m->mtype) अणु
		हाल CHAN0:
		हाल CHAN1:
		हाल CHAN2:
			pci_dev_get(pdev);
			d->imc[i].chan[m->mtype].cdev = pdev;
			अवरोध;
		हाल ERRCHAN0:
		हाल ERRCHAN1:
		हाल ERRCHAN2:
			pci_dev_get(pdev);
			d->imc[i].chan[m->mtype - ERRCHAN0].edev = pdev;
			अवरोध;
		हाल SAD_ALL:
			pci_dev_get(pdev);
			d->sad_all = pdev;
			अवरोध;
		हाल UTIL_ALL:
			pci_dev_get(pdev);
			d->util_all = pdev;
			अवरोध;
		हाल SAD:
			/*
			 * one of these devices per core, including cores
			 * that करोn't exist on this SKU. Ignore any that
			 * पढ़ो a route table of zero, make sure all the
			 * non-zero values match.
			 */
			pci_पढ़ो_config_dword(pdev, 0xB4, &reg);
			अगर (reg != 0) अणु
				अगर (d->mcroute == 0) अणु
					d->mcroute = reg;
				पूर्ण अन्यथा अगर (d->mcroute != reg) अणु
					skx_prपूर्णांकk(KERN_ERR, "mcroute mismatch\n");
					जाओ fail;
				पूर्ण
			पूर्ण
			ndev--;
			अवरोध;
		पूर्ण

		prev = pdev;
	पूर्ण

	वापस ndev;
fail:
	pci_dev_put(pdev);
	वापस -ENODEV;
पूर्ण

अटल काष्ठा res_config skx_cfg = अणु
	.type			= SKX,
	.decs_did		= 0x2016,
	.busno_cfg_offset	= 0xcc,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id skx_cpuids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL_STEPPINGS(SKYLAKE_X, X86_STEPPINGS(0x0, 0xf), &skx_cfg),
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, skx_cpuids);

अटल bool skx_check_ecc(u32 mcmtr)
अणु
	वापस !!GET_BITFIELD(mcmtr, 2, 2);
पूर्ण

अटल पूर्णांक skx_get_dimm_config(काष्ठा mem_ctl_info *mci, काष्ठा res_config *cfg)
अणु
	काष्ठा skx_pvt *pvt = mci->pvt_info;
	u32 mtr, mcmtr, amap, mcddrtcfg;
	काष्ठा skx_imc *imc = pvt->imc;
	काष्ठा dimm_info *dimm;
	पूर्णांक i, j;
	पूर्णांक ndimms;

	/* Only the mcmtr on the first channel is effective */
	pci_पढ़ो_config_dword(imc->chan[0].cdev, 0x87c, &mcmtr);

	क्रम (i = 0; i < SKX_NUM_CHANNELS; i++) अणु
		ndimms = 0;
		pci_पढ़ो_config_dword(imc->chan[i].cdev, 0x8C, &amap);
		pci_पढ़ो_config_dword(imc->chan[i].cdev, 0x400, &mcddrtcfg);
		क्रम (j = 0; j < SKX_NUM_DIMMS; j++) अणु
			dimm = edac_get_dimm(mci, i, j, 0);
			pci_पढ़ो_config_dword(imc->chan[i].cdev,
					      0x80 + 4 * j, &mtr);
			अगर (IS_DIMM_PRESENT(mtr)) अणु
				ndimms += skx_get_dimm_info(mtr, mcmtr, amap, dimm, imc, i, j, cfg);
			पूर्ण अन्यथा अगर (IS_NVDIMM_PRESENT(mcddrtcfg, j)) अणु
				ndimms += skx_get_nvdimm_info(dimm, imc, i, j,
							      EDAC_MOD_STR);
				nvdimm_count++;
			पूर्ण
		पूर्ण
		अगर (ndimms && !skx_check_ecc(mcmtr)) अणु
			skx_prपूर्णांकk(KERN_ERR, "ECC is disabled on imc %d\n", imc->mc);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा	SKX_MAX_SAD 24

#घोषणा SKX_GET_SAD(d, i, reg)	\
	pci_पढ़ो_config_dword((d)->sad_all, 0x60 + 8 * (i), &(reg))
#घोषणा SKX_GET_ILV(d, i, reg)	\
	pci_पढ़ो_config_dword((d)->sad_all, 0x64 + 8 * (i), &(reg))

#घोषणा	SKX_SAD_MOD3MODE(sad)	GET_BITFIELD((sad), 30, 31)
#घोषणा	SKX_SAD_MOD3(sad)	GET_BITFIELD((sad), 27, 27)
#घोषणा SKX_SAD_LIMIT(sad)	(((u64)GET_BITFIELD((sad), 7, 26) << 26) | MASK26)
#घोषणा	SKX_SAD_MOD3ASMOD2(sad)	GET_BITFIELD((sad), 5, 6)
#घोषणा	SKX_SAD_ATTR(sad)	GET_BITFIELD((sad), 3, 4)
#घोषणा	SKX_SAD_INTERLEAVE(sad)	GET_BITFIELD((sad), 1, 2)
#घोषणा SKX_SAD_ENABLE(sad)	GET_BITFIELD((sad), 0, 0)

#घोषणा SKX_ILV_REMOTE(tgt)	(((tgt) & 8) == 0)
#घोषणा SKX_ILV_TARGET(tgt)	((tgt) & 7)

अटल व्योम skx_show_retry_rd_err_log(काष्ठा decoded_addr *res,
				      अक्षर *msg, पूर्णांक len)
अणु
	u32 log0, log1, log2, log3, log4;
	u32 corr0, corr1, corr2, corr3;
	काष्ठा pci_dev *edev;
	पूर्णांक n;

	edev = res->dev->imc[res->imc].chan[res->channel].edev;

	pci_पढ़ो_config_dword(edev, 0x154, &log0);
	pci_पढ़ो_config_dword(edev, 0x148, &log1);
	pci_पढ़ो_config_dword(edev, 0x150, &log2);
	pci_पढ़ो_config_dword(edev, 0x15c, &log3);
	pci_पढ़ो_config_dword(edev, 0x114, &log4);

	n = snम_लिखो(msg, len, " retry_rd_err_log[%.8x %.8x %.8x %.8x %.8x]",
		     log0, log1, log2, log3, log4);

	pci_पढ़ो_config_dword(edev, 0x104, &corr0);
	pci_पढ़ो_config_dword(edev, 0x108, &corr1);
	pci_पढ़ो_config_dword(edev, 0x10c, &corr2);
	pci_पढ़ो_config_dword(edev, 0x110, &corr3);

	अगर (len - n > 0)
		snम_लिखो(msg + n, len - n,
			 " correrrcnt[%.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x]",
			 corr0 & 0xffff, corr0 >> 16,
			 corr1 & 0xffff, corr1 >> 16,
			 corr2 & 0xffff, corr2 >> 16,
			 corr3 & 0xffff, corr3 >> 16);
पूर्ण

अटल bool skx_sad_decode(काष्ठा decoded_addr *res)
अणु
	काष्ठा skx_dev *d = list_first_entry(skx_edac_list, typeof(*d), list);
	u64 addr = res->addr;
	पूर्णांक i, idx, tgt, lchan, shअगरt;
	u32 sad, ilv;
	u64 limit, prev_limit;
	पूर्णांक remote = 0;

	/* Simple sanity check क्रम I/O space or out of range */
	अगर (addr >= skx_tohm || (addr >= skx_tolm && addr < BIT_ULL(32))) अणु
		edac_dbg(0, "Address 0x%llx out of range\n", addr);
		वापस false;
	पूर्ण

restart:
	prev_limit = 0;
	क्रम (i = 0; i < SKX_MAX_SAD; i++) अणु
		SKX_GET_SAD(d, i, sad);
		limit = SKX_SAD_LIMIT(sad);
		अगर (SKX_SAD_ENABLE(sad)) अणु
			अगर (addr >= prev_limit && addr <= limit)
				जाओ sad_found;
		पूर्ण
		prev_limit = limit + 1;
	पूर्ण
	edac_dbg(0, "No SAD entry for 0x%llx\n", addr);
	वापस false;

sad_found:
	SKX_GET_ILV(d, i, ilv);

	चयन (SKX_SAD_INTERLEAVE(sad)) अणु
	हाल 0:
		idx = GET_BITFIELD(addr, 6, 8);
		अवरोध;
	हाल 1:
		idx = GET_BITFIELD(addr, 8, 10);
		अवरोध;
	हाल 2:
		idx = GET_BITFIELD(addr, 12, 14);
		अवरोध;
	हाल 3:
		idx = GET_BITFIELD(addr, 30, 32);
		अवरोध;
	पूर्ण

	tgt = GET_BITFIELD(ilv, 4 * idx, 4 * idx + 3);

	/* If poपूर्णांक to another node, find it and start over */
	अगर (SKX_ILV_REMOTE(tgt)) अणु
		अगर (remote) अणु
			edac_dbg(0, "Double remote!\n");
			वापस false;
		पूर्ण
		remote = 1;
		list_क्रम_each_entry(d, skx_edac_list, list) अणु
			अगर (d->imc[0].src_id == SKX_ILV_TARGET(tgt))
				जाओ restart;
		पूर्ण
		edac_dbg(0, "Can't find node %d\n", SKX_ILV_TARGET(tgt));
		वापस false;
	पूर्ण

	अगर (SKX_SAD_MOD3(sad) == 0) अणु
		lchan = SKX_ILV_TARGET(tgt);
	पूर्ण अन्यथा अणु
		चयन (SKX_SAD_MOD3MODE(sad)) अणु
		हाल 0:
			shअगरt = 6;
			अवरोध;
		हाल 1:
			shअगरt = 8;
			अवरोध;
		हाल 2:
			shअगरt = 12;
			अवरोध;
		शेष:
			edac_dbg(0, "illegal mod3mode\n");
			वापस false;
		पूर्ण
		चयन (SKX_SAD_MOD3ASMOD2(sad)) अणु
		हाल 0:
			lchan = (addr >> shअगरt) % 3;
			अवरोध;
		हाल 1:
			lchan = (addr >> shअगरt) % 2;
			अवरोध;
		हाल 2:
			lchan = (addr >> shअगरt) % 2;
			lchan = (lchan << 1) | !lchan;
			अवरोध;
		हाल 3:
			lchan = ((addr >> shअगरt) % 2) << 1;
			अवरोध;
		पूर्ण
		lchan = (lchan << 1) | (SKX_ILV_TARGET(tgt) & 1);
	पूर्ण

	res->dev = d;
	res->socket = d->imc[0].src_id;
	res->imc = GET_BITFIELD(d->mcroute, lchan * 3, lchan * 3 + 2);
	res->channel = GET_BITFIELD(d->mcroute, lchan * 2 + 18, lchan * 2 + 19);

	edac_dbg(2, "0x%llx: socket=%d imc=%d channel=%d\n",
		 res->addr, res->socket, res->imc, res->channel);
	वापस true;
पूर्ण

#घोषणा	SKX_MAX_TAD 8

#घोषणा SKX_GET_TADBASE(d, mc, i, reg)			\
	pci_पढ़ो_config_dword((d)->imc[mc].chan[0].cdev, 0x850 + 4 * (i), &(reg))
#घोषणा SKX_GET_TADWAYNESS(d, mc, i, reg)		\
	pci_पढ़ो_config_dword((d)->imc[mc].chan[0].cdev, 0x880 + 4 * (i), &(reg))
#घोषणा SKX_GET_TADCHNILVOFFSET(d, mc, ch, i, reg)	\
	pci_पढ़ो_config_dword((d)->imc[mc].chan[ch].cdev, 0x90 + 4 * (i), &(reg))

#घोषणा	SKX_TAD_BASE(b)		((u64)GET_BITFIELD((b), 12, 31) << 26)
#घोषणा SKX_TAD_SKT_GRAN(b)	GET_BITFIELD((b), 4, 5)
#घोषणा SKX_TAD_CHN_GRAN(b)	GET_BITFIELD((b), 6, 7)
#घोषणा	SKX_TAD_LIMIT(b)	(((u64)GET_BITFIELD((b), 12, 31) << 26) | MASK26)
#घोषणा	SKX_TAD_OFFSET(b)	((u64)GET_BITFIELD((b), 4, 23) << 26)
#घोषणा	SKX_TAD_SKTWAYS(b)	(1 << GET_BITFIELD((b), 10, 11))
#घोषणा	SKX_TAD_CHNWAYS(b)	(GET_BITFIELD((b), 8, 9) + 1)

/* which bit used क्रम both socket and channel पूर्णांकerleave */
अटल पूर्णांक skx_granularity[] = अणु 6, 8, 12, 30 पूर्ण;

अटल u64 skx_करो_पूर्णांकerleave(u64 addr, पूर्णांक shअगरt, पूर्णांक ways, u64 lowbits)
अणु
	addr >>= shअगरt;
	addr /= ways;
	addr <<= shअगरt;

	वापस addr | (lowbits & ((1ull << shअगरt) - 1));
पूर्ण

अटल bool skx_tad_decode(काष्ठा decoded_addr *res)
अणु
	पूर्णांक i;
	u32 base, wayness, chnilvoffset;
	पूर्णांक skt_पूर्णांकerleave_bit, chn_पूर्णांकerleave_bit;
	u64 channel_addr;

	क्रम (i = 0; i < SKX_MAX_TAD; i++) अणु
		SKX_GET_TADBASE(res->dev, res->imc, i, base);
		SKX_GET_TADWAYNESS(res->dev, res->imc, i, wayness);
		अगर (SKX_TAD_BASE(base) <= res->addr && res->addr <= SKX_TAD_LIMIT(wayness))
			जाओ tad_found;
	पूर्ण
	edac_dbg(0, "No TAD entry for 0x%llx\n", res->addr);
	वापस false;

tad_found:
	res->sktways = SKX_TAD_SKTWAYS(wayness);
	res->chanways = SKX_TAD_CHNWAYS(wayness);
	skt_पूर्णांकerleave_bit = skx_granularity[SKX_TAD_SKT_GRAN(base)];
	chn_पूर्णांकerleave_bit = skx_granularity[SKX_TAD_CHN_GRAN(base)];

	SKX_GET_TADCHNILVOFFSET(res->dev, res->imc, res->channel, i, chnilvoffset);
	channel_addr = res->addr - SKX_TAD_OFFSET(chnilvoffset);

	अगर (res->chanways == 3 && skt_पूर्णांकerleave_bit > chn_पूर्णांकerleave_bit) अणु
		/* Must handle channel first, then socket */
		channel_addr = skx_करो_पूर्णांकerleave(channel_addr, chn_पूर्णांकerleave_bit,
						 res->chanways, channel_addr);
		channel_addr = skx_करो_पूर्णांकerleave(channel_addr, skt_पूर्णांकerleave_bit,
						 res->sktways, channel_addr);
	पूर्ण अन्यथा अणु
		/* Handle socket then channel. Preserve low bits from original address */
		channel_addr = skx_करो_पूर्णांकerleave(channel_addr, skt_पूर्णांकerleave_bit,
						 res->sktways, res->addr);
		channel_addr = skx_करो_पूर्णांकerleave(channel_addr, chn_पूर्णांकerleave_bit,
						 res->chanways, res->addr);
	पूर्ण

	res->chan_addr = channel_addr;

	edac_dbg(2, "0x%llx: chan_addr=0x%llx sktways=%d chanways=%d\n",
		 res->addr, res->chan_addr, res->sktways, res->chanways);
	वापस true;
पूर्ण

#घोषणा SKX_MAX_RIR 4

#घोषणा SKX_GET_RIRWAYNESS(d, mc, ch, i, reg)		\
	pci_पढ़ो_config_dword((d)->imc[mc].chan[ch].cdev,	\
			      0x108 + 4 * (i), &(reg))
#घोषणा SKX_GET_RIRILV(d, mc, ch, idx, i, reg)		\
	pci_पढ़ो_config_dword((d)->imc[mc].chan[ch].cdev,	\
			      0x120 + 16 * (idx) + 4 * (i), &(reg))

#घोषणा	SKX_RIR_VALID(b) GET_BITFIELD((b), 31, 31)
#घोषणा	SKX_RIR_LIMIT(b) (((u64)GET_BITFIELD((b), 1, 11) << 29) | MASK29)
#घोषणा	SKX_RIR_WAYS(b) (1 << GET_BITFIELD((b), 28, 29))
#घोषणा	SKX_RIR_CHAN_RANK(b) GET_BITFIELD((b), 16, 19)
#घोषणा	SKX_RIR_OFFSET(b) ((u64)(GET_BITFIELD((b), 2, 15) << 26))

अटल bool skx_rir_decode(काष्ठा decoded_addr *res)
अणु
	पूर्णांक i, idx, chan_rank;
	पूर्णांक shअगरt;
	u32 rirway, rirlv;
	u64 rank_addr, prev_limit = 0, limit;

	अगर (res->dev->imc[res->imc].chan[res->channel].dimms[0].बंद_pg)
		shअगरt = 6;
	अन्यथा
		shअगरt = 13;

	क्रम (i = 0; i < SKX_MAX_RIR; i++) अणु
		SKX_GET_RIRWAYNESS(res->dev, res->imc, res->channel, i, rirway);
		limit = SKX_RIR_LIMIT(rirway);
		अगर (SKX_RIR_VALID(rirway)) अणु
			अगर (prev_limit <= res->chan_addr &&
			    res->chan_addr <= limit)
				जाओ rir_found;
		पूर्ण
		prev_limit = limit;
	पूर्ण
	edac_dbg(0, "No RIR entry for 0x%llx\n", res->addr);
	वापस false;

rir_found:
	rank_addr = res->chan_addr >> shअगरt;
	rank_addr /= SKX_RIR_WAYS(rirway);
	rank_addr <<= shअगरt;
	rank_addr |= res->chan_addr & GENMASK_ULL(shअगरt - 1, 0);

	res->rank_address = rank_addr;
	idx = (res->chan_addr >> shअगरt) % SKX_RIR_WAYS(rirway);

	SKX_GET_RIRILV(res->dev, res->imc, res->channel, idx, i, rirlv);
	res->rank_address = rank_addr - SKX_RIR_OFFSET(rirlv);
	chan_rank = SKX_RIR_CHAN_RANK(rirlv);
	res->channel_rank = chan_rank;
	res->dimm = chan_rank / 4;
	res->rank = chan_rank % 4;

	edac_dbg(2, "0x%llx: dimm=%d rank=%d chan_rank=%d rank_addr=0x%llx\n",
		 res->addr, res->dimm, res->rank,
		 res->channel_rank, res->rank_address);
	वापस true;
पूर्ण

अटल u8 skx_बंद_row[] = अणु
	15, 16, 17, 18, 20, 21, 22, 28, 10, 11, 12, 13, 29, 30, 31, 32, 33
पूर्ण;

अटल u8 skx_बंद_column[] = अणु
	3, 4, 5, 14, 19, 23, 24, 25, 26, 27
पूर्ण;

अटल u8 skx_खोलो_row[] = अणु
	14, 15, 16, 20, 28, 21, 22, 23, 24, 25, 26, 27, 29, 30, 31, 32, 33
पूर्ण;

अटल u8 skx_खोलो_column[] = अणु
	3, 4, 5, 6, 7, 8, 9, 10, 11, 12
पूर्ण;

अटल u8 skx_खोलो_fine_column[] = अणु
	3, 4, 5, 7, 8, 9, 10, 11, 12, 13
पूर्ण;

अटल पूर्णांक skx_bits(u64 addr, पूर्णांक nbits, u8 *bits)
अणु
	पूर्णांक i, res = 0;

	क्रम (i = 0; i < nbits; i++)
		res |= ((addr >> bits[i]) & 1) << i;
	वापस res;
पूर्ण

अटल पूर्णांक skx_bank_bits(u64 addr, पूर्णांक b0, पूर्णांक b1, पूर्णांक करो_xor, पूर्णांक x0, पूर्णांक x1)
अणु
	पूर्णांक ret = GET_BITFIELD(addr, b0, b0) | (GET_BITFIELD(addr, b1, b1) << 1);

	अगर (करो_xor)
		ret ^= GET_BITFIELD(addr, x0, x0) | (GET_BITFIELD(addr, x1, x1) << 1);

	वापस ret;
पूर्ण

अटल bool skx_mad_decode(काष्ठा decoded_addr *r)
अणु
	काष्ठा skx_dimm *dimm = &r->dev->imc[r->imc].chan[r->channel].dimms[r->dimm];
	पूर्णांक bg0 = dimm->fine_grain_bank ? 6 : 13;

	अगर (dimm->बंद_pg) अणु
		r->row = skx_bits(r->rank_address, dimm->rowbits, skx_बंद_row);
		r->column = skx_bits(r->rank_address, dimm->colbits, skx_बंद_column);
		r->column |= 0x400; /* C10 is स्वतःpreअक्षरge, always set */
		r->bank_address = skx_bank_bits(r->rank_address, 8, 9, dimm->bank_xor_enable, 22, 28);
		r->bank_group = skx_bank_bits(r->rank_address, 6, 7, dimm->bank_xor_enable, 20, 21);
	पूर्ण अन्यथा अणु
		r->row = skx_bits(r->rank_address, dimm->rowbits, skx_खोलो_row);
		अगर (dimm->fine_grain_bank)
			r->column = skx_bits(r->rank_address, dimm->colbits, skx_खोलो_fine_column);
		अन्यथा
			r->column = skx_bits(r->rank_address, dimm->colbits, skx_खोलो_column);
		r->bank_address = skx_bank_bits(r->rank_address, 18, 19, dimm->bank_xor_enable, 22, 23);
		r->bank_group = skx_bank_bits(r->rank_address, bg0, 17, dimm->bank_xor_enable, 20, 21);
	पूर्ण
	r->row &= (1u << dimm->rowbits) - 1;

	edac_dbg(2, "0x%llx: row=0x%x col=0x%x bank_addr=%d bank_group=%d\n",
		 r->addr, r->row, r->column, r->bank_address,
		 r->bank_group);
	वापस true;
पूर्ण

अटल bool skx_decode(काष्ठा decoded_addr *res)
अणु
	वापस skx_sad_decode(res) && skx_tad_decode(res) &&
		skx_rir_decode(res) && skx_mad_decode(res);
पूर्ण

अटल काष्ठा notअगरier_block skx_mce_dec = अणु
	.notअगरier_call	= skx_mce_check_error,
	.priority	= MCE_PRIO_EDAC,
पूर्ण;

#अगर_घोषित CONFIG_EDAC_DEBUG
/*
 * Debug feature.
 * Exercise the address decode logic by writing an address to
 * /sys/kernel/debug/edac/skx_test/addr.
 */
अटल काष्ठा dentry *skx_test;

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

अटल व्योम setup_skx_debug(व्योम)
अणु
	skx_test = edac_debugfs_create_dir("skx_test");
	अगर (!skx_test)
		वापस;

	अगर (!edac_debugfs_create_file("addr", 0200, skx_test,
				      शून्य, &fops_u64_wo)) अणु
		debugfs_हटाओ(skx_test);
		skx_test = शून्य;
	पूर्ण
पूर्ण

अटल व्योम tearकरोwn_skx_debug(व्योम)
अणु
	debugfs_हटाओ_recursive(skx_test);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम setup_skx_debug(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम tearकरोwn_skx_debug(व्योम) अणुपूर्ण
#पूर्ण_अगर /*CONFIG_EDAC_DEBUG*/

/*
 * skx_init:
 *	make sure we are running on the correct cpu model
 *	search क्रम all the devices we need
 *	check which DIMMs are present.
 */
अटल पूर्णांक __init skx_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	काष्ठा res_config *cfg;
	स्थिर काष्ठा munit *m;
	स्थिर अक्षर *owner;
	पूर्णांक rc = 0, i, off[3] = अणु0xd0, 0xd4, 0xd8पूर्ण;
	u8 mc = 0, src_id, node_id;
	काष्ठा skx_dev *d;

	edac_dbg(2, "\n");

	owner = edac_get_owner();
	अगर (owner && म_भेदन(owner, EDAC_MOD_STR, माप(EDAC_MOD_STR)))
		वापस -EBUSY;

	id = x86_match_cpu(skx_cpuids);
	अगर (!id)
		वापस -ENODEV;

	cfg = (काष्ठा res_config *)id->driver_data;

	rc = skx_get_hi_lo(0x2034, off, &skx_tolm, &skx_tohm);
	अगर (rc)
		वापस rc;

	rc = skx_get_all_bus_mappings(cfg, &skx_edac_list);
	अगर (rc < 0)
		जाओ fail;
	अगर (rc == 0) अणु
		edac_dbg(2, "No memory controllers found\n");
		वापस -ENODEV;
	पूर्ण
	skx_num_sockets = rc;

	क्रम (m = skx_all_munits; m->did; m++) अणु
		rc = get_all_munits(m);
		अगर (rc < 0)
			जाओ fail;
		अगर (rc != m->per_socket * skx_num_sockets) अणु
			edac_dbg(2, "Expected %d, got %d of 0x%x\n",
				 m->per_socket * skx_num_sockets, rc, m->did);
			rc = -ENODEV;
			जाओ fail;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(d, skx_edac_list, list) अणु
		rc = skx_get_src_id(d, 0xf0, &src_id);
		अगर (rc < 0)
			जाओ fail;
		rc = skx_get_node_id(d, &node_id);
		अगर (rc < 0)
			जाओ fail;
		edac_dbg(2, "src_id=%d node_id=%d\n", src_id, node_id);
		क्रम (i = 0; i < SKX_NUM_IMC; i++) अणु
			d->imc[i].mc = mc++;
			d->imc[i].lmc = i;
			d->imc[i].src_id = src_id;
			d->imc[i].node_id = node_id;
			rc = skx_रेजिस्टर_mci(&d->imc[i], d->imc[i].chan[0].cdev,
					      "Skylake Socket", EDAC_MOD_STR,
					      skx_get_dimm_config, cfg);
			अगर (rc < 0)
				जाओ fail;
		पूर्ण
	पूर्ण

	skx_set_decode(skx_decode, skx_show_retry_rd_err_log);

	अगर (nvdimm_count && skx_adxl_get() == -ENODEV)
		skx_prपूर्णांकk(KERN_NOTICE, "Only decoding DDR4 address!\n");

	/* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
	opstate_init();

	setup_skx_debug();

	mce_रेजिस्टर_decode_chain(&skx_mce_dec);

	वापस 0;
fail:
	skx_हटाओ();
	वापस rc;
पूर्ण

अटल व्योम __निकास skx_निकास(व्योम)
अणु
	edac_dbg(2, "\n");
	mce_unरेजिस्टर_decode_chain(&skx_mce_dec);
	tearकरोwn_skx_debug();
	अगर (nvdimm_count)
		skx_adxl_put();
	skx_हटाओ();
पूर्ण

module_init(skx_init);
module_निकास(skx_निकास);

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Tony Luck");
MODULE_DESCRIPTION("MC Driver for Intel Skylake server processors");
