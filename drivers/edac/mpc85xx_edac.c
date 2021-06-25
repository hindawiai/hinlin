<शैली गुरु>
/*
 * Freescale MPC85xx Memory Controller kernel module
 *
 * Parts Copyrighted (c) 2013 by Freescale Semiconductor, Inc.
 *
 * Author: Dave Jiang <djiang@mvista.com>
 *
 * 2006-2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
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
#समावेश <linux/fsl/edac.h>

#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>
#समावेश "edac_module.h"
#समावेश "mpc85xx_edac.h"
#समावेश "fsl_ddr_edac.h"

अटल पूर्णांक edac_dev_idx;
#अगर_घोषित CONFIG_PCI
अटल पूर्णांक edac_pci_idx;
#पूर्ण_अगर

/*
 * PCI Err defines
 */
#अगर_घोषित CONFIG_PCI
अटल u32 orig_pci_err_cap_dr;
अटल u32 orig_pci_err_en;
#पूर्ण_अगर

अटल u32 orig_l2_err_disable;

/**************************** PCI Err device ***************************/
#अगर_घोषित CONFIG_PCI

अटल व्योम mpc85xx_pci_check(काष्ठा edac_pci_ctl_info *pci)
अणु
	काष्ठा mpc85xx_pci_pdata *pdata = pci->pvt_info;
	u32 err_detect;

	err_detect = in_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_DR);

	/* master पातs can happen during PCI config cycles */
	अगर (!(err_detect & ~(PCI_EDE_MULTI_ERR | PCI_EDE_MST_ABRT))) अणु
		out_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_DR, err_detect);
		वापस;
	पूर्ण

	pr_err("PCI error(s) detected\n");
	pr_err("PCI/X ERR_DR register: %#08x\n", err_detect);

	pr_err("PCI/X ERR_ATTRIB register: %#08x\n",
	       in_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_ATTRIB));
	pr_err("PCI/X ERR_ADDR register: %#08x\n",
	       in_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_ADDR));
	pr_err("PCI/X ERR_EXT_ADDR register: %#08x\n",
	       in_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_EXT_ADDR));
	pr_err("PCI/X ERR_DL register: %#08x\n",
	       in_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_DL));
	pr_err("PCI/X ERR_DH register: %#08x\n",
	       in_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_DH));

	/* clear error bits */
	out_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_DR, err_detect);

	अगर (err_detect & PCI_EDE_PERR_MASK)
		edac_pci_handle_pe(pci, pci->ctl_name);

	अगर ((err_detect & ~PCI_EDE_MULTI_ERR) & ~PCI_EDE_PERR_MASK)
		edac_pci_handle_npe(pci, pci->ctl_name);
पूर्ण

अटल व्योम mpc85xx_pcie_check(काष्ठा edac_pci_ctl_info *pci)
अणु
	काष्ठा mpc85xx_pci_pdata *pdata = pci->pvt_info;
	u32 err_detect, err_cap_stat;

	err_detect = in_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_DR);
	err_cap_stat = in_be32(pdata->pci_vbase + MPC85XX_PCI_GAS_TIMR);

	pr_err("PCIe error(s) detected\n");
	pr_err("PCIe ERR_DR register: 0x%08x\n", err_detect);
	pr_err("PCIe ERR_CAP_STAT register: 0x%08x\n", err_cap_stat);
	pr_err("PCIe ERR_CAP_R0 register: 0x%08x\n",
			in_be32(pdata->pci_vbase + MPC85XX_PCIE_ERR_CAP_R0));
	pr_err("PCIe ERR_CAP_R1 register: 0x%08x\n",
			in_be32(pdata->pci_vbase + MPC85XX_PCIE_ERR_CAP_R1));
	pr_err("PCIe ERR_CAP_R2 register: 0x%08x\n",
			in_be32(pdata->pci_vbase + MPC85XX_PCIE_ERR_CAP_R2));
	pr_err("PCIe ERR_CAP_R3 register: 0x%08x\n",
			in_be32(pdata->pci_vbase + MPC85XX_PCIE_ERR_CAP_R3));

	/* clear error bits */
	out_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_DR, err_detect);

	/* reset error capture */
	out_be32(pdata->pci_vbase + MPC85XX_PCI_GAS_TIMR, err_cap_stat | 0x1);
पूर्ण

अटल पूर्णांक mpc85xx_pcie_find_capability(काष्ठा device_node *np)
अणु
	काष्ठा pci_controller *hose;

	अगर (!np)
		वापस -EINVAL;

	hose = pci_find_hose_क्रम_OF_device(np);

	वापस early_find_capability(hose, 0, 0, PCI_CAP_ID_EXP);
