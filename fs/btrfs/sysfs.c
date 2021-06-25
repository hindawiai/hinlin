<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/bug.h>
#समावेश <crypto/hash.h>

#समावेश "ctree.h"
#समावेश "discard.h"
#समावेश "disk-io.h"
#समावेश "send.h"
#समावेश "transaction.h"
#समावेश "sysfs.h"
#समावेश "volumes.h"
#समावेश "space-info.h"
#समावेश "block-group.h"
#समावेश "qgroup.h"

काष्ठा btrfs_feature_attr अणु
	काष्ठा kobj_attribute kobj_attr;
	क्रमागत btrfs_feature_set feature_set;
	u64 feature_bit;
पूर्ण;

/* For raid type sysfs entries */
काष्ठा raid_kobject अणु
	u64 flags;
	काष्ठा kobject kobj;
पूर्ण;

#घोषणा __INIT_KOBJ_ATTR(_name, _mode, _show, _store)			\
अणु									\
	.attr	= अणु .name = __stringअगरy(_name), .mode = _mode पूर्ण,	\
	.show	= _show,						\
	.store	= _store,						\
पूर्ण

#घोषणा BTRFS_ATTR_RW(_prefix, _name, _show, _store)			\
	अटल काष्ठा kobj_attribute btrfs_attr_##_prefix##_##_name =	\
			__INIT_KOBJ_ATTR(_name, 0644, _show, _store)

#घोषणा BTRFS_ATTR(_prefix, _name, _show)				\
	अटल काष्ठा kobj_attribute btrfs_attr_##_prefix##_##_name =	\
			__INIT_KOBJ_ATTR(_name, 0444, _show, शून्य)

#घोषणा BTRFS_ATTR_PTR(_prefix, _name)					\
	(&btrfs_attr_##_prefix##_##_name.attr)

#घोषणा BTRFS_FEAT_ATTR(_name, _feature_set, _feature_prefix, _feature_bit)  \
अटल काष्ठा btrfs_feature_attr btrfs_attr_features_##_name = अणु	     \
	.kobj_attr = __INIT_KOBJ_ATTR(_name, S_IRUGO,			     \
				      btrfs_feature_attr_show,		     \
				      btrfs_feature_attr_store),	     \
	.feature_set	= _feature_set,					     \
	.feature_bit	= _feature_prefix ##_## _feature_bit,		     \
पूर्ण
#घोषणा BTRFS_FEAT_ATTR_PTR(_name)					     \
	(&btrfs_attr_features_##_name.kobj_attr.attr)

#घोषणा BTRFS_FEAT_ATTR_COMPAT(name, feature) \
	BTRFS_FEAT_ATTR(name, FEAT_COMPAT, BTRFS_FEATURE_COMPAT, feature)
#घोषणा BTRFS_FEAT_ATTR_COMPAT_RO(name, feature) \
	BTRFS_FEAT_ATTR(name, FEAT_COMPAT_RO, BTRFS_FEATURE_COMPAT_RO, feature)
#घोषणा BTRFS_FEAT_ATTR_INCOMPAT(name, feature) \
	BTRFS_FEAT_ATTR(name, FEAT_INCOMPAT, BTRFS_FEATURE_INCOMPAT, feature)

अटल अंतरभूत काष्ठा btrfs_fs_info *to_fs_info(काष्ठा kobject *kobj);
अटल अंतरभूत काष्ठा btrfs_fs_devices *to_fs_devs(काष्ठा kobject *kobj);

अटल काष्ठा btrfs_feature_attr *to_btrfs_feature_attr(काष्ठा kobj_attribute *a)
अणु
	वापस container_of(a, काष्ठा btrfs_feature_attr, kobj_attr);
पूर्ण

अटल काष्ठा kobj_attribute *attr_to_btrfs_attr(काष्ठा attribute *attr)
अणु
	वापस container_of(attr, काष्ठा kobj_attribute, attr);
पूर्ण

अटल काष्ठा btrfs_feature_attr *attr_to_btrfs_feature_attr(
		काष्ठा attribute *attr)
अणु
	वापस to_btrfs_feature_attr(attr_to_btrfs_attr(attr));
पूर्ण

अटल u64 get_features(काष्ठा btrfs_fs_info *fs_info,
			क्रमागत btrfs_feature_set set)
अणु
	काष्ठा btrfs_super_block *disk_super = fs_info->super_copy;
	अगर (set == FEAT_COMPAT)
		वापस btrfs_super_compat_flags(disk_super);
	अन्यथा अगर (set == FEAT_COMPAT_RO)
		वापस btrfs_super_compat_ro_flags(disk_super);
	अन्यथा
		वापस btrfs_super_incompat_flags(disk_super);
पूर्ण

अटल व्योम set_features(काष्ठा btrfs_fs_info *fs_info,
			 क्रमागत btrfs_feature_set set, u64 features)
अणु
	काष्ठा btrfs_super_block *disk_super = fs_info->super_copy;
	अगर (set == FEAT_COMPAT)
		btrfs_set_super_compat_flags(disk_super, features);
	अन्यथा अगर (set == FEAT_COMPAT_RO)
		btrfs_set_super_compat_ro_flags(disk_super, features);
	अन्यथा
		btrfs_set_super_incompat_flags(disk_super, features);
पूर्ण

अटल पूर्णांक can_modअगरy_feature(काष्ठा btrfs_feature_attr *fa)
अणु
	पूर्णांक val = 0;
	u64 set, clear;
	चयन (fa->feature_set) अणु
	हाल FEAT_COMPAT:
		set = BTRFS_FEATURE_COMPAT_SAFE_SET;
		clear = BTRFS_FEATURE_COMPAT_SAFE_CLEAR;
		अवरोध;
	हाल FEAT_COMPAT_RO:
		set = BTRFS_FEATURE_COMPAT_RO_SAFE_SET;
		clear = BTRFS_FEATURE_COMPAT_RO_SAFE_CLEAR;
		अवरोध;
	हाल FEAT_INCOMPAT:
		set = BTRFS_FEATURE_INCOMPAT_SAFE_SET;
		clear = BTRFS_FEATURE_INCOMPAT_SAFE_CLEAR;
		अवरोध;
	शेष:
		pr_warn("btrfs: sysfs: unknown feature set %d\n",
				fa->feature_set);
		वापस 0;
	पूर्ण

	अगर (set & fa->feature_bit)
		val |= 1;
	अगर (clear & fa->feature_bit)
		val |= 2;

	वापस val;
पूर्ण

अटल sमाप_प्रकार btrfs_feature_attr_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	पूर्णांक val = 0;
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);
	काष्ठा btrfs_feature_attr *fa = to_btrfs_feature_attr(a);
	अगर (fs_info) अणु
		u64 features = get_features(fs_info, fa->feature_set);
		अगर (features & fa->feature_bit)
			val = 1;
	पूर्ण अन्यथा
		val = can_modअगरy_feature(fa);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार btrfs_feature_attr_store(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *a,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_feature_attr *fa = to_btrfs_feature_attr(a);
	u64 features, set, clear;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	fs_info = to_fs_info(kobj);
	अगर (!fs_info)
		वापस -EPERM;

	अगर (sb_rकरोnly(fs_info->sb))
		वापस -EROFS;

	ret = kम_से_अदीर्घ(skip_spaces(buf), 0, &val);
	अगर (ret)
		वापस ret;

	अगर (fa->feature_set == FEAT_COMPAT) अणु
		set = BTRFS_FEATURE_COMPAT_SAFE_SET;
		clear = BTRFS_FEATURE_COMPAT_SAFE_CLEAR;
	पूर्ण अन्यथा अगर (fa->feature_set == FEAT_COMPAT_RO) अणु
		set = BTRFS_FEATURE_COMPAT_RO_SAFE_SET;
		clear = BTRFS_FEATURE_COMPAT_RO_SAFE_CLEAR;
	पूर्ण अन्यथा अणु
		set = BTRFS_FEATURE_INCOMPAT_SAFE_SET;
		clear = BTRFS_FEATURE_INCOMPAT_SAFE_CLEAR;
	पूर्ण

	features = get_features(fs_info, fa->feature_set);

	/* Nothing to करो */
	अगर ((val && (features & fa->feature_bit)) ||
	    (!val && !(features & fa->feature_bit)))
		वापस count;

	अगर ((val && !(set & fa->feature_bit)) ||
	    (!val && !(clear & fa->feature_bit))) अणु
		btrfs_info(fs_info,
			"%sabling feature %s on mounted fs is not supported.",
			val ? "En" : "Dis", fa->kobj_attr.attr.name);
		वापस -EPERM;
	पूर्ण

	btrfs_info(fs_info, "%s %s feature flag",
		   val ? "Setting" : "Clearing", fa->kobj_attr.attr.name);

	spin_lock(&fs_info->super_lock);
	features = get_features(fs_info, fa->feature_set);
	अगर (val)
		features |= fa->feature_bit;
	अन्यथा
		features &= ~fa->feature_bit;
	set_features(fs_info, fa->feature_set, features);
	spin_unlock(&fs_info->super_lock);

	/*
	 * We करोn't want to करो full transaction commit from inside sysfs
	 */
	btrfs_set_pending(fs_info, COMMIT);
	wake_up_process(fs_info->transaction_kthपढ़ो);

	वापस count;
पूर्ण

अटल umode_t btrfs_feature_visible(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, पूर्णांक unused)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);
	umode_t mode = attr->mode;

	अगर (fs_info) अणु
		काष्ठा btrfs_feature_attr *fa;
		u64 features;

		fa = attr_to_btrfs_feature_attr(attr);
		features = get_features(fs_info, fa->feature_set);

		अगर (can_modअगरy_feature(fa))
			mode |= S_IWUSR;
		अन्यथा अगर (!(features & fa->feature_bit))
			mode = 0;
	पूर्ण

	वापस mode;
पूर्ण

BTRFS_FEAT_ATTR_INCOMPAT(mixed_backref, MIXED_BACKREF);
BTRFS_FEAT_ATTR_INCOMPAT(शेष_subvol, DEFAULT_SUBVOL);
BTRFS_FEAT_ATTR_INCOMPAT(mixed_groups, MIXED_GROUPS);
BTRFS_FEAT_ATTR_INCOMPAT(compress_lzo, COMPRESS_LZO);
BTRFS_FEAT_ATTR_INCOMPAT(compress_zstd, COMPRESS_ZSTD);
BTRFS_FEAT_ATTR_INCOMPAT(big_metadata, BIG_METADATA);
BTRFS_FEAT_ATTR_INCOMPAT(extended_iref, EXTENDED_IREF);
BTRFS_FEAT_ATTR_INCOMPAT(raid56, RAID56);
BTRFS_FEAT_ATTR_INCOMPAT(skinny_metadata, SKINNY_METADATA);
BTRFS_FEAT_ATTR_INCOMPAT(no_holes, NO_HOLES);
BTRFS_FEAT_ATTR_INCOMPAT(metadata_uuid, METADATA_UUID);
BTRFS_FEAT_ATTR_COMPAT_RO(मुक्त_space_tree, FREE_SPACE_TREE);
BTRFS_FEAT_ATTR_INCOMPAT(raid1c34, RAID1C34);
/* Remove once support क्रम zoned allocation is feature complete */
#अगर_घोषित CONFIG_BTRFS_DEBUG
BTRFS_FEAT_ATTR_INCOMPAT(zoned, ZONED);
#पूर्ण_अगर

अटल काष्ठा attribute *btrfs_supported_feature_attrs[] = अणु
	BTRFS_FEAT_ATTR_PTR(mixed_backref),
	BTRFS_FEAT_ATTR_PTR(शेष_subvol),
	BTRFS_FEAT_ATTR_PTR(mixed_groups),
	BTRFS_FEAT_ATTR_PTR(compress_lzo),
	BTRFS_FEAT_ATTR_PTR(compress_zstd),
	BTRFS_FEAT_ATTR_PTR(big_metadata),
	BTRFS_FEAT_ATTR_PTR(extended_iref),
	BTRFS_FEAT_ATTR_PTR(raid56),
	BTRFS_FEAT_ATTR_PTR(skinny_metadata),
	BTRFS_FEAT_ATTR_PTR(no_holes),
	BTRFS_FEAT_ATTR_PTR(metadata_uuid),
	BTRFS_FEAT_ATTR_PTR(मुक्त_space_tree),
	BTRFS_FEAT_ATTR_PTR(raid1c34),
#अगर_घोषित CONFIG_BTRFS_DEBUG
	BTRFS_FEAT_ATTR_PTR(zoned),
#पूर्ण_अगर
	शून्य
पूर्ण;

/*
 * Features which depend on feature bits and may dअगरfer between each fs.
 *
 * /sys/fs/btrfs/features lists all available features of this kernel जबतक
 * /sys/fs/btrfs/UUID/features shows features of the fs which are enabled or
 * can be changed online.
 */
अटल स्थिर काष्ठा attribute_group btrfs_feature_attr_group = अणु
	.name = "features",
	.is_visible = btrfs_feature_visible,
	.attrs = btrfs_supported_feature_attrs,
पूर्ण;

अटल sमाप_प्रकार सूची_हटाओ_subvol_show(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *ka, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "0\n");
पूर्ण
BTRFS_ATTR(अटल_feature, सूची_हटाओ_subvol, सूची_हटाओ_subvol_show);

अटल sमाप_प्रकार supported_checksums_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	sमाप_प्रकार ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < btrfs_get_num_csums(); i++) अणु
		/*
		 * This "trick" only works as दीर्घ as 'enum btrfs_csum_type' has
		 * no holes in it
		 */
		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "%s%s",
				(i == 0 ? "" : " "), btrfs_super_csum_name(i));

	पूर्ण

	ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "\n");
	वापस ret;
