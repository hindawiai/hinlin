<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_CL9097_H__
#घोषणा __NVIF_CL9097_H__

#घोषणा FERMI_A_ZBC_COLOR                                                  0x00
#घोषणा FERMI_A_ZBC_DEPTH                                                  0x01

काष्ठा fermi_a_zbc_color_v0 अणु
	__u8  version;
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_ZERO                                      0x01
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_UNORM_ONE                                 0x02
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_RF32_GF32_BF32_AF32                       0x04
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_R16_G16_B16_A16                           0x08
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_RN16_GN16_BN16_AN16                       0x0c
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_RS16_GS16_BS16_AS16                       0x10
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_RU16_GU16_BU16_AU16                       0x14
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_RF16_GF16_BF16_AF16                       0x16
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_A8R8G8B8                                  0x18
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_A8RL8GL8BL8                               0x1c
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_A2B10G10R10                               0x20
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_AU2BU10GU10RU10                           0x24
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_A8B8G8R8                                  0x28
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_A8BL8GL8RL8                               0x2c
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_AN8BN8GN8RN8                              0x30
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_AS8BS8GS8RS8                              0x34
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_AU8BU8GU8RU8                              0x38
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_A2R10G10B10                               0x3c
#घोषणा FERMI_A_ZBC_COLOR_V0_FMT_BF10GF11RF11                              0x40
	__u8  क्रमmat;
	__u8  index;
	__u8  pad03[5];
	__u32 ds[4];
	__u32 l2[4];
पूर्ण;

काष्ठा fermi_a_zbc_depth_v0 अणु
	__u8  version;
#घोषणा FERMI_A_ZBC_DEPTH_V0_FMT_FP32                                      0x01
	__u8  क्रमmat;
	__u8  index;
	__u8  pad03[5];
	__u32 ds;
	__u32 l2;
पूर्ण;
#पूर्ण_अगर
