<शैली गुरु>
/*
 *   Copyright (c) 2011, 2012, Qualcomm Atheros Communications Inc.
 *   Copyright (c) 2014, I2SE GmbH
 *
 *   Permission to use, copy, modअगरy, and/or distribute this software
 *   क्रम any purpose with or without fee is hereby granted, provided
 *   that the above copyright notice and this permission notice appear
 *   in all copies.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, सूचीECT, INसूचीECT, OR
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/*   Qualcomm Atheros SPI रेजिस्टर definition.
 *
 *   This module is deचिन्हित to define the Qualcomm Atheros SPI
 *   रेजिस्टर placeholders.
 */

#अगर_अघोषित _QCA_7K_H
#घोषणा _QCA_7K_H

#समावेश <linux/types.h>

#समावेश "qca_spi.h"

#घोषणा QCA7K_SPI_READ     (1 << 15)
#घोषणा QCA7K_SPI_WRITE    (0 << 15)
#घोषणा QCA7K_SPI_INTERNAL (1 << 14)
#घोषणा QCA7K_SPI_EXTERNAL (0 << 14)

#घोषणा QCASPI_CMD_LEN    2
#घोषणा QCASPI_HW_PKT_LEN 4
#घोषणा QCASPI_HW_BUF_LEN 0xC5B

/*   SPI रेजिस्टरs;                               */
#घोषणा SPI_REG_BFR_SIZE        0x0100
#घोषणा SPI_REG_WRBUF_SPC_AVA   0x0200
#घोषणा SPI_REG_RDBUF_BYTE_AVA  0x0300
#घोषणा SPI_REG_SPI_CONFIG      0x0400
#घोषणा SPI_REG_SPI_STATUS      0x0500
#घोषणा SPI_REG_INTR_CAUSE      0x0C00
#घोषणा SPI_REG_INTR_ENABLE     0x0D00
#घोषणा SPI_REG_RDBUF_WATERMARK 0x1200
#घोषणा SPI_REG_WRBUF_WATERMARK 0x1300
#घोषणा SPI_REG_SIGNATURE       0x1A00
#घोषणा SPI_REG_ACTION_CTRL     0x1B00

/*   SPI_CONFIG रेजिस्टर definition;             */
#घोषणा QCASPI_SLAVE_RESET_BIT  BIT(6)

/*   INTR_CAUSE/ENABLE रेजिस्टर definition.      */
#घोषणा SPI_INT_WRBUF_BELOW_WM  BIT(10)
#घोषणा SPI_INT_CPU_ON          BIT(6)
#घोषणा SPI_INT_ADDR_ERR        BIT(3)
#घोषणा SPI_INT_WRBUF_ERR       BIT(2)
#घोषणा SPI_INT_RDBUF_ERR       BIT(1)
#घोषणा SPI_INT_PKT_AVLBL       BIT(0)

व्योम qcaspi_spi_error(काष्ठा qcaspi *qca);
पूर्णांक qcaspi_पढ़ो_रेजिस्टर(काष्ठा qcaspi *qca, u16 reg, u16 *result);
पूर्णांक qcaspi_ग_लिखो_रेजिस्टर(काष्ठा qcaspi *qca, u16 reg, u16 value, पूर्णांक retry);

#पूर्ण_अगर /* _QCA_7K_H */
