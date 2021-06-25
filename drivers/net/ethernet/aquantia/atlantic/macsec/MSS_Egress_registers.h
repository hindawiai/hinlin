<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#अगर_अघोषित MSS_EGRESS_REGS_HEADER
#घोषणा MSS_EGRESS_REGS_HEADER

#घोषणा MSS_EGRESS_CTL_REGISTER_ADDR 0x00005002
#घोषणा MSS_EGRESS_SA_EXPIRED_STATUS_REGISTER_ADDR 0x00005060
#घोषणा MSS_EGRESS_SA_THRESHOLD_EXPIRED_STATUS_REGISTER_ADDR 0x00005062
#घोषणा MSS_EGRESS_LUT_ADDR_CTL_REGISTER_ADDR 0x00005080
#घोषणा MSS_EGRESS_LUT_CTL_REGISTER_ADDR 0x00005081
#घोषणा MSS_EGRESS_LUT_DATA_CTL_REGISTER_ADDR 0x000050A0

काष्ठा mss_egress_ctl_रेजिस्टर अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक soft_reset : 1;
			अचिन्हित पूर्णांक drop_kay_packet : 1;
			अचिन्हित पूर्णांक drop_egprc_lut_miss : 1;
			अचिन्हित पूर्णांक gcm_start : 1;
			अचिन्हित पूर्णांक gcm_test_mode : 1;
			अचिन्हित पूर्णांक unmatched_use_sc_0 : 1;
			अचिन्हित पूर्णांक drop_invalid_sa_sc_packets : 1;
			अचिन्हित पूर्णांक reserved0 : 1;
			/* Should always be set to 0. */
			अचिन्हित पूर्णांक बाह्यal_classअगरication_enable : 1;
			अचिन्हित पूर्णांक icv_lsb_8bytes_enable : 1;
			अचिन्हित पूर्णांक high_prio : 1;
			अचिन्हित पूर्णांक clear_counter : 1;
			अचिन्हित पूर्णांक clear_global_समय : 1;
			अचिन्हित पूर्णांक ethertype_explicit_sectag_lsb : 3;
		पूर्ण bits_0;
		अचिन्हित लघु word_0;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक ethertype_explicit_sectag_msb : 13;
			अचिन्हित पूर्णांक reserved0 : 3;
		पूर्ण bits_1;
		अचिन्हित लघु word_1;
	पूर्ण;
पूर्ण;

काष्ठा mss_egress_lut_addr_ctl_रेजिस्टर अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक lut_addr : 9;
			अचिन्हित पूर्णांक reserved0 : 3;
			/* 0x0 : Egress MAC Control FIlter (CTLF) LUT
			 * 0x1 : Egress Classअगरication LUT
			 * 0x2 : Egress SC/SA LUT
			 * 0x3 : Egress SMIB
			 */
			अचिन्हित पूर्णांक lut_select : 4;
		पूर्ण bits_0;
		अचिन्हित लघु word_0;
	पूर्ण;
पूर्ण;

काष्ठा mss_egress_lut_ctl_रेजिस्टर अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक reserved0 : 14;
			अचिन्हित पूर्णांक lut_पढ़ो : 1;
			अचिन्हित पूर्णांक lut_ग_लिखो : 1;
		पूर्ण bits_0;
		अचिन्हित लघु word_0;
	पूर्ण;
पूर्ण;

#पूर्ण_अगर /* MSS_EGRESS_REGS_HEADER */
