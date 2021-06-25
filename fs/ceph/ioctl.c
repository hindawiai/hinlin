<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>
#समावेश <linux/in.h>

#समावेश "super.h"
#समावेश "mds_client.h"
#समावेश "ioctl.h"
#समावेश <linux/ceph/striper.h>

/*
 * ioctls
 */

/*
 * get and set the file layout
 */
अटल दीर्घ ceph_ioctl_get_layout(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(file_inode(file));
	काष्ठा ceph_ioctl_layout l;
	पूर्णांक err;

	err = ceph_करो_getattr(file_inode(file), CEPH_STAT_CAP_LAYOUT, false);
	अगर (!err) अणु
		l.stripe_unit = ci->i_layout.stripe_unit;
		l.stripe_count = ci->i_layout.stripe_count;
		l.object_size = ci->i_layout.object_size;
		l.data_pool = ci->i_layout.pool_id;
		l.preferred_osd = -1;
		अगर (copy_to_user(arg, &l, माप(l)))
			वापस -EFAULT;
	पूर्ण

	वापस err;
पूर्ण

अटल दीर्घ __validate_layout(काष्ठा ceph_mds_client *mdsc,
			      काष्ठा ceph_ioctl_layout *l)
अणु
	पूर्णांक i, err;

	/* validate striping parameters */
	अगर ((l->object_size & ~PAGE_MASK) ||
	    (l->stripe_unit & ~PAGE_MASK) ||
	    ((अचिन्हित)l->stripe_unit != 0 &&
	     ((अचिन्हित)l->object_size % (अचिन्हित)l->stripe_unit)))
		वापस -EINVAL;

	/* make sure it's a valid data pool */
	mutex_lock(&mdsc->mutex);
	err = -EINVAL;
	क्रम (i = 0; i < mdsc->mdsmap->m_num_data_pg_pools; i++)
		अगर (mdsc->mdsmap->m_data_pg_pools[i] == l->data_pool) अणु
			err = 0;
			अवरोध;
		पूर्ण
	mutex_unlock(&mdsc->mutex);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल दीर्घ ceph_ioctl_set_layout(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_client(inode->i_sb)->mdsc;
	काष्ठा ceph_mds_request *req;
	काष्ठा ceph_ioctl_layout l;
	काष्ठा ceph_inode_info *ci = ceph_inode(file_inode(file));
	काष्ठा ceph_ioctl_layout nl;
	पूर्णांक err;

	अगर (copy_from_user(&l, arg, माप(l)))
		वापस -EFAULT;

	/* validate changed params against current layout */
	err = ceph_करो_getattr(file_inode(file), CEPH_STAT_CAP_LAYOUT, false);
	अगर (err)
		वापस err;

	स_रखो(&nl, 0, माप(nl));
	अगर (l.stripe_count)
		nl.stripe_count = l.stripe_count;
	अन्यथा
		nl.stripe_count = ci->i_layout.stripe_count;
	अगर (l.stripe_unit)
		nl.stripe_unit = l.stripe_unit;
	अन्यथा
		nl.stripe_unit = ci->i_layout.stripe_unit;
	अगर (l.object_size)
		nl.object_size = l.object_size;
	अन्यथा
		nl.object_size = ci->i_layout.object_size;
	अगर (l.data_pool)
		nl.data_pool = l.data_pool;
	अन्यथा
		nl.data_pool = ci->i_layout.pool_id;

	/* this is obsolete, and always -1 */
	nl.preferred_osd = -1;

	err = __validate_layout(mdsc, &nl);
	अगर (err)
		वापस err;

	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_SETLAYOUT,
				       USE_AUTH_MDS);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);
	req->r_inode = inode;
	ihold(inode);
	req->r_num_caps = 1;

	req->r_inode_drop = CEPH_CAP_खाता_SHARED | CEPH_CAP_खाता_EXCL;

	req->r_args.setlayout.layout.fl_stripe_unit =
		cpu_to_le32(l.stripe_unit);
	req->r_args.setlayout.layout.fl_stripe_count =
		cpu_to_le32(l.stripe_count);
	req->r_args.setlayout.layout.fl_object_size =
		cpu_to_le32(l.object_size);
	req->r_args.setlayout.layout.fl_pg_pool = cpu_to_le32(l.data_pool);

	err = ceph_mdsc_करो_request(mdsc, शून्य, req);
	ceph_mdsc_put_request(req);
	वापस err;
पूर्ण

/*
 * Set a layout policy on a directory inode. All items in the tree
 * rooted at this inode will inherit this layout on creation,
 * (It करोesn't apply retroactively )
 * unless a subdirectory has its own layout policy.
 */
अटल दीर्घ ceph_ioctl_set_layout_policy (काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_mds_request *req;
	काष्ठा ceph_ioctl_layout l;
	पूर्णांक err;
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_client(inode->i_sb)->mdsc;

	/* copy and validate */
	अगर (copy_from_user(&l, arg, माप(l)))
		वापस -EFAULT;

	err = __validate_layout(mdsc, &l);
	अगर (err)
		वापस err;

	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_SETसूचीLAYOUT,
				       USE_AUTH_MDS);

	अगर (IS_ERR(req))
		वापस PTR_ERR(req);
	req->r_inode = inode;
	ihold(inode);
	req->r_num_caps = 1;

	req->r_args.setlayout.layout.fl_stripe_unit =
			cpu_to_le32(l.stripe_unit);
	req->r_args.setlayout.layout.fl_stripe_count =
			cpu_to_le32(l.stripe_count);
	req->r_args.setlayout.layout.fl_object_size =
			cpu_to_le32(l.object_size);
	req->r_args.setlayout.layout.fl_pg_pool =
			cpu_to_le32(l.data_pool);

	err = ceph_mdsc_करो_request(mdsc, inode, req);
	ceph_mdsc_put_request(req);
	वापस err;
