<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2006 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Authors: 	Shlomi Gridish <gridish@मुक्तscale.com>
 * 		Li Yang <leoli@मुक्तscale.com>
 *
 * Description:
 * QUICC Engine (QE) बाह्यal definitions and काष्ठाure.
 */
#अगर_अघोषित _ASM_POWERPC_QE_H
#घोषणा _ASM_POWERPC_QE_H
#अगर_घोषित __KERNEL__

#समावेश <linux/compiler.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <soc/fsl/cpm.h>
#समावेश <soc/fsl/qe/immap_qe.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/types.h>

#घोषणा QE_NUM_OF_SNUM	256	/* There are 256 serial number in QE */
#घोषणा QE_NUM_OF_BRGS	16
#घोषणा QE_NUM_OF_PORTS	1024

/* Clocks and BRGs */
क्रमागत qe_घड़ी अणु
	QE_CLK_NONE = 0,
	QE_BRG1,		/* Baud Rate Generator 1 */
	QE_BRG2,		/* Baud Rate Generator 2 */
	QE_BRG3,		/* Baud Rate Generator 3 */
	QE_BRG4,		/* Baud Rate Generator 4 */
	QE_BRG5,		/* Baud Rate Generator 5 */
	QE_BRG6,		/* Baud Rate Generator 6 */
	QE_BRG7,		/* Baud Rate Generator 7 */
	QE_BRG8,		/* Baud Rate Generator 8 */
	QE_BRG9,		/* Baud Rate Generator 9 */
	QE_BRG10,		/* Baud Rate Generator 10 */
	QE_BRG11,		/* Baud Rate Generator 11 */
	QE_BRG12,		/* Baud Rate Generator 12 */
	QE_BRG13,		/* Baud Rate Generator 13 */
	QE_BRG14,		/* Baud Rate Generator 14 */
	QE_BRG15,		/* Baud Rate Generator 15 */
	QE_BRG16,		/* Baud Rate Generator 16 */
	QE_CLK1,		/* Clock 1 */
	QE_CLK2,		/* Clock 2 */
	QE_CLK3,		/* Clock 3 */
	QE_CLK4,		/* Clock 4 */
	QE_CLK5,		/* Clock 5 */
	QE_CLK6,		/* Clock 6 */
	QE_CLK7,		/* Clock 7 */
	QE_CLK8,		/* Clock 8 */
	QE_CLK9,		/* Clock 9 */
	QE_CLK10,		/* Clock 10 */
	QE_CLK11,		/* Clock 11 */
	QE_CLK12,		/* Clock 12 */
	QE_CLK13,		/* Clock 13 */
	QE_CLK14,		/* Clock 14 */
	QE_CLK15,		/* Clock 15 */
	QE_CLK16,		/* Clock 16 */
	QE_CLK17,		/* Clock 17 */
	QE_CLK18,		/* Clock 18 */
	QE_CLK19,		/* Clock 19 */
	QE_CLK20,		/* Clock 20 */
	QE_CLK21,		/* Clock 21 */
	QE_CLK22,		/* Clock 22 */
	QE_CLK23,		/* Clock 23 */
	QE_CLK24,		/* Clock 24 */
	QE_RSYNC_PIN,		/* RSYNC from pin */
	QE_TSYNC_PIN,		/* TSYNC from pin */
	QE_CLK_DUMMY
पूर्ण;

अटल अंतरभूत bool qe_घड़ी_is_brg(क्रमागत qe_घड़ी clk)
अणु
	वापस clk >= QE_BRG1 && clk <= QE_BRG16;
पूर्ण

बाह्य spinlock_t cmxgcr_lock;

/* Export QE common operations */
#अगर_घोषित CONFIG_QUICC_ENGINE
बाह्य व्योम qe_reset(व्योम);
#अन्यथा
अटल अंतरभूत व्योम qe_reset(व्योम) अणुपूर्ण
#पूर्ण_अगर

पूर्णांक cpm_muram_init(व्योम);

#अगर defined(CONFIG_CPM) || defined(CONFIG_QUICC_ENGINE)
s32 cpm_muram_alloc(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align);
व्योम cpm_muram_मुक्त(s32 offset);
s32 cpm_muram_alloc_fixed(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size);
व्योम __iomem *cpm_muram_addr(अचिन्हित दीर्घ offset);
अचिन्हित दीर्घ cpm_muram_offset(स्थिर व्योम __iomem *addr);
dma_addr_t cpm_muram_dma(व्योम __iomem *addr);
व्योम cpm_muram_मुक्त_addr(स्थिर व्योम __iomem *addr);
#अन्यथा
अटल अंतरभूत s32 cpm_muram_alloc(अचिन्हित दीर्घ size,
				  अचिन्हित दीर्घ align)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम cpm_muram_मुक्त(s32 offset)
अणु
पूर्ण

अटल अंतरभूत s32 cpm_muram_alloc_fixed(अचिन्हित दीर्घ offset,
					अचिन्हित दीर्घ size)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम __iomem *cpm_muram_addr(अचिन्हित दीर्घ offset)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cpm_muram_offset(स्थिर व्योम __iomem *addr)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत dma_addr_t cpm_muram_dma(व्योम __iomem *addr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम cpm_muram_मुक्त_addr(स्थिर व्योम __iomem *addr)
अणु
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_CPM) || defined(CONFIG_QUICC_ENGINE) */

/* QE PIO */
#घोषणा QE_PIO_PINS 32

काष्ठा qe_pio_regs अणु
	__be32	cpodr;		/* Open drain रेजिस्टर */
	__be32	cpdata;		/* Data रेजिस्टर */
	__be32	cpdir1;		/* Direction रेजिस्टर */
	__be32	cpdir2;		/* Direction रेजिस्टर */
	__be32	cppar1;		/* Pin assignment रेजिस्टर */
	__be32	cppar2;		/* Pin assignment रेजिस्टर */
#अगर_घोषित CONFIG_PPC_85xx
	u8	pad[8];
#पूर्ण_अगर
पूर्ण;

