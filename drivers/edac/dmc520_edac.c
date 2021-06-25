<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * EDAC driver क्रम DMC-520 memory controller.
 *
 * The driver supports 10 पूर्णांकerrupt lines,
 * though only dram_ecc_errc and dram_ecc_errd are currently handled.
 *
 * Authors:	Rui Zhao <ruizhao@microsoft.com>
 *		Lei Wang <lewan@microsoft.com>
 *		Shiping Ji <shji@microsoft.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/edac.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश "edac_mc.h"

/* DMC-520 रेजिस्टरs */
#घोषणा REG_OFFSET_FEATURE_CONFIG			0x130
#घोषणा REG_OFFSET_ECC_ERRC_COUNT_31_00		0x158
#घोषणा REG_OFFSET_ECC_ERRC_COUNT_63_32		0x15C
#घोषणा REG_OFFSET_ECC_ERRD_COUNT_31_00		0x160
#घोषणा REG_OFFSET_ECC_ERRD_COUNT_63_32		0x164
#घोषणा REG_OFFSET_INTERRUPT_CONTROL			0x500
#घोषणा REG_OFFSET_INTERRUPT_CLR			0x508
#घोषणा REG_OFFSET_INTERRUPT_STATUS			0x510
#घोषणा REG_OFFSET_DRAM_ECC_ERRC_INT_INFO_31_00	0x528
#घोषणा REG_OFFSET_DRAM_ECC_ERRC_INT_INFO_63_32	0x52C
#घोषणा REG_OFFSET_DRAM_ECC_ERRD_INT_INFO_31_00	0x530
#घोषणा REG_OFFSET_DRAM_ECC_ERRD_INT_INFO_63_32	0x534
#घोषणा REG_OFFSET_ADDRESS_CONTROL_NOW			0x1010
#घोषणा REG_OFFSET_MEMORY_TYPE_NOW			0x1128
#घोषणा REG_OFFSET_SCRUB_CONTROL0_NOW			0x1170
#घोषणा REG_OFFSET_FORMAT_CONTROL			0x18

/* DMC-520 types, masks and bitfields */
#घोषणा RAM_ECC_INT_CE_BIT			BIT(0)
#घोषणा RAM_ECC_INT_UE_BIT			BIT(1)
#घोषणा DRAM_ECC_INT_CE_BIT			BIT(2)
#घोषणा DRAM_ECC_INT_UE_BIT			BIT(3)
#घोषणा FAILED_ACCESS_INT_BIT			BIT(4)
#घोषणा FAILED_PROG_INT_BIT			BIT(5)
#घोषणा LINK_ERR_INT_BIT			BIT(6)
#घोषणा TEMPERATURE_EVENT_INT_BIT		BIT(7)
#घोषणा ARCH_FSM_INT_BIT			BIT(8)
#घोषणा PHY_REQUEST_INT_BIT			BIT(9)
#घोषणा MEMORY_WIDTH_MASK			GENMASK(1, 0)
#घोषणा SCRUB_TRIGGER0_NEXT_MASK		GENMASK(1, 0)
#घोषणा REG_FIELD_DRAM_ECC_ENABLED		GENMASK(1, 0)
#घोषणा REG_FIELD_MEMORY_TYPE			GENMASK(2, 0)
#घोषणा REG_FIELD_DEVICE_WIDTH			GENMASK(9, 8)
#घोषणा REG_FIELD_ADDRESS_CONTROL_COL		GENMASK(2,  0)
#घोषणा REG_FIELD_ADDRESS_CONTROL_ROW		GENMASK(10, 8)
#घोषणा REG_FIELD_ADDRESS_CONTROL_BANK		GENMASK(18, 16)
#घोषणा REG_FIELD_ADDRESS_CONTROL_RANK		GENMASK(25, 24)
#घोषणा REG_FIELD_ERR_INFO_LOW_VALID		BIT(0)
#घोषणा REG_FIELD_ERR_INFO_LOW_COL		GENMASK(10, 1)
#घोषणा REG_FIELD_ERR_INFO_LOW_ROW		GENMASK(28, 11)
#घोषणा REG_FIELD_ERR_INFO_LOW_RANK		GENMASK(31, 29)
#घोषणा REG_FIELD_ERR_INFO_HIGH_BANK		GENMASK(3, 0)
#घोषणा REG_FIELD_ERR_INFO_HIGH_VALID		BIT(31)

