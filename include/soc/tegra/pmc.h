<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010 Google, Inc
 * Copyright (c) 2014 NVIDIA Corporation
 *
 * Author:
 *	Colin Cross <ccross@google.com>
 */

#अगर_अघोषित __SOC_TEGRA_PMC_H__
#घोषणा __SOC_TEGRA_PMC_H__

#समावेश <linux/reboot.h>

#समावेश <soc/tegra/pm.h>

काष्ठा clk;
काष्ठा reset_control;

bool tegra_pmc_cpu_is_घातered(अचिन्हित पूर्णांक cpuid);
पूर्णांक tegra_pmc_cpu_घातer_on(अचिन्हित पूर्णांक cpuid);
पूर्णांक tegra_pmc_cpu_हटाओ_clamping(अचिन्हित पूर्णांक cpuid);

/*
 * घातergate and I/O rail APIs
 */

#घोषणा TEGRA_POWERGATE_CPU	0
#घोषणा TEGRA_POWERGATE_3D	1
#घोषणा TEGRA_POWERGATE_VENC	2
#घोषणा TEGRA_POWERGATE_PCIE	3
#घोषणा TEGRA_POWERGATE_VDEC	4
#घोषणा TEGRA_POWERGATE_L2	5
#घोषणा TEGRA_POWERGATE_MPE	6
#घोषणा TEGRA_POWERGATE_HEG	7
#घोषणा TEGRA_POWERGATE_SATA	8
#घोषणा TEGRA_POWERGATE_CPU1	9
#घोषणा TEGRA_POWERGATE_CPU2	10
#घोषणा TEGRA_POWERGATE_CPU3	11
#घोषणा TEGRA_POWERGATE_CELP	12
#घोषणा TEGRA_POWERGATE_3D1	13
#घोषणा TEGRA_POWERGATE_CPU0	14
#घोषणा TEGRA_POWERGATE_C0NC	15
#घोषणा TEGRA_POWERGATE_C1NC	16
#घोषणा TEGRA_POWERGATE_SOR	17
#घोषणा TEGRA_POWERGATE_DIS	18
#घोषणा TEGRA_POWERGATE_DISB	19
#घोषणा TEGRA_POWERGATE_XUSBA	20
#घोषणा TEGRA_POWERGATE_XUSBB	21
#घोषणा TEGRA_POWERGATE_XUSBC	22
#घोषणा TEGRA_POWERGATE_VIC	23
#घोषणा TEGRA_POWERGATE_IRAM	24
#घोषणा TEGRA_POWERGATE_NVDEC	25
#घोषणा TEGRA_POWERGATE_NVJPG	26
#घोषणा TEGRA_POWERGATE_AUD	27
#घोषणा TEGRA_POWERGATE_DFD	28
#घोषणा TEGRA_POWERGATE_VE2	29
#घोषणा TEGRA_POWERGATE_MAX	TEGRA_POWERGATE_VE2

#घोषणा TEGRA_POWERGATE_3D0	TEGRA_POWERGATE_3D

/**
 * क्रमागत tegra_io_pad - I/O pad group identअगरier
 *
 * I/O pins on Tegra SoCs are grouped पूर्णांकo so-called I/O pads. Each such pad
 * can be used to control the common voltage संकेत level and घातer state of
 * the pins of the given pad.
 */
क्रमागत tegra_io_pad अणु
	TEGRA_IO_PAD_AUDIO,
	TEGRA_IO_PAD_AUDIO_HV,
	TEGRA_IO_PAD_BB,
	TEGRA_IO_PAD_CAM,
	TEGRA_IO_PAD_COMP,
	TEGRA_IO_PAD_CONN,
	TEGRA_IO_PAD_CSIA,
	TEGRA_IO_PAD_CSIB,
	TEGRA_IO_PAD_CSIC,
	TEGRA_IO_PAD_CSID,
	TEGRA_IO_PAD_CSIE,
	TEGRA_IO_PAD_CSIF,
	TEGRA_IO_PAD_CSIG,
	TEGRA_IO_PAD_CSIH,
	TEGRA_IO_PAD_DAP3,
	TEGRA_IO_PAD_DAP5,
	TEGRA_IO_PAD_DBG,
	TEGRA_IO_PAD_DEBUG_NONAO,
	TEGRA_IO_PAD_DMIC,
	TEGRA_IO_PAD_DMIC_HV,
	TEGRA_IO_PAD_DP,
	TEGRA_IO_PAD_DSI,
	TEGRA_IO_PAD_DSIB,
	TEGRA_IO_PAD_DSIC,
	TEGRA_IO_PAD_DSID,
	TEGRA_IO_PAD_EDP,
	TEGRA_IO_PAD_EMMC,
	TEGRA_IO_PAD_EMMC2,
	TEGRA_IO_PAD_EQOS,
	TEGRA_IO_PAD_GPIO,
	TEGRA_IO_PAD_GP_PWM2,
	TEGRA_IO_PAD_GP_PWM3,
	TEGRA_IO_PAD_HDMI,
	TEGRA_IO_PAD_HDMI_DP0,
	TEGRA_IO_PAD_HDMI_DP1,
	TEGRA_IO_PAD_HDMI_DP2,
	TEGRA_IO_PAD_HDMI_DP3,
	TEGRA_IO_PAD_HSIC,
	TEGRA_IO_PAD_HV,
	TEGRA_IO_PAD_LVDS,
	TEGRA_IO_PAD_MIPI_BIAS,
	TEGRA_IO_PAD_न_अंकD,
	TEGRA_IO_PAD_PEX_BIAS,
	TEGRA_IO_PAD_PEX_CLK_BIAS,
	TEGRA_IO_PAD_PEX_CLK1,
	TEGRA_IO_PAD_PEX_CLK2,
	TEGRA_IO_PAD_PEX_CLK3,
	TEGRA_IO_PAD_PEX_CLK_2_BIAS,
	TEGRA_IO_PAD_PEX_CLK_2,
	TEGRA_IO_PAD_PEX_CNTRL,
	TEGRA_IO_PAD_PEX_CTL2,
	TEGRA_IO_PAD_PEX_L0_RST_N,
	TEGRA_IO_PAD_PEX_L1_RST_N,
	TEGRA_IO_PAD_PEX_L5_RST_N,
	TEGRA_IO_PAD_PWR_CTL,
	TEGRA_IO_PAD_SDMMC1,
	TEGRA_IO_PAD_SDMMC1_HV,
	TEGRA_IO_PAD_SDMMC2,
	TEGRA_IO_PAD_SDMMC2_HV,
	TEGRA_IO_PAD_SDMMC3,
	TEGRA_IO_PAD_SDMMC3_HV,
	TEGRA_IO_PAD_SDMMC4,
	TEGRA_IO_PAD_SOC_GPIO10,
	TEGRA_IO_PAD_SOC_GPIO12,
	TEGRA_IO_PAD_SOC_GPIO13,
	TEGRA_IO_PAD_SOC_GPIO53,
	TEGRA_IO_PAD_SPI,
	TEGRA_IO_PAD_SPI_HV,
	TEGRA_IO_PAD_SYS_DDC,
	TEGRA_IO_PAD_UART,
	TEGRA_IO_PAD_UART4,
	TEGRA_IO_PAD_UART5,
	TEGRA_IO_PAD_UFS,
	TEGRA_IO_PAD_USB0,
	TEGRA_IO_PAD_USB1,
	TEGRA_IO_PAD_USB2,
	TEGRA_IO_PAD_USB3,
	TEGRA_IO_PAD_USB_BIAS,
	TEGRA_IO_PAD_AO_HV,
