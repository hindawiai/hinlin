<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/** @file */

#अगर_अघोषित _MACH_T186_CLK_T186_H
#घोषणा _MACH_T186_CLK_T186_H

/**
 * @defgroup घड़ी_ids Clock Identअगरiers
 * @अणु
 *   @defgroup बाह्य_input बाह्यal input घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_OSC
 *     @def TEGRA186_CLK_CLK_32K
 *     @def TEGRA186_CLK_DTV_INPUT
 *     @def TEGRA186_CLK_SOR0_PAD_CLKOUT
 *     @def TEGRA186_CLK_SOR1_PAD_CLKOUT
 *     @def TEGRA186_CLK_I2S1_SYNC_INPUT
 *     @def TEGRA186_CLK_I2S2_SYNC_INPUT
 *     @def TEGRA186_CLK_I2S3_SYNC_INPUT
 *     @def TEGRA186_CLK_I2S4_SYNC_INPUT
 *     @def TEGRA186_CLK_I2S5_SYNC_INPUT
 *     @def TEGRA186_CLK_I2S6_SYNC_INPUT
 *     @def TEGRA186_CLK_SPDIFIN_SYNC_INPUT
 *   @पूर्ण
 *
 *   @defgroup बाह्य_output बाह्यal output घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_EXTPERIPH1
 *     @def TEGRA186_CLK_EXTPERIPH2
 *     @def TEGRA186_CLK_EXTPERIPH3
 *     @def TEGRA186_CLK_EXTPERIPH4
 *   @पूर्ण
 *
 *   @defgroup display_clks display related घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_CEC
 *     @def TEGRA186_CLK_DSIC
 *     @def TEGRA186_CLK_DSIC_LP
 *     @def TEGRA186_CLK_DSID
 *     @def TEGRA186_CLK_DSID_LP
 *     @def TEGRA186_CLK_DPAUX1
 *     @def TEGRA186_CLK_DPAUX
 *     @def TEGRA186_CLK_HDA2HDMICODEC
 *     @def TEGRA186_CLK_NVDISPLAY_DISP
 *     @def TEGRA186_CLK_NVDISPLAY_DSC
 *     @def TEGRA186_CLK_NVDISPLAY_P0
 *     @def TEGRA186_CLK_NVDISPLAY_P1
 *     @def TEGRA186_CLK_NVDISPLAY_P2
 *     @def TEGRA186_CLK_NVDISPLAYHUB
 *     @def TEGRA186_CLK_SOR_SAFE
 *     @def TEGRA186_CLK_SOR0
 *     @def TEGRA186_CLK_SOR0_OUT
 *     @def TEGRA186_CLK_SOR1
 *     @def TEGRA186_CLK_SOR1_OUT
 *     @def TEGRA186_CLK_DSI
 *     @def TEGRA186_CLK_MIPI_CAL
 *     @def TEGRA186_CLK_DSIA_LP
 *     @def TEGRA186_CLK_DSIB
 *     @def TEGRA186_CLK_DSIB_LP
 *   @पूर्ण
 *
 *   @defgroup camera_clks camera related घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_NVCSI
 *     @def TEGRA186_CLK_NVCSILP
 *     @def TEGRA186_CLK_VI
 *   @पूर्ण
 *
 *   @defgroup audio_clks audio related घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_ACLK
 *     @def TEGRA186_CLK_ADSP
 *     @def TEGRA186_CLK_ADSPNEON
 *     @def TEGRA186_CLK_AHUB
 *     @def TEGRA186_CLK_APE
 *     @def TEGRA186_CLK_APB2APE
 *     @def TEGRA186_CLK_AUD_MCLK
 *     @def TEGRA186_CLK_DMIC1
 *     @def TEGRA186_CLK_DMIC2
 *     @def TEGRA186_CLK_DMIC3
 *     @def TEGRA186_CLK_DMIC4
 *     @def TEGRA186_CLK_DSPK1
 *     @def TEGRA186_CLK_DSPK2
 *     @def TEGRA186_CLK_HDA
 *     @def TEGRA186_CLK_HDA2CODEC_2X
 *     @def TEGRA186_CLK_I2S1
 *     @def TEGRA186_CLK_I2S2
 *     @def TEGRA186_CLK_I2S3
 *     @def TEGRA186_CLK_I2S4
 *     @def TEGRA186_CLK_I2S5
 *     @def TEGRA186_CLK_I2S6
 *     @def TEGRA186_CLK_MAUD
 *     @def TEGRA186_CLK_PLL_A_OUT0
 *     @def TEGRA186_CLK_SPDIF_DOUBLER
 *     @def TEGRA186_CLK_SPDIF_IN
 *     @def TEGRA186_CLK_SPDIF_OUT
 *     @def TEGRA186_CLK_SYNC_DMIC1
 *     @def TEGRA186_CLK_SYNC_DMIC2
 *     @def TEGRA186_CLK_SYNC_DMIC3
 *     @def TEGRA186_CLK_SYNC_DMIC4
 *     @def TEGRA186_CLK_SYNC_DMIC5
 *     @def TEGRA186_CLK_SYNC_DSPK1
 *     @def TEGRA186_CLK_SYNC_DSPK2
 *     @def TEGRA186_CLK_SYNC_I2S1
 *     @def TEGRA186_CLK_SYNC_I2S2
 *     @def TEGRA186_CLK_SYNC_I2S3
 *     @def TEGRA186_CLK_SYNC_I2S4
 *     @def TEGRA186_CLK_SYNC_I2S5
 *     @def TEGRA186_CLK_SYNC_I2S6
 *     @def TEGRA186_CLK_SYNC_SPDIF
 *   @पूर्ण
 *
 *   @defgroup uart_clks UART घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_AON_UART_FST_MIPI_CAL
 *     @def TEGRA186_CLK_UARTA
 *     @def TEGRA186_CLK_UARTB
 *     @def TEGRA186_CLK_UARTC
 *     @def TEGRA186_CLK_UARTD
 *     @def TEGRA186_CLK_UARTE
 *     @def TEGRA186_CLK_UARTF
 *     @def TEGRA186_CLK_UARTG
 *     @def TEGRA186_CLK_UART_FST_MIPI_CAL
 *   @पूर्ण
 *
 *   @defgroup i2c_clks I2C घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_AON_I2C_SLOW
 *     @def TEGRA186_CLK_I2C1
 *     @def TEGRA186_CLK_I2C2
 *     @def TEGRA186_CLK_I2C3
 *     @def TEGRA186_CLK_I2C4
 *     @def TEGRA186_CLK_I2C5
 *     @def TEGRA186_CLK_I2C6
 *     @def TEGRA186_CLK_I2C8
 *     @def TEGRA186_CLK_I2C9
 *     @def TEGRA186_CLK_I2C1
 *     @def TEGRA186_CLK_I2C12
 *     @def TEGRA186_CLK_I2C13
 *     @def TEGRA186_CLK_I2C14
 *     @def TEGRA186_CLK_I2C_SLOW
 *     @def TEGRA186_CLK_VI_I2C
 *   @पूर्ण
 *
 *   @defgroup spi_clks SPI घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_SPI1
 *     @def TEGRA186_CLK_SPI2
 *     @def TEGRA186_CLK_SPI3
 *     @def TEGRA186_CLK_SPI4
 *   @पूर्ण
 *
 *   @defgroup storage storage related घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_SATA
 *     @def TEGRA186_CLK_SATA_OOB
 *     @def TEGRA186_CLK_SATA_IOBIST
 *     @def TEGRA186_CLK_SDMMC_LEGACY_TM
 *     @def TEGRA186_CLK_SDMMC1
 *     @def TEGRA186_CLK_SDMMC2
 *     @def TEGRA186_CLK_SDMMC3
 *     @def TEGRA186_CLK_SDMMC4
 *     @def TEGRA186_CLK_QSPI
 *     @def TEGRA186_CLK_QSPI_OUT
 *     @def TEGRA186_CLK_UFSDEV_REF
 *     @def TEGRA186_CLK_UFSHC
 *   @पूर्ण
 *
 *   @defgroup pwm_clks PWM घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_PWM1
 *     @def TEGRA186_CLK_PWM2
 *     @def TEGRA186_CLK_PWM3
 *     @def TEGRA186_CLK_PWM4
 *     @def TEGRA186_CLK_PWM5
 *     @def TEGRA186_CLK_PWM6
 *     @def TEGRA186_CLK_PWM7
 *     @def TEGRA186_CLK_PWM8
 *   @पूर्ण
 *
 *   @defgroup plls PLLs and related घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_PLLREFE_OUT_GATED
 *     @def TEGRA186_CLK_PLLREFE_OUT1
 *     @def TEGRA186_CLK_PLLD_OUT1
 *     @def TEGRA186_CLK_PLLP_OUT0
 *     @def TEGRA186_CLK_PLLP_OUT5
 *     @def TEGRA186_CLK_PLLA
 *     @def TEGRA186_CLK_PLLE_PWRSEQ
 *     @def TEGRA186_CLK_PLLA_OUT1
 *     @def TEGRA186_CLK_PLLREFE_REF
 *     @def TEGRA186_CLK_UPHY_PLL0_PWRSEQ
 *     @def TEGRA186_CLK_UPHY_PLL1_PWRSEQ
 *     @def TEGRA186_CLK_PLLREFE_PLLE_PASSTHROUGH
 *     @def TEGRA186_CLK_PLLREFE_PEX
 *     @def TEGRA186_CLK_PLLREFE_IDDQ
 *     @def TEGRA186_CLK_PLLC_OUT_AON
 *     @def TEGRA186_CLK_PLLC_OUT_ISP
 *     @def TEGRA186_CLK_PLLC_OUT_VE
 *     @def TEGRA186_CLK_PLLC4_OUT
 *     @def TEGRA186_CLK_PLLREFE_OUT
 *     @def TEGRA186_CLK_PLLREFE_PLL_REF
 *     @def TEGRA186_CLK_PLLE
 *     @def TEGRA186_CLK_PLLC
 *     @def TEGRA186_CLK_PLLP
 *     @def TEGRA186_CLK_PLLD
 *     @def TEGRA186_CLK_PLLD2
 *     @def TEGRA186_CLK_PLLREFE_VCO
 *     @def TEGRA186_CLK_PLLC2
 *     @def TEGRA186_CLK_PLLC3
 *     @def TEGRA186_CLK_PLLDP
 *     @def TEGRA186_CLK_PLLC4_VCO
 *     @def TEGRA186_CLK_PLLA1
 *     @def TEGRA186_CLK_PLLNVCSI
 *     @def TEGRA186_CLK_PLLDISPHUB
 *     @def TEGRA186_CLK_PLLD3
 *     @def TEGRA186_CLK_PLLBPMPCAM
 *     @def TEGRA186_CLK_PLLAON
 *     @def TEGRA186_CLK_PLLU
 *     @def TEGRA186_CLK_PLLC4_VCO_DIV2
 *     @def TEGRA186_CLK_PLL_REF
 *     @def TEGRA186_CLK_PLLREFE_OUT1_DIV5
 *     @def TEGRA186_CLK_UTMIP_PLL_PWRSEQ
 *     @def TEGRA186_CLK_PLL_U_48M
 *     @def TEGRA186_CLK_PLL_U_480M
 *     @def TEGRA186_CLK_PLLC4_OUT0
 *     @def TEGRA186_CLK_PLLC4_OUT1
 *     @def TEGRA186_CLK_PLLC4_OUT2
 *     @def TEGRA186_CLK_PLLC4_OUT_MUX
 *     @def TEGRA186_CLK_DFLLDISP_DIV
 *     @def TEGRA186_CLK_PLLDISPHUB_DIV
 *     @def TEGRA186_CLK_PLLP_DIV8
 *   @पूर्ण
 *
 *   @defgroup nafll_clks NAFLL घड़ी sources
 *   @अणु
 *     @def TEGRA186_CLK_NAFLL_AXI_CBB
 *     @def TEGRA186_CLK_NAFLL_BCPU
 *     @def TEGRA186_CLK_NAFLL_BPMP
 *     @def TEGRA186_CLK_NAFLL_DISP
 *     @def TEGRA186_CLK_NAFLL_GPU
 *     @def TEGRA186_CLK_NAFLL_ISP
 *     @def TEGRA186_CLK_NAFLL_MCPU
 *     @def TEGRA186_CLK_NAFLL_NVDEC
 *     @def TEGRA186_CLK_NAFLL_NVENC
 *     @def TEGRA186_CLK_NAFLL_NVJPG
 *     @def TEGRA186_CLK_NAFLL_SCE
 *     @def TEGRA186_CLK_NAFLL_SE
 *     @def TEGRA186_CLK_NAFLL_TSEC
 *     @def TEGRA186_CLK_NAFLL_TSECB
 *     @def TEGRA186_CLK_NAFLL_VI
 *     @def TEGRA186_CLK_NAFLL_VIC
 *   @पूर्ण
 *
 *   @defgroup mphy MPHY related घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_MPHY_L0_RX_SYMB
 *     @def TEGRA186_CLK_MPHY_L0_RX_LS_BIT
 *     @def TEGRA186_CLK_MPHY_L0_TX_SYMB
 *     @def TEGRA186_CLK_MPHY_L0_TX_LS_3XBIT
 *     @def TEGRA186_CLK_MPHY_L0_RX_ANA
 *     @def TEGRA186_CLK_MPHY_L1_RX_ANA
 *     @def TEGRA186_CLK_MPHY_IOBIST
 *     @def TEGRA186_CLK_MPHY_TX_1MHZ_REF
 *     @def TEGRA186_CLK_MPHY_CORE_PLL_FIXED
 *   @पूर्ण
 *
 *   @defgroup eavb EAVB related घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_EQOS_AXI
 *     @def TEGRA186_CLK_EQOS_PTP_REF
 *     @def TEGRA186_CLK_EQOS_RX
 *     @def TEGRA186_CLK_EQOS_RX_INPUT
 *     @def TEGRA186_CLK_EQOS_TX
 *   @पूर्ण
 *
 *   @defgroup usb USB related घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_PEX_USB_PAD0_MGMT
 *     @def TEGRA186_CLK_PEX_USB_PAD1_MGMT
 *     @def TEGRA186_CLK_HSIC_TRK
 *     @def TEGRA186_CLK_USB2_TRK
 *     @def TEGRA186_CLK_USB2_HSIC_TRK
 *     @def TEGRA186_CLK_XUSB_CORE_SS
 *     @def TEGRA186_CLK_XUSB_CORE_DEV
 *     @def TEGRA186_CLK_XUSB_FALCON
 *     @def TEGRA186_CLK_XUSB_FS
 *     @def TEGRA186_CLK_XUSB
 *     @def TEGRA186_CLK_XUSB_DEV
 *     @def TEGRA186_CLK_XUSB_HOST
 *     @def TEGRA186_CLK_XUSB_SS
 *   @पूर्ण
 *
 *   @defgroup bigblock compute block related घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_GPCCLK
 *     @def TEGRA186_CLK_GPC2CLK
 *     @def TEGRA186_CLK_GPU
 *     @def TEGRA186_CLK_HOST1X
 *     @def TEGRA186_CLK_ISP
 *     @def TEGRA186_CLK_NVDEC
 *     @def TEGRA186_CLK_NVENC
 *     @def TEGRA186_CLK_NVJPG
 *     @def TEGRA186_CLK_SE
 *     @def TEGRA186_CLK_TSEC
 *     @def TEGRA186_CLK_TSECB
 *     @def TEGRA186_CLK_VIC
 *   @पूर्ण
 *
 *   @defgroup can CAN bus related घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_CAN1
 *     @def TEGRA186_CLK_CAN1_HOST
 *     @def TEGRA186_CLK_CAN2
 *     @def TEGRA186_CLK_CAN2_HOST
 *   @पूर्ण
 *
 *   @defgroup प्रणाली basic प्रणाली घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_ACTMON
 *     @def TEGRA186_CLK_AON_APB
 *     @def TEGRA186_CLK_AON_CPU_NIC
 *     @def TEGRA186_CLK_AON_NIC
 *     @def TEGRA186_CLK_AXI_CBB
 *     @def TEGRA186_CLK_BPMP_APB
 *     @def TEGRA186_CLK_BPMP_CPU_NIC
 *     @def TEGRA186_CLK_BPMP_NIC_RATE
 *     @def TEGRA186_CLK_CLK_M
 *     @def TEGRA186_CLK_EMC
 *     @def TEGRA186_CLK_MSS_ENCRYPT
 *     @def TEGRA186_CLK_SCE_APB
 *     @def TEGRA186_CLK_SCE_CPU_NIC
 *     @def TEGRA186_CLK_SCE_NIC
 *     @def TEGRA186_CLK_TSC
 *   @पूर्ण
 *
 *   @defgroup pcie_clks PCIe related घड़ीs
 *   @अणु
 *     @def TEGRA186_CLK_AFI
 *     @def TEGRA186_CLK_PCIE
 *     @def TEGRA186_CLK_PCIE2_IOBIST
 *     @def TEGRA186_CLK_PCIERX0
 *     @def TEGRA186_CLK_PCIERX1
 *     @def TEGRA186_CLK_PCIERX2
 *     @def TEGRA186_CLK_PCIERX3
 *     @def TEGRA186_CLK_PCIERX4
 *   @पूर्ण
 */