पूर्ण

अटल irqवापस_t mpc85xx_pci_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा edac_pci_ctl_info *pci = dev_id;
	काष्ठा mpc85xx_pci_pdata *pdata = pci->pvt_info;
	u32 err_detect;

	err_detect = in_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_DR);

	अगर (!err_detect)
		वापस IRQ_NONE;

	अगर (pdata->is_pcie)
		mpc85xx_pcie_check(pci);
	अन्यथा
		mpc85xx_pci_check(pci);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mpc85xx_pci_err_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा edac_pci_ctl_info *pci;
	काष्ठा mpc85xx_pci_pdata *pdata;
	काष्ठा mpc85xx_edac_pci_plat_data *plat_data;
	काष्ठा device_node *of_node;
	काष्ठा resource r;
	पूर्णांक res = 0;

	अगर (!devres_खोलो_group(&op->dev, mpc85xx_pci_err_probe, GFP_KERNEL))
		वापस -ENOMEM;

	pci = edac_pci_alloc_ctl_info(माप(*pdata), "mpc85xx_pci_err");
	अगर (!pci)
		वापस -ENOMEM;

	/* make sure error reporting method is sane */
	चयन (edac_op_state) अणु
	हाल EDAC_OPSTATE_POLL:
	हाल EDAC_OPSTATE_INT:
		अवरोध;
	शेष:
		edac_op_state = EDAC_OPSTATE_INT;
		अवरोध;
	पूर्ण

	pdata = pci->pvt_info;
	pdata->name = "mpc85xx_pci_err";

	plat_data = op->dev.platक्रमm_data;
	अगर (!plat_data) अणु
		dev_err(&op->dev, "no platform data");
		res = -ENXIO;
		जाओ err;
	पूर्ण
	of_node = plat_data->of_node;

	अगर (mpc85xx_pcie_find_capability(of_node) > 0)
		pdata->is_pcie = true;

	dev_set_drvdata(&op->dev, pci);
	pci->dev = &op->dev;
	pci->mod_name = EDAC_MOD_STR;
	pci->ctl_name = pdata->name;
	pci->dev_name = dev_name(&op->dev);

	अगर (edac_op_state == EDAC_OPSTATE_POLL) अणु
		अगर (pdata->is_pcie)
			pci->edac_check = mpc85xx_pcie_check;
		अन्यथा
			pci->edac_check = mpc85xx_pci_check;
	पूर्ण

	pdata->edac_idx = edac_pci_idx++;

	res = of_address_to_resource(of_node, 0, &r);
	अगर (res) अणु
		pr_err("%s: Unable to get resource for PCI err regs\n", __func__);
		जाओ err;
	पूर्ण

	/* we only need the error रेजिस्टरs */
	r.start += 0xe00;

	अगर (!devm_request_mem_region(&op->dev, r.start, resource_size(&r),
					pdata->name)) अणु
		pr_err("%s: Error while requesting mem region\n", __func__);
		res = -EBUSY;
		जाओ err;
	पूर्ण

	pdata->pci_vbase = devm_ioremap(&op->dev, r.start, resource_size(&r));
	अगर (!pdata->pci_vbase) अणु
		pr_err("%s: Unable to setup PCI err regs\n", __func__);
		res = -ENOMEM;
		जाओ err;
	पूर्ण

	अगर (pdata->is_pcie) अणु
		orig_pci_err_cap_dr =
		    in_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_ADDR);
		out_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_ADDR, ~0);
		orig_pci_err_en =
		    in_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_EN);
		out_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_EN, 0);
	पूर्ण अन्यथा अणु
		orig_pci_err_cap_dr =
		    in_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_CAP_DR);

		/* PCI master पात is expected during config cycles */
		out_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_CAP_DR, 0x40);

		orig_pci_err_en =
		    in_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_EN);

		/* disable master पात reporting */
		out_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_EN, ~0x40);
	पूर्ण

	/* clear error bits */
	out_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_DR, ~0);

	/* reset error capture */
	out_be32(pdata->pci_vbase + MPC85XX_PCI_GAS_TIMR, 0x1);

	अगर (edac_pci_add_device(pci, pdata->edac_idx) > 0) अणु
		edac_dbg(3, "failed edac_pci_add_device()\n");
		जाओ err;
	पूर्ण

	अगर (edac_op_state == EDAC_OPSTATE_INT) अणु
		pdata->irq = irq_of_parse_and_map(of_node, 0);
		res = devm_request_irq(&op->dev, pdata->irq,
				       mpc85xx_pci_isr,
				       IRQF_SHARED,
				       "[EDAC] PCI err", pci);
		अगर (res < 0) अणु
			pr_err("%s: Unable to request irq %d for MPC85xx PCI err\n",
				__func__, pdata->irq);
			irq_dispose_mapping(pdata->irq);
			res = -ENODEV;
			जाओ err2;
		पूर्ण

		pr_info(EDAC_MOD_STR " acquired irq %d for PCI Err\n",
		       pdata->irq);
	पूर्ण

	अगर (pdata->is_pcie) अणु
		/*
		 * Enable all PCIe error पूर्णांकerrupt & error detect except invalid
		 * PEX_CONFIG_ADDR/PEX_CONFIG_DATA access पूर्णांकerrupt generation
		 * enable bit and invalid PEX_CONFIG_ADDR/PEX_CONFIG_DATA access
		 * detection enable bit. Because PCIe bus code to initialize and
		 * configure these PCIe devices on booting will use some invalid
		 * PEX_CONFIG_ADDR/PEX_CONFIG_DATA, edac driver prपूर्णांकs the much
		 * notice inक्रमmation. So disable this detect to fix ugly prपूर्णांक.
		 */
		out_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_EN, ~0
			 & ~PEX_ERR_ICCAIE_EN_BIT);
		out_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_ADDR, 0
			 | PEX_ERR_ICCAD_DISR_BIT);
	पूर्ण

	devres_हटाओ_group(&op->dev, mpc85xx_pci_err_probe);
	edac_dbg(3, "success\n");
	pr_info(EDAC_MOD_STR " PCI err registered\n");

	वापस 0;

