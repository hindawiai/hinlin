<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2015-2020 Intel Corporation.

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश "bus.h"
#समावेश "sysfs_local.h"

/*
 * Slave sysfs
 */

/*
 * The sysfs क्रम Slave reflects the MIPI description as given
 * in the MIPI DisCo spec.
 * status and device_number come directly from the MIPI SoundWire
 * 1.x specअगरication.
 *
 * Base file is device
 *	|---- status
 *	|---- device_number
 *	|---- modalias
 *	|---- dev-properties
 *		|---- mipi_revision
 *		|---- wake_capable
 *		|---- test_mode_capable
 *		|---- clk_stop_mode1
 *		|---- simple_clk_stop_capable
 *		|---- clk_stop_समयout
 *		|---- ch_prep_समयout
 *		|---- reset_behave
 *		|---- high_PHY_capable
 *		|---- paging_support
 *		|---- bank_delay_support
 *		|---- p15_behave
 *		|---- master_count
 *		|---- source_ports
 *		|---- sink_ports
 *	|---- dp0
 *		|---- max_word
 *		|---- min_word
 *		|---- words
 *		|---- BRA_flow_controlled
 *		|---- simple_ch_prep_sm
 *		|---- imp_def_पूर्णांकerrupts
 *	|---- dpN_<sink/src>
 *		|---- max_word
 *		|---- min_word
 *		|---- words
 *		|---- type
 *		|---- max_grouping
 *		|---- simple_ch_prep_sm
 *		|---- ch_prep_समयout
 *		|---- imp_def_पूर्णांकerrupts
 *		|---- min_ch
 *		|---- max_ch
 *		|---- channels
 *		|---- ch_combinations
 *		|---- max_async_buffer
 *		|---- block_pack_mode
 *		|---- port_encoding
 *
 */

#घोषणा sdw_slave_attr(field, क्रमmat_string)			\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,			\
			    काष्ठा device_attribute *attr,	\
			    अक्षर *buf)				\
अणु								\
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);		\
	वापस प्र_लिखो(buf, क्रमmat_string, slave->prop.field);	\
पूर्ण								\
अटल DEVICE_ATTR_RO(field)

sdw_slave_attr(mipi_revision, "0x%x\n");
sdw_slave_attr(wake_capable, "%d\n");
sdw_slave_attr(test_mode_capable, "%d\n");
sdw_slave_attr(clk_stop_mode1, "%d\n");
sdw_slave_attr(simple_clk_stop_capable, "%d\n");
sdw_slave_attr(clk_stop_समयout, "%d\n");
sdw_slave_attr(ch_prep_समयout, "%d\n");
sdw_slave_attr(reset_behave, "%d\n");
sdw_slave_attr(high_PHY_capable, "%d\n");
sdw_slave_attr(paging_support, "%d\n");
sdw_slave_attr(bank_delay_support, "%d\n");
sdw_slave_attr(p15_behave, "%d\n");
sdw_slave_attr(master_count, "%d\n");
sdw_slave_attr(source_ports, "0x%x\n");
sdw_slave_attr(sink_ports, "0x%x\n");

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);

	वापस sdw_slave_modalias(slave, buf, 256);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *slave_attrs[] = अणु
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(slave);

अटल काष्ठा attribute *slave_dev_attrs[] = अणु
	&dev_attr_mipi_revision.attr,
	&dev_attr_wake_capable.attr,
	&dev_attr_test_mode_capable.attr,
	&dev_attr_clk_stop_mode1.attr,
	&dev_attr_simple_clk_stop_capable.attr,
	&dev_attr_clk_stop_समयout.attr,
	&dev_attr_ch_prep_समयout.attr,
	&dev_attr_reset_behave.attr,
	&dev_attr_high_PHY_capable.attr,
	&dev_attr_paging_support.attr,
	&dev_attr_bank_delay_support.attr,
	&dev_attr_p15_behave.attr,
	&dev_attr_master_count.attr,
	&dev_attr_source_ports.attr,
	&dev_attr_sink_ports.attr,
	शून्य,
पूर्ण;

/*
 * we करोn't use ATTRIBUTES_GROUP here since we want to add a subdirectory
 * क्रम device-level properties
 */
