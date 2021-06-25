<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * EEPROM driver क्रम RAVE SP
 *
 * Copyright (C) 2018 Zodiac Inflight Innovations
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/rave-sp.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sizes.h>

/**
 * क्रमागत rave_sp_eeprom_access_type - Supported types of EEPROM access
 *
 * @RAVE_SP_EEPROM_WRITE:	EEPROM ग_लिखो
 * @RAVE_SP_EEPROM_READ:	EEPROM पढ़ो
 */
क्रमागत rave_sp_eeprom_access_type अणु
	RAVE_SP_EEPROM_WRITE = 0,
	RAVE_SP_EEPROM_READ  = 1,
पूर्ण;

/**
 * क्रमागत rave_sp_eeprom_header_size - EEPROM command header sizes
 *
 * @RAVE_SP_EEPROM_HEADER_SMALL: EEPROM header size क्रम "small" devices (< 8K)
 * @RAVE_SP_EEPROM_HEADER_BIG:	 EEPROM header size क्रम "big" devices (> 8K)
 */
क्रमागत rave_sp_eeprom_header_size अणु
	RAVE_SP_EEPROM_HEADER_SMALL = 4U,
	RAVE_SP_EEPROM_HEADER_BIG   = 5U,
पूर्ण;
#घोषणा RAVE_SP_EEPROM_HEADER_MAX	RAVE_SP_EEPROM_HEADER_BIG

#घोषणा	RAVE_SP_EEPROM_PAGE_SIZE	32U

/**
 * काष्ठा rave_sp_eeprom_page - RAVE SP EEPROM page
 *
 * @type:	Access type (see क्रमागत rave_sp_eeprom_access_type)
 * @success:	Success flag (Success = 1, Failure = 0)
 * @data:	Read data

 * Note this काष्ठाure corresponds to RSP_*_EEPROM payload from RAVE
 * SP ICD
 */
काष्ठा rave_sp_eeprom_page अणु
	u8  type;
	u8  success;
	u8  data[RAVE_SP_EEPROM_PAGE_SIZE];
पूर्ण __packed;

/**
 * काष्ठा rave_sp_eeprom - RAVE SP EEPROM device
 *
 * @sp:			Poपूर्णांकer to parent RAVE SP device
 * @mutex:		Lock protecting access to EEPROM
 * @address:		EEPROM device address
 * @header_size:	Size of EEPROM command header क्रम this device
 * @dev:		Poपूर्णांकer to corresponding काष्ठा device used क्रम logging
 */
काष्ठा rave_sp_eeprom अणु
	काष्ठा rave_sp *sp;
	काष्ठा mutex mutex;
	u8 address;
	अचिन्हित पूर्णांक header_size;
	काष्ठा device *dev;
पूर्ण;

/**
 * rave_sp_eeprom_io - Low-level part of EEPROM page access
 *
 * @eeprom:	EEPROM device to ग_लिखो to
 * @type:	EEPROM access type (पढ़ो or ग_लिखो)
 * @idx:	number of the EEPROM page
 * @page:	Data to ग_लिखो or buffer to store result (via page->data)
 *
 * This function करोes all of the low-level work required to perक्रमm a
 * EEPROM access. This includes क्रमmatting correct command payload,
 * sending it and checking received results.
 *
 * Returns zero in हाल of success or negative error code in
 * हाल of failure.
 */
अटल पूर्णांक rave_sp_eeprom_io(काष्ठा rave_sp_eeprom *eeprom,
			     क्रमागत rave_sp_eeprom_access_type type,
			     u16 idx,
			     काष्ठा rave_sp_eeprom_page *page)
