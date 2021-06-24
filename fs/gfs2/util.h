<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __UTIL_DOT_H__
#घोषणा __UTIL_DOT_H__

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#पूर्ण_अगर

#समावेश <linux/mempool.h>

#समावेश "incore.h"

#घोषणा fs_emerg(fs, fmt, ...)						\
	pr_emerg("fsid=%s: " fmt, (fs)->sd_fsname, ##__VA_ARGS__)
#घोषणा fs_warn(fs, fmt, ...)						\
	pr_warn("fsid=%s: " fmt, (fs)->sd_fsname, ##__VA_ARGS__)
#घोषणा fs_err(fs, fmt, ...)						\
	pr_err("fsid=%s: " fmt, (fs)->sd_fsname, ##__VA_ARGS__)
#घोषणा fs_info(fs, fmt, ...)						\
	pr_info("fsid=%s: " fmt, (fs)->sd_fsname, ##__VA_ARGS__)

व्योम gfs2_निश्चित_i(काष्ठा gfs2_sbd *sdp);

#घोषणा gfs2_निश्चित(sdp, निश्चितion) \
करो अणु \
	अगर (unlikely(!(निश्चितion))) अणु \
		gfs2_निश्चित_i(sdp); \
		BUG(); \
        पूर्ण \
पूर्ण जबतक (0)


व्योम gfs2_निश्चित_withdraw_i(काष्ठा gfs2_sbd *sdp, अक्षर *निश्चितion,
			    स्थिर अक्षर *function, अक्षर *file, अचिन्हित पूर्णांक line,
			    bool delayed);

#घोषणा gfs2_निश्चित_withdraw(sdp, निश्चितion) \
	(अणु \
		bool _bool = (निश्चितion); \
		अगर (unlikely(!_bool)) \
			gfs2_निश्चित_withdraw_i((sdp), #निश्चितion, \
					__func__, __खाता__, __LINE__, false); \
		!_bool; \
	पूर्ण)

#घोषणा gfs2_निश्चित_withdraw_delayed(sdp, निश्चितion) \
	(अणु \
		bool _bool = (निश्चितion); \
		अगर (unlikely(!_bool)) \
			gfs2_निश्चित_withdraw_i((sdp), #निश्चितion, \
					__func__, __खाता__, __LINE__, true); \
		!_bool; \
	पूर्ण)

व्योम gfs2_निश्चित_warn_i(काष्ठा gfs2_sbd *sdp, अक्षर *निश्चितion,
			स्थिर अक्षर *function, अक्षर *file, अचिन्हित पूर्णांक line);

#घोषणा gfs2_निश्चित_warn(sdp, निश्चितion) \
	(अणु \
		bool _bool = (निश्चितion); \
		अगर (unlikely(!_bool)) \
			gfs2_निश्चित_warn_i((sdp), #निश्चितion, \
					__func__, __खाता__, __LINE__); \
		!_bool; \
	पूर्ण)

व्योम gfs2_consist_i(काष्ठा gfs2_sbd *sdp,
		    स्थिर अक्षर *function, अक्षर *file, अचिन्हित पूर्णांक line);

#घोषणा gfs2_consist(sdp) \
gfs2_consist_i((sdp), __func__, __खाता__, __LINE__)


व्योम gfs2_consist_inode_i(काष्ठा gfs2_inode *ip,
			  स्थिर अक्षर *function, अक्षर *file, अचिन्हित पूर्णांक line);

#घोषणा gfs2_consist_inode(ip) \
gfs2_consist_inode_i((ip), __func__, __खाता__, __LINE__)


व्योम gfs2_consist_rgrpd_i(काष्ठा gfs2_rgrpd *rgd,
			  स्थिर अक्षर *function, अक्षर *file, अचिन्हित पूर्णांक line);

#घोषणा gfs2_consist_rgrpd(rgd) \
gfs2_consist_rgrpd_i((rgd), __func__, __खाता__, __LINE__)


पूर्णांक gfs2_meta_check_ii(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh,
		       स्थिर अक्षर *type, स्थिर अक्षर *function,
		       अक्षर *file, अचिन्हित पूर्णांक line);

अटल अंतरभूत पूर्णांक gfs2_meta_check(काष्ठा gfs2_sbd *sdp,
				    काष्ठा buffer_head *bh)
अणु
	काष्ठा gfs2_meta_header *mh = (काष्ठा gfs2_meta_header *)bh->b_data;
	u32 magic = be32_to_cpu(mh->mh_magic);
	अगर (unlikely(magic != GFS2_MAGIC)) अणु
		fs_err(sdp, "Magic number missing at %llu\n",
		       (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक gfs2_metatype_check_ii(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh,
			   u16 type, u16 t,
			   स्थिर अक्षर *function,
			   अक्षर *file, अचिन्हित पूर्णांक line);

अटल अंतरभूत पूर्णांक gfs2_metatype_check_i(काष्ठा gfs2_sbd *sdp,
					काष्ठा buffer_head *bh,
					u16 type,
					स्थिर अक्षर *function,
					अक्षर *file, अचिन्हित पूर्णांक line)
अणु
	काष्ठा gfs2_meta_header *mh = (काष्ठा gfs2_meta_header *)bh->b_data;
	u32 magic = be32_to_cpu(mh->mh_magic);
	u16 t = be32_to_cpu(mh->mh_type);
	अगर (unlikely(magic != GFS2_MAGIC))
		वापस gfs2_meta_check_ii(sdp, bh, "magic number", function,
					  file, line);
        अगर (unlikely(t != type))
		वापस gfs2_metatype_check_ii(sdp, bh, type, t, function,
					      file, line);
	वापस 0;
पूर्ण

#घोषणा gfs2_metatype_check(sdp, bh, type) \
gfs2_metatype_check_i((sdp), (bh), (type), __func__, __खाता__, __LINE__)

अटल अंतरभूत व्योम gfs2_metatype_set(काष्ठा buffer_head *bh, u16 type,
				     u16 क्रमmat)
अणु
	काष्ठा gfs2_meta_header *mh;
	mh = (काष्ठा gfs2_meta_header *)bh->b_data;
	mh->mh_type = cpu_to_be32(type);
	mh->mh_क्रमmat = cpu_to_be32(क्रमmat);
पूर्ण


पूर्णांक gfs2_io_error_i(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *function,
		    अक्षर *file, अचिन्हित पूर्णांक line);

बाह्य पूर्णांक check_journal_clean(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_jdesc *jd,
			       bool verbose);
बाह्य पूर्णांक gfs2_मुक्तze_lock(काष्ठा gfs2_sbd *sdp,
			    काष्ठा gfs2_holder *मुक्तze_gh, पूर्णांक caller_flags);
बाह्य व्योम gfs2_मुक्तze_unlock(काष्ठा gfs2_holder *मुक्तze_gh);

#घोषणा gfs2_io_error(sdp) \
gfs2_io_error_i((sdp), __func__, __खाता__, __LINE__)


व्योम gfs2_io_error_bh_i(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh,
			स्थिर अक्षर *function, अक्षर *file, अचिन्हित पूर्णांक line,
			bool withdraw);

#घोषणा gfs2_io_error_bh_wd(sdp, bh) \
gfs2_io_error_bh_i((sdp), (bh), __func__, __खाता__, __LINE__, true)

#घोषणा gfs2_io_error_bh(sdp, bh) \
gfs2_io_error_bh_i((sdp), (bh), __func__, __खाता__, __LINE__, false)


बाह्य काष्ठा kmem_cache *gfs2_glock_cachep;
बाह्य काष्ठा kmem_cache *gfs2_glock_aspace_cachep;
बाह्य काष्ठा kmem_cache *gfs2_inode_cachep;
बाह्य काष्ठा kmem_cache *gfs2_bufdata_cachep;
बाह्य काष्ठा kmem_cache *gfs2_rgrpd_cachep;
बाह्य काष्ठा kmem_cache *gfs2_quotad_cachep;
बाह्य काष्ठा kmem_cache *gfs2_qadata_cachep;
बाह्य काष्ठा kmem_cache *gfs2_trans_cachep;
बाह्य mempool_t *gfs2_page_pool;
बाह्य काष्ठा workqueue_काष्ठा *gfs2_control_wq;

अटल अंतरभूत अचिन्हित पूर्णांक gfs2_tune_get_i(काष्ठा gfs2_tune *gt,
					   अचिन्हित पूर्णांक *p)
अणु
	अचिन्हित पूर्णांक x;
	spin_lock(&gt->gt_spin);
	x = *p;
	spin_unlock(&gt->gt_spin);
	वापस x;
पूर्ण

/**
 * gfs2_withdraw_delayed - withdraw as soon as possible without deadlocks
 * @sdp: the superblock
 */
अटल अंतरभूत व्योम gfs2_withdraw_delayed(काष्ठा gfs2_sbd *sdp)
अणु
	set_bit(SDF_WITHDRAWING, &sdp->sd_flags);
पूर्ण

/**
 * gfs2_withdrawn - test whether the file प्रणाली is withdrawing or withdrawn
 * @sdp: the superblock
 */
अटल अंतरभूत bool gfs2_withdrawn(काष्ठा gfs2_sbd *sdp)
अणु
	वापस test_bit(SDF_WITHDRAWN, &sdp->sd_flags) ||
		test_bit(SDF_WITHDRAWING, &sdp->sd_flags);
पूर्ण

/**
 * gfs2_withdrawing - check अगर a withdraw is pending
 * @sdp: the superblock
 */
अटल अंतरभूत bool gfs2_withdrawing(काष्ठा gfs2_sbd *sdp)
अणु
	वापस test_bit(SDF_WITHDRAWING, &sdp->sd_flags) &&
	       !test_bit(SDF_WITHDRAWN, &sdp->sd_flags);
पूर्ण

#घोषणा gfs2_tune_get(sdp, field) \
gfs2_tune_get_i(&(sdp)->sd_tune, &(sdp)->sd_tune.field)

__म_लिखो(2, 3)
व्योम gfs2_lm(काष्ठा gfs2_sbd *sdp, स्थिर अक्षर *fmt, ...);
पूर्णांक gfs2_withdraw(काष्ठा gfs2_sbd *sdp);

#पूर्ण_अगर /* __UTIL_DOT_H__ */
