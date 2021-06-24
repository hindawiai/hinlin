<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#अगर_अघोषित MSS_INGRESS_REGS_HEADER
#घोषणा MSS_INGRESS_REGS_HEADER

#घोषणा MSS_INGRESS_CTL_REGISTER_ADDR 0x0000800E
#घोषणा MSS_INGRESS_LUT_ADDR_CTL_REGISTER_ADDR 0x00008080
#घोषणा MSS_INGRESS_LUT_CTL_REGISTER_ADDR 0x00008081
#घोषणा MSS_INGRESS_LUT_DATA_CTL_REGISTER_ADDR 0x000080A0

काष्ठा mss_ingress_ctl_रेजिस्टर अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक soft_reset : 1;
			अचिन्हित पूर्णांक operation_poपूर्णांक_to_poपूर्णांक : 1;
			अचिन्हित पूर्णांक create_sci : 1;
			/* Unused  */
			अचिन्हित पूर्णांक mask_लघु_length_error : 1;
			अचिन्हित पूर्णांक drop_kay_packet : 1;
			अचिन्हित पूर्णांक drop_igprc_miss : 1;
			/* Unused  */
			अचिन्हित पूर्णांक check_icv : 1;
			अचिन्हित पूर्णांक clear_global_समय : 1;
			अचिन्हित पूर्णांक clear_count : 1;
			अचिन्हित पूर्णांक high_prio : 1;
			अचिन्हित पूर्णांक हटाओ_sectag : 1;
			अचिन्हित पूर्णांक global_validate_frames : 2;
			अचिन्हित पूर्णांक icv_lsb_8bytes_enabled : 1;
			अचिन्हित पूर्णांक reserved0 : 2;
		पूर्ण bits_0;
		अचिन्हित लघु word_0;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक reserved0 : 16;
		पूर्ण bits_1;
		अचिन्हित लघु word_1;
	पूर्ण;
पूर्ण;

काष्ठा mss_ingress_lut_addr_ctl_रेजिस्टर अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक lut_addr : 9;
			अचिन्हित पूर्णांक reserved0 : 3;
			/* 0x0 : Ingress Pre-Security MAC Control FIlter
			 *       (IGPRCTLF) LUT
			 * 0x1 : Ingress Pre-Security Classअगरication LUT (IGPRC)
			 * 0x2 : Ingress Packet Format (IGPFMT) SAKey LUT
			 * 0x3 : Ingress Packet Format (IGPFMT) SC/SA LUT
			 * 0x4 : Ingress Post-Security Classअगरication LUT
			 *       (IGPOC)
			 * 0x5 : Ingress Post-Security MAC Control Filter
			 *       (IGPOCTLF) LUT
			 * 0x6 : Ingress MIB (IGMIB)
			 */
			अचिन्हित पूर्णांक lut_select : 4;
		पूर्ण bits_0;
		अचिन्हित लघु word_0;
	पूर्ण;
पूर्ण;

काष्ठा mss_ingress_lut_ctl_रेजिस्टर अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक reserved0 : 14;
			अचिन्हित पूर्णांक lut_पढ़ो : 1;
			अचिन्हित पूर्णांक lut_ग_लिखो : 1;
		पूर्ण bits_0;
		अचिन्हित लघु word_0;
	पूर्ण;
पूर्ण;

#पूर्ण_अगर /* MSS_INGRESS_REGS_HEADER */
