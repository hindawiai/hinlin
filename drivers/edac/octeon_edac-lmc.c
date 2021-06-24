<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2009 Wind River Systems,
 *   written by Ralf Baechle <ralf@linux-mips.org>
 *
 * Copyright (c) 2013 by Cisco Systems, Inc.
 * All rights reserved.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/edac.h>
#समावेश <linux/प्रकार.स>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/cvmx-lmcx-defs.h>

#समावेश "edac_module.h"

#घोषणा OCTEON_MAX_MC 4

#घोषणा to_mci(k) container_of(k, काष्ठा mem_ctl_info, dev)

काष्ठा octeon_lmc_pvt अणु
	अचिन्हित दीर्घ inject;
	अचिन्हित दीर्घ error_type;
	अचिन्हित दीर्घ dimm;
	अचिन्हित दीर्घ rank;
	अचिन्हित दीर्घ bank;
	अचिन्हित दीर्घ row;
	अचिन्हित दीर्घ col;
पूर्ण;

अटल व्योम octeon_lmc_edac_poll(काष्ठा mem_ctl_info *mci)
अणु
	जोड़ cvmx_lmcx_mem_cfg0 cfg0;
	bool करो_clear = false;
	अक्षर msg[64];

	cfg0.u64 = cvmx_पढ़ो_csr(CVMX_LMCX_MEM_CFG0(mci->mc_idx));
	अगर (cfg0.s.sec_err || cfg0.s.ded_err) अणु
		जोड़ cvmx_lmcx_fadr fadr;
		fadr.u64 = cvmx_पढ़ो_csr(CVMX_LMCX_FADR(mci->mc_idx));
		snम_लिखो(msg, माप(msg),
			 "DIMM %d rank %d bank %d row %d col %d",
			 fadr.cn30xx.fdimm, fadr.cn30xx.fbunk,
			 fadr.cn30xx.fbank, fadr.cn30xx.frow, fadr.cn30xx.fcol);
	पूर्ण

	अगर (cfg0.s.sec_err) अणु
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, msg, "");
		cfg0.s.sec_err = -1;	/* Done, re-arm */
		करो_clear = true;
	पूर्ण

	अगर (cfg0.s.ded_err) अणु
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, msg, "");
		cfg0.s.ded_err = -1;	/* Done, re-arm */
		करो_clear = true;
	पूर्ण
	अगर (करो_clear)
		cvmx_ग_लिखो_csr(CVMX_LMCX_MEM_CFG0(mci->mc_idx), cfg0.u64);
पूर्ण

अटल व्योम octeon_lmc_edac_poll_o2(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा octeon_lmc_pvt *pvt = mci->pvt_info;
	जोड़ cvmx_lmcx_पूर्णांक पूर्णांक_reg;
	bool करो_clear = false;
	अक्षर msg[64];

	अगर (!pvt->inject)
		पूर्णांक_reg.u64 = cvmx_पढ़ो_csr(CVMX_LMCX_INT(mci->mc_idx));
	अन्यथा अणु
		पूर्णांक_reg.u64 = 0;
		अगर (pvt->error_type == 1)
			पूर्णांक_reg.s.sec_err = 1;
		अगर (pvt->error_type == 2)
			पूर्णांक_reg.s.ded_err = 1;
	पूर्ण

	अगर (पूर्णांक_reg.s.sec_err || पूर्णांक_reg.s.ded_err) अणु
		जोड़ cvmx_lmcx_fadr fadr;
		अगर (likely(!pvt->inject))
			fadr.u64 = cvmx_पढ़ो_csr(CVMX_LMCX_FADR(mci->mc_idx));
		अन्यथा अणु
			fadr.cn61xx.fdimm = pvt->dimm;
			fadr.cn61xx.fbunk = pvt->rank;
			fadr.cn61xx.fbank = pvt->bank;
			fadr.cn61xx.frow = pvt->row;
			fadr.cn61xx.fcol = pvt->col;
		पूर्ण
		snम_लिखो(msg, माप(msg),
			 "DIMM %d rank %d bank %d row %d col %d",
			 fadr.cn61xx.fdimm, fadr.cn61xx.fbunk,
			 fadr.cn61xx.fbank, fadr.cn61xx.frow, fadr.cn61xx.fcol);
	पूर्ण

	अगर (पूर्णांक_reg.s.sec_err) अणु
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, msg, "");
		पूर्णांक_reg.s.sec_err = -1;	/* Done, re-arm */
		करो_clear = true;
	पूर्ण

	अगर (पूर्णांक_reg.s.ded_err) अणु
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, msg, "");
		पूर्णांक_reg.s.ded_err = -1;	/* Done, re-arm */
		करो_clear = true;
	पूर्ण

	अगर (करो_clear) अणु
		अगर (likely(!pvt->inject))
			cvmx_ग_लिखो_csr(CVMX_LMCX_INT(mci->mc_idx), पूर्णांक_reg.u64);
		अन्यथा
			pvt->inject = 0;
	पूर्ण
