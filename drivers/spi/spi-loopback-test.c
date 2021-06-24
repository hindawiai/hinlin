<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/spi/spi-loopback-test.c
 *
 *  (c) Martin Sperl <kernel@martin.sperl.org>
 *
 *  Loopback test driver to test several typical spi_message conditions
 *  that a spi_master driver may encounter
 *  this can also get used क्रम regression testing
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/spi/spi.h>

#समावेश "spi-test.h"

/* flag to only simulate transfers */
अटल पूर्णांक simulate_only;
module_param(simulate_only, पूर्णांक, 0);
MODULE_PARM_DESC(simulate_only, "if not 0 do not execute the spi message");

/* dump spi messages */
अटल पूर्णांक dump_messages;
module_param(dump_messages, पूर्णांक, 0);
MODULE_PARM_DESC(dump_messages,
		 "=1 dump the basic spi_message_structure, " \
		 "=2 dump the spi_message_structure including data, " \
		 "=3 dump the spi_message structure before and after execution");
/* the device is jumpered क्रम loopback - enabling some rx_buf tests */
अटल पूर्णांक loopback;
module_param(loopback, पूर्णांक, 0);
MODULE_PARM_DESC(loopback,
		 "if set enable loopback mode, where the rx_buf "	\
		 "is checked to match tx_buf after the spi_message "	\
		 "is executed");

अटल पूर्णांक loop_req;
module_param(loop_req, पूर्णांक, 0);
MODULE_PARM_DESC(loop_req,
		 "if set controller will be asked to enable test loop mode. " \
		 "If controller supported it, MISO and MOSI will be connected");

अटल पूर्णांक no_cs;
module_param(no_cs, पूर्णांक, 0);
MODULE_PARM_DESC(no_cs,
		 "if set Chip Select (CS) will not be used");

/* run only a specअगरic test */
अटल पूर्णांक run_only_test = -1;
module_param(run_only_test, पूर्णांक, 0);
MODULE_PARM_DESC(run_only_test,
		 "only run the test with this number (0-based !)");

/* use vदो_स्मृति'ed buffers */
अटल पूर्णांक use_vदो_स्मृति;
module_param(use_vदो_स्मृति, पूर्णांक, 0644);
MODULE_PARM_DESC(use_vदो_स्मृति,
		 "use vmalloc'ed buffers instead of kmalloc'ed");

/* check rx ranges */
अटल पूर्णांक check_ranges = 1;
module_param(check_ranges, पूर्णांक, 0644);
MODULE_PARM_DESC(check_ranges,
		 "checks rx_buffer pattern are valid");

