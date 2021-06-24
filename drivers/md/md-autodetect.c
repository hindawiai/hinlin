<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/mount.h>
#समावेश <linux/major.h>
#समावेश <linux/delay.h>
#समावेश <linux/init_syscalls.h>
#समावेश <linux/raid/detect.h>
#समावेश <linux/raid/md_u.h>
#समावेश <linux/raid/md_p.h>
#समावेश "md.h"

/*
 * When md (and any require personalities) are compiled पूर्णांकo the kernel
 * (not a module), arrays can be assembles are boot समय using with AUTODETECT
 * where specially marked partitions are रेजिस्टरed with md_स्वतःdetect_dev(),
 * and with MD_BOOT where devices to be collected are given on the boot line
 * with md=.....
 * The code क्रम that is here.
 */

#अगर_घोषित CONFIG_MD_AUTODETECT
अटल पूर्णांक __initdata raid_noस्वतःdetect;
#अन्यथा
अटल पूर्णांक __initdata raid_noस्वतःdetect=1;
#पूर्ण_अगर
अटल पूर्णांक __initdata raid_स्वतःpart;

अटल काष्ठा md_setup_args अणु
	पूर्णांक minor;
	पूर्णांक partitioned;
	पूर्णांक level;
	पूर्णांक chunk;
	अक्षर *device_names;
पूर्ण md_setup_args[256] __initdata;

अटल पूर्णांक md_setup_ents __initdata;

/*
 * Parse the command-line parameters given our kernel, but करो not
 * actually try to invoke the MD device now; that is handled by
 * md_setup_drive after the low-level disk drivers have initialised.
 *
 * 27/11/1999: Fixed to work correctly with the 2.3 kernel (which
 *             assigns the task of parsing पूर्णांकeger arguments to the
 *             invoked program now).  Added ability to initialise all
 *             the MD devices (by specअगरying multiple "md=" lines)
 *             instead of just one.  -- KTK
 * 18May2000: Added support क्रम persistent-superblock arrays:
 *             md=n,0,factor,fault,device-list   uses RAID0 क्रम device n
 *             md=n,-1,factor,fault,device-list  uses LINEAR क्रम device n
 *             md=n,device-list      पढ़ोs a RAID superblock from the devices
 *             elements in device-list are पढ़ो by name_to_kdev_t so can be
 *             a hex number or something like /dev/hda1 /dev/sdb
 * 2001-06-03: Dave Cinege <dcinege@psychosis.com>
 *		Shअगरted name_to_kdev_t() and related operations to md_set_drive()
 *		क्रम later execution. Rewrote section to make devfs compatible.
 */
अटल पूर्णांक __init md_setup(अक्षर *str)
अणु
	पूर्णांक minor, level, factor, fault, partitioned = 0;
	अक्षर *pername = "";
	अक्षर *str1;
	पूर्णांक ent;

	अगर (*str == 'd') अणु
		partitioned = 1;
		str++;
	पूर्ण
	अगर (get_option(&str, &minor) != 2) अणु	/* MD Number */
		prपूर्णांकk(KERN_WARNING "md: Too few arguments supplied to md=.\n");
		वापस 0;
	पूर्ण
	str1 = str;
	क्रम (ent=0 ; ent< md_setup_ents ; ent++)
		अगर (md_setup_args[ent].minor == minor &&
		    md_setup_args[ent].partitioned == partitioned) अणु
			prपूर्णांकk(KERN_WARNING "md: md=%s%d, Specified more than once. "
			       "Replacing previous definition.\n", partitioned?"d":"", minor);
			अवरोध;
		पूर्ण
	अगर (ent >= ARRAY_SIZE(md_setup_args)) अणु
		prपूर्णांकk(KERN_WARNING "md: md=%s%d - too many md initialisations\n", partitioned?"d":"", minor);
		वापस 0;
	पूर्ण
	अगर (ent >= md_setup_ents)
		md_setup_ents++;
	चयन (get_option(&str, &level)) अणु	/* RAID level */
	हाल 2: /* could be 0 or -1.. */
		अगर (level == 0 || level == LEVEL_LINEAR) अणु
			अगर (get_option(&str, &factor) != 2 ||	/* Chunk Size */
					get_option(&str, &fault) != 2) अणु
				prपूर्णांकk(KERN_WARNING "md: Too few arguments supplied to md=.\n");
				वापस 0;
			पूर्ण
			md_setup_args[ent].level = level;
			md_setup_args[ent].chunk = 1 << (factor+12);
			अगर (level ==  LEVEL_LINEAR)
				pername = "linear";
			अन्यथा
				pername = "raid0";
			अवरोध;
		पूर्ण
		fallthrough;
	हाल 1: /* the first device is numeric */
		str = str1;
		fallthrough;
	हाल 0:
		md_setup_args[ent].level = LEVEL_NONE;
		pername="super-block";
	पूर्ण

	prपूर्णांकk(KERN_INFO "md: Will configure md%d (%s) from %s, below.\n",
		minor, pername, str);
	md_setup_args[ent].device_names = str;
	md_setup_args[ent].partitioned = partitioned;
	md_setup_args[ent].minor = minor;

	वापस 1;
पूर्ण

