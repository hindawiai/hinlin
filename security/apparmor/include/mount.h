<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor file mediation function definitions.
 *
 * Copyright 2017 Canonical Ltd.
 */

#अगर_अघोषित __AA_MOUNT_H
#घोषणा __AA_MOUNT_H

#समावेश <linux/fs.h>
#समावेश <linux/path.h>

#समावेश "domain.h"
#समावेश "policy.h"

/* mount perms */
#घोषणा AA_MAY_PIVOTROOT	0x01
#घोषणा AA_MAY_MOUNT		0x02
#घोषणा AA_MAY_UMOUNT		0x04
#घोषणा AA_AUDIT_DATA		0x40
#घोषणा AA_MNT_CONT_MATCH	0x40

#घोषणा AA_MS_IGNORE_MASK (MS_KERNMOUNT | MS_NOSEC | MS_ACTIVE | MS_BORN)

पूर्णांक aa_remount(काष्ठा aa_label *label, स्थिर काष्ठा path *path,
	       अचिन्हित दीर्घ flags, व्योम *data);

पूर्णांक aa_bind_mount(काष्ठा aa_label *label, स्थिर काष्ठा path *path,
		  स्थिर अक्षर *old_name, अचिन्हित दीर्घ flags);


पूर्णांक aa_mount_change_type(काष्ठा aa_label *label, स्थिर काष्ठा path *path,
			 अचिन्हित दीर्घ flags);

पूर्णांक aa_move_mount(काष्ठा aa_label *label, स्थिर काष्ठा path *path,
		  स्थिर अक्षर *old_name);

पूर्णांक aa_new_mount(काष्ठा aa_label *label, स्थिर अक्षर *dev_name,
		 स्थिर काष्ठा path *path, स्थिर अक्षर *type, अचिन्हित दीर्घ flags,
		 व्योम *data);

पूर्णांक aa_umount(काष्ठा aa_label *label, काष्ठा vfsmount *mnt, पूर्णांक flags);

पूर्णांक aa_pivotroot(काष्ठा aa_label *label, स्थिर काष्ठा path *old_path,
		 स्थिर काष्ठा path *new_path);

#पूर्ण_अगर /* __AA_MOUNT_H */