/* the actual tests to execute */
अटल काष्ठा spi_test spi_tests[] = अणु
	अणु
		.description	= "tx/rx-transfer - start of page",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_MAX_LEN पूर्ण,
		.iterate_tx_align = ITERATE_ALIGN,
		.iterate_rx_align = ITERATE_ALIGN,
		.transfer_count = 1,
		.transfers		= अणु
			अणु
				.tx_buf = TX(0),
				.rx_buf = RX(0),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "tx/rx-transfer - crossing PAGE_SIZE",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_LEN पूर्ण,
		.iterate_tx_align = ITERATE_ALIGN,
		.iterate_rx_align = ITERATE_ALIGN,
		.transfer_count = 1,
		.transfers		= अणु
			अणु
				.tx_buf = TX(PAGE_SIZE - 4),
				.rx_buf = RX(PAGE_SIZE - 4),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "tx-transfer - only",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_MAX_LEN पूर्ण,
		.iterate_tx_align = ITERATE_ALIGN,
		.transfer_count = 1,
		.transfers		= अणु
			अणु
				.tx_buf = TX(0),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "rx-transfer - only",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_MAX_LEN पूर्ण,
		.iterate_rx_align = ITERATE_ALIGN,
		.transfer_count = 1,
		.transfers		= अणु
			अणु
				.rx_buf = RX(0),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "two tx-transfers - alter both",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_LEN पूर्ण,
		.iterate_tx_align = ITERATE_ALIGN,
		.iterate_transfer_mask = BIT(0) | BIT(1),
		.transfer_count = 2,
		.transfers		= अणु
			अणु
				.tx_buf = TX(0),
			पूर्ण,
			अणु
				/* this is why we cant use ITERATE_MAX_LEN */
				.tx_buf = TX(SPI_TEST_MAX_SIZE_HALF),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "two tx-transfers - alter first",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_MAX_LEN पूर्ण,
		.iterate_tx_align = ITERATE_ALIGN,
		.iterate_transfer_mask = BIT(0),
		.transfer_count = 2,
		.transfers		= अणु
			अणु
				.tx_buf = TX(64),
			पूर्ण,
			अणु
				.len = 1,
				.tx_buf = TX(0),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "two tx-transfers - alter second",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_MAX_LEN पूर्ण,
		.iterate_tx_align = ITERATE_ALIGN,
		.iterate_transfer_mask = BIT(1),
		.transfer_count = 2,
		.transfers		= अणु
			अणु
				.len = 16,
				.tx_buf = TX(0),
			पूर्ण,
			अणु
				.tx_buf = TX(64),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "two transfers tx then rx - alter both",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_MAX_LEN पूर्ण,
		.iterate_tx_align = ITERATE_ALIGN,
		.iterate_transfer_mask = BIT(0) | BIT(1),
		.transfer_count = 2,
		.transfers		= अणु
			अणु
				.tx_buf = TX(0),
			पूर्ण,
			अणु
				.rx_buf = RX(0),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "two transfers tx then rx - alter tx",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_MAX_LEN पूर्ण,
		.iterate_tx_align = ITERATE_ALIGN,
		.iterate_transfer_mask = BIT(0),
		.transfer_count = 2,
		.transfers		= अणु
			अणु
				.tx_buf = TX(0),
			पूर्ण,
			अणु
				.len = 1,
				.rx_buf = RX(0),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "two transfers tx then rx - alter rx",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_MAX_LEN पूर्ण,
		.iterate_tx_align = ITERATE_ALIGN,
		.iterate_transfer_mask = BIT(1),
		.transfer_count = 2,
		.transfers		= अणु
			अणु
				.len = 1,
				.tx_buf = TX(0),
			पूर्ण,
			अणु
				.rx_buf = RX(0),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "two tx+rx transfers - alter both",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_LEN पूर्ण,
		.iterate_tx_align = ITERATE_ALIGN,
		.iterate_transfer_mask = BIT(0) | BIT(1),
		.transfer_count = 2,
		.transfers		= अणु
			अणु
				.tx_buf = TX(0),
				.rx_buf = RX(0),
			पूर्ण,
			अणु
				/* making sure we align without overग_लिखो
				 * the reason we can not use ITERATE_MAX_LEN
				 */
				.tx_buf = TX(SPI_TEST_MAX_SIZE_HALF),
				.rx_buf = RX(SPI_TEST_MAX_SIZE_HALF),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "two tx+rx transfers - alter first",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_MAX_LEN पूर्ण,
		.iterate_tx_align = ITERATE_ALIGN,
		.iterate_transfer_mask = BIT(0),
		.transfer_count = 2,
		.transfers		= अणु
			अणु
				/* making sure we align without overग_लिखो */
				.tx_buf = TX(1024),
				.rx_buf = RX(1024),
			पूर्ण,
			अणु
				.len = 1,
				/* making sure we align without overग_लिखो */
				.tx_buf = TX(0),
				.rx_buf = RX(0),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "two tx+rx transfers - alter second",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_MAX_LEN पूर्ण,
		.iterate_tx_align = ITERATE_ALIGN,
		.iterate_transfer_mask = BIT(1),
		.transfer_count = 2,
		.transfers		= अणु
			अणु
				.len = 1,
				.tx_buf = TX(0),
				.rx_buf = RX(0),
			पूर्ण,
			अणु
				/* making sure we align without overग_लिखो */
				.tx_buf = TX(1024),
				.rx_buf = RX(1024),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.description	= "two tx+rx transfers - delay after transfer",
		.fill_option	= FILL_COUNT_8,
		.iterate_len    = अणु ITERATE_MAX_LEN पूर्ण,
		.iterate_transfer_mask = BIT(0) | BIT(1),
		.transfer_count = 2,
		.transfers		= अणु
			अणु
				.tx_buf = TX(0),
				.rx_buf = RX(0),
				.delay = अणु
					.value = 1000,
					.unit = SPI_DELAY_UNIT_USECS,
				पूर्ण,
			पूर्ण,
			अणु
				.tx_buf = TX(0),
				.rx_buf = RX(0),
				.delay = अणु
					.value = 1000,
					.unit = SPI_DELAY_UNIT_USECS,
				पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,

	अणु /* end of tests sequence */ पूर्ण
पूर्ण;

