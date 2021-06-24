<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
 *
 */
#अगर_अघोषित _AMDGPU_RAS_H
#घोषणा _AMDGPU_RAS_H

#समावेश <linux/debugfs.h>
#समावेश <linux/list.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_psp.h"
#समावेश "ta_ras_if.h"
#समावेश "amdgpu_ras_eeprom.h"

#घोषणा AMDGPU_RAS_FLAG_INIT_BY_VBIOS		(0x1 << 0)
#घोषणा AMDGPU_RAS_FLAG_INIT_NEED_RESET		(0x1 << 1)

क्रमागत amdgpu_ras_block अणु
	AMDGPU_RAS_BLOCK__UMC = 0,
	AMDGPU_RAS_BLOCK__SDMA,
	AMDGPU_RAS_BLOCK__GFX,
	AMDGPU_RAS_BLOCK__MMHUB,
	AMDGPU_RAS_BLOCK__ATHUB,
	AMDGPU_RAS_BLOCK__PCIE_BIF,
	AMDGPU_RAS_BLOCK__HDP,
	AMDGPU_RAS_BLOCK__XGMI_WAFL,
	AMDGPU_RAS_BLOCK__DF,
	AMDGPU_RAS_BLOCK__SMN,
	AMDGPU_RAS_BLOCK__SEM,
	AMDGPU_RAS_BLOCK__MP0,
	AMDGPU_RAS_BLOCK__MP1,
	AMDGPU_RAS_BLOCK__FUSE,

	AMDGPU_RAS_BLOCK__LAST
पूर्ण;

#घोषणा AMDGPU_RAS_BLOCK_COUNT	AMDGPU_RAS_BLOCK__LAST
#घोषणा AMDGPU_RAS_BLOCK_MASK	((1ULL << AMDGPU_RAS_BLOCK_COUNT) - 1)

