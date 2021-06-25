<शैली गुरु>
/*
 * Copyright 2016 Red Hat Inc.
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
#समावेश <nvअगर/driver.h>
#समावेश <nvअगर/client.h>

अटल स्थिर काष्ठा nvअगर_driver *
nvअगर_driver[] = अणु
#अगर_घोषित __KERNEL__
	&nvअगर_driver_nvkm,
#अन्यथा
	&nvअगर_driver_drm,
	&nvअगर_driver_lib,
	&nvअगर_driver_null,
#पूर्ण_अगर
	शून्य
पूर्ण;

पूर्णांक
nvअगर_driver_init(स्थिर अक्षर *drv, स्थिर अक्षर *cfg, स्थिर अक्षर *dbg,
		 स्थिर अक्षर *name, u64 device, काष्ठा nvअगर_client *client)
अणु
	पूर्णांक ret = -EINVAL, i;

	क्रम (i = 0; (client->driver = nvअगर_driver[i]); i++) अणु
		अगर (!drv || !म_भेद(client->driver->name, drv)) अणु
			ret = client->driver->init(name, device, cfg, dbg,
						   &client->object.priv);
			अगर (ret == 0)
				अवरोध;
			client->driver->fini(client->object.priv);
		पूर्ण
	पूर्ण

	अगर (ret == 0)
		ret = nvअगर_client_ctor(client, name, device, client);
	वापस ret;
पूर्ण
