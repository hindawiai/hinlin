<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-rds-gen.h - rds (radio data प्रणाली) generator support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_RDS_GEN_H_
#घोषणा _VIVID_RDS_GEN_H_

/*
 * It takes almost exactly 5 seconds to transmit 57 RDS groups.
 * Each group has 4 blocks and each block has a payload of 16 bits + a
 * block identअगरication. The driver will generate the contents of these
 * 57 groups only when necessary and it will just be played continuously.
 */
#घोषणा VIVID_RDS_GEN_GROUPS 57
#घोषणा VIVID_RDS_GEN_BLKS_PER_GRP 4
#घोषणा VIVID_RDS_GEN_BLOCKS (VIVID_RDS_GEN_BLKS_PER_GRP * VIVID_RDS_GEN_GROUPS)
#घोषणा VIVID_RDS_NSEC_PER_BLK (u32)(5ull * NSEC_PER_SEC / VIVID_RDS_GEN_BLOCKS)

काष्ठा vivid_rds_gen अणु
	काष्ठा v4l2_rds_data	data[VIVID_RDS_GEN_BLOCKS];
	bool			use_rbds;
	u16			picode;
	u8			pty;
	bool			mono_stereo;
	bool			art_head;
	bool			compressed;
	bool			dyn_pty;
	bool			ta;
	bool			tp;
	bool			ms;
	अक्षर			psname[8 + 1];
	अक्षर			radiotext[64 + 1];
पूर्ण;

व्योम vivid_rds_gen_fill(काष्ठा vivid_rds_gen *rds, अचिन्हित freq,
		    bool use_alternate);
व्योम vivid_rds_generate(काष्ठा vivid_rds_gen *rds);

#पूर्ण_अगर