पूर्ण
BTRFS_ATTR(अटल_feature, supported_checksums, supported_checksums_show);

अटल sमाप_प्रकार send_stream_version_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *ka, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", BTRFS_SEND_STREAM_VERSION);
पूर्ण
BTRFS_ATTR(अटल_feature, send_stream_version, send_stream_version_show);

अटल स्थिर अक्षर *rescue_opts[] = अणु
	"usebackuproot",
	"nologreplay",
	"ignorebadroots",
	"ignoredatacsums",
	"all",
पूर्ण;

अटल sमाप_प्रकार supported_rescue_options_show(काष्ठा kobject *kobj,
					     काष्ठा kobj_attribute *a,
					     अक्षर *buf)
अणु
	sमाप_प्रकार ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rescue_opts); i++)
		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "%s%s",
				 (i ? " " : ""), rescue_opts[i]);
	ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "\n");
	वापस ret;
पूर्ण
BTRFS_ATTR(अटल_feature, supported_rescue_options,
	   supported_rescue_options_show);

अटल sमाप_प्रकार supported_sectorsizes_show(काष्ठा kobject *kobj,
					  काष्ठा kobj_attribute *a,
					  अक्षर *buf)
अणु
	sमाप_प्रकार ret = 0;

	/* Only sectorsize == PAGE_SIZE is now supported */
	ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "%lu\n", PAGE_SIZE);

	वापस ret;
पूर्ण
BTRFS_ATTR(अटल_feature, supported_sectorsizes,
	   supported_sectorsizes_show);

अटल काष्ठा attribute *btrfs_supported_अटल_feature_attrs[] = अणु
	BTRFS_ATTR_PTR(अटल_feature, सूची_हटाओ_subvol),
	BTRFS_ATTR_PTR(अटल_feature, supported_checksums),
	BTRFS_ATTR_PTR(अटल_feature, send_stream_version),
	BTRFS_ATTR_PTR(अटल_feature, supported_rescue_options),
	BTRFS_ATTR_PTR(अटल_feature, supported_sectorsizes),
	शून्य
पूर्ण;

/*
 * Features which only depend on kernel version.
 *
 * These are listed in /sys/fs/btrfs/features aदीर्घ with
 * btrfs_feature_attr_group
 */
अटल स्थिर काष्ठा attribute_group btrfs_अटल_feature_attr_group = अणु
	.name = "features",
	.attrs = btrfs_supported_अटल_feature_attrs,
पूर्ण;

#अगर_घोषित CONFIG_BTRFS_DEBUG

/*
 * Discard statistics and tunables
 */
#घोषणा discard_to_fs_info(_kobj)	to_fs_info((_kobj)->parent->parent)

अटल sमाप_प्रकार btrfs_discardable_bytes_show(काष्ठा kobject *kobj,
					    काष्ठा kobj_attribute *a,
					    अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = discard_to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%lld\n",
			atomic64_पढ़ो(&fs_info->discard_ctl.discardable_bytes));
पूर्ण
BTRFS_ATTR(discard, discardable_bytes, btrfs_discardable_bytes_show);

अटल sमाप_प्रकार btrfs_discardable_extents_show(काष्ठा kobject *kobj,
					      काष्ठा kobj_attribute *a,
					      अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = discard_to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",
			atomic_पढ़ो(&fs_info->discard_ctl.discardable_extents));
पूर्ण
BTRFS_ATTR(discard, discardable_extents, btrfs_discardable_extents_show);

अटल sमाप_प्रकार btrfs_discard_biपंचांगap_bytes_show(काष्ठा kobject *kobj,
					       काष्ठा kobj_attribute *a,
					       अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = discard_to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%lld\n",
			fs_info->discard_ctl.discard_biपंचांगap_bytes);
पूर्ण
BTRFS_ATTR(discard, discard_biपंचांगap_bytes, btrfs_discard_biपंचांगap_bytes_show);

अटल sमाप_प्रकार btrfs_discard_bytes_saved_show(काष्ठा kobject *kobj,
					      काष्ठा kobj_attribute *a,
					      अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = discard_to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%lld\n",
		atomic64_पढ़ो(&fs_info->discard_ctl.discard_bytes_saved));
पूर्ण
BTRFS_ATTR(discard, discard_bytes_saved, btrfs_discard_bytes_saved_show);

अटल sमाप_प्रकार btrfs_discard_extent_bytes_show(काष्ठा kobject *kobj,
					       काष्ठा kobj_attribute *a,
					       अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = discard_to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%lld\n",
			fs_info->discard_ctl.discard_extent_bytes);
पूर्ण
BTRFS_ATTR(discard, discard_extent_bytes, btrfs_discard_extent_bytes_show);

