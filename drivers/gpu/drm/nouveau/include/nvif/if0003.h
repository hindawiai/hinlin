<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_IF0003_H__
#घोषणा __NVIF_IF0003_H__

काष्ठा nvअगर_perfकरोm_v0 अणु
	__u8  version;
	__u8  करोमुख्य;
	__u8  mode;
	__u8  pad03[1];
	काष्ठा अणु
		__u8  संकेत[4];
		__u64 source[4][8];
		__u16 logic_op;
	पूर्ण ctr[4];
पूर्ण;

#घोषणा NVIF_PERFDOM_V0_INIT                                               0x00
#घोषणा NVIF_PERFDOM_V0_SAMPLE                                             0x01
#घोषणा NVIF_PERFDOM_V0_READ                                               0x02

काष्ठा nvअगर_perfकरोm_init अणु
पूर्ण;

काष्ठा nvअगर_perfकरोm_sample अणु
पूर्ण;

काष्ठा nvअगर_perfकरोm_पढ़ो_v0 अणु
	__u8  version;
	__u8  pad01[7];
	__u32 ctr[4];
	__u32 clk;
	__u8  pad04[4];
पूर्ण;
#पूर्ण_अगर
