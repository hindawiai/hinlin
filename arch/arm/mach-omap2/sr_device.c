<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP3/OMAP4 smartreflex device file
 *
 * Author: Thara Gopinath	<thara@ti.com>
 *
 * Based originally on code from smartreflex.c
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Thara Gopinath <thara@ti.com>
 *
 * Copyright (C) 2008 Nokia Corporation
 * Kalle Jokiniemi
 *
 * Copyright (C) 2007 Texas Instruments, Inc.
 * Lesly A M <x0080970@ti.com>
 */
#समावेश <linux/घातer/smartreflex.h>

#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश "soc.h"
#समावेश "omap_device.h"
#समावेश "voltage.h"
#समावेश "control.h"
#समावेश "pm.h"

अटल bool sr_enable_on_init;

/* Read EFUSE values from control रेजिस्टरs क्रम OMAP3430 */
अटल व्योम __init sr_set_nvalues(काष्ठा omap_volt_data *volt_data,
				काष्ठा omap_sr_data *sr_data)
अणु
	काष्ठा omap_sr_nvalue_table *nvalue_table;
	पूर्णांक i, j, count = 0;

	sr_data->nvalue_count = 0;
	sr_data->nvalue_table = शून्य;

	जबतक (volt_data[count].volt_nominal)
		count++;

	nvalue_table = kसुस्मृति(count, माप(*nvalue_table), GFP_KERNEL);
	अगर (!nvalue_table)
		वापस;

	क्रम (i = 0, j = 0; i < count; i++) अणु
		u32 v;

		/*
		 * In OMAP4 the efuse रेजिस्टरs are 24 bit aligned.
		 * A पढ़ोl_relaxed will fail क्रम non-32 bit aligned address
		 * and hence the 8-bit पढ़ो and shअगरt.
		 */
		अगर (cpu_is_omap44xx()) अणु
			u16 offset = volt_data[i].sr_efuse_offs;

			v = omap_ctrl_पढ़ोb(offset) |
				omap_ctrl_पढ़ोb(offset + 1) << 8 |
				omap_ctrl_पढ़ोb(offset + 2) << 16;
		पूर्ण अन्यथा अणु
			v = omap_ctrl_पढ़ोl(volt_data[i].sr_efuse_offs);
		पूर्ण

		/*
		 * Many OMAP SoCs करोn't have the eFuse values set.
		 * For example, pretty much all OMAP3xxx beक्रमe
		 * ES3.something.
		 *
		 * XXX There needs to be some way क्रम board files or
		 * userspace to add these in.
		 */
		अगर (v == 0)
			जारी;

		nvalue_table[j].nvalue = v;
		nvalue_table[j].efuse_offs = volt_data[i].sr_efuse_offs;
		nvalue_table[j].errminlimit = volt_data[i].sr_errminlimit;
		nvalue_table[j].volt_nominal = volt_data[i].volt_nominal;

		j++;
	पूर्ण

	sr_data->nvalue_table = nvalue_table;
	sr_data->nvalue_count = j;
पूर्ण

बाह्य काष्ठा omap_sr_data omap_sr_pdata[];

