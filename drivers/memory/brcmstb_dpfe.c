<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DDR PHY Front End (DPFE) driver क्रम Broadcom set top box SoCs
 *
 * Copyright (c) 2017 Broadcom
 */

/*
 * This driver provides access to the DPFE पूर्णांकerface of Broadcom STB SoCs.
 * The firmware running on the DCPU inside the DDR PHY can provide current
 * inक्रमmation about the प्रणाली's RAM, क्रम instance the DRAM refresh rate.
 * This can be used as an indirect indicator क्रम the DRAM's temperature.
 * Slower refresh rate means cooler RAM, higher refresh rate means hotter
 * RAM.
 *
 * Throughout the driver, we use पढ़ोl_relaxed() and ग_लिखोl_relaxed(), which
 * alपढ़ोy contain the appropriate le32_to_cpu()/cpu_to_le32() calls.
 *
 * Note regarding the loading of the firmware image: we use be32_to_cpu()
 * and le_32_to_cpu(), so we can support the following four हालs:
 *     - LE kernel + LE firmware image (the most common हाल)
 *     - LE kernel + BE firmware image
 *     - BE kernel + LE firmware image
 *     - BE kernel + BE firmware image
 *
 * The DPCU always runs in big endian mode. The firmware image, however, can
 * be in either क्रमmat. Also, communication between host CPU and DCPU is
 * always in little endian.
 */

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRVNAME			"brcmstb-dpfe"

/* DCPU रेजिस्टर offsets */
#घोषणा REG_DCPU_RESET		0x0
#घोषणा REG_TO_DCPU_MBOX	0x10
#घोषणा REG_TO_HOST_MBOX	0x14

/* Macros to process offsets वापसed by the DCPU */
#घोषणा DRAM_MSG_ADDR_OFFSET	0x0
#घोषणा DRAM_MSG_TYPE_OFFSET	0x1c
#घोषणा DRAM_MSG_ADDR_MASK	((1UL << DRAM_MSG_TYPE_OFFSET) - 1)
#घोषणा DRAM_MSG_TYPE_MASK	((1UL << \
				 (BITS_PER_LONG - DRAM_MSG_TYPE_OFFSET)) - 1)

/* Message RAM */
#घोषणा DCPU_MSG_RAM_START	0x100
#घोषणा DCPU_MSG_RAM(x)		(DCPU_MSG_RAM_START + (x) * माप(u32))

/* DRAM Info Offsets & Masks */
#घोषणा DRAM_INFO_INTERVAL	0x0
#घोषणा DRAM_INFO_MR4		0x4
#घोषणा DRAM_INFO_ERROR		0x8
#घोषणा DRAM_INFO_MR4_MASK	0xff
#घोषणा DRAM_INFO_MR4_SHIFT	24	/* We need to look at byte 3 */

/* DRAM MR4 Offsets & Masks */
#घोषणा DRAM_MR4_REFRESH	0x0	/* Refresh rate */
#घोषणा DRAM_MR4_SR_ABORT	0x3	/* Self Refresh Abort */
#घोषणा DRAM_MR4_PPRE		0x4	/* Post-package repair entry/निकास */
#घोषणा DRAM_MR4_TH_OFFS	0x5	/* Thermal Offset; venकरोr specअगरic */
#घोषणा DRAM_MR4_TUF		0x7	/* Temperature Update Flag */

#घोषणा DRAM_MR4_REFRESH_MASK	0x7
#घोषणा DRAM_MR4_SR_ABORT_MASK	0x1
#घोषणा DRAM_MR4_PPRE_MASK	0x1
#घोषणा DRAM_MR4_TH_OFFS_MASK	0x3
#घोषणा DRAM_MR4_TUF_MASK	0x1

/* DRAM Venकरोr Offsets & Masks (API v2) */
#घोषणा DRAM_VENDOR_MR5		0x0
#घोषणा DRAM_VENDOR_MR6		0x4
#घोषणा DRAM_VENDOR_MR7		0x8
#घोषणा DRAM_VENDOR_MR8		0xc
#घोषणा DRAM_VENDOR_ERROR	0x10
#घोषणा DRAM_VENDOR_MASK	0xff
#घोषणा DRAM_VENDOR_SHIFT	24	/* We need to look at byte 3 */

/* DRAM Inक्रमmation Offsets & Masks (API v3) */
#घोषणा DRAM_DDR_INFO_MR4	0x0
#घोषणा DRAM_DDR_INFO_MR5	0x4
#घोषणा DRAM_DDR_INFO_MR6	0x8
#घोषणा DRAM_DDR_INFO_MR7	0xc
#घोषणा DRAM_DDR_INFO_MR8	0x10
#घोषणा DRAM_DDR_INFO_ERROR	0x14
#घोषणा DRAM_DDR_INFO_MASK	0xff

