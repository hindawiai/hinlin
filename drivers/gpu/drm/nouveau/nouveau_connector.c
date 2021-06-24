<शैली गुरु>
/*
 * Copyright (C) 2008 Maarten Maathuis.
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

#समावेश <acpi/button.h>

#समावेश <linux/pm_runसमय.स>
#समावेश <linux/vga_चयनeroo.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_atomic.h>

#समावेश "nouveau_reg.h"
#समावेश "nouveau_drv.h"
#समावेश "dispnv04/hw.h"
#समावेश "dispnv50/disp.h"
#समावेश "nouveau_acpi.h"

#समावेश "nouveau_display.h"
#समावेश "nouveau_connector.h"
#समावेश "nouveau_encoder.h"
#समावेश "nouveau_crtc.h"

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0046.h>
#समावेश <nvअगर/event.h>

काष्ठा drm_display_mode *
nouveau_conn_native_mode(काष्ठा drm_connector *connector)
अणु
	स्थिर काष्ठा drm_connector_helper_funcs *helper = connector->helper_निजी;
	काष्ठा nouveau_drm *drm = nouveau_drm(connector->dev);
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_display_mode *mode, *largest = शून्य;
	पूर्णांक high_w = 0, high_h = 0, high_v = 0;

	list_क्रम_each_entry(mode, &connector->probed_modes, head) अणु
		अगर (helper->mode_valid(connector, mode) != MODE_OK ||
		    (mode->flags & DRM_MODE_FLAG_INTERLACE))
			जारी;

		/* Use preferred mode अगर there is one.. */
		अगर (mode->type & DRM_MODE_TYPE_PREFERRED) अणु
			NV_DEBUG(drm, "native mode from preferred\n");
			वापस drm_mode_duplicate(dev, mode);
		पूर्ण

		/* Otherwise, take the resolution with the largest width, then
		 * height, then vertical refresh
		 */
		अगर (mode->hdisplay < high_w)
			जारी;

		अगर (mode->hdisplay == high_w && mode->vdisplay < high_h)
			जारी;

		अगर (mode->hdisplay == high_w && mode->vdisplay == high_h &&
		    drm_mode_vrefresh(mode) < high_v)
			जारी;

		high_w = mode->hdisplay;
		high_h = mode->vdisplay;
		high_v = drm_mode_vrefresh(mode);
		largest = mode;
	पूर्ण

	NV_DEBUG(drm, "native mode from largest: %dx%d@%d\n",
		      high_w, high_h, high_v);
	वापस largest ? drm_mode_duplicate(dev, largest) : शून्य;
पूर्ण

पूर्णांक
nouveau_conn_atomic_get_property(काष्ठा drm_connector *connector,
				 स्थिर काष्ठा drm_connector_state *state,
				 काष्ठा drm_property *property, u64 *val)
अणु
	काष्ठा nouveau_conn_atom *asyc = nouveau_conn_atom(state);
	काष्ठा nouveau_display *disp = nouveau_display(connector->dev);
	काष्ठा drm_device *dev = connector->dev;

	अगर (property == dev->mode_config.scaling_mode_property)
		*val = asyc->scaler.mode;
	अन्यथा अगर (property == disp->underscan_property)
		*val = asyc->scaler.underscan.mode;
	अन्यथा अगर (property == disp->underscan_hborder_property)
		*val = asyc->scaler.underscan.hborder;
	अन्यथा अगर (property == disp->underscan_vborder_property)
		*val = asyc->scaler.underscan.vborder;
	अन्यथा अगर (property == disp->dithering_mode)
		*val = asyc->dither.mode;
	अन्यथा अगर (property == disp->dithering_depth)
		*val = asyc->dither.depth;
	अन्यथा अगर (property == disp->vibrant_hue_property)
		*val = asyc->procamp.vibrant_hue;
	अन्यथा अगर (property == disp->color_vibrance_property)
		*val = asyc->procamp.color_vibrance;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक
nouveau_conn_atomic_set_property(काष्ठा drm_connector *connector,
				 काष्ठा drm_connector_state *state,
				 काष्ठा drm_property *property, u64 val)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा nouveau_conn_atom *asyc = nouveau_conn_atom(state);
	काष्ठा nouveau_display *disp = nouveau_display(dev);

	अगर (property == dev->mode_config.scaling_mode_property) अणु
		चयन (val) अणु
		हाल DRM_MODE_SCALE_NONE:
			/* We allow 'None' क्रम EDID modes, even on a fixed
			 * panel (some exist with support क्रम lower refresh
			 * rates, which people might want to use क्रम घातer-
			 * saving purposes).
			 *
			 * Non-EDID modes will क्रमce the use of GPU scaling
			 * to the native mode regardless of this setting.
			 */
			चयन (connector->connector_type) अणु
			हाल DRM_MODE_CONNECTOR_LVDS:
			हाल DRM_MODE_CONNECTOR_eDP:
				/* ... except prior to G80, where the code
				 * करोesn't support such things.
				 */
				अगर (disp->disp.object.oclass < NV50_DISP)
					वापस -EINVAL;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		हाल DRM_MODE_SCALE_FULLSCREEN:
		हाल DRM_MODE_SCALE_CENTER:
		हाल DRM_MODE_SCALE_ASPECT:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (asyc->scaler.mode != val) अणु
			asyc->scaler.mode = val;
			asyc->set.scaler = true;
		पूर्ण
	पूर्ण अन्यथा
	अगर (property == disp->underscan_property) अणु
		अगर (asyc->scaler.underscan.mode != val) अणु
			asyc->scaler.underscan.mode = val;
			asyc->set.scaler = true;
		पूर्ण
	पूर्ण अन्यथा
	अगर (property == disp->underscan_hborder_property) अणु
		अगर (asyc->scaler.underscan.hborder != val) अणु
			asyc->scaler.underscan.hborder = val;
			asyc->set.scaler = true;
		पूर्ण
	पूर्ण अन्यथा
	अगर (property == disp->underscan_vborder_property) अणु
		अगर (asyc->scaler.underscan.vborder != val) अणु
			asyc->scaler.underscan.vborder = val;
			asyc->set.scaler = true;
		पूर्ण
	पूर्ण अन्यथा
	अगर (property == disp->dithering_mode) अणु
		अगर (asyc->dither.mode != val) अणु
			asyc->dither.mode = val;
			asyc->set.dither = true;
		पूर्ण
	पूर्ण अन्यथा
	अगर (property == disp->dithering_depth) अणु
		अगर (asyc->dither.mode != val) अणु
			asyc->dither.depth = val;
			asyc->set.dither = true;
		पूर्ण
	पूर्ण अन्यथा
	अगर (property == disp->vibrant_hue_property) अणु
		अगर (asyc->procamp.vibrant_hue != val) अणु
			asyc->procamp.vibrant_hue = val;
			asyc->set.procamp = true;
		पूर्ण
	पूर्ण अन्यथा
	अगर (property == disp->color_vibrance_property) अणु
		अगर (asyc->procamp.color_vibrance != val) अणु
			asyc->procamp.color_vibrance = val;
			asyc->set.procamp = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
