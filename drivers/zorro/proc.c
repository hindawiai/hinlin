<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Procfs पूर्णांकerface क्रम the Zorro bus.
 *
 *	Copyright (C) 1998-2003 Geert Uytterhoeven
 *
 *	Heavily based on the procfs पूर्णांकerface क्रम the PCI bus, which is
 *
 *	Copyright (C) 1997, 1998 Martin Mares <mj@atrey.karlin.mff.cuni.cz>
 */

#समावेश <linux/types.h>
#समावेश <linux/zorro.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/setup.h>

अटल loff_t
proc_bus_zorro_lseek(काष्ठा file *file, loff_t off, पूर्णांक whence)
अणु
	वापस fixed_size_llseek(file, off, whence, माप(काष्ठा ConfigDev));
पूर्ण

अटल sमाप_प्रकार
proc_bus_zorro_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा zorro_dev *z = PDE_DATA(file_inode(file));
	काष्ठा ConfigDev cd;
	loff_t pos = *ppos;

	अगर (pos >= माप(काष्ठा ConfigDev))
		वापस 0;
	अगर (nbytes >= माप(काष्ठा ConfigDev))
		nbytes = माप(काष्ठा ConfigDev);
	अगर (pos + nbytes > माप(काष्ठा ConfigDev))
		nbytes = माप(काष्ठा ConfigDev) - pos;

	/* Conकाष्ठा a ConfigDev */
	स_रखो(&cd, 0, माप(cd));
	cd.cd_Rom = z->rom;
	cd.cd_SlotAddr = cpu_to_be16(z->slotaddr);
	cd.cd_SlotSize = cpu_to_be16(z->slotsize);
	cd.cd_BoardAddr = cpu_to_be32(zorro_resource_start(z));
	cd.cd_BoardSize = cpu_to_be32(zorro_resource_len(z));

	अगर (copy_to_user(buf, (व्योम *)&cd + pos, nbytes))
		वापस -EFAULT;
	*ppos += nbytes;

	वापस nbytes;
पूर्ण

अटल स्थिर काष्ठा proc_ops bus_zorro_proc_ops = अणु
	.proc_lseek	= proc_bus_zorro_lseek,
	.proc_पढ़ो	= proc_bus_zorro_पढ़ो,
पूर्ण;

अटल व्योम * zorro_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	वापस (*pos < zorro_num_स्वतःcon) ? pos : शून्य;
पूर्ण

अटल व्योम * zorro_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस (*pos < zorro_num_स्वतःcon) ? pos : शून्य;
पूर्ण

अटल व्योम zorro_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक zorro_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित पूर्णांक slot = *(loff_t *)v;
	काष्ठा zorro_dev *z = &zorro_स्वतःcon[slot];

	seq_म_लिखो(m, "%02x\t%08x\t%08lx\t%08lx\t%02x\n", slot, z->id,
		   (अचिन्हित दीर्घ)zorro_resource_start(z),
		   (अचिन्हित दीर्घ)zorro_resource_len(z),
		   z->rom.er_Type);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations zorro_devices_seq_ops = अणु
	.start = zorro_seq_start,
	.next  = zorro_seq_next,
	.stop  = zorro_seq_stop,
	.show  = zorro_seq_show,
पूर्ण;

अटल काष्ठा proc_dir_entry *proc_bus_zorro_dir;

अटल पूर्णांक __init zorro_proc_attach_device(अचिन्हित पूर्णांक slot)
अणु
	काष्ठा proc_dir_entry *entry;
	अक्षर name[4];

	प्र_लिखो(name, "%02x", slot);
	entry = proc_create_data(name, 0, proc_bus_zorro_dir,
				 &bus_zorro_proc_ops,
				 &zorro_स्वतःcon[slot]);
	अगर (!entry)
		वापस -ENOMEM;
	proc_set_size(entry, माप(काष्ठा zorro_dev));
	वापस 0;
पूर्ण

अटल पूर्णांक __init zorro_proc_init(व्योम)
अणु
	अचिन्हित पूर्णांक slot;

	अगर (MACH_IS_AMIGA && AMIGAHW_PRESENT(ZORRO)) अणु
		proc_bus_zorro_dir = proc_सूची_गढ़ो("bus/zorro", शून्य);
		proc_create_seq("devices", 0, proc_bus_zorro_dir,
			    &zorro_devices_seq_ops);
		क्रम (slot = 0; slot < zorro_num_स्वतःcon; slot++)
			zorro_proc_attach_device(slot);
	पूर्ण
	वापस 0;
पूर्ण

device_initcall(zorro_proc_init);
