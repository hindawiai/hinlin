<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * scsicam.c - SCSI CAM support functions, use क्रम HDIO_GETGEO, etc.
 *
 * Copyright 1993, 1994 Drew Eckhardt
 *      Visionary Computing 
 *      (Unix and Linux consulting and custom programming)
 *      drew@Coloraकरो.EDU
 *      +1 (303) 786-7975
 *
 * For more inक्रमmation, please consult the SCSI-CAM draft.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/genhd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/msकरोs_partition.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsicam.h>

/**
 * scsi_bios_ptable - Read PC partition table out of first sector of device.
 * @dev: from this device
 *
 * Description: Reads the first sector from the device and वापसs %0x42 bytes
 *              starting at offset %0x1be.
 * Returns: partition table in kदो_स्मृति(GFP_KERNEL) memory, or शून्य on error.
 */
अचिन्हित अक्षर *scsi_bios_ptable(काष्ठा block_device *dev)
अणु
	काष्ठा address_space *mapping = bdev_whole(dev)->bd_inode->i_mapping;
	अचिन्हित अक्षर *res = शून्य;
	काष्ठा page *page;

	page = पढ़ो_mapping_page(mapping, 0, शून्य);
	अगर (IS_ERR(page))
		वापस शून्य;

	अगर (!PageError(page))
		res = kmemdup(page_address(page) + 0x1be, 66, GFP_KERNEL);
	put_page(page);
	वापस res;
पूर्ण
EXPORT_SYMBOL(scsi_bios_ptable);

/**
 * scsi_partsize - Parse cylinders/heads/sectors from PC partition table
 * @bdev: block device to parse
 * @capacity: size of the disk in sectors
 * @geom: output in क्रमm of [hds, cylinders, sectors]
 *
 * Determine the BIOS mapping/geometry used to create the partition
 * table, storing the results in @geom.
 *
 * Returns: %false on failure, %true on success.
 */
bool scsi_partsize(काष्ठा block_device *bdev, sector_t capacity, पूर्णांक geom[3])
अणु
	पूर्णांक cyl, ext_cyl, end_head, end_cyl, end_sector;
	अचिन्हित पूर्णांक logical_end, physical_end, ext_physical_end;
	काष्ठा msकरोs_partition *p, *largest = शून्य;
	व्योम *buf;
	पूर्णांक ret = false;

	buf = scsi_bios_ptable(bdev);
	अगर (!buf)
		वापस false;

	अगर (*(अचिन्हित लघु *) (buf + 64) == 0xAA55) अणु
		पूर्णांक largest_cyl = -1, i;

		क्रम (i = 0, p = buf; i < 4; i++, p++) अणु
			अगर (!p->sys_ind)
				जारी;
#अगर_घोषित DEBUG
			prपूर्णांकk("scsicam_bios_param : partition %d has system \n",
			       i);
#पूर्ण_अगर
			cyl = p->cyl + ((p->sector & 0xc0) << 2);
			अगर (cyl > largest_cyl) अणु
				largest_cyl = cyl;
				largest = p;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (largest) अणु
		end_cyl = largest->end_cyl + ((largest->end_sector & 0xc0) << 2);
		end_head = largest->end_head;
		end_sector = largest->end_sector & 0x3f;

		अगर (end_head + 1 == 0 || end_sector == 0)
			जाओ out_मुक्त_buf;

#अगर_घोषित DEBUG
		prपूर्णांकk("scsicam_bios_param : end at h = %d, c = %d, s = %d\n",
		       end_head, end_cyl, end_sector);
#पूर्ण_अगर

		physical_end = end_cyl * (end_head + 1) * end_sector +
		    end_head * end_sector + end_sector;

		/* This is the actual _sector_ number at the end */
		logical_end = get_unaligned_le32(&largest->start_sect)
		    + get_unaligned_le32(&largest->nr_sects);

		/* This is क्रम >1023 cylinders */
		ext_cyl = (logical_end - (end_head * end_sector + end_sector))
		    / (end_head + 1) / end_sector;
		ext_physical_end = ext_cyl * (end_head + 1) * end_sector +
		    end_head * end_sector + end_sector;

#अगर_घोषित DEBUG
		prपूर्णांकk("scsicam_bios_param : logical_end=%d physical_end=%d ext_physical_end=%d ext_cyl=%d\n"
		  ,logical_end, physical_end, ext_physical_end, ext_cyl);
#पूर्ण_अगर

		अगर (logical_end == physical_end ||
		    (end_cyl == 1023 && ext_physical_end == logical_end)) अणु
			geom[0] = end_head + 1;
			geom[1] = end_sector;
			geom[2] = (अचिन्हित दीर्घ)capacity /
				((end_head + 1) * end_sector);
			ret = true;
			जाओ out_मुक्त_buf;
		पूर्ण
#अगर_घोषित DEBUG
		prपूर्णांकk("scsicam_bios_param : logical (%u) != physical (%u)\n",
		       logical_end, physical_end);
#पूर्ण_अगर
	पूर्ण

