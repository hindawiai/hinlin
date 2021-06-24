<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1997-1998	Mark Lord
 *  Copyright (C) 2003		Red Hat
 *
 *  Some code was moved here from ide.c, see it क्रम original copyrights.
 */

/*
 * This is the /proc/ide/ fileप्रणाली implementation.
 *
 * Drive/Driver settings can be retrieved by पढ़ोing the drive's
 * "settings" files.  e.g.    "cat /proc/ide0/hda/settings"
 * To ग_लिखो a new value "val" पूर्णांकo a specअगरic setting "name", use:
 *   echo "name:val" >/proc/ide/ide0/hda/settings
 */

#समावेश <linux/module.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mm.h>
#समावेश <linux/pci.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/ide.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>

अटल काष्ठा proc_dir_entry *proc_ide_root;

अटल पूर्णांक ide_imodel_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ide_hwअगर_t	*hwअगर = (ide_hwअगर_t *) m->निजी;
	स्थिर अक्षर	*name;

	चयन (hwअगर->chipset) अणु
	हाल ide_generic:	name = "generic";	अवरोध;
	हाल ide_pci:		name = "pci";		अवरोध;
	हाल ide_cmd640:	name = "cmd640";	अवरोध;
	हाल ide_dtc2278:	name = "dtc2278";	अवरोध;
	हाल ide_ali14xx:	name = "ali14xx";	अवरोध;
	हाल ide_qd65xx:	name = "qd65xx";	अवरोध;
	हाल ide_umc8672:	name = "umc8672";	अवरोध;
	हाल ide_ht6560b:	name = "ht6560b";	अवरोध;
	हाल ide_4drives:	name = "4drives";	अवरोध;
	हाल ide_pmac:		name = "mac-io";	अवरोध;
	हाल ide_au1xxx:	name = "au1xxx";	अवरोध;
	हाल ide_palm3710:      name = "palm3710";      अवरोध;
	हाल ide_acorn:		name = "acorn";		अवरोध;
	शेष:		name = "(unknown)";	अवरोध;
	पूर्ण
	seq_म_लिखो(m, "%s\n", name);
	वापस 0;
पूर्ण

