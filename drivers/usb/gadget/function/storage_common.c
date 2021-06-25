<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * storage_common.c -- Common definitions क्रम mass storage functionality
 *
 * Copyright (C) 2003-2008 Alan Stern
 * Copyeight (C) 2009 Samsung Electronics
 * Author: Michal Nazarewicz (mina86@mina86.com)
 */

/*
 * This file requires the following identअगरiers used in USB strings to
 * be defined (each of type poपूर्णांकer to अक्षर):
 *  - fsg_string_पूर्णांकerface    -- name of the पूर्णांकerface
 */

/*
 * When USB_GADGET_DEBUG_खाताS is defined the module param num_buffers
 * sets the number of pipeline buffers (length of the fsg_buffhd array).
 * The valid range of num_buffers is: num >= 2 && num <= 4.
 */

#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/usb/composite.h>

#समावेश "storage_common.h"

/* There is only one पूर्णांकerface. */

काष्ठा usb_पूर्णांकerface_descriptor fsg_पूर्णांकf_desc = अणु
	.bLength =		माप fsg_पूर्णांकf_desc,
	.bDescriptorType =	USB_DT_INTERFACE,

	.bNumEndpoपूर्णांकs =	2,		/* Adjusted during fsg_bind() */
	.bInterfaceClass =	USB_CLASS_MASS_STORAGE,
	.bInterfaceSubClass =	USB_SC_SCSI,	/* Adjusted during fsg_bind() */
	.bInterfaceProtocol =	USB_PR_BULK,	/* Adjusted during fsg_bind() */
	.iInterface =		FSG_STRING_INTERFACE,
पूर्ण;
EXPORT_SYMBOL_GPL(fsg_पूर्णांकf_desc);

/*
 * Three full-speed endpoपूर्णांक descriptors: bulk-in, bulk-out, and
 * पूर्णांकerrupt-in.
 */

काष्ठा usb_endpoपूर्णांक_descriptor fsg_fs_bulk_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	/* wMaxPacketSize set by स्वतःconfiguration */
पूर्ण;
EXPORT_SYMBOL_GPL(fsg_fs_bulk_in_desc);

काष्ठा usb_endpoपूर्णांक_descriptor fsg_fs_bulk_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	/* wMaxPacketSize set by स्वतःconfiguration */
पूर्ण;
EXPORT_SYMBOL_GPL(fsg_fs_bulk_out_desc);

काष्ठा usb_descriptor_header *fsg_fs_function[] = अणु
	(काष्ठा usb_descriptor_header *) &fsg_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &fsg_fs_bulk_in_desc,
	(काष्ठा usb_descriptor_header *) &fsg_fs_bulk_out_desc,
	शून्य,
पूर्ण;
EXPORT_SYMBOL_GPL(fsg_fs_function);


/*
 * USB 2.0 devices need to expose both high speed and full speed
 * descriptors, unless they only run at full speed.
 *
 * That means alternate endpoपूर्णांक descriptors (bigger packets).
 */
काष्ठा usb_endpoपूर्णांक_descriptor fsg_hs_bulk_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	/* bEndpoपूर्णांकAddress copied from fs_bulk_in_desc during fsg_bind() */
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;
EXPORT_SYMBOL_GPL(fsg_hs_bulk_in_desc);

काष्ठा usb_endpoपूर्णांक_descriptor fsg_hs_bulk_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	/* bEndpoपूर्णांकAddress copied from fs_bulk_out_desc during fsg_bind() */
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
	.bInterval =		1,	/* NAK every 1 uframe */
पूर्ण;
EXPORT_SYMBOL_GPL(fsg_hs_bulk_out_desc);


काष्ठा usb_descriptor_header *fsg_hs_function[] = अणु
	(काष्ठा usb_descriptor_header *) &fsg_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &fsg_hs_bulk_in_desc,
	(काष्ठा usb_descriptor_header *) &fsg_hs_bulk_out_desc,
	शून्य,
पूर्ण;
EXPORT_SYMBOL_GPL(fsg_hs_function);

काष्ठा usb_endpoपूर्णांक_descriptor fsg_ss_bulk_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	/* bEndpoपूर्णांकAddress copied from fs_bulk_in_desc during fsg_bind() */
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;
EXPORT_SYMBOL_GPL(fsg_ss_bulk_in_desc);

काष्ठा usb_ss_ep_comp_descriptor fsg_ss_bulk_in_comp_desc = अणु
	.bLength =		माप(fsg_ss_bulk_in_comp_desc),
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	/*.bMaxBurst =		DYNAMIC, */
पूर्ण;
EXPORT_SYMBOL_GPL(fsg_ss_bulk_in_comp_desc);

