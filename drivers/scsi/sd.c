<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *      sd.c Copyright (C) 1992 Drew Eckhardt
 *           Copyright (C) 1993, 1994, 1995, 1999 Eric Youngdale
 *
 *      Linux scsi disk driver
 *              Initial versions: Drew Eckhardt
 *              Subsequent revisions: Eric Youngdale
 *	Modअगरication history:
 *       - Drew Eckhardt <drew@coloraकरो.edu> original
 *       - Eric Youngdale <eric@andante.org> add scatter-gather, multiple 
 *         outstanding request, and other enhancements.
 *         Support loadable low-level scsi drivers.
 *       - Jirka Hanika <geo@ff.cuni.cz> support more scsi disks using 
 *         eight major numbers.
 *       - Riअक्षरd Gooch <rgooch@atnf.csiro.au> support devfs.
 *	 - Torben Mathiasen <पंचांगm@image.dk> Resource allocation fixes in 
 *	   sd_init and cleanups.
 *	 - Alex Davis <leपंचांगein@erols.com> Fix problem where partition info
 *	   not being पढ़ो in sd_खोलो. Fix problem where removable media 
 *	   could be ejected after sd_खोलो.
 *	 - Douglas Gilbert <dgilbert@पूर्णांकerlog.com> cleanup क्रम lk 2.5.x
 *	 - Badari Pulavarty <pbadari@us.ibm.com>, Matthew Wilcox 
 *	   <willy@debian.org>, Kurt Garloff <garloff@suse.de>: 
 *	   Support 32k/1M disks.
 *
 *	Logging policy (needs CONFIG_SCSI_LOGGING defined):
 *	 - setting up transfer: SCSI_LOG_HLQUEUE levels 1 and 2
 *	 - end of transfer (bh + scsi_lib): SCSI_LOG_HLCOMPLETE level 1
 *	 - entering sd_ioctl: SCSI_LOG_IOCTL level 1
 *	 - entering other commands: SCSI_LOG_HLQUEUE level 3
 *	Note: when the logging level is set by the user, it must be greater
 *	than the level indicated above to trigger output.	
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/bपन.स>
#समावेश <linux/genhd.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/blk-pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/async.h>
#समावेश <linux/slab.h>
#समावेश <linux/sed-opal.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pr.h>
#समावेश <linux/t10-pi.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_ioctl.h>
#समावेश <scsi/scsicam.h>

#समावेश "sd.h"
#समावेश "scsi_priv.h"
#समावेश "scsi_logging.h"

MODULE_AUTHOR("Eric Youngdale");
MODULE_DESCRIPTION("SCSI disk (sd) driver");
MODULE_LICENSE("GPL");

MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK0_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK1_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK2_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK3_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK4_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK5_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK6_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK7_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK8_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK9_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK10_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK11_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK12_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK13_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK14_MAJOR);
MODULE_ALIAS_BLOCKDEV_MAJOR(SCSI_DISK15_MAJOR);
MODULE_ALIAS_SCSI_DEVICE(TYPE_DISK);
MODULE_ALIAS_SCSI_DEVICE(TYPE_MOD);
MODULE_ALIAS_SCSI_DEVICE(TYPE_RBC);
MODULE_ALIAS_SCSI_DEVICE(TYPE_ZBC);

#अगर !defined(CONFIG_DEBUG_BLOCK_EXT_DEVT)
#घोषणा SD_MINORS	16
#अन्यथा
#घोषणा SD_MINORS	0
#पूर्ण_अगर

अटल व्योम sd_config_discard(काष्ठा scsi_disk *, अचिन्हित पूर्णांक);
अटल व्योम sd_config_ग_लिखो_same(काष्ठा scsi_disk *);
अटल पूर्णांक  sd_revalidate_disk(काष्ठा gendisk *);
अटल व्योम sd_unlock_native_capacity(काष्ठा gendisk *disk);
अटल पूर्णांक  sd_probe(काष्ठा device *);
अटल पूर्णांक  sd_हटाओ(काष्ठा device *);
अटल व्योम sd_shutकरोwn(काष्ठा device *);
अटल पूर्णांक sd_suspend_प्रणाली(काष्ठा device *);
अटल पूर्णांक sd_suspend_runसमय(काष्ठा device *);
अटल पूर्णांक sd_resume(काष्ठा device *);
अटल व्योम sd_rescan(काष्ठा device *);
अटल blk_status_t sd_init_command(काष्ठा scsi_cmnd *SCpnt);
अटल व्योम sd_uninit_command(काष्ठा scsi_cmnd *SCpnt);
अटल पूर्णांक sd_करोne(काष्ठा scsi_cmnd *);
अटल व्योम sd_eh_reset(काष्ठा scsi_cmnd *);
अटल पूर्णांक sd_eh_action(काष्ठा scsi_cmnd *, पूर्णांक);
अटल व्योम sd_पढ़ो_capacity(काष्ठा scsi_disk *sdkp, अचिन्हित अक्षर *buffer);
अटल व्योम scsi_disk_release(काष्ठा device *cdev);

अटल DEFINE_IDA(sd_index_ida);

/* This semaphore is used to mediate the 0->1 reference get in the
 * face of object deकाष्ठाion (i.e. we can't allow a get on an
 * object after last put) */
अटल DEFINE_MUTEX(sd_ref_mutex);

अटल काष्ठा kmem_cache *sd_cdb_cache;
अटल mempool_t *sd_cdb_pool;
अटल mempool_t *sd_page_pool;

अटल स्थिर अक्षर *sd_cache_types[] = अणु
	"write through", "none", "write back",
	"write back, no read (daft)"
पूर्ण;

अटल व्योम sd_set_flush_flag(काष्ठा scsi_disk *sdkp)
अणु
	bool wc = false, fua = false;

	अगर (sdkp->WCE) अणु
		wc = true;
		अगर (sdkp->DPOFUA)
			fua = true;
	पूर्ण

	blk_queue_ग_लिखो_cache(sdkp->disk->queue, wc, fua);
पूर्ण

अटल sमाप_प्रकार
cache_type_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ct, rcd, wce, sp;
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	काष्ठा scsi_device *sdp = sdkp->device;
	अक्षर buffer[64];
	अक्षर *buffer_data;
	काष्ठा scsi_mode_data data;
	काष्ठा scsi_sense_hdr sshdr;
	अटल स्थिर अक्षर temp[] = "temporary ";
	पूर्णांक len;

	अगर (sdp->type != TYPE_DISK && sdp->type != TYPE_ZBC)
		/* no cache control on RBC devices; theoretically they
		 * can करो it, but there's probably so many exceptions
		 * it's not worth the risk */
		वापस -EINVAL;

	अगर (म_भेदन(buf, temp, माप(temp) - 1) == 0) अणु
		buf += माप(temp) - 1;
		sdkp->cache_override = 1;
	पूर्ण अन्यथा अणु
		sdkp->cache_override = 0;
	पूर्ण

	ct = sysfs_match_string(sd_cache_types, buf);
	अगर (ct < 0)
		वापस -EINVAL;

	rcd = ct & 0x01 ? 1 : 0;
	wce = (ct & 0x02) && !sdkp->ग_लिखो_prot ? 1 : 0;

	अगर (sdkp->cache_override) अणु
		sdkp->WCE = wce;
		sdkp->RCD = rcd;
		sd_set_flush_flag(sdkp);
		वापस count;
	पूर्ण

	अगर (scsi_mode_sense(sdp, 0x08, 8, buffer, माप(buffer), SD_TIMEOUT,
			    sdkp->max_retries, &data, शून्य))
		वापस -EINVAL;
	len = min_t(माप_प्रकार, माप(buffer), data.length - data.header_length -
		  data.block_descriptor_length);
	buffer_data = buffer + data.header_length +
		data.block_descriptor_length;
	buffer_data[2] &= ~0x05;
	buffer_data[2] |= wce << 2 | rcd;
	sp = buffer_data[0] & 0x80 ? 1 : 0;
	buffer_data[0] &= ~0x80;

	/*
	 * Ensure WP, DPOFUA, and RESERVED fields are cleared in
	 * received mode parameter buffer beक्रमe करोing MODE SELECT.
	 */
	data.device_specअगरic = 0;

	अगर (scsi_mode_select(sdp, 1, sp, 8, buffer_data, len, SD_TIMEOUT,
			     sdkp->max_retries, &data, &sshdr)) अणु
		अगर (scsi_sense_valid(&sshdr))
			sd_prपूर्णांक_sense_hdr(sdkp, &sshdr);
		वापस -EINVAL;
	पूर्ण
	sd_revalidate_disk(sdkp->disk);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
manage_start_stop_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	काष्ठा scsi_device *sdp = sdkp->device;

	वापस प्र_लिखो(buf, "%u\n", sdp->manage_start_stop);
पूर्ण

अटल sमाप_प्रकार
manage_start_stop_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	काष्ठा scsi_device *sdp = sdkp->device;
	bool v;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (kstrtobool(buf, &v))
		वापस -EINVAL;

	sdp->manage_start_stop = v;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(manage_start_stop);

अटल sमाप_प्रकार
allow_restart_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);

	वापस प्र_लिखो(buf, "%u\n", sdkp->device->allow_restart);
पूर्ण

अटल sमाप_प्रकार
allow_restart_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	bool v;
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	काष्ठा scsi_device *sdp = sdkp->device;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (sdp->type != TYPE_DISK && sdp->type != TYPE_ZBC)
		वापस -EINVAL;

	अगर (kstrtobool(buf, &v))
		वापस -EINVAL;

	sdp->allow_restart = v;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(allow_restart);

अटल sमाप_प्रकार
cache_type_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	पूर्णांक ct = sdkp->RCD + 2*sdkp->WCE;

	वापस प्र_लिखो(buf, "%s\n", sd_cache_types[ct]);
पूर्ण
अटल DEVICE_ATTR_RW(cache_type);

अटल sमाप_प्रकार
FUA_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);

	वापस प्र_लिखो(buf, "%u\n", sdkp->DPOFUA);
पूर्ण
अटल DEVICE_ATTR_RO(FUA);

अटल sमाप_प्रकार
protection_type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);

	वापस प्र_लिखो(buf, "%u\n", sdkp->protection_type);
पूर्ण

अटल sमाप_प्रकार
protection_type_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	err = kstrtouपूर्णांक(buf, 10, &val);

	अगर (err)
		वापस err;

	अगर (val <= T10_PI_TYPE3_PROTECTION)
		sdkp->protection_type = val;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(protection_type);

अटल sमाप_प्रकार
protection_mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	काष्ठा scsi_device *sdp = sdkp->device;
	अचिन्हित पूर्णांक dअगर, dix;

	dअगर = scsi_host_dअगर_capable(sdp->host, sdkp->protection_type);
	dix = scsi_host_dix_capable(sdp->host, sdkp->protection_type);

	अगर (!dix && scsi_host_dix_capable(sdp->host, T10_PI_TYPE0_PROTECTION)) अणु
		dअगर = 0;
		dix = 1;
	पूर्ण

	अगर (!dअगर && !dix)
		वापस प्र_लिखो(buf, "none\n");

	वापस प्र_लिखो(buf, "%s%u\n", dix ? "dix" : "dif", dअगर);
पूर्ण
अटल DEVICE_ATTR_RO(protection_mode);

अटल sमाप_प्रकार
app_tag_own_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);

	वापस प्र_लिखो(buf, "%u\n", sdkp->ATO);
पूर्ण
अटल DEVICE_ATTR_RO(app_tag_own);

अटल sमाप_प्रकार
thin_provisioning_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);

	वापस प्र_लिखो(buf, "%u\n", sdkp->lbpme);
पूर्ण
अटल DEVICE_ATTR_RO(thin_provisioning);

/* sysfs_match_string() requires dense arrays */
अटल स्थिर अक्षर *lbp_mode[] = अणु
	[SD_LBP_FULL]		= "full",
	[SD_LBP_UNMAP]		= "unmap",
	[SD_LBP_WS16]		= "writesame_16",
	[SD_LBP_WS10]		= "writesame_10",
	[SD_LBP_ZERO]		= "writesame_zero",
	[SD_LBP_DISABLE]	= "disabled",
पूर्ण;

अटल sमाप_प्रकार
provisioning_mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);

	वापस प्र_लिखो(buf, "%s\n", lbp_mode[sdkp->provisioning_mode]);
पूर्ण

अटल sमाप_प्रकार
provisioning_mode_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	काष्ठा scsi_device *sdp = sdkp->device;
	पूर्णांक mode;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (sd_is_zoned(sdkp)) अणु
		sd_config_discard(sdkp, SD_LBP_DISABLE);
		वापस count;
	पूर्ण

	अगर (sdp->type != TYPE_DISK)
		वापस -EINVAL;

	mode = sysfs_match_string(lbp_mode, buf);
	अगर (mode < 0)
		वापस -EINVAL;

	sd_config_discard(sdkp, mode);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(provisioning_mode);

/* sysfs_match_string() requires dense arrays */
अटल स्थिर अक्षर *zeroing_mode[] = अणु
	[SD_ZERO_WRITE]		= "write",
	[SD_ZERO_WS]		= "writesame",
	[SD_ZERO_WS16_UNMAP]	= "writesame_16_unmap",
	[SD_ZERO_WS10_UNMAP]	= "writesame_10_unmap",
पूर्ण;

अटल sमाप_प्रकार
zeroing_mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);

	वापस प्र_लिखो(buf, "%s\n", zeroing_mode[sdkp->zeroing_mode]);
पूर्ण

अटल sमाप_प्रकार
zeroing_mode_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	पूर्णांक mode;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	mode = sysfs_match_string(zeroing_mode, buf);
	अगर (mode < 0)
		वापस -EINVAL;

	sdkp->zeroing_mode = mode;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(zeroing_mode);

अटल sमाप_प्रकार
max_medium_access_समयouts_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);

	वापस प्र_लिखो(buf, "%u\n", sdkp->max_medium_access_समयouts);
पूर्ण

अटल sमाप_प्रकार
max_medium_access_समयouts_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	err = kstrtouपूर्णांक(buf, 10, &sdkp->max_medium_access_समयouts);

	वापस err ? err : count;
पूर्ण
अटल DEVICE_ATTR_RW(max_medium_access_समयouts);

अटल sमाप_प्रकार
max_ग_लिखो_same_blocks_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);

	वापस प्र_लिखो(buf, "%u\n", sdkp->max_ws_blocks);
पूर्ण

अटल sमाप_प्रकार
max_ग_लिखो_same_blocks_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	काष्ठा scsi_device *sdp = sdkp->device;
	अचिन्हित दीर्घ max;
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (sdp->type != TYPE_DISK && sdp->type != TYPE_ZBC)
		वापस -EINVAL;

	err = kम_से_अदीर्घ(buf, 10, &max);

	अगर (err)
		वापस err;

	अगर (max == 0)
		sdp->no_ग_लिखो_same = 1;
	अन्यथा अगर (max <= SD_MAX_WS16_BLOCKS) अणु
		sdp->no_ग_लिखो_same = 0;
		sdkp->max_ws_blocks = max;
	पूर्ण

	sd_config_ग_लिखो_same(sdkp);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(max_ग_लिखो_same_blocks);

अटल sमाप_प्रकार
zoned_cap_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);

	अगर (sdkp->device->type == TYPE_ZBC)
		वापस प्र_लिखो(buf, "host-managed\n");
	अगर (sdkp->zoned == 1)
		वापस प्र_लिखो(buf, "host-aware\n");
	अगर (sdkp->zoned == 2)
		वापस प्र_लिखो(buf, "drive-managed\n");
	वापस प्र_लिखो(buf, "none\n");
पूर्ण
अटल DEVICE_ATTR_RO(zoned_cap);

अटल sमाप_प्रकार
max_retries_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	काष्ठा scsi_device *sdev = sdkp->device;
	पूर्णांक retries, err;

	err = kstrtoपूर्णांक(buf, 10, &retries);
	अगर (err)
		वापस err;

	अगर (retries == SCSI_CMD_RETRIES_NO_LIMIT || retries <= SD_MAX_RETRIES) अणु
		sdkp->max_retries = retries;
		वापस count;
	पूर्ण

	sdev_prपूर्णांकk(KERN_ERR, sdev, "max_retries must be between -1 and %d\n",
		    SD_MAX_RETRIES);
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार
max_retries_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		 अक्षर *buf)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);

	वापस प्र_लिखो(buf, "%d\n", sdkp->max_retries);
पूर्ण

अटल DEVICE_ATTR_RW(max_retries);

अटल काष्ठा attribute *sd_disk_attrs[] = अणु
	&dev_attr_cache_type.attr,
	&dev_attr_FUA.attr,
	&dev_attr_allow_restart.attr,
	&dev_attr_manage_start_stop.attr,
	&dev_attr_protection_type.attr,
	&dev_attr_protection_mode.attr,
	&dev_attr_app_tag_own.attr,
	&dev_attr_thin_provisioning.attr,
	&dev_attr_provisioning_mode.attr,
	&dev_attr_zeroing_mode.attr,
	&dev_attr_max_ग_लिखो_same_blocks.attr,
	&dev_attr_max_medium_access_समयouts.attr,
	&dev_attr_zoned_cap.attr,
	&dev_attr_max_retries.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(sd_disk);

अटल काष्ठा class sd_disk_class = अणु
	.name		= "scsi_disk",
	.owner		= THIS_MODULE,
	.dev_release	= scsi_disk_release,
	.dev_groups	= sd_disk_groups,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops sd_pm_ops = अणु
	.suspend		= sd_suspend_प्रणाली,
	.resume			= sd_resume,
	.घातeroff		= sd_suspend_प्रणाली,
	.restore		= sd_resume,
	.runसमय_suspend	= sd_suspend_runसमय,
	.runसमय_resume		= sd_resume,
पूर्ण;

अटल काष्ठा scsi_driver sd_ढाँचा = अणु
	.gendrv = अणु
		.name		= "sd",
		.owner		= THIS_MODULE,
		.probe		= sd_probe,
		.probe_type	= PROBE_PREFER_ASYNCHRONOUS,
		.हटाओ		= sd_हटाओ,
		.shutकरोwn	= sd_shutकरोwn,
		.pm		= &sd_pm_ops,
	पूर्ण,
	.rescan			= sd_rescan,
	.init_command		= sd_init_command,
	.uninit_command		= sd_uninit_command,
	.करोne			= sd_करोne,
	.eh_action		= sd_eh_action,
	.eh_reset		= sd_eh_reset,