#घोषणा QE_PIO_सूची_IN	2
#घोषणा QE_PIO_सूची_OUT	1
बाह्य व्योम __par_io_config_pin(काष्ठा qe_pio_regs __iomem *par_io, u8 pin,
				पूर्णांक dir, पूर्णांक खोलो_drain, पूर्णांक assignment,
				पूर्णांक has_irq);
#अगर_घोषित CONFIG_QUICC_ENGINE
बाह्य पूर्णांक par_io_init(काष्ठा device_node *np);
बाह्य पूर्णांक par_io_of_config(काष्ठा device_node *np);
बाह्य पूर्णांक par_io_config_pin(u8 port, u8 pin, पूर्णांक dir, पूर्णांक खोलो_drain,
			     पूर्णांक assignment, पूर्णांक has_irq);
बाह्य पूर्णांक par_io_data_set(u8 port, u8 pin, u8 val);
#अन्यथा
अटल अंतरभूत पूर्णांक par_io_init(काष्ठा device_node *np) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत पूर्णांक par_io_of_config(काष्ठा device_node *np) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत पूर्णांक par_io_config_pin(u8 port, u8 pin, पूर्णांक dir, पूर्णांक खोलो_drain,
		पूर्णांक assignment, पूर्णांक has_irq) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत पूर्णांक par_io_data_set(u8 port, u8 pin, u8 val) अणु वापस -ENOSYS; पूर्ण
#पूर्ण_अगर /* CONFIG_QUICC_ENGINE */

/*
 * Pin multiplexing functions.
 */
काष्ठा qe_pin;
#अगर_घोषित CONFIG_QE_GPIO
बाह्य काष्ठा qe_pin *qe_pin_request(काष्ठा device_node *np, पूर्णांक index);
बाह्य व्योम qe_pin_मुक्त(काष्ठा qe_pin *qe_pin);
बाह्य व्योम qe_pin_set_gpio(काष्ठा qe_pin *qe_pin);
बाह्य व्योम qe_pin_set_dedicated(काष्ठा qe_pin *pin);
#अन्यथा
अटल अंतरभूत काष्ठा qe_pin *qe_pin_request(काष्ठा device_node *np, पूर्णांक index)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण
अटल अंतरभूत व्योम qe_pin_मुक्त(काष्ठा qe_pin *qe_pin) अणुपूर्ण
अटल अंतरभूत व्योम qe_pin_set_gpio(काष्ठा qe_pin *qe_pin) अणुपूर्ण
अटल अंतरभूत व्योम qe_pin_set_dedicated(काष्ठा qe_pin *pin) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_QE_GPIO */

#अगर_घोषित CONFIG_QUICC_ENGINE
पूर्णांक qe_issue_cmd(u32 cmd, u32 device, u8 mcn_protocol, u32 cmd_input);
#अन्यथा
अटल अंतरभूत पूर्णांक qe_issue_cmd(u32 cmd, u32 device, u8 mcn_protocol,
			       u32 cmd_input)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर /* CONFIG_QUICC_ENGINE */

/* QE पूर्णांकernal API */
क्रमागत qe_घड़ी qe_घड़ी_source(स्थिर अक्षर *source);
अचिन्हित पूर्णांक qe_get_brg_clk(व्योम);
पूर्णांक qe_setbrg(क्रमागत qe_घड़ी brg, अचिन्हित पूर्णांक rate, अचिन्हित पूर्णांक multiplier);
पूर्णांक qe_get_snum(व्योम);
व्योम qe_put_snum(u8 snum);
अचिन्हित पूर्णांक qe_get_num_of_risc(व्योम);
अचिन्हित पूर्णांक qe_get_num_of_snums(व्योम);

अटल अंतरभूत पूर्णांक qe_alive_during_sleep(व्योम)
अणु
	/*
	 * MPC8568E reference manual says:
	 *
	 * "...घातer करोwn sequence रुकोs क्रम all I/O पूर्णांकerfaces to become idle.
	 *  In some applications this may happen eventually without actively
	 *  shutting करोwn पूर्णांकerfaces, but most likely, software will have to
	 *  take steps to shut करोwn the eTSEC, QUICC Engine Block, and PCI
	 *  पूर्णांकerfaces beक्रमe issuing the command (either the ग_लिखो to the core
	 *  MSR[WE] as described above or writing to POWMGTCSR) to put the
	 *  device पूर्णांकo sleep state."
	 *
	 * MPC8569E reference manual has a similar paragraph.
	 */
#अगर_घोषित CONFIG_PPC_85xx
	वापस 0;
#अन्यथा
	वापस 1;
#पूर्ण_अगर
पूर्ण

/* we actually use cpm_muram implementation, define this क्रम convenience */
#घोषणा qe_muram_init cpm_muram_init
#घोषणा qe_muram_alloc cpm_muram_alloc
#घोषणा qe_muram_alloc_fixed cpm_muram_alloc_fixed
#घोषणा qe_muram_मुक्त cpm_muram_मुक्त
#घोषणा qe_muram_addr cpm_muram_addr
#घोषणा qe_muram_offset cpm_muram_offset
#घोषणा qe_muram_dma cpm_muram_dma
#घोषणा qe_muram_मुक्त_addr cpm_muram_मुक्त_addr

#घोषणा qe_setbits_be32(_addr, _v) ioग_लिखो32be(ioपढ़ो32be(_addr) |  (_v), (_addr))
#घोषणा qe_clrbits_be32(_addr, _v) ioग_लिखो32be(ioपढ़ो32be(_addr) & ~(_v), (_addr))

#घोषणा qe_setbits_be16(_addr, _v) ioग_लिखो16be(ioपढ़ो16be(_addr) |  (_v), (_addr))
#घोषणा qe_clrbits_be16(_addr, _v) ioग_लिखो16be(ioपढ़ो16be(_addr) & ~(_v), (_addr))

#घोषणा qe_setbits_8(_addr, _v) ioग_लिखो8(ioपढ़ो8(_addr) |  (_v), (_addr))
#घोषणा qe_clrbits_8(_addr, _v) ioग_लिखो8(ioपढ़ो8(_addr) & ~(_v), (_addr))

