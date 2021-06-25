<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved. */

#घोषणा	XDPING_MAX_COUNT	10
#घोषणा	XDPING_DEFAULT_COUNT	4

काष्ठा pinginfo अणु
	__u64	start;
	__be16	seq;
	__u16	count;
	__u32	pad;
	__u64	बार[XDPING_MAX_COUNT];
पूर्ण;
