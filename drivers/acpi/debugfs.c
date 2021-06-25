<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * debugfs.c - ACPI debugfs पूर्णांकerface to userspace.
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/acpi.h>

#समावेश "internal.h"

काष्ठा dentry *acpi_debugfs_dir;
EXPORT_SYMBOL_GPL(acpi_debugfs_dir);

व्योम __init acpi_debugfs_init(व्योम)
अणु
	acpi_debugfs_dir = debugfs_create_dir("acpi", शून्य);
पूर्ण
