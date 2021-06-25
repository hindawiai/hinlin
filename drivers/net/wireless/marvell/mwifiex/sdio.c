<शैली गुरु>
/*
 * NXP Wireless LAN device driver: SDIO specअगरic handling
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश <linux/firmware.h>

#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "wmm.h"
#समावेश "11n.h"
#समावेश "sdio.h"


#घोषणा SDIO_VERSION	"1.0"

अटल व्योम mwअगरiex_sdio_work(काष्ठा work_काष्ठा *work);

अटल काष्ठा mwअगरiex_अगर_ops sdio_ops;

अटल स्थिर काष्ठा mwअगरiex_sdio_card_reg mwअगरiex_reg_sd87xx = अणु
	.start_rd_port = 1,
	.start_wr_port = 1,
	.base_0_reg = 0x0040,
	.base_1_reg = 0x0041,
	.poll_reg = 0x30,
	.host_पूर्णांक_enable = UP_LD_HOST_INT_MASK | DN_LD_HOST_INT_MASK,
	.host_पूर्णांक_rsr_reg = 0x1,
	.host_पूर्णांक_mask_reg = 0x02,
	.host_पूर्णांक_status_reg = 0x03,
	.status_reg_0 = 0x60,
	.status_reg_1 = 0x61,
	.sdio_पूर्णांक_mask = 0x3f,
	.data_port_mask = 0x0000fffe,
	.io_port_0_reg = 0x78,
	.io_port_1_reg = 0x79,
	.io_port_2_reg = 0x7A,
	.max_mp_regs = 64,
	.rd_biपंचांगap_l = 0x04,
	.rd_biपंचांगap_u = 0x05,
	.wr_biपंचांगap_l = 0x06,
	.wr_biपंचांगap_u = 0x07,
	.rd_len_p0_l = 0x08,
	.rd_len_p0_u = 0x09,
	.card_misc_cfg_reg = 0x6c,
	.func1_dump_reg_start = 0x0,
	.func1_dump_reg_end = 0x9,
	.func1_scratch_reg = 0x60,
	.func1_spec_reg_num = 5,
	.func1_spec_reg_table = अणु0x28, 0x30, 0x34, 0x38, 0x3cपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_card_reg mwअगरiex_reg_sd8897 = अणु
	.start_rd_port = 0,
	.start_wr_port = 0,
	.base_0_reg = 0x60,
	.base_1_reg = 0x61,
	.poll_reg = 0x50,
	.host_पूर्णांक_enable = UP_LD_HOST_INT_MASK | DN_LD_HOST_INT_MASK |
			CMD_PORT_UPLD_INT_MASK | CMD_PORT_DNLD_INT_MASK,
	.host_पूर्णांक_rsr_reg = 0x1,
	.host_पूर्णांक_status_reg = 0x03,
	.host_पूर्णांक_mask_reg = 0x02,
	.status_reg_0 = 0xc0,
	.status_reg_1 = 0xc1,
	.sdio_पूर्णांक_mask = 0xff,
	.data_port_mask = 0xffffffff,
	.io_port_0_reg = 0xD8,
	.io_port_1_reg = 0xD9,
	.io_port_2_reg = 0xDA,
	.max_mp_regs = 184,
	.rd_biपंचांगap_l = 0x04,
	.rd_biपंचांगap_u = 0x05,
	.rd_biपंचांगap_1l = 0x06,
	.rd_biपंचांगap_1u = 0x07,
	.wr_biपंचांगap_l = 0x08,
	.wr_biपंचांगap_u = 0x09,
	.wr_biपंचांगap_1l = 0x0a,
	.wr_biपंचांगap_1u = 0x0b,
	.rd_len_p0_l = 0x0c,
	.rd_len_p0_u = 0x0d,
	.card_misc_cfg_reg = 0xcc,
	.card_cfg_2_1_reg = 0xcd,
	.cmd_rd_len_0 = 0xb4,
	.cmd_rd_len_1 = 0xb5,
	.cmd_rd_len_2 = 0xb6,
	.cmd_rd_len_3 = 0xb7,
	.cmd_cfg_0 = 0xb8,
	.cmd_cfg_1 = 0xb9,
	.cmd_cfg_2 = 0xba,
	.cmd_cfg_3 = 0xbb,
	.fw_dump_host_पढ़ोy = 0xee,
	.fw_dump_ctrl = 0xe2,
	.fw_dump_start = 0xe3,
	.fw_dump_end = 0xea,
	.func1_dump_reg_start = 0x0,
	.func1_dump_reg_end = 0xb,
	.func1_scratch_reg = 0xc0,
	.func1_spec_reg_num = 8,
	.func1_spec_reg_table = अणु0x4C, 0x50, 0x54, 0x55, 0x58,
				 0x59, 0x5c, 0x5dपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_card_reg mwअगरiex_reg_sd8977 = अणु
	.start_rd_port = 0,
	.start_wr_port = 0,
	.base_0_reg = 0xF8,
	.base_1_reg = 0xF9,
	.poll_reg = 0x5C,
	.host_पूर्णांक_enable = UP_LD_HOST_INT_MASK | DN_LD_HOST_INT_MASK |
		CMD_PORT_UPLD_INT_MASK | CMD_PORT_DNLD_INT_MASK,
	.host_पूर्णांक_rsr_reg = 0x4,
	.host_पूर्णांक_status_reg = 0x0C,
	.host_पूर्णांक_mask_reg = 0x08,
	.status_reg_0 = 0xE8,
	.status_reg_1 = 0xE9,
	.sdio_पूर्णांक_mask = 0xff,
	.data_port_mask = 0xffffffff,
	.io_port_0_reg = 0xE4,
	.io_port_1_reg = 0xE5,
	.io_port_2_reg = 0xE6,
	.max_mp_regs = 196,
	.rd_biपंचांगap_l = 0x10,
	.rd_biपंचांगap_u = 0x11,
	.rd_biपंचांगap_1l = 0x12,
	.rd_biपंचांगap_1u = 0x13,
	.wr_biपंचांगap_l = 0x14,
	.wr_biपंचांगap_u = 0x15,
	.wr_biपंचांगap_1l = 0x16,
	.wr_biपंचांगap_1u = 0x17,
	.rd_len_p0_l = 0x18,
	.rd_len_p0_u = 0x19,
	.card_misc_cfg_reg = 0xd8,
	.card_cfg_2_1_reg = 0xd9,
	.cmd_rd_len_0 = 0xc0,
	.cmd_rd_len_1 = 0xc1,
	.cmd_rd_len_2 = 0xc2,
	.cmd_rd_len_3 = 0xc3,
	.cmd_cfg_0 = 0xc4,
	.cmd_cfg_1 = 0xc5,
	.cmd_cfg_2 = 0xc6,
	.cmd_cfg_3 = 0xc7,
	.fw_dump_host_पढ़ोy = 0xcc,
	.fw_dump_ctrl = 0xf0,
	.fw_dump_start = 0xf1,
	.fw_dump_end = 0xf8,
	.func1_dump_reg_start = 0x10,
	.func1_dump_reg_end = 0x17,
	.func1_scratch_reg = 0xe8,
	.func1_spec_reg_num = 13,
	.func1_spec_reg_table = अणु0x08, 0x58, 0x5C, 0x5D,
				 0x60, 0x61, 0x62, 0x64,
				 0x65, 0x66, 0x68, 0x69,
				 0x6aपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_card_reg mwअगरiex_reg_sd8997 = अणु
	.start_rd_port = 0,
	.start_wr_port = 0,
	.base_0_reg = 0xF8,
	.base_1_reg = 0xF9,
	.poll_reg = 0x5C,
	.host_पूर्णांक_enable = UP_LD_HOST_INT_MASK | DN_LD_HOST_INT_MASK |
			CMD_PORT_UPLD_INT_MASK | CMD_PORT_DNLD_INT_MASK,
	.host_पूर्णांक_rsr_reg = 0x4,
	.host_पूर्णांक_status_reg = 0x0C,
	.host_पूर्णांक_mask_reg = 0x08,
	.status_reg_0 = 0xE8,
	.status_reg_1 = 0xE9,
	.sdio_पूर्णांक_mask = 0xff,
	.data_port_mask = 0xffffffff,
	.io_port_0_reg = 0xE4,
	.io_port_1_reg = 0xE5,
	.io_port_2_reg = 0xE6,
	.max_mp_regs = 196,
	.rd_biपंचांगap_l = 0x10,
	.rd_biपंचांगap_u = 0x11,
	.rd_biपंचांगap_1l = 0x12,
	.rd_biपंचांगap_1u = 0x13,
	.wr_biपंचांगap_l = 0x14,
	.wr_biपंचांगap_u = 0x15,
	.wr_biपंचांगap_1l = 0x16,
	.wr_biपंचांगap_1u = 0x17,
	.rd_len_p0_l = 0x18,
	.rd_len_p0_u = 0x19,
	.card_misc_cfg_reg = 0xd8,
	.card_cfg_2_1_reg = 0xd9,
	.cmd_rd_len_0 = 0xc0,
	.cmd_rd_len_1 = 0xc1,
	.cmd_rd_len_2 = 0xc2,
	.cmd_rd_len_3 = 0xc3,
	.cmd_cfg_0 = 0xc4,
	.cmd_cfg_1 = 0xc5,
	.cmd_cfg_2 = 0xc6,
	.cmd_cfg_3 = 0xc7,
	.fw_dump_host_पढ़ोy = 0xcc,
	.fw_dump_ctrl = 0xf0,
	.fw_dump_start = 0xf1,
	.fw_dump_end = 0xf8,
	.func1_dump_reg_start = 0x10,
	.func1_dump_reg_end = 0x17,
	.func1_scratch_reg = 0xe8,
	.func1_spec_reg_num = 13,
	.func1_spec_reg_table = अणु0x08, 0x58, 0x5C, 0x5D,
				 0x60, 0x61, 0x62, 0x64,
				 0x65, 0x66, 0x68, 0x69,
				 0x6aपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_card_reg mwअगरiex_reg_sd8887 = अणु
	.start_rd_port = 0,
	.start_wr_port = 0,
	.base_0_reg = 0x6C,
	.base_1_reg = 0x6D,
	.poll_reg = 0x5C,
	.host_पूर्णांक_enable = UP_LD_HOST_INT_MASK | DN_LD_HOST_INT_MASK |
			CMD_PORT_UPLD_INT_MASK | CMD_PORT_DNLD_INT_MASK,
	.host_पूर्णांक_rsr_reg = 0x4,
	.host_पूर्णांक_status_reg = 0x0C,
	.host_पूर्णांक_mask_reg = 0x08,
	.status_reg_0 = 0x90,
	.status_reg_1 = 0x91,
	.sdio_पूर्णांक_mask = 0xff,
	.data_port_mask = 0xffffffff,
	.io_port_0_reg = 0xE4,
	.io_port_1_reg = 0xE5,
	.io_port_2_reg = 0xE6,
	.max_mp_regs = 196,
	.rd_biपंचांगap_l = 0x10,
	.rd_biपंचांगap_u = 0x11,
	.rd_biपंचांगap_1l = 0x12,
	.rd_biपंचांगap_1u = 0x13,
	.wr_biपंचांगap_l = 0x14,
	.wr_biपंचांगap_u = 0x15,
	.wr_biपंचांगap_1l = 0x16,
	.wr_biपंचांगap_1u = 0x17,
	.rd_len_p0_l = 0x18,
	.rd_len_p0_u = 0x19,
	.card_misc_cfg_reg = 0xd8,
	.card_cfg_2_1_reg = 0xd9,
	.cmd_rd_len_0 = 0xc0,
	.cmd_rd_len_1 = 0xc1,
	.cmd_rd_len_2 = 0xc2,
	.cmd_rd_len_3 = 0xc3,
	.cmd_cfg_0 = 0xc4,
	.cmd_cfg_1 = 0xc5,
	.cmd_cfg_2 = 0xc6,
	.cmd_cfg_3 = 0xc7,
	.func1_dump_reg_start = 0x10,
	.func1_dump_reg_end = 0x17,
	.func1_scratch_reg = 0x90,
	.func1_spec_reg_num = 13,
	.func1_spec_reg_table = अणु0x08, 0x58, 0x5C, 0x5D, 0x60,
				 0x61, 0x62, 0x64, 0x65, 0x66,
				 0x68, 0x69, 0x6aपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_card_reg mwअगरiex_reg_sd8987 = अणु
	.start_rd_port = 0,
	.start_wr_port = 0,
	.base_0_reg = 0xF8,
	.base_1_reg = 0xF9,
	.poll_reg = 0x5C,
	.host_पूर्णांक_enable = UP_LD_HOST_INT_MASK | DN_LD_HOST_INT_MASK |
			CMD_PORT_UPLD_INT_MASK | CMD_PORT_DNLD_INT_MASK,
	.host_पूर्णांक_rsr_reg = 0x4,
	.host_पूर्णांक_status_reg = 0x0C,
	.host_पूर्णांक_mask_reg = 0x08,
	.status_reg_0 = 0xE8,
	.status_reg_1 = 0xE9,
	.sdio_पूर्णांक_mask = 0xff,
	.data_port_mask = 0xffffffff,
	.io_port_0_reg = 0xE4,
	.io_port_1_reg = 0xE5,
	.io_port_2_reg = 0xE6,
	.max_mp_regs = 196,
	.rd_biपंचांगap_l = 0x10,
	.rd_biपंचांगap_u = 0x11,
	.rd_biपंचांगap_1l = 0x12,
	.rd_biपंचांगap_1u = 0x13,
	.wr_biपंचांगap_l = 0x14,
	.wr_biपंचांगap_u = 0x15,
	.wr_biपंचांगap_1l = 0x16,
	.wr_biपंचांगap_1u = 0x17,
	.rd_len_p0_l = 0x18,
	.rd_len_p0_u = 0x19,
	.card_misc_cfg_reg = 0xd8,
	.card_cfg_2_1_reg = 0xd9,
	.cmd_rd_len_0 = 0xc0,
	.cmd_rd_len_1 = 0xc1,
	.cmd_rd_len_2 = 0xc2,
	.cmd_rd_len_3 = 0xc3,
	.cmd_cfg_0 = 0xc4,
	.cmd_cfg_1 = 0xc5,
	.cmd_cfg_2 = 0xc6,
	.cmd_cfg_3 = 0xc7,
	.fw_dump_host_पढ़ोy = 0xcc,
	.fw_dump_ctrl = 0xf9,
	.fw_dump_start = 0xf1,
	.fw_dump_end = 0xf8,
	.func1_dump_reg_start = 0x10,
	.func1_dump_reg_end = 0x17,
	.func1_scratch_reg = 0xE8,
	.func1_spec_reg_num = 13,
	.func1_spec_reg_table = अणु0x08, 0x58, 0x5C, 0x5D, 0x60,
				 0x61, 0x62, 0x64, 0x65, 0x66,
				 0x68, 0x69, 0x6aपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_device mwअगरiex_sdio_sd8786 = अणु
	.firmware = SD8786_DEFAULT_FW_NAME,
	.reg = &mwअगरiex_reg_sd87xx,
	.max_ports = 16,
	.mp_agg_pkt_limit = 8,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_16K,
	.mp_rx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_16K,
	.supports_sdio_new_mode = false,
	.has_control_mask = true,
	.can_dump_fw = false,
	.can_स्वतः_tdls = false,
	.can_ext_scan = false,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_device mwअगरiex_sdio_sd8787 = अणु
	.firmware = SD8787_DEFAULT_FW_NAME,
	.reg = &mwअगरiex_reg_sd87xx,
	.max_ports = 16,
	.mp_agg_pkt_limit = 8,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_16K,
	.mp_rx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_16K,
	.supports_sdio_new_mode = false,
	.has_control_mask = true,
	.can_dump_fw = false,
	.can_स्वतः_tdls = false,
	.can_ext_scan = true,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_device mwअगरiex_sdio_sd8797 = अणु
	.firmware = SD8797_DEFAULT_FW_NAME,
	.reg = &mwअगरiex_reg_sd87xx,
	.max_ports = 16,
	.mp_agg_pkt_limit = 8,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_16K,
	.mp_rx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_16K,
	.supports_sdio_new_mode = false,
	.has_control_mask = true,
	.can_dump_fw = false,
	.can_स्वतः_tdls = false,
	.can_ext_scan = true,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_device mwअगरiex_sdio_sd8897 = अणु
	.firmware = SD8897_DEFAULT_FW_NAME,
	.reg = &mwअगरiex_reg_sd8897,
	.max_ports = 32,
	.mp_agg_pkt_limit = 16,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_MAX,
	.mp_rx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_MAX,
	.supports_sdio_new_mode = true,
	.has_control_mask = false,
	.can_dump_fw = true,
	.can_स्वतः_tdls = false,
	.can_ext_scan = true,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_device mwअगरiex_sdio_sd8977 = अणु
	.firmware = SD8977_DEFAULT_FW_NAME,
	.reg = &mwअगरiex_reg_sd8977,
	.max_ports = 32,
	.mp_agg_pkt_limit = 16,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_MAX,
	.mp_rx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_MAX,
	.supports_sdio_new_mode = true,
	.has_control_mask = false,
	.can_dump_fw = true,
	.fw_dump_enh = true,
	.can_स्वतः_tdls = false,
	.can_ext_scan = true,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_device mwअगरiex_sdio_sd8997 = अणु
	.firmware = SD8997_DEFAULT_FW_NAME,
	.reg = &mwअगरiex_reg_sd8997,
	.max_ports = 32,
	.mp_agg_pkt_limit = 16,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_MAX,
	.mp_rx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_MAX,
	.supports_sdio_new_mode = true,
	.has_control_mask = false,
	.can_dump_fw = true,
	.fw_dump_enh = true,
	.can_स्वतः_tdls = false,
	.can_ext_scan = true,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_device mwअगरiex_sdio_sd8887 = अणु
	.firmware = SD8887_DEFAULT_FW_NAME,
	.reg = &mwअगरiex_reg_sd8887,
	.max_ports = 32,
	.mp_agg_pkt_limit = 16,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_32K,
	.mp_rx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_32K,
	.supports_sdio_new_mode = true,
	.has_control_mask = false,
	.can_dump_fw = false,
	.can_स्वतः_tdls = true,
	.can_ext_scan = true,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_device mwअगरiex_sdio_sd8987 = अणु
	.firmware = SD8987_DEFAULT_FW_NAME,
	.reg = &mwअगरiex_reg_sd8987,
	.max_ports = 32,
	.mp_agg_pkt_limit = 16,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_MAX,
	.mp_rx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_MAX,
	.supports_sdio_new_mode = true,
	.has_control_mask = false,
	.can_dump_fw = true,
	.fw_dump_enh = true,
	.can_स्वतः_tdls = true,
	.can_ext_scan = true,
पूर्ण;

अटल स्थिर काष्ठा mwअगरiex_sdio_device mwअगरiex_sdio_sd8801 = अणु
	.firmware = SD8801_DEFAULT_FW_NAME,
	.reg = &mwअगरiex_reg_sd87xx,
	.max_ports = 16,
	.mp_agg_pkt_limit = 8,
	.supports_sdio_new_mode = false,
	.has_control_mask = true,
	.tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K,
	.mp_tx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_16K,
	.mp_rx_agg_buf_size = MWIFIEX_MP_AGGR_BUF_SIZE_16K,
	.can_dump_fw = false,
	.can_स्वतः_tdls = false,
	.can_ext_scan = true,
पूर्ण;

अटल काष्ठा memory_type_mapping generic_mem_type_map[] = अणु
	अणु"DUMP", शून्य, 0, 0xDDपूर्ण,
पूर्ण;

अटल काष्ठा memory_type_mapping mem_type_mapping_tbl[] = अणु
	अणु"ITCM", शून्य, 0, 0xF0पूर्ण,
	अणु"DTCM", शून्य, 0, 0xF1पूर्ण,
	अणु"SQRAM", शून्य, 0, 0xF2पूर्ण,
	अणु"APU", शून्य, 0, 0xF3पूर्ण,
	अणु"CIU", शून्य, 0, 0xF4पूर्ण,
	अणु"ICU", शून्य, 0, 0xF5पूर्ण,
	अणु"MAC", शून्य, 0, 0xF6पूर्ण,
	अणु"EXT7", शून्य, 0, 0xF7पूर्ण,
	अणु"EXT8", शून्य, 0, 0xF8पूर्ण,
	अणु"EXT9", शून्य, 0, 0xF9पूर्ण,
	अणु"EXT10", शून्य, 0, 0xFAपूर्ण,
	अणु"EXT11", शून्य, 0, 0xFBपूर्ण,
	अणु"EXT12", शून्य, 0, 0xFCपूर्ण,
	अणु"EXT13", शून्य, 0, 0xFDपूर्ण,
	अणु"EXTLAST", शून्य, 0, 0xFEपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mwअगरiex_sdio_of_match_table[] = अणु
	अणु .compatible = "marvell,sd8897" पूर्ण,
	अणु .compatible = "marvell,sd8997" पूर्ण,
	अणु पूर्ण
पूर्ण;

/* This function parse device tree node using mmc subnode devicetree API.
 * The device node is saved in card->plt_of_node.
 * अगर the device tree node exist and include पूर्णांकerrupts attributes, this
 * function will also request platक्रमm specअगरic wakeup पूर्णांकerrupt.
 */
