<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_IF0001_H__
#घोषणा __NVIF_IF0001_H__

#घोषणा NVIF_CONTROL_PSTATE_INFO                                           0x00
#घोषणा NVIF_CONTROL_PSTATE_ATTR                                           0x01
#घोषणा NVIF_CONTROL_PSTATE_USER                                           0x02

काष्ठा nvअगर_control_pstate_info_v0 अणु
	__u8  version;
	__u8  count; /* out: number of घातer states */
#घोषणा NVIF_CONTROL_PSTATE_INFO_V0_USTATE_DISABLE                         (-1)
#घोषणा NVIF_CONTROL_PSTATE_INFO_V0_USTATE_PERFMON                         (-2)
	__s8  ustate_ac; /* out: target pstate index */
	__s8  ustate_dc; /* out: target pstate index */
	__s8  pwrsrc; /* out: current घातer source */
#घोषणा NVIF_CONTROL_PSTATE_INFO_V0_PSTATE_UNKNOWN                         (-1)
#घोषणा NVIF_CONTROL_PSTATE_INFO_V0_PSTATE_PERFMON                         (-2)
	__s8  pstate; /* out: current pstate index */
	__u8  pad06[2];
पूर्ण;

काष्ठा nvअगर_control_pstate_attr_v0 अणु
	__u8  version;
#घोषणा NVIF_CONTROL_PSTATE_ATTR_V0_STATE_CURRENT                          (-1)
	__s8  state; /*  in: index of pstate to query
		      * out: pstate identअगरier
		      */
	__u8  index; /*  in: index of attribute to query
		      * out: index of next attribute, or 0 अगर no more
		      */
	__u8  pad03[5];
	__u32 min;
	__u32 max;
	अक्षर  name[32];
	अक्षर  unit[16];
पूर्ण;

काष्ठा nvअगर_control_pstate_user_v0 अणु
	__u8  version;
#घोषणा NVIF_CONTROL_PSTATE_USER_V0_STATE_UNKNOWN                          (-1)
#घोषणा NVIF_CONTROL_PSTATE_USER_V0_STATE_PERFMON                          (-2)
	__s8  ustate; /*  in: pstate identअगरier */
	__s8  pwrsrc; /*  in: target घातer source */
	__u8  pad03[5];
पूर्ण;
#पूर्ण_अगर
