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
#समावेश <nvfw/ls.h>

अटल व्योम
nvfw_ls_desc_head(काष्ठा nvkm_subdev *subdev,
		  स्थिर काष्ठा nvfw_ls_desc_head *hdr)
अणु
	अक्षर *date;

	nvkm_debug(subdev, "lsUcodeImgDesc:\n");
	nvkm_debug(subdev, "\tdescriptorSize       : %d\n",
			   hdr->descriptor_size);
	nvkm_debug(subdev, "\timageSize            : %d\n", hdr->image_size);
	nvkm_debug(subdev, "\ttoolsVersion         : 0x%x\n",
			   hdr->tools_version);
	nvkm_debug(subdev, "\tappVersion           : 0x%x\n", hdr->app_version);

	date = kstrndup(hdr->date, माप(hdr->date), GFP_KERNEL);
	nvkm_debug(subdev, "\tdate                 : %s\n", date);
	kमुक्त(date);

	nvkm_debug(subdev, "\tbootloaderStartOffset: 0x%x\n",
			   hdr->bootloader_start_offset);
	nvkm_debug(subdev, "\tbootloaderSize       : 0x%x\n",
			   hdr->bootloader_size);
	nvkm_debug(subdev, "\tbootloaderImemOffset : 0x%x\n",
			   hdr->bootloader_imem_offset);
	nvkm_debug(subdev, "\tbootloaderEntryPoint : 0x%x\n",
			   hdr->bootloader_entry_poपूर्णांक);

	nvkm_debug(subdev, "\tappStartOffset       : 0x%x\n",
			   hdr->app_start_offset);
	nvkm_debug(subdev, "\tappSize              : 0x%x\n", hdr->app_size);
	nvkm_debug(subdev, "\tappImemOffset        : 0x%x\n",
			   hdr->app_imem_offset);
	nvkm_debug(subdev, "\tappImemEntry         : 0x%x\n",
			   hdr->app_imem_entry);
	nvkm_debug(subdev, "\tappDmemOffset        : 0x%x\n",
			   hdr->app_dmem_offset);
	nvkm_debug(subdev, "\tappResidentCodeOffset: 0x%x\n",
			   hdr->app_resident_code_offset);
	nvkm_debug(subdev, "\tappResidentCodeSize  : 0x%x\n",
			   hdr->app_resident_code_size);
	nvkm_debug(subdev, "\tappResidentDataOffset: 0x%x\n",
			   hdr->app_resident_data_offset);
	nvkm_debug(subdev, "\tappResidentDataSize  : 0x%x\n",
			   hdr->app_resident_data_size);
पूर्ण

स्थिर काष्ठा nvfw_ls_desc *
nvfw_ls_desc(काष्ठा nvkm_subdev *subdev, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nvfw_ls_desc *hdr = data;
	पूर्णांक i;

	nvfw_ls_desc_head(subdev, &hdr->head);

	nvkm_debug(subdev, "\tnbOverlays           : %d\n", hdr->nb_overlays);
	क्रम (i = 0; i < ARRAY_SIZE(hdr->load_ovl); i++) अणु
		nvkm_debug(subdev, "\tloadOvl[%d]          : 0x%x %d\n", i,
			   hdr->load_ovl[i].start, hdr->load_ovl[i].size);
	पूर्ण
	nvkm_debug(subdev, "\tcompressed           : %d\n", hdr->compressed);

	वापस hdr;
पूर्ण

स्थिर काष्ठा nvfw_ls_desc_v1 *
nvfw_ls_desc_v1(काष्ठा nvkm_subdev *subdev, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nvfw_ls_desc_v1 *hdr = data;
	पूर्णांक i;

	nvfw_ls_desc_head(subdev, &hdr->head);

	nvkm_debug(subdev, "\tnbImemOverlays       : %d\n",
			   hdr->nb_imem_overlays);
	nvkm_debug(subdev, "\tnbDmemOverlays       : %d\n",
			   hdr->nb_imem_overlays);
	क्रम (i = 0; i < ARRAY_SIZE(hdr->load_ovl); i++) अणु
		nvkm_debug(subdev, "\tloadOvl[%2d]          : 0x%x %d\n", i,
			   hdr->load_ovl[i].start, hdr->load_ovl[i].size);
	पूर्ण
	nvkm_debug(subdev, "\tcompressed           : %d\n", hdr->compressed);

	वापस hdr;
पूर्ण
