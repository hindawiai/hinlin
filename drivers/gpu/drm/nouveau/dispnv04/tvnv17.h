<शैली गुरु>
/*
 * Copyright (C) 2009 Francisco Jerez.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __NV17_TV_H__
#घोषणा __NV17_TV_H__

काष्ठा nv17_tv_state अणु
	uपूर्णांक8_t tv_enc[0x40];

	uपूर्णांक32_t hfilter[4][7];
	uपूर्णांक32_t hfilter2[4][7];
	uपूर्णांक32_t vfilter[4][7];

	uपूर्णांक32_t ptv_200;
	uपूर्णांक32_t ptv_204;
	uपूर्णांक32_t ptv_208;
	uपूर्णांक32_t ptv_20c;
	uपूर्णांक32_t ptv_304;
	uपूर्णांक32_t ptv_500;
	uपूर्णांक32_t ptv_504;
	uपूर्णांक32_t ptv_508;
	uपूर्णांक32_t ptv_600;
	uपूर्णांक32_t ptv_604;
	uपूर्णांक32_t ptv_608;
	uपूर्णांक32_t ptv_60c;
	uपूर्णांक32_t ptv_610;
	uपूर्णांक32_t ptv_614;
पूर्ण;

क्रमागत nv17_tv_normअणु
	TV_NORM_PAL,
	TV_NORM_PAL_M,
	TV_NORM_PAL_N,
	TV_NORM_PAL_NC,
	TV_NORM_NTSC_M,
	TV_NORM_NTSC_J,
	NUM_LD_TV_NORMS,
	TV_NORM_HD480I = NUM_LD_TV_NORMS,
	TV_NORM_HD480P,
	TV_NORM_HD576I,
	TV_NORM_HD576P,
	TV_NORM_HD720P,
	TV_NORM_HD1080I,
	NUM_TV_NORMS
पूर्ण;

काष्ठा nv17_tv_encoder अणु
	काष्ठा nouveau_encoder base;

	काष्ठा nv17_tv_state state;
	काष्ठा nv17_tv_state saved_state;

	पूर्णांक overscan;
	पूर्णांक flicker;
	पूर्णांक saturation;
	पूर्णांक hue;
	क्रमागत nv17_tv_norm tv_norm;
	पूर्णांक subconnector;
	पूर्णांक select_subconnector;
	uपूर्णांक32_t pin_mask;
पूर्ण;
#घोषणा to_tv_enc(x) container_of(nouveau_encoder(x),		\
				  काष्ठा nv17_tv_encoder, base)

बाह्य स्थिर अक्षर * स्थिर nv17_tv_norm_names[NUM_TV_NORMS];

बाह्य काष्ठा nv17_tv_norm_params अणु
	क्रमागत अणु
		TV_ENC_MODE,
		CTV_ENC_MODE,
	पूर्ण kind;

	जोड़ अणु
		काष्ठा अणु
			पूर्णांक hdisplay;
			पूर्णांक vdisplay;
			पूर्णांक vrefresh; /* mHz */

			uपूर्णांक8_t tv_enc[0x40];
		पूर्ण tv_enc_mode;

		काष्ठा अणु
			काष्ठा drm_display_mode mode;

			uपूर्णांक32_t ctv_regs[38];
		पूर्ण ctv_enc_mode;
	पूर्ण;

पूर्ण nv17_tv_norms[NUM_TV_NORMS];
#घोषणा get_tv_norm(enc) (&nv17_tv_norms[to_tv_enc(enc)->tv_norm])

बाह्य स्थिर काष्ठा drm_display_mode nv17_tv_modes[];

अटल अंतरभूत पूर्णांक पूर्णांकerpolate(पूर्णांक y0, पूर्णांक y1, पूर्णांक y2, पूर्णांक x)
अणु
	वापस y1 + (x < 50 ? y1 - y0 : y2 - y1) * (x - 50) / 50;
पूर्ण

व्योम nv17_tv_state_save(काष्ठा drm_device *dev, काष्ठा nv17_tv_state *state);
व्योम nv17_tv_state_load(काष्ठा drm_device *dev, काष्ठा nv17_tv_state *state);
व्योम nv17_tv_update_properties(काष्ठा drm_encoder *encoder);
व्योम nv17_tv_update_rescaler(काष्ठा drm_encoder *encoder);
व्योम nv17_ctv_update_rescaler(काष्ठा drm_encoder *encoder);

/* TV hardware access functions */

अटल अंतरभूत व्योम nv_ग_लिखो_ptv(काष्ठा drm_device *dev, uपूर्णांक32_t reg,
				uपूर्णांक32_t val)
अणु
	काष्ठा nvअगर_device *device = &nouveau_drm(dev)->client.device;
	nvअगर_wr32(&device->object, reg, val);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t nv_पढ़ो_ptv(काष्ठा drm_device *dev, uपूर्णांक32_t reg)
अणु
	काष्ठा nvअगर_device *device = &nouveau_drm(dev)->client.device;
	वापस nvअगर_rd32(&device->object, reg);
पूर्ण

अटल अंतरभूत व्योम nv_ग_लिखो_tv_enc(काष्ठा drm_device *dev, uपूर्णांक8_t reg,
				   uपूर्णांक8_t val)
अणु
	nv_ग_लिखो_ptv(dev, NV_PTV_TV_INDEX, reg);
	nv_ग_लिखो_ptv(dev, NV_PTV_TV_DATA, val);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t nv_पढ़ो_tv_enc(काष्ठा drm_device *dev, uपूर्णांक8_t reg)
अणु
	nv_ग_लिखो_ptv(dev, NV_PTV_TV_INDEX, reg);
	वापस nv_पढ़ो_ptv(dev, NV_PTV_TV_DATA);
पूर्ण

#घोषणा nv_load_ptv(dev, state, reg) \
	nv_ग_लिखो_ptv(dev, NV_PTV_OFFSET + 0x##reg, state->ptv_##reg)
#घोषणा nv_save_ptv(dev, state, reg) \
	state->ptv_##reg = nv_पढ़ो_ptv(dev, NV_PTV_OFFSET + 0x##reg)
#घोषणा nv_load_tv_enc(dev, state, reg) \
	nv_ग_लिखो_tv_enc(dev, 0x##reg, state->tv_enc[0x##reg])

#पूर्ण_अगर
