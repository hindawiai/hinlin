<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011-2016 Synaptics Incorporated
 * Copyright (c) 2011 Unixphere
 *
 * This driver provides the core support क्रम a single RMI4-based device.
 *
 * The RMI4 specअगरication can be found here (URL split क्रम line length):
 *
 * http://www.synaptics.com/sites/शेष/files/
 *      511-000136-01-Rev-E-RMI4-Interfacing-Guide.pdf
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/irq.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <uapi/linux/input.h>
#समावेश <linux/rmi.h>
#समावेश "rmi_bus.h"
#समावेश "rmi_driver.h"

#घोषणा HAS_NONSTANDARD_PDT_MASK 0x40
#घोषणा RMI4_MAX_PAGE 0xff
#घोषणा RMI4_PAGE_SIZE 0x100
#घोषणा RMI4_PAGE_MASK 0xFF00

#घोषणा RMI_DEVICE_RESET_CMD	0x01
#घोषणा DEFAULT_RESET_DELAY_MS	100

व्योम rmi_मुक्त_function_list(काष्ठा rmi_device *rmi_dev)
अणु
	काष्ठा rmi_function *fn, *पंचांगp;
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);

	rmi_dbg(RMI_DEBUG_CORE, &rmi_dev->dev, "Freeing function list\n");

	/* Doing it in the reverse order so F01 will be हटाओd last */
	list_क्रम_each_entry_safe_reverse(fn, पंचांगp,
					 &data->function_list, node) अणु
		list_del(&fn->node);
		rmi_unरेजिस्टर_function(fn);
	पूर्ण

	devm_kमुक्त(&rmi_dev->dev, data->irq_memory);
	data->irq_memory = शून्य;
	data->irq_status = शून्य;
	data->fn_irq_bits = शून्य;
	data->current_irq_mask = शून्य;
	data->new_irq_mask = शून्य;

	data->f01_container = शून्य;
	data->f34_container = शून्य;
पूर्ण

अटल पूर्णांक reset_one_function(काष्ठा rmi_function *fn)
अणु
	काष्ठा rmi_function_handler *fh;
	पूर्णांक retval = 0;

	अगर (!fn || !fn->dev.driver)
		वापस 0;

	fh = to_rmi_function_handler(fn->dev.driver);
	अगर (fh->reset) अणु
		retval = fh->reset(fn);
		अगर (retval < 0)
			dev_err(&fn->dev, "Reset failed with code %d.\n",
				retval);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक configure_one_function(काष्ठा rmi_function *fn)
अणु
	काष्ठा rmi_function_handler *fh;
	पूर्णांक retval = 0;

	अगर (!fn || !fn->dev.driver)
		वापस 0;

	fh = to_rmi_function_handler(fn->dev.driver);
	अगर (fh->config) अणु
		retval = fh->config(fn);
		अगर (retval < 0)
			dev_err(&fn->dev, "Config failed with code %d.\n",
				retval);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक rmi_driver_process_reset_requests(काष्ठा rmi_device *rmi_dev)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा rmi_function *entry;
	पूर्णांक retval;

	list_क्रम_each_entry(entry, &data->function_list, node) अणु
		retval = reset_one_function(entry);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_driver_process_config_requests(काष्ठा rmi_device *rmi_dev)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा rmi_function *entry;
	पूर्णांक retval;

	list_क्रम_each_entry(entry, &data->function_list, node) अणु
		retval = configure_one_function(entry);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_process_पूर्णांकerrupt_requests(काष्ठा rmi_device *rmi_dev)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा device *dev = &rmi_dev->dev;
	पूर्णांक i;
	पूर्णांक error;

	अगर (!data)
		वापस 0;

	अगर (!data->attn_data.data) अणु
		error = rmi_पढ़ो_block(rmi_dev,
				data->f01_container->fd.data_base_addr + 1,
				data->irq_status, data->num_of_irq_regs);
		अगर (error < 0) अणु
			dev_err(dev, "Failed to read irqs, code=%d\n", error);
			वापस error;
		पूर्ण
	पूर्ण

	mutex_lock(&data->irq_mutex);
	biपंचांगap_and(data->irq_status, data->irq_status, data->fn_irq_bits,
	       data->irq_count);
	/*
	 * At this poपूर्णांक, irq_status has all bits that are set in the
	 * पूर्णांकerrupt status रेजिस्टर and are enabled.
	 */
	mutex_unlock(&data->irq_mutex);

	क्रम_each_set_bit(i, data->irq_status, data->irq_count)
		handle_nested_irq(irq_find_mapping(data->irqकरोमुख्य, i));

	अगर (data->input)
		input_sync(data->input);

	वापस 0;
पूर्ण

व्योम rmi_set_attn_data(काष्ठा rmi_device *rmi_dev, अचिन्हित दीर्घ irq_status,
		       व्योम *data, माप_प्रकार size)
अणु
	काष्ठा rmi_driver_data *drvdata = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा rmi4_attn_data attn_data;
	व्योम *fअगरo_data;

	अगर (!drvdata->enabled)
		वापस;

	fअगरo_data = kmemdup(data, size, GFP_ATOMIC);
	अगर (!fअगरo_data)
		वापस;

	attn_data.irq_status = irq_status;
	attn_data.size = size;
	attn_data.data = fअगरo_data;

	kfअगरo_put(&drvdata->attn_fअगरo, attn_data);
पूर्ण
EXPORT_SYMBOL_GPL(rmi_set_attn_data);

