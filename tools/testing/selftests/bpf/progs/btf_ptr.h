<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2020, Oracle and/or its affiliates. */
/* "undefine" काष्ठाs in vmlinux.h, because we "override" them below */
#घोषणा btf_ptr btf_ptr___not_used
#घोषणा BTF_F_COMPACT BTF_F_COMPACT___not_used
#घोषणा BTF_F_NONAME BTF_F_NONAME___not_used
#घोषणा BTF_F_PTR_RAW BTF_F_PTR_RAW___not_used
#घोषणा BTF_F_ZERO BTF_F_ZERO___not_used
#समावेश "vmlinux.h"
#अघोषित btf_ptr
#अघोषित BTF_F_COMPACT
#अघोषित BTF_F_NONAME
#अघोषित BTF_F_PTR_RAW
#अघोषित BTF_F_ZERO

काष्ठा btf_ptr अणु
	व्योम *ptr;
	__u32 type_id;
	__u32 flags;
पूर्ण;

क्रमागत अणु
	BTF_F_COMPACT	=	(1ULL << 0),
	BTF_F_NONAME	=	(1ULL << 1),
	BTF_F_PTR_RAW	=	(1ULL << 2),
	BTF_F_ZERO	=	(1ULL << 3),
पूर्ण;
