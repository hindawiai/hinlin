<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/ide.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/seq_file.h>

#समावेश "ide-disk.h"

अटल पूर्णांक smart_enable(ide_drive_t *drive)
अणु
	काष्ठा ide_cmd cmd;
	काष्ठा ide_taskfile *tf = &cmd.tf;

	स_रखो(&cmd, 0, माप(cmd));
	tf->feature = ATA_SMART_ENABLE;
	tf->lbam    = ATA_SMART_LBAM_PASS;
	tf->lbah    = ATA_SMART_LBAH_PASS;
	tf->command = ATA_CMD_SMART;
	cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;

	वापस ide_no_data_taskfile(drive, &cmd);
पूर्ण

अटल पूर्णांक get_smart_data(ide_drive_t *drive, u8 *buf, u8 sub_cmd)
अणु
	काष्ठा ide_cmd cmd;
	काष्ठा ide_taskfile *tf = &cmd.tf;

	स_रखो(&cmd, 0, माप(cmd));
	tf->feature = sub_cmd;
	tf->nsect   = 0x01;
	tf->lbam    = ATA_SMART_LBAM_PASS;
	tf->lbah    = ATA_SMART_LBAH_PASS;
	tf->command = ATA_CMD_SMART;
	cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;
	cmd.protocol = ATA_PROT_PIO;

	वापस ide_raw_taskfile(drive, &cmd, buf, 1);
पूर्ण

अटल पूर्णांक idedisk_cache_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ide_drive_t	*drive = (ide_drive_t *) m->निजी;

	अगर (drive->dev_flags & IDE_DFLAG_ID_READ)
		seq_म_लिखो(m, "%i\n", drive->id[ATA_ID_BUF_SIZE] / 2);
	अन्यथा
		seq_म_लिखो(m, "(none)\n");
	वापस 0;
पूर्ण

अटल पूर्णांक idedisk_capacity_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ide_drive_t*drive = (ide_drive_t *)m->निजी;

	seq_म_लिखो(m, "%llu\n", (दीर्घ दीर्घ)ide_gd_capacity(drive));
	वापस 0;
पूर्ण

अटल पूर्णांक __idedisk_proc_show(काष्ठा seq_file *m, ide_drive_t *drive, u8 sub_cmd)
अणु
	u8 *buf;

	buf = kदो_स्मृति(SECTOR_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	(व्योम)smart_enable(drive);

	अगर (get_smart_data(drive, buf, sub_cmd) == 0) अणु
		__le16 *val = (__le16 *)buf;
		पूर्णांक i;

		क्रम (i = 0; i < SECTOR_SIZE / 2; i++) अणु
			seq_म_लिखो(m, "%04x%c", le16_to_cpu(val[i]),
					(i % 8) == 7 ? '\n' : ' ');
		पूर्ण
	पूर्ण
	kमुक्त(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक idedisk_sv_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस __idedisk_proc_show(m, m->निजी, ATA_SMART_READ_VALUES);
पूर्ण

अटल पूर्णांक idedisk_st_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस __idedisk_proc_show(m, m->निजी, ATA_SMART_READ_THRESHOLDS);
पूर्ण

ide_proc_entry_t ide_disk_proc[] = अणु
	अणु "cache",	  S_IFREG|S_IRUGO, idedisk_cache_proc_show	पूर्ण,
	अणु "capacity",	  S_IFREG|S_IRUGO, idedisk_capacity_proc_show	पूर्ण,
	अणु "geometry",	  S_IFREG|S_IRUGO, ide_geometry_proc_show	पूर्ण,
	अणु "smart_values", S_IFREG|S_IRUSR, idedisk_sv_proc_show		पूर्ण,
	अणु "smart_thresholds", S_IFREG|S_IRUSR, idedisk_st_proc_show	पूर्ण,
	अणुपूर्ण
पूर्ण;

ide_devset_rw_field(bios_cyl, bios_cyl);
ide_devset_rw_field(bios_head, bios_head);
ide_devset_rw_field(bios_sect, bios_sect);
ide_devset_rw_field(failures, failures);
ide_devset_rw_field(lun, lun);
ide_devset_rw_field(max_failures, max_failures);

स्थिर काष्ठा ide_proc_devset ide_disk_settings[] = अणु
	IDE_PROC_DEVSET(acoustic,	0,   254),
	IDE_PROC_DEVSET(address,	0,     2),
	IDE_PROC_DEVSET(bios_cyl,	0, 65535),
	IDE_PROC_DEVSET(bios_head,	0,   255),
	IDE_PROC_DEVSET(bios_sect,	0,    63),
	IDE_PROC_DEVSET(failures,	0, 65535),
	IDE_PROC_DEVSET(lun,		0,     7),
	IDE_PROC_DEVSET(max_failures,	0, 65535),
	IDE_PROC_DEVSET(multcount,	0,    16),
	IDE_PROC_DEVSET(nowerr,		0,     1),
	IDE_PROC_DEVSET(wcache,		0,     1),
	अणु शून्य पूर्ण,
पूर्ण;
