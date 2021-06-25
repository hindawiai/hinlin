<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित _ISP_TYPES_H_
#घोषणा _ISP_TYPES_H_

/*
 * Workaround: hivecc complains about "tag "sh_css_3a_output" already declared"
 * without this extra decl.
 */
काष्ठा ia_css_3a_output;

/*
 * Input stream क्रमmats, these correspond to the MIPI क्रमmats and the way
 * the CSS receiver sends these to the input क्रमmatter.
 * The bit depth of each pixel element is stored in the global variable
 * isp_bits_per_pixel.
 * NOTE: क्रम rgb565, we set isp_bits_per_pixel to 565, क्रम all other rgb
 * क्रमmats it's the actual depth (4, क्रम 444, 8 क्रम 888 etc).
 */
क्रमागत sh_stream_क्रमmat अणु
	sh_stream_क्रमmat_yuv420_legacy,
	sh_stream_क्रमmat_yuv420,
	sh_stream_क्रमmat_yuv422,
	sh_stream_क्रमmat_rgb,
	sh_stream_क्रमmat_raw,
	sh_stream_क्रमmat_binary,	/* bytestream such as jpeg */
पूर्ण;

काष्ठा s_isp_frames अणु
	/*
	 * Global variables that are written to by either the SP or the host,
	 * every ISP binary needs these.
	 */
	/* output frame */
	अक्षर *xmem_base_addr_y;
	अक्षर *xmem_base_addr_uv;
	अक्षर *xmem_base_addr_u;
	अक्षर *xmem_base_addr_v;
	/* 2nd output frame */
	अक्षर *xmem_base_addr_second_out_y;
	अक्षर *xmem_base_addr_second_out_u;
	अक्षर *xmem_base_addr_second_out_v;
	/* input yuv frame */
	अक्षर *xmem_base_addr_y_in;
	अक्षर *xmem_base_addr_u_in;
	अक्षर *xmem_base_addr_v_in;
	/* input raw frame */
	अक्षर *xmem_base_addr_raw;
	/* output raw frame */
	अक्षर *xmem_base_addr_raw_out;
	/* viewfinder output (vf_veceven) */
	अक्षर *xmem_base_addr_vfout_y;
	अक्षर *xmem_base_addr_vfout_u;
	अक्षर *xmem_base_addr_vfout_v;
	/* overlay frame (क्रम vf_pp) */
	अक्षर *xmem_base_addr_overlay_y;
	अक्षर *xmem_base_addr_overlay_u;
	अक्षर *xmem_base_addr_overlay_v;
	/* pre-gdc output frame (gdc input) */
	अक्षर *xmem_base_addr_qplane_r;
	अक्षर *xmem_base_addr_qplane_ratb;
	अक्षर *xmem_base_addr_qplane_gr;
	अक्षर *xmem_base_addr_qplane_gb;
	अक्षर *xmem_base_addr_qplane_b;
	अक्षर *xmem_base_addr_qplane_batr;
	/* YUV as input, used by postisp binary */
	अक्षर *xmem_base_addr_yuv_16_y;
	अक्षर *xmem_base_addr_yuv_16_u;
	अक्षर *xmem_base_addr_yuv_16_v;
पूर्ण;

#पूर्ण_अगर /* _ISP_TYPES_H_ */