/* Reset रेजिस्टर bits & masks */
#घोषणा DCPU_RESET_SHIFT	0x0
#घोषणा DCPU_RESET_MASK		0x1
#घोषणा DCPU_CLK_DISABLE_SHIFT	0x2

/* DCPU वापस codes */
#घोषणा DCPU_RET_ERROR_BIT	BIT(31)
#घोषणा DCPU_RET_SUCCESS	0x1
#घोषणा DCPU_RET_ERR_HEADER	(DCPU_RET_ERROR_BIT | BIT(0))
#घोषणा DCPU_RET_ERR_INVAL	(DCPU_RET_ERROR_BIT | BIT(1))
#घोषणा DCPU_RET_ERR_CHKSUM	(DCPU_RET_ERROR_BIT | BIT(2))
#घोषणा DCPU_RET_ERR_COMMAND	(DCPU_RET_ERROR_BIT | BIT(3))
/* This error code is not firmware defined and only used in the driver. */
#घोषणा DCPU_RET_ERR_TIMEDOUT	(DCPU_RET_ERROR_BIT | BIT(4))

/* Firmware magic */
#घोषणा DPFE_BE_MAGIC		0xfe1010fe
#घोषणा DPFE_LE_MAGIC		0xfe0101fe

/* Error codes */
#घोषणा ERR_INVALID_MAGIC	-1
#घोषणा ERR_INVALID_SIZE	-2
#घोषणा ERR_INVALID_CHKSUM	-3

/* Message types */
#घोषणा DPFE_MSG_TYPE_COMMAND	1
#घोषणा DPFE_MSG_TYPE_RESPONSE	2

#घोषणा DELAY_LOOP_MAX		1000

क्रमागत dpfe_msg_fields अणु
	MSG_HEADER,
	MSG_COMMAND,
	MSG_ARG_COUNT,
	MSG_ARG0,
	MSG_FIELD_MAX	= 16 /* Max number of arguments */
पूर्ण;

क्रमागत dpfe_commands अणु
	DPFE_CMD_GET_INFO,
	DPFE_CMD_GET_REFRESH,
	DPFE_CMD_GET_VENDOR,
	DPFE_CMD_MAX /* Last entry */
पूर्ण;

/*
 * Format of the binary firmware file:
 *
 *   entry
 *      0    header
 *              value:  0xfe0101fe  <== little endian
 *                      0xfe1010fe  <== big endian
 *      1    sequence:
 *              [31:16] total segments on this build
 *              [15:0]  this segment sequence.
 *      2    FW version
 *      3    IMEM byte size
 *      4    DMEM byte size
 *           IMEM
 *           DMEM
 *      last checksum ==> sum of everything
 */
काष्ठा dpfe_firmware_header अणु
	u32 magic;
	u32 sequence;
	u32 version;
	u32 imem_size;
	u32 dmem_size;
पूर्ण;

/* Things we only need during initialization. */
काष्ठा init_data अणु
	अचिन्हित पूर्णांक dmem_len;
	अचिन्हित पूर्णांक imem_len;
	अचिन्हित पूर्णांक chksum;
	bool is_big_endian;
पूर्ण;

/* API version and corresponding commands */
काष्ठा dpfe_api अणु
	पूर्णांक version;
	स्थिर अक्षर *fw_name;
	स्थिर काष्ठा attribute_group **sysfs_attrs;
	u32 command[DPFE_CMD_MAX][MSG_FIELD_MAX];
पूर्ण;

/* Things we need क्रम as दीर्घ as we are active. */
काष्ठा brcmstb_dpfe_priv अणु
	व्योम __iomem *regs;
	व्योम __iomem *dmem;
	व्योम __iomem *imem;
	काष्ठा device *dev;
	स्थिर काष्ठा dpfe_api *dpfe_api;
	काष्ठा mutex lock;
पूर्ण;

/*
 * Forward declaration of our sysfs attribute functions, so we can declare the
 * attribute data काष्ठाures early.
 */
अटल sमाप_प्रकार show_info(काष्ठा device *, काष्ठा device_attribute *, अक्षर *);
अटल sमाप_प्रकार show_refresh(काष्ठा device *, काष्ठा device_attribute *, अक्षर *);
अटल sमाप_प्रकार store_refresh(काष्ठा device *, काष्ठा device_attribute *,
			  स्थिर अक्षर *, माप_प्रकार);
अटल sमाप_प्रकार show_venकरोr(काष्ठा device *, काष्ठा device_attribute *, अक्षर *);
अटल sमाप_प्रकार show_dram(काष्ठा device *, काष्ठा device_attribute *, अक्षर *);

/*
 * Declare our attributes early, so they can be referenced in the API data
 * काष्ठाure. We need to करो this, because the attributes depend on the API
 * version.
 */
