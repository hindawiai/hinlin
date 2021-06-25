<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
#समावेश "qlge.h"
#समावेश "qlge_devlink.h"

अटल पूर्णांक qlge_fill_seg_(काष्ठा devlink_fmsg *fmsg,
			  काष्ठा mpi_coredump_segment_header *seg_header,
			  u32 *reg_data)
अणु
	पूर्णांक regs_num = (seg_header->seg_size
			- माप(काष्ठा mpi_coredump_segment_header)) / माप(u32);
	पूर्णांक err;
	पूर्णांक i;

	err = devlink_fmsg_pair_nest_start(fmsg, seg_header->description);
	अगर (err)
		वापस err;
	err = devlink_fmsg_obj_nest_start(fmsg);
	अगर (err)
		वापस err;
	err = devlink_fmsg_u32_pair_put(fmsg, "segment", seg_header->seg_num);
	अगर (err)
		वापस err;
	err = devlink_fmsg_arr_pair_nest_start(fmsg, "values");
	अगर (err)
		वापस err;
	क्रम (i = 0; i < regs_num; i++) अणु
		err = devlink_fmsg_u32_put(fmsg, *reg_data);
		अगर (err)
			वापस err;
		reg_data++;
	पूर्ण
	err = devlink_fmsg_obj_nest_end(fmsg);
	अगर (err)
		वापस err;
	err = devlink_fmsg_arr_pair_nest_end(fmsg);
	अगर (err)
		वापस err;
	err = devlink_fmsg_pair_nest_end(fmsg);
	वापस err;
पूर्ण

#घोषणा FILL_SEG(seg_hdr, seg_regs)			                    \
	करो अणु                                                                \
		err = qlge_fill_seg_(fmsg, &dump->seg_hdr, dump->seg_regs); \
		अगर (err) अणु					            \
			kvमुक्त(dump);                                       \
			वापस err;				            \
		पूर्ण                                                           \
	पूर्ण जबतक (0)