#घोषणा qe_clrsetbits_be32(addr, clear, set) \
	ioग_लिखो32be((ioपढ़ो32be(addr) & ~(clear)) | (set), (addr))
#घोषणा qe_clrsetbits_be16(addr, clear, set) \
	ioग_लिखो16be((ioपढ़ो16be(addr) & ~(clear)) | (set), (addr))
#घोषणा qe_clrsetbits_8(addr, clear, set) \
	ioग_लिखो8((ioपढ़ो8(addr) & ~(clear)) | (set), (addr))

/* Structure that defines QE firmware binary files.
 *
 * See Documentation/घातerpc/qe_firmware.rst क्रम a description of these
 * fields.
 */
काष्ठा qe_firmware अणु
	काष्ठा qe_header अणु
		__be32 length;  /* Length of the entire काष्ठाure, in bytes */
		u8 magic[3];    /* Set to अणु 'Q', 'E', 'F' पूर्ण */
		u8 version;     /* Version of this layout. First ver is '1' */
	पूर्ण header;
	u8 id[62];      /* Null-terminated identअगरier string */
	u8 split;	/* 0 = shared I-RAM, 1 = split I-RAM */
	u8 count;       /* Number of microcode[] काष्ठाures */
	काष्ठा अणु
		__be16 model;   	/* The SOC model  */
		u8 major;       	/* The SOC revision major */
		u8 minor;       	/* The SOC revision minor */
	पूर्ण __attribute__ ((packed)) soc;
	u8 padding[4];			/* Reserved, क्रम alignment */
	__be64 extended_modes;		/* Extended modes */
	__be32 vtraps[8];		/* Virtual trap addresses */
	u8 reserved[4];			/* Reserved, क्रम future expansion */
	काष्ठा qe_microcode अणु
		u8 id[32];      	/* Null-terminated identअगरier */
		__be32 traps[16];       /* Trap addresses, 0 == ignore */
		__be32 eccr;    	/* The value क्रम the ECCR रेजिस्टर */
		__be32 iram_offset;     /* Offset पूर्णांकo I-RAM क्रम the code */
		__be32 count;   	/* Number of 32-bit words of the code */
		__be32 code_offset;     /* Offset of the actual microcode */
		u8 major;       	/* The microcode version major */
		u8 minor;       	/* The microcode version minor */
		u8 revision;		/* The microcode version revision */
		u8 padding;		/* Reserved, क्रम alignment */
		u8 reserved[4];		/* Reserved, क्रम future expansion */
	पूर्ण __packed microcode[];
	/* All microcode binaries should be located here */
	/* CRC32 should be located here, after the microcode binaries */
पूर्ण __attribute__ ((packed));

काष्ठा qe_firmware_info अणु
	अक्षर id[64];		/* Firmware name */
	u32 vtraps[8];		/* Virtual trap addresses */
	u64 extended_modes;	/* Extended modes */
पूर्ण;

#अगर_घोषित CONFIG_QUICC_ENGINE
/* Upload a firmware to the QE */
पूर्णांक qe_upload_firmware(स्थिर काष्ठा qe_firmware *firmware);
#अन्यथा
अटल अंतरभूत पूर्णांक qe_upload_firmware(स्थिर काष्ठा qe_firmware *firmware)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर /* CONFIG_QUICC_ENGINE */

/* Obtain inक्रमmation on the uploaded firmware */
काष्ठा qe_firmware_info *qe_get_firmware_info(व्योम);

/* QE USB */
पूर्णांक qe_usb_घड़ी_set(क्रमागत qe_घड़ी clk, पूर्णांक rate);

/* Buffer descriptors */
काष्ठा qe_bd अणु
	__be16 status;
	__be16 length;
	__be32 buf;
पूर्ण __attribute__ ((packed));

#घोषणा BD_STATUS_MASK	0xffff0000
#घोषणा BD_LENGTH_MASK	0x0000ffff

/* Alignment */
#घोषणा QE_INTR_TABLE_ALIGN	16	/* ??? */
#घोषणा QE_ALIGNMENT_OF_BD	8
#घोषणा QE_ALIGNMENT_OF_PRAM	64

/* RISC allocation */
#घोषणा QE_RISC_ALLOCATION_RISC1	0x1  /* RISC 1 */
#घोषणा QE_RISC_ALLOCATION_RISC2	0x2  /* RISC 2 */
#घोषणा QE_RISC_ALLOCATION_RISC3	0x4  /* RISC 3 */
#घोषणा QE_RISC_ALLOCATION_RISC4	0x8  /* RISC 4 */
#घोषणा QE_RISC_ALLOCATION_RISC1_AND_RISC2	(QE_RISC_ALLOCATION_RISC1 | \
						 QE_RISC_ALLOCATION_RISC2)
#घोषणा QE_RISC_ALLOCATION_FOUR_RISCS	(QE_RISC_ALLOCATION_RISC1 | \
					 QE_RISC_ALLOCATION_RISC2 | \
					 QE_RISC_ALLOCATION_RISC3 | \
					 QE_RISC_ALLOCATION_RISC4)

/* QE extended filtering Table Lookup Key Size */
क्रमागत qe_fltr_tbl_lookup_key_size अणु
	QE_FLTR_TABLE_LOOKUP_KEY_SIZE_8_BYTES
		= 0x3f,		/* LookupKey parsed by the Generate LookupKey
				   CMD is truncated to 8 bytes */
	QE_FLTR_TABLE_LOOKUP_KEY_SIZE_16_BYTES
		= 0x5f,		/* LookupKey parsed by the Generate LookupKey
				   CMD is truncated to 16 bytes */
पूर्ण;