अटल पूर्णांक spi_loopback_test_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;

	अगर (loop_req || no_cs) अणु
		spi->mode |= loop_req ? SPI_LOOP : 0;
		spi->mode |= no_cs ? SPI_NO_CS : 0;
		ret = spi_setup(spi);
		अगर (ret) अणु
			dev_err(&spi->dev, "SPI setup with SPI_LOOP or SPI_NO_CS failed (%d)\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	dev_info(&spi->dev, "Executing spi-loopback-tests\n");

	ret = spi_test_run_tests(spi, spi_tests);

	dev_info(&spi->dev, "Finished spi-loopback-tests with return: %i\n",
		 ret);

	वापस ret;
पूर्ण

/* non स्थिर match table to permit to change via a module parameter */
अटल काष्ठा of_device_id spi_loopback_test_of_match[] = अणु
	अणु .compatible	= "linux,spi-loopback-test", पूर्ण,
	अणु पूर्ण
पूर्ण;

/* allow to override the compatible string via a module_parameter */
module_param_string(compatible, spi_loopback_test_of_match[0].compatible,
		    माप(spi_loopback_test_of_match[0].compatible),
		    0000);

MODULE_DEVICE_TABLE(of, spi_loopback_test_of_match);

अटल काष्ठा spi_driver spi_loopback_test_driver = अणु
	.driver = अणु
		.name = "spi-loopback-test",
		.owner = THIS_MODULE,
		.of_match_table = spi_loopback_test_of_match,
	पूर्ण,
	.probe = spi_loopback_test_probe,
पूर्ण;

module_spi_driver(spi_loopback_test_driver);

MODULE_AUTHOR("Martin Sperl <kernel@martin.sperl.org>");
MODULE_DESCRIPTION("test spi_driver to check core functionality");
MODULE_LICENSE("GPL");

/*-------------------------------------------------------------------------*/

/* spi_test implementation */

#घोषणा RANGE_CHECK(ptr, plen, start, slen) \
	((ptr >= start) && (ptr + plen <= start + slen))

/* we allocate one page more, to allow क्रम offsets */
#घोषणा SPI_TEST_MAX_SIZE_PLUS (SPI_TEST_MAX_SIZE + PAGE_SIZE)

अटल व्योम spi_test_prपूर्णांक_hex_dump(अक्षर *pre, स्थिर व्योम *ptr, माप_प्रकार len)
अणु
	/* limit the hex_dump */
	अगर (len < 1024) अणु
		prपूर्णांक_hex_dump(KERN_INFO, pre,
			       DUMP_PREFIX_OFFSET, 16, 1,
			       ptr, len, 0);
		वापस;
	पूर्ण
	/* prपूर्णांक head */
	prपूर्णांक_hex_dump(KERN_INFO, pre,
		       DUMP_PREFIX_OFFSET, 16, 1,
		       ptr, 512, 0);
	/* prपूर्णांक tail */
	pr_info("%s truncated - continuing at offset %04zx\n",
		pre, len - 512);
	prपूर्णांक_hex_dump(KERN_INFO, pre,
		       DUMP_PREFIX_OFFSET, 16, 1,
		       ptr + (len - 512), 512, 0);
पूर्ण

अटल व्योम spi_test_dump_message(काष्ठा spi_device *spi,
				  काष्ठा spi_message *msg,
				  bool dump_data)
अणु
	काष्ठा spi_transfer *xfer;
	पूर्णांक i;
	u8 b;

	dev_info(&spi->dev, "  spi_msg@%pK\n", msg);
	अगर (msg->status)
		dev_info(&spi->dev, "    status:        %i\n",
			 msg->status);
	dev_info(&spi->dev, "    frame_length:  %i\n",
		 msg->frame_length);
	dev_info(&spi->dev, "    actual_length: %i\n",
		 msg->actual_length);

	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		dev_info(&spi->dev, "    spi_transfer@%pK\n", xfer);
		dev_info(&spi->dev, "      len:    %i\n", xfer->len);
		dev_info(&spi->dev, "      tx_buf: %pK\n", xfer->tx_buf);
		अगर (dump_data && xfer->tx_buf)
			spi_test_prपूर्णांक_hex_dump("          TX: ",
						xfer->tx_buf,
						xfer->len);

		dev_info(&spi->dev, "      rx_buf: %pK\n", xfer->rx_buf);
		अगर (dump_data && xfer->rx_buf)
			spi_test_prपूर्णांक_hex_dump("          RX: ",
						xfer->rx_buf,
						xfer->len);
		/* check क्रम unwritten test pattern on rx_buf */
		अगर (xfer->rx_buf) अणु
			क्रम (i = 0 ; i < xfer->len ; i++) अणु
				b = ((u8 *)xfer->rx_buf)[xfer->len - 1 - i];
				अगर (b != SPI_TEST_PATTERN_UNWRITTEN)
					अवरोध;
			पूर्ण
			अगर (i)
				dev_info(&spi->dev,
					 "      rx_buf filled with %02x starts at offset: %i\n",
					 SPI_TEST_PATTERN_UNWRITTEN,
					 xfer->len - i);
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा rx_ranges अणु
	काष्ठा list_head list;
	u8 *start;
	u8 *end;
पूर्ण;

अटल पूर्णांक rx_ranges_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
			 स्थिर काष्ठा list_head *b)