अटल irqवापस_t rmi_irq_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rmi_device *rmi_dev = dev_id;
	काष्ठा rmi_driver_data *drvdata = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा rmi4_attn_data attn_data = अणु0पूर्ण;
	पूर्णांक ret, count;

	count = kfअगरo_get(&drvdata->attn_fअगरo, &attn_data);
	अगर (count) अणु
		*(drvdata->irq_status) = attn_data.irq_status;
		drvdata->attn_data = attn_data;
	पूर्ण

	ret = rmi_process_पूर्णांकerrupt_requests(rmi_dev);
	अगर (ret)
		rmi_dbg(RMI_DEBUG_CORE, &rmi_dev->dev,
			"Failed to process interrupt request: %d\n", ret);

	अगर (count) अणु
		kमुक्त(attn_data.data);
		drvdata->attn_data.data = शून्य;
	पूर्ण

	अगर (!kfअगरo_is_empty(&drvdata->attn_fअगरo))
		वापस rmi_irq_fn(irq, dev_id);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rmi_irq_init(काष्ठा rmi_device *rmi_dev)
अणु
	काष्ठा rmi_device_platक्रमm_data *pdata = rmi_get_platक्रमm_data(rmi_dev);
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	पूर्णांक irq_flags = irq_get_trigger_type(pdata->irq);
	पूर्णांक ret;

	अगर (!irq_flags)
		irq_flags = IRQF_TRIGGER_LOW;

	ret = devm_request_thपढ़ोed_irq(&rmi_dev->dev, pdata->irq, शून्य,
					rmi_irq_fn, irq_flags | IRQF_ONESHOT,
					dev_driver_string(rmi_dev->xport->dev),
					rmi_dev);
	अगर (ret < 0) अणु
		dev_err(&rmi_dev->dev, "Failed to register interrupt %d\n",
			pdata->irq);

		वापस ret;
	पूर्ण

	data->enabled = true;

	वापस 0;
पूर्ण

काष्ठा rmi_function *rmi_find_function(काष्ठा rmi_device *rmi_dev, u8 number)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा rmi_function *entry;

	list_क्रम_each_entry(entry, &data->function_list, node) अणु
		अगर (entry->fd.function_number == number)
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक suspend_one_function(काष्ठा rmi_function *fn)
अणु
	काष्ठा rmi_function_handler *fh;
	पूर्णांक retval = 0;

	अगर (!fn || !fn->dev.driver)
		वापस 0;

	fh = to_rmi_function_handler(fn->dev.driver);
	अगर (fh->suspend) अणु
		retval = fh->suspend(fn);
		अगर (retval < 0)
			dev_err(&fn->dev, "Suspend failed with code %d.\n",
				retval);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक rmi_suspend_functions(काष्ठा rmi_device *rmi_dev)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा rmi_function *entry;
	पूर्णांक retval;

	list_क्रम_each_entry(entry, &data->function_list, node) अणु
		retval = suspend_one_function(entry);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक resume_one_function(काष्ठा rmi_function *fn)
अणु
	काष्ठा rmi_function_handler *fh;
	पूर्णांक retval = 0;

	अगर (!fn || !fn->dev.driver)
		वापस 0;

	fh = to_rmi_function_handler(fn->dev.driver);
	अगर (fh->resume) अणु
		retval = fh->resume(fn);
		अगर (retval < 0)
			dev_err(&fn->dev, "Resume failed with code %d.\n",
				retval);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक rmi_resume_functions(काष्ठा rmi_device *rmi_dev)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा rmi_function *entry;
	पूर्णांक retval;

	list_क्रम_each_entry(entry, &data->function_list, node) अणु
		retval = resume_one_function(entry);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rmi_enable_sensor(काष्ठा rmi_device *rmi_dev)
अणु
	पूर्णांक retval = 0;

	retval = rmi_driver_process_config_requests(rmi_dev);
	अगर (retval < 0)
		वापस retval;

	वापस rmi_process_पूर्णांकerrupt_requests(rmi_dev);
पूर्ण

/**
 * rmi_driver_set_input_params - set input device id and other data.
 *
 * @rmi_dev: Poपूर्णांकer to an RMI device
 * @input: Poपूर्णांकer to input device
 *
 */
अटल पूर्णांक rmi_driver_set_input_params(काष्ठा rmi_device *rmi_dev,
				काष्ठा input_dev *input)
अणु
	input->name = SYNAPTICS_INPUT_DEVICE_NAME;
	input->id.venकरोr  = SYNAPTICS_VENDOR_ID;
	input->id.bustype = BUS_RMI;
	वापस 0;
पूर्ण

अटल व्योम rmi_driver_set_input_name(काष्ठा rmi_device *rmi_dev,
				काष्ठा input_dev *input)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	स्थिर अक्षर *device_name = rmi_f01_get_product_ID(data->f01_container);
	अक्षर *name;

	name = devm_kaप्र_लिखो(&rmi_dev->dev, GFP_KERNEL,
			      "Synaptics %s", device_name);
	अगर (!name)
		वापस;

	input->name = name;
पूर्ण

अटल पूर्णांक rmi_driver_set_irq_bits(काष्ठा rmi_device *rmi_dev,
				   अचिन्हित दीर्घ *mask)
अणु
	पूर्णांक error = 0;
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा device *dev = &rmi_dev->dev;

	mutex_lock(&data->irq_mutex);
	biपंचांगap_or(data->new_irq_mask,
		  data->current_irq_mask, mask, data->irq_count);

	error = rmi_ग_लिखो_block(rmi_dev,
			data->f01_container->fd.control_base_addr + 1,
			data->new_irq_mask, data->num_of_irq_regs);
	अगर (error < 0) अणु
		dev_err(dev, "%s: Failed to change enabled interrupts!",
							__func__);
		जाओ error_unlock;
	पूर्ण
	biपंचांगap_copy(data->current_irq_mask, data->new_irq_mask,
		    data->num_of_irq_regs);

	biपंचांगap_or(data->fn_irq_bits, data->fn_irq_bits, mask, data->irq_count);

