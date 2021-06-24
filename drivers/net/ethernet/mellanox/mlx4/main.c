<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2005, 2006, 2007, 2008 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2006, 2007 Cisco Systems, Inc. All rights reserved.
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

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/io-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/kmod.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/devlink.h>

#समावेश <uapi/rdma/mlx4-abi.h>
#समावेश <linux/mlx4/device.h>
#समावेश <linux/mlx4/करोorbell.h>

#समावेश "mlx4.h"
#समावेश "fw.h"
#समावेश "icm.h"

MODULE_AUTHOR("Roland Dreier");
MODULE_DESCRIPTION("Mellanox ConnectX HCA low-level driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(DRV_VERSION);

काष्ठा workqueue_काष्ठा *mlx4_wq;

#अगर_घोषित CONFIG_MLX4_DEBUG

पूर्णांक mlx4_debug_level; /* 0 by शेष */
module_param_named(debug_level, mlx4_debug_level, पूर्णांक, 0644);
MODULE_PARM_DESC(debug_level, "Enable debug tracing if > 0");

#पूर्ण_अगर /* CONFIG_MLX4_DEBUG */

#अगर_घोषित CONFIG_PCI_MSI

अटल पूर्णांक msi_x = 1;
module_param(msi_x, पूर्णांक, 0444);
MODULE_PARM_DESC(msi_x, "0 - don't use MSI-X, 1 - use MSI-X, >1 - limit number of MSI-X irqs to msi_x");

#अन्यथा /* CONFIG_PCI_MSI */

#घोषणा msi_x (0)

#पूर्ण_अगर /* CONFIG_PCI_MSI */

अटल uपूर्णांक8_t num_vfs[3] = अणु0, 0, 0पूर्ण;
अटल पूर्णांक num_vfs_argc;
module_param_array(num_vfs, byte, &num_vfs_argc, 0444);
MODULE_PARM_DESC(num_vfs, "enable #num_vfs functions if num_vfs > 0\n"
			  "num_vfs=port1,port2,port1+2");

अटल uपूर्णांक8_t probe_vf[3] = अणु0, 0, 0पूर्ण;
अटल पूर्णांक probe_vfs_argc;
module_param_array(probe_vf, byte, &probe_vfs_argc, 0444);
MODULE_PARM_DESC(probe_vf, "number of vfs to probe by pf driver (num_vfs > 0)\n"
			   "probe_vf=port1,port2,port1+2");

अटल पूर्णांक mlx4_log_num_mgm_entry_size = MLX4_DEFAULT_MGM_LOG_ENTRY_SIZE;
module_param_named(log_num_mgm_entry_size,
			mlx4_log_num_mgm_entry_size, पूर्णांक, 0444);
MODULE_PARM_DESC(log_num_mgm_entry_size, "log mgm size, that defines the num"
					 " of qp per mcg, for example:"
					 " 10 gives 248.range: 7 <="
					 " log_num_mgm_entry_size <= 12."
					 " To activate device managed"
					 " flow steering when available, set to -1");

अटल bool enable_64b_cqe_eqe = true;
module_param(enable_64b_cqe_eqe, bool, 0444);
MODULE_PARM_DESC(enable_64b_cqe_eqe,
		 "Enable 64 byte CQEs/EQEs when the FW supports this (default: True)");

अटल bool enable_4k_uar;
module_param(enable_4k_uar, bool, 0444);
MODULE_PARM_DESC(enable_4k_uar,
		 "Enable using 4K UAR. Should not be enabled if have VFs which do not support 4K UARs (default: false)");

#घोषणा PF_CONTEXT_BEHAVIOUR_MASK	(MLX4_FUNC_CAP_64B_EQE_CQE | \
					 MLX4_FUNC_CAP_EQE_CQE_STRIDE | \
					 MLX4_FUNC_CAP_DMFS_A0_STATIC)

#घोषणा RESET_PERSIST_MASK_FLAGS	(MLX4_FLAG_SRIOV)

अटल अक्षर mlx4_version[] =
	DRV_NAME ": Mellanox ConnectX core driver v"
	DRV_VERSION "\n";

अटल स्थिर काष्ठा mlx4_profile शेष_profile = अणु
	.num_qp		= 1 << 18,
	.num_srq	= 1 << 16,
	.rdmarc_per_qp	= 1 << 4,
	.num_cq		= 1 << 16,
	.num_mcg	= 1 << 13,
	.num_mpt	= 1 << 19,
	.num_mtt	= 1 << 20, /* It is really num mtt segements */
पूर्ण;

अटल स्थिर काष्ठा mlx4_profile low_mem_profile = अणु
	.num_qp		= 1 << 17,
	.num_srq	= 1 << 6,
	.rdmarc_per_qp	= 1 << 4,
	.num_cq		= 1 << 8,
	.num_mcg	= 1 << 8,
	.num_mpt	= 1 << 9,
	.num_mtt	= 1 << 7,
पूर्ण;

अटल पूर्णांक log_num_mac = 7;
module_param_named(log_num_mac, log_num_mac, पूर्णांक, 0444);
MODULE_PARM_DESC(log_num_mac, "Log2 max number of MACs per ETH port (1-7)");

अटल पूर्णांक log_num_vlan;
module_param_named(log_num_vlan, log_num_vlan, पूर्णांक, 0444);
MODULE_PARM_DESC(log_num_vlan, "Log2 max number of VLANs per ETH port (0-7)");
/* Log2 max number of VLANs per ETH port (0-7) */
#घोषणा MLX4_LOG_NUM_VLANS 7
#घोषणा MLX4_MIN_LOG_NUM_VLANS 0
#घोषणा MLX4_MIN_LOG_NUM_MAC 1

अटल bool use_prio;
module_param_named(use_prio, use_prio, bool, 0444);
MODULE_PARM_DESC(use_prio, "Enable steering by VLAN priority on ETH ports (deprecated)");

पूर्णांक log_mtts_per_seg = ilog2(1);
module_param_named(log_mtts_per_seg, log_mtts_per_seg, पूर्णांक, 0444);
MODULE_PARM_DESC(log_mtts_per_seg, "Log2 number of MTT entries per segment "
		 "(0-7) (default: 0)");

अटल पूर्णांक port_type_array[2] = अणुMLX4_PORT_TYPE_NONE, MLX4_PORT_TYPE_NONEपूर्ण;
अटल पूर्णांक arr_argc = 2;
module_param_array(port_type_array, पूर्णांक, &arr_argc, 0444);
MODULE_PARM_DESC(port_type_array, "Array of port types: HW_DEFAULT (0) is default "
				"1 for IB, 2 for Ethernet");

काष्ठा mlx4_port_config अणु
	काष्ठा list_head list;
	क्रमागत mlx4_port_type port_type[MLX4_MAX_PORTS + 1];
	काष्ठा pci_dev *pdev;
पूर्ण;

अटल atomic_t pf_loading = ATOMIC_INIT(0);

अटल पूर्णांक mlx4_devlink_ierr_reset_get(काष्ठा devlink *devlink, u32 id,
				       काष्ठा devlink_param_gset_ctx *ctx)
अणु
	ctx->val.vbool = !!mlx4_पूर्णांकernal_err_reset;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_devlink_ierr_reset_set(काष्ठा devlink *devlink, u32 id,
				       काष्ठा devlink_param_gset_ctx *ctx)
अणु
	mlx4_पूर्णांकernal_err_reset = ctx->val.vbool;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_devlink_crdump_snapshot_get(काष्ठा devlink *devlink, u32 id,
					    काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा mlx4_priv *priv = devlink_priv(devlink);
	काष्ठा mlx4_dev *dev = &priv->dev;

	ctx->val.vbool = dev->persist->crdump.snapshot_enable;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_devlink_crdump_snapshot_set(काष्ठा devlink *devlink, u32 id,
					    काष्ठा devlink_param_gset_ctx *ctx)
अणु
	काष्ठा mlx4_priv *priv = devlink_priv(devlink);
	काष्ठा mlx4_dev *dev = &priv->dev;

	dev->persist->crdump.snapshot_enable = ctx->val.vbool;
	वापस 0;
पूर्ण

अटल पूर्णांक
mlx4_devlink_max_macs_validate(काष्ठा devlink *devlink, u32 id,
			       जोड़ devlink_param_value val,
			       काष्ठा netlink_ext_ack *extack)
अणु
	u32 value = val.vu32;

	अगर (value < 1 || value > 128)
		वापस -दुस्फल;

	अगर (!is_घातer_of_2(value)) अणु
		NL_SET_ERR_MSG_MOD(extack, "max_macs supported must be power of 2");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत mlx4_devlink_param_id अणु
	MLX4_DEVLINK_PARAM_ID_BASE = DEVLINK_PARAM_GENERIC_ID_MAX,
	MLX4_DEVLINK_PARAM_ID_ENABLE_64B_CQE_EQE,
	MLX4_DEVLINK_PARAM_ID_ENABLE_4K_UAR,
पूर्ण;

अटल स्थिर काष्ठा devlink_param mlx4_devlink_params[] = अणु
	DEVLINK_PARAM_GENERIC(INT_ERR_RESET,
			      BIT(DEVLINK_PARAM_CMODE_RUNTIME) |
			      BIT(DEVLINK_PARAM_CMODE_DRIVERINIT),
			      mlx4_devlink_ierr_reset_get,
			      mlx4_devlink_ierr_reset_set, शून्य),
	DEVLINK_PARAM_GENERIC(MAX_MACS,
			      BIT(DEVLINK_PARAM_CMODE_DRIVERINIT),
			      शून्य, शून्य, mlx4_devlink_max_macs_validate),
	DEVLINK_PARAM_GENERIC(REGION_SNAPSHOT,
			      BIT(DEVLINK_PARAM_CMODE_RUNTIME) |
			      BIT(DEVLINK_PARAM_CMODE_DRIVERINIT),
			      mlx4_devlink_crdump_snapshot_get,
			      mlx4_devlink_crdump_snapshot_set, शून्य),
	DEVLINK_PARAM_DRIVER(MLX4_DEVLINK_PARAM_ID_ENABLE_64B_CQE_EQE,
			     "enable_64b_cqe_eqe", DEVLINK_PARAM_TYPE_BOOL,
			     BIT(DEVLINK_PARAM_CMODE_DRIVERINIT),
			     शून्य, शून्य, शून्य),
	DEVLINK_PARAM_DRIVER(MLX4_DEVLINK_PARAM_ID_ENABLE_4K_UAR,
			     "enable_4k_uar", DEVLINK_PARAM_TYPE_BOOL,
			     BIT(DEVLINK_PARAM_CMODE_DRIVERINIT),
			     शून्य, शून्य, शून्य),
पूर्ण;

अटल व्योम mlx4_devlink_set_params_init_values(काष्ठा devlink *devlink)
अणु
	जोड़ devlink_param_value value;

	value.vbool = !!mlx4_पूर्णांकernal_err_reset;
	devlink_param_driverinit_value_set(devlink,
					   DEVLINK_PARAM_GENERIC_ID_INT_ERR_RESET,
					   value);

	value.vu32 = 1UL << log_num_mac;
	devlink_param_driverinit_value_set(devlink,
					   DEVLINK_PARAM_GENERIC_ID_MAX_MACS,
					   value);

	value.vbool = enable_64b_cqe_eqe;
	devlink_param_driverinit_value_set(devlink,
					   MLX4_DEVLINK_PARAM_ID_ENABLE_64B_CQE_EQE,
					   value);

	value.vbool = enable_4k_uar;
	devlink_param_driverinit_value_set(devlink,
					   MLX4_DEVLINK_PARAM_ID_ENABLE_4K_UAR,
					   value);

	value.vbool = false;
	devlink_param_driverinit_value_set(devlink,
					   DEVLINK_PARAM_GENERIC_ID_REGION_SNAPSHOT,
					   value);
पूर्ण

अटल अंतरभूत व्योम mlx4_set_num_reserved_uars(काष्ठा mlx4_dev *dev,
					      काष्ठा mlx4_dev_cap *dev_cap)
अणु
	/* The reserved_uars is calculated by प्रणाली page size unit.
	 * Thereक्रमe, adjusपंचांगent is added when the uar page size is less
	 * than the प्रणाली page size
	 */
	dev->caps.reserved_uars	=
		max_t(पूर्णांक,
		      mlx4_get_num_reserved_uar(dev),
		      dev_cap->reserved_uars /
			(1 << (PAGE_SHIFT - dev->uar_page_shअगरt)));
पूर्ण

पूर्णांक mlx4_check_port_params(काष्ठा mlx4_dev *dev,
			   क्रमागत mlx4_port_type *port_type)
अणु
	पूर्णांक i;

	अगर (!(dev->caps.flags & MLX4_DEV_CAP_FLAG_DPDP)) अणु
		क्रम (i = 0; i < dev->caps.num_ports - 1; i++) अणु
			अगर (port_type[i] != port_type[i + 1]) अणु
				mlx4_err(dev, "Only same port types supported on this HCA, aborting\n");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dev->caps.num_ports; i++) अणु
		अगर (!(port_type[i] & dev->caps.supported_type[i+1])) अणु
			mlx4_err(dev, "Requested port type for port %d is not supported on this HCA\n",
				 i + 1);
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mlx4_set_port_mask(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 1; i <= dev->caps.num_ports; ++i)
		dev->caps.port_mask[i] = dev->caps.port_type[i];
पूर्ण

क्रमागत अणु
	MLX4_QUERY_FUNC_NUM_SYS_EQS = 1 << 0,
पूर्ण;

