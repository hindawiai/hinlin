<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016 Google, Inc
 *
 * This device driver implements a TCG PTP FIFO पूर्णांकerface over SPI क्रम chips
 * with Cr50 firmware.
 * It is based on tpm_tis_spi driver by Peter Huewe and Christophe Ricard.
 */

#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/रुको.h>

#समावेश "tpm_tis_core.h"
#समावेश "tpm_tis_spi.h"

/*
 * Cr50 timing स्थिरants:
 * - can go to sleep not earlier than after CR50_SLEEP_DELAY_MSEC.
 * - needs up to CR50_WAKE_START_DELAY_USEC to wake after sleep.
 * - requires रुकोing क्रम "ready" IRQ, अगर supported; or रुकोing क्रम at least
 *   CR50_NOIRQ_ACCESS_DELAY_MSEC between transactions, अगर IRQ is not supported.
 * - रुकोs क्रम up to CR50_FLOW_CONTROL क्रम flow control 'ready' indication.
 */
#घोषणा CR50_SLEEP_DELAY_MSEC			1000
#घोषणा CR50_WAKE_START_DELAY_USEC		1000
#घोषणा CR50_NOIRQ_ACCESS_DELAY			msecs_to_jअगरfies(2)
#घोषणा CR50_READY_IRQ_TIMEOUT			msecs_to_jअगरfies(TPM2_TIMEOUT_A)
#घोषणा CR50_FLOW_CONTROL			msecs_to_jअगरfies(TPM2_TIMEOUT_A)
#घोषणा MAX_IRQ_CONFIRMATION_ATTEMPTS		3

#घोषणा TPM_CR50_FW_VER(l)			(0x0f90 | ((l) << 12))
#घोषणा TPM_CR50_MAX_FW_VER_LEN			64

काष्ठा cr50_spi_phy अणु
	काष्ठा tpm_tis_spi_phy spi_phy;

	काष्ठा mutex समय_प्रकारrack_mutex;
	अचिन्हित दीर्घ last_access;

	अचिन्हित दीर्घ access_delay;

	अचिन्हित पूर्णांक irq_confirmation_attempt;
	bool irq_needs_confirmation;
	bool irq_confirmed;
पूर्ण;

अटल अंतरभूत काष्ठा cr50_spi_phy *to_cr50_spi_phy(काष्ठा tpm_tis_spi_phy *phy)
अणु
	वापस container_of(phy, काष्ठा cr50_spi_phy, spi_phy);
पूर्ण

/*
 * The cr50 पूर्णांकerrupt handler just संकेतs रुकोing thपढ़ोs that the
 * पूर्णांकerrupt was निश्चितed.  It करोes not करो any processing triggered
 * by पूर्णांकerrupts but is instead used to aव्योम fixed delays.
 */
अटल irqवापस_t cr50_spi_irq_handler(पूर्णांक dummy, व्योम *dev_id)
अणु
	काष्ठा cr50_spi_phy *cr50_phy = dev_id;

	cr50_phy->irq_confirmed = true;
	complete(&cr50_phy->spi_phy.पढ़ोy);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Cr50 needs to have at least some delay between consecutive
 * transactions. Make sure we रुको.
 */
अटल व्योम cr50_ensure_access_delay(काष्ठा cr50_spi_phy *phy)
अणु
	अचिन्हित दीर्घ allowed_access = phy->last_access + phy->access_delay;
	अचिन्हित दीर्घ समय_now = jअगरfies;
	काष्ठा device *dev = &phy->spi_phy.spi_device->dev;

	/*
	 * Note: There is a small chance, अगर Cr50 is not accessed in a few days,
	 * that समय_in_range will not provide the correct result after the wrap
	 * around क्रम jअगरfies. In this हाल, we'll have an unneeded लघु delay,
	 * which is fine.
	 */
	अगर (समय_in_range_खोलो(समय_now, phy->last_access, allowed_access)) अणु
		अचिन्हित दीर्घ reमुख्यing, समयout = allowed_access - समय_now;

		reमुख्यing = रुको_क्रम_completion_समयout(&phy->spi_phy.पढ़ोy,
							समयout);
		अगर (!reमुख्यing && phy->irq_confirmed)
			dev_warn(dev, "Timeout waiting for TPM ready IRQ\n");
	पूर्ण

	अगर (phy->irq_needs_confirmation) अणु
		अचिन्हित पूर्णांक attempt = ++phy->irq_confirmation_attempt;

		अगर (phy->irq_confirmed) अणु
			phy->irq_needs_confirmation = false;
			phy->access_delay = CR50_READY_IRQ_TIMEOUT;
			dev_info(dev, "TPM ready IRQ confirmed on attempt %u\n",
				 attempt);
		पूर्ण अन्यथा अगर (attempt > MAX_IRQ_CONFIRMATION_ATTEMPTS) अणु
			phy->irq_needs_confirmation = false;
			dev_warn(dev, "IRQ not confirmed - will use delays\n");
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Cr50 might go to sleep अगर there is no SPI activity क्रम some समय and
 * miss the first few bits/bytes on the bus. In such हाल, wake it up
 * by निश्चितing CS and give it समय to start up.
 */
