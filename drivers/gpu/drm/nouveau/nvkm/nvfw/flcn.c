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
#समावेश <nvfw/flcn.h>

व्योम
loader_config_dump(काष्ठा nvkm_subdev *subdev, स्थिर काष्ठा loader_config *hdr)
अणु
	nvkm_debug(subdev, "loaderConfig\n");
	nvkm_debug(subdev, "\tdmaIdx        : %d\n", hdr->dma_idx);
	nvkm_debug(subdev, "\tcodeDmaBase   : 0x%xx\n", hdr->code_dma_base);
	nvkm_debug(subdev, "\tcodeSizeTotal : 0x%x\n", hdr->code_माप_प्रकारotal);
	nvkm_debug(subdev, "\tcodeSizeToLoad: 0x%x\n", hdr->code_माप_प्रकारo_load);
	nvkm_debug(subdev, "\tcodeEntryPoint: 0x%x\n", hdr->code_entry_poपूर्णांक);
	nvkm_debug(subdev, "\tdataDmaBase   : 0x%x\n", hdr->data_dma_base);
	nvkm_debug(subdev, "\tdataSize      : 0x%x\n", hdr->data_size);
	nvkm_debug(subdev, "\toverlayDmaBase: 0x%x\n", hdr->overlay_dma_base);
	nvkm_debug(subdev, "\targc          : 0x%08x\n", hdr->argc);
	nvkm_debug(subdev, "\targv          : 0x%08x\n", hdr->argv);
	nvkm_debug(subdev, "\tcodeDmaBase1  : 0x%x\n", hdr->code_dma_base1);
	nvkm_debug(subdev, "\tdataDmaBase1  : 0x%x\n", hdr->data_dma_base1);
	nvkm_debug(subdev, "\tovlyDmaBase1  : 0x%x\n", hdr->overlay_dma_base1);
पूर्ण

व्योम
loader_config_v1_dump(काष्ठा nvkm_subdev *subdev,
		      स्थिर काष्ठा loader_config_v1 *hdr)
अणु
	nvkm_debug(subdev, "loaderConfig\n");
	nvkm_debug(subdev, "\treserved      : 0x%08x\n", hdr->reserved);
	nvkm_debug(subdev, "\tdmaIdx        : %d\n", hdr->dma_idx);
	nvkm_debug(subdev, "\tcodeDmaBase   : 0x%llxx\n", hdr->code_dma_base);
	nvkm_debug(subdev, "\tcodeSizeTotal : 0x%x\n", hdr->code_माप_प्रकारotal);
	nvkm_debug(subdev, "\tcodeSizeToLoad: 0x%x\n", hdr->code_माप_प्रकारo_load);
	nvkm_debug(subdev, "\tcodeEntryPoint: 0x%x\n", hdr->code_entry_poपूर्णांक);
	nvkm_debug(subdev, "\tdataDmaBase   : 0x%llx\n", hdr->data_dma_base);
	nvkm_debug(subdev, "\tdataSize      : 0x%x\n", hdr->data_size);
	nvkm_debug(subdev, "\toverlayDmaBase: 0x%llx\n", hdr->overlay_dma_base);
	nvkm_debug(subdev, "\targc          : 0x%08x\n", hdr->argc);
	nvkm_debug(subdev, "\targv          : 0x%08x\n", hdr->argv);
पूर्ण

व्योम
flcn_bl_dmem_desc_dump(काष्ठा nvkm_subdev *subdev,
		       स्थिर काष्ठा flcn_bl_dmem_desc *hdr)
अणु
	nvkm_debug(subdev, "flcnBlDmemDesc\n");
	nvkm_debug(subdev, "\treserved      : 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   hdr->reserved[0], hdr->reserved[1], hdr->reserved[2],
		   hdr->reserved[3]);
	nvkm_debug(subdev, "\tsignature     : 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   hdr->signature[0], hdr->signature[1], hdr->signature[2],
		   hdr->signature[3]);
	nvkm_debug(subdev, "\tctxDma        : %d\n", hdr->ctx_dma);
	nvkm_debug(subdev, "\tcodeDmaBase   : 0x%x\n", hdr->code_dma_base);
	nvkm_debug(subdev, "\tnonSecCodeOff : 0x%x\n", hdr->non_sec_code_off);
	nvkm_debug(subdev, "\tnonSecCodeSize: 0x%x\n", hdr->non_sec_code_size);
	nvkm_debug(subdev, "\tsecCodeOff    : 0x%x\n", hdr->sec_code_off);
	nvkm_debug(subdev, "\tsecCodeSize   : 0x%x\n", hdr->sec_code_size);
	nvkm_debug(subdev, "\tcodeEntryPoint: 0x%x\n", hdr->code_entry_poपूर्णांक);
	nvkm_debug(subdev, "\tdataDmaBase   : 0x%x\n", hdr->data_dma_base);
	nvkm_debug(subdev, "\tdataSize      : 0x%x\n", hdr->data_size);
	nvkm_debug(subdev, "\tcodeDmaBase1  : 0x%x\n", hdr->code_dma_base1);
	nvkm_debug(subdev, "\tdataDmaBase1  : 0x%x\n", hdr->data_dma_base1);
पूर्ण

व्योम
flcn_bl_dmem_desc_v1_dump(काष्ठा nvkm_subdev *subdev,
			  स्थिर काष्ठा flcn_bl_dmem_desc_v1 *hdr)
अणु
	nvkm_debug(subdev, "flcnBlDmemDesc\n");
	nvkm_debug(subdev, "\treserved      : 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   hdr->reserved[0], hdr->reserved[1], hdr->reserved[2],
		   hdr->reserved[3]);
	nvkm_debug(subdev, "\tsignature     : 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   hdr->signature[0], hdr->signature[1], hdr->signature[2],
		   hdr->signature[3]);
	nvkm_debug(subdev, "\tctxDma        : %d\n", hdr->ctx_dma);
	nvkm_debug(subdev, "\tcodeDmaBase   : 0x%llx\n", hdr->code_dma_base);
	nvkm_debug(subdev, "\tnonSecCodeOff : 0x%x\n", hdr->non_sec_code_off);
	nvkm_debug(subdev, "\tnonSecCodeSize: 0x%x\n", hdr->non_sec_code_size);
	nvkm_debug(subdev, "\tsecCodeOff    : 0x%x\n", hdr->sec_code_off);
	nvkm_debug(subdev, "\tsecCodeSize   : 0x%x\n", hdr->sec_code_size);
	nvkm_debug(subdev, "\tcodeEntryPoint: 0x%x\n", hdr->code_entry_poपूर्णांक);
	nvkm_debug(subdev, "\tdataDmaBase   : 0x%llx\n", hdr->data_dma_base);
	nvkm_debug(subdev, "\tdataSize      : 0x%x\n", hdr->data_size);
पूर्ण

व्योम
flcn_bl_dmem_desc_v2_dump(काष्ठा nvkm_subdev *subdev,
			  स्थिर काष्ठा flcn_bl_dmem_desc_v2 *hdr)
अणु
	flcn_bl_dmem_desc_v1_dump(subdev, (व्योम *)hdr);
	nvkm_debug(subdev, "\targc          : 0x%08x\n", hdr->argc);
	nvkm_debug(subdev, "\targv          : 0x%08x\n", hdr->argv);
पूर्ण