error_unlock:
	mutex_unlock(&data->irq_mutex);
	वापस error;
पूर्ण

अटल पूर्णांक rmi_driver_clear_irq_bits(काष्ठा rmi_device *rmi_dev,
				     अचिन्हित दीर्घ *mask)
अणु
	पूर्णांक error = 0;
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा device *dev = &rmi_dev->dev;

	mutex_lock(&data->irq_mutex);
	biपंचांगap_andnot(data->fn_irq_bits,
		      data->fn_irq_bits, mask, data->irq_count);
	biपंचांगap_andnot(data->new_irq_mask,
		  data->current_irq_mask, mask, data->irq_count);

	error = rmi_ग_लिखो_block(rmi_dev,
			data->f01_container->fd.control_base_addr + 1,
			data->new_irq_mask, data->num_of_irq_regs);
	अगर (error < 0) अणु
		dev_err(dev, "%s: Failed to change enabled interrupts!",
							__func__);
		जाओ error_unlock;
	पूर्ण
	biपंचांगap_copy(data->current_irq_mask, data->new_irq_mask,
		    data->num_of_irq_regs);

error_unlock:
	mutex_unlock(&data->irq_mutex);
	वापस error;
पूर्ण

अटल पूर्णांक rmi_driver_reset_handler(काष्ठा rmi_device *rmi_dev)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	पूर्णांक error;

	/*
	 * Can get called beक्रमe the driver is fully पढ़ोy to deal with
	 * this situation.
	 */
	अगर (!data || !data->f01_container) अणु
		dev_warn(&rmi_dev->dev,
			 "Not ready to handle reset yet!\n");
		वापस 0;
	पूर्ण

	error = rmi_पढ़ो_block(rmi_dev,
			       data->f01_container->fd.control_base_addr + 1,
			       data->current_irq_mask, data->num_of_irq_regs);
	अगर (error < 0) अणु
		dev_err(&rmi_dev->dev, "%s: Failed to read current IRQ mask.\n",
			__func__);
		वापस error;
	पूर्ण

	error = rmi_driver_process_reset_requests(rmi_dev);
	अगर (error < 0)
		वापस error;

	error = rmi_driver_process_config_requests(rmi_dev);
	अगर (error < 0)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_पढ़ो_pdt_entry(काष्ठा rmi_device *rmi_dev,
			      काष्ठा pdt_entry *entry, u16 pdt_address)
अणु
	u8 buf[RMI_PDT_ENTRY_SIZE];
	पूर्णांक error;

	error = rmi_पढ़ो_block(rmi_dev, pdt_address, buf, RMI_PDT_ENTRY_SIZE);
	अगर (error) अणु
		dev_err(&rmi_dev->dev, "Read PDT entry at %#06x failed, code: %d.\n",
				pdt_address, error);
		वापस error;
	पूर्ण

	entry->page_start = pdt_address & RMI4_PAGE_MASK;
	entry->query_base_addr = buf[0];
	entry->command_base_addr = buf[1];
	entry->control_base_addr = buf[2];
	entry->data_base_addr = buf[3];
	entry->पूर्णांकerrupt_source_count = buf[4] & RMI_PDT_INT_SOURCE_COUNT_MASK;
	entry->function_version = (buf[4] & RMI_PDT_FUNCTION_VERSION_MASK) >> 5;
	entry->function_number = buf[5];

	वापस 0;
पूर्ण

अटल व्योम rmi_driver_copy_pdt_to_fd(स्थिर काष्ठा pdt_entry *pdt,
				      काष्ठा rmi_function_descriptor *fd)
अणु
	fd->query_base_addr = pdt->query_base_addr + pdt->page_start;
	fd->command_base_addr = pdt->command_base_addr + pdt->page_start;
	fd->control_base_addr = pdt->control_base_addr + pdt->page_start;
	fd->data_base_addr = pdt->data_base_addr + pdt->page_start;
	fd->function_number = pdt->function_number;
	fd->पूर्णांकerrupt_source_count = pdt->पूर्णांकerrupt_source_count;
	fd->function_version = pdt->function_version;
पूर्ण

#घोषणा RMI_SCAN_CONTINUE	0
#घोषणा RMI_SCAN_DONE		1

अटल पूर्णांक rmi_scan_pdt_page(काष्ठा rmi_device *rmi_dev,
			     पूर्णांक page,
			     पूर्णांक *empty_pages,
			     व्योम *ctx,
			     पूर्णांक (*callback)(काष्ठा rmi_device *rmi_dev,
					     व्योम *ctx,
					     स्थिर काष्ठा pdt_entry *entry))
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा pdt_entry pdt_entry;
	u16 page_start = RMI4_PAGE_SIZE * page;
	u16 pdt_start = page_start + PDT_START_SCAN_LOCATION;
	u16 pdt_end = page_start + PDT_END_SCAN_LOCATION;
	u16 addr;
	पूर्णांक error;
	पूर्णांक retval;

	क्रम (addr = pdt_start; addr >= pdt_end; addr -= RMI_PDT_ENTRY_SIZE) अणु
		error = rmi_पढ़ो_pdt_entry(rmi_dev, &pdt_entry, addr);
		अगर (error)
			वापस error;

		अगर (RMI4_END_OF_PDT(pdt_entry.function_number))
			अवरोध;

		retval = callback(rmi_dev, ctx, &pdt_entry);
		अगर (retval != RMI_SCAN_CONTINUE)
			वापस retval;
	पूर्ण

	/*
	 * Count number of empty PDT pages. If a gap of two pages
	 * or more is found, stop scanning.
	 */
	अगर (addr == pdt_start)
		++*empty_pages;
	अन्यथा
		*empty_pages = 0;

	वापस (data->bootloader_mode || *empty_pages >= 2) ?
					RMI_SCAN_DONE : RMI_SCAN_CONTINUE;
