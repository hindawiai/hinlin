<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * memconsole.h
 *
 * Internal headers of the memory based BIOS console.
 *
 * Copyright 2017 Google Inc.
 */

#अगर_अघोषित __FIRMWARE_GOOGLE_MEMCONSOLE_H
#घोषणा __FIRMWARE_GOOGLE_MEMCONSOLE_H

#समावेश <linux/types.h>

/*
 * memconsole_setup
 *
 * Initialize the memory console, passing the function to handle पढ़ो accesses.
 */
व्योम memconsole_setup(sमाप_प्रकार (*पढ़ो_func)(अक्षर *, loff_t, माप_प्रकार));

/*
 * memconsole_sysfs_init
 *
 * Update memory console length and create binary file
 * क्रम firmware object.
 */
पूर्णांक memconsole_sysfs_init(व्योम);

/* memconsole_निकास
 *
 * Unmap the console buffer.
 */
व्योम memconsole_निकास(व्योम);

#पूर्ण_अगर /* __FIRMWARE_GOOGLE_MEMCONSOLE_H */
