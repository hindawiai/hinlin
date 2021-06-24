<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>

#समावेश "bfad_drv.h"
#समावेश "bfad_im.h"

/*
 * BFA debufs पूर्णांकerface
 *
 * To access the पूर्णांकerface, debugfs file प्रणाली should be mounted
 * अगर not alपढ़ोy mounted using:
 * mount -t debugfs none /sys/kernel/debug
 *
 * BFA Hierarchy:
 *	- bfa/pci_dev:<pci_name>
 * where the pci_name corresponds to the one under /sys/bus/pci/drivers/bfa
 *
 * Debugging service available per pci_dev:
 * fwtrc:  To collect current firmware trace.
 * drvtrc: To collect current driver trace
 * fwsave: To collect last saved fw trace as a result of firmware crash.
 * regwr:  To ग_लिखो one word to chip रेजिस्टर
 * regrd:  To पढ़ो one or more words from chip रेजिस्टर.
 */

काष्ठा bfad_debug_info अणु
	अक्षर *debug_buffer;
	व्योम *i_निजी;
	पूर्णांक buffer_len;
पूर्ण;

अटल पूर्णांक
bfad_debugfs_खोलो_drvtrc(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bfad_port_s *port = inode->i_निजी;
	काष्ठा bfad_s *bfad = port->bfad;
	काष्ठा bfad_debug_info *debug;

	debug = kzalloc(माप(काष्ठा bfad_debug_info), GFP_KERNEL);
	अगर (!debug)
		वापस -ENOMEM;

	debug->debug_buffer = (व्योम *) bfad->trcmod;
	debug->buffer_len = माप(काष्ठा bfa_trc_mod_s);

	file->निजी_data = debug;

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_debugfs_खोलो_fwtrc(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bfad_port_s *port = inode->i_निजी;
	काष्ठा bfad_s *bfad = port->bfad;
	काष्ठा bfad_debug_info *fw_debug;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	fw_debug = kzalloc(माप(काष्ठा bfad_debug_info), GFP_KERNEL);
	अगर (!fw_debug)
		वापस -ENOMEM;

	fw_debug->buffer_len = माप(काष्ठा bfa_trc_mod_s);

	fw_debug->debug_buffer = vzalloc(fw_debug->buffer_len);
	अगर (!fw_debug->debug_buffer) अणु
		kमुक्त(fw_debug);
		prपूर्णांकk(KERN_INFO "bfad[%d]: Failed to allocate fwtrc buffer\n",
				bfad->inst_no);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	rc = bfa_ioc_debug_fwtrc(&bfad->bfa.ioc,
			fw_debug->debug_buffer,
			&fw_debug->buffer_len);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (rc != BFA_STATUS_OK) अणु
		vमुक्त(fw_debug->debug_buffer);
		fw_debug->debug_buffer = शून्य;
		kमुक्त(fw_debug);
		prपूर्णांकk(KERN_INFO "bfad[%d]: Failed to collect fwtrc\n",
				bfad->inst_no);
		वापस -ENOMEM;
	पूर्ण

	file->निजी_data = fw_debug;

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_debugfs_खोलो_fwsave(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bfad_port_s *port = inode->i_निजी;
	काष्ठा bfad_s *bfad = port->bfad;
	काष्ठा bfad_debug_info *fw_debug;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	fw_debug = kzalloc(माप(काष्ठा bfad_debug_info), GFP_KERNEL);
	अगर (!fw_debug)
		वापस -ENOMEM;

	fw_debug->buffer_len = माप(काष्ठा bfa_trc_mod_s);

	fw_debug->debug_buffer = vzalloc(fw_debug->buffer_len);
	अगर (!fw_debug->debug_buffer) अणु
		kमुक्त(fw_debug);
		prपूर्णांकk(KERN_INFO "bfad[%d]: Failed to allocate fwsave buffer\n",
				bfad->inst_no);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	rc = bfa_ioc_debug_fwsave(&bfad->bfa.ioc,
			fw_debug->debug_buffer,
			&fw_debug->buffer_len);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (rc != BFA_STATUS_OK) अणु
		vमुक्त(fw_debug->debug_buffer);
		fw_debug->debug_buffer = शून्य;
		kमुक्त(fw_debug);
		prपूर्णांकk(KERN_INFO "bfad[%d]: Failed to collect fwsave\n",
				bfad->inst_no);
		वापस -ENOMEM;
	पूर्ण

	file->निजी_data = fw_debug;

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_debugfs_खोलो_reg(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bfad_debug_info *reg_debug;

	reg_debug = kzalloc(माप(काष्ठा bfad_debug_info), GFP_KERNEL);
	अगर (!reg_debug)
		वापस -ENOMEM;

	reg_debug->i_निजी = inode->i_निजी;

	file->निजी_data = reg_debug;

	वापस 0;
पूर्ण

/* Changes the current file position */
अटल loff_t
bfad_debugfs_lseek(काष्ठा file *file, loff_t offset, पूर्णांक orig)
अणु
	काष्ठा bfad_debug_info *debug = file->निजी_data;
	वापस fixed_size_llseek(file, offset, orig,
				debug->buffer_len);
पूर्ण

अटल sमाप_प्रकार
bfad_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार nbytes, loff_t *pos)
अणु
	काष्ठा bfad_debug_info *debug = file->निजी_data;

	अगर (!debug || !debug->debug_buffer)
		वापस 0;

	वापस simple_पढ़ो_from_buffer(buf, nbytes, pos,
				debug->debug_buffer, debug->buffer_len);
पूर्ण

#घोषणा BFA_REG_CT_ADDRSZ	(0x40000)
#घोषणा BFA_REG_CB_ADDRSZ	(0x20000)
#घोषणा BFA_REG_ADDRSZ(__ioc)	\
	((u32)(bfa_asic_id_ctc(bfa_ioc_devid(__ioc)) ?	\
	 BFA_REG_CT_ADDRSZ : BFA_REG_CB_ADDRSZ))
#घोषणा BFA_REG_ADDRMSK(__ioc)	(BFA_REG_ADDRSZ(__ioc) - 1)

अटल bfa_status_t
bfad_reg_offset_check(काष्ठा bfa_s *bfa, u32 offset, u32 len)
अणु
	u8	area;

	/* check [16:15] */
	area = (offset >> 15) & 0x7;
	अगर (area == 0) अणु
		/* PCIe core रेजिस्टर */
		अगर ((offset + (len<<2)) > 0x8000)    /* 8k dwords or 32KB */
			वापस BFA_STATUS_EINVAL;
	पूर्ण अन्यथा अगर (area == 0x1) अणु
		/* CB 32 KB memory page */
		अगर ((offset + (len<<2)) > 0x10000)    /* 8k dwords or 32KB */
			वापस BFA_STATUS_EINVAL;
	पूर्ण अन्यथा अणु
		/* CB रेजिस्टर space 64KB */
		अगर ((offset + (len<<2)) > BFA_REG_ADDRMSK(&bfa->ioc))
			वापस BFA_STATUS_EINVAL;
	पूर्ण
	वापस BFA_STATUS_OK;
पूर्ण

अटल sमाप_प्रकार
bfad_debugfs_पढ़ो_regrd(काष्ठा file *file, अक्षर __user *buf,
		माप_प्रकार nbytes, loff_t *pos)
अणु
	काष्ठा bfad_debug_info *regrd_debug = file->निजी_data;
	काष्ठा bfad_port_s *port = (काष्ठा bfad_port_s *)regrd_debug->i_निजी;
	काष्ठा bfad_s *bfad = port->bfad;
	sमाप_प्रकार rc;

	अगर (!bfad->regdata)
		वापस 0;

	rc = simple_पढ़ो_from_buffer(buf, nbytes, pos,
			bfad->regdata, bfad->reglen);

	अगर ((*pos + nbytes) >= bfad->reglen) अणु
		kमुक्त(bfad->regdata);
		bfad->regdata = शून्य;
		bfad->reglen = 0;
	पूर्ण

	वापस rc;
पूर्ण

अटल sमाप_प्रकार
bfad_debugfs_ग_लिखो_regrd(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा bfad_debug_info *regrd_debug = file->निजी_data;
	काष्ठा bfad_port_s *port = (काष्ठा bfad_port_s *)regrd_debug->i_निजी;
	काष्ठा bfad_s *bfad = port->bfad;
	काष्ठा bfa_s *bfa = &bfad->bfa;
	काष्ठा bfa_ioc_s *ioc = &bfa->ioc;
	पूर्णांक addr, rc, i;
	u32 len;
	u32 *regbuf;
	व्योम __iomem *rb, *reg_addr;
	अचिन्हित दीर्घ flags;
	व्योम *kern_buf;

	kern_buf = memdup_user(buf, nbytes);
	अगर (IS_ERR(kern_buf))
		वापस PTR_ERR(kern_buf);

	rc = माला_पूछो(kern_buf, "%x:%x", &addr, &len);
	अगर (rc < 2 || len > (अच_पूर्णांक_उच्च >> 2)) अणु
		prपूर्णांकk(KERN_INFO
			"bfad[%d]: %s failed to read user buf\n",
			bfad->inst_no, __func__);
		kमुक्त(kern_buf);
		वापस -EINVAL;
	पूर्ण

	kमुक्त(kern_buf);
	kमुक्त(bfad->regdata);
	bfad->regdata = शून्य;
	bfad->reglen = 0;

	bfad->regdata = kzalloc(len << 2, GFP_KERNEL);
	अगर (!bfad->regdata) अणु
		prपूर्णांकk(KERN_INFO "bfad[%d]: Failed to allocate regrd buffer\n",
				bfad->inst_no);
		वापस -ENOMEM;
	पूर्ण

	bfad->reglen = len << 2;
	rb = bfa_ioc_bar0(ioc);
	addr &= BFA_REG_ADDRMSK(ioc);

	/* offset and len sanity check */
	rc = bfad_reg_offset_check(bfa, addr, len);
	अगर (rc) अणु
		prपूर्णांकk(KERN_INFO "bfad[%d]: Failed reg offset check\n",
				bfad->inst_no);
		kमुक्त(bfad->regdata);
		bfad->regdata = शून्य;
		bfad->reglen = 0;
		वापस -EINVAL;
	पूर्ण

	reg_addr = rb + addr;
	regbuf =  (u32 *)bfad->regdata;
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	क्रम (i = 0; i < len; i++) अणु
		*regbuf = पढ़ोl(reg_addr);
		regbuf++;
		reg_addr += माप(u32);
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस nbytes;
पूर्ण

अटल sमाप_प्रकार
bfad_debugfs_ग_लिखो_regwr(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा bfad_debug_info *debug = file->निजी_data;
	काष्ठा bfad_port_s *port = (काष्ठा bfad_port_s *)debug->i_निजी;
	काष्ठा bfad_s *bfad = port->bfad;
	काष्ठा bfa_s *bfa = &bfad->bfa;
	काष्ठा bfa_ioc_s *ioc = &bfa->ioc;
	पूर्णांक addr, val, rc;
	व्योम __iomem *reg_addr;
	अचिन्हित दीर्घ flags;
	व्योम *kern_buf;

	kern_buf = memdup_user(buf, nbytes);
	अगर (IS_ERR(kern_buf))
		वापस PTR_ERR(kern_buf);

	rc = माला_पूछो(kern_buf, "%x:%x", &addr, &val);
	अगर (rc < 2) अणु
		prपूर्णांकk(KERN_INFO
			"bfad[%d]: %s failed to read user buf\n",
			bfad->inst_no, __func__);
		kमुक्त(kern_buf);
		वापस -EINVAL;
	पूर्ण
	kमुक्त(kern_buf);

	addr &= BFA_REG_ADDRMSK(ioc); /* offset only 17 bit and word align */

	/* offset and len sanity check */
	rc = bfad_reg_offset_check(bfa, addr, 1);
	अगर (rc) अणु
		prपूर्णांकk(KERN_INFO
			"bfad[%d]: Failed reg offset check\n",
			bfad->inst_no);
		वापस -EINVAL;
	पूर्ण

	reg_addr = (bfa_ioc_bar0(ioc)) + addr;
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	ग_लिखोl(val, reg_addr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस nbytes;
पूर्ण

अटल पूर्णांक
bfad_debugfs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bfad_debug_info *debug = file->निजी_data;

	अगर (!debug)
		वापस 0;

	file->निजी_data = शून्य;
	kमुक्त(debug);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_debugfs_release_fwtrc(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा bfad_debug_info *fw_debug = file->निजी_data;

	अगर (!fw_debug)
		वापस 0;

	अगर (fw_debug->debug_buffer)
		vमुक्त(fw_debug->debug_buffer);

	file->निजी_data = शून्य;
	kमुक्त(fw_debug);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations bfad_debugfs_op_drvtrc = अणु
	.owner		=	THIS_MODULE,
	.खोलो		=	bfad_debugfs_खोलो_drvtrc,
	.llseek		=	bfad_debugfs_lseek,
	.पढ़ो		=	bfad_debugfs_पढ़ो,
	.release	=	bfad_debugfs_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations bfad_debugfs_op_fwtrc = अणु
	.owner		=	THIS_MODULE,
	.खोलो		=	bfad_debugfs_खोलो_fwtrc,
	.llseek		=	bfad_debugfs_lseek,
	.पढ़ो		=	bfad_debugfs_पढ़ो,
	.release	=	bfad_debugfs_release_fwtrc,
पूर्ण;

अटल स्थिर काष्ठा file_operations bfad_debugfs_op_fwsave = अणु
	.owner		=	THIS_MODULE,
	.खोलो		=	bfad_debugfs_खोलो_fwsave,
	.llseek		=	bfad_debugfs_lseek,
	.पढ़ो		=	bfad_debugfs_पढ़ो,
	.release	=	bfad_debugfs_release_fwtrc,
पूर्ण;

अटल स्थिर काष्ठा file_operations bfad_debugfs_op_regrd = अणु
	.owner		=	THIS_MODULE,
	.खोलो		=	bfad_debugfs_खोलो_reg,
	.llseek		=	bfad_debugfs_lseek,
	.पढ़ो		=	bfad_debugfs_पढ़ो_regrd,
	.ग_लिखो		=	bfad_debugfs_ग_लिखो_regrd,
	.release	=	bfad_debugfs_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations bfad_debugfs_op_regwr = अणु
	.owner		=	THIS_MODULE,
	.खोलो		=	bfad_debugfs_खोलो_reg,
	.llseek		=	bfad_debugfs_lseek,
	.ग_लिखो		=	bfad_debugfs_ग_लिखो_regwr,
	.release	=	bfad_debugfs_release,
पूर्ण;

काष्ठा bfad_debugfs_entry अणु
	स्थिर अक्षर *name;
	umode_t	mode;
	स्थिर काष्ठा file_operations *fops;
पूर्ण;

अटल स्थिर काष्ठा bfad_debugfs_entry bfad_debugfs_files[] = अणु
	अणु "drvtrc", S_IFREG|S_IRUGO, &bfad_debugfs_op_drvtrc, पूर्ण,
	अणु "fwtrc",  S_IFREG|S_IRUGO, &bfad_debugfs_op_fwtrc,  पूर्ण,
	अणु "fwsave", S_IFREG|S_IRUGO, &bfad_debugfs_op_fwsave, पूर्ण,
	अणु "regrd",  S_IFREG|S_IRUGO|S_IWUSR, &bfad_debugfs_op_regrd,  पूर्ण,
	अणु "regwr",  S_IFREG|S_IWUSR, &bfad_debugfs_op_regwr,  पूर्ण,
पूर्ण;

अटल काष्ठा dentry *bfa_debugfs_root;
अटल atomic_t bfa_debugfs_port_count;

अंतरभूत व्योम
bfad_debugfs_init(काष्ठा bfad_port_s *port)
अणु
	काष्ठा bfad_s *bfad = port->bfad;
	स्थिर काष्ठा bfad_debugfs_entry *file;
	अक्षर name[64];
	पूर्णांक i;

	अगर (!bfa_debugfs_enable)
		वापस;

	/* Setup the BFA debugfs root directory*/
	अगर (!bfa_debugfs_root) अणु
		bfa_debugfs_root = debugfs_create_dir("bfa", शून्य);
		atomic_set(&bfa_debugfs_port_count, 0);
	पूर्ण

	/* Setup the pci_dev debugfs directory क्रम the port */
	snम_लिखो(name, माप(name), "pci_dev:%s", bfad->pci_name);
	अगर (!port->port_debugfs_root) अणु
		port->port_debugfs_root =
			debugfs_create_dir(name, bfa_debugfs_root);

		atomic_inc(&bfa_debugfs_port_count);

		क्रम (i = 0; i < ARRAY_SIZE(bfad_debugfs_files); i++) अणु
			file = &bfad_debugfs_files[i];
			bfad->bfad_dentry_files[i] =
					debugfs_create_file(file->name,
							file->mode,
							port->port_debugfs_root,
							port,
							file->fops);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

अंतरभूत व्योम
bfad_debugfs_निकास(काष्ठा bfad_port_s *port)
अणु
	काष्ठा bfad_s *bfad = port->bfad;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bfad_debugfs_files); i++) अणु
		अगर (bfad->bfad_dentry_files[i]) अणु
			debugfs_हटाओ(bfad->bfad_dentry_files[i]);
			bfad->bfad_dentry_files[i] = शून्य;
		पूर्ण
	पूर्ण

	/* Remove the pci_dev debugfs directory क्रम the port */
	अगर (port->port_debugfs_root) अणु
		debugfs_हटाओ(port->port_debugfs_root);
		port->port_debugfs_root = शून्य;
		atomic_dec(&bfa_debugfs_port_count);
	पूर्ण

	/* Remove the BFA debugfs root directory */
	अगर (atomic_पढ़ो(&bfa_debugfs_port_count) == 0) अणु
		debugfs_हटाओ(bfa_debugfs_root);
		bfa_debugfs_root = शून्य;
	पूर्ण
पूर्ण
