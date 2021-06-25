<शैली गुरु>
/*
 * Copyright (C) 2009 Red Hat <mjg@redhat.com>
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

/*
 * Authors:
 *  Matthew Garrett <mjg@redhat.com>
 *
 * Register locations derived from NVClock by Roderick Colenbअक्रमer
 */

#समावेश <linux/apple-gmux.h>
#समावेश <linux/backlight.h>
#समावेश <linux/idr.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_reg.h"
#समावेश "nouveau_encoder.h"
#समावेश "nouveau_connector.h"

अटल काष्ठा ida bl_ida;
#घोषणा BL_NAME_SIZE 15 // 12 क्रम name + 2 क्रम digits + 1 क्रम '\0'

काष्ठा nouveau_backlight अणु
	काष्ठा backlight_device *dev;
	पूर्णांक id;
पूर्ण;

अटल bool
nouveau_get_backlight_name(अक्षर backlight_name[BL_NAME_SIZE],
			   काष्ठा nouveau_backlight *bl)
अणु
	स्थिर पूर्णांक nb = ida_simple_get(&bl_ida, 0, 0, GFP_KERNEL);
	अगर (nb < 0 || nb >= 100)
		वापस false;
	अगर (nb > 0)
		snम_लिखो(backlight_name, BL_NAME_SIZE, "nv_backlight%d", nb);
	अन्यथा
		snम_लिखो(backlight_name, BL_NAME_SIZE, "nv_backlight");
	bl->id = nb;
	वापस true;
पूर्ण

