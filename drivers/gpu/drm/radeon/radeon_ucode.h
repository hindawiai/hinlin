<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#अगर_अघोषित __RADEON_UCODE_H__
#घोषणा __RADEON_UCODE_H__

/* CP */
#घोषणा R600_PFP_UCODE_SIZE          576
#घोषणा R600_PM4_UCODE_SIZE          1792
#घोषणा R700_PFP_UCODE_SIZE          848
#घोषणा R700_PM4_UCODE_SIZE          1360
#घोषणा EVERGREEN_PFP_UCODE_SIZE     1120
#घोषणा EVERGREEN_PM4_UCODE_SIZE     1376
#घोषणा CAYMAN_PFP_UCODE_SIZE        2176
#घोषणा CAYMAN_PM4_UCODE_SIZE        2176
#घोषणा SI_PFP_UCODE_SIZE            2144
#घोषणा SI_PM4_UCODE_SIZE            2144
#घोषणा SI_CE_UCODE_SIZE             2144
#घोषणा CIK_PFP_UCODE_SIZE           2144
#घोषणा CIK_ME_UCODE_SIZE            2144
#घोषणा CIK_CE_UCODE_SIZE            2144

/* MEC */
#घोषणा CIK_MEC_UCODE_SIZE           4192

/* RLC */
#घोषणा R600_RLC_UCODE_SIZE          768
#घोषणा R700_RLC_UCODE_SIZE          1024
#घोषणा EVERGREEN_RLC_UCODE_SIZE     768
#घोषणा CAYMAN_RLC_UCODE_SIZE        1024
#घोषणा ARUBA_RLC_UCODE_SIZE         1536
#घोषणा SI_RLC_UCODE_SIZE            2048
#घोषणा BONAIRE_RLC_UCODE_SIZE       2048
#घोषणा KB_RLC_UCODE_SIZE            2560
#घोषणा KV_RLC_UCODE_SIZE            2560
#घोषणा ML_RLC_UCODE_SIZE            2560

/* MC */
#घोषणा BTC_MC_UCODE_SIZE            6024
#घोषणा CAYMAN_MC_UCODE_SIZE         6037
#घोषणा SI_MC_UCODE_SIZE             7769
#घोषणा TAHITI_MC_UCODE_SIZE         7808
#घोषणा PITCAIRN_MC_UCODE_SIZE       7775
#घोषणा VERDE_MC_UCODE_SIZE          7875
#घोषणा OLAND_MC_UCODE_SIZE          7863
#घोषणा BONAIRE_MC_UCODE_SIZE        7866
#घोषणा BONAIRE_MC2_UCODE_SIZE       7948
#घोषणा HAWAII_MC_UCODE_SIZE         7933
#घोषणा HAWAII_MC2_UCODE_SIZE        8091

/* SDMA */
#घोषणा CIK_SDMA_UCODE_SIZE          1050
#घोषणा CIK_SDMA_UCODE_VERSION       64

/* SMC */
#घोषणा RV770_SMC_UCODE_START        0x0100
#घोषणा RV770_SMC_UCODE_SIZE         0x410d
#घोषणा RV770_SMC_INT_VECTOR_START   0xffc0
#घोषणा RV770_SMC_INT_VECTOR_SIZE    0x0040

#घोषणा RV730_SMC_UCODE_START        0x0100
#घोषणा RV730_SMC_UCODE_SIZE         0x412c
#घोषणा RV730_SMC_INT_VECTOR_START   0xffc0
#घोषणा RV730_SMC_INT_VECTOR_SIZE    0x0040

#घोषणा RV710_SMC_UCODE_START        0x0100
#घोषणा RV710_SMC_UCODE_SIZE         0x3f1f
#घोषणा RV710_SMC_INT_VECTOR_START   0xffc0
#घोषणा RV710_SMC_INT_VECTOR_SIZE    0x0040

#घोषणा RV740_SMC_UCODE_START        0x0100
#घोषणा RV740_SMC_UCODE_SIZE         0x41c5
#घोषणा RV740_SMC_INT_VECTOR_START   0xffc0
#घोषणा RV740_SMC_INT_VECTOR_SIZE    0x0040

#घोषणा CEDAR_SMC_UCODE_START        0x0100
#घोषणा CEDAR_SMC_UCODE_SIZE         0x5d50
#घोषणा CEDAR_SMC_INT_VECTOR_START   0xffc0
#घोषणा CEDAR_SMC_INT_VECTOR_SIZE    0x0040

#घोषणा REDWOOD_SMC_UCODE_START      0x0100
#घोषणा REDWOOD_SMC_UCODE_SIZE       0x5f0a
#घोषणा REDWOOD_SMC_INT_VECTOR_START 0xffc0
#घोषणा REDWOOD_SMC_INT_VECTOR_SIZE  0x0040

#घोषणा JUNIPER_SMC_UCODE_START      0x0100
#घोषणा JUNIPER_SMC_UCODE_SIZE       0x5f1f
#घोषणा JUNIPER_SMC_INT_VECTOR_START 0xffc0
#घोषणा JUNIPER_SMC_INT_VECTOR_SIZE  0x0040

#घोषणा CYPRESS_SMC_UCODE_START      0x0100
#घोषणा CYPRESS_SMC_UCODE_SIZE       0x61f7
#घोषणा CYPRESS_SMC_INT_VECTOR_START 0xffc0
#घोषणा CYPRESS_SMC_INT_VECTOR_SIZE  0x0040

