<शैली गुरु>
/*
 * Virtio GPU Device
 *
 * Copyright Red Hat, Inc. 2013-2014
 *
 * Authors:
 *     Dave Airlie <airlied@redhat.com>
 *     Gerd Hoffmann <kraxel@redhat.com>
 *
 * This header is BSD licensed so anyone can use the definitions
 * to implement compatible drivers/servers:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of IBM nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#अगर_अघोषित VIRTIO_GPU_HW_H
#घोषणा VIRTIO_GPU_HW_H

#समावेश <linux/types.h>

/*
 * VIRTIO_GPU_CMD_CTX_*
 * VIRTIO_GPU_CMD_*_3D
 */
#घोषणा VIRTIO_GPU_F_VIRGL               0

/*
 * VIRTIO_GPU_CMD_GET_EDID
 */
#घोषणा VIRTIO_GPU_F_EDID                1
/*
 * VIRTIO_GPU_CMD_RESOURCE_ASSIGN_UUID
 */
#घोषणा VIRTIO_GPU_F_RESOURCE_UUID       2

/*
 * VIRTIO_GPU_CMD_RESOURCE_CREATE_BLOB
 */
#घोषणा VIRTIO_GPU_F_RESOURCE_BLOB       3

क्रमागत virtio_gpu_ctrl_type अणु
	VIRTIO_GPU_UNDEFINED = 0,

	/* 2d commands */
	VIRTIO_GPU_CMD_GET_DISPLAY_INFO = 0x0100,
	VIRTIO_GPU_CMD_RESOURCE_CREATE_2D,
	VIRTIO_GPU_CMD_RESOURCE_UNREF,
	VIRTIO_GPU_CMD_SET_SCANOUT,
	VIRTIO_GPU_CMD_RESOURCE_FLUSH,
	VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D,
	VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING,
	VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING,
	VIRTIO_GPU_CMD_GET_CAPSET_INFO,
	VIRTIO_GPU_CMD_GET_CAPSET,
	VIRTIO_GPU_CMD_GET_EDID,
	VIRTIO_GPU_CMD_RESOURCE_ASSIGN_UUID,
	VIRTIO_GPU_CMD_RESOURCE_CREATE_BLOB,
	VIRTIO_GPU_CMD_SET_SCANOUT_BLOB,

	/* 3d commands */
	VIRTIO_GPU_CMD_CTX_CREATE = 0x0200,
	VIRTIO_GPU_CMD_CTX_DESTROY,
	VIRTIO_GPU_CMD_CTX_ATTACH_RESOURCE,
	VIRTIO_GPU_CMD_CTX_DETACH_RESOURCE,
	VIRTIO_GPU_CMD_RESOURCE_CREATE_3D,
	VIRTIO_GPU_CMD_TRANSFER_TO_HOST_3D,
	VIRTIO_GPU_CMD_TRANSFER_FROM_HOST_3D,
	VIRTIO_GPU_CMD_SUBMIT_3D,
	VIRTIO_GPU_CMD_RESOURCE_MAP_BLOB,
	VIRTIO_GPU_CMD_RESOURCE_UNMAP_BLOB,

	/* cursor commands */
	VIRTIO_GPU_CMD_UPDATE_CURSOR = 0x0300,
	VIRTIO_GPU_CMD_MOVE_CURSOR,

	/* success responses */
	VIRTIO_GPU_RESP_OK_NODATA = 0x1100,
	VIRTIO_GPU_RESP_OK_DISPLAY_INFO,
	VIRTIO_GPU_RESP_OK_CAPSET_INFO,
	VIRTIO_GPU_RESP_OK_CAPSET,
	VIRTIO_GPU_RESP_OK_EDID,
	VIRTIO_GPU_RESP_OK_RESOURCE_UUID,
	VIRTIO_GPU_RESP_OK_MAP_INFO,

	/* error responses */
	VIRTIO_GPU_RESP_ERR_UNSPEC = 0x1200,
	VIRTIO_GPU_RESP_ERR_OUT_OF_MEMORY,
	VIRTIO_GPU_RESP_ERR_INVALID_SCANOUT_ID,
	VIRTIO_GPU_RESP_ERR_INVALID_RESOURCE_ID,
	VIRTIO_GPU_RESP_ERR_INVALID_CONTEXT_ID,
	VIRTIO_GPU_RESP_ERR_INVALID_PARAMETER,
पूर्ण;

क्रमागत virtio_gpu_shm_id अणु
	VIRTIO_GPU_SHM_ID_UNDEFINED = 0,
	/*
	 * VIRTIO_GPU_CMD_RESOURCE_MAP_BLOB
	 * VIRTIO_GPU_CMD_RESOURCE_UNMAP_BLOB
	 */
	VIRTIO_GPU_SHM_ID_HOST_VISIBLE = 1
पूर्ण;

#घोषणा VIRTIO_GPU_FLAG_FENCE (1 << 0)

काष्ठा virtio_gpu_ctrl_hdr अणु
	__le32 type;
	__le32 flags;
	__le64 fence_id;
	__le32 ctx_id;
	__le32 padding;