अटल पूर्णांक mwअगरiex_sdio_probe_of(काष्ठा device *dev)
अणु
	अगर (!of_match_node(mwअगरiex_sdio_of_match_table, dev->of_node)) अणु
		dev_err(dev, "required compatible string missing\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * SDIO probe.
 *
 * This function probes an mwअगरiex device and रेजिस्टरs it. It allocates
 * the card काष्ठाure, enables SDIO function number and initiates the
 * device registration and initialization procedure by adding a logical
 * पूर्णांकerface.
 */
अटल पूर्णांक
mwअगरiex_sdio_probe(काष्ठा sdio_func *func, स्थिर काष्ठा sdio_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा sdio_mmc_card *card = शून्य;

	pr_debug("info: vendor=0x%4.04X device=0x%4.04X class=%d function=%d\n",
		 func->venकरोr, func->device, func->class, func->num);

	card = devm_kzalloc(&func->dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	init_completion(&card->fw_करोne);

	card->func = func;

	func->card->quirks |= MMC_QUIRK_BLKSZ_FOR_BYTE_MODE;

	अगर (id->driver_data) अणु
		काष्ठा mwअगरiex_sdio_device *data = (व्योम *)id->driver_data;

		card->firmware = data->firmware;
		card->reg = data->reg;
		card->max_ports = data->max_ports;
		card->mp_agg_pkt_limit = data->mp_agg_pkt_limit;
		card->supports_sdio_new_mode = data->supports_sdio_new_mode;
		card->has_control_mask = data->has_control_mask;
		card->tx_buf_size = data->tx_buf_size;
		card->mp_tx_agg_buf_size = data->mp_tx_agg_buf_size;
		card->mp_rx_agg_buf_size = data->mp_rx_agg_buf_size;
		card->can_dump_fw = data->can_dump_fw;
		card->fw_dump_enh = data->fw_dump_enh;
		card->can_स्वतः_tdls = data->can_स्वतः_tdls;
		card->can_ext_scan = data->can_ext_scan;
		INIT_WORK(&card->work, mwअगरiex_sdio_work);
	पूर्ण

	sdio_claim_host(func);
	ret = sdio_enable_func(func);
	sdio_release_host(func);

	अगर (ret) अणु
		dev_err(&func->dev, "failed to enable function\n");
		वापस ret;
	पूर्ण

	/* device tree node parsing and platक्रमm specअगरic configuration*/
	अगर (func->dev.of_node) अणु
		ret = mwअगरiex_sdio_probe_of(&func->dev);
		अगर (ret)
			जाओ err_disable;
	पूर्ण

	ret = mwअगरiex_add_card(card, &card->fw_करोne, &sdio_ops,
			       MWIFIEX_SDIO, &func->dev);
	अगर (ret) अणु
		dev_err(&func->dev, "add card failed\n");
		जाओ err_disable;
	पूर्ण

	वापस 0;

err_disable:
	sdio_claim_host(func);
	sdio_disable_func(func);
	sdio_release_host(func);

	वापस ret;
पूर्ण

/*
 * SDIO resume.
 *
 * Kernel needs to suspend all functions separately. Thereक्रमe all
 * रेजिस्टरed functions must have drivers with suspend and resume
 * methods. Failing that the kernel simply हटाओs the whole card.
 *
 * If alपढ़ोy not resumed, this function turns on the traffic and
 * sends a host sleep cancel request to the firmware.
 */
अटल पूर्णांक mwअगरiex_sdio_resume(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा sdio_mmc_card *card;
	काष्ठा mwअगरiex_adapter *adapter;

	card = sdio_get_drvdata(func);
	अगर (!card || !card->adapter) अणु
		dev_err(dev, "resume: invalid card or adapter\n");
		वापस 0;
	पूर्ण

	adapter = card->adapter;

	अगर (!test_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags)) अणु
		mwअगरiex_dbg(adapter, WARN,
			    "device already resumed\n");
		वापस 0;
	पूर्ण

	clear_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags);

	/* Disable Host Sleep */
	mwअगरiex_cancel_hs(mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA),
			  MWIFIEX_SYNC_CMD);

	mwअगरiex_disable_wake(adapter);

	वापस 0;
पूर्ण

/* Write data पूर्णांकo SDIO card रेजिस्टर. Caller claims SDIO device. */
अटल पूर्णांक
mwअगरiex_ग_लिखो_reg_locked(काष्ठा sdio_func *func, u32 reg, u8 data)
अणु
	पूर्णांक ret = -1;

	sdio_ग_लिखोb(func, data, reg, &ret);
	वापस ret;
पूर्ण

/* This function ग_लिखोs data पूर्णांकo SDIO card रेजिस्टर.
 */
अटल पूर्णांक
mwअगरiex_ग_लिखो_reg(काष्ठा mwअगरiex_adapter *adapter, u32 reg, u8 data)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	पूर्णांक ret;

	sdio_claim_host(card->func);
	ret = mwअगरiex_ग_लिखो_reg_locked(card->func, reg, data);
	sdio_release_host(card->func);

	वापस ret;
पूर्ण

/* This function पढ़ोs data from SDIO card रेजिस्टर.
 */
अटल पूर्णांक
mwअगरiex_पढ़ो_reg(काष्ठा mwअगरiex_adapter *adapter, u32 reg, u8 *data)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	पूर्णांक ret = -1;
	u8 val;

	sdio_claim_host(card->func);
	val = sdio_पढ़ोb(card->func, reg, &ret);
	sdio_release_host(card->func);

	*data = val;

	वापस ret;
पूर्ण

/* This function ग_लिखोs multiple data पूर्णांकo SDIO card memory.
 *
 * This करोes not work in suspended mode.
 */
अटल पूर्णांक
mwअगरiex_ग_लिखो_data_sync(काष्ठा mwअगरiex_adapter *adapter,
			u8 *buffer, u32 pkt_len, u32 port)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	पूर्णांक ret;
	u8 blk_mode =
		(port & MWIFIEX_SDIO_BYTE_MODE_MASK) ? BYTE_MODE : BLOCK_MODE;
	u32 blk_size = (blk_mode == BLOCK_MODE) ? MWIFIEX_SDIO_BLOCK_SIZE : 1;
	u32 blk_cnt =
		(blk_mode ==
		 BLOCK_MODE) ? (pkt_len /
				MWIFIEX_SDIO_BLOCK_SIZE) : pkt_len;
	u32 ioport = (port & MWIFIEX_SDIO_IO_PORT_MASK);

	अगर (test_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: not allowed while suspended\n", __func__);
		वापस -1;
	पूर्ण

	sdio_claim_host(card->func);

	ret = sdio_ग_लिखोsb(card->func, ioport, buffer, blk_cnt * blk_size);

	sdio_release_host(card->func);

	वापस ret;
पूर्ण

/* This function पढ़ोs multiple data from SDIO card memory.
 */
अटल पूर्णांक mwअगरiex_पढ़ो_data_sync(काष्ठा mwअगरiex_adapter *adapter, u8 *buffer,
				  u32 len, u32 port, u8 claim)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	पूर्णांक ret;
	u8 blk_mode = (port & MWIFIEX_SDIO_BYTE_MODE_MASK) ? BYTE_MODE
		       : BLOCK_MODE;
	u32 blk_size = (blk_mode == BLOCK_MODE) ? MWIFIEX_SDIO_BLOCK_SIZE : 1;
	u32 blk_cnt = (blk_mode == BLOCK_MODE) ? (len / MWIFIEX_SDIO_BLOCK_SIZE)
			: len;
	u32 ioport = (port & MWIFIEX_SDIO_IO_PORT_MASK);

	अगर (claim)
		sdio_claim_host(card->func);

	ret = sdio_पढ़ोsb(card->func, buffer, ioport, blk_cnt * blk_size);

	अगर (claim)
		sdio_release_host(card->func);

	वापस ret;
पूर्ण

/* This function पढ़ोs the firmware status.
 */
अटल पूर्णांक
mwअगरiex_sdio_पढ़ो_fw_status(काष्ठा mwअगरiex_adapter *adapter, u16 *dat)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_sdio_card_reg *reg = card->reg;
	u8 fws0, fws1;

	अगर (mwअगरiex_पढ़ो_reg(adapter, reg->status_reg_0, &fws0))
		वापस -1;

	अगर (mwअगरiex_पढ़ो_reg(adapter, reg->status_reg_1, &fws1))
		वापस -1;

	*dat = (u16)((fws1 << 8) | fws0);
	वापस 0;
पूर्ण

/* This function checks the firmware status in card.
 */
अटल पूर्णांक mwअगरiex_check_fw_status(काष्ठा mwअगरiex_adapter *adapter,
				   u32 poll_num)
अणु
	पूर्णांक ret = 0;
	u16 firmware_stat;
	u32 tries;

	क्रम (tries = 0; tries < poll_num; tries++) अणु
		ret = mwअगरiex_sdio_पढ़ो_fw_status(adapter, &firmware_stat);
		अगर (ret)
			जारी;
		अगर (firmware_stat == FIRMWARE_READY_SDIO) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		msleep(100);
		ret = -1;
	पूर्ण

	वापस ret;
पूर्ण

/* This function checks अगर WLAN is the winner.
 */
अटल पूर्णांक mwअगरiex_check_winner_status(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक ret = 0;
	u8 winner = 0;
	काष्ठा sdio_mmc_card *card = adapter->card;

	अगर (mwअगरiex_पढ़ो_reg(adapter, card->reg->status_reg_0, &winner))
		वापस -1;

	अगर (winner)
		adapter->winner = 0;
	अन्यथा
		adapter->winner = 1;

	वापस ret;
पूर्ण

/*
 * SDIO हटाओ.
 *
 * This function हटाओs the पूर्णांकerface and मुक्तs up the card काष्ठाure.
 */
अटल व्योम
mwअगरiex_sdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा sdio_mmc_card *card;
	काष्ठा mwअगरiex_adapter *adapter;
	काष्ठा mwअगरiex_निजी *priv;
	पूर्णांक ret = 0;
	u16 firmware_stat;

	card = sdio_get_drvdata(func);
	अगर (!card)
		वापस;

	रुको_क्रम_completion(&card->fw_करोne);

	adapter = card->adapter;
	अगर (!adapter || !adapter->priv_num)
		वापस;

	mwअगरiex_dbg(adapter, INFO, "info: SDIO func num=%d\n", func->num);

	ret = mwअगरiex_sdio_पढ़ो_fw_status(adapter, &firmware_stat);
	अगर (!ret && firmware_stat == FIRMWARE_READY_SDIO &&
	    !adapter->mfg_mode) अणु
		mwअगरiex_deauthenticate_all(adapter);

		priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);
		mwअगरiex_disable_स्वतः_ds(priv);
		mwअगरiex_init_shutकरोwn_fw(priv, MWIFIEX_FUNC_SHUTDOWN);
	पूर्ण

	mwअगरiex_हटाओ_card(adapter);
पूर्ण

/*
 * SDIO suspend.
 *
 * Kernel needs to suspend all functions separately. Thereक्रमe all
 * रेजिस्टरed functions must have drivers with suspend and resume
 * methods. Failing that the kernel simply हटाओs the whole card.
 *
 * If alपढ़ोy not suspended, this function allocates and sends a host
 * sleep activate request to the firmware and turns off the traffic.
 */
अटल पूर्णांक mwअगरiex_sdio_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा sdio_mmc_card *card;
	काष्ठा mwअगरiex_adapter *adapter;
	mmc_pm_flag_t pm_flag = 0;
	पूर्णांक ret = 0;

	pm_flag = sdio_get_host_pm_caps(func);
	pr_debug("cmd: %s: suspend: PM flag = 0x%x\n",
		 sdio_func_id(func), pm_flag);
	अगर (!(pm_flag & MMC_PM_KEEP_POWER)) अणु
		dev_err(dev, "%s: cannot remain alive while host is"
			" suspended\n", sdio_func_id(func));
		वापस -ENOSYS;
	पूर्ण

	card = sdio_get_drvdata(func);
	अगर (!card) अणु
		dev_err(dev, "suspend: invalid card\n");
		वापस 0;
	पूर्ण

	/* Might still be loading firmware */
	रुको_क्रम_completion(&card->fw_करोne);

	adapter = card->adapter;
	अगर (!adapter) अणु
		dev_err(dev, "adapter is not valid\n");
		वापस 0;
	पूर्ण

	अगर (!adapter->is_up)
		वापस -EBUSY;

	mwअगरiex_enable_wake(adapter);

	/* Enable the Host Sleep */
	अगर (!mwअगरiex_enable_hs(adapter)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "cmd: failed to suspend\n");
		clear_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags);
		mwअगरiex_disable_wake(adapter);
		वापस -EFAULT;
	पूर्ण

	mwअगरiex_dbg(adapter, INFO,
		    "cmd: suspend with MMC_PM_KEEP_POWER\n");
	ret = sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);

	/* Indicate device suspended */
	set_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags);
	clear_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags);

	वापस ret;
