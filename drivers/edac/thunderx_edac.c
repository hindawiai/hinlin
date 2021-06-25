<शैली गुरु>
/*
 * Cavium ThunderX memory controller kernel module
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright Cavium, Inc. (C) 2015-2017. All rights reserved.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/edac.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/stop_machine.h>
#समावेश <linux/delay.h>
#समावेश <linux/sizes.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/circ_buf.h>

#समावेश <यंत्र/page.h>

#समावेश "edac_module.h"

#घोषणा phys_to_pfn(phys)	(PFN_DOWN(phys))

#घोषणा THUNDERX_NODE		GENMASK(45, 44)

क्रमागत अणु
	ERR_CORRECTED	= 1,
	ERR_UNCORRECTED	= 2,
	ERR_UNKNOWN	= 3,
पूर्ण;

#घोषणा MAX_SYNDROME_REGS 4

काष्ठा error_syndrome अणु
	u64 reg[MAX_SYNDROME_REGS];
पूर्ण;

काष्ठा error_descr अणु
	पूर्णांक	type;
	u64	mask;
	अक्षर	*descr;
पूर्ण;

अटल व्योम decode_रेजिस्टर(अक्षर *str, माप_प्रकार size,
			   स्थिर काष्ठा error_descr *descr,
			   स्थिर uपूर्णांक64_t reg)
अणु
	पूर्णांक ret = 0;

	जबतक (descr->type && descr->mask && descr->descr) अणु
		अगर (reg & descr->mask) अणु
			ret = snम_लिखो(str, size, "\n\t%s, %s",
				       descr->type == ERR_CORRECTED ?
					 "Corrected" : "Uncorrected",
				       descr->descr);
			str += ret;
			size -= ret;
		पूर्ण
		descr++;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ get_bits(अचिन्हित दीर्घ data, पूर्णांक pos, पूर्णांक width)
अणु
	वापस (data >> pos) & ((1 << width) - 1);
पूर्ण

#घोषणा L2C_CTL			0x87E080800000
#घोषणा L2C_CTL_DISIDXALIAS	BIT(0)

#घोषणा PCI_DEVICE_ID_THUNDER_LMC 0xa022

#घोषणा LMC_FADR		0x20
#घोषणा LMC_FADR_FDIMM(x)	((x >> 37) & 0x1)
#घोषणा LMC_FADR_FBUNK(x)	((x >> 36) & 0x1)
#घोषणा LMC_FADR_FBANK(x)	((x >> 32) & 0xf)
#घोषणा LMC_FADR_FROW(x)	((x >> 14) & 0xffff)
#घोषणा LMC_FADR_FCOL(x)	((x >> 0) & 0x1fff)

#घोषणा LMC_NXM_FADR		0x28
#घोषणा LMC_ECC_SYND		0x38

#घोषणा LMC_ECC_PARITY_TEST	0x108

#घोषणा LMC_INT_W1S		0x150

#घोषणा LMC_INT_ENA_W1C		0x158
#घोषणा LMC_INT_ENA_W1S		0x160

#घोषणा LMC_CONFIG		0x188

#घोषणा LMC_CONFIG_BG2		BIT(62)
#घोषणा LMC_CONFIG_RANK_ENA	BIT(42)
#घोषणा LMC_CONFIG_PBANK_LSB(x)	(((x) >> 5) & 0xF)
#घोषणा LMC_CONFIG_ROW_LSB(x)	(((x) >> 2) & 0x7)

#घोषणा LMC_CONTROL		0x190
#घोषणा LMC_CONTROL_XOR_BANK	BIT(16)

#घोषणा LMC_INT			0x1F0

#घोषणा LMC_INT_DDR_ERR		BIT(11)
#घोषणा LMC_INT_DED_ERR		(0xFUL << 5)
#घोषणा LMC_INT_SEC_ERR         (0xFUL << 1)
#घोषणा LMC_INT_NXM_WR_MASK	BIT(0)

#घोषणा LMC_DDR_PLL_CTL		0x258
#घोषणा LMC_DDR_PLL_CTL_DDR4	BIT(29)

#घोषणा LMC_FADR_SCRAMBLED	0x330

#घोषणा LMC_INT_UE              (LMC_INT_DDR_ERR | LMC_INT_DED_ERR | \
				 LMC_INT_NXM_WR_MASK)

#घोषणा LMC_INT_CE		(LMC_INT_SEC_ERR)

अटल स्थिर काष्ठा error_descr lmc_errors[] = अणु
	अणु
		.type  = ERR_CORRECTED,
		.mask  = LMC_INT_SEC_ERR,
		.descr = "Single-bit ECC error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = LMC_INT_DDR_ERR,
		.descr = "DDR chip error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = LMC_INT_DED_ERR,
		.descr = "Double-bit ECC error",
	पूर्ण,
	अणु
		.type = ERR_UNCORRECTED,
		.mask = LMC_INT_NXM_WR_MASK,
		.descr = "Non-existent memory write",
	पूर्ण,
	अणु0, 0, शून्यपूर्ण,
पूर्ण;

#घोषणा LMC_INT_EN_DDR_ERROR_ALERT_ENA	BIT(5)
#घोषणा LMC_INT_EN_DLCRAM_DED_ERR	BIT(4)
#घोषणा LMC_INT_EN_DLCRAM_SEC_ERR	BIT(3)
#घोषणा LMC_INT_INTR_DED_ENA		BIT(2)
#घोषणा LMC_INT_INTR_SEC_ENA		BIT(1)
#घोषणा LMC_INT_INTR_NXM_WR_ENA		BIT(0)

#घोषणा LMC_INT_ENA_ALL			GENMASK(5, 0)

#घोषणा LMC_DDR_PLL_CTL		0x258
#घोषणा LMC_DDR_PLL_CTL_DDR4	BIT(29)

#घोषणा LMC_CONTROL		0x190
#घोषणा LMC_CONTROL_RDIMM	BIT(0)

#घोषणा LMC_SCRAM_FADR		0x330

#घोषणा LMC_CHAR_MASK0		0x228
#घोषणा LMC_CHAR_MASK2		0x238

#घोषणा RING_ENTRIES	8

काष्ठा debugfs_entry अणु
	स्थिर अक्षर *name;
	umode_t mode;
	स्थिर काष्ठा file_operations fops;
पूर्ण;

काष्ठा lmc_err_ctx अणु
	u64 reg_पूर्णांक;
	u64 reg_fadr;
	u64 reg_nxm_fadr;
	u64 reg_scram_fadr;
	u64 reg_ecc_synd;
पूर्ण;

काष्ठा thunderx_lmc अणु
	व्योम __iomem *regs;
	काष्ठा pci_dev *pdev;
	काष्ठा msix_entry msix_ent;

	atomic_t ecc_पूर्णांक;

	u64 mask0;
	u64 mask2;
	u64 parity_test;
	u64 node;

	पूर्णांक xbits;
	पूर्णांक bank_width;
	पूर्णांक pbank_lsb;
	पूर्णांक dimm_lsb;
	पूर्णांक rank_lsb;
	पूर्णांक bank_lsb;
	पूर्णांक row_lsb;
	पूर्णांक col_hi_lsb;

	पूर्णांक xor_bank;
	पूर्णांक l2c_alias;

	काष्ठा page *mem;

	काष्ठा lmc_err_ctx err_ctx[RING_ENTRIES];
	अचिन्हित दीर्घ ring_head;
	अचिन्हित दीर्घ ring_tail;
पूर्ण;

#घोषणा ring_pos(pos, size) ((pos) & (size - 1))

#घोषणा DEBUGFS_STRUCT(_name, _mode, _ग_लिखो, _पढ़ो)			    \
अटल काष्ठा debugfs_entry debugfs_##_name = अणु				    \
	.name = __stringअगरy(_name),					    \
	.mode = VERIFY_OCTAL_PERMISSIONS(_mode),			    \
	.fops = अणु							    \
		.खोलो = simple_खोलो,					    \
		.ग_लिखो = _ग_लिखो,					    \
		.पढ़ो  = _पढ़ो,						    \
		.llseek = generic_file_llseek,				    \
	पूर्ण,								    \
पूर्ण

#घोषणा DEBUGFS_FIELD_ATTR(_type, _field)				    \
अटल sमाप_प्रकार thunderx_##_type##_##_field##_पढ़ो(काष्ठा file *file,	    \
					    अक्षर __user *data,		    \
					    माप_प्रकार count, loff_t *ppos)	    \
अणु									    \
	काष्ठा thunderx_##_type *pdata = file->निजी_data;		    \
	अक्षर buf[20];							    \
									    \
	snम_लिखो(buf, count, "0x%016llx", pdata->_field);		    \
	वापस simple_पढ़ो_from_buffer(data, count, ppos,		    \
				       buf, माप(buf));		    \
पूर्ण									    \
									    \
अटल sमाप_प्रकार thunderx_##_type##_##_field##_ग_लिखो(काष्ठा file *file,	    \
					     स्थिर अक्षर __user *data,	    \
					     माप_प्रकार count, loff_t *ppos)    \
अणु									    \
	काष्ठा thunderx_##_type *pdata = file->निजी_data;		    \
	पूर्णांक res;							    \
									    \
	res = kम_से_अदीर्घl_from_user(data, count, 0, &pdata->_field);	    \
									    \
	वापस res ? res : count;					    \
पूर्ण									    \
									    \
DEBUGFS_STRUCT(_field, 0600,						    \
		   thunderx_##_type##_##_field##_ग_लिखो,			    \
		   thunderx_##_type##_##_field##_पढ़ो)			    \

#घोषणा DEBUGFS_REG_ATTR(_type, _name, _reg)				    \
अटल sमाप_प्रकार thunderx_##_type##_##_name##_पढ़ो(काष्ठा file *file,	    \
					   अक्षर __user *data,		    \
					   माप_प्रकार count, loff_t *ppos)      \
अणु									    \
	काष्ठा thunderx_##_type *pdata = file->निजी_data;		    \
	अक्षर buf[20];							    \
									    \
	प्र_लिखो(buf, "0x%016llx", पढ़ोq(pdata->regs + _reg));		    \
	वापस simple_पढ़ो_from_buffer(data, count, ppos,		    \
				       buf, माप(buf));		    \
पूर्ण									    \
									    \
अटल sमाप_प्रकार thunderx_##_type##_##_name##_ग_लिखो(काष्ठा file *file,	    \
					    स्थिर अक्षर __user *data,	    \
					    माप_प्रकार count, loff_t *ppos)     \
अणु									    \
	काष्ठा thunderx_##_type *pdata = file->निजी_data;		    \
	u64 val;							    \
	पूर्णांक res;							    \
									    \
	res = kम_से_अदीर्घl_from_user(data, count, 0, &val);		    \
									    \
	अगर (!res) अणु							    \
		ग_लिखोq(val, pdata->regs + _reg);			    \
		res = count;						    \
	पूर्ण								    \
									    \
	वापस res;							    \
पूर्ण									    \
									    \
DEBUGFS_STRUCT(_name, 0600,						    \
	       thunderx_##_type##_##_name##_ग_लिखो,			    \
	       thunderx_##_type##_##_name##_पढ़ो)

#घोषणा LMC_DEBUGFS_ENT(_field)	DEBUGFS_FIELD_ATTR(lmc, _field)

/*
 * To get an ECC error injected, the following steps are needed:
 * - Setup the ECC injection by writing the appropriate parameters:
 *	echo <bit mask value> > /sys/kernel/debug/<device number>/ecc_mask0
 *	echo <bit mask value> > /sys/kernel/debug/<device number>/ecc_mask2
 *	echo 0x802 > /sys/kernel/debug/<device number>/ecc_parity_test
 * - Do the actual injection:
 *	echo 1 > /sys/kernel/debug/<device number>/inject_ecc
 */