पूर्ण

पूर्णांक rmi_scan_pdt(काष्ठा rmi_device *rmi_dev, व्योम *ctx,
		 पूर्णांक (*callback)(काष्ठा rmi_device *rmi_dev,
		 व्योम *ctx, स्थिर काष्ठा pdt_entry *entry))
अणु
	पूर्णांक page;
	पूर्णांक empty_pages = 0;
	पूर्णांक retval = RMI_SCAN_DONE;

	क्रम (page = 0; page <= RMI4_MAX_PAGE; page++) अणु
		retval = rmi_scan_pdt_page(rmi_dev, page, &empty_pages,
					   ctx, callback);
		अगर (retval != RMI_SCAN_CONTINUE)
			अवरोध;
	पूर्ण

	वापस retval < 0 ? retval : 0;
पूर्ण

पूर्णांक rmi_पढ़ो_रेजिस्टर_desc(काष्ठा rmi_device *d, u16 addr,
				काष्ठा rmi_रेजिस्टर_descriptor *rdesc)
अणु
	पूर्णांक ret;
	u8 size_presence_reg;
	u8 buf[35];
	पूर्णांक presense_offset = 1;
	u8 *काष्ठा_buf;
	पूर्णांक reg;
	पूर्णांक offset = 0;
	पूर्णांक map_offset = 0;
	पूर्णांक i;
	पूर्णांक b;

	/*
	 * The first रेजिस्टर of the रेजिस्टर descriptor is the size of
	 * the रेजिस्टर descriptor's presense रेजिस्टर.
	 */
	ret = rmi_पढ़ो(d, addr, &size_presence_reg);
	अगर (ret)
		वापस ret;
	++addr;

	अगर (size_presence_reg < 0 || size_presence_reg > 35)
		वापस -EIO;

	स_रखो(buf, 0, माप(buf));

	/*
	 * The presence रेजिस्टर contains the size of the रेजिस्टर काष्ठाure
	 * and a biपंचांगap which identअगरied which packet रेजिस्टरs are present
	 * क्रम this particular रेजिस्टर type (ie query, control, or data).
	 */
	ret = rmi_पढ़ो_block(d, addr, buf, size_presence_reg);
	अगर (ret)
		वापस ret;
	++addr;

	अगर (buf[0] == 0) अणु
		presense_offset = 3;
		rdesc->काष्ठा_size = buf[1] | (buf[2] << 8);
	पूर्ण अन्यथा अणु
		rdesc->काष्ठा_size = buf[0];
	पूर्ण

	क्रम (i = presense_offset; i < size_presence_reg; i++) अणु
		क्रम (b = 0; b < 8; b++) अणु
			अगर (buf[i] & (0x1 << b))
				biपंचांगap_set(rdesc->presense_map, map_offset, 1);
			++map_offset;
		पूर्ण
	पूर्ण

	rdesc->num_रेजिस्टरs = biपंचांगap_weight(rdesc->presense_map,
						RMI_REG_DESC_PRESENSE_BITS);

	rdesc->रेजिस्टरs = devm_kसुस्मृति(&d->dev,
					rdesc->num_रेजिस्टरs,
					माप(काष्ठा rmi_रेजिस्टर_desc_item),
					GFP_KERNEL);
	अगर (!rdesc->रेजिस्टरs)
		वापस -ENOMEM;

	/*
	 * Allocate a temporary buffer to hold the रेजिस्टर काष्ठाure.
	 * I'm not using devm_kzalloc here since it will not be retained
	 * after निकासing this function
	 */
	काष्ठा_buf = kzalloc(rdesc->काष्ठा_size, GFP_KERNEL);
	अगर (!काष्ठा_buf)
		वापस -ENOMEM;

	/*
	 * The रेजिस्टर काष्ठाure contains inक्रमmation about every packet
	 * रेजिस्टर of this type. This includes the size of the packet
	 * रेजिस्टर and a biपंचांगap of all subpackets contained in the packet
	 * रेजिस्टर.
	 */
	ret = rmi_पढ़ो_block(d, addr, काष्ठा_buf, rdesc->काष्ठा_size);
	अगर (ret)
		जाओ मुक्त_काष्ठा_buff;

	reg = find_first_bit(rdesc->presense_map, RMI_REG_DESC_PRESENSE_BITS);
	क्रम (i = 0; i < rdesc->num_रेजिस्टरs; i++) अणु
		काष्ठा rmi_रेजिस्टर_desc_item *item = &rdesc->रेजिस्टरs[i];
		पूर्णांक reg_size = काष्ठा_buf[offset];

		++offset;
		अगर (reg_size == 0) अणु
			reg_size = काष्ठा_buf[offset] |
					(काष्ठा_buf[offset + 1] << 8);
			offset += 2;
		पूर्ण

		अगर (reg_size == 0) अणु
			reg_size = काष्ठा_buf[offset] |
					(काष्ठा_buf[offset + 1] << 8) |
					(काष्ठा_buf[offset + 2] << 16) |
					(काष्ठा_buf[offset + 3] << 24);
			offset += 4;
		पूर्ण

		item->reg = reg;
		item->reg_size = reg_size;

		map_offset = 0;

		करो अणु
			क्रम (b = 0; b < 7; b++) अणु
				अगर (काष्ठा_buf[offset] & (0x1 << b))
					biपंचांगap_set(item->subpacket_map,
						map_offset, 1);
				++map_offset;
			पूर्ण
		पूर्ण जबतक (काष्ठा_buf[offset++] & 0x80);

		item->num_subpackets = biपंचांगap_weight(item->subpacket_map,
						RMI_REG_DESC_SUBPACKET_BITS);

		rmi_dbg(RMI_DEBUG_CORE, &d->dev,
			"%s: reg: %d reg size: %ld subpackets: %d\n", __func__,
			item->reg, item->reg_size, item->num_subpackets);

		reg = find_next_bit(rdesc->presense_map,
				RMI_REG_DESC_PRESENSE_BITS, reg + 1);
	पूर्ण

