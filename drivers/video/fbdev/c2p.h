<शैली गुरु>
/*
 *  Fast C2P (Chunky-to-Planar) Conversion
 *
 *  Copyright (C) 2003-2008 Geert Uytterhoeven
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#समावेश <linux/types.h>

बाह्य व्योम c2p_planar(व्योम *dst, स्थिर व्योम *src, u32 dx, u32 dy, u32 width,
		       u32 height, u32 dst_nextline, u32 dst_nextplane,
		       u32 src_nextline, u32 bpp);

बाह्य व्योम c2p_iplan2(व्योम *dst, स्थिर व्योम *src, u32 dx, u32 dy, u32 width,
		       u32 height, u32 dst_nextline, u32 src_nextline,
		       u32 bpp);
