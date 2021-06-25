<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश "bnad.h"

/*
 * BNA debufs पूर्णांकerface
 *
 * To access the पूर्णांकerface, debugfs file प्रणाली should be mounted
 * अगर not alपढ़ोy mounted using:
 *	mount -t debugfs none /sys/kernel/debug
 *
 * BNA Hierarchy:
 *	- bna/pci_dev:<pci_name>
 * where the pci_name corresponds to the one under /sys/bus/pci/drivers/bna
 *
 * Debugging service available per pci_dev:
 *	fwtrc:  To collect current firmware trace.
 *	fwsave: To collect last saved fw trace as a result of firmware crash.
 *	regwr:  To ग_लिखो one word to chip रेजिस्टर
 *	regrd:  To पढ़ो one or more words from chip रेजिस्टर.
 */

काष्ठा bnad_debug_info अणु
	अक्षर *debug_buffer;
	व्योम *i_निजी;
	पूर्णांक buffer_len;
पूर्ण;

अटल पूर्णांक
bnad_debugfs_खोलो_fwtrc(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bnad *bnad = inode->i_निजी;
	काष्ठा bnad_debug_info *fw_debug;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	fw_debug = kzalloc(माप(काष्ठा bnad_debug_info), GFP_KERNEL);
	अगर (!fw_debug)
		वापस -ENOMEM;

	fw_debug->buffer_len = BNA_DBG_FWTRC_LEN;

	fw_debug->debug_buffer = kzalloc(fw_debug->buffer_len, GFP_KERNEL);
	अगर (!fw_debug->debug_buffer) अणु
		kमुक्त(fw_debug);
		fw_debug = शून्य;
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&bnad->bna_lock, flags);
	rc = bfa_nw_ioc_debug_fwtrc(&bnad->bna.ioceth.ioc,
			fw_debug->debug_buffer,
			&fw_debug->buffer_len);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	अगर (rc != BFA_STATUS_OK) अणु
		kमुक्त(fw_debug->debug_buffer);
		fw_debug->debug_buffer = शून्य;
		kमुक्त(fw_debug);
		fw_debug = शून्य;
		netdev_warn(bnad->netdev, "failed to collect fwtrc\n");
		वापस -ENOMEM;
	पूर्ण

	file->निजी_data = fw_debug;

	वापस 0;
पूर्ण

अटल पूर्णांक
bnad_debugfs_खोलो_fwsave(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bnad *bnad = inode->i_निजी;
	काष्ठा bnad_debug_info *fw_debug;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	fw_debug = kzalloc(माप(काष्ठा bnad_debug_info), GFP_KERNEL);
	अगर (!fw_debug)
		वापस -ENOMEM;

	fw_debug->buffer_len = BNA_DBG_FWTRC_LEN;

	fw_debug->debug_buffer = kzalloc(fw_debug->buffer_len, GFP_KERNEL);
	अगर (!fw_debug->debug_buffer) अणु
		kमुक्त(fw_debug);
		fw_debug = शून्य;
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&bnad->bna_lock, flags);
	rc = bfa_nw_ioc_debug_fwsave(&bnad->bna.ioceth.ioc,
			fw_debug->debug_buffer,
			&fw_debug->buffer_len);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	अगर (rc != BFA_STATUS_OK && rc != BFA_STATUS_ENOFSAVE) अणु
		kमुक्त(fw_debug->debug_buffer);
		fw_debug->debug_buffer = शून्य;
		kमुक्त(fw_debug);
		fw_debug = शून्य;
		netdev_warn(bnad->netdev, "failed to collect fwsave\n");
		वापस -ENOMEM;
	पूर्ण

	file->निजी_data = fw_debug;

	वापस 0;
पूर्ण

