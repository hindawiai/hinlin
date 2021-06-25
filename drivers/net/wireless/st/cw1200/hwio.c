<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Low-level device IO routines क्रम ST-Ericsson CW1200 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 *
 * Based on:
 * ST-Ericsson UMAC CW1200 driver, which is
 * Copyright (c) 2010, ST-Ericsson
 * Author: Ajitpal Singh <ajitpal.singh@lockless.no>
 */

#समावेश <linux/types.h>

#समावेश "cw1200.h"
#समावेश "hwio.h"
#समावेश "hwbus.h"

 /* Sdio addr is 4*spi_addr */
#घोषणा SPI_REG_ADDR_TO_SDIO(spi_reg_addr) ((spi_reg_addr) << 2)
#घोषणा SDIO_ADDR17BIT(buf_id, mpf, rfu, reg_id_ofs) \
				((((buf_id)    & 0x1F) << 7) \
				| (((mpf)        & 1) << 6) \
				| (((rfu)        & 1) << 5) \
				| (((reg_id_ofs) & 0x1F) << 0))
#घोषणा MAX_RETRY		3


अटल पूर्णांक __cw1200_reg_पढ़ो(काष्ठा cw1200_common *priv, u16 addr,
			     व्योम *buf, माप_प्रकार buf_len, पूर्णांक buf_id)
अणु
	u16 addr_sdio;
	u32 sdio_reg_addr_17bit;

	/* Check अगर buffer is aligned to 4 byte boundary */
	अगर (WARN_ON(((अचिन्हित दीर्घ)buf & 3) && (buf_len > 4))) अणु
		pr_err("buffer is not aligned.\n");
		वापस -EINVAL;
	पूर्ण

	/* Convert to SDIO Register Address */
	addr_sdio = SPI_REG_ADDR_TO_SDIO(addr);
	sdio_reg_addr_17bit = SDIO_ADDR17BIT(buf_id, 0, 0, addr_sdio);

	वापस priv->hwbus_ops->hwbus_स_नकल_fromio(priv->hwbus_priv,
						  sdio_reg_addr_17bit,
						  buf, buf_len);
पूर्ण

अटल पूर्णांक __cw1200_reg_ग_लिखो(काष्ठा cw1200_common *priv, u16 addr,
				स्थिर व्योम *buf, माप_प्रकार buf_len, पूर्णांक buf_id)
अणु
	u16 addr_sdio;
	u32 sdio_reg_addr_17bit;

	/* Convert to SDIO Register Address */
	addr_sdio = SPI_REG_ADDR_TO_SDIO(addr);
	sdio_reg_addr_17bit = SDIO_ADDR17BIT(buf_id, 0, 0, addr_sdio);

	वापस priv->hwbus_ops->hwbus_स_नकल_toio(priv->hwbus_priv,
						sdio_reg_addr_17bit,
						buf, buf_len);
पूर्ण

अटल अंतरभूत पूर्णांक __cw1200_reg_पढ़ो_32(काष्ठा cw1200_common *priv,
					u16 addr, u32 *val)
अणु
	__le32 पंचांगp;
	पूर्णांक i = __cw1200_reg_पढ़ो(priv, addr, &पंचांगp, माप(पंचांगp), 0);
	*val = le32_to_cpu(पंचांगp);
	वापस i;
पूर्ण

अटल अंतरभूत पूर्णांक __cw1200_reg_ग_लिखो_32(काष्ठा cw1200_common *priv,
					u16 addr, u32 val)
अणु
	__le32 पंचांगp = cpu_to_le32(val);
	वापस __cw1200_reg_ग_लिखो(priv, addr, &पंचांगp, माप(पंचांगp), 0);
पूर्ण

अटल अंतरभूत पूर्णांक __cw1200_reg_पढ़ो_16(काष्ठा cw1200_common *priv,
					u16 addr, u16 *val)
अणु
	__le16 पंचांगp;
	पूर्णांक i = __cw1200_reg_पढ़ो(priv, addr, &पंचांगp, माप(पंचांगp), 0);
	*val = le16_to_cpu(पंचांगp);
	वापस i;
पूर्ण

अटल अंतरभूत पूर्णांक __cw1200_reg_ग_लिखो_16(काष्ठा cw1200_common *priv,
					u16 addr, u16 val)
