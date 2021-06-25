<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * sysfs.c - sysfs support implementation.
 *
 * Copyright (C) 2005-2014 Nippon Telegraph and Telephone Corporation.
 * Copyright (C) 2014 HGST, Inc., a Western Digital Company.
 *
 * Written by Vyacheslav Dubeyko <Vyacheslav.Dubeyko@hgst.com>
 */

#समावेश <linux/kobject.h>

#समावेश "nilfs.h"
#समावेश "mdt.h"
#समावेश "sufile.h"
#समावेश "cpfile.h"
#समावेश "sysfs.h"

/* /sys/fs/<nilfs>/ */
अटल काष्ठा kset *nilfs_kset;

#घोषणा NILFS_SHOW_TIME(समय_प्रकार_val, buf) (अणु \
		काष्ठा पंचांग res; \
		पूर्णांक count = 0; \
		समय64_to_पंचांग(समय_प्रकार_val, 0, &res); \
		res.पंचांग_year += 1900; \
		res.पंचांग_mon += 1; \
		count = scnम_लिखो(buf, PAGE_SIZE, \
				    "%ld-%.2d-%.2d %.2d:%.2d:%.2d\n", \
				    res.पंचांग_year, res.पंचांग_mon, res.पंचांग_mday, \
				    res.पंचांग_hour, res.पंचांग_min, res.पंचांग_sec);\
		count; \
पूर्ण)

#घोषणा NILFS_DEV_INT_GROUP_OPS(name, parent_name) \
अटल sमाप_प्रकार nilfs_##name##_attr_show(काष्ठा kobject *kobj, \
					काष्ठा attribute *attr, अक्षर *buf) \
अणु \
	काष्ठा the_nilfs *nilfs = container_of(kobj->parent, \
						काष्ठा the_nilfs, \
						ns_##parent_name##_kobj); \
	काष्ठा nilfs_##name##_attr *a = container_of(attr, \
						काष्ठा nilfs_##name##_attr, \
						attr); \
	वापस a->show ? a->show(a, nilfs, buf) : 0; \
पूर्ण \
अटल sमाप_प्रकार nilfs_##name##_attr_store(काष्ठा kobject *kobj, \
					 काष्ठा attribute *attr, \
					 स्थिर अक्षर *buf, माप_प्रकार len) \
अणु \
	काष्ठा the_nilfs *nilfs = container_of(kobj->parent, \
						काष्ठा the_nilfs, \
						ns_##parent_name##_kobj); \
	काष्ठा nilfs_##name##_attr *a = container_of(attr, \
						काष्ठा nilfs_##name##_attr, \
						attr); \
	वापस a->store ? a->store(a, nilfs, buf, len) : 0; \
पूर्ण \
अटल स्थिर काष्ठा sysfs_ops nilfs_##name##_attr_ops = अणु \
	.show	= nilfs_##name##_attr_show, \
	.store	= nilfs_##name##_attr_store, \
पूर्ण

