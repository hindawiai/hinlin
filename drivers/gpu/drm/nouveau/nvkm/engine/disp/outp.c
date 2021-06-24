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
#समावेश "outp.h"
#समावेश "ior.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/dcb.h>
#समावेश <subdev/i2c.h>

व्योम
nvkm_outp_route(काष्ठा nvkm_disp *disp)
अणु
	काष्ठा nvkm_outp *outp;
	काष्ठा nvkm_ior *ior;

	list_क्रम_each_entry(ior, &disp->ior, head) अणु
		अगर ((outp = ior->arm.outp) && ior->arm.outp != ior->asy.outp) अणु
			OUTP_DBG(outp, "release %s", ior->name);
			अगर (ior->func->route.set)
				ior->func->route.set(outp, शून्य);
			ior->arm.outp = शून्य;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(ior, &disp->ior, head) अणु
		अगर ((outp = ior->asy.outp)) अणु
			OUTP_DBG(outp, "acquire %s", ior->name);
			अगर (ior->asy.outp != ior->arm.outp) अणु
				अगर (ior->func->route.set)
					ior->func->route.set(outp, ior);
				ior->arm.outp = ior->asy.outp;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल क्रमागत nvkm_ior_proto
nvkm_outp_xlat(काष्ठा nvkm_outp *outp, क्रमागत nvkm_ior_type *type)
अणु
	चयन (outp->info.location) अणु
	हाल 0:
		चयन (outp->info.type) अणु
		हाल DCB_OUTPUT_ANALOG: *type = DAC; वापस  CRT;
		हाल DCB_OUTPUT_TV    : *type = DAC; वापस   TV;
		हाल DCB_OUTPUT_TMDS  : *type = SOR; वापस TMDS;
		हाल DCB_OUTPUT_LVDS  : *type = SOR; वापस LVDS;
		हाल DCB_OUTPUT_DP    : *type = SOR; वापस   DP;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 1:
		चयन (outp->info.type) अणु
		हाल DCB_OUTPUT_TMDS: *type = PIOR; वापस TMDS;
		हाल DCB_OUTPUT_DP  : *type = PIOR; वापस TMDS; /* not a bug */
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	WARN_ON(1);
	वापस UNKNOWN;
पूर्ण

व्योम
nvkm_outp_release(काष्ठा nvkm_outp *outp, u8 user)
अणु
	काष्ठा nvkm_ior *ior = outp->ior;
	OUTP_TRACE(outp, "release %02x &= %02x %p", outp->acquired, ~user, ior);
	अगर (ior) अणु
		outp->acquired &= ~user;
		अगर (!outp->acquired) अणु
			अगर (outp->func->release && outp->ior)
				outp->func->release(outp);
			outp->ior->asy.outp = शून्य;
			outp->ior = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
nvkm_outp_acquire_ior(काष्ठा nvkm_outp *outp, u8 user, काष्ठा nvkm_ior *ior)
अणु
	outp->ior = ior;
	outp->ior->asy.outp = outp;
	outp->ior->asy.link = outp->info.sorconf.link;
	outp->acquired |= user;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
nvkm_outp_acquire_hda(काष्ठा nvkm_outp *outp, क्रमागत nvkm_ior_type type,
		      u8 user, bool hda)
अणु
	काष्ठा nvkm_ior *ior;

	/* Failing that, a completely unused OR is the next best thing. */
	list_क्रम_each_entry(ior, &outp->disp->ior, head) अणु
		अगर (!ior->identity && !!ior->func->hda.hpd == hda &&
		    !ior->asy.outp && ior->type == type && !ior->arm.outp &&
		    (ior->func->route.set || ior->id == __ffs(outp->info.or)))
			वापस nvkm_outp_acquire_ior(outp, user, ior);
	पूर्ण

	/* Last resort is to assign an OR that's alपढ़ोy active on HW,
	 * but will be released during the next modeset.
	 */
	list_क्रम_each_entry(ior, &outp->disp->ior, head) अणु
		अगर (!ior->identity && !!ior->func->hda.hpd == hda &&
		    !ior->asy.outp && ior->type == type &&
		    (ior->func->route.set || ior->id == __ffs(outp->info.or)))
			वापस nvkm_outp_acquire_ior(outp, user, ior);
	पूर्ण

	वापस -ENOSPC;
पूर्ण

