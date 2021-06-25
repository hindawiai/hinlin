<शैली गुरु>
// SPDX-License-Identअगरier: MIT
#समावेश <drm/drm_mode.h>
#समावेश "nouveau_drv.h"
#समावेश "nouveau_reg.h"
#समावेश "nouveau_crtc.h"
#समावेश "hw.h"

अटल व्योम
nv04_cursor_show(काष्ठा nouveau_crtc *nv_crtc, bool update)
अणु
	nv_show_cursor(nv_crtc->base.dev, nv_crtc->index, true);
पूर्ण

अटल व्योम
nv04_cursor_hide(काष्ठा nouveau_crtc *nv_crtc, bool update)
अणु
	nv_show_cursor(nv_crtc->base.dev, nv_crtc->index, false);
पूर्ण

अटल व्योम
nv04_cursor_set_pos(काष्ठा nouveau_crtc *nv_crtc, पूर्णांक x, पूर्णांक y)
अणु
	nv_crtc->cursor_saved_x = x; nv_crtc->cursor_saved_y = y;
	NVWriteRAMDAC(nv_crtc->base.dev, nv_crtc->index,
		      NV_PRAMDAC_CU_START_POS,
		      XLATE(y, 0, NV_PRAMDAC_CU_START_POS_Y) |
		      XLATE(x, 0, NV_PRAMDAC_CU_START_POS_X));
पूर्ण

अटल व्योम
crtc_wr_cio_state(काष्ठा drm_crtc *crtc, काष्ठा nv04_crtc_reg *crtcstate, पूर्णांक index)
अणु
	NVWriteVgaCrtc(crtc->dev, nouveau_crtc(crtc)->index, index,
		       crtcstate->CRTC[index]);
पूर्ण

अटल व्योम
nv04_cursor_set_offset(काष्ठा nouveau_crtc *nv_crtc, uपूर्णांक32_t offset)
अणु
	काष्ठा drm_device *dev = nv_crtc->base.dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nv04_crtc_reg *regp = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index];
	काष्ठा drm_crtc *crtc = &nv_crtc->base;

	regp->CRTC[NV_CIO_CRE_HCUR_ADDR0_INDEX] =
		MASK(NV_CIO_CRE_HCUR_ASI) |
		XLATE(offset, 17, NV_CIO_CRE_HCUR_ADDR0_ADR);
	regp->CRTC[NV_CIO_CRE_HCUR_ADDR1_INDEX] =
		XLATE(offset, 11, NV_CIO_CRE_HCUR_ADDR1_ADR);
	अगर (crtc->mode.flags & DRM_MODE_FLAG_DBLSCAN)
		regp->CRTC[NV_CIO_CRE_HCUR_ADDR1_INDEX] |=
			MASK(NV_CIO_CRE_HCUR_ADDR1_CUR_DBL);
	regp->CRTC[NV_CIO_CRE_HCUR_ADDR2_INDEX] = offset >> 24;

	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_HCUR_ADDR0_INDEX);
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_HCUR_ADDR1_INDEX);
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_HCUR_ADDR2_INDEX);
	अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
		nv_fix_nv40_hw_cursor(dev, nv_crtc->index);
पूर्ण

पूर्णांक
nv04_cursor_init(काष्ठा nouveau_crtc *crtc)
अणु
	crtc->cursor.set_offset = nv04_cursor_set_offset;
	crtc->cursor.set_pos = nv04_cursor_set_pos;
	crtc->cursor.hide = nv04_cursor_hide;
	crtc->cursor.show = nv04_cursor_show;
	वापस 0;
पूर्ण
