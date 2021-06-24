<शैली गुरु>
/*
 * edac_mc kernel module
 * (C) 2005-2007 Linux Networx (http://lnxi.com)
 *
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written Doug Thompson <norsk5@xmission.com> www.softwarebiपंचांगaker.com
 *
 * (c) 2012-2013 - Mauro Carvalho Chehab
 *	The entire API were re-written, and ported to use काष्ठा device
 *
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/edac.h>
#समावेश <linux/bug.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/uaccess.h>

#समावेश "edac_mc.h"
#समावेश "edac_module.h"

/* MC EDAC Controls, setable by module parameter, and sysfs */
अटल पूर्णांक edac_mc_log_ue = 1;
अटल पूर्णांक edac_mc_log_ce = 1;
अटल पूर्णांक edac_mc_panic_on_ue;
अटल अचिन्हित पूर्णांक edac_mc_poll_msec = 1000;

/* Getter functions क्रम above */
पूर्णांक edac_mc_get_log_ue(व्योम)
अणु
	वापस edac_mc_log_ue;
पूर्ण

पूर्णांक edac_mc_get_log_ce(व्योम)
अणु
	वापस edac_mc_log_ce;
पूर्ण

पूर्णांक edac_mc_get_panic_on_ue(व्योम)
अणु
	वापस edac_mc_panic_on_ue;
पूर्ण

/* this is temporary */
अचिन्हित पूर्णांक edac_mc_get_poll_msec(व्योम)
अणु
	वापस edac_mc_poll_msec;
पूर्ण

अटल पूर्णांक edac_set_poll_msec(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!val)
		वापस -EINVAL;

	ret = kstrtouपूर्णांक(val, 0, &i);
	अगर (ret)
		वापस ret;

	अगर (i < 1000)
		वापस -EINVAL;

	*((अचिन्हित पूर्णांक *)kp->arg) = i;

	/* notअगरy edac_mc engine to reset the poll period */
	edac_mc_reset_delay_period(i);

	वापस 0;
पूर्ण

/* Parameter declarations क्रम above */
module_param(edac_mc_panic_on_ue, पूर्णांक, 0644);
MODULE_PARM_DESC(edac_mc_panic_on_ue, "Panic on uncorrected error: 0=off 1=on");
module_param(edac_mc_log_ue, पूर्णांक, 0644);
MODULE_PARM_DESC(edac_mc_log_ue,
		 "Log uncorrectable error to console: 0=off 1=on");
module_param(edac_mc_log_ce, पूर्णांक, 0644);
MODULE_PARM_DESC(edac_mc_log_ce,
		 "Log correctable error to console: 0=off 1=on");
module_param_call(edac_mc_poll_msec, edac_set_poll_msec, param_get_uपूर्णांक,
		  &edac_mc_poll_msec, 0644);
MODULE_PARM_DESC(edac_mc_poll_msec, "Polling period in milliseconds");

अटल काष्ठा device *mci_pdev;

/*
 * various स्थिरants क्रम Memory Controllers
 */
अटल स्थिर अक्षर * स्थिर dev_types[] = अणु
	[DEV_UNKNOWN] = "Unknown",
	[DEV_X1] = "x1",
	[DEV_X2] = "x2",
	[DEV_X4] = "x4",
	[DEV_X8] = "x8",
	[DEV_X16] = "x16",
	[DEV_X32] = "x32",
	[DEV_X64] = "x64"
पूर्ण;

अटल स्थिर अक्षर * स्थिर edac_caps[] = अणु
	[EDAC_UNKNOWN] = "Unknown",
	[EDAC_NONE] = "None",
	[EDAC_RESERVED] = "Reserved",
	[EDAC_PARITY] = "PARITY",
	[EDAC_EC] = "EC",
	[EDAC_SECDED] = "SECDED",
	[EDAC_S2ECD2ED] = "S2ECD2ED",
	[EDAC_S4ECD4ED] = "S4ECD4ED",
	[EDAC_S8ECD8ED] = "S8ECD8ED",
	[EDAC_S16ECD16ED] = "S16ECD16ED"
पूर्ण;

#अगर_घोषित CONFIG_EDAC_LEGACY_SYSFS
/*
 * EDAC sysfs CSROW data काष्ठाures and methods
 */

#घोषणा to_csrow(k) container_of(k, काष्ठा csrow_info, dev)

/*
 * We need it to aव्योम namespace conflicts between the legacy API
 * and the per-dimm/per-rank one
 */
#घोषणा DEVICE_ATTR_LEGACY(_name, _mode, _show, _store) \
	अटल काष्ठा device_attribute dev_attr_legacy_##_name = __ATTR(_name, _mode, _show, _store)

काष्ठा dev_ch_attribute अणु
	काष्ठा device_attribute attr;
	अचिन्हित पूर्णांक channel;
पूर्ण;

