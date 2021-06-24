<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  c 2001 PPC 64 Team, IBM Corp
 *
 * /proc/घातerpc/rtas/firmware_flash पूर्णांकerface
 *
 * This file implements a firmware_flash पूर्णांकerface to pump a firmware
 * image पूर्णांकo the kernel.  At reboot समय rtas_restart() will see the
 * firmware image and flash it as it reboots (see rtas.c).
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/reboot.h>
#समावेश <यंत्र/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/rtas.h>

#घोषणा MODULE_VERS "1.0"
#घोषणा MODULE_NAME "rtas_flash"

#घोषणा FIRMWARE_FLASH_NAME "firmware_flash"   
#घोषणा FIRMWARE_UPDATE_NAME "firmware_update"
#घोषणा MANAGE_FLASH_NAME "manage_flash"
#घोषणा VALIDATE_FLASH_NAME "validate_flash"

/* General RTAS Status Codes */
#घोषणा RTAS_RC_SUCCESS  0
#घोषणा RTAS_RC_HW_ERR	-1
#घोषणा RTAS_RC_BUSY	-2

/* Flash image status values */
#घोषणा FLASH_AUTH           -9002 /* RTAS Not Service Authority Partition */
#घोषणा FLASH_NO_OP          -1099 /* No operation initiated by user */	
#घोषणा FLASH_IMG_SHORT	     -1005 /* Flash image लघुer than expected */
#घोषणा FLASH_IMG_BAD_LEN    -1004 /* Bad length value in flash list block */
#घोषणा FLASH_IMG_शून्य_DATA  -1003 /* Bad data value in flash list block */
#घोषणा FLASH_IMG_READY      0     /* Firmware img पढ़ोy क्रम flash on reboot */

/* Manage image status values */
#घोषणा MANAGE_AUTH          -9002 /* RTAS Not Service Authority Partition */
#घोषणा MANAGE_ACTIVE_ERR    -9001 /* RTAS Cannot Overग_लिखो Active Img */
#घोषणा MANAGE_NO_OP         -1099 /* No operation initiated by user */
#घोषणा MANAGE_PARAM_ERR     -3    /* RTAS Parameter Error */
#घोषणा MANAGE_HW_ERR        -1    /* RTAS Hardware Error */

/* Validate image status values */
#घोषणा VALIDATE_AUTH          -9002 /* RTAS Not Service Authority Partition */
#घोषणा VALIDATE_NO_OP         -1099 /* No operation initiated by the user */
#घोषणा VALIDATE_INCOMPLETE    -1002 /* User copied < VALIDATE_BUF_SIZE */
#घोषणा VALIDATE_READY	       -1001 /* Firmware image पढ़ोy क्रम validation */
#घोषणा VALIDATE_PARAM_ERR     -3    /* RTAS Parameter Error */
#घोषणा VALIDATE_HW_ERR        -1    /* RTAS Hardware Error */

/* ibm,validate-flash-image update result tokens */
#घोषणा VALIDATE_TMP_UPDATE    0     /* T side will be updated */
#घोषणा VALIDATE_FLASH_AUTH    1     /* Partition करोes not have authority */
#घोषणा VALIDATE_INVALID_IMG   2     /* Candidate image is not valid */
#घोषणा VALIDATE_CUR_UNKNOWN   3     /* Current fixpack level is unknown */
/*
 * Current T side will be committed to P side beक्रमe being replace with new
 * image, and the new image is करोwnlevel from current image
 */
#घोषणा VALIDATE_TMP_COMMIT_DL 4
/*
 * Current T side will be committed to P side beक्रमe being replaced with new
 * image
 */
#घोषणा VALIDATE_TMP_COMMIT    5
/*
 * T side will be updated with a करोwnlevel image
 */
#घोषणा VALIDATE_TMP_UPDATE_DL 6
/*
 * The candidate image's release date is later than the system's firmware
 * service entitlement date - service warranty period has expired
 */
#घोषणा VALIDATE_OUT_OF_WRNTY  7

/* ibm,manage-flash-image operation tokens */
#घोषणा RTAS_REJECT_TMP_IMG   0
#घोषणा RTAS_COMMIT_TMP_IMG   1

/* Array sizes */
#घोषणा VALIDATE_BUF_SIZE 4096    
#घोषणा VALIDATE_MSG_LEN  256
#घोषणा RTAS_MSG_MAXLEN   64