अणु
	__le16 पंचांगp = cpu_to_le16(val);
	वापस __cw1200_reg_ग_लिखो(priv, addr, &पंचांगp, माप(पंचांगp), 0);
पूर्ण

पूर्णांक cw1200_reg_पढ़ो(काष्ठा cw1200_common *priv, u16 addr, व्योम *buf,
			माप_प्रकार buf_len)
अणु
	पूर्णांक ret;
	priv->hwbus_ops->lock(priv->hwbus_priv);
	ret = __cw1200_reg_पढ़ो(priv, addr, buf, buf_len, 0);
	priv->hwbus_ops->unlock(priv->hwbus_priv);
	वापस ret;
पूर्ण

पूर्णांक cw1200_reg_ग_लिखो(काष्ठा cw1200_common *priv, u16 addr, स्थिर व्योम *buf,
			माप_प्रकार buf_len)
अणु
	पूर्णांक ret;
	priv->hwbus_ops->lock(priv->hwbus_priv);
	ret = __cw1200_reg_ग_लिखो(priv, addr, buf, buf_len, 0);
	priv->hwbus_ops->unlock(priv->hwbus_priv);
	वापस ret;
पूर्ण

पूर्णांक cw1200_data_पढ़ो(काष्ठा cw1200_common *priv, व्योम *buf, माप_प्रकार buf_len)
अणु
	पूर्णांक ret, retry = 1;
	पूर्णांक buf_id_rx = priv->buf_id_rx;

	priv->hwbus_ops->lock(priv->hwbus_priv);

	जबतक (retry <= MAX_RETRY) अणु
		ret = __cw1200_reg_पढ़ो(priv,
					ST90TDS_IN_OUT_QUEUE_REG_ID, buf,
					buf_len, buf_id_rx + 1);
		अगर (!ret) अणु
			buf_id_rx = (buf_id_rx + 1) & 3;
			priv->buf_id_rx = buf_id_rx;
			अवरोध;
		पूर्ण अन्यथा अणु
			retry++;
			mdelay(1);
			pr_err("error :[%d]\n", ret);
		पूर्ण
	पूर्ण

	priv->hwbus_ops->unlock(priv->hwbus_priv);
	वापस ret;
पूर्ण

पूर्णांक cw1200_data_ग_लिखो(काष्ठा cw1200_common *priv, स्थिर व्योम *buf,
			माप_प्रकार buf_len)
अणु
	पूर्णांक ret, retry = 1;
	पूर्णांक buf_id_tx = priv->buf_id_tx;

	priv->hwbus_ops->lock(priv->hwbus_priv);

	जबतक (retry <= MAX_RETRY) अणु
		ret = __cw1200_reg_ग_लिखो(priv,
					 ST90TDS_IN_OUT_QUEUE_REG_ID, buf,
					 buf_len, buf_id_tx);
		अगर (!ret) अणु
			buf_id_tx = (buf_id_tx + 1) & 31;
			priv->buf_id_tx = buf_id_tx;
			अवरोध;
		पूर्ण अन्यथा अणु
			retry++;
			mdelay(1);
			pr_err("error :[%d]\n", ret);
		पूर्ण
	पूर्ण

	priv->hwbus_ops->unlock(priv->hwbus_priv);
	वापस ret;
पूर्ण

पूर्णांक cw1200_indirect_पढ़ो(काष्ठा cw1200_common *priv, u32 addr, व्योम *buf,
			 माप_प्रकार buf_len, u32 prefetch, u16 port_addr)
