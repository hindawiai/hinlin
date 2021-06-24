<शैली गुरु>
/*
 * Copyright 2014 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */

/*******************************************************************************
 * NVIF client driver - NVKM directly linked
 ******************************************************************************/

#समावेश <core/client.h>
#समावेश <core/notअगरy.h>
#समावेश <core/ioctl.h>

#समावेश <nvअगर/client.h>
#समावेश <nvअगर/driver.h>
#समावेश <nvअगर/notअगरy.h>
#समावेश <nvअगर/event.h>
#समावेश <nvअगर/ioctl.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_usif.h"

अटल व्योम
nvkm_client_unmap(व्योम *priv, व्योम __iomem *ptr, u32 size)
अणु
	iounmap(ptr);
पूर्ण

अटल व्योम __iomem *
nvkm_client_map(व्योम *priv, u64 handle, u32 size)
अणु
	वापस ioremap(handle, size);
पूर्ण

अटल पूर्णांक
nvkm_client_ioctl(व्योम *priv, bool super, व्योम *data, u32 size, व्योम **hack)
अणु
	वापस nvkm_ioctl(priv, super, data, size, hack);
पूर्ण

अटल पूर्णांक
nvkm_client_resume(व्योम *priv)
अणु
	काष्ठा nvkm_client *client = priv;
	वापस nvkm_object_init(&client->object);
पूर्ण

अटल पूर्णांक
nvkm_client_suspend(व्योम *priv)
अणु
	काष्ठा nvkm_client *client = priv;
	वापस nvkm_object_fini(&client->object, true);
पूर्ण

अटल पूर्णांक
nvkm_client_ntfy(स्थिर व्योम *header, u32 length, स्थिर व्योम *data, u32 size)
अणु
	स्थिर जोड़ अणु
		काष्ठा nvअगर_notअगरy_req_v0 v0;
	पूर्ण *args = header;
	u8 route;

	अगर (length == माप(args->v0) && args->v0.version == 0) अणु
		route = args->v0.route;
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		वापस NVKM_NOTIFY_DROP;
	पूर्ण

	चयन (route) अणु
	हाल NVDRM_NOTIFY_NVIF:
		वापस nvअगर_notअगरy(header, length, data, size);
	हाल NVDRM_NOTIFY_USIF:
		वापस usअगर_notअगरy(header, length, data, size);
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस NVKM_NOTIFY_DROP;
पूर्ण

अटल पूर्णांक
nvkm_client_driver_init(स्थिर अक्षर *name, u64 device, स्थिर अक्षर *cfg,
			स्थिर अक्षर *dbg, व्योम **ppriv)
अणु
	वापस nvkm_client_new(name, device, cfg, dbg, nvkm_client_ntfy,
			       (काष्ठा nvkm_client **)ppriv);
पूर्ण

स्थिर काष्ठा nvअगर_driver
nvअगर_driver_nvkm = अणु
	.name = "nvkm",
	.init = nvkm_client_driver_init,
	.suspend = nvkm_client_suspend,
	.resume = nvkm_client_resume,
	.ioctl = nvkm_client_ioctl,
	.map = nvkm_client_map,
	.unmap = nvkm_client_unmap,
	.keep = false,
पूर्ण;
