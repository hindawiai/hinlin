<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Russell King
 *  Rewritten from the करोvefb driver, and Armada510 manuals.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_file.h>

#समावेश "armada_crtc.h"
#समावेश "armada_drm.h"

अटल पूर्णांक armada_debugfs_gem_linear_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा armada_निजी *priv = drm_to_armada_dev(dev);
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	mutex_lock(&priv->linear_lock);
	drm_mm_prपूर्णांक(&priv->linear, &p);
	mutex_unlock(&priv->linear_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_debugfs_crtc_reg_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा armada_crtc *dcrtc = m->निजी;
	पूर्णांक i;

	क्रम (i = 0x84; i <= 0x1c4; i += 4) अणु
		u32 v = पढ़ोl_relaxed(dcrtc->base + i);
		seq_म_लिखो(m, "0x%04x: 0x%08x\n", i, v);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक armada_debugfs_crtc_reg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, armada_debugfs_crtc_reg_show,
			   inode->i_निजी);
पूर्ण

अटल पूर्णांक armada_debugfs_crtc_reg_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *ptr, माप_प्रकार len, loff_t *off)
अणु
	काष्ठा armada_crtc *dcrtc;
	अचिन्हित दीर्घ reg, mask, val;
	अक्षर buf[32];
	पूर्णांक ret;
	u32 v;

	अगर (*off != 0)
		वापस 0;

	अगर (len > माप(buf) - 1)
		len = माप(buf) - 1;

	ret = म_नकलन_from_user(buf, ptr, len);
	अगर (ret < 0)
		वापस ret;
	buf[len] = '\0';

	अगर (माला_पूछो(buf, "%lx %lx %lx", &reg, &mask, &val) != 3)
		वापस -EINVAL;
	अगर (reg < 0x84 || reg > 0x1c4 || reg & 3)
		वापस -दुस्फल;

	dcrtc = ((काष्ठा seq_file *)file->निजी_data)->निजी;
	v = पढ़ोl(dcrtc->base + reg);
	v &= ~mask;
	v |= val & mask;
	ग_लिखोl(v, dcrtc->base + reg);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations armada_debugfs_crtc_reg_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = armada_debugfs_crtc_reg_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = armada_debugfs_crtc_reg_ग_लिखो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

व्योम armada_drm_crtc_debugfs_init(काष्ठा armada_crtc *dcrtc)
अणु
	debugfs_create_file("armada-regs", 0600, dcrtc->crtc.debugfs_entry,
			    dcrtc, &armada_debugfs_crtc_reg_fops);
पूर्ण

अटल काष्ठा drm_info_list armada_debugfs_list[] = अणु
	अणु "gem_linear", armada_debugfs_gem_linear_show, 0 पूर्ण,
पूर्ण;
#घोषणा ARMADA_DEBUGFS_ENTRIES ARRAY_SIZE(armada_debugfs_list)

पूर्णांक armada_drm_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(armada_debugfs_list, ARMADA_DEBUGFS_ENTRIES,
				 minor->debugfs_root, minor);

	वापस 0;
पूर्ण