अणु
	u32 val32 = 0;
	पूर्णांक i, ret;

	अगर ((buf_len / 2) >= 0x1000) अणु
		pr_err("Can't read more than 0xfff words.\n");
		वापस -EINVAL;
	पूर्ण

	priv->hwbus_ops->lock(priv->hwbus_priv);
	/* Write address */
	ret = __cw1200_reg_ग_लिखो_32(priv, ST90TDS_SRAM_BASE_ADDR_REG_ID, addr);
	अगर (ret < 0) अणु
		pr_err("Can't write address register.\n");
		जाओ out;
	पूर्ण

	/* Read CONFIG Register Value - We will पढ़ो 32 bits */
	ret = __cw1200_reg_पढ़ो_32(priv, ST90TDS_CONFIG_REG_ID, &val32);
	अगर (ret < 0) अणु
		pr_err("Can't read config register.\n");
		जाओ out;
	पूर्ण

	/* Set PREFETCH bit */
	ret = __cw1200_reg_ग_लिखो_32(priv, ST90TDS_CONFIG_REG_ID,
					val32 | prefetch);
	अगर (ret < 0) अणु
		pr_err("Can't write prefetch bit.\n");
		जाओ out;
	पूर्ण

	/* Check क्रम PRE-FETCH bit to be cleared */
	क्रम (i = 0; i < 20; i++) अणु
		ret = __cw1200_reg_पढ़ो_32(priv, ST90TDS_CONFIG_REG_ID, &val32);
		अगर (ret < 0) अणु
			pr_err("Can't check prefetch bit.\n");
			जाओ out;
		पूर्ण
		अगर (!(val32 & prefetch))
			अवरोध;

		mdelay(i);
	पूर्ण

	अगर (val32 & prefetch) अणु
		pr_err("Prefetch bit is not cleared.\n");
		जाओ out;
	पूर्ण

	/* Read data port */
	ret = __cw1200_reg_पढ़ो(priv, port_addr, buf, buf_len, 0);
	अगर (ret < 0) अणु
		pr_err("Can't read data port.\n");
		जाओ out;
	पूर्ण

out:
	priv->hwbus_ops->unlock(priv->hwbus_priv);
	वापस ret;
पूर्ण

पूर्णांक cw1200_apb_ग_लिखो(काष्ठा cw1200_common *priv, u32 addr, स्थिर व्योम *buf,
			माप_प्रकार buf_len)
अणु
	पूर्णांक ret;

	अगर ((buf_len / 2) >= 0x1000) अणु
		pr_err("Can't write more than 0xfff words.\n");
		वापस -EINVAL;
	पूर्ण

	priv->hwbus_ops->lock(priv->hwbus_priv);

	/* Write address */
	ret = __cw1200_reg_ग_लिखो_32(priv, ST90TDS_SRAM_BASE_ADDR_REG_ID, addr);
	अगर (ret < 0) अणु
		pr_err("Can't write address register.\n");
		जाओ out;
	पूर्ण

	/* Write data port */
	ret = __cw1200_reg_ग_लिखो(priv, ST90TDS_SRAM_DPORT_REG_ID,
					buf, buf_len, 0);
	अगर (ret < 0) अणु
		pr_err("Can't write data port.\n");
		जाओ out;
	पूर्ण

out:
	priv->hwbus_ops->unlock(priv->hwbus_priv);
	वापस ret;
पूर्ण

पूर्णांक __cw1200_irq_enable(काष्ठा cw1200_common *priv, पूर्णांक enable)
अणु
	u32 val32;
	u16 val16;
	पूर्णांक ret;

	अगर (HIF_8601_SILICON == priv->hw_type) अणु
		ret = __cw1200_reg_पढ़ो_32(priv, ST90TDS_CONFIG_REG_ID, &val32);
		अगर (ret < 0) अणु
			pr_err("Can't read config register.\n");
			वापस ret;
		पूर्ण

		अगर (enable)
			val32 |= ST90TDS_CONF_IRQ_RDY_ENABLE;
		अन्यथा
			val32 &= ~ST90TDS_CONF_IRQ_RDY_ENABLE;

		ret = __cw1200_reg_ग_लिखो_32(priv, ST90TDS_CONFIG_REG_ID, val32);
		अगर (ret < 0) अणु
			pr_err("Can't write config register.\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = __cw1200_reg_पढ़ो_16(priv, ST90TDS_CONFIG_REG_ID, &val16);
		अगर (ret < 0) अणु
			pr_err("Can't read control register.\n");
			वापस ret;
		पूर्ण

		अगर (enable)
			val16 |= ST90TDS_CONT_IRQ_RDY_ENABLE;
		अन्यथा
			val16 &= ~ST90TDS_CONT_IRQ_RDY_ENABLE;

		ret = __cw1200_reg_ग_लिखो_16(priv, ST90TDS_CONFIG_REG_ID, val16);
		अगर (ret < 0) अणु
			pr_err("Can't write control register.\n");
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
