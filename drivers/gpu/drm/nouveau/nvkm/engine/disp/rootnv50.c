<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
#समावेश "rootnv50.h"
#समावेश "channv50.h"
#समावेश "dp.h"
#समावेश "head.h"
#समावेश "ior.h"

#समावेश <core/client.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl5070.h>
#समावेश <nvअगर/unpack.h>

अटल पूर्णांक
nv50_disp_root_mthd_(काष्ठा nvkm_object *object, u32 mthd, व्योम *data, u32 size)
अणु
	जोड़ अणु
		काष्ठा nv50_disp_mthd_v0 v0;
		काष्ठा nv50_disp_mthd_v1 v1;
	पूर्ण *args = data;
	काष्ठा nv50_disp_root *root = nv50_disp_root(object);
	काष्ठा nv50_disp *disp = root->disp;
	काष्ठा nvkm_outp *temp, *outp = शून्य;
	काष्ठा nvkm_head *head;
	u16 type, mask = 0;
	पूर्णांक hidx, ret = -ENOSYS;

	अगर (mthd != NV50_DISP_MTHD)
		वापस -EINVAL;

	nvअगर_ioctl(object, "disp mthd size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
		nvअगर_ioctl(object, "disp mthd vers %d mthd %02x head %d\n",
			   args->v0.version, args->v0.method, args->v0.head);
		mthd = args->v0.method;
		hidx = args->v0.head;
	पूर्ण अन्यथा
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v1, 1, 1, true))) अणु
		nvअगर_ioctl(object, "disp mthd vers %d mthd %02x "
				   "type %04x mask %04x\n",
			   args->v1.version, args->v1.method,
			   args->v1.hasht, args->v1.hashm);
		mthd = args->v1.method;
		type = args->v1.hasht;
		mask = args->v1.hashm;
		hidx = ffs((mask >> 8) & 0x0f) - 1;
	पूर्ण अन्यथा
		वापस ret;

	अगर (!(head = nvkm_head_find(&disp->base, hidx)))
		वापस -ENXIO;

	अगर (mask) अणु
		list_क्रम_each_entry(temp, &disp->base.outp, head) अणु
			अगर ((temp->info.hasht         == type) &&
			    (temp->info.hashm & mask) == mask) अणु
				outp = temp;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (outp == शून्य)
			वापस -ENXIO;
	पूर्ण

	चयन (mthd) अणु
	हाल NV50_DISP_SCANOUTPOS: अणु
		वापस nvkm_head_mthd_scanoutpos(object, head, data, size);
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	चयन (mthd * !!outp) अणु
	हाल NV50_DISP_MTHD_V1_ACQUIRE: अणु
		जोड़ अणु
			काष्ठा nv50_disp_acquire_v0 v0;
		पूर्ण *args = data;
		पूर्णांक ret = -ENOSYS;
		अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
			ret = nvkm_outp_acquire(outp, NVKM_OUTP_USER, args->v0.hda);
			अगर (ret == 0) अणु
				args->v0.or = outp->ior->id;
				args->v0.link = outp->ior->asy.link;
			पूर्ण
		पूर्ण
		वापस ret;
	पूर्ण
		अवरोध;
	हाल NV50_DISP_MTHD_V1_RELEASE:
		nvkm_outp_release(outp, NVKM_OUTP_USER);
		वापस 0;
	हाल NV50_DISP_MTHD_V1_DAC_LOAD: अणु
		जोड़ अणु
			काष्ठा nv50_disp_dac_load_v0 v0;
		पूर्ण *args = data;
		पूर्णांक ret = -ENOSYS;
		अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
			अगर (args->v0.data & 0xfff00000)
				वापस -EINVAL;
			ret = nvkm_outp_acquire(outp, NVKM_OUTP_PRIV, false);
			अगर (ret)
				वापस ret;
			ret = outp->ior->func->sense(outp->ior, args->v0.data);
			nvkm_outp_release(outp, NVKM_OUTP_PRIV);
			अगर (ret < 0)
				वापस ret;
			args->v0.load = ret;
			वापस 0;
		पूर्ण अन्यथा
			वापस ret;
	पूर्ण
		अवरोध;
	हाल NV50_DISP_MTHD_V1_SOR_HDA_ELD: अणु
		जोड़ अणु
			काष्ठा nv50_disp_sor_hda_eld_v0 v0;
		पूर्ण *args = data;
		काष्ठा nvkm_ior *ior = outp->ior;
		पूर्णांक ret = -ENOSYS;

		nvअगर_ioctl(object, "disp sor hda eld size %d\n", size);
		अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
			nvअगर_ioctl(object, "disp sor hda eld vers %d\n",
				   args->v0.version);
			अगर (size > 0x60)
				वापस -E2BIG;
		पूर्ण अन्यथा
			वापस ret;

		अगर (!ior->func->hda.hpd)
			वापस -ENODEV;

		अगर (size && args->v0.data[0]) अणु
			अगर (outp->info.type == DCB_OUTPUT_DP)
				ior->func->dp.audio(ior, hidx, true);
			ior->func->hda.hpd(ior, hidx, true);
			ior->func->hda.eld(ior, hidx, data, size);
		पूर्ण अन्यथा अणु
			अगर (outp->info.type == DCB_OUTPUT_DP)
				ior->func->dp.audio(ior, hidx, false);
			ior->func->hda.hpd(ior, hidx, false);
		पूर्ण

		वापस 0;
	पूर्ण
		अवरोध;
	हाल NV50_DISP_MTHD_V1_SOR_HDMI_PWR: अणु
		जोड़ अणु
			काष्ठा nv50_disp_sor_hdmi_pwr_v0 v0;
		पूर्ण *args = data;
		u8 *venकरोr, venकरोr_size;
		u8 *avi, avi_size;
		पूर्णांक ret = -ENOSYS;

		nvअगर_ioctl(object, "disp sor hdmi ctrl size %d\n", size);
		अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, true))) अणु
			nvअगर_ioctl(object, "disp sor hdmi ctrl vers %d state %d "
					   "max_ac_packet %d rekey %d scdc %d\n",
				   args->v0.version, args->v0.state,
				   args->v0.max_ac_packet, args->v0.rekey,
				   args->v0.scdc);
			अगर (args->v0.max_ac_packet > 0x1f || args->v0.rekey > 0x7f)
				वापस -EINVAL;
			अगर ((args->v0.avi_infoframe_length
			     + args->v0.venकरोr_infoframe_length) > size)
				वापस -EINVAL;
			अन्यथा
			अगर ((args->v0.avi_infoframe_length
			     + args->v0.venकरोr_infoframe_length) < size)
				वापस -E2BIG;
			avi = data;
			avi_size = args->v0.avi_infoframe_length;
			venकरोr = avi + avi_size;
			venकरोr_size = args->v0.venकरोr_infoframe_length;
		पूर्ण अन्यथा
			वापस ret;

		अगर (!outp->ior->func->hdmi.ctrl)
			वापस -ENODEV;

		outp->ior->func->hdmi.ctrl(outp->ior, hidx, args->v0.state,
					   args->v0.max_ac_packet,
					   args->v0.rekey, avi, avi_size,
					   venकरोr, venकरोr_size);

		अगर (outp->ior->func->hdmi.scdc)
			outp->ior->func->hdmi.scdc(outp->ior, args->v0.scdc);

		वापस 0;
	पूर्ण
		अवरोध;
	हाल NV50_DISP_MTHD_V1_SOR_LVDS_SCRIPT: अणु
		जोड़ अणु
			काष्ठा nv50_disp_sor_lvds_script_v0 v0;
		पूर्ण *args = data;
		पूर्णांक ret = -ENOSYS;
		nvअगर_ioctl(object, "disp sor lvds script size %d\n", size);
		अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
			nvअगर_ioctl(object, "disp sor lvds script "
					   "vers %d name %04x\n",
				   args->v0.version, args->v0.script);
			disp->sor.lvdsconf = args->v0.script;
			वापस 0;
		पूर्ण अन्यथा
			वापस ret;
	पूर्ण
		अवरोध;
	हाल NV50_DISP_MTHD_V1_SOR_DP_MST_LINK: अणु
		काष्ठा nvkm_dp *dp = nvkm_dp(outp);
		जोड़ अणु
			काष्ठा nv50_disp_sor_dp_mst_link_v0 v0;
		पूर्ण *args = data;
		पूर्णांक ret = -ENOSYS;
		nvअगर_ioctl(object, "disp sor dp mst link size %d\n", size);
		अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
			nvअगर_ioctl(object, "disp sor dp mst link vers %d state %d\n",
				   args->v0.version, args->v0.state);
			dp->lt.mst = !!args->v0.state;
			वापस 0;
		पूर्ण अन्यथा
			वापस ret;
	पूर्ण
		अवरोध;
	हाल NV50_DISP_MTHD_V1_SOR_DP_MST_VCPI: अणु
		जोड़ अणु
			काष्ठा nv50_disp_sor_dp_mst_vcpi_v0 v0;
		पूर्ण *args = data;
		पूर्णांक ret = -ENOSYS;
		nvअगर_ioctl(object, "disp sor dp mst vcpi size %d\n", size);
		अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
			nvअगर_ioctl(object, "disp sor dp mst vcpi vers %d "
					   "slot %02x/%02x pbn %04x/%04x\n",
				   args->v0.version, args->v0.start_slot,
				   args->v0.num_slots, args->v0.pbn,
				   args->v0.aligned_pbn);
			अगर (!outp->ior->func->dp.vcpi)
				वापस -ENODEV;
			outp->ior->func->dp.vcpi(outp->ior, hidx,
						 args->v0.start_slot,
						 args->v0.num_slots,
						 args->v0.pbn,
						 args->v0.aligned_pbn);
			वापस 0;
		पूर्ण अन्यथा
			वापस ret;
	पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nv50_disp_root_child_new_(स्थिर काष्ठा nvkm_oclass *oclass,
			  व्योम *argv, u32 argc, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv50_disp *disp = nv50_disp_root(oclass->parent)->disp;
	स्थिर काष्ठा nv50_disp_user *user = oclass->priv;
	वापस user->ctor(oclass, argv, argc, disp, pobject);
पूर्ण

अटल पूर्णांक
nv50_disp_root_child_get_(काष्ठा nvkm_object *object, पूर्णांक index,
			  काष्ठा nvkm_oclass *sclass)
अणु
	काष्ठा nv50_disp_root *root = nv50_disp_root(object);

	अगर (root->func->user[index].ctor) अणु
		sclass->base = root->func->user[index].base;
		sclass->priv = root->func->user + index;
		sclass->ctor = nv50_disp_root_child_new_;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम *
nv50_disp_root_dtor_(काष्ठा nvkm_object *object)
अणु
	काष्ठा nv50_disp_root *root = nv50_disp_root(object);
	वापस root;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nv50_disp_root_ = अणु
	.dtor = nv50_disp_root_dtor_,
	.mthd = nv50_disp_root_mthd_,
	.ntfy = nvkm_disp_ntfy,
	.sclass = nv50_disp_root_child_get_,
पूर्ण;

पूर्णांक
nv50_disp_root_new_(स्थिर काष्ठा nv50_disp_root_func *func,
		    काष्ठा nvkm_disp *base, स्थिर काष्ठा nvkm_oclass *oclass,
		    व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(base);
	काष्ठा nv50_disp_root *root;

	अगर (!(root = kzalloc(माप(*root), GFP_KERNEL)))
		वापस -ENOMEM;
	*pobject = &root->object;

	nvkm_object_ctor(&nv50_disp_root_, oclass, &root->object);
	root->func = func;
	root->disp = disp;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nv50_disp_root_func
nv50_disp_root = अणु
	.user = अणु
		अणुअणु0,0,NV50_DISP_CURSOR             पूर्ण, nv50_disp_curs_new पूर्ण,
		अणुअणु0,0,NV50_DISP_OVERLAY            पूर्ण, nv50_disp_oimm_new पूर्ण,
		अणुअणु0,0,NV50_DISP_BASE_CHANNEL_DMA   पूर्ण, nv50_disp_base_new पूर्ण,
		अणुअणु0,0,NV50_DISP_CORE_CHANNEL_DMA   पूर्ण, nv50_disp_core_new पूर्ण,
		अणुअणु0,0,NV50_DISP_OVERLAY_CHANNEL_DMAपूर्ण, nv50_disp_ovly_new पूर्ण,
		अणुपूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक
nv50_disp_root_new(काष्ठा nvkm_disp *disp, स्थिर काष्ठा nvkm_oclass *oclass,
		   व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	वापस nv50_disp_root_new_(&nv50_disp_root, disp, oclass,
				   data, size, pobject);
पूर्ण

स्थिर काष्ठा nvkm_disp_oclass
nv50_disp_root_oclass = अणु
	.base.oclass = NV50_DISP,
	.base.minver = -1,
	.base.maxver = -1,
	.ctor = nv50_disp_root_new,
पूर्ण;