err2:
	edac_pci_del_device(&op->dev);
err:
	edac_pci_मुक्त_ctl_info(pci);
	devres_release_group(&op->dev, mpc85xx_pci_err_probe);
	वापस res;
पूर्ण

अटल पूर्णांक mpc85xx_pci_err_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा edac_pci_ctl_info *pci = dev_get_drvdata(&op->dev);
	काष्ठा mpc85xx_pci_pdata *pdata = pci->pvt_info;

	edac_dbg(0, "\n");

	out_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_ADDR, orig_pci_err_cap_dr);
	out_be32(pdata->pci_vbase + MPC85XX_PCI_ERR_EN, orig_pci_err_en);

	edac_pci_del_device(&op->dev);
	edac_pci_मुक्त_ctl_info(pci);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mpc85xx_pci_err_match[] = अणु
	अणु
		.name = "mpc85xx-pci-edac"
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mpc85xx_pci_err_driver = अणु
	.probe = mpc85xx_pci_err_probe,
	.हटाओ = mpc85xx_pci_err_हटाओ,
	.id_table = mpc85xx_pci_err_match,
	.driver = अणु
		.name = "mpc85xx_pci_err",
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर				/* CONFIG_PCI */

/**************************** L2 Err device ***************************/

/************************ L2 SYSFS parts ***********************************/

अटल sमाप_प्रकार mpc85xx_l2_inject_data_hi_show(काष्ठा edac_device_ctl_info
					      *edac_dev, अक्षर *data)
अणु
	काष्ठा mpc85xx_l2_pdata *pdata = edac_dev->pvt_info;
	वापस प्र_लिखो(data, "0x%08x",
		       in_be32(pdata->l2_vbase + MPC85XX_L2_ERRINJHI));
पूर्ण

अटल sमाप_प्रकार mpc85xx_l2_inject_data_lo_show(काष्ठा edac_device_ctl_info
					      *edac_dev, अक्षर *data)
अणु
	काष्ठा mpc85xx_l2_pdata *pdata = edac_dev->pvt_info;
	वापस प्र_लिखो(data, "0x%08x",
		       in_be32(pdata->l2_vbase + MPC85XX_L2_ERRINJLO));
पूर्ण

अटल sमाप_प्रकार mpc85xx_l2_inject_ctrl_show(काष्ठा edac_device_ctl_info
					   *edac_dev, अक्षर *data)
अणु
	काष्ठा mpc85xx_l2_pdata *pdata = edac_dev->pvt_info;
	वापस प्र_लिखो(data, "0x%08x",
		       in_be32(pdata->l2_vbase + MPC85XX_L2_ERRINJCTL));
पूर्ण

