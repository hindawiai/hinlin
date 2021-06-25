<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा MMC_STRPCL	0x0000
#घोषणा STOP_CLOCK		(1 << 0)
#घोषणा START_CLOCK		(2 << 0)

#घोषणा MMC_STAT	0x0004
#घोषणा STAT_END_CMD_RES		(1 << 13)
#घोषणा STAT_PRG_DONE			(1 << 12)
#घोषणा STAT_DATA_TRAN_DONE		(1 << 11)
#घोषणा STAT_CLK_EN			(1 << 8)
#घोषणा STAT_RECV_FIFO_FULL		(1 << 7)
#घोषणा STAT_XMIT_FIFO_EMPTY		(1 << 6)
#घोषणा STAT_RES_CRC_ERR		(1 << 5)
#घोषणा STAT_SPI_READ_ERROR_TOKEN	(1 << 4)
#घोषणा STAT_CRC_READ_ERROR		(1 << 3)
#घोषणा STAT_CRC_WRITE_ERROR		(1 << 2)
#घोषणा STAT_TIME_OUT_RESPONSE		(1 << 1)
#घोषणा STAT_READ_TIME_OUT		(1 << 0)

#घोषणा MMC_CLKRT	0x0008		/* 3 bit */

#घोषणा MMC_SPI		0x000c
#घोषणा SPI_CS_ADDRESS		(1 << 3)
#घोषणा SPI_CS_EN		(1 << 2)
#घोषणा CRC_ON			(1 << 1)
#घोषणा SPI_EN			(1 << 0)

#घोषणा MMC_CMDAT	0x0010
#घोषणा CMDAT_SDIO_INT_EN	(1 << 11)
#घोषणा CMDAT_SD_4DAT		(1 << 8)
#घोषणा CMDAT_DMAEN		(1 << 7)
#घोषणा CMDAT_INIT		(1 << 6)
#घोषणा CMDAT_BUSY		(1 << 5)
#घोषणा CMDAT_STREAM		(1 << 4)	/* 1 = stream */
#घोषणा CMDAT_WRITE		(1 << 3)	/* 1 = ग_लिखो */
#घोषणा CMDAT_DATAEN		(1 << 2)
#घोषणा CMDAT_RESP_NONE		(0 << 0)
#घोषणा CMDAT_RESP_SHORT	(1 << 0)
#घोषणा CMDAT_RESP_R2		(2 << 0)
#घोषणा CMDAT_RESP_R3		(3 << 0)

#घोषणा MMC_RESTO	0x0014	/* 7 bit */

#घोषणा MMC_RDTO	0x0018	/* 16 bit */

#घोषणा MMC_BLKLEN	0x001c	/* 10 bit */

#घोषणा MMC_NOB		0x0020	/* 16 bit */

#घोषणा MMC_PRTBUF	0x0024
#घोषणा BUF_PART_FULL		(1 << 0)

#घोषणा MMC_I_MASK	0x0028

/*PXA27x MMC पूर्णांकerrupts*/
#घोषणा SDIO_SUSPEND_ACK  	(1 << 12)
#घोषणा SDIO_INT          	(1 << 11)
#घोषणा RD_STALLED        	(1 << 10)
#घोषणा RES_ERR           	(1 << 9)
#घोषणा DAT_ERR           	(1 << 8)
#घोषणा TINT              	(1 << 7)

/*PXA2xx MMC पूर्णांकerrupts*/
#घोषणा TXFIFO_WR_REQ		(1 << 6)
#घोषणा RXFIFO_RD_REQ		(1 << 5)
#घोषणा CLK_IS_OFF		(1 << 4)
#घोषणा STOP_CMD		(1 << 3)
#घोषणा END_CMD_RES		(1 << 2)
#घोषणा PRG_DONE		(1 << 1)
#घोषणा DATA_TRAN_DONE		(1 << 0)

#अगर defined(CONFIG_PXA27x) || defined(CONFIG_PXA3xx)
#घोषणा MMC_I_MASK_ALL          0x00001fff
#अन्यथा
#घोषणा MMC_I_MASK_ALL          0x0000007f
#पूर्ण_अगर

#घोषणा MMC_I_REG	0x002c
/* same as MMC_I_MASK */

#घोषणा MMC_CMD		0x0030

#घोषणा MMC_ARGH	0x0034	/* 16 bit */

#घोषणा MMC_ARGL	0x0038	/* 16 bit */

#घोषणा MMC_RES		0x003c	/* 16 bit */

#घोषणा MMC_RXFIFO	0x0040	/* 8 bit */

#घोषणा MMC_TXFIFO	0x0044	/* 8 bit */
