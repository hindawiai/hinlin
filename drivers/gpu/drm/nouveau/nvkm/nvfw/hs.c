<शैली गुरु>
/*
 * Copyright 2019 Red Hat Inc.
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
#समावेश <core/subdev.h>
#समावेश <nvfw/hs.h>

स्थिर काष्ठा nvfw_hs_header *
nvfw_hs_header(काष्ठा nvkm_subdev *subdev, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nvfw_hs_header *hdr = data;
	nvkm_debug(subdev, "hsHeader:\n");
	nvkm_debug(subdev, "\tsigDbgOffset     : 0x%x\n", hdr->sig_dbg_offset);
	nvkm_debug(subdev, "\tsigDbgSize       : 0x%x\n", hdr->sig_dbg_size);
	nvkm_debug(subdev, "\tsigProdOffset    : 0x%x\n", hdr->sig_prod_offset);
	nvkm_debug(subdev, "\tsigProdSize      : 0x%x\n", hdr->sig_prod_size);
	nvkm_debug(subdev, "\tpatchLoc         : 0x%x\n", hdr->patch_loc);
	nvkm_debug(subdev, "\tpatchSig         : 0x%x\n", hdr->patch_sig);
	nvkm_debug(subdev, "\thdrOffset        : 0x%x\n", hdr->hdr_offset);
	nvkm_debug(subdev, "\thdrSize          : 0x%x\n", hdr->hdr_size);
	वापस hdr;
पूर्ण

स्थिर काष्ठा nvfw_hs_load_header *
nvfw_hs_load_header(काष्ठा nvkm_subdev *subdev, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nvfw_hs_load_header *hdr = data;
	पूर्णांक i;

	nvkm_debug(subdev, "hsLoadHeader:\n");
	nvkm_debug(subdev, "\tnonSecCodeOff    : 0x%x\n",
			   hdr->non_sec_code_off);
	nvkm_debug(subdev, "\tnonSecCodeSize   : 0x%x\n",
			   hdr->non_sec_code_size);
	nvkm_debug(subdev, "\tdataDmaBase      : 0x%x\n", hdr->data_dma_base);
	nvkm_debug(subdev, "\tdataSize         : 0x%x\n", hdr->data_size);
	nvkm_debug(subdev, "\tnumApps          : 0x%x\n", hdr->num_apps);
	क्रम (i = 0; i < hdr->num_apps; i++) अणु
		nvkm_debug(subdev,
			   "\tApp[%d]           : offset 0x%x size 0x%x\n", i,
			   hdr->apps[(i * 2) + 0], hdr->apps[(i * 2) + 1]);
	पूर्ण

	वापस hdr;
पूर्ण
