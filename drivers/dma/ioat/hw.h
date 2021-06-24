<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright(c) 2004 - 2009 Intel Corporation. All rights reserved.
 */
#अगर_अघोषित _IOAT_HW_H_
#घोषणा _IOAT_HW_H_

/* PCI Configuration Space Values */
#घोषणा IOAT_MMIO_BAR		0

/* CB device ID's */
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_IVB0	0x0e20
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_IVB1	0x0e21
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_IVB2	0x0e22
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_IVB3	0x0e23
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_IVB4	0x0e24
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_IVB5	0x0e25
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_IVB6	0x0e26
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_IVB7	0x0e27
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_IVB8	0x0e2e
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_IVB9	0x0e2f

#घोषणा PCI_DEVICE_ID_INTEL_IOAT_HSW0	0x2f20
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_HSW1	0x2f21
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_HSW2	0x2f22
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_HSW3	0x2f23
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_HSW4	0x2f24
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_HSW5	0x2f25
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_HSW6	0x2f26
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_HSW7	0x2f27
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_HSW8	0x2f2e
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_HSW9	0x2f2f

#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BWD0	0x0C50
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BWD1	0x0C51
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BWD2	0x0C52
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BWD3	0x0C53

#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDXDE0	0x6f50
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDXDE1	0x6f51
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDXDE2	0x6f52
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDXDE3	0x6f53

#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDX0	0x6f20
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDX1	0x6f21
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDX2	0x6f22
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDX3	0x6f23
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDX4	0x6f24
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDX5	0x6f25
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDX6	0x6f26
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDX7	0x6f27
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDX8	0x6f2e
#घोषणा PCI_DEVICE_ID_INTEL_IOAT_BDX9	0x6f2f

#घोषणा PCI_DEVICE_ID_INTEL_IOAT_SKX	0x2021

#घोषणा PCI_DEVICE_ID_INTEL_IOAT_ICX	0x0b00

#घोषणा IOAT_VER_1_2            0x12    /* Version 1.2 */
#घोषणा IOAT_VER_2_0            0x20    /* Version 2.0 */
#घोषणा IOAT_VER_3_0            0x30    /* Version 3.0 */
#घोषणा IOAT_VER_3_2            0x32    /* Version 3.2 */
#घोषणा IOAT_VER_3_3            0x33    /* Version 3.3 */
#घोषणा IOAT_VER_3_4		0x34	/* Version 3.4 */


पूर्णांक प्रणाली_has_dca_enabled(काष्ठा pci_dev *pdev);

#घोषणा IOAT_DESC_SZ	64

काष्ठा ioat_dma_descriptor अणु
	uपूर्णांक32_t	size;
	जोड़ अणु
		uपूर्णांक32_t ctl;
		काष्ठा अणु
			अचिन्हित पूर्णांक पूर्णांक_en:1;
			अचिन्हित पूर्णांक src_snoop_dis:1;
			अचिन्हित पूर्णांक dest_snoop_dis:1;
			अचिन्हित पूर्णांक compl_ग_लिखो:1;
			अचिन्हित पूर्णांक fence:1;
			अचिन्हित पूर्णांक null:1;
			अचिन्हित पूर्णांक src_brk:1;
			अचिन्हित पूर्णांक dest_brk:1;
			अचिन्हित पूर्णांक bundle:1;
			अचिन्हित पूर्णांक dest_dca:1;
			अचिन्हित पूर्णांक hपूर्णांक:1;
			अचिन्हित पूर्णांक rsvd2:13;
			#घोषणा IOAT_OP_COPY 0x00
			अचिन्हित पूर्णांक op:8;
		पूर्ण ctl_f;
	पूर्ण;
	uपूर्णांक64_t	src_addr;
	uपूर्णांक64_t	dst_addr;
	uपूर्णांक64_t	next;
	uपूर्णांक64_t	rsv1;
	uपूर्णांक64_t	rsv2;
	/* store some driver data in an unused portion of the descriptor */
	जोड़ अणु
		uपूर्णांक64_t	user1;
		uपूर्णांक64_t	tx_cnt;
	पूर्ण;
	uपूर्णांक64_t	user2;
