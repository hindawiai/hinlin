<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * nozomi.c  -- HSDPA driver Broadband Wireless Data Card - Globe Trotter
 *
 * Written by: Ulf Jakobsson,
 *             Jan थkerfeldt,
 *             Stefan Thomasson,
 *
 * Maपूर्णांकained by: Paul Hardwick (p.hardwick@option.com)
 *
 * Patches:
 *          Locking code changes क्रम Vodafone by Sphere Systems Ltd,
 *                              Andrew Bird (ajb@sphereप्रणालीs.co.uk )
 *                              & Phil Sanderson
 *
 * Source has been ported from an implementation made by Filip Aben @ Option
 *
 * --------------------------------------------------------------------------
 *
 * Copyright (c) 2005,2006 Option Wireless Sweden AB
 * Copyright (c) 2006 Sphere Systems Ltd
 * Copyright (c) 2006 Option Wireless n/v
 * All rights Reserved.
 *
 * --------------------------------------------------------------------------
 */

/* Enable this to have a lot of debug prपूर्णांकouts */
#घोषणा DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/sched.h>
#समावेश <linux/serial.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kmod.h>
#समावेश <linux/init.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <linux/delay.h>

/* Default debug prपूर्णांकout level */
#घोषणा NOZOMI_DEBUG_LEVEL 0x00
अटल पूर्णांक debug = NOZOMI_DEBUG_LEVEL;
module_param(debug, पूर्णांक, S_IRUGO | S_IWUSR);

/*    Macros definitions */
#घोषणा DBG_(lvl, fmt, args...)				\
करो अणु							\
	अगर (lvl & debug)				\
		pr_debug("[%d] %s(): " fmt "\n",	\
			 __LINE__, __func__,  ##args);	\
पूर्ण जबतक (0)

#घोषणा DBG1(args...) DBG_(0x01, ##args)
#घोषणा DBG2(args...) DBG_(0x02, ##args)
#घोषणा DBG3(args...) DBG_(0x04, ##args)
#घोषणा DBG4(args...) DBG_(0x08, ##args)

/* TODO: reग_लिखो to optimize macros... */

#घोषणा TMP_BUF_MAX 256

#घोषणा DUMP(buf__, len__)						\
	करो अणु								\
		अक्षर tbuf[TMP_BUF_MAX] = अणु0पूर्ण;				\
		अगर (len__ > 1) अणु					\
			u32 data_len = min_t(u32, len__, TMP_BUF_MAX);	\
			strscpy(tbuf, buf__, data_len);			\
			अगर (tbuf[data_len - 2] == '\r')			\
				tbuf[data_len - 2] = 'r';		\
			DBG1("SENDING: '%s' (%d+n)", tbuf, len__);	\
		पूर्ण अन्यथा अणु						\
			DBG1("SENDING: '%s' (%d)", tbuf, len__);	\
		पूर्ण							\
	पूर्ण जबतक (0)

/*    Defines */
#घोषणा NOZOMI_NAME		"nozomi"
#घोषणा NOZOMI_NAME_TTY		"nozomi_tty"

#घोषणा NTTY_TTY_MAXMINORS	256
#घोषणा NTTY_FIFO_BUFFER_SIZE	8192

/* Must be घातer of 2 */
#घोषणा FIFO_BUFFER_SIZE_UL	8192

/* Size of पंचांगp send buffer to card */
#घोषणा SEND_BUF_MAX		1024
#घोषणा RECEIVE_BUF_MAX		4


#घोषणा R_IIR			0x0000	/* Interrupt Identity Register */
#घोषणा R_FCR			0x0000	/* Flow Control Register */
#घोषणा R_IER			0x0004	/* Interrupt Enable Register */

#घोषणा NOZOMI_CONFIG_MAGIC	0xEFEFFEFE
#घोषणा TOGGLE_VALID		0x0000

/* Definition of पूर्णांकerrupt tokens */
#घोषणा MDM_DL1			0x0001
#घोषणा MDM_UL1			0x0002
#घोषणा MDM_DL2			0x0004
#घोषणा MDM_UL2			0x0008
#घोषणा DIAG_DL1		0x0010
#घोषणा DIAG_DL2		0x0020
#घोषणा DIAG_UL			0x0040
#घोषणा APP1_DL			0x0080
#घोषणा APP1_UL			0x0100
#घोषणा APP2_DL			0x0200
#घोषणा APP2_UL			0x0400
#घोषणा CTRL_DL			0x0800
#घोषणा CTRL_UL			0x1000
#घोषणा RESET			0x8000

#घोषणा MDM_DL			(MDM_DL1  | MDM_DL2)
#घोषणा MDM_UL			(MDM_UL1  | MDM_UL2)
#घोषणा DIAG_DL			(DIAG_DL1 | DIAG_DL2)

/* modem संकेत definition */
#घोषणा CTRL_DSR		0x0001
#घोषणा CTRL_DCD		0x0002
#घोषणा CTRL_RI			0x0004
#घोषणा CTRL_CTS		0x0008

#घोषणा CTRL_DTR		0x0001
#घोषणा CTRL_RTS		0x0002

#घोषणा MAX_PORT		4
#घोषणा NOZOMI_MAX_PORTS	5
#घोषणा NOZOMI_MAX_CARDS	(NTTY_TTY_MAXMINORS / MAX_PORT)

/*    Type definitions */

/*
 * There are two types of nozomi cards,
 * one with 2048 memory and with 8192 memory
 */
क्रमागत card_type अणु
	F32_2 = 2048,	/* 512 bytes करोwnlink + uplink * 2 -> 2048 */
	F32_8 = 8192,	/* 3072 bytes करोwnl. + 1024 bytes uplink * 2 -> 8192 */
पूर्ण;

/* Initialization states a card can be in */
क्रमागत card_state अणु
	NOZOMI_STATE_UNKNOWN	= 0,
	NOZOMI_STATE_ENABLED	= 1,	/* pci device enabled */
	NOZOMI_STATE_ALLOCATED	= 2,	/* config setup करोne */
	NOZOMI_STATE_READY	= 3,	/* flowcontrols received */
पूर्ण;

/* Two dअगरferent toggle channels exist */
क्रमागत channel_type अणु
	CH_A = 0,
	CH_B = 1,
पूर्ण;

/* Port definition क्रम the card regarding flow control */
क्रमागत ctrl_port_type अणु
	CTRL_CMD	= 0,
	CTRL_MDM	= 1,
	CTRL_DIAG	= 2,
	CTRL_APP1	= 3,
	CTRL_APP2	= 4,
	CTRL_ERROR	= -1,
पूर्ण;

/* Ports that the nozomi has */
क्रमागत port_type अणु
	PORT_MDM	= 0,
	PORT_DIAG	= 1,
	PORT_APP1	= 2,
	PORT_APP2	= 3,
	PORT_CTRL	= 4,
	PORT_ERROR	= -1,
पूर्ण;

#अगर_घोषित __BIG_ENDIAN
/* Big endian */

काष्ठा toggles अणु
	अचिन्हित पूर्णांक enabled:5;	/*
				 * Toggle fields are valid अगर enabled is 0,
				 * अन्यथा A-channels must always be used.
				 */
	अचिन्हित पूर्णांक diag_dl:1;
	अचिन्हित पूर्णांक mdm_dl:1;
	अचिन्हित पूर्णांक mdm_ul:1;
पूर्ण __attribute__ ((packed));

/* Configuration table to पढ़ो at startup of card */
/* Is क्रम now only needed during initialization phase */
काष्ठा config_table अणु
	u32 signature;
	u16 product_inक्रमmation;
	u16 version;
	u8 pad3[3];
	काष्ठा toggles toggle;
	u8 pad1[4];
	u16 dl_mdm_len1;	/*
				 * If this is 64, it can hold
				 * 60 bytes + 4 that is length field
				 */
	u16 dl_start;

	u16 dl_diag_len1;
	u16 dl_mdm_len2;	/*
				 * If this is 64, it can hold
				 * 60 bytes + 4 that is length field
				 */
	u16 dl_app1_len;

	u16 dl_diag_len2;
	u16 dl_ctrl_len;
	u16 dl_app2_len;
	u8 pad2[16];
	u16 ul_mdm_len1;
	u16 ul_start;
	u16 ul_diag_len;
	u16 ul_mdm_len2;
	u16 ul_app1_len;
	u16 ul_app2_len;
	u16 ul_ctrl_len;
पूर्ण __attribute__ ((packed));

/* This stores all control करोwnlink flags */
काष्ठा ctrl_dl अणु
	u8 port;
	अचिन्हित पूर्णांक reserved:4;
	अचिन्हित पूर्णांक CTS:1;
	अचिन्हित पूर्णांक RI:1;
	अचिन्हित पूर्णांक DCD:1;
	अचिन्हित पूर्णांक DSR:1;
पूर्ण __attribute__ ((packed));

/* This stores all control uplink flags */
काष्ठा ctrl_ul अणु
	u8 port;
	अचिन्हित पूर्णांक reserved:6;
	अचिन्हित पूर्णांक RTS:1;
	अचिन्हित पूर्णांक DTR:1;
पूर्ण __attribute__ ((packed));

#अन्यथा
/* Little endian */

/* This represents the toggle inक्रमmation */
काष्ठा toggles अणु
	अचिन्हित पूर्णांक mdm_ul:1;
	अचिन्हित पूर्णांक mdm_dl:1;
	अचिन्हित पूर्णांक diag_dl:1;
	अचिन्हित पूर्णांक enabled:5;	/*
				 * Toggle fields are valid अगर enabled is 0,
				 * अन्यथा A-channels must always be used.
				 */
पूर्ण __attribute__ ((packed));

/* Configuration table to पढ़ो at startup of card */
काष्ठा config_table अणु
	u32 signature;
	u16 version;
	u16 product_inक्रमmation;
	काष्ठा toggles toggle;
	u8 pad1[7];
	u16 dl_start;
	u16 dl_mdm_len1;	/*
				 * If this is 64, it can hold
				 * 60 bytes + 4 that is length field
				 */
	u16 dl_mdm_len2;
	u16 dl_diag_len1;
	u16 dl_diag_len2;
	u16 dl_app1_len;
	u16 dl_app2_len;
	u16 dl_ctrl_len;
	u8 pad2[16];
	u16 ul_start;
	u16 ul_mdm_len2;
	u16 ul_mdm_len1;
	u16 ul_diag_len;
	u16 ul_app1_len;
	u16 ul_app2_len;
	u16 ul_ctrl_len;
पूर्ण __attribute__ ((packed));

/* This stores all control करोwnlink flags */
काष्ठा ctrl_dl अणु
	अचिन्हित पूर्णांक DSR:1;
	अचिन्हित पूर्णांक DCD:1;
	अचिन्हित पूर्णांक RI:1;
	अचिन्हित पूर्णांक CTS:1;
	अचिन्हित पूर्णांक reserved:4;
	u8 port;
पूर्ण __attribute__ ((packed));

/* This stores all control uplink flags */
काष्ठा ctrl_ul अणु
	अचिन्हित पूर्णांक DTR:1;
	अचिन्हित पूर्णांक RTS:1;
	अचिन्हित पूर्णांक reserved:6;
	u8 port;
पूर्ण __attribute__ ((packed));
#पूर्ण_अगर

/* This holds all inक्रमmation that is needed regarding a port */
काष्ठा port अणु
	काष्ठा tty_port port;
	u8 update_flow_control;
	काष्ठा ctrl_ul ctrl_ul;
	काष्ठा ctrl_dl ctrl_dl;
	काष्ठा kfअगरo fअगरo_ul;
	व्योम __iomem *dl_addr[2];
	u32 dl_size[2];
	u8 toggle_dl;
	व्योम __iomem *ul_addr[2];
	u32 ul_size[2];
	u8 toggle_ul;
	u16 token_dl;

	रुको_queue_head_t tty_रुको;
	काष्ठा async_icount tty_icount;

	काष्ठा nozomi *dc;
पूर्ण;

/* Private data one क्रम each card in the प्रणाली */
काष्ठा nozomi अणु
	व्योम __iomem *base_addr;
	अचिन्हित दीर्घ flip;

	/* Poपूर्णांकers to रेजिस्टरs */
	व्योम __iomem *reg_iir;
	व्योम __iomem *reg_fcr;
	व्योम __iomem *reg_ier;

	u16 last_ier;
	क्रमागत card_type card_type;
	काष्ठा config_table config_table;	/* Configuration table */
	काष्ठा pci_dev *pdev;
	काष्ठा port port[NOZOMI_MAX_PORTS];
	u8 *send_buf;

	spinlock_t spin_mutex;	/* secures access to रेजिस्टरs and tty */

	अचिन्हित पूर्णांक index_start;
	क्रमागत card_state state;
	u32 खोलो_ttys;
पूर्ण;

/* Global variables */
अटल स्थिर काष्ठा pci_device_id nozomi_pci_tbl[] = अणु
	अणुPCI_DEVICE(0x1931, 0x000c)पूर्ण,	/* Nozomi HSDPA */
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, nozomi_pci_tbl);