अटल पूर्णांक
nv40_get_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	काष्ठा nouveau_encoder *nv_encoder = bl_get_data(bd);
	काष्ठा nouveau_drm *drm = nouveau_drm(nv_encoder->base.base.dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	पूर्णांक val = (nvअगर_rd32(device, NV40_PMC_BACKLIGHT) &
		   NV40_PMC_BACKLIGHT_MASK) >> 16;

	वापस val;
पूर्ण

अटल पूर्णांक
nv40_set_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	काष्ठा nouveau_encoder *nv_encoder = bl_get_data(bd);
	काष्ठा nouveau_drm *drm = nouveau_drm(nv_encoder->base.base.dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	पूर्णांक val = bd->props.brightness;
	पूर्णांक reg = nvअगर_rd32(device, NV40_PMC_BACKLIGHT);

	nvअगर_wr32(device, NV40_PMC_BACKLIGHT,
		  (val << 16) | (reg & ~NV40_PMC_BACKLIGHT_MASK));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops nv40_bl_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.get_brightness = nv40_get_पूर्णांकensity,
	.update_status = nv40_set_पूर्णांकensity,
पूर्ण;

अटल पूर्णांक
nv40_backlight_init(काष्ठा nouveau_encoder *encoder,
		    काष्ठा backlight_properties *props,
		    स्थिर काष्ठा backlight_ops **ops)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(encoder->base.base.dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;

	अगर (!(nvअगर_rd32(device, NV40_PMC_BACKLIGHT) & NV40_PMC_BACKLIGHT_MASK))
		वापस -ENODEV;

	props->type = BACKLIGHT_RAW;
	props->max_brightness = 31;
	*ops = &nv40_bl_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_get_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	काष्ठा nouveau_encoder *nv_encoder = bl_get_data(bd);
	काष्ठा nouveau_drm *drm = nouveau_drm(nv_encoder->base.base.dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	पूर्णांक or = ffs(nv_encoder->dcb->or) - 1;
	u32 भाग = 1025;
	u32 val;

	val  = nvअगर_rd32(device, NV50_PDISP_SOR_PWM_CTL(or));
	val &= NV50_PDISP_SOR_PWM_CTL_VAL;
	वापस ((val * 100) + (भाग / 2)) / भाग;
पूर्ण

अटल पूर्णांक
nv50_set_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	काष्ठा nouveau_encoder *nv_encoder = bl_get_data(bd);
	काष्ठा nouveau_drm *drm = nouveau_drm(nv_encoder->base.base.dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	पूर्णांक or = ffs(nv_encoder->dcb->or) - 1;
	u32 भाग = 1025;
	u32 val = (bd->props.brightness * भाग) / 100;

	nvअगर_wr32(device, NV50_PDISP_SOR_PWM_CTL(or),
		  NV50_PDISP_SOR_PWM_CTL_NEW | val);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops nv50_bl_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.get_brightness = nv50_get_पूर्णांकensity,
	.update_status = nv50_set_पूर्णांकensity,
पूर्ण;

अटल पूर्णांक
nva3_get_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	काष्ठा nouveau_encoder *nv_encoder = bl_get_data(bd);
	काष्ठा nouveau_drm *drm = nouveau_drm(nv_encoder->base.base.dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	पूर्णांक or = ffs(nv_encoder->dcb->or) - 1;
	u32 भाग, val;

	भाग  = nvअगर_rd32(device, NV50_PDISP_SOR_PWM_DIV(or));
	val  = nvअगर_rd32(device, NV50_PDISP_SOR_PWM_CTL(or));
	val &= NVA3_PDISP_SOR_PWM_CTL_VAL;
	अगर (भाग && भाग >= val)
		वापस ((val * 100) + (भाग / 2)) / भाग;

	वापस 100;
पूर्ण

अटल पूर्णांक
nva3_set_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	काष्ठा nouveau_encoder *nv_encoder = bl_get_data(bd);
	काष्ठा nouveau_drm *drm = nouveau_drm(nv_encoder->base.base.dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;
	पूर्णांक or = ffs(nv_encoder->dcb->or) - 1;
	u32 भाग, val;

	भाग = nvअगर_rd32(device, NV50_PDISP_SOR_PWM_DIV(or));
	val = (bd->props.brightness * भाग) / 100;
	अगर (भाग) अणु
		nvअगर_wr32(device, NV50_PDISP_SOR_PWM_CTL(or),
			  val |
			  NV50_PDISP_SOR_PWM_CTL_NEW |
			  NVA3_PDISP_SOR_PWM_CTL_UNK);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा backlight_ops nva3_bl_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.get_brightness = nva3_get_पूर्णांकensity,
	.update_status = nva3_set_पूर्णांकensity,
पूर्ण;

अटल पूर्णांक
nv50_backlight_init(काष्ठा nouveau_encoder *nv_encoder,
		    काष्ठा backlight_properties *props,
		    स्थिर काष्ठा backlight_ops **ops)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(nv_encoder->base.base.dev);
	काष्ठा nvअगर_object *device = &drm->client.device.object;

	अगर (!nvअगर_rd32(device, NV50_PDISP_SOR_PWM_CTL(ffs(nv_encoder->dcb->or) - 1)))
		वापस -ENODEV;

	अगर (drm->client.device.info.chipset <= 0xa0 ||
	    drm->client.device.info.chipset == 0xaa ||
	    drm->client.device.info.chipset == 0xac)
		*ops = &nv50_bl_ops;
	अन्यथा
		*ops = &nva3_bl_ops;

	props->type = BACKLIGHT_RAW;
	props->max_brightness = 100;

	वापस 0;
पूर्ण

पूर्णांक
nouveau_backlight_init(काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(connector->dev);
	काष्ठा nouveau_backlight *bl;
	काष्ठा nouveau_encoder *nv_encoder = शून्य;
	काष्ठा nvअगर_device *device = &drm->client.device;
	अक्षर backlight_name[BL_NAME_SIZE];
	काष्ठा backlight_properties props = अणु0पूर्ण;
	स्थिर काष्ठा backlight_ops *ops;
	पूर्णांक ret;

	अगर (apple_gmux_present()) अणु
		NV_INFO_ONCE(drm, "Apple GMUX detected: not registering Nouveau backlight interface\n");
		वापस 0;
	पूर्ण

	अगर (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)
		nv_encoder = find_encoder(connector, DCB_OUTPUT_LVDS);
	अन्यथा अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP)
		nv_encoder = find_encoder(connector, DCB_OUTPUT_DP);
	अन्यथा
		वापस 0;

	अगर (!nv_encoder)
		वापस 0;

	चयन (device->info.family) अणु
	हाल NV_DEVICE_INFO_V0_CURIE:
		ret = nv40_backlight_init(nv_encoder, &props, &ops);
		अवरोध;
	हाल NV_DEVICE_INFO_V0_TESLA:
	हाल NV_DEVICE_INFO_V0_FERMI:
	हाल NV_DEVICE_INFO_V0_KEPLER:
	हाल NV_DEVICE_INFO_V0_MAXWELL:
	हाल NV_DEVICE_INFO_V0_PASCAL:
	हाल NV_DEVICE_INFO_V0_VOLTA:
	हाल NV_DEVICE_INFO_V0_TURING:
	हाल NV_DEVICE_INFO_V0_AMPERE: //XXX: not confirmed
		ret = nv50_backlight_init(nv_encoder, &props, &ops);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (ret == -ENODEV)
		वापस 0;
	अन्यथा अगर (ret)
		वापस ret;

	bl = kzalloc(माप(*bl), GFP_KERNEL);
	अगर (!bl)
		वापस -ENOMEM;

	अगर (!nouveau_get_backlight_name(backlight_name, bl)) अणु
		NV_ERROR(drm, "Failed to retrieve a unique name for the backlight interface\n");
		जाओ fail_alloc;
	पूर्ण

	bl->dev = backlight_device_रेजिस्टर(backlight_name, connector->kdev,
					    nv_encoder, ops, &props);
	अगर (IS_ERR(bl->dev)) अणु
		अगर (bl->id >= 0)
			ida_simple_हटाओ(&bl_ida, bl->id);
		ret = PTR_ERR(bl->dev);
		जाओ fail_alloc;
	पूर्ण

	nouveau_connector(connector)->backlight = bl;
	bl->dev->props.brightness = bl->dev->ops->get_brightness(bl->dev);
	backlight_update_status(bl->dev);

	वापस 0;

fail_alloc:
	kमुक्त(bl);
	वापस ret;
पूर्ण

व्योम
nouveau_backlight_fini(काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_connector *nv_conn = nouveau_connector(connector);
	काष्ठा nouveau_backlight *bl = nv_conn->backlight;

	अगर (!bl)
		वापस;

	अगर (bl->id >= 0)
		ida_simple_हटाओ(&bl_ida, bl->id);

	backlight_device_unरेजिस्टर(bl->dev);
	nv_conn->backlight = शून्य;
	kमुक्त(bl);
पूर्ण

व्योम
nouveau_backlight_ctor(व्योम)
अणु
	ida_init(&bl_ida);
पूर्ण

व्योम
nouveau_backlight_dtor(व्योम)
अणु
	ida_destroy(&bl_ida);
पूर्ण