#घोषणा DRAM_ADDRESS_CONTROL_MIN_COL_BITS	8
#घोषणा DRAM_ADDRESS_CONTROL_MIN_ROW_BITS	11

#घोषणा DMC520_SCRUB_TRIGGER_ERR_DETECT	2
#घोषणा DMC520_SCRUB_TRIGGER_IDLE		3

/* Driver settings */
/*
 * The max-length message would be: "rank:7 bank:15 row:262143 col:1023".
 * Max length is 34. Using a 40-size buffer is enough.
 */
#घोषणा DMC520_MSG_BUF_SIZE			40
#घोषणा EDAC_MOD_NAME				"dmc520-edac"
#घोषणा EDAC_CTL_NAME				"dmc520"

/* the data bus width क्रम the attached memory chips. */
क्रमागत dmc520_mem_width अणु
	MEM_WIDTH_X32 = 2,
	MEM_WIDTH_X64 = 3
पूर्ण;

/* memory type */
क्रमागत dmc520_mem_type अणु
	MEM_TYPE_DDR3 = 1,
	MEM_TYPE_DDR4 = 2
पूर्ण;

/* memory device width */
क्रमागत dmc520_dev_width अणु
	DEV_WIDTH_X4 = 0,
	DEV_WIDTH_X8 = 1,
	DEV_WIDTH_X16 = 2
पूर्ण;

काष्ठा ecc_error_info अणु
	u32 col;
	u32 row;
	u32 bank;
	u32 rank;
पूर्ण;

/* The पूर्णांकerrupt config */
काष्ठा dmc520_irq_config अणु
	अक्षर *name;
	पूर्णांक mask;
पूर्ण;

/* The पूर्णांकerrupt mappings */
अटल काष्ठा dmc520_irq_config dmc520_irq_configs[] = अणु
	अणु
		.name = "ram_ecc_errc",
		.mask = RAM_ECC_INT_CE_BIT
	पूर्ण,
	अणु
		.name = "ram_ecc_errd",
		.mask = RAM_ECC_INT_UE_BIT
	पूर्ण,
	अणु
		.name = "dram_ecc_errc",
		.mask = DRAM_ECC_INT_CE_BIT
	पूर्ण,
	अणु
		.name = "dram_ecc_errd",
		.mask = DRAM_ECC_INT_UE_BIT
	पूर्ण,
	अणु
		.name = "failed_access",
		.mask = FAILED_ACCESS_INT_BIT
	पूर्ण,
	अणु
		.name = "failed_prog",
		.mask = FAILED_PROG_INT_BIT
	पूर्ण,
	अणु
		.name = "link_err",
		.mask = LINK_ERR_INT_BIT
	पूर्ण,
	अणु
		.name = "temperature_event",
		.mask = TEMPERATURE_EVENT_INT_BIT
	पूर्ण,
	अणु
		.name = "arch_fsm",
		.mask = ARCH_FSM_INT_BIT
	पूर्ण,
	अणु
		.name = "phy_request",
		.mask = PHY_REQUEST_INT_BIT
	पूर्ण
पूर्ण;

#घोषणा NUMBER_OF_IRQS				ARRAY_SIZE(dmc520_irq_configs)

/*
 * The EDAC driver निजी data.
 * error_lock is to protect concurrent ग_लिखोs to the mci->error_desc through
 * edac_mc_handle_error().
 */
काष्ठा dmc520_edac अणु
	व्योम __iomem *reg_base;
	spinlock_t error_lock;
	u32 mem_width_in_bytes;
	पूर्णांक irqs[NUMBER_OF_IRQS];
	पूर्णांक masks[NUMBER_OF_IRQS];
पूर्ण;