पूर्ण;

/*
 * Don't request a new module, as that could deadlock in multipath
 * environment.
 */
अटल व्योम sd_शेष_probe(dev_t devt)
अणु
पूर्ण

/*
 * Device no to disk mapping:
 * 
 *       major         disc2     disc  p1
 *   |............|.............|....|....| <- dev_t
 *    31        20 19          8 7  4 3  0
 * 
 * Inside a major, we have 16k disks, however mapped non-
 * contiguously. The first 16 disks are क्रम major0, the next
 * ones with major1, ... Disk 256 is क्रम major0 again, disk 272 
 * क्रम major1, ... 
 * As we stay compatible with our numbering scheme, we can reuse 
 * the well-know SCSI majors 8, 65--71, 136--143.
 */
अटल पूर्णांक sd_major(पूर्णांक major_idx)
अणु
	चयन (major_idx) अणु
	हाल 0:
		वापस SCSI_DISK0_MAJOR;
	हाल 1 ... 7:
		वापस SCSI_DISK1_MAJOR + major_idx - 1;
	हाल 8 ... 15:
		वापस SCSI_DISK8_MAJOR + major_idx - 8;
	शेष:
		BUG();
		वापस 0;	/* shut up gcc */
	पूर्ण
पूर्ण

अटल काष्ठा scsi_disk *scsi_disk_get(काष्ठा gendisk *disk)
अणु
	काष्ठा scsi_disk *sdkp = शून्य;

	mutex_lock(&sd_ref_mutex);

	अगर (disk->निजी_data) अणु
		sdkp = scsi_disk(disk);
		अगर (scsi_device_get(sdkp->device) == 0)
			get_device(&sdkp->dev);
		अन्यथा
			sdkp = शून्य;
	पूर्ण
	mutex_unlock(&sd_ref_mutex);
	वापस sdkp;
पूर्ण

अटल व्योम scsi_disk_put(काष्ठा scsi_disk *sdkp)
अणु
	काष्ठा scsi_device *sdev = sdkp->device;

	mutex_lock(&sd_ref_mutex);
	put_device(&sdkp->dev);
	scsi_device_put(sdev);
	mutex_unlock(&sd_ref_mutex);
पूर्ण

#अगर_घोषित CONFIG_BLK_SED_OPAL
अटल पूर्णांक sd_sec_submit(व्योम *data, u16 spsp, u8 secp, व्योम *buffer,
		माप_प्रकार len, bool send)
अणु
	काष्ठा scsi_disk *sdkp = data;
	काष्ठा scsi_device *sdev = sdkp->device;
	u8 cdb[12] = अणु 0, पूर्ण;
	पूर्णांक ret;

	cdb[0] = send ? SECURITY_PROTOCOL_OUT : SECURITY_PROTOCOL_IN;
	cdb[1] = secp;
	put_unaligned_be16(spsp, &cdb[2]);
	put_unaligned_be32(len, &cdb[6]);

	ret = scsi_execute(sdev, cdb, send ? DMA_TO_DEVICE : DMA_FROM_DEVICE,
		buffer, len, शून्य, शून्य, SD_TIMEOUT, sdkp->max_retries, 0,
		RQF_PM, शून्य);
	वापस ret <= 0 ? ret : -EIO;
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_SED_OPAL */

/*
 * Look up the DIX operation based on whether the command is पढ़ो or
 * ग_लिखो and whether dix and dअगर are enabled.
 */
अटल अचिन्हित पूर्णांक sd_prot_op(bool ग_लिखो, bool dix, bool dअगर)
अणु
	/* Lookup table: bit 2 (ग_लिखो), bit 1 (dix), bit 0 (dअगर) */
	अटल स्थिर अचिन्हित पूर्णांक ops[] = अणु	/* wrt dix dअगर */
		SCSI_PROT_NORMAL,		/*  0	0   0  */
		SCSI_PROT_READ_STRIP,		/*  0	0   1  */
		SCSI_PROT_READ_INSERT,		/*  0	1   0  */
		SCSI_PROT_READ_PASS,		/*  0	1   1  */
		SCSI_PROT_NORMAL,		/*  1	0   0  */
		SCSI_PROT_WRITE_INSERT,		/*  1	0   1  */
		SCSI_PROT_WRITE_STRIP,		/*  1	1   0  */
		SCSI_PROT_WRITE_PASS,		/*  1	1   1  */
	पूर्ण;

	वापस ops[ग_लिखो << 2 | dix << 1 | dअगर];
पूर्ण

/*
 * Returns a mask of the protection flags that are valid क्रम a given DIX
 * operation.
 */
अटल अचिन्हित पूर्णांक sd_prot_flag_mask(अचिन्हित पूर्णांक prot_op)
अणु
	अटल स्थिर अचिन्हित पूर्णांक flag_mask[] = अणु
		[SCSI_PROT_NORMAL]		= 0,

		[SCSI_PROT_READ_STRIP]		= SCSI_PROT_TRANSFER_PI |
						  SCSI_PROT_GUARD_CHECK |
						  SCSI_PROT_REF_CHECK |
						  SCSI_PROT_REF_INCREMENT,

		[SCSI_PROT_READ_INSERT]		= SCSI_PROT_REF_INCREMENT |
						  SCSI_PROT_IP_CHECKSUM,

		[SCSI_PROT_READ_PASS]		= SCSI_PROT_TRANSFER_PI |
						  SCSI_PROT_GUARD_CHECK |
						  SCSI_PROT_REF_CHECK |
						  SCSI_PROT_REF_INCREMENT |
						  SCSI_PROT_IP_CHECKSUM,

		[SCSI_PROT_WRITE_INSERT]	= SCSI_PROT_TRANSFER_PI |
						  SCSI_PROT_REF_INCREMENT,

		[SCSI_PROT_WRITE_STRIP]		= SCSI_PROT_GUARD_CHECK |
						  SCSI_PROT_REF_CHECK |
						  SCSI_PROT_REF_INCREMENT |
						  SCSI_PROT_IP_CHECKSUM,

		[SCSI_PROT_WRITE_PASS]		= SCSI_PROT_TRANSFER_PI |
						  SCSI_PROT_GUARD_CHECK |
						  SCSI_PROT_REF_CHECK |
						  SCSI_PROT_REF_INCREMENT |
						  SCSI_PROT_IP_CHECKSUM,
	पूर्ण;

	वापस flag_mask[prot_op];
पूर्ण

अटल अचिन्हित अक्षर sd_setup_protect_cmnd(काष्ठा scsi_cmnd *scmd,
					   अचिन्हित पूर्णांक dix, अचिन्हित पूर्णांक dअगर)
अणु
	काष्ठा bio *bio = scmd->request->bio;
	अचिन्हित पूर्णांक prot_op = sd_prot_op(rq_data_dir(scmd->request), dix, dअगर);
	अचिन्हित पूर्णांक protect = 0;

	अगर (dix) अणु				/* DIX Type 0, 1, 2, 3 */
		अगर (bio_पूर्णांकegrity_flagged(bio, BIP_IP_CHECKSUM))
			scmd->prot_flags |= SCSI_PROT_IP_CHECKSUM;

		अगर (bio_पूर्णांकegrity_flagged(bio, BIP_CTRL_NOCHECK) == false)
			scmd->prot_flags |= SCSI_PROT_GUARD_CHECK;
	पूर्ण

	अगर (dअगर != T10_PI_TYPE3_PROTECTION) अणु	/* DIX/DIF Type 0, 1, 2 */
		scmd->prot_flags |= SCSI_PROT_REF_INCREMENT;

		अगर (bio_पूर्णांकegrity_flagged(bio, BIP_CTRL_NOCHECK) == false)
			scmd->prot_flags |= SCSI_PROT_REF_CHECK;
	पूर्ण

	अगर (dअगर) अणु				/* DIX/DIF Type 1, 2, 3 */
		scmd->prot_flags |= SCSI_PROT_TRANSFER_PI;

		अगर (bio_पूर्णांकegrity_flagged(bio, BIP_DISK_NOCHECK))
			protect = 3 << 5;	/* Disable target PI checking */
		अन्यथा
			protect = 1 << 5;	/* Enable target PI checking */
	पूर्ण

	scsi_set_prot_op(scmd, prot_op);
	scsi_set_prot_type(scmd, dअगर);
	scmd->prot_flags &= sd_prot_flag_mask(prot_op);

	वापस protect;
पूर्ण

