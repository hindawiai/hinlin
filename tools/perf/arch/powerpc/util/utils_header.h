<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_UTIL_HEADER_H
#घोषणा __PERF_UTIL_HEADER_H

#समावेश <linux/stringअगरy.h>

#घोषणा mfspr(rn)       (अणुअचिन्हित दीर्घ rval; \
			यंत्र अस्थिर("mfspr %0," __stringअगरy(rn) \
				: "=r" (rval)); rval; पूर्ण)

#घोषणा SPRN_PVR        0x11F   /* Processor Version Register */
#घोषणा PVR_VER(pvr)    (((pvr) >>  16) & 0xFFFF) /* Version field */
#घोषणा PVR_REV(pvr)    (((pvr) >>   0) & 0xFFFF) /* Revision field */

#पूर्ण_अगर /* __PERF_UTIL_HEADER_H */
