<शैली गुरु>
#अगर_अघोषित DT_BINDINGS_MEMORY_TEGRA194_MC_H
#घोषणा DT_BINDINGS_MEMORY_TEGRA194_MC_H

/* special clients */
#घोषणा TEGRA194_SID_INVALID		0x00
#घोषणा TEGRA194_SID_PASSTHROUGH	0x7f

/* host1x clients */
#घोषणा TEGRA194_SID_HOST1X		0x01
#घोषणा TEGRA194_SID_CSI		0x02
#घोषणा TEGRA194_SID_VIC		0x03
#घोषणा TEGRA194_SID_VI			0x04
#घोषणा TEGRA194_SID_ISP		0x05
#घोषणा TEGRA194_SID_NVDEC		0x06
#घोषणा TEGRA194_SID_NVENC		0x07
#घोषणा TEGRA194_SID_NVJPG		0x08
#घोषणा TEGRA194_SID_NVDISPLAY		0x09
#घोषणा TEGRA194_SID_TSEC		0x0a
#घोषणा TEGRA194_SID_TSECB		0x0b
#घोषणा TEGRA194_SID_SE			0x0c
#घोषणा TEGRA194_SID_SE1		0x0d
#घोषणा TEGRA194_SID_SE2		0x0e
#घोषणा TEGRA194_SID_SE3		0x0f

/* GPU clients */
#घोषणा TEGRA194_SID_GPU		0x10

/* other SoC clients */
#घोषणा TEGRA194_SID_AFI		0x11
#घोषणा TEGRA194_SID_HDA		0x12
#घोषणा TEGRA194_SID_ETR		0x13
#घोषणा TEGRA194_SID_EQOS		0x14
#घोषणा TEGRA194_SID_UFSHC		0x15
#घोषणा TEGRA194_SID_AON		0x16
#घोषणा TEGRA194_SID_SDMMC4		0x17
#घोषणा TEGRA194_SID_SDMMC3		0x18
#घोषणा TEGRA194_SID_SDMMC2		0x19
#घोषणा TEGRA194_SID_SDMMC1		0x1a
#घोषणा TEGRA194_SID_XUSB_HOST		0x1b
#घोषणा TEGRA194_SID_XUSB_DEV		0x1c
#घोषणा TEGRA194_SID_SATA		0x1d
#घोषणा TEGRA194_SID_APE		0x1e
#घोषणा TEGRA194_SID_SCE		0x1f

/* GPC DMA clients */
#घोषणा TEGRA194_SID_GPCDMA_0		0x20
#घोषणा TEGRA194_SID_GPCDMA_1		0x21
#घोषणा TEGRA194_SID_GPCDMA_2		0x22
#घोषणा TEGRA194_SID_GPCDMA_3		0x23
#घोषणा TEGRA194_SID_GPCDMA_4		0x24
#घोषणा TEGRA194_SID_GPCDMA_5		0x25
#घोषणा TEGRA194_SID_GPCDMA_6		0x26
#घोषणा TEGRA194_SID_GPCDMA_7		0x27

/* APE DMA clients */
#घोषणा TEGRA194_SID_APE_1		0x28
#घोषणा TEGRA194_SID_APE_2		0x29

/* camera RTCPU */
#घोषणा TEGRA194_SID_RCE		0x2a

/* camera RTCPU on host1x address space */
#घोषणा TEGRA194_SID_RCE_1X		0x2b

/* APE DMA clients */
#घोषणा TEGRA194_SID_APE_3		0x2c

/* camera RTCPU running on APE */
#घोषणा TEGRA194_SID_APE_CAM		0x2d
#घोषणा TEGRA194_SID_APE_CAM_1X		0x2e

#घोषणा TEGRA194_SID_RCE_RM		0x2f
#घोषणा TEGRA194_SID_VI_FALCON		0x30
#घोषणा TEGRA194_SID_ISP_FALCON		0x31

/*
 * The BPMP has its SID value hardcoded in the firmware. Changing it requires
 * considerable efक्रमt.
 */
#घोषणा TEGRA194_SID_BPMP		0x32

/* क्रम SMMU tests */
#घोषणा TEGRA194_SID_SMMU_TEST		0x33

/* host1x भवization channels */
#घोषणा TEGRA194_SID_HOST1X_CTX0	0x38
#घोषणा TEGRA194_SID_HOST1X_CTX1	0x39
#घोषणा TEGRA194_SID_HOST1X_CTX2	0x3a
#घोषणा TEGRA194_SID_HOST1X_CTX3	0x3b
#घोषणा TEGRA194_SID_HOST1X_CTX4	0x3c
#घोषणा TEGRA194_SID_HOST1X_CTX5	0x3d
#घोषणा TEGRA194_SID_HOST1X_CTX6	0x3e
#घोषणा TEGRA194_SID_HOST1X_CTX7	0x3f

