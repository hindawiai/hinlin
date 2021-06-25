<शैली गुरु>
/*
 * Copyright 2011 Red Hat Inc.
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
#समावेश "mxms.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/conn.h>
#समावेश <subdev/bios/dcb.h>
#समावेश <subdev/bios/mxm.h>

काष्ठा context अणु
	u32 *outp;
	काष्ठा mxms_odev desc;
पूर्ण;

अटल bool
mxm_match_पंचांगds_partner(काष्ठा nvkm_mxm *mxm, u8 *data, व्योम *info)
अणु
	काष्ठा context *ctx = info;
	काष्ठा mxms_odev desc;

	mxms_output_device(mxm, data, &desc);
	अगर (desc.outp_type == 2 &&
	    desc.dig_conn == ctx->desc.dig_conn)
		वापस false;
	वापस true;
पूर्ण

अटल bool
mxm_match_dcb(काष्ठा nvkm_mxm *mxm, u8 *data, व्योम *info)
अणु
	काष्ठा nvkm_bios *bios = mxm->subdev.device->bios;
	काष्ठा context *ctx = info;
	u64 desc = *(u64 *)data;

	mxms_output_device(mxm, data, &ctx->desc);

	/* match dcb encoder type to mxm-ods device type */
	अगर ((ctx->outp[0] & 0x0000000f) != ctx->desc.outp_type)
		वापस true;

	/* digital output, have some extra stuff to match here, there's a
	 * table in the vbios that provides a mapping from the mxm digital
	 * connection क्रमागत values to SOR/link
	 */
	अगर ((desc & 0x00000000000000f0) >= 0x20) अणु
		/* check against sor index */
		u8 link = mxm_sor_map(bios, ctx->desc.dig_conn);
		अगर ((ctx->outp[0] & 0x0f000000) != (link & 0x0f) << 24)
			वापस true;

		/* check dcb entry has a compatible link field */
		link = (link & 0x30) >> 4;
		अगर ((link & ((ctx->outp[1] & 0x00000030) >> 4)) != link)
			वापस true;
	पूर्ण

	/* mark this descriptor accounted क्रम by setting invalid device type,
	 * except of course some manufactures करोn't follow specs properly and
	 * we need to aव्योम समाप्तing off the TMDS function on DP connectors
	 * अगर MXM-SIS is missing an entry क्रम it.
	 */
	data[0] &= ~0xf0;
	अगर (ctx->desc.outp_type == 6 && ctx->desc.conn_type == 6 &&
	    mxms_क्रमeach(mxm, 0x01, mxm_match_पंचांगds_partner, ctx)) अणु
		data[0] |= 0x20; /* modअगरy descriptor to match TMDS now */
	पूर्ण अन्यथा अणु
		data[0] |= 0xf0;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
