<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_IF0000_H__
#घोषणा __NVIF_IF0000_H__

काष्ठा nvअगर_client_v0 अणु
	__u8  version;
	__u8  pad01[7];
	__u64 device;
	अक्षर  name[32];
पूर्ण;

#घोषणा NVIF_CLIENT_V0_DEVLIST                                             0x00

काष्ठा nvअगर_client_devlist_v0 अणु
	__u8  version;
	__u8  count;
	__u8  pad02[6];
	__u64 device[];
पूर्ण;
#पूर्ण_अगर