मुक्त_काष्ठा_buff:
	kमुक्त(काष्ठा_buf);
	वापस ret;
पूर्ण

स्थिर काष्ठा rmi_रेजिस्टर_desc_item *rmi_get_रेजिस्टर_desc_item(
				काष्ठा rmi_रेजिस्टर_descriptor *rdesc, u16 reg)
अणु
	स्थिर काष्ठा rmi_रेजिस्टर_desc_item *item;
	पूर्णांक i;

	क्रम (i = 0; i < rdesc->num_रेजिस्टरs; i++) अणु
		item = &rdesc->रेजिस्टरs[i];
		अगर (item->reg == reg)
			वापस item;
	पूर्ण

	वापस शून्य;
पूर्ण

माप_प्रकार rmi_रेजिस्टर_desc_calc_size(काष्ठा rmi_रेजिस्टर_descriptor *rdesc)
अणु
	स्थिर काष्ठा rmi_रेजिस्टर_desc_item *item;
	पूर्णांक i;
	माप_प्रकार size = 0;

	क्रम (i = 0; i < rdesc->num_रेजिस्टरs; i++) अणु
		item = &rdesc->रेजिस्टरs[i];
		size += item->reg_size;
	पूर्ण
	वापस size;
पूर्ण

/* Compute the रेजिस्टर offset relative to the base address */
पूर्णांक rmi_रेजिस्टर_desc_calc_reg_offset(
		काष्ठा rmi_रेजिस्टर_descriptor *rdesc, u16 reg)
अणु
	स्थिर काष्ठा rmi_रेजिस्टर_desc_item *item;
	पूर्णांक offset = 0;
	पूर्णांक i;

	क्रम (i = 0; i < rdesc->num_रेजिस्टरs; i++) अणु
		item = &rdesc->रेजिस्टरs[i];
		अगर (item->reg == reg)
			वापस offset;
		++offset;
	पूर्ण
	वापस -1;
पूर्ण

bool rmi_रेजिस्टर_desc_has_subpacket(स्थिर काष्ठा rmi_रेजिस्टर_desc_item *item,
	u8 subpacket)
अणु
	वापस find_next_bit(item->subpacket_map, RMI_REG_DESC_PRESENSE_BITS,
				subpacket) == subpacket;
पूर्ण

अटल पूर्णांक rmi_check_bootloader_mode(काष्ठा rmi_device *rmi_dev,
				     स्थिर काष्ठा pdt_entry *pdt)
अणु
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	पूर्णांक ret;
	u8 status;

	अगर (pdt->function_number == 0x34 && pdt->function_version > 1) अणु
		ret = rmi_पढ़ो(rmi_dev, pdt->data_base_addr, &status);
		अगर (ret) अणु
			dev_err(&rmi_dev->dev,
				"Failed to read F34 status: %d.\n", ret);
			वापस ret;
		पूर्ण

		अगर (status & BIT(7))
			data->bootloader_mode = true;
	पूर्ण अन्यथा अगर (pdt->function_number == 0x01) अणु
		ret = rmi_पढ़ो(rmi_dev, pdt->data_base_addr, &status);
		अगर (ret) अणु
			dev_err(&rmi_dev->dev,
				"Failed to read F01 status: %d.\n", ret);
			वापस ret;
		पूर्ण

		अगर (status & BIT(6))
			data->bootloader_mode = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_count_irqs(काष्ठा rmi_device *rmi_dev,
			 व्योम *ctx, स्थिर काष्ठा pdt_entry *pdt)
अणु
	पूर्णांक *irq_count = ctx;
	पूर्णांक ret;

	*irq_count += pdt->पूर्णांकerrupt_source_count;

	ret = rmi_check_bootloader_mode(rmi_dev, pdt);
	अगर (ret < 0)
		वापस ret;

	वापस RMI_SCAN_CONTINUE;
पूर्ण

पूर्णांक rmi_initial_reset(काष्ठा rmi_device *rmi_dev, व्योम *ctx,
		      स्थिर काष्ठा pdt_entry *pdt)
अणु
	पूर्णांक error;

	अगर (pdt->function_number == 0x01) अणु
		u16 cmd_addr = pdt->page_start + pdt->command_base_addr;
		u8 cmd_buf = RMI_DEVICE_RESET_CMD;
		स्थिर काष्ठा rmi_device_platक्रमm_data *pdata =
				rmi_get_platक्रमm_data(rmi_dev);

		अगर (rmi_dev->xport->ops->reset) अणु
			error = rmi_dev->xport->ops->reset(rmi_dev->xport,
								cmd_addr);
			अगर (error)
				वापस error;

			वापस RMI_SCAN_DONE;
		पूर्ण

		rmi_dbg(RMI_DEBUG_CORE, &rmi_dev->dev, "Sending reset\n");
		error = rmi_ग_लिखो_block(rmi_dev, cmd_addr, &cmd_buf, 1);
		अगर (error) अणु
			dev_err(&rmi_dev->dev,
				"Initial reset failed. Code = %d.\n", error);
			वापस error;
		पूर्ण

		mdelay(pdata->reset_delay_ms ?: DEFAULT_RESET_DELAY_MS);

		वापस RMI_SCAN_DONE;
	पूर्ण

	/* F01 should always be on page 0. If we करोn't find it there, fail. */
	वापस pdt->page_start == 0 ? RMI_SCAN_CONTINUE : -ENODEV;