अटल sमाप_प्रकार btrfs_discard_iops_limit_show(काष्ठा kobject *kobj,
					     काष्ठा kobj_attribute *a,
					     अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = discard_to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
			READ_ONCE(fs_info->discard_ctl.iops_limit));
पूर्ण

अटल sमाप_प्रकार btrfs_discard_iops_limit_store(काष्ठा kobject *kobj,
					      काष्ठा kobj_attribute *a,
					      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा btrfs_fs_info *fs_info = discard_to_fs_info(kobj);
	काष्ठा btrfs_discard_ctl *discard_ctl = &fs_info->discard_ctl;
	u32 iops_limit;
	पूर्णांक ret;

	ret = kstrtou32(buf, 10, &iops_limit);
	अगर (ret)
		वापस -EINVAL;

	WRITE_ONCE(discard_ctl->iops_limit, iops_limit);
	btrfs_discard_calc_delay(discard_ctl);
	btrfs_discard_schedule_work(discard_ctl, true);
	वापस len;
पूर्ण
BTRFS_ATTR_RW(discard, iops_limit, btrfs_discard_iops_limit_show,
	      btrfs_discard_iops_limit_store);

अटल sमाप_प्रकार btrfs_discard_kbps_limit_show(काष्ठा kobject *kobj,
					     काष्ठा kobj_attribute *a,
					     अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = discard_to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
			READ_ONCE(fs_info->discard_ctl.kbps_limit));
पूर्ण

अटल sमाप_प्रकार btrfs_discard_kbps_limit_store(काष्ठा kobject *kobj,
					      काष्ठा kobj_attribute *a,
					      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा btrfs_fs_info *fs_info = discard_to_fs_info(kobj);
	काष्ठा btrfs_discard_ctl *discard_ctl = &fs_info->discard_ctl;
	u32 kbps_limit;
	पूर्णांक ret;

	ret = kstrtou32(buf, 10, &kbps_limit);
	अगर (ret)
		वापस -EINVAL;

	WRITE_ONCE(discard_ctl->kbps_limit, kbps_limit);
	btrfs_discard_schedule_work(discard_ctl, true);
	वापस len;
पूर्ण
BTRFS_ATTR_RW(discard, kbps_limit, btrfs_discard_kbps_limit_show,
	      btrfs_discard_kbps_limit_store);

अटल sमाप_प्रकार btrfs_discard_max_discard_size_show(काष्ठा kobject *kobj,
						   काष्ठा kobj_attribute *a,
						   अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = discard_to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n",
			READ_ONCE(fs_info->discard_ctl.max_discard_size));
पूर्ण

अटल sमाप_प्रकार btrfs_discard_max_discard_size_store(काष्ठा kobject *kobj,
						    काष्ठा kobj_attribute *a,
						    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा btrfs_fs_info *fs_info = discard_to_fs_info(kobj);
	काष्ठा btrfs_discard_ctl *discard_ctl = &fs_info->discard_ctl;
	u64 max_discard_size;
	पूर्णांक ret;

	ret = kstrtou64(buf, 10, &max_discard_size);
	अगर (ret)
		वापस -EINVAL;

	WRITE_ONCE(discard_ctl->max_discard_size, max_discard_size);

	वापस len;
पूर्ण
BTRFS_ATTR_RW(discard, max_discard_size, btrfs_discard_max_discard_size_show,
	      btrfs_discard_max_discard_size_store);

अटल स्थिर काष्ठा attribute *discard_debug_attrs[] = अणु
	BTRFS_ATTR_PTR(discard, discardable_bytes),
	BTRFS_ATTR_PTR(discard, discardable_extents),
	BTRFS_ATTR_PTR(discard, discard_biपंचांगap_bytes),
	BTRFS_ATTR_PTR(discard, discard_bytes_saved),
	BTRFS_ATTR_PTR(discard, discard_extent_bytes),
	BTRFS_ATTR_PTR(discard, iops_limit),
	BTRFS_ATTR_PTR(discard, kbps_limit),
	BTRFS_ATTR_PTR(discard, max_discard_size),
	शून्य,
पूर्ण;

/*
 * Runसमय debugging exported via sysfs
 *
 * /sys/fs/btrfs/debug - applies to module or all fileप्रणालीs
 * /sys/fs/btrfs/UUID  - applies only to the given fileप्रणाली
 */
अटल स्थिर काष्ठा attribute *btrfs_debug_mount_attrs[] = अणु
	शून्य,
पूर्ण;

अटल काष्ठा attribute *btrfs_debug_feature_attrs[] = अणु
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group btrfs_debug_feature_attr_group = अणु
	.name = "debug",
	.attrs = btrfs_debug_feature_attrs,
पूर्ण;

#पूर्ण_अगर

अटल sमाप_प्रकार btrfs_show_u64(u64 *value_ptr, spinlock_t *lock, अक्षर *buf)
अणु
	u64 val;
	अगर (lock)
		spin_lock(lock);
	val = *value_ptr;
	अगर (lock)
		spin_unlock(lock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", val);
पूर्ण

अटल sमाप_प्रकार global_rsv_size_show(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *ka, अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj->parent);
	काष्ठा btrfs_block_rsv *block_rsv = &fs_info->global_block_rsv;
	वापस btrfs_show_u64(&block_rsv->size, &block_rsv->lock, buf);
पूर्ण
BTRFS_ATTR(allocation, global_rsv_size, global_rsv_size_show);

अटल sमाप_प्रकार global_rsv_reserved_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj->parent);
	काष्ठा btrfs_block_rsv *block_rsv = &fs_info->global_block_rsv;
	वापस btrfs_show_u64(&block_rsv->reserved, &block_rsv->lock, buf);
पूर्ण
BTRFS_ATTR(allocation, global_rsv_reserved, global_rsv_reserved_show);

#घोषणा to_space_info(_kobj) container_of(_kobj, काष्ठा btrfs_space_info, kobj)
#घोषणा to_raid_kobj(_kobj) container_of(_kobj, काष्ठा raid_kobject, kobj)

अटल sमाप_प्रकार raid_bytes_show(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr, अक्षर *buf);
BTRFS_ATTR(raid, total_bytes, raid_bytes_show);
BTRFS_ATTR(raid, used_bytes, raid_bytes_show);

अटल sमाप_प्रकार raid_bytes_show(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr, अक्षर *buf)

अणु
	काष्ठा btrfs_space_info *sinfo = to_space_info(kobj->parent);
	काष्ठा btrfs_block_group *block_group;
	पूर्णांक index = btrfs_bg_flags_to_raid_index(to_raid_kobj(kobj)->flags);
	u64 val = 0;

	करोwn_पढ़ो(&sinfo->groups_sem);
	list_क्रम_each_entry(block_group, &sinfo->block_groups[index], list) अणु
		अगर (&attr->attr == BTRFS_ATTR_PTR(raid, total_bytes))
			val += block_group->length;
		अन्यथा
			val += block_group->used;
	पूर्ण
	up_पढ़ो(&sinfo->groups_sem);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", val);
पूर्ण

अटल काष्ठा attribute *raid_attrs[] = अणु
	BTRFS_ATTR_PTR(raid, total_bytes),
	BTRFS_ATTR_PTR(raid, used_bytes),
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(raid);

अटल व्योम release_raid_kobj(काष्ठा kobject *kobj)
अणु
	kमुक्त(to_raid_kobj(kobj));
पूर्ण

अटल काष्ठा kobj_type btrfs_raid_ktype = अणु
	.sysfs_ops = &kobj_sysfs_ops,
	.release = release_raid_kobj,
	.शेष_groups = raid_groups,
पूर्ण;

#घोषणा SPACE_INFO_ATTR(field)						\
अटल sमाप_प्रकार btrfs_space_info_show_##field(काष्ठा kobject *kobj,	\
					     काष्ठा kobj_attribute *a,	\
					     अक्षर *buf)			\
अणु									\
	काष्ठा btrfs_space_info *sinfo = to_space_info(kobj);		\
	वापस btrfs_show_u64(&sinfo->field, &sinfo->lock, buf);	\
पूर्ण									\
BTRFS_ATTR(space_info, field, btrfs_space_info_show_##field)

अटल sमाप_प्रकार btrfs_space_info_show_total_bytes_pinned(काष्ठा kobject *kobj,
						       काष्ठा kobj_attribute *a,
						       अक्षर *buf)
अणु
	काष्ठा btrfs_space_info *sinfo = to_space_info(kobj);
	s64 val = percpu_counter_sum(&sinfo->total_bytes_pinned);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%lld\n", val);
पूर्ण

SPACE_INFO_ATTR(flags);
SPACE_INFO_ATTR(total_bytes);
SPACE_INFO_ATTR(bytes_used);
SPACE_INFO_ATTR(bytes_pinned);
SPACE_INFO_ATTR(bytes_reserved);
SPACE_INFO_ATTR(bytes_may_use);
SPACE_INFO_ATTR(bytes_पढ़ोonly);
SPACE_INFO_ATTR(bytes_zone_unusable);
SPACE_INFO_ATTR(disk_used);
SPACE_INFO_ATTR(disk_total);
BTRFS_ATTR(space_info, total_bytes_pinned,
	   btrfs_space_info_show_total_bytes_pinned);

अटल काष्ठा attribute *space_info_attrs[] = अणु
	BTRFS_ATTR_PTR(space_info, flags),
	BTRFS_ATTR_PTR(space_info, total_bytes),
	BTRFS_ATTR_PTR(space_info, bytes_used),
	BTRFS_ATTR_PTR(space_info, bytes_pinned),
	BTRFS_ATTR_PTR(space_info, bytes_reserved),
	BTRFS_ATTR_PTR(space_info, bytes_may_use),
	BTRFS_ATTR_PTR(space_info, bytes_पढ़ोonly),
	BTRFS_ATTR_PTR(space_info, bytes_zone_unusable),
	BTRFS_ATTR_PTR(space_info, disk_used),
	BTRFS_ATTR_PTR(space_info, disk_total),
	BTRFS_ATTR_PTR(space_info, total_bytes_pinned),
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(space_info);

अटल व्योम space_info_release(काष्ठा kobject *kobj)
अणु
	काष्ठा btrfs_space_info *sinfo = to_space_info(kobj);
	percpu_counter_destroy(&sinfo->total_bytes_pinned);
	kमुक्त(sinfo);
पूर्ण

अटल काष्ठा kobj_type space_info_ktype = अणु
	.sysfs_ops = &kobj_sysfs_ops,
	.release = space_info_release,
	.शेष_groups = space_info_groups,
पूर्ण;

अटल स्थिर काष्ठा attribute *allocation_attrs[] = अणु
	BTRFS_ATTR_PTR(allocation, global_rsv_reserved),
	BTRFS_ATTR_PTR(allocation, global_rsv_size),
	शून्य,
पूर्ण;

अटल sमाप_प्रकार btrfs_label_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);
	अक्षर *label = fs_info->super_copy->label;
	sमाप_प्रकार ret;

	spin_lock(&fs_info->super_lock);
	ret = scnम_लिखो(buf, PAGE_SIZE, label[0] ? "%s\n" : "%s", label);
	spin_unlock(&fs_info->super_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार btrfs_label_store(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *a,
				 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);
	माप_प्रकार p_len;

	अगर (!fs_info)
		वापस -EPERM;

	अगर (sb_rकरोnly(fs_info->sb))
		वापस -EROFS;

	/*
	 * p_len is the len until the first occurrence of either
	 * '\n' or '\0'
	 */
	p_len = म_खोज(buf, "\n");

	अगर (p_len >= BTRFS_LABEL_SIZE)
		वापस -EINVAL;

	spin_lock(&fs_info->super_lock);
	स_रखो(fs_info->super_copy->label, 0, BTRFS_LABEL_SIZE);
	स_नकल(fs_info->super_copy->label, buf, p_len);
	spin_unlock(&fs_info->super_lock);

	/*
	 * We करोn't want to करो full transaction commit from inside sysfs
	 */
	btrfs_set_pending(fs_info, COMMIT);
	wake_up_process(fs_info->transaction_kthपढ़ो);

	वापस len;
पूर्ण
BTRFS_ATTR_RW(, label, btrfs_label_show, btrfs_label_store);

अटल sमाप_प्रकार btrfs_nodesize_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", fs_info->super_copy->nodesize);
पूर्ण

BTRFS_ATTR(, nodesize, btrfs_nodesize_show);

अटल sमाप_प्रकार btrfs_sectorsize_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
			 fs_info->super_copy->sectorsize);
पूर्ण

BTRFS_ATTR(, sectorsize, btrfs_sectorsize_show);

अटल sमाप_प्रकार btrfs_clone_alignment_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", fs_info->super_copy->sectorsize);
पूर्ण

BTRFS_ATTR(, clone_alignment, btrfs_clone_alignment_show);

अटल sमाप_प्रकार quota_override_show(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);
	पूर्णांक quota_override;

	quota_override = test_bit(BTRFS_FS_QUOTA_OVERRIDE, &fs_info->flags);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", quota_override);
पूर्ण

अटल sमाप_प्रकार quota_override_store(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *a,
				    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);
	अचिन्हित दीर्घ knob;
	पूर्णांक err;

	अगर (!fs_info)
		वापस -EPERM;

	अगर (!capable(CAP_SYS_RESOURCE))
		वापस -EPERM;

	err = kम_से_अदीर्घ(buf, 10, &knob);
	अगर (err)
		वापस err;
	अगर (knob > 1)
		वापस -EINVAL;

	अगर (knob)
		set_bit(BTRFS_FS_QUOTA_OVERRIDE, &fs_info->flags);
	अन्यथा
		clear_bit(BTRFS_FS_QUOTA_OVERRIDE, &fs_info->flags);

	वापस len;
पूर्ण

BTRFS_ATTR_RW(, quota_override, quota_override_show, quota_override_store);

अटल sमाप_प्रकार btrfs_metadata_uuid_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%pU\n",
			fs_info->fs_devices->metadata_uuid);
पूर्ण

BTRFS_ATTR(, metadata_uuid, btrfs_metadata_uuid_show);

अटल sमाप_प्रकार btrfs_checksum_show(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);
	u16 csum_type = btrfs_super_csum_type(fs_info->super_copy);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s (%s)\n",
			btrfs_super_csum_name(csum_type),
			crypto_shash_driver_name(fs_info->csum_shash));
