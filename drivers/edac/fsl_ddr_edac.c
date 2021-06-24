<शैली गुरु>
/*
 * Freescale Memory Controller kernel module
 *
 * Support Power-based SoCs including MPC85xx, MPC86xx, MPC83xx and
 * ARM-based Layerscape SoCs including LS2xxx and LS1021A. Originally
 * split out from mpc85xx_edac EDAC driver.
 *
 * Parts Copyrighted (c) 2013 by Freescale Semiconductor, Inc.
 *
 * Author: Dave Jiang <djiang@mvista.com>
 *
 * 2006-2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/पन.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/edac.h>
#समावेश <linux/smp.h>
#समावेश <linux/gfp.h>

#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश "edac_module.h"
#समावेश "fsl_ddr_edac.h"

#घोषणा EDAC_MOD_STR	"fsl_ddr_edac"

अटल पूर्णांक edac_mc_idx;

अटल u32 orig_ddr_err_disable;
अटल u32 orig_ddr_err_sbe;
अटल bool little_endian;

अटल अंतरभूत u32 ddr_in32(व्योम __iomem *addr)
अणु
	वापस little_endian ? ioपढ़ो32(addr) : ioपढ़ो32be(addr);
पूर्ण

अटल अंतरभूत व्योम ddr_out32(व्योम __iomem *addr, u32 value)
अणु
	अगर (little_endian)
		ioग_लिखो32(value, addr);
	अन्यथा
		ioग_लिखो32be(value, addr);
पूर्ण

#अगर_घोषित CONFIG_EDAC_DEBUG
/************************ MC SYSFS parts ***********************************/

#घोषणा to_mci(k) container_of(k, काष्ठा mem_ctl_info, dev)