काष्ठा usb_endpoपूर्णांक_descriptor fsg_ss_bulk_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	/* bEndpoपूर्णांकAddress copied from fs_bulk_out_desc during fsg_bind() */
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;
EXPORT_SYMBOL_GPL(fsg_ss_bulk_out_desc);

काष्ठा usb_ss_ep_comp_descriptor fsg_ss_bulk_out_comp_desc = अणु
	.bLength =		माप(fsg_ss_bulk_in_comp_desc),
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	/*.bMaxBurst =		DYNAMIC, */
पूर्ण;
EXPORT_SYMBOL_GPL(fsg_ss_bulk_out_comp_desc);

काष्ठा usb_descriptor_header *fsg_ss_function[] = अणु
	(काष्ठा usb_descriptor_header *) &fsg_पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &fsg_ss_bulk_in_desc,
	(काष्ठा usb_descriptor_header *) &fsg_ss_bulk_in_comp_desc,
	(काष्ठा usb_descriptor_header *) &fsg_ss_bulk_out_desc,
	(काष्ठा usb_descriptor_header *) &fsg_ss_bulk_out_comp_desc,
	शून्य,
पूर्ण;
EXPORT_SYMBOL_GPL(fsg_ss_function);


 /*-------------------------------------------------------------------------*/

/*
 * If the next two routines are called जबतक the gadget is रेजिस्टरed,
 * the caller must own fsg->filesem क्रम writing.
 */

व्योम fsg_lun_बंद(काष्ठा fsg_lun *curlun)
अणु
	अगर (curlun->filp) अणु
		LDBG(curlun, "close backing file\n");
		fput(curlun->filp);
		curlun->filp = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fsg_lun_बंद);

पूर्णांक fsg_lun_खोलो(काष्ठा fsg_lun *curlun, स्थिर अक्षर *filename)
अणु
	पूर्णांक				ro;
	काष्ठा file			*filp = शून्य;
	पूर्णांक				rc = -EINVAL;
	काष्ठा inode			*inode = शून्य;
	loff_t				size;
	loff_t				num_sectors;
	loff_t				min_sectors;
	अचिन्हित पूर्णांक			blkbits;
	अचिन्हित पूर्णांक			blksize;

	/* R/W अगर we can, R/O अगर we must */
	ro = curlun->initially_ro;
	अगर (!ro) अणु
		filp = filp_खोलो(filename, O_RDWR | O_LARGEखाता, 0);
		अगर (PTR_ERR(filp) == -EROFS || PTR_ERR(filp) == -EACCES)
			ro = 1;
	पूर्ण
	अगर (ro)
		filp = filp_खोलो(filename, O_RDONLY | O_LARGEखाता, 0);
	अगर (IS_ERR(filp)) अणु
		LINFO(curlun, "unable to open backing file: %s\n", filename);
		वापस PTR_ERR(filp);
	पूर्ण

	अगर (!(filp->f_mode & FMODE_WRITE))
		ro = 1;

	inode = filp->f_mapping->host;
	अगर ((!S_ISREG(inode->i_mode) && !S_ISBLK(inode->i_mode))) अणु
		LINFO(curlun, "invalid file type: %s\n", filename);
		जाओ out;
	पूर्ण

	/*
	 * If we can't read the file, it's no good.
	 * If we can't ग_लिखो the file, use it पढ़ो-only.
	 */
	अगर (!(filp->f_mode & FMODE_CAN_READ)) अणु
		LINFO(curlun, "file not readable: %s\n", filename);
		जाओ out;
	पूर्ण
	अगर (!(filp->f_mode & FMODE_CAN_WRITE))
		ro = 1;

	size = i_size_पढ़ो(inode);
	अगर (size < 0) अणु
		LINFO(curlun, "unable to find file size: %s\n", filename);
		rc = (पूर्णांक) size;
		जाओ out;
	पूर्ण

	अगर (curlun->cdrom) अणु
		blksize = 2048;
		blkbits = 11;
	पूर्ण अन्यथा अगर (S_ISBLK(inode->i_mode)) अणु
		blksize = bdev_logical_block_size(I_BDEV(inode));
		blkbits = blksize_bits(blksize);
	पूर्ण अन्यथा अणु
		blksize = 512;
		blkbits = 9;
	पूर्ण

	num_sectors = size >> blkbits; /* File size in logic-block-size blocks */
	min_sectors = 1;
	अगर (curlun->cdrom) अणु
		min_sectors = 300;	/* Smallest track is 300 frames */
		अगर (num_sectors >= 256*60*75) अणु
			num_sectors = 256*60*75 - 1;
			LINFO(curlun, "file too big: %s\n", filename);
			LINFO(curlun, "using only first %d blocks\n",
					(पूर्णांक) num_sectors);
		पूर्ण
	पूर्ण
	अगर (num_sectors < min_sectors) अणु
		LINFO(curlun, "file too small: %s\n", filename);
		rc = -ETOOSMALL;
		जाओ out;
	पूर्ण

	अगर (fsg_lun_is_खोलो(curlun))
		fsg_lun_बंद(curlun);

	curlun->blksize = blksize;
	curlun->blkbits = blkbits;
	curlun->ro = ro;
	curlun->filp = filp;
	curlun->file_length = size;
	curlun->num_sectors = num_sectors;
	LDBG(curlun, "open backing file: %s\n", filename);
	वापस 0;