क्रमागत amdgpu_ras_gfx_subblock अणु
	/* CPC */
	AMDGPU_RAS_BLOCK__GFX_CPC_INDEX_START = 0,
	AMDGPU_RAS_BLOCK__GFX_CPC_SCRATCH =
		AMDGPU_RAS_BLOCK__GFX_CPC_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_CPC_UCODE,
	AMDGPU_RAS_BLOCK__GFX_DC_STATE_ME1,
	AMDGPU_RAS_BLOCK__GFX_DC_CSINVOC_ME1,
	AMDGPU_RAS_BLOCK__GFX_DC_RESTORE_ME1,
	AMDGPU_RAS_BLOCK__GFX_DC_STATE_ME2,
	AMDGPU_RAS_BLOCK__GFX_DC_CSINVOC_ME2,
	AMDGPU_RAS_BLOCK__GFX_DC_RESTORE_ME2,
	AMDGPU_RAS_BLOCK__GFX_CPC_INDEX_END =
		AMDGPU_RAS_BLOCK__GFX_DC_RESTORE_ME2,
	/* CPF */
	AMDGPU_RAS_BLOCK__GFX_CPF_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_CPF_ROQ_ME2 =
		AMDGPU_RAS_BLOCK__GFX_CPF_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_CPF_ROQ_ME1,
	AMDGPU_RAS_BLOCK__GFX_CPF_TAG,
	AMDGPU_RAS_BLOCK__GFX_CPF_INDEX_END = AMDGPU_RAS_BLOCK__GFX_CPF_TAG,
	/* CPG */
	AMDGPU_RAS_BLOCK__GFX_CPG_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_CPG_DMA_ROQ =
		AMDGPU_RAS_BLOCK__GFX_CPG_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_CPG_DMA_TAG,
	AMDGPU_RAS_BLOCK__GFX_CPG_TAG,
	AMDGPU_RAS_BLOCK__GFX_CPG_INDEX_END = AMDGPU_RAS_BLOCK__GFX_CPG_TAG,
	/* GDS */
	AMDGPU_RAS_BLOCK__GFX_GDS_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_GDS_MEM = AMDGPU_RAS_BLOCK__GFX_GDS_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_GDS_INPUT_QUEUE,
	AMDGPU_RAS_BLOCK__GFX_GDS_OA_PHY_CMD_RAM_MEM,
	AMDGPU_RAS_BLOCK__GFX_GDS_OA_PHY_DATA_RAM_MEM,
	AMDGPU_RAS_BLOCK__GFX_GDS_OA_PIPE_MEM,
	AMDGPU_RAS_BLOCK__GFX_GDS_INDEX_END =
		AMDGPU_RAS_BLOCK__GFX_GDS_OA_PIPE_MEM,
	/* SPI */
	AMDGPU_RAS_BLOCK__GFX_SPI_SR_MEM,
	/* SQ */
	AMDGPU_RAS_BLOCK__GFX_SQ_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_SQ_SGPR = AMDGPU_RAS_BLOCK__GFX_SQ_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_SQ_LDS_D,
	AMDGPU_RAS_BLOCK__GFX_SQ_LDS_I,
	AMDGPU_RAS_BLOCK__GFX_SQ_VGPR,
	AMDGPU_RAS_BLOCK__GFX_SQ_INDEX_END = AMDGPU_RAS_BLOCK__GFX_SQ_VGPR,
	/* SQC (3 ranges) */
	AMDGPU_RAS_BLOCK__GFX_SQC_INDEX_START,
	/* SQC range 0 */
	AMDGPU_RAS_BLOCK__GFX_SQC_INDEX0_START =
		AMDGPU_RAS_BLOCK__GFX_SQC_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_SQC_INST_UTCL1_LFIFO =
		AMDGPU_RAS_BLOCK__GFX_SQC_INDEX0_START,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_CU0_WRITE_DATA_BUF,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_CU0_UTCL1_LFIFO,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_CU1_WRITE_DATA_BUF,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_CU1_UTCL1_LFIFO,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_CU2_WRITE_DATA_BUF,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_CU2_UTCL1_LFIFO,
	AMDGPU_RAS_BLOCK__GFX_SQC_INDEX0_END =
		AMDGPU_RAS_BLOCK__GFX_SQC_DATA_CU2_UTCL1_LFIFO,
	/* SQC range 1 */
	AMDGPU_RAS_BLOCK__GFX_SQC_INDEX1_START,
	AMDGPU_RAS_BLOCK__GFX_SQC_INST_BANKA_TAG_RAM =
		AMDGPU_RAS_BLOCK__GFX_SQC_INDEX1_START,
	AMDGPU_RAS_BLOCK__GFX_SQC_INST_BANKA_UTCL1_MISS_FIFO,
	AMDGPU_RAS_BLOCK__GFX_SQC_INST_BANKA_MISS_FIFO,
	AMDGPU_RAS_BLOCK__GFX_SQC_INST_BANKA_BANK_RAM,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_BANKA_TAG_RAM,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_BANKA_HIT_FIFO,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_BANKA_MISS_FIFO,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_BANKA_सूचीTY_BIT_RAM,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_BANKA_BANK_RAM,
	AMDGPU_RAS_BLOCK__GFX_SQC_INDEX1_END =
		AMDGPU_RAS_BLOCK__GFX_SQC_DATA_BANKA_BANK_RAM,
	/* SQC range 2 */
	AMDGPU_RAS_BLOCK__GFX_SQC_INDEX2_START,
	AMDGPU_RAS_BLOCK__GFX_SQC_INST_BANKB_TAG_RAM =
		AMDGPU_RAS_BLOCK__GFX_SQC_INDEX2_START,
	AMDGPU_RAS_BLOCK__GFX_SQC_INST_BANKB_UTCL1_MISS_FIFO,
	AMDGPU_RAS_BLOCK__GFX_SQC_INST_BANKB_MISS_FIFO,
	AMDGPU_RAS_BLOCK__GFX_SQC_INST_BANKB_BANK_RAM,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_BANKB_TAG_RAM,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_BANKB_HIT_FIFO,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_BANKB_MISS_FIFO,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_BANKB_सूचीTY_BIT_RAM,
	AMDGPU_RAS_BLOCK__GFX_SQC_DATA_BANKB_BANK_RAM,
	AMDGPU_RAS_BLOCK__GFX_SQC_INDEX2_END =
		AMDGPU_RAS_BLOCK__GFX_SQC_DATA_BANKB_BANK_RAM,
	AMDGPU_RAS_BLOCK__GFX_SQC_INDEX_END =
		AMDGPU_RAS_BLOCK__GFX_SQC_INDEX2_END,
	/* TA */
	AMDGPU_RAS_BLOCK__GFX_TA_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_TA_FS_DFIFO =
		AMDGPU_RAS_BLOCK__GFX_TA_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_TA_FS_AFIFO,
	AMDGPU_RAS_BLOCK__GFX_TA_FL_LFIFO,
	AMDGPU_RAS_BLOCK__GFX_TA_FX_LFIFO,
	AMDGPU_RAS_BLOCK__GFX_TA_FS_CFIFO,
	AMDGPU_RAS_BLOCK__GFX_TA_INDEX_END = AMDGPU_RAS_BLOCK__GFX_TA_FS_CFIFO,
	/* TCA */
	AMDGPU_RAS_BLOCK__GFX_TCA_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_TCA_HOLE_FIFO =
		AMDGPU_RAS_BLOCK__GFX_TCA_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_TCA_REQ_FIFO,
	AMDGPU_RAS_BLOCK__GFX_TCA_INDEX_END =
		AMDGPU_RAS_BLOCK__GFX_TCA_REQ_FIFO,
	/* TCC (5 sub-ranges) */
	AMDGPU_RAS_BLOCK__GFX_TCC_INDEX_START,
	/* TCC range 0 */
	AMDGPU_RAS_BLOCK__GFX_TCC_INDEX0_START =
		AMDGPU_RAS_BLOCK__GFX_TCC_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_TCC_CACHE_DATA =
		AMDGPU_RAS_BLOCK__GFX_TCC_INDEX0_START,
	AMDGPU_RAS_BLOCK__GFX_TCC_CACHE_DATA_BANK_0_1,
	AMDGPU_RAS_BLOCK__GFX_TCC_CACHE_DATA_BANK_1_0,
	AMDGPU_RAS_BLOCK__GFX_TCC_CACHE_DATA_BANK_1_1,
	AMDGPU_RAS_BLOCK__GFX_TCC_CACHE_सूचीTY_BANK_0,
	AMDGPU_RAS_BLOCK__GFX_TCC_CACHE_सूचीTY_BANK_1,
	AMDGPU_RAS_BLOCK__GFX_TCC_HIGH_RATE_TAG,
	AMDGPU_RAS_BLOCK__GFX_TCC_LOW_RATE_TAG,
	AMDGPU_RAS_BLOCK__GFX_TCC_INDEX0_END =
		AMDGPU_RAS_BLOCK__GFX_TCC_LOW_RATE_TAG,
	/* TCC range 1 */
	AMDGPU_RAS_BLOCK__GFX_TCC_INDEX1_START,
	AMDGPU_RAS_BLOCK__GFX_TCC_IN_USE_DEC =
		AMDGPU_RAS_BLOCK__GFX_TCC_INDEX1_START,
	AMDGPU_RAS_BLOCK__GFX_TCC_IN_USE_TRANSFER,
	AMDGPU_RAS_BLOCK__GFX_TCC_INDEX1_END =
		AMDGPU_RAS_BLOCK__GFX_TCC_IN_USE_TRANSFER,
	/* TCC range 2 */
	AMDGPU_RAS_BLOCK__GFX_TCC_INDEX2_START,
	AMDGPU_RAS_BLOCK__GFX_TCC_RETURN_DATA =
		AMDGPU_RAS_BLOCK__GFX_TCC_INDEX2_START,
	AMDGPU_RAS_BLOCK__GFX_TCC_RETURN_CONTROL,
	AMDGPU_RAS_BLOCK__GFX_TCC_UC_ATOMIC_FIFO,
	AMDGPU_RAS_BLOCK__GFX_TCC_WRITE_RETURN,
	AMDGPU_RAS_BLOCK__GFX_TCC_WRITE_CACHE_READ,
	AMDGPU_RAS_BLOCK__GFX_TCC_SRC_FIFO,
	AMDGPU_RAS_BLOCK__GFX_TCC_SRC_FIFO_NEXT_RAM,
	AMDGPU_RAS_BLOCK__GFX_TCC_CACHE_TAG_PROBE_FIFO,
	AMDGPU_RAS_BLOCK__GFX_TCC_INDEX2_END =
		AMDGPU_RAS_BLOCK__GFX_TCC_CACHE_TAG_PROBE_FIFO,
	/* TCC range 3 */
	AMDGPU_RAS_BLOCK__GFX_TCC_INDEX3_START,
	AMDGPU_RAS_BLOCK__GFX_TCC_LATENCY_FIFO =
		AMDGPU_RAS_BLOCK__GFX_TCC_INDEX3_START,
	AMDGPU_RAS_BLOCK__GFX_TCC_LATENCY_FIFO_NEXT_RAM,
	AMDGPU_RAS_BLOCK__GFX_TCC_INDEX3_END =
		AMDGPU_RAS_BLOCK__GFX_TCC_LATENCY_FIFO_NEXT_RAM,
	/* TCC range 4 */
	AMDGPU_RAS_BLOCK__GFX_TCC_INDEX4_START,
	AMDGPU_RAS_BLOCK__GFX_TCC_WRRET_TAG_WRITE_RETURN =
		AMDGPU_RAS_BLOCK__GFX_TCC_INDEX4_START,
	AMDGPU_RAS_BLOCK__GFX_TCC_ATOMIC_RETURN_BUFFER,
	AMDGPU_RAS_BLOCK__GFX_TCC_INDEX4_END =
		AMDGPU_RAS_BLOCK__GFX_TCC_ATOMIC_RETURN_BUFFER,
	AMDGPU_RAS_BLOCK__GFX_TCC_INDEX_END =
		AMDGPU_RAS_BLOCK__GFX_TCC_INDEX4_END,
	/* TCI */
	AMDGPU_RAS_BLOCK__GFX_TCI_WRITE_RAM,
	/* TCP */
	AMDGPU_RAS_BLOCK__GFX_TCP_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_TCP_CACHE_RAM =
		AMDGPU_RAS_BLOCK__GFX_TCP_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_TCP_LFIFO_RAM,
	AMDGPU_RAS_BLOCK__GFX_TCP_CMD_FIFO,
	AMDGPU_RAS_BLOCK__GFX_TCP_VM_FIFO,
	AMDGPU_RAS_BLOCK__GFX_TCP_DB_RAM,
	AMDGPU_RAS_BLOCK__GFX_TCP_UTCL1_LFIFO0,
	AMDGPU_RAS_BLOCK__GFX_TCP_UTCL1_LFIFO1,
	AMDGPU_RAS_BLOCK__GFX_TCP_INDEX_END =
		AMDGPU_RAS_BLOCK__GFX_TCP_UTCL1_LFIFO1,
	/* TD */
	AMDGPU_RAS_BLOCK__GFX_TD_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_TD_SS_FIFO_LO =
		AMDGPU_RAS_BLOCK__GFX_TD_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_TD_SS_FIFO_HI,
	AMDGPU_RAS_BLOCK__GFX_TD_CS_FIFO,
	AMDGPU_RAS_BLOCK__GFX_TD_INDEX_END = AMDGPU_RAS_BLOCK__GFX_TD_CS_FIFO,
	/* EA (3 sub-ranges) */
	AMDGPU_RAS_BLOCK__GFX_EA_INDEX_START,
	/* EA range 0 */
	AMDGPU_RAS_BLOCK__GFX_EA_INDEX0_START =
		AMDGPU_RAS_BLOCK__GFX_EA_INDEX_START,
	AMDGPU_RAS_BLOCK__GFX_EA_DRAMRD_CMDMEM =
		AMDGPU_RAS_BLOCK__GFX_EA_INDEX0_START,
	AMDGPU_RAS_BLOCK__GFX_EA_DRAMWR_CMDMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_DRAMWR_DATAMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_RRET_TAGMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_WRET_TAGMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_GMIRD_CMDMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_GMIWR_CMDMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_GMIWR_DATAMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_INDEX0_END =
		AMDGPU_RAS_BLOCK__GFX_EA_GMIWR_DATAMEM,
	/* EA range 1 */
	AMDGPU_RAS_BLOCK__GFX_EA_INDEX1_START,
	AMDGPU_RAS_BLOCK__GFX_EA_DRAMRD_PAGEMEM =
		AMDGPU_RAS_BLOCK__GFX_EA_INDEX1_START,
	AMDGPU_RAS_BLOCK__GFX_EA_DRAMWR_PAGEMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_IORD_CMDMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_IOWR_CMDMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_IOWR_DATAMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_GMIRD_PAGEMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_GMIWR_PAGEMEM,
	AMDGPU_RAS_BLOCK__GFX_EA_INDEX1_END =
		AMDGPU_RAS_BLOCK__GFX_EA_GMIWR_PAGEMEM,
	/* EA range 2 */
	AMDGPU_RAS_BLOCK__GFX_EA_INDEX2_START,
	AMDGPU_RAS_BLOCK__GFX_EA_MAM_D0MEM =
		AMDGPU_RAS_BLOCK__GFX_EA_INDEX2_START,
	AMDGPU_RAS_BLOCK__GFX_EA_MAM_D1MEM,
	AMDGPU_RAS_BLOCK__GFX_EA_MAM_D2MEM,
	AMDGPU_RAS_BLOCK__GFX_EA_MAM_D3MEM,
	AMDGPU_RAS_BLOCK__GFX_EA_INDEX2_END =
		AMDGPU_RAS_BLOCK__GFX_EA_MAM_D3MEM,
	AMDGPU_RAS_BLOCK__GFX_EA_INDEX_END =
		AMDGPU_RAS_BLOCK__GFX_EA_INDEX2_END,
	/* UTC VM L2 bank */
	AMDGPU_RAS_BLOCK__UTC_VML2_BANK_CACHE,
	/* UTC VM walker */
	AMDGPU_RAS_BLOCK__UTC_VML2_WALKER,
	/* UTC ATC L2 2MB cache */
	AMDGPU_RAS_BLOCK__UTC_ATCL2_CACHE_2M_BANK,
	/* UTC ATC L2 4KB cache */
	AMDGPU_RAS_BLOCK__UTC_ATCL2_CACHE_4K_BANK,
	AMDGPU_RAS_BLOCK__GFX_MAX