/** @brief output of gate CLK_ENB_FUSE */
#घोषणा TEGRA186_CLK_FUSE 0
/**
 * @brief It's not what you think
 * @details output of gate CLK_ENB_GPU. This output connects to the GPU
 * pwrclk. @warning: This is almost certainly not the घड़ी you think
 * it is. If you're looking क्रम the घड़ी of the graphics engine, see
 * TEGRA186_GPCCLK
 */
#घोषणा TEGRA186_CLK_GPU 1
/** @brief output of gate CLK_ENB_PCIE */
#घोषणा TEGRA186_CLK_PCIE 3
/** @brief output of the भागider IPFS_CLK_DIVISOR */
#घोषणा TEGRA186_CLK_AFI 4
/** @brief output of gate CLK_ENB_PCIE2_IOBIST */
#घोषणा TEGRA186_CLK_PCIE2_IOBIST 5
/** @brief output of gate CLK_ENB_PCIERX0*/
#घोषणा TEGRA186_CLK_PCIERX0 6
/** @brief output of gate CLK_ENB_PCIERX1*/
#घोषणा TEGRA186_CLK_PCIERX1 7
/** @brief output of gate CLK_ENB_PCIERX2*/
#घोषणा TEGRA186_CLK_PCIERX2 8
/** @brief output of gate CLK_ENB_PCIERX3*/
#घोषणा TEGRA186_CLK_PCIERX3 9
/** @brief output of gate CLK_ENB_PCIERX4*/
#घोषणा TEGRA186_CLK_PCIERX4 10
/** @brief output branch of PLL_C क्रम ISP, controlled by gate CLK_ENB_PLLC_OUT_ISP */
#घोषणा TEGRA186_CLK_PLLC_OUT_ISP 11
/** @brief output branch of PLL_C क्रम VI, controlled by gate CLK_ENB_PLLC_OUT_VE */
#घोषणा TEGRA186_CLK_PLLC_OUT_VE 12
/** @brief output branch of PLL_C क्रम AON करोमुख्य, controlled by gate CLK_ENB_PLLC_OUT_AON */
#घोषणा TEGRA186_CLK_PLLC_OUT_AON 13
/** @brief output of gate CLK_ENB_SOR_SAFE */
#घोषणा TEGRA186_CLK_SOR_SAFE 39
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2S2 */
#घोषणा TEGRA186_CLK_I2S2 42
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2S3 */
#घोषणा TEGRA186_CLK_I2S3 43
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SPDF_IN */
#घोषणा TEGRA186_CLK_SPDIF_IN 44
/** @brief output of gate CLK_ENB_SPDIF_DOUBLER */
#घोषणा TEGRA186_CLK_SPDIF_DOUBLER 45
/**  @clkdescअणुspi_clks, out, mux, CLK_RST_CONTROLLER_CLK_SOURCE_SPI3पूर्ण */
#घोषणा TEGRA186_CLK_SPI3 46
/** @clkdescअणुi2c_clks, out, mux, CLK_RST_CONTROLLER_CLK_SOURCE_I2C1पूर्ण */
#घोषणा TEGRA186_CLK_I2C1 47
/** @clkdescअणुi2c_clks, out, mux, CLK_RST_CONTROLLER_CLK_SOURCE_I2C5पूर्ण */
#घोषणा TEGRA186_CLK_I2C5 48
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SPI1 */
#घोषणा TEGRA186_CLK_SPI1 49
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_ISP */
#घोषणा TEGRA186_CLK_ISP 50
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_VI */
#घोषणा TEGRA186_CLK_VI 51
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SDMMC1 */
#घोषणा TEGRA186_CLK_SDMMC1 52
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SDMMC2 */
#घोषणा TEGRA186_CLK_SDMMC2 53
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SDMMC4 */
#घोषणा TEGRA186_CLK_SDMMC4 54
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_UARTA */
#घोषणा TEGRA186_CLK_UARTA 55
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_UARTB */
#घोषणा TEGRA186_CLK_UARTB 56
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_HOST1X */
#घोषणा TEGRA186_CLK_HOST1X 57
/**
 * @brief controls the EMC घड़ी frequency.
 * @details Doing a clk_set_rate on this घड़ी will select the
 * appropriate घड़ी source, program the source rate and execute a
 * specअगरic sequence to चयन to the new घड़ी source क्रम both memory
 * controllers. This can be used to control the balance between memory
 * throughput and memory controller घातer.
 */
