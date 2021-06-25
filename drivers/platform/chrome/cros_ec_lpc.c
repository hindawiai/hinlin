<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// LPC पूर्णांकerface क्रम ChromeOS Embedded Controller
//
// Copyright (C) 2012-2015 Google, Inc
//
// This driver uses the ChromeOS EC byte-level message-based protocol क्रम
// communicating the keyboard state (which keys are pressed) from a keyboard EC
// to the AP over some bus (such as i2c, lpc, spi).  The EC करोes debouncing,
// but everything अन्यथा (including deghosting) is करोne here.  The मुख्य
// motivation क्रम this is to keep the EC firmware as simple as possible, since
// it cannot be easily upgraded and EC flash/IRAM space is relatively
// expensive.

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/suspend.h>

#समावेश "cros_ec.h"
#समावेश "cros_ec_lpc_mec.h"

#घोषणा DRV_NAME "cros_ec_lpcs"
#घोषणा ACPI_DRV_NAME "GOOG0004"

/* True अगर ACPI device is present */
अटल bool cros_ec_lpc_acpi_device_found;

/**
 * काष्ठा lpc_driver_ops - LPC driver operations
 * @पढ़ो: Copy length bytes from EC address offset पूर्णांकo buffer dest. Returns
 *        the 8-bit checksum of all bytes पढ़ो.
 * @ग_लिखो: Copy length bytes from buffer msg पूर्णांकo EC address offset. Returns
 *         the 8-bit checksum of all bytes written.
 */
काष्ठा lpc_driver_ops अणु
	u8 (*पढ़ो)(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length, u8 *dest);
	u8 (*ग_लिखो)(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length, स्थिर u8 *msg);
पूर्ण;

अटल काष्ठा lpc_driver_ops cros_ec_lpc_ops = अणु पूर्ण;

/*
 * A generic instance of the पढ़ो function of काष्ठा lpc_driver_ops, used क्रम
 * the LPC EC.
 */
अटल u8 cros_ec_lpc_पढ़ो_bytes(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length,
				 u8 *dest)
अणु
	पूर्णांक sum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < length; ++i) अणु
		dest[i] = inb(offset + i);
		sum += dest[i];
	पूर्ण

	/* Return checksum of all bytes पढ़ो */
	वापस sum;
पूर्ण

/*
 * A generic instance of the ग_लिखो function of काष्ठा lpc_driver_ops, used क्रम
 * the LPC EC.
 */
अटल u8 cros_ec_lpc_ग_लिखो_bytes(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length,
				  स्थिर u8 *msg)
अणु
	पूर्णांक sum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < length; ++i) अणु
		outb(msg[i], offset + i);
		sum += msg[i];
	पूर्ण

	/* Return checksum of all bytes written */
	वापस sum;
पूर्ण

/*
 * An instance of the पढ़ो function of काष्ठा lpc_driver_ops, used क्रम the
 * MEC variant of LPC EC.
 */
अटल u8 cros_ec_lpc_mec_पढ़ो_bytes(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length,
				     u8 *dest)
अणु
	पूर्णांक in_range = cros_ec_lpc_mec_in_range(offset, length);

	अगर (in_range < 0)
		वापस 0;

	वापस in_range ?
		cros_ec_lpc_io_bytes_mec(MEC_IO_READ,
					 offset - EC_HOST_CMD_REGION0,
					 length, dest) :
		cros_ec_lpc_पढ़ो_bytes(offset, length, dest);
पूर्ण

/*
 * An instance of the ग_लिखो function of काष्ठा lpc_driver_ops, used क्रम the
 * MEC variant of LPC EC.
 */
अटल u8 cros_ec_lpc_mec_ग_लिखो_bytes(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length,
				      स्थिर u8 *msg)
अणु
	पूर्णांक in_range = cros_ec_lpc_mec_in_range(offset, length);

	अगर (in_range < 0)
		वापस 0;

	वापस in_range ?
		cros_ec_lpc_io_bytes_mec(MEC_IO_WRITE,
					 offset - EC_HOST_CMD_REGION0,
					 length, (u8 *)msg) :
		cros_ec_lpc_ग_लिखो_bytes(offset, length, msg);
पूर्ण

