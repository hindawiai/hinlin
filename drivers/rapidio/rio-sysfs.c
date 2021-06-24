<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RapidIO sysfs attributes and support
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/rपन.स>
#समावेश <linux/rio_drv.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/capability.h>

#समावेश "rio.h"

/* Sysfs support */
#घोषणा rio_config_attr(field, क्रमmat_string)					\
अटल sमाप_प्रकार								\
field##_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)			\
अणु									\
	काष्ठा rio_dev *rdev = to_rio_dev(dev);				\
									\
	वापस प्र_लिखो(buf, क्रमmat_string, rdev->field);		\
पूर्ण									\
अटल DEVICE_ATTR_RO(field);

rio_config_attr(did, "0x%04x\n");
rio_config_attr(vid, "0x%04x\n");
rio_config_attr(device_rev, "0x%08x\n");
rio_config_attr(यंत्र_did, "0x%04x\n");
rio_config_attr(यंत्र_vid, "0x%04x\n");
rio_config_attr(यंत्र_rev, "0x%04x\n");
rio_config_attr(destid, "0x%04x\n");
rio_config_attr(hopcount, "0x%02x\n");

अटल sमाप_प्रकार routes_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rio_dev *rdev = to_rio_dev(dev);
	अक्षर *str = buf;
	पूर्णांक i;

	क्रम (i = 0; i < RIO_MAX_ROUTE_ENTRIES(rdev->net->hport->sys_size);
			i++) अणु
		अगर (rdev->rचयन->route_table[i] == RIO_INVALID_ROUTE)
			जारी;
		str +=
		    प्र_लिखो(str, "%04x %02x\n", i,
			    rdev->rचयन->route_table[i]);
	पूर्ण

	वापस (str - buf);
पूर्ण
अटल DEVICE_ATTR_RO(routes);

अटल sमाप_प्रकार lprev_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rio_dev *rdev = to_rio_dev(dev);

	वापस प्र_लिखो(buf, "%s\n",
			(rdev->prev) ? rio_name(rdev->prev) : "root");
पूर्ण
अटल DEVICE_ATTR_RO(lprev);

अटल sमाप_प्रकार lnext_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rio_dev *rdev = to_rio_dev(dev);
	अक्षर *str = buf;
	पूर्णांक i;

	अगर (rdev->pef & RIO_PEF_SWITCH) अणु
		क्रम (i = 0; i < RIO_GET_TOTAL_PORTS(rdev->swpinfo); i++) अणु
			अगर (rdev->rचयन->nextdev[i])
				str += प्र_लिखो(str, "%s\n",
					rio_name(rdev->rचयन->nextdev[i]));
			अन्यथा
				str += प्र_लिखो(str, "null\n");
		पूर्ण
	पूर्ण

	वापस str - buf;
पूर्ण
अटल DEVICE_ATTR_RO(lnext);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rio_dev *rdev = to_rio_dev(dev);

	वापस प्र_लिखो(buf, "rapidio:v%04Xd%04Xav%04Xad%04X\n",
		       rdev->vid, rdev->did, rdev->यंत्र_vid, rdev->यंत्र_did);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *rio_dev_attrs[] = अणु
	&dev_attr_did.attr,
	&dev_attr_vid.attr,
	&dev_attr_device_rev.attr,
	&dev_attr_यंत्र_did.attr,
	&dev_attr_यंत्र_vid.attr,
	&dev_attr_यंत्र_rev.attr,
	&dev_attr_lprev.attr,
	&dev_attr_destid.attr,
	&dev_attr_modalias.attr,

	/* Switch-only attributes */
	&dev_attr_routes.attr,
	&dev_attr_lnext.attr,
	&dev_attr_hopcount.attr,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार
rio_पढ़ो_config(काष्ठा file *filp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *bin_attr,
		अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा rio_dev *dev = to_rio_dev(kobj_to_dev(kobj));
	अचिन्हित पूर्णांक size = 0x100;
	loff_t init_off = off;
	u8 *data = (u8 *) buf;

	/* Several chips lock up trying to पढ़ो undefined config space */
	अगर (capable(CAP_SYS_ADMIN))
		size = RIO_MAINT_SPACE_SZ;

	अगर (off >= size)
		वापस 0;
	अगर (off + count > size) अणु
		size -= off;
		count = size;
	पूर्ण अन्यथा अणु
		size = count;
	पूर्ण

	अगर ((off & 1) && size) अणु
		u8 val;
		rio_पढ़ो_config_8(dev, off, &val);
		data[off - init_off] = val;
		off++;
		size--;
	पूर्ण

	अगर ((off & 3) && size > 2) अणु
		u16 val;
		rio_पढ़ो_config_16(dev, off, &val);
		data[off - init_off] = (val >> 8) & 0xff;
		data[off - init_off + 1] = val & 0xff;
		off += 2;
		size -= 2;
	पूर्ण

	जबतक (size > 3) अणु
		u32 val;
		rio_पढ़ो_config_32(dev, off, &val);
		data[off - init_off] = (val >> 24) & 0xff;
		data[off - init_off + 1] = (val >> 16) & 0xff;
		data[off - init_off + 2] = (val >> 8) & 0xff;
		data[off - init_off + 3] = val & 0xff;
		off += 4;
		size -= 4;
	पूर्ण

	अगर (size >= 2) अणु
		u16 val;
		rio_पढ़ो_config_16(dev, off, &val);
		data[off - init_off] = (val >> 8) & 0xff;
		data[off - init_off + 1] = val & 0xff;
		off += 2;
		size -= 2;
	पूर्ण

	अगर (size > 0) अणु
		u8 val;
		rio_पढ़ो_config_8(dev, off, &val);
		data[off - init_off] = val;
		off++;
		--size;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार
rio_ग_लिखो_config(काष्ठा file *filp, काष्ठा kobject *kobj,
		 काष्ठा bin_attribute *bin_attr,
		 अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा rio_dev *dev = to_rio_dev(kobj_to_dev(kobj));
	अचिन्हित पूर्णांक size = count;
	loff_t init_off = off;
	u8 *data = (u8 *) buf;

	अगर (off >= RIO_MAINT_SPACE_SZ)
		वापस 0;
	अगर (off + count > RIO_MAINT_SPACE_SZ) अणु
		size = RIO_MAINT_SPACE_SZ - off;
		count = size;
	पूर्ण

	अगर ((off & 1) && size) अणु
		rio_ग_लिखो_config_8(dev, off, data[off - init_off]);
		off++;
		size--;
	पूर्ण

	अगर ((off & 3) && (size > 2)) अणु
		u16 val = data[off - init_off + 1];
		val |= (u16) data[off - init_off] << 8;
		rio_ग_लिखो_config_16(dev, off, val);
		off += 2;
		size -= 2;
	पूर्ण

	जबतक (size > 3) अणु
		u32 val = data[off - init_off + 3];
		val |= (u32) data[off - init_off + 2] << 8;
		val |= (u32) data[off - init_off + 1] << 16;
		val |= (u32) data[off - init_off] << 24;
		rio_ग_लिखो_config_32(dev, off, val);
		off += 4;
		size -= 4;
	पूर्ण

	अगर (size >= 2) अणु
		u16 val = data[off - init_off + 1];
		val |= (u16) data[off - init_off] << 8;
		rio_ग_लिखो_config_16(dev, off, val);
		off += 2;
		size -= 2;
	पूर्ण

	अगर (size) अणु
		rio_ग_लिखो_config_8(dev, off, data[off - init_off]);
		off++;
		--size;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute rio_config_attr = अणु
	.attr = अणु
		 .name = "config",
		 .mode = S_IRUGO | S_IWUSR,
		 पूर्ण,
	.size = RIO_MAINT_SPACE_SZ,
	.पढ़ो = rio_पढ़ो_config,
	.ग_लिखो = rio_ग_लिखो_config,
पूर्ण;

अटल काष्ठा bin_attribute *rio_dev_bin_attrs[] = अणु
	&rio_config_attr,
	शून्य,
पूर्ण;

अटल umode_t rio_dev_is_attr_visible(काष्ठा kobject *kobj,
				       काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा rio_dev *rdev = to_rio_dev(kobj_to_dev(kobj));
	umode_t mode = attr->mode;

	अगर (!(rdev->pef & RIO_PEF_SWITCH) &&
	    (attr == &dev_attr_routes.attr ||
	     attr == &dev_attr_lnext.attr ||
	     attr == &dev_attr_hopcount.attr)) अणु
		/*
		 * Hide चयन-specअगरic attributes क्रम a non-चयन device.
		 */
		mode = 0;
	पूर्ण

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group rio_dev_group = अणु
	.attrs		= rio_dev_attrs,
	.is_visible	= rio_dev_is_attr_visible,
	.bin_attrs	= rio_dev_bin_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *rio_dev_groups[] = अणु
	&rio_dev_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार scan_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	दीर्घ val;
	पूर्णांक rc;

	अगर (kम_से_दीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	अगर (val == RIO_MPORT_ANY) अणु
		rc = rio_init_mports();
		जाओ निकास;
	पूर्ण

	अगर (val < 0 || val >= RIO_MAX_MPORTS)
		वापस -EINVAL;

	rc = rio_mport_scan((पूर्णांक)val);
निकास:
	अगर (!rc)
		rc = count;

	वापस rc;
पूर्ण
अटल BUS_ATTR_WO(scan);

अटल काष्ठा attribute *rio_bus_attrs[] = अणु
	&bus_attr_scan.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rio_bus_group = अणु
	.attrs = rio_bus_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *rio_bus_groups[] = अणु
	&rio_bus_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार
port_destid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		 अक्षर *buf)
अणु
	काष्ठा rio_mport *mport = to_rio_mport(dev);

	अगर (mport)
		वापस प्र_लिखो(buf, "0x%04x\n", mport->host_deviceid);
	अन्यथा
		वापस -ENODEV;
पूर्ण
अटल DEVICE_ATTR_RO(port_destid);

अटल sमाप_प्रकार sys_size_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा rio_mport *mport = to_rio_mport(dev);

	अगर (mport)
		वापस प्र_लिखो(buf, "%u\n", mport->sys_size);
	अन्यथा
		वापस -ENODEV;
पूर्ण
अटल DEVICE_ATTR_RO(sys_size);

अटल काष्ठा attribute *rio_mport_attrs[] = अणु
	&dev_attr_port_destid.attr,
	&dev_attr_sys_size.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rio_mport_group = अणु
	.attrs = rio_mport_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *rio_mport_groups[] = अणु
	&rio_mport_group,
	शून्य,
पूर्ण;
