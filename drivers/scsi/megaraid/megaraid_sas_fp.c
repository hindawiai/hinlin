<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Linux MegaRAID driver क्रम SAS based RAID controllers
 *
 *  Copyright (c) 2009-2013  LSI Corporation
 *  Copyright (c) 2013-2016  Avago Technologies
 *  Copyright (c) 2016-2018  Broadcom Inc.
 *
 *  खाता: megaraid_sas_fp.c
 *
 *  Authors: Broadcom Inc.
 *           Sumant Patro
 *           Varad Talamacki
 *           Manoj Jose
 *           Kashyap Desai <kashyap.desai@broadcom.com>
 *           Sumit Saxena <sumit.saxena@broadcom.com>
 *
 *  Send feedback to: megaraidlinux.pdl@broadcom.com
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/list.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/uपन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs.h>
#समावेश <linux/compat.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/poll.h>
#समावेश <linux/irq_poll.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>

#समावेश "megaraid_sas_fusion.h"
#समावेश "megaraid_sas.h"
#समावेश <यंत्र/भाग64.h>

#घोषणा LB_PENDING_CMDS_DEFAULT 4
अटल अचिन्हित पूर्णांक lb_pending_cmds = LB_PENDING_CMDS_DEFAULT;
module_param(lb_pending_cmds, पूर्णांक, 0444);
MODULE_PARM_DESC(lb_pending_cmds, "Change raid-1 load balancing outstanding "
	"threshold. Valid Values are 1-128. Default: 4");


#घोषणा ABS_DIFF(a, b)   (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))
#घोषणा MR_LD_STATE_OPTIMAL 3

#घोषणा SPAN_ROW_SIZE(map, ld, index_) (MR_LdSpanPtrGet(ld, index_, map)->spanRowSize)
#घोषणा SPAN_ROW_DATA_SIZE(map_, ld, index_)   (MR_LdSpanPtrGet(ld, index_, map)->spanRowDataSize)
#घोषणा SPAN_INVALID  0xff

/* Prototypes */
अटल व्योम mr_update_span_set(काष्ठा MR_DRV_RAID_MAP_ALL *map,
	PLD_SPAN_INFO ldSpanInfo);
अटल u8 mr_spanset_get_phy_params(काष्ठा megasas_instance *instance, u32 ld,
	u64 stripRow, u16 stripRef, काष्ठा IO_REQUEST_INFO *io_info,
	काष्ठा RAID_CONTEXT *pRAID_Context, काष्ठा MR_DRV_RAID_MAP_ALL *map);
अटल u64 get_row_from_strip(काष्ठा megasas_instance *instance, u32 ld,
	u64 strip, काष्ठा MR_DRV_RAID_MAP_ALL *map);

u32 mega_mod64(u64 भागidend, u32 भागisor)
अणु
	u64 d;
	u32 reमुख्यder;

	अगर (!भागisor)
		prपूर्णांकk(KERN_ERR "megasas : DIVISOR is zero, in div fn\n");
	d = भागidend;
	reमुख्यder = करो_भाग(d, भागisor);
	वापस reमुख्यder;
पूर्ण

/**
 * mega_भाग64_32 - Do a 64-bit भागision
 * @भागidend:	Dividend
 * @भागisor:	Divisor
 *
 * @वापस quotient
 **/
अटल u64 mega_भाग64_32(uपूर्णांक64_t भागidend, uपूर्णांक32_t भागisor)
अणु
	u64 d = भागidend;

	अगर (!भागisor)
		prपूर्णांकk(KERN_ERR "megasas : DIVISOR is zero in mod fn\n");

	करो_भाग(d, भागisor);

	वापस d;
पूर्ण

