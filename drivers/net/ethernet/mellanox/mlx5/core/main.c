<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/io-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/cq.h>
#समावेश <linux/mlx5/qp.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kmod.h>
#समावेश <linux/mlx5/mlx5_अगरc.h>
#समावेश <linux/mlx5/vport.h>
#अगर_घोषित CONFIG_RFS_ACCEL
#समावेश <linux/cpu_rmap.h>
#पूर्ण_अगर
#समावेश <linux/version.h>
#समावेश <net/devlink.h>
#समावेश "mlx5_core.h"
#समावेश "lib/eq.h"
#समावेश "fs_core.h"
#समावेश "lib/mpfs.h"
#समावेश "eswitch.h"
#समावेश "devlink.h"
#समावेश "fw_reset.h"
#समावेश "lib/mlx5.h"
#समावेश "fpga/core.h"
#समावेश "fpga/ipsec.h"
#समावेश "accel/ipsec.h"
#समावेश "accel/tls.h"
#समावेश "lib/clock.h"
#समावेश "lib/vxlan.h"
#समावेश "lib/geneve.h"
#समावेश "lib/devcom.h"
#समावेश "lib/pci_vsc.h"
#समावेश "diag/fw_tracer.h"
#समावेश "ecpf.h"
#समावेश "lib/hv_vhca.h"
#समावेश "diag/rsc_dump.h"
#समावेश "sf/vhca_event.h"
#समावेश "sf/dev/dev.h"
#समावेश "sf/sf.h"

MODULE_AUTHOR("Eli Cohen <eli@mellanox.com>");
MODULE_DESCRIPTION("Mellanox 5th generation network adapters (ConnectX series) core driver");
MODULE_LICENSE("Dual BSD/GPL");

अचिन्हित पूर्णांक mlx5_core_debug_mask;
module_param_named(debug_mask, mlx5_core_debug_mask, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug_mask, "debug mask: 1 = dump cmd data, 2 = dump cmd exec time, 3 = both. Default=0");

अटल अचिन्हित पूर्णांक prof_sel = MLX5_DEFAULT_PROF;
module_param_named(prof_sel, prof_sel, uपूर्णांक, 0444);
MODULE_PARM_DESC(prof_sel, "profile selector. Valid range 0 - 2");

अटल u32 sw_owner_id[4];

क्रमागत अणु
	MLX5_ATOMIC_REQ_MODE_BE = 0x0,
	MLX5_ATOMIC_REQ_MODE_HOST_ENDIANNESS = 0x1,
पूर्ण;

अटल काष्ठा mlx5_profile profile[] = अणु
	[0] = अणु
		.mask           = 0,
	पूर्ण,
	[1] = अणु
		.mask		= MLX5_PROF_MASK_QP_SIZE,
		.log_max_qp	= 12,
	पूर्ण,
	[2] = अणु
		.mask		= MLX5_PROF_MASK_QP_SIZE |
				  MLX5_PROF_MASK_MR_CACHE,
		.log_max_qp	= 18,
		.mr_cache[0]	= अणु
			.size	= 500,
			.limit	= 250
		पूर्ण,
		.mr_cache[1]	= अणु
			.size	= 500,
			.limit	= 250
		पूर्ण,
		.mr_cache[2]	= अणु
			.size	= 500,
			.limit	= 250
		पूर्ण,
		.mr_cache[3]	= अणु
			.size	= 500,
			.limit	= 250
		पूर्ण,
		.mr_cache[4]	= अणु
			.size	= 500,
			.limit	= 250
		पूर्ण,
		.mr_cache[5]	= अणु
			.size	= 500,
			.limit	= 250
		पूर्ण,
		.mr_cache[6]	= अणु
			.size	= 500,
			.limit	= 250
		पूर्ण,
		.mr_cache[7]	= अणु
			.size	= 500,
			.limit	= 250
		पूर्ण,
		.mr_cache[8]	= अणु
			.size	= 500,
			.limit	= 250
		पूर्ण,
		.mr_cache[9]	= अणु
			.size	= 500,
			.limit	= 250
		पूर्ण,
		.mr_cache[10]	= अणु
			.size	= 500,
			.limit	= 250
		पूर्ण,
		.mr_cache[11]	= अणु
			.size	= 500,
			.limit	= 250
		पूर्ण,
		.mr_cache[12]	= अणु
			.size	= 64,
			.limit	= 32
		पूर्ण,
		.mr_cache[13]	= अणु
			.size	= 32,
			.limit	= 16
		पूर्ण,
		.mr_cache[14]	= अणु
			.size	= 16,
			.limit	= 8
		पूर्ण,
		.mr_cache[15]	= अणु
			.size	= 8,
			.limit	= 4
		पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा FW_INIT_TIMEOUT_MILI		2000
#घोषणा FW_INIT_WAIT_MS			2
#घोषणा FW_PRE_INIT_TIMEOUT_MILI	120000
#घोषणा FW_INIT_WARN_MESSAGE_INTERVAL	20000

अटल पूर्णांक fw_initializing(काष्ठा mlx5_core_dev *dev)
अणु
	वापस ioपढ़ो32be(&dev->iseg->initializing) >> 31;
पूर्ण

अटल पूर्णांक रुको_fw_init(काष्ठा mlx5_core_dev *dev, u32 max_रुको_mili,
			u32 warn_समय_mili)
