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
#समावेश <nvfw/acr.h>

व्योम
wpr_header_dump(काष्ठा nvkm_subdev *subdev, स्थिर काष्ठा wpr_header *hdr)
अणु
	nvkm_debug(subdev, "wprHeader\n");
	nvkm_debug(subdev, "\tfalconID      : %d\n", hdr->falcon_id);
	nvkm_debug(subdev, "\tlsbOffset     : 0x%x\n", hdr->lsb_offset);
	nvkm_debug(subdev, "\tbootstrapOwner: %d\n", hdr->bootstrap_owner);
	nvkm_debug(subdev, "\tlazyBootstrap : %d\n", hdr->lazy_bootstrap);
	nvkm_debug(subdev, "\tstatus        : %d\n", hdr->status);
पूर्ण

व्योम
wpr_header_v1_dump(काष्ठा nvkm_subdev *subdev, स्थिर काष्ठा wpr_header_v1 *hdr)
अणु
	nvkm_debug(subdev, "wprHeader\n");
	nvkm_debug(subdev, "\tfalconID      : %d\n", hdr->falcon_id);
	nvkm_debug(subdev, "\tlsbOffset     : 0x%x\n", hdr->lsb_offset);
	nvkm_debug(subdev, "\tbootstrapOwner: %d\n", hdr->bootstrap_owner);
	nvkm_debug(subdev, "\tlazyBootstrap : %d\n", hdr->lazy_bootstrap);
	nvkm_debug(subdev, "\tbinVersion    : %d\n", hdr->bin_version);
	nvkm_debug(subdev, "\tstatus        : %d\n", hdr->status);
पूर्ण

अटल व्योम
lsb_header_tail_dump(काष्ठा nvkm_subdev *subdev, काष्ठा lsb_header_tail *hdr)
अणु
	nvkm_debug(subdev, "lsbHeader\n");
	nvkm_debug(subdev, "\tucodeOff      : 0x%x\n", hdr->ucode_off);
	nvkm_debug(subdev, "\tucodeSize     : 0x%x\n", hdr->ucode_size);
	nvkm_debug(subdev, "\tdataSize      : 0x%x\n", hdr->data_size);
	nvkm_debug(subdev, "\tblCodeSize    : 0x%x\n", hdr->bl_code_size);
	nvkm_debug(subdev, "\tblImemOff     : 0x%x\n", hdr->bl_imem_off);
	nvkm_debug(subdev, "\tblDataOff     : 0x%x\n", hdr->bl_data_off);
	nvkm_debug(subdev, "\tblDataSize    : 0x%x\n", hdr->bl_data_size);
	nvkm_debug(subdev, "\tappCodeOff    : 0x%x\n", hdr->app_code_off);
	nvkm_debug(subdev, "\tappCodeSize   : 0x%x\n", hdr->app_code_size);
	nvkm_debug(subdev, "\tappDataOff    : 0x%x\n", hdr->app_data_off);
	nvkm_debug(subdev, "\tappDataSize   : 0x%x\n", hdr->app_data_size);
	nvkm_debug(subdev, "\tflags         : 0x%x\n", hdr->flags);
पूर्ण

व्योम
lsb_header_dump(काष्ठा nvkm_subdev *subdev, काष्ठा lsb_header *hdr)
अणु
	lsb_header_tail_dump(subdev, &hdr->tail);
पूर्ण

व्योम
lsb_header_v1_dump(काष्ठा nvkm_subdev *subdev, काष्ठा lsb_header_v1 *hdr)
अणु
	lsb_header_tail_dump(subdev, &hdr->tail);
पूर्ण