#घोषणा NILFS_DEV_INT_GROUP_TYPE(name, parent_name) \
अटल व्योम nilfs_##name##_attr_release(काष्ठा kobject *kobj) \
अणु \
	काष्ठा nilfs_sysfs_##parent_name##_subgroups *subgroups; \
	काष्ठा the_nilfs *nilfs = container_of(kobj->parent, \
						काष्ठा the_nilfs, \
						ns_##parent_name##_kobj); \
	subgroups = nilfs->ns_##parent_name##_subgroups; \
	complete(&subgroups->sg_##name##_kobj_unरेजिस्टर); \
पूर्ण \
अटल काष्ठा kobj_type nilfs_##name##_ktype = अणु \
	.शेष_attrs	= nilfs_##name##_attrs, \
	.sysfs_ops	= &nilfs_##name##_attr_ops, \
	.release	= nilfs_##name##_attr_release, \
पूर्ण

#घोषणा NILFS_DEV_INT_GROUP_FNS(name, parent_name) \
अटल पूर्णांक nilfs_sysfs_create_##name##_group(काष्ठा the_nilfs *nilfs) \
अणु \
	काष्ठा kobject *parent; \
	काष्ठा kobject *kobj; \
	काष्ठा completion *kobj_unरेजिस्टर; \
	काष्ठा nilfs_sysfs_##parent_name##_subgroups *subgroups; \
	पूर्णांक err; \
	subgroups = nilfs->ns_##parent_name##_subgroups; \
	kobj = &subgroups->sg_##name##_kobj; \
	kobj_unरेजिस्टर = &subgroups->sg_##name##_kobj_unरेजिस्टर; \
	parent = &nilfs->ns_##parent_name##_kobj; \
	kobj->kset = nilfs_kset; \
	init_completion(kobj_unरेजिस्टर); \
	err = kobject_init_and_add(kobj, &nilfs_##name##_ktype, parent, \
				    #name); \
	अगर (err) \
		वापस err; \
	वापस 0; \
पूर्ण \
अटल व्योम nilfs_sysfs_delete_##name##_group(काष्ठा the_nilfs *nilfs) \
अणु \
	kobject_del(&nilfs->ns_##parent_name##_subgroups->sg_##name##_kobj); \
पूर्ण

/************************************************************************
 *                        NILFS snapshot attrs                          *
 ************************************************************************/

अटल sमाप_प्रकार
nilfs_snapshot_inodes_count_show(काष्ठा nilfs_snapshot_attr *attr,
				 काष्ठा nilfs_root *root, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ)atomic64_पढ़ो(&root->inodes_count));
पूर्ण

अटल sमाप_प्रकार
nilfs_snapshot_blocks_count_show(काष्ठा nilfs_snapshot_attr *attr,
				 काष्ठा nilfs_root *root, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ)atomic64_पढ़ो(&root->blocks_count));
पूर्ण

अटल स्थिर अक्षर snapshot_पढ़ोme_str[] =
	"The group contains details about mounted snapshot.\n\n"
	"(1) inodes_count\n\tshow number of inodes for snapshot.\n\n"
	"(2) blocks_count\n\tshow number of blocks for snapshot.\n\n";

अटल sमाप_प्रकार
nilfs_snapshot_README_show(काष्ठा nilfs_snapshot_attr *attr,
			    काष्ठा nilfs_root *root, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, snapshot_पढ़ोme_str);
पूर्ण

NILFS_SNAPSHOT_RO_ATTR(inodes_count);
NILFS_SNAPSHOT_RO_ATTR(blocks_count);
NILFS_SNAPSHOT_RO_ATTR(README);

अटल काष्ठा attribute *nilfs_snapshot_attrs[] = अणु
	NILFS_SNAPSHOT_ATTR_LIST(inodes_count),
	NILFS_SNAPSHOT_ATTR_LIST(blocks_count),
	NILFS_SNAPSHOT_ATTR_LIST(README),
	शून्य,
पूर्ण;

अटल sमाप_प्रकार nilfs_snapshot_attr_show(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा nilfs_root *root =
			container_of(kobj, काष्ठा nilfs_root, snapshot_kobj);
	काष्ठा nilfs_snapshot_attr *a =
			container_of(attr, काष्ठा nilfs_snapshot_attr, attr);

	वापस a->show ? a->show(a, root, buf) : 0;
पूर्ण

अटल sमाप_प्रकार nilfs_snapshot_attr_store(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nilfs_root *root =
			container_of(kobj, काष्ठा nilfs_root, snapshot_kobj);
	काष्ठा nilfs_snapshot_attr *a =
			container_of(attr, काष्ठा nilfs_snapshot_attr, attr);

	वापस a->store ? a->store(a, root, buf, len) : 0;
पूर्ण

अटल व्योम nilfs_snapshot_attr_release(काष्ठा kobject *kobj)
अणु
	काष्ठा nilfs_root *root = container_of(kobj, काष्ठा nilfs_root,
						snapshot_kobj);
	complete(&root->snapshot_kobj_unरेजिस्टर);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops nilfs_snapshot_attr_ops = अणु
	.show	= nilfs_snapshot_attr_show,
	.store	= nilfs_snapshot_attr_store,
पूर्ण;

अटल काष्ठा kobj_type nilfs_snapshot_ktype = अणु
	.शेष_attrs	= nilfs_snapshot_attrs,
	.sysfs_ops	= &nilfs_snapshot_attr_ops,
	.release	= nilfs_snapshot_attr_release,
पूर्ण;

पूर्णांक nilfs_sysfs_create_snapshot_group(काष्ठा nilfs_root *root)
अणु
	काष्ठा the_nilfs *nilfs;
	काष्ठा kobject *parent;
	पूर्णांक err;

	nilfs = root->nilfs;
	parent = &nilfs->ns_dev_subgroups->sg_mounted_snapshots_kobj;
	root->snapshot_kobj.kset = nilfs_kset;
	init_completion(&root->snapshot_kobj_unरेजिस्टर);

	अगर (root->cno == NILFS_CPTREE_CURRENT_CNO) अणु
		err = kobject_init_and_add(&root->snapshot_kobj,
					    &nilfs_snapshot_ktype,
					    &nilfs->ns_dev_kobj,
					    "current_checkpoint");
	पूर्ण अन्यथा अणु
		err = kobject_init_and_add(&root->snapshot_kobj,
					    &nilfs_snapshot_ktype,
					    parent,
					    "%llu", root->cno);
	पूर्ण

	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

व्योम nilfs_sysfs_delete_snapshot_group(काष्ठा nilfs_root *root)
अणु
	kobject_del(&root->snapshot_kobj);
पूर्ण

/************************************************************************
 *                    NILFS mounted snapshots attrs                     *
 ************************************************************************/

अटल स्थिर अक्षर mounted_snapshots_पढ़ोme_str[] =
	"The mounted_snapshots group contains group for\n"
	"every mounted snapshot.\n";

अटल sमाप_प्रकार
nilfs_mounted_snapshots_README_show(काष्ठा nilfs_mounted_snapshots_attr *attr,
				    काष्ठा the_nilfs *nilfs, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, mounted_snapshots_पढ़ोme_str);
पूर्ण

NILFS_MOUNTED_SNAPSHOTS_RO_ATTR(README);

अटल काष्ठा attribute *nilfs_mounted_snapshots_attrs[] = अणु
	NILFS_MOUNTED_SNAPSHOTS_ATTR_LIST(README),
	शून्य,
पूर्ण;

NILFS_DEV_INT_GROUP_OPS(mounted_snapshots, dev);
NILFS_DEV_INT_GROUP_TYPE(mounted_snapshots, dev);
NILFS_DEV_INT_GROUP_FNS(mounted_snapshots, dev);

/************************************************************************
 *                      NILFS checkpoपूर्णांकs attrs                         *
 ************************************************************************/

अटल sमाप_प्रकार
nilfs_checkpoपूर्णांकs_checkpoपूर्णांकs_number_show(काष्ठा nilfs_checkpoपूर्णांकs_attr *attr,
					    काष्ठा the_nilfs *nilfs,
					    अक्षर *buf)
अणु
	__u64 ncheckpoपूर्णांकs;
	काष्ठा nilfs_cpstat cpstat;
	पूर्णांक err;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	err = nilfs_cpfile_get_stat(nilfs->ns_cpfile, &cpstat);
	up_पढ़ो(&nilfs->ns_segctor_sem);
	अगर (err < 0) अणु
		nilfs_err(nilfs->ns_sb, "unable to get checkpoint stat: err=%d",
			  err);
		वापस err;
	पूर्ण

	ncheckpoपूर्णांकs = cpstat.cs_ncps;

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", ncheckpoपूर्णांकs);
पूर्ण

अटल sमाप_प्रकार
nilfs_checkpoपूर्णांकs_snapshots_number_show(काष्ठा nilfs_checkpoपूर्णांकs_attr *attr,
					काष्ठा the_nilfs *nilfs,
					अक्षर *buf)
अणु
	__u64 nsnapshots;
	काष्ठा nilfs_cpstat cpstat;
	पूर्णांक err;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	err = nilfs_cpfile_get_stat(nilfs->ns_cpfile, &cpstat);
	up_पढ़ो(&nilfs->ns_segctor_sem);
	अगर (err < 0) अणु
		nilfs_err(nilfs->ns_sb, "unable to get checkpoint stat: err=%d",
			  err);
		वापस err;
	पूर्ण

	nsnapshots = cpstat.cs_nsss;

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", nsnapshots);
पूर्ण

अटल sमाप_प्रकार
nilfs_checkpoपूर्णांकs_last_seg_checkpoपूर्णांक_show(काष्ठा nilfs_checkpoपूर्णांकs_attr *attr,
					    काष्ठा the_nilfs *nilfs,
					    अक्षर *buf)
अणु
	__u64 last_cno;

	spin_lock(&nilfs->ns_last_segment_lock);
	last_cno = nilfs->ns_last_cno;
	spin_unlock(&nilfs->ns_last_segment_lock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", last_cno);
पूर्ण

अटल sमाप_प्रकार
nilfs_checkpoपूर्णांकs_next_checkpoपूर्णांक_show(काष्ठा nilfs_checkpoपूर्णांकs_attr *attr,
					काष्ठा the_nilfs *nilfs,
					अक्षर *buf)
अणु
	__u64 cno;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	cno = nilfs->ns_cno;
	up_पढ़ो(&nilfs->ns_segctor_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", cno);
पूर्ण

अटल स्थिर अक्षर checkpoपूर्णांकs_पढ़ोme_str[] =
	"The checkpoints group contains attributes that describe\n"
	"details about volume's checkpoints.\n\n"
	"(1) checkpoints_number\n\tshow number of checkpoints on volume.\n\n"
	"(2) snapshots_number\n\tshow number of snapshots on volume.\n\n"
	"(3) last_seg_checkpoint\n"
	"\tshow checkpoint number of the latest segment.\n\n"
	"(4) next_checkpoint\n\tshow next checkpoint number.\n\n";

अटल sमाप_प्रकार
nilfs_checkpoपूर्णांकs_README_show(काष्ठा nilfs_checkpoपूर्णांकs_attr *attr,
				काष्ठा the_nilfs *nilfs, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, checkpoपूर्णांकs_पढ़ोme_str);
पूर्ण

NILFS_CHECKPOINTS_RO_ATTR(checkpoपूर्णांकs_number);
NILFS_CHECKPOINTS_RO_ATTR(snapshots_number);
NILFS_CHECKPOINTS_RO_ATTR(last_seg_checkpoपूर्णांक);
NILFS_CHECKPOINTS_RO_ATTR(next_checkpoपूर्णांक);
NILFS_CHECKPOINTS_RO_ATTR(README);

अटल काष्ठा attribute *nilfs_checkpoपूर्णांकs_attrs[] = अणु
	NILFS_CHECKPOINTS_ATTR_LIST(checkpoपूर्णांकs_number),
	NILFS_CHECKPOINTS_ATTR_LIST(snapshots_number),
	NILFS_CHECKPOINTS_ATTR_LIST(last_seg_checkpoपूर्णांक),
	NILFS_CHECKPOINTS_ATTR_LIST(next_checkpoपूर्णांक),
	NILFS_CHECKPOINTS_ATTR_LIST(README),
	शून्य,
पूर्ण;

NILFS_DEV_INT_GROUP_OPS(checkpoपूर्णांकs, dev);
NILFS_DEV_INT_GROUP_TYPE(checkpoपूर्णांकs, dev);
NILFS_DEV_INT_GROUP_FNS(checkpoपूर्णांकs, dev);

/************************************************************************
 *                        NILFS segments attrs                          *
 ************************************************************************/

अटल sमाप_प्रकार
nilfs_segments_segments_number_show(काष्ठा nilfs_segments_attr *attr,
				     काष्ठा the_nilfs *nilfs,
				     अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%lu\n", nilfs->ns_nsegments);
पूर्ण

अटल sमाप_प्रकार
nilfs_segments_blocks_per_segment_show(काष्ठा nilfs_segments_attr *attr,
					काष्ठा the_nilfs *nilfs,
					अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%lu\n", nilfs->ns_blocks_per_segment);
पूर्ण

अटल sमाप_प्रकार
nilfs_segments_clean_segments_show(काष्ठा nilfs_segments_attr *attr,
				    काष्ठा the_nilfs *nilfs,
				    अक्षर *buf)
अणु
	अचिन्हित दीर्घ ncleansegs;

	करोwn_पढ़ो(&NILFS_MDT(nilfs->ns_dat)->mi_sem);
	ncleansegs = nilfs_sufile_get_ncleansegs(nilfs->ns_sufile);
	up_पढ़ो(&NILFS_MDT(nilfs->ns_dat)->mi_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%lu\n", ncleansegs);
पूर्ण

अटल sमाप_प्रकार
nilfs_segments_dirty_segments_show(काष्ठा nilfs_segments_attr *attr,
				    काष्ठा the_nilfs *nilfs,
				    अक्षर *buf)
अणु
	काष्ठा nilfs_sustat sustat;
	पूर्णांक err;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	err = nilfs_sufile_get_stat(nilfs->ns_sufile, &sustat);
	up_पढ़ो(&nilfs->ns_segctor_sem);
	अगर (err < 0) अणु
		nilfs_err(nilfs->ns_sb, "unable to get segment stat: err=%d",
			  err);
		वापस err;
	पूर्ण

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", sustat.ss_ndirtysegs);
पूर्ण

अटल स्थिर अक्षर segments_पढ़ोme_str[] =
	"The segments group contains attributes that describe\n"
	"details about volume's segments.\n\n"
	"(1) segments_number\n\tshow number of segments on volume.\n\n"
	"(2) blocks_per_segment\n\tshow number of blocks in segment.\n\n"
	"(3) clean_segments\n\tshow count of clean segments.\n\n"
	"(4) dirty_segments\n\tshow count of dirty segments.\n\n";

अटल sमाप_प्रकार
nilfs_segments_README_show(काष्ठा nilfs_segments_attr *attr,
			    काष्ठा the_nilfs *nilfs,
			    अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, segments_पढ़ोme_str);
पूर्ण

NILFS_SEGMENTS_RO_ATTR(segments_number);
NILFS_SEGMENTS_RO_ATTR(blocks_per_segment);
NILFS_SEGMENTS_RO_ATTR(clean_segments);
NILFS_SEGMENTS_RO_ATTR(dirty_segments);
NILFS_SEGMENTS_RO_ATTR(README);

अटल काष्ठा attribute *nilfs_segments_attrs[] = अणु
	NILFS_SEGMENTS_ATTR_LIST(segments_number),
	NILFS_SEGMENTS_ATTR_LIST(blocks_per_segment),
	NILFS_SEGMENTS_ATTR_LIST(clean_segments),
	NILFS_SEGMENTS_ATTR_LIST(dirty_segments),
	NILFS_SEGMENTS_ATTR_LIST(README),
	शून्य,
पूर्ण;

NILFS_DEV_INT_GROUP_OPS(segments, dev);
NILFS_DEV_INT_GROUP_TYPE(segments, dev);
NILFS_DEV_INT_GROUP_FNS(segments, dev);

/************************************************************************
 *                        NILFS segctor attrs                           *
 ************************************************************************/

अटल sमाप_प्रकार
nilfs_segctor_last_pseg_block_show(काष्ठा nilfs_segctor_attr *attr,
				    काष्ठा the_nilfs *nilfs,
				    अक्षर *buf)
अणु
	sector_t last_pseg;

	spin_lock(&nilfs->ns_last_segment_lock);
	last_pseg = nilfs->ns_last_pseg;
	spin_unlock(&nilfs->ns_last_segment_lock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ)last_pseg);
पूर्ण

अटल sमाप_प्रकार
nilfs_segctor_last_seg_sequence_show(काष्ठा nilfs_segctor_attr *attr,
					काष्ठा the_nilfs *nilfs,
					अक्षर *buf)
अणु
	u64 last_seq;

	spin_lock(&nilfs->ns_last_segment_lock);
	last_seq = nilfs->ns_last_seq;
	spin_unlock(&nilfs->ns_last_segment_lock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", last_seq);
पूर्ण

अटल sमाप_प्रकार
nilfs_segctor_last_seg_checkpoपूर्णांक_show(काष्ठा nilfs_segctor_attr *attr,
					काष्ठा the_nilfs *nilfs,
					अक्षर *buf)
अणु
	__u64 last_cno;

	spin_lock(&nilfs->ns_last_segment_lock);
	last_cno = nilfs->ns_last_cno;
	spin_unlock(&nilfs->ns_last_segment_lock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", last_cno);
पूर्ण

अटल sमाप_प्रकार
nilfs_segctor_current_seg_sequence_show(काष्ठा nilfs_segctor_attr *attr,
					काष्ठा the_nilfs *nilfs,
					अक्षर *buf)
अणु
	u64 seg_seq;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	seg_seq = nilfs->ns_seg_seq;
	up_पढ़ो(&nilfs->ns_segctor_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", seg_seq);
पूर्ण

अटल sमाप_प्रकार
nilfs_segctor_current_last_full_seg_show(काष्ठा nilfs_segctor_attr *attr,
					 काष्ठा the_nilfs *nilfs,
					 अक्षर *buf)
अणु
	__u64 segnum;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	segnum = nilfs->ns_segnum;
	up_पढ़ो(&nilfs->ns_segctor_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", segnum);
पूर्ण

अटल sमाप_प्रकार
nilfs_segctor_next_full_seg_show(काष्ठा nilfs_segctor_attr *attr,
				 काष्ठा the_nilfs *nilfs,
				 अक्षर *buf)
अणु
	__u64 nextnum;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	nextnum = nilfs->ns_nextnum;
	up_पढ़ो(&nilfs->ns_segctor_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", nextnum);
पूर्ण

अटल sमाप_प्रकार
nilfs_segctor_next_pseg_offset_show(काष्ठा nilfs_segctor_attr *attr,
					काष्ठा the_nilfs *nilfs,
					अक्षर *buf)
अणु
	अचिन्हित दीर्घ pseg_offset;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	pseg_offset = nilfs->ns_pseg_offset;
	up_पढ़ो(&nilfs->ns_segctor_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%lu\n", pseg_offset);
पूर्ण

अटल sमाप_प्रकार
nilfs_segctor_next_checkpoपूर्णांक_show(काष्ठा nilfs_segctor_attr *attr,
					काष्ठा the_nilfs *nilfs,
					अक्षर *buf)
अणु
	__u64 cno;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	cno = nilfs->ns_cno;
	up_पढ़ो(&nilfs->ns_segctor_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", cno);
पूर्ण

अटल sमाप_प्रकार
nilfs_segctor_last_seg_ग_लिखो_समय_show(काष्ठा nilfs_segctor_attr *attr,
					काष्ठा the_nilfs *nilfs,
					अक्षर *buf)
अणु
	समय64_t स_समय;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	स_समय = nilfs->ns_स_समय;
	up_पढ़ो(&nilfs->ns_segctor_sem);

	वापस NILFS_SHOW_TIME(स_समय, buf);
पूर्ण

अटल sमाप_प्रकार
nilfs_segctor_last_seg_ग_लिखो_समय_secs_show(काष्ठा nilfs_segctor_attr *attr,
					    काष्ठा the_nilfs *nilfs,
					    अक्षर *buf)
अणु
	समय64_t स_समय;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	स_समय = nilfs->ns_स_समय;
	up_पढ़ो(&nilfs->ns_segctor_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", स_समय);
पूर्ण

अटल sमाप_प्रकार
nilfs_segctor_last_nongc_ग_लिखो_समय_show(काष्ठा nilfs_segctor_attr *attr,
					 काष्ठा the_nilfs *nilfs,
					 अक्षर *buf)
अणु
	समय64_t nongc_स_समय;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	nongc_स_समय = nilfs->ns_nongc_स_समय;
	up_पढ़ो(&nilfs->ns_segctor_sem);

	वापस NILFS_SHOW_TIME(nongc_स_समय, buf);
पूर्ण

अटल sमाप_प्रकार
nilfs_segctor_last_nongc_ग_लिखो_समय_secs_show(काष्ठा nilfs_segctor_attr *attr,
						काष्ठा the_nilfs *nilfs,
						अक्षर *buf)
अणु
	समय64_t nongc_स_समय;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	nongc_स_समय = nilfs->ns_nongc_स_समय;
	up_पढ़ो(&nilfs->ns_segctor_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", nongc_स_समय);
पूर्ण

अटल sमाप_प्रकार
nilfs_segctor_dirty_data_blocks_count_show(काष्ठा nilfs_segctor_attr *attr,
					    काष्ठा the_nilfs *nilfs,
					    अक्षर *buf)
अणु
	u32 ndirtyblks;

	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	ndirtyblks = atomic_पढ़ो(&nilfs->ns_ndirtyblks);
	up_पढ़ो(&nilfs->ns_segctor_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", ndirtyblks);
पूर्ण

अटल स्थिर अक्षर segctor_पढ़ोme_str[] =
	"The segctor group contains attributes that describe\n"
	"segctor thread activity details.\n\n"
	"(1) last_pseg_block\n"
	"\tshow start block number of the latest segment.\n\n"
	"(2) last_seg_sequence\n"
	"\tshow sequence value of the latest segment.\n\n"
	"(3) last_seg_checkpoint\n"
	"\tshow checkpoint number of the latest segment.\n\n"
	"(4) current_seg_sequence\n\tshow segment sequence counter.\n\n"
	"(5) current_last_full_seg\n"
	"\tshow index number of the latest full segment.\n\n"
	"(6) next_full_seg\n"
	"\tshow index number of the full segment index to be used next.\n\n"
	"(7) next_pseg_offset\n"
	"\tshow offset of next partial segment in the current full segment.\n\n"
	"(8) next_checkpoint\n\tshow next checkpoint number.\n\n"
	"(9) last_seg_write_time\n"
	"\tshow write time of the last segment in human-readable format.\n\n"
	"(10) last_seg_write_time_secs\n"
	"\tshow write time of the last segment in seconds.\n\n"
	"(11) last_nongc_write_time\n"
	"\tshow write time of the last segment not for cleaner operation "
	"in human-readable format.\n\n"
	"(12) last_nongc_write_time_secs\n"
	"\tshow write time of the last segment not for cleaner operation "
	"in seconds.\n\n"
	"(13) dirty_data_blocks_count\n"
	"\tshow number of dirty data blocks.\n\n";

अटल sमाप_प्रकार
nilfs_segctor_README_show(काष्ठा nilfs_segctor_attr *attr,
			  काष्ठा the_nilfs *nilfs, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, segctor_पढ़ोme_str);
पूर्ण

NILFS_SEGCTOR_RO_ATTR(last_pseg_block);
NILFS_SEGCTOR_RO_ATTR(last_seg_sequence);
NILFS_SEGCTOR_RO_ATTR(last_seg_checkpoपूर्णांक);
NILFS_SEGCTOR_RO_ATTR(current_seg_sequence);
NILFS_SEGCTOR_RO_ATTR(current_last_full_seg);
NILFS_SEGCTOR_RO_ATTR(next_full_seg);
NILFS_SEGCTOR_RO_ATTR(next_pseg_offset);
NILFS_SEGCTOR_RO_ATTR(next_checkpoपूर्णांक);
NILFS_SEGCTOR_RO_ATTR(last_seg_ग_लिखो_समय);
NILFS_SEGCTOR_RO_ATTR(last_seg_ग_लिखो_समय_secs);
NILFS_SEGCTOR_RO_ATTR(last_nongc_ग_लिखो_समय);
NILFS_SEGCTOR_RO_ATTR(last_nongc_ग_लिखो_समय_secs);
NILFS_SEGCTOR_RO_ATTR(dirty_data_blocks_count);
NILFS_SEGCTOR_RO_ATTR(README);

अटल काष्ठा attribute *nilfs_segctor_attrs[] = अणु
	NILFS_SEGCTOR_ATTR_LIST(last_pseg_block),
	NILFS_SEGCTOR_ATTR_LIST(last_seg_sequence),
	NILFS_SEGCTOR_ATTR_LIST(last_seg_checkpoपूर्णांक),
	NILFS_SEGCTOR_ATTR_LIST(current_seg_sequence),
	NILFS_SEGCTOR_ATTR_LIST(current_last_full_seg),
	NILFS_SEGCTOR_ATTR_LIST(next_full_seg),
	NILFS_SEGCTOR_ATTR_LIST(next_pseg_offset),
	NILFS_SEGCTOR_ATTR_LIST(next_checkpoपूर्णांक),
	NILFS_SEGCTOR_ATTR_LIST(last_seg_ग_लिखो_समय),
	NILFS_SEGCTOR_ATTR_LIST(last_seg_ग_लिखो_समय_secs),
	NILFS_SEGCTOR_ATTR_LIST(last_nongc_ग_लिखो_समय),
	NILFS_SEGCTOR_ATTR_LIST(last_nongc_ग_लिखो_समय_secs),
	NILFS_SEGCTOR_ATTR_LIST(dirty_data_blocks_count),
	NILFS_SEGCTOR_ATTR_LIST(README),
	शून्य,
पूर्ण;

NILFS_DEV_INT_GROUP_OPS(segctor, dev);
NILFS_DEV_INT_GROUP_TYPE(segctor, dev);
NILFS_DEV_INT_GROUP_FNS(segctor, dev);

/************************************************************************
 *                        NILFS superblock attrs                        *
 ************************************************************************/

अटल sमाप_प्रकार
nilfs_superblock_sb_ग_लिखो_समय_show(काष्ठा nilfs_superblock_attr *attr,
				     काष्ठा the_nilfs *nilfs,
				     अक्षर *buf)
अणु
	समय64_t sbwसमय;

	करोwn_पढ़ो(&nilfs->ns_sem);
	sbwसमय = nilfs->ns_sbwसमय;
	up_पढ़ो(&nilfs->ns_sem);

	वापस NILFS_SHOW_TIME(sbwसमय, buf);
पूर्ण

अटल sमाप_प्रकार
nilfs_superblock_sb_ग_लिखो_समय_secs_show(काष्ठा nilfs_superblock_attr *attr,
					 काष्ठा the_nilfs *nilfs,
					 अक्षर *buf)
अणु
	समय64_t sbwसमय;

	करोwn_पढ़ो(&nilfs->ns_sem);
	sbwसमय = nilfs->ns_sbwसमय;
	up_पढ़ो(&nilfs->ns_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", sbwसमय);
पूर्ण

अटल sमाप_प्रकार
nilfs_superblock_sb_ग_लिखो_count_show(काष्ठा nilfs_superblock_attr *attr,
				      काष्ठा the_nilfs *nilfs,
				      अक्षर *buf)
अणु
	अचिन्हित पूर्णांक sbwcount;

	करोwn_पढ़ो(&nilfs->ns_sem);
	sbwcount = nilfs->ns_sbwcount;
	up_पढ़ो(&nilfs->ns_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", sbwcount);
पूर्ण

अटल sमाप_प्रकार
nilfs_superblock_sb_update_frequency_show(काष्ठा nilfs_superblock_attr *attr,
					    काष्ठा the_nilfs *nilfs,
					    अक्षर *buf)
अणु
	अचिन्हित पूर्णांक sb_update_freq;

	करोwn_पढ़ो(&nilfs->ns_sem);
	sb_update_freq = nilfs->ns_sb_update_freq;
	up_पढ़ो(&nilfs->ns_sem);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", sb_update_freq);
पूर्ण

अटल sमाप_प्रकार
nilfs_superblock_sb_update_frequency_store(काष्ठा nilfs_superblock_attr *attr,
					    काष्ठा the_nilfs *nilfs,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = kstrtouपूर्णांक(skip_spaces(buf), 0, &val);
	अगर (err) अणु
		nilfs_err(nilfs->ns_sb, "unable to convert string: err=%d",
			  err);
		वापस err;
	पूर्ण

	अगर (val < NILFS_SB_FREQ) अणु
		val = NILFS_SB_FREQ;
		nilfs_warn(nilfs->ns_sb,
			   "superblock update frequency cannot be lesser than 10 seconds");
	पूर्ण

	करोwn_ग_लिखो(&nilfs->ns_sem);
	nilfs->ns_sb_update_freq = val;
	up_ग_लिखो(&nilfs->ns_sem);

	वापस count;
पूर्ण

अटल स्थिर अक्षर sb_पढ़ोme_str[] =
	"The superblock group contains attributes that describe\n"
	"superblock's details.\n\n"
	"(1) sb_write_time\n\tshow previous write time of super block "
	"in human-readable format.\n\n"
	"(2) sb_write_time_secs\n\tshow previous write time of super block "
	"in seconds.\n\n"
	"(3) sb_write_count\n\tshow write count of super block.\n\n"
	"(4) sb_update_frequency\n"
	"\tshow/set interval of periodical update of superblock (in seconds).\n\n"
	"\tYou can set preferable frequency of superblock update by command:\n\n"
	"\t'echo <val> > /sys/fs/<nilfs>/<dev>/superblock/sb_update_frequency'\n";

अटल sमाप_प्रकार
nilfs_superblock_README_show(काष्ठा nilfs_superblock_attr *attr,
				काष्ठा the_nilfs *nilfs, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, sb_पढ़ोme_str);
पूर्ण

NILFS_SUPERBLOCK_RO_ATTR(sb_ग_लिखो_समय);
NILFS_SUPERBLOCK_RO_ATTR(sb_ग_लिखो_समय_secs);
NILFS_SUPERBLOCK_RO_ATTR(sb_ग_लिखो_count);
NILFS_SUPERBLOCK_RW_ATTR(sb_update_frequency);
NILFS_SUPERBLOCK_RO_ATTR(README);

अटल काष्ठा attribute *nilfs_superblock_attrs[] = अणु
	NILFS_SUPERBLOCK_ATTR_LIST(sb_ग_लिखो_समय),
	NILFS_SUPERBLOCK_ATTR_LIST(sb_ग_लिखो_समय_secs),
	NILFS_SUPERBLOCK_ATTR_LIST(sb_ग_लिखो_count),
	NILFS_SUPERBLOCK_ATTR_LIST(sb_update_frequency),
	NILFS_SUPERBLOCK_ATTR_LIST(README),
	शून्य,
पूर्ण;

NILFS_DEV_INT_GROUP_OPS(superblock, dev);
NILFS_DEV_INT_GROUP_TYPE(superblock, dev);
NILFS_DEV_INT_GROUP_FNS(superblock, dev);

/************************************************************************
 *                        NILFS device attrs                            *
 ************************************************************************/

अटल
sमाप_प्रकार nilfs_dev_revision_show(काष्ठा nilfs_dev_attr *attr,
				काष्ठा the_nilfs *nilfs,
				अक्षर *buf)
अणु
	काष्ठा nilfs_super_block **sbp = nilfs->ns_sbp;
	u32 major = le32_to_cpu(sbp[0]->s_rev_level);
	u16 minor = le16_to_cpu(sbp[0]->s_minor_rev_level);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d.%d\n", major, minor);
पूर्ण

अटल
sमाप_प्रकार nilfs_dev_blocksize_show(काष्ठा nilfs_dev_attr *attr,
				 काष्ठा the_nilfs *nilfs,
				 अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", nilfs->ns_blocksize);
पूर्ण

अटल
sमाप_प्रकार nilfs_dev_device_size_show(काष्ठा nilfs_dev_attr *attr,
				    काष्ठा the_nilfs *nilfs,
				    अक्षर *buf)
अणु
	काष्ठा nilfs_super_block **sbp = nilfs->ns_sbp;
	u64 dev_size = le64_to_cpu(sbp[0]->s_dev_size);

	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", dev_size);
पूर्ण

अटल
sमाप_प्रकार nilfs_dev_मुक्त_blocks_show(काष्ठा nilfs_dev_attr *attr,
				   काष्ठा the_nilfs *nilfs,
				   अक्षर *buf)
अणु
	sector_t मुक्त_blocks = 0;

	nilfs_count_मुक्त_blocks(nilfs, &मुक्त_blocks);
	वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n",
			(अचिन्हित दीर्घ दीर्घ)मुक्त_blocks);
पूर्ण

अटल
sमाप_प्रकार nilfs_dev_uuid_show(काष्ठा nilfs_dev_attr *attr,
			    काष्ठा the_nilfs *nilfs,
			    अक्षर *buf)
अणु
	काष्ठा nilfs_super_block **sbp = nilfs->ns_sbp;

	वापस snम_लिखो(buf, PAGE_SIZE, "%pUb\n", sbp[0]->s_uuid);
पूर्ण

अटल
sमाप_प्रकार nilfs_dev_volume_name_show(काष्ठा nilfs_dev_attr *attr,
				    काष्ठा the_nilfs *nilfs,
				    अक्षर *buf)
अणु
	काष्ठा nilfs_super_block **sbp = nilfs->ns_sbp;

	वापस scnम_लिखो(buf, माप(sbp[0]->s_volume_name), "%s\n",
			 sbp[0]->s_volume_name);
पूर्ण

अटल स्थिर अक्षर dev_पढ़ोme_str[] =
	"The <device> group contains attributes that describe file system\n"
	"partition's details.\n\n"
	"(1) revision\n\tshow NILFS file system revision.\n\n"
	"(2) blocksize\n\tshow volume block size in bytes.\n\n"
	"(3) device_size\n\tshow volume size in bytes.\n\n"
	"(4) free_blocks\n\tshow count of free blocks on volume.\n\n"
	"(5) uuid\n\tshow volume's UUID.\n\n"
	"(6) volume_name\n\tshow volume's name.\n\n";

अटल sमाप_प्रकार nilfs_dev_README_show(काष्ठा nilfs_dev_attr *attr,
				     काष्ठा the_nilfs *nilfs,
				     अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, dev_पढ़ोme_str);
पूर्ण

NILFS_DEV_RO_ATTR(revision);
NILFS_DEV_RO_ATTR(blocksize);
NILFS_DEV_RO_ATTR(device_size);
NILFS_DEV_RO_ATTR(मुक्त_blocks);
NILFS_DEV_RO_ATTR(uuid);
NILFS_DEV_RO_ATTR(volume_name);
NILFS_DEV_RO_ATTR(README);

अटल काष्ठा attribute *nilfs_dev_attrs[] = अणु
	NILFS_DEV_ATTR_LIST(revision),
	NILFS_DEV_ATTR_LIST(blocksize),
	NILFS_DEV_ATTR_LIST(device_size),
	NILFS_DEV_ATTR_LIST(मुक्त_blocks),
	NILFS_DEV_ATTR_LIST(uuid),
	NILFS_DEV_ATTR_LIST(volume_name),
	NILFS_DEV_ATTR_LIST(README),
	शून्य,
पूर्ण;

अटल sमाप_प्रकार nilfs_dev_attr_show(काष्ठा kobject *kobj,
				    काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा the_nilfs *nilfs = container_of(kobj, काष्ठा the_nilfs,
						ns_dev_kobj);
	काष्ठा nilfs_dev_attr *a = container_of(attr, काष्ठा nilfs_dev_attr,
						attr);

	वापस a->show ? a->show(a, nilfs, buf) : 0;
पूर्ण

अटल sमाप_प्रकार nilfs_dev_attr_store(काष्ठा kobject *kobj,
				    काष्ठा attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा the_nilfs *nilfs = container_of(kobj, काष्ठा the_nilfs,
						ns_dev_kobj);
	काष्ठा nilfs_dev_attr *a = container_of(attr, काष्ठा nilfs_dev_attr,
						attr);

	वापस a->store ? a->store(a, nilfs, buf, len) : 0;
पूर्ण

अटल व्योम nilfs_dev_attr_release(काष्ठा kobject *kobj)
अणु
	काष्ठा the_nilfs *nilfs = container_of(kobj, काष्ठा the_nilfs,
						ns_dev_kobj);
	complete(&nilfs->ns_dev_kobj_unरेजिस्टर);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops nilfs_dev_attr_ops = अणु
	.show	= nilfs_dev_attr_show,
	.store	= nilfs_dev_attr_store,
पूर्ण;

अटल काष्ठा kobj_type nilfs_dev_ktype = अणु
	.शेष_attrs	= nilfs_dev_attrs,
	.sysfs_ops	= &nilfs_dev_attr_ops,
	.release	= nilfs_dev_attr_release,
पूर्ण;

पूर्णांक nilfs_sysfs_create_device_group(काष्ठा super_block *sb)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	माप_प्रकार devgrp_size = माप(काष्ठा nilfs_sysfs_dev_subgroups);
	पूर्णांक err;

	nilfs->ns_dev_subgroups = kzalloc(devgrp_size, GFP_KERNEL);
	अगर (unlikely(!nilfs->ns_dev_subgroups)) अणु
		err = -ENOMEM;
		nilfs_err(sb, "unable to allocate memory for device group");
		जाओ failed_create_device_group;
	पूर्ण

	nilfs->ns_dev_kobj.kset = nilfs_kset;
	init_completion(&nilfs->ns_dev_kobj_unरेजिस्टर);
	err = kobject_init_and_add(&nilfs->ns_dev_kobj, &nilfs_dev_ktype, शून्य,
				    "%s", sb->s_id);
	अगर (err)
		जाओ मुक्त_dev_subgroups;

	err = nilfs_sysfs_create_mounted_snapshots_group(nilfs);
	अगर (err)
		जाओ cleanup_dev_kobject;

	err = nilfs_sysfs_create_checkpoपूर्णांकs_group(nilfs);
	अगर (err)
		जाओ delete_mounted_snapshots_group;

	err = nilfs_sysfs_create_segments_group(nilfs);
	अगर (err)
		जाओ delete_checkpoपूर्णांकs_group;

	err = nilfs_sysfs_create_superblock_group(nilfs);
	अगर (err)
		जाओ delete_segments_group;

	err = nilfs_sysfs_create_segctor_group(nilfs);
	अगर (err)
		जाओ delete_superblock_group;

	वापस 0;

delete_superblock_group:
	nilfs_sysfs_delete_superblock_group(nilfs);

delete_segments_group:
	nilfs_sysfs_delete_segments_group(nilfs);

delete_checkpoपूर्णांकs_group:
	nilfs_sysfs_delete_checkpoपूर्णांकs_group(nilfs);

delete_mounted_snapshots_group:
	nilfs_sysfs_delete_mounted_snapshots_group(nilfs);

cleanup_dev_kobject:
	kobject_del(&nilfs->ns_dev_kobj);

मुक्त_dev_subgroups:
	kमुक्त(nilfs->ns_dev_subgroups);

failed_create_device_group:
	वापस err;
पूर्ण

व्योम nilfs_sysfs_delete_device_group(काष्ठा the_nilfs *nilfs)
अणु
	nilfs_sysfs_delete_mounted_snapshots_group(nilfs);
	nilfs_sysfs_delete_checkpoपूर्णांकs_group(nilfs);
	nilfs_sysfs_delete_segments_group(nilfs);
	nilfs_sysfs_delete_superblock_group(nilfs);
	nilfs_sysfs_delete_segctor_group(nilfs);
	kobject_del(&nilfs->ns_dev_kobj);
	kमुक्त(nilfs->ns_dev_subgroups);
पूर्ण

/************************************************************************
 *                        NILFS feature attrs                           *
 ************************************************************************/

अटल sमाप_प्रकार nilfs_feature_revision_show(काष्ठा kobject *kobj,
					    काष्ठा attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d.%d\n",
			NILFS_CURRENT_REV, NILFS_MINOR_REV);
पूर्ण

अटल स्थिर अक्षर features_पढ़ोme_str[] =
	"The features group contains attributes that describe NILFS file\n"
	"system driver features.\n\n"
	"(1) revision\n\tshow current revision of NILFS file system driver.\n";

अटल sमाप_प्रकार nilfs_feature_README_show(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr,
					 अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, features_पढ़ोme_str);
पूर्ण

NILFS_FEATURE_RO_ATTR(revision);
NILFS_FEATURE_RO_ATTR(README);

अटल काष्ठा attribute *nilfs_feature_attrs[] = अणु
	NILFS_FEATURE_ATTR_LIST(revision),
	NILFS_FEATURE_ATTR_LIST(README),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nilfs_feature_attr_group = अणु
	.name = "features",
	.attrs = nilfs_feature_attrs,
पूर्ण;

पूर्णांक __init nilfs_sysfs_init(व्योम)
अणु
	पूर्णांक err;

	nilfs_kset = kset_create_and_add(NILFS_ROOT_GROUP_NAME, शून्य, fs_kobj);
	अगर (!nilfs_kset) अणु
		err = -ENOMEM;
		nilfs_err(शून्य, "unable to create sysfs entry: err=%d", err);
		जाओ failed_sysfs_init;
	पूर्ण

	err = sysfs_create_group(&nilfs_kset->kobj, &nilfs_feature_attr_group);
	अगर (unlikely(err)) अणु
		nilfs_err(शून्य, "unable to create feature group: err=%d", err);
		जाओ cleanup_sysfs_init;
	पूर्ण

	वापस 0;

cleanup_sysfs_init:
	kset_unरेजिस्टर(nilfs_kset);

failed_sysfs_init:
	वापस err;
पूर्ण

व्योम nilfs_sysfs_निकास(व्योम)
अणु
	sysfs_हटाओ_group(&nilfs_kset->kobj, &nilfs_feature_attr_group);
	kset_unरेजिस्टर(nilfs_kset);
पूर्ण
