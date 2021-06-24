<शैली गुरु>
/*
 * Copyright 2009 Red Hat Inc.
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
 *
 * Authors: Ben Skeggs
 */

#समावेश <drm/drm_dp_helper.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_connector.h"
#समावेश "nouveau_encoder.h"
#समावेश "nouveau_crtc.h"

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl5070.h>

MODULE_PARM_DESC(mst, "Enable DisplayPort multi-stream (default: enabled)");
अटल पूर्णांक nouveau_mst = 1;
module_param_named(mst, nouveau_mst, पूर्णांक, 0400);

अटल bool
nouveau_dp_has_sink_count(काष्ठा drm_connector *connector,
			  काष्ठा nouveau_encoder *outp)
अणु
	वापस drm_dp_पढ़ो_sink_count_cap(connector, outp->dp.dpcd, &outp->dp.desc);
पूर्ण

अटल क्रमागत drm_connector_status
nouveau_dp_probe_dpcd(काष्ठा nouveau_connector *nv_connector,
		      काष्ठा nouveau_encoder *outp)
अणु
	काष्ठा drm_connector *connector = &nv_connector->base;
	काष्ठा drm_dp_aux *aux = &nv_connector->aux;
	काष्ठा nv50_msपंचांग *msपंचांग = शून्य;
	क्रमागत drm_connector_status status = connector_status_disconnected;
	पूर्णांक ret;
	u8 *dpcd = outp->dp.dpcd;

	ret = drm_dp_पढ़ो_dpcd_caps(aux, dpcd);
	अगर (ret < 0)
		जाओ out;

	ret = drm_dp_पढ़ो_desc(aux, &outp->dp.desc, drm_dp_is_branch(dpcd));
	अगर (ret < 0)
		जाओ out;

	अगर (nouveau_mst) अणु
		msपंचांग = outp->dp.msपंचांग;
		अगर (msपंचांग)
			msपंचांग->can_mst = drm_dp_पढ़ो_mst_cap(aux, dpcd);
	पूर्ण

	अगर (nouveau_dp_has_sink_count(connector, outp)) अणु
		ret = drm_dp_पढ़ो_sink_count(aux);
		अगर (ret < 0)
			जाओ out;

		outp->dp.sink_count = ret;

		/*
		 * Dongle connected, but no display. Don't bother पढ़ोing
		 * करोwnstream port info
		 */
		अगर (!outp->dp.sink_count)
			वापस connector_status_disconnected;
	पूर्ण

	ret = drm_dp_पढ़ो_करोwnstream_info(aux, dpcd,
					  outp->dp.करोwnstream_ports);
	अगर (ret < 0)
		जाओ out;

	status = connector_status_connected;
out:
	अगर (status != connector_status_connected) अणु
		/* Clear any cached info */
		outp->dp.sink_count = 0;
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक
nouveau_dp_detect(काष्ठा nouveau_connector *nv_connector,
		  काष्ठा nouveau_encoder *nv_encoder)
अणु
	काष्ठा drm_device *dev = nv_encoder->base.base.dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा drm_connector *connector = &nv_connector->base;
	काष्ठा nv50_msपंचांग *msपंचांग = nv_encoder->dp.msपंचांग;
	क्रमागत drm_connector_status status;
	u8 *dpcd = nv_encoder->dp.dpcd;
	पूर्णांक ret = NOUVEAU_DP_NONE;

	/* If we've already read the DPCD on an eDP device, we don't need to
	 * reपढ़ो it as it won't change
	 */
	अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP &&
	    dpcd[DP_DPCD_REV] != 0)
		वापस NOUVEAU_DP_SST;

	mutex_lock(&nv_encoder->dp.hpd_irq_lock);
	अगर (msपंचांग) अणु
		/* If we're not पढ़ोy to handle MST state changes yet, just
		 * report the last status of the connector. We'll reprobe it
		 * once we've resumed.
		 */
		अगर (msपंचांग->suspended) अणु
			अगर (msपंचांग->is_mst)
				ret = NOUVEAU_DP_MST;
			अन्यथा अगर (connector->status ==
				 connector_status_connected)
				ret = NOUVEAU_DP_SST;

			जाओ out;
		पूर्ण
	पूर्ण

	status = nouveau_dp_probe_dpcd(nv_connector, nv_encoder);
	अगर (status == connector_status_disconnected)
		जाओ out;

	/* If we're in MST mode, we're करोne here */
	अगर (msपंचांग && msपंचांग->can_mst && msपंचांग->is_mst) अणु
		ret = NOUVEAU_DP_MST;
		जाओ out;
	पूर्ण

	nv_encoder->dp.link_bw = 27000 * dpcd[DP_MAX_LINK_RATE];
	nv_encoder->dp.link_nr =
		dpcd[DP_MAX_LANE_COUNT] & DP_MAX_LANE_COUNT_MASK;

	NV_DEBUG(drm, "display: %dx%d dpcd 0x%02x\n",
		 nv_encoder->dp.link_nr, nv_encoder->dp.link_bw,
		 dpcd[DP_DPCD_REV]);
	NV_DEBUG(drm, "encoder: %dx%d\n",
		 nv_encoder->dcb->dpconf.link_nr,
		 nv_encoder->dcb->dpconf.link_bw);

	अगर (nv_encoder->dcb->dpconf.link_nr < nv_encoder->dp.link_nr)
		nv_encoder->dp.link_nr = nv_encoder->dcb->dpconf.link_nr;
	अगर (nv_encoder->dcb->dpconf.link_bw < nv_encoder->dp.link_bw)
		nv_encoder->dp.link_bw = nv_encoder->dcb->dpconf.link_bw;

	NV_DEBUG(drm, "maximum: %dx%d\n",
		 nv_encoder->dp.link_nr, nv_encoder->dp.link_bw);

	अगर (msपंचांग && msपंचांग->can_mst) अणु
		ret = nv50_msपंचांग_detect(nv_encoder);
		अगर (ret == 1) अणु
			ret = NOUVEAU_DP_MST;
			जाओ out;
		पूर्ण अन्यथा अगर (ret != 0) अणु
			जाओ out;
		पूर्ण
	पूर्ण
	ret = NOUVEAU_DP_SST;