पूर्ण;

क्रमागत amdgpu_ras_error_type अणु
	AMDGPU_RAS_ERROR__NONE							= 0,
	AMDGPU_RAS_ERROR__PARITY						= 1,
	AMDGPU_RAS_ERROR__SINGLE_CORRECTABLE					= 2,
	AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE					= 4,
	AMDGPU_RAS_ERROR__POISON						= 8,
पूर्ण;

क्रमागत amdgpu_ras_ret अणु
	AMDGPU_RAS_SUCCESS = 0,
	AMDGPU_RAS_FAIL,
	AMDGPU_RAS_UE,
	AMDGPU_RAS_CE,
	AMDGPU_RAS_PT,
पूर्ण;

काष्ठा ras_common_अगर अणु
	क्रमागत amdgpu_ras_block block;
	क्रमागत amdgpu_ras_error_type type;
	uपूर्णांक32_t sub_block_index;
	/* block name */
	अक्षर name[32];
पूर्ण;

काष्ठा amdgpu_ras अणु
	/* ras infraकाष्ठाure */
	/* क्रम ras itself. */
	uपूर्णांक32_t hw_supported;
	/* क्रम IP to check its ras ability. */
	uपूर्णांक32_t supported;
	uपूर्णांक32_t features;
	काष्ठा list_head head;
	/* sysfs */
	काष्ठा device_attribute features_attr;
	काष्ठा bin_attribute badpages_attr;
	/* block array */
	काष्ठा ras_manager *objs;

	/* gpu recovery */
	काष्ठा work_काष्ठा recovery_work;
	atomic_t in_recovery;
	काष्ठा amdgpu_device *adev;
	/* error handler data */
	काष्ठा ras_err_handler_data *eh_data;
	काष्ठा mutex recovery_lock;

	uपूर्णांक32_t flags;
	bool reboot;
	काष्ठा amdgpu_ras_eeprom_control eeprom_control;

	bool error_query_पढ़ोy;

	/* bad page count threshold */
	uपूर्णांक32_t bad_page_cnt_threshold;

	/* disable ras error count harvest in recovery */
	bool disable_ras_err_cnt_harvest;