#घोषणा TEGRA186_CLK_EMC 58
/* @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_EXTPERIPH4 */
#घोषणा TEGRA186_CLK_EXTPERIPH4 73
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SPI4 */
#घोषणा TEGRA186_CLK_SPI4 74
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C3 */
#घोषणा TEGRA186_CLK_I2C3 75
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SDMMC3 */
#घोषणा TEGRA186_CLK_SDMMC3 76
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_UARTD */
#घोषणा TEGRA186_CLK_UARTD 77
/** output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2S1 */
#घोषणा TEGRA186_CLK_I2S1 79
/** output of gate CLK_ENB_DTV */
#घोषणा TEGRA186_CLK_DTV 80
/** output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_TSEC */
#घोषणा TEGRA186_CLK_TSEC 81
/** @brief output of gate CLK_ENB_DP2 */
#घोषणा TEGRA186_CLK_DP2 82
/** output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2S4 */
#घोषणा TEGRA186_CLK_I2S4 84
/** output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2S5 */
#घोषणा TEGRA186_CLK_I2S5 85
/** output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C4 */
#घोषणा TEGRA186_CLK_I2C4 86
/** output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_AHUB */
#घोषणा TEGRA186_CLK_AHUB 87
/** output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_HDA2CODEC_2X */
#घोषणा TEGRA186_CLK_HDA2CODEC_2X 88
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_EXTPERIPH1 */
#घोषणा TEGRA186_CLK_EXTPERIPH1 89
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_EXTPERIPH2 */
#घोषणा TEGRA186_CLK_EXTPERIPH2 90
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_EXTPERIPH3 */
#घोषणा TEGRA186_CLK_EXTPERIPH3 91
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C_SLOW */
#घोषणा TEGRA186_CLK_I2C_SLOW 92
/** @brief output of the SOR1_CLK_SRC mux in CLK_RST_CONTROLLER_CLK_SOURCE_SOR1 */
#घोषणा TEGRA186_CLK_SOR1 93
/** @brief output of gate CLK_ENB_CEC */
#घोषणा TEGRA186_CLK_CEC 94
/** @brief output of gate CLK_ENB_DPAUX1 */
#घोषणा TEGRA186_CLK_DPAUX1 95
/** @brief output of gate CLK_ENB_DPAUX */
#घोषणा TEGRA186_CLK_DPAUX 96
/** @brief output of the SOR0_CLK_SRC mux in CLK_RST_CONTROLLER_CLK_SOURCE_SOR0 */
#घोषणा TEGRA186_CLK_SOR0 97
/** @brief output of gate CLK_ENB_HDA2HDMICODEC */
#घोषणा TEGRA186_CLK_HDA2HDMICODEC 98
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SATA */
#घोषणा TEGRA186_CLK_SATA 99
/** @brief output of gate CLK_ENB_SATA_OOB */
#घोषणा TEGRA186_CLK_SATA_OOB 100
/** @brief output of gate CLK_ENB_SATA_IOBIST */
#घोषणा TEGRA186_CLK_SATA_IOBIST 101
/** output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_HDA */
#घोषणा TEGRA186_CLK_HDA 102
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SE */
#घोषणा TEGRA186_CLK_SE 103
/** @brief output of gate CLK_ENB_APB2APE */
#घोषणा TEGRA186_CLK_APB2APE 104
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_APE */
#घोषणा TEGRA186_CLK_APE 105
/** @brief output of gate CLK_ENB_IQC1 */
#घोषणा TEGRA186_CLK_IQC1 106
/** @brief output of gate CLK_ENB_IQC2 */
#घोषणा TEGRA186_CLK_IQC2 107
/** भागide by 2 version of TEGRA186_CLK_PLLREFE_VCO */
#घोषणा TEGRA186_CLK_PLLREFE_OUT 108
/** @brief output of gate CLK_ENB_PLLREFE_PLL_REF */
#घोषणा TEGRA186_CLK_PLLREFE_PLL_REF 109
/** @brief output of gate CLK_ENB_PLLC4_OUT */
#घोषणा TEGRA186_CLK_PLLC4_OUT 110
/** @brief output of mux xusb_core_clk_चयन on page 67 of T186_Clocks_IAS.करोc */
#घोषणा TEGRA186_CLK_XUSB 111
/** controls xusb_dev_ce संकेत on page 66 and 67 of T186_Clocks_IAS.करोc */
#घोषणा TEGRA186_CLK_XUSB_DEV 112
/** controls xusb_host_ce संकेत on page 67 of T186_Clocks_IAS.करोc */
#घोषणा TEGRA186_CLK_XUSB_HOST 113
/** controls xusb_ss_ce संकेत on page 67 of T186_Clocks_IAS.करोc */
#घोषणा TEGRA186_CLK_XUSB_SS 114
/** @brief output of gate CLK_ENB_DSI */
#घोषणा TEGRA186_CLK_DSI 115
/** @brief output of gate CLK_ENB_MIPI_CAL */
#घोषणा TEGRA186_CLK_MIPI_CAL 116
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_DSIA_LP */
#घोषणा TEGRA186_CLK_DSIA_LP 117
/** @brief output of gate CLK_ENB_DSIB */
#घोषणा TEGRA186_CLK_DSIB 118
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_DSIB_LP */
#घोषणा TEGRA186_CLK_DSIB_LP 119
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_DMIC1 */
#घोषणा TEGRA186_CLK_DMIC1 122
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_DMIC2 */
#घोषणा TEGRA186_CLK_DMIC2 123
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_AUD_MCLK */
#घोषणा TEGRA186_CLK_AUD_MCLK 124
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C6 */
#घोषणा TEGRA186_CLK_I2C6 125
/**output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_UART_FST_MIPI_CAL */
#घोषणा TEGRA186_CLK_UART_FST_MIPI_CAL 126
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_VIC */
#घोषणा TEGRA186_CLK_VIC 127
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SDMMC_LEGACY_TM */
#घोषणा TEGRA186_CLK_SDMMC_LEGACY_TM 128
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_NVDEC */
#घोषणा TEGRA186_CLK_NVDEC 129
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_NVJPG */
#घोषणा TEGRA186_CLK_NVJPG 130
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_NVENC */
#घोषणा TEGRA186_CLK_NVENC 131
/** @brief output of the QSPI_CLK_SRC mux in CLK_RST_CONTROLLER_CLK_SOURCE_QSPI */
#घोषणा TEGRA186_CLK_QSPI 132
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_VI_I2C */
#घोषणा TEGRA186_CLK_VI_I2C 133
/** @brief output of gate CLK_ENB_HSIC_TRK */
#घोषणा TEGRA186_CLK_HSIC_TRK 134
/** @brief output of gate CLK_ENB_USB2_TRK */
#घोषणा TEGRA186_CLK_USB2_TRK 135
/** output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_MAUD */
#घोषणा TEGRA186_CLK_MAUD 136
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_TSECB */
#घोषणा TEGRA186_CLK_TSECB 137
/** @brief output of gate CLK_ENB_ADSP */
#घोषणा TEGRA186_CLK_ADSP 138
/** @brief output of gate CLK_ENB_ADSPNEON */
#घोषणा TEGRA186_CLK_ADSPNEON 139
/** @brief output of the भागider CLK_RST_CONTROLLER_CLK_SOURCE_MPHY_L0_RX_LS_SYMB */
#घोषणा TEGRA186_CLK_MPHY_L0_RX_SYMB 140
/** @brief output of gate CLK_ENB_MPHY_L0_RX_LS_BIT */
#घोषणा TEGRA186_CLK_MPHY_L0_RX_LS_BIT 141
/** @brief output of the भागider CLK_RST_CONTROLLER_CLK_SOURCE_MPHY_L0_TX_LS_SYMB */
#घोषणा TEGRA186_CLK_MPHY_L0_TX_SYMB 142
/** @brief output of gate CLK_ENB_MPHY_L0_TX_LS_3XBIT */
#घोषणा TEGRA186_CLK_MPHY_L0_TX_LS_3XBIT 143
/** @brief output of gate CLK_ENB_MPHY_L0_RX_ANA */
#घोषणा TEGRA186_CLK_MPHY_L0_RX_ANA 144
/** @brief output of gate CLK_ENB_MPHY_L1_RX_ANA */
#घोषणा TEGRA186_CLK_MPHY_L1_RX_ANA 145
/** @brief output of the भागider CLK_RST_CONTROLLER_CLK_SOURCE_MPHY_IOBIST */
#घोषणा TEGRA186_CLK_MPHY_IOBIST 146
/** @brief output of the भागider CLK_RST_CONTROLLER_CLK_SOURCE_MPHY_TX_1MHZ_REF */
#घोषणा TEGRA186_CLK_MPHY_TX_1MHZ_REF 147
/** @brief output of the भागider CLK_RST_CONTROLLER_CLK_SOURCE_MPHY_CORE_PLL_FIXED */
#घोषणा TEGRA186_CLK_MPHY_CORE_PLL_FIXED 148
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_AXI_CBB */
#घोषणा TEGRA186_CLK_AXI_CBB 149
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_DMIC3 */
#घोषणा TEGRA186_CLK_DMIC3 150
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_DMIC4 */
#घोषणा TEGRA186_CLK_DMIC4 151
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_DSPK1 */
#घोषणा TEGRA186_CLK_DSPK1 152
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_DSPK2 */
#घोषणा TEGRA186_CLK_DSPK2 153
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C6 */
#घोषणा TEGRA186_CLK_I2S6 154
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_NVDISPLAY_P0 */
#घोषणा TEGRA186_CLK_NVDISPLAY_P0 155
/** @brief output of the NVDISPLAY_DISP_CLK_SRC mux in CLK_RST_CONTROLLER_CLK_SOURCE_NVDISPLAY_DISP */
#घोषणा TEGRA186_CLK_NVDISPLAY_DISP 156
/** @brief output of gate CLK_ENB_NVDISPLAY_DSC */
#घोषणा TEGRA186_CLK_NVDISPLAY_DSC 157
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_NVDISPLAYHUB */
#घोषणा TEGRA186_CLK_NVDISPLAYHUB 158
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_NVDISPLAY_P1 */
#घोषणा TEGRA186_CLK_NVDISPLAY_P1 159
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_NVDISPLAY_P2 */
#घोषणा TEGRA186_CLK_NVDISPLAY_P2 160
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_TACH */
#घोषणा TEGRA186_CLK_TACH 166
/** @brief output of gate CLK_ENB_EQOS */
#घोषणा TEGRA186_CLK_EQOS_AXI 167
/** @brief output of gate CLK_ENB_EQOS_RX */
#घोषणा TEGRA186_CLK_EQOS_RX 168
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_UFSHC_CG_SYS */
#घोषणा TEGRA186_CLK_UFSHC 178
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_UFSDEV_REF */
#घोषणा TEGRA186_CLK_UFSDEV_REF 179
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_NVCSI */
#घोषणा TEGRA186_CLK_NVCSI 180
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_NVCSILP */
#घोषणा TEGRA186_CLK_NVCSILP 181
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C7 */
#घोषणा TEGRA186_CLK_I2C7 182
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C9 */
#घोषणा TEGRA186_CLK_I2C9 183
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C12 */
#घोषणा TEGRA186_CLK_I2C12 184
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C13 */
#घोषणा TEGRA186_CLK_I2C13 185
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C14 */
#घोषणा TEGRA186_CLK_I2C14 186
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_PWM1 */
#घोषणा TEGRA186_CLK_PWM1 187
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_PWM2 */
#घोषणा TEGRA186_CLK_PWM2 188
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_PWM3 */
#घोषणा TEGRA186_CLK_PWM3 189
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_PWM5 */
#घोषणा TEGRA186_CLK_PWM5 190
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_PWM6 */
#घोषणा TEGRA186_CLK_PWM6 191
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_PWM7 */
#घोषणा TEGRA186_CLK_PWM7 192
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_PWM8 */
#घोषणा TEGRA186_CLK_PWM8 193
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_UARTE */
#घोषणा TEGRA186_CLK_UARTE 194
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_UARTF */
#घोषणा TEGRA186_CLK_UARTF 195
/** @deprecated */
#घोषणा TEGRA186_CLK_DBGAPB 196
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_BPMP_CPU_NIC */
#घोषणा TEGRA186_CLK_BPMP_CPU_NIC 197
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_BPMP_APB */
#घोषणा TEGRA186_CLK_BPMP_APB 199
/** @brief output of mux controlled by TEGRA186_CLK_SOC_ACTMON */
#घोषणा TEGRA186_CLK_ACTMON 201
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_AON_CPU_NIC */
#घोषणा TEGRA186_CLK_AON_CPU_NIC 208
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_CAN1 */
#घोषणा TEGRA186_CLK_CAN1 210
/** @brief output of gate CLK_ENB_CAN1_HOST */
#घोषणा TEGRA186_CLK_CAN1_HOST 211
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_CAN2 */
#घोषणा TEGRA186_CLK_CAN2 212
/** @brief output of gate CLK_ENB_CAN2_HOST */
#घोषणा TEGRA186_CLK_CAN2_HOST 213
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_AON_APB */
#घोषणा TEGRA186_CLK_AON_APB 214
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_UARTC */
#घोषणा TEGRA186_CLK_UARTC 215
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_UARTG */
#घोषणा TEGRA186_CLK_UARTG 216
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_AON_UART_FST_MIPI_CAL */
#घोषणा TEGRA186_CLK_AON_UART_FST_MIPI_CAL 217
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C2 */
#घोषणा TEGRA186_CLK_I2C2 218
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C8 */
#घोषणा TEGRA186_CLK_I2C8 219
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_I2C10 */
#घोषणा TEGRA186_CLK_I2C10 220
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_AON_I2C_SLOW */
#घोषणा TEGRA186_CLK_AON_I2C_SLOW 221
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SPI2 */
#घोषणा TEGRA186_CLK_SPI2 222
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_DMIC5 */
#घोषणा TEGRA186_CLK_DMIC5 223
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_AON_TOUCH */
#घोषणा TEGRA186_CLK_AON_TOUCH 224
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_PWM4 */
#घोषणा TEGRA186_CLK_PWM4 225
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_TSC. This घड़ी object is पढ़ो only and is used क्रम all समयrs in the प्रणाली. */
#घोषणा TEGRA186_CLK_TSC 226
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_MSS_ENCRYPT */
#घोषणा TEGRA186_CLK_MSS_ENCRYPT 227
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SCE_CPU_NIC */
#घोषणा TEGRA186_CLK_SCE_CPU_NIC 228
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SCE_APB */
#घोषणा TEGRA186_CLK_SCE_APB 230
/** @brief output of gate CLK_ENB_DSIC */
#घोषणा TEGRA186_CLK_DSIC 231
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_DSIC_LP */
#घोषणा TEGRA186_CLK_DSIC_LP 232
/** @brief output of gate CLK_ENB_DSID */
#घोषणा TEGRA186_CLK_DSID 233
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_DSID_LP */
#घोषणा TEGRA186_CLK_DSID_LP 234
/** @brief output of the भागider CLK_RST_CONTROLLER_CLK_SOURCE_PEX_SATA_USB_RX_BYP */
#घोषणा TEGRA186_CLK_PEX_SATA_USB_RX_BYP 236
/** @brief output of mux controlled by CLK_RST_CONTROLLER_CLK_SOURCE_SPDIF_OUT */
#घोषणा TEGRA186_CLK_SPDIF_OUT 238
/** @brief output of the भागider CLK_RST_CONTROLLER_CLK_SOURCE_EQOS_PTP_REF_CLK_0 */
#घोषणा TEGRA186_CLK_EQOS_PTP_REF 239
/** @brief output of the भागider CLK_RST_CONTROLLER_CLK_SOURCE_EQOS_TX_CLK */
#घोषणा TEGRA186_CLK_EQOS_TX 240
/** @brief output of the भागider CLK_RST_CONTROLLER_CLK_SOURCE_USB2_HSIC_TRK */
#घोषणा TEGRA186_CLK_USB2_HSIC_TRK 241
/** @brief output of mux xusb_ss_clk_चयन on page 66 of T186_Clocks_IAS.करोc */
#घोषणा TEGRA186_CLK_XUSB_CORE_SS 242
/** @brief output of mux xusb_core_dev_clk_चयन on page 67 of T186_Clocks_IAS.करोc */
#घोषणा TEGRA186_CLK_XUSB_CORE_DEV 243
/** @brief output of mux xusb_core_falcon_clk_चयन on page 67 of T186_Clocks_IAS.करोc */
#घोषणा TEGRA186_CLK_XUSB_FALCON 244
/** @brief output of mux xusb_fs_clk_चयन on page 66 of T186_Clocks_IAS.करोc */
#घोषणा TEGRA186_CLK_XUSB_FS 245
/** @brief output of the भागider CLK_RST_CONTROLLER_PLLA_OUT */
#घोषणा TEGRA186_CLK_PLL_A_OUT0 246
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_I2S1 */
#घोषणा TEGRA186_CLK_SYNC_I2S1 247
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_I2S2 */
#घोषणा TEGRA186_CLK_SYNC_I2S2 248
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_I2S3 */
#घोषणा TEGRA186_CLK_SYNC_I2S3 249
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_I2S4 */
#घोषणा TEGRA186_CLK_SYNC_I2S4 250
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_I2S5 */
#घोषणा TEGRA186_CLK_SYNC_I2S5 251
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_I2S6 */
#घोषणा TEGRA186_CLK_SYNC_I2S6 252
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_DSPK1 */
#घोषणा TEGRA186_CLK_SYNC_DSPK1 253
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_DSPK2 */
#घोषणा TEGRA186_CLK_SYNC_DSPK2 254
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_DMIC1 */
#घोषणा TEGRA186_CLK_SYNC_DMIC1 255
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_DMIC2 */
#घोषणा TEGRA186_CLK_SYNC_DMIC2 256
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_DMIC3 */
#घोषणा TEGRA186_CLK_SYNC_DMIC3 257
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_DMIC4 */
#घोषणा TEGRA186_CLK_SYNC_DMIC4 259
/** @brief output of mux controlled by CLK_RST_CONTROLLER_AUDIO_SYNC_CLK_SPDIF */
#घोषणा TEGRA186_CLK_SYNC_SPDIF 260
/** @brief output of gate CLK_ENB_PLLREFE_OUT */
#घोषणा TEGRA186_CLK_PLLREFE_OUT_GATED 261
/** @brief output of the भागider PLLREFE_DIVP in CLK_RST_CONTROLLER_PLLREFE_BASE. PLLREFE has 2 outमाला_दो:
  *      * VCO/pभाग defined by this घड़ी object
  *      * VCO/2 defined by TEGRA186_CLK_PLLREFE_OUT
  */