#घोषणा BARTS_SMC_UCODE_START        0x0100
#घोषणा BARTS_SMC_UCODE_SIZE         0x6107
#घोषणा BARTS_SMC_INT_VECTOR_START   0xffc0
#घोषणा BARTS_SMC_INT_VECTOR_SIZE    0x0040

#घोषणा TURKS_SMC_UCODE_START        0x0100
#घोषणा TURKS_SMC_UCODE_SIZE         0x605b
#घोषणा TURKS_SMC_INT_VECTOR_START   0xffc0
#घोषणा TURKS_SMC_INT_VECTOR_SIZE    0x0040

#घोषणा CAICOS_SMC_UCODE_START       0x0100
#घोषणा CAICOS_SMC_UCODE_SIZE        0x5fbd
#घोषणा CAICOS_SMC_INT_VECTOR_START  0xffc0
#घोषणा CAICOS_SMC_INT_VECTOR_SIZE   0x0040

#घोषणा CAYMAN_SMC_UCODE_START       0x0100
#घोषणा CAYMAN_SMC_UCODE_SIZE        0x79ec
#घोषणा CAYMAN_SMC_INT_VECTOR_START  0xffc0
#घोषणा CAYMAN_SMC_INT_VECTOR_SIZE   0x0040

#घोषणा TAHITI_SMC_UCODE_START       0x10000
#घोषणा TAHITI_SMC_UCODE_SIZE        0xf458

#घोषणा PITCAIRN_SMC_UCODE_START     0x10000
#घोषणा PITCAIRN_SMC_UCODE_SIZE      0xe9f4

#घोषणा VERDE_SMC_UCODE_START        0x10000
#घोषणा VERDE_SMC_UCODE_SIZE         0xebe4

#घोषणा OLAND_SMC_UCODE_START        0x10000
#घोषणा OLAND_SMC_UCODE_SIZE         0xe7b4

#घोषणा HAIन_अंक_SMC_UCODE_START       0x10000
#घोषणा HAIन_अंक_SMC_UCODE_SIZE        0xe67C

#घोषणा BONAIRE_SMC_UCODE_START      0x20000
#घोषणा BONAIRE_SMC_UCODE_SIZE       0x1FDEC

#घोषणा HAWAII_SMC_UCODE_START       0x20000
#घोषणा HAWAII_SMC_UCODE_SIZE        0x1FDEC

काष्ठा common_firmware_header अणु
	uपूर्णांक32_t size_bytes; /* size of the entire header+image(s) in bytes */
	uपूर्णांक32_t header_size_bytes; /* size of just the header in bytes */
	uपूर्णांक16_t header_version_major; /* header version */
	uपूर्णांक16_t header_version_minor; /* header version */
	uपूर्णांक16_t ip_version_major; /* IP version */
	uपूर्णांक16_t ip_version_minor; /* IP version */
	uपूर्णांक32_t ucode_version;
	uपूर्णांक32_t ucode_size_bytes; /* size of ucode in bytes */
	uपूर्णांक32_t ucode_array_offset_bytes; /* payload offset from the start of the header */
	uपूर्णांक32_t crc32;  /* crc32 checksum of the payload */
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा mc_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t io_debug_size_bytes; /* size of debug array in dwords */
	uपूर्णांक32_t io_debug_array_offset_bytes; /* payload offset from the start of the header */
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा smc_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t ucode_start_addr;
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा gfx_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t ucode_feature_version;
	uपूर्णांक32_t jt_offset; /* jt location */
	uपूर्णांक32_t jt_size;  /* size of jt */
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा rlc_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t ucode_feature_version;
	uपूर्णांक32_t save_and_restore_offset;
	uपूर्णांक32_t clear_state_descriptor_offset;
	uपूर्णांक32_t avail_scratch_ram_locations;
	uपूर्णांक32_t master_pkt_description_offset;
पूर्ण;

/* version_major=1, version_minor=0 */
काष्ठा sdma_firmware_header_v1_0 अणु
	काष्ठा common_firmware_header header;
	uपूर्णांक32_t ucode_feature_version;
	uपूर्णांक32_t ucode_change_version;
	uपूर्णांक32_t jt_offset; /* jt location */
	uपूर्णांक32_t jt_size; /* size of jt */
पूर्ण;

/* header is fixed size */
जोड़ radeon_firmware_header अणु
	काष्ठा common_firmware_header common;
	काष्ठा mc_firmware_header_v1_0 mc;
	काष्ठा smc_firmware_header_v1_0 smc;
	काष्ठा gfx_firmware_header_v1_0 gfx;
	काष्ठा rlc_firmware_header_v1_0 rlc;
	काष्ठा sdma_firmware_header_v1_0 sdma;
	uपूर्णांक8_t raw[0x100];
पूर्ण;

व्योम radeon_ucode_prपूर्णांक_mc_hdr(स्थिर काष्ठा common_firmware_header *hdr);
व्योम radeon_ucode_prपूर्णांक_smc_hdr(स्थिर काष्ठा common_firmware_header *hdr);
व्योम radeon_ucode_prपूर्णांक_gfx_hdr(स्थिर काष्ठा common_firmware_header *hdr);
व्योम radeon_ucode_prपूर्णांक_rlc_hdr(स्थिर काष्ठा common_firmware_header *hdr);
व्योम radeon_ucode_prपूर्णांक_sdma_hdr(स्थिर काष्ठा common_firmware_header *hdr);
पूर्णांक radeon_ucode_validate(स्थिर काष्ठा firmware *fw);

#पूर्ण_अगर
