<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>
#समावेश <linux/ceph/pagelist.h>

#समावेश "super.h"
#समावेश "mds_client.h"

#समावेश <linux/ceph/decode.h>

#समावेश <linux/xattr.h>
#समावेश <linux/security.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/slab.h>

#घोषणा XATTR_CEPH_PREFIX "ceph."
#घोषणा XATTR_CEPH_PREFIX_LEN (माप (XATTR_CEPH_PREFIX) - 1)

अटल पूर्णांक __हटाओ_xattr(काष्ठा ceph_inode_info *ci,
			  काष्ठा ceph_inode_xattr *xattr);

अटल bool ceph_is_valid_xattr(स्थिर अक्षर *name)
अणु
	वापस !म_भेदन(name, XATTR_SECURITY_PREFIX, XATTR_SECURITY_PREFIX_LEN) ||
	       !म_भेदन(name, XATTR_CEPH_PREFIX, XATTR_CEPH_PREFIX_LEN) ||
	       !म_भेदन(name, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN) ||
	       !म_भेदन(name, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN);
पूर्ण

/*
 * These define भव xattrs exposing the recursive directory
 * statistics and layout metadata.
 */
काष्ठा ceph_vxattr अणु
	अक्षर *name;
	माप_प्रकार name_size;	/* म_माप(name) + 1 (क्रम '\0') */
	sमाप_प्रकार (*getxattr_cb)(काष्ठा ceph_inode_info *ci, अक्षर *val,
			       माप_प्रकार size);
	bool (*exists_cb)(काष्ठा ceph_inode_info *ci);
	अचिन्हित पूर्णांक flags;
पूर्ण;

#घोषणा VXATTR_FLAG_READONLY		(1<<0)
#घोषणा VXATTR_FLAG_HIDDEN		(1<<1)
#घोषणा VXATTR_FLAG_RSTAT		(1<<2)
#घोषणा VXATTR_FLAG_सूचीSTAT		(1<<3)

/* layouts */

अटल bool ceph_vxattrcb_layout_exists(काष्ठा ceph_inode_info *ci)
अणु
	काष्ठा ceph_file_layout *fl = &ci->i_layout;
	वापस (fl->stripe_unit > 0 || fl->stripe_count > 0 ||
		fl->object_size > 0 || fl->pool_id >= 0 ||
		rcu_dereference_raw(fl->pool_ns) != शून्य);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_layout(काष्ठा ceph_inode_info *ci, अक्षर *val,
				    माप_प्रकार size)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(ci->vfs_inode.i_sb);
	काष्ठा ceph_osd_client *osdc = &fsc->client->osdc;
	काष्ठा ceph_string *pool_ns;
	s64 pool = ci->i_layout.pool_id;
	स्थिर अक्षर *pool_name;
	स्थिर अक्षर *ns_field = " pool_namespace=";
	अक्षर buf[128];
	माप_प्रकार len, total_len = 0;
	sमाप_प्रकार ret;

	pool_ns = ceph_try_get_string(ci->i_layout.pool_ns);

	करोut("ceph_vxattrcb_layout %p\n", &ci->vfs_inode);
	करोwn_पढ़ो(&osdc->lock);
	pool_name = ceph_pg_pool_name_by_id(osdc->osdmap, pool);
	अगर (pool_name) अणु
		len = snम_लिखो(buf, माप(buf),
		"stripe_unit=%u stripe_count=%u object_size=%u pool=",
		ci->i_layout.stripe_unit, ci->i_layout.stripe_count,
	        ci->i_layout.object_size);
		total_len = len + म_माप(pool_name);
	पूर्ण अन्यथा अणु
		len = snम_लिखो(buf, माप(buf),
		"stripe_unit=%u stripe_count=%u object_size=%u pool=%lld",
		ci->i_layout.stripe_unit, ci->i_layout.stripe_count,
		ci->i_layout.object_size, pool);
		total_len = len;
	पूर्ण

	अगर (pool_ns)
		total_len += म_माप(ns_field) + pool_ns->len;

	ret = total_len;
	अगर (size >= total_len) अणु
		स_नकल(val, buf, len);
		ret = len;
		अगर (pool_name) अणु
			len = म_माप(pool_name);
			स_नकल(val + ret, pool_name, len);
			ret += len;
		पूर्ण
		अगर (pool_ns) अणु
			len = म_माप(ns_field);
			स_नकल(val + ret, ns_field, len);
			ret += len;
			स_नकल(val + ret, pool_ns->str, pool_ns->len);
			ret += pool_ns->len;
		पूर्ण
	पूर्ण
	up_पढ़ो(&osdc->lock);
	ceph_put_string(pool_ns);
	वापस ret;
पूर्ण

/*
 * The convention with strings in xattrs is that they should not be शून्य
 * terminated, since we're वापसing the length with them. snम_लिखो always
 * शून्य terminates however, so call it on a temporary buffer and then स_नकल
 * the result पूर्णांकo place.
 */