#घोषणा TEGRA186_CLK_PLLREFE_OUT1 262
#घोषणा TEGRA186_CLK_PLLD_OUT1 267
/** @brief output of the भागider PLLP_DIVP in CLK_RST_CONTROLLER_PLLP_BASE */
#घोषणा TEGRA186_CLK_PLLP_OUT0 269
/** @brief output of the भागider CLK_RST_CONTROLLER_PLLP_OUTC */
#घोषणा TEGRA186_CLK_PLLP_OUT5 270
/** PLL controlled by CLK_RST_CONTROLLER_PLLA_BASE क्रम use by audio घड़ीs */
#घोषणा TEGRA186_CLK_PLLA 271
/** @brief output of mux controlled by CLK_RST_CONTROLLER_ACLK_BURST_POLICY भागided by the भागider controlled by ACLK_CLK_DIVISOR in CLK_RST_CONTROLLER_SUPER_ACLK_DIVIDER */
#घोषणा TEGRA186_CLK_ACLK 273
/** fixed 48MHz घड़ी भागided करोwn from TEGRA186_CLK_PLL_U */
#घोषणा TEGRA186_CLK_PLL_U_48M 274
/** fixed 480MHz घड़ी भागided करोwn from TEGRA186_CLK_PLL_U */
#घोषणा TEGRA186_CLK_PLL_U_480M 275
/** @brief output of the भागider PLLC4_DIVP in CLK_RST_CONTROLLER_PLLC4_BASE. Output frequency is TEGRA186_CLK_PLLC4_VCO/PLLC4_DIVP */
#घोषणा TEGRA186_CLK_PLLC4_OUT0 276
/** fixed /3 भागider. Output frequency of this घड़ी is TEGRA186_CLK_PLLC4_VCO/3 */
#घोषणा TEGRA186_CLK_PLLC4_OUT1 277
/** fixed /5 भागider. Output frequency of this घड़ी is TEGRA186_CLK_PLLC4_VCO/5 */
#घोषणा TEGRA186_CLK_PLLC4_OUT2 278
/** @brief output of mux controlled by PLLC4_CLK_SEL in CLK_RST_CONTROLLER_PLLC4_MISC1 */
#घोषणा TEGRA186_CLK_PLLC4_OUT_MUX 279
/** @brief output of भागider NVDISPLAY_DISP_CLK_DIVISOR in CLK_RST_CONTROLLER_CLK_SOURCE_NVDISPLAY_DISP when DFLLDISP_DIV is selected in NVDISPLAY_DISP_CLK_SRC */
#घोषणा TEGRA186_CLK_DFLLDISP_DIV 284
/** @brief output of भागider NVDISPLAY_DISP_CLK_DIVISOR in CLK_RST_CONTROLLER_CLK_SOURCE_NVDISPLAY_DISP when PLLDISPHUB_DIV is selected in NVDISPLAY_DISP_CLK_SRC */
#घोषणा TEGRA186_CLK_PLLDISPHUB_DIV 285
/** fixed /8 भागider which is used as the input क्रम TEGRA186_CLK_SOR_SAFE */
#घोषणा TEGRA186_CLK_PLLP_DIV8 286
/** @brief output of भागider CLK_RST_CONTROLLER_BPMP_NIC_RATE */
#घोषणा TEGRA186_CLK_BPMP_NIC 287
/** @brief output of the भागider CLK_RST_CONTROLLER_PLLA1_OUT1 */
#घोषणा TEGRA186_CLK_PLL_A_OUT1 288
/** @deprecated */
#घोषणा TEGRA186_CLK_GPC2CLK 289
/** A fake घड़ी which must be enabled during KFUSE पढ़ो operations to ensure adequate VDD_CORE voltage. */
#घोषणा TEGRA186_CLK_KFUSE 293
/**
 * @brief controls the PLLE hardware sequencer.
 * @details This घड़ी only has enable and disable methods. When the
 * PLLE hw sequencer is enabled, PLLE, will be enabled or disabled by
 * hw based on the control संकेतs from the PCIe, SATA and XUSB
 * घड़ीs. When the PLLE hw sequencer is disabled, the state of PLLE
 * is controlled by sw using clk_enable/clk_disable on
 * TEGRA186_CLK_PLLE.
 */