/* Quirk - RTAS requires 4k list length and block size */
#घोषणा RTAS_BLKLIST_LENGTH 4096
#घोषणा RTAS_BLK_SIZE 4096

काष्ठा flash_block अणु
	अक्षर *data;
	अचिन्हित दीर्घ length;
पूर्ण;

/* This काष्ठा is very similar but not identical to
 * that needed by the rtas flash update.
 * All we need to करो क्रम rtas is reग_लिखो num_blocks
 * पूर्णांकo a version/length and translate the poपूर्णांकers
 * to असलolute.
 */
#घोषणा FLASH_BLOCKS_PER_NODE ((RTAS_BLKLIST_LENGTH - 16) / माप(काष्ठा flash_block))
काष्ठा flash_block_list अणु
	अचिन्हित दीर्घ num_blocks;
	काष्ठा flash_block_list *next;
	काष्ठा flash_block blocks[FLASH_BLOCKS_PER_NODE];
पूर्ण;

अटल काष्ठा flash_block_list *rtas_firmware_flash_list;

/* Use slab cache to guarantee 4k alignment */
अटल काष्ठा kmem_cache *flash_block_cache = शून्य;

#घोषणा FLASH_BLOCK_LIST_VERSION (1UL)

/*
 * Local copy of the flash block list.
 *
 * The rtas_firmware_flash_list varable will be
 * set once the data is fully पढ़ो.
 *
 * For convenience as we build the list we use भव addrs,
 * we करो not fill in the version number, and the length field
 * is treated as the number of entries currently in the block
 * (i.e. not a byte count).  This is all fixed when calling 
 * the flash routine.
 */

/* Status पूर्णांक must be first member of काष्ठा */
काष्ठा rtas_update_flash_t
अणु
	पूर्णांक status;			/* Flash update status */
	काष्ठा flash_block_list *flist; /* Local copy of flash block list */
पूर्ण;

/* Status पूर्णांक must be first member of काष्ठा */
काष्ठा rtas_manage_flash_t
अणु
	पूर्णांक status;			/* Returned status */
पूर्ण;

/* Status पूर्णांक must be first member of काष्ठा */
काष्ठा rtas_validate_flash_t
अणु
	पूर्णांक status;		 	/* Returned status */	
	अक्षर *buf;			/* Candidate image buffer */
	अचिन्हित पूर्णांक buf_size;		/* Size of image buf */
	अचिन्हित पूर्णांक update_results;	/* Update results token */
पूर्ण;

अटल काष्ठा rtas_update_flash_t rtas_update_flash_data;
अटल काष्ठा rtas_manage_flash_t rtas_manage_flash_data;
अटल काष्ठा rtas_validate_flash_t rtas_validate_flash_data;
अटल DEFINE_MUTEX(rtas_update_flash_mutex);
अटल DEFINE_MUTEX(rtas_manage_flash_mutex);
अटल DEFINE_MUTEX(rtas_validate_flash_mutex);

/* Do simple sanity checks on the flash image. */
अटल पूर्णांक flash_list_valid(काष्ठा flash_block_list *flist)
अणु
	काष्ठा flash_block_list *f;
	पूर्णांक i;
	अचिन्हित दीर्घ block_size, image_size;

	/* Paranoid self test here.  We also collect the image size. */
	image_size = 0;
	क्रम (f = flist; f; f = f->next) अणु
		क्रम (i = 0; i < f->num_blocks; i++) अणु
			अगर (f->blocks[i].data == शून्य) अणु
				वापस FLASH_IMG_शून्य_DATA;
			पूर्ण
			block_size = f->blocks[i].length;
			अगर (block_size <= 0 || block_size > RTAS_BLK_SIZE) अणु
				वापस FLASH_IMG_BAD_LEN;
			पूर्ण
			image_size += block_size;
		पूर्ण
	पूर्ण

	अगर (image_size < (256 << 10)) अणु
		अगर (image_size < 2) 
			वापस FLASH_NO_OP;
	पूर्ण

	prपूर्णांकk(KERN_INFO "FLASH: flash image with %ld bytes stored for hardware flash on reboot\n", image_size);

	वापस FLASH_IMG_READY;
पूर्ण

अटल व्योम मुक्त_flash_list(काष्ठा flash_block_list *f)
अणु
	काष्ठा flash_block_list *next;
	पूर्णांक i;

	जबतक (f) अणु
		क्रम (i = 0; i < f->num_blocks; i++)
			kmem_cache_मुक्त(flash_block_cache, f->blocks[i].data);
		next = f->next;
		kmem_cache_मुक्त(flash_block_cache, f);
		f = next;
	पूर्ण