अणु
	काष्ठा rx_ranges *rx_a = list_entry(a, काष्ठा rx_ranges, list);
	काष्ठा rx_ranges *rx_b = list_entry(b, काष्ठा rx_ranges, list);

	अगर (rx_a->start > rx_b->start)
		वापस 1;
	अगर (rx_a->start < rx_b->start)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक spi_check_rx_ranges(काष्ठा spi_device *spi,
			       काष्ठा spi_message *msg,
			       व्योम *rx)
अणु
	काष्ठा spi_transfer *xfer;
	काष्ठा rx_ranges ranges[SPI_TEST_MAX_TRANSFERS], *r;
	पूर्णांक i = 0;
	LIST_HEAD(ranges_list);
	u8 *addr;
	पूर्णांक ret = 0;

	/* loop over all transfers to fill in the rx_ranges */
	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		/* अगर there is no rx, then no check is needed */
		अगर (!xfer->rx_buf)
			जारी;
		/* fill in the rx_range */
		अगर (RANGE_CHECK(xfer->rx_buf, xfer->len,
				rx, SPI_TEST_MAX_SIZE_PLUS)) अणु
			ranges[i].start = xfer->rx_buf;
			ranges[i].end = xfer->rx_buf + xfer->len;
			list_add(&ranges[i].list, &ranges_list);
			i++;
		पूर्ण
	पूर्ण

	/* अगर no ranges, then we can वापस and aव्योम the checks...*/
	अगर (!i)
		वापस 0;

	/* sort the list */
	list_sort(शून्य, &ranges_list, rx_ranges_cmp);

	/* and iterate over all the rx addresses */
	क्रम (addr = rx; addr < (u8 *)rx + SPI_TEST_MAX_SIZE_PLUS; addr++) अणु
		/* अगर we are the DO not ग_लिखो pattern,
		 * then जारी with the loop...
		 */
		अगर (*addr == SPI_TEST_PATTERN_DO_NOT_WRITE)
			जारी;

		/* check अगर we are inside a range */
		list_क्रम_each_entry(r, &ranges_list, list) अणु
			/* अगर so then set to end... */
			अगर ((addr >= r->start) && (addr < r->end))
				addr = r->end;
		पूर्ण
		/* second test after a (hopefull) translation */
		अगर (*addr == SPI_TEST_PATTERN_DO_NOT_WRITE)
			जारी;

		/* अगर still not found then something has modअगरied too much */
		/* we could list the "closest" transfer here... */
		dev_err(&spi->dev,
			"loopback strangeness - rx changed outside of allowed range at: %pK\n",
			addr);
		/* करो not वापस, only set ret,
		 * so that we list all addresses
		 */
		ret = -दुस्फल;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक spi_test_check_elapsed_समय(काष्ठा spi_device *spi,
				       काष्ठा spi_test *test)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ दीर्घ estimated_समय = 0;
	अचिन्हित दीर्घ दीर्घ delay_usecs = 0;

	क्रम (i = 0; i < test->transfer_count; i++) अणु
		काष्ठा spi_transfer *xfer = test->transfers + i;
		अचिन्हित दीर्घ दीर्घ nbits = (अचिन्हित दीर्घ दीर्घ)BITS_PER_BYTE *
					   xfer->len;

		delay_usecs += xfer->delay.value;
		अगर (!xfer->speed_hz)
			जारी;
		estimated_समय += भाग_u64(nbits * NSEC_PER_SEC, xfer->speed_hz);
	पूर्ण

	estimated_समय += delay_usecs * NSEC_PER_USEC;
	अगर (test->elapsed_समय < estimated_समय) अणु
		dev_err(&spi->dev,
			"elapsed time %lld ns is shorter than minimum estimated time %lld ns\n",
			test->elapsed_समय, estimated_समय);

		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spi_test_check_loopback_result(काष्ठा spi_device *spi,
					  काष्ठा spi_message *msg,
					  व्योम *tx, व्योम *rx)
