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
#समावेश <linux/debugfs.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/reboot.h>
#समावेश <linux/syscalls.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_ras.h"
#समावेश "amdgpu_atomfirmware.h"
#समावेश "amdgpu_xgmi.h"
#समावेश "ivsrcid/nbio/irqsrcs_nbif_7_4.h"

अटल स्थिर अक्षर *RAS_FS_NAME = "ras";

स्थिर अक्षर *ras_error_string[] = अणु
	"none",
	"parity",
	"single_correctable",
	"multi_uncorrectable",
	"poison",
पूर्ण;

स्थिर अक्षर *ras_block_string[] = अणु
	"umc",
	"sdma",
	"gfx",
	"mmhub",
	"athub",
	"pcie_bif",
	"hdp",
	"xgmi_wafl",
	"df",
	"smn",
	"sem",
	"mp0",
	"mp1",
	"fuse",
पूर्ण;

#घोषणा ras_err_str(i) (ras_error_string[ffs(i)])
#घोषणा ras_block_str(i) (ras_block_string[i])

#घोषणा RAS_DEFAULT_FLAGS (AMDGPU_RAS_FLAG_INIT_BY_VBIOS)

/* inject address is 52 bits */
#घोषणा	RAS_UMC_INJECT_ADDR_LIMIT	(0x1ULL << 52)

/* typical ECC bad page rate(1 bad page per 100MB VRAM) */
#घोषणा RAS_BAD_PAGE_RATE		(100 * 1024 * 1024ULL)

क्रमागत amdgpu_ras_retire_page_reservation अणु
	AMDGPU_RAS_RETIRE_PAGE_RESERVED,
	AMDGPU_RAS_RETIRE_PAGE_PENDING,
	AMDGPU_RAS_RETIRE_PAGE_FAULT,
पूर्ण;

atomic_t amdgpu_ras_in_पूर्णांकr = ATOMIC_INIT(0);

अटल bool amdgpu_ras_check_bad_page_unlock(काष्ठा amdgpu_ras *con,
				uपूर्णांक64_t addr);
अटल bool amdgpu_ras_check_bad_page(काष्ठा amdgpu_device *adev,
				uपूर्णांक64_t addr);

व्योम amdgpu_ras_set_error_query_पढ़ोy(काष्ठा amdgpu_device *adev, bool पढ़ोy)
अणु
	अगर (adev && amdgpu_ras_get_context(adev))
		amdgpu_ras_get_context(adev)->error_query_पढ़ोy = पढ़ोy;
पूर्ण

अटल bool amdgpu_ras_get_error_query_पढ़ोy(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev && amdgpu_ras_get_context(adev))
		वापस amdgpu_ras_get_context(adev)->error_query_पढ़ोy;

	वापस false;
पूर्ण

अटल पूर्णांक amdgpu_reserve_page_direct(काष्ठा amdgpu_device *adev, uपूर्णांक64_t address)
अणु
	काष्ठा ras_err_data err_data = अणु0, 0, 0, शून्यपूर्ण;
	काष्ठा eeprom_table_record err_rec;

	अगर ((address >= adev->gmc.mc_vram_size) ||
	    (address >= RAS_UMC_INJECT_ADDR_LIMIT)) अणु
		dev_warn(adev->dev,
		         "RAS WARN: input address 0x%llx is invalid.\n",
		         address);
		वापस -EINVAL;
	पूर्ण

	अगर (amdgpu_ras_check_bad_page(adev, address)) अणु
		dev_warn(adev->dev,
			 "RAS WARN: 0x%llx has already been marked as bad page!\n",
			 address);
		वापस 0;
	पूर्ण

	स_रखो(&err_rec, 0x0, माप(काष्ठा eeprom_table_record));

	err_rec.address = address;
	err_rec.retired_page = address >> AMDGPU_GPU_PAGE_SHIFT;
	err_rec.ts = (uपूर्णांक64_t)kसमय_get_real_seconds();
	err_rec.err_type = AMDGPU_RAS_EEPROM_ERR_NON_RECOVERABLE;

	err_data.err_addr = &err_rec;
	err_data.err_addr_cnt = 1;

	अगर (amdgpu_bad_page_threshold != 0) अणु
		amdgpu_ras_add_bad_pages(adev, err_data.err_addr,
					 err_data.err_addr_cnt);
		amdgpu_ras_save_bad_pages(adev);
	पूर्ण

	dev_warn(adev->dev, "WARNING: THIS IS ONLY FOR TEST PURPOSES AND WILL CORRUPT RAS EEPROM\n");
	dev_warn(adev->dev, "Clear EEPROM:\n");
	dev_warn(adev->dev, "    echo 1 > /sys/kernel/debug/dri/0/ras/ras_eeprom_reset\n");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार amdgpu_ras_debugfs_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा ras_manager *obj = (काष्ठा ras_manager *)file_inode(f)->i_निजी;
	काष्ठा ras_query_अगर info = अणु
		.head = obj->head,
	पूर्ण;
	sमाप_प्रकार s;
	अक्षर val[128];

	अगर (amdgpu_ras_query_error_status(obj->adev, &info))
		वापस -EINVAL;

	s = snम_लिखो(val, माप(val), "%s: %lu\n%s: %lu\n",
			"ue", info.ue_count,
			"ce", info.ce_count);
	अगर (*pos >= s)
		वापस 0;

	s -= *pos;
	s = min_t(u64, s, size);


	अगर (copy_to_user(buf, &val[*pos], s))
		वापस -EINVAL;

	*pos += s;

	वापस s;
पूर्ण

अटल स्थिर काष्ठा file_operations amdgpu_ras_debugfs_ops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_ras_debugfs_पढ़ो,
	.ग_लिखो = शून्य,
	.llseek = शेष_llseek
पूर्ण;

अटल पूर्णांक amdgpu_ras_find_block_id_by_name(स्थिर अक्षर *name, पूर्णांक *block_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ras_block_string); i++) अणु
		*block_id = i;
		अगर (म_भेद(name, ras_block_str(i)) == 0)
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक amdgpu_ras_debugfs_ctrl_parse_data(काष्ठा file *f,
		स्थिर अक्षर __user *buf, माप_प्रकार size,
		loff_t *pos, काष्ठा ras_debug_अगर *data)
अणु
	sमाप_प्रकार s = min_t(u64, 64, size);
	अक्षर str[65];
	अक्षर block_name[33];
	अक्षर err[9] = "ue";
	पूर्णांक op = -1;
	पूर्णांक block_id;
	uपूर्णांक32_t sub_block;
	u64 address, value;

	अगर (*pos)
		वापस -EINVAL;
	*pos = size;

	स_रखो(str, 0, माप(str));
	स_रखो(data, 0, माप(*data));

	अगर (copy_from_user(str, buf, s))
		वापस -EINVAL;

	अगर (माला_पूछो(str, "disable %32s", block_name) == 1)
		op = 0;
	अन्यथा अगर (माला_पूछो(str, "enable %32s %8s", block_name, err) == 2)
		op = 1;
	अन्यथा अगर (माला_पूछो(str, "inject %32s %8s", block_name, err) == 2)
		op = 2;
	अन्यथा अगर (म_माला(str, "retire_page") != शून्य)
		op = 3;
	अन्यथा अगर (str[0] && str[1] && str[2] && str[3])
		/* ascii string, but commands are not matched. */
		वापस -EINVAL;

	अगर (op != -1) अणु
		अगर (op == 3) अणु
			अगर (माला_पूछो(str, "%*s 0x%llx", &address) != 1 &&
			    माला_पूछो(str, "%*s %llu", &address) != 1)
				वापस -EINVAL;

			data->op = op;
			data->inject.address = address;

			वापस 0;
		पूर्ण

		अगर (amdgpu_ras_find_block_id_by_name(block_name, &block_id))
			वापस -EINVAL;

		data->head.block = block_id;
		/* only ue and ce errors are supported */
		अगर (!स_भेद("ue", err, 2))
			data->head.type = AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE;
		अन्यथा अगर (!स_भेद("ce", err, 2))
			data->head.type = AMDGPU_RAS_ERROR__SINGLE_CORRECTABLE;
		अन्यथा
			वापस -EINVAL;

		data->op = op;

		अगर (op == 2) अणु
			अगर (माला_पूछो(str, "%*s %*s %*s 0x%x 0x%llx 0x%llx",
				   &sub_block, &address, &value) != 3 &&
			    माला_पूछो(str, "%*s %*s %*s %u %llu %llu",
				   &sub_block, &address, &value) != 3)
				वापस -EINVAL;
			data->head.sub_block_index = sub_block;
			data->inject.address = address;
			data->inject.value = value;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (size < माप(*data))
			वापस -EINVAL;

		अगर (copy_from_user(data, buf, माप(*data)))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * DOC: AMDGPU RAS debugfs control पूर्णांकerface
 *
 * The control पूर्णांकerface accepts काष्ठा ras_debug_अगर which has two members.
 *
 * First member: ras_debug_अगर::head or ras_debug_अगर::inject.
 *
 * head is used to indicate which IP block will be under control.
 *
 * head has four members, they are block, type, sub_block_index, name.
 * block: which IP will be under control.
 * type: what kind of error will be enabled/disabled/injected.
 * sub_block_index: some IPs have subcomponets. say, GFX, sDMA.
 * name: the name of IP.
 *
 * inject has two more members than head, they are address, value.
 * As their names indicate, inject operation will ग_लिखो the
 * value to the address.
 *
 * The second member: काष्ठा ras_debug_अगर::op.
 * It has three kinds of operations.
 *
 * - 0: disable RAS on the block. Take ::head as its data.
 * - 1: enable RAS on the block. Take ::head as its data.
 * - 2: inject errors on the block. Take ::inject as its data.
 *
 * How to use the पूर्णांकerface?
 *
 * In a program
 *
 * Copy the काष्ठा ras_debug_अगर in your code and initialize it.
 * Write the काष्ठा to the control पूर्णांकerface.
 *
 * From shell
 *
 * .. code-block:: bash
 *
 *	echo "disable <block>" > /sys/kernel/debug/dri/<N>/ras/ras_ctrl
 *	echo "enable  <block> <error>" > /sys/kernel/debug/dri/<N>/ras/ras_ctrl
 *	echo "inject  <block> <error> <sub-block> <address> <value> > /sys/kernel/debug/dri/<N>/ras/ras_ctrl
 *
 * Where N, is the card which you want to affect.
 *
 * "disable" requires only the block.
 * "enable" requires the block and error type.
 * "inject" requires the block, error type, address, and value.
 * The block is one of: umc, sdma, gfx, etc.
 *	see ras_block_string[] क्रम details
 * The error type is one of: ue, ce, where,
 *	ue is multi-uncorrectable
 *	ce is single-correctable
 * The sub-block is a the sub-block index, pass 0 अगर there is no sub-block.
 * The address and value are hexadecimal numbers, leading 0x is optional.
 *
 * For instance,
 *
 * .. code-block:: bash
 *
 *	echo inject umc ue 0x0 0x0 0x0 > /sys/kernel/debug/dri/0/ras/ras_ctrl
 *	echo inject umc ce 0 0 0 > /sys/kernel/debug/dri/0/ras/ras_ctrl
 *	echo disable umc > /sys/kernel/debug/dri/0/ras/ras_ctrl
 *
 * How to check the result of the operation?
 *
 * To check disable/enable, see "ras" features at,
 * /sys/class/drm/card[0/1/2...]/device/ras/features
 *
 * To check inject, see the corresponding error count at,
 * /sys/class/drm/card[0/1/2...]/device/ras/[gfx|sdma|umc|...]_err_count
 *
 * .. note::
 *	Operations are only allowed on blocks which are supported.
 *	Check the "ras" mask at /sys/module/amdgpu/parameters/ras_mask
 *	to see which blocks support RAS on a particular asic.
 *
 */
