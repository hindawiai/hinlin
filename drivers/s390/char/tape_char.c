<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    अक्षरacter device frontend क्रम tape device driver
 *
 *  S390 and zSeries version
 *    Copyright IBM Corp. 2001, 2006
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *		 Michael Holzheu <holzheu@de.ibm.com>
 *		 Tuan Ngo-Anh <ngoanh@de.ibm.com>
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "tape"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mtपन.स>
#समावेश <linux/compat.h>

#समावेश <linux/uaccess.h>

#घोषणा TAPE_DBF_AREA	tape_core_dbf

#समावेश "tape.h"
#समावेश "tape_std.h"
#समावेश "tape_class.h"

#घोषणा TAPECHAR_MAJOR		0	/* get dynamic major */

/*
 * file operation काष्ठाure क्रम tape अक्षरacter frontend
 */
अटल sमाप_प्रकार tapeअक्षर_पढ़ो(काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
अटल sमाप_प्रकार tapeअक्षर_ग_लिखो(काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
अटल पूर्णांक tapeअक्षर_खोलो(काष्ठा inode *,काष्ठा file *);
अटल पूर्णांक tapeअक्षर_release(काष्ठा inode *,काष्ठा file *);
अटल दीर्घ tapeअक्षर_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ tapeअक्षर_compat_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations tape_fops =
अणु
	.owner = THIS_MODULE,
	.पढ़ो = tapeअक्षर_पढ़ो,
	.ग_लिखो = tapeअक्षर_ग_लिखो,
	.unlocked_ioctl = tapeअक्षर_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = tapeअक्षर_compat_ioctl,
#पूर्ण_अगर
	.खोलो = tapeअक्षर_खोलो,
	.release = tapeअक्षर_release,
	.llseek = no_llseek,
पूर्ण;

अटल पूर्णांक tapeअक्षर_major = TAPECHAR_MAJOR;

/*
 * This function is called क्रम every new tapedevice
 */
पूर्णांक
tapeअक्षर_setup_device(काष्ठा tape_device * device)
अणु
	अक्षर	device_name[20];

	प्र_लिखो(device_name, "ntibm%i", device->first_minor / 2);
	device->nt = रेजिस्टर_tape_dev(
		&device->cdev->dev,
		MKDEV(tapeअक्षर_major, device->first_minor),
		&tape_fops,
		device_name,
		"non-rewinding"
	);
	device_name[0] = 'r';
	device->rt = रेजिस्टर_tape_dev(
		&device->cdev->dev,
		MKDEV(tapeअक्षर_major, device->first_minor + 1),
		&tape_fops,
		device_name,
		"rewinding"
	);

	वापस 0;
पूर्ण

व्योम
tapeअक्षर_cleanup_device(काष्ठा tape_device *device)
अणु
	unरेजिस्टर_tape_dev(&device->cdev->dev, device->rt);
	device->rt = शून्य;
	unरेजिस्टर_tape_dev(&device->cdev->dev, device->nt);
	device->nt = शून्य;
पूर्ण

अटल पूर्णांक
tapeअक्षर_check_idalbuffer(काष्ठा tape_device *device, माप_प्रकार block_size)
अणु
	काष्ठा idal_buffer *new;

	अगर (device->अक्षर_data.idal_buf != शून्य &&
	    device->अक्षर_data.idal_buf->size == block_size)
		वापस 0;

	अगर (block_size > MAX_BLOCKSIZE) अणु
		DBF_EVENT(3, "Invalid blocksize (%zd > %d)\n",
			block_size, MAX_BLOCKSIZE);
		वापस -EINVAL;
	पूर्ण

	/* The current idal buffer is not correct. Allocate a new one. */
	new = idal_buffer_alloc(block_size, 0);
	अगर (IS_ERR(new))
		वापस -ENOMEM;

	अगर (device->अक्षर_data.idal_buf != शून्य)
		idal_buffer_मुक्त(device->अक्षर_data.idal_buf);

	device->अक्षर_data.idal_buf = new;

	वापस 0;
पूर्ण

/*
 * Tape device पढ़ो function
 */
अटल sमाप_प्रकार
tapeअक्षर_पढ़ो(काष्ठा file *filp, अक्षर __user *data, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा tape_device *device;
	काष्ठा tape_request *request;
	माप_प्रकार block_size;
	पूर्णांक rc;

	DBF_EVENT(6, "TCHAR:read\n");
	device = (काष्ठा tape_device *) filp->निजी_data;

	/*
	 * If the tape isn't terminated yet, करो it now. And since we then
	 * are at the end of the tape there wouldn't be anything to पढ़ो
	 * anyways. So we वापस immediately.
	 */
	अगर(device->required_tapemarks) अणु
		वापस tape_std_terminate_ग_लिखो(device);
	पूर्ण

	/* Find out block size to use */
	अगर (device->अक्षर_data.block_size != 0) अणु
		अगर (count < device->अक्षर_data.block_size) अणु
			DBF_EVENT(3, "TCHAR:read smaller than block "
				  "size was requested\n");
			वापस -EINVAL;
		पूर्ण
		block_size = device->अक्षर_data.block_size;
	पूर्ण अन्यथा अणु
		block_size = count;
	पूर्ण

	rc = tapeअक्षर_check_idalbuffer(device, block_size);
	अगर (rc)
		वापस rc;

	DBF_EVENT(6, "TCHAR:nbytes: %lx\n", block_size);
	/* Let the discipline build the ccw chain. */
	request = device->discipline->पढ़ो_block(device, block_size);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	/* Execute it. */
	rc = tape_करो_io(device, request);
	अगर (rc == 0) अणु
		rc = block_size - request->rescnt;
		DBF_EVENT(6, "TCHAR:rbytes:  %x\n", rc);
		/* Copy data from idal buffer to user space. */
		अगर (idal_buffer_to_user(device->अक्षर_data.idal_buf,
					data, rc) != 0)
			rc = -EFAULT;
	पूर्ण
	tape_मुक्त_request(request);
	वापस rc;
पूर्ण

/*
 * Tape device ग_लिखो function
 */
अटल sमाप_प्रकार
tapeअक्षर_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *data, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा tape_device *device;
	काष्ठा tape_request *request;
	माप_प्रकार block_size;
	माप_प्रकार written;
	पूर्णांक nblocks;
	पूर्णांक i, rc;

	DBF_EVENT(6, "TCHAR:write\n");
	device = (काष्ठा tape_device *) filp->निजी_data;
	/* Find out block size and number of blocks */
	अगर (device->अक्षर_data.block_size != 0) अणु
		अगर (count < device->अक्षर_data.block_size) अणु
			DBF_EVENT(3, "TCHAR:write smaller than block "
				  "size was requested\n");
			वापस -EINVAL;
		पूर्ण
		block_size = device->अक्षर_data.block_size;
		nblocks = count / block_size;
	पूर्ण अन्यथा अणु
		block_size = count;
		nblocks = 1;
	पूर्ण

	rc = tapeअक्षर_check_idalbuffer(device, block_size);
	अगर (rc)
		वापस rc;

	DBF_EVENT(6,"TCHAR:nbytes: %lx\n", block_size);
	DBF_EVENT(6, "TCHAR:nblocks: %x\n", nblocks);
	/* Let the discipline build the ccw chain. */
	request = device->discipline->ग_लिखो_block(device, block_size);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	rc = 0;
	written = 0;
	क्रम (i = 0; i < nblocks; i++) अणु
		/* Copy data from user space to idal buffer. */
		अगर (idal_buffer_from_user(device->अक्षर_data.idal_buf,
					  data, block_size)) अणु
			rc = -EFAULT;
			अवरोध;
		पूर्ण
		rc = tape_करो_io(device, request);
		अगर (rc)
			अवरोध;
		DBF_EVENT(6, "TCHAR:wbytes: %lx\n",
			  block_size - request->rescnt);
		written += block_size - request->rescnt;
		अगर (request->rescnt != 0)
			अवरोध;
		data += block_size;
	पूर्ण
	tape_मुक्त_request(request);
	अगर (rc == -ENOSPC) अणु
		/*
		 * Ok, the device has no more space. It has NOT written
		 * the block.
		 */
		अगर (device->discipline->process_eov)
			device->discipline->process_eov(device);
		अगर (written > 0)
			rc = 0;

	पूर्ण

	/*
	 * After करोing a ग_लिखो we always need two tapemarks to correctly
	 * terminate the tape (one to terminate the file, the second to
	 * flag the end of recorded data.
	 * Since process_eov positions the tape in front of the written
	 * tapemark it करोesn't hurt to ग_लिखो two marks again.
	 */
	अगर (!rc)
		device->required_tapemarks = 2;

	वापस rc ? rc : written;
पूर्ण

/*
 * Character frontend tape device खोलो function.
 */
अटल पूर्णांक
tapeअक्षर_खोलो (काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा tape_device *device;
	पूर्णांक minor, rc;

	DBF_EVENT(6, "TCHAR:open: %i:%i\n",
		imajor(file_inode(filp)),
		iminor(file_inode(filp)));

	अगर (imajor(file_inode(filp)) != tapeअक्षर_major)
		वापस -ENODEV;

	minor = iminor(file_inode(filp));
	device = tape_find_device(minor / TAPE_MINORS_PER_DEV);
	अगर (IS_ERR(device)) अणु
		DBF_EVENT(3, "TCHAR:open: tape_find_device() failed\n");
		वापस PTR_ERR(device);
	पूर्ण

	rc = tape_खोलो(device);
	अगर (rc == 0) अणु
		filp->निजी_data = device;
		stream_खोलो(inode, filp);
	पूर्ण अन्यथा
		tape_put_device(device);

	वापस rc;
पूर्ण

/*
 * Character frontend tape device release function.
 */

अटल पूर्णांक
tapeअक्षर_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा tape_device *device;

	DBF_EVENT(6, "TCHAR:release: %x\n", iminor(inode));
	device = (काष्ठा tape_device *) filp->निजी_data;

	/*
	 * If this is the शुरुआतing tape minor then शुरुआत. In that हाल we
	 * ग_लिखो all required tapemarks. Otherwise only one to terminate the
	 * file.
	 */
	अगर ((iminor(inode) & 1) != 0) अणु
		अगर (device->required_tapemarks)
			tape_std_terminate_ग_लिखो(device);
		tape_mtop(device, MTREW, 1);
	पूर्ण अन्यथा अणु
		अगर (device->required_tapemarks > 1) अणु
			अगर (tape_mtop(device, MTWखातापूर्ण, 1) == 0)
				device->required_tapemarks--;
		पूर्ण
	पूर्ण

	अगर (device->अक्षर_data.idal_buf != शून्य) अणु
		idal_buffer_मुक्त(device->अक्षर_data.idal_buf);
		device->अक्षर_data.idal_buf = शून्य;
	पूर्ण
	tape_release(device);
	filp->निजी_data = शून्य;
	tape_put_device(device);

	वापस 0;
पूर्ण

/*
 * Tape device io controls.
 */
अटल पूर्णांक
__tapeअक्षर_ioctl(काष्ठा tape_device *device,
		 अचिन्हित पूर्णांक no, व्योम __user *data)
अणु
	पूर्णांक rc;

	अगर (no == MTIOCTOP) अणु
		काष्ठा mtop op;

		अगर (copy_from_user(&op, data, माप(op)) != 0)
			वापस -EFAULT;
		अगर (op.mt_count < 0)
			वापस -EINVAL;

		/*
		 * Operations that change tape position should ग_लिखो final
		 * tapemarks.
		 */
		चयन (op.mt_op) अणु
			हाल MTFSF:
			हाल MTBSF:
			हाल MTFSR:
			हाल MTBSR:
			हाल MTREW:
			हाल MTOFFL:
			हाल MTEOM:
			हाल MTRETEN:
			हाल MTBSFM:
			हाल MTFSFM:
			हाल MTSEEK:
				अगर (device->required_tapemarks)
					tape_std_terminate_ग_लिखो(device);
			शेष:
				;
		पूर्ण
		rc = tape_mtop(device, op.mt_op, op.mt_count);

		अगर (op.mt_op == MTWखातापूर्ण && rc == 0) अणु
			अगर (op.mt_count > device->required_tapemarks)
				device->required_tapemarks = 0;
			अन्यथा
				device->required_tapemarks -= op.mt_count;
		पूर्ण
		वापस rc;
	पूर्ण
	अगर (no == MTIOCPOS) अणु
		/* MTIOCPOS: query the tape position. */
		काष्ठा mtpos pos;

		rc = tape_mtop(device, MTTELL, 1);
		अगर (rc < 0)
			वापस rc;
		pos.mt_blkno = rc;
		वापस put_user_mtpos(data, &pos);
	पूर्ण
	अगर (no == MTIOCGET) अणु
		/* MTIOCGET: query the tape drive status. */
		काष्ठा mtget get;

		स_रखो(&get, 0, माप(get));
		get.mt_type = MT_ISUNKNOWN;
		get.mt_resid = 0 /* device->devstat.rescnt */;
		get.mt_dsreg =
			((device->अक्षर_data.block_size << MT_ST_BLKSIZE_SHIFT)
			 & MT_ST_BLKSIZE_MASK);
		/* FIXME: mt_gstat, mt_erreg, mt_fileno */
		get.mt_gstat = 0;
		get.mt_erreg = 0;
		get.mt_fileno = 0;
		get.mt_gstat  = device->tape_generic_status;

		अगर (device->medium_state == MS_LOADED) अणु
			rc = tape_mtop(device, MTTELL, 1);

			अगर (rc < 0)
				वापस rc;

			अगर (rc == 0)
				get.mt_gstat |= GMT_BOT(~0);

			get.mt_blkno = rc;
		पूर्ण

		वापस put_user_mtget(data, &get);
	पूर्ण
	/* Try the discipline ioctl function. */
	अगर (device->discipline->ioctl_fn == शून्य)
		वापस -EINVAL;
	वापस device->discipline->ioctl_fn(device, no, (अचिन्हित दीर्घ)data);
पूर्ण

अटल दीर्घ
tapeअक्षर_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक no, अचिन्हित दीर्घ data)
अणु
	काष्ठा tape_device *device;
	दीर्घ rc;

	DBF_EVENT(6, "TCHAR:ioct\n");

	device = (काष्ठा tape_device *) filp->निजी_data;
	mutex_lock(&device->mutex);
	rc = __tapeअक्षर_ioctl(device, no, (व्योम __user *)data);
	mutex_unlock(&device->mutex);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ
tapeअक्षर_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक no, अचिन्हित दीर्घ data)
अणु
	काष्ठा tape_device *device = filp->निजी_data;
	दीर्घ rc;

	अगर (no == MTIOCPOS32)
		no = MTIOCPOS;
	अन्यथा अगर (no == MTIOCGET32)
		no = MTIOCGET;

	mutex_lock(&device->mutex);
	rc = __tapeअक्षर_ioctl(device, no, compat_ptr(data));
	mutex_unlock(&device->mutex);
	वापस rc;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

/*
 * Initialize अक्षरacter device frontend.
 */
पूर्णांक
tapeअक्षर_init (व्योम)
अणु
	dev_t	dev;

	अगर (alloc_chrdev_region(&dev, 0, 256, "tape") != 0)
		वापस -1;

	tapeअक्षर_major = MAJOR(dev);

	वापस 0;
पूर्ण

/*
 * cleanup
 */
व्योम
tapeअक्षर_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev_region(MKDEV(tapeअक्षर_major, 0), 256);
पूर्ण