अटल sमाप_प्रकार thunderx_lmc_inject_पूर्णांक_ग_लिखो(काष्ठा file *file,
					     स्थिर अक्षर __user *data,
					     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा thunderx_lmc *lmc = file->निजी_data;
	u64 val;
	पूर्णांक res;

	res = kम_से_अदीर्घl_from_user(data, count, 0, &val);

	अगर (!res) अणु
		/* Trigger the पूर्णांकerrupt */
		ग_लिखोq(val, lmc->regs + LMC_INT_W1S);
		res = count;
	पूर्ण

	वापस res;
पूर्ण

अटल sमाप_प्रकार thunderx_lmc_पूर्णांक_पढ़ो(काष्ठा file *file,
				     अक्षर __user *data,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा thunderx_lmc *lmc = file->निजी_data;
	अक्षर buf[20];
	u64 lmc_पूर्णांक = पढ़ोq(lmc->regs + LMC_INT);

	snम_लिखो(buf, माप(buf), "0x%016llx", lmc_पूर्णांक);
	वापस simple_पढ़ो_from_buffer(data, count, ppos, buf, माप(buf));
पूर्ण

#घोषणा TEST_PATTERN 0xa5

अटल पूर्णांक inject_ecc_fn(व्योम *arg)
अणु
	काष्ठा thunderx_lmc *lmc = arg;
	uपूर्णांकptr_t addr, phys;
	अचिन्हित पूर्णांक cline_size = cache_line_size();
	स्थिर अचिन्हित पूर्णांक lines = PAGE_SIZE / cline_size;
	अचिन्हित पूर्णांक i, cl_idx;

	addr = (uपूर्णांकptr_t)page_address(lmc->mem);
	phys = (uपूर्णांकptr_t)page_to_phys(lmc->mem);

	cl_idx = (phys & 0x7f) >> 4;
	lmc->parity_test &= ~(7ULL << 8);
	lmc->parity_test |= (cl_idx << 8);

	ग_लिखोq(lmc->mask0, lmc->regs + LMC_CHAR_MASK0);
	ग_लिखोq(lmc->mask2, lmc->regs + LMC_CHAR_MASK2);
	ग_लिखोq(lmc->parity_test, lmc->regs + LMC_ECC_PARITY_TEST);

	पढ़ोq(lmc->regs + LMC_CHAR_MASK0);
	पढ़ोq(lmc->regs + LMC_CHAR_MASK2);
	पढ़ोq(lmc->regs + LMC_ECC_PARITY_TEST);

	क्रम (i = 0; i < lines; i++) अणु
		स_रखो((व्योम *)addr, TEST_PATTERN, cline_size);
		barrier();

		/*
		 * Flush L1 cachelines to the PoC (L2).
		 * This will cause cacheline eviction to the L2.
		 */
		यंत्र अस्थिर("dc civac, %0\n"
			     "dsb sy\n"
			     : : "r"(addr + i * cline_size));
	पूर्ण

	क्रम (i = 0; i < lines; i++) अणु
		/*
		 * Flush L2 cachelines to the DRAM.
		 * This will cause cacheline eviction to the DRAM
		 * and ECC corruption according to the masks set.
		 */
		__यंत्र__ अस्थिर("sys #0,c11,C1,#2, %0\n"
				 : : "r"(phys + i * cline_size));
	पूर्ण

	क्रम (i = 0; i < lines; i++) अणु
		/*
		 * Invalidate L2 cachelines.
		 * The subsequent load will cause cacheline fetch
		 * from the DRAM and an error पूर्णांकerrupt
		 */
		__यंत्र__ अस्थिर("sys #0,c11,C1,#1, %0"
				 : : "r"(phys + i * cline_size));
	पूर्ण

	क्रम (i = 0; i < lines; i++) अणु
		/*
		 * Invalidate L1 cachelines.
		 * The subsequent load will cause cacheline fetch
		 * from the L2 and/or DRAM
		 */
		यंत्र अस्थिर("dc ivac, %0\n"
			     "dsb sy\n"
			     : : "r"(addr + i * cline_size));
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार thunderx_lmc_inject_ecc_ग_लिखो(काष्ठा file *file,
					     स्थिर अक्षर __user *data,
					     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा thunderx_lmc *lmc = file->निजी_data;
	अचिन्हित पूर्णांक cline_size = cache_line_size();
	u8 *पंचांगp;
	व्योम __iomem *addr;
	अचिन्हित पूर्णांक offs, समयout = 100000;

	atomic_set(&lmc->ecc_पूर्णांक, 0);

	lmc->mem = alloc_pages_node(lmc->node, GFP_KERNEL, 0);
	अगर (!lmc->mem)
		वापस -ENOMEM;

	पंचांगp = kदो_स्मृति(cline_size, GFP_KERNEL);
	अगर (!पंचांगp) अणु
		__मुक्त_pages(lmc->mem, 0);
		वापस -ENOMEM;
	पूर्ण

	addr = page_address(lmc->mem);

	जबतक (!atomic_पढ़ो(&lmc->ecc_पूर्णांक) && समयout--) अणु
		stop_machine(inject_ecc_fn, lmc, शून्य);

		क्रम (offs = 0; offs < PAGE_SIZE; offs += cline_size) अणु
			/*
			 * Do a load from the previously rigged location
			 * This should generate an error पूर्णांकerrupt.
			 */
			स_नकल(पंचांगp, addr + offs, cline_size);
			यंत्र अस्थिर("dsb ld\n");
		पूर्ण
	पूर्ण

	kमुक्त(पंचांगp);
	__मुक्त_pages(lmc->mem, 0);

	वापस count;
पूर्ण

LMC_DEBUGFS_ENT(mask0);
LMC_DEBUGFS_ENT(mask2);
LMC_DEBUGFS_ENT(parity_test);

DEBUGFS_STRUCT(inject_पूर्णांक, 0200, thunderx_lmc_inject_पूर्णांक_ग_लिखो, शून्य);
DEBUGFS_STRUCT(inject_ecc, 0200, thunderx_lmc_inject_ecc_ग_लिखो, शून्य);
DEBUGFS_STRUCT(पूर्णांक_w1c, 0400, शून्य, thunderx_lmc_पूर्णांक_पढ़ो);

अटल काष्ठा debugfs_entry *lmc_dfs_ents[] = अणु
	&debugfs_mask0,
	&debugfs_mask2,
	&debugfs_parity_test,
	&debugfs_inject_ecc,
	&debugfs_inject_पूर्णांक,
	&debugfs_पूर्णांक_w1c,
पूर्ण;

अटल पूर्णांक thunderx_create_debugfs_nodes(काष्ठा dentry *parent,
					  काष्ठा debugfs_entry *attrs[],
					  व्योम *data,
					  माप_प्रकार num)
अणु
	पूर्णांक i;
	काष्ठा dentry *ent;

	अगर (!IS_ENABLED(CONFIG_EDAC_DEBUG))
		वापस 0;

	अगर (!parent)
		वापस -ENOENT;

	क्रम (i = 0; i < num; i++) अणु
		ent = edac_debugfs_create_file(attrs[i]->name, attrs[i]->mode,
					       parent, data, &attrs[i]->fops);

		अगर (!ent)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल phys_addr_t thunderx_faddr_to_phys(u64 faddr, काष्ठा thunderx_lmc *lmc)
अणु
	phys_addr_t addr = 0;
	पूर्णांक bank, xbits;

	addr |= lmc->node << 40;
	addr |= LMC_FADR_FDIMM(faddr) << lmc->dimm_lsb;
	addr |= LMC_FADR_FBUNK(faddr) << lmc->rank_lsb;
	addr |= LMC_FADR_FROW(faddr) << lmc->row_lsb;
	addr |= (LMC_FADR_FCOL(faddr) >> 4) << lmc->col_hi_lsb;

	bank = LMC_FADR_FBANK(faddr) << lmc->bank_lsb;

	अगर (lmc->xor_bank)
		bank ^= get_bits(addr, 12 + lmc->xbits, lmc->bank_width);

	addr |= bank << lmc->bank_lsb;

	xbits = PCI_FUNC(lmc->pdev->devfn);

	अगर (lmc->l2c_alias)
		xbits ^= get_bits(addr, 20, lmc->xbits) ^
			 get_bits(addr, 12, lmc->xbits);

	addr |= xbits << 7;

	वापस addr;
पूर्ण

अटल अचिन्हित पूर्णांक thunderx_get_num_lmcs(अचिन्हित पूर्णांक node)
अणु
	अचिन्हित पूर्णांक number = 0;
	काष्ठा pci_dev *pdev = शून्य;

	करो अणु
		pdev = pci_get_device(PCI_VENDOR_ID_CAVIUM,
				      PCI_DEVICE_ID_THUNDER_LMC,
				      pdev);
		अगर (pdev) अणु
#अगर_घोषित CONFIG_NUMA
			अगर (pdev->dev.numa_node == node)
				number++;
#अन्यथा
			number++;
#पूर्ण_अगर
		पूर्ण
	पूर्ण जबतक (pdev);

	वापस number;
पूर्ण

#घोषणा LMC_MESSAGE_SIZE	120
#घोषणा LMC_OTHER_SIZE		(50 * ARRAY_SIZE(lmc_errors))

अटल irqवापस_t thunderx_lmc_err_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mem_ctl_info *mci = dev_id;
	काष्ठा thunderx_lmc *lmc = mci->pvt_info;

	अचिन्हित दीर्घ head = ring_pos(lmc->ring_head, ARRAY_SIZE(lmc->err_ctx));
	काष्ठा lmc_err_ctx *ctx = &lmc->err_ctx[head];

	ग_लिखोq(0, lmc->regs + LMC_CHAR_MASK0);
	ग_लिखोq(0, lmc->regs + LMC_CHAR_MASK2);
	ग_लिखोq(0x2, lmc->regs + LMC_ECC_PARITY_TEST);

	ctx->reg_पूर्णांक = पढ़ोq(lmc->regs + LMC_INT);
	ctx->reg_fadr = पढ़ोq(lmc->regs + LMC_FADR);
	ctx->reg_nxm_fadr = पढ़ोq(lmc->regs + LMC_NXM_FADR);
	ctx->reg_scram_fadr = पढ़ोq(lmc->regs + LMC_SCRAM_FADR);
	ctx->reg_ecc_synd = पढ़ोq(lmc->regs + LMC_ECC_SYND);

	lmc->ring_head++;

	atomic_set(&lmc->ecc_पूर्णांक, 1);

	/* Clear the पूर्णांकerrupt */
	ग_लिखोq(ctx->reg_पूर्णांक, lmc->regs + LMC_INT);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t thunderx_lmc_thपढ़ोed_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mem_ctl_info *mci = dev_id;
	काष्ठा thunderx_lmc *lmc = mci->pvt_info;
	phys_addr_t phys_addr;

	अचिन्हित दीर्घ tail;
	काष्ठा lmc_err_ctx *ctx;

	irqवापस_t ret = IRQ_NONE;

	अक्षर *msg;
	अक्षर *other;

	msg = kदो_स्मृति(LMC_MESSAGE_SIZE, GFP_KERNEL);
	other =  kदो_स्मृति(LMC_OTHER_SIZE, GFP_KERNEL);

	अगर (!msg || !other)
		जाओ err_मुक्त;

	जबतक (CIRC_CNT(lmc->ring_head, lmc->ring_tail,
		ARRAY_SIZE(lmc->err_ctx))) अणु
		tail = ring_pos(lmc->ring_tail, ARRAY_SIZE(lmc->err_ctx));

		ctx = &lmc->err_ctx[tail];

		dev_dbg(&lmc->pdev->dev, "LMC_INT: %016llx\n",
			ctx->reg_पूर्णांक);
		dev_dbg(&lmc->pdev->dev, "LMC_FADR: %016llx\n",
			ctx->reg_fadr);
		dev_dbg(&lmc->pdev->dev, "LMC_NXM_FADR: %016llx\n",
			ctx->reg_nxm_fadr);
		dev_dbg(&lmc->pdev->dev, "LMC_SCRAM_FADR: %016llx\n",
			ctx->reg_scram_fadr);
		dev_dbg(&lmc->pdev->dev, "LMC_ECC_SYND: %016llx\n",
			ctx->reg_ecc_synd);

		snम_लिखो(msg, LMC_MESSAGE_SIZE,
			 "DIMM %lld rank %lld bank %lld row %lld col %lld",
			 LMC_FADR_FDIMM(ctx->reg_scram_fadr),
			 LMC_FADR_FBUNK(ctx->reg_scram_fadr),
			 LMC_FADR_FBANK(ctx->reg_scram_fadr),
			 LMC_FADR_FROW(ctx->reg_scram_fadr),
			 LMC_FADR_FCOL(ctx->reg_scram_fadr));

		decode_रेजिस्टर(other, LMC_OTHER_SIZE, lmc_errors,
				ctx->reg_पूर्णांक);

		phys_addr = thunderx_faddr_to_phys(ctx->reg_fadr, lmc);

		अगर (ctx->reg_पूर्णांक & LMC_INT_UE)
			edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
					     phys_to_pfn(phys_addr),
					     offset_in_page(phys_addr),
					     0, -1, -1, -1, msg, other);
		अन्यथा अगर (ctx->reg_पूर्णांक & LMC_INT_CE)
			edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
					     phys_to_pfn(phys_addr),
					     offset_in_page(phys_addr),
					     0, -1, -1, -1, msg, other);

		lmc->ring_tail++;
	पूर्ण

	ret = IRQ_HANDLED;

err_मुक्त:
	kमुक्त(msg);
	kमुक्त(other);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pci_device_id thunderx_lmc_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_THUNDER_LMC) पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक pci_dev_to_mc_idx(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक node = dev_to_node(&pdev->dev);
	पूर्णांक ret = PCI_FUNC(pdev->devfn);

	ret += max(node, 0) << 3;

	वापस ret;
पूर्ण

अटल पूर्णांक thunderx_lmc_probe(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा thunderx_lmc *lmc;
	काष्ठा edac_mc_layer layer;
	काष्ठा mem_ctl_info *mci;
	u64 lmc_control, lmc_ddr_pll_ctl, lmc_config;
	पूर्णांक ret;
	u64 lmc_पूर्णांक;
	व्योम *l2c_ioaddr;

	layer.type = EDAC_MC_LAYER_SLOT;
	layer.size = 2;
	layer.is_virt_csrow = false;

	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot enable PCI device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = pcim_iomap_regions(pdev, BIT(0), "thunderx_lmc");
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot map PCI resources: %d\n", ret);
		वापस ret;
	पूर्ण

	mci = edac_mc_alloc(pci_dev_to_mc_idx(pdev), 1, &layer,
			    माप(काष्ठा thunderx_lmc));
	अगर (!mci)
		वापस -ENOMEM;

	mci->pdev = &pdev->dev;
	lmc = mci->pvt_info;

	pci_set_drvdata(pdev, mci);

	lmc->regs = pcim_iomap_table(pdev)[0];

	lmc_control = पढ़ोq(lmc->regs + LMC_CONTROL);
	lmc_ddr_pll_ctl = पढ़ोq(lmc->regs + LMC_DDR_PLL_CTL);
	lmc_config = पढ़ोq(lmc->regs + LMC_CONFIG);

	अगर (lmc_control & LMC_CONTROL_RDIMM) अणु
		mci->mtype_cap = FIELD_GET(LMC_DDR_PLL_CTL_DDR4,
					   lmc_ddr_pll_ctl) ?
				MEM_RDDR4 : MEM_RDDR3;
	पूर्ण अन्यथा अणु
		mci->mtype_cap = FIELD_GET(LMC_DDR_PLL_CTL_DDR4,
					   lmc_ddr_pll_ctl) ?
				MEM_DDR4 : MEM_DDR3;
	पूर्ण

	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;

	mci->mod_name = "thunderx-lmc";
	mci->ctl_name = "thunderx-lmc";
	mci->dev_name = dev_name(&pdev->dev);
	mci->scrub_mode = SCRUB_NONE;

	lmc->pdev = pdev;
	lmc->msix_ent.entry = 0;

	lmc->ring_head = 0;
	lmc->ring_tail = 0;

	ret = pci_enable_msix_exact(pdev, &lmc->msix_ent, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot enable interrupt: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, lmc->msix_ent.vector,
					thunderx_lmc_err_isr,
					thunderx_lmc_thपढ़ोed_isr, 0,
					"[EDAC] ThunderX LMC", mci);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot set ISR: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	lmc->node = FIELD_GET(THUNDERX_NODE, pci_resource_start(pdev, 0));

	lmc->xbits = thunderx_get_num_lmcs(lmc->node) >> 1;
	lmc->bank_width = (FIELD_GET(LMC_DDR_PLL_CTL_DDR4, lmc_ddr_pll_ctl) &&
			   FIELD_GET(LMC_CONFIG_BG2, lmc_config)) ? 4 : 3;

	lmc->pbank_lsb = (lmc_config >> 5) & 0xf;
	lmc->dimm_lsb  = 28 + lmc->pbank_lsb + lmc->xbits;
	lmc->rank_lsb = lmc->dimm_lsb;
	lmc->rank_lsb -= FIELD_GET(LMC_CONFIG_RANK_ENA, lmc_config) ? 1 : 0;
	lmc->bank_lsb = 7 + lmc->xbits;
	lmc->row_lsb = 14 + LMC_CONFIG_ROW_LSB(lmc_config) + lmc->xbits;

	lmc->col_hi_lsb = lmc->bank_lsb + lmc->bank_width;

	lmc->xor_bank = lmc_control & LMC_CONTROL_XOR_BANK;

	l2c_ioaddr = ioremap(L2C_CTL | FIELD_PREP(THUNDERX_NODE, lmc->node), PAGE_SIZE);
	अगर (!l2c_ioaddr) अणु
		dev_err(&pdev->dev, "Cannot map L2C_CTL\n");
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	lmc->l2c_alias = !(पढ़ोq(l2c_ioaddr) & L2C_CTL_DISIDXALIAS);

	iounmap(l2c_ioaddr);

	ret = edac_mc_add_mc(mci);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot add the MC: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	lmc_पूर्णांक = पढ़ोq(lmc->regs + LMC_INT);
	ग_लिखोq(lmc_पूर्णांक, lmc->regs + LMC_INT);

	ग_लिखोq(LMC_INT_ENA_ALL, lmc->regs + LMC_INT_ENA_W1S);

	अगर (IS_ENABLED(CONFIG_EDAC_DEBUG)) अणु
		ret = thunderx_create_debugfs_nodes(mci->debugfs,
						    lmc_dfs_ents,
						    lmc,
						    ARRAY_SIZE(lmc_dfs_ents));

		अगर (ret != ARRAY_SIZE(lmc_dfs_ents)) अणु
			dev_warn(&pdev->dev, "Error creating debugfs entries: %d%s\n",
				 ret, ret >= 0 ? " created" : "");
		पूर्ण
	पूर्ण

	वापस 0;

err_मुक्त:
	pci_set_drvdata(pdev, शून्य);
	edac_mc_मुक्त(mci);

	वापस ret;
पूर्ण

अटल व्योम thunderx_lmc_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci = pci_get_drvdata(pdev);
	काष्ठा thunderx_lmc *lmc = mci->pvt_info;

	ग_लिखोq(LMC_INT_ENA_ALL, lmc->regs + LMC_INT_ENA_W1C);

	edac_mc_del_mc(&pdev->dev);
	edac_mc_मुक्त(mci);
पूर्ण

MODULE_DEVICE_TABLE(pci, thunderx_lmc_pci_tbl);

अटल काष्ठा pci_driver thunderx_lmc_driver = अणु
	.name     = "thunderx_lmc_edac",
	.probe    = thunderx_lmc_probe,
	.हटाओ   = thunderx_lmc_हटाओ,
	.id_table = thunderx_lmc_pci_tbl,
पूर्ण;

/*---------------------- OCX driver ---------------------------------*/

#घोषणा PCI_DEVICE_ID_THUNDER_OCX 0xa013

#घोषणा OCX_LINK_INTS		3
#घोषणा OCX_INTS		(OCX_LINK_INTS + 1)
#घोषणा OCX_RX_LANES		24
#घोषणा OCX_RX_LANE_STATS	15

#घोषणा OCX_COM_INT		0x100
#घोषणा OCX_COM_INT_W1S		0x108
#घोषणा OCX_COM_INT_ENA_W1S	0x110
#घोषणा OCX_COM_INT_ENA_W1C	0x118

#घोषणा OCX_COM_IO_BADID		BIT(54)
#घोषणा OCX_COM_MEM_BADID		BIT(53)
#घोषणा OCX_COM_COPR_BADID		BIT(52)
#घोषणा OCX_COM_WIN_REQ_BADID		BIT(51)
#घोषणा OCX_COM_WIN_REQ_TOUT		BIT(50)
#घोषणा OCX_COM_RX_LANE			GENMASK(23, 0)

#घोषणा OCX_COM_INT_CE			(OCX_COM_IO_BADID      | \
					 OCX_COM_MEM_BADID     | \
					 OCX_COM_COPR_BADID    | \
					 OCX_COM_WIN_REQ_BADID | \
					 OCX_COM_WIN_REQ_TOUT)

अटल स्थिर काष्ठा error_descr ocx_com_errors[] = अणु
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_COM_IO_BADID,
		.descr = "Invalid IO transaction node ID",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_COM_MEM_BADID,
		.descr = "Invalid memory transaction node ID",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_COM_COPR_BADID,
		.descr = "Invalid coprocessor transaction node ID",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_COM_WIN_REQ_BADID,
		.descr = "Invalid SLI transaction node ID",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_COM_WIN_REQ_TOUT,
		.descr = "Window/core request timeout",
	पूर्ण,
	अणु0, 0, शून्यपूर्ण,
पूर्ण;

#घोषणा OCX_COM_LINKX_INT(x)		(0x120 + (x) * 8)
#घोषणा OCX_COM_LINKX_INT_W1S(x)	(0x140 + (x) * 8)
#घोषणा OCX_COM_LINKX_INT_ENA_W1S(x)	(0x160 + (x) * 8)
#घोषणा OCX_COM_LINKX_INT_ENA_W1C(x)	(0x180 + (x) * 8)

#घोषणा OCX_COM_LINK_BAD_WORD			BIT(13)
#घोषणा OCX_COM_LINK_ALIGN_FAIL			BIT(12)
#घोषणा OCX_COM_LINK_ALIGN_DONE			BIT(11)
#घोषणा OCX_COM_LINK_UP				BIT(10)
#घोषणा OCX_COM_LINK_STOP			BIT(9)
#घोषणा OCX_COM_LINK_BLK_ERR			BIT(8)
#घोषणा OCX_COM_LINK_REINIT			BIT(7)
#घोषणा OCX_COM_LINK_LNK_DATA			BIT(6)
#घोषणा OCX_COM_LINK_RXFIFO_DBE			BIT(5)
#घोषणा OCX_COM_LINK_RXFIFO_SBE			BIT(4)
#घोषणा OCX_COM_LINK_TXFIFO_DBE			BIT(3)
#घोषणा OCX_COM_LINK_TXFIFO_SBE			BIT(2)
#घोषणा OCX_COM_LINK_REPLAY_DBE			BIT(1)
#घोषणा OCX_COM_LINK_REPLAY_SBE			BIT(0)

अटल स्थिर काष्ठा error_descr ocx_com_link_errors[] = अणु
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_COM_LINK_REPLAY_SBE,
		.descr = "Replay buffer single-bit error",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_COM_LINK_TXFIFO_SBE,
		.descr = "TX FIFO single-bit error",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_COM_LINK_RXFIFO_SBE,
		.descr = "RX FIFO single-bit error",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_COM_LINK_BLK_ERR,
		.descr = "Block code error",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_COM_LINK_ALIGN_FAIL,
		.descr = "Link alignment failure",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_COM_LINK_BAD_WORD,
		.descr = "Bad code word",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = OCX_COM_LINK_REPLAY_DBE,
		.descr = "Replay buffer double-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = OCX_COM_LINK_TXFIFO_DBE,
		.descr = "TX FIFO double-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = OCX_COM_LINK_RXFIFO_DBE,
		.descr = "RX FIFO double-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = OCX_COM_LINK_STOP,
		.descr = "Link stopped",
	पूर्ण,
	अणु0, 0, शून्यपूर्ण,
पूर्ण;

#घोषणा OCX_COM_LINK_INT_UE       (OCX_COM_LINK_REPLAY_DBE | \
				   OCX_COM_LINK_TXFIFO_DBE | \
				   OCX_COM_LINK_RXFIFO_DBE | \
				   OCX_COM_LINK_STOP)