पूर्ण

/*
 * Return object name, size/offset inक्रमmation, and location (OSD
 * number, network address) क्रम a given file offset.
 */
अटल दीर्घ ceph_ioctl_get_dataloc(काष्ठा file *file, व्योम __user *arg)
अणु
	काष्ठा ceph_ioctl_dataloc dl;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_osd_client *osdc =
		&ceph_sb_to_client(inode->i_sb)->client->osdc;
	काष्ठा ceph_object_locator oloc;
	CEPH_DEFINE_OID_ONSTACK(oid);
	u32 xlen;
	u64 पंचांगp;
	काष्ठा ceph_pg pgid;
	पूर्णांक r;

	/* copy and validate */
	अगर (copy_from_user(&dl, arg, माप(dl)))
		वापस -EFAULT;

	करोwn_पढ़ो(&osdc->lock);
	ceph_calc_file_object_mapping(&ci->i_layout, dl.file_offset, 1,
				      &dl.object_no, &dl.object_offset, &xlen);
	dl.file_offset -= dl.object_offset;
	dl.object_size = ci->i_layout.object_size;
	dl.block_size = ci->i_layout.stripe_unit;

	/* block_offset = object_offset % block_size */
	पंचांगp = dl.object_offset;
	dl.block_offset = करो_भाग(पंचांगp, dl.block_size);

	snम_लिखो(dl.object_name, माप(dl.object_name), "%llx.%08llx",
		 ceph_ino(inode), dl.object_no);

	oloc.pool = ci->i_layout.pool_id;
	oloc.pool_ns = ceph_try_get_string(ci->i_layout.pool_ns);
	ceph_oid_म_लिखो(&oid, "%s", dl.object_name);

	r = ceph_object_locator_to_pg(osdc->osdmap, &oid, &oloc, &pgid);

	ceph_oloc_destroy(&oloc);
	अगर (r < 0) अणु
		up_पढ़ो(&osdc->lock);
		वापस r;
	पूर्ण

	dl.osd = ceph_pg_to_acting_primary(osdc->osdmap, &pgid);
	अगर (dl.osd >= 0) अणु
		काष्ठा ceph_entity_addr *a =
			ceph_osd_addr(osdc->osdmap, dl.osd);
		अगर (a)
			स_नकल(&dl.osd_addr, &a->in_addr, माप(dl.osd_addr));
	पूर्ण अन्यथा अणु
		स_रखो(&dl.osd_addr, 0, माप(dl.osd_addr));
	पूर्ण
	up_पढ़ो(&osdc->lock);

	/* send result back to user */
	अगर (copy_to_user(arg, &dl, माप(dl)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ ceph_ioctl_lazyio(काष्ठा file *file)
अणु
	काष्ठा ceph_file_info *fi = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_mds_client *mdsc = ceph_inode_to_client(inode)->mdsc;

	अगर ((fi->भ_शेषe & CEPH_खाता_MODE_LAZY) == 0) अणु
		spin_lock(&ci->i_ceph_lock);
		fi->भ_शेषe |= CEPH_खाता_MODE_LAZY;
		ci->i_nr_by_mode[ffs(CEPH_खाता_MODE_LAZY)]++;
		__ceph_touch_भ_शेषe(ci, mdsc, fi->भ_शेषe);
		spin_unlock(&ci->i_ceph_lock);
		करोut("ioctl_layzio: file %p marked lazy\n", file);

		ceph_check_caps(ci, 0, शून्य);
	पूर्ण अन्यथा अणु
		करोut("ioctl_layzio: file %p already lazy\n", file);
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ ceph_ioctl_syncio(काष्ठा file *file)
अणु
	काष्ठा ceph_file_info *fi = file->निजी_data;

	fi->flags |= CEPH_F_SYNC;
	वापस 0;
पूर्ण

दीर्घ ceph_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	करोut("ioctl file %p cmd %u arg %lu\n", file, cmd, arg);
	चयन (cmd) अणु
	हाल CEPH_IOC_GET_LAYOUT:
		वापस ceph_ioctl_get_layout(file, (व्योम __user *)arg);

	हाल CEPH_IOC_SET_LAYOUT:
		वापस ceph_ioctl_set_layout(file, (व्योम __user *)arg);

	हाल CEPH_IOC_SET_LAYOUT_POLICY:
		वापस ceph_ioctl_set_layout_policy(file, (व्योम __user *)arg);

	हाल CEPH_IOC_GET_DATALOC:
		वापस ceph_ioctl_get_dataloc(file, (व्योम __user *)arg);

	हाल CEPH_IOC_LAZYIO:
		वापस ceph_ioctl_lazyio(file);

	हाल CEPH_IOC_SYNCIO:
		वापस ceph_ioctl_syncio(file);
	पूर्ण

	वापस -ENOTTY;
पूर्ण