पूर्ण;

/* data passed in the cursor vq */

काष्ठा virtio_gpu_cursor_pos अणु
	__le32 scanout_id;
	__le32 x;
	__le32 y;
	__le32 padding;
पूर्ण;

/* VIRTIO_GPU_CMD_UPDATE_CURSOR, VIRTIO_GPU_CMD_MOVE_CURSOR */
काष्ठा virtio_gpu_update_cursor अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	काष्ठा virtio_gpu_cursor_pos pos;  /* update & move */
	__le32 resource_id;           /* update only */
	__le32 hot_x;                 /* update only */
	__le32 hot_y;                 /* update only */
	__le32 padding;
पूर्ण;

/* data passed in the control vq, 2d related */

काष्ठा virtio_gpu_rect अणु
	__le32 x;
	__le32 y;
	__le32 width;
	__le32 height;
पूर्ण;

/* VIRTIO_GPU_CMD_RESOURCE_UNREF */
काष्ठा virtio_gpu_resource_unref अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 resource_id;
	__le32 padding;
पूर्ण;

/* VIRTIO_GPU_CMD_RESOURCE_CREATE_2D: create a 2d resource with a क्रमmat */
काष्ठा virtio_gpu_resource_create_2d अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 resource_id;
	__le32 क्रमmat;
	__le32 width;
	__le32 height;
पूर्ण;

/* VIRTIO_GPU_CMD_SET_SCANOUT */
काष्ठा virtio_gpu_set_scanout अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	काष्ठा virtio_gpu_rect r;
	__le32 scanout_id;
	__le32 resource_id;
पूर्ण;

/* VIRTIO_GPU_CMD_RESOURCE_FLUSH */
काष्ठा virtio_gpu_resource_flush अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	काष्ठा virtio_gpu_rect r;
	__le32 resource_id;
	__le32 padding;
पूर्ण;

/* VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D: simple transfer to_host */
काष्ठा virtio_gpu_transfer_to_host_2d अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	काष्ठा virtio_gpu_rect r;
	__le64 offset;
	__le32 resource_id;
	__le32 padding;
पूर्ण;

काष्ठा virtio_gpu_mem_entry अणु
	__le64 addr;
	__le32 length;
	__le32 padding;
पूर्ण;

/* VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING */
काष्ठा virtio_gpu_resource_attach_backing अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 resource_id;
	__le32 nr_entries;
पूर्ण;

/* VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING */
काष्ठा virtio_gpu_resource_detach_backing अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 resource_id;
	__le32 padding;
पूर्ण;

/* VIRTIO_GPU_RESP_OK_DISPLAY_INFO */
#घोषणा VIRTIO_GPU_MAX_SCANOUTS 16
काष्ठा virtio_gpu_resp_display_info अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	काष्ठा virtio_gpu_display_one अणु
		काष्ठा virtio_gpu_rect r;
		__le32 enabled;
		__le32 flags;
	पूर्ण pmodes[VIRTIO_GPU_MAX_SCANOUTS];
पूर्ण;

/* data passed in the control vq, 3d related */

काष्ठा virtio_gpu_box अणु
	__le32 x, y, z;
	__le32 w, h, d;
पूर्ण;

/* VIRTIO_GPU_CMD_TRANSFER_TO_HOST_3D, VIRTIO_GPU_CMD_TRANSFER_FROM_HOST_3D */
काष्ठा virtio_gpu_transfer_host_3d अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	काष्ठा virtio_gpu_box box;
	__le64 offset;
	__le32 resource_id;
	__le32 level;
	__le32 stride;
	__le32 layer_stride;
पूर्ण;

/* VIRTIO_GPU_CMD_RESOURCE_CREATE_3D */
#घोषणा VIRTIO_GPU_RESOURCE_FLAG_Y_0_TOP (1 << 0)
काष्ठा virtio_gpu_resource_create_3d अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 resource_id;
	__le32 target;
	__le32 क्रमmat;
	__le32 bind;
	__le32 width;
	__le32 height;
	__le32 depth;
	__le32 array_size;
	__le32 last_level;
	__le32 nr_samples;
	__le32 flags;
	__le32 padding;
पूर्ण;

/* VIRTIO_GPU_CMD_CTX_CREATE */
काष्ठा virtio_gpu_ctx_create अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 nlen;
	__le32 padding;
	अक्षर debug_name[64];
पूर्ण;

/* VIRTIO_GPU_CMD_CTX_DESTROY */
काष्ठा virtio_gpu_ctx_destroy अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
पूर्ण;

/* VIRTIO_GPU_CMD_CTX_ATTACH_RESOURCE, VIRTIO_GPU_CMD_CTX_DETACH_RESOURCE */
काष्ठा virtio_gpu_ctx_resource अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 resource_id;
	__le32 padding;
पूर्ण;

/* VIRTIO_GPU_CMD_SUBMIT_3D */
काष्ठा virtio_gpu_cmd_submit अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 size;
	__le32 padding;
पूर्ण;

