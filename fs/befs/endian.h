<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/fs/befs/endian.h
 *
 * Copyright (C) 2001 Will Dyson <will_dyson@pobox.com>
 *
 * Partially based on similar funtions in the sysv driver.
 */

#अगर_अघोषित LINUX_BEFS_ENDIAN
#घोषणा LINUX_BEFS_ENDIAN

#समावेश <यंत्र/byteorder.h>

अटल अंतरभूत u64
fs64_to_cpu(स्थिर काष्ठा super_block *sb, fs64 n)
अणु
	अगर (BEFS_SB(sb)->byte_order == BEFS_BYTESEX_LE)
		वापस le64_to_cpu((__क्रमce __le64)n);
	अन्यथा
		वापस be64_to_cpu((__क्रमce __be64)n);
पूर्ण

अटल अंतरभूत fs64
cpu_to_fs64(स्थिर काष्ठा super_block *sb, u64 n)
अणु
	अगर (BEFS_SB(sb)->byte_order == BEFS_BYTESEX_LE)
		वापस (__क्रमce fs64)cpu_to_le64(n);
	अन्यथा
		वापस (__क्रमce fs64)cpu_to_be64(n);
पूर्ण

अटल अंतरभूत u32
fs32_to_cpu(स्थिर काष्ठा super_block *sb, fs32 n)
अणु
	अगर (BEFS_SB(sb)->byte_order == BEFS_BYTESEX_LE)
		वापस le32_to_cpu((__क्रमce __le32)n);
	अन्यथा
		वापस be32_to_cpu((__क्रमce __be32)n);
पूर्ण

अटल अंतरभूत fs32
cpu_to_fs32(स्थिर काष्ठा super_block *sb, u32 n)
अणु
	अगर (BEFS_SB(sb)->byte_order == BEFS_BYTESEX_LE)
		वापस (__क्रमce fs32)cpu_to_le32(n);
	अन्यथा
		वापस (__क्रमce fs32)cpu_to_be32(n);
पूर्ण

अटल अंतरभूत u16
fs16_to_cpu(स्थिर काष्ठा super_block *sb, fs16 n)
अणु
	अगर (BEFS_SB(sb)->byte_order == BEFS_BYTESEX_LE)
		वापस le16_to_cpu((__क्रमce __le16)n);
	अन्यथा
		वापस be16_to_cpu((__क्रमce __be16)n);
पूर्ण

अटल अंतरभूत fs16
cpu_to_fs16(स्थिर काष्ठा super_block *sb, u16 n)
अणु
	अगर (BEFS_SB(sb)->byte_order == BEFS_BYTESEX_LE)
		वापस (__क्रमce fs16)cpu_to_le16(n);
	अन्यथा
		वापस (__क्रमce fs16)cpu_to_be16(n);
पूर्ण

/* Composite types below here */

अटल अंतरभूत befs_block_run
fsrun_to_cpu(स्थिर काष्ठा super_block *sb, befs_disk_block_run n)
अणु
	befs_block_run run;

	अगर (BEFS_SB(sb)->byte_order == BEFS_BYTESEX_LE) अणु
		run.allocation_group = le32_to_cpu((__क्रमce __le32)n.allocation_group);
		run.start = le16_to_cpu((__क्रमce __le16)n.start);
		run.len = le16_to_cpu((__क्रमce __le16)n.len);
	पूर्ण अन्यथा अणु
		run.allocation_group = be32_to_cpu((__क्रमce __be32)n.allocation_group);
		run.start = be16_to_cpu((__क्रमce __be16)n.start);
		run.len = be16_to_cpu((__क्रमce __be16)n.len);
	पूर्ण
	वापस run;
पूर्ण

अटल अंतरभूत befs_disk_block_run
cpu_to_fsrun(स्थिर काष्ठा super_block *sb, befs_block_run n)
अणु
	befs_disk_block_run run;

	अगर (BEFS_SB(sb)->byte_order == BEFS_BYTESEX_LE) अणु
		run.allocation_group = cpu_to_le32(n.allocation_group);
		run.start = cpu_to_le16(n.start);
		run.len = cpu_to_le16(n.len);
	पूर्ण अन्यथा अणु
		run.allocation_group = cpu_to_be32(n.allocation_group);
		run.start = cpu_to_be16(n.start);
		run.len = cpu_to_be16(n.len);
	पूर्ण
	वापस run;
पूर्ण

अटल अंतरभूत befs_data_stream
fsds_to_cpu(स्थिर काष्ठा super_block *sb, स्थिर befs_disk_data_stream *n)
अणु
	befs_data_stream data;
	पूर्णांक i;

	क्रम (i = 0; i < BEFS_NUM_सूचीECT_BLOCKS; ++i)
		data.direct[i] = fsrun_to_cpu(sb, n->direct[i]);

	data.max_direct_range = fs64_to_cpu(sb, n->max_direct_range);
	data.indirect = fsrun_to_cpu(sb, n->indirect);
	data.max_indirect_range = fs64_to_cpu(sb, n->max_indirect_range);
	data.द्विगुन_indirect = fsrun_to_cpu(sb, n->द्विगुन_indirect);
	data.max_द्विगुन_indirect_range = fs64_to_cpu(sb,
						     n->
						     max_द्विगुन_indirect_range);
	data.size = fs64_to_cpu(sb, n->size);

	वापस data;
पूर्ण

#पूर्ण_अगर				//LINUX_BEFS_ENDIAN