पूर्ण;

काष्ठा ras_fs_data अणु
	अक्षर sysfs_name[32];
	अक्षर debugfs_name[32];
पूर्ण;

काष्ठा ras_err_data अणु
	अचिन्हित दीर्घ ue_count;
	अचिन्हित दीर्घ ce_count;
	अचिन्हित दीर्घ err_addr_cnt;
	काष्ठा eeprom_table_record *err_addr;
पूर्ण;

काष्ठा ras_err_handler_data अणु
	/* poपूर्णांक to bad page records array */
	काष्ठा eeprom_table_record *bps;
	/* the count of entries */
	पूर्णांक count;
	/* the space can place new entries */
	पूर्णांक space_left;
पूर्ण;

प्रकार पूर्णांक (*ras_ih_cb)(काष्ठा amdgpu_device *adev,
		व्योम *err_data,
		काष्ठा amdgpu_iv_entry *entry);

काष्ठा ras_ih_data अणु
	/* पूर्णांकerrupt bottom half */
	काष्ठा work_काष्ठा ih_work;
	पूर्णांक inuse;
	/* IP callback */
	ras_ih_cb cb;
	/* full of entries */
	अचिन्हित अक्षर *ring;
	अचिन्हित पूर्णांक ring_size;
	अचिन्हित पूर्णांक element_size;
	अचिन्हित पूर्णांक aligned_element_size;
	अचिन्हित पूर्णांक rptr;
	अचिन्हित पूर्णांक wptr;
