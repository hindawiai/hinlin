<शैली गुरु>
/*****************************************************************************
 *
 *     Author: Xilinx, Inc.
 *
 *     This program is मुक्त software; you can redistribute it and/or modअगरy it
 *     under the terms of the GNU General Public License as published by the
 *     Free Software Foundation; either version 2 of the License, or (at your
 *     option) any later version.
 *
 *     XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
 *     AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND
 *     SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,
 *     OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,
 *     APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION
 *     THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
 *     AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
 *     FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
 *     WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
 *     IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
 *     REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
 *     INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *     FOR A PARTICULAR PURPOSE.
 *
 *     (c) Copyright 2003-2007 Xilinx Inc.
 *     All rights reserved.
 *
 *     You should have received a copy of the GNU General Public License aदीर्घ
 *     with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 *     675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *****************************************************************************/

#अगर_अघोषित XILINX_HWICAP_H_	/* prevent circular inclusions */
#घोषणा XILINX_HWICAP_H_	/* by using protection macros */

#समावेश <linux/types.h>
#समावेश <linux/cdev.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/पन.स>

काष्ठा hwicap_drvdata अणु
	u32 ग_लिखो_buffer_in_use;  /* Always in [0,3] */
	u8 ग_लिखो_buffer[4];
	u32 पढ़ो_buffer_in_use;	  /* Always in [0,3] */
	u8 पढ़ो_buffer[4];
	resource_माप_प्रकार mem_start;/* phys. address of the control रेजिस्टरs */
	resource_माप_प्रकार mem_end;  /* phys. address of the control रेजिस्टरs */
	resource_माप_प्रकार mem_size;
	व्योम __iomem *base_address;/* virt. address of the control रेजिस्टरs */

	काष्ठा device *dev;
	काष्ठा cdev cdev;	/* Char device काष्ठाure */
	dev_t devt;

	स्थिर काष्ठा hwicap_driver_config *config;
	स्थिर काष्ठा config_रेजिस्टरs *config_regs;
	व्योम *निजी_data;
	bool is_खोलो;
	काष्ठा mutex sem;
पूर्ण;

काष्ठा hwicap_driver_config अणु
	/* Read configuration data given by size पूर्णांकo the data buffer.
	 * Return 0 अगर successful.
	 */
	पूर्णांक (*get_configuration)(काष्ठा hwicap_drvdata *drvdata, u32 *data,
			u32 size);
	/* Write configuration data given by size from the data buffer.
	 * Return 0 अगर successful.
	 */
	पूर्णांक (*set_configuration)(काष्ठा hwicap_drvdata *drvdata, u32 *data,
			u32 size);
	/* Get the status रेजिस्टर, bit pattern given by:
	 * D8 - 0 = configuration error
	 * D7 - 1 = alignment found
	 * D6 - 1 = पढ़ोback in progress
	 * D5 - 0 = पात in progress
	 * D4 - Always 1
	 * D3 - Always 1
	 * D2 - Always 1
	 * D1 - Always 1
	 * D0 - 1 = operation completed
	 */
	u32 (*get_status)(काष्ठा hwicap_drvdata *drvdata);
	/* Reset the hw */
	व्योम (*reset)(काष्ठा hwicap_drvdata *drvdata);
पूर्ण;

/* Number of बार to poll the करोne रेजिस्टर. This has to be large
 * enough to allow an entire configuration to complete. If an entire
 * page (4kb) is configured at once, that could take up to 4k cycles
 * with a byte-wide icap पूर्णांकerface. In most हालs, this driver is
 * used with a much smaller fअगरo, but this should be sufficient in the
 * worst हाल.
 */
#घोषणा XHI_MAX_RETRIES     5000

/************ Constant Definitions *************/

#घोषणा XHI_PAD_FRAMES              0x1

/* Mask क्रम calculating configuration packet headers */
#घोषणा XHI_WORD_COUNT_MASK_TYPE_1  0x7FFUL
#घोषणा XHI_WORD_COUNT_MASK_TYPE_2  0x1FFFFFUL
#घोषणा XHI_TYPE_MASK               0x7
#घोषणा XHI_REGISTER_MASK           0xF
#घोषणा XHI_OP_MASK                 0x3

#घोषणा XHI_TYPE_SHIFT              29
#घोषणा XHI_REGISTER_SHIFT          13
#घोषणा XHI_OP_SHIFT                27

#घोषणा XHI_TYPE_1                  1
#घोषणा XHI_TYPE_2                  2
#घोषणा XHI_OP_WRITE                2
#घोषणा XHI_OP_READ                 1

/* Address Block Types */
#घोषणा XHI_FAR_CLB_BLOCK           0
#घोषणा XHI_FAR_BRAM_BLOCK          1
#घोषणा XHI_FAR_BRAM_INT_BLOCK      2