out:
	fput(filp);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_lun_खोलो);


/*-------------------------------------------------------------------------*/

/*
 * Sync the file data, करोn't bother with the metadata.
 * This code was copied from fs/buffer.c:sys_fdatasync().
 */
पूर्णांक fsg_lun_fsync_sub(काष्ठा fsg_lun *curlun)
अणु
	काष्ठा file	*filp = curlun->filp;

	अगर (curlun->ro || !filp)
		वापस 0;
	वापस vfs_fsync(filp, 1);
पूर्ण
EXPORT_SYMBOL_GPL(fsg_lun_fsync_sub);

व्योम store_cdrom_address(u8 *dest, पूर्णांक msf, u32 addr)
अणु
	अगर (msf) अणु
		/* Convert to Minutes-Seconds-Frames */
		addr >>= 2;		/* Convert to 2048-byte frames */
		addr += 2*75;		/* Lead-in occupies 2 seconds */
		dest[3] = addr % 75;	/* Frames */
		addr /= 75;
		dest[2] = addr % 60;	/* Seconds */
		addr /= 60;
		dest[1] = addr;		/* Minutes */
		dest[0] = 0;		/* Reserved */
	पूर्ण अन्यथा अणु
		/* Absolute sector */
		put_unaligned_be32(addr, dest);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(store_cdrom_address);

/*-------------------------------------------------------------------------*/


sमाप_प्रकार fsg_show_ro(काष्ठा fsg_lun *curlun, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", fsg_lun_is_खोलो(curlun)
				  ? curlun->ro
				  : curlun->initially_ro);
पूर्ण
EXPORT_SYMBOL_GPL(fsg_show_ro);

sमाप_प्रकार fsg_show_nofua(काष्ठा fsg_lun *curlun, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", curlun->nofua);
पूर्ण
EXPORT_SYMBOL_GPL(fsg_show_nofua);

sमाप_प्रकार fsg_show_file(काष्ठा fsg_lun *curlun, काष्ठा rw_semaphore *filesem,
		      अक्षर *buf)
अणु
	अक्षर		*p;
	sमाप_प्रकार		rc;

	करोwn_पढ़ो(filesem);
	अगर (fsg_lun_is_खोलो(curlun)) अणु	/* Get the complete pathname */
		p = file_path(curlun->filp, buf, PAGE_SIZE - 1);
		अगर (IS_ERR(p))
			rc = PTR_ERR(p);
		अन्यथा अणु
			rc = म_माप(p);
			स_हटाओ(buf, p, rc);
			buf[rc] = '\n';		/* Add a newline */
			buf[++rc] = 0;
		पूर्ण
	पूर्ण अन्यथा अणु				/* No file, वापस 0 bytes */
		*buf = 0;
		rc = 0;
	पूर्ण
	up_पढ़ो(filesem);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_show_file);

