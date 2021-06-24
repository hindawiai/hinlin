<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/linux/mmc/sh_mmcअगर.h
 *
 * platक्रमm data क्रम eMMC driver
 *
 * Copyright (C) 2010 Renesas Solutions Corp.
 */

#अगर_अघोषित LINUX_MMC_SH_MMCIF_H
#घोषणा LINUX_MMC_SH_MMCIF_H

#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>

/*
 * MMCIF : CE_CLK_CTRL [19:16]
 * 1000 : Peripheral घड़ी / 512
 * 0111 : Peripheral घड़ी / 256
 * 0110 : Peripheral घड़ी / 128
 * 0101 : Peripheral घड़ी / 64
 * 0100 : Peripheral घड़ी / 32
 * 0011 : Peripheral घड़ी / 16
 * 0010 : Peripheral घड़ी / 8
 * 0001 : Peripheral घड़ी / 4
 * 0000 : Peripheral घड़ी / 2
 * 1111 : Peripheral घड़ी (sup_pclk set '1')
 */

काष्ठा sh_mmcअगर_plat_data अणु
	अचिन्हित पूर्णांक		slave_id_tx;	/* embedded slave_id_[tr]x */
	अचिन्हित पूर्णांक		slave_id_rx;
	u8			sup_pclk;	/* 1 :SH7757, 0: SH7724/SH7372 */
	अचिन्हित दीर्घ		caps;
	u32			ocr;
पूर्ण;

#घोषणा MMCIF_CE_CMD_SET	0x00000000
#घोषणा MMCIF_CE_ARG		0x00000008
#घोषणा MMCIF_CE_ARG_CMD12	0x0000000C
#घोषणा MMCIF_CE_CMD_CTRL	0x00000010
#घोषणा MMCIF_CE_BLOCK_SET	0x00000014
#घोषणा MMCIF_CE_CLK_CTRL	0x00000018
#घोषणा MMCIF_CE_BUF_ACC	0x0000001C
#घोषणा MMCIF_CE_RESP3		0x00000020
#घोषणा MMCIF_CE_RESP2		0x00000024
#घोषणा MMCIF_CE_RESP1		0x00000028
#घोषणा MMCIF_CE_RESP0		0x0000002C
#घोषणा MMCIF_CE_RESP_CMD12	0x00000030
#घोषणा MMCIF_CE_DATA		0x00000034
#घोषणा MMCIF_CE_INT		0x00000040
#घोषणा MMCIF_CE_INT_MASK	0x00000044
#घोषणा MMCIF_CE_HOST_STS1	0x00000048
#घोषणा MMCIF_CE_HOST_STS2	0x0000004C
#घोषणा MMCIF_CE_CLK_CTRL2	0x00000070
#घोषणा MMCIF_CE_VERSION	0x0000007C

/* CE_BUF_ACC */
#घोषणा BUF_ACC_DMAWEN		(1 << 25)
#घोषणा BUF_ACC_DMAREN		(1 << 24)
#घोषणा BUF_ACC_BUSW_32		(0 << 17)
#घोषणा BUF_ACC_BUSW_16		(1 << 17)
#घोषणा BUF_ACC_ATYP		(1 << 16)

/* CE_CLK_CTRL */
#घोषणा CLK_ENABLE		(1 << 24) /* 1: output mmc घड़ी */
#घोषणा CLK_CLEAR		(0xf << 16)
#घोषणा CLK_SUP_PCLK		(0xf << 16)
#घोषणा CLKDIV_4		(1 << 16) /* mmc घड़ी frequency.
					   * n: bus घड़ी/(2^(n+1)) */
#घोषणा CLKDIV_256		(7 << 16) /* mmc घड़ी frequency. (see above) */
#घोषणा SRSPTO_256		(2 << 12) /* resp समयout */
#घोषणा SRBSYTO_29		(0xf << 8) /* resp busy समयout */
#घोषणा SRWDTO_29		(0xf << 4) /* पढ़ो/ग_लिखो समयout */
#घोषणा SCCSTO_29		(0xf << 0) /* ccs समयout */

/* CE_VERSION */
#घोषणा SOFT_RST_ON		(1 << 31)
#घोषणा SOFT_RST_OFF		0

