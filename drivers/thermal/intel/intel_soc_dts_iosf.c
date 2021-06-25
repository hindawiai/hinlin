<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel_soc_dts_iosf.c
 * Copyright (c) 2015, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/iosf_mbi.h>
#समावेश "intel_soc_dts_iosf.h"

#घोषणा SOC_DTS_OFFSET_ENABLE		0xB0
#घोषणा SOC_DTS_OFFSET_TEMP		0xB1

#घोषणा SOC_DTS_OFFSET_PTPS		0xB2
#घोषणा SOC_DTS_OFFSET_PTTS		0xB3
#घोषणा SOC_DTS_OFFSET_PTTSS		0xB4
#घोषणा SOC_DTS_OFFSET_PTMC		0x80
#घोषणा SOC_DTS_TE_AUX0			0xB5
#घोषणा SOC_DTS_TE_AUX1			0xB6

#घोषणा SOC_DTS_AUX0_ENABLE_BIT		BIT(0)
#घोषणा SOC_DTS_AUX1_ENABLE_BIT		BIT(1)
#घोषणा SOC_DTS_CPU_MODULE0_ENABLE_BIT	BIT(16)
#घोषणा SOC_DTS_CPU_MODULE1_ENABLE_BIT	BIT(17)
#घोषणा SOC_DTS_TE_SCI_ENABLE		BIT(9)
#घोषणा SOC_DTS_TE_SMI_ENABLE		BIT(10)
#घोषणा SOC_DTS_TE_MSI_ENABLE		BIT(11)
#घोषणा SOC_DTS_TE_APICA_ENABLE		BIT(14)
#घोषणा SOC_DTS_PTMC_APIC_DEASSERT_BIT	BIT(4)

/* DTS encoding क्रम TJ MAX temperature */
#घोषणा SOC_DTS_TJMAX_ENCODING		0x7F

/* Only 2 out of 4 is allowed क्रम OSPM */
#घोषणा SOC_MAX_DTS_TRIPS		2

/* Mask क्रम two trips in status bits */
#घोषणा SOC_DTS_TRIP_MASK		0x03

/* DTS0 and DTS 1 */
#घोषणा SOC_MAX_DTS_SENSORS		2

अटल पूर्णांक get_tj_max(u32 *tj_max)
अणु
	u32 eax, edx;
	u32 val;
	पूर्णांक err;

	err = rdmsr_safe(MSR_IA32_TEMPERATURE_TARGET, &eax, &edx);
	अगर (err)
		जाओ err_ret;
	अन्यथा अणु
		val = (eax >> 16) & 0xff;
		अगर (val)
			*tj_max = val * 1000;
		अन्यथा अणु
			err = -EINVAL;
			जाओ err_ret;
		पूर्ण
	पूर्ण

	वापस 0;
err_ret:
	*tj_max = 0;

	वापस err;
पूर्ण

अटल पूर्णांक sys_get_trip_temp(काष्ठा thermal_zone_device *tzd, पूर्णांक trip,
			     पूर्णांक *temp)
अणु
	पूर्णांक status;
	u32 out;
	काष्ठा पूर्णांकel_soc_dts_sensor_entry *dts;
	काष्ठा पूर्णांकel_soc_dts_sensors *sensors;

	dts = tzd->devdata;
	sensors = dts->sensors;
	mutex_lock(&sensors->dts_update_lock);
	status = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_OFFSET_PTPS, &out);
	mutex_unlock(&sensors->dts_update_lock);
	अगर (status)
		वापस status;

	out = (out >> (trip * 8)) & SOC_DTS_TJMAX_ENCODING;
	अगर (!out)
		*temp = 0;
	अन्यथा
		*temp = sensors->tj_max - out * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक update_trip_temp(काष्ठा पूर्णांकel_soc_dts_sensor_entry *dts,
			    पूर्णांक thres_index, पूर्णांक temp,
			    क्रमागत thermal_trip_type trip_type)