अणु
	काष्ठा spi_transfer *xfer;
	u8 rxb, txb;
	माप_प्रकार i;
	पूर्णांक ret;

	/* checks rx_buffer pattern are valid with loopback or without */
	अगर (check_ranges) अणु
		ret = spi_check_rx_ranges(spi, msg, rx);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* अगर we run without loopback, then वापस now */
	अगर (!loopback)
		वापस 0;

	/* अगर applicable to transfer check that rx_buf is equal to tx_buf */
	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		/* अगर there is no rx, then no check is needed */
		अगर (!xfer->len || !xfer->rx_buf)
			जारी;
		/* so depending on tx_buf we need to handle things */
		अगर (xfer->tx_buf) अणु
			क्रम (i = 0; i < xfer->len; i++) अणु
				txb = ((u8 *)xfer->tx_buf)[i];
				rxb = ((u8 *)xfer->rx_buf)[i];
				अगर (txb != rxb)
					जाओ mismatch_error;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* first byte received */
			txb = ((u8 *)xfer->rx_buf)[0];
			/* first byte may be 0 or xff */
			अगर (!((txb == 0) || (txb == 0xff))) अणु
				dev_err(&spi->dev,
					"loopback strangeness - we expect 0x00 or 0xff, but not 0x%02x\n",
					txb);
				वापस -EINVAL;
			पूर्ण
			/* check that all bytes are identical */
			क्रम (i = 1; i < xfer->len; i++) अणु
				rxb = ((u8 *)xfer->rx_buf)[i];
				अगर (rxb != txb)
					जाओ mismatch_error;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

mismatch_error:
	dev_err(&spi->dev,
		"loopback strangeness - transfer mismatch on byte %04zx - expected 0x%02x, but got 0x%02x\n",
		i, txb, rxb);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक spi_test_translate(काष्ठा spi_device *spi,
			      व्योम **ptr, माप_प्रकार len,
			      व्योम *tx, व्योम *rx)
अणु
	माप_प्रकार off;

	/* वापस on null */
	अगर (!*ptr)
		वापस 0;

	/* in the MAX_SIZE_HALF हाल modअगरy the poपूर्णांकer */
	अगर (((माप_प्रकार)*ptr) & SPI_TEST_MAX_SIZE_HALF)
		/* move the poपूर्णांकer to the correct range */
		*ptr += (SPI_TEST_MAX_SIZE_PLUS / 2) -
			SPI_TEST_MAX_SIZE_HALF;

	/* RX range
	 * - we check against MAX_SIZE_PLUS to allow क्रम स्वतःmated alignment
	 */
	अगर (RANGE_CHECK(*ptr, len,  RX(0), SPI_TEST_MAX_SIZE_PLUS)) अणु
		off = *ptr - RX(0);
		*ptr = rx + off;

		वापस 0;
	पूर्ण

	/* TX range */
	अगर (RANGE_CHECK(*ptr, len,  TX(0), SPI_TEST_MAX_SIZE_PLUS)) अणु
		off = *ptr - TX(0);
		*ptr = tx + off;

		वापस 0;
	पूर्ण

	dev_err(&spi->dev,
		"PointerRange [%pK:%pK[ not in range [%pK:%pK[ or [%pK:%pK[\n",
		*ptr, *ptr + len,
		RX(0), RX(SPI_TEST_MAX_SIZE),
		TX(0), TX(SPI_TEST_MAX_SIZE));

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक spi_test_fill_pattern(काष्ठा spi_device *spi,
				 काष्ठा spi_test *test)
अणु
	काष्ठा spi_transfer *xfers = test->transfers;
	u8 *tx_buf;
	माप_प्रकार count = 0;
	पूर्णांक i, j;

#अगर_घोषित __BIG_ENDIAN
#घोषणा GET_VALUE_BYTE(value, index, bytes) \
	(value >> (8 * (bytes - 1 - count % bytes)))
#अन्यथा
#घोषणा GET_VALUE_BYTE(value, index, bytes) \
	(value >> (8 * (count % bytes)))