पूर्ण;

काष्ठा ioat_xor_descriptor अणु
	uपूर्णांक32_t	size;
	जोड़ अणु
		uपूर्णांक32_t ctl;
		काष्ठा अणु
			अचिन्हित पूर्णांक पूर्णांक_en:1;
			अचिन्हित पूर्णांक src_snoop_dis:1;
			अचिन्हित पूर्णांक dest_snoop_dis:1;
			अचिन्हित पूर्णांक compl_ग_लिखो:1;
			अचिन्हित पूर्णांक fence:1;
			अचिन्हित पूर्णांक src_cnt:3;
			अचिन्हित पूर्णांक bundle:1;
			अचिन्हित पूर्णांक dest_dca:1;
			अचिन्हित पूर्णांक hपूर्णांक:1;
			अचिन्हित पूर्णांक rsvd:13;
			#घोषणा IOAT_OP_XOR 0x87
			#घोषणा IOAT_OP_XOR_VAL 0x88
			अचिन्हित पूर्णांक op:8;
		पूर्ण ctl_f;
	पूर्ण;
	uपूर्णांक64_t	src_addr;
	uपूर्णांक64_t	dst_addr;
	uपूर्णांक64_t	next;
	uपूर्णांक64_t	src_addr2;
	uपूर्णांक64_t	src_addr3;
	uपूर्णांक64_t	src_addr4;
	uपूर्णांक64_t	src_addr5;
पूर्ण;

काष्ठा ioat_xor_ext_descriptor अणु
	uपूर्णांक64_t	src_addr6;
	uपूर्णांक64_t	src_addr7;
	uपूर्णांक64_t	src_addr8;
	uपूर्णांक64_t	next;
	uपूर्णांक64_t	rsvd[4];
पूर्ण;

काष्ठा ioat_pq_descriptor अणु
	जोड़ अणु
		uपूर्णांक32_t	size;
		uपूर्णांक32_t	dwbes;
		काष्ठा अणु
			अचिन्हित पूर्णांक rsvd:25;
			अचिन्हित पूर्णांक p_val_err:1;
			अचिन्हित पूर्णांक q_val_err:1;
			अचिन्हित पूर्णांक rsvd1:4;
			अचिन्हित पूर्णांक wbes:1;
		पूर्ण dwbes_f;
	पूर्ण;
	जोड़ अणु
		uपूर्णांक32_t ctl;
		काष्ठा अणु
			अचिन्हित पूर्णांक पूर्णांक_en:1;
			अचिन्हित पूर्णांक src_snoop_dis:1;
			अचिन्हित पूर्णांक dest_snoop_dis:1;
			अचिन्हित पूर्णांक compl_ग_लिखो:1;
			अचिन्हित पूर्णांक fence:1;
			अचिन्हित पूर्णांक src_cnt:3;
			अचिन्हित पूर्णांक bundle:1;
			अचिन्हित पूर्णांक dest_dca:1;
			अचिन्हित पूर्णांक hपूर्णांक:1;
			अचिन्हित पूर्णांक p_disable:1;
			अचिन्हित पूर्णांक q_disable:1;
			अचिन्हित पूर्णांक rsvd2:2;
			अचिन्हित पूर्णांक wb_en:1;
			अचिन्हित पूर्णांक prl_en:1;
			अचिन्हित पूर्णांक rsvd3:7;
			#घोषणा IOAT_OP_PQ 0x89
			#घोषणा IOAT_OP_PQ_VAL 0x8a
			#घोषणा IOAT_OP_PQ_16S 0xa0
			#घोषणा IOAT_OP_PQ_VAL_16S 0xa1
			अचिन्हित पूर्णांक op:8;
		पूर्ण ctl_f;
	पूर्ण;
	uपूर्णांक64_t	src_addr;
	uपूर्णांक64_t	p_addr;
	uपूर्णांक64_t	next;
	uपूर्णांक64_t	src_addr2;
	जोड़ अणु
		uपूर्णांक64_t	src_addr3;
		uपूर्णांक64_t	sed_addr;
	पूर्ण;
	uपूर्णांक8_t		coef[8];
	uपूर्णांक64_t	q_addr;