पूर्ण

अटल व्योम mwअगरiex_sdio_coredump(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा sdio_mmc_card *card;

	card = sdio_get_drvdata(func);
	अगर (!test_and_set_bit(MWIFIEX_IFACE_WORK_DEVICE_DUMP,
			      &card->work_flags))
		schedule_work(&card->work);
पूर्ण

/* WLAN IDs */
अटल स्थिर काष्ठा sdio_device_id mwअगरiex_ids[] = अणु
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8786_WLAN),
		.driver_data = (अचिन्हित दीर्घ) &mwअगरiex_sdio_sd8786पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8787_WLAN),
		.driver_data = (अचिन्हित दीर्घ) &mwअगरiex_sdio_sd8787पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8797_WLAN),
		.driver_data = (अचिन्हित दीर्घ) &mwअगरiex_sdio_sd8797पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8897_WLAN),
		.driver_data = (अचिन्हित दीर्घ) &mwअगरiex_sdio_sd8897पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8887_WLAN),
		.driver_data = (अचिन्हित दीर्घ)&mwअगरiex_sdio_sd8887पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8801_WLAN),
		.driver_data = (अचिन्हित दीर्घ)&mwअगरiex_sdio_sd8801पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8977_WLAN),
		.driver_data = (अचिन्हित दीर्घ)&mwअगरiex_sdio_sd8977पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8987_WLAN),
		.driver_data = (अचिन्हित दीर्घ)&mwअगरiex_sdio_sd8987पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_MARVELL, SDIO_DEVICE_ID_MARVELL_8997_WLAN),
		.driver_data = (अचिन्हित दीर्घ)&mwअगरiex_sdio_sd8997पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(sdio, mwअगरiex_ids);

अटल स्थिर काष्ठा dev_pm_ops mwअगरiex_sdio_pm_ops = अणु
	.suspend = mwअगरiex_sdio_suspend,
	.resume = mwअगरiex_sdio_resume,
पूर्ण;

अटल काष्ठा sdio_driver mwअगरiex_sdio = अणु
	.name = "mwifiex_sdio",
	.id_table = mwअगरiex_ids,
	.probe = mwअगरiex_sdio_probe,
	.हटाओ = mwअगरiex_sdio_हटाओ,
	.drv = अणु
		.owner = THIS_MODULE,
		.coredump = mwअगरiex_sdio_coredump,
		.pm = &mwअगरiex_sdio_pm_ops,
	पूर्ण
पूर्ण;

/*
 * This function wakes up the card.
 *
 * A host घातer up command is written to the card configuration
 * रेजिस्टर to wake up the card.
 */
अटल पूर्णांक mwअगरiex_pm_wakeup_card(काष्ठा mwअगरiex_adapter *adapter)
अणु
	mwअगरiex_dbg(adapter, EVENT,
		    "event: wakeup device...\n");

	वापस mwअगरiex_ग_लिखो_reg(adapter, CONFIGURATION_REG, HOST_POWER_UP);
पूर्ण

/*
 * This function is called after the card has woken up.
 *
 * The card configuration रेजिस्टर is reset.
 */
अटल पूर्णांक mwअगरiex_pm_wakeup_card_complete(काष्ठा mwअगरiex_adapter *adapter)
अणु
	mwअगरiex_dbg(adapter, EVENT,
		    "cmd: wakeup device completed\n");

	वापस mwअगरiex_ग_लिखो_reg(adapter, CONFIGURATION_REG, 0);
पूर्ण

अटल पूर्णांक mwअगरiex_sdio_dnld_fw(काष्ठा mwअगरiex_adapter *adapter,
			काष्ठा mwअगरiex_fw_image *fw)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	पूर्णांक ret;

	sdio_claim_host(card->func);
	ret = mwअगरiex_dnld_fw(adapter, fw);
	sdio_release_host(card->func);

	वापस ret;
पूर्ण

/*
 * This function is used to initialize IO ports क्रम the
 * chipsets supporting SDIO new mode eg SD8897.
 */
अटल पूर्णांक mwअगरiex_init_sdio_new_mode(काष्ठा mwअगरiex_adapter *adapter)
अणु
	u8 reg;
	काष्ठा sdio_mmc_card *card = adapter->card;

	adapter->ioport = MEM_PORT;

	/* enable sdio new mode */
	अगर (mwअगरiex_पढ़ो_reg(adapter, card->reg->card_cfg_2_1_reg, &reg))
		वापस -1;
	अगर (mwअगरiex_ग_लिखो_reg(adapter, card->reg->card_cfg_2_1_reg,
			      reg | CMD53_NEW_MODE))
		वापस -1;

	/* Configure cmd port and enable पढ़ोing rx length from the रेजिस्टर */
	अगर (mwअगरiex_पढ़ो_reg(adapter, card->reg->cmd_cfg_0, &reg))
		वापस -1;
	अगर (mwअगरiex_ग_लिखो_reg(adapter, card->reg->cmd_cfg_0,
			      reg | CMD_PORT_RD_LEN_EN))
		वापस -1;

	/* Enable Dnld/Upld पढ़ोy स्वतः reset क्रम cmd port after cmd53 is
	 * completed
	 */
	अगर (mwअगरiex_पढ़ो_reg(adapter, card->reg->cmd_cfg_1, &reg))
		वापस -1;
	अगर (mwअगरiex_ग_लिखो_reg(adapter, card->reg->cmd_cfg_1,
			      reg | CMD_PORT_AUTO_EN))
		वापस -1;

	वापस 0;
पूर्ण

/* This function initializes the IO ports.
 *
 * The following operations are perक्रमmed -
 *      - Read the IO ports (0, 1 and 2)
 *      - Set host पूर्णांकerrupt Reset-To-Read to clear
 *      - Set स्वतः re-enable पूर्णांकerrupt
 */
अटल पूर्णांक mwअगरiex_init_sdio_ioport(काष्ठा mwअगरiex_adapter *adapter)
अणु
	u8 reg;
	काष्ठा sdio_mmc_card *card = adapter->card;

	adapter->ioport = 0;

	अगर (card->supports_sdio_new_mode) अणु
		अगर (mwअगरiex_init_sdio_new_mode(adapter))
			वापस -1;
		जाओ cont;
	पूर्ण

	/* Read the IO port */
	अगर (!mwअगरiex_पढ़ो_reg(adapter, card->reg->io_port_0_reg, &reg))
		adapter->ioport |= (reg & 0xff);
	अन्यथा
		वापस -1;

	अगर (!mwअगरiex_पढ़ो_reg(adapter, card->reg->io_port_1_reg, &reg))
		adapter->ioport |= ((reg & 0xff) << 8);
	अन्यथा
		वापस -1;

	अगर (!mwअगरiex_पढ़ो_reg(adapter, card->reg->io_port_2_reg, &reg))
		adapter->ioport |= ((reg & 0xff) << 16);
	अन्यथा
		वापस -1;
cont:
	mwअगरiex_dbg(adapter, INFO,
		    "info: SDIO FUNC1 IO port: %#x\n", adapter->ioport);

	/* Set Host पूर्णांकerrupt reset to पढ़ो to clear */
	अगर (!mwअगरiex_पढ़ो_reg(adapter, card->reg->host_पूर्णांक_rsr_reg, &reg))
		mwअगरiex_ग_लिखो_reg(adapter, card->reg->host_पूर्णांक_rsr_reg,
				  reg | card->reg->sdio_पूर्णांक_mask);
	अन्यथा
		वापस -1;

	/* Dnld/Upld पढ़ोy set to स्वतः reset */
	अगर (!mwअगरiex_पढ़ो_reg(adapter, card->reg->card_misc_cfg_reg, &reg))
		mwअगरiex_ग_लिखो_reg(adapter, card->reg->card_misc_cfg_reg,
				  reg | AUTO_RE_ENABLE_INT);
	अन्यथा
		वापस -1;

	वापस 0;
पूर्ण

/*
 * This function sends data to the card.
 */
अटल पूर्णांक mwअगरiex_ग_लिखो_data_to_card(काष्ठा mwअगरiex_adapter *adapter,
				      u8 *payload, u32 pkt_len, u32 port)
अणु
	u32 i = 0;
	पूर्णांक ret;

	करो अणु
		ret = mwअगरiex_ग_लिखो_data_sync(adapter, payload, pkt_len, port);
		अगर (ret) अणु
			i++;
			mwअगरiex_dbg(adapter, ERROR,
				    "host_to_card, write iomem\t"
				    "(%d) failed: %d\n", i, ret);
			अगर (mwअगरiex_ग_लिखो_reg(adapter, CONFIGURATION_REG, 0x04))
				mwअगरiex_dbg(adapter, ERROR,
					    "write CFG reg failed\n");

			ret = -1;
			अगर (i > MAX_WRITE_IOMEM_RETRY)
				वापस ret;
		पूर्ण
	पूर्ण जबतक (ret == -1);

	वापस ret;
पूर्ण

/*
 * This function माला_लो the पढ़ो port.
 *
 * If control port bit is set in MP पढ़ो biपंचांगap, the control port
 * is वापसed, otherwise the current पढ़ो port is वापसed and
 * the value is increased (provided it करोes not reach the maximum
 * limit, in which हाल it is reset to 1)
 */
अटल पूर्णांक mwअगरiex_get_rd_port(काष्ठा mwअगरiex_adapter *adapter, u8 *port)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_sdio_card_reg *reg = card->reg;
	u32 rd_biपंचांगap = card->mp_rd_biपंचांगap;

	mwअगरiex_dbg(adapter, DATA,
		    "data: mp_rd_bitmap=0x%08x\n", rd_biपंचांगap);

	अगर (card->supports_sdio_new_mode) अणु
		अगर (!(rd_biपंचांगap & reg->data_port_mask))
			वापस -1;
	पूर्ण अन्यथा अणु
		अगर (!(rd_biपंचांगap & (CTRL_PORT_MASK | reg->data_port_mask)))
			वापस -1;
	पूर्ण

	अगर ((card->has_control_mask) &&
	    (card->mp_rd_biपंचांगap & CTRL_PORT_MASK)) अणु
		card->mp_rd_biपंचांगap &= (u32) (~CTRL_PORT_MASK);
		*port = CTRL_PORT;
		mwअगरiex_dbg(adapter, DATA,
			    "data: port=%d mp_rd_bitmap=0x%08x\n",
			    *port, card->mp_rd_biपंचांगap);
		वापस 0;
	पूर्ण

	अगर (!(card->mp_rd_biपंचांगap & (1 << card->curr_rd_port)))
		वापस -1;

	/* We are now handling the SDIO data ports */
	card->mp_rd_biपंचांगap &= (u32)(~(1 << card->curr_rd_port));
	*port = card->curr_rd_port;

	अगर (++card->curr_rd_port == card->max_ports)
		card->curr_rd_port = reg->start_rd_port;

	mwअगरiex_dbg(adapter, DATA,
		    "data: port=%d mp_rd_bitmap=0x%08x -> 0x%08x\n",
		    *port, rd_biपंचांगap, card->mp_rd_biपंचांगap);

	वापस 0;
