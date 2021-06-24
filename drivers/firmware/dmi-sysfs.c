<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * dmi-sysfs.c
 *
 * This module exports the DMI tables पढ़ो-only to userspace through the
 * sysfs file प्रणाली.
 *
 * Data is currently found below
 *    /sys/firmware/dmi/...
 *
 * DMI attributes are presented in attribute files with names
 * क्रमmatted using %d-%d, so that the first पूर्णांकeger indicates the
 * काष्ठाure type (0-255), and the second field is the instance of that
 * entry.
 *
 * Copyright 2011 Google, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kobject.h>
#समावेश <linux/dmi.h>
#समावेश <linux/capability.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/dmi.h>

#घोषणा MAX_ENTRY_TYPE 255 /* Most of these aren't used, but we consider
			      the top entry type is only 8 bits */

काष्ठा dmi_sysfs_entry अणु
	काष्ठा dmi_header dh;
	काष्ठा kobject kobj;
	पूर्णांक instance;
	पूर्णांक position;
	काष्ठा list_head list;
	काष्ठा kobject *child;
पूर्ण;

/*
 * Global list of dmi_sysfs_entry.  Even though this should only be
 * manipulated at setup and tearकरोwn, the lazy nature of the kobject
 * प्रणाली means we get lazy हटाओs.
 */
अटल LIST_HEAD(entry_list);
अटल DEFINE_SPINLOCK(entry_list_lock);

/* dmi_sysfs_attribute - Top level attribute. used by all entries. */
काष्ठा dmi_sysfs_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा dmi_sysfs_entry *entry, अक्षर *buf);
पूर्ण;

#घोषणा DMI_SYSFS_ATTR(_entry, _name) \
काष्ठा dmi_sysfs_attribute dmi_sysfs_attr_##_entry##_##_name = अणु \
	.attr = अणु.name = __stringअगरy(_name), .mode = 0400पूर्ण, \
	.show = dmi_sysfs_##_entry##_##_name, \
पूर्ण

/*
 * dmi_sysfs_mapped_attribute - Attribute where we require the entry be
 * mapped in.  Use in conjunction with dmi_sysfs_specialize_attr_ops.
 */
काष्ठा dmi_sysfs_mapped_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा dmi_sysfs_entry *entry,
			स्थिर काष्ठा dmi_header *dh,
			अक्षर *buf);
पूर्ण;

#घोषणा DMI_SYSFS_MAPPED_ATTR(_entry, _name) \
काष्ठा dmi_sysfs_mapped_attribute dmi_sysfs_attr_##_entry##_##_name = अणु \
	.attr = अणु.name = __stringअगरy(_name), .mode = 0400पूर्ण, \
	.show = dmi_sysfs_##_entry##_##_name, \
पूर्ण

/*************************************************
 * Generic DMI entry support.
 *************************************************/
अटल व्योम dmi_entry_मुक्त(काष्ठा kobject *kobj)
अणु
	kमुक्त(kobj);
पूर्ण

अटल काष्ठा dmi_sysfs_entry *to_entry(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा dmi_sysfs_entry, kobj);
पूर्ण

अटल काष्ठा dmi_sysfs_attribute *to_attr(काष्ठा attribute *attr)
अणु
	वापस container_of(attr, काष्ठा dmi_sysfs_attribute, attr);
पूर्ण

अटल sमाप_प्रकार dmi_sysfs_attr_show(काष्ठा kobject *kobj,
				   काष्ठा attribute *_attr, अक्षर *buf)
अणु
	काष्ठा dmi_sysfs_entry *entry = to_entry(kobj);
	काष्ठा dmi_sysfs_attribute *attr = to_attr(_attr);

	/* DMI stuff is only ever admin visible */
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	वापस attr->show(entry, buf);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops dmi_sysfs_attr_ops = अणु
	.show = dmi_sysfs_attr_show,
पूर्ण;

प्रकार sमाप_प्रकार (*dmi_callback)(काष्ठा dmi_sysfs_entry *,
				स्थिर काष्ठा dmi_header *dh, व्योम *);

काष्ठा find_dmi_data अणु
	काष्ठा dmi_sysfs_entry	*entry;
	dmi_callback		callback;
	व्योम			*निजी;
	पूर्णांक			instance_countकरोwn;
	sमाप_प्रकार			ret;