अटल पूर्णांक ec_response_समयd_out(व्योम)
अणु
	अचिन्हित दीर्घ one_second = jअगरfies + HZ;
	u8 data;

	usleep_range(200, 300);
	करो अणु
		अगर (!(cros_ec_lpc_ops.पढ़ो(EC_LPC_ADDR_HOST_CMD, 1, &data) &
		    EC_LPC_STATUS_BUSY_MASK))
			वापस 0;
		usleep_range(100, 200);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, one_second));

	वापस 1;
पूर्ण

अटल पूर्णांक cros_ec_pkt_xfer_lpc(काष्ठा cros_ec_device *ec,
				काष्ठा cros_ec_command *msg)
अणु
	काष्ठा ec_host_response response;
	u8 sum;
	पूर्णांक ret = 0;
	u8 *करोut;

	ret = cros_ec_prepare_tx(ec, msg);

	/* Write buffer */
	cros_ec_lpc_ops.ग_लिखो(EC_LPC_ADDR_HOST_PACKET, ret, ec->करोut);

	/* Here we go */
	sum = EC_COMMAND_PROTOCOL_3;
	cros_ec_lpc_ops.ग_लिखो(EC_LPC_ADDR_HOST_CMD, 1, &sum);

	अगर (ec_response_समयd_out()) अणु
		dev_warn(ec->dev, "EC responsed timed out\n");
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	/* Check result */
	msg->result = cros_ec_lpc_ops.पढ़ो(EC_LPC_ADDR_HOST_DATA, 1, &sum);
	ret = cros_ec_check_result(ec, msg);
	अगर (ret)
		जाओ करोne;

	/* Read back response */
	करोut = (u8 *)&response;
	sum = cros_ec_lpc_ops.पढ़ो(EC_LPC_ADDR_HOST_PACKET, माप(response),
				   करोut);

	msg->result = response.result;

	अगर (response.data_len > msg->insize) अणु
		dev_err(ec->dev,
			"packet too long (%d bytes, expected %d)",
			response.data_len, msg->insize);
		ret = -EMSGSIZE;
		जाओ करोne;
	पूर्ण

	/* Read response and process checksum */
	sum += cros_ec_lpc_ops.पढ़ो(EC_LPC_ADDR_HOST_PACKET +
				    माप(response), response.data_len,
				    msg->data);

	अगर (sum) अणु
		dev_err(ec->dev,
			"bad packet checksum %02x\n",
			response.checksum);
		ret = -EBADMSG;
		जाओ करोne;
	पूर्ण

	/* Return actual amount of data received */
	ret = response.data_len;
करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_cmd_xfer_lpc(काष्ठा cros_ec_device *ec,
				काष्ठा cros_ec_command *msg)
अणु
	काष्ठा ec_lpc_host_args args;
	u8 sum;
	पूर्णांक ret = 0;

	अगर (msg->outsize > EC_PROTO2_MAX_PARAM_SIZE ||
	    msg->insize > EC_PROTO2_MAX_PARAM_SIZE) अणु
		dev_err(ec->dev,
			"invalid buffer sizes (out %d, in %d)\n",
			msg->outsize, msg->insize);
		वापस -EINVAL;
	पूर्ण

	/* Now actually send the command to the EC and get the result */
	args.flags = EC_HOST_ARGS_FLAG_FROM_HOST;
	args.command_version = msg->version;
	args.data_size = msg->outsize;

	/* Initialize checksum */
	sum = msg->command + args.flags + args.command_version + args.data_size;

	/* Copy data and update checksum */
	sum += cros_ec_lpc_ops.ग_लिखो(EC_LPC_ADDR_HOST_PARAM, msg->outsize,
				     msg->data);

	/* Finalize checksum and ग_लिखो args */
	args.checksum = sum;
	cros_ec_lpc_ops.ग_लिखो(EC_LPC_ADDR_HOST_ARGS, माप(args),
			      (u8 *)&args);

	/* Here we go */
	sum = msg->command;
	cros_ec_lpc_ops.ग_लिखो(EC_LPC_ADDR_HOST_CMD, 1, &sum);

	अगर (ec_response_समयd_out()) अणु
		dev_warn(ec->dev, "EC responsed timed out\n");
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	/* Check result */
	msg->result = cros_ec_lpc_ops.पढ़ो(EC_LPC_ADDR_HOST_DATA, 1, &sum);
	ret = cros_ec_check_result(ec, msg);
	अगर (ret)
		जाओ करोne;

	/* Read back args */
	cros_ec_lpc_ops.पढ़ो(EC_LPC_ADDR_HOST_ARGS, माप(args), (u8 *)&args);

	अगर (args.data_size > msg->insize) अणु
		dev_err(ec->dev,
			"packet too long (%d bytes, expected %d)",
			args.data_size, msg->insize);
		ret = -ENOSPC;
		जाओ करोne;
	पूर्ण

	/* Start calculating response checksum */
	sum = msg->command + args.flags + args.command_version + args.data_size;

	/* Read response and update checksum */
	sum += cros_ec_lpc_ops.पढ़ो(EC_LPC_ADDR_HOST_PARAM, args.data_size,
				    msg->data);

	/* Verअगरy checksum */
	अगर (args.checksum != sum) अणु
		dev_err(ec->dev,
			"bad packet checksum, expected %02x, got %02x\n",
			args.checksum, sum);
		ret = -EBADMSG;
		जाओ करोne;
	पूर्ण

	/* Return actual amount of data received */
	ret = args.data_size;
