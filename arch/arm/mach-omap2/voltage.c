<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP3/OMAP4 Voltage Management Routines
 *
 * Author: Thara Gopinath	<thara@ti.com>
 *
 * Copyright (C) 2007 Texas Instruments, Inc.
 * Rajendra Nayak <rnayak@ti.com>
 * Lesly A M <x0080970@ti.com>
 *
 * Copyright (C) 2008, 2011 Nokia Corporation
 * Kalle Jokiniemi
 * Paul Walmsley
 *
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Thara Gopinath <thara@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>

#समावेश "common.h"

#समावेश "prm-regbits-34xx.h"
#समावेश "prm-regbits-44xx.h"
#समावेश "prm44xx.h"
#समावेश "prcm44xx.h"
#समावेश "prminst44xx.h"
#समावेश "control.h"

#समावेश "voltage.h"
#समावेश "powerdomain.h"

#समावेश "vc.h"
#समावेश "vp.h"

अटल LIST_HEAD(voltdm_list);

/* Public functions */
/**
 * voltdm_get_voltage() - Gets the current non-स्वतः-compensated voltage
 * @voltdm:	poपूर्णांकer to the voltdm क्रम which current voltage info is needed
 *
 * API to get the current non-स्वतः-compensated voltage क्रम a voltage करोमुख्य.
 * Returns 0 in हाल of error अन्यथा वापसs the current voltage.
 */