पूर्ण;

अटल व्योम find_dmi_entry_helper(स्थिर काष्ठा dmi_header *dh,
				  व्योम *_data)
अणु
	काष्ठा find_dmi_data *data = _data;
	काष्ठा dmi_sysfs_entry *entry = data->entry;

	/* Is this the entry we want? */
	अगर (dh->type != entry->dh.type)
		वापस;

	अगर (data->instance_countकरोwn != 0) अणु
		/* try the next instance? */
		data->instance_countकरोwn--;
		वापस;
	पूर्ण

	/*
	 * Don't ever revisit the instance.  Short circuit later
	 * instances by letting the instance_countकरोwn run negative
	 */
	data->instance_countकरोwn--;

	/* Found the entry */
	data->ret = data->callback(entry, dh, data->निजी);
पूर्ण

/* State क्रम passing the पढ़ो parameters through dmi_find_entry() */
काष्ठा dmi_पढ़ो_state अणु
	अक्षर *buf;
	loff_t pos;
	माप_प्रकार count;
पूर्ण;

अटल sमाप_प्रकार find_dmi_entry(काष्ठा dmi_sysfs_entry *entry,
			      dmi_callback callback, व्योम *निजी)
अणु
	काष्ठा find_dmi_data data = अणु
		.entry = entry,
		.callback = callback,
		.निजी = निजी,
		.instance_countकरोwn = entry->instance,
		.ret = -EIO,  /* To संकेत the entry disappeared */
	पूर्ण;
	पूर्णांक ret;

	ret = dmi_walk(find_dmi_entry_helper, &data);
	/* This shouldn't happen, but just in हाल. */
	अगर (ret)
		वापस -EINVAL;
	वापस data.ret;
पूर्ण

/*
 * Calculate and वापस the byte length of the dmi entry identअगरied by
 * dh.  This includes both the क्रमmatted portion as well as the
 * unक्रमmatted string space, including the two trailing nul अक्षरacters.
 */
अटल माप_प्रकार dmi_entry_length(स्थिर काष्ठा dmi_header *dh)
अणु
	स्थिर अक्षर *p = (स्थिर अक्षर *)dh;

	p += dh->length;

	जबतक (p[0] || p[1])
		p++;

	वापस 2 + p - (स्थिर अक्षर *)dh;
पूर्ण

/*************************************************
 * Support bits क्रम specialized DMI entry support
 *************************************************/
काष्ठा dmi_entry_attr_show_data अणु
	काष्ठा attribute *attr;
	अक्षर *buf;
पूर्ण;

अटल sमाप_प्रकार dmi_entry_attr_show_helper(काष्ठा dmi_sysfs_entry *entry,
					  स्थिर काष्ठा dmi_header *dh,
					  व्योम *_data)
अणु
	काष्ठा dmi_entry_attr_show_data *data = _data;
	काष्ठा dmi_sysfs_mapped_attribute *attr;

	attr = container_of(data->attr,
			    काष्ठा dmi_sysfs_mapped_attribute, attr);
	वापस attr->show(entry, dh, data->buf);
पूर्ण

अटल sमाप_प्रकार dmi_entry_attr_show(काष्ठा kobject *kobj,
				   काष्ठा attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा dmi_entry_attr_show_data data = अणु
		.attr = attr,
		.buf  = buf,
	पूर्ण;
	/* Find the entry according to our parent and call the
	 * normalized show method hanging off of the attribute */
	वापस find_dmi_entry(to_entry(kobj->parent),
			      dmi_entry_attr_show_helper, &data);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops dmi_sysfs_specialize_attr_ops = अणु
	.show = dmi_entry_attr_show,
पूर्ण;

/*************************************************
 * Specialized DMI entry support.
 *************************************************/

/*** Type 15 - System Event Table ***/

#घोषणा DMI_SEL_ACCESS_METHOD_IO8	0x00
#घोषणा DMI_SEL_ACCESS_METHOD_IO2x8	0x01
#घोषणा DMI_SEL_ACCESS_METHOD_IO16	0x02
#घोषणा DMI_SEL_ACCESS_METHOD_PHYS32	0x03
#घोषणा DMI_SEL_ACCESS_METHOD_GPNV	0x04

काष्ठा dmi_प्रणाली_event_log अणु
	काष्ठा dmi_header header;
	u16	area_length;
	u16	header_start_offset;
	u16	data_start_offset;
	u8	access_method;
	u8	status;
	u32	change_token;
	जोड़ अणु
		काष्ठा अणु
			u16 index_addr;
			u16 data_addr;
		पूर्ण io;
		u32	phys_addr32;
		u16	gpnv_handle;
		u32	access_method_address;
	पूर्ण;
	u8	header_क्रमmat;
	u8	type_descriptors_supported_count;
	u8	per_log_type_descriptor_length;
	u8	supported_log_type_descriptos[];
पूर्ण __packed;

#घोषणा DMI_SYSFS_SEL_FIELD(_field) \
अटल sमाप_प्रकार dmi_sysfs_sel_##_field(काष्ठा dmi_sysfs_entry *entry, \
				      स्थिर काष्ठा dmi_header *dh, \
				      अक्षर *buf) \