अटल पूर्णांक mlx4_query_func(काष्ठा mlx4_dev *dev, काष्ठा mlx4_dev_cap *dev_cap)
अणु
	पूर्णांक err = 0;
	काष्ठा mlx4_func func;

	अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SYS_EQS) अणु
		err = mlx4_QUERY_FUNC(dev, &func, 0);
		अगर (err) अणु
			mlx4_err(dev, "QUERY_DEV_CAP command failed, aborting.\n");
			वापस err;
		पूर्ण
		dev_cap->max_eqs = func.max_eq;
		dev_cap->reserved_eqs = func.rsvd_eqs;
		dev_cap->reserved_uars = func.rsvd_uars;
		err |= MLX4_QUERY_FUNC_NUM_SYS_EQS;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम mlx4_enable_cqe_eqe_stride(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_caps *dev_cap = &dev->caps;

	/* FW not supporting or cancelled by user */
	अगर (!(dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_EQE_STRIDE) ||
	    !(dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_CQE_STRIDE))
		वापस;

	/* Must have 64B CQE_EQE enabled by FW to use bigger stride
	 * When FW has NCSI it may decide not to report 64B CQE/EQEs
	 */
	अगर (!(dev_cap->flags & MLX4_DEV_CAP_FLAG_64B_EQE) ||
	    !(dev_cap->flags & MLX4_DEV_CAP_FLAG_64B_CQE)) अणु
		dev_cap->flags2 &= ~MLX4_DEV_CAP_FLAG2_CQE_STRIDE;
		dev_cap->flags2 &= ~MLX4_DEV_CAP_FLAG2_EQE_STRIDE;
		वापस;
	पूर्ण

	अगर (cache_line_size() == 128 || cache_line_size() == 256) अणु
		mlx4_dbg(dev, "Enabling CQE stride cacheLine supported\n");
		/* Changing the real data inside CQE size to 32B */
		dev_cap->flags &= ~MLX4_DEV_CAP_FLAG_64B_CQE;
		dev_cap->flags &= ~MLX4_DEV_CAP_FLAG_64B_EQE;

		अगर (mlx4_is_master(dev))
			dev_cap->function_caps |= MLX4_FUNC_CAP_EQE_CQE_STRIDE;
	पूर्ण अन्यथा अणु
		अगर (cache_line_size() != 32  && cache_line_size() != 64)
			mlx4_dbg(dev, "Disabling CQE stride, cacheLine size unsupported\n");
		dev_cap->flags2 &= ~MLX4_DEV_CAP_FLAG2_CQE_STRIDE;
		dev_cap->flags2 &= ~MLX4_DEV_CAP_FLAG2_EQE_STRIDE;
	पूर्ण
पूर्ण

अटल पूर्णांक _mlx4_dev_port(काष्ठा mlx4_dev *dev, पूर्णांक port,
			  काष्ठा mlx4_port_cap *port_cap)
अणु
	dev->caps.vl_cap[port]	    = port_cap->max_vl;
	dev->caps.ib_mtu_cap[port]	    = port_cap->ib_mtu;
	dev->phys_caps.gid_phys_table_len[port]  = port_cap->max_gids;
	dev->phys_caps.pkey_phys_table_len[port] = port_cap->max_pkeys;
	/* set gid and pkey table operating lengths by शेष
	 * to non-sriov values
	 */
	dev->caps.gid_table_len[port]  = port_cap->max_gids;
	dev->caps.pkey_table_len[port] = port_cap->max_pkeys;
	dev->caps.port_width_cap[port] = port_cap->max_port_width;
	dev->caps.eth_mtu_cap[port]    = port_cap->eth_mtu;
	dev->caps.max_tc_eth	       = port_cap->max_tc_eth;
	dev->caps.def_mac[port]        = port_cap->def_mac;
	dev->caps.supported_type[port] = port_cap->supported_port_types;
	dev->caps.suggested_type[port] = port_cap->suggested_type;
	dev->caps.शेष_sense[port] = port_cap->शेष_sense;
	dev->caps.trans_type[port]	    = port_cap->trans_type;
	dev->caps.venकरोr_oui[port]     = port_cap->venकरोr_oui;
	dev->caps.wavelength[port]     = port_cap->wavelength;
	dev->caps.trans_code[port]     = port_cap->trans_code;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_dev_port(काष्ठा mlx4_dev *dev, पूर्णांक port,
			 काष्ठा mlx4_port_cap *port_cap)
अणु
	पूर्णांक err = 0;

	err = mlx4_QUERY_PORT(dev, port, port_cap);

	अगर (err)
		mlx4_err(dev, "QUERY_PORT command failed.\n");

	वापस err;
पूर्ण

अटल अंतरभूत व्योम mlx4_enable_ignore_fcs(काष्ठा mlx4_dev *dev)
अणु
	अगर (!(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_IGNORE_FCS))
		वापस;

	अगर (mlx4_is_mfunc(dev)) अणु
		mlx4_dbg(dev, "SRIOV mode - Disabling Ignore FCS");
		dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_IGNORE_FCS;
		वापस;
	पूर्ण

	अगर (!(dev->caps.flags & MLX4_DEV_CAP_FLAG_FCS_KEEP)) अणु
		mlx4_dbg(dev,
			 "Keep FCS is not supported - Disabling Ignore FCS");
		dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_IGNORE_FCS;
		वापस;
	पूर्ण
पूर्ण

#घोषणा MLX4_A0_STEERING_TABLE_SIZE	256
अटल पूर्णांक mlx4_dev_cap(काष्ठा mlx4_dev *dev, काष्ठा mlx4_dev_cap *dev_cap)
अणु
	पूर्णांक err;
	पूर्णांक i;

	err = mlx4_QUERY_DEV_CAP(dev, dev_cap);
	अगर (err) अणु
		mlx4_err(dev, "QUERY_DEV_CAP command failed, aborting\n");
		वापस err;
	पूर्ण
	mlx4_dev_cap_dump(dev, dev_cap);

	अगर (dev_cap->min_page_sz > PAGE_SIZE) अणु
		mlx4_err(dev, "HCA minimum page size of %d bigger than kernel PAGE_SIZE of %ld, aborting\n",
			 dev_cap->min_page_sz, PAGE_SIZE);
		वापस -ENODEV;
	पूर्ण
	अगर (dev_cap->num_ports > MLX4_MAX_PORTS) अणु
		mlx4_err(dev, "HCA has %d ports, but we only support %d, aborting\n",
			 dev_cap->num_ports, MLX4_MAX_PORTS);
		वापस -ENODEV;
	पूर्ण

	अगर (dev_cap->uar_size > pci_resource_len(dev->persist->pdev, 2)) अणु
		mlx4_err(dev, "HCA reported UAR size of 0x%x bigger than PCI resource 2 size of 0x%llx, aborting\n",
			 dev_cap->uar_size,
			 (अचिन्हित दीर्घ दीर्घ)
			 pci_resource_len(dev->persist->pdev, 2));
		वापस -ENODEV;
	पूर्ण

	dev->caps.num_ports	     = dev_cap->num_ports;
	dev->caps.num_sys_eqs = dev_cap->num_sys_eqs;
	dev->phys_caps.num_phys_eqs = dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_SYS_EQS ?
				      dev->caps.num_sys_eqs :
				      MLX4_MAX_EQ_NUM;
	क्रम (i = 1; i <= dev->caps.num_ports; ++i) अणु
		err = _mlx4_dev_port(dev, i, dev_cap->port_cap + i);
		अगर (err) अणु
			mlx4_err(dev, "QUERY_PORT command failed, aborting\n");
			वापस err;
		पूर्ण
	पूर्ण

	dev->caps.map_घड़ी_प्रकारo_user  = dev_cap->map_घड़ी_प्रकारo_user;
	dev->caps.uar_page_size	     = PAGE_SIZE;
	dev->caps.num_uars	     = dev_cap->uar_size / PAGE_SIZE;
	dev->caps.local_ca_ack_delay = dev_cap->local_ca_ack_delay;
	dev->caps.bf_reg_size	     = dev_cap->bf_reg_size;
	dev->caps.bf_regs_per_page   = dev_cap->bf_regs_per_page;
	dev->caps.max_sq_sg	     = dev_cap->max_sq_sg;
	dev->caps.max_rq_sg	     = dev_cap->max_rq_sg;
	dev->caps.max_wqes	     = dev_cap->max_qp_sz;
	dev->caps.max_qp_init_rdma   = dev_cap->max_requester_per_qp;
	dev->caps.max_srq_wqes	     = dev_cap->max_srq_sz;
	dev->caps.max_srq_sge	     = dev_cap->max_rq_sg - 1;
	dev->caps.reserved_srqs	     = dev_cap->reserved_srqs;
	dev->caps.max_sq_desc_sz     = dev_cap->max_sq_desc_sz;
	dev->caps.max_rq_desc_sz     = dev_cap->max_rq_desc_sz;
	/*
	 * Subtract 1 from the limit because we need to allocate a
	 * spare CQE to enable resizing the CQ.
	 */
	dev->caps.max_cqes	     = dev_cap->max_cq_sz - 1;
	dev->caps.reserved_cqs	     = dev_cap->reserved_cqs;
	dev->caps.reserved_eqs	     = dev_cap->reserved_eqs;
	dev->caps.reserved_mtts      = dev_cap->reserved_mtts;
	dev->caps.reserved_mrws	     = dev_cap->reserved_mrws;

	dev->caps.reserved_pds	     = dev_cap->reserved_pds;
	dev->caps.reserved_xrcds     = (dev->caps.flags & MLX4_DEV_CAP_FLAG_XRC) ?
					dev_cap->reserved_xrcds : 0;
	dev->caps.max_xrcds          = (dev->caps.flags & MLX4_DEV_CAP_FLAG_XRC) ?
					dev_cap->max_xrcds : 0;
	dev->caps.mtt_entry_sz       = dev_cap->mtt_entry_sz;

	dev->caps.max_msg_sz         = dev_cap->max_msg_sz;
	dev->caps.page_size_cap	     = ~(u32) (dev_cap->min_page_sz - 1);
	dev->caps.flags		     = dev_cap->flags;
	dev->caps.flags2	     = dev_cap->flags2;
	dev->caps.bmme_flags	     = dev_cap->bmme_flags;
	dev->caps.reserved_lkey	     = dev_cap->reserved_lkey;
	dev->caps.stat_rate_support  = dev_cap->stat_rate_support;
	dev->caps.max_gso_sz	     = dev_cap->max_gso_sz;
	dev->caps.max_rss_tbl_sz     = dev_cap->max_rss_tbl_sz;
	dev->caps.wol_port[1]          = dev_cap->wol_port[1];
	dev->caps.wol_port[2]          = dev_cap->wol_port[2];
	dev->caps.health_buffer_addrs  = dev_cap->health_buffer_addrs;

	/* Save uar page shअगरt */
	अगर (!mlx4_is_slave(dev)) अणु
		/* Virtual PCI function needs to determine UAR page size from
		 * firmware. Only master PCI function can set the uar page size
		 */
		अगर (enable_4k_uar || !dev->persist->num_vfs)
			dev->uar_page_shअगरt = DEFAULT_UAR_PAGE_SHIFT;
		अन्यथा
			dev->uar_page_shअगरt = PAGE_SHIFT;

		mlx4_set_num_reserved_uars(dev, dev_cap);
	पूर्ण

	अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_PHV_EN) अणु
		काष्ठा mlx4_init_hca_param hca_param;

		स_रखो(&hca_param, 0, माप(hca_param));
		err = mlx4_QUERY_HCA(dev, &hca_param);
		/* Turn off PHV_EN flag in हाल phv_check_en is set.
		 * phv_check_en is a HW check that parse the packet and verअगरy
		 * phv bit was reported correctly in the wqe. To allow QinQ
		 * PHV_EN flag should be set and phv_check_en must be cleared
		 * otherwise QinQ packets will be drop by the HW.
		 */
		अगर (err || hca_param.phv_check_en)
			dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_PHV_EN;
	पूर्ण

	/* Sense port always allowed on supported devices क्रम ConnectX-1 and -2 */
	अगर (mlx4_priv(dev)->pci_dev_data & MLX4_PCI_DEV_FORCE_SENSE_PORT)
		dev->caps.flags |= MLX4_DEV_CAP_FLAG_SENSE_SUPPORT;
	/* Don't करो sense port on multअगरunction devices (क्रम now at least) */
	अगर (mlx4_is_mfunc(dev))
		dev->caps.flags &= ~MLX4_DEV_CAP_FLAG_SENSE_SUPPORT;

	अगर (mlx4_low_memory_profile()) अणु
		dev->caps.log_num_macs  = MLX4_MIN_LOG_NUM_MAC;
		dev->caps.log_num_vlans = MLX4_MIN_LOG_NUM_VLANS;
	पूर्ण अन्यथा अणु
		dev->caps.log_num_macs  = log_num_mac;
		dev->caps.log_num_vlans = MLX4_LOG_NUM_VLANS;
	पूर्ण

	क्रम (i = 1; i <= dev->caps.num_ports; ++i) अणु
		dev->caps.port_type[i] = MLX4_PORT_TYPE_NONE;
		अगर (dev->caps.supported_type[i]) अणु
			/* अगर only ETH is supported - assign ETH */
			अगर (dev->caps.supported_type[i] == MLX4_PORT_TYPE_ETH)
				dev->caps.port_type[i] = MLX4_PORT_TYPE_ETH;
			/* अगर only IB is supported, assign IB */
			अन्यथा अगर (dev->caps.supported_type[i] ==
				 MLX4_PORT_TYPE_IB)
				dev->caps.port_type[i] = MLX4_PORT_TYPE_IB;
			अन्यथा अणु
				/* अगर IB and ETH are supported, we set the port
				 * type according to user selection of port type;
				 * अगर user selected none, take the FW hपूर्णांक */
				अगर (port_type_array[i - 1] == MLX4_PORT_TYPE_NONE)
					dev->caps.port_type[i] = dev->caps.suggested_type[i] ?
						MLX4_PORT_TYPE_ETH : MLX4_PORT_TYPE_IB;
				अन्यथा
					dev->caps.port_type[i] = port_type_array[i - 1];
			पूर्ण
		पूर्ण
		/*
		 * Link sensing is allowed on the port अगर 3 conditions are true:
		 * 1. Both protocols are supported on the port.
		 * 2. Dअगरferent types are supported on the port
		 * 3. FW declared that it supports link sensing
		 */
		mlx4_priv(dev)->sense.sense_allowed[i] =
			((dev->caps.supported_type[i] == MLX4_PORT_TYPE_AUTO) &&
			 (dev->caps.flags & MLX4_DEV_CAP_FLAG_DPDP) &&
			 (dev->caps.flags & MLX4_DEV_CAP_FLAG_SENSE_SUPPORT));

		/*
		 * If "default_sense" bit is set, we move the port to "AUTO" mode
		 * and perक्रमm sense_port FW command to try and set the correct
		 * port type from beginning
		 */
		अगर (mlx4_priv(dev)->sense.sense_allowed[i] && dev->caps.शेष_sense[i]) अणु
			क्रमागत mlx4_port_type sensed_port = MLX4_PORT_TYPE_NONE;
			dev->caps.possible_type[i] = MLX4_PORT_TYPE_AUTO;
			mlx4_SENSE_PORT(dev, i, &sensed_port);
			अगर (sensed_port != MLX4_PORT_TYPE_NONE)
				dev->caps.port_type[i] = sensed_port;
		पूर्ण अन्यथा अणु
			dev->caps.possible_type[i] = dev->caps.port_type[i];
		पूर्ण

		अगर (dev->caps.log_num_macs > dev_cap->port_cap[i].log_max_macs) अणु
			dev->caps.log_num_macs = dev_cap->port_cap[i].log_max_macs;
			mlx4_warn(dev, "Requested number of MACs is too much for port %d, reducing to %d\n",
				  i, 1 << dev->caps.log_num_macs);
		पूर्ण
		अगर (dev->caps.log_num_vlans > dev_cap->port_cap[i].log_max_vlans) अणु
			dev->caps.log_num_vlans = dev_cap->port_cap[i].log_max_vlans;
			mlx4_warn(dev, "Requested number of VLANs is too much for port %d, reducing to %d\n",
				  i, 1 << dev->caps.log_num_vlans);
		पूर्ण
	पूर्ण

	अगर (mlx4_is_master(dev) && (dev->caps.num_ports == 2) &&
	    (port_type_array[0] == MLX4_PORT_TYPE_IB) &&
	    (port_type_array[1] == MLX4_PORT_TYPE_ETH)) अणु
		mlx4_warn(dev,
			  "Granular QoS per VF not supported with IB/Eth configuration\n");
		dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_QOS_VPP;
	पूर्ण

	dev->caps.max_counters = dev_cap->max_counters;

	dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW] = dev_cap->reserved_qps;
	dev->caps.reserved_qps_cnt[MLX4_QP_REGION_ETH_ADDR] =
		dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FC_ADDR] =
		(1 << dev->caps.log_num_macs) *
		(1 << dev->caps.log_num_vlans) *
		dev->caps.num_ports;
	dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FC_EXCH] = MLX4_NUM_FEXCH;

	अगर (dev_cap->dmfs_high_rate_qpn_base > 0 &&
	    dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_FS_EN)
		dev->caps.dmfs_high_rate_qpn_base = dev_cap->dmfs_high_rate_qpn_base;
	अन्यथा
		dev->caps.dmfs_high_rate_qpn_base =
			dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW];

	अगर (dev_cap->dmfs_high_rate_qpn_range > 0 &&
	    dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_FS_EN) अणु
		dev->caps.dmfs_high_rate_qpn_range = dev_cap->dmfs_high_rate_qpn_range;
		dev->caps.dmfs_high_steer_mode = MLX4_STEERING_DMFS_A0_DEFAULT;
		dev->caps.flags2 |= MLX4_DEV_CAP_FLAG2_FS_A0;
	पूर्ण अन्यथा अणु
		dev->caps.dmfs_high_steer_mode = MLX4_STEERING_DMFS_A0_NOT_SUPPORTED;
		dev->caps.dmfs_high_rate_qpn_base =
			dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW];
		dev->caps.dmfs_high_rate_qpn_range = MLX4_A0_STEERING_TABLE_SIZE;
	पूर्ण

	dev->caps.rl_caps = dev_cap->rl_caps;

	dev->caps.reserved_qps_cnt[MLX4_QP_REGION_RSS_RAW_ETH] =
		dev->caps.dmfs_high_rate_qpn_range;

	dev->caps.reserved_qps = dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW] +
		dev->caps.reserved_qps_cnt[MLX4_QP_REGION_ETH_ADDR] +
		dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FC_ADDR] +
		dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FC_EXCH];

	dev->caps.sqp_demux = (mlx4_is_master(dev)) ? MLX4_MAX_NUM_SLAVES : 0;

	अगर (!enable_64b_cqe_eqe && !mlx4_is_slave(dev)) अणु
		अगर (dev_cap->flags &
		    (MLX4_DEV_CAP_FLAG_64B_CQE | MLX4_DEV_CAP_FLAG_64B_EQE)) अणु
			mlx4_warn(dev, "64B EQEs/CQEs supported by the device but not enabled\n");
			dev->caps.flags &= ~MLX4_DEV_CAP_FLAG_64B_CQE;
			dev->caps.flags &= ~MLX4_DEV_CAP_FLAG_64B_EQE;
		पूर्ण

		अगर (dev_cap->flags2 &
		    (MLX4_DEV_CAP_FLAG2_CQE_STRIDE |
		     MLX4_DEV_CAP_FLAG2_EQE_STRIDE)) अणु
			mlx4_warn(dev, "Disabling EQE/CQE stride per user request\n");
			dev_cap->flags2 &= ~MLX4_DEV_CAP_FLAG2_CQE_STRIDE;
			dev_cap->flags2 &= ~MLX4_DEV_CAP_FLAG2_EQE_STRIDE;
		पूर्ण
	पूर्ण

	अगर ((dev->caps.flags &
	    (MLX4_DEV_CAP_FLAG_64B_CQE | MLX4_DEV_CAP_FLAG_64B_EQE)) &&
	    mlx4_is_master(dev))
		dev->caps.function_caps |= MLX4_FUNC_CAP_64B_EQE_CQE;

	अगर (!mlx4_is_slave(dev)) अणु
		mlx4_enable_cqe_eqe_stride(dev);
		dev->caps.alloc_res_qp_mask =
			(dev->caps.bf_reg_size ? MLX4_RESERVE_ETH_BF_QP : 0) |
			MLX4_RESERVE_A0_QP;

		अगर (!(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ETS_CFG) &&
		    dev->caps.flags & MLX4_DEV_CAP_FLAG_SET_ETH_SCHED) अणु
			mlx4_warn(dev, "Old device ETS support detected\n");
			mlx4_warn(dev, "Consider upgrading device FW.\n");
			dev->caps.flags2 |= MLX4_DEV_CAP_FLAG2_ETS_CFG;
		पूर्ण

	पूर्ण अन्यथा अणु
		dev->caps.alloc_res_qp_mask = 0;
	पूर्ण

	mlx4_enable_ignore_fcs(dev);

	वापस 0;
पूर्ण

/*The function checks अगर there are live vf, वापस the num of them*/
अटल पूर्णांक mlx4_how_many_lives_vf(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_state *s_state;
	पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 1/*the ppf is 0*/; i < dev->num_slaves; ++i) अणु
		s_state = &priv->mfunc.master.slave_state[i];
		अगर (s_state->active && s_state->last_cmd !=
		    MLX4_COMM_CMD_RESET) अणु
			mlx4_warn(dev, "%s: slave: %d is still active\n",
				  __func__, i);
			ret++;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक mlx4_get_parav_qkey(काष्ठा mlx4_dev *dev, u32 qpn, u32 *qkey)
अणु
	u32 qk = MLX4_RESERVED_QKEY_BASE;

	अगर (qpn >= dev->phys_caps.base_tunnel_sqpn + 8 * MLX4_MFUNC_MAX ||
	    qpn < dev->phys_caps.base_proxy_sqpn)
		वापस -EINVAL;

	अगर (qpn >= dev->phys_caps.base_tunnel_sqpn)
		/* tunnel qp */
		qk += qpn - dev->phys_caps.base_tunnel_sqpn;
	अन्यथा
		qk += qpn - dev->phys_caps.base_proxy_sqpn;
	*qkey = qk;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlx4_get_parav_qkey);

व्योम mlx4_sync_pkey_table(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port, पूर्णांक i, पूर्णांक val)
अणु
	काष्ठा mlx4_priv *priv = container_of(dev, काष्ठा mlx4_priv, dev);

	अगर (!mlx4_is_master(dev))
		वापस;

	priv->virt2phys_pkey[slave][port - 1][i] = val;
पूर्ण
EXPORT_SYMBOL(mlx4_sync_pkey_table);

व्योम mlx4_put_slave_node_guid(काष्ठा mlx4_dev *dev, पूर्णांक slave, __be64 guid)
अणु
	काष्ठा mlx4_priv *priv = container_of(dev, काष्ठा mlx4_priv, dev);

	अगर (!mlx4_is_master(dev))
		वापस;

	priv->slave_node_guids[slave] = guid;
पूर्ण
EXPORT_SYMBOL(mlx4_put_slave_node_guid);

