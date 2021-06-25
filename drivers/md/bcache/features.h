<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _BCACHE_FEATURES_H
#घोषणा _BCACHE_FEATURES_H

#समावेश <linux/bcache.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#घोषणा BCH_FEATURE_COMPAT		0
#घोषणा BCH_FEATURE_RO_COMPAT		1
#घोषणा BCH_FEATURE_INCOMPAT		2
#घोषणा BCH_FEATURE_TYPE_MASK		0x03

/* Feature set definition */
/* Incompat feature set */
/* 32bit bucket size, obsoleted */
#घोषणा BCH_FEATURE_INCOMPAT_OBSO_LARGE_BUCKET		0x0001
/* real bucket size is (1 << bucket_size) */
#घोषणा BCH_FEATURE_INCOMPAT_LOG_LARGE_BUCKET_SIZE	0x0002

#घोषणा BCH_FEATURE_COMPAT_SUPP		0
#घोषणा BCH_FEATURE_RO_COMPAT_SUPP	0
#घोषणा BCH_FEATURE_INCOMPAT_SUPP	(BCH_FEATURE_INCOMPAT_OBSO_LARGE_BUCKET| \
					 BCH_FEATURE_INCOMPAT_LOG_LARGE_BUCKET_SIZE)

#घोषणा BCH_HAS_COMPAT_FEATURE(sb, mask) \
		((sb)->feature_compat & (mask))
#घोषणा BCH_HAS_RO_COMPAT_FEATURE(sb, mask) \
		((sb)->feature_ro_compat & (mask))
#घोषणा BCH_HAS_INCOMPAT_FEATURE(sb, mask) \
		((sb)->feature_incompat & (mask))

#घोषणा BCH_FEATURE_COMPAT_FUNCS(name, flagname) \
अटल अंतरभूत पूर्णांक bch_has_feature_##name(काष्ठा cache_sb *sb) \
अणु \
	अगर (sb->version < BCACHE_SB_VERSION_CDEV_WITH_FEATURES) \
		वापस 0; \
	वापस (((sb)->feature_compat & \
		BCH##_FEATURE_COMPAT_##flagname) != 0); \
पूर्ण \
अटल अंतरभूत व्योम bch_set_feature_##name(काष्ठा cache_sb *sb) \
अणु \
	(sb)->feature_compat |= \
		BCH##_FEATURE_COMPAT_##flagname; \
पूर्ण \
अटल अंतरभूत व्योम bch_clear_feature_##name(काष्ठा cache_sb *sb) \
अणु \
	(sb)->feature_compat &= \
		~BCH##_FEATURE_COMPAT_##flagname; \
पूर्ण

#घोषणा BCH_FEATURE_RO_COMPAT_FUNCS(name, flagname) \
अटल अंतरभूत पूर्णांक bch_has_feature_##name(काष्ठा cache_sb *sb) \
अणु \
	अगर (sb->version < BCACHE_SB_VERSION_CDEV_WITH_FEATURES) \
		वापस 0; \
	वापस (((sb)->feature_ro_compat & \
		BCH##_FEATURE_RO_COMPAT_##flagname) != 0); \
पूर्ण \
अटल अंतरभूत व्योम bch_set_feature_##name(काष्ठा cache_sb *sb) \
अणु \
	(sb)->feature_ro_compat |= \
		BCH##_FEATURE_RO_COMPAT_##flagname; \
पूर्ण \
अटल अंतरभूत व्योम bch_clear_feature_##name(काष्ठा cache_sb *sb) \
अणु \
	(sb)->feature_ro_compat &= \
		~BCH##_FEATURE_RO_COMPAT_##flagname; \
पूर्ण

#घोषणा BCH_FEATURE_INCOMPAT_FUNCS(name, flagname) \
अटल अंतरभूत पूर्णांक bch_has_feature_##name(काष्ठा cache_sb *sb) \
अणु \
	अगर (sb->version < BCACHE_SB_VERSION_CDEV_WITH_FEATURES) \
		वापस 0; \
	वापस (((sb)->feature_incompat & \
		BCH##_FEATURE_INCOMPAT_##flagname) != 0); \
पूर्ण \
अटल अंतरभूत व्योम bch_set_feature_##name(काष्ठा cache_sb *sb) \
अणु \
	(sb)->feature_incompat |= \
		BCH##_FEATURE_INCOMPAT_##flagname; \
पूर्ण \
अटल अंतरभूत व्योम bch_clear_feature_##name(काष्ठा cache_sb *sb) \
अणु \
	(sb)->feature_incompat &= \
		~BCH##_FEATURE_INCOMPAT_##flagname; \
पूर्ण

BCH_FEATURE_INCOMPAT_FUNCS(obso_large_bucket, OBSO_LARGE_BUCKET);
BCH_FEATURE_INCOMPAT_FUNCS(large_bucket, LOG_LARGE_BUCKET_SIZE);

अटल अंतरभूत bool bch_has_unknown_compat_features(काष्ठा cache_sb *sb)
अणु
	वापस ((sb->feature_compat & ~BCH_FEATURE_COMPAT_SUPP) != 0);
पूर्ण

अटल अंतरभूत bool bch_has_unknown_ro_compat_features(काष्ठा cache_sb *sb)
अणु
	वापस ((sb->feature_ro_compat & ~BCH_FEATURE_RO_COMPAT_SUPP) != 0);
पूर्ण

अटल अंतरभूत bool bch_has_unknown_incompat_features(काष्ठा cache_sb *sb)
अणु
	वापस ((sb->feature_incompat & ~BCH_FEATURE_INCOMPAT_SUPP) != 0);
पूर्ण

पूर्णांक bch_prपूर्णांक_cache_set_feature_compat(काष्ठा cache_set *c, अक्षर *buf, पूर्णांक size);
पूर्णांक bch_prपूर्णांक_cache_set_feature_ro_compat(काष्ठा cache_set *c, अक्षर *buf, पूर्णांक size);
पूर्णांक bch_prपूर्णांक_cache_set_feature_incompat(काष्ठा cache_set *c, अक्षर *buf, पूर्णांक size);

#पूर्ण_अगर