अटल DEVICE_ATTR(dpfe_info, 0444, show_info, शून्य);
अटल DEVICE_ATTR(dpfe_refresh, 0644, show_refresh, store_refresh);
अटल DEVICE_ATTR(dpfe_venकरोr, 0444, show_venकरोr, शून्य);
अटल DEVICE_ATTR(dpfe_dram, 0444, show_dram, शून्य);

/* API v2 sysfs attributes */
अटल काष्ठा attribute *dpfe_v2_attrs[] = अणु
	&dev_attr_dpfe_info.attr,
	&dev_attr_dpfe_refresh.attr,
	&dev_attr_dpfe_venकरोr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(dpfe_v2);

/* API v3 sysfs attributes */
अटल काष्ठा attribute *dpfe_v3_attrs[] = अणु
	&dev_attr_dpfe_info.attr,
	&dev_attr_dpfe_dram.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(dpfe_v3);

/*
 * Old API v2 firmware commands, as defined in the rev 0.61 specअगरication, we
 * use a version set to 1 to denote that it is not compatible with the new API
 * v2 and onwards.
 */
अटल स्थिर काष्ठा dpfe_api dpfe_api_old_v2 = अणु
	.version = 1,
	.fw_name = "dpfe.bin",
	.sysfs_attrs = dpfe_v2_groups,
	.command = अणु
		[DPFE_CMD_GET_INFO] = अणु
			[MSG_HEADER] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 1,
			[MSG_ARG_COUNT] = 1,
			[MSG_ARG0] = 1,
		पूर्ण,
		[DPFE_CMD_GET_REFRESH] = अणु
			[MSG_HEADER] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 2,
			[MSG_ARG_COUNT] = 1,
			[MSG_ARG0] = 1,
		पूर्ण,
		[DPFE_CMD_GET_VENDOR] = अणु
			[MSG_HEADER] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 2,
			[MSG_ARG_COUNT] = 1,
			[MSG_ARG0] = 2,
		पूर्ण,
	पूर्ण
पूर्ण;

/*
 * API v2 firmware commands, as defined in the rev 0.8 specअगरication, named new
 * v2 here
 */
अटल स्थिर काष्ठा dpfe_api dpfe_api_new_v2 = अणु
	.version = 2,
	.fw_name = शून्य, /* We expect the firmware to have been करोwnloaded! */
	.sysfs_attrs = dpfe_v2_groups,
	.command = अणु
		[DPFE_CMD_GET_INFO] = अणु
			[MSG_HEADER] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 0x101,
		पूर्ण,
		[DPFE_CMD_GET_REFRESH] = अणु
			[MSG_HEADER] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 0x201,
		पूर्ण,
		[DPFE_CMD_GET_VENDOR] = अणु
			[MSG_HEADER] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 0x202,
		पूर्ण,
	पूर्ण
पूर्ण;

/* API v3 firmware commands */
अटल स्थिर काष्ठा dpfe_api dpfe_api_v3 = अणु
	.version = 3,
	.fw_name = शून्य, /* We expect the firmware to have been करोwnloaded! */
	.sysfs_attrs = dpfe_v3_groups,
	.command = अणु
		[DPFE_CMD_GET_INFO] = अणु
			[MSG_HEADER] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 0x0101,
			[MSG_ARG_COUNT] = 1,
			[MSG_ARG0] = 1,
		पूर्ण,
		[DPFE_CMD_GET_REFRESH] = अणु
			[MSG_HEADER] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 0x0202,
			[MSG_ARG_COUNT] = 0,
		पूर्ण,
		/* There's no GET_VENDOR command in API v3. */
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *get_error_text(अचिन्हित पूर्णांक i)
अणु
	अटल स्थिर अक्षर * स्थिर error_text[] = अणु
		"Success", "Header code incorrect",
		"Unknown command or argument", "Incorrect checksum",
		"Malformed command", "Timed out", "Unknown error",
	पूर्ण;

	अगर (unlikely(i >= ARRAY_SIZE(error_text)))
		i = ARRAY_SIZE(error_text) - 1;

	वापस error_text[i];
पूर्ण

अटल bool is_dcpu_enabled(काष्ठा brcmstb_dpfe_priv *priv)
अणु
	u32 val;

	mutex_lock(&priv->lock);
	val = पढ़ोl_relaxed(priv->regs + REG_DCPU_RESET);
	mutex_unlock(&priv->lock);

	वापस !(val & DCPU_RESET_MASK);
पूर्ण

