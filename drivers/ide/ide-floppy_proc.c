<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/ide.h>
#समावेश <linux/seq_file.h>

#समावेश "ide-floppy.h"

अटल पूर्णांक idefloppy_capacity_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ide_drive_t*drive = (ide_drive_t *)m->निजी;

	seq_म_लिखो(m, "%llu\n", (दीर्घ दीर्घ)ide_gd_capacity(drive));
	वापस 0;
पूर्ण

ide_proc_entry_t ide_floppy_proc[] = अणु
	अणु "capacity",	S_IFREG|S_IRUGO, idefloppy_capacity_proc_show	पूर्ण,
	अणु "geometry",	S_IFREG|S_IRUGO, ide_geometry_proc_show		पूर्ण,
	अणुपूर्ण
पूर्ण;

ide_devset_rw_field(bios_cyl, bios_cyl);
ide_devset_rw_field(bios_head, bios_head);
ide_devset_rw_field(bios_sect, bios_sect);
ide_devset_rw_field(ticks, pc_delay);

स्थिर काष्ठा ide_proc_devset ide_floppy_settings[] = अणु
	IDE_PROC_DEVSET(bios_cyl,  0, 1023),
	IDE_PROC_DEVSET(bios_head, 0,  255),
	IDE_PROC_DEVSET(bios_sect, 0,   63),
	IDE_PROC_DEVSET(ticks,	   0,  255),
	अणु शून्य पूर्ण,
पूर्ण;
