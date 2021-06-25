<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Intel client SoC with पूर्णांकegrated memory controller using IBECC
 *
 * Copyright (C) 2020 Intel Corporation
 *
 * The In-Band ECC (IBECC) IP provides ECC protection to all or specअगरic
 * regions of the physical memory space. It's used क्रम memory controllers
 * that करोn't support the out-of-band ECC which often needs an additional
 * storage device to each channel क्रम storing ECC data.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/llist.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/edac.h>
#समावेश <linux/bits.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/mach_traps.h>
#समावेश <यंत्र/nmi.h>

#समावेश "edac_mc.h"
#समावेश "edac_module.h"

#घोषणा IGEN6_REVISION	"v2.4"

#घोषणा EDAC_MOD_STR	"igen6_edac"
#घोषणा IGEN6_NMI_NAME	"igen6_ibecc"

/* Debug macros */
#घोषणा igen6_prपूर्णांकk(level, fmt, arg...)		\
	edac_prपूर्णांकk(level, "igen6", fmt, ##arg)

#घोषणा igen6_mc_prपूर्णांकk(mci, level, fmt, arg...)	\
	edac_mc_chipset_prपूर्णांकk(mci, level, "igen6", fmt, ##arg)

#घोषणा GET_BITFIELD(v, lo, hi) (((v) & GENMASK_ULL(hi, lo)) >> (lo))

#घोषणा NUM_IMC				1 /* Max memory controllers */
#घोषणा NUM_CHANNELS			2 /* Max channels */
#घोषणा NUM_DIMMS			2 /* Max DIMMs per channel */

#घोषणा _4GB				BIT_ULL(32)

/* Size of physical memory */
#घोषणा TOM_OFFSET			0xa0
/* Top of low usable DRAM */
#घोषणा TOLUD_OFFSET			0xbc
/* Capability रेजिस्टर C */
#घोषणा CAPID_C_OFFSET			0xec
#घोषणा CAPID_C_IBECC			BIT(15)

/* Error Status */
#घोषणा ERRSTS_OFFSET			0xc8
#घोषणा ERRSTS_CE			BIT_ULL(6)
#घोषणा ERRSTS_UE			BIT_ULL(7)

/* Error Command */
#घोषणा ERRCMD_OFFSET			0xca
#घोषणा ERRCMD_CE			BIT_ULL(6)
#घोषणा ERRCMD_UE			BIT_ULL(7)

/* IBECC MMIO base address */
#घोषणा IBECC_BASE			(res_cfg->ibecc_base)
#घोषणा IBECC_ACTIVATE_OFFSET		IBECC_BASE
#घोषणा IBECC_ACTIVATE_EN		BIT(0)

/* IBECC error log */
#घोषणा ECC_ERROR_LOG_OFFSET		(IBECC_BASE + 0x170)
#घोषणा ECC_ERROR_LOG_CE		BIT_ULL(62)
#घोषणा ECC_ERROR_LOG_UE		BIT_ULL(63)
#घोषणा ECC_ERROR_LOG_ADDR_SHIFT	5
#घोषणा ECC_ERROR_LOG_ADDR(v)		GET_BITFIELD(v, 5, 38)
#घोषणा ECC_ERROR_LOG_SYND(v)		GET_BITFIELD(v, 46, 61)

/* Host MMIO base address */
#घोषणा MCHBAR_OFFSET			0x48
#घोषणा MCHBAR_EN			BIT_ULL(0)
#घोषणा MCHBAR_BASE(v)			(GET_BITFIELD(v, 16, 38) << 16)
#घोषणा MCHBAR_SIZE			0x10000

/* Parameters क्रम the channel decode stage */
#घोषणा MAD_INTER_CHANNEL_OFFSET	0x5000
#घोषणा MAD_INTER_CHANNEL_DDR_TYPE(v)	GET_BITFIELD(v, 0, 2)
#घोषणा MAD_INTER_CHANNEL_ECHM(v)	GET_BITFIELD(v, 3, 3)
#घोषणा MAD_INTER_CHANNEL_CH_L_MAP(v)	GET_BITFIELD(v, 4, 4)
#घोषणा MAD_INTER_CHANNEL_CH_S_SIZE(v)	((u64)GET_BITFIELD(v, 12, 19) << 29)

/* Parameters क्रम DRAM decode stage */
#घोषणा MAD_INTRA_CH0_OFFSET		0x5004
#घोषणा MAD_INTRA_CH_DIMM_L_MAP(v)	GET_BITFIELD(v, 0, 0)

/* DIMM अक्षरacteristics */
#घोषणा MAD_DIMM_CH0_OFFSET		0x500c
#घोषणा MAD_DIMM_CH_DIMM_L_SIZE(v)	((u64)GET_BITFIELD(v, 0, 6) << 29)
#घोषणा MAD_DIMM_CH_DLW(v)		GET_BITFIELD(v, 7, 8)
#घोषणा MAD_DIMM_CH_DIMM_S_SIZE(v)	((u64)GET_BITFIELD(v, 16, 22) << 29)
#घोषणा MAD_DIMM_CH_DSW(v)		GET_BITFIELD(v, 24, 25)

/* Hash क्रम channel selection */
#घोषणा CHANNEL_HASH_OFFSET		0X5024
/* Hash क्रम enhanced channel selection */
#घोषणा CHANNEL_EHASH_OFFSET		0X5028
#घोषणा CHANNEL_HASH_MASK(v)		(GET_BITFIELD(v, 6, 19) << 6)
#घोषणा CHANNEL_HASH_LSB_MASK_BIT(v)	GET_BITFIELD(v, 24, 26)
#घोषणा CHANNEL_HASH_MODE(v)		GET_BITFIELD(v, 28, 28)

अटल काष्ठा res_config अणु
	पूर्णांक num_imc;
	u32 ibecc_base;
	bool (*ibecc_available)(काष्ठा pci_dev *pdev);
	/* Convert error address logged in IBECC to प्रणाली physical address */
	u64 (*err_addr_to_sys_addr)(u64 eaddr);
	/* Convert error address logged in IBECC to पूर्णांकegrated memory controller address */
	u64 (*err_addr_to_imc_addr)(u64 eaddr);
पूर्ण *res_cfg;

काष्ठा igen6_imc अणु
	पूर्णांक mc;
	काष्ठा mem_ctl_info *mci;
	काष्ठा pci_dev *pdev;
	काष्ठा device dev;
	व्योम __iomem *winकरोw;
	u64 ch_s_size;
	पूर्णांक ch_l_map;
	u64 dimm_s_size[NUM_CHANNELS];
	u64 dimm_l_size[NUM_CHANNELS];
	पूर्णांक dimm_l_map[NUM_CHANNELS];
पूर्ण;

अटल काष्ठा igen6_pvt अणु
	काष्ठा igen6_imc imc[NUM_IMC];
पूर्ण *igen6_pvt;

/* The top of low usable DRAM */
अटल u32 igen6_tolud;
/* The size of physical memory */
अटल u64 igen6_tom;

काष्ठा decoded_addr अणु
	पूर्णांक mc;
	u64 imc_addr;
	u64 sys_addr;
	पूर्णांक channel_idx;
	u64 channel_addr;
	पूर्णांक sub_channel_idx;
	u64 sub_channel_addr;
पूर्ण;

काष्ठा ecclog_node अणु
	काष्ठा llist_node llnode;
	पूर्णांक mc;
	u64 ecclog;
पूर्ण;

/*
 * In the NMI handler, the driver uses the lock-less memory allocator
 * to allocate memory to store the IBECC error logs and links the logs
 * to the lock-less list. Delay prपूर्णांकk() and the work of error reporting
 * to EDAC core in a worker.
 */
#घोषणा ECCLOG_POOL_SIZE	PAGE_SIZE
अटल LLIST_HEAD(ecclog_llist);
अटल काष्ठा gen_pool *ecclog_pool;
अटल अक्षर ecclog_buf[ECCLOG_POOL_SIZE];
अटल काष्ठा irq_work ecclog_irq_work;
अटल काष्ठा work_काष्ठा ecclog_work;

/* Compute die IDs क्रम Elkhart Lake with IBECC */
#घोषणा DID_EHL_SKU5	0x4514
#घोषणा DID_EHL_SKU6	0x4528
#घोषणा DID_EHL_SKU7	0x452a
#घोषणा DID_EHL_SKU8	0x4516
#घोषणा DID_EHL_SKU9	0x452c
#घोषणा DID_EHL_SKU10	0x452e
#घोषणा DID_EHL_SKU11	0x4532
#घोषणा DID_EHL_SKU12	0x4518
#घोषणा DID_EHL_SKU13	0x451a
#घोषणा DID_EHL_SKU14	0x4534
#घोषणा DID_EHL_SKU15	0x4536

अटल bool ehl_ibecc_available(काष्ठा pci_dev *pdev)
अणु
	u32 v;

	अगर (pci_पढ़ो_config_dword(pdev, CAPID_C_OFFSET, &v))
		वापस false;

	वापस !!(CAPID_C_IBECC & v);
पूर्ण

अटल u64 ehl_err_addr_to_sys_addr(u64 eaddr)
अणु
	वापस eaddr;
पूर्ण

अटल u64 ehl_err_addr_to_imc_addr(u64 eaddr)
अणु
	अगर (eaddr < igen6_tolud)
		वापस eaddr;

	अगर (igen6_tom <= _4GB)
		वापस eaddr + igen6_tolud - _4GB;

	अगर (eaddr < _4GB)
		वापस eaddr + igen6_tolud - igen6_tom;

	वापस eaddr;
पूर्ण

अटल काष्ठा res_config ehl_cfg = अणु
	.num_imc	 = 1,
	.ibecc_base	 = 0xdc00,
	.ibecc_available = ehl_ibecc_available,
	.err_addr_to_sys_addr  = ehl_err_addr_to_sys_addr,
	.err_addr_to_imc_addr  = ehl_err_addr_to_imc_addr,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id igen6_pci_tbl[] = अणु
	अणु PCI_VDEVICE(INTEL, DID_EHL_SKU5), (kernel_uदीर्घ_t)&ehl_cfg पूर्ण,
	अणु PCI_VDEVICE(INTEL, DID_EHL_SKU6), (kernel_uदीर्घ_t)&ehl_cfg पूर्ण,
	अणु PCI_VDEVICE(INTEL, DID_EHL_SKU7), (kernel_uदीर्घ_t)&ehl_cfg पूर्ण,
	अणु PCI_VDEVICE(INTEL, DID_EHL_SKU8), (kernel_uदीर्घ_t)&ehl_cfg पूर्ण,
	अणु PCI_VDEVICE(INTEL, DID_EHL_SKU9), (kernel_uदीर्घ_t)&ehl_cfg पूर्ण,
	अणु PCI_VDEVICE(INTEL, DID_EHL_SKU10), (kernel_uदीर्घ_t)&ehl_cfg पूर्ण,
	अणु PCI_VDEVICE(INTEL, DID_EHL_SKU11), (kernel_uदीर्घ_t)&ehl_cfg पूर्ण,
	अणु PCI_VDEVICE(INTEL, DID_EHL_SKU12), (kernel_uदीर्घ_t)&ehl_cfg पूर्ण,
	अणु PCI_VDEVICE(INTEL, DID_EHL_SKU13), (kernel_uदीर्घ_t)&ehl_cfg पूर्ण,
	अणु PCI_VDEVICE(INTEL, DID_EHL_SKU14), (kernel_uदीर्घ_t)&ehl_cfg पूर्ण,
	अणु PCI_VDEVICE(INTEL, DID_EHL_SKU15), (kernel_uदीर्घ_t)&ehl_cfg पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, igen6_pci_tbl);

अटल क्रमागत dev_type get_width(पूर्णांक dimm_l, u32 mad_dimm)
अणु
	u32 w = dimm_l ? MAD_DIMM_CH_DLW(mad_dimm) :
			 MAD_DIMM_CH_DSW(mad_dimm);

	चयन (w) अणु
	हाल 0:
		वापस DEV_X8;
	हाल 1:
		वापस DEV_X16;
	हाल 2:
		वापस DEV_X32;
	शेष:
		वापस DEV_UNKNOWN;
	पूर्ण
पूर्ण

अटल क्रमागत mem_type get_memory_type(u32 mad_पूर्णांकer)
अणु
	u32 t = MAD_INTER_CHANNEL_DDR_TYPE(mad_पूर्णांकer);

	चयन (t) अणु
	हाल 0:
		वापस MEM_DDR4;
	हाल 1:
		वापस MEM_DDR3;
	हाल 2:
		वापस MEM_LPDDR3;
	हाल 3:
		वापस MEM_LPDDR4;
	हाल 4:
		वापस MEM_WIO2;
	शेष:
		वापस MEM_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक decode_chan_idx(u64 addr, u64 mask, पूर्णांक पूर्णांकlv_bit)
अणु
	u64 hash_addr = addr & mask, hash = 0;
	u64 पूर्णांकlv = (addr >> पूर्णांकlv_bit) & 1;
	पूर्णांक i;

	क्रम (i = 6; i < 20; i++)
		hash ^= (hash_addr >> i) & 1;

	वापस (पूर्णांक)hash ^ पूर्णांकlv;
पूर्ण

अटल u64 decode_channel_addr(u64 addr, पूर्णांक पूर्णांकlv_bit)
अणु
	u64 channel_addr;

	/* Remove the पूर्णांकerleave bit and shअगरt upper part करोwn to fill gap */
	channel_addr  = GET_BITFIELD(addr, पूर्णांकlv_bit + 1, 63) << पूर्णांकlv_bit;
	channel_addr |= GET_BITFIELD(addr, 0, पूर्णांकlv_bit - 1);

	वापस channel_addr;
पूर्ण

अटल व्योम decode_addr(u64 addr, u32 hash, u64 s_size, पूर्णांक l_map,
			पूर्णांक *idx, u64 *sub_addr)
अणु
	पूर्णांक पूर्णांकlv_bit = CHANNEL_HASH_LSB_MASK_BIT(hash) + 6;

	अगर (addr > 2 * s_size) अणु
		*sub_addr = addr - s_size;
		*idx = l_map;
		वापस;
	पूर्ण

	अगर (CHANNEL_HASH_MODE(hash)) अणु
		*sub_addr = decode_channel_addr(addr, पूर्णांकlv_bit);
		*idx = decode_chan_idx(addr, CHANNEL_HASH_MASK(hash), पूर्णांकlv_bit);
	पूर्ण अन्यथा अणु
		*sub_addr = decode_channel_addr(addr, 6);
		*idx = GET_BITFIELD(addr, 6, 6);
	पूर्ण
पूर्ण

अटल पूर्णांक igen6_decode(काष्ठा decoded_addr *res)
अणु
	काष्ठा igen6_imc *imc = &igen6_pvt->imc[res->mc];
	u64 addr = res->imc_addr, sub_addr, s_size;
	पूर्णांक idx, l_map;
	u32 hash;

	अगर (addr >= igen6_tom) अणु
		edac_dbg(0, "Address 0x%llx out of range\n", addr);
		वापस -EINVAL;
	पूर्ण

	/* Decode channel */
	hash   = पढ़ोl(imc->winकरोw + CHANNEL_HASH_OFFSET);
	s_size = imc->ch_s_size;
	l_map  = imc->ch_l_map;
	decode_addr(addr, hash, s_size, l_map, &idx, &sub_addr);
	res->channel_idx  = idx;
	res->channel_addr = sub_addr;

	/* Decode sub-channel/DIMM */
	hash   = पढ़ोl(imc->winकरोw + CHANNEL_EHASH_OFFSET);
	s_size = imc->dimm_s_size[idx];
	l_map  = imc->dimm_l_map[idx];
	decode_addr(res->channel_addr, hash, s_size, l_map, &idx, &sub_addr);
	res->sub_channel_idx  = idx;
	res->sub_channel_addr = sub_addr;

	वापस 0;
पूर्ण

अटल व्योम igen6_output_error(काष्ठा decoded_addr *res,
			       काष्ठा mem_ctl_info *mci, u64 ecclog)
अणु
	क्रमागत hw_event_mc_err_type type = ecclog & ECC_ERROR_LOG_UE ?
					 HW_EVENT_ERR_UNCORRECTED :
					 HW_EVENT_ERR_CORRECTED;

	edac_mc_handle_error(type, mci, 1,
			     res->sys_addr >> PAGE_SHIFT,
			     res->sys_addr & ~PAGE_MASK,
			     ECC_ERROR_LOG_SYND(ecclog),
			     res->channel_idx, res->sub_channel_idx,
			     -1, "", "");
पूर्ण

अटल काष्ठा gen_pool *ecclog_gen_pool_create(व्योम)
अणु
	काष्ठा gen_pool *pool;

	pool = gen_pool_create(ilog2(माप(काष्ठा ecclog_node)), -1);
	अगर (!pool)
		वापस शून्य;

	अगर (gen_pool_add(pool, (अचिन्हित दीर्घ)ecclog_buf, ECCLOG_POOL_SIZE, -1)) अणु
		gen_pool_destroy(pool);
		वापस शून्य;
	पूर्ण

	वापस pool;
पूर्ण

अटल पूर्णांक ecclog_gen_pool_add(पूर्णांक mc, u64 ecclog)
अणु
	काष्ठा ecclog_node *node;

	node = (व्योम *)gen_pool_alloc(ecclog_pool, माप(*node));
	अगर (!node)
		वापस -ENOMEM;

	node->mc = mc;
	node->ecclog = ecclog;
	llist_add(&node->llnode, &ecclog_llist);

	वापस 0;
पूर्ण

/*
 * Either the memory-mapped I/O status रेजिस्टर ECC_ERROR_LOG or the PCI
 * configuration space status रेजिस्टर ERRSTS can indicate whether a
 * correctable error or an uncorrectable error occurred. We only use the
 * ECC_ERROR_LOG रेजिस्टर to check error type, but need to clear both
 * रेजिस्टरs to enable future error events.
 */
अटल u64 ecclog_पढ़ो_and_clear(काष्ठा igen6_imc *imc)
अणु
	u64 ecclog = पढ़ोq(imc->winकरोw + ECC_ERROR_LOG_OFFSET);

	अगर (ecclog & (ECC_ERROR_LOG_CE | ECC_ERROR_LOG_UE)) अणु
		/* Clear CE/UE bits by writing 1s */
		ग_लिखोq(ecclog, imc->winकरोw + ECC_ERROR_LOG_OFFSET);
		वापस ecclog;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम errsts_clear(काष्ठा igen6_imc *imc)
अणु
	u16 errsts;

	अगर (pci_पढ़ो_config_word(imc->pdev, ERRSTS_OFFSET, &errsts)) अणु
		igen6_prपूर्णांकk(KERN_ERR, "Failed to read ERRSTS\n");
		वापस;
	पूर्ण

	/* Clear CE/UE bits by writing 1s */
	अगर (errsts & (ERRSTS_CE | ERRSTS_UE))
		pci_ग_लिखो_config_word(imc->pdev, ERRSTS_OFFSET, errsts);
पूर्ण

अटल पूर्णांक errcmd_enable_error_reporting(bool enable)
अणु
	काष्ठा igen6_imc *imc = &igen6_pvt->imc[0];
	u16 errcmd;
	पूर्णांक rc;

	rc = pci_पढ़ो_config_word(imc->pdev, ERRCMD_OFFSET, &errcmd);
	अगर (rc)
		वापस rc;

	अगर (enable)
		errcmd |= ERRCMD_CE | ERRSTS_UE;
	अन्यथा
		errcmd &= ~(ERRCMD_CE | ERRSTS_UE);

	rc = pci_ग_लिखो_config_word(imc->pdev, ERRCMD_OFFSET, errcmd);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक ecclog_handler(व्योम)
अणु
	काष्ठा igen6_imc *imc;
	पूर्णांक i, n = 0;
	u64 ecclog;

	क्रम (i = 0; i < res_cfg->num_imc; i++) अणु
		imc = &igen6_pvt->imc[i];

		/* errsts_clear() isn't NMI-safe. Delay it in the IRQ context */

		ecclog = ecclog_पढ़ो_and_clear(imc);
		अगर (!ecclog)
			जारी;

		अगर (!ecclog_gen_pool_add(i, ecclog))
			irq_work_queue(&ecclog_irq_work);

		n++;
	पूर्ण

	वापस n;
पूर्ण

अटल व्योम ecclog_work_cb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ecclog_node *node, *पंचांगp;
	काष्ठा mem_ctl_info *mci;
	काष्ठा llist_node *head;
	काष्ठा decoded_addr res;
	u64 eaddr;

	head = llist_del_all(&ecclog_llist);
	अगर (!head)
		वापस;

	llist_क्रम_each_entry_safe(node, पंचांगp, head, llnode) अणु
		स_रखो(&res, 0, माप(res));
		eaddr = ECC_ERROR_LOG_ADDR(node->ecclog) <<
			ECC_ERROR_LOG_ADDR_SHIFT;
		res.mc	     = node->mc;
		res.sys_addr = res_cfg->err_addr_to_sys_addr(eaddr);
		res.imc_addr = res_cfg->err_addr_to_imc_addr(eaddr);

		mci = igen6_pvt->imc[res.mc].mci;

		edac_dbg(2, "MC %d, ecclog = 0x%llx\n", node->mc, node->ecclog);
		igen6_mc_prपूर्णांकk(mci, KERN_DEBUG, "HANDLING IBECC MEMORY ERROR\n");
		igen6_mc_prपूर्णांकk(mci, KERN_DEBUG, "ADDR 0x%llx ", res.sys_addr);

		अगर (!igen6_decode(&res))
			igen6_output_error(&res, mci, node->ecclog);

		gen_pool_मुक्त(ecclog_pool, (अचिन्हित दीर्घ)node, माप(*node));
	पूर्ण
पूर्ण

अटल व्योम ecclog_irq_work_cb(काष्ठा irq_work *irq_work)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < res_cfg->num_imc; i++)
		errsts_clear(&igen6_pvt->imc[i]);

	अगर (!llist_empty(&ecclog_llist))
		schedule_work(&ecclog_work);
