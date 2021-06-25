<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor security identअगरier (secid) definitions
 *
 * Copyright 2009-2018 Canonical Ltd.
 */

#अगर_अघोषित __AA_SECID_H
#घोषणा __AA_SECID_H

#समावेश <linux/slab.h>
#समावेश <linux/types.h>

काष्ठा aa_label;

/* secid value that will not be allocated */
#घोषणा AA_SECID_INVALID 0

/* secid value that matches any other secid */
#घोषणा AA_SECID_WILDCARD 1

काष्ठा aa_label *aa_secid_to_label(u32 secid);
पूर्णांक apparmor_secid_to_secctx(u32 secid, अक्षर **secdata, u32 *seclen);
पूर्णांक apparmor_secctx_to_secid(स्थिर अक्षर *secdata, u32 seclen, u32 *secid);
व्योम apparmor_release_secctx(अक्षर *secdata, u32 seclen);


पूर्णांक aa_alloc_secid(काष्ठा aa_label *label, gfp_t gfp);
व्योम aa_मुक्त_secid(u32 secid);
व्योम aa_secid_update(u32 secid, काष्ठा aa_label *label);

व्योम aa_secids_init(व्योम);

#पूर्ण_अगर /* __AA_SECID_H */