पूर्ण

/*
 * This function माला_लो the ग_लिखो port क्रम data.
 *
 * The current ग_लिखो port is वापसed अगर available and the value is
 * increased (provided it करोes not reach the maximum limit, in which
 * हाल it is reset to 1)
 */
अटल पूर्णांक mwअगरiex_get_wr_port_data(काष्ठा mwअगरiex_adapter *adapter, u32 *port)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_sdio_card_reg *reg = card->reg;
	u32 wr_biपंचांगap = card->mp_wr_biपंचांगap;

	mwअगरiex_dbg(adapter, DATA,
		    "data: mp_wr_bitmap=0x%08x\n", wr_biपंचांगap);

	अगर (!(wr_biपंचांगap & card->mp_data_port_mask)) अणु
		adapter->data_sent = true;
		वापस -EBUSY;
	पूर्ण

	अगर (card->mp_wr_biपंचांगap & (1 << card->curr_wr_port)) अणु
		card->mp_wr_biपंचांगap &= (u32) (~(1 << card->curr_wr_port));
		*port = card->curr_wr_port;
		अगर (++card->curr_wr_port == card->mp_end_port)
			card->curr_wr_port = reg->start_wr_port;
	पूर्ण अन्यथा अणु
		adapter->data_sent = true;
		वापस -EBUSY;
	पूर्ण

	अगर ((card->has_control_mask) && (*port == CTRL_PORT)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "invalid data port=%d cur port=%d mp_wr_bitmap=0x%08x -> 0x%08x\n",
			    *port, card->curr_wr_port, wr_biपंचांगap,
			    card->mp_wr_biपंचांगap);
		वापस -1;
	पूर्ण

	mwअगरiex_dbg(adapter, DATA,
		    "data: port=%d mp_wr_bitmap=0x%08x -> 0x%08x\n",
		    *port, wr_biपंचांगap, card->mp_wr_biपंचांगap);

	वापस 0;
पूर्ण

/*
 * This function polls the card status.
 */
अटल पूर्णांक
mwअगरiex_sdio_poll_card_status(काष्ठा mwअगरiex_adapter *adapter, u8 bits)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	u32 tries;
	u8 cs;

	क्रम (tries = 0; tries < MAX_POLL_TRIES; tries++) अणु
		अगर (mwअगरiex_पढ़ो_reg(adapter, card->reg->poll_reg, &cs))
			अवरोध;
		अन्यथा अगर ((cs & bits) == bits)
			वापस 0;

		usleep_range(10, 20);
	पूर्ण

	mwअगरiex_dbg(adapter, ERROR,
		    "poll card status failed, tries = %d\n", tries);

	वापस -1;
पूर्ण

/*
 * This function disables the host पूर्णांकerrupt.
 *
 * The host पूर्णांकerrupt mask is पढ़ो, the disable bit is reset and
 * written back to the card host पूर्णांकerrupt mask रेजिस्टर.
 */
अटल व्योम mwअगरiex_sdio_disable_host_पूर्णांक(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	काष्ठा sdio_func *func = card->func;

	sdio_claim_host(func);
	mwअगरiex_ग_लिखो_reg_locked(func, card->reg->host_पूर्णांक_mask_reg, 0);
	sdio_release_irq(func);
	sdio_release_host(func);
पूर्ण

/*
 * This function पढ़ोs the पूर्णांकerrupt status from card.
 */
अटल व्योम mwअगरiex_पूर्णांकerrupt_status(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	u8 sdio_ireg;
	अचिन्हित दीर्घ flags;

	अगर (mwअगरiex_पढ़ो_data_sync(adapter, card->mp_regs,
				   card->reg->max_mp_regs,
				   REG_PORT | MWIFIEX_SDIO_BYTE_MODE_MASK, 0)) अणु
		mwअगरiex_dbg(adapter, ERROR, "read mp_regs failed\n");
		वापस;
	पूर्ण

	sdio_ireg = card->mp_regs[card->reg->host_पूर्णांक_status_reg];
	अगर (sdio_ireg) अणु
		/*
		 * DN_LD_HOST_INT_STATUS and/or UP_LD_HOST_INT_STATUS
		 * For SDIO new mode CMD port पूर्णांकerrupts
		 *	DN_LD_CMD_PORT_HOST_INT_STATUS and/or
		 *	UP_LD_CMD_PORT_HOST_INT_STATUS
		 * Clear the पूर्णांकerrupt status रेजिस्टर
		 */
		mwअगरiex_dbg(adapter, INTR,
			    "int: sdio_ireg = %#x\n", sdio_ireg);
		spin_lock_irqsave(&adapter->पूर्णांक_lock, flags);
		adapter->पूर्णांक_status |= sdio_ireg;
		spin_unlock_irqrestore(&adapter->पूर्णांक_lock, flags);
	पूर्ण
पूर्ण

/*
 * SDIO पूर्णांकerrupt handler.
 *
 * This function पढ़ोs the पूर्णांकerrupt status from firmware and handles
 * the पूर्णांकerrupt in current thपढ़ो (ksdioirqd) right away.
 */
अटल व्योम
mwअगरiex_sdio_पूर्णांकerrupt(काष्ठा sdio_func *func)
अणु
	काष्ठा mwअगरiex_adapter *adapter;
	काष्ठा sdio_mmc_card *card;

	card = sdio_get_drvdata(func);
	अगर (!card || !card->adapter) अणु
		pr_err("int: func=%p card=%p adapter=%p\n",
		       func, card, card ? card->adapter : शून्य);
		वापस;
	पूर्ण
	adapter = card->adapter;

	अगर (!adapter->pps_uapsd_mode && adapter->ps_state == PS_STATE_SLEEP)
		adapter->ps_state = PS_STATE_AWAKE;

	mwअगरiex_पूर्णांकerrupt_status(adapter);
	mwअगरiex_मुख्य_process(adapter);
पूर्ण

/*
 * This function enables the host पूर्णांकerrupt.
 *
 * The host पूर्णांकerrupt enable mask is written to the card
 * host पूर्णांकerrupt mask रेजिस्टर.
 */
अटल पूर्णांक mwअगरiex_sdio_enable_host_पूर्णांक(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	काष्ठा sdio_func *func = card->func;
	पूर्णांक ret;

	sdio_claim_host(func);

	/* Request the SDIO IRQ */
	ret = sdio_claim_irq(func, mwअगरiex_sdio_पूर्णांकerrupt);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "claim irq failed: ret=%d\n", ret);
		जाओ out;
	पूर्ण

	/* Simply ग_लिखो the mask to the रेजिस्टर */
	ret = mwअगरiex_ग_लिखो_reg_locked(func, card->reg->host_पूर्णांक_mask_reg,
				       card->reg->host_पूर्णांक_enable);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "enable host interrupt failed\n");
		sdio_release_irq(func);
	पूर्ण

out:
	sdio_release_host(func);
	वापस ret;
पूर्ण

/*
 * This function sends a data buffer to the card.
 */
अटल पूर्णांक mwअगरiex_sdio_card_to_host(काष्ठा mwअगरiex_adapter *adapter,
				     u32 *type, u8 *buffer,
				     u32 npayload, u32 ioport)
अणु
	पूर्णांक ret;
	u32 nb;

	अगर (!buffer) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: buffer is NULL\n", __func__);
		वापस -1;
	पूर्ण

	ret = mwअगरiex_पढ़ो_data_sync(adapter, buffer, npayload, ioport, 1);

	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: read iomem failed: %d\n", __func__,
			ret);
		वापस -1;
	पूर्ण

	nb = get_unaligned_le16((buffer));
	अगर (nb > npayload) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: invalid packet, nb=%d npayload=%d\n",
			    __func__, nb, npayload);
		वापस -1;
	पूर्ण

	*type = get_unaligned_le16((buffer + 2));

	वापस ret;
पूर्ण

/*
 * This function करोwnloads the firmware to the card.
 *
 * Firmware is करोwnloaded to the card in blocks. Every block करोwnload
 * is tested क्रम CRC errors, and retried a number of बार beक्रमe
 * वापसing failure.
 */
अटल पूर्णांक mwअगरiex_prog_fw_w_helper(काष्ठा mwअगरiex_adapter *adapter,
				    काष्ठा mwअगरiex_fw_image *fw)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_sdio_card_reg *reg = card->reg;
	पूर्णांक ret;
	u8 *firmware = fw->fw_buf;
	u32 firmware_len = fw->fw_len;
	u32 offset = 0;
	u8 base0, base1;
	u8 *fwbuf;
	u16 len = 0;
	u32 txlen, tx_blocks = 0, tries;
	u32 i = 0;

	अगर (!firmware_len) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "firmware image not found! Terminating download\n");
		वापस -1;
	पूर्ण

	mwअगरiex_dbg(adapter, INFO,
		    "info: downloading FW image (%d bytes)\n",
		    firmware_len);

	/* Assume that the allocated buffer is 8-byte aligned */
	fwbuf = kzalloc(MWIFIEX_UPLD_SIZE, GFP_KERNEL);
	अगर (!fwbuf)
		वापस -ENOMEM;

	sdio_claim_host(card->func);

	/* Perक्रमm firmware data transfer */
	करो अणु
		/* The host polls क्रम the DN_LD_CARD_RDY and CARD_IO_READY
		   bits */
		ret = mwअगरiex_sdio_poll_card_status(adapter, CARD_IO_READY |
						    DN_LD_CARD_RDY);
		अगर (ret) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "FW download with helper:\t"
				    "poll status timeout @ %d\n", offset);
			जाओ करोne;
		पूर्ण

		/* More data? */
		अगर (offset >= firmware_len)
			अवरोध;

		क्रम (tries = 0; tries < MAX_POLL_TRIES; tries++) अणु
			ret = mwअगरiex_पढ़ो_reg(adapter, reg->base_0_reg,
					       &base0);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "dev BASE0 register read failed:\t"
					    "base0=%#04X(%d). Terminating dnld\n",
					    base0, base0);
				जाओ करोne;
			पूर्ण
			ret = mwअगरiex_पढ़ो_reg(adapter, reg->base_1_reg,
					       &base1);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "dev BASE1 register read failed:\t"
					    "base1=%#04X(%d). Terminating dnld\n",
					    base1, base1);
				जाओ करोne;
			पूर्ण
			len = (u16) (((base1 & 0xff) << 8) | (base0 & 0xff));

			अगर (len)
				अवरोध;

			usleep_range(10, 20);
		पूर्ण

		अगर (!len) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (len > MWIFIEX_UPLD_SIZE) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "FW dnld failed @ %d, invalid length %d\n",
				    offset, len);
			ret = -1;
			जाओ करोne;
		पूर्ण

		txlen = len;

		अगर (len & BIT(0)) अणु
			i++;
			अगर (i > MAX_WRITE_IOMEM_RETRY) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "FW dnld failed @ %d, over max retry\n",
					    offset);
				ret = -1;
				जाओ करोne;
			पूर्ण
			mwअगरiex_dbg(adapter, ERROR,
				    "CRC indicated by the helper:\t"
				    "len = 0x%04X, txlen = %d\n", len, txlen);
			len &= ~BIT(0);
			/* Setting this to 0 to resend from same offset */
			txlen = 0;
		पूर्ण अन्यथा अणु
			i = 0;

			/* Set blocksize to transfer - checking क्रम last
			   block */
			अगर (firmware_len - offset < txlen)
				txlen = firmware_len - offset;

			tx_blocks = (txlen + MWIFIEX_SDIO_BLOCK_SIZE - 1)
				    / MWIFIEX_SDIO_BLOCK_SIZE;

			/* Copy payload to buffer */
			स_हटाओ(fwbuf, &firmware[offset], txlen);
		पूर्ण

		ret = mwअगरiex_ग_लिखो_data_sync(adapter, fwbuf, tx_blocks *
					      MWIFIEX_SDIO_BLOCK_SIZE,
					      adapter->ioport);
		अगर (ret) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "FW download, write iomem (%d) failed @ %d\n",
				    i, offset);
			अगर (mwअगरiex_ग_लिखो_reg(adapter, CONFIGURATION_REG, 0x04))
				mwअगरiex_dbg(adapter, ERROR,
					    "write CFG reg failed\n");

			ret = -1;
			जाओ करोne;
		पूर्ण

		offset += txlen;
	पूर्ण जबतक (true);

	mwअगरiex_dbg(adapter, MSG,
		    "info: FW download over, size %d bytes\n", offset);

	ret = 0;
करोne:
	sdio_release_host(card->func);
	kमुक्त(fwbuf);
	वापस ret;
पूर्ण

/*
 * This function decode sdio aggreation pkt.
 *
 * Based on the the data block size and pkt_len,
 * skb data will be decoded to few packets.
 */
अटल व्योम mwअगरiex_deaggr_sdio_pkt(काष्ठा mwअगरiex_adapter *adapter,
				    काष्ठा sk_buff *skb)
अणु
	u32 total_pkt_len, pkt_len;
	काष्ठा sk_buff *skb_deaggr;
	u16 blk_size;
	u8 blk_num;
	u8 *data;

	data = skb->data;
	total_pkt_len = skb->len;

	जबतक (total_pkt_len >= (SDIO_HEADER_OFFSET + adapter->पूर्णांकf_hdr_len)) अणु
		अगर (total_pkt_len < adapter->sdio_rx_block_size)
			अवरोध;
		blk_num = *(data + BLOCK_NUMBER_OFFSET);
		blk_size = adapter->sdio_rx_block_size * blk_num;
		अगर (blk_size > total_pkt_len) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "%s: error in blk_size,\t"
				    "blk_num=%d, blk_size=%d, total_pkt_len=%d\n",
				    __func__, blk_num, blk_size, total_pkt_len);
			अवरोध;
		पूर्ण
		pkt_len = get_unaligned_le16((data +
					     SDIO_HEADER_OFFSET));
		अगर ((pkt_len + SDIO_HEADER_OFFSET) > blk_size) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "%s: error in pkt_len,\t"
				    "pkt_len=%d, blk_size=%d\n",
				    __func__, pkt_len, blk_size);
			अवरोध;
		पूर्ण

		skb_deaggr = mwअगरiex_alloc_dma_align_buf(pkt_len, GFP_KERNEL);
		अगर (!skb_deaggr)
			अवरोध;
		skb_put(skb_deaggr, pkt_len);
		स_नकल(skb_deaggr->data, data + SDIO_HEADER_OFFSET, pkt_len);
		skb_pull(skb_deaggr, adapter->पूर्णांकf_hdr_len);

		mwअगरiex_handle_rx_packet(adapter, skb_deaggr);
		data += blk_size;
		total_pkt_len -= blk_size;
	पूर्ण
पूर्ण

/*
 * This function decodes a received packet.
 *
 * Based on the type, the packet is treated as either a data, or
 * a command response, or an event, and the correct handler
 * function is invoked.
 */
अटल पूर्णांक mwअगरiex_decode_rx_packet(काष्ठा mwअगरiex_adapter *adapter,
				    काष्ठा sk_buff *skb, u32 upld_typ)