/* host1x command buffers */
#घोषणा TEGRA194_SID_HOST1X_VM0		0x40
#घोषणा TEGRA194_SID_HOST1X_VM1		0x41
#घोषणा TEGRA194_SID_HOST1X_VM2		0x42
#घोषणा TEGRA194_SID_HOST1X_VM3		0x43
#घोषणा TEGRA194_SID_HOST1X_VM4		0x44
#घोषणा TEGRA194_SID_HOST1X_VM5		0x45
#घोषणा TEGRA194_SID_HOST1X_VM6		0x46
#घोषणा TEGRA194_SID_HOST1X_VM7		0x47

/* SE data buffers */
#घोषणा TEGRA194_SID_SE_VM0		0x48
#घोषणा TEGRA194_SID_SE_VM1		0x49
#घोषणा TEGRA194_SID_SE_VM2		0x4a
#घोषणा TEGRA194_SID_SE_VM3		0x4b
#घोषणा TEGRA194_SID_SE_VM4		0x4c
#घोषणा TEGRA194_SID_SE_VM5		0x4d
#घोषणा TEGRA194_SID_SE_VM6		0x4e
#घोषणा TEGRA194_SID_SE_VM7		0x4f

#घोषणा TEGRA194_SID_MIU		0x50

#घोषणा TEGRA194_SID_NVDLA0		0x51
#घोषणा TEGRA194_SID_NVDLA1		0x52

#घोषणा TEGRA194_SID_PVA0		0x53
#घोषणा TEGRA194_SID_PVA1		0x54
#घोषणा TEGRA194_SID_NVENC1		0x55
#घोषणा TEGRA194_SID_PCIE0		0x56
#घोषणा TEGRA194_SID_PCIE1		0x57
#घोषणा TEGRA194_SID_PCIE2		0x58
#घोषणा TEGRA194_SID_PCIE3		0x59
#घोषणा TEGRA194_SID_PCIE4		0x5a
#घोषणा TEGRA194_SID_PCIE5		0x5b
#घोषणा TEGRA194_SID_NVDEC1		0x5c

#घोषणा TEGRA194_SID_XUSB_VF0		0x5d
#घोषणा TEGRA194_SID_XUSB_VF1		0x5e
#घोषणा TEGRA194_SID_XUSB_VF2		0x5f
#घोषणा TEGRA194_SID_XUSB_VF3		0x60

#घोषणा TEGRA194_SID_RCE_VM3		0x61
#घोषणा TEGRA194_SID_VI_VM2		0x62
#घोषणा TEGRA194_SID_VI_VM3		0x63
#घोषणा TEGRA194_SID_RCE_SERVER		0x64

/*
 * memory client IDs
 */