अटल sमाप_प्रकार mpc85xx_l2_inject_data_hi_store(काष्ठा edac_device_ctl_info
					       *edac_dev, स्थिर अक्षर *data,
					       माप_प्रकार count)
अणु
	काष्ठा mpc85xx_l2_pdata *pdata = edac_dev->pvt_info;
	अगर (है_अंक(*data)) अणु
		out_be32(pdata->l2_vbase + MPC85XX_L2_ERRINJHI,
			 simple_म_से_अदीर्घ(data, शून्य, 0));
		वापस count;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार mpc85xx_l2_inject_data_lo_store(काष्ठा edac_device_ctl_info
					       *edac_dev, स्थिर अक्षर *data,
					       माप_प्रकार count)
अणु
	काष्ठा mpc85xx_l2_pdata *pdata = edac_dev->pvt_info;
	अगर (है_अंक(*data)) अणु
		out_be32(pdata->l2_vbase + MPC85XX_L2_ERRINJLO,
			 simple_म_से_अदीर्घ(data, शून्य, 0));
		वापस count;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार mpc85xx_l2_inject_ctrl_store(काष्ठा edac_device_ctl_info
					    *edac_dev, स्थिर अक्षर *data,
					    माप_प्रकार count)
अणु
	काष्ठा mpc85xx_l2_pdata *pdata = edac_dev->pvt_info;
	अगर (है_अंक(*data)) अणु
		out_be32(pdata->l2_vbase + MPC85XX_L2_ERRINJCTL,
			 simple_म_से_अदीर्घ(data, शून्य, 0));
		वापस count;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा edac_dev_sysfs_attribute mpc85xx_l2_sysfs_attributes[] = अणु
	अणु
	 .attr = अणु
		  .name = "inject_data_hi",
		  .mode = (S_IRUGO | S_IWUSR)
		  पूर्ण,
	 .show = mpc85xx_l2_inject_data_hi_show,
	 .store = mpc85xx_l2_inject_data_hi_storeपूर्ण,
	अणु
	 .attr = अणु
		  .name = "inject_data_lo",
		  .mode = (S_IRUGO | S_IWUSR)
		  पूर्ण,
	 .show = mpc85xx_l2_inject_data_lo_show,
	 .store = mpc85xx_l2_inject_data_lo_storeपूर्ण,
	अणु
	 .attr = अणु
		  .name = "inject_ctrl",
		  .mode = (S_IRUGO | S_IWUSR)
		  पूर्ण,
	 .show = mpc85xx_l2_inject_ctrl_show,
	 .store = mpc85xx_l2_inject_ctrl_storeपूर्ण,

	/* End of list */
	अणु
	 .attr = अणु.name = शून्यपूर्ण
	 पूर्ण
पूर्ण;

अटल व्योम mpc85xx_set_l2_sysfs_attributes(काष्ठा edac_device_ctl_info
					    *edac_dev)
अणु
	edac_dev->sysfs_attributes = mpc85xx_l2_sysfs_attributes;
पूर्ण

/***************************** L2 ops ***********************************/

अटल व्योम mpc85xx_l2_check(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा mpc85xx_l2_pdata *pdata = edac_dev->pvt_info;
	u32 err_detect;

	err_detect = in_be32(pdata->l2_vbase + MPC85XX_L2_ERRDET);

	अगर (!(err_detect & L2_EDE_MASK))
		वापस;

	pr_err("ECC Error in CPU L2 cache\n");
	pr_err("L2 Error Detect Register: 0x%08x\n", err_detect);
	pr_err("L2 Error Capture Data High Register: 0x%08x\n",
	       in_be32(pdata->l2_vbase + MPC85XX_L2_CAPTDATAHI));
	pr_err("L2 Error Capture Data Lo Register: 0x%08x\n",
	       in_be32(pdata->l2_vbase + MPC85XX_L2_CAPTDATALO));
	pr_err("L2 Error Syndrome Register: 0x%08x\n",
	       in_be32(pdata->l2_vbase + MPC85XX_L2_CAPTECC));
	pr_err("L2 Error Attributes Capture Register: 0x%08x\n",
	       in_be32(pdata->l2_vbase + MPC85XX_L2_ERRATTR));
	pr_err("L2 Error Address Capture Register: 0x%08x\n",
	       in_be32(pdata->l2_vbase + MPC85XX_L2_ERRADDR));

	/* clear error detect रेजिस्टर */
	out_be32(pdata->l2_vbase + MPC85XX_L2_ERRDET, err_detect);

	अगर (err_detect & L2_EDE_CE_MASK)
		edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);

	अगर (err_detect & L2_EDE_UE_MASK)
		edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
