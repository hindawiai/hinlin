<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016-2017, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _QCOM_BAM_DMA_H
#घोषणा _QCOM_BAM_DMA_H

#समावेश <यंत्र/byteorder.h>

/*
 * This data type corresponds to the native Command Element
 * supported by BAM DMA Engine.
 *
 * @cmd_and_addr - upper 8 bits command and lower 24 bits रेजिस्टर address.
 * @data - क्रम ग_लिखो command: content to be written पूर्णांकo peripheral रेजिस्टर.
 *	   क्रम पढ़ो command: dest addr to ग_लिखो peripheral रेजिस्टर value.
 * @mask - रेजिस्टर mask.
 * @reserved - क्रम future usage.
 *
 */
काष्ठा bam_cmd_element अणु
	__le32 cmd_and_addr;
	__le32 data;
	__le32 mask;
	__le32 reserved;
पूर्ण;

/*
 * This क्रमागत indicates the command type in a command element
 */
क्रमागत bam_command_type अणु
	BAM_WRITE_COMMAND = 0,
	BAM_READ_COMMAND,
पूर्ण;

/*
 * prep_bam_ce_le32 - Wrapper function to prepare a single BAM command
 * element with the data alपढ़ोy in le32 क्रमmat.
 *
 * @bam_ce: bam command element
 * @addr: target address
 * @cmd: BAM command
 * @data: actual data क्रम ग_लिखो and dest addr क्रम पढ़ो in le32
 */
अटल अंतरभूत व्योम
bam_prep_ce_le32(काष्ठा bam_cmd_element *bam_ce, u32 addr,
		 क्रमागत bam_command_type cmd, __le32 data)
अणु
	bam_ce->cmd_and_addr =
		cpu_to_le32((addr & 0xffffff) | ((cmd & 0xff) << 24));
	bam_ce->data = data;
	bam_ce->mask = cpu_to_le32(0xffffffff);
पूर्ण

/*
 * bam_prep_ce - Wrapper function to prepare a single BAM command element
 * with the data.
 *
 * @bam_ce: BAM command element
 * @addr: target address
 * @cmd: BAM command
 * @data: actual data क्रम ग_लिखो and dest addr क्रम पढ़ो
 */
अटल अंतरभूत व्योम
bam_prep_ce(काष्ठा bam_cmd_element *bam_ce, u32 addr,
	    क्रमागत bam_command_type cmd, u32 data)
अणु
	bam_prep_ce_le32(bam_ce, addr, cmd, cpu_to_le32(data));
पूर्ण
#पूर्ण_अगर
