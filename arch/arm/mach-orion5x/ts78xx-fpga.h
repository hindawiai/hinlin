<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा TS7800_FPGA_MAGIC 0x00b480
#घोषणा FPGAID(_magic, _rev) ((_magic << 8) + _rev)

/*
 * get yer id's from http://ts78xx.digriz.org.uk/
 * करो *not* make up your own or 'borrow' any!
 */
क्रमागत fpga_ids अणु
	/* Technologic Systems */
	TS7800_REV_1	= FPGAID(TS7800_FPGA_MAGIC, 0x01),
	TS7800_REV_2	= FPGAID(TS7800_FPGA_MAGIC, 0x02),
	TS7800_REV_3	= FPGAID(TS7800_FPGA_MAGIC, 0x03),
	TS7800_REV_4	= FPGAID(TS7800_FPGA_MAGIC, 0x04),
	TS7800_REV_5	= FPGAID(TS7800_FPGA_MAGIC, 0x05),
	TS7800_REV_6	= FPGAID(TS7800_FPGA_MAGIC, 0x06),
	TS7800_REV_7	= FPGAID(TS7800_FPGA_MAGIC, 0x07),
	TS7800_REV_8	= FPGAID(TS7800_FPGA_MAGIC, 0x08),
	TS7800_REV_9	= FPGAID(TS7800_FPGA_MAGIC, 0x09),

	/* Unafक्रमdable & Expensive */
	UAE_DUMMY	= FPGAID(0xffffff, 0x01),
पूर्ण;

काष्ठा fpga_device अणु
	अचिन्हित		present:1;
	अचिन्हित		init:1;
पूर्ण;

काष्ठा fpga_devices अणु
	/* Technologic Systems */
	काष्ठा fpga_device	ts_rtc;
	काष्ठा fpga_device	ts_nand;
	काष्ठा fpga_device	ts_rng;
पूर्ण;

काष्ठा ts78xx_fpga_data अणु
	अचिन्हित पूर्णांक		id;
	पूर्णांक			state;

	काष्ठा fpga_devices	supports;
पूर्ण;