पूर्ण

BTRFS_ATTR(, checksum, btrfs_checksum_show);

अटल sमाप_प्रकार btrfs_exclusive_operation_show(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);
	स्थिर अक्षर *str;

	चयन (READ_ONCE(fs_info->exclusive_operation)) अणु
		हाल  BTRFS_EXCLOP_NONE:
			str = "none\n";
			अवरोध;
		हाल BTRFS_EXCLOP_BALANCE:
			str = "balance\n";
			अवरोध;
		हाल BTRFS_EXCLOP_DEV_ADD:
			str = "device add\n";
			अवरोध;
		हाल BTRFS_EXCLOP_DEV_REMOVE:
			str = "device remove\n";
			अवरोध;
		हाल BTRFS_EXCLOP_DEV_REPLACE:
			str = "device replace\n";
			अवरोध;
		हाल BTRFS_EXCLOP_RESIZE:
			str = "resize\n";
			अवरोध;
		हाल BTRFS_EXCLOP_SWAP_ACTIVATE:
			str = "swap activate\n";
			अवरोध;
		शेष:
			str = "UNKNOWN\n";
			अवरोध;
	पूर्ण
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s", str);
पूर्ण
BTRFS_ATTR(, exclusive_operation, btrfs_exclusive_operation_show);

अटल sमाप_प्रकार btrfs_generation_show(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", fs_info->generation);
पूर्ण
BTRFS_ATTR(, generation, btrfs_generation_show);

/*
 * Look क्रम an exact string @string in @buffer with possible leading or
 * trailing whitespace
 */
अटल bool strmatch(स्थिर अक्षर *buffer, स्थिर अक्षर *string)
अणु
	स्थिर माप_प्रकार len = म_माप(string);

	/* Skip leading whitespace */
	buffer = skip_spaces(buffer);

	/* Match entire string, check अगर the rest is whitespace or empty */
	अगर (म_भेदन(string, buffer, len) == 0 &&
	    म_माप(skip_spaces(buffer + len)) == 0)
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर अक्षर * स्थिर btrfs_पढ़ो_policy_name[] = अणु "pid" पूर्ण;

अटल sमाप_प्रकार btrfs_पढ़ो_policy_show(काष्ठा kobject *kobj,
				      काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	काष्ठा btrfs_fs_devices *fs_devices = to_fs_devs(kobj);
	sमाप_प्रकार ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < BTRFS_NR_READ_POLICY; i++) अणु
		अगर (fs_devices->पढ़ो_policy == i)
			ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "%s[%s]",
					 (ret == 0 ? "" : " "),
					 btrfs_पढ़ो_policy_name[i]);
		अन्यथा
			ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "%s%s",
					 (ret == 0 ? "" : " "),
					 btrfs_पढ़ो_policy_name[i]);
	पूर्ण

	ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "\n");

	वापस ret;
पूर्ण

अटल sमाप_प्रकार btrfs_पढ़ो_policy_store(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *a,
				       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा btrfs_fs_devices *fs_devices = to_fs_devs(kobj);
	पूर्णांक i;

	क्रम (i = 0; i < BTRFS_NR_READ_POLICY; i++) अणु
		अगर (strmatch(buf, btrfs_पढ़ो_policy_name[i])) अणु
			अगर (i != fs_devices->पढ़ो_policy) अणु
				fs_devices->पढ़ो_policy = i;
				btrfs_info(fs_devices->fs_info,
					   "read policy set to '%s'",
					   btrfs_पढ़ो_policy_name[i]);
			पूर्ण
			वापस len;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
BTRFS_ATTR_RW(, पढ़ो_policy, btrfs_पढ़ो_policy_show, btrfs_पढ़ो_policy_store);

अटल sमाप_प्रकार btrfs_bg_reclaim_threshold_show(काष्ठा kobject *kobj,
					       काष्ठा kobj_attribute *a,
					       अक्षर *buf)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);
	sमाप_प्रकार ret;

	ret = scnम_लिखो(buf, PAGE_SIZE, "%d\n", fs_info->bg_reclaim_threshold);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार btrfs_bg_reclaim_threshold_store(काष्ठा kobject *kobj,
						काष्ठा kobj_attribute *a,
						स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा btrfs_fs_info *fs_info = to_fs_info(kobj);
	पूर्णांक thresh;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 10, &thresh);
	अगर (ret)
		वापस ret;

	अगर (thresh <= 50 || thresh > 100)
		वापस -EINVAL;

	fs_info->bg_reclaim_threshold = thresh;

	वापस len;
