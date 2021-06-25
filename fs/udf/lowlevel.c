<शैली गुरु>
/*
 * lowlevel.c
 *
 * PURPOSE
 *  Low Level Device Routines क्रम the UDF fileप्रणाली
 *
 * COPYRIGHT
 *	This file is distributed under the terms of the GNU General Public
 *	License (GPL). Copies of the GPL can be obtained from:
 *		ftp://prep.ai.mit.edu/pub/gnu/GPL
 *	Each contributing author retains all rights to their own work.
 *
 *  (C) 1999-2001 Ben Fennema
 *
 * HISTORY
 *
 *  03/26/99 blf  Created.
 */

#समावेश "udfdecl.h"

#समावेश <linux/blkdev.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/uaccess.h>

#समावेश "udf_sb.h"

अचिन्हित पूर्णांक udf_get_last_session(काष्ठा super_block *sb)
अणु
	काष्ठा cdrom_device_info *cdi = disk_to_cdi(sb->s_bdev->bd_disk);
	काष्ठा cdrom_multisession ms_info;

	अगर (!cdi) अणु
		udf_debug("CDROMMULTISESSION not supported.\n");
		वापस 0;
	पूर्ण

	ms_info.addr_क्रमmat = CDROM_LBA;
	अगर (cdrom_multisession(cdi, &ms_info) == 0) अणु
		udf_debug("XA disk: %s, vol_desc_start=%d\n",
			  ms_info.xa_flag ? "yes" : "no", ms_info.addr.lba);
		अगर (ms_info.xa_flag) /* necessary क्रम a valid ms_info.addr */
			वापस ms_info.addr.lba;
	पूर्ण
	वापस 0;
पूर्ण

अचिन्हित दीर्घ udf_get_last_block(काष्ठा super_block *sb)
अणु
	काष्ठा block_device *bdev = sb->s_bdev;
	काष्ठा cdrom_device_info *cdi = disk_to_cdi(bdev->bd_disk);
	अचिन्हित दीर्घ lblock = 0;

	/*
	 * The cdrom layer call failed or वापसed obviously bogus value?
	 * Try using the device size...
	 */
	अगर (!cdi || cdrom_get_last_written(cdi, &lblock) || lblock == 0)
		lblock = i_size_पढ़ो(bdev->bd_inode) >> sb->s_blocksize_bits;

	अगर (lblock)
		वापस lblock - 1;
	वापस 0;
पूर्ण