करोne:
	वापस ret;
पूर्ण

/* Returns num bytes पढ़ो, or negative on error. Doesn't need locking. */
अटल पूर्णांक cros_ec_lpc_पढ़ोmem(काष्ठा cros_ec_device *ec, अचिन्हित पूर्णांक offset,
			       अचिन्हित पूर्णांक bytes, व्योम *dest)
अणु
	पूर्णांक i = offset;
	अक्षर *s = dest;
	पूर्णांक cnt = 0;

	अगर (offset >= EC_MEMMAP_SIZE - bytes)
		वापस -EINVAL;

	/* fixed length */
	अगर (bytes) अणु
		cros_ec_lpc_ops.पढ़ो(EC_LPC_ADDR_MEMMAP + offset, bytes, s);
		वापस bytes;
	पूर्ण

	/* string */
	क्रम (; i < EC_MEMMAP_SIZE; i++, s++) अणु
		cros_ec_lpc_ops.पढ़ो(EC_LPC_ADDR_MEMMAP + i, 1, s);
		cnt++;
		अगर (!*s)
			अवरोध;
	पूर्ण

	वापस cnt;
पूर्ण

अटल व्योम cros_ec_lpc_acpi_notअगरy(acpi_handle device, u32 value, व्योम *data)
अणु
	काष्ठा cros_ec_device *ec_dev = data;
	bool ec_has_more_events;
	पूर्णांक ret;

	ec_dev->last_event_समय = cros_ec_get_समय_ns();

	अगर (ec_dev->mkbp_event_supported)
		करो अणु
			ret = cros_ec_get_next_event(ec_dev, शून्य,
						     &ec_has_more_events);
			अगर (ret > 0)
				blocking_notअगरier_call_chain(
						&ec_dev->event_notअगरier, 0,
						ec_dev);
		पूर्ण जबतक (ec_has_more_events);

	अगर (value == ACPI_NOTIFY_DEVICE_WAKE)
		pm_प्रणाली_wakeup();
पूर्ण