अणु \
	काष्ठा dmi_प्रणाली_event_log sel; \
	अगर (माप(sel) > dmi_entry_length(dh)) \
		वापस -EIO; \
	स_नकल(&sel, dh, माप(sel)); \
	वापस प्र_लिखो(buf, "%u\n", sel._field); \
पूर्ण \
अटल DMI_SYSFS_MAPPED_ATTR(sel, _field)

DMI_SYSFS_SEL_FIELD(area_length);
DMI_SYSFS_SEL_FIELD(header_start_offset);
DMI_SYSFS_SEL_FIELD(data_start_offset);
DMI_SYSFS_SEL_FIELD(access_method);
DMI_SYSFS_SEL_FIELD(status);
DMI_SYSFS_SEL_FIELD(change_token);
DMI_SYSFS_SEL_FIELD(access_method_address);
DMI_SYSFS_SEL_FIELD(header_क्रमmat);
DMI_SYSFS_SEL_FIELD(type_descriptors_supported_count);
DMI_SYSFS_SEL_FIELD(per_log_type_descriptor_length);

अटल काष्ठा attribute *dmi_sysfs_sel_attrs[] = अणु
	&dmi_sysfs_attr_sel_area_length.attr,
	&dmi_sysfs_attr_sel_header_start_offset.attr,
	&dmi_sysfs_attr_sel_data_start_offset.attr,
	&dmi_sysfs_attr_sel_access_method.attr,
	&dmi_sysfs_attr_sel_status.attr,
	&dmi_sysfs_attr_sel_change_token.attr,
	&dmi_sysfs_attr_sel_access_method_address.attr,
	&dmi_sysfs_attr_sel_header_क्रमmat.attr,
	&dmi_sysfs_attr_sel_type_descriptors_supported_count.attr,
	&dmi_sysfs_attr_sel_per_log_type_descriptor_length.attr,
	शून्य,
पूर्ण;


अटल काष्ठा kobj_type dmi_प्रणाली_event_log_ktype = अणु
	.release = dmi_entry_मुक्त,
	.sysfs_ops = &dmi_sysfs_specialize_attr_ops,
	.शेष_attrs = dmi_sysfs_sel_attrs,
पूर्ण;

प्रकार u8 (*sel_io_पढ़ोer)(स्थिर काष्ठा dmi_प्रणाली_event_log *sel,
			    loff_t offset);

अटल DEFINE_MUTEX(io_port_lock);

अटल u8 पढ़ो_sel_8bit_indexed_io(स्थिर काष्ठा dmi_प्रणाली_event_log *sel,
				   loff_t offset)
अणु
	u8 ret;

	mutex_lock(&io_port_lock);
	outb((u8)offset, sel->io.index_addr);
	ret = inb(sel->io.data_addr);
	mutex_unlock(&io_port_lock);
	वापस ret;
पूर्ण

अटल u8 पढ़ो_sel_2x8bit_indexed_io(स्थिर काष्ठा dmi_प्रणाली_event_log *sel,
				     loff_t offset)
अणु
	u8 ret;

	mutex_lock(&io_port_lock);
	outb((u8)offset, sel->io.index_addr);
	outb((u8)(offset >> 8), sel->io.index_addr + 1);
	ret = inb(sel->io.data_addr);
	mutex_unlock(&io_port_lock);
	वापस ret;