पूर्ण;

/* deprecated, use TEGRA_IO_PAD_अणुHDMI,LVDSपूर्ण instead */
#घोषणा TEGRA_IO_RAIL_HDMI	TEGRA_IO_PAD_HDMI
#घोषणा TEGRA_IO_RAIL_LVDS	TEGRA_IO_PAD_LVDS

#अगर_घोषित CONFIG_SOC_TEGRA_PMC
पूर्णांक tegra_घातergate_घातer_on(अचिन्हित पूर्णांक id);
पूर्णांक tegra_घातergate_घातer_off(अचिन्हित पूर्णांक id);
पूर्णांक tegra_घातergate_हटाओ_clamping(अचिन्हित पूर्णांक id);

/* Must be called with clk disabled, and वापसs with clk enabled */
पूर्णांक tegra_घातergate_sequence_घातer_up(अचिन्हित पूर्णांक id, काष्ठा clk *clk,
				      काष्ठा reset_control *rst);

पूर्णांक tegra_io_pad_घातer_enable(क्रमागत tegra_io_pad id);
पूर्णांक tegra_io_pad_घातer_disable(क्रमागत tegra_io_pad id);

/* deprecated, use tegra_io_pad_घातer_अणुenable,disableपूर्ण() instead */
पूर्णांक tegra_io_rail_घातer_on(अचिन्हित पूर्णांक id);
पूर्णांक tegra_io_rail_घातer_off(अचिन्हित पूर्णांक id);

व्योम tegra_pmc_set_suspend_mode(क्रमागत tegra_suspend_mode mode);
व्योम tegra_pmc_enter_suspend_mode(क्रमागत tegra_suspend_mode mode);

#अन्यथा
अटल अंतरभूत पूर्णांक tegra_घातergate_घातer_on(अचिन्हित पूर्णांक id)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक tegra_घातergate_घातer_off(अचिन्हित पूर्णांक id)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक tegra_घातergate_हटाओ_clamping(अचिन्हित पूर्णांक id)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक tegra_घातergate_sequence_घातer_up(अचिन्हित पूर्णांक id,
						    काष्ठा clk *clk,
						    काष्ठा reset_control *rst)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक tegra_io_pad_घातer_enable(क्रमागत tegra_io_pad id)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक tegra_io_pad_घातer_disable(क्रमागत tegra_io_pad id)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक tegra_io_pad_get_voltage(क्रमागत tegra_io_pad id)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक tegra_io_rail_घातer_on(अचिन्हित पूर्णांक id)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक tegra_io_rail_घातer_off(अचिन्हित पूर्णांक id)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम tegra_pmc_set_suspend_mode(क्रमागत tegra_suspend_mode mode)
अणु
पूर्ण

अटल अंतरभूत व्योम tegra_pmc_enter_suspend_mode(क्रमागत tegra_suspend_mode mode)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_SOC_TEGRA_PMC */

#अगर defined(CONFIG_SOC_TEGRA_PMC) && defined(CONFIG_PM_SLEEP)
क्रमागत tegra_suspend_mode tegra_pmc_get_suspend_mode(व्योम);
#अन्यथा
अटल अंतरभूत क्रमागत tegra_suspend_mode tegra_pmc_get_suspend_mode(व्योम)
अणु
	वापस TEGRA_SUSPEND_NONE;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SOC_TEGRA_PMC_H__ */