अटल sमाप_प्रकार amdgpu_ras_debugfs_ctrl_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
		माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)file_inode(f)->i_निजी;
	काष्ठा ras_debug_अगर data;
	पूर्णांक ret = 0;

	अगर (!amdgpu_ras_get_error_query_पढ़ोy(adev)) अणु
		dev_warn(adev->dev, "RAS WARN: error injection "
				"currently inaccessible\n");
		वापस size;
	पूर्ण

	ret = amdgpu_ras_debugfs_ctrl_parse_data(f, buf, size, pos, &data);
	अगर (ret)
		वापस -EINVAL;

	अगर (data.op == 3) अणु
		ret = amdgpu_reserve_page_direct(adev, data.inject.address);
		अगर (!ret)
			वापस size;
		अन्यथा
			वापस ret;
	पूर्ण

	अगर (!amdgpu_ras_is_supported(adev, data.head.block))
		वापस -EINVAL;

	चयन (data.op) अणु
	हाल 0:
		ret = amdgpu_ras_feature_enable(adev, &data.head, 0);
		अवरोध;
	हाल 1:
		ret = amdgpu_ras_feature_enable(adev, &data.head, 1);
		अवरोध;
	हाल 2:
		अगर ((data.inject.address >= adev->gmc.mc_vram_size) ||
		    (data.inject.address >= RAS_UMC_INJECT_ADDR_LIMIT)) अणु
			dev_warn(adev->dev, "RAS WARN: input address "
					"0x%llx is invalid.",
					data.inject.address);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/* umc ce/ue error injection क्रम a bad page is not allowed */
		अगर ((data.head.block == AMDGPU_RAS_BLOCK__UMC) &&
		    amdgpu_ras_check_bad_page(adev, data.inject.address)) अणु
			dev_warn(adev->dev, "RAS WARN: 0x%llx has been marked "
					"as bad before error injection!\n",
					data.inject.address);
			अवरोध;
		पूर्ण

		/* data.inject.address is offset instead of असलolute gpu address */
		ret = amdgpu_ras_error_inject(adev, &data.inject);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस -EINVAL;

	वापस size;
पूर्ण

/**
 * DOC: AMDGPU RAS debugfs EEPROM table reset पूर्णांकerface
 *
 * Some boards contain an EEPROM which is used to persistently store a list of
 * bad pages which experiences ECC errors in vram.  This पूर्णांकerface provides
 * a way to reset the EEPROM, e.g., after testing error injection.
 *
 * Usage:
 *
 * .. code-block:: bash
 *
 *	echo 1 > ../ras/ras_eeprom_reset
 *
 * will reset EEPROM table to 0 entries.
 *
 */
अटल sमाप_प्रकार amdgpu_ras_debugfs_eeprom_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
		माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev =
		(काष्ठा amdgpu_device *)file_inode(f)->i_निजी;
	पूर्णांक ret;

	ret = amdgpu_ras_eeprom_reset_table(
			&(amdgpu_ras_get_context(adev)->eeprom_control));

	अगर (ret == 1) अणु
		amdgpu_ras_get_context(adev)->flags = RAS_DEFAULT_FLAGS;
		वापस size;
	पूर्ण अन्यथा अणु
		वापस -EIO;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations amdgpu_ras_debugfs_ctrl_ops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = शून्य,
	.ग_लिखो = amdgpu_ras_debugfs_ctrl_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

अटल स्थिर काष्ठा file_operations amdgpu_ras_debugfs_eeprom_ops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = शून्य,
	.ग_लिखो = amdgpu_ras_debugfs_eeprom_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

/**
 * DOC: AMDGPU RAS sysfs Error Count Interface
 *
 * It allows the user to पढ़ो the error count क्रम each IP block on the gpu through
 * /sys/class/drm/card[0/1/2...]/device/ras/[gfx/sdma/...]_err_count
 *
 * It outमाला_दो the multiple lines which report the uncorrected (ue) and corrected
 * (ce) error counts.
 *
 * The क्रमmat of one line is below,
 *
 * [ce|ue]: count
 *
 * Example:
 *
 * .. code-block:: bash
 *
 *	ue: 0
 *	ce: 1
 *
 */
अटल sमाप_प्रकार amdgpu_ras_sysfs_पढ़ो(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ras_manager *obj = container_of(attr, काष्ठा ras_manager, sysfs_attr);
	काष्ठा ras_query_अगर info = अणु
		.head = obj->head,
	पूर्ण;

	अगर (!amdgpu_ras_get_error_query_पढ़ोy(obj->adev))
		वापस sysfs_emit(buf, "Query currently inaccessible\n");

	अगर (amdgpu_ras_query_error_status(obj->adev, &info))
		वापस -EINVAL;


	अगर (obj->adev->asic_type == CHIP_ALDEBARAN) अणु
		अगर (amdgpu_ras_reset_error_status(obj->adev, info.head.block))
			DRM_WARN("Failed to reset error counter and error status");
	पूर्ण

	वापस sysfs_emit(buf, "%s: %lu\n%s: %lu\n", "ue", info.ue_count,
			  "ce", info.ce_count);
पूर्ण

/* obj begin */

#घोषणा get_obj(obj) करो अणु (obj)->use++; पूर्ण जबतक (0)
#घोषणा alive_obj(obj) ((obj)->use)

अटल अंतरभूत व्योम put_obj(काष्ठा ras_manager *obj)
अणु
	अगर (obj && (--obj->use == 0))
		list_del(&obj->node);
	अगर (obj && (obj->use < 0))
		DRM_ERROR("RAS ERROR: Unbalance obj(%s) use\n", obj->head.name);
पूर्ण

/* make one obj and वापस it. */
अटल काष्ठा ras_manager *amdgpu_ras_create_obj(काष्ठा amdgpu_device *adev,
		काष्ठा ras_common_अगर *head)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_manager *obj;

	अगर (!adev->ras_features || !con)
		वापस शून्य;

	अगर (head->block >= AMDGPU_RAS_BLOCK_COUNT)
		वापस शून्य;

	obj = &con->objs[head->block];
	/* alपढ़ोy exist. वापस obj? */
	अगर (alive_obj(obj))
		वापस शून्य;

	obj->head = *head;
	obj->adev = adev;
	list_add(&obj->node, &con->head);
	get_obj(obj);

	वापस obj;
पूर्ण

/* वापस an obj equal to head, or the first when head is शून्य */
काष्ठा ras_manager *amdgpu_ras_find_obj(काष्ठा amdgpu_device *adev,
		काष्ठा ras_common_अगर *head)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_manager *obj;
	पूर्णांक i;

	अगर (!adev->ras_features || !con)
		वापस शून्य;

	अगर (head) अणु
		अगर (head->block >= AMDGPU_RAS_BLOCK_COUNT)
			वापस शून्य;

		obj = &con->objs[head->block];

		अगर (alive_obj(obj)) अणु
			WARN_ON(head->block != obj->head.block);
			वापस obj;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < AMDGPU_RAS_BLOCK_COUNT; i++) अणु
			obj = &con->objs[i];
			अगर (alive_obj(obj)) अणु
				WARN_ON(i != obj->head.block);
				वापस obj;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
/* obj end */

अटल व्योम amdgpu_ras_parse_status_code(काष्ठा amdgpu_device *adev,
					 स्थिर अक्षर* invoke_type,
					 स्थिर अक्षर* block_name,
					 क्रमागत ta_ras_status ret)
अणु
	चयन (ret) अणु
	हाल TA_RAS_STATUS__SUCCESS:
		वापस;
	हाल TA_RAS_STATUS__ERROR_RAS_NOT_AVAILABLE:
		dev_warn(adev->dev,
			"RAS WARN: %s %s currently unavailable\n",
			invoke_type,
			block_name);
		अवरोध;
	शेष:
		dev_err(adev->dev,
			"RAS ERROR: %s %s error failed ret 0x%X\n",
			invoke_type,
			block_name,
			ret);
	पूर्ण
पूर्ण

/* feature ctl begin */
अटल पूर्णांक amdgpu_ras_is_feature_allowed(काष्ठा amdgpu_device *adev,
		काष्ठा ras_common_अगर *head)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);

	वापस con->hw_supported & BIT(head->block);
पूर्ण

अटल पूर्णांक amdgpu_ras_is_feature_enabled(काष्ठा amdgpu_device *adev,
		काष्ठा ras_common_अगर *head)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);

	वापस con->features & BIT(head->block);
पूर्ण

/*
 * अगर obj is not created, then create one.
 * set feature enable flag.
 */
