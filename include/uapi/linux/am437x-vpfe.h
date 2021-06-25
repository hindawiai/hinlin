<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2013 - 2014 Texas Instruments, Inc.
 *
 * Benoit Parrot <bparrot@ti.com>
 * Lad, Prabhakar <prabhakar.csengg@gmail.com>
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित AM437X_VPFE_USER_H
#घोषणा AM437X_VPFE_USER_H

#समावेश <linux/videodev2.h>

क्रमागत vpfe_ccdc_data_size अणु
	VPFE_CCDC_DATA_16BITS = 0,
	VPFE_CCDC_DATA_15BITS,
	VPFE_CCDC_DATA_14BITS,
	VPFE_CCDC_DATA_13BITS,
	VPFE_CCDC_DATA_12BITS,
	VPFE_CCDC_DATA_11BITS,
	VPFE_CCDC_DATA_10BITS,
	VPFE_CCDC_DATA_8BITS,
पूर्ण;

/* क्रमागत क्रम No of pixel per line to be avg. in Black Clamping*/
क्रमागत vpfe_ccdc_sample_length अणु
	VPFE_CCDC_SAMPLE_1PIXELS = 0,
	VPFE_CCDC_SAMPLE_2PIXELS,
	VPFE_CCDC_SAMPLE_4PIXELS,
	VPFE_CCDC_SAMPLE_8PIXELS,
	VPFE_CCDC_SAMPLE_16PIXELS,
पूर्ण;

/* क्रमागत क्रम No of lines in Black Clamping */
क्रमागत vpfe_ccdc_sample_line अणु
	VPFE_CCDC_SAMPLE_1LINES = 0,
	VPFE_CCDC_SAMPLE_2LINES,
	VPFE_CCDC_SAMPLE_4LINES,
	VPFE_CCDC_SAMPLE_8LINES,
	VPFE_CCDC_SAMPLE_16LINES,
पूर्ण;

/* क्रमागत क्रम Alaw gamma width */
क्रमागत vpfe_ccdc_gamma_width अणु
	VPFE_CCDC_GAMMA_BITS_15_6 = 0,	/* use bits 15-6 क्रम gamma */
	VPFE_CCDC_GAMMA_BITS_14_5,
	VPFE_CCDC_GAMMA_BITS_13_4,
	VPFE_CCDC_GAMMA_BITS_12_3,
	VPFE_CCDC_GAMMA_BITS_11_2,
	VPFE_CCDC_GAMMA_BITS_10_1,
	VPFE_CCDC_GAMMA_BITS_09_0,	/* use bits 9-0 क्रम gamma */
पूर्ण;

/* काष्ठाure क्रम ALaw */
काष्ठा vpfe_ccdc_a_law अणु
	/* Enable/disable A-Law */
	अचिन्हित अक्षर enable;
	/* Gamma Width Input */
	क्रमागत vpfe_ccdc_gamma_width gamma_wd;
पूर्ण;

/* काष्ठाure क्रम Black Clamping */
काष्ठा vpfe_ccdc_black_clamp अणु
	अचिन्हित अक्षर enable;
	/* only अगर bClampEnable is TRUE */
	क्रमागत vpfe_ccdc_sample_length sample_pixel;
	/* only अगर bClampEnable is TRUE */
	क्रमागत vpfe_ccdc_sample_line sample_ln;
	/* only अगर bClampEnable is TRUE */
	अचिन्हित लघु start_pixel;
	/* only अगर bClampEnable is TRUE */
	अचिन्हित लघु sgain;
	/* only अगर bClampEnable is FALSE */
	अचिन्हित लघु dc_sub;
पूर्ण;

/* काष्ठाure क्रम Black Level Compensation */
काष्ठा vpfe_ccdc_black_compensation अणु
	/* Constant value to subtract from Red component */
	अक्षर r;
	/* Constant value to subtract from Gr component */
	अक्षर gr;
	/* Constant value to subtract from Blue component */
	अक्षर b;
	/* Constant value to subtract from Gb component */
	अक्षर gb;
पूर्ण;

/* Structure क्रम CCDC configuration parameters क्रम raw capture mode passed
 * by application
 */
काष्ठा vpfe_ccdc_config_params_raw अणु
	/* data size value from 8 to 16 bits */
	क्रमागत vpfe_ccdc_data_size data_sz;
	/* Structure क्रम Optional A-Law */
	काष्ठा vpfe_ccdc_a_law alaw;
	/* Structure क्रम Optical Black Clamp */
	काष्ठा vpfe_ccdc_black_clamp blk_clamp;
	/* Structure क्रम Black Compensation */
	काष्ठा vpfe_ccdc_black_compensation blk_comp;
पूर्ण;

/*
 *  Private IOCTL
 * VIDIOC_AM437X_CCDC_CFG - Set CCDC configuration क्रम raw capture
 * This is an experimental ioctl that will change in future kernels. So use
 * this ioctl with care !
 **/
#घोषणा VIDIOC_AM437X_CCDC_CFG \
	_IOW('V', BASE_VIDIOC_PRIVATE + 1, व्योम *)

#पूर्ण_अगर		/* AM437X_VPFE_USER_H */
