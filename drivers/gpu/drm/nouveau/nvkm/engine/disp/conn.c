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
 * Authors: Ben Skeggs
 */
#समावेश "conn.h"
#समावेश "outp.h"
#समावेश "priv.h"

#समावेश <subdev/gpपन.स>

#समावेश <nvअगर/event.h>

अटल पूर्णांक
nvkm_conn_hpd(काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nvkm_conn *conn = container_of(notअगरy, typeof(*conn), hpd);
	काष्ठा nvkm_disp *disp = conn->disp;
	काष्ठा nvkm_gpio *gpio = disp->engine.subdev.device->gpio;
	स्थिर काष्ठा nvkm_gpio_ntfy_rep *line = notअगरy->data;
	काष्ठा nvअगर_notअगरy_conn_rep_v0 rep;
	पूर्णांक index = conn->index;

	CONN_DBG(conn, "HPD: %d", line->mask);

	अगर (!nvkm_gpio_get(gpio, 0, DCB_GPIO_UNUSED, conn->hpd.index))
		rep.mask = NVIF_NOTIFY_CONN_V0_UNPLUG;
	अन्यथा
		rep.mask = NVIF_NOTIFY_CONN_V0_PLUG;
	rep.version = 0;

	nvkm_event_send(&disp->hpd, rep.mask, index, &rep, माप(rep));
	वापस NVKM_NOTIFY_KEEP;
पूर्ण

व्योम
nvkm_conn_fini(काष्ठा nvkm_conn *conn)
अणु
	nvkm_notअगरy_put(&conn->hpd);
पूर्ण

व्योम
nvkm_conn_init(काष्ठा nvkm_conn *conn)
अणु
	nvkm_notअगरy_get(&conn->hpd);
पूर्ण

व्योम
nvkm_conn_del(काष्ठा nvkm_conn **pconn)
अणु
	काष्ठा nvkm_conn *conn = *pconn;
	अगर (conn) अणु
		nvkm_notअगरy_fini(&conn->hpd);
		kमुक्त(*pconn);
		*pconn = शून्य;
	पूर्ण
पूर्ण

अटल व्योम
nvkm_conn_ctor(काष्ठा nvkm_disp *disp, पूर्णांक index, काष्ठा nvbios_connE *info,
	       काष्ठा nvkm_conn *conn)
अणु
	अटल स्थिर u8 hpd[] = अणु 0x07, 0x08, 0x51, 0x52, 0x5e, 0x5f, 0x60 पूर्ण;
	काष्ठा nvkm_gpio *gpio = disp->engine.subdev.device->gpio;
	काष्ठा dcb_gpio_func func;
	पूर्णांक ret;

	conn->disp = disp;
	conn->index = index;
	conn->info = *info;

	CONN_DBG(conn, "type %02x loc %d hpd %02x dp %x di %x sr %x lcdid %x",
		 info->type, info->location, info->hpd, info->dp,
		 info->di, info->sr, info->lcdid);

	अगर ((info->hpd = ffs(info->hpd))) अणु
		अगर (--info->hpd >= ARRAY_SIZE(hpd)) अणु
			CONN_ERR(conn, "hpd %02x unknown", info->hpd);
			वापस;
		पूर्ण
		info->hpd = hpd[info->hpd];

		ret = nvkm_gpio_find(gpio, 0, info->hpd, DCB_GPIO_UNUSED, &func);
		अगर (ret) अणु
			CONN_ERR(conn, "func %02x lookup failed, %d",
				 info->hpd, ret);
			वापस;
		पूर्ण

		ret = nvkm_notअगरy_init(शून्य, &gpio->event, nvkm_conn_hpd,
				       true, &(काष्ठा nvkm_gpio_ntfy_req) अणु
					.mask = NVKM_GPIO_TOGGLED,
					.line = func.line,
				       पूर्ण,
				       माप(काष्ठा nvkm_gpio_ntfy_req),
				       माप(काष्ठा nvkm_gpio_ntfy_rep),
				       &conn->hpd);
		अगर (ret) अणु
			CONN_ERR(conn, "func %02x failed, %d", info->hpd, ret);
		पूर्ण अन्यथा अणु
			CONN_DBG(conn, "func %02x (HPD)", info->hpd);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
nvkm_conn_new(काष्ठा nvkm_disp *disp, पूर्णांक index, काष्ठा nvbios_connE *info,
	      काष्ठा nvkm_conn **pconn)
अणु
	अगर (!(*pconn = kzalloc(माप(**pconn), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_conn_ctor(disp, index, info, *pconn);
	वापस 0;
पूर्ण
