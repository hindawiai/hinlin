<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Register bitfield descriptions क्रम Pondicherry2 memory controller.
 *
 * Copyright (c) 2016, Intel Corporation.
 */

#अगर_अघोषित _PND2_REGS_H
#घोषणा _PND2_REGS_H

काष्ठा b_cr_touud_lo_pci अणु
	u32	lock : 1;
	u32	reserved_1 : 19;
	u32	touud : 12;
पूर्ण;

#घोषणा b_cr_touud_lo_pci_port 0x4c
#घोषणा b_cr_touud_lo_pci_offset 0xa8
#घोषणा b_cr_touud_lo_pci_r_opcode 0x04

काष्ठा b_cr_touud_hi_pci अणु
	u32	touud : 7;
	u32	reserved_0 : 25;
पूर्ण;

#घोषणा b_cr_touud_hi_pci_port 0x4c
#घोषणा b_cr_touud_hi_pci_offset 0xac
#घोषणा b_cr_touud_hi_pci_r_opcode 0x04

काष्ठा b_cr_tolud_pci अणु
	u32	lock : 1;
	u32	reserved_0 : 19;
	u32	tolud : 12;
पूर्ण;

#घोषणा b_cr_tolud_pci_port 0x4c
#घोषणा b_cr_tolud_pci_offset 0xbc
#घोषणा b_cr_tolud_pci_r_opcode 0x04

काष्ठा b_cr_mchbar_lo_pci अणु
	u32 enable : 1;
	u32 pad_3_1 : 3;
	u32 pad_14_4: 11;
	u32 base: 17;
पूर्ण;

काष्ठा b_cr_mchbar_hi_pci अणु
	u32 base : 7;
	u32 pad_31_7 : 25;
पूर्ण;

/* Symmetric region */
काष्ठा b_cr_slice_channel_hash अणु
	u64	slice_1_disabled : 1;
	u64	hvm_mode : 1;
	u64	पूर्णांकerleave_mode : 2;
	u64	slice_0_mem_disabled : 1;
	u64	reserved_0 : 1;
	u64	slice_hash_mask : 14;
	u64	reserved_1 : 11;
	u64	enable_pmi_dual_data_mode : 1;
	u64	ch_1_disabled : 1;
	u64	reserved_2 : 1;
	u64	sym_slice0_channel_enabled : 2;
	u64	sym_slice1_channel_enabled : 2;
	u64	ch_hash_mask : 14;
	u64	reserved_3 : 11;
	u64	lock : 1;
पूर्ण;

#घोषणा b_cr_slice_channel_hash_port 0x4c
#घोषणा b_cr_slice_channel_hash_offset 0x4c58
#घोषणा b_cr_slice_channel_hash_r_opcode 0x06

काष्ठा b_cr_mot_out_base_mchbar अणु
	u32	reserved_0 : 14;
	u32	mot_out_base : 15;
	u32	reserved_1 : 1;
	u32	tr_en : 1;
	u32	imr_en : 1;
पूर्ण;

#घोषणा b_cr_mot_out_base_mchbar_port 0x4c
#घोषणा b_cr_mot_out_base_mchbar_offset 0x6af0
#घोषणा b_cr_mot_out_base_mchbar_r_opcode 0x00

काष्ठा b_cr_mot_out_mask_mchbar अणु
	u32	reserved_0 : 14;
	u32	mot_out_mask : 15;
	u32	reserved_1 : 1;
	u32	ia_iwb_en : 1;
	u32	gt_iwb_en : 1;
पूर्ण;

#घोषणा b_cr_mot_out_mask_mchbar_port 0x4c
#घोषणा b_cr_mot_out_mask_mchbar_offset 0x6af4
#घोषणा b_cr_mot_out_mask_mchbar_r_opcode 0x00

काष्ठा b_cr_asym_mem_region0_mchbar अणु
	u32	pad : 4;
	u32	slice0_asym_base : 11;
	u32	pad_18_15 : 4;
	u32	slice0_asym_limit : 11;
	u32	slice0_asym_channel_select : 1;
	u32	slice0_asym_enable : 1;
पूर्ण;

#घोषणा b_cr_asym_mem_region0_mchbar_port 0x4c
#घोषणा b_cr_asym_mem_region0_mchbar_offset 0x6e40
#घोषणा b_cr_asym_mem_region0_mchbar_r_opcode 0x00

काष्ठा b_cr_asym_mem_region1_mchbar अणु
	u32	pad : 4;
	u32	slice1_asym_base : 11;
	u32	pad_18_15 : 4;
	u32	slice1_asym_limit : 11;
	u32	slice1_asym_channel_select : 1;
	u32	slice1_asym_enable : 1;
पूर्ण;

#घोषणा b_cr_asym_mem_region1_mchbar_port 0x4c
#घोषणा b_cr_asym_mem_region1_mchbar_offset 0x6e44
#घोषणा b_cr_asym_mem_region1_mchbar_r_opcode 0x00

/* Some bit fields moved in above two काष्ठाs on Denverton */
काष्ठा b_cr_asym_mem_region_denverton अणु
	u32	pad : 4;
	u32	slice_asym_base : 8;
	u32	pad_19_12 : 8;
	u32	slice_asym_limit : 8;
	u32	pad_28_30 : 3;
	u32	slice_asym_enable : 1;
पूर्ण;