अटल पूर्णांक __init sr_init_by_name(स्थिर अक्षर *name, स्थिर अक्षर *voltdm)
अणु
	काष्ठा omap_sr_data *sr_data = शून्य;
	काष्ठा omap_volt_data *volt_data;
	अटल पूर्णांक i;

	अगर (!म_भेदन(name, "smartreflex_mpu_iva", 20) ||
	    !म_भेदन(name, "smartreflex_mpu", 16))
		sr_data = &omap_sr_pdata[OMAP_SR_MPU];
	अन्यथा अगर (!म_भेदन(name, "smartreflex_core", 17))
		sr_data = &omap_sr_pdata[OMAP_SR_CORE];
	अन्यथा अगर (!म_भेदन(name, "smartreflex_iva", 16))
		sr_data = &omap_sr_pdata[OMAP_SR_IVA];

	अगर (!sr_data) अणु
		pr_err("%s: Unknown instance %s\n", __func__, name);
		वापस -EINVAL;
	पूर्ण

	sr_data->name = name;
	अगर (cpu_is_omap343x())
		sr_data->ip_type = 1;
	अन्यथा
		sr_data->ip_type = 2;
	sr_data->senn_mod = 0x1;
	sr_data->senp_mod = 0x1;

	अगर (cpu_is_omap34xx() || cpu_is_omap44xx()) अणु
		sr_data->err_weight = OMAP3430_SR_ERRWEIGHT;
		sr_data->err_maxlimit = OMAP3430_SR_ERRMAXLIMIT;
		sr_data->accum_data = OMAP3430_SR_ACCUMDATA;
		अगर (!(म_भेद(sr_data->name, "smartreflex_mpu"))) अणु
			sr_data->senn_avgweight = OMAP3430_SR1_SENNAVGWEIGHT;
			sr_data->senp_avgweight = OMAP3430_SR1_SENPAVGWEIGHT;
		पूर्ण अन्यथा अणु
			sr_data->senn_avgweight = OMAP3430_SR2_SENNAVGWEIGHT;
			sr_data->senp_avgweight = OMAP3430_SR2_SENPAVGWEIGHT;
		पूर्ण
	पूर्ण

	sr_data->voltdm = voltdm_lookup(voltdm);
	अगर (!sr_data->voltdm) अणु
		pr_err("%s: Unable to get voltage domain pointer for VDD %s\n",
			__func__, voltdm);
		जाओ निकास;
	पूर्ण

	omap_voltage_get_volttable(sr_data->voltdm, &volt_data);
	अगर (!volt_data) अणु
		pr_err("%s: No Voltage table registered for VDD%d\n",
		       __func__, i + 1);
		जाओ निकास;
	पूर्ण

	sr_set_nvalues(volt_data, sr_data);

	sr_data->enable_on_init = sr_enable_on_init;

निकास:
	i++;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OMAP_HWMOD
अटल पूर्णांक __init sr_dev_init(काष्ठा omap_hwmod *oh, व्योम *user)
अणु
	काष्ठा omap_smartreflex_dev_attr *sr_dev_attr;

	sr_dev_attr = (काष्ठा omap_smartreflex_dev_attr *)oh->dev_attr;
	अगर (!sr_dev_attr || !sr_dev_attr->sensor_voltdm_name) अणु
		pr_err("%s: No voltage domain specified for %s. Cannot initialize\n",
		       __func__, oh->name);
		वापस 0;
	पूर्ण

	वापस sr_init_by_name(oh->name, sr_dev_attr->sensor_voltdm_name);
पूर्ण
#अन्यथा
अटल पूर्णांक __init sr_dev_init(काष्ठा omap_hwmod *oh, व्योम *user)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

/*
 * API to be called from board files to enable smartreflex
 * स्वतःcompensation at init.
 */
व्योम __init omap_enable_smartreflex_on_init(व्योम)
अणु
	sr_enable_on_init = true;
पूर्ण

अटल स्थिर अक्षर * स्थिर omap4_sr_instances[] = अणु
	"mpu",
	"iva",
	"core",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dra7_sr_instances[] = अणु
	"mpu",
	"core",
पूर्ण;

पूर्णांक __init omap_devinit_smartreflex(व्योम)
अणु
	स्थिर अक्षर * स्थिर *sr_inst = शून्य;
	पूर्णांक i, nr_sr = 0;

	अगर (soc_is_omap44xx()) अणु
		sr_inst = omap4_sr_instances;
		nr_sr = ARRAY_SIZE(omap4_sr_instances);

	पूर्ण अन्यथा अगर (soc_is_dra7xx()) अणु
		sr_inst = dra7_sr_instances;
		nr_sr = ARRAY_SIZE(dra7_sr_instances);
	पूर्ण

	अगर (nr_sr) अणु
		स्थिर अक्षर *name, *voltdm;

		क्रम (i = 0; i < nr_sr; i++) अणु
			name = kaप्र_लिखो(GFP_KERNEL, "smartreflex_%s", sr_inst[i]);
			voltdm = sr_inst[i];
			sr_init_by_name(name, voltdm);
		पूर्ण

		वापस 0;
	पूर्ण

	वापस omap_hwmod_क्रम_each_by_class("smartreflex", sr_dev_init, शून्य);
पूर्ण
