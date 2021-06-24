<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright IBM Corp 2019

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sysfs.h>

#समावेश "common.h"

/* OCC status रेजिस्टर */
#घोषणा OCC_STAT_MASTER			BIT(7)
#घोषणा OCC_STAT_ACTIVE			BIT(0)

/* OCC extended status रेजिस्टर */
#घोषणा OCC_EXT_STAT_DVFS_OT		BIT(7)
#घोषणा OCC_EXT_STAT_DVFS_POWER		BIT(6)
#घोषणा OCC_EXT_STAT_MEM_THROTTLE	BIT(5)
#घोषणा OCC_EXT_STAT_QUICK_DROP		BIT(4)

अटल sमाप_प्रकार occ_sysfs_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc;
	पूर्णांक val = 0;
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_poll_response_header *header;
	काष्ठा sensor_device_attribute *sattr = to_sensor_dev_attr(attr);

	rc = occ_update_response(occ);
	अगर (rc)
		वापस rc;

	header = (काष्ठा occ_poll_response_header *)occ->resp.data;

	चयन (sattr->index) अणु
	हाल 0:
		val = !!(header->status & OCC_STAT_MASTER);
		अवरोध;
	हाल 1:
		val = !!(header->status & OCC_STAT_ACTIVE);
		अवरोध;
	हाल 2:
		val = !!(header->ext_status & OCC_EXT_STAT_DVFS_OT);
		अवरोध;
	हाल 3:
		val = !!(header->ext_status & OCC_EXT_STAT_DVFS_POWER);
		अवरोध;
	हाल 4:
		val = !!(header->ext_status & OCC_EXT_STAT_MEM_THROTTLE);
		अवरोध;
	हाल 5:
		val = !!(header->ext_status & OCC_EXT_STAT_QUICK_DROP);
		अवरोध;
	हाल 6:
		val = header->occ_state;
		अवरोध;
	हाल 7:
		अगर (header->status & OCC_STAT_MASTER)
			val = hweight8(header->occs_present);
		अन्यथा
			val = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार occ_error_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा occ *occ = dev_get_drvdata(dev);

	occ_update_response(occ);

	वापस sysfs_emit(buf, "%d\n", occ->error);
पूर्ण

अटल SENSOR_DEVICE_ATTR(occ_master, 0444, occ_sysfs_show, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(occ_active, 0444, occ_sysfs_show, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(occ_dvfs_overtemp, 0444, occ_sysfs_show, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(occ_dvfs_घातer, 0444, occ_sysfs_show, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(occ_mem_throttle, 0444, occ_sysfs_show, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(occ_quick_pwr_drop, 0444, occ_sysfs_show, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(occ_state, 0444, occ_sysfs_show, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(occs_present, 0444, occ_sysfs_show, शून्य, 7);
अटल DEVICE_ATTR_RO(occ_error);

अटल काष्ठा attribute *occ_attributes[] = अणु
	&sensor_dev_attr_occ_master.dev_attr.attr,
	&sensor_dev_attr_occ_active.dev_attr.attr,
	&sensor_dev_attr_occ_dvfs_overtemp.dev_attr.attr,
	&sensor_dev_attr_occ_dvfs_घातer.dev_attr.attr,
	&sensor_dev_attr_occ_mem_throttle.dev_attr.attr,
	&sensor_dev_attr_occ_quick_pwr_drop.dev_attr.attr,
	&sensor_dev_attr_occ_state.dev_attr.attr,
	&sensor_dev_attr_occs_present.dev_attr.attr,
	&dev_attr_occ_error.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group occ_sysfs = अणु
	.attrs = occ_attributes,
पूर्ण;

व्योम occ_sysfs_poll_करोne(काष्ठा occ *occ)
अणु
	स्थिर अक्षर *name;
	काष्ठा occ_poll_response_header *header =
		(काष्ठा occ_poll_response_header *)occ->resp.data;

	/*
	 * On the first poll response, we haven't yet created the sysfs
	 * attributes, so करोn't make any notअगरy calls.
	 */
	अगर (!occ->hwmon)
		जाओ करोne;

	अगर ((header->status & OCC_STAT_MASTER) !=
	    (occ->prev_stat & OCC_STAT_MASTER)) अणु
		name = sensor_dev_attr_occ_master.dev_attr.attr.name;
		sysfs_notअगरy(&occ->bus_dev->kobj, शून्य, name);
	पूर्ण

	अगर ((header->status & OCC_STAT_ACTIVE) !=
	    (occ->prev_stat & OCC_STAT_ACTIVE)) अणु
		name = sensor_dev_attr_occ_active.dev_attr.attr.name;
		sysfs_notअगरy(&occ->bus_dev->kobj, शून्य, name);
	पूर्ण

	अगर ((header->ext_status & OCC_EXT_STAT_DVFS_OT) !=
	    (occ->prev_ext_stat & OCC_EXT_STAT_DVFS_OT)) अणु
		name = sensor_dev_attr_occ_dvfs_overtemp.dev_attr.attr.name;
		sysfs_notअगरy(&occ->bus_dev->kobj, शून्य, name);
	पूर्ण

	अगर ((header->ext_status & OCC_EXT_STAT_DVFS_POWER) !=
	    (occ->prev_ext_stat & OCC_EXT_STAT_DVFS_POWER)) अणु
		name = sensor_dev_attr_occ_dvfs_घातer.dev_attr.attr.name;
		sysfs_notअगरy(&occ->bus_dev->kobj, शून्य, name);
	पूर्ण

	अगर ((header->ext_status & OCC_EXT_STAT_MEM_THROTTLE) !=
	    (occ->prev_ext_stat & OCC_EXT_STAT_MEM_THROTTLE)) अणु
		name = sensor_dev_attr_occ_mem_throttle.dev_attr.attr.name;
		sysfs_notअगरy(&occ->bus_dev->kobj, शून्य, name);
	पूर्ण

	अगर ((header->ext_status & OCC_EXT_STAT_QUICK_DROP) !=
	    (occ->prev_ext_stat & OCC_EXT_STAT_QUICK_DROP)) अणु
		name = sensor_dev_attr_occ_quick_pwr_drop.dev_attr.attr.name;
		sysfs_notअगरy(&occ->bus_dev->kobj, शून्य, name);
	पूर्ण

	अगर ((header->status & OCC_STAT_MASTER) &&
	    header->occs_present != occ->prev_occs_present) अणु
		name = sensor_dev_attr_occs_present.dev_attr.attr.name;
		sysfs_notअगरy(&occ->bus_dev->kobj, शून्य, name);
	पूर्ण

	अगर (occ->error && occ->error != occ->prev_error) अणु
		name = dev_attr_occ_error.attr.name;
		sysfs_notअगरy(&occ->bus_dev->kobj, शून्य, name);
	पूर्ण

	/* no notअगरications क्रम OCC state; करोesn't indicate error condition */

करोne:
	occ->prev_error = occ->error;
	occ->prev_stat = header->status;
	occ->prev_ext_stat = header->ext_status;
	occ->prev_occs_present = header->occs_present;
पूर्ण

पूर्णांक occ_setup_sysfs(काष्ठा occ *occ)
अणु
	वापस sysfs_create_group(&occ->bus_dev->kobj, &occ_sysfs);
पूर्ण

व्योम occ_shutकरोwn(काष्ठा occ *occ)
अणु
	sysfs_हटाओ_group(&occ->bus_dev->kobj, &occ_sysfs);
पूर्ण
EXPORT_SYMBOL_GPL(occ_shutकरोwn);
