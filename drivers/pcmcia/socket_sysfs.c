<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * socket_sysfs.c -- most of socket-related sysfs output
 *
 * (C) 2003 - 2004		Dominik Broकरोwski
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/irq.h>

#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ds.h>
#समावेश "cs_internal.h"

#घोषणा to_socket(_dev) container_of(_dev, काष्ठा pcmcia_socket, dev)

अटल sमाप_प्रकार pccard_show_type(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा pcmcia_socket *s = to_socket(dev);

	अगर (!(s->state & SOCKET_PRESENT))
		वापस -ENODEV;
	अगर (s->state & SOCKET_CARDBUS)
		वापस प्र_लिखो(buf, "32-bit\n");
	वापस प्र_लिखो(buf, "16-bit\n");
पूर्ण
अटल DEVICE_ATTR(card_type, 0444, pccard_show_type, शून्य);

अटल sमाप_प्रकार pccard_show_voltage(काष्ठा device *dev, काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा pcmcia_socket *s = to_socket(dev);

	अगर (!(s->state & SOCKET_PRESENT))
		वापस -ENODEV;
	अगर (s->socket.Vcc)
		वापस प्र_लिखो(buf, "%d.%dV\n", s->socket.Vcc / 10,
			       s->socket.Vcc % 10);
	वापस प्र_लिखो(buf, "X.XV\n");
पूर्ण
अटल DEVICE_ATTR(card_voltage, 0444, pccard_show_voltage, शून्य);

अटल sमाप_प्रकार pccard_show_vpp(काष्ठा device *dev, काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा pcmcia_socket *s = to_socket(dev);
	अगर (!(s->state & SOCKET_PRESENT))
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d.%dV\n", s->socket.Vpp / 10, s->socket.Vpp % 10);
पूर्ण
अटल DEVICE_ATTR(card_vpp, 0444, pccard_show_vpp, शून्य);

अटल sमाप_प्रकार pccard_show_vcc(काष्ठा device *dev, काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा pcmcia_socket *s = to_socket(dev);
	अगर (!(s->state & SOCKET_PRESENT))
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d.%dV\n", s->socket.Vcc / 10, s->socket.Vcc % 10);
पूर्ण
अटल DEVICE_ATTR(card_vcc, 0444, pccard_show_vcc, शून्य);


अटल sमाप_प्रकार pccard_store_insert(काष्ठा device *dev, काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcmcia_socket *s = to_socket(dev);

	अगर (!count)
		वापस -EINVAL;

	pcmcia_parse_uevents(s, PCMCIA_UEVENT_INSERT);

	वापस count;
पूर्ण
अटल DEVICE_ATTR(card_insert, 0200, शून्य, pccard_store_insert);


अटल sमाप_प्रकार pccard_show_card_pm_state(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा pcmcia_socket *s = to_socket(dev);
	वापस प्र_लिखो(buf, "%s\n", s->state & SOCKET_SUSPEND ? "off" : "on");
पूर्ण

अटल sमाप_प्रकार pccard_store_card_pm_state(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcmcia_socket *s = to_socket(dev);
	sमाप_प्रकार ret = count;

	अगर (!count)
		वापस -EINVAL;

	अगर (!म_भेदन(buf, "off", 3))
		pcmcia_parse_uevents(s, PCMCIA_UEVENT_SUSPEND);
	अन्यथा अणु
		अगर (!म_भेदन(buf, "on", 2))
			pcmcia_parse_uevents(s, PCMCIA_UEVENT_RESUME);
		अन्यथा
			ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
अटल DEVICE_ATTR(card_pm_state, 0644, pccard_show_card_pm_state, pccard_store_card_pm_state);

अटल sमाप_प्रकार pccard_store_eject(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcmcia_socket *s = to_socket(dev);

	अगर (!count)
		वापस -EINVAL;

	pcmcia_parse_uevents(s, PCMCIA_UEVENT_EJECT);

	वापस count;
पूर्ण
अटल DEVICE_ATTR(card_eject, 0200, शून्य, pccard_store_eject);


अटल sमाप_प्रकार pccard_show_irq_mask(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा pcmcia_socket *s = to_socket(dev);
	वापस प्र_लिखो(buf, "0x%04x\n", s->irq_mask);
पूर्ण

अटल sमाप_प्रकार pccard_store_irq_mask(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;
	काष्ठा pcmcia_socket *s = to_socket(dev);
	u32 mask;

	अगर (!count)
		वापस -EINVAL;

	ret = माला_पूछो(buf, "0x%x\n", &mask);

	अगर (ret == 1) अणु
		mutex_lock(&s->ops_mutex);
		s->irq_mask &= mask;
		mutex_unlock(&s->ops_mutex);
		ret = 0;
	पूर्ण

	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR(card_irq_mask, 0600, pccard_show_irq_mask, pccard_store_irq_mask);


अटल sमाप_प्रकार pccard_show_resource(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcmcia_socket *s = to_socket(dev);
	वापस प्र_लिखो(buf, "%s\n", s->resource_setup_करोne ? "yes" : "no");
पूर्ण

अटल sमाप_प्रकार pccard_store_resource(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcmcia_socket *s = to_socket(dev);

	अगर (!count)
		वापस -EINVAL;

	mutex_lock(&s->ops_mutex);
	अगर (!s->resource_setup_करोne)
		s->resource_setup_करोne = 1;
	mutex_unlock(&s->ops_mutex);

	pcmcia_parse_uevents(s, PCMCIA_UEVENT_REQUERY);

	वापस count;
पूर्ण
अटल DEVICE_ATTR(available_resources_setup_करोne, 0600, pccard_show_resource, pccard_store_resource);

अटल काष्ठा attribute *pccard_socket_attributes[] = अणु
	&dev_attr_card_type.attr,
	&dev_attr_card_voltage.attr,
	&dev_attr_card_vpp.attr,
	&dev_attr_card_vcc.attr,
	&dev_attr_card_insert.attr,
	&dev_attr_card_pm_state.attr,
	&dev_attr_card_eject.attr,
	&dev_attr_card_irq_mask.attr,
	&dev_attr_available_resources_setup_करोne.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group socket_attrs = अणु
	.attrs = pccard_socket_attributes,
पूर्ण;

पूर्णांक pccard_sysfs_add_socket(काष्ठा device *dev)
अणु
	वापस sysfs_create_group(&dev->kobj, &socket_attrs);
पूर्ण

व्योम pccard_sysfs_हटाओ_socket(काष्ठा device *dev)
अणु
	sysfs_हटाओ_group(&dev->kobj, &socket_attrs);
पूर्ण
