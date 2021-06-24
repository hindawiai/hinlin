<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Infineon Technologies AG
 * Copyright (C) 2016 STMicroelectronics SAS
 *
 * Authors:
 * Peter Huewe <peter.huewe@infineon.com>
 * Christophe Ricard <christophe-h.ricard@st.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org
 *
 * This device driver implements the TPM पूर्णांकerface as defined in
 * the TCG TPM Interface Spec version 1.3, revision 27 via _raw/native
 * SPI access_.
 *
 * It is based on the original tpm_tis device driver from Leendert van
 * Dorn and Kyleen Hall and Jarko Sakkinnen.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/completion.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/tpm.h>

#समावेश "tpm.h"
#समावेश "tpm_tis_core.h"
#समावेश "tpm_tis_spi.h"

#घोषणा MAX_SPI_FRAMESIZE 64

/*
 * TCG SPI flow control is करोcumented in section 6.4 of the spec[1]. In लघु,
 * keep trying to पढ़ो from the device until MISO goes high indicating the
 * रुको state has ended.
 *
 * [1] https://trustedcomputinggroup.org/resource/pc-client-platक्रमm-tpm-profile-ptp-specअगरication/
 */
अटल पूर्णांक tpm_tis_spi_flow_control(काष्ठा tpm_tis_spi_phy *phy,
				    काष्ठा spi_transfer *spi_xfer)
अणु
	काष्ठा spi_message m;
	पूर्णांक ret, i;

	अगर ((phy->iobuf[3] & 0x01) == 0) अणु
		// handle SPI रुको states
		क्रम (i = 0; i < TPM_RETRY; i++) अणु
			spi_xfer->len = 1;
			spi_message_init(&m);
			spi_message_add_tail(spi_xfer, &m);
			ret = spi_sync_locked(phy->spi_device, &m);
			अगर (ret < 0)
				वापस ret;
			अगर (phy->iobuf[0] & 0x01)
				अवरोध;
		पूर्ण

		अगर (i == TPM_RETRY)
			वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tpm_tis_spi_transfer(काष्ठा tpm_tis_data *data, u32 addr, u16 len,
			 u8 *in, स्थिर u8 *out)
अणु
	काष्ठा tpm_tis_spi_phy *phy = to_tpm_tis_spi_phy(data);
	पूर्णांक ret = 0;
	काष्ठा spi_message m;
	काष्ठा spi_transfer spi_xfer;
	u8 transfer_len;

	spi_bus_lock(phy->spi_device->master);

	जबतक (len) अणु
		transfer_len = min_t(u16, len, MAX_SPI_FRAMESIZE);

		phy->iobuf[0] = (in ? 0x80 : 0) | (transfer_len - 1);
		phy->iobuf[1] = 0xd4;
		phy->iobuf[2] = addr >> 8;
		phy->iobuf[3] = addr;

		स_रखो(&spi_xfer, 0, माप(spi_xfer));
		spi_xfer.tx_buf = phy->iobuf;
		spi_xfer.rx_buf = phy->iobuf;
		spi_xfer.len = 4;
		spi_xfer.cs_change = 1;

		spi_message_init(&m);
		spi_message_add_tail(&spi_xfer, &m);
		ret = spi_sync_locked(phy->spi_device, &m);
		अगर (ret < 0)
			जाओ निकास;

		/* Flow control transfers are receive only */
		spi_xfer.tx_buf = शून्य;
		ret = phy->flow_control(phy, &spi_xfer);
		अगर (ret < 0)
			जाओ निकास;

		spi_xfer.cs_change = 0;
		spi_xfer.len = transfer_len;
		spi_xfer.delay.value = 5;
		spi_xfer.delay.unit = SPI_DELAY_UNIT_USECS;

		अगर (out) अणु
			spi_xfer.tx_buf = phy->iobuf;
			spi_xfer.rx_buf = शून्य;
			स_नकल(phy->iobuf, out, transfer_len);
			out += transfer_len;
		पूर्ण

		spi_message_init(&m);
		spi_message_add_tail(&spi_xfer, &m);
		reinit_completion(&phy->पढ़ोy);
		ret = spi_sync_locked(phy->spi_device, &m);
		अगर (ret < 0)
			जाओ निकास;

		अगर (in) अणु
			स_नकल(in, phy->iobuf, transfer_len);
			in += transfer_len;
		पूर्ण

		len -= transfer_len;
	पूर्ण

निकास:
	spi_bus_unlock(phy->spi_device->master);
	वापस ret;
पूर्ण

अटल पूर्णांक tpm_tis_spi_पढ़ो_bytes(काष्ठा tpm_tis_data *data, u32 addr,
				  u16 len, u8 *result)
अणु
	वापस tpm_tis_spi_transfer(data, addr, len, result, शून्य);
पूर्ण

अटल पूर्णांक tpm_tis_spi_ग_लिखो_bytes(काष्ठा tpm_tis_data *data, u32 addr,
				   u16 len, स्थिर u8 *value)
अणु
	वापस tpm_tis_spi_transfer(data, addr, len, शून्य, value);
पूर्ण

पूर्णांक tpm_tis_spi_पढ़ो16(काष्ठा tpm_tis_data *data, u32 addr, u16 *result)
अणु
	__le16 result_le;
	पूर्णांक rc;

	rc = data->phy_ops->पढ़ो_bytes(data, addr, माप(u16),
				       (u8 *)&result_le);
	अगर (!rc)
		*result = le16_to_cpu(result_le);

	वापस rc;