पूर्ण

अटल पूर्णांक rmi_create_function(काष्ठा rmi_device *rmi_dev,
			       व्योम *ctx, स्थिर काष्ठा pdt_entry *pdt)
अणु
	काष्ठा device *dev = &rmi_dev->dev;
	काष्ठा rmi_driver_data *data = dev_get_drvdata(dev);
	पूर्णांक *current_irq_count = ctx;
	काष्ठा rmi_function *fn;
	पूर्णांक i;
	पूर्णांक error;

	rmi_dbg(RMI_DEBUG_CORE, dev, "Initializing F%02X.\n",
			pdt->function_number);

	fn = kzalloc(माप(काष्ठा rmi_function) +
			BITS_TO_LONGS(data->irq_count) * माप(अचिन्हित दीर्घ),
		     GFP_KERNEL);
	अगर (!fn) अणु
		dev_err(dev, "Failed to allocate memory for F%02X\n",
			pdt->function_number);
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&fn->node);
	rmi_driver_copy_pdt_to_fd(pdt, &fn->fd);

	fn->rmi_dev = rmi_dev;

	fn->num_of_irqs = pdt->पूर्णांकerrupt_source_count;
	fn->irq_pos = *current_irq_count;
	*current_irq_count += fn->num_of_irqs;

	क्रम (i = 0; i < fn->num_of_irqs; i++)
		set_bit(fn->irq_pos + i, fn->irq_mask);

	error = rmi_रेजिस्टर_function(fn);
	अगर (error)
		वापस error;

	अगर (pdt->function_number == 0x01)
		data->f01_container = fn;
	अन्यथा अगर (pdt->function_number == 0x34)
		data->f34_container = fn;

	list_add_tail(&fn->node, &data->function_list);

	वापस RMI_SCAN_CONTINUE;
पूर्ण

व्योम rmi_enable_irq(काष्ठा rmi_device *rmi_dev, bool clear_wake)
अणु
	काष्ठा rmi_device_platक्रमm_data *pdata = rmi_get_platक्रमm_data(rmi_dev);
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	पूर्णांक irq = pdata->irq;
	पूर्णांक irq_flags;
	पूर्णांक retval;

	mutex_lock(&data->enabled_mutex);

	अगर (data->enabled)
		जाओ out;

	enable_irq(irq);
	data->enabled = true;
	अगर (clear_wake && device_may_wakeup(rmi_dev->xport->dev)) अणु
		retval = disable_irq_wake(irq);
		अगर (retval)
			dev_warn(&rmi_dev->dev,
				 "Failed to disable irq for wake: %d\n",
				 retval);
	पूर्ण

	/*
	 * Call rmi_process_पूर्णांकerrupt_requests() after enabling irq,
	 * otherwise we may lose पूर्णांकerrupt on edge-triggered प्रणालीs.
	 */
	irq_flags = irq_get_trigger_type(pdata->irq);
	अगर (irq_flags & IRQ_TYPE_EDGE_BOTH)
		rmi_process_पूर्णांकerrupt_requests(rmi_dev);

out:
	mutex_unlock(&data->enabled_mutex);
पूर्ण

व्योम rmi_disable_irq(काष्ठा rmi_device *rmi_dev, bool enable_wake)
अणु
	काष्ठा rmi_device_platक्रमm_data *pdata = rmi_get_platक्रमm_data(rmi_dev);
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा rmi4_attn_data attn_data = अणु0पूर्ण;
	पूर्णांक irq = pdata->irq;
	पूर्णांक retval, count;

	mutex_lock(&data->enabled_mutex);

	अगर (!data->enabled)
		जाओ out;

	data->enabled = false;
	disable_irq(irq);
	अगर (enable_wake && device_may_wakeup(rmi_dev->xport->dev)) अणु
		retval = enable_irq_wake(irq);
		अगर (retval)
			dev_warn(&rmi_dev->dev,
				 "Failed to enable irq for wake: %d\n",
				 retval);
	पूर्ण

	/* make sure the fअगरo is clean */
	जबतक (!kfअगरo_is_empty(&data->attn_fअगरo)) अणु
		count = kfअगरo_get(&data->attn_fअगरo, &attn_data);
		अगर (count)
			kमुक्त(attn_data.data);
	पूर्ण

out:
	mutex_unlock(&data->enabled_mutex);
पूर्ण

पूर्णांक rmi_driver_suspend(काष्ठा rmi_device *rmi_dev, bool enable_wake)
अणु
	पूर्णांक retval;

	retval = rmi_suspend_functions(rmi_dev);
	अगर (retval)
		dev_warn(&rmi_dev->dev, "Failed to suspend functions: %d\n",
			retval);

	rmi_disable_irq(rmi_dev, enable_wake);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(rmi_driver_suspend);

पूर्णांक rmi_driver_resume(काष्ठा rmi_device *rmi_dev, bool clear_wake)
अणु
	पूर्णांक retval;

	rmi_enable_irq(rmi_dev, clear_wake);

	retval = rmi_resume_functions(rmi_dev);
	अगर (retval)
		dev_warn(&rmi_dev->dev, "Failed to suspend functions: %d\n",
			retval);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(rmi_driver_resume);