अणु
	पूर्णांक status;
	u32 temp_out;
	u32 out;
	अचिन्हित दीर्घ update_ptps;
	u32 store_ptps;
	u32 store_pपंचांगc;
	u32 store_te_out;
	u32 te_out;
	u32 पूर्णांक_enable_bit = SOC_DTS_TE_APICA_ENABLE;
	काष्ठा पूर्णांकel_soc_dts_sensors *sensors = dts->sensors;

	अगर (sensors->पूर्णांकr_type == INTEL_SOC_DTS_INTERRUPT_MSI)
		पूर्णांक_enable_bit |= SOC_DTS_TE_MSI_ENABLE;

	temp_out = (sensors->tj_max - temp) / 1000;

	status = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_OFFSET_PTPS, &store_ptps);
	अगर (status)
		वापस status;

	update_ptps = store_ptps;
	biपंचांगap_set_value8(&update_ptps, temp_out & 0xFF, thres_index * 8);
	out = update_ptps;

	status = iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
				SOC_DTS_OFFSET_PTPS, out);
	अगर (status)
		वापस status;

	pr_debug("update_trip_temp PTPS = %x\n", out);
	status = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_OFFSET_PTMC, &out);
	अगर (status)
		जाओ err_restore_ptps;

	store_pपंचांगc = out;

	status = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_TE_AUX0 + thres_index,
			       &te_out);
	अगर (status)
		जाओ err_restore_pपंचांगc;

	store_te_out = te_out;
	/* Enable क्रम CPU module 0 and module 1 */
	out |= (SOC_DTS_CPU_MODULE0_ENABLE_BIT |
					SOC_DTS_CPU_MODULE1_ENABLE_BIT);
	अगर (temp) अणु
		अगर (thres_index)
			out |= SOC_DTS_AUX1_ENABLE_BIT;
		अन्यथा
			out |= SOC_DTS_AUX0_ENABLE_BIT;
		te_out |= पूर्णांक_enable_bit;
	पूर्ण अन्यथा अणु
		अगर (thres_index)
			out &= ~SOC_DTS_AUX1_ENABLE_BIT;
		अन्यथा
			out &= ~SOC_DTS_AUX0_ENABLE_BIT;
		te_out &= ~पूर्णांक_enable_bit;
	पूर्ण
	status = iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
				SOC_DTS_OFFSET_PTMC, out);
	अगर (status)
		जाओ err_restore_te_out;

	status = iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
				SOC_DTS_TE_AUX0 + thres_index,
				te_out);
	अगर (status)
		जाओ err_restore_te_out;

	dts->trip_types[thres_index] = trip_type;

	वापस 0;
err_restore_te_out:
	iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
		       SOC_DTS_OFFSET_PTMC, store_te_out);
err_restore_pपंचांगc:
	iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
		       SOC_DTS_OFFSET_PTMC, store_pपंचांगc);
err_restore_ptps:
	iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
		       SOC_DTS_OFFSET_PTPS, store_ptps);
	/* Nothing we can करो अगर restore fails */

	वापस status;
पूर्ण

अटल पूर्णांक sys_set_trip_temp(काष्ठा thermal_zone_device *tzd, पूर्णांक trip,
			     पूर्णांक temp)
अणु
	काष्ठा पूर्णांकel_soc_dts_sensor_entry *dts = tzd->devdata;
	काष्ठा पूर्णांकel_soc_dts_sensors *sensors = dts->sensors;
	पूर्णांक status;

	अगर (temp > sensors->tj_max)
		वापस -EINVAL;

	mutex_lock(&sensors->dts_update_lock);
	status = update_trip_temp(tzd->devdata, trip, temp,
				  dts->trip_types[trip]);
	mutex_unlock(&sensors->dts_update_lock);

	वापस status;
पूर्ण

अटल पूर्णांक sys_get_trip_type(काष्ठा thermal_zone_device *tzd,
			     पूर्णांक trip, क्रमागत thermal_trip_type *type)
अणु
	काष्ठा पूर्णांकel_soc_dts_sensor_entry *dts;

	dts = tzd->devdata;

	*type = dts->trip_types[trip];

	वापस 0;
पूर्ण

अटल पूर्णांक sys_get_curr_temp(काष्ठा thermal_zone_device *tzd,
			     पूर्णांक *temp)
अणु
	पूर्णांक status;
	u32 out;
	काष्ठा पूर्णांकel_soc_dts_sensor_entry *dts;
	काष्ठा पूर्णांकel_soc_dts_sensors *sensors;
	अचिन्हित दीर्घ raw;

	dts = tzd->devdata;
	sensors = dts->sensors;
	status = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_OFFSET_TEMP, &out);
	अगर (status)
		वापस status;

	raw = out;
	out = biपंचांगap_get_value8(&raw, dts->id * 8) - SOC_DTS_TJMAX_ENCODING;
	*temp = sensors->tj_max - out * 1000;

	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_device_ops tzone_ops = अणु
	.get_temp = sys_get_curr_temp,
	.get_trip_temp = sys_get_trip_temp,
	.get_trip_type = sys_get_trip_type,
	.set_trip_temp = sys_set_trip_temp,