काष्ठा config_रेजिस्टरs अणु
	u32 CRC;
	u32 FAR;
	u32 FDRI;
	u32 FDRO;
	u32 CMD;
	u32 CTL;
	u32 MASK;
	u32 STAT;
	u32 LOUT;
	u32 COR;
	u32 MFWR;
	u32 FLR;
	u32 KEY;
	u32 CBC;
	u32 IDCODE;
	u32 AXSS;
	u32 C0R_1;
	u32 CSOB;
	u32 WBSTAR;
	u32 TIMER;
	u32 BOOTSTS;
	u32 CTL_1;
पूर्ण;

/* Configuration Commands */
#घोषणा XHI_CMD_शून्य                0
#घोषणा XHI_CMD_WCFG                1
#घोषणा XHI_CMD_MFW                 2
#घोषणा XHI_CMD_DGHIGH              3
#घोषणा XHI_CMD_RCFG                4
#घोषणा XHI_CMD_START               5
#घोषणा XHI_CMD_RCAP                6
#घोषणा XHI_CMD_RCRC                7
#घोषणा XHI_CMD_AGHIGH              8
#घोषणा XHI_CMD_SWITCH              9
#घोषणा XHI_CMD_GRESTORE            10
#घोषणा XHI_CMD_SHUTDOWN            11
#घोषणा XHI_CMD_GCAPTURE            12
#घोषणा XHI_CMD_DESYNCH             13
#घोषणा XHI_CMD_IPROG               15 /* Only in Virtex5 */
#घोषणा XHI_CMD_CRCC                16 /* Only in Virtex5 */
#घोषणा XHI_CMD_LTIMER              17 /* Only in Virtex5 */

/* Packet स्थिरants */
#घोषणा XHI_SYNC_PACKET             0xAA995566UL
#घोषणा XHI_DUMMY_PACKET            0xFFFFFFFFUL
#घोषणा XHI_NOOP_PACKET             (XHI_TYPE_1 << XHI_TYPE_SHIFT)
#घोषणा XHI_TYPE_2_READ ((XHI_TYPE_2 << XHI_TYPE_SHIFT) | \
			(XHI_OP_READ << XHI_OP_SHIFT))

#घोषणा XHI_TYPE_2_WRITE ((XHI_TYPE_2 << XHI_TYPE_SHIFT) | \
			(XHI_OP_WRITE << XHI_OP_SHIFT))

#घोषणा XHI_TYPE2_CNT_MASK          0x07FFFFFF

#घोषणा XHI_TYPE_1_PACKET_MAX_WORDS 2047UL
#घोषणा XHI_TYPE_1_HEADER_BYTES     4
#घोषणा XHI_TYPE_2_HEADER_BYTES     8

/* Constant to use क्रम CRC check when CRC has been disabled */
#घोषणा XHI_DISABLED_AUTO_CRC       0x0000DEFCUL

/* Meanings of the bits वापसed by get_status */
#घोषणा XHI_SR_CFGERR_N_MASK 0x00000100 /* Config Error Mask */
#घोषणा XHI_SR_DALIGN_MASK 0x00000080 /* Data Alignment Mask */
#घोषणा XHI_SR_RIP_MASK 0x00000040 /* Read back Mask */
#घोषणा XHI_SR_IN_ABORT_N_MASK 0x00000020 /* Select Map Abort Mask */
#घोषणा XHI_SR_DONE_MASK 0x00000001 /* Done bit Mask  */

/**
 * hwicap_type_1_पढ़ो - Generates a Type 1 पढ़ो packet header.
 * @reg: is the address of the रेजिस्टर to be पढ़ो back.
 *
 * Return:
 * Generates a Type 1 पढ़ो packet header, which is used to indirectly
 * पढ़ो रेजिस्टरs in the configuration logic.  This packet must then
 * be sent through the icap device, and a वापस packet received with
 * the inक्रमmation.
 */
अटल अंतरभूत u32 hwicap_type_1_पढ़ो(u32 reg)
अणु
	वापस (XHI_TYPE_1 << XHI_TYPE_SHIFT) |
		(reg << XHI_REGISTER_SHIFT) |
		(XHI_OP_READ << XHI_OP_SHIFT);
पूर्ण

/**
 * hwicap_type_1_ग_लिखो - Generates a Type 1 ग_लिखो packet header
 * @reg: is the address of the रेजिस्टर to be पढ़ो back.
 *
 * Return: Type 1 ग_लिखो packet header
 */
अटल अंतरभूत u32 hwicap_type_1_ग_लिखो(u32 reg)
अणु
	वापस (XHI_TYPE_1 << XHI_TYPE_SHIFT) |
		(reg << XHI_REGISTER_SHIFT) |
		(XHI_OP_WRITE << XHI_OP_SHIFT);
पूर्ण

#पूर्ण_अगर