#घोषणा VIRTIO_GPU_CAPSET_VIRGL 1
#घोषणा VIRTIO_GPU_CAPSET_VIRGL2 2

/* VIRTIO_GPU_CMD_GET_CAPSET_INFO */
काष्ठा virtio_gpu_get_capset_info अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 capset_index;
	__le32 padding;
पूर्ण;

/* VIRTIO_GPU_RESP_OK_CAPSET_INFO */
काष्ठा virtio_gpu_resp_capset_info अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 capset_id;
	__le32 capset_max_version;
	__le32 capset_max_size;
	__le32 padding;
पूर्ण;

/* VIRTIO_GPU_CMD_GET_CAPSET */
काष्ठा virtio_gpu_get_capset अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 capset_id;
	__le32 capset_version;
पूर्ण;

/* VIRTIO_GPU_RESP_OK_CAPSET */
काष्ठा virtio_gpu_resp_capset अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__u8 capset_data[];
पूर्ण;

/* VIRTIO_GPU_CMD_GET_EDID */
काष्ठा virtio_gpu_cmd_get_edid अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 scanout;
	__le32 padding;
पूर्ण;

/* VIRTIO_GPU_RESP_OK_EDID */
काष्ठा virtio_gpu_resp_edid अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 size;
	__le32 padding;
	__u8 edid[1024];
पूर्ण;

#घोषणा VIRTIO_GPU_EVENT_DISPLAY (1 << 0)

काष्ठा virtio_gpu_config अणु
	__le32 events_पढ़ो;
	__le32 events_clear;
	__le32 num_scanouts;
	__le32 num_capsets;
पूर्ण;

/* simple क्रमmats क्रम fbcon/X use */
क्रमागत virtio_gpu_क्रमmats अणु
	VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM  = 1,
	VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM  = 2,
	VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM  = 3,
	VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM  = 4,

	VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM  = 67,
	VIRTIO_GPU_FORMAT_X8B8G8R8_UNORM  = 68,

	VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM  = 121,
	VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM  = 134,
पूर्ण;

/* VIRTIO_GPU_CMD_RESOURCE_ASSIGN_UUID */
काष्ठा virtio_gpu_resource_assign_uuid अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 resource_id;
	__le32 padding;
पूर्ण;

/* VIRTIO_GPU_RESP_OK_RESOURCE_UUID */
काष्ठा virtio_gpu_resp_resource_uuid अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__u8 uuid[16];
पूर्ण;

/* VIRTIO_GPU_CMD_RESOURCE_CREATE_BLOB */
काष्ठा virtio_gpu_resource_create_blob अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 resource_id;
#घोषणा VIRTIO_GPU_BLOB_MEM_GUEST             0x0001
#घोषणा VIRTIO_GPU_BLOB_MEM_HOST3D            0x0002
#घोषणा VIRTIO_GPU_BLOB_MEM_HOST3D_GUEST      0x0003

#घोषणा VIRTIO_GPU_BLOB_FLAG_USE_MAPPABLE     0x0001
#घोषणा VIRTIO_GPU_BLOB_FLAG_USE_SHAREABLE    0x0002
#घोषणा VIRTIO_GPU_BLOB_FLAG_USE_CROSS_DEVICE 0x0004
	/* zero is invalid blob mem */
	__le32 blob_mem;
	__le32 blob_flags;
	__le32 nr_entries;
	__le64 blob_id;
	__le64 size;
	/*
	 * माप(nr_entries * virtio_gpu_mem_entry) bytes follow
	 */
पूर्ण;

/* VIRTIO_GPU_CMD_SET_SCANOUT_BLOB */
काष्ठा virtio_gpu_set_scanout_blob अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	काष्ठा virtio_gpu_rect r;
	__le32 scanout_id;
	__le32 resource_id;
	__le32 width;
	__le32 height;
	__le32 क्रमmat;
	__le32 padding;
	__le32 strides[4];
	__le32 offsets[4];
पूर्ण;

/* VIRTIO_GPU_CMD_RESOURCE_MAP_BLOB */
काष्ठा virtio_gpu_resource_map_blob अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 resource_id;
	__le32 padding;
	__le64 offset;
पूर्ण;

/* VIRTIO_GPU_RESP_OK_MAP_INFO */
#घोषणा VIRTIO_GPU_MAP_CACHE_MASK     0x0f
#घोषणा VIRTIO_GPU_MAP_CACHE_NONE     0x00
#घोषणा VIRTIO_GPU_MAP_CACHE_CACHED   0x01
#घोषणा VIRTIO_GPU_MAP_CACHE_UNCACHED 0x02
#घोषणा VIRTIO_GPU_MAP_CACHE_WC       0x03
काष्ठा virtio_gpu_resp_map_info अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__u32 map_info;
	__u32 padding;
पूर्ण;

/* VIRTIO_GPU_CMD_RESOURCE_UNMAP_BLOB */
काष्ठा virtio_gpu_resource_unmap_blob अणु
	काष्ठा virtio_gpu_ctrl_hdr hdr;
	__le32 resource_id;
	__le32 padding;
पूर्ण;

#पूर्ण_अगर