अणु
	u8 *cmd_buf;
	u16 pkt_len;
	काष्ठा mwअगरiex_rxinfo *rx_info;

	pkt_len = get_unaligned_le16(skb->data);

	अगर (upld_typ != MWIFIEX_TYPE_AGGR_DATA) अणु
		skb_trim(skb, pkt_len);
		skb_pull(skb, adapter->पूर्णांकf_hdr_len);
	पूर्ण

	चयन (upld_typ) अणु
	हाल MWIFIEX_TYPE_AGGR_DATA:
		mwअगरiex_dbg(adapter, INFO,
			    "info: --- Rx: Aggr Data packet ---\n");
		rx_info = MWIFIEX_SKB_RXCB(skb);
		rx_info->buf_type = MWIFIEX_TYPE_AGGR_DATA;
		अगर (adapter->rx_work_enabled) अणु
			skb_queue_tail(&adapter->rx_data_q, skb);
			atomic_inc(&adapter->rx_pending);
			adapter->data_received = true;
		पूर्ण अन्यथा अणु
			mwअगरiex_deaggr_sdio_pkt(adapter, skb);
			dev_kमुक्त_skb_any(skb);
		पूर्ण
		अवरोध;

	हाल MWIFIEX_TYPE_DATA:
		mwअगरiex_dbg(adapter, DATA,
			    "info: --- Rx: Data packet ---\n");
		अगर (adapter->rx_work_enabled) अणु
			skb_queue_tail(&adapter->rx_data_q, skb);
			adapter->data_received = true;
			atomic_inc(&adapter->rx_pending);
		पूर्ण अन्यथा अणु
			mwअगरiex_handle_rx_packet(adapter, skb);
		पूर्ण
		अवरोध;

	हाल MWIFIEX_TYPE_CMD:
		mwअगरiex_dbg(adapter, CMD,
			    "info: --- Rx: Cmd Response ---\n");
		/* take care of curr_cmd = शून्य हाल */
		अगर (!adapter->curr_cmd) अणु
			cmd_buf = adapter->upld_buf;

			अगर (adapter->ps_state == PS_STATE_SLEEP_CFM)
				mwअगरiex_process_sleep_confirm_resp(adapter,
								   skb->data,
								   skb->len);

			स_नकल(cmd_buf, skb->data,
			       min_t(u32, MWIFIEX_SIZE_OF_CMD_BUFFER,
				     skb->len));

			dev_kमुक्त_skb_any(skb);
		पूर्ण अन्यथा अणु
			adapter->cmd_resp_received = true;
			adapter->curr_cmd->resp_skb = skb;
		पूर्ण
		अवरोध;

	हाल MWIFIEX_TYPE_EVENT:
		mwअगरiex_dbg(adapter, EVENT,
			    "info: --- Rx: Event ---\n");
		adapter->event_cause = get_unaligned_le32(skb->data);

		अगर ((skb->len > 0) && (skb->len  < MAX_EVENT_SIZE))
			स_नकल(adapter->event_body,
			       skb->data + MWIFIEX_EVENT_HEADER_LEN,
			       skb->len);

		/* event cause has been saved to adapter->event_cause */
		adapter->event_received = true;
		adapter->event_skb = skb;

		अवरोध;

	शेष:
		mwअगरiex_dbg(adapter, ERROR,
			    "unknown upload type %#x\n", upld_typ);
		dev_kमुक्त_skb_any(skb);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function transfers received packets from card to driver, perक्रमming
 * aggregation अगर required.
 *
 * For data received on control port, or अगर aggregation is disabled, the
 * received buffers are uploaded as separate packets. However, अगर aggregation
 * is enabled and required, the buffers are copied onto an aggregation buffer,
 * provided there is space left, processed and finally uploaded.
 */
अटल पूर्णांक mwअगरiex_sdio_card_to_host_mp_aggr(काष्ठा mwअगरiex_adapter *adapter,
					     u16 rx_len, u8 port)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	s32 f_करो_rx_aggr = 0;
	s32 f_करो_rx_cur = 0;
	s32 f_aggr_cur = 0;
	s32 f_post_aggr_cur = 0;
	काष्ठा sk_buff *skb_deaggr;
	काष्ठा sk_buff *skb = शून्य;
	u32 pkt_len, pkt_type, mport, pind;
	u8 *curr_ptr;

	अगर ((card->has_control_mask) && (port == CTRL_PORT)) अणु
		/* Read the command Resp without aggr */
		mwअगरiex_dbg(adapter, CMD,
			    "info: %s: no aggregation for cmd\t"
			    "response\n", __func__);

		f_करो_rx_cur = 1;
		जाओ rx_curr_single;
	पूर्ण

	अगर (!card->mpa_rx.enabled) अणु
		mwअगरiex_dbg(adapter, WARN,
			    "info: %s: rx aggregation disabled\n",
			    __func__);

		f_करो_rx_cur = 1;
		जाओ rx_curr_single;
	पूर्ण

	अगर ((!card->has_control_mask && (card->mp_rd_biपंचांगap &
					 card->reg->data_port_mask)) ||
	    (card->has_control_mask && (card->mp_rd_biपंचांगap &
					(~((u32) CTRL_PORT_MASK))))) अणु
		/* Some more data RX pending */
		mwअगरiex_dbg(adapter, INFO,
			    "info: %s: not last packet\n", __func__);

		अगर (MP_RX_AGGR_IN_PROGRESS(card)) अणु
			अगर (MP_RX_AGGR_BUF_HAS_ROOM(card, rx_len)) अणु
				f_aggr_cur = 1;
			पूर्ण अन्यथा अणु
				/* No room in Aggr buf, करो rx aggr now */
				f_करो_rx_aggr = 1;
				f_post_aggr_cur = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Rx aggr not in progress */
			f_aggr_cur = 1;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* No more data RX pending */
		mwअगरiex_dbg(adapter, INFO,
			    "info: %s: last packet\n", __func__);

		अगर (MP_RX_AGGR_IN_PROGRESS(card)) अणु
			f_करो_rx_aggr = 1;
			अगर (MP_RX_AGGR_BUF_HAS_ROOM(card, rx_len))
				f_aggr_cur = 1;
			अन्यथा
				/* No room in Aggr buf, करो rx aggr now */
				f_करो_rx_cur = 1;
		पूर्ण अन्यथा अणु
			f_करो_rx_cur = 1;
		पूर्ण
	पूर्ण

	अगर (f_aggr_cur) अणु
		mwअगरiex_dbg(adapter, INFO,
			    "info: current packet aggregation\n");
		/* Curr pkt can be aggregated */
		mp_rx_aggr_setup(card, rx_len, port);

		अगर (MP_RX_AGGR_PKT_LIMIT_REACHED(card) ||
		    mp_rx_aggr_port_limit_reached(card)) अणु
			mwअगरiex_dbg(adapter, INFO,
				    "info: %s: aggregated packet\t"
				    "limit reached\n", __func__);
			/* No more pkts allowed in Aggr buf, rx it */
			f_करो_rx_aggr = 1;
		पूर्ण
	पूर्ण

	अगर (f_करो_rx_aggr) अणु
		/* करो aggr RX now */
		mwअगरiex_dbg(adapter, DATA,
			    "info: do_rx_aggr: num of packets: %d\n",
			    card->mpa_rx.pkt_cnt);

		अगर (card->supports_sdio_new_mode) अणु
			पूर्णांक i;
			u32 port_count;

			क्रम (i = 0, port_count = 0; i < card->max_ports; i++)
				अगर (card->mpa_rx.ports & BIT(i))
					port_count++;

			/* Reading data from "start_port + 0" to "start_port +
			 * port_count -1", so decrease the count by 1
			 */
			port_count--;
			mport = (adapter->ioport | SDIO_MPA_ADDR_BASE |
				 (port_count << 8)) + card->mpa_rx.start_port;
		पूर्ण अन्यथा अणु
			mport = (adapter->ioport | SDIO_MPA_ADDR_BASE |
				 (card->mpa_rx.ports << 4)) +
				 card->mpa_rx.start_port;
		पूर्ण

		अगर (card->mpa_rx.pkt_cnt == 1)
			mport = adapter->ioport + card->mpa_rx.start_port;

		अगर (mwअगरiex_पढ़ो_data_sync(adapter, card->mpa_rx.buf,
					   card->mpa_rx.buf_len, mport, 1))
			जाओ error;

		curr_ptr = card->mpa_rx.buf;

		क्रम (pind = 0; pind < card->mpa_rx.pkt_cnt; pind++) अणु
			u32 *len_arr = card->mpa_rx.len_arr;

			/* get curr PKT len & type */
			pkt_len = get_unaligned_le16(&curr_ptr[0]);
			pkt_type = get_unaligned_le16(&curr_ptr[2]);

			/* copy pkt to deaggr buf */
			skb_deaggr = mwअगरiex_alloc_dma_align_buf(len_arr[pind],
								 GFP_KERNEL);
			अगर (!skb_deaggr) अणु
				mwअगरiex_dbg(adapter, ERROR, "skb allocation failure\t"
					    "drop pkt len=%d type=%d\n",
					    pkt_len, pkt_type);
				curr_ptr += len_arr[pind];
				जारी;
			पूर्ण

			skb_put(skb_deaggr, len_arr[pind]);

			अगर ((pkt_type == MWIFIEX_TYPE_DATA ||
			     (pkt_type == MWIFIEX_TYPE_AGGR_DATA &&
			      adapter->sdio_rx_aggr_enable)) &&
			    (pkt_len <= len_arr[pind])) अणु

				स_नकल(skb_deaggr->data, curr_ptr, pkt_len);

				skb_trim(skb_deaggr, pkt_len);

				/* Process de-aggr packet */
				mwअगरiex_decode_rx_packet(adapter, skb_deaggr,
							 pkt_type);
			पूर्ण अन्यथा अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "drop wrong aggr pkt:\t"
					    "sdio_single_port_rx_aggr=%d\t"
					    "type=%d len=%d max_len=%d\n",
					    adapter->sdio_rx_aggr_enable,
					    pkt_type, pkt_len, len_arr[pind]);
				dev_kमुक्त_skb_any(skb_deaggr);
			पूर्ण
			curr_ptr += len_arr[pind];
		पूर्ण
		MP_RX_AGGR_BUF_RESET(card);
	पूर्ण

rx_curr_single:
	अगर (f_करो_rx_cur) अणु
		mwअगरiex_dbg(adapter, INFO, "info: RX: port: %d, rx_len: %d\n",
			    port, rx_len);

		skb = mwअगरiex_alloc_dma_align_buf(rx_len, GFP_KERNEL);
		अगर (!skb) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "single skb allocated fail,\t"
				    "drop pkt port=%d len=%d\n", port, rx_len);
			अगर (mwअगरiex_sdio_card_to_host(adapter, &pkt_type,
						      card->mpa_rx.buf, rx_len,
						      adapter->ioport + port))
				जाओ error;
			वापस 0;
		पूर्ण

		skb_put(skb, rx_len);

		अगर (mwअगरiex_sdio_card_to_host(adapter, &pkt_type,
					      skb->data, skb->len,
					      adapter->ioport + port))
			जाओ error;
		अगर (!adapter->sdio_rx_aggr_enable &&
		    pkt_type == MWIFIEX_TYPE_AGGR_DATA) अणु
			mwअगरiex_dbg(adapter, ERROR, "drop wrong pkt type %d\t"
				    "current SDIO RX Aggr not enabled\n",
				    pkt_type);
			dev_kमुक्त_skb_any(skb);
			वापस 0;
		पूर्ण

		mwअगरiex_decode_rx_packet(adapter, skb, pkt_type);
	पूर्ण
	अगर (f_post_aggr_cur) अणु
		mwअगरiex_dbg(adapter, INFO,
			    "info: current packet aggregation\n");
		/* Curr pkt can be aggregated */
		mp_rx_aggr_setup(card, rx_len, port);
	पूर्ण

	वापस 0;
error:
	अगर (MP_RX_AGGR_IN_PROGRESS(card))
		MP_RX_AGGR_BUF_RESET(card);

	अगर (f_करो_rx_cur && skb)
		/* Single transfer pending. Free curr buff also */
		dev_kमुक्त_skb_any(skb);

	वापस -1;
पूर्ण

/*
 * This function checks the current पूर्णांकerrupt status.
 *
 * The following पूर्णांकerrupts are checked and handled by this function -
 *      - Data sent
 *      - Command sent
 *      - Packets received
 *
 * Since the firmware करोes not generate करोwnload पढ़ोy पूर्णांकerrupt अगर the
 * port updated is command port only, command sent पूर्णांकerrupt checking
 * should be करोne manually, and क्रम every SDIO पूर्णांकerrupt.
 *
 * In हाल of Rx packets received, the packets are uploaded from card to
 * host and processed accordingly.
 */