पूर्ण;

काष्ठा ras_manager अणु
	काष्ठा ras_common_अगर head;
	/* reference count */
	पूर्णांक use;
	/* ras block link */
	काष्ठा list_head node;
	/* the device */
	काष्ठा amdgpu_device *adev;
	/* sysfs */
	काष्ठा device_attribute sysfs_attr;
	पूर्णांक attr_inuse;

	/* fs node name */
	काष्ठा ras_fs_data fs_data;

	/* IH data */
	काष्ठा ras_ih_data ih_data;

	काष्ठा ras_err_data err_data;
पूर्ण;

काष्ठा ras_badpage अणु
	अचिन्हित पूर्णांक bp;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक flags;
पूर्ण;

/* पूर्णांकerfaces क्रम IP */
काष्ठा ras_fs_अगर अणु
	काष्ठा ras_common_अगर head;
	अक्षर sysfs_name[32];
	अक्षर debugfs_name[32];
पूर्ण;

काष्ठा ras_query_अगर अणु
	काष्ठा ras_common_अगर head;
	अचिन्हित दीर्घ ue_count;
	अचिन्हित दीर्घ ce_count;
पूर्ण;

काष्ठा ras_inject_अगर अणु
	काष्ठा ras_common_अगर head;
	uपूर्णांक64_t address;
	uपूर्णांक64_t value;