#घोषणा OCX_COM_LINK_INT_CE       (OCX_COM_LINK_REPLAY_SBE | \
				   OCX_COM_LINK_TXFIFO_SBE | \
				   OCX_COM_LINK_RXFIFO_SBE | \
				   OCX_COM_LINK_BLK_ERR    | \
				   OCX_COM_LINK_ALIGN_FAIL | \
				   OCX_COM_LINK_BAD_WORD)

#घोषणा OCX_LNE_INT(x)			(0x8018 + (x) * 0x100)
#घोषणा OCX_LNE_INT_EN(x)		(0x8020 + (x) * 0x100)
#घोषणा OCX_LNE_BAD_CNT(x)		(0x8028 + (x) * 0x100)
#घोषणा OCX_LNE_CFG(x)			(0x8000 + (x) * 0x100)
#घोषणा OCX_LNE_STAT(x, y)		(0x8040 + (x) * 0x100 + (y) * 8)

#घोषणा OCX_LNE_CFG_RX_BDRY_LOCK_DIS		BIT(8)
#घोषणा OCX_LNE_CFG_RX_STAT_WRAP_DIS		BIT(2)
#घोषणा OCX_LNE_CFG_RX_STAT_RDCLR		BIT(1)
#घोषणा OCX_LNE_CFG_RX_STAT_ENA			BIT(0)


