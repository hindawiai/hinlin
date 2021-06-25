<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 *		    Horst Hummel <Horst.Hummel@de.ibm.com>
 *		    Carsten Otte <Cotte@de.ibm.com>
 *		    Martin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2002
 *
 * /proc पूर्णांकerface क्रम the dasd driver.
 *
 */

#घोषणा KMSG_COMPONENT "dasd"

#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/proc_fs.h>

#समावेश <यंत्र/debug.h>
#समावेश <linux/uaccess.h>

/* This is ugly... */
#घोषणा PRINTK_HEADER "dasd_proc:"

#समावेश "dasd_int.h"

अटल काष्ठा proc_dir_entry *dasd_proc_root_entry = शून्य;
अटल काष्ठा proc_dir_entry *dasd_devices_entry = शून्य;
अटल काष्ठा proc_dir_entry *dasd_statistics_entry = शून्य;

अटल पूर्णांक
dasd_devices_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा dasd_device *device;
	काष्ठा dasd_block *block;
	अक्षर *substr;

	device = dasd_device_from_devindex((अचिन्हित दीर्घ) v - 1);
	अगर (IS_ERR(device))
		वापस 0;
	अगर (device->block)
		block = device->block;
	अन्यथा अणु
		dasd_put_device(device);
		वापस 0;
	पूर्ण
	/* Prपूर्णांक device number. */
	seq_म_लिखो(m, "%s", dev_name(&device->cdev->dev));
	/* Prपूर्णांक discipline string. */
	अगर (device->discipline != शून्य)
		seq_म_लिखो(m, "(%s)", device->discipline->name);
	अन्यथा
		seq_म_लिखो(m, "(none)");
	/* Prपूर्णांक kdev. */
	अगर (block->gdp)
		seq_म_लिखो(m, " at (%3d:%6d)",
			   MAJOR(disk_devt(block->gdp)),
			   MINOR(disk_devt(block->gdp)));
	अन्यथा
		seq_म_लिखो(m, "  at (???:??????)");
	/* Prपूर्णांक device name. */
	अगर (block->gdp)
		seq_म_लिखो(m, " is %-8s", block->gdp->disk_name);
	अन्यथा
		seq_म_लिखो(m, " is ????????");
	/* Prपूर्णांक devices features. */
	substr = (device->features & DASD_FEATURE_READONLY) ? "(ro)" : " ";
	seq_म_लिखो(m, "%4s: ", substr);
	/* Prपूर्णांक device status inक्रमmation. */
	चयन (device->state) अणु
	हाल DASD_STATE_NEW:
		seq_म_लिखो(m, "new");
		अवरोध;
	हाल DASD_STATE_KNOWN:
		seq_म_लिखो(m, "detected");
		अवरोध;
	हाल DASD_STATE_BASIC:
		seq_म_लिखो(m, "basic");
		अवरोध;
	हाल DASD_STATE_UNFMT:
		seq_म_लिखो(m, "unformatted");
		अवरोध;
	हाल DASD_STATE_READY:
	हाल DASD_STATE_ONLINE:
		seq_म_लिखो(m, "active ");
		अगर (dasd_check_blocksize(block->bp_block))
			seq_म_लिखो(m, "n/f	 ");
		अन्यथा
			seq_म_लिखो(m,
				   "at blocksize: %u, %lu blocks, %lu MB",
				   block->bp_block, block->blocks,
				   ((block->bp_block >> 9) *
				    block->blocks) >> 11);
		अवरोध;
	शेष:
		seq_म_लिखो(m, "no stat");
		अवरोध;
	पूर्ण
	dasd_put_device(device);
	अगर (dasd_probeonly)
		seq_म_लिखो(m, "(probeonly)");
	seq_म_लिखो(m, "\n");
	वापस 0;
पूर्ण

अटल व्योम *dasd_devices_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	अगर (*pos >= dasd_max_devindex)
		वापस शून्य;
	वापस (व्योम *)((अचिन्हित दीर्घ) *pos + 1);
पूर्ण

अटल व्योम *dasd_devices_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस dasd_devices_start(m, pos);
पूर्ण

अटल व्योम dasd_devices_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations dasd_devices_seq_ops = अणु
	.start		= dasd_devices_start,
	.next		= dasd_devices_next,
	.stop		= dasd_devices_stop,
	.show		= dasd_devices_show,
पूर्ण;

