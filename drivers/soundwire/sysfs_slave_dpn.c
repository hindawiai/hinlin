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

काष्ठा dpn_attribute अणु
	काष्ठा device_attribute	dev_attr;
	पूर्णांक N;
	पूर्णांक dir;
	स्थिर अक्षर *क्रमmat_string;
पूर्ण;

/*
 * Since we can't use ARRAY_SIZE, hard-code number of dpN attributes.
 * This needs to be updated when adding new attributes - an error will be
 * flagged on a mismatch.
 */
#घोषणा SDW_DPN_ATTRIBUTES 15

#घोषणा sdw_dpn_attribute_alloc(field)					\
अटल पूर्णांक field##_attribute_alloc(काष्ठा device *dev,			\
				काष्ठा attribute **res,			\
				पूर्णांक N, पूर्णांक dir,				\
				स्थिर अक्षर *क्रमmat_string)		\
अणु									\
	काष्ठा dpn_attribute *dpn_attr;					\
									\
	dpn_attr = devm_kzalloc(dev, माप(*dpn_attr), GFP_KERNEL);	\
	अगर (!dpn_attr)							\
		वापस -ENOMEM;						\
	dpn_attr->N = N;						\
	dpn_attr->dir = dir;						\
	sysfs_attr_init(&dpn_attr->dev_attr.attr);			\
	dpn_attr->क्रमmat_string = क्रमmat_string;			\
	dpn_attr->dev_attr.attr.name = __stringअगरy(field);		\
	dpn_attr->dev_attr.attr.mode = 0444;				\
	dpn_attr->dev_attr.show = field##_show;				\
									\
	*res = &dpn_attr->dev_attr.attr;				\
									\
	वापस 0;							\
पूर्ण

#घोषणा sdw_dpn_attr(field)						\
									\
अटल sमाप_प्रकार field##_dpn_show(काष्ठा sdw_slave *slave,		\
				पूर्णांक N,					\
				पूर्णांक dir,				\
				स्थिर अक्षर *क्रमmat_string,		\
				अक्षर *buf)				\
अणु									\
	काष्ठा sdw_dpn_prop *dpn;					\
	अचिन्हित दीर्घ mask;						\
	पूर्णांक bit;							\
	पूर्णांक i;								\
									\
	अगर (dir) अणु							\
		dpn = slave->prop.src_dpn_prop;				\
		mask = slave->prop.source_ports;			\
	पूर्ण अन्यथा अणु							\
		dpn = slave->prop.sink_dpn_prop;			\
		mask = slave->prop.sink_ports;				\
	पूर्ण								\
									\
	i = 0;								\
	क्रम_each_set_bit(bit, &mask, 32) अणु				\
		अगर (bit == N) अणु						\
			वापस प्र_लिखो(buf, क्रमmat_string,		\
				       dpn[i].field);			\
		पूर्ण							\
		i++;							\
	पूर्ण								\
	वापस -EINVAL;							\
पूर्ण									\
									\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr,		\
			    अक्षर *buf)					\
अणु									\
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);			\
	काष्ठा dpn_attribute *dpn_attr =				\
		container_of(attr, काष्ठा dpn_attribute, dev_attr);	\
									\
	वापस field##_dpn_show(slave,					\
				dpn_attr->N, dpn_attr->dir,		\
				dpn_attr->क्रमmat_string,		\
				buf);					\
पूर्ण									\
sdw_dpn_attribute_alloc(field)

sdw_dpn_attr(imp_def_पूर्णांकerrupts);
sdw_dpn_attr(max_word);
sdw_dpn_attr(min_word);
sdw_dpn_attr(type);
sdw_dpn_attr(max_grouping);
sdw_dpn_attr(simple_ch_prep_sm);
sdw_dpn_attr(ch_prep_समयout);
sdw_dpn_attr(max_ch);
sdw_dpn_attr(min_ch);
sdw_dpn_attr(max_async_buffer);
sdw_dpn_attr(block_pack_mode);
sdw_dpn_attr(port_encoding);

#घोषणा sdw_dpn_array_attr(field)					\
									\
अटल sमाप_प्रकार field##_dpn_show(काष्ठा sdw_slave *slave,		\
				पूर्णांक N,					\
				पूर्णांक dir,				\
				स्थिर अक्षर *क्रमmat_string,		\
				अक्षर *buf)				\