#घोषणा OCX_LANE_BAD_64B67B			BIT(8)
#घोषणा OCX_LANE_DSKEW_FIFO_OVFL		BIT(5)
#घोषणा OCX_LANE_SCRM_SYNC_LOSS			BIT(4)
#घोषणा OCX_LANE_UKWN_CNTL_WORD			BIT(3)
#घोषणा OCX_LANE_CRC32_ERR			BIT(2)
#घोषणा OCX_LANE_BDRY_SYNC_LOSS			BIT(1)
#घोषणा OCX_LANE_SERDES_LOCK_LOSS		BIT(0)

#घोषणा OCX_COM_LANE_INT_UE       (0)
#घोषणा OCX_COM_LANE_INT_CE       (OCX_LANE_SERDES_LOCK_LOSS | \
				   OCX_LANE_BDRY_SYNC_LOSS   | \
				   OCX_LANE_CRC32_ERR        | \
				   OCX_LANE_UKWN_CNTL_WORD   | \
				   OCX_LANE_SCRM_SYNC_LOSS   | \
				   OCX_LANE_DSKEW_FIFO_OVFL  | \
				   OCX_LANE_BAD_64B67B)

अटल स्थिर काष्ठा error_descr ocx_lane_errors[] = अणु
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_LANE_SERDES_LOCK_LOSS,
		.descr = "RX SerDes lock lost",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_LANE_BDRY_SYNC_LOSS,
		.descr = "RX word boundary lost",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_LANE_CRC32_ERR,
		.descr = "CRC32 error",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_LANE_UKWN_CNTL_WORD,
		.descr = "Unknown control word",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_LANE_SCRM_SYNC_LOSS,
		.descr = "Scrambler synchronization lost",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_LANE_DSKEW_FIFO_OVFL,
		.descr = "RX deskew FIFO overflow",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = OCX_LANE_BAD_64B67B,
		.descr = "Bad 64B/67B codeword",
	पूर्ण,
	अणु0, 0, शून्यपूर्ण,
पूर्ण;

#घोषणा OCX_LNE_INT_ENA_ALL		(GENMASK(9, 8) | GENMASK(6, 0))
#घोषणा OCX_COM_INT_ENA_ALL		(GENMASK(54, 50) | GENMASK(23, 0))
#घोषणा OCX_COM_LINKX_INT_ENA_ALL	(GENMASK(13, 12) | \
					 GENMASK(9, 7) | GENMASK(5, 0))

#घोषणा OCX_TLKX_ECC_CTL(x)		(0x10018 + (x) * 0x2000)
#घोषणा OCX_RLKX_ECC_CTL(x)		(0x18018 + (x) * 0x2000)

काष्ठा ocx_com_err_ctx अणु
	u64 reg_com_पूर्णांक;
	u64 reg_lane_पूर्णांक[OCX_RX_LANES];
	u64 reg_lane_stat11[OCX_RX_LANES];
पूर्ण;

काष्ठा ocx_link_err_ctx अणु
	u64 reg_com_link_पूर्णांक;
	पूर्णांक link;
पूर्ण;

काष्ठा thunderx_ocx अणु
	व्योम __iomem *regs;
	पूर्णांक com_link;
	काष्ठा pci_dev *pdev;
	काष्ठा edac_device_ctl_info *edac_dev;

	काष्ठा dentry *debugfs;
	काष्ठा msix_entry msix_ent[OCX_INTS];

	काष्ठा ocx_com_err_ctx com_err_ctx[RING_ENTRIES];
	काष्ठा ocx_link_err_ctx link_err_ctx[RING_ENTRIES];

	अचिन्हित दीर्घ com_ring_head;
	अचिन्हित दीर्घ com_ring_tail;

	अचिन्हित दीर्घ link_ring_head;
	अचिन्हित दीर्घ link_ring_tail;
पूर्ण;

#घोषणा OCX_MESSAGE_SIZE	SZ_1K
#घोषणा OCX_OTHER_SIZE		(50 * ARRAY_SIZE(ocx_com_link_errors))

