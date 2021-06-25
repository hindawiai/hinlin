<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_CL0080_H__
#घोषणा __NVIF_CL0080_H__

काष्ठा nv_device_v0 अणु
	__u8  version;
	__u8  pad01[7];
	__u64 device;	/* device identअगरier, ~0 क्रम client शेष */
पूर्ण;

#घोषणा NV_DEVICE_V0_INFO                                                  0x00
#घोषणा NV_DEVICE_V0_TIME                                                  0x01

काष्ठा nv_device_info_v0 अणु
	__u8  version;
#घोषणा NV_DEVICE_INFO_V0_IGP                                              0x00
#घोषणा NV_DEVICE_INFO_V0_PCI                                              0x01
#घोषणा NV_DEVICE_INFO_V0_AGP                                              0x02
#घोषणा NV_DEVICE_INFO_V0_PCIE                                             0x03
#घोषणा NV_DEVICE_INFO_V0_SOC                                              0x04
	__u8  platक्रमm;
	__u16 chipset;	/* from NV_PMC_BOOT_0 */
	__u8  revision;	/* from NV_PMC_BOOT_0 */
#घोषणा NV_DEVICE_INFO_V0_TNT                                              0x01
#घोषणा NV_DEVICE_INFO_V0_CELSIUS                                          0x02
#घोषणा NV_DEVICE_INFO_V0_KELVIN                                           0x03
#घोषणा NV_DEVICE_INFO_V0_RANKINE                                          0x04
#घोषणा NV_DEVICE_INFO_V0_CURIE                                            0x05
#घोषणा NV_DEVICE_INFO_V0_TESLA                                            0x06
#घोषणा NV_DEVICE_INFO_V0_FERMI                                            0x07
#घोषणा NV_DEVICE_INFO_V0_KEPLER                                           0x08
#घोषणा NV_DEVICE_INFO_V0_MAXWELL                                          0x09
#घोषणा NV_DEVICE_INFO_V0_PASCAL                                           0x0a
#घोषणा NV_DEVICE_INFO_V0_VOLTA                                            0x0b
#घोषणा NV_DEVICE_INFO_V0_TURING                                           0x0c
#घोषणा NV_DEVICE_INFO_V0_AMPERE                                           0x0d
	__u8  family;
	__u8  pad06[2];
	__u64 ram_size;
	__u64 ram_user;
	अक्षर  chip[16];
	अक्षर  name[64];
पूर्ण;

काष्ठा nv_device_info_v1 अणु
	__u8  version;
	__u8  count;
	__u8  pad02[6];
	काष्ठा nv_device_info_v1_data अणु
		__u64 mthd; /* NV_DEVICE_INFO_* (see below). */
		__u64 data;
	पूर्ण data[];
पूर्ण;

काष्ठा nv_device_समय_v0 अणु
	__u8  version;
	__u8  pad01[7];
	__u64 समय;
पूर्ण;

#घोषणा NV_DEVICE_INFO_UNIT                               (0xffffffffULL << 32)
#घोषणा NV_DEVICE_INFO(n)                          ((n) | (0x00000000ULL << 32))
#घोषणा NV_DEVICE_HOST(n)                          ((n) | (0x00000001ULL << 32))

/* This will be वापसed in the mthd field क्रम unsupported queries. */
#घोषणा NV_DEVICE_INFO_INVALID                                           ~0ULL

/* Returns the number of available runlists. */
#घोषणा NV_DEVICE_HOST_RUNLISTS                       NV_DEVICE_HOST(0x00000000)
/* Returns the number of available channels. */
#घोषणा NV_DEVICE_HOST_CHANNELS                       NV_DEVICE_HOST(0x00000001)

/* Returns a mask of available engine types on runlist(data). */
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES                NV_DEVICE_HOST(0x00000100)
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_SW                            0x00000001
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_GR                            0x00000002
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_MPEG                          0x00000004
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_ME                            0x00000008
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_CIPHER                        0x00000010
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_BSP                           0x00000020
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_VP                            0x00000040
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_CE                            0x00000080
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_SEC                           0x00000100
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_MSVLD                         0x00000200
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_MSPDEC                        0x00000400
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_MSPPP                         0x00000800
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_MSENC                         0x00001000
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_VIC                           0x00002000
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_SEC2                          0x00004000
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_NVDEC                         0x00008000
#घोषणा NV_DEVICE_HOST_RUNLIST_ENGINES_NVENC                         0x00010000
#पूर्ण_अगर