__be64 mlx4_get_slave_node_guid(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = container_of(dev, काष्ठा mlx4_priv, dev);

	अगर (!mlx4_is_master(dev))
		वापस 0;

	वापस priv->slave_node_guids[slave];
पूर्ण
EXPORT_SYMBOL(mlx4_get_slave_node_guid);

पूर्णांक mlx4_is_slave_active(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_state *s_slave;

	अगर (!mlx4_is_master(dev))
		वापस 0;

	s_slave = &priv->mfunc.master.slave_state[slave];
	वापस !!s_slave->active;
पूर्ण
EXPORT_SYMBOL(mlx4_is_slave_active);

व्योम mlx4_handle_eth_header_mcast_prio(काष्ठा mlx4_net_trans_rule_hw_ctrl *ctrl,
				       काष्ठा _rule_hw *eth_header)
अणु
	अगर (is_multicast_ether_addr(eth_header->eth.dst_mac) ||
	    is_broadcast_ether_addr(eth_header->eth.dst_mac)) अणु
		काष्ठा mlx4_net_trans_rule_hw_eth *eth =
			(काष्ठा mlx4_net_trans_rule_hw_eth *)eth_header;
		काष्ठा _rule_hw *next_rule = (काष्ठा _rule_hw *)(eth + 1);
		bool last_rule = next_rule->size == 0 && next_rule->id == 0 &&
			next_rule->rsvd == 0;

		अगर (last_rule)
			ctrl->prio = cpu_to_be16(MLX4_DOMAIN_NIC);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mlx4_handle_eth_header_mcast_prio);

अटल व्योम slave_adjust_steering_mode(काष्ठा mlx4_dev *dev,
				       काष्ठा mlx4_dev_cap *dev_cap,
				       काष्ठा mlx4_init_hca_param *hca_param)
अणु
	dev->caps.steering_mode = hca_param->steering_mode;
	अगर (dev->caps.steering_mode == MLX4_STEERING_MODE_DEVICE_MANAGED) अणु
		dev->caps.num_qp_per_mgm = dev_cap->fs_max_num_qp_per_entry;
		dev->caps.fs_log_max_ucast_qp_range_size =
			dev_cap->fs_log_max_ucast_qp_range_size;
	पूर्ण अन्यथा
		dev->caps.num_qp_per_mgm =
			4 * ((1 << hca_param->log_mc_entry_sz)/16 - 2);

	mlx4_dbg(dev, "Steering mode is: %s\n",
		 mlx4_steering_mode_str(dev->caps.steering_mode));
पूर्ण

अटल व्योम mlx4_slave_destroy_special_qp_cap(काष्ठा mlx4_dev *dev)
अणु
	kमुक्त(dev->caps.spec_qps);
	dev->caps.spec_qps = शून्य;
पूर्ण

अटल पूर्णांक mlx4_slave_special_qp_cap(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_func_cap *func_cap = शून्य;
	काष्ठा mlx4_caps *caps = &dev->caps;
	पूर्णांक i, err = 0;

	func_cap = kzalloc(माप(*func_cap), GFP_KERNEL);
	caps->spec_qps = kसुस्मृति(caps->num_ports, माप(*caps->spec_qps), GFP_KERNEL);

	अगर (!func_cap || !caps->spec_qps) अणु
		mlx4_err(dev, "Failed to allocate memory for special qps cap\n");
		err = -ENOMEM;
		जाओ err_mem;
	पूर्ण

	क्रम (i = 1; i <= caps->num_ports; ++i) अणु
		err = mlx4_QUERY_FUNC_CAP(dev, i, func_cap);
		अगर (err) अणु
			mlx4_err(dev, "QUERY_FUNC_CAP port command failed for port %d, aborting (%d)\n",
				 i, err);
			जाओ err_mem;
		पूर्ण
		caps->spec_qps[i - 1] = func_cap->spec_qps;
		caps->port_mask[i] = caps->port_type[i];
		caps->phys_port_id[i] = func_cap->phys_port_id;
		err = mlx4_get_slave_pkey_gid_tbl_len(dev, i,
						      &caps->gid_table_len[i],
						      &caps->pkey_table_len[i]);
		अगर (err) अणु
			mlx4_err(dev, "QUERY_PORT command failed for port %d, aborting (%d)\n",
				 i, err);
			जाओ err_mem;
		पूर्ण
	पूर्ण

err_mem:
	अगर (err)
		mlx4_slave_destroy_special_qp_cap(dev);
	kमुक्त(func_cap);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_slave_cap(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक			   err;
	u32			   page_size;
	काष्ठा mlx4_dev_cap	   *dev_cap = शून्य;
	काष्ठा mlx4_func_cap	   *func_cap = शून्य;
	काष्ठा mlx4_init_hca_param *hca_param = शून्य;

	hca_param = kzalloc(माप(*hca_param), GFP_KERNEL);
	func_cap = kzalloc(माप(*func_cap), GFP_KERNEL);
	dev_cap = kzalloc(माप(*dev_cap), GFP_KERNEL);
	अगर (!hca_param || !func_cap || !dev_cap) अणु
		mlx4_err(dev, "Failed to allocate memory for slave_cap\n");
		err = -ENOMEM;
		जाओ मुक्त_mem;
	पूर्ण

	err = mlx4_QUERY_HCA(dev, hca_param);
	अगर (err) अणु
		mlx4_err(dev, "QUERY_HCA command failed, aborting\n");
		जाओ मुक्त_mem;
	पूर्ण

	/* fail अगर the hca has an unknown global capability
	 * at this समय global_caps should be always zeroed
	 */
	अगर (hca_param->global_caps) अणु
		mlx4_err(dev, "Unknown hca global capabilities\n");
		err = -EINVAL;
		जाओ मुक्त_mem;
	पूर्ण

	dev->caps.hca_core_घड़ी = hca_param->hca_core_घड़ी;

	dev->caps.max_qp_dest_rdma = 1 << hca_param->log_rd_per_qp;
	err = mlx4_dev_cap(dev, dev_cap);
	अगर (err) अणु
		mlx4_err(dev, "QUERY_DEV_CAP command failed, aborting\n");
		जाओ मुक्त_mem;
	पूर्ण

	err = mlx4_QUERY_FW(dev);
	अगर (err)
		mlx4_err(dev, "QUERY_FW command failed: could not get FW version\n");

	page_size = ~dev->caps.page_size_cap + 1;
	mlx4_warn(dev, "HCA minimum page size:%d\n", page_size);
	अगर (page_size > PAGE_SIZE) अणु
		mlx4_err(dev, "HCA minimum page size of %d bigger than kernel PAGE_SIZE of %ld, aborting\n",
			 page_size, PAGE_SIZE);
		err = -ENODEV;
		जाओ मुक्त_mem;
	पूर्ण

	/* Set uar_page_shअगरt क्रम VF */
	dev->uar_page_shअगरt = hca_param->uar_page_sz + 12;

	/* Make sure the master uar page size is valid */
	अगर (dev->uar_page_shअगरt > PAGE_SHIFT) अणु
		mlx4_err(dev,
			 "Invalid configuration: uar page size is larger than system page size\n");
		err = -ENODEV;
		जाओ मुक्त_mem;
	पूर्ण

	/* Set reserved_uars based on the uar_page_shअगरt */
	mlx4_set_num_reserved_uars(dev, dev_cap);

	/* Although uar page size in FW dअगरfers from प्रणाली page size,
	 * upper software layers (mlx4_ib, mlx4_en and part of mlx4_core)
	 * still works with assumption that uar page size == प्रणाली page size
	 */
	dev->caps.uar_page_size = PAGE_SIZE;

	err = mlx4_QUERY_FUNC_CAP(dev, 0, func_cap);
	अगर (err) अणु
		mlx4_err(dev, "QUERY_FUNC_CAP general command failed, aborting (%d)\n",
			 err);
		जाओ मुक्त_mem;
	पूर्ण

	अगर ((func_cap->pf_context_behaviour | PF_CONTEXT_BEHAVIOUR_MASK) !=
	    PF_CONTEXT_BEHAVIOUR_MASK) अणु
		mlx4_err(dev, "Unknown pf context behaviour %x known flags %x\n",
			 func_cap->pf_context_behaviour,
			 PF_CONTEXT_BEHAVIOUR_MASK);
		err = -EINVAL;
		जाओ मुक्त_mem;
	पूर्ण

	dev->caps.num_ports		= func_cap->num_ports;
	dev->quotas.qp			= func_cap->qp_quota;
	dev->quotas.srq			= func_cap->srq_quota;
	dev->quotas.cq			= func_cap->cq_quota;
	dev->quotas.mpt			= func_cap->mpt_quota;
	dev->quotas.mtt			= func_cap->mtt_quota;
	dev->caps.num_qps		= 1 << hca_param->log_num_qps;
	dev->caps.num_srqs		= 1 << hca_param->log_num_srqs;
	dev->caps.num_cqs		= 1 << hca_param->log_num_cqs;
	dev->caps.num_mpts		= 1 << hca_param->log_mpt_sz;
	dev->caps.num_eqs		= func_cap->max_eq;
	dev->caps.reserved_eqs		= func_cap->reserved_eq;
	dev->caps.reserved_lkey		= func_cap->reserved_lkey;
	dev->caps.num_pds               = MLX4_NUM_PDS;
	dev->caps.num_mgms              = 0;
	dev->caps.num_amgms             = 0;

	अगर (dev->caps.num_ports > MLX4_MAX_PORTS) अणु
		mlx4_err(dev, "HCA has %d ports, but we only support %d, aborting\n",
			 dev->caps.num_ports, MLX4_MAX_PORTS);
		err = -ENODEV;
		जाओ मुक्त_mem;
	पूर्ण

	mlx4_replace_zero_macs(dev);

	err = mlx4_slave_special_qp_cap(dev);
	अगर (err) अणु
		mlx4_err(dev, "Set special QP caps failed. aborting\n");
		जाओ मुक्त_mem;
	पूर्ण

	अगर (dev->caps.uar_page_size * (dev->caps.num_uars -
				       dev->caps.reserved_uars) >
				       pci_resource_len(dev->persist->pdev,
							2)) अणु
		mlx4_err(dev, "HCA reported UAR region size of 0x%x bigger than PCI resource 2 size of 0x%llx, aborting\n",
			 dev->caps.uar_page_size * dev->caps.num_uars,
			 (अचिन्हित दीर्घ दीर्घ)
			 pci_resource_len(dev->persist->pdev, 2));
		err = -ENOMEM;
		जाओ err_mem;
	पूर्ण

	अगर (hca_param->dev_cap_enabled & MLX4_DEV_CAP_64B_EQE_ENABLED) अणु
		dev->caps.eqe_size   = 64;
		dev->caps.eqe_factor = 1;
	पूर्ण अन्यथा अणु
		dev->caps.eqe_size   = 32;
		dev->caps.eqe_factor = 0;
	पूर्ण

	अगर (hca_param->dev_cap_enabled & MLX4_DEV_CAP_64B_CQE_ENABLED) अणु
		dev->caps.cqe_size   = 64;
		dev->caps.userspace_caps |= MLX4_USER_DEV_CAP_LARGE_CQE;
	पूर्ण अन्यथा अणु
		dev->caps.cqe_size   = 32;
	पूर्ण

	अगर (hca_param->dev_cap_enabled & MLX4_DEV_CAP_EQE_STRIDE_ENABLED) अणु
		dev->caps.eqe_size = hca_param->eqe_size;
		dev->caps.eqe_factor = 0;
	पूर्ण

	अगर (hca_param->dev_cap_enabled & MLX4_DEV_CAP_CQE_STRIDE_ENABLED) अणु
		dev->caps.cqe_size = hca_param->cqe_size;
		/* User still need to know when CQE > 32B */
		dev->caps.userspace_caps |= MLX4_USER_DEV_CAP_LARGE_CQE;
	पूर्ण

	dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_TS;
	mlx4_warn(dev, "Timestamping is not supported in slave mode\n");

	dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_USER_MAC_EN;
	mlx4_dbg(dev, "User MAC FW update is not supported in slave mode\n");

	slave_adjust_steering_mode(dev, dev_cap, hca_param);
	mlx4_dbg(dev, "RSS support for IP fragments is %s\n",
		 hca_param->rss_ip_frags ? "on" : "off");

	अगर (func_cap->extra_flags & MLX4_QUERY_FUNC_FLAGS_BF_RES_QP &&
	    dev->caps.bf_reg_size)
		dev->caps.alloc_res_qp_mask |= MLX4_RESERVE_ETH_BF_QP;

	अगर (func_cap->extra_flags & MLX4_QUERY_FUNC_FLAGS_A0_RES_QP)
		dev->caps.alloc_res_qp_mask |= MLX4_RESERVE_A0_QP;

err_mem:
	अगर (err)
		mlx4_slave_destroy_special_qp_cap(dev);
मुक्त_mem:
	kमुक्त(hca_param);
	kमुक्त(func_cap);
	kमुक्त(dev_cap);
	वापस err;
पूर्ण

अटल व्योम mlx4_request_modules(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक port;
	पूर्णांक has_ib_port = false;
	पूर्णांक has_eth_port = false;
#घोषणा EN_DRV_NAME	"mlx4_en"
#घोषणा IB_DRV_NAME	"mlx4_ib"

	क्रम (port = 1; port <= dev->caps.num_ports; port++) अणु
		अगर (dev->caps.port_type[port] == MLX4_PORT_TYPE_IB)
			has_ib_port = true;
		अन्यथा अगर (dev->caps.port_type[port] == MLX4_PORT_TYPE_ETH)
			has_eth_port = true;
	पूर्ण

	अगर (has_eth_port)
		request_module_noरुको(EN_DRV_NAME);
	अगर (has_ib_port || (dev->caps.flags & MLX4_DEV_CAP_FLAG_IBOE))
		request_module_noरुको(IB_DRV_NAME);
पूर्ण

/*
 * Change the port configuration of the device.
 * Every user of this function must hold the port mutex.
 */
पूर्णांक mlx4_change_port_types(काष्ठा mlx4_dev *dev,
			   क्रमागत mlx4_port_type *port_types)
अणु
	पूर्णांक err = 0;
	पूर्णांक change = 0;
	पूर्णांक port;

	क्रम (port = 0; port <  dev->caps.num_ports; port++) अणु
		/* Change the port type only अगर the new type is dअगरferent
		 * from the current, and not set to Auto */
		अगर (port_types[port] != dev->caps.port_type[port + 1])
			change = 1;
	पूर्ण
	अगर (change) अणु
		mlx4_unरेजिस्टर_device(dev);
		क्रम (port = 1; port <= dev->caps.num_ports; port++) अणु
			mlx4_CLOSE_PORT(dev, port);
			dev->caps.port_type[port] = port_types[port - 1];
			err = mlx4_SET_PORT(dev, port, -1);
			अगर (err) अणु
				mlx4_err(dev, "Failed to set port %d, aborting\n",
					 port);
				जाओ out;
			पूर्ण
		पूर्ण
		mlx4_set_port_mask(dev);
		err = mlx4_रेजिस्टर_device(dev);
		अगर (err) अणु
			mlx4_err(dev, "Failed to register device\n");
			जाओ out;
		पूर्ण
		mlx4_request_modules(dev);
	पूर्ण

out:
	वापस err;
पूर्ण

अटल sमाप_प्रकार show_port_type(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा mlx4_port_info *info = container_of(attr, काष्ठा mlx4_port_info,
						   port_attr);
	काष्ठा mlx4_dev *mdev = info->dev;
	अक्षर type[8];

	प्र_लिखो(type, "%s",
		(mdev->caps.port_type[info->port] == MLX4_PORT_TYPE_IB) ?
		"ib" : "eth");
	अगर (mdev->caps.possible_type[info->port] == MLX4_PORT_TYPE_AUTO)
		प्र_लिखो(buf, "auto (%s)\n", type);
	अन्यथा
		प्र_लिखो(buf, "%s\n", type);

	वापस म_माप(buf);
पूर्ण

अटल पूर्णांक __set_port_type(काष्ठा mlx4_port_info *info,
			   क्रमागत mlx4_port_type port_type)
अणु
	काष्ठा mlx4_dev *mdev = info->dev;
	काष्ठा mlx4_priv *priv = mlx4_priv(mdev);
	क्रमागत mlx4_port_type types[MLX4_MAX_PORTS];
	क्रमागत mlx4_port_type new_types[MLX4_MAX_PORTS];
	पूर्णांक i;
	पूर्णांक err = 0;

	अगर ((port_type & mdev->caps.supported_type[info->port]) != port_type) अणु
		mlx4_err(mdev,
			 "Requested port type for port %d is not supported on this HCA\n",
			 info->port);
		वापस -EOPNOTSUPP;
	पूर्ण

	mlx4_stop_sense(mdev);
	mutex_lock(&priv->port_mutex);
	info->पंचांगp_type = port_type;

	/* Possible type is always the one that was delivered */
	mdev->caps.possible_type[info->port] = info->पंचांगp_type;

	क्रम (i = 0; i < mdev->caps.num_ports; i++) अणु
		types[i] = priv->port[i+1].पंचांगp_type ? priv->port[i+1].पंचांगp_type :
					mdev->caps.possible_type[i+1];
		अगर (types[i] == MLX4_PORT_TYPE_AUTO)
			types[i] = mdev->caps.port_type[i+1];
	पूर्ण

	अगर (!(mdev->caps.flags & MLX4_DEV_CAP_FLAG_DPDP) &&
	    !(mdev->caps.flags & MLX4_DEV_CAP_FLAG_SENSE_SUPPORT)) अणु
		क्रम (i = 1; i <= mdev->caps.num_ports; i++) अणु
			अगर (mdev->caps.possible_type[i] == MLX4_PORT_TYPE_AUTO) अणु
				mdev->caps.possible_type[i] = mdev->caps.port_type[i];
				err = -EOPNOTSUPP;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (err) अणु
		mlx4_err(mdev, "Auto sensing is not supported on this HCA. Set only 'eth' or 'ib' for both ports (should be the same)\n");
		जाओ out;
	पूर्ण

	mlx4_करो_sense_ports(mdev, new_types, types);

	err = mlx4_check_port_params(mdev, new_types);
	अगर (err)
		जाओ out;

	/* We are about to apply the changes after the configuration
	 * was verअगरied, no need to remember the temporary types
	 * any more */
	क्रम (i = 0; i < mdev->caps.num_ports; i++)
		priv->port[i + 1].पंचांगp_type = 0;

	err = mlx4_change_port_types(mdev, new_types);

out:
	mlx4_start_sense(mdev);
	mutex_unlock(&priv->port_mutex);

	वापस err;
पूर्ण

अटल sमाप_प्रकार set_port_type(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mlx4_port_info *info = container_of(attr, काष्ठा mlx4_port_info,
						   port_attr);
	काष्ठा mlx4_dev *mdev = info->dev;
	क्रमागत mlx4_port_type port_type;
	अटल DEFINE_MUTEX(set_port_type_mutex);
	पूर्णांक err;

	mutex_lock(&set_port_type_mutex);

	अगर (!म_भेद(buf, "ib\n")) अणु
		port_type = MLX4_PORT_TYPE_IB;
	पूर्ण अन्यथा अगर (!म_भेद(buf, "eth\n")) अणु
		port_type = MLX4_PORT_TYPE_ETH;
	पूर्ण अन्यथा अगर (!म_भेद(buf, "auto\n")) अणु
		port_type = MLX4_PORT_TYPE_AUTO;
	पूर्ण अन्यथा अणु
		mlx4_err(mdev, "%s is not supported port type\n", buf);
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	err = __set_port_type(info, port_type);

err_out:
	mutex_unlock(&set_port_type_mutex);

	वापस err ? err : count;
पूर्ण

क्रमागत ibta_mtu अणु
	IB_MTU_256  = 1,
	IB_MTU_512  = 2,
	IB_MTU_1024 = 3,
	IB_MTU_2048 = 4,
	IB_MTU_4096 = 5
पूर्ण;

अटल अंतरभूत पूर्णांक पूर्णांक_to_ibta_mtu(पूर्णांक mtu)
अणु
	चयन (mtu) अणु
	हाल 256:  वापस IB_MTU_256;
	हाल 512:  वापस IB_MTU_512;
	हाल 1024: वापस IB_MTU_1024;
	हाल 2048: वापस IB_MTU_2048;
	हाल 4096: वापस IB_MTU_4096;
	शेष: वापस -1;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक ibta_mtu_to_पूर्णांक(क्रमागत ibta_mtu mtu)
अणु
	चयन (mtu) अणु
	हाल IB_MTU_256:  वापस  256;
	हाल IB_MTU_512:  वापस  512;
	हाल IB_MTU_1024: वापस 1024;
	हाल IB_MTU_2048: वापस 2048;
	हाल IB_MTU_4096: वापस 4096;
	शेष: वापस -1;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार show_port_ib_mtu(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा mlx4_port_info *info = container_of(attr, काष्ठा mlx4_port_info,
						   port_mtu_attr);
	काष्ठा mlx4_dev *mdev = info->dev;

	अगर (mdev->caps.port_type[info->port] == MLX4_PORT_TYPE_ETH)
		mlx4_warn(mdev, "port level mtu is only used for IB ports\n");

	प्र_लिखो(buf, "%d\n",
			ibta_mtu_to_पूर्णांक(mdev->caps.port_ib_mtu[info->port]));
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार set_port_ib_mtu(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mlx4_port_info *info = container_of(attr, काष्ठा mlx4_port_info,
						   port_mtu_attr);
	काष्ठा mlx4_dev *mdev = info->dev;
	काष्ठा mlx4_priv *priv = mlx4_priv(mdev);
	पूर्णांक err, port, mtu, ibta_mtu = -1;

	अगर (mdev->caps.port_type[info->port] == MLX4_PORT_TYPE_ETH) अणु
		mlx4_warn(mdev, "port level mtu is only used for IB ports\n");
		वापस -EINVAL;
	पूर्ण

	err = kstrtoपूर्णांक(buf, 0, &mtu);
	अगर (!err)
		ibta_mtu = पूर्णांक_to_ibta_mtu(mtu);

	अगर (err || ibta_mtu < 0) अणु
		mlx4_err(mdev, "%s is invalid IBTA mtu\n", buf);
		वापस -EINVAL;
	पूर्ण

	mdev->caps.port_ib_mtu[info->port] = ibta_mtu;

	mlx4_stop_sense(mdev);
	mutex_lock(&priv->port_mutex);
	mlx4_unरेजिस्टर_device(mdev);
	क्रम (port = 1; port <= mdev->caps.num_ports; port++) अणु
		mlx4_CLOSE_PORT(mdev, port);
		err = mlx4_SET_PORT(mdev, port, -1);
		अगर (err) अणु
			mlx4_err(mdev, "Failed to set port %d, aborting\n",
				 port);
			जाओ err_set_port;
		पूर्ण
	पूर्ण
	err = mlx4_रेजिस्टर_device(mdev);
err_set_port:
	mutex_unlock(&priv->port_mutex);
	mlx4_start_sense(mdev);
	वापस err ? err : count;
पूर्ण

/* bond क्रम multi-function device */
#घोषणा MAX_MF_BOND_ALLOWED_SLAVES 63
अटल पूर्णांक mlx4_mf_bond(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक err = 0;
	पूर्णांक nvfs;
	काष्ठा mlx4_slaves_pport slaves_port1;
	काष्ठा mlx4_slaves_pport slaves_port2;
	DECLARE_BITMAP(slaves_port_1_2, MLX4_MFUNC_MAX);

	slaves_port1 = mlx4_phys_to_slaves_pport(dev, 1);
	slaves_port2 = mlx4_phys_to_slaves_pport(dev, 2);
	biपंचांगap_and(slaves_port_1_2,
		   slaves_port1.slaves, slaves_port2.slaves,
		   dev->persist->num_vfs + 1);

	/* only single port vfs are allowed */
	अगर (biपंचांगap_weight(slaves_port_1_2, dev->persist->num_vfs + 1) > 1) अणु
		mlx4_warn(dev, "HA mode unsupported for dual ported VFs\n");
		वापस -EINVAL;
	पूर्ण

	/* number of भव functions is number of total functions minus one
	 * physical function क्रम each port.
	 */
	nvfs = biपंचांगap_weight(slaves_port1.slaves, dev->persist->num_vfs + 1) +
		biपंचांगap_weight(slaves_port2.slaves, dev->persist->num_vfs + 1) - 2;

	/* limit on maximum allowed VFs */
	अगर (nvfs > MAX_MF_BOND_ALLOWED_SLAVES) अणु
		mlx4_warn(dev, "HA mode is not supported for %d VFs (max %d are allowed)\n",
			  nvfs, MAX_MF_BOND_ALLOWED_SLAVES);
		वापस -EINVAL;
	पूर्ण

	अगर (dev->caps.steering_mode != MLX4_STEERING_MODE_DEVICE_MANAGED) अणु
		mlx4_warn(dev, "HA mode unsupported for NON DMFS steering\n");
		वापस -EINVAL;
	पूर्ण

	err = mlx4_bond_mac_table(dev);
	अगर (err)
		वापस err;
	err = mlx4_bond_vlan_table(dev);
	अगर (err)
		जाओ err1;
	err = mlx4_bond_fs_rules(dev);
	अगर (err)
		जाओ err2;

	वापस 0;
err2:
	(व्योम)mlx4_unbond_vlan_table(dev);
err1:
	(व्योम)mlx4_unbond_mac_table(dev);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_mf_unbond(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक ret, ret1;

	ret = mlx4_unbond_fs_rules(dev);
	अगर (ret)
		mlx4_warn(dev, "multifunction unbond for flow rules failed (%d)\n", ret);
	ret1 = mlx4_unbond_mac_table(dev);
	अगर (ret1) अणु
		mlx4_warn(dev, "multifunction unbond for MAC table failed (%d)\n", ret1);
		ret = ret1;
	पूर्ण
	ret1 = mlx4_unbond_vlan_table(dev);
	अगर (ret1) अणु
		mlx4_warn(dev, "multifunction unbond for VLAN table failed (%d)\n", ret1);
		ret = ret1;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक mlx4_bond(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	mutex_lock(&priv->bond_mutex);

	अगर (!mlx4_is_bonded(dev)) अणु
		ret = mlx4_करो_bond(dev, true);
		अगर (ret)
			mlx4_err(dev, "Failed to bond device: %d\n", ret);
		अगर (!ret && mlx4_is_master(dev)) अणु
			ret = mlx4_mf_bond(dev);
			अगर (ret) अणु
				mlx4_err(dev, "bond for multifunction failed\n");
				mlx4_करो_bond(dev, false);
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&priv->bond_mutex);
	अगर (!ret)
		mlx4_dbg(dev, "Device is bonded\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_bond);

पूर्णांक mlx4_unbond(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	mutex_lock(&priv->bond_mutex);

	अगर (mlx4_is_bonded(dev)) अणु
		पूर्णांक ret2 = 0;

		ret = mlx4_करो_bond(dev, false);
		अगर (ret)
			mlx4_err(dev, "Failed to unbond device: %d\n", ret);
		अगर (mlx4_is_master(dev))
			ret2 = mlx4_mf_unbond(dev);
		अगर (ret2) अणु
			mlx4_warn(dev, "Failed to unbond device for multifunction (%d)\n", ret2);
			ret = ret2;
		पूर्ण
	पूर्ण

	mutex_unlock(&priv->bond_mutex);
	अगर (!ret)
		mlx4_dbg(dev, "Device is unbonded\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_unbond);


पूर्णांक mlx4_port_map_set(काष्ठा mlx4_dev *dev, काष्ठा mlx4_port_map *v2p)
अणु
	u8 port1 = v2p->port1;
	u8 port2 = v2p->port2;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक err;

	अगर (!(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_PORT_REMAP))
		वापस -EOPNOTSUPP;

	mutex_lock(&priv->bond_mutex);

	/* zero means keep current mapping क्रम this port */
	अगर (port1 == 0)
		port1 = priv->v2p.port1;
	अगर (port2 == 0)
		port2 = priv->v2p.port2;

	अगर ((port1 < 1) || (port1 > MLX4_MAX_PORTS) ||
	    (port2 < 1) || (port2 > MLX4_MAX_PORTS) ||
	    (port1 == 2 && port2 == 1)) अणु
		/* besides boundary checks cross mapping makes
		 * no sense and thereक्रमe not allowed */
		err = -EINVAL;
	पूर्ण अन्यथा अगर ((port1 == priv->v2p.port1) &&
		 (port2 == priv->v2p.port2)) अणु
		err = 0;
	पूर्ण अन्यथा अणु
		err = mlx4_virt2phy_port_map(dev, port1, port2);
		अगर (!err) अणु
			mlx4_dbg(dev, "port map changed: [%d][%d]\n",
				 port1, port2);
			priv->v2p.port1 = port1;
			priv->v2p.port2 = port2;
		पूर्ण अन्यथा अणु
			mlx4_err(dev, "Failed to change port mape: %d\n", err);
		पूर्ण
	पूर्ण

	mutex_unlock(&priv->bond_mutex);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_port_map_set);

अटल पूर्णांक mlx4_load_fw(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक err;

	priv->fw.fw_icm = mlx4_alloc_icm(dev, priv->fw.fw_pages,
					 GFP_HIGHUSER | __GFP_NOWARN, 0);
	अगर (!priv->fw.fw_icm) अणु
		mlx4_err(dev, "Couldn't allocate FW area, aborting\n");
		वापस -ENOMEM;
	पूर्ण

	err = mlx4_MAP_FA(dev, priv->fw.fw_icm);
	अगर (err) अणु
		mlx4_err(dev, "MAP_FA command failed, aborting\n");
		जाओ err_मुक्त;
	पूर्ण

	err = mlx4_RUN_FW(dev);
	अगर (err) अणु
		mlx4_err(dev, "RUN_FW command failed, aborting\n");
		जाओ err_unmap_fa;
	पूर्ण

	वापस 0;

err_unmap_fa:
	mlx4_UNMAP_FA(dev);

err_मुक्त:
	mlx4_मुक्त_icm(dev, priv->fw.fw_icm, 0);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_init_cmpt_table(काष्ठा mlx4_dev *dev, u64 cmpt_base,
				पूर्णांक cmpt_entry_sz)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक err;
	पूर्णांक num_eqs;

	err = mlx4_init_icm_table(dev, &priv->qp_table.cmpt_table,
				  cmpt_base +
				  ((u64) (MLX4_CMPT_TYPE_QP *
					  cmpt_entry_sz) << MLX4_CMPT_SHIFT),
				  cmpt_entry_sz, dev->caps.num_qps,
				  dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW],
				  0, 0);
	अगर (err)
		जाओ err;

	err = mlx4_init_icm_table(dev, &priv->srq_table.cmpt_table,
				  cmpt_base +
				  ((u64) (MLX4_CMPT_TYPE_SRQ *
					  cmpt_entry_sz) << MLX4_CMPT_SHIFT),
				  cmpt_entry_sz, dev->caps.num_srqs,
				  dev->caps.reserved_srqs, 0, 0);
	अगर (err)
		जाओ err_qp;

	err = mlx4_init_icm_table(dev, &priv->cq_table.cmpt_table,
				  cmpt_base +
				  ((u64) (MLX4_CMPT_TYPE_CQ *
					  cmpt_entry_sz) << MLX4_CMPT_SHIFT),
				  cmpt_entry_sz, dev->caps.num_cqs,
				  dev->caps.reserved_cqs, 0, 0);
	अगर (err)
		जाओ err_srq;

	num_eqs = dev->phys_caps.num_phys_eqs;
	err = mlx4_init_icm_table(dev, &priv->eq_table.cmpt_table,
				  cmpt_base +
				  ((u64) (MLX4_CMPT_TYPE_EQ *
					  cmpt_entry_sz) << MLX4_CMPT_SHIFT),
				  cmpt_entry_sz, num_eqs, num_eqs, 0, 0);
	अगर (err)
		जाओ err_cq;

	वापस 0;

err_cq:
	mlx4_cleanup_icm_table(dev, &priv->cq_table.cmpt_table);

err_srq:
	mlx4_cleanup_icm_table(dev, &priv->srq_table.cmpt_table);

err_qp:
	mlx4_cleanup_icm_table(dev, &priv->qp_table.cmpt_table);

err:
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_init_icm(काष्ठा mlx4_dev *dev, काष्ठा mlx4_dev_cap *dev_cap,
			 काष्ठा mlx4_init_hca_param *init_hca, u64 icm_size)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	u64 aux_pages;
	पूर्णांक num_eqs;
	पूर्णांक err;

	err = mlx4_SET_ICM_SIZE(dev, icm_size, &aux_pages);
	अगर (err) अणु
		mlx4_err(dev, "SET_ICM_SIZE command failed, aborting\n");
		वापस err;
	पूर्ण

	mlx4_dbg(dev, "%lld KB of HCA context requires %lld KB aux memory\n",
		 (अचिन्हित दीर्घ दीर्घ) icm_size >> 10,
		 (अचिन्हित दीर्घ दीर्घ) aux_pages << 2);

	priv->fw.aux_icm = mlx4_alloc_icm(dev, aux_pages,
					  GFP_HIGHUSER | __GFP_NOWARN, 0);
	अगर (!priv->fw.aux_icm) अणु
		mlx4_err(dev, "Couldn't allocate aux memory, aborting\n");
		वापस -ENOMEM;
	पूर्ण

	err = mlx4_MAP_ICM_AUX(dev, priv->fw.aux_icm);
	अगर (err) अणु
		mlx4_err(dev, "MAP_ICM_AUX command failed, aborting\n");
		जाओ err_मुक्त_aux;
	पूर्ण

	err = mlx4_init_cmpt_table(dev, init_hca->cmpt_base, dev_cap->cmpt_entry_sz);
	अगर (err) अणु
		mlx4_err(dev, "Failed to map cMPT context memory, aborting\n");
		जाओ err_unmap_aux;
	पूर्ण


	num_eqs = dev->phys_caps.num_phys_eqs;
	err = mlx4_init_icm_table(dev, &priv->eq_table.table,
				  init_hca->eqc_base, dev_cap->eqc_entry_sz,
				  num_eqs, num_eqs, 0, 0);
	अगर (err) अणु
		mlx4_err(dev, "Failed to map EQ context memory, aborting\n");
		जाओ err_unmap_cmpt;
	पूर्ण

	/*
	 * Reserved MTT entries must be aligned up to a cacheline
	 * boundary, since the FW will ग_लिखो to them, जबतक the driver
	 * ग_लिखोs to all other MTT entries. (The variable
	 * dev->caps.mtt_entry_sz below is really the MTT segment
	 * size, not the raw entry size)
	 */
	dev->caps.reserved_mtts =
		ALIGN(dev->caps.reserved_mtts * dev->caps.mtt_entry_sz,
		      dma_get_cache_alignment()) / dev->caps.mtt_entry_sz;

	err = mlx4_init_icm_table(dev, &priv->mr_table.mtt_table,
				  init_hca->mtt_base,
				  dev->caps.mtt_entry_sz,
				  dev->caps.num_mtts,
				  dev->caps.reserved_mtts, 1, 0);
	अगर (err) अणु
		mlx4_err(dev, "Failed to map MTT context memory, aborting\n");
		जाओ err_unmap_eq;
	पूर्ण

	err = mlx4_init_icm_table(dev, &priv->mr_table.dmpt_table,
				  init_hca->dmpt_base,
				  dev_cap->dmpt_entry_sz,
				  dev->caps.num_mpts,
				  dev->caps.reserved_mrws, 1, 1);
	अगर (err) अणु
		mlx4_err(dev, "Failed to map dMPT context memory, aborting\n");
		जाओ err_unmap_mtt;
	पूर्ण

	err = mlx4_init_icm_table(dev, &priv->qp_table.qp_table,
				  init_hca->qpc_base,
				  dev_cap->qpc_entry_sz,
				  dev->caps.num_qps,
				  dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW],
				  0, 0);
	अगर (err) अणु
		mlx4_err(dev, "Failed to map QP context memory, aborting\n");
		जाओ err_unmap_dmpt;
	पूर्ण

	err = mlx4_init_icm_table(dev, &priv->qp_table.auxc_table,
				  init_hca->auxc_base,
				  dev_cap->aux_entry_sz,
				  dev->caps.num_qps,
				  dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW],
				  0, 0);
	अगर (err) अणु
		mlx4_err(dev, "Failed to map AUXC context memory, aborting\n");
		जाओ err_unmap_qp;
	पूर्ण

	err = mlx4_init_icm_table(dev, &priv->qp_table.altc_table,
				  init_hca->altc_base,
				  dev_cap->altc_entry_sz,
				  dev->caps.num_qps,
				  dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW],
				  0, 0);
	अगर (err) अणु
		mlx4_err(dev, "Failed to map ALTC context memory, aborting\n");
		जाओ err_unmap_auxc;
	पूर्ण

	err = mlx4_init_icm_table(dev, &priv->qp_table.rdmarc_table,
				  init_hca->rdmarc_base,
				  dev_cap->rdmarc_entry_sz << priv->qp_table.rdmarc_shअगरt,
				  dev->caps.num_qps,
				  dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW],
				  0, 0);
	अगर (err) अणु
		mlx4_err(dev, "Failed to map RDMARC context memory, aborting\n");
		जाओ err_unmap_altc;
	पूर्ण

	err = mlx4_init_icm_table(dev, &priv->cq_table.table,
				  init_hca->cqc_base,
				  dev_cap->cqc_entry_sz,
				  dev->caps.num_cqs,
				  dev->caps.reserved_cqs, 0, 0);
	अगर (err) अणु
		mlx4_err(dev, "Failed to map CQ context memory, aborting\n");
		जाओ err_unmap_rdmarc;
	पूर्ण

	err = mlx4_init_icm_table(dev, &priv->srq_table.table,
				  init_hca->srqc_base,
				  dev_cap->srq_entry_sz,
				  dev->caps.num_srqs,
				  dev->caps.reserved_srqs, 0, 0);
	अगर (err) अणु
		mlx4_err(dev, "Failed to map SRQ context memory, aborting\n");
		जाओ err_unmap_cq;
	पूर्ण

	/*
	 * For flow steering device managed mode it is required to use
	 * mlx4_init_icm_table. For B0 steering mode it's not strictly
	 * required, but क्रम simplicity just map the whole multicast
	 * group table now.  The table isn't very big and it's a lot
	 * easier than trying to track ref counts.
	 */
	err = mlx4_init_icm_table(dev, &priv->mcg_table.table,
				  init_hca->mc_base,
				  mlx4_get_mgm_entry_size(dev),
				  dev->caps.num_mgms + dev->caps.num_amgms,
				  dev->caps.num_mgms + dev->caps.num_amgms,
				  0, 0);
	अगर (err) अणु
		mlx4_err(dev, "Failed to map MCG context memory, aborting\n");
		जाओ err_unmap_srq;
	पूर्ण

	वापस 0;

err_unmap_srq:
	mlx4_cleanup_icm_table(dev, &priv->srq_table.table);

err_unmap_cq:
	mlx4_cleanup_icm_table(dev, &priv->cq_table.table);

err_unmap_rdmarc:
	mlx4_cleanup_icm_table(dev, &priv->qp_table.rdmarc_table);

err_unmap_altc:
	mlx4_cleanup_icm_table(dev, &priv->qp_table.altc_table);

err_unmap_auxc:
	mlx4_cleanup_icm_table(dev, &priv->qp_table.auxc_table);

err_unmap_qp:
	mlx4_cleanup_icm_table(dev, &priv->qp_table.qp_table);

err_unmap_dmpt:
	mlx4_cleanup_icm_table(dev, &priv->mr_table.dmpt_table);

err_unmap_mtt:
	mlx4_cleanup_icm_table(dev, &priv->mr_table.mtt_table);

err_unmap_eq:
	mlx4_cleanup_icm_table(dev, &priv->eq_table.table);

err_unmap_cmpt:
	mlx4_cleanup_icm_table(dev, &priv->eq_table.cmpt_table);
	mlx4_cleanup_icm_table(dev, &priv->cq_table.cmpt_table);
	mlx4_cleanup_icm_table(dev, &priv->srq_table.cmpt_table);
	mlx4_cleanup_icm_table(dev, &priv->qp_table.cmpt_table);

err_unmap_aux:
	mlx4_UNMAP_ICM_AUX(dev);

err_मुक्त_aux:
	mlx4_मुक्त_icm(dev, priv->fw.aux_icm, 0);

	वापस err;
पूर्ण

अटल व्योम mlx4_मुक्त_icms(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	mlx4_cleanup_icm_table(dev, &priv->mcg_table.table);
	mlx4_cleanup_icm_table(dev, &priv->srq_table.table);
	mlx4_cleanup_icm_table(dev, &priv->cq_table.table);
	mlx4_cleanup_icm_table(dev, &priv->qp_table.rdmarc_table);
	mlx4_cleanup_icm_table(dev, &priv->qp_table.altc_table);
	mlx4_cleanup_icm_table(dev, &priv->qp_table.auxc_table);
	mlx4_cleanup_icm_table(dev, &priv->qp_table.qp_table);
	mlx4_cleanup_icm_table(dev, &priv->mr_table.dmpt_table);
	mlx4_cleanup_icm_table(dev, &priv->mr_table.mtt_table);
	mlx4_cleanup_icm_table(dev, &priv->eq_table.table);
	mlx4_cleanup_icm_table(dev, &priv->eq_table.cmpt_table);
	mlx4_cleanup_icm_table(dev, &priv->cq_table.cmpt_table);
	mlx4_cleanup_icm_table(dev, &priv->srq_table.cmpt_table);
	mlx4_cleanup_icm_table(dev, &priv->qp_table.cmpt_table);

	mlx4_UNMAP_ICM_AUX(dev);
	mlx4_मुक्त_icm(dev, priv->fw.aux_icm, 0);
पूर्ण

अटल व्योम mlx4_slave_निकास(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	mutex_lock(&priv->cmd.slave_cmd_mutex);
	अगर (mlx4_comm_cmd(dev, MLX4_COMM_CMD_RESET, 0, MLX4_COMM_CMD_NA_OP,
			  MLX4_COMM_TIME))
		mlx4_warn(dev, "Failed to close slave function\n");
	mutex_unlock(&priv->cmd.slave_cmd_mutex);
पूर्ण

अटल पूर्णांक map_bf_area(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	resource_माप_प्रकार bf_start;
	resource_माप_प्रकार bf_len;
	पूर्णांक err = 0;

	अगर (!dev->caps.bf_reg_size)
		वापस -ENXIO;

	bf_start = pci_resource_start(dev->persist->pdev, 2) +
			(dev->caps.num_uars << PAGE_SHIFT);
	bf_len = pci_resource_len(dev->persist->pdev, 2) -
			(dev->caps.num_uars << PAGE_SHIFT);
	priv->bf_mapping = io_mapping_create_wc(bf_start, bf_len);
	अगर (!priv->bf_mapping)
		err = -ENOMEM;

	वापस err;
पूर्ण

अटल व्योम unmap_bf_area(काष्ठा mlx4_dev *dev)
अणु
	अगर (mlx4_priv(dev)->bf_mapping)
		io_mapping_मुक्त(mlx4_priv(dev)->bf_mapping);
पूर्ण

u64 mlx4_पढ़ो_घड़ी(काष्ठा mlx4_dev *dev)
अणु
	u32 घड़ीhi, घड़ीlo, घड़ीhi1;
	u64 cycles;
	पूर्णांक i;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	क्रम (i = 0; i < 10; i++) अणु
		घड़ीhi = swab32(पढ़ोl(priv->घड़ी_mapping));
		घड़ीlo = swab32(पढ़ोl(priv->घड़ी_mapping + 4));
		घड़ीhi1 = swab32(पढ़ोl(priv->घड़ी_mapping));
		अगर (घड़ीhi == घड़ीhi1)
			अवरोध;
	पूर्ण

	cycles = (u64) घड़ीhi << 32 | (u64) घड़ीlo;

	वापस cycles;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_पढ़ो_घड़ी);


अटल पूर्णांक map_पूर्णांकernal_घड़ी(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	priv->घड़ी_mapping =
		ioremap(pci_resource_start(dev->persist->pdev,
					   priv->fw.घड़ी_bar) +
			priv->fw.घड़ी_offset, MLX4_CLOCK_SIZE);

	अगर (!priv->घड़ी_mapping)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक mlx4_get_पूर्णांकernal_घड़ी_params(काष्ठा mlx4_dev *dev,
				   काष्ठा mlx4_घड़ी_params *params)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	अगर (mlx4_is_slave(dev))
		वापस -EOPNOTSUPP;

	अगर (!dev->caps.map_घड़ी_प्रकारo_user) अणु
		mlx4_dbg(dev, "Map clock to user is not supported.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!params)
		वापस -EINVAL;

	params->bar = priv->fw.घड़ी_bar;
	params->offset = priv->fw.घड़ी_offset;
	params->size = MLX4_CLOCK_SIZE;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_get_पूर्णांकernal_घड़ी_params);

अटल व्योम unmap_पूर्णांकernal_घड़ी(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	अगर (priv->घड़ी_mapping)
		iounmap(priv->घड़ी_mapping);
पूर्ण

अटल व्योम mlx4_बंद_hca(काष्ठा mlx4_dev *dev)
अणु
	unmap_पूर्णांकernal_घड़ी(dev);
	unmap_bf_area(dev);
	अगर (mlx4_is_slave(dev))
		mlx4_slave_निकास(dev);
	अन्यथा अणु
		mlx4_CLOSE_HCA(dev, 0);
		mlx4_मुक्त_icms(dev);
	पूर्ण
पूर्ण

अटल व्योम mlx4_बंद_fw(काष्ठा mlx4_dev *dev)
अणु
	अगर (!mlx4_is_slave(dev)) अणु
		mlx4_UNMAP_FA(dev);
		mlx4_मुक्त_icm(dev, mlx4_priv(dev)->fw.fw_icm, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_comm_check_offline(काष्ठा mlx4_dev *dev)
अणु
#घोषणा COMM_CHAN_OFFLINE_OFFSET 0x09

	u32 comm_flags;
	u32 offline_bit;
	अचिन्हित दीर्घ end;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	end = msecs_to_jअगरfies(MLX4_COMM_OFFLINE_TIME_OUT) + jअगरfies;
	जबतक (समय_beक्रमe(jअगरfies, end)) अणु
		comm_flags = swab32(पढ़ोl((__iomem अक्षर *)priv->mfunc.comm +
					  MLX4_COMM_CHAN_FLAGS));
		offline_bit = (comm_flags &
			       (u32)(1 << COMM_CHAN_OFFLINE_OFFSET));
		अगर (!offline_bit)
			वापस 0;

		/* If device removal has been requested,
		 * करो not जारी retrying.
		 */
		अगर (dev->persist->पूर्णांकerface_state &
		    MLX4_INTERFACE_STATE_NOWAIT)
			अवरोध;

		/* There are हालs as part of AER/Reset flow that PF needs
		 * around 100 msec to load. We thereक्रमe sleep क्रम 100 msec
		 * to allow other tasks to make use of that CPU during this
		 * समय पूर्णांकerval.
		 */
		msleep(100);
	पूर्ण
	mlx4_err(dev, "Communication channel is offline.\n");
	वापस -EIO;
पूर्ण

अटल व्योम mlx4_reset_vf_support(काष्ठा mlx4_dev *dev)
अणु
#घोषणा COMM_CHAN_RST_OFFSET 0x1e

	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	u32 comm_rst;
	u32 comm_caps;

	comm_caps = swab32(पढ़ोl((__iomem अक्षर *)priv->mfunc.comm +
				 MLX4_COMM_CHAN_CAPS));
	comm_rst = (comm_caps & (u32)(1 << COMM_CHAN_RST_OFFSET));

	अगर (comm_rst)
		dev->caps.vf_caps |= MLX4_VF_CAP_FLAG_RESET;
पूर्ण

अटल पूर्णांक mlx4_init_slave(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	u64 dma = (u64) priv->mfunc.vhcr_dma;
	पूर्णांक ret_from_reset = 0;
	u32 slave_पढ़ो;
	u32 cmd_channel_ver;

	अगर (atomic_पढ़ो(&pf_loading)) अणु
		mlx4_warn(dev, "PF is not ready - Deferring probe\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	mutex_lock(&priv->cmd.slave_cmd_mutex);
	priv->cmd.max_cmds = 1;
	अगर (mlx4_comm_check_offline(dev)) अणु
		mlx4_err(dev, "PF is not responsive, skipping initialization\n");
		जाओ err_offline;
	पूर्ण

	mlx4_reset_vf_support(dev);
	mlx4_warn(dev, "Sending reset\n");
	ret_from_reset = mlx4_comm_cmd(dev, MLX4_COMM_CMD_RESET, 0,
				       MLX4_COMM_CMD_NA_OP, MLX4_COMM_TIME);
	/* अगर we are in the middle of flr the slave will try
	 * NUM_OF_RESET_RETRIES बार beक्रमe leaving.*/
	अगर (ret_from_reset) अणु
		अगर (MLX4_DELAY_RESET_SLAVE == ret_from_reset) अणु
			mlx4_warn(dev, "slave is currently in the middle of FLR - Deferring probe\n");
			mutex_unlock(&priv->cmd.slave_cmd_mutex);
			वापस -EPROBE_DEFER;
		पूर्ण अन्यथा
			जाओ err;
	पूर्ण

	/* check the driver version - the slave I/F revision
	 * must match the master's */
	slave_पढ़ो = swab32(पढ़ोl(&priv->mfunc.comm->slave_पढ़ो));
	cmd_channel_ver = mlx4_comm_get_version();

	अगर (MLX4_COMM_GET_IF_REV(cmd_channel_ver) !=
		MLX4_COMM_GET_IF_REV(slave_पढ़ो)) अणु
		mlx4_err(dev, "slave driver version is not supported by the master\n");
		जाओ err;
	पूर्ण

	mlx4_warn(dev, "Sending vhcr0\n");
	अगर (mlx4_comm_cmd(dev, MLX4_COMM_CMD_VHCR0, dma >> 48,
			     MLX4_COMM_CMD_NA_OP, MLX4_COMM_TIME))
		जाओ err;
	अगर (mlx4_comm_cmd(dev, MLX4_COMM_CMD_VHCR1, dma >> 32,
			     MLX4_COMM_CMD_NA_OP, MLX4_COMM_TIME))
		जाओ err;
	अगर (mlx4_comm_cmd(dev, MLX4_COMM_CMD_VHCR2, dma >> 16,
			     MLX4_COMM_CMD_NA_OP, MLX4_COMM_TIME))
		जाओ err;
	अगर (mlx4_comm_cmd(dev, MLX4_COMM_CMD_VHCR_EN, dma,
			  MLX4_COMM_CMD_NA_OP, MLX4_COMM_TIME))
		जाओ err;

	mutex_unlock(&priv->cmd.slave_cmd_mutex);
	वापस 0;

err:
	mlx4_comm_cmd(dev, MLX4_COMM_CMD_RESET, 0, MLX4_COMM_CMD_NA_OP, 0);
err_offline:
	mutex_unlock(&priv->cmd.slave_cmd_mutex);
	वापस -EIO;
पूर्ण

अटल व्योम mlx4_parav_master_pf_caps(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 1; i <= dev->caps.num_ports; i++) अणु
		अगर (dev->caps.port_type[i] == MLX4_PORT_TYPE_ETH)
			dev->caps.gid_table_len[i] =
				mlx4_get_slave_num_gids(dev, 0, i);
		अन्यथा
			dev->caps.gid_table_len[i] = 1;
		dev->caps.pkey_table_len[i] =
			dev->phys_caps.pkey_phys_table_len[i] - 1;
	पूर्ण
पूर्ण

अटल पूर्णांक choose_log_fs_mgm_entry_size(पूर्णांक qp_per_entry)
अणु
	पूर्णांक i = MLX4_MIN_MGM_LOG_ENTRY_SIZE;

	क्रम (i = MLX4_MIN_MGM_LOG_ENTRY_SIZE; i <= MLX4_MAX_MGM_LOG_ENTRY_SIZE;
	      i++) अणु
		अगर (qp_per_entry <= 4 * ((1 << i) / 16 - 2))
			अवरोध;
	पूर्ण

	वापस (i <= MLX4_MAX_MGM_LOG_ENTRY_SIZE) ? i : -1;
पूर्ण

अटल स्थिर अक्षर *dmfs_high_rate_steering_mode_str(पूर्णांक dmfs_high_steer_mode)
अणु
	चयन (dmfs_high_steer_mode) अणु
	हाल MLX4_STEERING_DMFS_A0_DEFAULT:
		वापस "default performance";

	हाल MLX4_STEERING_DMFS_A0_DYNAMIC:
		वापस "dynamic hybrid mode";

	हाल MLX4_STEERING_DMFS_A0_STATIC:
		वापस "performance optimized for limited rule configuration (static)";

	हाल MLX4_STEERING_DMFS_A0_DISABLE:
		वापस "disabled performance optimized steering";

	हाल MLX4_STEERING_DMFS_A0_NOT_SUPPORTED:
		वापस "performance optimized steering not supported";

	शेष:
		वापस "Unrecognized mode";
	पूर्ण
पूर्ण

#घोषणा MLX4_DMFS_A0_STEERING			(1UL << 2)

अटल व्योम choose_steering_mode(काष्ठा mlx4_dev *dev,
				 काष्ठा mlx4_dev_cap *dev_cap)
अणु
	अगर (mlx4_log_num_mgm_entry_size <= 0) अणु
		अगर ((-mlx4_log_num_mgm_entry_size) & MLX4_DMFS_A0_STEERING) अणु
			अगर (dev->caps.dmfs_high_steer_mode ==
			    MLX4_STEERING_DMFS_A0_NOT_SUPPORTED)
				mlx4_err(dev, "DMFS high rate mode not supported\n");
			अन्यथा
				dev->caps.dmfs_high_steer_mode =
					MLX4_STEERING_DMFS_A0_STATIC;
		पूर्ण
	पूर्ण

	अगर (mlx4_log_num_mgm_entry_size <= 0 &&
	    dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_FS_EN &&
	    (!mlx4_is_mfunc(dev) ||
	     (dev_cap->fs_max_num_qp_per_entry >=
	     (dev->persist->num_vfs + 1))) &&
	    choose_log_fs_mgm_entry_size(dev_cap->fs_max_num_qp_per_entry) >=
		MLX4_MIN_MGM_LOG_ENTRY_SIZE) अणु
		dev->oper_log_mgm_entry_size =
			choose_log_fs_mgm_entry_size(dev_cap->fs_max_num_qp_per_entry);
		dev->caps.steering_mode = MLX4_STEERING_MODE_DEVICE_MANAGED;
		dev->caps.num_qp_per_mgm = dev_cap->fs_max_num_qp_per_entry;
		dev->caps.fs_log_max_ucast_qp_range_size =
			dev_cap->fs_log_max_ucast_qp_range_size;
	पूर्ण अन्यथा अणु
		अगर (dev->caps.dmfs_high_steer_mode !=
		    MLX4_STEERING_DMFS_A0_NOT_SUPPORTED)
			dev->caps.dmfs_high_steer_mode = MLX4_STEERING_DMFS_A0_DISABLE;
		अगर (dev->caps.flags & MLX4_DEV_CAP_FLAG_VEP_UC_STEER &&
		    dev->caps.flags & MLX4_DEV_CAP_FLAG_VEP_MC_STEER)
			dev->caps.steering_mode = MLX4_STEERING_MODE_B0;
		अन्यथा अणु
			dev->caps.steering_mode = MLX4_STEERING_MODE_A0;

			अगर (dev->caps.flags & MLX4_DEV_CAP_FLAG_VEP_UC_STEER ||
			    dev->caps.flags & MLX4_DEV_CAP_FLAG_VEP_MC_STEER)
				mlx4_warn(dev, "Must have both UC_STEER and MC_STEER flags set to use B0 steering - falling back to A0 steering mode\n");
		पूर्ण
		dev->oper_log_mgm_entry_size =
			mlx4_log_num_mgm_entry_size > 0 ?
			mlx4_log_num_mgm_entry_size :
			MLX4_DEFAULT_MGM_LOG_ENTRY_SIZE;
		dev->caps.num_qp_per_mgm = mlx4_get_qp_per_mgm(dev);
	पूर्ण
	mlx4_dbg(dev, "Steering mode is: %s, oper_log_mgm_entry_size = %d, modparam log_num_mgm_entry_size = %d\n",
		 mlx4_steering_mode_str(dev->caps.steering_mode),
		 dev->oper_log_mgm_entry_size,
		 mlx4_log_num_mgm_entry_size);
पूर्ण

अटल व्योम choose_tunnel_offload_mode(काष्ठा mlx4_dev *dev,
				       काष्ठा mlx4_dev_cap *dev_cap)
अणु
	अगर (dev->caps.steering_mode == MLX4_STEERING_MODE_DEVICE_MANAGED &&
	    dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_VXLAN_OFFLOADS)
		dev->caps.tunnel_offload_mode = MLX4_TUNNEL_OFFLOAD_MODE_VXLAN;
	अन्यथा
		dev->caps.tunnel_offload_mode = MLX4_TUNNEL_OFFLOAD_MODE_NONE;

	mlx4_dbg(dev, "Tunneling offload mode is: %s\n",  (dev->caps.tunnel_offload_mode
		 == MLX4_TUNNEL_OFFLOAD_MODE_VXLAN) ? "vxlan" : "none");
पूर्ण

अटल पूर्णांक mlx4_validate_optimized_steering(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक i;
	काष्ठा mlx4_port_cap port_cap;

	अगर (dev->caps.dmfs_high_steer_mode == MLX4_STEERING_DMFS_A0_NOT_SUPPORTED)
		वापस -EINVAL;

	क्रम (i = 1; i <= dev->caps.num_ports; i++) अणु
		अगर (mlx4_dev_port(dev, i, &port_cap)) अणु
			mlx4_err(dev,
				 "QUERY_DEV_CAP command failed, can't verify DMFS high rate steering.\n");
		पूर्ण अन्यथा अगर ((dev->caps.dmfs_high_steer_mode !=
			    MLX4_STEERING_DMFS_A0_DEFAULT) &&
			   (port_cap.dmfs_optimized_state ==
			    !!(dev->caps.dmfs_high_steer_mode ==
			    MLX4_STEERING_DMFS_A0_DISABLE))) अणु
			mlx4_err(dev,
				 "DMFS high rate steer mode differ, driver requested %s but %s in FW.\n",
				 dmfs_high_rate_steering_mode_str(
					dev->caps.dmfs_high_steer_mode),
				 (port_cap.dmfs_optimized_state ?
					"enabled" : "disabled"));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_init_fw(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_mod_stat_cfg   mlx4_cfg;
	पूर्णांक err = 0;

	अगर (!mlx4_is_slave(dev)) अणु
		err = mlx4_QUERY_FW(dev);
		अगर (err) अणु
			अगर (err == -EACCES)
				mlx4_info(dev, "non-primary physical function, skipping\n");
			अन्यथा
				mlx4_err(dev, "QUERY_FW command failed, aborting\n");
			वापस err;
		पूर्ण

		err = mlx4_load_fw(dev);
		अगर (err) अणु
			mlx4_err(dev, "Failed to start FW, aborting\n");
			वापस err;
		पूर्ण

		mlx4_cfg.log_pg_sz_m = 1;
		mlx4_cfg.log_pg_sz = 0;
		err = mlx4_MOD_STAT_CFG(dev, &mlx4_cfg);
		अगर (err)
			mlx4_warn(dev, "Failed to override log_pg_sz parameter\n");
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_init_hca(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv	  *priv = mlx4_priv(dev);
	काष्ठा mlx4_init_hca_param *init_hca = शून्य;
	काष्ठा mlx4_dev_cap	  *dev_cap = शून्य;
	काष्ठा mlx4_adapter	   adapter;
	काष्ठा mlx4_profile	   profile;
	u64 icm_size;
	काष्ठा mlx4_config_dev_params params;
	पूर्णांक err;

	अगर (!mlx4_is_slave(dev)) अणु
		dev_cap = kzalloc(माप(*dev_cap), GFP_KERNEL);
		init_hca = kzalloc(माप(*init_hca), GFP_KERNEL);

		अगर (!dev_cap || !init_hca) अणु
			err = -ENOMEM;
			जाओ out_मुक्त;
		पूर्ण

		err = mlx4_dev_cap(dev, dev_cap);
		अगर (err) अणु
			mlx4_err(dev, "QUERY_DEV_CAP command failed, aborting\n");
			जाओ out_मुक्त;
		पूर्ण

		choose_steering_mode(dev, dev_cap);
		choose_tunnel_offload_mode(dev, dev_cap);

		अगर (dev->caps.dmfs_high_steer_mode == MLX4_STEERING_DMFS_A0_STATIC &&
		    mlx4_is_master(dev))
			dev->caps.function_caps |= MLX4_FUNC_CAP_DMFS_A0_STATIC;

		err = mlx4_get_phys_port_id(dev);
		अगर (err)
			mlx4_err(dev, "Fail to get physical port id\n");

		अगर (mlx4_is_master(dev))
			mlx4_parav_master_pf_caps(dev);

		अगर (mlx4_low_memory_profile()) अणु
			mlx4_info(dev, "Running from within kdump kernel. Using low memory profile\n");
			profile = low_mem_profile;
		पूर्ण अन्यथा अणु
			profile = शेष_profile;
		पूर्ण
		अगर (dev->caps.steering_mode ==
		    MLX4_STEERING_MODE_DEVICE_MANAGED)
			profile.num_mcg = MLX4_FS_NUM_MCG;

		icm_size = mlx4_make_profile(dev, &profile, dev_cap,
					     init_hca);
		अगर ((दीर्घ दीर्घ) icm_size < 0) अणु
			err = icm_size;
			जाओ out_मुक्त;
		पूर्ण

		अगर (enable_4k_uar || !dev->persist->num_vfs) अणु
			init_hca->log_uar_sz = ilog2(dev->caps.num_uars) +
						    PAGE_SHIFT - DEFAULT_UAR_PAGE_SHIFT;
			init_hca->uar_page_sz = DEFAULT_UAR_PAGE_SHIFT - 12;
		पूर्ण अन्यथा अणु
			init_hca->log_uar_sz = ilog2(dev->caps.num_uars);
			init_hca->uar_page_sz = PAGE_SHIFT - 12;
		पूर्ण

		init_hca->mw_enabled = 0;
		अगर (dev->caps.flags & MLX4_DEV_CAP_FLAG_MEM_WINDOW ||
		    dev->caps.bmme_flags & MLX4_BMME_FLAG_TYPE_2_WIN)
			init_hca->mw_enabled = INIT_HCA_TPT_MW_ENABLE;

		err = mlx4_init_icm(dev, dev_cap, init_hca, icm_size);
		अगर (err)
			जाओ out_मुक्त;

		err = mlx4_INIT_HCA(dev, init_hca);
		अगर (err) अणु
			mlx4_err(dev, "INIT_HCA command failed, aborting\n");
			जाओ err_मुक्त_icm;
		पूर्ण

		अगर (dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_SYS_EQS) अणु
			err = mlx4_query_func(dev, dev_cap);
			अगर (err < 0) अणु
				mlx4_err(dev, "QUERY_FUNC command failed, aborting.\n");
				जाओ err_बंद;
			पूर्ण अन्यथा अगर (err & MLX4_QUERY_FUNC_NUM_SYS_EQS) अणु
				dev->caps.num_eqs = dev_cap->max_eqs;
				dev->caps.reserved_eqs = dev_cap->reserved_eqs;
				dev->caps.reserved_uars = dev_cap->reserved_uars;
			पूर्ण
		पूर्ण

		/*
		 * If TS is supported by FW
		 * पढ़ो HCA frequency by QUERY_HCA command
		 */
		अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_TS) अणु
			err = mlx4_QUERY_HCA(dev, init_hca);
			अगर (err) अणु
				mlx4_err(dev, "QUERY_HCA command failed, disable timestamp\n");
				dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_TS;
			पूर्ण अन्यथा अणु
				dev->caps.hca_core_घड़ी =
					init_hca->hca_core_घड़ी;
			पूर्ण

			/* In हाल we got HCA frequency 0 - disable बारtamping
			 * to aव्योम भागiding by zero
			 */
			अगर (!dev->caps.hca_core_घड़ी) अणु
				dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_TS;
				mlx4_err(dev,
					 "HCA frequency is 0 - timestamping is not supported\n");
			पूर्ण अन्यथा अगर (map_पूर्णांकernal_घड़ी(dev)) अणु
				/*
				 * Map पूर्णांकernal घड़ी,
				 * in हाल of failure disable बारtamping
				 */
				dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_TS;
				mlx4_err(dev, "Failed to map internal clock. Timestamping is not supported\n");
			पूर्ण
		पूर्ण

		अगर (dev->caps.dmfs_high_steer_mode !=
		    MLX4_STEERING_DMFS_A0_NOT_SUPPORTED) अणु
			अगर (mlx4_validate_optimized_steering(dev))
				mlx4_warn(dev, "Optimized steering validation failed\n");

			अगर (dev->caps.dmfs_high_steer_mode ==
			    MLX4_STEERING_DMFS_A0_DISABLE) अणु
				dev->caps.dmfs_high_rate_qpn_base =
					dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW];
				dev->caps.dmfs_high_rate_qpn_range =
					MLX4_A0_STEERING_TABLE_SIZE;
			पूर्ण

			mlx4_info(dev, "DMFS high rate steer mode is: %s\n",
				  dmfs_high_rate_steering_mode_str(
					dev->caps.dmfs_high_steer_mode));
		पूर्ण
	पूर्ण अन्यथा अणु
		err = mlx4_init_slave(dev);
		अगर (err) अणु
			अगर (err != -EPROBE_DEFER)
				mlx4_err(dev, "Failed to initialize slave\n");
			वापस err;
		पूर्ण

		err = mlx4_slave_cap(dev);
		अगर (err) अणु
			mlx4_err(dev, "Failed to obtain slave caps\n");
			जाओ err_बंद;
		पूर्ण
	पूर्ण

	अगर (map_bf_area(dev))
		mlx4_dbg(dev, "Failed to map blue flame area\n");

	/*Only the master set the ports, all the rest got it from it.*/
	अगर (!mlx4_is_slave(dev))
		mlx4_set_port_mask(dev);

	err = mlx4_QUERY_ADAPTER(dev, &adapter);
	अगर (err) अणु
		mlx4_err(dev, "QUERY_ADAPTER command failed, aborting\n");
		जाओ unmap_bf;
	पूर्ण

	/* Query CONFIG_DEV parameters */
	err = mlx4_config_dev_retrieval(dev, &params);
	अगर (err && err != -EOPNOTSUPP) अणु
		mlx4_err(dev, "Failed to query CONFIG_DEV parameters\n");
	पूर्ण अन्यथा अगर (!err) अणु
		dev->caps.rx_checksum_flags_port[1] = params.rx_csum_flags_port_1;
		dev->caps.rx_checksum_flags_port[2] = params.rx_csum_flags_port_2;
	पूर्ण
	priv->eq_table.पूर्णांकa_pin = adapter.पूर्णांकa_pin;
	स_नकल(dev->board_id, adapter.board_id, माप(dev->board_id));

	err = 0;
	जाओ out_मुक्त;

unmap_bf:
	unmap_पूर्णांकernal_घड़ी(dev);
	unmap_bf_area(dev);

	अगर (mlx4_is_slave(dev))
		mlx4_slave_destroy_special_qp_cap(dev);

err_बंद:
	अगर (mlx4_is_slave(dev))
		mlx4_slave_निकास(dev);
	अन्यथा
		mlx4_CLOSE_HCA(dev, 0);

err_मुक्त_icm:
	अगर (!mlx4_is_slave(dev))
		mlx4_मुक्त_icms(dev);

out_मुक्त:
	kमुक्त(dev_cap);
	kमुक्त(init_hca);

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_init_counters_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक nent_घात2;

	अगर (!(dev->caps.flags & MLX4_DEV_CAP_FLAG_COUNTERS))
		वापस -ENOENT;

	अगर (!dev->caps.max_counters)
		वापस -ENOSPC;

	nent_घात2 = roundup_घात_of_two(dev->caps.max_counters);
	/* reserve last counter index क्रम sink counter */
	वापस mlx4_biपंचांगap_init(&priv->counters_biपंचांगap, nent_घात2,
				nent_घात2 - 1, 0,
				nent_घात2 - dev->caps.max_counters + 1);
पूर्ण

अटल व्योम mlx4_cleanup_counters_table(काष्ठा mlx4_dev *dev)
अणु
	अगर (!(dev->caps.flags & MLX4_DEV_CAP_FLAG_COUNTERS))
		वापस;

	अगर (!dev->caps.max_counters)
		वापस;

	mlx4_biपंचांगap_cleanup(&mlx4_priv(dev)->counters_biपंचांगap);
पूर्ण

अटल व्योम mlx4_cleanup_शेष_counters(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक port;

	क्रम (port = 0; port < dev->caps.num_ports; port++)
		अगर (priv->def_counter[port] != -1)
			mlx4_counter_मुक्त(dev,  priv->def_counter[port]);
पूर्ण

अटल पूर्णांक mlx4_allocate_शेष_counters(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक port, err = 0;
	u32 idx;

	क्रम (port = 0; port < dev->caps.num_ports; port++)
		priv->def_counter[port] = -1;

	क्रम (port = 0; port < dev->caps.num_ports; port++) अणु
		err = mlx4_counter_alloc(dev, &idx, MLX4_RES_USAGE_DRIVER);

		अगर (!err || err == -ENOSPC) अणु
			priv->def_counter[port] = idx;
			err = 0;
		पूर्ण अन्यथा अगर (err == -ENOENT) अणु
			err = 0;
			जारी;
		पूर्ण अन्यथा अगर (mlx4_is_slave(dev) && err == -EINVAL) अणु
			priv->def_counter[port] = MLX4_SINK_COUNTER_INDEX(dev);
			mlx4_warn(dev, "can't allocate counter from old PF driver, using index %d\n",
				  MLX4_SINK_COUNTER_INDEX(dev));
			err = 0;
		पूर्ण अन्यथा अणु
			mlx4_err(dev, "%s: failed to allocate default counter port %d err %d\n",
				 __func__, port + 1, err);
			mlx4_cleanup_शेष_counters(dev);
			वापस err;
		पूर्ण

		mlx4_dbg(dev, "%s: default counter index %d for port %d\n",
			 __func__, priv->def_counter[port], port + 1);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक __mlx4_counter_alloc(काष्ठा mlx4_dev *dev, u32 *idx)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	अगर (!(dev->caps.flags & MLX4_DEV_CAP_FLAG_COUNTERS))
		वापस -ENOENT;

	*idx = mlx4_biपंचांगap_alloc(&priv->counters_biपंचांगap);
	अगर (*idx == -1) अणु
		*idx = MLX4_SINK_COUNTER_INDEX(dev);
		वापस -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx4_counter_alloc(काष्ठा mlx4_dev *dev, u32 *idx, u8 usage)
अणु
	u32 in_modअगरier = RES_COUNTER | (((u32)usage & 3) << 30);
	u64 out_param;
	पूर्णांक err;

	अगर (mlx4_is_mfunc(dev)) अणु
		err = mlx4_cmd_imm(dev, 0, &out_param, in_modअगरier,
				   RES_OP_RESERVE, MLX4_CMD_ALLOC_RES,
				   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		अगर (!err)
			*idx = get_param_l(&out_param);
		अगर (WARN_ON(err == -ENOSPC))
			err = -EINVAL;
		वापस err;
	पूर्ण
	वापस __mlx4_counter_alloc(dev, idx);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_counter_alloc);

अटल पूर्णांक __mlx4_clear_अगर_stat(काष्ठा mlx4_dev *dev,
				u8 counter_index)
अणु
	काष्ठा mlx4_cmd_mailbox *अगर_stat_mailbox;
	पूर्णांक err;
	u32 अगर_stat_in_mod = (counter_index & 0xff) | MLX4_QUERY_IF_STAT_RESET;

	अगर_stat_mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(अगर_stat_mailbox))
		वापस PTR_ERR(अगर_stat_mailbox);

	err = mlx4_cmd_box(dev, 0, अगर_stat_mailbox->dma, अगर_stat_in_mod, 0,
			   MLX4_CMD_QUERY_IF_STAT, MLX4_CMD_TIME_CLASS_C,
			   MLX4_CMD_NATIVE);

	mlx4_मुक्त_cmd_mailbox(dev, अगर_stat_mailbox);
	वापस err;
पूर्ण

व्योम __mlx4_counter_मुक्त(काष्ठा mlx4_dev *dev, u32 idx)
अणु
	अगर (!(dev->caps.flags & MLX4_DEV_CAP_FLAG_COUNTERS))
		वापस;

	अगर (idx == MLX4_SINK_COUNTER_INDEX(dev))
		वापस;

	__mlx4_clear_अगर_stat(dev, idx);

	mlx4_biपंचांगap_मुक्त(&mlx4_priv(dev)->counters_biपंचांगap, idx, MLX4_USE_RR);
	वापस;
पूर्ण

व्योम mlx4_counter_मुक्त(काष्ठा mlx4_dev *dev, u32 idx)
अणु
	u64 in_param = 0;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&in_param, idx);
		mlx4_cmd(dev, in_param, RES_COUNTER, RES_OP_RESERVE,
			 MLX4_CMD_FREE_RES, MLX4_CMD_TIME_CLASS_A,
			 MLX4_CMD_WRAPPED);
		वापस;
	पूर्ण
	__mlx4_counter_मुक्त(dev, idx);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_counter_मुक्त);

पूर्णांक mlx4_get_शेष_counter_index(काष्ठा mlx4_dev *dev, पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	वापस priv->def_counter[port - 1];
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_get_शेष_counter_index);

व्योम mlx4_set_admin_guid(काष्ठा mlx4_dev *dev, __be64 guid, पूर्णांक entry, पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	priv->mfunc.master.vf_admin[entry].vport[port].guid = guid;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_set_admin_guid);

__be64 mlx4_get_admin_guid(काष्ठा mlx4_dev *dev, पूर्णांक entry, पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	वापस priv->mfunc.master.vf_admin[entry].vport[port].guid;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_get_admin_guid);

व्योम mlx4_set_अक्रमom_admin_guid(काष्ठा mlx4_dev *dev, पूर्णांक entry, पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	__be64 guid;

	/* hw GUID */
	अगर (entry == 0)
		वापस;

	get_अक्रमom_bytes((अक्षर *)&guid, माप(guid));
	guid &= ~(cpu_to_be64(1ULL << 56));
	guid |= cpu_to_be64(1ULL << 57);
	priv->mfunc.master.vf_admin[entry].vport[port].guid = guid;
पूर्ण

अटल पूर्णांक mlx4_setup_hca(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक err;
	पूर्णांक port;
	__be32 ib_port_शेष_caps;

	err = mlx4_init_uar_table(dev);
	अगर (err) अणु
		mlx4_err(dev, "Failed to initialize user access region table, aborting\n");
		वापस err;
	पूर्ण

	err = mlx4_uar_alloc(dev, &priv->driver_uar);
	अगर (err) अणु
		mlx4_err(dev, "Failed to allocate driver access region, aborting\n");
		जाओ err_uar_table_मुक्त;
	पूर्ण

	priv->kar = ioremap((phys_addr_t) priv->driver_uar.pfn << PAGE_SHIFT, PAGE_SIZE);
	अगर (!priv->kar) अणु
		mlx4_err(dev, "Couldn't map kernel access region, aborting\n");
		err = -ENOMEM;
		जाओ err_uar_मुक्त;
	पूर्ण

	err = mlx4_init_pd_table(dev);
	अगर (err) अणु
		mlx4_err(dev, "Failed to initialize protection domain table, aborting\n");
		जाओ err_kar_unmap;
	पूर्ण

	err = mlx4_init_xrcd_table(dev);
	अगर (err) अणु
		mlx4_err(dev, "Failed to initialize reliable connection domain table, aborting\n");
		जाओ err_pd_table_मुक्त;
	पूर्ण

	err = mlx4_init_mr_table(dev);
	अगर (err) अणु
		mlx4_err(dev, "Failed to initialize memory region table, aborting\n");
		जाओ err_xrcd_table_मुक्त;
	पूर्ण

	अगर (!mlx4_is_slave(dev)) अणु
		err = mlx4_init_mcg_table(dev);
		अगर (err) अणु
			mlx4_err(dev, "Failed to initialize multicast group table, aborting\n");
			जाओ err_mr_table_मुक्त;
		पूर्ण
		err = mlx4_config_mad_demux(dev);
		अगर (err) अणु
			mlx4_err(dev, "Failed in config_mad_demux, aborting\n");
			जाओ err_mcg_table_मुक्त;
		पूर्ण
	पूर्ण

	err = mlx4_init_eq_table(dev);
	अगर (err) अणु
		mlx4_err(dev, "Failed to initialize event queue table, aborting\n");
		जाओ err_mcg_table_मुक्त;
	पूर्ण

	err = mlx4_cmd_use_events(dev);
	अगर (err) अणु
		mlx4_err(dev, "Failed to switch to event-driven firmware commands, aborting\n");
		जाओ err_eq_table_मुक्त;
	पूर्ण

	err = mlx4_NOP(dev);
	अगर (err) अणु
		अगर (dev->flags & MLX4_FLAG_MSI_X) अणु
			mlx4_warn(dev, "NOP command failed to generate MSI-X interrupt IRQ %d)\n",
				  priv->eq_table.eq[MLX4_EQ_ASYNC].irq);
			mlx4_warn(dev, "Trying again without MSI-X\n");
		पूर्ण अन्यथा अणु
			mlx4_err(dev, "NOP command failed to generate interrupt (IRQ %d), aborting\n",
				 priv->eq_table.eq[MLX4_EQ_ASYNC].irq);
			mlx4_err(dev, "BIOS or ACPI interrupt routing problem?\n");
		पूर्ण

		जाओ err_cmd_poll;
	पूर्ण

	mlx4_dbg(dev, "NOP command IRQ test passed\n");

	err = mlx4_init_cq_table(dev);
	अगर (err) अणु
		mlx4_err(dev, "Failed to initialize completion queue table, aborting\n");
		जाओ err_cmd_poll;
	पूर्ण

	err = mlx4_init_srq_table(dev);
	अगर (err) अणु
		mlx4_err(dev, "Failed to initialize shared receive queue table, aborting\n");
		जाओ err_cq_table_मुक्त;
	पूर्ण

	err = mlx4_init_qp_table(dev);
	अगर (err) अणु
		mlx4_err(dev, "Failed to initialize queue pair table, aborting\n");
		जाओ err_srq_table_मुक्त;
	पूर्ण

	अगर (!mlx4_is_slave(dev)) अणु
		err = mlx4_init_counters_table(dev);
		अगर (err && err != -ENOENT) अणु
			mlx4_err(dev, "Failed to initialize counters table, aborting\n");
			जाओ err_qp_table_मुक्त;
		पूर्ण
	पूर्ण

	err = mlx4_allocate_शेष_counters(dev);
	अगर (err) अणु
		mlx4_err(dev, "Failed to allocate default counters, aborting\n");
		जाओ err_counters_table_मुक्त;
	पूर्ण

	अगर (!mlx4_is_slave(dev)) अणु
		क्रम (port = 1; port <= dev->caps.num_ports; port++) अणु
			ib_port_शेष_caps = 0;
			err = mlx4_get_port_ib_caps(dev, port,
						    &ib_port_शेष_caps);
			अगर (err)
				mlx4_warn(dev, "failed to get port %d default ib capabilities (%d). Continuing with caps = 0\n",
					  port, err);
			dev->caps.ib_port_def_cap[port] = ib_port_शेष_caps;

			/* initialize per-slave शेष ib port capabilities */
			अगर (mlx4_is_master(dev)) अणु
				पूर्णांक i;
				क्रम (i = 0; i < dev->num_slaves; i++) अणु
					अगर (i == mlx4_master_func_num(dev))
						जारी;
					priv->mfunc.master.slave_state[i].ib_cap_mask[port] =
						ib_port_शेष_caps;
				पूर्ण
			पूर्ण

			अगर (mlx4_is_mfunc(dev))
				dev->caps.port_ib_mtu[port] = IB_MTU_2048;
			अन्यथा
				dev->caps.port_ib_mtu[port] = IB_MTU_4096;

			err = mlx4_SET_PORT(dev, port, mlx4_is_master(dev) ?
					    dev->caps.pkey_table_len[port] : -1);
			अगर (err) अणु
				mlx4_err(dev, "Failed to set port %d, aborting\n",
					 port);
				जाओ err_शेष_countes_मुक्त;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

err_शेष_countes_मुक्त:
	mlx4_cleanup_शेष_counters(dev);

err_counters_table_मुक्त:
	अगर (!mlx4_is_slave(dev))
		mlx4_cleanup_counters_table(dev);

err_qp_table_मुक्त:
	mlx4_cleanup_qp_table(dev);

err_srq_table_मुक्त:
	mlx4_cleanup_srq_table(dev);

err_cq_table_मुक्त:
	mlx4_cleanup_cq_table(dev);

err_cmd_poll:
	mlx4_cmd_use_polling(dev);

err_eq_table_मुक्त:
	mlx4_cleanup_eq_table(dev);

err_mcg_table_मुक्त:
	अगर (!mlx4_is_slave(dev))
		mlx4_cleanup_mcg_table(dev);

err_mr_table_मुक्त:
	mlx4_cleanup_mr_table(dev);

err_xrcd_table_मुक्त:
	mlx4_cleanup_xrcd_table(dev);

err_pd_table_मुक्त:
	mlx4_cleanup_pd_table(dev);

err_kar_unmap:
	iounmap(priv->kar);

err_uar_मुक्त:
	mlx4_uar_मुक्त(dev, &priv->driver_uar);

err_uar_table_मुक्त:
	mlx4_cleanup_uar_table(dev);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_init_affinity_hपूर्णांक(काष्ठा mlx4_dev *dev, पूर्णांक port, पूर्णांक eqn)
अणु
	पूर्णांक requested_cpu = 0;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_eq *eq;
	पूर्णांक off = 0;
	पूर्णांक i;

	अगर (eqn > dev->caps.num_comp_vectors)
		वापस -EINVAL;

	क्रम (i = 1; i < port; i++)
		off += mlx4_get_eqs_per_port(dev, i);

	requested_cpu = eqn - off - !!(eqn > MLX4_EQ_ASYNC);

	/* Meaning EQs are shared, and this call comes from the second port */
	अगर (requested_cpu < 0)
		वापस 0;

	eq = &priv->eq_table.eq[eqn];

	अगर (!zalloc_cpumask_var(&eq->affinity_mask, GFP_KERNEL))
		वापस -ENOMEM;

	cpumask_set_cpu(requested_cpu, eq->affinity_mask);

	वापस 0;
पूर्ण

अटल व्योम mlx4_enable_msi_x(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा msix_entry *entries;
	पूर्णांक i;
	पूर्णांक port = 0;

	अगर (msi_x) अणु
		पूर्णांक nreq = min3(dev->caps.num_ports *
				(पूर्णांक)num_online_cpus() + 1,
				dev->caps.num_eqs - dev->caps.reserved_eqs,
				MAX_MSIX);

		अगर (msi_x > 1)
			nreq = min_t(पूर्णांक, nreq, msi_x);

		entries = kसुस्मृति(nreq, माप(*entries), GFP_KERNEL);
		अगर (!entries)
			जाओ no_msi;

		क्रम (i = 0; i < nreq; ++i)
			entries[i].entry = i;

		nreq = pci_enable_msix_range(dev->persist->pdev, entries, 2,
					     nreq);

		अगर (nreq < 0 || nreq < MLX4_EQ_ASYNC) अणु
			kमुक्त(entries);
			जाओ no_msi;
		पूर्ण
		/* 1 is reserved क्रम events (asyncrounous EQ) */
		dev->caps.num_comp_vectors = nreq - 1;

		priv->eq_table.eq[MLX4_EQ_ASYNC].irq = entries[0].vector;
		biपंचांगap_zero(priv->eq_table.eq[MLX4_EQ_ASYNC].actv_ports.ports,
			    dev->caps.num_ports);

		क्रम (i = 0; i < dev->caps.num_comp_vectors + 1; i++) अणु
			अगर (i == MLX4_EQ_ASYNC)
				जारी;

			priv->eq_table.eq[i].irq =
				entries[i + 1 - !!(i > MLX4_EQ_ASYNC)].vector;

			अगर (MLX4_IS_LEGACY_EQ_MODE(dev->caps)) अणु
				biपंचांगap_fill(priv->eq_table.eq[i].actv_ports.ports,
					    dev->caps.num_ports);
				/* We करोn't set affinity hपूर्णांक when there
				 * aren't enough EQs
				 */
			पूर्ण अन्यथा अणु
				set_bit(port,
					priv->eq_table.eq[i].actv_ports.ports);
				अगर (mlx4_init_affinity_hपूर्णांक(dev, port + 1, i))
					mlx4_warn(dev, "Couldn't init hint cpumask for EQ %d\n",
						  i);
			पूर्ण
			/* We भागide the Eqs evenly between the two ports.
			 * (dev->caps.num_comp_vectors / dev->caps.num_ports)
			 * refers to the number of Eqs per port
			 * (i.e eqs_per_port). Theoretically, we would like to
			 * ग_लिखो something like (i + 1) % eqs_per_port == 0.
			 * However, since there's an asynchronous Eq, we have
			 * to skip over it by comparing this condition to
			 * !!((i + 1) > MLX4_EQ_ASYNC).
			 */
			अगर ((dev->caps.num_comp_vectors > dev->caps.num_ports) &&
			    ((i + 1) %
			     (dev->caps.num_comp_vectors / dev->caps.num_ports)) ==
			    !!((i + 1) > MLX4_EQ_ASYNC))
				/* If dev->caps.num_comp_vectors < dev->caps.num_ports,
				 * everything is shared anyway.
				 */
				port++;
		पूर्ण

		dev->flags |= MLX4_FLAG_MSI_X;

		kमुक्त(entries);
		वापस;
	पूर्ण

no_msi:
	dev->caps.num_comp_vectors = 1;

	BUG_ON(MLX4_EQ_ASYNC >= 2);
	क्रम (i = 0; i < 2; ++i) अणु
		priv->eq_table.eq[i].irq = dev->persist->pdev->irq;
		अगर (i != MLX4_EQ_ASYNC) अणु
			biपंचांगap_fill(priv->eq_table.eq[i].actv_ports.ports,
				    dev->caps.num_ports);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_init_port_info(काष्ठा mlx4_dev *dev, पूर्णांक port)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlx4_priv(dev));
	काष्ठा mlx4_port_info *info = &mlx4_priv(dev)->port[port];
	पूर्णांक err;

	err = devlink_port_रेजिस्टर(devlink, &info->devlink_port, port);
	अगर (err)
		वापस err;

	/* Ethernet and IB drivers will normally set the port type,
	 * but अगर they are not built set the type now to prevent
	 * devlink_port_type_warn() from firing.
	 */
	अगर (!IS_ENABLED(CONFIG_MLX4_EN) &&
	    dev->caps.port_type[port] == MLX4_PORT_TYPE_ETH)
		devlink_port_type_eth_set(&info->devlink_port, शून्य);
	अन्यथा अगर (!IS_ENABLED(CONFIG_MLX4_INFINIBAND) &&
		 dev->caps.port_type[port] == MLX4_PORT_TYPE_IB)
		devlink_port_type_ib_set(&info->devlink_port, शून्य);

	info->dev = dev;
	info->port = port;
	अगर (!mlx4_is_slave(dev)) अणु
		mlx4_init_mac_table(dev, &info->mac_table);
		mlx4_init_vlan_table(dev, &info->vlan_table);
		mlx4_init_roce_gid_table(dev, &info->gid_table);
		info->base_qpn = mlx4_get_base_qpn(dev, port);
	पूर्ण

	प्र_लिखो(info->dev_name, "mlx4_port%d", port);
	info->port_attr.attr.name = info->dev_name;
	अगर (mlx4_is_mfunc(dev)) अणु
		info->port_attr.attr.mode = 0444;
	पूर्ण अन्यथा अणु
		info->port_attr.attr.mode = 0644;
		info->port_attr.store     = set_port_type;
	पूर्ण
	info->port_attr.show      = show_port_type;
	sysfs_attr_init(&info->port_attr.attr);

	err = device_create_file(&dev->persist->pdev->dev, &info->port_attr);
	अगर (err) अणु
		mlx4_err(dev, "Failed to create file for port %d\n", port);
		devlink_port_unरेजिस्टर(&info->devlink_port);
		info->port = -1;
		वापस err;
	पूर्ण

	प्र_लिखो(info->dev_mtu_name, "mlx4_port%d_mtu", port);
	info->port_mtu_attr.attr.name = info->dev_mtu_name;
	अगर (mlx4_is_mfunc(dev)) अणु
		info->port_mtu_attr.attr.mode = 0444;
	पूर्ण अन्यथा अणु
		info->port_mtu_attr.attr.mode = 0644;
		info->port_mtu_attr.store     = set_port_ib_mtu;
	पूर्ण
	info->port_mtu_attr.show      = show_port_ib_mtu;
	sysfs_attr_init(&info->port_mtu_attr.attr);

	err = device_create_file(&dev->persist->pdev->dev,
				 &info->port_mtu_attr);
	अगर (err) अणु
		mlx4_err(dev, "Failed to create mtu file for port %d\n", port);
		device_हटाओ_file(&info->dev->persist->pdev->dev,
				   &info->port_attr);
		devlink_port_unरेजिस्टर(&info->devlink_port);
		info->port = -1;
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx4_cleanup_port_info(काष्ठा mlx4_port_info *info)
अणु
	अगर (info->port < 0)
		वापस;

	device_हटाओ_file(&info->dev->persist->pdev->dev, &info->port_attr);
	device_हटाओ_file(&info->dev->persist->pdev->dev,
			   &info->port_mtu_attr);
	devlink_port_unरेजिस्टर(&info->devlink_port);

#अगर_घोषित CONFIG_RFS_ACCEL
	मुक्त_irq_cpu_rmap(info->rmap);
	info->rmap = शून्य;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक mlx4_init_steering(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक num_entries = dev->caps.num_ports;
	पूर्णांक i, j;

	priv->steer = kसुस्मृति(num_entries, माप(काष्ठा mlx4_steer),
			      GFP_KERNEL);
	अगर (!priv->steer)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_entries; i++)
		क्रम (j = 0; j < MLX4_NUM_STEERS; j++) अणु
			INIT_LIST_HEAD(&priv->steer[i].promisc_qps[j]);
			INIT_LIST_HEAD(&priv->steer[i].steer_entries[j]);
		पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mlx4_clear_steering(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_steer_index *entry, *पंचांगp_entry;
	काष्ठा mlx4_promisc_qp *pqp, *पंचांगp_pqp;
	पूर्णांक num_entries = dev->caps.num_ports;
	पूर्णांक i, j;

	क्रम (i = 0; i < num_entries; i++) अणु
		क्रम (j = 0; j < MLX4_NUM_STEERS; j++) अणु
			list_क्रम_each_entry_safe(pqp, पंचांगp_pqp,
						 &priv->steer[i].promisc_qps[j],
						 list) अणु
				list_del(&pqp->list);
				kमुक्त(pqp);
			पूर्ण
			list_क्रम_each_entry_safe(entry, पंचांगp_entry,
						 &priv->steer[i].steer_entries[j],
						 list) अणु
				list_del(&entry->list);
				list_क्रम_each_entry_safe(pqp, पंचांगp_pqp,
							 &entry->duplicates,
							 list) अणु
					list_del(&pqp->list);
					kमुक्त(pqp);
				पूर्ण
				kमुक्त(entry);
			पूर्ण
		पूर्ण
	पूर्ण
	kमुक्त(priv->steer);
पूर्ण

अटल पूर्णांक extended_func_num(काष्ठा pci_dev *pdev)
अणु
	वापस PCI_SLOT(pdev->devfn) * 8 + PCI_FUNC(pdev->devfn);
पूर्ण

#घोषणा MLX4_OWNER_BASE	0x8069c
#घोषणा MLX4_OWNER_SIZE	4

अटल पूर्णांक mlx4_get_ownership(काष्ठा mlx4_dev *dev)
अणु
	व्योम __iomem *owner;
	u32 ret;

	अगर (pci_channel_offline(dev->persist->pdev))
		वापस -EIO;

	owner = ioremap(pci_resource_start(dev->persist->pdev, 0) +
			MLX4_OWNER_BASE,
			MLX4_OWNER_SIZE);
	अगर (!owner) अणु
		mlx4_err(dev, "Failed to obtain ownership bit\n");
		वापस -ENOMEM;
	पूर्ण

	ret = पढ़ोl(owner);
	iounmap(owner);
	वापस (पूर्णांक) !!ret;
पूर्ण

अटल व्योम mlx4_मुक्त_ownership(काष्ठा mlx4_dev *dev)
अणु
	व्योम __iomem *owner;

	अगर (pci_channel_offline(dev->persist->pdev))
		वापस;

	owner = ioremap(pci_resource_start(dev->persist->pdev, 0) +
			MLX4_OWNER_BASE,
			MLX4_OWNER_SIZE);
	अगर (!owner) अणु
		mlx4_err(dev, "Failed to obtain ownership bit\n");
		वापस;
	पूर्ण
	ग_लिखोl(0, owner);
	msleep(1000);
	iounmap(owner);
पूर्ण

#घोषणा SRIOV_VALID_STATE(flags) (!!((flags) & MLX4_FLAG_SRIOV)	==\
				  !!((flags) & MLX4_FLAG_MASTER))

अटल u64 mlx4_enable_sriov(काष्ठा mlx4_dev *dev, काष्ठा pci_dev *pdev,
			     u8 total_vfs, पूर्णांक existing_vfs, पूर्णांक reset_flow)
अणु
	u64 dev_flags = dev->flags;
	पूर्णांक err = 0;
	पूर्णांक fw_enabled_sriov_vfs = min(pci_sriov_get_totalvfs(pdev),
					MLX4_MAX_NUM_VF);

	अगर (reset_flow) अणु
		dev->dev_vfs = kसुस्मृति(total_vfs, माप(*dev->dev_vfs),
				       GFP_KERNEL);
		अगर (!dev->dev_vfs)
			जाओ मुक्त_mem;
		वापस dev_flags;
	पूर्ण

	atomic_inc(&pf_loading);
	अगर (dev->flags &  MLX4_FLAG_SRIOV) अणु
		अगर (existing_vfs != total_vfs) अणु
			mlx4_err(dev, "SR-IOV was already enabled, but with num_vfs (%d) different than requested (%d)\n",
				 existing_vfs, total_vfs);
			total_vfs = existing_vfs;
		पूर्ण
	पूर्ण

	dev->dev_vfs = kसुस्मृति(total_vfs, माप(*dev->dev_vfs), GFP_KERNEL);
	अगर (शून्य == dev->dev_vfs) अणु
		mlx4_err(dev, "Failed to allocate memory for VFs\n");
		जाओ disable_sriov;
	पूर्ण

	अगर (!(dev->flags &  MLX4_FLAG_SRIOV)) अणु
		अगर (total_vfs > fw_enabled_sriov_vfs) अणु
			mlx4_err(dev, "requested vfs (%d) > available vfs (%d). Continuing without SR_IOV\n",
				 total_vfs, fw_enabled_sriov_vfs);
			err = -ENOMEM;
			जाओ disable_sriov;
		पूर्ण
		mlx4_warn(dev, "Enabling SR-IOV with %d VFs\n", total_vfs);
		err = pci_enable_sriov(pdev, total_vfs);
	पूर्ण
	अगर (err) अणु
		mlx4_err(dev, "Failed to enable SR-IOV, continuing without SR-IOV (err = %d)\n",
			 err);
		जाओ disable_sriov;
	पूर्ण अन्यथा अणु
		mlx4_warn(dev, "Running in master mode\n");
		dev_flags |= MLX4_FLAG_SRIOV |
			MLX4_FLAG_MASTER;
		dev_flags &= ~MLX4_FLAG_SLAVE;
		dev->persist->num_vfs = total_vfs;
	पूर्ण
	वापस dev_flags;

disable_sriov:
	atomic_dec(&pf_loading);
मुक्त_mem:
	dev->persist->num_vfs = 0;
	kमुक्त(dev->dev_vfs);
	dev->dev_vfs = शून्य;
	वापस dev_flags & ~MLX4_FLAG_MASTER;
पूर्ण

क्रमागत अणु
	MLX4_DEV_CAP_CHECK_NUM_VFS_ABOVE_64 = -1,
पूर्ण;

अटल पूर्णांक mlx4_check_dev_cap(काष्ठा mlx4_dev *dev, काष्ठा mlx4_dev_cap *dev_cap,
			      पूर्णांक *nvfs)
अणु
	पूर्णांक requested_vfs = nvfs[0] + nvfs[1] + nvfs[2];
	/* Checking क्रम 64 VFs as a limitation of CX2 */
	अगर (!(dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_80_VFS) &&
	    requested_vfs >= 64) अणु
		mlx4_err(dev, "Requested %d VFs, but FW does not support more than 64\n",
			 requested_vfs);
		वापस MLX4_DEV_CAP_CHECK_NUM_VFS_ABOVE_64;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_pci_enable_device(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा pci_dev *pdev = dev->persist->pdev;
	पूर्णांक err = 0;

	mutex_lock(&dev->persist->pci_status_mutex);
	अगर (dev->persist->pci_status == MLX4_PCI_STATUS_DISABLED) अणु
		err = pci_enable_device(pdev);
		अगर (!err)
			dev->persist->pci_status = MLX4_PCI_STATUS_ENABLED;
	पूर्ण
	mutex_unlock(&dev->persist->pci_status_mutex);

	वापस err;
पूर्ण

अटल व्योम mlx4_pci_disable_device(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा pci_dev *pdev = dev->persist->pdev;

	mutex_lock(&dev->persist->pci_status_mutex);
	अगर (dev->persist->pci_status == MLX4_PCI_STATUS_ENABLED) अणु
		pci_disable_device(pdev);
		dev->persist->pci_status = MLX4_PCI_STATUS_DISABLED;
	पूर्ण
	mutex_unlock(&dev->persist->pci_status_mutex);
पूर्ण

अटल पूर्णांक mlx4_load_one(काष्ठा pci_dev *pdev, पूर्णांक pci_dev_data,
			 पूर्णांक total_vfs, पूर्णांक *nvfs, काष्ठा mlx4_priv *priv,
			 पूर्णांक reset_flow)
अणु
	काष्ठा mlx4_dev *dev;
	अचिन्हित sum = 0;
	पूर्णांक err;
	पूर्णांक port;
	पूर्णांक i;
	काष्ठा mlx4_dev_cap *dev_cap = शून्य;
	पूर्णांक existing_vfs = 0;

	dev = &priv->dev;

	INIT_LIST_HEAD(&priv->ctx_list);
	spin_lock_init(&priv->ctx_lock);

	mutex_init(&priv->port_mutex);
	mutex_init(&priv->bond_mutex);

	INIT_LIST_HEAD(&priv->pgdir_list);
	mutex_init(&priv->pgdir_mutex);
	spin_lock_init(&priv->cmd.context_lock);

	INIT_LIST_HEAD(&priv->bf_list);
	mutex_init(&priv->bf_mutex);

	dev->rev_id = pdev->revision;
	dev->numa_node = dev_to_node(&pdev->dev);

	/* Detect अगर this device is a भव function */
	अगर (pci_dev_data & MLX4_PCI_DEV_IS_VF) अणु
		mlx4_warn(dev, "Detected virtual function - running in slave mode\n");
		dev->flags |= MLX4_FLAG_SLAVE;
	पूर्ण अन्यथा अणु
		/* We reset the device and enable SRIOV only क्रम physical
		 * devices.  Try to claim ownership on the device;
		 * अगर alपढ़ोy taken, skip -- करो not allow multiple PFs */
		err = mlx4_get_ownership(dev);
		अगर (err) अणु
			अगर (err < 0)
				वापस err;
			अन्यथा अणु
				mlx4_warn(dev, "Multiple PFs not yet supported - Skipping PF\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		atomic_set(&priv->opreq_count, 0);
		INIT_WORK(&priv->opreq_task, mlx4_opreq_action);

		/*
		 * Now reset the HCA beक्रमe we touch the PCI capabilities or
		 * attempt a firmware command, since a boot ROM may have left
		 * the HCA in an undefined state.
		 */
		err = mlx4_reset(dev);
		अगर (err) अणु
			mlx4_err(dev, "Failed to reset HCA, aborting\n");
			जाओ err_sriov;
		पूर्ण

		अगर (total_vfs) अणु
			dev->flags = MLX4_FLAG_MASTER;
			existing_vfs = pci_num_vf(pdev);
			अगर (existing_vfs)
				dev->flags |= MLX4_FLAG_SRIOV;
			dev->persist->num_vfs = total_vfs;
		पूर्ण
	पूर्ण

	/* on load हटाओ any previous indication of पूर्णांकernal error,
	 * device is up.
	 */
	dev->persist->state = MLX4_DEVICE_STATE_UP;

slave_start:
	err = mlx4_cmd_init(dev);
	अगर (err) अणु
		mlx4_err(dev, "Failed to init command interface, aborting\n");
		जाओ err_sriov;
	पूर्ण

	/* In slave functions, the communication channel must be initialized
	 * beक्रमe posting commands. Also, init num_slaves beक्रमe calling
	 * mlx4_init_hca */
	अगर (mlx4_is_mfunc(dev)) अणु
		अगर (mlx4_is_master(dev)) अणु
			dev->num_slaves = MLX4_MAX_NUM_SLAVES;

		पूर्ण अन्यथा अणु
			dev->num_slaves = 0;
			err = mlx4_multi_func_init(dev);
			अगर (err) अणु
				mlx4_err(dev, "Failed to init slave mfunc interface, aborting\n");
				जाओ err_cmd;
			पूर्ण
		पूर्ण
	पूर्ण

	err = mlx4_init_fw(dev);
	अगर (err) अणु
		mlx4_err(dev, "Failed to init fw, aborting.\n");
		जाओ err_mfunc;
	पूर्ण

	अगर (mlx4_is_master(dev)) अणु
		/* when we hit the जाओ slave_start below, dev_cap alपढ़ोy initialized */
		अगर (!dev_cap) अणु
			dev_cap = kzalloc(माप(*dev_cap), GFP_KERNEL);

			अगर (!dev_cap) अणु
				err = -ENOMEM;
				जाओ err_fw;
			पूर्ण

			err = mlx4_QUERY_DEV_CAP(dev, dev_cap);
			अगर (err) अणु
				mlx4_err(dev, "QUERY_DEV_CAP command failed, aborting.\n");
				जाओ err_fw;
			पूर्ण

			अगर (mlx4_check_dev_cap(dev, dev_cap, nvfs))
				जाओ err_fw;

			अगर (!(dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_SYS_EQS)) अणु
				u64 dev_flags = mlx4_enable_sriov(dev, pdev,
								  total_vfs,
								  existing_vfs,
								  reset_flow);

				mlx4_बंद_fw(dev);
				mlx4_cmd_cleanup(dev, MLX4_CMD_CLEANUP_ALL);
				dev->flags = dev_flags;
				अगर (!SRIOV_VALID_STATE(dev->flags)) अणु
					mlx4_err(dev, "Invalid SRIOV state\n");
					जाओ err_sriov;
				पूर्ण
				err = mlx4_reset(dev);
				अगर (err) अणु
					mlx4_err(dev, "Failed to reset HCA, aborting.\n");
					जाओ err_sriov;
				पूर्ण
				जाओ slave_start;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Legacy mode FW requires SRIOV to be enabled beक्रमe
			 * करोing QUERY_DEV_CAP, since max_eq's value is dअगरferent अगर
			 * SRIOV is enabled.
			 */
			स_रखो(dev_cap, 0, माप(*dev_cap));
			err = mlx4_QUERY_DEV_CAP(dev, dev_cap);
			अगर (err) अणु
				mlx4_err(dev, "QUERY_DEV_CAP command failed, aborting.\n");
				जाओ err_fw;
			पूर्ण

			अगर (mlx4_check_dev_cap(dev, dev_cap, nvfs))
				जाओ err_fw;
		पूर्ण
	पूर्ण

	err = mlx4_init_hca(dev);
	अगर (err) अणु
		अगर (err == -EACCES) अणु
			/* Not primary Physical function
			 * Running in slave mode */
			mlx4_cmd_cleanup(dev, MLX4_CMD_CLEANUP_ALL);
			/* We're not a PF */
			अगर (dev->flags & MLX4_FLAG_SRIOV) अणु
				अगर (!existing_vfs)
					pci_disable_sriov(pdev);
				अगर (mlx4_is_master(dev) && !reset_flow)
					atomic_dec(&pf_loading);
				dev->flags &= ~MLX4_FLAG_SRIOV;
			पूर्ण
			अगर (!mlx4_is_slave(dev))
				mlx4_मुक्त_ownership(dev);
			dev->flags |= MLX4_FLAG_SLAVE;
			dev->flags &= ~MLX4_FLAG_MASTER;
			जाओ slave_start;
		पूर्ण अन्यथा
			जाओ err_fw;
	पूर्ण

	अगर (mlx4_is_master(dev) && (dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_SYS_EQS)) अणु
		u64 dev_flags = mlx4_enable_sriov(dev, pdev, total_vfs,
						  existing_vfs, reset_flow);

		अगर ((dev->flags ^ dev_flags) & (MLX4_FLAG_MASTER | MLX4_FLAG_SLAVE)) अणु
			mlx4_cmd_cleanup(dev, MLX4_CMD_CLEANUP_VHCR);
			dev->flags = dev_flags;
			err = mlx4_cmd_init(dev);
			अगर (err) अणु
				/* Only VHCR is cleaned up, so could still
				 * send FW commands
				 */
				mlx4_err(dev, "Failed to init VHCR command interface, aborting\n");
				जाओ err_बंद;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev->flags = dev_flags;
		पूर्ण

		अगर (!SRIOV_VALID_STATE(dev->flags)) अणु
			mlx4_err(dev, "Invalid SRIOV state\n");
			जाओ err_बंद;
		पूर्ण
	पूर्ण

	/* check अगर the device is functioning at its maximum possible speed.
	 * No वापस code क्रम this call, just warn the user in हाल of PCI
	 * express device capabilities are under-satisfied by the bus.
	 */
	अगर (!mlx4_is_slave(dev))
		pcie_prपूर्णांक_link_status(dev->persist->pdev);

	/* In master functions, the communication channel must be initialized
	 * after obtaining its address from fw */
	अगर (mlx4_is_master(dev)) अणु
		अगर (dev->caps.num_ports < 2 &&
		    num_vfs_argc > 1) अणु
			err = -EINVAL;
			mlx4_err(dev,
				 "Error: Trying to configure VFs on port 2, but HCA has only %d physical ports\n",
				 dev->caps.num_ports);
			जाओ err_बंद;
		पूर्ण
		स_नकल(dev->persist->nvfs, nvfs, माप(dev->persist->nvfs));

		क्रम (i = 0;
		     i < माप(dev->persist->nvfs)/
		     माप(dev->persist->nvfs[0]); i++) अणु
			अचिन्हित j;

			क्रम (j = 0; j < dev->persist->nvfs[i]; ++sum, ++j) अणु
				dev->dev_vfs[sum].min_port = i < 2 ? i + 1 : 1;
				dev->dev_vfs[sum].n_ports = i < 2 ? 1 :
					dev->caps.num_ports;
			पूर्ण
		पूर्ण

		/* In master functions, the communication channel
		 * must be initialized after obtaining its address from fw
		 */
		err = mlx4_multi_func_init(dev);
		अगर (err) अणु
			mlx4_err(dev, "Failed to init master mfunc interface, aborting.\n");
			जाओ err_बंद;
		पूर्ण
	पूर्ण

	err = mlx4_alloc_eq_table(dev);
	अगर (err)
		जाओ err_master_mfunc;

	biपंचांगap_zero(priv->msix_ctl.pool_bm, MAX_MSIX);
	mutex_init(&priv->msix_ctl.pool_lock);

	mlx4_enable_msi_x(dev);
	अगर ((mlx4_is_mfunc(dev)) &&
	    !(dev->flags & MLX4_FLAG_MSI_X)) अणु
		err = -EOPNOTSUPP;
		mlx4_err(dev, "INTx is not supported in multi-function mode, aborting\n");
		जाओ err_मुक्त_eq;
	पूर्ण

	अगर (!mlx4_is_slave(dev)) अणु
		err = mlx4_init_steering(dev);
		अगर (err)
			जाओ err_disable_msix;
	पूर्ण

	mlx4_init_quotas(dev);

	err = mlx4_setup_hca(dev);
	अगर (err == -EBUSY && (dev->flags & MLX4_FLAG_MSI_X) &&
	    !mlx4_is_mfunc(dev)) अणु
		dev->flags &= ~MLX4_FLAG_MSI_X;
		dev->caps.num_comp_vectors = 1;
		pci_disable_msix(pdev);
		err = mlx4_setup_hca(dev);
	पूर्ण

	अगर (err)
		जाओ err_steer;

	/* When PF resources are पढ़ोy arm its comm channel to enable
	 * getting commands
	 */
	अगर (mlx4_is_master(dev)) अणु
		err = mlx4_ARM_COMM_CHANNEL(dev);
		अगर (err) अणु
			mlx4_err(dev, " Failed to arm comm channel eq: %x\n",
				 err);
			जाओ err_steer;
		पूर्ण
	पूर्ण

	क्रम (port = 1; port <= dev->caps.num_ports; port++) अणु
		err = mlx4_init_port_info(dev, port);
		अगर (err)
			जाओ err_port;
	पूर्ण

	priv->v2p.port1 = 1;
	priv->v2p.port2 = 2;

	err = mlx4_रेजिस्टर_device(dev);
	अगर (err)
		जाओ err_port;

	mlx4_request_modules(dev);

	mlx4_sense_init(dev);
	mlx4_start_sense(dev);

	priv->हटाओd = 0;

	अगर (mlx4_is_master(dev) && dev->persist->num_vfs && !reset_flow)
		atomic_dec(&pf_loading);

	kमुक्त(dev_cap);
	वापस 0;

err_port:
	क्रम (--port; port >= 1; --port)
		mlx4_cleanup_port_info(&priv->port[port]);

	mlx4_cleanup_शेष_counters(dev);
	अगर (!mlx4_is_slave(dev))
		mlx4_cleanup_counters_table(dev);
	mlx4_cleanup_qp_table(dev);
	mlx4_cleanup_srq_table(dev);
	mlx4_cleanup_cq_table(dev);
	mlx4_cmd_use_polling(dev);
	mlx4_cleanup_eq_table(dev);
	mlx4_cleanup_mcg_table(dev);
	mlx4_cleanup_mr_table(dev);
	mlx4_cleanup_xrcd_table(dev);
	mlx4_cleanup_pd_table(dev);
	mlx4_cleanup_uar_table(dev);

err_steer:
	अगर (!mlx4_is_slave(dev))
		mlx4_clear_steering(dev);

err_disable_msix:
	अगर (dev->flags & MLX4_FLAG_MSI_X)
		pci_disable_msix(pdev);

err_मुक्त_eq:
	mlx4_मुक्त_eq_table(dev);

err_master_mfunc:
	अगर (mlx4_is_master(dev)) अणु
		mlx4_मुक्त_resource_tracker(dev, RES_TR_FREE_STRUCTS_ONLY);
		mlx4_multi_func_cleanup(dev);
	पूर्ण

	अगर (mlx4_is_slave(dev))
		mlx4_slave_destroy_special_qp_cap(dev);

err_बंद:
	mlx4_बंद_hca(dev);

err_fw:
	mlx4_बंद_fw(dev);

err_mfunc:
	अगर (mlx4_is_slave(dev))
		mlx4_multi_func_cleanup(dev);

err_cmd:
	mlx4_cmd_cleanup(dev, MLX4_CMD_CLEANUP_ALL);

err_sriov:
	अगर (dev->flags & MLX4_FLAG_SRIOV && !existing_vfs) अणु
		pci_disable_sriov(pdev);
		dev->flags &= ~MLX4_FLAG_SRIOV;
	पूर्ण

	अगर (mlx4_is_master(dev) && dev->persist->num_vfs && !reset_flow)
		atomic_dec(&pf_loading);

	kमुक्त(priv->dev.dev_vfs);

	अगर (!mlx4_is_slave(dev))
		mlx4_मुक्त_ownership(dev);

	kमुक्त(dev_cap);
	वापस err;
पूर्ण

अटल पूर्णांक __mlx4_init_one(काष्ठा pci_dev *pdev, पूर्णांक pci_dev_data,
			   काष्ठा mlx4_priv *priv)
अणु
	पूर्णांक err;
	पूर्णांक nvfs[MLX4_MAX_PORTS + 1] = अणु0, 0, 0पूर्ण;
	पूर्णांक prb_vf[MLX4_MAX_PORTS + 1] = अणु0, 0, 0पूर्ण;
	स्थिर पूर्णांक param_map[MLX4_MAX_PORTS + 1][MLX4_MAX_PORTS + 1] = अणु
		अणु2, 0, 0पूर्ण, अणु0, 1, 2पूर्ण, अणु0, 1, 2पूर्ण पूर्ण;
	अचिन्हित total_vfs = 0;
	अचिन्हित पूर्णांक i;

	pr_info(DRV_NAME ": Initializing %s\n", pci_name(pdev));

	err = mlx4_pci_enable_device(&priv->dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot enable PCI device, aborting\n");
		वापस err;
	पूर्ण

	/* Due to requirement that all VFs and the PF are *guaranteed* 2 MACS
	 * per port, we must limit the number of VFs to 63 (since their are
	 * 128 MACs)
	 */
	क्रम (i = 0; i < ARRAY_SIZE(nvfs) && i < num_vfs_argc;
	     total_vfs += nvfs[param_map[num_vfs_argc - 1][i]], i++) अणु
		nvfs[param_map[num_vfs_argc - 1][i]] = num_vfs[i];
		अगर (nvfs[i] < 0) अणु
			dev_err(&pdev->dev, "num_vfs module parameter cannot be negative\n");
			err = -EINVAL;
			जाओ err_disable_pdev;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(prb_vf) && i < probe_vfs_argc;
	     i++) अणु
		prb_vf[param_map[probe_vfs_argc - 1][i]] = probe_vf[i];
		अगर (prb_vf[i] < 0 || prb_vf[i] > nvfs[i]) अणु
			dev_err(&pdev->dev, "probe_vf module parameter cannot be negative or greater than num_vfs\n");
			err = -EINVAL;
			जाओ err_disable_pdev;
		पूर्ण
	पूर्ण
	अगर (total_vfs > MLX4_MAX_NUM_VF) अणु
		dev_err(&pdev->dev,
			"Requested more VF's (%d) than allowed by hw (%d)\n",
			total_vfs, MLX4_MAX_NUM_VF);
		err = -EINVAL;
		जाओ err_disable_pdev;
	पूर्ण

	क्रम (i = 0; i < MLX4_MAX_PORTS; i++) अणु
		अगर (nvfs[i] + nvfs[2] > MLX4_MAX_NUM_VF_P_PORT) अणु
			dev_err(&pdev->dev,
				"Requested more VF's (%d) for port (%d) than allowed by driver (%d)\n",
				nvfs[i] + nvfs[2], i + 1,
				MLX4_MAX_NUM_VF_P_PORT);
			err = -EINVAL;
			जाओ err_disable_pdev;
		पूर्ण
	पूर्ण

	/* Check क्रम BARs. */
	अगर (!(pci_dev_data & MLX4_PCI_DEV_IS_VF) &&
	    !(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev, "Missing DCS, aborting (driver_data: 0x%x, pci_resource_flags(pdev, 0):0x%lx)\n",
			pci_dev_data, pci_resource_flags(pdev, 0));
		err = -ENODEV;
		जाओ err_disable_pdev;
	पूर्ण
	अगर (!(pci_resource_flags(pdev, 2) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev, "Missing UAR, aborting\n");
		err = -ENODEV;
		जाओ err_disable_pdev;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "Couldn't get PCI resources, aborting\n");
		जाओ err_disable_pdev;
	पूर्ण

	pci_set_master(pdev);

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err) अणु
		dev_warn(&pdev->dev, "Warning: couldn't set 64-bit PCI DMA mask\n");
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "Can't set PCI DMA mask, aborting\n");
			जाओ err_release_regions;
		पूर्ण
	पूर्ण
	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err) अणु
		dev_warn(&pdev->dev, "Warning: couldn't set 64-bit consistent PCI DMA mask\n");
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "Can't set consistent PCI DMA mask, aborting\n");
			जाओ err_release_regions;
		पूर्ण
	पूर्ण

	/* Allow large DMA segments, up to the firmware limit of 1 GB */
	dma_set_max_seg_size(&pdev->dev, 1024 * 1024 * 1024);
	/* Detect अगर this device is a भव function */
	अगर (pci_dev_data & MLX4_PCI_DEV_IS_VF) अणु
		/* When acting as pf, we normally skip vfs unless explicitly
		 * requested to probe them.
		 */
		अगर (total_vfs) अणु
			अचिन्हित vfs_offset = 0;

			क्रम (i = 0; i < ARRAY_SIZE(nvfs) &&
			     vfs_offset + nvfs[i] < extended_func_num(pdev);
			     vfs_offset += nvfs[i], i++)
				;
			अगर (i == ARRAY_SIZE(nvfs)) अणु
				err = -ENODEV;
				जाओ err_release_regions;
			पूर्ण
			अगर ((extended_func_num(pdev) - vfs_offset)
			    > prb_vf[i]) अणु
				dev_warn(&pdev->dev, "Skipping virtual function:%d\n",
					 extended_func_num(pdev));
				err = -ENODEV;
				जाओ err_release_regions;
			पूर्ण
		पूर्ण
	पूर्ण

	err = mlx4_crdump_init(&priv->dev);
	अगर (err)
		जाओ err_release_regions;

	err = mlx4_catas_init(&priv->dev);
	अगर (err)
		जाओ err_crdump;

	err = mlx4_load_one(pdev, pci_dev_data, total_vfs, nvfs, priv, 0);
	अगर (err)
		जाओ err_catas;

	वापस 0;

err_catas:
	mlx4_catas_end(&priv->dev);

err_crdump:
	mlx4_crdump_end(&priv->dev);

err_release_regions:
	pci_release_regions(pdev);

err_disable_pdev:
	mlx4_pci_disable_device(&priv->dev);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_devlink_port_type_set(काष्ठा devlink_port *devlink_port,
				      क्रमागत devlink_port_type port_type)
अणु
	काष्ठा mlx4_port_info *info = container_of(devlink_port,
						   काष्ठा mlx4_port_info,
						   devlink_port);
	क्रमागत mlx4_port_type mlx4_port_type;

	चयन (port_type) अणु
	हाल DEVLINK_PORT_TYPE_AUTO:
		mlx4_port_type = MLX4_PORT_TYPE_AUTO;
		अवरोध;
	हाल DEVLINK_PORT_TYPE_ETH:
		mlx4_port_type = MLX4_PORT_TYPE_ETH;
		अवरोध;
	हाल DEVLINK_PORT_TYPE_IB:
		mlx4_port_type = MLX4_PORT_TYPE_IB;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस __set_port_type(info, mlx4_port_type);
पूर्ण

अटल व्योम mlx4_devlink_param_load_driverinit_values(काष्ठा devlink *devlink)
अणु
	काष्ठा mlx4_priv *priv = devlink_priv(devlink);
	काष्ठा mlx4_dev *dev = &priv->dev;
	काष्ठा mlx4_fw_crdump *crdump = &dev->persist->crdump;
	जोड़ devlink_param_value saved_value;
	पूर्णांक err;

	err = devlink_param_driverinit_value_get(devlink,
						 DEVLINK_PARAM_GENERIC_ID_INT_ERR_RESET,
						 &saved_value);
	अगर (!err && mlx4_पूर्णांकernal_err_reset != saved_value.vbool) अणु
		mlx4_पूर्णांकernal_err_reset = saved_value.vbool;
		/* Notअगरy on value changed on runसमय configuration mode */
		devlink_param_value_changed(devlink,
					    DEVLINK_PARAM_GENERIC_ID_INT_ERR_RESET);
	पूर्ण
	err = devlink_param_driverinit_value_get(devlink,
						 DEVLINK_PARAM_GENERIC_ID_MAX_MACS,
						 &saved_value);
	अगर (!err)
		log_num_mac = order_base_2(saved_value.vu32);
	err = devlink_param_driverinit_value_get(devlink,
						 MLX4_DEVLINK_PARAM_ID_ENABLE_64B_CQE_EQE,
						 &saved_value);
	अगर (!err)
		enable_64b_cqe_eqe = saved_value.vbool;
	err = devlink_param_driverinit_value_get(devlink,
						 MLX4_DEVLINK_PARAM_ID_ENABLE_4K_UAR,
						 &saved_value);
	अगर (!err)
		enable_4k_uar = saved_value.vbool;
	err = devlink_param_driverinit_value_get(devlink,
						 DEVLINK_PARAM_GENERIC_ID_REGION_SNAPSHOT,
						 &saved_value);
	अगर (!err && crdump->snapshot_enable != saved_value.vbool) अणु
		crdump->snapshot_enable = saved_value.vbool;
		devlink_param_value_changed(devlink,
					    DEVLINK_PARAM_GENERIC_ID_REGION_SNAPSHOT);
	पूर्ण
पूर्ण

अटल व्योम mlx4_restart_one_करोwn(काष्ठा pci_dev *pdev);
अटल पूर्णांक mlx4_restart_one_up(काष्ठा pci_dev *pdev, bool reload,
			       काष्ठा devlink *devlink);

अटल पूर्णांक mlx4_devlink_reload_करोwn(काष्ठा devlink *devlink, bool netns_change,
				    क्रमागत devlink_reload_action action,
				    क्रमागत devlink_reload_limit limit,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx4_priv *priv = devlink_priv(devlink);
	काष्ठा mlx4_dev *dev = &priv->dev;
	काष्ठा mlx4_dev_persistent *persist = dev->persist;

	अगर (netns_change) अणु
		NL_SET_ERR_MSG_MOD(extack, "Namespace change is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (persist->num_vfs)
		mlx4_warn(persist->dev, "Reload performed on PF, will cause reset on operating Virtual Functions\n");
	mlx4_restart_one_करोwn(persist->pdev);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_devlink_reload_up(काष्ठा devlink *devlink, क्रमागत devlink_reload_action action,
				  क्रमागत devlink_reload_limit limit, u32 *actions_perक्रमmed,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx4_priv *priv = devlink_priv(devlink);
	काष्ठा mlx4_dev *dev = &priv->dev;
	काष्ठा mlx4_dev_persistent *persist = dev->persist;
	पूर्णांक err;

	*actions_perक्रमmed = BIT(DEVLINK_RELOAD_ACTION_DRIVER_REINIT);
	err = mlx4_restart_one_up(persist->pdev, true, devlink);
	अगर (err)
		mlx4_err(persist->dev, "mlx4_restart_one_up failed, ret=%d\n",
			 err);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा devlink_ops mlx4_devlink_ops = अणु
	.port_type_set	= mlx4_devlink_port_type_set,
	.reload_actions = BIT(DEVLINK_RELOAD_ACTION_DRIVER_REINIT),
	.reload_करोwn	= mlx4_devlink_reload_करोwn,
	.reload_up	= mlx4_devlink_reload_up,
पूर्ण;

अटल पूर्णांक mlx4_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा devlink *devlink;
	काष्ठा mlx4_priv *priv;
	काष्ठा mlx4_dev *dev;
	पूर्णांक ret;

	prपूर्णांकk_once(KERN_INFO "%s", mlx4_version);

	devlink = devlink_alloc(&mlx4_devlink_ops, माप(*priv));
	अगर (!devlink)
		वापस -ENOMEM;
	priv = devlink_priv(devlink);

	dev       = &priv->dev;
	dev->persist = kzalloc(माप(*dev->persist), GFP_KERNEL);
	अगर (!dev->persist) अणु
		ret = -ENOMEM;
		जाओ err_devlink_मुक्त;
	पूर्ण
	dev->persist->pdev = pdev;
	dev->persist->dev = dev;
	pci_set_drvdata(pdev, dev->persist);
	priv->pci_dev_data = id->driver_data;
	mutex_init(&dev->persist->device_state_mutex);
	mutex_init(&dev->persist->पूर्णांकerface_state_mutex);
	mutex_init(&dev->persist->pci_status_mutex);

	ret = devlink_रेजिस्टर(devlink, &pdev->dev);
	अगर (ret)
		जाओ err_persist_मुक्त;
	ret = devlink_params_रेजिस्टर(devlink, mlx4_devlink_params,
				      ARRAY_SIZE(mlx4_devlink_params));
	अगर (ret)
		जाओ err_devlink_unरेजिस्टर;
	mlx4_devlink_set_params_init_values(devlink);
	ret =  __mlx4_init_one(pdev, id->driver_data, priv);
	अगर (ret)
		जाओ err_params_unरेजिस्टर;

	devlink_params_publish(devlink);
	devlink_reload_enable(devlink);
	pci_save_state(pdev);
	वापस 0;

err_params_unरेजिस्टर:
	devlink_params_unरेजिस्टर(devlink, mlx4_devlink_params,
				  ARRAY_SIZE(mlx4_devlink_params));
err_devlink_unरेजिस्टर:
	devlink_unरेजिस्टर(devlink);
err_persist_मुक्त:
	kमुक्त(dev->persist);
err_devlink_मुक्त:
	devlink_मुक्त(devlink);
	वापस ret;
पूर्ण

अटल व्योम mlx4_clean_dev(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_dev_persistent *persist = dev->persist;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	अचिन्हित दीर्घ	flags = (dev->flags & RESET_PERSIST_MASK_FLAGS);

	स_रखो(priv, 0, माप(*priv));
	priv->dev.persist = persist;
	priv->dev.flags = flags;
पूर्ण

अटल व्योम mlx4_unload_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx4_dev_persistent *persist = pci_get_drvdata(pdev);
	काष्ठा mlx4_dev  *dev  = persist->dev;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक               pci_dev_data;
	पूर्णांक p, i;

	अगर (priv->हटाओd)
		वापस;

	/* saving current ports type क्रम further use */
	क्रम (i = 0; i < dev->caps.num_ports; i++) अणु
		dev->persist->curr_port_type[i] = dev->caps.port_type[i + 1];
		dev->persist->curr_port_poss_type[i] = dev->caps.
						       possible_type[i + 1];
	पूर्ण

	pci_dev_data = priv->pci_dev_data;

	mlx4_stop_sense(dev);
	mlx4_unरेजिस्टर_device(dev);

	क्रम (p = 1; p <= dev->caps.num_ports; p++) अणु
		mlx4_cleanup_port_info(&priv->port[p]);
		mlx4_CLOSE_PORT(dev, p);
	पूर्ण

	अगर (mlx4_is_master(dev))
		mlx4_मुक्त_resource_tracker(dev,
					   RES_TR_FREE_SLAVES_ONLY);

	mlx4_cleanup_शेष_counters(dev);
	अगर (!mlx4_is_slave(dev))
		mlx4_cleanup_counters_table(dev);
	mlx4_cleanup_qp_table(dev);
	mlx4_cleanup_srq_table(dev);
	mlx4_cleanup_cq_table(dev);
	mlx4_cmd_use_polling(dev);
	mlx4_cleanup_eq_table(dev);
	mlx4_cleanup_mcg_table(dev);
	mlx4_cleanup_mr_table(dev);
	mlx4_cleanup_xrcd_table(dev);
	mlx4_cleanup_pd_table(dev);

	अगर (mlx4_is_master(dev))
		mlx4_मुक्त_resource_tracker(dev,
					   RES_TR_FREE_STRUCTS_ONLY);

	iounmap(priv->kar);
	mlx4_uar_मुक्त(dev, &priv->driver_uar);
	mlx4_cleanup_uar_table(dev);
	अगर (!mlx4_is_slave(dev))
		mlx4_clear_steering(dev);
	mlx4_मुक्त_eq_table(dev);
	अगर (mlx4_is_master(dev))
		mlx4_multi_func_cleanup(dev);
	mlx4_बंद_hca(dev);
	mlx4_बंद_fw(dev);
	अगर (mlx4_is_slave(dev))
		mlx4_multi_func_cleanup(dev);
	mlx4_cmd_cleanup(dev, MLX4_CMD_CLEANUP_ALL);

	अगर (dev->flags & MLX4_FLAG_MSI_X)
		pci_disable_msix(pdev);

	अगर (!mlx4_is_slave(dev))
		mlx4_मुक्त_ownership(dev);

	mlx4_slave_destroy_special_qp_cap(dev);
	kमुक्त(dev->dev_vfs);

	mlx4_clean_dev(dev);
	priv->pci_dev_data = pci_dev_data;
	priv->हटाओd = 1;
पूर्ण

अटल व्योम mlx4_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx4_dev_persistent *persist = pci_get_drvdata(pdev);
	काष्ठा mlx4_dev  *dev  = persist->dev;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा devlink *devlink = priv_to_devlink(priv);
	पूर्णांक active_vfs = 0;

	devlink_reload_disable(devlink);

	अगर (mlx4_is_slave(dev))
		persist->पूर्णांकerface_state |= MLX4_INTERFACE_STATE_NOWAIT;

	mutex_lock(&persist->पूर्णांकerface_state_mutex);
	persist->पूर्णांकerface_state |= MLX4_INTERFACE_STATE_DELETION;
	mutex_unlock(&persist->पूर्णांकerface_state_mutex);

	/* Disabling SR-IOV is not allowed जबतक there are active vf's */
	अगर (mlx4_is_master(dev) && dev->flags & MLX4_FLAG_SRIOV) अणु
		active_vfs = mlx4_how_many_lives_vf(dev);
		अगर (active_vfs) अणु
			pr_warn("Removing PF when there are active VF's !!\n");
			pr_warn("Will not disable SR-IOV.\n");
		पूर्ण
	पूर्ण

	/* device marked to be under deletion running now without the lock
	 * letting other tasks to be terminated
	 */
	अगर (persist->पूर्णांकerface_state & MLX4_INTERFACE_STATE_UP)
		mlx4_unload_one(pdev);
	अन्यथा
		mlx4_info(dev, "%s: interface is down\n", __func__);
	mlx4_catas_end(dev);
	mlx4_crdump_end(dev);
	अगर (dev->flags & MLX4_FLAG_SRIOV && !active_vfs) अणु
		mlx4_warn(dev, "Disabling SR-IOV\n");
		pci_disable_sriov(pdev);
	पूर्ण

	pci_release_regions(pdev);
	mlx4_pci_disable_device(dev);
	devlink_params_unरेजिस्टर(devlink, mlx4_devlink_params,
				  ARRAY_SIZE(mlx4_devlink_params));
	devlink_unरेजिस्टर(devlink);
	kमुक्त(dev->persist);
	devlink_मुक्त(devlink);
पूर्ण

अटल पूर्णांक restore_current_port_types(काष्ठा mlx4_dev *dev,
				      क्रमागत mlx4_port_type *types,
				      क्रमागत mlx4_port_type *poss_types)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक err, i;

	mlx4_stop_sense(dev);

	mutex_lock(&priv->port_mutex);
	क्रम (i = 0; i < dev->caps.num_ports; i++)
		dev->caps.possible_type[i + 1] = poss_types[i];
	err = mlx4_change_port_types(dev, types);
	mlx4_start_sense(dev);
	mutex_unlock(&priv->port_mutex);

	वापस err;
पूर्ण

अटल व्योम mlx4_restart_one_करोwn(काष्ठा pci_dev *pdev)
अणु
	mlx4_unload_one(pdev);
पूर्ण

अटल पूर्णांक mlx4_restart_one_up(काष्ठा pci_dev *pdev, bool reload,
			       काष्ठा devlink *devlink)
अणु
	काष्ठा mlx4_dev_persistent *persist = pci_get_drvdata(pdev);
	काष्ठा mlx4_dev	 *dev  = persist->dev;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक nvfs[MLX4_MAX_PORTS + 1] = अणु0, 0, 0पूर्ण;
	पूर्णांक pci_dev_data, err, total_vfs;

	pci_dev_data = priv->pci_dev_data;
	total_vfs = dev->persist->num_vfs;
	स_नकल(nvfs, dev->persist->nvfs, माप(dev->persist->nvfs));

	अगर (reload)
		mlx4_devlink_param_load_driverinit_values(devlink);
	err = mlx4_load_one(pdev, pci_dev_data, total_vfs, nvfs, priv, 1);
	अगर (err) अणु
		mlx4_err(dev, "%s: ERROR: mlx4_load_one failed, pci_name=%s, err=%d\n",
			 __func__, pci_name(pdev), err);
		वापस err;
	पूर्ण

	err = restore_current_port_types(dev, dev->persist->curr_port_type,
					 dev->persist->curr_port_poss_type);
	अगर (err)
		mlx4_err(dev, "could not restore original port types (%d)\n",
			 err);

	वापस err;
पूर्ण

पूर्णांक mlx4_restart_one(काष्ठा pci_dev *pdev)
अणु
	mlx4_restart_one_करोwn(pdev);
	वापस mlx4_restart_one_up(pdev, false, शून्य);
पूर्ण

#घोषणा MLX_SP(id) अणु PCI_VDEVICE(MELLANOX, id), MLX4_PCI_DEV_FORCE_SENSE_PORT पूर्ण
#घोषणा MLX_VF(id) अणु PCI_VDEVICE(MELLANOX, id), MLX4_PCI_DEV_IS_VF पूर्ण
#घोषणा MLX_GN(id) अणु PCI_VDEVICE(MELLANOX, id), 0 पूर्ण

अटल स्थिर काष्ठा pci_device_id mlx4_pci_table[] = अणु
#अगर_घोषित CONFIG_MLX4_CORE_GEN2
	/* MT25408 "Hermon" */
	MLX_SP(PCI_DEVICE_ID_MELLANOX_HERMON_SDR),	/* SDR */
	MLX_SP(PCI_DEVICE_ID_MELLANOX_HERMON_DDR),	/* DDR */
	MLX_SP(PCI_DEVICE_ID_MELLANOX_HERMON_QDR),	/* QDR */
	MLX_SP(PCI_DEVICE_ID_MELLANOX_HERMON_DDR_GEN2), /* DDR Gen2 */
	MLX_SP(PCI_DEVICE_ID_MELLANOX_HERMON_QDR_GEN2),	/* QDR Gen2 */
	MLX_SP(PCI_DEVICE_ID_MELLANOX_HERMON_EN),	/* EN 10GigE */
	MLX_SP(PCI_DEVICE_ID_MELLANOX_HERMON_EN_GEN2),  /* EN 10GigE Gen2 */
	/* MT25458 ConnectX EN 10GBASE-T */
	MLX_SP(PCI_DEVICE_ID_MELLANOX_CONNECTX_EN),
	MLX_SP(PCI_DEVICE_ID_MELLANOX_CONNECTX_EN_T_GEN2),	/* Gen2 */
	/* MT26468 ConnectX EN 10GigE PCIe Gen2*/
	MLX_SP(PCI_DEVICE_ID_MELLANOX_CONNECTX_EN_GEN2),
	/* MT26438 ConnectX EN 40GigE PCIe Gen2 5GT/s */
	MLX_SP(PCI_DEVICE_ID_MELLANOX_CONNECTX_EN_5_GEN2),
	/* MT26478 ConnectX2 40GigE PCIe Gen2 */
	MLX_SP(PCI_DEVICE_ID_MELLANOX_CONNECTX2),
	/* MT25400 Family [ConnectX-2] */
	MLX_VF(0x1002),					/* Virtual Function */
#पूर्ण_अगर /* CONFIG_MLX4_CORE_GEN2 */
	/* MT27500 Family [ConnectX-3] */
	MLX_GN(PCI_DEVICE_ID_MELLANOX_CONNECTX3),
	MLX_VF(0x1004),					/* Virtual Function */
	MLX_GN(0x1005),					/* MT27510 Family */
	MLX_GN(0x1006),					/* MT27511 Family */
	MLX_GN(PCI_DEVICE_ID_MELLANOX_CONNECTX3_PRO),	/* MT27520 Family */
	MLX_GN(0x1008),					/* MT27521 Family */
	MLX_GN(0x1009),					/* MT27530 Family */
	MLX_GN(0x100a),					/* MT27531 Family */
	MLX_GN(0x100b),					/* MT27540 Family */
	MLX_GN(0x100c),					/* MT27541 Family */
	MLX_GN(0x100d),					/* MT27550 Family */
	MLX_GN(0x100e),					/* MT27551 Family */
	MLX_GN(0x100f),					/* MT27560 Family */
	MLX_GN(0x1010),					/* MT27561 Family */

	/*
	 * See the mellanox_check_broken_पूर्णांकx_masking() quirk when
	 * adding devices
	 */

	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, mlx4_pci_table);

अटल pci_ers_result_t mlx4_pci_err_detected(काष्ठा pci_dev *pdev,
					      pci_channel_state_t state)
अणु
	काष्ठा mlx4_dev_persistent *persist = pci_get_drvdata(pdev);

	mlx4_err(persist->dev, "mlx4_pci_err_detected was called\n");
	mlx4_enter_error_state(persist);

	mutex_lock(&persist->पूर्णांकerface_state_mutex);
	अगर (persist->पूर्णांकerface_state & MLX4_INTERFACE_STATE_UP)
		mlx4_unload_one(pdev);

	mutex_unlock(&persist->पूर्णांकerface_state_mutex);
	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	mlx4_pci_disable_device(persist->dev);
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t mlx4_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx4_dev_persistent *persist = pci_get_drvdata(pdev);
	काष्ठा mlx4_dev	 *dev  = persist->dev;
	पूर्णांक err;

	mlx4_err(dev, "mlx4_pci_slot_reset was called\n");
	err = mlx4_pci_enable_device(dev);
	अगर (err) अणु
		mlx4_err(dev, "Can not re-enable device, err=%d\n", err);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	pci_set_master(pdev);
	pci_restore_state(pdev);
	pci_save_state(pdev);
	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम mlx4_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx4_dev_persistent *persist = pci_get_drvdata(pdev);
	काष्ठा mlx4_dev	 *dev  = persist->dev;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक nvfs[MLX4_MAX_PORTS + 1] = अणु0, 0, 0पूर्ण;
	पूर्णांक total_vfs;
	पूर्णांक err;

	mlx4_err(dev, "%s was called\n", __func__);
	total_vfs = dev->persist->num_vfs;
	स_नकल(nvfs, dev->persist->nvfs, माप(dev->persist->nvfs));

	mutex_lock(&persist->पूर्णांकerface_state_mutex);
	अगर (!(persist->पूर्णांकerface_state & MLX4_INTERFACE_STATE_UP)) अणु
		err = mlx4_load_one(pdev, priv->pci_dev_data, total_vfs, nvfs,
				    priv, 1);
		अगर (err) अणु
			mlx4_err(dev, "%s: mlx4_load_one failed, err=%d\n",
				 __func__,  err);
			जाओ end;
		पूर्ण

		err = restore_current_port_types(dev, dev->persist->
						 curr_port_type, dev->persist->
						 curr_port_poss_type);
		अगर (err)
			mlx4_err(dev, "could not restore original port types (%d)\n", err);
	पूर्ण
end:
	mutex_unlock(&persist->पूर्णांकerface_state_mutex);

पूर्ण

अटल व्योम mlx4_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx4_dev_persistent *persist = pci_get_drvdata(pdev);
	काष्ठा mlx4_dev *dev = persist->dev;

	mlx4_info(persist->dev, "mlx4_shutdown was called\n");
	mutex_lock(&persist->पूर्णांकerface_state_mutex);
	अगर (persist->पूर्णांकerface_state & MLX4_INTERFACE_STATE_UP)
		mlx4_unload_one(pdev);
	mutex_unlock(&persist->पूर्णांकerface_state_mutex);
	mlx4_pci_disable_device(dev);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers mlx4_err_handler = अणु
	.error_detected = mlx4_pci_err_detected,
	.slot_reset     = mlx4_pci_slot_reset,
	.resume		= mlx4_pci_resume,
पूर्ण;

अटल पूर्णांक __maybe_unused mlx4_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा mlx4_dev_persistent *persist = pci_get_drvdata(pdev);
	काष्ठा mlx4_dev	*dev = persist->dev;

	mlx4_err(dev, "suspend was called\n");
	mutex_lock(&persist->पूर्णांकerface_state_mutex);
	अगर (persist->पूर्णांकerface_state & MLX4_INTERFACE_STATE_UP)
		mlx4_unload_one(pdev);
	mutex_unlock(&persist->पूर्णांकerface_state_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mlx4_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा mlx4_dev_persistent *persist = pci_get_drvdata(pdev);
	काष्ठा mlx4_dev	*dev = persist->dev;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक nvfs[MLX4_MAX_PORTS + 1] = अणु0, 0, 0पूर्ण;
	पूर्णांक total_vfs;
	पूर्णांक ret = 0;

	mlx4_err(dev, "resume was called\n");
	total_vfs = dev->persist->num_vfs;
	स_नकल(nvfs, dev->persist->nvfs, माप(dev->persist->nvfs));

	mutex_lock(&persist->पूर्णांकerface_state_mutex);
	अगर (!(persist->पूर्णांकerface_state & MLX4_INTERFACE_STATE_UP)) अणु
		ret = mlx4_load_one(pdev, priv->pci_dev_data, total_vfs,
				    nvfs, priv, 1);
		अगर (!ret) अणु
			ret = restore_current_port_types(dev,
					dev->persist->curr_port_type,
					dev->persist->curr_port_poss_type);
			अगर (ret)
				mlx4_err(dev, "resume: could not restore original port types (%d)\n", ret);
		पूर्ण
	पूर्ण
	mutex_unlock(&persist->पूर्णांकerface_state_mutex);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mlx4_pm_ops, mlx4_suspend, mlx4_resume);

अटल काष्ठा pci_driver mlx4_driver = अणु
	.name		= DRV_NAME,
	.id_table	= mlx4_pci_table,
	.probe		= mlx4_init_one,
	.shutकरोwn	= mlx4_shutकरोwn,
	.हटाओ		= mlx4_हटाओ_one,
	.driver.pm	= &mlx4_pm_ops,
	.err_handler    = &mlx4_err_handler,
पूर्ण;

अटल पूर्णांक __init mlx4_verअगरy_params(व्योम)
अणु
	अगर (msi_x < 0) अणु
		pr_warn("mlx4_core: bad msi_x: %d\n", msi_x);
		वापस -1;
	पूर्ण

	अगर ((log_num_mac < 0) || (log_num_mac > 7)) अणु
		pr_warn("mlx4_core: bad num_mac: %d\n", log_num_mac);
		वापस -1;
	पूर्ण

	अगर (log_num_vlan != 0)
		pr_warn("mlx4_core: log_num_vlan - obsolete module param, using %d\n",
			MLX4_LOG_NUM_VLANS);

	अगर (use_prio != 0)
		pr_warn("mlx4_core: use_prio - obsolete module param, ignored\n");

	अगर ((log_mtts_per_seg < 0) || (log_mtts_per_seg > 7)) अणु
		pr_warn("mlx4_core: bad log_mtts_per_seg: %d\n",
			log_mtts_per_seg);
		वापस -1;
	पूर्ण

	/* Check अगर module param क्रम ports type has legal combination */
	अगर (port_type_array[0] == false && port_type_array[1] == true) अणु
		pr_warn("Module parameter configuration ETH/IB is not supported. Switching to default configuration IB/IB\n");
		port_type_array[0] = true;
	पूर्ण

	अगर (mlx4_log_num_mgm_entry_size < -7 ||
	    (mlx4_log_num_mgm_entry_size > 0 &&
	     (mlx4_log_num_mgm_entry_size < MLX4_MIN_MGM_LOG_ENTRY_SIZE ||
	      mlx4_log_num_mgm_entry_size > MLX4_MAX_MGM_LOG_ENTRY_SIZE))) अणु
		pr_warn("mlx4_core: mlx4_log_num_mgm_entry_size (%d) not in legal range (-7..0 or %d..%d)\n",
			mlx4_log_num_mgm_entry_size,
			MLX4_MIN_MGM_LOG_ENTRY_SIZE,
			MLX4_MAX_MGM_LOG_ENTRY_SIZE);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init mlx4_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (mlx4_verअगरy_params())
		वापस -EINVAL;


	mlx4_wq = create_singlethपढ़ो_workqueue("mlx4");
	अगर (!mlx4_wq)
		वापस -ENOMEM;

	ret = pci_रेजिस्टर_driver(&mlx4_driver);
	अगर (ret < 0)
		destroy_workqueue(mlx4_wq);
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम __निकास mlx4_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&mlx4_driver);
	destroy_workqueue(mlx4_wq);
पूर्ण

module_init(mlx4_init);
module_निकास(mlx4_cleanup);