अटल पूर्णांक rmi_driver_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा rmi_device *rmi_dev = to_rmi_device(dev);
	काष्ठा rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);

	rmi_disable_irq(rmi_dev, false);

	irq_करोमुख्य_हटाओ(data->irqकरोमुख्य);
	data->irqकरोमुख्य = शून्य;

	rmi_f34_हटाओ_sysfs(rmi_dev);
	rmi_मुक्त_function_list(rmi_dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक rmi_driver_of_probe(काष्ठा device *dev,
				काष्ठा rmi_device_platक्रमm_data *pdata)
अणु
	पूर्णांक retval;

	retval = rmi_of_property_पढ़ो_u32(dev, &pdata->reset_delay_ms,
					"syna,reset-delay-ms", 1);
	अगर (retval)
		वापस retval;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक rmi_driver_of_probe(काष्ठा device *dev,
					काष्ठा rmi_device_platक्रमm_data *pdata)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

पूर्णांक rmi_probe_पूर्णांकerrupts(काष्ठा rmi_driver_data *data)
अणु
	काष्ठा rmi_device *rmi_dev = data->rmi_dev;
	काष्ठा device *dev = &rmi_dev->dev;
	काष्ठा fwnode_handle *fwnode = rmi_dev->xport->dev->fwnode;
	पूर्णांक irq_count = 0;
	माप_प्रकार size;
	पूर्णांक retval;

	/*
	 * We need to count the IRQs and allocate their storage beक्रमe scanning
	 * the PDT and creating the function entries, because adding a new
	 * function can trigger events that result in the IRQ related storage
	 * being accessed.
	 */
	rmi_dbg(RMI_DEBUG_CORE, dev, "%s: Counting IRQs.\n", __func__);
	data->bootloader_mode = false;

	retval = rmi_scan_pdt(rmi_dev, &irq_count, rmi_count_irqs);
	अगर (retval < 0) अणु
		dev_err(dev, "IRQ counting failed with code %d.\n", retval);
		वापस retval;
	पूर्ण

	अगर (data->bootloader_mode)
		dev_warn(dev, "Device in bootloader mode.\n");

	/* Allocate and रेजिस्टर a linear revmap irq_करोमुख्य */
	data->irqकरोमुख्य = irq_करोमुख्य_create_linear(fwnode, irq_count,
						   &irq_करोमुख्य_simple_ops,
						   data);
	अगर (!data->irqकरोमुख्य) अणु
		dev_err(&rmi_dev->dev, "Failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	data->irq_count = irq_count;
	data->num_of_irq_regs = (data->irq_count + 7) / 8;

	size = BITS_TO_LONGS(data->irq_count) * माप(अचिन्हित दीर्घ);
	data->irq_memory = devm_kसुस्मृति(dev, size, 4, GFP_KERNEL);
	अगर (!data->irq_memory) अणु
		dev_err(dev, "Failed to allocate memory for irq masks.\n");
		वापस -ENOMEM;
	पूर्ण

	data->irq_status	= data->irq_memory + size * 0;
	data->fn_irq_bits	= data->irq_memory + size * 1;
	data->current_irq_mask	= data->irq_memory + size * 2;
	data->new_irq_mask	= data->irq_memory + size * 3;

	वापस retval;
पूर्ण

पूर्णांक rmi_init_functions(काष्ठा rmi_driver_data *data)
अणु
	काष्ठा rmi_device *rmi_dev = data->rmi_dev;
	काष्ठा device *dev = &rmi_dev->dev;
	पूर्णांक irq_count = 0;
	पूर्णांक retval;

	rmi_dbg(RMI_DEBUG_CORE, dev, "%s: Creating functions.\n", __func__);
	retval = rmi_scan_pdt(rmi_dev, &irq_count, rmi_create_function);
	अगर (retval < 0) अणु
		dev_err(dev, "Function creation failed with code %d.\n",
			retval);
		जाओ err_destroy_functions;
	पूर्ण

	अगर (!data->f01_container) अणु
		dev_err(dev, "Missing F01 container!\n");
		retval = -EINVAL;
		जाओ err_destroy_functions;
	पूर्ण

	retval = rmi_पढ़ो_block(rmi_dev,
				data->f01_container->fd.control_base_addr + 1,
				data->current_irq_mask, data->num_of_irq_regs);
	अगर (retval < 0) अणु
		dev_err(dev, "%s: Failed to read current IRQ mask.\n",
			__func__);
		जाओ err_destroy_functions;
	पूर्ण

	वापस 0;

err_destroy_functions:
	rmi_मुक्त_function_list(rmi_dev);
	वापस retval;
पूर्ण

अटल पूर्णांक rmi_driver_probe(काष्ठा device *dev)
अणु
	काष्ठा rmi_driver *rmi_driver;
	काष्ठा rmi_driver_data *data;
	काष्ठा rmi_device_platक्रमm_data *pdata;
	काष्ठा rmi_device *rmi_dev;
	पूर्णांक retval;

	rmi_dbg(RMI_DEBUG_CORE, dev, "%s: Starting probe.\n",
			__func__);

	अगर (!rmi_is_physical_device(dev)) अणु
		rmi_dbg(RMI_DEBUG_CORE, dev, "Not a physical device.\n");
		वापस -ENODEV;
	पूर्ण

	rmi_dev = to_rmi_device(dev);
	rmi_driver = to_rmi_driver(dev->driver);
	rmi_dev->driver = rmi_driver;

	pdata = rmi_get_platक्रमm_data(rmi_dev);

	अगर (rmi_dev->xport->dev->of_node) अणु
		retval = rmi_driver_of_probe(rmi_dev->xport->dev, pdata);
		अगर (retval)
			वापस retval;
	पूर्ण

	data = devm_kzalloc(dev, माप(काष्ठा rmi_driver_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&data->function_list);
	data->rmi_dev = rmi_dev;
	dev_set_drvdata(&rmi_dev->dev, data);

	/*
	 * Right beक्रमe a warm boot, the sensor might be in some unusual state,
	 * such as F54 diagnostics, or F34 bootloader mode after a firmware
	 * or configuration update.  In order to clear the sensor to a known
	 * state and/or apply any updates, we issue a initial reset to clear any
	 * previous settings and क्रमce it पूर्णांकo normal operation.
	 *
	 * We have to करो this beक्रमe actually building the PDT because
	 * the reflash updates (अगर any) might cause various रेजिस्टरs to move
	 * around.
	 *
	 * For a number of reasons, this initial reset may fail to वापस
	 * within the specअगरied समय, but we'll still be able to bring up the
	 * driver normally after that failure.  This occurs most commonly in
	 * a cold boot situation (where then firmware takes दीर्घer to come up
	 * than from a warm boot) and the reset_delay_ms in the platक्रमm data
	 * has been set too लघु to accommodate that.  Since the sensor will
	 * eventually come up and be usable, we करोn't want to just fail here
	 * and leave the customer's device unusable.  So we warn them, and
	 * जारी processing.
	 */
	retval = rmi_scan_pdt(rmi_dev, शून्य, rmi_initial_reset);
	अगर (retval < 0)
		dev_warn(dev, "RMI initial reset failed! Continuing in spite of this.\n");

	retval = rmi_पढ़ो(rmi_dev, PDT_PROPERTIES_LOCATION, &data->pdt_props);
	अगर (retval < 0) अणु
		/*
		 * we'll prपूर्णांक out a warning and जारी since
		 * failure to get the PDT properties is not a cause to fail
		 */
		dev_warn(dev, "Could not read PDT properties from %#06x (code %d). Assuming 0x00.\n",
			 PDT_PROPERTIES_LOCATION, retval);
	पूर्ण

	mutex_init(&data->irq_mutex);
	mutex_init(&data->enabled_mutex);

	retval = rmi_probe_पूर्णांकerrupts(data);
	अगर (retval)
		जाओ err;

	अगर (rmi_dev->xport->input) अणु
		/*
		 * The transport driver alपढ़ोy has an input device.
		 * In some हालs it is preferable to reuse the transport
		 * devices input device instead of creating a new one here.
		 * One example is some HID touchpads report "pass-through"
		 * button events are not reported by rmi रेजिस्टरs.
		 */
		data->input = rmi_dev->xport->input;
	पूर्ण अन्यथा अणु
		data->input = devm_input_allocate_device(dev);
		अगर (!data->input) अणु
			dev_err(dev, "%s: Failed to allocate input device.\n",
				__func__);
			retval = -ENOMEM;
			जाओ err;
		पूर्ण
		rmi_driver_set_input_params(rmi_dev, data->input);
		data->input->phys = devm_kaप्र_लिखो(dev, GFP_KERNEL,
						"%s/input0", dev_name(dev));
	पूर्ण

	retval = rmi_init_functions(data);
	अगर (retval)
		जाओ err;

	retval = rmi_f34_create_sysfs(rmi_dev);
	अगर (retval)
		जाओ err;

	अगर (data->input) अणु
		rmi_driver_set_input_name(rmi_dev, data->input);
		अगर (!rmi_dev->xport->input) अणु
			retval = input_रेजिस्टर_device(data->input);
			अगर (retval) अणु
				dev_err(dev, "%s: Failed to register input device.\n",
					__func__);
				जाओ err_destroy_functions;
			पूर्ण
		पूर्ण
	पूर्ण

	retval = rmi_irq_init(rmi_dev);
	अगर (retval < 0)
		जाओ err_destroy_functions;

	अगर (data->f01_container->dev.driver) अणु
		/* Driver alपढ़ोy bound, so enable ATTN now. */
		retval = rmi_enable_sensor(rmi_dev);
		अगर (retval)
			जाओ err_disable_irq;
	पूर्ण

	वापस 0;

err_disable_irq:
	rmi_disable_irq(rmi_dev, false);
err_destroy_functions:
	rmi_मुक्त_function_list(rmi_dev);
err:
	वापस retval;
पूर्ण

अटल काष्ठा rmi_driver rmi_physical_driver = अणु
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= "rmi4_physical",
		.bus	= &rmi_bus_type,
		.probe = rmi_driver_probe,
		.हटाओ = rmi_driver_हटाओ,
	पूर्ण,
	.reset_handler = rmi_driver_reset_handler,
	.clear_irq_bits = rmi_driver_clear_irq_bits,
	.set_irq_bits = rmi_driver_set_irq_bits,
	.set_input_params = rmi_driver_set_input_params,
पूर्ण;

bool rmi_is_physical_driver(काष्ठा device_driver *drv)
अणु
	वापस drv == &rmi_physical_driver.driver;
पूर्ण

पूर्णांक __init rmi_रेजिस्टर_physical_driver(व्योम)
अणु
	पूर्णांक error;

	error = driver_रेजिस्टर(&rmi_physical_driver.driver);
	अगर (error) अणु
		pr_err("%s: driver register failed, code=%d.\n", __func__,
		       error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

व्योम __निकास rmi_unरेजिस्टर_physical_driver(व्योम)
अणु
	driver_unरेजिस्टर(&rmi_physical_driver.driver);
पूर्ण