पूर्ण;

काष्ठा ioat_pq_ext_descriptor अणु
	uपूर्णांक64_t	src_addr4;
	uपूर्णांक64_t	src_addr5;
	uपूर्णांक64_t	src_addr6;
	uपूर्णांक64_t	next;
	uपूर्णांक64_t	src_addr7;
	uपूर्णांक64_t	src_addr8;
	uपूर्णांक64_t	rsvd[2];
पूर्ण;

काष्ठा ioat_pq_update_descriptor अणु
	uपूर्णांक32_t	size;
	जोड़ अणु
		uपूर्णांक32_t ctl;
		काष्ठा अणु
			अचिन्हित पूर्णांक पूर्णांक_en:1;
			अचिन्हित पूर्णांक src_snoop_dis:1;
			अचिन्हित पूर्णांक dest_snoop_dis:1;
			अचिन्हित पूर्णांक compl_ग_लिखो:1;
			अचिन्हित पूर्णांक fence:1;
			अचिन्हित पूर्णांक src_cnt:3;
			अचिन्हित पूर्णांक bundle:1;
			अचिन्हित पूर्णांक dest_dca:1;
			अचिन्हित पूर्णांक hपूर्णांक:1;
			अचिन्हित पूर्णांक p_disable:1;
			अचिन्हित पूर्णांक q_disable:1;
			अचिन्हित पूर्णांक rsvd:3;
			अचिन्हित पूर्णांक coef:8;
			#घोषणा IOAT_OP_PQ_UP 0x8b
			अचिन्हित पूर्णांक op:8;
		पूर्ण ctl_f;
	पूर्ण;
	uपूर्णांक64_t	src_addr;
	uपूर्णांक64_t	p_addr;
	uपूर्णांक64_t	next;
	uपूर्णांक64_t	src_addr2;
	uपूर्णांक64_t	p_src;
	uपूर्णांक64_t	q_src;
	uपूर्णांक64_t	q_addr;
पूर्ण;

काष्ठा ioat_raw_descriptor अणु
	uपूर्णांक64_t	field[8];
पूर्ण;

काष्ठा ioat_pq16a_descriptor अणु
	uपूर्णांक8_t coef[8];
	uपूर्णांक64_t src_addr3;
	uपूर्णांक64_t src_addr4;
	uपूर्णांक64_t src_addr5;
	uपूर्णांक64_t src_addr6;
	uपूर्णांक64_t src_addr7;
	uपूर्णांक64_t src_addr8;
	uपूर्णांक64_t src_addr9;
पूर्ण;

काष्ठा ioat_pq16b_descriptor अणु
	uपूर्णांक64_t src_addr10;
	uपूर्णांक64_t src_addr11;
	uपूर्णांक64_t src_addr12;
	uपूर्णांक64_t src_addr13;
	uपूर्णांक64_t src_addr14;
	uपूर्णांक64_t src_addr15;
	uपूर्णांक64_t src_addr16;
	uपूर्णांक64_t rsvd;
पूर्ण;

जोड़ ioat_sed_pq_descriptor अणु
	काष्ठा ioat_pq16a_descriptor a;
	काष्ठा ioat_pq16b_descriptor b;
पूर्ण;

#घोषणा SED_SIZE	64

काष्ठा ioat_sed_raw_descriptor अणु
	uपूर्णांक64_t	a[8];
	uपूर्णांक64_t	b[8];
	uपूर्णांक64_t	c[8];
पूर्ण;

#पूर्ण_अगर
