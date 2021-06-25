<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_DISK_H
#घोषणा _SCSI_DISK_H

/*
 * More than enough क्रम everybody ;)  The huge number of majors
 * is a leftover from 16bit dev_t days, we करोn't really need that
 * much numberspace.
 */
#घोषणा SD_MAJORS	16

/*
 * Time out in seconds क्रम disks and Magneto-opticals (which are slower).
 */
#घोषणा SD_TIMEOUT		(30 * HZ)
#घोषणा SD_MOD_TIMEOUT		(75 * HZ)
/*
 * Flush समयout is a multiplier over the standard device समयout which is
 * user modअगरiable via sysfs but initially set to SD_TIMEOUT
 */
#घोषणा SD_FLUSH_TIMEOUT_MULTIPLIER	2
#घोषणा SD_WRITE_SAME_TIMEOUT	(120 * HZ)

/*
 * Number of allowed retries
 */
#घोषणा SD_MAX_RETRIES		5
#घोषणा SD_PASSTHROUGH_RETRIES	1
#घोषणा SD_MAX_MEDIUM_TIMEOUTS	2

/*
 * Size of the initial data buffer क्रम mode and पढ़ो capacity data
 */
#घोषणा SD_BUF_SIZE		512

/*
 * Number of sectors at the end of the device to aव्योम multi-sector
 * accesses to in the हाल of last_sector_bug
 */
#घोषणा SD_LAST_BUGGY_SECTORS	8

क्रमागत अणु
	SD_EXT_CDB_SIZE = 32,	/* Extended CDB size */
	SD_MEMPOOL_SIZE = 2,	/* CDB pool size */
पूर्ण;

क्रमागत अणु
	SD_DEF_XFER_BLOCKS = 0xffff,
	SD_MAX_XFER_BLOCKS = 0xffffffff,
	SD_MAX_WS10_BLOCKS = 0xffff,
	SD_MAX_WS16_BLOCKS = 0x7fffff,
पूर्ण;

क्रमागत अणु
	SD_LBP_FULL = 0,	/* Full logical block provisioning */
	SD_LBP_UNMAP,		/* Use UNMAP command */
	SD_LBP_WS16,		/* Use WRITE SAME(16) with UNMAP bit */
	SD_LBP_WS10,		/* Use WRITE SAME(10) with UNMAP bit */
	SD_LBP_ZERO,		/* Use WRITE SAME(10) with zero payload */
	SD_LBP_DISABLE,		/* Discard disabled due to failed cmd */
पूर्ण;

क्रमागत अणु
	SD_ZERO_WRITE = 0,	/* Use WRITE(10/16) command */
	SD_ZERO_WS,		/* Use WRITE SAME(10/16) command */
	SD_ZERO_WS16_UNMAP,	/* Use WRITE SAME(16) with UNMAP */
	SD_ZERO_WS10_UNMAP,	/* Use WRITE SAME(10) with UNMAP */
पूर्ण;

काष्ठा scsi_disk अणु
	काष्ठा scsi_driver *driver;	/* always &sd_ढाँचा */
	काष्ठा scsi_device *device;
	काष्ठा device	dev;
	काष्ठा gendisk	*disk;
	काष्ठा opal_dev *opal_dev;
#अगर_घोषित CONFIG_BLK_DEV_ZONED
	u32		nr_zones;
	u32		rev_nr_zones;
	u32		zone_blocks;
	u32		rev_zone_blocks;
	u32		zones_optimal_खोलो;
	u32		zones_optimal_nonseq;
	u32		zones_max_खोलो;
	u32		*zones_wp_offset;
	spinlock_t	zones_wp_offset_lock;
	u32		*rev_wp_offset;
	काष्ठा mutex	rev_mutex;
	काष्ठा work_काष्ठा zone_wp_offset_work;
	अक्षर		*zone_wp_update_buf;