अटल पूर्णांक dmc520_mc_idx;

अटल u32 dmc520_पढ़ो_reg(काष्ठा dmc520_edac *pvt, u32 offset)
अणु
	वापस पढ़ोl(pvt->reg_base + offset);
पूर्ण

अटल व्योम dmc520_ग_लिखो_reg(काष्ठा dmc520_edac *pvt, u32 val, u32 offset)
अणु
	ग_लिखोl(val, pvt->reg_base + offset);
पूर्ण

अटल u32 dmc520_calc_dram_ecc_error(u32 value)
अणु
	u32 total = 0;

	/* Each rank's error counter takes one byte. */
	जबतक (value > 0) अणु
		total += (value & 0xFF);
		value >>= 8;
	पूर्ण
	वापस total;
पूर्ण

अटल u32 dmc520_get_dram_ecc_error_count(काष्ठा dmc520_edac *pvt,
					    bool is_ce)
अणु
	u32 reg_offset_low, reg_offset_high;
	u32 err_low, err_high;
	u32 err_count;

	reg_offset_low = is_ce ? REG_OFFSET_ECC_ERRC_COUNT_31_00 :
				 REG_OFFSET_ECC_ERRD_COUNT_31_00;
	reg_offset_high = is_ce ? REG_OFFSET_ECC_ERRC_COUNT_63_32 :
				  REG_OFFSET_ECC_ERRD_COUNT_63_32;

	err_low = dmc520_पढ़ो_reg(pvt, reg_offset_low);
	err_high = dmc520_पढ़ो_reg(pvt, reg_offset_high);
	/* Reset error counters */
	dmc520_ग_लिखो_reg(pvt, 0, reg_offset_low);
	dmc520_ग_लिखो_reg(pvt, 0, reg_offset_high);

	err_count = dmc520_calc_dram_ecc_error(err_low) +
		   dmc520_calc_dram_ecc_error(err_high);

	वापस err_count;
पूर्ण

अटल व्योम dmc520_get_dram_ecc_error_info(काष्ठा dmc520_edac *pvt,
					    bool is_ce,
					    काष्ठा ecc_error_info *info)
अणु
	u32 reg_offset_low, reg_offset_high;
	u32 reg_val_low, reg_val_high;
	bool valid;

	reg_offset_low = is_ce ? REG_OFFSET_DRAM_ECC_ERRC_INT_INFO_31_00 :
				 REG_OFFSET_DRAM_ECC_ERRD_INT_INFO_31_00;
	reg_offset_high = is_ce ? REG_OFFSET_DRAM_ECC_ERRC_INT_INFO_63_32 :
				  REG_OFFSET_DRAM_ECC_ERRD_INT_INFO_63_32;

	reg_val_low = dmc520_पढ़ो_reg(pvt, reg_offset_low);
	reg_val_high = dmc520_पढ़ो_reg(pvt, reg_offset_high);

	valid = (FIELD_GET(REG_FIELD_ERR_INFO_LOW_VALID, reg_val_low) != 0) &&
		(FIELD_GET(REG_FIELD_ERR_INFO_HIGH_VALID, reg_val_high) != 0);

	अगर (valid) अणु
		info->col = FIELD_GET(REG_FIELD_ERR_INFO_LOW_COL, reg_val_low);
		info->row = FIELD_GET(REG_FIELD_ERR_INFO_LOW_ROW, reg_val_low);
		info->rank = FIELD_GET(REG_FIELD_ERR_INFO_LOW_RANK, reg_val_low);
		info->bank = FIELD_GET(REG_FIELD_ERR_INFO_HIGH_BANK, reg_val_high);
	पूर्ण अन्यथा अणु
		स_रखो(info, 0, माप(*info));
	पूर्ण
पूर्ण

अटल bool dmc520_is_ecc_enabled(व्योम __iomem *reg_base)
अणु
	u32 reg_val = पढ़ोl(reg_base + REG_OFFSET_FEATURE_CONFIG);

	वापस FIELD_GET(REG_FIELD_DRAM_ECC_ENABLED, reg_val);