पूर्ण

अटल पूर्णांक rtas_flash_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा rtas_update_flash_t *स्थिर uf = &rtas_update_flash_data;

	mutex_lock(&rtas_update_flash_mutex);

	अगर (uf->flist) अणु    
		/* File was खोलोed in ग_लिखो mode क्रम a new flash attempt */
		/* Clear saved list */
		अगर (rtas_firmware_flash_list) अणु
			मुक्त_flash_list(rtas_firmware_flash_list);
			rtas_firmware_flash_list = शून्य;
		पूर्ण

		अगर (uf->status != FLASH_AUTH)  
			uf->status = flash_list_valid(uf->flist);

		अगर (uf->status == FLASH_IMG_READY) 
			rtas_firmware_flash_list = uf->flist;
		अन्यथा
			मुक्त_flash_list(uf->flist);

		uf->flist = शून्य;
	पूर्ण

	mutex_unlock(&rtas_update_flash_mutex);
	वापस 0;
पूर्ण

अटल माप_प्रकार get_flash_status_msg(पूर्णांक status, अक्षर *buf)
अणु
	स्थिर अक्षर *msg;
	माप_प्रकार len;

	चयन (status) अणु
	हाल FLASH_AUTH:
		msg = "error: this partition does not have service authority\n";
		अवरोध;
	हाल FLASH_NO_OP:
		msg = "info: no firmware image for flash\n";
		अवरोध;
	हाल FLASH_IMG_SHORT:
		msg = "error: flash image short\n";
		अवरोध;
	हाल FLASH_IMG_BAD_LEN:
		msg = "error: internal error bad length\n";
		अवरोध;
	हाल FLASH_IMG_शून्य_DATA:
		msg = "error: internal error null data\n";
		अवरोध;
	हाल FLASH_IMG_READY:
		msg = "ready: firmware image ready for flash on reboot\n";
		अवरोध;
	शेष:
		वापस प्र_लिखो(buf, "error: unexpected status value %d\n",
			       status);
	पूर्ण

	len = म_माप(msg);
	स_नकल(buf, msg, len + 1);
	वापस len;
पूर्ण

/* Reading the proc file will show status (not the firmware contents) */
अटल sमाप_प्रकार rtas_flash_पढ़ो_msg(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rtas_update_flash_t *स्थिर uf = &rtas_update_flash_data;
	अक्षर msg[RTAS_MSG_MAXLEN];
	माप_प्रकार len;
	पूर्णांक status;

	mutex_lock(&rtas_update_flash_mutex);
	status = uf->status;
	mutex_unlock(&rtas_update_flash_mutex);

	/* Read as text message */
	len = get_flash_status_msg(status, msg);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, msg, len);
पूर्ण

अटल sमाप_प्रकार rtas_flash_पढ़ो_num(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rtas_update_flash_t *स्थिर uf = &rtas_update_flash_data;
	अक्षर msg[RTAS_MSG_MAXLEN];
	पूर्णांक status;

	mutex_lock(&rtas_update_flash_mutex);
	status = uf->status;
	mutex_unlock(&rtas_update_flash_mutex);

	/* Read as number */
	प्र_लिखो(msg, "%d\n", status);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, msg, म_माप(msg));
पूर्ण

/* We could be much more efficient here.  But to keep this function
 * simple we allocate a page to the block list no matter how small the
 * count is.  If the प्रणाली is low on memory it will be just as well
 * that we fail....
 */