अटल पूर्णांक qlge_reporter_coredump(काष्ठा devlink_health_reporter *reporter,
				  काष्ठा devlink_fmsg *fmsg, व्योम *priv_ctx,
				  काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err = 0;

	काष्ठा qlge_adapter *qdev = devlink_health_reporter_priv(reporter);
	काष्ठा qlge_mpi_coredump *dump;
	रुको_queue_head_t रुको;

	अगर (!netअगर_running(qdev->ndev))
		वापस 0;

	अगर (test_bit(QL_FRC_COREDUMP, &qdev->flags)) अणु
		अगर (qlge_own_firmware(qdev)) अणु
			qlge_queue_fw_error(qdev);
			init_रुकोqueue_head(&रुको);
			रुको_event_समयout(रुको, 0, 5 * HZ);
		पूर्ण अन्यथा अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Force Coredump failed because this NIC function doesn't own the firmware\n");
			वापस -EPERM;
		पूर्ण
	पूर्ण

	dump = kvदो_स्मृति(माप(*dump), GFP_KERNEL);
	अगर (!dump)
		वापस -ENOMEM;

	err = qlge_core_dump(qdev, dump);
	अगर (err) अणु
		kvमुक्त(dump);
		वापस err;
	पूर्ण

	qlge_soft_reset_mpi_risc(qdev);

	FILL_SEG(core_regs_seg_hdr, mpi_core_regs);
	FILL_SEG(test_logic_regs_seg_hdr, test_logic_regs);
	FILL_SEG(rmii_regs_seg_hdr, rmii_regs);
	FILL_SEG(fcmac1_regs_seg_hdr, fcmac1_regs);
	FILL_SEG(fcmac2_regs_seg_hdr, fcmac2_regs);
	FILL_SEG(fc1_mbx_regs_seg_hdr, fc1_mbx_regs);
	FILL_SEG(ide_regs_seg_hdr, ide_regs);
	FILL_SEG(nic1_mbx_regs_seg_hdr, nic1_mbx_regs);
	FILL_SEG(smbus_regs_seg_hdr, smbus_regs);
	FILL_SEG(fc2_mbx_regs_seg_hdr, fc2_mbx_regs);
	FILL_SEG(nic2_mbx_regs_seg_hdr, nic2_mbx_regs);
	FILL_SEG(i2c_regs_seg_hdr, i2c_regs);
	FILL_SEG(memc_regs_seg_hdr, memc_regs);
	FILL_SEG(pbus_regs_seg_hdr, pbus_regs);
	FILL_SEG(mde_regs_seg_hdr, mde_regs);
	FILL_SEG(nic_regs_seg_hdr, nic_regs);
	FILL_SEG(nic2_regs_seg_hdr, nic2_regs);
	FILL_SEG(xgmac1_seg_hdr, xgmac1);
	FILL_SEG(xgmac2_seg_hdr, xgmac2);
	FILL_SEG(code_ram_seg_hdr, code_ram);
	FILL_SEG(memc_ram_seg_hdr, memc_ram);
	FILL_SEG(xaui_an_hdr, serdes_xaui_an);
	FILL_SEG(xaui_hss_pcs_hdr, serdes_xaui_hss_pcs);
	FILL_SEG(xfi_an_hdr, serdes_xfi_an);
	FILL_SEG(xfi_train_hdr, serdes_xfi_train);
	FILL_SEG(xfi_hss_pcs_hdr, serdes_xfi_hss_pcs);
	FILL_SEG(xfi_hss_tx_hdr, serdes_xfi_hss_tx);
	FILL_SEG(xfi_hss_rx_hdr, serdes_xfi_hss_rx);
	FILL_SEG(xfi_hss_pll_hdr, serdes_xfi_hss_pll);

	err = qlge_fill_seg_(fmsg, &dump->misc_nic_seg_hdr,
			     (u32 *)&dump->misc_nic_info);
	अगर (err) अणु
		kvमुक्त(dump);
		वापस err;
	पूर्ण

	FILL_SEG(पूर्णांकr_states_seg_hdr, पूर्णांकr_states);
	FILL_SEG(cam_entries_seg_hdr, cam_entries);
	FILL_SEG(nic_routing_words_seg_hdr, nic_routing_words);
	FILL_SEG(ets_seg_hdr, ets);
	FILL_SEG(probe_dump_seg_hdr, probe_dump);
	FILL_SEG(routing_reg_seg_hdr, routing_regs);
	FILL_SEG(mac_prot_reg_seg_hdr, mac_prot_regs);
	FILL_SEG(xaui2_an_hdr, serdes2_xaui_an);
	FILL_SEG(xaui2_hss_pcs_hdr, serdes2_xaui_hss_pcs);
	FILL_SEG(xfi2_an_hdr, serdes2_xfi_an);
	FILL_SEG(xfi2_train_hdr, serdes2_xfi_train);
	FILL_SEG(xfi2_hss_pcs_hdr, serdes2_xfi_hss_pcs);
	FILL_SEG(xfi2_hss_tx_hdr, serdes2_xfi_hss_tx);
	FILL_SEG(xfi2_hss_rx_hdr, serdes2_xfi_hss_rx);
	FILL_SEG(xfi2_hss_pll_hdr, serdes2_xfi_hss_pll);
	FILL_SEG(sem_regs_seg_hdr, sem_regs);

	kvमुक्त(dump);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा devlink_health_reporter_ops qlge_reporter_ops = अणु
	.name = "coredump",
	.dump = qlge_reporter_coredump,
पूर्ण;

दीर्घ qlge_health_create_reporters(काष्ठा qlge_adapter *priv)
अणु
	काष्ठा devlink *devlink;
	दीर्घ err = 0;

	devlink = priv_to_devlink(priv);
	priv->reporter =
		devlink_health_reporter_create(devlink, &qlge_reporter_ops,
					       0, priv);
	अगर (IS_ERR(priv->reporter)) अणु
		err = PTR_ERR(priv->reporter);
		netdev_warn(priv->ndev,
			    "Failed to create reporter, err = %ld\n",
			    err);
	पूर्ण
	वापस err;
पूर्ण