पूर्ण

अटल क्रमागत scrub_type dmc520_get_scrub_type(काष्ठा dmc520_edac *pvt)
अणु
	क्रमागत scrub_type type = SCRUB_NONE;
	u32 reg_val, scrub_cfg;

	reg_val = dmc520_पढ़ो_reg(pvt, REG_OFFSET_SCRUB_CONTROL0_NOW);
	scrub_cfg = FIELD_GET(SCRUB_TRIGGER0_NEXT_MASK, reg_val);

	अगर (scrub_cfg == DMC520_SCRUB_TRIGGER_ERR_DETECT ||
	    scrub_cfg == DMC520_SCRUB_TRIGGER_IDLE)
		type = SCRUB_HW_PROG;

	वापस type;
पूर्ण

/* Get the memory data bus width, in number of bytes. */
अटल u32 dmc520_get_memory_width(काष्ठा dmc520_edac *pvt)
अणु
	क्रमागत dmc520_mem_width mem_width_field;
	u32 mem_width_in_bytes = 0;
	u32 reg_val;

	reg_val = dmc520_पढ़ो_reg(pvt, REG_OFFSET_FORMAT_CONTROL);
	mem_width_field = FIELD_GET(MEMORY_WIDTH_MASK, reg_val);

	अगर (mem_width_field == MEM_WIDTH_X32)
		mem_width_in_bytes = 4;
	अन्यथा अगर (mem_width_field == MEM_WIDTH_X64)
		mem_width_in_bytes = 8;
	वापस mem_width_in_bytes;
पूर्ण

अटल क्रमागत mem_type dmc520_get_mtype(काष्ठा dmc520_edac *pvt)
अणु
	क्रमागत mem_type mt = MEM_UNKNOWN;
	क्रमागत dmc520_mem_type type;
	u32 reg_val;

	reg_val = dmc520_पढ़ो_reg(pvt, REG_OFFSET_MEMORY_TYPE_NOW);
	type = FIELD_GET(REG_FIELD_MEMORY_TYPE, reg_val);

	चयन (type) अणु
	हाल MEM_TYPE_DDR3:
		mt = MEM_DDR3;
		अवरोध;

	हाल MEM_TYPE_DDR4:
		mt = MEM_DDR4;
		अवरोध;
	पूर्ण

	वापस mt;
पूर्ण

अटल क्रमागत dev_type dmc520_get_dtype(काष्ठा dmc520_edac *pvt)
अणु
	क्रमागत dmc520_dev_width device_width;
	क्रमागत dev_type dt = DEV_UNKNOWN;
	u32 reg_val;

	reg_val = dmc520_पढ़ो_reg(pvt, REG_OFFSET_MEMORY_TYPE_NOW);
	device_width = FIELD_GET(REG_FIELD_DEVICE_WIDTH, reg_val);

	चयन (device_width) अणु
	हाल DEV_WIDTH_X4:
		dt = DEV_X4;
		अवरोध;

	हाल DEV_WIDTH_X8:
		dt = DEV_X8;
		अवरोध;

	हाल DEV_WIDTH_X16:
		dt = DEV_X16;
		अवरोध;
	पूर्ण

	वापस dt;
पूर्ण

अटल u32 dmc520_get_rank_count(व्योम __iomem *reg_base)
अणु
	u32 reg_val, rank_bits;

	reg_val = पढ़ोl(reg_base + REG_OFFSET_ADDRESS_CONTROL_NOW);
	rank_bits = FIELD_GET(REG_FIELD_ADDRESS_CONTROL_RANK, reg_val);

	वापस BIT(rank_bits);
पूर्ण

