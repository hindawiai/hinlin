<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  (C) 2003 Dave Jones.
 *
 *  AMD-specअगरic inक्रमmation
 */

जोड़ msr_fidvidctl अणु
	काष्ठा अणु
		अचिन्हित FID:5,			// 4:0
		reserved1:3,	// 7:5
		VID:5,			// 12:8
		reserved2:3,	// 15:13
		FIDC:1,			// 16
		VIDC:1,			// 17
		reserved3:2,	// 19:18
		FIDCHGRATIO:1,	// 20
		reserved4:11,	// 31-21
		SGTC:20,		// 32:51
		reserved5:12;	// 63:52
	पूर्ण bits;
	अचिन्हित दीर्घ दीर्घ val;
पूर्ण;

जोड़ msr_fidvidstatus अणु
	काष्ठा अणु
		अचिन्हित CFID:5,			// 4:0
		reserved1:3,	// 7:5
		SFID:5,			// 12:8
		reserved2:3,	// 15:13
		MFID:5,			// 20:16
		reserved3:11,	// 31:21
		CVID:5,			// 36:32
		reserved4:3,	// 39:37
		SVID:5,			// 44:40
		reserved5:3,	// 47:45
		MVID:5,			// 52:48
		reserved6:11;	// 63:53
	पूर्ण bits;
	अचिन्हित दीर्घ दीर्घ val;
पूर्ण;