#पूर्ण_अगर

	/* fill all transfers with the pattern requested */
	क्रम (i = 0; i < test->transfer_count; i++) अणु
		/* fill rx_buf with SPI_TEST_PATTERN_UNWRITTEN */
		अगर (xfers[i].rx_buf)
			स_रखो(xfers[i].rx_buf, SPI_TEST_PATTERN_UNWRITTEN,
			       xfers[i].len);
		/* अगर tx_buf is शून्य then skip */
		tx_buf = (u8 *)xfers[i].tx_buf;
		अगर (!tx_buf)
			जारी;
		/* modअगरy all the transfers */
		क्रम (j = 0; j < xfers[i].len; j++, tx_buf++, count++) अणु
			/* fill tx */
			चयन (test->fill_option) अणु
			हाल FILL_MEMSET_8:
				*tx_buf = test->fill_pattern;
				अवरोध;
			हाल FILL_MEMSET_16:
				*tx_buf = GET_VALUE_BYTE(test->fill_pattern,
							 count, 2);
				अवरोध;
			हाल FILL_MEMSET_24:
				*tx_buf = GET_VALUE_BYTE(test->fill_pattern,
							 count, 3);
				अवरोध;
			हाल FILL_MEMSET_32:
				*tx_buf = GET_VALUE_BYTE(test->fill_pattern,
							 count, 4);
				अवरोध;
			हाल FILL_COUNT_8:
				*tx_buf = count;
				अवरोध;
			हाल FILL_COUNT_16:
				*tx_buf = GET_VALUE_BYTE(count, count, 2);
				अवरोध;
			हाल FILL_COUNT_24:
				*tx_buf = GET_VALUE_BYTE(count, count, 3);
				अवरोध;
			हाल FILL_COUNT_32:
				*tx_buf = GET_VALUE_BYTE(count, count, 4);
				अवरोध;
			हाल FILL_TRANSFER_BYTE_8:
				*tx_buf = j;
				अवरोध;
			हाल FILL_TRANSFER_BYTE_16:
				*tx_buf = GET_VALUE_BYTE(j, j, 2);
				अवरोध;
			हाल FILL_TRANSFER_BYTE_24:
				*tx_buf = GET_VALUE_BYTE(j, j, 3);
				अवरोध;
			हाल FILL_TRANSFER_BYTE_32:
				*tx_buf = GET_VALUE_BYTE(j, j, 4);
				अवरोध;
			हाल FILL_TRANSFER_NUM:
				*tx_buf = i;
				अवरोध;
			शेष:
				dev_err(&spi->dev,
					"unsupported fill_option: %i\n",
					test->fill_option);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _spi_test_run_iter(काष्ठा spi_device *spi,
			      काष्ठा spi_test *test,
			      व्योम *tx, व्योम *rx)
अणु
	काष्ठा spi_message *msg = &test->msg;
	काष्ठा spi_transfer *x;
	पूर्णांक i, ret;

	/* initialize message - zero-filled via अटल initialization */
	spi_message_init_no_स_रखो(msg);

	/* fill rx with the DO_NOT_WRITE pattern */
	स_रखो(rx, SPI_TEST_PATTERN_DO_NOT_WRITE, SPI_TEST_MAX_SIZE_PLUS);

	/* add the inभागidual transfers */
	क्रम (i = 0; i < test->transfer_count; i++) अणु
		x = &test->transfers[i];

		/* patch the values of tx_buf */
		ret = spi_test_translate(spi, (व्योम **)&x->tx_buf, x->len,
					 (व्योम *)tx, rx);
		अगर (ret)
			वापस ret;

		/* patch the values of rx_buf */
		ret = spi_test_translate(spi, &x->rx_buf, x->len,
					 (व्योम *)tx, rx);
		अगर (ret)
			वापस ret;

		/* and add it to the list */
		spi_message_add_tail(x, msg);
	पूर्ण

	/* fill in the transfer buffers with pattern */
	ret = spi_test_fill_pattern(spi, test);
	अगर (ret)
		वापस ret;

	/* and execute */
	अगर (test->execute_msg)
		ret = test->execute_msg(spi, test, tx, rx);
	अन्यथा
		ret = spi_test_execute_msg(spi, test, tx, rx);

	/* handle result */
	अगर (ret == test->expected_वापस)
		वापस 0;

	dev_err(&spi->dev,
		"test failed - test returned %i, but we expect %i\n",
		ret, test->expected_वापस);

	अगर (ret)
		वापस ret;

	/* अगर it is 0, as we expected something अन्यथा,
	 * then वापस something special
	 */
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक spi_test_run_iter(काष्ठा spi_device *spi,
			     स्थिर काष्ठा spi_test *testढाँचा,
			     व्योम *tx, व्योम *rx,
			     माप_प्रकार len,
			     माप_प्रकार tx_off,
			     माप_प्रकार rx_off
	)
