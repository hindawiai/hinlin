<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel(R) Trace Hub Software Trace Hub (STH) data काष्ठाures
 *
 * Copyright (C) 2014-2015 Intel Corporation.
 */

#अगर_अघोषित __INTEL_TH_STH_H__
#घोषणा __INTEL_TH_STH_H__

क्रमागत अणु
	REG_STH_STHCAP0		= 0x0000, /* capabilities pt1 */
	REG_STH_STHCAP1		= 0x0004, /* capabilities pt2 */
	REG_STH_TRIG		= 0x0008, /* TRIG packet payload */
	REG_STH_TRIG_TS		= 0x000c, /* TRIG_TS packet payload */
	REG_STH_XSYNC		= 0x0010, /* XSYNC packet payload */
	REG_STH_XSYNC_TS	= 0x0014, /* XSYNC_TS packet payload */
	REG_STH_GERR		= 0x0018, /* GERR packet payload */
पूर्ण;

काष्ठा पूर्णांकel_th_channel अणु
	u64	Dn;
	u64	DnM;
	u64	DnTS;
	u64	DnMTS;
	u64	USER;
	u64	USER_TS;
	u32	FLAG;
	u32	FLAG_TS;
	u32	MERR;
	u32	__unused;
पूर्ण __packed;

#पूर्ण_अगर /* __INTEL_TH_STH_H__ */