/* This handler is thपढ़ोed */
अटल irqवापस_t thunderx_ocx_com_isr(पूर्णांक irq, व्योम *irq_id)
अणु
	काष्ठा msix_entry *msix = irq_id;
	काष्ठा thunderx_ocx *ocx = container_of(msix, काष्ठा thunderx_ocx,
						msix_ent[msix->entry]);

	पूर्णांक lane;
	अचिन्हित दीर्घ head = ring_pos(ocx->com_ring_head,
				      ARRAY_SIZE(ocx->com_err_ctx));
	काष्ठा ocx_com_err_ctx *ctx = &ocx->com_err_ctx[head];

	ctx->reg_com_पूर्णांक = पढ़ोq(ocx->regs + OCX_COM_INT);

	क्रम (lane = 0; lane < OCX_RX_LANES; lane++) अणु
		ctx->reg_lane_पूर्णांक[lane] =
			पढ़ोq(ocx->regs + OCX_LNE_INT(lane));
		ctx->reg_lane_stat11[lane] =
			पढ़ोq(ocx->regs + OCX_LNE_STAT(lane, 11));

		ग_लिखोq(ctx->reg_lane_पूर्णांक[lane], ocx->regs + OCX_LNE_INT(lane));
	पूर्ण

	ग_लिखोq(ctx->reg_com_पूर्णांक, ocx->regs + OCX_COM_INT);

	ocx->com_ring_head++;

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t thunderx_ocx_com_thपढ़ोed_isr(पूर्णांक irq, व्योम *irq_id)
अणु
	काष्ठा msix_entry *msix = irq_id;
	काष्ठा thunderx_ocx *ocx = container_of(msix, काष्ठा thunderx_ocx,
						msix_ent[msix->entry]);

	irqवापस_t ret = IRQ_NONE;

	अचिन्हित दीर्घ tail;
	काष्ठा ocx_com_err_ctx *ctx;
	पूर्णांक lane;
	अक्षर *msg;
	अक्षर *other;

	msg = kदो_स्मृति(OCX_MESSAGE_SIZE, GFP_KERNEL);
	other = kदो_स्मृति(OCX_OTHER_SIZE, GFP_KERNEL);

	अगर (!msg || !other)
		जाओ err_मुक्त;

	जबतक (CIRC_CNT(ocx->com_ring_head, ocx->com_ring_tail,
			ARRAY_SIZE(ocx->com_err_ctx))) अणु
		tail = ring_pos(ocx->com_ring_tail,
				ARRAY_SIZE(ocx->com_err_ctx));
		ctx = &ocx->com_err_ctx[tail];

		snम_लिखो(msg, OCX_MESSAGE_SIZE, "%s: OCX_COM_INT: %016llx",
			ocx->edac_dev->ctl_name, ctx->reg_com_पूर्णांक);

		decode_रेजिस्टर(other, OCX_OTHER_SIZE,
				ocx_com_errors, ctx->reg_com_पूर्णांक);

		म_जोड़न(msg, other, OCX_MESSAGE_SIZE);

		क्रम (lane = 0; lane < OCX_RX_LANES; lane++)
			अगर (ctx->reg_com_पूर्णांक & BIT(lane)) अणु
				snम_लिखो(other, OCX_OTHER_SIZE,
					 "\n\tOCX_LNE_INT[%02d]: %016llx OCX_LNE_STAT11[%02d]: %016llx",
					 lane, ctx->reg_lane_पूर्णांक[lane],
					 lane, ctx->reg_lane_stat11[lane]);

				म_जोड़न(msg, other, OCX_MESSAGE_SIZE);

				decode_रेजिस्टर(other, OCX_OTHER_SIZE,
						ocx_lane_errors,
						ctx->reg_lane_पूर्णांक[lane]);
				म_जोड़न(msg, other, OCX_MESSAGE_SIZE);
			पूर्ण

		अगर (ctx->reg_com_पूर्णांक & OCX_COM_INT_CE)
			edac_device_handle_ce(ocx->edac_dev, 0, 0, msg);

		ocx->com_ring_tail++;
	पूर्ण

	ret = IRQ_HANDLED;

err_मुक्त:
	kमुक्त(other);
	kमुक्त(msg);

	वापस ret;
पूर्ण

अटल irqवापस_t thunderx_ocx_lnk_isr(पूर्णांक irq, व्योम *irq_id)
अणु
	काष्ठा msix_entry *msix = irq_id;
	काष्ठा thunderx_ocx *ocx = container_of(msix, काष्ठा thunderx_ocx,
						msix_ent[msix->entry]);
	अचिन्हित दीर्घ head = ring_pos(ocx->link_ring_head,
				      ARRAY_SIZE(ocx->link_err_ctx));
	काष्ठा ocx_link_err_ctx *ctx = &ocx->link_err_ctx[head];

	ctx->link = msix->entry;
	ctx->reg_com_link_पूर्णांक = पढ़ोq(ocx->regs + OCX_COM_LINKX_INT(ctx->link));

	ग_लिखोq(ctx->reg_com_link_पूर्णांक, ocx->regs + OCX_COM_LINKX_INT(ctx->link));

	ocx->link_ring_head++;

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t thunderx_ocx_lnk_thपढ़ोed_isr(पूर्णांक irq, व्योम *irq_id)
अणु
	काष्ठा msix_entry *msix = irq_id;
	काष्ठा thunderx_ocx *ocx = container_of(msix, काष्ठा thunderx_ocx,
						msix_ent[msix->entry]);
	irqवापस_t ret = IRQ_NONE;
	अचिन्हित दीर्घ tail;
	काष्ठा ocx_link_err_ctx *ctx;

	अक्षर *msg;
	अक्षर *other;

	msg = kदो_स्मृति(OCX_MESSAGE_SIZE, GFP_KERNEL);
	other = kदो_स्मृति(OCX_OTHER_SIZE, GFP_KERNEL);

	अगर (!msg || !other)
		जाओ err_मुक्त;

	जबतक (CIRC_CNT(ocx->link_ring_head, ocx->link_ring_tail,
			ARRAY_SIZE(ocx->link_err_ctx))) अणु
		tail = ring_pos(ocx->link_ring_head,
				ARRAY_SIZE(ocx->link_err_ctx));

		ctx = &ocx->link_err_ctx[tail];

		snम_लिखो(msg, OCX_MESSAGE_SIZE,
			 "%s: OCX_COM_LINK_INT[%d]: %016llx",
			 ocx->edac_dev->ctl_name,
			 ctx->link, ctx->reg_com_link_पूर्णांक);

		decode_रेजिस्टर(other, OCX_OTHER_SIZE,
				ocx_com_link_errors, ctx->reg_com_link_पूर्णांक);

		म_जोड़न(msg, other, OCX_MESSAGE_SIZE);

		अगर (ctx->reg_com_link_पूर्णांक & OCX_COM_LINK_INT_UE)
			edac_device_handle_ue(ocx->edac_dev, 0, 0, msg);
		अन्यथा अगर (ctx->reg_com_link_पूर्णांक & OCX_COM_LINK_INT_CE)
			edac_device_handle_ce(ocx->edac_dev, 0, 0, msg);

		ocx->link_ring_tail++;
	पूर्ण

	ret = IRQ_HANDLED;
err_मुक्त:
	kमुक्त(other);
	kमुक्त(msg);

	वापस ret;
पूर्ण

#घोषणा OCX_DEBUGFS_ATTR(_name, _reg)	DEBUGFS_REG_ATTR(ocx, _name, _reg)

OCX_DEBUGFS_ATTR(tlk0_ecc_ctl, OCX_TLKX_ECC_CTL(0));
OCX_DEBUGFS_ATTR(tlk1_ecc_ctl, OCX_TLKX_ECC_CTL(1));
OCX_DEBUGFS_ATTR(tlk2_ecc_ctl, OCX_TLKX_ECC_CTL(2));

OCX_DEBUGFS_ATTR(rlk0_ecc_ctl, OCX_RLKX_ECC_CTL(0));
OCX_DEBUGFS_ATTR(rlk1_ecc_ctl, OCX_RLKX_ECC_CTL(1));
OCX_DEBUGFS_ATTR(rlk2_ecc_ctl, OCX_RLKX_ECC_CTL(2));

OCX_DEBUGFS_ATTR(com_link0_पूर्णांक, OCX_COM_LINKX_INT_W1S(0));
OCX_DEBUGFS_ATTR(com_link1_पूर्णांक, OCX_COM_LINKX_INT_W1S(1));
OCX_DEBUGFS_ATTR(com_link2_पूर्णांक, OCX_COM_LINKX_INT_W1S(2));

OCX_DEBUGFS_ATTR(lne00_badcnt, OCX_LNE_BAD_CNT(0));
OCX_DEBUGFS_ATTR(lne01_badcnt, OCX_LNE_BAD_CNT(1));
OCX_DEBUGFS_ATTR(lne02_badcnt, OCX_LNE_BAD_CNT(2));
OCX_DEBUGFS_ATTR(lne03_badcnt, OCX_LNE_BAD_CNT(3));
OCX_DEBUGFS_ATTR(lne04_badcnt, OCX_LNE_BAD_CNT(4));
OCX_DEBUGFS_ATTR(lne05_badcnt, OCX_LNE_BAD_CNT(5));
OCX_DEBUGFS_ATTR(lne06_badcnt, OCX_LNE_BAD_CNT(6));
OCX_DEBUGFS_ATTR(lne07_badcnt, OCX_LNE_BAD_CNT(7));

OCX_DEBUGFS_ATTR(lne08_badcnt, OCX_LNE_BAD_CNT(8));
OCX_DEBUGFS_ATTR(lne09_badcnt, OCX_LNE_BAD_CNT(9));
OCX_DEBUGFS_ATTR(lne10_badcnt, OCX_LNE_BAD_CNT(10));
OCX_DEBUGFS_ATTR(lne11_badcnt, OCX_LNE_BAD_CNT(11));
OCX_DEBUGFS_ATTR(lne12_badcnt, OCX_LNE_BAD_CNT(12));
OCX_DEBUGFS_ATTR(lne13_badcnt, OCX_LNE_BAD_CNT(13));
OCX_DEBUGFS_ATTR(lne14_badcnt, OCX_LNE_BAD_CNT(14));
OCX_DEBUGFS_ATTR(lne15_badcnt, OCX_LNE_BAD_CNT(15));

OCX_DEBUGFS_ATTR(lne16_badcnt, OCX_LNE_BAD_CNT(16));
OCX_DEBUGFS_ATTR(lne17_badcnt, OCX_LNE_BAD_CNT(17));
OCX_DEBUGFS_ATTR(lne18_badcnt, OCX_LNE_BAD_CNT(18));
OCX_DEBUGFS_ATTR(lne19_badcnt, OCX_LNE_BAD_CNT(19));
OCX_DEBUGFS_ATTR(lne20_badcnt, OCX_LNE_BAD_CNT(20));
OCX_DEBUGFS_ATTR(lne21_badcnt, OCX_LNE_BAD_CNT(21));
OCX_DEBUGFS_ATTR(lne22_badcnt, OCX_LNE_BAD_CNT(22));
OCX_DEBUGFS_ATTR(lne23_badcnt, OCX_LNE_BAD_CNT(23));

OCX_DEBUGFS_ATTR(com_पूर्णांक, OCX_COM_INT_W1S);

अटल काष्ठा debugfs_entry *ocx_dfs_ents[] = अणु
	&debugfs_tlk0_ecc_ctl,
	&debugfs_tlk1_ecc_ctl,
	&debugfs_tlk2_ecc_ctl,

	&debugfs_rlk0_ecc_ctl,
	&debugfs_rlk1_ecc_ctl,
	&debugfs_rlk2_ecc_ctl,

	&debugfs_com_link0_पूर्णांक,
	&debugfs_com_link1_पूर्णांक,
	&debugfs_com_link2_पूर्णांक,

	&debugfs_lne00_badcnt,
	&debugfs_lne01_badcnt,
	&debugfs_lne02_badcnt,
	&debugfs_lne03_badcnt,
	&debugfs_lne04_badcnt,
	&debugfs_lne05_badcnt,
	&debugfs_lne06_badcnt,
	&debugfs_lne07_badcnt,
	&debugfs_lne08_badcnt,
	&debugfs_lne09_badcnt,
	&debugfs_lne10_badcnt,
	&debugfs_lne11_badcnt,
	&debugfs_lne12_badcnt,
	&debugfs_lne13_badcnt,
	&debugfs_lne14_badcnt,
	&debugfs_lne15_badcnt,
	&debugfs_lne16_badcnt,
	&debugfs_lne17_badcnt,
	&debugfs_lne18_badcnt,
	&debugfs_lne19_badcnt,
	&debugfs_lne20_badcnt,
	&debugfs_lne21_badcnt,
	&debugfs_lne22_badcnt,
	&debugfs_lne23_badcnt,

	&debugfs_com_पूर्णांक,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id thunderx_ocx_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_THUNDER_OCX) पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