पूर्ण

अटल पूर्णांक ecclog_nmi_handler(अचिन्हित पूर्णांक cmd, काष्ठा pt_regs *regs)
अणु
	अचिन्हित अक्षर reason;

	अगर (!ecclog_handler())
		वापस NMI_DONE;

	/*
	 * Both In-Band ECC correctable error and uncorrectable error are
	 * reported by SERR# NMI. The NMI generic code (see pci_serr_error())
	 * करोesn't clear the bit NMI_REASON_CLEAR_SERR (in port 0x61) to
	 * re-enable the SERR# NMI after NMI handling. So clear this bit here
	 * to re-enable SERR# NMI क्रम receiving future In-Band ECC errors.
	 */
	reason  = x86_platक्रमm.get_nmi_reason() & NMI_REASON_CLEAR_MASK;
	reason |= NMI_REASON_CLEAR_SERR;
	outb(reason, NMI_REASON_PORT);
	reason &= ~NMI_REASON_CLEAR_SERR;
	outb(reason, NMI_REASON_PORT);

	वापस NMI_HANDLED;
पूर्ण

अटल bool igen6_check_ecc(काष्ठा igen6_imc *imc)
अणु
	u32 activate = पढ़ोl(imc->winकरोw + IBECC_ACTIVATE_OFFSET);

	वापस !!(activate & IBECC_ACTIVATE_EN);
