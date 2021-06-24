<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * processor thermal device RFIM control
 * Copyright (c) 2020, Intel Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश "processor_thermal_device.h"

काष्ठा mmio_reg अणु
	पूर्णांक पढ़ो_only;
	u32 offset;
	पूर्णांक bits;
	u16 mask;
	u16 shअगरt;
पूर्ण;

/* These will represent sysfs attribute names */
अटल स्थिर अक्षर * स्थिर fivr_strings[] = अणु
	"vco_ref_code_lo",
	"vco_ref_code_hi",
	"spread_spectrum_pct",
	"spread_spectrum_clk_enable",
	"rfi_vco_ref_code",
	"fivr_fffc_rev",
	शून्य
पूर्ण;

अटल स्थिर काष्ठा mmio_reg tgl_fivr_mmio_regs[] = अणु
	अणु 0, 0x5A18, 3, 0x7, 12पूर्ण, /* vco_ref_code_lo */
	अणु 0, 0x5A18, 8, 0xFF, 16पूर्ण, /* vco_ref_code_hi */
	अणु 0, 0x5A08, 8, 0xFF, 0पूर्ण, /* spपढ़ो_spectrum_pct */
	अणु 0, 0x5A08, 1, 0x1, 8पूर्ण, /* spपढ़ो_spectrum_clk_enable */
	अणु 1, 0x5A10, 12, 0xFFF, 0पूर्ण, /* rfi_vco_ref_code */
	अणु 1, 0x5A14, 2, 0x3, 1पूर्ण, /* fivr_fffc_rev */
पूर्ण;

/* These will represent sysfs attribute names */
अटल स्थिर अक्षर * स्थिर dvfs_strings[] = अणु
	"rfi_restriction_run_busy",
	"rfi_restriction_err_code",
	"rfi_restriction_data_rate",
	"rfi_restriction_data_rate_base",
	"ddr_data_rate_point_0",
	"ddr_data_rate_point_1",
	"ddr_data_rate_point_2",
	"ddr_data_rate_point_3",
	"rfi_disable",
	शून्य
पूर्ण;

अटल स्थिर काष्ठा mmio_reg adl_dvfs_mmio_regs[] = अणु
	अणु 0, 0x5A38, 1, 0x1, 31पूर्ण, /* rfi_restriction_run_busy */
	अणु 0, 0x5A38, 7, 0x7F, 24पूर्ण, /* rfi_restriction_err_code */
	अणु 0, 0x5A38, 8, 0xFF, 16पूर्ण, /* rfi_restriction_data_rate */
	अणु 0, 0x5A38, 16, 0xFFFF, 0पूर्ण, /* rfi_restriction_data_rate_base */
	अणु 0, 0x5A30, 10, 0x3FF, 0पूर्ण, /* ddr_data_rate_poपूर्णांक_0 */
	अणु 0, 0x5A30, 10, 0x3FF, 10पूर्ण, /* ddr_data_rate_poपूर्णांक_1 */
	अणु 0, 0x5A30, 10, 0x3FF, 20पूर्ण, /* ddr_data_rate_poपूर्णांक_2 */
	अणु 0, 0x5A30, 10, 0x3FF, 30पूर्ण, /* ddr_data_rate_poपूर्णांक_3 */
	अणु 0, 0x5A40, 1, 0x1, 0पूर्ण, /* rfi_disable */
पूर्ण;

#घोषणा RFIM_SHOW(suffix, table)\
अटल sमाप_प्रकार suffix##_show(काष्ठा device *dev,\
			      काष्ठा device_attribute *attr,\
			      अक्षर *buf)\
अणु\
	काष्ठा proc_thermal_device *proc_priv;\
	काष्ठा pci_dev *pdev = to_pci_dev(dev);\
	स्थिर काष्ठा mmio_reg *mmio_regs;\
	स्थिर अक्षर **match_strs;\
	u32 reg_val;\
	पूर्णांक ret;\