अटल पूर्णांक cros_ec_lpc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा acpi_device *adev;
	acpi_status status;
	काष्ठा cros_ec_device *ec_dev;
	u8 buf[2];
	पूर्णांक irq, ret;

	अगर (!devm_request_region(dev, EC_LPC_ADDR_MEMMAP, EC_MEMMAP_SIZE,
				 dev_name(dev))) अणु
		dev_err(dev, "couldn't reserve memmap region\n");
		वापस -EBUSY;
	पूर्ण

	/*
	 * Read the mapped ID twice, the first one is assuming the
	 * EC is a Microchip Embedded Controller (MEC) variant, अगर the
	 * protocol fails, fallback to the non MEC variant and try to
	 * पढ़ो again the ID.
	 */
	cros_ec_lpc_ops.पढ़ो = cros_ec_lpc_mec_पढ़ो_bytes;
	cros_ec_lpc_ops.ग_लिखो = cros_ec_lpc_mec_ग_लिखो_bytes;
	cros_ec_lpc_ops.पढ़ो(EC_LPC_ADDR_MEMMAP + EC_MEMMAP_ID, 2, buf);
	अगर (buf[0] != 'E' || buf[1] != 'C') अणु
		/* Re-assign पढ़ो/ग_लिखो operations क्रम the non MEC variant */
		cros_ec_lpc_ops.पढ़ो = cros_ec_lpc_पढ़ो_bytes;
		cros_ec_lpc_ops.ग_लिखो = cros_ec_lpc_ग_लिखो_bytes;
		cros_ec_lpc_ops.पढ़ो(EC_LPC_ADDR_MEMMAP + EC_MEMMAP_ID, 2,
				     buf);
		अगर (buf[0] != 'E' || buf[1] != 'C') अणु
			dev_err(dev, "EC ID not detected\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (!devm_request_region(dev, EC_HOST_CMD_REGION0,
				 EC_HOST_CMD_REGION_SIZE, dev_name(dev))) अणु
		dev_err(dev, "couldn't reserve region0\n");
		वापस -EBUSY;
	पूर्ण
	अगर (!devm_request_region(dev, EC_HOST_CMD_REGION1,
				 EC_HOST_CMD_REGION_SIZE, dev_name(dev))) अणु
		dev_err(dev, "couldn't reserve region1\n");
		वापस -EBUSY;
	पूर्ण

	ec_dev = devm_kzalloc(dev, माप(*ec_dev), GFP_KERNEL);
	अगर (!ec_dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ec_dev);
	ec_dev->dev = dev;
	ec_dev->phys_name = dev_name(dev);
	ec_dev->cmd_xfer = cros_ec_cmd_xfer_lpc;
	ec_dev->pkt_xfer = cros_ec_pkt_xfer_lpc;
	ec_dev->cmd_पढ़ोmem = cros_ec_lpc_पढ़ोmem;
	ec_dev->din_size = माप(काष्ठा ec_host_response) +
			   माप(काष्ठा ec_response_get_protocol_info);
	ec_dev->करोut_size = माप(काष्ठा ec_host_request);

	/*
	 * Some boards करो not have an IRQ allotted क्रम cros_ec_lpc,
	 * which makes ENXIO an expected (and safe) scenario.
	 */
	irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (irq > 0)
		ec_dev->irq = irq;
	अन्यथा अगर (irq != -ENXIO) अणु
		dev_err(dev, "couldn't retrieve IRQ number (%d)\n", irq);
		वापस irq;
	पूर्ण

	ret = cros_ec_रेजिस्टर(ec_dev);
	अगर (ret) अणु
		dev_err(dev, "couldn't register ec_dev (%d)\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Connect a notअगरy handler to process MKBP messages अगर we have a
	 * companion ACPI device.
	 */
	adev = ACPI_COMPANION(dev);
	अगर (adev) अणु
		status = acpi_install_notअगरy_handler(adev->handle,
						     ACPI_ALL_NOTIFY,
						     cros_ec_lpc_acpi_notअगरy,
						     ec_dev);
		अगर (ACPI_FAILURE(status))
			dev_warn(dev, "Failed to register notifier %08x\n",
				 status);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_lpc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_device *ec_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा acpi_device *adev;

	adev = ACPI_COMPANION(&pdev->dev);
	अगर (adev)
		acpi_हटाओ_notअगरy_handler(adev->handle, ACPI_ALL_NOTIFY,
					   cros_ec_lpc_acpi_notअगरy);

	वापस cros_ec_unरेजिस्टर(ec_dev);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id cros_ec_lpc_acpi_device_ids[] = अणु
	अणु ACPI_DRV_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cros_ec_lpc_acpi_device_ids);