अटल sमाप_प्रकार fsl_mc_inject_data_hi_show(काष्ठा device *dev,
					  काष्ठा device_attribute *mattr,
					  अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा fsl_mc_pdata *pdata = mci->pvt_info;
	वापस प्र_लिखो(data, "0x%08x",
		       ddr_in32(pdata->mc_vbase + FSL_MC_DATA_ERR_INJECT_HI));
पूर्ण

अटल sमाप_प्रकार fsl_mc_inject_data_lo_show(काष्ठा device *dev,
					  काष्ठा device_attribute *mattr,
					      अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा fsl_mc_pdata *pdata = mci->pvt_info;
	वापस प्र_लिखो(data, "0x%08x",
		       ddr_in32(pdata->mc_vbase + FSL_MC_DATA_ERR_INJECT_LO));
पूर्ण

अटल sमाप_प्रकार fsl_mc_inject_ctrl_show(काष्ठा device *dev,
				       काष्ठा device_attribute *mattr,
					   अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा fsl_mc_pdata *pdata = mci->pvt_info;
	वापस प्र_लिखो(data, "0x%08x",
		       ddr_in32(pdata->mc_vbase + FSL_MC_ECC_ERR_INJECT));
पूर्ण

अटल sमाप_प्रकार fsl_mc_inject_data_hi_store(काष्ठा device *dev,
					   काष्ठा device_attribute *mattr,
					       स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा fsl_mc_pdata *pdata = mci->pvt_info;
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	अगर (है_अंक(*data)) अणु
		rc = kम_से_अदीर्घ(data, 0, &val);
		अगर (rc)
			वापस rc;

		ddr_out32(pdata->mc_vbase + FSL_MC_DATA_ERR_INJECT_HI, val);
		वापस count;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार fsl_mc_inject_data_lo_store(काष्ठा device *dev,
					   काष्ठा device_attribute *mattr,
					       स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा fsl_mc_pdata *pdata = mci->pvt_info;
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	अगर (है_अंक(*data)) अणु
		rc = kम_से_अदीर्घ(data, 0, &val);
		अगर (rc)
			वापस rc;

		ddr_out32(pdata->mc_vbase + FSL_MC_DATA_ERR_INJECT_LO, val);
		वापस count;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार fsl_mc_inject_ctrl_store(काष्ठा device *dev,
					काष्ठा device_attribute *mattr,
					       स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा fsl_mc_pdata *pdata = mci->pvt_info;
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	अगर (है_अंक(*data)) अणु
		rc = kम_से_अदीर्घ(data, 0, &val);
		अगर (rc)
			वापस rc;

		ddr_out32(pdata->mc_vbase + FSL_MC_ECC_ERR_INJECT, val);
		वापस count;
	पूर्ण
	वापस 0;
पूर्ण

अटल DEVICE_ATTR(inject_data_hi, S_IRUGO | S_IWUSR,
		   fsl_mc_inject_data_hi_show, fsl_mc_inject_data_hi_store);
अटल DEVICE_ATTR(inject_data_lo, S_IRUGO | S_IWUSR,
		   fsl_mc_inject_data_lo_show, fsl_mc_inject_data_lo_store);
अटल DEVICE_ATTR(inject_ctrl, S_IRUGO | S_IWUSR,
		   fsl_mc_inject_ctrl_show, fsl_mc_inject_ctrl_store);
#पूर्ण_अगर /* CONFIG_EDAC_DEBUG */

अटल काष्ठा attribute *fsl_ddr_dev_attrs[] = अणु
#अगर_घोषित CONFIG_EDAC_DEBUG
	&dev_attr_inject_data_hi.attr,
	&dev_attr_inject_data_lo.attr,
	&dev_attr_inject_ctrl.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(fsl_ddr_dev);

/**************************** MC Err device ***************************/

/*
 * Taken from table 8-55 in the MPC8641 User's Manual and/or 9-61 in the
 * MPC8572 User's Manual.  Each line represents a syndrome bit column as a
 * 64-bit value, but split पूर्णांकo an upper and lower 32-bit chunk.  The labels
 * below correspond to Freescale's manuals.
 */
अटल अचिन्हित पूर्णांक ecc_table[16] = अणु
	/* MSB           LSB */
	/* [0:31]    [32:63] */
	0xf00fe11e, 0xc33c0ff7,	/* Syndrome bit 7 */
	0x00ff00ff, 0x00fff0ff,
	0x0f0f0f0f, 0x0f0fff00,
	0x11113333, 0x7777000f,
	0x22224444, 0x8888222f,
	0x44448888, 0xffff4441,
	0x8888ffff, 0x11118882,
	0xffff1111, 0x22221114,	/* Syndrome bit 0 */
पूर्ण;

/*
 * Calculate the correct ECC value क्रम a 64-bit value specअगरied by high:low
 */
अटल u8 calculate_ecc(u32 high, u32 low)
अणु
	u32 mask_low;
	u32 mask_high;
	पूर्णांक bit_cnt;
	u8 ecc = 0;
	पूर्णांक i;
	पूर्णांक j;

	क्रम (i = 0; i < 8; i++) अणु
		mask_high = ecc_table[i * 2];
		mask_low = ecc_table[i * 2 + 1];
		bit_cnt = 0;

		क्रम (j = 0; j < 32; j++) अणु
			अगर ((mask_high >> j) & 1)
				bit_cnt ^= (high >> j) & 1;
			अगर ((mask_low >> j) & 1)
				bit_cnt ^= (low >> j) & 1;
		पूर्ण

		ecc |= bit_cnt << i;
	पूर्ण

	वापस ecc;
पूर्ण

/*
 * Create the syndrome code which is generated अगर the data line specअगरied by
 * 'bit' failed.  Eg generate an 8-bit codes seen in Table 8-55 in the MPC8641
 * User's Manual and 9-61 in the MPC8572 User's Manual.
 */
अटल u8 syndrome_from_bit(अचिन्हित पूर्णांक bit) अणु
	पूर्णांक i;
	u8 syndrome = 0;

	/*
	 * Cycle through the upper or lower 32-bit portion of each value in
	 * ecc_table depending on अगर 'bit' is in the upper or lower half of
	 * 64-bit data.
	 */
	क्रम (i = bit < 32; i < 16; i += 2)
		syndrome |= ((ecc_table[i] >> (bit % 32)) & 1) << (i / 2);

	वापस syndrome;
पूर्ण

/*
 * Decode data and ecc syndrome to determine what went wrong
 * Note: This can only decode single-bit errors
 */
अटल व्योम sbe_ecc_decode(u32 cap_high, u32 cap_low, u32 cap_ecc,
		       पूर्णांक *bad_data_bit, पूर्णांक *bad_ecc_bit)
अणु
	पूर्णांक i;
	u8 syndrome;

	*bad_data_bit = -1;
	*bad_ecc_bit = -1;

	/*
	 * Calculate the ECC of the captured data and XOR it with the captured
	 * ECC to find an ECC syndrome value we can search क्रम
	 */
	syndrome = calculate_ecc(cap_high, cap_low) ^ cap_ecc;

	/* Check अगर a data line is stuck... */
	क्रम (i = 0; i < 64; i++) अणु
		अगर (syndrome == syndrome_from_bit(i)) अणु
			*bad_data_bit = i;
			वापस;
		पूर्ण
	पूर्ण

	/* If data is correct, check ECC bits क्रम errors... */
	क्रम (i = 0; i < 8; i++) अणु
		अगर ((syndrome >> i) & 0x1) अणु
			*bad_ecc_bit = i;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा make64(high, low) (((u64)(high) << 32) | (low))

अटल व्योम fsl_mc_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा fsl_mc_pdata *pdata = mci->pvt_info;
	काष्ठा csrow_info *csrow;
	u32 bus_width;
	u32 err_detect;
	u32 syndrome;
	u64 err_addr;
	u32 pfn;
	पूर्णांक row_index;
	u32 cap_high;
	u32 cap_low;
	पूर्णांक bad_data_bit;
	पूर्णांक bad_ecc_bit;

	err_detect = ddr_in32(pdata->mc_vbase + FSL_MC_ERR_DETECT);
	अगर (!err_detect)
		वापस;

	fsl_mc_prपूर्णांकk(mci, KERN_ERR, "Err Detect Register: %#8.8x\n",
		      err_detect);

	/* no more processing अगर not ECC bit errors */
	अगर (!(err_detect & (DDR_EDE_SBE | DDR_EDE_MBE))) अणु
		ddr_out32(pdata->mc_vbase + FSL_MC_ERR_DETECT, err_detect);
		वापस;
	पूर्ण

	syndrome = ddr_in32(pdata->mc_vbase + FSL_MC_CAPTURE_ECC);

	/* Mask off appropriate bits of syndrome based on bus width */
	bus_width = (ddr_in32(pdata->mc_vbase + FSL_MC_DDR_SDRAM_CFG) &
		     DSC_DBW_MASK) ? 32 : 64;
	अगर (bus_width == 64)
		syndrome &= 0xff;
	अन्यथा
		syndrome &= 0xffff;

	err_addr = make64(
		ddr_in32(pdata->mc_vbase + FSL_MC_CAPTURE_EXT_ADDRESS),
		ddr_in32(pdata->mc_vbase + FSL_MC_CAPTURE_ADDRESS));
	pfn = err_addr >> PAGE_SHIFT;

	क्रम (row_index = 0; row_index < mci->nr_csrows; row_index++) अणु
		csrow = mci->csrows[row_index];
		अगर ((pfn >= csrow->first_page) && (pfn <= csrow->last_page))
			अवरोध;
	पूर्ण

	cap_high = ddr_in32(pdata->mc_vbase + FSL_MC_CAPTURE_DATA_HI);
	cap_low = ddr_in32(pdata->mc_vbase + FSL_MC_CAPTURE_DATA_LO);

	/*
	 * Analyze single-bit errors on 64-bit wide buses
	 * TODO: Add support क्रम 32-bit wide buses
	 */
	अगर ((err_detect & DDR_EDE_SBE) && (bus_width == 64)) अणु
		sbe_ecc_decode(cap_high, cap_low, syndrome,
				&bad_data_bit, &bad_ecc_bit);

		अगर (bad_data_bit != -1)
			fsl_mc_prपूर्णांकk(mci, KERN_ERR,
				"Faulty Data bit: %d\n", bad_data_bit);
		अगर (bad_ecc_bit != -1)
			fsl_mc_prपूर्णांकk(mci, KERN_ERR,
				"Faulty ECC bit: %d\n", bad_ecc_bit);

		fsl_mc_prपूर्णांकk(mci, KERN_ERR,
			"Expected Data / ECC:\t%#8.8x_%08x / %#2.2x\n",
			cap_high ^ (1 << (bad_data_bit - 32)),
			cap_low ^ (1 << bad_data_bit),
			syndrome ^ (1 << bad_ecc_bit));
	पूर्ण

	fsl_mc_prपूर्णांकk(mci, KERN_ERR,
			"Captured Data / ECC:\t%#8.8x_%08x / %#2.2x\n",
			cap_high, cap_low, syndrome);
	fsl_mc_prपूर्णांकk(mci, KERN_ERR, "Err addr: %#8.8llx\n", err_addr);
	fsl_mc_prपूर्णांकk(mci, KERN_ERR, "PFN: %#8.8x\n", pfn);

	/* we are out of range */
	अगर (row_index == mci->nr_csrows)
		fsl_mc_prपूर्णांकk(mci, KERN_ERR, "PFN out of range!\n");

	अगर (err_detect & DDR_EDE_SBE)
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
				     pfn, err_addr & ~PAGE_MASK, syndrome,
				     row_index, 0, -1,
				     mci->ctl_name, "");

	अगर (err_detect & DDR_EDE_MBE)
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     pfn, err_addr & ~PAGE_MASK, syndrome,
				     row_index, 0, -1,
				     mci->ctl_name, "");

	ddr_out32(pdata->mc_vbase + FSL_MC_ERR_DETECT, err_detect);
पूर्ण

अटल irqवापस_t fsl_mc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mem_ctl_info *mci = dev_id;
	काष्ठा fsl_mc_pdata *pdata = mci->pvt_info;
	u32 err_detect;

	err_detect = ddr_in32(pdata->mc_vbase + FSL_MC_ERR_DETECT);
	अगर (!err_detect)
		वापस IRQ_NONE;

	fsl_mc_check(mci);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम fsl_ddr_init_csrows(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा fsl_mc_pdata *pdata = mci->pvt_info;
	काष्ठा csrow_info *csrow;
	काष्ठा dimm_info *dimm;
	u32 sdram_ctl;
	u32 sdtype;
	क्रमागत mem_type mtype;
	u32 cs_bnds;
	पूर्णांक index;

	sdram_ctl = ddr_in32(pdata->mc_vbase + FSL_MC_DDR_SDRAM_CFG);

	sdtype = sdram_ctl & DSC_SDTYPE_MASK;
	अगर (sdram_ctl & DSC_RD_EN) अणु
		चयन (sdtype) अणु
		हाल 0x02000000:
			mtype = MEM_RDDR;
			अवरोध;
		हाल 0x03000000:
			mtype = MEM_RDDR2;
			अवरोध;
		हाल 0x07000000:
			mtype = MEM_RDDR3;
			अवरोध;
		हाल 0x05000000:
			mtype = MEM_RDDR4;
			अवरोध;
		शेष:
			mtype = MEM_UNKNOWN;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (sdtype) अणु
		हाल 0x02000000:
			mtype = MEM_DDR;
			अवरोध;
		हाल 0x03000000:
			mtype = MEM_DDR2;
			अवरोध;
		हाल 0x07000000:
			mtype = MEM_DDR3;
			अवरोध;
		हाल 0x05000000:
			mtype = MEM_DDR4;
			अवरोध;
		शेष:
			mtype = MEM_UNKNOWN;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (index = 0; index < mci->nr_csrows; index++) अणु
		u32 start;
		u32 end;

		csrow = mci->csrows[index];
		dimm = csrow->channels[0]->dimm;

		cs_bnds = ddr_in32(pdata->mc_vbase + FSL_MC_CS_BNDS_0 +
				   (index * FSL_MC_CS_BNDS_OFS));

		start = (cs_bnds & 0xffff0000) >> 16;
		end   = (cs_bnds & 0x0000ffff);

		अगर (start == end)
			जारी;	/* not populated */

		start <<= (24 - PAGE_SHIFT);
		end   <<= (24 - PAGE_SHIFT);
		end    |= (1 << (24 - PAGE_SHIFT)) - 1;

		csrow->first_page = start;
		csrow->last_page = end;

		dimm->nr_pages = end + 1 - start;
		dimm->grain = 8;
		dimm->mtype = mtype;
		dimm->dtype = DEV_UNKNOWN;
		अगर (sdram_ctl & DSC_X32_EN)
			dimm->dtype = DEV_X32;
		dimm->edac_mode = EDAC_SECDED;
	पूर्ण
पूर्ण

पूर्णांक fsl_mc_err_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा fsl_mc_pdata *pdata;
	काष्ठा resource r;
	u32 sdram_ctl;
	पूर्णांक res;

	अगर (!devres_खोलो_group(&op->dev, fsl_mc_err_probe, GFP_KERNEL))
		वापस -ENOMEM;

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = 4;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = 1;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(edac_mc_idx, ARRAY_SIZE(layers), layers,
			    माप(*pdata));
	अगर (!mci) अणु
		devres_release_group(&op->dev, fsl_mc_err_probe);
		वापस -ENOMEM;
	पूर्ण

	pdata = mci->pvt_info;
	pdata->name = "fsl_mc_err";
	mci->pdev = &op->dev;
	pdata->edac_idx = edac_mc_idx++;
	dev_set_drvdata(mci->pdev, mci);
	mci->ctl_name = pdata->name;
	mci->dev_name = pdata->name;

	/*
	 * Get the endianness of DDR controller रेजिस्टरs.
	 * Default is big endian.
	 */
	little_endian = of_property_पढ़ो_bool(op->dev.of_node, "little-endian");

	res = of_address_to_resource(op->dev.of_node, 0, &r);
	अगर (res) अणु
		pr_err("%s: Unable to get resource for MC err regs\n",
		       __func__);
		जाओ err;
	पूर्ण

	अगर (!devm_request_mem_region(&op->dev, r.start, resource_size(&r),
				     pdata->name)) अणु
		pr_err("%s: Error while requesting mem region\n",
		       __func__);
		res = -EBUSY;
		जाओ err;
	पूर्ण

	pdata->mc_vbase = devm_ioremap(&op->dev, r.start, resource_size(&r));
	अगर (!pdata->mc_vbase) अणु
		pr_err("%s: Unable to setup MC err regs\n", __func__);
		res = -ENOMEM;
		जाओ err;
	पूर्ण

	sdram_ctl = ddr_in32(pdata->mc_vbase + FSL_MC_DDR_SDRAM_CFG);
	अगर (!(sdram_ctl & DSC_ECC_EN)) अणु
		/* no ECC */
		pr_warn("%s: No ECC DIMMs discovered\n", __func__);
		res = -ENODEV;
		जाओ err;
	पूर्ण

	edac_dbg(3, "init mci\n");
	mci->mtype_cap = MEM_FLAG_DDR | MEM_FLAG_RDDR |
			 MEM_FLAG_DDR2 | MEM_FLAG_RDDR2 |
			 MEM_FLAG_DDR3 | MEM_FLAG_RDDR3 |
			 MEM_FLAG_DDR4 | MEM_FLAG_RDDR4;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->mod_name = EDAC_MOD_STR;

	अगर (edac_op_state == EDAC_OPSTATE_POLL)
		mci->edac_check = fsl_mc_check;

	mci->ctl_page_to_phys = शून्य;

	mci->scrub_mode = SCRUB_SW_SRC;

	fsl_ddr_init_csrows(mci);

	/* store the original error disable bits */
	orig_ddr_err_disable = ddr_in32(pdata->mc_vbase + FSL_MC_ERR_DISABLE);
	ddr_out32(pdata->mc_vbase + FSL_MC_ERR_DISABLE, 0);

	/* clear all error bits */
	ddr_out32(pdata->mc_vbase + FSL_MC_ERR_DETECT, ~0);

	res = edac_mc_add_mc_with_groups(mci, fsl_ddr_dev_groups);
	अगर (res) अणु
		edac_dbg(3, "failed edac_mc_add_mc()\n");
		जाओ err;
	पूर्ण

	अगर (edac_op_state == EDAC_OPSTATE_INT) अणु
		ddr_out32(pdata->mc_vbase + FSL_MC_ERR_INT_EN,
			  DDR_EIE_MBEE | DDR_EIE_SBEE);

		/* store the original error management threshold */
		orig_ddr_err_sbe = ddr_in32(pdata->mc_vbase +
					    FSL_MC_ERR_SBE) & 0xff0000;

		/* set threshold to 1 error per पूर्णांकerrupt */
		ddr_out32(pdata->mc_vbase + FSL_MC_ERR_SBE, 0x10000);

		/* रेजिस्टर पूर्णांकerrupts */
		pdata->irq = platक्रमm_get_irq(op, 0);
		res = devm_request_irq(&op->dev, pdata->irq,
				       fsl_mc_isr,
				       IRQF_SHARED,
				       "[EDAC] MC err", mci);
		अगर (res < 0) अणु
			pr_err("%s: Unable to request irq %d for FSL DDR DRAM ERR\n",
			       __func__, pdata->irq);
			res = -ENODEV;
			जाओ err2;
		पूर्ण

		pr_info(EDAC_MOD_STR " acquired irq %d for MC\n",
		       pdata->irq);
	पूर्ण

	devres_हटाओ_group(&op->dev, fsl_mc_err_probe);
	edac_dbg(3, "success\n");
	pr_info(EDAC_MOD_STR " MC err registered\n");

	वापस 0;

err2:
	edac_mc_del_mc(&op->dev);
err:
	devres_release_group(&op->dev, fsl_mc_err_probe);
	edac_mc_मुक्त(mci);
	वापस res;
पूर्ण

पूर्णांक fsl_mc_err_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा mem_ctl_info *mci = dev_get_drvdata(&op->dev);
	काष्ठा fsl_mc_pdata *pdata = mci->pvt_info;

	edac_dbg(0, "\n");

	अगर (edac_op_state == EDAC_OPSTATE_INT) अणु
		ddr_out32(pdata->mc_vbase + FSL_MC_ERR_INT_EN, 0);
	पूर्ण

	ddr_out32(pdata->mc_vbase + FSL_MC_ERR_DISABLE,
		  orig_ddr_err_disable);
	ddr_out32(pdata->mc_vbase + FSL_MC_ERR_SBE, orig_ddr_err_sbe);

	edac_mc_del_mc(&op->dev);
	edac_mc_मुक्त(mci);
	वापस 0;
पूर्ण
