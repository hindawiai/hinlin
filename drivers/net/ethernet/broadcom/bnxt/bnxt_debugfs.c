<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2017-2018 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश "bnxt_hsi.h"
#समावेश <linux/dim.h>
#समावेश "bnxt.h"
#समावेश "bnxt_debugfs.h"

अटल काष्ठा dentry *bnxt_debug_mnt;

अटल sमाप_प्रकार debugfs_dim_पढ़ो(काष्ठा file *filep,
				अक्षर __user *buffer,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dim *dim = filep->निजी_data;
	पूर्णांक len;
	अक्षर *buf;

	अगर (*ppos)
		वापस 0;
	अगर (!dim)
		वापस -ENODEV;
	buf = kaप्र_लिखो(GFP_KERNEL,
			"state = %d\n" \
			"profile_ix = %d\n" \
			"mode = %d\n" \
			"tune_state = %d\n" \
			"steps_right = %d\n" \
			"steps_left = %d\n" \
			"tired = %d\n",
			dim->state,
			dim->profile_ix,
			dim->mode,
			dim->tune_state,
			dim->steps_right,
			dim->steps_left,
			dim->tired);
	अगर (!buf)
		वापस -ENOMEM;
	अगर (count < म_माप(buf)) अणु
		kमुक्त(buf);
		वापस -ENOSPC;
	पूर्ण
	len = simple_पढ़ो_from_buffer(buffer, count, ppos, buf, म_माप(buf));
	kमुक्त(buf);
	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_dim_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = debugfs_dim_पढ़ो,
पूर्ण;

अटल व्योम debugfs_dim_ring_init(काष्ठा dim *dim, पूर्णांक ring_idx,
				  काष्ठा dentry *dd)
अणु
	अटल अक्षर qname[16];

	snम_लिखो(qname, 10, "%d", ring_idx);
	debugfs_create_file(qname, 0600, dd, dim, &debugfs_dim_fops);
पूर्ण

व्योम bnxt_debug_dev_init(काष्ठा bnxt *bp)
अणु
	स्थिर अक्षर *pname = pci_name(bp->pdev);
	काष्ठा dentry *dir;
	पूर्णांक i;

	bp->debugfs_pdev = debugfs_create_dir(pname, bnxt_debug_mnt);
	dir = debugfs_create_dir("dim", bp->debugfs_pdev);

	/* create files क्रम each rx ring */
	क्रम (i = 0; i < bp->cp_nr_rings; i++) अणु
		काष्ठा bnxt_cp_ring_info *cpr = &bp->bnapi[i]->cp_ring;

		अगर (cpr && bp->bnapi[i]->rx_ring)
			debugfs_dim_ring_init(&cpr->dim, i, dir);
	पूर्ण
पूर्ण

व्योम bnxt_debug_dev_निकास(काष्ठा bnxt *bp)
अणु
	अगर (bp) अणु
		debugfs_हटाओ_recursive(bp->debugfs_pdev);
		bp->debugfs_pdev = शून्य;
	पूर्ण
पूर्ण

व्योम bnxt_debug_init(व्योम)
अणु
	bnxt_debug_mnt = debugfs_create_dir("bnxt_en", शून्य);
पूर्ण

व्योम bnxt_debug_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(bnxt_debug_mnt);
पूर्ण
