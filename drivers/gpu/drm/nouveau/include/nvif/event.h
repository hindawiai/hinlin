<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_EVENT_H__
#घोषणा __NVIF_EVENT_H__

काष्ठा nvअगर_notअगरy_req_v0 अणु
	__u8  version;
	__u8  reply;
	__u8  pad02[5];
#घोषणा NVIF_NOTIFY_V0_ROUTE_NVIF                                          0x00
	__u8  route;
	__u64 token;	/* must be unique */
	__u8  data[];	/* request data (below) */
पूर्ण;

काष्ठा nvअगर_notअगरy_rep_v0 अणु
	__u8  version;
	__u8  pad01[6];
	__u8  route;
	__u64 token;
	__u8  data[];	/* reply data (below) */
पूर्ण;

काष्ठा nvअगर_notअगरy_head_req_v0 अणु
	/* nvअगर_notअगरy_req ... */
	__u8  version;
	__u8  head;
	__u8  pad02[6];
पूर्ण;

काष्ठा nvअगर_notअगरy_head_rep_v0 अणु
	/* nvअगर_notअगरy_rep ... */
	__u8  version;
	__u8  pad01[7];
पूर्ण;

काष्ठा nvअगर_notअगरy_conn_req_v0 अणु
	/* nvअगर_notअगरy_req ... */
	__u8  version;
#घोषणा NVIF_NOTIFY_CONN_V0_PLUG                                           0x01
#घोषणा NVIF_NOTIFY_CONN_V0_UNPLUG                                         0x02
#घोषणा NVIF_NOTIFY_CONN_V0_IRQ                                            0x04
#घोषणा NVIF_NOTIFY_CONN_V0_ANY                                            0x07
	__u8  mask;
	__u8  conn;
	__u8  pad03[5];
पूर्ण;

काष्ठा nvअगर_notअगरy_conn_rep_v0 अणु
	/* nvअगर_notअगरy_rep ... */
	__u8  version;
	__u8  mask;
	__u8  pad02[6];
पूर्ण;

काष्ठा nvअगर_notअगरy_uevent_req अणु
	/* nvअगर_notअगरy_req ... */
पूर्ण;

काष्ठा nvअगर_notअगरy_uevent_rep अणु
	/* nvअगर_notअगरy_rep ... */
पूर्ण;

#पूर्ण_अगर