अटल पूर्णांक __amdgpu_ras_feature_enable(काष्ठा amdgpu_device *adev,
		काष्ठा ras_common_अगर *head, पूर्णांक enable)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_manager *obj = amdgpu_ras_find_obj(adev, head);

	/* If hardware करोes not support ras, then करो not create obj.
	 * But अगर hardware support ras, we can create the obj.
	 * Ras framework checks con->hw_supported to see अगर it need करो
	 * corresponding initialization.
	 * IP checks con->support to see अगर it need disable ras.
	 */
	अगर (!amdgpu_ras_is_feature_allowed(adev, head))
		वापस 0;
	अगर (!(!!enable ^ !!amdgpu_ras_is_feature_enabled(adev, head)))
		वापस 0;

	अगर (enable) अणु
		अगर (!obj) अणु
			obj = amdgpu_ras_create_obj(adev, head);
			अगर (!obj)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			/* In हाल we create obj somewhere अन्यथा */
			get_obj(obj);
		पूर्ण
		con->features |= BIT(head->block);
	पूर्ण अन्यथा अणु
		अगर (obj && amdgpu_ras_is_feature_enabled(adev, head)) अणु
			/* skip clean gfx ras context feature क्रम VEGA20 Gaming.
			 * will clean later
			 */
			अगर (!(!adev->ras_features && con->features & BIT(AMDGPU_RAS_BLOCK__GFX)))
				con->features &= ~BIT(head->block);
			put_obj(obj);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* wrapper of psp_ras_enable_features */