अणु
	काष्ठा spi_test test;
	पूर्णांक i, tx_count, rx_count;

	/* copy the test ढाँचा to test */
	स_नकल(&test, testढाँचा, माप(test));

	/* अगर iterate_transfer_mask is not set,
	 * then set it to first transfer only
	 */
	अगर (!(test.iterate_transfer_mask & (BIT(test.transfer_count) - 1)))
		test.iterate_transfer_mask = 1;

	/* count number of transfers with tx/rx_buf != शून्य */
	rx_count = tx_count = 0;
	क्रम (i = 0; i < test.transfer_count; i++) अणु
		अगर (test.transfers[i].tx_buf)
			tx_count++;
		अगर (test.transfers[i].rx_buf)
			rx_count++;
	पूर्ण

	/* in some iteration हालs warn and निकास early,
	 * as there is nothing to करो, that has not been tested alपढ़ोy...
	 */
	अगर (tx_off && (!tx_count)) अणु
		dev_warn_once(&spi->dev,
			      "%s: iterate_tx_off configured with tx_buf==NULL - ignoring\n",
			      test.description);
		वापस 0;
	पूर्ण
	अगर (rx_off && (!rx_count)) अणु
		dev_warn_once(&spi->dev,
			      "%s: iterate_rx_off configured with rx_buf==NULL - ignoring\n",
			      test.description);
		वापस 0;
	पूर्ण

	/* ग_लिखो out info */
	अगर (!(len || tx_off || rx_off)) अणु
		dev_info(&spi->dev, "Running test %s\n", test.description);
	पूर्ण अन्यथा अणु
		dev_info(&spi->dev,
			 "  with iteration values: len = %zu, tx_off = %zu, rx_off = %zu\n",
			 len, tx_off, rx_off);
	पूर्ण

	/* update in the values from iteration values */
	क्रम (i = 0; i < test.transfer_count; i++) अणु
		/* only when bit in transfer mask is set */
		अगर (!(test.iterate_transfer_mask & BIT(i)))
			जारी;
		test.transfers[i].len = len;
		अगर (test.transfers[i].tx_buf)
			test.transfers[i].tx_buf += tx_off;
		अगर (test.transfers[i].tx_buf)
			test.transfers[i].rx_buf += rx_off;
	पूर्ण

	/* and execute */
	वापस _spi_test_run_iter(spi, &test, tx, rx);
पूर्ण

/**
 * spi_test_execute_msg - शेष implementation to run a test
 *
 * @spi: @spi_device on which to run the @spi_message
 * @test: the test to execute, which alपढ़ोy contains @msg
 * @tx:   the tx buffer allocated क्रम the test sequence
 * @rx:   the rx buffer allocated क्रम the test sequence
 *
 * Returns: error code of spi_sync as well as basic error checking
 */
पूर्णांक spi_test_execute_msg(काष्ठा spi_device *spi, काष्ठा spi_test *test,
			 व्योम *tx, व्योम *rx)
अणु
	काष्ठा spi_message *msg = &test->msg;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* only अगर we करो not simulate */
	अगर (!simulate_only) अणु
		kसमय_प्रकार start;

		/* dump the complete message beक्रमe and after the transfer */
		अगर (dump_messages == 3)
			spi_test_dump_message(spi, msg, true);

		start = kसमय_get();
		/* run spi message */
		ret = spi_sync(spi, msg);
		test->elapsed_समय = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), start));
		अगर (ret == -ETIMEDOUT) अणु
			dev_info(&spi->dev,
				 "spi-message timed out - rerunning...\n");
			/* rerun after a few explicit schedules */
			क्रम (i = 0; i < 16; i++)
				schedule();
			ret = spi_sync(spi, msg);
		पूर्ण
		अगर (ret) अणु
			dev_err(&spi->dev,
				"Failed to execute spi_message: %i\n",
				ret);
			जाओ निकास;
		पूर्ण

		/* करो some extra error checks */
		अगर (msg->frame_length != msg->actual_length) अणु
			dev_err(&spi->dev,
				"actual length differs from expected\n");
			ret = -EIO;
			जाओ निकास;
		पूर्ण

		/* run rx-buffer tests */
		ret = spi_test_check_loopback_result(spi, msg, tx, rx);
		अगर (ret)
			जाओ निकास;

		ret = spi_test_check_elapsed_समय(spi, test);
	पूर्ण

	/* अगर requested or on error dump message (including data) */