#घोषणा DEVICE_CHANNEL(_name, _mode, _show, _store, _var) \
	अटल काष्ठा dev_ch_attribute dev_attr_legacy_##_name = \
		अणु __ATTR(_name, _mode, _show, _store), (_var) पूर्ण

#घोषणा to_channel(k) (container_of(k, काष्ठा dev_ch_attribute, attr)->channel)

/* Set of more शेष csrow<id> attribute show/store functions */
अटल sमाप_प्रकार csrow_ue_count_show(काष्ठा device *dev,
				   काष्ठा device_attribute *mattr, अक्षर *data)
अणु
	काष्ठा csrow_info *csrow = to_csrow(dev);

	वापस प्र_लिखो(data, "%u\n", csrow->ue_count);
पूर्ण

अटल sमाप_प्रकार csrow_ce_count_show(काष्ठा device *dev,
				   काष्ठा device_attribute *mattr, अक्षर *data)
अणु
	काष्ठा csrow_info *csrow = to_csrow(dev);

	वापस प्र_लिखो(data, "%u\n", csrow->ce_count);
पूर्ण

अटल sमाप_प्रकार csrow_size_show(काष्ठा device *dev,
			       काष्ठा device_attribute *mattr, अक्षर *data)
अणु
	काष्ठा csrow_info *csrow = to_csrow(dev);
	पूर्णांक i;
	u32 nr_pages = 0;

	क्रम (i = 0; i < csrow->nr_channels; i++)
		nr_pages += csrow->channels[i]->dimm->nr_pages;
	वापस प्र_लिखो(data, "%u\n", PAGES_TO_MiB(nr_pages));
पूर्ण

अटल sमाप_प्रकार csrow_mem_type_show(काष्ठा device *dev,
				   काष्ठा device_attribute *mattr, अक्षर *data)
अणु
	काष्ठा csrow_info *csrow = to_csrow(dev);

	वापस प्र_लिखो(data, "%s\n", edac_mem_types[csrow->channels[0]->dimm->mtype]);
पूर्ण

अटल sमाप_प्रकार csrow_dev_type_show(काष्ठा device *dev,
				   काष्ठा device_attribute *mattr, अक्षर *data)
अणु
	काष्ठा csrow_info *csrow = to_csrow(dev);

	वापस प्र_लिखो(data, "%s\n", dev_types[csrow->channels[0]->dimm->dtype]);
पूर्ण

अटल sमाप_प्रकार csrow_edac_mode_show(काष्ठा device *dev,
				    काष्ठा device_attribute *mattr,
				    अक्षर *data)
अणु
	काष्ठा csrow_info *csrow = to_csrow(dev);

	वापस प्र_लिखो(data, "%s\n", edac_caps[csrow->channels[0]->dimm->edac_mode]);
पूर्ण

/* show/store functions क्रम DIMM Label attributes */
अटल sमाप_प्रकार channel_dimm_label_show(काष्ठा device *dev,
				       काष्ठा device_attribute *mattr,
				       अक्षर *data)
अणु
	काष्ठा csrow_info *csrow = to_csrow(dev);
	अचिन्हित पूर्णांक chan = to_channel(mattr);
	काष्ठा rank_info *rank = csrow->channels[chan];

	/* अगर field has not been initialized, there is nothing to send */
	अगर (!rank->dimm->label[0])
		वापस 0;

	वापस snम_लिखो(data, माप(rank->dimm->label) + 1, "%s\n",
			rank->dimm->label);
पूर्ण