अणु
	स्थिर bool is_ग_लिखो = type == RAVE_SP_EEPROM_WRITE;
	स्थिर अचिन्हित पूर्णांक data_size = is_ग_लिखो ? माप(page->data) : 0;
	स्थिर अचिन्हित पूर्णांक cmd_size = eeprom->header_size + data_size;
	स्थिर अचिन्हित पूर्णांक rsp_size =
		is_ग_लिखो ? माप(*page) - माप(page->data) : माप(*page);
	अचिन्हित पूर्णांक offset = 0;
	u8 cmd[RAVE_SP_EEPROM_HEADER_MAX + माप(page->data)];
	पूर्णांक ret;

	अगर (WARN_ON(cmd_size > माप(cmd)))
		वापस -EINVAL;

	cmd[offset++] = eeprom->address;
	cmd[offset++] = 0;
	cmd[offset++] = type;
	cmd[offset++] = idx;

	/*
	 * If there's still room in this command's header it means we
	 * are talkin to EEPROM that uses 16-bit page numbers and we
	 * have to specअगरy index's MSB in payload as well.
	 */
	अगर (offset < eeprom->header_size)
		cmd[offset++] = idx >> 8;
	/*
	 * Copy our data to ग_लिखो to command buffer first. In हाल of
	 * a पढ़ो data_size should be zero and स_नकल would become a
	 * no-op
	 */
	स_नकल(&cmd[offset], page->data, data_size);

	ret = rave_sp_exec(eeprom->sp, cmd, cmd_size, page, rsp_size);
	अगर (ret)
		वापस ret;

	अगर (page->type != type)
		वापस -EPROTO;

	अगर (!page->success)
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * rave_sp_eeprom_page_access - Access single EEPROM page
 *
 * @eeprom:	EEPROM device to access
 * @type:	Access type to perक्रमm (पढ़ो or ग_लिखो)
 * @offset:	Offset within EEPROM to access
 * @data:	Data buffer
 * @data_len:	Size of the data buffer
 *
 * This function perक्रमms a generic access to a single page or a
 * portion thereof. Requested access MUST NOT cross the EEPROM page
 * boundary.
 *
 * Returns zero in हाल of success or negative error code in
 * हाल of failure.
 */
अटल पूर्णांक
rave_sp_eeprom_page_access(काष्ठा rave_sp_eeprom *eeprom,
			   क्रमागत rave_sp_eeprom_access_type type,
			   अचिन्हित पूर्णांक offset, u8 *data,
			   माप_प्रकार data_len)
अणु
	स्थिर अचिन्हित पूर्णांक page_offset = offset % RAVE_SP_EEPROM_PAGE_SIZE;
	स्थिर अचिन्हित पूर्णांक page_nr     = offset / RAVE_SP_EEPROM_PAGE_SIZE;
	काष्ठा rave_sp_eeprom_page page;
	पूर्णांक ret;

	/*
	 * This function will not work अगर data access we've been asked
	 * to करो is crossing EEPROM page boundary. Normally this
	 * should never happen and getting here would indicate a bug
	 * in the code.
	 */
	अगर (WARN_ON(data_len > माप(page.data) - page_offset))
		वापस -EINVAL;

	अगर (type == RAVE_SP_EEPROM_WRITE) अणु
		/*
		 * If करोing a partial ग_लिखो we need to करो a पढ़ो first
		 * to fill the rest of the page with correct data.
		 */
		अगर (data_len < RAVE_SP_EEPROM_PAGE_SIZE) अणु
			ret = rave_sp_eeprom_io(eeprom, RAVE_SP_EEPROM_READ,
						page_nr, &page);
			अगर (ret)
				वापस ret;
		पूर्ण

		स_नकल(&page.data[page_offset], data, data_len);
	पूर्ण

	ret = rave_sp_eeprom_io(eeprom, type, page_nr, &page);
	अगर (ret)
		वापस ret;

	/*
	 * Since we receive the result of the पढ़ो via 'page.data'
	 * buffer we need to copy that to 'data'
	 */
	अगर (type == RAVE_SP_EEPROM_READ)
		स_नकल(data, &page.data[page_offset], data_len);

	वापस 0;
पूर्ण

/**
 * rave_sp_eeprom_access - Access EEPROM data
 *
 * @eeprom:	EEPROM device to access
 * @type:	Access type to perक्रमm (पढ़ो or ग_लिखो)
 * @offset:	Offset within EEPROM to access
 * @data:	Data buffer
 * @data_len:	Size of the data buffer
 *
 * This function perक्रमms a generic access (either पढ़ो or ग_लिखो) at
 * arbitrary offset (not necessary page aligned) of arbitrary length
 * (is not स्थिरrained by EEPROM page size).
 *
 * Returns zero in हाल of success or negative error code in हाल of
 * failure.
 */
अटल पूर्णांक rave_sp_eeprom_access(काष्ठा rave_sp_eeprom *eeprom,
				 क्रमागत rave_sp_eeprom_access_type type,
				 अचिन्हित पूर्णांक offset, u8 *data,
				 अचिन्हित पूर्णांक data_len)
