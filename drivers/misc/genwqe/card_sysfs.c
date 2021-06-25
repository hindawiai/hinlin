<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IBM Accelerator Family 'GenWQE'
 *
 * (C) Copyright IBM Corp. 2013
 *
 * Author: Frank Haverkamp <haver@linux.vnet.ibm.com>
 * Author: Joerg-Stephan Vogt <jsvogt@de.ibm.com>
 * Author: Michael Jung <mijung@gmx.net>
 * Author: Michael Ruettger <michael@ibmra.de>
 */

/*
 * Sysfs पूर्णांकerfaces क्रम the GenWQE card. There are attributes to query
 * the version of the bitstream as well as some क्रम the driver. For
 * debugging, please also see the debugfs पूर्णांकerfaces of this driver.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/fs.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/device.h>

#समावेश "card_base.h"
#समावेश "card_ddcb.h"

अटल स्थिर अक्षर * स्थिर genwqe_types[] = अणु
	[GENWQE_TYPE_ALTERA_230] = "GenWQE4-230",
	[GENWQE_TYPE_ALTERA_530] = "GenWQE4-530",
	[GENWQE_TYPE_ALTERA_A4]  = "GenWQE5-A4",
	[GENWQE_TYPE_ALTERA_A7]  = "GenWQE5-A7",
पूर्ण;

अटल sमाप_प्रकार status_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);
	स्थिर अक्षर *cs[GENWQE_CARD_STATE_MAX] = अणु "unused", "used", "error" पूर्ण;

	वापस प्र_लिखो(buf, "%s\n", cs[cd->card_state]);
पूर्ण
अटल DEVICE_ATTR_RO(status);

अटल sमाप_प्रकार appid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	अक्षर app_name[5];
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);

	genwqe_पढ़ो_app_id(cd, app_name, माप(app_name));
	वापस प्र_लिखो(buf, "%s\n", app_name);
पूर्ण
अटल DEVICE_ATTR_RO(appid);

अटल sमाप_प्रकार version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	u64 slu_id, app_id;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);

	slu_id = __genwqe_पढ़ोq(cd, IO_SLU_UNITCFG);
	app_id = __genwqe_पढ़ोq(cd, IO_APP_UNITCFG);

	वापस प्र_लिखो(buf, "%016llx.%016llx\n", slu_id, app_id);
पूर्ण
अटल DEVICE_ATTR_RO(version);

अटल sमाप_प्रकार type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	u8 card_type;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);

	card_type = genwqe_card_type(cd);
	वापस प्र_लिखो(buf, "%s\n", (card_type >= ARRAY_SIZE(genwqe_types)) ?
		       "invalid" : genwqe_types[card_type]);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार tempsens_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	u64 tempsens;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);

	tempsens = __genwqe_पढ़ोq(cd, IO_SLU_TEMPERATURE_SENSOR);
	वापस प्र_लिखो(buf, "%016llx\n", tempsens);
पूर्ण
अटल DEVICE_ATTR_RO(tempsens);

अटल sमाप_प्रकार मुक्तrunning_समयr_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	u64 t;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);

	t = __genwqe_पढ़ोq(cd, IO_SLC_FREE_RUNNING_TIMER);
	वापस प्र_लिखो(buf, "%016llx\n", t);
पूर्ण
अटल DEVICE_ATTR_RO(मुक्तrunning_समयr);

अटल sमाप_प्रकार queue_working_समय_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	u64 t;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);

	t = __genwqe_पढ़ोq(cd, IO_SLC_QUEUE_WTIME);
	वापस प्र_लिखो(buf, "%016llx\n", t);
पूर्ण
अटल DEVICE_ATTR_RO(queue_working_समय);

अटल sमाप_प्रकार base_घड़ी_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	u64 base_घड़ी;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);

	base_घड़ी = genwqe_base_घड़ी_frequency(cd);
	वापस प्र_लिखो(buf, "%lld\n", base_घड़ी);
पूर्ण
अटल DEVICE_ATTR_RO(base_घड़ी);

/*
 * curr_bitstream_show() - Show the current bitstream id
 *
 * There is a bug in some old versions of the CPLD which selects the
 * bitstream, which causes the IO_SLU_BITSTREAM रेजिस्टर to report
 * unreliable data in very rare हालs. This makes this sysfs
 * unreliable up to the poपूर्णांक were a new CPLD version is being used.
 *
 * Unक्रमtunately there is no स्वतःmatic way yet to query the CPLD
 * version, such that you need to manually ensure via programming
 * tools that you have a recent version of the CPLD software.
 *
 * The proposed circumvention is to use a special recovery bitstream
 * on the backup partition (0) to identअगरy problems जबतक loading the
 * image.
 */