/* QE FLTR extended filtering Largest External Table Lookup Key Size */
क्रमागत qe_fltr_largest_बाह्यal_tbl_lookup_key_size अणु
	QE_FLTR_LARGEST_EXTERNAL_TABLE_LOOKUP_KEY_SIZE_NONE
		= 0x0,/* not used */
	QE_FLTR_LARGEST_EXTERNAL_TABLE_LOOKUP_KEY_SIZE_8_BYTES
		= QE_FLTR_TABLE_LOOKUP_KEY_SIZE_8_BYTES,	/* 8 bytes */
	QE_FLTR_LARGEST_EXTERNAL_TABLE_LOOKUP_KEY_SIZE_16_BYTES
		= QE_FLTR_TABLE_LOOKUP_KEY_SIZE_16_BYTES,	/* 16 bytes */
पूर्ण;

/* काष्ठाure representing QE parameter RAM */
काष्ठा qe_समयr_tables अणु
	u16 पंचांग_base;		/* QE समयr table base adr */
	u16 पंचांग_ptr;		/* QE समयr table poपूर्णांकer */
	u16 r_पंचांगr;		/* QE समयr mode रेजिस्टर */
	u16 r_पंचांगv;		/* QE समयr valid रेजिस्टर */
	u32 पंचांग_cmd;		/* QE समयr cmd रेजिस्टर */
	u32 पंचांग_cnt;		/* QE समयr पूर्णांकernal cnt */
पूर्ण __attribute__ ((packed));

#घोषणा QE_FLTR_TAD_SIZE	8

/* QE extended filtering Termination Action Descriptor (TAD) */
काष्ठा qe_fltr_tad अणु
	u8 serialized[QE_FLTR_TAD_SIZE];
पूर्ण __attribute__ ((packed));

/* Communication Direction */
क्रमागत comm_dir अणु
	COMM_सूची_NONE = 0,
	COMM_सूची_RX = 1,
	COMM_सूची_TX = 2,
	COMM_सूची_RX_AND_TX = 3
पूर्ण;

/* QE CMXUCR Registers.
 * There are two UCCs represented in each of the four CMXUCR रेजिस्टरs.
 * These values are क्रम the UCC in the LSBs
 */
#घोषणा QE_CMXUCR_MII_ENET_MNG		0x00007000
#घोषणा QE_CMXUCR_MII_ENET_MNG_SHIFT	12
#घोषणा QE_CMXUCR_GRANT			0x00008000
#घोषणा QE_CMXUCR_TSA			0x00004000
#घोषणा QE_CMXUCR_BKPT			0x00000100
#घोषणा QE_CMXUCR_TX_CLK_SRC_MASK	0x0000000F

/* QE CMXGCR Registers.
*/
#घोषणा QE_CMXGCR_MII_ENET_MNG		0x00007000
#घोषणा QE_CMXGCR_MII_ENET_MNG_SHIFT	12
#घोषणा QE_CMXGCR_USBCS			0x0000000f
#घोषणा QE_CMXGCR_USBCS_CLK3		0x1
#घोषणा QE_CMXGCR_USBCS_CLK5		0x2
#घोषणा QE_CMXGCR_USBCS_CLK7		0x3
#घोषणा QE_CMXGCR_USBCS_CLK9		0x4
#घोषणा QE_CMXGCR_USBCS_CLK13		0x5
#घोषणा QE_CMXGCR_USBCS_CLK17		0x6
#घोषणा QE_CMXGCR_USBCS_CLK19		0x7
#घोषणा QE_CMXGCR_USBCS_CLK21		0x8
#घोषणा QE_CMXGCR_USBCS_BRG9		0x9
#घोषणा QE_CMXGCR_USBCS_BRG10		0xa

/* QE CECR Commands.
*/
#घोषणा QE_CR_FLG			0x00010000
#घोषणा QE_RESET			0x80000000
#घोषणा QE_INIT_TX_RX			0x00000000
#घोषणा QE_INIT_RX			0x00000001
#घोषणा QE_INIT_TX			0x00000002
#घोषणा QE_ENTER_HUNT_MODE		0x00000003
#घोषणा QE_STOP_TX			0x00000004
#घोषणा QE_GRACEFUL_STOP_TX		0x00000005
#घोषणा QE_RESTART_TX			0x00000006
#घोषणा QE_CLOSE_RX_BD			0x00000007
#घोषणा QE_SWITCH_COMMAND		0x00000007
#घोषणा QE_SET_GROUP_ADDRESS		0x00000008
#घोषणा QE_START_IDMA			0x00000009
#घोषणा QE_MCC_STOP_RX			0x00000009
#घोषणा QE_ATM_TRANSMIT			0x0000000a
#घोषणा QE_HPAC_CLEAR_ALL		0x0000000b
#घोषणा QE_GRACEFUL_STOP_RX		0x0000001a
#घोषणा QE_RESTART_RX			0x0000001b
#घोषणा QE_HPAC_SET_PRIORITY		0x0000010b
#घोषणा QE_HPAC_STOP_TX			0x0000020b
#घोषणा QE_HPAC_STOP_RX			0x0000030b
#घोषणा QE_HPAC_GRACEFUL_STOP_TX	0x0000040b
#घोषणा QE_HPAC_GRACEFUL_STOP_RX	0x0000050b
#घोषणा QE_HPAC_START_TX		0x0000060b
#घोषणा QE_HPAC_START_RX		0x0000070b
#घोषणा QE_USB_STOP_TX			0x0000000a
#घोषणा QE_USB_RESTART_TX		0x0000000c
#घोषणा QE_QMC_STOP_TX			0x0000000c
#घोषणा QE_QMC_STOP_RX			0x0000000d
#घोषणा QE_SS7_SU_FIL_RESET		0x0000000e
/* jonathbr added from here करोwn क्रम 83xx */
#घोषणा QE_RESET_BCS			0x0000000a
#घोषणा QE_MCC_INIT_TX_RX_16		0x00000003
#घोषणा QE_MCC_STOP_TX			0x00000004
#घोषणा QE_MCC_INIT_TX_1		0x00000005
#घोषणा QE_MCC_INIT_RX_1		0x00000006
#घोषणा QE_MCC_RESET			0x00000007
#घोषणा QE_SET_TIMER			0x00000008
#घोषणा QE_RANDOM_NUMBER		0x0000000c
#घोषणा QE_ATM_MULTI_THREAD_INIT	0x00000011
#घोषणा QE_ASSIGN_PAGE			0x00000012
#घोषणा QE_ADD_REMOVE_HASH_ENTRY	0x00000013
#घोषणा QE_START_FLOW_CONTROL		0x00000014
#घोषणा QE_STOP_FLOW_CONTROL		0x00000015
#घोषणा QE_ASSIGN_PAGE_TO_DEVICE	0x00000016