अटल पूर्णांक ide_mate_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ide_hwअगर_t	*hwअगर = (ide_hwअगर_t *) m->निजी;

	अगर (hwअगर && hwअगर->mate)
		seq_म_लिखो(m, "%s\n", hwअगर->mate->name);
	अन्यथा
		seq_म_लिखो(m, "(none)\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ide_channel_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ide_hwअगर_t	*hwअगर = (ide_hwअगर_t *) m->निजी;

	seq_म_लिखो(m, "%c\n", hwअगर->channel ? '1' : '0');
	वापस 0;
पूर्ण

अटल पूर्णांक ide_identअगरy_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ide_drive_t *drive = (ide_drive_t *)m->निजी;
	u8 *buf;

	अगर (!drive) अणु
		seq_अ_दो(m, '\n');
		वापस 0;
	पूर्ण

	buf = kदो_स्मृति(SECTOR_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	अगर (taskfile_lib_get_identअगरy(drive, buf) == 0) अणु
		__le16 *val = (__le16 *)buf;
		पूर्णांक i;

		क्रम (i = 0; i < SECTOR_SIZE / 2; i++) अणु
			seq_म_लिखो(m, "%04x%c", le16_to_cpu(val[i]),
					(i % 8) == 7 ? '\n' : ' ');
		पूर्ण
	पूर्ण अन्यथा
		seq_अ_दो(m, buf[0]);
	kमुक्त(buf);
	वापस 0;
पूर्ण

/**
 *	ide_find_setting	-	find a specअगरic setting
 *	@st: setting table poपूर्णांकer
 *	@name: setting name
 *
 *	Scan's the setting table क्रम a matching entry and वापसs
 *	this or शून्य अगर no entry is found. The caller must hold the
 *	setting semaphore
 */

अटल
स्थिर काष्ठा ide_proc_devset *ide_find_setting(स्थिर काष्ठा ide_proc_devset *st,
					       अक्षर *name)
अणु
	जबतक (st->name) अणु
		अगर (म_भेद(st->name, name) == 0)
			अवरोध;
		st++;
	पूर्ण
	वापस st->name ? st : शून्य;
पूर्ण

/**
 *	ide_पढ़ो_setting	-	पढ़ो an IDE setting
 *	@drive: drive to पढ़ो from
 *	@setting: drive setting
 *
 *	Read a drive setting and वापस the value. The caller
 *	must hold the ide_setting_mtx when making this call.
 *
 *	BUGS: the data वापस and error are the same वापस value
 *	so an error -EINVAL and true वापस of the same value cannot
 *	be told apart
 */

अटल पूर्णांक ide_पढ़ो_setting(ide_drive_t *drive,
			    स्थिर काष्ठा ide_proc_devset *setting)
अणु
	स्थिर काष्ठा ide_devset *ds = setting->setting;
	पूर्णांक val = -EINVAL;

	अगर (ds->get)
		val = ds->get(drive);

	वापस val;
पूर्ण

/**
 *	ide_ग_लिखो_setting	-	पढ़ो an IDE setting
 *	@drive: drive to पढ़ो from
 *	@setting: drive setting
 *	@val: value
 *
 *	Write a drive setting अगर it is possible. The caller
 *	must hold the ide_setting_mtx when making this call.
 *
 *	BUGS: the data वापस and error are the same वापस value
 *	so an error -EINVAL and true वापस of the same value cannot
 *	be told apart
 *
 *	FIXME:  This should be changed to enqueue a special request
 *	to the driver to change settings, and then रुको on a sema क्रम completion.
 *	The current scheme of polling is kludgy, though safe enough.
 */

अटल पूर्णांक ide_ग_लिखो_setting(ide_drive_t *drive,
			     स्थिर काष्ठा ide_proc_devset *setting, पूर्णांक val)
अणु
	स्थिर काष्ठा ide_devset *ds = setting->setting;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	अगर (!ds->set)
		वापस -EPERM;
	अगर ((ds->flags & DS_SYNC)
	    && (val < setting->min || val > setting->max))
		वापस -EINVAL;
	वापस ide_devset_execute(drive, ds, val);
पूर्ण

ide_devset_get(xfer_rate, current_speed);

अटल पूर्णांक set_xfer_rate (ide_drive_t *drive, पूर्णांक arg)
अणु
	काष्ठा ide_cmd cmd;

	अगर (arg < XFER_PIO_0 || arg > XFER_UDMA_6)
		वापस -EINVAL;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.tf.command = ATA_CMD_SET_FEATURES;
	cmd.tf.feature = SETFEATURES_XFER;
	cmd.tf.nsect   = (u8)arg;
	cmd.valid.out.tf = IDE_VALID_FEATURE | IDE_VALID_NSECT;
	cmd.valid.in.tf  = IDE_VALID_NSECT;
	cmd.tf_flags   = IDE_TFLAG_SET_XFER;

	वापस ide_no_data_taskfile(drive, &cmd);
पूर्ण

ide_devset_rw(current_speed, xfer_rate);
ide_devset_rw_field(init_speed, init_speed);
ide_devset_rw_flag(nice1, IDE_DFLAG_NICE1);
ide_devset_ro_field(number, dn);

अटल स्थिर काष्ठा ide_proc_devset ide_generic_settings[] = अणु
	IDE_PROC_DEVSET(current_speed, 0, 70),
	IDE_PROC_DEVSET(init_speed, 0, 70),
	IDE_PROC_DEVSET(io_32bit,  0, 1 + (SUPPORT_VLB_SYNC << 1)),
	IDE_PROC_DEVSET(keepsettings, 0, 1),
	IDE_PROC_DEVSET(nice1, 0, 1),
	IDE_PROC_DEVSET(number, 0, 3),
	IDE_PROC_DEVSET(pio_mode, 0, 255),
	IDE_PROC_DEVSET(unmaskirq, 0, 1),
	IDE_PROC_DEVSET(using_dma, 0, 1),
	अणु शून्य पूर्ण,
पूर्ण;

अटल व्योम proc_ide_settings_warn(व्योम)
अणु
	prपूर्णांकk_once(KERN_WARNING "Warning: /proc/ide/hd?/settings interface is "
			    "obsolete, and will be removed soon!\n");
पूर्ण

अटल पूर्णांक ide_settings_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	स्थिर काष्ठा ide_proc_devset *setting, *g, *d;
	स्थिर काष्ठा ide_devset *ds;
	ide_drive_t	*drive = (ide_drive_t *) m->निजी;
	पूर्णांक		rc, mul_factor, भाग_factor;

	proc_ide_settings_warn();

	mutex_lock(&ide_setting_mtx);
	g = ide_generic_settings;
	d = drive->settings;
	seq_म_लिखो(m, "name\t\t\tvalue\t\tmin\t\tmax\t\tmode\n");
	seq_म_लिखो(m, "----\t\t\t-----\t\t---\t\t---\t\t----\n");
	जबतक (g->name || (d && d->name)) अणु
		/* पढ़ो settings in the alphabetical order */
		अगर (g->name && d && d->name) अणु
			अगर (म_भेद(d->name, g->name) < 0)
				setting = d++;
			अन्यथा
				setting = g++;
		पूर्ण अन्यथा अगर (d && d->name) अणु
			setting = d++;
		पूर्ण अन्यथा
			setting = g++;
		mul_factor = setting->mulf ? setting->mulf(drive) : 1;
		भाग_factor = setting->भागf ? setting->भागf(drive) : 1;
		seq_म_लिखो(m, "%-24s", setting->name);
		rc = ide_पढ़ो_setting(drive, setting);
		अगर (rc >= 0)
			seq_म_लिखो(m, "%-16d", rc * mul_factor / भाग_factor);
		अन्यथा
			seq_म_लिखो(m, "%-16s", "write-only");
		seq_म_लिखो(m, "%-16d%-16d", (setting->min * mul_factor + भाग_factor - 1) / भाग_factor, setting->max * mul_factor / भाग_factor);
		ds = setting->setting;
		अगर (ds->get)
			seq_म_लिखो(m, "r");
		अगर (ds->set)
			seq_म_लिखो(m, "w");
		seq_म_लिखो(m, "\n");
	पूर्ण
	mutex_unlock(&ide_setting_mtx);
	वापस 0;
पूर्ण

अटल पूर्णांक ide_settings_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ide_settings_proc_show, PDE_DATA(inode));
पूर्ण

#घोषणा MAX_LEN	30

अटल sमाप_प्रकार ide_settings_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				       माप_प्रकार count, loff_t *pos)
अणु
	ide_drive_t	*drive = PDE_DATA(file_inode(file));
	अक्षर		name[MAX_LEN + 1];
	पूर्णांक		क्रम_real = 0, mul_factor, भाग_factor;
	अचिन्हित दीर्घ	n;

	स्थिर काष्ठा ide_proc_devset *setting;
	अक्षर *buf, *s;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	proc_ide_settings_warn();

	अगर (count >= PAGE_SIZE)
		वापस -EINVAL;

	s = buf = (अक्षर *)__get_मुक्त_page(GFP_USER);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (copy_from_user(buf, buffer, count)) अणु
		मुक्त_page((अचिन्हित दीर्घ)buf);
		वापस -EFAULT;
	पूर्ण

	buf[count] = '\0';

	/*
	 * Skip over leading whitespace
	 */
	जबतक (count && है_खाली(*s)) अणु
		--count;
		++s;
	पूर्ण
	/*
	 * Do one full pass to verअगरy all parameters,
	 * then करो another to actually ग_लिखो the new settings.
	 */
	करो अणु
		अक्षर *p = s;
		n = count;
		जबतक (n > 0) अणु
			अचिन्हित val;
			अक्षर *q = p;

			जबतक (n > 0 && *p != ':') अणु
				--n;
				p++;
			पूर्ण
			अगर (*p != ':')
				जाओ parse_error;
			अगर (p - q > MAX_LEN)
				जाओ parse_error;
			स_नकल(name, q, p - q);
			name[p - q] = 0;

			अगर (n > 0) अणु
				--n;
				p++;
			पूर्ण अन्यथा
				जाओ parse_error;

			val = simple_म_से_अदीर्घ(p, &q, 10);
			n -= q - p;
			p = q;
			अगर (n > 0 && !है_खाली(*p))
				जाओ parse_error;
			जबतक (n > 0 && है_खाली(*p)) अणु
				--n;
				++p;
			पूर्ण

			mutex_lock(&ide_setting_mtx);
			/* generic settings first, then driver specअगरic ones */
			setting = ide_find_setting(ide_generic_settings, name);
			अगर (!setting) अणु
				अगर (drive->settings)
					setting = ide_find_setting(drive->settings, name);
				अगर (!setting) अणु
					mutex_unlock(&ide_setting_mtx);
					जाओ parse_error;
				पूर्ण
			पूर्ण
			अगर (क्रम_real) अणु
				mul_factor = setting->mulf ? setting->mulf(drive) : 1;
				भाग_factor = setting->भागf ? setting->भागf(drive) : 1;
				ide_ग_लिखो_setting(drive, setting, val * भाग_factor / mul_factor);
			पूर्ण
			mutex_unlock(&ide_setting_mtx);
		पूर्ण
	पूर्ण जबतक (!क्रम_real++);
	मुक्त_page((अचिन्हित दीर्घ)buf);
	वापस count;