काष्ठा MR_LD_RAID *MR_LdRaidGet(u32 ld, काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	वापस &map->raidMap.ldSpanMap[ld].ldRaid;
पूर्ण

अटल काष्ठा MR_SPAN_BLOCK_INFO *MR_LdSpanInfoGet(u32 ld,
						   काष्ठा MR_DRV_RAID_MAP_ALL
						   *map)
अणु
	वापस &map->raidMap.ldSpanMap[ld].spanBlock[0];
पूर्ण

अटल u8 MR_LdDataArmGet(u32 ld, u32 armIdx, काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	वापस map->raidMap.ldSpanMap[ld].dataArmMap[armIdx];
पूर्ण

u16 MR_ArPdGet(u32 ar, u32 arm, काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	वापस le16_to_cpu(map->raidMap.arMapInfo[ar].pd[arm]);
पूर्ण

u16 MR_LdSpanArrayGet(u32 ld, u32 span, काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	वापस le16_to_cpu(map->raidMap.ldSpanMap[ld].spanBlock[span].span.arrayRef);
पूर्ण

__le16 MR_PdDevHandleGet(u32 pd, काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	वापस map->raidMap.devHndlInfo[pd].curDevHdl;
पूर्ण

अटल u8 MR_PdInterfaceTypeGet(u32 pd, काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	वापस map->raidMap.devHndlInfo[pd].पूर्णांकerfaceType;
पूर्ण

u16 MR_GetLDTgtId(u32 ld, काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	वापस le16_to_cpu(map->raidMap.ldSpanMap[ld].ldRaid.targetId);
पूर्ण

u16 MR_TargetIdToLdGet(u32 ldTgtId, काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	वापस map->raidMap.ldTgtIdToLd[ldTgtId];
पूर्ण

अटल काष्ठा MR_LD_SPAN *MR_LdSpanPtrGet(u32 ld, u32 span,
					  काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	वापस &map->raidMap.ldSpanMap[ld].spanBlock[span].span;
पूर्ण

/*
 * This function will Populate Driver Map using firmware raid map
 */
अटल पूर्णांक MR_PopulateDrvRaidMap(काष्ठा megasas_instance *instance, u64 map_id)
अणु
	काष्ठा fusion_context *fusion = instance->ctrl_context;
	काष्ठा MR_FW_RAID_MAP_ALL     *fw_map_old    = शून्य;
	काष्ठा MR_FW_RAID_MAP         *pFwRaidMap    = शून्य;
	पूर्णांक i, j;
	u16 ld_count;
	काष्ठा MR_FW_RAID_MAP_DYNAMIC *fw_map_dyn;
	काष्ठा MR_FW_RAID_MAP_EXT *fw_map_ext;
	काष्ठा MR_RAID_MAP_DESC_TABLE *desc_table;


	काष्ठा MR_DRV_RAID_MAP_ALL *drv_map =
			fusion->ld_drv_map[(map_id & 1)];
	काष्ठा MR_DRV_RAID_MAP *pDrvRaidMap = &drv_map->raidMap;
	व्योम *raid_map_data = शून्य;

	स_रखो(drv_map, 0, fusion->drv_map_sz);
	स_रखो(pDrvRaidMap->ldTgtIdToLd,
	       0xff, (माप(u16) * MAX_LOGICAL_DRIVES_DYN));

	अगर (instance->max_raid_mapsize) अणु
		fw_map_dyn = fusion->ld_map[(map_id & 1)];
		desc_table =
		(काष्ठा MR_RAID_MAP_DESC_TABLE *)((व्योम *)fw_map_dyn + le32_to_cpu(fw_map_dyn->desc_table_offset));
		अगर (desc_table != fw_map_dyn->raid_map_desc_table)
			dev_dbg(&instance->pdev->dev, "offsets of desc table are not matching desc %p original %p\n",
				desc_table, fw_map_dyn->raid_map_desc_table);

		ld_count = (u16)le16_to_cpu(fw_map_dyn->ld_count);
		pDrvRaidMap->ldCount = (__le16)cpu_to_le16(ld_count);
		pDrvRaidMap->fpPdIoTimeoutSec =
			fw_map_dyn->fp_pd_io_समयout_sec;
		pDrvRaidMap->totalSize =
			cpu_to_le32(माप(काष्ठा MR_DRV_RAID_MAP_ALL));
		/* poपूर्णांक to actual data starting poपूर्णांक*/
		raid_map_data = (व्योम *)fw_map_dyn +
			le32_to_cpu(fw_map_dyn->desc_table_offset) +
			le32_to_cpu(fw_map_dyn->desc_table_size);

		क्रम (i = 0; i < le32_to_cpu(fw_map_dyn->desc_table_num_elements); ++i) अणु
			चयन (le32_to_cpu(desc_table->raid_map_desc_type)) अणु
			हाल RAID_MAP_DESC_TYPE_DEVHDL_INFO:
				fw_map_dyn->dev_hndl_info =
				(काष्ठा MR_DEV_HANDLE_INFO *)(raid_map_data + le32_to_cpu(desc_table->raid_map_desc_offset));
				स_नकल(pDrvRaidMap->devHndlInfo,
					fw_map_dyn->dev_hndl_info,
					माप(काष्ठा MR_DEV_HANDLE_INFO) *
					le32_to_cpu(desc_table->raid_map_desc_elements));
			अवरोध;
			हाल RAID_MAP_DESC_TYPE_TGTID_INFO:
				fw_map_dyn->ld_tgt_id_to_ld =
					(u16 *)(raid_map_data +
					le32_to_cpu(desc_table->raid_map_desc_offset));
				क्रम (j = 0; j < le32_to_cpu(desc_table->raid_map_desc_elements); j++) अणु
					pDrvRaidMap->ldTgtIdToLd[j] =
						le16_to_cpu(fw_map_dyn->ld_tgt_id_to_ld[j]);
				पूर्ण
			अवरोध;
			हाल RAID_MAP_DESC_TYPE_ARRAY_INFO:
				fw_map_dyn->ar_map_info =
					(काष्ठा MR_ARRAY_INFO *)
					(raid_map_data + le32_to_cpu(desc_table->raid_map_desc_offset));
				स_नकल(pDrvRaidMap->arMapInfo,
				       fw_map_dyn->ar_map_info,
				       माप(काष्ठा MR_ARRAY_INFO) *
				       le32_to_cpu(desc_table->raid_map_desc_elements));
			अवरोध;
			हाल RAID_MAP_DESC_TYPE_SPAN_INFO:
				fw_map_dyn->ld_span_map =
					(काष्ठा MR_LD_SPAN_MAP *)
					(raid_map_data +
					le32_to_cpu(desc_table->raid_map_desc_offset));
				स_नकल(pDrvRaidMap->ldSpanMap,
				       fw_map_dyn->ld_span_map,
				       माप(काष्ठा MR_LD_SPAN_MAP) *
				       le32_to_cpu(desc_table->raid_map_desc_elements));
			अवरोध;
			शेष:
				dev_dbg(&instance->pdev->dev, "wrong number of desctableElements %d\n",
					fw_map_dyn->desc_table_num_elements);
			पूर्ण
			++desc_table;
		पूर्ण

	पूर्ण अन्यथा अगर (instance->supporपंचांगax256vd) अणु
		fw_map_ext =
			(काष्ठा MR_FW_RAID_MAP_EXT *)fusion->ld_map[(map_id & 1)];
		ld_count = (u16)le16_to_cpu(fw_map_ext->ldCount);
		अगर (ld_count > MAX_LOGICAL_DRIVES_EXT) अणु
			dev_dbg(&instance->pdev->dev, "megaraid_sas: LD count exposed in RAID map in not valid\n");
			वापस 1;
		पूर्ण

		pDrvRaidMap->ldCount = (__le16)cpu_to_le16(ld_count);
		pDrvRaidMap->fpPdIoTimeoutSec = fw_map_ext->fpPdIoTimeoutSec;
		क्रम (i = 0; i < (MAX_LOGICAL_DRIVES_EXT); i++)
			pDrvRaidMap->ldTgtIdToLd[i] =
				(u16)fw_map_ext->ldTgtIdToLd[i];
		स_नकल(pDrvRaidMap->ldSpanMap, fw_map_ext->ldSpanMap,
		       माप(काष्ठा MR_LD_SPAN_MAP) * ld_count);
		स_नकल(pDrvRaidMap->arMapInfo, fw_map_ext->arMapInfo,
		       माप(काष्ठा MR_ARRAY_INFO) * MAX_API_ARRAYS_EXT);
		स_नकल(pDrvRaidMap->devHndlInfo, fw_map_ext->devHndlInfo,
		       माप(काष्ठा MR_DEV_HANDLE_INFO) *
		       MAX_RAIDMAP_PHYSICAL_DEVICES);

		/* New Raid map will not set totalSize, so keep expected value
		 * क्रम legacy code in ValidateMapInfo
		 */
		pDrvRaidMap->totalSize =
			cpu_to_le32(माप(काष्ठा MR_FW_RAID_MAP_EXT));
	पूर्ण अन्यथा अणु
		fw_map_old = (काष्ठा MR_FW_RAID_MAP_ALL *)
				fusion->ld_map[(map_id & 1)];
		pFwRaidMap = &fw_map_old->raidMap;
		ld_count = (u16)le32_to_cpu(pFwRaidMap->ldCount);
		अगर (ld_count > MAX_LOGICAL_DRIVES) अणु
			dev_dbg(&instance->pdev->dev,
				"LD count exposed in RAID map in not valid\n");
			वापस 1;
		पूर्ण

		pDrvRaidMap->totalSize = pFwRaidMap->totalSize;
		pDrvRaidMap->ldCount = (__le16)cpu_to_le16(ld_count);
		pDrvRaidMap->fpPdIoTimeoutSec = pFwRaidMap->fpPdIoTimeoutSec;
		क्रम (i = 0; i < MAX_RAIDMAP_LOGICAL_DRIVES + MAX_RAIDMAP_VIEWS; i++)
			pDrvRaidMap->ldTgtIdToLd[i] =
				(u8)pFwRaidMap->ldTgtIdToLd[i];
		क्रम (i = 0; i < ld_count; i++) अणु
			pDrvRaidMap->ldSpanMap[i] = pFwRaidMap->ldSpanMap[i];
		पूर्ण
		स_नकल(pDrvRaidMap->arMapInfo, pFwRaidMap->arMapInfo,
			माप(काष्ठा MR_ARRAY_INFO) * MAX_RAIDMAP_ARRAYS);
		स_नकल(pDrvRaidMap->devHndlInfo, pFwRaidMap->devHndlInfo,
			माप(काष्ठा MR_DEV_HANDLE_INFO) *
			MAX_RAIDMAP_PHYSICAL_DEVICES);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function will validate Map info data provided by FW
 */
u8 MR_ValidateMapInfo(काष्ठा megasas_instance *instance, u64 map_id)
अणु
	काष्ठा fusion_context *fusion;
	काष्ठा MR_DRV_RAID_MAP_ALL *drv_map;
	काष्ठा MR_DRV_RAID_MAP *pDrvRaidMap;
	काष्ठा LD_LOAD_BALANCE_INFO *lbInfo;
	PLD_SPAN_INFO ldSpanInfo;
	काष्ठा MR_LD_RAID         *raid;
	u16 num_lds, i;
	u16 ld;
	u32 expected_size;

	अगर (MR_PopulateDrvRaidMap(instance, map_id))
		वापस 0;

	fusion = instance->ctrl_context;
	drv_map = fusion->ld_drv_map[(map_id & 1)];
	pDrvRaidMap = &drv_map->raidMap;

	lbInfo = fusion->load_balance_info;
	ldSpanInfo = fusion->log_to_span;

	अगर (instance->max_raid_mapsize)
		expected_size = माप(काष्ठा MR_DRV_RAID_MAP_ALL);
	अन्यथा अगर (instance->supporपंचांगax256vd)
		expected_size = माप(काष्ठा MR_FW_RAID_MAP_EXT);
	अन्यथा
		expected_size =
			(माप(काष्ठा MR_FW_RAID_MAP) - माप(काष्ठा MR_LD_SPAN_MAP) +
			(माप(काष्ठा MR_LD_SPAN_MAP) * le16_to_cpu(pDrvRaidMap->ldCount)));

	अगर (le32_to_cpu(pDrvRaidMap->totalSize) != expected_size) अणु
		dev_dbg(&instance->pdev->dev, "megasas: map info structure size 0x%x",
			le32_to_cpu(pDrvRaidMap->totalSize));
		dev_dbg(&instance->pdev->dev, "is not matching expected size 0x%x\n",
			(अचिन्हित पूर्णांक)expected_size);
		dev_err(&instance->pdev->dev, "megasas: span map %x, pDrvRaidMap->totalSize : %x\n",
			(अचिन्हित पूर्णांक)माप(काष्ठा MR_LD_SPAN_MAP),
			le32_to_cpu(pDrvRaidMap->totalSize));
		वापस 0;
	पूर्ण

	अगर (instance->UnevenSpanSupport)
		mr_update_span_set(drv_map, ldSpanInfo);

	अगर (lbInfo)
		mr_update_load_balance_params(drv_map, lbInfo);

	num_lds = le16_to_cpu(drv_map->raidMap.ldCount);

	/*Convert Raid capability values to CPU arch */
	क्रम (i = 0; (num_lds > 0) && (i < MAX_LOGICAL_DRIVES_EXT); i++) अणु
		ld = MR_TargetIdToLdGet(i, drv_map);

		/* For non existing VDs, iterate to next VD*/
		अगर (ld >= (MAX_LOGICAL_DRIVES_EXT - 1))
			जारी;

		raid = MR_LdRaidGet(ld, drv_map);
		le32_to_cpus((u32 *)&raid->capability);

		num_lds--;
	पूर्ण

	वापस 1;
पूर्ण

अटल u32 MR_GetSpanBlock(u32 ld, u64 row, u64 *span_blk,
		    काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	काष्ठा MR_SPAN_BLOCK_INFO *pSpanBlock = MR_LdSpanInfoGet(ld, map);
	काष्ठा MR_QUAD_ELEMENT    *quad;
	काष्ठा MR_LD_RAID         *raid = MR_LdRaidGet(ld, map);
	u32                span, j;

	क्रम (span = 0; span < raid->spanDepth; span++, pSpanBlock++) अणु

		क्रम (j = 0; j < le32_to_cpu(pSpanBlock->block_span_info.noElements); j++) अणु
			quad = &pSpanBlock->block_span_info.quad[j];

			अगर (le32_to_cpu(quad->dअगरf) == 0)
				वापस SPAN_INVALID;
			अगर (le64_to_cpu(quad->logStart) <= row && row <=
				le64_to_cpu(quad->logEnd) && (mega_mod64(row - le64_to_cpu(quad->logStart),
				le32_to_cpu(quad->dअगरf))) == 0) अणु
				अगर (span_blk != शून्य) अणु
					u64  blk;
					blk =  mega_भाग64_32((row-le64_to_cpu(quad->logStart)), le32_to_cpu(quad->dअगरf));

					blk = (blk + le64_to_cpu(quad->offsetInSpan)) << raid->stripeShअगरt;
					*span_blk = blk;
				पूर्ण
				वापस span;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस SPAN_INVALID;
पूर्ण

/*
******************************************************************************
*
* This routine calculates the Span block क्रम given row using spanset.
*
* Inमाला_दो :
*    instance - HBA instance
*    ld   - Logical drive number
*    row        - Row number
*    map    - LD map
*
* Outमाला_दो :
*
*    span          - Span number
*    block         - Absolute Block number in the physical disk
*    भाग_error	   - Devide error code.
*/

अटल u32 mr_spanset_get_span_block(काष्ठा megasas_instance *instance,
		u32 ld, u64 row, u64 *span_blk, काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	काष्ठा fusion_context *fusion = instance->ctrl_context;
	काष्ठा MR_LD_RAID         *raid = MR_LdRaidGet(ld, map);
	LD_SPAN_SET *span_set;
	काष्ठा MR_QUAD_ELEMENT    *quad;
	u32    span, info;
	PLD_SPAN_INFO ldSpanInfo = fusion->log_to_span;

	क्रम (info = 0; info < MAX_QUAD_DEPTH; info++) अणु
		span_set = &(ldSpanInfo[ld].span_set[info]);

		अगर (span_set->span_row_data_width == 0)
			अवरोध;

		अगर (row > span_set->data_row_end)
			जारी;

		क्रम (span = 0; span < raid->spanDepth; span++)
			अगर (le32_to_cpu(map->raidMap.ldSpanMap[ld].spanBlock[span].
				block_span_info.noElements) >= info+1) अणु
				quad = &map->raidMap.ldSpanMap[ld].
					spanBlock[span].
					block_span_info.quad[info];
				अगर (le32_to_cpu(quad->dअगरf) == 0)
					वापस SPAN_INVALID;
				अगर (le64_to_cpu(quad->logStart) <= row  &&
					row <= le64_to_cpu(quad->logEnd)  &&
					(mega_mod64(row - le64_to_cpu(quad->logStart),
						le32_to_cpu(quad->dअगरf))) == 0) अणु
					अगर (span_blk != शून्य) अणु
						u64  blk;
						blk = mega_भाग64_32
						    ((row - le64_to_cpu(quad->logStart)),
						    le32_to_cpu(quad->dअगरf));
						blk = (blk + le64_to_cpu(quad->offsetInSpan))
							 << raid->stripeShअगरt;
						*span_blk = blk;
					पूर्ण
					वापस span;
				पूर्ण
			पूर्ण
	पूर्ण
	वापस SPAN_INVALID;
पूर्ण

/*
******************************************************************************
*
* This routine calculates the row क्रम given strip using spanset.
*
* Inमाला_दो :
*    instance - HBA instance
*    ld   - Logical drive number
*    Strip        - Strip
*    map    - LD map
*
* Outमाला_दो :
*
*    row         - row associated with strip
*/

अटल u64  get_row_from_strip(काष्ठा megasas_instance *instance,
	u32 ld, u64 strip, काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	काष्ठा fusion_context *fusion = instance->ctrl_context;
	काष्ठा MR_LD_RAID	*raid = MR_LdRaidGet(ld, map);
	LD_SPAN_SET	*span_set;
	PLD_SPAN_INFO	ldSpanInfo = fusion->log_to_span;
	u32		info, strip_offset, span, span_offset;
	u64		span_set_Strip, span_set_Row, retval;

	क्रम (info = 0; info < MAX_QUAD_DEPTH; info++) अणु
		span_set = &(ldSpanInfo[ld].span_set[info]);

		अगर (span_set->span_row_data_width == 0)
			अवरोध;
		अगर (strip > span_set->data_strip_end)
			जारी;

		span_set_Strip = strip - span_set->data_strip_start;
		strip_offset = mega_mod64(span_set_Strip,
				span_set->span_row_data_width);
		span_set_Row = mega_भाग64_32(span_set_Strip,
				span_set->span_row_data_width) * span_set->dअगरf;
		क्रम (span = 0, span_offset = 0; span < raid->spanDepth; span++)
			अगर (le32_to_cpu(map->raidMap.ldSpanMap[ld].spanBlock[span].
				block_span_info.noElements) >= info+1) अणु
				अगर (strip_offset >=
					span_set->strip_offset[span])
					span_offset++;
				अन्यथा
					अवरोध;
			पूर्ण

		retval = (span_set->data_row_start + span_set_Row +
				(span_offset - 1));
		वापस retval;
	पूर्ण
	वापस -1LLU;
पूर्ण


/*
******************************************************************************
*
* This routine calculates the Start Strip क्रम given row using spanset.
*
* Inमाला_दो :
*    instance - HBA instance
*    ld   - Logical drive number
*    row        - Row number
*    map    - LD map
*
* Outमाला_दो :
*
*    Strip         - Start strip associated with row
*/

अटल u64 get_strip_from_row(काष्ठा megasas_instance *instance,
		u32 ld, u64 row, काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	काष्ठा fusion_context *fusion = instance->ctrl_context;
	काष्ठा MR_LD_RAID         *raid = MR_LdRaidGet(ld, map);
	LD_SPAN_SET *span_set;
	काष्ठा MR_QUAD_ELEMENT    *quad;
	PLD_SPAN_INFO ldSpanInfo = fusion->log_to_span;
	u32    span, info;
	u64  strip;

	क्रम (info = 0; info < MAX_QUAD_DEPTH; info++) अणु
		span_set = &(ldSpanInfo[ld].span_set[info]);

		अगर (span_set->span_row_data_width == 0)
			अवरोध;
		अगर (row > span_set->data_row_end)
			जारी;

		क्रम (span = 0; span < raid->spanDepth; span++)
			अगर (le32_to_cpu(map->raidMap.ldSpanMap[ld].spanBlock[span].
				block_span_info.noElements) >= info+1) अणु
				quad = &map->raidMap.ldSpanMap[ld].
					spanBlock[span].block_span_info.quad[info];
				अगर (le64_to_cpu(quad->logStart) <= row  &&
					row <= le64_to_cpu(quad->logEnd)  &&
					mega_mod64((row - le64_to_cpu(quad->logStart)),
					le32_to_cpu(quad->dअगरf)) == 0) अणु
					strip = mega_भाग64_32
						(((row - span_set->data_row_start)
							- le64_to_cpu(quad->logStart)),
							le32_to_cpu(quad->dअगरf));
					strip *= span_set->span_row_data_width;
					strip += span_set->data_strip_start;
					strip += span_set->strip_offset[span];
					वापस strip;
				पूर्ण
			पूर्ण
	पूर्ण
	dev_err(&instance->pdev->dev, "get_strip_from_row"
		"returns invalid strip for ld=%x, row=%lx\n",
		ld, (दीर्घ अचिन्हित पूर्णांक)row);
	वापस -1;
पूर्ण

/*
******************************************************************************
*
* This routine calculates the Physical Arm क्रम given strip using spanset.
*
* Inमाला_दो :
*    instance - HBA instance
*    ld   - Logical drive number
*    strip      - Strip
*    map    - LD map
*
* Outमाला_दो :
*
*    Phys Arm         - Phys Arm associated with strip
*/

अटल u32 get_arm_from_strip(काष्ठा megasas_instance *instance,
	u32 ld, u64 strip, काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	काष्ठा fusion_context *fusion = instance->ctrl_context;
	काष्ठा MR_LD_RAID         *raid = MR_LdRaidGet(ld, map);
	LD_SPAN_SET *span_set;
	PLD_SPAN_INFO ldSpanInfo = fusion->log_to_span;
	u32    info, strip_offset, span, span_offset, retval;

	क्रम (info = 0 ; info < MAX_QUAD_DEPTH; info++) अणु
		span_set = &(ldSpanInfo[ld].span_set[info]);

		अगर (span_set->span_row_data_width == 0)
			अवरोध;
		अगर (strip > span_set->data_strip_end)
			जारी;

		strip_offset = (uपूर्णांक)mega_mod64
				((strip - span_set->data_strip_start),
				span_set->span_row_data_width);

		क्रम (span = 0, span_offset = 0; span < raid->spanDepth; span++)
			अगर (le32_to_cpu(map->raidMap.ldSpanMap[ld].spanBlock[span].
				block_span_info.noElements) >= info+1) अणु
				अगर (strip_offset >=
					span_set->strip_offset[span])
					span_offset =
						span_set->strip_offset[span];
				अन्यथा
					अवरोध;
			पूर्ण

		retval = (strip_offset - span_offset);
		वापस retval;
	पूर्ण

	dev_err(&instance->pdev->dev, "get_arm_from_strip"
		"returns invalid arm for ld=%x strip=%lx\n",
		ld, (दीर्घ अचिन्हित पूर्णांक)strip);

	वापस -1;
पूर्ण

/* This Function will वापस Phys arm */
अटल u8 get_arm(काष्ठा megasas_instance *instance, u32 ld, u8 span, u64 stripe,
		काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	काष्ठा MR_LD_RAID  *raid = MR_LdRaidGet(ld, map);
	/* Need to check correct शेष value */
	u32    arm = 0;

	चयन (raid->level) अणु
	हाल 0:
	हाल 5:
	हाल 6:
		arm = mega_mod64(stripe, SPAN_ROW_SIZE(map, ld, span));
		अवरोध;
	हाल 1:
		/* start with logical arm */
		arm = get_arm_from_strip(instance, ld, stripe, map);
		अगर (arm != -1U)
			arm *= 2;
		अवरोध;
	पूर्ण

	वापस arm;
पूर्ण


/*
******************************************************************************
*
* This routine calculates the arm, span and block क्रम the specअगरied stripe and
* reference in stripe using spanset
*
* Inमाला_दो :
*
*    ld   - Logical drive number
*    stripRow        - Stripe number
*    stripRef    - Reference in stripe
*
* Outमाला_दो :
*
*    span          - Span number
*    block         - Absolute Block number in the physical disk
*/
अटल u8 mr_spanset_get_phy_params(काष्ठा megasas_instance *instance, u32 ld,
		u64 stripRow, u16 stripRef, काष्ठा IO_REQUEST_INFO *io_info,
		काष्ठा RAID_CONTEXT *pRAID_Context,
		काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	काष्ठा MR_LD_RAID  *raid = MR_LdRaidGet(ld, map);
	u32     pd, arRef, r1_alt_pd;
	u8      physArm, span;
	u64     row;
	u8	retval = true;
	u64	*pdBlock = &io_info->pdBlock;
	__le16	*pDevHandle = &io_info->devHandle;
	u8	*pPdInterface = &io_info->pd_पूर्णांकerface;
	u32	logArm, rowMod, armQ, arm;

	*pDevHandle = cpu_to_le16(MR_DEVHANDLE_INVALID);

	/*Get row and span from io_info क्रम Uneven Span IO.*/
	row	    = io_info->start_row;
	span	    = io_info->start_span;


	अगर (raid->level == 6) अणु
		logArm = get_arm_from_strip(instance, ld, stripRow, map);
		अगर (logArm == -1U)
			वापस false;
		rowMod = mega_mod64(row, SPAN_ROW_SIZE(map, ld, span));
		armQ = SPAN_ROW_SIZE(map, ld, span) - 1 - rowMod;
		arm = armQ + 1 + logArm;
		अगर (arm >= SPAN_ROW_SIZE(map, ld, span))
			arm -= SPAN_ROW_SIZE(map, ld, span);
		physArm = (u8)arm;
	पूर्ण अन्यथा
		/* Calculate the arm */
		physArm = get_arm(instance, ld, span, stripRow, map);
	अगर (physArm == 0xFF)
		वापस false;

	arRef       = MR_LdSpanArrayGet(ld, span, map);
	pd          = MR_ArPdGet(arRef, physArm, map);

	अगर (pd != MR_PD_INVALID) अणु
		*pDevHandle = MR_PdDevHandleGet(pd, map);
		*pPdInterface = MR_PdInterfaceTypeGet(pd, map);
		/* get second pd also क्रम raid 1/10 fast path ग_लिखोs*/
		अगर ((instance->adapter_type >= VENTURA_SERIES) &&
		    (raid->level == 1) &&
		    !io_info->isRead) अणु
			r1_alt_pd = MR_ArPdGet(arRef, physArm + 1, map);
			अगर (r1_alt_pd != MR_PD_INVALID)
				io_info->r1_alt_dev_handle =
				MR_PdDevHandleGet(r1_alt_pd, map);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((raid->level >= 5) &&
			((instance->adapter_type == THUNDERBOLT_SERIES)  ||
			((instance->adapter_type == INVADER_SERIES) &&
			(raid->regTypeReqOnRead != REGION_TYPE_UNUSED))))
			pRAID_Context->reg_lock_flags = REGION_TYPE_EXCLUSIVE;
		अन्यथा अगर (raid->level == 1) अणु
			physArm = physArm + 1;
			pd = MR_ArPdGet(arRef, physArm, map);
			अगर (pd != MR_PD_INVALID) अणु
				*pDevHandle = MR_PdDevHandleGet(pd, map);
				*pPdInterface = MR_PdInterfaceTypeGet(pd, map);
			पूर्ण
		पूर्ण
	पूर्ण

	*pdBlock += stripRef + le64_to_cpu(MR_LdSpanPtrGet(ld, span, map)->startBlk);
	अगर (instance->adapter_type >= VENTURA_SERIES) अणु
		((काष्ठा RAID_CONTEXT_G35 *)pRAID_Context)->span_arm =
			(span << RAID_CTX_SPANARM_SPAN_SHIFT) | physArm;
		io_info->span_arm =
			(span << RAID_CTX_SPANARM_SPAN_SHIFT) | physArm;
	पूर्ण अन्यथा अणु
		pRAID_Context->span_arm =
			(span << RAID_CTX_SPANARM_SPAN_SHIFT) | physArm;
		io_info->span_arm = pRAID_Context->span_arm;
	पूर्ण
	io_info->pd_after_lb = pd;
	वापस retval;
पूर्ण

/*
******************************************************************************
*
* This routine calculates the arm, span and block क्रम the specअगरied stripe and
* reference in stripe.
*
* Inमाला_दो :
*
*    ld   - Logical drive number
*    stripRow        - Stripe number
*    stripRef    - Reference in stripe
*
* Outमाला_दो :
*
*    span          - Span number
*    block         - Absolute Block number in the physical disk
*/
अटल u8 MR_GetPhyParams(काष्ठा megasas_instance *instance, u32 ld, u64 stripRow,
		u16 stripRef, काष्ठा IO_REQUEST_INFO *io_info,
		काष्ठा RAID_CONTEXT *pRAID_Context,
		काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	काष्ठा MR_LD_RAID  *raid = MR_LdRaidGet(ld, map);
	u32         pd, arRef, r1_alt_pd;
	u8          physArm, span;
	u64         row;
	u8	    retval = true;
	u64	    *pdBlock = &io_info->pdBlock;
	__le16	    *pDevHandle = &io_info->devHandle;
	u8	    *pPdInterface = &io_info->pd_पूर्णांकerface;

	*pDevHandle = cpu_to_le16(MR_DEVHANDLE_INVALID);

	row =  mega_भाग64_32(stripRow, raid->rowDataSize);

	अगर (raid->level == 6) अणु
		/* logical arm within row */
		u32 logArm =  mega_mod64(stripRow, raid->rowDataSize);
		u32 rowMod, armQ, arm;

		अगर (raid->rowSize == 0)
			वापस false;
		/* get logical row mod */
		rowMod = mega_mod64(row, raid->rowSize);
		armQ = raid->rowSize-1-rowMod; /* index of Q drive */
		arm = armQ+1+logArm; /* data always logically follows Q */
		अगर (arm >= raid->rowSize) /* handle wrap condition */
			arm -= raid->rowSize;
		physArm = (u8)arm;
	पूर्ण अन्यथा  अणु
		अगर (raid->modFactor == 0)
			वापस false;
		physArm = MR_LdDataArmGet(ld,  mega_mod64(stripRow,
							  raid->modFactor),
					  map);
	पूर्ण

	अगर (raid->spanDepth == 1) अणु
		span = 0;
		*pdBlock = row << raid->stripeShअगरt;
	पूर्ण अन्यथा अणु
		span = (u8)MR_GetSpanBlock(ld, row, pdBlock, map);
		अगर (span == SPAN_INVALID)
			वापस false;
	पूर्ण

	/* Get the array on which this span is present */
	arRef       = MR_LdSpanArrayGet(ld, span, map);
	pd          = MR_ArPdGet(arRef, physArm, map); /* Get the pd */

	अगर (pd != MR_PD_INVALID) अणु
		/* Get dev handle from Pd. */
		*pDevHandle = MR_PdDevHandleGet(pd, map);
		*pPdInterface = MR_PdInterfaceTypeGet(pd, map);
		/* get second pd also क्रम raid 1/10 fast path ग_लिखोs*/
		अगर ((instance->adapter_type >= VENTURA_SERIES) &&
		    (raid->level == 1) &&
		    !io_info->isRead) अणु
			r1_alt_pd = MR_ArPdGet(arRef, physArm + 1, map);
			अगर (r1_alt_pd != MR_PD_INVALID)
				io_info->r1_alt_dev_handle =
					MR_PdDevHandleGet(r1_alt_pd, map);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((raid->level >= 5) &&
			((instance->adapter_type == THUNDERBOLT_SERIES)  ||
			((instance->adapter_type == INVADER_SERIES) &&
			(raid->regTypeReqOnRead != REGION_TYPE_UNUSED))))
			pRAID_Context->reg_lock_flags = REGION_TYPE_EXCLUSIVE;
		अन्यथा अगर (raid->level == 1) अणु
			/* Get alternate Pd. */
			physArm = physArm + 1;
			pd = MR_ArPdGet(arRef, physArm, map);
			अगर (pd != MR_PD_INVALID) अणु
				/* Get dev handle from Pd */
				*pDevHandle = MR_PdDevHandleGet(pd, map);
				*pPdInterface = MR_PdInterfaceTypeGet(pd, map);
			पूर्ण
		पूर्ण
	पूर्ण

	*pdBlock += stripRef + le64_to_cpu(MR_LdSpanPtrGet(ld, span, map)->startBlk);
	अगर (instance->adapter_type >= VENTURA_SERIES) अणु
		((काष्ठा RAID_CONTEXT_G35 *)pRAID_Context)->span_arm =
				(span << RAID_CTX_SPANARM_SPAN_SHIFT) | physArm;
		io_info->span_arm =
				(span << RAID_CTX_SPANARM_SPAN_SHIFT) | physArm;
	पूर्ण अन्यथा अणु
		pRAID_Context->span_arm =
			(span << RAID_CTX_SPANARM_SPAN_SHIFT) | physArm;
		io_info->span_arm = pRAID_Context->span_arm;
	पूर्ण
	io_info->pd_after_lb = pd;
	वापस retval;
पूर्ण

/*
 * mr_get_phy_params_r56_rmw -  Calculate parameters क्रम R56 CTIO ग_लिखो operation
 * @instance:			Adapter soft state
 * @ld:				LD index
 * @stripNo:			Strip Number
 * @io_info:			IO info काष्ठाure poपूर्णांकer
 * pRAID_Context:		RAID context poपूर्णांकer
 * map:				RAID map poपूर्णांकer
 *
 * This routine calculates the logical arm, data Arm, row number and parity arm
 * क्रम R56 CTIO ग_लिखो operation.
 */
अटल व्योम mr_get_phy_params_r56_rmw(काष्ठा megasas_instance *instance,
			    u32 ld, u64 stripNo,
			    काष्ठा IO_REQUEST_INFO *io_info,
			    काष्ठा RAID_CONTEXT_G35 *pRAID_Context,
			    काष्ठा MR_DRV_RAID_MAP_ALL *map)
अणु
	काष्ठा MR_LD_RAID  *raid = MR_LdRaidGet(ld, map);
	u8          span, dataArms, arms, dataArm, logArm;
	s8          righपंचांगostParityArm, PParityArm;
	u64         rowNum;
	u64 *pdBlock = &io_info->pdBlock;

	dataArms = raid->rowDataSize;
	arms = raid->rowSize;

	rowNum =  mega_भाग64_32(stripNo, dataArms);
	/* parity disk arm, first arm is 0 */
	righपंचांगostParityArm = (arms - 1) - mega_mod64(rowNum, arms);

	/* logical arm within row */
	logArm =  mega_mod64(stripNo, dataArms);
	/* physical arm क्रम data */
	dataArm = mega_mod64((righपंचांगostParityArm + 1 + logArm), arms);

	अगर (raid->spanDepth == 1) अणु
		span = 0;
	पूर्ण अन्यथा अणु
		span = (u8)MR_GetSpanBlock(ld, rowNum, pdBlock, map);
		अगर (span == SPAN_INVALID)
			वापस;
	पूर्ण

	अगर (raid->level == 6) अणु
		/* P Parity arm, note this can go negative adjust अगर negative */
		PParityArm = (arms - 2) - mega_mod64(rowNum, arms);

		अगर (PParityArm < 0)
			PParityArm += arms;

		/* righपंचांगostParityArm is P-Parity क्रम RAID 5 and Q-Parity क्रम RAID */
		pRAID_Context->flow_specअगरic.r56_arm_map = righपंचांगostParityArm;
		pRAID_Context->flow_specअगरic.r56_arm_map |=
				    (u16)(PParityArm << RAID_CTX_R56_P_ARM_SHIFT);
	पूर्ण अन्यथा अणु
		pRAID_Context->flow_specअगरic.r56_arm_map |=
				    (u16)(righपंचांगostParityArm << RAID_CTX_R56_P_ARM_SHIFT);
	पूर्ण

	pRAID_Context->reg_lock_row_lba = cpu_to_le64(rowNum);
	pRAID_Context->flow_specअगरic.r56_arm_map |=
				   (u16)(logArm << RAID_CTX_R56_LOG_ARM_SHIFT);
	cpu_to_le16s(&pRAID_Context->flow_specअगरic.r56_arm_map);
	pRAID_Context->span_arm = (span << RAID_CTX_SPANARM_SPAN_SHIFT) | dataArm;
	pRAID_Context->raid_flags = (MR_RAID_FLAGS_IO_SUB_TYPE_R56_DIV_OFFLOAD <<
				    MR_RAID_CTX_RAID_FLAGS_IO_SUB_TYPE_SHIFT);

	वापस;
पूर्ण

/*
******************************************************************************
*
* MR_BuildRaidContext function
*
* This function will initiate command processing.  The start/end row and strip
* inक्रमmation is calculated then the lock is acquired.
* This function will वापस 0 अगर region lock was acquired OR वापस num strips
*/
u8
MR_BuildRaidContext(काष्ठा megasas_instance *instance,
		    काष्ठा IO_REQUEST_INFO *io_info,
		    काष्ठा RAID_CONTEXT *pRAID_Context,
		    काष्ठा MR_DRV_RAID_MAP_ALL *map, u8 **raidLUN)
अणु
	काष्ठा fusion_context *fusion;
	काष्ठा MR_LD_RAID  *raid;
	u32         stripSize, stripe_mask;
	u64         endLba, endStrip, endRow, start_row, start_strip;
	u64         regStart;
	u32         regSize;
	u8          num_strips, numRows;
	u16         ref_in_start_stripe, ref_in_end_stripe;
	u64         ldStartBlock;
	u32         numBlocks, ldTgtId;
	u8          isRead;
	u8	    retval = 0;
	u8	    startlba_span = SPAN_INVALID;
	u64 *pdBlock = &io_info->pdBlock;
	u16	    ld;

	ldStartBlock = io_info->ldStartBlock;
	numBlocks = io_info->numBlocks;
	ldTgtId = io_info->ldTgtId;
	isRead = io_info->isRead;
	io_info->Ioक्रमUnevenSpan = 0;
	io_info->start_span	= SPAN_INVALID;
	fusion = instance->ctrl_context;

	ld = MR_TargetIdToLdGet(ldTgtId, map);
	raid = MR_LdRaidGet(ld, map);
	/*check पढ़ो ahead bit*/
	io_info->ra_capable = raid->capability.ra_capable;

	/*
	 * अगर rowDataSize @RAID map and spanRowDataSize @SPAN INFO are zero
	 * वापस FALSE
	 */
	अगर (raid->rowDataSize == 0) अणु
		अगर (MR_LdSpanPtrGet(ld, 0, map)->spanRowDataSize == 0)
			वापस false;
		अन्यथा अगर (instance->UnevenSpanSupport) अणु
			io_info->Ioक्रमUnevenSpan = 1;
		पूर्ण अन्यथा अणु
			dev_info(&instance->pdev->dev,
				"raid->rowDataSize is 0, but has SPAN[0]"
				"rowDataSize = 0x%0x,"
				"but there is _NO_ UnevenSpanSupport\n",
				MR_LdSpanPtrGet(ld, 0, map)->spanRowDataSize);
			वापस false;
		पूर्ण
	पूर्ण

	stripSize = 1 << raid->stripeShअगरt;
	stripe_mask = stripSize-1;

	io_info->data_arms = raid->rowDataSize;

	/*
	 * calculate starting row and stripe, and number of strips and rows
	 */
	start_strip         = ldStartBlock >> raid->stripeShअगरt;
	ref_in_start_stripe = (u16)(ldStartBlock & stripe_mask);
	endLba              = ldStartBlock + numBlocks - 1;
	ref_in_end_stripe   = (u16)(endLba & stripe_mask);
	endStrip            = endLba >> raid->stripeShअगरt;
	num_strips          = (u8)(endStrip - start_strip + 1); /* End strip */

	अगर (io_info->Ioक्रमUnevenSpan) अणु
		start_row = get_row_from_strip(instance, ld, start_strip, map);
		endRow	  = get_row_from_strip(instance, ld, endStrip, map);
		अगर (start_row == -1ULL || endRow == -1ULL) अणु
			dev_info(&instance->pdev->dev, "return from %s %d."
				"Send IO w/o region lock.\n",
				__func__, __LINE__);
			वापस false;
		पूर्ण

		अगर (raid->spanDepth == 1) अणु
			startlba_span = 0;
			*pdBlock = start_row << raid->stripeShअगरt;
		पूर्ण अन्यथा
			startlba_span = (u8)mr_spanset_get_span_block(instance,
						ld, start_row, pdBlock, map);
		अगर (startlba_span == SPAN_INVALID) अणु
			dev_info(&instance->pdev->dev, "return from %s %d"
				"for row 0x%llx,start strip %llx"
				"endSrip %llx\n", __func__, __LINE__,
				(अचिन्हित दीर्घ दीर्घ)start_row,
				(अचिन्हित दीर्घ दीर्घ)start_strip,
				(अचिन्हित दीर्घ दीर्घ)endStrip);
			वापस false;
		पूर्ण
		io_info->start_span	= startlba_span;
		io_info->start_row	= start_row;
	पूर्ण अन्यथा अणु
		start_row = mega_भाग64_32(start_strip, raid->rowDataSize);
		endRow    = mega_भाग64_32(endStrip, raid->rowDataSize);
	पूर्ण
	numRows = (u8)(endRow - start_row + 1);

	/*
	 * calculate region info.
	 */

	/* assume region is at the start of the first row */
	regStart            = start_row << raid->stripeShअगरt;
	/* assume this IO needs the full row - we'll adjust अगर not true */
	regSize             = stripSize;

	io_info->करो_fp_rlbypass = raid->capability.fpBypassRegionLock;

	/* Check अगर we can send this I/O via FastPath */
	अगर (raid->capability.fpCapable) अणु
		अगर (isRead)
			io_info->fpOkForIo = (raid->capability.fpReadCapable &&
					      ((num_strips == 1) ||
					       raid->capability.
					       fpReadAcrossStripe));
		अन्यथा
			io_info->fpOkForIo = (raid->capability.fpWriteCapable &&
					      ((num_strips == 1) ||
					       raid->capability.
					       fpWriteAcrossStripe));
	पूर्ण अन्यथा
		io_info->fpOkForIo = false;

	अगर (numRows == 1) अणु
		/* single-strip IOs can always lock only the data needed */
		अगर (num_strips == 1) अणु
			regStart += ref_in_start_stripe;
			regSize = numBlocks;
		पूर्ण
		/* multi-strip IOs always need to full stripe locked */
	पूर्ण अन्यथा अगर (io_info->Ioक्रमUnevenSpan == 0) अणु
		/*
		 * For Even span region lock optimization.
		 * If the start strip is the last in the start row
		 */
		अगर (start_strip == (start_row + 1) * raid->rowDataSize - 1) अणु
			regStart += ref_in_start_stripe;
			/* initialize count to sectors from startref to end
			   of strip */
			regSize = stripSize - ref_in_start_stripe;
		पूर्ण

		/* add complete rows in the middle of the transfer */
		अगर (numRows > 2)
			regSize += (numRows-2) << raid->stripeShअगरt;

		/* अगर IO ends within first strip of last row*/
		अगर (endStrip == endRow*raid->rowDataSize)
			regSize += ref_in_end_stripe+1;
		अन्यथा
			regSize += stripSize;
	पूर्ण अन्यथा अणु
		/*
		 * For Uneven span region lock optimization.
		 * If the start strip is the last in the start row
		 */
		अगर (start_strip == (get_strip_from_row(instance, ld, start_row, map) +
				SPAN_ROW_DATA_SIZE(map, ld, startlba_span) - 1)) अणु
			regStart += ref_in_start_stripe;
			/* initialize count to sectors from
			 * startRef to end of strip
			 */
			regSize = stripSize - ref_in_start_stripe;
		पूर्ण
		/* Add complete rows in the middle of the transfer*/

		अगर (numRows > 2)
			/* Add complete rows in the middle of the transfer*/
			regSize += (numRows-2) << raid->stripeShअगरt;

		/* अगर IO ends within first strip of last row */
		अगर (endStrip == get_strip_from_row(instance, ld, endRow, map))
			regSize += ref_in_end_stripe + 1;
		अन्यथा
			regSize += stripSize;
	पूर्ण

	pRAID_Context->समयout_value =
		cpu_to_le16(raid->fpIoTimeoutForLd ?
			    raid->fpIoTimeoutForLd :
			    map->raidMap.fpPdIoTimeoutSec);
	अगर (instance->adapter_type == INVADER_SERIES)
		pRAID_Context->reg_lock_flags = (isRead) ?
			raid->regTypeReqOnRead : raid->regTypeReqOnWrite;
	अन्यथा अगर (instance->adapter_type == THUNDERBOLT_SERIES)
		pRAID_Context->reg_lock_flags = (isRead) ?
			REGION_TYPE_SHARED_READ : raid->regTypeReqOnWrite;
	pRAID_Context->भव_disk_tgt_id = raid->targetId;
	pRAID_Context->reg_lock_row_lba    = cpu_to_le64(regStart);
	pRAID_Context->reg_lock_length    = cpu_to_le32(regSize);
	pRAID_Context->config_seq_num	= raid->seqNum;
	/* save poपूर्णांकer to raid->LUN array */
	*raidLUN = raid->LUN;

	/* Aero R5/6 Division Offload क्रम WRITE */
	अगर (fusion->r56_भाग_offload && (raid->level >= 5) && !isRead) अणु
		mr_get_phy_params_r56_rmw(instance, ld, start_strip, io_info,
				       (काष्ठा RAID_CONTEXT_G35 *)pRAID_Context,
				       map);
		वापस true;
	पूर्ण

	/*Get Phy Params only अगर FP capable, or अन्यथा leave it to MR firmware
	  to करो the calculation.*/
	अगर (io_info->fpOkForIo) अणु
		retval = io_info->Ioक्रमUnevenSpan ?
				mr_spanset_get_phy_params(instance, ld,
					start_strip, ref_in_start_stripe,
					io_info, pRAID_Context, map) :
				MR_GetPhyParams(instance, ld, start_strip,
					ref_in_start_stripe, io_info,
					pRAID_Context, map);
		/* If IO on an invalid Pd, then FP is not possible.*/
		अगर (io_info->devHandle == MR_DEVHANDLE_INVALID)
			io_info->fpOkForIo = false;
		वापस retval;
	पूर्ण अन्यथा अगर (isRead) अणु
		uपूर्णांक stripIdx;
		क्रम (stripIdx = 0; stripIdx < num_strips; stripIdx++) अणु
			retval = io_info->Ioक्रमUnevenSpan ?
				mr_spanset_get_phy_params(instance, ld,
				    start_strip + stripIdx,
				    ref_in_start_stripe, io_info,
				    pRAID_Context, map) :
				MR_GetPhyParams(instance, ld,
				    start_strip + stripIdx, ref_in_start_stripe,
				    io_info, pRAID_Context, map);
			अगर (!retval)
				वापस true;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

/*
******************************************************************************
*
* This routine pepare spanset info from Valid Raid map and store it पूर्णांकo
* local copy of ldSpanInfo per instance data काष्ठाure.
*
* Inमाला_दो :
* map    - LD map
* ldSpanInfo - ldSpanInfo per HBA instance
*
*/
व्योम mr_update_span_set(काष्ठा MR_DRV_RAID_MAP_ALL *map,
	PLD_SPAN_INFO ldSpanInfo)
अणु
	u8   span, count;
	u32  element, span_row_width;
	u64  span_row;
	काष्ठा MR_LD_RAID *raid;
	LD_SPAN_SET *span_set, *span_set_prev;
	काष्ठा MR_QUAD_ELEMENT    *quad;
	पूर्णांक ldCount;
	u16 ld;


	क्रम (ldCount = 0; ldCount < MAX_LOGICAL_DRIVES_EXT; ldCount++) अणु
		ld = MR_TargetIdToLdGet(ldCount, map);
		अगर (ld >= (MAX_LOGICAL_DRIVES_EXT - 1))
			जारी;
		raid = MR_LdRaidGet(ld, map);
		क्रम (element = 0; element < MAX_QUAD_DEPTH; element++) अणु
			क्रम (span = 0; span < raid->spanDepth; span++) अणु
				अगर (le32_to_cpu(map->raidMap.ldSpanMap[ld].spanBlock[span].
					block_span_info.noElements) <
					element + 1)
					जारी;
				span_set = &(ldSpanInfo[ld].span_set[element]);
				quad = &map->raidMap.ldSpanMap[ld].
					spanBlock[span].block_span_info.
					quad[element];

				span_set->dअगरf = le32_to_cpu(quad->dअगरf);

				क्रम (count = 0, span_row_width = 0;
					count < raid->spanDepth; count++) अणु
					अगर (le32_to_cpu(map->raidMap.ldSpanMap[ld].
						spanBlock[count].
						block_span_info.
						noElements) >= element + 1) अणु
						span_set->strip_offset[count] =
							span_row_width;
						span_row_width +=
							MR_LdSpanPtrGet
							(ld, count, map)->spanRowDataSize;
					पूर्ण
				पूर्ण

				span_set->span_row_data_width = span_row_width;
				span_row = mega_भाग64_32(((le64_to_cpu(quad->logEnd) -
					le64_to_cpu(quad->logStart)) + le32_to_cpu(quad->dअगरf)),
					le32_to_cpu(quad->dअगरf));

				अगर (element == 0) अणु
					span_set->log_start_lba = 0;
					span_set->log_end_lba =
						((span_row << raid->stripeShअगरt)
						* span_row_width) - 1;

					span_set->span_row_start = 0;
					span_set->span_row_end = span_row - 1;

					span_set->data_strip_start = 0;
					span_set->data_strip_end =
						(span_row * span_row_width) - 1;

					span_set->data_row_start = 0;
					span_set->data_row_end =
						(span_row * le32_to_cpu(quad->dअगरf)) - 1;
				पूर्ण अन्यथा अणु
					span_set_prev = &(ldSpanInfo[ld].
							span_set[element - 1]);
					span_set->log_start_lba =
						span_set_prev->log_end_lba + 1;
					span_set->log_end_lba =
						span_set->log_start_lba +
						((span_row << raid->stripeShअगरt)
						* span_row_width) - 1;

					span_set->span_row_start =
						span_set_prev->span_row_end + 1;
					span_set->span_row_end =
					span_set->span_row_start + span_row - 1;

					span_set->data_strip_start =
					span_set_prev->data_strip_end + 1;
					span_set->data_strip_end =
						span_set->data_strip_start +
						(span_row * span_row_width) - 1;

					span_set->data_row_start =
						span_set_prev->data_row_end + 1;
					span_set->data_row_end =
						span_set->data_row_start +
						(span_row * le32_to_cpu(quad->dअगरf)) - 1;
				पूर्ण
				अवरोध;
		पूर्ण
		अगर (span == raid->spanDepth)
			अवरोध;
	    पूर्ण
	पूर्ण
पूर्ण

व्योम mr_update_load_balance_params(काष्ठा MR_DRV_RAID_MAP_ALL *drv_map,
	काष्ठा LD_LOAD_BALANCE_INFO *lbInfo)
अणु
	पूर्णांक ldCount;
	u16 ld;
	काष्ठा MR_LD_RAID *raid;

	अगर (lb_pending_cmds > 128 || lb_pending_cmds < 1)
		lb_pending_cmds = LB_PENDING_CMDS_DEFAULT;

	क्रम (ldCount = 0; ldCount < MAX_LOGICAL_DRIVES_EXT; ldCount++) अणु
		ld = MR_TargetIdToLdGet(ldCount, drv_map);
		अगर (ld >= MAX_LOGICAL_DRIVES_EXT - 1) अणु
			lbInfo[ldCount].loadBalanceFlag = 0;
			जारी;
		पूर्ण

		raid = MR_LdRaidGet(ld, drv_map);
		अगर ((raid->level != 1) ||
			(raid->ldState != MR_LD_STATE_OPTIMAL)) अणु
			lbInfo[ldCount].loadBalanceFlag = 0;
			जारी;
		पूर्ण
		lbInfo[ldCount].loadBalanceFlag = 1;
	पूर्ण
पूर्ण

अटल u8 megasas_get_best_arm_pd(काष्ठा megasas_instance *instance,
			   काष्ठा LD_LOAD_BALANCE_INFO *lbInfo,
			   काष्ठा IO_REQUEST_INFO *io_info,
			   काष्ठा MR_DRV_RAID_MAP_ALL *drv_map)
अणु
	काष्ठा MR_LD_RAID  *raid;
	u16	pd1_dev_handle;
	u16     pend0, pend1, ld;
	u64     dअगरf0, dअगरf1;
	u8      bestArm, pd0, pd1, span, arm;
	u32     arRef, span_row_size;

	u64 block = io_info->ldStartBlock;
	u32 count = io_info->numBlocks;

	span = ((io_info->span_arm & RAID_CTX_SPANARM_SPAN_MASK)
			>> RAID_CTX_SPANARM_SPAN_SHIFT);
	arm = (io_info->span_arm & RAID_CTX_SPANARM_ARM_MASK);

	ld = MR_TargetIdToLdGet(io_info->ldTgtId, drv_map);
	raid = MR_LdRaidGet(ld, drv_map);
	span_row_size = instance->UnevenSpanSupport ?
			SPAN_ROW_SIZE(drv_map, ld, span) : raid->rowSize;

	arRef = MR_LdSpanArrayGet(ld, span, drv_map);
	pd0 = MR_ArPdGet(arRef, arm, drv_map);
	pd1 = MR_ArPdGet(arRef, (arm + 1) >= span_row_size ?
		(arm + 1 - span_row_size) : arm + 1, drv_map);

	/* Get PD1 Dev Handle */

	pd1_dev_handle = MR_PdDevHandleGet(pd1, drv_map);

	अगर (pd1_dev_handle == MR_DEVHANDLE_INVALID) अणु
		bestArm = arm;
	पूर्ण अन्यथा अणु
		/* get the pending cmds क्रम the data and mirror arms */
		pend0 = atomic_पढ़ो(&lbInfo->scsi_pending_cmds[pd0]);
		pend1 = atomic_पढ़ो(&lbInfo->scsi_pending_cmds[pd1]);

		/* Determine the disk whose head is nearer to the req. block */
		dअगरf0 = ABS_DIFF(block, lbInfo->last_accessed_block[pd0]);
		dअगरf1 = ABS_DIFF(block, lbInfo->last_accessed_block[pd1]);
		bestArm = (dअगरf0 <= dअगरf1 ? arm : arm ^ 1);

		/* Make balance count from 16 to 4 to
		 *  keep driver in sync with Firmware
		 */
		अगर ((bestArm == arm && pend0 > pend1 + lb_pending_cmds)  ||
		    (bestArm != arm && pend1 > pend0 + lb_pending_cmds))
			bestArm ^= 1;

		/* Update the last accessed block on the correct pd */
		io_info->span_arm =
			(span << RAID_CTX_SPANARM_SPAN_SHIFT) | bestArm;
		io_info->pd_after_lb = (bestArm == arm) ? pd0 : pd1;
	पूर्ण

	lbInfo->last_accessed_block[io_info->pd_after_lb] = block + count - 1;
	वापस io_info->pd_after_lb;
पूर्ण

__le16 get_updated_dev_handle(काष्ठा megasas_instance *instance,
			      काष्ठा LD_LOAD_BALANCE_INFO *lbInfo,
			      काष्ठा IO_REQUEST_INFO *io_info,
			      काष्ठा MR_DRV_RAID_MAP_ALL *drv_map)
अणु
	u8 arm_pd;
	__le16 devHandle;

	/* get best new arm (PD ID) */
	arm_pd  = megasas_get_best_arm_pd(instance, lbInfo, io_info, drv_map);
	devHandle = MR_PdDevHandleGet(arm_pd, drv_map);
	io_info->pd_पूर्णांकerface = MR_PdInterfaceTypeGet(arm_pd, drv_map);
	atomic_inc(&lbInfo->scsi_pending_cmds[arm_pd]);

	वापस devHandle;
पूर्ण