#घोषणा QE_ASSIGN_RISC			0x00000010
#घोषणा QE_CR_MCN_NORMAL_SHIFT		6
#घोषणा QE_CR_MCN_USB_SHIFT		4
#घोषणा QE_CR_MCN_RISC_ASSIGN_SHIFT	8
#घोषणा QE_CR_SNUM_SHIFT		17

/* QE CECR Sub Block - sub block of QE command.
*/
#घोषणा QE_CR_SUBBLOCK_INVALID		0x00000000
#घोषणा QE_CR_SUBBLOCK_USB		0x03200000
#घोषणा QE_CR_SUBBLOCK_UCCFAST1		0x02000000
#घोषणा QE_CR_SUBBLOCK_UCCFAST2		0x02200000
#घोषणा QE_CR_SUBBLOCK_UCCFAST3		0x02400000
#घोषणा QE_CR_SUBBLOCK_UCCFAST4		0x02600000
#घोषणा QE_CR_SUBBLOCK_UCCFAST5		0x02800000
#घोषणा QE_CR_SUBBLOCK_UCCFAST6		0x02a00000
#घोषणा QE_CR_SUBBLOCK_UCCFAST7		0x02c00000
#घोषणा QE_CR_SUBBLOCK_UCCFAST8		0x02e00000
#घोषणा QE_CR_SUBBLOCK_UCCSLOW1		0x00000000
#घोषणा QE_CR_SUBBLOCK_UCCSLOW2		0x00200000
#घोषणा QE_CR_SUBBLOCK_UCCSLOW3		0x00400000
#घोषणा QE_CR_SUBBLOCK_UCCSLOW4		0x00600000
#घोषणा QE_CR_SUBBLOCK_UCCSLOW5		0x00800000
#घोषणा QE_CR_SUBBLOCK_UCCSLOW6		0x00a00000
#घोषणा QE_CR_SUBBLOCK_UCCSLOW7		0x00c00000
#घोषणा QE_CR_SUBBLOCK_UCCSLOW8		0x00e00000
#घोषणा QE_CR_SUBBLOCK_MCC1		0x03800000
#घोषणा QE_CR_SUBBLOCK_MCC2		0x03a00000
#घोषणा QE_CR_SUBBLOCK_MCC3		0x03000000
#घोषणा QE_CR_SUBBLOCK_IDMA1		0x02800000
#घोषणा QE_CR_SUBBLOCK_IDMA2		0x02a00000
#घोषणा QE_CR_SUBBLOCK_IDMA3		0x02c00000
#घोषणा QE_CR_SUBBLOCK_IDMA4		0x02e00000
#घोषणा QE_CR_SUBBLOCK_HPAC		0x01e00000
#घोषणा QE_CR_SUBBLOCK_SPI1		0x01400000
#घोषणा QE_CR_SUBBLOCK_SPI2		0x01600000
#घोषणा QE_CR_SUBBLOCK_RAND		0x01c00000
#घोषणा QE_CR_SUBBLOCK_TIMER		0x01e00000
#घोषणा QE_CR_SUBBLOCK_GENERAL		0x03c00000

/* QE CECR Protocol - For non-MCC, specअगरies mode क्रम QE CECR command */
#घोषणा QE_CR_PROTOCOL_UNSPECIFIED	0x00	/* For all other protocols */
#घोषणा QE_CR_PROTOCOL_HDLC_TRANSPARENT	0x00
#घोषणा QE_CR_PROTOCOL_QMC		0x02
#घोषणा QE_CR_PROTOCOL_UART		0x04
#घोषणा QE_CR_PROTOCOL_ATM_POS		0x0A
#घोषणा QE_CR_PROTOCOL_ETHERNET		0x0C
#घोषणा QE_CR_PROTOCOL_L2_SWITCH	0x0D

/* BRG configuration रेजिस्टर */
#घोषणा QE_BRGC_ENABLE		0x00010000
#घोषणा QE_BRGC_DIVISOR_SHIFT	1
#घोषणा QE_BRGC_DIVISOR_MAX	0xFFF
#घोषणा QE_BRGC_DIV16		1

/* QE Timers रेजिस्टरs */
#घोषणा QE_GTCFR1_PCAS	0x80
#घोषणा QE_GTCFR1_STP2	0x20
#घोषणा QE_GTCFR1_RST2	0x10
#घोषणा QE_GTCFR1_GM2	0x08
#घोषणा QE_GTCFR1_GM1	0x04
#घोषणा QE_GTCFR1_STP1	0x02
#घोषणा QE_GTCFR1_RST1	0x01

/* SDMA रेजिस्टरs */
#घोषणा QE_SDSR_BER1	0x02000000
#घोषणा QE_SDSR_BER2	0x01000000

#घोषणा QE_SDMR_GLB_1_MSK	0x80000000
#घोषणा QE_SDMR_ADR_SEL		0x20000000
#घोषणा QE_SDMR_BER1_MSK	0x02000000
#घोषणा QE_SDMR_BER2_MSK	0x01000000
#घोषणा QE_SDMR_EB1_MSK		0x00800000
#घोषणा QE_SDMR_ER1_MSK		0x00080000
#घोषणा QE_SDMR_ER2_MSK		0x00040000
#घोषणा QE_SDMR_CEN_MASK	0x0000E000
#घोषणा QE_SDMR_SBER_1		0x00000200
#घोषणा QE_SDMR_SBER_2		0x00000200
#घोषणा QE_SDMR_EB1_PR_MASK	0x000000C0
#घोषणा QE_SDMR_ER1_PR		0x00000008

#घोषणा QE_SDMR_CEN_SHIFT	13
#घोषणा QE_SDMR_EB1_PR_SHIFT	6

#घोषणा QE_SDTM_MSNUM_SHIFT	24

