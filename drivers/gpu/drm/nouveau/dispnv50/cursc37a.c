<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
 */
#समावेश "curs.h"
#समावेश "atom.h"

#समावेश <nvhw/class/clc37a.h>

अटल पूर्णांक
cursc37a_update(काष्ठा nv50_wndw *wndw, u32 *पूर्णांकerlock)
अणु
	काष्ठा nvअगर_object *user = &wndw->wimm.base.user;
	पूर्णांक ret = nvअगर_chan_रुको(&wndw->wimm, 1);
	अगर (ret == 0)
		NVIF_WR32(user, NVC37A, UPDATE, 0x00000001);
	वापस ret;
पूर्ण

अटल पूर्णांक
cursc37a_poपूर्णांक(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nvअगर_object *user = &wndw->wimm.base.user;
	पूर्णांक ret = nvअगर_chan_रुको(&wndw->wimm, 1);
	अगर (ret == 0) अणु
		NVIF_WR32(user, NVC37A, SET_CURSOR_HOT_SPOT_POINT_OUT(0),
			  NVVAL(NVC37A, SET_CURSOR_HOT_SPOT_POINT_OUT, X, asyw->poपूर्णांक.x) |
			  NVVAL(NVC37A, SET_CURSOR_HOT_SPOT_POINT_OUT, Y, asyw->poपूर्णांक.y));
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nv50_wimm_func
cursc37a = अणु
	.poपूर्णांक = cursc37a_poपूर्णांक,
	.update = cursc37a_update,
पूर्ण;

पूर्णांक
cursc37a_new(काष्ठा nouveau_drm *drm, पूर्णांक head, s32 oclass,
	     काष्ठा nv50_wndw **pwndw)
अणु
	वापस curs507a_new_(&cursc37a, drm, head, oclass,
			     0x00000001 << head, pwndw);
पूर्ण