mxm_dcb_sanitise_entry(काष्ठा nvkm_bios *bios, व्योम *data, पूर्णांक idx, u16 pdcb)
अणु
	काष्ठा nvkm_mxm *mxm = data;
	काष्ठा context ctx = अणु .outp = (u32 *)(bios->data + pdcb) पूर्ण;
	u8 type, i2cidx, link, ver, len;
	u8 *conn;

	/* look क्रम an output device काष्ठाure that matches this dcb entry.
	 * अगर one isn't found, disable it.
	 */
	अगर (mxms_क्रमeach(mxm, 0x01, mxm_match_dcb, &ctx)) अणु
		nvkm_debug(&mxm->subdev, "disable %d: %08x %08x\n",
			   idx, ctx.outp[0], ctx.outp[1]);
		ctx.outp[0] |= 0x0000000f;
		वापस 0;
	पूर्ण

	/* modअगरy the output's ddc/aux port, there's a poपूर्णांकer to a table
	 * with the mapping from mxm ddc/aux port to dcb i2c_index in the
	 * vbios mxm table
	 */
	i2cidx = mxm_ddc_map(bios, ctx.desc.ddc_port);
	अगर ((ctx.outp[0] & 0x0000000f) != DCB_OUTPUT_DP)
		i2cidx = (i2cidx & 0x0f) << 4;
	अन्यथा
		i2cidx = (i2cidx & 0xf0);

	अगर (i2cidx != 0xf0) अणु
		ctx.outp[0] &= ~0x000000f0;
		ctx.outp[0] |= i2cidx;
	पूर्ण

	/* override dcb sorconf.link, based on what mxm data says */
	चयन (ctx.desc.outp_type) अणु
	हाल 0x00: /* Analog CRT */
	हाल 0x01: /* Analog TV/HDTV */
		अवरोध;
	शेष:
		link = mxm_sor_map(bios, ctx.desc.dig_conn) & 0x30;
		ctx.outp[1] &= ~0x00000030;
		ctx.outp[1] |= link;
		अवरोध;
	पूर्ण

	/* we may need to fixup various other vbios tables based on what
	 * the descriptor says the connector type should be.
	 *
	 * in a lot of हालs, the vbios tables will claim DVI-I is possible,
	 * and the mxm data says the connector is really HDMI.  another
	 * common example is DP->eDP.
	 */
	conn  = bios->data;
	conn += nvbios_connEe(bios, (ctx.outp[0] & 0x0000f000) >> 12, &ver, &len);
	type  = conn[0];
	चयन (ctx.desc.conn_type) अणु
	हाल 0x01: /* LVDS */
		ctx.outp[1] |= 0x00000004; /* use_घातer_scripts */
		/* XXX: modअगरy शेष link width in LVDS table */
		अवरोध;
	हाल 0x02: /* HDMI */
		type = DCB_CONNECTOR_HDMI_1;
		अवरोध;
	हाल 0x03: /* DVI-D */
		type = DCB_CONNECTOR_DVI_D;
		अवरोध;
	हाल 0x0e: /* eDP, falls through to DPपूर्णांक */
		ctx.outp[1] |= 0x00010000;
		fallthrough;
	हाल 0x07: /* DP पूर्णांकernal, wtf is this?? HP8670w */
		ctx.outp[1] |= 0x00000004; /* use_घातer_scripts? */
		type = DCB_CONNECTOR_eDP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (mxms_version(mxm) >= 0x0300)
		conn[0] = type;

	वापस 0;
पूर्ण

अटल bool
mxm_show_unmatched(काष्ठा nvkm_mxm *mxm, u8 *data, व्योम *info)
अणु
	काष्ठा nvkm_subdev *subdev = &mxm->subdev;
	u64 desc = *(u64 *)data;
	अगर ((desc & 0xf0) != 0xf0)
		nvkm_info(subdev, "unmatched output device %016llx\n", desc);
	वापस true;
पूर्ण

अटल व्योम
mxm_dcb_sanitise(काष्ठा nvkm_mxm *mxm)
अणु
	काष्ठा nvkm_subdev *subdev = &mxm->subdev;
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	u8  ver, hdr, cnt, len;
	u16 dcb = dcb_table(bios, &ver, &hdr, &cnt, &len);
	अगर (dcb == 0x0000 || (ver != 0x40 && ver != 0x41)) अणु
		nvkm_warn(subdev, "unsupported DCB version\n");
		वापस;
	पूर्ण

	dcb_outp_क्रमeach(bios, mxm, mxm_dcb_sanitise_entry);
	mxms_क्रमeach(mxm, 0x01, mxm_show_unmatched, शून्य);
पूर्ण

पूर्णांक
nv50_mxm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_subdev **pmxm)
अणु
	काष्ठा nvkm_mxm *mxm;
	पूर्णांक ret;

	ret = nvkm_mxm_new_(device, type, inst, &mxm);
	अगर (mxm)
		*pmxm = &mxm->subdev;
	अगर (ret)
		वापस ret;

	अगर (mxm->action & MXM_SANITISE_DCB)
		mxm_dcb_sanitise(mxm);

	वापस 0;
पूर्ण
