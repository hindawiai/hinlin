<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_XT_CGROUP_H
#घोषणा _UAPI_XT_CGROUP_H

#समावेश <linux/types.h>
#समावेश <linux/सीमा.स>

काष्ठा xt_cgroup_info_v0 अणु
	__u32 id;
	__u32 invert;
पूर्ण;

काष्ठा xt_cgroup_info_v1 अणु
	__u8		has_path;
	__u8		has_classid;
	__u8		invert_path;
	__u8		invert_classid;
	अक्षर		path[PATH_MAX];
	__u32		classid;

	/* kernel पूर्णांकernal data */
	व्योम		*priv __attribute__((aligned(8)));
पूर्ण;

#घोषणा XT_CGROUP_PATH_MAX	512

काष्ठा xt_cgroup_info_v2 अणु
	__u8		has_path;
	__u8		has_classid;
	__u8		invert_path;
	__u8		invert_classid;
	जोड़ अणु
		अक्षर	path[XT_CGROUP_PATH_MAX];
		__u32	classid;
	पूर्ण;

	/* kernel पूर्णांकernal data */
	व्योम		*priv __attribute__((aligned(8)));
पूर्ण;

#पूर्ण_अगर /* _UAPI_XT_CGROUP_H */