अटल व्योम __init md_setup_drive(काष्ठा md_setup_args *args)
अणु
	अक्षर *devname = args->device_names;
	dev_t devices[MD_SB_DISKS + 1], mdev;
	काष्ठा mdu_array_info_s ainfo = अणु पूर्ण;
	काष्ठा block_device *bdev;
	काष्ठा mddev *mddev;
	पूर्णांक err = 0, i;
	अक्षर name[16];

	अगर (args->partitioned) अणु
		mdev = MKDEV(mdp_major, args->minor << MdpMinorShअगरt);
		प्र_लिखो(name, "md_d%d", args->minor);
	पूर्ण अन्यथा अणु
		mdev = MKDEV(MD_MAJOR, args->minor);
		प्र_लिखो(name, "md%d", args->minor);
	पूर्ण

	क्रम (i = 0; i < MD_SB_DISKS && devname != शून्य; i++) अणु
		काष्ठा kstat stat;
		अक्षर *p;
		अक्षर comp_name[64];
		dev_t dev;

		p = म_अक्षर(devname, ',');
		अगर (p)
			*p++ = 0;

		dev = name_to_dev_t(devname);
		अगर (म_भेदन(devname, "/dev/", 5) == 0)
			devname += 5;
		snम_लिखो(comp_name, 63, "/dev/%s", devname);
		अगर (init_stat(comp_name, &stat, 0) == 0 && S_ISBLK(stat.mode))
			dev = new_decode_dev(stat.rdev);
		अगर (!dev) अणु
			pr_warn("md: Unknown device name: %s\n", devname);
			अवरोध;
		पूर्ण

		devices[i] = dev;
		devname = p;
	पूर्ण
	devices[i] = 0;

	अगर (!i)
		वापस;

	pr_info("md: Loading %s: %s\n", name, args->device_names);

	bdev = blkdev_get_by_dev(mdev, FMODE_READ, शून्य);
	अगर (IS_ERR(bdev)) अणु
		pr_err("md: open failed - cannot start array %s\n", name);
		वापस;
	पूर्ण

	err = -EIO;
	अगर (WARN(bdev->bd_disk->fops != &md_fops,
			"Opening block device %x resulted in non-md device\n",
			mdev))
		जाओ out_blkdev_put;

	mddev = bdev->bd_disk->निजी_data;

	err = mddev_lock(mddev);
	अगर (err) अणु
		pr_err("md: failed to lock array %s\n", name);
		जाओ out_blkdev_put;
	पूर्ण

	अगर (!list_empty(&mddev->disks) || mddev->raid_disks) अणु
		pr_warn("md: Ignoring %s, already autodetected. (Use raid=noautodetect)\n",
		       name);
		जाओ out_unlock;
	पूर्ण

	अगर (args->level != LEVEL_NONE) अणु
		/* non-persistent */
		ainfo.level = args->level;
		ainfo.md_minor = args->minor;
		ainfo.not_persistent = 1;
		ainfo.state = (1 << MD_SB_CLEAN);
		ainfo.chunk_size = args->chunk;
		जबतक (devices[ainfo.raid_disks])
			ainfo.raid_disks++;
	पूर्ण

	err = md_set_array_info(mddev, &ainfo);

	क्रम (i = 0; i <= MD_SB_DISKS && devices[i]; i++) अणु
		काष्ठा mdu_disk_info_s dinfo = अणु
			.major	= MAJOR(devices[i]),
			.minor	= MINOR(devices[i]),
		पूर्ण;

		अगर (args->level != LEVEL_NONE) अणु
			dinfo.number = i;
			dinfo.raid_disk = i;
			dinfo.state =
				(1 << MD_DISK_ACTIVE) | (1 << MD_DISK_SYNC);
		पूर्ण

		md_add_new_disk(mddev, &dinfo);
	पूर्ण

	अगर (!err)
		err = करो_md_run(mddev);
	अगर (err)
		pr_warn("md: starting %s failed\n", name);
out_unlock:
	mddev_unlock(mddev);
out_blkdev_put:
	blkdev_put(bdev, FMODE_READ);
पूर्ण

अटल पूर्णांक __init raid_setup(अक्षर *str)
अणु
	पूर्णांक len, pos;

	len = म_माप(str) + 1;
	pos = 0;

	जबतक (pos < len) अणु
		अक्षर *comma = म_अक्षर(str+pos, ',');
		पूर्णांक wlen;
		अगर (comma)
			wlen = (comma-str)-pos;
		अन्यथा	wlen = (len-1)-pos;

		अगर (!म_भेदन(str, "noautodetect", wlen))
			raid_noस्वतःdetect = 1;
		अगर (!म_भेदन(str, "autodetect", wlen))
			raid_noस्वतःdetect = 0;
		अगर (म_भेदन(str, "partitionable", wlen)==0)
			raid_स्वतःpart = 1;
		अगर (म_भेदन(str, "part", wlen)==0)
			raid_स्वतःpart = 1;
		pos += wlen+1;
	पूर्ण
	वापस 1;
पूर्ण

__setup("raid=", raid_setup);
__setup("md=", md_setup);

अटल व्योम __init स्वतःdetect_raid(व्योम)
अणु
	/*
	 * Since we करोn't want to detect and use half a raid array, we need to
	 * रुको क्रम the known devices to complete their probing
	 */
	prपूर्णांकk(KERN_INFO "md: Waiting for all devices to be available before autodetect\n");
	prपूर्णांकk(KERN_INFO "md: If you don't use raid, use raid=noautodetect\n");

	रुको_क्रम_device_probe();
	md_स्वतःstart_arrays(raid_स्वतःpart);
पूर्ण

व्योम __init md_run_setup(व्योम)
अणु
	पूर्णांक ent;

	अगर (raid_noस्वतःdetect)
		prपूर्णांकk(KERN_INFO "md: Skipping autodetection of RAID arrays. (raid=autodetect will force)\n");
	अन्यथा
		स्वतःdetect_raid();

	क्रम (ent = 0; ent < md_setup_ents; ent++)
		md_setup_drive(&md_setup_args[ent]);
पूर्ण