parse_error:
	मुक्त_page((अचिन्हित दीर्घ)buf);
	prपूर्णांकk("%s(): parse error\n", __func__);
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा proc_ops ide_settings_proc_ops = अणु
	.proc_खोलो	= ide_settings_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= ide_settings_proc_ग_लिखो,
पूर्ण;

पूर्णांक ide_capacity_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "%llu\n", (दीर्घ दीर्घ)0x7fffffff);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_capacity_proc_show);

पूर्णांक ide_geometry_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ide_drive_t	*drive = (ide_drive_t *) m->निजी;

	seq_म_लिखो(m, "physical     %d/%d/%d\n",
			drive->cyl, drive->head, drive->sect);
	seq_म_लिखो(m, "logical      %d/%d/%d\n",
			drive->bios_cyl, drive->bios_head, drive->bios_sect);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ide_geometry_proc_show);

अटल पूर्णांक ide_dmodel_proc_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	ide_drive_t	*drive = (ide_drive_t *) seq->निजी;
	अक्षर		*m = (अक्षर *)&drive->id[ATA_ID_PROD];

	seq_म_लिखो(seq, "%.40s\n", m[0] ? m : "(none)");
	वापस 0;
पूर्ण

अटल पूर्णांक ide_driver_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ide_drive_t		*drive = (ide_drive_t *)m->निजी;
	काष्ठा device		*dev = &drive->gendev;
	काष्ठा ide_driver	*ide_drv;

	अगर (dev->driver) अणु
		ide_drv = to_ide_driver(dev->driver);
		seq_म_लिखो(m, "%s version %s\n",
				dev->driver->name, ide_drv->version);
	पूर्ण अन्यथा
		seq_म_लिखो(m, "ide-default version 0.9.newide\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ide_media_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ide_drive_t	*drive = (ide_drive_t *) m->निजी;
	स्थिर अक्षर	*media;

	चयन (drive->media) अणु
	हाल ide_disk:		media = "disk\n";	अवरोध;
	हाल ide_cdrom:		media = "cdrom\n";	अवरोध;
	हाल ide_tape:		media = "tape\n";	अवरोध;
	हाल ide_floppy:	media = "floppy\n";	अवरोध;
	हाल ide_optical:	media = "optical\n";	अवरोध;
	शेष:		media = "UNKNOWN\n";	अवरोध;
	पूर्ण
	seq_माला_दो(m, media);
	वापस 0;
पूर्ण

अटल पूर्णांक ide_media_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, ide_media_proc_show, PDE_DATA(inode));
पूर्ण

