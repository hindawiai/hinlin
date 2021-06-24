<शैली गुरु>
#अगर_अघोषित DT_BINDINGS_MEMORY_TEGRA186_MC_H
#घोषणा DT_BINDINGS_MEMORY_TEGRA186_MC_H

/* special clients */
#घोषणा TEGRA186_SID_INVALID		0x00
#घोषणा TEGRA186_SID_PASSTHROUGH	0x7f

/* host1x clients */
#घोषणा TEGRA186_SID_HOST1X		0x01
#घोषणा TEGRA186_SID_CSI		0x02
#घोषणा TEGRA186_SID_VIC		0x03
#घोषणा TEGRA186_SID_VI			0x04
#घोषणा TEGRA186_SID_ISP		0x05
#घोषणा TEGRA186_SID_NVDEC		0x06
#घोषणा TEGRA186_SID_NVENC		0x07
#घोषणा TEGRA186_SID_NVJPG		0x08
#घोषणा TEGRA186_SID_NVDISPLAY		0x09
#घोषणा TEGRA186_SID_TSEC		0x0a
#घोषणा TEGRA186_SID_TSECB		0x0b
#घोषणा TEGRA186_SID_SE			0x0c
#घोषणा TEGRA186_SID_SE1		0x0d
#घोषणा TEGRA186_SID_SE2		0x0e
#घोषणा TEGRA186_SID_SE3		0x0f

/* GPU clients */
#घोषणा TEGRA186_SID_GPU		0x10

/* other SoC clients */
#घोषणा TEGRA186_SID_AFI		0x11
#घोषणा TEGRA186_SID_HDA		0x12
#घोषणा TEGRA186_SID_ETR		0x13
#घोषणा TEGRA186_SID_EQOS		0x14
#घोषणा TEGRA186_SID_UFSHC		0x15
#घोषणा TEGRA186_SID_AON		0x16
#घोषणा TEGRA186_SID_SDMMC4		0x17
#घोषणा TEGRA186_SID_SDMMC3		0x18
#घोषणा TEGRA186_SID_SDMMC2		0x19
#घोषणा TEGRA186_SID_SDMMC1		0x1a
#घोषणा TEGRA186_SID_XUSB_HOST		0x1b
#घोषणा TEGRA186_SID_XUSB_DEV		0x1c
#घोषणा TEGRA186_SID_SATA		0x1d
#घोषणा TEGRA186_SID_APE		0x1e
#घोषणा TEGRA186_SID_SCE		0x1f

/* GPC DMA clients */
#घोषणा TEGRA186_SID_GPCDMA_0		0x20
#घोषणा TEGRA186_SID_GPCDMA_1		0x21
#घोषणा TEGRA186_SID_GPCDMA_2		0x22
#घोषणा TEGRA186_SID_GPCDMA_3		0x23
#घोषणा TEGRA186_SID_GPCDMA_4		0x24
#घोषणा TEGRA186_SID_GPCDMA_5		0x25
#घोषणा TEGRA186_SID_GPCDMA_6		0x26
#घोषणा TEGRA186_SID_GPCDMA_7		0x27

/* APE DMA clients */
#घोषणा TEGRA186_SID_APE_1		0x28
#घोषणा TEGRA186_SID_APE_2		0x29

/* camera RTCPU */
#घोषणा TEGRA186_SID_RCE		0x2a

/* camera RTCPU on host1x address space */
#घोषणा TEGRA186_SID_RCE_1X		0x2b

/* APE DMA clients */
#घोषणा TEGRA186_SID_APE_3		0x2c

/* camera RTCPU running on APE */
#घोषणा TEGRA186_SID_APE_CAM		0x2d
#घोषणा TEGRA186_SID_APE_CAM_1X		0x2e

/*
 * The BPMP has its SID value hardcoded in the firmware. Changing it requires
 * considerable efक्रमt.
 */
#घोषणा TEGRA186_SID_BPMP		0x32

/* क्रम SMMU tests */
#घोषणा TEGRA186_SID_SMMU_TEST		0x33

/* host1x भवization channels */
#घोषणा TEGRA186_SID_HOST1X_CTX0	0x38
#घोषणा TEGRA186_SID_HOST1X_CTX1	0x39
#घोषणा TEGRA186_SID_HOST1X_CTX2	0x3a
#घोषणा TEGRA186_SID_HOST1X_CTX3	0x3b
#घोषणा TEGRA186_SID_HOST1X_CTX4	0x3c
#घोषणा TEGRA186_SID_HOST1X_CTX5	0x3d
#घोषणा TEGRA186_SID_HOST1X_CTX6	0x3e
#घोषणा TEGRA186_SID_HOST1X_CTX7	0x3f