पूर्ण;

अटल पूर्णांक soc_dts_enable(पूर्णांक id)
अणु
	u32 out;
	पूर्णांक ret;

	ret = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ,
			    SOC_DTS_OFFSET_ENABLE, &out);
	अगर (ret)
		वापस ret;

	अगर (!(out & BIT(id))) अणु
		out |= BIT(id);
		ret = iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
				     SOC_DTS_OFFSET_ENABLE, out);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम हटाओ_dts_thermal_zone(काष्ठा पूर्णांकel_soc_dts_sensor_entry *dts)
अणु
	अगर (dts) अणु
		iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
			       SOC_DTS_OFFSET_ENABLE, dts->store_status);
		thermal_zone_device_unरेजिस्टर(dts->tzone);
	पूर्ण
पूर्ण

अटल पूर्णांक add_dts_thermal_zone(पूर्णांक id, काष्ठा पूर्णांकel_soc_dts_sensor_entry *dts,
				bool notअगरication_support, पूर्णांक trip_cnt,
				पूर्णांक पढ़ो_only_trip_cnt)
अणु
	अक्षर name[10];
	अचिन्हित दीर्घ trip;
	पूर्णांक trip_count = 0;
	पूर्णांक trip_mask = 0;
	पूर्णांक writable_trip_cnt = 0;
	अचिन्हित दीर्घ ptps;
	u32 store_ptps;
	अचिन्हित दीर्घ i;
	पूर्णांक ret;

	/* Store status to restor on निकास */
	ret = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ,
			    SOC_DTS_OFFSET_ENABLE, &dts->store_status);
	अगर (ret)
		जाओ err_ret;

	dts->id = id;
	अगर (notअगरication_support) अणु
		trip_count = min(SOC_MAX_DTS_TRIPS, trip_cnt);
		writable_trip_cnt = trip_count - पढ़ो_only_trip_cnt;
		trip_mask = GENMASK(writable_trip_cnt - 1, 0);
	पूर्ण

	/* Check अगर the writable trip we provide is not used by BIOS */
	ret = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ,
			    SOC_DTS_OFFSET_PTPS, &store_ptps);
	अगर (ret)
		trip_mask = 0;
	अन्यथा अणु
		ptps = store_ptps;
		क्रम_each_set_clump8(i, trip, &ptps, writable_trip_cnt * 8)
			trip_mask &= ~BIT(i / 8);
	पूर्ण
	dts->trip_mask = trip_mask;
	dts->trip_count = trip_count;
	snम_लिखो(name, माप(name), "soc_dts%d", id);
	dts->tzone = thermal_zone_device_रेजिस्टर(name,
						  trip_count,
						  trip_mask,
						  dts, &tzone_ops,
						  शून्य, 0, 0);
	अगर (IS_ERR(dts->tzone)) अणु
		ret = PTR_ERR(dts->tzone);
		जाओ err_ret;
	पूर्ण
	ret = thermal_zone_device_enable(dts->tzone);
	अगर (ret)
		जाओ err_enable;

	ret = soc_dts_enable(id);
	अगर (ret)
		जाओ err_enable;

	वापस 0;
err_enable:
	thermal_zone_device_unरेजिस्टर(dts->tzone);
err_ret:
	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_soc_dts_iosf_add_पढ़ो_only_critical_trip(
	काष्ठा पूर्णांकel_soc_dts_sensors *sensors, पूर्णांक critical_offset)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < SOC_MAX_DTS_SENSORS; ++i) अणु
		क्रम (j = 0; j < sensors->soc_dts[i].trip_count; ++j) अणु
			अगर (!(sensors->soc_dts[i].trip_mask & BIT(j))) अणु
				वापस update_trip_temp(&sensors->soc_dts[i], j,
					sensors->tj_max - critical_offset,
					THERMAL_TRIP_CRITICAL);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_soc_dts_iosf_add_पढ़ो_only_critical_trip);