\
	proc_priv = pci_get_drvdata(pdev);\
	अगर (table) अणु\
		match_strs = (स्थिर अक्षर **)dvfs_strings;\
		mmio_regs = adl_dvfs_mmio_regs;\
	पूर्ण अन्यथा अणु \
		match_strs = (स्थिर अक्षर **)fivr_strings;\
		mmio_regs = tgl_fivr_mmio_regs;\
	पूर्ण \
	\
	ret = match_string(match_strs, -1, attr->attr.name);\
	अगर (ret < 0)\
		वापस ret;\
	reg_val = पढ़ोl((व्योम __iomem *) (proc_priv->mmio_base + mmio_regs[ret].offset));\
	ret = (reg_val >> mmio_regs[ret].shअगरt) & mmio_regs[ret].mask;\
	वापस प्र_लिखो(buf, "%u\n", ret);\
पूर्ण

#घोषणा RFIM_STORE(suffix, table)\
अटल sमाप_प्रकार suffix##_store(काष्ठा device *dev,\
			       काष्ठा device_attribute *attr,\
			       स्थिर अक्षर *buf, माप_प्रकार count)\
अणु\
	काष्ठा proc_thermal_device *proc_priv;\
	काष्ठा pci_dev *pdev = to_pci_dev(dev);\
	अचिन्हित पूर्णांक input;\
	स्थिर अक्षर **match_strs;\
	स्थिर काष्ठा mmio_reg *mmio_regs;\
	पूर्णांक ret, err;\
	u32 reg_val;\
	u32 mask;\
\
	proc_priv = pci_get_drvdata(pdev);\
	अगर (table) अणु\
		match_strs = (स्थिर अक्षर **)dvfs_strings;\
		mmio_regs = adl_dvfs_mmio_regs;\
	पूर्ण अन्यथा अणु \
		match_strs = (स्थिर अक्षर **)fivr_strings;\
		mmio_regs = tgl_fivr_mmio_regs;\
	पूर्ण \
	\
	ret = match_string(match_strs, -1, attr->attr.name);\
	अगर (ret < 0)\
		वापस ret;\
	अगर (mmio_regs[ret].पढ़ो_only)\
		वापस -EPERM;\
	err = kstrtouपूर्णांक(buf, 10, &input);\
	अगर (err)\
		वापस err;\
	mask = GENMASK(mmio_regs[ret].shअगरt + mmio_regs[ret].bits - 1, mmio_regs[ret].shअगरt);\
	reg_val = पढ़ोl((व्योम __iomem *) (proc_priv->mmio_base + mmio_regs[ret].offset));\
	reg_val &= ~mask;\
	reg_val |= (input << mmio_regs[ret].shअगरt);\
	ग_लिखोl(reg_val, (व्योम __iomem *) (proc_priv->mmio_base + mmio_regs[ret].offset));\
	वापस count;\
पूर्ण

RFIM_SHOW(vco_ref_code_lo, 0)
RFIM_SHOW(vco_ref_code_hi, 0)
RFIM_SHOW(spपढ़ो_spectrum_pct, 0)
RFIM_SHOW(spपढ़ो_spectrum_clk_enable, 0)
RFIM_SHOW(rfi_vco_ref_code, 0)
RFIM_SHOW(fivr_fffc_rev, 0)

RFIM_STORE(vco_ref_code_lo, 0)
RFIM_STORE(vco_ref_code_hi, 0)
RFIM_STORE(spपढ़ो_spectrum_pct, 0)
RFIM_STORE(spपढ़ो_spectrum_clk_enable, 0)
RFIM_STORE(rfi_vco_ref_code, 0)
RFIM_STORE(fivr_fffc_rev, 0)

अटल DEVICE_ATTR_RW(vco_ref_code_lo);
अटल DEVICE_ATTR_RW(vco_ref_code_hi);
अटल DEVICE_ATTR_RW(spपढ़ो_spectrum_pct);
अटल DEVICE_ATTR_RW(spपढ़ो_spectrum_clk_enable);
अटल DEVICE_ATTR_RW(rfi_vco_ref_code);
अटल DEVICE_ATTR_RW(fivr_fffc_rev);