अटल व्योम thunderx_ocx_clearstats(काष्ठा thunderx_ocx *ocx)
अणु
	पूर्णांक lane, stat, cfg;

	क्रम (lane = 0; lane < OCX_RX_LANES; lane++) अणु
		cfg = पढ़ोq(ocx->regs + OCX_LNE_CFG(lane));
		cfg |= OCX_LNE_CFG_RX_STAT_RDCLR;
		cfg &= ~OCX_LNE_CFG_RX_STAT_ENA;
		ग_लिखोq(cfg, ocx->regs + OCX_LNE_CFG(lane));

		क्रम (stat = 0; stat < OCX_RX_LANE_STATS; stat++)
			पढ़ोq(ocx->regs + OCX_LNE_STAT(lane, stat));
	पूर्ण
पूर्ण

अटल पूर्णांक thunderx_ocx_probe(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा thunderx_ocx *ocx;
	काष्ठा edac_device_ctl_info *edac_dev;
	अक्षर name[32];
	पूर्णांक idx;
	पूर्णांक i;
	पूर्णांक ret;
	u64 reg;

	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot enable PCI device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = pcim_iomap_regions(pdev, BIT(0), "thunderx_ocx");
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot map PCI resources: %d\n", ret);
		वापस ret;
	पूर्ण

	idx = edac_device_alloc_index();
	snम_लिखो(name, माप(name), "OCX%d", idx);
	edac_dev = edac_device_alloc_ctl_info(माप(काष्ठा thunderx_ocx),
					      name, 1, "CCPI", 1,
					      0, शून्य, 0, idx);
	अगर (!edac_dev) अणु
		dev_err(&pdev->dev, "Cannot allocate EDAC device: %d\n", ret);
		वापस -ENOMEM;
	पूर्ण
	ocx = edac_dev->pvt_info;
	ocx->edac_dev = edac_dev;
	ocx->com_ring_head = 0;
	ocx->com_ring_tail = 0;
	ocx->link_ring_head = 0;
	ocx->link_ring_tail = 0;

	ocx->regs = pcim_iomap_table(pdev)[0];
	अगर (!ocx->regs) अणु
		dev_err(&pdev->dev, "Cannot map PCI resources: %d\n", ret);
		ret = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	ocx->pdev = pdev;

	क्रम (i = 0; i < OCX_INTS; i++) अणु
		ocx->msix_ent[i].entry = i;
		ocx->msix_ent[i].vector = 0;
	पूर्ण

	ret = pci_enable_msix_exact(pdev, ocx->msix_ent, OCX_INTS);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot enable interrupt: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	क्रम (i = 0; i < OCX_INTS; i++) अणु
		ret = devm_request_thपढ़ोed_irq(&pdev->dev,
						ocx->msix_ent[i].vector,
						(i == 3) ?
						 thunderx_ocx_com_isr :
						 thunderx_ocx_lnk_isr,
						(i == 3) ?
						 thunderx_ocx_com_thपढ़ोed_isr :
						 thunderx_ocx_lnk_thपढ़ोed_isr,
						0, "[EDAC] ThunderX OCX",
						&ocx->msix_ent[i]);
		अगर (ret)
			जाओ err_मुक्त;
	पूर्ण

	edac_dev->dev = &pdev->dev;
	edac_dev->dev_name = dev_name(&pdev->dev);
	edac_dev->mod_name = "thunderx-ocx";
	edac_dev->ctl_name = "thunderx-ocx";

	ret = edac_device_add_device(edac_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot add EDAC device: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_EDAC_DEBUG)) अणु
		ocx->debugfs = edac_debugfs_create_dir(pdev->dev.kobj.name);

		ret = thunderx_create_debugfs_nodes(ocx->debugfs,
						    ocx_dfs_ents,
						    ocx,
						    ARRAY_SIZE(ocx_dfs_ents));
		अगर (ret != ARRAY_SIZE(ocx_dfs_ents)) अणु
			dev_warn(&pdev->dev, "Error creating debugfs entries: %d%s\n",
				 ret, ret >= 0 ? " created" : "");
		पूर्ण
	पूर्ण

	pci_set_drvdata(pdev, edac_dev);

	thunderx_ocx_clearstats(ocx);

	क्रम (i = 0; i < OCX_RX_LANES; i++) अणु
		ग_लिखोq(OCX_LNE_INT_ENA_ALL,
		       ocx->regs + OCX_LNE_INT_EN(i));

		reg = पढ़ोq(ocx->regs + OCX_LNE_INT(i));
		ग_लिखोq(reg, ocx->regs + OCX_LNE_INT(i));

	पूर्ण

	क्रम (i = 0; i < OCX_LINK_INTS; i++) अणु
		reg = पढ़ोq(ocx->regs + OCX_COM_LINKX_INT(i));
		ग_लिखोq(reg, ocx->regs + OCX_COM_LINKX_INT(i));

		ग_लिखोq(OCX_COM_LINKX_INT_ENA_ALL,
		       ocx->regs + OCX_COM_LINKX_INT_ENA_W1S(i));
	पूर्ण

	reg = पढ़ोq(ocx->regs + OCX_COM_INT);
	ग_लिखोq(reg, ocx->regs + OCX_COM_INT);

	ग_लिखोq(OCX_COM_INT_ENA_ALL, ocx->regs + OCX_COM_INT_ENA_W1S);

	वापस 0;
err_मुक्त:
	edac_device_मुक्त_ctl_info(edac_dev);

	वापस ret;
पूर्ण

अटल व्योम thunderx_ocx_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = pci_get_drvdata(pdev);
	काष्ठा thunderx_ocx *ocx = edac_dev->pvt_info;
	पूर्णांक i;

	ग_लिखोq(OCX_COM_INT_ENA_ALL, ocx->regs + OCX_COM_INT_ENA_W1C);

	क्रम (i = 0; i < OCX_INTS; i++) अणु
		ग_लिखोq(OCX_COM_LINKX_INT_ENA_ALL,
		       ocx->regs + OCX_COM_LINKX_INT_ENA_W1C(i));
	पूर्ण

	edac_debugfs_हटाओ_recursive(ocx->debugfs);

	edac_device_del_device(&pdev->dev);
	edac_device_मुक्त_ctl_info(edac_dev);
पूर्ण

MODULE_DEVICE_TABLE(pci, thunderx_ocx_pci_tbl);

अटल काष्ठा pci_driver thunderx_ocx_driver = अणु
	.name     = "thunderx_ocx_edac",
	.probe    = thunderx_ocx_probe,
	.हटाओ   = thunderx_ocx_हटाओ,
	.id_table = thunderx_ocx_pci_tbl,
पूर्ण;

/*---------------------- L2C driver ---------------------------------*/

#घोषणा PCI_DEVICE_ID_THUNDER_L2C_TAD 0xa02e
#घोषणा PCI_DEVICE_ID_THUNDER_L2C_CBC 0xa02f
#घोषणा PCI_DEVICE_ID_THUNDER_L2C_MCI 0xa030

#घोषणा L2C_TAD_INT_W1C		0x40000
#घोषणा L2C_TAD_INT_W1S		0x40008

#घोषणा L2C_TAD_INT_ENA_W1C	0x40020
#घोषणा L2C_TAD_INT_ENA_W1S	0x40028


#घोषणा L2C_TAD_INT_L2DDBE	 BIT(1)
#घोषणा L2C_TAD_INT_SBFSBE	 BIT(2)
#घोषणा L2C_TAD_INT_SBFDBE	 BIT(3)
#घोषणा L2C_TAD_INT_FBFSBE	 BIT(4)
#घोषणा L2C_TAD_INT_FBFDBE	 BIT(5)
#घोषणा L2C_TAD_INT_TAGDBE	 BIT(9)
#घोषणा L2C_TAD_INT_RDDISLMC	 BIT(15)
#घोषणा L2C_TAD_INT_WRDISLMC	 BIT(16)
#घोषणा L2C_TAD_INT_LFBTO	 BIT(17)
#घोषणा L2C_TAD_INT_GSYNCTO	 BIT(18)
#घोषणा L2C_TAD_INT_RTGSBE	 BIT(32)
#घोषणा L2C_TAD_INT_RTGDBE	 BIT(33)
#घोषणा L2C_TAD_INT_RDDISOCI	 BIT(34)
#घोषणा L2C_TAD_INT_WRDISOCI	 BIT(35)

#घोषणा L2C_TAD_INT_ECC		(L2C_TAD_INT_L2DDBE | \
				 L2C_TAD_INT_SBFSBE | L2C_TAD_INT_SBFDBE | \
				 L2C_TAD_INT_FBFSBE | L2C_TAD_INT_FBFDBE)

#घोषणा L2C_TAD_INT_CE          (L2C_TAD_INT_SBFSBE | \
				 L2C_TAD_INT_FBFSBE)

#घोषणा L2C_TAD_INT_UE          (L2C_TAD_INT_L2DDBE | \
				 L2C_TAD_INT_SBFDBE | \
				 L2C_TAD_INT_FBFDBE | \
				 L2C_TAD_INT_TAGDBE | \
				 L2C_TAD_INT_RTGDBE | \
				 L2C_TAD_INT_WRDISOCI | \
				 L2C_TAD_INT_RDDISOCI | \
				 L2C_TAD_INT_WRDISLMC | \
				 L2C_TAD_INT_RDDISLMC | \
				 L2C_TAD_INT_LFBTO    | \
				 L2C_TAD_INT_GSYNCTO)

अटल स्थिर काष्ठा error_descr l2_tad_errors[] = अणु
	अणु
		.type  = ERR_CORRECTED,
		.mask  = L2C_TAD_INT_SBFSBE,
		.descr = "SBF single-bit error",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = L2C_TAD_INT_FBFSBE,
		.descr = "FBF single-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_TAD_INT_L2DDBE,
		.descr = "L2D double-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_TAD_INT_SBFDBE,
		.descr = "SBF double-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_TAD_INT_FBFDBE,
		.descr = "FBF double-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_TAD_INT_TAGDBE,
		.descr = "TAG double-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_TAD_INT_RTGDBE,
		.descr = "RTG double-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_TAD_INT_WRDISOCI,
		.descr = "Write to a disabled CCPI",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_TAD_INT_RDDISOCI,
		.descr = "Read from a disabled CCPI",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_TAD_INT_WRDISLMC,
		.descr = "Write to a disabled LMC",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_TAD_INT_RDDISLMC,
		.descr = "Read from a disabled LMC",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_TAD_INT_LFBTO,
		.descr = "LFB entry timeout",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_TAD_INT_GSYNCTO,
		.descr = "Global sync CCPI timeout",
	पूर्ण,
	अणु0, 0, शून्यपूर्ण,
पूर्ण;

#घोषणा L2C_TAD_INT_TAG		(L2C_TAD_INT_TAGDBE)

#घोषणा L2C_TAD_INT_RTG		(L2C_TAD_INT_RTGDBE)