अटल u64 dmc520_get_rank_size(काष्ठा dmc520_edac *pvt)
अणु
	u32 reg_val, col_bits, row_bits, bank_bits;

	reg_val = dmc520_पढ़ो_reg(pvt, REG_OFFSET_ADDRESS_CONTROL_NOW);

	col_bits = FIELD_GET(REG_FIELD_ADDRESS_CONTROL_COL, reg_val) +
		   DRAM_ADDRESS_CONTROL_MIN_COL_BITS;
	row_bits = FIELD_GET(REG_FIELD_ADDRESS_CONTROL_ROW, reg_val) +
		   DRAM_ADDRESS_CONTROL_MIN_ROW_BITS;
	bank_bits = FIELD_GET(REG_FIELD_ADDRESS_CONTROL_BANK, reg_val);

	वापस (u64)pvt->mem_width_in_bytes << (col_bits + row_bits + bank_bits);
पूर्ण

अटल व्योम dmc520_handle_dram_ecc_errors(काष्ठा mem_ctl_info *mci,
					   bool is_ce)
अणु
	काष्ठा dmc520_edac *pvt = mci->pvt_info;
	अक्षर message[DMC520_MSG_BUF_SIZE];
	काष्ठा ecc_error_info info;
	u32 cnt;

	dmc520_get_dram_ecc_error_info(pvt, is_ce, &info);

	cnt = dmc520_get_dram_ecc_error_count(pvt, is_ce);
	अगर (!cnt)
		वापस;

	snम_लिखो(message, ARRAY_SIZE(message),
		 "rank:%d bank:%d row:%d col:%d",
		 info.rank, info.bank,
		 info.row, info.col);

	spin_lock(&pvt->error_lock);
	edac_mc_handle_error((is_ce ? HW_EVENT_ERR_CORRECTED :
			     HW_EVENT_ERR_UNCORRECTED),
			     mci, cnt, 0, 0, 0, info.rank, -1, -1,
			     message, "");
	spin_unlock(&pvt->error_lock);
पूर्ण

अटल irqवापस_t dmc520_edac_dram_ecc_isr(पूर्णांक irq, काष्ठा mem_ctl_info *mci,
					     bool is_ce)
अणु
	काष्ठा dmc520_edac *pvt = mci->pvt_info;
	u32 i_mask;

	i_mask = is_ce ? DRAM_ECC_INT_CE_BIT : DRAM_ECC_INT_UE_BIT;

	dmc520_handle_dram_ecc_errors(mci, is_ce);

	dmc520_ग_लिखो_reg(pvt, i_mask, REG_OFFSET_INTERRUPT_CLR);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dmc520_edac_dram_all_isr(पूर्णांक irq, काष्ठा mem_ctl_info *mci,
					     u32 irq_mask)
अणु
	काष्ठा dmc520_edac *pvt = mci->pvt_info;
	irqवापस_t irq_ret = IRQ_NONE;
	u32 status;

	status = dmc520_पढ़ो_reg(pvt, REG_OFFSET_INTERRUPT_STATUS);

	अगर ((irq_mask & DRAM_ECC_INT_CE_BIT) &&
		(status & DRAM_ECC_INT_CE_BIT))
		irq_ret = dmc520_edac_dram_ecc_isr(irq, mci, true);

	अगर ((irq_mask & DRAM_ECC_INT_UE_BIT) &&
		(status & DRAM_ECC_INT_UE_BIT))
		irq_ret = dmc520_edac_dram_ecc_isr(irq, mci, false);

	वापस irq_ret;
पूर्ण

अटल irqवापस_t dmc520_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mem_ctl_info *mci = data;
	काष्ठा dmc520_edac *pvt = mci->pvt_info;
	u32 mask = 0;
	पूर्णांक idx;

	क्रम (idx = 0; idx < NUMBER_OF_IRQS; idx++) अणु
		अगर (pvt->irqs[idx] == irq) अणु
			mask = pvt->masks[idx];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस dmc520_edac_dram_all_isr(irq, mci, mask);
पूर्ण

