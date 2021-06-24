<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Renesas RPC-IF core driver
 *
 * Copyright (C) 2018~2019 Renesas Solutions Corp.
 * Copyright (C) 2019 Macronix International Co., Ltd.
 * Copyright (C) 2019-2020 Cogent Embedded, Inc.
 */

#अगर_अघोषित __RENESAS_RPC_IF_H
#घोषणा __RENESAS_RPC_IF_H

#समावेश <linux/pm_runसमय.स>
#समावेश <linux/types.h>

क्रमागत rpcअगर_data_dir अणु
	RPCIF_NO_DATA,
	RPCIF_DATA_IN,
	RPCIF_DATA_OUT,
पूर्ण;

काष्ठा	rpcअगर_op अणु
	काष्ठा अणु
		u8 buswidth;
		u8 opcode;
		bool ddr;
	पूर्ण cmd, ocmd;

	काष्ठा अणु
		u8 nbytes;
		u8 buswidth;
		bool ddr;
		u64 val;
	पूर्ण addr;

	काष्ठा अणु
		u8 ncycles;
		u8 buswidth;
	पूर्ण dummy;

	काष्ठा अणु
		u8 nbytes;
		u8 buswidth;
		bool ddr;
		u32 val;
	पूर्ण option;

	काष्ठा अणु
		u8 buswidth;
		अचिन्हित पूर्णांक nbytes;
		क्रमागत rpcअगर_data_dir dir;
		bool ddr;
		जोड़ अणु
			व्योम *in;
			स्थिर व्योम *out;
		पूर्ण buf;
	पूर्ण data;
पूर्ण;

काष्ठा	rpcअगर अणु
	काष्ठा device *dev;
	व्योम __iomem *dirmap;
	काष्ठा regmap *regmap;
	काष्ठा reset_control *rstc;
	माप_प्रकार size;
	क्रमागत rpcअगर_data_dir dir;
	u8 bus_size;
	व्योम *buffer;
	u32 xferlen;
	u32 smcr;
	u32 smadr;
	u32 command;		/* DRCMR or SMCMR */
	u32 option;		/* DROPR or SMOPR */
	u32 enable;		/* DRENR or SMENR */
	u32 dummy;		/* DRDMCR or SMDMCR */
	u32 ddr;		/* DRDRENR or SMDRENR */
पूर्ण;

पूर्णांक  rpcअगर_sw_init(काष्ठा rpcअगर *rpc, काष्ठा device *dev);
व्योम rpcअगर_hw_init(काष्ठा rpcअगर *rpc, bool hyperflash);
व्योम rpcअगर_prepare(काष्ठा rpcअगर *rpc, स्थिर काष्ठा rpcअगर_op *op, u64 *offs,
		   माप_प्रकार *len);
पूर्णांक rpcअगर_manual_xfer(काष्ठा rpcअगर *rpc);
sमाप_प्रकार rpcअगर_dirmap_पढ़ो(काष्ठा rpcअगर *rpc, u64 offs, माप_प्रकार len, व्योम *buf);

अटल अंतरभूत व्योम rpcअगर_enable_rpm(काष्ठा rpcअगर *rpc)
अणु
	pm_runसमय_enable(rpc->dev);
पूर्ण

अटल अंतरभूत व्योम rpcअगर_disable_rpm(काष्ठा rpcअगर *rpc)
अणु
	pm_runसमय_disable(rpc->dev);
पूर्ण

#पूर्ण_अगर // __RENESAS_RPC_IF_H
