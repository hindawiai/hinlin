<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Texas Instruments DDR3 ECC error correction and detection driver
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#समावेश <linux/init.h>
#समावेश <linux/edac.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>

#समावेश "edac_module.h"

/* EMIF controller रेजिस्टरs */
#घोषणा EMIF_SDRAM_CONFIG		0x008
#घोषणा EMIF_IRQ_STATUS			0x0ac
#घोषणा EMIF_IRQ_ENABLE_SET		0x0b4
#घोषणा EMIF_ECC_CTRL			0x110
#घोषणा EMIF_1B_ECC_ERR_CNT		0x130
#घोषणा EMIF_1B_ECC_ERR_THRSH		0x134
#घोषणा EMIF_1B_ECC_ERR_ADDR_LOG	0x13c
#घोषणा EMIF_2B_ECC_ERR_ADDR_LOG	0x140

/* Bit definitions क्रम EMIF_SDRAM_CONFIG */
#घोषणा SDRAM_TYPE_SHIFT		29
#घोषणा SDRAM_TYPE_MASK			GENMASK(31, 29)
#घोषणा SDRAM_TYPE_DDR3			(3 << SDRAM_TYPE_SHIFT)
#घोषणा SDRAM_TYPE_DDR2			(2 << SDRAM_TYPE_SHIFT)
#घोषणा SDRAM_NARROW_MODE_MASK		GENMASK(15, 14)
#घोषणा SDRAM_K2_NARROW_MODE_SHIFT	12
#घोषणा SDRAM_K2_NARROW_MODE_MASK	GENMASK(13, 12)
#घोषणा SDRAM_ROWSIZE_SHIFT		7
#घोषणा SDRAM_ROWSIZE_MASK		GENMASK(9, 7)
#घोषणा SDRAM_IBANK_SHIFT		4
#घोषणा SDRAM_IBANK_MASK		GENMASK(6, 4)
#घोषणा SDRAM_K2_IBANK_SHIFT		5
#घोषणा SDRAM_K2_IBANK_MASK		GENMASK(6, 5)
#घोषणा SDRAM_K2_EBANK_SHIFT		3
#घोषणा SDRAM_K2_EBANK_MASK		BIT(SDRAM_K2_EBANK_SHIFT)
#घोषणा SDRAM_PAGESIZE_SHIFT		0
#घोषणा SDRAM_PAGESIZE_MASK		GENMASK(2, 0)
#घोषणा SDRAM_K2_PAGESIZE_SHIFT		0
#घोषणा SDRAM_K2_PAGESIZE_MASK		GENMASK(1, 0)

#घोषणा EMIF_1B_ECC_ERR_THRSH_SHIFT	24

/* IRQ bit definitions */
#घोषणा EMIF_1B_ECC_ERR			BIT(5)
#घोषणा EMIF_2B_ECC_ERR			BIT(4)
#घोषणा EMIF_WR_ECC_ERR			BIT(3)
#घोषणा EMIF_SYS_ERR			BIT(0)
/* Bit 31 enables ECC and 28 enables RMW */
#घोषणा ECC_ENABLED			(BIT(31) | BIT(28))

#घोषणा EDAC_MOD_NAME			"ti-emif-edac"

क्रमागत अणु
	EMIF_TYPE_DRA7,
	EMIF_TYPE_K2
पूर्ण;

काष्ठा ti_edac अणु
	व्योम __iomem *reg;
पूर्ण;

अटल u32 ti_edac_पढ़ोl(काष्ठा ti_edac *edac, u16 offset)
अणु
	वापस पढ़ोl_relaxed(edac->reg + offset);
पूर्ण

अटल व्योम ti_edac_ग_लिखोl(काष्ठा ti_edac *edac, u32 val, u16 offset)
अणु
	ग_लिखोl_relaxed(val, edac->reg + offset);
पूर्ण