/* Misses from System Memory Management Unit (SMMU) Page Table Cache (PTC) */
#घोषणा TEGRA194_MEMORY_CLIENT_PTCR 0x00
/* MSS पूर्णांकernal memqual MIU7 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU7R 0x01
/* MSS पूर्णांकernal memqual MIU7 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU7W 0x02
/* High-definition audio (HDA) पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_HDAR 0x15
/* Host channel data पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_HOST1XDMAR 0x16
#घोषणा TEGRA194_MEMORY_CLIENT_NVENCSRD 0x1c
/* SATA पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_SATAR 0x1f
/* Reads from Cortex-A9 4 CPU cores via the L2 cache */
#घोषणा TEGRA194_MEMORY_CLIENT_MPCORER 0x27
#घोषणा TEGRA194_MEMORY_CLIENT_NVENCSWR 0x2b
/* High-definition audio (HDA) ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_HDAW 0x35
/* Writes from Cortex-A9 4 CPU cores via the L2 cache */
#घोषणा TEGRA194_MEMORY_CLIENT_MPCOREW 0x39
/* SATA ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_SATAW 0x3d
/* ISP पढ़ो client क्रम Crossbar A */
#घोषणा TEGRA194_MEMORY_CLIENT_ISPRA 0x44
/* ISP पढ़ो client 1 क्रम Crossbar A */
#घोषणा TEGRA194_MEMORY_CLIENT_ISPFALR 0x45
/* ISP Write client क्रम Crossbar A */
#घोषणा TEGRA194_MEMORY_CLIENT_ISPWA 0x46
/* ISP Write client Crossbar B */
#घोषणा TEGRA194_MEMORY_CLIENT_ISPWB 0x47
/* XUSB_HOST पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_XUSB_HOSTR 0x4a
/* XUSB_HOST ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_XUSB_HOSTW 0x4b
/* XUSB पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_XUSB_DEVR 0x4c
/* XUSB_DEV ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_XUSB_DEVW 0x4d
/* sdmmca memory पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_SDMMCRA 0x60
/* sdmmc memory पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_SDMMCR 0x62
/* sdmmcd memory पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_SDMMCRAB 0x63
/* sdmmca memory ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_SDMMCWA 0x64
/* sdmmc memory ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_SDMMCW 0x66
/* sdmmcd memory ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_SDMMCWAB 0x67
#घोषणा TEGRA194_MEMORY_CLIENT_VICSRD 0x6c
#घोषणा TEGRA194_MEMORY_CLIENT_VICSWR 0x6d
/* VI Write client */
#घोषणा TEGRA194_MEMORY_CLIENT_VIW 0x72
#घोषणा TEGRA194_MEMORY_CLIENT_NVDECSRD 0x78
#घोषणा TEGRA194_MEMORY_CLIENT_NVDECSWR 0x79
/* Audio Processing (APE) engine पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_APER 0x7a
/* Audio Processing (APE) engine ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_APEW 0x7b
#घोषणा TEGRA194_MEMORY_CLIENT_NVJPGSRD 0x7e
#घोषणा TEGRA194_MEMORY_CLIENT_NVJPGSWR 0x7f
/* AXI AP and DFD-AUX0/1 पढ़ो clients Both share the same पूर्णांकerface on the on MSS */
#घोषणा TEGRA194_MEMORY_CLIENT_AXIAPR 0x82
/* AXI AP and DFD-AUX0/1 ग_लिखो clients Both sahre the same पूर्णांकerface on MSS */
#घोषणा TEGRA194_MEMORY_CLIENT_AXIAPW 0x83
/* ETR पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_ETRR 0x84
/* ETR ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_ETRW 0x85
/* AXI Switch पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_AXISR 0x8c
/* AXI Switch ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_AXISW 0x8d
/* EQOS पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_EQOSR 0x8e
/* EQOS ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_EQOSW 0x8f
/* UFSHC पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_UFSHCR 0x90
/* UFSHC ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_UFSHCW 0x91
/* NVDISPLAY पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_NVDISPLAYR 0x92
/* BPMP पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_BPMPR 0x93
/* BPMP ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_BPMPW 0x94
/* BPMPDMA पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_BPMPDMAR 0x95
/* BPMPDMA ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_BPMPDMAW 0x96
/* AON पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_AONR 0x97
/* AON ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_AONW 0x98
/* AONDMA पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_AONDMAR 0x99
/* AONDMA ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_AONDMAW 0x9a
/* SCE पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_SCER 0x9b
/* SCE ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_SCEW 0x9c
/* SCEDMA पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_SCEDMAR 0x9d
/* SCEDMA ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_SCEDMAW 0x9e
/* APEDMA पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_APEDMAR 0x9f
/* APEDMA ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_APEDMAW 0xa0
/* NVDISPLAY पढ़ो client instance 2 */
#घोषणा TEGRA194_MEMORY_CLIENT_NVDISPLAYR1 0xa1
#घोषणा TEGRA194_MEMORY_CLIENT_VICSRD1 0xa2
#घोषणा TEGRA194_MEMORY_CLIENT_NVDECSRD1 0xa3
/* MSS पूर्णांकernal memqual MIU0 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU0R 0xa6
/* MSS पूर्णांकernal memqual MIU0 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU0W 0xa7
/* MSS पूर्णांकernal memqual MIU1 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU1R 0xa8
/* MSS पूर्णांकernal memqual MIU1 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU1W 0xa9
/* MSS पूर्णांकernal memqual MIU2 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU2R 0xae
/* MSS पूर्णांकernal memqual MIU2 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU2W 0xaf
/* MSS पूर्णांकernal memqual MIU3 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU3R 0xb0
/* MSS पूर्णांकernal memqual MIU3 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU3W 0xb1
/* MSS पूर्णांकernal memqual MIU4 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU4R 0xb2
/* MSS पूर्णांकernal memqual MIU4 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU4W 0xb3
#घोषणा TEGRA194_MEMORY_CLIENT_DPMUR 0xb4
#घोषणा TEGRA194_MEMORY_CLIENT_DPMUW 0xb5
#घोषणा TEGRA194_MEMORY_CLIENT_NVL0R 0xb6
#घोषणा TEGRA194_MEMORY_CLIENT_NVL0W 0xb7
#घोषणा TEGRA194_MEMORY_CLIENT_NVL1R 0xb8
#घोषणा TEGRA194_MEMORY_CLIENT_NVL1W 0xb9
#घोषणा TEGRA194_MEMORY_CLIENT_NVL2R 0xba
#घोषणा TEGRA194_MEMORY_CLIENT_NVL2W 0xbb
/* VI FLACON पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_VIFALR 0xbc
/* VIFAL ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_VIFALW 0xbd
/* DLA0ARDA पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_DLA0RDA 0xbe
/* DLA0 Falcon पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_DLA0FALRDB 0xbf
/* DLA0 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_DLA0WRA 0xc0
/* DLA0 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_DLA0FALWRB 0xc1
/* DLA1ARDA पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_DLA1RDA 0xc2
/* DLA1 Falcon पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_DLA1FALRDB 0xc3
/* DLA1 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_DLA1WRA 0xc4
/* DLA1 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_DLA1FALWRB 0xc5
/* PVA0RDA पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA0RDA 0xc6
/* PVA0RDB पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA0RDB 0xc7
/* PVA0RDC पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA0RDC 0xc8
/* PVA0WRA ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA0WRA 0xc9
/* PVA0WRB ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA0WRB 0xca
/* PVA0WRC ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA0WRC 0xcb
/* PVA1RDA पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA1RDA 0xcc
/* PVA1RDB पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA1RDB 0xcd
/* PVA1RDC पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA1RDC 0xce
/* PVA1WRA ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA1WRA 0xcf
/* PVA1WRB ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA1WRB 0xd0
/* PVA1WRC ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA1WRC 0xd1
/* RCE पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_RCER 0xd2
/* RCE ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_RCEW 0xd3
/* RCEDMA पढ़ो client */
#घोषणा TEGRA194_MEMORY_CLIENT_RCEDMAR 0xd4
/* RCEDMA ग_लिखो client */
#घोषणा TEGRA194_MEMORY_CLIENT_RCEDMAW 0xd5
#घोषणा TEGRA194_MEMORY_CLIENT_NVENC1SRD 0xd6
#घोषणा TEGRA194_MEMORY_CLIENT_NVENC1SWR 0xd7
/* PCIE0 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE0R 0xd8
/* PCIE0 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE0W 0xd9
/* PCIE1 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE1R 0xda
/* PCIE1 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE1W 0xdb
/* PCIE2 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE2AR 0xdc
/* PCIE2 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE2AW 0xdd
/* PCIE3 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE3R 0xde
/* PCIE3 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE3W 0xdf
/* PCIE4 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE4R 0xe0
/* PCIE4 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE4W 0xe1
/* PCIE5 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE5R 0xe2
/* PCIE5 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE5W 0xe3
/* ISP पढ़ो client 1 क्रम Crossbar A */
#घोषणा TEGRA194_MEMORY_CLIENT_ISPFALW 0xe4
#घोषणा TEGRA194_MEMORY_CLIENT_NVL3R 0xe5
#घोषणा TEGRA194_MEMORY_CLIENT_NVL3W 0xe6
#घोषणा TEGRA194_MEMORY_CLIENT_NVL4R 0xe7
#घोषणा TEGRA194_MEMORY_CLIENT_NVL4W 0xe8
/* DLA0ARDA1 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_DLA0RDA1 0xe9
/* DLA1ARDA1 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_DLA1RDA1 0xea
/* PVA0RDA1 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA0RDA1 0xeb
/* PVA0RDB1 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA0RDB1 0xec
/* PVA1RDA1 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA1RDA1 0xed
/* PVA1RDB1 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PVA1RDB1 0xee
/* PCIE5r1 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE5R1 0xef
#घोषणा TEGRA194_MEMORY_CLIENT_NVENCSRD1 0xf0
#घोषणा TEGRA194_MEMORY_CLIENT_NVENC1SRD1 0xf1
/* ISP पढ़ो client क्रम Crossbar A */
#घोषणा TEGRA194_MEMORY_CLIENT_ISPRA1 0xf2
/* PCIE0 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_PCIE0R1 0xf3
#घोषणा TEGRA194_MEMORY_CLIENT_NVL0RHP 0xf4
#घोषणा TEGRA194_MEMORY_CLIENT_NVL1RHP 0xf5
#घोषणा TEGRA194_MEMORY_CLIENT_NVL2RHP 0xf6
#घोषणा TEGRA194_MEMORY_CLIENT_NVL3RHP 0xf7
#घोषणा TEGRA194_MEMORY_CLIENT_NVL4RHP 0xf8
#घोषणा TEGRA194_MEMORY_CLIENT_NVDEC1SRD 0xf9
#घोषणा TEGRA194_MEMORY_CLIENT_NVDEC1SRD1 0xfa
#घोषणा TEGRA194_MEMORY_CLIENT_NVDEC1SWR 0xfb
/* MSS पूर्णांकernal memqual MIU5 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU5R 0xfc
/* MSS पूर्णांकernal memqual MIU5 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU5W 0xfd
/* MSS पूर्णांकernal memqual MIU6 पढ़ो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU6R 0xfe
/* MSS पूर्णांकernal memqual MIU6 ग_लिखो clients */
#घोषणा TEGRA194_MEMORY_CLIENT_MIU6W 0xff

#पूर्ण_अगर