अटल व्योम dmc520_init_csrow(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा dmc520_edac *pvt = mci->pvt_info;
	काष्ठा csrow_info *csi;
	काष्ठा dimm_info *dimm;
	u32 pages_per_rank;
	क्रमागत dev_type dt;
	क्रमागत mem_type mt;
	पूर्णांक row, ch;
	u64 rs;

	dt = dmc520_get_dtype(pvt);
	mt = dmc520_get_mtype(pvt);
	rs = dmc520_get_rank_size(pvt);
	pages_per_rank = rs >> PAGE_SHIFT;

	क्रम (row = 0; row < mci->nr_csrows; row++) अणु
		csi = mci->csrows[row];

		क्रम (ch = 0; ch < csi->nr_channels; ch++) अणु
			dimm		= csi->channels[ch]->dimm;
			dimm->grain	= pvt->mem_width_in_bytes;
			dimm->dtype	= dt;
			dimm->mtype	= mt;
			dimm->edac_mode	= EDAC_FLAG_SECDED;
			dimm->nr_pages	= pages_per_rank / csi->nr_channels;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dmc520_edac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	bool रेजिस्टरed[NUMBER_OF_IRQS] = अणु false पूर्ण;
	पूर्णांक irqs[NUMBER_OF_IRQS] = अणु -ENXIO पूर्ण;
	पूर्णांक masks[NUMBER_OF_IRQS] = अणु 0 पूर्ण;
	काष्ठा edac_mc_layer layers[1];
	काष्ठा dmc520_edac *pvt = शून्य;
	काष्ठा mem_ctl_info *mci;
	व्योम __iomem *reg_base;
	u32 irq_mask_all = 0;
	काष्ठा resource *res;
	काष्ठा device *dev;
	पूर्णांक ret, idx, irq;
	u32 reg_val;

	/* Parse the device node */
	dev = &pdev->dev;

	क्रम (idx = 0; idx < NUMBER_OF_IRQS; idx++) अणु
		irq = platक्रमm_get_irq_byname(pdev, dmc520_irq_configs[idx].name);
		irqs[idx] = irq;
		masks[idx] = dmc520_irq_configs[idx].mask;
		अगर (irq >= 0) अणु
			irq_mask_all |= dmc520_irq_configs[idx].mask;
			edac_dbg(0, "Discovered %s, irq: %d.\n", dmc520_irq_configs[idx].name, irq);
		पूर्ण
	पूर्ण

	अगर (!irq_mask_all) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MOD_NAME,
			    "At least one valid interrupt line is expected.\n");
		वापस -EINVAL;
	पूर्ण

	/* Initialize dmc520 edac */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(reg_base))
		वापस PTR_ERR(reg_base);

	अगर (!dmc520_is_ecc_enabled(reg_base))
		वापस -ENXIO;

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = dmc520_get_rank_count(reg_base);
	layers[0].is_virt_csrow = true;

	mci = edac_mc_alloc(dmc520_mc_idx++, ARRAY_SIZE(layers), layers, माप(*pvt));
	अगर (!mci) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MOD_NAME,
			    "Failed to allocate memory for mc instance\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	pvt = mci->pvt_info;

	pvt->reg_base = reg_base;
	spin_lock_init(&pvt->error_lock);
	स_नकल(pvt->irqs, irqs, माप(irqs));
	स_नकल(pvt->masks, masks, माप(masks));

	platक्रमm_set_drvdata(pdev, mci);

	mci->pdev = dev;
	mci->mtype_cap		= MEM_FLAG_DDR3 | MEM_FLAG_DDR4;
	mci->edac_ctl_cap	= EDAC_FLAG_NONE | EDAC_FLAG_SECDED;
	mci->edac_cap		= EDAC_FLAG_SECDED;
	mci->scrub_cap		= SCRUB_FLAG_HW_SRC;
	mci->scrub_mode		= dmc520_get_scrub_type(pvt);
	mci->ctl_name		= EDAC_CTL_NAME;
	mci->dev_name		= dev_name(mci->pdev);
	mci->mod_name		= EDAC_MOD_NAME;

	edac_op_state = EDAC_OPSTATE_INT;

	pvt->mem_width_in_bytes = dmc520_get_memory_width(pvt);

	dmc520_init_csrow(mci);

	/* Clear पूर्णांकerrupts, not affecting other unrelated पूर्णांकerrupts */
	reg_val = dmc520_पढ़ो_reg(pvt, REG_OFFSET_INTERRUPT_CONTROL);
	dmc520_ग_लिखो_reg(pvt, reg_val & (~irq_mask_all),
			 REG_OFFSET_INTERRUPT_CONTROL);
	dmc520_ग_लिखो_reg(pvt, irq_mask_all, REG_OFFSET_INTERRUPT_CLR);

	क्रम (idx = 0; idx < NUMBER_OF_IRQS; idx++) अणु
		irq = irqs[idx];
		अगर (irq >= 0) अणु
			ret = devm_request_irq(&pdev->dev, irq,
					       dmc520_isr, IRQF_SHARED,
					       dev_name(&pdev->dev), mci);
			अगर (ret < 0) अणु
				edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
					    "Failed to request irq %d\n", irq);
				जाओ err;
			पूर्ण
			रेजिस्टरed[idx] = true;
		पूर्ण
	पूर्ण

	/* Reset DRAM CE/UE counters */
	अगर (irq_mask_all & DRAM_ECC_INT_CE_BIT)
		dmc520_get_dram_ecc_error_count(pvt, true);

	अगर (irq_mask_all & DRAM_ECC_INT_UE_BIT)
		dmc520_get_dram_ecc_error_count(pvt, false);

	ret = edac_mc_add_mc(mci);
	अगर (ret) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MOD_NAME,
			    "Failed to register with EDAC core\n");
		जाओ err;
	पूर्ण

	/* Enable पूर्णांकerrupts, not affecting other unrelated पूर्णांकerrupts */
	dmc520_ग_लिखो_reg(pvt, reg_val | irq_mask_all,
			 REG_OFFSET_INTERRUPT_CONTROL);

	वापस 0;