अटल स्थिर काष्ठा dmi_प्रणाली_id cros_ec_lpc_dmi_table[] __initस्थिर = अणु
	अणु
		/*
		 * Today all Chromebooks/boxes ship with Google_* as version and
		 * coreboot as bios venकरोr. No other प्रणालीs with this
		 * combination are known to date.
		 */
		.matches = अणु
			DMI_MATCH(DMI_BIOS_VENDOR, "coreboot"),
			DMI_MATCH(DMI_BIOS_VERSION, "Google_"),
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * If the box is running custom coreboot firmware then the
		 * DMI BIOS version string will not be matched by "Google_",
		 * but the प्रणाली venकरोr string will still be matched by
		 * "GOOGLE".
		 */
		.matches = अणु
			DMI_MATCH(DMI_BIOS_VENDOR, "coreboot"),
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
		पूर्ण,
	पूर्ण,
	अणु
		/* x86-link, the Chromebook Pixel. */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Link"),
		पूर्ण,
	पूर्ण,
	अणु
		/* x86-samus, the Chromebook Pixel 2. */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Samus"),
		पूर्ण,
	पूर्ण,
	अणु
		/* x86-peppy, the Acer C720 Chromebook. */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Peppy"),
		पूर्ण,
	पूर्ण,
	अणु
		/* x86-glimmer, the Lenovo Thinkpad Yoga 11e. */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Glimmer"),
		पूर्ण,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, cros_ec_lpc_dmi_table);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cros_ec_lpc_suspend(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_device *ec_dev = dev_get_drvdata(dev);

	वापस cros_ec_suspend(ec_dev);
पूर्ण

अटल पूर्णांक cros_ec_lpc_resume(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_device *ec_dev = dev_get_drvdata(dev);

	वापस cros_ec_resume(ec_dev);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops cros_ec_lpc_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(cros_ec_lpc_suspend, cros_ec_lpc_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver cros_ec_lpc_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.acpi_match_table = cros_ec_lpc_acpi_device_ids,
		.pm = &cros_ec_lpc_pm_ops,
	पूर्ण,
	.probe = cros_ec_lpc_probe,
	.हटाओ = cros_ec_lpc_हटाओ,
पूर्ण;

अटल काष्ठा platक्रमm_device cros_ec_lpc_device = अणु
	.name = DRV_NAME
पूर्ण;

अटल acpi_status cros_ec_lpc_parse_device(acpi_handle handle, u32 level,
					    व्योम *context, व्योम **retval)
अणु
	*(bool *)context = true;
	वापस AE_CTRL_TERMINATE;
पूर्ण

अटल पूर्णांक __init cros_ec_lpc_init(व्योम)
अणु
	पूर्णांक ret;
	acpi_status status;

	status = acpi_get_devices(ACPI_DRV_NAME, cros_ec_lpc_parse_device,
				  &cros_ec_lpc_acpi_device_found, शून्य);
	अगर (ACPI_FAILURE(status))
		pr_warn(DRV_NAME ": Looking for %s failed\n", ACPI_DRV_NAME);

	अगर (!cros_ec_lpc_acpi_device_found &&
	    !dmi_check_प्रणाली(cros_ec_lpc_dmi_table)) अणु
		pr_err(DRV_NAME ": unsupported system.\n");
		वापस -ENODEV;
	पूर्ण

	cros_ec_lpc_mec_init(EC_HOST_CMD_REGION0,
			     EC_LPC_ADDR_MEMMAP + EC_MEMMAP_SIZE);

	/* Register the driver */
	ret = platक्रमm_driver_रेजिस्टर(&cros_ec_lpc_driver);
	अगर (ret) अणु
		pr_err(DRV_NAME ": can't register driver: %d\n", ret);
		cros_ec_lpc_mec_destroy();
		वापस ret;
	पूर्ण

	अगर (!cros_ec_lpc_acpi_device_found) अणु
		/* Register the device, and it'll get hooked up स्वतःmatically */
		ret = platक्रमm_device_रेजिस्टर(&cros_ec_lpc_device);
		अगर (ret) अणु
			pr_err(DRV_NAME ": can't register device: %d\n", ret);
			platक्रमm_driver_unरेजिस्टर(&cros_ec_lpc_driver);
			cros_ec_lpc_mec_destroy();
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास cros_ec_lpc_निकास(व्योम)
अणु
	अगर (!cros_ec_lpc_acpi_device_found)
		platक्रमm_device_unरेजिस्टर(&cros_ec_lpc_device);
	platक्रमm_driver_unरेजिस्टर(&cros_ec_lpc_driver);
	cros_ec_lpc_mec_destroy();
पूर्ण

module_init(cros_ec_lpc_init);
module_निकास(cros_ec_lpc_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ChromeOS EC LPC driver");
