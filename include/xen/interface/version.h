<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * version.h
 *
 * Xen version, type, and compile inक्रमmation.
 *
 * Copyright (c) 2005, Nguyen Anh Quynh <aquynh@gmail.com>
 * Copyright (c) 2005, Keir Fraser <keir@xensource.com>
 */

#अगर_अघोषित __XEN_PUBLIC_VERSION_H__
#घोषणा __XEN_PUBLIC_VERSION_H__

/* NB. All ops वापस zero on success, except XENVER_version. */

/* arg == शून्य; वापसs major:minor (16:16). */
#घोषणा XENVER_version      0

/* arg == xen_extraversion_t. */
#घोषणा XENVER_extraversion 1
काष्ठा xen_extraversion अणु
    अक्षर extraversion[16];
पूर्ण;
#घोषणा XEN_EXTRAVERSION_LEN (माप(काष्ठा xen_extraversion))

/* arg == xen_compile_info_t. */
#घोषणा XENVER_compile_info 2
काष्ठा xen_compile_info अणु
    अक्षर compiler[64];
    अक्षर compile_by[16];
    अक्षर compile_करोमुख्य[32];
    अक्षर compile_date[32];
पूर्ण;

#घोषणा XENVER_capabilities 3
काष्ठा xen_capabilities_info अणु
    अक्षर info[1024];
पूर्ण;
#घोषणा XEN_CAPABILITIES_INFO_LEN (माप(काष्ठा xen_capabilities_info))

#घोषणा XENVER_changeset 4
काष्ठा xen_changeset_info अणु
    अक्षर info[64];
पूर्ण;
#घोषणा XEN_CHANGESET_INFO_LEN (माप(काष्ठा xen_changeset_info))

#घोषणा XENVER_platक्रमm_parameters 5
काष्ठा xen_platक्रमm_parameters अणु
    xen_uदीर्घ_t virt_start;
पूर्ण;

#घोषणा XENVER_get_features 6
काष्ठा xen_feature_info अणु
    अचिन्हित पूर्णांक submap_idx;    /* IN: which 32-bit submap to वापस */
    uपूर्णांक32_t     submap;        /* OUT: 32-bit submap */
पूर्ण;

/* Declares the features reported by XENVER_get_features. */
#समावेश <xen/पूर्णांकerface/features.h>

/* arg == शून्य; वापसs host memory page size. */
#घोषणा XENVER_pagesize 7

/* arg == xen_करोमुख्य_handle_t. */
#घोषणा XENVER_guest_handle 8

#घोषणा XENVER_commandline 9
काष्ठा xen_commandline अणु
	अक्षर buf[1024];
पूर्ण;

/*
 * Return value is the number of bytes written, or XEN_Exx on error.
 * Calling with empty parameter वापसs the size of build_id.
 */
#घोषणा XENVER_build_id 10
काष्ठा xen_build_id अणु
	uपूर्णांक32_t	len; /* IN: size of buf[]. */
	अचिन्हित अक्षर	buf[];
पूर्ण;

#पूर्ण_अगर /* __XEN_PUBLIC_VERSION_H__ */