अटल sमाप_प्रकार rtas_flash_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				माप_प्रकार count, loff_t *off)
अणु
	काष्ठा rtas_update_flash_t *स्थिर uf = &rtas_update_flash_data;
	अक्षर *p;
	पूर्णांक next_मुक्त, rc;
	काष्ठा flash_block_list *fl;

	mutex_lock(&rtas_update_flash_mutex);

	अगर (uf->status == FLASH_AUTH || count == 0)
		जाओ out;	/* discard data */

	/* In the हाल that the image is not पढ़ोy क्रम flashing, the memory
	 * allocated क्रम the block list will be मुक्तd upon the release of the 
	 * proc file
	 */
	अगर (uf->flist == शून्य) अणु
		uf->flist = kmem_cache_zalloc(flash_block_cache, GFP_KERNEL);
		अगर (!uf->flist)
			जाओ nomem;
	पूर्ण

	fl = uf->flist;
	जबतक (fl->next)
		fl = fl->next; /* seek to last block_list क्रम append */
	next_मुक्त = fl->num_blocks;
	अगर (next_मुक्त == FLASH_BLOCKS_PER_NODE) अणु
		/* Need to allocate another block_list */
		fl->next = kmem_cache_zalloc(flash_block_cache, GFP_KERNEL);
		अगर (!fl->next)
			जाओ nomem;
		fl = fl->next;
		next_मुक्त = 0;
	पूर्ण

	अगर (count > RTAS_BLK_SIZE)
		count = RTAS_BLK_SIZE;
	p = kmem_cache_zalloc(flash_block_cache, GFP_KERNEL);
	अगर (!p)
		जाओ nomem;
	
	अगर(copy_from_user(p, buffer, count)) अणु
		kmem_cache_मुक्त(flash_block_cache, p);
		rc = -EFAULT;
		जाओ error;
	पूर्ण
	fl->blocks[next_मुक्त].data = p;
	fl->blocks[next_मुक्त].length = count;
	fl->num_blocks++;
out:
	mutex_unlock(&rtas_update_flash_mutex);
	वापस count;

nomem:
	rc = -ENOMEM;
error:
	mutex_unlock(&rtas_update_flash_mutex);
	वापस rc;
पूर्ण

/*
 * Flash management routines.
 */
अटल व्योम manage_flash(काष्ठा rtas_manage_flash_t *args_buf, अचिन्हित पूर्णांक op)
अणु
	s32 rc;

	करो अणु
		rc = rtas_call(rtas_token("ibm,manage-flash-image"), 1, 1,
			       शून्य, op);
	पूर्ण जबतक (rtas_busy_delay(rc));

	args_buf->status = rc;
पूर्ण

अटल sमाप_प्रकार manage_flash_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rtas_manage_flash_t *स्थिर args_buf = &rtas_manage_flash_data;
	अक्षर msg[RTAS_MSG_MAXLEN];
	पूर्णांक msglen, status;

	mutex_lock(&rtas_manage_flash_mutex);
	status = args_buf->status;
	mutex_unlock(&rtas_manage_flash_mutex);

	msglen = प्र_लिखो(msg, "%d\n", status);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, msg, msglen);
पूर्ण

अटल sमाप_प्रकार manage_flash_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *off)
अणु
	काष्ठा rtas_manage_flash_t *स्थिर args_buf = &rtas_manage_flash_data;
	अटल स्थिर अक्षर reject_str[] = "0";
	अटल स्थिर अक्षर commit_str[] = "1";
	अक्षर stkbuf[10];
	पूर्णांक op, rc;

	mutex_lock(&rtas_manage_flash_mutex);

	अगर ((args_buf->status == MANAGE_AUTH) || (count == 0))
		जाओ out;
		
	op = -1;
	अगर (buf) अणु
		अगर (count > 9) count = 9;
		rc = -EFAULT;
		अगर (copy_from_user (stkbuf, buf, count))
			जाओ error;
		अगर (म_भेदन(stkbuf, reject_str, म_माप(reject_str)) == 0) 
			op = RTAS_REJECT_TMP_IMG;
		अन्यथा अगर (म_भेदन(stkbuf, commit_str, म_माप(commit_str)) == 0) 
			op = RTAS_COMMIT_TMP_IMG;
	पूर्ण
	
	अगर (op == -1) अणु   /* buf is empty, or contains invalid string */
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	manage_flash(args_buf, op);
out:
	mutex_unlock(&rtas_manage_flash_mutex);
	वापस count;

error:
	mutex_unlock(&rtas_manage_flash_mutex);
	वापस rc;
पूर्ण

/*
 * Validation routines.
 */
अटल व्योम validate_flash(काष्ठा rtas_validate_flash_t *args_buf)
अणु
	पूर्णांक token = rtas_token("ibm,validate-flash-image");
	पूर्णांक update_results;
	s32 rc;	

	rc = 0;
	करो अणु
		spin_lock(&rtas_data_buf_lock);
		स_नकल(rtas_data_buf, args_buf->buf, VALIDATE_BUF_SIZE);
		rc = rtas_call(token, 2, 2, &update_results, 
			       (u32) __pa(rtas_data_buf), args_buf->buf_size);
		स_नकल(args_buf->buf, rtas_data_buf, VALIDATE_BUF_SIZE);
		spin_unlock(&rtas_data_buf_lock);
	पूर्ण जबतक (rtas_busy_delay(rc));

	args_buf->status = rc;
	args_buf->update_results = update_results;