पूर्ण

अटल irqवापस_t mpc85xx_l2_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = dev_id;
	काष्ठा mpc85xx_l2_pdata *pdata = edac_dev->pvt_info;
	u32 err_detect;

	err_detect = in_be32(pdata->l2_vbase + MPC85XX_L2_ERRDET);

	अगर (!(err_detect & L2_EDE_MASK))
		वापस IRQ_NONE;

	mpc85xx_l2_check(edac_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mpc85xx_l2_err_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा edac_device_ctl_info *edac_dev;
	काष्ठा mpc85xx_l2_pdata *pdata;
	काष्ठा resource r;
	पूर्णांक res;

	अगर (!devres_खोलो_group(&op->dev, mpc85xx_l2_err_probe, GFP_KERNEL))
		वापस -ENOMEM;

	edac_dev = edac_device_alloc_ctl_info(माप(*pdata),
					      "cpu", 1, "L", 1, 2, शून्य, 0,
					      edac_dev_idx);
	अगर (!edac_dev) अणु
		devres_release_group(&op->dev, mpc85xx_l2_err_probe);
		वापस -ENOMEM;
	पूर्ण

	pdata = edac_dev->pvt_info;
	pdata->name = "mpc85xx_l2_err";
	edac_dev->dev = &op->dev;
	dev_set_drvdata(edac_dev->dev, edac_dev);
	edac_dev->ctl_name = pdata->name;
	edac_dev->dev_name = pdata->name;

	res = of_address_to_resource(op->dev.of_node, 0, &r);
	अगर (res) अणु
		pr_err("%s: Unable to get resource for L2 err regs\n", __func__);
		जाओ err;
	पूर्ण

	/* we only need the error रेजिस्टरs */
	r.start += 0xe00;

	अगर (!devm_request_mem_region(&op->dev, r.start, resource_size(&r),
				     pdata->name)) अणु
		pr_err("%s: Error while requesting mem region\n", __func__);
		res = -EBUSY;
		जाओ err;
	पूर्ण

	pdata->l2_vbase = devm_ioremap(&op->dev, r.start, resource_size(&r));
	अगर (!pdata->l2_vbase) अणु
		pr_err("%s: Unable to setup L2 err regs\n", __func__);
		res = -ENOMEM;
		जाओ err;
	पूर्ण

	out_be32(pdata->l2_vbase + MPC85XX_L2_ERRDET, ~0);

	orig_l2_err_disable = in_be32(pdata->l2_vbase + MPC85XX_L2_ERRDIS);

	/* clear the err_dis */
	out_be32(pdata->l2_vbase + MPC85XX_L2_ERRDIS, 0);

	edac_dev->mod_name = EDAC_MOD_STR;

	अगर (edac_op_state == EDAC_OPSTATE_POLL)
		edac_dev->edac_check = mpc85xx_l2_check;

	mpc85xx_set_l2_sysfs_attributes(edac_dev);

	pdata->edac_idx = edac_dev_idx++;

	अगर (edac_device_add_device(edac_dev) > 0) अणु
		edac_dbg(3, "failed edac_device_add_device()\n");
		जाओ err;
	पूर्ण

	अगर (edac_op_state == EDAC_OPSTATE_INT) अणु
		pdata->irq = irq_of_parse_and_map(op->dev.of_node, 0);
		res = devm_request_irq(&op->dev, pdata->irq,
				       mpc85xx_l2_isr, IRQF_SHARED,
				       "[EDAC] L2 err", edac_dev);
		अगर (res < 0) अणु
			pr_err("%s: Unable to request irq %d for MPC85xx L2 err\n",
				__func__, pdata->irq);
			irq_dispose_mapping(pdata->irq);
			res = -ENODEV;
			जाओ err2;
		पूर्ण

		pr_info(EDAC_MOD_STR " acquired irq %d for L2 Err\n", pdata->irq);

		edac_dev->op_state = OP_RUNNING_INTERRUPT;

		out_be32(pdata->l2_vbase + MPC85XX_L2_ERRINTEN, L2_EIE_MASK);
	पूर्ण

	devres_हटाओ_group(&op->dev, mpc85xx_l2_err_probe);

	edac_dbg(3, "success\n");
	pr_info(EDAC_MOD_STR " L2 err registered\n");

	वापस 0;

err2:
	edac_device_del_device(&op->dev);
err:
	devres_release_group(&op->dev, mpc85xx_l2_err_probe);
	edac_device_मुक्त_ctl_info(edac_dev);
	वापस res;
पूर्ण

अटल पूर्णांक mpc85xx_l2_err_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = dev_get_drvdata(&op->dev);
	काष्ठा mpc85xx_l2_pdata *pdata = edac_dev->pvt_info;

	edac_dbg(0, "\n");

	अगर (edac_op_state == EDAC_OPSTATE_INT) अणु
		out_be32(pdata->l2_vbase + MPC85XX_L2_ERRINTEN, 0);
		irq_dispose_mapping(pdata->irq);
	पूर्ण

	out_be32(pdata->l2_vbase + MPC85XX_L2_ERRDIS, orig_l2_err_disable);
	edac_device_del_device(&op->dev);
	edac_device_मुक्त_ctl_info(edac_dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc85xx_l2_err_of_match[] = अणु
/* deprecate the fsl,85.. क्रमms in the future, 2.6.30? */
	अणु .compatible = "fsl,8540-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,8541-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,8544-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,8548-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,8555-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,8568-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8536-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8540-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8541-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8544-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8548-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8555-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8560-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8568-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8569-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8572-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,p1020-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,p1021-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,p2020-l2-cache-controller", पूर्ण,
	अणु .compatible = "fsl,t2080-l2-cache-controller", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc85xx_l2_err_of_match);

अटल काष्ठा platक्रमm_driver mpc85xx_l2_err_driver = अणु
	.probe = mpc85xx_l2_err_probe,
	.हटाओ = mpc85xx_l2_err_हटाओ,
	.driver = अणु
		.name = "mpc85xx_l2_err",
		.of_match_table = mpc85xx_l2_err_of_match,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mpc85xx_mc_err_of_match[] = अणु
/* deprecate the fsl,85.. क्रमms in the future, 2.6.30? */
	अणु .compatible = "fsl,8540-memory-controller", पूर्ण,
	अणु .compatible = "fsl,8541-memory-controller", पूर्ण,
	अणु .compatible = "fsl,8544-memory-controller", पूर्ण,
	अणु .compatible = "fsl,8548-memory-controller", पूर्ण,
	अणु .compatible = "fsl,8555-memory-controller", पूर्ण,
	अणु .compatible = "fsl,8568-memory-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8536-memory-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8540-memory-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8541-memory-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8544-memory-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8548-memory-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8555-memory-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8560-memory-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8568-memory-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8569-memory-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8572-memory-controller", पूर्ण,
	अणु .compatible = "fsl,mpc8349-memory-controller", पूर्ण,
	अणु .compatible = "fsl,p1020-memory-controller", पूर्ण,
	अणु .compatible = "fsl,p1021-memory-controller", पूर्ण,
	अणु .compatible = "fsl,p2020-memory-controller", पूर्ण,
	अणु .compatible = "fsl,qoriq-memory-controller", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc85xx_mc_err_of_match);

