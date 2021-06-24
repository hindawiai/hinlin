<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-vbi-gen.h - vbi generator support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_VBI_GEN_H_
#घोषणा _VIVID_VBI_GEN_H_

काष्ठा vivid_vbi_gen_data अणु
	काष्ठा v4l2_sliced_vbi_data data[25];
	u8 समय_of_day_packet[16];
पूर्ण;

व्योम vivid_vbi_gen_sliced(काष्ठा vivid_vbi_gen_data *vbi,
		bool is_60hz, अचिन्हित seqnr);
व्योम vivid_vbi_gen_raw(स्थिर काष्ठा vivid_vbi_gen_data *vbi,
		स्थिर काष्ठा v4l2_vbi_क्रमmat *vbi_fmt, u8 *buf);

#पूर्ण_अगर