अणु
	अचिन्हित दीर्घ warn = jअगरfies + msecs_to_jअगरfies(warn_समय_mili);
	अचिन्हित दीर्घ end = jअगरfies + msecs_to_jअगरfies(max_रुको_mili);
	पूर्णांक err = 0;

	BUILD_BUG_ON(FW_PRE_INIT_TIMEOUT_MILI < FW_INIT_WARN_MESSAGE_INTERVAL);

	जबतक (fw_initializing(dev)) अणु
		अगर (समय_after(jअगरfies, end)) अणु
			err = -EBUSY;
			अवरोध;
		पूर्ण
		अगर (warn_समय_mili && समय_after(jअगरfies, warn)) अणु
			mlx5_core_warn(dev, "Waiting for FW initialization, timeout abort in %ds\n",
				       jअगरfies_to_msecs(end - warn) / 1000);
			warn = jअगरfies + msecs_to_jअगरfies(warn_समय_mili);
		पूर्ण
		msleep(FW_INIT_WAIT_MS);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम mlx5_set_driver_version(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक driver_ver_sz = MLX5_FLD_SZ_BYTES(set_driver_version_in,
					      driver_version);
	u8 in[MLX5_ST_SZ_BYTES(set_driver_version_in)] = अणुपूर्ण;
	पूर्णांक reमुख्यing_size = driver_ver_sz;
	अक्षर *string;

	अगर (!MLX5_CAP_GEN(dev, driver_version))
		वापस;

	string = MLX5_ADDR_OF(set_driver_version_in, in, driver_version);

	म_नकलन(string, "Linux", reमुख्यing_size);

	reमुख्यing_size = max_t(पूर्णांक, 0, driver_ver_sz - म_माप(string));
	म_जोड़न(string, ",", reमुख्यing_size);

	reमुख्यing_size = max_t(पूर्णांक, 0, driver_ver_sz - म_माप(string));
	म_जोड़न(string, KBUILD_MODNAME, reमुख्यing_size);

	reमुख्यing_size = max_t(पूर्णांक, 0, driver_ver_sz - म_माप(string));
	म_जोड़न(string, ",", reमुख्यing_size);

	reमुख्यing_size = max_t(पूर्णांक, 0, driver_ver_sz - म_माप(string));

	snम_लिखो(string + म_माप(string), reमुख्यing_size, "%u.%u.%u",
		LINUX_VERSION_MAJOR, LINUX_VERSION_PATCHLEVEL,
		LINUX_VERSION_SUBLEVEL);

	/*Send the command*/
	MLX5_SET(set_driver_version_in, in, opcode,
		 MLX5_CMD_OP_SET_DRIVER_VERSION);

	mlx5_cmd_exec_in(dev, set_driver_version, in);
पूर्ण

अटल पूर्णांक set_dma_caps(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err;

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err) अणु
		dev_warn(&pdev->dev, "Warning: couldn't set 64-bit PCI DMA mask\n");
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "Can't set PCI DMA mask, aborting\n");
			वापस err;
		पूर्ण
	पूर्ण

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err) अणु
		dev_warn(&pdev->dev,
			 "Warning: couldn't set 64-bit consistent PCI DMA mask\n");
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Can't set consistent PCI DMA mask, aborting\n");
			वापस err;
		पूर्ण
	पूर्ण

	dma_set_max_seg_size(&pdev->dev, 2u * 1024 * 1024 * 1024);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_pci_enable_device(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा pci_dev *pdev = dev->pdev;
	पूर्णांक err = 0;

	mutex_lock(&dev->pci_status_mutex);
	अगर (dev->pci_status == MLX5_PCI_STATUS_DISABLED) अणु
		err = pci_enable_device(pdev);
		अगर (!err)
			dev->pci_status = MLX5_PCI_STATUS_ENABLED;
	पूर्ण
	mutex_unlock(&dev->pci_status_mutex);

	वापस err;
पूर्ण

अटल व्योम mlx5_pci_disable_device(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा pci_dev *pdev = dev->pdev;

	mutex_lock(&dev->pci_status_mutex);
	अगर (dev->pci_status == MLX5_PCI_STATUS_ENABLED) अणु
		pci_disable_device(pdev);
		dev->pci_status = MLX5_PCI_STATUS_DISABLED;
	पूर्ण
	mutex_unlock(&dev->pci_status_mutex);
पूर्ण

अटल पूर्णांक request_bar(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err = 0;

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev, "Missing registers BAR, aborting\n");
		वापस -ENODEV;
	पूर्ण

	err = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (err)
		dev_err(&pdev->dev, "Couldn't get PCI resources, aborting\n");

	वापस err;
पूर्ण

अटल व्योम release_bar(काष्ठा pci_dev *pdev)
अणु
	pci_release_regions(pdev);
पूर्ण

काष्ठा mlx5_reg_host_endianness अणु
	u8	he;
	u8      rsvd[15];
पूर्ण;

#घोषणा CAP_MASK(pos, size) ((u64)((1 << (size)) - 1) << (pos))

क्रमागत अणु
	MLX5_CAP_BITS_RW_MASK = CAP_MASK(MLX5_CAP_OFF_CMDIF_CSUM, 2) |
				MLX5_DEV_CAP_FLAG_DCT,
पूर्ण;

अटल u16 to_fw_pkey_sz(काष्ठा mlx5_core_dev *dev, u32 size)
अणु
	चयन (size) अणु
	हाल 128:
		वापस 0;
	हाल 256:
		वापस 1;
	हाल 512:
		वापस 2;
	हाल 1024:
		वापस 3;
	हाल 2048:
		वापस 4;
	हाल 4096:
		वापस 5;
	शेष:
		mlx5_core_warn(dev, "invalid pkey table size %d\n", size);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_core_get_caps_mode(काष्ठा mlx5_core_dev *dev,
				   क्रमागत mlx5_cap_type cap_type,
				   क्रमागत mlx5_cap_mode cap_mode)
अणु
	u8 in[MLX5_ST_SZ_BYTES(query_hca_cap_in)];
	पूर्णांक out_sz = MLX5_ST_SZ_BYTES(query_hca_cap_out);
	व्योम *out, *hca_caps;
	u16 opmod = (cap_type << 1) | (cap_mode & 0x01);
	पूर्णांक err;

	स_रखो(in, 0, माप(in));
	out = kzalloc(out_sz, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	MLX5_SET(query_hca_cap_in, in, opcode, MLX5_CMD_OP_QUERY_HCA_CAP);
	MLX5_SET(query_hca_cap_in, in, op_mod, opmod);
	err = mlx5_cmd_exec_inout(dev, query_hca_cap, in, out);
	अगर (err) अणु
		mlx5_core_warn(dev,
			       "QUERY_HCA_CAP : type(%x) opmode(%x) Failed(%d)\n",
			       cap_type, cap_mode, err);
		जाओ query_ex;
	पूर्ण

	hca_caps =  MLX5_ADDR_OF(query_hca_cap_out, out, capability);

	चयन (cap_mode) अणु
	हाल HCA_CAP_OPMOD_GET_MAX:
		स_नकल(dev->caps.hca_max[cap_type], hca_caps,
		       MLX5_UN_SZ_BYTES(hca_cap_जोड़));
		अवरोध;
	हाल HCA_CAP_OPMOD_GET_CUR:
		स_नकल(dev->caps.hca_cur[cap_type], hca_caps,
		       MLX5_UN_SZ_BYTES(hca_cap_जोड़));
		अवरोध;
	शेष:
		mlx5_core_warn(dev,
			       "Tried to query dev cap type(%x) with wrong opmode(%x)\n",
			       cap_type, cap_mode);
		err = -EINVAL;
		अवरोध;
	पूर्ण
query_ex:
	kमुक्त(out);
	वापस err;
पूर्ण

पूर्णांक mlx5_core_get_caps(काष्ठा mlx5_core_dev *dev, क्रमागत mlx5_cap_type cap_type)
अणु
	पूर्णांक ret;

	ret = mlx5_core_get_caps_mode(dev, cap_type, HCA_CAP_OPMOD_GET_CUR);
	अगर (ret)
		वापस ret;
	वापस mlx5_core_get_caps_mode(dev, cap_type, HCA_CAP_OPMOD_GET_MAX);
पूर्ण

अटल पूर्णांक set_caps(काष्ठा mlx5_core_dev *dev, व्योम *in, पूर्णांक opmod)
अणु
	MLX5_SET(set_hca_cap_in, in, opcode, MLX5_CMD_OP_SET_HCA_CAP);
	MLX5_SET(set_hca_cap_in, in, op_mod, opmod << 1);
	वापस mlx5_cmd_exec_in(dev, set_hca_cap, in);
पूर्ण

अटल पूर्णांक handle_hca_cap_atomic(काष्ठा mlx5_core_dev *dev, व्योम *set_ctx)
अणु
	व्योम *set_hca_cap;
	पूर्णांक req_endianness;
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(dev, atomic))
		वापस 0;

	err = mlx5_core_get_caps(dev, MLX5_CAP_ATOMIC);
	अगर (err)
		वापस err;

	req_endianness =
		MLX5_CAP_ATOMIC(dev,
				supported_atomic_req_8B_endianness_mode_1);

	अगर (req_endianness != MLX5_ATOMIC_REQ_MODE_HOST_ENDIANNESS)
		वापस 0;

	set_hca_cap = MLX5_ADDR_OF(set_hca_cap_in, set_ctx, capability);

	/* Set requestor to host endianness */
	MLX5_SET(atomic_caps, set_hca_cap, atomic_req_8B_endianness_mode,
		 MLX5_ATOMIC_REQ_MODE_HOST_ENDIANNESS);

	वापस set_caps(dev, set_ctx, MLX5_SET_HCA_CAP_OP_MOD_ATOMIC);
पूर्ण

अटल पूर्णांक handle_hca_cap_odp(काष्ठा mlx5_core_dev *dev, व्योम *set_ctx)
अणु
	व्योम *set_hca_cap;
	bool करो_set = false;
	पूर्णांक err;

	अगर (!IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING) ||
	    !MLX5_CAP_GEN(dev, pg))
		वापस 0;

	err = mlx5_core_get_caps(dev, MLX5_CAP_ODP);
	अगर (err)
		वापस err;

	set_hca_cap = MLX5_ADDR_OF(set_hca_cap_in, set_ctx, capability);
	स_नकल(set_hca_cap, dev->caps.hca_cur[MLX5_CAP_ODP],
	       MLX5_ST_SZ_BYTES(odp_cap));

#घोषणा ODP_CAP_SET_MAX(dev, field)                                            \
	करो अणु                                                                   \
		u32 _res = MLX5_CAP_ODP_MAX(dev, field);                       \
		अगर (_res) अणु                                                    \
			करो_set = true;                                         \
			MLX5_SET(odp_cap, set_hca_cap, field, _res);           \
		पूर्ण                                                              \
	पूर्ण जबतक (0)

	ODP_CAP_SET_MAX(dev, ud_odp_caps.srq_receive);
	ODP_CAP_SET_MAX(dev, rc_odp_caps.srq_receive);
	ODP_CAP_SET_MAX(dev, xrc_odp_caps.srq_receive);
	ODP_CAP_SET_MAX(dev, xrc_odp_caps.send);
	ODP_CAP_SET_MAX(dev, xrc_odp_caps.receive);
	ODP_CAP_SET_MAX(dev, xrc_odp_caps.ग_लिखो);
	ODP_CAP_SET_MAX(dev, xrc_odp_caps.पढ़ो);
	ODP_CAP_SET_MAX(dev, xrc_odp_caps.atomic);
	ODP_CAP_SET_MAX(dev, dc_odp_caps.srq_receive);
	ODP_CAP_SET_MAX(dev, dc_odp_caps.send);
	ODP_CAP_SET_MAX(dev, dc_odp_caps.receive);
	ODP_CAP_SET_MAX(dev, dc_odp_caps.ग_लिखो);
	ODP_CAP_SET_MAX(dev, dc_odp_caps.पढ़ो);
	ODP_CAP_SET_MAX(dev, dc_odp_caps.atomic);

	अगर (!करो_set)
		वापस 0;

	वापस set_caps(dev, set_ctx, MLX5_SET_HCA_CAP_OP_MOD_ODP);
पूर्ण

अटल पूर्णांक handle_hca_cap(काष्ठा mlx5_core_dev *dev, व्योम *set_ctx)
अणु
	काष्ठा mlx5_profile *prof = &dev->profile;
	व्योम *set_hca_cap;
	पूर्णांक err;

	err = mlx5_core_get_caps(dev, MLX5_CAP_GENERAL);
	अगर (err)
		वापस err;

	set_hca_cap = MLX5_ADDR_OF(set_hca_cap_in, set_ctx,
				   capability);
	स_नकल(set_hca_cap, dev->caps.hca_cur[MLX5_CAP_GENERAL],
	       MLX5_ST_SZ_BYTES(cmd_hca_cap));

	mlx5_core_dbg(dev, "Current Pkey table size %d Setting new size %d\n",
		      mlx5_to_sw_pkey_sz(MLX5_CAP_GEN(dev, pkey_table_size)),
		      128);
	/* we limit the size of the pkey table to 128 entries क्रम now */
	MLX5_SET(cmd_hca_cap, set_hca_cap, pkey_table_size,
		 to_fw_pkey_sz(dev, 128));

	/* Check log_max_qp from HCA caps to set in current profile */
	अगर (MLX5_CAP_GEN_MAX(dev, log_max_qp) < prof->log_max_qp) अणु
		mlx5_core_warn(dev, "log_max_qp value in current profile is %d, changing it to HCA capability limit (%d)\n",
			       prof->log_max_qp,
			       MLX5_CAP_GEN_MAX(dev, log_max_qp));
		prof->log_max_qp = MLX5_CAP_GEN_MAX(dev, log_max_qp);
	पूर्ण
	अगर (prof->mask & MLX5_PROF_MASK_QP_SIZE)
		MLX5_SET(cmd_hca_cap, set_hca_cap, log_max_qp,
			 prof->log_max_qp);

	/* disable cmdअगर checksum */
	MLX5_SET(cmd_hca_cap, set_hca_cap, cmdअगर_checksum, 0);

	/* Enable 4K UAR only when HCA supports it and page size is bigger
	 * than 4K.
	 */
	अगर (MLX5_CAP_GEN_MAX(dev, uar_4k) && PAGE_SIZE > 4096)
		MLX5_SET(cmd_hca_cap, set_hca_cap, uar_4k, 1);

	MLX5_SET(cmd_hca_cap, set_hca_cap, log_uar_page_sz, PAGE_SHIFT - 12);

	अगर (MLX5_CAP_GEN_MAX(dev, cache_line_128byte))
		MLX5_SET(cmd_hca_cap,
			 set_hca_cap,
			 cache_line_128byte,
			 cache_line_size() >= 128 ? 1 : 0);

	अगर (MLX5_CAP_GEN_MAX(dev, dct))
		MLX5_SET(cmd_hca_cap, set_hca_cap, dct, 1);

	अगर (MLX5_CAP_GEN_MAX(dev, pci_sync_क्रम_fw_update_event))
		MLX5_SET(cmd_hca_cap, set_hca_cap, pci_sync_क्रम_fw_update_event, 1);

	अगर (MLX5_CAP_GEN_MAX(dev, num_vhca_ports))
		MLX5_SET(cmd_hca_cap,
			 set_hca_cap,
			 num_vhca_ports,
			 MLX5_CAP_GEN_MAX(dev, num_vhca_ports));

	अगर (MLX5_CAP_GEN_MAX(dev, release_all_pages))
		MLX5_SET(cmd_hca_cap, set_hca_cap, release_all_pages, 1);

	अगर (MLX5_CAP_GEN_MAX(dev, mkey_by_name))
		MLX5_SET(cmd_hca_cap, set_hca_cap, mkey_by_name, 1);

	mlx5_vhca_state_cap_handle(dev, set_hca_cap);

	अगर (MLX5_CAP_GEN_MAX(dev, num_total_dynamic_vf_msix))
		MLX5_SET(cmd_hca_cap, set_hca_cap, num_total_dynamic_vf_msix,
			 MLX5_CAP_GEN_MAX(dev, num_total_dynamic_vf_msix));

	वापस set_caps(dev, set_ctx, MLX5_SET_HCA_CAP_OP_MOD_GENERAL_DEVICE);
पूर्ण

अटल पूर्णांक handle_hca_cap_roce(काष्ठा mlx5_core_dev *dev, व्योम *set_ctx)
अणु
	व्योम *set_hca_cap;
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(dev, roce))
		वापस 0;

	err = mlx5_core_get_caps(dev, MLX5_CAP_ROCE);
	अगर (err)
		वापस err;

	अगर (MLX5_CAP_ROCE(dev, sw_r_roce_src_udp_port) ||
	    !MLX5_CAP_ROCE_MAX(dev, sw_r_roce_src_udp_port))
		वापस 0;

	set_hca_cap = MLX5_ADDR_OF(set_hca_cap_in, set_ctx, capability);
	स_नकल(set_hca_cap, dev->caps.hca_cur[MLX5_CAP_ROCE],
	       MLX5_ST_SZ_BYTES(roce_cap));
	MLX5_SET(roce_cap, set_hca_cap, sw_r_roce_src_udp_port, 1);

	err = set_caps(dev, set_ctx, MLX5_SET_HCA_CAP_OP_MOD_ROCE);
	वापस err;