#घोषणा L2C_TAD_INT_DISLMC	(L2C_TAD_INT_WRDISLMC | L2C_TAD_INT_RDDISLMC)

#घोषणा L2C_TAD_INT_DISOCI	(L2C_TAD_INT_WRDISOCI | L2C_TAD_INT_RDDISOCI)

#घोषणा L2C_TAD_INT_ENA_ALL	(L2C_TAD_INT_ECC | L2C_TAD_INT_TAG | \
				 L2C_TAD_INT_RTG | \
				 L2C_TAD_INT_DISLMC | L2C_TAD_INT_DISOCI | \
				 L2C_TAD_INT_LFBTO)

#घोषणा L2C_TAD_TIMETWO		0x50000
#घोषणा L2C_TAD_TIMEOUT		0x50100
#घोषणा L2C_TAD_ERR		0x60000
#घोषणा L2C_TAD_TQD_ERR		0x60100
#घोषणा L2C_TAD_TTG_ERR		0x60200


#घोषणा L2C_CBC_INT_W1C		0x60000

#घोषणा L2C_CBC_INT_RSDSBE	 BIT(0)
#घोषणा L2C_CBC_INT_RSDDBE	 BIT(1)

#घोषणा L2C_CBC_INT_RSD		 (L2C_CBC_INT_RSDSBE | L2C_CBC_INT_RSDDBE)

#घोषणा L2C_CBC_INT_MIBSBE	 BIT(4)
#घोषणा L2C_CBC_INT_MIBDBE	 BIT(5)

#घोषणा L2C_CBC_INT_MIB		 (L2C_CBC_INT_MIBSBE | L2C_CBC_INT_MIBDBE)

#घोषणा L2C_CBC_INT_IORDDISOCI	 BIT(6)
#घोषणा L2C_CBC_INT_IOWRDISOCI	 BIT(7)

#घोषणा L2C_CBC_INT_IODISOCI	 (L2C_CBC_INT_IORDDISOCI | \
				  L2C_CBC_INT_IOWRDISOCI)

#घोषणा L2C_CBC_INT_CE		 (L2C_CBC_INT_RSDSBE | L2C_CBC_INT_MIBSBE)
#घोषणा L2C_CBC_INT_UE		 (L2C_CBC_INT_RSDDBE | L2C_CBC_INT_MIBDBE)


अटल स्थिर काष्ठा error_descr l2_cbc_errors[] = अणु
	अणु
		.type  = ERR_CORRECTED,
		.mask  = L2C_CBC_INT_RSDSBE,
		.descr = "RSD single-bit error",
	पूर्ण,
	अणु
		.type  = ERR_CORRECTED,
		.mask  = L2C_CBC_INT_MIBSBE,
		.descr = "MIB single-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_CBC_INT_RSDDBE,
		.descr = "RSD double-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_CBC_INT_MIBDBE,
		.descr = "MIB double-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_CBC_INT_IORDDISOCI,
		.descr = "Read from a disabled CCPI",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_CBC_INT_IOWRDISOCI,
		.descr = "Write to a disabled CCPI",
	पूर्ण,
	अणु0, 0, शून्यपूर्ण,
पूर्ण;

#घोषणा L2C_CBC_INT_W1S		0x60008
#घोषणा L2C_CBC_INT_ENA_W1C	0x60020

#घोषणा L2C_CBC_INT_ENA_ALL	 (L2C_CBC_INT_RSD | L2C_CBC_INT_MIB | \
				  L2C_CBC_INT_IODISOCI)

#घोषणा L2C_CBC_INT_ENA_W1S	0x60028

#घोषणा L2C_CBC_IODISOCIERR	0x80008
#घोषणा L2C_CBC_IOCERR		0x80010
#घोषणा L2C_CBC_RSDERR		0x80018
#घोषणा L2C_CBC_MIBERR		0x80020


#घोषणा L2C_MCI_INT_W1C		0x0

#घोषणा L2C_MCI_INT_VBFSBE	 BIT(0)
#घोषणा L2C_MCI_INT_VBFDBE	 BIT(1)

अटल स्थिर काष्ठा error_descr l2_mci_errors[] = अणु
	अणु
		.type  = ERR_CORRECTED,
		.mask  = L2C_MCI_INT_VBFSBE,
		.descr = "VBF single-bit error",
	पूर्ण,
	अणु
		.type  = ERR_UNCORRECTED,
		.mask  = L2C_MCI_INT_VBFDBE,
		.descr = "VBF double-bit error",
	पूर्ण,
	अणु0, 0, शून्यपूर्ण,
पूर्ण;

#घोषणा L2C_MCI_INT_W1S		0x8
#घोषणा L2C_MCI_INT_ENA_W1C	0x20

#घोषणा L2C_MCI_INT_ENA_ALL	 (L2C_MCI_INT_VBFSBE | L2C_MCI_INT_VBFDBE)

#घोषणा L2C_MCI_INT_ENA_W1S	0x28

#घोषणा L2C_MCI_ERR		0x10000

#घोषणा L2C_MESSAGE_SIZE	SZ_1K
#घोषणा L2C_OTHER_SIZE		(50 * ARRAY_SIZE(l2_tad_errors))

काष्ठा l2c_err_ctx अणु
	अक्षर *reg_ext_name;
	u64  reg_पूर्णांक;
	u64  reg_ext;
पूर्ण;

काष्ठा thunderx_l2c अणु
	व्योम __iomem *regs;
	काष्ठा pci_dev *pdev;
	काष्ठा edac_device_ctl_info *edac_dev;

	काष्ठा dentry *debugfs;

	पूर्णांक index;

	काष्ठा msix_entry msix_ent;

	काष्ठा l2c_err_ctx err_ctx[RING_ENTRIES];
	अचिन्हित दीर्घ ring_head;
	अचिन्हित दीर्घ ring_tail;
पूर्ण;

अटल irqवापस_t thunderx_l2c_tad_isr(पूर्णांक irq, व्योम *irq_id)
अणु
	काष्ठा msix_entry *msix = irq_id;
	काष्ठा thunderx_l2c *tad = container_of(msix, काष्ठा thunderx_l2c,
						msix_ent);

	अचिन्हित दीर्घ head = ring_pos(tad->ring_head, ARRAY_SIZE(tad->err_ctx));
	काष्ठा l2c_err_ctx *ctx = &tad->err_ctx[head];

	ctx->reg_पूर्णांक = पढ़ोq(tad->regs + L2C_TAD_INT_W1C);

	अगर (ctx->reg_पूर्णांक & L2C_TAD_INT_ECC) अणु
		ctx->reg_ext_name = "TQD_ERR";
		ctx->reg_ext = पढ़ोq(tad->regs + L2C_TAD_TQD_ERR);
	पूर्ण अन्यथा अगर (ctx->reg_पूर्णांक & L2C_TAD_INT_TAG) अणु
		ctx->reg_ext_name = "TTG_ERR";
		ctx->reg_ext = पढ़ोq(tad->regs + L2C_TAD_TTG_ERR);
	पूर्ण अन्यथा अगर (ctx->reg_पूर्णांक & L2C_TAD_INT_LFBTO) अणु
		ctx->reg_ext_name = "TIMEOUT";
		ctx->reg_ext = पढ़ोq(tad->regs + L2C_TAD_TIMEOUT);
	पूर्ण अन्यथा अगर (ctx->reg_पूर्णांक & L2C_TAD_INT_DISOCI) अणु
		ctx->reg_ext_name = "ERR";
		ctx->reg_ext = पढ़ोq(tad->regs + L2C_TAD_ERR);
	पूर्ण

	ग_लिखोq(ctx->reg_पूर्णांक, tad->regs + L2C_TAD_INT_W1C);

	tad->ring_head++;

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t thunderx_l2c_cbc_isr(पूर्णांक irq, व्योम *irq_id)
अणु
	काष्ठा msix_entry *msix = irq_id;
	काष्ठा thunderx_l2c *cbc = container_of(msix, काष्ठा thunderx_l2c,
						msix_ent);

	अचिन्हित दीर्घ head = ring_pos(cbc->ring_head, ARRAY_SIZE(cbc->err_ctx));
	काष्ठा l2c_err_ctx *ctx = &cbc->err_ctx[head];

	ctx->reg_पूर्णांक = पढ़ोq(cbc->regs + L2C_CBC_INT_W1C);

	अगर (ctx->reg_पूर्णांक & L2C_CBC_INT_RSD) अणु
		ctx->reg_ext_name = "RSDERR";
		ctx->reg_ext = पढ़ोq(cbc->regs + L2C_CBC_RSDERR);
	पूर्ण अन्यथा अगर (ctx->reg_पूर्णांक & L2C_CBC_INT_MIB) अणु
		ctx->reg_ext_name = "MIBERR";
		ctx->reg_ext = पढ़ोq(cbc->regs + L2C_CBC_MIBERR);
	पूर्ण अन्यथा अगर (ctx->reg_पूर्णांक & L2C_CBC_INT_IODISOCI) अणु
		ctx->reg_ext_name = "IODISOCIERR";
		ctx->reg_ext = पढ़ोq(cbc->regs + L2C_CBC_IODISOCIERR);
	पूर्ण

	ग_लिखोq(ctx->reg_पूर्णांक, cbc->regs + L2C_CBC_INT_W1C);

	cbc->ring_head++;

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t thunderx_l2c_mci_isr(पूर्णांक irq, व्योम *irq_id)
अणु
	काष्ठा msix_entry *msix = irq_id;
	काष्ठा thunderx_l2c *mci = container_of(msix, काष्ठा thunderx_l2c,
						msix_ent);

	अचिन्हित दीर्घ head = ring_pos(mci->ring_head, ARRAY_SIZE(mci->err_ctx));
	काष्ठा l2c_err_ctx *ctx = &mci->err_ctx[head];

	ctx->reg_पूर्णांक = पढ़ोq(mci->regs + L2C_MCI_INT_W1C);
	ctx->reg_ext = पढ़ोq(mci->regs + L2C_MCI_ERR);

	ग_लिखोq(ctx->reg_पूर्णांक, mci->regs + L2C_MCI_INT_W1C);

	ctx->reg_ext_name = "ERR";

	mci->ring_head++;

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t thunderx_l2c_thपढ़ोed_isr(पूर्णांक irq, व्योम *irq_id)
अणु
	काष्ठा msix_entry *msix = irq_id;
	काष्ठा thunderx_l2c *l2c = container_of(msix, काष्ठा thunderx_l2c,
						msix_ent);

	अचिन्हित दीर्घ tail = ring_pos(l2c->ring_tail, ARRAY_SIZE(l2c->err_ctx));
	काष्ठा l2c_err_ctx *ctx = &l2c->err_ctx[tail];
	irqवापस_t ret = IRQ_NONE;

	u64 mask_ue, mask_ce;
	स्थिर काष्ठा error_descr *l2_errors;
	अक्षर *reg_पूर्णांक_name;

	अक्षर *msg;
	अक्षर *other;

	msg = kदो_स्मृति(OCX_MESSAGE_SIZE, GFP_KERNEL);
	other = kदो_स्मृति(OCX_OTHER_SIZE, GFP_KERNEL);

	अगर (!msg || !other)
		जाओ err_मुक्त;

	चयन (l2c->pdev->device) अणु
	हाल PCI_DEVICE_ID_THUNDER_L2C_TAD:
		reg_पूर्णांक_name = "L2C_TAD_INT";
		mask_ue = L2C_TAD_INT_UE;
		mask_ce = L2C_TAD_INT_CE;
		l2_errors = l2_tad_errors;
		अवरोध;
	हाल PCI_DEVICE_ID_THUNDER_L2C_CBC:
		reg_पूर्णांक_name = "L2C_CBC_INT";
		mask_ue = L2C_CBC_INT_UE;
		mask_ce = L2C_CBC_INT_CE;
		l2_errors = l2_cbc_errors;
		अवरोध;
	हाल PCI_DEVICE_ID_THUNDER_L2C_MCI:
		reg_पूर्णांक_name = "L2C_MCI_INT";
		mask_ue = L2C_MCI_INT_VBFDBE;
		mask_ce = L2C_MCI_INT_VBFSBE;
		l2_errors = l2_mci_errors;
		अवरोध;
	शेष:
		dev_err(&l2c->pdev->dev, "Unsupported device: %04x\n",
			l2c->pdev->device);
		जाओ err_मुक्त;
	पूर्ण

	जबतक (CIRC_CNT(l2c->ring_head, l2c->ring_tail,
			ARRAY_SIZE(l2c->err_ctx))) अणु
		snम_लिखो(msg, L2C_MESSAGE_SIZE,
			 "%s: %s: %016llx, %s: %016llx",
			 l2c->edac_dev->ctl_name, reg_पूर्णांक_name, ctx->reg_पूर्णांक,
			 ctx->reg_ext_name, ctx->reg_ext);

		decode_रेजिस्टर(other, L2C_OTHER_SIZE, l2_errors, ctx->reg_पूर्णांक);

		म_जोड़न(msg, other, L2C_MESSAGE_SIZE);

		अगर (ctx->reg_पूर्णांक & mask_ue)
			edac_device_handle_ue(l2c->edac_dev, 0, 0, msg);
		अन्यथा अगर (ctx->reg_पूर्णांक & mask_ce)
			edac_device_handle_ce(l2c->edac_dev, 0, 0, msg);

		l2c->ring_tail++;
	पूर्ण

	ret = IRQ_HANDLED;

