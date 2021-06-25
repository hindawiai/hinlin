<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * VAS user space API क्रम its accelerators (Only NX-GZIP is supported now)
 * Copyright (C) 2019 Haren Myneni, IBM Corp
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/vas.h>
#समावेश <uapi/यंत्र/vas-api.h>
#समावेश "vas.h"

/*
 * The driver creates the device node that can be used as follows:
 * For NX-GZIP
 *
 *	fd = खोलो("/dev/crypto/nx-gzip", O_RDWR);
 *	rc = ioctl(fd, VAS_TX_WIN_OPEN, &attr);
 *	paste_addr = mmap(शून्य, PAGE_SIZE, prot, MAP_SHARED, fd, 0ULL).
 *	vas_copy(&crb, 0, 1);
 *	vas_paste(paste_addr, 0, 1);
 *	बंद(fd) or निकास process to बंद winकरोw.
 *
 * where "vas_copy" and "vas_paste" are defined in copy-paste.h.
 * copy/paste वापसs to the user space directly. So refer NX hardware
 * करोcumententation क्रम exact copy/paste usage and completion / error
 * conditions.
 */

/*
 * Wrapper object क्रम the nx-gzip device - there is just one instance of
 * this node क्रम the whole प्रणाली.
 */
अटल काष्ठा coproc_dev अणु
	काष्ठा cdev cdev;
	काष्ठा device *device;
	अक्षर *name;
	dev_t devt;
	काष्ठा class *class;
	क्रमागत vas_cop_type cop_type;
पूर्ण coproc_device;

काष्ठा coproc_instance अणु
	काष्ठा coproc_dev *coproc;
	काष्ठा vas_winकरोw *txwin;
पूर्ण;

अटल अक्षर *coproc_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "crypto/%s", dev_name(dev));
पूर्ण