#पूर्ण_अगर
	atomic_t	खोलोers;
	sector_t	capacity;	/* size in logical blocks */
	पूर्णांक		max_retries;
	u32		max_xfer_blocks;
	u32		opt_xfer_blocks;
	u32		max_ws_blocks;
	u32		max_unmap_blocks;
	u32		unmap_granularity;
	u32		unmap_alignment;
	u32		index;
	अचिन्हित पूर्णांक	physical_block_size;
	अचिन्हित पूर्णांक	max_medium_access_समयouts;
	अचिन्हित पूर्णांक	medium_access_समयd_out;
	u8		media_present;
	u8		ग_लिखो_prot;
	u8		protection_type;/* Data Integrity Field */
	u8		provisioning_mode;
	u8		zeroing_mode;
	अचिन्हित	ATO : 1;	/* state of disk ATO bit */
	अचिन्हित	cache_override : 1; /* temp override of WCE,RCD */
	अचिन्हित	WCE : 1;	/* state of disk WCE bit */
	अचिन्हित	RCD : 1;	/* state of disk RCD bit, unused */
	अचिन्हित	DPOFUA : 1;	/* state of disk DPOFUA bit */
	अचिन्हित	first_scan : 1;
	अचिन्हित	lbpme : 1;
	अचिन्हित	lbprz : 1;
	अचिन्हित	lbpu : 1;
	अचिन्हित	lbpws : 1;
	अचिन्हित	lbpws10 : 1;
	अचिन्हित	lbpvpd : 1;
	अचिन्हित	ws10 : 1;
	अचिन्हित	ws16 : 1;
	अचिन्हित	rc_basis: 2;
	अचिन्हित	zoned: 2;
	अचिन्हित	urswrz : 1;
	अचिन्हित	security : 1;
	अचिन्हित	ignore_medium_access_errors : 1;
पूर्ण;
#घोषणा to_scsi_disk(obj) container_of(obj,काष्ठा scsi_disk,dev)

अटल अंतरभूत काष्ठा scsi_disk *scsi_disk(काष्ठा gendisk *disk)
अणु
	वापस container_of(disk->निजी_data, काष्ठा scsi_disk, driver);
पूर्ण

