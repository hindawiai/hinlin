<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Linux driver क्रम digital TV devices equipped with B2C2 FlexcopII(b)/III
 * flexcop-reg.h - रेजिस्टर असलtraction क्रम FlexCopII, FlexCopIIb and FlexCopIII
 * see flexcop.c क्रम copyright inक्रमmation
 */
#अगर_अघोषित __FLEXCOP_REG_H__
#घोषणा __FLEXCOP_REG_H__

प्रकार क्रमागत अणु
	FLEXCOP_UNK = 0,
	FLEXCOP_II,
	FLEXCOP_IIB,
	FLEXCOP_III,
पूर्ण flexcop_revision_t;

प्रकार क्रमागत अणु
	FC_UNK = 0,
	FC_CABLE,
	FC_AIR_DVBT,
	FC_AIR_ATSC1,
	FC_AIR_ATSC2,
	FC_AIR_ATSC3,
	FC_SKY_REV23,
	FC_SKY_REV26,
	FC_SKY_REV27,
	FC_SKY_REV28,
	FC_SKYS2_REV33,
पूर्ण flexcop_device_type_t;

प्रकार क्रमागत अणु
	FC_USB = 0,
	FC_PCI,
पूर्ण flexcop_bus_t;

/* FlexCop IBI Registers */
#अगर defined(__LITTLE_ENDIAN)
#समावेश "flexcop_ibi_value_le.h"
#अन्यथा
#अगर defined(__BIG_ENDIAN)
#समावेश "flexcop_ibi_value_be.h"
#अन्यथा
#त्रुटि no endian defined
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा fc_data_Tag_ID_DVB  0x3e
#घोषणा fc_data_Tag_ID_ATSC 0x3f
#घोषणा fc_data_Tag_ID_IDSB 0x8b

#घोषणा fc_key_code_शेष 0x1
#घोषणा fc_key_code_even    0x2
#घोषणा fc_key_code_odd     0x3

बाह्य flexcop_ibi_value ibi_zero;

प्रकार क्रमागत अणु
	FC_I2C_PORT_DEMOD  = 1,
	FC_I2C_PORT_EEPROM = 2,
	FC_I2C_PORT_TUNER  = 3,
पूर्ण flexcop_i2c_port_t;

प्रकार क्रमागत अणु
	FC_WRITE = 0,
	FC_READ  = 1,
पूर्ण flexcop_access_op_t;

प्रकार क्रमागत अणु
	FC_SRAM_DEST_NET   = 1,
	FC_SRAM_DEST_CAI   = 2,
	FC_SRAM_DEST_CAO   = 4,
	FC_SRAM_DEST_MEDIA = 8
पूर्ण flexcop_sram_dest_t;

प्रकार क्रमागत अणु
	FC_SRAM_DEST_TARGET_WAN_USB = 0,
	FC_SRAM_DEST_TARGET_DMA1    = 1,
	FC_SRAM_DEST_TARGET_DMA2    = 2,
	FC_SRAM_DEST_TARGET_FC3_CA  = 3
पूर्ण flexcop_sram_dest_target_t;

प्रकार क्रमागत अणु
	FC_SRAM_2_32KB  = 0, /*  64KB */
	FC_SRAM_1_32KB  = 1, /*  32KB - शेष fow FCII */
	FC_SRAM_1_128KB = 2, /* 128KB */
	FC_SRAM_1_48KB  = 3, /*  48KB - शेष क्रम FCIII */
पूर्ण flexcop_sram_type_t;

प्रकार क्रमागत अणु
	FC_WAN_SPEED_4MBITS  = 0,
	FC_WAN_SPEED_8MBITS  = 1,
	FC_WAN_SPEED_12MBITS = 2,
	FC_WAN_SPEED_16MBITS = 3,
पूर्ण flexcop_wan_speed_t;

प्रकार क्रमागत अणु
	FC_DMA_1 = 1,
	FC_DMA_2 = 2,
पूर्ण flexcop_dma_index_t;

प्रकार क्रमागत अणु
	FC_DMA_SUBADDR_0 = 1,
	FC_DMA_SUBADDR_1 = 2,
पूर्ण flexcop_dma_addr_index_t;

/* names of the particular रेजिस्टरs */
प्रकार क्रमागत अणु
	dma1_000            = 0x000,
	dma1_004            = 0x004,
	dma1_008            = 0x008,
	dma1_00c            = 0x00c,
	dma2_010            = 0x010,
	dma2_014            = 0x014,
	dma2_018            = 0x018,
	dma2_01c            = 0x01c,

	tw_sm_c_100         = 0x100,
	tw_sm_c_104         = 0x104,
	tw_sm_c_108         = 0x108,
	tw_sm_c_10c         = 0x10c,
	tw_sm_c_110         = 0x110,

	lnb_चयन_freq_200 = 0x200,
	misc_204            = 0x204,
	ctrl_208            = 0x208,
	irq_20c             = 0x20c,
	sw_reset_210        = 0x210,
	misc_214            = 0x214,
	mbox_v8_to_host_218 = 0x218,
	mbox_host_to_v8_21c = 0x21c,

	pid_filter_300      = 0x300,
	pid_filter_304      = 0x304,
	pid_filter_308      = 0x308,
	pid_filter_30c      = 0x30c,
	index_reg_310       = 0x310,
	pid_n_reg_314       = 0x314,
	mac_low_reg_318     = 0x318,
	mac_high_reg_31c    = 0x31c,

	data_tag_400        = 0x400,
	card_id_408         = 0x408,
	card_id_40c         = 0x40c,
	mac_address_418     = 0x418,
	mac_address_41c     = 0x41c,

	ci_600              = 0x600,
	pi_604              = 0x604,
	pi_608              = 0x608,
	dvb_reg_60c         = 0x60c,

	sram_ctrl_reg_700   = 0x700,
	net_buf_reg_704     = 0x704,
	cai_buf_reg_708     = 0x708,
	cao_buf_reg_70c     = 0x70c,
	media_buf_reg_710   = 0x710,
	sram_dest_reg_714   = 0x714,
	net_buf_reg_718     = 0x718,
	wan_ctrl_reg_71c    = 0x71c,
पूर्ण flexcop_ibi_रेजिस्टर;

#घोषणा flexcop_set_ibi_value(reg,attr,val) अणु \
	flexcop_ibi_value v = fc->पढ़ो_ibi_reg(fc,reg); \
	v.reg.attr = val; \
	fc->ग_लिखो_ibi_reg(fc,reg,v); \
पूर्ण

#पूर्ण_अगर