#घोषणा QE_SDEBCR_BA_MASK	0x01FFFFFF

/* Communication Processor */
#घोषणा QE_CP_CERCR_MEE		0x8000	/* Multi-user RAM ECC enable */
#घोषणा QE_CP_CERCR_IEE		0x4000	/* Inकाष्ठाion RAM ECC enable */
#घोषणा QE_CP_CERCR_CIR		0x0800	/* Common inकाष्ठाion RAM */

/* I-RAM */
#घोषणा QE_IRAM_IADD_AIE	0x80000000	/* Auto Increment Enable */
#घोषणा QE_IRAM_IADD_BADDR	0x00080000	/* Base Address */
#घोषणा QE_IRAM_READY           0x80000000      /* Ready */

/* UPC */
#घोषणा UPGCR_PROTOCOL	0x80000000	/* protocol ul2 or pl2 */
#घोषणा UPGCR_TMS	0x40000000	/* Transmit master/slave mode */
#घोषणा UPGCR_RMS	0x20000000	/* Receive master/slave mode */
#घोषणा UPGCR_ADDR	0x10000000	/* Master MPHY Addr multiplexing */
#घोषणा UPGCR_DIAG	0x01000000	/* Diagnostic mode */

/* UCC GUEMR रेजिस्टर */
#घोषणा UCC_GUEMR_MODE_MASK_RX	0x02
#घोषणा UCC_GUEMR_MODE_FAST_RX	0x02
#घोषणा UCC_GUEMR_MODE_SLOW_RX	0x00
#घोषणा UCC_GUEMR_MODE_MASK_TX	0x01
#घोषणा UCC_GUEMR_MODE_FAST_TX	0x01
#घोषणा UCC_GUEMR_MODE_SLOW_TX	0x00
#घोषणा UCC_GUEMR_MODE_MASK (UCC_GUEMR_MODE_MASK_RX | UCC_GUEMR_MODE_MASK_TX)
#घोषणा UCC_GUEMR_SET_RESERVED3	0x10	/* Bit 3 in the guemr is reserved but
					   must be set 1 */

/* काष्ठाure representing UCC SLOW parameter RAM */
काष्ठा ucc_slow_pram अणु
	__be16 rbase;		/* RX BD base address */
	__be16 tbase;		/* TX BD base address */
	u8 rbmr;		/* RX bus mode रेजिस्टर (same as CPM's RFCR) */
	u8 tbmr;		/* TX bus mode रेजिस्टर (same as CPM's TFCR) */
	__be16 mrblr;		/* Rx buffer length */
	__be32 rstate;		/* Rx पूर्णांकernal state */
	__be32 rptr;		/* Rx पूर्णांकernal data poपूर्णांकer */
	__be16 rbptr;		/* rb BD Poपूर्णांकer */
	__be16 rcount;		/* Rx पूर्णांकernal byte count */
	__be32 rtemp;		/* Rx temp */
	__be32 tstate;		/* Tx पूर्णांकernal state */
	__be32 tptr;		/* Tx पूर्णांकernal data poपूर्णांकer */
	__be16 tbptr;		/* Tx BD poपूर्णांकer */
	__be16 tcount;		/* Tx byte count */
	__be32 ttemp;		/* Tx temp */
	__be32 rcrc;		/* temp receive CRC */
	__be32 tcrc;		/* temp transmit CRC */
पूर्ण __attribute__ ((packed));

/* General UCC SLOW Mode Register (GUMRH & GUMRL) */
#घोषणा UCC_SLOW_GUMR_H_SAM_QMC		0x00000000
#घोषणा UCC_SLOW_GUMR_H_SAM_SATM	0x00008000
#घोषणा UCC_SLOW_GUMR_H_REVD		0x00002000
#घोषणा UCC_SLOW_GUMR_H_TRX		0x00001000
#घोषणा UCC_SLOW_GUMR_H_TTX		0x00000800
#घोषणा UCC_SLOW_GUMR_H_CDP		0x00000400
#घोषणा UCC_SLOW_GUMR_H_CTSP		0x00000200
#घोषणा UCC_SLOW_GUMR_H_CDS		0x00000100
#घोषणा UCC_SLOW_GUMR_H_CTSS		0x00000080
#घोषणा UCC_SLOW_GUMR_H_TFL		0x00000040
#घोषणा UCC_SLOW_GUMR_H_RFW		0x00000020
#घोषणा UCC_SLOW_GUMR_H_TXSY		0x00000010
#घोषणा UCC_SLOW_GUMR_H_4SYNC		0x00000004
#घोषणा UCC_SLOW_GUMR_H_8SYNC		0x00000008
#घोषणा UCC_SLOW_GUMR_H_16SYNC		0x0000000c
#घोषणा UCC_SLOW_GUMR_H_RTSM		0x00000002
#घोषणा UCC_SLOW_GUMR_H_RSYN		0x00000001