अटल काष्ठा nozomi *ndevs[NOZOMI_MAX_CARDS];
अटल काष्ठा tty_driver *ntty_driver;

अटल स्थिर काष्ठा tty_port_operations noz_tty_port_ops;

/*
 * find card by tty_index
 */
अटल अंतरभूत काष्ठा nozomi *get_dc_by_tty(स्थिर काष्ठा tty_काष्ठा *tty)
अणु
	वापस tty ? ndevs[tty->index / MAX_PORT] : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा port *get_port_by_tty(स्थिर काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा nozomi *ndev = get_dc_by_tty(tty);
	वापस ndev ? &ndev->port[tty->index % MAX_PORT] : शून्य;
पूर्ण

/*
 * TODO:
 * -Optimize
 * -Reग_लिखो cleaner
 */

अटल व्योम पढ़ो_mem32(u32 *buf, स्थिर व्योम __iomem *mem_addr_start,
			u32 size_bytes)
अणु
	u32 i = 0;
	स्थिर u32 __iomem *ptr = mem_addr_start;
	u16 *buf16;

	अगर (unlikely(!ptr || !buf))
		जाओ out;

	/* लघुcut क्रम extremely often used हालs */
	चयन (size_bytes) अणु
	हाल 2:	/* 2 bytes */
		buf16 = (u16 *) buf;
		*buf16 = __le16_to_cpu(पढ़ोw(ptr));
		जाओ out;
	हाल 4:	/* 4 bytes */
		*(buf) = __le32_to_cpu(पढ़ोl(ptr));
		जाओ out;
	पूर्ण

	जबतक (i < size_bytes) अणु
		अगर (size_bytes - i == 2) अणु
			/* Handle 2 bytes in the end */
			buf16 = (u16 *) buf;
			*(buf16) = __le16_to_cpu(पढ़ोw(ptr));
			i += 2;
		पूर्ण अन्यथा अणु
			/* Read 4 bytes */
			*(buf) = __le32_to_cpu(पढ़ोl(ptr));
			i += 4;
		पूर्ण
		buf++;
		ptr++;
	पूर्ण
out:
	वापस;
पूर्ण

/*
 * TODO:
 * -Optimize
 * -Reग_लिखो cleaner
 */
अटल u32 ग_लिखो_mem32(व्योम __iomem *mem_addr_start, स्थिर u32 *buf,
			u32 size_bytes)
अणु
	u32 i = 0;
	u32 __iomem *ptr = mem_addr_start;
	स्थिर u16 *buf16;

	अगर (unlikely(!ptr || !buf))
		वापस 0;

	/* लघुcut क्रम extremely often used हालs */
	चयन (size_bytes) अणु
	हाल 2:	/* 2 bytes */
		buf16 = (स्थिर u16 *)buf;
		ग_लिखोw(__cpu_to_le16(*buf16), ptr);
		वापस 2;
	हाल 1: /*
		 * also needs to ग_लिखो 4 bytes in this हाल
		 * so falling through..
		 */
		fallthrough;
	हाल 4: /* 4 bytes */
		ग_लिखोl(__cpu_to_le32(*buf), ptr);
		वापस 4;
	पूर्ण

	जबतक (i < size_bytes) अणु
		अगर (size_bytes - i == 2) अणु
			/* 2 bytes */
			buf16 = (स्थिर u16 *)buf;
			ग_लिखोw(__cpu_to_le16(*buf16), ptr);
			i += 2;
		पूर्ण अन्यथा अणु
			/* 4 bytes */
			ग_लिखोl(__cpu_to_le32(*buf), ptr);
			i += 4;
		पूर्ण
		buf++;
		ptr++;
	पूर्ण
	वापस i;
पूर्ण

/* Setup poपूर्णांकers to dअगरferent channels and also setup buffer sizes. */
अटल व्योम nozomi_setup_memory(काष्ठा nozomi *dc)
अणु
	व्योम __iomem *offset = dc->base_addr + dc->config_table.dl_start;
	/* The length reported is including the length field of 4 bytes,
	 * hence subtract with 4.
	 */
	स्थिर u16 buff_offset = 4;

	/* Modem port dl configuration */
	dc->port[PORT_MDM].dl_addr[CH_A] = offset;
	dc->port[PORT_MDM].dl_addr[CH_B] =
				(offset += dc->config_table.dl_mdm_len1);
	dc->port[PORT_MDM].dl_size[CH_A] =
				dc->config_table.dl_mdm_len1 - buff_offset;
	dc->port[PORT_MDM].dl_size[CH_B] =
				dc->config_table.dl_mdm_len2 - buff_offset;

	/* Diag port dl configuration */
	dc->port[PORT_DIAG].dl_addr[CH_A] =
				(offset += dc->config_table.dl_mdm_len2);
	dc->port[PORT_DIAG].dl_size[CH_A] =
				dc->config_table.dl_diag_len1 - buff_offset;
	dc->port[PORT_DIAG].dl_addr[CH_B] =
				(offset += dc->config_table.dl_diag_len1);
	dc->port[PORT_DIAG].dl_size[CH_B] =
				dc->config_table.dl_diag_len2 - buff_offset;

	/* App1 port dl configuration */
	dc->port[PORT_APP1].dl_addr[CH_A] =
				(offset += dc->config_table.dl_diag_len2);
	dc->port[PORT_APP1].dl_size[CH_A] =
				dc->config_table.dl_app1_len - buff_offset;

	/* App2 port dl configuration */
	dc->port[PORT_APP2].dl_addr[CH_A] =
				(offset += dc->config_table.dl_app1_len);
	dc->port[PORT_APP2].dl_size[CH_A] =
				dc->config_table.dl_app2_len - buff_offset;

	/* Ctrl dl configuration */
	dc->port[PORT_CTRL].dl_addr[CH_A] =
				(offset += dc->config_table.dl_app2_len);
	dc->port[PORT_CTRL].dl_size[CH_A] =
				dc->config_table.dl_ctrl_len - buff_offset;

	offset = dc->base_addr + dc->config_table.ul_start;

	/* Modem Port ul configuration */
	dc->port[PORT_MDM].ul_addr[CH_A] = offset;
	dc->port[PORT_MDM].ul_size[CH_A] =
				dc->config_table.ul_mdm_len1 - buff_offset;
	dc->port[PORT_MDM].ul_addr[CH_B] =
				(offset += dc->config_table.ul_mdm_len1);
	dc->port[PORT_MDM].ul_size[CH_B] =
				dc->config_table.ul_mdm_len2 - buff_offset;

	/* Diag port ul configuration */
	dc->port[PORT_DIAG].ul_addr[CH_A] =
				(offset += dc->config_table.ul_mdm_len2);
	dc->port[PORT_DIAG].ul_size[CH_A] =
				dc->config_table.ul_diag_len - buff_offset;

	/* App1 port ul configuration */
	dc->port[PORT_APP1].ul_addr[CH_A] =
				(offset += dc->config_table.ul_diag_len);
	dc->port[PORT_APP1].ul_size[CH_A] =
				dc->config_table.ul_app1_len - buff_offset;

	/* App2 port ul configuration */
	dc->port[PORT_APP2].ul_addr[CH_A] =
				(offset += dc->config_table.ul_app1_len);
	dc->port[PORT_APP2].ul_size[CH_A] =
				dc->config_table.ul_app2_len - buff_offset;

	/* Ctrl ul configuration */
	dc->port[PORT_CTRL].ul_addr[CH_A] =
				(offset += dc->config_table.ul_app2_len);
	dc->port[PORT_CTRL].ul_size[CH_A] =
				dc->config_table.ul_ctrl_len - buff_offset;
पूर्ण

/* Dump config table under initalization phase */
#अगर_घोषित DEBUG
अटल व्योम dump_table(स्थिर काष्ठा nozomi *dc)
अणु
	DBG3("signature: 0x%08X", dc->config_table.signature);
	DBG3("version: 0x%04X", dc->config_table.version);
	DBG3("product_information: 0x%04X", \
				dc->config_table.product_inक्रमmation);
	DBG3("toggle enabled: %d", dc->config_table.toggle.enabled);
	DBG3("toggle up_mdm: %d", dc->config_table.toggle.mdm_ul);
	DBG3("toggle dl_mdm: %d", dc->config_table.toggle.mdm_dl);
	DBG3("toggle dl_dbg: %d", dc->config_table.toggle.diag_dl);

	DBG3("dl_start: 0x%04X", dc->config_table.dl_start);
	DBG3("dl_mdm_len0: 0x%04X, %d", dc->config_table.dl_mdm_len1,
	   dc->config_table.dl_mdm_len1);
	DBG3("dl_mdm_len1: 0x%04X, %d", dc->config_table.dl_mdm_len2,
	   dc->config_table.dl_mdm_len2);
	DBG3("dl_diag_len0: 0x%04X, %d", dc->config_table.dl_diag_len1,
	   dc->config_table.dl_diag_len1);
	DBG3("dl_diag_len1: 0x%04X, %d", dc->config_table.dl_diag_len2,
	   dc->config_table.dl_diag_len2);
	DBG3("dl_app1_len: 0x%04X, %d", dc->config_table.dl_app1_len,
	   dc->config_table.dl_app1_len);
	DBG3("dl_app2_len: 0x%04X, %d", dc->config_table.dl_app2_len,
	   dc->config_table.dl_app2_len);
	DBG3("dl_ctrl_len: 0x%04X, %d", dc->config_table.dl_ctrl_len,
	   dc->config_table.dl_ctrl_len);
	DBG3("ul_start: 0x%04X, %d", dc->config_table.ul_start,
	   dc->config_table.ul_start);
	DBG3("ul_mdm_len[0]: 0x%04X, %d", dc->config_table.ul_mdm_len1,
	   dc->config_table.ul_mdm_len1);
	DBG3("ul_mdm_len[1]: 0x%04X, %d", dc->config_table.ul_mdm_len2,
	   dc->config_table.ul_mdm_len2);
	DBG3("ul_diag_len: 0x%04X, %d", dc->config_table.ul_diag_len,
	   dc->config_table.ul_diag_len);
	DBG3("ul_app1_len: 0x%04X, %d", dc->config_table.ul_app1_len,
	   dc->config_table.ul_app1_len);
	DBG3("ul_app2_len: 0x%04X, %d", dc->config_table.ul_app2_len,
	   dc->config_table.ul_app2_len);
	DBG3("ul_ctrl_len: 0x%04X, %d", dc->config_table.ul_ctrl_len,
	   dc->config_table.ul_ctrl_len);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dump_table(स्थिर काष्ठा nozomi *dc) अणु पूर्ण
#पूर्ण_अगर

/*
 * Read configuration table from card under पूर्णांकalization phase
 * Returns 1 अगर ok, अन्यथा 0
 */
अटल पूर्णांक nozomi_पढ़ो_config_table(काष्ठा nozomi *dc)
अणु
	पढ़ो_mem32((u32 *) &dc->config_table, dc->base_addr + 0,
						माप(काष्ठा config_table));

	अगर (dc->config_table.signature != NOZOMI_CONFIG_MAGIC) अणु
		dev_err(&dc->pdev->dev, "ConfigTable Bad! 0x%08X != 0x%08X\n",
			dc->config_table.signature, NOZOMI_CONFIG_MAGIC);
		वापस 0;
	पूर्ण

	अगर ((dc->config_table.version == 0)
	    || (dc->config_table.toggle.enabled == TOGGLE_VALID)) अणु
		पूर्णांक i;
		DBG1("Second phase, configuring card");

		nozomi_setup_memory(dc);

		dc->port[PORT_MDM].toggle_ul = dc->config_table.toggle.mdm_ul;
		dc->port[PORT_MDM].toggle_dl = dc->config_table.toggle.mdm_dl;
		dc->port[PORT_DIAG].toggle_dl = dc->config_table.toggle.diag_dl;
		DBG1("toggle ports: MDM UL:%d MDM DL:%d, DIAG DL:%d",
		   dc->port[PORT_MDM].toggle_ul,
		   dc->port[PORT_MDM].toggle_dl, dc->port[PORT_DIAG].toggle_dl);

		dump_table(dc);

		क्रम (i = PORT_MDM; i < MAX_PORT; i++) अणु
			स_रखो(&dc->port[i].ctrl_dl, 0, माप(काष्ठा ctrl_dl));
			स_रखो(&dc->port[i].ctrl_ul, 0, माप(काष्ठा ctrl_ul));
		पूर्ण

		/* Enable control channel */
		dc->last_ier = dc->last_ier | CTRL_DL;
		ग_लिखोw(dc->last_ier, dc->reg_ier);

		dc->state = NOZOMI_STATE_ALLOCATED;
		dev_info(&dc->pdev->dev, "Initialization OK!\n");
		वापस 1;
	पूर्ण

	अगर ((dc->config_table.version > 0)
	    && (dc->config_table.toggle.enabled != TOGGLE_VALID)) अणु
		u32 offset = 0;
		DBG1("First phase: pushing upload buffers, clearing download");

		dev_info(&dc->pdev->dev, "Version of card: %d\n",
			 dc->config_table.version);

		/* Here we should disable all I/O over F32. */
		nozomi_setup_memory(dc);

		/*
		 * We should send ALL channel pair tokens back aदीर्घ
		 * with reset token
		 */

		/* push upload modem buffers */
		ग_लिखो_mem32(dc->port[PORT_MDM].ul_addr[CH_A],
			(u32 *) &offset, 4);
		ग_लिखो_mem32(dc->port[PORT_MDM].ul_addr[CH_B],
			(u32 *) &offset, 4);

		ग_लिखोw(MDM_UL | DIAG_DL | MDM_DL, dc->reg_fcr);

		DBG1("First phase done");
	पूर्ण

	वापस 1;
पूर्ण

/* Enable uplink पूर्णांकerrupts  */
अटल व्योम enable_transmit_ul(क्रमागत port_type port, काष्ठा nozomi *dc)
अणु
	अटल स्थिर u16 mask[] = अणुMDM_UL, DIAG_UL, APP1_UL, APP2_UL, CTRL_ULपूर्ण;

	अगर (port < NOZOMI_MAX_PORTS) अणु
		dc->last_ier |= mask[port];
		ग_लिखोw(dc->last_ier, dc->reg_ier);
	पूर्ण अन्यथा अणु
		dev_err(&dc->pdev->dev, "Called with wrong port?\n");
	पूर्ण
पूर्ण

/* Disable uplink पूर्णांकerrupts  */
अटल व्योम disable_transmit_ul(क्रमागत port_type port, काष्ठा nozomi *dc)
अणु
	अटल स्थिर u16 mask[] =
		अणु~MDM_UL, ~DIAG_UL, ~APP1_UL, ~APP2_UL, ~CTRL_ULपूर्ण;

	अगर (port < NOZOMI_MAX_PORTS) अणु
		dc->last_ier &= mask[port];
		ग_लिखोw(dc->last_ier, dc->reg_ier);
	पूर्ण अन्यथा अणु
		dev_err(&dc->pdev->dev, "Called with wrong port?\n");
	पूर्ण
पूर्ण

/* Enable करोwnlink पूर्णांकerrupts */
अटल व्योम enable_transmit_dl(क्रमागत port_type port, काष्ठा nozomi *dc)
अणु
	अटल स्थिर u16 mask[] = अणुMDM_DL, DIAG_DL, APP1_DL, APP2_DL, CTRL_DLपूर्ण;

	अगर (port < NOZOMI_MAX_PORTS) अणु
		dc->last_ier |= mask[port];
		ग_लिखोw(dc->last_ier, dc->reg_ier);
	पूर्ण अन्यथा अणु
		dev_err(&dc->pdev->dev, "Called with wrong port?\n");
	पूर्ण
पूर्ण

/* Disable करोwnlink पूर्णांकerrupts */
अटल व्योम disable_transmit_dl(क्रमागत port_type port, काष्ठा nozomi *dc)
अणु
	अटल स्थिर u16 mask[] =
		अणु~MDM_DL, ~DIAG_DL, ~APP1_DL, ~APP2_DL, ~CTRL_DLपूर्ण;

	अगर (port < NOZOMI_MAX_PORTS) अणु
		dc->last_ier &= mask[port];
		ग_लिखोw(dc->last_ier, dc->reg_ier);
	पूर्ण अन्यथा अणु
		dev_err(&dc->pdev->dev, "Called with wrong port?\n");
	पूर्ण
पूर्ण

/*
 * Return 1 - send buffer to card and ack.
 * Return 0 - करोn't ack, don't send buffer to card.
 */
अटल पूर्णांक send_data(क्रमागत port_type index, काष्ठा nozomi *dc)
अणु
	u32 size = 0;
	काष्ठा port *port = &dc->port[index];
	स्थिर u8 toggle = port->toggle_ul;
	व्योम __iomem *addr = port->ul_addr[toggle];
	स्थिर u32 ul_size = port->ul_size[toggle];

	/* Get data from tty and place in buf क्रम now */
	size = kfअगरo_out(&port->fअगरo_ul, dc->send_buf,
			   ul_size < SEND_BUF_MAX ? ul_size : SEND_BUF_MAX);

	अगर (size == 0) अणु
		DBG4("No more data to send, disable link:");
		वापस 0;
	पूर्ण

	/* DUMP(buf, size); */

	/* Write length + data */
	ग_लिखो_mem32(addr, (u32 *) &size, 4);
	ग_लिखो_mem32(addr + 4, (u32 *) dc->send_buf, size);

	tty_port_tty_wakeup(&port->port);

	वापस 1;
पूर्ण

/* If all data has been पढ़ो, वापस 1, अन्यथा 0 */
अटल पूर्णांक receive_data(क्रमागत port_type index, काष्ठा nozomi *dc)
अणु
	u8 buf[RECEIVE_BUF_MAX] = अणु 0 पूर्ण;
	पूर्णांक size;
	u32 offset = 4;
	काष्ठा port *port = &dc->port[index];
	व्योम __iomem *addr = port->dl_addr[port->toggle_dl];
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&port->port);
	पूर्णांक i, ret;

	size = __le32_to_cpu(पढ़ोl(addr));

	अगर (tty && tty_throttled(tty)) अणु
		DBG1("No room in tty, don't read data, don't ack interrupt, "
			"disable interrupt");

		/* disable पूर्णांकerrupt in करोwnlink... */
		disable_transmit_dl(index, dc);
		ret = 0;
		जाओ put;
	पूर्ण

	अगर (unlikely(size == 0)) अणु
		dev_err(&dc->pdev->dev, "size == 0?\n");
		ret = 1;
		जाओ put;
	पूर्ण

	जबतक (size > 0) अणु
		पढ़ो_mem32((u32 *) buf, addr + offset, RECEIVE_BUF_MAX);

		अगर (size == 1) अणु
			tty_insert_flip_अक्षर(&port->port, buf[0], TTY_NORMAL);
			size = 0;
		पूर्ण अन्यथा अगर (size < RECEIVE_BUF_MAX) अणु
			size -= tty_insert_flip_string(&port->port,
					(अक्षर *)buf, size);
		पूर्ण अन्यथा अणु
			i = tty_insert_flip_string(&port->port,
					(अक्षर *)buf, RECEIVE_BUF_MAX);
			size -= i;
			offset += i;
		पूर्ण
	पूर्ण

	set_bit(index, &dc->flip);
	ret = 1;