पूर्ण

अटल पूर्णांक igen6_get_dimm_config(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा igen6_imc *imc = mci->pvt_info;
	u32 mad_पूर्णांकer, mad_पूर्णांकra, mad_dimm;
	पूर्णांक i, j, ndimms, mc = imc->mc;
	काष्ठा dimm_info *dimm;
	क्रमागत mem_type mtype;
	क्रमागत dev_type dtype;
	u64 dsize;
	bool ecc;

	edac_dbg(2, "\n");

	mad_पूर्णांकer = पढ़ोl(imc->winकरोw + MAD_INTER_CHANNEL_OFFSET);
	mtype = get_memory_type(mad_पूर्णांकer);
	ecc = igen6_check_ecc(imc);
	imc->ch_s_size = MAD_INTER_CHANNEL_CH_S_SIZE(mad_पूर्णांकer);
	imc->ch_l_map  = MAD_INTER_CHANNEL_CH_L_MAP(mad_पूर्णांकer);

	क्रम (i = 0; i < NUM_CHANNELS; i++) अणु
		mad_पूर्णांकra = पढ़ोl(imc->winकरोw + MAD_INTRA_CH0_OFFSET + i * 4);
		mad_dimm  = पढ़ोl(imc->winकरोw + MAD_DIMM_CH0_OFFSET + i * 4);

		imc->dimm_l_size[i] = MAD_DIMM_CH_DIMM_L_SIZE(mad_dimm);
		imc->dimm_s_size[i] = MAD_DIMM_CH_DIMM_S_SIZE(mad_dimm);
		imc->dimm_l_map[i]  = MAD_INTRA_CH_DIMM_L_MAP(mad_पूर्णांकra);
		ndimms = 0;

		क्रम (j = 0; j < NUM_DIMMS; j++) अणु
			dimm = edac_get_dimm(mci, i, j, 0);

			अगर (j ^ imc->dimm_l_map[i]) अणु
				dtype = get_width(0, mad_dimm);
				dsize = imc->dimm_s_size[i];
			पूर्ण अन्यथा अणु
				dtype = get_width(1, mad_dimm);
				dsize = imc->dimm_l_size[i];
			पूर्ण

			अगर (!dsize)
				जारी;

			dimm->grain = 64;
			dimm->mtype = mtype;
			dimm->dtype = dtype;
			dimm->nr_pages  = MiB_TO_PAGES(dsize >> 20);
			dimm->edac_mode = EDAC_SECDED;
			snम_लिखो(dimm->label, माप(dimm->label),
				 "MC#%d_Chan#%d_DIMM#%d", mc, i, j);
			edac_dbg(0, "MC %d, Channel %d, DIMM %d, Size %llu MiB (%u pages)\n",
				 mc, i, j, dsize >> 20, dimm->nr_pages);

			ndimms++;
		पूर्ण

		अगर (ndimms && !ecc) अणु
			igen6_prपूर्णांकk(KERN_ERR, "MC%d In-Band ECC is disabled\n", mc);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_EDAC_DEBUG
/* Top of upper usable DRAM */
अटल u64 igen6_touud;
#घोषणा TOUUD_OFFSET	0xa8

अटल व्योम igen6_reg_dump(काष्ठा igen6_imc *imc)
अणु
	पूर्णांक i;

	edac_dbg(2, "CHANNEL_HASH     : 0x%x\n",
		 पढ़ोl(imc->winकरोw + CHANNEL_HASH_OFFSET));
	edac_dbg(2, "CHANNEL_EHASH    : 0x%x\n",
		 पढ़ोl(imc->winकरोw + CHANNEL_EHASH_OFFSET));
	edac_dbg(2, "MAD_INTER_CHANNEL: 0x%x\n",
		 पढ़ोl(imc->winकरोw + MAD_INTER_CHANNEL_OFFSET));
	edac_dbg(2, "ECC_ERROR_LOG    : 0x%llx\n",
		 पढ़ोq(imc->winकरोw + ECC_ERROR_LOG_OFFSET));

	क्रम (i = 0; i < NUM_CHANNELS; i++) अणु
		edac_dbg(2, "MAD_INTRA_CH%d    : 0x%x\n", i,
			 पढ़ोl(imc->winकरोw + MAD_INTRA_CH0_OFFSET + i * 4));
		edac_dbg(2, "MAD_DIMM_CH%d     : 0x%x\n", i,
			 पढ़ोl(imc->winकरोw + MAD_DIMM_CH0_OFFSET + i * 4));
	पूर्ण
	edac_dbg(2, "TOLUD            : 0x%x", igen6_tolud);
	edac_dbg(2, "TOUUD            : 0x%llx", igen6_touud);
	edac_dbg(2, "TOM              : 0x%llx", igen6_tom);
पूर्ण

अटल काष्ठा dentry *igen6_test;

अटल पूर्णांक debugfs_u64_set(व्योम *data, u64 val)
अणु
	u64 ecclog;

	अगर ((val >= igen6_tolud && val < _4GB) || val >= igen6_touud) अणु
		edac_dbg(0, "Address 0x%llx out of range\n", val);
		वापस 0;
	पूर्ण

	pr_warn_once("Fake error to 0x%llx injected via debugfs\n", val);

	val  >>= ECC_ERROR_LOG_ADDR_SHIFT;
	ecclog = (val << ECC_ERROR_LOG_ADDR_SHIFT) | ECC_ERROR_LOG_CE;

	अगर (!ecclog_gen_pool_add(0, ecclog))
		irq_work_queue(&ecclog_irq_work);

	वापस 0;
पूर्ण
DEFINE_SIMPLE_ATTRIBUTE(fops_u64_wo, शून्य, debugfs_u64_set, "%llu\n");

अटल व्योम igen6_debug_setup(व्योम)
अणु
	igen6_test = edac_debugfs_create_dir("igen6_test");
	अगर (!igen6_test)
		वापस;

	अगर (!edac_debugfs_create_file("addr", 0200, igen6_test,
				      शून्य, &fops_u64_wo)) अणु
		debugfs_हटाओ(igen6_test);
		igen6_test = शून्य;
	पूर्ण
पूर्ण

अटल व्योम igen6_debug_tearकरोwn(व्योम)
अणु
	debugfs_हटाओ_recursive(igen6_test);
पूर्ण
#अन्यथा
अटल व्योम igen6_reg_dump(काष्ठा igen6_imc *imc) अणुपूर्ण
अटल व्योम igen6_debug_setup(व्योम) अणुपूर्ण
अटल व्योम igen6_debug_tearकरोwn(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक igen6_pci_setup(काष्ठा pci_dev *pdev, u64 *mchbar)
अणु
	जोड़  अणु
		u64 v;
		काष्ठा अणु
			u32 v_lo;
			u32 v_hi;
		पूर्ण;
	पूर्ण u;

	edac_dbg(2, "\n");

	अगर (!res_cfg->ibecc_available(pdev)) अणु
		edac_dbg(2, "No In-Band ECC IP\n");
		जाओ fail;
	पूर्ण

	अगर (pci_पढ़ो_config_dword(pdev, TOLUD_OFFSET, &igen6_tolud)) अणु
		igen6_prपूर्णांकk(KERN_ERR, "Failed to read TOLUD\n");
		जाओ fail;
	पूर्ण

	igen6_tolud &= GENMASK(31, 20);

	अगर (pci_पढ़ो_config_dword(pdev, TOM_OFFSET, &u.v_lo)) अणु
		igen6_prपूर्णांकk(KERN_ERR, "Failed to read lower TOM\n");
		जाओ fail;
	पूर्ण

	अगर (pci_पढ़ो_config_dword(pdev, TOM_OFFSET + 4, &u.v_hi)) अणु
		igen6_prपूर्णांकk(KERN_ERR, "Failed to read upper TOM\n");
		जाओ fail;
	पूर्ण

	igen6_tom = u.v & GENMASK_ULL(38, 20);

	अगर (pci_पढ़ो_config_dword(pdev, MCHBAR_OFFSET, &u.v_lo)) अणु
		igen6_prपूर्णांकk(KERN_ERR, "Failed to read lower MCHBAR\n");
		जाओ fail;
	पूर्ण

	अगर (pci_पढ़ो_config_dword(pdev, MCHBAR_OFFSET + 4, &u.v_hi)) अणु
		igen6_prपूर्णांकk(KERN_ERR, "Failed to read upper MCHBAR\n");
		जाओ fail;
	पूर्ण

	अगर (!(u.v & MCHBAR_EN)) अणु
		igen6_prपूर्णांकk(KERN_ERR, "MCHBAR is disabled\n");
		जाओ fail;
	पूर्ण

	*mchbar = MCHBAR_BASE(u.v);

#अगर_घोषित CONFIG_EDAC_DEBUG
	अगर (pci_पढ़ो_config_dword(pdev, TOUUD_OFFSET, &u.v_lo))
		edac_dbg(2, "Failed to read lower TOUUD\n");
	अन्यथा अगर (pci_पढ़ो_config_dword(pdev, TOUUD_OFFSET + 4, &u.v_hi))
		edac_dbg(2, "Failed to read upper TOUUD\n");
	अन्यथा
		igen6_touud = u.v & GENMASK_ULL(38, 20);
#पूर्ण_अगर

	वापस 0;
fail:
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक igen6_रेजिस्टर_mci(पूर्णांक mc, u64 mchbar, काष्ठा pci_dev *pdev)
अणु
	काष्ठा edac_mc_layer layers[2];
	काष्ठा mem_ctl_info *mci;
	काष्ठा igen6_imc *imc;
	व्योम __iomem *winकरोw;
	पूर्णांक rc;

	edac_dbg(2, "\n");

	mchbar += mc * MCHBAR_SIZE;
	winकरोw = ioremap(mchbar, MCHBAR_SIZE);
	अगर (!winकरोw) अणु
		igen6_prपूर्णांकk(KERN_ERR, "Failed to ioremap 0x%llx\n", mchbar);
		वापस -ENODEV;
	पूर्ण

	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = NUM_CHANNELS;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_SLOT;
	layers[1].size = NUM_DIMMS;
	layers[1].is_virt_csrow = true;

	mci = edac_mc_alloc(mc, ARRAY_SIZE(layers), layers, 0);
	अगर (!mci) अणु
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण

	mci->ctl_name = kaप्र_लिखो(GFP_KERNEL, "Intel_client_SoC MC#%d", mc);
	अगर (!mci->ctl_name) अणु
		rc = -ENOMEM;
		जाओ fail2;
	पूर्ण

	mci->mtype_cap = MEM_FLAG_LPDDR4 | MEM_FLAG_DDR4;
	mci->edac_ctl_cap = EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->mod_name = EDAC_MOD_STR;
	mci->dev_name = pci_name(pdev);
	mci->pvt_info = &igen6_pvt->imc[mc];

	imc = mci->pvt_info;
	device_initialize(&imc->dev);
	/*
	 * EDAC core uses mci->pdev(poपूर्णांकer of काष्ठाure device) as
	 * memory controller ID. The client SoCs attach one or more
	 * memory controllers to single pci_dev (single pci_dev->dev
	 * can be क्रम multiple memory controllers).
	 *
	 * To make mci->pdev unique, assign pci_dev->dev to mci->pdev
	 * क्रम the first memory controller and assign a unique imc->dev
	 * to mci->pdev क्रम each non-first memory controller.
	 */
	mci->pdev = mc ? &imc->dev : &pdev->dev;
	imc->mc	= mc;
	imc->pdev = pdev;
	imc->winकरोw = winकरोw;

	igen6_reg_dump(imc);

	rc = igen6_get_dimm_config(mci);
	अगर (rc)
		जाओ fail3;

	rc = edac_mc_add_mc(mci);
	अगर (rc) अणु
		igen6_prपूर्णांकk(KERN_ERR, "Failed to register mci#%d\n", mc);
		जाओ fail3;
	पूर्ण

	imc->mci = mci;
	वापस 0;
fail3:
	kमुक्त(mci->ctl_name);
fail2:
	edac_mc_मुक्त(mci);
fail:
	iounmap(winकरोw);
	वापस rc;
पूर्ण

अटल व्योम igen6_unरेजिस्टर_mcis(व्योम)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा igen6_imc *imc;
	पूर्णांक i;

	edac_dbg(2, "\n");

	क्रम (i = 0; i < res_cfg->num_imc; i++) अणु
		imc = &igen6_pvt->imc[i];
		mci = imc->mci;
		अगर (!mci)
			जारी;

		edac_mc_del_mc(mci->pdev);
		kमुक्त(mci->ctl_name);
		edac_mc_मुक्त(mci);
		iounmap(imc->winकरोw);
	पूर्ण
पूर्ण

अटल पूर्णांक igen6_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	u64 mchbar;
	पूर्णांक i, rc;

	edac_dbg(2, "\n");

	igen6_pvt = kzalloc(माप(*igen6_pvt), GFP_KERNEL);
	अगर (!igen6_pvt)
		वापस -ENOMEM;

	res_cfg = (काष्ठा res_config *)ent->driver_data;

	rc = igen6_pci_setup(pdev, &mchbar);
	अगर (rc)
		जाओ fail;

	क्रम (i = 0; i < res_cfg->num_imc; i++) अणु
		rc = igen6_रेजिस्टर_mci(i, mchbar, pdev);
		अगर (rc)
			जाओ fail2;
	पूर्ण

	ecclog_pool = ecclog_gen_pool_create();
	अगर (!ecclog_pool) अणु
		rc = -ENOMEM;
		जाओ fail2;
	पूर्ण

	INIT_WORK(&ecclog_work, ecclog_work_cb);
	init_irq_work(&ecclog_irq_work, ecclog_irq_work_cb);

	/* Check अगर any pending errors beक्रमe रेजिस्टरing the NMI handler */
	ecclog_handler();

	rc = रेजिस्टर_nmi_handler(NMI_SERR, ecclog_nmi_handler,
				  0, IGEN6_NMI_NAME);
	अगर (rc) अणु
		igen6_prपूर्णांकk(KERN_ERR, "Failed to register NMI handler\n");
		जाओ fail3;
	पूर्ण

	/* Enable error reporting */
	rc = errcmd_enable_error_reporting(true);
	अगर (rc) अणु
		igen6_prपूर्णांकk(KERN_ERR, "Failed to enable error reporting\n");
		जाओ fail4;
	पूर्ण

	igen6_debug_setup();
	वापस 0;
fail4:
	unरेजिस्टर_nmi_handler(NMI_SERR, IGEN6_NMI_NAME);
fail3:
	gen_pool_destroy(ecclog_pool);
fail2:
	igen6_unरेजिस्टर_mcis();
fail:
	kमुक्त(igen6_pvt);
	वापस rc;
पूर्ण

अटल व्योम igen6_हटाओ(काष्ठा pci_dev *pdev)
अणु
	edac_dbg(2, "\n");

	igen6_debug_tearकरोwn();
	errcmd_enable_error_reporting(false);
	unरेजिस्टर_nmi_handler(NMI_SERR, IGEN6_NMI_NAME);
	irq_work_sync(&ecclog_irq_work);
	flush_work(&ecclog_work);
	gen_pool_destroy(ecclog_pool);
	igen6_unरेजिस्टर_mcis();
	kमुक्त(igen6_pvt);
पूर्ण

अटल काष्ठा pci_driver igen6_driver = अणु
	.name     = EDAC_MOD_STR,
	.probe    = igen6_probe,
	.हटाओ   = igen6_हटाओ,
	.id_table = igen6_pci_tbl,
पूर्ण;

अटल पूर्णांक __init igen6_init(व्योम)
अणु
	स्थिर अक्षर *owner;
	पूर्णांक rc;

	edac_dbg(2, "\n");

	owner = edac_get_owner();
	अगर (owner && म_भेदन(owner, EDAC_MOD_STR, माप(EDAC_MOD_STR)))
		वापस -ENODEV;

	edac_op_state = EDAC_OPSTATE_NMI;

	rc = pci_रेजिस्टर_driver(&igen6_driver);
	अगर (rc)
		वापस rc;

	igen6_prपूर्णांकk(KERN_INFO, "%s\n", IGEN6_REVISION);

	वापस 0;
पूर्ण

अटल व्योम __निकास igen6_निकास(व्योम)
अणु
	edac_dbg(2, "\n");

	pci_unरेजिस्टर_driver(&igen6_driver);
पूर्ण

module_init(igen6_init);
module_निकास(igen6_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Qiuxu Zhuo");
MODULE_DESCRIPTION("MC Driver for Intel client SoC using In-Band ECC");