अटल irqवापस_t ti_edac_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mem_ctl_info *mci = data;
	काष्ठा ti_edac *edac = mci->pvt_info;
	u32 irq_status;
	u32 err_addr;
	पूर्णांक err_count;

	irq_status = ti_edac_पढ़ोl(edac, EMIF_IRQ_STATUS);

	अगर (irq_status & EMIF_1B_ECC_ERR) अणु
		err_addr = ti_edac_पढ़ोl(edac, EMIF_1B_ECC_ERR_ADDR_LOG);
		err_count = ti_edac_पढ़ोl(edac, EMIF_1B_ECC_ERR_CNT);
		ti_edac_ग_लिखोl(edac, err_count, EMIF_1B_ECC_ERR_CNT);
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, err_count,
				     err_addr >> PAGE_SHIFT,
				     err_addr & ~PAGE_MASK, -1, 0, 0, 0,
				     mci->ctl_name, "1B");
	पूर्ण

	अगर (irq_status & EMIF_2B_ECC_ERR) अणु
		err_addr = ti_edac_पढ़ोl(edac, EMIF_2B_ECC_ERR_ADDR_LOG);
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     err_addr >> PAGE_SHIFT,
				     err_addr & ~PAGE_MASK, -1, 0, 0, 0,
				     mci->ctl_name, "2B");
	पूर्ण

	अगर (irq_status & EMIF_WR_ECC_ERR)
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     0, 0, -1, 0, 0, 0,
				     mci->ctl_name, "WR");

	ti_edac_ग_लिखोl(edac, irq_status, EMIF_IRQ_STATUS);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ti_edac_setup_dimm(काष्ठा mem_ctl_info *mci, u32 type)
अणु
	काष्ठा dimm_info *dimm;
	काष्ठा ti_edac *edac = mci->pvt_info;
	पूर्णांक bits;
	u32 val;
	u32 memsize;

	dimm = edac_get_dimm(mci, 0, 0, 0);

	val = ti_edac_पढ़ोl(edac, EMIF_SDRAM_CONFIG);

	अगर (type == EMIF_TYPE_DRA7) अणु
		bits = ((val & SDRAM_PAGESIZE_MASK) >> SDRAM_PAGESIZE_SHIFT) + 8;
		bits += ((val & SDRAM_ROWSIZE_MASK) >> SDRAM_ROWSIZE_SHIFT) + 9;
		bits += (val & SDRAM_IBANK_MASK) >> SDRAM_IBANK_SHIFT;

		अगर (val & SDRAM_NARROW_MODE_MASK) अणु
			bits++;
			dimm->dtype = DEV_X16;
		पूर्ण अन्यथा अणु
			bits += 2;
			dimm->dtype = DEV_X32;
		पूर्ण
	पूर्ण अन्यथा अणु
		bits = 16;
		bits += ((val & SDRAM_K2_PAGESIZE_MASK) >>
			SDRAM_K2_PAGESIZE_SHIFT) + 8;
		bits += (val & SDRAM_K2_IBANK_MASK) >> SDRAM_K2_IBANK_SHIFT;
		bits += (val & SDRAM_K2_EBANK_MASK) >> SDRAM_K2_EBANK_SHIFT;

		val = (val & SDRAM_K2_NARROW_MODE_MASK) >>
			SDRAM_K2_NARROW_MODE_SHIFT;
		चयन (val) अणु
		हाल 0:
			bits += 3;
			dimm->dtype = DEV_X64;
			अवरोध;
		हाल 1:
			bits += 2;
			dimm->dtype = DEV_X32;
			अवरोध;
		हाल 2:
			bits++;
			dimm->dtype = DEV_X16;
			अवरोध;
		पूर्ण
	पूर्ण

	memsize = 1 << bits;

	dimm->nr_pages = memsize >> PAGE_SHIFT;
	dimm->grain = 4;
	अगर ((val & SDRAM_TYPE_MASK) == SDRAM_TYPE_DDR2)
		dimm->mtype = MEM_DDR2;
	अन्यथा
		dimm->mtype = MEM_DDR3;

	val = ti_edac_पढ़ोl(edac, EMIF_ECC_CTRL);
	अगर (val & ECC_ENABLED)
		dimm->edac_mode = EDAC_SECDED;
	अन्यथा
		dimm->edac_mode = EDAC_NONE;
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_edac_of_match[] = अणु
	अणु .compatible = "ti,emif-keystone", .data = (व्योम *)EMIF_TYPE_K2 पूर्ण,
	अणु .compatible = "ti,emif-dra7xx", .data = (व्योम *)EMIF_TYPE_DRA7 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक _emअगर_get_id(काष्ठा device_node *node)