अटल व्योम sd_config_discard(काष्ठा scsi_disk *sdkp, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा request_queue *q = sdkp->disk->queue;
	अचिन्हित पूर्णांक logical_block_size = sdkp->device->sector_size;
	अचिन्हित पूर्णांक max_blocks = 0;

	q->limits.discard_alignment =
		sdkp->unmap_alignment * logical_block_size;
	q->limits.discard_granularity =
		max(sdkp->physical_block_size,
		    sdkp->unmap_granularity * logical_block_size);
	sdkp->provisioning_mode = mode;

	चयन (mode) अणु

	हाल SD_LBP_FULL:
	हाल SD_LBP_DISABLE:
		blk_queue_max_discard_sectors(q, 0);
		blk_queue_flag_clear(QUEUE_FLAG_DISCARD, q);
		वापस;

	हाल SD_LBP_UNMAP:
		max_blocks = min_not_zero(sdkp->max_unmap_blocks,
					  (u32)SD_MAX_WS16_BLOCKS);
		अवरोध;

	हाल SD_LBP_WS16:
		अगर (sdkp->device->unmap_limit_क्रम_ws)
			max_blocks = sdkp->max_unmap_blocks;
		अन्यथा
			max_blocks = sdkp->max_ws_blocks;

		max_blocks = min_not_zero(max_blocks, (u32)SD_MAX_WS16_BLOCKS);
		अवरोध;

	हाल SD_LBP_WS10:
		अगर (sdkp->device->unmap_limit_क्रम_ws)
			max_blocks = sdkp->max_unmap_blocks;
		अन्यथा
			max_blocks = sdkp->max_ws_blocks;

		max_blocks = min_not_zero(max_blocks, (u32)SD_MAX_WS10_BLOCKS);
		अवरोध;

	हाल SD_LBP_ZERO:
		max_blocks = min_not_zero(sdkp->max_ws_blocks,
					  (u32)SD_MAX_WS10_BLOCKS);
		अवरोध;
	पूर्ण

	blk_queue_max_discard_sectors(q, max_blocks * (logical_block_size >> 9));
	blk_queue_flag_set(QUEUE_FLAG_DISCARD, q);
पूर्ण

अटल blk_status_t sd_setup_unmap_cmnd(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_device *sdp = cmd->device;
	काष्ठा request *rq = cmd->request;
	काष्ठा scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	u64 lba = sectors_to_logical(sdp, blk_rq_pos(rq));
	u32 nr_blocks = sectors_to_logical(sdp, blk_rq_sectors(rq));
	अचिन्हित पूर्णांक data_len = 24;
	अक्षर *buf;

	rq->special_vec.bv_page = mempool_alloc(sd_page_pool, GFP_ATOMIC);
	अगर (!rq->special_vec.bv_page)
		वापस BLK_STS_RESOURCE;
	clear_highpage(rq->special_vec.bv_page);
	rq->special_vec.bv_offset = 0;
	rq->special_vec.bv_len = data_len;
	rq->rq_flags |= RQF_SPECIAL_PAYLOAD;

	cmd->cmd_len = 10;
	cmd->cmnd[0] = UNMAP;
	cmd->cmnd[8] = 24;

	buf = page_address(rq->special_vec.bv_page);
	put_unaligned_be16(6 + 16, &buf[0]);
	put_unaligned_be16(16, &buf[2]);
	put_unaligned_be64(lba, &buf[8]);
	put_unaligned_be32(nr_blocks, &buf[16]);

	cmd->allowed = sdkp->max_retries;
	cmd->transfersize = data_len;
	rq->समयout = SD_TIMEOUT;

	वापस scsi_alloc_sgtables(cmd);
पूर्ण

अटल blk_status_t sd_setup_ग_लिखो_same16_cmnd(काष्ठा scsi_cmnd *cmd,
		bool unmap)
अणु
	काष्ठा scsi_device *sdp = cmd->device;
	काष्ठा request *rq = cmd->request;
	काष्ठा scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	u64 lba = sectors_to_logical(sdp, blk_rq_pos(rq));
	u32 nr_blocks = sectors_to_logical(sdp, blk_rq_sectors(rq));
	u32 data_len = sdp->sector_size;

	rq->special_vec.bv_page = mempool_alloc(sd_page_pool, GFP_ATOMIC);
	अगर (!rq->special_vec.bv_page)
		वापस BLK_STS_RESOURCE;
	clear_highpage(rq->special_vec.bv_page);
	rq->special_vec.bv_offset = 0;
	rq->special_vec.bv_len = data_len;
	rq->rq_flags |= RQF_SPECIAL_PAYLOAD;

	cmd->cmd_len = 16;
	cmd->cmnd[0] = WRITE_SAME_16;
	अगर (unmap)
		cmd->cmnd[1] = 0x8; /* UNMAP */
	put_unaligned_be64(lba, &cmd->cmnd[2]);
	put_unaligned_be32(nr_blocks, &cmd->cmnd[10]);

	cmd->allowed = sdkp->max_retries;
	cmd->transfersize = data_len;
	rq->समयout = unmap ? SD_TIMEOUT : SD_WRITE_SAME_TIMEOUT;

	वापस scsi_alloc_sgtables(cmd);
पूर्ण

अटल blk_status_t sd_setup_ग_लिखो_same10_cmnd(काष्ठा scsi_cmnd *cmd,
		bool unmap)
अणु
	काष्ठा scsi_device *sdp = cmd->device;
	काष्ठा request *rq = cmd->request;
	काष्ठा scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	u64 lba = sectors_to_logical(sdp, blk_rq_pos(rq));
	u32 nr_blocks = sectors_to_logical(sdp, blk_rq_sectors(rq));
	u32 data_len = sdp->sector_size;

	rq->special_vec.bv_page = mempool_alloc(sd_page_pool, GFP_ATOMIC);
	अगर (!rq->special_vec.bv_page)
		वापस BLK_STS_RESOURCE;
	clear_highpage(rq->special_vec.bv_page);
	rq->special_vec.bv_offset = 0;
	rq->special_vec.bv_len = data_len;
	rq->rq_flags |= RQF_SPECIAL_PAYLOAD;

	cmd->cmd_len = 10;
	cmd->cmnd[0] = WRITE_SAME;
	अगर (unmap)
		cmd->cmnd[1] = 0x8; /* UNMAP */
	put_unaligned_be32(lba, &cmd->cmnd[2]);
	put_unaligned_be16(nr_blocks, &cmd->cmnd[7]);

	cmd->allowed = sdkp->max_retries;
	cmd->transfersize = data_len;
	rq->समयout = unmap ? SD_TIMEOUT : SD_WRITE_SAME_TIMEOUT;

	वापस scsi_alloc_sgtables(cmd);
पूर्ण

अटल blk_status_t sd_setup_ग_लिखो_zeroes_cmnd(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा request *rq = cmd->request;
	काष्ठा scsi_device *sdp = cmd->device;
	काष्ठा scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	u64 lba = sectors_to_logical(sdp, blk_rq_pos(rq));
	u32 nr_blocks = sectors_to_logical(sdp, blk_rq_sectors(rq));

	अगर (!(rq->cmd_flags & REQ_NOUNMAP)) अणु
		चयन (sdkp->zeroing_mode) अणु
		हाल SD_ZERO_WS16_UNMAP:
			वापस sd_setup_ग_लिखो_same16_cmnd(cmd, true);
		हाल SD_ZERO_WS10_UNMAP:
			वापस sd_setup_ग_लिखो_same10_cmnd(cmd, true);
		पूर्ण
	पूर्ण

	अगर (sdp->no_ग_लिखो_same) अणु
		rq->rq_flags |= RQF_QUIET;
		वापस BLK_STS_TARGET;
	पूर्ण

	अगर (sdkp->ws16 || lba > 0xffffffff || nr_blocks > 0xffff)
		वापस sd_setup_ग_लिखो_same16_cmnd(cmd, false);

	वापस sd_setup_ग_लिखो_same10_cmnd(cmd, false);
पूर्ण

अटल व्योम sd_config_ग_लिखो_same(काष्ठा scsi_disk *sdkp)
अणु
	काष्ठा request_queue *q = sdkp->disk->queue;
	अचिन्हित पूर्णांक logical_block_size = sdkp->device->sector_size;

	अगर (sdkp->device->no_ग_लिखो_same) अणु
		sdkp->max_ws_blocks = 0;
		जाओ out;
	पूर्ण

	/* Some devices can not handle block counts above 0xffff despite
	 * supporting WRITE SAME(16). Consequently we शेष to 64k
	 * blocks per I/O unless the device explicitly advertises a
	 * bigger limit.
	 */
	अगर (sdkp->max_ws_blocks > SD_MAX_WS10_BLOCKS)
		sdkp->max_ws_blocks = min_not_zero(sdkp->max_ws_blocks,
						   (u32)SD_MAX_WS16_BLOCKS);
	अन्यथा अगर (sdkp->ws16 || sdkp->ws10 || sdkp->device->no_report_opcodes)
		sdkp->max_ws_blocks = min_not_zero(sdkp->max_ws_blocks,
						   (u32)SD_MAX_WS10_BLOCKS);
	अन्यथा अणु
		sdkp->device->no_ग_लिखो_same = 1;
		sdkp->max_ws_blocks = 0;
	पूर्ण

	अगर (sdkp->lbprz && sdkp->lbpws)
		sdkp->zeroing_mode = SD_ZERO_WS16_UNMAP;
	अन्यथा अगर (sdkp->lbprz && sdkp->lbpws10)
		sdkp->zeroing_mode = SD_ZERO_WS10_UNMAP;
	अन्यथा अगर (sdkp->max_ws_blocks)
		sdkp->zeroing_mode = SD_ZERO_WS;
	अन्यथा
		sdkp->zeroing_mode = SD_ZERO_WRITE;

	अगर (sdkp->max_ws_blocks &&
	    sdkp->physical_block_size > logical_block_size) अणु
		/*
		 * Reporting a maximum number of blocks that is not aligned
		 * on the device physical size would cause a large ग_लिखो same
		 * request to be split पूर्णांकo physically unaligned chunks by
		 * __blkdev_issue_ग_लिखो_zeroes() and __blkdev_issue_ग_लिखो_same()
		 * even अगर the caller of these functions took care to align the
		 * large request. So make sure the maximum reported is aligned
		 * to the device physical block size. This is only an optional
		 * optimization क्रम regular disks, but this is mandatory to
		 * aव्योम failure of large ग_लिखो same requests directed at
		 * sequential ग_लिखो required zones of host-managed ZBC disks.
		 */
		sdkp->max_ws_blocks =
			round_करोwn(sdkp->max_ws_blocks,
				   bytes_to_logical(sdkp->device,
						    sdkp->physical_block_size));
	पूर्ण

out:
	blk_queue_max_ग_लिखो_same_sectors(q, sdkp->max_ws_blocks *
					 (logical_block_size >> 9));
	blk_queue_max_ग_लिखो_zeroes_sectors(q, sdkp->max_ws_blocks *
					 (logical_block_size >> 9));
पूर्ण

/**
 * sd_setup_ग_लिखो_same_cmnd - ग_लिखो the same data to multiple blocks
 * @cmd: command to prepare
 *
 * Will set up either WRITE SAME(10) or WRITE SAME(16) depending on
 * the preference indicated by the target device.
 **/
अटल blk_status_t sd_setup_ग_लिखो_same_cmnd(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा request *rq = cmd->request;
	काष्ठा scsi_device *sdp = cmd->device;
	काष्ठा scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	काष्ठा bio *bio = rq->bio;
	u64 lba = sectors_to_logical(sdp, blk_rq_pos(rq));
	u32 nr_blocks = sectors_to_logical(sdp, blk_rq_sectors(rq));
	blk_status_t ret;

	अगर (sdkp->device->no_ग_लिखो_same)
		वापस BLK_STS_TARGET;

	BUG_ON(bio_offset(bio) || bio_iovec(bio).bv_len != sdp->sector_size);

	rq->समयout = SD_WRITE_SAME_TIMEOUT;

	अगर (sdkp->ws16 || lba > 0xffffffff || nr_blocks > 0xffff) अणु
		cmd->cmd_len = 16;
		cmd->cmnd[0] = WRITE_SAME_16;
		put_unaligned_be64(lba, &cmd->cmnd[2]);
		put_unaligned_be32(nr_blocks, &cmd->cmnd[10]);
	पूर्ण अन्यथा अणु
		cmd->cmd_len = 10;
		cmd->cmnd[0] = WRITE_SAME;
		put_unaligned_be32(lba, &cmd->cmnd[2]);
		put_unaligned_be16(nr_blocks, &cmd->cmnd[7]);
	पूर्ण

	cmd->transfersize = sdp->sector_size;
	cmd->allowed = sdkp->max_retries;

	/*
	 * For WRITE SAME the data transferred via the DATA OUT buffer is
	 * dअगरferent from the amount of data actually written to the target.
	 *
	 * We set up __data_len to the amount of data transferred via the
	 * DATA OUT buffer so that blk_rq_map_sg sets up the proper S/G list
	 * to transfer a single sector of data first, but then reset it to
	 * the amount of data to be written right after so that the I/O path
	 * knows how much to actually ग_लिखो.
	 */
	rq->__data_len = sdp->sector_size;
	ret = scsi_alloc_sgtables(cmd);
	rq->__data_len = blk_rq_bytes(rq);

	वापस ret;
पूर्ण

अटल blk_status_t sd_setup_flush_cmnd(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा request *rq = cmd->request;
	काष्ठा scsi_disk *sdkp = scsi_disk(rq->rq_disk);

	/* flush requests करोn't perक्रमm I/O, zero the S/G table */
	स_रखो(&cmd->sdb, 0, माप(cmd->sdb));

	cmd->cmnd[0] = SYNCHRONIZE_CACHE;
	cmd->cmd_len = 10;
	cmd->transfersize = 0;
	cmd->allowed = sdkp->max_retries;

	rq->समयout = rq->q->rq_समयout * SD_FLUSH_TIMEOUT_MULTIPLIER;
	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t sd_setup_rw32_cmnd(काष्ठा scsi_cmnd *cmd, bool ग_लिखो,
				       sector_t lba, अचिन्हित पूर्णांक nr_blocks,
				       अचिन्हित अक्षर flags)
अणु
	cmd->cmnd = mempool_alloc(sd_cdb_pool, GFP_ATOMIC);
	अगर (unlikely(cmd->cmnd == शून्य))
		वापस BLK_STS_RESOURCE;

	cmd->cmd_len = SD_EXT_CDB_SIZE;
	स_रखो(cmd->cmnd, 0, cmd->cmd_len);

	cmd->cmnd[0]  = VARIABLE_LENGTH_CMD;
	cmd->cmnd[7]  = 0x18; /* Additional CDB len */
	cmd->cmnd[9]  = ग_लिखो ? WRITE_32 : READ_32;
	cmd->cmnd[10] = flags;
	put_unaligned_be64(lba, &cmd->cmnd[12]);
	put_unaligned_be32(lba, &cmd->cmnd[20]); /* Expected Indirect LBA */
	put_unaligned_be32(nr_blocks, &cmd->cmnd[28]);

	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t sd_setup_rw16_cmnd(काष्ठा scsi_cmnd *cmd, bool ग_लिखो,
				       sector_t lba, अचिन्हित पूर्णांक nr_blocks,
				       अचिन्हित अक्षर flags)
अणु
	cmd->cmd_len  = 16;
	cmd->cmnd[0]  = ग_लिखो ? WRITE_16 : READ_16;
	cmd->cmnd[1]  = flags;
	cmd->cmnd[14] = 0;
	cmd->cmnd[15] = 0;
	put_unaligned_be64(lba, &cmd->cmnd[2]);
	put_unaligned_be32(nr_blocks, &cmd->cmnd[10]);

	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t sd_setup_rw10_cmnd(काष्ठा scsi_cmnd *cmd, bool ग_लिखो,
				       sector_t lba, अचिन्हित पूर्णांक nr_blocks,
				       अचिन्हित अक्षर flags)
अणु
	cmd->cmd_len = 10;
	cmd->cmnd[0] = ग_लिखो ? WRITE_10 : READ_10;
	cmd->cmnd[1] = flags;
	cmd->cmnd[6] = 0;
	cmd->cmnd[9] = 0;
	put_unaligned_be32(lba, &cmd->cmnd[2]);
	put_unaligned_be16(nr_blocks, &cmd->cmnd[7]);

	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t sd_setup_rw6_cmnd(काष्ठा scsi_cmnd *cmd, bool ग_लिखो,
				      sector_t lba, अचिन्हित पूर्णांक nr_blocks,
				      अचिन्हित अक्षर flags)
अणु
	/* Aव्योम that 0 blocks माला_लो translated पूर्णांकo 256 blocks. */
	अगर (WARN_ON_ONCE(nr_blocks == 0))
		वापस BLK_STS_IOERR;

	अगर (unlikely(flags & 0x8)) अणु
		/*
		 * This happens only अगर this drive failed 10byte rw
		 * command with ILLEGAL_REQUEST during operation and
		 * thus turned off use_10_क्रम_rw.
		 */
		scmd_prपूर्णांकk(KERN_ERR, cmd, "FUA write on READ/WRITE(6) drive\n");
		वापस BLK_STS_IOERR;
	पूर्ण

	cmd->cmd_len = 6;
	cmd->cmnd[0] = ग_लिखो ? WRITE_6 : READ_6;
	cmd->cmnd[1] = (lba >> 16) & 0x1f;
	cmd->cmnd[2] = (lba >> 8) & 0xff;
	cmd->cmnd[3] = lba & 0xff;
	cmd->cmnd[4] = nr_blocks;
	cmd->cmnd[5] = 0;

	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t sd_setup_पढ़ो_ग_लिखो_cmnd(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा request *rq = cmd->request;
	काष्ठा scsi_device *sdp = cmd->device;
	काष्ठा scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	sector_t lba = sectors_to_logical(sdp, blk_rq_pos(rq));
	sector_t threshold;
	अचिन्हित पूर्णांक nr_blocks = sectors_to_logical(sdp, blk_rq_sectors(rq));
	अचिन्हित पूर्णांक mask = logical_to_sectors(sdp, 1) - 1;
	bool ग_लिखो = rq_data_dir(rq) == WRITE;
	अचिन्हित अक्षर protect, fua;
	blk_status_t ret;
	अचिन्हित पूर्णांक dअगर;
	bool dix;

	ret = scsi_alloc_sgtables(cmd);
	अगर (ret != BLK_STS_OK)
		वापस ret;

	ret = BLK_STS_IOERR;
	अगर (!scsi_device_online(sdp) || sdp->changed) अणु
		scmd_prपूर्णांकk(KERN_ERR, cmd, "device offline or changed\n");
		जाओ fail;
	पूर्ण

	अगर (blk_rq_pos(rq) + blk_rq_sectors(rq) > get_capacity(rq->rq_disk)) अणु
		scmd_prपूर्णांकk(KERN_ERR, cmd, "access beyond end of device\n");
		जाओ fail;
	पूर्ण

	अगर ((blk_rq_pos(rq) & mask) || (blk_rq_sectors(rq) & mask)) अणु
		scmd_prपूर्णांकk(KERN_ERR, cmd, "request not aligned to the logical block size\n");
		जाओ fail;
	पूर्ण

	/*
	 * Some SD card पढ़ोers can't handle accesses which touch the
	 * last one or two logical blocks. Split accesses as needed.
	 */
	threshold = sdkp->capacity - SD_LAST_BUGGY_SECTORS;

	अगर (unlikely(sdp->last_sector_bug && lba + nr_blocks > threshold)) अणु
		अगर (lba < threshold) अणु
			/* Access up to the threshold but not beyond */
			nr_blocks = threshold - lba;
		पूर्ण अन्यथा अणु
			/* Access only a single logical block */
			nr_blocks = 1;
		पूर्ण
	पूर्ण

	अगर (req_op(rq) == REQ_OP_ZONE_APPEND) अणु
		ret = sd_zbc_prepare_zone_append(cmd, &lba, nr_blocks);
		अगर (ret)
			जाओ fail;
	पूर्ण

	fua = rq->cmd_flags & REQ_FUA ? 0x8 : 0;
	dix = scsi_prot_sg_count(cmd);
	dअगर = scsi_host_dअगर_capable(cmd->device->host, sdkp->protection_type);

	अगर (dअगर || dix)
		protect = sd_setup_protect_cmnd(cmd, dix, dअगर);
	अन्यथा
		protect = 0;

	अगर (protect && sdkp->protection_type == T10_PI_TYPE2_PROTECTION) अणु
		ret = sd_setup_rw32_cmnd(cmd, ग_लिखो, lba, nr_blocks,
					 protect | fua);
	पूर्ण अन्यथा अगर (sdp->use_16_क्रम_rw || (nr_blocks > 0xffff)) अणु
		ret = sd_setup_rw16_cmnd(cmd, ग_लिखो, lba, nr_blocks,
					 protect | fua);
	पूर्ण अन्यथा अगर ((nr_blocks > 0xff) || (lba > 0x1fffff) ||
		   sdp->use_10_क्रम_rw || protect) अणु
		ret = sd_setup_rw10_cmnd(cmd, ग_लिखो, lba, nr_blocks,
					 protect | fua);
	पूर्ण अन्यथा अणु
		ret = sd_setup_rw6_cmnd(cmd, ग_लिखो, lba, nr_blocks,
					protect | fua);
	पूर्ण

	अगर (unlikely(ret != BLK_STS_OK))
		जाओ fail;

	/*
	 * We shouldn't disconnect in the middle of a sector, so with a dumb
	 * host adapter, it's safe to assume that we can at least transfer
	 * this many bytes between each connect / disconnect.
	 */
	cmd->transfersize = sdp->sector_size;
	cmd->underflow = nr_blocks << 9;
	cmd->allowed = sdkp->max_retries;
	cmd->sdb.length = nr_blocks * sdp->sector_size;

	SCSI_LOG_HLQUEUE(1,
			 scmd_prपूर्णांकk(KERN_INFO, cmd,
				     "%s: block=%llu, count=%d\n", __func__,
				     (अचिन्हित दीर्घ दीर्घ)blk_rq_pos(rq),
				     blk_rq_sectors(rq)));
	SCSI_LOG_HLQUEUE(2,
			 scmd_prपूर्णांकk(KERN_INFO, cmd,
				     "%s %d/%u 512 byte blocks.\n",
				     ग_लिखो ? "writing" : "reading", nr_blocks,
				     blk_rq_sectors(rq)));

	/*
	 * This indicates that the command is पढ़ोy from our end to be queued.
	 */
	वापस BLK_STS_OK;
fail:
	scsi_मुक्त_sgtables(cmd);
	वापस ret;
पूर्ण

अटल blk_status_t sd_init_command(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा request *rq = cmd->request;

	चयन (req_op(rq)) अणु
	हाल REQ_OP_DISCARD:
		चयन (scsi_disk(rq->rq_disk)->provisioning_mode) अणु
		हाल SD_LBP_UNMAP:
			वापस sd_setup_unmap_cmnd(cmd);
		हाल SD_LBP_WS16:
			वापस sd_setup_ग_लिखो_same16_cmnd(cmd, true);
		हाल SD_LBP_WS10:
			वापस sd_setup_ग_लिखो_same10_cmnd(cmd, true);
		हाल SD_LBP_ZERO:
			वापस sd_setup_ग_लिखो_same10_cmnd(cmd, false);
		शेष:
			वापस BLK_STS_TARGET;
		पूर्ण
	हाल REQ_OP_WRITE_ZEROES:
		वापस sd_setup_ग_लिखो_zeroes_cmnd(cmd);
	हाल REQ_OP_WRITE_SAME:
		वापस sd_setup_ग_लिखो_same_cmnd(cmd);
	हाल REQ_OP_FLUSH:
		वापस sd_setup_flush_cmnd(cmd);
	हाल REQ_OP_READ:
	हाल REQ_OP_WRITE:
	हाल REQ_OP_ZONE_APPEND:
		वापस sd_setup_पढ़ो_ग_लिखो_cmnd(cmd);
	हाल REQ_OP_ZONE_RESET:
		वापस sd_zbc_setup_zone_mgmt_cmnd(cmd, ZO_RESET_WRITE_POINTER,
						   false);
	हाल REQ_OP_ZONE_RESET_ALL:
		वापस sd_zbc_setup_zone_mgmt_cmnd(cmd, ZO_RESET_WRITE_POINTER,
						   true);
	हाल REQ_OP_ZONE_OPEN:
		वापस sd_zbc_setup_zone_mgmt_cmnd(cmd, ZO_OPEN_ZONE, false);
	हाल REQ_OP_ZONE_CLOSE:
		वापस sd_zbc_setup_zone_mgmt_cmnd(cmd, ZO_CLOSE_ZONE, false);
	हाल REQ_OP_ZONE_FINISH:
		वापस sd_zbc_setup_zone_mgmt_cmnd(cmd, ZO_FINISH_ZONE, false);
	शेष:
		WARN_ON_ONCE(1);
		वापस BLK_STS_NOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम sd_uninit_command(काष्ठा scsi_cmnd *SCpnt)
अणु
	काष्ठा request *rq = SCpnt->request;
	u8 *cmnd;

	अगर (rq->rq_flags & RQF_SPECIAL_PAYLOAD)
		mempool_मुक्त(rq->special_vec.bv_page, sd_page_pool);

	अगर (SCpnt->cmnd != scsi_req(rq)->cmd) अणु
		cmnd = SCpnt->cmnd;
		SCpnt->cmnd = शून्य;
		SCpnt->cmd_len = 0;
		mempool_मुक्त(cmnd, sd_cdb_pool);
	पूर्ण
पूर्ण

/**
 *	sd_खोलो - खोलो a scsi disk device
 *	@bdev: Block device of the scsi disk to खोलो
 *	@mode: FMODE_* mask
 *
 *	Returns 0 अगर successful. Returns a negated त्रुटि_सं value in हाल 
 *	of error.
 *
 *	Note: This can be called from a user context (e.g. fsck(1) )
 *	or from within the kernel (e.g. as a result of a mount(1) ).
 *	In the latter हाल @inode and @filp carry an abridged amount
 *	of inक्रमmation as noted above.
 *
 *	Locking: called with bdev->bd_mutex held.
 **/
अटल पूर्णांक sd_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा scsi_disk *sdkp = scsi_disk_get(bdev->bd_disk);
	काष्ठा scsi_device *sdev;
	पूर्णांक retval;

	अगर (!sdkp)
		वापस -ENXIO;

	SCSI_LOG_HLQUEUE(3, sd_prपूर्णांकk(KERN_INFO, sdkp, "sd_open\n"));

	sdev = sdkp->device;

	/*
	 * If the device is in error recovery, रुको until it is करोne.
	 * If the device is offline, then disallow any access to it.
	 */
	retval = -ENXIO;
	अगर (!scsi_block_when_processing_errors(sdev))
		जाओ error_out;

	अगर (sdev->removable || sdkp->ग_लिखो_prot) अणु
		अगर (bdev_check_media_change(bdev))
			sd_revalidate_disk(bdev->bd_disk);
	पूर्ण

	/*
	 * If the drive is empty, just let the खोलो fail.
	 */
	retval = -ENOMEDIUM;
	अगर (sdev->removable && !sdkp->media_present && !(mode & FMODE_NDELAY))
		जाओ error_out;

	/*
	 * If the device has the ग_लिखो protect tab set, have the खोलो fail
	 * अगर the user expects to be able to ग_लिखो to the thing.
	 */
	retval = -EROFS;
	अगर (sdkp->ग_लिखो_prot && (mode & FMODE_WRITE))
		जाओ error_out;

	/*
	 * It is possible that the disk changing stuff resulted in
	 * the device being taken offline.  If this is the हाल,
	 * report this to the user, and करोn't pretend that the
	 * खोलो actually succeeded.
	 */
	retval = -ENXIO;
	अगर (!scsi_device_online(sdev))
		जाओ error_out;

	अगर ((atomic_inc_वापस(&sdkp->खोलोers) == 1) && sdev->removable) अणु
		अगर (scsi_block_when_processing_errors(sdev))
			scsi_set_medium_removal(sdev, SCSI_REMOVAL_PREVENT);
	पूर्ण

	वापस 0;

error_out:
	scsi_disk_put(sdkp);
	वापस retval;	
पूर्ण

/**
 *	sd_release - invoked when the (last) बंद(2) is called on this
 *	scsi disk.
 *	@disk: disk to release
 *	@mode: FMODE_* mask
 *
 *	Returns 0. 
 *
 *	Note: may block (unपूर्णांकerruptible) अगर error recovery is underway
 *	on this disk.
 *
 *	Locking: called with bdev->bd_mutex held.
 **/
अटल व्योम sd_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा scsi_disk *sdkp = scsi_disk(disk);
	काष्ठा scsi_device *sdev = sdkp->device;

	SCSI_LOG_HLQUEUE(3, sd_prपूर्णांकk(KERN_INFO, sdkp, "sd_release\n"));

	अगर (atomic_dec_वापस(&sdkp->खोलोers) == 0 && sdev->removable) अणु
		अगर (scsi_block_when_processing_errors(sdev))
			scsi_set_medium_removal(sdev, SCSI_REMOVAL_ALLOW);
	पूर्ण

	scsi_disk_put(sdkp);
पूर्ण

अटल पूर्णांक sd_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा scsi_disk *sdkp = scsi_disk(bdev->bd_disk);
	काष्ठा scsi_device *sdp = sdkp->device;
	काष्ठा Scsi_Host *host = sdp->host;
	sector_t capacity = logical_to_sectors(sdp, sdkp->capacity);
	पूर्णांक diskinfo[4];

	/* शेष to most commonly used values */
	diskinfo[0] = 0x40;	/* 1 << 6 */
	diskinfo[1] = 0x20;	/* 1 << 5 */
	diskinfo[2] = capacity >> 11;

	/* override with calculated, extended शेष, or driver values */
	अगर (host->hostt->bios_param)
		host->hostt->bios_param(sdp, bdev, capacity, diskinfo);
	अन्यथा
		scsicam_bios_param(bdev, capacity, diskinfo);

	geo->heads = diskinfo[0];
	geo->sectors = diskinfo[1];
	geo->cylinders = diskinfo[2];
	वापस 0;
पूर्ण

/**
 *	sd_ioctl_common - process an ioctl
 *	@bdev: target block device
 *	@mode: FMODE_* mask
 *	@cmd: ioctl command number
 *	@p: this is third argument given to ioctl(2) प्रणाली call.
 *	Often contains a poपूर्णांकer.
 *
 *	Returns 0 अगर successful (some ioctls वापस positive numbers on
 *	success as well). Returns a negated त्रुटि_सं value in हाल of error.
 *
 *	Note: most ioctls are क्रमward onto the block subप्रणाली or further
 *	करोwn in the scsi subप्रणाली.
 **/
अटल पूर्णांक sd_ioctl_common(काष्ठा block_device *bdev, भ_शेषe_t mode,
			   अचिन्हित पूर्णांक cmd, व्योम __user *p)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	काष्ठा scsi_disk *sdkp = scsi_disk(disk);
	काष्ठा scsi_device *sdp = sdkp->device;
	पूर्णांक error;
    
	SCSI_LOG_IOCTL(1, sd_prपूर्णांकk(KERN_INFO, sdkp, "sd_ioctl: disk=%s, "
				    "cmd=0x%x\n", disk->disk_name, cmd));

	error = scsi_verअगरy_blk_ioctl(bdev, cmd);
	अगर (error < 0)
		वापस error;

	/*
	 * If we are in the middle of error recovery, करोn't let anyone
	 * अन्यथा try and use this device.  Also, अगर error recovery fails, it
	 * may try and take the device offline, in which हाल all further
	 * access to the device is prohibited.
	 */
	error = scsi_ioctl_block_when_processing_errors(sdp, cmd,
			(mode & FMODE_NDELAY) != 0);
	अगर (error)
		जाओ out;

	अगर (is_sed_ioctl(cmd))
		वापस sed_ioctl(sdkp->opal_dev, cmd, p);

	/*
	 * Send SCSI addressing ioctls directly to mid level, send other
	 * ioctls to block level and then onto mid level अगर they can't be
	 * resolved.
	 */
	चयन (cmd) अणु
		हाल SCSI_IOCTL_GET_IDLUN:
		हाल SCSI_IOCTL_GET_BUS_NUMBER:
			error = scsi_ioctl(sdp, cmd, p);
			अवरोध;
		शेष:
			error = scsi_cmd_blk_ioctl(bdev, mode, cmd, p);
			अवरोध;
	पूर्ण
out:
	वापस error;
पूर्ण

अटल व्योम set_media_not_present(काष्ठा scsi_disk *sdkp)
अणु
	अगर (sdkp->media_present)
		sdkp->device->changed = 1;

	अगर (sdkp->device->removable) अणु
		sdkp->media_present = 0;
		sdkp->capacity = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक media_not_present(काष्ठा scsi_disk *sdkp,
			     काष्ठा scsi_sense_hdr *sshdr)
अणु
	अगर (!scsi_sense_valid(sshdr))
		वापस 0;

	/* not invoked क्रम commands that could वापस deferred errors */
	चयन (sshdr->sense_key) अणु
	हाल UNIT_ATTENTION:
	हाल NOT_READY:
		/* medium not present */
		अगर (sshdr->asc == 0x3A) अणु
			set_media_not_present(sdkp);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	sd_check_events - check media events
 *	@disk: kernel device descriptor
 *	@clearing: disk events currently being cleared
 *
 *	Returns mask of DISK_EVENT_*.
 *
 *	Note: this function is invoked from the block subप्रणाली.
 **/
अटल अचिन्हित पूर्णांक sd_check_events(काष्ठा gendisk *disk, अचिन्हित पूर्णांक clearing)
अणु
	काष्ठा scsi_disk *sdkp = scsi_disk_get(disk);
	काष्ठा scsi_device *sdp;
	पूर्णांक retval;
	bool disk_changed;

	अगर (!sdkp)
		वापस 0;

	sdp = sdkp->device;
	SCSI_LOG_HLQUEUE(3, sd_prपूर्णांकk(KERN_INFO, sdkp, "sd_check_events\n"));

	/*
	 * If the device is offline, करोn't send any commands - just pretend as
	 * अगर the command failed.  If the device ever comes back online, we
	 * can deal with it then.  It is only because of unrecoverable errors
	 * that we would ever take a device offline in the first place.
	 */
	अगर (!scsi_device_online(sdp)) अणु
		set_media_not_present(sdkp);
		जाओ out;
	पूर्ण

	/*
	 * Using TEST_UNIT_READY enables dअगरferentiation between drive with
	 * no cartridge loaded - NOT READY, drive with changed cartridge -
	 * UNIT ATTENTION, or with same cartridge - GOOD STATUS.
	 *
	 * Drives that स्वतः spin करोwn. eg iomega jaz 1G, will be started
	 * by sd_spinup_disk() from sd_revalidate_disk(), which happens whenever
	 * sd_revalidate() is called.
	 */
	अगर (scsi_block_when_processing_errors(sdp)) अणु
		काष्ठा scsi_sense_hdr sshdr = अणु 0, पूर्ण;

		retval = scsi_test_unit_पढ़ोy(sdp, SD_TIMEOUT, sdkp->max_retries,
					      &sshdr);

		/* failed to execute TUR, assume media not present */
		अगर (host_byte(retval)) अणु
			set_media_not_present(sdkp);
			जाओ out;
		पूर्ण

		अगर (media_not_present(sdkp, &sshdr))
			जाओ out;
	पूर्ण

	/*
	 * For removable scsi disk we have to recognise the presence
	 * of a disk in the drive.
	 */
	अगर (!sdkp->media_present)
		sdp->changed = 1;
	sdkp->media_present = 1;
out:
	/*
	 * sdp->changed is set under the following conditions:
	 *
	 *	Medium present state has changed in either direction.
	 *	Device has indicated UNIT_ATTENTION.
	 */
	disk_changed = sdp->changed;
	sdp->changed = 0;
	scsi_disk_put(sdkp);
	वापस disk_changed ? DISK_EVENT_MEDIA_CHANGE : 0;
पूर्ण

अटल पूर्णांक sd_sync_cache(काष्ठा scsi_disk *sdkp, काष्ठा scsi_sense_hdr *sshdr)
अणु
	पूर्णांक retries, res;
	काष्ठा scsi_device *sdp = sdkp->device;
	स्थिर पूर्णांक समयout = sdp->request_queue->rq_समयout
		* SD_FLUSH_TIMEOUT_MULTIPLIER;
	काष्ठा scsi_sense_hdr my_sshdr;

	अगर (!scsi_device_online(sdp))
		वापस -ENODEV;

	/* caller might not be पूर्णांकerested in sense, but we need it */
	अगर (!sshdr)
		sshdr = &my_sshdr;

	क्रम (retries = 3; retries > 0; --retries) अणु
		अचिन्हित अक्षर cmd[10] = अणु 0 पूर्ण;

		cmd[0] = SYNCHRONIZE_CACHE;
		/*
		 * Leave the rest of the command zero to indicate
		 * flush everything.
		 */
		res = scsi_execute(sdp, cmd, DMA_NONE, शून्य, 0, शून्य, sshdr,
				समयout, sdkp->max_retries, 0, RQF_PM, शून्य);
		अगर (res == 0)
			अवरोध;
	पूर्ण

	अगर (res) अणु
		sd_prपूर्णांक_result(sdkp, "Synchronize Cache(10) failed", res);

		अगर (driver_byte(res) == DRIVER_SENSE)
			sd_prपूर्णांक_sense_hdr(sdkp, sshdr);

		/* we need to evaluate the error वापस  */
		अगर (scsi_sense_valid(sshdr) &&
			(sshdr->asc == 0x3a ||	/* medium not present */
			 sshdr->asc == 0x20 ||	/* invalid command */
			 (sshdr->asc == 0x74 && sshdr->ascq == 0x71)))	/* drive is password locked */
				/* this is no error here */
				वापस 0;

		चयन (host_byte(res)) अणु
		/* ignore errors due to racing a disconnection */
		हाल DID_BAD_TARGET:
		हाल DID_NO_CONNECT:
			वापस 0;
		/* संकेत the upper layer it might try again */
		हाल DID_BUS_BUSY:
		हाल DID_IMM_RETRY:
		हाल DID_REQUEUE:
		हाल DID_SOFT_ERROR:
			वापस -EBUSY;
		शेष:
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sd_rescan(काष्ठा device *dev)
अणु
	काष्ठा scsi_disk *sdkp = dev_get_drvdata(dev);

	sd_revalidate_disk(sdkp->disk);
पूर्ण

अटल पूर्णांक sd_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *p = (व्योम __user *)arg;
	पूर्णांक ret;

	ret = sd_ioctl_common(bdev, mode, cmd, p);
	अगर (ret != -ENOTTY)
		वापस ret;

	वापस scsi_ioctl(scsi_disk(bdev->bd_disk)->device, cmd, p);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक sd_compat_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *p = compat_ptr(arg);
	पूर्णांक ret;

	ret = sd_ioctl_common(bdev, mode, cmd, p);
	अगर (ret != -ENOTTY)
		वापस ret;

	वापस scsi_compat_ioctl(scsi_disk(bdev->bd_disk)->device, cmd, p);
पूर्ण
#पूर्ण_अगर

अटल अक्षर sd_pr_type(क्रमागत pr_type type)
अणु
	चयन (type) अणु
	हाल PR_WRITE_EXCLUSIVE:
		वापस 0x01;
	हाल PR_EXCLUSIVE_ACCESS:
		वापस 0x03;
	हाल PR_WRITE_EXCLUSIVE_REG_ONLY:
		वापस 0x05;
	हाल PR_EXCLUSIVE_ACCESS_REG_ONLY:
		वापस 0x06;
	हाल PR_WRITE_EXCLUSIVE_ALL_REGS:
		वापस 0x07;
	हाल PR_EXCLUSIVE_ACCESS_ALL_REGS:
		वापस 0x08;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण;

अटल पूर्णांक sd_pr_command(काष्ठा block_device *bdev, u8 sa,
		u64 key, u64 sa_key, u8 type, u8 flags)
अणु
	काष्ठा scsi_disk *sdkp = scsi_disk(bdev->bd_disk);
	काष्ठा scsi_device *sdev = sdkp->device;
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक result;
	u8 cmd[16] = अणु 0, पूर्ण;
	u8 data[24] = अणु 0, पूर्ण;

	cmd[0] = PERSISTENT_RESERVE_OUT;
	cmd[1] = sa;
	cmd[2] = type;
	put_unaligned_be32(माप(data), &cmd[5]);

	put_unaligned_be64(key, &data[0]);
	put_unaligned_be64(sa_key, &data[8]);
	data[20] = flags;

	result = scsi_execute_req(sdev, cmd, DMA_TO_DEVICE, &data, माप(data),
			&sshdr, SD_TIMEOUT, sdkp->max_retries, शून्य);

	अगर (driver_byte(result) == DRIVER_SENSE &&
	    scsi_sense_valid(&sshdr)) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev, "PR command failed: %d\n", result);
		scsi_prपूर्णांक_sense_hdr(sdev, शून्य, &sshdr);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक sd_pr_रेजिस्टर(काष्ठा block_device *bdev, u64 old_key, u64 new_key,
		u32 flags)
अणु
	अगर (flags & ~PR_FL_IGNORE_KEY)
		वापस -EOPNOTSUPP;
	वापस sd_pr_command(bdev, (flags & PR_FL_IGNORE_KEY) ? 0x06 : 0x00,
			old_key, new_key, 0,
			(1 << 0) /* APTPL */);
पूर्ण

अटल पूर्णांक sd_pr_reserve(काष्ठा block_device *bdev, u64 key, क्रमागत pr_type type,
		u32 flags)
अणु
	अगर (flags)
		वापस -EOPNOTSUPP;
	वापस sd_pr_command(bdev, 0x01, key, 0, sd_pr_type(type), 0);
पूर्ण

अटल पूर्णांक sd_pr_release(काष्ठा block_device *bdev, u64 key, क्रमागत pr_type type)
अणु
	वापस sd_pr_command(bdev, 0x02, key, 0, sd_pr_type(type), 0);
पूर्ण

अटल पूर्णांक sd_pr_preempt(काष्ठा block_device *bdev, u64 old_key, u64 new_key,
		क्रमागत pr_type type, bool पात)
अणु
	वापस sd_pr_command(bdev, पात ? 0x05 : 0x04, old_key, new_key,
			     sd_pr_type(type), 0);
पूर्ण

अटल पूर्णांक sd_pr_clear(काष्ठा block_device *bdev, u64 key)
अणु
	वापस sd_pr_command(bdev, 0x03, key, 0, 0, 0);
पूर्ण

अटल स्थिर काष्ठा pr_ops sd_pr_ops = अणु
	.pr_रेजिस्टर	= sd_pr_रेजिस्टर,
	.pr_reserve	= sd_pr_reserve,
	.pr_release	= sd_pr_release,
	.pr_preempt	= sd_pr_preempt,
	.pr_clear	= sd_pr_clear,
पूर्ण;

अटल स्थिर काष्ठा block_device_operations sd_fops = अणु
	.owner			= THIS_MODULE,
	.खोलो			= sd_खोलो,
	.release		= sd_release,
	.ioctl			= sd_ioctl,
	.getgeo			= sd_getgeo,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= sd_compat_ioctl,
#पूर्ण_अगर
	.check_events		= sd_check_events,
	.unlock_native_capacity	= sd_unlock_native_capacity,
	.report_zones		= sd_zbc_report_zones,
	.pr_ops			= &sd_pr_ops,
पूर्ण;

/**
 *	sd_eh_reset - reset error handling callback
 *	@scmd:		sd-issued command that has failed
 *
 *	This function is called by the SCSI midlayer beक्रमe starting
 *	SCSI EH. When counting medium access failures we have to be
 *	careful to रेजिस्टर it only only once per device and SCSI EH run;
 *	there might be several समयd out commands which will cause the
 *	'max_medium_access_timeouts' counter to trigger after the first
 *	SCSI EH run alपढ़ोy and set the device to offline.
 *	So this function resets the पूर्णांकernal counter beक्रमe starting SCSI EH.
 **/
अटल व्योम sd_eh_reset(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा scsi_disk *sdkp = scsi_disk(scmd->request->rq_disk);

	/* New SCSI EH run, reset gate variable */
	sdkp->ignore_medium_access_errors = false;
पूर्ण

/**
 *	sd_eh_action - error handling callback
 *	@scmd:		sd-issued command that has failed
 *	@eh_disp:	The recovery disposition suggested by the midlayer
 *
 *	This function is called by the SCSI midlayer upon completion of an
 *	error test command (currently TEST UNIT READY). The result of sending
 *	the eh command is passed in eh_disp.  We're looking क्रम devices that
 *	fail medium access commands but are OK with non access commands like
 *	test unit पढ़ोy (so wrongly see the device as having a successful
 *	recovery)
 **/
अटल पूर्णांक sd_eh_action(काष्ठा scsi_cmnd *scmd, पूर्णांक eh_disp)
अणु
	काष्ठा scsi_disk *sdkp = scsi_disk(scmd->request->rq_disk);
	काष्ठा scsi_device *sdev = scmd->device;

	अगर (!scsi_device_online(sdev) ||
	    !scsi_medium_access_command(scmd) ||
	    host_byte(scmd->result) != DID_TIME_OUT ||
	    eh_disp != SUCCESS)
		वापस eh_disp;

	/*
	 * The device has समयd out executing a medium access command.
	 * However, the TEST UNIT READY command sent during error
	 * handling completed successfully. Either the device is in the
	 * process of recovering or has it suffered an पूर्णांकernal failure
	 * that prevents access to the storage medium.
	 */
	अगर (!sdkp->ignore_medium_access_errors) अणु
		sdkp->medium_access_समयd_out++;
		sdkp->ignore_medium_access_errors = true;
	पूर्ण

	/*
	 * If the device keeps failing पढ़ो/ग_लिखो commands but TEST UNIT
	 * READY always completes successfully we assume that medium
	 * access is no दीर्घer possible and take the device offline.
	 */
	अगर (sdkp->medium_access_समयd_out >= sdkp->max_medium_access_समयouts) अणु
		scmd_prपूर्णांकk(KERN_ERR, scmd,
			    "Medium access timeout failure. Offlining disk!\n");
		mutex_lock(&sdev->state_mutex);
		scsi_device_set_state(sdev, SDEV_OFFLINE);
		mutex_unlock(&sdev->state_mutex);

		वापस SUCCESS;
	पूर्ण

	वापस eh_disp;
पूर्ण

अटल अचिन्हित पूर्णांक sd_completed_bytes(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा request *req = scmd->request;
	काष्ठा scsi_device *sdev = scmd->device;
	अचिन्हित पूर्णांक transferred, good_bytes;
	u64 start_lba, end_lba, bad_lba;

	/*
	 * Some commands have a payload smaller than the device logical
	 * block size (e.g. INQUIRY on a 4K disk).
	 */
	अगर (scsi_bufflen(scmd) <= sdev->sector_size)
		वापस 0;

	/* Check अगर we have a 'bad_lba' inक्रमmation */
	अगर (!scsi_get_sense_info_fld(scmd->sense_buffer,
				     SCSI_SENSE_BUFFERSIZE,
				     &bad_lba))
		वापस 0;

	/*
	 * If the bad lba was reported incorrectly, we have no idea where
	 * the error is.
	 */
	start_lba = sectors_to_logical(sdev, blk_rq_pos(req));
	end_lba = start_lba + bytes_to_logical(sdev, scsi_bufflen(scmd));
	अगर (bad_lba < start_lba || bad_lba >= end_lba)
		वापस 0;

	/*
	 * resid is optional but mostly filled in.  When it's unused,
	 * its value is zero, so we assume the whole buffer transferred
	 */
	transferred = scsi_bufflen(scmd) - scsi_get_resid(scmd);

	/* This computation should always be करोne in terms of the
	 * resolution of the device's medium.
	 */
	good_bytes = logical_to_bytes(sdev, bad_lba - start_lba);

	वापस min(good_bytes, transferred);
पूर्ण

/**
 *	sd_करोne - bottom half handler: called when the lower level
 *	driver has completed (successfully or otherwise) a scsi command.
 *	@SCpnt: mid-level's per command काष्ठाure.
 *
 *	Note: potentially run from within an ISR. Must not block.
 **/
अटल पूर्णांक sd_करोne(काष्ठा scsi_cmnd *SCpnt)
अणु
	पूर्णांक result = SCpnt->result;
	अचिन्हित पूर्णांक good_bytes = result ? 0 : scsi_bufflen(SCpnt);
	अचिन्हित पूर्णांक sector_size = SCpnt->device->sector_size;
	अचिन्हित पूर्णांक resid;
	काष्ठा scsi_sense_hdr sshdr;
	काष्ठा scsi_disk *sdkp = scsi_disk(SCpnt->request->rq_disk);
	काष्ठा request *req = SCpnt->request;
	पूर्णांक sense_valid = 0;
	पूर्णांक sense_deferred = 0;

	चयन (req_op(req)) अणु
	हाल REQ_OP_DISCARD:
	हाल REQ_OP_WRITE_ZEROES:
	हाल REQ_OP_WRITE_SAME:
	हाल REQ_OP_ZONE_RESET:
	हाल REQ_OP_ZONE_RESET_ALL:
	हाल REQ_OP_ZONE_OPEN:
	हाल REQ_OP_ZONE_CLOSE:
	हाल REQ_OP_ZONE_FINISH:
		अगर (!result) अणु
			good_bytes = blk_rq_bytes(req);
			scsi_set_resid(SCpnt, 0);
		पूर्ण अन्यथा अणु
			good_bytes = 0;
			scsi_set_resid(SCpnt, blk_rq_bytes(req));
		पूर्ण
		अवरोध;
	शेष:
		/*
		 * In हाल of bogus fw or device, we could end up having
		 * an unaligned partial completion. Check this here and क्रमce
		 * alignment.
		 */
		resid = scsi_get_resid(SCpnt);
		अगर (resid & (sector_size - 1)) अणु
			sd_prपूर्णांकk(KERN_INFO, sdkp,
				"Unaligned partial completion (resid=%u, sector_sz=%u)\n",
				resid, sector_size);
			scsi_prपूर्णांक_command(SCpnt);
			resid = min(scsi_bufflen(SCpnt),
				    round_up(resid, sector_size));
			scsi_set_resid(SCpnt, resid);
		पूर्ण
	पूर्ण

	अगर (result) अणु
		sense_valid = scsi_command_normalize_sense(SCpnt, &sshdr);
		अगर (sense_valid)
			sense_deferred = scsi_sense_is_deferred(&sshdr);
	पूर्ण
	sdkp->medium_access_समयd_out = 0;

	अगर (driver_byte(result) != DRIVER_SENSE &&
	    (!sense_valid || sense_deferred))
		जाओ out;

	चयन (sshdr.sense_key) अणु
	हाल HARDWARE_ERROR:
	हाल MEDIUM_ERROR:
		good_bytes = sd_completed_bytes(SCpnt);
		अवरोध;
	हाल RECOVERED_ERROR:
		good_bytes = scsi_bufflen(SCpnt);
		अवरोध;
	हाल NO_SENSE:
		/* This indicates a false check condition, so ignore it.  An
		 * unknown amount of data was transferred so treat it as an
		 * error.
		 */
		SCpnt->result = 0;
		स_रखो(SCpnt->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
		अवरोध;
	हाल ABORTED_COMMAND:
		अगर (sshdr.asc == 0x10)  /* DIF: Target detected corruption */
			good_bytes = sd_completed_bytes(SCpnt);
		अवरोध;
	हाल ILLEGAL_REQUEST:
		चयन (sshdr.asc) अणु
		हाल 0x10:	/* DIX: Host detected corruption */
			good_bytes = sd_completed_bytes(SCpnt);
			अवरोध;
		हाल 0x20:	/* INVALID COMMAND OPCODE */
		हाल 0x24:	/* INVALID FIELD IN CDB */
			चयन (SCpnt->cmnd[0]) अणु
			हाल UNMAP:
				sd_config_discard(sdkp, SD_LBP_DISABLE);
				अवरोध;
			हाल WRITE_SAME_16:
			हाल WRITE_SAME:
				अगर (SCpnt->cmnd[1] & 8) अणु /* UNMAP */
					sd_config_discard(sdkp, SD_LBP_DISABLE);
				पूर्ण अन्यथा अणु
					sdkp->device->no_ग_लिखो_same = 1;
					sd_config_ग_लिखो_same(sdkp);
					req->rq_flags |= RQF_QUIET;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

 out:
	अगर (sd_is_zoned(sdkp))
		good_bytes = sd_zbc_complete(SCpnt, good_bytes, &sshdr);

	SCSI_LOG_HLCOMPLETE(1, scmd_prपूर्णांकk(KERN_INFO, SCpnt,
					   "sd_done: completed %d of %d bytes\n",
					   good_bytes, scsi_bufflen(SCpnt)));

	वापस good_bytes;
पूर्ण

/*
 * spinup disk - called only in sd_revalidate_disk()
 */
अटल व्योम
sd_spinup_disk(काष्ठा scsi_disk *sdkp)
अणु
	अचिन्हित अक्षर cmd[10];
	अचिन्हित दीर्घ spपूर्णांकime_expire = 0;
	पूर्णांक retries, spपूर्णांकime;
	अचिन्हित पूर्णांक the_result;
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक sense_valid = 0;

	spपूर्णांकime = 0;

	/* Spin up drives, as required.  Only करो this at boot समय */
	/* Spinup needs to be करोne क्रम module loads too. */
	करो अणु
		retries = 0;

		करो अणु
			cmd[0] = TEST_UNIT_READY;
			स_रखो((व्योम *) &cmd[1], 0, 9);

			the_result = scsi_execute_req(sdkp->device, cmd,
						      DMA_NONE, शून्य, 0,
						      &sshdr, SD_TIMEOUT,
						      sdkp->max_retries, शून्य);

			/*
			 * If the drive has indicated to us that it
			 * करोesn't have any media in it, don't bother
			 * with any more polling.
			 */
			अगर (media_not_present(sdkp, &sshdr))
				वापस;

			अगर (the_result)
				sense_valid = scsi_sense_valid(&sshdr);
			retries++;
		पूर्ण जबतक (retries < 3 && 
			 (!scsi_status_is_good(the_result) ||
			  ((driver_byte(the_result) == DRIVER_SENSE) &&
			  sense_valid && sshdr.sense_key == UNIT_ATTENTION)));

		अगर (driver_byte(the_result) != DRIVER_SENSE) अणु
			/* no sense, TUR either succeeded or failed
			 * with a status error */
			अगर(!spपूर्णांकime && !scsi_status_is_good(the_result)) अणु
				sd_prपूर्णांक_result(sdkp, "Test Unit Ready failed",
						the_result);
			पूर्ण
			अवरोध;
		पूर्ण

		/*
		 * The device करोes not want the स्वतःmatic start to be issued.
		 */
		अगर (sdkp->device->no_start_on_add)
			अवरोध;

		अगर (sense_valid && sshdr.sense_key == NOT_READY) अणु
			अगर (sshdr.asc == 4 && sshdr.ascq == 3)
				अवरोध;	/* manual पूर्णांकervention required */
			अगर (sshdr.asc == 4 && sshdr.ascq == 0xb)
				अवरोध;	/* standby */
			अगर (sshdr.asc == 4 && sshdr.ascq == 0xc)
				अवरोध;	/* unavailable */
			अगर (sshdr.asc == 4 && sshdr.ascq == 0x1b)
				अवरोध;	/* sanitize in progress */
			/*
			 * Issue command to spin up drive when not पढ़ोy
			 */
			अगर (!spपूर्णांकime) अणु
				sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Spinning up disk...");
				cmd[0] = START_STOP;
				cmd[1] = 1;	/* Return immediately */
				स_रखो((व्योम *) &cmd[2], 0, 8);
				cmd[4] = 1;	/* Start spin cycle */
				अगर (sdkp->device->start_stop_pwr_cond)
					cmd[4] |= 1 << 4;
				scsi_execute_req(sdkp->device, cmd, DMA_NONE,
						 शून्य, 0, &sshdr,
						 SD_TIMEOUT, sdkp->max_retries,
						 शून्य);
				spपूर्णांकime_expire = jअगरfies + 100 * HZ;
				spपूर्णांकime = 1;
			पूर्ण
			/* Wait 1 second क्रम next try */
			msleep(1000);
			prपूर्णांकk(KERN_CONT ".");

		/*
		 * Wait क्रम USB flash devices with slow firmware.
		 * Yes, this sense key/ASC combination shouldn't
		 * occur here.  It's अक्षरacteristic of these devices.
		 */
		पूर्ण अन्यथा अगर (sense_valid &&
				sshdr.sense_key == UNIT_ATTENTION &&
				sshdr.asc == 0x28) अणु
			अगर (!spपूर्णांकime) अणु
				spपूर्णांकime_expire = jअगरfies + 5 * HZ;
				spपूर्णांकime = 1;
			पूर्ण
			/* Wait 1 second क्रम next try */
			msleep(1000);
		पूर्ण अन्यथा अणु
			/* we करोn't understand the sense code, so it's
			 * probably poपूर्णांकless to loop */
			अगर(!spपूर्णांकime) अणु
				sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Unit Not Ready\n");
				sd_prपूर्णांक_sense_hdr(sdkp, &sshdr);
			पूर्ण
			अवरोध;
		पूर्ण
				
	पूर्ण जबतक (spपूर्णांकime && समय_beक्रमe_eq(jअगरfies, spपूर्णांकime_expire));

	अगर (spपूर्णांकime) अणु
		अगर (scsi_status_is_good(the_result))
			prपूर्णांकk(KERN_CONT "ready\n");
		अन्यथा
			prपूर्णांकk(KERN_CONT "not responding...\n");
	पूर्ण
पूर्ण

/*
 * Determine whether disk supports Data Integrity Field.
 */
अटल पूर्णांक sd_पढ़ो_protection_type(काष्ठा scsi_disk *sdkp, अचिन्हित अक्षर *buffer)
अणु
	काष्ठा scsi_device *sdp = sdkp->device;
	u8 type;
	पूर्णांक ret = 0;

	अगर (scsi_device_protection(sdp) == 0 || (buffer[12] & 1) == 0) अणु
		sdkp->protection_type = 0;
		वापस ret;
	पूर्ण

	type = ((buffer[12] >> 1) & 7) + 1; /* P_TYPE 0 = Type 1 */

	अगर (type > T10_PI_TYPE3_PROTECTION)
		ret = -ENODEV;
	अन्यथा अगर (scsi_host_dअगर_capable(sdp->host, type))
		ret = 1;

	अगर (sdkp->first_scan || type != sdkp->protection_type)
		चयन (ret) अणु
		हाल -ENODEV:
			sd_prपूर्णांकk(KERN_ERR, sdkp, "formatted with unsupported" \
				  " protection type %u. Disabling disk!\n",
				  type);
			अवरोध;
		हाल 1:
			sd_prपूर्णांकk(KERN_NOTICE, sdkp,
				  "Enabling DIF Type %u protection\n", type);
			अवरोध;
		हाल 0:
			sd_prपूर्णांकk(KERN_NOTICE, sdkp,
				  "Disabling DIF Type %u protection\n", type);
			अवरोध;
		पूर्ण

	sdkp->protection_type = type;

	वापस ret;
पूर्ण

अटल व्योम पढ़ो_capacity_error(काष्ठा scsi_disk *sdkp, काष्ठा scsi_device *sdp,
			काष्ठा scsi_sense_hdr *sshdr, पूर्णांक sense_valid,
			पूर्णांक the_result)
अणु
	अगर (driver_byte(the_result) == DRIVER_SENSE)
		sd_prपूर्णांक_sense_hdr(sdkp, sshdr);
	अन्यथा
		sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Sense not available.\n");

	/*
	 * Set dirty bit क्रम removable devices अगर not पढ़ोy -
	 * someबार drives will not report this properly.
	 */
	अगर (sdp->removable &&
	    sense_valid && sshdr->sense_key == NOT_READY)
		set_media_not_present(sdkp);

	/*
	 * We used to set media_present to 0 here to indicate no media
	 * in the drive, but some drives fail पढ़ो capacity even with
	 * media present, so we can't करो that.
	 */
	sdkp->capacity = 0; /* unknown mapped to zero - as usual */
पूर्ण

#घोषणा RC16_LEN 32
#अगर RC16_LEN > SD_BUF_SIZE
#त्रुटि RC16_LEN must not be more than SD_BUF_SIZE
#पूर्ण_अगर

#घोषणा READ_CAPACITY_RETRIES_ON_RESET	10

अटल पूर्णांक पढ़ो_capacity_16(काष्ठा scsi_disk *sdkp, काष्ठा scsi_device *sdp,
						अचिन्हित अक्षर *buffer)
अणु
	अचिन्हित अक्षर cmd[16];
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक sense_valid = 0;
	पूर्णांक the_result;
	पूर्णांक retries = 3, reset_retries = READ_CAPACITY_RETRIES_ON_RESET;
	अचिन्हित पूर्णांक alignment;
	अचिन्हित दीर्घ दीर्घ lba;
	अचिन्हित sector_size;

	अगर (sdp->no_पढ़ो_capacity_16)
		वापस -EINVAL;

	करो अणु
		स_रखो(cmd, 0, 16);
		cmd[0] = SERVICE_ACTION_IN_16;
		cmd[1] = SAI_READ_CAPACITY_16;
		cmd[13] = RC16_LEN;
		स_रखो(buffer, 0, RC16_LEN);

		the_result = scsi_execute_req(sdp, cmd, DMA_FROM_DEVICE,
					buffer, RC16_LEN, &sshdr,
					SD_TIMEOUT, sdkp->max_retries, शून्य);

		अगर (media_not_present(sdkp, &sshdr))
			वापस -ENODEV;

		अगर (the_result) अणु
			sense_valid = scsi_sense_valid(&sshdr);
			अगर (sense_valid &&
			    sshdr.sense_key == ILLEGAL_REQUEST &&
			    (sshdr.asc == 0x20 || sshdr.asc == 0x24) &&
			    sshdr.ascq == 0x00)
				/* Invalid Command Operation Code or
				 * Invalid Field in CDB, just retry
				 * silently with RC10 */
				वापस -EINVAL;
			अगर (sense_valid &&
			    sshdr.sense_key == UNIT_ATTENTION &&
			    sshdr.asc == 0x29 && sshdr.ascq == 0x00)
				/* Device reset might occur several बार,
				 * give it one more chance */
				अगर (--reset_retries > 0)
					जारी;
		पूर्ण
		retries--;

	पूर्ण जबतक (the_result && retries);

	अगर (the_result) अणु
		sd_prपूर्णांक_result(sdkp, "Read Capacity(16) failed", the_result);
		पढ़ो_capacity_error(sdkp, sdp, &sshdr, sense_valid, the_result);
		वापस -EINVAL;
	पूर्ण

	sector_size = get_unaligned_be32(&buffer[8]);
	lba = get_unaligned_be64(&buffer[0]);

	अगर (sd_पढ़ो_protection_type(sdkp, buffer) < 0) अणु
		sdkp->capacity = 0;
		वापस -ENODEV;
	पूर्ण

	/* Logical blocks per physical block exponent */
	sdkp->physical_block_size = (1 << (buffer[13] & 0xf)) * sector_size;

	/* RC basis */
	sdkp->rc_basis = (buffer[12] >> 4) & 0x3;

	/* Lowest aligned logical block */
	alignment = ((buffer[14] & 0x3f) << 8 | buffer[15]) * sector_size;
	blk_queue_alignment_offset(sdp->request_queue, alignment);
	अगर (alignment && sdkp->first_scan)
		sd_prपूर्णांकk(KERN_NOTICE, sdkp,
			  "physical block alignment offset: %u\n", alignment);

	अगर (buffer[14] & 0x80) अणु /* LBPME */
		sdkp->lbpme = 1;

		अगर (buffer[14] & 0x40) /* LBPRZ */
			sdkp->lbprz = 1;

		sd_config_discard(sdkp, SD_LBP_WS16);
	पूर्ण

	sdkp->capacity = lba + 1;
	वापस sector_size;
पूर्ण

अटल पूर्णांक पढ़ो_capacity_10(काष्ठा scsi_disk *sdkp, काष्ठा scsi_device *sdp,
						अचिन्हित अक्षर *buffer)
अणु
	अचिन्हित अक्षर cmd[16];
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक sense_valid = 0;
	पूर्णांक the_result;
	पूर्णांक retries = 3, reset_retries = READ_CAPACITY_RETRIES_ON_RESET;
	sector_t lba;
	अचिन्हित sector_size;

	करो अणु
		cmd[0] = READ_CAPACITY;
		स_रखो(&cmd[1], 0, 9);
		स_रखो(buffer, 0, 8);

		the_result = scsi_execute_req(sdp, cmd, DMA_FROM_DEVICE,
					buffer, 8, &sshdr,
					SD_TIMEOUT, sdkp->max_retries, शून्य);

		अगर (media_not_present(sdkp, &sshdr))
			वापस -ENODEV;

		अगर (the_result) अणु
			sense_valid = scsi_sense_valid(&sshdr);
			अगर (sense_valid &&
			    sshdr.sense_key == UNIT_ATTENTION &&
			    sshdr.asc == 0x29 && sshdr.ascq == 0x00)
				/* Device reset might occur several बार,
				 * give it one more chance */
				अगर (--reset_retries > 0)
					जारी;
		पूर्ण
		retries--;

	पूर्ण जबतक (the_result && retries);

	अगर (the_result) अणु
		sd_prपूर्णांक_result(sdkp, "Read Capacity(10) failed", the_result);
		पढ़ो_capacity_error(sdkp, sdp, &sshdr, sense_valid, the_result);
		वापस -EINVAL;
	पूर्ण

	sector_size = get_unaligned_be32(&buffer[4]);
	lba = get_unaligned_be32(&buffer[0]);

	अगर (sdp->no_पढ़ो_capacity_16 && (lba == 0xffffffff)) अणु
		/* Some buggy (usb cardपढ़ोer) devices वापस an lba of
		   0xffffffff when the want to report a size of 0 (with
		   which they really mean no media is present) */
		sdkp->capacity = 0;
		sdkp->physical_block_size = sector_size;
		वापस sector_size;
	पूर्ण

	sdkp->capacity = lba + 1;
	sdkp->physical_block_size = sector_size;
	वापस sector_size;
पूर्ण

अटल पूर्णांक sd_try_rc16_first(काष्ठा scsi_device *sdp)
अणु
	अगर (sdp->host->max_cmd_len < 16)
		वापस 0;
	अगर (sdp->try_rc_10_first)
		वापस 0;
	अगर (sdp->scsi_level > SCSI_SPC_2)
		वापस 1;
	अगर (scsi_device_protection(sdp))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * पढ़ो disk capacity
 */
अटल व्योम
sd_पढ़ो_capacity(काष्ठा scsi_disk *sdkp, अचिन्हित अक्षर *buffer)
अणु
	पूर्णांक sector_size;
	काष्ठा scsi_device *sdp = sdkp->device;

	अगर (sd_try_rc16_first(sdp)) अणु
		sector_size = पढ़ो_capacity_16(sdkp, sdp, buffer);
		अगर (sector_size == -EOVERFLOW)
			जाओ got_data;
		अगर (sector_size == -ENODEV)
			वापस;
		अगर (sector_size < 0)
			sector_size = पढ़ो_capacity_10(sdkp, sdp, buffer);
		अगर (sector_size < 0)
			वापस;
	पूर्ण अन्यथा अणु
		sector_size = पढ़ो_capacity_10(sdkp, sdp, buffer);
		अगर (sector_size == -EOVERFLOW)
			जाओ got_data;
		अगर (sector_size < 0)
			वापस;
		अगर ((माप(sdkp->capacity) > 4) &&
		    (sdkp->capacity > 0xffffffffULL)) अणु
			पूर्णांक old_sector_size = sector_size;
			sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Very big device. "
					"Trying to use READ CAPACITY(16).\n");
			sector_size = पढ़ो_capacity_16(sdkp, sdp, buffer);
			अगर (sector_size < 0) अणु
				sd_prपूर्णांकk(KERN_NOTICE, sdkp,
					"Using 0xffffffff as device size\n");
				sdkp->capacity = 1 + (sector_t) 0xffffffff;
				sector_size = old_sector_size;
				जाओ got_data;
			पूर्ण
			/* Remember that READ CAPACITY(16) succeeded */
			sdp->try_rc_10_first = 0;
		पूर्ण
	पूर्ण

	/* Some devices are known to वापस the total number of blocks,
	 * not the highest block number.  Some devices have versions
	 * which करो this and others which करो not.  Some devices we might
	 * suspect of करोing this but we करोn't know क्रम certain.
	 *
	 * If we know the reported capacity is wrong, decrement it.  If
	 * we can only guess, then assume the number of blocks is even
	 * (usually true but not always) and err on the side of lowering
	 * the capacity.
	 */
	अगर (sdp->fix_capacity ||
	    (sdp->guess_capacity && (sdkp->capacity & 0x01))) अणु
		sd_prपूर्णांकk(KERN_INFO, sdkp, "Adjusting the sector count "
				"from its reported value: %llu\n",
				(अचिन्हित दीर्घ दीर्घ) sdkp->capacity);
		--sdkp->capacity;
	पूर्ण

got_data:
	अगर (sector_size == 0) अणु
		sector_size = 512;
		sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Sector size 0 reported, "
			  "assuming 512.\n");
	पूर्ण

	अगर (sector_size != 512 &&
	    sector_size != 1024 &&
	    sector_size != 2048 &&
	    sector_size != 4096) अणु
		sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Unsupported sector size %d.\n",
			  sector_size);
		/*
		 * The user might want to re-क्रमmat the drive with
		 * a supported sectorsize.  Once this happens, it
		 * would be relatively trivial to set the thing up.
		 * For this reason, we leave the thing in the table.
		 */
		sdkp->capacity = 0;
		/*
		 * set a bogus sector size so the normal पढ़ो/ग_लिखो
		 * logic in the block layer will eventually refuse any
		 * request on this device without tripping over घातer
		 * of two sector size assumptions
		 */
		sector_size = 512;
	पूर्ण
	blk_queue_logical_block_size(sdp->request_queue, sector_size);
	blk_queue_physical_block_size(sdp->request_queue,
				      sdkp->physical_block_size);
	sdkp->device->sector_size = sector_size;

	अगर (sdkp->capacity > 0xffffffff)
		sdp->use_16_क्रम_rw = 1;

पूर्ण

/*
 * Prपूर्णांक disk capacity
 */
अटल व्योम
sd_prपूर्णांक_capacity(काष्ठा scsi_disk *sdkp,
		  sector_t old_capacity)
अणु
	पूर्णांक sector_size = sdkp->device->sector_size;
	अक्षर cap_str_2[10], cap_str_10[10];

	अगर (!sdkp->first_scan && old_capacity == sdkp->capacity)
		वापस;

	string_get_size(sdkp->capacity, sector_size,
			STRING_UNITS_2, cap_str_2, माप(cap_str_2));
	string_get_size(sdkp->capacity, sector_size,
			STRING_UNITS_10, cap_str_10, माप(cap_str_10));

	sd_prपूर्णांकk(KERN_NOTICE, sdkp,
		  "%llu %d-byte logical blocks: (%s/%s)\n",
		  (अचिन्हित दीर्घ दीर्घ)sdkp->capacity,
		  sector_size, cap_str_10, cap_str_2);

	अगर (sdkp->physical_block_size != sector_size)
		sd_prपूर्णांकk(KERN_NOTICE, sdkp,
			  "%u-byte physical blocks\n",
			  sdkp->physical_block_size);
पूर्ण

/* called with buffer of length 512 */
अटल अंतरभूत पूर्णांक
sd_करो_mode_sense(काष्ठा scsi_disk *sdkp, पूर्णांक dbd, पूर्णांक modepage,
		 अचिन्हित अक्षर *buffer, पूर्णांक len, काष्ठा scsi_mode_data *data,
		 काष्ठा scsi_sense_hdr *sshdr)
अणु
	वापस scsi_mode_sense(sdkp->device, dbd, modepage, buffer, len,
			       SD_TIMEOUT, sdkp->max_retries, data,
			       sshdr);
पूर्ण

/*
 * पढ़ो ग_लिखो protect setting, अगर possible - called only in sd_revalidate_disk()
 * called with buffer of length SD_BUF_SIZE
 */
अटल व्योम
sd_पढ़ो_ग_लिखो_protect_flag(काष्ठा scsi_disk *sdkp, अचिन्हित अक्षर *buffer)
अणु
	पूर्णांक res;
	काष्ठा scsi_device *sdp = sdkp->device;
	काष्ठा scsi_mode_data data;
	पूर्णांक old_wp = sdkp->ग_लिखो_prot;

	set_disk_ro(sdkp->disk, 0);
	अगर (sdp->skip_ms_page_3f) अणु
		sd_first_prपूर्णांकk(KERN_NOTICE, sdkp, "Assuming Write Enabled\n");
		वापस;
	पूर्ण

	अगर (sdp->use_192_bytes_क्रम_3f) अणु
		res = sd_करो_mode_sense(sdkp, 0, 0x3F, buffer, 192, &data, शून्य);
	पूर्ण अन्यथा अणु
		/*
		 * First attempt: ask क्रम all pages (0x3F), but only 4 bytes.
		 * We have to start carefully: some devices hang अगर we ask
		 * क्रम more than is available.
		 */
		res = sd_करो_mode_sense(sdkp, 0, 0x3F, buffer, 4, &data, शून्य);

		/*
		 * Second attempt: ask क्रम page 0 When only page 0 is
		 * implemented, a request क्रम page 3F may वापस Sense Key
		 * 5: Illegal Request, Sense Code 24: Invalid field in
		 * CDB.
		 */
		अगर (!scsi_status_is_good(res))
			res = sd_करो_mode_sense(sdkp, 0, 0, buffer, 4, &data, शून्य);

		/*
		 * Third attempt: ask 255 bytes, as we did earlier.
		 */
		अगर (!scsi_status_is_good(res))
			res = sd_करो_mode_sense(sdkp, 0, 0x3F, buffer, 255,
					       &data, शून्य);
	पूर्ण

	अगर (!scsi_status_is_good(res)) अणु
		sd_first_prपूर्णांकk(KERN_WARNING, sdkp,
			  "Test WP failed, assume Write Enabled\n");
	पूर्ण अन्यथा अणु
		sdkp->ग_लिखो_prot = ((data.device_specअगरic & 0x80) != 0);
		set_disk_ro(sdkp->disk, sdkp->ग_लिखो_prot);
		अगर (sdkp->first_scan || old_wp != sdkp->ग_लिखो_prot) अणु
			sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Write Protect is %s\n",
				  sdkp->ग_लिखो_prot ? "on" : "off");
			sd_prपूर्णांकk(KERN_DEBUG, sdkp, "Mode Sense: %4ph\n", buffer);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * sd_पढ़ो_cache_type - called only from sd_revalidate_disk()
 * called with buffer of length SD_BUF_SIZE
 */
अटल व्योम
sd_पढ़ो_cache_type(काष्ठा scsi_disk *sdkp, अचिन्हित अक्षर *buffer)
अणु
	पूर्णांक len = 0, res;
	काष्ठा scsi_device *sdp = sdkp->device;

	पूर्णांक dbd;
	पूर्णांक modepage;
	पूर्णांक first_len;
	काष्ठा scsi_mode_data data;
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक old_wce = sdkp->WCE;
	पूर्णांक old_rcd = sdkp->RCD;
	पूर्णांक old_dpofua = sdkp->DPOFUA;


	अगर (sdkp->cache_override)
		वापस;

	first_len = 4;
	अगर (sdp->skip_ms_page_8) अणु
		अगर (sdp->type == TYPE_RBC)
			जाओ शेषs;
		अन्यथा अणु
			अगर (sdp->skip_ms_page_3f)
				जाओ शेषs;
			modepage = 0x3F;
			अगर (sdp->use_192_bytes_क्रम_3f)
				first_len = 192;
			dbd = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (sdp->type == TYPE_RBC) अणु
		modepage = 6;
		dbd = 8;
	पूर्ण अन्यथा अणु
		modepage = 8;
		dbd = 0;
	पूर्ण

	/* cautiously ask */
	res = sd_करो_mode_sense(sdkp, dbd, modepage, buffer, first_len,
			&data, &sshdr);

	अगर (!scsi_status_is_good(res))
		जाओ bad_sense;

	अगर (!data.header_length) अणु
		modepage = 6;
		first_len = 0;
		sd_first_prपूर्णांकk(KERN_ERR, sdkp,
				"Missing header in MODE_SENSE response\n");
	पूर्ण

	/* that went OK, now ask क्रम the proper length */
	len = data.length;

	/*
	 * We're only पूर्णांकerested in the first three bytes, actually.
	 * But the data cache page is defined क्रम the first 20.
	 */
	अगर (len < 3)
		जाओ bad_sense;
	अन्यथा अगर (len > SD_BUF_SIZE) अणु
		sd_first_prपूर्णांकk(KERN_NOTICE, sdkp, "Truncating mode parameter "
			  "data from %d to %d bytes\n", len, SD_BUF_SIZE);
		len = SD_BUF_SIZE;
	पूर्ण
	अगर (modepage == 0x3F && sdp->use_192_bytes_क्रम_3f)
		len = 192;

	/* Get the data */
	अगर (len > first_len)
		res = sd_करो_mode_sense(sdkp, dbd, modepage, buffer, len,
				&data, &sshdr);

	अगर (scsi_status_is_good(res)) अणु
		पूर्णांक offset = data.header_length + data.block_descriptor_length;

		जबतक (offset < len) अणु
			u8 page_code = buffer[offset] & 0x3F;
			u8 spf       = buffer[offset] & 0x40;

			अगर (page_code == 8 || page_code == 6) अणु
				/* We're पूर्णांकerested only in the first 3 bytes.
				 */
				अगर (len - offset <= 2) अणु
					sd_first_prपूर्णांकk(KERN_ERR, sdkp,
						"Incomplete mode parameter "
							"data\n");
					जाओ शेषs;
				पूर्ण अन्यथा अणु
					modepage = page_code;
					जाओ Page_found;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Go to the next page */
				अगर (spf && len - offset > 3)
					offset += 4 + (buffer[offset+2] << 8) +
						buffer[offset+3];
				अन्यथा अगर (!spf && len - offset > 1)
					offset += 2 + buffer[offset+1];
				अन्यथा अणु
					sd_first_prपूर्णांकk(KERN_ERR, sdkp,
							"Incomplete mode "
							"parameter data\n");
					जाओ शेषs;
				पूर्ण
			पूर्ण
		पूर्ण

		sd_first_prपूर्णांकk(KERN_ERR, sdkp, "No Caching mode page found\n");
		जाओ शेषs;

	Page_found:
		अगर (modepage == 8) अणु
			sdkp->WCE = ((buffer[offset + 2] & 0x04) != 0);
			sdkp->RCD = ((buffer[offset + 2] & 0x01) != 0);
		पूर्ण अन्यथा अणु
			sdkp->WCE = ((buffer[offset + 2] & 0x01) == 0);
			sdkp->RCD = 0;
		पूर्ण

		sdkp->DPOFUA = (data.device_specअगरic & 0x10) != 0;
		अगर (sdp->broken_fua) अणु
			sd_first_prपूर्णांकk(KERN_NOTICE, sdkp, "Disabling FUA\n");
			sdkp->DPOFUA = 0;
		पूर्ण अन्यथा अगर (sdkp->DPOFUA && !sdkp->device->use_10_क्रम_rw &&
			   !sdkp->device->use_16_क्रम_rw) अणु
			sd_first_prपूर्णांकk(KERN_NOTICE, sdkp,
				  "Uses READ/WRITE(6), disabling FUA\n");
			sdkp->DPOFUA = 0;
		पूर्ण

		/* No cache flush allowed क्रम ग_लिखो रक्षित devices */
		अगर (sdkp->WCE && sdkp->ग_लिखो_prot)
			sdkp->WCE = 0;

		अगर (sdkp->first_scan || old_wce != sdkp->WCE ||
		    old_rcd != sdkp->RCD || old_dpofua != sdkp->DPOFUA)
			sd_prपूर्णांकk(KERN_NOTICE, sdkp,
				  "Write cache: %s, read cache: %s, %s\n",
				  sdkp->WCE ? "enabled" : "disabled",
				  sdkp->RCD ? "disabled" : "enabled",
				  sdkp->DPOFUA ? "supports DPO and FUA"
				  : "doesn't support DPO or FUA");

		वापस;
	पूर्ण

bad_sense:
	अगर (scsi_sense_valid(&sshdr) &&
	    sshdr.sense_key == ILLEGAL_REQUEST &&
	    sshdr.asc == 0x24 && sshdr.ascq == 0x0)
		/* Invalid field in CDB */
		sd_first_prपूर्णांकk(KERN_NOTICE, sdkp, "Cache data unavailable\n");
	अन्यथा
		sd_first_prपूर्णांकk(KERN_ERR, sdkp,
				"Asking for cache data failed\n");

शेषs:
	अगर (sdp->wce_शेष_on) अणु
		sd_first_prपूर्णांकk(KERN_NOTICE, sdkp,
				"Assuming drive cache: write back\n");
		sdkp->WCE = 1;
	पूर्ण अन्यथा अणु
		sd_first_prपूर्णांकk(KERN_ERR, sdkp,
				"Assuming drive cache: write through\n");
		sdkp->WCE = 0;
	पूर्ण
	sdkp->RCD = 0;
	sdkp->DPOFUA = 0;
पूर्ण

/*
 * The ATO bit indicates whether the DIF application tag is available
 * क्रम use by the operating प्रणाली.
 */
अटल व्योम sd_पढ़ो_app_tag_own(काष्ठा scsi_disk *sdkp, अचिन्हित अक्षर *buffer)
अणु
	पूर्णांक res, offset;
	काष्ठा scsi_device *sdp = sdkp->device;
	काष्ठा scsi_mode_data data;
	काष्ठा scsi_sense_hdr sshdr;

	अगर (sdp->type != TYPE_DISK && sdp->type != TYPE_ZBC)
		वापस;

	अगर (sdkp->protection_type == 0)
		वापस;

	res = scsi_mode_sense(sdp, 1, 0x0a, buffer, 36, SD_TIMEOUT,
			      sdkp->max_retries, &data, &sshdr);

	अगर (!scsi_status_is_good(res) || !data.header_length ||
	    data.length < 6) अणु
		sd_first_prपूर्णांकk(KERN_WARNING, sdkp,
			  "getting Control mode page failed, assume no ATO\n");

		अगर (scsi_sense_valid(&sshdr))
			sd_prपूर्णांक_sense_hdr(sdkp, &sshdr);

		वापस;
	पूर्ण

	offset = data.header_length + data.block_descriptor_length;

	अगर ((buffer[offset] & 0x3f) != 0x0a) अणु
		sd_first_prपूर्णांकk(KERN_ERR, sdkp, "ATO Got wrong page\n");
		वापस;
	पूर्ण

	अगर ((buffer[offset + 5] & 0x80) == 0)
		वापस;

	sdkp->ATO = 1;

	वापस;
पूर्ण

/**
 * sd_पढ़ो_block_limits - Query disk device क्रम preferred I/O sizes.
 * @sdkp: disk to query
 */
अटल व्योम sd_पढ़ो_block_limits(काष्ठा scsi_disk *sdkp)
अणु
	अचिन्हित पूर्णांक sector_sz = sdkp->device->sector_size;
	स्थिर पूर्णांक vpd_len = 64;
	अचिन्हित अक्षर *buffer = kदो_स्मृति(vpd_len, GFP_KERNEL);

	अगर (!buffer ||
	    /* Block Limits VPD */
	    scsi_get_vpd_page(sdkp->device, 0xb0, buffer, vpd_len))
		जाओ out;

	blk_queue_io_min(sdkp->disk->queue,
			 get_unaligned_be16(&buffer[6]) * sector_sz);

	sdkp->max_xfer_blocks = get_unaligned_be32(&buffer[8]);
	sdkp->opt_xfer_blocks = get_unaligned_be32(&buffer[12]);

	अगर (buffer[3] == 0x3c) अणु
		अचिन्हित पूर्णांक lba_count, desc_count;

		sdkp->max_ws_blocks = (u32)get_unaligned_be64(&buffer[36]);

		अगर (!sdkp->lbpme)
			जाओ out;

		lba_count = get_unaligned_be32(&buffer[20]);
		desc_count = get_unaligned_be32(&buffer[24]);

		अगर (lba_count && desc_count)
			sdkp->max_unmap_blocks = lba_count;

		sdkp->unmap_granularity = get_unaligned_be32(&buffer[28]);

		अगर (buffer[32] & 0x80)
			sdkp->unmap_alignment =
				get_unaligned_be32(&buffer[32]) & ~(1 << 31);

		अगर (!sdkp->lbpvpd) अणु /* LBP VPD page not provided */

			अगर (sdkp->max_unmap_blocks)
				sd_config_discard(sdkp, SD_LBP_UNMAP);
			अन्यथा
				sd_config_discard(sdkp, SD_LBP_WS16);

		पूर्ण अन्यथा अणु	/* LBP VPD page tells us what to use */
			अगर (sdkp->lbpu && sdkp->max_unmap_blocks)
				sd_config_discard(sdkp, SD_LBP_UNMAP);
			अन्यथा अगर (sdkp->lbpws)
				sd_config_discard(sdkp, SD_LBP_WS16);
			अन्यथा अगर (sdkp->lbpws10)
				sd_config_discard(sdkp, SD_LBP_WS10);
			अन्यथा
				sd_config_discard(sdkp, SD_LBP_DISABLE);
		पूर्ण
	पूर्ण

 out:
	kमुक्त(buffer);
पूर्ण

/**
 * sd_पढ़ो_block_अक्षरacteristics - Query block dev. अक्षरacteristics
 * @sdkp: disk to query
 */
अटल व्योम sd_पढ़ो_block_अक्षरacteristics(काष्ठा scsi_disk *sdkp)
अणु
	काष्ठा request_queue *q = sdkp->disk->queue;
	अचिन्हित अक्षर *buffer;
	u16 rot;
	स्थिर पूर्णांक vpd_len = 64;

	buffer = kदो_स्मृति(vpd_len, GFP_KERNEL);

	अगर (!buffer ||
	    /* Block Device Characteristics VPD */
	    scsi_get_vpd_page(sdkp->device, 0xb1, buffer, vpd_len))
		जाओ out;

	rot = get_unaligned_be16(&buffer[4]);

	अगर (rot == 1) अणु
		blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
		blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, q);
	पूर्ण

	अगर (sdkp->device->type == TYPE_ZBC) अणु
		/* Host-managed */
		blk_queue_set_zoned(sdkp->disk, BLK_ZONED_HM);
	पूर्ण अन्यथा अणु
		sdkp->zoned = (buffer[8] >> 4) & 3;
		अगर (sdkp->zoned == 1) अणु
			/* Host-aware */
			blk_queue_set_zoned(sdkp->disk, BLK_ZONED_HA);
		पूर्ण अन्यथा अणु
			/* Regular disk or drive managed disk */
			blk_queue_set_zoned(sdkp->disk, BLK_ZONED_NONE);
		पूर्ण
	पूर्ण

	अगर (!sdkp->first_scan)
		जाओ out;

	अगर (blk_queue_is_zoned(q)) अणु
		sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Host-%s zoned block device\n",
		      q->limits.zoned == BLK_ZONED_HM ? "managed" : "aware");
	पूर्ण अन्यथा अणु
		अगर (sdkp->zoned == 1)
			sd_prपूर्णांकk(KERN_NOTICE, sdkp,
				  "Host-aware SMR disk used as regular disk\n");
		अन्यथा अगर (sdkp->zoned == 2)
			sd_prपूर्णांकk(KERN_NOTICE, sdkp,
				  "Drive-managed SMR disk\n");
	पूर्ण

 out:
	kमुक्त(buffer);
पूर्ण

/**
 * sd_पढ़ो_block_provisioning - Query provisioning VPD page
 * @sdkp: disk to query
 */
अटल व्योम sd_पढ़ो_block_provisioning(काष्ठा scsi_disk *sdkp)
अणु
	अचिन्हित अक्षर *buffer;
	स्थिर पूर्णांक vpd_len = 8;

	अगर (sdkp->lbpme == 0)
		वापस;

	buffer = kदो_स्मृति(vpd_len, GFP_KERNEL);

	अगर (!buffer || scsi_get_vpd_page(sdkp->device, 0xb2, buffer, vpd_len))
		जाओ out;

	sdkp->lbpvpd	= 1;
	sdkp->lbpu	= (buffer[5] >> 7) & 1;	/* UNMAP */
	sdkp->lbpws	= (buffer[5] >> 6) & 1;	/* WRITE SAME(16) with UNMAP */
	sdkp->lbpws10	= (buffer[5] >> 5) & 1;	/* WRITE SAME(10) with UNMAP */

 out:
	kमुक्त(buffer);
पूर्ण

अटल व्योम sd_पढ़ो_ग_लिखो_same(काष्ठा scsi_disk *sdkp, अचिन्हित अक्षर *buffer)
अणु
	काष्ठा scsi_device *sdev = sdkp->device;

	अगर (sdev->host->no_ग_लिखो_same) अणु
		sdev->no_ग_लिखो_same = 1;

		वापस;
	पूर्ण

	अगर (scsi_report_opcode(sdev, buffer, SD_BUF_SIZE, INQUIRY) < 0) अणु
		/* too large values might cause issues with arcmsr */
		पूर्णांक vpd_buf_len = 64;

		sdev->no_report_opcodes = 1;

		/* Disable WRITE SAME अगर REPORT SUPPORTED OPERATION
		 * CODES is unsupported and the device has an ATA
		 * Inक्रमmation VPD page (SAT).
		 */
		अगर (!scsi_get_vpd_page(sdev, 0x89, buffer, vpd_buf_len))
			sdev->no_ग_लिखो_same = 1;
	पूर्ण

	अगर (scsi_report_opcode(sdev, buffer, SD_BUF_SIZE, WRITE_SAME_16) == 1)
		sdkp->ws16 = 1;

	अगर (scsi_report_opcode(sdev, buffer, SD_BUF_SIZE, WRITE_SAME) == 1)
		sdkp->ws10 = 1;
पूर्ण

अटल व्योम sd_पढ़ो_security(काष्ठा scsi_disk *sdkp, अचिन्हित अक्षर *buffer)
अणु
	काष्ठा scsi_device *sdev = sdkp->device;

	अगर (!sdev->security_supported)
		वापस;

	अगर (scsi_report_opcode(sdev, buffer, SD_BUF_SIZE,
			SECURITY_PROTOCOL_IN) == 1 &&
	    scsi_report_opcode(sdev, buffer, SD_BUF_SIZE,
			SECURITY_PROTOCOL_OUT) == 1)
		sdkp->security = 1;
पूर्ण

/*
 * Determine the device's preferred I/O size क्रम पढ़ोs and ग_लिखोs
 * unless the reported value is unreasonably small, large, not a
 * multiple of the physical block size, or simply garbage.
 */
अटल bool sd_validate_opt_xfer_size(काष्ठा scsi_disk *sdkp,
				      अचिन्हित पूर्णांक dev_max)
अणु
	काष्ठा scsi_device *sdp = sdkp->device;
	अचिन्हित पूर्णांक opt_xfer_bytes =
		logical_to_bytes(sdp, sdkp->opt_xfer_blocks);

	अगर (sdkp->opt_xfer_blocks == 0)
		वापस false;

	अगर (sdkp->opt_xfer_blocks > dev_max) अणु
		sd_first_prपूर्णांकk(KERN_WARNING, sdkp,
				"Optimal transfer size %u logical blocks " \
				"> dev_max (%u logical blocks)\n",
				sdkp->opt_xfer_blocks, dev_max);
		वापस false;
	पूर्ण

	अगर (sdkp->opt_xfer_blocks > SD_DEF_XFER_BLOCKS) अणु
		sd_first_prपूर्णांकk(KERN_WARNING, sdkp,
				"Optimal transfer size %u logical blocks " \
				"> sd driver limit (%u logical blocks)\n",
				sdkp->opt_xfer_blocks, SD_DEF_XFER_BLOCKS);
		वापस false;
	पूर्ण

	अगर (opt_xfer_bytes < PAGE_SIZE) अणु
		sd_first_prपूर्णांकk(KERN_WARNING, sdkp,
				"Optimal transfer size %u bytes < " \
				"PAGE_SIZE (%u bytes)\n",
				opt_xfer_bytes, (अचिन्हित पूर्णांक)PAGE_SIZE);
		वापस false;
	पूर्ण

	अगर (opt_xfer_bytes & (sdkp->physical_block_size - 1)) अणु
		sd_first_prपूर्णांकk(KERN_WARNING, sdkp,
				"Optimal transfer size %u bytes not a " \
				"multiple of physical block size (%u bytes)\n",
				opt_xfer_bytes, sdkp->physical_block_size);
		वापस false;
	पूर्ण

	sd_first_prपूर्णांकk(KERN_INFO, sdkp, "Optimal transfer size %u bytes\n",
			opt_xfer_bytes);
	वापस true;
पूर्ण

/**
 *	sd_revalidate_disk - called the first समय a new disk is seen,
 *	perक्रमms disk spin up, पढ़ो_capacity, etc.
 *	@disk: काष्ठा gendisk we care about
 **/
अटल पूर्णांक sd_revalidate_disk(काष्ठा gendisk *disk)
अणु
	काष्ठा scsi_disk *sdkp = scsi_disk(disk);
	काष्ठा scsi_device *sdp = sdkp->device;
	काष्ठा request_queue *q = sdkp->disk->queue;
	sector_t old_capacity = sdkp->capacity;
	अचिन्हित अक्षर *buffer;
	अचिन्हित पूर्णांक dev_max, rw_max;

	SCSI_LOG_HLQUEUE(3, sd_prपूर्णांकk(KERN_INFO, sdkp,
				      "sd_revalidate_disk\n"));

	/*
	 * If the device is offline, करोn't try and पढ़ो capacity or any
	 * of the other niceties.
	 */
	अगर (!scsi_device_online(sdp))
		जाओ out;

	buffer = kदो_स्मृति(SD_BUF_SIZE, GFP_KERNEL);
	अगर (!buffer) अणु
		sd_prपूर्णांकk(KERN_WARNING, sdkp, "sd_revalidate_disk: Memory "
			  "allocation failure.\n");
		जाओ out;
	पूर्ण

	sd_spinup_disk(sdkp);

	/*
	 * Without media there is no reason to ask; moreover, some devices
	 * react badly अगर we करो.
	 */
	अगर (sdkp->media_present) अणु
		sd_पढ़ो_capacity(sdkp, buffer);

		/*
		 * set the शेष to rotational.  All non-rotational devices
		 * support the block अक्षरacteristics VPD page, which will
		 * cause this to be updated correctly and any device which
		 * करोesn't support it should be treated as rotational.
		 */
		blk_queue_flag_clear(QUEUE_FLAG_NONROT, q);
		blk_queue_flag_set(QUEUE_FLAG_ADD_RANDOM, q);

		अगर (scsi_device_supports_vpd(sdp)) अणु
			sd_पढ़ो_block_provisioning(sdkp);
			sd_पढ़ो_block_limits(sdkp);
			sd_पढ़ो_block_अक्षरacteristics(sdkp);
			sd_zbc_पढ़ो_zones(sdkp, buffer);
		पूर्ण

		sd_prपूर्णांक_capacity(sdkp, old_capacity);

		sd_पढ़ो_ग_लिखो_protect_flag(sdkp, buffer);
		sd_पढ़ो_cache_type(sdkp, buffer);
		sd_पढ़ो_app_tag_own(sdkp, buffer);
		sd_पढ़ो_ग_लिखो_same(sdkp, buffer);
		sd_पढ़ो_security(sdkp, buffer);
	पूर्ण

	/*
	 * We now have all cache related info, determine how we deal
	 * with flush requests.
	 */
	sd_set_flush_flag(sdkp);

	/* Initial block count limit based on CDB TRANSFER LENGTH field size. */
	dev_max = sdp->use_16_क्रम_rw ? SD_MAX_XFER_BLOCKS : SD_DEF_XFER_BLOCKS;

	/* Some devices report a maximum block count क्रम READ/WRITE requests. */
	dev_max = min_not_zero(dev_max, sdkp->max_xfer_blocks);
	q->limits.max_dev_sectors = logical_to_sectors(sdp, dev_max);

	अगर (sd_validate_opt_xfer_size(sdkp, dev_max)) अणु
		q->limits.io_opt = logical_to_bytes(sdp, sdkp->opt_xfer_blocks);
		rw_max = logical_to_sectors(sdp, sdkp->opt_xfer_blocks);
	पूर्ण अन्यथा अणु
		q->limits.io_opt = 0;
		rw_max = min_not_zero(logical_to_sectors(sdp, dev_max),
				      (sector_t)BLK_DEF_MAX_SECTORS);
	पूर्ण

	/* Do not exceed controller limit */
	rw_max = min(rw_max, queue_max_hw_sectors(q));

	/*
	 * Only update max_sectors अगर previously unset or अगर the current value
	 * exceeds the capabilities of the hardware.
	 */
	अगर (sdkp->first_scan ||
	    q->limits.max_sectors > q->limits.max_dev_sectors ||
	    q->limits.max_sectors > q->limits.max_hw_sectors)
		q->limits.max_sectors = rw_max;

	sdkp->first_scan = 0;

	set_capacity_and_notअगरy(disk, logical_to_sectors(sdp, sdkp->capacity));
	sd_config_ग_लिखो_same(sdkp);
	kमुक्त(buffer);

	/*
	 * For a zoned drive, revalidating the zones can be करोne only once
	 * the gendisk capacity is set. So अगर this fails, set back the gendisk
	 * capacity to 0.
	 */
	अगर (sd_zbc_revalidate_zones(sdkp))
		set_capacity_and_notअगरy(disk, 0);

 out:
	वापस 0;
पूर्ण

/**
 *	sd_unlock_native_capacity - unlock native capacity
 *	@disk: काष्ठा gendisk to set capacity क्रम
 *
 *	Block layer calls this function अगर it detects that partitions
 *	on @disk reach beyond the end of the device.  If the SCSI host
 *	implements ->unlock_native_capacity() method, it's invoked to
 *	give it a chance to adjust the device capacity.
 *
 *	CONTEXT:
 *	Defined by block layer.  Might sleep.
 */
अटल व्योम sd_unlock_native_capacity(काष्ठा gendisk *disk)
अणु
	काष्ठा scsi_device *sdev = scsi_disk(disk)->device;

	अगर (sdev->host->hostt->unlock_native_capacity)
		sdev->host->hostt->unlock_native_capacity(sdev);
पूर्ण

/**
 *	sd_क्रमmat_disk_name - क्रमmat disk name
 *	@prefix: name prefix - ie. "sd" क्रम SCSI disks
 *	@index: index of the disk to क्रमmat name क्रम
 *	@buf: output buffer
 *	@buflen: length of the output buffer
 *
 *	SCSI disk names starts at sda.  The 26th device is sdz and the
 *	27th is sdaa.  The last one क्रम two lettered suffix is sdzz
 *	which is followed by sdaaa.
 *
 *	This is basically 26 base counting with one extra 'nil' entry
 *	at the beginning from the second digit on and can be
 *	determined using similar method as 26 base conversion with the
 *	index shअगरted -1 after each digit is computed.
 *
 *	CONTEXT:
 *	Don't care.
 *
 *	RETURNS:
 *	0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक sd_क्रमmat_disk_name(अक्षर *prefix, पूर्णांक index, अक्षर *buf, पूर्णांक buflen)
अणु
	स्थिर पूर्णांक base = 'z' - 'a' + 1;
	अक्षर *begin = buf + म_माप(prefix);
	अक्षर *end = buf + buflen;
	अक्षर *p;
	पूर्णांक unit;

	p = end - 1;
	*p = '\0';
	unit = base;
	करो अणु
		अगर (p == begin)
			वापस -EINVAL;
		*--p = 'a' + (index % unit);
		index = (index / unit) - 1;
	पूर्ण जबतक (index >= 0);

	स_हटाओ(begin, p, end - p);
	स_नकल(buf, prefix, म_माप(prefix));

	वापस 0;
पूर्ण

/**
 *	sd_probe - called during driver initialization and whenever a
 *	new scsi device is attached to the प्रणाली. It is called once
 *	क्रम each scsi device (not just disks) present.
 *	@dev: poपूर्णांकer to device object
 *
 *	Returns 0 अगर successful (or not पूर्णांकerested in this scsi device 
 *	(e.g. scanner)); 1 when there is an error.
 *
 *	Note: this function is invoked from the scsi mid-level.
 *	This function sets up the mapping between a given 
 *	<host,channel,id,lun> (found in sdp) and new device name 
 *	(e.g. /dev/sda). More precisely it is the block device major 
 *	and minor number that is chosen here.
 *
 *	Assume sd_probe is not re-entrant (क्रम समय being)
 *	Also think about sd_probe() and sd_हटाओ() running coincidentally.
 **/
अटल पूर्णांक sd_probe(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdp = to_scsi_device(dev);
	काष्ठा scsi_disk *sdkp;
	काष्ठा gendisk *gd;
	पूर्णांक index;
	पूर्णांक error;

	scsi_स्वतःpm_get_device(sdp);
	error = -ENODEV;
	अगर (sdp->type != TYPE_DISK &&
	    sdp->type != TYPE_ZBC &&
	    sdp->type != TYPE_MOD &&
	    sdp->type != TYPE_RBC)
		जाओ out;

	अगर (!IS_ENABLED(CONFIG_BLK_DEV_ZONED) && sdp->type == TYPE_ZBC) अणु
		sdev_prपूर्णांकk(KERN_WARNING, sdp,
			    "Unsupported ZBC host-managed device.\n");
		जाओ out;
	पूर्ण

	SCSI_LOG_HLQUEUE(3, sdev_prपूर्णांकk(KERN_INFO, sdp,
					"sd_probe\n"));

	error = -ENOMEM;
	sdkp = kzalloc(माप(*sdkp), GFP_KERNEL);
	अगर (!sdkp)
		जाओ out;

	gd = alloc_disk(SD_MINORS);
	अगर (!gd)
		जाओ out_मुक्त;

	index = ida_alloc(&sd_index_ida, GFP_KERNEL);
	अगर (index < 0) अणु
		sdev_prपूर्णांकk(KERN_WARNING, sdp, "sd_probe: memory exhausted.\n");
		जाओ out_put;
	पूर्ण

	error = sd_क्रमmat_disk_name("sd", index, gd->disk_name, DISK_NAME_LEN);
	अगर (error) अणु
		sdev_prपूर्णांकk(KERN_WARNING, sdp, "SCSI disk (sd) name length exceeded.\n");
		जाओ out_मुक्त_index;
	पूर्ण

	sdkp->device = sdp;
	sdkp->driver = &sd_ढाँचा;
	sdkp->disk = gd;
	sdkp->index = index;
	sdkp->max_retries = SD_MAX_RETRIES;
	atomic_set(&sdkp->खोलोers, 0);
	atomic_set(&sdkp->device->ioerr_cnt, 0);

	अगर (!sdp->request_queue->rq_समयout) अणु
		अगर (sdp->type != TYPE_MOD)
			blk_queue_rq_समयout(sdp->request_queue, SD_TIMEOUT);
		अन्यथा
			blk_queue_rq_समयout(sdp->request_queue,
					     SD_MOD_TIMEOUT);
	पूर्ण

	device_initialize(&sdkp->dev);
	sdkp->dev.parent = dev;
	sdkp->dev.class = &sd_disk_class;
	dev_set_name(&sdkp->dev, "%s", dev_name(dev));

	error = device_add(&sdkp->dev);
	अगर (error)
		जाओ out_मुक्त_index;

	get_device(dev);
	dev_set_drvdata(dev, sdkp);

	gd->major = sd_major((index & 0xf0) >> 4);
	gd->first_minor = ((index & 0xf) << 4) | (index & 0xfff00);

	gd->fops = &sd_fops;
	gd->निजी_data = &sdkp->driver;
	gd->queue = sdkp->device->request_queue;

	/* शेषs, until the device tells us otherwise */
	sdp->sector_size = 512;
	sdkp->capacity = 0;
	sdkp->media_present = 1;
	sdkp->ग_लिखो_prot = 0;
	sdkp->cache_override = 0;
	sdkp->WCE = 0;
	sdkp->RCD = 0;
	sdkp->ATO = 0;
	sdkp->first_scan = 1;
	sdkp->max_medium_access_समयouts = SD_MAX_MEDIUM_TIMEOUTS;

	sd_revalidate_disk(gd);

	gd->flags = GENHD_FL_EXT_DEVT;
	अगर (sdp->removable) अणु
		gd->flags |= GENHD_FL_REMOVABLE;
		gd->events |= DISK_EVENT_MEDIA_CHANGE;
		gd->event_flags = DISK_EVENT_FLAG_POLL | DISK_EVENT_FLAG_UEVENT;
	पूर्ण

	blk_pm_runसमय_init(sdp->request_queue, dev);
	अगर (sdp->rpm_स्वतःsuspend) अणु
		pm_runसमय_set_स्वतःsuspend_delay(dev,
			sdp->host->hostt->rpm_स्वतःsuspend_delay);
	पूर्ण
	device_add_disk(dev, gd, शून्य);
	अगर (sdkp->capacity)
		sd_dअगर_config_host(sdkp);

	sd_revalidate_disk(gd);

	अगर (sdkp->security) अणु
		sdkp->opal_dev = init_opal_dev(sdkp, &sd_sec_submit);
		अगर (sdkp->opal_dev)
			sd_prपूर्णांकk(KERN_NOTICE, sdkp, "supports TCG Opal\n");
	पूर्ण

	sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Attached SCSI %sdisk\n",
		  sdp->removable ? "removable " : "");
	scsi_स्वतःpm_put_device(sdp);

	वापस 0;

 out_मुक्त_index:
	ida_मुक्त(&sd_index_ida, index);
 out_put:
	put_disk(gd);
 out_मुक्त:
	sd_zbc_release_disk(sdkp);
	kमुक्त(sdkp);
 out:
	scsi_स्वतःpm_put_device(sdp);
	वापस error;
पूर्ण

/**
 *	sd_हटाओ - called whenever a scsi disk (previously recognized by
 *	sd_probe) is detached from the प्रणाली. It is called (potentially
 *	multiple बार) during sd module unload.
 *	@dev: poपूर्णांकer to device object
 *
 *	Note: this function is invoked from the scsi mid-level.
 *	This function potentially मुक्तs up a device name (e.g. /dev/sdc)
 *	that could be re-used by a subsequent sd_probe().
 *	This function is not called when the built-in sd driver is "exit-ed".
 **/
अटल पूर्णांक sd_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा scsi_disk *sdkp;

	sdkp = dev_get_drvdata(dev);
	scsi_स्वतःpm_get_device(sdkp->device);

	async_synchronize_full_करोमुख्य(&scsi_sd_pm_करोमुख्य);
	device_del(&sdkp->dev);
	del_gendisk(sdkp->disk);
	sd_shutकरोwn(dev);

	मुक्त_opal_dev(sdkp->opal_dev);

	mutex_lock(&sd_ref_mutex);
	dev_set_drvdata(dev, शून्य);
	put_device(&sdkp->dev);
	mutex_unlock(&sd_ref_mutex);

	वापस 0;
पूर्ण

/**
 *	scsi_disk_release - Called to मुक्त the scsi_disk काष्ठाure
 *	@dev: poपूर्णांकer to embedded class device
 *
 *	sd_ref_mutex must be held entering this routine.  Because it is
 *	called on last put, you should always use the scsi_disk_get()
 *	scsi_disk_put() helpers which manipulate the semaphore directly
 *	and never करो a direct put_device.
 **/
अटल व्योम scsi_disk_release(काष्ठा device *dev)
अणु
	काष्ठा scsi_disk *sdkp = to_scsi_disk(dev);
	काष्ठा gendisk *disk = sdkp->disk;
	काष्ठा request_queue *q = disk->queue;

	ida_मुक्त(&sd_index_ida, sdkp->index);

	/*
	 * Wait until all requests that are in progress have completed.
	 * This is necessary to aव्योम that e.g. scsi_end_request() crashes
	 * due to clearing the disk->निजी_data poपूर्णांकer. Wait from inside
	 * scsi_disk_release() instead of from sd_release() to aव्योम that
	 * मुक्तzing and unमुक्तzing the request queue affects user space I/O
	 * in हाल multiple processes खोलो a /dev/sd... node concurrently.
	 */
	blk_mq_मुक्तze_queue(q);
	blk_mq_unमुक्तze_queue(q);

	disk->निजी_data = शून्य;
	put_disk(disk);
	put_device(&sdkp->device->sdev_gendev);

	sd_zbc_release_disk(sdkp);

	kमुक्त(sdkp);
पूर्ण

अटल पूर्णांक sd_start_stop_device(काष्ठा scsi_disk *sdkp, पूर्णांक start)
अणु
	अचिन्हित अक्षर cmd[6] = अणु START_STOP पूर्ण;	/* START_VALID */
	काष्ठा scsi_sense_hdr sshdr;
	काष्ठा scsi_device *sdp = sdkp->device;
	पूर्णांक res;

	अगर (start)
		cmd[4] |= 1;	/* START */

	अगर (sdp->start_stop_pwr_cond)
		cmd[4] |= start ? 1 << 4 : 3 << 4;	/* Active or Standby */

	अगर (!scsi_device_online(sdp))
		वापस -ENODEV;

	res = scsi_execute(sdp, cmd, DMA_NONE, शून्य, 0, शून्य, &sshdr,
			SD_TIMEOUT, sdkp->max_retries, 0, RQF_PM, शून्य);
	अगर (res) अणु
		sd_prपूर्णांक_result(sdkp, "Start/Stop Unit failed", res);
		अगर (driver_byte(res) == DRIVER_SENSE)
			sd_prपूर्णांक_sense_hdr(sdkp, &sshdr);
		अगर (scsi_sense_valid(&sshdr) &&
			/* 0x3a is medium not present */
			sshdr.asc == 0x3a)
			res = 0;
	पूर्ण

	/* SCSI error codes must not go to the generic layer */
	अगर (res)
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * Send a SYNCHRONIZE CACHE inकाष्ठाion करोwn to the device through
 * the normal SCSI command काष्ठाure.  Wait क्रम the command to
 * complete.
 */
अटल व्योम sd_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा scsi_disk *sdkp = dev_get_drvdata(dev);

	अगर (!sdkp)
		वापस;         /* this can happen */

	अगर (pm_runसमय_suspended(dev))
		वापस;

	अगर (sdkp->WCE && sdkp->media_present) अणु
		sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Synchronizing SCSI cache\n");
		sd_sync_cache(sdkp, शून्य);
	पूर्ण

	अगर (प्रणाली_state != SYSTEM_RESTART && sdkp->device->manage_start_stop) अणु
		sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Stopping disk\n");
		sd_start_stop_device(sdkp, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक sd_suspend_common(काष्ठा device *dev, bool ignore_stop_errors)
अणु
	काष्ठा scsi_disk *sdkp = dev_get_drvdata(dev);
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक ret = 0;

	अगर (!sdkp)	/* E.g.: runसमय suspend following sd_हटाओ() */
		वापस 0;

	अगर (sdkp->WCE && sdkp->media_present) अणु
		sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Synchronizing SCSI cache\n");
		ret = sd_sync_cache(sdkp, &sshdr);

		अगर (ret) अणु
			/* ignore OFFLINE device */
			अगर (ret == -ENODEV)
				वापस 0;

			अगर (!scsi_sense_valid(&sshdr) ||
			    sshdr.sense_key != ILLEGAL_REQUEST)
				वापस ret;

			/*
			 * sshdr.sense_key == ILLEGAL_REQUEST means this drive
			 * करोesn't support sync. There's not much to करो and
			 * suspend shouldn't fail.
			 */
			ret = 0;
		पूर्ण
	पूर्ण

	अगर (sdkp->device->manage_start_stop) अणु
		sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Stopping disk\n");
		/* an error is not worth पातing a प्रणाली sleep */
		ret = sd_start_stop_device(sdkp, 0);
		अगर (ignore_stop_errors)
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sd_suspend_प्रणाली(काष्ठा device *dev)
अणु
	वापस sd_suspend_common(dev, true);
पूर्ण

अटल पूर्णांक sd_suspend_runसमय(काष्ठा device *dev)
अणु
	वापस sd_suspend_common(dev, false);
पूर्ण

अटल पूर्णांक sd_resume(काष्ठा device *dev)
अणु
	काष्ठा scsi_disk *sdkp = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!sdkp)	/* E.g.: runसमय resume at the start of sd_probe() */
		वापस 0;

	अगर (!sdkp->device->manage_start_stop)
		वापस 0;

	sd_prपूर्णांकk(KERN_NOTICE, sdkp, "Starting disk\n");
	ret = sd_start_stop_device(sdkp, 1);
	अगर (!ret)
		opal_unlock_from_suspend(sdkp->opal_dev);
	वापस ret;
पूर्ण

/**
 *	init_sd - entry poपूर्णांक क्रम this driver (both when built in or when
 *	a module).
 *
 *	Note: this function रेजिस्टरs this driver with the scsi mid-level.
 **/
अटल पूर्णांक __init init_sd(व्योम)
अणु
	पूर्णांक majors = 0, i, err;

	SCSI_LOG_HLQUEUE(3, prपूर्णांकk("init_sd: sd driver entry point\n"));

	क्रम (i = 0; i < SD_MAJORS; i++) अणु
		अगर (__रेजिस्टर_blkdev(sd_major(i), "sd", sd_शेष_probe))
			जारी;
		majors++;
	पूर्ण

	अगर (!majors)
		वापस -ENODEV;

	err = class_रेजिस्टर(&sd_disk_class);
	अगर (err)
		जाओ err_out;

	sd_cdb_cache = kmem_cache_create("sd_ext_cdb", SD_EXT_CDB_SIZE,
					 0, 0, शून्य);
	अगर (!sd_cdb_cache) अणु
		prपूर्णांकk(KERN_ERR "sd: can't init extended cdb cache\n");
		err = -ENOMEM;
		जाओ err_out_class;
	पूर्ण

	sd_cdb_pool = mempool_create_slab_pool(SD_MEMPOOL_SIZE, sd_cdb_cache);
	अगर (!sd_cdb_pool) अणु
		prपूर्णांकk(KERN_ERR "sd: can't init extended cdb pool\n");
		err = -ENOMEM;
		जाओ err_out_cache;
	पूर्ण

	sd_page_pool = mempool_create_page_pool(SD_MEMPOOL_SIZE, 0);
	अगर (!sd_page_pool) अणु
		prपूर्णांकk(KERN_ERR "sd: can't init discard page pool\n");
		err = -ENOMEM;
		जाओ err_out_ppool;
	पूर्ण

	err = scsi_रेजिस्टर_driver(&sd_ढाँचा.gendrv);
	अगर (err)
		जाओ err_out_driver;

	वापस 0;

err_out_driver:
	mempool_destroy(sd_page_pool);

err_out_ppool:
	mempool_destroy(sd_cdb_pool);

err_out_cache:
	kmem_cache_destroy(sd_cdb_cache);

err_out_class:
	class_unरेजिस्टर(&sd_disk_class);
err_out:
	क्रम (i = 0; i < SD_MAJORS; i++)
		unरेजिस्टर_blkdev(sd_major(i), "sd");
	वापस err;
पूर्ण

/**
 *	निकास_sd - निकास poपूर्णांक क्रम this driver (when it is a module).
 *
 *	Note: this function unरेजिस्टरs this driver from the scsi mid-level.
 **/
अटल व्योम __निकास निकास_sd(व्योम)
अणु
	पूर्णांक i;

	SCSI_LOG_HLQUEUE(3, prपूर्णांकk("exit_sd: exiting sd driver\n"));

	scsi_unरेजिस्टर_driver(&sd_ढाँचा.gendrv);
	mempool_destroy(sd_cdb_pool);
	mempool_destroy(sd_page_pool);
	kmem_cache_destroy(sd_cdb_cache);

	class_unरेजिस्टर(&sd_disk_class);

	क्रम (i = 0; i < SD_MAJORS; i++)
		unरेजिस्टर_blkdev(sd_major(i), "sd");
पूर्ण

module_init(init_sd);
module_निकास(निकास_sd);

व्योम sd_prपूर्णांक_sense_hdr(काष्ठा scsi_disk *sdkp, काष्ठा scsi_sense_hdr *sshdr)
अणु
	scsi_prपूर्णांक_sense_hdr(sdkp->device,
			     sdkp->disk ? sdkp->disk->disk_name : शून्य, sshdr);
पूर्ण

व्योम sd_prपूर्णांक_result(स्थिर काष्ठा scsi_disk *sdkp, स्थिर अक्षर *msg, पूर्णांक result)
अणु
	स्थिर अक्षर *hb_string = scsi_hostbyte_string(result);
	स्थिर अक्षर *db_string = scsi_driverbyte_string(result);

	अगर (hb_string || db_string)
		sd_prपूर्णांकk(KERN_INFO, sdkp,
			  "%s: Result: hostbyte=%s driverbyte=%s\n", msg,
			  hb_string ? hb_string : "invalid",
			  db_string ? db_string : "invalid");
	अन्यथा
		sd_prपूर्णांकk(KERN_INFO, sdkp,
			  "%s: Result: hostbyte=0x%02x driverbyte=0x%02x\n",
			  msg, host_byte(result), driver_byte(result));
पूर्ण