अटल bool cr50_needs_waking(काष्ठा cr50_spi_phy *phy)
अणु
	/*
	 * Note: There is a small chance, अगर Cr50 is not accessed in a few days,
	 * that समय_in_range will not provide the correct result after the wrap
	 * around क्रम jअगरfies. In this हाल, we'll probably समयout or पढ़ो
	 * incorrect value from TPM_STS and just retry the operation.
	 */
	वापस !समय_in_range_खोलो(jअगरfies, phy->last_access,
				   phy->spi_phy.wake_after);
पूर्ण

अटल व्योम cr50_wake_अगर_needed(काष्ठा cr50_spi_phy *cr50_phy)
अणु
	काष्ठा tpm_tis_spi_phy *phy = &cr50_phy->spi_phy;

	अगर (cr50_needs_waking(cr50_phy)) अणु
		/* Assert CS, रुको 1 msec, deनिश्चित CS */
		काष्ठा spi_transfer spi_cs_wake = अणु
			.delay = अणु
				.value = 1000,
				.unit = SPI_DELAY_UNIT_USECS
			पूर्ण
		पूर्ण;

		spi_sync_transfer(phy->spi_device, &spi_cs_wake, 1);
		/* Wait क्रम it to fully wake */
		usleep_range(CR50_WAKE_START_DELAY_USEC,
			     CR50_WAKE_START_DELAY_USEC * 2);
	पूर्ण

	/* Reset the समय when we need to wake Cr50 again */
	phy->wake_after = jअगरfies + msecs_to_jअगरfies(CR50_SLEEP_DELAY_MSEC);
पूर्ण

/*
 * Flow control: घड़ी the bus and रुको क्रम cr50 to set LSB beक्रमe
 * sending/receiving data. TCG PTP spec allows it to happen during
 * the last byte of header, but cr50 never करोes that in practice,
 * and earlier versions had a bug when it was set too early, so करोn't
 * check क्रम it during header transfer.
 */
अटल पूर्णांक cr50_spi_flow_control(काष्ठा tpm_tis_spi_phy *phy,
				 काष्ठा spi_transfer *spi_xfer)