अटल पूर्णांक mwअगरiex_process_पूर्णांक_status(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_sdio_card_reg *reg = card->reg;
	पूर्णांक ret = 0;
	u8 sdio_ireg;
	काष्ठा sk_buff *skb;
	u8 port = CTRL_PORT;
	u32 len_reg_l, len_reg_u;
	u32 rx_blocks;
	u16 rx_len;
	अचिन्हित दीर्घ flags;
	u32 biपंचांगap;
	u8 cr;

	spin_lock_irqsave(&adapter->पूर्णांक_lock, flags);
	sdio_ireg = adapter->पूर्णांक_status;
	adapter->पूर्णांक_status = 0;
	spin_unlock_irqrestore(&adapter->पूर्णांक_lock, flags);

	अगर (!sdio_ireg)
		वापस ret;

	/* Following पूर्णांकerrupt is only क्रम SDIO new mode */
	अगर (sdio_ireg & DN_LD_CMD_PORT_HOST_INT_STATUS && adapter->cmd_sent)
		adapter->cmd_sent = false;

	/* Following पूर्णांकerrupt is only क्रम SDIO new mode */
	अगर (sdio_ireg & UP_LD_CMD_PORT_HOST_INT_STATUS) अणु
		u32 pkt_type;

		/* पढ़ो the len of control packet */
		rx_len = card->mp_regs[reg->cmd_rd_len_1] << 8;
		rx_len |= (u16)card->mp_regs[reg->cmd_rd_len_0];
		rx_blocks = DIV_ROUND_UP(rx_len, MWIFIEX_SDIO_BLOCK_SIZE);
		अगर (rx_len <= adapter->पूर्णांकf_hdr_len ||
		    (rx_blocks * MWIFIEX_SDIO_BLOCK_SIZE) >
		     MWIFIEX_RX_DATA_BUF_SIZE)
			वापस -1;
		rx_len = (u16) (rx_blocks * MWIFIEX_SDIO_BLOCK_SIZE);
		mwअगरiex_dbg(adapter, INFO, "info: rx_len = %d\n", rx_len);

		skb = mwअगरiex_alloc_dma_align_buf(rx_len, GFP_KERNEL);
		अगर (!skb)
			वापस -1;

		skb_put(skb, rx_len);

		अगर (mwअगरiex_sdio_card_to_host(adapter, &pkt_type, skb->data,
					      skb->len, adapter->ioport |
							CMD_PORT_SLCT)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "%s: failed to card_to_host", __func__);
			dev_kमुक्त_skb_any(skb);
			जाओ term_cmd;
		पूर्ण

		अगर ((pkt_type != MWIFIEX_TYPE_CMD) &&
		    (pkt_type != MWIFIEX_TYPE_EVENT))
			mwअगरiex_dbg(adapter, ERROR,
				    "%s:Received wrong packet on cmd port",
				    __func__);

		mwअगरiex_decode_rx_packet(adapter, skb, pkt_type);
	पूर्ण

	अगर (sdio_ireg & DN_LD_HOST_INT_STATUS) अणु
		biपंचांगap = (u32) card->mp_regs[reg->wr_biपंचांगap_l];
		biपंचांगap |= ((u32) card->mp_regs[reg->wr_biपंचांगap_u]) << 8;
		अगर (card->supports_sdio_new_mode) अणु
			biपंचांगap |=
				((u32) card->mp_regs[reg->wr_biपंचांगap_1l]) << 16;
			biपंचांगap |=
				((u32) card->mp_regs[reg->wr_biपंचांगap_1u]) << 24;
		पूर्ण
		card->mp_wr_biपंचांगap = biपंचांगap;

		mwअगरiex_dbg(adapter, INTR,
			    "int: DNLD: wr_bitmap=0x%x\n",
			    card->mp_wr_biपंचांगap);
		अगर (adapter->data_sent &&
		    (card->mp_wr_biपंचांगap & card->mp_data_port_mask)) अणु
			mwअगरiex_dbg(adapter, INTR,
				    "info:  <--- Tx DONE Interrupt --->\n");
			adapter->data_sent = false;
		पूर्ण
	पूर्ण

	/* As firmware will not generate करोwnload पढ़ोy पूर्णांकerrupt अगर the port
	   updated is command port only, cmd_sent should be करोne क्रम any SDIO
	   पूर्णांकerrupt. */
	अगर (card->has_control_mask && adapter->cmd_sent) अणु
		/* Check अगर firmware has attach buffer at command port and
		   update just that in wr_bit_map. */
		card->mp_wr_biपंचांगap |=
			(u32) card->mp_regs[reg->wr_biपंचांगap_l] & CTRL_PORT_MASK;
		अगर (card->mp_wr_biपंचांगap & CTRL_PORT_MASK)
			adapter->cmd_sent = false;
	पूर्ण

	mwअगरiex_dbg(adapter, INTR, "info: cmd_sent=%d data_sent=%d\n",
		    adapter->cmd_sent, adapter->data_sent);
	अगर (sdio_ireg & UP_LD_HOST_INT_STATUS) अणु
		biपंचांगap = (u32) card->mp_regs[reg->rd_biपंचांगap_l];
		biपंचांगap |= ((u32) card->mp_regs[reg->rd_biपंचांगap_u]) << 8;
		अगर (card->supports_sdio_new_mode) अणु
			biपंचांगap |=
				((u32) card->mp_regs[reg->rd_biपंचांगap_1l]) << 16;
			biपंचांगap |=
				((u32) card->mp_regs[reg->rd_biपंचांगap_1u]) << 24;
		पूर्ण
		card->mp_rd_biपंचांगap = biपंचांगap;
		mwअगरiex_dbg(adapter, INTR,
			    "int: UPLD: rd_bitmap=0x%x\n",
			    card->mp_rd_biपंचांगap);

		जबतक (true) अणु
			ret = mwअगरiex_get_rd_port(adapter, &port);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, INFO,
					    "info: no more rd_port available\n");
				अवरोध;
			पूर्ण
			len_reg_l = reg->rd_len_p0_l + (port << 1);
			len_reg_u = reg->rd_len_p0_u + (port << 1);
			rx_len = ((u16) card->mp_regs[len_reg_u]) << 8;
			rx_len |= (u16) card->mp_regs[len_reg_l];
			mwअगरiex_dbg(adapter, INFO,
				    "info: RX: port=%d rx_len=%u\n",
				    port, rx_len);
			rx_blocks =
				(rx_len + MWIFIEX_SDIO_BLOCK_SIZE -
				 1) / MWIFIEX_SDIO_BLOCK_SIZE;
			अगर (rx_len <= adapter->पूर्णांकf_hdr_len ||
			    (card->mpa_rx.enabled &&
			     ((rx_blocks * MWIFIEX_SDIO_BLOCK_SIZE) >
			      card->mpa_rx.buf_size))) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "invalid rx_len=%d\n",
					    rx_len);
				वापस -1;
			पूर्ण

			rx_len = (u16) (rx_blocks * MWIFIEX_SDIO_BLOCK_SIZE);
			mwअगरiex_dbg(adapter, INFO, "info: rx_len = %d\n",
				    rx_len);

			अगर (mwअगरiex_sdio_card_to_host_mp_aggr(adapter, rx_len,
							      port)) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "card_to_host_mpa failed: int status=%#x\n",
					    sdio_ireg);
				जाओ term_cmd;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

term_cmd:
	/* terminate cmd */
	अगर (mwअगरiex_पढ़ो_reg(adapter, CONFIGURATION_REG, &cr))
		mwअगरiex_dbg(adapter, ERROR, "read CFG reg failed\n");
	अन्यथा
		mwअगरiex_dbg(adapter, INFO,
			    "info: CFG reg val = %d\n", cr);

	अगर (mwअगरiex_ग_लिखो_reg(adapter, CONFIGURATION_REG, (cr | 0x04)))
		mwअगरiex_dbg(adapter, ERROR,
			    "write CFG reg failed\n");
	अन्यथा
		mwअगरiex_dbg(adapter, INFO, "info: write success\n");

	अगर (mwअगरiex_पढ़ो_reg(adapter, CONFIGURATION_REG, &cr))
		mwअगरiex_dbg(adapter, ERROR,
			    "read CFG reg failed\n");
	अन्यथा
		mwअगरiex_dbg(adapter, INFO,
			    "info: CFG reg val =%x\n", cr);

	वापस -1;
पूर्ण

/*
 * This function aggregates transmission buffers in driver and करोwnloads
 * the aggregated packet to card.
 *
 * The inभागidual packets are aggregated by copying पूर्णांकo an aggregation
 * buffer and then करोwnloaded to the card. Previous unsent packets in the
 * aggregation buffer are pre-copied first beक्रमe new packets are added.
 * Aggregation is करोne till there is space left in the aggregation buffer,
 * or till new packets are available.
 *
 * The function will only करोwnload the packet to the card when aggregation
 * stops, otherwise it will just aggregate the packet in aggregation buffer
 * and वापस.
 */
अटल पूर्णांक mwअगरiex_host_to_card_mp_aggr(काष्ठा mwअगरiex_adapter *adapter,
					u8 *payload, u32 pkt_len, u32 port,
					u32 next_pkt_len)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	पूर्णांक ret = 0;
	s32 f_send_aggr_buf = 0;
	s32 f_send_cur_buf = 0;
	s32 f_precopy_cur_buf = 0;
	s32 f_postcopy_cur_buf = 0;
	u32 mport;
	पूर्णांक index;

	अगर (!card->mpa_tx.enabled ||
	    (card->has_control_mask && (port == CTRL_PORT)) ||
	    (card->supports_sdio_new_mode && (port == CMD_PORT_SLCT))) अणु
		mwअगरiex_dbg(adapter, WARN,
			    "info: %s: tx aggregation disabled\n",
			    __func__);

		f_send_cur_buf = 1;
		जाओ tx_curr_single;
	पूर्ण

	अगर (next_pkt_len) अणु
		/* More pkt in TX queue */
		mwअगरiex_dbg(adapter, INFO,
			    "info: %s: more packets in queue.\n",
			    __func__);

		अगर (MP_TX_AGGR_IN_PROGRESS(card)) अणु
			अगर (MP_TX_AGGR_BUF_HAS_ROOM(card, pkt_len)) अणु
				f_precopy_cur_buf = 1;

				अगर (!(card->mp_wr_biपंचांगap &
				      (1 << card->curr_wr_port)) ||
				    !MP_TX_AGGR_BUF_HAS_ROOM(
					    card, pkt_len + next_pkt_len))
					f_send_aggr_buf = 1;
			पूर्ण अन्यथा अणु
				/* No room in Aggr buf, send it */
				f_send_aggr_buf = 1;

				अगर (!(card->mp_wr_biपंचांगap &
				      (1 << card->curr_wr_port)))
					f_send_cur_buf = 1;
				अन्यथा
					f_postcopy_cur_buf = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (MP_TX_AGGR_BUF_HAS_ROOM(card, pkt_len) &&
			    (card->mp_wr_biपंचांगap & (1 << card->curr_wr_port)))
				f_precopy_cur_buf = 1;
			अन्यथा
				f_send_cur_buf = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Last pkt in TX queue */
		mwअगरiex_dbg(adapter, INFO,
			    "info: %s: Last packet in Tx Queue.\n",
			    __func__);

		अगर (MP_TX_AGGR_IN_PROGRESS(card)) अणु
			/* some packs in Aggr buf alपढ़ोy */
			f_send_aggr_buf = 1;

			अगर (MP_TX_AGGR_BUF_HAS_ROOM(card, pkt_len))
				f_precopy_cur_buf = 1;
			अन्यथा
				/* No room in Aggr buf, send it */
				f_send_cur_buf = 1;
		पूर्ण अन्यथा अणु
			f_send_cur_buf = 1;
		पूर्ण
	पूर्ण

	अगर (f_precopy_cur_buf) अणु
		mwअगरiex_dbg(adapter, DATA,
			    "data: %s: precopy current buffer\n",
			    __func__);
		MP_TX_AGGR_BUF_PUT(card, payload, pkt_len, port);

		अगर (MP_TX_AGGR_PKT_LIMIT_REACHED(card) ||
		    mp_tx_aggr_port_limit_reached(card))
			/* No more pkts allowed in Aggr buf, send it */
			f_send_aggr_buf = 1;
	पूर्ण

	अगर (f_send_aggr_buf) अणु
		mwअगरiex_dbg(adapter, DATA,
			    "data: %s: send aggr buffer: %d %d\n",
			    __func__, card->mpa_tx.start_port,
			    card->mpa_tx.ports);
		अगर (card->supports_sdio_new_mode) अणु
			u32 port_count;
			पूर्णांक i;

			क्रम (i = 0, port_count = 0; i < card->max_ports; i++)
				अगर (card->mpa_tx.ports & BIT(i))
					port_count++;

			/* Writing data from "start_port + 0" to "start_port +
			 * port_count -1", so decrease the count by 1
			 */
			port_count--;
			mport = (adapter->ioport | SDIO_MPA_ADDR_BASE |
				 (port_count << 8)) + card->mpa_tx.start_port;
		पूर्ण अन्यथा अणु
			mport = (adapter->ioport | SDIO_MPA_ADDR_BASE |
				 (card->mpa_tx.ports << 4)) +
				 card->mpa_tx.start_port;
		पूर्ण

		अगर (card->mpa_tx.pkt_cnt == 1)
			mport = adapter->ioport + card->mpa_tx.start_port;

		ret = mwअगरiex_ग_लिखो_data_to_card(adapter, card->mpa_tx.buf,
						 card->mpa_tx.buf_len, mport);

		/* Save the last multi port tx aggreagation info to debug log */
		index = adapter->dbg.last_sdio_mp_index;
		index = (index + 1) % MWIFIEX_DBG_SDIO_MP_NUM;
		adapter->dbg.last_sdio_mp_index = index;
		adapter->dbg.last_mp_wr_ports[index] = mport;
		adapter->dbg.last_mp_wr_biपंचांगap[index] = card->mp_wr_biपंचांगap;
		adapter->dbg.last_mp_wr_len[index] = card->mpa_tx.buf_len;
		adapter->dbg.last_mp_curr_wr_port[index] = card->curr_wr_port;

		MP_TX_AGGR_BUF_RESET(card);
	पूर्ण

tx_curr_single:
	अगर (f_send_cur_buf) अणु
		mwअगरiex_dbg(adapter, DATA,
			    "data: %s: send current buffer %d\n",
			    __func__, port);
		ret = mwअगरiex_ग_लिखो_data_to_card(adapter, payload, pkt_len,
						 adapter->ioport + port);
	पूर्ण

	अगर (f_postcopy_cur_buf) अणु
		mwअगरiex_dbg(adapter, DATA,
			    "data: %s: postcopy current buffer\n",
			    __func__);
		MP_TX_AGGR_BUF_PUT(card, payload, pkt_len, port);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function करोwnloads data from driver to card.
 *
 * Both commands and data packets are transferred to the card by this
 * function.
 *
 * This function adds the SDIO specअगरic header to the front of the buffer
 * beक्रमe transferring. The header contains the length of the packet and
 * the type. The firmware handles the packets based upon this set type.
 */
अटल पूर्णांक mwअगरiex_sdio_host_to_card(काष्ठा mwअगरiex_adapter *adapter,
				     u8 type, काष्ठा sk_buff *skb,
				     काष्ठा mwअगरiex_tx_param *tx_param)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	पूर्णांक ret;
	u32 buf_block_len;
	u32 blk_size;
	u32 port = CTRL_PORT;
	u8 *payload = (u8 *)skb->data;
	u32 pkt_len = skb->len;

	/* Allocate buffer and copy payload */
	blk_size = MWIFIEX_SDIO_BLOCK_SIZE;
	buf_block_len = (pkt_len + blk_size - 1) / blk_size;
	put_unaligned_le16((u16)pkt_len, payload + 0);
	put_unaligned_le16((u32)type, payload + 2);


	/*
	 * This is SDIO specअगरic header
	 *  u16 length,
	 *  u16 type (MWIFIEX_TYPE_DATA = 0, MWIFIEX_TYPE_CMD = 1,
	 *  MWIFIEX_TYPE_EVENT = 3)
	 */
	अगर (type == MWIFIEX_TYPE_DATA) अणु
		ret = mwअगरiex_get_wr_port_data(adapter, &port);
		अगर (ret) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "%s: no wr_port available\n",
				    __func__);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		adapter->cmd_sent = true;
		/* Type must be MWIFIEX_TYPE_CMD */

		अगर (pkt_len <= adapter->पूर्णांकf_hdr_len ||
		    pkt_len > MWIFIEX_UPLD_SIZE)
			mwअगरiex_dbg(adapter, ERROR,
				    "%s: payload=%p, nb=%d\n",
				    __func__, payload, pkt_len);

		अगर (card->supports_sdio_new_mode)
			port = CMD_PORT_SLCT;
	पूर्ण

	/* Transfer data to card */
	pkt_len = buf_block_len * blk_size;

	अगर (tx_param)
		ret = mwअगरiex_host_to_card_mp_aggr(adapter, payload, pkt_len,
						   port, tx_param->next_pkt_len
						   );
	अन्यथा
		ret = mwअगरiex_host_to_card_mp_aggr(adapter, payload, pkt_len,
						   port, 0);

	अगर (ret) अणु
		अगर (type == MWIFIEX_TYPE_CMD)
			adapter->cmd_sent = false;
		अगर (type == MWIFIEX_TYPE_DATA) अणु
			adapter->data_sent = false;
			/* restore curr_wr_port in error हालs */
			card->curr_wr_port = port;
			card->mp_wr_biपंचांगap |= (u32)(1 << card->curr_wr_port);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (type == MWIFIEX_TYPE_DATA) अणु
			अगर (!(card->mp_wr_biपंचांगap & (1 << card->curr_wr_port)))
				adapter->data_sent = true;
			अन्यथा
				adapter->data_sent = false;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function allocates the MPA Tx and Rx buffers.
 */