पूर्ण

अटल u8 पढ़ो_sel_16bit_indexed_io(स्थिर काष्ठा dmi_प्रणाली_event_log *sel,
				    loff_t offset)
अणु
	u8 ret;

	mutex_lock(&io_port_lock);
	outw((u16)offset, sel->io.index_addr);
	ret = inb(sel->io.data_addr);
	mutex_unlock(&io_port_lock);
	वापस ret;
पूर्ण

अटल sel_io_पढ़ोer sel_io_पढ़ोers[] = अणु
	[DMI_SEL_ACCESS_METHOD_IO8]	= पढ़ो_sel_8bit_indexed_io,
	[DMI_SEL_ACCESS_METHOD_IO2x8]	= पढ़ो_sel_2x8bit_indexed_io,
	[DMI_SEL_ACCESS_METHOD_IO16]	= पढ़ो_sel_16bit_indexed_io,
पूर्ण;

अटल sमाप_प्रकार dmi_sel_raw_पढ़ो_io(काष्ठा dmi_sysfs_entry *entry,
				   स्थिर काष्ठा dmi_प्रणाली_event_log *sel,
				   अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	sमाप_प्रकार wrote = 0;

	sel_io_पढ़ोer io_पढ़ोer = sel_io_पढ़ोers[sel->access_method];

	जबतक (count && pos < sel->area_length) अणु
		count--;
		*(buf++) = io_पढ़ोer(sel, pos++);
		wrote++;
	पूर्ण

	वापस wrote;
पूर्ण

अटल sमाप_प्रकार dmi_sel_raw_पढ़ो_phys32(काष्ठा dmi_sysfs_entry *entry,
				       स्थिर काष्ठा dmi_प्रणाली_event_log *sel,
				       अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	u8 __iomem *mapped;
	sमाप_प्रकार wrote = 0;

	mapped = dmi_remap(sel->access_method_address, sel->area_length);
	अगर (!mapped)
		वापस -EIO;

	जबतक (count && pos < sel->area_length) अणु
		count--;
		*(buf++) = पढ़ोb(mapped + pos++);
		wrote++;
	पूर्ण

	dmi_unmap(mapped);
	वापस wrote;
पूर्ण

अटल sमाप_प्रकार dmi_sel_raw_पढ़ो_helper(काष्ठा dmi_sysfs_entry *entry,
				       स्थिर काष्ठा dmi_header *dh,
				       व्योम *_state)
अणु
	काष्ठा dmi_पढ़ो_state *state = _state;
	काष्ठा dmi_प्रणाली_event_log sel;

	अगर (माप(sel) > dmi_entry_length(dh))
		वापस -EIO;

	स_नकल(&sel, dh, माप(sel));

	चयन (sel.access_method) अणु
	हाल DMI_SEL_ACCESS_METHOD_IO8:
	हाल DMI_SEL_ACCESS_METHOD_IO2x8:
	हाल DMI_SEL_ACCESS_METHOD_IO16:
		वापस dmi_sel_raw_पढ़ो_io(entry, &sel, state->buf,
					   state->pos, state->count);
	हाल DMI_SEL_ACCESS_METHOD_PHYS32:
		वापस dmi_sel_raw_पढ़ो_phys32(entry, &sel, state->buf,
					       state->pos, state->count);
	हाल DMI_SEL_ACCESS_METHOD_GPNV:
		pr_info("dmi-sysfs: GPNV support missing.\n");
		वापस -EIO;
	शेष:
		pr_info("dmi-sysfs: Unknown access method %02x\n",
			sel.access_method);
		वापस -EIO;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार dmi_sel_raw_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr,
				अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	काष्ठा dmi_sysfs_entry *entry = to_entry(kobj->parent);
	काष्ठा dmi_पढ़ो_state state = अणु
		.buf = buf,
		.pos = pos,
		.count = count,
	पूर्ण;

	वापस find_dmi_entry(entry, dmi_sel_raw_पढ़ो_helper, &state);
पूर्ण

अटल काष्ठा bin_attribute dmi_sel_raw_attr = अणु
	.attr = अणु.name = "raw_event_log", .mode = 0400पूर्ण,
	.पढ़ो = dmi_sel_raw_पढ़ो,
पूर्ण;

अटल पूर्णांक dmi_प्रणाली_event_log(काष्ठा dmi_sysfs_entry *entry)
अणु
	पूर्णांक ret;

	entry->child = kzalloc(माप(*entry->child), GFP_KERNEL);
	अगर (!entry->child)
		वापस -ENOMEM;
	ret = kobject_init_and_add(entry->child,
				   &dmi_प्रणाली_event_log_ktype,
				   &entry->kobj,
				   "system_event_log");
	अगर (ret)
		जाओ out_मुक्त;

	ret = sysfs_create_bin_file(entry->child, &dmi_sel_raw_attr);
	अगर (ret)
		जाओ out_del;

	वापस 0;

out_del:
	kobject_del(entry->child);
out_मुक्त:
	kमुक्त(entry->child);
	वापस ret;
पूर्ण

/*************************************************
 * Generic DMI entry support.
 *************************************************/

अटल sमाप_प्रकार dmi_sysfs_entry_length(काष्ठा dmi_sysfs_entry *entry, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", entry->dh.length);
पूर्ण

अटल sमाप_प्रकार dmi_sysfs_entry_handle(काष्ठा dmi_sysfs_entry *entry, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", entry->dh.handle);
पूर्ण

अटल sमाप_प्रकार dmi_sysfs_entry_type(काष्ठा dmi_sysfs_entry *entry, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", entry->dh.type);
पूर्ण

अटल sमाप_प्रकार dmi_sysfs_entry_instance(काष्ठा dmi_sysfs_entry *entry,
					अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", entry->instance);
पूर्ण

अटल sमाप_प्रकार dmi_sysfs_entry_position(काष्ठा dmi_sysfs_entry *entry,
					अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", entry->position);
पूर्ण

अटल DMI_SYSFS_ATTR(entry, length);
अटल DMI_SYSFS_ATTR(entry, handle);
अटल DMI_SYSFS_ATTR(entry, type);
अटल DMI_SYSFS_ATTR(entry, instance);
अटल DMI_SYSFS_ATTR(entry, position);

अटल काष्ठा attribute *dmi_sysfs_entry_attrs[] = अणु
	&dmi_sysfs_attr_entry_length.attr,
	&dmi_sysfs_attr_entry_handle.attr,
	&dmi_sysfs_attr_entry_type.attr,
	&dmi_sysfs_attr_entry_instance.attr,
	&dmi_sysfs_attr_entry_position.attr,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार dmi_entry_raw_पढ़ो_helper(काष्ठा dmi_sysfs_entry *entry,
					 स्थिर काष्ठा dmi_header *dh,
					 व्योम *_state)
अणु
	काष्ठा dmi_पढ़ो_state *state = _state;
	माप_प्रकार entry_length;

	entry_length = dmi_entry_length(dh);

	वापस memory_पढ़ो_from_buffer(state->buf, state->count,
				       &state->pos, dh, entry_length);
पूर्ण

अटल sमाप_प्रकार dmi_entry_raw_पढ़ो(काष्ठा file *filp,
				  काष्ठा kobject *kobj,
				  काष्ठा bin_attribute *bin_attr,
				  अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	काष्ठा dmi_sysfs_entry *entry = to_entry(kobj);
	काष्ठा dmi_पढ़ो_state state = अणु
		.buf = buf,
		.pos = pos,
		.count = count,
	पूर्ण;

	वापस find_dmi_entry(entry, dmi_entry_raw_पढ़ो_helper, &state);
पूर्ण

अटल स्थिर काष्ठा bin_attribute dmi_entry_raw_attr = अणु
	.attr = अणु.name = "raw", .mode = 0400पूर्ण,
	.पढ़ो = dmi_entry_raw_पढ़ो,
पूर्ण;

अटल व्योम dmi_sysfs_entry_release(काष्ठा kobject *kobj)
अणु
	काष्ठा dmi_sysfs_entry *entry = to_entry(kobj);

	spin_lock(&entry_list_lock);
	list_del(&entry->list);
	spin_unlock(&entry_list_lock);
	kमुक्त(entry);
पूर्ण

अटल काष्ठा kobj_type dmi_sysfs_entry_ktype = अणु
	.release = dmi_sysfs_entry_release,
	.sysfs_ops = &dmi_sysfs_attr_ops,
	.शेष_attrs = dmi_sysfs_entry_attrs,
पूर्ण;

अटल काष्ठा kset *dmi_kset;

/* Global count of all instances seen.  Only क्रम setup */
अटल पूर्णांक __initdata instance_counts[MAX_ENTRY_TYPE + 1];

/* Global positional count of all entries seen.  Only क्रम setup */
अटल पूर्णांक __initdata position_count;

अटल व्योम __init dmi_sysfs_रेजिस्टर_handle(स्थिर काष्ठा dmi_header *dh,
					     व्योम *_ret)
अणु
	काष्ठा dmi_sysfs_entry *entry;
	पूर्णांक *ret = _ret;

	/* If a previous entry saw an error, लघु circuit */
	अगर (*ret)
		वापस;

	/* Allocate and रेजिस्टर a new entry पूर्णांकo the entries set */
	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		*ret = -ENOMEM;
		वापस;
	पूर्ण

	/* Set the key */
	स_नकल(&entry->dh, dh, माप(*dh));
	entry->instance = instance_counts[dh->type]++;
	entry->position = position_count++;

	entry->kobj.kset = dmi_kset;
	*ret = kobject_init_and_add(&entry->kobj, &dmi_sysfs_entry_ktype, शून्य,
				    "%d-%d", dh->type, entry->instance);

	अगर (*ret) अणु
		kमुक्त(entry);
		वापस;
	पूर्ण

	/* Thपढ़ो on the global list क्रम cleanup */
	spin_lock(&entry_list_lock);
	list_add_tail(&entry->list, &entry_list);
	spin_unlock(&entry_list_lock);

	/* Handle specializations by type */
	चयन (dh->type) अणु
	हाल DMI_ENTRY_SYSTEM_EVENT_LOG:
		*ret = dmi_प्रणाली_event_log(entry);
		अवरोध;
	शेष:
		/* No specialization */
		अवरोध;
	पूर्ण
	अगर (*ret)
		जाओ out_err;

	/* Create the raw binary file to access the entry */
	*ret = sysfs_create_bin_file(&entry->kobj, &dmi_entry_raw_attr);
	अगर (*ret)
		जाओ out_err;

	वापस;
out_err:
	kobject_put(entry->child);
	kobject_put(&entry->kobj);
	वापस;
पूर्ण

अटल व्योम cleanup_entry_list(व्योम)
अणु
	काष्ठा dmi_sysfs_entry *entry, *next;

	/* No locks, we are on our way out */
	list_क्रम_each_entry_safe(entry, next, &entry_list, list) अणु
		kobject_put(entry->child);
		kobject_put(&entry->kobj);
	पूर्ण
पूर्ण

अटल पूर्णांक __init dmi_sysfs_init(व्योम)
अणु
	पूर्णांक error;
	पूर्णांक val;

	अगर (!dmi_kobj) अणु
		pr_debug("dmi-sysfs: dmi entry is absent.\n");
		error = -ENODATA;
		जाओ err;
	पूर्ण

	dmi_kset = kset_create_and_add("entries", शून्य, dmi_kobj);
	अगर (!dmi_kset) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	val = 0;
	error = dmi_walk(dmi_sysfs_रेजिस्टर_handle, &val);
	अगर (error)
		जाओ err;
	अगर (val) अणु
		error = val;
		जाओ err;
	पूर्ण

	pr_debug("dmi-sysfs: loaded.\n");

	वापस 0;
err:
	cleanup_entry_list();
	kset_unरेजिस्टर(dmi_kset);
	वापस error;
पूर्ण

/* clean up everything. */
अटल व्योम __निकास dmi_sysfs_निकास(व्योम)
अणु
	pr_debug("dmi-sysfs: unloading.\n");
	cleanup_entry_list();
	kset_unरेजिस्टर(dmi_kset);
पूर्ण

module_init(dmi_sysfs_init);
module_निकास(dmi_sysfs_निकास);

MODULE_AUTHOR("Mike Waychison <mikew@google.com>");
MODULE_DESCRIPTION("DMI sysfs support");
MODULE_LICENSE("GPL");
