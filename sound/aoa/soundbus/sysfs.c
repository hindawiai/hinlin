<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/स्थिति.स>
/* FIX UP */
#समावेश "soundbus.h"

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा soundbus_dev *sdev = to_soundbus_device(dev);
	काष्ठा platक्रमm_device *of = &sdev->ofdev;
	पूर्णांक length;

	अगर (*sdev->modalias) अणु
		strscpy(buf, sdev->modalias, माप(sdev->modalias) + 1);
		म_जोड़ो(buf, "\n");
		length = म_माप(buf);
	पूर्ण अन्यथा अणु
		length = प्र_लिखो(buf, "of:N%pOFn%c%s\n",
				 of->dev.of_node, 'T',
                                 of_node_get_device_type(of->dev.of_node));
	पूर्ण

	वापस length;
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा soundbus_dev *sdev = to_soundbus_device(dev);
	काष्ठा platक्रमm_device *of = &sdev->ofdev;

	वापस प्र_लिखो(buf, "%pOFn\n", of->dev.of_node);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा soundbus_dev *sdev = to_soundbus_device(dev);
	काष्ठा platक्रमm_device *of = &sdev->ofdev;

	वापस प्र_लिखो(buf, "%s\n", of_node_get_device_type(of->dev.of_node));
पूर्ण
अटल DEVICE_ATTR_RO(type);

काष्ठा attribute *soundbus_dev_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_type.attr,
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