पूर्ण

पूर्णांक tpm_tis_spi_पढ़ो32(काष्ठा tpm_tis_data *data, u32 addr, u32 *result)
अणु
	__le32 result_le;
	पूर्णांक rc;

	rc = data->phy_ops->पढ़ो_bytes(data, addr, माप(u32),
				       (u8 *)&result_le);
	अगर (!rc)
		*result = le32_to_cpu(result_le);

	वापस rc;
पूर्ण

पूर्णांक tpm_tis_spi_ग_लिखो32(काष्ठा tpm_tis_data *data, u32 addr, u32 value)
अणु
	__le32 value_le;
	पूर्णांक rc;

	value_le = cpu_to_le32(value);
	rc = data->phy_ops->ग_लिखो_bytes(data, addr, माप(u32),
					(u8 *)&value_le);

	वापस rc;
पूर्ण

पूर्णांक tpm_tis_spi_init(काष्ठा spi_device *spi, काष्ठा tpm_tis_spi_phy *phy,
		     पूर्णांक irq, स्थिर काष्ठा tpm_tis_phy_ops *phy_ops)
अणु
	phy->iobuf = devm_kदो_स्मृति(&spi->dev, MAX_SPI_FRAMESIZE, GFP_KERNEL);
	अगर (!phy->iobuf)
		वापस -ENOMEM;

	phy->spi_device = spi;

	वापस tpm_tis_core_init(&spi->dev, &phy->priv, irq, phy_ops, शून्य);
पूर्ण

अटल स्थिर काष्ठा tpm_tis_phy_ops tpm_spi_phy_ops = अणु
	.पढ़ो_bytes = tpm_tis_spi_पढ़ो_bytes,
	.ग_लिखो_bytes = tpm_tis_spi_ग_लिखो_bytes,
	.पढ़ो16 = tpm_tis_spi_पढ़ो16,
	.पढ़ो32 = tpm_tis_spi_पढ़ो32,
	.ग_लिखो32 = tpm_tis_spi_ग_लिखो32,
पूर्ण;

अटल पूर्णांक tpm_tis_spi_probe(काष्ठा spi_device *dev)
अणु
	काष्ठा tpm_tis_spi_phy *phy;
	पूर्णांक irq;

	phy = devm_kzalloc(&dev->dev, माप(काष्ठा tpm_tis_spi_phy),
			   GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->flow_control = tpm_tis_spi_flow_control;

	/* If the SPI device has an IRQ then use that */
	अगर (dev->irq > 0)
		irq = dev->irq;
	अन्यथा
		irq = -1;

	init_completion(&phy->पढ़ोy);
	वापस tpm_tis_spi_init(dev, phy, irq, &tpm_spi_phy_ops);
पूर्ण

प्रकार पूर्णांक (*tpm_tis_spi_probe_func)(काष्ठा spi_device *);

अटल पूर्णांक tpm_tis_spi_driver_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *spi_dev_id = spi_get_device_id(spi);
	tpm_tis_spi_probe_func probe_func;

	probe_func = of_device_get_match_data(&spi->dev);
	अगर (!probe_func && spi_dev_id)
		probe_func = (tpm_tis_spi_probe_func)spi_dev_id->driver_data;
	अगर (!probe_func)
		वापस -ENODEV;

	वापस probe_func(spi);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tpm_tis_pm, tpm_pm_suspend, tpm_tis_spi_resume);

अटल पूर्णांक tpm_tis_spi_हटाओ(काष्ठा spi_device *dev)
अणु
	काष्ठा tpm_chip *chip = spi_get_drvdata(dev);

	tpm_chip_unरेजिस्टर(chip);
	tpm_tis_हटाओ(chip);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id tpm_tis_spi_id[] = अणु
	अणु "tpm_tis_spi", (अचिन्हित दीर्घ)tpm_tis_spi_probe पूर्ण,
	अणु "cr50", (अचिन्हित दीर्घ)cr50_spi_probe पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, tpm_tis_spi_id);

अटल स्थिर काष्ठा of_device_id of_tis_spi_match[] = अणु
	अणु .compatible = "st,st33htpm-spi", .data = tpm_tis_spi_probe पूर्ण,
	अणु .compatible = "infineon,slb9670", .data = tpm_tis_spi_probe पूर्ण,
	अणु .compatible = "tcg,tpm_tis-spi", .data = tpm_tis_spi_probe पूर्ण,
	अणु .compatible = "google,cr50", .data = cr50_spi_probe पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_tis_spi_match);

अटल स्थिर काष्ठा acpi_device_id acpi_tis_spi_match[] = अणु
	अणु"SMO0768", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, acpi_tis_spi_match);

अटल काष्ठा spi_driver tpm_tis_spi_driver = अणु
	.driver = अणु
		.name = "tpm_tis_spi",
		.pm = &tpm_tis_pm,
		.of_match_table = of_match_ptr(of_tis_spi_match),
		.acpi_match_table = ACPI_PTR(acpi_tis_spi_match),
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
	.probe = tpm_tis_spi_driver_probe,
	.हटाओ = tpm_tis_spi_हटाओ,
	.id_table = tpm_tis_spi_id,
पूर्ण;
module_spi_driver(tpm_tis_spi_driver);

MODULE_DESCRIPTION("TPM Driver for native SPI access");
MODULE_LICENSE("GPL");
