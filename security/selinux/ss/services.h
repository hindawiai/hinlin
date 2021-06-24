<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Implementation of the security services.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
#अगर_अघोषित _SS_SERVICES_H_
#घोषणा _SS_SERVICES_H_

#समावेश "policydb.h"

/* Mapping क्रम a single class */
काष्ठा selinux_mapping अणु
	u16 value; /* policy value क्रम class */
	अचिन्हित पूर्णांक num_perms; /* number of permissions in class */
	u32 perms[माप(u32) * 8]; /* policy values क्रम permissions */
पूर्ण;

/* Map क्रम all of the classes, with array size */
काष्ठा selinux_map अणु
	काष्ठा selinux_mapping *mapping; /* indexed by class */
	u16 size; /* array size of mapping */
पूर्ण;

काष्ठा selinux_policy अणु
	काष्ठा sidtab *sidtab;
	काष्ठा policydb policydb;
	काष्ठा selinux_map map;
	u32 latest_granting;
पूर्ण __अक्रमomize_layout;

व्योम services_compute_xperms_drivers(काष्ठा extended_perms *xperms,
				काष्ठा avtab_node *node);

व्योम services_compute_xperms_decision(काष्ठा extended_perms_decision *xpermd,
					काष्ठा avtab_node *node);

#पूर्ण_अगर	/* _SS_SERVICES_H_ */