#अगर_घोषित CONFIG_DASD_PROखाता
अटल पूर्णांक dasd_stats_all_block_on(व्योम)
अणु
	पूर्णांक i, rc;
	काष्ठा dasd_device *device;

	rc = 0;
	क्रम (i = 0; i < dasd_max_devindex; ++i) अणु
		device = dasd_device_from_devindex(i);
		अगर (IS_ERR(device))
			जारी;
		अगर (device->block)
			rc = dasd_profile_on(&device->block->profile);
		dasd_put_device(device);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dasd_stats_all_block_off(व्योम)
अणु
	पूर्णांक i;
	काष्ठा dasd_device *device;

	क्रम (i = 0; i < dasd_max_devindex; ++i) अणु
		device = dasd_device_from_devindex(i);
		अगर (IS_ERR(device))
			जारी;
		अगर (device->block)
			dasd_profile_off(&device->block->profile);
		dasd_put_device(device);
	पूर्ण
पूर्ण

अटल व्योम dasd_stats_all_block_reset(व्योम)
अणु
	पूर्णांक i;
	काष्ठा dasd_device *device;

	क्रम (i = 0; i < dasd_max_devindex; ++i) अणु
		device = dasd_device_from_devindex(i);
		अगर (IS_ERR(device))
			जारी;
		अगर (device->block)
			dasd_profile_reset(&device->block->profile);
		dasd_put_device(device);
	पूर्ण
पूर्ण

अटल व्योम dasd_statistics_array(काष्ठा seq_file *m, अचिन्हित पूर्णांक *array, पूर्णांक factor)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 32; i++) अणु
		seq_म_लिखो(m, "%7d ", array[i] / factor);
		अगर (i == 15)
			seq_अ_दो(m, '\n');
	पूर्ण
	seq_अ_दो(m, '\n');
पूर्ण
#पूर्ण_अगर /* CONFIG_DASD_PROखाता */

अटल पूर्णांक dasd_stats_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
#अगर_घोषित CONFIG_DASD_PROखाता
	काष्ठा dasd_profile_info *prof;
	पूर्णांक factor;

	spin_lock_bh(&dasd_global_profile.lock);
	prof = dasd_global_profile.data;
	अगर (!prof) अणु
		spin_unlock_bh(&dasd_global_profile.lock);
		seq_म_लिखो(m, "Statistics are off - they might be "
				    "switched on using 'echo set on > "
				    "/proc/dasd/statistics'\n");
		वापस 0;
	पूर्ण

	/* prevent counter 'overflow' on output */
	क्रम (factor = 1; (prof->dasd_io_reqs / factor) > 9999999;
	     factor *= 10);

	seq_म_लिखो(m, "%d dasd I/O requests\n", prof->dasd_io_reqs);
	seq_म_लिखो(m, "with %u sectors(512B each)\n",
		       prof->dasd_io_sects);
	seq_म_लिखो(m, "Scale Factor is  %d\n", factor);
	seq_म_लिखो(m,
		       "   __<4	   ___8	   __16	   __32	   __64	   _128	"
		       "   _256	   _512	   __1k	   __2k	   __4k	   __8k	"
		       "   _16k	   _32k	   _64k	   128k\n");
	seq_म_लिखो(m,
		       "   _256	   _512	   __1M	   __2M	   __4M	   __8M	"
		       "   _16M	   _32M	   _64M	   128M	   256M	   512M	"
		       "   __1G	   __2G	   __4G " "   _>4G\n");

	seq_म_लिखो(m, "Histogram of sizes (512B secs)\n");
	dasd_statistics_array(m, prof->dasd_io_secs, factor);
	seq_म_लिखो(m, "Histogram of I/O times (microseconds)\n");
	dasd_statistics_array(m, prof->dasd_io_बार, factor);
	seq_म_लिखो(m, "Histogram of I/O times per sector\n");
	dasd_statistics_array(m, prof->dasd_io_timps, factor);
	seq_म_लिखो(m, "Histogram of I/O time till ssch\n");
	dasd_statistics_array(m, prof->dasd_io_समय1, factor);
	seq_म_लिखो(m, "Histogram of I/O time between ssch and irq\n");
	dasd_statistics_array(m, prof->dasd_io_समय2, factor);
	seq_म_लिखो(m, "Histogram of I/O time between ssch "
			    "and irq per sector\n");
	dasd_statistics_array(m, prof->dasd_io_समय2ps, factor);
	seq_म_लिखो(m, "Histogram of I/O time between irq and end\n");
	dasd_statistics_array(m, prof->dasd_io_समय3, factor);
	seq_म_लिखो(m, "# of req in chanq at enqueuing (1..32) \n");
	dasd_statistics_array(m, prof->dasd_io_nr_req, factor);
	spin_unlock_bh(&dasd_global_profile.lock);