अटल पूर्णांक coproc_खोलो(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	काष्ठा coproc_instance *cp_inst;

	cp_inst = kzalloc(माप(*cp_inst), GFP_KERNEL);
	अगर (!cp_inst)
		वापस -ENOMEM;

	cp_inst->coproc = container_of(inode->i_cdev, काष्ठा coproc_dev,
					cdev);
	fp->निजी_data = cp_inst;

	वापस 0;
पूर्ण

अटल पूर्णांक coproc_ioc_tx_win_खोलो(काष्ठा file *fp, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *uptr = (व्योम __user *)arg;
	काष्ठा vas_tx_win_attr txattr = अणुपूर्ण;
	काष्ठा vas_tx_win_खोलो_attr uattr;
	काष्ठा coproc_instance *cp_inst;
	काष्ठा vas_winकरोw *txwin;
	पूर्णांक rc, vasid;

	cp_inst = fp->निजी_data;

	/*
	 * One winकरोw क्रम file descriptor
	 */
	अगर (cp_inst->txwin)
		वापस -EEXIST;

	rc = copy_from_user(&uattr, uptr, माप(uattr));
	अगर (rc) अणु
		pr_err("%s(): copy_from_user() returns %d\n", __func__, rc);
		वापस -EFAULT;
	पूर्ण

	अगर (uattr.version != 1) अणु
		pr_err("Invalid version\n");
		वापस -EINVAL;
	पूर्ण

	vasid = uattr.vas_id;

	vas_init_tx_win_attr(&txattr, cp_inst->coproc->cop_type);

	txattr.lpid = mfspr(SPRN_LPID);
	txattr.pidr = mfspr(SPRN_PID);
	txattr.user_win = true;
	txattr.rsvd_txbuf_count = false;
	txattr.pswid = false;

	pr_devel("Pid %d: Opening txwin, PIDR %ld\n", txattr.pidr,
				mfspr(SPRN_PID));

	txwin = vas_tx_win_खोलो(vasid, cp_inst->coproc->cop_type, &txattr);
	अगर (IS_ERR(txwin)) अणु
		pr_err("%s() vas_tx_win_open() failed, %ld\n", __func__,
					PTR_ERR(txwin));
		वापस PTR_ERR(txwin);
	पूर्ण

	cp_inst->txwin = txwin;

	वापस 0;
पूर्ण

अटल पूर्णांक coproc_release(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	काष्ठा coproc_instance *cp_inst = fp->निजी_data;

	अगर (cp_inst->txwin) अणु
		vas_win_बंद(cp_inst->txwin);
		cp_inst->txwin = शून्य;
	पूर्ण

	kमुक्त(cp_inst);
	fp->निजी_data = शून्य;

	/*
	 * We करोn't know here अगर user has other receive winकरोws
	 * खोलो, so we can't really call clear_thपढ़ो_tidr().
	 * So, once the process calls set_thपढ़ो_tidr(), the
	 * TIDR value sticks around until process निकासs, resulting
	 * in an extra copy in restore_sprs().
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक coproc_mmap(काष्ठा file *fp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा coproc_instance *cp_inst = fp->निजी_data;
	काष्ठा vas_winकरोw *txwin;
	अचिन्हित दीर्घ pfn;
	u64 paste_addr;
	pgprot_t prot;
	पूर्णांक rc;

	txwin = cp_inst->txwin;

	अगर ((vma->vm_end - vma->vm_start) > PAGE_SIZE) अणु
		pr_debug("%s(): size 0x%zx, PAGE_SIZE 0x%zx\n", __func__,
				(vma->vm_end - vma->vm_start), PAGE_SIZE);
		वापस -EINVAL;
	पूर्ण

	/* Ensure instance has an खोलो send winकरोw */
	अगर (!txwin) अणु
		pr_err("%s(): No send window open?\n", __func__);
		वापस -EINVAL;
	पूर्ण

	vas_win_paste_addr(txwin, &paste_addr, शून्य);
	pfn = paste_addr >> PAGE_SHIFT;

	/* flags, page_prot from cxl_mmap(), except we want cachable */
	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_cached(vma->vm_page_prot);

	prot = __pgprot(pgprot_val(vma->vm_page_prot) | _PAGE_सूचीTY);

	rc = remap_pfn_range(vma, vma->vm_start, pfn + vma->vm_pgoff,
			vma->vm_end - vma->vm_start, prot);

	pr_devel("%s(): paste addr %llx at %lx, rc %d\n", __func__,
			paste_addr, vma->vm_start, rc);

	वापस rc;
पूर्ण

अटल दीर्घ coproc_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल VAS_TX_WIN_OPEN:
		वापस coproc_ioc_tx_win_खोलो(fp, arg);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा file_operations coproc_fops = अणु
	.खोलो = coproc_खोलो,
	.release = coproc_release,
	.mmap = coproc_mmap,
	.unlocked_ioctl = coproc_ioctl,
पूर्ण;

/*
 * Supporting only nx-gzip coprocessor type now, but this API code
 * extended to other coprocessor types later.
 */
पूर्णांक vas_रेजिस्टर_coproc_api(काष्ठा module *mod, क्रमागत vas_cop_type cop_type,
				स्थिर अक्षर *name)
अणु
	पूर्णांक rc = -EINVAL;
	dev_t devno;

	rc = alloc_chrdev_region(&coproc_device.devt, 1, 1, name);
	अगर (rc) अणु
		pr_err("Unable to allocate coproc major number: %i\n", rc);
		वापस rc;
	पूर्ण

	pr_devel("%s device allocated, dev [%i,%i]\n", name,
			MAJOR(coproc_device.devt), MINOR(coproc_device.devt));

	coproc_device.class = class_create(mod, name);
	अगर (IS_ERR(coproc_device.class)) अणु
		rc = PTR_ERR(coproc_device.class);
		pr_err("Unable to create %s class %d\n", name, rc);
		जाओ err_class;
	पूर्ण
	coproc_device.class->devnode = coproc_devnode;
	coproc_device.cop_type = cop_type;

	coproc_fops.owner = mod;
	cdev_init(&coproc_device.cdev, &coproc_fops);

	devno = MKDEV(MAJOR(coproc_device.devt), 0);
	rc = cdev_add(&coproc_device.cdev, devno, 1);
	अगर (rc) अणु
		pr_err("cdev_add() failed %d\n", rc);
		जाओ err_cdev;
	पूर्ण

	coproc_device.device = device_create(coproc_device.class, शून्य,
			devno, शून्य, name, MINOR(devno));
	अगर (IS_ERR(coproc_device.device)) अणु
		rc = PTR_ERR(coproc_device.device);
		pr_err("Unable to create coproc-%d %d\n", MINOR(devno), rc);
		जाओ err;
	पूर्ण

	pr_devel("%s: Added dev [%d,%d]\n", __func__, MAJOR(devno),
			MINOR(devno));

	वापस 0;

err:
	cdev_del(&coproc_device.cdev);
err_cdev:
	class_destroy(coproc_device.class);
err_class:
	unरेजिस्टर_chrdev_region(coproc_device.devt, 1);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(vas_रेजिस्टर_coproc_api);

व्योम vas_unरेजिस्टर_coproc_api(व्योम)
अणु
	dev_t devno;

	cdev_del(&coproc_device.cdev);
	devno = MKDEV(MAJOR(coproc_device.devt), 0);
	device_destroy(coproc_device.class, devno);

	class_destroy(coproc_device.class);
	unरेजिस्टर_chrdev_region(coproc_device.devt, 1);
पूर्ण
EXPORT_SYMBOL_GPL(vas_unरेजिस्टर_coproc_api);