पूर्णांक
nvkm_outp_acquire(काष्ठा nvkm_outp *outp, u8 user, bool hda)
अणु
	काष्ठा nvkm_ior *ior = outp->ior;
	क्रमागत nvkm_ior_proto proto;
	क्रमागत nvkm_ior_type type;

	OUTP_TRACE(outp, "acquire %02x |= %02x %p", outp->acquired, user, ior);
	अगर (ior) अणु
		outp->acquired |= user;
		वापस 0;
	पूर्ण

	/* Lookup a compatible, and unused, OR to assign to the device. */
	proto = nvkm_outp_xlat(outp, &type);
	अगर (proto == UNKNOWN)
		वापस -ENOSYS;

	/* Deal with panels requiring identity-mapped SOR assignment. */
	अगर (outp->identity) अणु
		ior = nvkm_ior_find(outp->disp, SOR, ffs(outp->info.or) - 1);
		अगर (WARN_ON(!ior))
			वापस -ENOSPC;
		वापस nvkm_outp_acquire_ior(outp, user, ior);
	पूर्ण

	/* First preference is to reuse the OR that is currently armed
	 * on HW, अगर any, in order to prevent unnecessary चयनing.
	 */
	list_क्रम_each_entry(ior, &outp->disp->ior, head) अणु
		अगर (!ior->identity && !ior->asy.outp && ior->arm.outp == outp) अणु
			/*XXX: For various complicated reasons, we can't outright चयन
			 *     the boot-समय OR on the first modeset without some fairly
			 *     invasive changes.
			 *
			 *     The प्रणालीs that were fixed by modअगरying the OR selection
			 *     code to account क्रम HDA support shouldn't regress here as
			 *     the HDA-enabled ORs match the relevant output's pad macro
			 *     index, and the firmware seems to select an OR this way.
			 *
			 *     This warning is to make it obvious अगर that proves wrong.
			 */
			WARN_ON(hda && !ior->func->hda.hpd);
			वापस nvkm_outp_acquire_ior(outp, user, ior);
		पूर्ण
	पूर्ण

	/* If we करोn't need HDA, first try to acquire an OR that doesn't
	 * support it to leave मुक्त the ones that करो.
	 */
	अगर (!hda) अणु
		अगर (!nvkm_outp_acquire_hda(outp, type, user, false))
			वापस 0;

		/* Use a HDA-supporting SOR anyway. */
		वापस nvkm_outp_acquire_hda(outp, type, user, true);
	पूर्ण

	/* We want HDA, try to acquire an OR that supports it. */
	अगर (!nvkm_outp_acquire_hda(outp, type, user, true))
		वापस 0;

	/* There weren't any मुक्त ORs that support HDA, grab one that
	 * करोesn't and at least allow display to work still.
	 */
	वापस nvkm_outp_acquire_hda(outp, type, user, false);
पूर्ण

व्योम
nvkm_outp_fini(काष्ठा nvkm_outp *outp)
अणु
	अगर (outp->func->fini)
		outp->func->fini(outp);
पूर्ण

अटल व्योम
nvkm_outp_init_route(काष्ठा nvkm_outp *outp)
अणु
	काष्ठा nvkm_disp *disp = outp->disp;
	क्रमागत nvkm_ior_proto proto;
	क्रमागत nvkm_ior_type type;
	काष्ठा nvkm_ior *ior;
	पूर्णांक id, link;

	/* Find any OR from the class that is able to support this device. */
	proto = nvkm_outp_xlat(outp, &type);
	अगर (proto == UNKNOWN)
		वापस;

	ior = nvkm_ior_find(disp, type, -1);
	अगर (!ior) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	/* Determine the specअगरic OR, अगर any, this device is attached to. */
	अगर (ior->func->route.get) अणु
		id = ior->func->route.get(outp, &link);
		अगर (id < 0) अणु
			OUTP_DBG(outp, "no route");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Prior to DCB 4.1, this is hardwired like so. */
		id   = ffs(outp->info.or) - 1;
		link = (ior->type == SOR) ? outp->info.sorconf.link : 0;
	पूर्ण

	ior = nvkm_ior_find(disp, type, id);
	अगर (!ior) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	/* Determine अगर the OR is alपढ़ोy configured क्रम this device. */
	ior->func->state(ior, &ior->arm);
	अगर (!ior->arm.head || ior->arm.proto != proto) अणु
		OUTP_DBG(outp, "no heads (%x %d %d)", ior->arm.head,
			 ior->arm.proto, proto);
		वापस;
	पूर्ण

	OUTP_DBG(outp, "on %s link %x", ior->name, ior->arm.link);
	ior->arm.outp = outp;
पूर्ण

व्योम
nvkm_outp_init(काष्ठा nvkm_outp *outp)
अणु
	nvkm_outp_init_route(outp);
	अगर (outp->func->init)
		outp->func->init(outp);
पूर्ण

व्योम
nvkm_outp_del(काष्ठा nvkm_outp **poutp)
अणु
	काष्ठा nvkm_outp *outp = *poutp;
	अगर (outp && !WARN_ON(!outp->func)) अणु
		अगर (outp->func->dtor)
			*poutp = outp->func->dtor(outp);
		kमुक्त(*poutp);
		*poutp = शून्य;
	पूर्ण
पूर्ण

पूर्णांक
nvkm_outp_ctor(स्थिर काष्ठा nvkm_outp_func *func, काष्ठा nvkm_disp *disp,
	       पूर्णांक index, काष्ठा dcb_output *dcbE, काष्ठा nvkm_outp *outp)
अणु
	काष्ठा nvkm_i2c *i2c = disp->engine.subdev.device->i2c;
	क्रमागत nvkm_ior_proto proto;
	क्रमागत nvkm_ior_type type;

	outp->func = func;
	outp->disp = disp;
	outp->index = index;
	outp->info = *dcbE;
	outp->i2c = nvkm_i2c_bus_find(i2c, dcbE->i2c_index);

	OUTP_DBG(outp, "type %02x loc %d or %d link %d con %x "
		       "edid %x bus %d head %x",
		 outp->info.type, outp->info.location, outp->info.or,
		 outp->info.type >= 2 ? outp->info.sorconf.link : 0,
		 outp->info.connector, outp->info.i2c_index,
		 outp->info.bus, outp->info.heads);

	/* Cull output paths we can't map to an output resource. */
	proto = nvkm_outp_xlat(outp, &type);
	अगर (proto == UNKNOWN)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_outp_func
nvkm_outp = अणु
पूर्ण;

पूर्णांक
nvkm_outp_new(काष्ठा nvkm_disp *disp, पूर्णांक index, काष्ठा dcb_output *dcbE,
	      काष्ठा nvkm_outp **poutp)
अणु
	अगर (!(*poutp = kzalloc(माप(**poutp), GFP_KERNEL)))
		वापस -ENOMEM;
	वापस nvkm_outp_ctor(&nvkm_outp, disp, index, dcbE, *poutp);
पूर्ण