अटल व्योम __disable_dcpu(काष्ठा brcmstb_dpfe_priv *priv)
अणु
	u32 val;

	अगर (!is_dcpu_enabled(priv))
		वापस;

	mutex_lock(&priv->lock);

	/* Put DCPU in reset अगर it's running. */
	val = पढ़ोl_relaxed(priv->regs + REG_DCPU_RESET);
	val |= (1 << DCPU_RESET_SHIFT);
	ग_लिखोl_relaxed(val, priv->regs + REG_DCPU_RESET);

	mutex_unlock(&priv->lock);
पूर्ण

अटल व्योम __enable_dcpu(काष्ठा brcmstb_dpfe_priv *priv)
अणु
	व्योम __iomem *regs = priv->regs;
	u32 val;

	mutex_lock(&priv->lock);

	/* Clear mailbox रेजिस्टरs. */
	ग_लिखोl_relaxed(0, regs + REG_TO_DCPU_MBOX);
	ग_लिखोl_relaxed(0, regs + REG_TO_HOST_MBOX);

	/* Disable DCPU घड़ी gating */
	val = पढ़ोl_relaxed(regs + REG_DCPU_RESET);
	val &= ~(1 << DCPU_CLK_DISABLE_SHIFT);
	ग_लिखोl_relaxed(val, regs + REG_DCPU_RESET);

	/* Take DCPU out of reset */
	val = पढ़ोl_relaxed(regs + REG_DCPU_RESET);
	val &= ~(1 << DCPU_RESET_SHIFT);
	ग_लिखोl_relaxed(val, regs + REG_DCPU_RESET);

	mutex_unlock(&priv->lock);
पूर्ण