#घोषणा TEGRA186_CLK_PLLE_PWRSEQ 294
/** fixed 60MHz घड़ी भागided करोwn from, TEGRA186_CLK_PLL_U */
#घोषणा TEGRA186_CLK_PLLREFE_REF 295
/** @brief output of mux controlled by SOR0_CLK_SEL0 and SOR0_CLK_SEL1 in CLK_RST_CONTROLLER_CLK_SOURCE_SOR0 */
#घोषणा TEGRA186_CLK_SOR0_OUT 296
/** @brief output of mux controlled by SOR1_CLK_SEL0 and SOR1_CLK_SEL1 in CLK_RST_CONTROLLER_CLK_SOURCE_SOR1 */
#घोषणा TEGRA186_CLK_SOR1_OUT 297
/** @brief fixed /5 भागider.  Output frequency of this घड़ी is TEGRA186_CLK_PLLREFE_OUT1/5. Used as input क्रम TEGRA186_CLK_EQOS_AXI */
#घोषणा TEGRA186_CLK_PLLREFE_OUT1_DIV5 298
/** @brief controls the UTMIP_PLL (aka PLLU) hardware sqeuencer */
#घोषणा TEGRA186_CLK_UTMIP_PLL_PWRSEQ 301
/** @brief output of the भागider CLK_RST_CONTROLLER_CLK_SOURCE_PEX_USB_PAD_PLL0_MGMT */
#घोषणा TEGRA186_CLK_PEX_USB_PAD0_MGMT 302
/** @brief output of the भागider CLK_RST_CONTROLLER_CLK_SOURCE_PEX_USB_PAD_PLL1_MGMT */
#घोषणा TEGRA186_CLK_PEX_USB_PAD1_MGMT 303
/** @brief controls the UPHY_PLL0 hardware sqeuencer */
#घोषणा TEGRA186_CLK_UPHY_PLL0_PWRSEQ 304
/** @brief controls the UPHY_PLL1 hardware sqeuencer */
#घोषणा TEGRA186_CLK_UPHY_PLL1_PWRSEQ 305
/** @brief control क्रम PLLREFE_IDDQ in CLK_RST_CONTROLLER_PLLREFE_MISC so the bypass output even be used when the PLL is disabled */
#घोषणा TEGRA186_CLK_PLLREFE_PLLE_PASSTHROUGH 306
/** @brief output of the mux controlled by PLLREFE_SEL_CLKIN_PEX in CLK_RST_CONTROLLER_PLLREFE_MISC */
#घोषणा TEGRA186_CLK_PLLREFE_PEX 307
/** @brief control क्रम PLLREFE_IDDQ in CLK_RST_CONTROLLER_PLLREFE_MISC to turn on the PLL when enabled */
#घोषणा TEGRA186_CLK_PLLREFE_IDDQ 308
/** @brief output of the भागider QSPI_CLK_DIV2_SEL in CLK_RST_CONTROLLER_CLK_SOURCE_QSPI */
#घोषणा TEGRA186_CLK_QSPI_OUT 309
/**
 * @brief GPC2CLK-भाग-2
 * @details fixed /2 भागider. Output frequency is
 * TEGRA186_CLK_GPC2CLK/2. The frequency of this घड़ी is the
 * frequency at which the GPU graphics engine runs. */
