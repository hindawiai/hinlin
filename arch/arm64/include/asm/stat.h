<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_STAT_H
#घोषणा __ASM_STAT_H

#समावेश <uapi/यंत्र/स्थिति.स>

#अगर_घोषित CONFIG_COMPAT

#समावेश <linux/समय.स>
#समावेश <यंत्र/compat.h>

/*
 * काष्ठा stat64 is needed क्रम compat tasks only. Its definition is dअगरferent
 * from the generic काष्ठा stat64.
 */
काष्ठा stat64 अणु
	compat_u64	st_dev;
	अचिन्हित अक्षर   __pad0[4];

#घोषणा STAT64_HAS_BROKEN_ST_INO	1
	compat_uदीर्घ_t	__st_ino;
	compat_uपूर्णांक_t	st_mode;
	compat_uपूर्णांक_t	st_nlink;

	compat_uदीर्घ_t	st_uid;
	compat_uदीर्घ_t	st_gid;

	compat_u64	st_rdev;
	अचिन्हित अक्षर   __pad3[4];

	compat_s64	st_size;
	compat_uदीर्घ_t	st_blksize;
	compat_u64	st_blocks;	/* Number of 512-byte blocks allocated. */

	compat_uदीर्घ_t	st_aसमय;
	compat_uदीर्घ_t	st_aसमय_nsec;

	compat_uदीर्घ_t	st_mसमय;
	compat_uदीर्घ_t	st_mसमय_nsec;

	compat_uदीर्घ_t	st_स_समय;
	compat_uदीर्घ_t	st_स_समय_nsec;

	compat_u64	st_ino;
पूर्ण;

#पूर्ण_अगर
#पूर्ण_अगर