अटल पूर्णांक mwअगरiex_alloc_sdio_mpa_buffers(काष्ठा mwअगरiex_adapter *adapter,
				   u32 mpa_tx_buf_size, u32 mpa_rx_buf_size)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	u32 rx_buf_size;
	पूर्णांक ret = 0;

	card->mpa_tx.buf = kzalloc(mpa_tx_buf_size, GFP_KERNEL);
	अगर (!card->mpa_tx.buf) अणु
		ret = -1;
		जाओ error;
	पूर्ण

	card->mpa_tx.buf_size = mpa_tx_buf_size;

	rx_buf_size = max_t(u32, mpa_rx_buf_size,
			    (u32)SDIO_MAX_AGGR_BUF_SIZE);
	card->mpa_rx.buf = kzalloc(rx_buf_size, GFP_KERNEL);
	अगर (!card->mpa_rx.buf) अणु
		ret = -1;
		जाओ error;
	पूर्ण

	card->mpa_rx.buf_size = rx_buf_size;

error:
	अगर (ret) अणु
		kमुक्त(card->mpa_tx.buf);
		kमुक्त(card->mpa_rx.buf);
		card->mpa_tx.buf_size = 0;
		card->mpa_rx.buf_size = 0;
		card->mpa_tx.buf = शून्य;
		card->mpa_rx.buf = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function unरेजिस्टरs the SDIO device.
 *
 * The SDIO IRQ is released, the function is disabled and driver
 * data is set to null.
 */
अटल व्योम
mwअगरiex_unरेजिस्टर_dev(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;

	अगर (adapter->card) अणु
		card->adapter = शून्य;
		sdio_claim_host(card->func);
		sdio_disable_func(card->func);
		sdio_release_host(card->func);
	पूर्ण
पूर्ण

/*
 * This function रेजिस्टरs the SDIO device.
 *
 * SDIO IRQ is claimed, block size is set and driver data is initialized.
 */
अटल पूर्णांक mwअगरiex_रेजिस्टर_dev(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक ret;
	काष्ठा sdio_mmc_card *card = adapter->card;
	काष्ठा sdio_func *func = card->func;

	/* save adapter poपूर्णांकer in card */
	card->adapter = adapter;
	adapter->tx_buf_size = card->tx_buf_size;

	sdio_claim_host(func);

	/* Set block size */
	ret = sdio_set_block_size(card->func, MWIFIEX_SDIO_BLOCK_SIZE);
	sdio_release_host(func);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "cannot set SDIO block size\n");
		वापस ret;
	पूर्ण

	म_नकल(adapter->fw_name, card->firmware);
	अगर (card->fw_dump_enh) अणु
		adapter->mem_type_mapping_tbl = generic_mem_type_map;
		adapter->num_mem_types = 1;
	पूर्ण अन्यथा अणु
		adapter->mem_type_mapping_tbl = mem_type_mapping_tbl;
		adapter->num_mem_types = ARRAY_SIZE(mem_type_mapping_tbl);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function initializes the SDIO driver.
 *
 * The following initializations steps are followed -
 *      - Read the Host पूर्णांकerrupt status रेजिस्टर to acknowledge
 *        the first पूर्णांकerrupt got from bootloader
 *      - Disable host पूर्णांकerrupt mask रेजिस्टर
 *      - Get SDIO port
 *      - Initialize SDIO variables in card
 *      - Allocate MP रेजिस्टरs
 *      - Allocate MPA Tx and Rx buffers
 */
अटल पूर्णांक mwअगरiex_init_sdio(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_sdio_card_reg *reg = card->reg;
	पूर्णांक ret;
	u8 sdio_ireg;

	sdio_set_drvdata(card->func, card);

	/*
	 * Read the host_पूर्णांक_status_reg क्रम ACK the first पूर्णांकerrupt got
	 * from the bootloader. If we करोn't करो this we get a पूर्णांकerrupt
	 * as soon as we रेजिस्टर the irq.
	 */
	mwअगरiex_पढ़ो_reg(adapter, card->reg->host_पूर्णांक_status_reg, &sdio_ireg);

	/* Get SDIO ioport */
	mwअगरiex_init_sdio_ioport(adapter);

	/* Initialize SDIO variables in card */
	card->mp_rd_biपंचांगap = 0;
	card->mp_wr_biपंचांगap = 0;
	card->curr_rd_port = reg->start_rd_port;
	card->curr_wr_port = reg->start_wr_port;

	card->mp_data_port_mask = reg->data_port_mask;

	card->mpa_tx.buf_len = 0;
	card->mpa_tx.pkt_cnt = 0;
	card->mpa_tx.start_port = 0;

	card->mpa_tx.enabled = 1;
	card->mpa_tx.pkt_aggr_limit = card->mp_agg_pkt_limit;

	card->mpa_rx.buf_len = 0;
	card->mpa_rx.pkt_cnt = 0;
	card->mpa_rx.start_port = 0;

	card->mpa_rx.enabled = 1;
	card->mpa_rx.pkt_aggr_limit = card->mp_agg_pkt_limit;

	/* Allocate buffers क्रम SDIO MP-A */
	card->mp_regs = kzalloc(reg->max_mp_regs, GFP_KERNEL);
	अगर (!card->mp_regs)
		वापस -ENOMEM;

	/* Allocate skb poपूर्णांकer buffers */
	card->mpa_rx.skb_arr = kसुस्मृति(card->mp_agg_pkt_limit, माप(व्योम *),
				       GFP_KERNEL);
	अगर (!card->mpa_rx.skb_arr) अणु
		kमुक्त(card->mp_regs);
		वापस -ENOMEM;
	पूर्ण

	card->mpa_rx.len_arr = kसुस्मृति(card->mp_agg_pkt_limit,
				       माप(*card->mpa_rx.len_arr),
				       GFP_KERNEL);
	अगर (!card->mpa_rx.len_arr) अणु
		kमुक्त(card->mp_regs);
		kमुक्त(card->mpa_rx.skb_arr);
		वापस -ENOMEM;
	पूर्ण

	ret = mwअगरiex_alloc_sdio_mpa_buffers(adapter,
					     card->mp_tx_agg_buf_size,
					     card->mp_rx_agg_buf_size);

	/* Allocate 32k MPA Tx/Rx buffers अगर 64k memory allocation fails */
	अगर (ret && (card->mp_tx_agg_buf_size == MWIFIEX_MP_AGGR_BUF_SIZE_MAX ||
		    card->mp_rx_agg_buf_size == MWIFIEX_MP_AGGR_BUF_SIZE_MAX)) अणु
		/* Disable rx single port aggregation */
		adapter->host_disable_sdio_rx_aggr = true;

		ret = mwअगरiex_alloc_sdio_mpa_buffers
			(adapter, MWIFIEX_MP_AGGR_BUF_SIZE_32K,
			 MWIFIEX_MP_AGGR_BUF_SIZE_32K);
		अगर (ret) अणु
			/* Disable multi port aggregation */
			card->mpa_tx.enabled = 0;
			card->mpa_rx.enabled = 0;
		पूर्ण
	पूर्ण

	adapter->स्वतः_tdls = card->can_स्वतः_tdls;
	adapter->ext_scan = card->can_ext_scan;
	वापस 0;
पूर्ण

/*
 * This function resets the MPA Tx and Rx buffers.
 */
अटल व्योम mwअगरiex_cleanup_mpa_buf(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;

	MP_TX_AGGR_BUF_RESET(card);
	MP_RX_AGGR_BUF_RESET(card);
पूर्ण

/*
 * This function cleans up the allocated card buffers.
 *
 * The following are मुक्तd by this function -
 *      - MP रेजिस्टरs
 *      - MPA Tx buffer
 *      - MPA Rx buffer
 */
अटल व्योम mwअगरiex_cleanup_sdio(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;

	cancel_work_sync(&card->work);

	kमुक्त(card->mp_regs);
	kमुक्त(card->mpa_rx.skb_arr);
	kमुक्त(card->mpa_rx.len_arr);
	kमुक्त(card->mpa_tx.buf);
	kमुक्त(card->mpa_rx.buf);
पूर्ण

/*
 * This function updates the MP end port in card.
 */
अटल व्योम
mwअगरiex_update_mp_end_port(काष्ठा mwअगरiex_adapter *adapter, u16 port)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	स्थिर काष्ठा mwअगरiex_sdio_card_reg *reg = card->reg;
	पूर्णांक i;

	card->mp_end_port = port;

	card->mp_data_port_mask = reg->data_port_mask;

	अगर (reg->start_wr_port) अणु
		क्रम (i = 1; i <= card->max_ports - card->mp_end_port; i++)
			card->mp_data_port_mask &=
					~(1 << (card->max_ports - i));
	पूर्ण

	card->curr_wr_port = reg->start_wr_port;

	mwअगरiex_dbg(adapter, CMD,
		    "cmd: mp_end_port %d, data port mask 0x%x\n",
		    port, card->mp_data_port_mask);
पूर्ण

अटल व्योम mwअगरiex_sdio_card_reset_work(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	काष्ठा sdio_func *func = card->func;
	पूर्णांक ret;

	/* Prepare the adapter क्रम the reset. */
	mwअगरiex_shutकरोwn_sw(adapter);
	clear_bit(MWIFIEX_IFACE_WORK_DEVICE_DUMP, &card->work_flags);
	clear_bit(MWIFIEX_IFACE_WORK_CARD_RESET, &card->work_flags);

	/* Run a HW reset of the SDIO पूर्णांकerface. */
	sdio_claim_host(func);
	ret = mmc_hw_reset(func->card->host);
	sdio_release_host(func);

	चयन (ret) अणु
	हाल 1:
		dev_dbg(&func->dev, "SDIO HW reset asynchronous\n");
		complete_all(adapter->fw_करोne);
		अवरोध;
	हाल 0:
		ret = mwअगरiex_reinit_sw(adapter);
		अगर (ret)
			dev_err(&func->dev, "reinit failed: %d\n", ret);
		अवरोध;
	शेष:
		dev_err(&func->dev, "SDIO HW reset failed: %d\n", ret);
		अवरोध;
	पूर्ण
पूर्ण

/* This function पढ़ो/ग_लिखो firmware */
अटल क्रमागत
rdwr_status mwअगरiex_sdio_rdwr_firmware(काष्ठा mwअगरiex_adapter *adapter,
				       u8 करोneflag)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	पूर्णांक ret, tries;
	u8 ctrl_data = 0;

	sdio_ग_लिखोb(card->func, card->reg->fw_dump_host_पढ़ोy,
		    card->reg->fw_dump_ctrl, &ret);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR, "SDIO Write ERR\n");
		वापस RDWR_STATUS_FAILURE;
	पूर्ण
	क्रम (tries = 0; tries < MAX_POLL_TRIES; tries++) अणु
		ctrl_data = sdio_पढ़ोb(card->func, card->reg->fw_dump_ctrl,
				       &ret);
		अगर (ret) अणु
			mwअगरiex_dbg(adapter, ERROR, "SDIO read err\n");
			वापस RDWR_STATUS_FAILURE;
		पूर्ण
		अगर (ctrl_data == FW_DUMP_DONE)
			अवरोध;
		अगर (करोneflag && ctrl_data == करोneflag)
			वापस RDWR_STATUS_DONE;
		अगर (ctrl_data != card->reg->fw_dump_host_पढ़ोy) अणु
			mwअगरiex_dbg(adapter, WARN,
				    "The ctrl reg was changed, re-try again\n");
			sdio_ग_लिखोb(card->func, card->reg->fw_dump_host_पढ़ोy,
				    card->reg->fw_dump_ctrl, &ret);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, ERROR, "SDIO write err\n");
				वापस RDWR_STATUS_FAILURE;
			पूर्ण
		पूर्ण
		usleep_range(100, 200);
	पूर्ण
	अगर (ctrl_data == card->reg->fw_dump_host_पढ़ोy) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Fail to pull ctrl_data\n");
		वापस RDWR_STATUS_FAILURE;
	पूर्ण

	वापस RDWR_STATUS_SUCCESS;
पूर्ण

/* This function dump firmware memory to file */
अटल व्योम mwअगरiex_sdio_fw_dump(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक reg, reg_start, reg_end;
	u8 *dbg_ptr, *end_ptr, dump_num, idx, i, पढ़ो_reg, करोneflag = 0;
	क्रमागत rdwr_status stat;
	u32 memory_size;

	अगर (!card->can_dump_fw)
		वापस;

	क्रम (idx = 0; idx < ARRAY_SIZE(mem_type_mapping_tbl); idx++) अणु
		काष्ठा memory_type_mapping *entry = &mem_type_mapping_tbl[idx];

		अगर (entry->mem_ptr) अणु
			vमुक्त(entry->mem_ptr);
			entry->mem_ptr = शून्य;
		पूर्ण
		entry->mem_size = 0;
	पूर्ण

	mwअगरiex_pm_wakeup_card(adapter);
	sdio_claim_host(card->func);

	mwअगरiex_dbg(adapter, MSG, "== mwifiex firmware dump start ==\n");

	stat = mwअगरiex_sdio_rdwr_firmware(adapter, करोneflag);
	अगर (stat == RDWR_STATUS_FAILURE)
		जाओ करोne;

	reg = card->reg->fw_dump_start;
	/* Read the number of the memories which will dump */
	dump_num = sdio_पढ़ोb(card->func, reg, &ret);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR, "SDIO read memory length err\n");
		जाओ करोne;
	पूर्ण

	/* Read the length of every memory which will dump */
	क्रम (idx = 0; idx < dump_num; idx++) अणु
		काष्ठा memory_type_mapping *entry = &mem_type_mapping_tbl[idx];

		stat = mwअगरiex_sdio_rdwr_firmware(adapter, करोneflag);
		अगर (stat == RDWR_STATUS_FAILURE)
			जाओ करोne;

		memory_size = 0;
		reg = card->reg->fw_dump_start;
		क्रम (i = 0; i < 4; i++) अणु
			पढ़ो_reg = sdio_पढ़ोb(card->func, reg, &ret);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, ERROR, "SDIO read err\n");
				जाओ करोne;
			पूर्ण
			memory_size |= (पढ़ो_reg << i*8);
			reg++;
		पूर्ण

		अगर (memory_size == 0) अणु
			mwअगरiex_dbg(adapter, DUMP, "Firmware dump Finished!\n");
			ret = mwअगरiex_ग_लिखो_reg(adapter,
						card->reg->fw_dump_ctrl,
						FW_DUMP_READ_DONE);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, ERROR, "SDIO write err\n");
				वापस;
			पूर्ण
			अवरोध;
		पूर्ण

		mwअगरiex_dbg(adapter, DUMP,
			    "%s_SIZE=0x%x\n", entry->mem_name, memory_size);
		entry->mem_ptr = vदो_स्मृति(memory_size + 1);
		entry->mem_size = memory_size;
		अगर (!entry->mem_ptr) अणु
			mwअगरiex_dbg(adapter, ERROR, "Vmalloc %s failed\n",
				    entry->mem_name);
			जाओ करोne;
		पूर्ण
		dbg_ptr = entry->mem_ptr;
		end_ptr = dbg_ptr + memory_size;

		करोneflag = entry->करोne_flag;
		mwअगरiex_dbg(adapter, DUMP,
			    "Start %s output, please wait...\n",
			    entry->mem_name);

		करो अणु
			stat = mwअगरiex_sdio_rdwr_firmware(adapter, करोneflag);
			अगर (stat == RDWR_STATUS_FAILURE)
				जाओ करोne;

			reg_start = card->reg->fw_dump_start;
			reg_end = card->reg->fw_dump_end;
			क्रम (reg = reg_start; reg <= reg_end; reg++) अणु
				*dbg_ptr = sdio_पढ़ोb(card->func, reg, &ret);
				अगर (ret) अणु
					mwअगरiex_dbg(adapter, ERROR,
						    "SDIO read err\n");
					जाओ करोne;
				पूर्ण
				अगर (dbg_ptr < end_ptr)
					dbg_ptr++;
				अन्यथा
					mwअगरiex_dbg(adapter, ERROR,
						    "Allocated buf not enough\n");
			पूर्ण

			अगर (stat != RDWR_STATUS_DONE)
				जारी;

			mwअगरiex_dbg(adapter, DUMP, "%s done: size=0x%tx\n",
				    entry->mem_name, dbg_ptr - entry->mem_ptr);
			अवरोध;
		पूर्ण जबतक (1);
	पूर्ण
	mwअगरiex_dbg(adapter, MSG, "== mwifiex firmware dump end ==\n");

करोne:
	sdio_release_host(card->func);
पूर्ण

अटल व्योम mwअगरiex_sdio_generic_fw_dump(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	काष्ठा memory_type_mapping *entry = &generic_mem_type_map[0];
	अचिन्हित पूर्णांक reg, reg_start, reg_end;
	u8 start_flag = 0, करोne_flag = 0;
	u8 *dbg_ptr, *end_ptr;
	क्रमागत rdwr_status stat;
	पूर्णांक ret = -1, tries;

	अगर (!card->fw_dump_enh)
		वापस;

	अगर (entry->mem_ptr) अणु
		vमुक्त(entry->mem_ptr);
		entry->mem_ptr = शून्य;
	पूर्ण
	entry->mem_size = 0;

	mwअगरiex_pm_wakeup_card(adapter);
	sdio_claim_host(card->func);

	mwअगरiex_dbg(adapter, MSG, "== mwifiex firmware dump start ==\n");

	stat = mwअगरiex_sdio_rdwr_firmware(adapter, करोne_flag);
	अगर (stat == RDWR_STATUS_FAILURE)
		जाओ करोne;

	reg_start = card->reg->fw_dump_start;
	reg_end = card->reg->fw_dump_end;
	क्रम (reg = reg_start; reg <= reg_end; reg++) अणु
		क्रम (tries = 0; tries < MAX_POLL_TRIES; tries++) अणु
			start_flag = sdio_पढ़ोb(card->func, reg, &ret);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "SDIO read err\n");
				जाओ करोne;
			पूर्ण
			अगर (start_flag == 0)
				अवरोध;
			अगर (tries == MAX_POLL_TRIES) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "FW not ready to dump\n");
				ret = -1;
				जाओ करोne;
			पूर्ण
		पूर्ण
		usleep_range(100, 200);
	पूर्ण

	entry->mem_ptr = vदो_स्मृति(0xf0000 + 1);
	अगर (!entry->mem_ptr) अणु
		ret = -1;
		जाओ करोne;
	पूर्ण
	dbg_ptr = entry->mem_ptr;
	entry->mem_size = 0xf0000;
	end_ptr = dbg_ptr + entry->mem_size;

	करोne_flag = entry->करोne_flag;
	mwअगरiex_dbg(adapter, DUMP,
		    "Start %s output, please wait...\n", entry->mem_name);

	जबतक (true) अणु
		stat = mwअगरiex_sdio_rdwr_firmware(adapter, करोne_flag);
		अगर (stat == RDWR_STATUS_FAILURE)
			जाओ करोne;
		क्रम (reg = reg_start; reg <= reg_end; reg++) अणु
			*dbg_ptr = sdio_पढ़ोb(card->func, reg, &ret);
			अगर (ret) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "SDIO read err\n");
				जाओ करोne;
			पूर्ण
			dbg_ptr++;
			अगर (dbg_ptr >= end_ptr) अणु
				u8 *पंचांगp_ptr;

				पंचांगp_ptr = vदो_स्मृति(entry->mem_size + 0x4000 + 1);
				अगर (!पंचांगp_ptr)
					जाओ करोne;

				स_नकल(पंचांगp_ptr, entry->mem_ptr,
				       entry->mem_size);
				vमुक्त(entry->mem_ptr);
				entry->mem_ptr = पंचांगp_ptr;
				पंचांगp_ptr = शून्य;
				dbg_ptr = entry->mem_ptr + entry->mem_size;
				entry->mem_size += 0x4000;
				end_ptr = entry->mem_ptr + entry->mem_size;
			पूर्ण
		पूर्ण
		अगर (stat == RDWR_STATUS_DONE) अणु
			entry->mem_size = dbg_ptr - entry->mem_ptr;
			mwअगरiex_dbg(adapter, DUMP, "dump %s done size=0x%x\n",
				    entry->mem_name, entry->mem_size);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mwअगरiex_dbg(adapter, MSG, "== mwifiex firmware dump end ==\n");