पूर्ण;

काष्ठा ras_cure_अगर अणु
	काष्ठा ras_common_अगर head;
	uपूर्णांक64_t address;
पूर्ण;

काष्ठा ras_ih_अगर अणु
	काष्ठा ras_common_अगर head;
	ras_ih_cb cb;
पूर्ण;

काष्ठा ras_dispatch_अगर अणु
	काष्ठा ras_common_अगर head;
	काष्ठा amdgpu_iv_entry *entry;
पूर्ण;

काष्ठा ras_debug_अगर अणु
	जोड़ अणु
		काष्ठा ras_common_अगर head;
		काष्ठा ras_inject_अगर inject;
	पूर्ण;
	पूर्णांक op;
पूर्ण;
/* work flow
 * vbios
 * 1: ras feature enable (enabled by शेष)
 * psp
 * 2: ras framework init (in ip_init)
 * IP
 * 3: IH add
 * 4: debugfs/sysfs create
 * 5: query/inject
 * 6: debugfs/sysfs हटाओ
 * 7: IH हटाओ
 * 8: feature disable
 */

#घोषणा amdgpu_ras_get_context(adev)		((adev)->psp.ras.ras)
#घोषणा amdgpu_ras_set_context(adev, ras_con)	((adev)->psp.ras.ras = (ras_con))