अटल __म_लिखो(3, 4)
पूर्णांक ceph_fmt_xattr(अक्षर *val, माप_प्रकार size, स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक ret;
	बहु_सूची args;
	अक्षर buf[96]; /* NB: reevaluate size अगर new vxattrs are added */

	बहु_शुरू(args, fmt);
	ret = vsnम_लिखो(buf, size ? माप(buf) : 0, fmt, args);
	बहु_पूर्ण(args);

	/* Sanity check */
	अगर (size && ret + 1 > माप(buf)) अणु
		WARN_ONCE(true, "Returned length too big (%d)", ret);
		वापस -E2BIG;
	पूर्ण

	अगर (ret <= size)
		स_नकल(val, buf, ret);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_layout_stripe_unit(काष्ठा ceph_inode_info *ci,
						अक्षर *val, माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%u", ci->i_layout.stripe_unit);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_layout_stripe_count(काष्ठा ceph_inode_info *ci,
						 अक्षर *val, माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%u", ci->i_layout.stripe_count);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_layout_object_size(काष्ठा ceph_inode_info *ci,
						अक्षर *val, माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%u", ci->i_layout.object_size);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_layout_pool(काष्ठा ceph_inode_info *ci,
					 अक्षर *val, माप_प्रकार size)
अणु
	sमाप_प्रकार ret;
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(ci->vfs_inode.i_sb);
	काष्ठा ceph_osd_client *osdc = &fsc->client->osdc;
	s64 pool = ci->i_layout.pool_id;
	स्थिर अक्षर *pool_name;

	करोwn_पढ़ो(&osdc->lock);
	pool_name = ceph_pg_pool_name_by_id(osdc->osdmap, pool);
	अगर (pool_name) अणु
		ret = म_माप(pool_name);
		अगर (ret <= size)
			स_नकल(val, pool_name, ret);
	पूर्ण अन्यथा अणु
		ret = ceph_fmt_xattr(val, size, "%lld", pool);
	पूर्ण
	up_पढ़ो(&osdc->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_layout_pool_namespace(काष्ठा ceph_inode_info *ci,
						   अक्षर *val, माप_प्रकार size)
अणु
	sमाप_प्रकार ret = 0;
	काष्ठा ceph_string *ns = ceph_try_get_string(ci->i_layout.pool_ns);

	अगर (ns) अणु
		ret = ns->len;
		अगर (ret <= size)
			स_नकल(val, ns->str, ret);
		ceph_put_string(ns);
	पूर्ण
	वापस ret;
पूर्ण

/* directories */

अटल sमाप_प्रकार ceph_vxattrcb_dir_entries(काष्ठा ceph_inode_info *ci, अक्षर *val,
					 माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%lld", ci->i_files + ci->i_subdirs);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_dir_files(काष्ठा ceph_inode_info *ci, अक्षर *val,
				       माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%lld", ci->i_files);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_dir_subdirs(काष्ठा ceph_inode_info *ci, अक्षर *val,
					 माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%lld", ci->i_subdirs);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_dir_rentries(काष्ठा ceph_inode_info *ci, अक्षर *val,
					  माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%lld",
				ci->i_rfiles + ci->i_rsubdirs);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_dir_rfiles(काष्ठा ceph_inode_info *ci, अक्षर *val,
					माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%lld", ci->i_rfiles);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_dir_rsubdirs(काष्ठा ceph_inode_info *ci, अक्षर *val,
					  माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%lld", ci->i_rsubdirs);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_dir_rsnaps(काष्ठा ceph_inode_info *ci, अक्षर *val,
					  माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%lld", ci->i_rsnaps);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_dir_rbytes(काष्ठा ceph_inode_info *ci, अक्षर *val,
					माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%lld", ci->i_rbytes);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_dir_rस_समय(काष्ठा ceph_inode_info *ci, अक्षर *val,
					माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%lld.%09ld", ci->i_rस_समय.tv_sec,
				ci->i_rस_समय.tv_nsec);
पूर्ण

/* dir pin */
अटल bool ceph_vxattrcb_dir_pin_exists(काष्ठा ceph_inode_info *ci)
अणु
	वापस ci->i_dir_pin != -ENODATA;
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_dir_pin(काष्ठा ceph_inode_info *ci, अक्षर *val,
				     माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%d", (पूर्णांक)ci->i_dir_pin);
पूर्ण

/* quotas */
अटल bool ceph_vxattrcb_quota_exists(काष्ठा ceph_inode_info *ci)
अणु
	bool ret = false;
	spin_lock(&ci->i_ceph_lock);
	अगर ((ci->i_max_files || ci->i_max_bytes) &&
	    ci->i_vino.snap == CEPH_NOSNAP &&
	    ci->i_snap_realm &&
	    ci->i_snap_realm->ino == ci->i_vino.ino)
		ret = true;
	spin_unlock(&ci->i_ceph_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_quota(काष्ठा ceph_inode_info *ci, अक्षर *val,
				   माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "max_bytes=%llu max_files=%llu",
				ci->i_max_bytes, ci->i_max_files);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_quota_max_bytes(काष्ठा ceph_inode_info *ci,
					     अक्षर *val, माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%llu", ci->i_max_bytes);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_quota_max_files(काष्ठा ceph_inode_info *ci,
					     अक्षर *val, माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%llu", ci->i_max_files);
पूर्ण

/* snapshots */
अटल bool ceph_vxattrcb_snap_bसमय_exists(काष्ठा ceph_inode_info *ci)
अणु
	वापस (ci->i_snap_bसमय.tv_sec != 0 || ci->i_snap_bसमय.tv_nsec != 0);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_snap_bसमय(काष्ठा ceph_inode_info *ci, अक्षर *val,
					माप_प्रकार size)
अणु
	वापस ceph_fmt_xattr(val, size, "%lld.%09ld", ci->i_snap_bसमय.tv_sec,
				ci->i_snap_bसमय.tv_nsec);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_cluster_fsid(काष्ठा ceph_inode_info *ci,
					  अक्षर *val, माप_प्रकार size)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(ci->vfs_inode.i_sb);

	वापस ceph_fmt_xattr(val, size, "%pU", &fsc->client->fsid);
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_client_id(काष्ठा ceph_inode_info *ci,
				       अक्षर *val, माप_प्रकार size)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(ci->vfs_inode.i_sb);

	वापस ceph_fmt_xattr(val, size, "client%lld",
			      ceph_client_gid(fsc->client));
पूर्ण

अटल sमाप_प्रकार ceph_vxattrcb_caps(काष्ठा ceph_inode_info *ci, अक्षर *val,
					माप_प्रकार size)
अणु
	पूर्णांक issued;

	spin_lock(&ci->i_ceph_lock);
	issued = __ceph_caps_issued(ci, शून्य);
	spin_unlock(&ci->i_ceph_lock);

	वापस ceph_fmt_xattr(val, size, "%s/0x%x",
			      ceph_cap_string(issued), issued);
पूर्ण

#घोषणा CEPH_XATTR_NAME(_type, _name)	XATTR_CEPH_PREFIX #_type "." #_name
#घोषणा CEPH_XATTR_NAME2(_type, _name, _name2)	\
	XATTR_CEPH_PREFIX #_type "." #_name "." #_name2

#घोषणा XATTR_NAME_CEPH(_type, _name, _flags)				\
	अणु								\
		.name = CEPH_XATTR_NAME(_type, _name),			\
		.name_size = माप (CEPH_XATTR_NAME(_type, _name)), \
		.getxattr_cb = ceph_vxattrcb_ ## _type ## _ ## _name, \
		.exists_cb = शून्य,					\
		.flags = (VXATTR_FLAG_READONLY | _flags),		\
	पूर्ण
#घोषणा XATTR_RSTAT_FIELD(_type, _name)			\
	XATTR_NAME_CEPH(_type, _name, VXATTR_FLAG_RSTAT)
#घोषणा XATTR_LAYOUT_FIELD(_type, _name, _field)			\
	अणु								\
		.name = CEPH_XATTR_NAME2(_type, _name, _field),	\
		.name_size = माप (CEPH_XATTR_NAME2(_type, _name, _field)), \
		.getxattr_cb = ceph_vxattrcb_ ## _name ## _ ## _field, \
		.exists_cb = ceph_vxattrcb_layout_exists,	\
		.flags = VXATTR_FLAG_HIDDEN,			\
	पूर्ण
#घोषणा XATTR_QUOTA_FIELD(_type, _name)					\
	अणु								\
		.name = CEPH_XATTR_NAME(_type, _name),			\
		.name_size = माप(CEPH_XATTR_NAME(_type, _name)),	\
		.getxattr_cb = ceph_vxattrcb_ ## _type ## _ ## _name,	\
		.exists_cb = ceph_vxattrcb_quota_exists,		\
		.flags = VXATTR_FLAG_HIDDEN,				\
	पूर्ण

अटल काष्ठा ceph_vxattr ceph_dir_vxattrs[] = अणु
	अणु
		.name = "ceph.dir.layout",
		.name_size = माप("ceph.dir.layout"),
		.getxattr_cb = ceph_vxattrcb_layout,
		.exists_cb = ceph_vxattrcb_layout_exists,
		.flags = VXATTR_FLAG_HIDDEN,
	पूर्ण,
	XATTR_LAYOUT_FIELD(dir, layout, stripe_unit),
	XATTR_LAYOUT_FIELD(dir, layout, stripe_count),
	XATTR_LAYOUT_FIELD(dir, layout, object_size),
	XATTR_LAYOUT_FIELD(dir, layout, pool),
	XATTR_LAYOUT_FIELD(dir, layout, pool_namespace),
	XATTR_NAME_CEPH(dir, entries, VXATTR_FLAG_सूचीSTAT),
	XATTR_NAME_CEPH(dir, files, VXATTR_FLAG_सूचीSTAT),
	XATTR_NAME_CEPH(dir, subdirs, VXATTR_FLAG_सूचीSTAT),
	XATTR_RSTAT_FIELD(dir, rentries),
	XATTR_RSTAT_FIELD(dir, rfiles),
	XATTR_RSTAT_FIELD(dir, rsubdirs),
	XATTR_RSTAT_FIELD(dir, rsnaps),
	XATTR_RSTAT_FIELD(dir, rbytes),
	XATTR_RSTAT_FIELD(dir, rस_समय),
	अणु
		.name = "ceph.dir.pin",
		.name_size = माप("ceph.dir.pin"),
		.getxattr_cb = ceph_vxattrcb_dir_pin,
		.exists_cb = ceph_vxattrcb_dir_pin_exists,
		.flags = VXATTR_FLAG_HIDDEN,
	पूर्ण,
	अणु
		.name = "ceph.quota",
		.name_size = माप("ceph.quota"),
		.getxattr_cb = ceph_vxattrcb_quota,
		.exists_cb = ceph_vxattrcb_quota_exists,
		.flags = VXATTR_FLAG_HIDDEN,
	पूर्ण,
	XATTR_QUOTA_FIELD(quota, max_bytes),
	XATTR_QUOTA_FIELD(quota, max_files),
	अणु
		.name = "ceph.snap.btime",
		.name_size = माप("ceph.snap.btime"),
		.getxattr_cb = ceph_vxattrcb_snap_bसमय,
		.exists_cb = ceph_vxattrcb_snap_bसमय_exists,
		.flags = VXATTR_FLAG_READONLY,
	पूर्ण,
	अणु
		.name = "ceph.caps",
		.name_size = माप("ceph.caps"),
		.getxattr_cb = ceph_vxattrcb_caps,
		.exists_cb = शून्य,
		.flags = VXATTR_FLAG_HIDDEN,
	पूर्ण,
	अणु .name = शून्य, 0 पूर्ण	/* Required table terminator */
पूर्ण;

/* files */

अटल काष्ठा ceph_vxattr ceph_file_vxattrs[] = अणु
	अणु
		.name = "ceph.file.layout",
		.name_size = माप("ceph.file.layout"),
		.getxattr_cb = ceph_vxattrcb_layout,
		.exists_cb = ceph_vxattrcb_layout_exists,
		.flags = VXATTR_FLAG_HIDDEN,
	पूर्ण,
	XATTR_LAYOUT_FIELD(file, layout, stripe_unit),
	XATTR_LAYOUT_FIELD(file, layout, stripe_count),
	XATTR_LAYOUT_FIELD(file, layout, object_size),
	XATTR_LAYOUT_FIELD(file, layout, pool),
	XATTR_LAYOUT_FIELD(file, layout, pool_namespace),
	अणु
		.name = "ceph.snap.btime",
		.name_size = माप("ceph.snap.btime"),
		.getxattr_cb = ceph_vxattrcb_snap_bसमय,
		.exists_cb = ceph_vxattrcb_snap_bसमय_exists,
		.flags = VXATTR_FLAG_READONLY,
	पूर्ण,
	अणु
		.name = "ceph.caps",
		.name_size = माप("ceph.caps"),
		.getxattr_cb = ceph_vxattrcb_caps,
		.exists_cb = शून्य,
		.flags = VXATTR_FLAG_HIDDEN,
	पूर्ण,
	अणु .name = शून्य, 0 पूर्ण	/* Required table terminator */
पूर्ण;

अटल काष्ठा ceph_vxattr ceph_common_vxattrs[] = अणु
	अणु
		.name = "ceph.cluster_fsid",
		.name_size = माप("ceph.cluster_fsid"),
		.getxattr_cb = ceph_vxattrcb_cluster_fsid,
		.exists_cb = शून्य,
		.flags = VXATTR_FLAG_READONLY,
	पूर्ण,
	अणु
		.name = "ceph.client_id",
		.name_size = माप("ceph.client_id"),
		.getxattr_cb = ceph_vxattrcb_client_id,
		.exists_cb = शून्य,
		.flags = VXATTR_FLAG_READONLY,
	पूर्ण,
	अणु .name = शून्य, 0 पूर्ण	/* Required table terminator */
पूर्ण;

अटल काष्ठा ceph_vxattr *ceph_inode_vxattrs(काष्ठा inode *inode)
अणु
	अगर (S_ISसूची(inode->i_mode))
		वापस ceph_dir_vxattrs;
	अन्यथा अगर (S_ISREG(inode->i_mode))
		वापस ceph_file_vxattrs;
	वापस शून्य;
पूर्ण

अटल काष्ठा ceph_vxattr *ceph_match_vxattr(काष्ठा inode *inode,
						स्थिर अक्षर *name)
अणु
	काष्ठा ceph_vxattr *vxattr = ceph_inode_vxattrs(inode);

	अगर (vxattr) अणु
		जबतक (vxattr->name) अणु
			अगर (!म_भेद(vxattr->name, name))
				वापस vxattr;
			vxattr++;
		पूर्ण
	पूर्ण

	vxattr = ceph_common_vxattrs;
	जबतक (vxattr->name) अणु
		अगर (!म_भेद(vxattr->name, name))
			वापस vxattr;
		vxattr++;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक __set_xattr(काष्ठा ceph_inode_info *ci,
			   स्थिर अक्षर *name, पूर्णांक name_len,
			   स्थिर अक्षर *val, पूर्णांक val_len,
			   पूर्णांक flags, पूर्णांक update_xattr,
			   काष्ठा ceph_inode_xattr **newxattr)
अणु
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा ceph_inode_xattr *xattr = शून्य;
	पूर्णांक c;
	पूर्णांक new = 0;

	p = &ci->i_xattrs.index.rb_node;
	जबतक (*p) अणु
		parent = *p;
		xattr = rb_entry(parent, काष्ठा ceph_inode_xattr, node);
		c = म_भेदन(name, xattr->name, min(name_len, xattr->name_len));
		अगर (c < 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (c > 0)
			p = &(*p)->rb_right;
		अन्यथा अणु
			अगर (name_len == xattr->name_len)
				अवरोध;
			अन्यथा अगर (name_len < xattr->name_len)
				p = &(*p)->rb_left;
			अन्यथा
				p = &(*p)->rb_right;
		पूर्ण
		xattr = शून्य;
	पूर्ण

	अगर (update_xattr) अणु
		पूर्णांक err = 0;

		अगर (xattr && (flags & XATTR_CREATE))
			err = -EEXIST;
		अन्यथा अगर (!xattr && (flags & XATTR_REPLACE))
			err = -ENODATA;
		अगर (err) अणु
			kमुक्त(name);
			kमुक्त(val);
			kमुक्त(*newxattr);
			वापस err;
		पूर्ण
		अगर (update_xattr < 0) अणु
			अगर (xattr)
				__हटाओ_xattr(ci, xattr);
			kमुक्त(name);
			kमुक्त(*newxattr);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (!xattr) अणु
		new = 1;
		xattr = *newxattr;
		xattr->name = name;
		xattr->name_len = name_len;
		xattr->should_मुक्त_name = update_xattr;

		ci->i_xattrs.count++;
		करोut("__set_xattr count=%d\n", ci->i_xattrs.count);
	पूर्ण अन्यथा अणु
		kमुक्त(*newxattr);
		*newxattr = शून्य;
		अगर (xattr->should_मुक्त_val)
			kमुक्त(xattr->val);

		अगर (update_xattr) अणु
			kमुक्त(name);
			name = xattr->name;
		पूर्ण
		ci->i_xattrs.names_size -= xattr->name_len;
		ci->i_xattrs.vals_size -= xattr->val_len;
	पूर्ण
	ci->i_xattrs.names_size += name_len;
	ci->i_xattrs.vals_size += val_len;
	अगर (val)
		xattr->val = val;
	अन्यथा
		xattr->val = "";

	xattr->val_len = val_len;
	xattr->dirty = update_xattr;
	xattr->should_मुक्त_val = (val && update_xattr);

	अगर (new) अणु
		rb_link_node(&xattr->node, parent, p);
		rb_insert_color(&xattr->node, &ci->i_xattrs.index);
		करोut("__set_xattr_val p=%p\n", p);
	पूर्ण

	करोut("__set_xattr_val added %llx.%llx xattr %p %.*s=%.*s\n",
	     ceph_vinop(&ci->vfs_inode), xattr, name_len, name, val_len, val);

	वापस 0;
पूर्ण

अटल काष्ठा ceph_inode_xattr *__get_xattr(काष्ठा ceph_inode_info *ci,
			   स्थिर अक्षर *name)
अणु
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा ceph_inode_xattr *xattr = शून्य;
	पूर्णांक name_len = म_माप(name);
	पूर्णांक c;

	p = &ci->i_xattrs.index.rb_node;
	जबतक (*p) अणु
		parent = *p;
		xattr = rb_entry(parent, काष्ठा ceph_inode_xattr, node);
		c = म_भेदन(name, xattr->name, xattr->name_len);
		अगर (c == 0 && name_len > xattr->name_len)
			c = 1;
		अगर (c < 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (c > 0)
			p = &(*p)->rb_right;
		अन्यथा अणु
			करोut("__get_xattr %s: found %.*s\n", name,
			     xattr->val_len, xattr->val);
			वापस xattr;
		पूर्ण
	पूर्ण

	करोut("__get_xattr %s: not found\n", name);

	वापस शून्य;
पूर्ण

अटल व्योम __मुक्त_xattr(काष्ठा ceph_inode_xattr *xattr)
अणु
	BUG_ON(!xattr);

	अगर (xattr->should_मुक्त_name)
		kमुक्त(xattr->name);
	अगर (xattr->should_मुक्त_val)
		kमुक्त(xattr->val);

	kमुक्त(xattr);
पूर्ण

अटल पूर्णांक __हटाओ_xattr(काष्ठा ceph_inode_info *ci,
			  काष्ठा ceph_inode_xattr *xattr)
अणु
	अगर (!xattr)
		वापस -ENODATA;

	rb_erase(&xattr->node, &ci->i_xattrs.index);

	अगर (xattr->should_मुक्त_name)
		kमुक्त(xattr->name);
	अगर (xattr->should_मुक्त_val)
		kमुक्त(xattr->val);

	ci->i_xattrs.names_size -= xattr->name_len;
	ci->i_xattrs.vals_size -= xattr->val_len;
	ci->i_xattrs.count--;
	kमुक्त(xattr);

	वापस 0;
पूर्ण

अटल अक्षर *__copy_xattr_names(काष्ठा ceph_inode_info *ci,
				अक्षर *dest)
अणु
	काष्ठा rb_node *p;
	काष्ठा ceph_inode_xattr *xattr = शून्य;

	p = rb_first(&ci->i_xattrs.index);
	करोut("__copy_xattr_names count=%d\n", ci->i_xattrs.count);

	जबतक (p) अणु
		xattr = rb_entry(p, काष्ठा ceph_inode_xattr, node);
		स_नकल(dest, xattr->name, xattr->name_len);
		dest[xattr->name_len] = '\0';

		करोut("dest=%s %p (%s) (%d/%d)\n", dest, xattr, xattr->name,
		     xattr->name_len, ci->i_xattrs.names_size);

		dest += xattr->name_len + 1;
		p = rb_next(p);
	पूर्ण

	वापस dest;
पूर्ण

व्योम __ceph_destroy_xattrs(काष्ठा ceph_inode_info *ci)
अणु
	काष्ठा rb_node *p, *पंचांगp;
	काष्ठा ceph_inode_xattr *xattr = शून्य;

	p = rb_first(&ci->i_xattrs.index);

	करोut("__ceph_destroy_xattrs p=%p\n", p);

	जबतक (p) अणु
		xattr = rb_entry(p, काष्ठा ceph_inode_xattr, node);
		पंचांगp = p;
		p = rb_next(पंचांगp);
		करोut("__ceph_destroy_xattrs next p=%p (%.*s)\n", p,
		     xattr->name_len, xattr->name);
		rb_erase(पंचांगp, &ci->i_xattrs.index);

		__मुक्त_xattr(xattr);
	पूर्ण

	ci->i_xattrs.names_size = 0;
	ci->i_xattrs.vals_size = 0;
	ci->i_xattrs.index_version = 0;
	ci->i_xattrs.count = 0;
	ci->i_xattrs.index = RB_ROOT;
पूर्ण

अटल पूर्णांक __build_xattrs(काष्ठा inode *inode)
	__releases(ci->i_ceph_lock)
	__acquires(ci->i_ceph_lock)
अणु
	u32 namelen;
	u32 numattr = 0;
	व्योम *p, *end;
	u32 len;
	स्थिर अक्षर *name, *val;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	u64 xattr_version;
	काष्ठा ceph_inode_xattr **xattrs = शून्य;
	पूर्णांक err = 0;
	पूर्णांक i;

	करोut("__build_xattrs() len=%d\n",
	     ci->i_xattrs.blob ? (पूर्णांक)ci->i_xattrs.blob->vec.iov_len : 0);

	अगर (ci->i_xattrs.index_version >= ci->i_xattrs.version)
		वापस 0; /* alपढ़ोy built */

	__ceph_destroy_xattrs(ci);

start:
	/* updated पूर्णांकernal xattr rb tree */
	अगर (ci->i_xattrs.blob && ci->i_xattrs.blob->vec.iov_len > 4) अणु
		p = ci->i_xattrs.blob->vec.iov_base;
		end = p + ci->i_xattrs.blob->vec.iov_len;
		ceph_decode_32_safe(&p, end, numattr, bad);
		xattr_version = ci->i_xattrs.version;
		spin_unlock(&ci->i_ceph_lock);

		xattrs = kसुस्मृति(numattr, माप(काष्ठा ceph_inode_xattr *),
				 GFP_NOFS);
		err = -ENOMEM;
		अगर (!xattrs)
			जाओ bad_lock;

		क्रम (i = 0; i < numattr; i++) अणु
			xattrs[i] = kदो_स्मृति(माप(काष्ठा ceph_inode_xattr),
					    GFP_NOFS);
			अगर (!xattrs[i])
				जाओ bad_lock;
		पूर्ण

		spin_lock(&ci->i_ceph_lock);
		अगर (ci->i_xattrs.version != xattr_version) अणु
			/* lost a race, retry */
			क्रम (i = 0; i < numattr; i++)
				kमुक्त(xattrs[i]);
			kमुक्त(xattrs);
			xattrs = शून्य;
			जाओ start;
		पूर्ण
		err = -EIO;
		जबतक (numattr--) अणु
			ceph_decode_32_safe(&p, end, len, bad);
			namelen = len;
			name = p;
			p += len;
			ceph_decode_32_safe(&p, end, len, bad);
			val = p;
			p += len;

			err = __set_xattr(ci, name, namelen, val, len,
					  0, 0, &xattrs[numattr]);

			अगर (err < 0)
				जाओ bad;
		पूर्ण
		kमुक्त(xattrs);
	पूर्ण
	ci->i_xattrs.index_version = ci->i_xattrs.version;
	ci->i_xattrs.dirty = false;

	वापस err;
bad_lock:
	spin_lock(&ci->i_ceph_lock);
bad:
	अगर (xattrs) अणु
		क्रम (i = 0; i < numattr; i++)
			kमुक्त(xattrs[i]);
		kमुक्त(xattrs);
	पूर्ण
	ci->i_xattrs.names_size = 0;
	वापस err;
पूर्ण

अटल पूर्णांक __get_required_blob_size(काष्ठा ceph_inode_info *ci, पूर्णांक name_size,
				    पूर्णांक val_size)
अणु
	/*
	 * 4 bytes क्रम the length, and additional 4 bytes per each xattr name,
	 * 4 bytes per each value
	 */
	पूर्णांक size = 4 + ci->i_xattrs.count*(4 + 4) +
			     ci->i_xattrs.names_size +
			     ci->i_xattrs.vals_size;
	करोut("__get_required_blob_size c=%d names.size=%d vals.size=%d\n",
	     ci->i_xattrs.count, ci->i_xattrs.names_size,
	     ci->i_xattrs.vals_size);

	अगर (name_size)
		size += 4 + 4 + name_size + val_size;

	वापस size;
पूर्ण

/*
 * If there are dirty xattrs, reencode xattrs पूर्णांकo the pपुनः_स्मृति_blob
 * and swap पूर्णांकo place.  It वापसs the old i_xattrs.blob (or शून्य) so
 * that it can be मुक्तd by the caller as the i_ceph_lock is likely to be
 * held.
 */
काष्ठा ceph_buffer *__ceph_build_xattrs_blob(काष्ठा ceph_inode_info *ci)
अणु
	काष्ठा rb_node *p;
	काष्ठा ceph_inode_xattr *xattr = शून्य;
	काष्ठा ceph_buffer *old_blob = शून्य;
	व्योम *dest;

	करोut("__build_xattrs_blob %p\n", &ci->vfs_inode);
	अगर (ci->i_xattrs.dirty) अणु
		पूर्णांक need = __get_required_blob_size(ci, 0, 0);

		BUG_ON(need > ci->i_xattrs.pपुनः_स्मृति_blob->alloc_len);

		p = rb_first(&ci->i_xattrs.index);
		dest = ci->i_xattrs.pपुनः_स्मृति_blob->vec.iov_base;

		ceph_encode_32(&dest, ci->i_xattrs.count);
		जबतक (p) अणु
			xattr = rb_entry(p, काष्ठा ceph_inode_xattr, node);

			ceph_encode_32(&dest, xattr->name_len);
			स_नकल(dest, xattr->name, xattr->name_len);
			dest += xattr->name_len;
			ceph_encode_32(&dest, xattr->val_len);
			स_नकल(dest, xattr->val, xattr->val_len);
			dest += xattr->val_len;

			p = rb_next(p);
		पूर्ण

		/* adjust buffer len; it may be larger than we need */
		ci->i_xattrs.pपुनः_स्मृति_blob->vec.iov_len =
			dest - ci->i_xattrs.pपुनः_स्मृति_blob->vec.iov_base;

		अगर (ci->i_xattrs.blob)
			old_blob = ci->i_xattrs.blob;
		ci->i_xattrs.blob = ci->i_xattrs.pपुनः_स्मृति_blob;
		ci->i_xattrs.pपुनः_स्मृति_blob = शून्य;
		ci->i_xattrs.dirty = false;
		ci->i_xattrs.version++;
	पूर्ण

	वापस old_blob;
पूर्ण

अटल अंतरभूत पूर्णांक __get_request_mask(काष्ठा inode *in) अणु
	काष्ठा ceph_mds_request *req = current->journal_info;
	पूर्णांक mask = 0;
	अगर (req && req->r_target_inode == in) अणु
		अगर (req->r_op == CEPH_MDS_OP_LOOKUP ||
		    req->r_op == CEPH_MDS_OP_LOOKUPINO ||
		    req->r_op == CEPH_MDS_OP_LOOKUPPARENT ||
		    req->r_op == CEPH_MDS_OP_GETATTR) अणु
			mask = le32_to_cpu(req->r_args.getattr.mask);
		पूर्ण अन्यथा अगर (req->r_op == CEPH_MDS_OP_OPEN ||
			   req->r_op == CEPH_MDS_OP_CREATE) अणु
			mask = le32_to_cpu(req->r_args.खोलो.mask);
		पूर्ण
	पूर्ण
	वापस mask;
पूर्ण

sमाप_प्रकार __ceph_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name, व्योम *value,
		      माप_प्रकार size)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_inode_xattr *xattr;
	काष्ठा ceph_vxattr *vxattr = शून्य;
	पूर्णांक req_mask;
	sमाप_प्रकार err;

	/* let's see अगर a भव xattr was requested */
	vxattr = ceph_match_vxattr(inode, name);
	अगर (vxattr) अणु
		पूर्णांक mask = 0;
		अगर (vxattr->flags & VXATTR_FLAG_RSTAT)
			mask |= CEPH_STAT_RSTAT;
		अगर (vxattr->flags & VXATTR_FLAG_सूचीSTAT)
			mask |= CEPH_CAP_खाता_SHARED;
		err = ceph_करो_getattr(inode, mask, true);
		अगर (err)
			वापस err;
		err = -ENODATA;
		अगर (!(vxattr->exists_cb && !vxattr->exists_cb(ci))) अणु
			err = vxattr->getxattr_cb(ci, value, size);
			अगर (size && size < err)
				err = -दुस्फल;
		पूर्ण
		वापस err;
	पूर्ण

	req_mask = __get_request_mask(inode);

	spin_lock(&ci->i_ceph_lock);
	करोut("getxattr %p name '%s' ver=%lld index_ver=%lld\n", inode, name,
	     ci->i_xattrs.version, ci->i_xattrs.index_version);

	अगर (ci->i_xattrs.version == 0 ||
	    !((req_mask & CEPH_CAP_XATTR_SHARED) ||
	      __ceph_caps_issued_mask_metric(ci, CEPH_CAP_XATTR_SHARED, 1))) अणु
		spin_unlock(&ci->i_ceph_lock);

		/* security module माला_लो xattr जबतक filling trace */
		अगर (current->journal_info) अणु
			pr_warn_ratelimited("sync getxattr %p "
					    "during filling trace\n", inode);
			वापस -EBUSY;
		पूर्ण

		/* get xattrs from mds (अगर we करोn't alपढ़ोy have them) */
		err = ceph_करो_getattr(inode, CEPH_STAT_CAP_XATTR, true);
		अगर (err)
			वापस err;
		spin_lock(&ci->i_ceph_lock);
	पूर्ण

	err = __build_xattrs(inode);
	अगर (err < 0)
		जाओ out;

	err = -ENODATA;  /* == ENOATTR */
	xattr = __get_xattr(ci, name);
	अगर (!xattr)
		जाओ out;

	err = -दुस्फल;
	अगर (size && size < xattr->val_len)
		जाओ out;

	err = xattr->val_len;
	अगर (size == 0)
		जाओ out;

	स_नकल(value, xattr->val, xattr->val_len);

	अगर (current->journal_info &&
	    !म_भेदन(name, XATTR_SECURITY_PREFIX, XATTR_SECURITY_PREFIX_LEN) &&
	    security_ismaclabel(name + XATTR_SECURITY_PREFIX_LEN))
		ci->i_ceph_flags |= CEPH_I_SEC_INITED;
out:
	spin_unlock(&ci->i_ceph_lock);
	वापस err;
पूर्ण

sमाप_प्रकार ceph_listxattr(काष्ठा dentry *dentry, अक्षर *names, माप_प्रकार size)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	bool len_only = (size == 0);
	u32 namelen;
	पूर्णांक err;

	spin_lock(&ci->i_ceph_lock);
	करोut("listxattr %p ver=%lld index_ver=%lld\n", inode,
	     ci->i_xattrs.version, ci->i_xattrs.index_version);

	अगर (ci->i_xattrs.version == 0 ||
	    !__ceph_caps_issued_mask_metric(ci, CEPH_CAP_XATTR_SHARED, 1)) अणु
		spin_unlock(&ci->i_ceph_lock);
		err = ceph_करो_getattr(inode, CEPH_STAT_CAP_XATTR, true);
		अगर (err)
			वापस err;
		spin_lock(&ci->i_ceph_lock);
	पूर्ण

	err = __build_xattrs(inode);
	अगर (err < 0)
		जाओ out;

	/* add 1 byte क्रम each xattr due to the null termination */
	namelen = ci->i_xattrs.names_size + ci->i_xattrs.count;
	अगर (!len_only) अणु
		अगर (namelen > size) अणु
			err = -दुस्फल;
			जाओ out;
		पूर्ण
		names = __copy_xattr_names(ci, names);
		size -= namelen;
	पूर्ण
	err = namelen;
out:
	spin_unlock(&ci->i_ceph_lock);
	वापस err;
पूर्ण

अटल पूर्णांक ceph_sync_setxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			      स्थिर अक्षर *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(inode->i_sb);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_mds_request *req;
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	काष्ठा ceph_osd_client *osdc = &fsc->client->osdc;
	काष्ठा ceph_pagelist *pagelist = शून्य;
	पूर्णांक op = CEPH_MDS_OP_SETXATTR;
	पूर्णांक err;

	अगर (size > 0) अणु
		/* copy value पूर्णांकo pagelist */
		pagelist = ceph_pagelist_alloc(GFP_NOFS);
		अगर (!pagelist)
			वापस -ENOMEM;

		err = ceph_pagelist_append(pagelist, value, size);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अगर (!value) अणु
		अगर (flags & CEPH_XATTR_REPLACE)
			op = CEPH_MDS_OP_RMXATTR;
		अन्यथा
			flags |= CEPH_XATTR_REMOVE;
	पूर्ण

	करोut("setxattr value=%.*s\n", (पूर्णांक)size, value);

	/* करो request */
	req = ceph_mdsc_create_request(mdsc, op, USE_AUTH_MDS);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->r_path2 = kstrdup(name, GFP_NOFS);
	अगर (!req->r_path2) अणु
		ceph_mdsc_put_request(req);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (op == CEPH_MDS_OP_SETXATTR) अणु
		req->r_args.setxattr.flags = cpu_to_le32(flags);
		req->r_args.setxattr.osdmap_epoch =
			cpu_to_le32(osdc->osdmap->epoch);
		req->r_pagelist = pagelist;
		pagelist = शून्य;
	पूर्ण

	req->r_inode = inode;
	ihold(inode);
	req->r_num_caps = 1;
	req->r_inode_drop = CEPH_CAP_XATTR_SHARED;

	करोut("xattr.ver (before): %lld\n", ci->i_xattrs.version);
	err = ceph_mdsc_करो_request(mdsc, शून्य, req);
	ceph_mdsc_put_request(req);
	करोut("xattr.ver (after): %lld\n", ci->i_xattrs.version);

out:
	अगर (pagelist)
		ceph_pagelist_release(pagelist);
	वापस err;
पूर्ण

पूर्णांक __ceph_setxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा ceph_vxattr *vxattr;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_client(inode->i_sb)->mdsc;
	काष्ठा ceph_cap_flush *pपुनः_स्मृति_cf = शून्य;
	काष्ठा ceph_buffer *old_blob = शून्य;
	पूर्णांक issued;
	पूर्णांक err;
	पूर्णांक dirty = 0;
	पूर्णांक name_len = म_माप(name);
	पूर्णांक val_len = size;
	अक्षर *newname = शून्य;
	अक्षर *newval = शून्य;
	काष्ठा ceph_inode_xattr *xattr = शून्य;
	पूर्णांक required_blob_size;
	bool check_realm = false;
	bool lock_snap_rwsem = false;

	अगर (ceph_snap(inode) != CEPH_NOSNAP)
		वापस -EROFS;

	vxattr = ceph_match_vxattr(inode, name);
	अगर (vxattr) अणु
		अगर (vxattr->flags & VXATTR_FLAG_READONLY)
			वापस -EOPNOTSUPP;
		अगर (value && !म_भेदन(vxattr->name, "ceph.quota", 10))
			check_realm = true;
	पूर्ण

	/* pass any unhandled ceph.* xattrs through to the MDS */
	अगर (!म_भेदन(name, XATTR_CEPH_PREFIX, XATTR_CEPH_PREFIX_LEN))
		जाओ करो_sync_unlocked;

	/* pपुनः_स्मृतिate memory क्रम xattr name, value, index node */
	err = -ENOMEM;
	newname = kmemdup(name, name_len + 1, GFP_NOFS);
	अगर (!newname)
		जाओ out;

	अगर (val_len) अणु
		newval = kmemdup(value, val_len, GFP_NOFS);
		अगर (!newval)
			जाओ out;
	पूर्ण

	xattr = kदो_स्मृति(माप(काष्ठा ceph_inode_xattr), GFP_NOFS);
	अगर (!xattr)
		जाओ out;

	pपुनः_स्मृति_cf = ceph_alloc_cap_flush();
	अगर (!pपुनः_स्मृति_cf)
		जाओ out;

	spin_lock(&ci->i_ceph_lock);
retry:
	issued = __ceph_caps_issued(ci, शून्य);
	अगर (ci->i_xattrs.version == 0 || !(issued & CEPH_CAP_XATTR_EXCL))
		जाओ करो_sync;

	अगर (!lock_snap_rwsem && !ci->i_head_snapc) अणु
		lock_snap_rwsem = true;
		अगर (!करोwn_पढ़ो_trylock(&mdsc->snap_rwsem)) अणु
			spin_unlock(&ci->i_ceph_lock);
			करोwn_पढ़ो(&mdsc->snap_rwsem);
			spin_lock(&ci->i_ceph_lock);
			जाओ retry;
		पूर्ण
	पूर्ण

	करोut("setxattr %p name '%s' issued %s\n", inode, name,
	     ceph_cap_string(issued));
	__build_xattrs(inode);

	required_blob_size = __get_required_blob_size(ci, name_len, val_len);

	अगर (!ci->i_xattrs.pपुनः_स्मृति_blob ||
	    required_blob_size > ci->i_xattrs.pपुनः_स्मृति_blob->alloc_len) अणु
		काष्ठा ceph_buffer *blob;

		spin_unlock(&ci->i_ceph_lock);
		ceph_buffer_put(old_blob); /* Shouldn't be required */
		करोut(" pre-allocating new blob size=%d\n", required_blob_size);
		blob = ceph_buffer_new(required_blob_size, GFP_NOFS);
		अगर (!blob)
			जाओ करो_sync_unlocked;
		spin_lock(&ci->i_ceph_lock);
		/* pपुनः_स्मृति_blob can't be released जबतक holding i_ceph_lock */
		अगर (ci->i_xattrs.pपुनः_स्मृति_blob)
			old_blob = ci->i_xattrs.pपुनः_स्मृति_blob;
		ci->i_xattrs.pपुनः_स्मृति_blob = blob;
		जाओ retry;
	पूर्ण

	err = __set_xattr(ci, newname, name_len, newval, val_len,
			  flags, value ? 1 : -1, &xattr);

	अगर (!err) अणु
		dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_XATTR_EXCL,
					       &pपुनः_स्मृति_cf);
		ci->i_xattrs.dirty = true;
		inode->i_स_समय = current_समय(inode);
	पूर्ण

	spin_unlock(&ci->i_ceph_lock);
	ceph_buffer_put(old_blob);
	अगर (lock_snap_rwsem)
		up_पढ़ो(&mdsc->snap_rwsem);
	अगर (dirty)
		__mark_inode_dirty(inode, dirty);
	ceph_मुक्त_cap_flush(pपुनः_स्मृति_cf);
	वापस err;

करो_sync:
	spin_unlock(&ci->i_ceph_lock);
करो_sync_unlocked:
	अगर (lock_snap_rwsem)
		up_पढ़ो(&mdsc->snap_rwsem);

	/* security module set xattr जबतक filling trace */
	अगर (current->journal_info) अणु
		pr_warn_ratelimited("sync setxattr %p "
				    "during filling trace\n", inode);
		err = -EBUSY;
	पूर्ण अन्यथा अणु
		err = ceph_sync_setxattr(inode, name, value, size, flags);
		अगर (err >= 0 && check_realm) अणु
			/* check अगर snaprealm was created क्रम quota inode */
			spin_lock(&ci->i_ceph_lock);
			अगर ((ci->i_max_files || ci->i_max_bytes) &&
			    !(ci->i_snap_realm &&
			      ci->i_snap_realm->ino == ci->i_vino.ino))
				err = -EOPNOTSUPP;
			spin_unlock(&ci->i_ceph_lock);
		पूर्ण
	पूर्ण
out:
	ceph_मुक्त_cap_flush(pपुनः_स्मृति_cf);
	kमुक्त(newname);
	kमुक्त(newval);
	kमुक्त(xattr);
	वापस err;
पूर्ण

अटल पूर्णांक ceph_get_xattr_handler(स्थिर काष्ठा xattr_handler *handler,
				  काष्ठा dentry *dentry, काष्ठा inode *inode,
				  स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	अगर (!ceph_is_valid_xattr(name))
		वापस -EOPNOTSUPP;
	वापस __ceph_getxattr(inode, name, value, size);
पूर्ण

अटल पूर्णांक ceph_set_xattr_handler(स्थिर काष्ठा xattr_handler *handler,
				  काष्ठा user_namespace *mnt_userns,
				  काष्ठा dentry *unused, काष्ठा inode *inode,
				  स्थिर अक्षर *name, स्थिर व्योम *value,
				  माप_प्रकार size, पूर्णांक flags)
अणु
	अगर (!ceph_is_valid_xattr(name))
		वापस -EOPNOTSUPP;
	वापस __ceph_setxattr(inode, name, value, size, flags);
पूर्ण

अटल स्थिर काष्ठा xattr_handler ceph_other_xattr_handler = अणु
	.prefix = "",  /* match any name => handlers called with full name */
	.get = ceph_get_xattr_handler,
	.set = ceph_set_xattr_handler,
पूर्ण;

#अगर_घोषित CONFIG_SECURITY
bool ceph_security_xattr_wanted(काष्ठा inode *in)
अणु
	वापस in->i_security != शून्य;
पूर्ण

bool ceph_security_xattr_deadlock(काष्ठा inode *in)
अणु
	काष्ठा ceph_inode_info *ci;
	bool ret;
	अगर (!in->i_security)
		वापस false;
	ci = ceph_inode(in);
	spin_lock(&ci->i_ceph_lock);
	ret = !(ci->i_ceph_flags & CEPH_I_SEC_INITED) &&
	      !(ci->i_xattrs.version > 0 &&
		__ceph_caps_issued_mask(ci, CEPH_CAP_XATTR_SHARED, 0));
	spin_unlock(&ci->i_ceph_lock);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_CEPH_FS_SECURITY_LABEL
पूर्णांक ceph_security_init_secctx(काष्ठा dentry *dentry, umode_t mode,
			   काष्ठा ceph_acl_sec_ctx *as_ctx)
अणु
	काष्ठा ceph_pagelist *pagelist = as_ctx->pagelist;
	स्थिर अक्षर *name;
	माप_प्रकार name_len;
	पूर्णांक err;

	err = security_dentry_init_security(dentry, mode, &dentry->d_name,
					    &as_ctx->sec_ctx,
					    &as_ctx->sec_ctxlen);
	अगर (err < 0) अणु
		WARN_ON_ONCE(err != -EOPNOTSUPP);
		err = 0; /* करो nothing */
		जाओ out;
	पूर्ण

	err = -ENOMEM;
	अगर (!pagelist) अणु
		pagelist = ceph_pagelist_alloc(GFP_KERNEL);
		अगर (!pagelist)
			जाओ out;
		err = ceph_pagelist_reserve(pagelist, PAGE_SIZE);
		अगर (err)
			जाओ out;
		ceph_pagelist_encode_32(pagelist, 1);
	पूर्ण

	/*
	 * FIXME: Make security_dentry_init_security() generic. Currently
	 * It only supports single security module and only selinux has
	 * dentry_init_security hook.
	 */
	name = XATTR_NAME_SELINUX;
	name_len = म_माप(name);
	err = ceph_pagelist_reserve(pagelist,
				    4 * 2 + name_len + as_ctx->sec_ctxlen);
	अगर (err)
		जाओ out;

	अगर (as_ctx->pagelist) अणु
		/* update count of KV pairs */
		BUG_ON(pagelist->length <= माप(__le32));
		अगर (list_is_singular(&pagelist->head)) अणु
			le32_add_cpu((__le32*)pagelist->mapped_tail, 1);
		पूर्ण अन्यथा अणु
			काष्ठा page *page = list_first_entry(&pagelist->head,
							     काष्ठा page, lru);
			व्योम *addr = kmap_atomic(page);
			le32_add_cpu((__le32*)addr, 1);
			kunmap_atomic(addr);
		पूर्ण
	पूर्ण अन्यथा अणु
		as_ctx->pagelist = pagelist;
	पूर्ण

	ceph_pagelist_encode_32(pagelist, name_len);
	ceph_pagelist_append(pagelist, name, name_len);

	ceph_pagelist_encode_32(pagelist, as_ctx->sec_ctxlen);
	ceph_pagelist_append(pagelist, as_ctx->sec_ctx, as_ctx->sec_ctxlen);

	err = 0;
out:
	अगर (pagelist && !as_ctx->pagelist)
		ceph_pagelist_release(pagelist);
	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_CEPH_FS_SECURITY_LABEL */
#पूर्ण_अगर /* CONFIG_SECURITY */

व्योम ceph_release_acl_sec_ctx(काष्ठा ceph_acl_sec_ctx *as_ctx)
अणु
#अगर_घोषित CONFIG_CEPH_FS_POSIX_ACL
	posix_acl_release(as_ctx->acl);
	posix_acl_release(as_ctx->शेष_acl);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CEPH_FS_SECURITY_LABEL
	security_release_secctx(as_ctx->sec_ctx, as_ctx->sec_ctxlen);
#पूर्ण_अगर
	अगर (as_ctx->pagelist)
		ceph_pagelist_release(as_ctx->pagelist);
पूर्ण

/*
 * List of handlers क्रम synthetic प्रणाली.* attributes. Other
 * attributes are handled directly.
 */
स्थिर काष्ठा xattr_handler *ceph_xattr_handlers[] = अणु
#अगर_घोषित CONFIG_CEPH_FS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	&ceph_other_xattr_handler,
	शून्य,
पूर्ण;
