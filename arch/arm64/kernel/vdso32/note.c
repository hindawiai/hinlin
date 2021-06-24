<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012-2018 ARM Limited
 *
 * This supplies .note.* sections to go पूर्णांकo the PT_NOTE inside the vDSO text.
 * Here we can supply some inक्रमmation useful to userland.
 */

#समावेश <linux/uts.h>
#समावेश <linux/version.h>
#समावेश <linux/elfnote.h>
#समावेश <linux/build-salt.h>

ELFNOTE32("Linux", 0, LINUX_VERSION_CODE);
BUILD_SALT;