अटल अचिन्हित पूर्णांक get_msg_chksum(स्थिर u32 msg[], अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक sum = 0;
	अचिन्हित पूर्णांक i;

	/* Don't include the last field in the checksum. */
	क्रम (i = 0; i < max; i++)
		sum += msg[i];

	वापस sum;
पूर्ण

अटल व्योम __iomem *get_msg_ptr(काष्ठा brcmstb_dpfe_priv *priv, u32 response,
				 अक्षर *buf, sमाप_प्रकार *size)
अणु
	अचिन्हित पूर्णांक msg_type;
	अचिन्हित पूर्णांक offset;
	व्योम __iomem *ptr = शून्य;

	/* There is no need to use this function क्रम API v3 or later. */
	अगर (unlikely(priv->dpfe_api->version >= 3))
		वापस शून्य;

	msg_type = (response >> DRAM_MSG_TYPE_OFFSET) & DRAM_MSG_TYPE_MASK;
	offset = (response >> DRAM_MSG_ADDR_OFFSET) & DRAM_MSG_ADDR_MASK;

	/*
	 * msg_type == 1: the offset is relative to the message RAM
	 * msg_type == 0: the offset is relative to the data RAM (this is the
	 *                previous way of passing data)
	 * msg_type is anything अन्यथा: there's critical hardware problem
	 */
	चयन (msg_type) अणु
	हाल 1:
		ptr = priv->regs + DCPU_MSG_RAM_START + offset;
		अवरोध;
	हाल 0:
		ptr = priv->dmem + offset;
		अवरोध;
	शेष:
		dev_emerg(priv->dev, "invalid message reply from DCPU: %#x\n",
			response);
		अगर (buf && size)
			*size = प्र_लिखो(buf,
				"FATAL: communication error with DCPU\n");
	पूर्ण

	वापस ptr;
पूर्ण

अटल व्योम __finalize_command(काष्ठा brcmstb_dpfe_priv *priv)
अणु
	अचिन्हित पूर्णांक release_mbox;

	/*
	 * It depends on the API version which MBOX रेजिस्टर we have to ग_लिखो to
	 * to संकेत we are करोne.
	 */
	release_mbox = (priv->dpfe_api->version < 2)
			? REG_TO_HOST_MBOX : REG_TO_DCPU_MBOX;
	ग_लिखोl_relaxed(0, priv->regs + release_mbox);
पूर्ण

अटल पूर्णांक __send_command(काष्ठा brcmstb_dpfe_priv *priv, अचिन्हित पूर्णांक cmd,
			  u32 result[])
अणु
	स्थिर u32 *msg = priv->dpfe_api->command[cmd];
	व्योम __iomem *regs = priv->regs;
	अचिन्हित पूर्णांक i, chksum, chksum_idx;
	पूर्णांक ret = 0;
	u32 resp;

	अगर (cmd >= DPFE_CMD_MAX)
		वापस -1;

	mutex_lock(&priv->lock);

	/* Wait क्रम DCPU to become पढ़ोy */
	क्रम (i = 0; i < DELAY_LOOP_MAX; i++) अणु
		resp = पढ़ोl_relaxed(regs + REG_TO_HOST_MBOX);
		अगर (resp == 0)
			अवरोध;
		msleep(1);
	पूर्ण
	अगर (resp != 0) अणु
		mutex_unlock(&priv->lock);
		वापस -ffs(DCPU_RET_ERR_TIMEDOUT);
	पूर्ण

	/* Compute checksum over the message */
	chksum_idx = msg[MSG_ARG_COUNT] + MSG_ARG_COUNT + 1;
	chksum = get_msg_chksum(msg, chksum_idx);

	/* Write command and arguments to message area */
	क्रम (i = 0; i < MSG_FIELD_MAX; i++) अणु
		अगर (i == chksum_idx)
			ग_लिखोl_relaxed(chksum, regs + DCPU_MSG_RAM(i));
		अन्यथा
			ग_लिखोl_relaxed(msg[i], regs + DCPU_MSG_RAM(i));
	पूर्ण

	/* Tell DCPU there is a command रुकोing */
	ग_लिखोl_relaxed(1, regs + REG_TO_DCPU_MBOX);

	/* Wait क्रम DCPU to process the command */
	क्रम (i = 0; i < DELAY_LOOP_MAX; i++) अणु
		/* Read response code */
		resp = पढ़ोl_relaxed(regs + REG_TO_HOST_MBOX);
		अगर (resp > 0)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (i == DELAY_LOOP_MAX) अणु
		resp = (DCPU_RET_ERR_TIMEDOUT & ~DCPU_RET_ERROR_BIT);
		ret = -ffs(resp);
	पूर्ण अन्यथा अणु
		/* Read response data */
		क्रम (i = 0; i < MSG_FIELD_MAX; i++)
			result[i] = पढ़ोl_relaxed(regs + DCPU_MSG_RAM(i));
		chksum_idx = result[MSG_ARG_COUNT] + MSG_ARG_COUNT + 1;
	पूर्ण

	/* Tell DCPU we are करोne */
	__finalize_command(priv);

	mutex_unlock(&priv->lock);

	अगर (ret)
		वापस ret;

	/* Verअगरy response */
	chksum = get_msg_chksum(result, chksum_idx);
	अगर (chksum != result[chksum_idx])
		resp = DCPU_RET_ERR_CHKSUM;

	अगर (resp != DCPU_RET_SUCCESS) अणु
		resp &= ~DCPU_RET_ERROR_BIT;
		ret = -ffs(resp);
	पूर्ण

	वापस ret;
पूर्ण

/* Ensure that the firmware file loaded meets all the requirements. */
अटल पूर्णांक __verअगरy_firmware(काष्ठा init_data *init,
			     स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा dpfe_firmware_header *header = (व्योम *)fw->data;
	अचिन्हित पूर्णांक dmem_size, imem_size, total_size;
	bool is_big_endian = false;
	स्थिर u32 *chksum_ptr;

	अगर (header->magic == DPFE_BE_MAGIC)
		is_big_endian = true;
	अन्यथा अगर (header->magic != DPFE_LE_MAGIC)
		वापस ERR_INVALID_MAGIC;

	अगर (is_big_endian) अणु
		dmem_size = be32_to_cpu(header->dmem_size);
		imem_size = be32_to_cpu(header->imem_size);
	पूर्ण अन्यथा अणु
		dmem_size = le32_to_cpu(header->dmem_size);
		imem_size = le32_to_cpu(header->imem_size);
	पूर्ण

	/* Data and inकाष्ठाion sections are 32 bit words. */
	अगर ((dmem_size % माप(u32)) != 0 || (imem_size % माप(u32)) != 0)
		वापस ERR_INVALID_SIZE;

	/*
	 * The header + the data section + the inकाष्ठाion section + the
	 * checksum must be equal to the total firmware size.
	 */
	total_size = dmem_size + imem_size + माप(*header) +
		माप(*chksum_ptr);
	अगर (total_size != fw->size)
		वापस ERR_INVALID_SIZE;

	/* The checksum comes at the very end. */
	chksum_ptr = (व्योम *)fw->data + माप(*header) + dmem_size + imem_size;

	init->is_big_endian = is_big_endian;
	init->dmem_len = dmem_size;
	init->imem_len = imem_size;
	init->chksum = (is_big_endian)
		? be32_to_cpu(*chksum_ptr) : le32_to_cpu(*chksum_ptr);

	वापस 0;
पूर्ण

/* Verअगरy checksum by पढ़ोing back the firmware from co-processor RAM. */
अटल पूर्णांक __verअगरy_fw_checksum(काष्ठा init_data *init,
				काष्ठा brcmstb_dpfe_priv *priv,
				स्थिर काष्ठा dpfe_firmware_header *header,
				u32 checksum)
अणु
	u32 magic, sequence, version, sum;
	u32 __iomem *dmem = priv->dmem;
	u32 __iomem *imem = priv->imem;
	अचिन्हित पूर्णांक i;

	अगर (init->is_big_endian) अणु
		magic = be32_to_cpu(header->magic);
		sequence = be32_to_cpu(header->sequence);
		version = be32_to_cpu(header->version);
	पूर्ण अन्यथा अणु
		magic = le32_to_cpu(header->magic);
		sequence = le32_to_cpu(header->sequence);
		version = le32_to_cpu(header->version);
	पूर्ण

	sum = magic + sequence + version + init->dmem_len + init->imem_len;

	क्रम (i = 0; i < init->dmem_len / माप(u32); i++)
		sum += पढ़ोl_relaxed(dmem + i);

	क्रम (i = 0; i < init->imem_len / माप(u32); i++)
		sum += पढ़ोl_relaxed(imem + i);

	वापस (sum == checksum) ? 0 : -1;
पूर्ण

अटल पूर्णांक __ग_लिखो_firmware(u32 __iomem *mem, स्थिर u32 *fw,
			    अचिन्हित पूर्णांक size, bool is_big_endian)
अणु
	अचिन्हित पूर्णांक i;

	/* Convert size to 32-bit words. */
	size /= माप(u32);

	/* It is recommended to clear the firmware area first. */
	क्रम (i = 0; i < size; i++)
		ग_लिखोl_relaxed(0, mem + i);

	/* Now copy it. */
	अगर (is_big_endian) अणु
		क्रम (i = 0; i < size; i++)
			ग_लिखोl_relaxed(be32_to_cpu(fw[i]), mem + i);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < size; i++)
			ग_लिखोl_relaxed(le32_to_cpu(fw[i]), mem + i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_dpfe_करोwnload_firmware(काष्ठा brcmstb_dpfe_priv *priv)
अणु
	स्थिर काष्ठा dpfe_firmware_header *header;
	अचिन्हित पूर्णांक dmem_size, imem_size;
	काष्ठा device *dev = priv->dev;
	bool is_big_endian = false;
	स्थिर काष्ठा firmware *fw;
	स्थिर u32 *dmem, *imem;
	काष्ठा init_data init;
	स्थिर व्योम *fw_blob;
	पूर्णांक ret;

	/*
	 * Skip करोwnloading the firmware अगर the DCPU is alपढ़ोy running and
	 * responding to commands.
	 */
	अगर (is_dcpu_enabled(priv)) अणु
		u32 response[MSG_FIELD_MAX];

		ret = __send_command(priv, DPFE_CMD_GET_INFO, response);
		अगर (!ret)
			वापस 0;
	पूर्ण

	/*
	 * If the firmware filename is शून्य it means the boot firmware has to
	 * करोwnload the DCPU firmware क्रम us. If that didn't work, we have to
	 * bail, since करोwnloading it ourselves wouldn't work either.
	 */
	अगर (!priv->dpfe_api->fw_name)
		वापस -ENODEV;

	ret = firmware_request_nowarn(&fw, priv->dpfe_api->fw_name, dev);
	/*
	 * Defer the firmware करोwnload अगर the firmware file couldn't be found.
	 * The root file प्रणाली may not be available yet.
	 */
	अगर (ret)
		वापस (ret == -ENOENT) ? -EPROBE_DEFER : ret;

	ret = __verअगरy_firmware(&init, fw);
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ release_fw;
	पूर्ण

	__disable_dcpu(priv);

	is_big_endian = init.is_big_endian;
	dmem_size = init.dmem_len;
	imem_size = init.imem_len;

	/* At the beginning of the firmware blob is a header. */
	header = (काष्ठा dpfe_firmware_header *)fw->data;
	/* Void poपूर्णांकer to the beginning of the actual firmware. */
	fw_blob = fw->data + माप(*header);
	/* IMEM comes right after the header. */
	imem = fw_blob;
	/* DMEM follows after IMEM. */
	dmem = fw_blob + imem_size;

	ret = __ग_लिखो_firmware(priv->dmem, dmem, dmem_size, is_big_endian);
	अगर (ret)
		जाओ release_fw;
	ret = __ग_लिखो_firmware(priv->imem, imem, imem_size, is_big_endian);
	अगर (ret)
		जाओ release_fw;

	ret = __verअगरy_fw_checksum(&init, priv, header, init.chksum);
	अगर (ret)
		जाओ release_fw;

	__enable_dcpu(priv);

release_fw:
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार generic_show(अचिन्हित पूर्णांक command, u32 response[],
			    काष्ठा brcmstb_dpfe_priv *priv, अक्षर *buf)
अणु
	पूर्णांक ret;

	अगर (!priv)
		वापस प्र_लिखो(buf, "ERROR: driver private data not set\n");

	ret = __send_command(priv, command, response);
	अगर (ret < 0)
		वापस प्र_लिखो(buf, "ERROR: %s\n", get_error_text(-ret));

	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_info(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	u32 response[MSG_FIELD_MAX];
	काष्ठा brcmstb_dpfe_priv *priv;
	अचिन्हित पूर्णांक info;
	sमाप_प्रकार ret;

	priv = dev_get_drvdata(dev);
	ret = generic_show(DPFE_CMD_GET_INFO, response, priv, buf);
	अगर (ret)
		वापस ret;

	info = response[MSG_ARG0];

	वापस प्र_लिखो(buf, "%u.%u.%u.%u\n",
		       (info >> 24) & 0xff,
		       (info >> 16) & 0xff,
		       (info >> 8) & 0xff,
		       info & 0xff);
पूर्ण

अटल sमाप_प्रकार show_refresh(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	u32 response[MSG_FIELD_MAX];
	व्योम __iomem *info;
	काष्ठा brcmstb_dpfe_priv *priv;
	u8 refresh, sr_पात, ppre, thermal_offs, tuf;
	u32 mr4;
	sमाप_प्रकार ret;

	priv = dev_get_drvdata(dev);
	ret = generic_show(DPFE_CMD_GET_REFRESH, response, priv, buf);
	अगर (ret)
		वापस ret;

	info = get_msg_ptr(priv, response[MSG_ARG0], buf, &ret);
	अगर (!info)
		वापस ret;

	mr4 = (पढ़ोl_relaxed(info + DRAM_INFO_MR4) >> DRAM_INFO_MR4_SHIFT) &
	       DRAM_INFO_MR4_MASK;

	refresh = (mr4 >> DRAM_MR4_REFRESH) & DRAM_MR4_REFRESH_MASK;
	sr_पात = (mr4 >> DRAM_MR4_SR_ABORT) & DRAM_MR4_SR_ABORT_MASK;
	ppre = (mr4 >> DRAM_MR4_PPRE) & DRAM_MR4_PPRE_MASK;
	thermal_offs = (mr4 >> DRAM_MR4_TH_OFFS) & DRAM_MR4_TH_OFFS_MASK;
	tuf = (mr4 >> DRAM_MR4_TUF) & DRAM_MR4_TUF_MASK;

	वापस प्र_लिखो(buf, "%#x %#x %#x %#x %#x %#x %#x\n",
		       पढ़ोl_relaxed(info + DRAM_INFO_INTERVAL),
		       refresh, sr_पात, ppre, thermal_offs, tuf,
		       पढ़ोl_relaxed(info + DRAM_INFO_ERROR));
पूर्ण

अटल sमाप_प्रकार store_refresh(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 response[MSG_FIELD_MAX];
	काष्ठा brcmstb_dpfe_priv *priv;
	व्योम __iomem *info;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	priv = dev_get_drvdata(dev);
	ret = __send_command(priv, DPFE_CMD_GET_REFRESH, response);
	अगर (ret)
		वापस ret;

	info = get_msg_ptr(priv, response[MSG_ARG0], शून्य, शून्य);
	अगर (!info)
		वापस -EIO;

	ग_लिखोl_relaxed(val, info + DRAM_INFO_INTERVAL);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_venकरोr(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			   अक्षर *buf)
अणु
	u32 response[MSG_FIELD_MAX];
	काष्ठा brcmstb_dpfe_priv *priv;
	व्योम __iomem *info;
	sमाप_प्रकार ret;
	u32 mr5, mr6, mr7, mr8, err;

	priv = dev_get_drvdata(dev);
	ret = generic_show(DPFE_CMD_GET_VENDOR, response, priv, buf);
	अगर (ret)
		वापस ret;

	info = get_msg_ptr(priv, response[MSG_ARG0], buf, &ret);
	अगर (!info)
		वापस ret;

	mr5 = (पढ़ोl_relaxed(info + DRAM_VENDOR_MR5) >> DRAM_VENDOR_SHIFT) &
		DRAM_VENDOR_MASK;
	mr6 = (पढ़ोl_relaxed(info + DRAM_VENDOR_MR6) >> DRAM_VENDOR_SHIFT) &
		DRAM_VENDOR_MASK;
	mr7 = (पढ़ोl_relaxed(info + DRAM_VENDOR_MR7) >> DRAM_VENDOR_SHIFT) &
		DRAM_VENDOR_MASK;
	mr8 = (पढ़ोl_relaxed(info + DRAM_VENDOR_MR8) >> DRAM_VENDOR_SHIFT) &
		DRAM_VENDOR_MASK;
	err = पढ़ोl_relaxed(info + DRAM_VENDOR_ERROR) & DRAM_VENDOR_MASK;

	वापस प्र_लिखो(buf, "%#x %#x %#x %#x %#x\n", mr5, mr6, mr7, mr8, err);
पूर्ण

अटल sमाप_प्रकार show_dram(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	u32 response[MSG_FIELD_MAX];
	काष्ठा brcmstb_dpfe_priv *priv;
	sमाप_प्रकार ret;
	u32 mr4, mr5, mr6, mr7, mr8, err;

	priv = dev_get_drvdata(dev);
	ret = generic_show(DPFE_CMD_GET_REFRESH, response, priv, buf);
	अगर (ret)
		वापस ret;

	mr4 = response[MSG_ARG0 + 0] & DRAM_INFO_MR4_MASK;
	mr5 = response[MSG_ARG0 + 1] & DRAM_DDR_INFO_MASK;
	mr6 = response[MSG_ARG0 + 2] & DRAM_DDR_INFO_MASK;
	mr7 = response[MSG_ARG0 + 3] & DRAM_DDR_INFO_MASK;
	mr8 = response[MSG_ARG0 + 4] & DRAM_DDR_INFO_MASK;
	err = response[MSG_ARG0 + 5] & DRAM_DDR_INFO_MASK;

	वापस प्र_लिखो(buf, "%#x %#x %#x %#x %#x %#x\n", mr4, mr5, mr6, mr7,
			mr8, err);
पूर्ण

अटल पूर्णांक brcmstb_dpfe_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा brcmstb_dpfe_priv *priv = platक्रमm_get_drvdata(pdev);

	वापस brcmstb_dpfe_करोwnload_firmware(priv);
पूर्ण

अटल पूर्णांक brcmstb_dpfe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा brcmstb_dpfe_priv *priv;
	काष्ठा resource *res;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;

	mutex_init(&priv->lock);
	platक्रमm_set_drvdata(pdev, priv);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dpfe-cpu");
	priv->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->regs)) अणु
		dev_err(dev, "couldn't map DCPU registers\n");
		वापस -ENODEV;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dpfe-dmem");
	priv->dmem = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->dmem)) अणु
		dev_err(dev, "Couldn't map DCPU data memory\n");
		वापस -ENOENT;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dpfe-imem");
	priv->imem = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->imem)) अणु
		dev_err(dev, "Couldn't map DCPU instruction memory\n");
		वापस -ENOENT;
	पूर्ण

	priv->dpfe_api = of_device_get_match_data(dev);
	अगर (unlikely(!priv->dpfe_api)) अणु
		/*
		 * It should be impossible to end up here, but to be safe we
		 * check anyway.
		 */
		dev_err(dev, "Couldn't determine API\n");
		वापस -ENOENT;
	पूर्ण

	ret = brcmstb_dpfe_करोwnload_firmware(priv);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "Couldn't download firmware\n");

	ret = sysfs_create_groups(&pdev->dev.kobj, priv->dpfe_api->sysfs_attrs);
	अगर (!ret)
		dev_info(dev, "registered with API v%d.\n",
			 priv->dpfe_api->version);

	वापस ret;