put:
	tty_kref_put(tty);
	वापस ret;
पूर्ण

/* Debug क्रम पूर्णांकerrupts */
#अगर_घोषित DEBUG
अटल अक्षर *पूर्णांकerrupt2str(u16 पूर्णांकerrupt)
अणु
	अटल अक्षर buf[TMP_BUF_MAX];
	अक्षर *p = buf;

	अगर (पूर्णांकerrupt & MDM_DL1)
		p += scnम_लिखो(p, TMP_BUF_MAX, "MDM_DL1 ");
	अगर (पूर्णांकerrupt & MDM_DL2)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "MDM_DL2 ");
	अगर (पूर्णांकerrupt & MDM_UL1)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "MDM_UL1 ");
	अगर (पूर्णांकerrupt & MDM_UL2)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "MDM_UL2 ");
	अगर (पूर्णांकerrupt & DIAG_DL1)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "DIAG_DL1 ");
	अगर (पूर्णांकerrupt & DIAG_DL2)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "DIAG_DL2 ");

	अगर (पूर्णांकerrupt & DIAG_UL)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "DIAG_UL ");

	अगर (पूर्णांकerrupt & APP1_DL)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "APP1_DL ");
	अगर (पूर्णांकerrupt & APP2_DL)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "APP2_DL ");

	अगर (पूर्णांकerrupt & APP1_UL)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "APP1_UL ");
	अगर (पूर्णांकerrupt & APP2_UL)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "APP2_UL ");

	अगर (पूर्णांकerrupt & CTRL_DL)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "CTRL_DL ");
	अगर (पूर्णांकerrupt & CTRL_UL)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "CTRL_UL ");

	अगर (पूर्णांकerrupt & RESET)
		p += scnम_लिखो(p, TMP_BUF_MAX - (p - buf), "RESET ");

	वापस buf;