err:
	क्रम (idx = 0; idx < NUMBER_OF_IRQS; idx++) अणु
		अगर (रेजिस्टरed[idx])
			devm_मुक्त_irq(&pdev->dev, pvt->irqs[idx], mci);
	पूर्ण
	अगर (mci)
		edac_mc_मुक्त(mci);

	वापस ret;
पूर्ण

अटल पूर्णांक dmc520_edac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	u32 reg_val, idx, irq_mask_all = 0;
	काष्ठा mem_ctl_info *mci;
	काष्ठा dmc520_edac *pvt;

	mci = platक्रमm_get_drvdata(pdev);
	pvt = mci->pvt_info;

	/* Disable पूर्णांकerrupts */
	reg_val = dmc520_पढ़ो_reg(pvt, REG_OFFSET_INTERRUPT_CONTROL);
	dmc520_ग_लिखो_reg(pvt, reg_val & (~irq_mask_all),
			 REG_OFFSET_INTERRUPT_CONTROL);

	/* मुक्त irq's */
	क्रम (idx = 0; idx < NUMBER_OF_IRQS; idx++) अणु
		अगर (pvt->irqs[idx] >= 0) अणु
			irq_mask_all |= pvt->masks[idx];
			devm_मुक्त_irq(&pdev->dev, pvt->irqs[idx], mci);
		पूर्ण
	पूर्ण

	edac_mc_del_mc(&pdev->dev);
	edac_mc_मुक्त(mci);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dmc520_edac_driver_id[] = अणु
	अणु .compatible = "arm,dmc-520", पूर्ण,
	अणु /* end of table */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, dmc520_edac_driver_id);

अटल काष्ठा platक्रमm_driver dmc520_edac_driver = अणु
	.driver = अणु
		.name = "dmc520",
		.of_match_table = dmc520_edac_driver_id,
	पूर्ण,

	.probe = dmc520_edac_probe,
	.हटाओ = dmc520_edac_हटाओ
पूर्ण;

module_platक्रमm_driver(dmc520_edac_driver);

MODULE_AUTHOR("Rui Zhao <ruizhao@microsoft.com>");
MODULE_AUTHOR("Lei Wang <lewan@microsoft.com>");
MODULE_AUTHOR("Shiping Ji <shji@microsoft.com>");
MODULE_DESCRIPTION("DMC-520 ECC driver");
MODULE_LICENSE("GPL v2");
