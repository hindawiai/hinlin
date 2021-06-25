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
 * Authors: Ben Skeggs
 */
#समावेश "priv.h"
#समावेश "conn.h"
#समावेश "dp.h"
#समावेश "head.h"
#समावेश "ior.h"
#समावेश "outp.h"

#समावेश <core/client.h>
#समावेश <core/notअगरy.h>
#समावेश <core/oproxy.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/dcb.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0046.h>
#समावेश <nvअगर/event.h>
#समावेश <nvअगर/unpack.h>

अटल व्योम
nvkm_disp_vblank_fini(काष्ठा nvkm_event *event, पूर्णांक type, पूर्णांक id)
अणु
	काष्ठा nvkm_disp *disp = container_of(event, typeof(*disp), vblank);
	काष्ठा nvkm_head *head = nvkm_head_find(disp, id);
	अगर (head)
		head->func->vblank_put(head);
पूर्ण

अटल व्योम
nvkm_disp_vblank_init(काष्ठा nvkm_event *event, पूर्णांक type, पूर्णांक id)
अणु
	काष्ठा nvkm_disp *disp = container_of(event, typeof(*disp), vblank);
	काष्ठा nvkm_head *head = nvkm_head_find(disp, id);
	अगर (head)
		head->func->vblank_get(head);
पूर्ण

अटल पूर्णांक
nvkm_disp_vblank_ctor(काष्ठा nvkm_object *object, व्योम *data, u32 size,
		      काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nvkm_disp *disp =
		container_of(notअगरy->event, typeof(*disp), vblank);
	जोड़ अणु
		काष्ठा nvअगर_notअगरy_head_req_v0 v0;
	पूर्ण *req = data;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, req->v0, 0, 0, false))) अणु
		notअगरy->size = माप(काष्ठा nvअगर_notअगरy_head_rep_v0);
		अगर (ret = -ENXIO, req->v0.head <= disp->vblank.index_nr) अणु
			notअगरy->types = 1;
			notअगरy->index = req->v0.head;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_event_func
nvkm_disp_vblank_func = अणु
	.ctor = nvkm_disp_vblank_ctor,
	.init = nvkm_disp_vblank_init,
	.fini = nvkm_disp_vblank_fini,
पूर्ण;

व्योम
nvkm_disp_vblank(काष्ठा nvkm_disp *disp, पूर्णांक head)
अणु
	काष्ठा nvअगर_notअगरy_head_rep_v0 rep = अणुपूर्ण;
	nvkm_event_send(&disp->vblank, 1, head, &rep, माप(rep));
पूर्ण

अटल पूर्णांक
nvkm_disp_hpd_ctor(काष्ठा nvkm_object *object, व्योम *data, u32 size,
		   काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nvkm_disp *disp =
		container_of(notअगरy->event, typeof(*disp), hpd);
	जोड़ अणु
		काष्ठा nvअगर_notअगरy_conn_req_v0 v0;
	पूर्ण *req = data;
	काष्ठा nvkm_outp *outp;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unpack(ret, &data, &size, req->v0, 0, 0, false))) अणु
		notअगरy->size = माप(काष्ठा nvअगर_notअगरy_conn_rep_v0);
		list_क्रम_each_entry(outp, &disp->outp, head) अणु
			अगर (ret = -ENXIO, outp->conn->index == req->v0.conn) अणु
				अगर (ret = -ENODEV, outp->conn->hpd.event) अणु
					notअगरy->types = req->v0.mask;
					notअगरy->index = req->v0.conn;
					ret = 0;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_event_func
nvkm_disp_hpd_func = अणु
	.ctor = nvkm_disp_hpd_ctor
पूर्ण;

पूर्णांक
nvkm_disp_ntfy(काष्ठा nvkm_object *object, u32 type, काष्ठा nvkm_event **event)
अणु
	काष्ठा nvkm_disp *disp = nvkm_disp(object->engine);
	चयन (type) अणु
	हाल NV04_DISP_NTFY_VBLANK:
		*event = &disp->vblank;
		वापस 0;
	हाल NV04_DISP_NTFY_CONN:
		*event = &disp->hpd;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम
nvkm_disp_class_del(काष्ठा nvkm_oproxy *oproxy)
अणु
	काष्ठा nvkm_disp *disp = nvkm_disp(oproxy->base.engine);
	spin_lock(&disp->client.lock);
	अगर (disp->client.object == oproxy)
		disp->client.object = शून्य;
	spin_unlock(&disp->client.lock);
पूर्ण

अटल स्थिर काष्ठा nvkm_oproxy_func
nvkm_disp_class = अणु
	.dtor[1] = nvkm_disp_class_del,
पूर्ण;

अटल पूर्णांक
nvkm_disp_class_new(काष्ठा nvkm_device *device,
		    स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
		    काष्ठा nvkm_object **pobject)
अणु
	स्थिर काष्ठा nvkm_disp_oclass *sclass = oclass->engn;
	काष्ठा nvkm_disp *disp = nvkm_disp(oclass->engine);
	काष्ठा nvkm_oproxy *oproxy;
	पूर्णांक ret;

	ret = nvkm_oproxy_new_(&nvkm_disp_class, oclass, &oproxy);
	अगर (ret)
		वापस ret;
	*pobject = &oproxy->base;

	spin_lock(&disp->client.lock);
	अगर (disp->client.object) अणु
		spin_unlock(&disp->client.lock);
		वापस -EBUSY;
	पूर्ण
	disp->client.object = oproxy;
	spin_unlock(&disp->client.lock);

	वापस sclass->ctor(disp, oclass, data, size, &oproxy->object);
पूर्ण

अटल स्थिर काष्ठा nvkm_device_oclass
nvkm_disp_sclass = अणु
	.ctor = nvkm_disp_class_new,
पूर्ण;

अटल पूर्णांक
nvkm_disp_class_get(काष्ठा nvkm_oclass *oclass, पूर्णांक index,
		    स्थिर काष्ठा nvkm_device_oclass **class)