#घोषणा TEGRA186_CLK_GPCCLK 310
/** @brief output of भागider CLK_RST_CONTROLLER_AON_NIC_RATE */
#घोषणा TEGRA186_CLK_AON_NIC 450
/** @brief output of भागider CLK_RST_CONTROLLER_SCE_NIC_RATE */
#घोषणा TEGRA186_CLK_SCE_NIC 451
/** Fixed 100MHz PLL क्रम PCIe, SATA and superspeed USB */
#घोषणा TEGRA186_CLK_PLLE 512
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLC_BASE */
#घोषणा TEGRA186_CLK_PLLC 513
/** Fixed 408MHz PLL क्रम use by peripheral घड़ीs */
#घोषणा TEGRA186_CLK_PLLP 516
/** @deprecated */
#घोषणा TEGRA186_CLK_PLL_P TEGRA186_CLK_PLLP
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLD_BASE क्रम use by DSI */
#घोषणा TEGRA186_CLK_PLLD 518
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLD2_BASE क्रम use by HDMI or DP */
#घोषणा TEGRA186_CLK_PLLD2 519
/**
 * @brief PLL controlled by CLK_RST_CONTROLLER_PLLREFE_BASE.
 * @details Note that this घड़ी only controls the VCO output, beक्रमe
 * the post-भागider. See TEGRA186_CLK_PLLREFE_OUT1 क्रम more
 * inक्रमmation.
 */