अटल sमाप_प्रकार curr_bitstream_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक curr_bitstream;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);

	curr_bitstream = __genwqe_पढ़ोq(cd, IO_SLU_BITSTREAM) & 0x1;
	वापस प्र_लिखो(buf, "%d\n", curr_bitstream);
पूर्ण
अटल DEVICE_ATTR_RO(curr_bitstream);

/*
 * next_bitstream_show() - Show the next activated bitstream
 *
 * IO_SLC_CFGREG_SOFTRESET: This रेजिस्टर can only be accessed by the PF.
 */
अटल sमाप_प्रकार next_bitstream_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक next_bitstream;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);

	चयन ((cd->softreset & 0xc) >> 2) अणु
	हाल 0x2:
		next_bitstream =  0;
		अवरोध;
	हाल 0x3:
		next_bitstream =  1;
		अवरोध;
	शेष:
		next_bitstream = -1;
		अवरोध;		/* error */
	पूर्ण
	वापस प्र_लिखो(buf, "%d\n", next_bitstream);
पूर्ण

अटल sमाप_प्रकार next_bitstream_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक partition;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);

	अगर (kstrtoपूर्णांक(buf, 0, &partition) < 0)
		वापस -EINVAL;

	चयन (partition) अणु
	हाल 0x0:
		cd->softreset = 0x78;
		अवरोध;
	हाल 0x1:
		cd->softreset = 0x7c;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	__genwqe_ग_लिखोq(cd, IO_SLC_CFGREG_SOFTRESET, cd->softreset);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(next_bitstream);

अटल sमाप_प्रकार reload_bitstream_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक reload;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);

	अगर (kstrtoपूर्णांक(buf, 0, &reload) < 0)
		वापस -EINVAL;

	अगर (reload == 0x1) अणु
		अगर (cd->card_state == GENWQE_CARD_UNUSED ||
		    cd->card_state == GENWQE_CARD_USED)
			cd->card_state = GENWQE_CARD_RELOAD_BITSTREAM;
		अन्यथा
			वापस -EIO;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(reload_bitstream);

/*
 * Create device_attribute काष्ठाures / params: name, mode, show, store
 * additional flag अगर valid in VF
 */
अटल काष्ठा attribute *genwqe_attributes[] = अणु
	&dev_attr_tempsens.attr,
	&dev_attr_next_bitstream.attr,
	&dev_attr_curr_bitstream.attr,
	&dev_attr_base_घड़ी.attr,
	&dev_attr_type.attr,
	&dev_attr_version.attr,
	&dev_attr_appid.attr,
	&dev_attr_status.attr,
	&dev_attr_मुक्तrunning_समयr.attr,
	&dev_attr_queue_working_समय.attr,
	&dev_attr_reload_bitstream.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *genwqe_normal_attributes[] = अणु
	&dev_attr_type.attr,
	&dev_attr_version.attr,
	&dev_attr_appid.attr,
	&dev_attr_status.attr,
	&dev_attr_मुक्तrunning_समयr.attr,
	&dev_attr_queue_working_समय.attr,
	शून्य,
पूर्ण;

/*
 * genwqe_is_visible() - Determine अगर sysfs attribute should be visible or not
 *
 * VFs have restricted mmio capabilities, so not all sysfs entries
 * are allowed in VFs.
 */
अटल umode_t genwqe_is_visible(काष्ठा kobject *kobj,
				 काष्ठा attribute *attr, पूर्णांक n)
अणु
	अचिन्हित पूर्णांक j;
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा genwqe_dev *cd = dev_get_drvdata(dev);
	umode_t mode = attr->mode;

	अगर (genwqe_is_privileged(cd))
		वापस mode;

	क्रम (j = 0; genwqe_normal_attributes[j] != शून्य;  j++)
		अगर (genwqe_normal_attributes[j] == attr)
			वापस mode;

	वापस 0;
पूर्ण

अटल काष्ठा attribute_group genwqe_attribute_group = अणु
	.is_visible = genwqe_is_visible,
	.attrs      = genwqe_attributes,
पूर्ण;

स्थिर काष्ठा attribute_group *genwqe_attribute_groups[] = अणु
	&genwqe_attribute_group,
	शून्य,
पूर्ण;