पूर्ण
#पूर्ण_अगर

/*
 * Receive flow control
 * Return 1 - If ok, अन्यथा 0
 */
अटल पूर्णांक receive_flow_control(काष्ठा nozomi *dc)
अणु
	क्रमागत port_type port = PORT_MDM;
	काष्ठा ctrl_dl ctrl_dl;
	काष्ठा ctrl_dl old_ctrl;
	u16 enable_ier = 0;

	पढ़ो_mem32((u32 *) &ctrl_dl, dc->port[PORT_CTRL].dl_addr[CH_A], 2);

	चयन (ctrl_dl.port) अणु
	हाल CTRL_CMD:
		DBG1("The Base Band sends this value as a response to a "
			"request for IMSI detach sent over the control "
			"channel uplink (see section 7.6.1).");
		अवरोध;
	हाल CTRL_MDM:
		port = PORT_MDM;
		enable_ier = MDM_DL;
		अवरोध;
	हाल CTRL_DIAG:
		port = PORT_DIAG;
		enable_ier = DIAG_DL;
		अवरोध;
	हाल CTRL_APP1:
		port = PORT_APP1;
		enable_ier = APP1_DL;
		अवरोध;
	हाल CTRL_APP2:
		port = PORT_APP2;
		enable_ier = APP2_DL;
		अगर (dc->state == NOZOMI_STATE_ALLOCATED) अणु
			/*
			 * After card initialization the flow control
			 * received क्रम APP2 is always the last
			 */
			dc->state = NOZOMI_STATE_READY;
			dev_info(&dc->pdev->dev, "Device READY!\n");
		पूर्ण
		अवरोध;
	शेष:
		dev_err(&dc->pdev->dev,
			"ERROR: flow control received for non-existing port\n");
		वापस 0;
	पूर्ण

	DBG1("0x%04X->0x%04X", *((u16 *)&dc->port[port].ctrl_dl),
	   *((u16 *)&ctrl_dl));

	old_ctrl = dc->port[port].ctrl_dl;
	dc->port[port].ctrl_dl = ctrl_dl;

	अगर (old_ctrl.CTS == 1 && ctrl_dl.CTS == 0) अणु
		DBG1("Disable interrupt (0x%04X) on port: %d",
			enable_ier, port);
		disable_transmit_ul(port, dc);

	पूर्ण अन्यथा अगर (old_ctrl.CTS == 0 && ctrl_dl.CTS == 1) अणु

		अगर (kfअगरo_len(&dc->port[port].fअगरo_ul)) अणु
			DBG1("Enable interrupt (0x%04X) on port: %d",
				enable_ier, port);
			DBG1("Data in buffer [%d], enable transmit! ",
				kfअगरo_len(&dc->port[port].fअगरo_ul));
			enable_transmit_ul(port, dc);
		पूर्ण अन्यथा अणु
			DBG1("No data in buffer...");
		पूर्ण
	पूर्ण

	अगर (*(u16 *)&old_ctrl == *(u16 *)&ctrl_dl) अणु
		DBG1(" No change in mctrl");
		वापस 1;
	पूर्ण
	/* Update statistics */
	अगर (old_ctrl.CTS != ctrl_dl.CTS)
		dc->port[port].tty_icount.cts++;
	अगर (old_ctrl.DSR != ctrl_dl.DSR)
		dc->port[port].tty_icount.dsr++;
	अगर (old_ctrl.RI != ctrl_dl.RI)
		dc->port[port].tty_icount.rng++;
	अगर (old_ctrl.DCD != ctrl_dl.DCD)
		dc->port[port].tty_icount.dcd++;

	wake_up_पूर्णांकerruptible(&dc->port[port].tty_रुको);

	DBG1("port: %d DCD(%d), CTS(%d), RI(%d), DSR(%d)",
	   port,
	   dc->port[port].tty_icount.dcd, dc->port[port].tty_icount.cts,
	   dc->port[port].tty_icount.rng, dc->port[port].tty_icount.dsr);

	वापस 1;
