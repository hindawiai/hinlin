<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_IOCTL_H__
#घोषणा __NVIF_IOCTL_H__

#घोषणा NVIF_VERSION_LATEST                               0x0000000000000100ULL

काष्ठा nvअगर_ioctl_v0 अणु
	__u8  version;
#घोषणा NVIF_IOCTL_V0_NOP                                                  0x00
#घोषणा NVIF_IOCTL_V0_SCLASS                                               0x01
#घोषणा NVIF_IOCTL_V0_NEW                                                  0x02
#घोषणा NVIF_IOCTL_V0_DEL                                                  0x03
#घोषणा NVIF_IOCTL_V0_MTHD                                                 0x04
#घोषणा NVIF_IOCTL_V0_RD                                                   0x05
#घोषणा NVIF_IOCTL_V0_WR                                                   0x06
#घोषणा NVIF_IOCTL_V0_MAP                                                  0x07
#घोषणा NVIF_IOCTL_V0_UNMAP                                                0x08
#घोषणा NVIF_IOCTL_V0_NTFY_NEW                                             0x09
#घोषणा NVIF_IOCTL_V0_NTFY_DEL                                             0x0a
#घोषणा NVIF_IOCTL_V0_NTFY_GET                                             0x0b
#घोषणा NVIF_IOCTL_V0_NTFY_PUT                                             0x0c
	__u8  type;
	__u8  pad02[4];
#घोषणा NVIF_IOCTL_V0_OWNER_NVIF                                           0x00
#घोषणा NVIF_IOCTL_V0_OWNER_ANY                                            0xff
	__u8  owner;
#घोषणा NVIF_IOCTL_V0_ROUTE_NVIF                                           0x00
#घोषणा NVIF_IOCTL_V0_ROUTE_HIDDEN                                         0xff
	__u8  route;
	__u64 token;
	__u64 object;
	__u8  data[];		/* ioctl data (below) */
पूर्ण;

काष्ठा nvअगर_ioctl_nop_v0 अणु
	__u64 version;
पूर्ण;

काष्ठा nvअगर_ioctl_sclass_v0 अणु
	/* nvअगर_ioctl ... */
	__u8  version;
	__u8  count;
	__u8  pad02[6];
	काष्ठा nvअगर_ioctl_sclass_oclass_v0 अणु
		__s32 oclass;
		__s16 minver;
		__s16 maxver;
	पूर्ण oclass[];
पूर्ण;

काष्ठा nvअगर_ioctl_new_v0 अणु
	/* nvअगर_ioctl ... */
	__u8  version;
	__u8  pad01[6];
	__u8  route;
	__u64 token;
	__u64 object;
	__u32 handle;
	__s32 oclass;
	__u8  data[];		/* class data (class.h) */
पूर्ण;

काष्ठा nvअगर_ioctl_del अणु
पूर्ण;

काष्ठा nvअगर_ioctl_rd_v0 अणु
	/* nvअगर_ioctl ... */
	__u8  version;
	__u8  size;
	__u8  pad02[2];
	__u32 data;
	__u64 addr;
पूर्ण;

काष्ठा nvअगर_ioctl_wr_v0 अणु
	/* nvअगर_ioctl ... */
	__u8  version;
	__u8  size;
	__u8  pad02[2];
	__u32 data;
	__u64 addr;
पूर्ण;

काष्ठा nvअगर_ioctl_map_v0 अणु
	/* nvअगर_ioctl ... */
	__u8  version;
#घोषणा NVIF_IOCTL_MAP_V0_IO                                               0x00
#घोषणा NVIF_IOCTL_MAP_V0_VA                                               0x01
	__u8  type;
	__u8  pad02[6];
	__u64 handle;
	__u64 length;
	__u8  data[];
पूर्ण;

काष्ठा nvअगर_ioctl_unmap अणु
पूर्ण;

काष्ठा nvअगर_ioctl_ntfy_new_v0 अणु
	/* nvअगर_ioctl ... */
	__u8  version;
	__u8  event;
	__u8  index;
	__u8  pad03[5];
	__u8  data[];		/* event request data (event.h) */
पूर्ण;

काष्ठा nvअगर_ioctl_ntfy_del_v0 अणु
	/* nvअगर_ioctl ... */
	__u8  version;
	__u8  index;
	__u8  pad02[6];
पूर्ण;

काष्ठा nvअगर_ioctl_ntfy_get_v0 अणु
	/* nvअगर_ioctl ... */
	__u8  version;
	__u8  index;
	__u8  pad02[6];
पूर्ण;

काष्ठा nvअगर_ioctl_ntfy_put_v0 अणु
	/* nvअगर_ioctl ... */
	__u8  version;
	__u8  index;
	__u8  pad02[6];
पूर्ण;

काष्ठा nvअगर_ioctl_mthd_v0 अणु
	/* nvअगर_ioctl ... */
	__u8  version;
	__u8  method;
	__u8  pad02[6];
	__u8  data[];		/* method data (class.h) */
पूर्ण;

#पूर्ण_अगर