पूर्णांक amdgpu_ras_feature_enable(काष्ठा amdgpu_device *adev,
		काष्ठा ras_common_अगर *head, bool enable)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	जोड़ ta_ras_cmd_input *info;
	पूर्णांक ret;

	अगर (!con)
		वापस -EINVAL;

	info = kzalloc(माप(जोड़ ta_ras_cmd_input), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	अगर (!enable) अणु
		info->disable_features = (काष्ठा ta_ras_disable_features_input) अणु
			.block_id =  amdgpu_ras_block_to_ta(head->block),
			.error_type = amdgpu_ras_error_to_ta(head->type),
		पूर्ण;
	पूर्ण अन्यथा अणु
		info->enable_features = (काष्ठा ta_ras_enable_features_input) अणु
			.block_id =  amdgpu_ras_block_to_ta(head->block),
			.error_type = amdgpu_ras_error_to_ta(head->type),
		पूर्ण;
	पूर्ण

	/* Do not enable अगर it is not allowed. */
	WARN_ON(enable && !amdgpu_ras_is_feature_allowed(adev, head));
	/* Are we alerady in that state we are going to set? */
	अगर (!(!!enable ^ !!amdgpu_ras_is_feature_enabled(adev, head))) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (!amdgpu_ras_पूर्णांकr_triggered()) अणु
		ret = psp_ras_enable_features(&adev->psp, info, enable);
		अगर (ret) अणु
			amdgpu_ras_parse_status_code(adev,
						     enable ? "enable":"disable",
						     ras_block_str(head->block),
						    (क्रमागत ta_ras_status)ret);
			अगर (ret == TA_RAS_STATUS__RESET_NEEDED)
				ret = -EAGAIN;
			अन्यथा
				ret = -EINVAL;

			जाओ out;
		पूर्ण
	पूर्ण

	/* setup the obj */
	__amdgpu_ras_feature_enable(adev, head, enable);
	ret = 0;
out:
	kमुक्त(info);
	वापस ret;
पूर्ण

/* Only used in device probe stage and called only once. */
पूर्णांक amdgpu_ras_feature_enable_on_boot(काष्ठा amdgpu_device *adev,
		काष्ठा ras_common_अगर *head, bool enable)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	पूर्णांक ret;

	अगर (!con)
		वापस -EINVAL;

	अगर (con->flags & AMDGPU_RAS_FLAG_INIT_BY_VBIOS) अणु
		अगर (enable) अणु
			/* There is no harm to issue a ras TA cmd regardless of
			 * the currecnt ras state.
			 * If current state == target state, it will करो nothing
			 * But someबार it requests driver to reset and repost
			 * with error code -EAGAIN.
			 */
			ret = amdgpu_ras_feature_enable(adev, head, 1);
			/* With old ras TA, we might fail to enable ras.
			 * Log it and just setup the object.
			 * TODO need हटाओ this WA in the future.
			 */
			अगर (ret == -EINVAL) अणु
				ret = __amdgpu_ras_feature_enable(adev, head, 1);
				अगर (!ret)
					dev_info(adev->dev,
						"RAS INFO: %s setup object\n",
						ras_block_str(head->block));
			पूर्ण
		पूर्ण अन्यथा अणु
			/* setup the object then issue a ras TA disable cmd.*/
			ret = __amdgpu_ras_feature_enable(adev, head, 1);
			अगर (ret)
				वापस ret;

			/* gfx block ras dsiable cmd must send to ras-ta */
			अगर (head->block == AMDGPU_RAS_BLOCK__GFX)
				con->features |= BIT(head->block);

			ret = amdgpu_ras_feature_enable(adev, head, 0);
		पूर्ण
	पूर्ण अन्यथा
		ret = amdgpu_ras_feature_enable(adev, head, enable);

	वापस ret;
पूर्ण

अटल पूर्णांक amdgpu_ras_disable_all_features(काष्ठा amdgpu_device *adev,
		bool bypass)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_manager *obj, *पंचांगp;

	list_क्रम_each_entry_safe(obj, पंचांगp, &con->head, node) अणु
		/* bypass psp.
		 * aka just release the obj and corresponding flags
		 */
		अगर (bypass) अणु
			अगर (__amdgpu_ras_feature_enable(adev, &obj->head, 0))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (amdgpu_ras_feature_enable(adev, &obj->head, 0))
				अवरोध;
		पूर्ण
	पूर्ण

	वापस con->features;
पूर्ण

अटल पूर्णांक amdgpu_ras_enable_all_features(काष्ठा amdgpu_device *adev,
		bool bypass)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	पूर्णांक ras_block_count = AMDGPU_RAS_BLOCK_COUNT;
	पूर्णांक i;
	स्थिर क्रमागत amdgpu_ras_error_type शेष_ras_type =
		AMDGPU_RAS_ERROR__NONE;

	क्रम (i = 0; i < ras_block_count; i++) अणु
		काष्ठा ras_common_अगर head = अणु
			.block = i,
			.type = शेष_ras_type,
			.sub_block_index = 0,
		पूर्ण;
		म_नकल(head.name, ras_block_str(i));
		अगर (bypass) अणु
			/*
			 * bypass psp. vbios enable ras क्रम us.
			 * so just create the obj
			 */
			अगर (__amdgpu_ras_feature_enable(adev, &head, 1))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (amdgpu_ras_feature_enable(adev, &head, 1))
				अवरोध;
		पूर्ण
	पूर्ण

	वापस con->features;
पूर्ण
/* feature ctl end */

/* query/inject/cure begin */
पूर्णांक amdgpu_ras_query_error_status(काष्ठा amdgpu_device *adev,
	काष्ठा ras_query_अगर *info)
अणु
	काष्ठा ras_manager *obj = amdgpu_ras_find_obj(adev, &info->head);
	काष्ठा ras_err_data err_data = अणु0, 0, 0, शून्यपूर्ण;
	पूर्णांक i;

	अगर (!obj)
		वापस -EINVAL;

	चयन (info->head.block) अणु
	हाल AMDGPU_RAS_BLOCK__UMC:
		अगर (adev->umc.ras_funcs &&
		    adev->umc.ras_funcs->query_ras_error_count)
			adev->umc.ras_funcs->query_ras_error_count(adev, &err_data);
		/* umc query_ras_error_address is also responsible क्रम clearing
		 * error status
		 */
		अगर (adev->umc.ras_funcs &&
		    adev->umc.ras_funcs->query_ras_error_address)
			adev->umc.ras_funcs->query_ras_error_address(adev, &err_data);
		अवरोध;
	हाल AMDGPU_RAS_BLOCK__SDMA:
		अगर (adev->sdma.funcs->query_ras_error_count) अणु
			क्रम (i = 0; i < adev->sdma.num_instances; i++)
				adev->sdma.funcs->query_ras_error_count(adev, i,
									&err_data);
		पूर्ण
		अवरोध;
	हाल AMDGPU_RAS_BLOCK__GFX:
		अगर (adev->gfx.ras_funcs &&
		    adev->gfx.ras_funcs->query_ras_error_count)
			adev->gfx.ras_funcs->query_ras_error_count(adev, &err_data);

		अगर (adev->gfx.ras_funcs &&
		    adev->gfx.ras_funcs->query_ras_error_status)
			adev->gfx.ras_funcs->query_ras_error_status(adev);
		अवरोध;
	हाल AMDGPU_RAS_BLOCK__MMHUB:
		अगर (adev->mmhub.ras_funcs &&
		    adev->mmhub.ras_funcs->query_ras_error_count)
			adev->mmhub.ras_funcs->query_ras_error_count(adev, &err_data);

		अगर (adev->mmhub.ras_funcs &&
		    adev->mmhub.ras_funcs->query_ras_error_status)
			adev->mmhub.ras_funcs->query_ras_error_status(adev);
		अवरोध;
	हाल AMDGPU_RAS_BLOCK__PCIE_BIF:
		अगर (adev->nbio.ras_funcs &&
		    adev->nbio.ras_funcs->query_ras_error_count)
			adev->nbio.ras_funcs->query_ras_error_count(adev, &err_data);
		अवरोध;
	हाल AMDGPU_RAS_BLOCK__XGMI_WAFL:
		अगर (adev->gmc.xgmi.ras_funcs &&
		    adev->gmc.xgmi.ras_funcs->query_ras_error_count)
			adev->gmc.xgmi.ras_funcs->query_ras_error_count(adev, &err_data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	obj->err_data.ue_count += err_data.ue_count;
	obj->err_data.ce_count += err_data.ce_count;

	info->ue_count = obj->err_data.ue_count;
	info->ce_count = obj->err_data.ce_count;

	अगर (err_data.ce_count) अणु
		dev_info(adev->dev, "%ld correctable hardware errors "
					"detected in %s block, no user "
					"action is needed.\n",
					obj->err_data.ce_count,
					ras_block_str(info->head.block));
	पूर्ण
	अगर (err_data.ue_count) अणु
		dev_info(adev->dev, "%ld uncorrectable hardware errors "
					"detected in %s block\n",
					obj->err_data.ue_count,
					ras_block_str(info->head.block));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक amdgpu_ras_reset_error_status(काष्ठा amdgpu_device *adev,
		क्रमागत amdgpu_ras_block block)
अणु
	अगर (!amdgpu_ras_is_supported(adev, block))
		वापस -EINVAL;

	चयन (block) अणु
	हाल AMDGPU_RAS_BLOCK__GFX:
		अगर (adev->gfx.ras_funcs &&
		    adev->gfx.ras_funcs->reset_ras_error_count)
			adev->gfx.ras_funcs->reset_ras_error_count(adev);

		अगर (adev->gfx.ras_funcs &&
		    adev->gfx.ras_funcs->reset_ras_error_status)
			adev->gfx.ras_funcs->reset_ras_error_status(adev);
		अवरोध;
	हाल AMDGPU_RAS_BLOCK__MMHUB:
		अगर (adev->mmhub.ras_funcs &&
		    adev->mmhub.ras_funcs->reset_ras_error_count)
			adev->mmhub.ras_funcs->reset_ras_error_count(adev);
		अवरोध;
	हाल AMDGPU_RAS_BLOCK__SDMA:
		अगर (adev->sdma.funcs->reset_ras_error_count)
			adev->sdma.funcs->reset_ras_error_count(adev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Trigger XGMI/WAFL error */
अटल पूर्णांक amdgpu_ras_error_inject_xgmi(काष्ठा amdgpu_device *adev,
				 काष्ठा ta_ras_trigger_error_input *block_info)
अणु
	पूर्णांक ret;

	अगर (amdgpu_dpm_set_df_cstate(adev, DF_CSTATE_DISALLOW))
		dev_warn(adev->dev, "Failed to disallow df cstate");

	अगर (amdgpu_dpm_allow_xgmi_घातer_करोwn(adev, false))
		dev_warn(adev->dev, "Failed to disallow XGMI power down");

	ret = psp_ras_trigger_error(&adev->psp, block_info);

	अगर (amdgpu_ras_पूर्णांकr_triggered())
		वापस ret;

	अगर (amdgpu_dpm_allow_xgmi_घातer_करोwn(adev, true))
		dev_warn(adev->dev, "Failed to allow XGMI power down");

	अगर (amdgpu_dpm_set_df_cstate(adev, DF_CSTATE_ALLOW))
		dev_warn(adev->dev, "Failed to allow df cstate");

	वापस ret;
पूर्ण

/* wrapper of psp_ras_trigger_error */
पूर्णांक amdgpu_ras_error_inject(काष्ठा amdgpu_device *adev,
		काष्ठा ras_inject_अगर *info)
अणु
	काष्ठा ras_manager *obj = amdgpu_ras_find_obj(adev, &info->head);
	काष्ठा ta_ras_trigger_error_input block_info = अणु
		.block_id =  amdgpu_ras_block_to_ta(info->head.block),
		.inject_error_type = amdgpu_ras_error_to_ta(info->head.type),
		.sub_block_index = info->head.sub_block_index,
		.address = info->address,
		.value = info->value,
	पूर्ण;
	पूर्णांक ret = 0;

	अगर (!obj)
		वापस -EINVAL;

	/* Calculate XGMI relative offset */
	अगर (adev->gmc.xgmi.num_physical_nodes > 1) अणु
		block_info.address =
			amdgpu_xgmi_get_relative_phy_addr(adev,
							  block_info.address);
	पूर्ण

	चयन (info->head.block) अणु
	हाल AMDGPU_RAS_BLOCK__GFX:
		अगर (adev->gfx.ras_funcs &&
		    adev->gfx.ras_funcs->ras_error_inject)
			ret = adev->gfx.ras_funcs->ras_error_inject(adev, info);
		अन्यथा
			ret = -EINVAL;
		अवरोध;
	हाल AMDGPU_RAS_BLOCK__UMC:
	हाल AMDGPU_RAS_BLOCK__SDMA:
	हाल AMDGPU_RAS_BLOCK__MMHUB:
	हाल AMDGPU_RAS_BLOCK__PCIE_BIF:
		ret = psp_ras_trigger_error(&adev->psp, &block_info);
		अवरोध;
	हाल AMDGPU_RAS_BLOCK__XGMI_WAFL:
		ret = amdgpu_ras_error_inject_xgmi(adev, &block_info);
		अवरोध;
	शेष:
		dev_info(adev->dev, "%s error injection is not supported yet\n",
			 ras_block_str(info->head.block));
		ret = -EINVAL;
	पूर्ण

	amdgpu_ras_parse_status_code(adev,
				     "inject",
				     ras_block_str(info->head.block),
				     (क्रमागत ta_ras_status)ret);

	वापस ret;
पूर्ण

/* get the total error counts on all IPs */
अचिन्हित दीर्घ amdgpu_ras_query_error_count(काष्ठा amdgpu_device *adev,
		bool is_ce)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_manager *obj;
	काष्ठा ras_err_data data = अणु0, 0पूर्ण;

	अगर (!adev->ras_features || !con)
		वापस 0;

	list_क्रम_each_entry(obj, &con->head, node) अणु
		काष्ठा ras_query_अगर info = अणु
			.head = obj->head,
		पूर्ण;

		अगर (amdgpu_ras_query_error_status(adev, &info))
			वापस 0;

		data.ce_count += info.ce_count;
		data.ue_count += info.ue_count;
	पूर्ण

	वापस is_ce ? data.ce_count : data.ue_count;
पूर्ण
/* query/inject/cure end */


/* sysfs begin */

अटल पूर्णांक amdgpu_ras_badpages_पढ़ो(काष्ठा amdgpu_device *adev,
		काष्ठा ras_badpage **bps, अचिन्हित पूर्णांक *count);

अटल अक्षर *amdgpu_ras_badpage_flags_str(अचिन्हित पूर्णांक flags)
अणु
	चयन (flags) अणु
	हाल AMDGPU_RAS_RETIRE_PAGE_RESERVED:
		वापस "R";
	हाल AMDGPU_RAS_RETIRE_PAGE_PENDING:
		वापस "P";
	हाल AMDGPU_RAS_RETIRE_PAGE_FAULT:
	शेष:
		वापस "F";
	पूर्ण
पूर्ण

/**
 * DOC: AMDGPU RAS sysfs gpu_vram_bad_pages Interface
 *
 * It allows user to पढ़ो the bad pages of vram on the gpu through
 * /sys/class/drm/card[0/1/2...]/device/ras/gpu_vram_bad_pages
 *
 * It outमाला_दो multiple lines, and each line stands क्रम one gpu page.
 *
 * The क्रमmat of one line is below,
 * gpu pfn : gpu page size : flags
 *
 * gpu pfn and gpu page size are prपूर्णांकed in hex क्रमmat.
 * flags can be one of below अक्षरacter,
 *
 * R: reserved, this gpu page is reserved and not able to use.
 *
 * P: pending क्रम reserve, this gpu page is marked as bad, will be reserved
 * in next winकरोw of page_reserve.
 *
 * F: unable to reserve. this gpu page can't be reserved due to some reasons.
 *
 * Examples:
 *
 * .. code-block:: bash
 *
 *	0x00000001 : 0x00001000 : R
 *	0x00000002 : 0x00001000 : P
 *
 */

अटल sमाप_प्रकार amdgpu_ras_sysfs_badpages_पढ़ो(काष्ठा file *f,
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr,
		अक्षर *buf, loff_t ppos, माप_प्रकार count)
अणु
	काष्ठा amdgpu_ras *con =
		container_of(attr, काष्ठा amdgpu_ras, badpages_attr);
	काष्ठा amdgpu_device *adev = con->adev;
	स्थिर अचिन्हित पूर्णांक element_size =
		माप("0xabcdabcd : 0x12345678 : R\n") - 1;
	अचिन्हित पूर्णांक start = भाग64_ul(ppos + element_size - 1, element_size);
	अचिन्हित पूर्णांक end = भाग64_ul(ppos + count - 1, element_size);
	sमाप_प्रकार s = 0;
	काष्ठा ras_badpage *bps = शून्य;
	अचिन्हित पूर्णांक bps_count = 0;

	स_रखो(buf, 0, count);

	अगर (amdgpu_ras_badpages_पढ़ो(adev, &bps, &bps_count))
		वापस 0;

	क्रम (; start < end && start < bps_count; start++)
		s += scnम_लिखो(&buf[s], element_size + 1,
				"0x%08x : 0x%08x : %1s\n",
				bps[start].bp,
				bps[start].size,
				amdgpu_ras_badpage_flags_str(bps[start].flags));

	kमुक्त(bps);

	वापस s;
पूर्ण

अटल sमाप_प्रकार amdgpu_ras_sysfs_features_पढ़ो(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा amdgpu_ras *con =
		container_of(attr, काष्ठा amdgpu_ras, features_attr);

	वापस scnम_लिखो(buf, PAGE_SIZE, "feature mask: 0x%x\n", con->features);
पूर्ण

अटल व्योम amdgpu_ras_sysfs_हटाओ_bad_page_node(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);

	sysfs_हटाओ_file_from_group(&adev->dev->kobj,
				&con->badpages_attr.attr,
				RAS_FS_NAME);
पूर्ण

अटल पूर्णांक amdgpu_ras_sysfs_हटाओ_feature_node(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा attribute *attrs[] = अणु
		&con->features_attr.attr,
		शून्य
	पूर्ण;
	काष्ठा attribute_group group = अणु
		.name = RAS_FS_NAME,
		.attrs = attrs,
	पूर्ण;

	sysfs_हटाओ_group(&adev->dev->kobj, &group);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_ras_sysfs_create(काष्ठा amdgpu_device *adev,
		काष्ठा ras_fs_अगर *head)
अणु
	काष्ठा ras_manager *obj = amdgpu_ras_find_obj(adev, &head->head);

	अगर (!obj || obj->attr_inuse)
		वापस -EINVAL;

	get_obj(obj);

	स_नकल(obj->fs_data.sysfs_name,
			head->sysfs_name,
			माप(obj->fs_data.sysfs_name));

	obj->sysfs_attr = (काष्ठा device_attribute)अणु
		.attr = अणु
			.name = obj->fs_data.sysfs_name,
			.mode = S_IRUGO,
		पूर्ण,
			.show = amdgpu_ras_sysfs_पढ़ो,
	पूर्ण;
	sysfs_attr_init(&obj->sysfs_attr.attr);

	अगर (sysfs_add_file_to_group(&adev->dev->kobj,
				&obj->sysfs_attr.attr,
				RAS_FS_NAME)) अणु
		put_obj(obj);
		वापस -EINVAL;
	पूर्ण

	obj->attr_inuse = 1;

	वापस 0;
पूर्ण

पूर्णांक amdgpu_ras_sysfs_हटाओ(काष्ठा amdgpu_device *adev,
		काष्ठा ras_common_अगर *head)
अणु
	काष्ठा ras_manager *obj = amdgpu_ras_find_obj(adev, head);

	अगर (!obj || !obj->attr_inuse)
		वापस -EINVAL;

	sysfs_हटाओ_file_from_group(&adev->dev->kobj,
				&obj->sysfs_attr.attr,
				RAS_FS_NAME);
	obj->attr_inuse = 0;
	put_obj(obj);

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_ras_sysfs_हटाओ_all(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_manager *obj, *पंचांगp;

	list_क्रम_each_entry_safe(obj, पंचांगp, &con->head, node) अणु
		amdgpu_ras_sysfs_हटाओ(adev, &obj->head);
	पूर्ण

	अगर (amdgpu_bad_page_threshold != 0)
		amdgpu_ras_sysfs_हटाओ_bad_page_node(adev);

	amdgpu_ras_sysfs_हटाओ_feature_node(adev);

	वापस 0;
पूर्ण
/* sysfs end */

/**
 * DOC: AMDGPU RAS Reboot Behavior क्रम Unrecoverable Errors
 *
 * Normally when there is an uncorrectable error, the driver will reset
 * the GPU to recover.  However, in the event of an unrecoverable error,
 * the driver provides an पूर्णांकerface to reboot the प्रणाली स्वतःmatically
 * in that event.
 *
 * The following file in debugfs provides that पूर्णांकerface:
 * /sys/kernel/debug/dri/[0/1/2...]/ras/स्वतः_reboot
 *
 * Usage:
 *
 * .. code-block:: bash
 *
 *	echo true > .../ras/स्वतः_reboot
 *
 */
/* debugfs begin */
अटल काष्ठा dentry *amdgpu_ras_debugfs_create_ctrl_node(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा dentry *dir;
	काष्ठा drm_minor *minor = adev_to_drm(adev)->primary;

	dir = debugfs_create_dir(RAS_FS_NAME, minor->debugfs_root);
	debugfs_create_file("ras_ctrl", S_IWUGO | S_IRUGO, dir, adev,
			    &amdgpu_ras_debugfs_ctrl_ops);
	debugfs_create_file("ras_eeprom_reset", S_IWUGO | S_IRUGO, dir, adev,
			    &amdgpu_ras_debugfs_eeprom_ops);
	debugfs_create_u32("bad_page_cnt_threshold", 0444, dir,
			   &con->bad_page_cnt_threshold);

	/*
	 * After one uncorrectable error happens, usually GPU recovery will
	 * be scheduled. But due to the known problem in GPU recovery failing
	 * to bring GPU back, below पूर्णांकerface provides one direct way to
	 * user to reboot प्रणाली स्वतःmatically in such हाल within
	 * ERREVENT_ATHUB_INTERRUPT generated. Normal GPU recovery routine
	 * will never be called.
	 */
	debugfs_create_bool("auto_reboot", S_IWUGO | S_IRUGO, dir, &con->reboot);

	/*
	 * User could set this not to clean up hardware's error count रेजिस्टर
	 * of RAS IPs during ras recovery.
	 */
	debugfs_create_bool("disable_ras_err_cnt_harvest", 0644, dir,
			    &con->disable_ras_err_cnt_harvest);
	वापस dir;
पूर्ण

अटल व्योम amdgpu_ras_debugfs_create(काष्ठा amdgpu_device *adev,
				      काष्ठा ras_fs_अगर *head,
				      काष्ठा dentry *dir)
अणु
	काष्ठा ras_manager *obj = amdgpu_ras_find_obj(adev, &head->head);

	अगर (!obj || !dir)
		वापस;

	get_obj(obj);

	स_नकल(obj->fs_data.debugfs_name,
			head->debugfs_name,
			माप(obj->fs_data.debugfs_name));

	debugfs_create_file(obj->fs_data.debugfs_name, S_IWUGO | S_IRUGO, dir,
			    obj, &amdgpu_ras_debugfs_ops);
पूर्ण

व्योम amdgpu_ras_debugfs_create_all(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा dentry *dir;
	काष्ठा ras_manager *obj;
	काष्ठा ras_fs_अगर fs_info;

	/*
	 * it won't be called in resume path, no need to check
	 * suspend and gpu reset status
	 */
	अगर (!IS_ENABLED(CONFIG_DEBUG_FS) || !con)
		वापस;

	dir = amdgpu_ras_debugfs_create_ctrl_node(adev);

	list_क्रम_each_entry(obj, &con->head, node) अणु
		अगर (amdgpu_ras_is_supported(adev, obj->head.block) &&
			(obj->attr_inuse == 1)) अणु
			प्र_लिखो(fs_info.debugfs_name, "%s_err_inject",
					ras_block_str(obj->head.block));
			fs_info.head = obj->head;
			amdgpu_ras_debugfs_create(adev, &fs_info, dir);
		पूर्ण
	पूर्ण
पूर्ण

/* debugfs end */

/* ras fs */
अटल BIN_ATTR(gpu_vram_bad_pages, S_IRUGO,
		amdgpu_ras_sysfs_badpages_पढ़ो, शून्य, 0);
अटल DEVICE_ATTR(features, S_IRUGO,
		amdgpu_ras_sysfs_features_पढ़ो, शून्य);
अटल पूर्णांक amdgpu_ras_fs_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा attribute_group group = अणु
		.name = RAS_FS_NAME,
	पूर्ण;
	काष्ठा attribute *attrs[] = अणु
		&con->features_attr.attr,
		शून्य
	पूर्ण;
	काष्ठा bin_attribute *bin_attrs[] = अणु
		शून्य,
		शून्य,
	पूर्ण;
	पूर्णांक r;

	/* add features entry */
	con->features_attr = dev_attr_features;
	group.attrs = attrs;
	sysfs_attr_init(attrs[0]);

	अगर (amdgpu_bad_page_threshold != 0) अणु
		/* add bad_page_features entry */
		bin_attr_gpu_vram_bad_pages.निजी = शून्य;
		con->badpages_attr = bin_attr_gpu_vram_bad_pages;
		bin_attrs[0] = &con->badpages_attr;
		group.bin_attrs = bin_attrs;
		sysfs_bin_attr_init(bin_attrs[0]);
	पूर्ण

	r = sysfs_create_group(&adev->dev->kobj, &group);
	अगर (r)
		dev_err(adev->dev, "Failed to create RAS sysfs group!");

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_ras_fs_fini(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_manager *con_obj, *ip_obj, *पंचांगp;

	अगर (IS_ENABLED(CONFIG_DEBUG_FS)) अणु
		list_क्रम_each_entry_safe(con_obj, पंचांगp, &con->head, node) अणु
			ip_obj = amdgpu_ras_find_obj(adev, &con_obj->head);
			अगर (ip_obj)
				put_obj(ip_obj);
		पूर्ण
	पूर्ण

	amdgpu_ras_sysfs_हटाओ_all(adev);
	वापस 0;
पूर्ण
/* ras fs end */

/* ih begin */
अटल व्योम amdgpu_ras_पूर्णांकerrupt_handler(काष्ठा ras_manager *obj)
अणु
	काष्ठा ras_ih_data *data = &obj->ih_data;
	काष्ठा amdgpu_iv_entry entry;
	पूर्णांक ret;
	काष्ठा ras_err_data err_data = अणु0, 0, 0, शून्यपूर्ण;

	जबतक (data->rptr != data->wptr) अणु
		rmb();
		स_नकल(&entry, &data->ring[data->rptr],
				data->element_size);

		wmb();
		data->rptr = (data->aligned_element_size +
				data->rptr) % data->ring_size;

		/* Let IP handle its data, maybe we need get the output
		 * from the callback to udpate the error type/count, etc
		 */
		अगर (data->cb) अणु
			ret = data->cb(obj->adev, &err_data, &entry);
			/* ue will trigger an पूर्णांकerrupt, and in that हाल
			 * we need करो a reset to recovery the whole प्रणाली.
			 * But leave IP करो that recovery, here we just dispatch
			 * the error.
			 */
			अगर (ret == AMDGPU_RAS_SUCCESS) अणु
				/* these counts could be left as 0 अगर
				 * some blocks करो not count error number
				 */
				obj->err_data.ue_count += err_data.ue_count;
				obj->err_data.ce_count += err_data.ce_count;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम amdgpu_ras_पूर्णांकerrupt_process_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ras_ih_data *data =
		container_of(work, काष्ठा ras_ih_data, ih_work);
	काष्ठा ras_manager *obj =
		container_of(data, काष्ठा ras_manager, ih_data);

	amdgpu_ras_पूर्णांकerrupt_handler(obj);
पूर्ण

पूर्णांक amdgpu_ras_पूर्णांकerrupt_dispatch(काष्ठा amdgpu_device *adev,
		काष्ठा ras_dispatch_अगर *info)
अणु
	काष्ठा ras_manager *obj = amdgpu_ras_find_obj(adev, &info->head);
	काष्ठा ras_ih_data *data = &obj->ih_data;

	अगर (!obj)
		वापस -EINVAL;

	अगर (data->inuse == 0)
		वापस 0;

	/* Might be overflow... */
	स_नकल(&data->ring[data->wptr], info->entry,
			data->element_size);

	wmb();
	data->wptr = (data->aligned_element_size +
			data->wptr) % data->ring_size;

	schedule_work(&data->ih_work);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_ras_पूर्णांकerrupt_हटाओ_handler(काष्ठा amdgpu_device *adev,
		काष्ठा ras_ih_अगर *info)
अणु
	काष्ठा ras_manager *obj = amdgpu_ras_find_obj(adev, &info->head);
	काष्ठा ras_ih_data *data;

	अगर (!obj)
		वापस -EINVAL;

	data = &obj->ih_data;
	अगर (data->inuse == 0)
		वापस 0;

	cancel_work_sync(&data->ih_work);

	kमुक्त(data->ring);
	स_रखो(data, 0, माप(*data));
	put_obj(obj);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_ras_पूर्णांकerrupt_add_handler(काष्ठा amdgpu_device *adev,
		काष्ठा ras_ih_अगर *info)
अणु
	काष्ठा ras_manager *obj = amdgpu_ras_find_obj(adev, &info->head);
	काष्ठा ras_ih_data *data;

	अगर (!obj) अणु
		/* in हाल we registe the IH beक्रमe enable ras feature */
		obj = amdgpu_ras_create_obj(adev, &info->head);
		अगर (!obj)
			वापस -EINVAL;
	पूर्ण अन्यथा
		get_obj(obj);

	data = &obj->ih_data;
	/* add the callback.etc */
	*data = (काष्ठा ras_ih_data) अणु
		.inuse = 0,
		.cb = info->cb,
		.element_size = माप(काष्ठा amdgpu_iv_entry),
		.rptr = 0,
		.wptr = 0,
	पूर्ण;

	INIT_WORK(&data->ih_work, amdgpu_ras_पूर्णांकerrupt_process_handler);

	data->aligned_element_size = ALIGN(data->element_size, 8);
	/* the ring can store 64 iv entries. */
	data->ring_size = 64 * data->aligned_element_size;
	data->ring = kदो_स्मृति(data->ring_size, GFP_KERNEL);
	अगर (!data->ring) अणु
		put_obj(obj);
		वापस -ENOMEM;
	पूर्ण

	/* IH is पढ़ोy */
	data->inuse = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_ras_पूर्णांकerrupt_हटाओ_all(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_manager *obj, *पंचांगp;

	list_क्रम_each_entry_safe(obj, पंचांगp, &con->head, node) अणु
		काष्ठा ras_ih_अगर info = अणु
			.head = obj->head,
		पूर्ण;
		amdgpu_ras_पूर्णांकerrupt_हटाओ_handler(adev, &info);
	पूर्ण

	वापस 0;
पूर्ण
/* ih end */

/* traversal all IPs except NBIO to query error counter */
अटल व्योम amdgpu_ras_log_on_err_counter(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_manager *obj;

	अगर (!adev->ras_features || !con)
		वापस;

	list_क्रम_each_entry(obj, &con->head, node) अणु
		काष्ठा ras_query_अगर info = अणु
			.head = obj->head,
		पूर्ण;

		/*
		 * PCIE_BIF IP has one dअगरferent isr by ras controller
		 * पूर्णांकerrupt, the specअगरic ras counter query will be
		 * करोne in that isr. So skip such block from common
		 * sync flood पूर्णांकerrupt isr calling.
		 */
		अगर (info.head.block == AMDGPU_RAS_BLOCK__PCIE_BIF)
			जारी;

		amdgpu_ras_query_error_status(adev, &info);
	पूर्ण
पूर्ण

/* Parse RdRspStatus and WrRspStatus */
अटल व्योम amdgpu_ras_error_status_query(काष्ठा amdgpu_device *adev,
					  काष्ठा ras_query_अगर *info)
अणु
	/*
	 * Only two block need to query पढ़ो/ग_लिखो
	 * RspStatus at current state
	 */
	चयन (info->head.block) अणु
	हाल AMDGPU_RAS_BLOCK__GFX:
		अगर (adev->gfx.ras_funcs &&
		    adev->gfx.ras_funcs->query_ras_error_status)
			adev->gfx.ras_funcs->query_ras_error_status(adev);
		अवरोध;
	हाल AMDGPU_RAS_BLOCK__MMHUB:
		अगर (adev->mmhub.ras_funcs &&
		    adev->mmhub.ras_funcs->query_ras_error_status)
			adev->mmhub.ras_funcs->query_ras_error_status(adev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम amdgpu_ras_query_err_status(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_manager *obj;

	अगर (!adev->ras_features || !con)
		वापस;

	list_क्रम_each_entry(obj, &con->head, node) अणु
		काष्ठा ras_query_अगर info = अणु
			.head = obj->head,
		पूर्ण;

		amdgpu_ras_error_status_query(adev, &info);
	पूर्ण
पूर्ण

/* recovery begin */

/* वापस 0 on success.
 * caller need मुक्त bps.
 */
अटल पूर्णांक amdgpu_ras_badpages_पढ़ो(काष्ठा amdgpu_device *adev,
		काष्ठा ras_badpage **bps, अचिन्हित पूर्णांक *count)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_err_handler_data *data;
	पूर्णांक i = 0;
	पूर्णांक ret = 0, status;

	अगर (!con || !con->eh_data || !bps || !count)
		वापस -EINVAL;

	mutex_lock(&con->recovery_lock);
	data = con->eh_data;
	अगर (!data || data->count == 0) अणु
		*bps = शून्य;
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	*bps = kदो_स्मृति(माप(काष्ठा ras_badpage) * data->count, GFP_KERNEL);
	अगर (!*bps) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (; i < data->count; i++) अणु
		(*bps)[i] = (काष्ठा ras_badpage)अणु
			.bp = data->bps[i].retired_page,
			.size = AMDGPU_GPU_PAGE_SIZE,
			.flags = AMDGPU_RAS_RETIRE_PAGE_RESERVED,
		पूर्ण;
		status = amdgpu_vram_mgr_query_page_status(
				tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM),
				data->bps[i].retired_page);
		अगर (status == -EBUSY)
			(*bps)[i].flags = AMDGPU_RAS_RETIRE_PAGE_PENDING;
		अन्यथा अगर (status == -ENOENT)
			(*bps)[i].flags = AMDGPU_RAS_RETIRE_PAGE_FAULT;
	पूर्ण

	*count = data->count;
out:
	mutex_unlock(&con->recovery_lock);
	वापस ret;
पूर्ण

अटल व्योम amdgpu_ras_करो_recovery(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_ras *ras =
		container_of(work, काष्ठा amdgpu_ras, recovery_work);
	काष्ठा amdgpu_device *remote_adev = शून्य;
	काष्ठा amdgpu_device *adev = ras->adev;
	काष्ठा list_head device_list, *device_list_handle =  शून्य;

	अगर (!ras->disable_ras_err_cnt_harvest) अणु
		काष्ठा amdgpu_hive_info *hive = amdgpu_get_xgmi_hive(adev);

		/* Build list of devices to query RAS related errors */
		अगर  (hive && adev->gmc.xgmi.num_physical_nodes > 1) अणु
			device_list_handle = &hive->device_list;
		पूर्ण अन्यथा अणु
			INIT_LIST_HEAD(&device_list);
			list_add_tail(&adev->gmc.xgmi.head, &device_list);
			device_list_handle = &device_list;
		पूर्ण

		list_क्रम_each_entry(remote_adev,
				device_list_handle, gmc.xgmi.head) अणु
			amdgpu_ras_query_err_status(remote_adev);
			amdgpu_ras_log_on_err_counter(remote_adev);
		पूर्ण

		amdgpu_put_xgmi_hive(hive);
	पूर्ण

	अगर (amdgpu_device_should_recover_gpu(ras->adev))
		amdgpu_device_gpu_recover(ras->adev, शून्य);
	atomic_set(&ras->in_recovery, 0);
पूर्ण

/* alloc/पुनः_स्मृति bps array */
अटल पूर्णांक amdgpu_ras_पुनः_स्मृति_eh_data_space(काष्ठा amdgpu_device *adev,
		काष्ठा ras_err_handler_data *data, पूर्णांक pages)
अणु
	अचिन्हित पूर्णांक old_space = data->count + data->space_left;
	अचिन्हित पूर्णांक new_space = old_space + pages;
	अचिन्हित पूर्णांक align_space = ALIGN(new_space, 512);
	व्योम *bps = kदो_स्मृति(align_space * माप(*data->bps), GFP_KERNEL);

	अगर (!bps) अणु
		kमुक्त(bps);
		वापस -ENOMEM;
	पूर्ण

	अगर (data->bps) अणु
		स_नकल(bps, data->bps,
				data->count * माप(*data->bps));
		kमुक्त(data->bps);
	पूर्ण

	data->bps = bps;
	data->space_left += align_space - old_space;
	वापस 0;
पूर्ण

/* it deal with vram only. */
पूर्णांक amdgpu_ras_add_bad_pages(काष्ठा amdgpu_device *adev,
		काष्ठा eeprom_table_record *bps, पूर्णांक pages)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_err_handler_data *data;
	पूर्णांक ret = 0;
	uपूर्णांक32_t i;

	अगर (!con || !con->eh_data || !bps || pages <= 0)
		वापस 0;

	mutex_lock(&con->recovery_lock);
	data = con->eh_data;
	अगर (!data)
		जाओ out;

	क्रम (i = 0; i < pages; i++) अणु
		अगर (amdgpu_ras_check_bad_page_unlock(con,
			bps[i].retired_page << AMDGPU_GPU_PAGE_SHIFT))
			जारी;

		अगर (!data->space_left &&
			amdgpu_ras_पुनः_स्मृति_eh_data_space(adev, data, 256)) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		amdgpu_vram_mgr_reserve_range(
			tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM),
			bps[i].retired_page << AMDGPU_GPU_PAGE_SHIFT,
			AMDGPU_GPU_PAGE_SIZE);

		स_नकल(&data->bps[data->count], &bps[i], माप(*data->bps));
		data->count++;
		data->space_left--;
	पूर्ण
out:
	mutex_unlock(&con->recovery_lock);

	वापस ret;
पूर्ण

/*
 * ग_लिखो error record array to eeprom, the function should be
 * रक्षित by recovery_lock
 */
पूर्णांक amdgpu_ras_save_bad_pages(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_err_handler_data *data;
	काष्ठा amdgpu_ras_eeprom_control *control;
	पूर्णांक save_count;

	अगर (!con || !con->eh_data)
		वापस 0;

	control = &con->eeprom_control;
	data = con->eh_data;
	save_count = data->count - control->num_recs;
	/* only new entries are saved */
	अगर (save_count > 0) अणु
		अगर (amdgpu_ras_eeprom_process_recods(control,
							&data->bps[control->num_recs],
							true,
							save_count)) अणु
			dev_err(adev->dev, "Failed to save EEPROM table data!");
			वापस -EIO;
		पूर्ण

		dev_info(adev->dev, "Saved %d pages to EEPROM table.\n", save_count);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * पढ़ो error record array in eeprom and reserve enough space क्रम
 * storing new bad pages
 */
अटल पूर्णांक amdgpu_ras_load_bad_pages(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras_eeprom_control *control =
					&adev->psp.ras.ras->eeprom_control;
	काष्ठा eeprom_table_record *bps = शून्य;
	पूर्णांक ret = 0;

	/* no bad page record, skip eeprom access */
	अगर (!control->num_recs || (amdgpu_bad_page_threshold == 0))
		वापस ret;

	bps = kसुस्मृति(control->num_recs, माप(*bps), GFP_KERNEL);
	अगर (!bps)
		वापस -ENOMEM;

	अगर (amdgpu_ras_eeprom_process_recods(control, bps, false,
		control->num_recs)) अणु
		dev_err(adev->dev, "Failed to load EEPROM table records!");
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret = amdgpu_ras_add_bad_pages(adev, bps, control->num_recs);

out:
	kमुक्त(bps);
	वापस ret;
पूर्ण

अटल bool amdgpu_ras_check_bad_page_unlock(काष्ठा amdgpu_ras *con,
				uपूर्णांक64_t addr)
अणु
	काष्ठा ras_err_handler_data *data = con->eh_data;
	पूर्णांक i;

	addr >>= AMDGPU_GPU_PAGE_SHIFT;
	क्रम (i = 0; i < data->count; i++)
		अगर (addr == data->bps[i].retired_page)
			वापस true;

	वापस false;
पूर्ण

/*
 * check अगर an address beदीर्घs to bad page
 *
 * Note: this check is only क्रम umc block
 */
अटल bool amdgpu_ras_check_bad_page(काष्ठा amdgpu_device *adev,
				uपूर्णांक64_t addr)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	bool ret = false;

	अगर (!con || !con->eh_data)
		वापस ret;

	mutex_lock(&con->recovery_lock);
	ret = amdgpu_ras_check_bad_page_unlock(con, addr);
	mutex_unlock(&con->recovery_lock);
	वापस ret;
पूर्ण

अटल व्योम amdgpu_ras_validate_threshold(काष्ठा amdgpu_device *adev,
					uपूर्णांक32_t max_length)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	पूर्णांक पंचांगp_threshold = amdgpu_bad_page_threshold;
	u64 val;

	/*
	 * Justअगरication of value bad_page_cnt_threshold in ras काष्ठाure
	 *
	 * Generally, -1 <= amdgpu_bad_page_threshold <= max record length
	 * in eeprom, and पूर्णांकroduce two scenarios accordingly.
	 *
	 * Bad page retirement enablement:
	 *    - If amdgpu_bad_page_threshold = -1,
	 *      bad_page_cnt_threshold = typical value by क्रमmula.
	 *
	 *    - When the value from user is 0 < amdgpu_bad_page_threshold <
	 *      max record length in eeprom, use it directly.
	 *
	 * Bad page retirement disablement:
	 *    - If amdgpu_bad_page_threshold = 0, bad page retirement
	 *      functionality is disabled, and bad_page_cnt_threshold will
	 *      take no effect.
	 */

	अगर (पंचांगp_threshold < -1)
		पंचांगp_threshold = -1;
	अन्यथा अगर (पंचांगp_threshold > max_length)
		पंचांगp_threshold = max_length;

	अगर (पंचांगp_threshold == -1) अणु
		val = adev->gmc.mc_vram_size;
		करो_भाग(val, RAS_BAD_PAGE_RATE);
		con->bad_page_cnt_threshold = min(lower_32_bits(val),
						max_length);
	पूर्ण अन्यथा अणु
		con->bad_page_cnt_threshold = पंचांगp_threshold;
	पूर्ण
पूर्ण

पूर्णांक amdgpu_ras_recovery_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_err_handler_data **data;
	uपूर्णांक32_t max_eeprom_records_len = 0;
	bool exc_err_limit = false;
	पूर्णांक ret;

	अगर (adev->ras_features && con)
		data = &con->eh_data;
	अन्यथा
		वापस 0;

	*data = kदो_स्मृति(माप(**data), GFP_KERNEL | __GFP_ZERO);
	अगर (!*data) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mutex_init(&con->recovery_lock);
	INIT_WORK(&con->recovery_work, amdgpu_ras_करो_recovery);
	atomic_set(&con->in_recovery, 0);
	con->adev = adev;

	max_eeprom_records_len = amdgpu_ras_eeprom_get_record_max_length();
	amdgpu_ras_validate_threshold(adev, max_eeprom_records_len);

	/* Toकरो: During test the SMU might fail to पढ़ो the eeprom through I2C
	 * when the GPU is pending on XGMI reset during probe समय
	 * (Mostly after second bus reset), skip it now
	 */
	अगर (adev->gmc.xgmi.pending_reset)
		वापस 0;
	ret = amdgpu_ras_eeprom_init(&con->eeprom_control, &exc_err_limit);
	/*
	 * This calling fails when exc_err_limit is true or
	 * ret != 0.
	 */
	अगर (exc_err_limit || ret)
		जाओ मुक्त;

	अगर (con->eeprom_control.num_recs) अणु
		ret = amdgpu_ras_load_bad_pages(adev);
		अगर (ret)
			जाओ मुक्त;
	पूर्ण

	वापस 0;

मुक्त:
	kमुक्त((*data)->bps);
	kमुक्त(*data);
	con->eh_data = शून्य;
out:
	dev_warn(adev->dev, "Failed to initialize ras recovery!\n");

	/*
	 * Except error threshold exceeding हाल, other failure हालs in this
	 * function would not fail amdgpu driver init.
	 */
	अगर (!exc_err_limit)
		ret = 0;
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक amdgpu_ras_recovery_fini(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_err_handler_data *data = con->eh_data;

	/* recovery_init failed to init it, fini is useless */
	अगर (!data)
		वापस 0;

	cancel_work_sync(&con->recovery_work);

	mutex_lock(&con->recovery_lock);
	con->eh_data = शून्य;
	kमुक्त(data->bps);
	kमुक्त(data);
	mutex_unlock(&con->recovery_lock);

	वापस 0;
पूर्ण
/* recovery end */

/* वापस 0 अगर ras will reset gpu and repost.*/
पूर्णांक amdgpu_ras_request_reset_on_boot(काष्ठा amdgpu_device *adev,
		अचिन्हित पूर्णांक block)
अणु
	काष्ठा amdgpu_ras *ras = amdgpu_ras_get_context(adev);

	अगर (!ras)
		वापस -EINVAL;

	ras->flags |= AMDGPU_RAS_FLAG_INIT_NEED_RESET;
	वापस 0;
पूर्ण

अटल bool amdgpu_ras_asic_supported(काष्ठा amdgpu_device *adev)
अणु
	वापस adev->asic_type == CHIP_VEGA10 ||
		adev->asic_type == CHIP_VEGA20 ||
		adev->asic_type == CHIP_ARCTURUS ||
		adev->asic_type == CHIP_ALDEBARAN ||
		adev->asic_type == CHIP_SIENNA_CICHLID;
पूर्ण

/*
 * check hardware's ras ability which will be saved in hw_supported.
 * अगर hardware करोes not support ras, we can skip some ras initializtion and
 * क्रमbid some ras operations from IP.
 * अगर software itself, say boot parameter, limit the ras ability. We still
 * need allow IP करो some limited operations, like disable. In such हाल,
 * we have to initialize ras as normal. but need check अगर operation is
 * allowed or not in each function.
 */
अटल व्योम amdgpu_ras_check_supported(काष्ठा amdgpu_device *adev,
		uपूर्णांक32_t *hw_supported, uपूर्णांक32_t *supported)
अणु
	*hw_supported = 0;
	*supported = 0;

	अगर (amdgpu_sriov_vf(adev) || !adev->is_atom_fw ||
	    !amdgpu_ras_asic_supported(adev))
		वापस;

	अगर (!adev->gmc.xgmi.connected_to_cpu) अणु
		अगर (amdgpu_atomfirmware_mem_ecc_supported(adev)) अणु
			dev_info(adev->dev, "MEM ECC is active.\n");
			*hw_supported |= (1 << AMDGPU_RAS_BLOCK__UMC |
					1 << AMDGPU_RAS_BLOCK__DF);
		पूर्ण अन्यथा अणु
			dev_info(adev->dev, "MEM ECC is not presented.\n");
		पूर्ण

		अगर (amdgpu_atomfirmware_sram_ecc_supported(adev)) अणु
			dev_info(adev->dev, "SRAM ECC is active.\n");
			*hw_supported |= ~(1 << AMDGPU_RAS_BLOCK__UMC |
					1 << AMDGPU_RAS_BLOCK__DF);
		पूर्ण अन्यथा अणु
			dev_info(adev->dev, "SRAM ECC is not presented.\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		/* driver only manages a few IP blocks RAS feature
		 * when GPU is connected cpu through XGMI */
		*hw_supported |= (1 << AMDGPU_RAS_BLOCK__GFX |
				1 << AMDGPU_RAS_BLOCK__SDMA |
				1 << AMDGPU_RAS_BLOCK__MMHUB);
	पूर्ण

	/* hw_supported needs to be aligned with RAS block mask. */
	*hw_supported &= AMDGPU_RAS_BLOCK_MASK;

	*supported = amdgpu_ras_enable == 0 ?
			0 : *hw_supported & amdgpu_ras_mask;
	adev->ras_features = *supported;
पूर्ण

पूर्णांक amdgpu_ras_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	पूर्णांक r;

	अगर (con)
		वापस 0;

	con = kदो_स्मृति(माप(काष्ठा amdgpu_ras) +
			माप(काष्ठा ras_manager) * AMDGPU_RAS_BLOCK_COUNT,
			GFP_KERNEL|__GFP_ZERO);
	अगर (!con)
		वापस -ENOMEM;

	con->objs = (काष्ठा ras_manager *)(con + 1);

	amdgpu_ras_set_context(adev, con);

	amdgpu_ras_check_supported(adev, &con->hw_supported,
			&con->supported);
	अगर (!con->hw_supported || (adev->asic_type == CHIP_VEGA10)) अणु
		/* set gfx block ras context feature क्रम VEGA20 Gaming
		 * send ras disable cmd to ras ta during ras late init.
		 */
		अगर (!adev->ras_features && adev->asic_type == CHIP_VEGA20) अणु
			con->features |= BIT(AMDGPU_RAS_BLOCK__GFX);

			वापस 0;
		पूर्ण

		r = 0;
		जाओ release_con;
	पूर्ण

	con->features = 0;
	INIT_LIST_HEAD(&con->head);
	/* Might need get this flag from vbios. */
	con->flags = RAS_DEFAULT_FLAGS;

	/* initialize nbio ras function ahead of any other
	 * ras functions so hardware fatal error पूर्णांकerrupt
	 * can be enabled as early as possible */
	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA20:
	हाल CHIP_ARCTURUS:
	हाल CHIP_ALDEBARAN:
		अगर (!adev->gmc.xgmi.connected_to_cpu)
			adev->nbio.ras_funcs = &nbio_v7_4_ras_funcs;
		अवरोध;
	शेष:
		/* nbio ras is not available */
		अवरोध;
	पूर्ण

	अगर (adev->nbio.ras_funcs &&
	    adev->nbio.ras_funcs->init_ras_controller_पूर्णांकerrupt) अणु
		r = adev->nbio.ras_funcs->init_ras_controller_पूर्णांकerrupt(adev);
		अगर (r)
			जाओ release_con;
	पूर्ण

	अगर (adev->nbio.ras_funcs &&
	    adev->nbio.ras_funcs->init_ras_err_event_athub_पूर्णांकerrupt) अणु
		r = adev->nbio.ras_funcs->init_ras_err_event_athub_पूर्णांकerrupt(adev);
		अगर (r)
			जाओ release_con;
	पूर्ण

	अगर (amdgpu_ras_fs_init(adev)) अणु
		r = -EINVAL;
		जाओ release_con;
	पूर्ण

	dev_info(adev->dev, "RAS INFO: ras initialized successfully, "
			"hardware ability[%x] ras_mask[%x]\n",
			con->hw_supported, con->supported);
	वापस 0;
release_con:
	amdgpu_ras_set_context(adev, शून्य);
	kमुक्त(con);

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_persistent_edc_harvesting_supported(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->gmc.xgmi.connected_to_cpu)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_persistent_edc_harvesting(काष्ठा amdgpu_device *adev,
					काष्ठा ras_common_अगर *ras_block)
अणु
	काष्ठा ras_query_अगर info = अणु
		.head = *ras_block,
	पूर्ण;

	अगर (!amdgpu_persistent_edc_harvesting_supported(adev))
		वापस 0;

	अगर (amdgpu_ras_query_error_status(adev, &info) != 0)
		DRM_WARN("RAS init harvest failure");

	अगर (amdgpu_ras_reset_error_status(adev, ras_block->block) != 0)
		DRM_WARN("RAS init harvest reset failure");

	वापस 0;
पूर्ण

/* helper function to handle common stuff in ip late init phase */
पूर्णांक amdgpu_ras_late_init(काष्ठा amdgpu_device *adev,
			 काष्ठा ras_common_अगर *ras_block,
			 काष्ठा ras_fs_अगर *fs_info,
			 काष्ठा ras_ih_अगर *ih_info)
अणु
	पूर्णांक r;

	/* disable RAS feature per IP block अगर it is not supported */
	अगर (!amdgpu_ras_is_supported(adev, ras_block->block)) अणु
		amdgpu_ras_feature_enable_on_boot(adev, ras_block, 0);
		वापस 0;
	पूर्ण

	r = amdgpu_ras_feature_enable_on_boot(adev, ras_block, 1);
	अगर (r) अणु
		अगर (r == -EAGAIN) अणु
			/* request gpu reset. will run again */
			amdgpu_ras_request_reset_on_boot(adev,
					ras_block->block);
			वापस 0;
		पूर्ण अन्यथा अगर (adev->in_suspend || amdgpu_in_reset(adev)) अणु
			/* in resume phase, अगर fail to enable ras,
			 * clean up all ras fs nodes, and disable ras */
			जाओ cleanup;
		पूर्ण अन्यथा
			वापस r;
	पूर्ण

	/* check क्रम errors on warm reset edc persisant supported ASIC */
	amdgpu_persistent_edc_harvesting(adev, ras_block);

	/* in resume phase, no need to create ras fs node */
	अगर (adev->in_suspend || amdgpu_in_reset(adev))
		वापस 0;

	अगर (ih_info->cb) अणु
		r = amdgpu_ras_पूर्णांकerrupt_add_handler(adev, ih_info);
		अगर (r)
			जाओ पूर्णांकerrupt;
	पूर्ण

	r = amdgpu_ras_sysfs_create(adev, fs_info);
	अगर (r)
		जाओ sysfs;

	वापस 0;
cleanup:
	amdgpu_ras_sysfs_हटाओ(adev, ras_block);
sysfs:
	अगर (ih_info->cb)
		amdgpu_ras_पूर्णांकerrupt_हटाओ_handler(adev, ih_info);
पूर्णांकerrupt:
	amdgpu_ras_feature_enable(adev, ras_block, 0);
	वापस r;
पूर्ण

/* helper function to हटाओ ras fs node and पूर्णांकerrupt handler */
व्योम amdgpu_ras_late_fini(काष्ठा amdgpu_device *adev,
			  काष्ठा ras_common_अगर *ras_block,
			  काष्ठा ras_ih_अगर *ih_info)
अणु
	अगर (!ras_block || !ih_info)
		वापस;

	amdgpu_ras_sysfs_हटाओ(adev, ras_block);
	अगर (ih_info->cb)
		amdgpu_ras_पूर्णांकerrupt_हटाओ_handler(adev, ih_info);
	amdgpu_ras_feature_enable(adev, ras_block, 0);
पूर्ण

/* करो some init work after IP late init as dependence.
 * and it runs in resume/gpu reset/booting up हालs.
 */
व्योम amdgpu_ras_resume(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);
	काष्ठा ras_manager *obj, *पंचांगp;

	अगर (!adev->ras_features || !con) अणु
		/* clean ras context क्रम VEGA20 Gaming after send ras disable cmd */
		amdgpu_release_ras_context(adev);

		वापस;
	पूर्ण

	अगर (con->flags & AMDGPU_RAS_FLAG_INIT_BY_VBIOS) अणु
		/* Set up all other IPs which are not implemented. There is a
		 * tricky thing that IP's actual ras error type should be
		 * MULTI_UNCORRECTABLE, but as driver करोes not handle it, so
		 * ERROR_NONE make sense anyway.
		 */
		amdgpu_ras_enable_all_features(adev, 1);

		/* We enable ras on all hw_supported block, but as boot
		 * parameter might disable some of them and one or more IP has
		 * not implemented yet. So we disable them on behalf.
		 */
		list_क्रम_each_entry_safe(obj, पंचांगp, &con->head, node) अणु
			अगर (!amdgpu_ras_is_supported(adev, obj->head.block)) अणु
				amdgpu_ras_feature_enable(adev, &obj->head, 0);
				/* there should be no any reference. */
				WARN_ON(alive_obj(obj));
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (con->flags & AMDGPU_RAS_FLAG_INIT_NEED_RESET) अणु
		con->flags &= ~AMDGPU_RAS_FLAG_INIT_NEED_RESET;
		/* setup ras obj state as disabled.
		 * क्रम init_by_vbios हाल.
		 * अगर we want to enable ras, just enable it in a normal way.
		 * If we want करो disable it, need setup ras obj as enabled,
		 * then issue another TA disable cmd.
		 * See feature_enable_on_boot
		 */
		amdgpu_ras_disable_all_features(adev, 1);
		amdgpu_ras_reset_gpu(adev);
	पूर्ण
पूर्ण

व्योम amdgpu_ras_suspend(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);

	अगर (!adev->ras_features || !con)
		वापस;

	amdgpu_ras_disable_all_features(adev, 0);
	/* Make sure all ras objects are disabled. */
	अगर (con->features)
		amdgpu_ras_disable_all_features(adev, 1);
पूर्ण

/* करो some fini work beक्रमe IP fini as dependence */
पूर्णांक amdgpu_ras_pre_fini(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);

	अगर (!adev->ras_features || !con)
		वापस 0;

	/* Need disable ras on all IPs here beक्रमe ip [hw/sw]fini */
	amdgpu_ras_disable_all_features(adev, 0);
	amdgpu_ras_recovery_fini(adev);
	वापस 0;
पूर्ण

पूर्णांक amdgpu_ras_fini(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);

	अगर (!adev->ras_features || !con)
		वापस 0;

	amdgpu_ras_fs_fini(adev);
	amdgpu_ras_पूर्णांकerrupt_हटाओ_all(adev);

	WARN(con->features, "Feature mask is not cleared");

	अगर (con->features)
		amdgpu_ras_disable_all_features(adev, 1);

	amdgpu_ras_set_context(adev, शून्य);
	kमुक्त(con);

	वापस 0;
पूर्ण

व्योम amdgpu_ras_global_ras_isr(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t hw_supported, supported;

	amdgpu_ras_check_supported(adev, &hw_supported, &supported);
	अगर (!hw_supported)
		वापस;

	अगर (atomic_cmpxchg(&amdgpu_ras_in_पूर्णांकr, 0, 1) == 0) अणु
		dev_info(adev->dev, "uncorrectable hardware error"
			"(ERREVENT_ATHUB_INTERRUPT) detected!\n");

		amdgpu_ras_reset_gpu(adev);
	पूर्ण
पूर्ण

bool amdgpu_ras_need_emergency_restart(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->asic_type == CHIP_VEGA20 &&
	    adev->pm.fw_version <= 0x283400) अणु
		वापस !(amdgpu_asic_reset_method(adev) == AMD_RESET_METHOD_BACO) &&
				amdgpu_ras_पूर्णांकr_triggered();
	पूर्ण

	वापस false;
पूर्ण

व्योम amdgpu_release_ras_context(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ras *con = amdgpu_ras_get_context(adev);

	अगर (!con)
		वापस;

	अगर (!adev->ras_features && con->features & BIT(AMDGPU_RAS_BLOCK__GFX)) अणु
		con->features &= ~BIT(AMDGPU_RAS_BLOCK__GFX);
		amdgpu_ras_set_context(adev, शून्य);
		kमुक्त(con);
	पूर्ण
पूर्ण
