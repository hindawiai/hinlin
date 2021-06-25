<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2005-2018 Andes Technology Corporation */

#अगर_अघोषित __ARCH_NDS32_FPUEMU_H
#घोषणा __ARCH_NDS32_FPUEMU_H

/*
 * single precision
 */

व्योम fadds(व्योम *ft, व्योम *fa, व्योम *fb);
व्योम fsubs(व्योम *ft, व्योम *fa, व्योम *fb);
व्योम fmuls(व्योम *ft, व्योम *fa, व्योम *fb);
व्योम fभागs(व्योम *ft, व्योम *fa, व्योम *fb);
व्योम fs2d(व्योम *ft, व्योम *fa);
व्योम fs2si(व्योम *ft, व्योम *fa);
व्योम fs2si_z(व्योम *ft, व्योम *fa);
व्योम fs2ui(व्योम *ft, व्योम *fa);
व्योम fs2ui_z(व्योम *ft, व्योम *fa);
व्योम fsi2s(व्योम *ft, व्योम *fa);
व्योम fui2s(व्योम *ft, व्योम *fa);
व्योम fवर्ग_मूलs(व्योम *ft, व्योम *fa);
व्योम fnegs(व्योम *ft, व्योम *fa);
पूर्णांक fcmps(व्योम *ft, व्योम *fa, व्योम *fb, पूर्णांक cop);

/*
 * द्विगुन precision
 */
व्योम faddd(व्योम *ft, व्योम *fa, व्योम *fb);
व्योम fsubd(व्योम *ft, व्योम *fa, व्योम *fb);
व्योम fmuld(व्योम *ft, व्योम *fa, व्योम *fb);
व्योम fभागd(व्योम *ft, व्योम *fa, व्योम *fb);
व्योम fवर्ग_मूलd(व्योम *ft, व्योम *fa);
व्योम fd2s(व्योम *ft, व्योम *fa);
व्योम fd2si(व्योम *ft, व्योम *fa);
व्योम fd2si_z(व्योम *ft, व्योम *fa);
व्योम fd2ui(व्योम *ft, व्योम *fa);
व्योम fd2ui_z(व्योम *ft, व्योम *fa);
व्योम fsi2d(व्योम *ft, व्योम *fa);
व्योम fui2d(व्योम *ft, व्योम *fa);
व्योम fnegd(व्योम *ft, व्योम *fa);
पूर्णांक fcmpd(व्योम *ft, व्योम *fa, व्योम *fb, पूर्णांक cop);

#पूर्ण_अगर /* __ARCH_NDS32_FPUEMU_H */