पूर्ण

अटल पूर्णांक get_validate_flash_msg(काष्ठा rtas_validate_flash_t *args_buf, 
		                   अक्षर *msg, पूर्णांक msglen)
अणु
	पूर्णांक n;

	अगर (args_buf->status >= VALIDATE_TMP_UPDATE) अणु 
		n = प्र_लिखो(msg, "%d\n", args_buf->update_results);
		अगर ((args_buf->update_results >= VALIDATE_CUR_UNKNOWN) ||
		    (args_buf->update_results == VALIDATE_TMP_UPDATE))
			n += snम_लिखो(msg + n, msglen - n, "%s\n",
					args_buf->buf);
	पूर्ण अन्यथा अणु
		n = प्र_लिखो(msg, "%d\n", args_buf->status);
	पूर्ण
	वापस n;
पूर्ण

अटल sमाप_प्रकार validate_flash_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा rtas_validate_flash_t *स्थिर args_buf =
		&rtas_validate_flash_data;
	अक्षर msg[VALIDATE_MSG_LEN];
	पूर्णांक msglen;

	mutex_lock(&rtas_validate_flash_mutex);
	msglen = get_validate_flash_msg(args_buf, msg, VALIDATE_MSG_LEN);
	mutex_unlock(&rtas_validate_flash_mutex);

	वापस simple_पढ़ो_from_buffer(buf, count, ppos, msg, msglen);
पूर्ण

अटल sमाप_प्रकार validate_flash_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				    माप_प्रकार count, loff_t *off)
अणु
	काष्ठा rtas_validate_flash_t *स्थिर args_buf =
		&rtas_validate_flash_data;
	पूर्णांक rc;

	mutex_lock(&rtas_validate_flash_mutex);

	/* We are only पूर्णांकerested in the first 4K of the
	 * candidate image */
	अगर ((*off >= VALIDATE_BUF_SIZE) || 
		(args_buf->status == VALIDATE_AUTH)) अणु
		*off += count;
		mutex_unlock(&rtas_validate_flash_mutex);
		वापस count;
	पूर्ण

	अगर (*off + count >= VALIDATE_BUF_SIZE)  अणु
		count = VALIDATE_BUF_SIZE - *off;
		args_buf->status = VALIDATE_READY;	
	पूर्ण अन्यथा अणु
		args_buf->status = VALIDATE_INCOMPLETE;
	पूर्ण

	अगर (!access_ok(buf, count)) अणु
		rc = -EFAULT;
		जाओ करोne;
	पूर्ण
	अगर (copy_from_user(args_buf->buf + *off, buf, count)) अणु
		rc = -EFAULT;
		जाओ करोne;
	पूर्ण

	*off += count;
	rc = count;