अटल sमाप_प्रकार channel_dimm_label_store(काष्ठा device *dev,
					काष्ठा device_attribute *mattr,
					स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा csrow_info *csrow = to_csrow(dev);
	अचिन्हित पूर्णांक chan = to_channel(mattr);
	काष्ठा rank_info *rank = csrow->channels[chan];
	माप_प्रकार copy_count = count;

	अगर (count == 0)
		वापस -EINVAL;

	अगर (data[count - 1] == '\0' || data[count - 1] == '\n')
		copy_count -= 1;

	अगर (copy_count == 0 || copy_count >= माप(rank->dimm->label))
		वापस -EINVAL;

	म_नकलन(rank->dimm->label, data, copy_count);
	rank->dimm->label[copy_count] = '\0';

	वापस count;
पूर्ण

/* show function क्रम dynamic chX_ce_count attribute */
अटल sमाप_प्रकार channel_ce_count_show(काष्ठा device *dev,
				     काष्ठा device_attribute *mattr, अक्षर *data)
अणु
	काष्ठा csrow_info *csrow = to_csrow(dev);
	अचिन्हित पूर्णांक chan = to_channel(mattr);
	काष्ठा rank_info *rank = csrow->channels[chan];

	वापस प्र_लिखो(data, "%u\n", rank->ce_count);
पूर्ण

/* cwrow<id>/attribute files */
DEVICE_ATTR_LEGACY(size_mb, S_IRUGO, csrow_size_show, शून्य);
DEVICE_ATTR_LEGACY(dev_type, S_IRUGO, csrow_dev_type_show, शून्य);
DEVICE_ATTR_LEGACY(mem_type, S_IRUGO, csrow_mem_type_show, शून्य);
DEVICE_ATTR_LEGACY(edac_mode, S_IRUGO, csrow_edac_mode_show, शून्य);
DEVICE_ATTR_LEGACY(ue_count, S_IRUGO, csrow_ue_count_show, शून्य);
DEVICE_ATTR_LEGACY(ce_count, S_IRUGO, csrow_ce_count_show, शून्य);

/* शेष attributes of the CSROW<id> object */
अटल काष्ठा attribute *csrow_attrs[] = अणु
	&dev_attr_legacy_dev_type.attr,
	&dev_attr_legacy_mem_type.attr,
	&dev_attr_legacy_edac_mode.attr,
	&dev_attr_legacy_size_mb.attr,
	&dev_attr_legacy_ue_count.attr,
	&dev_attr_legacy_ce_count.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group csrow_attr_grp = अणु
	.attrs	= csrow_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *csrow_attr_groups[] = अणु
	&csrow_attr_grp,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा device_type csrow_attr_type = अणु
	.groups		= csrow_attr_groups,
पूर्ण;

/*
 * possible dynamic channel DIMM Label attribute files
 *
 */
DEVICE_CHANNEL(ch0_dimm_label, S_IRUGO | S_IWUSR,
	channel_dimm_label_show, channel_dimm_label_store, 0);
DEVICE_CHANNEL(ch1_dimm_label, S_IRUGO | S_IWUSR,
	channel_dimm_label_show, channel_dimm_label_store, 1);
DEVICE_CHANNEL(ch2_dimm_label, S_IRUGO | S_IWUSR,
	channel_dimm_label_show, channel_dimm_label_store, 2);
DEVICE_CHANNEL(ch3_dimm_label, S_IRUGO | S_IWUSR,
	channel_dimm_label_show, channel_dimm_label_store, 3);
DEVICE_CHANNEL(ch4_dimm_label, S_IRUGO | S_IWUSR,
	channel_dimm_label_show, channel_dimm_label_store, 4);
DEVICE_CHANNEL(ch5_dimm_label, S_IRUGO | S_IWUSR,
	channel_dimm_label_show, channel_dimm_label_store, 5);
DEVICE_CHANNEL(ch6_dimm_label, S_IRUGO | S_IWUSR,
	channel_dimm_label_show, channel_dimm_label_store, 6);
DEVICE_CHANNEL(ch7_dimm_label, S_IRUGO | S_IWUSR,
	channel_dimm_label_show, channel_dimm_label_store, 7);

/* Total possible dynamic DIMM Label attribute file table */
अटल काष्ठा attribute *dynamic_csrow_dimm_attr[] = अणु
	&dev_attr_legacy_ch0_dimm_label.attr.attr,
	&dev_attr_legacy_ch1_dimm_label.attr.attr,
	&dev_attr_legacy_ch2_dimm_label.attr.attr,
	&dev_attr_legacy_ch3_dimm_label.attr.attr,
	&dev_attr_legacy_ch4_dimm_label.attr.attr,
	&dev_attr_legacy_ch5_dimm_label.attr.attr,
	&dev_attr_legacy_ch6_dimm_label.attr.attr,
	&dev_attr_legacy_ch7_dimm_label.attr.attr,
	शून्य
पूर्ण;

/* possible dynamic channel ce_count attribute files */
DEVICE_CHANNEL(ch0_ce_count, S_IRUGO,
		   channel_ce_count_show, शून्य, 0);
DEVICE_CHANNEL(ch1_ce_count, S_IRUGO,
		   channel_ce_count_show, शून्य, 1);
DEVICE_CHANNEL(ch2_ce_count, S_IRUGO,
		   channel_ce_count_show, शून्य, 2);
DEVICE_CHANNEL(ch3_ce_count, S_IRUGO,
		   channel_ce_count_show, शून्य, 3);
DEVICE_CHANNEL(ch4_ce_count, S_IRUGO,
		   channel_ce_count_show, शून्य, 4);
DEVICE_CHANNEL(ch5_ce_count, S_IRUGO,
		   channel_ce_count_show, शून्य, 5);
DEVICE_CHANNEL(ch6_ce_count, S_IRUGO,
		   channel_ce_count_show, शून्य, 6);
DEVICE_CHANNEL(ch7_ce_count, S_IRUGO,
		   channel_ce_count_show, शून्य, 7);

/* Total possible dynamic ce_count attribute file table */
अटल काष्ठा attribute *dynamic_csrow_ce_count_attr[] = अणु
	&dev_attr_legacy_ch0_ce_count.attr.attr,
	&dev_attr_legacy_ch1_ce_count.attr.attr,
	&dev_attr_legacy_ch2_ce_count.attr.attr,
	&dev_attr_legacy_ch3_ce_count.attr.attr,
	&dev_attr_legacy_ch4_ce_count.attr.attr,
	&dev_attr_legacy_ch5_ce_count.attr.attr,
	&dev_attr_legacy_ch6_ce_count.attr.attr,
	&dev_attr_legacy_ch7_ce_count.attr.attr,
	शून्य
पूर्ण;

अटल umode_t csrow_dev_is_visible(काष्ठा kobject *kobj,
				    काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा csrow_info *csrow = container_of(dev, काष्ठा csrow_info, dev);

	अगर (idx >= csrow->nr_channels)
		वापस 0;

	अगर (idx >= ARRAY_SIZE(dynamic_csrow_ce_count_attr) - 1) अणु
		WARN_ONCE(1, "idx: %d\n", idx);
		वापस 0;
	पूर्ण

	/* Only expose populated DIMMs */
	अगर (!csrow->channels[idx]->dimm->nr_pages)
		वापस 0;

	वापस attr->mode;
पूर्ण


अटल स्थिर काष्ठा attribute_group csrow_dev_dimm_group = अणु
	.attrs = dynamic_csrow_dimm_attr,
	.is_visible = csrow_dev_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group csrow_dev_ce_count_group = अणु
	.attrs = dynamic_csrow_ce_count_attr,
	.is_visible = csrow_dev_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *csrow_dev_groups[] = अणु
	&csrow_dev_dimm_group,
	&csrow_dev_ce_count_group,
	शून्य
पूर्ण;

अटल व्योम csrow_release(काष्ठा device *dev)
अणु
	/*
	 * Nothing to करो, just unरेजिस्टर sysfs here. The mci
	 * device owns the data and will also release it.
	 */
पूर्ण

अटल अंतरभूत पूर्णांक nr_pages_per_csrow(काष्ठा csrow_info *csrow)
अणु
	पूर्णांक chan, nr_pages = 0;

	क्रम (chan = 0; chan < csrow->nr_channels; chan++)
		nr_pages += csrow->channels[chan]->dimm->nr_pages;

	वापस nr_pages;
पूर्ण

/* Create a CSROW object under specअगरed edac_mc_device */
अटल पूर्णांक edac_create_csrow_object(काष्ठा mem_ctl_info *mci,
				    काष्ठा csrow_info *csrow, पूर्णांक index)
अणु
	पूर्णांक err;

	csrow->dev.type = &csrow_attr_type;
	csrow->dev.groups = csrow_dev_groups;
	csrow->dev.release = csrow_release;
	device_initialize(&csrow->dev);
	csrow->dev.parent = &mci->dev;
	csrow->mci = mci;
	dev_set_name(&csrow->dev, "csrow%d", index);
	dev_set_drvdata(&csrow->dev, csrow);

	err = device_add(&csrow->dev);
	अगर (err) अणु
		edac_dbg(1, "failure: create device %s\n", dev_name(&csrow->dev));
		put_device(&csrow->dev);
		वापस err;
	पूर्ण

	edac_dbg(0, "device %s created\n", dev_name(&csrow->dev));

	वापस 0;
पूर्ण

/* Create a CSROW object under specअगरed edac_mc_device */
अटल पूर्णांक edac_create_csrow_objects(काष्ठा mem_ctl_info *mci)
अणु
	पूर्णांक err, i;
	काष्ठा csrow_info *csrow;

	क्रम (i = 0; i < mci->nr_csrows; i++) अणु
		csrow = mci->csrows[i];
		अगर (!nr_pages_per_csrow(csrow))
			जारी;
		err = edac_create_csrow_object(mci, mci->csrows[i], i);
		अगर (err < 0)
			जाओ error;
	पूर्ण
	वापस 0;

error:
	क्रम (--i; i >= 0; i--) अणु
		अगर (device_is_रेजिस्टरed(&mci->csrows[i]->dev))
			device_unरेजिस्टर(&mci->csrows[i]->dev);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम edac_delete_csrow_objects(काष्ठा mem_ctl_info *mci)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mci->nr_csrows; i++) अणु
		अगर (device_is_रेजिस्टरed(&mci->csrows[i]->dev))
			device_unरेजिस्टर(&mci->csrows[i]->dev);
	पूर्ण
पूर्ण

#पूर्ण_अगर

/*
 * Per-dimm (or per-rank) devices
 */

#घोषणा to_dimm(k) container_of(k, काष्ठा dimm_info, dev)

/* show/store functions क्रम DIMM Label attributes */
अटल sमाप_प्रकार dimmdev_location_show(काष्ठा device *dev,
				     काष्ठा device_attribute *mattr, अक्षर *data)
अणु
	काष्ठा dimm_info *dimm = to_dimm(dev);
	sमाप_प्रकार count;

	count = edac_dimm_info_location(dimm, data, PAGE_SIZE);
	count += scnम_लिखो(data + count, PAGE_SIZE - count, "\n");

	वापस count;
पूर्ण

अटल sमाप_प्रकार dimmdev_label_show(काष्ठा device *dev,
				  काष्ठा device_attribute *mattr, अक्षर *data)
अणु
	काष्ठा dimm_info *dimm = to_dimm(dev);

	/* अगर field has not been initialized, there is nothing to send */
	अगर (!dimm->label[0])
		वापस 0;

	वापस snम_लिखो(data, माप(dimm->label) + 1, "%s\n", dimm->label);
पूर्ण

अटल sमाप_प्रकार dimmdev_label_store(काष्ठा device *dev,
				   काष्ठा device_attribute *mattr,
				   स्थिर अक्षर *data,
				   माप_प्रकार count)
अणु
	काष्ठा dimm_info *dimm = to_dimm(dev);
	माप_प्रकार copy_count = count;

	अगर (count == 0)
		वापस -EINVAL;

	अगर (data[count - 1] == '\0' || data[count - 1] == '\n')
		copy_count -= 1;

	अगर (copy_count == 0 || copy_count >= माप(dimm->label))
		वापस -EINVAL;

	म_नकलन(dimm->label, data, copy_count);
	dimm->label[copy_count] = '\0';

	वापस count;
पूर्ण

अटल sमाप_प्रकार dimmdev_size_show(काष्ठा device *dev,
				 काष्ठा device_attribute *mattr, अक्षर *data)
अणु
	काष्ठा dimm_info *dimm = to_dimm(dev);

	वापस प्र_लिखो(data, "%u\n", PAGES_TO_MiB(dimm->nr_pages));
पूर्ण

अटल sमाप_प्रकार dimmdev_mem_type_show(काष्ठा device *dev,
				     काष्ठा device_attribute *mattr, अक्षर *data)
अणु
	काष्ठा dimm_info *dimm = to_dimm(dev);

	वापस प्र_लिखो(data, "%s\n", edac_mem_types[dimm->mtype]);
पूर्ण

अटल sमाप_प्रकार dimmdev_dev_type_show(काष्ठा device *dev,
				     काष्ठा device_attribute *mattr, अक्षर *data)
अणु
	काष्ठा dimm_info *dimm = to_dimm(dev);

	वापस प्र_लिखो(data, "%s\n", dev_types[dimm->dtype]);
पूर्ण

अटल sमाप_प्रकार dimmdev_edac_mode_show(काष्ठा device *dev,
				      काष्ठा device_attribute *mattr,
				      अक्षर *data)
अणु
	काष्ठा dimm_info *dimm = to_dimm(dev);

	वापस प्र_लिखो(data, "%s\n", edac_caps[dimm->edac_mode]);
पूर्ण

अटल sमाप_प्रकार dimmdev_ce_count_show(काष्ठा device *dev,
				      काष्ठा device_attribute *mattr,
				      अक्षर *data)
अणु
	काष्ठा dimm_info *dimm = to_dimm(dev);

	वापस प्र_लिखो(data, "%u\n", dimm->ce_count);
पूर्ण

अटल sमाप_प्रकार dimmdev_ue_count_show(काष्ठा device *dev,
				      काष्ठा device_attribute *mattr,
				      अक्षर *data)
अणु
	काष्ठा dimm_info *dimm = to_dimm(dev);

	वापस प्र_लिखो(data, "%u\n", dimm->ue_count);
पूर्ण

/* dimm/rank attribute files */
अटल DEVICE_ATTR(dimm_label, S_IRUGO | S_IWUSR,
		   dimmdev_label_show, dimmdev_label_store);
अटल DEVICE_ATTR(dimm_location, S_IRUGO, dimmdev_location_show, शून्य);
अटल DEVICE_ATTR(size, S_IRUGO, dimmdev_size_show, शून्य);
अटल DEVICE_ATTR(dimm_mem_type, S_IRUGO, dimmdev_mem_type_show, शून्य);
अटल DEVICE_ATTR(dimm_dev_type, S_IRUGO, dimmdev_dev_type_show, शून्य);
अटल DEVICE_ATTR(dimm_edac_mode, S_IRUGO, dimmdev_edac_mode_show, शून्य);
अटल DEVICE_ATTR(dimm_ce_count, S_IRUGO, dimmdev_ce_count_show, शून्य);
अटल DEVICE_ATTR(dimm_ue_count, S_IRUGO, dimmdev_ue_count_show, शून्य);

/* attributes of the dimm<id>/rank<id> object */
अटल काष्ठा attribute *dimm_attrs[] = अणु
	&dev_attr_dimm_label.attr,
	&dev_attr_dimm_location.attr,
	&dev_attr_size.attr,
	&dev_attr_dimm_mem_type.attr,
	&dev_attr_dimm_dev_type.attr,
	&dev_attr_dimm_edac_mode.attr,
	&dev_attr_dimm_ce_count.attr,
	&dev_attr_dimm_ue_count.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dimm_attr_grp = अणु
	.attrs	= dimm_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *dimm_attr_groups[] = अणु
	&dimm_attr_grp,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा device_type dimm_attr_type = अणु
	.groups		= dimm_attr_groups,
पूर्ण;

अटल व्योम dimm_release(काष्ठा device *dev)
अणु
	/*
	 * Nothing to करो, just unरेजिस्टर sysfs here. The mci
	 * device owns the data and will also release it.
	 */
पूर्ण

/* Create a DIMM object under specअगरed memory controller device */
अटल पूर्णांक edac_create_dimm_object(काष्ठा mem_ctl_info *mci,
				   काष्ठा dimm_info *dimm)
अणु
	पूर्णांक err;
	dimm->mci = mci;

	dimm->dev.type = &dimm_attr_type;
	dimm->dev.release = dimm_release;
	device_initialize(&dimm->dev);

	dimm->dev.parent = &mci->dev;
	अगर (mci->csbased)
		dev_set_name(&dimm->dev, "rank%d", dimm->idx);
	अन्यथा
		dev_set_name(&dimm->dev, "dimm%d", dimm->idx);
	dev_set_drvdata(&dimm->dev, dimm);
	pm_runसमय_क्रमbid(&mci->dev);

	err = device_add(&dimm->dev);
	अगर (err) अणु
		edac_dbg(1, "failure: create device %s\n", dev_name(&dimm->dev));
		put_device(&dimm->dev);
		वापस err;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_EDAC_DEBUG)) अणु
		अक्षर location[80];

		edac_dimm_info_location(dimm, location, माप(location));
		edac_dbg(0, "device %s created at location %s\n",
			dev_name(&dimm->dev), location);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Memory controller device
 */

