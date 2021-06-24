<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_PCI_INSN_H
#घोषणा _ASM_S390_PCI_INSN_H

#समावेश <linux/jump_label.h>

/* Load/Store status codes */
#घोषणा ZPCI_PCI_ST_FUNC_NOT_ENABLED		4
#घोषणा ZPCI_PCI_ST_FUNC_IN_ERR			8
#घोषणा ZPCI_PCI_ST_BLOCKED			12
#घोषणा ZPCI_PCI_ST_INSUF_RES			16
#घोषणा ZPCI_PCI_ST_INVAL_AS			20
#घोषणा ZPCI_PCI_ST_FUNC_ALREADY_ENABLED	24
#घोषणा ZPCI_PCI_ST_DMA_AS_NOT_ENABLED		28
#घोषणा ZPCI_PCI_ST_2ND_OP_IN_INV_AS		36
#घोषणा ZPCI_PCI_ST_FUNC_NOT_AVAIL		40
#घोषणा ZPCI_PCI_ST_ALREADY_IN_RQ_STATE		44

/* Load/Store वापस codes */
#घोषणा ZPCI_PCI_LS_OK				0
#घोषणा ZPCI_PCI_LS_ERR				1
#घोषणा ZPCI_PCI_LS_BUSY			2
#घोषणा ZPCI_PCI_LS_INVAL_HANDLE		3

/* Load/Store address space identअगरiers */
#घोषणा ZPCI_PCIAS_MEMIO_0			0
#घोषणा ZPCI_PCIAS_MEMIO_1			1
#घोषणा ZPCI_PCIAS_MEMIO_2			2
#घोषणा ZPCI_PCIAS_MEMIO_3			3
#घोषणा ZPCI_PCIAS_MEMIO_4			4
#घोषणा ZPCI_PCIAS_MEMIO_5			5
#घोषणा ZPCI_PCIAS_CFGSPC			15

/* Modअगरy PCI Function Controls */
#घोषणा ZPCI_MOD_FC_REG_INT	2
#घोषणा ZPCI_MOD_FC_DEREG_INT	3
#घोषणा ZPCI_MOD_FC_REG_IOAT	4
#घोषणा ZPCI_MOD_FC_DEREG_IOAT	5
#घोषणा ZPCI_MOD_FC_REREG_IOAT	6
#घोषणा ZPCI_MOD_FC_RESET_ERROR	7
#घोषणा ZPCI_MOD_FC_RESET_BLOCK	9
#घोषणा ZPCI_MOD_FC_SET_MEASURE	10
#घोषणा ZPCI_MOD_FC_REG_INT_D	16
#घोषणा ZPCI_MOD_FC_DEREG_INT_D	17

/* FIB function controls */
#घोषणा ZPCI_FIB_FC_ENABLED	0x80
#घोषणा ZPCI_FIB_FC_ERROR	0x40
#घोषणा ZPCI_FIB_FC_LS_BLOCKED	0x20
#घोषणा ZPCI_FIB_FC_DMAAS_REG	0x10

/* FIB function controls */
#घोषणा ZPCI_FIB_FC_ENABLED	0x80
#घोषणा ZPCI_FIB_FC_ERROR	0x40
#घोषणा ZPCI_FIB_FC_LS_BLOCKED	0x20
#घोषणा ZPCI_FIB_FC_DMAAS_REG	0x10

काष्ठा zpci_fib_fmt0 अणु
	u32		:  1;
	u32 isc		:  3;	/* Interrupt subclass */
	u32 noi		: 12;	/* Number of पूर्णांकerrupts */
	u32		:  2;
	u32 aibvo	:  6;	/* Adapter पूर्णांकerrupt bit vector offset */
	u32 sum		:  1;	/* Adapter पूर्णांक summary bit enabled */
	u32		:  1;
	u32 aisbo	:  6;	/* Adapter पूर्णांक summary bit offset */
	u32		: 32;
	u64 aibv;		/* Adapter पूर्णांक bit vector address */
	u64 aisb;		/* Adapter पूर्णांक summary bit address */
पूर्ण;

काष्ठा zpci_fib_fmt1 अणु
	u32		:  4;
	u32 noi		: 12;
	u32		: 16;
	u32 dibvo	: 16;
	u32		: 16;
	u64		: 64;
	u64		: 64;
पूर्ण;

/* Function Inक्रमmation Block */
काष्ठा zpci_fib अणु
	u32 fmt		:  8;	/* क्रमmat */
	u32		: 24;
	u32		: 32;
	u8 fc;			/* function controls */
	u64		: 56;
	u64 pba;		/* PCI base address */
	u64 pal;		/* PCI address limit */
	u64 iota;		/* I/O Translation Anchor */
	जोड़ अणु
		काष्ठा zpci_fib_fmt0 fmt0;
		काष्ठा zpci_fib_fmt1 fmt1;
	पूर्ण;
	u64 fmb_addr;		/* Function measurement block address and key */
	u32		: 32;
	u32 gd;
पूर्ण __packed __aligned(8);

/* directed पूर्णांकerruption inक्रमmation block */
काष्ठा zpci_diib अणु
	u32 : 1;
	u32 isc : 3;
	u32 : 28;
	u16 : 16;
	u16 nr_cpus;
	u64 disb_addr;
	u64 : 64;
	u64 : 64;
पूर्ण __packed __aligned(8);

/* cpu directed पूर्णांकerruption inक्रमmation block */
काष्ठा zpci_cdiib अणु
	u64 : 64;
	u64 dibv_addr;
	u64 : 64;
	u64 : 64;
	u64 : 64;
पूर्ण __packed __aligned(8);

जोड़ zpci_sic_iib अणु
	काष्ठा zpci_diib diib;
	काष्ठा zpci_cdiib cdiib;
पूर्ण;

DECLARE_STATIC_KEY_FALSE(have_mio);

u8 zpci_mod_fc(u64 req, काष्ठा zpci_fib *fib, u8 *status);
पूर्णांक zpci_refresh_trans(u64 fn, u64 addr, u64 range);
पूर्णांक __zpci_load(u64 *data, u64 req, u64 offset);
पूर्णांक zpci_load(u64 *data, स्थिर अस्थिर व्योम __iomem *addr, अचिन्हित दीर्घ len);
पूर्णांक __zpci_store(u64 data, u64 req, u64 offset);
पूर्णांक zpci_store(स्थिर अस्थिर व्योम __iomem *addr, u64 data, अचिन्हित दीर्घ len);
पूर्णांक __zpci_store_block(स्थिर u64 *data, u64 req, u64 offset);
व्योम zpci_barrier(व्योम);
पूर्णांक __zpci_set_irq_ctrl(u16 ctl, u8 isc, जोड़ zpci_sic_iib *iib);

अटल अंतरभूत पूर्णांक zpci_set_irq_ctrl(u16 ctl, u8 isc)
अणु
	जोड़ zpci_sic_iib iib = अणुअणु0पूर्णपूर्ण;

	वापस __zpci_set_irq_ctrl(ctl, isc, &iib);
पूर्ण

#पूर्ण_अगर
