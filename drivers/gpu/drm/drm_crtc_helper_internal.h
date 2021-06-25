<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * This header file contains mode setting related functions and definitions
 * which are only used within the drm kms helper module as पूर्णांकernal
 * implementation details and are not exported to drivers.
 */

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_modes.h>

/* drm_dp_aux_dev.c */
#अगर_घोषित CONFIG_DRM_DP_AUX_CHARDEV
पूर्णांक drm_dp_aux_dev_init(व्योम);
व्योम drm_dp_aux_dev_निकास(व्योम);
पूर्णांक drm_dp_aux_रेजिस्टर_devnode(काष्ठा drm_dp_aux *aux);
व्योम drm_dp_aux_unरेजिस्टर_devnode(काष्ठा drm_dp_aux *aux);
#अन्यथा
अटल अंतरभूत पूर्णांक drm_dp_aux_dev_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम drm_dp_aux_dev_निकास(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक drm_dp_aux_रेजिस्टर_devnode(काष्ठा drm_dp_aux *aux)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम drm_dp_aux_unरेजिस्टर_devnode(काष्ठा drm_dp_aux *aux)
अणु
पूर्ण
#पूर्ण_अगर

/* drm_probe_helper.c */
क्रमागत drm_mode_status drm_crtc_mode_valid(काष्ठा drm_crtc *crtc,
					 स्थिर काष्ठा drm_display_mode *mode);
क्रमागत drm_mode_status drm_encoder_mode_valid(काष्ठा drm_encoder *encoder,
					    स्थिर काष्ठा drm_display_mode *mode);
पूर्णांक
drm_connector_mode_valid(काष्ठा drm_connector *connector,
			 काष्ठा drm_display_mode *mode,
			 काष्ठा drm_modeset_acquire_ctx *ctx,
			 क्रमागत drm_mode_status *status);

काष्ठा drm_encoder *
drm_connector_get_single_encoder(काष्ठा drm_connector *connector);