अणु									\
	काष्ठा sdw_dpn_prop *dpn;					\
	अचिन्हित दीर्घ mask;						\
	sमाप_प्रकार size = 0;						\
	पूर्णांक bit;							\
	पूर्णांक i;								\
	पूर्णांक j;								\
									\
	अगर (dir) अणु							\
		dpn = slave->prop.src_dpn_prop;				\
		mask = slave->prop.source_ports;			\
	पूर्ण अन्यथा अणु							\
		dpn = slave->prop.sink_dpn_prop;			\
		mask = slave->prop.sink_ports;				\
	पूर्ण								\
									\
	i = 0;								\
	क्रम_each_set_bit(bit, &mask, 32) अणु				\
		अगर (bit == N) अणु						\
			क्रम (j = 0; j < dpn[i].num_##field; j++)	\
				size += प्र_लिखो(buf + size,		\
						क्रमmat_string,		\
						dpn[i].field[j]);	\
			size += प्र_लिखो(buf + size, "\n");		\
			वापस size;					\
		पूर्ण							\
		i++;							\
	पूर्ण								\
	वापस -EINVAL;							\
पूर्ण									\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr,		\
			    अक्षर *buf)					\
अणु									\
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);			\
	काष्ठा dpn_attribute *dpn_attr =				\
		container_of(attr, काष्ठा dpn_attribute, dev_attr);	\
									\
	वापस field##_dpn_show(slave,					\
				dpn_attr->N, dpn_attr->dir,		\
				dpn_attr->क्रमmat_string,		\
				buf);					\
पूर्ण									\
sdw_dpn_attribute_alloc(field)

sdw_dpn_array_attr(words);
sdw_dpn_array_attr(ch_combinations);
sdw_dpn_array_attr(channels);

अटल पूर्णांक add_all_attributes(काष्ठा device *dev, पूर्णांक N, पूर्णांक dir)
अणु
	काष्ठा attribute **dpn_attrs;
	काष्ठा attribute_group *dpn_group;
	पूर्णांक i = 0;
	पूर्णांक ret;

	/* allocate attributes, last one is शून्य */
	dpn_attrs = devm_kसुस्मृति(dev, SDW_DPN_ATTRIBUTES + 1,
				 माप(काष्ठा attribute *),
				 GFP_KERNEL);
	अगर (!dpn_attrs)
		वापस -ENOMEM;

	ret = max_word_attribute_alloc(dev, &dpn_attrs[i++],
				       N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = min_word_attribute_alloc(dev, &dpn_attrs[i++],
				       N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = words_attribute_alloc(dev, &dpn_attrs[i++],
				    N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = type_attribute_alloc(dev, &dpn_attrs[i++],
				   N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = max_grouping_attribute_alloc(dev, &dpn_attrs[i++],
					   N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = simple_ch_prep_sm_attribute_alloc(dev, &dpn_attrs[i++],
						N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = ch_prep_समयout_attribute_alloc(dev, &dpn_attrs[i++],
					      N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = imp_def_पूर्णांकerrupts_attribute_alloc(dev, &dpn_attrs[i++],
						 N, dir, "0x%x\n");
	अगर (ret < 0)
		वापस ret;

	ret = min_ch_attribute_alloc(dev, &dpn_attrs[i++],
				     N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = max_ch_attribute_alloc(dev, &dpn_attrs[i++],
				     N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = channels_attribute_alloc(dev, &dpn_attrs[i++],
				       N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = ch_combinations_attribute_alloc(dev, &dpn_attrs[i++],
					      N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = max_async_buffer_attribute_alloc(dev, &dpn_attrs[i++],
					       N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = block_pack_mode_attribute_alloc(dev, &dpn_attrs[i++],
					      N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	ret = port_encoding_attribute_alloc(dev, &dpn_attrs[i++],
					    N, dir, "%d\n");
	अगर (ret < 0)
		वापस ret;

	/* paranoia check क्रम editing mistakes */
	अगर (i != SDW_DPN_ATTRIBUTES) अणु
		dev_err(dev, "mismatch in attributes, allocated %d got %d\n",
			SDW_DPN_ATTRIBUTES, i);
		वापस -EINVAL;
	पूर्ण

	dpn_group = devm_kzalloc(dev, माप(*dpn_group), GFP_KERNEL);
	अगर (!dpn_group)
		वापस -ENOMEM;

	dpn_group->attrs = dpn_attrs;
	dpn_group->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "dp%d_%s",
					 N, dir ? "src" : "sink");
	अगर (!dpn_group->name)
		वापस -ENOMEM;

	ret = devm_device_add_group(dev, dpn_group);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक sdw_slave_sysfs_dpn_init(काष्ठा sdw_slave *slave)
अणु
	अचिन्हित दीर्घ mask;
	पूर्णांक ret;
	पूर्णांक i;

	mask = slave->prop.source_ports;
	क्रम_each_set_bit(i, &mask, 32) अणु
		ret = add_all_attributes(&slave->dev, i, 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	mask = slave->prop.sink_ports;
	क्रम_each_set_bit(i, &mask, 32) अणु
		ret = add_all_attributes(&slave->dev, i, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