#घोषणा UCC_SLOW_GUMR_L_TCI		0x10000000
#घोषणा UCC_SLOW_GUMR_L_RINV		0x02000000
#घोषणा UCC_SLOW_GUMR_L_TINV		0x01000000
#घोषणा UCC_SLOW_GUMR_L_TEND		0x00040000
#घोषणा UCC_SLOW_GUMR_L_TDCR_MASK	0x00030000
#घोषणा UCC_SLOW_GUMR_L_TDCR_32	        0x00030000
#घोषणा UCC_SLOW_GUMR_L_TDCR_16	        0x00020000
#घोषणा UCC_SLOW_GUMR_L_TDCR_8	        0x00010000
#घोषणा UCC_SLOW_GUMR_L_TDCR_1	        0x00000000
#घोषणा UCC_SLOW_GUMR_L_RDCR_MASK	0x0000c000
#घोषणा UCC_SLOW_GUMR_L_RDCR_32		0x0000c000
#घोषणा UCC_SLOW_GUMR_L_RDCR_16	        0x00008000
#घोषणा UCC_SLOW_GUMR_L_RDCR_8	        0x00004000
#घोषणा UCC_SLOW_GUMR_L_RDCR_1		0x00000000
#घोषणा UCC_SLOW_GUMR_L_RENC_NRZI	0x00000800
#घोषणा UCC_SLOW_GUMR_L_RENC_NRZ	0x00000000
#घोषणा UCC_SLOW_GUMR_L_TENC_NRZI	0x00000100
#घोषणा UCC_SLOW_GUMR_L_TENC_NRZ	0x00000000
#घोषणा UCC_SLOW_GUMR_L_DIAG_MASK	0x000000c0
#घोषणा UCC_SLOW_GUMR_L_DIAG_LE	        0x000000c0
#घोषणा UCC_SLOW_GUMR_L_DIAG_ECHO	0x00000080
#घोषणा UCC_SLOW_GUMR_L_DIAG_LOOP	0x00000040
#घोषणा UCC_SLOW_GUMR_L_DIAG_NORM	0x00000000
#घोषणा UCC_SLOW_GUMR_L_ENR		0x00000020
#घोषणा UCC_SLOW_GUMR_L_ENT		0x00000010
#घोषणा UCC_SLOW_GUMR_L_MODE_MASK	0x0000000F
#घोषणा UCC_SLOW_GUMR_L_MODE_BISYNC	0x00000008
#घोषणा UCC_SLOW_GUMR_L_MODE_AHDLC	0x00000006
#घोषणा UCC_SLOW_GUMR_L_MODE_UART	0x00000004
#घोषणा UCC_SLOW_GUMR_L_MODE_QMC	0x00000002

/* General UCC FAST Mode Register */
#घोषणा UCC_FAST_GUMR_LOOPBACK	0x40000000
#घोषणा UCC_FAST_GUMR_TCI	0x20000000
#घोषणा UCC_FAST_GUMR_TRX	0x10000000
#घोषणा UCC_FAST_GUMR_TTX	0x08000000
#घोषणा UCC_FAST_GUMR_CDP	0x04000000
#घोषणा UCC_FAST_GUMR_CTSP	0x02000000
#घोषणा UCC_FAST_GUMR_CDS	0x01000000
#घोषणा UCC_FAST_GUMR_CTSS	0x00800000
#घोषणा UCC_FAST_GUMR_TXSY	0x00020000
#घोषणा UCC_FAST_GUMR_RSYN	0x00010000
#घोषणा UCC_FAST_GUMR_SYNL_MASK	0x0000C000
#घोषणा UCC_FAST_GUMR_SYNL_16	0x0000C000
#घोषणा UCC_FAST_GUMR_SYNL_8	0x00008000
#घोषणा UCC_FAST_GUMR_SYNL_AUTO	0x00004000
#घोषणा UCC_FAST_GUMR_RTSM	0x00002000
#घोषणा UCC_FAST_GUMR_REVD	0x00000400
#घोषणा UCC_FAST_GUMR_ENR	0x00000020
#घोषणा UCC_FAST_GUMR_ENT	0x00000010

/* UART Slow UCC Event Register (UCCE) */
#घोषणा UCC_UART_UCCE_AB	0x0200
#घोषणा UCC_UART_UCCE_IDLE	0x0100
#घोषणा UCC_UART_UCCE_GRA	0x0080
#घोषणा UCC_UART_UCCE_BRKE	0x0040
#घोषणा UCC_UART_UCCE_BRKS	0x0020
#घोषणा UCC_UART_UCCE_CCR	0x0008
#घोषणा UCC_UART_UCCE_BSY	0x0004
#घोषणा UCC_UART_UCCE_TX	0x0002
#घोषणा UCC_UART_UCCE_RX	0x0001

/* HDLC Slow UCC Event Register (UCCE) */
#घोषणा UCC_HDLC_UCCE_GLR	0x1000
#घोषणा UCC_HDLC_UCCE_GLT	0x0800
#घोषणा UCC_HDLC_UCCE_IDLE	0x0100
#घोषणा UCC_HDLC_UCCE_BRKE	0x0040
#घोषणा UCC_HDLC_UCCE_BRKS	0x0020
#घोषणा UCC_HDLC_UCCE_TXE	0x0010
#घोषणा UCC_HDLC_UCCE_RXF	0x0008
#घोषणा UCC_HDLC_UCCE_BSY	0x0004
#घोषणा UCC_HDLC_UCCE_TXB	0x0002
#घोषणा UCC_HDLC_UCCE_RXB	0x0001

/* BISYNC Slow UCC Event Register (UCCE) */
#घोषणा UCC_BISYNC_UCCE_GRA	0x0080
#घोषणा UCC_BISYNC_UCCE_TXE	0x0010
#घोषणा UCC_BISYNC_UCCE_RCH	0x0008
#घोषणा UCC_BISYNC_UCCE_BSY	0x0004
#घोषणा UCC_BISYNC_UCCE_TXB	0x0002
#घोषणा UCC_BISYNC_UCCE_RXB	0x0001

