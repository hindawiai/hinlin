<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/libnvdimm.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/sizes.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <nd-core.h>
#समावेश <पूर्णांकel.h>
#समावेश <nfit.h>
#समावेश <nd.h>
#समावेश "nfit_test.h"
#समावेश "../watermark.h"

#समावेश <यंत्र/mce.h>

/*
 * Generate an NFIT table to describe the following topology:
 *
 * BUS0: Interleaved PMEM regions, and aliasing with BLK regions
 *
 *                     (a)                       (b)            DIMM   BLK-REGION
 *           +----------+--------------+----------+---------+
 * +------+  |  blk2.0  |     pm0.0    |  blk2.1  |  pm1.0  |    0      region2
 * | imc0 +--+- - - - - region0 - - - -+----------+         +
 * +--+---+  |  blk3.0  |     pm0.0    |  blk3.1  |  pm1.0  |    1      region3
 *    |      +----------+--------------v----------v         v
 * +--+---+                            |                    |
 * | cpu0 |                                    region1
 * +--+---+                            |                    |
 *    |      +-------------------------^----------^         ^
 * +--+---+  |                 blk4.0             |  pm1.0  |    2      region4
 * | imc1 +--+-------------------------+----------+         +
 * +------+  |                 blk5.0             |  pm1.0  |    3      region5
 *           +-------------------------+----------+-+-------+
 *
 * +--+---+
 * | cpu1 |
 * +--+---+                   (Hotplug DIMM)
 *    |      +----------------------------------------------+
 * +--+---+  |                 blk6.0/pm7.0                 |    4      region6/7
 * | imc0 +--+----------------------------------------------+
 * +------+
 *
 *
 * *) In this layout we have four dimms and two memory controllers in one
 *    socket.  Each unique पूर्णांकerface (BLK or PMEM) to DPA space
 *    is identअगरied by a region device with a dynamically asचिन्हित id.
 *
 * *) The first portion of dimm0 and dimm1 are पूर्णांकerleaved as REGION0.
 *    A single PMEM namespace "pm0.0" is created using half of the
 *    REGION0 SPA-range.  REGION0 spans dimm0 and dimm1.  PMEM namespace
 *    allocate from from the bottom of a region.  The unallocated
 *    portion of REGION0 aliases with REGION2 and REGION3.  That
 *    unallacted capacity is reclaimed as BLK namespaces ("blk2.0" and
 *    "blk3.0") starting at the base of each DIMM to offset (a) in those
 *    DIMMs.  "pm0.0", "blk2.0" and "blk3.0" are मुक्त-क्रमm पढ़ोable
 *    names that can be asचिन्हित to a namespace.
 *
 * *) In the last portion of dimm0 and dimm1 we have an पूर्णांकerleaved
 *    SPA range, REGION1, that spans those two dimms as well as dimm2
 *    and dimm3.  Some of REGION1 allocated to a PMEM namespace named
 *    "pm1.0" the rest is reclaimed in 4 BLK namespaces (क्रम each
 *    dimm in the पूर्णांकerleave set), "blk2.1", "blk3.1", "blk4.0", and
 *    "blk5.0".
 *
 * *) The portion of dimm2 and dimm3 that करो not participate in the
 *    REGION1 पूर्णांकerleaved SPA range (i.e. the DPA address below offset
 *    (b) are also included in the "blk4.0" and "blk5.0" namespaces.
 *    Note, that BLK namespaces need not be contiguous in DPA-space, and
 *    can consume aliased capacity from multiple पूर्णांकerleave sets.
 *
 * BUS1: Legacy NVDIMM (single contiguous range)
 *
 *  region2
 * +---------------------+
 * |---------------------|
 * ||       pm2.0       ||
 * |---------------------|
 * +---------------------+
 *
 * *) A NFIT-table may describe a simple प्रणाली-physical-address range
 *    with no BLK aliasing.  This type of region may optionally
 *    reference an NVDIMM.
 */
क्रमागत अणु
	NUM_PM  = 3,
	NUM_DCR = 5,
	NUM_HINTS = 8,
	NUM_BDW = NUM_DCR,
	NUM_SPA = NUM_PM + NUM_DCR + NUM_BDW,
	NUM_MEM = NUM_DCR + NUM_BDW + 2 /* spa0 iset */
		+ 4 /* spa1 iset */ + 1 /* spa11 iset */,
	DIMM_SIZE = SZ_32M,
	LABEL_SIZE = SZ_128K,
	SPA_VCD_SIZE = SZ_4M,
	SPA0_SIZE = DIMM_SIZE,
	SPA1_SIZE = DIMM_SIZE*2,
	SPA2_SIZE = DIMM_SIZE,
	BDW_SIZE = 64 << 8,
	DCR_SIZE = 12,
	NUM_NFITS = 2, /* permit testing multiple NFITs per प्रणाली */
पूर्ण;

काष्ठा nfit_test_dcr अणु
	__le64 bdw_addr;
	__le32 bdw_status;
	__u8 aperature[BDW_SIZE];
पूर्ण;

#घोषणा NFIT_DIMM_HANDLE(node, socket, imc, chan, dimm) \
	(((node & 0xfff) << 16) | ((socket & 0xf) << 12) \
	 | ((imc & 0xf) << 8) | ((chan & 0xf) << 4) | (dimm & 0xf))

अटल u32 handle[] = अणु
	[0] = NFIT_DIMM_HANDLE(0, 0, 0, 0, 0),
	[1] = NFIT_DIMM_HANDLE(0, 0, 0, 0, 1),
	[2] = NFIT_DIMM_HANDLE(0, 0, 1, 0, 0),
	[3] = NFIT_DIMM_HANDLE(0, 0, 1, 0, 1),
	[4] = NFIT_DIMM_HANDLE(0, 1, 0, 0, 0),
	[5] = NFIT_DIMM_HANDLE(1, 0, 0, 0, 0),
	[6] = NFIT_DIMM_HANDLE(1, 0, 0, 0, 1),
पूर्ण;

अटल अचिन्हित दीर्घ dimm_fail_cmd_flags[ARRAY_SIZE(handle)];
अटल पूर्णांक dimm_fail_cmd_code[ARRAY_SIZE(handle)];
काष्ठा nfit_test_sec अणु
	u8 state;
	u8 ext_state;
	u8 old_state;
	u8 passphrase[32];
	u8 master_passphrase[32];
	u64 overग_लिखो_end_समय;
पूर्ण dimm_sec_info[NUM_DCR];

अटल स्थिर काष्ठा nd_पूर्णांकel_smart smart_def = अणु
	.flags = ND_INTEL_SMART_HEALTH_VALID
		| ND_INTEL_SMART_SPARES_VALID
		| ND_INTEL_SMART_ALARM_VALID
		| ND_INTEL_SMART_USED_VALID
		| ND_INTEL_SMART_SHUTDOWN_VALID
		| ND_INTEL_SMART_SHUTDOWN_COUNT_VALID
		| ND_INTEL_SMART_MTEMP_VALID
		| ND_INTEL_SMART_CTEMP_VALID,
	.health = ND_INTEL_SMART_NON_CRITICAL_HEALTH,
	.media_temperature = 23 * 16,
	.ctrl_temperature = 25 * 16,
	.pmic_temperature = 40 * 16,
	.spares = 75,
	.alarm_flags = ND_INTEL_SMART_SPARE_TRIP
		| ND_INTEL_SMART_TEMP_TRIP,
	.ait_status = 1,
	.lअगरe_used = 5,
	.shutकरोwn_state = 0,
	.shutकरोwn_count = 42,
	.venकरोr_size = 0,
पूर्ण;

काष्ठा nfit_test_fw अणु
	क्रमागत पूर्णांकel_fw_update_state state;
	u32 context;
	u64 version;
	u32 size_received;
	u64 end_समय;
	bool armed;
	bool missed_activate;
	अचिन्हित दीर्घ last_activate;
पूर्ण;

काष्ठा nfit_test अणु
	काष्ठा acpi_nfit_desc acpi_desc;
	काष्ठा platक्रमm_device pdev;
	काष्ठा list_head resources;
	व्योम *nfit_buf;
	dma_addr_t nfit_dma;
	माप_प्रकार nfit_size;
	माप_प्रकार nfit_filled;
	पूर्णांक dcr_idx;
	पूर्णांक num_dcr;
	पूर्णांक num_pm;
	व्योम **dimm;
	dma_addr_t *dimm_dma;
	व्योम **flush;
	dma_addr_t *flush_dma;
	व्योम **label;
	dma_addr_t *label_dma;
	व्योम **spa_set;
	dma_addr_t *spa_set_dma;
	काष्ठा nfit_test_dcr **dcr;
	dma_addr_t *dcr_dma;
	पूर्णांक (*alloc)(काष्ठा nfit_test *t);
	व्योम (*setup)(काष्ठा nfit_test *t);
	पूर्णांक setup_hotplug;
	जोड़ acpi_object **_fit;
	dma_addr_t _fit_dma;
	काष्ठा ars_state अणु
		काष्ठा nd_cmd_ars_status *ars_status;
		अचिन्हित दीर्घ deadline;
		spinlock_t lock;
	पूर्ण ars_state;
	काष्ठा device *dimm_dev[ARRAY_SIZE(handle)];
	काष्ठा nd_पूर्णांकel_smart *smart;
	काष्ठा nd_पूर्णांकel_smart_threshold *smart_threshold;
	काष्ठा badrange badrange;
	काष्ठा work_काष्ठा work;
	काष्ठा nfit_test_fw *fw;
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *nfit_wq;

अटल काष्ठा gen_pool *nfit_pool;

अटल स्थिर अक्षर zero_key[NVDIMM_PASSPHRASE_LEN];