अटल स्थिर काष्ठा attribute_group sdw_slave_dev_attr_group = अणु
	.attrs	= slave_dev_attrs,
	.name = "dev-properties",
पूर्ण;

/*
 * DP0 sysfs
 */

#घोषणा sdw_dp0_attr(field, क्रमmat_string)				\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr,		\
			    अक्षर *buf)					\
अणु									\
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);			\
	वापस प्र_लिखो(buf, क्रमmat_string, slave->prop.dp0_prop->field);\
पूर्ण									\
अटल DEVICE_ATTR_RO(field)

sdw_dp0_attr(max_word, "%d\n");
sdw_dp0_attr(min_word, "%d\n");
sdw_dp0_attr(BRA_flow_controlled, "%d\n");
sdw_dp0_attr(simple_ch_prep_sm, "%d\n");
sdw_dp0_attr(imp_def_पूर्णांकerrupts, "0x%x\n");

अटल sमाप_प्रकार words_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	sमाप_प्रकार size = 0;
	पूर्णांक i;

	क्रम (i = 0; i < slave->prop.dp0_prop->num_words; i++)
		size += प्र_लिखो(buf + size, "%d ",
				slave->prop.dp0_prop->words[i]);
	size += प्र_लिखो(buf + size, "\n");

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RO(words);

अटल काष्ठा attribute *dp0_attrs[] = अणु
	&dev_attr_max_word.attr,
	&dev_attr_min_word.attr,
	&dev_attr_words.attr,
	&dev_attr_BRA_flow_controlled.attr,
	&dev_attr_simple_ch_prep_sm.attr,
	&dev_attr_imp_def_पूर्णांकerrupts.attr,
	शून्य,
पूर्ण;

/*
 * we करोn't use ATTRIBUTES_GROUP here since we want to add a subdirectory
 * क्रम dp0-level properties
 */
अटल स्थिर काष्ठा attribute_group dp0_group = अणु
	.attrs = dp0_attrs,
	.name = "dp0",
पूर्ण;

पूर्णांक sdw_slave_sysfs_init(काष्ठा sdw_slave *slave)
अणु
	पूर्णांक ret;

	ret = devm_device_add_groups(&slave->dev, slave_groups);
	अगर (ret < 0)
		वापस ret;

	ret = devm_device_add_group(&slave->dev, &sdw_slave_dev_attr_group);
	अगर (ret < 0)
		वापस ret;

	अगर (slave->prop.dp0_prop) अणु
		ret = devm_device_add_group(&slave->dev, &dp0_group);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (slave->prop.source_ports || slave->prop.sink_ports) अणु
		ret = sdw_slave_sysfs_dpn_init(slave);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * the status is shown in capital letters क्रम UNATTACHED and RESERVED
 * on purpose, to highligh users to the fact that these status values
 * are not expected.
 */
अटल स्थिर अक्षर *स्थिर slave_status[] = अणु
	[SDW_SLAVE_UNATTACHED] =  "UNATTACHED",
	[SDW_SLAVE_ATTACHED] = "Attached",
	[SDW_SLAVE_ALERT] = "Alert",
	[SDW_SLAVE_RESERVED] = "RESERVED",
पूर्ण;

अटल sमाप_प्रकार status_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);

	वापस प्र_लिखो(buf, "%s\n", slave_status[slave->status]);
पूर्ण
अटल DEVICE_ATTR_RO(status);

अटल sमाप_प्रकार device_number_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);

	अगर (slave->status == SDW_SLAVE_UNATTACHED)
		वापस प्र_लिखो(buf, "%s", "N/A");
	अन्यथा
		वापस प्र_लिखो(buf, "%d", slave->dev_num);
पूर्ण
अटल DEVICE_ATTR_RO(device_number);

अटल काष्ठा attribute *slave_status_attrs[] = अणु
	&dev_attr_status.attr,
	&dev_attr_device_number.attr,
	शून्य,
पूर्ण;

/*
 * we करोn't use ATTRIBUTES_GROUP here since the group is used in a
 * separate file and can't be handled as a अटल.
 */
अटल स्थिर काष्ठा attribute_group sdw_slave_status_attr_group = अणु
	.attrs	= slave_status_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *sdw_slave_status_attr_groups[] = अणु
	&sdw_slave_status_attr_group,
	शून्य
पूर्ण;