अटल अंतरभूत u32 sh_mmcअगर_पढ़ोl(व्योम __iomem *addr, पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(addr + reg);
पूर्ण

अटल अंतरभूत व्योम sh_mmcअगर_ग_लिखोl(व्योम __iomem *addr, पूर्णांक reg, u32 val)
अणु
	__raw_ग_लिखोl(val, addr + reg);
पूर्ण

#घोषणा SH_MMCIF_BBS 512 /* boot block size */

अटल अंतरभूत व्योम sh_mmcअगर_boot_cmd_send(व्योम __iomem *base,
					  अचिन्हित दीर्घ cmd, अचिन्हित दीर्घ arg)
अणु
	sh_mmcअगर_ग_लिखोl(base, MMCIF_CE_INT, 0);
	sh_mmcअगर_ग_लिखोl(base, MMCIF_CE_ARG, arg);
	sh_mmcअगर_ग_लिखोl(base, MMCIF_CE_CMD_SET, cmd);
पूर्ण

अटल अंतरभूत पूर्णांक sh_mmcअगर_boot_cmd_poll(व्योम __iomem *base, अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक cnt;

	क्रम (cnt = 0; cnt < 1000000; cnt++) अणु
		पंचांगp = sh_mmcअगर_पढ़ोl(base, MMCIF_CE_INT);
		अगर (पंचांगp & mask) अणु
			sh_mmcअगर_ग_लिखोl(base, MMCIF_CE_INT, पंचांगp & ~mask);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक sh_mmcअगर_boot_cmd(व्योम __iomem *base,
				    अचिन्हित दीर्घ cmd, अचिन्हित दीर्घ arg)
अणु
	sh_mmcअगर_boot_cmd_send(base, cmd, arg);
	वापस sh_mmcअगर_boot_cmd_poll(base, 0x00010000);
पूर्ण

अटल अंतरभूत पूर्णांक sh_mmcअगर_boot_करो_पढ़ो_single(व्योम __iomem *base,
					       अचिन्हित पूर्णांक block_nr,
					       अचिन्हित दीर्घ *buf)
अणु
	पूर्णांक k;

	/* CMD13 - Status */
	sh_mmcअगर_boot_cmd(base, 0x0d400000, 0x00010000);

	अगर (sh_mmcअगर_पढ़ोl(base, MMCIF_CE_RESP0) != 0x0900)
		वापस -1;

	/* CMD17 - Read */
	sh_mmcअगर_boot_cmd(base, 0x11480000, block_nr * SH_MMCIF_BBS);
	अगर (sh_mmcअगर_boot_cmd_poll(base, 0x00100000) < 0)
		वापस -1;

	क्रम (k = 0; k < (SH_MMCIF_BBS / 4); k++)
		buf[k] = sh_mmcअगर_पढ़ोl(base, MMCIF_CE_DATA);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sh_mmcअगर_boot_करो_पढ़ो(व्योम __iomem *base,
					अचिन्हित दीर्घ first_block,
					अचिन्हित दीर्घ nr_blocks,
					व्योम *buf)
अणु
	अचिन्हित दीर्घ k;
	पूर्णांक ret = 0;

	/* In data transfer mode: Set घड़ी to Bus घड़ी/4 (about 20Mhz) */
	sh_mmcअगर_ग_लिखोl(base, MMCIF_CE_CLK_CTRL,
			CLK_ENABLE | CLKDIV_4 | SRSPTO_256 |
			SRBSYTO_29 | SRWDTO_29 | SCCSTO_29);

	/* CMD9 - Get CSD */
	sh_mmcअगर_boot_cmd(base, 0x09806000, 0x00010000);

	/* CMD7 - Select the card */
	sh_mmcअगर_boot_cmd(base, 0x07400000, 0x00010000);

	/* CMD16 - Set the block size */
	sh_mmcअगर_boot_cmd(base, 0x10400000, SH_MMCIF_BBS);

	क्रम (k = 0; !ret && k < nr_blocks; k++)
		ret = sh_mmcअगर_boot_करो_पढ़ो_single(base, first_block + k,
						   buf + (k * SH_MMCIF_BBS));

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम sh_mmcअगर_boot_init(व्योम __iomem *base)
अणु
	/* reset */
	sh_mmcअगर_ग_लिखोl(base, MMCIF_CE_VERSION, SOFT_RST_ON);
	sh_mmcअगर_ग_लिखोl(base, MMCIF_CE_VERSION, SOFT_RST_OFF);

	/* byte swap */
	sh_mmcअगर_ग_लिखोl(base, MMCIF_CE_BUF_ACC, BUF_ACC_ATYP);

	/* Set block size in MMCIF hardware */
	sh_mmcअगर_ग_लिखोl(base, MMCIF_CE_BLOCK_SET, SH_MMCIF_BBS);

	/* Enable the घड़ी, set it to Bus घड़ी/256 (about 325Khz). */
	sh_mmcअगर_ग_लिखोl(base, MMCIF_CE_CLK_CTRL,
			CLK_ENABLE | CLKDIV_256 | SRSPTO_256 |
			SRBSYTO_29 | SRWDTO_29 | SCCSTO_29);

	/* CMD0 */
	sh_mmcअगर_boot_cmd(base, 0x00000040, 0);

	/* CMD1 - Get OCR */
	करो अणु
		sh_mmcअगर_boot_cmd(base, 0x01405040, 0x40300000); /* CMD1 */
	पूर्ण जबतक ((sh_mmcअगर_पढ़ोl(base, MMCIF_CE_RESP0) & 0x80000000)
		 != 0x80000000);

	/* CMD2 - Get CID */
	sh_mmcअगर_boot_cmd(base, 0x02806040, 0);

	/* CMD3 - Set card relative address */
	sh_mmcअगर_boot_cmd(base, 0x03400040, 0x00010000);
पूर्ण

#पूर्ण_अगर /* LINUX_MMC_SH_MMCIF_H */
