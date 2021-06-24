<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/spi/spi-test.h
 *
 *  (c) Martin Sperl <kernel@martin.sperl.org>
 *
 *  spi_test definitions
 */

#समावेश <linux/spi/spi.h>

#घोषणा SPI_TEST_MAX_TRANSFERS 4
#घोषणा SPI_TEST_MAX_SIZE (32 * PAGE_SIZE)
#घोषणा SPI_TEST_MAX_ITERATE 32

/* the "dummy" start addresses used in spi_test
 * these addresses get translated at a later stage
 */
#घोषणा RX_START	BIT(30)
#घोषणा TX_START	BIT(31)
#घोषणा RX(off)		((व्योम *)(RX_START + off))
#घोषणा TX(off)		((व्योम *)(TX_START + off))

/* some special defines क्रम offsets */
#घोषणा SPI_TEST_MAX_SIZE_HALF	BIT(29)

/* detection pattern क्रम unfinished पढ़ोs...
 * - 0x00 or 0xff could be valid levels क्रम tx_buf = शून्य,
 * so we करो not use either of them
 */
#घोषणा SPI_TEST_PATTERN_UNWRITTEN 0xAA
#घोषणा SPI_TEST_PATTERN_DO_NOT_WRITE 0x55
#घोषणा SPI_TEST_CHECK_DO_NOT_WRITE 64

/**
 * काष्ठा spi_test - describes a specअगरic (set of) tests to execute
 *
 * @description:      description of the test
 *
 * @msg:              a ढाँचा @spi_message usedक्रम the शेष settings
 * @transfers:        array of @spi_transfers that are part of the
 *                    resulting spi_message.
 * @transfer_count:   number of transfers
 *
 * @run_test:         run a specअगरic spi_test - this allows to override
 *                    the शेष implementation of @spi_test_run_transfer
 *                    either to add some custom filters क्रम a specअगरic test
 *                    or to effectively run some very custom tests...
 * @execute_msg:      run the spi_message क्रम real - this allows to override
 *                    @spi_test_execute_msg to apply final modअगरications
 *                    on the spi_message
 * @expected_वापस:  the expected वापस code - in some हालs we want to
 *                    test also क्रम error conditions
 *
 * @iterate_len:      list of length to iterate on
 * @iterate_tx_align: change the alignment of @spi_transfer.tx_buf
 *                    क्रम all values in the below range अगर set.
 *                    the ranges are:
 *                    [0 : @spi_master.dma_alignment[ अगर set
 *                    [0 : iterate_tx_align[ अगर unset
 * @iterate_rx_align: change the alignment of @spi_transfer.rx_buf
 *                    see @iterate_tx_align क्रम details
 * @iterate_transfer_mask: the biपंचांगask of transfers to which the iterations
 *                         apply - अगर 0, then it applies to all transfer
 *
 * @fill_option:      define the way how tx_buf is filled
 * @fill_pattern:     fill pattern to apply to the tx_buf
 *                    (used in some of the @fill_options)
 * @elapsed_समय:     elapsed समय in nanoseconds
 */

काष्ठा spi_test अणु
	अक्षर description[64];
	काष्ठा spi_message msg;
	काष्ठा spi_transfer transfers[SPI_TEST_MAX_TRANSFERS];
	अचिन्हित पूर्णांक transfer_count;
	पूर्णांक (*run_test)(काष्ठा spi_device *spi, काष्ठा spi_test *test,
			व्योम *tx, व्योम *rx);
	पूर्णांक (*execute_msg)(काष्ठा spi_device *spi, काष्ठा spi_test *test,
			   व्योम *tx, व्योम *rx);
	पूर्णांक expected_वापस;
	/* iterate over all values, terminated by a -1 */
	पूर्णांक iterate_len[SPI_TEST_MAX_ITERATE];
	पूर्णांक iterate_tx_align;
	पूर्णांक iterate_rx_align;
	u32 iterate_transfer_mask;
	/* the tx-fill operation */
	u32 fill_option;
#घोषणा FILL_MEMSET_8	0	/* just स_रखो with 8 bit */
#घोषणा FILL_MEMSET_16	1	/* just स_रखो with 16 bit */
#घोषणा FILL_MEMSET_24	2	/* just स_रखो with 24 bit */
#घोषणा FILL_MEMSET_32	3	/* just स_रखो with 32 bit */
#घोषणा FILL_COUNT_8	4	/* fill with a 8 byte counter */
#घोषणा FILL_COUNT_16	5	/* fill with a 16 bit counter */
#घोषणा FILL_COUNT_24	6	/* fill with a 24 bit counter */
#घोषणा FILL_COUNT_32	7	/* fill with a 32 bit counter */
#घोषणा FILL_TRANSFER_BYTE_8  8	/* fill with the transfer byte - 8 bit */
#घोषणा FILL_TRANSFER_BYTE_16 9	/* fill with the transfer byte - 16 bit */
#घोषणा FILL_TRANSFER_BYTE_24 10 /* fill with the transfer byte - 24 bit */
#घोषणा FILL_TRANSFER_BYTE_32 11 /* fill with the transfer byte - 32 bit */
#घोषणा FILL_TRANSFER_NUM     16 /* fill with the transfer number */
	u32 fill_pattern;
	अचिन्हित दीर्घ दीर्घ elapsed_समय;
पूर्ण;

/* शेष implementation क्रम @spi_test.run_test */
पूर्णांक spi_test_run_test(काष्ठा spi_device *spi,
		      स्थिर काष्ठा spi_test *test,
		      व्योम *tx, व्योम *rx);

/* शेष implementation क्रम @spi_test.execute_msg */
पूर्णांक spi_test_execute_msg(काष्ठा spi_device *spi,
			 काष्ठा spi_test *test,
			 व्योम *tx, व्योम *rx);

/* function to execute a set of tests */
पूर्णांक spi_test_run_tests(काष्ठा spi_device *spi,
		       काष्ठा spi_test *tests);

#घोषणा ITERATE_LEN_LIST 0, 1, 2, 3, 7, 11, 16, 31, 32, 64, 97, 128, 251, 256, \
		1021, 1024, 1031, 4093, PAGE_SIZE, 4099, 65536, 65537
/* some of the शेष @spi_transfer.len to test, terminated by a -1 */
#घोषणा ITERATE_LEN ITERATE_LEN_LIST, -1
#घोषणा ITERATE_MAX_LEN ITERATE_LEN_LIST, (SPI_TEST_MAX_SIZE - 1), \
		SPI_TEST_MAX_SIZE, -1

/* the शेष alignment to test */
#घोषणा ITERATE_ALIGN माप(पूर्णांक)