अटल पूर्णांक
bnad_debugfs_खोलो_reg(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bnad_debug_info *reg_debug;

	reg_debug = kzalloc(माप(काष्ठा bnad_debug_info), GFP_KERNEL);
	अगर (!reg_debug)
		वापस -ENOMEM;

	reg_debug->i_निजी = inode->i_निजी;

	file->निजी_data = reg_debug;

	वापस 0;
पूर्ण

अटल पूर्णांक
bnad_get_debug_drvinfo(काष्ठा bnad *bnad, व्योम *buffer, u32 len)
अणु
	काष्ठा bnad_drvinfo *drvinfo = (काष्ठा bnad_drvinfo *) buffer;
	काष्ठा bnad_iocmd_comp fcomp;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret = BFA_STATUS_FAILED;

	/* Get IOC info */
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bfa_nw_ioc_get_attr(&bnad->bna.ioceth.ioc, &drvinfo->ioc_attr);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	/* Retrieve CEE related info */
	fcomp.bnad = bnad;
	fcomp.comp_status = 0;
	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	ret = bfa_nw_cee_get_attr(&bnad->bna.cee, &drvinfo->cee_attr,
				bnad_cb_completion, &fcomp);
	अगर (ret != BFA_STATUS_OK) अणु
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		जाओ out;
	पूर्ण
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	रुको_क्रम_completion(&fcomp.comp);
	drvinfo->cee_status = fcomp.comp_status;

	/* Retrieve flash partition info */
	fcomp.comp_status = 0;
	reinit_completion(&fcomp.comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	ret = bfa_nw_flash_get_attr(&bnad->bna.flash, &drvinfo->flash_attr,
				bnad_cb_completion, &fcomp);
	अगर (ret != BFA_STATUS_OK) अणु
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		जाओ out;
	पूर्ण
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	रुको_क्रम_completion(&fcomp.comp);
	drvinfo->flash_status = fcomp.comp_status;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक
bnad_debugfs_खोलो_drvinfo(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bnad *bnad = inode->i_निजी;
	काष्ठा bnad_debug_info *drv_info;
	पूर्णांक rc;

	drv_info = kzalloc(माप(काष्ठा bnad_debug_info), GFP_KERNEL);
	अगर (!drv_info)
		वापस -ENOMEM;

	drv_info->buffer_len = माप(काष्ठा bnad_drvinfo);

	drv_info->debug_buffer = kzalloc(drv_info->buffer_len, GFP_KERNEL);
	अगर (!drv_info->debug_buffer) अणु
		kमुक्त(drv_info);
		drv_info = शून्य;
		वापस -ENOMEM;
	पूर्ण

	mutex_lock(&bnad->conf_mutex);
	rc = bnad_get_debug_drvinfo(bnad, drv_info->debug_buffer,
				drv_info->buffer_len);
	mutex_unlock(&bnad->conf_mutex);
	अगर (rc != BFA_STATUS_OK) अणु
		kमुक्त(drv_info->debug_buffer);
		drv_info->debug_buffer = शून्य;
		kमुक्त(drv_info);
		drv_info = शून्य;
		netdev_warn(bnad->netdev, "failed to collect drvinfo\n");
		वापस -ENOMEM;
	पूर्ण

	file->निजी_data = drv_info;

	वापस 0;
पूर्ण

/* Changes the current file position */
अटल loff_t
bnad_debugfs_lseek(काष्ठा file *file, loff_t offset, पूर्णांक orig)
अणु
	काष्ठा bnad_debug_info *debug = file->निजी_data;

	अगर (!debug)
		वापस -EINVAL;

	वापस fixed_size_llseek(file, offset, orig, debug->buffer_len);
पूर्ण

अटल sमाप_प्रकार
bnad_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		  माप_प्रकार nbytes, loff_t *pos)
अणु
	काष्ठा bnad_debug_info *debug = file->निजी_data;

	अगर (!debug || !debug->debug_buffer)
		वापस 0;

	वापस simple_पढ़ो_from_buffer(buf, nbytes, pos,
				debug->debug_buffer, debug->buffer_len);
पूर्ण

#घोषणा BFA_REG_CT_ADDRSZ	(0x40000)
#घोषणा BFA_REG_CB_ADDRSZ	(0x20000)
#घोषणा BFA_REG_ADDRSZ(__ioc)	\
	((u32)(bfa_asic_id_ctc(bfa_ioc_devid(__ioc)) ?  \
	 BFA_REG_CT_ADDRSZ : BFA_REG_CB_ADDRSZ))
#घोषणा BFA_REG_ADDRMSK(__ioc)	(BFA_REG_ADDRSZ(__ioc) - 1)

/*
 * Function to check अगर the रेजिस्टर offset passed is valid.
 */
अटल पूर्णांक
bna_reg_offset_check(काष्ठा bfa_ioc *ioc, u32 offset, u32 len)
अणु
	u8 area;

	/* check [16:15] */
	area = (offset >> 15) & 0x7;
	अगर (area == 0) अणु
		/* PCIe core रेजिस्टर */
		अगर (offset + (len << 2) > 0x8000)	/* 8k dwords or 32KB */
			वापस BFA_STATUS_EINVAL;
	पूर्ण अन्यथा अगर (area == 0x1) अणु
		/* CB 32 KB memory page */
		अगर (offset + (len << 2) > 0x10000)	/* 8k dwords or 32KB */
			वापस BFA_STATUS_EINVAL;
	पूर्ण अन्यथा अणु
		/* CB रेजिस्टर space 64KB */
		अगर (offset + (len << 2) > BFA_REG_ADDRMSK(ioc))
			वापस BFA_STATUS_EINVAL;
	पूर्ण
	वापस BFA_STATUS_OK;
पूर्ण

अटल sमाप_प्रकार
bnad_debugfs_पढ़ो_regrd(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार nbytes, loff_t *pos)
अणु
	काष्ठा bnad_debug_info *regrd_debug = file->निजी_data;
	काष्ठा bnad *bnad = (काष्ठा bnad *)regrd_debug->i_निजी;
	sमाप_प्रकार rc;

	अगर (!bnad->regdata)
		वापस 0;

	rc = simple_पढ़ो_from_buffer(buf, nbytes, pos,
			bnad->regdata, bnad->reglen);

	अगर ((*pos + nbytes) >= bnad->reglen) अणु
		kमुक्त(bnad->regdata);
		bnad->regdata = शून्य;
		bnad->reglen = 0;
	पूर्ण

	वापस rc;
पूर्ण

अटल sमाप_प्रकार
bnad_debugfs_ग_लिखो_regrd(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा bnad_debug_info *regrd_debug = file->निजी_data;
	काष्ठा bnad *bnad = (काष्ठा bnad *)regrd_debug->i_निजी;
	काष्ठा bfa_ioc *ioc = &bnad->bna.ioceth.ioc;
	पूर्णांक rc, i;
	u32 addr, len;
	u32 *regbuf;
	व्योम __iomem *rb, *reg_addr;
	अचिन्हित दीर्घ flags;
	व्योम *kern_buf;

	/* Copy the user space buf */
	kern_buf = memdup_user(buf, nbytes);
	अगर (IS_ERR(kern_buf))
		वापस PTR_ERR(kern_buf);

	rc = माला_पूछो(kern_buf, "%x:%x", &addr, &len);
	अगर (rc < 2 || len > अच_पूर्णांक_उच्च >> 2) अणु
		netdev_warn(bnad->netdev, "failed to read user buffer\n");
		kमुक्त(kern_buf);
		वापस -EINVAL;
	पूर्ण

	kमुक्त(kern_buf);
	kमुक्त(bnad->regdata);
	bnad->reglen = 0;

	bnad->regdata = kzalloc(len << 2, GFP_KERNEL);
	अगर (!bnad->regdata)
		वापस -ENOMEM;

	bnad->reglen = len << 2;
	rb = bfa_ioc_bar0(ioc);
	addr &= BFA_REG_ADDRMSK(ioc);

	/* offset and len sanity check */
	rc = bna_reg_offset_check(ioc, addr, len);
	अगर (rc) अणु
		netdev_warn(bnad->netdev, "failed reg offset check\n");
		kमुक्त(bnad->regdata);
		bnad->regdata = शून्य;
		bnad->reglen = 0;
		वापस -EINVAL;
	पूर्ण

	reg_addr = rb + addr;
	regbuf =  (u32 *)bnad->regdata;
	spin_lock_irqsave(&bnad->bna_lock, flags);
	क्रम (i = 0; i < len; i++) अणु
		*regbuf = पढ़ोl(reg_addr);
		regbuf++;
		reg_addr += माप(u32);
	पूर्ण
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	वापस nbytes;
पूर्ण

अटल sमाप_प्रकार
bnad_debugfs_ग_लिखो_regwr(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा bnad_debug_info *debug = file->निजी_data;
	काष्ठा bnad *bnad = (काष्ठा bnad *)debug->i_निजी;
	काष्ठा bfa_ioc *ioc = &bnad->bna.ioceth.ioc;
	पूर्णांक rc;
	u32 addr, val;
	व्योम __iomem *reg_addr;
	अचिन्हित दीर्घ flags;
	व्योम *kern_buf;

	/* Copy the user space buf */
	kern_buf = memdup_user(buf, nbytes);
	अगर (IS_ERR(kern_buf))
		वापस PTR_ERR(kern_buf);

	rc = माला_पूछो(kern_buf, "%x:%x", &addr, &val);
	अगर (rc < 2) अणु
		netdev_warn(bnad->netdev, "failed to read user buffer\n");
		kमुक्त(kern_buf);
		वापस -EINVAL;
	पूर्ण
	kमुक्त(kern_buf);

	addr &= BFA_REG_ADDRMSK(ioc); /* offset only 17 bit and word align */

	/* offset and len sanity check */
	rc = bna_reg_offset_check(ioc, addr, 1);
	अगर (rc) अणु
		netdev_warn(bnad->netdev, "failed reg offset check\n");
		वापस -EINVAL;
	पूर्ण

	reg_addr = (bfa_ioc_bar0(ioc)) + addr;
	spin_lock_irqsave(&bnad->bna_lock, flags);
	ग_लिखोl(val, reg_addr);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	वापस nbytes;
पूर्ण

अटल पूर्णांक
bnad_debugfs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bnad_debug_info *debug = file->निजी_data;

	अगर (!debug)
		वापस 0;

	file->निजी_data = शून्य;
	kमुक्त(debug);
	वापस 0;
पूर्ण

अटल पूर्णांक
bnad_debugfs_buffer_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bnad_debug_info *debug = file->निजी_data;

	अगर (!debug)
		वापस 0;

	kमुक्त(debug->debug_buffer);

	file->निजी_data = शून्य;
	kमुक्त(debug);
	debug = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations bnad_debugfs_op_fwtrc = अणु
	.owner		=	THIS_MODULE,
	.खोलो		=	bnad_debugfs_खोलो_fwtrc,
	.llseek		=	bnad_debugfs_lseek,
	.पढ़ो		=	bnad_debugfs_पढ़ो,
	.release	=	bnad_debugfs_buffer_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations bnad_debugfs_op_fwsave = अणु
	.owner		=	THIS_MODULE,
	.खोलो		=	bnad_debugfs_खोलो_fwsave,
	.llseek		=	bnad_debugfs_lseek,
	.पढ़ो		=	bnad_debugfs_पढ़ो,
	.release	=	bnad_debugfs_buffer_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations bnad_debugfs_op_regrd = अणु
	.owner		=       THIS_MODULE,
	.खोलो		=	bnad_debugfs_खोलो_reg,
	.llseek		=	bnad_debugfs_lseek,
	.पढ़ो		=	bnad_debugfs_पढ़ो_regrd,
	.ग_लिखो		=	bnad_debugfs_ग_लिखो_regrd,
	.release	=	bnad_debugfs_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations bnad_debugfs_op_regwr = अणु
	.owner		=	THIS_MODULE,
	.खोलो		=	bnad_debugfs_खोलो_reg,
	.llseek		=	bnad_debugfs_lseek,
	.ग_लिखो		=	bnad_debugfs_ग_लिखो_regwr,
	.release	=	bnad_debugfs_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations bnad_debugfs_op_drvinfo = अणु
	.owner		=	THIS_MODULE,
	.खोलो		=	bnad_debugfs_खोलो_drvinfo,
	.llseek		=	bnad_debugfs_lseek,
	.पढ़ो		=	bnad_debugfs_पढ़ो,
	.release	=	bnad_debugfs_buffer_release,
पूर्ण;

काष्ठा bnad_debugfs_entry अणु
	स्थिर अक्षर *name;
	umode_t  mode;
	स्थिर काष्ठा file_operations *fops;
पूर्ण;

अटल स्थिर काष्ठा bnad_debugfs_entry bnad_debugfs_files[] = अणु
	अणु "fwtrc",  S_IFREG | 0444, &bnad_debugfs_op_fwtrc, पूर्ण,
	अणु "fwsave", S_IFREG | 0444, &bnad_debugfs_op_fwsave, पूर्ण,
	अणु "regrd",  S_IFREG | 0644, &bnad_debugfs_op_regrd, पूर्ण,
	अणु "regwr",  S_IFREG | 0200, &bnad_debugfs_op_regwr, पूर्ण,
	अणु "drvinfo", S_IFREG | 0444, &bnad_debugfs_op_drvinfo, पूर्ण,
पूर्ण;

अटल काष्ठा dentry *bna_debugfs_root;
अटल atomic_t bna_debugfs_port_count;

/* Initialize debugfs पूर्णांकerface क्रम BNA */
व्योम
bnad_debugfs_init(काष्ठा bnad *bnad)
अणु
	स्थिर काष्ठा bnad_debugfs_entry *file;
	अक्षर name[64];
	पूर्णांक i;

	/* Setup the BNA debugfs root directory*/
	अगर (!bna_debugfs_root) अणु
		bna_debugfs_root = debugfs_create_dir("bna", शून्य);
		atomic_set(&bna_debugfs_port_count, 0);
		अगर (!bna_debugfs_root) अणु
			netdev_warn(bnad->netdev,
				    "debugfs root dir creation failed\n");
			वापस;
		पूर्ण
	पूर्ण

	/* Setup the pci_dev debugfs directory क्रम the port */
	snम_लिखो(name, माप(name), "pci_dev:%s", pci_name(bnad->pcidev));
	अगर (!bnad->port_debugfs_root) अणु
		bnad->port_debugfs_root =
			debugfs_create_dir(name, bna_debugfs_root);
		अगर (!bnad->port_debugfs_root) अणु
			netdev_warn(bnad->netdev,
				    "debugfs root dir creation failed\n");
			वापस;
		पूर्ण

		atomic_inc(&bna_debugfs_port_count);

		क्रम (i = 0; i < ARRAY_SIZE(bnad_debugfs_files); i++) अणु
			file = &bnad_debugfs_files[i];
			bnad->bnad_dentry_files[i] =
					debugfs_create_file(file->name,
							file->mode,
							bnad->port_debugfs_root,
							bnad,
							file->fops);
			अगर (!bnad->bnad_dentry_files[i]) अणु
				netdev_warn(bnad->netdev,
					    "create %s entry failed\n",
					    file->name);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Uninitialize debugfs पूर्णांकerface क्रम BNA */
व्योम
bnad_debugfs_uninit(काष्ठा bnad *bnad)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bnad_debugfs_files); i++) अणु
		अगर (bnad->bnad_dentry_files[i]) अणु
			debugfs_हटाओ(bnad->bnad_dentry_files[i]);
			bnad->bnad_dentry_files[i] = शून्य;
		पूर्ण
	पूर्ण

	/* Remove the pci_dev debugfs directory क्रम the port */
	अगर (bnad->port_debugfs_root) अणु
		debugfs_हटाओ(bnad->port_debugfs_root);
		bnad->port_debugfs_root = शून्य;
		atomic_dec(&bna_debugfs_port_count);
	पूर्ण

	/* Remove the BNA debugfs root directory */
	अगर (atomic_पढ़ो(&bna_debugfs_port_count) == 0) अणु
		debugfs_हटाओ(bna_debugfs_root);
		bna_debugfs_root = शून्य;
	पूर्ण
पूर्ण
