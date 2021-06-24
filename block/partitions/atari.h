<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  fs/partitions/atari.h
 *  Moved by Russell King from:
 *
 * linux/include/linux/atari_rootsec.h
 * definitions क्रम Atari Rootsector layout
 * by Andreas Schwab (schwab@ls5.inक्रमmatik.uni-करोrपंचांगund.de)
 *
 * modअगरied क्रम ICD/Supra partitioning scheme restricted to at most 12
 * partitions
 * by Guenther Kelleter (guenther@pool.inक्रमmatik.rwth-aachen.de)
 */

#समावेश <linux/compiler.h>

काष्ठा partition_info
अणु
  u8 flg;			/* bit 0: active; bit 7: bootable */
  अक्षर id[3];			/* "GEM", "BGM", "XGM", or other */
  __be32 st;			/* start of partition */
  __be32 siz;			/* length of partition */
पूर्ण;

काष्ठा rootsector
अणु
  अक्षर unused[0x156];		/* room क्रम boot code */
  काष्ठा partition_info icdpart[8];	/* info क्रम ICD-partitions 5..12 */
  अक्षर unused2[0xc];
  u32 hd_siz;			/* size of disk in blocks */
  काष्ठा partition_info part[4];
  u32 bsl_st;			/* start of bad sector list */
  u32 bsl_cnt;			/* length of bad sector list */
  u16 checksum;			/* checksum क्रम bootable disks */
पूर्ण __packed;