nouveau_conn_atomic_destroy_state(काष्ठा drm_connector *connector,
				  काष्ठा drm_connector_state *state)
अणु
	काष्ठा nouveau_conn_atom *asyc = nouveau_conn_atom(state);
	__drm_atomic_helper_connector_destroy_state(&asyc->state);
	kमुक्त(asyc);
पूर्ण

काष्ठा drm_connector_state *
nouveau_conn_atomic_duplicate_state(काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_conn_atom *armc = nouveau_conn_atom(connector->state);
	काष्ठा nouveau_conn_atom *asyc;
	अगर (!(asyc = kदो_स्मृति(माप(*asyc), GFP_KERNEL)))
		वापस शून्य;
	__drm_atomic_helper_connector_duplicate_state(connector, &asyc->state);
	asyc->dither = armc->dither;
	asyc->scaler = armc->scaler;
	asyc->procamp = armc->procamp;
	asyc->set.mask = 0;
	वापस &asyc->state;
पूर्ण

व्योम
nouveau_conn_reset(काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_conn_atom *asyc;

	अगर (drm_drv_uses_atomic_modeset(connector->dev)) अणु
		अगर (WARN_ON(!(asyc = kzalloc(माप(*asyc), GFP_KERNEL))))
			वापस;

		अगर (connector->state)
			nouveau_conn_atomic_destroy_state(connector,
							  connector->state);

		__drm_atomic_helper_connector_reset(connector, &asyc->state);
	पूर्ण अन्यथा अणु
		asyc = &nv_connector->properties_state;
	पूर्ण

	asyc->dither.mode = DITHERING_MODE_AUTO;
	asyc->dither.depth = DITHERING_DEPTH_AUTO;
	asyc->scaler.mode = DRM_MODE_SCALE_NONE;
	asyc->scaler.underscan.mode = UNDERSCAN_OFF;
	asyc->procamp.color_vibrance = 150;
	asyc->procamp.vibrant_hue = 90;

	अगर (nouveau_display(connector->dev)->disp.object.oclass < NV50_DISP) अणु
		चयन (connector->connector_type) अणु
		हाल DRM_MODE_CONNECTOR_LVDS:
			/* See note in nouveau_conn_atomic_set_property(). */
			asyc->scaler.mode = DRM_MODE_SCALE_FULLSCREEN;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम
nouveau_conn_attach_properties(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा nouveau_display *disp = nouveau_display(dev);
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_conn_atom *armc;

	अगर (drm_drv_uses_atomic_modeset(connector->dev))
		armc = nouveau_conn_atom(connector->state);
	अन्यथा
		armc = &nv_connector->properties_state;

	/* Init DVI-I specअगरic properties. */
	अगर (connector->connector_type == DRM_MODE_CONNECTOR_DVII)
		drm_object_attach_property(&connector->base, dev->mode_config.
					   dvi_i_subconnector_property, 0);

	/* Add overscan compensation options to digital outमाला_दो. */
	अगर (disp->underscan_property &&
	    (connector->connector_type == DRM_MODE_CONNECTOR_DVID ||
	     connector->connector_type == DRM_MODE_CONNECTOR_DVII ||
	     connector->connector_type == DRM_MODE_CONNECTOR_HDMIA ||
	     connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort)) अणु
		drm_object_attach_property(&connector->base,
					   disp->underscan_property,
					   UNDERSCAN_OFF);
		drm_object_attach_property(&connector->base,
					   disp->underscan_hborder_property, 0);
		drm_object_attach_property(&connector->base,
					   disp->underscan_vborder_property, 0);
	पूर्ण

	/* Add hue and saturation options. */
	अगर (disp->vibrant_hue_property)
		drm_object_attach_property(&connector->base,
					   disp->vibrant_hue_property,
					   armc->procamp.vibrant_hue);
	अगर (disp->color_vibrance_property)
		drm_object_attach_property(&connector->base,
					   disp->color_vibrance_property,
					   armc->procamp.color_vibrance);

	/* Scaling mode property. */
	चयन (connector->connector_type) अणु
	हाल DRM_MODE_CONNECTOR_TV:
		अवरोध;
	हाल DRM_MODE_CONNECTOR_VGA:
		अगर (disp->disp.object.oclass < NV50_DISP)
			अवरोध; /* Can only scale on DFPs. */
		fallthrough;
	शेष:
		drm_object_attach_property(&connector->base, dev->mode_config.
					   scaling_mode_property,
					   armc->scaler.mode);
		अवरोध;
	पूर्ण

	/* Dithering properties. */
	चयन (connector->connector_type) अणु
	हाल DRM_MODE_CONNECTOR_TV:
	हाल DRM_MODE_CONNECTOR_VGA:
		अवरोध;
	शेष:
		अगर (disp->dithering_mode) अणु
			drm_object_attach_property(&connector->base,
						   disp->dithering_mode,
						   armc->dither.mode);
		पूर्ण
		अगर (disp->dithering_depth) अणु
			drm_object_attach_property(&connector->base,
						   disp->dithering_depth,
						   armc->dither.depth);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

MODULE_PARM_DESC(tv_disable, "Disable TV-out detection");
पूर्णांक nouveau_tv_disable = 0;
module_param_named(tv_disable, nouveau_tv_disable, पूर्णांक, 0400);

MODULE_PARM_DESC(ignorelid, "Ignore ACPI lid status");
पूर्णांक nouveau_ignorelid = 0;
module_param_named(ignorelid, nouveau_ignorelid, पूर्णांक, 0400);

MODULE_PARM_DESC(duallink, "Allow dual-link TMDS (default: enabled)");
पूर्णांक nouveau_duallink = 1;
module_param_named(duallink, nouveau_duallink, पूर्णांक, 0400);

MODULE_PARM_DESC(hdmimhz, "Force a maximum HDMI pixel clock (in MHz)");
पूर्णांक nouveau_hdmimhz = 0;
module_param_named(hdmimhz, nouveau_hdmimhz, पूर्णांक, 0400);

काष्ठा nouveau_encoder *
find_encoder(काष्ठा drm_connector *connector, पूर्णांक type)
अणु
	काष्ठा nouveau_encoder *nv_encoder;
	काष्ठा drm_encoder *enc;

	drm_connector_क्रम_each_possible_encoder(connector, enc) अणु
		nv_encoder = nouveau_encoder(enc);

		अगर (type == DCB_OUTPUT_ANY ||
		    (nv_encoder->dcb && nv_encoder->dcb->type == type))
			वापस nv_encoder;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
nouveau_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	nvअगर_notअगरy_dtor(&nv_connector->hpd);
	kमुक्त(nv_connector->edid);
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	अगर (nv_connector->aux.transfer) अणु
		drm_dp_cec_unरेजिस्टर_connector(&nv_connector->aux);
		drm_dp_aux_unरेजिस्टर(&nv_connector->aux);
		kमुक्त(nv_connector->aux.name);
	पूर्ण
	kमुक्त(connector);
पूर्ण

अटल काष्ठा nouveau_encoder *
nouveau_connector_ddc_detect(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा nouveau_encoder *nv_encoder = शून्य, *found = शून्य;
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret;
	bool चयनeroo_ddc = false;

	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		nv_encoder = nouveau_encoder(encoder);

		चयन (nv_encoder->dcb->type) अणु
		हाल DCB_OUTPUT_DP:
			ret = nouveau_dp_detect(nouveau_connector(connector),
						nv_encoder);
			अगर (ret == NOUVEAU_DP_MST)
				वापस शून्य;
			अन्यथा अगर (ret == NOUVEAU_DP_SST)
				found = nv_encoder;

			अवरोध;
		हाल DCB_OUTPUT_LVDS:
			चयनeroo_ddc = !!(vga_चयनeroo_handler_flags() &
					    VGA_SWITCHEROO_CAN_SWITCH_DDC);
			fallthrough;
		शेष:
			अगर (!nv_encoder->i2c)
				अवरोध;

			अगर (चयनeroo_ddc)
				vga_चयनeroo_lock_ddc(pdev);
			अगर (nvkm_probe_i2c(nv_encoder->i2c, 0x50))
				found = nv_encoder;
			अगर (चयनeroo_ddc)
				vga_चयनeroo_unlock_ddc(pdev);

			अवरोध;
		पूर्ण
		अगर (found)
			अवरोध;
	पूर्ण

	वापस found;
पूर्ण

अटल काष्ठा nouveau_encoder *
nouveau_connector_of_detect(काष्ठा drm_connector *connector)
अणु
#अगर_घोषित __घातerpc__
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_encoder *nv_encoder;
	काष्ठा device_node *cn, *dn = pci_device_to_OF_node(dev->pdev);

	अगर (!dn ||
	    !((nv_encoder = find_encoder(connector, DCB_OUTPUT_TMDS)) ||
	      (nv_encoder = find_encoder(connector, DCB_OUTPUT_ANALOG))))
		वापस शून्य;

	क्रम_each_child_of_node(dn, cn) अणु
		स्थिर अक्षर *name = of_get_property(cn, "name", शून्य);
		स्थिर व्योम *edid = of_get_property(cn, "EDID", शून्य);
		पूर्णांक idx = name ? name[म_माप(name) - 1] - 'A' : 0;

		अगर (nv_encoder->dcb->i2c_index == idx && edid) अणु
			nv_connector->edid =
				kmemdup(edid, EDID_LENGTH, GFP_KERNEL);
			of_node_put(cn);
			वापस nv_encoder;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस शून्य;
पूर्ण

अटल व्योम
nouveau_connector_set_encoder(काष्ठा drm_connector *connector,
			      काष्ठा nouveau_encoder *nv_encoder)
अणु
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_drm *drm = nouveau_drm(connector->dev);
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	अगर (nv_connector->detected_encoder == nv_encoder)
		वापस;
	nv_connector->detected_encoder = nv_encoder;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA) अणु
		अगर (nv_encoder->dcb->type == DCB_OUTPUT_DP)
			connector->पूर्णांकerlace_allowed =
				nv_encoder->caps.dp_पूर्णांकerlace;
		अन्यथा
			connector->पूर्णांकerlace_allowed = true;
		connector->द्विगुनscan_allowed = true;
	पूर्ण अन्यथा
	अगर (nv_encoder->dcb->type == DCB_OUTPUT_LVDS ||
	    nv_encoder->dcb->type == DCB_OUTPUT_TMDS) अणु
		connector->द्विगुनscan_allowed = false;
		connector->पूर्णांकerlace_allowed = false;
	पूर्ण अन्यथा अणु
		connector->द्विगुनscan_allowed = true;
		अगर (drm->client.device.info.family == NV_DEVICE_INFO_V0_KELVIN ||
		    (drm->client.device.info.family == NV_DEVICE_INFO_V0_CELSIUS &&
		     (pdev->device & 0x0ff0) != 0x0100 &&
		     (pdev->device & 0x0ff0) != 0x0150))
			/* HW is broken */
			connector->पूर्णांकerlace_allowed = false;
		अन्यथा
			connector->पूर्णांकerlace_allowed = true;
	पूर्ण

	अगर (nv_connector->type == DCB_CONNECTOR_DVI_I) अणु
		drm_object_property_set_value(&connector->base,
			dev->mode_config.dvi_i_subconnector_property,
			nv_encoder->dcb->type == DCB_OUTPUT_TMDS ?
			DRM_MODE_SUBCONNECTOR_DVID :
			DRM_MODE_SUBCONNECTOR_DVIA);
	पूर्ण
पूर्ण

अटल व्योम
nouveau_connector_set_edid(काष्ठा nouveau_connector *nv_connector,
			   काष्ठा edid *edid)
अणु
	अगर (nv_connector->edid != edid) अणु
		काष्ठा edid *old_edid = nv_connector->edid;

		drm_connector_update_edid_property(&nv_connector->base, edid);
		kमुक्त(old_edid);
		nv_connector->edid = edid;
	पूर्ण
पूर्ण

अटल क्रमागत drm_connector_status
nouveau_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_encoder *nv_encoder = शून्य;
	काष्ठा nouveau_encoder *nv_partner;
	काष्ठा i2c_adapter *i2c;
	पूर्णांक type;
	पूर्णांक ret;
	क्रमागत drm_connector_status conn_status = connector_status_disconnected;

	/* Outमाला_दो are only polled जबतक runसमय active, so resuming the
	 * device here is unnecessary (and would deadlock upon runसमय suspend
	 * because it रुकोs क्रम polling to finish). We करो however, want to
	 * prevent the स्वतःsuspend समयr from elapsing during this operation
	 * अगर possible.
	 */
	अगर (drm_kms_helper_is_poll_worker()) अणु
		pm_runसमय_get_noresume(dev->dev);
	पूर्ण अन्यथा अणु
		ret = pm_runसमय_get_sync(dev->dev);
		अगर (ret < 0 && ret != -EACCES) अणु
			pm_runसमय_put_स्वतःsuspend(dev->dev);
			nouveau_connector_set_edid(nv_connector, शून्य);
			वापस conn_status;
		पूर्ण
	पूर्ण

	nv_encoder = nouveau_connector_ddc_detect(connector);
	अगर (nv_encoder && (i2c = nv_encoder->i2c) != शून्य) अणु
		काष्ठा edid *new_edid;

		अगर ((vga_चयनeroo_handler_flags() &
		     VGA_SWITCHEROO_CAN_SWITCH_DDC) &&
		    nv_connector->type == DCB_CONNECTOR_LVDS)
			new_edid = drm_get_edid_चयनeroo(connector, i2c);
		अन्यथा
			new_edid = drm_get_edid(connector, i2c);

		nouveau_connector_set_edid(nv_connector, new_edid);
		अगर (!nv_connector->edid) अणु
			NV_ERROR(drm, "DDC responded, but no EDID for %s\n",
				 connector->name);
			जाओ detect_analog;
		पूर्ण

		/* Override encoder type क्रम DVI-I based on whether EDID
		 * says the display is digital or analog, both use the
		 * same i2c channel so the value वापसed from ddc_detect
		 * isn't necessarily correct.
		 */
		nv_partner = शून्य;
		अगर (nv_encoder->dcb->type == DCB_OUTPUT_TMDS)
			nv_partner = find_encoder(connector, DCB_OUTPUT_ANALOG);
		अगर (nv_encoder->dcb->type == DCB_OUTPUT_ANALOG)
			nv_partner = find_encoder(connector, DCB_OUTPUT_TMDS);

		अगर (nv_partner && ((nv_encoder->dcb->type == DCB_OUTPUT_ANALOG &&
				    nv_partner->dcb->type == DCB_OUTPUT_TMDS) ||
				   (nv_encoder->dcb->type == DCB_OUTPUT_TMDS &&
				    nv_partner->dcb->type == DCB_OUTPUT_ANALOG))) अणु
			अगर (nv_connector->edid->input & DRM_EDID_INPUT_DIGITAL)
				type = DCB_OUTPUT_TMDS;
			अन्यथा
				type = DCB_OUTPUT_ANALOG;

			nv_encoder = find_encoder(connector, type);
		पूर्ण

		nouveau_connector_set_encoder(connector, nv_encoder);
		conn_status = connector_status_connected;
		drm_dp_cec_set_edid(&nv_connector->aux, nv_connector->edid);
		जाओ out;
	पूर्ण अन्यथा अणु
		nouveau_connector_set_edid(nv_connector, शून्य);
	पूर्ण

	nv_encoder = nouveau_connector_of_detect(connector);
	अगर (nv_encoder) अणु
		nouveau_connector_set_encoder(connector, nv_encoder);
		conn_status = connector_status_connected;
		जाओ out;
	पूर्ण

detect_analog:
	nv_encoder = find_encoder(connector, DCB_OUTPUT_ANALOG);
	अगर (!nv_encoder && !nouveau_tv_disable)
		nv_encoder = find_encoder(connector, DCB_OUTPUT_TV);
	अगर (nv_encoder && क्रमce) अणु
		काष्ठा drm_encoder *encoder = to_drm_encoder(nv_encoder);
		स्थिर काष्ठा drm_encoder_helper_funcs *helper =
						encoder->helper_निजी;

		अगर (helper->detect(encoder, connector) ==
						connector_status_connected) अणु
			nouveau_connector_set_encoder(connector, nv_encoder);
			conn_status = connector_status_connected;
			जाओ out;
		पूर्ण
	पूर्ण

 out:
	अगर (!nv_connector->edid)
		drm_dp_cec_unset_edid(&nv_connector->aux);

	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस conn_status;
पूर्ण

अटल क्रमागत drm_connector_status
nouveau_connector_detect_lvds(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_encoder *nv_encoder = शून्य;
	काष्ठा edid *edid = शून्य;
	क्रमागत drm_connector_status status = connector_status_disconnected;

	nv_encoder = find_encoder(connector, DCB_OUTPUT_LVDS);
	अगर (!nv_encoder)
		जाओ out;

	/* Try retrieving EDID via DDC */
	अगर (!drm->vbios.fp_no_ddc) अणु
		status = nouveau_connector_detect(connector, क्रमce);
		अगर (status == connector_status_connected) अणु
			edid = nv_connector->edid;
			जाओ out;
		पूर्ण
	पूर्ण

	/* On some laptops (Sony, i'm looking at you) there appears to
	 * be no direct way of accessing the panel's EDID.  The only
	 * option available to us appears to be to ask ACPI क्रम help..
	 *
	 * It's important this check's beक्रमe trying straps, one of the
	 * said manufacturer's laptops are configured in such a way
	 * the nouveau decides an entry in the VBIOS FP mode table is
	 * valid - it's not (rh#613284)
	 */
	अगर (nv_encoder->dcb->lvdsconf.use_acpi_क्रम_edid) अणु
		edid = nouveau_acpi_edid(dev, connector);
		अगर (edid) अणु
			status = connector_status_connected;
			जाओ out;
		पूर्ण
	पूर्ण

	/* If no EDID found above, and the VBIOS indicates a hardcoded
	 * modeline is avalilable क्रम the panel, set it as the panel's
	 * native mode and निकास.
	 */
	अगर (nouveau_bios_fp_mode(dev, शून्य) && (drm->vbios.fp_no_ddc ||
	    nv_encoder->dcb->lvdsconf.use_straps_क्रम_mode)) अणु
		status = connector_status_connected;
		जाओ out;
	पूर्ण

	/* Still nothing, some VBIOS images have a hardcoded EDID block
	 * stored क्रम the panel stored in them.
	 */
	अगर (!drm->vbios.fp_no_ddc) अणु
		edid = (काष्ठा edid *)nouveau_bios_embedded_edid(dev);
		अगर (edid) अणु
			edid = kmemdup(edid, EDID_LENGTH, GFP_KERNEL);
			अगर (edid)
				status = connector_status_connected;
		पूर्ण
	पूर्ण

out:
#अगर defined(CONFIG_ACPI_BUTTON) || \
	(defined(CONFIG_ACPI_BUTTON_MODULE) && defined(MODULE))
	अगर (status == connector_status_connected &&
	    !nouveau_ignorelid && !acpi_lid_खोलो())
		status = connector_status_unknown;
#पूर्ण_अगर

	nouveau_connector_set_edid(nv_connector, edid);
	nouveau_connector_set_encoder(connector, nv_encoder);
	वापस status;
पूर्ण

अटल व्योम
nouveau_connector_क्रमce(काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(connector->dev);
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_encoder *nv_encoder;
	पूर्णांक type;

	अगर (nv_connector->type == DCB_CONNECTOR_DVI_I) अणु
		अगर (connector->क्रमce == DRM_FORCE_ON_DIGITAL)
			type = DCB_OUTPUT_TMDS;
		अन्यथा
			type = DCB_OUTPUT_ANALOG;
	पूर्ण अन्यथा
		type = DCB_OUTPUT_ANY;

	nv_encoder = find_encoder(connector, type);
	अगर (!nv_encoder) अणु
		NV_ERROR(drm, "can't find encoder to force %s on!\n",
			 connector->name);
		connector->status = connector_status_disconnected;
		वापस;
	पूर्ण

	nouveau_connector_set_encoder(connector, nv_encoder);
पूर्ण

अटल पूर्णांक
nouveau_connector_set_property(काष्ठा drm_connector *connector,
			       काष्ठा drm_property *property, uपूर्णांक64_t value)
अणु
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_encoder *nv_encoder = nv_connector->detected_encoder;
	काष्ठा nouveau_conn_atom *asyc = &nv_connector->properties_state;
	काष्ठा drm_encoder *encoder = to_drm_encoder(nv_encoder);
	पूर्णांक ret;

	ret = connector->funcs->atomic_set_property(&nv_connector->base,
						    &asyc->state,
						    property, value);
	अगर (ret) अणु
		अगर (nv_encoder && nv_encoder->dcb->type == DCB_OUTPUT_TV)
			वापस get_slave_funcs(encoder)->set_property(
				encoder, connector, property, value);
		वापस ret;
	पूर्ण

	nv_connector->scaling_mode = asyc->scaler.mode;
	nv_connector->dithering_mode = asyc->dither.mode;

	अगर (connector->encoder && connector->encoder->crtc) अणु
		ret = drm_crtc_helper_set_mode(connector->encoder->crtc,
					      &connector->encoder->crtc->mode,
					       connector->encoder->crtc->x,
					       connector->encoder->crtc->y,
					       शून्य);
		अगर (!ret)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा moderec अणु
	पूर्णांक hdisplay;
	पूर्णांक vdisplay;
पूर्ण;

अटल काष्ठा moderec scaler_modes[] = अणु
	अणु 1920, 1200 पूर्ण,
	अणु 1920, 1080 पूर्ण,
	अणु 1680, 1050 पूर्ण,
	अणु 1600, 1200 पूर्ण,
	अणु 1400, 1050 पूर्ण,
	अणु 1280, 1024 पूर्ण,
	अणु 1280, 960 पूर्ण,
	अणु 1152, 864 पूर्ण,
	अणु 1024, 768 पूर्ण,
	अणु 800, 600 पूर्ण,
	अणु 720, 400 पूर्ण,
	अणु 640, 480 पूर्ण,
	अणु 640, 400 पूर्ण,
	अणु 640, 350 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक
nouveau_connector_scaler_modes_add(काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा drm_display_mode *native = nv_connector->native_mode, *m;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा moderec *mode = &scaler_modes[0];
	पूर्णांक modes = 0;

	अगर (!native)
		वापस 0;

	जबतक (mode->hdisplay) अणु
		अगर (mode->hdisplay <= native->hdisplay &&
		    mode->vdisplay <= native->vdisplay &&
		    (mode->hdisplay != native->hdisplay ||
		     mode->vdisplay != native->vdisplay)) अणु
			m = drm_cvt_mode(dev, mode->hdisplay, mode->vdisplay,
					 drm_mode_vrefresh(native), false,
					 false, false);
			अगर (!m)
				जारी;

			drm_mode_probed_add(connector, m);
			modes++;
		पूर्ण

		mode++;
	पूर्ण

	वापस modes;
पूर्ण

अटल व्योम
nouveau_connector_detect_depth(काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(connector->dev);
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_encoder *nv_encoder = nv_connector->detected_encoder;
	काष्ठा nvbios *bios = &drm->vbios;
	काष्ठा drm_display_mode *mode = nv_connector->native_mode;
	bool duallink;

	/* अगर the edid is feeling nice enough to provide this info, use it */
	अगर (nv_connector->edid && connector->display_info.bpc)
		वापस;

	/* EDID 1.4 is *supposed* to be supported on eDP, but, Apple... */
	अगर (nv_connector->type == DCB_CONNECTOR_eDP) अणु
		connector->display_info.bpc = 6;
		वापस;
	पूर्ण

	/* we're out of options unless we're LVDS, शेष to 8bpc */
	अगर (nv_encoder->dcb->type != DCB_OUTPUT_LVDS) अणु
		connector->display_info.bpc = 8;
		वापस;
	पूर्ण

	connector->display_info.bpc = 6;

	/* LVDS: panel straps */
	अगर (bios->fp_no_ddc) अणु
		अगर (bios->fp.अगर_is_24bit)
			connector->display_info.bpc = 8;
		वापस;
	पूर्ण

	/* LVDS: DDC panel, need to first determine the number of links to
	 * know which अगर_is_24bit flag to check...
	 */
	अगर (nv_connector->edid &&
	    nv_connector->type == DCB_CONNECTOR_LVDS_SPWG)
		duallink = ((u8 *)nv_connector->edid)[121] == 2;
	अन्यथा
		duallink = mode->घड़ी >= bios->fp.duallink_transition_clk;

	अगर ((!duallink && (bios->fp.strapless_is_24bit & 1)) ||
	    ( duallink && (bios->fp.strapless_is_24bit & 2)))
		connector->display_info.bpc = 8;
पूर्ण

अटल पूर्णांक
nouveau_connector_late_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	पूर्णांक ret;

	ret = nouveau_backlight_init(connector);

	वापस ret;
पूर्ण

अटल व्योम
nouveau_connector_early_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	nouveau_backlight_fini(connector);
पूर्ण

अटल पूर्णांक
nouveau_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_encoder *nv_encoder = nv_connector->detected_encoder;
	काष्ठा drm_encoder *encoder = to_drm_encoder(nv_encoder);
	पूर्णांक ret = 0;

	/* destroy the native mode, the attached monitor could have changed.
	 */
	अगर (nv_connector->native_mode) अणु
		drm_mode_destroy(dev, nv_connector->native_mode);
		nv_connector->native_mode = शून्य;
	पूर्ण

	अगर (nv_connector->edid)
		ret = drm_add_edid_modes(connector, nv_connector->edid);
	अन्यथा
	अगर (nv_encoder->dcb->type == DCB_OUTPUT_LVDS &&
	    (nv_encoder->dcb->lvdsconf.use_straps_क्रम_mode ||
	     drm->vbios.fp_no_ddc) && nouveau_bios_fp_mode(dev, शून्य)) अणु
		काष्ठा drm_display_mode mode;

		nouveau_bios_fp_mode(dev, &mode);
		nv_connector->native_mode = drm_mode_duplicate(dev, &mode);
	पूर्ण

	/* Determine display colour depth क्रम everything except LVDS now,
	 * DP requires this beक्रमe mode_valid() is called.
	 */
	अगर (connector->connector_type != DRM_MODE_CONNECTOR_LVDS)
		nouveau_connector_detect_depth(connector);

	/* Find the native mode अगर this is a digital panel, अगर we didn't
	 * find any modes through DDC previously add the native mode to
	 * the list of modes.
	 */
	अगर (!nv_connector->native_mode)
		nv_connector->native_mode = nouveau_conn_native_mode(connector);
	अगर (ret == 0 && nv_connector->native_mode) अणु
		काष्ठा drm_display_mode *mode;

		mode = drm_mode_duplicate(dev, nv_connector->native_mode);
		drm_mode_probed_add(connector, mode);
		ret = 1;
	पूर्ण

	/* Determine LVDS colour depth, must happen after determining
	 * "native" mode as some VBIOS tables require us to use the
	 * pixel घड़ी as part of the lookup...
	 */
	अगर (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)
		nouveau_connector_detect_depth(connector);

	अगर (nv_encoder->dcb->type == DCB_OUTPUT_TV)
		ret = get_slave_funcs(encoder)->get_modes(encoder, connector);

	अगर (nv_connector->type == DCB_CONNECTOR_LVDS ||
	    nv_connector->type == DCB_CONNECTOR_LVDS_SPWG ||
	    nv_connector->type == DCB_CONNECTOR_eDP)
		ret += nouveau_connector_scaler_modes_add(connector);

	वापस ret;
पूर्ण

अटल अचिन्हित
get_पंचांगds_link_bandwidth(काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_encoder *nv_encoder = nv_connector->detected_encoder;
	काष्ठा nouveau_drm *drm = nouveau_drm(connector->dev);
	काष्ठा dcb_output *dcb = nv_connector->detected_encoder->dcb;
	काष्ठा drm_display_info *info = शून्य;
	अचिन्हित duallink_scale =
		nouveau_duallink && nv_encoder->dcb->duallink_possible ? 2 : 1;

	अगर (drm_detect_hdmi_monitor(nv_connector->edid)) अणु
		info = &nv_connector->base.display_info;
		duallink_scale = 1;
	पूर्ण

	अगर (info) अणु
		अगर (nouveau_hdmimhz > 0)
			वापस nouveau_hdmimhz * 1000;
		/* Note: these limits are conservative, some Fermi's
		 * can करो 297 MHz. Unclear how this can be determined.
		 */
		अगर (drm->client.device.info.chipset >= 0x120) अणु
			स्थिर पूर्णांक max_पंचांगds_घड़ी =
				info->hdmi.scdc.scrambling.supported ?
				594000 : 340000;
			वापस info->max_पंचांगds_घड़ी ?
				min(info->max_पंचांगds_घड़ी, max_पंचांगds_घड़ी) :
				max_पंचांगds_घड़ी;
		पूर्ण
		अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_KEPLER)
			वापस 297000;
		अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_FERMI)
			वापस 225000;
	पूर्ण

	अगर (dcb->location != DCB_LOC_ON_CHIP ||
	    drm->client.device.info.chipset >= 0x46)
		वापस 165000 * duallink_scale;
	अन्यथा अगर (drm->client.device.info.chipset >= 0x40)
		वापस 155000 * duallink_scale;
	अन्यथा अगर (drm->client.device.info.chipset >= 0x18)
		वापस 135000 * duallink_scale;
	अन्यथा
		वापस 112000 * duallink_scale;
पूर्ण

अटल क्रमागत drm_mode_status
nouveau_connector_mode_valid(काष्ठा drm_connector *connector,
			     काष्ठा drm_display_mode *mode)
अणु
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_encoder *nv_encoder = nv_connector->detected_encoder;
	काष्ठा drm_encoder *encoder = to_drm_encoder(nv_encoder);
	अचिन्हित पूर्णांक min_घड़ी = 25000, max_घड़ी = min_घड़ी, घड़ी = mode->घड़ी;

	चयन (nv_encoder->dcb->type) अणु
	हाल DCB_OUTPUT_LVDS:
		अगर (nv_connector->native_mode &&
		    (mode->hdisplay > nv_connector->native_mode->hdisplay ||
		     mode->vdisplay > nv_connector->native_mode->vdisplay))
			वापस MODE_PANEL;

		min_घड़ी = 0;
		max_घड़ी = 400000;
		अवरोध;
	हाल DCB_OUTPUT_TMDS:
		max_घड़ी = get_पंचांगds_link_bandwidth(connector);
		अवरोध;
	हाल DCB_OUTPUT_ANALOG:
		max_घड़ी = nv_encoder->dcb->crtconf.maxfreq;
		अगर (!max_घड़ी)
			max_घड़ी = 350000;
		अवरोध;
	हाल DCB_OUTPUT_TV:
		वापस get_slave_funcs(encoder)->mode_valid(encoder, mode);
	हाल DCB_OUTPUT_DP:
		वापस nv50_dp_mode_valid(connector, nv_encoder, mode, शून्य);
	शेष:
		BUG();
		वापस MODE_BAD;
	पूर्ण

	अगर ((mode->flags & DRM_MODE_FLAG_3D_MASK) == DRM_MODE_FLAG_3D_FRAME_PACKING)
		घड़ी *= 2;

	अगर (घड़ी < min_घड़ी)
		वापस MODE_CLOCK_LOW;
	अगर (घड़ी > max_घड़ी)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल काष्ठा drm_encoder *
nouveau_connector_best_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);

	अगर (nv_connector->detected_encoder)
		वापस to_drm_encoder(nv_connector->detected_encoder);

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs
nouveau_connector_helper_funcs = अणु
	.get_modes = nouveau_connector_get_modes,
	.mode_valid = nouveau_connector_mode_valid,
	.best_encoder = nouveau_connector_best_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs
nouveau_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.reset = nouveau_conn_reset,
	.detect = nouveau_connector_detect,
	.क्रमce = nouveau_connector_क्रमce,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = nouveau_connector_set_property,
	.destroy = nouveau_connector_destroy,
	.atomic_duplicate_state = nouveau_conn_atomic_duplicate_state,
	.atomic_destroy_state = nouveau_conn_atomic_destroy_state,
	.atomic_set_property = nouveau_conn_atomic_set_property,
	.atomic_get_property = nouveau_conn_atomic_get_property,
	.late_रेजिस्टर = nouveau_connector_late_रेजिस्टर,
	.early_unरेजिस्टर = nouveau_connector_early_unरेजिस्टर,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs
nouveau_connector_funcs_lvds = अणु
	.dpms = drm_helper_connector_dpms,
	.reset = nouveau_conn_reset,
	.detect = nouveau_connector_detect_lvds,
	.क्रमce = nouveau_connector_क्रमce,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = nouveau_connector_set_property,
	.destroy = nouveau_connector_destroy,
	.atomic_duplicate_state = nouveau_conn_atomic_duplicate_state,
	.atomic_destroy_state = nouveau_conn_atomic_destroy_state,
	.atomic_set_property = nouveau_conn_atomic_set_property,
	.atomic_get_property = nouveau_conn_atomic_get_property,
	.late_रेजिस्टर = nouveau_connector_late_रेजिस्टर,
	.early_unरेजिस्टर = nouveau_connector_early_unरेजिस्टर,
पूर्ण;

व्योम
nouveau_connector_hpd(काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(connector->dev);
	u32 mask = drm_connector_mask(connector);

	mutex_lock(&drm->hpd_lock);
	अगर (!(drm->hpd_pending & mask)) अणु
		drm->hpd_pending |= mask;
		schedule_work(&drm->hpd_work);
	पूर्ण
	mutex_unlock(&drm->hpd_lock);
पूर्ण

अटल पूर्णांक
nouveau_connector_hotplug(काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	काष्ठा nouveau_connector *nv_connector =
		container_of(notअगरy, typeof(*nv_connector), hpd);
	काष्ठा drm_connector *connector = &nv_connector->base;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	स्थिर काष्ठा nvअगर_notअगरy_conn_rep_v0 *rep = notअगरy->data;
	bool plugged = (rep->mask != NVIF_NOTIFY_CONN_V0_UNPLUG);

	अगर (rep->mask & NVIF_NOTIFY_CONN_V0_IRQ) अणु
		nouveau_dp_irq(drm, nv_connector);
		वापस NVIF_NOTIFY_KEEP;
	पूर्ण

	NV_DEBUG(drm, "%splugged %s\n", plugged ? "" : "un", connector->name);
	nouveau_connector_hpd(connector);

	वापस NVIF_NOTIFY_KEEP;
पूर्ण

अटल sमाप_प्रकार
nouveau_connector_aux_xfer(काष्ठा drm_dp_aux *obj, काष्ठा drm_dp_aux_msg *msg)
अणु
	काष्ठा nouveau_connector *nv_connector =
		container_of(obj, typeof(*nv_connector), aux);
	काष्ठा nouveau_encoder *nv_encoder;
	काष्ठा nvkm_i2c_aux *aux;
	u8 size = msg->size;
	पूर्णांक ret;

	nv_encoder = find_encoder(&nv_connector->base, DCB_OUTPUT_DP);
	अगर (!nv_encoder || !(aux = nv_encoder->aux))
		वापस -ENODEV;
	अगर (WARN_ON(msg->size > 16))
		वापस -E2BIG;

	ret = nvkm_i2c_aux_acquire(aux);
	अगर (ret)
		वापस ret;

	ret = nvkm_i2c_aux_xfer(aux, false, msg->request, msg->address,
				msg->buffer, &size);
	nvkm_i2c_aux_release(aux);
	अगर (ret >= 0) अणु
		msg->reply = ret;
		वापस size;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
drm_conntype_from_dcb(क्रमागत dcb_connector_type dcb)
अणु
	चयन (dcb) अणु
	हाल DCB_CONNECTOR_VGA      : वापस DRM_MODE_CONNECTOR_VGA;
	हाल DCB_CONNECTOR_TV_0     :
	हाल DCB_CONNECTOR_TV_1     :
	हाल DCB_CONNECTOR_TV_3     : वापस DRM_MODE_CONNECTOR_TV;
	हाल DCB_CONNECTOR_DMS59_0  :
	हाल DCB_CONNECTOR_DMS59_1  :
	हाल DCB_CONNECTOR_DVI_I    : वापस DRM_MODE_CONNECTOR_DVII;
	हाल DCB_CONNECTOR_DVI_D    : वापस DRM_MODE_CONNECTOR_DVID;
	हाल DCB_CONNECTOR_LVDS     :
	हाल DCB_CONNECTOR_LVDS_SPWG: वापस DRM_MODE_CONNECTOR_LVDS;
	हाल DCB_CONNECTOR_DMS59_DP0:
	हाल DCB_CONNECTOR_DMS59_DP1:
	हाल DCB_CONNECTOR_DP       :
	हाल DCB_CONNECTOR_mDP      :
	हाल DCB_CONNECTOR_USB_C    : वापस DRM_MODE_CONNECTOR_DisplayPort;
	हाल DCB_CONNECTOR_eDP      : वापस DRM_MODE_CONNECTOR_eDP;
	हाल DCB_CONNECTOR_HDMI_0   :
	हाल DCB_CONNECTOR_HDMI_1   :
	हाल DCB_CONNECTOR_HDMI_C   : वापस DRM_MODE_CONNECTOR_HDMIA;
	हाल DCB_CONNECTOR_WFD	    : वापस DRM_MODE_CONNECTOR_VIRTUAL;
	शेष:
		अवरोध;
	पूर्ण

	वापस DRM_MODE_CONNECTOR_Unknown;
पूर्ण

काष्ठा drm_connector *
nouveau_connector_create(काष्ठा drm_device *dev,
			 स्थिर काष्ठा dcb_output *dcbe)
अणु
	स्थिर काष्ठा drm_connector_funcs *funcs = &nouveau_connector_funcs;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_display *disp = nouveau_display(dev);
	काष्ठा nouveau_connector *nv_connector = शून्य;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	अक्षर aux_name[48] = अणु0पूर्ण;
	पूर्णांक index = dcbe->connector;
	पूर्णांक type, ret = 0;
	bool dummy;

	drm_connector_list_iter_begin(dev, &conn_iter);
	nouveau_क्रम_each_non_mst_connector_iter(connector, &conn_iter) अणु
		nv_connector = nouveau_connector(connector);
		अगर (nv_connector->index == index) अणु
			drm_connector_list_iter_end(&conn_iter);
			वापस connector;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	nv_connector = kzalloc(माप(*nv_connector), GFP_KERNEL);
	अगर (!nv_connector)
		वापस ERR_PTR(-ENOMEM);

	connector = &nv_connector->base;
	nv_connector->index = index;

	/* attempt to parse vbios connector type and hotplug gpio */
	nv_connector->dcb = olddcb_conn(dev, index);
	अगर (nv_connector->dcb) अणु
		u32 entry = ROM16(nv_connector->dcb[0]);
		अगर (olddcb_conntab(dev)[3] >= 4)
			entry |= (u32)ROM16(nv_connector->dcb[2]) << 16;

		nv_connector->type = nv_connector->dcb[0];
		अगर (drm_conntype_from_dcb(nv_connector->type) ==
					  DRM_MODE_CONNECTOR_Unknown) अणु
			NV_WARN(drm, "unknown connector type %02x\n",
				nv_connector->type);
			nv_connector->type = DCB_CONNECTOR_NONE;
		पूर्ण

		/* Gigabyte NX85T */
		अगर (nv_match_device(dev, 0x0421, 0x1458, 0x344c)) अणु
			अगर (nv_connector->type == DCB_CONNECTOR_HDMI_1)
				nv_connector->type = DCB_CONNECTOR_DVI_I;
		पूर्ण

		/* Gigabyte GV-NX86T512H */
		अगर (nv_match_device(dev, 0x0402, 0x1458, 0x3455)) अणु
			अगर (nv_connector->type == DCB_CONNECTOR_HDMI_1)
				nv_connector->type = DCB_CONNECTOR_DVI_I;
		पूर्ण
	पूर्ण अन्यथा अणु
		nv_connector->type = DCB_CONNECTOR_NONE;
	पूर्ण

	/* no vbios data, or an unknown dcb connector type - attempt to
	 * figure out something suitable ourselves
	 */
	अगर (nv_connector->type == DCB_CONNECTOR_NONE) अणु
		काष्ठा nouveau_drm *drm = nouveau_drm(dev);
		काष्ठा dcb_table *dcbt = &drm->vbios.dcb;
		u32 encoders = 0;
		पूर्णांक i;

		क्रम (i = 0; i < dcbt->entries; i++) अणु
			अगर (dcbt->entry[i].connector == nv_connector->index)
				encoders |= (1 << dcbt->entry[i].type);
		पूर्ण

		अगर (encoders & (1 << DCB_OUTPUT_DP)) अणु
			अगर (encoders & (1 << DCB_OUTPUT_TMDS))
				nv_connector->type = DCB_CONNECTOR_DP;
			अन्यथा
				nv_connector->type = DCB_CONNECTOR_eDP;
		पूर्ण अन्यथा
		अगर (encoders & (1 << DCB_OUTPUT_TMDS)) अणु
			अगर (encoders & (1 << DCB_OUTPUT_ANALOG))
				nv_connector->type = DCB_CONNECTOR_DVI_I;
			अन्यथा
				nv_connector->type = DCB_CONNECTOR_DVI_D;
		पूर्ण अन्यथा
		अगर (encoders & (1 << DCB_OUTPUT_ANALOG)) अणु
			nv_connector->type = DCB_CONNECTOR_VGA;
		पूर्ण अन्यथा
		अगर (encoders & (1 << DCB_OUTPUT_LVDS)) अणु
			nv_connector->type = DCB_CONNECTOR_LVDS;
		पूर्ण अन्यथा
		अगर (encoders & (1 << DCB_OUTPUT_TV)) अणु
			nv_connector->type = DCB_CONNECTOR_TV_0;
		पूर्ण
	पूर्ण

	चयन ((type = drm_conntype_from_dcb(nv_connector->type))) अणु
	हाल DRM_MODE_CONNECTOR_LVDS:
		ret = nouveau_bios_parse_lvds_table(dev, 0, &dummy, &dummy);
		अगर (ret) अणु
			NV_ERROR(drm, "Error parsing LVDS table, disabling\n");
			kमुक्त(nv_connector);
			वापस ERR_PTR(ret);
		पूर्ण

		funcs = &nouveau_connector_funcs_lvds;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DisplayPort:
	हाल DRM_MODE_CONNECTOR_eDP:
		nv_connector->aux.dev = connector->kdev;
		nv_connector->aux.transfer = nouveau_connector_aux_xfer;
		snम_लिखो(aux_name, माप(aux_name), "sor-%04x-%04x",
			 dcbe->hasht, dcbe->hashm);
		nv_connector->aux.name = kstrdup(aux_name, GFP_KERNEL);
		ret = drm_dp_aux_रेजिस्टर(&nv_connector->aux);
		अगर (ret) अणु
			NV_ERROR(drm, "failed to register aux channel\n");
			kमुक्त(nv_connector);
			वापस ERR_PTR(ret);
		पूर्ण
		funcs = &nouveau_connector_funcs;
		अवरोध;
	शेष:
		funcs = &nouveau_connector_funcs;
		अवरोध;
	पूर्ण

	/* HDMI 3D support */
	अगर ((disp->disp.object.oclass >= G82_DISP)
	    && ((type == DRM_MODE_CONNECTOR_DisplayPort)
		|| (type == DRM_MODE_CONNECTOR_eDP)
		|| (type == DRM_MODE_CONNECTOR_HDMIA)))
		connector->stereo_allowed = true;

	/* शेषs, will get overridden in detect() */
	connector->पूर्णांकerlace_allowed = false;
	connector->द्विगुनscan_allowed = false;

	drm_connector_init(dev, connector, funcs, type);
	drm_connector_helper_add(connector, &nouveau_connector_helper_funcs);

	connector->funcs->reset(connector);
	nouveau_conn_attach_properties(connector);

	/* Default scaling mode */
	चयन (nv_connector->type) अणु
	हाल DCB_CONNECTOR_LVDS:
	हाल DCB_CONNECTOR_LVDS_SPWG:
	हाल DCB_CONNECTOR_eDP:
		/* see note in nouveau_connector_set_property() */
		अगर (disp->disp.object.oclass < NV50_DISP) अणु
			nv_connector->scaling_mode = DRM_MODE_SCALE_FULLSCREEN;
			अवरोध;
		पूर्ण
		nv_connector->scaling_mode = DRM_MODE_SCALE_NONE;
		अवरोध;
	शेष:
		nv_connector->scaling_mode = DRM_MODE_SCALE_NONE;
		अवरोध;
	पूर्ण

	/* dithering properties */
	चयन (nv_connector->type) अणु
	हाल DCB_CONNECTOR_TV_0:
	हाल DCB_CONNECTOR_TV_1:
	हाल DCB_CONNECTOR_TV_3:
	हाल DCB_CONNECTOR_VGA:
		अवरोध;
	शेष:
		nv_connector->dithering_mode = DITHERING_MODE_AUTO;
		अवरोध;
	पूर्ण

	चयन (type) अणु
	हाल DRM_MODE_CONNECTOR_DisplayPort:
	हाल DRM_MODE_CONNECTOR_eDP:
		drm_dp_cec_रेजिस्टर_connector(&nv_connector->aux, connector);
		अवरोध;
	पूर्ण

	ret = nvअगर_notअगरy_ctor(&disp->disp.object, "kmsHotplug",
			       nouveau_connector_hotplug,
			       true, NV04_DISP_NTFY_CONN,
			       &(काष्ठा nvअगर_notअगरy_conn_req_v0) अणु
				.mask = NVIF_NOTIFY_CONN_V0_ANY,
				.conn = index,
			       पूर्ण,
			       माप(काष्ठा nvअगर_notअगरy_conn_req_v0),
			       माप(काष्ठा nvअगर_notअगरy_conn_rep_v0),
			       &nv_connector->hpd);
	अगर (ret)
		connector->polled = DRM_CONNECTOR_POLL_CONNECT;
	अन्यथा
		connector->polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_रेजिस्टर(connector);
	वापस connector;
पूर्ण