पूर्ण

/************************ MC SYSFS parts ***********************************/

/* Only a couple naming dअगरferences per ढाँचा, so very similar */
#घोषणा TEMPLATE_SHOW(reg)						\
अटल sमाप_प्रकार octeon_mc_inject_##reg##_show(काष्ठा device *dev,	\
			       काष्ठा device_attribute *attr,		\
			       अक्षर *data)				\
अणु									\
	काष्ठा mem_ctl_info *mci = to_mci(dev);				\
	काष्ठा octeon_lmc_pvt *pvt = mci->pvt_info;			\
	वापस प्र_लिखो(data, "%016llu\n", (u64)pvt->reg);		\
पूर्ण

#घोषणा TEMPLATE_STORE(reg)						\
अटल sमाप_प्रकार octeon_mc_inject_##reg##_store(काष्ठा device *dev,	\
			       काष्ठा device_attribute *attr,		\
			       स्थिर अक्षर *data, माप_प्रकार count)		\
अणु									\
	काष्ठा mem_ctl_info *mci = to_mci(dev);				\
	काष्ठा octeon_lmc_pvt *pvt = mci->pvt_info;			\
	अगर (है_अंक(*data)) अणु						\
		अगर (!kम_से_अदीर्घ(data, 0, &pvt->reg))			\
			वापस count;					\
	पूर्ण								\
	वापस 0;							\
पूर्ण

TEMPLATE_SHOW(inject);
TEMPLATE_STORE(inject);
TEMPLATE_SHOW(dimm);
TEMPLATE_STORE(dimm);
TEMPLATE_SHOW(bank);
TEMPLATE_STORE(bank);
TEMPLATE_SHOW(rank);
TEMPLATE_STORE(rank);
TEMPLATE_SHOW(row);
TEMPLATE_STORE(row);
TEMPLATE_SHOW(col);
TEMPLATE_STORE(col);

अटल sमाप_प्रकार octeon_mc_inject_error_type_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *data,
					  माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा octeon_lmc_pvt *pvt = mci->pvt_info;

	अगर (!म_भेदन(data, "single", 6))
		pvt->error_type = 1;
	अन्यथा अगर (!म_भेदन(data, "double", 6))
		pvt->error_type = 2;

	वापस count;
पूर्ण

अटल sमाप_प्रकार octeon_mc_inject_error_type_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा octeon_lmc_pvt *pvt = mci->pvt_info;
	अगर (pvt->error_type == 1)
		वापस प्र_लिखो(data, "single");
	अन्यथा अगर (pvt->error_type == 2)
		वापस प्र_लिखो(data, "double");

	वापस 0;
पूर्ण

अटल DEVICE_ATTR(inject, S_IRUGO | S_IWUSR,
		   octeon_mc_inject_inject_show, octeon_mc_inject_inject_store);
अटल DEVICE_ATTR(error_type, S_IRUGO | S_IWUSR,
		   octeon_mc_inject_error_type_show, octeon_mc_inject_error_type_store);
अटल DEVICE_ATTR(dimm, S_IRUGO | S_IWUSR,
		   octeon_mc_inject_dimm_show, octeon_mc_inject_dimm_store);
अटल DEVICE_ATTR(rank, S_IRUGO | S_IWUSR,
		   octeon_mc_inject_rank_show, octeon_mc_inject_rank_store);
अटल DEVICE_ATTR(bank, S_IRUGO | S_IWUSR,
		   octeon_mc_inject_bank_show, octeon_mc_inject_bank_store);
अटल DEVICE_ATTR(row, S_IRUGO | S_IWUSR,
		   octeon_mc_inject_row_show, octeon_mc_inject_row_store);
अटल DEVICE_ATTR(col, S_IRUGO | S_IWUSR,
		   octeon_mc_inject_col_show, octeon_mc_inject_col_store);