पूर्ण
BTRFS_ATTR_RW(, bg_reclaim_threshold, btrfs_bg_reclaim_threshold_show,
	      btrfs_bg_reclaim_threshold_store);

अटल स्थिर काष्ठा attribute *btrfs_attrs[] = अणु
	BTRFS_ATTR_PTR(, label),
	BTRFS_ATTR_PTR(, nodesize),
	BTRFS_ATTR_PTR(, sectorsize),
	BTRFS_ATTR_PTR(, clone_alignment),
	BTRFS_ATTR_PTR(, quota_override),
	BTRFS_ATTR_PTR(, metadata_uuid),
	BTRFS_ATTR_PTR(, checksum),
	BTRFS_ATTR_PTR(, exclusive_operation),
	BTRFS_ATTR_PTR(, generation),
	BTRFS_ATTR_PTR(, पढ़ो_policy),
	BTRFS_ATTR_PTR(, bg_reclaim_threshold),
	शून्य,
पूर्ण;

अटल व्योम btrfs_release_fsid_kobj(काष्ठा kobject *kobj)
अणु
	काष्ठा btrfs_fs_devices *fs_devs = to_fs_devs(kobj);

	स_रखो(&fs_devs->fsid_kobj, 0, माप(काष्ठा kobject));
	complete(&fs_devs->kobj_unरेजिस्टर);
पूर्ण

अटल काष्ठा kobj_type btrfs_ktype = अणु
	.sysfs_ops	= &kobj_sysfs_ops,
	.release	= btrfs_release_fsid_kobj,
पूर्ण;

अटल अंतरभूत काष्ठा btrfs_fs_devices *to_fs_devs(काष्ठा kobject *kobj)
अणु
	अगर (kobj->ktype != &btrfs_ktype)
		वापस शून्य;
	वापस container_of(kobj, काष्ठा btrfs_fs_devices, fsid_kobj);
पूर्ण

अटल अंतरभूत काष्ठा btrfs_fs_info *to_fs_info(काष्ठा kobject *kobj)
अणु
	अगर (kobj->ktype != &btrfs_ktype)
		वापस शून्य;
	वापस to_fs_devs(kobj)->fs_info;
पूर्ण

#घोषणा NUM_FEATURE_BITS 64
#घोषणा BTRFS_FEATURE_NAME_MAX 13
अटल अक्षर btrfs_unknown_feature_names[FEAT_MAX][NUM_FEATURE_BITS][BTRFS_FEATURE_NAME_MAX];
अटल काष्ठा btrfs_feature_attr btrfs_feature_attrs[FEAT_MAX][NUM_FEATURE_BITS];

अटल स्थिर u64 supported_feature_masks[FEAT_MAX] = अणु
	[FEAT_COMPAT]    = BTRFS_FEATURE_COMPAT_SUPP,
	[FEAT_COMPAT_RO] = BTRFS_FEATURE_COMPAT_RO_SUPP,
	[FEAT_INCOMPAT]  = BTRFS_FEATURE_INCOMPAT_SUPP,
पूर्ण;

अटल पूर्णांक addrm_unknown_feature_attrs(काष्ठा btrfs_fs_info *fs_info, bool add)
अणु
	पूर्णांक set;

	क्रम (set = 0; set < FEAT_MAX; set++) अणु
		पूर्णांक i;
		काष्ठा attribute *attrs[2];
		काष्ठा attribute_group agroup = अणु
			.name = "features",
			.attrs = attrs,
		पूर्ण;
		u64 features = get_features(fs_info, set);
		features &= ~supported_feature_masks[set];

		अगर (!features)
			जारी;

		attrs[1] = शून्य;
		क्रम (i = 0; i < NUM_FEATURE_BITS; i++) अणु
			काष्ठा btrfs_feature_attr *fa;

			अगर (!(features & (1ULL << i)))
				जारी;

			fa = &btrfs_feature_attrs[set][i];
			attrs[0] = &fa->kobj_attr.attr;
			अगर (add) अणु
				पूर्णांक ret;
				ret = sysfs_merge_group(&fs_info->fs_devices->fsid_kobj,
							&agroup);
				अगर (ret)
					वापस ret;
			पूर्ण अन्यथा
				sysfs_unmerge_group(&fs_info->fs_devices->fsid_kobj,
						    &agroup);
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __btrfs_sysfs_हटाओ_fsid(काष्ठा btrfs_fs_devices *fs_devs)
अणु
	अगर (fs_devs->devinfo_kobj) अणु
		kobject_del(fs_devs->devinfo_kobj);
		kobject_put(fs_devs->devinfo_kobj);
		fs_devs->devinfo_kobj = शून्य;
	पूर्ण

	अगर (fs_devs->devices_kobj) अणु
		kobject_del(fs_devs->devices_kobj);
		kobject_put(fs_devs->devices_kobj);
		fs_devs->devices_kobj = शून्य;
	पूर्ण

	अगर (fs_devs->fsid_kobj.state_initialized) अणु
		kobject_del(&fs_devs->fsid_kobj);
		kobject_put(&fs_devs->fsid_kobj);
		रुको_क्रम_completion(&fs_devs->kobj_unरेजिस्टर);
	पूर्ण
पूर्ण

/* when fs_devs is शून्य it will हटाओ all fsid kobject */
व्योम btrfs_sysfs_हटाओ_fsid(काष्ठा btrfs_fs_devices *fs_devs)
अणु
	काष्ठा list_head *fs_uuids = btrfs_get_fs_uuids();

	अगर (fs_devs) अणु
		__btrfs_sysfs_हटाओ_fsid(fs_devs);
		वापस;
	पूर्ण

	list_क्रम_each_entry(fs_devs, fs_uuids, fs_list) अणु
		__btrfs_sysfs_हटाओ_fsid(fs_devs);
	पूर्ण
पूर्ण

अटल व्योम btrfs_sysfs_हटाओ_fs_devices(काष्ठा btrfs_fs_devices *fs_devices)
अणु
	काष्ठा btrfs_device *device;
	काष्ठा btrfs_fs_devices *seed;

	list_क्रम_each_entry(device, &fs_devices->devices, dev_list)
		btrfs_sysfs_हटाओ_device(device);

	list_क्रम_each_entry(seed, &fs_devices->seed_list, seed_list) अणु
		list_क्रम_each_entry(device, &seed->devices, dev_list)
			btrfs_sysfs_हटाओ_device(device);
	पूर्ण
पूर्ण

