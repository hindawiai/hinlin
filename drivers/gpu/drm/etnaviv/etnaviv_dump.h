<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015 Etnaviv Project
 */

#अगर_अघोषित ETNAVIV_DUMP_H
#घोषणा ETNAVIV_DUMP_H

#समावेश <linux/types.h>

क्रमागत अणु
	ETDUMP_MAGIC = 0x414e5445,
	ETDUMP_BUF_REG = 0,
	ETDUMP_BUF_MMU,
	ETDUMP_BUF_RING,
	ETDUMP_BUF_CMD,
	ETDUMP_BUF_BOMAP,
	ETDUMP_BUF_BO,
	ETDUMP_BUF_END,
पूर्ण;

काष्ठा etnaviv_dump_object_header अणु
	__le32 magic;
	__le32 type;
	__le32 file_offset;
	__le32 file_size;
	__le64 iova;
	__le32 data[2];
पूर्ण;

/* Registers object, an array of these */
काष्ठा etnaviv_dump_रेजिस्टरs अणु
	__le32 reg;
	__le32 value;
पूर्ण;

#अगर_घोषित __KERNEL__
काष्ठा etnaviv_gem_submit;
व्योम etnaviv_core_dump(काष्ठा etnaviv_gem_submit *submit);
#पूर्ण_अगर

#पूर्ण_अगर