#घोषणा sd_prपूर्णांकk(prefix, sdsk, fmt, a...)				\
        (sdsk)->disk ?							\
	      sdev_prefix_prपूर्णांकk(prefix, (sdsk)->device,		\
				 (sdsk)->disk->disk_name, fmt, ##a) :	\
	      sdev_prपूर्णांकk(prefix, (sdsk)->device, fmt, ##a)

#घोषणा sd_first_prपूर्णांकk(prefix, sdsk, fmt, a...)			\
	करो अणु								\
		अगर ((sdsk)->first_scan)					\
			sd_prपूर्णांकk(prefix, sdsk, fmt, ##a);		\
	पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक scsi_medium_access_command(काष्ठा scsi_cmnd *scmd)
अणु
	चयन (scmd->cmnd[0]) अणु
	हाल READ_6:
	हाल READ_10:
	हाल READ_12:
	हाल READ_16:
	हाल SYNCHRONIZE_CACHE:
	हाल VERIFY:
	हाल VERIFY_12:
	हाल VERIFY_16:
	हाल WRITE_6:
	हाल WRITE_10:
	हाल WRITE_12:
	हाल WRITE_16:
	हाल WRITE_SAME:
	हाल WRITE_SAME_16:
	हाल UNMAP:
		वापस 1;
	हाल VARIABLE_LENGTH_CMD:
		चयन (scmd->cmnd[9]) अणु
		हाल READ_32:
		हाल VERIFY_32:
		हाल WRITE_32:
		हाल WRITE_SAME_32:
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत sector_t logical_to_sectors(काष्ठा scsi_device *sdev, sector_t blocks)
अणु
	वापस blocks << (ilog2(sdev->sector_size) - 9);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक logical_to_bytes(काष्ठा scsi_device *sdev, sector_t blocks)
अणु
	वापस blocks * sdev->sector_size;
पूर्ण

अटल अंतरभूत sector_t bytes_to_logical(काष्ठा scsi_device *sdev, अचिन्हित पूर्णांक bytes)
अणु
	वापस bytes >> ilog2(sdev->sector_size);
पूर्ण

अटल अंतरभूत sector_t sectors_to_logical(काष्ठा scsi_device *sdev, sector_t sector)
अणु
	वापस sector >> (ilog2(sdev->sector_size) - 9);
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY

बाह्य व्योम sd_dअगर_config_host(काष्ठा scsi_disk *);

#अन्यथा /* CONFIG_BLK_DEV_INTEGRITY */

अटल अंतरभूत व्योम sd_dअगर_config_host(काष्ठा scsi_disk *disk)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_BLK_DEV_INTEGRITY */

अटल अंतरभूत पूर्णांक sd_is_zoned(काष्ठा scsi_disk *sdkp)
अणु
	वापस sdkp->zoned == 1 || sdkp->device->type == TYPE_ZBC;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_ZONED

व्योम sd_zbc_release_disk(काष्ठा scsi_disk *sdkp);
पूर्णांक sd_zbc_पढ़ो_zones(काष्ठा scsi_disk *sdkp, अचिन्हित अक्षर *buffer);
पूर्णांक sd_zbc_revalidate_zones(काष्ठा scsi_disk *sdkp);
blk_status_t sd_zbc_setup_zone_mgmt_cmnd(काष्ठा scsi_cmnd *cmd,
					 अचिन्हित अक्षर op, bool all);
अचिन्हित पूर्णांक sd_zbc_complete(काष्ठा scsi_cmnd *cmd, अचिन्हित पूर्णांक good_bytes,
			     काष्ठा scsi_sense_hdr *sshdr);
पूर्णांक sd_zbc_report_zones(काष्ठा gendisk *disk, sector_t sector,
		अचिन्हित पूर्णांक nr_zones, report_zones_cb cb, व्योम *data);

blk_status_t sd_zbc_prepare_zone_append(काष्ठा scsi_cmnd *cmd, sector_t *lba,
				        अचिन्हित पूर्णांक nr_blocks);

#अन्यथा /* CONFIG_BLK_DEV_ZONED */

अटल अंतरभूत व्योम sd_zbc_release_disk(काष्ठा scsi_disk *sdkp) अणुपूर्ण

अटल अंतरभूत पूर्णांक sd_zbc_पढ़ो_zones(काष्ठा scsi_disk *sdkp,
				    अचिन्हित अक्षर *buf)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sd_zbc_revalidate_zones(काष्ठा scsi_disk *sdkp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत blk_status_t sd_zbc_setup_zone_mgmt_cmnd(काष्ठा scsi_cmnd *cmd,
						       अचिन्हित अक्षर op,
						       bool all)
अणु
	वापस BLK_STS_TARGET;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sd_zbc_complete(काष्ठा scsi_cmnd *cmd,
			अचिन्हित पूर्णांक good_bytes, काष्ठा scsi_sense_hdr *sshdr)
अणु
	वापस good_bytes;
पूर्ण

अटल अंतरभूत blk_status_t sd_zbc_prepare_zone_append(काष्ठा scsi_cmnd *cmd,
						      sector_t *lba,
						      अचिन्हित पूर्णांक nr_blocks)
अणु
	वापस BLK_STS_TARGET;
पूर्ण

#घोषणा sd_zbc_report_zones शून्य

#पूर्ण_अगर /* CONFIG_BLK_DEV_ZONED */

व्योम sd_prपूर्णांक_sense_hdr(काष्ठा scsi_disk *sdkp, काष्ठा scsi_sense_hdr *sshdr);
व्योम sd_prपूर्णांक_result(स्थिर काष्ठा scsi_disk *sdkp, स्थिर अक्षर *msg, पूर्णांक result);

#पूर्ण_अगर /* _SCSI_DISK_H */