अटल काष्ठा platक्रमm_driver mpc85xx_mc_err_driver = अणु
	.probe = fsl_mc_err_probe,
	.हटाओ = fsl_mc_err_हटाओ,
	.driver = अणु
		.name = "mpc85xx_mc_err",
		.of_match_table = mpc85xx_mc_err_of_match,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&mpc85xx_mc_err_driver,
	&mpc85xx_l2_err_driver,
#अगर_घोषित CONFIG_PCI
	&mpc85xx_pci_err_driver,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init mpc85xx_mc_init(व्योम)
अणु
	पूर्णांक res = 0;
	u32 __maybe_unused pvr = 0;

	pr_info("Freescale(R) MPC85xx EDAC driver, (C) 2006 Montavista Software\n");

	/* make sure error reporting method is sane */
	चयन (edac_op_state) अणु
	हाल EDAC_OPSTATE_POLL:
	हाल EDAC_OPSTATE_INT:
		अवरोध;
	शेष:
		edac_op_state = EDAC_OPSTATE_INT;
		अवरोध;
	पूर्ण

	res = platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
	अगर (res)
		pr_warn(EDAC_MOD_STR "drivers fail to register\n");

	वापस 0;
पूर्ण

module_init(mpc85xx_mc_init);

अटल व्योम __निकास mpc85xx_mc_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण

module_निकास(mpc85xx_mc_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Montavista Software, Inc.");
module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state,
		 "EDAC Error Reporting state: 0=Poll, 2=Interrupt");