व्योम
flcn_acr_desc_dump(काष्ठा nvkm_subdev *subdev, काष्ठा flcn_acr_desc *hdr)
अणु
	पूर्णांक i;

	nvkm_debug(subdev, "acrDesc\n");
	nvkm_debug(subdev, "\twprRegionId  : %d\n", hdr->wpr_region_id);
	nvkm_debug(subdev, "\twprOffset    : 0x%x\n", hdr->wpr_offset);
	nvkm_debug(subdev, "\tmmuMemRange  : 0x%x\n",
		   hdr->mmu_mem_range);
	nvkm_debug(subdev, "\tnoRegions    : %d\n",
		   hdr->regions.no_regions);

	क्रम (i = 0; i < ARRAY_SIZE(hdr->regions.region_props); i++) अणु
		nvkm_debug(subdev, "\tregion[%d]    :\n", i);
		nvkm_debug(subdev, "\t  startAddr  : 0x%x\n",
			   hdr->regions.region_props[i].start_addr);
		nvkm_debug(subdev, "\t  endAddr    : 0x%x\n",
			   hdr->regions.region_props[i].end_addr);
		nvkm_debug(subdev, "\t  regionId   : %d\n",
			   hdr->regions.region_props[i].region_id);
		nvkm_debug(subdev, "\t  readMask   : 0x%x\n",
			   hdr->regions.region_props[i].पढ़ो_mask);
		nvkm_debug(subdev, "\t  writeMask  : 0x%x\n",
			   hdr->regions.region_props[i].ग_लिखो_mask);
		nvkm_debug(subdev, "\t  clientMask : 0x%x\n",
			   hdr->regions.region_props[i].client_mask);
	पूर्ण

	nvkm_debug(subdev, "\tucodeBlobSize: %d\n",
		   hdr->ucode_blob_size);
	nvkm_debug(subdev, "\tucodeBlobBase: 0x%llx\n",
		   hdr->ucode_blob_base);
	nvkm_debug(subdev, "\tvprEnabled   : %d\n",
		   hdr->vpr_desc.vpr_enabled);
	nvkm_debug(subdev, "\tvprStart     : 0x%x\n",
		   hdr->vpr_desc.vpr_start);
	nvkm_debug(subdev, "\tvprEnd       : 0x%x\n",
		   hdr->vpr_desc.vpr_end);
	nvkm_debug(subdev, "\thdcpPolicies : 0x%x\n",
		   hdr->vpr_desc.hdcp_policies);
पूर्ण

व्योम
flcn_acr_desc_v1_dump(काष्ठा nvkm_subdev *subdev, काष्ठा flcn_acr_desc_v1 *hdr)
अणु
	पूर्णांक i;

	nvkm_debug(subdev, "acrDesc\n");
	nvkm_debug(subdev, "\twprRegionId         : %d\n", hdr->wpr_region_id);
	nvkm_debug(subdev, "\twprOffset           : 0x%x\n", hdr->wpr_offset);
	nvkm_debug(subdev, "\tmmuMemoryRange      : 0x%x\n",
		   hdr->mmu_memory_range);
	nvkm_debug(subdev, "\tnoRegions           : %d\n",
		   hdr->regions.no_regions);

	क्रम (i = 0; i < ARRAY_SIZE(hdr->regions.region_props); i++) अणु
		nvkm_debug(subdev, "\tregion[%d]           :\n", i);
		nvkm_debug(subdev, "\t  startAddr         : 0x%x\n",
			   hdr->regions.region_props[i].start_addr);
		nvkm_debug(subdev, "\t  endAddr           : 0x%x\n",
			   hdr->regions.region_props[i].end_addr);
		nvkm_debug(subdev, "\t  regionId          : %d\n",
			   hdr->regions.region_props[i].region_id);
		nvkm_debug(subdev, "\t  readMask          : 0x%x\n",
			   hdr->regions.region_props[i].पढ़ो_mask);
		nvkm_debug(subdev, "\t  writeMask         : 0x%x\n",
			   hdr->regions.region_props[i].ग_लिखो_mask);
		nvkm_debug(subdev, "\t  clientMask        : 0x%x\n",
			   hdr->regions.region_props[i].client_mask);
		nvkm_debug(subdev, "\t  shadowMemStartAddr: 0x%x\n",
			   hdr->regions.region_props[i].shaकरोw_mem_start_addr);
	पूर्ण

	nvkm_debug(subdev, "\tucodeBlobSize       : %d\n",
		   hdr->ucode_blob_size);
	nvkm_debug(subdev, "\tucodeBlobBase       : 0x%llx\n",
		   hdr->ucode_blob_base);
	nvkm_debug(subdev, "\tvprEnabled          : %d\n",
		   hdr->vpr_desc.vpr_enabled);
	nvkm_debug(subdev, "\tvprStart            : 0x%x\n",
		   hdr->vpr_desc.vpr_start);
	nvkm_debug(subdev, "\tvprEnd              : 0x%x\n",
		   hdr->vpr_desc.vpr_end);
	nvkm_debug(subdev, "\thdcpPolicies        : 0x%x\n",
		   hdr->vpr_desc.hdcp_policies);
पूर्ण
