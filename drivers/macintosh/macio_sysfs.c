<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/स्थिति.स>
#समावेश <यंत्र/macपन.स>

अटल sमाप_प्रकार
compatible_show (काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *of;
	स्थिर अक्षर *compat;
	पूर्णांक cplen;
	पूर्णांक length = 0;

	of = &to_macio_device (dev)->ofdev;
	compat = of_get_property(of->dev.of_node, "compatible", &cplen);
	अगर (!compat) अणु
		*buf = '\0';
		वापस 0;
	पूर्ण
	जबतक (cplen > 0) अणु
		पूर्णांक l;
		length += प्र_लिखो (buf, "%s\n", compat);
		buf += length;
		l = म_माप (compat) + 1;
		compat += l;
		cplen -= l;
	पूर्ण

	वापस length;
पूर्ण
अटल DEVICE_ATTR_RO(compatible);

अटल sमाप_प्रकार modalias_show (काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस of_device_modalias(dev, buf, PAGE_SIZE);
पूर्ण

अटल sमाप_प्रकार devspec_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *ofdev;

	ofdev = to_platक्रमm_device(dev);
	वापस प्र_लिखो(buf, "%pOF\n", ofdev->dev.of_node);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);
अटल DEVICE_ATTR_RO(devspec);

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%pOFn\n", dev->of_node);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", of_node_get_device_type(dev->of_node));
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल काष्ठा attribute *macio_dev_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_type.attr,
	&dev_attr_compatible.attr,
	&dev_attr_modalias.attr,
	&dev_attr_devspec.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group macio_dev_group = अणु
	.attrs = macio_dev_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *macio_dev_groups[] = अणु
	&macio_dev_group,
	शून्य,
पूर्ण;