अटल स्थिर काष्ठा file_operations ide_media_proc_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= ide_media_proc_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल ide_proc_entry_t generic_drive_entries[] = अणु
	अणु "driver",	S_IFREG|S_IRUGO,	 ide_driver_proc_show	पूर्ण,
	अणु "identify",	S_IFREG|S_IRUSR,	 ide_identअगरy_proc_show	पूर्ण,
	अणु "media",	S_IFREG|S_IRUGO,	 ide_media_proc_show	पूर्ण,
	अणु "model",	S_IFREG|S_IRUGO,	 ide_dmodel_proc_show	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम ide_add_proc_entries(काष्ठा proc_dir_entry *dir, ide_proc_entry_t *p, व्योम *data)
अणु
	काष्ठा proc_dir_entry *ent;

	अगर (!dir || !p)
		वापस;
	जबतक (p->name != शून्य) अणु
		ent = proc_create_single_data(p->name, p->mode, dir, p->show, data);
		अगर (!ent) वापस;
		p++;
	पूर्ण
पूर्ण

अटल व्योम ide_हटाओ_proc_entries(काष्ठा proc_dir_entry *dir, ide_proc_entry_t *p)
अणु
	अगर (!dir || !p)
		वापस;
	जबतक (p->name != शून्य) अणु
		हटाओ_proc_entry(p->name, dir);
		p++;
	पूर्ण
पूर्ण

व्योम ide_proc_रेजिस्टर_driver(ide_drive_t *drive, काष्ठा ide_driver *driver)
अणु
	mutex_lock(&ide_setting_mtx);
	drive->settings = driver->proc_devsets(drive);
	mutex_unlock(&ide_setting_mtx);

	ide_add_proc_entries(drive->proc, driver->proc_entries(drive), drive);
पूर्ण

EXPORT_SYMBOL(ide_proc_रेजिस्टर_driver);

/**
 *	ide_proc_unरेजिस्टर_driver	-	हटाओ driver specअगरic data
 *	@drive: drive
 *	@driver: driver
 *
 *	Clean up the driver specअगरic /proc files and IDE settings
 *	क्रम a given drive.
 *
 *	Takes ide_setting_mtx.
 */

