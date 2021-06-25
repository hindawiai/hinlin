<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DISP_DP_H__
#घोषणा __NVKM_DISP_DP_H__
#घोषणा nvkm_dp(p) container_of((p), काष्ठा nvkm_dp, outp)
#समावेश "outp.h"

#समावेश <core/notअगरy.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/dp.h>

काष्ठा nvkm_dp अणु
	जोड़ अणु
		काष्ठा nvkm_outp base;
		काष्ठा nvkm_outp outp;
	पूर्ण;

	काष्ठा nvbios_dpout info;
	u8 version;

	काष्ठा nvkm_i2c_aux *aux;

	काष्ठा nvkm_notअगरy hpd;
	bool present;
	u8 dpcd[16];

	काष्ठा mutex mutex;
	काष्ठा अणु
		atomic_t करोne;
		bool mst;
	पूर्ण lt;
पूर्ण;

पूर्णांक nvkm_dp_new(काष्ठा nvkm_disp *, पूर्णांक index, काष्ठा dcb_output *,
		काष्ठा nvkm_outp **);

/* DPCD Receiver Capabilities */
#घोषणा DPCD_RC00_DPCD_REV                                              0x00000
#घोषणा DPCD_RC01_MAX_LINK_RATE                                         0x00001
#घोषणा DPCD_RC02                                                       0x00002
#घोषणा DPCD_RC02_ENHANCED_FRAME_CAP                                       0x80
#घोषणा DPCD_RC02_TPS3_SUPPORTED                                           0x40
#घोषणा DPCD_RC02_MAX_LANE_COUNT                                           0x1f
#घोषणा DPCD_RC03                                                       0x00003
#घोषणा DPCD_RC03_MAX_DOWNSPREAD                                           0x01
#घोषणा DPCD_RC0E_AUX_RD_INTERVAL                                       0x0000e

/* DPCD Link Configuration */
#घोषणा DPCD_LC00_LINK_BW_SET                                           0x00100
#घोषणा DPCD_LC01                                                       0x00101
#घोषणा DPCD_LC01_ENHANCED_FRAME_EN                                        0x80
#घोषणा DPCD_LC01_LANE_COUNT_SET                                           0x1f
#घोषणा DPCD_LC02                                                       0x00102
#घोषणा DPCD_LC02_TRAINING_PATTERN_SET                                     0x03
#घोषणा DPCD_LC03(l)                                            ((l) +  0x00103)
#घोषणा DPCD_LC03_MAX_PRE_EMPHASIS_REACHED                                 0x20
#घोषणा DPCD_LC03_PRE_EMPHASIS_SET                                         0x18
#घोषणा DPCD_LC03_MAX_SWING_REACHED                                        0x04
#घोषणा DPCD_LC03_VOLTAGE_SWING_SET                                        0x03
#घोषणा DPCD_LC0F                                                       0x0010f
#घोषणा DPCD_LC0F_LANE1_MAX_POST_CURSOR2_REACHED                           0x40
#घोषणा DPCD_LC0F_LANE1_POST_CURSOR2_SET                                   0x30
#घोषणा DPCD_LC0F_LANE0_MAX_POST_CURSOR2_REACHED                           0x04
#घोषणा DPCD_LC0F_LANE0_POST_CURSOR2_SET                                   0x03
#घोषणा DPCD_LC10                                                       0x00110
#घोषणा DPCD_LC10_LANE3_MAX_POST_CURSOR2_REACHED                           0x40
#घोषणा DPCD_LC10_LANE3_POST_CURSOR2_SET                                   0x30
#घोषणा DPCD_LC10_LANE2_MAX_POST_CURSOR2_REACHED                           0x04
#घोषणा DPCD_LC10_LANE2_POST_CURSOR2_SET                                   0x03

/* DPCD Link/Sink Status */
#घोषणा DPCD_LS02                                                       0x00202
#घोषणा DPCD_LS02_LANE1_SYMBOL_LOCKED                                      0x40
#घोषणा DPCD_LS02_LANE1_CHANNEL_EQ_DONE                                    0x20
#घोषणा DPCD_LS02_LANE1_CR_DONE                                            0x10
#घोषणा DPCD_LS02_LANE0_SYMBOL_LOCKED                                      0x04
#घोषणा DPCD_LS02_LANE0_CHANNEL_EQ_DONE                                    0x02
#घोषणा DPCD_LS02_LANE0_CR_DONE                                            0x01
#घोषणा DPCD_LS03                                                       0x00203
#घोषणा DPCD_LS03_LANE3_SYMBOL_LOCKED                                      0x40
#घोषणा DPCD_LS03_LANE3_CHANNEL_EQ_DONE                                    0x20
#घोषणा DPCD_LS03_LANE3_CR_DONE                                            0x10
#घोषणा DPCD_LS03_LANE2_SYMBOL_LOCKED                                      0x04
#घोषणा DPCD_LS03_LANE2_CHANNEL_EQ_DONE                                    0x02
#घोषणा DPCD_LS03_LANE2_CR_DONE                                            0x01
#घोषणा DPCD_LS04                                                       0x00204
#घोषणा DPCD_LS04_LINK_STATUS_UPDATED                                      0x80
#घोषणा DPCD_LS04_DOWNSTREAM_PORT_STATUS_CHANGED                           0x40
#घोषणा DPCD_LS04_INTERLANE_ALIGN_DONE                                     0x01
#घोषणा DPCD_LS06                                                       0x00206
#घोषणा DPCD_LS06_LANE1_PRE_EMPHASIS                                       0xc0
#घोषणा DPCD_LS06_LANE1_VOLTAGE_SWING                                      0x30
#घोषणा DPCD_LS06_LANE0_PRE_EMPHASIS                                       0x0c
#घोषणा DPCD_LS06_LANE0_VOLTAGE_SWING                                      0x03
#घोषणा DPCD_LS07                                                       0x00207
#घोषणा DPCD_LS07_LANE3_PRE_EMPHASIS                                       0xc0
#घोषणा DPCD_LS07_LANE3_VOLTAGE_SWING                                      0x30
#घोषणा DPCD_LS07_LANE2_PRE_EMPHASIS                                       0x0c
#घोषणा DPCD_LS07_LANE2_VOLTAGE_SWING                                      0x03
#घोषणा DPCD_LS0C                                                       0x0020c
#घोषणा DPCD_LS0C_LANE3_POST_CURSOR2                                       0xc0
#घोषणा DPCD_LS0C_LANE2_POST_CURSOR2                                       0x30
#घोषणा DPCD_LS0C_LANE1_POST_CURSOR2                                       0x0c
#घोषणा DPCD_LS0C_LANE0_POST_CURSOR2                                       0x03

/* DPCD Sink Control */
#घोषणा DPCD_SC00                                                       0x00600
#घोषणा DPCD_SC00_SET_POWER                                                0x03
#घोषणा DPCD_SC00_SET_POWER_D0                                             0x01
#घोषणा DPCD_SC00_SET_POWER_D3                                             0x03
#पूर्ण_अगर