पूर्ण

अटल पूर्णांक brcmstb_dpfe_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा brcmstb_dpfe_priv *priv = dev_get_drvdata(&pdev->dev);

	sysfs_हटाओ_groups(&pdev->dev.kobj, priv->dpfe_api->sysfs_attrs);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id brcmstb_dpfe_of_match[] = अणु
	/* Use legacy API v2 क्रम a select number of chips */
	अणु .compatible = "brcm,bcm7268-dpfe-cpu", .data = &dpfe_api_old_v2 पूर्ण,
	अणु .compatible = "brcm,bcm7271-dpfe-cpu", .data = &dpfe_api_old_v2 पूर्ण,
	अणु .compatible = "brcm,bcm7278-dpfe-cpu", .data = &dpfe_api_old_v2 पूर्ण,
	अणु .compatible = "brcm,bcm7211-dpfe-cpu", .data = &dpfe_api_new_v2 पूर्ण,
	/* API v3 is the शेष going क्रमward */
	अणु .compatible = "brcm,dpfe-cpu", .data = &dpfe_api_v3 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, brcmstb_dpfe_of_match);

अटल काष्ठा platक्रमm_driver brcmstb_dpfe_driver = अणु
	.driver	= अणु
		.name = DRVNAME,
		.of_match_table = brcmstb_dpfe_of_match,
	पूर्ण,
	.probe = brcmstb_dpfe_probe,
	.हटाओ	= brcmstb_dpfe_हटाओ,
	.resume = brcmstb_dpfe_resume,
पूर्ण;

module_platक्रमm_driver(brcmstb_dpfe_driver);

MODULE_AUTHOR("Markus Mayer <mmayer@broadcom.com>");
MODULE_DESCRIPTION("BRCMSTB DDR PHY Front End Driver");
MODULE_LICENSE("GPL");