अणु
	अचिन्हित पूर्णांक residue;
	अचिन्हित पूर्णांक chunk;
	अचिन्हित पूर्णांक head;
	पूर्णांक ret;

	mutex_lock(&eeprom->mutex);

	head    = offset % RAVE_SP_EEPROM_PAGE_SIZE;
	residue = data_len;

	करो अणु
		/*
		 * First iteration, अगर we are करोing an access that is
		 * not 32-byte aligned, we need to access only data up
		 * to a page boundary to aव्योम corssing it in
		 * rave_sp_eeprom_page_access()
		 */
		अगर (unlikely(head)) अणु
			chunk = RAVE_SP_EEPROM_PAGE_SIZE - head;
			/*
			 * This can only happen once per
			 * rave_sp_eeprom_access() call, so we set
			 * head to zero to process all the other
			 * iterations normally.
			 */
			head  = 0;
		पूर्ण अन्यथा अणु
			chunk = RAVE_SP_EEPROM_PAGE_SIZE;
		पूर्ण

		/*
		 * We should never पढ़ो more that 'residue' bytes
		 */
		chunk = min(chunk, residue);
		ret = rave_sp_eeprom_page_access(eeprom, type, offset,
						 data, chunk);
		अगर (ret)
			जाओ out;

		residue -= chunk;
		offset  += chunk;
		data    += chunk;
	पूर्ण जबतक (residue);
out:
	mutex_unlock(&eeprom->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक rave_sp_eeprom_reg_पढ़ो(व्योम *eeprom, अचिन्हित पूर्णांक offset,
				   व्योम *val, माप_प्रकार bytes)
अणु
	वापस rave_sp_eeprom_access(eeprom, RAVE_SP_EEPROM_READ,
				     offset, val, bytes);
पूर्ण

अटल पूर्णांक rave_sp_eeprom_reg_ग_लिखो(व्योम *eeprom, अचिन्हित पूर्णांक offset,
				    व्योम *val, माप_प्रकार bytes)
अणु
	वापस rave_sp_eeprom_access(eeprom, RAVE_SP_EEPROM_WRITE,
				     offset, val, bytes);
पूर्ण

अटल पूर्णांक rave_sp_eeprom_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rave_sp *sp = dev_get_drvdata(dev->parent);
	काष्ठा device_node *np = dev->of_node;
	काष्ठा nvmem_config config = अणु 0 पूर्ण;
	काष्ठा rave_sp_eeprom *eeprom;
	काष्ठा nvmem_device *nvmem;
	u32 reg[2], size;

	अगर (of_property_पढ़ो_u32_array(np, "reg", reg, ARRAY_SIZE(reg))) अणु
		dev_err(dev, "Failed to parse \"reg\" property\n");
		वापस -EINVAL;
	पूर्ण

	size = reg[1];
	/*
	 * Per ICD, we have no more than 2 bytes to specअगरy EEPROM
	 * page.
	 */
	अगर (size > U16_MAX * RAVE_SP_EEPROM_PAGE_SIZE) अणु
		dev_err(dev, "Specified size is too big\n");
		वापस -EINVAL;
	पूर्ण

	eeprom = devm_kzalloc(dev, माप(*eeprom), GFP_KERNEL);
	अगर (!eeprom)
		वापस -ENOMEM;

	eeprom->address = reg[0];
	eeprom->sp      = sp;
	eeprom->dev     = dev;

	अगर (size > SZ_8K)
		eeprom->header_size = RAVE_SP_EEPROM_HEADER_BIG;
	अन्यथा
		eeprom->header_size = RAVE_SP_EEPROM_HEADER_SMALL;

	mutex_init(&eeprom->mutex);

	config.id		= -1;
	of_property_पढ़ो_string(np, "zii,eeprom-name", &config.name);
	config.priv		= eeprom;
	config.dev		= dev;
	config.size		= size;
	config.reg_पढ़ो		= rave_sp_eeprom_reg_पढ़ो;
	config.reg_ग_लिखो	= rave_sp_eeprom_reg_ग_लिखो;
	config.word_size	= 1;
	config.stride		= 1;

	nvmem = devm_nvmem_रेजिस्टर(dev, &config);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल स्थिर काष्ठा of_device_id rave_sp_eeprom_of_match[] = अणु
	अणु .compatible = "zii,rave-sp-eeprom" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rave_sp_eeprom_of_match);

अटल काष्ठा platक्रमm_driver rave_sp_eeprom_driver = अणु
	.probe = rave_sp_eeprom_probe,
	.driver	= अणु
		.name = KBUILD_MODNAME,
		.of_match_table = rave_sp_eeprom_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rave_sp_eeprom_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrey Vostrikov <andrey.vostrikov@cogentembedded.com>");
MODULE_AUTHOR("Nikita Yushchenko <nikita.yoush@cogentembedded.com>");
MODULE_AUTHOR("Andrey Smirnov <andrew.smirnov@gmail.com>");
MODULE_DESCRIPTION("RAVE SP EEPROM driver");