पूर्ण

अटल क्रमागत ctrl_port_type port2ctrl(क्रमागत port_type port,
					स्थिर काष्ठा nozomi *dc)
अणु
	चयन (port) अणु
	हाल PORT_MDM:
		वापस CTRL_MDM;
	हाल PORT_DIAG:
		वापस CTRL_DIAG;
	हाल PORT_APP1:
		वापस CTRL_APP1;
	हाल PORT_APP2:
		वापस CTRL_APP2;
	शेष:
		dev_err(&dc->pdev->dev,
			"ERROR: send flow control " \
			"received for non-existing port\n");
	पूर्ण
	वापस CTRL_ERROR;
पूर्ण

/*
 * Send flow control, can only update one channel at a समय
 * Return 0 - If we have updated all flow control
 * Return 1 - If we need to update more flow control, ack current enable more
 */
अटल पूर्णांक send_flow_control(काष्ठा nozomi *dc)
अणु
	u32 i, more_flow_control_to_be_updated = 0;
	u16 *ctrl;

	क्रम (i = PORT_MDM; i < MAX_PORT; i++) अणु
		अगर (dc->port[i].update_flow_control) अणु
			अगर (more_flow_control_to_be_updated) अणु
				/* We have more flow control to be updated */
				वापस 1;
			पूर्ण
			dc->port[i].ctrl_ul.port = port2ctrl(i, dc);
			ctrl = (u16 *)&dc->port[i].ctrl_ul;
			ग_लिखो_mem32(dc->port[PORT_CTRL].ul_addr[0], \
				(u32 *) ctrl, 2);
			dc->port[i].update_flow_control = 0;
			more_flow_control_to_be_updated = 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Handle करोwnlink data, ports that are handled are modem and diagnostics
 * Return 1 - ok
 * Return 0 - toggle fields are out of sync
 */
अटल पूर्णांक handle_data_dl(काष्ठा nozomi *dc, क्रमागत port_type port, u8 *toggle,
			u16 पढ़ो_iir, u16 mask1, u16 mask2)
अणु
	अगर (*toggle == 0 && पढ़ो_iir & mask1) अणु
		अगर (receive_data(port, dc)) अणु
			ग_लिखोw(mask1, dc->reg_fcr);
			*toggle = !(*toggle);
		पूर्ण

		अगर (पढ़ो_iir & mask2) अणु
			अगर (receive_data(port, dc)) अणु
				ग_लिखोw(mask2, dc->reg_fcr);
				*toggle = !(*toggle);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (*toggle == 1 && पढ़ो_iir & mask2) अणु
		अगर (receive_data(port, dc)) अणु
			ग_लिखोw(mask2, dc->reg_fcr);
			*toggle = !(*toggle);
		पूर्ण

		अगर (पढ़ो_iir & mask1) अणु
			अगर (receive_data(port, dc)) अणु
				ग_लिखोw(mask1, dc->reg_fcr);
				*toggle = !(*toggle);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&dc->pdev->dev, "port out of sync!, toggle:%d\n",
			*toggle);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Handle uplink data, this is currently क्रम the modem port
 * Return 1 - ok
 * Return 0 - toggle field are out of sync
 */