err_मुक्त:
	kमुक्त(other);
	kमुक्त(msg);

	वापस ret;
पूर्ण

#घोषणा L2C_DEBUGFS_ATTR(_name, _reg)	DEBUGFS_REG_ATTR(l2c, _name, _reg)

L2C_DEBUGFS_ATTR(tad_पूर्णांक, L2C_TAD_INT_W1S);

अटल काष्ठा debugfs_entry *l2c_tad_dfs_ents[] = अणु
	&debugfs_tad_पूर्णांक,
पूर्ण;

L2C_DEBUGFS_ATTR(cbc_पूर्णांक, L2C_CBC_INT_W1S);

अटल काष्ठा debugfs_entry *l2c_cbc_dfs_ents[] = अणु
	&debugfs_cbc_पूर्णांक,
पूर्ण;

L2C_DEBUGFS_ATTR(mci_पूर्णांक, L2C_MCI_INT_W1S);

अटल काष्ठा debugfs_entry *l2c_mci_dfs_ents[] = अणु
	&debugfs_mci_पूर्णांक,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id thunderx_l2c_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_THUNDER_L2C_TAD), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_THUNDER_L2C_CBC), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, PCI_DEVICE_ID_THUNDER_L2C_MCI), पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

अटल पूर्णांक thunderx_l2c_probe(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा thunderx_l2c *l2c;
	काष्ठा edac_device_ctl_info *edac_dev;
	काष्ठा debugfs_entry **l2c_devattr;
	माप_प्रकार dfs_entries;
	irqवापस_t (*thunderx_l2c_isr)(पूर्णांक, व्योम *) = शून्य;
	अक्षर name[32];
	स्थिर अक्षर *fmt;
	u64 reg_en_offs, reg_en_mask;
	पूर्णांक idx;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot enable PCI device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = pcim_iomap_regions(pdev, BIT(0), "thunderx_l2c");
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot map PCI resources: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_THUNDER_L2C_TAD:
		thunderx_l2c_isr = thunderx_l2c_tad_isr;
		l2c_devattr = l2c_tad_dfs_ents;
		dfs_entries = ARRAY_SIZE(l2c_tad_dfs_ents);
		fmt = "L2C-TAD%d";
		reg_en_offs = L2C_TAD_INT_ENA_W1S;
		reg_en_mask = L2C_TAD_INT_ENA_ALL;
		अवरोध;
	हाल PCI_DEVICE_ID_THUNDER_L2C_CBC:
		thunderx_l2c_isr = thunderx_l2c_cbc_isr;
		l2c_devattr = l2c_cbc_dfs_ents;
		dfs_entries = ARRAY_SIZE(l2c_cbc_dfs_ents);
		fmt = "L2C-CBC%d";
		reg_en_offs = L2C_CBC_INT_ENA_W1S;
		reg_en_mask = L2C_CBC_INT_ENA_ALL;
		अवरोध;
	हाल PCI_DEVICE_ID_THUNDER_L2C_MCI:
		thunderx_l2c_isr = thunderx_l2c_mci_isr;
		l2c_devattr = l2c_mci_dfs_ents;
		dfs_entries = ARRAY_SIZE(l2c_mci_dfs_ents);
		fmt = "L2C-MCI%d";
		reg_en_offs = L2C_MCI_INT_ENA_W1S;
		reg_en_mask = L2C_MCI_INT_ENA_ALL;
		अवरोध;
	शेष:
		//Should never ever get here
		dev_err(&pdev->dev, "Unsupported PCI device: %04x\n",
			pdev->device);
		वापस -EINVAL;
	पूर्ण

	idx = edac_device_alloc_index();
	snम_लिखो(name, माप(name), fmt, idx);

	edac_dev = edac_device_alloc_ctl_info(माप(काष्ठा thunderx_l2c),
					      name, 1, "L2C", 1, 0,
					      शून्य, 0, idx);
	अगर (!edac_dev) अणु
		dev_err(&pdev->dev, "Cannot allocate EDAC device\n");
		वापस -ENOMEM;
	पूर्ण

	l2c = edac_dev->pvt_info;
	l2c->edac_dev = edac_dev;

	l2c->regs = pcim_iomap_table(pdev)[0];
	अगर (!l2c->regs) अणु
		dev_err(&pdev->dev, "Cannot map PCI resources\n");
		ret = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	l2c->pdev = pdev;

	l2c->ring_head = 0;
	l2c->ring_tail = 0;

	l2c->msix_ent.entry = 0;
	l2c->msix_ent.vector = 0;

	ret = pci_enable_msix_exact(pdev, &l2c->msix_ent, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot enable interrupt: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, l2c->msix_ent.vector,
					thunderx_l2c_isr,
					thunderx_l2c_thपढ़ोed_isr,
					0, "[EDAC] ThunderX L2C",
					&l2c->msix_ent);
	अगर (ret)
		जाओ err_मुक्त;

	edac_dev->dev = &pdev->dev;
	edac_dev->dev_name = dev_name(&pdev->dev);
	edac_dev->mod_name = "thunderx-l2c";
	edac_dev->ctl_name = "thunderx-l2c";

	ret = edac_device_add_device(edac_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot add EDAC device: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_EDAC_DEBUG)) अणु
		l2c->debugfs = edac_debugfs_create_dir(pdev->dev.kobj.name);

		ret = thunderx_create_debugfs_nodes(l2c->debugfs, l2c_devattr,
					      l2c, dfs_entries);

		अगर (ret != dfs_entries) अणु
			dev_warn(&pdev->dev, "Error creating debugfs entries: %d%s\n",
				 ret, ret >= 0 ? " created" : "");
		पूर्ण
	पूर्ण

	pci_set_drvdata(pdev, edac_dev);

	ग_लिखोq(reg_en_mask, l2c->regs + reg_en_offs);

	वापस 0;

err_मुक्त:
	edac_device_मुक्त_ctl_info(edac_dev);

	वापस ret;
पूर्ण

अटल व्योम thunderx_l2c_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = pci_get_drvdata(pdev);
	काष्ठा thunderx_l2c *l2c = edac_dev->pvt_info;

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_THUNDER_L2C_TAD:
		ग_लिखोq(L2C_TAD_INT_ENA_ALL, l2c->regs + L2C_TAD_INT_ENA_W1C);
		अवरोध;
	हाल PCI_DEVICE_ID_THUNDER_L2C_CBC:
		ग_लिखोq(L2C_CBC_INT_ENA_ALL, l2c->regs + L2C_CBC_INT_ENA_W1C);
		अवरोध;
	हाल PCI_DEVICE_ID_THUNDER_L2C_MCI:
		ग_लिखोq(L2C_MCI_INT_ENA_ALL, l2c->regs + L2C_MCI_INT_ENA_W1C);
		अवरोध;
	पूर्ण

	edac_debugfs_हटाओ_recursive(l2c->debugfs);

	edac_device_del_device(&pdev->dev);
	edac_device_मुक्त_ctl_info(edac_dev);
पूर्ण

MODULE_DEVICE_TABLE(pci, thunderx_l2c_pci_tbl);

अटल काष्ठा pci_driver thunderx_l2c_driver = अणु
	.name     = "thunderx_l2c_edac",
	.probe    = thunderx_l2c_probe,
	.हटाओ   = thunderx_l2c_हटाओ,
	.id_table = thunderx_l2c_pci_tbl,
पूर्ण;

अटल पूर्णांक __init thunderx_edac_init(व्योम)
अणु
	पूर्णांक rc = 0;

	rc = pci_रेजिस्टर_driver(&thunderx_lmc_driver);
	अगर (rc)
		वापस rc;

	rc = pci_रेजिस्टर_driver(&thunderx_ocx_driver);
	अगर (rc)
		जाओ err_lmc;

	rc = pci_रेजिस्टर_driver(&thunderx_l2c_driver);
	अगर (rc)
		जाओ err_ocx;

	वापस rc;
err_ocx:
	pci_unरेजिस्टर_driver(&thunderx_ocx_driver);
err_lmc:
	pci_unरेजिस्टर_driver(&thunderx_lmc_driver);

	वापस rc;
पूर्ण

अटल व्योम __निकास thunderx_edac_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&thunderx_l2c_driver);
	pci_unरेजिस्टर_driver(&thunderx_ocx_driver);
	pci_unरेजिस्टर_driver(&thunderx_lmc_driver);

पूर्ण

module_init(thunderx_edac_init);
module_निकास(thunderx_edac_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Cavium, Inc.");
MODULE_DESCRIPTION("EDAC Driver for Cavium ThunderX");