अटल काष्ठा attribute *octeon_dev_attrs[] = अणु
	&dev_attr_inject.attr,
	&dev_attr_error_type.attr,
	&dev_attr_dimm.attr,
	&dev_attr_rank.attr,
	&dev_attr_bank.attr,
	&dev_attr_row.attr,
	&dev_attr_col.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(octeon_dev);

अटल पूर्णांक octeon_lmc_edac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[1];
	पूर्णांक mc = pdev->id;

	opstate_init();

	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = 1;
	layers[0].is_virt_csrow = false;

	अगर (OCTEON_IS_OCTEON1PLUS()) अणु
		जोड़ cvmx_lmcx_mem_cfg0 cfg0;

		cfg0.u64 = cvmx_पढ़ो_csr(CVMX_LMCX_MEM_CFG0(0));
		अगर (!cfg0.s.ecc_ena) अणु
			dev_info(&pdev->dev, "Disabled (ECC not enabled)\n");
			वापस 0;
		पूर्ण

		mci = edac_mc_alloc(mc, ARRAY_SIZE(layers), layers, माप(काष्ठा octeon_lmc_pvt));
		अगर (!mci)
			वापस -ENXIO;

		mci->pdev = &pdev->dev;
		mci->dev_name = dev_name(&pdev->dev);

		mci->mod_name = "octeon-lmc";
		mci->ctl_name = "octeon-lmc-err";
		mci->edac_check = octeon_lmc_edac_poll;

		अगर (edac_mc_add_mc_with_groups(mci, octeon_dev_groups)) अणु
			dev_err(&pdev->dev, "edac_mc_add_mc() failed\n");
			edac_mc_मुक्त(mci);
			वापस -ENXIO;
		पूर्ण

		cfg0.u64 = cvmx_पढ़ो_csr(CVMX_LMCX_MEM_CFG0(mc));
		cfg0.s.पूर्णांकr_ded_ena = 0;	/* We poll */
		cfg0.s.पूर्णांकr_sec_ena = 0;
		cvmx_ग_लिखो_csr(CVMX_LMCX_MEM_CFG0(mc), cfg0.u64);
	पूर्ण अन्यथा अणु
		/* OCTEON II */
		जोड़ cvmx_lmcx_पूर्णांक_en en;
		जोड़ cvmx_lmcx_config config;

		config.u64 = cvmx_पढ़ो_csr(CVMX_LMCX_CONFIG(0));
		अगर (!config.s.ecc_ena) अणु
			dev_info(&pdev->dev, "Disabled (ECC not enabled)\n");
			वापस 0;
		पूर्ण

		mci = edac_mc_alloc(mc, ARRAY_SIZE(layers), layers, माप(काष्ठा octeon_lmc_pvt));
		अगर (!mci)
			वापस -ENXIO;

		mci->pdev = &pdev->dev;
		mci->dev_name = dev_name(&pdev->dev);

		mci->mod_name = "octeon-lmc";
		mci->ctl_name = "co_lmc_err";
		mci->edac_check = octeon_lmc_edac_poll_o2;

		अगर (edac_mc_add_mc_with_groups(mci, octeon_dev_groups)) अणु
			dev_err(&pdev->dev, "edac_mc_add_mc() failed\n");
			edac_mc_मुक्त(mci);
			वापस -ENXIO;
		पूर्ण

		en.u64 = cvmx_पढ़ो_csr(CVMX_LMCX_MEM_CFG0(mc));
		en.s.पूर्णांकr_ded_ena = 0;	/* We poll */
		en.s.पूर्णांकr_sec_ena = 0;
		cvmx_ग_लिखो_csr(CVMX_LMCX_MEM_CFG0(mc), en.u64);
	पूर्ण
	platक्रमm_set_drvdata(pdev, mci);

	वापस 0;
पूर्ण

अटल पूर्णांक octeon_lmc_edac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mem_ctl_info *mci = platक्रमm_get_drvdata(pdev);

	edac_mc_del_mc(&pdev->dev);
	edac_mc_मुक्त(mci);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver octeon_lmc_edac_driver = अणु
	.probe = octeon_lmc_edac_probe,
	.हटाओ = octeon_lmc_edac_हटाओ,
	.driver = अणु
		   .name = "octeon_lmc_edac",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(octeon_lmc_edac_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ralf Baechle <ralf@linux-mips.org>");