करोne:
	mutex_unlock(&rtas_validate_flash_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक validate_flash_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा rtas_validate_flash_t *स्थिर args_buf =
		&rtas_validate_flash_data;

	mutex_lock(&rtas_validate_flash_mutex);

	अगर (args_buf->status == VALIDATE_READY) अणु
		args_buf->buf_size = VALIDATE_BUF_SIZE;
		validate_flash(args_buf);
	पूर्ण

	mutex_unlock(&rtas_validate_flash_mutex);
	वापस 0;
पूर्ण

/*
 * On-reboot flash update applicator.
 */
अटल व्योम rtas_flash_firmware(पूर्णांक reboot_type)
अणु
	अचिन्हित दीर्घ image_size;
	काष्ठा flash_block_list *f, *next, *flist;
	अचिन्हित दीर्घ rtas_block_list;
	पूर्णांक i, status, update_token;

	अगर (rtas_firmware_flash_list == शून्य)
		वापस;		/* nothing to करो */

	अगर (reboot_type != SYS_RESTART) अणु
		prपूर्णांकk(KERN_ALERT "FLASH: firmware flash requires a reboot\n");
		prपूर्णांकk(KERN_ALERT "FLASH: the firmware image will NOT be flashed\n");
		वापस;
	पूर्ण

	update_token = rtas_token("ibm,update-flash-64-and-reboot");
	अगर (update_token == RTAS_UNKNOWN_SERVICE) अणु
		prपूर्णांकk(KERN_ALERT "FLASH: ibm,update-flash-64-and-reboot "
		       "is not available -- not a service partition?\n");
		prपूर्णांकk(KERN_ALERT "FLASH: firmware will not be flashed\n");
		वापस;
	पूर्ण

	/*
	 * Just beक्रमe starting the firmware flash, cancel the event scan work
	 * to aव्योम any soft lockup issues.
	 */
	rtas_cancel_event_scan();

	/*
	 * NOTE: the "first" block must be under 4GB, so we create
	 * an entry with no data blocks in the reserved buffer in
	 * the kernel data segment.
	 */
	spin_lock(&rtas_data_buf_lock);
	flist = (काष्ठा flash_block_list *)&rtas_data_buf[0];
	flist->num_blocks = 0;
	flist->next = rtas_firmware_flash_list;
	rtas_block_list = __pa(flist);
	अगर (rtas_block_list >= 4UL*1024*1024*1024) अणु
		prपूर्णांकk(KERN_ALERT "FLASH: kernel bug...flash list header addr above 4GB\n");
		spin_unlock(&rtas_data_buf_lock);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_ALERT "FLASH: preparing saved firmware image for flash\n");
	/* Update the block_list in place. */
	rtas_firmware_flash_list = शून्य; /* too hard to backout on error */
	image_size = 0;
	क्रम (f = flist; f; f = next) अणु
		/* Translate data addrs to असलolute */
		क्रम (i = 0; i < f->num_blocks; i++) अणु
			f->blocks[i].data = (अक्षर *)cpu_to_be64(__pa(f->blocks[i].data));
			image_size += f->blocks[i].length;
			f->blocks[i].length = cpu_to_be64(f->blocks[i].length);
		पूर्ण
		next = f->next;
		/* Don't translate शून्य poपूर्णांकer क्रम last entry */
		अगर (f->next)
			f->next = (काष्ठा flash_block_list *)cpu_to_be64(__pa(f->next));
		अन्यथा
			f->next = शून्य;
		/* make num_blocks पूर्णांकo the version/length field */
		f->num_blocks = (FLASH_BLOCK_LIST_VERSION << 56) | ((f->num_blocks+1)*16);
		f->num_blocks = cpu_to_be64(f->num_blocks);
	पूर्ण

	prपूर्णांकk(KERN_ALERT "FLASH: flash image is %ld bytes\n", image_size);
	prपूर्णांकk(KERN_ALERT "FLASH: performing flash and reboot\n");
	rtas_progress("Flashing        \n", 0x0);
	rtas_progress("Please Wait...  ", 0x0);
	prपूर्णांकk(KERN_ALERT "FLASH: this will take several minutes.  Do not power off!\n");
	status = rtas_call(update_token, 1, 1, शून्य, rtas_block_list);
	चयन (status) अणु	/* should only get "bad" status */
	    हाल 0:
		prपूर्णांकk(KERN_ALERT "FLASH: success\n");
		अवरोध;
	    हाल -1:
		prपूर्णांकk(KERN_ALERT "FLASH: hardware error.  Firmware may not be not flashed\n");
		अवरोध;
	    हाल -3:
		prपूर्णांकk(KERN_ALERT "FLASH: image is corrupt or not correct for this platform.  Firmware not flashed\n");
		अवरोध;
	    हाल -4:
		prपूर्णांकk(KERN_ALERT "FLASH: flash failed when partially complete.  System may not reboot\n");
		अवरोध;
	    शेष:
		prपूर्णांकk(KERN_ALERT "FLASH: unknown flash return code %d\n", status);
		अवरोध;
	पूर्ण
	spin_unlock(&rtas_data_buf_lock);
पूर्ण

/*
 * Manअगरest of proc files to create
 */
काष्ठा rtas_flash_file अणु
	स्थिर अक्षर *filename;
	स्थिर अक्षर *rtas_call_name;
	पूर्णांक *status;
	स्थिर काष्ठा proc_ops ops;
पूर्ण;