#घोषणा TEGRA186_CLK_PLLREFE_VCO 520
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLC2_BASE */
#घोषणा TEGRA186_CLK_PLLC2 521
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLC3_BASE */
#घोषणा TEGRA186_CLK_PLLC3 522
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLDP_BASE क्रम use as the DP link घड़ी */
#घोषणा TEGRA186_CLK_PLLDP 523
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLC4_BASE */
#घोषणा TEGRA186_CLK_PLLC4_VCO 524
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLA1_BASE क्रम use by audio घड़ीs */
#घोषणा TEGRA186_CLK_PLLA1 525
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLNVCSI_BASE */
#घोषणा TEGRA186_CLK_PLLNVCSI 526
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLDISPHUB_BASE */
#घोषणा TEGRA186_CLK_PLLDISPHUB 527
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLD3_BASE क्रम use by HDMI or DP */
#घोषणा TEGRA186_CLK_PLLD3 528
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLBPMPCAM_BASE */
#घोषणा TEGRA186_CLK_PLLBPMPCAM 531
/** @brief PLL controlled by CLK_RST_CONTROLLER_PLLAON_BASE क्रम use by IP blocks in the AON करोमुख्य */
#घोषणा TEGRA186_CLK_PLLAON 532
/** Fixed frequency 960MHz PLL क्रम USB and EAVB */
#घोषणा TEGRA186_CLK_PLLU 533
/** fixed /2 भागider. Output frequency is TEGRA186_CLK_PLLC4_VCO/2 */
#घोषणा TEGRA186_CLK_PLLC4_VCO_DIV2 535
/** @brief NAFLL घड़ी source क्रम AXI_CBB */
#घोषणा TEGRA186_CLK_NAFLL_AXI_CBB 564
/** @brief NAFLL घड़ी source क्रम BPMP */
#घोषणा TEGRA186_CLK_NAFLL_BPMP 565
/** @brief NAFLL घड़ी source क्रम ISP */
#घोषणा TEGRA186_CLK_NAFLL_ISP 566
/** @brief NAFLL घड़ी source क्रम NVDEC */
#घोषणा TEGRA186_CLK_NAFLL_NVDEC 567
/** @brief NAFLL घड़ी source क्रम NVENC */
#घोषणा TEGRA186_CLK_NAFLL_NVENC 568
/** @brief NAFLL घड़ी source क्रम NVJPG */
#घोषणा TEGRA186_CLK_NAFLL_NVJPG 569
/** @brief NAFLL घड़ी source क्रम SCE */
#घोषणा TEGRA186_CLK_NAFLL_SCE 570
/** @brief NAFLL घड़ी source क्रम SE */
#घोषणा TEGRA186_CLK_NAFLL_SE 571
/** @brief NAFLL घड़ी source क्रम TSEC */
#घोषणा TEGRA186_CLK_NAFLL_TSEC 572
/** @brief NAFLL घड़ी source क्रम TSECB */
#घोषणा TEGRA186_CLK_NAFLL_TSECB 573
/** @brief NAFLL घड़ी source क्रम VI */
#घोषणा TEGRA186_CLK_NAFLL_VI 574
/** @brief NAFLL घड़ी source क्रम VIC */
#घोषणा TEGRA186_CLK_NAFLL_VIC 575
/** @brief NAFLL घड़ी source क्रम DISP */
#घोषणा TEGRA186_CLK_NAFLL_DISP 576
/** @brief NAFLL घड़ी source क्रम GPU */
#घोषणा TEGRA186_CLK_NAFLL_GPU 577
/** @brief NAFLL घड़ी source क्रम M-CPU cluster */
#घोषणा TEGRA186_CLK_NAFLL_MCPU 578
/** @brief NAFLL घड़ी source क्रम B-CPU cluster */
#घोषणा TEGRA186_CLK_NAFLL_BCPU 579
/** @brief input from Tegra's CLK_32K_IN pad */
#घोषणा TEGRA186_CLK_CLK_32K 608
/** @brief output of भागider CLK_RST_CONTROLLER_CLK_M_DIVIDE */
#घोषणा TEGRA186_CLK_CLK_M 609
/** @brief output of भागider PLL_REF_DIV in CLK_RST_CONTROLLER_OSC_CTRL */
#घोषणा TEGRA186_CLK_PLL_REF 610
/** @brief input from Tegra's XTAL_IN */
#घोषणा TEGRA186_CLK_OSC 612
/** @brief घड़ी recovered from EAVB input */
#घोषणा TEGRA186_CLK_EQOS_RX_INPUT 613
/** @brief घड़ी recovered from DTV input */
#घोषणा TEGRA186_CLK_DTV_INPUT 614
/** @brief SOR0 brick output which feeds पूर्णांकo SOR0_CLK_SEL mux in CLK_RST_CONTROLLER_CLK_SOURCE_SOR0*/
#घोषणा TEGRA186_CLK_SOR0_PAD_CLKOUT 615
/** @brief SOR1 brick output which feeds पूर्णांकo SOR1_CLK_SEL mux in CLK_RST_CONTROLLER_CLK_SOURCE_SOR1*/
#घोषणा TEGRA186_CLK_SOR1_PAD_CLKOUT 616
/** @brief घड़ी recovered from I2S1 input */
#घोषणा TEGRA186_CLK_I2S1_SYNC_INPUT 617
/** @brief घड़ी recovered from I2S2 input */
#घोषणा TEGRA186_CLK_I2S2_SYNC_INPUT 618
/** @brief घड़ी recovered from I2S3 input */
#घोषणा TEGRA186_CLK_I2S3_SYNC_INPUT 619
/** @brief घड़ी recovered from I2S4 input */
#घोषणा TEGRA186_CLK_I2S4_SYNC_INPUT 620
/** @brief घड़ी recovered from I2S5 input */
#घोषणा TEGRA186_CLK_I2S5_SYNC_INPUT 621
/** @brief घड़ी recovered from I2S6 input */
#घोषणा TEGRA186_CLK_I2S6_SYNC_INPUT 622
/** @brief घड़ी recovered from SPDIFIN input */
#घोषणा TEGRA186_CLK_SPDIFIN_SYNC_INPUT 623

/**
 * @brief subject to change
 * @details maximum घड़ी identअगरier value plus one.
 */
#घोषणा TEGRA186_CLK_CLK_MAX 624

/** @पूर्ण */

#पूर्ण_अगर