#अन्यथा
	seq_म_लिखो(m, "Statistics are not activated in this kernel\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक dasd_stats_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, dasd_stats_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार dasd_stats_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *user_buf, माप_प्रकार user_len, loff_t *pos)
अणु
#अगर_घोषित CONFIG_DASD_PROखाता
	अक्षर *buffer, *str;
	पूर्णांक rc;

	अगर (user_len > 65536)
		user_len = 65536;
	buffer = dasd_get_user_string(user_buf, user_len);
	अगर (IS_ERR(buffer))
		वापस PTR_ERR(buffer);

	/* check क्रम valid verbs */
	str = skip_spaces(buffer);
	अगर (म_भेदन(str, "set", 3) == 0 && है_खाली(str[3])) अणु
		/* 'set xxx' was given */
		str = skip_spaces(str + 4);
		अगर (म_भेद(str, "on") == 0) अणु
			/* चयन on statistics profiling */
			rc = dasd_stats_all_block_on();
			अगर (rc) अणु
				dasd_stats_all_block_off();
				जाओ out_error;
			पूर्ण
			rc = dasd_profile_on(&dasd_global_profile);
			अगर (rc) अणु
				dasd_stats_all_block_off();
				जाओ out_error;
			पूर्ण
			dasd_profile_reset(&dasd_global_profile);
			dasd_global_profile_level = DASD_PROखाता_ON;
			pr_info("The statistics feature has been switched "
				"on\n");
		पूर्ण अन्यथा अगर (म_भेद(str, "off") == 0) अणु
			/* चयन off statistics profiling */
			dasd_global_profile_level = DASD_PROखाता_OFF;
			dasd_profile_off(&dasd_global_profile);
			dasd_stats_all_block_off();
			pr_info("The statistics feature has been switched "
				"off\n");
		पूर्ण अन्यथा
			जाओ out_parse_error;
	पूर्ण अन्यथा अगर (म_भेदन(str, "reset", 5) == 0) अणु
		/* reset the statistics */
		dasd_profile_reset(&dasd_global_profile);
		dasd_stats_all_block_reset();
		pr_info("The statistics have been reset\n");
	पूर्ण अन्यथा
		जाओ out_parse_error;
	vमुक्त(buffer);
	वापस user_len;
out_parse_error:
	rc = -EINVAL;
	pr_warn("%s is not a supported value for /proc/dasd/statistics\n", str);
out_error:
	vमुक्त(buffer);
	वापस rc;
#अन्यथा
	pr_warn("/proc/dasd/statistics: is not activated in this kernel\n");
	वापस user_len;
#पूर्ण_अगर				/* CONFIG_DASD_PROखाता */
पूर्ण

अटल स्थिर काष्ठा proc_ops dasd_stats_proc_ops = अणु
	.proc_खोलो	= dasd_stats_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= dasd_stats_proc_ग_लिखो,
पूर्ण;

/*
 * Create dasd proc-fs entries.
 * In हाल creation failed, cleanup and वापस -ENOENT.
 */
पूर्णांक
dasd_proc_init(व्योम)
अणु
	dasd_proc_root_entry = proc_सूची_गढ़ो("dasd", शून्य);
	अगर (!dasd_proc_root_entry)
		जाओ out_nodasd;
	dasd_devices_entry = proc_create_seq("devices", 0444,
					 dasd_proc_root_entry,
					 &dasd_devices_seq_ops);
	अगर (!dasd_devices_entry)
		जाओ out_nodevices;
	dasd_statistics_entry = proc_create("statistics",
					    S_IFREG | S_IRUGO | S_IWUSR,
					    dasd_proc_root_entry,
					    &dasd_stats_proc_ops);
	अगर (!dasd_statistics_entry)
		जाओ out_nostatistics;
	वापस 0;

 out_nostatistics:
	हटाओ_proc_entry("devices", dasd_proc_root_entry);
 out_nodevices:
	हटाओ_proc_entry("dasd", शून्य);
 out_nodasd:
	वापस -ENOENT;
पूर्ण

व्योम
dasd_proc_निकास(व्योम)
अणु
	हटाओ_proc_entry("devices", dasd_proc_root_entry);
	हटाओ_proc_entry("statistics", dasd_proc_root_entry);
	हटाओ_proc_entry("dasd", शून्य);
पूर्ण