अणु
	काष्ठा device_node *np;
	स्थिर __be32 *addrp;
	u32 addr, my_addr;
	पूर्णांक my_id = 0;

	addrp = of_get_address(node, 0, शून्य, शून्य);
	my_addr = (u32)of_translate_address(node, addrp);

	क्रम_each_matching_node(np, ti_edac_of_match) अणु
		अगर (np == node)
			जारी;

		addrp = of_get_address(np, 0, शून्य, शून्य);
		addr = (u32)of_translate_address(np, addrp);

		edac_prपूर्णांकk(KERN_INFO, EDAC_MOD_NAME,
			    "addr=%x, my_addr=%x\n",
			    addr, my_addr);

		अगर (addr < my_addr)
			my_id++;
	पूर्ण

	वापस my_id;
पूर्ण

अटल पूर्णांक ti_edac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक error_irq = 0, ret = -ENODEV;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	व्योम __iomem *reg;
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[1];
	स्थिर काष्ठा of_device_id *id;
	काष्ठा ti_edac *edac;
	पूर्णांक emअगर_id;

	id = of_match_device(ti_edac_of_match, &pdev->dev);
	अगर (!id)
		वापस -ENODEV;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(reg)) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MOD_NAME,
			    "EMIF controller regs not defined\n");
		वापस PTR_ERR(reg);
	पूर्ण

	layers[0].type = EDAC_MC_LAYER_ALL_MEM;
	layers[0].size = 1;

	/* Allocate ID number क्रम our EMIF controller */
	emअगर_id = _emअगर_get_id(pdev->dev.of_node);
	अगर (emअगर_id < 0)
		वापस -EINVAL;

	mci = edac_mc_alloc(emअगर_id, 1, layers, माप(*edac));
	अगर (!mci)
		वापस -ENOMEM;

	mci->pdev = &pdev->dev;
	edac = mci->pvt_info;
	edac->reg = reg;
	platक्रमm_set_drvdata(pdev, mci);

	mci->mtype_cap = MEM_FLAG_DDR3 | MEM_FLAG_DDR2;
	mci->edac_ctl_cap = EDAC_FLAG_SECDED | EDAC_FLAG_NONE;
	mci->mod_name = EDAC_MOD_NAME;
	mci->ctl_name = id->compatible;
	mci->dev_name = dev_name(&pdev->dev);

	/* Setup memory layout */
	ti_edac_setup_dimm(mci, (u32)(id->data));

	/* add EMIF ECC error handler */
	error_irq = platक्रमm_get_irq(pdev, 0);
	अगर (error_irq < 0) अणु
		ret = error_irq;
		edac_prपूर्णांकk(KERN_ERR, EDAC_MOD_NAME,
			    "EMIF irq number not defined.\n");
		जाओ err;
	पूर्ण

	ret = devm_request_irq(dev, error_irq, ti_edac_isr, 0,
			       "emif-edac-irq", mci);
	अगर (ret) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MOD_NAME,
			    "request_irq fail for EMIF EDAC irq\n");
		जाओ err;
	पूर्ण

	ret = edac_mc_add_mc(mci);
	अगर (ret) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MOD_NAME,
			    "Failed to register mci: %d.\n", ret);
		जाओ err;
	पूर्ण

	/* Generate an पूर्णांकerrupt with each 1b error */
	ti_edac_ग_लिखोl(edac, 1 << EMIF_1B_ECC_ERR_THRSH_SHIFT,
		       EMIF_1B_ECC_ERR_THRSH);

	/* Enable पूर्णांकerrupts */
	ti_edac_ग_लिखोl(edac,
		       EMIF_1B_ECC_ERR | EMIF_2B_ECC_ERR | EMIF_WR_ECC_ERR,
		       EMIF_IRQ_ENABLE_SET);

	वापस 0;

err:
	edac_mc_मुक्त(mci);
	वापस ret;
पूर्ण

अटल पूर्णांक ti_edac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mem_ctl_info *mci = platक्रमm_get_drvdata(pdev);

	edac_mc_del_mc(&pdev->dev);
	edac_mc_मुक्त(mci);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ti_edac_driver = अणु
	.probe = ti_edac_probe,
	.हटाओ = ti_edac_हटाओ,
	.driver = अणु
		   .name = EDAC_MOD_NAME,
		   .of_match_table = ti_edac_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ti_edac_driver);

MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_DESCRIPTION("EDAC Driver for Texas Instruments DDR3 MC");
MODULE_LICENSE("GPL v2");
