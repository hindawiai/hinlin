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
#समावेश <linux/list.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_xgmi.h"
#समावेश "amdgpu_ras.h"
#समावेश "soc15.h"
#समावेश "df/df_3_6_offset.h"
#समावेश "xgmi/xgmi_4_0_0_smn.h"
#समावेश "xgmi/xgmi_4_0_0_sh_mask.h"
#समावेश "wafl/wafl2_4_0_0_smn.h"
#समावेश "wafl/wafl2_4_0_0_sh_mask.h"

अटल DEFINE_MUTEX(xgmi_mutex);

#घोषणा AMDGPU_MAX_XGMI_DEVICE_PER_HIVE		4

अटल LIST_HEAD(xgmi_hive_list);

अटल स्थिर पूर्णांक xgmi_pcs_err_status_reg_vg20[] = अणु
	smnXGMI0_PCS_GOPX16_PCS_ERROR_STATUS,
	smnXGMI0_PCS_GOPX16_PCS_ERROR_STATUS + 0x100000,
पूर्ण;

अटल स्थिर पूर्णांक wafl_pcs_err_status_reg_vg20[] = अणु
	smnPCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS,
	smnPCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS + 0x100000,
पूर्ण;

अटल स्थिर पूर्णांक xgmi_pcs_err_status_reg_arct[] = अणु
	smnXGMI0_PCS_GOPX16_PCS_ERROR_STATUS,
	smnXGMI0_PCS_GOPX16_PCS_ERROR_STATUS + 0x100000,
	smnXGMI0_PCS_GOPX16_PCS_ERROR_STATUS + 0x500000,
	smnXGMI0_PCS_GOPX16_PCS_ERROR_STATUS + 0x600000,
	smnXGMI0_PCS_GOPX16_PCS_ERROR_STATUS + 0x700000,
	smnXGMI0_PCS_GOPX16_PCS_ERROR_STATUS + 0x800000,
पूर्ण;

/* same as vg20*/
अटल स्थिर पूर्णांक wafl_pcs_err_status_reg_arct[] = अणु
	smnPCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS,
	smnPCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS + 0x100000,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_pcs_ras_field xgmi_pcs_ras_fields[] = अणु
	अणु"XGMI PCS DataLossErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, DataLossErr)पूर्ण,
	अणु"XGMI PCS TrainingErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, TrainingErr)पूर्ण,
	अणु"XGMI PCS CRCErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, CRCErr)पूर्ण,
	अणु"XGMI PCS BERExceededErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, BERExceededErr)पूर्ण,
	अणु"XGMI PCS TxMetaDataErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, TxMetaDataErr)पूर्ण,
	अणु"XGMI PCS ReplayBufParityErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, ReplayBufParityErr)पूर्ण,
	अणु"XGMI PCS DataParityErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, DataParityErr)पूर्ण,
	अणु"XGMI PCS ReplayFifoOverflowErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, ReplayFअगरoOverflowErr)पूर्ण,
	अणु"XGMI PCS ReplayFifoUnderflowErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, ReplayFअगरoUnderflowErr)पूर्ण,
	अणु"XGMI PCS ElasticFifoOverflowErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, ElasticFअगरoOverflowErr)पूर्ण,
	अणु"XGMI PCS DeskewErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, DeskewErr)पूर्ण,
	अणु"XGMI PCS DataStartupLimitErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, DataStartupLimitErr)पूर्ण,
	अणु"XGMI PCS FCInitTimeoutErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, FCInitTimeoutErr)पूर्ण,
	अणु"XGMI PCS RecoveryTimeoutErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, RecoveryTimeoutErr)पूर्ण,
	अणु"XGMI PCS ReadySerialTimeoutErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, ReadySerialTimeoutErr)पूर्ण,
	अणु"XGMI PCS ReadySerialAttemptErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, ReadySerialAttemptErr)पूर्ण,
	अणु"XGMI PCS RecoveryAttemptErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, RecoveryAttemptErr)पूर्ण,
	अणु"XGMI PCS RecoveryRelockAttemptErr",
	 SOC15_REG_FIELD(XGMI0_PCS_GOPX16_PCS_ERROR_STATUS, RecoveryRelockAttemptErr)पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_pcs_ras_field wafl_pcs_ras_fields[] = अणु
	अणु"WAFL PCS DataLossErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, DataLossErr)पूर्ण,
	अणु"WAFL PCS TrainingErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, TrainingErr)पूर्ण,
	अणु"WAFL PCS CRCErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, CRCErr)पूर्ण,
	अणु"WAFL PCS BERExceededErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, BERExceededErr)पूर्ण,
	अणु"WAFL PCS TxMetaDataErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, TxMetaDataErr)पूर्ण,
	अणु"WAFL PCS ReplayBufParityErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, ReplayBufParityErr)पूर्ण,
	अणु"WAFL PCS DataParityErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, DataParityErr)पूर्ण,
	अणु"WAFL PCS ReplayFifoOverflowErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, ReplayFअगरoOverflowErr)पूर्ण,
	अणु"WAFL PCS ReplayFifoUnderflowErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, ReplayFअगरoUnderflowErr)पूर्ण,
	अणु"WAFL PCS ElasticFifoOverflowErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, ElasticFअगरoOverflowErr)पूर्ण,
	अणु"WAFL PCS DeskewErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, DeskewErr)पूर्ण,
	अणु"WAFL PCS DataStartupLimitErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, DataStartupLimitErr)पूर्ण,
	अणु"WAFL PCS FCInitTimeoutErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, FCInitTimeoutErr)पूर्ण,
	अणु"WAFL PCS RecoveryTimeoutErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, RecoveryTimeoutErr)पूर्ण,
	अणु"WAFL PCS ReadySerialTimeoutErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, ReadySerialTimeoutErr)पूर्ण,
	अणु"WAFL PCS ReadySerialAttemptErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, ReadySerialAttemptErr)पूर्ण,
	अणु"WAFL PCS RecoveryAttemptErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, RecoveryAttemptErr)पूर्ण,
	अणु"WAFL PCS RecoveryRelockAttemptErr",
	 SOC15_REG_FIELD(PCS_GOPX1_0_PCS_GOPX1_PCS_ERROR_STATUS, RecoveryRelockAttemptErr)पूर्ण,
