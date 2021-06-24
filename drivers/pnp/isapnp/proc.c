<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ISA Plug & Play support
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/module.h>
#समावेश <linux/isapnp.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/init.h>
#समावेश <linux/uaccess.h>

बाह्य काष्ठा pnp_protocol isapnp_protocol;

अटल काष्ठा proc_dir_entry *isapnp_proc_bus_dir = शून्य;

अटल loff_t isapnp_proc_bus_lseek(काष्ठा file *file, loff_t off, पूर्णांक whence)
अणु
	वापस fixed_size_llseek(file, off, whence, 256);
पूर्ण

अटल sमाप_प्रकार isapnp_proc_bus_पढ़ो(काष्ठा file *file, अक्षर __user * buf,
				    माप_प्रकार nbytes, loff_t * ppos)
अणु
	काष्ठा pnp_dev *dev = PDE_DATA(file_inode(file));
	पूर्णांक pos = *ppos;
	पूर्णांक cnt, size = 256;

	अगर (pos >= size)
		वापस 0;
	अगर (nbytes >= size)
		nbytes = size;
	अगर (pos + nbytes > size)
		nbytes = size - pos;
	cnt = nbytes;

	अगर (!access_ok(buf, cnt))
		वापस -EINVAL;

	isapnp_cfg_begin(dev->card->number, dev->number);
	क्रम (; pos < 256 && cnt > 0; pos++, buf++, cnt--) अणु
		अचिन्हित अक्षर val;
		val = isapnp_पढ़ो_byte(pos);
		__put_user(val, buf);
	पूर्ण
	isapnp_cfg_end();

	*ppos = pos;
	वापस nbytes;
पूर्ण

अटल स्थिर काष्ठा proc_ops isapnp_proc_bus_proc_ops = अणु
	.proc_lseek	= isapnp_proc_bus_lseek,
	.proc_पढ़ो	= isapnp_proc_bus_पढ़ो,
पूर्ण;

अटल पूर्णांक isapnp_proc_attach_device(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_card *bus = dev->card;
	काष्ठा proc_dir_entry *de, *e;
	अक्षर name[16];

	अगर (!(de = bus->procdir)) अणु
		प्र_लिखो(name, "%02x", bus->number);
		de = bus->procdir = proc_सूची_गढ़ो(name, isapnp_proc_bus_dir);
		अगर (!de)
			वापस -ENOMEM;
	पूर्ण
	प्र_लिखो(name, "%02x", dev->number);
	e = dev->procent = proc_create_data(name, S_IFREG | S_IRUGO, de,
					    &isapnp_proc_bus_proc_ops, dev);
	अगर (!e)
		वापस -ENOMEM;
	proc_set_size(e, 256);
	वापस 0;
पूर्ण

पूर्णांक __init isapnp_proc_init(व्योम)
अणु
	काष्ठा pnp_dev *dev;

	isapnp_proc_bus_dir = proc_सूची_गढ़ो("bus/isapnp", शून्य);
	protocol_क्रम_each_dev(&isapnp_protocol, dev) अणु
		isapnp_proc_attach_device(dev);
	पूर्ण
	वापस 0;
पूर्ण