अटल पूर्णांक handle_data_ul(काष्ठा nozomi *dc, क्रमागत port_type port, u16 पढ़ो_iir)
अणु
	u8 *toggle = &(dc->port[port].toggle_ul);

	अगर (*toggle == 0 && पढ़ो_iir & MDM_UL1) अणु
		dc->last_ier &= ~MDM_UL;
		ग_लिखोw(dc->last_ier, dc->reg_ier);
		अगर (send_data(port, dc)) अणु
			ग_लिखोw(MDM_UL1, dc->reg_fcr);
			dc->last_ier = dc->last_ier | MDM_UL;
			ग_लिखोw(dc->last_ier, dc->reg_ier);
			*toggle = !*toggle;
		पूर्ण

		अगर (पढ़ो_iir & MDM_UL2) अणु
			dc->last_ier &= ~MDM_UL;
			ग_लिखोw(dc->last_ier, dc->reg_ier);
			अगर (send_data(port, dc)) अणु
				ग_लिखोw(MDM_UL2, dc->reg_fcr);
				dc->last_ier = dc->last_ier | MDM_UL;
				ग_लिखोw(dc->last_ier, dc->reg_ier);
				*toggle = !*toggle;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (*toggle == 1 && पढ़ो_iir & MDM_UL2) अणु
		dc->last_ier &= ~MDM_UL;
		ग_लिखोw(dc->last_ier, dc->reg_ier);
		अगर (send_data(port, dc)) अणु
			ग_लिखोw(MDM_UL2, dc->reg_fcr);
			dc->last_ier = dc->last_ier | MDM_UL;
			ग_लिखोw(dc->last_ier, dc->reg_ier);
			*toggle = !*toggle;
		पूर्ण

		अगर (पढ़ो_iir & MDM_UL1) अणु
			dc->last_ier &= ~MDM_UL;
			ग_लिखोw(dc->last_ier, dc->reg_ier);
			अगर (send_data(port, dc)) अणु
				ग_लिखोw(MDM_UL1, dc->reg_fcr);
				dc->last_ier = dc->last_ier | MDM_UL;
				ग_लिखोw(dc->last_ier, dc->reg_ier);
				*toggle = !*toggle;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ग_लिखोw(पढ़ो_iir & MDM_UL, dc->reg_fcr);
		dev_err(&dc->pdev->dev, "port out of sync!\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल irqवापस_t पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा nozomi *dc = dev_id;
	अचिन्हित पूर्णांक a;
	u16 पढ़ो_iir;

	अगर (!dc)
		वापस IRQ_NONE;

	spin_lock(&dc->spin_mutex);
	पढ़ो_iir = पढ़ोw(dc->reg_iir);

	/* Card हटाओd */
	अगर (पढ़ो_iir == (u16)-1)
		जाओ none;
	/*
	 * Just handle पूर्णांकerrupt enabled in IER
	 * (by masking with dc->last_ier)
	 */
	पढ़ो_iir &= dc->last_ier;

	अगर (पढ़ो_iir == 0)
		जाओ none;


	DBG4("%s irq:0x%04X, prev:0x%04X", पूर्णांकerrupt2str(पढ़ो_iir), पढ़ो_iir,
		dc->last_ier);

	अगर (पढ़ो_iir & RESET) अणु
		अगर (unlikely(!nozomi_पढ़ो_config_table(dc))) अणु
			dc->last_ier = 0x0;
			ग_लिखोw(dc->last_ier, dc->reg_ier);
			dev_err(&dc->pdev->dev, "Could not read status from "
				"card, we should disable interface\n");
		पूर्ण अन्यथा अणु
			ग_लिखोw(RESET, dc->reg_fcr);
		पूर्ण
		/* No more useful info अगर this was the reset पूर्णांकerrupt. */
		जाओ निकास_handler;
	पूर्ण
	अगर (पढ़ो_iir & CTRL_UL) अणु
		DBG1("CTRL_UL");
		dc->last_ier &= ~CTRL_UL;
		ग_लिखोw(dc->last_ier, dc->reg_ier);
		अगर (send_flow_control(dc)) अणु
			ग_लिखोw(CTRL_UL, dc->reg_fcr);
			dc->last_ier = dc->last_ier | CTRL_UL;
			ग_लिखोw(dc->last_ier, dc->reg_ier);
		पूर्ण
	पूर्ण
	अगर (पढ़ो_iir & CTRL_DL) अणु
		receive_flow_control(dc);
		ग_लिखोw(CTRL_DL, dc->reg_fcr);
	पूर्ण
	अगर (पढ़ो_iir & MDM_DL) अणु
		अगर (!handle_data_dl(dc, PORT_MDM,
				&(dc->port[PORT_MDM].toggle_dl), पढ़ो_iir,
				MDM_DL1, MDM_DL2)) अणु
			dev_err(&dc->pdev->dev, "MDM_DL out of sync!\n");
			जाओ निकास_handler;
		पूर्ण
	पूर्ण
	अगर (पढ़ो_iir & MDM_UL) अणु
		अगर (!handle_data_ul(dc, PORT_MDM, पढ़ो_iir)) अणु
			dev_err(&dc->pdev->dev, "MDM_UL out of sync!\n");
			जाओ निकास_handler;
		पूर्ण
	पूर्ण
	अगर (पढ़ो_iir & DIAG_DL) अणु
		अगर (!handle_data_dl(dc, PORT_DIAG,
				&(dc->port[PORT_DIAG].toggle_dl), पढ़ो_iir,
				DIAG_DL1, DIAG_DL2)) अणु
			dev_err(&dc->pdev->dev, "DIAG_DL out of sync!\n");
			जाओ निकास_handler;
		पूर्ण
	पूर्ण
	अगर (पढ़ो_iir & DIAG_UL) अणु
		dc->last_ier &= ~DIAG_UL;
		ग_लिखोw(dc->last_ier, dc->reg_ier);
		अगर (send_data(PORT_DIAG, dc)) अणु
			ग_लिखोw(DIAG_UL, dc->reg_fcr);
			dc->last_ier = dc->last_ier | DIAG_UL;
			ग_लिखोw(dc->last_ier, dc->reg_ier);
		पूर्ण
	पूर्ण
	अगर (पढ़ो_iir & APP1_DL) अणु
		अगर (receive_data(PORT_APP1, dc))
			ग_लिखोw(APP1_DL, dc->reg_fcr);
	पूर्ण
	अगर (पढ़ो_iir & APP1_UL) अणु
		dc->last_ier &= ~APP1_UL;
		ग_लिखोw(dc->last_ier, dc->reg_ier);
		अगर (send_data(PORT_APP1, dc)) अणु
			ग_लिखोw(APP1_UL, dc->reg_fcr);
			dc->last_ier = dc->last_ier | APP1_UL;
			ग_लिखोw(dc->last_ier, dc->reg_ier);
		पूर्ण
	पूर्ण
	अगर (पढ़ो_iir & APP2_DL) अणु
		अगर (receive_data(PORT_APP2, dc))
			ग_लिखोw(APP2_DL, dc->reg_fcr);
	पूर्ण
	अगर (पढ़ो_iir & APP2_UL) अणु
		dc->last_ier &= ~APP2_UL;
		ग_लिखोw(dc->last_ier, dc->reg_ier);
		अगर (send_data(PORT_APP2, dc)) अणु
			ग_लिखोw(APP2_UL, dc->reg_fcr);
			dc->last_ier = dc->last_ier | APP2_UL;
			ग_लिखोw(dc->last_ier, dc->reg_ier);
		पूर्ण
	पूर्ण

निकास_handler:
	spin_unlock(&dc->spin_mutex);

	क्रम (a = 0; a < NOZOMI_MAX_PORTS; a++)
		अगर (test_and_clear_bit(a, &dc->flip))
			tty_flip_buffer_push(&dc->port[a].port);

	वापस IRQ_HANDLED;
none:
	spin_unlock(&dc->spin_mutex);
	वापस IRQ_NONE;
पूर्ण

अटल व्योम nozomi_get_card_type(काष्ठा nozomi *dc)
अणु
	पूर्णांक i;
	u32 size = 0;

	क्रम (i = 0; i < 6; i++)
		size += pci_resource_len(dc->pdev, i);

	/* Assume card type F32_8 अगर no match */
	dc->card_type = size == 2048 ? F32_2 : F32_8;

	dev_info(&dc->pdev->dev, "Card type is: %d\n", dc->card_type);
पूर्ण

अटल व्योम nozomi_setup_निजी_data(काष्ठा nozomi *dc)
अणु
	व्योम __iomem *offset = dc->base_addr + dc->card_type / 2;
	अचिन्हित पूर्णांक i;

	dc->reg_fcr = (व्योम __iomem *)(offset + R_FCR);
	dc->reg_iir = (व्योम __iomem *)(offset + R_IIR);
	dc->reg_ier = (व्योम __iomem *)(offset + R_IER);
	dc->last_ier = 0;
	dc->flip = 0;

	dc->port[PORT_MDM].token_dl = MDM_DL;
	dc->port[PORT_DIAG].token_dl = DIAG_DL;
	dc->port[PORT_APP1].token_dl = APP1_DL;
	dc->port[PORT_APP2].token_dl = APP2_DL;

	क्रम (i = 0; i < MAX_PORT; i++)
		init_रुकोqueue_head(&dc->port[i].tty_रुको);
पूर्ण

अटल sमाप_प्रकार card_type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	स्थिर काष्ठा nozomi *dc = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", dc->card_type);
पूर्ण
अटल DEVICE_ATTR_RO(card_type);

अटल sमाप_प्रकार खोलो_ttys_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	स्थिर काष्ठा nozomi *dc = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", dc->खोलो_ttys);
पूर्ण
अटल DEVICE_ATTR_RO(खोलो_ttys);

अटल व्योम make_sysfs_files(काष्ठा nozomi *dc)
अणु
	अगर (device_create_file(&dc->pdev->dev, &dev_attr_card_type))
		dev_err(&dc->pdev->dev,
			"Could not create sysfs file for card_type\n");
	अगर (device_create_file(&dc->pdev->dev, &dev_attr_खोलो_ttys))
		dev_err(&dc->pdev->dev,
			"Could not create sysfs file for open_ttys\n");
पूर्ण

अटल व्योम हटाओ_sysfs_files(काष्ठा nozomi *dc)
अणु
	device_हटाओ_file(&dc->pdev->dev, &dev_attr_card_type);
	device_हटाओ_file(&dc->pdev->dev, &dev_attr_खोलो_ttys);
पूर्ण

/* Allocate memory क्रम one device */
अटल पूर्णांक nozomi_card_init(काष्ठा pci_dev *pdev,
				      स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret;
	काष्ठा nozomi *dc = शून्य;
	पूर्णांक ndev_idx;
	पूर्णांक i;

	क्रम (ndev_idx = 0; ndev_idx < ARRAY_SIZE(ndevs); ndev_idx++)
		अगर (!ndevs[ndev_idx])
			अवरोध;

	अगर (ndev_idx >= ARRAY_SIZE(ndevs)) अणु
		dev_err(&pdev->dev, "no free tty range for this card left\n");
		ret = -EIO;
		जाओ err;
	पूर्ण

	dc = kzalloc(माप(काष्ठा nozomi), GFP_KERNEL);
	अगर (unlikely(!dc)) अणु
		dev_err(&pdev->dev, "Could not allocate memory\n");
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	dc->pdev = pdev;

	ret = pci_enable_device(dc->pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to enable PCI Device\n");
		जाओ err_मुक्त;
	पूर्ण

	ret = pci_request_regions(dc->pdev, NOZOMI_NAME);
	अगर (ret) अणु
		dev_err(&pdev->dev, "I/O address 0x%04x already in use\n",
			(पूर्णांक) /* nozomi_निजी.io_addr */ 0);
		जाओ err_disable_device;
	पूर्ण

	/* Find out what card type it is */
	nozomi_get_card_type(dc);

	dc->base_addr = pci_iomap(dc->pdev, 0, dc->card_type);
	अगर (!dc->base_addr) अणु
		dev_err(&pdev->dev, "Unable to map card MMIO\n");
		ret = -ENODEV;
		जाओ err_rel_regs;
	पूर्ण

	dc->send_buf = kदो_स्मृति(SEND_BUF_MAX, GFP_KERNEL);
	अगर (!dc->send_buf) अणु
		dev_err(&pdev->dev, "Could not allocate send buffer?\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_sbuf;
	पूर्ण

	क्रम (i = PORT_MDM; i < MAX_PORT; i++) अणु
		अगर (kfअगरo_alloc(&dc->port[i].fअगरo_ul, FIFO_BUFFER_SIZE_UL,
					GFP_KERNEL)) अणु
			dev_err(&pdev->dev,
					"Could not allocate kfifo buffer\n");
			ret = -ENOMEM;
			जाओ err_मुक्त_kfअगरo;
		पूर्ण
	पूर्ण

	spin_lock_init(&dc->spin_mutex);

	nozomi_setup_निजी_data(dc);

	/* Disable all पूर्णांकerrupts */
	dc->last_ier = 0;
	ग_लिखोw(dc->last_ier, dc->reg_ier);

	ret = request_irq(pdev->irq, &पूर्णांकerrupt_handler, IRQF_SHARED,
			NOZOMI_NAME, dc);
	अगर (unlikely(ret)) अणु
		dev_err(&pdev->dev, "can't request irq %d\n", pdev->irq);
		जाओ err_मुक्त_kfअगरo;
	पूर्ण

	DBG1("base_addr: %p", dc->base_addr);

	make_sysfs_files(dc);

	dc->index_start = ndev_idx * MAX_PORT;
	ndevs[ndev_idx] = dc;

	pci_set_drvdata(pdev, dc);

	/* Enable RESET पूर्णांकerrupt */
	dc->last_ier = RESET;
	ioग_लिखो16(dc->last_ier, dc->reg_ier);

	dc->state = NOZOMI_STATE_ENABLED;

	क्रम (i = 0; i < MAX_PORT; i++) अणु
		काष्ठा device *tty_dev;
		काष्ठा port *port = &dc->port[i];
		port->dc = dc;
		tty_port_init(&port->port);
		port->port.ops = &noz_tty_port_ops;
		tty_dev = tty_port_रेजिस्टर_device(&port->port, ntty_driver,
				dc->index_start + i, &pdev->dev);

		अगर (IS_ERR(tty_dev)) अणु
			ret = PTR_ERR(tty_dev);
			dev_err(&pdev->dev, "Could not allocate tty?\n");
			tty_port_destroy(&port->port);
			जाओ err_मुक्त_tty;
		पूर्ण
	पूर्ण

	वापस 0;

err_मुक्त_tty:
	क्रम (i = 0; i < MAX_PORT; ++i) अणु
		tty_unरेजिस्टर_device(ntty_driver, dc->index_start + i);
		tty_port_destroy(&dc->port[i].port);
	पूर्ण
err_मुक्त_kfअगरo:
	क्रम (i = 0; i < MAX_PORT; i++)
		kfअगरo_मुक्त(&dc->port[i].fअगरo_ul);
err_मुक्त_sbuf:
	kमुक्त(dc->send_buf);
	iounmap(dc->base_addr);
err_rel_regs:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
err_मुक्त:
	kमुक्त(dc);
err:
	वापस ret;
पूर्ण

अटल व्योम tty_निकास(काष्ठा nozomi *dc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_PORT; ++i)
		tty_port_tty_hangup(&dc->port[i].port, false);

	/* Racy below - surely should रुको क्रम scheduled work to be करोne or
	   complete off a hangup method ? */
	जबतक (dc->खोलो_ttys)
		msleep(1);
	क्रम (i = 0; i < MAX_PORT; ++i) अणु
		tty_unरेजिस्टर_device(ntty_driver, dc->index_start + i);
		tty_port_destroy(&dc->port[i].port);
	पूर्ण
पूर्ण

/* Deallocate memory क्रम one device */
अटल व्योम nozomi_card_निकास(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा ctrl_ul ctrl;
	काष्ठा nozomi *dc = pci_get_drvdata(pdev);

	/* Disable all पूर्णांकerrupts */
	dc->last_ier = 0;
	ग_लिखोw(dc->last_ier, dc->reg_ier);

	tty_निकास(dc);

	/* Send 0x0001, command card to resend the reset token.  */
	/* This is to get the reset when the module is reloaded. */
	ctrl.port = 0x00;
	ctrl.reserved = 0;
	ctrl.RTS = 0;
	ctrl.DTR = 1;
	DBG1("sending flow control 0x%04X", *((u16 *)&ctrl));

	/* Setup dc->reg addresses to we can use defines here */
	ग_लिखो_mem32(dc->port[PORT_CTRL].ul_addr[0], (u32 *)&ctrl, 2);
	ग_लिखोw(CTRL_UL, dc->reg_fcr);	/* push the token to the card. */

	हटाओ_sysfs_files(dc);

	मुक्त_irq(pdev->irq, dc);

	क्रम (i = 0; i < MAX_PORT; i++)
		kfअगरo_मुक्त(&dc->port[i].fअगरo_ul);

	kमुक्त(dc->send_buf);

	iounmap(dc->base_addr);

	pci_release_regions(pdev);

	pci_disable_device(pdev);

	ndevs[dc->index_start / MAX_PORT] = शून्य;

	kमुक्त(dc);
पूर्ण

अटल व्योम set_rts(स्थिर काष्ठा tty_काष्ठा *tty, पूर्णांक rts)
अणु
	काष्ठा port *port = get_port_by_tty(tty);

	port->ctrl_ul.RTS = rts;
	port->update_flow_control = 1;
	enable_transmit_ul(PORT_CTRL, get_dc_by_tty(tty));
पूर्ण

अटल व्योम set_dtr(स्थिर काष्ठा tty_काष्ठा *tty, पूर्णांक dtr)
अणु
	काष्ठा port *port = get_port_by_tty(tty);

	DBG1("SETTING DTR index: %d, dtr: %d", tty->index, dtr);

	port->ctrl_ul.DTR = dtr;
	port->update_flow_control = 1;
	enable_transmit_ul(PORT_CTRL, get_dc_by_tty(tty));
पूर्ण

/*
 * ----------------------------------------------------------------------------
 * TTY code
 * ----------------------------------------------------------------------------
 */

अटल पूर्णांक ntty_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा port *port = get_port_by_tty(tty);
	काष्ठा nozomi *dc = get_dc_by_tty(tty);
	पूर्णांक ret;
	अगर (!port || !dc || dc->state != NOZOMI_STATE_READY)
		वापस -ENODEV;
	ret = tty_standard_install(driver, tty);
	अगर (ret == 0)
		tty->driver_data = port;
	वापस ret;
पूर्ण

अटल व्योम ntty_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	tty->driver_data = शून्य;
पूर्ण

अटल पूर्णांक ntty_activate(काष्ठा tty_port *tport, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा port *port = container_of(tport, काष्ठा port, port);
	काष्ठा nozomi *dc = port->dc;
	अचिन्हित दीर्घ flags;

	DBG1("open: %d", port->token_dl);
	spin_lock_irqsave(&dc->spin_mutex, flags);
	dc->last_ier = dc->last_ier | port->token_dl;
	ग_लिखोw(dc->last_ier, dc->reg_ier);
	dc->खोलो_ttys++;
	spin_unlock_irqrestore(&dc->spin_mutex, flags);
	prपूर्णांकk("noz: activated %d: %p\n", tty->index, tport);
	वापस 0;
पूर्ण

अटल पूर्णांक ntty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा port *port = tty->driver_data;
	वापस tty_port_खोलो(&port->port, tty, filp);
पूर्ण

अटल व्योम ntty_shutकरोwn(काष्ठा tty_port *tport)
अणु
	काष्ठा port *port = container_of(tport, काष्ठा port, port);
	काष्ठा nozomi *dc = port->dc;
	अचिन्हित दीर्घ flags;

	DBG1("close: %d", port->token_dl);
	spin_lock_irqsave(&dc->spin_mutex, flags);
	dc->last_ier &= ~(port->token_dl);
	ग_लिखोw(dc->last_ier, dc->reg_ier);
	dc->खोलो_ttys--;
	spin_unlock_irqrestore(&dc->spin_mutex, flags);
	prपूर्णांकk("noz: shutdown %p\n", tport);
पूर्ण

अटल व्योम ntty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा port *port = tty->driver_data;
	अगर (port)
		tty_port_बंद(&port->port, tty, filp);
पूर्ण

अटल व्योम ntty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा port *port = tty->driver_data;
	tty_port_hangup(&port->port);
पूर्ण

/*
 * called when the userspace process ग_लिखोs to the tty (/dev/noz*).
 * Data is inserted पूर्णांकo a fअगरo, which is then पढ़ो and transferred to the modem.
 */
अटल पूर्णांक ntty_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buffer,
		      पूर्णांक count)
अणु
	पूर्णांक rval = -EINVAL;
	काष्ठा nozomi *dc = get_dc_by_tty(tty);
	काष्ठा port *port = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (!dc || !port)
		वापस -ENODEV;

	rval = kfअगरo_in(&port->fअगरo_ul, (अचिन्हित अक्षर *)buffer, count);

	spin_lock_irqsave(&dc->spin_mutex, flags);
	/* CTS is only valid on the modem channel */
	अगर (port == &(dc->port[PORT_MDM])) अणु
		अगर (port->ctrl_dl.CTS) अणु
			DBG4("Enable interrupt");
			enable_transmit_ul(tty->index % MAX_PORT, dc);
		पूर्ण अन्यथा अणु
			dev_err(&dc->pdev->dev,
				"CTS not active on modem port?\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		enable_transmit_ul(tty->index % MAX_PORT, dc);
	पूर्ण
	spin_unlock_irqrestore(&dc->spin_mutex, flags);

	वापस rval;
पूर्ण

/*
 * Calculate how much is left in device
 * This method is called by the upper tty layer.
 *   #according to sources N_TTY.c it expects a value >= 0 and
 *    करोes not check क्रम negative values.
 *
 * If the port is unplugged report lots of room and let the bits
 * dribble away so we करोn't block anything.
 */
अटल पूर्णांक ntty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा port *port = tty->driver_data;
	पूर्णांक room = 4096;
	स्थिर काष्ठा nozomi *dc = get_dc_by_tty(tty);

	अगर (dc)
		room = kfअगरo_avail(&port->fअगरo_ul);

	वापस room;
पूर्ण

/* Gets io control parameters */
अटल पूर्णांक ntty_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	स्थिर काष्ठा port *port = tty->driver_data;
	स्थिर काष्ठा ctrl_dl *ctrl_dl = &port->ctrl_dl;
	स्थिर काष्ठा ctrl_ul *ctrl_ul = &port->ctrl_ul;

	/* Note: these could change under us but it is not clear this
	   matters अगर so */
	वापस (ctrl_ul->RTS ? TIOCM_RTS : 0)
		| (ctrl_ul->DTR ? TIOCM_DTR : 0)
		| (ctrl_dl->DCD ? TIOCM_CAR : 0)
		| (ctrl_dl->RI  ? TIOCM_RNG : 0)
		| (ctrl_dl->DSR ? TIOCM_DSR : 0)
		| (ctrl_dl->CTS ? TIOCM_CTS : 0);
पूर्ण

/* Sets io controls parameters */
अटल पूर्णांक ntty_tiocmset(काष्ठा tty_काष्ठा *tty,
					अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा nozomi *dc = get_dc_by_tty(tty);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dc->spin_mutex, flags);
	अगर (set & TIOCM_RTS)
		set_rts(tty, 1);
	अन्यथा अगर (clear & TIOCM_RTS)
		set_rts(tty, 0);

	अगर (set & TIOCM_DTR)
		set_dtr(tty, 1);
	अन्यथा अगर (clear & TIOCM_DTR)
		set_dtr(tty, 0);
	spin_unlock_irqrestore(&dc->spin_mutex, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ntty_cflags_changed(काष्ठा port *port, अचिन्हित दीर्घ flags,
		काष्ठा async_icount *cprev)
अणु
	स्थिर काष्ठा async_icount cnow = port->tty_icount;
	पूर्णांक ret;

	ret = ((flags & TIOCM_RNG) && (cnow.rng != cprev->rng))
		|| ((flags & TIOCM_DSR) && (cnow.dsr != cprev->dsr))
		|| ((flags & TIOCM_CD)  && (cnow.dcd != cprev->dcd))
		|| ((flags & TIOCM_CTS) && (cnow.cts != cprev->cts));

	*cprev = cnow;

	वापस ret;
पूर्ण

अटल पूर्णांक ntty_tiocgicount(काष्ठा tty_काष्ठा *tty,
				काष्ठा serial_icounter_काष्ठा *icount)
अणु
	काष्ठा port *port = tty->driver_data;
	स्थिर काष्ठा async_icount cnow = port->tty_icount;

	icount->cts = cnow.cts;
	icount->dsr = cnow.dsr;
	icount->rng = cnow.rng;
	icount->dcd = cnow.dcd;
	icount->rx = cnow.rx;
	icount->tx = cnow.tx;
	icount->frame = cnow.frame;
	icount->overrun = cnow.overrun;
	icount->parity = cnow.parity;
	icount->brk = cnow.brk;
	icount->buf_overrun = cnow.buf_overrun;
	वापस 0;
पूर्ण

अटल पूर्णांक ntty_ioctl(काष्ठा tty_काष्ठा *tty,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा port *port = tty->driver_data;
	पूर्णांक rval = -ENOIOCTLCMD;

	चयन (cmd) अणु
	हाल TIOCMIWAIT: अणु
		काष्ठा async_icount cprev = port->tty_icount;

		rval = रुको_event_पूर्णांकerruptible(port->tty_रुको,
				ntty_cflags_changed(port, arg, &cprev));
		अवरोध;
	पूर्ण
	शेष:
		DBG1("ERR: 0x%08X, %d", cmd, cmd);
		अवरोध;
	पूर्ण

	वापस rval;
पूर्ण

/*
 * Called by the upper tty layer when tty buffers are पढ़ोy
 * to receive data again after a call to throttle.
 */
अटल व्योम ntty_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा nozomi *dc = get_dc_by_tty(tty);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dc->spin_mutex, flags);
	enable_transmit_dl(tty->index % MAX_PORT, dc);
	set_rts(tty, 1);

	spin_unlock_irqrestore(&dc->spin_mutex, flags);
पूर्ण

/*
 * Called by the upper tty layer when the tty buffers are almost full.
 * The driver should stop send more data.
 */
अटल व्योम ntty_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा nozomi *dc = get_dc_by_tty(tty);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dc->spin_mutex, flags);
	set_rts(tty, 0);
	spin_unlock_irqrestore(&dc->spin_mutex, flags);
पूर्ण

/* Returns number of अक्षरs in buffer, called by tty layer */
अटल s32 ntty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा port *port = tty->driver_data;
	काष्ठा nozomi *dc = get_dc_by_tty(tty);
	s32 rval = 0;

	अगर (unlikely(!dc || !port)) अणु
		जाओ निकास_in_buffer;
	पूर्ण

	rval = kfअगरo_len(&port->fअगरo_ul);

निकास_in_buffer:
	वापस rval;
पूर्ण

अटल स्थिर काष्ठा tty_port_operations noz_tty_port_ops = अणु
	.activate = ntty_activate,
	.shutकरोwn = ntty_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा tty_operations tty_ops = अणु
	.ioctl = ntty_ioctl,
	.खोलो = ntty_खोलो,
	.बंद = ntty_बंद,
	.hangup = ntty_hangup,
	.ग_लिखो = ntty_ग_लिखो,
	.ग_लिखो_room = ntty_ग_लिखो_room,
	.unthrottle = ntty_unthrottle,
	.throttle = ntty_throttle,
	.अक्षरs_in_buffer = ntty_अक्षरs_in_buffer,
	.tiocmget = ntty_tiocmget,
	.tiocmset = ntty_tiocmset,
	.get_icount = ntty_tiocgicount,
	.install = ntty_install,
	.cleanup = ntty_cleanup,
पूर्ण;

/* Module initialization */
अटल काष्ठा pci_driver nozomi_driver = अणु
	.name = NOZOMI_NAME,
	.id_table = nozomi_pci_tbl,
	.probe = nozomi_card_init,
	.हटाओ = nozomi_card_निकास,
पूर्ण;

अटल __init पूर्णांक nozomi_init(व्योम)
अणु
	पूर्णांक ret;

	ntty_driver = alloc_tty_driver(NTTY_TTY_MAXMINORS);
	अगर (!ntty_driver)
		वापस -ENOMEM;

	ntty_driver->driver_name = NOZOMI_NAME_TTY;
	ntty_driver->name = "noz";
	ntty_driver->major = 0;
	ntty_driver->type = TTY_DRIVER_TYPE_SERIAL;
	ntty_driver->subtype = SERIAL_TYPE_NORMAL;
	ntty_driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	ntty_driver->init_termios = tty_std_termios;
	ntty_driver->init_termios.c_cflag = B115200 | CS8 | CREAD | \
						HUPCL | CLOCAL;
	ntty_driver->init_termios.c_ispeed = 115200;
	ntty_driver->init_termios.c_ospeed = 115200;
	tty_set_operations(ntty_driver, &tty_ops);

	ret = tty_रेजिस्टर_driver(ntty_driver);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Nozomi: failed to register ntty driver\n");
		जाओ मुक्त_tty;
	पूर्ण

	ret = pci_रेजिस्टर_driver(&nozomi_driver);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Nozomi: can't register pci driver\n");
		जाओ unr_tty;
	पूर्ण

	वापस 0;
unr_tty:
	tty_unरेजिस्टर_driver(ntty_driver);
मुक्त_tty:
	put_tty_driver(ntty_driver);
	वापस ret;
पूर्ण

अटल __निकास व्योम nozomi_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&nozomi_driver);
	tty_unरेजिस्टर_driver(ntty_driver);
	put_tty_driver(ntty_driver);
पूर्ण

module_init(nozomi_init);
module_निकास(nozomi_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Nozomi driver");