व्योम btrfs_sysfs_हटाओ_mounted(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा kobject *fsid_kobj = &fs_info->fs_devices->fsid_kobj;

	sysfs_हटाओ_link(fsid_kobj, "bdi");

	अगर (fs_info->space_info_kobj) अणु
		sysfs_हटाओ_files(fs_info->space_info_kobj, allocation_attrs);
		kobject_del(fs_info->space_info_kobj);
		kobject_put(fs_info->space_info_kobj);
	पूर्ण
#अगर_घोषित CONFIG_BTRFS_DEBUG
	अगर (fs_info->discard_debug_kobj) अणु
		sysfs_हटाओ_files(fs_info->discard_debug_kobj,
				   discard_debug_attrs);
		kobject_del(fs_info->discard_debug_kobj);
		kobject_put(fs_info->discard_debug_kobj);
	पूर्ण
	अगर (fs_info->debug_kobj) अणु
		sysfs_हटाओ_files(fs_info->debug_kobj, btrfs_debug_mount_attrs);
		kobject_del(fs_info->debug_kobj);
		kobject_put(fs_info->debug_kobj);
	पूर्ण
#पूर्ण_अगर
	addrm_unknown_feature_attrs(fs_info, false);
	sysfs_हटाओ_group(fsid_kobj, &btrfs_feature_attr_group);
	sysfs_हटाओ_files(fsid_kobj, btrfs_attrs);
	btrfs_sysfs_हटाओ_fs_devices(fs_info->fs_devices);
पूर्ण

अटल स्थिर अक्षर * स्थिर btrfs_feature_set_names[FEAT_MAX] = अणु
	[FEAT_COMPAT]	 = "compat",
	[FEAT_COMPAT_RO] = "compat_ro",
	[FEAT_INCOMPAT]	 = "incompat",
पूर्ण;

स्थिर अक्षर *btrfs_feature_set_name(क्रमागत btrfs_feature_set set)
अणु
	वापस btrfs_feature_set_names[set];
पूर्ण

अक्षर *btrfs_prपूर्णांकable_features(क्रमागत btrfs_feature_set set, u64 flags)
अणु
	माप_प्रकार bufsize = 4096; /* safe max, 64 names * 64 bytes */
	पूर्णांक len = 0;
	पूर्णांक i;
	अक्षर *str;

	str = kदो_स्मृति(bufsize, GFP_KERNEL);
	अगर (!str)
		वापस str;

	क्रम (i = 0; i < ARRAY_SIZE(btrfs_feature_attrs[set]); i++) अणु
		स्थिर अक्षर *name;

		अगर (!(flags & (1ULL << i)))
			जारी;

		name = btrfs_feature_attrs[set][i].kobj_attr.attr.name;
		len += scnम_लिखो(str + len, bufsize - len, "%s%s",
				len ? "," : "", name);
	पूर्ण

	वापस str;
पूर्ण

अटल व्योम init_feature_attrs(व्योम)
अणु
	काष्ठा btrfs_feature_attr *fa;
	पूर्णांक set, i;

	BUILD_BUG_ON(ARRAY_SIZE(btrfs_unknown_feature_names) !=
		     ARRAY_SIZE(btrfs_feature_attrs));
	BUILD_BUG_ON(ARRAY_SIZE(btrfs_unknown_feature_names[0]) !=
		     ARRAY_SIZE(btrfs_feature_attrs[0]));

	स_रखो(btrfs_feature_attrs, 0, माप(btrfs_feature_attrs));
	स_रखो(btrfs_unknown_feature_names, 0,
	       माप(btrfs_unknown_feature_names));

	क्रम (i = 0; btrfs_supported_feature_attrs[i]; i++) अणु
		काष्ठा btrfs_feature_attr *sfa;
		काष्ठा attribute *a = btrfs_supported_feature_attrs[i];
		पूर्णांक bit;
		sfa = attr_to_btrfs_feature_attr(a);
		bit = ilog2(sfa->feature_bit);
		fa = &btrfs_feature_attrs[sfa->feature_set][bit];

		fa->kobj_attr.attr.name = sfa->kobj_attr.attr.name;
	पूर्ण

	क्रम (set = 0; set < FEAT_MAX; set++) अणु
		क्रम (i = 0; i < ARRAY_SIZE(btrfs_feature_attrs[set]); i++) अणु
			अक्षर *name = btrfs_unknown_feature_names[set][i];
			fa = &btrfs_feature_attrs[set][i];

			अगर (fa->kobj_attr.attr.name)
				जारी;

			snम_लिखो(name, BTRFS_FEATURE_NAME_MAX, "%s:%u",
				 btrfs_feature_set_names[set], i);

			fa->kobj_attr.attr.name = name;
			fa->kobj_attr.attr.mode = S_IRUGO;
			fa->feature_set = set;
			fa->feature_bit = 1ULL << i;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Create a sysfs entry क्रम a given block group type at path
 * /sys/fs/btrfs/UUID/allocation/data/TYPE
 */
व्योम btrfs_sysfs_add_block_group_type(काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	काष्ठा btrfs_space_info *space_info = cache->space_info;
	काष्ठा raid_kobject *rkobj;
	स्थिर पूर्णांक index = btrfs_bg_flags_to_raid_index(cache->flags);
	अचिन्हित पूर्णांक nofs_flag;
	पूर्णांक ret;

	/*
	 * Setup a NOFS context because kobject_add(), deep in its call chain,
	 * करोes GFP_KERNEL allocations, and we are often called in a context
	 * where अगर reclaim is triggered we can deadlock (we are either holding
	 * a transaction handle or some lock required क्रम a transaction
	 * commit).
	 */
	nofs_flag = meदो_स्मृति_nofs_save();

	rkobj = kzalloc(माप(*rkobj), GFP_NOFS);
	अगर (!rkobj) अणु
		meदो_स्मृति_nofs_restore(nofs_flag);
		btrfs_warn(cache->fs_info,
				"couldn't alloc memory for raid level kobject");
		वापस;
	पूर्ण

	rkobj->flags = cache->flags;
	kobject_init(&rkobj->kobj, &btrfs_raid_ktype);

	/*
	 * We call this either on mount, or अगर we've created a block group क्रम a
	 * new index type जबतक running (i.e. when restriping).  The running
	 * हाल is tricky because we could race with other thपढ़ोs, so we need
	 * to have this check to make sure we didn't alपढ़ोy init the kobject.
	 *
	 * We करोn't have to protect on the मुक्त side because it only happens on
	 * unmount.
	 */
	spin_lock(&space_info->lock);
	अगर (space_info->block_group_kobjs[index]) अणु
		spin_unlock(&space_info->lock);
		kobject_put(&rkobj->kobj);
		वापस;
	पूर्ण अन्यथा अणु
		space_info->block_group_kobjs[index] = &rkobj->kobj;
	पूर्ण
	spin_unlock(&space_info->lock);

	ret = kobject_add(&rkobj->kobj, &space_info->kobj, "%s",
			  btrfs_bg_type_to_raid_name(rkobj->flags));
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (ret) अणु
		spin_lock(&space_info->lock);
		space_info->block_group_kobjs[index] = शून्य;
		spin_unlock(&space_info->lock);
		kobject_put(&rkobj->kobj);
		btrfs_warn(fs_info,
			"failed to add kobject for block cache, ignoring");
		वापस;
	पूर्ण
पूर्ण

/*
 * Remove sysfs directories क्रम all block group types of a given space info and
 * the space info as well
 */
व्योम btrfs_sysfs_हटाओ_space_info(काष्ठा btrfs_space_info *space_info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BTRFS_NR_RAID_TYPES; i++) अणु
		काष्ठा kobject *kobj;

		kobj = space_info->block_group_kobjs[i];
		space_info->block_group_kobjs[i] = शून्य;
		अगर (kobj) अणु
			kobject_del(kobj);
			kobject_put(kobj);
		पूर्ण
	पूर्ण
	kobject_del(&space_info->kobj);
	kobject_put(&space_info->kobj);
पूर्ण

अटल स्थिर अक्षर *alloc_name(u64 flags)
अणु
	चयन (flags) अणु
	हाल BTRFS_BLOCK_GROUP_METADATA | BTRFS_BLOCK_GROUP_DATA:
		वापस "mixed";
	हाल BTRFS_BLOCK_GROUP_METADATA:
		वापस "metadata";
	हाल BTRFS_BLOCK_GROUP_DATA:
		वापस "data";
	हाल BTRFS_BLOCK_GROUP_SYSTEM:
		वापस "system";
	शेष:
		WARN_ON(1);
		वापस "invalid-combination";
	पूर्ण
पूर्ण

/*
 * Create a sysfs entry क्रम a space info type at path
 * /sys/fs/btrfs/UUID/allocation/TYPE
 */
पूर्णांक btrfs_sysfs_add_space_info_type(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा btrfs_space_info *space_info)
अणु
	पूर्णांक ret;

	ret = kobject_init_and_add(&space_info->kobj, &space_info_ktype,
				   fs_info->space_info_kobj, "%s",
				   alloc_name(space_info->flags));
	अगर (ret) अणु
		kobject_put(&space_info->kobj);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम btrfs_sysfs_हटाओ_device(काष्ठा btrfs_device *device)
अणु
	काष्ठा kobject *devices_kobj;

	/*
	 * Seed fs_devices devices_kobj aren't used, fetch kobject from the
	 * fs_info::fs_devices.
	 */
	devices_kobj = device->fs_info->fs_devices->devices_kobj;
	ASSERT(devices_kobj);

	अगर (device->bdev)
		sysfs_हटाओ_link(devices_kobj, bdev_kobj(device->bdev)->name);

	अगर (device->devid_kobj.state_initialized) अणु
		kobject_del(&device->devid_kobj);
		kobject_put(&device->devid_kobj);
		रुको_क्रम_completion(&device->kobj_unरेजिस्टर);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार btrfs_devinfo_in_fs_metadata_show(काष्ठा kobject *kobj,
					         काष्ठा kobj_attribute *a,
					         अक्षर *buf)
अणु
	पूर्णांक val;
	काष्ठा btrfs_device *device = container_of(kobj, काष्ठा btrfs_device,
						   devid_kobj);

	val = !!test_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &device->dev_state);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", val);
पूर्ण
BTRFS_ATTR(devid, in_fs_metadata, btrfs_devinfo_in_fs_metadata_show);

अटल sमाप_प्रकार btrfs_devinfo_missing_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	पूर्णांक val;
	काष्ठा btrfs_device *device = container_of(kobj, काष्ठा btrfs_device,
						   devid_kobj);

	val = !!test_bit(BTRFS_DEV_STATE_MISSING, &device->dev_state);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", val);
पूर्ण
BTRFS_ATTR(devid, missing, btrfs_devinfo_missing_show);

अटल sमाप_प्रकार btrfs_devinfo_replace_target_show(काष्ठा kobject *kobj,
					         काष्ठा kobj_attribute *a,
					         अक्षर *buf)
अणु
	पूर्णांक val;
	काष्ठा btrfs_device *device = container_of(kobj, काष्ठा btrfs_device,
						   devid_kobj);

	val = !!test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", val);
पूर्ण
BTRFS_ATTR(devid, replace_target, btrfs_devinfo_replace_target_show);

अटल sमाप_प्रकार btrfs_devinfo_ग_लिखोable_show(काष्ठा kobject *kobj,
					    काष्ठा kobj_attribute *a, अक्षर *buf)
अणु
	पूर्णांक val;
	काष्ठा btrfs_device *device = container_of(kobj, काष्ठा btrfs_device,
						   devid_kobj);

	val = !!test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", val);
पूर्ण
BTRFS_ATTR(devid, ग_लिखोable, btrfs_devinfo_ग_लिखोable_show);

अटल काष्ठा attribute *devid_attrs[] = अणु
	BTRFS_ATTR_PTR(devid, in_fs_metadata),
	BTRFS_ATTR_PTR(devid, missing),
	BTRFS_ATTR_PTR(devid, replace_target),
	BTRFS_ATTR_PTR(devid, ग_लिखोable),
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(devid);

अटल व्योम btrfs_release_devid_kobj(काष्ठा kobject *kobj)
अणु
	काष्ठा btrfs_device *device = container_of(kobj, काष्ठा btrfs_device,
						   devid_kobj);

	स_रखो(&device->devid_kobj, 0, माप(काष्ठा kobject));
	complete(&device->kobj_unरेजिस्टर);
पूर्ण

अटल काष्ठा kobj_type devid_ktype = अणु
	.sysfs_ops	= &kobj_sysfs_ops,
	.शेष_groups = devid_groups,
	.release	= btrfs_release_devid_kobj,
पूर्ण;

पूर्णांक btrfs_sysfs_add_device(काष्ठा btrfs_device *device)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक nofs_flag;
	काष्ठा kobject *devices_kobj;
	काष्ठा kobject *devinfo_kobj;

	/*
	 * Make sure we use the fs_info::fs_devices to fetch the kobjects even
	 * क्रम the seed fs_devices
	 */
	devices_kobj = device->fs_info->fs_devices->devices_kobj;
	devinfo_kobj = device->fs_info->fs_devices->devinfo_kobj;
	ASSERT(devices_kobj);
	ASSERT(devinfo_kobj);

	nofs_flag = meदो_स्मृति_nofs_save();

	अगर (device->bdev) अणु
		काष्ठा kobject *disk_kobj = bdev_kobj(device->bdev);

		ret = sysfs_create_link(devices_kobj, disk_kobj, disk_kobj->name);
		अगर (ret) अणु
			btrfs_warn(device->fs_info,
				"creating sysfs device link for devid %llu failed: %d",
				device->devid, ret);
			जाओ out;
		पूर्ण
	पूर्ण

	init_completion(&device->kobj_unरेजिस्टर);
	ret = kobject_init_and_add(&device->devid_kobj, &devid_ktype,
				   devinfo_kobj, "%llu", device->devid);
	अगर (ret) अणु
		kobject_put(&device->devid_kobj);
		btrfs_warn(device->fs_info,
			   "devinfo init for devid %llu failed: %d",
			   device->devid, ret);
	पूर्ण

out:
	meदो_स्मृति_nofs_restore(nofs_flag);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_sysfs_add_fs_devices(काष्ठा btrfs_fs_devices *fs_devices)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_device *device;
	काष्ठा btrfs_fs_devices *seed;

	list_क्रम_each_entry(device, &fs_devices->devices, dev_list) अणु
		ret = btrfs_sysfs_add_device(device);
		अगर (ret)
			जाओ fail;
	पूर्ण

	list_क्रम_each_entry(seed, &fs_devices->seed_list, seed_list) अणु
		list_क्रम_each_entry(device, &seed->devices, dev_list) अणु
			ret = btrfs_sysfs_add_device(device);
			अगर (ret)
				जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;

fail:
	btrfs_sysfs_हटाओ_fs_devices(fs_devices);
	वापस ret;
पूर्ण

व्योम btrfs_kobject_uevent(काष्ठा block_device *bdev, क्रमागत kobject_action action)
अणु
	पूर्णांक ret;

	ret = kobject_uevent(&disk_to_dev(bdev->bd_disk)->kobj, action);
	अगर (ret)
		pr_warn("BTRFS: Sending event '%d' to kobject: '%s' (%p): failed\n",
			action, kobject_name(&disk_to_dev(bdev->bd_disk)->kobj),
			&disk_to_dev(bdev->bd_disk)->kobj);
पूर्ण

व्योम btrfs_sysfs_update_sprout_fsid(काष्ठा btrfs_fs_devices *fs_devices)

अणु
	अक्षर fsid_buf[BTRFS_UUID_UNPARSED_SIZE];

	/*
	 * Sprouting changes fsid of the mounted fileप्रणाली, नाम the fsid
	 * directory
	 */
	snम_लिखो(fsid_buf, BTRFS_UUID_UNPARSED_SIZE, "%pU", fs_devices->fsid);
	अगर (kobject_नाम(&fs_devices->fsid_kobj, fsid_buf))
		btrfs_warn(fs_devices->fs_info,
				"sysfs: failed to create fsid for sprout");
पूर्ण

व्योम btrfs_sysfs_update_devid(काष्ठा btrfs_device *device)
अणु
	अक्षर पंचांगp[24];

	snम_लिखो(पंचांगp, माप(पंचांगp), "%llu", device->devid);

	अगर (kobject_नाम(&device->devid_kobj, पंचांगp))
		btrfs_warn(device->fs_devices->fs_info,
			   "sysfs: failed to update devid for %llu",
			   device->devid);
पूर्ण

/* /sys/fs/btrfs/ entry */
अटल काष्ठा kset *btrfs_kset;

/*
 * Creates:
 *		/sys/fs/btrfs/UUID
 *
 * Can be called by the device discovery thपढ़ो.
 */
पूर्णांक btrfs_sysfs_add_fsid(काष्ठा btrfs_fs_devices *fs_devs)
अणु
	पूर्णांक error;

	init_completion(&fs_devs->kobj_unरेजिस्टर);
	fs_devs->fsid_kobj.kset = btrfs_kset;
	error = kobject_init_and_add(&fs_devs->fsid_kobj, &btrfs_ktype, शून्य,
				     "%pU", fs_devs->fsid);
	अगर (error) अणु
		kobject_put(&fs_devs->fsid_kobj);
		वापस error;
	पूर्ण

	fs_devs->devices_kobj = kobject_create_and_add("devices",
						       &fs_devs->fsid_kobj);
	अगर (!fs_devs->devices_kobj) अणु
		btrfs_err(fs_devs->fs_info,
			  "failed to init sysfs device interface");
		btrfs_sysfs_हटाओ_fsid(fs_devs);
		वापस -ENOMEM;
	पूर्ण

	fs_devs->devinfo_kobj = kobject_create_and_add("devinfo",
						       &fs_devs->fsid_kobj);
	अगर (!fs_devs->devinfo_kobj) अणु
		btrfs_err(fs_devs->fs_info,
			  "failed to init sysfs devinfo kobject");
		btrfs_sysfs_हटाओ_fsid(fs_devs);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक btrfs_sysfs_add_mounted(काष्ठा btrfs_fs_info *fs_info)
अणु
	पूर्णांक error;
	काष्ठा btrfs_fs_devices *fs_devs = fs_info->fs_devices;
	काष्ठा kobject *fsid_kobj = &fs_devs->fsid_kobj;

	error = btrfs_sysfs_add_fs_devices(fs_devs);
	अगर (error)
		वापस error;

	error = sysfs_create_files(fsid_kobj, btrfs_attrs);
	अगर (error) अणु
		btrfs_sysfs_हटाओ_fs_devices(fs_devs);
		वापस error;
	पूर्ण

	error = sysfs_create_group(fsid_kobj,
				   &btrfs_feature_attr_group);
	अगर (error)
		जाओ failure;

#अगर_घोषित CONFIG_BTRFS_DEBUG
	fs_info->debug_kobj = kobject_create_and_add("debug", fsid_kobj);
	अगर (!fs_info->debug_kobj) अणु
		error = -ENOMEM;
		जाओ failure;
	पूर्ण

	error = sysfs_create_files(fs_info->debug_kobj, btrfs_debug_mount_attrs);
	अगर (error)
		जाओ failure;

	/* Discard directory */
	fs_info->discard_debug_kobj = kobject_create_and_add("discard",
						     fs_info->debug_kobj);
	अगर (!fs_info->discard_debug_kobj) अणु
		error = -ENOMEM;
		जाओ failure;
	पूर्ण

	error = sysfs_create_files(fs_info->discard_debug_kobj,
				   discard_debug_attrs);
	अगर (error)
		जाओ failure;
#पूर्ण_अगर

	error = addrm_unknown_feature_attrs(fs_info, true);
	अगर (error)
		जाओ failure;

	error = sysfs_create_link(fsid_kobj, &fs_info->sb->s_bdi->dev->kobj, "bdi");
	अगर (error)
		जाओ failure;

	fs_info->space_info_kobj = kobject_create_and_add("allocation",
						  fsid_kobj);
	अगर (!fs_info->space_info_kobj) अणु
		error = -ENOMEM;
		जाओ failure;
	पूर्ण

	error = sysfs_create_files(fs_info->space_info_kobj, allocation_attrs);
	अगर (error)
		जाओ failure;

	वापस 0;
failure:
	btrfs_sysfs_हटाओ_mounted(fs_info);
	वापस error;
पूर्ण

अटल अंतरभूत काष्ठा btrfs_fs_info *qgroup_kobj_to_fs_info(काष्ठा kobject *kobj)
अणु
	वापस to_fs_info(kobj->parent->parent);
पूर्ण

#घोषणा QGROUP_ATTR(_member, _show_name)					\
अटल sमाप_प्रकार btrfs_qgroup_show_##_member(काष्ठा kobject *qgroup_kobj,		\
					   काष्ठा kobj_attribute *a,		\
					   अक्षर *buf)				\