/* Gigabit Ethernet Fast UCC Event Register (UCCE) */
#घोषणा UCC_GETH_UCCE_MPD       0x80000000
#घोषणा UCC_GETH_UCCE_SCAR      0x40000000
#घोषणा UCC_GETH_UCCE_GRA       0x20000000
#घोषणा UCC_GETH_UCCE_CBPR      0x10000000
#घोषणा UCC_GETH_UCCE_BSY       0x08000000
#घोषणा UCC_GETH_UCCE_RXC       0x04000000
#घोषणा UCC_GETH_UCCE_TXC       0x02000000
#घोषणा UCC_GETH_UCCE_TXE       0x01000000
#घोषणा UCC_GETH_UCCE_TXB7      0x00800000
#घोषणा UCC_GETH_UCCE_TXB6      0x00400000
#घोषणा UCC_GETH_UCCE_TXB5      0x00200000
#घोषणा UCC_GETH_UCCE_TXB4      0x00100000
#घोषणा UCC_GETH_UCCE_TXB3      0x00080000
#घोषणा UCC_GETH_UCCE_TXB2      0x00040000
#घोषणा UCC_GETH_UCCE_TXB1      0x00020000
#घोषणा UCC_GETH_UCCE_TXB0      0x00010000
#घोषणा UCC_GETH_UCCE_RXB7      0x00008000
#घोषणा UCC_GETH_UCCE_RXB6      0x00004000
#घोषणा UCC_GETH_UCCE_RXB5      0x00002000
#घोषणा UCC_GETH_UCCE_RXB4      0x00001000
#घोषणा UCC_GETH_UCCE_RXB3      0x00000800
#घोषणा UCC_GETH_UCCE_RXB2      0x00000400
#घोषणा UCC_GETH_UCCE_RXB1      0x00000200
#घोषणा UCC_GETH_UCCE_RXB0      0x00000100
#घोषणा UCC_GETH_UCCE_RXF7      0x00000080
#घोषणा UCC_GETH_UCCE_RXF6      0x00000040
#घोषणा UCC_GETH_UCCE_RXF5      0x00000020
#घोषणा UCC_GETH_UCCE_RXF4      0x00000010
#घोषणा UCC_GETH_UCCE_RXF3      0x00000008
#घोषणा UCC_GETH_UCCE_RXF2      0x00000004
#घोषणा UCC_GETH_UCCE_RXF1      0x00000002
#घोषणा UCC_GETH_UCCE_RXF0      0x00000001

/* UCC Protocol Specअगरic Mode Register (UPSMR), when used क्रम UART */
#घोषणा UCC_UART_UPSMR_FLC		0x8000
#घोषणा UCC_UART_UPSMR_SL		0x4000
#घोषणा UCC_UART_UPSMR_CL_MASK		0x3000
#घोषणा UCC_UART_UPSMR_CL_8		0x3000
#घोषणा UCC_UART_UPSMR_CL_7		0x2000
#घोषणा UCC_UART_UPSMR_CL_6		0x1000
#घोषणा UCC_UART_UPSMR_CL_5		0x0000
#घोषणा UCC_UART_UPSMR_UM_MASK		0x0c00
#घोषणा UCC_UART_UPSMR_UM_NORMAL	0x0000
#घोषणा UCC_UART_UPSMR_UM_MAN_MULTI	0x0400
#घोषणा UCC_UART_UPSMR_UM_AUTO_MULTI	0x0c00
#घोषणा UCC_UART_UPSMR_FRZ		0x0200
#घोषणा UCC_UART_UPSMR_RZS		0x0100
#घोषणा UCC_UART_UPSMR_SYN		0x0080
#घोषणा UCC_UART_UPSMR_DRT		0x0040
#घोषणा UCC_UART_UPSMR_PEN		0x0010
#घोषणा UCC_UART_UPSMR_RPM_MASK		0x000c
#घोषणा UCC_UART_UPSMR_RPM_ODD		0x0000
#घोषणा UCC_UART_UPSMR_RPM_LOW		0x0004
#घोषणा UCC_UART_UPSMR_RPM_EVEN		0x0008
#घोषणा UCC_UART_UPSMR_RPM_HIGH		0x000C
#घोषणा UCC_UART_UPSMR_TPM_MASK		0x0003
#घोषणा UCC_UART_UPSMR_TPM_ODD		0x0000
#घोषणा UCC_UART_UPSMR_TPM_LOW		0x0001
#घोषणा UCC_UART_UPSMR_TPM_EVEN		0x0002
#घोषणा UCC_UART_UPSMR_TPM_HIGH		0x0003

/* UCC Protocol Specअगरic Mode Register (UPSMR), when used क्रम Ethernet */
#घोषणा UCC_GETH_UPSMR_FTFE     0x80000000
#घोषणा UCC_GETH_UPSMR_PTPE     0x40000000
#घोषणा UCC_GETH_UPSMR_ECM      0x04000000
#घोषणा UCC_GETH_UPSMR_HSE      0x02000000
#घोषणा UCC_GETH_UPSMR_PRO      0x00400000
#घोषणा UCC_GETH_UPSMR_CAP      0x00200000
#घोषणा UCC_GETH_UPSMR_RSH      0x00100000
#घोषणा UCC_GETH_UPSMR_RPM      0x00080000
#घोषणा UCC_GETH_UPSMR_R10M     0x00040000
#घोषणा UCC_GETH_UPSMR_RLPB     0x00020000
#घोषणा UCC_GETH_UPSMR_TBIM     0x00010000
#घोषणा UCC_GETH_UPSMR_RES1     0x00002000
#घोषणा UCC_GETH_UPSMR_RMM      0x00001000
#घोषणा UCC_GETH_UPSMR_CAM      0x00000400
#घोषणा UCC_GETH_UPSMR_BRO      0x00000200
#घोषणा UCC_GETH_UPSMR_SMM	0x00000080
#घोषणा UCC_GETH_UPSMR_SGMM	0x00000020

/* UCC Protocol Specअगरic Mode Register (UPSMR), when used क्रम HDLC */
#घोषणा UCC_HDLC_UPSMR_RTE	0x02000000
#घोषणा UCC_HDLC_UPSMR_BUS	0x00200000
#घोषणा UCC_HDLC_UPSMR_CW8	0x00007000

/* UCC Transmit On Demand Register (UTODR) */
#घोषणा UCC_SLOW_TOD	0x8000
#घोषणा UCC_FAST_TOD	0x8000

/* UCC Bus Mode Register masks */
/* Not to be confused with the Bundle Mode Register */
#घोषणा UCC_BMR_GBL		0x20
#घोषणा UCC_BMR_BO_BE		0x10
#घोषणा UCC_BMR_CETM		0x04
#घोषणा UCC_BMR_DTB		0x02
#घोषणा UCC_BMR_BDB		0x01

/* Function code masks */
#घोषणा FC_GBL				0x20
#घोषणा FC_DTB_LCL			0x02
#घोषणा UCC_FAST_FUNCTION_CODE_GBL	0x20
#घोषणा UCC_FAST_FUNCTION_CODE_DTB_LCL	0x02
#घोषणा UCC_FAST_FUNCTION_CODE_BDB_LCL	0x01

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_QE_H */
