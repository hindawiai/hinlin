<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * sysctl.h - Defines क्रम sysctl handling in NTFS Linux kernel driver. Part of
 *	      the Linux-NTFS project. Adapted from the old NTFS driver,
 *	      Copyright (C) 1997 Martin von Lथघwis, Rथऊgis Duchesne
 *
 * Copyright (c) 2002-2004 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_SYSCTL_H
#घोषणा _LINUX_NTFS_SYSCTL_H


#अगर defined(DEBUG) && defined(CONFIG_SYSCTL)

बाह्य पूर्णांक ntfs_sysctl(पूर्णांक add);

#अन्यथा

/* Just वापस success. */
अटल अंतरभूत पूर्णांक ntfs_sysctl(पूर्णांक add)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* DEBUG && CONFIG_SYSCTL */
#पूर्ण_अगर /* _LINUX_NTFS_SYSCTL_H */