out:
	अगर (msपंचांग && !msपंचांग->suspended && ret != NOUVEAU_DP_MST)
		nv50_msपंचांग_हटाओ(msपंचांग);

	mutex_unlock(&nv_encoder->dp.hpd_irq_lock);
	वापस ret;
पूर्ण

व्योम nouveau_dp_irq(काष्ठा nouveau_drm *drm,
		    काष्ठा nouveau_connector *nv_connector)
अणु
	काष्ठा drm_connector *connector = &nv_connector->base;
	काष्ठा nouveau_encoder *outp = find_encoder(connector, DCB_OUTPUT_DP);
	काष्ठा nv50_msपंचांग *msपंचांग;
	पूर्णांक ret;
	bool send_hpd = false;

	अगर (!outp)
		वापस;

	msपंचांग = outp->dp.msपंचांग;
	NV_DEBUG(drm, "service %s\n", connector->name);

	mutex_lock(&outp->dp.hpd_irq_lock);

	अगर (msपंचांग && msपंचांग->is_mst) अणु
		अगर (!nv50_msपंचांग_service(drm, nv_connector, msपंचांग))
			send_hpd = true;
	पूर्ण अन्यथा अणु
		drm_dp_cec_irq(&nv_connector->aux);

		अगर (nouveau_dp_has_sink_count(connector, outp)) अणु
			ret = drm_dp_पढ़ो_sink_count(&nv_connector->aux);
			अगर (ret != outp->dp.sink_count)
				send_hpd = true;
			अगर (ret >= 0)
				outp->dp.sink_count = ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&outp->dp.hpd_irq_lock);

	अगर (send_hpd)
		nouveau_connector_hpd(connector);
पूर्ण

/* TODO:
 * - Use the minimum possible BPC here, once we add support क्रम the max bpc
 *   property.
 * - Validate against the DP caps advertised by the GPU (we करोn't check these
 *   yet)
 */
क्रमागत drm_mode_status
nv50_dp_mode_valid(काष्ठा drm_connector *connector,
		   काष्ठा nouveau_encoder *outp,
		   स्थिर काष्ठा drm_display_mode *mode,
		   अचिन्हित *out_घड़ी)
अणु
	स्थिर अचिन्हित पूर्णांक min_घड़ी = 25000;
	अचिन्हित पूर्णांक max_rate, mode_rate, ds_max_करोtघड़ी, घड़ी = mode->घड़ी;
	स्थिर u8 bpp = connector->display_info.bpc * 3;

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE && !outp->caps.dp_पूर्णांकerlace)
		वापस MODE_NO_INTERLACE;

	अगर ((mode->flags & DRM_MODE_FLAG_3D_MASK) == DRM_MODE_FLAG_3D_FRAME_PACKING)
		घड़ी *= 2;

	max_rate = outp->dp.link_nr * outp->dp.link_bw;
	mode_rate = DIV_ROUND_UP(घड़ी * bpp, 8);
	अगर (mode_rate > max_rate)
		वापस MODE_CLOCK_HIGH;

	ds_max_करोtघड़ी = drm_dp_करोwnstream_max_करोtघड़ी(outp->dp.dpcd, outp->dp.करोwnstream_ports);
	अगर (ds_max_करोtघड़ी && घड़ी > ds_max_करोtघड़ी)
		वापस MODE_CLOCK_HIGH;

	अगर (घड़ी < min_घड़ी)
		वापस MODE_CLOCK_LOW;

	अगर (out_घड़ी)
		*out_घड़ी = घड़ी;

	वापस MODE_OK;
पूर्ण