पूर्ण;

/**
 * DOC: AMDGPU XGMI Support
 *
 * XGMI is a high speed पूर्णांकerconnect that joins multiple GPU cards
 * पूर्णांकo a homogeneous memory space that is organized by a collective
 * hive ID and inभागidual node IDs, both of which are 64-bit numbers.
 *
 * The file xgmi_device_id contains the unique per GPU device ID and
 * is stored in the /sys/class/drm/card$अणुcardnoपूर्ण/device/ directory.
 *
 * Inside the device directory a sub-directory 'xgmi_hive_info' is
 * created which contains the hive ID and the list of nodes.
 *
 * The hive ID is stored in:
 *   /sys/class/drm/card$अणुcardnoपूर्ण/device/xgmi_hive_info/xgmi_hive_id
 *
 * The node inक्रमmation is stored in numbered directories:
 *   /sys/class/drm/card$अणुcardnoपूर्ण/device/xgmi_hive_info/node$अणुnodenoपूर्ण/xgmi_device_id
 *
 * Each device has their own xgmi_hive_info direction with a mirror
 * set of node sub-directories.
 *
 * The XGMI memory space is built by contiguously adding the घातer of
 * two padded VRAM space from each node to each other.
 *
 */

अटल काष्ठा attribute amdgpu_xgmi_hive_id = अणु
	.name = "xgmi_hive_id",
	.mode = S_IRUGO
पूर्ण;

अटल काष्ठा attribute *amdgpu_xgmi_hive_attrs[] = अणु
	&amdgpu_xgmi_hive_id,
	शून्य
पूर्ण;