अटल काष्ठा nfit_test *to_nfit_test(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	वापस container_of(pdev, काष्ठा nfit_test, pdev);
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_get_fw_info(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_fw_info *nd_cmd, अचिन्हित पूर्णांक buf_len,
		पूर्णांक idx)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_fw *fw = &t->fw[idx];

	dev_dbg(dev, "%s(nfit_test: %p nd_cmd: %p, buf_len: %u, idx: %d\n",
			__func__, t, nd_cmd, buf_len, idx);

	अगर (buf_len < माप(*nd_cmd))
		वापस -EINVAL;

	nd_cmd->status = 0;
	nd_cmd->storage_size = INTEL_FW_STORAGE_SIZE;
	nd_cmd->max_send_len = INTEL_FW_MAX_SEND_LEN;
	nd_cmd->query_पूर्णांकerval = INTEL_FW_QUERY_INTERVAL;
	nd_cmd->max_query_समय = INTEL_FW_QUERY_MAX_TIME;
	nd_cmd->update_cap = 0;
	nd_cmd->fis_version = INTEL_FW_FIS_VERSION;
	nd_cmd->run_version = 0;
	nd_cmd->updated_version = fw->version;

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_start_update(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_fw_start *nd_cmd, अचिन्हित पूर्णांक buf_len,
		पूर्णांक idx)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_fw *fw = &t->fw[idx];

	dev_dbg(dev, "%s(nfit_test: %p nd_cmd: %p buf_len: %u idx: %d)\n",
			__func__, t, nd_cmd, buf_len, idx);

	अगर (buf_len < माप(*nd_cmd))
		वापस -EINVAL;

	अगर (fw->state != FW_STATE_NEW) अणु
		/* extended status, FW update in progress */
		nd_cmd->status = 0x10007;
		वापस 0;
	पूर्ण

	fw->state = FW_STATE_IN_PROGRESS;
	fw->context++;
	fw->size_received = 0;
	nd_cmd->status = 0;
	nd_cmd->context = fw->context;

	dev_dbg(dev, "%s: context issued: %#x\n", __func__, nd_cmd->context);

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_send_data(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_fw_send_data *nd_cmd, अचिन्हित पूर्णांक buf_len,
		पूर्णांक idx)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_fw *fw = &t->fw[idx];
	u32 *status = (u32 *)&nd_cmd->data[nd_cmd->length];

	dev_dbg(dev, "%s(nfit_test: %p nd_cmd: %p buf_len: %u idx: %d)\n",
			__func__, t, nd_cmd, buf_len, idx);

	अगर (buf_len < माप(*nd_cmd))
		वापस -EINVAL;


	dev_dbg(dev, "%s: cmd->status: %#x\n", __func__, *status);
	dev_dbg(dev, "%s: cmd->data[0]: %#x\n", __func__, nd_cmd->data[0]);
	dev_dbg(dev, "%s: cmd->data[%u]: %#x\n", __func__, nd_cmd->length-1,
			nd_cmd->data[nd_cmd->length-1]);

	अगर (fw->state != FW_STATE_IN_PROGRESS) अणु
		dev_dbg(dev, "%s: not in IN_PROGRESS state\n", __func__);
		*status = 0x5;
		वापस 0;
	पूर्ण

	अगर (nd_cmd->context != fw->context) अणु
		dev_dbg(dev, "%s: incorrect context: in: %#x correct: %#x\n",
				__func__, nd_cmd->context, fw->context);
		*status = 0x10007;
		वापस 0;
	पूर्ण

	/*
	 * check offset + len > size of fw storage
	 * check length is > max send length
	 */
	अगर (nd_cmd->offset + nd_cmd->length > INTEL_FW_STORAGE_SIZE ||
			nd_cmd->length > INTEL_FW_MAX_SEND_LEN) अणु
		*status = 0x3;
		dev_dbg(dev, "%s: buffer boundary violation\n", __func__);
		वापस 0;
	पूर्ण

	fw->size_received += nd_cmd->length;
	dev_dbg(dev, "%s: copying %u bytes, %u bytes so far\n",
			__func__, nd_cmd->length, fw->size_received);
	*status = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_finish_fw(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_fw_finish_update *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक idx)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_fw *fw = &t->fw[idx];

	dev_dbg(dev, "%s(nfit_test: %p nd_cmd: %p buf_len: %u idx: %d)\n",
			__func__, t, nd_cmd, buf_len, idx);

	अगर (fw->state == FW_STATE_UPDATED) अणु
		/* update alपढ़ोy करोne, need activation */
		nd_cmd->status = 0x20007;
		वापस 0;
	पूर्ण

	dev_dbg(dev, "%s: context: %#x  ctrl_flags: %#x\n",
			__func__, nd_cmd->context, nd_cmd->ctrl_flags);

	चयन (nd_cmd->ctrl_flags) अणु
	हाल 0: /* finish */
		अगर (nd_cmd->context != fw->context) अणु
			dev_dbg(dev, "%s: incorrect context: in: %#x correct: %#x\n",
					__func__, nd_cmd->context,
					fw->context);
			nd_cmd->status = 0x10007;
			वापस 0;
		पूर्ण
		nd_cmd->status = 0;
		fw->state = FW_STATE_VERIFY;
		/* set 1 second of समय क्रम firmware "update" */
		fw->end_समय = jअगरfies + HZ;
		अवरोध;

	हाल 1: /* पात */
		fw->size_received = 0;
		/* successfully पातed status */
		nd_cmd->status = 0x40007;
		fw->state = FW_STATE_NEW;
		dev_dbg(dev, "%s: abort successful\n", __func__);
		अवरोध;

	शेष: /* bad control flag */
		dev_warn(dev, "%s: unknown control flag: %#x\n",
				__func__, nd_cmd->ctrl_flags);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_finish_query(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_fw_finish_query *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक idx)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_fw *fw = &t->fw[idx];

	dev_dbg(dev, "%s(nfit_test: %p nd_cmd: %p buf_len: %u idx: %d)\n",
			__func__, t, nd_cmd, buf_len, idx);

	अगर (buf_len < माप(*nd_cmd))
		वापस -EINVAL;

	अगर (nd_cmd->context != fw->context) अणु
		dev_dbg(dev, "%s: incorrect context: in: %#x correct: %#x\n",
				__func__, nd_cmd->context, fw->context);
		nd_cmd->status = 0x10007;
		वापस 0;
	पूर्ण

	dev_dbg(dev, "%s context: %#x\n", __func__, nd_cmd->context);

	चयन (fw->state) अणु
	हाल FW_STATE_NEW:
		nd_cmd->updated_fw_rev = 0;
		nd_cmd->status = 0;
		dev_dbg(dev, "%s: new state\n", __func__);
		अवरोध;

	हाल FW_STATE_IN_PROGRESS:
		/* sequencing error */
		nd_cmd->status = 0x40007;
		nd_cmd->updated_fw_rev = 0;
		dev_dbg(dev, "%s: sequence error\n", __func__);
		अवरोध;

	हाल FW_STATE_VERIFY:
		अगर (समय_is_after_jअगरfies64(fw->end_समय)) अणु
			nd_cmd->updated_fw_rev = 0;
			nd_cmd->status = 0x20007;
			dev_dbg(dev, "%s: still verifying\n", __func__);
			अवरोध;
		पूर्ण
		dev_dbg(dev, "%s: transition out verify\n", __func__);
		fw->state = FW_STATE_UPDATED;
		fw->missed_activate = false;
		/* fall through */
	हाल FW_STATE_UPDATED:
		nd_cmd->status = 0;
		/* bogus test version */
		fw->version = nd_cmd->updated_fw_rev =
			INTEL_FW_FAKE_VERSION;
		dev_dbg(dev, "%s: updated\n", __func__);
		अवरोध;

	शेष: /* we should never get here */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfit_test_cmd_get_config_size(काष्ठा nd_cmd_get_config_size *nd_cmd,
		अचिन्हित पूर्णांक buf_len)
अणु
	अगर (buf_len < माप(*nd_cmd))
		वापस -EINVAL;

	nd_cmd->status = 0;
	nd_cmd->config_size = LABEL_SIZE;
	nd_cmd->max_xfer = SZ_4K;

	वापस 0;
पूर्ण

अटल पूर्णांक nfit_test_cmd_get_config_data(काष्ठा nd_cmd_get_config_data_hdr
		*nd_cmd, अचिन्हित पूर्णांक buf_len, व्योम *label)
अणु
	अचिन्हित पूर्णांक len, offset = nd_cmd->in_offset;
	पूर्णांक rc;

	अगर (buf_len < माप(*nd_cmd))
		वापस -EINVAL;
	अगर (offset >= LABEL_SIZE)
		वापस -EINVAL;
	अगर (nd_cmd->in_length + माप(*nd_cmd) > buf_len)
		वापस -EINVAL;

	nd_cmd->status = 0;
	len = min(nd_cmd->in_length, LABEL_SIZE - offset);
	स_नकल(nd_cmd->out_buf, label + offset, len);
	rc = buf_len - माप(*nd_cmd) - len;

	वापस rc;
पूर्ण

अटल पूर्णांक nfit_test_cmd_set_config_data(काष्ठा nd_cmd_set_config_hdr *nd_cmd,
		अचिन्हित पूर्णांक buf_len, व्योम *label)
अणु
	अचिन्हित पूर्णांक len, offset = nd_cmd->in_offset;
	u32 *status;
	पूर्णांक rc;

	अगर (buf_len < माप(*nd_cmd))
		वापस -EINVAL;
	अगर (offset >= LABEL_SIZE)
		वापस -EINVAL;
	अगर (nd_cmd->in_length + माप(*nd_cmd) + 4 > buf_len)
		वापस -EINVAL;

	status = (व्योम *)nd_cmd + nd_cmd->in_length + माप(*nd_cmd);
	*status = 0;
	len = min(nd_cmd->in_length, LABEL_SIZE - offset);
	स_नकल(label + offset, nd_cmd->in_buf, len);
	rc = buf_len - माप(*nd_cmd) - (len + 4);

	वापस rc;
पूर्ण

#घोषणा NFIT_TEST_CLEAR_ERR_UNIT 256

अटल पूर्णांक nfit_test_cmd_ars_cap(काष्ठा nd_cmd_ars_cap *nd_cmd,
		अचिन्हित पूर्णांक buf_len)
अणु
	पूर्णांक ars_recs;

	अगर (buf_len < माप(*nd_cmd))
		वापस -EINVAL;

	/* क्रम testing, only store up to n records that fit within 4k */
	ars_recs = SZ_4K / माप(काष्ठा nd_ars_record);

	nd_cmd->max_ars_out = माप(काष्ठा nd_cmd_ars_status)
		+ ars_recs * माप(काष्ठा nd_ars_record);
	nd_cmd->status = (ND_ARS_PERSISTENT | ND_ARS_VOLATILE) << 16;
	nd_cmd->clear_err_unit = NFIT_TEST_CLEAR_ERR_UNIT;

	वापस 0;
पूर्ण

अटल व्योम post_ars_status(काष्ठा ars_state *ars_state,
		काष्ठा badrange *badrange, u64 addr, u64 len)
अणु
	काष्ठा nd_cmd_ars_status *ars_status;
	काष्ठा nd_ars_record *ars_record;
	काष्ठा badrange_entry *be;
	u64 end = addr + len - 1;
	पूर्णांक i = 0;

	ars_state->deadline = jअगरfies + 1*HZ;
	ars_status = ars_state->ars_status;
	ars_status->status = 0;
	ars_status->address = addr;
	ars_status->length = len;
	ars_status->type = ND_ARS_PERSISTENT;

	spin_lock(&badrange->lock);
	list_क्रम_each_entry(be, &badrange->list, list) अणु
		u64 be_end = be->start + be->length - 1;
		u64 rstart, rend;

		/* skip entries outside the range */
		अगर (be_end < addr || be->start > end)
			जारी;

		rstart = (be->start < addr) ? addr : be->start;
		rend = (be_end < end) ? be_end : end;
		ars_record = &ars_status->records[i];
		ars_record->handle = 0;
		ars_record->err_address = rstart;
		ars_record->length = rend - rstart + 1;
		i++;
	पूर्ण
	spin_unlock(&badrange->lock);
	ars_status->num_records = i;
	ars_status->out_length = माप(काष्ठा nd_cmd_ars_status)
		+ i * माप(काष्ठा nd_ars_record);
पूर्ण

अटल पूर्णांक nfit_test_cmd_ars_start(काष्ठा nfit_test *t,
		काष्ठा ars_state *ars_state,
		काष्ठा nd_cmd_ars_start *ars_start, अचिन्हित पूर्णांक buf_len,
		पूर्णांक *cmd_rc)
अणु
	अगर (buf_len < माप(*ars_start))
		वापस -EINVAL;

	spin_lock(&ars_state->lock);
	अगर (समय_beक्रमe(jअगरfies, ars_state->deadline)) अणु
		ars_start->status = NFIT_ARS_START_BUSY;
		*cmd_rc = -EBUSY;
	पूर्ण अन्यथा अणु
		ars_start->status = 0;
		ars_start->scrub_समय = 1;
		post_ars_status(ars_state, &t->badrange, ars_start->address,
				ars_start->length);
		*cmd_rc = 0;
	पूर्ण
	spin_unlock(&ars_state->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक nfit_test_cmd_ars_status(काष्ठा ars_state *ars_state,
		काष्ठा nd_cmd_ars_status *ars_status, अचिन्हित पूर्णांक buf_len,
		पूर्णांक *cmd_rc)
अणु
	अगर (buf_len < ars_state->ars_status->out_length)
		वापस -EINVAL;

	spin_lock(&ars_state->lock);
	अगर (समय_beक्रमe(jअगरfies, ars_state->deadline)) अणु
		स_रखो(ars_status, 0, buf_len);
		ars_status->status = NFIT_ARS_STATUS_BUSY;
		ars_status->out_length = माप(*ars_status);
		*cmd_rc = -EBUSY;
	पूर्ण अन्यथा अणु
		स_नकल(ars_status, ars_state->ars_status,
				ars_state->ars_status->out_length);
		*cmd_rc = 0;
	पूर्ण
	spin_unlock(&ars_state->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक nfit_test_cmd_clear_error(काष्ठा nfit_test *t,
		काष्ठा nd_cmd_clear_error *clear_err,
		अचिन्हित पूर्णांक buf_len, पूर्णांक *cmd_rc)
अणु
	स्थिर u64 mask = NFIT_TEST_CLEAR_ERR_UNIT - 1;
	अगर (buf_len < माप(*clear_err))
		वापस -EINVAL;

	अगर ((clear_err->address & mask) || (clear_err->length & mask))
		वापस -EINVAL;

	badrange_क्रमget(&t->badrange, clear_err->address, clear_err->length);
	clear_err->status = 0;
	clear_err->cleared = clear_err->length;
	*cmd_rc = 0;
	वापस 0;
पूर्ण

काष्ठा region_search_spa अणु
	u64 addr;
	काष्ठा nd_region *region;
पूर्ण;

अटल पूर्णांक is_region_device(काष्ठा device *dev)
अणु
	वापस !म_भेदन(dev->kobj.name, "region", 6);
पूर्ण

अटल पूर्णांक nfit_test_search_region_spa(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा region_search_spa *ctx = data;
	काष्ठा nd_region *nd_region;
	resource_माप_प्रकार ndr_end;

	अगर (!is_region_device(dev))
		वापस 0;

	nd_region = to_nd_region(dev);
	ndr_end = nd_region->ndr_start + nd_region->ndr_size;

	अगर (ctx->addr >= nd_region->ndr_start && ctx->addr < ndr_end) अणु
		ctx->region = nd_region;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfit_test_search_spa(काष्ठा nvdimm_bus *bus,
		काष्ठा nd_cmd_translate_spa *spa)
अणु
	पूर्णांक ret;
	काष्ठा nd_region *nd_region = शून्य;
	काष्ठा nvdimm *nvdimm = शून्य;
	काष्ठा nd_mapping *nd_mapping = शून्य;
	काष्ठा region_search_spa ctx = अणु
		.addr = spa->spa,
		.region = शून्य,
	पूर्ण;
	u64 dpa;

	ret = device_क्रम_each_child(&bus->dev, &ctx,
				nfit_test_search_region_spa);

	अगर (!ret)
		वापस -ENODEV;

	nd_region = ctx.region;

	dpa = ctx.addr - nd_region->ndr_start;

	/*
	 * last dimm is selected क्रम test
	 */
	nd_mapping = &nd_region->mapping[nd_region->ndr_mappings - 1];
	nvdimm = nd_mapping->nvdimm;

	spa->devices[0].nfit_device_handle = handle[nvdimm->id];
	spa->num_nvdimms = 1;
	spa->devices[0].dpa = dpa;

	वापस 0;
पूर्ण

अटल पूर्णांक nfit_test_cmd_translate_spa(काष्ठा nvdimm_bus *bus,
		काष्ठा nd_cmd_translate_spa *spa, अचिन्हित पूर्णांक buf_len)
अणु
	अगर (buf_len < spa->translate_length)
		वापस -EINVAL;

	अगर (nfit_test_search_spa(bus, spa) < 0 || !spa->num_nvdimms)
		spa->status = 2;

	वापस 0;
पूर्ण

अटल पूर्णांक nfit_test_cmd_smart(काष्ठा nd_पूर्णांकel_smart *smart, अचिन्हित पूर्णांक buf_len,
		काष्ठा nd_पूर्णांकel_smart *smart_data)
अणु
	अगर (buf_len < माप(*smart))
		वापस -EINVAL;
	स_नकल(smart, smart_data, माप(*smart));
	वापस 0;
पूर्ण

अटल पूर्णांक nfit_test_cmd_smart_threshold(
		काष्ठा nd_पूर्णांकel_smart_threshold *out,
		अचिन्हित पूर्णांक buf_len,
		काष्ठा nd_पूर्णांकel_smart_threshold *smart_t)
अणु
	अगर (buf_len < माप(*smart_t))
		वापस -EINVAL;
	स_नकल(out, smart_t, माप(*smart_t));
	वापस 0;
पूर्ण

अटल व्योम smart_notअगरy(काष्ठा device *bus_dev,
		काष्ठा device *dimm_dev, काष्ठा nd_पूर्णांकel_smart *smart,
		काष्ठा nd_पूर्णांकel_smart_threshold *thresh)
अणु
	dev_dbg(dimm_dev, "%s: alarm: %#x spares: %d (%d) mtemp: %d (%d) ctemp: %d (%d)\n",
			__func__, thresh->alarm_control, thresh->spares,
			smart->spares, thresh->media_temperature,
			smart->media_temperature, thresh->ctrl_temperature,
			smart->ctrl_temperature);
	अगर (((thresh->alarm_control & ND_INTEL_SMART_SPARE_TRIP)
				&& smart->spares
				<= thresh->spares)
			|| ((thresh->alarm_control & ND_INTEL_SMART_TEMP_TRIP)
				&& smart->media_temperature
				>= thresh->media_temperature)
			|| ((thresh->alarm_control & ND_INTEL_SMART_CTEMP_TRIP)
				&& smart->ctrl_temperature
				>= thresh->ctrl_temperature)
			|| (smart->health != ND_INTEL_SMART_NON_CRITICAL_HEALTH)
			|| (smart->shutकरोwn_state != 0)) अणु
		device_lock(bus_dev);
		__acpi_nvdimm_notअगरy(dimm_dev, 0x81);
		device_unlock(bus_dev);
	पूर्ण
पूर्ण

अटल पूर्णांक nfit_test_cmd_smart_set_threshold(
		काष्ठा nd_पूर्णांकel_smart_set_threshold *in,
		अचिन्हित पूर्णांक buf_len,
		काष्ठा nd_पूर्णांकel_smart_threshold *thresh,
		काष्ठा nd_पूर्णांकel_smart *smart,
		काष्ठा device *bus_dev, काष्ठा device *dimm_dev)
अणु
	अचिन्हित पूर्णांक size;

	size = माप(*in) - 4;
	अगर (buf_len < size)
		वापस -EINVAL;
	स_नकल(thresh->data, in, size);
	in->status = 0;
	smart_notअगरy(bus_dev, dimm_dev, smart, thresh);

	वापस 0;
पूर्ण

अटल पूर्णांक nfit_test_cmd_smart_inject(
		काष्ठा nd_पूर्णांकel_smart_inject *inj,
		अचिन्हित पूर्णांक buf_len,
		काष्ठा nd_पूर्णांकel_smart_threshold *thresh,
		काष्ठा nd_पूर्णांकel_smart *smart,
		काष्ठा device *bus_dev, काष्ठा device *dimm_dev)
अणु
	अगर (buf_len != माप(*inj))
		वापस -EINVAL;

	अगर (inj->flags & ND_INTEL_SMART_INJECT_MTEMP) अणु
		अगर (inj->mtemp_enable)
			smart->media_temperature = inj->media_temperature;
		अन्यथा
			smart->media_temperature = smart_def.media_temperature;
	पूर्ण
	अगर (inj->flags & ND_INTEL_SMART_INJECT_SPARE) अणु
		अगर (inj->spare_enable)
			smart->spares = inj->spares;
		अन्यथा
			smart->spares = smart_def.spares;
	पूर्ण
	अगर (inj->flags & ND_INTEL_SMART_INJECT_FATAL) अणु
		अगर (inj->fatal_enable)
			smart->health = ND_INTEL_SMART_FATAL_HEALTH;
		अन्यथा
			smart->health = ND_INTEL_SMART_NON_CRITICAL_HEALTH;
	पूर्ण
	अगर (inj->flags & ND_INTEL_SMART_INJECT_SHUTDOWN) अणु
		अगर (inj->unsafe_shutकरोwn_enable) अणु
			smart->shutकरोwn_state = 1;
			smart->shutकरोwn_count++;
		पूर्ण अन्यथा
			smart->shutकरोwn_state = 0;
	पूर्ण
	inj->status = 0;
	smart_notअगरy(bus_dev, dimm_dev, smart, thresh);

	वापस 0;
पूर्ण

अटल व्योम uc_error_notअगरy(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfit_test *t = container_of(work, typeof(*t), work);

	__acpi_nfit_notअगरy(&t->pdev.dev, t, NFIT_NOTIFY_UC_MEMORY_ERROR);
पूर्ण

अटल पूर्णांक nfit_test_cmd_ars_error_inject(काष्ठा nfit_test *t,
		काष्ठा nd_cmd_ars_err_inj *err_inj, अचिन्हित पूर्णांक buf_len)
अणु
	पूर्णांक rc;

	अगर (buf_len != माप(*err_inj)) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (err_inj->err_inj_spa_range_length <= 0) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	rc =  badrange_add(&t->badrange, err_inj->err_inj_spa_range_base,
			err_inj->err_inj_spa_range_length);
	अगर (rc < 0)
		जाओ err;

	अगर (err_inj->err_inj_options & (1 << ND_ARS_ERR_INJ_OPT_NOTIFY))
		queue_work(nfit_wq, &t->work);

	err_inj->status = 0;
	वापस 0;

err:
	err_inj->status = NFIT_ARS_INJECT_INVALID;
	वापस rc;
पूर्ण

अटल पूर्णांक nfit_test_cmd_ars_inject_clear(काष्ठा nfit_test *t,
		काष्ठा nd_cmd_ars_err_inj_clr *err_clr, अचिन्हित पूर्णांक buf_len)
अणु
	पूर्णांक rc;

	अगर (buf_len != माप(*err_clr)) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (err_clr->err_inj_clr_spa_range_length <= 0) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	badrange_क्रमget(&t->badrange, err_clr->err_inj_clr_spa_range_base,
			err_clr->err_inj_clr_spa_range_length);

	err_clr->status = 0;
	वापस 0;

err:
	err_clr->status = NFIT_ARS_INJECT_INVALID;
	वापस rc;
पूर्ण

अटल पूर्णांक nfit_test_cmd_ars_inject_status(काष्ठा nfit_test *t,
		काष्ठा nd_cmd_ars_err_inj_stat *err_stat,
		अचिन्हित पूर्णांक buf_len)
अणु
	काष्ठा badrange_entry *be;
	पूर्णांक max = SZ_4K / माप(काष्ठा nd_error_stat_query_record);
	पूर्णांक i = 0;

	err_stat->status = 0;
	spin_lock(&t->badrange.lock);
	list_क्रम_each_entry(be, &t->badrange.list, list) अणु
		err_stat->record[i].err_inj_stat_spa_range_base = be->start;
		err_stat->record[i].err_inj_stat_spa_range_length = be->length;
		i++;
		अगर (i > max)
			अवरोध;
	पूर्ण
	spin_unlock(&t->badrange.lock);
	err_stat->inj_err_rec_count = i;

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_set_lss_status(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_lss *nd_cmd, अचिन्हित पूर्णांक buf_len)
अणु
	काष्ठा device *dev = &t->pdev.dev;

	अगर (buf_len < माप(*nd_cmd))
		वापस -EINVAL;

	चयन (nd_cmd->enable) अणु
	हाल 0:
		nd_cmd->status = 0;
		dev_dbg(dev, "%s: Latch System Shutdown Status disabled\n",
				__func__);
		अवरोध;
	हाल 1:
		nd_cmd->status = 0;
		dev_dbg(dev, "%s: Latch System Shutdown Status enabled\n",
				__func__);
		अवरोध;
	शेष:
		dev_warn(dev, "Unknown enable value: %#x\n", nd_cmd->enable);
		nd_cmd->status = 0x3;
		अवरोध;
	पूर्ण


	वापस 0;
पूर्ण

अटल पूर्णांक override_वापस_code(पूर्णांक dimm, अचिन्हित पूर्णांक func, पूर्णांक rc)
अणु
	अगर ((1 << func) & dimm_fail_cmd_flags[dimm]) अणु
		अगर (dimm_fail_cmd_code[dimm])
			वापस dimm_fail_cmd_code[dimm];
		वापस -EIO;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_security_status(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_get_security_state *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक dimm)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_sec *sec = &dimm_sec_info[dimm];

	nd_cmd->status = 0;
	nd_cmd->state = sec->state;
	nd_cmd->extended_state = sec->ext_state;
	dev_dbg(dev, "security state (%#x) returned\n", nd_cmd->state);

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_unlock_unit(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_unlock_unit *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक dimm)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_sec *sec = &dimm_sec_info[dimm];

	अगर (!(sec->state & ND_INTEL_SEC_STATE_LOCKED) ||
			(sec->state & ND_INTEL_SEC_STATE_FROZEN)) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_STATE;
		dev_dbg(dev, "unlock unit: invalid state: %#x\n",
				sec->state);
	पूर्ण अन्यथा अगर (स_भेद(nd_cmd->passphrase, sec->passphrase,
				ND_INTEL_PASSPHRASE_SIZE) != 0) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_PASS;
		dev_dbg(dev, "unlock unit: invalid passphrase\n");
	पूर्ण अन्यथा अणु
		nd_cmd->status = 0;
		sec->state = ND_INTEL_SEC_STATE_ENABLED;
		dev_dbg(dev, "Unit unlocked\n");
	पूर्ण

	dev_dbg(dev, "unlocking status returned: %#x\n", nd_cmd->status);
	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_set_pass(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_set_passphrase *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक dimm)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_sec *sec = &dimm_sec_info[dimm];

	अगर (sec->state & ND_INTEL_SEC_STATE_FROZEN) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_STATE;
		dev_dbg(dev, "set passphrase: wrong security state\n");
	पूर्ण अन्यथा अगर (स_भेद(nd_cmd->old_pass, sec->passphrase,
				ND_INTEL_PASSPHRASE_SIZE) != 0) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_PASS;
		dev_dbg(dev, "set passphrase: wrong passphrase\n");
	पूर्ण अन्यथा अणु
		स_नकल(sec->passphrase, nd_cmd->new_pass,
				ND_INTEL_PASSPHRASE_SIZE);
		sec->state |= ND_INTEL_SEC_STATE_ENABLED;
		nd_cmd->status = 0;
		dev_dbg(dev, "passphrase updated\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_मुक्तze_lock(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_मुक्तze_lock *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक dimm)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_sec *sec = &dimm_sec_info[dimm];

	अगर (!(sec->state & ND_INTEL_SEC_STATE_ENABLED)) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_STATE;
		dev_dbg(dev, "freeze lock: wrong security state\n");
	पूर्ण अन्यथा अणु
		sec->state |= ND_INTEL_SEC_STATE_FROZEN;
		nd_cmd->status = 0;
		dev_dbg(dev, "security frozen\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_disable_pass(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_disable_passphrase *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक dimm)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_sec *sec = &dimm_sec_info[dimm];

	अगर (!(sec->state & ND_INTEL_SEC_STATE_ENABLED) ||
			(sec->state & ND_INTEL_SEC_STATE_FROZEN)) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_STATE;
		dev_dbg(dev, "disable passphrase: wrong security state\n");
	पूर्ण अन्यथा अगर (स_भेद(nd_cmd->passphrase, sec->passphrase,
				ND_INTEL_PASSPHRASE_SIZE) != 0) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_PASS;
		dev_dbg(dev, "disable passphrase: wrong passphrase\n");
	पूर्ण अन्यथा अणु
		स_रखो(sec->passphrase, 0, ND_INTEL_PASSPHRASE_SIZE);
		sec->state = 0;
		dev_dbg(dev, "disable passphrase: done\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_secure_erase(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_secure_erase *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक dimm)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_sec *sec = &dimm_sec_info[dimm];

	अगर (sec->state & ND_INTEL_SEC_STATE_FROZEN) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_STATE;
		dev_dbg(dev, "secure erase: wrong security state\n");
	पूर्ण अन्यथा अगर (स_भेद(nd_cmd->passphrase, sec->passphrase,
				ND_INTEL_PASSPHRASE_SIZE) != 0) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_PASS;
		dev_dbg(dev, "secure erase: wrong passphrase\n");
	पूर्ण अन्यथा अणु
		अगर (!(sec->state & ND_INTEL_SEC_STATE_ENABLED)
				&& (स_भेद(nd_cmd->passphrase, zero_key,
					ND_INTEL_PASSPHRASE_SIZE) != 0)) अणु
			dev_dbg(dev, "invalid zero key\n");
			वापस 0;
		पूर्ण
		स_रखो(sec->passphrase, 0, ND_INTEL_PASSPHRASE_SIZE);
		स_रखो(sec->master_passphrase, 0, ND_INTEL_PASSPHRASE_SIZE);
		sec->state = 0;
		sec->ext_state = ND_INTEL_SEC_ESTATE_ENABLED;
		dev_dbg(dev, "secure erase: done\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_overग_लिखो(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_overग_लिखो *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक dimm)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_sec *sec = &dimm_sec_info[dimm];

	अगर ((sec->state & ND_INTEL_SEC_STATE_ENABLED) &&
			स_भेद(nd_cmd->passphrase, sec->passphrase,
				ND_INTEL_PASSPHRASE_SIZE) != 0) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_PASS;
		dev_dbg(dev, "overwrite: wrong passphrase\n");
		वापस 0;
	पूर्ण

	sec->old_state = sec->state;
	sec->state = ND_INTEL_SEC_STATE_OVERWRITE;
	dev_dbg(dev, "overwrite progressing.\n");
	sec->overग_लिखो_end_समय = get_jअगरfies_64() + 5 * HZ;

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_query_overग_लिखो(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_query_overग_लिखो *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक dimm)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_sec *sec = &dimm_sec_info[dimm];

	अगर (!(sec->state & ND_INTEL_SEC_STATE_OVERWRITE)) अणु
		nd_cmd->status = ND_INTEL_STATUS_OQUERY_SEQUENCE_ERR;
		वापस 0;
	पूर्ण

	अगर (समय_is_beक्रमe_jअगरfies64(sec->overग_लिखो_end_समय)) अणु
		sec->overग_लिखो_end_समय = 0;
		sec->state = sec->old_state;
		sec->old_state = 0;
		sec->ext_state = ND_INTEL_SEC_ESTATE_ENABLED;
		dev_dbg(dev, "overwrite is complete\n");
	पूर्ण अन्यथा
		nd_cmd->status = ND_INTEL_STATUS_OQUERY_INPROGRESS;
	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_master_set_pass(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_set_master_passphrase *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक dimm)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_sec *sec = &dimm_sec_info[dimm];

	अगर (!(sec->ext_state & ND_INTEL_SEC_ESTATE_ENABLED)) अणु
		nd_cmd->status = ND_INTEL_STATUS_NOT_SUPPORTED;
		dev_dbg(dev, "master set passphrase: in wrong state\n");
	पूर्ण अन्यथा अगर (sec->ext_state & ND_INTEL_SEC_ESTATE_PLIMIT) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_STATE;
		dev_dbg(dev, "master set passphrase: in wrong security state\n");
	पूर्ण अन्यथा अगर (स_भेद(nd_cmd->old_pass, sec->master_passphrase,
				ND_INTEL_PASSPHRASE_SIZE) != 0) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_PASS;
		dev_dbg(dev, "master set passphrase: wrong passphrase\n");
	पूर्ण अन्यथा अणु
		स_नकल(sec->master_passphrase, nd_cmd->new_pass,
				ND_INTEL_PASSPHRASE_SIZE);
		sec->ext_state = ND_INTEL_SEC_ESTATE_ENABLED;
		dev_dbg(dev, "master passphrase: updated\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_master_secure_erase(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_master_secure_erase *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक dimm)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_sec *sec = &dimm_sec_info[dimm];

	अगर (!(sec->ext_state & ND_INTEL_SEC_ESTATE_ENABLED)) अणु
		nd_cmd->status = ND_INTEL_STATUS_NOT_SUPPORTED;
		dev_dbg(dev, "master secure erase: in wrong state\n");
	पूर्ण अन्यथा अगर (sec->ext_state & ND_INTEL_SEC_ESTATE_PLIMIT) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_STATE;
		dev_dbg(dev, "master secure erase: in wrong security state\n");
	पूर्ण अन्यथा अगर (स_भेद(nd_cmd->passphrase, sec->master_passphrase,
				ND_INTEL_PASSPHRASE_SIZE) != 0) अणु
		nd_cmd->status = ND_INTEL_STATUS_INVALID_PASS;
		dev_dbg(dev, "master secure erase: wrong passphrase\n");
	पूर्ण अन्यथा अणु
		/* we करो not erase master state passphrase ever */
		sec->ext_state = ND_INTEL_SEC_ESTATE_ENABLED;
		स_रखो(sec->passphrase, 0, ND_INTEL_PASSPHRASE_SIZE);
		sec->state = 0;
		dev_dbg(dev, "master secure erase: done\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ last_activate;

अटल पूर्णांक nvdimm_bus_पूर्णांकel_fw_activate_businfo(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_bus_fw_activate_businfo *nd_cmd,
		अचिन्हित पूर्णांक buf_len)
अणु
	पूर्णांक i, armed = 0;
	पूर्णांक state;
	u64 पंचांगo;

	क्रम (i = 0; i < NUM_DCR; i++) अणु
		काष्ठा nfit_test_fw *fw = &t->fw[i];

		अगर (fw->armed)
			armed++;
	पूर्ण

	/*
	 * Emulate 3 second activation max, and 1 second incremental
	 * quiesce समय per dimm requiring multiple activates to get all
	 * DIMMs updated.
	 */
	अगर (armed)
		state = ND_INTEL_FWA_ARMED;
	अन्यथा अगर (!last_activate || समय_after(jअगरfies, last_activate + 3 * HZ))
		state = ND_INTEL_FWA_IDLE;
	अन्यथा
		state = ND_INTEL_FWA_BUSY;

	पंचांगo = armed * USEC_PER_SEC;
	*nd_cmd = (काष्ठा nd_पूर्णांकel_bus_fw_activate_businfo) अणु
		.capability = ND_INTEL_BUS_FWA_CAP_FWQUIESCE
			| ND_INTEL_BUS_FWA_CAP_OSQUIESCE
			| ND_INTEL_BUS_FWA_CAP_RESET,
		.state = state,
		.activate_पंचांगo = पंचांगo,
		.cpu_quiesce_पंचांगo = पंचांगo,
		.io_quiesce_पंचांगo = पंचांगo,
		.max_quiesce_पंचांगo = 3 * USEC_PER_SEC,
	पूर्ण;

	वापस 0;
पूर्ण

अटल पूर्णांक nvdimm_bus_पूर्णांकel_fw_activate(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_bus_fw_activate *nd_cmd,
		अचिन्हित पूर्णांक buf_len)
अणु
	काष्ठा nd_पूर्णांकel_bus_fw_activate_businfo info;
	u32 status = 0;
	पूर्णांक i;

	nvdimm_bus_पूर्णांकel_fw_activate_businfo(t, &info, माप(info));
	अगर (info.state == ND_INTEL_FWA_BUSY)
		status = ND_INTEL_BUS_FWA_STATUS_BUSY;
	अन्यथा अगर (info.activate_पंचांगo > info.max_quiesce_पंचांगo)
		status = ND_INTEL_BUS_FWA_STATUS_TMO;
	अन्यथा अगर (info.state == ND_INTEL_FWA_IDLE)
		status = ND_INTEL_BUS_FWA_STATUS_NOARM;

	dev_dbg(&t->pdev.dev, "status: %d\n", status);
	nd_cmd->status = status;
	अगर (status && status != ND_INTEL_BUS_FWA_STATUS_TMO)
		वापस 0;

	last_activate = jअगरfies;
	क्रम (i = 0; i < NUM_DCR; i++) अणु
		काष्ठा nfit_test_fw *fw = &t->fw[i];

		अगर (!fw->armed)
			जारी;
		अगर (fw->state != FW_STATE_UPDATED)
			fw->missed_activate = true;
		अन्यथा
			fw->state = FW_STATE_NEW;
		fw->armed = false;
		fw->last_activate = last_activate;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_fw_activate_dimminfo(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_fw_activate_dimminfo *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक dimm)
अणु
	काष्ठा nd_पूर्णांकel_bus_fw_activate_businfo info;
	काष्ठा nfit_test_fw *fw = &t->fw[dimm];
	u32 result, state;

	nvdimm_bus_पूर्णांकel_fw_activate_businfo(t, &info, माप(info));

	अगर (info.state == ND_INTEL_FWA_BUSY)
		state = ND_INTEL_FWA_BUSY;
	अन्यथा अगर (info.state == ND_INTEL_FWA_IDLE)
		state = ND_INTEL_FWA_IDLE;
	अन्यथा अगर (fw->armed)
		state = ND_INTEL_FWA_ARMED;
	अन्यथा
		state = ND_INTEL_FWA_IDLE;

	result = ND_INTEL_DIMM_FWA_NONE;
	अगर (last_activate && fw->last_activate == last_activate &&
			state == ND_INTEL_FWA_IDLE) अणु
		अगर (fw->missed_activate)
			result = ND_INTEL_DIMM_FWA_NOTSTAGED;
		अन्यथा
			result = ND_INTEL_DIMM_FWA_SUCCESS;
	पूर्ण

	*nd_cmd = (काष्ठा nd_पूर्णांकel_fw_activate_dimminfo) अणु
		.result = result,
		.state = state,
	पूर्ण;

	वापस 0;
पूर्ण

अटल पूर्णांक nd_पूर्णांकel_test_cmd_fw_activate_arm(काष्ठा nfit_test *t,
		काष्ठा nd_पूर्णांकel_fw_activate_arm *nd_cmd,
		अचिन्हित पूर्णांक buf_len, पूर्णांक dimm)
अणु
	काष्ठा nfit_test_fw *fw = &t->fw[dimm];

	fw->armed = nd_cmd->activate_arm == ND_INTEL_DIMM_FWA_ARM;
	nd_cmd->status = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक get_dimm(काष्ठा nfit_mem *nfit_mem, अचिन्हित पूर्णांक func)
अणु
	पूर्णांक i;

	/* lookup per-dimm data */
	क्रम (i = 0; i < ARRAY_SIZE(handle); i++)
		अगर (__to_nfit_memdev(nfit_mem)->device_handle == handle[i])
			अवरोध;
	अगर (i >= ARRAY_SIZE(handle))
		वापस -ENXIO;
	वापस i;
पूर्ण

अटल व्योम nfit_ctl_dbg(काष्ठा acpi_nfit_desc *acpi_desc,
		काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक cmd, व्योम *buf,
		अचिन्हित पूर्णांक len)
अणु
	काष्ठा nfit_test *t = container_of(acpi_desc, typeof(*t), acpi_desc);
	अचिन्हित पूर्णांक func = cmd;
	अचिन्हित पूर्णांक family = 0;

	अगर (cmd == ND_CMD_CALL) अणु
		काष्ठा nd_cmd_pkg *pkg = buf;

		len = pkg->nd_size_in;
		family = pkg->nd_family;
		buf = pkg->nd_payload;
		func = pkg->nd_command;
	पूर्ण
	dev_dbg(&t->pdev.dev, "%s family: %d cmd: %d: func: %d input length: %d\n",
			nvdimm ? nvdimm_name(nvdimm) : "bus", family, cmd, func,
			len);
	prपूर्णांक_hex_dump_debug("nvdimm in  ", DUMP_PREFIX_OFFSET, 16, 4,
			buf, min(len, 256u), true);
पूर्ण

अटल पूर्णांक nfit_test_ctl(काष्ठा nvdimm_bus_descriptor *nd_desc,
		काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक cmd, व्योम *buf,
		अचिन्हित पूर्णांक buf_len, पूर्णांक *cmd_rc)
अणु
	काष्ठा acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	काष्ठा nfit_test *t = container_of(acpi_desc, typeof(*t), acpi_desc);
	अचिन्हित पूर्णांक func = cmd;
	पूर्णांक i, rc = 0, __cmd_rc;

	अगर (!cmd_rc)
		cmd_rc = &__cmd_rc;
	*cmd_rc = 0;

	nfit_ctl_dbg(acpi_desc, nvdimm, cmd, buf, buf_len);

	अगर (nvdimm) अणु
		काष्ठा nfit_mem *nfit_mem = nvdimm_provider_data(nvdimm);
		अचिन्हित दीर्घ cmd_mask = nvdimm_cmd_mask(nvdimm);

		अगर (!nfit_mem)
			वापस -ENOTTY;

		अगर (cmd == ND_CMD_CALL) अणु
			काष्ठा nd_cmd_pkg *call_pkg = buf;

			buf_len = call_pkg->nd_size_in + call_pkg->nd_size_out;
			buf = (व्योम *) call_pkg->nd_payload;
			func = call_pkg->nd_command;
			अगर (call_pkg->nd_family != nfit_mem->family)
				वापस -ENOTTY;

			i = get_dimm(nfit_mem, func);
			अगर (i < 0)
				वापस i;
			अगर (i >= NUM_DCR) अणु
				dev_WARN_ONCE(&t->pdev.dev, 1,
						"ND_CMD_CALL only valid for nfit_test0\n");
				वापस -EINVAL;
			पूर्ण

			चयन (func) अणु
			हाल NVDIMM_INTEL_GET_SECURITY_STATE:
				rc = nd_पूर्णांकel_test_cmd_security_status(t,
						buf, buf_len, i);
				अवरोध;
			हाल NVDIMM_INTEL_UNLOCK_UNIT:
				rc = nd_पूर्णांकel_test_cmd_unlock_unit(t,
						buf, buf_len, i);
				अवरोध;
			हाल NVDIMM_INTEL_SET_PASSPHRASE:
				rc = nd_पूर्णांकel_test_cmd_set_pass(t,
						buf, buf_len, i);
				अवरोध;
			हाल NVDIMM_INTEL_DISABLE_PASSPHRASE:
				rc = nd_पूर्णांकel_test_cmd_disable_pass(t,
						buf, buf_len, i);
				अवरोध;
			हाल NVDIMM_INTEL_FREEZE_LOCK:
				rc = nd_पूर्णांकel_test_cmd_मुक्तze_lock(t,
						buf, buf_len, i);
				अवरोध;
			हाल NVDIMM_INTEL_SECURE_ERASE:
				rc = nd_पूर्णांकel_test_cmd_secure_erase(t,
						buf, buf_len, i);
				अवरोध;
			हाल NVDIMM_INTEL_OVERWRITE:
				rc = nd_पूर्णांकel_test_cmd_overग_लिखो(t,
						buf, buf_len, i);
				अवरोध;
			हाल NVDIMM_INTEL_QUERY_OVERWRITE:
				rc = nd_पूर्णांकel_test_cmd_query_overग_लिखो(t,
						buf, buf_len, i);
				अवरोध;
			हाल NVDIMM_INTEL_SET_MASTER_PASSPHRASE:
				rc = nd_पूर्णांकel_test_cmd_master_set_pass(t,
						buf, buf_len, i);
				अवरोध;
			हाल NVDIMM_INTEL_MASTER_SECURE_ERASE:
				rc = nd_पूर्णांकel_test_cmd_master_secure_erase(t,
						buf, buf_len, i);
				अवरोध;
			हाल NVDIMM_INTEL_FW_ACTIVATE_DIMMINFO:
				rc = nd_पूर्णांकel_test_cmd_fw_activate_dimminfo(
					t, buf, buf_len, i);
				अवरोध;
			हाल NVDIMM_INTEL_FW_ACTIVATE_ARM:
				rc = nd_पूर्णांकel_test_cmd_fw_activate_arm(
					t, buf, buf_len, i);
				अवरोध;
			हाल ND_INTEL_ENABLE_LSS_STATUS:
				rc = nd_पूर्णांकel_test_cmd_set_lss_status(t,
						buf, buf_len);
				अवरोध;
			हाल ND_INTEL_FW_GET_INFO:
				rc = nd_पूर्णांकel_test_get_fw_info(t, buf,
						buf_len, i);
				अवरोध;
			हाल ND_INTEL_FW_START_UPDATE:
				rc = nd_पूर्णांकel_test_start_update(t, buf,
						buf_len, i);
				अवरोध;
			हाल ND_INTEL_FW_SEND_DATA:
				rc = nd_पूर्णांकel_test_send_data(t, buf,
						buf_len, i);
				अवरोध;
			हाल ND_INTEL_FW_FINISH_UPDATE:
				rc = nd_पूर्णांकel_test_finish_fw(t, buf,
						buf_len, i);
				अवरोध;
			हाल ND_INTEL_FW_FINISH_QUERY:
				rc = nd_पूर्णांकel_test_finish_query(t, buf,
						buf_len, i);
				अवरोध;
			हाल ND_INTEL_SMART:
				rc = nfit_test_cmd_smart(buf, buf_len,
						&t->smart[i]);
				अवरोध;
			हाल ND_INTEL_SMART_THRESHOLD:
				rc = nfit_test_cmd_smart_threshold(buf,
						buf_len,
						&t->smart_threshold[i]);
				अवरोध;
			हाल ND_INTEL_SMART_SET_THRESHOLD:
				rc = nfit_test_cmd_smart_set_threshold(buf,
						buf_len,
						&t->smart_threshold[i],
						&t->smart[i],
						&t->pdev.dev, t->dimm_dev[i]);
				अवरोध;
			हाल ND_INTEL_SMART_INJECT:
				rc = nfit_test_cmd_smart_inject(buf,
						buf_len,
						&t->smart_threshold[i],
						&t->smart[i],
						&t->pdev.dev, t->dimm_dev[i]);
				अवरोध;
			शेष:
				वापस -ENOTTY;
			पूर्ण
			वापस override_वापस_code(i, func, rc);
		पूर्ण

		अगर (!test_bit(cmd, &cmd_mask)
				|| !test_bit(func, &nfit_mem->dsm_mask))
			वापस -ENOTTY;

		i = get_dimm(nfit_mem, func);
		अगर (i < 0)
			वापस i;

		चयन (func) अणु
		हाल ND_CMD_GET_CONFIG_SIZE:
			rc = nfit_test_cmd_get_config_size(buf, buf_len);
			अवरोध;
		हाल ND_CMD_GET_CONFIG_DATA:
			rc = nfit_test_cmd_get_config_data(buf, buf_len,
				t->label[i - t->dcr_idx]);
			अवरोध;
		हाल ND_CMD_SET_CONFIG_DATA:
			rc = nfit_test_cmd_set_config_data(buf, buf_len,
				t->label[i - t->dcr_idx]);
			अवरोध;
		शेष:
			वापस -ENOTTY;
		पूर्ण
		वापस override_वापस_code(i, func, rc);
	पूर्ण अन्यथा अणु
		काष्ठा ars_state *ars_state = &t->ars_state;
		काष्ठा nd_cmd_pkg *call_pkg = buf;

		अगर (!nd_desc)
			वापस -ENOTTY;

		अगर (cmd == ND_CMD_CALL && call_pkg->nd_family
				== NVDIMM_BUS_FAMILY_NFIT) अणु
			func = call_pkg->nd_command;
			buf_len = call_pkg->nd_size_in + call_pkg->nd_size_out;
			buf = (व्योम *) call_pkg->nd_payload;

			चयन (func) अणु
			हाल NFIT_CMD_TRANSLATE_SPA:
				rc = nfit_test_cmd_translate_spa(
					acpi_desc->nvdimm_bus, buf, buf_len);
				वापस rc;
			हाल NFIT_CMD_ARS_INJECT_SET:
				rc = nfit_test_cmd_ars_error_inject(t, buf,
					buf_len);
				वापस rc;
			हाल NFIT_CMD_ARS_INJECT_CLEAR:
				rc = nfit_test_cmd_ars_inject_clear(t, buf,
					buf_len);
				वापस rc;
			हाल NFIT_CMD_ARS_INJECT_GET:
				rc = nfit_test_cmd_ars_inject_status(t, buf,
					buf_len);
				वापस rc;
			शेष:
				वापस -ENOTTY;
			पूर्ण
		पूर्ण अन्यथा अगर (cmd == ND_CMD_CALL && call_pkg->nd_family
				== NVDIMM_BUS_FAMILY_INTEL) अणु
			func = call_pkg->nd_command;
			buf_len = call_pkg->nd_size_in + call_pkg->nd_size_out;
			buf = (व्योम *) call_pkg->nd_payload;

			चयन (func) अणु
			हाल NVDIMM_BUS_INTEL_FW_ACTIVATE_BUSINFO:
				rc = nvdimm_bus_पूर्णांकel_fw_activate_businfo(t,
						buf, buf_len);
				वापस rc;
			हाल NVDIMM_BUS_INTEL_FW_ACTIVATE:
				rc = nvdimm_bus_पूर्णांकel_fw_activate(t, buf,
						buf_len);
				वापस rc;
			शेष:
				वापस -ENOTTY;
			पूर्ण
		पूर्ण अन्यथा अगर (cmd == ND_CMD_CALL)
			वापस -ENOTTY;

		अगर (!nd_desc || !test_bit(cmd, &nd_desc->cmd_mask))
			वापस -ENOTTY;

		चयन (func) अणु
		हाल ND_CMD_ARS_CAP:
			rc = nfit_test_cmd_ars_cap(buf, buf_len);
			अवरोध;
		हाल ND_CMD_ARS_START:
			rc = nfit_test_cmd_ars_start(t, ars_state, buf,
					buf_len, cmd_rc);
			अवरोध;
		हाल ND_CMD_ARS_STATUS:
			rc = nfit_test_cmd_ars_status(ars_state, buf, buf_len,
					cmd_rc);
			अवरोध;
		हाल ND_CMD_CLEAR_ERROR:
			rc = nfit_test_cmd_clear_error(t, buf, buf_len, cmd_rc);
			अवरोध;
		शेष:
			वापस -ENOTTY;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल DEFINE_SPINLOCK(nfit_test_lock);
अटल काष्ठा nfit_test *instances[NUM_NFITS];

अटल व्योम release_nfit_res(व्योम *data)
अणु
	काष्ठा nfit_test_resource *nfit_res = data;

	spin_lock(&nfit_test_lock);
	list_del(&nfit_res->list);
	spin_unlock(&nfit_test_lock);

	अगर (resource_size(&nfit_res->res) >= DIMM_SIZE)
		gen_pool_मुक्त(nfit_pool, nfit_res->res.start,
				resource_size(&nfit_res->res));
	vमुक्त(nfit_res->buf);
	kमुक्त(nfit_res);
पूर्ण

अटल व्योम *__test_alloc(काष्ठा nfit_test *t, माप_प्रकार size, dma_addr_t *dma,
		व्योम *buf)
अणु
	काष्ठा device *dev = &t->pdev.dev;
	काष्ठा nfit_test_resource *nfit_res = kzalloc(माप(*nfit_res),
			GFP_KERNEL);
	पूर्णांक rc;

	अगर (!buf || !nfit_res || !*dma)
		जाओ err;
	rc = devm_add_action(dev, release_nfit_res, nfit_res);
	अगर (rc)
		जाओ err;
	INIT_LIST_HEAD(&nfit_res->list);
	स_रखो(buf, 0, size);
	nfit_res->dev = dev;
	nfit_res->buf = buf;
	nfit_res->res.start = *dma;
	nfit_res->res.end = *dma + size - 1;
	nfit_res->res.name = "NFIT";
	spin_lock_init(&nfit_res->lock);
	INIT_LIST_HEAD(&nfit_res->requests);
	spin_lock(&nfit_test_lock);
	list_add(&nfit_res->list, &t->resources);
	spin_unlock(&nfit_test_lock);

	वापस nfit_res->buf;
 err:
	अगर (*dma && size >= DIMM_SIZE)
		gen_pool_मुक्त(nfit_pool, *dma, size);
	अगर (buf)
		vमुक्त(buf);
	kमुक्त(nfit_res);
	वापस शून्य;
पूर्ण

अटल व्योम *test_alloc(काष्ठा nfit_test *t, माप_प्रकार size, dma_addr_t *dma)
अणु
	काष्ठा genpool_data_align data = अणु
		.align = SZ_128M,
	पूर्ण;
	व्योम *buf = vदो_स्मृति(size);

	अगर (size >= DIMM_SIZE)
		*dma = gen_pool_alloc_algo(nfit_pool, size,
				gen_pool_first_fit_align, &data);
	अन्यथा
		*dma = (अचिन्हित दीर्घ) buf;
	वापस __test_alloc(t, size, dma, buf);
पूर्ण

अटल काष्ठा nfit_test_resource *nfit_test_lookup(resource_माप_प्रकार addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(instances); i++) अणु
		काष्ठा nfit_test_resource *n, *nfit_res = शून्य;
		काष्ठा nfit_test *t = instances[i];

		अगर (!t)
			जारी;
		spin_lock(&nfit_test_lock);
		list_क्रम_each_entry(n, &t->resources, list) अणु
			अगर (addr >= n->res.start && (addr < n->res.start
						+ resource_size(&n->res))) अणु
				nfit_res = n;
				अवरोध;
			पूर्ण अन्यथा अगर (addr >= (अचिन्हित दीर्घ) n->buf
					&& (addr < (अचिन्हित दीर्घ) n->buf
						+ resource_size(&n->res))) अणु
				nfit_res = n;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&nfit_test_lock);
		अगर (nfit_res)
			वापस nfit_res;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक ars_state_init(काष्ठा device *dev, काष्ठा ars_state *ars_state)
अणु
	/* क्रम testing, only store up to n records that fit within 4k */
	ars_state->ars_status = devm_kzalloc(dev,
			माप(काष्ठा nd_cmd_ars_status) + SZ_4K, GFP_KERNEL);
	अगर (!ars_state->ars_status)
		वापस -ENOMEM;
	spin_lock_init(&ars_state->lock);
	वापस 0;
पूर्ण

अटल व्योम put_dimms(व्योम *data)
अणु
	काष्ठा nfit_test *t = data;
	पूर्णांक i;

	क्रम (i = 0; i < t->num_dcr; i++)
		अगर (t->dimm_dev[i])
			device_unरेजिस्टर(t->dimm_dev[i]);
पूर्ण

अटल काष्ठा class *nfit_test_dimm;

अटल पूर्णांक dimm_name_to_id(काष्ठा device *dev)
अणु
	पूर्णांक dimm;

	अगर (माला_पूछो(dev_name(dev), "test_dimm%d", &dimm) != 1)
		वापस -ENXIO;
	वापस dimm;
पूर्ण

अटल sमाप_प्रकार handle_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक dimm = dimm_name_to_id(dev);

	अगर (dimm < 0)
		वापस dimm;

	वापस प्र_लिखो(buf, "%#x\n", handle[dimm]);
पूर्ण
DEVICE_ATTR_RO(handle);

अटल sमाप_प्रकार fail_cmd_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक dimm = dimm_name_to_id(dev);

	अगर (dimm < 0)
		वापस dimm;

	वापस प्र_लिखो(buf, "%#lx\n", dimm_fail_cmd_flags[dimm]);
पूर्ण

अटल sमाप_प्रकार fail_cmd_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक dimm = dimm_name_to_id(dev);
	अचिन्हित दीर्घ val;
	sमाप_प्रकार rc;

	अगर (dimm < 0)
		वापस dimm;

	rc = kम_से_दीर्घ(buf, 0, &val);
	अगर (rc)
		वापस rc;

	dimm_fail_cmd_flags[dimm] = val;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(fail_cmd);

अटल sमाप_प्रकार fail_cmd_code_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक dimm = dimm_name_to_id(dev);

	अगर (dimm < 0)
		वापस dimm;

	वापस प्र_लिखो(buf, "%d\n", dimm_fail_cmd_code[dimm]);
पूर्ण

अटल sमाप_प्रकार fail_cmd_code_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक dimm = dimm_name_to_id(dev);
	अचिन्हित दीर्घ val;
	sमाप_प्रकार rc;

	अगर (dimm < 0)
		वापस dimm;

	rc = kम_से_दीर्घ(buf, 0, &val);
	अगर (rc)
		वापस rc;

	dimm_fail_cmd_code[dimm] = val;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(fail_cmd_code);

अटल sमाप_प्रकार lock_dimm_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक dimm = dimm_name_to_id(dev);
	काष्ठा nfit_test_sec *sec = &dimm_sec_info[dimm];

	sec->state = ND_INTEL_SEC_STATE_ENABLED | ND_INTEL_SEC_STATE_LOCKED;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_WO(lock_dimm);

अटल काष्ठा attribute *nfit_test_dimm_attributes[] = अणु
	&dev_attr_fail_cmd.attr,
	&dev_attr_fail_cmd_code.attr,
	&dev_attr_handle.attr,
	&dev_attr_lock_dimm.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group nfit_test_dimm_attribute_group = अणु
	.attrs = nfit_test_dimm_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *nfit_test_dimm_attribute_groups[] = अणु
	&nfit_test_dimm_attribute_group,
	शून्य,
पूर्ण;

अटल पूर्णांक nfit_test_dimm_init(काष्ठा nfit_test *t)
अणु
	पूर्णांक i;

	अगर (devm_add_action_or_reset(&t->pdev.dev, put_dimms, t))
		वापस -ENOMEM;
	क्रम (i = 0; i < t->num_dcr; i++) अणु
		t->dimm_dev[i] = device_create_with_groups(nfit_test_dimm,
				&t->pdev.dev, 0, शून्य,
				nfit_test_dimm_attribute_groups,
				"test_dimm%d", i + t->dcr_idx);
		अगर (!t->dimm_dev[i])
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम security_init(काष्ठा nfit_test *t)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < t->num_dcr; i++) अणु
		काष्ठा nfit_test_sec *sec = &dimm_sec_info[i];

		sec->ext_state = ND_INTEL_SEC_ESTATE_ENABLED;
	पूर्ण
पूर्ण

अटल व्योम smart_init(काष्ठा nfit_test *t)
अणु
	पूर्णांक i;
	स्थिर काष्ठा nd_पूर्णांकel_smart_threshold smart_t_data = अणु
		.alarm_control = ND_INTEL_SMART_SPARE_TRIP
			| ND_INTEL_SMART_TEMP_TRIP,
		.media_temperature = 40 * 16,
		.ctrl_temperature = 30 * 16,
		.spares = 5,
	पूर्ण;

	क्रम (i = 0; i < t->num_dcr; i++) अणु
		स_नकल(&t->smart[i], &smart_def, माप(smart_def));
		स_नकल(&t->smart_threshold[i], &smart_t_data,
				माप(smart_t_data));
	पूर्ण
पूर्ण

अटल माप_प्रकार माप_spa(काष्ठा acpi_nfit_प्रणाली_address *spa)
अणु
	/* until spa location cookie support is added... */
	वापस माप(*spa) - 8;
पूर्ण

अटल पूर्णांक nfit_test0_alloc(काष्ठा nfit_test *t)
अणु
	काष्ठा acpi_nfit_प्रणाली_address *spa = शून्य;
	माप_प्रकार nfit_size = माप_spa(spa) * NUM_SPA
			+ माप(काष्ठा acpi_nfit_memory_map) * NUM_MEM
			+ माप(काष्ठा acpi_nfit_control_region) * NUM_DCR
			+ दुरत्व(काष्ठा acpi_nfit_control_region,
					winकरोw_size) * NUM_DCR
			+ माप(काष्ठा acpi_nfit_data_region) * NUM_BDW
			+ (माप(काष्ठा acpi_nfit_flush_address)
					+ माप(u64) * NUM_HINTS) * NUM_DCR
			+ माप(काष्ठा acpi_nfit_capabilities);
	पूर्णांक i;

	t->nfit_buf = test_alloc(t, nfit_size, &t->nfit_dma);
	अगर (!t->nfit_buf)
		वापस -ENOMEM;
	t->nfit_size = nfit_size;

	t->spa_set[0] = test_alloc(t, SPA0_SIZE, &t->spa_set_dma[0]);
	अगर (!t->spa_set[0])
		वापस -ENOMEM;

	t->spa_set[1] = test_alloc(t, SPA1_SIZE, &t->spa_set_dma[1]);
	अगर (!t->spa_set[1])
		वापस -ENOMEM;

	t->spa_set[2] = test_alloc(t, SPA0_SIZE, &t->spa_set_dma[2]);
	अगर (!t->spa_set[2])
		वापस -ENOMEM;

	क्रम (i = 0; i < t->num_dcr; i++) अणु
		t->dimm[i] = test_alloc(t, DIMM_SIZE, &t->dimm_dma[i]);
		अगर (!t->dimm[i])
			वापस -ENOMEM;

		t->label[i] = test_alloc(t, LABEL_SIZE, &t->label_dma[i]);
		अगर (!t->label[i])
			वापस -ENOMEM;
		प्र_लिखो(t->label[i], "label%d", i);

		t->flush[i] = test_alloc(t, max(PAGE_SIZE,
					माप(u64) * NUM_HINTS),
				&t->flush_dma[i]);
		अगर (!t->flush[i])
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < t->num_dcr; i++) अणु
		t->dcr[i] = test_alloc(t, LABEL_SIZE, &t->dcr_dma[i]);
		अगर (!t->dcr[i])
			वापस -ENOMEM;
	पूर्ण

	t->_fit = test_alloc(t, माप(जोड़ acpi_object **), &t->_fit_dma);
	अगर (!t->_fit)
		वापस -ENOMEM;

	अगर (nfit_test_dimm_init(t))
		वापस -ENOMEM;
	smart_init(t);
	security_init(t);
	वापस ars_state_init(&t->pdev.dev, &t->ars_state);
पूर्ण

अटल पूर्णांक nfit_test1_alloc(काष्ठा nfit_test *t)
अणु
	काष्ठा acpi_nfit_प्रणाली_address *spa = शून्य;
	माप_प्रकार nfit_size = माप_spa(spa) * 2
		+ माप(काष्ठा acpi_nfit_memory_map) * 2
		+ दुरत्व(काष्ठा acpi_nfit_control_region, winकरोw_size) * 2;
	पूर्णांक i;

	t->nfit_buf = test_alloc(t, nfit_size, &t->nfit_dma);
	अगर (!t->nfit_buf)
		वापस -ENOMEM;
	t->nfit_size = nfit_size;

	t->spa_set[0] = test_alloc(t, SPA2_SIZE, &t->spa_set_dma[0]);
	अगर (!t->spa_set[0])
		वापस -ENOMEM;

	क्रम (i = 0; i < t->num_dcr; i++) अणु
		t->label[i] = test_alloc(t, LABEL_SIZE, &t->label_dma[i]);
		अगर (!t->label[i])
			वापस -ENOMEM;
		प्र_लिखो(t->label[i], "label%d", i);
	पूर्ण

	t->spa_set[1] = test_alloc(t, SPA_VCD_SIZE, &t->spa_set_dma[1]);
	अगर (!t->spa_set[1])
		वापस -ENOMEM;

	अगर (nfit_test_dimm_init(t))
		वापस -ENOMEM;
	smart_init(t);
	वापस ars_state_init(&t->pdev.dev, &t->ars_state);
पूर्ण

अटल व्योम dcr_common_init(काष्ठा acpi_nfit_control_region *dcr)
अणु
	dcr->venकरोr_id = 0xabcd;
	dcr->device_id = 0;
	dcr->revision_id = 1;
	dcr->valid_fields = 1;
	dcr->manufacturing_location = 0xa;
	dcr->manufacturing_date = cpu_to_be16(2016);
पूर्ण

अटल व्योम nfit_test0_setup(काष्ठा nfit_test *t)
अणु
	स्थिर पूर्णांक flush_hपूर्णांक_size = माप(काष्ठा acpi_nfit_flush_address)
		+ (माप(u64) * NUM_HINTS);
	काष्ठा acpi_nfit_desc *acpi_desc;
	काष्ठा acpi_nfit_memory_map *memdev;
	व्योम *nfit_buf = t->nfit_buf;
	काष्ठा acpi_nfit_प्रणाली_address *spa;
	काष्ठा acpi_nfit_control_region *dcr;
	काष्ठा acpi_nfit_data_region *bdw;
	काष्ठा acpi_nfit_flush_address *flush;
	काष्ठा acpi_nfit_capabilities *pcap;
	अचिन्हित पूर्णांक offset = 0, i;
	अचिन्हित दीर्घ *acpi_mask;

	/*
	 * spa0 (पूर्णांकerleave first half of dimm0 and dimm1, note storage
	 * करोes not actually alias the related block-data-winकरोw
	 * regions)
	 */
	spa = nfit_buf;
	spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
	spa->header.length = माप_spa(spa);
	स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_PM), 16);
	spa->range_index = 0+1;
	spa->address = t->spa_set_dma[0];
	spa->length = SPA0_SIZE;
	offset += spa->header.length;

	/*
	 * spa1 (पूर्णांकerleave last half of the 4 DIMMS, note storage
	 * करोes not actually alias the related block-data-winकरोw
	 * regions)
	 */
	spa = nfit_buf + offset;
	spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
	spa->header.length = माप_spa(spa);
	स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_PM), 16);
	spa->range_index = 1+1;
	spa->address = t->spa_set_dma[1];
	spa->length = SPA1_SIZE;
	offset += spa->header.length;

	/* spa2 (dcr0) dimm0 */
	spa = nfit_buf + offset;
	spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
	spa->header.length = माप_spa(spa);
	स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_DCR), 16);
	spa->range_index = 2+1;
	spa->address = t->dcr_dma[0];
	spa->length = DCR_SIZE;
	offset += spa->header.length;

	/* spa3 (dcr1) dimm1 */
	spa = nfit_buf + offset;
	spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
	spa->header.length = माप_spa(spa);
	स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_DCR), 16);
	spa->range_index = 3+1;
	spa->address = t->dcr_dma[1];
	spa->length = DCR_SIZE;
	offset += spa->header.length;

	/* spa4 (dcr2) dimm2 */
	spa = nfit_buf + offset;
	spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
	spa->header.length = माप_spa(spa);
	स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_DCR), 16);
	spa->range_index = 4+1;
	spa->address = t->dcr_dma[2];
	spa->length = DCR_SIZE;
	offset += spa->header.length;

	/* spa5 (dcr3) dimm3 */
	spa = nfit_buf + offset;
	spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
	spa->header.length = माप_spa(spa);
	स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_DCR), 16);
	spa->range_index = 5+1;
	spa->address = t->dcr_dma[3];
	spa->length = DCR_SIZE;
	offset += spa->header.length;

	/* spa6 (bdw क्रम dcr0) dimm0 */
	spa = nfit_buf + offset;
	spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
	spa->header.length = माप_spa(spa);
	स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_BDW), 16);
	spa->range_index = 6+1;
	spa->address = t->dimm_dma[0];
	spa->length = DIMM_SIZE;
	offset += spa->header.length;

	/* spa7 (bdw क्रम dcr1) dimm1 */
	spa = nfit_buf + offset;
	spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
	spa->header.length = माप_spa(spa);
	स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_BDW), 16);
	spa->range_index = 7+1;
	spa->address = t->dimm_dma[1];
	spa->length = DIMM_SIZE;
	offset += spa->header.length;

	/* spa8 (bdw क्रम dcr2) dimm2 */
	spa = nfit_buf + offset;
	spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
	spa->header.length = माप_spa(spa);
	स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_BDW), 16);
	spa->range_index = 8+1;
	spa->address = t->dimm_dma[2];
	spa->length = DIMM_SIZE;
	offset += spa->header.length;

	/* spa9 (bdw क्रम dcr3) dimm3 */
	spa = nfit_buf + offset;
	spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
	spa->header.length = माप_spa(spa);
	स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_BDW), 16);
	spa->range_index = 9+1;
	spa->address = t->dimm_dma[3];
	spa->length = DIMM_SIZE;
	offset += spa->header.length;

	/* mem-region0 (spa0, dimm0) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[0];
	memdev->physical_id = 0;
	memdev->region_id = 0;
	memdev->range_index = 0+1;
	memdev->region_index = 4+1;
	memdev->region_size = SPA0_SIZE/2;
	memdev->region_offset = 1;
	memdev->address = 0;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 2;
	offset += memdev->header.length;

	/* mem-region1 (spa0, dimm1) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[1];
	memdev->physical_id = 1;
	memdev->region_id = 0;
	memdev->range_index = 0+1;
	memdev->region_index = 5+1;
	memdev->region_size = SPA0_SIZE/2;
	memdev->region_offset = (1 << 8);
	memdev->address = 0;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 2;
	memdev->flags = ACPI_NFIT_MEM_HEALTH_ENABLED;
	offset += memdev->header.length;

	/* mem-region2 (spa1, dimm0) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[0];
	memdev->physical_id = 0;
	memdev->region_id = 1;
	memdev->range_index = 1+1;
	memdev->region_index = 4+1;
	memdev->region_size = SPA1_SIZE/4;
	memdev->region_offset = (1 << 16);
	memdev->address = SPA0_SIZE/2;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 4;
	memdev->flags = ACPI_NFIT_MEM_HEALTH_ENABLED;
	offset += memdev->header.length;

	/* mem-region3 (spa1, dimm1) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[1];
	memdev->physical_id = 1;
	memdev->region_id = 1;
	memdev->range_index = 1+1;
	memdev->region_index = 5+1;
	memdev->region_size = SPA1_SIZE/4;
	memdev->region_offset = (1 << 24);
	memdev->address = SPA0_SIZE/2;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 4;
	offset += memdev->header.length;

	/* mem-region4 (spa1, dimm2) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[2];
	memdev->physical_id = 2;
	memdev->region_id = 0;
	memdev->range_index = 1+1;
	memdev->region_index = 6+1;
	memdev->region_size = SPA1_SIZE/4;
	memdev->region_offset = (1ULL << 32);
	memdev->address = SPA0_SIZE/2;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 4;
	memdev->flags = ACPI_NFIT_MEM_HEALTH_ENABLED;
	offset += memdev->header.length;

	/* mem-region5 (spa1, dimm3) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[3];
	memdev->physical_id = 3;
	memdev->region_id = 0;
	memdev->range_index = 1+1;
	memdev->region_index = 7+1;
	memdev->region_size = SPA1_SIZE/4;
	memdev->region_offset = (1ULL << 40);
	memdev->address = SPA0_SIZE/2;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 4;
	offset += memdev->header.length;

	/* mem-region6 (spa/dcr0, dimm0) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[0];
	memdev->physical_id = 0;
	memdev->region_id = 0;
	memdev->range_index = 2+1;
	memdev->region_index = 0+1;
	memdev->region_size = 0;
	memdev->region_offset = 0;
	memdev->address = 0;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 1;
	offset += memdev->header.length;

	/* mem-region7 (spa/dcr1, dimm1) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[1];
	memdev->physical_id = 1;
	memdev->region_id = 0;
	memdev->range_index = 3+1;
	memdev->region_index = 1+1;
	memdev->region_size = 0;
	memdev->region_offset = 0;
	memdev->address = 0;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 1;
	offset += memdev->header.length;

	/* mem-region8 (spa/dcr2, dimm2) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[2];
	memdev->physical_id = 2;
	memdev->region_id = 0;
	memdev->range_index = 4+1;
	memdev->region_index = 2+1;
	memdev->region_size = 0;
	memdev->region_offset = 0;
	memdev->address = 0;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 1;
	offset += memdev->header.length;

	/* mem-region9 (spa/dcr3, dimm3) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[3];
	memdev->physical_id = 3;
	memdev->region_id = 0;
	memdev->range_index = 5+1;
	memdev->region_index = 3+1;
	memdev->region_size = 0;
	memdev->region_offset = 0;
	memdev->address = 0;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 1;
	offset += memdev->header.length;

	/* mem-region10 (spa/bdw0, dimm0) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[0];
	memdev->physical_id = 0;
	memdev->region_id = 0;
	memdev->range_index = 6+1;
	memdev->region_index = 0+1;
	memdev->region_size = 0;
	memdev->region_offset = 0;
	memdev->address = 0;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 1;
	offset += memdev->header.length;

	/* mem-region11 (spa/bdw1, dimm1) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[1];
	memdev->physical_id = 1;
	memdev->region_id = 0;
	memdev->range_index = 7+1;
	memdev->region_index = 1+1;
	memdev->region_size = 0;
	memdev->region_offset = 0;
	memdev->address = 0;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 1;
	offset += memdev->header.length;

	/* mem-region12 (spa/bdw2, dimm2) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[2];
	memdev->physical_id = 2;
	memdev->region_id = 0;
	memdev->range_index = 8+1;
	memdev->region_index = 2+1;
	memdev->region_size = 0;
	memdev->region_offset = 0;
	memdev->address = 0;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 1;
	offset += memdev->header.length;

	/* mem-region13 (spa/dcr3, dimm3) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[3];
	memdev->physical_id = 3;
	memdev->region_id = 0;
	memdev->range_index = 9+1;
	memdev->region_index = 3+1;
	memdev->region_size = 0;
	memdev->region_offset = 0;
	memdev->address = 0;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 1;
	memdev->flags = ACPI_NFIT_MEM_HEALTH_ENABLED;
	offset += memdev->header.length;

	/* dcr-descriptor0: blk */
	dcr = nfit_buf + offset;
	dcr->header.type = ACPI_NFIT_TYPE_CONTROL_REGION;
	dcr->header.length = माप(*dcr);
	dcr->region_index = 0+1;
	dcr_common_init(dcr);
	dcr->serial_number = ~handle[0];
	dcr->code = NFIT_FIC_BLK;
	dcr->winकरोws = 1;
	dcr->winकरोw_size = DCR_SIZE;
	dcr->command_offset = 0;
	dcr->command_size = 8;
	dcr->status_offset = 8;
	dcr->status_size = 4;
	offset += dcr->header.length;

	/* dcr-descriptor1: blk */
	dcr = nfit_buf + offset;
	dcr->header.type = ACPI_NFIT_TYPE_CONTROL_REGION;
	dcr->header.length = माप(*dcr);
	dcr->region_index = 1+1;
	dcr_common_init(dcr);
	dcr->serial_number = ~handle[1];
	dcr->code = NFIT_FIC_BLK;
	dcr->winकरोws = 1;
	dcr->winकरोw_size = DCR_SIZE;
	dcr->command_offset = 0;
	dcr->command_size = 8;
	dcr->status_offset = 8;
	dcr->status_size = 4;
	offset += dcr->header.length;

	/* dcr-descriptor2: blk */
	dcr = nfit_buf + offset;
	dcr->header.type = ACPI_NFIT_TYPE_CONTROL_REGION;
	dcr->header.length = माप(*dcr);
	dcr->region_index = 2+1;
	dcr_common_init(dcr);
	dcr->serial_number = ~handle[2];
	dcr->code = NFIT_FIC_BLK;
	dcr->winकरोws = 1;
	dcr->winकरोw_size = DCR_SIZE;
	dcr->command_offset = 0;
	dcr->command_size = 8;
	dcr->status_offset = 8;
	dcr->status_size = 4;
	offset += dcr->header.length;

	/* dcr-descriptor3: blk */
	dcr = nfit_buf + offset;
	dcr->header.type = ACPI_NFIT_TYPE_CONTROL_REGION;
	dcr->header.length = माप(*dcr);
	dcr->region_index = 3+1;
	dcr_common_init(dcr);
	dcr->serial_number = ~handle[3];
	dcr->code = NFIT_FIC_BLK;
	dcr->winकरोws = 1;
	dcr->winकरोw_size = DCR_SIZE;
	dcr->command_offset = 0;
	dcr->command_size = 8;
	dcr->status_offset = 8;
	dcr->status_size = 4;
	offset += dcr->header.length;

	/* dcr-descriptor0: pmem */
	dcr = nfit_buf + offset;
	dcr->header.type = ACPI_NFIT_TYPE_CONTROL_REGION;
	dcr->header.length = दुरत्व(काष्ठा acpi_nfit_control_region,
			winकरोw_size);
	dcr->region_index = 4+1;
	dcr_common_init(dcr);
	dcr->serial_number = ~handle[0];
	dcr->code = NFIT_FIC_BYTEN;
	dcr->winकरोws = 0;
	offset += dcr->header.length;

	/* dcr-descriptor1: pmem */
	dcr = nfit_buf + offset;
	dcr->header.type = ACPI_NFIT_TYPE_CONTROL_REGION;
	dcr->header.length = दुरत्व(काष्ठा acpi_nfit_control_region,
			winकरोw_size);
	dcr->region_index = 5+1;
	dcr_common_init(dcr);
	dcr->serial_number = ~handle[1];
	dcr->code = NFIT_FIC_BYTEN;
	dcr->winकरोws = 0;
	offset += dcr->header.length;

	/* dcr-descriptor2: pmem */
	dcr = nfit_buf + offset;
	dcr->header.type = ACPI_NFIT_TYPE_CONTROL_REGION;
	dcr->header.length = दुरत्व(काष्ठा acpi_nfit_control_region,
			winकरोw_size);
	dcr->region_index = 6+1;
	dcr_common_init(dcr);
	dcr->serial_number = ~handle[2];
	dcr->code = NFIT_FIC_BYTEN;
	dcr->winकरोws = 0;
	offset += dcr->header.length;

	/* dcr-descriptor3: pmem */
	dcr = nfit_buf + offset;
	dcr->header.type = ACPI_NFIT_TYPE_CONTROL_REGION;
	dcr->header.length = दुरत्व(काष्ठा acpi_nfit_control_region,
			winकरोw_size);
	dcr->region_index = 7+1;
	dcr_common_init(dcr);
	dcr->serial_number = ~handle[3];
	dcr->code = NFIT_FIC_BYTEN;
	dcr->winकरोws = 0;
	offset += dcr->header.length;

	/* bdw0 (spa/dcr0, dimm0) */
	bdw = nfit_buf + offset;
	bdw->header.type = ACPI_NFIT_TYPE_DATA_REGION;
	bdw->header.length = माप(*bdw);
	bdw->region_index = 0+1;
	bdw->winकरोws = 1;
	bdw->offset = 0;
	bdw->size = BDW_SIZE;
	bdw->capacity = DIMM_SIZE;
	bdw->start_address = 0;
	offset += bdw->header.length;

	/* bdw1 (spa/dcr1, dimm1) */
	bdw = nfit_buf + offset;
	bdw->header.type = ACPI_NFIT_TYPE_DATA_REGION;
	bdw->header.length = माप(*bdw);
	bdw->region_index = 1+1;
	bdw->winकरोws = 1;
	bdw->offset = 0;
	bdw->size = BDW_SIZE;
	bdw->capacity = DIMM_SIZE;
	bdw->start_address = 0;
	offset += bdw->header.length;

	/* bdw2 (spa/dcr2, dimm2) */
	bdw = nfit_buf + offset;
	bdw->header.type = ACPI_NFIT_TYPE_DATA_REGION;
	bdw->header.length = माप(*bdw);
	bdw->region_index = 2+1;
	bdw->winकरोws = 1;
	bdw->offset = 0;
	bdw->size = BDW_SIZE;
	bdw->capacity = DIMM_SIZE;
	bdw->start_address = 0;
	offset += bdw->header.length;

	/* bdw3 (spa/dcr3, dimm3) */
	bdw = nfit_buf + offset;
	bdw->header.type = ACPI_NFIT_TYPE_DATA_REGION;
	bdw->header.length = माप(*bdw);
	bdw->region_index = 3+1;
	bdw->winकरोws = 1;
	bdw->offset = 0;
	bdw->size = BDW_SIZE;
	bdw->capacity = DIMM_SIZE;
	bdw->start_address = 0;
	offset += bdw->header.length;

	/* flush0 (dimm0) */
	flush = nfit_buf + offset;
	flush->header.type = ACPI_NFIT_TYPE_FLUSH_ADDRESS;
	flush->header.length = flush_hपूर्णांक_size;
	flush->device_handle = handle[0];
	flush->hपूर्णांक_count = NUM_HINTS;
	क्रम (i = 0; i < NUM_HINTS; i++)
		flush->hपूर्णांक_address[i] = t->flush_dma[0] + i * माप(u64);
	offset += flush->header.length;

	/* flush1 (dimm1) */
	flush = nfit_buf + offset;
	flush->header.type = ACPI_NFIT_TYPE_FLUSH_ADDRESS;
	flush->header.length = flush_hपूर्णांक_size;
	flush->device_handle = handle[1];
	flush->hपूर्णांक_count = NUM_HINTS;
	क्रम (i = 0; i < NUM_HINTS; i++)
		flush->hपूर्णांक_address[i] = t->flush_dma[1] + i * माप(u64);
	offset += flush->header.length;

	/* flush2 (dimm2) */
	flush = nfit_buf + offset;
	flush->header.type = ACPI_NFIT_TYPE_FLUSH_ADDRESS;
	flush->header.length = flush_hपूर्णांक_size;
	flush->device_handle = handle[2];
	flush->hपूर्णांक_count = NUM_HINTS;
	क्रम (i = 0; i < NUM_HINTS; i++)
		flush->hपूर्णांक_address[i] = t->flush_dma[2] + i * माप(u64);
	offset += flush->header.length;

	/* flush3 (dimm3) */
	flush = nfit_buf + offset;
	flush->header.type = ACPI_NFIT_TYPE_FLUSH_ADDRESS;
	flush->header.length = flush_hपूर्णांक_size;
	flush->device_handle = handle[3];
	flush->hपूर्णांक_count = NUM_HINTS;
	क्रम (i = 0; i < NUM_HINTS; i++)
		flush->hपूर्णांक_address[i] = t->flush_dma[3] + i * माप(u64);
	offset += flush->header.length;

	/* platक्रमm capabilities */
	pcap = nfit_buf + offset;
	pcap->header.type = ACPI_NFIT_TYPE_CAPABILITIES;
	pcap->header.length = माप(*pcap);
	pcap->highest_capability = 1;
	pcap->capabilities = ACPI_NFIT_CAPABILITY_MEM_FLUSH;
	offset += pcap->header.length;

	अगर (t->setup_hotplug) अणु
		/* dcr-descriptor4: blk */
		dcr = nfit_buf + offset;
		dcr->header.type = ACPI_NFIT_TYPE_CONTROL_REGION;
		dcr->header.length = माप(*dcr);
		dcr->region_index = 8+1;
		dcr_common_init(dcr);
		dcr->serial_number = ~handle[4];
		dcr->code = NFIT_FIC_BLK;
		dcr->winकरोws = 1;
		dcr->winकरोw_size = DCR_SIZE;
		dcr->command_offset = 0;
		dcr->command_size = 8;
		dcr->status_offset = 8;
		dcr->status_size = 4;
		offset += dcr->header.length;

		/* dcr-descriptor4: pmem */
		dcr = nfit_buf + offset;
		dcr->header.type = ACPI_NFIT_TYPE_CONTROL_REGION;
		dcr->header.length = दुरत्व(काष्ठा acpi_nfit_control_region,
				winकरोw_size);
		dcr->region_index = 9+1;
		dcr_common_init(dcr);
		dcr->serial_number = ~handle[4];
		dcr->code = NFIT_FIC_BYTEN;
		dcr->winकरोws = 0;
		offset += dcr->header.length;

		/* bdw4 (spa/dcr4, dimm4) */
		bdw = nfit_buf + offset;
		bdw->header.type = ACPI_NFIT_TYPE_DATA_REGION;
		bdw->header.length = माप(*bdw);
		bdw->region_index = 8+1;
		bdw->winकरोws = 1;
		bdw->offset = 0;
		bdw->size = BDW_SIZE;
		bdw->capacity = DIMM_SIZE;
		bdw->start_address = 0;
		offset += bdw->header.length;

		/* spa10 (dcr4) dimm4 */
		spa = nfit_buf + offset;
		spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
		spa->header.length = माप_spa(spa);
		स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_DCR), 16);
		spa->range_index = 10+1;
		spa->address = t->dcr_dma[4];
		spa->length = DCR_SIZE;
		offset += spa->header.length;

		/*
		 * spa11 (single-dimm पूर्णांकerleave क्रम hotplug, note storage
		 * करोes not actually alias the related block-data-winकरोw
		 * regions)
		 */
		spa = nfit_buf + offset;
		spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
		spa->header.length = माप_spa(spa);
		स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_PM), 16);
		spa->range_index = 11+1;
		spa->address = t->spa_set_dma[2];
		spa->length = SPA0_SIZE;
		offset += spa->header.length;

		/* spa12 (bdw क्रम dcr4) dimm4 */
		spa = nfit_buf + offset;
		spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
		spa->header.length = माप_spa(spa);
		स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_BDW), 16);
		spa->range_index = 12+1;
		spa->address = t->dimm_dma[4];
		spa->length = DIMM_SIZE;
		offset += spa->header.length;

		/* mem-region14 (spa/dcr4, dimm4) */
		memdev = nfit_buf + offset;
		memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
		memdev->header.length = माप(*memdev);
		memdev->device_handle = handle[4];
		memdev->physical_id = 4;
		memdev->region_id = 0;
		memdev->range_index = 10+1;
		memdev->region_index = 8+1;
		memdev->region_size = 0;
		memdev->region_offset = 0;
		memdev->address = 0;
		memdev->पूर्णांकerleave_index = 0;
		memdev->पूर्णांकerleave_ways = 1;
		offset += memdev->header.length;

		/* mem-region15 (spa11, dimm4) */
		memdev = nfit_buf + offset;
		memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
		memdev->header.length = माप(*memdev);
		memdev->device_handle = handle[4];
		memdev->physical_id = 4;
		memdev->region_id = 0;
		memdev->range_index = 11+1;
		memdev->region_index = 9+1;
		memdev->region_size = SPA0_SIZE;
		memdev->region_offset = (1ULL << 48);
		memdev->address = 0;
		memdev->पूर्णांकerleave_index = 0;
		memdev->पूर्णांकerleave_ways = 1;
		memdev->flags = ACPI_NFIT_MEM_HEALTH_ENABLED;
		offset += memdev->header.length;

		/* mem-region16 (spa/bdw4, dimm4) */
		memdev = nfit_buf + offset;
		memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
		memdev->header.length = माप(*memdev);
		memdev->device_handle = handle[4];
		memdev->physical_id = 4;
		memdev->region_id = 0;
		memdev->range_index = 12+1;
		memdev->region_index = 8+1;
		memdev->region_size = 0;
		memdev->region_offset = 0;
		memdev->address = 0;
		memdev->पूर्णांकerleave_index = 0;
		memdev->पूर्णांकerleave_ways = 1;
		offset += memdev->header.length;

		/* flush3 (dimm4) */
		flush = nfit_buf + offset;
		flush->header.type = ACPI_NFIT_TYPE_FLUSH_ADDRESS;
		flush->header.length = flush_hपूर्णांक_size;
		flush->device_handle = handle[4];
		flush->hपूर्णांक_count = NUM_HINTS;
		क्रम (i = 0; i < NUM_HINTS; i++)
			flush->hपूर्णांक_address[i] = t->flush_dma[4]
				+ i * माप(u64);
		offset += flush->header.length;

		/* sanity check to make sure we've filled the buffer */
		WARN_ON(offset != t->nfit_size);
	पूर्ण

	t->nfit_filled = offset;

	post_ars_status(&t->ars_state, &t->badrange, t->spa_set_dma[0],
			SPA0_SIZE);

	acpi_desc = &t->acpi_desc;
	set_bit(ND_CMD_GET_CONFIG_SIZE, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_CMD_GET_CONFIG_DATA, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_CMD_SET_CONFIG_DATA, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_INTEL_SMART, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_INTEL_SMART_THRESHOLD, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_INTEL_SMART_SET_THRESHOLD, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_INTEL_SMART_INJECT, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_CMD_ARS_CAP, &acpi_desc->bus_cmd_क्रमce_en);
	set_bit(ND_CMD_ARS_START, &acpi_desc->bus_cmd_क्रमce_en);
	set_bit(ND_CMD_ARS_STATUS, &acpi_desc->bus_cmd_क्रमce_en);
	set_bit(ND_CMD_CLEAR_ERROR, &acpi_desc->bus_cmd_क्रमce_en);
	set_bit(ND_CMD_CALL, &acpi_desc->bus_cmd_क्रमce_en);
	set_bit(NFIT_CMD_TRANSLATE_SPA, &acpi_desc->bus_dsm_mask);
	set_bit(NFIT_CMD_ARS_INJECT_SET, &acpi_desc->bus_dsm_mask);
	set_bit(NFIT_CMD_ARS_INJECT_CLEAR, &acpi_desc->bus_dsm_mask);
	set_bit(NFIT_CMD_ARS_INJECT_GET, &acpi_desc->bus_dsm_mask);
	set_bit(ND_INTEL_FW_GET_INFO, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_INTEL_FW_START_UPDATE, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_INTEL_FW_SEND_DATA, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_INTEL_FW_FINISH_UPDATE, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_INTEL_FW_FINISH_QUERY, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_INTEL_ENABLE_LSS_STATUS, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(NVDIMM_INTEL_GET_SECURITY_STATE,
			&acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(NVDIMM_INTEL_SET_PASSPHRASE, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(NVDIMM_INTEL_DISABLE_PASSPHRASE,
			&acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(NVDIMM_INTEL_UNLOCK_UNIT, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(NVDIMM_INTEL_FREEZE_LOCK, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(NVDIMM_INTEL_SECURE_ERASE, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(NVDIMM_INTEL_OVERWRITE, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(NVDIMM_INTEL_QUERY_OVERWRITE, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(NVDIMM_INTEL_SET_MASTER_PASSPHRASE,
			&acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(NVDIMM_INTEL_MASTER_SECURE_ERASE,
			&acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(NVDIMM_INTEL_FW_ACTIVATE_DIMMINFO, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(NVDIMM_INTEL_FW_ACTIVATE_ARM, &acpi_desc->dimm_cmd_क्रमce_en);

	acpi_mask = &acpi_desc->family_dsm_mask[NVDIMM_BUS_FAMILY_INTEL];
	set_bit(NVDIMM_BUS_INTEL_FW_ACTIVATE_BUSINFO, acpi_mask);
	set_bit(NVDIMM_BUS_INTEL_FW_ACTIVATE, acpi_mask);
पूर्ण

अटल व्योम nfit_test1_setup(काष्ठा nfit_test *t)
अणु
	माप_प्रकार offset;
	व्योम *nfit_buf = t->nfit_buf;
	काष्ठा acpi_nfit_memory_map *memdev;
	काष्ठा acpi_nfit_control_region *dcr;
	काष्ठा acpi_nfit_प्रणाली_address *spa;
	काष्ठा acpi_nfit_desc *acpi_desc;

	offset = 0;
	/* spa0 (flat range with no bdw aliasing) */
	spa = nfit_buf + offset;
	spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
	spa->header.length = माप_spa(spa);
	स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_PM), 16);
	spa->range_index = 0+1;
	spa->address = t->spa_set_dma[0];
	spa->length = SPA2_SIZE;
	offset += spa->header.length;

	/* भव cd region */
	spa = nfit_buf + offset;
	spa->header.type = ACPI_NFIT_TYPE_SYSTEM_ADDRESS;
	spa->header.length = माप_spa(spa);
	स_नकल(spa->range_guid, to_nfit_uuid(NFIT_SPA_VCD), 16);
	spa->range_index = 0;
	spa->address = t->spa_set_dma[1];
	spa->length = SPA_VCD_SIZE;
	offset += spa->header.length;

	/* mem-region0 (spa0, dimm0) */
	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[5];
	memdev->physical_id = 0;
	memdev->region_id = 0;
	memdev->range_index = 0+1;
	memdev->region_index = 0+1;
	memdev->region_size = SPA2_SIZE;
	memdev->region_offset = 0;
	memdev->address = 0;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 1;
	memdev->flags = ACPI_NFIT_MEM_SAVE_FAILED | ACPI_NFIT_MEM_RESTORE_FAILED
		| ACPI_NFIT_MEM_FLUSH_FAILED | ACPI_NFIT_MEM_HEALTH_OBSERVED
		| ACPI_NFIT_MEM_NOT_ARMED;
	offset += memdev->header.length;

	/* dcr-descriptor0 */
	dcr = nfit_buf + offset;
	dcr->header.type = ACPI_NFIT_TYPE_CONTROL_REGION;
	dcr->header.length = दुरत्व(काष्ठा acpi_nfit_control_region,
			winकरोw_size);
	dcr->region_index = 0+1;
	dcr_common_init(dcr);
	dcr->serial_number = ~handle[5];
	dcr->code = NFIT_FIC_BYTE;
	dcr->winकरोws = 0;
	offset += dcr->header.length;

	memdev = nfit_buf + offset;
	memdev->header.type = ACPI_NFIT_TYPE_MEMORY_MAP;
	memdev->header.length = माप(*memdev);
	memdev->device_handle = handle[6];
	memdev->physical_id = 0;
	memdev->region_id = 0;
	memdev->range_index = 0;
	memdev->region_index = 0+2;
	memdev->region_size = SPA2_SIZE;
	memdev->region_offset = 0;
	memdev->address = 0;
	memdev->पूर्णांकerleave_index = 0;
	memdev->पूर्णांकerleave_ways = 1;
	memdev->flags = ACPI_NFIT_MEM_MAP_FAILED;
	offset += memdev->header.length;

	/* dcr-descriptor1 */
	dcr = nfit_buf + offset;
	dcr->header.type = ACPI_NFIT_TYPE_CONTROL_REGION;
	dcr->header.length = दुरत्व(काष्ठा acpi_nfit_control_region,
			winकरोw_size);
	dcr->region_index = 0+2;
	dcr_common_init(dcr);
	dcr->serial_number = ~handle[6];
	dcr->code = NFIT_FIC_BYTE;
	dcr->winकरोws = 0;
	offset += dcr->header.length;

	/* sanity check to make sure we've filled the buffer */
	WARN_ON(offset != t->nfit_size);

	t->nfit_filled = offset;

	post_ars_status(&t->ars_state, &t->badrange, t->spa_set_dma[0],
			SPA2_SIZE);

	acpi_desc = &t->acpi_desc;
	set_bit(ND_CMD_ARS_CAP, &acpi_desc->bus_cmd_क्रमce_en);
	set_bit(ND_CMD_ARS_START, &acpi_desc->bus_cmd_क्रमce_en);
	set_bit(ND_CMD_ARS_STATUS, &acpi_desc->bus_cmd_क्रमce_en);
	set_bit(ND_CMD_CLEAR_ERROR, &acpi_desc->bus_cmd_क्रमce_en);
	set_bit(ND_INTEL_ENABLE_LSS_STATUS, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_CMD_GET_CONFIG_SIZE, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_CMD_GET_CONFIG_DATA, &acpi_desc->dimm_cmd_क्रमce_en);
	set_bit(ND_CMD_SET_CONFIG_DATA, &acpi_desc->dimm_cmd_क्रमce_en);
पूर्ण

अटल पूर्णांक nfit_test_blk_करो_io(काष्ठा nd_blk_region *ndbr, resource_माप_प्रकार dpa,
		व्योम *iobuf, u64 len, पूर्णांक rw)
अणु
	काष्ठा nfit_blk *nfit_blk = ndbr->blk_provider_data;
	काष्ठा nfit_blk_mmio *mmio = &nfit_blk->mmio[BDW];
	काष्ठा nd_region *nd_region = &ndbr->nd_region;
	अचिन्हित पूर्णांक lane;

	lane = nd_region_acquire_lane(nd_region);
	अगर (rw)
		स_नकल(mmio->addr.base + dpa, iobuf, len);
	अन्यथा अणु
		स_नकल(iobuf, mmio->addr.base + dpa, len);

		/* give us some some coverage of the arch_invalidate_pmem() API */
		arch_invalidate_pmem(mmio->addr.base + dpa, len);
	पूर्ण
	nd_region_release_lane(nd_region, lane);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ nfit_ctl_handle;

जोड़ acpi_object *result;

अटल जोड़ acpi_object *nfit_test_evaluate_dsm(acpi_handle handle,
		स्थिर guid_t *guid, u64 rev, u64 func, जोड़ acpi_object *argv4)
अणु
	अगर (handle != &nfit_ctl_handle)
		वापस ERR_PTR(-ENXIO);

	वापस result;
पूर्ण

अटल पूर्णांक setup_result(व्योम *buf, माप_प्रकार size)
अणु
	result = kदो_स्मृति(माप(जोड़ acpi_object) + size, GFP_KERNEL);
	अगर (!result)
		वापस -ENOMEM;
	result->package.type = ACPI_TYPE_BUFFER,
	result->buffer.poपूर्णांकer = (व्योम *) (result + 1);
	result->buffer.length = size;
	स_नकल(result->buffer.poपूर्णांकer, buf, size);
	स_रखो(buf, 0, size);
	वापस 0;
पूर्ण

अटल पूर्णांक nfit_ctl_test(काष्ठा device *dev)
अणु
	पूर्णांक rc, cmd_rc;
	काष्ठा nvdimm *nvdimm;
	काष्ठा acpi_device *adev;
	काष्ठा nfit_mem *nfit_mem;
	काष्ठा nd_ars_record *record;
	काष्ठा acpi_nfit_desc *acpi_desc;
	स्थिर u64 test_val = 0x0123456789abcdefULL;
	अचिन्हित दीर्घ mask, cmd_size, offset;
	काष्ठा nfit_ctl_test_cmd अणु
		काष्ठा nd_cmd_pkg pkg;
		जोड़ अणु
			काष्ठा nd_cmd_get_config_size cfg_size;
			काष्ठा nd_cmd_clear_error clear_err;
			काष्ठा nd_cmd_ars_status ars_stat;
			काष्ठा nd_cmd_ars_cap ars_cap;
			काष्ठा nd_पूर्णांकel_bus_fw_activate_businfo fwa_info;
			अक्षर buf[माप(काष्ठा nd_cmd_ars_status)
				+ माप(काष्ठा nd_ars_record)];
		पूर्ण;
	पूर्ण cmd;

	adev = devm_kzalloc(dev, माप(*adev), GFP_KERNEL);
	अगर (!adev)
		वापस -ENOMEM;
	*adev = (काष्ठा acpi_device) अणु
		.handle = &nfit_ctl_handle,
		.dev = अणु
			.init_name = "test-adev",
		पूर्ण,
	पूर्ण;

	acpi_desc = devm_kzalloc(dev, माप(*acpi_desc), GFP_KERNEL);
	अगर (!acpi_desc)
		वापस -ENOMEM;
	*acpi_desc = (काष्ठा acpi_nfit_desc) अणु
		.nd_desc = अणु
			.cmd_mask = 1UL << ND_CMD_ARS_CAP
				| 1UL << ND_CMD_ARS_START
				| 1UL << ND_CMD_ARS_STATUS
				| 1UL << ND_CMD_CLEAR_ERROR
				| 1UL << ND_CMD_CALL,
			.module = THIS_MODULE,
			.provider_name = "ACPI.NFIT",
			.ndctl = acpi_nfit_ctl,
			.bus_family_mask = 1UL << NVDIMM_BUS_FAMILY_NFIT
				| 1UL << NVDIMM_BUS_FAMILY_INTEL,
		पूर्ण,
		.bus_dsm_mask = 1UL << NFIT_CMD_TRANSLATE_SPA
			| 1UL << NFIT_CMD_ARS_INJECT_SET
			| 1UL << NFIT_CMD_ARS_INJECT_CLEAR
			| 1UL << NFIT_CMD_ARS_INJECT_GET,
		.family_dsm_mask[NVDIMM_BUS_FAMILY_INTEL] =
			NVDIMM_BUS_INTEL_FW_ACTIVATE_CMDMASK,
		.dev = &adev->dev,
	पूर्ण;

	nfit_mem = devm_kzalloc(dev, माप(*nfit_mem), GFP_KERNEL);
	अगर (!nfit_mem)
		वापस -ENOMEM;

	mask = 1UL << ND_CMD_SMART | 1UL << ND_CMD_SMART_THRESHOLD
		| 1UL << ND_CMD_DIMM_FLAGS | 1UL << ND_CMD_GET_CONFIG_SIZE
		| 1UL << ND_CMD_GET_CONFIG_DATA | 1UL << ND_CMD_SET_CONFIG_DATA
		| 1UL << ND_CMD_VENDOR;
	*nfit_mem = (काष्ठा nfit_mem) अणु
		.adev = adev,
		.family = NVDIMM_FAMILY_INTEL,
		.dsm_mask = mask,
	पूर्ण;

	nvdimm = devm_kzalloc(dev, माप(*nvdimm), GFP_KERNEL);
	अगर (!nvdimm)
		वापस -ENOMEM;
	*nvdimm = (काष्ठा nvdimm) अणु
		.provider_data = nfit_mem,
		.cmd_mask = mask,
		.dev = अणु
			.init_name = "test-dimm",
		पूर्ण,
	पूर्ण;


	/* basic checkout of a typical 'get config size' command */
	cmd_size = माप(cmd.cfg_size);
	cmd.cfg_size = (काष्ठा nd_cmd_get_config_size) अणु
		.status = 0,
		.config_size = SZ_128K,
		.max_xfer = SZ_4K,
	पूर्ण;
	rc = setup_result(cmd.buf, cmd_size);
	अगर (rc)
		वापस rc;
	rc = acpi_nfit_ctl(&acpi_desc->nd_desc, nvdimm, ND_CMD_GET_CONFIG_SIZE,
			cmd.buf, cmd_size, &cmd_rc);

	अगर (rc < 0 || cmd_rc || cmd.cfg_size.status != 0
			|| cmd.cfg_size.config_size != SZ_128K
			|| cmd.cfg_size.max_xfer != SZ_4K) अणु
		dev_dbg(dev, "%s: failed at: %d rc: %d cmd_rc: %d\n",
				__func__, __LINE__, rc, cmd_rc);
		वापस -EIO;
	पूर्ण


	/* test ars_status with zero output */
	cmd_size = दुरत्व(काष्ठा nd_cmd_ars_status, address);
	cmd.ars_stat = (काष्ठा nd_cmd_ars_status) अणु
		.out_length = 0,
	पूर्ण;
	rc = setup_result(cmd.buf, cmd_size);
	अगर (rc)
		वापस rc;
	rc = acpi_nfit_ctl(&acpi_desc->nd_desc, शून्य, ND_CMD_ARS_STATUS,
			cmd.buf, cmd_size, &cmd_rc);

	अगर (rc < 0 || cmd_rc) अणु
		dev_dbg(dev, "%s: failed at: %d rc: %d cmd_rc: %d\n",
				__func__, __LINE__, rc, cmd_rc);
		वापस -EIO;
	पूर्ण


	/* test ars_cap with benign extended status */
	cmd_size = माप(cmd.ars_cap);
	cmd.ars_cap = (काष्ठा nd_cmd_ars_cap) अणु
		.status = ND_ARS_PERSISTENT << 16,
	पूर्ण;
	offset = दुरत्व(काष्ठा nd_cmd_ars_cap, status);
	rc = setup_result(cmd.buf + offset, cmd_size - offset);
	अगर (rc)
		वापस rc;
	rc = acpi_nfit_ctl(&acpi_desc->nd_desc, शून्य, ND_CMD_ARS_CAP,
			cmd.buf, cmd_size, &cmd_rc);

	अगर (rc < 0 || cmd_rc) अणु
		dev_dbg(dev, "%s: failed at: %d rc: %d cmd_rc: %d\n",
				__func__, __LINE__, rc, cmd_rc);
		वापस -EIO;
	पूर्ण


	/* test ars_status with 'status' trimmed from 'out_length' */
	cmd_size = माप(cmd.ars_stat) + माप(काष्ठा nd_ars_record);
	cmd.ars_stat = (काष्ठा nd_cmd_ars_status) अणु
		.out_length = cmd_size - 4,
	पूर्ण;
	record = &cmd.ars_stat.records[0];
	*record = (काष्ठा nd_ars_record) अणु
		.length = test_val,
	पूर्ण;
	rc = setup_result(cmd.buf, cmd_size);
	अगर (rc)
		वापस rc;
	rc = acpi_nfit_ctl(&acpi_desc->nd_desc, शून्य, ND_CMD_ARS_STATUS,
			cmd.buf, cmd_size, &cmd_rc);

	अगर (rc < 0 || cmd_rc || record->length != test_val) अणु
		dev_dbg(dev, "%s: failed at: %d rc: %d cmd_rc: %d\n",
				__func__, __LINE__, rc, cmd_rc);
		वापस -EIO;
	पूर्ण


	/* test ars_status with 'Output (Size)' including 'status' */
	cmd_size = माप(cmd.ars_stat) + माप(काष्ठा nd_ars_record);
	cmd.ars_stat = (काष्ठा nd_cmd_ars_status) अणु
		.out_length = cmd_size,
	पूर्ण;
	record = &cmd.ars_stat.records[0];
	*record = (काष्ठा nd_ars_record) अणु
		.length = test_val,
	पूर्ण;
	rc = setup_result(cmd.buf, cmd_size);
	अगर (rc)
		वापस rc;
	rc = acpi_nfit_ctl(&acpi_desc->nd_desc, शून्य, ND_CMD_ARS_STATUS,
			cmd.buf, cmd_size, &cmd_rc);

	अगर (rc < 0 || cmd_rc || record->length != test_val) अणु
		dev_dbg(dev, "%s: failed at: %d rc: %d cmd_rc: %d\n",
				__func__, __LINE__, rc, cmd_rc);
		वापस -EIO;
	पूर्ण


	/* test extended status क्रम get_config_size results in failure */
	cmd_size = माप(cmd.cfg_size);
	cmd.cfg_size = (काष्ठा nd_cmd_get_config_size) अणु
		.status = 1 << 16,
	पूर्ण;
	rc = setup_result(cmd.buf, cmd_size);
	अगर (rc)
		वापस rc;
	rc = acpi_nfit_ctl(&acpi_desc->nd_desc, nvdimm, ND_CMD_GET_CONFIG_SIZE,
			cmd.buf, cmd_size, &cmd_rc);

	अगर (rc < 0 || cmd_rc >= 0) अणु
		dev_dbg(dev, "%s: failed at: %d rc: %d cmd_rc: %d\n",
				__func__, __LINE__, rc, cmd_rc);
		वापस -EIO;
	पूर्ण

	/* test clear error */
	cmd_size = माप(cmd.clear_err);
	cmd.clear_err = (काष्ठा nd_cmd_clear_error) अणु
		.length = 512,
		.cleared = 512,
	पूर्ण;
	rc = setup_result(cmd.buf, cmd_size);
	अगर (rc)
		वापस rc;
	rc = acpi_nfit_ctl(&acpi_desc->nd_desc, शून्य, ND_CMD_CLEAR_ERROR,
			cmd.buf, cmd_size, &cmd_rc);
	अगर (rc < 0 || cmd_rc) अणु
		dev_dbg(dev, "%s: failed at: %d rc: %d cmd_rc: %d\n",
				__func__, __LINE__, rc, cmd_rc);
		वापस -EIO;
	पूर्ण

	/* test firmware activate bus info */
	cmd_size = माप(cmd.fwa_info);
	cmd = (काष्ठा nfit_ctl_test_cmd) अणु
		.pkg = अणु
			.nd_command = NVDIMM_BUS_INTEL_FW_ACTIVATE_BUSINFO,
			.nd_family = NVDIMM_BUS_FAMILY_INTEL,
			.nd_size_out = cmd_size,
			.nd_fw_size = cmd_size,
		पूर्ण,
		.fwa_info = अणु
			.state = ND_INTEL_FWA_IDLE,
			.capability = ND_INTEL_BUS_FWA_CAP_FWQUIESCE
				| ND_INTEL_BUS_FWA_CAP_OSQUIESCE,
			.activate_पंचांगo = 1,
			.cpu_quiesce_पंचांगo = 1,
			.io_quiesce_पंचांगo = 1,
			.max_quiesce_पंचांगo = 1,
		पूर्ण,
	पूर्ण;
	rc = setup_result(cmd.buf, cmd_size);
	अगर (rc)
		वापस rc;
	rc = acpi_nfit_ctl(&acpi_desc->nd_desc, शून्य, ND_CMD_CALL,
			&cmd, माप(cmd.pkg) + cmd_size, &cmd_rc);
	अगर (rc < 0 || cmd_rc) अणु
		dev_dbg(dev, "%s: failed at: %d rc: %d cmd_rc: %d\n",
				__func__, __LINE__, rc, cmd_rc);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfit_test_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc;
	काष्ठा acpi_nfit_desc *acpi_desc;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा nfit_test *nfit_test;
	काष्ठा nfit_mem *nfit_mem;
	जोड़ acpi_object *obj;
	पूर्णांक rc;

	अगर (म_भेद(dev_name(&pdev->dev), "nfit_test.0") == 0) अणु
		rc = nfit_ctl_test(&pdev->dev);
		अगर (rc)
			वापस rc;
	पूर्ण

	nfit_test = to_nfit_test(&pdev->dev);

	/* common alloc */
	अगर (nfit_test->num_dcr) अणु
		पूर्णांक num = nfit_test->num_dcr;

		nfit_test->dimm = devm_kसुस्मृति(dev, num, माप(व्योम *),
				GFP_KERNEL);
		nfit_test->dimm_dma = devm_kसुस्मृति(dev, num, माप(dma_addr_t),
				GFP_KERNEL);
		nfit_test->flush = devm_kसुस्मृति(dev, num, माप(व्योम *),
				GFP_KERNEL);
		nfit_test->flush_dma = devm_kसुस्मृति(dev, num, माप(dma_addr_t),
				GFP_KERNEL);
		nfit_test->label = devm_kसुस्मृति(dev, num, माप(व्योम *),
				GFP_KERNEL);
		nfit_test->label_dma = devm_kसुस्मृति(dev, num,
				माप(dma_addr_t), GFP_KERNEL);
		nfit_test->dcr = devm_kसुस्मृति(dev, num,
				माप(काष्ठा nfit_test_dcr *), GFP_KERNEL);
		nfit_test->dcr_dma = devm_kसुस्मृति(dev, num,
				माप(dma_addr_t), GFP_KERNEL);
		nfit_test->smart = devm_kसुस्मृति(dev, num,
				माप(काष्ठा nd_पूर्णांकel_smart), GFP_KERNEL);
		nfit_test->smart_threshold = devm_kसुस्मृति(dev, num,
				माप(काष्ठा nd_पूर्णांकel_smart_threshold),
				GFP_KERNEL);
		nfit_test->fw = devm_kसुस्मृति(dev, num,
				माप(काष्ठा nfit_test_fw), GFP_KERNEL);
		अगर (nfit_test->dimm && nfit_test->dimm_dma && nfit_test->label
				&& nfit_test->label_dma && nfit_test->dcr
				&& nfit_test->dcr_dma && nfit_test->flush
				&& nfit_test->flush_dma
				&& nfit_test->fw)
			/* pass */;
		अन्यथा
			वापस -ENOMEM;
	पूर्ण

	अगर (nfit_test->num_pm) अणु
		पूर्णांक num = nfit_test->num_pm;

		nfit_test->spa_set = devm_kसुस्मृति(dev, num, माप(व्योम *),
				GFP_KERNEL);
		nfit_test->spa_set_dma = devm_kसुस्मृति(dev, num,
				माप(dma_addr_t), GFP_KERNEL);
		अगर (nfit_test->spa_set && nfit_test->spa_set_dma)
			/* pass */;
		अन्यथा
			वापस -ENOMEM;
	पूर्ण

	/* per-nfit specअगरic alloc */
	अगर (nfit_test->alloc(nfit_test))
		वापस -ENOMEM;

	nfit_test->setup(nfit_test);
	acpi_desc = &nfit_test->acpi_desc;
	acpi_nfit_desc_init(acpi_desc, &pdev->dev);
	acpi_desc->blk_करो_io = nfit_test_blk_करो_io;
	nd_desc = &acpi_desc->nd_desc;
	nd_desc->provider_name = शून्य;
	nd_desc->module = THIS_MODULE;
	nd_desc->ndctl = nfit_test_ctl;

	rc = acpi_nfit_init(acpi_desc, nfit_test->nfit_buf,
			nfit_test->nfit_filled);
	अगर (rc)
		वापस rc;

	rc = devm_add_action_or_reset(&pdev->dev, acpi_nfit_shutकरोwn, acpi_desc);
	अगर (rc)
		वापस rc;

	अगर (nfit_test->setup != nfit_test0_setup)
		वापस 0;

	nfit_test->setup_hotplug = 1;
	nfit_test->setup(nfit_test);

	obj = kzalloc(माप(*obj), GFP_KERNEL);
	अगर (!obj)
		वापस -ENOMEM;
	obj->type = ACPI_TYPE_BUFFER;
	obj->buffer.length = nfit_test->nfit_size;
	obj->buffer.poपूर्णांकer = nfit_test->nfit_buf;
	*(nfit_test->_fit) = obj;
	__acpi_nfit_notअगरy(&pdev->dev, nfit_test, 0x80);

	/* associate dimm devices with nfit_mem data क्रम notअगरication testing */
	mutex_lock(&acpi_desc->init_mutex);
	list_क्रम_each_entry(nfit_mem, &acpi_desc->dimms, list) अणु
		u32 nfit_handle = __to_nfit_memdev(nfit_mem)->device_handle;
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(handle); i++)
			अगर (nfit_handle == handle[i])
				dev_set_drvdata(nfit_test->dimm_dev[i],
						nfit_mem);
	पूर्ण
	mutex_unlock(&acpi_desc->init_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक nfit_test_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल व्योम nfit_test_release(काष्ठा device *dev)
अणु
	काष्ठा nfit_test *nfit_test = to_nfit_test(dev);

	kमुक्त(nfit_test);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id nfit_test_id[] = अणु
	अणु KBUILD_MODNAME पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver nfit_test_driver = अणु
	.probe = nfit_test_probe,
	.हटाओ = nfit_test_हटाओ,
	.driver = अणु
		.name = KBUILD_MODNAME,
	पूर्ण,
	.id_table = nfit_test_id,
पूर्ण;

अटल __init पूर्णांक nfit_test_init(व्योम)
अणु
	पूर्णांक rc, i;

	pmem_test();
	libnvdimm_test();
	acpi_nfit_test();
	device_dax_test();
	dax_pmem_test();
	dax_pmem_core_test();
#अगर_घोषित CONFIG_DEV_DAX_PMEM_COMPAT
	dax_pmem_compat_test();
#पूर्ण_अगर

	nfit_test_setup(nfit_test_lookup, nfit_test_evaluate_dsm);

	nfit_wq = create_singlethपढ़ो_workqueue("nfit");
	अगर (!nfit_wq)
		वापस -ENOMEM;

	nfit_test_dimm = class_create(THIS_MODULE, "nfit_test_dimm");
	अगर (IS_ERR(nfit_test_dimm)) अणु
		rc = PTR_ERR(nfit_test_dimm);
		जाओ err_रेजिस्टर;
	पूर्ण

	nfit_pool = gen_pool_create(ilog2(SZ_4M), NUMA_NO_NODE);
	अगर (!nfit_pool) अणु
		rc = -ENOMEM;
		जाओ err_रेजिस्टर;
	पूर्ण

	अगर (gen_pool_add(nfit_pool, SZ_4G, SZ_4G, NUMA_NO_NODE)) अणु
		rc = -ENOMEM;
		जाओ err_रेजिस्टर;
	पूर्ण

	क्रम (i = 0; i < NUM_NFITS; i++) अणु
		काष्ठा nfit_test *nfit_test;
		काष्ठा platक्रमm_device *pdev;

		nfit_test = kzalloc(माप(*nfit_test), GFP_KERNEL);
		अगर (!nfit_test) अणु
			rc = -ENOMEM;
			जाओ err_रेजिस्टर;
		पूर्ण
		INIT_LIST_HEAD(&nfit_test->resources);
		badrange_init(&nfit_test->badrange);
		चयन (i) अणु
		हाल 0:
			nfit_test->num_pm = NUM_PM;
			nfit_test->dcr_idx = 0;
			nfit_test->num_dcr = NUM_DCR;
			nfit_test->alloc = nfit_test0_alloc;
			nfit_test->setup = nfit_test0_setup;
			अवरोध;
		हाल 1:
			nfit_test->num_pm = 2;
			nfit_test->dcr_idx = NUM_DCR;
			nfit_test->num_dcr = 2;
			nfit_test->alloc = nfit_test1_alloc;
			nfit_test->setup = nfit_test1_setup;
			अवरोध;
		शेष:
			rc = -EINVAL;
			जाओ err_रेजिस्टर;
		पूर्ण
		pdev = &nfit_test->pdev;
		pdev->name = KBUILD_MODNAME;
		pdev->id = i;
		pdev->dev.release = nfit_test_release;
		rc = platक्रमm_device_रेजिस्टर(pdev);
		अगर (rc) अणु
			put_device(&pdev->dev);
			जाओ err_रेजिस्टर;
		पूर्ण
		get_device(&pdev->dev);

		rc = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
		अगर (rc)
			जाओ err_रेजिस्टर;

		instances[i] = nfit_test;
		INIT_WORK(&nfit_test->work, uc_error_notअगरy);
	पूर्ण

	rc = platक्रमm_driver_रेजिस्टर(&nfit_test_driver);
	अगर (rc)
		जाओ err_रेजिस्टर;
	वापस 0;

 err_रेजिस्टर:
	अगर (nfit_pool)
		gen_pool_destroy(nfit_pool);

	destroy_workqueue(nfit_wq);
	क्रम (i = 0; i < NUM_NFITS; i++)
		अगर (instances[i])
			platक्रमm_device_unरेजिस्टर(&instances[i]->pdev);
	nfit_test_tearकरोwn();
	क्रम (i = 0; i < NUM_NFITS; i++)
		अगर (instances[i])
			put_device(&instances[i]->pdev.dev);

	वापस rc;
पूर्ण

अटल __निकास व्योम nfit_test_निकास(व्योम)
अणु
	पूर्णांक i;

	flush_workqueue(nfit_wq);
	destroy_workqueue(nfit_wq);
	क्रम (i = 0; i < NUM_NFITS; i++)
		platक्रमm_device_unरेजिस्टर(&instances[i]->pdev);
	platक्रमm_driver_unरेजिस्टर(&nfit_test_driver);
	nfit_test_tearकरोwn();

	gen_pool_destroy(nfit_pool);

	क्रम (i = 0; i < NUM_NFITS; i++)
		put_device(&instances[i]->pdev.dev);
	class_destroy(nfit_test_dimm);
पूर्ण

module_init(nfit_test_init);
module_निकास(nfit_test_निकास);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Intel Corporation");