#घोषणा to_mci(k) container_of(k, काष्ठा mem_ctl_info, dev)

अटल sमाप_प्रकार mci_reset_counters_store(काष्ठा device *dev,
					काष्ठा device_attribute *mattr,
					स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	काष्ठा dimm_info *dimm;
	पूर्णांक row, chan;

	mci->ue_mc = 0;
	mci->ce_mc = 0;
	mci->ue_noinfo_count = 0;
	mci->ce_noinfo_count = 0;

	क्रम (row = 0; row < mci->nr_csrows; row++) अणु
		काष्ठा csrow_info *ri = mci->csrows[row];

		ri->ue_count = 0;
		ri->ce_count = 0;

		क्रम (chan = 0; chan < ri->nr_channels; chan++)
			ri->channels[chan]->ce_count = 0;
	पूर्ण

	mci_क्रम_each_dimm(mci, dimm) अणु
		dimm->ue_count = 0;
		dimm->ce_count = 0;
	पूर्ण

	mci->start_समय = jअगरfies;
	वापस count;
पूर्ण

/* Memory scrubbing पूर्णांकerface:
 *
 * A MC driver can limit the scrubbing bandwidth based on the CPU type.
 * Thereक्रमe, ->set_sdram_scrub_rate should be made to वापस the actual
 * bandwidth that is accepted or 0 when scrubbing is to be disabled.
 *
 * Negative value still means that an error has occurred जबतक setting
 * the scrub rate.
 */
अटल sमाप_प्रकार mci_sdram_scrub_rate_store(काष्ठा device *dev,
					  काष्ठा device_attribute *mattr,
					  स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	अचिन्हित दीर्घ bandwidth = 0;
	पूर्णांक new_bw = 0;

	अगर (kम_से_अदीर्घ(data, 10, &bandwidth) < 0)
		वापस -EINVAL;

	new_bw = mci->set_sdram_scrub_rate(mci, bandwidth);
	अगर (new_bw < 0) अणु
		edac_prपूर्णांकk(KERN_WARNING, EDAC_MC,
			    "Error setting scrub rate to: %lu\n", bandwidth);
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

/*
 * ->get_sdram_scrub_rate() वापस value semantics same as above.
 */
अटल sमाप_प्रकार mci_sdram_scrub_rate_show(काष्ठा device *dev,
					 काष्ठा device_attribute *mattr,
					 अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	पूर्णांक bandwidth = 0;

	bandwidth = mci->get_sdram_scrub_rate(mci);
	अगर (bandwidth < 0) अणु
		edac_prपूर्णांकk(KERN_DEBUG, EDAC_MC, "Error reading scrub rate\n");
		वापस bandwidth;
	पूर्ण

	वापस प्र_लिखो(data, "%d\n", bandwidth);
पूर्ण

/* शेष attribute files क्रम the MCI object */
अटल sमाप_प्रकार mci_ue_count_show(काष्ठा device *dev,
				 काष्ठा device_attribute *mattr,
				 अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);

	वापस प्र_लिखो(data, "%d\n", mci->ue_mc);
पूर्ण

अटल sमाप_प्रकार mci_ce_count_show(काष्ठा device *dev,
				 काष्ठा device_attribute *mattr,
				 अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);

	वापस प्र_लिखो(data, "%d\n", mci->ce_mc);
पूर्ण

अटल sमाप_प्रकार mci_ce_noinfo_show(काष्ठा device *dev,
				  काष्ठा device_attribute *mattr,
				  अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);

	वापस प्र_लिखो(data, "%d\n", mci->ce_noinfo_count);
पूर्ण

अटल sमाप_प्रकार mci_ue_noinfo_show(काष्ठा device *dev,
				  काष्ठा device_attribute *mattr,
				  अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);

	वापस प्र_लिखो(data, "%d\n", mci->ue_noinfo_count);
पूर्ण

अटल sमाप_प्रकार mci_seconds_show(काष्ठा device *dev,
				काष्ठा device_attribute *mattr,
				अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);

	वापस प्र_लिखो(data, "%ld\n", (jअगरfies - mci->start_समय) / HZ);
पूर्ण

अटल sमाप_प्रकार mci_ctl_name_show(काष्ठा device *dev,
				 काष्ठा device_attribute *mattr,
				 अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);

	वापस प्र_लिखो(data, "%s\n", mci->ctl_name);
पूर्ण

अटल sमाप_प्रकार mci_size_mb_show(काष्ठा device *dev,
				काष्ठा device_attribute *mattr,
				अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	पूर्णांक total_pages = 0, csrow_idx, j;

	क्रम (csrow_idx = 0; csrow_idx < mci->nr_csrows; csrow_idx++) अणु
		काष्ठा csrow_info *csrow = mci->csrows[csrow_idx];

		क्रम (j = 0; j < csrow->nr_channels; j++) अणु
			काष्ठा dimm_info *dimm = csrow->channels[j]->dimm;

			total_pages += dimm->nr_pages;
		पूर्ण
	पूर्ण

	वापस प्र_लिखो(data, "%u\n", PAGES_TO_MiB(total_pages));
पूर्ण

अटल sमाप_प्रकार mci_max_location_show(काष्ठा device *dev,
				     काष्ठा device_attribute *mattr,
				     अक्षर *data)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	पूर्णांक len = PAGE_SIZE;
	अक्षर *p = data;
	पूर्णांक i, n;

	क्रम (i = 0; i < mci->n_layers; i++) अणु
		n = scnम_लिखो(p, len, "%s %d ",
			      edac_layer_name[mci->layers[i].type],
			      mci->layers[i].size - 1);
		len -= n;
		अगर (len <= 0)
			जाओ out;

		p += n;
	पूर्ण

	p += scnम_लिखो(p, len, "\n");
out:
	वापस p - data;
पूर्ण

/* शेष Control file */
अटल DEVICE_ATTR(reset_counters, S_IWUSR, शून्य, mci_reset_counters_store);

/* शेष Attribute files */
अटल DEVICE_ATTR(mc_name, S_IRUGO, mci_ctl_name_show, शून्य);
अटल DEVICE_ATTR(size_mb, S_IRUGO, mci_size_mb_show, शून्य);
अटल DEVICE_ATTR(seconds_since_reset, S_IRUGO, mci_seconds_show, शून्य);
अटल DEVICE_ATTR(ue_noinfo_count, S_IRUGO, mci_ue_noinfo_show, शून्य);
अटल DEVICE_ATTR(ce_noinfo_count, S_IRUGO, mci_ce_noinfo_show, शून्य);
अटल DEVICE_ATTR(ue_count, S_IRUGO, mci_ue_count_show, शून्य);
अटल DEVICE_ATTR(ce_count, S_IRUGO, mci_ce_count_show, शून्य);
अटल DEVICE_ATTR(max_location, S_IRUGO, mci_max_location_show, शून्य);

/* memory scrubber attribute file */
अटल DEVICE_ATTR(sdram_scrub_rate, 0, mci_sdram_scrub_rate_show,
	    mci_sdram_scrub_rate_store); /* umode set later in is_visible */

अटल काष्ठा attribute *mci_attrs[] = अणु
	&dev_attr_reset_counters.attr,
	&dev_attr_mc_name.attr,
	&dev_attr_size_mb.attr,
	&dev_attr_seconds_since_reset.attr,
	&dev_attr_ue_noinfo_count.attr,
	&dev_attr_ce_noinfo_count.attr,
	&dev_attr_ue_count.attr,
	&dev_attr_ce_count.attr,
	&dev_attr_max_location.attr,
	&dev_attr_sdram_scrub_rate.attr,
	शून्य
पूर्ण;

अटल umode_t mci_attr_is_visible(काष्ठा kobject *kobj,
				   काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	umode_t mode = 0;

	अगर (attr != &dev_attr_sdram_scrub_rate.attr)
		वापस attr->mode;
	अगर (mci->get_sdram_scrub_rate)
		mode |= S_IRUGO;
	अगर (mci->set_sdram_scrub_rate)
		mode |= S_IWUSR;
	वापस mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group mci_attr_grp = अणु
	.attrs	= mci_attrs,
	.is_visible = mci_attr_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mci_attr_groups[] = अणु
	&mci_attr_grp,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा device_type mci_attr_type = अणु
	.groups		= mci_attr_groups,
पूर्ण;

/*
 * Create a new Memory Controller kobject instance,
 *	mc<id> under the 'mc' directory
 *
 * Return:
 *	0	Success
 *	!0	Failure
 */
पूर्णांक edac_create_sysfs_mci_device(काष्ठा mem_ctl_info *mci,
				 स्थिर काष्ठा attribute_group **groups)
अणु
	काष्ठा dimm_info *dimm;
	पूर्णांक err;

	/* get the /sys/devices/प्रणाली/edac subsys reference */
	mci->dev.type = &mci_attr_type;
	mci->dev.parent = mci_pdev;
	mci->dev.groups = groups;
	dev_set_name(&mci->dev, "mc%d", mci->mc_idx);
	dev_set_drvdata(&mci->dev, mci);
	pm_runसमय_क्रमbid(&mci->dev);

	err = device_add(&mci->dev);
	अगर (err < 0) अणु
		edac_dbg(1, "failure: create device %s\n", dev_name(&mci->dev));
		/* no put_device() here, मुक्त mci with _edac_mc_मुक्त() */
		वापस err;
	पूर्ण

	edac_dbg(0, "device %s created\n", dev_name(&mci->dev));

	/*
	 * Create the dimm/rank devices
	 */
	mci_क्रम_each_dimm(mci, dimm) अणु
		/* Only expose populated DIMMs */
		अगर (!dimm->nr_pages)
			जारी;

		err = edac_create_dimm_object(mci, dimm);
		अगर (err)
			जाओ fail;
	पूर्ण

#अगर_घोषित CONFIG_EDAC_LEGACY_SYSFS
	err = edac_create_csrow_objects(mci);
	अगर (err < 0)
		जाओ fail;
#पूर्ण_अगर

	edac_create_debugfs_nodes(mci);
	वापस 0;

fail:
	edac_हटाओ_sysfs_mci_device(mci);

	वापस err;
पूर्ण

/*
 * हटाओ a Memory Controller instance
 */
व्योम edac_हटाओ_sysfs_mci_device(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा dimm_info *dimm;

	अगर (!device_is_रेजिस्टरed(&mci->dev))
		वापस;

	edac_dbg(0, "\n");

#अगर_घोषित CONFIG_EDAC_DEBUG
	edac_debugfs_हटाओ_recursive(mci->debugfs);
#पूर्ण_अगर
#अगर_घोषित CONFIG_EDAC_LEGACY_SYSFS
	edac_delete_csrow_objects(mci);
#पूर्ण_अगर

	mci_क्रम_each_dimm(mci, dimm) अणु
		अगर (!device_is_रेजिस्टरed(&dimm->dev))
			जारी;
		edac_dbg(1, "unregistering device %s\n", dev_name(&dimm->dev));
		device_unरेजिस्टर(&dimm->dev);
	पूर्ण

	/* only हटाओ the device, but keep mci */
	device_del(&mci->dev);
पूर्ण

अटल व्योम mc_attr_release(काष्ठा device *dev)
अणु
	/*
	 * There's no container काष्ठाure here, as this is just the mci
	 * parent device, used to create the /sys/devices/mc sysfs node.
	 * So, there are no attributes on it.
	 */
	edac_dbg(1, "device %s released\n", dev_name(dev));
	kमुक्त(dev);
पूर्ण

/*
 * Init/निकास code क्रम the module. Basically, creates/हटाओs /sys/class/rc
 */
पूर्णांक __init edac_mc_sysfs_init(व्योम)
अणु
	पूर्णांक err;

	mci_pdev = kzalloc(माप(*mci_pdev), GFP_KERNEL);
	अगर (!mci_pdev)
		वापस -ENOMEM;

	mci_pdev->bus = edac_get_sysfs_subsys();
	mci_pdev->release = mc_attr_release;
	mci_pdev->init_name = "mc";

	err = device_रेजिस्टर(mci_pdev);
	अगर (err < 0) अणु
		edac_dbg(1, "failure: create device %s\n", dev_name(mci_pdev));
		put_device(mci_pdev);
		वापस err;
	पूर्ण

	edac_dbg(0, "device %s created\n", dev_name(mci_pdev));

	वापस 0;
पूर्ण

व्योम edac_mc_sysfs_निकास(व्योम)
अणु
	device_unरेजिस्टर(mci_pdev);
पूर्ण