अणु
	काष्ठा nvkm_disp *disp = nvkm_disp(oclass->engine);
	अगर (index == 0) अणु
		स्थिर काष्ठा nvkm_disp_oclass *root = disp->func->root(disp);
		oclass->base = root->base;
		oclass->engn = root;
		*class = &nvkm_disp_sclass;
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम
nvkm_disp_पूर्णांकr(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_disp *disp = nvkm_disp(engine);
	disp->func->पूर्णांकr(disp);
पूर्ण

अटल पूर्णांक
nvkm_disp_fini(काष्ठा nvkm_engine *engine, bool suspend)
अणु
	काष्ठा nvkm_disp *disp = nvkm_disp(engine);
	काष्ठा nvkm_conn *conn;
	काष्ठा nvkm_outp *outp;

	अगर (disp->func->fini)
		disp->func->fini(disp);

	list_क्रम_each_entry(outp, &disp->outp, head) अणु
		nvkm_outp_fini(outp);
	पूर्ण

	list_क्रम_each_entry(conn, &disp->conn, head) अणु
		nvkm_conn_fini(conn);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_disp_init(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_disp *disp = nvkm_disp(engine);
	काष्ठा nvkm_conn *conn;
	काष्ठा nvkm_outp *outp;
	काष्ठा nvkm_ior *ior;

	list_क्रम_each_entry(conn, &disp->conn, head) अणु
		nvkm_conn_init(conn);
	पूर्ण

	list_क्रम_each_entry(outp, &disp->outp, head) अणु
		nvkm_outp_init(outp);
	पूर्ण

	अगर (disp->func->init) अणु
		पूर्णांक ret = disp->func->init(disp);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Set 'normal' (ie. when it's attached to a head) state क्रम
	 * each output resource to 'fully enabled'.
	 */
	list_क्रम_each_entry(ior, &disp->ior, head) अणु
		ior->func->घातer(ior, true, true, true, true, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_disp_oneinit(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_disp *disp = nvkm_disp(engine);
	काष्ठा nvkm_subdev *subdev = &disp->engine.subdev;
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	काष्ठा nvkm_outp *outp, *outt, *pair;
	काष्ठा nvkm_conn *conn;
	काष्ठा nvkm_head *head;
	काष्ठा nvkm_ior *ior;
	काष्ठा nvbios_connE connE;
	काष्ठा dcb_output dcbE;
	u8  hpd = 0, ver, hdr;
	u32 data;
	पूर्णांक ret, i;

	/* Create output path objects क्रम each VBIOS display path. */
	i = -1;
	जबतक ((data = dcb_outp_parse(bios, ++i, &ver, &hdr, &dcbE))) अणु
		अगर (ver < 0x40) /* No support क्रम chipsets prior to NV50. */
			अवरोध;
		अगर (dcbE.type == DCB_OUTPUT_UNUSED)
			जारी;
		अगर (dcbE.type == DCB_OUTPUT_EOL)
			अवरोध;
		outp = शून्य;

		चयन (dcbE.type) अणु
		हाल DCB_OUTPUT_ANALOG:
		हाल DCB_OUTPUT_TV:
		हाल DCB_OUTPUT_TMDS:
		हाल DCB_OUTPUT_LVDS:
			ret = nvkm_outp_new(disp, i, &dcbE, &outp);
			अवरोध;
		हाल DCB_OUTPUT_DP:
			ret = nvkm_dp_new(disp, i, &dcbE, &outp);
			अवरोध;
		हाल DCB_OUTPUT_WFD:
			/* No support क्रम WFD yet. */
			ret = -ENODEV;
			जारी;
		शेष:
			nvkm_warn(subdev, "dcb %d type %d unknown\n",
				  i, dcbE.type);
			जारी;
		पूर्ण

		अगर (ret) अणु
			अगर (outp) अणु
				अगर (ret != -ENODEV)
					OUTP_ERR(outp, "ctor failed: %d", ret);
				अन्यथा
					OUTP_DBG(outp, "not supported");
				nvkm_outp_del(&outp);
				जारी;
			पूर्ण
			nvkm_error(subdev, "failed to create outp %d\n", i);
			जारी;
		पूर्ण

		list_add_tail(&outp->head, &disp->outp);
		hpd = max(hpd, (u8)(dcbE.connector + 1));
	पूर्ण

	/* Create connector objects based on available output paths. */
	list_क्रम_each_entry_safe(outp, outt, &disp->outp, head) अणु
		/* VBIOS data *should* give us the most useful inक्रमmation. */
		data = nvbios_connEp(bios, outp->info.connector, &ver, &hdr,
				     &connE);

		/* No bios connector data... */
		अगर (!data) अणु
			/* Heuristic: anything with the same ccb index is
			 * considered to be on the same connector, any
			 * output path without an associated ccb entry will
			 * be put on its own connector.
			 */
			पूर्णांक ccb_index = outp->info.i2c_index;
			अगर (ccb_index != 0xf) अणु
				list_क्रम_each_entry(pair, &disp->outp, head) अणु
					अगर (pair->info.i2c_index == ccb_index) अणु
						outp->conn = pair->conn;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			/* Connector shared with another output path. */
			अगर (outp->conn)
				जारी;

			स_रखो(&connE, 0x00, माप(connE));
			connE.type = DCB_CONNECTOR_NONE;
			i = -1;
		पूर्ण अन्यथा अणु
			i = outp->info.connector;
		पूर्ण

		/* Check that we haven't alपढ़ोy created this connector. */
		list_क्रम_each_entry(conn, &disp->conn, head) अणु
			अगर (conn->index == outp->info.connector) अणु
				outp->conn = conn;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (outp->conn)
			जारी;

		/* Apparently we need to create a new one! */
		ret = nvkm_conn_new(disp, i, &connE, &outp->conn);
		अगर (ret) अणु
			nvkm_error(&disp->engine.subdev,
				   "failed to create outp %d conn: %d\n",
				   outp->index, ret);
			nvkm_conn_del(&outp->conn);
			list_del(&outp->head);
			nvkm_outp_del(&outp);
			जारी;
		पूर्ण

		list_add_tail(&outp->conn->head, &disp->conn);
	पूर्ण

	ret = nvkm_event_init(&nvkm_disp_hpd_func, 3, hpd, &disp->hpd);
	अगर (ret)
		वापस ret;

	अगर (disp->func->oneinit) अणु
		ret = disp->func->oneinit(disp);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Enक्रमce identity-mapped SOR assignment क्रम panels, which have
	 * certain bits (ie. backlight controls) wired to a specअगरic SOR.
	 */
	list_क्रम_each_entry(outp, &disp->outp, head) अणु
		अगर (outp->conn->info.type == DCB_CONNECTOR_LVDS ||
		    outp->conn->info.type == DCB_CONNECTOR_eDP) अणु
			ior = nvkm_ior_find(disp, SOR, ffs(outp->info.or) - 1);
			अगर (!WARN_ON(!ior))
				ior->identity = true;
			outp->identity = true;
		पूर्ण
	पूर्ण

	i = 0;
	list_क्रम_each_entry(head, &disp->head, head)
		i = max(i, head->id + 1);

	वापस nvkm_event_init(&nvkm_disp_vblank_func, 1, i, &disp->vblank);
पूर्ण

अटल व्योम *
nvkm_disp_dtor(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_disp *disp = nvkm_disp(engine);
	काष्ठा nvkm_conn *conn;
	काष्ठा nvkm_outp *outp;
	व्योम *data = disp;

	अगर (disp->func->dtor)
		data = disp->func->dtor(disp);

	nvkm_event_fini(&disp->vblank);
	nvkm_event_fini(&disp->hpd);

	जबतक (!list_empty(&disp->conn)) अणु
		conn = list_first_entry(&disp->conn, typeof(*conn), head);
		list_del(&conn->head);
		nvkm_conn_del(&conn);
	पूर्ण

	जबतक (!list_empty(&disp->outp)) अणु
		outp = list_first_entry(&disp->outp, typeof(*outp), head);
		list_del(&outp->head);
		nvkm_outp_del(&outp);
	पूर्ण

	जबतक (!list_empty(&disp->ior)) अणु
		काष्ठा nvkm_ior *ior =
			list_first_entry(&disp->ior, typeof(*ior), head);
		nvkm_ior_del(&ior);
	पूर्ण

	जबतक (!list_empty(&disp->head)) अणु
		काष्ठा nvkm_head *head =
			list_first_entry(&disp->head, typeof(*head), head);
		nvkm_head_del(&head);
	पूर्ण

	वापस data;
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nvkm_disp = अणु
	.dtor = nvkm_disp_dtor,
	.oneinit = nvkm_disp_oneinit,
	.init = nvkm_disp_init,
	.fini = nvkm_disp_fini,
	.पूर्णांकr = nvkm_disp_पूर्णांकr,
	.base.sclass = nvkm_disp_class_get,
पूर्ण;

पूर्णांक
nvkm_disp_ctor(स्थिर काष्ठा nvkm_disp_func *func, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_disp *disp)
अणु
	disp->func = func;
	INIT_LIST_HEAD(&disp->head);
	INIT_LIST_HEAD(&disp->ior);
	INIT_LIST_HEAD(&disp->outp);
	INIT_LIST_HEAD(&disp->conn);
	spin_lock_init(&disp->client.lock);
	वापस nvkm_engine_ctor(&nvkm_disp, device, type, inst, true, &disp->engine);
पूर्ण

पूर्णांक
nvkm_disp_new_(स्थिर काष्ठा nvkm_disp_func *func, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_disp **pdisp)
अणु
	अगर (!(*pdisp = kzalloc(माप(**pdisp), GFP_KERNEL)))
		वापस -ENOMEM;
	वापस nvkm_disp_ctor(func, device, type, inst, *pdisp);
पूर्ण