sमाप_प्रकार fsg_show_cdrom(काष्ठा fsg_lun *curlun, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", curlun->cdrom);
पूर्ण
EXPORT_SYMBOL_GPL(fsg_show_cdrom);

sमाप_प्रकार fsg_show_removable(काष्ठा fsg_lun *curlun, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", curlun->removable);
पूर्ण
EXPORT_SYMBOL_GPL(fsg_show_removable);

sमाप_प्रकार fsg_show_inquiry_string(काष्ठा fsg_lun *curlun, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", curlun->inquiry_string);
पूर्ण
EXPORT_SYMBOL_GPL(fsg_show_inquiry_string);

/*
 * The caller must hold fsg->filesem क्रम पढ़ोing when calling this function.
 */
अटल sमाप_प्रकार _fsg_store_ro(काष्ठा fsg_lun *curlun, bool ro)
अणु
	अगर (fsg_lun_is_खोलो(curlun)) अणु
		LDBG(curlun, "read-only status change prevented\n");
		वापस -EBUSY;
	पूर्ण

	curlun->ro = ro;
	curlun->initially_ro = ro;
	LDBG(curlun, "read-only status set to %d\n", curlun->ro);

	वापस 0;
पूर्ण

sमाप_प्रकार fsg_store_ro(काष्ठा fsg_lun *curlun, काष्ठा rw_semaphore *filesem,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार		rc;
	bool		ro;

	rc = strtobool(buf, &ro);
	अगर (rc)
		वापस rc;

	/*
	 * Allow the ग_लिखो-enable status to change only जबतक the
	 * backing file is बंदd.
	 */
	करोwn_पढ़ो(filesem);
	rc = _fsg_store_ro(curlun, ro);
	अगर (!rc)
		rc = count;
	up_पढ़ो(filesem);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_store_ro);

sमाप_प्रकार fsg_store_nofua(काष्ठा fsg_lun *curlun, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	bool		nofua;
	पूर्णांक		ret;

	ret = strtobool(buf, &nofua);
	अगर (ret)
		वापस ret;

	/* Sync data when चयनing from async mode to sync */
	अगर (!nofua && curlun->nofua)
		fsg_lun_fsync_sub(curlun);

	curlun->nofua = nofua;

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_store_nofua);

sमाप_प्रकार fsg_store_file(काष्ठा fsg_lun *curlun, काष्ठा rw_semaphore *filesem,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक		rc = 0;

	अगर (curlun->prevent_medium_removal && fsg_lun_is_खोलो(curlun)) अणु
		LDBG(curlun, "eject attempt prevented\n");
		वापस -EBUSY;				/* "Door is locked" */
	पूर्ण

	/* Remove a trailing newline */
	अगर (count > 0 && buf[count-1] == '\n')
		((अक्षर *) buf)[count-1] = 0;		/* Ugh! */

	/* Load new medium */
	करोwn_ग_लिखो(filesem);
	अगर (count > 0 && buf[0]) अणु
		/* fsg_lun_खोलो() will बंद existing file अगर any. */
		rc = fsg_lun_खोलो(curlun, buf);
		अगर (rc == 0)
			curlun->unit_attention_data =
					SS_NOT_READY_TO_READY_TRANSITION;
	पूर्ण अन्यथा अगर (fsg_lun_is_खोलो(curlun)) अणु
		fsg_lun_बंद(curlun);
		curlun->unit_attention_data = SS_MEDIUM_NOT_PRESENT;
	पूर्ण
	up_ग_लिखो(filesem);
	वापस (rc < 0 ? rc : count);
पूर्ण
EXPORT_SYMBOL_GPL(fsg_store_file);

sमाप_प्रकार fsg_store_cdrom(काष्ठा fsg_lun *curlun, काष्ठा rw_semaphore *filesem,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	bool		cdrom;
	पूर्णांक		ret;

	ret = strtobool(buf, &cdrom);
	अगर (ret)
		वापस ret;

	करोwn_पढ़ो(filesem);
	ret = cdrom ? _fsg_store_ro(curlun, true) : 0;

	अगर (!ret) अणु
		curlun->cdrom = cdrom;
		ret = count;
	पूर्ण
	up_पढ़ो(filesem);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_store_cdrom);

sमाप_प्रकार fsg_store_removable(काष्ठा fsg_lun *curlun, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	bool		removable;
	पूर्णांक		ret;

	ret = strtobool(buf, &removable);
	अगर (ret)
		वापस ret;

	curlun->removable = removable;

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_store_removable);

sमाप_प्रकार fsg_store_inquiry_string(काष्ठा fsg_lun *curlun, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	स्थिर माप_प्रकार len = min(count, माप(curlun->inquiry_string));

	अगर (len == 0 || buf[0] == '\n') अणु
		curlun->inquiry_string[0] = 0;
	पूर्ण अन्यथा अणु
		snम_लिखो(curlun->inquiry_string,
			 माप(curlun->inquiry_string), "%-28s", buf);
		अगर (curlun->inquiry_string[len-1] == '\n')
			curlun->inquiry_string[len-1] = ' ';
	पूर्ण

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_store_inquiry_string);

MODULE_LICENSE("GPL");