निकास:
	अगर (dump_messages || ret)
		spi_test_dump_message(spi, msg,
				      (dump_messages >= 2) || (ret));

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(spi_test_execute_msg);

/**
 * spi_test_run_test - run an inभागidual spi_test
 *                     including all the relevant iterations on:
 *                     length and buffer alignment
 *
 * @spi:  the spi_device to send the messages to
 * @test: the test which we need to execute
 * @tx:   the tx buffer allocated क्रम the test sequence
 * @rx:   the rx buffer allocated क्रम the test sequence
 *
 * Returns: status code of spi_sync or other failures
 */

पूर्णांक spi_test_run_test(काष्ठा spi_device *spi, स्थिर काष्ठा spi_test *test,
		      व्योम *tx, व्योम *rx)
अणु
	पूर्णांक idx_len;
	माप_प्रकार len;
	माप_प्रकार tx_align, rx_align;
	पूर्णांक ret;

	/* test क्रम transfer limits */
	अगर (test->transfer_count >= SPI_TEST_MAX_TRANSFERS) अणु
		dev_err(&spi->dev,
			"%s: Exceeded max number of transfers with %i\n",
			test->description, test->transfer_count);
		वापस -E2BIG;
	पूर्ण

	/* setting up some values in spi_message
	 * based on some settings in spi_master
	 * some of this can also get करोne in the run() method
	 */

	/* iterate over all the iterable values using macros
	 * (to make it a bit more पढ़ोable...
	 */
#घोषणा FOR_EACH_ALIGNMENT(var)						\
	क्रम (var = 0;							\
	    var < (test->iterate_##var ?				\
			(spi->master->dma_alignment ?			\
			 spi->master->dma_alignment :			\
			 test->iterate_##var) :				\
			1);						\
	    var++)

	क्रम (idx_len = 0; idx_len < SPI_TEST_MAX_ITERATE &&
	     (len = test->iterate_len[idx_len]) != -1; idx_len++) अणु
		FOR_EACH_ALIGNMENT(tx_align) अणु
			FOR_EACH_ALIGNMENT(rx_align) अणु
				/* and run the iteration */
				ret = spi_test_run_iter(spi, test,
							tx, rx,
							len,
							tx_align,
							rx_align);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spi_test_run_test);

/**
 * spi_test_run_tests - run an array of spi_messages tests
 * @spi: the spi device on which to run the tests
 * @tests: शून्य-terminated array of @spi_test
 *
 * Returns: status errors as per @spi_test_run_test()
 */

पूर्णांक spi_test_run_tests(काष्ठा spi_device *spi,
		       काष्ठा spi_test *tests)
अणु
	अक्षर *rx = शून्य, *tx = शून्य;
	पूर्णांक ret = 0, count = 0;
	काष्ठा spi_test *test;

	/* allocate rx/tx buffers of 128kB size without devm
	 * in the hope that is on a page boundary
	 */
	अगर (use_vदो_स्मृति)
		rx = vदो_स्मृति(SPI_TEST_MAX_SIZE_PLUS);
	अन्यथा
		rx = kzalloc(SPI_TEST_MAX_SIZE_PLUS, GFP_KERNEL);
	अगर (!rx)
		वापस -ENOMEM;


	अगर (use_vदो_स्मृति)
		tx = vदो_स्मृति(SPI_TEST_MAX_SIZE_PLUS);
	अन्यथा
		tx = kzalloc(SPI_TEST_MAX_SIZE_PLUS, GFP_KERNEL);
	अगर (!tx) अणु
		ret = -ENOMEM;
		जाओ err_tx;
	पूर्ण

	/* now run the inभागidual tests in the table */
	क्रम (test = tests, count = 0; test->description[0];
	     test++, count++) अणु
		/* only run test अगर requested */
		अगर ((run_only_test > -1) && (count != run_only_test))
			जारी;
		/* run custom implementation */
		अगर (test->run_test)
			ret = test->run_test(spi, test, tx, rx);
		अन्यथा
			ret = spi_test_run_test(spi, test, tx, rx);
		अगर (ret)
			जाओ out;
		/* add some delays so that we can easily
		 * detect the inभागidual tests when using a logic analyzer
		 * we also add scheduling to aव्योम potential spi_समयouts...
		 */
		mdelay(100);
		schedule();
	पूर्ण

out:
	kvमुक्त(tx);
err_tx:
	kvमुक्त(rx);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(spi_test_run_tests);
