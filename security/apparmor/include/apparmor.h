<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor basic global
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2017 Canonical Ltd.
 */

#अगर_अघोषित __APPARMOR_H
#घोषणा __APPARMOR_H

#समावेश <linux/types.h>

/*
 * Class of mediation types in the AppArmor policy db
 */
#घोषणा AA_CLASS_ENTRY		0
#घोषणा AA_CLASS_UNKNOWN	1
#घोषणा AA_CLASS_खाता		2
#घोषणा AA_CLASS_CAP		3
#घोषणा AA_CLASS_DEPRECATED	4
#घोषणा AA_CLASS_RLIMITS	5
#घोषणा AA_CLASS_DOMAIN		6
#घोषणा AA_CLASS_MOUNT		7
#घोषणा AA_CLASS_PTRACE		9
#घोषणा AA_CLASS_SIGNAL		10
#घोषणा AA_CLASS_NET		14
#घोषणा AA_CLASS_LABEL		16

#घोषणा AA_CLASS_LAST		AA_CLASS_LABEL

/* Control parameters settable through module/boot flags */
बाह्य क्रमागत audit_mode aa_g_audit;
बाह्य bool aa_g_audit_header;
बाह्य bool aa_g_debug;
बाह्य bool aa_g_hash_policy;
बाह्य पूर्णांक aa_g_rawdata_compression_level;
बाह्य bool aa_g_lock_policy;
बाह्य bool aa_g_logsyscall;
बाह्य bool aa_g_paranoid_load;
बाह्य अचिन्हित पूर्णांक aa_g_path_max;

#पूर्ण_अगर /* __APPARMOR_H */
