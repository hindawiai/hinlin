<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Debugfs पूर्णांकerface Support क्रम MPT (Message Passing Technology) based
 * controllers.
 *
 * Copyright (C) 2020  Broadcom Inc.
 *
 * Authors: Broadcom Inc.
 * Sreekanth Reddy  <sreekanth.reddy@broadcom.com>
 * Suganath Prabu <suganath-prabu.subramani@broadcom.com>
 *
 * Send feedback to : MPT-FusionLinux.pdl@broadcom.com)
 *
 **/

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/compat.h>
#समावेश <linux/uपन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश "mpt3sas_base.h"
#समावेश <linux/debugfs.h>

अटल काष्ठा dentry *mpt3sas_debugfs_root;

/*
 * _debugfs_iocdump_पढ़ो - copy ioc dump from debugfs buffer
 * @filep:	File Poपूर्णांकer
 * @ubuf:	Buffer to fill data
 * @cnt:	Length of the buffer
 * @ppos:	Offset in the file
 */

अटल sमाप_प्रकार
_debugfs_iocdump_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf, माप_प्रकार cnt,
	loff_t *ppos)

अणु
	काष्ठा mpt3sas_debugfs_buffer *debug = filp->निजी_data;

	अगर (!debug || !debug->buf)
		वापस 0;

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, debug->buf, debug->len);
पूर्ण

/*
 * _debugfs_iocdump_खोलो :	खोलो the ioc_dump debugfs attribute file
 */
अटल पूर्णांक
_debugfs_iocdump_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = inode->i_निजी;
	काष्ठा mpt3sas_debugfs_buffer *debug;

	debug = kzalloc(माप(काष्ठा mpt3sas_debugfs_buffer), GFP_KERNEL);
	अगर (!debug)
		वापस -ENOMEM;

	debug->buf = (व्योम *)ioc;
	debug->len = माप(काष्ठा MPT3SAS_ADAPTER);
	file->निजी_data = debug;
	वापस 0;
पूर्ण

/*
 * _debugfs_iocdump_release :	release the ioc_dump debugfs attribute
 * @inode: inode काष्ठाure to the corresponds device
 * @file: File poपूर्णांकer
 */
अटल पूर्णांक
_debugfs_iocdump_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mpt3sas_debugfs_buffer *debug = file->निजी_data;

	अगर (!debug)
		वापस 0;

	file->निजी_data = शून्य;
	kमुक्त(debug);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations mpt3sas_debugfs_iocdump_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = _debugfs_iocdump_खोलो,
	.पढ़ो           = _debugfs_iocdump_पढ़ो,
	.release        = _debugfs_iocdump_release,
पूर्ण;

/*
 * mpt3sas_init_debugfs :	Create debugfs root क्रम mpt3sas driver
 */
व्योम mpt3sas_init_debugfs(व्योम)
अणु
	mpt3sas_debugfs_root = debugfs_create_dir("mpt3sas", शून्य);
	अगर (!mpt3sas_debugfs_root)
		pr_info("mpt3sas: Cannot create debugfs root\n");
पूर्ण

/*
 * mpt3sas_निकास_debugfs :	Remove debugfs root क्रम mpt3sas driver
 */
व्योम mpt3sas_निकास_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(mpt3sas_debugfs_root);
पूर्ण

/*
 * mpt3sas_setup_debugfs :	Setup debugfs per HBA adapter
 * ioc:				MPT3SAS_ADAPTER object
 */
व्योम
mpt3sas_setup_debugfs(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	अक्षर name[64];

	snम_लिखो(name, माप(name), "scsi_host%d", ioc->shost->host_no);
	अगर (!ioc->debugfs_root) अणु
		ioc->debugfs_root =
		    debugfs_create_dir(name, mpt3sas_debugfs_root);
		अगर (!ioc->debugfs_root) अणु
			dev_err(&ioc->pdev->dev,
			    "Cannot create per adapter debugfs directory\n");
			वापस;
		पूर्ण
	पूर्ण

	snम_लिखो(name, माप(name), "ioc_dump");
	ioc->ioc_dump =	debugfs_create_file(name, 0444,
	    ioc->debugfs_root, ioc, &mpt3sas_debugfs_iocdump_fops);
	अगर (!ioc->ioc_dump) अणु
		dev_err(&ioc->pdev->dev,
		    "Cannot create ioc_dump debugfs file\n");
		debugfs_हटाओ(ioc->debugfs_root);
		वापस;
	पूर्ण

	snम_लिखो(name, माप(name), "host_recovery");
	debugfs_create_u8(name, 0444, ioc->debugfs_root, &ioc->shost_recovery);

पूर्ण

/*
 * mpt3sas_destroy_debugfs :	Destroy debugfs per HBA adapter
 * @ioc:	MPT3SAS_ADAPTER object
 */
व्योम mpt3sas_destroy_debugfs(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	debugfs_हटाओ_recursive(ioc->debugfs_root);
पूर्ण