व्योम ide_proc_unरेजिस्टर_driver(ide_drive_t *drive, काष्ठा ide_driver *driver)
अणु
	ide_हटाओ_proc_entries(drive->proc, driver->proc_entries(drive));

	mutex_lock(&ide_setting_mtx);
	/*
	 * ide_setting_mtx protects both the settings list and the use
	 * of settings (we cannot take a setting out that is being used).
	 */
	drive->settings = शून्य;
	mutex_unlock(&ide_setting_mtx);
पूर्ण
EXPORT_SYMBOL(ide_proc_unरेजिस्टर_driver);

व्योम ide_proc_port_रेजिस्टर_devices(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा proc_dir_entry *ent;
	काष्ठा proc_dir_entry *parent = hwअगर->proc;
	ide_drive_t *drive;
	अक्षर name[64];
	पूर्णांक i;

	ide_port_क्रम_each_dev(i, drive, hwअगर) अणु
		अगर ((drive->dev_flags & IDE_DFLAG_PRESENT) == 0)
			जारी;

		drive->proc = proc_सूची_गढ़ो(drive->name, parent);
		अगर (drive->proc) अणु
			ide_add_proc_entries(drive->proc, generic_drive_entries, drive);
			proc_create_data("settings", S_IFREG|S_IRUSR|S_IWUSR,
					drive->proc, &ide_settings_proc_ops,
					drive);
		पूर्ण
		प्र_लिखो(name, "ide%d/%s", (drive->name[2]-'a')/2, drive->name);
		ent = proc_symlink(drive->name, proc_ide_root, name);
		अगर (!ent) वापस;
	पूर्ण
पूर्ण

व्योम ide_proc_unरेजिस्टर_device(ide_drive_t *drive)
अणु
	अगर (drive->proc) अणु
		हटाओ_proc_entry("settings", drive->proc);
		ide_हटाओ_proc_entries(drive->proc, generic_drive_entries);
		हटाओ_proc_entry(drive->name, proc_ide_root);
		हटाओ_proc_entry(drive->name, drive->hwअगर->proc);
		drive->proc = शून्य;
	पूर्ण
पूर्ण

अटल ide_proc_entry_t hwअगर_entries[] = अणु
	अणु "channel",	S_IFREG|S_IRUGO,	ide_channel_proc_show	पूर्ण,
	अणु "mate",	S_IFREG|S_IRUGO,	ide_mate_proc_show	पूर्ण,
	अणु "model",	S_IFREG|S_IRUGO,	ide_imodel_proc_show	पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम ide_proc_रेजिस्टर_port(ide_hwअगर_t *hwअगर)
अणु
	अगर (!hwअगर->proc) अणु
		hwअगर->proc = proc_सूची_गढ़ो(hwअगर->name, proc_ide_root);

		अगर (!hwअगर->proc)
			वापस;

		ide_add_proc_entries(hwअगर->proc, hwअगर_entries, hwअगर);
	पूर्ण
पूर्ण

व्योम ide_proc_unरेजिस्टर_port(ide_hwअगर_t *hwअगर)
अणु
	अगर (hwअगर->proc) अणु
		ide_हटाओ_proc_entries(hwअगर->proc, hwअगर_entries);
		हटाओ_proc_entry(hwअगर->name, proc_ide_root);
		hwअगर->proc = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक proc_prपूर्णांक_driver(काष्ठा device_driver *drv, व्योम *data)
अणु
	काष्ठा ide_driver *ide_drv = to_ide_driver(drv);
	काष्ठा seq_file *s = data;

	seq_म_लिखो(s, "%s version %s\n", drv->name, ide_drv->version);

	वापस 0;
पूर्ण

अटल पूर्णांक ide_drivers_show(काष्ठा seq_file *s, व्योम *p)
अणु
	पूर्णांक err;

	err = bus_क्रम_each_drv(&ide_bus_type, शून्य, s, proc_prपूर्णांक_driver);
	अगर (err < 0)
		prपूर्णांकk(KERN_WARNING "IDE: %s: bus_for_each_drv error: %d\n",
			__func__, err);
	वापस 0;
पूर्ण

DEFINE_PROC_SHOW_ATTRIBUTE(ide_drivers);

व्योम proc_ide_create(व्योम)
अणु
	proc_ide_root = proc_सूची_गढ़ो("ide", शून्य);

	अगर (!proc_ide_root)
		वापस;

	proc_create("drivers", 0, proc_ide_root, &ide_drivers_proc_ops);
पूर्ण

व्योम proc_ide_destroy(व्योम)
अणु
	हटाओ_proc_entry("drivers", proc_ide_root);
	हटाओ_proc_entry("ide", शून्य);
पूर्ण
