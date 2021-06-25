<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright Novell Inc. 2010
 *
 * Authors: Alexander Graf <agraf@suse.de>
 */

#अगर_अघोषित __ASM_KVM_FPU_H__
#घोषणा __ASM_KVM_FPU_H__

#समावेश <linux/types.h>

बाह्य व्योम fps_fres(u64 *fpscr, u32 *dst, u32 *src1);
बाह्य व्योम fps_frवर्ग_मूलe(u64 *fpscr, u32 *dst, u32 *src1);
बाह्य व्योम fps_fवर्ग_मूलs(u64 *fpscr, u32 *dst, u32 *src1);

बाह्य व्योम fps_fadds(u64 *fpscr, u32 *dst, u32 *src1, u32 *src2);
बाह्य व्योम fps_fभागs(u64 *fpscr, u32 *dst, u32 *src1, u32 *src2);
बाह्य व्योम fps_fmuls(u64 *fpscr, u32 *dst, u32 *src1, u32 *src2);
बाह्य व्योम fps_fsubs(u64 *fpscr, u32 *dst, u32 *src1, u32 *src2);

बाह्य व्योम fps_fmadds(u64 *fpscr, u32 *dst, u32 *src1, u32 *src2,
		       u32 *src3);
बाह्य व्योम fps_fmsubs(u64 *fpscr, u32 *dst, u32 *src1, u32 *src2,
		       u32 *src3);
बाह्य व्योम fps_fnmadds(u64 *fpscr, u32 *dst, u32 *src1, u32 *src2,
		        u32 *src3);
बाह्य व्योम fps_fnmsubs(u64 *fpscr, u32 *dst, u32 *src1, u32 *src2,
		        u32 *src3);
बाह्य व्योम fps_fsel(u64 *fpscr, u32 *dst, u32 *src1, u32 *src2,
		     u32 *src3);

#घोषणा FPD_ONE_IN(name) बाह्य व्योम fpd_ ## name(u64 *fpscr, u32 *cr, \
				u64 *dst, u64 *src1);
#घोषणा FPD_TWO_IN(name) बाह्य व्योम fpd_ ## name(u64 *fpscr, u32 *cr, \
				u64 *dst, u64 *src1, u64 *src2);
#घोषणा FPD_THREE_IN(name) बाह्य व्योम fpd_ ## name(u64 *fpscr, u32 *cr, \
				u64 *dst, u64 *src1, u64 *src2, u64 *src3);

बाह्य व्योम fpd_fcmpu(u64 *fpscr, u32 *cr, u64 *src1, u64 *src2);
बाह्य व्योम fpd_fcmpo(u64 *fpscr, u32 *cr, u64 *src1, u64 *src2);

FPD_ONE_IN(fवर्ग_मूलs)
FPD_ONE_IN(frवर्ग_मूलes)
FPD_ONE_IN(fres)
FPD_ONE_IN(frsp)
FPD_ONE_IN(fctiw)
FPD_ONE_IN(fctiwz)
FPD_ONE_IN(fवर्ग_मूल)
FPD_ONE_IN(fre)
FPD_ONE_IN(frवर्ग_मूलe)
FPD_ONE_IN(fneg)
FPD_ONE_IN(भ_असल)
FPD_TWO_IN(fadds)
FPD_TWO_IN(fsubs)
FPD_TWO_IN(fभागs)
FPD_TWO_IN(fmuls)
FPD_TWO_IN(fcpsgn)
FPD_TWO_IN(fभाग)
FPD_TWO_IN(fadd)
FPD_TWO_IN(fmul)
FPD_TWO_IN(fsub)
FPD_THREE_IN(fmsubs)
FPD_THREE_IN(fmadds)
FPD_THREE_IN(fnmsubs)
FPD_THREE_IN(fnmadds)
FPD_THREE_IN(fsel)
FPD_THREE_IN(fmsub)
FPD_THREE_IN(fmadd)
FPD_THREE_IN(fnmsub)
FPD_THREE_IN(fnmadd)

बाह्य व्योम kvm_cvt_fd(u32 *from, u64 *to);
बाह्य व्योम kvm_cvt_df(u64 *from, u32 *to);

#पूर्ण_अगर