/* check अगर ras is supported on block, say, sdma, gfx */
अटल अंतरभूत पूर्णांक amdgpu_ras_is_supported(काष्ठा amdgpu_device *adev,
		अचिन्हित पूर्णांक block)
अणु
	काष्ठा amdgpu_ras *ras = amdgpu_ras_get_context(adev);

	अगर (block >= AMDGPU_RAS_BLOCK_COUNT)
		वापस 0;
	वापस ras && (ras->supported & (1 << block));
पूर्ण

पूर्णांक amdgpu_ras_recovery_init(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_ras_request_reset_on_boot(काष्ठा amdgpu_device *adev,
		अचिन्हित पूर्णांक block);

व्योम amdgpu_ras_resume(काष्ठा amdgpu_device *adev);
व्योम amdgpu_ras_suspend(काष्ठा amdgpu_device *adev);

अचिन्हित दीर्घ amdgpu_ras_query_error_count(काष्ठा amdgpu_device *adev,
		bool is_ce);

/* error handling functions */
पूर्णांक amdgpu_ras_add_bad_pages(काष्ठा amdgpu_device *adev,
		काष्ठा eeprom_table_record *bps, पूर्णांक pages);

पूर्णांक amdgpu_ras_save_bad_pages(काष्ठा amdgpu_device *adev);

अटल अंतरभूत पूर्णांक amdgpu_ras_reset_gpu(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *ras = amdgpu_ras_get_context(adev);

	अगर (atomic_cmpxchg(&ras->in_recovery, 0, 1) == 0)
		schedule_work(&ras->recovery_work);
	वापस 0;
पूर्ण

अटल अंतरभूत क्रमागत ta_ras_block
amdgpu_ras_block_to_ta(क्रमागत amdgpu_ras_block block) अणु
	चयन (block) अणु
	हाल AMDGPU_RAS_BLOCK__UMC:
		वापस TA_RAS_BLOCK__UMC;
	हाल AMDGPU_RAS_BLOCK__SDMA:
		वापस TA_RAS_BLOCK__SDMA;
	हाल AMDGPU_RAS_BLOCK__GFX:
		वापस TA_RAS_BLOCK__GFX;
	हाल AMDGPU_RAS_BLOCK__MMHUB:
		वापस TA_RAS_BLOCK__MMHUB;
	हाल AMDGPU_RAS_BLOCK__ATHUB:
		वापस TA_RAS_BLOCK__ATHUB;
	हाल AMDGPU_RAS_BLOCK__PCIE_BIF:
		वापस TA_RAS_BLOCK__PCIE_BIF;
	हाल AMDGPU_RAS_BLOCK__HDP:
		वापस TA_RAS_BLOCK__HDP;
	हाल AMDGPU_RAS_BLOCK__XGMI_WAFL:
		वापस TA_RAS_BLOCK__XGMI_WAFL;
	हाल AMDGPU_RAS_BLOCK__DF:
		वापस TA_RAS_BLOCK__DF;
	हाल AMDGPU_RAS_BLOCK__SMN:
		वापस TA_RAS_BLOCK__SMN;
	हाल AMDGPU_RAS_BLOCK__SEM:
		वापस TA_RAS_BLOCK__SEM;
	हाल AMDGPU_RAS_BLOCK__MP0:
		वापस TA_RAS_BLOCK__MP0;
	हाल AMDGPU_RAS_BLOCK__MP1:
		वापस TA_RAS_BLOCK__MP1;
	हाल AMDGPU_RAS_BLOCK__FUSE:
		वापस TA_RAS_BLOCK__FUSE;
	शेष:
		WARN_ONCE(1, "RAS ERROR: unexpected block id %d\n", block);
		वापस TA_RAS_BLOCK__UMC;
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत ta_ras_error_type
amdgpu_ras_error_to_ta(क्रमागत amdgpu_ras_error_type error) अणु
	चयन (error) अणु
	हाल AMDGPU_RAS_ERROR__NONE:
		वापस TA_RAS_ERROR__NONE;
	हाल AMDGPU_RAS_ERROR__PARITY:
		वापस TA_RAS_ERROR__PARITY;
	हाल AMDGPU_RAS_ERROR__SINGLE_CORRECTABLE:
		वापस TA_RAS_ERROR__SINGLE_CORRECTABLE;
	हाल AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE:
		वापस TA_RAS_ERROR__MULTI_UNCORRECTABLE;
	हाल AMDGPU_RAS_ERROR__POISON:
		वापस TA_RAS_ERROR__POISON;
	शेष:
		WARN_ONCE(1, "RAS ERROR: unexpected error type %d\n", error);
		वापस TA_RAS_ERROR__NONE;
	पूर्ण
पूर्ण

/* called in ip_init and ip_fini */
पूर्णांक amdgpu_ras_init(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_ras_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_ras_pre_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_ras_late_init(काष्ठा amdgpu_device *adev,
			 काष्ठा ras_common_अगर *ras_block,
			 काष्ठा ras_fs_अगर *fs_info,
			 काष्ठा ras_ih_अगर *ih_info);
व्योम amdgpu_ras_late_fini(काष्ठा amdgpu_device *adev,
			  काष्ठा ras_common_अगर *ras_block,
			  काष्ठा ras_ih_अगर *ih_info);

पूर्णांक amdgpu_ras_feature_enable(काष्ठा amdgpu_device *adev,
		काष्ठा ras_common_अगर *head, bool enable);

पूर्णांक amdgpu_ras_feature_enable_on_boot(काष्ठा amdgpu_device *adev,
		काष्ठा ras_common_अगर *head, bool enable);

पूर्णांक amdgpu_ras_sysfs_create(काष्ठा amdgpu_device *adev,
		काष्ठा ras_fs_अगर *head);

पूर्णांक amdgpu_ras_sysfs_हटाओ(काष्ठा amdgpu_device *adev,
		काष्ठा ras_common_अगर *head);

व्योम amdgpu_ras_debugfs_create_all(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_ras_query_error_status(काष्ठा amdgpu_device *adev,
		काष्ठा ras_query_अगर *info);

पूर्णांक amdgpu_ras_reset_error_status(काष्ठा amdgpu_device *adev,
		क्रमागत amdgpu_ras_block block);

पूर्णांक amdgpu_ras_error_inject(काष्ठा amdgpu_device *adev,
		काष्ठा ras_inject_अगर *info);

पूर्णांक amdgpu_ras_पूर्णांकerrupt_add_handler(काष्ठा amdgpu_device *adev,
		काष्ठा ras_ih_अगर *info);

पूर्णांक amdgpu_ras_पूर्णांकerrupt_हटाओ_handler(काष्ठा amdgpu_device *adev,
		काष्ठा ras_ih_अगर *info);

पूर्णांक amdgpu_ras_पूर्णांकerrupt_dispatch(काष्ठा amdgpu_device *adev,
		काष्ठा ras_dispatch_अगर *info);

काष्ठा ras_manager *amdgpu_ras_find_obj(काष्ठा amdgpu_device *adev,
		काष्ठा ras_common_अगर *head);

बाह्य atomic_t amdgpu_ras_in_पूर्णांकr;

अटल अंतरभूत bool amdgpu_ras_पूर्णांकr_triggered(व्योम)
अणु
	वापस !!atomic_पढ़ो(&amdgpu_ras_in_पूर्णांकr);
पूर्ण

अटल अंतरभूत व्योम amdgpu_ras_पूर्णांकr_cleared(व्योम)
अणु
	atomic_set(&amdgpu_ras_in_पूर्णांकr, 0);
पूर्ण

व्योम amdgpu_ras_global_ras_isr(काष्ठा amdgpu_device *adev);

व्योम amdgpu_ras_set_error_query_पढ़ोy(काष्ठा amdgpu_device *adev, bool पढ़ोy);

bool amdgpu_ras_need_emergency_restart(काष्ठा amdgpu_device *adev);

व्योम amdgpu_release_ras_context(काष्ठा amdgpu_device *adev);
#पूर्ण_अगर
