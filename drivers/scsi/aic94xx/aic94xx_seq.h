<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Aic94xx SAS/SATA driver sequencer पूर्णांकerface header file.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#अगर_अघोषित _AIC94XX_SEQ_H_
#घोषणा _AIC94XX_SEQ_H_

#घोषणा CSEQ_NUM_VECS	3
#घोषणा LSEQ_NUM_VECS	11

#घोषणा SAS_RAZOR_SEQUENCER_FW_खाता "aic94xx-seq.fw"
#घोषणा SAS_RAZOR_SEQUENCER_FW_MAJOR	1

/* Note:  All quantites in the sequencer file are little endian */
काष्ठा sequencer_file_header अणु
	/* Checksum of the entire contents of the sequencer excluding
	 * these four bytes */
	u32	csum;
	/* numeric major version */
	u32	major;
	/* numeric minor version */
	u32	minor;
	/* version string prपूर्णांकed by driver */
	अक्षर	version[16];
	u32	cseq_table_offset;
	u32	cseq_table_size;
	u32	lseq_table_offset;
	u32	lseq_table_size;
	u32	cseq_code_offset;
	u32	cseq_code_size;
	u32	lseq_code_offset;
	u32	lseq_code_size;
	u16	mode2_task;
	u16	cseq_idle_loop;
	u16	lseq_idle_loop;
पूर्ण __attribute__((packed));

#अगर_घोषित __KERNEL__
पूर्णांक asd_init_seqs(काष्ठा asd_ha_काष्ठा *asd_ha);
पूर्णांक asd_start_seqs(काष्ठा asd_ha_काष्ठा *asd_ha);
पूर्णांक asd_release_firmware(व्योम);

व्योम asd_update_port_links(काष्ठा asd_ha_काष्ठा *asd_ha, काष्ठा asd_phy *phy);
#पूर्ण_अगर

#पूर्ण_अगर