काष्ठा b_cr_asym_2way_mem_region_mchbar अणु
	u32	pad : 2;
	u32	asym_2way_पूर्णांकlv_mode : 2;
	u32	asym_2way_base : 11;
	u32	pad_16_15 : 2;
	u32	asym_2way_limit : 11;
	u32	pad_30_28 : 3;
	u32	asym_2way_पूर्णांकerleave_enable : 1;
पूर्ण;

#घोषणा b_cr_asym_2way_mem_region_mchbar_port 0x4c
#घोषणा b_cr_asym_2way_mem_region_mchbar_offset 0x6e50
#घोषणा b_cr_asym_2way_mem_region_mchbar_r_opcode 0x00

/* Apollo Lake d-unit */

काष्ठा d_cr_drp0 अणु
	u32	rken0 : 1;
	u32	rken1 : 1;
	u32	ddmen : 1;
	u32	rsvd3 : 1;
	u32	dwid : 2;
	u32	dden : 3;
	u32	rsvd13_9 : 5;
	u32	rsien : 1;
	u32	bahen : 1;
	u32	rsvd18_16 : 3;
	u32	caswizzle : 2;
	u32	eccen : 1;
	u32	dramtype : 3;
	u32	blmode : 3;
	u32	addrdec : 2;
	u32	dramdevice_pr : 2;
पूर्ण;

#घोषणा d_cr_drp0_offset 0x1400
#घोषणा d_cr_drp0_r_opcode 0x00

/* Denverton d-unit */

काष्ठा d_cr_dsch अणु
	u32	ch0en : 1;
	u32	ch1en : 1;
	u32	ddr4en : 1;
	u32	coldwake : 1;
	u32	newbypdis : 1;
	u32	chan_width : 1;
	u32	rsvd6_6 : 1;
	u32	ooodis : 1;
	u32	rsvd18_8 : 11;
	u32	ic : 1;
	u32	rsvd31_20 : 12;
पूर्ण;

#घोषणा d_cr_dsch_port 0x16
#घोषणा d_cr_dsch_offset 0x0
#घोषणा d_cr_dsch_r_opcode 0x0

काष्ठा d_cr_ecc_ctrl अणु
	u32	eccen : 1;
	u32	rsvd31_1 : 31;
पूर्ण;

#घोषणा d_cr_ecc_ctrl_offset 0x180
#घोषणा d_cr_ecc_ctrl_r_opcode 0x0

काष्ठा d_cr_drp अणु
	u32	rken0 : 1;
	u32	rken1 : 1;
	u32	rken2 : 1;
	u32	rken3 : 1;
	u32	dimmdwid0 : 2;
	u32	dimmdden0 : 2;
	u32	dimmdwid1 : 2;
	u32	dimmdden1 : 2;
	u32	rsvd15_12 : 4;
	u32	dimmflip : 1;
	u32	rsvd31_17 : 15;
पूर्ण;

#घोषणा d_cr_drp_offset 0x158
#घोषणा d_cr_drp_r_opcode 0x0

काष्ठा d_cr_dmap अणु
	u32	ba0 : 5;
	u32	ba1 : 5;
	u32	bg0 : 5; /* अगर ddr3, ba2 = bg0 */
	u32	bg1 : 5; /* अगर ddr3, ba3 = bg1 */
	u32	rs0 : 5;
	u32	rs1 : 5;
	u32	rsvd : 2;
पूर्ण;

#घोषणा d_cr_dmap_offset 0x174
#घोषणा d_cr_dmap_r_opcode 0x0

काष्ठा d_cr_dmap1 अणु
	u32	ca11 : 6;
	u32	bxor : 1;
	u32	rsvd : 25;
पूर्ण;

#घोषणा d_cr_dmap1_offset 0xb4
#घोषणा d_cr_dmap1_r_opcode 0x0

काष्ठा d_cr_dmap2 अणु
	u32	row0 : 5;
	u32	row1 : 5;
	u32	row2 : 5;
	u32	row3 : 5;
	u32	row4 : 5;
	u32	row5 : 5;
	u32	rsvd : 2;
पूर्ण;

#घोषणा d_cr_dmap2_offset 0x148
#घोषणा d_cr_dmap2_r_opcode 0x0

काष्ठा d_cr_dmap3 अणु
	u32	row6 : 5;
	u32	row7 : 5;
	u32	row8 : 5;
	u32	row9 : 5;
	u32	row10 : 5;
	u32	row11 : 5;
	u32	rsvd : 2;
पूर्ण;

#घोषणा d_cr_dmap3_offset 0x14c
#घोषणा d_cr_dmap3_r_opcode 0x0

काष्ठा d_cr_dmap4 अणु
	u32	row12 : 5;
	u32	row13 : 5;
	u32	row14 : 5;
	u32	row15 : 5;
	u32	row16 : 5;
	u32	row17 : 5;
	u32	rsvd : 2;
पूर्ण;

#घोषणा d_cr_dmap4_offset 0x150
#घोषणा d_cr_dmap4_r_opcode 0x0

काष्ठा d_cr_dmap5 अणु
	u32	ca3 : 4;
	u32	ca4 : 4;
	u32	ca5 : 4;
	u32	ca6 : 4;
	u32	ca7 : 4;
	u32	ca8 : 4;
	u32	ca9 : 4;
	u32	rsvd : 4;
पूर्ण;

#घोषणा d_cr_dmap5_offset 0x154
#घोषणा d_cr_dmap5_r_opcode 0x0

#पूर्ण_अगर /* _PND2_REGS_H */