पूर्ण

अटल पूर्णांक set_hca_cap(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक set_sz = MLX5_ST_SZ_BYTES(set_hca_cap_in);
	व्योम *set_ctx;
	पूर्णांक err;

	set_ctx = kzalloc(set_sz, GFP_KERNEL);
	अगर (!set_ctx)
		वापस -ENOMEM;

	err = handle_hca_cap(dev, set_ctx);
	अगर (err) अणु
		mlx5_core_err(dev, "handle_hca_cap failed\n");
		जाओ out;
	पूर्ण

	स_रखो(set_ctx, 0, set_sz);
	err = handle_hca_cap_atomic(dev, set_ctx);
	अगर (err) अणु
		mlx5_core_err(dev, "handle_hca_cap_atomic failed\n");
		जाओ out;
	पूर्ण

	स_रखो(set_ctx, 0, set_sz);
	err = handle_hca_cap_odp(dev, set_ctx);
	अगर (err) अणु
		mlx5_core_err(dev, "handle_hca_cap_odp failed\n");
		जाओ out;
	पूर्ण

	स_रखो(set_ctx, 0, set_sz);
	err = handle_hca_cap_roce(dev, set_ctx);
	अगर (err) अणु
		mlx5_core_err(dev, "handle_hca_cap_roce failed\n");
		जाओ out;
	पूर्ण

out:
	kमुक्त(set_ctx);
	वापस err;
पूर्ण

अटल पूर्णांक set_hca_ctrl(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_reg_host_endianness he_in;
	काष्ठा mlx5_reg_host_endianness he_out;
	पूर्णांक err;

	अगर (!mlx5_core_is_pf(dev))
		वापस 0;

	स_रखो(&he_in, 0, माप(he_in));
	he_in.he = MLX5_SET_HOST_ENDIANNESS;
	err = mlx5_core_access_reg(dev, &he_in,  माप(he_in),
					&he_out, माप(he_out),
					MLX5_REG_HOST_ENDIANNESS, 0, 1);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_core_set_hca_शेषs(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक ret = 0;

	/* Disable local_lb by शेष */
	अगर (MLX5_CAP_GEN(dev, port_type) == MLX5_CAP_PORT_TYPE_ETH)
		ret = mlx5_nic_vport_update_local_lb(dev, false);

	वापस ret;
पूर्ण

पूर्णांक mlx5_core_enable_hca(काष्ठा mlx5_core_dev *dev, u16 func_id)
अणु
	u32 in[MLX5_ST_SZ_DW(enable_hca_in)] = अणुपूर्ण;

	MLX5_SET(enable_hca_in, in, opcode, MLX5_CMD_OP_ENABLE_HCA);
	MLX5_SET(enable_hca_in, in, function_id, func_id);
	MLX5_SET(enable_hca_in, in, embedded_cpu_function,
		 dev->caps.embedded_cpu);
	वापस mlx5_cmd_exec_in(dev, enable_hca, in);
पूर्ण

पूर्णांक mlx5_core_disable_hca(काष्ठा mlx5_core_dev *dev, u16 func_id)
अणु
	u32 in[MLX5_ST_SZ_DW(disable_hca_in)] = अणुपूर्ण;

	MLX5_SET(disable_hca_in, in, opcode, MLX5_CMD_OP_DISABLE_HCA);
	MLX5_SET(disable_hca_in, in, function_id, func_id);
	MLX5_SET(enable_hca_in, in, embedded_cpu_function,
		 dev->caps.embedded_cpu);
	वापस mlx5_cmd_exec_in(dev, disable_hca, in);
पूर्ण

अटल पूर्णांक mlx5_core_set_issi(काष्ठा mlx5_core_dev *dev)
अणु
	u32 query_out[MLX5_ST_SZ_DW(query_issi_out)] = अणुपूर्ण;
	u32 query_in[MLX5_ST_SZ_DW(query_issi_in)] = अणुपूर्ण;
	u32 sup_issi;
	पूर्णांक err;

	MLX5_SET(query_issi_in, query_in, opcode, MLX5_CMD_OP_QUERY_ISSI);
	err = mlx5_cmd_exec_inout(dev, query_issi, query_in, query_out);
	अगर (err) अणु
		u32 syndrome;
		u8 status;

		mlx5_cmd_mbox_status(query_out, &status, &syndrome);
		अगर (!status || syndrome == MLX5_DRIVER_SYND) अणु
			mlx5_core_err(dev, "Failed to query ISSI err(%d) status(%d) synd(%d)\n",
				      err, status, syndrome);
			वापस err;
		पूर्ण

		mlx5_core_warn(dev, "Query ISSI is not supported by FW, ISSI is 0\n");
		dev->issi = 0;
		वापस 0;
	पूर्ण

	sup_issi = MLX5_GET(query_issi_out, query_out, supported_issi_dw0);

	अगर (sup_issi & (1 << 1)) अणु
		u32 set_in[MLX5_ST_SZ_DW(set_issi_in)] = अणुपूर्ण;

		MLX5_SET(set_issi_in, set_in, opcode, MLX5_CMD_OP_SET_ISSI);
		MLX5_SET(set_issi_in, set_in, current_issi, 1);
		err = mlx5_cmd_exec_in(dev, set_issi, set_in);
		अगर (err) अणु
			mlx5_core_err(dev, "Failed to set ISSI to 1 err(%d)\n",
				      err);
			वापस err;
		पूर्ण

		dev->issi = 1;

		वापस 0;
	पूर्ण अन्यथा अगर (sup_issi & (1 << 0) || !sup_issi) अणु
		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक mlx5_pci_init(काष्ठा mlx5_core_dev *dev, काष्ठा pci_dev *pdev,
			 स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा mlx5_priv *priv = &dev->priv;
	पूर्णांक err = 0;

	mutex_init(&dev->pci_status_mutex);
	pci_set_drvdata(dev->pdev, dev);

	dev->bar_addr = pci_resource_start(pdev, 0);
	priv->numa_node = dev_to_node(mlx5_core_dma_dev(dev));

	err = mlx5_pci_enable_device(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Cannot enable PCI device, aborting\n");
		वापस err;
	पूर्ण

	err = request_bar(pdev);
	अगर (err) अणु
		mlx5_core_err(dev, "error requesting BARs, aborting\n");
		जाओ err_disable;
	पूर्ण

	pci_set_master(pdev);

	err = set_dma_caps(pdev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed setting DMA capabilities mask, aborting\n");
		जाओ err_clr_master;
	पूर्ण

	अगर (pci_enable_atomic_ops_to_root(pdev, PCI_EXP_DEVCAP2_ATOMIC_COMP32) &&
	    pci_enable_atomic_ops_to_root(pdev, PCI_EXP_DEVCAP2_ATOMIC_COMP64) &&
	    pci_enable_atomic_ops_to_root(pdev, PCI_EXP_DEVCAP2_ATOMIC_COMP128))
		mlx5_core_dbg(dev, "Enabling pci atomics failed\n");

	dev->iseg_base = dev->bar_addr;
	dev->iseg = ioremap(dev->iseg_base, माप(*dev->iseg));
	अगर (!dev->iseg) अणु
		err = -ENOMEM;
		mlx5_core_err(dev, "Failed mapping initialization segment, aborting\n");
		जाओ err_clr_master;
	पूर्ण

	mlx5_pci_vsc_init(dev);
	dev->caps.embedded_cpu = mlx5_पढ़ो_embedded_cpu(dev);
	वापस 0;

err_clr_master:
	pci_clear_master(dev->pdev);
	release_bar(dev->pdev);
err_disable:
	mlx5_pci_disable_device(dev);
	वापस err;
पूर्ण

अटल व्योम mlx5_pci_बंद(काष्ठा mlx5_core_dev *dev)
अणु
	/* health work might still be active, and it needs pci bar in
	 * order to know the NIC state. Thereक्रमe, drain the health WQ
	 * beक्रमe removing the pci bars
	 */
	mlx5_drain_health_wq(dev);
	iounmap(dev->iseg);
	pci_clear_master(dev->pdev);
	release_bar(dev->pdev);
	mlx5_pci_disable_device(dev);
पूर्ण

अटल पूर्णांक mlx5_init_once(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक err;

	dev->priv.devcom = mlx5_devcom_रेजिस्टर_device(dev);
	अगर (IS_ERR(dev->priv.devcom))
		mlx5_core_err(dev, "failed to register with devcom (0x%p)\n",
			      dev->priv.devcom);

	err = mlx5_query_board_id(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "query board id failed\n");
		जाओ err_devcom;
	पूर्ण

	err = mlx5_irq_table_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "failed to initialize irq table\n");
		जाओ err_devcom;
	पूर्ण

	err = mlx5_eq_table_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "failed to initialize eq\n");
		जाओ err_irq_cleanup;
	पूर्ण

	err = mlx5_events_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "failed to initialize events\n");
		जाओ err_eq_cleanup;
	पूर्ण

	err = mlx5_fw_reset_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "failed to initialize fw reset events\n");
		जाओ err_events_cleanup;
	पूर्ण

	mlx5_cq_debugfs_init(dev);

	mlx5_init_reserved_gids(dev);

	mlx5_init_घड़ी(dev);

	dev->vxlan = mlx5_vxlan_create(dev);
	dev->geneve = mlx5_geneve_create(dev);

	err = mlx5_init_rl_table(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to init rate limiting\n");
		जाओ err_tables_cleanup;
	पूर्ण

	err = mlx5_mpfs_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to init l2 table %d\n", err);
		जाओ err_rl_cleanup;
	पूर्ण

	err = mlx5_sriov_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to init sriov %d\n", err);
		जाओ err_mpfs_cleanup;
	पूर्ण

	err = mlx5_eचयन_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to init eswitch %d\n", err);
		जाओ err_sriov_cleanup;
	पूर्ण

	err = mlx5_fpga_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to init fpga device %d\n", err);
		जाओ err_eचयन_cleanup;
	पूर्ण

	err = mlx5_vhca_event_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to init vhca event notifier %d\n", err);
		जाओ err_fpga_cleanup;
	पूर्ण

	err = mlx5_sf_hw_table_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to init SF HW table %d\n", err);
		जाओ err_sf_hw_table_cleanup;
	पूर्ण

	err = mlx5_sf_table_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to init SF table %d\n", err);
		जाओ err_sf_table_cleanup;
	पूर्ण

	dev->dm = mlx5_dm_create(dev);
	अगर (IS_ERR(dev->dm))
		mlx5_core_warn(dev, "Failed to init device memory%d\n", err);

	dev->tracer = mlx5_fw_tracer_create(dev);
	dev->hv_vhca = mlx5_hv_vhca_create(dev);
	dev->rsc_dump = mlx5_rsc_dump_create(dev);

	वापस 0;

err_sf_table_cleanup:
	mlx5_sf_hw_table_cleanup(dev);
err_sf_hw_table_cleanup:
	mlx5_vhca_event_cleanup(dev);
err_fpga_cleanup:
	mlx5_fpga_cleanup(dev);
err_eचयन_cleanup:
	mlx5_eचयन_cleanup(dev->priv.eचयन);
err_sriov_cleanup:
	mlx5_sriov_cleanup(dev);
err_mpfs_cleanup:
	mlx5_mpfs_cleanup(dev);
err_rl_cleanup:
	mlx5_cleanup_rl_table(dev);
err_tables_cleanup:
	mlx5_geneve_destroy(dev->geneve);
	mlx5_vxlan_destroy(dev->vxlan);
	mlx5_cq_debugfs_cleanup(dev);
	mlx5_fw_reset_cleanup(dev);
err_events_cleanup:
	mlx5_events_cleanup(dev);
err_eq_cleanup:
	mlx5_eq_table_cleanup(dev);
err_irq_cleanup:
	mlx5_irq_table_cleanup(dev);
err_devcom:
	mlx5_devcom_unरेजिस्टर_device(dev->priv.devcom);

	वापस err;
पूर्ण

अटल व्योम mlx5_cleanup_once(काष्ठा mlx5_core_dev *dev)
अणु
	mlx5_rsc_dump_destroy(dev);
	mlx5_hv_vhca_destroy(dev->hv_vhca);
	mlx5_fw_tracer_destroy(dev->tracer);
	mlx5_dm_cleanup(dev);
	mlx5_sf_table_cleanup(dev);
	mlx5_sf_hw_table_cleanup(dev);
	mlx5_vhca_event_cleanup(dev);
	mlx5_fpga_cleanup(dev);
	mlx5_eचयन_cleanup(dev->priv.eचयन);
	mlx5_sriov_cleanup(dev);
	mlx5_mpfs_cleanup(dev);
	mlx5_cleanup_rl_table(dev);
	mlx5_geneve_destroy(dev->geneve);
	mlx5_vxlan_destroy(dev->vxlan);
	mlx5_cleanup_घड़ी(dev);
	mlx5_cleanup_reserved_gids(dev);
	mlx5_cq_debugfs_cleanup(dev);
	mlx5_fw_reset_cleanup(dev);
	mlx5_events_cleanup(dev);
	mlx5_eq_table_cleanup(dev);
	mlx5_irq_table_cleanup(dev);
	mlx5_devcom_unरेजिस्टर_device(dev->priv.devcom);
पूर्ण

अटल पूर्णांक mlx5_function_setup(काष्ठा mlx5_core_dev *dev, bool boot)
अणु
	पूर्णांक err;

	mlx5_core_info(dev, "firmware version: %d.%d.%d\n", fw_rev_maj(dev),
		       fw_rev_min(dev), fw_rev_sub(dev));

	/* Only PFs hold the relevant PCIe inक्रमmation क्रम this query */
	अगर (mlx5_core_is_pf(dev))
		pcie_prपूर्णांक_link_status(dev->pdev);

	/* रुको क्रम firmware to accept initialization segments configurations
	 */
	err = रुको_fw_init(dev, FW_PRE_INIT_TIMEOUT_MILI, FW_INIT_WARN_MESSAGE_INTERVAL);
	अगर (err) अणु
		mlx5_core_err(dev, "Firmware over %d MS in pre-initializing state, aborting\n",
			      FW_PRE_INIT_TIMEOUT_MILI);
		वापस err;
	पूर्ण

	err = mlx5_cmd_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed initializing command interface, aborting\n");
		वापस err;
	पूर्ण

	err = रुको_fw_init(dev, FW_INIT_TIMEOUT_MILI, 0);
	अगर (err) अणु
		mlx5_core_err(dev, "Firmware over %d MS in initializing state, aborting\n",
			      FW_INIT_TIMEOUT_MILI);
		जाओ err_cmd_cleanup;
	पूर्ण

	mlx5_cmd_set_state(dev, MLX5_CMDIF_STATE_UP);

	err = mlx5_core_enable_hca(dev, 0);
	अगर (err) अणु
		mlx5_core_err(dev, "enable hca failed\n");
		जाओ err_cmd_cleanup;
	पूर्ण

	err = mlx5_core_set_issi(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "failed to set issi\n");
		जाओ err_disable_hca;
	पूर्ण

	err = mlx5_satisfy_startup_pages(dev, 1);
	अगर (err) अणु
		mlx5_core_err(dev, "failed to allocate boot pages\n");
		जाओ err_disable_hca;
	पूर्ण

	err = set_hca_ctrl(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "set_hca_ctrl failed\n");
		जाओ reclaim_boot_pages;
	पूर्ण

	err = set_hca_cap(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "set_hca_cap failed\n");
		जाओ reclaim_boot_pages;
	पूर्ण

	err = mlx5_satisfy_startup_pages(dev, 0);
	अगर (err) अणु
		mlx5_core_err(dev, "failed to allocate init pages\n");
		जाओ reclaim_boot_pages;
	पूर्ण

	err = mlx5_cmd_init_hca(dev, sw_owner_id);
	अगर (err) अणु
		mlx5_core_err(dev, "init hca failed\n");
		जाओ reclaim_boot_pages;
	पूर्ण

	mlx5_set_driver_version(dev);

	mlx5_start_health_poll(dev);

	err = mlx5_query_hca_caps(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "query hca failed\n");
		जाओ stop_health;
	पूर्ण

	वापस 0;

stop_health:
	mlx5_stop_health_poll(dev, boot);
reclaim_boot_pages:
	mlx5_reclaim_startup_pages(dev);
err_disable_hca:
	mlx5_core_disable_hca(dev, 0);
err_cmd_cleanup:
	mlx5_cmd_set_state(dev, MLX5_CMDIF_STATE_DOWN);
	mlx5_cmd_cleanup(dev);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_function_tearकरोwn(काष्ठा mlx5_core_dev *dev, bool boot)
अणु
	पूर्णांक err;

	mlx5_stop_health_poll(dev, boot);
	err = mlx5_cmd_tearकरोwn_hca(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "tear_down_hca failed, skip cleanup\n");
		वापस err;
	पूर्ण
	mlx5_reclaim_startup_pages(dev);
	mlx5_core_disable_hca(dev, 0);
	mlx5_cmd_set_state(dev, MLX5_CMDIF_STATE_DOWN);
	mlx5_cmd_cleanup(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_load(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक err;

	dev->priv.uar = mlx5_get_uars_page(dev);
	अगर (IS_ERR(dev->priv.uar)) अणु
		mlx5_core_err(dev, "Failed allocating uar, aborting\n");
		err = PTR_ERR(dev->priv.uar);
		वापस err;
	पूर्ण

	mlx5_events_start(dev);
	mlx5_pagealloc_start(dev);

	err = mlx5_irq_table_create(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to alloc IRQs\n");
		जाओ err_irq_table;
	पूर्ण

	err = mlx5_eq_table_create(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to create EQs\n");
		जाओ err_eq_table;
	पूर्ण

	err = mlx5_fw_tracer_init(dev->tracer);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to init FW tracer\n");
		जाओ err_fw_tracer;
	पूर्ण

	mlx5_fw_reset_events_start(dev);
	mlx5_hv_vhca_init(dev->hv_vhca);

	err = mlx5_rsc_dump_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to init Resource dump\n");
		जाओ err_rsc_dump;
	पूर्ण

	err = mlx5_fpga_device_start(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "fpga device start failed %d\n", err);
		जाओ err_fpga_start;
	पूर्ण

	mlx5_accel_ipsec_init(dev);

	err = mlx5_accel_tls_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "TLS device start failed %d\n", err);
		जाओ err_tls_start;
	पूर्ण

	err = mlx5_init_fs(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to init flow steering\n");
		जाओ err_fs;
	पूर्ण

	err = mlx5_core_set_hca_शेषs(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to set hca defaults\n");
		जाओ err_set_hca;
	पूर्ण

	mlx5_vhca_event_start(dev);

	err = mlx5_sf_hw_table_create(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "sf table create failed %d\n", err);
		जाओ err_vhca;
	पूर्ण

	err = mlx5_ec_init(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to init embedded CPU\n");
		जाओ err_ec;
	पूर्ण

	err = mlx5_sriov_attach(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "sriov init failed %d\n", err);
		जाओ err_sriov;
	पूर्ण

	mlx5_sf_dev_table_create(dev);

	वापस 0;

err_sriov:
	mlx5_ec_cleanup(dev);
err_ec:
	mlx5_sf_hw_table_destroy(dev);
err_vhca:
	mlx5_vhca_event_stop(dev);
err_set_hca:
	mlx5_cleanup_fs(dev);
err_fs:
	mlx5_accel_tls_cleanup(dev);
err_tls_start:
	mlx5_accel_ipsec_cleanup(dev);
	mlx5_fpga_device_stop(dev);
err_fpga_start:
	mlx5_rsc_dump_cleanup(dev);
err_rsc_dump:
	mlx5_hv_vhca_cleanup(dev->hv_vhca);
	mlx5_fw_reset_events_stop(dev);
	mlx5_fw_tracer_cleanup(dev->tracer);
err_fw_tracer:
	mlx5_eq_table_destroy(dev);
err_eq_table:
	mlx5_irq_table_destroy(dev);
err_irq_table:
	mlx5_pagealloc_stop(dev);
	mlx5_events_stop(dev);
	mlx5_put_uars_page(dev, dev->priv.uar);
	वापस err;
पूर्ण

अटल व्योम mlx5_unload(काष्ठा mlx5_core_dev *dev)
अणु
	mlx5_sf_dev_table_destroy(dev);
	mlx5_sriov_detach(dev);
	mlx5_ec_cleanup(dev);
	mlx5_sf_hw_table_destroy(dev);
	mlx5_vhca_event_stop(dev);
	mlx5_cleanup_fs(dev);
	mlx5_accel_ipsec_cleanup(dev);
	mlx5_accel_tls_cleanup(dev);
	mlx5_fpga_device_stop(dev);
	mlx5_rsc_dump_cleanup(dev);
	mlx5_hv_vhca_cleanup(dev->hv_vhca);
	mlx5_fw_reset_events_stop(dev);
	mlx5_fw_tracer_cleanup(dev->tracer);
	mlx5_eq_table_destroy(dev);
	mlx5_irq_table_destroy(dev);
	mlx5_pagealloc_stop(dev);
	mlx5_events_stop(dev);
	mlx5_put_uars_page(dev, dev->priv.uar);
पूर्ण

पूर्णांक mlx5_init_one(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक err = 0;

	mutex_lock(&dev->पूर्णांकf_state_mutex);
	अगर (test_bit(MLX5_INTERFACE_STATE_UP, &dev->पूर्णांकf_state)) अणु
		mlx5_core_warn(dev, "interface is up, NOP\n");
		जाओ out;
	पूर्ण
	/* हटाओ any previous indication of पूर्णांकernal error */
	dev->state = MLX5_DEVICE_STATE_UP;

	err = mlx5_function_setup(dev, true);
	अगर (err)
		जाओ err_function;

	err = mlx5_init_once(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "sw objs init failed\n");
		जाओ function_tearकरोwn;
	पूर्ण

	err = mlx5_load(dev);
	अगर (err)
		जाओ err_load;

	set_bit(MLX5_INTERFACE_STATE_UP, &dev->पूर्णांकf_state);

	err = mlx5_devlink_रेजिस्टर(priv_to_devlink(dev), dev->device);
	अगर (err)
		जाओ err_devlink_reg;

	err = mlx5_रेजिस्टर_device(dev);
	अगर (err)
		जाओ err_रेजिस्टर;

	mutex_unlock(&dev->पूर्णांकf_state_mutex);
	वापस 0;

err_रेजिस्टर:
	mlx5_devlink_unरेजिस्टर(priv_to_devlink(dev));
err_devlink_reg:
	clear_bit(MLX5_INTERFACE_STATE_UP, &dev->पूर्णांकf_state);
	mlx5_unload(dev);
err_load:
	mlx5_cleanup_once(dev);
function_tearकरोwn:
	mlx5_function_tearकरोwn(dev, true);
err_function:
	dev->state = MLX5_DEVICE_STATE_INTERNAL_ERROR;
out:
	mutex_unlock(&dev->पूर्णांकf_state_mutex);
	वापस err;
पूर्ण

व्योम mlx5_uninit_one(काष्ठा mlx5_core_dev *dev)
अणु
	mutex_lock(&dev->पूर्णांकf_state_mutex);

	mlx5_unरेजिस्टर_device(dev);
	mlx5_devlink_unरेजिस्टर(priv_to_devlink(dev));

	अगर (!test_bit(MLX5_INTERFACE_STATE_UP, &dev->पूर्णांकf_state)) अणु
		mlx5_core_warn(dev, "%s: interface is down, NOP\n",
			       __func__);
		mlx5_cleanup_once(dev);
		जाओ out;
	पूर्ण

	clear_bit(MLX5_INTERFACE_STATE_UP, &dev->पूर्णांकf_state);
	mlx5_unload(dev);
	mlx5_cleanup_once(dev);
	mlx5_function_tearकरोwn(dev, true);
out:
	mutex_unlock(&dev->पूर्णांकf_state_mutex);
पूर्ण

पूर्णांक mlx5_load_one(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक err = 0;

	mutex_lock(&dev->पूर्णांकf_state_mutex);
	अगर (test_bit(MLX5_INTERFACE_STATE_UP, &dev->पूर्णांकf_state)) अणु
		mlx5_core_warn(dev, "interface is up, NOP\n");
		जाओ out;
	पूर्ण
	/* हटाओ any previous indication of पूर्णांकernal error */
	dev->state = MLX5_DEVICE_STATE_UP;

	err = mlx5_function_setup(dev, false);
	अगर (err)
		जाओ err_function;

	err = mlx5_load(dev);
	अगर (err)
		जाओ err_load;

	set_bit(MLX5_INTERFACE_STATE_UP, &dev->पूर्णांकf_state);

	err = mlx5_attach_device(dev);
	अगर (err)
		जाओ err_attach;

	mutex_unlock(&dev->पूर्णांकf_state_mutex);
	वापस 0;

err_attach:
	clear_bit(MLX5_INTERFACE_STATE_UP, &dev->पूर्णांकf_state);
	mlx5_unload(dev);
err_load:
	mlx5_function_tearकरोwn(dev, false);
err_function:
	dev->state = MLX5_DEVICE_STATE_INTERNAL_ERROR;
out:
	mutex_unlock(&dev->पूर्णांकf_state_mutex);
	वापस err;
पूर्ण

व्योम mlx5_unload_one(काष्ठा mlx5_core_dev *dev)
अणु
	mutex_lock(&dev->पूर्णांकf_state_mutex);

	mlx5_detach_device(dev);

	अगर (!test_bit(MLX5_INTERFACE_STATE_UP, &dev->पूर्णांकf_state)) अणु
		mlx5_core_warn(dev, "%s: interface is down, NOP\n",
			       __func__);
		जाओ out;
	पूर्ण

	clear_bit(MLX5_INTERFACE_STATE_UP, &dev->पूर्णांकf_state);
	mlx5_unload(dev);
	mlx5_function_tearकरोwn(dev, false);
out:
	mutex_unlock(&dev->पूर्णांकf_state_mutex);
पूर्ण

पूर्णांक mlx5_mdev_init(काष्ठा mlx5_core_dev *dev, पूर्णांक profile_idx)
अणु
	काष्ठा mlx5_priv *priv = &dev->priv;
	पूर्णांक err;

	स_नकल(&dev->profile, &profile[profile_idx], माप(dev->profile));
	INIT_LIST_HEAD(&priv->ctx_list);
	spin_lock_init(&priv->ctx_lock);
	mutex_init(&dev->पूर्णांकf_state_mutex);

	mutex_init(&priv->bfregs.reg_head.lock);
	mutex_init(&priv->bfregs.wc_head.lock);
	INIT_LIST_HEAD(&priv->bfregs.reg_head.list);
	INIT_LIST_HEAD(&priv->bfregs.wc_head.list);

	mutex_init(&priv->alloc_mutex);
	mutex_init(&priv->pgdir_mutex);
	INIT_LIST_HEAD(&priv->pgdir_list);

	priv->dbg_root = debugfs_create_dir(dev_name(dev->device),
					    mlx5_debugfs_root);
	INIT_LIST_HEAD(&priv->traps);

	err = mlx5_health_init(dev);
	अगर (err)
		जाओ err_health_init;

	err = mlx5_pagealloc_init(dev);
	अगर (err)
		जाओ err_pagealloc_init;

	err = mlx5_adev_init(dev);
	अगर (err)
		जाओ err_adev_init;

	वापस 0;

err_adev_init:
	mlx5_pagealloc_cleanup(dev);
err_pagealloc_init:
	mlx5_health_cleanup(dev);
err_health_init:
	debugfs_हटाओ(dev->priv.dbg_root);
	mutex_destroy(&priv->pgdir_mutex);
	mutex_destroy(&priv->alloc_mutex);
	mutex_destroy(&priv->bfregs.wc_head.lock);
	mutex_destroy(&priv->bfregs.reg_head.lock);
	mutex_destroy(&dev->पूर्णांकf_state_mutex);
	वापस err;
पूर्ण

व्योम mlx5_mdev_uninit(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_priv *priv = &dev->priv;

	mlx5_adev_cleanup(dev);
	mlx5_pagealloc_cleanup(dev);
	mlx5_health_cleanup(dev);
	debugfs_हटाओ_recursive(dev->priv.dbg_root);
	mutex_destroy(&priv->pgdir_mutex);
	mutex_destroy(&priv->alloc_mutex);
	mutex_destroy(&priv->bfregs.wc_head.lock);
	mutex_destroy(&priv->bfregs.reg_head.lock);
	mutex_destroy(&dev->पूर्णांकf_state_mutex);
पूर्ण

अटल पूर्णांक probe_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा mlx5_core_dev *dev;
	काष्ठा devlink *devlink;
	पूर्णांक err;

	devlink = mlx5_devlink_alloc();
	अगर (!devlink) अणु
		dev_err(&pdev->dev, "devlink alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	dev = devlink_priv(devlink);
	dev->device = &pdev->dev;
	dev->pdev = pdev;

	dev->coredev_type = id->driver_data & MLX5_PCI_DEV_IS_VF ?
			 MLX5_COREDEV_VF : MLX5_COREDEV_PF;

	dev->priv.adev_idx = mlx5_adev_idx_alloc();
	अगर (dev->priv.adev_idx < 0) अणु
		err = dev->priv.adev_idx;
		जाओ adev_init_err;
	पूर्ण

	err = mlx5_mdev_init(dev, prof_sel);
	अगर (err)
		जाओ mdev_init_err;

	err = mlx5_pci_init(dev, pdev, id);
	अगर (err) अणु
		mlx5_core_err(dev, "mlx5_pci_init failed with error code %d\n",
			      err);
		जाओ pci_init_err;
	पूर्ण

	err = mlx5_init_one(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "mlx5_init_one failed with error code %d\n",
			      err);
		जाओ err_init_one;
	पूर्ण

	err = mlx5_crdump_enable(dev);
	अगर (err)
		dev_err(&pdev->dev, "mlx5_crdump_enable failed with error code %d\n", err);

	pci_save_state(pdev);
	अगर (!mlx5_core_is_mp_slave(dev))
		devlink_reload_enable(devlink);
	वापस 0;

err_init_one:
	mlx5_pci_बंद(dev);
pci_init_err:
	mlx5_mdev_uninit(dev);
mdev_init_err:
	mlx5_adev_idx_मुक्त(dev->priv.adev_idx);
adev_init_err:
	mlx5_devlink_मुक्त(devlink);

	वापस err;
पूर्ण

अटल व्योम हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	काष्ठा devlink *devlink = priv_to_devlink(dev);

	devlink_reload_disable(devlink);
	mlx5_crdump_disable(dev);
	mlx5_drain_health_wq(dev);
	mlx5_uninit_one(dev);
	mlx5_pci_बंद(dev);
	mlx5_mdev_uninit(dev);
	mlx5_adev_idx_मुक्त(dev->priv.adev_idx);
	mlx5_devlink_मुक्त(devlink);
पूर्ण

अटल pci_ers_result_t mlx5_pci_err_detected(काष्ठा pci_dev *pdev,
					      pci_channel_state_t state)
अणु
	काष्ठा mlx5_core_dev *dev = pci_get_drvdata(pdev);

	mlx5_core_info(dev, "%s was called\n", __func__);

	mlx5_enter_error_state(dev, false);
	mlx5_error_sw_reset(dev);
	mlx5_unload_one(dev);
	mlx5_drain_health_wq(dev);
	mlx5_pci_disable_device(dev);

	वापस state == pci_channel_io_perm_failure ?
		PCI_ERS_RESULT_DISCONNECT : PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/* रुको क्रम the device to show vital signs by रुकोing
 * क्रम the health counter to start counting.
 */
अटल पूर्णांक रुको_vital(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx5_core_dev *dev = pci_get_drvdata(pdev);
	काष्ठा mlx5_core_health *health = &dev->priv.health;
	स्थिर पूर्णांक niter = 100;
	u32 last_count = 0;
	u32 count;
	पूर्णांक i;

	क्रम (i = 0; i < niter; i++) अणु
		count = ioपढ़ो32be(health->health_counter);
		अगर (count && count != 0xffffffff) अणु
			अगर (last_count && last_count != count) अणु
				mlx5_core_info(dev,
					       "wait vital counter value 0x%x after %d iterations\n",
					       count, i);
				वापस 0;
			पूर्ण
			last_count = count;
		पूर्ण
		msleep(50);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल pci_ers_result_t mlx5_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx5_core_dev *dev = pci_get_drvdata(pdev);
	पूर्णांक err;

	mlx5_core_info(dev, "%s was called\n", __func__);

	err = mlx5_pci_enable_device(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "%s: mlx5_pci_enable_device failed with error code: %d\n",
			      __func__, err);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	pci_set_master(pdev);
	pci_restore_state(pdev);
	pci_save_state(pdev);

	अगर (रुको_vital(pdev)) अणु
		mlx5_core_err(dev, "%s: wait_vital timed out\n", __func__);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम mlx5_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx5_core_dev *dev = pci_get_drvdata(pdev);
	पूर्णांक err;

	mlx5_core_info(dev, "%s was called\n", __func__);

	err = mlx5_load_one(dev);
	अगर (err)
		mlx5_core_err(dev, "%s: mlx5_load_one failed with error code: %d\n",
			      __func__, err);
	अन्यथा
		mlx5_core_info(dev, "%s: device recovered\n", __func__);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers mlx5_err_handler = अणु
	.error_detected = mlx5_pci_err_detected,
	.slot_reset	= mlx5_pci_slot_reset,
	.resume		= mlx5_pci_resume
पूर्ण;

अटल पूर्णांक mlx5_try_fast_unload(काष्ठा mlx5_core_dev *dev)
अणु
	bool fast_tearकरोwn = false, क्रमce_tearकरोwn = false;
	पूर्णांक ret = 1;

	fast_tearकरोwn = MLX5_CAP_GEN(dev, fast_tearकरोwn);
	क्रमce_tearकरोwn = MLX5_CAP_GEN(dev, क्रमce_tearकरोwn);

	mlx5_core_dbg(dev, "force teardown firmware support=%d\n", क्रमce_tearकरोwn);
	mlx5_core_dbg(dev, "fast teardown firmware support=%d\n", fast_tearकरोwn);

	अगर (!fast_tearकरोwn && !क्रमce_tearकरोwn)
		वापस -EOPNOTSUPP;

	अगर (dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR) अणु
		mlx5_core_dbg(dev, "Device in internal error state, giving up\n");
		वापस -EAGAIN;
	पूर्ण

	/* Panic tear करोwn fw command will stop the PCI bus communication
	 * with the HCA, so the health polll is no दीर्घer needed.
	 */
	mlx5_drain_health_wq(dev);
	mlx5_stop_health_poll(dev, false);

	ret = mlx5_cmd_fast_tearकरोwn_hca(dev);
	अगर (!ret)
		जाओ succeed;

	ret = mlx5_cmd_क्रमce_tearकरोwn_hca(dev);
	अगर (!ret)
		जाओ succeed;

	mlx5_core_dbg(dev, "Firmware couldn't do fast unload error: %d\n", ret);
	mlx5_start_health_poll(dev);
	वापस ret;

succeed:
	mlx5_enter_error_state(dev, true);

	/* Some platक्रमms requiring मुक्तing the IRQ's in the shutकरोwn
	 * flow. If they aren't freed they can't be allocated after
	 * kexec. There is no need to cleanup the mlx5_core software
	 * contexts.
	 */
	mlx5_core_eq_मुक्त_irqs(dev);

	वापस 0;
पूर्ण

अटल व्योम shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	पूर्णांक err;

	mlx5_core_info(dev, "Shutdown was called\n");
	err = mlx5_try_fast_unload(dev);
	अगर (err)
		mlx5_unload_one(dev);
	mlx5_pci_disable_device(dev);
पूर्ण

अटल पूर्णांक mlx5_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	काष्ठा mlx5_core_dev *dev = pci_get_drvdata(pdev);

	mlx5_unload_one(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx5_core_dev *dev = pci_get_drvdata(pdev);

	वापस mlx5_load_one(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id mlx5_core_pci_table[] = अणु
	अणु PCI_VDEVICE(MELLANOX, PCI_DEVICE_ID_MELLANOX_CONNECTIB) पूर्ण,
	अणु PCI_VDEVICE(MELLANOX, 0x1012), MLX5_PCI_DEV_IS_VFपूर्ण,	/* Connect-IB VF */
	अणु PCI_VDEVICE(MELLANOX, PCI_DEVICE_ID_MELLANOX_CONNECTX4) पूर्ण,
	अणु PCI_VDEVICE(MELLANOX, 0x1014), MLX5_PCI_DEV_IS_VFपूर्ण,	/* ConnectX-4 VF */
	अणु PCI_VDEVICE(MELLANOX, PCI_DEVICE_ID_MELLANOX_CONNECTX4_LX) पूर्ण,
	अणु PCI_VDEVICE(MELLANOX, 0x1016), MLX5_PCI_DEV_IS_VFपूर्ण,	/* ConnectX-4LX VF */
	अणु PCI_VDEVICE(MELLANOX, 0x1017) पूर्ण,			/* ConnectX-5, PCIe 3.0 */
	अणु PCI_VDEVICE(MELLANOX, 0x1018), MLX5_PCI_DEV_IS_VFपूर्ण,	/* ConnectX-5 VF */
	अणु PCI_VDEVICE(MELLANOX, 0x1019) पूर्ण,			/* ConnectX-5 Ex */
	अणु PCI_VDEVICE(MELLANOX, 0x101a), MLX5_PCI_DEV_IS_VFपूर्ण,	/* ConnectX-5 Ex VF */
	अणु PCI_VDEVICE(MELLANOX, 0x101b) पूर्ण,			/* ConnectX-6 */
	अणु PCI_VDEVICE(MELLANOX, 0x101c), MLX5_PCI_DEV_IS_VFपूर्ण,	/* ConnectX-6 VF */
	अणु PCI_VDEVICE(MELLANOX, 0x101d) पूर्ण,			/* ConnectX-6 Dx */
	अणु PCI_VDEVICE(MELLANOX, 0x101e), MLX5_PCI_DEV_IS_VFपूर्ण,	/* ConnectX Family mlx5Gen Virtual Function */
	अणु PCI_VDEVICE(MELLANOX, 0x101f) पूर्ण,			/* ConnectX-6 LX */
	अणु PCI_VDEVICE(MELLANOX, 0x1021) पूर्ण,			/* ConnectX-7 */
	अणु PCI_VDEVICE(MELLANOX, 0xa2d2) पूर्ण,			/* BlueField पूर्णांकegrated ConnectX-5 network controller */
	अणु PCI_VDEVICE(MELLANOX, 0xa2d3), MLX5_PCI_DEV_IS_VFपूर्ण,	/* BlueField पूर्णांकegrated ConnectX-5 network controller VF */
	अणु PCI_VDEVICE(MELLANOX, 0xa2d6) पूर्ण,			/* BlueField-2 पूर्णांकegrated ConnectX-6 Dx network controller */
	अणु PCI_VDEVICE(MELLANOX, 0xa2dc) पूर्ण,			/* BlueField-3 पूर्णांकegrated ConnectX-7 network controller */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, mlx5_core_pci_table);

व्योम mlx5_disable_device(काष्ठा mlx5_core_dev *dev)
अणु
	mlx5_error_sw_reset(dev);
	mlx5_unload_one(dev);
पूर्ण

पूर्णांक mlx5_recover_device(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक ret = -EIO;

	mlx5_pci_disable_device(dev);
	अगर (mlx5_pci_slot_reset(dev->pdev) == PCI_ERS_RESULT_RECOVERED)
		ret = mlx5_load_one(dev);
	वापस ret;
पूर्ण

अटल काष्ठा pci_driver mlx5_core_driver = अणु
	.name           = KBUILD_MODNAME,
	.id_table       = mlx5_core_pci_table,
	.probe          = probe_one,
	.हटाओ         = हटाओ_one,
	.suspend        = mlx5_suspend,
	.resume         = mlx5_resume,
	.shutकरोwn	= shutकरोwn,
	.err_handler	= &mlx5_err_handler,
	.sriov_configure   = mlx5_core_sriov_configure,
	.sriov_get_vf_total_msix = mlx5_sriov_get_vf_total_msix,
	.sriov_set_msix_vec_count = mlx5_core_sriov_set_msix_vec_count,
पूर्ण;

अटल व्योम mlx5_core_verअगरy_params(व्योम)
अणु
	अगर (prof_sel >= ARRAY_SIZE(profile)) अणु
		pr_warn("mlx5_core: WARNING: Invalid module parameter prof_sel %d, valid range 0-%zu, changing back to default(%d)\n",
			prof_sel,
			ARRAY_SIZE(profile) - 1,
			MLX5_DEFAULT_PROF);
		prof_sel = MLX5_DEFAULT_PROF;
	पूर्ण
पूर्ण

अटल पूर्णांक __init init(व्योम)
अणु
	पूर्णांक err;

	WARN_ONCE(म_भेद(MLX5_ADEV_NAME, KBUILD_MODNAME),
		  "mlx5_core name not in sync with kernel module name");

	get_अक्रमom_bytes(&sw_owner_id, माप(sw_owner_id));

	mlx5_core_verअगरy_params();
	mlx5_fpga_ipsec_build_fs_cmds();
	mlx5_रेजिस्टर_debugfs();

	err = pci_रेजिस्टर_driver(&mlx5_core_driver);
	अगर (err)
		जाओ err_debug;

	err = mlx5_sf_driver_रेजिस्टर();
	अगर (err)
		जाओ err_sf;

#अगर_घोषित CONFIG_MLX5_CORE_EN
	err = mlx5e_init();
	अगर (err) अणु
		pci_unरेजिस्टर_driver(&mlx5_core_driver);
		जाओ err_debug;
	पूर्ण
#पूर्ण_अगर

	वापस 0;

err_sf:
	pci_unरेजिस्टर_driver(&mlx5_core_driver);
err_debug:
	mlx5_unरेजिस्टर_debugfs();
	वापस err;
पूर्ण

अटल व्योम __निकास cleanup(व्योम)
अणु
#अगर_घोषित CONFIG_MLX5_CORE_EN
	mlx5e_cleanup();
#पूर्ण_अगर
	mlx5_sf_driver_unरेजिस्टर();
	pci_unरेजिस्टर_driver(&mlx5_core_driver);
	mlx5_unरेजिस्टर_debugfs();
पूर्ण

module_init(init);
module_निकास(cleanup);