व्योम पूर्णांकel_soc_dts_iosf_पूर्णांकerrupt_handler(काष्ठा पूर्णांकel_soc_dts_sensors *sensors)
अणु
	u32 sticky_out;
	पूर्णांक status;
	u32 pपंचांगc_out;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sensors->पूर्णांकr_notअगरy_lock, flags);

	status = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_OFFSET_PTMC, &pपंचांगc_out);
	pपंचांगc_out |= SOC_DTS_PTMC_APIC_DEASSERT_BIT;
	status = iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
				SOC_DTS_OFFSET_PTMC, pपंचांगc_out);

	status = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_OFFSET_PTTSS, &sticky_out);
	pr_debug("status %d PTTSS %x\n", status, sticky_out);
	अगर (sticky_out & SOC_DTS_TRIP_MASK) अणु
		पूर्णांक i;
		/* reset sticky bit */
		status = iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
					SOC_DTS_OFFSET_PTTSS, sticky_out);
		spin_unlock_irqrestore(&sensors->पूर्णांकr_notअगरy_lock, flags);

		क्रम (i = 0; i < SOC_MAX_DTS_SENSORS; ++i) अणु
			pr_debug("TZD update for zone %d\n", i);
			thermal_zone_device_update(sensors->soc_dts[i].tzone,
						   THERMAL_EVENT_UNSPECIFIED);
		पूर्ण
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&sensors->पूर्णांकr_notअगरy_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_soc_dts_iosf_पूर्णांकerrupt_handler);

काष्ठा पूर्णांकel_soc_dts_sensors *पूर्णांकel_soc_dts_iosf_init(
	क्रमागत पूर्णांकel_soc_dts_पूर्णांकerrupt_type पूर्णांकr_type, पूर्णांक trip_count,
	पूर्णांक पढ़ो_only_trip_count)
अणु
	काष्ठा पूर्णांकel_soc_dts_sensors *sensors;
	bool notअगरication;
	u32 tj_max;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!iosf_mbi_available())
		वापस ERR_PTR(-ENODEV);

	अगर (!trip_count || पढ़ो_only_trip_count > trip_count)
		वापस ERR_PTR(-EINVAL);

	अगर (get_tj_max(&tj_max))
		वापस ERR_PTR(-EINVAL);

	sensors = kzalloc(माप(*sensors), GFP_KERNEL);
	अगर (!sensors)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&sensors->पूर्णांकr_notअगरy_lock);
	mutex_init(&sensors->dts_update_lock);
	sensors->पूर्णांकr_type = पूर्णांकr_type;
	sensors->tj_max = tj_max;
	अगर (पूर्णांकr_type == INTEL_SOC_DTS_INTERRUPT_NONE)
		notअगरication = false;
	अन्यथा
		notअगरication = true;
	क्रम (i = 0; i < SOC_MAX_DTS_SENSORS; ++i) अणु
		sensors->soc_dts[i].sensors = sensors;
		ret = add_dts_thermal_zone(i, &sensors->soc_dts[i],
					   notअगरication, trip_count,
					   पढ़ो_only_trip_count);
		अगर (ret)
			जाओ err_मुक्त;
	पूर्ण

	क्रम (i = 0; i < SOC_MAX_DTS_SENSORS; ++i) अणु
		ret = update_trip_temp(&sensors->soc_dts[i], 0, 0,
				       THERMAL_TRIP_PASSIVE);
		अगर (ret)
			जाओ err_हटाओ_zone;

		ret = update_trip_temp(&sensors->soc_dts[i], 1, 0,
				       THERMAL_TRIP_PASSIVE);
		अगर (ret)
			जाओ err_हटाओ_zone;
	पूर्ण

	वापस sensors;
err_हटाओ_zone:
	क्रम (i = 0; i < SOC_MAX_DTS_SENSORS; ++i)
		हटाओ_dts_thermal_zone(&sensors->soc_dts[i]);

err_मुक्त:
	kमुक्त(sensors);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_soc_dts_iosf_init);

व्योम पूर्णांकel_soc_dts_iosf_निकास(काष्ठा पूर्णांकel_soc_dts_sensors *sensors)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SOC_MAX_DTS_SENSORS; ++i) अणु
		update_trip_temp(&sensors->soc_dts[i], 0, 0, 0);
		update_trip_temp(&sensors->soc_dts[i], 1, 0, 0);
		हटाओ_dts_thermal_zone(&sensors->soc_dts[i]);
	पूर्ण
	kमुक्त(sensors);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_soc_dts_iosf_निकास);

MODULE_LICENSE("GPL v2");
