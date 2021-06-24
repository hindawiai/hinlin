<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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

#समावेश <nvअगर/client.h>
#समावेश <nvअगर/driver.h>
#समावेश <nvअगर/ioctl.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/अगर0000.h>

पूर्णांक
nvअगर_client_ioctl(काष्ठा nvअगर_client *client, व्योम *data, u32 size)
अणु
	वापस client->driver->ioctl(client->object.priv, client->super, data, size, शून्य);
पूर्ण

पूर्णांक
nvअगर_client_suspend(काष्ठा nvअगर_client *client)
अणु
	वापस client->driver->suspend(client->object.priv);
पूर्ण

पूर्णांक
nvअगर_client_resume(काष्ठा nvअगर_client *client)
अणु
	वापस client->driver->resume(client->object.priv);
पूर्ण

व्योम
nvअगर_client_dtor(काष्ठा nvअगर_client *client)
अणु
	nvअगर_object_dtor(&client->object);
	अगर (client->driver) अणु
		अगर (client->driver->fini)
			client->driver->fini(client->object.priv);
		client->driver = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvअगर_client_ctor(काष्ठा nvअगर_client *parent, स्थिर अक्षर *name, u64 device,
		 काष्ठा nvअगर_client *client)
अणु
	काष्ठा nvअगर_client_v0 args = अणु .device = device पूर्ण;
	काष्ठा अणु
		काष्ठा nvअगर_ioctl_v0 ioctl;
		काष्ठा nvअगर_ioctl_nop_v0 nop;
	पूर्ण nop = अणुपूर्ण;
	पूर्णांक ret;

	म_नकलन(args.name, name, माप(args.name));
	ret = nvअगर_object_ctor(parent != client ? &parent->object : शून्य,
			       name ? name : "nvifClient", 0,
			       NVIF_CLASS_CLIENT, &args, माप(args),
			       &client->object);
	अगर (ret)
		वापस ret;

	client->object.client = client;
	client->object.handle = ~0;
	client->route = NVIF_IOCTL_V0_ROUTE_NVIF;
	client->super = true;
	client->driver = parent->driver;

	अगर (ret == 0) अणु
		ret = nvअगर_client_ioctl(client, &nop, माप(nop));
		client->version = nop.nop.version;
	पूर्ण

	अगर (ret)
		nvअगर_client_dtor(client);
	वापस ret;
पूर्ण
