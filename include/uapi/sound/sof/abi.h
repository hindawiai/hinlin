<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

/**
 * SOF ABI versioning is based on Semantic Versioning where we have a given
 * MAJOR.MINOR.PATCH version number. See https://semver.org/
 *
 * Rules क्रम incrementing or changing version :-
 *
 * 1) Increment MAJOR version अगर you make incompatible API changes. MINOR and
 *    PATCH should be reset to 0.
 *
 * 2) Increment MINOR version अगर you add backwards compatible features or
 *    changes. PATCH should be reset to 0.
 *
 * 3) Increment PATCH version अगर you add backwards compatible bug fixes.
 */

#अगर_अघोषित __INCLUDE_UAPI_SOUND_SOF_ABI_H__
#घोषणा __INCLUDE_UAPI_SOUND_SOF_ABI_H__

/* SOF ABI version major, minor and patch numbers */
#घोषणा SOF_ABI_MAJOR 3
#घोषणा SOF_ABI_MINOR 18
#घोषणा SOF_ABI_PATCH 0

/* SOF ABI version number. Format within 32bit word is MMmmmppp */
#घोषणा SOF_ABI_MAJOR_SHIFT	24
#घोषणा SOF_ABI_MAJOR_MASK	0xff
#घोषणा SOF_ABI_MINOR_SHIFT	12
#घोषणा SOF_ABI_MINOR_MASK	0xfff
#घोषणा SOF_ABI_PATCH_SHIFT	0
#घोषणा SOF_ABI_PATCH_MASK	0xfff

#घोषणा SOF_ABI_VER(major, minor, patch) \
	(((major) << SOF_ABI_MAJOR_SHIFT) | \
	((minor) << SOF_ABI_MINOR_SHIFT) | \
	((patch) << SOF_ABI_PATCH_SHIFT))

#घोषणा SOF_ABI_VERSION_MAJOR(version) \
	(((version) >> SOF_ABI_MAJOR_SHIFT) & SOF_ABI_MAJOR_MASK)
#घोषणा SOF_ABI_VERSION_MINOR(version)	\
	(((version) >> SOF_ABI_MINOR_SHIFT) & SOF_ABI_MINOR_MASK)
#घोषणा SOF_ABI_VERSION_PATCH(version)	\
	(((version) >> SOF_ABI_PATCH_SHIFT) & SOF_ABI_PATCH_MASK)

#घोषणा SOF_ABI_VERSION_INCOMPATIBLE(sof_ver, client_ver)		\
	(SOF_ABI_VERSION_MAJOR((sof_ver)) !=				\
		SOF_ABI_VERSION_MAJOR((client_ver))			\
	)

#घोषणा SOF_ABI_VERSION SOF_ABI_VER(SOF_ABI_MAJOR, SOF_ABI_MINOR, SOF_ABI_PATCH)

/* SOF ABI magic number "SOF\0". */
#घोषणा SOF_ABI_MAGIC		0x00464F53

#पूर्ण_अगर