अटल स्थिर काष्ठा rtas_flash_file rtas_flash_files[] = अणु
	अणु
		.filename	= "powerpc/rtas/" FIRMWARE_FLASH_NAME,
		.rtas_call_name	= "ibm,update-flash-64-and-reboot",
		.status		= &rtas_update_flash_data.status,
		.ops.proc_पढ़ो	= rtas_flash_पढ़ो_msg,
		.ops.proc_ग_लिखो	= rtas_flash_ग_लिखो,
		.ops.proc_release = rtas_flash_release,
		.ops.proc_lseek	= शेष_llseek,
	पूर्ण,
	अणु
		.filename	= "powerpc/rtas/" FIRMWARE_UPDATE_NAME,
		.rtas_call_name	= "ibm,update-flash-64-and-reboot",
		.status		= &rtas_update_flash_data.status,
		.ops.proc_पढ़ो	= rtas_flash_पढ़ो_num,
		.ops.proc_ग_लिखो	= rtas_flash_ग_लिखो,
		.ops.proc_release = rtas_flash_release,
		.ops.proc_lseek	= शेष_llseek,
	पूर्ण,
	अणु
		.filename	= "powerpc/rtas/" VALIDATE_FLASH_NAME,
		.rtas_call_name	= "ibm,validate-flash-image",
		.status		= &rtas_validate_flash_data.status,
		.ops.proc_पढ़ो	= validate_flash_पढ़ो,
		.ops.proc_ग_लिखो	= validate_flash_ग_लिखो,
		.ops.proc_release = validate_flash_release,
		.ops.proc_lseek	= शेष_llseek,
	पूर्ण,
	अणु
		.filename	= "powerpc/rtas/" MANAGE_FLASH_NAME,
		.rtas_call_name	= "ibm,manage-flash-image",
		.status		= &rtas_manage_flash_data.status,
		.ops.proc_पढ़ो	= manage_flash_पढ़ो,
		.ops.proc_ग_लिखो	= manage_flash_ग_लिखो,
		.ops.proc_lseek	= शेष_llseek,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init rtas_flash_init(व्योम)
अणु
	पूर्णांक i;

	अगर (rtas_token("ibm,update-flash-64-and-reboot") ==
		       RTAS_UNKNOWN_SERVICE) अणु
		pr_info("rtas_flash: no firmware flash support\n");
		वापस -EINVAL;
	पूर्ण

	rtas_validate_flash_data.buf = kzalloc(VALIDATE_BUF_SIZE, GFP_KERNEL);
	अगर (!rtas_validate_flash_data.buf)
		वापस -ENOMEM;

	flash_block_cache = kmem_cache_create("rtas_flash_cache",
					      RTAS_BLK_SIZE, RTAS_BLK_SIZE, 0,
					      शून्य);
	अगर (!flash_block_cache) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to create block cache\n",
				__func__);
		जाओ enomem_buf;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(rtas_flash_files); i++) अणु
		स्थिर काष्ठा rtas_flash_file *f = &rtas_flash_files[i];
		पूर्णांक token;

		अगर (!proc_create(f->filename, 0600, शून्य, &f->ops))
			जाओ enomem;

		/*
		 * This code assumes that the status पूर्णांक is the first member of the
		 * काष्ठा
		 */
		token = rtas_token(f->rtas_call_name);
		अगर (token == RTAS_UNKNOWN_SERVICE)
			*f->status = FLASH_AUTH;
		अन्यथा
			*f->status = FLASH_NO_OP;
	पूर्ण

	rtas_flash_term_hook = rtas_flash_firmware;
	वापस 0;

enomem:
	जबतक (--i >= 0) अणु
		स्थिर काष्ठा rtas_flash_file *f = &rtas_flash_files[i];
		हटाओ_proc_entry(f->filename, शून्य);
	पूर्ण

	kmem_cache_destroy(flash_block_cache);
enomem_buf:
	kमुक्त(rtas_validate_flash_data.buf);
	वापस -ENOMEM;
पूर्ण

अटल व्योम __निकास rtas_flash_cleanup(व्योम)
अणु
	पूर्णांक i;

	rtas_flash_term_hook = शून्य;

	अगर (rtas_firmware_flash_list) अणु
		मुक्त_flash_list(rtas_firmware_flash_list);
		rtas_firmware_flash_list = शून्य;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(rtas_flash_files); i++) अणु
		स्थिर काष्ठा rtas_flash_file *f = &rtas_flash_files[i];
		हटाओ_proc_entry(f->filename, शून्य);
	पूर्ण

	kmem_cache_destroy(flash_block_cache);
	kमुक्त(rtas_validate_flash_data.buf);
पूर्ण

module_init(rtas_flash_init);
module_निकास(rtas_flash_cleanup);
MODULE_LICENSE("GPL");