अटल काष्ठा attribute *fivr_attrs[] = अणु
	&dev_attr_vco_ref_code_lo.attr,
	&dev_attr_vco_ref_code_hi.attr,
	&dev_attr_spपढ़ो_spectrum_pct.attr,
	&dev_attr_spपढ़ो_spectrum_clk_enable.attr,
	&dev_attr_rfi_vco_ref_code.attr,
	&dev_attr_fivr_fffc_rev.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group fivr_attribute_group = अणु
	.attrs = fivr_attrs,
	.name = "fivr"
पूर्ण;

RFIM_SHOW(rfi_restriction_run_busy, 1)
RFIM_SHOW(rfi_restriction_err_code, 1)
RFIM_SHOW(rfi_restriction_data_rate, 1)
RFIM_SHOW(ddr_data_rate_poपूर्णांक_0, 1)
RFIM_SHOW(ddr_data_rate_poपूर्णांक_1, 1)
RFIM_SHOW(ddr_data_rate_poपूर्णांक_2, 1)
RFIM_SHOW(ddr_data_rate_poपूर्णांक_3, 1)
RFIM_SHOW(rfi_disable, 1)

RFIM_STORE(rfi_restriction_run_busy, 1)
RFIM_STORE(rfi_restriction_err_code, 1)
RFIM_STORE(rfi_restriction_data_rate, 1)
RFIM_STORE(rfi_disable, 1)

अटल DEVICE_ATTR_RW(rfi_restriction_run_busy);
अटल DEVICE_ATTR_RW(rfi_restriction_err_code);
अटल DEVICE_ATTR_RW(rfi_restriction_data_rate);
अटल DEVICE_ATTR_RO(ddr_data_rate_poपूर्णांक_0);
अटल DEVICE_ATTR_RO(ddr_data_rate_poपूर्णांक_1);
अटल DEVICE_ATTR_RO(ddr_data_rate_poपूर्णांक_2);
अटल DEVICE_ATTR_RO(ddr_data_rate_poपूर्णांक_3);
अटल DEVICE_ATTR_RW(rfi_disable);

अटल काष्ठा attribute *dvfs_attrs[] = अणु
	&dev_attr_rfi_restriction_run_busy.attr,
	&dev_attr_rfi_restriction_err_code.attr,
	&dev_attr_rfi_restriction_data_rate.attr,
	&dev_attr_ddr_data_rate_poपूर्णांक_0.attr,
	&dev_attr_ddr_data_rate_poपूर्णांक_1.attr,
	&dev_attr_ddr_data_rate_poपूर्णांक_2.attr,
	&dev_attr_ddr_data_rate_poपूर्णांक_3.attr,
	&dev_attr_rfi_disable.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dvfs_attribute_group = अणु
	.attrs = dvfs_attrs,
	.name = "dvfs"
पूर्ण;

पूर्णांक proc_thermal_rfim_add(काष्ठा pci_dev *pdev, काष्ठा proc_thermal_device *proc_priv)
अणु
	पूर्णांक ret;

	अगर (proc_priv->mmio_feature_mask & PROC_THERMAL_FEATURE_FIVR) अणु
		ret = sysfs_create_group(&pdev->dev.kobj, &fivr_attribute_group);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (proc_priv->mmio_feature_mask & PROC_THERMAL_FEATURE_DVFS) अणु
		ret = sysfs_create_group(&pdev->dev.kobj, &dvfs_attribute_group);
		अगर (ret && proc_priv->mmio_feature_mask & PROC_THERMAL_FEATURE_FIVR) अणु
			sysfs_हटाओ_group(&pdev->dev.kobj, &fivr_attribute_group);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(proc_thermal_rfim_add);

व्योम proc_thermal_rfim_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा proc_thermal_device *proc_priv = pci_get_drvdata(pdev);

	अगर (proc_priv->mmio_feature_mask & PROC_THERMAL_FEATURE_FIVR)
		sysfs_हटाओ_group(&pdev->dev.kobj, &fivr_attribute_group);

	अगर (proc_priv->mmio_feature_mask & PROC_THERMAL_FEATURE_DVFS)
		sysfs_हटाओ_group(&pdev->dev.kobj, &dvfs_attribute_group);
पूर्ण
EXPORT_SYMBOL_GPL(proc_thermal_rfim_हटाओ);

MODULE_LICENSE("GPL v2");