अचिन्हित दीर्घ voltdm_get_voltage(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	अगर (!voltdm || IS_ERR(voltdm)) अणु
		pr_warn("%s: VDD specified does not exist!\n", __func__);
		वापस 0;
	पूर्ण

	वापस voltdm->nominal_volt;
पूर्ण

/**
 * voltdm_scale() - API to scale voltage of a particular voltage करोमुख्य.
 * @voltdm: poपूर्णांकer to the voltage करोमुख्य which is to be scaled.
 * @target_volt: The target voltage of the voltage करोमुख्य
 *
 * This API should be called by the kernel to करो the voltage scaling
 * क्रम a particular voltage करोमुख्य during DVFS.
 */
पूर्णांक voltdm_scale(काष्ठा voltageकरोमुख्य *voltdm,
		 अचिन्हित दीर्घ target_volt)
अणु
	पूर्णांक ret, i;
	अचिन्हित दीर्घ volt = 0;

	अगर (!voltdm || IS_ERR(voltdm)) अणु
		pr_warn("%s: VDD specified does not exist!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!voltdm->scale) अणु
		pr_err("%s: No voltage scale API registered for vdd_%s\n",
			__func__, voltdm->name);
		वापस -ENODATA;
	पूर्ण

	अगर (!voltdm->volt_data) अणु
		pr_err("%s: No voltage data defined for vdd_%s\n",
			__func__, voltdm->name);
		वापस -ENODATA;
	पूर्ण

	/* Adjust voltage to the exact voltage from the OPP table */
	क्रम (i = 0; voltdm->volt_data[i].volt_nominal != 0; i++) अणु
		अगर (voltdm->volt_data[i].volt_nominal >= target_volt) अणु
			volt = voltdm->volt_data[i].volt_nominal;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!volt) अणु
		pr_warn("%s: not scaling. OPP voltage for %lu, not found.\n",
			__func__, target_volt);
		वापस -EINVAL;
	पूर्ण

	ret = voltdm->scale(voltdm, volt);
	अगर (!ret)
		voltdm->nominal_volt = volt;

	वापस ret;
पूर्ण

/**
 * voltdm_reset() - Resets the voltage of a particular voltage करोमुख्य
 *		    to that of the current OPP.
 * @voltdm: poपूर्णांकer to the voltage करोमुख्य whose voltage is to be reset.
 *
 * This API finds out the correct voltage the voltage करोमुख्य is supposed
 * to be at and resets the voltage to that level. Should be used especially
 * जबतक disabling any voltage compensation modules.
 */
व्योम voltdm_reset(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	अचिन्हित दीर्घ target_volt;

	अगर (!voltdm || IS_ERR(voltdm)) अणु
		pr_warn("%s: VDD specified does not exist!\n", __func__);
		वापस;
	पूर्ण

	target_volt = voltdm_get_voltage(voltdm);
	अगर (!target_volt) अणु
		pr_err("%s: unable to find current voltage for vdd_%s\n",
			__func__, voltdm->name);
		वापस;
	पूर्ण

	voltdm_scale(voltdm, target_volt);
पूर्ण

/**
 * omap_voltage_get_volttable() - API to get the voltage table associated with a
 *				particular voltage करोमुख्य.
 * @voltdm:	poपूर्णांकer to the VDD क्रम which the voltage table is required
 * @volt_data:	the voltage table क्रम the particular vdd which is to be
 *		populated by this API
 *
 * This API populates the voltage table associated with a VDD पूर्णांकo the
 * passed parameter poपूर्णांकer. Returns the count of distinct voltages
 * supported by this vdd.
 *
 */
व्योम omap_voltage_get_volttable(काष्ठा voltageकरोमुख्य *voltdm,
				काष्ठा omap_volt_data **volt_data)
अणु
	अगर (!voltdm || IS_ERR(voltdm)) अणु
		pr_warn("%s: VDD specified does not exist!\n", __func__);
		वापस;
	पूर्ण

	*volt_data = voltdm->volt_data;
पूर्ण

/**
 * omap_voltage_get_voltdata() - API to get the voltage table entry क्रम a
 *				particular voltage
 * @voltdm:	poपूर्णांकer to the VDD whose voltage table has to be searched
 * @volt:	the voltage to be searched in the voltage table
 *
 * This API searches through the voltage table क्रम the required voltage
 * करोमुख्य and tries to find a matching entry क्रम the passed voltage volt.
 * If a matching entry is found volt_data is populated with that entry.
 * This API searches only through the non-compensated voltages पूर्णांक the
 * voltage table.
 * Returns poपूर्णांकer to the voltage table entry corresponding to volt on
 * success. Returns -ENODATA अगर no voltage table exisits क्रम the passed voltage
 * करोमुख्य or अगर there is no matching entry.
 */
काष्ठा omap_volt_data *omap_voltage_get_voltdata(काष्ठा voltageकरोमुख्य *voltdm,
						 अचिन्हित दीर्घ volt)
अणु
	पूर्णांक i;

	अगर (!voltdm || IS_ERR(voltdm)) अणु
		pr_warn("%s: VDD specified does not exist!\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!voltdm->volt_data) अणु
		pr_warn("%s: voltage table does not exist for vdd_%s\n",
			__func__, voltdm->name);
		वापस ERR_PTR(-ENODATA);
	पूर्ण

	क्रम (i = 0; voltdm->volt_data[i].volt_nominal != 0; i++) अणु
		अगर (voltdm->volt_data[i].volt_nominal == volt)
			वापस &voltdm->volt_data[i];
	पूर्ण

	pr_notice("%s: Unable to match the current voltage with the voltage table for vdd_%s\n",
		  __func__, voltdm->name);

	वापस ERR_PTR(-ENODATA);
पूर्ण

/**
 * omap_voltage_रेजिस्टर_pmic() - API to रेजिस्टर PMIC specअगरic data
 * @voltdm:	poपूर्णांकer to the VDD क्रम which the PMIC specअगरic data is
 *		to be रेजिस्टरed
 * @pmic:	the काष्ठाure containing pmic info
 *
 * This API is to be called by the SOC/PMIC file to specअगरy the
 * pmic specअगरic info as present in omap_voltdm_pmic काष्ठाure.
 */
पूर्णांक omap_voltage_रेजिस्टर_pmic(काष्ठा voltageकरोमुख्य *voltdm,
			       काष्ठा omap_voltdm_pmic *pmic)
अणु
	अगर (!voltdm || IS_ERR(voltdm)) अणु
		pr_warn("%s: VDD specified does not exist!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	voltdm->pmic = pmic;

	वापस 0;
पूर्ण

/**
 * omap_voltage_late_init() - Init the various voltage parameters
 *
 * This API is to be called in the later stages of the
 * प्रणाली boot to init the voltage controller and
 * voltage processors.
 */
पूर्णांक __init omap_voltage_late_init(व्योम)
अणु
	काष्ठा voltageकरोमुख्य *voltdm;

	अगर (list_empty(&voltdm_list)) अणु
		pr_err("%s: Voltage driver support not added\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	list_क्रम_each_entry(voltdm, &voltdm_list, node) अणु
		काष्ठा clk *sys_ck;

		अगर (!voltdm->scalable)
			जारी;

		sys_ck = clk_get(शून्य, voltdm->sys_clk.name);
		अगर (IS_ERR(sys_ck)) अणु
			pr_warn("%s: Could not get sys clk.\n", __func__);
			वापस -EINVAL;
		पूर्ण
		voltdm->sys_clk.rate = clk_get_rate(sys_ck);
		WARN_ON(!voltdm->sys_clk.rate);
		clk_put(sys_ck);

		अगर (voltdm->vc) अणु
			voltdm->scale = omap_vc_bypass_scale;
			omap_vc_init_channel(voltdm);
		पूर्ण

		अगर (voltdm->vp) अणु
			voltdm->scale = omap_vp_क्रमceupdate_scale;
			omap_vp_init(voltdm);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा voltageकरोमुख्य *_voltdm_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा voltageकरोमुख्य *voltdm, *temp_voltdm;

	voltdm = शून्य;

	list_क्रम_each_entry(temp_voltdm, &voltdm_list, node) अणु
		अगर (!म_भेद(name, temp_voltdm->name)) अणु
			voltdm = temp_voltdm;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस voltdm;
पूर्ण

अटल पूर्णांक _voltdm_रेजिस्टर(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	अगर (!voltdm || !voltdm->name)
		वापस -EINVAL;

	list_add(&voltdm->node, &voltdm_list);

	pr_debug("voltagedomain: registered %s\n", voltdm->name);

	वापस 0;
पूर्ण

/**
 * voltdm_lookup - look up a voltageकरोमुख्य by name, वापस a poपूर्णांकer
 * @name: name of voltageकरोमुख्य
 *
 * Find a रेजिस्टरed voltageकरोमुख्य by its name @name.  Returns a poपूर्णांकer
 * to the काष्ठा voltageकरोमुख्य अगर found, or शून्य otherwise.
 */
काष्ठा voltageकरोमुख्य *voltdm_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा voltageकरोमुख्य *voltdm ;

	अगर (!name)
		वापस शून्य;

	voltdm = _voltdm_lookup(name);

	वापस voltdm;
पूर्ण

/**
 * voltdm_init - set up the voltageकरोमुख्य layer
 * @voltdm_list: array of काष्ठा voltageकरोमुख्य poपूर्णांकers to रेजिस्टर
 *
 * Loop through the array of voltageकरोमुख्यs @voltdm_list, रेजिस्टरing all
 * that are available on the current CPU. If voltdm_list is supplied
 * and not null, all of the referenced voltageकरोमुख्यs will be
 * रेजिस्टरed.  No वापस value.
 */
व्योम voltdm_init(काष्ठा voltageकरोमुख्य **voltdms)
अणु
	काष्ठा voltageकरोमुख्य **v;

	अगर (voltdms) अणु
		क्रम (v = voltdms; *v; v++)
			_voltdm_रेजिस्टर(*v);
	पूर्ण
पूर्ण