अणु										\
	काष्ठा btrfs_fs_info *fs_info = qgroup_kobj_to_fs_info(qgroup_kobj);	\
	काष्ठा btrfs_qgroup *qgroup = container_of(qgroup_kobj,			\
			काष्ठा btrfs_qgroup, kobj);				\
	वापस btrfs_show_u64(&qgroup->_member, &fs_info->qgroup_lock, buf);	\
पूर्ण										\
BTRFS_ATTR(qgroup, _show_name, btrfs_qgroup_show_##_member)

#घोषणा QGROUP_RSV_ATTR(_name, _type)						\
अटल sमाप_प्रकार btrfs_qgroup_rsv_show_##_name(काष्ठा kobject *qgroup_kobj,	\
					     काष्ठा kobj_attribute *a,		\
					     अक्षर *buf)				\
अणु										\
	काष्ठा btrfs_fs_info *fs_info = qgroup_kobj_to_fs_info(qgroup_kobj);	\
	काष्ठा btrfs_qgroup *qgroup = container_of(qgroup_kobj,			\
			काष्ठा btrfs_qgroup, kobj);				\
	वापस btrfs_show_u64(&qgroup->rsv.values[_type],			\
			&fs_info->qgroup_lock, buf);				\
पूर्ण										\
BTRFS_ATTR(qgroup, rsv_##_name, btrfs_qgroup_rsv_show_##_name)

QGROUP_ATTR(rfer, referenced);
QGROUP_ATTR(excl, exclusive);
QGROUP_ATTR(max_rfer, max_referenced);
QGROUP_ATTR(max_excl, max_exclusive);
QGROUP_ATTR(lim_flags, limit_flags);
QGROUP_RSV_ATTR(data, BTRFS_QGROUP_RSV_DATA);
QGROUP_RSV_ATTR(meta_pertrans, BTRFS_QGROUP_RSV_META_PERTRANS);
QGROUP_RSV_ATTR(meta_pपुनः_स्मृति, BTRFS_QGROUP_RSV_META_PREALLOC);

अटल काष्ठा attribute *qgroup_attrs[] = अणु
	BTRFS_ATTR_PTR(qgroup, referenced),
	BTRFS_ATTR_PTR(qgroup, exclusive),
	BTRFS_ATTR_PTR(qgroup, max_referenced),
	BTRFS_ATTR_PTR(qgroup, max_exclusive),
	BTRFS_ATTR_PTR(qgroup, limit_flags),
	BTRFS_ATTR_PTR(qgroup, rsv_data),
	BTRFS_ATTR_PTR(qgroup, rsv_meta_pertrans),
	BTRFS_ATTR_PTR(qgroup, rsv_meta_pपुनः_स्मृति),
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(qgroup);

अटल व्योम qgroup_release(काष्ठा kobject *kobj)
अणु
	काष्ठा btrfs_qgroup *qgroup = container_of(kobj, काष्ठा btrfs_qgroup, kobj);

	स_रखो(&qgroup->kobj, 0, माप(*kobj));
पूर्ण

अटल काष्ठा kobj_type qgroup_ktype = अणु
	.sysfs_ops = &kobj_sysfs_ops,
	.release = qgroup_release,
	.शेष_groups = qgroup_groups,
पूर्ण;

पूर्णांक btrfs_sysfs_add_one_qgroup(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_qgroup *qgroup)
अणु
	काष्ठा kobject *qgroups_kobj = fs_info->qgroups_kobj;
	पूर्णांक ret;

	अगर (test_bit(BTRFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state))
		वापस 0;
	अगर (qgroup->kobj.state_initialized)
		वापस 0;
	अगर (!qgroups_kobj)
		वापस -EINVAL;

	ret = kobject_init_and_add(&qgroup->kobj, &qgroup_ktype, qgroups_kobj,
			"%hu_%llu", btrfs_qgroup_level(qgroup->qgroupid),
			btrfs_qgroup_subvolid(qgroup->qgroupid));
	अगर (ret < 0)
		kobject_put(&qgroup->kobj);

	वापस ret;
पूर्ण

व्योम btrfs_sysfs_del_qgroups(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_qgroup *qgroup;
	काष्ठा btrfs_qgroup *next;

	अगर (test_bit(BTRFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state))
		वापस;

	rbtree_postorder_क्रम_each_entry_safe(qgroup, next,
					     &fs_info->qgroup_tree, node)
		btrfs_sysfs_del_one_qgroup(fs_info, qgroup);
	अगर (fs_info->qgroups_kobj) अणु
		kobject_del(fs_info->qgroups_kobj);
		kobject_put(fs_info->qgroups_kobj);
		fs_info->qgroups_kobj = शून्य;
	पूर्ण
पूर्ण

/* Called when qgroups get initialized, thus there is no need क्रम locking */
पूर्णांक btrfs_sysfs_add_qgroups(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा kobject *fsid_kobj = &fs_info->fs_devices->fsid_kobj;
	काष्ठा btrfs_qgroup *qgroup;
	काष्ठा btrfs_qgroup *next;
	पूर्णांक ret = 0;

	अगर (test_bit(BTRFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state))
		वापस 0;

	ASSERT(fsid_kobj);
	अगर (fs_info->qgroups_kobj)
		वापस 0;

	fs_info->qgroups_kobj = kobject_create_and_add("qgroups", fsid_kobj);
	अगर (!fs_info->qgroups_kobj) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	rbtree_postorder_क्रम_each_entry_safe(qgroup, next,
					     &fs_info->qgroup_tree, node) अणु
		ret = btrfs_sysfs_add_one_qgroup(fs_info, qgroup);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	अगर (ret < 0)
		btrfs_sysfs_del_qgroups(fs_info);
	वापस ret;
पूर्ण

व्योम btrfs_sysfs_del_one_qgroup(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_qgroup *qgroup)
अणु
	अगर (test_bit(BTRFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state))
		वापस;

	अगर (qgroup->kobj.state_initialized) अणु
		kobject_del(&qgroup->kobj);
		kobject_put(&qgroup->kobj);
	पूर्ण
पूर्ण

/*
 * Change per-fs features in /sys/fs/btrfs/UUID/features to match current
 * values in superblock. Call after any changes to incompat/compat_ro flags
 */
व्योम btrfs_sysfs_feature_update(काष्ठा btrfs_fs_info *fs_info,
		u64 bit, क्रमागत btrfs_feature_set set)
अणु
	काष्ठा btrfs_fs_devices *fs_devs;
	काष्ठा kobject *fsid_kobj;
	u64 __maybe_unused features;
	पूर्णांक __maybe_unused ret;

	अगर (!fs_info)
		वापस;

	/*
	 * See 14e46e04958df74 and e410e34fad913dd, feature bit updates are not
	 * safe when called from some contexts (eg. balance)
	 */
	features = get_features(fs_info, set);
	ASSERT(bit & supported_feature_masks[set]);

	fs_devs = fs_info->fs_devices;
	fsid_kobj = &fs_devs->fsid_kobj;

	अगर (!fsid_kobj->state_initialized)
		वापस;

	/*
	 * FIXME: this is too heavy to update just one value, ideally we'd like
	 * to use sysfs_update_group but some refactoring is needed first.
	 */
	sysfs_हटाओ_group(fsid_kobj, &btrfs_feature_attr_group);
	ret = sysfs_create_group(fsid_kobj, &btrfs_feature_attr_group);
पूर्ण

पूर्णांक __init btrfs_init_sysfs(व्योम)
अणु
	पूर्णांक ret;

	btrfs_kset = kset_create_and_add("btrfs", शून्य, fs_kobj);
	अगर (!btrfs_kset)
		वापस -ENOMEM;

	init_feature_attrs();
	ret = sysfs_create_group(&btrfs_kset->kobj, &btrfs_feature_attr_group);
	अगर (ret)
		जाओ out2;
	ret = sysfs_merge_group(&btrfs_kset->kobj,
				&btrfs_अटल_feature_attr_group);
	अगर (ret)
		जाओ out_हटाओ_group;

#अगर_घोषित CONFIG_BTRFS_DEBUG
	ret = sysfs_create_group(&btrfs_kset->kobj, &btrfs_debug_feature_attr_group);
	अगर (ret)
		जाओ out2;
#पूर्ण_अगर

	वापस 0;

out_हटाओ_group:
	sysfs_हटाओ_group(&btrfs_kset->kobj, &btrfs_feature_attr_group);
out2:
	kset_unरेजिस्टर(btrfs_kset);

	वापस ret;
पूर्ण

व्योम __cold btrfs_निकास_sysfs(व्योम)
अणु
	sysfs_unmerge_group(&btrfs_kset->kobj,
			    &btrfs_अटल_feature_attr_group);
	sysfs_हटाओ_group(&btrfs_kset->kobj, &btrfs_feature_attr_group);
#अगर_घोषित CONFIG_BTRFS_DEBUG
	sysfs_हटाओ_group(&btrfs_kset->kobj, &btrfs_debug_feature_attr_group);
#पूर्ण_अगर
	kset_unरेजिस्टर(btrfs_kset);
पूर्ण