/* host1x command buffers */
#घोषणा TEGRA186_SID_HOST1X_VM0		0x40
#घोषणा TEGRA186_SID_HOST1X_VM1		0x41
#घोषणा TEGRA186_SID_HOST1X_VM2		0x42
#घोषणा TEGRA186_SID_HOST1X_VM3		0x43
#घोषणा TEGRA186_SID_HOST1X_VM4		0x44
#घोषणा TEGRA186_SID_HOST1X_VM5		0x45
#घोषणा TEGRA186_SID_HOST1X_VM6		0x46
#घोषणा TEGRA186_SID_HOST1X_VM7		0x47

/* SE data buffers */
#घोषणा TEGRA186_SID_SE_VM0		0x48
#घोषणा TEGRA186_SID_SE_VM1		0x49
#घोषणा TEGRA186_SID_SE_VM2		0x4a
#घोषणा TEGRA186_SID_SE_VM3		0x4b
#घोषणा TEGRA186_SID_SE_VM4		0x4c
#घोषणा TEGRA186_SID_SE_VM5		0x4d
#घोषणा TEGRA186_SID_SE_VM6		0x4e
#घोषणा TEGRA186_SID_SE_VM7		0x4f

/*
 * memory client IDs
 */

/* Misses from System Memory Management Unit (SMMU) Page Table Cache (PTC) */
#घोषणा TEGRA186_MEMORY_CLIENT_PTCR 0x00
/* PCIE पढ़ोs */
#घोषणा TEGRA186_MEMORY_CLIENT_AFIR 0x0e
/* High-definition audio (HDA) पढ़ोs */
#घोषणा TEGRA186_MEMORY_CLIENT_HDAR 0x15
/* Host channel data पढ़ोs */
#घोषणा TEGRA186_MEMORY_CLIENT_HOST1XDMAR 0x16
#घोषणा TEGRA186_MEMORY_CLIENT_NVENCSRD 0x1c
/* SATA पढ़ोs */
#घोषणा TEGRA186_MEMORY_CLIENT_SATAR 0x1f
/* Reads from Cortex-A9 4 CPU cores via the L2 cache */
#घोषणा TEGRA186_MEMORY_CLIENT_MPCORER 0x27
#घोषणा TEGRA186_MEMORY_CLIENT_NVENCSWR 0x2b
/* PCIE ग_लिखोs */
#घोषणा TEGRA186_MEMORY_CLIENT_AFIW 0x31
/* High-definition audio (HDA) ग_लिखोs */
#घोषणा TEGRA186_MEMORY_CLIENT_HDAW 0x35
/* Writes from Cortex-A9 4 CPU cores via the L2 cache */
#घोषणा TEGRA186_MEMORY_CLIENT_MPCOREW 0x39
/* SATA ग_लिखोs */
#घोषणा TEGRA186_MEMORY_CLIENT_SATAW 0x3d
/* ISP Read client क्रम Crossbar A */
#घोषणा TEGRA186_MEMORY_CLIENT_ISPRA 0x44
/* ISP Write client क्रम Crossbar A */
#घोषणा TEGRA186_MEMORY_CLIENT_ISPWA 0x46
/* ISP Write client Crossbar B */
#घोषणा TEGRA186_MEMORY_CLIENT_ISPWB 0x47
/* XUSB पढ़ोs */
#घोषणा TEGRA186_MEMORY_CLIENT_XUSB_HOSTR 0x4a
/* XUSB_HOST ग_लिखोs */
#घोषणा TEGRA186_MEMORY_CLIENT_XUSB_HOSTW 0x4b
/* XUSB पढ़ोs */
#घोषणा TEGRA186_MEMORY_CLIENT_XUSB_DEVR 0x4c
/* XUSB_DEV ग_लिखोs */
#घोषणा TEGRA186_MEMORY_CLIENT_XUSB_DEVW 0x4d
/* TSEC Memory Return Data Client Description */
#घोषणा TEGRA186_MEMORY_CLIENT_TSECSRD 0x54
/* TSEC Memory Write Client Description */
#घोषणा TEGRA186_MEMORY_CLIENT_TSECSWR 0x55
/* 3D, ltcx पढ़ोs instance 0 */
#घोषणा TEGRA186_MEMORY_CLIENT_GPUSRD 0x58
/* 3D, ltcx ग_लिखोs instance 0 */
#घोषणा TEGRA186_MEMORY_CLIENT_GPUSWR 0x59
/* sdmmca memory पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_SDMMCRA 0x60
/* sdmmcbmemory पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_SDMMCRAA 0x61
/* sdmmc memory पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_SDMMCR 0x62
/* sdmmcd memory पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_SDMMCRAB 0x63
/* sdmmca memory ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_SDMMCWA 0x64
/* sdmmcb memory ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_SDMMCWAA 0x65
/* sdmmc memory ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_SDMMCW 0x66
/* sdmmcd memory ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_SDMMCWAB 0x67
#घोषणा TEGRA186_MEMORY_CLIENT_VICSRD 0x6c
#घोषणा TEGRA186_MEMORY_CLIENT_VICSWR 0x6d
/* VI Write client */
#घोषणा TEGRA186_MEMORY_CLIENT_VIW 0x72
#घोषणा TEGRA186_MEMORY_CLIENT_NVDECSRD 0x78
#घोषणा TEGRA186_MEMORY_CLIENT_NVDECSWR 0x79
/* Audio Processing (APE) engine पढ़ोs */
#घोषणा TEGRA186_MEMORY_CLIENT_APER 0x7a
/* Audio Processing (APE) engine ग_लिखोs */
#घोषणा TEGRA186_MEMORY_CLIENT_APEW 0x7b
#घोषणा TEGRA186_MEMORY_CLIENT_NVJPGSRD 0x7e
#घोषणा TEGRA186_MEMORY_CLIENT_NVJPGSWR 0x7f
/* SE Memory Return Data Client Description */
#घोषणा TEGRA186_MEMORY_CLIENT_SESRD 0x80
/* SE Memory Write Client Description */
#घोषणा TEGRA186_MEMORY_CLIENT_SESWR 0x81
/* ETR पढ़ोs */
#घोषणा TEGRA186_MEMORY_CLIENT_ETRR 0x84
/* ETR ग_लिखोs */
#घोषणा TEGRA186_MEMORY_CLIENT_ETRW 0x85
/* TSECB Memory Return Data Client Description */
#घोषणा TEGRA186_MEMORY_CLIENT_TSECSRDB 0x86
/* TSECB Memory Write Client Description */
#घोषणा TEGRA186_MEMORY_CLIENT_TSECSWRB 0x87
/* 3D, ltcx पढ़ोs instance 1 */
#घोषणा TEGRA186_MEMORY_CLIENT_GPUSRD2 0x88
/* 3D, ltcx ग_लिखोs instance 1 */
#घोषणा TEGRA186_MEMORY_CLIENT_GPUSWR2 0x89
/* AXI Switch पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_AXISR 0x8c
/* AXI Switch ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_AXISW 0x8d
/* EQOS पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_EQOSR 0x8e
/* EQOS ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_EQOSW 0x8f
/* UFSHC पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_UFSHCR 0x90
/* UFSHC ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_UFSHCW 0x91
/* NVDISPLAY पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_NVDISPLAYR 0x92
/* BPMP पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_BPMPR 0x93
/* BPMP ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_BPMPW 0x94
/* BPMPDMA पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_BPMPDMAR 0x95
/* BPMPDMA ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_BPMPDMAW 0x96
/* AON पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_AONR 0x97
/* AON ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_AONW 0x98
/* AONDMA पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_AONDMAR 0x99
/* AONDMA ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_AONDMAW 0x9a
/* SCE पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_SCER 0x9b
/* SCE ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_SCEW 0x9c
/* SCEDMA पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_SCEDMAR 0x9d
/* SCEDMA ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_SCEDMAW 0x9e
/* APEDMA पढ़ो client */
#घोषणा TEGRA186_MEMORY_CLIENT_APEDMAR 0x9f
/* APEDMA ग_लिखो client */
#घोषणा TEGRA186_MEMORY_CLIENT_APEDMAW 0xa0
/* NVDISPLAY पढ़ो client instance 2 */
#घोषणा TEGRA186_MEMORY_CLIENT_NVDISPLAYR1 0xa1
#घोषणा TEGRA186_MEMORY_CLIENT_VICSRD1 0xa2
#घोषणा TEGRA186_MEMORY_CLIENT_NVDECSRD1 0xa3

#पूर्ण_अगर