out_मुक्त_buf:
	kमुक्त(buf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(scsi_partsize);

/*
 * Function : अटल पूर्णांक setsize(अचिन्हित दीर्घ capacity,अचिन्हित पूर्णांक *cyls,
 *      अचिन्हित पूर्णांक *hds, अचिन्हित पूर्णांक *secs);
 *
 * Purpose : to determine a near-optimal पूर्णांक 0x13 mapping क्रम a
 *      SCSI disk in terms of lost space of size capacity, storing
 *      the results in *cyls, *hds, and *secs.
 *
 * Returns : -1 on failure, 0 on success.
 *
 * Extracted from
 *
 * WORKING                                                    X3T9.2
 * DRAFT                                                        792D
 * see http://www.t10.org/ftp/t10/drafts/cam/cam-r12b.pdf
 *
 *                                                        Revision 6
 *                                                         10-MAR-94
 * Inक्रमmation technology -
 * SCSI-2 Common access method
 * transport and SCSI पूर्णांकerface module
 * 
 * ANNEX A :
 *
 * setsize() converts a पढ़ो capacity value to पूर्णांक 13h
 * head-cylinder-sector requirements. It minimizes the value क्रम
 * number of heads and maximizes the number of cylinders. This
 * will support rather large disks beक्रमe the number of heads
 * will not fit in 4 bits (or 6 bits). This algorithm also
 * minimizes the number of sectors that will be unused at the end
 * of the disk जबतक allowing क्रम very large disks to be
 * accommodated. This algorithm करोes not use physical geometry. 
 */

अटल पूर्णांक setsize(अचिन्हित दीर्घ capacity, अचिन्हित पूर्णांक *cyls, अचिन्हित पूर्णांक *hds,
		   अचिन्हित पूर्णांक *secs)
अणु
	अचिन्हित पूर्णांक rv = 0;
	अचिन्हित दीर्घ heads, sectors, cylinders, temp;

	cylinders = 1024L;	/* Set number of cylinders to max */
	sectors = 62L;		/* Maximize sectors per track */

	temp = cylinders * sectors;	/* Compute भागisor क्रम heads */
	heads = capacity / temp;	/* Compute value क्रम number of heads */
	अगर (capacity % temp) अणु	/* If no reमुख्यder, करोne! */
		heads++;	/* Else, increment number of heads */
		temp = cylinders * heads;	/* Compute भागisor क्रम sectors */
		sectors = capacity / temp;	/* Compute value क्रम sectors per
						   track */
		अगर (capacity % temp) अणु	/* If no reमुख्यder, करोne! */
			sectors++;	/* Else, increment number of sectors */
			temp = heads * sectors;		/* Compute भागisor क्रम cylinders */
			cylinders = capacity / temp;	/* Compute number of cylinders */
		पूर्ण
	पूर्ण
	अगर (cylinders == 0)
		rv = (अचिन्हित) -1;	/* Give error अगर 0 cylinders */

	*cyls = (अचिन्हित पूर्णांक) cylinders;	/* Stuff वापस values */
	*secs = (अचिन्हित पूर्णांक) sectors;
	*hds = (अचिन्हित पूर्णांक) heads;
	वापस (rv);
पूर्ण

/**
 * scsicam_bios_param - Determine geometry of a disk in cylinders/heads/sectors.
 * @bdev: which device
 * @capacity: size of the disk in sectors
 * @ip: वापस value: ip[0]=heads, ip[1]=sectors, ip[2]=cylinders
 *
 * Description : determine the BIOS mapping/geometry used क्रम a drive in a
 *      SCSI-CAM प्रणाली, storing the results in ip as required
 *      by the HDIO_GETGEO ioctl().
 *
 * Returns : -1 on failure, 0 on success.
 */
पूर्णांक scsicam_bios_param(काष्ठा block_device *bdev, sector_t capacity, पूर्णांक *ip)
अणु
	u64 capacity64 = capacity;	/* Suppress gcc warning */
	पूर्णांक ret = 0;

	/* try to infer mapping from partition table */
	अगर (scsi_partsize(bdev, capacity, ip))
		वापस 0;

	अगर (capacity64 < (1ULL << 32)) अणु
		/*
		 * Pick some standard mapping with at most 1024 cylinders, and
		 * at most 62 sectors per track - this works up to 7905 MB.
		 */
		ret = setsize((अचिन्हित दीर्घ)capacity, (अचिन्हित पूर्णांक *)ip + 2,
		       (अचिन्हित पूर्णांक *)ip + 0, (अचिन्हित पूर्णांक *)ip + 1);
	पूर्ण

	/*
	 * If something went wrong, then apparently we have to वापस a geometry
	 * with more than 1024 cylinders.
	 */
	अगर (ret || ip[0] > 255 || ip[1] > 63) अणु
		अगर ((capacity >> 11) > 65534) अणु
			ip[0] = 255;
			ip[1] = 63;
		पूर्ण अन्यथा अणु
			ip[0] = 64;
			ip[1] = 32;
		पूर्ण

		अगर (capacity > 65535*63*255)
			ip[2] = 65535;
		अन्यथा
			ip[2] = (अचिन्हित दीर्घ)capacity / (ip[0] * ip[1]);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(scsicam_bios_param);
