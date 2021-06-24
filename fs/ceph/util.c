<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Some non-अंतरभूत ceph helpers
 */
#समावेश <linux/module.h>
#समावेश <linux/ceph/types.h>

/*
 * वापस true अगर @layout appears to be valid
 */
पूर्णांक ceph_file_layout_is_valid(स्थिर काष्ठा ceph_file_layout *layout)
अणु
	__u32 su = layout->stripe_unit;
	__u32 sc = layout->stripe_count;
	__u32 os = layout->object_size;

	/* stripe unit, object size must be non-zero, 64k increment */
	अगर (!su || (su & (CEPH_MIN_STRIPE_UNIT-1)))
		वापस 0;
	अगर (!os || (os & (CEPH_MIN_STRIPE_UNIT-1)))
		वापस 0;
	/* object size must be a multiple of stripe unit */
	अगर (os < su || os % su)
		वापस 0;
	/* stripe count must be non-zero */
	अगर (!sc)
		वापस 0;
	वापस 1;
पूर्ण

व्योम ceph_file_layout_from_legacy(काष्ठा ceph_file_layout *fl,
				  काष्ठा ceph_file_layout_legacy *legacy)
अणु
	fl->stripe_unit = le32_to_cpu(legacy->fl_stripe_unit);
	fl->stripe_count = le32_to_cpu(legacy->fl_stripe_count);
	fl->object_size = le32_to_cpu(legacy->fl_object_size);
	fl->pool_id = le32_to_cpu(legacy->fl_pg_pool);
	अगर (fl->pool_id == 0 && fl->stripe_unit == 0 &&
	    fl->stripe_count == 0 && fl->object_size == 0)
		fl->pool_id = -1;
पूर्ण

व्योम ceph_file_layout_to_legacy(काष्ठा ceph_file_layout *fl,
				काष्ठा ceph_file_layout_legacy *legacy)
अणु
	legacy->fl_stripe_unit = cpu_to_le32(fl->stripe_unit);
	legacy->fl_stripe_count = cpu_to_le32(fl->stripe_count);
	legacy->fl_object_size = cpu_to_le32(fl->object_size);
	अगर (fl->pool_id >= 0)
		legacy->fl_pg_pool = cpu_to_le32(fl->pool_id);
	अन्यथा
		legacy->fl_pg_pool = 0;
पूर्ण

पूर्णांक ceph_flags_to_mode(पूर्णांक flags)
अणु
	पूर्णांक mode;

#अगर_घोषित O_सूचीECTORY  /* fixme */
	अगर ((flags & O_सूचीECTORY) == O_सूचीECTORY)
		वापस CEPH_खाता_MODE_PIN;
#पूर्ण_अगर

	चयन (flags & O_ACCMODE) अणु
	हाल O_WRONLY:
		mode = CEPH_खाता_MODE_WR;
		अवरोध;
	हाल O_RDONLY:
		mode = CEPH_खाता_MODE_RD;
		अवरोध;
	हाल O_RDWR:
	हाल O_ACCMODE: /* this is what the VFS करोes */
		mode = CEPH_खाता_MODE_RDWR;
		अवरोध;
	पूर्ण
#अगर_घोषित O_LAZY
	अगर (flags & O_LAZY)
		mode |= CEPH_खाता_MODE_LAZY;
#पूर्ण_अगर

	वापस mode;
पूर्ण

पूर्णांक ceph_caps_क्रम_mode(पूर्णांक mode)
अणु
	पूर्णांक caps = CEPH_CAP_PIN;

	अगर (mode & CEPH_खाता_MODE_RD)
		caps |= CEPH_CAP_खाता_SHARED |
			CEPH_CAP_खाता_RD | CEPH_CAP_खाता_CACHE;
	अगर (mode & CEPH_खाता_MODE_WR)
		caps |= CEPH_CAP_खाता_EXCL |
			CEPH_CAP_खाता_WR | CEPH_CAP_खाता_BUFFER |
			CEPH_CAP_AUTH_SHARED | CEPH_CAP_AUTH_EXCL |
			CEPH_CAP_XATTR_SHARED | CEPH_CAP_XATTR_EXCL;
	अगर (mode & CEPH_खाता_MODE_LAZY)
		caps |= CEPH_CAP_खाता_LAZYIO;

	वापस caps;
पूर्ण
