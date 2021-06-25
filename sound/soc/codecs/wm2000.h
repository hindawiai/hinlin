<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm2000.h  --  WM2000 Soc Audio driver
 */

#अगर_अघोषित _WM2000_H
#घोषणा _WM2000_H

#घोषणा WM2000_REG_SYS_START	    0x8000
#घोषणा WM2000_REG_ANC_GAIN_CTRL    0x8fa2
#घोषणा WM2000_REG_MSE_TH2          0x8fdf
#घोषणा WM2000_REG_MSE_TH1          0x8fe0
#घोषणा WM2000_REG_SPEECH_CLARITY   0x8fef
#घोषणा WM2000_REG_SYS_WATCHDOG     0x8ff6
#घोषणा WM2000_REG_ANA_VMID_PD_TIME 0x8ff7
#घोषणा WM2000_REG_ANA_VMID_PU_TIME 0x8ff8
#घोषणा WM2000_REG_CAT_FLTR_INDX    0x8ff9
#घोषणा WM2000_REG_CAT_GAIN_0       0x8ffa
#घोषणा WM2000_REG_SYS_STATUS       0x8ffc
#घोषणा WM2000_REG_SYS_MODE_CNTRL   0x8ffd
#घोषणा WM2000_REG_SYS_START0       0x8ffe
#घोषणा WM2000_REG_SYS_START1       0x8fff
#घोषणा WM2000_REG_ID1              0xf000
#घोषणा WM2000_REG_ID2              0xf001
#घोषणा WM2000_REG_REVISON          0xf002
#घोषणा WM2000_REG_SYS_CTL1         0xf003
#घोषणा WM2000_REG_SYS_CTL2         0xf004
#घोषणा WM2000_REG_ANC_STAT         0xf005
#घोषणा WM2000_REG_IF_CTL           0xf006
#घोषणा WM2000_REG_ANA_MIC_CTL      0xf028
#घोषणा WM2000_REG_SPK_CTL          0xf034

/* SPEECH_CLARITY */
#घोषणा WM2000_SPEECH_CLARITY   0x01

/* SYS_STATUS */
#घोषणा WM2000_STATUS_MOUSE_ACTIVE              0x40
#घोषणा WM2000_STATUS_CAT_FREQ_COMPLETE         0x20
#घोषणा WM2000_STATUS_CAT_GAIN_COMPLETE         0x10
#घोषणा WM2000_STATUS_THERMAL_SHUTDOWN_COMPLETE 0x08
#घोषणा WM2000_STATUS_ANC_DISABLED              0x04
#घोषणा WM2000_STATUS_POWER_DOWN_COMPLETE       0x02
#घोषणा WM2000_STATUS_BOOT_COMPLETE             0x01

/* SYS_MODE_CNTRL */
#घोषणा WM2000_MODE_ANA_SEQ_INCLUDE 0x80
#घोषणा WM2000_MODE_MOUSE_ENABLE    0x40
#घोषणा WM2000_MODE_CAT_FREQ_ENABLE 0x20
#घोषणा WM2000_MODE_CAT_GAIN_ENABLE 0x10
#घोषणा WM2000_MODE_BYPASS_ENTRY    0x08
#घोषणा WM2000_MODE_STANDBY_ENTRY   0x04
#घोषणा WM2000_MODE_THERMAL_ENABLE  0x02
#घोषणा WM2000_MODE_POWER_DOWN      0x01

/* SYS_CTL1 */
#घोषणा WM2000_SYS_STBY          0x01

/* SYS_CTL2 */
#घोषणा WM2000_MCLK_DIV2_ENA_CLR 0x80
#घोषणा WM2000_MCLK_DIV2_ENA_SET 0x40
#घोषणा WM2000_ANC_ENG_CLR       0x20
#घोषणा WM2000_ANC_ENG_SET       0x10
#घोषणा WM2000_ANC_INT_N_CLR     0x08
#घोषणा WM2000_ANC_INT_N_SET     0x04
#घोषणा WM2000_RAM_CLR           0x02
#घोषणा WM2000_RAM_SET           0x01

/* ANC_STAT */
#घोषणा WM2000_ANC_ENG_IDLE      0x01

#पूर्ण_अगर