अटल sमाप_प्रकार amdgpu_xgmi_show_attrs(काष्ठा kobject *kobj,
	काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा amdgpu_hive_info *hive = container_of(
		kobj, काष्ठा amdgpu_hive_info, kobj);

	अगर (attr == &amdgpu_xgmi_hive_id)
		वापस snम_लिखो(buf, PAGE_SIZE, "%llu\n", hive->hive_id);

	वापस 0;
पूर्ण

अटल व्योम amdgpu_xgmi_hive_release(काष्ठा kobject *kobj)
अणु
	काष्ठा amdgpu_hive_info *hive = container_of(
		kobj, काष्ठा amdgpu_hive_info, kobj);

	mutex_destroy(&hive->hive_lock);
	kमुक्त(hive);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops amdgpu_xgmi_hive_ops = अणु
	.show = amdgpu_xgmi_show_attrs,
पूर्ण;

काष्ठा kobj_type amdgpu_xgmi_hive_type = अणु
	.release = amdgpu_xgmi_hive_release,
	.sysfs_ops = &amdgpu_xgmi_hive_ops,
	.शेष_attrs = amdgpu_xgmi_hive_attrs,
पूर्ण;

अटल sमाप_प्रकार amdgpu_xgmi_show_device_id(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);

	वापस sysfs_emit(buf, "%llu\n", adev->gmc.xgmi.node_id);

पूर्ण

#घोषणा AMDGPU_XGMI_SET_FICAA(o)	((o) | 0x456801)
अटल sमाप_प्रकार amdgpu_xgmi_show_error(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	uपूर्णांक32_t ficaa_pie_ctl_in, ficaa_pie_status_in;
	uपूर्णांक64_t fica_out;
	अचिन्हित पूर्णांक error_count = 0;

	ficaa_pie_ctl_in = AMDGPU_XGMI_SET_FICAA(0x200);
	ficaa_pie_status_in = AMDGPU_XGMI_SET_FICAA(0x208);

	fica_out = adev->df.funcs->get_fica(adev, ficaa_pie_ctl_in);
	अगर (fica_out != 0x1f)
		pr_err("xGMI error counters not enabled!\n");

	fica_out = adev->df.funcs->get_fica(adev, ficaa_pie_status_in);

	अगर ((fica_out & 0xffff) == 2)
		error_count = ((fica_out >> 62) & 0x1) + (fica_out >> 63);

	adev->df.funcs->set_fica(adev, ficaa_pie_status_in, 0, 0);

	वापस sysfs_emit(buf, "%u\n", error_count);
पूर्ण


अटल DEVICE_ATTR(xgmi_device_id, S_IRUGO, amdgpu_xgmi_show_device_id, शून्य);
अटल DEVICE_ATTR(xgmi_error, S_IRUGO, amdgpu_xgmi_show_error, शून्य);

अटल पूर्णांक amdgpu_xgmi_sysfs_add_dev_info(काष्ठा amdgpu_device *adev,
					 काष्ठा amdgpu_hive_info *hive)
अणु
	पूर्णांक ret = 0;
	अक्षर node[10] = अणु 0 पूर्ण;

	/* Create xgmi device id file */
	ret = device_create_file(adev->dev, &dev_attr_xgmi_device_id);
	अगर (ret) अणु
		dev_err(adev->dev, "XGMI: Failed to create device file xgmi_device_id\n");
		वापस ret;
	पूर्ण

	/* Create xgmi error file */
	ret = device_create_file(adev->dev, &dev_attr_xgmi_error);
	अगर (ret)
		pr_err("failed to create xgmi_error\n");


	/* Create sysfs link to hive info folder on the first device */
	अगर (hive->kobj.parent != (&adev->dev->kobj)) अणु
		ret = sysfs_create_link(&adev->dev->kobj, &hive->kobj,
					"xgmi_hive_info");
		अगर (ret) अणु
			dev_err(adev->dev, "XGMI: Failed to create link to hive info");
			जाओ हटाओ_file;
		पूर्ण
	पूर्ण

	प्र_लिखो(node, "node%d", atomic_पढ़ो(&hive->number_devices));
	/* Create sysfs link क्रमm the hive folder to yourself */
	ret = sysfs_create_link(&hive->kobj, &adev->dev->kobj, node);
	अगर (ret) अणु
		dev_err(adev->dev, "XGMI: Failed to create link from hive info");
		जाओ हटाओ_link;
	पूर्ण

	जाओ success;


हटाओ_link:
	sysfs_हटाओ_link(&adev->dev->kobj, adev_to_drm(adev)->unique);

हटाओ_file:
	device_हटाओ_file(adev->dev, &dev_attr_xgmi_device_id);

success:
	वापस ret;
पूर्ण

अटल व्योम amdgpu_xgmi_sysfs_rem_dev_info(काष्ठा amdgpu_device *adev,
					  काष्ठा amdgpu_hive_info *hive)
अणु
	अक्षर node[10];
	स_रखो(node, 0, माप(node));

	device_हटाओ_file(adev->dev, &dev_attr_xgmi_device_id);
	device_हटाओ_file(adev->dev, &dev_attr_xgmi_error);

	अगर (hive->kobj.parent != (&adev->dev->kobj))
		sysfs_हटाओ_link(&adev->dev->kobj,"xgmi_hive_info");

	प्र_लिखो(node, "node%d", atomic_पढ़ो(&hive->number_devices));
	sysfs_हटाओ_link(&hive->kobj, node);

पूर्ण



काष्ठा amdgpu_hive_info *amdgpu_get_xgmi_hive(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_hive_info *hive = शून्य;
	पूर्णांक ret;

	अगर (!adev->gmc.xgmi.hive_id)
		वापस शून्य;

	अगर (adev->hive) अणु
		kobject_get(&adev->hive->kobj);
		वापस adev->hive;
	पूर्ण

	mutex_lock(&xgmi_mutex);

	list_क्रम_each_entry(hive, &xgmi_hive_list, node)  अणु
		अगर (hive->hive_id == adev->gmc.xgmi.hive_id)
			जाओ pro_end;
	पूर्ण

	hive = kzalloc(माप(*hive), GFP_KERNEL);
	अगर (!hive) अणु
		dev_err(adev->dev, "XGMI: allocation failed\n");
		hive = शून्य;
		जाओ pro_end;
	पूर्ण

	/* initialize new hive अगर not exist */
	ret = kobject_init_and_add(&hive->kobj,
			&amdgpu_xgmi_hive_type,
			&adev->dev->kobj,
			"%s", "xgmi_hive_info");
	अगर (ret) अणु
		dev_err(adev->dev, "XGMI: failed initializing kobject for xgmi hive\n");
		kमुक्त(hive);
		hive = शून्य;
		जाओ pro_end;
	पूर्ण

	hive->hive_id = adev->gmc.xgmi.hive_id;
	INIT_LIST_HEAD(&hive->device_list);
	INIT_LIST_HEAD(&hive->node);
	mutex_init(&hive->hive_lock);
	atomic_set(&hive->in_reset, 0);
	atomic_set(&hive->number_devices, 0);
	task_barrier_init(&hive->tb);
	hive->pstate = AMDGPU_XGMI_PSTATE_UNKNOWN;
	hive->hi_req_gpu = शून्य;
	/*
	 * hive pstate on boot is high in vega20 so we have to go to low
	 * pstate on after boot.
	 */
	hive->hi_req_count = AMDGPU_MAX_XGMI_DEVICE_PER_HIVE;
	list_add_tail(&hive->node, &xgmi_hive_list);

pro_end:
	अगर (hive)
		kobject_get(&hive->kobj);
	mutex_unlock(&xgmi_mutex);
	वापस hive;
पूर्ण

व्योम amdgpu_put_xgmi_hive(काष्ठा amdgpu_hive_info *hive)
अणु
	अगर (hive)
		kobject_put(&hive->kobj);
पूर्ण

पूर्णांक amdgpu_xgmi_set_pstate(काष्ठा amdgpu_device *adev, पूर्णांक pstate)
अणु
	पूर्णांक ret = 0;
	काष्ठा amdgpu_hive_info *hive;
	काष्ठा amdgpu_device *request_adev;
	bool is_hi_req = pstate == AMDGPU_XGMI_PSTATE_MAX_VEGA20;
	bool init_low;

	hive = amdgpu_get_xgmi_hive(adev);
	अगर (!hive)
		वापस 0;

	request_adev = hive->hi_req_gpu ? hive->hi_req_gpu : adev;
	init_low = hive->pstate == AMDGPU_XGMI_PSTATE_UNKNOWN;
	amdgpu_put_xgmi_hive(hive);
	/* fw bug so temporarily disable pstate चयनing */
	वापस 0;

	अगर (!hive || adev->asic_type != CHIP_VEGA20)
		वापस 0;

	mutex_lock(&hive->hive_lock);

	अगर (is_hi_req)
		hive->hi_req_count++;
	अन्यथा
		hive->hi_req_count--;

	/*
	 * Vega20 only needs single peer to request pstate high क्रम the hive to
	 * go high but all peers must request pstate low क्रम the hive to go low
	 */
	अगर (hive->pstate == pstate ||
			(!is_hi_req && hive->hi_req_count && !init_low))
		जाओ out;

	dev_dbg(request_adev->dev, "Set xgmi pstate %d.\n", pstate);

	ret = amdgpu_dpm_set_xgmi_pstate(request_adev, pstate);
	अगर (ret) अणु
		dev_err(request_adev->dev,
			"XGMI: Set pstate failure on device %llx, hive %llx, ret %d",
			request_adev->gmc.xgmi.node_id,
			request_adev->gmc.xgmi.hive_id, ret);
		जाओ out;
	पूर्ण

	अगर (init_low)
		hive->pstate = hive->hi_req_count ?
					hive->pstate : AMDGPU_XGMI_PSTATE_MIN;
	अन्यथा अणु
		hive->pstate = pstate;
		hive->hi_req_gpu = pstate != AMDGPU_XGMI_PSTATE_MIN ?
							adev : शून्य;
	पूर्ण
out:
	mutex_unlock(&hive->hive_lock);
	वापस ret;
पूर्ण

पूर्णांक amdgpu_xgmi_update_topology(काष्ठा amdgpu_hive_info *hive, काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret;

	/* Each psp need to set the latest topology */
	ret = psp_xgmi_set_topology_info(&adev->psp,
					 atomic_पढ़ो(&hive->number_devices),
					 &adev->psp.xgmi_context.top_info);
	अगर (ret)
		dev_err(adev->dev,
			"XGMI: Set topology failure on device %llx, hive %llx, ret %d",
			adev->gmc.xgmi.node_id,
			adev->gmc.xgmi.hive_id, ret);

	वापस ret;
पूर्ण


/*
 * NOTE psp_xgmi_node_info.num_hops layout is as follows:
 * num_hops[7:6] = link type (0 = xGMI2, 1 = xGMI3, 2/3 = reserved)
 * num_hops[5:3] = reserved
 * num_hops[2:0] = number of hops
 */
पूर्णांक amdgpu_xgmi_get_hops_count(काष्ठा amdgpu_device *adev,
		काष्ठा amdgpu_device *peer_adev)
अणु
	काष्ठा psp_xgmi_topology_info *top = &adev->psp.xgmi_context.top_info;
	uपूर्णांक8_t num_hops_mask = 0x7;
	पूर्णांक i;

	क्रम (i = 0 ; i < top->num_nodes; ++i)
		अगर (top->nodes[i].node_id == peer_adev->gmc.xgmi.node_id)
			वापस top->nodes[i].num_hops & num_hops_mask;
	वापस	-EINVAL;
पूर्ण

पूर्णांक amdgpu_xgmi_add_device(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा psp_xgmi_topology_info *top_info;
	काष्ठा amdgpu_hive_info *hive;
	काष्ठा amdgpu_xgmi	*entry;
	काष्ठा amdgpu_device *पंचांगp_adev = शून्य;

	पूर्णांक count = 0, ret = 0;

	अगर (!adev->gmc.xgmi.supported)
		वापस 0;

	अगर (!adev->gmc.xgmi.pending_reset &&
	    amdgpu_device_ip_get_ip_block(adev, AMD_IP_BLOCK_TYPE_PSP)) अणु
		ret = psp_xgmi_initialize(&adev->psp);
		अगर (ret) अणु
			dev_err(adev->dev,
				"XGMI: Failed to initialize xgmi session\n");
			वापस ret;
		पूर्ण

		ret = psp_xgmi_get_hive_id(&adev->psp, &adev->gmc.xgmi.hive_id);
		अगर (ret) अणु
			dev_err(adev->dev,
				"XGMI: Failed to get hive id\n");
			वापस ret;
		पूर्ण

		ret = psp_xgmi_get_node_id(&adev->psp, &adev->gmc.xgmi.node_id);
		अगर (ret) अणु
			dev_err(adev->dev,
				"XGMI: Failed to get node id\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		adev->gmc.xgmi.hive_id = 16;
		adev->gmc.xgmi.node_id = adev->gmc.xgmi.physical_node_id + 16;
	पूर्ण

	hive = amdgpu_get_xgmi_hive(adev);
	अगर (!hive) अणु
		ret = -EINVAL;
		dev_err(adev->dev,
			"XGMI: node 0x%llx, can not match hive 0x%llx in the hive list.\n",
			adev->gmc.xgmi.node_id, adev->gmc.xgmi.hive_id);
		जाओ निकास;
	पूर्ण
	mutex_lock(&hive->hive_lock);

	top_info = &adev->psp.xgmi_context.top_info;

	list_add_tail(&adev->gmc.xgmi.head, &hive->device_list);
	list_क्रम_each_entry(entry, &hive->device_list, head)
		top_info->nodes[count++].node_id = entry->node_id;
	top_info->num_nodes = count;
	atomic_set(&hive->number_devices, count);

	task_barrier_add_task(&hive->tb);

	अगर (!adev->gmc.xgmi.pending_reset &&
	    amdgpu_device_ip_get_ip_block(adev, AMD_IP_BLOCK_TYPE_PSP)) अणु
		list_क्रम_each_entry(पंचांगp_adev, &hive->device_list, gmc.xgmi.head) अणु
			/* update node list क्रम other device in the hive */
			अगर (पंचांगp_adev != adev) अणु
				top_info = &पंचांगp_adev->psp.xgmi_context.top_info;
				top_info->nodes[count - 1].node_id =
					adev->gmc.xgmi.node_id;
				top_info->num_nodes = count;
			पूर्ण
			ret = amdgpu_xgmi_update_topology(hive, पंचांगp_adev);
			अगर (ret)
				जाओ निकास_unlock;
		पूर्ण

		/* get latest topology info क्रम each device from psp */
		list_क्रम_each_entry(पंचांगp_adev, &hive->device_list, gmc.xgmi.head) अणु
			ret = psp_xgmi_get_topology_info(&पंचांगp_adev->psp, count,
					&पंचांगp_adev->psp.xgmi_context.top_info);
			अगर (ret) अणु
				dev_err(पंचांगp_adev->dev,
					"XGMI: Get topology failure on device %llx, hive %llx, ret %d",
					पंचांगp_adev->gmc.xgmi.node_id,
					पंचांगp_adev->gmc.xgmi.hive_id, ret);
				/* To करो : जारी with some node failed or disable the whole hive */
				जाओ निकास_unlock;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ret && !adev->gmc.xgmi.pending_reset)
		ret = amdgpu_xgmi_sysfs_add_dev_info(adev, hive);

निकास_unlock:
	mutex_unlock(&hive->hive_lock);
निकास:
	अगर (!ret) अणु
		adev->hive = hive;
		dev_info(adev->dev, "XGMI: Add node %d, hive 0x%llx.\n",
			 adev->gmc.xgmi.physical_node_id, adev->gmc.xgmi.hive_id);
	पूर्ण अन्यथा अणु
		amdgpu_put_xgmi_hive(hive);
		dev_err(adev->dev, "XGMI: Failed to add node %d, hive 0x%llx ret: %d\n",
			adev->gmc.xgmi.physical_node_id, adev->gmc.xgmi.hive_id,
			ret);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक amdgpu_xgmi_हटाओ_device(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_hive_info *hive = adev->hive;

	अगर (!adev->gmc.xgmi.supported)
		वापस -EINVAL;

	अगर (!hive)
		वापस -EINVAL;

	mutex_lock(&hive->hive_lock);
	task_barrier_rem_task(&hive->tb);
	amdgpu_xgmi_sysfs_rem_dev_info(adev, hive);
	अगर (hive->hi_req_gpu == adev)
		hive->hi_req_gpu = शून्य;
	list_del(&adev->gmc.xgmi.head);
	mutex_unlock(&hive->hive_lock);

	amdgpu_put_xgmi_hive(hive);
	adev->hive = शून्य;

	अगर (atomic_dec_वापस(&hive->number_devices) == 0) अणु
		/* Remove the hive from global hive list */
		mutex_lock(&xgmi_mutex);
		list_del(&hive->node);
		mutex_unlock(&xgmi_mutex);

		amdgpu_put_xgmi_hive(hive);
	पूर्ण

	वापस psp_xgmi_terminate(&adev->psp);
पूर्ण

अटल पूर्णांक amdgpu_xgmi_ras_late_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;
	काष्ठा ras_ih_अगर ih_info = अणु
		.cb = शून्य,
	पूर्ण;
	काष्ठा ras_fs_अगर fs_info = अणु
		.sysfs_name = "xgmi_wafl_err_count",
	पूर्ण;

	अगर (!adev->gmc.xgmi.supported ||
	    adev->gmc.xgmi.num_physical_nodes == 0)
		वापस 0;

	adev->gmc.xgmi.ras_funcs->reset_ras_error_count(adev);

	अगर (!adev->gmc.xgmi.ras_अगर) अणु
		adev->gmc.xgmi.ras_अगर = kदो_स्मृति(माप(काष्ठा ras_common_अगर), GFP_KERNEL);
		अगर (!adev->gmc.xgmi.ras_अगर)
			वापस -ENOMEM;
		adev->gmc.xgmi.ras_अगर->block = AMDGPU_RAS_BLOCK__XGMI_WAFL;
		adev->gmc.xgmi.ras_अगर->type = AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE;
		adev->gmc.xgmi.ras_अगर->sub_block_index = 0;
		म_नकल(adev->gmc.xgmi.ras_अगर->name, "xgmi_wafl");
	पूर्ण
	ih_info.head = fs_info.head = *adev->gmc.xgmi.ras_अगर;
	r = amdgpu_ras_late_init(adev, adev->gmc.xgmi.ras_अगर,
				 &fs_info, &ih_info);
	अगर (r || !amdgpu_ras_is_supported(adev, adev->gmc.xgmi.ras_अगर->block)) अणु
		kमुक्त(adev->gmc.xgmi.ras_अगर);
		adev->gmc.xgmi.ras_अगर = शून्य;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम amdgpu_xgmi_ras_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_ras_is_supported(adev, AMDGPU_RAS_BLOCK__XGMI_WAFL) &&
			adev->gmc.xgmi.ras_अगर) अणु
		काष्ठा ras_common_अगर *ras_अगर = adev->gmc.xgmi.ras_अगर;
		काष्ठा ras_ih_अगर ih_info = अणु
			.cb = शून्य,
		पूर्ण;

		amdgpu_ras_late_fini(adev, ras_अगर, &ih_info);
		kमुक्त(ras_अगर);
	पूर्ण
पूर्ण

uपूर्णांक64_t amdgpu_xgmi_get_relative_phy_addr(काष्ठा amdgpu_device *adev,
					   uपूर्णांक64_t addr)
अणु
	काष्ठा amdgpu_xgmi *xgmi = &adev->gmc.xgmi;
	वापस (addr + xgmi->physical_node_id * xgmi->node_segment_size);
पूर्ण

अटल व्योम pcs_clear_status(काष्ठा amdgpu_device *adev, uपूर्णांक32_t pcs_status_reg)
अणु
	WREG32_PCIE(pcs_status_reg, 0xFFFFFFFF);
	WREG32_PCIE(pcs_status_reg, 0);
पूर्ण

अटल व्योम amdgpu_xgmi_reset_ras_error_count(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t i;

	चयन (adev->asic_type) अणु
	हाल CHIP_ARCTURUS:
		क्रम (i = 0; i < ARRAY_SIZE(xgmi_pcs_err_status_reg_arct); i++)
			pcs_clear_status(adev,
					 xgmi_pcs_err_status_reg_arct[i]);
		अवरोध;
	हाल CHIP_VEGA20:
		क्रम (i = 0; i < ARRAY_SIZE(xgmi_pcs_err_status_reg_vg20); i++)
			pcs_clear_status(adev,
					 xgmi_pcs_err_status_reg_vg20[i]);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक amdgpu_xgmi_query_pcs_error_status(काष्ठा amdgpu_device *adev,
					      uपूर्णांक32_t value,
					      uपूर्णांक32_t *ue_count,
					      uपूर्णांक32_t *ce_count,
					      bool is_xgmi_pcs)
अणु
	पूर्णांक i;
	पूर्णांक ue_cnt;

	अगर (is_xgmi_pcs) अणु
		/* query xgmi pcs error status,
		 * only ue is supported */
		क्रम (i = 0; i < ARRAY_SIZE(xgmi_pcs_ras_fields); i ++) अणु
			ue_cnt = (value &
				  xgmi_pcs_ras_fields[i].pcs_err_mask) >>
				  xgmi_pcs_ras_fields[i].pcs_err_shअगरt;
			अगर (ue_cnt) अणु
				dev_info(adev->dev, "%s detected\n",
					 xgmi_pcs_ras_fields[i].err_name);
				*ue_count += ue_cnt;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* query wafl pcs error status,
		 * only ue is supported */
		क्रम (i = 0; i < ARRAY_SIZE(wafl_pcs_ras_fields); i++) अणु
			ue_cnt = (value &
				  wafl_pcs_ras_fields[i].pcs_err_mask) >>
				  wafl_pcs_ras_fields[i].pcs_err_shअगरt;
			अगर (ue_cnt) अणु
				dev_info(adev->dev, "%s detected\n",
					 wafl_pcs_ras_fields[i].err_name);
				*ue_count += ue_cnt;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_xgmi_query_ras_error_count(काष्ठा amdgpu_device *adev,
					     व्योम *ras_error_status)
अणु
	काष्ठा ras_err_data *err_data = (काष्ठा ras_err_data *)ras_error_status;
	पूर्णांक i;
	uपूर्णांक32_t data;
	uपूर्णांक32_t ue_cnt = 0, ce_cnt = 0;

	अगर (!amdgpu_ras_is_supported(adev, AMDGPU_RAS_BLOCK__XGMI_WAFL))
		वापस -EINVAL;

	err_data->ue_count = 0;
	err_data->ce_count = 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_ARCTURUS:
		/* check xgmi pcs error */
		क्रम (i = 0; i < ARRAY_SIZE(xgmi_pcs_err_status_reg_arct); i++) अणु
			data = RREG32_PCIE(xgmi_pcs_err_status_reg_arct[i]);
			अगर (data)
				amdgpu_xgmi_query_pcs_error_status(adev,
						data, &ue_cnt, &ce_cnt, true);
		पूर्ण
		/* check wafl pcs error */
		क्रम (i = 0; i < ARRAY_SIZE(wafl_pcs_err_status_reg_arct); i++) अणु
			data = RREG32_PCIE(wafl_pcs_err_status_reg_arct[i]);
			अगर (data)
				amdgpu_xgmi_query_pcs_error_status(adev,
						data, &ue_cnt, &ce_cnt, false);
		पूर्ण
		अवरोध;
	हाल CHIP_VEGA20:
	शेष:
		/* check xgmi pcs error */
		क्रम (i = 0; i < ARRAY_SIZE(xgmi_pcs_err_status_reg_vg20); i++) अणु
			data = RREG32_PCIE(xgmi_pcs_err_status_reg_vg20[i]);
			अगर (data)
				amdgpu_xgmi_query_pcs_error_status(adev,
						data, &ue_cnt, &ce_cnt, true);
		पूर्ण
		/* check wafl pcs error */
		क्रम (i = 0; i < ARRAY_SIZE(wafl_pcs_err_status_reg_vg20); i++) अणु
			data = RREG32_PCIE(wafl_pcs_err_status_reg_vg20[i]);
			अगर (data)
				amdgpu_xgmi_query_pcs_error_status(adev,
						data, &ue_cnt, &ce_cnt, false);
		पूर्ण
		अवरोध;
	पूर्ण

	adev->gmc.xgmi.ras_funcs->reset_ras_error_count(adev);

	err_data->ue_count += ue_cnt;
	err_data->ce_count += ce_cnt;

	वापस 0;
पूर्ण

स्थिर काष्ठा amdgpu_xgmi_ras_funcs xgmi_ras_funcs = अणु
	.ras_late_init = amdgpu_xgmi_ras_late_init,
	.ras_fini = amdgpu_xgmi_ras_fini,
	.query_ras_error_count = amdgpu_xgmi_query_ras_error_count,
	.reset_ras_error_count = amdgpu_xgmi_reset_ras_error_count,
पूर्ण;