अणु
	काष्ठा device *dev = &phy->spi_device->dev;
	अचिन्हित दीर्घ समयout = jअगरfies + CR50_FLOW_CONTROL;
	काष्ठा spi_message m;
	पूर्णांक ret;

	spi_xfer->len = 1;

	करो अणु
		spi_message_init(&m);
		spi_message_add_tail(spi_xfer, &m);
		ret = spi_sync_locked(phy->spi_device, &m);
		अगर (ret < 0)
			वापस ret;

		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_warn(dev, "Timeout during flow control\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण जबतक (!(phy->iobuf[0] & 0x01));

	वापस 0;
पूर्ण

अटल पूर्णांक tpm_tis_spi_cr50_transfer(काष्ठा tpm_tis_data *data, u32 addr, u16 len,
				     u8 *in, स्थिर u8 *out)
अणु
	काष्ठा tpm_tis_spi_phy *phy = to_tpm_tis_spi_phy(data);
	काष्ठा cr50_spi_phy *cr50_phy = to_cr50_spi_phy(phy);
	पूर्णांक ret;

	mutex_lock(&cr50_phy->समय_प्रकारrack_mutex);
	/*
	 * Do this outside of spi_bus_lock in हाल cr50 is not the
	 * only device on that spi bus.
	 */
	cr50_ensure_access_delay(cr50_phy);
	cr50_wake_अगर_needed(cr50_phy);

	ret = tpm_tis_spi_transfer(data, addr, len, in, out);

	cr50_phy->last_access = jअगरfies;
	mutex_unlock(&cr50_phy->समय_प्रकारrack_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक tpm_tis_spi_cr50_पढ़ो_bytes(काष्ठा tpm_tis_data *data, u32 addr,
				       u16 len, u8 *result)
अणु
	वापस tpm_tis_spi_cr50_transfer(data, addr, len, result, शून्य);
पूर्ण

अटल पूर्णांक tpm_tis_spi_cr50_ग_लिखो_bytes(काष्ठा tpm_tis_data *data, u32 addr,
					u16 len, स्थिर u8 *value)
अणु
	वापस tpm_tis_spi_cr50_transfer(data, addr, len, शून्य, value);
पूर्ण

अटल स्थिर काष्ठा tpm_tis_phy_ops tpm_spi_cr50_phy_ops = अणु
	.पढ़ो_bytes = tpm_tis_spi_cr50_पढ़ो_bytes,
	.ग_लिखो_bytes = tpm_tis_spi_cr50_ग_लिखो_bytes,
	.पढ़ो16 = tpm_tis_spi_पढ़ो16,
	.पढ़ो32 = tpm_tis_spi_पढ़ो32,
	.ग_लिखो32 = tpm_tis_spi_ग_लिखो32,
पूर्ण;

अटल व्योम cr50_prपूर्णांक_fw_version(काष्ठा tpm_tis_data *data)
अणु
	काष्ठा tpm_tis_spi_phy *phy = to_tpm_tis_spi_phy(data);
	पूर्णांक i, len = 0;
	अक्षर fw_ver[TPM_CR50_MAX_FW_VER_LEN + 1];
	अक्षर fw_ver_block[4];

	/*
	 * Write anything to TPM_CR50_FW_VER to start from the beginning
	 * of the version string
	 */
	tpm_tis_ग_लिखो8(data, TPM_CR50_FW_VER(data->locality), 0);

	/* Read the string, 4 bytes at a समय, until we get '\0' */
	करो अणु
		tpm_tis_पढ़ो_bytes(data, TPM_CR50_FW_VER(data->locality), 4,
				   fw_ver_block);
		क्रम (i = 0; i < 4 && fw_ver_block[i]; ++len, ++i)
			fw_ver[len] = fw_ver_block[i];
	पूर्ण जबतक (i == 4 && len < TPM_CR50_MAX_FW_VER_LEN);
	fw_ver[len] = '\0';

	dev_info(&phy->spi_device->dev, "Cr50 firmware version: %s\n", fw_ver);
पूर्ण

पूर्णांक cr50_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा tpm_tis_spi_phy *phy;
	काष्ठा cr50_spi_phy *cr50_phy;
	पूर्णांक ret;
	काष्ठा tpm_chip *chip;

	cr50_phy = devm_kzalloc(&spi->dev, माप(*cr50_phy), GFP_KERNEL);
	अगर (!cr50_phy)
		वापस -ENOMEM;

	phy = &cr50_phy->spi_phy;
	phy->flow_control = cr50_spi_flow_control;
	phy->wake_after = jअगरfies;
	init_completion(&phy->पढ़ोy);

	cr50_phy->access_delay = CR50_NOIRQ_ACCESS_DELAY;
	cr50_phy->last_access = jअगरfies;
	mutex_init(&cr50_phy->समय_प्रकारrack_mutex);

	अगर (spi->irq > 0) अणु
		ret = devm_request_irq(&spi->dev, spi->irq,
				       cr50_spi_irq_handler,
				       IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				       "cr50_spi", cr50_phy);
		अगर (ret < 0) अणु
			अगर (ret == -EPROBE_DEFER)
				वापस ret;
			dev_warn(&spi->dev, "Requesting IRQ %d failed: %d\n",
				 spi->irq, ret);
			/*
			 * This is not fatal, the driver will fall back to
			 * delays स्वतःmatically, since पढ़ोy will never
			 * be completed without a रेजिस्टरed irq handler.
			 * So, just fall through.
			 */
		पूर्ण अन्यथा अणु
			/*
			 * IRQ requested, let's verअगरy that it is actually
			 * triggered, beक्रमe relying on it.
			 */
			cr50_phy->irq_needs_confirmation = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(&spi->dev,
			 "No IRQ - will use delays between transactions.\n");
	पूर्ण

	ret = tpm_tis_spi_init(spi, phy, -1, &tpm_spi_cr50_phy_ops);
	अगर (ret)
		वापस ret;

	cr50_prपूर्णांक_fw_version(&phy->priv);

	chip = dev_get_drvdata(&spi->dev);
	chip->flags |= TPM_CHIP_FLAG_FIRMWARE_POWER_MANAGED;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक tpm_tis_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(dev);
	काष्ठा tpm_tis_data *data = dev_get_drvdata(&chip->dev);
	काष्ठा tpm_tis_spi_phy *phy = to_tpm_tis_spi_phy(data);
	/*
	 * Jअगरfies not increased during suspend, so we need to reset
	 * the समय to wake Cr50 after resume.
	 */
	phy->wake_after = jअगरfies;

	वापस tpm_tis_resume(dev);
पूर्ण
#पूर्ण_अगर
