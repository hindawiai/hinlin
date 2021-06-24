<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_IF0002_H__
#घोषणा __NVIF_IF0002_H__

#घोषणा NVIF_PERFMON_V0_QUERY_DOMAIN                                       0x00
#घोषणा NVIF_PERFMON_V0_QUERY_SIGNAL                                       0x01
#घोषणा NVIF_PERFMON_V0_QUERY_SOURCE                                       0x02

काष्ठा nvअगर_perfmon_query_करोमुख्य_v0 अणु
	__u8  version;
	__u8  id;
	__u8  counter_nr;
	__u8  iter;
	__u16 संकेत_nr;
	__u8  pad05[2];
	अक्षर  name[64];
पूर्ण;

काष्ठा nvअगर_perfmon_query_संकेत_v0 अणु
	__u8  version;
	__u8  करोमुख्य;
	__u16 iter;
	__u8  संकेत;
	__u8  source_nr;
	__u8  pad05[2];
	अक्षर  name[64];
पूर्ण;

काष्ठा nvअगर_perfmon_query_source_v0 अणु
	__u8  version;
	__u8  करोमुख्य;
	__u8  संकेत;
	__u8  iter;
	__u8  pad04[4];
	__u32 source;
	__u32 mask;
	अक्षर  name[64];
पूर्ण;
#पूर्ण_अगर