करोne:
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR, "firmware dump failed\n");
		अगर (entry->mem_ptr) अणु
			vमुक्त(entry->mem_ptr);
			entry->mem_ptr = शून्य;
		पूर्ण
		entry->mem_size = 0;
	पूर्ण
	sdio_release_host(card->func);
पूर्ण

अटल व्योम mwअगरiex_sdio_device_dump_work(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;

	adapter->devdump_data = vzalloc(MWIFIEX_FW_DUMP_SIZE);
	अगर (!adapter->devdump_data) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "vzalloc devdump data failure!\n");
		वापस;
	पूर्ण

	mwअगरiex_drv_info_dump(adapter);
	अगर (card->fw_dump_enh)
		mwअगरiex_sdio_generic_fw_dump(adapter);
	अन्यथा
		mwअगरiex_sdio_fw_dump(adapter);
	mwअगरiex_prepare_fw_dump_info(adapter);
	mwअगरiex_upload_device_dump(adapter);
पूर्ण

अटल व्योम mwअगरiex_sdio_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sdio_mmc_card *card =
		container_of(work, काष्ठा sdio_mmc_card, work);

	अगर (test_and_clear_bit(MWIFIEX_IFACE_WORK_DEVICE_DUMP,
			       &card->work_flags))
		mwअगरiex_sdio_device_dump_work(card->adapter);
	अगर (test_and_clear_bit(MWIFIEX_IFACE_WORK_CARD_RESET,
			       &card->work_flags))
		mwअगरiex_sdio_card_reset_work(card->adapter);
पूर्ण

/* This function resets the card */
अटल व्योम mwअगरiex_sdio_card_reset(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;

	अगर (!test_and_set_bit(MWIFIEX_IFACE_WORK_CARD_RESET, &card->work_flags))
		schedule_work(&card->work);
पूर्ण

/* This function dumps FW inक्रमmation */
अटल व्योम mwअगरiex_sdio_device_dump(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;

	अगर (!test_and_set_bit(MWIFIEX_IFACE_WORK_DEVICE_DUMP,
			      &card->work_flags))
		schedule_work(&card->work);
पूर्ण

/* Function to dump SDIO function रेजिस्टरs and SDIO scratch रेजिस्टरs in हाल
 * of FW crash
 */
अटल पूर्णांक
mwअगरiex_sdio_reg_dump(काष्ठा mwअगरiex_adapter *adapter, अक्षर *drv_buf)
अणु
	अक्षर *p = drv_buf;
	काष्ठा sdio_mmc_card *cardp = adapter->card;
	पूर्णांक ret = 0;
	u8 count, func, data, index = 0, size = 0;
	u8 reg, reg_start, reg_end;
	अक्षर buf[256], *ptr;

	अगर (!p)
		वापस 0;

	mwअगरiex_dbg(adapter, MSG, "SDIO register dump start\n");

	mwअगरiex_pm_wakeup_card(adapter);

	sdio_claim_host(cardp->func);

	क्रम (count = 0; count < 5; count++) अणु
		स_रखो(buf, 0, माप(buf));
		ptr = buf;

		चयन (count) अणु
		हाल 0:
			/* Read the रेजिस्टरs of SDIO function0 */
			func = count;
			reg_start = 0;
			reg_end = 9;
			अवरोध;
		हाल 1:
			/* Read the रेजिस्टरs of SDIO function1 */
			func = count;
			reg_start = cardp->reg->func1_dump_reg_start;
			reg_end = cardp->reg->func1_dump_reg_end;
			अवरोध;
		हाल 2:
			index = 0;
			func = 1;
			reg_start = cardp->reg->func1_spec_reg_table[index++];
			size = cardp->reg->func1_spec_reg_num;
			reg_end = cardp->reg->func1_spec_reg_table[size-1];
			अवरोध;
		शेष:
			/* Read the scratch रेजिस्टरs of SDIO function1 */
			अगर (count == 4)
				mdelay(100);
			func = 1;
			reg_start = cardp->reg->func1_scratch_reg;
			reg_end = reg_start + MWIFIEX_SDIO_SCRATCH_SIZE;
		पूर्ण

		अगर (count != 2)
			ptr += प्र_लिखो(ptr, "SDIO Func%d (%#x-%#x): ",
				       func, reg_start, reg_end);
		अन्यथा
			ptr += प्र_लिखो(ptr, "SDIO Func%d: ", func);

		क्रम (reg = reg_start; reg <= reg_end;) अणु
			अगर (func == 0)
				data = sdio_f0_पढ़ोb(cardp->func, reg, &ret);
			अन्यथा
				data = sdio_पढ़ोb(cardp->func, reg, &ret);

			अगर (count == 2)
				ptr += प्र_लिखो(ptr, "(%#x) ", reg);
			अगर (!ret) अणु
				ptr += प्र_लिखो(ptr, "%02x ", data);
			पूर्ण अन्यथा अणु
				ptr += प्र_लिखो(ptr, "ERR");
				अवरोध;
			पूर्ण

			अगर (count == 2 && reg < reg_end)
				reg = cardp->reg->func1_spec_reg_table[index++];
			अन्यथा
				reg++;
		पूर्ण

		mwअगरiex_dbg(adapter, MSG, "%s\n", buf);
		p += प्र_लिखो(p, "%s\n", buf);
	पूर्ण

	sdio_release_host(cardp->func);

	mwअगरiex_dbg(adapter, MSG, "SDIO register dump end\n");

	वापस p - drv_buf;
पूर्ण

/* sdio device/function initialization, code is extracted
 * from init_अगर handler and रेजिस्टर_dev handler.
 */
अटल व्योम mwअगरiex_sdio_up_dev(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा sdio_mmc_card *card = adapter->card;
	u8 sdio_ireg;

	sdio_claim_host(card->func);
	sdio_enable_func(card->func);
	sdio_set_block_size(card->func, MWIFIEX_SDIO_BLOCK_SIZE);
	sdio_release_host(card->func);

	/* tx_buf_size might be changed to 3584 by firmware during
	 * data transfer, we will reset to शेष size.
	 */
	adapter->tx_buf_size = card->tx_buf_size;

	/* Read the host_पूर्णांक_status_reg क्रम ACK the first पूर्णांकerrupt got
	 * from the bootloader. If we करोn't करो this we get a पूर्णांकerrupt
	 * as soon as we रेजिस्टर the irq.
	 */
	mwअगरiex_पढ़ो_reg(adapter, card->reg->host_पूर्णांक_status_reg, &sdio_ireg);

	mwअगरiex_init_sdio_ioport(adapter);
पूर्ण

अटल काष्ठा mwअगरiex_अगर_ops sdio_ops = अणु
	.init_अगर = mwअगरiex_init_sdio,
	.cleanup_अगर = mwअगरiex_cleanup_sdio,
	.check_fw_status = mwअगरiex_check_fw_status,
	.check_winner_status = mwअगरiex_check_winner_status,
	.prog_fw = mwअगरiex_prog_fw_w_helper,
	.रेजिस्टर_dev = mwअगरiex_रेजिस्टर_dev,
	.unरेजिस्टर_dev = mwअगरiex_unरेजिस्टर_dev,
	.enable_पूर्णांक = mwअगरiex_sdio_enable_host_पूर्णांक,
	.disable_पूर्णांक = mwअगरiex_sdio_disable_host_पूर्णांक,
	.process_पूर्णांक_status = mwअगरiex_process_पूर्णांक_status,
	.host_to_card = mwअगरiex_sdio_host_to_card,
	.wakeup = mwअगरiex_pm_wakeup_card,
	.wakeup_complete = mwअगरiex_pm_wakeup_card_complete,

	/* SDIO specअगरic */
	.update_mp_end_port = mwअगरiex_update_mp_end_port,
	.cleanup_mpa_buf = mwअगरiex_cleanup_mpa_buf,
	.cmdrsp_complete = mwअगरiex_sdio_cmdrsp_complete,
	.event_complete = mwअगरiex_sdio_event_complete,
	.dnld_fw = mwअगरiex_sdio_dnld_fw,
	.card_reset = mwअगरiex_sdio_card_reset,
	.reg_dump = mwअगरiex_sdio_reg_dump,
	.device_dump = mwअगरiex_sdio_device_dump,
	.deaggr_pkt = mwअगरiex_deaggr_sdio_pkt,
	.up_dev = mwअगरiex_sdio_up_dev,
पूर्ण;

module_driver(mwअगरiex_sdio, sdio_रेजिस्टर_driver, sdio_unरेजिस्टर_driver);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell WiFi-Ex SDIO Driver version " SDIO_VERSION);
MODULE_VERSION(SDIO_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_FIRMWARE(SD8786_DEFAULT_FW_NAME);
MODULE_FIRMWARE(SD8787_DEFAULT_FW_NAME);
MODULE_FIRMWARE(SD8797_DEFAULT_FW_NAME);
MODULE_FIRMWARE(SD8897_DEFAULT_FW_NAME);
MODULE_FIRMWARE(SD8887_DEFAULT_FW_NAME);
MODULE_FIRMWARE(SD8977_DEFAULT_FW_NAME);
MODULE_FIRMWARE(SD8987_DEFAULT_FW_NAME);
MODULE_FIRMWARE(SD8997_DEFAULT_FW_NAME);
