<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/befs/debug.c
 *
 * Copyright (C) 2001 Will Dyson (will_dyson at pobox.com)
 *
 * With help from the ntfs-tng driver by Anton Altparmakov
 *
 * Copyright (C) 1999  Makoto Kato (m_kato@ga2.so-net.ne.jp)
 *
 * debug functions
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#अगर_घोषित __KERNEL__

#समावेश <मानकतर्क.स>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>

#पूर्ण_अगर				/* __KERNEL__ */

#समावेश "befs.h"

व्योम
befs_error(स्थिर काष्ठा super_block *sb, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	pr_err("(%s): %pV\n", sb->s_id, &vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम
befs_warning(स्थिर काष्ठा super_block *sb, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	pr_warn("(%s): %pV\n", sb->s_id, &vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम
befs_debug(स्थिर काष्ठा super_block *sb, स्थिर अक्षर *fmt, ...)
अणु
#अगर_घोषित CONFIG_BEFS_DEBUG

	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	pr_debug("(%s): %pV\n", sb->s_id, &vaf);
	बहु_पूर्ण(args);

#पूर्ण_अगर				//CONFIG_BEFS_DEBUG
पूर्ण

व्योम
befs_dump_inode(स्थिर काष्ठा super_block *sb, befs_inode *inode)
अणु
#अगर_घोषित CONFIG_BEFS_DEBUG

	befs_block_run पंचांगp_run;

	befs_debug(sb, "befs_inode information");

	befs_debug(sb, "  magic1 %08x", fs32_to_cpu(sb, inode->magic1));

	पंचांगp_run = fsrun_to_cpu(sb, inode->inode_num);
	befs_debug(sb, "  inode_num %u, %hu, %hu",
		   पंचांगp_run.allocation_group, पंचांगp_run.start, पंचांगp_run.len);

	befs_debug(sb, "  uid %u", fs32_to_cpu(sb, inode->uid));
	befs_debug(sb, "  gid %u", fs32_to_cpu(sb, inode->gid));
	befs_debug(sb, "  mode %08x", fs32_to_cpu(sb, inode->mode));
	befs_debug(sb, "  flags %08x", fs32_to_cpu(sb, inode->flags));
	befs_debug(sb, "  create_time %llu",
		   fs64_to_cpu(sb, inode->create_समय));
	befs_debug(sb, "  last_modified_time %llu",
		   fs64_to_cpu(sb, inode->last_modअगरied_समय));

	पंचांगp_run = fsrun_to_cpu(sb, inode->parent);
	befs_debug(sb, "  parent [%u, %hu, %hu]",
		   पंचांगp_run.allocation_group, पंचांगp_run.start, पंचांगp_run.len);

	पंचांगp_run = fsrun_to_cpu(sb, inode->attributes);
	befs_debug(sb, "  attributes [%u, %hu, %hu]",
		   पंचांगp_run.allocation_group, पंचांगp_run.start, पंचांगp_run.len);

	befs_debug(sb, "  type %08x", fs32_to_cpu(sb, inode->type));
	befs_debug(sb, "  inode_size %u", fs32_to_cpu(sb, inode->inode_size));

	अगर (S_ISLNK(fs32_to_cpu(sb, inode->mode))) अणु
		befs_debug(sb, "  Symbolic link [%s]", inode->data.symlink);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 0; i < BEFS_NUM_सूचीECT_BLOCKS; i++) अणु
			पंचांगp_run =
			    fsrun_to_cpu(sb, inode->data.datastream.direct[i]);
			befs_debug(sb, "  direct %d [%u, %hu, %hu]", i,
				   पंचांगp_run.allocation_group, पंचांगp_run.start,
				   पंचांगp_run.len);
		पूर्ण
		befs_debug(sb, "  max_direct_range %llu",
			   fs64_to_cpu(sb,
				       inode->data.datastream.
				       max_direct_range));

		पंचांगp_run = fsrun_to_cpu(sb, inode->data.datastream.indirect);
		befs_debug(sb, "  indirect [%u, %hu, %hu]",
			   पंचांगp_run.allocation_group,
			   पंचांगp_run.start, पंचांगp_run.len);

		befs_debug(sb, "  max_indirect_range %llu",
			   fs64_to_cpu(sb,
				       inode->data.datastream.
				       max_indirect_range));

		पंचांगp_run =
		    fsrun_to_cpu(sb, inode->data.datastream.द्विगुन_indirect);
		befs_debug(sb, "  double indirect [%u, %hu, %hu]",
			   पंचांगp_run.allocation_group, पंचांगp_run.start,
			   पंचांगp_run.len);

		befs_debug(sb, "  max_double_indirect_range %llu",
			   fs64_to_cpu(sb,
				       inode->data.datastream.
				       max_द्विगुन_indirect_range));

		befs_debug(sb, "  size %llu",
			   fs64_to_cpu(sb, inode->data.datastream.size));
	पूर्ण

#पूर्ण_अगर				//CONFIG_BEFS_DEBUG
पूर्ण

/*
 * Display super block काष्ठाure क्रम debug.
 */

व्योम
befs_dump_super_block(स्थिर काष्ठा super_block *sb, befs_super_block *sup)
अणु
#अगर_घोषित CONFIG_BEFS_DEBUG

	befs_block_run पंचांगp_run;

	befs_debug(sb, "befs_super_block information");

	befs_debug(sb, "  name %s", sup->name);
	befs_debug(sb, "  magic1 %08x", fs32_to_cpu(sb, sup->magic1));
	befs_debug(sb, "  fs_byte_order %08x",
		   fs32_to_cpu(sb, sup->fs_byte_order));

	befs_debug(sb, "  block_size %u", fs32_to_cpu(sb, sup->block_size));
	befs_debug(sb, "  block_shift %u", fs32_to_cpu(sb, sup->block_shअगरt));

	befs_debug(sb, "  num_blocks %llu", fs64_to_cpu(sb, sup->num_blocks));
	befs_debug(sb, "  used_blocks %llu", fs64_to_cpu(sb, sup->used_blocks));
	befs_debug(sb, "  inode_size %u", fs32_to_cpu(sb, sup->inode_size));

	befs_debug(sb, "  magic2 %08x", fs32_to_cpu(sb, sup->magic2));
	befs_debug(sb, "  blocks_per_ag %u",
		   fs32_to_cpu(sb, sup->blocks_per_ag));
	befs_debug(sb, "  ag_shift %u", fs32_to_cpu(sb, sup->ag_shअगरt));
	befs_debug(sb, "  num_ags %u", fs32_to_cpu(sb, sup->num_ags));

	befs_debug(sb, "  flags %08x", fs32_to_cpu(sb, sup->flags));

	पंचांगp_run = fsrun_to_cpu(sb, sup->log_blocks);
	befs_debug(sb, "  log_blocks %u, %hu, %hu",
		   पंचांगp_run.allocation_group, पंचांगp_run.start, पंचांगp_run.len);

	befs_debug(sb, "  log_start %lld", fs64_to_cpu(sb, sup->log_start));
	befs_debug(sb, "  log_end %lld", fs64_to_cpu(sb, sup->log_end));

	befs_debug(sb, "  magic3 %08x", fs32_to_cpu(sb, sup->magic3));

	पंचांगp_run = fsrun_to_cpu(sb, sup->root_dir);
	befs_debug(sb, "  root_dir %u, %hu, %hu",
		   पंचांगp_run.allocation_group, पंचांगp_run.start, पंचांगp_run.len);

	पंचांगp_run = fsrun_to_cpu(sb, sup->indices);
	befs_debug(sb, "  indices %u, %hu, %hu",
		   पंचांगp_run.allocation_group, पंचांगp_run.start, पंचांगp_run.len);

#पूर्ण_अगर				//CONFIG_BEFS_DEBUG
पूर्ण

#अगर 0
/* unused */
व्योम
befs_dump_small_data(स्थिर काष्ठा super_block *sb, befs_small_data *sd)
अणु
पूर्ण

/* unused */
व्योम
befs_dump_run(स्थिर काष्ठा super_block *sb, befs_disk_block_run run)
अणु
#अगर_घोषित CONFIG_BEFS_DEBUG

	befs_block_run n = fsrun_to_cpu(sb, run);

	befs_debug(sb, "[%u, %hu, %hu]", n.allocation_group, n.start, n.len);

#पूर्ण_अगर				//CONFIG_BEFS_DEBUG
पूर्ण
#पूर्ण_अगर  /*  0  */

व्योम
befs_dump_index_entry(स्थिर काष्ठा super_block *sb,
		      befs_disk_btree_super *super)
अणु
#अगर_घोषित CONFIG_BEFS_DEBUG

	befs_debug(sb, "Btree super structure");
	befs_debug(sb, "  magic %08x", fs32_to_cpu(sb, super->magic));
	befs_debug(sb, "  node_size %u", fs32_to_cpu(sb, super->node_size));
	befs_debug(sb, "  max_depth %08x", fs32_to_cpu(sb, super->max_depth));

	befs_debug(sb, "  data_type %08x", fs32_to_cpu(sb, super->data_type));
	befs_debug(sb, "  root_node_pointer %016LX",
		   fs64_to_cpu(sb, super->root_node_ptr));
	befs_debug(sb, "  free_node_pointer %016LX",
		   fs64_to_cpu(sb, super->मुक्त_node_ptr));
	befs_debug(sb, "  maximum size %016LX",
		   fs64_to_cpu(sb, super->max_size));

#पूर्ण_अगर				//CONFIG_BEFS_DEBUG
पूर्ण

व्योम
befs_dump_index_node(स्थिर काष्ठा super_block *sb, befs_btree_nodehead *node)
अणु
#अगर_घोषित CONFIG_BEFS_DEBUG

	befs_debug(sb, "Btree node structure");
	befs_debug(sb, "  left %016LX", fs64_to_cpu(sb, node->left));
	befs_debug(sb, "  right %016LX", fs64_to_cpu(sb, node->right));
	befs_debug(sb, "  overflow %016LX", fs64_to_cpu(sb, node->overflow));
	befs_debug(sb, "  all_key_count %hu",
		   fs16_to_cpu(sb, node->all_key_count));
	befs_debug(sb, "  all_key_length %hu",
		   fs16_to_cpu(sb, node->all_key_length));

#पूर्ण_अगर				//CONFIG_BEFS_DEBUG
पूर्ण
